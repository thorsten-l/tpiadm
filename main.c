/* 
 * File:   main.c
 * Author: Dr. Thorsten Ludewig <t.ludewig@gmail.com>
 *
 * Created on 9. Januar 2021, 13:23
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include <argp.h>
#include "appargs.h"

#define I2C_DEVICE_PATH "/dev/i2c-1"
#define I2C_ADDRESS 0x57

#define I2C_TPI_REGISTER_CONTROL 0xf2
#define I2C_TPI_REGISTER_STATUS  0xf8

char *SLOT_STATE_UNKNOWN = "-";
char *SLOT_STATE_EMPTY = "empty";
char *SLOT_STATE_INSTALLED = "installed";

// turing pi 1 slots    -     1     2     3     4     5     6     7
int slot_masks[] = {0x00, 0x02, 0x04, 0x08, 0x10, 0x80, 0x40, 0x20};

/*
 * 
 */
int main(int argc, char** argv) {

  init_appargs(argc, argv);

  int i2c = 0;

  if ((i2c = open(I2C_DEVICE_PATH, O_RDWR)) < 0) {
    puts("Failed to open the i2c device");
    exit - 1;
  }

  if (ioctl(i2c, I2C_SLAVE, I2C_ADDRESS) < 0) {
    puts("Failed to acquire bus access and/or talk to slave.\n");
    exit - 2;
  }

  int control = i2c_smbus_read_byte_data(i2c, I2C_TPI_REGISTER_CONTROL);
  int status = i2c_smbus_read_byte_data(i2c, I2C_TPI_REGISTER_STATUS);

  if (arguments.verbose) {
    puts("\r");
    printf("control register = 0x%02x\r\n", (unsigned char)control );
    printf("status register = 0x%02x\r\n\r\n", (unsigned char)status );
  }

  if (arguments.set_mode) {
    
    printf( "slot #%d power %s\n", 
            arguments.slot_number, ( arguments.slot_power ) ? "ON" : "OFF" );

    int data;
    
    if ( arguments.slot_power )
    {
      data = control | slot_masks[arguments.slot_number];
    }
    else
    {
      data = 0x00ff ^ slot_masks[arguments.slot_number];
      data &= control;
    }
    
    if (arguments.verbose) {
      printf("set control register = 0x%02x\r\n", (unsigned char)data );
    }

    i2c_smbus_write_byte_data( i2c, I2C_TPI_REGISTER_CONTROL, data );
    control = data;
  }
  
  if (arguments.show_info) {
    char *slot_state;

    for (int i = 1; i < 8; i++) {
      unsigned char power_on = (control & slot_masks[i]) != 0;

      if (power_on) {
        if ((status & slot_masks[i]) != 0) {
          slot_state = SLOT_STATE_INSTALLED;
        } else {
          slot_state = SLOT_STATE_EMPTY;
        }
      } else {
        slot_state = SLOT_STATE_UNKNOWN;
      }

      printf("slot %d %s %s\r\n", i, power_on ? "ON" : "OFF", slot_state);
    }
  }

  close(i2c);
  return (EXIT_SUCCESS);
}
