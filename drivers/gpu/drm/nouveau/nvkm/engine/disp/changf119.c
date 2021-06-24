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
#समावेश "channv50.h"

अटल व्योम
gf119_disp_chan_uevent_fini(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nv50_disp *disp = container_of(event, typeof(*disp), uevent);
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	nvkm_mask(device, 0x610090, 0x00000001 << index, 0x00000000 << index);
	nvkm_wr32(device, 0x61008c, 0x00000001 << index);
पूर्ण

अटल व्योम
gf119_disp_chan_uevent_init(काष्ठा nvkm_event *event, पूर्णांक types, पूर्णांक index)
अणु
	काष्ठा nv50_disp *disp = container_of(event, typeof(*disp), uevent);
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	nvkm_wr32(device, 0x61008c, 0x00000001 << index);
	nvkm_mask(device, 0x610090, 0x00000001 << index, 0x00000001 << index);
पूर्ण

स्थिर काष्ठा nvkm_event_func
gf119_disp_chan_uevent = अणु
	.ctor = nv50_disp_chan_uevent_ctor,
	.init = gf119_disp_chan_uevent_init,
	.fini = gf119_disp_chan_uevent_fini,
पूर्ण;

व्योम
gf119_disp_chan_पूर्णांकr(काष्ठा nv50_disp_chan *chan, bool en)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 mask = 0x00000001 << chan->chid.user;
	अगर (!en) अणु
		nvkm_mask(device, 0x610090, mask, 0x00000000);
		nvkm_mask(device, 0x6100a0, mask, 0x00000000);
	पूर्ण अन्यथा अणु
		nvkm_mask(device, 0x6100a0, mask, mask);
	पूर्ण
पूर्ण
