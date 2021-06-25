<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश "nv20.h"
#समावेश "regs.h"

#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>
#समावेश <engine/fअगरo/chan.h>

/*******************************************************************************
 * PGRAPH context
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_object_func
nv2a_gr_chan = अणु
	.dtor = nv20_gr_chan_dtor,
	.init = nv20_gr_chan_init,
	.fini = nv20_gr_chan_fini,
पूर्ण;

अटल पूर्णांक
nv2a_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv20_gr *gr = nv20_gr(base);
	काष्ठा nv20_gr_chan *chan;
	पूर्णांक ret, i;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv2a_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fअगरoch->chid;
	*pobject = &chan->object;

	ret = nvkm_memory_new(gr->base.engine.subdev.device,
			      NVKM_MEM_TARGET_INST, 0x36b0, 16, true,
			      &chan->inst);
	अगर (ret)
		वापस ret;

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x0000, 0x00000001 | (chan->chid << 24));
	nvkm_wo32(chan->inst, 0x033c, 0xffff0000);
	nvkm_wo32(chan->inst, 0x03a0, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x03a4, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x047c, 0x00000101);
	nvkm_wo32(chan->inst, 0x0490, 0x00000111);
	nvkm_wo32(chan->inst, 0x04a8, 0x44400000);
	क्रम (i = 0x04d4; i <= 0x04e0; i += 4)
		nvkm_wo32(chan->inst, i, 0x00030303);
	क्रम (i = 0x04f4; i <= 0x0500; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080000);
	क्रम (i = 0x050c; i <= 0x0518; i += 4)
		nvkm_wo32(chan->inst, i, 0x01012000);
	क्रम (i = 0x051c; i <= 0x0528; i += 4)
		nvkm_wo32(chan->inst, i, 0x000105b8);
	क्रम (i = 0x052c; i <= 0x0538; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080008);
	क्रम (i = 0x055c; i <= 0x0598; i += 4)
		nvkm_wo32(chan->inst, i, 0x07ff0000);
	nvkm_wo32(chan->inst, 0x05a4, 0x4b7fffff);
	nvkm_wo32(chan->inst, 0x05fc, 0x00000001);
	nvkm_wo32(chan->inst, 0x0604, 0x00004000);
	nvkm_wo32(chan->inst, 0x0610, 0x00000001);
	nvkm_wo32(chan->inst, 0x0618, 0x00040000);
	nvkm_wo32(chan->inst, 0x061c, 0x00010000);
	क्रम (i = 0x1a9c; i <= 0x22fc; i += 16) अणु /*XXX: check!! */
		nvkm_wo32(chan->inst, (i + 0), 0x10700ff9);
		nvkm_wo32(chan->inst, (i + 4), 0x0436086c);
		nvkm_wo32(chan->inst, (i + 8), 0x000c001b);
	पूर्ण
	nvkm_wo32(chan->inst, 0x269c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26b0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26dc, 0x40000000);
	nvkm_wo32(chan->inst, 0x26e0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26e4, 0x3f000000);
	nvkm_wo32(chan->inst, 0x26ec, 0x40000000);
	nvkm_wo32(chan->inst, 0x26f0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26f8, 0xbf800000);
	nvkm_wo32(chan->inst, 0x2700, 0xbf800000);
	nvkm_wo32(chan->inst, 0x3024, 0x000fe000);
	nvkm_wo32(chan->inst, 0x30a0, 0x000003f8);
	nvkm_wo32(chan->inst, 0x33fc, 0x002fe000);
	क्रम (i = 0x341c; i <= 0x3438; i += 4)
		nvkm_wo32(chan->inst, i, 0x001c527c);
	nvkm_करोne(chan->inst);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_gr_func
nv2a_gr = अणु
	.dtor = nv20_gr_dtor,
	.oneinit = nv20_gr_oneinit,
	.init = nv20_gr_init,
	.पूर्णांकr = nv20_gr_पूर्णांकr,
	.tile = nv20_gr_tile,
	.chan_new = nv2a_gr_chan_new,
	.sclass = अणु
		अणु -1, -1, 0x0012, &nv04_gr_object पूर्ण, /* beta1 */
		अणु -1, -1, 0x0019, &nv04_gr_object पूर्ण, /* clip */
		अणु -1, -1, 0x0030, &nv04_gr_object पूर्ण, /* null */
		अणु -1, -1, 0x0039, &nv04_gr_object पूर्ण, /* m2mf */
		अणु -1, -1, 0x0043, &nv04_gr_object पूर्ण, /* rop */
		अणु -1, -1, 0x0044, &nv04_gr_object पूर्ण, /* patt */
		अणु -1, -1, 0x004a, &nv04_gr_object पूर्ण, /* gdi */
		अणु -1, -1, 0x0062, &nv04_gr_object पूर्ण, /* surf2d */
		अणु -1, -1, 0x0072, &nv04_gr_object पूर्ण, /* beta4 */
		अणु -1, -1, 0x0089, &nv04_gr_object पूर्ण, /* sअगरm */
		अणु -1, -1, 0x008a, &nv04_gr_object पूर्ण, /* अगरc */
		अणु -1, -1, 0x0096, &nv04_gr_object पूर्ण, /* celcius */
		अणु -1, -1, 0x009e, &nv04_gr_object पूर्ण, /* swzsurf */
		अणु -1, -1, 0x009f, &nv04_gr_object पूर्ण, /* imageblit */
		अणु -1, -1, 0x0597, &nv04_gr_object पूर्ण, /* kelvin */
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv2a_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv20_gr_new_(&nv2a_gr, device, type, inst, pgr);
पूर्ण
