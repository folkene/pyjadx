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
#include "pyjadx.hpp"
#include "version.h"
#include "utils.hpp"
#include <jadx/jadx.hpp>
#include "core.hpp"
#include <sstream>

py::module jadx_module("pyjadx", "JADX Python API");

using namespace jni::jadx::args;
using namespace jni::jadx::info;
using namespace jni::jadx::api;


PYBIND11_MODULE(pyjadx, jadx_module) {

  jadx_module.attr("__version__")          = py::str(PYJADX_VERSION);
  jadx_module.attr("__pyjadx_tag__")       = py::str(PYJADX_TAG);
  jadx_module.attr("__pyjadx_is_tagged__") = py::bool_(PYJADX_TAGGED);

  jadx_module.def("normalize_class_name", &normalize_class_name,
      "",
      "name"_a);

  jadx_module.def("pretty_class_name", &pretty_class_name,
      "",
      "name"_a, "with_ext"_a = false);

  py::class_<jni::Jadx>(jadx_module, "Jadx", "")
    .def(py::init<>())
    .def("load",
        &jni::Jadx::load,
        "Load an APK or Dex file to decompile",
        "apk_path"_a, "escape_unicode"_a = true, "show_inconsistent_code"_a = true,
        "deobfuscation_on"_a = false, "deobfuscation_min_length"_a = 3, "deobfuscation_max_length"_a = 64
        );


  py::class_<JadxDecompiler>(jadx_module, "JadxDecompiler", "")
    .def("load",
        &JadxDecompiler::load,
        "Load an APK or Dex file to decompile")

    .def_property_readonly("classes",
        &JadxDecompiler::classes,
        "List of :class:`~pyjadx.JavaClass`")

    .def_property_readonly("packages",
        &JadxDecompiler::packages,
        "List of :class:`~pyjadx.JavaPackage`")

    .def("has_class",
        &JadxDecompiler::has_class,
        "Check if the class given in first argument is present",
        "class_name"_a)

    .def("has_package",
        &JadxDecompiler::has_package,
        "Check if the package given in first argument is present",
        "package_name"_a)

    .def("get_class",
        &JadxDecompiler::get_class,
        "Return the :class:`~pyjadx.JavaClass` object from "
        "the name given in first parameter",
        "class_name"_a)

    .def("get_package",
        &JadxDecompiler::get_package,
        "Return the :class:`~pyjadx.JavaPackage` object from "
        "the name given in first parameter",
        "pkg_name"_a);

  py::class_<JavaMethod>(jadx_module, "JavaMethod", "")
    .def_property_readonly("name",
        &JavaMethod::name,
        "Method name as a ``str``")

    .def_property_readonly("fullname",
        &JavaMethod::fullname,
        "Method fullname as a ``str``")

    .def_property_readonly("decompiled_line",
        &JavaMethod::decompiled_line,
        "Line number in decompiled code associated with this method")

    .def_property_readonly("access_flags",
        &JavaMethod::getAccessFlags,
        "accessor to getAccessFlags")

    .def_property_readonly("return_type",
        &JavaMethod::getReturnType,
        "accessor to getReturnType")

    .def_property_readonly("arguments",
        &JavaMethod::getArguments,
        "accessor to getArguments")

    .def("__str__", &JavaMethod::to_string)
    .def("__hash__", &JavaMethod::hash_code)
    .def("__eq__", &JavaMethod::operator==)
    .def("getAccessFlags", &JavaMethod::getAccessFlags);

  py::class_<AccessInfo>(jadx_module, "AccessInfo", "")
    .def("__str__", &AccessInfo::to_string)
    .def_property_readonly("is_native", &AccessInfo::isNative, "Indicate if is native")
    .def_property_readonly("is_public", &AccessInfo::isPublic, "Indicate if is public")
    .def_property_readonly("is_protected", &AccessInfo::isProtected, "Indicate if is protected")
    .def_property_readonly("is_private", &AccessInfo::isPrivate, "Indicate if is private")
    .def_property_readonly("is_private_package", &AccessInfo::isPackagePrivate, "Indicate if is private to the package")
    .def_property_readonly("is_abstract", &AccessInfo::isAbstract, "Indicate if is abstract")
    .def_property_readonly("is_interface", &AccessInfo::isInterface, "Indicate if is an Interface")
    .def_property_readonly("is_annotation", &AccessInfo::isAnnotation, "Indicate if is an annotation")
    .def_property_readonly("is_static", &AccessInfo::isStatic, "Indicate if is static")
    .def_property_readonly("is_final", &AccessInfo::isFinal, "Indicate if is final")
    .def_property_readonly("is_constructor", &AccessInfo::isConstructor, "Indicate if is a constructor")
    .def_property_readonly("is_enum", &AccessInfo::isEnum, "Indicate if is enum")
    .def_property_readonly("is_synthetic", &AccessInfo::isSynthetic, "Indicate if is synthetic")
    .def_property_readonly("is_bridge", &AccessInfo::isBridge, "Indicate if is a bridge")
    .def_property_readonly("is_var_args", &AccessInfo::isVarArgs, "Indicate if is a varargs")
    .def_property_readonly("is_synchronized", &AccessInfo::isSynchronized, "Indicate if is synchronized")
    .def_property_readonly("is_transcient", &AccessInfo::isTransient, "Indicate if is transcient")
    .def_property_readonly("is_volatile", &AccessInfo::isVolatile, "Indicate if is volatile");


  py::class_<ArgType>(jadx_module, "ArgType", "")
    .def("__str__", &ArgType::to_string)
    .def_property_readonly("is_primitive", &ArgType::isPrimitive, "Indicate if is primitive type")
    .def_property_readonly("is_array", &ArgType::isArray, "Indicate if is array")
    .def_property_readonly("array_root_element", &ArgType::getArrayRootElement, "getter of the root element (if array)")
    .def_property_readonly("primitive_type", &ArgType::getPrimitiveType, "return the primitive type instance corresponding to this argument");

  py::class_<PrimitiveType>(jadx_module, "PrimitiveType", "")
    .def("__str__", &PrimitiveType::to_string)
    .def_property_readonly("longname", &PrimitiveType::getLongName, "the long name of the primitive type");

  py::class_<JavaClass>(jadx_module, "JavaClass", "")
    .def_property_readonly("code_highlight",
        [] (JavaClass& cls) -> py::object {
          try {
            auto&& pygments              = py::module::import("pygments");
            auto&& get_lexer_by_name     = py::module::import("pygments.lexers").attr("get_lexer_by_name");
            auto&& get_formatter_by_name = py::module::import("pygments.formatters").attr("get_formatter_by_name");
            auto&& highlight             = pygments.attr("highlight");

            auto&& lexer     = get_lexer_by_name("java");
            auto&& formatter = get_formatter_by_name("terminal256", "style"_a="monokai", "linenos"_a=false);
            return highlight(cls.getCode(), lexer, formatter);
          } catch (const std::exception& e) {
            py::print(e.what());
          }
          return py::str(cls.getCode());
        },
        "Highlight decompiled code (Require Pygments)")

    .def("save",
        [] (JavaClass& cls, py::object output) {
          std::string str_output;

          auto&& pathlib = py::module::import("pathlib");
          auto&& Path = pathlib.attr("Path");
          if (py::isinstance<py::str>(output)) {
            str_output = output.cast<std::string>();
          }
          else if (py::isinstance(output, Path)) {
            str_output = output.attr("as_posix")().cast<std::string>();

          } else {
            std::string error_str = py::repr(output).cast<std::string>();
            error_str = error_str + " is not supported!";
            throw py::type_error(error_str.c_str());
          }

          return cls.save(str_output);
        },
        "Save decompiled code in the file given in first parameter\n\n"
        "Return False is an error occurred",
        "output_path"_a)

    .def_property_readonly("methods",
        &JavaClass::methods,
        "List of :class:`~pyjadx.JavaMethod`")

    .def_property_readonly("name",
        &JavaClass::name,
        "Class name as a ``str``")

    .def_property_readonly("fullname",
        &JavaClass::fullname,
        "Class fullname as a ``str``")

    .def_property_readonly("decompiled_line",
        &JavaClass::decompiled_line,
        "Line number in decompiled code associated with this class");


  py::class_<JavaPackage>(jadx_module, "JavaPackage", "")
    .def_property_readonly("classes",
        &JavaPackage::classes,
        "List of :class:`~pyjadx.JavaClass`")

    .def_property_readonly("name",
        &JavaPackage::name,
        "Package name")

    .def_property_readonly("fullname",
        &JavaPackage::fullname,
        "Package fullname")

    .def_property_readonly("decompiled_line",
        &JavaPackage::decompiled_line,
        "Line number in decompiled code associated with this package")

    .def("save",
        [] (JavaPackage& cls, py::object output) {
          std::string str_output;

          auto&& pathlib = py::module::import("pathlib");
          auto&& Path    = pathlib.attr("Path");
          if (py::isinstance<py::str>(output)) {
            str_output = output.cast<std::string>();
          }
          else if (py::isinstance(output, Path)) {
            str_output = output.attr("resolve")().attr("absolute")().attr("as_posix")().cast<std::string>();
          } else {
            std::string error_str = py::repr(output).cast<std::string>();
            error_str = error_str + " is not supported!";
            throw py::type_error(error_str.c_str());
          }

          return cls.save(str_output);
        },
        "Decompile the package in the directory given in first parameter"
        "output_path"_a);
}
