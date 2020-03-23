// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/reader/spirv/namer.h"

#include <algorithm>
#include <sstream>

namespace tint {
namespace reader {
namespace spirv {

Namer::Namer(const FailStream& fail_stream) : fail_stream_(fail_stream) {}

Namer::~Namer() = default;

std::string Namer::Sanitize(const std::string& suggested_name) {
  if (suggested_name.empty()) {
    return "empty";
  }
  // Otherwise, replace invalid characters by '_'.
  std::string result;
  std::string invalid_as_first_char = "_0123456789";
  std::string valid =
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "_0123456789";
  // If the first character is invalid for starting a WGSL identifier, then
  // prefix the result with "x".
  if ((std::string::npos != invalid_as_first_char.find(suggested_name[0])) ||
      (std::string::npos == valid.find(suggested_name[0]))) {
    result = "x";
  }
  std::transform(suggested_name.begin(), suggested_name.end(),
                 std::back_inserter(result), [&valid](const char c) {
                   return (std::string::npos == valid.find(c)) ? '_' : c;
                 });
  return result;
}

std::string Namer::GetMemberName(uint32_t struct_id,
                                 uint32_t member_index) const {
  std::string result;
  auto where = struct_member_names_.find(struct_id);
  if (where != struct_member_names_.end()) {
    auto& member_names = where->second;
    if (member_index < member_names.size()) {
      result = member_names[member_index];
    }
  }
  return result;
}

std::string Namer::FindUnusedDerivedName(const std::string& base_name) const {
  // Ensure uniqueness among names.
  std::string derived_name;
  for (int i = 0;; i++) {
    std::stringstream new_name_stream;
    new_name_stream << base_name;
    if (i > 0) {
      new_name_stream << "_" << i;
    }
    derived_name = new_name_stream.str();
    if (name_to_id_.count(derived_name) == 0) {
      break;
    }
  }
  return derived_name;
}

bool Namer::SaveName(uint32_t id, const std::string& name) {
  if (HasName(id)) {
    return Fail() << "internal error: ID " << id
                  << " already has registered name: " << id_to_name_[id];
  }
  id_to_name_[id] = name;
  name_to_id_[name] = id;
  return true;
}

bool Namer::SuggestSanitizedName(uint32_t id,
                                 const std::string& suggested_name) {
  if (HasName(id)) {
    return false;
  }

  return SaveName(id, FindUnusedDerivedName(Sanitize(suggested_name)));
}

bool Namer::SuggestSanitizedMemberName(uint32_t struct_id,
                                       uint32_t member_index,
                                       const std::string& suggested_name) {
  // Creates an empty vector the first time we visit this struct.
  auto& name_vector = struct_member_names_[struct_id];
  // Resizing will set new entries to the empty string.
  name_vector.resize(std::max(name_vector.size(), size_t(member_index + 1)));
  auto& entry = name_vector[member_index];
  if (entry.empty()) {
    entry = Sanitize(suggested_name);
    return true;
  }
  return false;
}

}  // namespace spirv
}  // namespace reader
}  // namespace tint
