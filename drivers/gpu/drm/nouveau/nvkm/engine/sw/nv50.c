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
#समावेश "nv50.h"

#समावेश <core/gpuobj.h>
#समावेश <engine/disp.h>
#समावेश <engine/fअगरo/chan.h>
#समावेश <subdev/bar.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/event.h>

/*******************************************************************************
 * software context
 ******************************************************************************/

अटल पूर्णांक
nv50_sw_chan_vblsem_release(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nv50_sw_chan *chan =
		container_of(notअगरy, typeof(*chan), vblank.notअगरy[notअगरy->index]);
	काष्ठा nvkm_sw *sw = chan->base.sw;
	काष्ठा nvkm_device *device = sw->engine.subdev.device;

	nvkm_wr32(device, 0x001704, chan->base.fअगरo->inst->addr >> 12);
	nvkm_wr32(device, 0x001710, 0x80000000 | chan->vblank.ctxdma);
	nvkm_bar_flush(device->bar);

	अगर (device->chipset == 0x50) अणु
		nvkm_wr32(device, 0x001570, chan->vblank.offset);
		nvkm_wr32(device, 0x001574, chan->vblank.value);
	पूर्ण अन्यथा अणु
		nvkm_wr32(device, 0x060010, chan->vblank.offset);
		nvkm_wr32(device, 0x060014, chan->vblank.value);
	पूर्ण

	वापस NVKM_NOTIFY_DROP;
पूर्ण

अटल bool
nv50_sw_chan_mthd(काष्ठा nvkm_sw_chan *base, पूर्णांक subc, u32 mthd, u32 data)
अणु
	काष्ठा nv50_sw_chan *chan = nv50_sw_chan(base);
	काष्ठा nvkm_engine *engine = chan->base.object.engine;
	काष्ठा nvkm_device *device = engine->subdev.device;
	चयन (mthd) अणु
	हाल 0x018c: chan->vblank.ctxdma = data; वापस true;
	हाल 0x0400: chan->vblank.offset = data; वापस true;
	हाल 0x0404: chan->vblank.value  = data; वापस true;
	हाल 0x0408:
		अगर (data < device->disp->vblank.index_nr) अणु
			nvkm_notअगरy_get(&chan->vblank.notअगरy[data]);
			वापस true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

व्योम *
nv50_sw_chan_dtor(काष्ठा nvkm_sw_chan *base)
अणु
	काष्ठा nv50_sw_chan *chan = nv50_sw_chan(base);
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(chan->vblank.notअगरy); i++)
		nvkm_notअगरy_fini(&chan->vblank.notअगरy[i]);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_sw_chan_func
nv50_sw_chan = अणु
	.dtor = nv50_sw_chan_dtor,
	.mthd = nv50_sw_chan_mthd,
पूर्ण;

अटल पूर्णांक
nv50_sw_chan_new(काष्ठा nvkm_sw *sw, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_disp *disp = sw->engine.subdev.device->disp;
	काष्ठा nv50_sw_chan *chan;
	पूर्णांक ret, i;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &chan->base.object;

	ret = nvkm_sw_chan_ctor(&nv50_sw_chan, sw, fअगरoch, oclass, &chan->base);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; disp && i < disp->vblank.index_nr; i++) अणु
		ret = nvkm_notअगरy_init(शून्य, &disp->vblank,
				       nv50_sw_chan_vblsem_release, false,
				       &(काष्ठा nvअगर_notअगरy_head_req_v0) अणु
					.head = i,
				       पूर्ण,
				       माप(काष्ठा nvअगर_notअगरy_head_req_v0),
				       माप(काष्ठा nvअगर_notअगरy_head_rep_v0),
				       &chan->vblank.notअगरy[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*******************************************************************************
 * software engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_sw_func
nv50_sw = अणु
	.chan_new = nv50_sw_chan_new,
	.sclass = अणु
		अणु nvkm_nvsw_new, अणु -1, -1, NVIF_CLASS_SW_NV50 पूर्ण पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv50_sw_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_sw **psw)
अणु
	वापस nvkm_sw_new_(&nv50_sw, device, type, inst, psw);
पूर्ण
