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
nv35_gr_chan = अणु
	.dtor = nv20_gr_chan_dtor,
	.init = nv20_gr_chan_init,
	.fini = nv20_gr_chan_fini,
पूर्ण;

अटल पूर्णांक
nv35_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv20_gr *gr = nv20_gr(base);
	काष्ठा nv20_gr_chan *chan;
	पूर्णांक ret, i;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv35_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fअगरoch->chid;
	*pobject = &chan->object;

	ret = nvkm_memory_new(gr->base.engine.subdev.device,
			      NVKM_MEM_TARGET_INST, 0x577c, 16, true,
			      &chan->inst);
	अगर (ret)
		वापस ret;

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x0028, 0x00000001 | (chan->chid << 24));
	nvkm_wo32(chan->inst, 0x040c, 0x00000101);
	nvkm_wo32(chan->inst, 0x0420, 0x00000111);
	nvkm_wo32(chan->inst, 0x0424, 0x00000060);
	nvkm_wo32(chan->inst, 0x0440, 0x00000080);
	nvkm_wo32(chan->inst, 0x0444, 0xffff0000);
	nvkm_wo32(chan->inst, 0x0448, 0x00000001);
	nvkm_wo32(chan->inst, 0x045c, 0x44400000);
	nvkm_wo32(chan->inst, 0x0488, 0xffff0000);
	क्रम (i = 0x04dc; i < 0x04e4; i += 4)
		nvkm_wo32(chan->inst, i, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x04e8, 0x00011100);
	क्रम (i = 0x0504; i < 0x0544; i += 4)
		nvkm_wo32(chan->inst, i, 0x07ff0000);
	nvkm_wo32(chan->inst, 0x054c, 0x4b7fffff);
	nvkm_wo32(chan->inst, 0x0588, 0x00000080);
	nvkm_wo32(chan->inst, 0x058c, 0x30201000);
	nvkm_wo32(chan->inst, 0x0590, 0x70605040);
	nvkm_wo32(chan->inst, 0x0594, 0xb8a89888);
	nvkm_wo32(chan->inst, 0x0598, 0xf8e8d8c8);
	nvkm_wo32(chan->inst, 0x05ac, 0xb0000000);
	क्रम (i = 0x0604; i < 0x0644; i += 4)
		nvkm_wo32(chan->inst, i, 0x00010588);
	क्रम (i = 0x0644; i < 0x0684; i += 4)
		nvkm_wo32(chan->inst, i, 0x00030303);
	क्रम (i = 0x06c4; i < 0x0704; i += 4)
		nvkm_wo32(chan->inst, i, 0x0008aae4);
	क्रम (i = 0x0704; i < 0x0744; i += 4)
		nvkm_wo32(chan->inst, i, 0x01012000);
	क्रम (i = 0x0744; i < 0x0784; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080008);
	nvkm_wo32(chan->inst, 0x0860, 0x00040000);
	nvkm_wo32(chan->inst, 0x0864, 0x00010000);
	क्रम (i = 0x0868; i < 0x0878; i += 4)
		nvkm_wo32(chan->inst, i, 0x00040004);
	क्रम (i = 0x1f1c; i <= 0x308c ; i += 16) अणु
		nvkm_wo32(chan->inst, i + 0, 0x10700ff9);
		nvkm_wo32(chan->inst, i + 4, 0x0436086c);
		nvkm_wo32(chan->inst, i + 8, 0x000c001b);
	पूर्ण
	क्रम (i = 0x30bc; i < 0x30cc; i += 4)
		nvkm_wo32(chan->inst, i, 0x0000ffff);
	nvkm_wo32(chan->inst, 0x3450, 0x3f800000);
	nvkm_wo32(chan->inst, 0x380c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x3820, 0x3f800000);
	nvkm_wo32(chan->inst, 0x384c, 0x40000000);
	nvkm_wo32(chan->inst, 0x3850, 0x3f800000);
	nvkm_wo32(chan->inst, 0x3854, 0x3f000000);
	nvkm_wo32(chan->inst, 0x385c, 0x40000000);
	nvkm_wo32(chan->inst, 0x3860, 0x3f800000);
	nvkm_wo32(chan->inst, 0x3868, 0xbf800000);
	nvkm_wo32(chan->inst, 0x3870, 0xbf800000);
	nvkm_करोne(chan->inst);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_gr_func
nv35_gr = अणु
	.dtor = nv20_gr_dtor,
	.oneinit = nv20_gr_oneinit,
	.init = nv30_gr_init,
	.पूर्णांकr = nv20_gr_पूर्णांकr,
	.tile = nv20_gr_tile,
	.chan_new = nv35_gr_chan_new,
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
		अणु -1, -1, 0x0497, &nv04_gr_object पूर्ण, /* rankine */
		अणु -1, -1, 0x0597, &nv04_gr_object पूर्ण, /* kelvin */
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv35_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv20_gr_new_(&nv35_gr, device, type, inst, pgr);
पूर्ण
