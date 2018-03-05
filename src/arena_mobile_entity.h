/**
 * @file arena_mobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena_entity.h"
#include "src/common.h"
#include "src/sensor_touch.h"
#include "src/pose.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A mobile entity in the Arena, capable of updating its own position
 * and/or velocity when asked by the simulation.
 *
 * All mobile entities must have a heading angle so that their orientation can
 * be properly drawn by the GraphicsArenaViewer.
 *
 * Since this is also a base class, many of its methods are intuitively
 * `virtual`.
 */
class ArenaMobileEntity : public ArenaEntity {
 public:
  /**
   * @brief ArenaMobileEntity's constructor.
   */

  ArenaMobileEntity()
    : ArenaEntity(),
      speed_(0),
      sensor_touch_(new SensorTouch) {
        set_mobility(true);
  }
  ArenaMobileEntity(const ArenaMobileEntity& other) = delete;
  ArenaMobileEntity& operator=(const ArenaMobileEntity& other) = delete;


  virtual double get_speed() { return speed_; }
  virtual void set_speed(double sp) { speed_ = sp; }

  virtual void HandleCollision(EntityType, ArenaEntity *, bool) {};
  /**
   * @brief Get a pointer to the ArenaMobileEntity's touch sensor.
  */
  SensorTouch * get_touch_sensor() { return sensor_touch_; }

  /**
   * @brief Get a random position in the arena
  */
  Pose SetPoseRandomly() {
    // Dividing arena into 19x14 grid. Each grid square is 50x50
    return {static_cast<double>((30 + (random() % 19) * 50)),
          static_cast<double>((30 + (random() % 14) * 50))};
  }


  /**
   * @brief Get a random radius for obstacle
  */
  double SetRadiusRandomly() {
    // OBSTACLE_MIN_RAIDUS and OBSTACLE_MAX_RADIUS are available from params.h
    double val = static_cast<double>(rand());
    val /= RAND_MAX;
    return OBSTACLE_MIN_RADIUS + val*(OBSTACLE_MAX_RADIUS - OBSTACLE_MIN_RADIUS);
  }

 private:
  double speed_;

 protected:
  // Using protected allows for direct access to sensor within entity.
  // It was awkward to have get_touch_sensor()->get_output() .
  SensorTouch * sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_MOBILE_ENTITY_H_ */
