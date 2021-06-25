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

#समावेश <subdev/समयr.h>

अटल पूर्णांक
gv100_disp_curs_idle(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 soff = (chan->chid.ctrl - 1) * 0x04;
	nvkm_msec(device, 2000,
		u32 stat = nvkm_rd32(device, 0x610664 + soff);
		अगर ((stat & 0x00070000) == 0x00040000)
			वापस 0;
	);
	वापस -EBUSY;
पूर्ण

अटल व्योम
gv100_disp_curs_पूर्णांकr(काष्ठा nv50_disp_chan *chan, bool en)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 mask = 0x00010000 << chan->head;
	स्थिर u32 data = en ? mask : 0;
	nvkm_mask(device, 0x611dac, mask, data);
पूर्ण

अटल व्योम
gv100_disp_curs_fini(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 hoff = chan->chid.ctrl * 4;
	nvkm_mask(device, 0x6104e0 + hoff, 0x00000010, 0x00000010);
	gv100_disp_curs_idle(chan);
	nvkm_mask(device, 0x6104e0 + hoff, 0x00000001, 0x00000000);
पूर्ण

अटल पूर्णांक
gv100_disp_curs_init(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	nvkm_wr32(device, 0x6104e0 + chan->chid.ctrl * 4, 0x00000001);
	वापस gv100_disp_curs_idle(chan);
पूर्ण

अटल स्थिर काष्ठा nv50_disp_chan_func
gv100_disp_curs = अणु
	.init = gv100_disp_curs_init,
	.fini = gv100_disp_curs_fini,
	.पूर्णांकr = gv100_disp_curs_पूर्णांकr,
	.user = gv100_disp_chan_user,
पूर्ण;

पूर्णांक
gv100_disp_curs_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_curs_new_(&gv100_disp_curs, disp, 73, 73,
				   oclass, argv, argc, pobject);
पूर्ण
