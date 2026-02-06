#pragma once

constexpr auto CONFIG_NAME = L"AudioPlaybackConnector.json";
inline const auto config_file = usylibpp::windows::current_executable_path_or_default().get().parent_path() / CONFIG_NAME;

void DefaultSettings() {
	g_Settings = settings_t{};
}

static inline constexpr glz::opts glz_opts{
    .null_terminated = true,
    .minified = false
};

bool LoadSettings() {
	DefaultSettings();

	settings_json_t data;
	auto j = usylibpp::files::read_as_bytes(config_file);
	if (!j) return false;

	auto err = glz::read<glz_opts>(data, *j);
	if (err) {
		std::error_code ec;
		std::filesystem::remove(config_file, ec);
		return false;
	}

	g_Settings = data;
	return true;
}

bool SaveSettings() {
	static std::string json;
	settings_json_t data{g_Settings};

	auto err = glz::write_json(data, json);
	if (err) return false;

	return usylibpp::files::write(config_file, json);
}
