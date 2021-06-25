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

#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_kms.h"
#समावेश "radeon_reg.h"


#घोषणा RADEON_WAIT_IDLE_TIMEOUT 200

/*
 * radeon_driver_irq_handler_kms - irq handler क्रम KMS
 *
 * This is the irq handler क्रम the radeon KMS driver (all asics).
 * radeon_irq_process is a macro that poपूर्णांकs to the per-asic
 * irq handler callback.
 */
irqवापस_t radeon_driver_irq_handler_kms(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *) arg;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	irqवापस_t ret;

	ret = radeon_irq_process(rdev);
	अगर (ret == IRQ_HANDLED)
		pm_runसमय_mark_last_busy(dev->dev);
	वापस ret;
पूर्ण

/*
 * Handle hotplug events outside the पूर्णांकerrupt handler proper.
 */
/**
 * radeon_hotplug_work_func - display hotplug work handler
 *
 * @work: work काष्ठा
 *
 * This is the hot plug event work handler (all asics).
 * The work माला_लो scheduled from the irq handler अगर there
 * was a hot plug पूर्णांकerrupt.  It walks the connector table
 * and calls the hotplug handler क्रम each one, then sends
 * a drm hotplug event to alert userspace.
 */
अटल व्योम radeon_hotplug_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_device *rdev = container_of(work, काष्ठा radeon_device,
						  hotplug_work.work);
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_connector *connector;

	/* we can race here at startup, some boards seem to trigger
	 * hotplug irqs when they shouldn't. */
	अगर (!rdev->mode_info.mode_config_initialized)
		वापस;

	mutex_lock(&mode_config->mutex);
	list_क्रम_each_entry(connector, &mode_config->connector_list, head)
		radeon_connector_hotplug(connector);
	mutex_unlock(&mode_config->mutex);
	/* Just fire off a uevent and let userspace tell us what to करो */
	drm_helper_hpd_irq_event(dev);
पूर्ण

अटल व्योम radeon_dp_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_device *rdev = container_of(work, काष्ठा radeon_device,
						  dp_work);
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_connector *connector;

	/* this should take a mutex */
	list_क्रम_each_entry(connector, &mode_config->connector_list, head)
		radeon_connector_hotplug(connector);
पूर्ण
/**
 * radeon_driver_irq_preinstall_kms - drm irq preinstall callback
 *
 * @dev: drm dev poपूर्णांकer
 *
 * Gets the hw पढ़ोy to enable irqs (all asics).
 * This function disables all पूर्णांकerrupt sources on the GPU.
 */
