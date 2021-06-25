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
 */

#समावेश <nvअगर/client.h>
#समावेश <nvअगर/driver.h>
#समावेश <nvअगर/fअगरo.h>
#समावेश <nvअगर/ioctl.h>
#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/cla06f.h>
#समावेश <nvअगर/unpack.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_chan.h"
#समावेश "nouveau_abi16.h"
#समावेश "nouveau_vmm.h"

अटल काष्ठा nouveau_abi16 *
nouveau_abi16(काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	अगर (!cli->abi16) अणु
		काष्ठा nouveau_abi16 *abi16;
		cli->abi16 = abi16 = kzalloc(माप(*abi16), GFP_KERNEL);
		अगर (cli->abi16) अणु
			काष्ठा nv_device_v0 args = अणु
				.device = ~0ULL,
			पूर्ण;

			INIT_LIST_HEAD(&abi16->channels);

			/* allocate device object targeting client's शेष
			 * device (ie. the one that beदीर्घs to the fd it
			 * खोलोed)
			 */
			अगर (nvअगर_device_ctor(&cli->base.object, "abi16Device",
					     0, NV_DEVICE, &args, माप(args),
					     &abi16->device) == 0)
				वापस cli->abi16;

			kमुक्त(cli->abi16);
			cli->abi16 = शून्य;
		पूर्ण
	पूर्ण
	वापस cli->abi16;
पूर्ण

काष्ठा nouveau_abi16 *
nouveau_abi16_get(काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	mutex_lock(&cli->mutex);
	अगर (nouveau_abi16(file_priv))
		वापस cli->abi16;
	mutex_unlock(&cli->mutex);
	वापस शून्य;
पूर्ण

पूर्णांक
nouveau_abi16_put(काष्ठा nouveau_abi16 *abi16, पूर्णांक ret)
अणु
	काष्ठा nouveau_cli *cli = (व्योम *)abi16->device.object.client;
	mutex_unlock(&cli->mutex);
	वापस ret;
पूर्ण

s32
nouveau_abi16_swclass(काष्ठा nouveau_drm *drm)
अणु
	चयन (drm->client.device.info.family) अणु
	हाल NV_DEVICE_INFO_V0_TNT:
		वापस NVIF_CLASS_SW_NV04;
	हाल NV_DEVICE_INFO_V0_CELSIUS:
	हाल NV_DEVICE_INFO_V0_KELVIN:
	हाल NV_DEVICE_INFO_V0_RANKINE:
	हाल NV_DEVICE_INFO_V0_CURIE:
		वापस NVIF_CLASS_SW_NV10;
	हाल NV_DEVICE_INFO_V0_TESLA:
		वापस NVIF_CLASS_SW_NV50;
	हाल NV_DEVICE_INFO_V0_FERMI:
	हाल NV_DEVICE_INFO_V0_KEPLER:
	हाल NV_DEVICE_INFO_V0_MAXWELL:
	हाल NV_DEVICE_INFO_V0_PASCAL:
	हाल NV_DEVICE_INFO_V0_VOLTA:
		वापस NVIF_CLASS_SW_GF100;
	पूर्ण

	वापस 0x0000;
पूर्ण

अटल व्योम
nouveau_abi16_ntfy_fini(काष्ठा nouveau_abi16_chan *chan,
			काष्ठा nouveau_abi16_ntfy *ntfy)
अणु
	nvअगर_object_dtor(&ntfy->object);
	nvkm_mm_मुक्त(&chan->heap, &ntfy->node);
	list_del(&ntfy->head);
	kमुक्त(ntfy);
पूर्ण

अटल व्योम
nouveau_abi16_chan_fini(काष्ठा nouveau_abi16 *abi16,
			काष्ठा nouveau_abi16_chan *chan)
अणु
	काष्ठा nouveau_abi16_ntfy *ntfy, *temp;

	/* रुको क्रम all activity to stop beक्रमe releasing notअगरy object, which
	 * may be still in use */
	अगर (chan->chan && chan->ntfy)
		nouveau_channel_idle(chan->chan);

	/* cleanup notअगरier state */
	list_क्रम_each_entry_safe(ntfy, temp, &chan->notअगरiers, head) अणु
		nouveau_abi16_ntfy_fini(chan, ntfy);
	पूर्ण

	अगर (chan->ntfy) अणु
		nouveau_vma_del(&chan->ntfy_vma);
		nouveau_bo_unpin(chan->ntfy);
		drm_gem_object_put(&chan->ntfy->bo.base);
	पूर्ण

	अगर (chan->heap.block_size)
		nvkm_mm_fini(&chan->heap);

	/* destroy channel object, all children will be समाप्तed too */
	अगर (chan->chan) अणु
		nouveau_channel_idle(chan->chan);
		nouveau_channel_del(&chan->chan);
	पूर्ण

	list_del(&chan->head);
	kमुक्त(chan);
पूर्ण

व्योम
nouveau_abi16_fini(काष्ठा nouveau_abi16 *abi16)
अणु
	काष्ठा nouveau_cli *cli = (व्योम *)abi16->device.object.client;
	काष्ठा nouveau_abi16_chan *chan, *temp;

	/* cleanup channels */
	list_क्रम_each_entry_safe(chan, temp, &abi16->channels, head) अणु
		nouveau_abi16_chan_fini(abi16, chan);
	पूर्ण

	/* destroy the device object */
	nvअगर_device_dtor(&abi16->device);

	kमुक्त(cli->abi16);
	cli->abi16 = शून्य;
पूर्ण

पूर्णांक
nouveau_abi16_ioctl_getparam(ABI16_IOCTL_ARGS)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_device *device = &drm->client.device;
	काष्ठा nvkm_gr *gr = nvxx_gr(device);
	काष्ठा drm_nouveau_getparam *getparam = data;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	चयन (getparam->param) अणु
	हाल NOUVEAU_GETPARAM_CHIPSET_ID:
		getparam->value = device->info.chipset;
		अवरोध;
	हाल NOUVEAU_GETPARAM_PCI_VENDOR:
		अगर (device->info.platक्रमm != NV_DEVICE_INFO_V0_SOC)
			getparam->value = pdev->venकरोr;
		अन्यथा
			getparam->value = 0;
		अवरोध;
	हाल NOUVEAU_GETPARAM_PCI_DEVICE:
		अगर (device->info.platक्रमm != NV_DEVICE_INFO_V0_SOC)
			getparam->value = pdev->device;
		अन्यथा
			getparam->value = 0;
		अवरोध;
	हाल NOUVEAU_GETPARAM_BUS_TYPE:
		चयन (device->info.platक्रमm) अणु
		हाल NV_DEVICE_INFO_V0_AGP : getparam->value = 0; अवरोध;
		हाल NV_DEVICE_INFO_V0_PCI : getparam->value = 1; अवरोध;
		हाल NV_DEVICE_INFO_V0_PCIE: getparam->value = 2; अवरोध;
		हाल NV_DEVICE_INFO_V0_SOC : getparam->value = 3; अवरोध;
		हाल NV_DEVICE_INFO_V0_IGP :
			अगर (!pci_is_pcie(pdev))
				getparam->value = 1;
			अन्यथा
				getparam->value = 2;
			अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NOUVEAU_GETPARAM_FB_SIZE:
		getparam->value = drm->gem.vram_available;
		अवरोध;
	हाल NOUVEAU_GETPARAM_AGP_SIZE:
		getparam->value = drm->gem.gart_available;
		अवरोध;
	हाल NOUVEAU_GETPARAM_VM_VRAM_BASE:
		getparam->value = 0; /* deprecated */
		अवरोध;
	हाल NOUVEAU_GETPARAM_PTIMER_TIME:
		getparam->value = nvअगर_device_समय(device);
		अवरोध;
	हाल NOUVEAU_GETPARAM_HAS_BO_USAGE:
		getparam->value = 1;
		अवरोध;
	हाल NOUVEAU_GETPARAM_HAS_PAGEFLIP:
		getparam->value = 1;
		अवरोध;
	हाल NOUVEAU_GETPARAM_GRAPH_UNITS:
		getparam->value = nvkm_gr_units(gr);
		अवरोध;
	शेष:
		NV_PRINTK(dbg, cli, "unknown parameter %lld\n", getparam->param);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nouveau_abi16_ioctl_channel_alloc(ABI16_IOCTL_ARGS)
अणु
	काष्ठा drm_nouveau_channel_alloc *init = data;
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_abi16 *abi16 = nouveau_abi16_get(file_priv);
	काष्ठा nouveau_abi16_chan *chan;
	काष्ठा nvअगर_device *device;
	u64 engine;
	पूर्णांक ret;

	अगर (unlikely(!abi16))
		वापस -ENOMEM;

	अगर (!drm->channel)
		वापस nouveau_abi16_put(abi16, -ENODEV);

	device = &abi16->device;

	/* hack to allow channel engine type specअगरication on kepler */
	अगर (device->info.family >= NV_DEVICE_INFO_V0_KEPLER) अणु
		अगर (init->fb_ctxdma_handle == ~0) अणु
			चयन (init->tt_ctxdma_handle) अणु
			हाल 0x01: engine = NV_DEVICE_HOST_RUNLIST_ENGINES_GR    ; अवरोध;
			हाल 0x02: engine = NV_DEVICE_HOST_RUNLIST_ENGINES_MSPDEC; अवरोध;
			हाल 0x04: engine = NV_DEVICE_HOST_RUNLIST_ENGINES_MSPPP ; अवरोध;
			हाल 0x08: engine = NV_DEVICE_HOST_RUNLIST_ENGINES_MSVLD ; अवरोध;
			हाल 0x30: engine = NV_DEVICE_HOST_RUNLIST_ENGINES_CE    ; अवरोध;
			शेष:
				वापस nouveau_abi16_put(abi16, -ENOSYS);
			पूर्ण
		पूर्ण अन्यथा अणु
			engine = NV_DEVICE_HOST_RUNLIST_ENGINES_GR;
		पूर्ण

		अगर (engine != NV_DEVICE_HOST_RUNLIST_ENGINES_CE)
			engine = nvअगर_fअगरo_runlist(device, engine);
		अन्यथा
			engine = nvअगर_fअगरo_runlist_ce(device);
		init->fb_ctxdma_handle = engine;
		init->tt_ctxdma_handle = 0;
	पूर्ण

	अगर (init->fb_ctxdma_handle == ~0 || init->tt_ctxdma_handle == ~0)
		वापस nouveau_abi16_put(abi16, -EINVAL);

	/* allocate "abi16 channel" data and make up a handle क्रम it */
	chan = kzalloc(माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस nouveau_abi16_put(abi16, -ENOMEM);

	INIT_LIST_HEAD(&chan->notअगरiers);
	list_add(&chan->head, &abi16->channels);

	/* create channel object and initialise dma and fence management */
	ret = nouveau_channel_new(drm, device, init->fb_ctxdma_handle,
				  init->tt_ctxdma_handle, false, &chan->chan);
	अगर (ret)
		जाओ करोne;

	init->channel = chan->chan->chid;

	अगर (device->info.family >= NV_DEVICE_INFO_V0_TESLA)
		init->pushbuf_करोमुख्यs = NOUVEAU_GEM_DOMAIN_VRAM |
					NOUVEAU_GEM_DOMAIN_GART;
	अन्यथा
	अगर (chan->chan->push.buffer->bo.mem.mem_type == TTM_PL_VRAM)
		init->pushbuf_करोमुख्यs = NOUVEAU_GEM_DOMAIN_VRAM;
	अन्यथा
		init->pushbuf_करोमुख्यs = NOUVEAU_GEM_DOMAIN_GART;

	अगर (device->info.family < NV_DEVICE_INFO_V0_CELSIUS) अणु
		init->subchan[0].handle = 0x00000000;
		init->subchan[0].grclass = 0x0000;
		init->subchan[1].handle = chan->chan->nvsw.handle;
		init->subchan[1].grclass = 0x506e;
		init->nr_subchan = 2;
	पूर्ण

	/* Named memory object area */
	ret = nouveau_gem_new(cli, PAGE_SIZE, 0, NOUVEAU_GEM_DOMAIN_GART,
			      0, 0, &chan->ntfy);
	अगर (ret == 0)
		ret = nouveau_bo_pin(chan->ntfy, NOUVEAU_GEM_DOMAIN_GART,
				     false);
	अगर (ret)
		जाओ करोne;

	अगर (device->info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		ret = nouveau_vma_new(chan->ntfy, chan->chan->vmm,
				      &chan->ntfy_vma);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	ret = drm_gem_handle_create(file_priv, &chan->ntfy->bo.base,
				    &init->notअगरier_handle);
	अगर (ret)
		जाओ करोne;

	ret = nvkm_mm_init(&chan->heap, 0, 0, PAGE_SIZE, 1);
करोne:
	अगर (ret)
		nouveau_abi16_chan_fini(abi16, chan);
	वापस nouveau_abi16_put(abi16, ret);
पूर्ण

अटल काष्ठा nouveau_abi16_chan *
nouveau_abi16_chan(काष्ठा nouveau_abi16 *abi16, पूर्णांक channel)
अणु
	काष्ठा nouveau_abi16_chan *chan;

	list_क्रम_each_entry(chan, &abi16->channels, head) अणु
		अगर (chan->chan->chid == channel)
			वापस chan;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक
nouveau_abi16_usअगर(काष्ठा drm_file *file_priv, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_v0 v0;
	पूर्ण *args = data;
	काष्ठा nouveau_abi16_chan *chan;
	काष्ठा nouveau_abi16 *abi16;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		चयन (args->v0.type) अणु
		हाल NVIF_IOCTL_V0_NEW:
		हाल NVIF_IOCTL_V0_MTHD:
		हाल NVIF_IOCTL_V0_SCLASS:
			अवरोध;
		शेष:
			वापस -EACCES;
		पूर्ण
	पूर्ण अन्यथा
		वापस ret;

	अगर (!(abi16 = nouveau_abi16(file_priv)))
		वापस -ENOMEM;

	अगर (args->v0.token != ~0ULL) अणु
		अगर (!(chan = nouveau_abi16_chan(abi16, args->v0.token)))
			वापस -EINVAL;
		args->v0.object = nvअगर_handle(&chan->chan->user);
		args->v0.owner  = NVIF_IOCTL_V0_OWNER_ANY;
		वापस 0;
	पूर्ण

	args->v0.object = nvअगर_handle(&abi16->device.object);
	args->v0.owner  = NVIF_IOCTL_V0_OWNER_ANY;
	वापस 0;
पूर्ण

पूर्णांक
nouveau_abi16_ioctl_channel_मुक्त(ABI16_IOCTL_ARGS)
अणु
	काष्ठा drm_nouveau_channel_मुक्त *req = data;
	काष्ठा nouveau_abi16 *abi16 = nouveau_abi16_get(file_priv);
	काष्ठा nouveau_abi16_chan *chan;

	अगर (unlikely(!abi16))
		वापस -ENOMEM;

	chan = nouveau_abi16_chan(abi16, req->channel);
	अगर (!chan)
		वापस nouveau_abi16_put(abi16, -ENOENT);
	nouveau_abi16_chan_fini(abi16, chan);
	वापस nouveau_abi16_put(abi16, 0);
पूर्ण

पूर्णांक
nouveau_abi16_ioctl_grobj_alloc(ABI16_IOCTL_ARGS)
अणु
	काष्ठा drm_nouveau_grobj_alloc *init = data;
	काष्ठा nouveau_abi16 *abi16 = nouveau_abi16_get(file_priv);
	काष्ठा nouveau_abi16_chan *chan;
	काष्ठा nouveau_abi16_ntfy *ntfy;
	काष्ठा nvअगर_client *client;
	काष्ठा nvअगर_sclass *sclass;
	s32 oclass = 0;
	पूर्णांक ret, i;

	अगर (unlikely(!abi16))
		वापस -ENOMEM;

	अगर (init->handle == ~0)
		वापस nouveau_abi16_put(abi16, -EINVAL);
	client = abi16->device.object.client;

	chan = nouveau_abi16_chan(abi16, init->channel);
	अगर (!chan)
		वापस nouveau_abi16_put(abi16, -ENOENT);

	ret = nvअगर_object_sclass_get(&chan->chan->user, &sclass);
	अगर (ret < 0)
		वापस nouveau_abi16_put(abi16, ret);

	अगर ((init->class & 0x00ff) == 0x006e) अणु
		/* nvsw: compatibility with older 0x*6e class identअगरier */
		क्रम (i = 0; !oclass && i < ret; i++) अणु
			चयन (sclass[i].oclass) अणु
			हाल NVIF_CLASS_SW_NV04:
			हाल NVIF_CLASS_SW_NV10:
			हाल NVIF_CLASS_SW_NV50:
			हाल NVIF_CLASS_SW_GF100:
				oclass = sclass[i].oclass;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
	अगर ((init->class & 0x00ff) == 0x00b1) अणु
		/* msvld: compatibility with incorrect version exposure */
		क्रम (i = 0; i < ret; i++) अणु
			अगर ((sclass[i].oclass & 0x00ff) == 0x00b1) अणु
				oclass = sclass[i].oclass;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
	अगर ((init->class & 0x00ff) == 0x00b2) अणु /* mspdec */
		/* mspdec: compatibility with incorrect version exposure */
		क्रम (i = 0; i < ret; i++) अणु
			अगर ((sclass[i].oclass & 0x00ff) == 0x00b2) अणु
				oclass = sclass[i].oclass;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
	अगर ((init->class & 0x00ff) == 0x00b3) अणु /* msppp */
		/* msppp: compatibility with incorrect version exposure */
		क्रम (i = 0; i < ret; i++) अणु
			अगर ((sclass[i].oclass & 0x00ff) == 0x00b3) अणु
				oclass = sclass[i].oclass;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		oclass = init->class;
	पूर्ण

	nvअगर_object_sclass_put(&sclass);
	अगर (!oclass)
		वापस nouveau_abi16_put(abi16, -EINVAL);

	ntfy = kzalloc(माप(*ntfy), GFP_KERNEL);
	अगर (!ntfy)
		वापस nouveau_abi16_put(abi16, -ENOMEM);

	list_add(&ntfy->head, &chan->notअगरiers);

	client->route = NVDRM_OBJECT_ABI16;
	ret = nvअगर_object_ctor(&chan->chan->user, "abi16EngObj", init->handle,
			       oclass, शून्य, 0, &ntfy->object);
	client->route = NVDRM_OBJECT_NVIF;

	अगर (ret)
		nouveau_abi16_ntfy_fini(chan, ntfy);
	वापस nouveau_abi16_put(abi16, ret);
पूर्ण

पूर्णांक
nouveau_abi16_ioctl_notअगरierobj_alloc(ABI16_IOCTL_ARGS)
अणु
	काष्ठा drm_nouveau_notअगरierobj_alloc *info = data;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_abi16 *abi16 = nouveau_abi16_get(file_priv);
	काष्ठा nouveau_abi16_chan *chan;
	काष्ठा nouveau_abi16_ntfy *ntfy;
	काष्ठा nvअगर_device *device = &abi16->device;
	काष्ठा nvअगर_client *client;
	काष्ठा nv_dma_v0 args = अणुपूर्ण;
	पूर्णांक ret;

	अगर (unlikely(!abi16))
		वापस -ENOMEM;

	/* completely unnecessary क्रम these chipsets... */
	अगर (unlikely(device->info.family >= NV_DEVICE_INFO_V0_FERMI))
		वापस nouveau_abi16_put(abi16, -EINVAL);
	client = abi16->device.object.client;

	chan = nouveau_abi16_chan(abi16, info->channel);
	अगर (!chan)
		वापस nouveau_abi16_put(abi16, -ENOENT);

	ntfy = kzalloc(माप(*ntfy), GFP_KERNEL);
	अगर (!ntfy)
		वापस nouveau_abi16_put(abi16, -ENOMEM);

	list_add(&ntfy->head, &chan->notअगरiers);

	ret = nvkm_mm_head(&chan->heap, 0, 1, info->size, info->size, 1,
			   &ntfy->node);
	अगर (ret)
		जाओ करोne;

	args.start = ntfy->node->offset;
	args.limit = ntfy->node->offset + ntfy->node->length - 1;
	अगर (device->info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		args.target = NV_DMA_V0_TARGET_VM;
		args.access = NV_DMA_V0_ACCESS_VM;
		args.start += chan->ntfy_vma->addr;
		args.limit += chan->ntfy_vma->addr;
	पूर्ण अन्यथा
	अगर (drm->agp.bridge) अणु
		args.target = NV_DMA_V0_TARGET_AGP;
		args.access = NV_DMA_V0_ACCESS_RDWR;
		args.start += drm->agp.base + chan->ntfy->offset;
		args.limit += drm->agp.base + chan->ntfy->offset;
	पूर्ण अन्यथा अणु
		args.target = NV_DMA_V0_TARGET_VM;
		args.access = NV_DMA_V0_ACCESS_RDWR;
		args.start += chan->ntfy->offset;
		args.limit += chan->ntfy->offset;
	पूर्ण

	client->route = NVDRM_OBJECT_ABI16;
	client->super = true;
	ret = nvअगर_object_ctor(&chan->chan->user, "abi16Ntfy", info->handle,
			       NV_DMA_IN_MEMORY, &args, माप(args),
			       &ntfy->object);
	client->super = false;
	client->route = NVDRM_OBJECT_NVIF;
	अगर (ret)
		जाओ करोne;

	info->offset = ntfy->node->offset;
करोne:
	अगर (ret)
		nouveau_abi16_ntfy_fini(chan, ntfy);
	वापस nouveau_abi16_put(abi16, ret);
पूर्ण

पूर्णांक
nouveau_abi16_ioctl_gpuobj_मुक्त(ABI16_IOCTL_ARGS)
अणु
	काष्ठा drm_nouveau_gpuobj_मुक्त *fini = data;
	काष्ठा nouveau_abi16 *abi16 = nouveau_abi16_get(file_priv);
	काष्ठा nouveau_abi16_chan *chan;
	काष्ठा nouveau_abi16_ntfy *ntfy;
	पूर्णांक ret = -ENOENT;

	अगर (unlikely(!abi16))
		वापस -ENOMEM;

	chan = nouveau_abi16_chan(abi16, fini->channel);
	अगर (!chan)
		वापस nouveau_abi16_put(abi16, -EINVAL);

	/* synchronize with the user channel and destroy the gpu object */
	nouveau_channel_idle(chan->chan);

	list_क्रम_each_entry(ntfy, &chan->notअगरiers, head) अणु
		अगर (ntfy->object.handle == fini->handle) अणु
			nouveau_abi16_ntfy_fini(chan, ntfy);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस nouveau_abi16_put(abi16, ret);
पूर्ण
