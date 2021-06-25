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
#समावेश "nv40.h"
#समावेश "regs.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/fअगरo.h>

u64
nv40_gr_units(काष्ठा nvkm_gr *gr)
अणु
	वापस nvkm_rd32(gr->engine.subdev.device, 0x1540);
पूर्ण

/*******************************************************************************
 * Graphics object classes
 ******************************************************************************/

अटल पूर्णांक
nv40_gr_object_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		    पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	पूर्णांक ret = nvkm_gpuobj_new(object->engine->subdev.device, 20, align,
				  false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->oclass);
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
#अगर_घोषित __BIG_ENDIAN
		nvkm_mo32(*pgpuobj, 0x08, 0x01000000, 0x01000000);
#पूर्ण_अगर
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा nvkm_object_func
nv40_gr_object = अणु
	.bind = nv40_gr_object_bind,
पूर्ण;

/*******************************************************************************
 * PGRAPH context
 ******************************************************************************/

अटल पूर्णांक
nv40_gr_chan_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		  पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nv40_gr_chan *chan = nv40_gr_chan(object);
	काष्ठा nv40_gr *gr = chan->gr;
	पूर्णांक ret = nvkm_gpuobj_new(gr->base.engine.subdev.device, gr->size,
				  align, true, parent, pgpuobj);
	अगर (ret == 0) अणु
		chan->inst = (*pgpuobj)->addr;
		nvkm_kmap(*pgpuobj);
		nv40_grctx_fill(gr->base.engine.subdev.device, *pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00000, chan->inst >> 4);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nv40_gr_chan_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nv40_gr_chan *chan = nv40_gr_chan(object);
	काष्ठा nv40_gr *gr = chan->gr;
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 inst = 0x01000000 | chan->inst >> 4;
	पूर्णांक ret = 0;

	nvkm_mask(device, 0x400720, 0x00000001, 0x00000000);

	अगर (nvkm_rd32(device, 0x40032c) == inst) अणु
		अगर (suspend) अणु
			nvkm_wr32(device, 0x400720, 0x00000000);
			nvkm_wr32(device, 0x400784, inst);
			nvkm_mask(device, 0x400310, 0x00000020, 0x00000020);
			nvkm_mask(device, 0x400304, 0x00000001, 0x00000001);
			अगर (nvkm_msec(device, 2000,
				अगर (!(nvkm_rd32(device, 0x400300) & 0x00000001))
					अवरोध;
			) < 0) अणु
				u32 insn = nvkm_rd32(device, 0x400308);
				nvkm_warn(subdev, "ctxprog timeout %08x\n", insn);
				ret = -EBUSY;
			पूर्ण
		पूर्ण

		nvkm_mask(device, 0x40032c, 0x01000000, 0x00000000);
	पूर्ण

	अगर (nvkm_rd32(device, 0x400330) == inst)
		nvkm_mask(device, 0x400330, 0x01000000, 0x00000000);

	nvkm_mask(device, 0x400720, 0x00000001, 0x00000001);
	वापस ret;
पूर्ण

अटल व्योम *
nv40_gr_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv40_gr_chan *chan = nv40_gr_chan(object);
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chan->gr->base.engine.lock, flags);
	list_del(&chan->head);
	spin_unlock_irqrestore(&chan->gr->base.engine.lock, flags);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv40_gr_chan = अणु
	.dtor = nv40_gr_chan_dtor,
	.fini = nv40_gr_chan_fini,
	.bind = nv40_gr_chan_bind,
पूर्ण;

पूर्णांक
nv40_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv40_gr *gr = nv40_gr(base);
	काष्ठा nv40_gr_chan *chan;
	अचिन्हित दीर्घ flags;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv40_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->fअगरo = fअगरoch;
	*pobject = &chan->object;

	spin_lock_irqsave(&chan->gr->base.engine.lock, flags);
	list_add(&chan->head, &gr->chan);
	spin_unlock_irqrestore(&chan->gr->base.engine.lock, flags);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल व्योम
