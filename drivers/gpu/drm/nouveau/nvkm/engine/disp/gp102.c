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
#समावेश "nv50.h"
#समावेश "head.h"
#समावेश "ior.h"
#समावेश "channv50.h"
#समावेश "rootnv50.h"

अटल व्योम
gp102_disp_पूर्णांकr_error(काष्ठा nv50_disp *disp, पूर्णांक chid)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mthd = nvkm_rd32(device, 0x6111f0 + (chid * 12));
	u32 data = nvkm_rd32(device, 0x6111f4 + (chid * 12));
	u32 unkn = nvkm_rd32(device, 0x6111f8 + (chid * 12));

	nvkm_error(subdev, "chid %d mthd %04x data %08x %08x %08x\n",
		   chid, (mthd & 0x0000ffc), data, mthd, unkn);

	अगर (chid < ARRAY_SIZE(disp->chan)) अणु
		चयन (mthd & 0xffc) अणु
		हाल 0x0080:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_ERROR);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x61009c, (1 << chid));
	nvkm_wr32(device, 0x6111f0 + (chid * 12), 0x90000000);
पूर्ण

अटल स्थिर काष्ठा nv50_disp_func
gp102_disp = अणु
	.init = gf119_disp_init,
	.fini = gf119_disp_fini,
	.पूर्णांकr = gf119_disp_पूर्णांकr,
	.पूर्णांकr_error = gp102_disp_पूर्णांकr_error,
	.uevent = &gf119_disp_chan_uevent,
	.super = gf119_disp_super,
	.root = &gp102_disp_root_oclass,
	.head = अणु .cnt = gf119_head_cnt, .new = gf119_head_new पूर्ण,
	.sor = अणु .cnt = gf119_sor_cnt, .new = gp100_sor_new पूर्ण,
पूर्ण;

पूर्णांक
gp102_disp_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_disp **pdisp)
अणु
	वापस nv50_disp_new_(&gp102_disp, device, type, inst, pdisp);
पूर्ण
