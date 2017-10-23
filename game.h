#ifndef  __GAME_H__
#define  __GAME_H__

#define COLS 11
#define ROWS 11
#define MAX 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void Display(char arr[COLS][ROWS], int col, int row);
void set_mine(char mine[COLS][ROWS], int col, int row);
int get_mine_count(char mine[COLS][ROWS],int x,int y);
void reset_mine(char mine[COLS][ROWS], int col, int row, int x, int y);
void extend(char mine[COLS][ROWS], int x, int y, int* win, char show[COLS][ROWS]);

#endif //__GAME_H__
