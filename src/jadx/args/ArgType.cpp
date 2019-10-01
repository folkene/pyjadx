/* Copyright 2018 R. Thomas
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
#include <jadx/args/ArgType.hpp>

namespace jni::jadx::args {

ArgType::ArgType(JNIEnv& env, const Object_t& obj) {
  this->env_ = &env;
  this->obj_ = NewLocal(env, obj);
}

ArgType::ArgType(JNIEnv& env, const Object<>& obj) {

  this->env_ = &env;
  auto&& casted = Cast<ArgTypeTag>(this->env(), this->clazz(), obj);
  this->obj_ = NewLocal(env, casted);
}

std::string ArgType::to_string(void) const {
  static auto&& toString = this->clazz().template GetMethod<String()>(this->env(), "toString");
  return Make<std::string>(this->env(), this->obj_.Call(this->env(), toString));
}

}
