/*
 * Author: Kofi and Isabella
 * Organisation: HYPED
 * Date: 15/04/18
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

#ifndef BEAGLEBONE_BLACK_COMMUNICATIONS_RECEIVER_HPP_
#define BEAGLEBONE_BLACK_COMMUNICATIONS_RECEIVER_HPP_

#include "communications/communications.hpp"
#include "data/data.hpp"
#include "utils/concurrent/thread.hpp"
#include "utils/logger.hpp"
#include "utils/system.hpp"

namespace hyped {

using utils::Logger;
using utils::concurrent::Thread;

namespace communications {

class ReceiverThread : public Thread {
public:
  explicit ReceiverThread(Logger &log, Communications *base_communicator);
  void run() override;

private:
  utils::System &sys_;
  Logger &log_;
  data::Data &data_;
  Communications *base_communicator_;
};

} // namespace communications
} // namespace hyped

#endif // BEAGLEBONE_BLACK_COMMUNICATIONS_RECEIVER_HPP_
