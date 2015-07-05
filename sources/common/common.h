/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 05:49:07 by achazal           #+#    #+#             */
/*   Updated: 2015/06/08 05:49:10 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_COLOR_RED_LEN     (sizeof(ANSI_COLOR_RED))
#define ANSI_COLOR_GREEN_LEN   (sizeof(ANSI_COLOR_GREEN))
#define ANSI_COLOR_YELLOW_LEN  (sizeof(ANSI_COLOR_YELLOW))
#define ANSI_COLOR_BLUE_LEN    (sizeof(ANSI_COLOR_BLUE))
#define ANSI_COLOR_MAGENTA_LEN (sizeof(ANSI_COLOR_MAGENTA))
#define ANSI_COLOR_CYAN_LEN    (sizeof(ANSI_COLOR_CYAN))
#define ANSI_COLOR_RESET_LEN   (sizeof(ANSI_COLOR_RESET))

#endif