/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrysh <dpetrysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:36:14 by dpetrysh          #+#    #+#             */
/*   Updated: 2018/12/03 14:36:15 by dpetrysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h> 
#include <unistd.h>

void draw_borders(WINDOW *screen)
{
	int x, y, i;
	getmaxyx(screen, y, x);
	// 4 corners
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	// sides
	for (i = 1; i < (y - 1); i++)
	{ mvwprintw(screen, i, 0, "|");
	mvwprintw(screen, i, x - 1, "|"); }
	// top and bottom
	for (i = 1; i < (x - 1); i++)
	{
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}


int main(int argc, char *argv[])
{
		int parent_x, parent_y;
 	int score_size = 3; 
 	initscr();
  	noecho(); 
  	curs_set(FALSE);
   // get our maximum window dimensions
    getmaxyx(stdscr, parent_y, parent_x); 
   // set up initial windows 
	WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
    WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0); // draw to our windows
	//draw our borders
	draw_borders(field);
	draw_borders(score);
	// simulate the game loop
	while(1)
	{
		// draw to our windows
		mvwprintw(field, 1, 1, "Field");
		mvwprintw(score, 1, 1, "Score");
		// refresh each window
		wrefresh(field);
		wrefresh(score);
	}
	// clean up
	delwin(field);
	delwin(score);
	// ...
}



// int main(int argc, char *argv[])
// { 
// 	int parent_x, parent_y;
//  	int score_size = 3; 
//  	initscr();
//   	noecho(); 
//   	curs_set(FALSE);
//    // get our maximum window dimensions
//     getmaxyx(stdscr, parent_y, parent_x); 
//    // set up initial windows 
// 	WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
//     WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0); // draw to our windows 
//     mvwprintw(field, 0, 0, "Field");
//     mvwprintw(score, 0, 0, "Score"); 
//     // refresh each window 
//     wrefresh(field);
//     wrefresh(score);
//     sleep(5); // clean up 
//     delwin(field);
//     delwin(score);
//     endwin();
//     return 0;
// }