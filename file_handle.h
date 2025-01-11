/**
 * @file      file_handle.h
 * @brief     Linux平台文件处理函数接口头文件
 * @author    huenrong (huenrong1028@outlook.com)
 * @date      2025-01-11 15:51:06
 *
 * @copyright Copyright (c) 2025 huenrong
 *
 */

#ifndef __FILE_HANDLE_H
#define __FILE_HANDLE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief 执行命令并获取输出结果
 *
 * @param[in] cmd: 待执行命令
 *
 * @return 成功: 命令结果
 * @return 失败: NULL
 */
char *exec_cmd(const char *cmd);

/**
 * @brief 获取文件大小
 *
 * @param[out] file_size: 文件大小
 * @param[in]  file_name: 文件名
 *
 * @return true : 成功
 * @return false: 失败
 */
bool get_file_size(uint32_t *file_size, const char *file_name);

/**
 * @brief 获取文件内容
 *
 * @param[in] file_name: 文件名
 * @param[in] is_binary: 是否是二进制文件(true: 是)
 *
 * @return 成功: 文件内容
 * @return 失败: NULL
 */
char *get_file_data(const char *file_name, const bool is_binary);

/**
 * @brief 计算文件MD5值
 *
 * @note 内部使用md5sum命令实现
 *
 * @param[out] md5      : MD5值
 * @param[in]  file_name: 文件名
 *
 * @return true : 成功
 * @return false: 失败
 */
bool calc_file_md5(char *md5, const char *file_name);

#ifdef __cplusplus
}
#endif

#endif // __FILE_HANDLE_H
