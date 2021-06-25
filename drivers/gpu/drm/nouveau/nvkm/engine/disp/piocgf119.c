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
#समावेश "rootnv50.h"

#समावेश <subdev/समयr.h>

अटल व्योम
gf119_disp_pioc_fini(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nv50_disp *disp = chan->disp;
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ctrl = chan->chid.ctrl;
	पूर्णांक user = chan->chid.user;

	nvkm_mask(device, 0x610490 + (ctrl * 0x10), 0x00000001, 0x00000000);
	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x610490 + (ctrl * 0x10)) & 0x00030000))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "ch %d fini: %08x\n", user,
			   nvkm_rd32(device, 0x610490 + (ctrl * 0x10)));
	पूर्ण
पूर्ण

अटल पूर्णांक
gf119_disp_pioc_init(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nv50_disp *disp = chan->disp;
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ctrl = chan->chid.ctrl;
	पूर्णांक user = chan->chid.user;

	/* activate channel */
	nvkm_wr32(device, 0x610490 + (ctrl * 0x10), 0x00000001);
	अगर (nvkm_msec(device, 2000,
		u32 पंचांगp = nvkm_rd32(device, 0x610490 + (ctrl * 0x10));
		अगर ((पंचांगp & 0x00030000) == 0x00010000)
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "ch %d init: %08x\n", user,
			   nvkm_rd32(device, 0x610490 + (ctrl * 0x10)));
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा nv50_disp_chan_func
gf119_disp_pioc_func = अणु
	.init = gf119_disp_pioc_init,
	.fini = gf119_disp_pioc_fini,
	.पूर्णांकr = gf119_disp_chan_पूर्णांकr,
	.user = nv50_disp_chan_user,
पूर्ण;
