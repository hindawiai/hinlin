<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

/**
 * DOC: Interrupt Handling
 *
 * Interrupts generated within GPU hardware उठाओ पूर्णांकerrupt requests that are
 * passed to amdgpu IRQ handler which is responsible क्रम detecting source and
 * type of the पूर्णांकerrupt and dispatching matching handlers. If handling an
 * पूर्णांकerrupt requires calling kernel functions that may sleep processing is
 * dispatched to work handlers.
 *
 * If MSI functionality is not disabled by module parameter then MSI
 * support will be enabled.
 *
 * For GPU पूर्णांकerrupt sources that may be driven by another driver, IRQ करोमुख्य
 * support is used (with mapping between भव and hardware IRQs).
 */

#समावेश <linux/irq.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_ih.h"
#समावेश "atom.h"
#समावेश "amdgpu_connectors.h"
#समावेश "amdgpu_trace.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_ras.h"

#समावेश <linux/pm_runसमय.स>

#अगर_घोषित CONFIG_DRM_AMD_DC
#समावेश "amdgpu_dm_irq.h"
#पूर्ण_अगर

#घोषणा AMDGPU_WAIT_IDLE_TIMEOUT 200

स्थिर अक्षर *soc15_ih_clientid_name[] = अणु
	"IH",
	"SDMA2 or ACP",
	"ATHUB",
	"BIF",
	"SDMA3 or DCE",
	"SDMA4 or ISP",
	"VMC1 or PCIE0",
	"RLC",
	"SDMA0",
	"SDMA1",
	"SE0SH",
	"SE1SH",
	"SE2SH",
	"SE3SH",
	"VCN1 or UVD1",
	"THM",
	"VCN or UVD",
	"SDMA5 or VCE0",
	"VMC",
	"SDMA6 or XDMA",
	"GRBM_CP",
	"ATS",
	"ROM_SMUIO",
	"DF",
	"SDMA7 or VCE1",
	"PWR",
	"reserved",
	"UTCL2",
	"EA",
	"UTCL2LOG",
	"MP0",
	"MP1"
पूर्ण;

/**
 * amdgpu_hotplug_work_func - work handler क्रम display hotplug event
 *
 * @work: work काष्ठा poपूर्णांकer
 *
 * This is the hotplug event work handler (all ASICs).
 * The work माला_लो scheduled from the IRQ handler अगर there
 * was a hotplug पूर्णांकerrupt.  It walks through the connector table
 * and calls hotplug handler क्रम each connector. After this, it sends
 * a DRM hotplug event to alert userspace.
 *
 * This design approach is required in order to defer hotplug event handling
 * from the IRQ handler to a work handler because hotplug handler has to use
 * mutexes which cannot be locked in an IRQ handler (since &mutex_lock may
 * sleep).
 */
अटल व्योम amdgpu_hotplug_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev = container_of(work, काष्ठा amdgpu_device,
						  hotplug_work);
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;

	mutex_lock(&mode_config->mutex);
	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter)
		amdgpu_connector_hotplug(connector);
	drm_connector_list_iter_end(&iter);
	mutex_unlock(&mode_config->mutex);
	/* Just fire off a uevent and let userspace tell us what to करो */
	drm_helper_hpd_irq_event(dev);
पूर्ण

/**
 * amdgpu_irq_disable_all - disable *all* पूर्णांकerrupts
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Disable all types of पूर्णांकerrupts from all sources.
 */
व्योम amdgpu_irq_disable_all(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित दीर्घ irqflags;
	अचिन्हित i, j, k;
	पूर्णांक r;

	spin_lock_irqsave(&adev->irq.lock, irqflags);
	क्रम (i = 0; i < AMDGPU_IRQ_CLIENTID_MAX; ++i) अणु
		अगर (!adev->irq.client[i].sources)
			जारी;

		क्रम (j = 0; j < AMDGPU_MAX_IRQ_SRC_ID; ++j) अणु
			काष्ठा amdgpu_irq_src *src = adev->irq.client[i].sources[j];

			अगर (!src || !src->funcs->set || !src->num_types)
				जारी;

			क्रम (k = 0; k < src->num_types; ++k) अणु
				atomic_set(&src->enabled_types[k], 0);
				r = src->funcs->set(adev, src, k,
						    AMDGPU_IRQ_STATE_DISABLE);
				अगर (r)
					DRM_ERROR("error disabling interrupt (%d)\n",
						  r);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&adev->irq.lock, irqflags);
