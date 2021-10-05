//* Copyright 2021 The Dawn Authors
//*
//* Licensed under the Apache License, Version 2.0 (the "License");
//* you may not use this file except in compliance with the License.
//* You may obtain a copy of the License at
//*
//*     http://www.apache.org/licenses/LICENSE-2.0
//*
//* Unless required by applicable law or agreed to in writing, software
//* distributed under the License is distributed on an "AS IS" BASIS,
//* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//* See the License for the specific language governing permissions and
//* limitations under the License.

#ifndef WEBGPU_ABSL_FORMAT_H_
#define WEBGPU_ABSL_FORMAT_H_

#include "dawn_native/dawn_platform.h"

#include "absl/strings/str_format.h"

namespace dawn_native {

    //
    // Structs (Manually written)
    //

    struct Color;
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const Color* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    struct Extent3D;
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const Extent3D* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    struct Origin3D;
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const Origin3D* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    //
    // Objects
    //

    class DeviceBase;
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const DeviceBase* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    class ApiObjectBase;
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ApiObjectBase* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    // Special case for TextureViews, since frequently the texture will be the
    // thing that's labeled.
    class TextureViewBase;
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureViewBase* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    //
    // Descriptors
    //

    // Only includes structures that have a 'label' member.
    {% for type in by_category["structure"] %}
        {% for member in type.members %}
            {% if member.name.canonical_case() == "label" %}
                absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
                AbslFormatConvert(const {{as_cppType(type.name)}}* value,
                                  const absl::FormatConversionSpec& spec,
                                  absl::FormatSink* s);
            {% endif %}
        {% endfor %}
    {% endfor %}
}

namespace wgpu {

    //
    // Enums
    //

    {% for type in by_category["enum"] %}
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert({{as_cppType(type.name)}} value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    {% endfor %}

    //
    // Bitmasks
    //

    {% for type in by_category["bitmask"] %}
        absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert({{as_cppType(type.name)}} value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    {% endfor %}

}  // namespace dawn_native

#endif // WEBGPU_ABSL_FORMAT_H_
