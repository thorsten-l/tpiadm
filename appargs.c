#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <argp.h>
#include "appargs.h"

const char *argp_program_version =
        "tpiadm 1.0.1, Dr. Thorsten Ludewig <t.ludewig@gmail.com>";
const char *argp_program_bug_address = "<t.ludewig@gmail.com>";

static struct argp_option options[] = {
  {"verbose", 'v', 0, 0, "verbose output"},
  {"info", 'i', 0, 0, "show slots info"},
  {"set", 's', 0, 0, "set slot power mode"},
  {"slot", 'n', "SLOT-ID", 0, "slot number (1-7)"},
  {"power", 'p', "POWER", 0, "power 0=OFF, 1=ON"},
  {0}
};

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
    case 'v':
      arguments->verbose = 1;
      break;
    case 'i':
      arguments->show_info = 1;
      break;
    case 's':
      arguments->set_mode = 1;
      break;
    case 'n':
      arguments->slot_number = atoi(arg);
      break;
    case 'p':
      arguments->slot_power = atoi(arg);
      break;
    case ARGP_KEY_ARG:
      break;
    case ARGP_KEY_END:
      if (arguments->show_info == 0 && arguments->set_mode == 0) {
        argp_usage(state);
      }
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static char args_doc[] = "";

static char doc[] = "tpiadm -- TuringPi V1 slot administration tool.";

static struct argp argp = {options, parse_opt, args_doc, doc};

struct arguments arguments;

void init_appargs(int argc, char** argv) {
  arguments.verbose = 0;
  arguments.show_info = 0;
  arguments.set_mode = 0;
  arguments.slot_number = -1;
  arguments.slot_power = -1;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.set_mode) {
    
    if (arguments.slot_number == -1) {
      puts("ERROR: slot number is missing. --slot=NUMBER (1..7)");
      exit(-3);
    }

    if (arguments.slot_number < 1 || arguments.slot_number > 7) {
      puts("ERROR: Wrong slot number. (valid slots = 1..7)");
      exit(-4);
    }

    if (arguments.slot_power == -1) {
      puts("ERROR: power state is missing. --power=STATE (0=OFF|1=ON)");
      exit(-3);
    }

    if (arguments.slot_power < 0 || arguments.slot_power > 1) {
      puts("ERROR: Wrong power state. (valid states = 0=OFF|1=ON)");
      exit(-4);
    }
  }
}

