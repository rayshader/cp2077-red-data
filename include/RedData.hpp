#ifndef REDDATA_REDDATA_HPP
#define REDDATA_REDDATA_HPP

#include <RedLib.hpp>

#include "Json/Json.hpp"

namespace RedData {

inline bool IsDetected() {
  return Red::GetGlobalFunction("RedData.Json.ParseJson") != nullptr;
}

}  // namespace RedData

#endif  //REDDATA_REDDATA_HPP
