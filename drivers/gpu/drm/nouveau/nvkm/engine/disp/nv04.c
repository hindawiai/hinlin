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
#समावेश "head.h"

अटल स्थिर काष्ठा nvkm_disp_oclass *
nv04_disp_root(काष्ठा nvkm_disp *disp)
अणु
	वापस &nv04_disp_root_oclass;
पूर्ण

अटल व्योम
nv04_disp_पूर्णांकr(काष्ठा nvkm_disp *disp)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 crtc0 = nvkm_rd32(device, 0x600100);
	u32 crtc1 = nvkm_rd32(device, 0x602100);
	u32 pvideo;

	अगर (crtc0 & 0x00000001) अणु
		nvkm_disp_vblank(disp, 0);
		nvkm_wr32(device, 0x600100, 0x00000001);
	पूर्ण

	अगर (crtc1 & 0x00000001) अणु
		nvkm_disp_vblank(disp, 1);
		nvkm_wr32(device, 0x602100, 0x00000001);
	पूर्ण

	अगर (device->chipset >= 0x10 && device->chipset <= 0x40) अणु
		pvideo = nvkm_rd32(device, 0x8100);
		अगर (pvideo & ~0x11)
			nvkm_info(subdev, "PVIDEO intr: %08x\n", pvideo);
		nvkm_wr32(device, 0x8100, pvideo);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_disp_func
nv04_disp = अणु
	.पूर्णांकr = nv04_disp_पूर्णांकr,
	.root = nv04_disp_root,
पूर्ण;

पूर्णांक
nv04_disp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_disp **pdisp)
अणु
	पूर्णांक ret, i;

	ret = nvkm_disp_new_(&nv04_disp, device, type, inst, pdisp);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < 2; i++) अणु
		ret = nv04_head_new(*pdisp, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
