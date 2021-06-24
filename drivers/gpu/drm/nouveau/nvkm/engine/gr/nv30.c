<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश "nv20.h"
#समावेश "regs.h"

#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>
#समावेश <engine/fअगरo/chan.h>
#समावेश <subdev/fb.h>

/*******************************************************************************
 * PGRAPH context
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_object_func
nv30_gr_chan = अणु
	.dtor = nv20_gr_chan_dtor,
	.init = nv20_gr_chan_init,
	.fini = nv20_gr_chan_fini,
पूर्ण;

अटल पूर्णांक
nv30_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv20_gr *gr = nv20_gr(base);
	काष्ठा nv20_gr_chan *chan;
	पूर्णांक ret, i;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv30_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->chid = fअगरoch->chid;
	*pobject = &chan->object;

	ret = nvkm_memory_new(gr->base.engine.subdev.device,
			      NVKM_MEM_TARGET_INST, 0x5f48, 16, true,
			      &chan->inst);
	अगर (ret)
		वापस ret;

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x0028, 0x00000001 | (chan->chid << 24));
	nvkm_wo32(chan->inst, 0x0410, 0x00000101);
	nvkm_wo32(chan->inst, 0x0424, 0x00000111);
	nvkm_wo32(chan->inst, 0x0428, 0x00000060);
	nvkm_wo32(chan->inst, 0x0444, 0x00000080);
	nvkm_wo32(chan->inst, 0x0448, 0xffff0000);
	nvkm_wo32(chan->inst, 0x044c, 0x00000001);
	nvkm_wo32(chan->inst, 0x0460, 0x44400000);
	nvkm_wo32(chan->inst, 0x048c, 0xffff0000);
	क्रम (i = 0x04e0; i < 0x04e8; i += 4)
		nvkm_wo32(chan->inst, i, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x04ec, 0x00011100);
	क्रम (i = 0x0508; i < 0x0548; i += 4)
		nvkm_wo32(chan->inst, i, 0x07ff0000);
	nvkm_wo32(chan->inst, 0x0550, 0x4b7fffff);
	nvkm_wo32(chan->inst, 0x058c, 0x00000080);
	nvkm_wo32(chan->inst, 0x0590, 0x30201000);
	nvkm_wo32(chan->inst, 0x0594, 0x70605040);
	nvkm_wo32(chan->inst, 0x0598, 0xb8a89888);
	nvkm_wo32(chan->inst, 0x059c, 0xf8e8d8c8);
	nvkm_wo32(chan->inst, 0x05b0, 0xb0000000);
	क्रम (i = 0x0600; i < 0x0640; i += 4)
		nvkm_wo32(chan->inst, i, 0x00010588);
	क्रम (i = 0x0640; i < 0x0680; i += 4)
		nvkm_wo32(chan->inst, i, 0x00030303);
	क्रम (i = 0x06c0; i < 0x0700; i += 4)
		nvkm_wo32(chan->inst, i, 0x0008aae4);
	क्रम (i = 0x0700; i < 0x0740; i += 4)
		nvkm_wo32(chan->inst, i, 0x01012000);
	क्रम (i = 0x0740; i < 0x0780; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080008);
	nvkm_wo32(chan->inst, 0x085c, 0x00040000);
	nvkm_wo32(chan->inst, 0x0860, 0x00010000);
	क्रम (i = 0x0864; i < 0x0874; i += 4)
		nvkm_wo32(chan->inst, i, 0x00040004);
	क्रम (i = 0x1f18; i <= 0x3088 ; i += 16) अणु
		nvkm_wo32(chan->inst, i + 0, 0x10700ff9);
		nvkm_wo32(chan->inst, i + 4, 0x0436086c);
		nvkm_wo32(chan->inst, i + 8, 0x000c001b);
	पूर्ण
	क्रम (i = 0x30b8; i < 0x30c8; i += 4)
		nvkm_wo32(chan->inst, i, 0x0000ffff);
	nvkm_wo32(chan->inst, 0x344c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x3808, 0x3f800000);
	nvkm_wo32(chan->inst, 0x381c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x3848, 0x40000000);
	nvkm_wo32(chan->inst, 0x384c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x3850, 0x3f000000);
	nvkm_wo32(chan->inst, 0x3858, 0x40000000);
	nvkm_wo32(chan->inst, 0x385c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x3864, 0xbf800000);
	nvkm_wo32(chan->inst, 0x386c, 0xbf800000);
	nvkm_करोne(chan->inst);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

पूर्णांक
nv30_gr_init(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv20_gr *gr = nv20_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, NV20_PGRAPH_CHANNEL_CTX_TABLE,
			  nvkm_memory_addr(gr->ctxtab) >> 4);

	nvkm_wr32(device, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nvkm_wr32(device, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_1, 0x401287c0);
	nvkm_wr32(device, 0x400890, 0x01b463ff);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0xf2de0475);
	nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x00008000);
	nvkm_wr32(device, NV04_PGRAPH_LIMIT_VIOL_PIX, 0xf04bdff6);
	nvkm_wr32(device, 0x400B80, 0x1003d888);
	nvkm_wr32(device, 0x400B84, 0x0c000000);
	nvkm_wr32(device, 0x400098, 0x00000000);
	nvkm_wr32(device, 0x40009C, 0x0005ad00);
	nvkm_wr32(device, 0x400B88, 0x62ff00ff); /* suspiciously like PGRAPH_DEBUG_2 */
	nvkm_wr32(device, 0x4000a0, 0x00000000);
	nvkm_wr32(device, 0x4000a4, 0x00000008);
	nvkm_wr32(device, 0x4008a8, 0xb784a400);
	nvkm_wr32(device, 0x400ba0, 0x002f8685);
	nvkm_wr32(device, 0x400ba4, 0x00231f3f);
	nvkm_wr32(device, 0x4008a4, 0x40000020);

	अगर (device->chipset == 0x34) अणु
		nvkm_wr32(device, NV10_PGRAPH_RDI_INDEX, 0x00EA0004);
		nvkm_wr32(device, NV10_PGRAPH_RDI_DATA , 0x00200201);
		nvkm_wr32(device, NV10_PGRAPH_RDI_INDEX, 0x00EA0008);
		nvkm_wr32(device, NV10_PGRAPH_RDI_DATA , 0x00000008);
		nvkm_wr32(device, NV10_PGRAPH_RDI_INDEX, 0x00EA0000);
		nvkm_wr32(device, NV10_PGRAPH_RDI_DATA , 0x00000032);
		nvkm_wr32(device, NV10_PGRAPH_RDI_INDEX, 0x00E00004);
		nvkm_wr32(device, NV10_PGRAPH_RDI_DATA , 0x00000002);
	पूर्ण

	nvkm_wr32(device, 0x4000c0, 0x00000016);

	nvkm_wr32(device, NV10_PGRAPH_CTX_CONTROL, 0x10000100);
	nvkm_wr32(device, NV10_PGRAPH_STATE      , 0xFFFFFFFF);
	nvkm_wr32(device, 0x0040075c             , 0x00000001);

	/* begin RAM config */
	/* vramsz = pci_resource_len(gr->dev->pdev, 1) - 1; */
	nvkm_wr32(device, 0x4009A4, nvkm_rd32(device, 0x100200));
	nvkm_wr32(device, 0x4009A8, nvkm_rd32(device, 0x100204));
	अगर (device->chipset != 0x34) अणु
		nvkm_wr32(device, 0x400750, 0x00EA0000);
		nvkm_wr32(device, 0x400754, nvkm_rd32(device, 0x100200));
		nvkm_wr32(device, 0x400750, 0x00EA0004);
		nvkm_wr32(device, 0x400754, nvkm_rd32(device, 0x100204));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
nv30_gr = अणु
	.dtor = nv20_gr_dtor,
	.oneinit = nv20_gr_oneinit,
	.init = nv30_gr_init,
	.पूर्णांकr = nv20_gr_पूर्णांकr,
	.tile = nv20_gr_tile,
	.chan_new = nv30_gr_chan_new,
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
		अणु -1, -1, 0x0397, &nv04_gr_object पूर्ण, /* rankine */
		अणु -1, -1, 0x0597, &nv04_gr_object पूर्ण, /* kelvin */
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv30_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv20_gr_new_(&nv30_gr, device, type, inst, pgr);
पूर्ण
