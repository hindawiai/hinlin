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
#समावेश "ram.h"

#समावेश <core/client.h>
#समावेश <core/क्रमागत.h>
#समावेश <engine/fअगरo.h>

अटल पूर्णांक
nv50_fb_ram_new(काष्ठा nvkm_fb *base, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nv50_fb *fb = nv50_fb(base);
	वापस fb->func->ram_new(&fb->base, pram);
पूर्ण

अटल स्थिर काष्ठा nvkm_क्रमागत vm_dispatch_subclients[] = अणु
	अणु 0x00000000, "GRCTX" पूर्ण,
	अणु 0x00000001, "NOTIFY" पूर्ण,
	अणु 0x00000002, "QUERY" पूर्ण,
	अणु 0x00000003, "COND" पूर्ण,
	अणु 0x00000004, "M2M_IN" पूर्ण,
	अणु 0x00000005, "M2M_OUT" पूर्ण,
	अणु 0x00000006, "M2M_NOTIFY" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत vm_ccache_subclients[] = अणु
	अणु 0x00000000, "CB" पूर्ण,
	अणु 0x00000001, "TIC" पूर्ण,
	अणु 0x00000002, "TSC" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत vm_prop_subclients[] = अणु
	अणु 0x00000000, "RT0" पूर्ण,
	अणु 0x00000001, "RT1" पूर्ण,
	अणु 0x00000002, "RT2" पूर्ण,
	अणु 0x00000003, "RT3" पूर्ण,
	अणु 0x00000004, "RT4" पूर्ण,
	अणु 0x00000005, "RT5" पूर्ण,
	अणु 0x00000006, "RT6" पूर्ण,
	अणु 0x00000007, "RT7" पूर्ण,
	अणु 0x00000008, "ZETA" पूर्ण,
	अणु 0x00000009, "LOCAL" पूर्ण,
	अणु 0x0000000a, "GLOBAL" पूर्ण,
	अणु 0x0000000b, "STACK" पूर्ण,
	अणु 0x0000000c, "DST2D" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत vm_pfअगरo_subclients[] = अणु
	अणु 0x00000000, "PUSHBUF" पूर्ण,
	अणु 0x00000001, "SEMAPHORE" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत vm_bar_subclients[] = अणु
	अणु 0x00000000, "FB" पूर्ण,
	अणु 0x00000001, "IN" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत vm_client[] = अणु
	अणु 0x00000000, "STRMOUT" पूर्ण,
	अणु 0x00000003, "DISPATCH", vm_dispatch_subclients पूर्ण,
	अणु 0x00000004, "PFIFO_WRITE" पूर्ण,
	अणु 0x00000005, "CCACHE", vm_ccache_subclients पूर्ण,
	अणु 0x00000006, "PMSPPP" पूर्ण,
	अणु 0x00000007, "CLIPID" पूर्ण,
	अणु 0x00000008, "PFIFO_READ" पूर्ण,
	अणु 0x00000009, "VFETCH" पूर्ण,
	अणु 0x0000000a, "TEXTURE" पूर्ण,
	अणु 0x0000000b, "PROP", vm_prop_subclients पूर्ण,
	अणु 0x0000000c, "PVP" पूर्ण,
	अणु 0x0000000d, "PBSP" पूर्ण,
	अणु 0x0000000e, "PCRYPT" पूर्ण,
	अणु 0x0000000f, "PCOUNTER" पूर्ण,
	अणु 0x00000011, "PDAEMON" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत vm_engine[] = अणु
	अणु 0x00000000, "PGRAPH" पूर्ण,
	अणु 0x00000001, "PVP" पूर्ण,
	अणु 0x00000004, "PEEPHOLE" पूर्ण,
	अणु 0x00000005, "PFIFO", vm_pfअगरo_subclients पूर्ण,
	अणु 0x00000006, "BAR", vm_bar_subclients पूर्ण,
	अणु 0x00000008, "PMSPPP" पूर्ण,
	अणु 0x00000008, "PMPEG" पूर्ण,
	अणु 0x00000009, "PBSP" पूर्ण,
	अणु 0x0000000a, "PCRYPT" पूर्ण,
	अणु 0x0000000b, "PCOUNTER" पूर्ण,
	अणु 0x0000000c, "SEMAPHORE_BG" पूर्ण,
	अणु 0x0000000d, "PCE0" पूर्ण,
	अणु 0x0000000e, "PMU" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत vm_fault[] = अणु
	अणु 0x00000000, "PT_NOT_PRESENT" पूर्ण,
	अणु 0x00000001, "PT_TOO_SHORT" पूर्ण,
	अणु 0x00000002, "PAGE_NOT_PRESENT" पूर्ण,
	अणु 0x00000003, "PAGE_SYSTEM_ONLY" पूर्ण,
	अणु 0x00000004, "PAGE_READ_ONLY" पूर्ण,
	अणु 0x00000006, "NULL_DMAOBJ" पूर्ण,
	अणु 0x00000007, "WRONG_MEMTYPE" पूर्ण,
	अणु 0x0000000b, "VRAM_LIMIT" पूर्ण,
	अणु 0x0000000f, "DMAOBJ_LIMIT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nv50_fb_पूर्णांकr(काष्ठा nvkm_fb *base)
अणु
	काष्ठा nv50_fb *fb = nv50_fb(base);
	काष्ठा nvkm_subdev *subdev = &fb->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fअगरo *fअगरo = device->fअगरo;
	काष्ठा nvkm_fअगरo_chan *chan;
	स्थिर काष्ठा nvkm_क्रमागत *en, *re, *cl, *sc;
	u32 trap[6], idx, inst;
	u8 st0, st1, st2, st3;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	idx = nvkm_rd32(device, 0x100c90);
	अगर (!(idx & 0x80000000))
		वापस;
	idx &= 0x00ffffff;

	क्रम (i = 0; i < 6; i++) अणु
		nvkm_wr32(device, 0x100c90, idx | i << 24);
		trap[i] = nvkm_rd32(device, 0x100c94);
	पूर्ण
	nvkm_wr32(device, 0x100c90, idx | 0x80000000);

	/* decode status bits पूर्णांकo something more useful */
	अगर (device->chipset  < 0xa3 ||
	    device->chipset == 0xaa || device->chipset == 0xac) अणु
		st0 = (trap[0] & 0x0000000f) >> 0;
		st1 = (trap[0] & 0x000000f0) >> 4;
		st2 = (trap[0] & 0x00000f00) >> 8;
		st3 = (trap[0] & 0x0000f000) >> 12;
	पूर्ण अन्यथा अणु
		st0 = (trap[0] & 0x000000ff) >> 0;
		st1 = (trap[0] & 0x0000ff00) >> 8;
		st2 = (trap[0] & 0x00ff0000) >> 16;
		st3 = (trap[0] & 0xff000000) >> 24;
	पूर्ण
	inst = ((trap[2] << 16) | trap[1]) << 12;

	en = nvkm_क्रमागत_find(vm_engine, st0);
	re = nvkm_क्रमागत_find(vm_fault , st1);
	cl = nvkm_क्रमागत_find(vm_client, st2);
	अगर      (cl && cl->data) sc = nvkm_क्रमागत_find(cl->data, st3);
	अन्यथा अगर (en && en->data) sc = nvkm_क्रमागत_find(en->data, st3);
	अन्यथा                     sc = शून्य;

	chan = nvkm_fअगरo_chan_inst(fअगरo, inst, &flags);
	nvkm_error(subdev, "trapped %s at %02x%04x%04x on channel %d [%08x %s] "
			   "engine %02x [%s] client %02x [%s] "
			   "subclient %02x [%s] reason %08x [%s]\n",
		   (trap[5] & 0x00000100) ? "read" : "write",
		   trap[5] & 0xff, trap[4] & 0xffff, trap[3] & 0xffff,
		   chan ? chan->chid : -1, inst,
		   chan ? chan->object.client->name : "unknown",
		   st0, en ? en->name : "",
		   st2, cl ? cl->name : "", st3, sc ? sc->name : "",
		   st1, re ? re->name : "");
	nvkm_fअगरo_chan_put(fअगरo, flags, &chan);
पूर्ण

अटल पूर्णांक
nv50_fb_oneinit(काष्ठा nvkm_fb *base)
अणु
	काष्ठा nv50_fb *fb = nv50_fb(base);
	काष्ठा nvkm_device *device = fb->base.subdev.device;

	fb->r100c08_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (fb->r100c08_page) अणु
		fb->r100c08 = dma_map_page(device->dev, fb->r100c08_page, 0,
					   PAGE_SIZE, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(device->dev, fb->r100c08))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nv50_fb_init(काष्ठा nvkm_fb *base)
अणु
	काष्ठा nv50_fb *fb = nv50_fb(base);
	काष्ठा nvkm_device *device = fb->base.subdev.device;

	/* Not a clue what this is exactly.  Without poपूर्णांकing it at a
	 * scratch page, VRAM->GART blits with M2MF (as in DDX DFS)
	 * cause IOMMU "read from address 0" errors (rh#561267)
	 */
	nvkm_wr32(device, 0x100c08, fb->r100c08 >> 8);

	/* This is needed to get meaningful inक्रमmation from 100c90
	 * on traps. No idea what these values mean exactly. */
	nvkm_wr32(device, 0x100c90, fb->func->trap);
पूर्ण

अटल u32
nv50_fb_tags(काष्ठा nvkm_fb *base)
अणु
	काष्ठा nv50_fb *fb = nv50_fb(base);
	अगर (fb->func->tags)
		वापस fb->func->tags(&fb->base);
	वापस 0;
पूर्ण

अटल व्योम *
nv50_fb_dtor(काष्ठा nvkm_fb *base)
अणु
	काष्ठा nv50_fb *fb = nv50_fb(base);
	काष्ठा nvkm_device *device = fb->base.subdev.device;

	अगर (fb->r100c08_page) अणु
		dma_unmap_page(device->dev, fb->r100c08, PAGE_SIZE,
			       DMA_BIसूचीECTIONAL);
		__मुक्त_page(fb->r100c08_page);
	पूर्ण

	वापस fb;
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
nv50_fb_ = अणु
	.dtor = nv50_fb_dtor,
	.tags = nv50_fb_tags,
	.oneinit = nv50_fb_oneinit,
	.init = nv50_fb_init,
	.पूर्णांकr = nv50_fb_पूर्णांकr,
	.ram_new = nv50_fb_ram_new,
पूर्ण;

पूर्णांक
nv50_fb_new_(स्थिर काष्ठा nv50_fb_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	काष्ठा nv50_fb *fb;

	अगर (!(fb = kzalloc(माप(*fb), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_fb_ctor(&nv50_fb_, device, type, inst, &fb->base);
	fb->func = func;
	*pfb = &fb->base;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_fb_func
nv50_fb = अणु
	.ram_new = nv50_ram_new,
	.tags = nv20_fb_tags,
	.trap = 0x000707ff,
पूर्ण;

पूर्णांक
nv50_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस nv50_fb_new_(&nv50_fb, device, type, inst, pfb);
पूर्ण
