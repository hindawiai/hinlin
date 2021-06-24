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

#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/mmu_notअगरier.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_vblank.h>

#समावेश <core/gpuobj.h>
#समावेश <core/option.h>
#समावेश <core/pci.h>
#समावेश <core/tegra.h>

#समावेश <nvअगर/driver.h>
#समावेश <nvअगर/fअगरo.h>
#समावेश <nvअगर/push006c.h>
#समावेश <nvअगर/user.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/cla06f.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_ttm.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_vga.h"
#समावेश "nouveau_led.h"
#समावेश "nouveau_hwmon.h"
#समावेश "nouveau_acpi.h"
#समावेश "nouveau_bios.h"
#समावेश "nouveau_ioctl.h"
#समावेश "nouveau_abi16.h"
#समावेश "nouveau_fbcon.h"
#समावेश "nouveau_fence.h"
#समावेश "nouveau_debugfs.h"
#समावेश "nouveau_usif.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_platform.h"
#समावेश "nouveau_svm.h"
#समावेश "nouveau_dmem.h"

MODULE_PARM_DESC(config, "option string to pass to driver core");
अटल अक्षर *nouveau_config;
module_param_named(config, nouveau_config, अक्षरp, 0400);

MODULE_PARM_DESC(debug, "debug string to pass to driver core");
अटल अक्षर *nouveau_debug;
module_param_named(debug, nouveau_debug, अक्षरp, 0400);

MODULE_PARM_DESC(noaccel, "disable kernel/abi16 acceleration");
अटल पूर्णांक nouveau_noaccel = 0;
module_param_named(noaccel, nouveau_noaccel, पूर्णांक, 0400);

MODULE_PARM_DESC(modeset, "enable driver (default: auto, "
		          "0 = disabled, 1 = enabled, 2 = headless)");
पूर्णांक nouveau_modeset = -1;
module_param_named(modeset, nouveau_modeset, पूर्णांक, 0400);

MODULE_PARM_DESC(atomic, "Expose atomic ioctl (default: disabled)");
अटल पूर्णांक nouveau_atomic = 0;
module_param_named(atomic, nouveau_atomic, पूर्णांक, 0400);

MODULE_PARM_DESC(runpm, "disable (0), force enable (1), optimus only default (-1)");
अटल पूर्णांक nouveau_runसमय_pm = -1;
module_param_named(runpm, nouveau_runसमय_pm, पूर्णांक, 0400);

अटल काष्ठा drm_driver driver_stub;
अटल काष्ठा drm_driver driver_pci;
अटल काष्ठा drm_driver driver_platक्रमm;

अटल u64
nouveau_pci_name(काष्ठा pci_dev *pdev)
अणु
	u64 name = (u64)pci_करोमुख्य_nr(pdev->bus) << 32;
	name |= pdev->bus->number << 16;
	name |= PCI_SLOT(pdev->devfn) << 8;
	वापस name | PCI_FUNC(pdev->devfn);
पूर्ण

अटल u64
nouveau_platक्रमm_name(काष्ठा platक्रमm_device *platक्रमmdev)
अणु
	वापस platक्रमmdev->id;
पूर्ण

अटल u64
nouveau_name(काष्ठा drm_device *dev)
अणु
	अगर (dev_is_pci(dev->dev))
		वापस nouveau_pci_name(to_pci_dev(dev->dev));
	अन्यथा
		वापस nouveau_platक्रमm_name(to_platक्रमm_device(dev->dev));
पूर्ण

अटल अंतरभूत bool
nouveau_cli_work_पढ़ोy(काष्ठा dma_fence *fence)
अणु
	अगर (!dma_fence_is_संकेतed(fence))
		वापस false;
	dma_fence_put(fence);
	वापस true;
पूर्ण

अटल व्योम
nouveau_cli_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा nouveau_cli *cli = container_of(w, typeof(*cli), work);
	काष्ठा nouveau_cli_work *work, *wपंचांगp;
	mutex_lock(&cli->lock);
	list_क्रम_each_entry_safe(work, wपंचांगp, &cli->worker, head) अणु
		अगर (!work->fence || nouveau_cli_work_पढ़ोy(work->fence)) अणु
			list_del(&work->head);
			work->func(work);
		पूर्ण
	पूर्ण
	mutex_unlock(&cli->lock);
पूर्ण

