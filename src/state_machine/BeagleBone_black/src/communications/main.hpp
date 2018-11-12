/*
 * Authors: Kofi and Isabella
 * Organisation: HYPED
 * Date: 1. April 2018
 * Description:
 *
 *    Copyright 2018 HYPED
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef BEAGLEBONE_BLACK_COMMUNICATIONS_MAIN_HPP_
#define BEAGLEBONE_BLACK_COMMUNICATIONS_MAIN_HPP_

#include "communications/communications.hpp"
#include "communications/receiver.hpp"
#include "data/data.hpp"
#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"

namespace hyped {

using data::Imu;
using data::ModuleStatus;
using data::Sensors;
#ifdef PROXI
using data::Proximity;
#endif
using data::Battery;
using data::State;
using utils::Logger;
using utils::concurrent::Thread;

namespace communications {

class Main : public Thread {
 public:
  typedef std::array<Imu, Sensors::kNumImus> ImuArray;
#ifdef PROXI
  typedef std::array<Proximity, Sensors::kNumProximities> ProximityArray;
#endif
  explicit Main(uint8_t id, Logger& log);
  void run() override;
  int getModuleStatusCode(ModuleStatus mod_status);
  int sendState(State state);                             // CMD01
  int sendBmsStatus(ModuleStatus bms_status);             // CMD02
  int sendNavStatus(ModuleStatus nav_status);             // CMD03
  int sendSenStatus(ModuleStatus sen_status);             // CMD04
  int sendMtrStatus(ModuleStatus mtr_status);             // CMD05
  int sendDistance(NavigationType distance);              // CMD06
  int sendVelocity(NavigationType speed);                 // CMD07
  int sendAcceleration(NavigationType accel);             // CMD08
  int sendHpBattery(Battery hpb);                         // CMD09-14
  int sendHpBattery_1(Battery hpb_1);                     // CMD15-20
  int sendLpBattery(Battery lpb);                         // CMD21-23
  int sendLpBattery_1(Battery lpb_1);                     // CMD24-26
  int sendRpmFl(float rpm_fl);                            // CMD27
  int sendRpmFr(float rpm_fr);                            // CMD28
  int sendRpmBl(float rpm_bl);                            // CMD29
  int sendRpmBr(float rpm_br);                            // CMD30
  int sendImu(ImuArray imus);                             // CMD31
  int sendEmBrakes(bool front_brakes, bool rear_brakes);  // CMD32
#ifdef PROXI
  int sendProxiFront(ProximityArray proxies_front);  // CMD33
  int sendProxiRear(ProximityArray proxies_rear);    // CMD34
#endif

 private:
  int state_code_;
  Communications* base_communicator_;
  utils::System& sys_;
  Logger& log_;
  data::Data& data_;
  data::StateMachine stm_;
  data::Motors mtr_;
  data::Sensors sen_;
  data::Batteries bat_;
  data::Navigation nav_;
  data::Communications cmn_;
  data::EmergencyBrakes emb_;
};

}  // namespace communications
}  // namespace hyped

#endif  // BEAGLEBONE_BLACK_COMMUNICATIONS_MAIN_HPP_
