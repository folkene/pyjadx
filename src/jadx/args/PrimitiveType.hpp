/* Copyright 2019 El-Houari Soussi
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef JADX_ARGS_PRIMITIVE_TYPE_H_
#define JADX_ARGS_PRIMITIVE_TYPE_H_

#include <jni/jni.hpp>
#include <jadx/api/JavaNode.hpp>
#include <string>

#include "utils.hpp" /* Method generator */

using namespace jni::jadx::api;

namespace jni::jadx::args {

struct PrimitiveTypeTag { static constexpr auto Name() { return "jadx/core/dex/instructions/args/PrimitiveType"; } };
class PrimitiveType : public JavaNode<PrimitiveType, PrimitiveTypeTag, Object<PrimitiveTypeTag>, Class<PrimitiveTypeTag>> {
  public:

  using Object_t = Object<PrimitiveTypeTag>;
  using Class_t  = Class<PrimitiveTypeTag>;

  PrimitiveType(JNIEnv& env, const Object_t& obj);
  PrimitiveType(JNIEnv& env, const Object<>& obj);

  std::string to_string(void) const;
  std::string getLongName(void);

};

}
#endif /* JADX_ARGS_PRIMITIVE_TYPE_H_ */
