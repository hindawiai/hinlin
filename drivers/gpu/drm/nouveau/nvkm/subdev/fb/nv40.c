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
nv40_fb_tile_comp(काष्ठा nvkm_fb *fb, पूर्णांक i, u32 size, u32 flags,
		  काष्ठा nvkm_fb_tile *tile)
अणु
	u32 tiles = DIV_ROUND_UP(size, 0x80);
	u32 tags  = round_up(tiles / fb->ram->parts, 0x100);
	अगर ( (flags & 2) &&
	    !nvkm_mm_head(&fb->tags.mm, 0, 1, tags, tags, 1, &tile->tag)) अणु
		tile->zcomp  = 0x28000000; /* Z24S8_SPLIT_GRAD */
		tile->zcomp |= ((tile->tag->offset           ) >> 8);
		tile->zcomp |= ((tile->tag->offset + tags - 1) >> 8) << 13;
#अगर_घोषित __BIG_ENDIAN
		tile->zcomp |= 0x40000000;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम
nv40_fb_init(काष्ठा nvkm_fb *fb)
अणु
	nvkm_mask(fb->subdev.device, 0x10033c, 0x00008000, 0x00000000);
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
nv40_fb = अणु
	.tags = nv20_fb_tags,
	.init = nv40_fb_init,
	.tile.regions = 8,
	.tile.init = nv30_fb_tile_init,
	.tile.comp = nv40_fb_tile_comp,
	.tile.fini = nv20_fb_tile_fini,
	.tile.prog = nv20_fb_tile_prog,
	.ram_new = nv40_ram_new,
पूर्ण;

पूर्णांक
nv40_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस nvkm_fb_new_(&nv40_fb, device, type, inst, pfb);
पूर्ण