व्योम radeon_driver_irq_preinstall_kms(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित i;

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	/* Disable *all* पूर्णांकerrupts */
	क्रम (i = 0; i < RADEON_NUM_RINGS; i++)
		atomic_set(&rdev->irq.ring_पूर्णांक[i], 0);
	rdev->irq.dpm_thermal = false;
	क्रम (i = 0; i < RADEON_MAX_HPD_PINS; i++)
		rdev->irq.hpd[i] = false;
	क्रम (i = 0; i < RADEON_MAX_CRTCS; i++) अणु
		rdev->irq.crtc_vblank_पूर्णांक[i] = false;
		atomic_set(&rdev->irq.pflip[i], 0);
		rdev->irq.afmt[i] = false;
	पूर्ण
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	/* Clear bits */
	radeon_irq_process(rdev);
पूर्ण

/**
 * radeon_driver_irq_postinstall_kms - drm irq preinstall callback
 *
 * @dev: drm dev poपूर्णांकer
 *
 * Handles stuff to be करोne after enabling irqs (all asics).
 * Returns 0 on success.
 */
पूर्णांक radeon_driver_irq_postinstall_kms(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (ASIC_IS_AVIVO(rdev))
		dev->max_vblank_count = 0x00ffffff;
	अन्यथा
		dev->max_vblank_count = 0x001fffff;

	वापस 0;
पूर्ण

/**
 * radeon_driver_irq_uninstall_kms - drm irq uninstall callback
 *
 * @dev: drm dev poपूर्णांकer
 *
 * This function disables all पूर्णांकerrupt sources on the GPU (all asics).
 */
व्योम radeon_driver_irq_uninstall_kms(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित i;

	अगर (rdev == शून्य) अणु
		वापस;
	पूर्ण
	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	/* Disable *all* पूर्णांकerrupts */
	क्रम (i = 0; i < RADEON_NUM_RINGS; i++)
		atomic_set(&rdev->irq.ring_पूर्णांक[i], 0);
	rdev->irq.dpm_thermal = false;
	क्रम (i = 0; i < RADEON_MAX_HPD_PINS; i++)
		rdev->irq.hpd[i] = false;
	क्रम (i = 0; i < RADEON_MAX_CRTCS; i++) अणु
		rdev->irq.crtc_vblank_पूर्णांक[i] = false;
		atomic_set(&rdev->irq.pflip[i], 0);
		rdev->irq.afmt[i] = false;
	पूर्ण
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
पूर्ण

/**
 * radeon_msi_ok - asic specअगरic msi checks
 *
 * @rdev: radeon device poपूर्णांकer
 *
 * Handles asic specअगरic MSI checks to determine अगर
 * MSIs should be enabled on a particular chip (all asics).
 * Returns true अगर MSIs should be enabled, false अगर MSIs
 * should not be enabled.
 */
अटल bool radeon_msi_ok(काष्ठा radeon_device *rdev)
अणु
	/* RV370/RV380 was first asic with MSI support */
	अगर (rdev->family < CHIP_RV380)
		वापस false;

	/* MSIs करोn't work on AGP */
	अगर (rdev->flags & RADEON_IS_AGP)
		वापस false;

	/*
	 * Older chips have a HW limitation, they can only generate 40 bits
	 * of address क्रम "64-bit" MSIs which अवरोधs on some platक्रमms, notably
	 * IBM POWER servers, so we limit them
	 */
	अगर (rdev->family < CHIP_BONAIRE) अणु
		dev_info(rdev->dev, "radeon: MSI limited to 32-bit\n");
		rdev->pdev->no_64bit_msi = 1;
	पूर्ण

	/* क्रमce MSI on */
	अगर (radeon_msi == 1)
		वापस true;
	अन्यथा अगर (radeon_msi == 0)
		वापस false;

	/* Quirks */
	/* HP RS690 only seems to work with MSIs. */
	अगर ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subप्रणाली_venकरोr == 0x103c) &&
	    (rdev->pdev->subप्रणाली_device == 0x30c2))
		वापस true;

	/* Dell RS690 only seems to work with MSIs. */
	अगर ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subप्रणाली_venकरोr == 0x1028) &&
	    (rdev->pdev->subप्रणाली_device == 0x01fc))
		वापस true;

	/* Dell RS690 only seems to work with MSIs. */
	अगर ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subप्रणाली_venकरोr == 0x1028) &&
	    (rdev->pdev->subप्रणाली_device == 0x01fd))
		वापस true;

	/* Gateway RS690 only seems to work with MSIs. */
	अगर ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subप्रणाली_venकरोr == 0x107b) &&
	    (rdev->pdev->subप्रणाली_device == 0x0185))
		वापस true;

	/* try and enable MSIs by शेष on all RS690s */
	अगर (rdev->family == CHIP_RS690)
		वापस true;

	/* RV515 seems to have MSI issues where it loses
	 * MSI rearms occasionally. This leads to lockups and मुक्तzes.
	 * disable it by शेष.
	 */
	अगर (rdev->family == CHIP_RV515)
		वापस false;
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		/* APUs work fine with MSIs */
		अगर (rdev->family >= CHIP_PALM)
			वापस true;
		/* lots of IGPs have problems with MSIs */
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * radeon_irq_kms_init - init driver पूर्णांकerrupt info
 *
 * @rdev: radeon device poपूर्णांकer
 *
 * Sets up the work irq handlers, vblank init, MSIs, etc. (all asics).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक radeon_irq_kms_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r = 0;

	spin_lock_init(&rdev->irq.lock);

	/* Disable vblank irqs aggressively क्रम घातer-saving */
	rdev->ddev->vblank_disable_immediate = true;

	r = drm_vblank_init(rdev->ddev, rdev->num_crtc);
	अगर (r) अणु
		वापस r;
	पूर्ण

	/* enable msi */
	rdev->msi_enabled = 0;

	अगर (radeon_msi_ok(rdev)) अणु
		पूर्णांक ret = pci_enable_msi(rdev->pdev);
		अगर (!ret) अणु
			rdev->msi_enabled = 1;
			dev_info(rdev->dev, "radeon: using MSI.\n");
		पूर्ण
	पूर्ण

	INIT_DELAYED_WORK(&rdev->hotplug_work, radeon_hotplug_work_func);
	INIT_WORK(&rdev->dp_work, radeon_dp_work_func);
	INIT_WORK(&rdev->audio_work, r600_audio_update_hdmi);

	rdev->irq.installed = true;
	r = drm_irq_install(rdev->ddev, rdev->pdev->irq);
	अगर (r) अणु
		rdev->irq.installed = false;
		flush_delayed_work(&rdev->hotplug_work);
		वापस r;
	पूर्ण

	DRM_INFO("radeon: irq initialized.\n");
	वापस 0;
