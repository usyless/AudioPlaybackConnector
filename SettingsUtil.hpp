#pragma once

constexpr auto CONFIG_NAME = L"AudioPlaybackConnector.json";

void DefaultSettings() {
	g_reconnect = false;
	g_lastDevices.clear();
}

void LoadSettings() {
	try {
		DefaultSettings();

		std::wstring utf16 = usylibpp::windows::to_wstr_or_default(
			usylibpp::files::read_as_bytes_or_default(sylibpp::windows::current_executable_path_or_default().remove_filename() / CONFIG_NAME)
		);
		auto jsonObj = JsonObject::Parse(utf16);
		g_reconnect = jsonObj.Lookup(L"reconnect").GetBoolean();

		auto lastDevices = jsonObj.Lookup(L"lastDevices").GetArray();
		g_lastDevices.reserve(lastDevices.Size());
		for (const auto& i : lastDevices) {
			if (i.ValueType() == JsonValueType::String)
				g_lastDevices.push_back(std::wstring(i.GetString()));
		}
	}
	CATCH_LOG();
}

void SaveSettings() {
	try {
		JsonObject jsonObj;
		jsonObj.Insert(L"reconnect", JsonValue::CreateBooleanValue(g_reconnect));

		JsonArray lastDevices;
		for (const auto& i : g_audioPlaybackConnections) {
			lastDevices.Append(JsonValue::CreateStringValue(i.first));
		}
		jsonObj.Insert(L"lastDevices", lastDevices);

		wil::unique_hfile hFile(CreateFileW((usylibpp::windows::current_executable_path_or_default().remove_filename() / CONFIG_NAME).c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));
		THROW_LAST_ERROR_IF(!hFile);

		std::string utf8 = usylibpp::windows::to_utf8_or_default(jsonObj.Stringify());
		DWORD written = 0;
		THROW_IF_WIN32_BOOL_FALSE(WriteFile(hFile.get(), utf8.data(), static_cast<DWORD>(utf8.size()), &written, nullptr));
		THROW_HR_IF(E_FAIL, written != utf8.size());
	}
	CATCH_LOG();
}
