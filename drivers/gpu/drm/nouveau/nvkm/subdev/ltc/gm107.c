<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"

#समावेश <subdev/fb.h>
#समावेश <subdev/समयr.h>

व्योम
gm107_ltc_cbc_clear(काष्ठा nvkm_ltc *ltc, u32 start, u32 limit)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	nvkm_wr32(device, 0x17e270, start);
	nvkm_wr32(device, 0x17e274, limit);
	nvkm_mask(device, 0x17e26c, 0x00000000, 0x00000004);
पूर्ण

व्योम
gm107_ltc_cbc_रुको(काष्ठा nvkm_ltc *ltc)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	पूर्णांक c, s;
	क्रम (c = 0; c < ltc->ltc_nr; c++) अणु
		क्रम (s = 0; s < ltc->lts_nr; s++) अणु
			स्थिर u32 addr = 0x14046c + (c * 0x2000) + (s * 0x200);
			nvkm_रुको_msec(device, 2000, addr,
				       0x00000004, 0x00000000);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
gm107_ltc_zbc_clear_color(काष्ठा nvkm_ltc *ltc, पूर्णांक i, स्थिर u32 color[4])
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	nvkm_mask(device, 0x17e338, 0x0000000f, i);
	nvkm_wr32(device, 0x17e33c, color[0]);
	nvkm_wr32(device, 0x17e340, color[1]);
	nvkm_wr32(device, 0x17e344, color[2]);
	nvkm_wr32(device, 0x17e348, color[3]);
पूर्ण

व्योम
gm107_ltc_zbc_clear_depth(काष्ठा nvkm_ltc *ltc, पूर्णांक i, स्थिर u32 depth)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	nvkm_mask(device, 0x17e338, 0x0000000f, i);
	nvkm_wr32(device, 0x17e34c, depth);
पूर्ण

व्योम
gm107_ltc_पूर्णांकr_lts(काष्ठा nvkm_ltc *ltc, पूर्णांक c, पूर्णांक s)
अणु
	काष्ठा nvkm_subdev *subdev = &ltc->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 base = 0x140400 + (c * 0x2000) + (s * 0x200);
	u32 पूर्णांकr = nvkm_rd32(device, base + 0x00c);
	u16 stat = पूर्णांकr & 0x0000ffff;
	अक्षर msg[128];

	अगर (stat) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), gf100_ltc_lts_पूर्णांकr_name, stat);
		nvkm_error(subdev, "LTC%d_LTS%d: %08x [%s]\n", c, s, पूर्णांकr, msg);
	पूर्ण

	nvkm_wr32(device, base + 0x00c, पूर्णांकr);
पूर्ण

व्योम
gm107_ltc_पूर्णांकr(काष्ठा nvkm_ltc *ltc)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	u32 mask;

	mask = nvkm_rd32(device, 0x00017c);
	जबतक (mask) अणु
		u32 s, c = __ffs(mask);
		क्रम (s = 0; s < ltc->lts_nr; s++)
			gm107_ltc_पूर्णांकr_lts(ltc, c, s);
		mask &= ~(1 << c);
	पूर्ण
पूर्ण

अटल पूर्णांक
gm107_ltc_oneinit(काष्ठा nvkm_ltc *ltc)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	स्थिर u32 parts = nvkm_rd32(device, 0x022438);
	स्थिर u32  mask = nvkm_rd32(device, 0x021c14);
	स्थिर u32 slice = nvkm_rd32(device, 0x17e280) >> 28;
	पूर्णांक i;

	क्रम (i = 0; i < parts; i++) अणु
		अगर (!(mask & (1 << i)))
			ltc->ltc_nr++;
	पूर्ण
	ltc->lts_nr = slice;

	वापस gf100_ltc_oneinit_tag_ram(ltc);
पूर्ण

अटल व्योम
gm107_ltc_init(काष्ठा nvkm_ltc *ltc)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	u32 lpg128 = !(nvkm_rd32(device, 0x100c80) & 0x00000001);

	nvkm_wr32(device, 0x17e27c, ltc->ltc_nr);
	nvkm_wr32(device, 0x17e278, ltc->tag_base);
	nvkm_mask(device, 0x17e264, 0x00000002, lpg128 ? 0x00000002 : 0x00000000);
पूर्ण

अटल स्थिर काष्ठा nvkm_ltc_func
gm107_ltc = अणु
	.oneinit = gm107_ltc_oneinit,
	.init = gm107_ltc_init,
	.पूर्णांकr = gm107_ltc_पूर्णांकr,
	.cbc_clear = gm107_ltc_cbc_clear,
	.cbc_रुको = gm107_ltc_cbc_रुको,
	.zbc = 16,
	.zbc_clear_color = gm107_ltc_zbc_clear_color,
	.zbc_clear_depth = gm107_ltc_zbc_clear_depth,
	.invalidate = gf100_ltc_invalidate,
	.flush = gf100_ltc_flush,
पूर्ण;

पूर्णांक
gm107_ltc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_ltc **pltc)
अणु
	वापस nvkm_ltc_new_(&gm107_ltc, device, type, inst, pltc);
पूर्ण
