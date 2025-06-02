/**
 * @file      file_handle.c
 * @brief     Linux平台文件处理函数接口源文件
 * @author    huenrong (huenrong1028@outlook.com)
 * @date      2025-01-11 15:53:23
 *
 * @copyright Copyright (c) 2025 huenrong
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "file_handle.h"

char *exec_cmd(const char *cmd)
{
    assert(cmd != NULL);

    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    size_t total_len = 256; // 缓冲区总容量
    size_t used_len = 0;    // 缓冲区已使用容量
    char *result = (char *)malloc(total_len);
    if (result == NULL)
    {
        pclose(fp);

        return NULL;
    }
    result[0] = '\0';

    char read_data[256] = "";
    while (fgets(read_data, sizeof(read_data), fp) != NULL)
    {
        // 本次实际读取的长度
        size_t read_len = strlen(read_data);

        // 需要扩展缓冲区
        size_t need_len = used_len + read_len + 1;
        if (need_len > total_len)
        {
            size_t new_total_len = (total_len * 2 > need_len) ? total_len * 2 : need_len;
            char *new_result = (char *)realloc(result, new_total_len);
            if (new_result == NULL)
            {
                free(result);
                pclose(fp);

                return NULL;
            }
            result = new_result;
            total_len = new_total_len;
        }

        memcpy(result + used_len, read_data, read_len);
        used_len += read_len;
    }

    pclose(fp);
    result[used_len] = '\0';

    char *final_result = (char *)realloc(result, (used_len + 1));
    if (final_result != NULL)
    {
        result = final_result;
    }

    return result;
}

bool get_file_size(uint32_t *file_size, const char *file_name)
{
    assert((file_size != NULL) && (file_name != NULL));

    struct stat file_stat = {0};
    if (stat(file_name, &file_stat) != 0)
    {
        return false;
    }

    *file_size = file_stat.st_size;

    return true;
}

char *get_file_data(const char *file_name, const bool is_binary)
{
    assert(file_name != NULL);

    uint32_t file_size = 0;
    if (!get_file_size(&file_size, file_name))
    {
        return NULL;
    }

    FILE *fp = fopen(file_name, is_binary ? "rb" : "r");
    if (fp == NULL)
    {
        return NULL;
    }

    char *file_data = (char *)malloc(file_size + 1);
    if (file_data == NULL)
    {
        fclose(fp);

        return NULL;
    }

    size_t ret = fread(file_data, 1, file_size, fp);
    fclose(fp);
    if (ret != file_size)
    {
        free(file_data);

        return NULL;
    }

    if (!is_binary)
    {
        file_data[file_size] = '\0';
    }

    return file_data;
}

bool calc_file_md5(char *md5, const char *file_name)
{
    assert((md5 != NULL) && (file_name != NULL));

    int cmd_len = 32 + strlen(file_name);
    char *cmd = (char *)malloc(cmd_len + 1);
    if (cmd == NULL)
    {
        return false;
    }

    snprintf(cmd, cmd_len, "md5sum %s | awk '{print $1}'", file_name);
    char *result = exec_cmd(cmd);
    free(cmd);
    if (result == NULL)
    {
        return false;
    }

    memcpy(md5, result, (strlen(result) - 1));
    free(result);

    return true;
}
