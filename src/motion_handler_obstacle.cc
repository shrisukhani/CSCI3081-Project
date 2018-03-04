/**
 * @file motion_handler_obstacle.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_obstacle.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// @TODO add clamped

void MotionHandlerObstacle::TurnLeft(){}

void MotionHandlerObstacle::TurnRight(){}

void MotionHandlerObstacle::Stop(){
  set_velocity(
    0.0,
    0.0
  );
}


void MotionHandlerObstacle::IncreaseSpeed() {}

void MotionHandlerObstacle::DecreaseSpeed() {}
//@TODO: Finish implementation
void MotionHandlerObstacle::UpdateVelocity() {
  printf(entity_->get_touch_sensor()->get_output() ? "true" : "false");
  if (entity_->get_touch_sensor()->get_output()) {
    entity_->RelativeChangeHeading(+180);
    printf("Check 1");
  }
  if (entity_->get_collision_timer() > 0) {
    printf("Check 2");
    entity_->set_collision_timer(entity_->get_collision_timer() - 1);
    entity_->RelativeChangeHeading(+20);
    if (entity_->get_collision_timer() == 0) {
      entity_->RelativeChangeHeading(+180);
    }
    printf("check 3");
  }
}

double MotionHandlerObstacle::clamp_vel(double vel) {
  return vel;
}

NAMESPACE_END(csci3081);
