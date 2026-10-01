// SPDX-License-Identifier: Apache-2.0
// Copyright 2025 WimbleRobotics
// https://github.com/wimblerobotics/Sigyn

#pragma once

#include "roboclaw_cmd.h"

// Command 58 - Set Logic Battery Voltage Limits (SETLOGICVOLTAGES)
// Sets both min and max logic battery voltage limits.
// Voltage values are in 0.1V increments (e.g., 30 = 3.0V, 140 = 14.0V).
// On models like the 2x7a where logic power is internally regulated,
// set a wide range (e.g., 0 to 140) to prevent spurious voltage errors.
class CmdSetLogicBatteryVoltages : public Cmd {
 public:
  CmdSetLogicBatteryVoltages(RoboClaw &roboclaw, uint16_t min_voltage_tenths,
                             uint16_t max_voltage_tenths)
      : Cmd(roboclaw, "SetLogicBatteryVoltages", RoboClaw::kNone),
        min_voltage_(min_voltage_tenths),
        max_voltage_(max_voltage_tenths) {}

  void send() override {
    roboclaw_.appendToWriteLog(
        "SetLogicBatteryVoltages: min: %u (%.1fV), max: %u (%.1fV), WROTE: ", min_voltage_,
        min_voltage_ / 10.0, max_voltage_, max_voltage_ / 10.0);
    roboclaw_.writeN2(6, roboclaw_.portAddress_, RoboClaw::SETLOGICVOLTAGES,
                      SetWORDval(min_voltage_), SetWORDval(max_voltage_));
  }

 private:
  uint16_t min_voltage_;
  uint16_t max_voltage_;
};