nv40_gr_tile(काष्ठा nvkm_gr *base, पूर्णांक i, काष्ठा nvkm_fb_tile *tile)
अणु
	काष्ठा nv40_gr *gr = nv40_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nvkm_fअगरo *fअगरo = device->fअगरo;
	अचिन्हित दीर्घ flags;

	nvkm_fअगरo_छोड़ो(fअगरo, &flags);
	nv04_gr_idle(&gr->base);

	चयन (device->chipset) अणु
	हाल 0x40:
	हाल 0x41:
	हाल 0x42:
	हाल 0x43:
	हाल 0x45:
		nvkm_wr32(device, NV20_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV20_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV20_PGRAPH_TILE(i), tile->addr);
		nvkm_wr32(device, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nvkm_wr32(device, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nvkm_wr32(device, NV40_PGRAPH_TILE1(i), tile->addr);
		चयन (device->chipset) अणु
		हाल 0x40:
		हाल 0x45:
			nvkm_wr32(device, NV20_PGRAPH_ZCOMP(i), tile->zcomp);
			nvkm_wr32(device, NV40_PGRAPH_ZCOMP1(i), tile->zcomp);
			अवरोध;
		हाल 0x41:
		हाल 0x42:
		हाल 0x43:
			nvkm_wr32(device, NV41_PGRAPH_ZCOMP0(i), tile->zcomp);
			nvkm_wr32(device, NV41_PGRAPH_ZCOMP1(i), tile->zcomp);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x47:
	हाल 0x49:
	हाल 0x4b:
		nvkm_wr32(device, NV47_PGRAPH_TSIZE(i), tile->pitch);
		nvkm_wr32(device, NV47_PGRAPH_TLIMIT(i), tile->limit);
		nvkm_wr32(device, NV47_PGRAPH_TILE(i), tile->addr);
		nvkm_wr32(device, NV40_PGRAPH_TSIZE1(i), tile->pitch);
		nvkm_wr32(device, NV40_PGRAPH_TLIMIT1(i), tile->limit);
		nvkm_wr32(device, NV40_PGRAPH_TILE1(i), tile->addr);
		nvkm_wr32(device, NV47_PGRAPH_ZCOMP0(i), tile->zcomp);
		nvkm_wr32(device, NV47_PGRAPH_ZCOMP1(i), tile->zcomp);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	nvkm_fअगरo_start(fअगरo, &flags);
पूर्ण

व्योम
nv40_gr_पूर्णांकr(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv40_gr *gr = nv40_gr(base);
	काष्ठा nv40_gr_chan *temp, *chan = शून्य;
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, NV03_PGRAPH_INTR);
	u32 nsource = nvkm_rd32(device, NV03_PGRAPH_NSOURCE);
	u32 nstatus = nvkm_rd32(device, NV03_PGRAPH_NSTATUS);
	u32 inst = nvkm_rd32(device, 0x40032c) & 0x000fffff;
	u32 addr = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_ADDR);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nvkm_rd32(device, NV04_PGRAPH_TRAPPED_DATA);
	u32 class = nvkm_rd32(device, 0x400160 + subc * 4) & 0xffff;
	u32 show = stat;
	अक्षर msg[128], src[128], sta[128];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gr->base.engine.lock, flags);
	list_क्रम_each_entry(temp, &gr->chan, head) अणु
		अगर (temp->inst >> 4 == inst) अणु
			chan = temp;
			list_del(&chan->head);
			list_add(&chan->head, &gr->chan);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stat & NV_PGRAPH_INTR_ERROR) अणु
		अगर (nsource & NV03_PGRAPH_NSOURCE_DMA_VTX_PROTECTION) अणु
			nvkm_mask(device, 0x402000, 0, 0);
		पूर्ण
	पूर्ण

	nvkm_wr32(device, NV03_PGRAPH_INTR, stat);
	nvkm_wr32(device, NV04_PGRAPH_FIFO, 0x00000001);

	अगर (show) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), nv10_gr_पूर्णांकr_name, show);
		nvkm_snprपूर्णांकbf(src, माप(src), nv04_gr_nsource, nsource);
		nvkm_snprपूर्णांकbf(sta, माप(sta), nv10_gr_nstatus, nstatus);
		nvkm_error(subdev, "intr %08x [%s] nsource %08x [%s] "
				   "nstatus %08x [%s] ch %d [%08x %s] subc %d "
				   "class %04x mthd %04x data %08x\n",
			   show, msg, nsource, src, nstatus, sta,
			   chan ? chan->fअगरo->chid : -1, inst << 4,
			   chan ? chan->fअगरo->object.client->name : "unknown",
			   subc, class, mthd, data);
	पूर्ण

	spin_unlock_irqrestore(&gr->base.engine.lock, flags);
