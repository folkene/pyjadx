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
#ifndef JADX_INFO_ACCESS_INFO_H_
#define JADX_INFO_ACCESS_INFO_H_

#include <jni/jni.hpp>

#include <jadx/api/JavaNode.hpp>

#include <string>

#include "utils.hpp" /* Method generator */

using namespace jni::jadx::api;

namespace jni::jadx::info {

struct AccessInfoTag { static constexpr auto Name() { return "jadx/core/dex/info/AccessInfo"; } };
class AccessInfo : public JavaNode<AccessInfo, AccessInfoTag, Object<AccessInfoTag>, Class<AccessInfoTag>> {
  public:

  using Object_t = Object<AccessInfoTag>;
  using Class_t  = Class<AccessInfoTag>;

  AccessInfo(JNIEnv& env, const Object_t& obj);
  AccessInfo(JNIEnv& env, const Object<>& obj);

  std::string to_string(void) const;

  CREATE_GETTER_BOOLEAN(isNative);
  CREATE_GETTER_BOOLEAN(isPublic);
  CREATE_GETTER_BOOLEAN(isProtected);
  CREATE_GETTER_BOOLEAN(isPrivate);
  CREATE_GETTER_BOOLEAN(isPackagePrivate);
  CREATE_GETTER_BOOLEAN(isAbstract);
  CREATE_GETTER_BOOLEAN(isInterface);
  CREATE_GETTER_BOOLEAN(isAnnotation);
  CREATE_GETTER_BOOLEAN(isStatic);
  CREATE_GETTER_BOOLEAN(isFinal);
  CREATE_GETTER_BOOLEAN(isConstructor);
  CREATE_GETTER_BOOLEAN(isEnum);
  CREATE_GETTER_BOOLEAN(isSynthetic);
  CREATE_GETTER_BOOLEAN(isBridge);
  CREATE_GETTER_BOOLEAN(isVarArgs);
  CREATE_GETTER_BOOLEAN(isSynchronized);
  CREATE_GETTER_BOOLEAN(isTransient);
  CREATE_GETTER_BOOLEAN(isVolatile);
};

}
#endif /* JADX_INFO_ACCESS_INFO_H_ */
