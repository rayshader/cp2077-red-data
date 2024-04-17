#ifndef REDDATA_REDDATA_HPP
#define REDDATA_REDDATA_HPP

#include <RedLib.hpp>

#include "src/Json.hpp"

namespace RedData {

inline bool IsDetected() {
  return Red::Detail::GetGlobalFunction("RedData.Json.ParseJson") != nullptr;
}

}  // namespace RedData

#endif  //REDDATA_REDDATA_HPP
