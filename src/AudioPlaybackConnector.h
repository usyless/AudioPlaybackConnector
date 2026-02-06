#pragma once

#include "resource.h"

using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Media::Audio;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Hosting;
namespace fs = std::filesystem;

constexpr UINT WM_NOTIFYICON = WM_APP + 1;
constexpr UINT WM_CONNECTDEVICE = WM_APP + 2;

HINSTANCE g_hInst;
HWND g_hWnd;
HWND g_hWndXaml;
Canvas g_xamlCanvas = nullptr;
Flyout g_xamlFlyout = nullptr;
MenuFlyout g_xamlMenu = nullptr;
FocusState g_menuFocusState = FocusState::Unfocused;
DevicePicker g_devicePicker = nullptr;
std::unordered_map<std::wstring, std::pair<DeviceInformation, AudioPlaybackConnection>> g_audioPlaybackConnections;
HICON g_hIconLight = nullptr;
HICON g_hIconDark = nullptr;
NOTIFYICONDATAW g_nid = {
	.cbSize = sizeof(g_nid),
	.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP,
	.uCallbackMessage = WM_NOTIFYICON,
	.uVersion = NOTIFYICON_VERSION_4
};
NOTIFYICONIDENTIFIER g_niid = {
	.cbSize = sizeof(g_niid)
};
UINT WM_TASKBAR_CREATED = 0;

struct settings_json_t;

struct settings_t {
    bool reconnect = false;
    std::vector<std::wstring> lastDevices;

    settings_t& operator=(const settings_json_t& rhs);
};

struct settings_json_t {
    bool reconnect = false;
    std::vector<std::string> lastDevices;

    settings_json_t& operator=(const settings_t& rhs) {
        reconnect = rhs.reconnect;

        lastDevices.clear();
        lastDevices.reserve(rhs.lastDevices.size());
        for (const auto& dev : rhs.lastDevices) {
            auto utf8 = usylibpp::windows::to_utf8(dev);
            if (utf8) lastDevices.emplace_back(std::move(utf8.value()));
        }
		return *this;
    }
};

inline settings_t& settings_t::operator=(const settings_json_t& rhs) {
    reconnect = rhs.reconnect;

    lastDevices.clear();
    lastDevices.reserve(rhs.lastDevices.size());
    for (const auto& dev : rhs.lastDevices) {
        auto wstr = usylibpp::windows::to_wstr(dev);
        if (wstr) lastDevices.emplace_back(std::move(wstr.value()));
    }
    return *this;
}

settings_t g_Settings{};

#include "SettingsUtil.hpp"
#include "Direct2DSvg.hpp"
