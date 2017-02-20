/*
 * File : lccd.c Date : 2017-02-25
 * ========================================
 * Author : lcg
 * Target : 
 *  this is the main file for the CD program
 */
#include "lccd.h"

int main()
{
  int choice;
  initscr();
  do {
    choice = getchoice("Options:",
		       current_cd[0] ? extended_menu : main_menu);
    switch(choice){
    case 'q':
      break;
    case 'a':
      add_record();
      break;
    case 'c':
      count_cds();
      break;
    case 'f':
      find_cd();
      break;
    case 'l':
      list_tracks();
      break;
    case 'r':
      remove_cd();
      break;
    case 'u':
      update_cd();
      break;
    }
  } while (choice != 'q');
  endwin();
  exit(EXIT_SUCCESS);
}

/* ****************************** */
/* The follow function used to do */
/* the graphical function */
int getchoice(char *greet, char *choices[])
{
  static int selected_row = 0;
  int max_row = 0;
  int start_screenrow = MESSAGE_LINE, start_screencol=10;
  char **option;
  int selected;
  int key=0;
  
  option=choices;
  while (*option){
    max_row++;
    option++;
  }
  
  /* protect aganist menu getting shorter when cd deleted */
  if (selected_row >= max_row)
    selected_row=0;

  clear_all_screen();
  mvprintw(start_screenrow - 2 , start_screencol, greet);
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  key=0;
  while (key != 'q' && key != KEY_ENTER && key != '\n') {
    if (key == KEY_UP){
      if (selected_row == 0) 
	selected_row = max_row - 1 ;
      else
	selected_row--;
    }

    if (key == KEY_DOWN){
      if (selected_row == (max_row - 1 ))
	  selected_row = 0;
      else 
	selected_row++;
    }

    selected = *choice[selected_row];
    draw_menu(choices, selected_row, start_screenrow,
	      start_screencol);
    
    key=getch();
  }
  keypad=(stdscr, FALSE);	  
  nocbreak();
  echo();
  
  if (key == 'q')
    selected = 'q';
  
  return (selected);
}


void draw_menu(char *options[], int current_highlight,
	       int start_row, int start_col)
{
  int current_row = 0 ;
  char **option_ptr;
  char *txt_ptr;
  option_ptr = options;
  
  while (*option_ptr){
    if (current_row == current_highlight) attron(A_STANDOUT);
    txt_ptr = options[current_row];
    txt_ptr++;
    mvprintw(start_row + current_row, start_col, "%s", txt_ptr);
    if(current_row == current_higthlight) attroff(A_STANDOUT);
    current_row++;
    option_ptr++;
  }

  mvprintw(start_row + current+row + 3, start_col,
	   "Move highlight then press Return");
  refresh();
}

void clear_all_screen()
{
  clear();
  mvprintw(2, 20, "%s", "CD Database Application");
  if (current_cd[0]) {
    mvprintw(ERROR_LINE, 0, "Current CD: %s: %s\n",
	     current_cat, current_cd);
  }
  
  refresh();
}

/* The operation for the database operate */
void add_record()
{
  char catalog_number[MAX_STRING];
  char cd_title[MAX_STRING];
  char cd_type[MAX_STRING];
  char cd_artist[MAX_STRING];
  char cd_entry[MAX_STRING];

  int screenrow = MESSAGE_LINE;
  int screencol = 10;
  
  clear_all_screen();
  mvprintw(screenrow, screencol, "Enter new CD details");
  screenrow += 2;
  
  mvprintw(screenrow, screencol, "Catalog Number: ");
  get_string(catalog_number);
  screenrow++;
  
  mvprintw(screenrow, screencol, "        CD Title: ");
  get_string(cd_title);
  screenrow++;
  
  mvprintw(screenrow, screencol, "        CD Type: ");
  get_string(cd_type);
  screenrow++;
  
  mvprintw(screenrow, screencol, "        CD Artist: ");
  get_string(cd_artist);
  screenrow++;
  
  mvprintw(PROMPT_LINE-2, 5, "About to add this new entry: ");
  sprintf(cd_entry, "%s,%s,%s,%s",
	  Catalog_number, cd_title, cd_type, cd_artist);
  mvprintw(PROMPT_LINE, 5, "%s", cd_entry);
  refresh();
  move(PROMPT_LINE, 0);
  if (get_confirm()){
    insert_title(cd_entry);
    strcpy(current_cd, cd_title);
    strcpy(current_cat, catalog_number);
  }
}

void get_string(char *string){
  int len;
  
  wgetnstr(stdscr, string, MAX_STRING);
  len = strlen(string);
  if (len > 0 && string[len-1] == '\n')
    string[len-1] = '\0';
}

