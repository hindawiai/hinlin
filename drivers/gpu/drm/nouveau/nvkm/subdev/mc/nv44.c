<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
nv44_mc_init(काष्ठा nvkm_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->subdev.device;
	u32 पंचांगp = nvkm_rd32(device, 0x10020c);

	nvkm_wr32(device, 0x000200, 0xffffffff); /* everything enabled */

	nvkm_wr32(device, 0x001700, पंचांगp);
	nvkm_wr32(device, 0x001704, 0);
	nvkm_wr32(device, 0x001708, 0);
	nvkm_wr32(device, 0x00170c, पंचांगp);
पूर्ण

अटल स्थिर काष्ठा nvkm_mc_func
nv44_mc = अणु
	.init = nv44_mc_init,
	.पूर्णांकr = nv17_mc_पूर्णांकr,
	.पूर्णांकr_unarm = nv04_mc_पूर्णांकr_unarm,
	.पूर्णांकr_rearm = nv04_mc_पूर्णांकr_rearm,
	.पूर्णांकr_stat = nv04_mc_पूर्णांकr_stat,
	.reset = nv17_mc_reset,
पूर्ण;

पूर्णांक
nv44_mc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	वापस nvkm_mc_new_(&nv44_mc, device, type, inst, pmc);
पूर्ण
