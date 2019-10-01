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
#ifndef JADX_UTILS_H_
#define JADX_UTILS_H_
#include <string>

bool endswith(const std::string& str, const std::string& suffix);
bool startswith(const std::string& str, const std::string& prefix);

std::string normalize_class_name(const std::string& name);

// La;
// Lsome/pkg/Class;
// some.pkg.Class
//
std::string pretty_class_name(const std::string& name, bool with_ext = false);


/**************** MACRO ****************/

/* This macro is used to generate a getter of a boolean */
#define CREATE_GETTER_BOOLEAN(method_name)                                                              \
  bool method_name(void) {                                                                              \
    static auto&& m = this->clazz().template GetMethod<jboolean()>(this->env(), #method_name);          \
    return this->obj_.Call(this->env(), m);                                                             \
  }

/* This macro is used to generate a getter of a boolean */
#define CREATE_GETTER_OBJECT(object_type, method_name)                                                              \
  object_type method_name(void) {                                                                                   \
    static auto&& method = this->clazz().template GetMethod<Object<object_type::Tag>()>(this->env(), #method_name); \
    return object_type( this->env(),  this->obj_.Call(this->env(), method));                                        \
  }

#define CREATE_GETTER_LIST(object_type, method_name)                                                              \
  std::vector<object_type> method_name(void) {                                                                    \
    using List_t = java::util::List<object_type>;                                                                 \
    static auto&& method = this->clazz().template GetMethod<Object<List_t::Tag>()>(this->env(), #method_name);    \
    auto&& results = this->obj_.Call(this->env(), method);                                                        \
                                                                                                                  \
    List_t jlist{this->env(), results};                                                                           \
                                                                                                                  \
    std::vector<object_type> v;                                                                                   \
    v.reserve(jlist.size());                                                                                      \
                                                                                                                  \
    for (size_t i = 0; i < jlist.size(); ++i) {                                                                   \
      v.emplace_back(jlist.at(i));                                                                                \
    }                                                                                                             \
                                                                                                                  \
    return v;                                                                                                     \
  }

#endif