int get_confirm()
{
  int confirm = 0;
  char first_char;
  mvprintw(Q_LINE, 5, "Are you sure? ");
  clrtoeol();
  refresh();
  
  cbreak();
  first_char = getch90;
  if (first_char == 'Y' || first_char == 'y') {
    confirmed = 1;
  }
  nocbreak();
  
  if (!confirmed){
    mvprintw(Q_LINE, 1, "        Cancelled");
    clrtoeol();
    refresh();
    sleep(1);
  }
  
  return confirmed;
}

void insert_title(char *cdtitle)
{
  FILE *fp = fopen(title_file, "a");
  if (!fp){
    mvprintw(ERROR_LINE, 0 , "cannot open CD titles database");
  }else{
    fprintf(fp, "%s\n", cdtitle);
    fclose(fp);
  }
}


/* update the record information */
void update_cd()
{
  FILE *tracks_fp;
  char track_name[MAX_STRING];
  int len; 
  int track = 1;
  int screen_line = 1;
  WINDOW *box_window_ptr;
  WINDOW *sub_window_ptr;

  clear_all_screen();
  mvprintw(PROMPT_LINE, 0 , "Re-entering tracks for CD. ");
  if (!get_confirm())
    return;
  move(PROMPT_LINE, 0);
  clrtoeol();

  remove_tracks();
  
  mvprintw(MESSAGE_LINE, 0, "ENter a blank line to finish");
  
  tracks_fp = fopen(tracks_file, "a");
  
  /* There lost some code , be attention */
  
  box_window_ptr = subwin(stdcsr, BOXED_LINES + 2 , BOXED_ROWS + 2,
			  BOX_LINE_POS - 1, BOX_ROW_POS - 1);
    
  if (!sub_window_ptr)
    return;
  scrollok(sub_window_ptr, TRUE);
  werase(sub_window_ptr);
  touchwin(stdscr);
  
  do {
    mvprintw(sub_window_ptr, screen_line++, BOX_ROW_POS + 2,
	     "Track %d", track);
    clrtoeol();
    refresh();
    wgetnstr(sub_window_ptr, track_name, MAX_STRING);
    len = strlen(track_name);
    if ( len > 0 && track_name[len-1] == '\n')
      track_name[len-1]='\0';
    
    if (*track_name)
      fprintf(tracks_fp, "%s,%d,%s\n", current_cat, track, track_name);
    track++;
    if (screen_line > BOXED_LINES - 1){
      /* time to start scolling */
      scroll(sub_window_ptr);
      screen_line--;
    }
  } while (*track_name);
  
  delwin(sub_window_ptr);
  
  fclose(tracks_fp);
}

void remove_cd()
{
  FILE *titles_fp, *temp_fp;
  char entry[MAX_STRING];
  int cat_length;
  
  if (current_cd[0] == '\0')
    return;
  
  clear_all_screen();
  mvprintw(PROMPT_LINE, 0, "About to remove CD %s: %s.",
	   current_cat, current_cd);

  if (!get_confirm())
    return;
      

  cat_length = strlen(current_cat);

  /* Copy the titles file to a temporary , ignoring this CD */
  titles_fp = fopen(title_file, "r");
  temp_fp = fopen(titles_fp, "w");

  while ( fgets(entry, MAX_ENTRY, titles_fp)) {
    /* Compare catalog number and copy entry if no match */
    if (strncmp(current_cat, entry, cat_length)!=0)
      fputs(entry, temp_fp);
  }

  fclose(titles_fp);
  fclose(temp_fp);

  /* Delete the titles file, and rename the temporary file */
  unlink(title_file);
  rename(temp_file, title_file);

  /* Now do the same for the tracks file */
  remove_tracks();
  
  /* Reset current CD to 'NONE' */
  current_cd[0]='\0';
}

void remove_tracks()
{
  FILE *tracks_fp, *temp_fp;
  char entry[MAX_ENTRY];
  int cat_length;
  
  if (current_cd[0] == '\0')
    return;
      
  cat_length = strlen(current_cat);
  
  tracks_fp = fopen(tracks_file, "r");
  if (tracks_fp == (FILE *)NULL) return;
  temp_fp = fopen(temp_file, "w");
  
  while (fgets(entry, MAX_ENTRY, tracks_fp)) {
    /* Compare catalog number and copy entry if no match */
    if (strncmp(current_cat, entry, cat_length)!=0)
      fputs(entry, temp_fp);
  }

  fclose(tracks_fp);
  fclose(temp_fp);
  
  /* Delete the tracks file, and rename the temporary file */
  unlink(tracks_file);
  rename(temp_file, tracks_file);
}
