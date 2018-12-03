/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrysh <dpetrysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:41:21 by dpetrysh          #+#    #+#             */
/*   Updated: 2018/11/30 12:41:22 by dpetrysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <string.h>
#include <stdlib.h>

// void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}

void	show_map(unsigned char *map)
{
	initscr();			/* Start curses mode 		*/
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_CYAN);
	attron(COLOR_PAIR(1));
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			mvprintw(i + 2 , 1 + 4 * j,"%02hhx ", map[j + i * 64]);
		}
	}
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	for (int i = 0; i < 256; i++)
	{
		mvprintw(0 , i,"%s", " ");
	}
	attroff(COLOR_PAIR(1));
    	getch();
	endwin();
}
