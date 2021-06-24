<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "channv50.h"

#समावेश <core/ramht.h>
#समावेश <subdev/समयr.h>

अटल पूर्णांक
gv100_disp_dmac_idle(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 soff = (chan->chid.ctrl - 1) * 0x04;
	nvkm_msec(device, 2000,
		u32 stat = nvkm_rd32(device, 0x610664 + soff);
		अगर ((stat & 0x000f0000) == 0x00040000)
			वापस 0;
	);
	वापस -EBUSY;
पूर्ण

पूर्णांक
gv100_disp_dmac_bind(काष्ठा nv50_disp_chan *chan,
		     काष्ठा nvkm_object *object, u32 handle)
अणु
	वापस nvkm_ramht_insert(chan->disp->ramht, object,
				 chan->chid.user, -9, handle,
				 chan->chid.user << 25 | 0x00000040);
पूर्ण

व्योम
gv100_disp_dmac_fini(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 uoff = (chan->chid.ctrl - 1) * 0x1000;
	स्थिर u32 coff = chan->chid.ctrl * 0x04;
	nvkm_mask(device, 0x6104e0 + coff, 0x00000010, 0x00000000);
	gv100_disp_dmac_idle(chan);
	nvkm_mask(device, 0x6104e0 + coff, 0x00000002, 0x00000000);
	chan->suspend_put = nvkm_rd32(device, 0x690000 + uoff);
पूर्ण

पूर्णांक
gv100_disp_dmac_init(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 uoff = (chan->chid.ctrl - 1) * 0x1000;
	स्थिर u32 poff = chan->chid.ctrl * 0x10;
	स्थिर u32 coff = chan->chid.ctrl * 0x04;

	nvkm_wr32(device, 0x610b24 + poff, lower_32_bits(chan->push));
	nvkm_wr32(device, 0x610b20 + poff, upper_32_bits(chan->push));
	nvkm_wr32(device, 0x610b28 + poff, 0x00000001);
	nvkm_wr32(device, 0x610b2c + poff, 0x00000040);

	nvkm_mask(device, 0x6104e0 + coff, 0x00000010, 0x00000010);
	nvkm_wr32(device, 0x690000 + uoff, chan->suspend_put);
	nvkm_wr32(device, 0x6104e0 + coff, 0x00000013);
	वापस gv100_disp_dmac_idle(chan);
पूर्ण
