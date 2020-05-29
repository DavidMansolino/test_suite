#include <webots/gyro.h>
#include <webots/motor.h>
#include <webots/robot.h>

#include "../../../lib/ts_assertion.h"
#include "../../../lib/ts_utils.h"

#define TIME_STEP 32

int main(int argc, char **argv) {
  ts_setup(argv[0]);

  WbDeviceTag motor = wb_robot_get_device("rotational motor");
  WbDeviceTag gyro = wb_robot_get_device("gyro");

  wb_motor_set_position(motor, INFINITY);
  wb_motor_set_velocity(motor, 10.0);

  wb_gyro_enable(gyro, TIME_STEP);

  int i;
  for (i = 0; i < 40; i++)
    wb_robot_step(TIME_STEP);

  const double *values = wb_gyro_get_values(gyro);

  const double expected[] = {0.0, 10.0, 0.0};

  printf("expected = {%f, %f, %f}\n", expected[0], expected[1], expected[2]);
  printf("values = {%f, %f, %f}\n", values[0], values[1], values[2]);
  ts_assert_vec3_in_delta(values[0], values[1], values[2], expected[0], expected[1], expected[2], 0.0001,
                          "The Gyro doesn't return the right angular velocity."
                          " (expected = {%f, %f, %f}, received = {%f, %f, %f})",
                          expected[0], expected[1], expected[2], values[0], values[1], values[2]);

  ts_send_success();
  return EXIT_SUCCESS;
}
