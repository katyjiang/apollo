/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/

#pragma once

#include <string>

#include "modules/planning/scenarios/side_pass/side_pass_scenario.h"
#include "modules/planning/scenarios/stage.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace side_pass {

struct SidePassContext;

/**
 * @brief:
 * STAGE: SidePassStopOnWaitPoint
 * Notations:
 *
 *    front of car
 * A +----------+ B
 *   |          |
 *   /          /
 *   |          |
 *   |          |
 *   |          |
 *   |    X     |                                       O
 *   |<-->.<----|-------------------------------------->* (turn center)
 *   |          |   VehicleParam.min_turn_radius()
 *   |          |
 * D +----------+ C
 *    back of car
 *
 */
class SidePassStopOnWaitPoint : public Stage {
 public:
  explicit SidePassStopOnWaitPoint(const ScenarioConfig::StageConfig& config)
      : Stage(config) {}
  Stage::StageStatus Process(const common::TrajectoryPoint& planning_init_point,
                             Frame* frame);
  SidePassContext* GetContext() { return GetContextAs<SidePassContext>(); }

 private:
  bool IsFarAwayFromObstacles(
      const ReferenceLine& reference_line,
      const IndexedList<std::string, Obstacle>& indexed_obstacle_list,
      const common::PathPoint& first_path_point,
      const common::PathPoint& last_path_point);
  bool GetMoveForwardLastPathPoint(const ReferenceLine& reference_line,
                                   common::PathPoint* const last_path_point);
};

}  // namespace side_pass
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
