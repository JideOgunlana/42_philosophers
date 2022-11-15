/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:25:35 by bogunlan          #+#    #+#             */
/*   Updated: 2022/11/14 17:14:54 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

# define RESET "\e[0m"

// foreground colour code
# define BLACK "\e[30m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define DEFAULT "\e[39m"

//Background colour code
# define BG_BLACK "\e[40m"
# define BG_RED "\e[41m"
# define BG_GREEN "\e[42m"
# define BG_YELLOW "\e[43m"
# define BG_BLUE "\e[44m"
# define BG_MAGENTA "\e[45m"
# define BG_CYAN "\e[46m"
# define BG_WHITE "\e[47m"
# define BG_DEFAULT "\e[49m"

// Graphics mode
# define BOLD "\e[1m"
# define DIM "\e[2m"
# define ITALIC "\e[3m"
# define U_LINE "\e[4m"
# define BLINK "\e[5m"
# define REVERSE "\e[6m"
# define HIDDEN "\e[7m"
# define STRIKE "\e[8m"

#endif