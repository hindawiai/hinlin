<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "channv50.h"

#समावेश <subdev/समयr.h>

अटल पूर्णांक
gp102_disp_dmac_init(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ctrl = chan->chid.ctrl;
	पूर्णांक user = chan->chid.user;

	/* initialise channel क्रम dma command submission */
	nvkm_wr32(device, 0x611494 + (ctrl * 0x0010), chan->push);
	nvkm_wr32(device, 0x611498 + (ctrl * 0x0010), 0x00010000);
	nvkm_wr32(device, 0x61149c + (ctrl * 0x0010), 0x00000001);
	nvkm_mask(device, 0x610490 + (ctrl * 0x0010), 0x00000010, 0x00000010);
	nvkm_wr32(device, 0x640000 + (ctrl * 0x1000), chan->suspend_put);
	nvkm_wr32(device, 0x610490 + (ctrl * 0x0010), 0x00000013);

	/* रुको क्रम it to go inactive */
	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x610490 + (ctrl * 0x10)) & 0x80000000))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "ch %d init: %08x\n", user,
			   nvkm_rd32(device, 0x610490 + (ctrl * 0x10)));
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा nv50_disp_chan_func
gp102_disp_dmac_func = अणु
	.init = gp102_disp_dmac_init,
	.fini = gf119_disp_dmac_fini,
	.पूर्णांकr = gf119_disp_chan_पूर्णांकr,
	.user = nv50_disp_chan_user,
	.bind = gf119_disp_dmac_bind,
पूर्ण;
