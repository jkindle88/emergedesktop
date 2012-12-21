//----  --------------------------------------------------------------------------------------------------------
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
//----  --------------------------------------------------------------------------------------------------------
//
// Note: The task menu code was derived from BBSystemBar which is part of the
// BB4Win source code, copyright 2001-2004 The Blackbox for Windows Development
// Team.
//
//----  --------------------------------------------------------------------------------------------------------

#ifndef __ET_TASK_H
#define __ET_TASK_H

// Defines required for tooltip
#undef _WIN32_IE
#define _WIN32_IE 0x0600

#include "../emergeLib/emergeLib.h"
#include "../emergeGraphics/emergeGraphics.h"
#include "../emergeAppletEngine/emergeAppletEngine.h"
#include <commctrl.h>
#include "Thumbnail.h"

#define TIP_SIZE 256


//====================
// The Task Class
class Task: public Thumbnail
{
public:
  Task(HWND task, HINSTANCE mainInstance, Settings *pSettings);
  ~Task();

  HWND GetWnd();
  HICON GetIcon();
  RECT *GetRect();
  bool GetFlash();
  bool GetVisible();
  void SetIcon(HICON icon, int iconSize);
  void SetRect(RECT rect);
  void SetFlash(bool flash);
  void DisplayMenu(HWND callingWnd);
  void ToggleVisible();
  void SetFlashCount(UINT flashCount);
  UINT GetFlashCount();
  void CreateNewIcon(BYTE foregroundAlpha, BYTE backgroundAlpha);
  void UpdateIcon();
  void SetHidden(bool hidden);
  bool GetHidden();

private:
  HWND wnd;
  HICON origIcon, newIcon;
  HINSTANCE mainInstance;
  RECT rect;
  bool flash, visible, hidden;
  UINT flashCount;
  bool convertIcon;
};

//====================

#endif

