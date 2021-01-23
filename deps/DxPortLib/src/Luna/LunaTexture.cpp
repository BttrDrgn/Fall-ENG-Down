/*
  DxPortLib - A portability library for DxLib-based software.
  Copyright (C) 2013-2015 Patrick McCarthy <mauve@sandwich.net>
  
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
    
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
 */

/* This implementation of LunaTexture is just a frontend to PLGraph. */

#include "Luna.h"

#ifdef DXPORTLIB_LUNA_INTERFACE

#include "PL/PLInternal.h"
#include "LunaInternal.h"
#include "DxPortLib.h"

struct FilenameCache_t {
    DPL::ListNode<FilenameCache_t> node;
    
    int handle;
    
    char *filename;
};

DPL::List<FilenameCache_t> s_filenameList;

static int s_FindTextureFromFilename(const char *filename) {
    DPL::ListNode<FilenameCache_t> *node;
    
    node = s_filenameList.First();
    while (node != NULL) {
        FilenameCache_t *c = node->Value();
        
        if (PL_Text_Strcmp(filename, c->filename) == 0) {
            return c->handle;
        }
        
        node = node->Next();
    }
    
    return -1;
}

static void s_ReleaseTexture(int handle) {
    PLTextureBase *texBase = (PLTextureBase*)PL_Handle_GetData(handle, DXHANDLE_TEXTURE);
    FilenameCache_t *entry;
    
    if (texBase == NULL) {
        return;
    }
    
    entry = (FilenameCache_t *)texBase->userdata;
    if (entry == NULL) {
        return;
    }
    entry->node.Unlink();
    
    DXFREE(entry->filename);
    DXFREE(entry);
}

static void s_AddTexture(int handle, const char *filename) {
    PLTextureBase *texBase = (PLTextureBase*)PL_Handle_GetData(handle, DXHANDLE_TEXTURE);
    FilenameCache_t *entry;
    
    if (texBase == NULL) {
        return;
    }
    
    entry = (FilenameCache_t *)DXALLOC(sizeof(FilenameCache_t));
    entry->filename = PL_Text_Strdup(filename);
    entry->handle = handle;
    texBase->userdata = (void *)entry;
    texBase->releaseFunc = s_ReleaseTexture;
    
    s_filenameList.AddFirst(&entry->node, entry);
}

LTEXTURE LunaTexture::Create(Uint32 Width, Uint32 Height,
                             eSurfaceFormat format)
{
    LTEXTURE handle = (int)PLG.Texture_CreateFromDimensions(Width, Height, true);
    
    return handle;
}

LTEXTURE LunaTexture::CreateFromFile(const char *pFileName,
                                     eSurfaceFormat format,
                                     D3DCOLOR keyColor) {
    char buf[2048];
    int handle = s_FindTextureFromFilename(pFileName);
    int surfaceID;
    
    if (handle > 0) {
        PLG.Texture_AddRef(handle);
        return handle;
    }
    
    surfaceID = PL_Surface_Load(
        PL_Text_ConvertStrncpyIfNecessary(
            buf, -1, pFileName, g_lunaUseCharSet, 2048)
    );
    if (surfaceID < 0) {
        return -1;
    }
    
    if (keyColor != COLORKEY_DISABLE) {
        PL_Surface_ApplyTransparentColor(surfaceID, keyColor | 0xff000000);
    }
    
    handle = PL_Surface_ToTexture(surfaceID);
    PL_Surface_Delete(surfaceID);
    
    PLG.Texture_SetWrap(handle, DXTRUE);
    
    s_AddTexture(handle, pFileName);
    
    return handle;
}

LTEXTURE LunaTexture::CreateFromLAG(const char *pFileName,
                                    const char *pDataName,
                                    eSurfaceFormat format) {
    /* Not supported yet. */
    return INVALID_TEXTURE;
}

LTEXTURE LunaTexture::CreateRenderTarget(Uint32 Width,
                                         Uint32 Height,
                                         eSurfaceFormat format)
{
    LTEXTURE handle = (int)PLG.Texture_CreateFramebuffer(Width, Height, DXTRUE);
    
    return handle;
}

void LunaTexture::Release(LTEXTURE texture) {
    PLG.Texture_Release(texture);
}

void LunaTexture::ColorFill(LTEXTURE texture, D3DCOLOR color) {
    PLRect rect;
    
    PLG.Texture_RenderGetTextureInfo(texture, &rect, NULL, NULL);
    if (rect.w <= 0 || rect.h <= 0) {
        return;
    }
    
    int surf = PL_Surface_Create(rect.w, rect.h);
    if (surf < 0) {
        return;
    }
    
    PL_Surface_FillWithColor(surf, (unsigned int)color);
    
    PL_Surface_DrawToTexture(surf, texture, &rect);
    
    PL_Surface_Delete(surf);
}

int LunaTexture::GetWidth(LTEXTURE texture) {
    PLRect rect;
    
    PLG.Texture_RenderGetTextureInfo(texture, &rect, NULL, NULL);
    
    return rect.w;
}
int LunaTexture::GetHeight(LTEXTURE texture) {
    PLRect rect;
    
    PLG.Texture_RenderGetTextureInfo(texture, &rect, NULL, NULL);
    
    return rect.h;
}

#endif /* #ifdef DXPORTLIB_LUNA_INTERFACE */