पूर्ण

/**
 * amdgpu_irq_handler - IRQ handler
 *
 * @irq: IRQ number (unused)
 * @arg: poपूर्णांकer to DRM device
 *
 * IRQ handler क्रम amdgpu driver (all ASICs).
 *
 * Returns:
 * result of handling the IRQ, as defined by &irqवापस_t
 */
irqवापस_t amdgpu_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *) arg;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	irqवापस_t ret;

	ret = amdgpu_ih_process(adev, &adev->irq.ih);
	अगर (ret == IRQ_HANDLED)
		pm_runसमय_mark_last_busy(dev->dev);

	/* For the hardware that cannot enable bअगर ring क्रम both ras_controller_irq
         * and ras_err_evnet_athub_irq ih cookies, the driver has to poll status
	 * रेजिस्टर to check whether the पूर्णांकerrupt is triggered or not, and properly
	 * ack the पूर्णांकerrupt अगर it is there
	 */
	अगर (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__PCIE_BIF)) अणु
		अगर (adev->nbio.ras_funcs &&
		    adev->nbio.ras_funcs->handle_ras_controller_पूर्णांकr_no_bअगरring)
			adev->nbio.ras_funcs->handle_ras_controller_पूर्णांकr_no_bअगरring(adev);

		अगर (adev->nbio.ras_funcs &&
		    adev->nbio.ras_funcs->handle_ras_err_event_athub_पूर्णांकr_no_bअगरring)
			adev->nbio.ras_funcs->handle_ras_err_event_athub_पूर्णांकr_no_bअगरring(adev);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * amdgpu_irq_handle_ih1 - kick of processing क्रम IH1
 *
 * @work: work काष्ठाure in काष्ठा amdgpu_irq
 *
 * Kick of processing IH ring 1.
 */
