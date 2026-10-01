// SPDX-License-Identifier: Apache-2.0
// Copyright 2025 WimbleRobotics
// https://github.com/wimblerobotics/Sigyn

#pragma once

#include "roboclaw_cmd.h"

class CmdReadMainBatteryVoltage : public Cmd {
 public:
  CmdReadMainBatteryVoltage(RoboClaw &roboclaw, float &voltage, bool &read_successful)
      : Cmd(roboclaw, "ReadLMainBatteryVoltage", RoboClaw::kNone),
        voltage_(voltage),
        read_successful_(read_successful) {}
  void send() override {
    read_successful_ = false;
    try {
      roboclaw_.appendToWriteLog("CmdReadMainBatteryVoltage: WROTE: ");
      float result = ((float)roboclaw_.get2ByteCommandResult2(RoboClaw::GETMBATT)) / 10.0;
      voltage_ = result;
      read_successful_ = true;
      roboclaw_.appendToReadLog(", RESULT: %f", result);
      return;
    } catch (...) {
      RCUTILS_LOG_ERROR("[RoboClaw::CmdReadMainBatteryVoltage] Uncaught exception !!!");
    }
  }

 private:
  float &voltage_;
  bool &read_successful_;
};
