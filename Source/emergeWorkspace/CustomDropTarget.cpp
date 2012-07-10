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

#include "CustomDropTarget.h"

CustomDropTarget::CustomDropTarget(UINT type)
{
  refCount = 0;
  this->type = type;

  CF_EMERGE_MENUITEM = RegisterClipboardFormat(TEXT("CF_EMERGE_MENUITEM"));
  if (CF_EMERGE_MENUITEM == 0)
    ELMessageBox(GetDesktopWindow(), (WCHAR*)TEXT("Failed to register Emerge Desktop Menu Item clipboard format."), (WCHAR*)TEXT("emergeWorkspace"),
                 ELMB_OK|ELMB_ICONERROR|ELMB_MODAL);
}

CustomDropTarget::~CustomDropTarget()
{
}

bool CustomDropTarget::QueryDataObject(IDataObject *pDataObject)
{
  FORMATETC fmtetc;

  ZeroMemory(&fmtetc, sizeof(FORMATETC));
  fmtetc.tymed = TYMED_HGLOBAL;
  fmtetc.dwAspect = DVASPECT_CONTENT;
  fmtetc.lindex = -1;
  fmtetc.cfFormat = CF_EMERGE_MENUITEM;

  // does the data object support CF_EMERGE_MENUITEM using a HGLOBAL?
  return pDataObject->QueryGetData(&fmtetc) == S_OK ? true : false;
}

DWORD CustomDropTarget::DropEffect(DWORD grfKeyState, POINTL pt UNUSED, DWORD dwAllowed)
{
  DWORD dwEffect = 0;

  // 1. check "pt" -> do we allow a drop at the specified coordinates?
  // 2. work out that the drop-effect should be based on grfKeyState
  if(grfKeyState & MK_CONTROL)
    dwEffect = dwAllowed & DROPEFFECT_COPY;
  else if(grfKeyState & MK_SHIFT)
    dwEffect = dwAllowed & DROPEFFECT_MOVE;

  // 3. no key-modifiers were specified (or drop effect not allowed), so
  //    base the effect on those allowed by the dropsource
  if(dwEffect == 0)
    {
      if(dwAllowed & DROPEFFECT_COPY)
        dwEffect = DROPEFFECT_COPY;
      if(dwAllowed & DROPEFFECT_MOVE)
        dwEffect = DROPEFFECT_MOVE;
    }

  return dwEffect;
}

bool CustomDropTarget::DataDrop(IDataObject *pDataObj)
{
  FORMATETC fmtetc;
  STGMEDIUM stgmed;

  ZeroMemory(&fmtetc, sizeof(FORMATETC));
  fmtetc.cfFormat = CF_EMERGE_MENUITEM;
  fmtetc.dwAspect = DVASPECT_CONTENT;
  fmtetc.lindex = -1;
  fmtetc.tymed = TYMED_HGLOBAL;

  if (SUCCEEDED(pDataObj->QueryGetData(&fmtetc)))
    {
      if (SUCCEEDED(pDataObj->GetData(&fmtetc, &stgmed)))
        {
          void *data = GlobalLock(stgmed.hGlobal);
          MENUITEMDATA *menuItemData = reinterpret_cast< MENUITEMDATA* >(data);

          ELMessageBox(GetDesktopWindow(), menuItemData->value, menuItemData->name, ELMB_OK);

          GlobalUnlock(stgmed.hGlobal);

          return true;
        }
    }

  return false;
}

STDMETHODIMP_(ULONG) CustomDropTarget::AddRef()
{
  return ++refCount;
}

STDMETHODIMP_(ULONG) CustomDropTarget::Release()
{
  ULONG tmp;
  tmp = --refCount;

  return tmp;
}

STDMETHODIMP CustomDropTarget::QueryInterface(REFIID riid, void ** ppvObject)
{
  if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDropTarget))
    {
      AddRef();
      *ppvObject = this;
      return S_OK;
    }
  else
    {
      *ppvObject = NULL;
      return E_NOINTERFACE;
    }
}

STDMETHODIMP CustomDropTarget::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
  // does the dataobject contain data we want?
  allowDrop = QueryDataObject(pDataObj);

  if(allowDrop)
    // get the dropeffect based on keyboard state
    *pdwEffect = DropEffect(grfKeyState, pt, *pdwEffect);
  else
    *pdwEffect = DROPEFFECT_NONE;

  return S_OK;
}

STDMETHODIMP CustomDropTarget::DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
  if(allowDrop)
    *pdwEffect = DropEffect(grfKeyState, pt, *pdwEffect);
  else
    *pdwEffect = DROPEFFECT_NONE;

  return S_OK;
}

STDMETHODIMP CustomDropTarget::DragLeave()
{
  return S_OK;
}

STDMETHODIMP CustomDropTarget::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
  if(allowDrop)
    {
      DataDrop(pDataObj);
      *pdwEffect = DropEffect(grfKeyState, pt, *pdwEffect);
    }
  else
    *pdwEffect = DROPEFFECT_NONE;

  return S_OK;
}