अटल व्योम amdgpu_irq_handle_ih1(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev = container_of(work, काष्ठा amdgpu_device,
						  irq.ih1_work);

	amdgpu_ih_process(adev, &adev->irq.ih1);
पूर्ण

/**
 * amdgpu_irq_handle_ih2 - kick of processing क्रम IH2
 *
 * @work: work काष्ठाure in काष्ठा amdgpu_irq
 *
 * Kick of processing IH ring 2.
 */
अटल व्योम amdgpu_irq_handle_ih2(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev = container_of(work, काष्ठा amdgpu_device,
						  irq.ih2_work);

	amdgpu_ih_process(adev, &adev->irq.ih2);
पूर्ण

/**
 * amdgpu_irq_handle_ih_soft - kick of processing क्रम ih_soft
 *
 * @work: work काष्ठाure in काष्ठा amdgpu_irq
 *
 * Kick of processing IH soft ring.
 */
अटल व्योम amdgpu_irq_handle_ih_soft(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev = container_of(work, काष्ठा amdgpu_device,
						  irq.ih_soft_work);

	amdgpu_ih_process(adev, &adev->irq.ih_soft);
पूर्ण

/**
 * amdgpu_msi_ok - check whether MSI functionality is enabled
 *
 * @adev: amdgpu device poपूर्णांकer (unused)
 *
 * Checks whether MSI functionality has been disabled via module parameter
 * (all ASICs).
 *
 * Returns:
 * *true* अगर MSIs are allowed to be enabled or *false* otherwise
 */
अटल bool amdgpu_msi_ok(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_msi == 1)
		वापस true;
	अन्यथा अगर (amdgpu_msi == 0)
		वापस false;

	वापस true;
पूर्ण

/**
 * amdgpu_irq_init - initialize पूर्णांकerrupt handling
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Sets up work functions क्रम hotplug and reset पूर्णांकerrupts, enables MSI
 * functionality, initializes vblank, hotplug and reset पूर्णांकerrupt handling.
 *
 * Returns:
 * 0 on success or error code on failure
 */
पूर्णांक amdgpu_irq_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r = 0;

	spin_lock_init(&adev->irq.lock);

	/* Enable MSI अगर not disabled by module parameter */
	adev->irq.msi_enabled = false;

	अगर (amdgpu_msi_ok(adev)) अणु
		पूर्णांक nvec = pci_msix_vec_count(adev->pdev);
		अचिन्हित पूर्णांक flags;

		अगर (nvec <= 0) अणु
			flags = PCI_IRQ_MSI;
		पूर्ण अन्यथा अणु
			flags = PCI_IRQ_MSI | PCI_IRQ_MSIX;
		पूर्ण
		/* we only need one vector */
		nvec = pci_alloc_irq_vectors(adev->pdev, 1, 1, flags);
		अगर (nvec > 0) अणु
			adev->irq.msi_enabled = true;
			dev_dbg(adev->dev, "using MSI/MSI-X.\n");
		पूर्ण
	पूर्ण

	अगर (!amdgpu_device_has_dc_support(adev)) अणु
		अगर (!adev->enable_भव_display)
			/* Disable vblank IRQs aggressively क्रम घातer-saving */
			/* XXX: can this be enabled क्रम DC? */
			adev_to_drm(adev)->vblank_disable_immediate = true;

		r = drm_vblank_init(adev_to_drm(adev), adev->mode_info.num_crtc);
		अगर (r)
			वापस r;

		/* Pre-DCE11 */
		INIT_WORK(&adev->hotplug_work,
				amdgpu_hotplug_work_func);
	पूर्ण

	INIT_WORK(&adev->irq.ih1_work, amdgpu_irq_handle_ih1);
	INIT_WORK(&adev->irq.ih2_work, amdgpu_irq_handle_ih2);
	INIT_WORK(&adev->irq.ih_soft_work, amdgpu_irq_handle_ih_soft);

	adev->irq.installed = true;
	/* Use vector 0 क्रम MSI-X */
	r = drm_irq_install(adev_to_drm(adev), pci_irq_vector(adev->pdev, 0));
	अगर (r) अणु
		adev->irq.installed = false;
		अगर (!amdgpu_device_has_dc_support(adev))
			flush_work(&adev->hotplug_work);
		वापस r;
	पूर्ण
	adev_to_drm(adev)->max_vblank_count = 0x00ffffff;

	DRM_DEBUG("amdgpu: irq initialized.\n");
	वापस 0;
पूर्ण

/**
 * amdgpu_irq_fini - shut करोwn पूर्णांकerrupt handling
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Tears करोwn work functions क्रम hotplug and reset पूर्णांकerrupts, disables MSI
 * functionality, shuts करोwn vblank, hotplug and reset पूर्णांकerrupt handling,
 * turns off पूर्णांकerrupts from all sources (all ASICs).
 */
व्योम amdgpu_irq_fini(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i, j;

	अगर (adev->irq.installed) अणु
		drm_irq_uninstall(adev_to_drm(adev));
		adev->irq.installed = false;
		अगर (adev->irq.msi_enabled)
			pci_मुक्त_irq_vectors(adev->pdev);
		अगर (!amdgpu_device_has_dc_support(adev))
			flush_work(&adev->hotplug_work);
	पूर्ण

	क्रम (i = 0; i < AMDGPU_IRQ_CLIENTID_MAX; ++i) अणु
		अगर (!adev->irq.client[i].sources)
			जारी;

		क्रम (j = 0; j < AMDGPU_MAX_IRQ_SRC_ID; ++j) अणु
			काष्ठा amdgpu_irq_src *src = adev->irq.client[i].sources[j];

			अगर (!src)
				जारी;

			kमुक्त(src->enabled_types);
			src->enabled_types = शून्य;
		पूर्ण
		kमुक्त(adev->irq.client[i].sources);
		adev->irq.client[i].sources = शून्य;
	पूर्ण
पूर्ण

/**
 * amdgpu_irq_add_id - रेजिस्टर IRQ source
 *
 * @adev: amdgpu device poपूर्णांकer
 * @client_id: client id
 * @src_id: source id
 * @source: IRQ source poपूर्णांकer
 *
 * Registers IRQ source on a client.
 *
 * Returns:
 * 0 on success or error code otherwise
 */
पूर्णांक amdgpu_irq_add_id(काष्ठा amdgpu_device *adev,
		      अचिन्हित client_id, अचिन्हित src_id,
		      काष्ठा amdgpu_irq_src *source)
अणु
	अगर (client_id >= AMDGPU_IRQ_CLIENTID_MAX)
		वापस -EINVAL;

	अगर (src_id >= AMDGPU_MAX_IRQ_SRC_ID)
		वापस -EINVAL;

	अगर (!source->funcs)
		वापस -EINVAL;

	अगर (!adev->irq.client[client_id].sources) अणु
		adev->irq.client[client_id].sources =
			kसुस्मृति(AMDGPU_MAX_IRQ_SRC_ID,
				माप(काष्ठा amdgpu_irq_src *),
				GFP_KERNEL);
		अगर (!adev->irq.client[client_id].sources)
			वापस -ENOMEM;
	पूर्ण

	अगर (adev->irq.client[client_id].sources[src_id] != शून्य)
		वापस -EINVAL;

	अगर (source->num_types && !source->enabled_types) अणु
		atomic_t *types;

		types = kसुस्मृति(source->num_types, माप(atomic_t),
				GFP_KERNEL);
		अगर (!types)
			वापस -ENOMEM;

		source->enabled_types = types;
	पूर्ण

	adev->irq.client[client_id].sources[src_id] = source;
	वापस 0;
पूर्ण

/**
 * amdgpu_irq_dispatch - dispatch IRQ to IP blocks
 *
 * @adev: amdgpu device poपूर्णांकer
 * @ih: पूर्णांकerrupt ring instance
 *
 * Dispatches IRQ to IP blocks.
 */
व्योम amdgpu_irq_dispatch(काष्ठा amdgpu_device *adev,
			 काष्ठा amdgpu_ih_ring *ih)
अणु
	u32 ring_index = ih->rptr >> 2;
	काष्ठा amdgpu_iv_entry entry;
	अचिन्हित client_id, src_id;
	काष्ठा amdgpu_irq_src *src;
	bool handled = false;
	पूर्णांक r;

	entry.ih = ih;
	entry.iv_entry = (स्थिर uपूर्णांक32_t *)&ih->ring[ring_index];
	amdgpu_ih_decode_iv(adev, &entry);

	trace_amdgpu_iv(ih - &adev->irq.ih, &entry);

	client_id = entry.client_id;
	src_id = entry.src_id;

	अगर (client_id >= AMDGPU_IRQ_CLIENTID_MAX) अणु
		DRM_DEBUG("Invalid client_id in IV: %d\n", client_id);

	पूर्ण अन्यथा	अगर (src_id >= AMDGPU_MAX_IRQ_SRC_ID) अणु
		DRM_DEBUG("Invalid src_id in IV: %d\n", src_id);

	पूर्ण अन्यथा अगर ((client_id == AMDGPU_IRQ_CLIENTID_LEGACY) &&
		   adev->irq.virq[src_id]) अणु
		generic_handle_irq(irq_find_mapping(adev->irq.करोमुख्य, src_id));

	पूर्ण अन्यथा अगर (!adev->irq.client[client_id].sources) अणु
		DRM_DEBUG("Unregistered interrupt client_id: %d src_id: %d\n",
			  client_id, src_id);

	पूर्ण अन्यथा अगर ((src = adev->irq.client[client_id].sources[src_id])) अणु
		r = src->funcs->process(adev, src, &entry);
		अगर (r < 0)
			DRM_ERROR("error processing interrupt (%d)\n", r);
		अन्यथा अगर (r)
			handled = true;

	पूर्ण अन्यथा अणु
		DRM_DEBUG("Unhandled interrupt src_id: %d\n", src_id);
	पूर्ण

	/* Send it to amdkfd as well अगर it isn't alपढ़ोy handled */
	अगर (!handled)
		amdgpu_amdkfd_पूर्णांकerrupt(adev, entry.iv_entry);
पूर्ण

/**
 * amdgpu_irq_delegate - delegate IV to soft IH ring
 *
 * @adev: amdgpu device poपूर्णांकer
 * @entry: IV entry
 * @num_dw: size of IV
 *
 * Delegate the IV to the soft IH ring and schedule processing of it. Used
 * अगर the hardware delegation to IH1 or IH2 करोesn't work क्रम some reason.
 */
व्योम amdgpu_irq_delegate(काष्ठा amdgpu_device *adev,
			 काष्ठा amdgpu_iv_entry *entry,
			 अचिन्हित पूर्णांक num_dw)
अणु
	amdgpu_ih_ring_ग_लिखो(&adev->irq.ih_soft, entry->iv_entry, num_dw);
	schedule_work(&adev->irq.ih_soft_work);
पूर्ण

/**
 * amdgpu_irq_update - update hardware पूर्णांकerrupt state
 *
 * @adev: amdgpu device poपूर्णांकer
 * @src: पूर्णांकerrupt source poपूर्णांकer
 * @type: type of पूर्णांकerrupt
 *
 * Updates पूर्णांकerrupt state क्रम the specअगरic source (all ASICs).
 */
पूर्णांक amdgpu_irq_update(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_irq_src *src, अचिन्हित type)
अणु
	अचिन्हित दीर्घ irqflags;
	क्रमागत amdgpu_पूर्णांकerrupt_state state;
	पूर्णांक r;

	spin_lock_irqsave(&adev->irq.lock, irqflags);

	/* We need to determine after taking the lock, otherwise
	   we might disable just enabled पूर्णांकerrupts again */
	अगर (amdgpu_irq_enabled(adev, src, type))
		state = AMDGPU_IRQ_STATE_ENABLE;
	अन्यथा
		state = AMDGPU_IRQ_STATE_DISABLE;

	r = src->funcs->set(adev, src, type, state);
	spin_unlock_irqrestore(&adev->irq.lock, irqflags);
	वापस r;
पूर्ण

/**
 * amdgpu_irq_gpu_reset_resume_helper - update पूर्णांकerrupt states on all sources
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Updates state of all types of पूर्णांकerrupts on all sources on resume after
 * reset.
 */
व्योम amdgpu_irq_gpu_reset_resume_helper(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j, k;

	क्रम (i = 0; i < AMDGPU_IRQ_CLIENTID_MAX; ++i) अणु
		अगर (!adev->irq.client[i].sources)
			जारी;

		क्रम (j = 0; j < AMDGPU_MAX_IRQ_SRC_ID; ++j) अणु
			काष्ठा amdgpu_irq_src *src = adev->irq.client[i].sources[j];

			अगर (!src || !src->funcs || !src->funcs->set)
				जारी;
			क्रम (k = 0; k < src->num_types; k++)
				amdgpu_irq_update(adev, src, k);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * amdgpu_irq_get - enable पूर्णांकerrupt
 *
 * @adev: amdgpu device poपूर्णांकer
 * @src: पूर्णांकerrupt source poपूर्णांकer
 * @type: type of पूर्णांकerrupt
 *
 * Enables specअगरied type of पूर्णांकerrupt on the specअगरied source (all ASICs).
 *
 * Returns:
 * 0 on success or error code otherwise
 */
पूर्णांक amdgpu_irq_get(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *src,
		   अचिन्हित type)
अणु
	अगर (!adev_to_drm(adev)->irq_enabled)
		वापस -ENOENT;

	अगर (type >= src->num_types)
		वापस -EINVAL;

	अगर (!src->enabled_types || !src->funcs->set)
		वापस -EINVAL;

	अगर (atomic_inc_वापस(&src->enabled_types[type]) == 1)
		वापस amdgpu_irq_update(adev, src, type);

	वापस 0;
पूर्ण

/**
 * amdgpu_irq_put - disable पूर्णांकerrupt
 *
 * @adev: amdgpu device poपूर्णांकer
 * @src: पूर्णांकerrupt source poपूर्णांकer
 * @type: type of पूर्णांकerrupt
 *
 * Enables specअगरied type of पूर्णांकerrupt on the specअगरied source (all ASICs).
 *
 * Returns:
 * 0 on success or error code otherwise
 */
पूर्णांक amdgpu_irq_put(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *src,
		   अचिन्हित type)
अणु
	अगर (!adev_to_drm(adev)->irq_enabled)
		वापस -ENOENT;

	अगर (type >= src->num_types)
		वापस -EINVAL;

	अगर (!src->enabled_types || !src->funcs->set)
		वापस -EINVAL;

	अगर (atomic_dec_and_test(&src->enabled_types[type]))
		वापस amdgpu_irq_update(adev, src, type);

	वापस 0;
पूर्ण

/**
 * amdgpu_irq_enabled - check whether पूर्णांकerrupt is enabled or not
 *
 * @adev: amdgpu device poपूर्णांकer
 * @src: पूर्णांकerrupt source poपूर्णांकer
 * @type: type of पूर्णांकerrupt
 *
 * Checks whether the given type of पूर्णांकerrupt is enabled on the given source.
 *
 * Returns:
 * *true* अगर पूर्णांकerrupt is enabled, *false* अगर पूर्णांकerrupt is disabled or on
 * invalid parameters
 */
bool amdgpu_irq_enabled(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *src,
			अचिन्हित type)
अणु
	अगर (!adev_to_drm(adev)->irq_enabled)
		वापस false;

	अगर (type >= src->num_types)
		वापस false;

	अगर (!src->enabled_types || !src->funcs->set)
		वापस false;

	वापस !!atomic_पढ़ो(&src->enabled_types[type]);
पूर्ण

/* XXX: Generic IRQ handling */
अटल व्योम amdgpu_irq_mask(काष्ठा irq_data *irqd)
अणु
	/* XXX */
पूर्ण

अटल व्योम amdgpu_irq_unmask(काष्ठा irq_data *irqd)
अणु
	/* XXX */
पूर्ण

/* amdgpu hardware पूर्णांकerrupt chip descriptor */
अटल काष्ठा irq_chip amdgpu_irq_chip = अणु
	.name = "amdgpu-ih",
	.irq_mask = amdgpu_irq_mask,
	.irq_unmask = amdgpu_irq_unmask,
पूर्ण;

/**
 * amdgpu_irqकरोमुख्य_map - create mapping between भव and hardware IRQ numbers
 *
 * @d: amdgpu IRQ करोमुख्य poपूर्णांकer (unused)
 * @irq: भव IRQ number
 * @hwirq: hardware irq number
 *
 * Current implementation assigns simple पूर्णांकerrupt handler to the given भव
 * IRQ.
 *
 * Returns:
 * 0 on success or error code otherwise
 */
अटल पूर्णांक amdgpu_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d,
				अचिन्हित पूर्णांक irq, irq_hw_number_t hwirq)
अणु
	अगर (hwirq >= AMDGPU_MAX_IRQ_SRC_ID)
		वापस -EPERM;

	irq_set_chip_and_handler(irq,
				 &amdgpu_irq_chip, handle_simple_irq);
	वापस 0;
पूर्ण

/* Implementation of methods क्रम amdgpu IRQ करोमुख्य */
अटल स्थिर काष्ठा irq_करोमुख्य_ops amdgpu_hw_irqकरोमुख्य_ops = अणु
	.map = amdgpu_irqकरोमुख्य_map,
पूर्ण;

/**
 * amdgpu_irq_add_करोमुख्य - create a linear IRQ करोमुख्य
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Creates an IRQ करोमुख्य क्रम GPU पूर्णांकerrupt sources
 * that may be driven by another driver (e.g., ACP).
 *
 * Returns:
 * 0 on success or error code otherwise
 */
पूर्णांक amdgpu_irq_add_करोमुख्य(काष्ठा amdgpu_device *adev)
अणु
	adev->irq.करोमुख्य = irq_करोमुख्य_add_linear(शून्य, AMDGPU_MAX_IRQ_SRC_ID,
						 &amdgpu_hw_irqकरोमुख्य_ops, adev);
	अगर (!adev->irq.करोमुख्य) अणु
		DRM_ERROR("GPU irq add domain failed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_irq_हटाओ_करोमुख्य - हटाओ the IRQ करोमुख्य
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Removes the IRQ करोमुख्य क्रम GPU पूर्णांकerrupt sources
 * that may be driven by another driver (e.g., ACP).
 */
व्योम amdgpu_irq_हटाओ_करोमुख्य(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->irq.करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(adev->irq.करोमुख्य);
		adev->irq.करोमुख्य = शून्य;
	पूर्ण
पूर्ण

/**
 * amdgpu_irq_create_mapping - create mapping between करोमुख्य Linux IRQs
 *
 * @adev: amdgpu device poपूर्णांकer
 * @src_id: IH source id
 *
 * Creates mapping between a करोमुख्य IRQ (GPU IH src id) and a Linux IRQ
 * Use this क्रम components that generate a GPU पूर्णांकerrupt, but are driven
 * by a dअगरferent driver (e.g., ACP).
 *
 * Returns:
 * Linux IRQ
 */
अचिन्हित amdgpu_irq_create_mapping(काष्ठा amdgpu_device *adev, अचिन्हित src_id)
अणु
	adev->irq.virq[src_id] = irq_create_mapping(adev->irq.करोमुख्य, src_id);

	वापस adev->irq.virq[src_id];
पूर्ण
