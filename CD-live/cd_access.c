/*
 * File : cd_access.c  Date: 2017-06-14
 * ==============================
 * Author : lcg
 * Target :
 *    the access code for database and sql statement
 */
#define _XOPEN_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include <ndbm.h>
#include "cd_data.h"

#define CDC_FILE_BASE "cdc_data"
#define CDT_FILE_BASE "cdt_data"
#define CDC_FILE_DIR  "cdc_data.dir"
#define CDC_FILE_PAG  "cdc_data.pag"
#define CDT_FILE_DIR  "cdt_data.dir"
#define CDT_FILE_PAG  "cdt_data.pag"

static DBM *cdc_dbm_ptr = NULL;
static DBM *cdt_dbm_ptr = NULL;

int database_initialize(const int new_database)
{
  int open_mode  =  O_CREAT | O_RDWR;
  
  /* if any existing database is open then close it  */
  if (cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
  if (cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);
  
  if (new_database) {
    /* delete the old files */
    (void) unlink(CDC_FILE_DIR);
    (void) unlink(CDC_FILE_PAG);
    (void) unlink(CDT_FILE_DIR);
    (void) unlink(CDT_FILE_PAG);
  }
  
  /* Open some new files , creating them if required */
  cdc_dbm_ptr = dbm_open(CDC_FILE_BASE, open_mode, 0644);
  cdt_dbm_ptr = dbm_open(CDT_FILE_BASE, open_mode, 0644);
  if (!cdc_dbm_ptr || !cdt_dbm_ptr) {
    fprintf(stderr, "Unable to create database\n");
    cdc_dbm_ptr  = cdt_dbm_ptr = NULL;
    return 0;
  }
  
  return 1;
}

void database_close(void)
{
  if (cdc_dbm_ptr) dbm_close(cdc_dbm_ptr);
  if (cdt_dbm_ptr) dbm_close(cdt_dbm_ptr);
  
  cdc_dbm_ptr = cdt_dbm_ptr = NULL;
}

cdc_entry get_cdc_entry(const char *cd_catalog_ptr)
{
  cdc_entry entry_to_return;
  char entry_to_find[CAT_CAT_LEN + 1];
  datum local_data_datum;
  datum local_key_datum;
  
  memset(&entry_to_return, '\0', sizeof(entry_to_return));

  if (!cdc_dbm_ptr || !cdt_dbm_ptr) return entry_to_return;
  if (!cd_catalog_ptr) return entry_to_return;
  if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return entry_to_return;
  
  memset(&entry_to_find, '\0', sizeof(entry_to_find));
  strcpy(entry_to_find, cd_catalog_ptr);

  local_key_datum.dptr = (void *) entry_to_find;
  local_key_datum.dsize = sizeof(entry_to_find);

  memset(&local_data_datum, '\0', sizeof(local_data_datum));
  local_data_datum = dbm_fetch(cdc_dbm_ptr, local_key_datum);
  if (local_data_datum.dptr) {
    memcpy(&entry_to_return , (char *)local_data_datum.ptr,local_data_datum.dsize);
  }
  
  return entry_to_return;
} /* get_cdc_entry */

cdt_entry get_cdt_entry(const char *cd_catalog_ptr, const int track_no)
{
  cdt_entry entry_to_return;
  char entry_to_find(CAT_CAT_LEN + 10];
  datum local_data_datum;
  datum local_key_datum;
  
  memset(&entry_to_return, '\0', sizeof(entry_to_return));
  
  if (!cdc_dbm_ptr || !cdt_dbm_ptr) return entry_to_return;
  if (!cd_catalog_ptr) return entry_to_return;
  if (strlen(cd_catalog_ptr) >= CAT_CAT_LEN) return entry_to_return;
  
  /* set up the search key, which is a composite key of catalog entry and
   track number*/
  memset(&entry_to_find, '\0', sizeof(entry_to_find));
  springf(entry_to_find, "%s %d", cd_catalog_ptr, track_no);
  
  local_key_datum.dptr = (void *) entry_to_return;
  local_key_datum.dsize = sizeof(entry_to_return);
  
  memset(&local_data_datum, '\0', sizeof(local_data_datum));
  local_data_datum = dbm_fetch(cdt_dbm_ptr, local_key_datum);
  if (local_data_datum.dptr) {
    memcpy(&entry_to_return, (char *) local_data_datum.dptr, local_data_datum.dsize);
  }
  
  return entry_to_return
} /* end of get_cdt_entry */

int add_cdc_entry(const cdc_entry entry_to_add)
{
  char key_to_add[CAT_CAT_LEN + 1];
  datum local_key_datum;
  datum local_data_datum;
  int result;
  
  /* check database initialized and parameters valid */
  if (!cdc_dbm_ptr || !cdt_dbm_ptr) return 0;
  if (strlen(entry_to_add.catalog) >= CAT_CAT_LEN) return 0;
  
  /* ensure the search key contains only the valid string and nulls  */
  memset(&key_to_add, '\0', sizeof(key_to_add));
  strcpy(key_to_add, entry_to_add.catalog);
  
  local_key_datum.dptr = (void *) key_to_add;
  local_key_datum.dsize = sizeof(key_to_add);
  local_data_datum.dptr = (void *) &entry_to_add;
  local_data_datum.dsize = sizeof(entry_to_add);
  
  result = dbm_store(cdc_dbm_ptr, local_key_datum, local_data_datum, DBM_REPLACE);
  
  /* dbm_store() uses 0 fore success */
  if (result==0) return 1;
  return 0;
}

int add_cdt_entry(const cdt_entry entry_to_add)
{
  char key_to_add[CAT_CAT_LEN + 10];
  datum local_data_datum;
  datum local_key_datum;
  int result;
  
  if (!cdc_dbm_ptr || !cdt_dbm_ptr) return 0;
  if (strlen(entry_to_add.catalog) >= CAT_CAT_LEN) return 0;
  
  memset(&key_to_add, '\0', sizeof(key_to_add));
  sprintf(key_to_add, "%s %d", entry_to_add.catalog,
	  entry_to_add.track_no);
  
  local_key_datum.dptr = (void *) key_to_add;
  local_key_datum.dsize = sizeof(key_to_add);
  local_data_datum.dptr = (void *) &entry_to_add;
  local_data_datum.dsize = sizeof(entry_to_add);
  
  result = dbm_store(cdt_dbm_ptr, local_key_datum, local_data_datum, DBM_REPLACE);
  
  /* dbm_store() uses o for success and -ve numbers for errors */
  if (result == 0) return 1;
  return 0;
}
