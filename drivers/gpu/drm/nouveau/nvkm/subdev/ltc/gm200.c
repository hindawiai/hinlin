<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "priv.h"

#समावेश <subdev/fb.h>
#समावेश <subdev/समयr.h>

अटल पूर्णांक
gm200_ltc_oneinit(काष्ठा nvkm_ltc *ltc)
अणु
	काष्ठा nvkm_device *device = ltc->subdev.device;

	ltc->ltc_nr = nvkm_rd32(device, 0x12006c);
	ltc->lts_nr = nvkm_rd32(device, 0x17e280) >> 28;

	वापस gf100_ltc_oneinit_tag_ram(ltc);
पूर्ण
अटल व्योम
gm200_ltc_init(काष्ठा nvkm_ltc *ltc)
अणु
	nvkm_wr32(ltc->subdev.device, 0x17e278, ltc->tag_base);
पूर्ण

अटल स्थिर काष्ठा nvkm_ltc_func
gm200_ltc = अणु
	.oneinit = gm200_ltc_oneinit,
	.init = gm200_ltc_init,
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
gm200_ltc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_ltc **pltc)
अणु
	वापस nvkm_ltc_new_(&gm200_ltc, device, type, inst, pltc);
पूर्ण
