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
nv25_gr_chan = अणु
	.dtor = nv20_gr_chan_dtor,
	.init = nv20_gr_chan_init,
	.fini = nv20_gr_chan_fini,
पूर्ण;

अटल पूर्णांक
nv25_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv20_gr *gr = nv20_gr(base);
	काष्ठा nv20_gr_chan *chan;
	पूर्णांक ret, i;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv25_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fअगरoch->chid;
	*pobject = &chan->object;

	ret = nvkm_memory_new(gr->base.engine.subdev.device,
			      NVKM_MEM_TARGET_INST, 0x3724, 16, true,
			      &chan->inst);
	अगर (ret)
		वापस ret;

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x0028, 0x00000001 | (chan->chid << 24));
	nvkm_wo32(chan->inst, 0x035c, 0xffff0000);
	nvkm_wo32(chan->inst, 0x03c0, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x03c4, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x049c, 0x00000101);
	nvkm_wo32(chan->inst, 0x04b0, 0x00000111);
	nvkm_wo32(chan->inst, 0x04c8, 0x00000080);
	nvkm_wo32(chan->inst, 0x04cc, 0xffff0000);
	nvkm_wo32(chan->inst, 0x04d0, 0x00000001);
	nvkm_wo32(chan->inst, 0x04e4, 0x44400000);
	nvkm_wo32(chan->inst, 0x04fc, 0x4b800000);
	क्रम (i = 0x0510; i <= 0x051c; i += 4)
		nvkm_wo32(chan->inst, i, 0x00030303);
	क्रम (i = 0x0530; i <= 0x053c; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080000);
	क्रम (i = 0x0548; i <= 0x0554; i += 4)
		nvkm_wo32(chan->inst, i, 0x01012000);
	क्रम (i = 0x0558; i <= 0x0564; i += 4)
		nvkm_wo32(chan->inst, i, 0x000105b8);
	क्रम (i = 0x0568; i <= 0x0574; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080008);
	क्रम (i = 0x0598; i <= 0x05d4; i += 4)
		nvkm_wo32(chan->inst, i, 0x07ff0000);
	nvkm_wo32(chan->inst, 0x05e0, 0x4b7fffff);
	nvkm_wo32(chan->inst, 0x0620, 0x00000080);
	nvkm_wo32(chan->inst, 0x0624, 0x30201000);
	nvkm_wo32(chan->inst, 0x0628, 0x70605040);
	nvkm_wo32(chan->inst, 0x062c, 0xb0a09080);
	nvkm_wo32(chan->inst, 0x0630, 0xf0e0d0c0);
	nvkm_wo32(chan->inst, 0x0664, 0x00000001);
	nvkm_wo32(chan->inst, 0x066c, 0x00004000);
	nvkm_wo32(chan->inst, 0x0678, 0x00000001);
	nvkm_wo32(chan->inst, 0x0680, 0x00040000);
	nvkm_wo32(chan->inst, 0x0684, 0x00010000);
	क्रम (i = 0x1b04; i <= 0x2374; i += 16) अणु
		nvkm_wo32(chan->inst, (i + 0), 0x10700ff9);
		nvkm_wo32(chan->inst, (i + 4), 0x0436086c);
		nvkm_wo32(chan->inst, (i + 8), 0x000c001b);
	पूर्ण
	nvkm_wo32(chan->inst, 0x2704, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2718, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2744, 0x40000000);
	nvkm_wo32(chan->inst, 0x2748, 0x3f800000);
	nvkm_wo32(chan->inst, 0x274c, 0x3f000000);
	nvkm_wo32(chan->inst, 0x2754, 0x40000000);
	nvkm_wo32(chan->inst, 0x2758, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2760, 0xbf800000);
	nvkm_wo32(chan->inst, 0x2768, 0xbf800000);
	nvkm_wo32(chan->inst, 0x308c, 0x000fe000);
	nvkm_wo32(chan->inst, 0x3108, 0x000003f8);
	nvkm_wo32(chan->inst, 0x3468, 0x002fe000);
	क्रम (i = 0x3484; i <= 0x34a0; i += 4)
		nvkm_wo32(chan->inst, i, 0x001c527c);
	nvkm_करोne(chan->inst);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_gr_func
nv25_gr = अणु
	.dtor = nv20_gr_dtor,
	.oneinit = nv20_gr_oneinit,
	.init = nv20_gr_init,
	.पूर्णांकr = nv20_gr_पूर्णांकr,
	.tile = nv20_gr_tile,
	.chan_new = nv25_gr_chan_new,
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
nv25_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv20_gr_new_(&nv25_gr, device, type, inst, pgr);
पूर्ण
