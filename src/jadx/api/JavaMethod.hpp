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
#ifndef JADX_API_JAVA_METHOD_H_
#define JADX_API_JAVA_METHOD_H_

#include <jni/jni.hpp>

#include <jadx/api/JavaNode.hpp>
//#include <jadx/api/JavaClass.hpp>

#include <string>


namespace jni::jadx::api {

struct JavaMethodTag { static constexpr auto Name() { return "jadx/api/JavaMethod"; } };
class JavaMethod : public JavaNode<JavaMethod, JavaMethodTag, Object<JavaMethodTag>, Class<JavaMethodTag>> {
  public:

  using Object_t = Object<JavaMethodTag>;
  using Class_t  = Class<JavaMethodTag>;

  JavaMethod(JNIEnv& env, const Object_t& obj);
  JavaMethod(JNIEnv& env, const Object<>& obj);

  bool is_constructor(void) const;
  bool is_class_init(void) const;

  std::string to_string(void) const;

  size_t hash_code(void) const;

  bool operator==(const JavaMethod& other) const;
  bool operator!=(const JavaMethod& other) const;

  friend std::ostream& operator<<(std::ostream& os, const JavaMethod& meth);

};

}
#endif
