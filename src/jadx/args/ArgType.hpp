/* Copyright 2019 El-Houari SOUSSI
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
#ifndef JADX_ARGS_ARG_TYPE_H_
#define JADX_ARGS_ARG_TYPE_H_

#include <jni/jni.hpp>
#include <jadx/api/JavaNode.hpp>
#include <jadx/args/PrimitiveType.hpp>
#include <string>

#include "utils.hpp" /* Method generator */

namespace jni::jadx::args {

struct ArgTypeTag { static constexpr auto Name() { return "jadx/core/dex/instructions/args/ArgType"; } };
class ArgType : public jni::jadx::api::JavaNode<ArgType, ArgTypeTag, Object<ArgTypeTag>, Class<ArgTypeTag>> {
  public:

  using Object_t = Object<ArgTypeTag>;
  using Class_t  = Class<ArgTypeTag>;

  ArgType(JNIEnv& env, const Object_t& obj);
  ArgType(JNIEnv& env, const Object<>& obj);

  std::string to_string(void) const;

  CREATE_GETTER_BOOLEAN(isPrimitive)
  CREATE_GETTER_BOOLEAN(isArray)

  
  CREATE_GETTER_OBJECT(ArgType, getArrayRootElement)
  CREATE_GETTER_OBJECT(PrimitiveType, getPrimitiveType)

};

}
#endif /* JADX_ARGS_ARG_TYPE_H_ */
