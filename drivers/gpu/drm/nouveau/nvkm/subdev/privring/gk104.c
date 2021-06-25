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
#समावेश <subdev/समयr.h>

अटल व्योम
gk104_privring_पूर्णांकr_hub(काष्ठा nvkm_subdev *privring, पूर्णांक i)
अणु
	काष्ठा nvkm_device *device = privring->device;
	u32 addr = nvkm_rd32(device, 0x122120 + (i * 0x0800));
	u32 data = nvkm_rd32(device, 0x122124 + (i * 0x0800));
	u32 stat = nvkm_rd32(device, 0x122128 + (i * 0x0800));
	nvkm_debug(privring, "HUB%d: %06x %08x (%08x)\n", i, addr, data, stat);
पूर्ण

अटल व्योम
gk104_privring_पूर्णांकr_rop(काष्ठा nvkm_subdev *privring, पूर्णांक i)
अणु
	काष्ठा nvkm_device *device = privring->device;
	u32 addr = nvkm_rd32(device, 0x124120 + (i * 0x0800));
	u32 data = nvkm_rd32(device, 0x124124 + (i * 0x0800));
	u32 stat = nvkm_rd32(device, 0x124128 + (i * 0x0800));
	nvkm_debug(privring, "ROP%d: %06x %08x (%08x)\n", i, addr, data, stat);
पूर्ण

अटल व्योम
gk104_privring_पूर्णांकr_gpc(काष्ठा nvkm_subdev *privring, पूर्णांक i)
अणु
	काष्ठा nvkm_device *device = privring->device;
	u32 addr = nvkm_rd32(device, 0x128120 + (i * 0x0800));
	u32 data = nvkm_rd32(device, 0x128124 + (i * 0x0800));
	u32 stat = nvkm_rd32(device, 0x128128 + (i * 0x0800));
	nvkm_debug(privring, "GPC%d: %06x %08x (%08x)\n", i, addr, data, stat);
पूर्ण

व्योम
gk104_privring_पूर्णांकr(काष्ठा nvkm_subdev *privring)
अणु
	काष्ठा nvkm_device *device = privring->device;
	u32 पूर्णांकr0 = nvkm_rd32(device, 0x120058);
	u32 पूर्णांकr1 = nvkm_rd32(device, 0x12005c);
	u32 hubnr = nvkm_rd32(device, 0x120070);
	u32 ropnr = nvkm_rd32(device, 0x120074);
	u32 gpcnr = nvkm_rd32(device, 0x120078);
	u32 i;

	क्रम (i = 0; (पूर्णांकr0 & 0x0000ff00) && i < hubnr; i++) अणु
		u32 stat = 0x00000100 << i;
		अगर (पूर्णांकr0 & stat) अणु
			gk104_privring_पूर्णांकr_hub(privring, i);
			पूर्णांकr0 &= ~stat;
		पूर्ण
	पूर्ण

	क्रम (i = 0; (पूर्णांकr0 & 0xffff0000) && i < ropnr; i++) अणु
		u32 stat = 0x00010000 << i;
		अगर (पूर्णांकr0 & stat) अणु
			gk104_privring_पूर्णांकr_rop(privring, i);
			पूर्णांकr0 &= ~stat;
		पूर्ण
	पूर्ण

	क्रम (i = 0; पूर्णांकr1 && i < gpcnr; i++) अणु
		u32 stat = 0x00000001 << i;
		अगर (पूर्णांकr1 & stat) अणु
			gk104_privring_पूर्णांकr_gpc(privring, i);
			पूर्णांकr1 &= ~stat;
		पूर्ण
	पूर्ण

	nvkm_mask(device, 0x12004c, 0x0000003f, 0x00000002);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x12004c) & 0x0000003f))
			अवरोध;
	);
पूर्ण

अटल पूर्णांक
gk104_privring_init(काष्ठा nvkm_subdev *privring)
अणु
	काष्ठा nvkm_device *device = privring->device;
	nvkm_mask(device, 0x122318, 0x0003ffff, 0x00001000);
	nvkm_mask(device, 0x12231c, 0x0003ffff, 0x00000200);
	nvkm_mask(device, 0x122310, 0x0003ffff, 0x00000800);
	nvkm_mask(device, 0x122348, 0x0003ffff, 0x00000100);
	nvkm_mask(device, 0x1223b0, 0x0003ffff, 0x00000fff);
	nvkm_mask(device, 0x122348, 0x0003ffff, 0x00000200);
	nvkm_mask(device, 0x122358, 0x0003ffff, 0x00002880);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
gk104_privring = अणु
	.preinit = gk104_privring_init,
	.init = gk104_privring_init,
	.पूर्णांकr = gk104_privring_पूर्णांकr,
पूर्ण;

पूर्णांक
gk104_privring_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		   काष्ठा nvkm_subdev **pprivring)
अणु
	वापस nvkm_subdev_new_(&gk104_privring, device, type, inst, pprivring);
पूर्ण
