#pragma once

#include <fstream>

#include "json.hpp"

#include "../util/utilFunctions.hpp"
#include "../Include/auth.hpp"

namespace jsonn {
	auto clientDLLFile = nlohmann::json::parse(executeRequest("https://raw.githubusercontent.com/a2x/cs2-dumper/main/generated/client.dll.json"));
	auto offsetFile = nlohmann::json::parse(executeRequest("https://raw.githubusercontent.com/a2x/cs2-dumper/main/generated/offsets.json"));

}
