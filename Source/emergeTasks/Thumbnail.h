/*!
  @file Thumbnail.h
  @brief header for emergeTasks
  @author The Emerge Desktop Development Team

  @attention This file is part of Emerge Desktop.
  @attention Copyright (C) 2004-2013  The Emerge Desktop Development Team

  @attention Emerge Desktop is free software; you can redistribute it and/or
  modify  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  @attention Emerge Desktop is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  @attention You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#ifndef __GUARD_8710e75a_a313_4603_b006_3d778bd929ad
#define __GUARD_8710e75a_a313_4603_b006_3d778bd929ad

#define UNICODE 1

// Define required for the Window Transparency
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501

// Define required for menu animation
#undef WINVER
#define WINVER 0x0501

#undef _WIN32_IE
#define _WIN32_IE 0x0501

#define OEMRESOURCE 1

#include "../emergeGraphics/emergeGraphics.h"
#include "../emergeAppletEngine/emergeAppletEngine.h"
#include "Settings.h"

#define BALLOON_TIMER_ID 1

#ifndef NIIF_USER
#define NIIF_USER 0x4
#endif

#ifndef NIIF_LARGE_ICON
#define NIIF_LARGE_ICON 0x20
#endif

class TrayIcon;

class Thumbnail
{
public:
  Thumbnail(HWND taskWnd, HINSTANCE instance, Settings* pSettings);
  ~Thumbnail();
  void ShowThumbnail(HWND ownerWnd, RECT* taskRect);
  void HideThumbnail();
  HWND GetThumbnailWnd();

private:
  HTHUMBNAIL dwmThumbnailId;
  HWND dwmThumbnailWnd;
  static LRESULT CALLBACK ThumbnailProcedure (HWND, UINT, WPARAM, LPARAM);
  Settings* pSettings;
};

#endif