पूर्ण

पूर्णांक
nv40_gr_init(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv40_gr *gr = nv40_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक ret, i, j;
	u32 vramsz;

	/* generate and upload context program */
	ret = nv40_grctx_init(device, &gr->size);
	अगर (ret)
		वापस ret;

	/* No context present currently */
	nvkm_wr32(device, NV40_PGRAPH_CTXCTL_CUR, 0x00000000);

	nvkm_wr32(device, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nvkm_wr32(device, NV40_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_1, 0x401287c0);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0xe0de8055);
	nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x00008000);
	nvkm_wr32(device, NV04_PGRAPH_LIMIT_VIOL_PIX, 0x00be3c5f);

	nvkm_wr32(device, NV10_PGRAPH_CTX_CONTROL, 0x10010100);
	nvkm_wr32(device, NV10_PGRAPH_STATE      , 0xFFFFFFFF);

	j = nvkm_rd32(device, 0x1540) & 0xff;
	अगर (j) अणु
		क्रम (i = 0; !(j & 1); j >>= 1, i++)
			;
		nvkm_wr32(device, 0x405000, i);
	पूर्ण

	अगर (device->chipset == 0x40) अणु
		nvkm_wr32(device, 0x4009b0, 0x83280fff);
		nvkm_wr32(device, 0x4009b4, 0x000000a0);
	पूर्ण अन्यथा अणु
		nvkm_wr32(device, 0x400820, 0x83280eff);
		nvkm_wr32(device, 0x400824, 0x000000a0);
	पूर्ण

	चयन (device->chipset) अणु
	हाल 0x40:
	हाल 0x45:
		nvkm_wr32(device, 0x4009b8, 0x0078e366);
		nvkm_wr32(device, 0x4009bc, 0x0000014c);
		अवरोध;
	हाल 0x41:
	हाल 0x42: /* pciid also 0x00Cx */
	/* हाल 0x0120: XXX (pciid) */
		nvkm_wr32(device, 0x400828, 0x007596ff);
		nvkm_wr32(device, 0x40082c, 0x00000108);
		अवरोध;
	हाल 0x43:
		nvkm_wr32(device, 0x400828, 0x0072cb77);
		nvkm_wr32(device, 0x40082c, 0x00000108);
		अवरोध;
	हाल 0x44:
	हाल 0x46: /* G72 */
	हाल 0x4a:
	हाल 0x4c: /* G7x-based C51 */
	हाल 0x4e:
		nvkm_wr32(device, 0x400860, 0);
		nvkm_wr32(device, 0x400864, 0);
		अवरोध;
	हाल 0x47: /* G70 */
	हाल 0x49: /* G71 */
	हाल 0x4b: /* G73 */
		nvkm_wr32(device, 0x400828, 0x07830610);
		nvkm_wr32(device, 0x40082c, 0x0000016A);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	nvkm_wr32(device, 0x400b38, 0x2ffff800);
	nvkm_wr32(device, 0x400b3c, 0x00006000);

	/* Tiling related stuff. */
	चयन (device->chipset) अणु
	हाल 0x44:
	हाल 0x4a:
		nvkm_wr32(device, 0x400bc4, 0x1003d888);
		nvkm_wr32(device, 0x400bbc, 0xb7a7b500);
		अवरोध;
	हाल 0x46:
		nvkm_wr32(device, 0x400bc4, 0x0000e024);
		nvkm_wr32(device, 0x400bbc, 0xb7a7b520);
		अवरोध;
	हाल 0x4c:
	हाल 0x4e:
	हाल 0x67:
		nvkm_wr32(device, 0x400bc4, 0x1003d888);
		nvkm_wr32(device, 0x400bbc, 0xb7a7b540);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* begin RAM config */
	vramsz = device->func->resource_size(device, 1) - 1;
	चयन (device->chipset) अणु
	हाल 0x40:
		nvkm_wr32(device, 0x4009A4, nvkm_rd32(device, 0x100200));
		nvkm_wr32(device, 0x4009A8, nvkm_rd32(device, 0x100204));
		nvkm_wr32(device, 0x4069A4, nvkm_rd32(device, 0x100200));
		nvkm_wr32(device, 0x4069A8, nvkm_rd32(device, 0x100204));
		nvkm_wr32(device, 0x400820, 0);
		nvkm_wr32(device, 0x400824, 0);
		nvkm_wr32(device, 0x400864, vramsz);
		nvkm_wr32(device, 0x400868, vramsz);
		अवरोध;
	शेष:
		चयन (device->chipset) अणु
		हाल 0x41:
		हाल 0x42:
		हाल 0x43:
		हाल 0x45:
		हाल 0x4e:
		हाल 0x44:
		हाल 0x4a:
			nvkm_wr32(device, 0x4009F0, nvkm_rd32(device, 0x100200));
			nvkm_wr32(device, 0x4009F4, nvkm_rd32(device, 0x100204));
			अवरोध;
		शेष:
			nvkm_wr32(device, 0x400DF0, nvkm_rd32(device, 0x100200));
			nvkm_wr32(device, 0x400DF4, nvkm_rd32(device, 0x100204));
			अवरोध;
		पूर्ण
		nvkm_wr32(device, 0x4069F0, nvkm_rd32(device, 0x100200));
		nvkm_wr32(device, 0x4069F4, nvkm_rd32(device, 0x100204));
		nvkm_wr32(device, 0x400840, 0);
		nvkm_wr32(device, 0x400844, 0);
		nvkm_wr32(device, 0x4008A0, vramsz);
		nvkm_wr32(device, 0x4008A4, vramsz);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nv40_gr_new_(स्थिर काष्ठा nvkm_gr_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	काष्ठा nv40_gr *gr;

	अगर (!(gr = kzalloc(माप(*gr), GFP_KERNEL)))
		वापस -ENOMEM;
	*pgr = &gr->base;
	INIT_LIST_HEAD(&gr->chan);

	वापस nvkm_gr_ctor(func, device, type, inst, true, &gr->base);
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
nv40_gr = अणु
	.init = nv40_gr_init,
	.पूर्णांकr = nv40_gr_पूर्णांकr,
	.tile = nv40_gr_tile,
	.units = nv40_gr_units,
	.chan_new = nv40_gr_chan_new,
	.sclass = अणु
		अणु -1, -1, 0x0012, &nv40_gr_object पूर्ण, /* beta1 */
		अणु -1, -1, 0x0019, &nv40_gr_object पूर्ण, /* clip */
		अणु -1, -1, 0x0030, &nv40_gr_object पूर्ण, /* null */
		अणु -1, -1, 0x0039, &nv40_gr_object पूर्ण, /* m2mf */
		अणु -1, -1, 0x0043, &nv40_gr_object पूर्ण, /* rop */
		अणु -1, -1, 0x0044, &nv40_gr_object पूर्ण, /* patt */
		अणु -1, -1, 0x004a, &nv40_gr_object पूर्ण, /* gdi */
		अणु -1, -1, 0x0062, &nv40_gr_object पूर्ण, /* surf2d */
		अणु -1, -1, 0x0072, &nv40_gr_object पूर्ण, /* beta4 */
		अणु -1, -1, 0x0089, &nv40_gr_object पूर्ण, /* sअगरm */
		अणु -1, -1, 0x008a, &nv40_gr_object पूर्ण, /* अगरc */
		अणु -1, -1, 0x009f, &nv40_gr_object पूर्ण, /* imageblit */
		अणु -1, -1, 0x3062, &nv40_gr_object पूर्ण, /* surf2d (nv40) */
		अणु -1, -1, 0x3089, &nv40_gr_object पूर्ण, /* sअगरm (nv40) */
		अणु -1, -1, 0x309e, &nv40_gr_object पूर्ण, /* swzsurf (nv40) */
		अणु -1, -1, 0x4097, &nv40_gr_object पूर्ण, /* curie */
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv40_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv40_gr_new_(&nv40_gr, device, type, inst, pgr);
पूर्ण
