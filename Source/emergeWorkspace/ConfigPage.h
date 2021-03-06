//---
//
//  This file is part of Emerge Desktop.
//  Copyright (C) 2004-2012  The Emerge Desktop Development Team
//
//  Emerge Desktop is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  Emerge Desktop is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//---

#pragma once

#undef _WIN32_IE
#define _WIN32_IE	0x501

#undef _WIN32_WINNT
#define _WIN32_WINNT	0x501

#include "Settings.h"
#include <shlwapi.h>
#include <commctrl.h>
#include "resource.h"
#include <map>
#include <string>

//GetVersionEx is deprecated in Visual Studio, to be replaced by IsWindows* functions. It's supposed to be deprecated
//in other compilers too, but so far only VS has the replacements implemented. So we'll have to roll our own for other
//compilers until GCC gets around to adding proper support.
#ifdef _MSC_VER
#include <versionhelpers.h>
#else
inline bool IsWindowsVistaOrGreater()
{
  OSVERSIONINFO osv;

  ZeroMemory(&osv, sizeof(osv));

  osv.dwOSVersionInfoSize = sizeof(osv);
  GetVersionEx(&osv);

  return ((osv.dwMajorVersion + (osv.dwMinorVersion / 10.0)) >= 6.0);
}
#endif

class ConfigPage
{
public:
  ConfigPage(HINSTANCE hInstance, std::tr1::shared_ptr<Settings> pSettings);
  ~ConfigPage();
  int Show();
  BOOL DoInitDialog(HWND hwndDlg);
  BOOL DoSettingsCommand(HWND hwndDlg, WPARAM wParam, LPARAM lParam);
  BOOL DoSettingsNotify(HWND hwndDlg, LPARAM lParam);
  BOOL DoSettingsChange(HWND hwndDlg, WPARAM wParam);
  bool UpdateSettings(HWND hwndDlg);
  bool GetVisible();
  static INT_PTR CALLBACK ConfigPageDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
  std::tr1::shared_ptr<Settings> pSettings;
  void SetTooltip(HWND browseWnd, UINT type);
  bool dialogVisible;
  HINSTANCE hInstance;
  HWND toolWnd;
};
