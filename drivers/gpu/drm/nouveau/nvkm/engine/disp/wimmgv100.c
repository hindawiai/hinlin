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

#समावेश <core/client.h>

#समावेश <nvअगर/clc37b.h>
#समावेश <nvअगर/unpack.h>

अटल व्योम
gv100_disp_wimm_पूर्णांकr(काष्ठा nv50_disp_chan *chan, bool en)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 mask = 0x00000001 << chan->head;
	स्थिर u32 data = en ? mask : 0;
	nvkm_mask(device, 0x611da8, mask, data);
पूर्ण

स्थिर काष्ठा nv50_disp_chan_func
gv100_disp_wimm = अणु
	.init = gv100_disp_dmac_init,
	.fini = gv100_disp_dmac_fini,
	.पूर्णांकr = gv100_disp_wimm_पूर्णांकr,
	.user = gv100_disp_chan_user,
पूर्ण;

अटल पूर्णांक
gv100_disp_wimm_new_(स्थिर काष्ठा nv50_disp_chan_func *func,
		     स्थिर काष्ठा nv50_disp_chan_mthd *mthd,
		     काष्ठा nv50_disp *disp, पूर्णांक chid,
		     स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		     काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nvc37b_winकरोw_imm_channel_dma_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_object *parent = oclass->parent;
	पूर्णांक wndw, ret = -ENOSYS;
	u64 push;

	nvअगर_ioctl(parent, "create window imm channel dma size %d\n", argc);
	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create window imm channel dma vers %d "
				   "pushbuf %016llx index %d\n",
			   args->v0.version, args->v0.pushbuf, args->v0.index);
		अगर (!(disp->wndw.mask & BIT(args->v0.index)))
			वापस -EINVAL;
		push = args->v0.pushbuf;
		wndw = args->v0.index;
	पूर्ण अन्यथा
		वापस ret;

	वापस nv50_disp_dmac_new_(func, mthd, disp, chid + wndw,
				   wndw, push, oclass, pobject);
पूर्ण

पूर्णांक
gv100_disp_wimm_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	वापस gv100_disp_wimm_new_(&gv100_disp_wimm, शून्य, disp, 33,
				    oclass, argv, argc, pobject);
पूर्ण
