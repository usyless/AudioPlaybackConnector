#pragma once

#include "AudioPlaybackConnector.h"

inline constexpr auto CONFIG_NAME = L"AudioPlaybackConnector.json";
inline const auto config_file = usylibpp::windows::current_executable_path_or_default().get().parent_path() / CONFIG_NAME;

inline void DefaultSettings() {
	g_Settings = settings_t{};
}

static inline constexpr glz::opts glz_opts{
    .null_terminated = true,
    .minified = false
};

inline bool LoadSettings() {
	DefaultSettings();

	settings_json_t data;
	auto j = usylibpp::files::read_as_bytes(config_file);
	if (!j) return false;

	auto err = glz::read<glz_opts>(data, j.value());
	if (err) {
		std::error_code ec;
		std::filesystem::remove(config_file, ec);
		return false;
	}

	g_Settings = data;
	return true;
}

inline bool SaveSettings() {
	settings_json_t data;
	data = g_Settings;

	std::string json;

	auto err = glz::write_json(data, json);
	if (err) return false;

	return usylibpp::files::write(config_file, json);
}
