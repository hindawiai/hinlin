<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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

व्योम
gp100_ltc_पूर्णांकr(काष्ठा nvkm_ltc *ltc)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	u32 mask;

	mask = nvkm_rd32(device, 0x0001c0);
	जबतक (mask) अणु
		u32 s, c = __ffs(mask);
		क्रम (s = 0; s < ltc->lts_nr; s++)
			gm107_ltc_पूर्णांकr_lts(ltc, c, s);
		mask &= ~(1 << c);
	पूर्ण
पूर्ण

पूर्णांक
gp100_ltc_oneinit(काष्ठा nvkm_ltc *ltc)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;
	ltc->ltc_nr = nvkm_rd32(device, 0x12006c);
	ltc->lts_nr = nvkm_rd32(device, 0x17e280) >> 28;
	/*XXX: tagram allocation - TBD */
	वापस 0;
पूर्ण

व्योम
gp100_ltc_init(काष्ठा nvkm_ltc *ltc)
अणु
	/*XXX: PMU LS call to setup tagram address */
पूर्ण

अटल स्थिर काष्ठा nvkm_ltc_func
gp100_ltc = अणु
	.oneinit = gp100_ltc_oneinit,
	.init = gp100_ltc_init,
	.पूर्णांकr = gp100_ltc_पूर्णांकr,
	.cbc_clear = gm107_ltc_cbc_clear,
	.cbc_रुको = gm107_ltc_cbc_रुको,
	.zbc = 16,
	.zbc_clear_color = gm107_ltc_zbc_clear_color,
	.zbc_clear_depth = gm107_ltc_zbc_clear_depth,
	.invalidate = gf100_ltc_invalidate,
	.flush = gf100_ltc_flush,
पूर्ण;

पूर्णांक
gp100_ltc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_ltc **pltc)
अणु
	वापस nvkm_ltc_new_(&gp100_ltc, device, type, inst, pltc);
पूर्ण
