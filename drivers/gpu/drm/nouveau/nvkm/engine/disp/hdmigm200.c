<शैली गुरु>
/*
 * Copyright 2018 Ilia Mirkin
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
 * Authors: Ilia Mirkin
 */
#समावेश "hdmi.h"

व्योम
gm200_hdmi_scdc(काष्ठा nvkm_ior *ior, u8 scdc)
अणु
	काष्ठा nvkm_device *device = ior->disp->engine.subdev.device;
	स्थिर u32 soff = nv50_ior_base(ior);
	स्थिर u32 ctrl = scdc & 0x3;

	nvkm_mask(device, 0x61c5bc + soff, 0x00000003, ctrl);

	ior->पंचांगds.high_speed = !!(scdc & 0x2);
पूर्ण
