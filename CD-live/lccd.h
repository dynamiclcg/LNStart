/*
 * File : lccd.c Date : 2017-02-25
 * ========================================
 * Author : lcg
 * Target : 
 *    get familiar with the linux graphical design with
 * curses library , the last program is a cd program 
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

/* **** MACRO DEFINE FOR GLOBAL VARIABLES **** */
#define MAX_STRING 80
#define MAX_ENTRY 1024		/* Longest allowed response */

#define MESSAGE_LINE 6		/* Misc. Messages on this rule */
#define ERROR_LINE  22		/* Line to use for errors */
#define Q_LINE      20 		/* Line for questions */
#define PROMPT_LINE 18		/* Line for prompting on */

/* define variable for windows */
#define BOXED_LINES 11
#define BOXED_ROWS  60
#define BOX_LINE_POS 8
#define BOX_ROW_POS  2

/* **** THE GLOBAL STRING **** */
static char current_cd[MAX_STRING] = "\0";
static char current_cat[MAX_STRING];

/* **** Constant define **** */
const char *title_file = "title.cdb";
const char *tracks_file = "tracks.cdb";
const char *temp_file="cdb.tmp";

/* The define for the cd program function */
void cleal_all_screen(void);
void get_return(void);
int get_confirm(void);
int getchoice(char *greet, char *choicesp[]);
void draw_menu(char *options[], int highlisht,
	       int start_row, int start_col);
void insert_title(char *cdtitle);
void get_string(char *string);
void add_record(void);
void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);

char *main_menu[] =
  {
    "add new CD",
    "find CD",
    "count CDs and tracks in the catalog",
    "quit",
    0,
  };

char *extended_menu[] =
  {
    "add new CD",
    "find CD",
    "count CDS and tracks in the catalog",
    "list tracks on current CD",
    "remove current CD",
    "update track information",
    "quit",
    0,
  };
