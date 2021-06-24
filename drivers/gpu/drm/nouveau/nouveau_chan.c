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
#समावेश <nvअगर/push006c.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/cl006b.h>
#समावेश <nvअगर/cl506f.h>
#समावेश <nvअगर/cl906f.h>
#समावेश <nvअगर/cla06f.h>
#समावेश <nvअगर/clc36f.h>
#समावेश <nvअगर/ioctl.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_bo.h"
#समावेश "nouveau_chan.h"
#समावेश "nouveau_fence.h"
#समावेश "nouveau_abi16.h"
#समावेश "nouveau_vmm.h"
#समावेश "nouveau_svm.h"

MODULE_PARM_DESC(vram_pushbuf, "Create DMA push buffers in VRAM");
पूर्णांक nouveau_vram_pushbuf;
module_param_named(vram_pushbuf, nouveau_vram_pushbuf, पूर्णांक, 0400);

अटल पूर्णांक
nouveau_channel_समाप्तed(काष्ठा nvअगर_notअगरy *ntfy)
अणु
	काष्ठा nouveau_channel *chan = container_of(ntfy, typeof(*chan), समाप्त);
	काष्ठा nouveau_cli *cli = (व्योम *)chan->user.client;
	NV_PRINTK(warn, cli, "channel %d killed!\n", chan->chid);
	atomic_set(&chan->समाप्तed, 1);
	अगर (chan->fence)
		nouveau_fence_context_समाप्त(chan->fence, -ENODEV);
	वापस NVIF_NOTIFY_DROP;
पूर्ण

पूर्णांक
nouveau_channel_idle(काष्ठा nouveau_channel *chan)
अणु
	अगर (likely(chan && chan->fence && !atomic_पढ़ो(&chan->समाप्तed))) अणु
		काष्ठा nouveau_cli *cli = (व्योम *)chan->user.client;
		काष्ठा nouveau_fence *fence = शून्य;
		पूर्णांक ret;

		ret = nouveau_fence_new(chan, false, &fence);
		अगर (!ret) अणु
			ret = nouveau_fence_रुको(fence, false, false);
			nouveau_fence_unref(&fence);
		पूर्ण

		अगर (ret) अणु
			NV_PRINTK(err, cli, "failed to idle channel %d [%s]\n",
				  chan->chid, nvxx_client(&cli->base)->name);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम
nouveau_channel_del(काष्ठा nouveau_channel **pchan)
अणु
	काष्ठा nouveau_channel *chan = *pchan;
	अगर (chan) अणु
		काष्ठा nouveau_cli *cli = (व्योम *)chan->user.client;
		bool super;

		अगर (cli) अणु
			super = cli->base.super;
			cli->base.super = true;
		पूर्ण

		अगर (chan->fence)
			nouveau_fence(chan->drm)->context_del(chan);

		अगर (cli)
			nouveau_svmm_part(chan->vmm->svmm, chan->inst);

		nvअगर_object_dtor(&chan->nvsw);
		nvअगर_object_dtor(&chan->gart);
		nvअगर_object_dtor(&chan->vram);
		nvअगर_notअगरy_dtor(&chan->समाप्त);
		nvअगर_object_dtor(&chan->user);
		nvअगर_object_dtor(&chan->push.ctxdma);
		nouveau_vma_del(&chan->push.vma);
		nouveau_bo_unmap(chan->push.buffer);
		अगर (chan->push.buffer && chan->push.buffer->bo.pin_count)
			nouveau_bo_unpin(chan->push.buffer);
		nouveau_bo_ref(शून्य, &chan->push.buffer);
		kमुक्त(chan);

		अगर (cli)
			cli->base.super = super;
	पूर्ण
	*pchan = शून्य;
पूर्ण

अटल व्योम
nouveau_channel_kick(काष्ठा nvअगर_push *push)
अणु
	काष्ठा nouveau_channel *chan = container_of(push, typeof(*chan), chan._push);
	chan->dma.cur = chan->dma.cur + (chan->chan._push.cur - chan->chan._push.bgn);
	FIRE_RING(chan);
	chan->chan._push.bgn = chan->chan._push.cur;
पूर्ण

