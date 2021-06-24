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
#समावेश "ram.h"
#समावेश "regsnv04.h"

अटल व्योम
nv04_fb_init(काष्ठा nvkm_fb *fb)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;

	/* This is what the DDX did क्रम NV_ARCH_04, but a mmio-trace shows
	 * nvidia पढ़ोing PFB_CFG_0, then writing back its original value.
	 * (which was 0x701114 in this हाल)
	 */
	nvkm_wr32(device, NV04_PFB_CFG0, 0x1114);
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
nv04_fb = अणु
	.init = nv04_fb_init,
	.ram_new = nv04_ram_new,
पूर्ण;

पूर्णांक
nv04_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस nvkm_fb_new_(&nv04_fb, device, type, inst, pfb);
पूर्ण
