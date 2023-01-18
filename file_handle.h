/**
 * @file      : file_handle.h
 * @brief     : Linux平台文件处理函数接口头文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-01-18 11:23:13
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-01-16 huenrong        创建文件
 *
 */

#ifndef __FILE_HANDLE_H
#define __FILE_HANDLE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  获取文件大小
 * @param  file_name: 输入参数, 待获取文件
 * @return 成功: 文件大小(单位: bytes)
 *         失败: -1
 */
long int get_file_size(const char *file_name);

/**
 * @brief  计算文件md5校验
 * @param  file_md5 : 输出参数, 获取到的文件md5校验
 * @param  file_name: 输入参数, 待获取文件
 * @return true : 成功
 * @return false: 失败
 */
bool get_file_md5(char *file_md5, const char *file_name);

#ifdef __cplusplus
}
#endif

#endif // __FILE_HANDLE_H
