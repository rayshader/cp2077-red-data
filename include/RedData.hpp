#ifndef REDDATA_REDDATA_HPP
#define REDDATA_REDDATA_HPP

#include <RedLib.hpp>

#include "Json/Json.hpp"

#define HAS_REDDATA

namespace RedData {

inline bool IsDetected() {
  return Red::Detail::GetGlobalFunction("RedData.Json.ParseJson") != nullptr;
}

}  // namespace RedData

#endif  //REDDATA_REDDATA_HPP
