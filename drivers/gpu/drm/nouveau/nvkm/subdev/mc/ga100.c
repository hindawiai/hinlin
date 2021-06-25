<शैली गुरु>
/*
 * Copyright 2021 Red Hat Inc.
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
 */
#समावेश "priv.h"

अटल व्योम
ga100_mc_पूर्णांकr_unarm(काष्ठा nvkm_mc *mc)
अणु
	nvkm_wr32(mc->subdev.device, 0xb81610, 0x00000004);
पूर्ण

अटल व्योम
ga100_mc_पूर्णांकr_rearm(काष्ठा nvkm_mc *mc)
अणु
	nvkm_wr32(mc->subdev.device, 0xb81608, 0x00000004);
पूर्ण

अटल व्योम
ga100_mc_पूर्णांकr_mask(काष्ठा nvkm_mc *mc, u32 mask, u32 पूर्णांकr)
अणु
	nvkm_wr32(mc->subdev.device, 0xb81210,          mask & पूर्णांकr );
	nvkm_wr32(mc->subdev.device, 0xb81410, mask & ~(mask & पूर्णांकr));
पूर्ण

अटल u32
ga100_mc_पूर्णांकr_stat(काष्ठा nvkm_mc *mc)
अणु
	u32 पूर्णांकr_top = nvkm_rd32(mc->subdev.device, 0xb81600), पूर्णांकr = 0x00000000;
	अगर (पूर्णांकr_top & 0x00000004)
		पूर्णांकr = nvkm_mask(mc->subdev.device, 0xb81010, 0x00000000, 0x00000000);
	वापस पूर्णांकr;
पूर्ण

अटल व्योम
ga100_mc_init(काष्ठा nvkm_mc *mc)
अणु
	nv50_mc_init(mc);
	nvkm_wr32(mc->subdev.device, 0xb81210, 0xffffffff);
पूर्ण

अटल स्थिर काष्ठा nvkm_mc_func
ga100_mc = अणु
	.init = ga100_mc_init,
	.पूर्णांकr = gp100_mc_पूर्णांकr,
	.पूर्णांकr_unarm = ga100_mc_पूर्णांकr_unarm,
	.पूर्णांकr_rearm = ga100_mc_पूर्णांकr_rearm,
	.पूर्णांकr_mask = ga100_mc_पूर्णांकr_mask,
	.पूर्णांकr_stat = ga100_mc_पूर्णांकr_stat,
	.reset = gk104_mc_reset,
पूर्ण;

पूर्णांक
ga100_mc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	वापस nvkm_mc_new_(&ga100_mc, device, type, inst, pmc);
पूर्ण
