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
nv34_gr_chan = अणु
	.dtor = nv20_gr_chan_dtor,
	.init = nv20_gr_chan_init,
	.fini = nv20_gr_chan_fini,
पूर्ण;

अटल पूर्णांक
nv34_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv20_gr *gr = nv20_gr(base);
	काष्ठा nv20_gr_chan *chan;
	पूर्णांक ret, i;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv34_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fअगरoch->chid;
	*pobject = &chan->object;

	ret = nvkm_memory_new(gr->base.engine.subdev.device,
			      NVKM_MEM_TARGET_INST, 0x46dc, 16, true,
			      &chan->inst);
	अगर (ret)
		वापस ret;

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x0028, 0x00000001 | (chan->chid << 24));
	nvkm_wo32(chan->inst, 0x040c, 0x01000101);
	nvkm_wo32(chan->inst, 0x0420, 0x00000111);
	nvkm_wo32(chan->inst, 0x0424, 0x00000060);
	nvkm_wo32(chan->inst, 0x0440, 0x00000080);
	nvkm_wo32(chan->inst, 0x0444, 0xffff0000);
	nvkm_wo32(chan->inst, 0x0448, 0x00000001);
	nvkm_wo32(chan->inst, 0x045c, 0x44400000);
	nvkm_wo32(chan->inst, 0x0480, 0xffff0000);
	क्रम (i = 0x04d4; i < 0x04dc; i += 4)
		nvkm_wo32(chan->inst, i, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x04e0, 0x00011100);
	क्रम (i = 0x04fc; i < 0x053c; i += 4)
		nvkm_wo32(chan->inst, i, 0x07ff0000);
	nvkm_wo32(chan->inst, 0x0544, 0x4b7fffff);
	nvkm_wo32(chan->inst, 0x057c, 0x00000080);
	nvkm_wo32(chan->inst, 0x0580, 0x30201000);
	nvkm_wo32(chan->inst, 0x0584, 0x70605040);
	nvkm_wo32(chan->inst, 0x0588, 0xb8a89888);
	nvkm_wo32(chan->inst, 0x058c, 0xf8e8d8c8);
	nvkm_wo32(chan->inst, 0x05a0, 0xb0000000);
	क्रम (i = 0x05f0; i < 0x0630; i += 4)
		nvkm_wo32(chan->inst, i, 0x00010588);
	क्रम (i = 0x0630; i < 0x0670; i += 4)
		nvkm_wo32(chan->inst, i, 0x00030303);
	क्रम (i = 0x06b0; i < 0x06f0; i += 4)
		nvkm_wo32(chan->inst, i, 0x0008aae4);
	क्रम (i = 0x06f0; i < 0x0730; i += 4)
		nvkm_wo32(chan->inst, i, 0x01012000);
	क्रम (i = 0x0730; i < 0x0770; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080008);
	nvkm_wo32(chan->inst, 0x0850, 0x00040000);
	nvkm_wo32(chan->inst, 0x0854, 0x00010000);
	क्रम (i = 0x0858; i < 0x0868; i += 4)
		nvkm_wo32(chan->inst, i, 0x00040004);
	क्रम (i = 0x15ac; i <= 0x271c ; i += 16) अणु
		nvkm_wo32(chan->inst, i + 0, 0x10700ff9);
		nvkm_wo32(chan->inst, i + 4, 0x0436086c);
		nvkm_wo32(chan->inst, i + 8, 0x000c001b);
	पूर्ण
	क्रम (i = 0x274c; i < 0x275c; i += 4)
		nvkm_wo32(chan->inst, i, 0x0000ffff);
	nvkm_wo32(chan->inst, 0x2ae0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2e9c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2eb0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2edc, 0x40000000);
	nvkm_wo32(chan->inst, 0x2ee0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2ee4, 0x3f000000);
	nvkm_wo32(chan->inst, 0x2eec, 0x40000000);
	nvkm_wo32(chan->inst, 0x2ef0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x2ef8, 0xbf800000);
	nvkm_wo32(chan->inst, 0x2f00, 0xbf800000);
	nvkm_करोne(chan->inst);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_gr_func
nv34_gr = अणु
	.dtor = nv20_gr_dtor,
	.oneinit = nv20_gr_oneinit,
	.init = nv30_gr_init,
	.पूर्णांकr = nv20_gr_पूर्णांकr,
	.tile = nv20_gr_tile,
	.chan_new = nv34_gr_chan_new,
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
		अणु -1, -1, 0x009f, &nv04_gr_object पूर्ण, /* imageblit */
		अणु -1, -1, 0x0362, &nv04_gr_object पूर्ण, /* surf2d (nv30) */
		अणु -1, -1, 0x0389, &nv04_gr_object पूर्ण, /* sअगरm (nv30) */
		अणु -1, -1, 0x038a, &nv04_gr_object पूर्ण, /* अगरc (nv30) */
		अणु -1, -1, 0x039e, &nv04_gr_object पूर्ण, /* swzsurf (nv30) */
		अणु -1, -1, 0x0597, &nv04_gr_object पूर्ण, /* kelvin */
		अणु -1, -1, 0x0697, &nv04_gr_object पूर्ण, /* rankine */
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv34_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv20_gr_new_(&nv34_gr, device, type, inst, pgr);
पूर्ण
