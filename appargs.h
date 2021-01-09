/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   appargs.h
 * Author: Dr. Thorsten Ludewig <t.ludewig@gmail.com>
 *
 * Created on 9. Januar 2021, 18:09
 */

#ifndef APPARGS_H
#define APPARGS_H

#include <argp.h>

#ifdef __cplusplus
extern "C" {
#endif

struct arguments
{
  int verbose;              
  int show_info;
  int set_mode;
  int slot_number;
  int slot_power;
};
  
extern struct arguments arguments;
void init_appargs(int argc, char** argv);

#ifdef __cplusplus
}
#endif

#endif /* APPARGS_H */

