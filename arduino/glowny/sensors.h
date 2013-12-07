#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

typedef struct {
  int16_t magic_number;
  int16_t frame_no;
  int16_t load_cell_a;
  int16_t load_cell_b;
  int16_t load_cell_c;
  int16_t load_cell_d;
  int16_t temp;
  int16_t light;
} Sensors;

#endif