अटल पूर्णांक
nouveau_channel_रुको(काष्ठा nvअगर_push *push, u32 size)
अणु
	काष्ठा nouveau_channel *chan = container_of(push, typeof(*chan), chan._push);
	पूर्णांक ret;
	chan->dma.cur = chan->dma.cur + (chan->chan._push.cur - chan->chan._push.bgn);
	ret = RING_SPACE(chan, size);
	अगर (ret == 0) अणु
		chan->chan._push.bgn = chan->chan._push.mem.object.map.ptr;
		chan->chan._push.bgn = chan->chan._push.bgn + chan->dma.cur;
		chan->chan._push.cur = chan->chan._push.bgn;
		chan->chan._push.end = chan->chan._push.bgn + size;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_channel_prep(काष्ठा nouveau_drm *drm, काष्ठा nvअगर_device *device,
		     u32 size, काष्ठा nouveau_channel **pchan)
अणु
	काष्ठा nouveau_cli *cli = (व्योम *)device->object.client;
	काष्ठा nv_dma_v0 args = अणुपूर्ण;
	काष्ठा nouveau_channel *chan;
	u32 target;
	पूर्णांक ret;

	chan = *pchan = kzalloc(माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	chan->device = device;
	chan->drm = drm;
	chan->vmm = cli->svm.cli ? &cli->svm : &cli->vmm;
	atomic_set(&chan->समाप्तed, 0);

	/* allocate memory क्रम dma push buffer */
	target = NOUVEAU_GEM_DOMAIN_GART | NOUVEAU_GEM_DOMAIN_COHERENT;
	अगर (nouveau_vram_pushbuf)
		target = NOUVEAU_GEM_DOMAIN_VRAM;

	ret = nouveau_bo_new(cli, size, 0, target, 0, 0, शून्य, शून्य,
			    &chan->push.buffer);
	अगर (ret == 0) अणु
		ret = nouveau_bo_pin(chan->push.buffer, target, false);
		अगर (ret == 0)
			ret = nouveau_bo_map(chan->push.buffer);
	पूर्ण

	अगर (ret) अणु
		nouveau_channel_del(pchan);
		वापस ret;
	पूर्ण

	chan->chan._push.mem.object.parent = cli->base.object.parent;
	chan->chan._push.mem.object.client = &cli->base;
	chan->chan._push.mem.object.name = "chanPush";
	chan->chan._push.mem.object.map.ptr = chan->push.buffer->kmap.भव;
	chan->chan._push.रुको = nouveau_channel_रुको;
	chan->chan._push.kick = nouveau_channel_kick;
	chan->chan.push = &chan->chan._push;

	/* create dma object covering the *entire* memory space that the
	 * pushbuf lives in, this is because the GEM code requires that
	 * we be able to call out to other (indirect) push buffers
	 */
	chan->push.addr = chan->push.buffer->offset;

	अगर (device->info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		ret = nouveau_vma_new(chan->push.buffer, chan->vmm,
				      &chan->push.vma);
		अगर (ret) अणु
			nouveau_channel_del(pchan);
			वापस ret;
		पूर्ण

		chan->push.addr = chan->push.vma->addr;

		अगर (device->info.family >= NV_DEVICE_INFO_V0_FERMI)
			वापस 0;

		args.target = NV_DMA_V0_TARGET_VM;
		args.access = NV_DMA_V0_ACCESS_VM;
		args.start = 0;
		args.limit = chan->vmm->vmm.limit - 1;
	पूर्ण अन्यथा
	अगर (chan->push.buffer->bo.mem.mem_type == TTM_PL_VRAM) अणु
		अगर (device->info.family == NV_DEVICE_INFO_V0_TNT) अणु
			/* nv04 vram pushbuf hack, retarget to its location in
			 * the framebuffer bar rather than direct vram access..
			 * nfi why this exists, it came from the -nv ddx.
			 */
			args.target = NV_DMA_V0_TARGET_PCI;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = nvxx_device(device)->func->
				resource_addr(nvxx_device(device), 1);
			args.limit = args.start + device->info.ram_user - 1;
		पूर्ण अन्यथा अणु
			args.target = NV_DMA_V0_TARGET_VRAM;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = 0;
			args.limit = device->info.ram_user - 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chan->drm->agp.bridge) अणु
			args.target = NV_DMA_V0_TARGET_AGP;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = chan->drm->agp.base;
			args.limit = chan->drm->agp.base +
				     chan->drm->agp.size - 1;
		पूर्ण अन्यथा अणु
			args.target = NV_DMA_V0_TARGET_VM;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = 0;
			args.limit = chan->vmm->vmm.limit - 1;
		पूर्ण
	पूर्ण

	ret = nvअगर_object_ctor(&device->object, "abi16PushCtxDma", 0,
			       NV_DMA_FROM_MEMORY, &args, माप(args),
			       &chan->push.ctxdma);
	अगर (ret) अणु
		nouveau_channel_del(pchan);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_channel_ind(काष्ठा nouveau_drm *drm, काष्ठा nvअगर_device *device,
		    u64 runlist, bool priv, काष्ठा nouveau_channel **pchan)
अणु
	अटल स्थिर u16 oclasses[] = अणु TURING_CHANNEL_GPFIFO_A,
					VOLTA_CHANNEL_GPFIFO_A,
					PASCAL_CHANNEL_GPFIFO_A,
					MAXWELL_CHANNEL_GPFIFO_A,
					KEPLER_CHANNEL_GPFIFO_B,
					KEPLER_CHANNEL_GPFIFO_A,
					FERMI_CHANNEL_GPFIFO,
					G82_CHANNEL_GPFIFO,
					NV50_CHANNEL_GPFIFO,
					0 पूर्ण;
	स्थिर u16 *oclass = oclasses;
	जोड़ अणु
		काष्ठा nv50_channel_gpfअगरo_v0 nv50;
		काष्ठा fermi_channel_gpfअगरo_v0 fermi;
		काष्ठा kepler_channel_gpfअगरo_a_v0 kepler;
		काष्ठा volta_channel_gpfअगरo_a_v0 volta;
	पूर्ण args;
	काष्ठा nouveau_channel *chan;
	u32 size;
	पूर्णांक ret;

	/* allocate dma push buffer */
	ret = nouveau_channel_prep(drm, device, 0x12000, &chan);
	*pchan = chan;
	अगर (ret)
		वापस ret;

	/* create channel object */
	करो अणु
		अगर (oclass[0] >= VOLTA_CHANNEL_GPFIFO_A) अणु
			args.volta.version = 0;
			args.volta.ilength = 0x02000;
			args.volta.ioffset = 0x10000 + chan->push.addr;
			args.volta.runlist = runlist;
			args.volta.vmm = nvअगर_handle(&chan->vmm->vmm.object);
			args.volta.priv = priv;
			size = माप(args.volta);
		पूर्ण अन्यथा
		अगर (oclass[0] >= KEPLER_CHANNEL_GPFIFO_A) अणु
			args.kepler.version = 0;
			args.kepler.ilength = 0x02000;
			args.kepler.ioffset = 0x10000 + chan->push.addr;
			args.kepler.runlist = runlist;
			args.kepler.vmm = nvअगर_handle(&chan->vmm->vmm.object);
			args.kepler.priv = priv;
			size = माप(args.kepler);
		पूर्ण अन्यथा
		अगर (oclass[0] >= FERMI_CHANNEL_GPFIFO) अणु
			args.fermi.version = 0;
			args.fermi.ilength = 0x02000;
			args.fermi.ioffset = 0x10000 + chan->push.addr;
			args.fermi.vmm = nvअगर_handle(&chan->vmm->vmm.object);
			size = माप(args.fermi);
		पूर्ण अन्यथा अणु
			args.nv50.version = 0;
			args.nv50.ilength = 0x02000;
			args.nv50.ioffset = 0x10000 + chan->push.addr;
			args.nv50.pushbuf = nvअगर_handle(&chan->push.ctxdma);
			args.nv50.vmm = nvअगर_handle(&chan->vmm->vmm.object);
			size = माप(args.nv50);
		पूर्ण

		ret = nvअगर_object_ctor(&device->object, "abi16ChanUser", 0,
				       *oclass++, &args, size, &chan->user);
		अगर (ret == 0) अणु
			अगर (chan->user.oclass >= VOLTA_CHANNEL_GPFIFO_A) अणु
				chan->chid = args.volta.chid;
				chan->inst = args.volta.inst;
				chan->token = args.volta.token;
			पूर्ण अन्यथा
			अगर (chan->user.oclass >= KEPLER_CHANNEL_GPFIFO_A) अणु
				chan->chid = args.kepler.chid;
				chan->inst = args.kepler.inst;
			पूर्ण अन्यथा
			अगर (chan->user.oclass >= FERMI_CHANNEL_GPFIFO) अणु
				chan->chid = args.fermi.chid;
			पूर्ण अन्यथा अणु
				chan->chid = args.nv50.chid;
			पूर्ण
			वापस ret;
		पूर्ण
	पूर्ण जबतक (*oclass);

	nouveau_channel_del(pchan);
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_channel_dma(काष्ठा nouveau_drm *drm, काष्ठा nvअगर_device *device,
		    काष्ठा nouveau_channel **pchan)
अणु
	अटल स्थिर u16 oclasses[] = अणु NV40_CHANNEL_DMA,
					NV17_CHANNEL_DMA,
					NV10_CHANNEL_DMA,
					NV03_CHANNEL_DMA,
					0 पूर्ण;
	स्थिर u16 *oclass = oclasses;
	काष्ठा nv03_channel_dma_v0 args;
	काष्ठा nouveau_channel *chan;
	पूर्णांक ret;

	/* allocate dma push buffer */
	ret = nouveau_channel_prep(drm, device, 0x10000, &chan);
	*pchan = chan;
	अगर (ret)
		वापस ret;

	/* create channel object */
	args.version = 0;
	args.pushbuf = nvअगर_handle(&chan->push.ctxdma);
	args.offset = chan->push.addr;

	करो अणु
		ret = nvअगर_object_ctor(&device->object, "abi16ChanUser", 0,
				       *oclass++, &args, माप(args),
				       &chan->user);
		अगर (ret == 0) अणु
			chan->chid = args.chid;
			वापस ret;
		पूर्ण
	पूर्ण जबतक (ret && *oclass);

	nouveau_channel_del(pchan);
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_channel_init(काष्ठा nouveau_channel *chan, u32 vram, u32 gart)
अणु
	काष्ठा nvअगर_device *device = chan->device;
	काष्ठा nouveau_drm *drm = chan->drm;
	काष्ठा nv_dma_v0 args = अणुपूर्ण;
	पूर्णांक ret, i;

	nvअगर_object_map(&chan->user, शून्य, 0);

	अगर (chan->user.oclass >= FERMI_CHANNEL_GPFIFO) अणु
		ret = nvअगर_notअगरy_ctor(&chan->user, "abi16ChanKilled",
				       nouveau_channel_समाप्तed,
				       true, NV906F_V0_NTFY_KILLED,
				       शून्य, 0, 0, &chan->समाप्त);
		अगर (ret == 0)
			ret = nvअगर_notअगरy_get(&chan->समाप्त);
		अगर (ret) अणु
			NV_ERROR(drm, "Failed to request channel kill "
				      "notification: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* allocate dma objects to cover all allowed vram, and gart */
	अगर (device->info.family < NV_DEVICE_INFO_V0_FERMI) अणु
		अगर (device->info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
			args.target = NV_DMA_V0_TARGET_VM;
			args.access = NV_DMA_V0_ACCESS_VM;
			args.start = 0;
			args.limit = chan->vmm->vmm.limit - 1;
		पूर्ण अन्यथा अणु
			args.target = NV_DMA_V0_TARGET_VRAM;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = 0;
			args.limit = device->info.ram_user - 1;
		पूर्ण

		ret = nvअगर_object_ctor(&chan->user, "abi16ChanVramCtxDma", vram,
				       NV_DMA_IN_MEMORY, &args, माप(args),
				       &chan->vram);
		अगर (ret)
			वापस ret;

		अगर (device->info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
			args.target = NV_DMA_V0_TARGET_VM;
			args.access = NV_DMA_V0_ACCESS_VM;
			args.start = 0;
			args.limit = chan->vmm->vmm.limit - 1;
		पूर्ण अन्यथा
		अगर (chan->drm->agp.bridge) अणु
			args.target = NV_DMA_V0_TARGET_AGP;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = chan->drm->agp.base;
			args.limit = chan->drm->agp.base +
				     chan->drm->agp.size - 1;
		पूर्ण अन्यथा अणु
			args.target = NV_DMA_V0_TARGET_VM;
			args.access = NV_DMA_V0_ACCESS_RDWR;
			args.start = 0;
			args.limit = chan->vmm->vmm.limit - 1;
		पूर्ण

		ret = nvअगर_object_ctor(&chan->user, "abi16ChanGartCtxDma", gart,
				       NV_DMA_IN_MEMORY, &args, माप(args),
				       &chan->gart);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* initialise dma tracking parameters */
	चयन (chan->user.oclass & 0x00ff) अणु
	हाल 0x006b:
	हाल 0x006e:
		chan->user_put = 0x40;
		chan->user_get = 0x44;
		chan->dma.max = (0x10000 / 4) - 2;
		अवरोध;
	शेष:
		chan->user_put = 0x40;
		chan->user_get = 0x44;
		chan->user_get_hi = 0x60;
		chan->dma.ib_base =  0x10000 / 4;
		chan->dma.ib_max  = (0x02000 / 8) - 1;
		chan->dma.ib_put  = 0;
		chan->dma.ib_मुक्त = chan->dma.ib_max - chan->dma.ib_put;
		chan->dma.max = chan->dma.ib_base;
		अवरोध;
	पूर्ण

	chan->dma.put = 0;
	chan->dma.cur = chan->dma.put;
	chan->dma.मुक्त = chan->dma.max - chan->dma.cur;

	ret = PUSH_WAIT(chan->chan.push, NOUVEAU_DMA_SKIPS);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < NOUVEAU_DMA_SKIPS; i++)
		PUSH_DATA(chan->chan.push, 0x00000000);

	/* allocate software object class (used क्रम fences on <= nv05) */
	अगर (device->info.family < NV_DEVICE_INFO_V0_CELSIUS) अणु
		ret = nvअगर_object_ctor(&chan->user, "abi16NvswFence", 0x006e,
				       NVIF_CLASS_SW_NV04,
				       शून्य, 0, &chan->nvsw);
		अगर (ret)
			वापस ret;

		ret = PUSH_WAIT(chan->chan.push, 2);
		अगर (ret)
			वापस ret;

		PUSH_NVSQ(chan->chan.push, NV_SW, 0x0000, chan->nvsw.handle);
		PUSH_KICK(chan->chan.push);
	पूर्ण

	/* initialise synchronisation */
	वापस nouveau_fence(chan->drm)->context_new(chan);
पूर्ण

पूर्णांक
nouveau_channel_new(काष्ठा nouveau_drm *drm, काष्ठा nvअगर_device *device,
		    u32 arg0, u32 arg1, bool priv,
		    काष्ठा nouveau_channel **pchan)
अणु
	काष्ठा nouveau_cli *cli = (व्योम *)device->object.client;
	bool super;
	पूर्णांक ret;

	/* hack until fencenv50 is fixed, and agp access relaxed */
	super = cli->base.super;
	cli->base.super = true;

	ret = nouveau_channel_ind(drm, device, arg0, priv, pchan);
	अगर (ret) अणु
		NV_PRINTK(dbg, cli, "ib channel create, %d\n", ret);
		ret = nouveau_channel_dma(drm, device, pchan);
		अगर (ret) अणु
			NV_PRINTK(dbg, cli, "dma channel create, %d\n", ret);
			जाओ करोne;
		पूर्ण
	पूर्ण

	ret = nouveau_channel_init(*pchan, arg0, arg1);
	अगर (ret) अणु
		NV_PRINTK(err, cli, "channel failed to initialise, %d\n", ret);
		nouveau_channel_del(pchan);
		जाओ करोne;
	पूर्ण

	ret = nouveau_svmm_join((*pchan)->vmm->svmm, (*pchan)->inst);
	अगर (ret)
		nouveau_channel_del(pchan);

करोne:
	cli->base.super = super;
	वापस ret;
पूर्ण

पूर्णांक
nouveau_channels_init(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा अणु
		काष्ठा nv_device_info_v1 m;
		काष्ठा अणु
			काष्ठा nv_device_info_v1_data channels;
		पूर्ण v;
	पूर्ण args = अणु
		.m.version = 1,
		.m.count = माप(args.v) / माप(args.v.channels),
		.v.channels.mthd = NV_DEVICE_HOST_CHANNELS,
	पूर्ण;
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक ret;

	ret = nvअगर_object_mthd(device, NV_DEVICE_V0_INFO, &args, माप(args));
	अगर (ret || args.v.channels.mthd == NV_DEVICE_INFO_INVALID)
		वापस -ENODEV;

	drm->chan.nr = args.v.channels.data;
	drm->chan.context_base = dma_fence_context_alloc(drm->chan.nr);
	वापस 0;
पूर्ण
