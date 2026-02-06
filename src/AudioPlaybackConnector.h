#pragma once

#include "resource.h"

using namespace winrt::Windows::Devices::Enumeration;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Media::Audio;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Hosting;

inline constexpr UINT WM_NOTIFYICON = WM_APP + 1;
inline constexpr UINT WM_CONNECTDEVICE = WM_APP + 2;

inline HINSTANCE g_hInst;
inline HWND g_hWnd;
inline HWND g_hWndXaml;
inline Canvas g_xamlCanvas = nullptr;
inline Flyout g_xamlFlyout = nullptr;
inline MenuFlyout g_xamlMenu = nullptr;
inline FocusState g_menuFocusState = FocusState::Unfocused;
inline DevicePicker g_devicePicker = nullptr;
inline std::unordered_map<std::wstring, std::pair<DeviceInformation, AudioPlaybackConnection>> g_audioPlaybackConnections;
inline HICON g_hIconLight = nullptr;
inline HICON g_hIconDark = nullptr;
inline NOTIFYICONDATAW g_nid = {
	.cbSize = sizeof(g_nid),
	.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP,
	.uCallbackMessage = WM_NOTIFYICON,
	.uVersion = NOTIFYICON_VERSION_4
};
inline NOTIFYICONIDENTIFIER g_niid = {
	.cbSize = sizeof(g_niid)
};
inline UINT WM_TASKBAR_CREATED = 0;

struct settings_json_t;

struct settings_t {
    bool reconnect = false;
    std::vector<std::wstring> lastDevices;

    settings_t& operator=(const settings_json_t& rhs);
};

struct settings_json_t {
    bool reconnect = false;
    std::vector<std::string> lastDevices;

    // this is using g_audioPlaybackConnections and not lastDevices from rhs
    settings_json_t& operator=(const settings_t& rhs) {
        reconnect = rhs.reconnect;

        lastDevices.clear();
        lastDevices.reserve(g_audioPlaybackConnections.size());
        for (const auto& dev : g_audioPlaybackConnections) {
            auto utf8 = usylibpp::windows::to_utf8(dev.first);
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

inline settings_t g_Settings{};

#include "SettingsUtil.hpp"
#include "Direct2DSvg.hpp"
