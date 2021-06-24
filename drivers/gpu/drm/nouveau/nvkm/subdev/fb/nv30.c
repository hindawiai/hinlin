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
nv30_fb_tile_init(काष्ठा nvkm_fb *fb, पूर्णांक i, u32 addr, u32 size, u32 pitch,
		  u32 flags, काष्ठा nvkm_fb_tile *tile)
अणु
	/* क्रम perक्रमmance, select alternate bank offset क्रम zeta */
	अगर (!(flags & 4)) अणु
		tile->addr = (0 << 4);
	पूर्ण अन्यथा अणु
		अगर (fb->func->tile.comp) /* z compression */
			fb->func->tile.comp(fb, i, size, flags, tile);
		tile->addr = (1 << 4);
	पूर्ण

	tile->addr |= 0x00000001; /* enable */
	tile->addr |= addr;
	tile->limit = max(1u, addr + size) - 1;
	tile->pitch = pitch;
पूर्ण

अटल व्योम
nv30_fb_tile_comp(काष्ठा nvkm_fb *fb, पूर्णांक i, u32 size, u32 flags,
		  काष्ठा nvkm_fb_tile *tile)
अणु
	u32 tiles = DIV_ROUND_UP(size, 0x40);
	u32 tags  = round_up(tiles / fb->ram->parts, 0x40);
	अगर (!nvkm_mm_head(&fb->tags.mm, 0, 1, tags, tags, 1, &tile->tag)) अणु
		अगर (flags & 2) tile->zcomp |= 0x01000000; /* Z16 */
		अन्यथा           tile->zcomp |= 0x02000000; /* Z24S8 */
		tile->zcomp |= ((tile->tag->offset           ) >> 6);
		tile->zcomp |= ((tile->tag->offset + tags - 1) >> 6) << 12;
#अगर_घोषित __BIG_ENDIAN
		tile->zcomp |= 0x10000000;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक
calc_bias(काष्ठा nvkm_fb *fb, पूर्णांक k, पूर्णांक i, पूर्णांक j)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	पूर्णांक b = (device->chipset > 0x30 ?
		 nvkm_rd32(device, 0x122c + 0x10 * k + 0x4 * j) >>
			(4 * (i ^ 1)) :
		 0) & 0xf;

	वापस 2 * (b & 0x8 ? b - 0x10 : b);
पूर्ण

अटल पूर्णांक
calc_ref(काष्ठा nvkm_fb *fb, पूर्णांक l, पूर्णांक k, पूर्णांक i)
अणु
	पूर्णांक j, x = 0;

	क्रम (j = 0; j < 4; j++) अणु
		पूर्णांक m = (l >> (8 * i) & 0xff) + calc_bias(fb, k, i, j);

		x |= (0x80 | clamp(m, 0, 0x1f)) << (8 * j);
	पूर्ण

	वापस x;
पूर्ण

व्योम
nv30_fb_init(काष्ठा nvkm_fb *fb)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	पूर्णांक i, j;

	/* Init the memory timing regs at 0x10037c/0x1003ac */
	अगर (device->chipset == 0x30 ||
	    device->chipset == 0x31 ||
	    device->chipset == 0x35) अणु
		/* Related to ROP count */
		पूर्णांक n = (device->chipset == 0x31 ? 2 : 4);
		पूर्णांक l = nvkm_rd32(device, 0x1003d0);

		क्रम (i = 0; i < n; i++) अणु
			क्रम (j = 0; j < 3; j++)
				nvkm_wr32(device, 0x10037c + 0xc * i + 0x4 * j,
					  calc_ref(fb, l, 0, j));

			क्रम (j = 0; j < 2; j++)
				nvkm_wr32(device, 0x1003ac + 0x8 * i + 0x4 * j,
					  calc_ref(fb, l, 1, j));
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
nv30_fb = अणु
	.tags = nv20_fb_tags,
	.init = nv30_fb_init,
	.tile.regions = 8,
	.tile.init = nv30_fb_tile_init,
	.tile.comp = nv30_fb_tile_comp,
	.tile.fini = nv20_fb_tile_fini,
	.tile.prog = nv20_fb_tile_prog,
	.ram_new = nv20_ram_new,
पूर्ण;

पूर्णांक
nv30_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस nvkm_fb_new_(&nv30_fb, device, type, inst, pfb);
पूर्ण