अटल व्योम
nouveau_cli_work_fence(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा nouveau_cli_work *work = container_of(cb, typeof(*work), cb);
	schedule_work(&work->cli->work);
पूर्ण

व्योम
nouveau_cli_work_queue(काष्ठा nouveau_cli *cli, काष्ठा dma_fence *fence,
		       काष्ठा nouveau_cli_work *work)
अणु
	work->fence = dma_fence_get(fence);
	work->cli = cli;
	mutex_lock(&cli->lock);
	list_add_tail(&work->head, &cli->worker);
	अगर (dma_fence_add_callback(fence, &work->cb, nouveau_cli_work_fence))
		nouveau_cli_work_fence(fence, &work->cb);
	mutex_unlock(&cli->lock);
पूर्ण

अटल व्योम
nouveau_cli_fini(काष्ठा nouveau_cli *cli)
अणु
	/* All our channels are dead now, which means all the fences they
	 * own are संकेतled, and all callback functions have been called.
	 *
	 * So, after flushing the workqueue, there should be nothing left.
	 */
	flush_work(&cli->work);
	WARN_ON(!list_empty(&cli->worker));

	usअगर_client_fini(cli);
	nouveau_vmm_fini(&cli->svm);
	nouveau_vmm_fini(&cli->vmm);
	nvअगर_mmu_dtor(&cli->mmu);
	nvअगर_device_dtor(&cli->device);
	mutex_lock(&cli->drm->master.lock);
	nvअगर_client_dtor(&cli->base);
	mutex_unlock(&cli->drm->master.lock);
पूर्ण

अटल पूर्णांक
nouveau_cli_init(काष्ठा nouveau_drm *drm, स्थिर अक्षर *sname,
		 काष्ठा nouveau_cli *cli)
अणु
	अटल स्थिर काष्ठा nvअगर_mclass
	mems[] = अणु
		अणु NVIF_CLASS_MEM_GF100, -1 पूर्ण,
		अणु NVIF_CLASS_MEM_NV50 , -1 पूर्ण,
		अणु NVIF_CLASS_MEM_NV04 , -1 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा nvअगर_mclass
	mmus[] = अणु
		अणु NVIF_CLASS_MMU_GF100, -1 पूर्ण,
		अणु NVIF_CLASS_MMU_NV50 , -1 पूर्ण,
		अणु NVIF_CLASS_MMU_NV04 , -1 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा nvअगर_mclass
	vmms[] = अणु
		अणु NVIF_CLASS_VMM_GP100, -1 पूर्ण,
		अणु NVIF_CLASS_VMM_GM200, -1 पूर्ण,
		अणु NVIF_CLASS_VMM_GF100, -1 पूर्ण,
		अणु NVIF_CLASS_VMM_NV50 , -1 पूर्ण,
		अणु NVIF_CLASS_VMM_NV04 , -1 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	u64 device = nouveau_name(drm->dev);
	पूर्णांक ret;

	snम_लिखो(cli->name, माप(cli->name), "%s", sname);
	cli->drm = drm;
	mutex_init(&cli->mutex);
	usअगर_client_init(cli);

	INIT_WORK(&cli->work, nouveau_cli_work);
	INIT_LIST_HEAD(&cli->worker);
	mutex_init(&cli->lock);

	अगर (cli == &drm->master) अणु
		ret = nvअगर_driver_init(शून्य, nouveau_config, nouveau_debug,
				       cli->name, device, &cli->base);
	पूर्ण अन्यथा अणु
		mutex_lock(&drm->master.lock);
		ret = nvअगर_client_ctor(&drm->master.base, cli->name, device,
				       &cli->base);
		mutex_unlock(&drm->master.lock);
	पूर्ण
	अगर (ret) अणु
		NV_PRINTK(err, cli, "Client allocation failed: %d\n", ret);
		जाओ करोne;
	पूर्ण

	ret = nvअगर_device_ctor(&cli->base.object, "drmDevice", 0, NV_DEVICE,
			       &(काष्ठा nv_device_v0) अणु
					.device = ~0,
			       पूर्ण, माप(काष्ठा nv_device_v0),
			       &cli->device);
	अगर (ret) अणु
		NV_PRINTK(err, cli, "Device allocation failed: %d\n", ret);
		जाओ करोne;
	पूर्ण

	ret = nvअगर_mclass(&cli->device.object, mmus);
	अगर (ret < 0) अणु
		NV_PRINTK(err, cli, "No supported MMU class\n");
		जाओ करोne;
	पूर्ण

	ret = nvअगर_mmu_ctor(&cli->device.object, "drmMmu", mmus[ret].oclass,
			    &cli->mmu);
	अगर (ret) अणु
		NV_PRINTK(err, cli, "MMU allocation failed: %d\n", ret);
		जाओ करोne;
	पूर्ण

	ret = nvअगर_mclass(&cli->mmu.object, vmms);
	अगर (ret < 0) अणु
		NV_PRINTK(err, cli, "No supported VMM class\n");
		जाओ करोne;
	पूर्ण

	ret = nouveau_vmm_init(cli, vmms[ret].oclass, &cli->vmm);
	अगर (ret) अणु
		NV_PRINTK(err, cli, "VMM allocation failed: %d\n", ret);
		जाओ करोne;
	पूर्ण

	ret = nvअगर_mclass(&cli->mmu.object, mems);
	अगर (ret < 0) अणु
		NV_PRINTK(err, cli, "No supported MEM class\n");
		जाओ करोne;
	पूर्ण

	cli->mem = &mems[ret];
	वापस 0;
करोne:
	अगर (ret)
		nouveau_cli_fini(cli);
	वापस ret;
पूर्ण

अटल व्योम
nouveau_accel_ce_fini(काष्ठा nouveau_drm *drm)
अणु
	nouveau_channel_idle(drm->cechan);
	nvअगर_object_dtor(&drm->tपंचांग.copy);
	nouveau_channel_del(&drm->cechan);
पूर्ण

अटल व्योम
nouveau_accel_ce_init(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nvअगर_device *device = &drm->client.device;
	पूर्णांक ret = 0;

	/* Allocate channel that has access to a (preferably async) copy
	 * engine, to use क्रम TTM buffer moves.
	 */
	अगर (device->info.family >= NV_DEVICE_INFO_V0_KEPLER) अणु
		ret = nouveau_channel_new(drm, device,
					  nvअगर_fअगरo_runlist_ce(device), 0,
					  true, &drm->cechan);
	पूर्ण अन्यथा
	अगर (device->info.chipset >= 0xa3 &&
	    device->info.chipset != 0xaa &&
	    device->info.chipset != 0xac) अणु
		/* Prior to Kepler, there's only a single runlist, so all
		 * engines can be accessed from any channel.
		 *
		 * We still want to use a separate channel though.
		 */
		ret = nouveau_channel_new(drm, device, NvDmaFB, NvDmaTT, false,
					  &drm->cechan);
	पूर्ण

	अगर (ret)
		NV_ERROR(drm, "failed to create ce channel, %d\n", ret);
पूर्ण

अटल व्योम
nouveau_accel_gr_fini(काष्ठा nouveau_drm *drm)
अणु
	nouveau_channel_idle(drm->channel);
	nvअगर_object_dtor(&drm->ntfy);
	nvkm_gpuobj_del(&drm->notअगरy);
	nouveau_channel_del(&drm->channel);
पूर्ण

अटल व्योम
nouveau_accel_gr_init(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nvअगर_device *device = &drm->client.device;
	u32 arg0, arg1;
	पूर्णांक ret;

	/* Allocate channel that has access to the graphics engine. */
	अगर (device->info.family >= NV_DEVICE_INFO_V0_KEPLER) अणु
		arg0 = nvअगर_fअगरo_runlist(device, NV_DEVICE_HOST_RUNLIST_ENGINES_GR);
		arg1 = 1;
	पूर्ण अन्यथा अणु
		arg0 = NvDmaFB;
		arg1 = NvDmaTT;
	पूर्ण

	ret = nouveau_channel_new(drm, device, arg0, arg1, false,
				  &drm->channel);
	अगर (ret) अणु
		NV_ERROR(drm, "failed to create kernel channel, %d\n", ret);
		nouveau_accel_gr_fini(drm);
		वापस;
	पूर्ण

	/* A SW class is used on pre-NV50 HW to assist with handling the
	 * synchronisation of page flips, as well as to implement fences
	 * on TNT/TNT2 HW that lacks any kind of support in host.
	 */
	अगर (!drm->channel->nvsw.client && device->info.family < NV_DEVICE_INFO_V0_TESLA) अणु
		ret = nvअगर_object_ctor(&drm->channel->user, "drmNvsw",
				       NVDRM_NVSW, nouveau_abi16_swclass(drm),
				       शून्य, 0, &drm->channel->nvsw);
		अगर (ret == 0) अणु
			काष्ठा nvअगर_push *push = drm->channel->chan.push;
			ret = PUSH_WAIT(push, 2);
			अगर (ret == 0)
				PUSH_NVSQ(push, NV_SW, 0x0000, drm->channel->nvsw.handle);
		पूर्ण

		अगर (ret) अणु
			NV_ERROR(drm, "failed to allocate sw class, %d\n", ret);
			nouveau_accel_gr_fini(drm);
			वापस;
		पूर्ण
	पूर्ण

	/* NvMemoryToMemoryFormat requires a notअगरier ctxdma क्रम some reason,
	 * even अगर notअगरication is never requested, so, allocate a ctxdma on
	 * any GPU where it's possible we'll end up using M2MF क्रम BO moves.
	 */
	अगर (device->info.family < NV_DEVICE_INFO_V0_FERMI) अणु
		ret = nvkm_gpuobj_new(nvxx_device(device), 32, 0, false, शून्य,
				      &drm->notअगरy);
		अगर (ret) अणु
			NV_ERROR(drm, "failed to allocate notifier, %d\n", ret);
			nouveau_accel_gr_fini(drm);
			वापस;
		पूर्ण

		ret = nvअगर_object_ctor(&drm->channel->user, "drmM2mfNtfy",
				       NvNotअगरy0, NV_DMA_IN_MEMORY,
				       &(काष्ठा nv_dma_v0) अणु
						.target = NV_DMA_V0_TARGET_VRAM,
						.access = NV_DMA_V0_ACCESS_RDWR,
						.start = drm->notअगरy->addr,
						.limit = drm->notअगरy->addr + 31
				       पूर्ण, माप(काष्ठा nv_dma_v0),
				       &drm->ntfy);
		अगर (ret) अणु
			nouveau_accel_gr_fini(drm);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nouveau_accel_fini(काष्ठा nouveau_drm *drm)
अणु
	nouveau_accel_ce_fini(drm);
	nouveau_accel_gr_fini(drm);
	अगर (drm->fence)
		nouveau_fence(drm)->dtor(drm);
पूर्ण

अटल व्योम
nouveau_accel_init(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nvअगर_device *device = &drm->client.device;
	काष्ठा nvअगर_sclass *sclass;
	पूर्णांक ret, i, n;

	अगर (nouveau_noaccel)
		वापस;

	/* Initialise global support क्रम channels, and synchronisation. */
	ret = nouveau_channels_init(drm);
	अगर (ret)
		वापस;

	/*XXX: this is crap, but the fence/channel stuff is a little
	 *     backwards in some places.  this will be fixed.
	 */
	ret = n = nvअगर_object_sclass_get(&device->object, &sclass);
	अगर (ret < 0)
		वापस;

	क्रम (ret = -ENOSYS, i = 0; i < n; i++) अणु
		चयन (sclass[i].oclass) अणु
		हाल NV03_CHANNEL_DMA:
			ret = nv04_fence_create(drm);
			अवरोध;
		हाल NV10_CHANNEL_DMA:
			ret = nv10_fence_create(drm);
			अवरोध;
		हाल NV17_CHANNEL_DMA:
		हाल NV40_CHANNEL_DMA:
			ret = nv17_fence_create(drm);
			अवरोध;
		हाल NV50_CHANNEL_GPFIFO:
			ret = nv50_fence_create(drm);
			अवरोध;
		हाल G82_CHANNEL_GPFIFO:
			ret = nv84_fence_create(drm);
			अवरोध;
		हाल FERMI_CHANNEL_GPFIFO:
		हाल KEPLER_CHANNEL_GPFIFO_A:
		हाल KEPLER_CHANNEL_GPFIFO_B:
		हाल MAXWELL_CHANNEL_GPFIFO_A:
		हाल PASCAL_CHANNEL_GPFIFO_A:
		हाल VOLTA_CHANNEL_GPFIFO_A:
		हाल TURING_CHANNEL_GPFIFO_A:
			ret = nvc0_fence_create(drm);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	nvअगर_object_sclass_put(&sclass);
	अगर (ret) अणु
		NV_ERROR(drm, "failed to initialise sync subsystem, %d\n", ret);
		nouveau_accel_fini(drm);
		वापस;
	पूर्ण

	/* Volta requires access to a करोorbell रेजिस्टर क्रम kickoff. */
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_VOLTA) अणु
		ret = nvअगर_user_ctor(device, "drmUsermode");
		अगर (ret)
			वापस;
	पूर्ण

	/* Allocate channels we need to support various functions. */
	nouveau_accel_gr_init(drm);
	nouveau_accel_ce_init(drm);

	/* Initialise accelerated TTM buffer moves. */
	nouveau_bo_move_init(drm);
पूर्ण

अटल व्योम __म_लिखो(2, 3)
nouveau_drm_errorf(काष्ठा nvअगर_object *object, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा nouveau_drm *drm = container_of(object->parent, typeof(*drm), parent);
	काष्ठा va_क्रमmat vaf;
	बहु_सूची va;

	बहु_शुरू(va, fmt);
	vaf.fmt = fmt;
	vaf.va = &va;
	NV_ERROR(drm, "%pV", &vaf);
	बहु_पूर्ण(va);
पूर्ण

अटल व्योम __म_लिखो(2, 3)
nouveau_drm_debugf(काष्ठा nvअगर_object *object, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा nouveau_drm *drm = container_of(object->parent, typeof(*drm), parent);
	काष्ठा va_क्रमmat vaf;
	बहु_सूची va;

	बहु_शुरू(va, fmt);
	vaf.fmt = fmt;
	vaf.va = &va;
	NV_DEBUG(drm, "%pV", &vaf);
	बहु_पूर्ण(va);
पूर्ण

अटल स्थिर काष्ठा nvअगर_parent_func
nouveau_parent = अणु
	.debugf = nouveau_drm_debugf,
	.errorf = nouveau_drm_errorf,
पूर्ण;

अटल पूर्णांक
nouveau_drm_device_init(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm;
	पूर्णांक ret;

	अगर (!(drm = kzalloc(माप(*drm), GFP_KERNEL)))
		वापस -ENOMEM;
	dev->dev_निजी = drm;
	drm->dev = dev;

	nvअगर_parent_ctor(&nouveau_parent, &drm->parent);
	drm->master.base.object.parent = &drm->parent;

	ret = nouveau_cli_init(drm, "DRM-master", &drm->master);
	अगर (ret)
		जाओ fail_alloc;

	ret = nouveau_cli_init(drm, "DRM", &drm->client);
	अगर (ret)
		जाओ fail_master;

	dev->irq_enabled = true;

	nvxx_client(&drm->client.base)->debug =
		nvkm_dbgopt(nouveau_debug, "DRM");

	INIT_LIST_HEAD(&drm->clients);
	spin_lock_init(&drm->tile.lock);

	/* workaround an odd issue on nvc1 by disabling the device's
	 * nosnoop capability.  hopefully won't cause issues until a
	 * better fix is found - assuming there is one...
	 */
	अगर (drm->client.device.info.chipset == 0xc1)
		nvअगर_mask(&drm->client.device.object, 0x00088080, 0x00000800, 0x00000000);

	nouveau_vga_init(drm);

	ret = nouveau_tपंचांग_init(drm);
	अगर (ret)
		जाओ fail_tपंचांग;

	ret = nouveau_bios_init(dev);
	अगर (ret)
		जाओ fail_bios;

	nouveau_accel_init(drm);

	ret = nouveau_display_create(dev);
	अगर (ret)
		जाओ fail_dispctor;

	अगर (dev->mode_config.num_crtc) अणु
		ret = nouveau_display_init(dev, false, false);
		अगर (ret)
			जाओ fail_dispinit;
	पूर्ण

	nouveau_debugfs_init(drm);
	nouveau_hwmon_init(dev);
	nouveau_svm_init(drm);
	nouveau_dmem_init(drm);
	nouveau_fbcon_init(dev);
	nouveau_led_init(dev);

	अगर (nouveau_pmops_runसमय()) अणु
		pm_runसमय_use_स्वतःsuspend(dev->dev);
		pm_runसमय_set_स्वतःsuspend_delay(dev->dev, 5000);
		pm_runसमय_set_active(dev->dev);
		pm_runसमय_allow(dev->dev);
		pm_runसमय_mark_last_busy(dev->dev);
		pm_runसमय_put(dev->dev);
	पूर्ण

	वापस 0;

fail_dispinit:
	nouveau_display_destroy(dev);
fail_dispctor:
	nouveau_accel_fini(drm);
	nouveau_bios_takeकरोwn(dev);
fail_bios:
	nouveau_tपंचांग_fini(drm);
fail_tपंचांग:
	nouveau_vga_fini(drm);
	nouveau_cli_fini(&drm->client);
fail_master:
	nouveau_cli_fini(&drm->master);
fail_alloc:
	nvअगर_parent_dtor(&drm->parent);
	kमुक्त(drm);
	वापस ret;
पूर्ण

अटल व्योम
nouveau_drm_device_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	अगर (nouveau_pmops_runसमय()) अणु
		pm_runसमय_get_sync(dev->dev);
		pm_runसमय_क्रमbid(dev->dev);
	पूर्ण

	nouveau_led_fini(dev);
	nouveau_fbcon_fini(dev);
	nouveau_dmem_fini(drm);
	nouveau_svm_fini(drm);
	nouveau_hwmon_fini(dev);
	nouveau_debugfs_fini(drm);

	अगर (dev->mode_config.num_crtc)
		nouveau_display_fini(dev, false, false);
	nouveau_display_destroy(dev);

	nouveau_accel_fini(drm);
	nouveau_bios_takeकरोwn(dev);

	nouveau_tपंचांग_fini(drm);
	nouveau_vga_fini(drm);

	nouveau_cli_fini(&drm->client);
	nouveau_cli_fini(&drm->master);
	nvअगर_parent_dtor(&drm->parent);
	kमुक्त(drm);
पूर्ण

/*
 * On some Intel PCIe bridge controllers करोing a
 * D0 -> D3hot -> D3cold -> D0 sequence causes Nvidia GPUs to not reappear.
 * Skipping the पूर्णांकermediate D3hot step seems to make it work again. This is
 * probably caused by not meeting the expectation the involved AML code has
 * when the GPU is put पूर्णांकo D3hot state beक्रमe invoking it.
 *
 * This leads to various manअगरestations of this issue:
 *  - AML code execution to घातer on the GPU hits an infinite loop (as the
 *    code रुकोs on device memory to change).
 *  - kernel crashes, as all PCI पढ़ोs वापस -1, which most code isn't able
 *    to handle well enough.
 *
 * In all हालs dmesg will contain at least one line like this:
 * 'nouveau 0000:01:00.0: Refused to change power state, currently in D3'
 * followed by a lot of nouveau समयouts.
 *
 * In the \_SB.PCI0.PEG0.PG00._OFF code deeper करोwn ग_लिखोs bit 0x80 to the not
 * करोcumented PCI config space रेजिस्टर 0x248 of the Intel PCIe bridge
 * controller (0x1901) in order to change the state of the PCIe link between
 * the PCIe port and the GPU. There are alternative code paths using other
 * रेजिस्टरs, which seem to work fine (executed pre Winकरोws 8):
 *  - 0xbc bit 0x20 (खुलाly available करोcumentation claims 'reserved')
 *  - 0xb0 bit 0x10 (link disable)
 * Changing the conditions inside the firmware by poking पूर्णांकo the relevant
 * addresses करोes resolve the issue, but it seemed to be ACPI निजी memory
 * and not any device accessible memory at all, so there is no portable way of
 * changing the conditions.
 * On a XPS 9560 that means bits [0,3] on \CPEX need to be cleared.
 *
 * The only प्रणालीs where this behavior can be seen are hybrid graphics laptops
 * with a secondary Nvidia Maxwell, Pascal or Turing GPU. It's unclear whether
 * this issue only occurs in combination with listed Intel PCIe bridge
 * controllers and the mentioned GPUs or other devices as well.
 *
 * करोcumentation on the PCIe bridge controller can be found in the
 * "7th Generation Intelतऍ Processor Families for H Platforms Datasheet Volume 2"
 * Section "12 PCI Express* Controller (x16) Registers"
 */

अटल व्योम quirk_broken_nv_runpm(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा pci_dev *bridge = pci_upstream_bridge(pdev);

	अगर (!bridge || bridge->venकरोr != PCI_VENDOR_ID_INTEL)
		वापस;

	चयन (bridge->device) अणु
	हाल 0x1901:
		drm->old_pm_cap = pdev->pm_cap;
		pdev->pm_cap = 0;
		NV_INFO(drm, "Disabling PCI power management to avoid bug\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nouveau_drm_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *pent)
अणु
	काष्ठा nvkm_device *device;
	काष्ठा drm_device *drm_dev;
	पूर्णांक ret;

	अगर (vga_चयनeroo_client_probe_defer(pdev))
		वापस -EPROBE_DEFER;

	/* We need to check that the chipset is supported beक्रमe booting
	 * fbdev off the hardware, as there's no way to put it back.
	 */
	ret = nvkm_device_pci_new(pdev, nouveau_config, "error",
				  true, false, 0, &device);
	अगर (ret)
		वापस ret;

	nvkm_device_del(&device);

	/* Remove conflicting drivers (vesafb, efअगरb etc). */
	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "nouveaufb");
	अगर (ret)
		वापस ret;

	ret = nvkm_device_pci_new(pdev, nouveau_config, nouveau_debug,
				  true, true, ~0ULL, &device);
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	अगर (nouveau_atomic)
		driver_pci.driver_features |= DRIVER_ATOMIC;

	drm_dev = drm_dev_alloc(&driver_pci, &pdev->dev);
	अगर (IS_ERR(drm_dev)) अणु
		ret = PTR_ERR(drm_dev);
		जाओ fail_nvkm;
	पूर्ण

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ fail_drm;

	pci_set_drvdata(pdev, drm_dev);

	ret = nouveau_drm_device_init(drm_dev);
	अगर (ret)
		जाओ fail_pci;

	ret = drm_dev_रेजिस्टर(drm_dev, pent->driver_data);
	अगर (ret)
		जाओ fail_drm_dev_init;

	quirk_broken_nv_runpm(pdev);
	वापस 0;

fail_drm_dev_init:
	nouveau_drm_device_fini(drm_dev);
fail_pci:
	pci_disable_device(pdev);
fail_drm:
	drm_dev_put(drm_dev);
fail_nvkm:
	nvkm_device_del(&device);
	वापस ret;
पूर्ण

व्योम
nouveau_drm_device_हटाओ(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_client *client;
	काष्ठा nvkm_device *device;

	drm_dev_unरेजिस्टर(dev);

	dev->irq_enabled = false;
	client = nvxx_client(&drm->client.base);
	device = nvkm_device_find(client->device);

	nouveau_drm_device_fini(dev);
	drm_dev_put(dev);
	nvkm_device_del(&device);
पूर्ण

अटल व्योम
nouveau_drm_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	/* revert our workaround */
	अगर (drm->old_pm_cap)
		pdev->pm_cap = drm->old_pm_cap;
	nouveau_drm_device_हटाओ(dev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक
nouveau_करो_suspend(काष्ठा drm_device *dev, bool runसमय)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा tपंचांग_resource_manager *man;
	पूर्णांक ret;

	nouveau_svm_suspend(drm);
	nouveau_dmem_suspend(drm);
	nouveau_led_suspend(dev);

	अगर (dev->mode_config.num_crtc) अणु
		NV_DEBUG(drm, "suspending console...\n");
		nouveau_fbcon_set_suspend(dev, 1);
		NV_DEBUG(drm, "suspending display...\n");
		ret = nouveau_display_suspend(dev, runसमय);
		अगर (ret)
			वापस ret;
	पूर्ण

	NV_DEBUG(drm, "evicting buffers...\n");

	man = tपंचांग_manager_type(&drm->tपंचांग.bdev, TTM_PL_VRAM);
	tपंचांग_resource_manager_evict_all(&drm->tपंचांग.bdev, man);

	NV_DEBUG(drm, "waiting for kernel channels to go idle...\n");
	अगर (drm->cechan) अणु
		ret = nouveau_channel_idle(drm->cechan);
		अगर (ret)
			जाओ fail_display;
	पूर्ण

	अगर (drm->channel) अणु
		ret = nouveau_channel_idle(drm->channel);
		अगर (ret)
			जाओ fail_display;
	पूर्ण

	NV_DEBUG(drm, "suspending fence...\n");
	अगर (drm->fence && nouveau_fence(drm)->suspend) अणु
		अगर (!nouveau_fence(drm)->suspend(drm)) अणु
			ret = -ENOMEM;
			जाओ fail_display;
		पूर्ण
	पूर्ण

	NV_DEBUG(drm, "suspending object tree...\n");
	ret = nvअगर_client_suspend(&drm->master.base);
	अगर (ret)
		जाओ fail_client;

	वापस 0;

fail_client:
	अगर (drm->fence && nouveau_fence(drm)->resume)
		nouveau_fence(drm)->resume(drm);

fail_display:
	अगर (dev->mode_config.num_crtc) अणु
		NV_DEBUG(drm, "resuming display...\n");
		nouveau_display_resume(dev, runसमय);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_करो_resume(काष्ठा drm_device *dev, bool runसमय)
अणु
	पूर्णांक ret = 0;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	NV_DEBUG(drm, "resuming object tree...\n");
	ret = nvअगर_client_resume(&drm->master.base);
	अगर (ret) अणु
		NV_ERROR(drm, "Client resume failed with error: %d\n", ret);
		वापस ret;
	पूर्ण

	NV_DEBUG(drm, "resuming fence...\n");
	अगर (drm->fence && nouveau_fence(drm)->resume)
		nouveau_fence(drm)->resume(drm);

	nouveau_run_vbios_init(dev);

	अगर (dev->mode_config.num_crtc) अणु
		NV_DEBUG(drm, "resuming display...\n");
		nouveau_display_resume(dev, runसमय);
		NV_DEBUG(drm, "resuming console...\n");
		nouveau_fbcon_set_suspend(dev, 0);
	पूर्ण

	nouveau_led_resume(dev);
	nouveau_dmem_resume(drm);
	nouveau_svm_resume(drm);
	वापस 0;
पूर्ण

पूर्णांक
nouveau_pmops_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (drm_dev->चयन_घातer_state == DRM_SWITCH_POWER_OFF ||
	    drm_dev->चयन_घातer_state == DRM_SWITCH_POWER_DYNAMIC_OFF)
		वापस 0;

	ret = nouveau_करो_suspend(drm_dev, false);
	अगर (ret)
		वापस ret;

	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);
	udelay(200);
	वापस 0;
पूर्ण

पूर्णांक
nouveau_pmops_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (drm_dev->चयन_घातer_state == DRM_SWITCH_POWER_OFF ||
	    drm_dev->चयन_घातer_state == DRM_SWITCH_POWER_DYNAMIC_OFF)
		वापस 0;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;
	pci_set_master(pdev);

	ret = nouveau_करो_resume(drm_dev, false);

	/* Monitors may have been connected / disconnected during suspend */
	nouveau_display_hpd_resume(drm_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_pmops_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	वापस nouveau_करो_suspend(drm_dev, false);
पूर्ण

अटल पूर्णांक
nouveau_pmops_thaw(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	वापस nouveau_करो_resume(drm_dev, false);
पूर्ण

bool
nouveau_pmops_runसमय(व्योम)
अणु
	अगर (nouveau_runसमय_pm == -1)
		वापस nouveau_is_optimus() || nouveau_is_v1_dsm();
	वापस nouveau_runसमय_pm == 1;
पूर्ण

अटल पूर्णांक
nouveau_pmops_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (!nouveau_pmops_runसमय()) अणु
		pm_runसमय_क्रमbid(dev);
		वापस -EBUSY;
	पूर्ण

	nouveau_चयनeroo_optimus_dsm();
	ret = nouveau_करो_suspend(drm_dev, true);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_ignore_hotplug(pdev);
	pci_set_घातer_state(pdev, PCI_D3cold);
	drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_DYNAMIC_OFF;
	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_pmops_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा nvअगर_device *device = &nouveau_drm(drm_dev)->client.device;
	पूर्णांक ret;

	अगर (!nouveau_pmops_runसमय()) अणु
		pm_runसमय_क्रमbid(dev);
		वापस -EBUSY;
	पूर्ण

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;
	pci_set_master(pdev);

	ret = nouveau_करो_resume(drm_dev, true);
	अगर (ret) अणु
		NV_ERROR(drm, "resume failed with: %d\n", ret);
		वापस ret;
	पूर्ण

	/* करो magic */
	nvअगर_mask(&device->object, 0x088488, (1 << 25), (1 << 25));
	drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_ON;

	/* Monitors may have been connected / disconnected during suspend */
	nouveau_display_hpd_resume(drm_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_pmops_runसमय_idle(काष्ठा device *dev)
अणु
	अगर (!nouveau_pmops_runसमय()) अणु
		pm_runसमय_क्रमbid(dev);
		वापस -EBUSY;
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_स्वतःsuspend(dev);
	/* we करोn't want the मुख्य rpm_idle to call suspend - we want to स्वतःsuspend */
	वापस 1;
पूर्ण

अटल पूर्णांक
nouveau_drm_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *fpriv)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_cli *cli;
	अक्षर name[32], क्षणिकe[TASK_COMM_LEN];
	पूर्णांक ret;

	/* need to bring up घातer immediately अगर खोलोing device */
	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस ret;
	पूर्ण

	get_task_comm(क्षणिकe, current);
	snम_लिखो(name, माप(name), "%s[%d]", क्षणिकe, pid_nr(fpriv->pid));

	अगर (!(cli = kzalloc(माप(*cli), GFP_KERNEL))) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	ret = nouveau_cli_init(drm, name, cli);
	अगर (ret)
		जाओ करोne;

	cli->base.super = false;

	fpriv->driver_priv = cli;

	mutex_lock(&drm->client.mutex);
	list_add(&cli->head, &drm->clients);
	mutex_unlock(&drm->client.mutex);

करोne:
	अगर (ret && cli) अणु
		nouveau_cli_fini(cli);
		kमुक्त(cli);
	पूर्ण

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस ret;
पूर्ण

अटल व्योम
nouveau_drm_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *fpriv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(fpriv);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	pm_runसमय_get_sync(dev->dev);

	mutex_lock(&cli->mutex);
	अगर (cli->abi16)
		nouveau_abi16_fini(cli->abi16);
	mutex_unlock(&cli->mutex);

	mutex_lock(&drm->client.mutex);
	list_del(&cli->head);
	mutex_unlock(&drm->client.mutex);

	nouveau_cli_fini(cli);
	kमुक्त(cli);
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc
nouveau_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(NOUVEAU_GETPARAM, nouveau_abi16_ioctl_getparam, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_SETPARAM, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(NOUVEAU_CHANNEL_ALLOC, nouveau_abi16_ioctl_channel_alloc, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_CHANNEL_FREE, nouveau_abi16_ioctl_channel_मुक्त, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_GROBJ_ALLOC, nouveau_abi16_ioctl_grobj_alloc, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_NOTIFIEROBJ_ALLOC, nouveau_abi16_ioctl_notअगरierobj_alloc, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_GPUOBJ_FREE, nouveau_abi16_ioctl_gpuobj_मुक्त, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_SVM_INIT, nouveau_svmm_init, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_SVM_BIND, nouveau_svmm_bind, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_GEM_NEW, nouveau_gem_ioctl_new, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_GEM_PUSHBUF, nouveau_gem_ioctl_pushbuf, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_GEM_CPU_PREP, nouveau_gem_ioctl_cpu_prep, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_GEM_CPU_FINI, nouveau_gem_ioctl_cpu_fini, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(NOUVEAU_GEM_INFO, nouveau_gem_ioctl_info, DRM_RENDER_ALLOW),
पूर्ण;

दीर्घ
nouveau_drm_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_file *filp = file->निजी_data;
	काष्ठा drm_device *dev = filp->minor->dev;
	दीर्घ ret;

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस ret;
	पूर्ण

	चयन (_IOC_NR(cmd) - DRM_COMMAND_BASE) अणु
	हाल DRM_NOUVEAU_NVIF:
		ret = usअगर_ioctl(filp, (व्योम __user *)arg, _IOC_SIZE(cmd));
		अवरोध;
	शेष:
		ret = drm_ioctl(file, cmd, arg);
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations
nouveau_driver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = nouveau_drm_ioctl,
	.mmap = nouveau_tपंचांग_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
#अगर defined(CONFIG_COMPAT)
	.compat_ioctl = nouveau_compat_ioctl,
#पूर्ण_अगर
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा drm_driver
driver_stub = अणु
	.driver_features =
		DRIVER_GEM | DRIVER_MODESET | DRIVER_RENDER
#अगर defined(CONFIG_NOUVEAU_LEGACY_CTX_SUPPORT)
		| DRIVER_KMS_LEGACY_CONTEXT
#पूर्ण_अगर
		,

	.खोलो = nouveau_drm_खोलो,
	.postबंद = nouveau_drm_postबंद,
	.lastबंद = nouveau_vga_lastबंद,

#अगर defined(CONFIG_DEBUG_FS)
	.debugfs_init = nouveau_drm_debugfs_init,
#पूर्ण_अगर

	.ioctls = nouveau_ioctls,
	.num_ioctls = ARRAY_SIZE(nouveau_ioctls),
	.fops = &nouveau_driver_fops,

	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = nouveau_gem_prime_import_sg_table,

	.dumb_create = nouveau_display_dumb_create,
	.dumb_map_offset = nouveau_display_dumb_map_offset,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
#अगर_घोषित GIT_REVISION
	.date = GIT_REVISION,
#अन्यथा
	.date = DRIVER_DATE,
#पूर्ण_अगर
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा pci_device_id
nouveau_drm_pci_table[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID),
		.class = PCI_BASE_CLASS_DISPLAY << 16,
		.class_mask  = 0xff << 16,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_NVIDIA_SGS, PCI_ANY_ID),
		.class = PCI_BASE_CLASS_DISPLAY << 16,
		.class_mask  = 0xff << 16,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम nouveau_display_options(व्योम)
अणु
	DRM_DEBUG_DRIVER("Loading Nouveau with parameters:\n");

	DRM_DEBUG_DRIVER("... tv_disable   : %d\n", nouveau_tv_disable);
	DRM_DEBUG_DRIVER("... ignorelid    : %d\n", nouveau_ignorelid);
	DRM_DEBUG_DRIVER("... duallink     : %d\n", nouveau_duallink);
	DRM_DEBUG_DRIVER("... nofbaccel    : %d\n", nouveau_nofbaccel);
	DRM_DEBUG_DRIVER("... config       : %s\n", nouveau_config);
	DRM_DEBUG_DRIVER("... debug        : %s\n", nouveau_debug);
	DRM_DEBUG_DRIVER("... noaccel      : %d\n", nouveau_noaccel);
	DRM_DEBUG_DRIVER("... modeset      : %d\n", nouveau_modeset);
	DRM_DEBUG_DRIVER("... runpm        : %d\n", nouveau_runसमय_pm);
	DRM_DEBUG_DRIVER("... vram_pushbuf : %d\n", nouveau_vram_pushbuf);
	DRM_DEBUG_DRIVER("... hdmimhz      : %d\n", nouveau_hdmimhz);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops nouveau_pm_ops = अणु
	.suspend = nouveau_pmops_suspend,
	.resume = nouveau_pmops_resume,
	.मुक्तze = nouveau_pmops_मुक्तze,
	.thaw = nouveau_pmops_thaw,
	.घातeroff = nouveau_pmops_मुक्तze,
	.restore = nouveau_pmops_resume,
	.runसमय_suspend = nouveau_pmops_runसमय_suspend,
	.runसमय_resume = nouveau_pmops_runसमय_resume,
	.runसमय_idle = nouveau_pmops_runसमय_idle,
पूर्ण;

अटल काष्ठा pci_driver
nouveau_drm_pci_driver = अणु
	.name = "nouveau",
	.id_table = nouveau_drm_pci_table,
	.probe = nouveau_drm_probe,
	.हटाओ = nouveau_drm_हटाओ,
	.driver.pm = &nouveau_pm_ops,
पूर्ण;

काष्ठा drm_device *
nouveau_platक्रमm_device_create(स्थिर काष्ठा nvkm_device_tegra_func *func,
			       काष्ठा platक्रमm_device *pdev,
			       काष्ठा nvkm_device **pdevice)
अणु
	काष्ठा drm_device *drm;
	पूर्णांक err;

	err = nvkm_device_tegra_new(func, pdev, nouveau_config, nouveau_debug,
				    true, true, ~0ULL, pdevice);
	अगर (err)
		जाओ err_मुक्त;

	drm = drm_dev_alloc(&driver_platक्रमm, &pdev->dev);
	अगर (IS_ERR(drm)) अणु
		err = PTR_ERR(drm);
		जाओ err_मुक्त;
	पूर्ण

	err = nouveau_drm_device_init(drm);
	अगर (err)
		जाओ err_put;

	platक्रमm_set_drvdata(pdev, drm);

	वापस drm;

err_put:
	drm_dev_put(drm);
err_मुक्त:
	nvkm_device_del(pdevice);

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक __init
nouveau_drm_init(व्योम)
अणु
	driver_pci = driver_stub;
	driver_platक्रमm = driver_stub;

	nouveau_display_options();

	अगर (nouveau_modeset == -1) अणु
		अगर (vgacon_text_क्रमce())
			nouveau_modeset = 0;
	पूर्ण

	अगर (!nouveau_modeset)
		वापस 0;

#अगर_घोषित CONFIG_NOUVEAU_PLATFORM_DRIVER
	platक्रमm_driver_रेजिस्टर(&nouveau_platक्रमm_driver);
#पूर्ण_अगर

	nouveau_रेजिस्टर_dsm_handler();
	nouveau_backlight_ctor();

#अगर_घोषित CONFIG_PCI
	वापस pci_रेजिस्टर_driver(&nouveau_drm_pci_driver);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम __निकास
nouveau_drm_निकास(व्योम)
अणु
	अगर (!nouveau_modeset)
		वापस;

#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&nouveau_drm_pci_driver);
#पूर्ण_अगर
	nouveau_backlight_dtor();
	nouveau_unरेजिस्टर_dsm_handler();

#अगर_घोषित CONFIG_NOUVEAU_PLATFORM_DRIVER
	platक्रमm_driver_unरेजिस्टर(&nouveau_platक्रमm_driver);
#पूर्ण_अगर
	अगर (IS_ENABLED(CONFIG_DRM_NOUVEAU_SVM))
		mmu_notअगरier_synchronize();
पूर्ण

module_init(nouveau_drm_init);
module_निकास(nouveau_drm_निकास);

MODULE_DEVICE_TABLE(pci, nouveau_drm_pci_table);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
