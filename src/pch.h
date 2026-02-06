#pragma once

#include "targetver.h"

// Windows Header Files
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shobjidl_core.h>
#include <d2d1_3.h>
#include <shlwapi.h>

// C++ RunTime Header Files
#include <cstdlib>
#include <cstdint>
#include <unordered_map>
#include <filesystem>

// glaze
#include <glaze/glaze.hpp>

// wil
#ifndef _DEBUG
#define RESULT_DIAGNOSTICS_LEVEL 1
#endif

// usylibpp (includes wil)
#include <usylibpp/usylibpp.hpp>

#include <wil/common.h>
#include <wil/result.h>
#include <wil/cppwinrt.h>

// C++/WinRT
// Fixes warning C4002: too many arguments for function-like macro invocation 'GetCurrentTime'
#undef GetCurrentTime

#include <winrt/base.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.Metadata.h>
#include <winrt/Windows.Media.Audio.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
