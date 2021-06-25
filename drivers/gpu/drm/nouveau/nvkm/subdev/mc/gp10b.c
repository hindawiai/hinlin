<शैली गुरु>
/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
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
 */

#समावेश "priv.h"

अटल व्योम
gp10b_mc_init(काष्ठा nvkm_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->subdev.device;
	nvkm_wr32(device, 0x000200, 0xffffffff); /* everything on */
	nvkm_wr32(device, 0x00020c, 0xffffffff); /* everything out of ELPG */
पूर्ण

अटल स्थिर काष्ठा nvkm_mc_func
gp10b_mc = अणु
	.init = gp10b_mc_init,
	.पूर्णांकr = gp100_mc_पूर्णांकr,
	.पूर्णांकr_unarm = gp100_mc_पूर्णांकr_unarm,
	.पूर्णांकr_rearm = gp100_mc_पूर्णांकr_rearm,
	.पूर्णांकr_mask = gp100_mc_पूर्णांकr_mask,
	.पूर्णांकr_stat = gf100_mc_पूर्णांकr_stat,
	.reset = gk104_mc_reset,
पूर्ण;

पूर्णांक
gp10b_mc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	वापस gp100_mc_new_(&gp10b_mc, device, type, inst, pmc);
पूर्ण
