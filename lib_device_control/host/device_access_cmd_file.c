// Copyright (c) 2018, XMOS Ltd, All rights reserved
#if USE_CMD_FILE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "control_host.h"
#include "control_host_support.h"
#include "util.h"
#include "xmos_beclear_control.h"

//#define DBG(x) x
#define DBG(x)

FILE *pCMD_FILE;

control_ret_t control_init_cmd_file(void)
{
  pCMD_FILE = fopen("command_file.txt", "a");
  if(pCMD_FILE==NULL) 
  {
    printf("Error opening file.\n");
    return CONTROL_ERROR;
  }
  return CONTROL_SUCCESS;
}

control_ret_t
control_write_command(control_resid_t resid, control_cmd_t cmd,
                      const uint8_t payload[], size_t payload_len)
{
  char cmd_string[256];
  char tmp_string[256];
  sprintf(cmd_string, "resid:%d cmd:%d len:%d payload:", resid, cmd, (unsigned)payload_len);
  for (int i = 0; i < payload_len; i++)
  {  
    sprintf(tmp_string, "%02x ", payload[i]);
    strcat(cmd_string, tmp_string);
  }
  sprintf(tmp_string, "\n");
  strcat(cmd_string, tmp_string);
  printf("%s", cmd_string);
  fprintf(pCMD_FILE, "%s", cmd_string);
  return CONTROL_SUCCESS;
}

control_ret_t
control_read_command(control_resid_t resid, control_cmd_t cmd,
                     uint8_t payload[], size_t payload_len)
{
  //Not supported
  //return CONTROL_ERROR;
  unsigned ver = SMARTTV;
  //ver = SMARTHOME;
  memcpy(payload, &ver, sizeof(unsigned));
  printf("resid:%d cmd:0x%02x payload_len:%d\n", resid, cmd, (unsigned)payload_len );
  return CONTROL_SUCCESS;
}

control_ret_t control_cleanup_cmd_file(void)
{
  //close(fd);
  return CONTROL_SUCCESS;
}

#endif // USE_CMD_FILE
