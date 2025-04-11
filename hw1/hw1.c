#include "hw1.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// For the value of Pi, please use M_PI, which is defined in math.h.
double area_of_disk(double radius) {
  return (M_PI * (radius * radius));
}

double area_of_ring(double outer_radius, double inner_radius) {   
  return area_of_disk(outer_radius) - area_of_disk(inner_radius);
}

int bigger_minus_smaller(int a, int b) {
  return (a > b) ? (a - b) : (b - a);
}

bool value_in_range(int lower_bound, int x, int upper_bound) {
  if (x >= lower_bound && x <= upper_bound){
  	return true;
  }else{
	return false;
  }
}

int sum_of_greater_squares(int a, int b, int c) {
  if ((a * a) < (b * b) && (a * a) < (c * c)){
	return ((b * b) + (c * c));
  }else if ((b * b) < (a * a) && (b * b) < (c * c)){
	return ((a * a) + (c * c));
  }else{
	return ((a * a) + (b * b));
  }
}
