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

#समावेश <core/client.h>
#समावेश <core/ramht.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/mmu.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/dma.h>

पूर्णांक
nv50_disp_dmac_new_(स्थिर काष्ठा nv50_disp_chan_func *func,
		    स्थिर काष्ठा nv50_disp_chan_mthd *mthd,
		    काष्ठा nv50_disp *disp, पूर्णांक chid, पूर्णांक head, u64 push,
		    स्थिर काष्ठा nvkm_oclass *oclass,
		    काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_client *client = oclass->client;
	काष्ठा nv50_disp_chan *chan;
	पूर्णांक ret;

	ret = nv50_disp_chan_new_(func, mthd, disp, chid, chid, head, oclass,
				  pobject);
	chan = nv50_disp_chan(*pobject);
	अगर (ret)
		वापस ret;

	chan->memory = nvkm_umem_search(client, push);
	अगर (IS_ERR(chan->memory))
		वापस PTR_ERR(chan->memory);

	अगर (nvkm_memory_size(chan->memory) < 0x1000)
		वापस -EINVAL;

	चयन (nvkm_memory_target(chan->memory)) अणु
	हाल NVKM_MEM_TARGET_VRAM: chan->push = 0x00000001; अवरोध;
	हाल NVKM_MEM_TARGET_NCOH: chan->push = 0x00000002; अवरोध;
	हाल NVKM_MEM_TARGET_HOST: chan->push = 0x00000003; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	chan->push |= nvkm_memory_addr(chan->memory) >> 8;
	वापस 0;
पूर्ण

पूर्णांक
nv50_disp_dmac_bind(काष्ठा nv50_disp_chan *chan,
		    काष्ठा nvkm_object *object, u32 handle)
अणु
	वापस nvkm_ramht_insert(chan->disp->ramht, object,
				 chan->chid.user, -10, handle,
				 chan->chid.user << 28 |
				 chan->chid.user);
पूर्ण

अटल व्योम
nv50_disp_dmac_fini(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ctrl = chan->chid.ctrl;
	पूर्णांक user = chan->chid.user;

	/* deactivate channel */
	nvkm_mask(device, 0x610200 + (ctrl * 0x0010), 0x00001010, 0x00001000);
	nvkm_mask(device, 0x610200 + (ctrl * 0x0010), 0x00000003, 0x00000000);
	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x610200 + (ctrl * 0x10)) & 0x001e0000))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "ch %d fini timeout, %08x\n", user,
			   nvkm_rd32(device, 0x610200 + (ctrl * 0x10)));
	पूर्ण

	chan->suspend_put = nvkm_rd32(device, 0x640000 + (ctrl * 0x1000));
पूर्ण

अटल पूर्णांक
nv50_disp_dmac_init(काष्ठा nv50_disp_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &chan->disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक ctrl = chan->chid.ctrl;
	पूर्णांक user = chan->chid.user;

	/* initialise channel क्रम dma command submission */
	nvkm_wr32(device, 0x610204 + (ctrl * 0x0010), chan->push);
	nvkm_wr32(device, 0x610208 + (ctrl * 0x0010), 0x00010000);
	nvkm_wr32(device, 0x61020c + (ctrl * 0x0010), ctrl);
	nvkm_mask(device, 0x610200 + (ctrl * 0x0010), 0x00000010, 0x00000010);
	nvkm_wr32(device, 0x640000 + (ctrl * 0x1000), chan->suspend_put);
	nvkm_wr32(device, 0x610200 + (ctrl * 0x0010), 0x00000013);

	/* रुको क्रम it to go inactive */
	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x610200 + (ctrl * 0x10)) & 0x80000000))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "ch %d init timeout, %08x\n", user,
			   nvkm_rd32(device, 0x610200 + (ctrl * 0x10)));
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा nv50_disp_chan_func
nv50_disp_dmac_func = अणु
	.init = nv50_disp_dmac_init,
	.fini = nv50_disp_dmac_fini,
	.पूर्णांकr = nv50_disp_chan_पूर्णांकr,
	.user = nv50_disp_chan_user,
	.bind = nv50_disp_dmac_bind,
पूर्ण;
