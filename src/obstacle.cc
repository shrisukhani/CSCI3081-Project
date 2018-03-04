/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/obstacle.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Obstacle::Obstacle() : motion_handler_(this), motion_behavior_(this) {
  motion_handler_.set_velocity(2,2);
  set_color(OBSTACLE_COLOR);
  set_pose(OBSTACLE_POSITION);
  set_radius(OBSTACLE_RADIUS);
  set_type(kObstacle);
}

Pose Obstacle::SetPoseRandomly() {
  // Dividing arena into 19x14 grid. Each grid square is 50x50
  return {static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))};
}

void Obstacle::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
}

void Obstacle::Reset() {
  double rad = static_cast<double>(rand());
  rad /= RAND_MAX;
  rad  = OBSTACLE_MIN_RADIUS + rad*(OBSTACLE_MAX_RADIUS - OBSTACLE_MIN_RADIUS);
  set_pose(SetPoseRandomly());
  set_radius(rad);
  set_color(OBSTACLE_COLOR);
  sensor_touch_->Reset();
  motion_handler_.set_velocity(2, 2);
  // motion_behavior_(this);
}

void Obstacle::HandleCollision(EntityType object_type, ArenaEntity * object) {
  set_collision_timer(20);
  sensor_touch_->HandleCollision(object_type, object);
  motion_handler_.UpdateVelocity();
  printf("\n\n\n\n HandleCollision Baby\n\n\n\n\n");
  switch (object_type) {
    case kRightWall:
    case kLeftWall:
    case kTopWall:
    case kBottomWall:
      motion_handler_.set_velocity(0.0);
      motion_handler_.UpdateVelocity();
      break;
    case kRobot:
      break;
    case kBase:
      break;
    default: break;
  }
}


NAMESPACE_END(csci3081);
