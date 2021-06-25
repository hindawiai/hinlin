<शैली गुरु>
/*
 * Copyright (C) 2010 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश "priv.h"
#समावेश "ram.h"

व्योम
nv10_fb_tile_init(काष्ठा nvkm_fb *fb, पूर्णांक i, u32 addr, u32 size, u32 pitch,
		  u32 flags, काष्ठा nvkm_fb_tile *tile)
अणु
	tile->addr  = 0x80000000 | addr;
	tile->limit = max(1u, addr + size) - 1;
	tile->pitch = pitch;
पूर्ण

व्योम
nv10_fb_tile_fini(काष्ठा nvkm_fb *fb, पूर्णांक i, काष्ठा nvkm_fb_tile *tile)
अणु
	tile->addr  = 0;
	tile->limit = 0;
	tile->pitch = 0;
	tile->zcomp = 0;
पूर्ण

व्योम
nv10_fb_tile_prog(काष्ठा nvkm_fb *fb, पूर्णांक i, काष्ठा nvkm_fb_tile *tile)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	nvkm_wr32(device, 0x100244 + (i * 0x10), tile->limit);
	nvkm_wr32(device, 0x100248 + (i * 0x10), tile->pitch);
	nvkm_wr32(device, 0x100240 + (i * 0x10), tile->addr);
	nvkm_rd32(device, 0x100240 + (i * 0x10));
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
nv10_fb = अणु
	.tile.regions = 8,
	.tile.init = nv10_fb_tile_init,
	.tile.fini = nv10_fb_tile_fini,
	.tile.prog = nv10_fb_tile_prog,
	.ram_new = nv10_ram_new,
पूर्ण;

पूर्णांक
nv10_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस nvkm_fb_new_(&nv10_fb, device, type, inst, pfb);
पूर्ण
