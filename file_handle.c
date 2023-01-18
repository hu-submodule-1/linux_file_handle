/**
 * @file      : file_handle.c
 * @brief     : Linux平台文件处理函数接口源文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-01-18 11:23:07
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-01-16 huenrong        创建文件
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "./file_handle.h"

/**
 * @brief  执行命令并获取输出结果
 * @param  result: 输出参数, 命令输出结果
 * @param  cmd   : 输入参数, 待执行命令
 * @return true : 成功
 * @return false: 失败
 */
static bool exec_cmd(char *result, const char *cmd)
{
    // 执行结果
    char result_buf[1024] = {0};
    FILE *ptr = NULL;

    if ((!result) || (!cmd))
    {
        return false;
    }

    ptr = popen(cmd, "r");
    if (NULL != ptr)
    {
        // 循环获取返回值, 一行一行的获取
        while (NULL != fgets(result_buf, 1024, ptr))
        {
            // 将当前行数据, 追加到目标buf
            strcat(result, result_buf);

            // 获取结果长度过长, 返回错误
            if (strlen(result) > 1024)
            {
                pclose(ptr);
                ptr = NULL;

                return false;
            }
        }

        pclose(ptr);
        ptr = NULL;

        return true;
    }

    return false;
}

/**
 * @brief  获取文件大小
 * @param  file_name: 输入参数, 待获取文件
 * @return 成功: 文件大小(单位: bytes)
 *         失败: -1
 */
long int get_file_size(const char *file_name)
{
    int ret = -1;
    long int file_size = -1;
    struct stat stat_buf = {0};

    if (!file_name)
    {
        return -1;
    }

    ret = stat(file_name, &stat_buf);
    if (0 != ret)
    {
        return -1;
    }

    file_size = stat_buf.st_size;

    return file_size;
}

/**
 * @brief  计算文件md5校验
 * @param  file_md5 : 输出参数, 获取到的文件md5校验
 * @param  file_name: 输入参数, 待获取文件
 * @return true : 成功
 * @return false: 失败
 */
bool get_file_md5(char *file_md5, const char *file_name)
{
    char cmd[256] = {0};
    char result[256] = {0};

    if ((!file_md5) || (!file_name))
    {
        return false;
    }

    snprintf(cmd, sizeof(cmd), "md5sum %s | cut -d \" \" -f1", file_name);
    if (!exec_cmd(result, cmd))
    {
        return false;
    }

    memcpy(file_md5, result, (strlen(result) - 1));

    return true;
}