पूर्ण

/**
 * radeon_irq_kms_fini - tear करोwn driver पूर्णांकerrupt info
 *
 * @rdev: radeon device poपूर्णांकer
 *
 * Tears करोwn the work irq handlers, vblank handlers, MSIs, etc. (all asics).
 */
व्योम radeon_irq_kms_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->irq.installed) अणु
		drm_irq_uninstall(rdev->ddev);
		rdev->irq.installed = false;
		अगर (rdev->msi_enabled)
			pci_disable_msi(rdev->pdev);
		flush_delayed_work(&rdev->hotplug_work);
	पूर्ण
पूर्ण

/**
 * radeon_irq_kms_sw_irq_get - enable software पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring whose पूर्णांकerrupt you want to enable
 *
 * Enables the software पूर्णांकerrupt क्रम a specअगरic ring (all asics).
 * The software पूर्णांकerrupt is generally used to संकेत a fence on
 * a particular ring.
 */
व्योम radeon_irq_kms_sw_irq_get(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	अगर (atomic_inc_वापस(&rdev->irq.ring_पूर्णांक[ring]) == 1) अणु
		spin_lock_irqsave(&rdev->irq.lock, irqflags);
		radeon_irq_set(rdev);
		spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	पूर्ण
पूर्ण

/**
 * radeon_irq_kms_sw_irq_get_delayed - enable software पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring whose पूर्णांकerrupt you want to enable
 *
 * Enables the software पूर्णांकerrupt क्रम a specअगरic ring (all asics).
 * The software पूर्णांकerrupt is generally used to संकेत a fence on
 * a particular ring.
 */
bool radeon_irq_kms_sw_irq_get_delayed(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	वापस atomic_inc_वापस(&rdev->irq.ring_पूर्णांक[ring]) == 1;
पूर्ण

/**
 * radeon_irq_kms_sw_irq_put - disable software पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring whose पूर्णांकerrupt you want to disable
 *
 * Disables the software पूर्णांकerrupt क्रम a specअगरic ring (all asics).
 * The software पूर्णांकerrupt is generally used to संकेत a fence on
 * a particular ring.
 */
व्योम radeon_irq_kms_sw_irq_put(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	अगर (atomic_dec_and_test(&rdev->irq.ring_पूर्णांक[ring])) अणु
		spin_lock_irqsave(&rdev->irq.lock, irqflags);
		radeon_irq_set(rdev);
		spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	पूर्ण
पूर्ण

/**
 * radeon_irq_kms_pflip_irq_get - enable pageflip पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @crtc: crtc whose पूर्णांकerrupt you want to enable
 *
 * Enables the pageflip पूर्णांकerrupt क्रम a specअगरic crtc (all asics).
 * For pageflips we use the vblank पूर्णांकerrupt source.
 */
व्योम radeon_irq_kms_pflip_irq_get(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (crtc < 0 || crtc >= rdev->num_crtc)
		वापस;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	अगर (atomic_inc_वापस(&rdev->irq.pflip[crtc]) == 1) अणु
		spin_lock_irqsave(&rdev->irq.lock, irqflags);
		radeon_irq_set(rdev);
		spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	पूर्ण
पूर्ण

/**
 * radeon_irq_kms_pflip_irq_put - disable pageflip पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @crtc: crtc whose पूर्णांकerrupt you want to disable
 *
 * Disables the pageflip पूर्णांकerrupt क्रम a specअगरic crtc (all asics).
 * For pageflips we use the vblank पूर्णांकerrupt source.
 */
व्योम radeon_irq_kms_pflip_irq_put(काष्ठा radeon_device *rdev, पूर्णांक crtc)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (crtc < 0 || crtc >= rdev->num_crtc)
		वापस;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	अगर (atomic_dec_and_test(&rdev->irq.pflip[crtc])) अणु
		spin_lock_irqsave(&rdev->irq.lock, irqflags);
		radeon_irq_set(rdev);
		spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	पूर्ण
पूर्ण

/**
 * radeon_irq_kms_enable_afmt - enable audio क्रमmat change पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @block: afmt block whose पूर्णांकerrupt you want to enable
 *
 * Enables the afmt change पूर्णांकerrupt क्रम a specअगरic afmt block (all asics).
 */
व्योम radeon_irq_kms_enable_afmt(काष्ठा radeon_device *rdev, पूर्णांक block)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	rdev->irq.afmt[block] = true;
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);

पूर्ण

/**
 * radeon_irq_kms_disable_afmt - disable audio क्रमmat change पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @block: afmt block whose पूर्णांकerrupt you want to disable
 *
 * Disables the afmt change पूर्णांकerrupt क्रम a specअगरic afmt block (all asics).
 */
व्योम radeon_irq_kms_disable_afmt(काष्ठा radeon_device *rdev, पूर्णांक block)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	rdev->irq.afmt[block] = false;
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
पूर्ण

/**
 * radeon_irq_kms_enable_hpd - enable hotplug detect पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @hpd_mask: mask of hpd pins you want to enable.
 *
 * Enables the hotplug detect पूर्णांकerrupt क्रम a specअगरic hpd pin (all asics).
 */
व्योम radeon_irq_kms_enable_hpd(काष्ठा radeon_device *rdev, अचिन्हित hpd_mask)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक i;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	क्रम (i = 0; i < RADEON_MAX_HPD_PINS; ++i)
		rdev->irq.hpd[i] |= !!(hpd_mask & (1 << i));
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
पूर्ण

/**
 * radeon_irq_kms_disable_hpd - disable hotplug detect पूर्णांकerrupt
 *
 * @rdev: radeon device poपूर्णांकer
 * @hpd_mask: mask of hpd pins you want to disable.
 *
 * Disables the hotplug detect पूर्णांकerrupt क्रम a specअगरic hpd pin (all asics).
 */
व्योम radeon_irq_kms_disable_hpd(काष्ठा radeon_device *rdev, अचिन्हित hpd_mask)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक i;

	अगर (!rdev->ddev->irq_enabled)
		वापस;

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	क्रम (i = 0; i < RADEON_MAX_HPD_PINS; ++i)
		rdev->irq.hpd[i] &= !(hpd_mask & (1 << i));
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
पूर्ण

/**
 * radeon_irq_kms_set_irq_n_enabled - helper क्रम updating पूर्णांकerrupt enable रेजिस्टरs
 *
 * @rdev: radeon device poपूर्णांकer
 * @reg: the रेजिस्टर to ग_लिखो to enable/disable पूर्णांकerrupts
 * @mask: the mask that enables the पूर्णांकerrupts
 * @enable: whether to enable or disable the पूर्णांकerrupt रेजिस्टर
 * @name: the name of the पूर्णांकerrupt रेजिस्टर to prपूर्णांक to the kernel log
 * @n: the number of the पूर्णांकerrupt रेजिस्टर to prपूर्णांक to the kernel log
 *
 * Helper क्रम updating the enable state of पूर्णांकerrupt रेजिस्टरs. Checks whether
 * or not the पूर्णांकerrupt matches the enable state we want. If it करोesn't, then
 * we update it and prपूर्णांक a debugging message to the kernel log indicating the
 * new state of the पूर्णांकerrupt रेजिस्टर.
 *
 * Used क्रम updating sequences of पूर्णांकerrupts रेजिस्टरs like HPD1, HPD2, etc.
 */
व्योम radeon_irq_kms_set_irq_n_enabled(काष्ठा radeon_device *rdev,
				      u32 reg, u32 mask,
				      bool enable, स्थिर अक्षर *name, अचिन्हित n)
अणु
	u32 पंचांगp = RREG32(reg);

	/* Interrupt state didn't change */
	अगर (!!(पंचांगp & mask) == enable)
		वापस;

	अगर (enable) अणु
		DRM_DEBUG("%s%d interrupts enabled\n", name, n);
		WREG32(reg, पंचांगp |= mask);
	पूर्ण अन्यथा अणु
		DRM_DEBUG("%s%d interrupts disabled\n", name, n);
		WREG32(reg, पंचांगp & ~mask);
	पूर्ण
पूर्ण
