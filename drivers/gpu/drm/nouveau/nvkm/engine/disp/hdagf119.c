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
#समावेश "ior.h"

व्योम
gf119_hda_device_entry(काष्ठा nvkm_ior *ior, पूर्णांक head)
अणु
	काष्ठा nvkm_device *device = ior->disp->engine.subdev.device;
	स्थिर u32 hoff = 0x800 * head;
	nvkm_mask(device, 0x616548 + hoff, 0x00000070, head << 4);
पूर्ण

व्योम
gf119_hda_eld(काष्ठा nvkm_ior *ior, पूर्णांक head, u8 *data, u8 size)
अणु
	काष्ठा nvkm_device *device = ior->disp->engine.subdev.device;
	स्थिर u32 soff = 0x030 * ior->id + (head * 0x04);
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		nvkm_wr32(device, 0x10ec00 + soff, (i << 8) | data[i]);
	क्रम (; i < 0x60; i++)
		nvkm_wr32(device, 0x10ec00 + soff, (i << 8));
	nvkm_mask(device, 0x10ec10 + soff, 0x80000002, 0x80000002);
पूर्ण

व्योम
gf119_hda_hpd(काष्ठा nvkm_ior *ior, पूर्णांक head, bool present)
अणु
	काष्ठा nvkm_device *device = ior->disp->engine.subdev.device;
	स्थिर u32 soff = 0x030 * ior->id + (head * 0x04);
	u32 data = 0x80000000;
	u32 mask = 0x80000001;
	अगर (present) अणु
		ior->func->hda.device_entry(ior, head);
		data |= 0x00000001;
	पूर्ण अन्यथा अणु
		mask |= 0x00000002;
	पूर्ण
	nvkm_mask(device, 0x10ec10 + soff, mask, data);
पूर्ण
