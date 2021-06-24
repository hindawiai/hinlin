<शैली गुरु>
/* i915_drv.c -- i830,i845,i855,i865,i915 driver -*- linux-c -*-
 */
/*
 *
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/oom.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pnp.h>
#समावेश <linux/slab.h>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/vt.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "display/intel_acpi.h"
#समावेश "display/intel_bw.h"
#समावेश "display/intel_cdclk.h"
#समावेश "display/intel_csr.h"
#समावेश "display/intel_display_types.h"
#समावेश "display/intel_dp.h"
#समावेश "display/intel_fbdev.h"
#समावेश "display/intel_hotplug.h"
#समावेश "display/intel_overlay.h"
#समावेश "display/intel_pipe_crc.h"
#समावेश "display/intel_pps.h"
#समावेश "display/intel_sprite.h"
#समावेश "display/intel_vga.h"

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_ioctls.h"
#समावेश "gem/i915_gem_mman.h"
#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_rc6.h"

#समावेश "i915_debugfs.h"
#समावेश "i915_drv.h"
#समावेश "i915_ioc32.h"
#समावेश "i915_irq.h"
#समावेश "i915_memcpy.h"
#समावेश "i915_perf.h"
#समावेश "i915_query.h"
#समावेश "i915_suspend.h"
#समावेश "i915_switcheroo.h"
#समावेश "i915_sysfs.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_dram.h"
#समावेश "intel_gvt.h"
#समावेश "intel_memory_region.h"
#समावेश "intel_pm.h"
#समावेश "intel_sideband.h"
#समावेश "vlv_suspend.h"

अटल स्थिर काष्ठा drm_driver driver;

अटल पूर्णांक i915_get_bridge_dev(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक करोमुख्य = pci_करोमुख्य_nr(to_pci_dev(dev_priv->drm.dev)->bus);

	dev_priv->bridge_dev =
		pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, PCI_DEVFN(0, 0));
	अगर (!dev_priv->bridge_dev) अणु
		drm_err(&dev_priv->drm, "bridge device not found\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* Allocate space क्रम the MCH regs अगर needed, वापस nonzero on error */
अटल पूर्णांक
पूर्णांकel_alloc_mchbar_resource(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक reg = INTEL_GEN(dev_priv) >= 4 ? MCHBAR_I965 : MCHBAR_I915;
	u32 temp_lo, temp_hi = 0;
	u64 mchbar_addr;
	पूर्णांक ret;

	अगर (INTEL_GEN(dev_priv) >= 4)
		pci_पढ़ो_config_dword(dev_priv->bridge_dev, reg + 4, &temp_hi);
	pci_पढ़ो_config_dword(dev_priv->bridge_dev, reg, &temp_lo);
	mchbar_addr = ((u64)temp_hi << 32) | temp_lo;

	/* If ACPI करोesn't have it, assume we need to allocate it ourselves */
#अगर_घोषित CONFIG_PNP
	अगर (mchbar_addr &&
	    pnp_range_reserved(mchbar_addr, mchbar_addr + MCHBAR_SIZE))
		वापस 0;
#पूर्ण_अगर

	/* Get some space क्रम it */
	dev_priv->mch_res.name = "i915 MCHBAR";
	dev_priv->mch_res.flags = IORESOURCE_MEM;
	ret = pci_bus_alloc_resource(dev_priv->bridge_dev->bus,
				     &dev_priv->mch_res,
				     MCHBAR_SIZE, MCHBAR_SIZE,
				     PCIBIOS_MIN_MEM,
				     0, pcibios_align_resource,
				     dev_priv->bridge_dev);
	अगर (ret) अणु
		drm_dbg(&dev_priv->drm, "failed bus alloc: %d\n", ret);
		dev_priv->mch_res.start = 0;
		वापस ret;
	पूर्ण

	अगर (INTEL_GEN(dev_priv) >= 4)
		pci_ग_लिखो_config_dword(dev_priv->bridge_dev, reg + 4,
				       upper_32_bits(dev_priv->mch_res.start));

	pci_ग_लिखो_config_dword(dev_priv->bridge_dev, reg,
			       lower_32_bits(dev_priv->mch_res.start));
	वापस 0;
पूर्ण

/* Setup MCHBAR अगर possible, वापस true अगर we should disable it again */
अटल व्योम
पूर्णांकel_setup_mchbar(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक mchbar_reg = INTEL_GEN(dev_priv) >= 4 ? MCHBAR_I965 : MCHBAR_I915;
	u32 temp;
	bool enabled;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		वापस;

	dev_priv->mchbar_need_disable = false;

	अगर (IS_I915G(dev_priv) || IS_I915GM(dev_priv)) अणु
		pci_पढ़ो_config_dword(dev_priv->bridge_dev, DEVEN, &temp);
		enabled = !!(temp & DEVEN_MCHBAR_EN);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(dev_priv->bridge_dev, mchbar_reg, &temp);
		enabled = temp & 1;
	पूर्ण

	/* If it's already enabled, don't have to करो anything */
	अगर (enabled)
		वापस;

	अगर (पूर्णांकel_alloc_mchbar_resource(dev_priv))
		वापस;

	dev_priv->mchbar_need_disable = true;

	/* Space is allocated or reserved, so enable it. */
	अगर (IS_I915G(dev_priv) || IS_I915GM(dev_priv)) अणु
		pci_ग_लिखो_config_dword(dev_priv->bridge_dev, DEVEN,
				       temp | DEVEN_MCHBAR_EN);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(dev_priv->bridge_dev, mchbar_reg, &temp);
		pci_ग_लिखो_config_dword(dev_priv->bridge_dev, mchbar_reg, temp | 1);
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_tearकरोwn_mchbar(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक mchbar_reg = INTEL_GEN(dev_priv) >= 4 ? MCHBAR_I965 : MCHBAR_I915;

	अगर (dev_priv->mchbar_need_disable) अणु
		अगर (IS_I915G(dev_priv) || IS_I915GM(dev_priv)) अणु
			u32 deven_val;

			pci_पढ़ो_config_dword(dev_priv->bridge_dev, DEVEN,
					      &deven_val);
			deven_val &= ~DEVEN_MCHBAR_EN;
			pci_ग_लिखो_config_dword(dev_priv->bridge_dev, DEVEN,
					       deven_val);
		पूर्ण अन्यथा अणु
			u32 mchbar_val;

			pci_पढ़ो_config_dword(dev_priv->bridge_dev, mchbar_reg,
					      &mchbar_val);
			mchbar_val &= ~1;
			pci_ग_लिखो_config_dword(dev_priv->bridge_dev, mchbar_reg,
					       mchbar_val);
		पूर्ण
	पूर्ण

	अगर (dev_priv->mch_res.start)
		release_resource(&dev_priv->mch_res);
पूर्ण

अटल पूर्णांक i915_workqueues_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * The i915 workqueue is primarily used क्रम batched retirement of
	 * requests (and thus managing bo) once the task has been completed
	 * by the GPU. i915_retire_requests() is called directly when we
	 * need high-priority retirement, such as रुकोing क्रम an explicit
	 * bo.
	 *
	 * It is also used क्रम periodic low-priority events, such as
	 * idle-समयrs and recording error state.
	 *
	 * All tasks on the workqueue are expected to acquire the dev mutex
	 * so there is no poपूर्णांक in running more than one instance of the
	 * workqueue at any समय.  Use an ordered one.
	 */
	dev_priv->wq = alloc_ordered_workqueue("i915", 0);
	अगर (dev_priv->wq == शून्य)
		जाओ out_err;

	dev_priv->hotplug.dp_wq = alloc_ordered_workqueue("i915-dp", 0);
	अगर (dev_priv->hotplug.dp_wq == शून्य)
		जाओ out_मुक्त_wq;

	वापस 0;

out_मुक्त_wq:
	destroy_workqueue(dev_priv->wq);
out_err:
	drm_err(&dev_priv->drm, "Failed to allocate workqueues.\n");

	वापस -ENOMEM;
पूर्ण

अटल व्योम i915_workqueues_cleanup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	destroy_workqueue(dev_priv->hotplug.dp_wq);
	destroy_workqueue(dev_priv->wq);
पूर्ण

/*
 * We करोn't keep the workarounds क्रम pre-production hardware, so we expect our
 * driver to fail on these machines in one way or another. A little warning on
 * dmesg may help both the user and the bug triagers.
 *
 * Our policy क्रम removing pre-production workarounds is to keep the
 * current gen workarounds as a guide to the bring-up of the next gen
 * (workarounds have a habit of persisting!). Anything older than that
 * should be हटाओd aदीर्घ with the complications they पूर्णांकroduce.
 */
अटल व्योम पूर्णांकel_detect_preproduction_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	bool pre = false;

	pre |= IS_HSW_EARLY_SDV(dev_priv);
	pre |= IS_SKL_REVID(dev_priv, 0, SKL_REVID_F0);
	pre |= IS_BXT_REVID(dev_priv, 0, BXT_REVID_B_LAST);
	pre |= IS_KBL_GT_STEP(dev_priv, 0, STEP_A0);
	pre |= IS_GLK_REVID(dev_priv, 0, GLK_REVID_A2);

	अगर (pre) अणु
		drm_err(&dev_priv->drm, "This is a pre-production stepping. "
			  "It may not be fully functional.\n");
		add_taपूर्णांक(TAINT_MACHINE_CHECK, LOCKDEP_STILL_OK);
	पूर्ण
पूर्ण

अटल व्योम sanitize_gpu(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (!INTEL_INFO(i915)->gpu_reset_clobbers_display)
		__पूर्णांकel_gt_reset(&i915->gt, ALL_ENGINES);
पूर्ण

/**
 * i915_driver_early_probe - setup state not requiring device access
 * @dev_priv: device निजी
 *
 * Initialize everything that is a "SW-only" state, that is state not
 * requiring accessing the device or exposing the driver via kernel पूर्णांकernal
 * or userspace पूर्णांकerfaces. Example steps beदीर्घing here: lock initialization,
 * प्रणाली memory allocation, setting up device specअगरic attributes and
 * function hooks not requiring accessing the device.
 */
अटल पूर्णांक i915_driver_early_probe(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret = 0;

	अगर (i915_inject_probe_failure(dev_priv))
		वापस -ENODEV;

	पूर्णांकel_device_info_subplatक्रमm_init(dev_priv);
	पूर्णांकel_step_init(dev_priv);

	पूर्णांकel_uncore_mmio_debug_init_early(&dev_priv->mmio_debug);
	पूर्णांकel_uncore_init_early(&dev_priv->uncore, dev_priv);

	spin_lock_init(&dev_priv->irq_lock);
	spin_lock_init(&dev_priv->gpu_error.lock);
	mutex_init(&dev_priv->backlight_lock);

	mutex_init(&dev_priv->sb_lock);
	cpu_latency_qos_add_request(&dev_priv->sb_qos, PM_QOS_DEFAULT_VALUE);

	mutex_init(&dev_priv->av_mutex);
	mutex_init(&dev_priv->wm.wm_mutex);
	mutex_init(&dev_priv->pps_mutex);
	mutex_init(&dev_priv->hdcp_comp_mutex);

	i915_स_नकल_init_early(dev_priv);
	पूर्णांकel_runसमय_pm_init_early(&dev_priv->runसमय_pm);

	ret = i915_workqueues_init(dev_priv);
	अगर (ret < 0)
		वापस ret;

	ret = vlv_suspend_init(dev_priv);
	अगर (ret < 0)
		जाओ err_workqueues;

	पूर्णांकel_wopcm_init_early(&dev_priv->wopcm);

	पूर्णांकel_gt_init_early(&dev_priv->gt, dev_priv);

	i915_gem_init_early(dev_priv);

	/* This must be called beक्रमe any calls to HAS_PCH_* */
	पूर्णांकel_detect_pch(dev_priv);

	पूर्णांकel_pm_setup(dev_priv);
	ret = पूर्णांकel_घातer_करोमुख्यs_init(dev_priv);
	अगर (ret < 0)
		जाओ err_gem;
	पूर्णांकel_irq_init(dev_priv);
	पूर्णांकel_init_display_hooks(dev_priv);
	पूर्णांकel_init_घड़ी_gating_hooks(dev_priv);

	पूर्णांकel_detect_preproduction_hw(dev_priv);

	वापस 0;

err_gem:
	i915_gem_cleanup_early(dev_priv);
	पूर्णांकel_gt_driver_late_release(&dev_priv->gt);
	vlv_suspend_cleanup(dev_priv);
err_workqueues:
	i915_workqueues_cleanup(dev_priv);
	वापस ret;
पूर्ण

/**
 * i915_driver_late_release - cleanup the setup करोne in
 *			       i915_driver_early_probe()
 * @dev_priv: device निजी
 */
अटल व्योम i915_driver_late_release(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_irq_fini(dev_priv);
	पूर्णांकel_घातer_करोमुख्यs_cleanup(dev_priv);
	i915_gem_cleanup_early(dev_priv);
	पूर्णांकel_gt_driver_late_release(&dev_priv->gt);
	vlv_suspend_cleanup(dev_priv);
	i915_workqueues_cleanup(dev_priv);

	cpu_latency_qos_हटाओ_request(&dev_priv->sb_qos);
	mutex_destroy(&dev_priv->sb_lock);

	i915_params_मुक्त(&dev_priv->params);
पूर्ण

/**
 * i915_driver_mmio_probe - setup device MMIO
 * @dev_priv: device निजी
 *
 * Setup minimal device state necessary क्रम MMIO accesses later in the
 * initialization sequence. The setup here should aव्योम any other device-wide
 * side effects or exposing the driver via kernel पूर्णांकernal or user space
 * पूर्णांकerfaces.
 */
अटल पूर्णांक i915_driver_mmio_probe(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	अगर (i915_inject_probe_failure(dev_priv))
		वापस -ENODEV;

	अगर (i915_get_bridge_dev(dev_priv))
		वापस -EIO;

	ret = पूर्णांकel_uncore_init_mmio(&dev_priv->uncore);
	अगर (ret < 0)
		जाओ err_bridge;

	/* Try to make sure MCHBAR is enabled beक्रमe poking at it */
	पूर्णांकel_setup_mchbar(dev_priv);
	पूर्णांकel_device_info_runसमय_init(dev_priv);

	ret = पूर्णांकel_gt_init_mmio(&dev_priv->gt);
	अगर (ret)
		जाओ err_uncore;

	/* As early as possible, scrub existing GPU state beक्रमe clobbering */
	sanitize_gpu(dev_priv);

	वापस 0;

err_uncore:
	पूर्णांकel_tearकरोwn_mchbar(dev_priv);
	पूर्णांकel_uncore_fini_mmio(&dev_priv->uncore);
err_bridge:
	pci_dev_put(dev_priv->bridge_dev);

	वापस ret;
पूर्ण

/**
 * i915_driver_mmio_release - cleanup the setup करोne in i915_driver_mmio_probe()
 * @dev_priv: device निजी
 */
अटल व्योम i915_driver_mmio_release(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_tearकरोwn_mchbar(dev_priv);
	पूर्णांकel_uncore_fini_mmio(&dev_priv->uncore);
	pci_dev_put(dev_priv->bridge_dev);
पूर्ण

अटल व्योम पूर्णांकel_sanitize_options(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_gvt_sanitize_options(dev_priv);
पूर्ण

/**
 * i915_set_dma_info - set all relevant PCI dma info as configured क्रम the
 * platक्रमm
 * @i915: valid i915 instance
 *
 * Set the dma max segment size, device and coherent masks.  The dma mask set
 * needs to occur beक्रमe i915_ggtt_probe_hw.
 *
 * A couple of platक्रमms have special needs.  Address them as well.
 *
 */
अटल पूर्णांक i915_set_dma_info(काष्ठा drm_i915_निजी *i915)
अणु
	अचिन्हित पूर्णांक mask_size = INTEL_INFO(i915)->dma_mask_size;
	पूर्णांक ret;

	GEM_BUG_ON(!mask_size);

	/*
	 * We करोn't have a max segment size, so set it to the max so sg's
	 * debugging layer करोesn't complain
	 */
	dma_set_max_seg_size(i915->drm.dev, अच_पूर्णांक_उच्च);

	ret = dma_set_mask(i915->drm.dev, DMA_BIT_MASK(mask_size));
	अगर (ret)
		जाओ mask_err;

	/* overlay on gen2 is broken and can't address above 1G */
	अगर (IS_GEN(i915, 2))
		mask_size = 30;

	/*
	 * 965GM someबार incorrectly ग_लिखोs to hardware status page (HWS)
	 * using 32bit addressing, overwriting memory अगर HWS is located
	 * above 4GB.
	 *
	 * The करोcumentation also mentions an issue with undefined
	 * behaviour अगर any general state is accessed within a page above 4GB,
	 * which also needs to be handled carefully.
	 */
	अगर (IS_I965G(i915) || IS_I965GM(i915))
		mask_size = 32;

	ret = dma_set_coherent_mask(i915->drm.dev, DMA_BIT_MASK(mask_size));
	अगर (ret)
		जाओ mask_err;

	वापस 0;

mask_err:
	drm_err(&i915->drm, "Can't set DMA mask/consistent mask (%d)\n", ret);
	वापस ret;
पूर्ण

/**
 * i915_driver_hw_probe - setup state requiring device access
 * @dev_priv: device निजी
 *
 * Setup state that requires accessing the device, but करोesn't require
 * exposing the driver via kernel पूर्णांकernal or userspace पूर्णांकerfaces.
 */
अटल पूर्णांक i915_driver_hw_probe(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	पूर्णांक ret;

	अगर (i915_inject_probe_failure(dev_priv))
		वापस -ENODEV;

	अगर (HAS_PPGTT(dev_priv)) अणु
		अगर (पूर्णांकel_vgpu_active(dev_priv) &&
		    !पूर्णांकel_vgpu_has_full_ppgtt(dev_priv)) अणु
			i915_report_error(dev_priv,
					  "incompatible vGPU found, support for isolated ppGTT required\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	अगर (HAS_EXECLISTS(dev_priv)) अणु
		/*
		 * Older GVT emulation depends upon पूर्णांकercepting CSB mmio,
		 * which we no दीर्घer use, preferring to use the HWSP cache
		 * instead.
		 */
		अगर (पूर्णांकel_vgpu_active(dev_priv) &&
		    !पूर्णांकel_vgpu_has_hwsp_emulation(dev_priv)) अणु
			i915_report_error(dev_priv,
					  "old vGPU host found, support for HWSP emulation required\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	पूर्णांकel_sanitize_options(dev_priv);

	/* needs to be करोne beक्रमe ggtt probe */
	पूर्णांकel_dram_edram_detect(dev_priv);

	ret = i915_set_dma_info(dev_priv);
	अगर (ret)
		वापस ret;

	i915_perf_init(dev_priv);

	ret = i915_ggtt_probe_hw(dev_priv);
	अगर (ret)
		जाओ err_perf;

	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "inteldrmfb");
	अगर (ret)
		जाओ err_ggtt;

	ret = i915_ggtt_init_hw(dev_priv);
	अगर (ret)
		जाओ err_ggtt;

	ret = पूर्णांकel_memory_regions_hw_probe(dev_priv);
	अगर (ret)
		जाओ err_ggtt;

	पूर्णांकel_gt_init_hw_early(&dev_priv->gt, &dev_priv->ggtt);

	ret = पूर्णांकel_gt_probe_lmem(&dev_priv->gt);
	अगर (ret)
		जाओ err_mem_regions;

	ret = i915_ggtt_enable_hw(dev_priv);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "failed to enable GGTT\n");
		जाओ err_mem_regions;
	पूर्ण

	pci_set_master(pdev);

	पूर्णांकel_gt_init_workarounds(dev_priv);

	/* On the 945G/GM, the chipset reports the MSI capability on the
	 * पूर्णांकegrated graphics even though the support isn't actually there
	 * according to the published specs.  It करोesn't appear to function
	 * correctly in testing on 945G.
	 * This may be a side effect of MSI having been made available क्रम PEG
	 * and the रेजिस्टरs being बंदly associated.
	 *
	 * According to chipset errata, on the 965GM, MSI पूर्णांकerrupts may
	 * be lost or delayed, and was defeatured. MSI पूर्णांकerrupts seem to
	 * get lost on g4x as well, and पूर्णांकerrupt delivery seems to stay
	 * properly dead afterwards. So we'll just disable them क्रम all
	 * pre-gen5 chipsets.
	 *
	 * dp aux and gmbus irq on gen4 seems to be able to generate legacy
	 * पूर्णांकerrupts even when in MSI mode. This results in spurious
	 * पूर्णांकerrupt warnings अगर the legacy irq no. is shared with another
	 * device. The kernel then disables that पूर्णांकerrupt source and so
	 * prevents the other device from working properly.
	 */
	अगर (INTEL_GEN(dev_priv) >= 5) अणु
		अगर (pci_enable_msi(pdev) < 0)
			drm_dbg(&dev_priv->drm, "can't enable MSI");
	पूर्ण

	ret = पूर्णांकel_gvt_init(dev_priv);
	अगर (ret)
		जाओ err_msi;

	पूर्णांकel_opregion_setup(dev_priv);

	पूर्णांकel_pcode_init(dev_priv);

	/*
	 * Fill the dram काष्ठाure to get the प्रणाली dram info. This will be
	 * used क्रम memory latency calculation.
	 */
	पूर्णांकel_dram_detect(dev_priv);

	पूर्णांकel_bw_init_hw(dev_priv);

	वापस 0;

err_msi:
	अगर (pdev->msi_enabled)
		pci_disable_msi(pdev);
err_mem_regions:
	पूर्णांकel_memory_regions_driver_release(dev_priv);
err_ggtt:
	i915_ggtt_driver_release(dev_priv);
err_perf:
	i915_perf_fini(dev_priv);
	वापस ret;
पूर्ण

/**
 * i915_driver_hw_हटाओ - cleanup the setup करोne in i915_driver_hw_probe()
 * @dev_priv: device निजी
 */
अटल व्योम i915_driver_hw_हटाओ(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);

	i915_perf_fini(dev_priv);

	अगर (pdev->msi_enabled)
		pci_disable_msi(pdev);
पूर्ण

/**
 * i915_driver_रेजिस्टर - रेजिस्टर the driver with the rest of the प्रणाली
 * @dev_priv: device निजी
 *
 * Perक्रमm any steps necessary to make the driver available via kernel
 * पूर्णांकernal or userspace पूर्णांकerfaces.
 */
अटल व्योम i915_driver_रेजिस्टर(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;

	i915_gem_driver_रेजिस्टर(dev_priv);
	i915_pmu_रेजिस्टर(dev_priv);

	पूर्णांकel_vgpu_रेजिस्टर(dev_priv);

	/* Reveal our presence to userspace */
	अगर (drm_dev_रेजिस्टर(dev, 0)) अणु
		drm_err(&dev_priv->drm,
			"Failed to register driver for userspace access!\n");
		वापस;
	पूर्ण

	i915_debugfs_रेजिस्टर(dev_priv);
	i915_setup_sysfs(dev_priv);

	/* Depends on sysfs having been initialized */
	i915_perf_रेजिस्टर(dev_priv);

	पूर्णांकel_gt_driver_रेजिस्टर(&dev_priv->gt);

	पूर्णांकel_display_driver_रेजिस्टर(dev_priv);

	पूर्णांकel_घातer_करोमुख्यs_enable(dev_priv);
	पूर्णांकel_runसमय_pm_enable(&dev_priv->runसमय_pm);

	पूर्णांकel_रेजिस्टर_dsm_handler();

	अगर (i915_चयनeroo_रेजिस्टर(dev_priv))
		drm_err(&dev_priv->drm, "Failed to register vga switcheroo!\n");
पूर्ण

/**
 * i915_driver_unरेजिस्टर - cleanup the registration करोne in i915_driver_regiser()
 * @dev_priv: device निजी
 */
अटल व्योम i915_driver_unरेजिस्टर(काष्ठा drm_i915_निजी *dev_priv)
अणु
	i915_चयनeroo_unरेजिस्टर(dev_priv);

	पूर्णांकel_unरेजिस्टर_dsm_handler();

	पूर्णांकel_runसमय_pm_disable(&dev_priv->runसमय_pm);
	पूर्णांकel_घातer_करोमुख्यs_disable(dev_priv);

	पूर्णांकel_display_driver_unरेजिस्टर(dev_priv);

	पूर्णांकel_gt_driver_unरेजिस्टर(&dev_priv->gt);

	i915_perf_unरेजिस्टर(dev_priv);
	i915_pmu_unरेजिस्टर(dev_priv);

	i915_tearकरोwn_sysfs(dev_priv);
	drm_dev_unplug(&dev_priv->drm);

	i915_gem_driver_unरेजिस्टर(dev_priv);
पूर्ण

अटल व्योम i915_welcome_messages(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (drm_debug_enabled(DRM_UT_DRIVER)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer("i915 device info:");

		drm_म_लिखो(&p, "pciid=0x%04x rev=0x%02x platform=%s (subplatform=0x%x) gen=%i\n",
			   INTEL_DEVID(dev_priv),
			   INTEL_REVID(dev_priv),
			   पूर्णांकel_platक्रमm_name(INTEL_INFO(dev_priv)->platक्रमm),
			   पूर्णांकel_subplatक्रमm(RUNTIME_INFO(dev_priv),
					     INTEL_INFO(dev_priv)->platक्रमm),
			   INTEL_GEN(dev_priv));

		पूर्णांकel_device_info_prपूर्णांक_अटल(INTEL_INFO(dev_priv), &p);
		पूर्णांकel_device_info_prपूर्णांक_runसमय(RUNTIME_INFO(dev_priv), &p);
		पूर्णांकel_gt_info_prपूर्णांक(&dev_priv->gt.info, &p);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG))
		drm_info(&dev_priv->drm, "DRM_I915_DEBUG enabled\n");
	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		drm_info(&dev_priv->drm, "DRM_I915_DEBUG_GEM enabled\n");
	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM))
		drm_info(&dev_priv->drm,
			 "DRM_I915_DEBUG_RUNTIME_PM enabled\n");
पूर्ण

अटल काष्ठा drm_i915_निजी *
i915_driver_create(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा पूर्णांकel_device_info *match_info =
		(काष्ठा पूर्णांकel_device_info *)ent->driver_data;
	काष्ठा पूर्णांकel_device_info *device_info;
	काष्ठा drm_i915_निजी *i915;

	i915 = devm_drm_dev_alloc(&pdev->dev, &driver,
				  काष्ठा drm_i915_निजी, drm);
	अगर (IS_ERR(i915))
		वापस i915;

	i915->drm.pdev = pdev;
	pci_set_drvdata(pdev, i915);

	/* Device parameters start as a copy of module parameters. */
	i915_params_copy(&i915->params, &i915_modparams);

	/* Setup the ग_लिखो-once "constant" device info */
	device_info = mkग_लिखो_device_info(i915);
	स_नकल(device_info, match_info, माप(*device_info));
	RUNTIME_INFO(i915)->device_id = pdev->device;

	BUG_ON(device_info->gen > BITS_PER_TYPE(device_info->gen_mask));

	वापस i915;
पूर्ण

/**
 * i915_driver_probe - setup chip and create an initial config
 * @pdev: PCI device
 * @ent: matching PCI ID entry
 *
 * The driver probe routine has to करो several things:
 *   - drive output discovery via पूर्णांकel_modeset_init()
 *   - initialize the memory manager
 *   - allocate initial config memory
 *   - setup the DRM framebuffer with the allocated memory
 */
पूर्णांक i915_driver_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा पूर्णांकel_device_info *match_info =
		(काष्ठा पूर्णांकel_device_info *)ent->driver_data;
	काष्ठा drm_i915_निजी *i915;
	पूर्णांक ret;

	i915 = i915_driver_create(pdev, ent);
	अगर (IS_ERR(i915))
		वापस PTR_ERR(i915);

	/* Disable nuclear pageflip by शेष on pre-ILK */
	अगर (!i915->params.nuclear_pageflip && match_info->gen < 5)
		i915->drm.driver_features &= ~DRIVER_ATOMIC;

	/*
	 * Check अगर we support fake LMEM -- क्रम now we only unleash this क्रम
	 * the live selftests(test-and-निकास).
	 */
#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
	अगर (IS_ENABLED(CONFIG_DRM_I915_UNSTABLE_FAKE_LMEM)) अणु
		अगर (INTEL_GEN(i915) >= 9 && i915_selftest.live < 0 &&
		    i915->params.fake_lmem_start) अणु
			mkग_लिखो_device_info(i915)->memory_regions =
				REGION_SMEM | REGION_LMEM | REGION_STOLEN_SMEM;
			GEM_BUG_ON(!HAS_LMEM(i915));
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ out_fini;

	ret = i915_driver_early_probe(i915);
	अगर (ret < 0)
		जाओ out_pci_disable;

	disable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);

	पूर्णांकel_vgpu_detect(i915);

	ret = i915_driver_mmio_probe(i915);
	अगर (ret < 0)
		जाओ out_runसमय_pm_put;

	ret = i915_driver_hw_probe(i915);
	अगर (ret < 0)
		जाओ out_cleanup_mmio;

	ret = पूर्णांकel_modeset_init_noirq(i915);
	अगर (ret < 0)
		जाओ out_cleanup_hw;

	ret = पूर्णांकel_irq_install(i915);
	अगर (ret)
		जाओ out_cleanup_modeset;

	ret = पूर्णांकel_modeset_init_nogem(i915);
	अगर (ret)
		जाओ out_cleanup_irq;

	ret = i915_gem_init(i915);
	अगर (ret)
		जाओ out_cleanup_modeset2;

	ret = पूर्णांकel_modeset_init(i915);
	अगर (ret)
		जाओ out_cleanup_gem;

	i915_driver_रेजिस्टर(i915);

	enable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);

	i915_welcome_messages(i915);

	i915->करो_release = true;

	वापस 0;

out_cleanup_gem:
	i915_gem_suspend(i915);
	i915_gem_driver_हटाओ(i915);
	i915_gem_driver_release(i915);
out_cleanup_modeset2:
	/* FIXME clean up the error path */
	पूर्णांकel_modeset_driver_हटाओ(i915);
	पूर्णांकel_irq_uninstall(i915);
	पूर्णांकel_modeset_driver_हटाओ_noirq(i915);
	जाओ out_cleanup_modeset;
out_cleanup_irq:
	पूर्णांकel_irq_uninstall(i915);
out_cleanup_modeset:
	पूर्णांकel_modeset_driver_हटाओ_nogem(i915);
out_cleanup_hw:
	i915_driver_hw_हटाओ(i915);
	पूर्णांकel_memory_regions_driver_release(i915);
	i915_ggtt_driver_release(i915);
out_cleanup_mmio:
	i915_driver_mmio_release(i915);
out_runसमय_pm_put:
	enable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);
	i915_driver_late_release(i915);
out_pci_disable:
	pci_disable_device(pdev);
out_fini:
	i915_probe_error(i915, "Device initialization failed (%d)\n", ret);
	वापस ret;
पूर्ण

व्योम i915_driver_हटाओ(काष्ठा drm_i915_निजी *i915)
अणु
	disable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);

	i915_driver_unरेजिस्टर(i915);

	/* Flush any बाह्यal code that still may be under the RCU lock */
	synchronize_rcu();

	i915_gem_suspend(i915);

	पूर्णांकel_gvt_driver_हटाओ(i915);

	पूर्णांकel_modeset_driver_हटाओ(i915);

	पूर्णांकel_irq_uninstall(i915);

	पूर्णांकel_modeset_driver_हटाओ_noirq(i915);

	i915_reset_error_state(i915);
	i915_gem_driver_हटाओ(i915);

	पूर्णांकel_modeset_driver_हटाओ_nogem(i915);

	i915_driver_hw_हटाओ(i915);

	enable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);
पूर्ण

अटल व्योम i915_driver_release(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &dev_priv->runसमय_pm;

	अगर (!dev_priv->करो_release)
		वापस;

	disable_rpm_wakeref_निश्चितs(rpm);

	i915_gem_driver_release(dev_priv);

	पूर्णांकel_memory_regions_driver_release(dev_priv);
	i915_ggtt_driver_release(dev_priv);
	i915_gem_drain_मुक्तd_objects(dev_priv);

	i915_driver_mmio_release(dev_priv);

	enable_rpm_wakeref_निश्चितs(rpm);
	पूर्णांकel_runसमय_pm_driver_release(rpm);

	i915_driver_late_release(dev_priv);
पूर्ण

अटल पूर्णांक i915_driver_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	पूर्णांक ret;

	ret = i915_gem_खोलो(i915, file);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * i915_driver_lastबंद - clean up after all DRM clients have निकासed
 * @dev: DRM device
 *
 * Take care of cleaning up after all DRM clients have निकासed.  In the
 * mode setting हाल, we want to restore the kernel's initial mode (just
 * in हाल the last client left us in a bad state).
 *
 * Additionally, in the non-mode setting हाल, we'll tear करोwn the GTT
 * and DMA काष्ठाures, since the kernel won't be using them, and clea
 * up any GEM state.
 */
अटल व्योम i915_driver_lastबंद(काष्ठा drm_device *dev)
अणु
	पूर्णांकel_fbdev_restore_mode(dev);
	vga_चयनeroo_process_delayed_चयन();
पूर्ण

अटल व्योम i915_driver_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;

	i915_gem_context_बंद(file);

	kमुक्त_rcu(file_priv, rcu);

	/* Catch up with all the deferred मुक्तs from "this" client */
	i915_gem_flush_मुक्त_objects(to_i915(dev));
पूर्ण

अटल व्योम पूर्णांकel_suspend_encoders(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_encoder *encoder;

	drm_modeset_lock_all(dev);
	क्रम_each_पूर्णांकel_encoder(dev, encoder)
		अगर (encoder->suspend)
			encoder->suspend(encoder);
	drm_modeset_unlock_all(dev);
पूर्ण

अटल व्योम पूर्णांकel_shutकरोwn_encoders(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_encoder *encoder;

	drm_modeset_lock_all(dev);
	क्रम_each_पूर्णांकel_encoder(dev, encoder)
		अगर (encoder->shutकरोwn)
			encoder->shutकरोwn(encoder);
	drm_modeset_unlock_all(dev);
पूर्ण

व्योम i915_driver_shutकरोwn(काष्ठा drm_i915_निजी *i915)
अणु
	disable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);
	पूर्णांकel_runसमय_pm_disable(&i915->runसमय_pm);
	पूर्णांकel_घातer_करोमुख्यs_disable(i915);

	i915_gem_suspend(i915);

	drm_kms_helper_poll_disable(&i915->drm);

	drm_atomic_helper_shutकरोwn(&i915->drm);

	पूर्णांकel_dp_mst_suspend(i915);

	पूर्णांकel_runसमय_pm_disable_पूर्णांकerrupts(i915);
	पूर्णांकel_hpd_cancel_work(i915);

	पूर्णांकel_suspend_encoders(i915);
	पूर्णांकel_shutकरोwn_encoders(i915);

	/*
	 * The only requirement is to reboot with display DC states disabled,
	 * क्रम now leaving all display घातer wells in the INIT घातer करोमुख्य
	 * enabled matching the driver reload sequence.
	 */
	पूर्णांकel_घातer_करोमुख्यs_driver_हटाओ(i915);
	enable_rpm_wakeref_निश्चितs(&i915->runसमय_pm);

	पूर्णांकel_runसमय_pm_driver_release(&i915->runसमय_pm);
पूर्ण

अटल bool suspend_to_idle(काष्ठा drm_i915_निजी *dev_priv)
अणु
#अगर IS_ENABLED(CONFIG_ACPI_SLEEP)
	अगर (acpi_target_प्रणाली_state() < ACPI_STATE_S3)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक i915_drm_prepare(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);

	/*
	 * NB पूर्णांकel_display_suspend() may issue new requests after we've
	 * ostensibly marked the GPU as पढ़ोy-to-sleep here. We need to
	 * split out that work and pull it क्रमward so that after poपूर्णांक,
	 * the GPU is not woken again.
	 */
	i915_gem_suspend(i915);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_drm_suspend(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	pci_घातer_t opregion_target_state;

	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	/* We करो a lot of poking in a lot of रेजिस्टरs, make sure they work
	 * properly. */
	पूर्णांकel_घातer_करोमुख्यs_disable(dev_priv);

	drm_kms_helper_poll_disable(dev);

	pci_save_state(pdev);

	पूर्णांकel_display_suspend(dev);

	पूर्णांकel_dp_mst_suspend(dev_priv);

	पूर्णांकel_runसमय_pm_disable_पूर्णांकerrupts(dev_priv);
	पूर्णांकel_hpd_cancel_work(dev_priv);

	पूर्णांकel_suspend_encoders(dev_priv);

	पूर्णांकel_suspend_hw(dev_priv);

	i915_ggtt_suspend(&dev_priv->ggtt);

	i915_save_display(dev_priv);

	opregion_target_state = suspend_to_idle(dev_priv) ? PCI_D1 : PCI_D3cold;
	पूर्णांकel_opregion_suspend(dev_priv, opregion_target_state);

	पूर्णांकel_fbdev_set_suspend(dev, FBINFO_STATE_SUSPENDED, true);

	dev_priv->suspend_count++;

	पूर्णांकel_csr_ucode_suspend(dev_priv);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस 0;
पूर्ण

अटल क्रमागत i915_drm_suspend_mode
get_suspend_mode(काष्ठा drm_i915_निजी *dev_priv, bool hibernate)
अणु
	अगर (hibernate)
		वापस I915_DRM_SUSPEND_HIBERNATE;

	अगर (suspend_to_idle(dev_priv))
		वापस I915_DRM_SUSPEND_IDLE;

	वापस I915_DRM_SUSPEND_MEM;
पूर्ण

अटल पूर्णांक i915_drm_suspend_late(काष्ठा drm_device *dev, bool hibernation)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &dev_priv->runसमय_pm;
	पूर्णांक ret;

	disable_rpm_wakeref_निश्चितs(rpm);

	i915_gem_suspend_late(dev_priv);

	पूर्णांकel_uncore_suspend(&dev_priv->uncore);

	पूर्णांकel_घातer_करोमुख्यs_suspend(dev_priv,
				    get_suspend_mode(dev_priv, hibernation));

	पूर्णांकel_display_घातer_suspend_late(dev_priv);

	ret = vlv_suspend_complete(dev_priv);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "Suspend complete failed: %d\n", ret);
		पूर्णांकel_घातer_करोमुख्यs_resume(dev_priv);

		जाओ out;
	पूर्ण

	pci_disable_device(pdev);
	/*
	 * During hibernation on some platक्रमms the BIOS may try to access
	 * the device even though it's alपढ़ोy in D3 and hang the machine. So
	 * leave the device in D0 on those platक्रमms and hope the BIOS will
	 * घातer करोwn the device properly. The issue was seen on multiple old
	 * GENs with dअगरferent BIOS venकरोrs, so having an explicit blacklist
	 * is inpractical; apply the workaround on everything pre GEN6. The
	 * platक्रमms where the issue was seen:
	 * Lenovo Thinkpad X301, X61s, X60, T60, X41
	 * Fujitsu FSC S7110
	 * Acer Aspire 1830T
	 */
	अगर (!(hibernation && INTEL_GEN(dev_priv) < 6))
		pci_set_घातer_state(pdev, PCI_D3hot);

out:
	enable_rpm_wakeref_निश्चितs(rpm);
	अगर (!dev_priv->uncore.user_क्रमcewake_count)
		पूर्णांकel_runसमय_pm_driver_release(rpm);

	वापस ret;
पूर्ण

पूर्णांक i915_suspend_चयनeroo(काष्ठा drm_i915_निजी *i915, pm_message_t state)
अणु
	पूर्णांक error;

	अगर (drm_WARN_ON_ONCE(&i915->drm, state.event != PM_EVENT_SUSPEND &&
			     state.event != PM_EVENT_FREEZE))
		वापस -EINVAL;

	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	error = i915_drm_suspend(&i915->drm);
	अगर (error)
		वापस error;

	वापस i915_drm_suspend_late(&i915->drm, false);
पूर्ण

अटल पूर्णांक i915_drm_resume(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	पूर्णांक ret;

	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	sanitize_gpu(dev_priv);

	ret = i915_ggtt_enable_hw(dev_priv);
	अगर (ret)
		drm_err(&dev_priv->drm, "failed to re-enable GGTT\n");

	i915_ggtt_resume(&dev_priv->ggtt);

	पूर्णांकel_csr_ucode_resume(dev_priv);

	i915_restore_display(dev_priv);
	पूर्णांकel_pps_unlock_regs_wa(dev_priv);

	पूर्णांकel_init_pch_refclk(dev_priv);

	/*
	 * Interrupts have to be enabled beक्रमe any batches are run. If not the
	 * GPU will hang. i915_gem_init_hw() will initiate batches to
	 * update/restore the context.
	 *
	 * drm_mode_config_reset() needs AUX पूर्णांकerrupts.
	 *
	 * Modeset enabling in पूर्णांकel_modeset_init_hw() also needs working
	 * पूर्णांकerrupts.
	 */
	पूर्णांकel_runसमय_pm_enable_पूर्णांकerrupts(dev_priv);

	drm_mode_config_reset(dev);

	i915_gem_resume(dev_priv);

	पूर्णांकel_modeset_init_hw(dev_priv);
	पूर्णांकel_init_घड़ी_gating(dev_priv);
	पूर्णांकel_hpd_init(dev_priv);

	/* MST sideband requires HPD पूर्णांकerrupts enabled */
	पूर्णांकel_dp_mst_resume(dev_priv);
	पूर्णांकel_display_resume(dev);

	पूर्णांकel_hpd_poll_disable(dev_priv);
	drm_kms_helper_poll_enable(dev);

	पूर्णांकel_opregion_resume(dev_priv);

	पूर्णांकel_fbdev_set_suspend(dev, FBINFO_STATE_RUNNING, false);

	पूर्णांकel_घातer_करोमुख्यs_enable(dev_priv);

	पूर्णांकel_gvt_resume(dev_priv);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_drm_resume_early(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	पूर्णांक ret;

	/*
	 * We have a resume ordering issue with the snd-hda driver also
	 * requiring our device to be घातer up. Due to the lack of a
	 * parent/child relationship we currently solve this with an early
	 * resume hook.
	 *
	 * FIXME: This should be solved with a special hdmi sink device or
	 * similar so that घातer करोमुख्यs can be employed.
	 */

	/*
	 * Note that we need to set the घातer state explicitly, since we
	 * घातered off the device during मुक्तze and the PCI core won't घातer
	 * it back up क्रम us during thaw. Powering off the device during
	 * मुक्तze is not a hard requirement though, and during the
	 * suspend/resume phases the PCI core makes sure we get here with the
	 * device घातered on. So in हाल we change our मुक्तze logic and keep
	 * the device घातered we can also हटाओ the following set घातer state
	 * call.
	 */
	ret = pci_set_घातer_state(pdev, PCI_D0);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"failed to set PCI D0 power state (%d)\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Note that pci_enable_device() first enables any parent bridge
	 * device and only then sets the घातer state क्रम this device. The
	 * bridge enabling is a nop though, since bridge devices are resumed
	 * first. The order of enabling घातer and enabling the device is
	 * imposed by the PCI core as described above, so here we preserve the
	 * same order क्रम the मुक्तze/thaw phases.
	 *
	 * TODO: eventually we should हटाओ pci_disable_device() /
	 * pci_enable_enable_device() from suspend/resume. Due to how they
	 * depend on the device enable refcount we can't anyway depend on them
	 * disabling/enabling the device.
	 */
	अगर (pci_enable_device(pdev))
		वापस -EIO;

	pci_set_master(pdev);

	disable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	ret = vlv_resume_prepare(dev_priv, false);
	अगर (ret)
		drm_err(&dev_priv->drm,
			"Resume prepare failed: %d, continuing anyway\n", ret);

	पूर्णांकel_uncore_resume_early(&dev_priv->uncore);

	पूर्णांकel_gt_check_and_clear_faults(&dev_priv->gt);

	पूर्णांकel_display_घातer_resume_early(dev_priv);

	पूर्णांकel_घातer_करोमुख्यs_resume(dev_priv);

	enable_rpm_wakeref_निश्चितs(&dev_priv->runसमय_pm);

	वापस ret;
पूर्ण

पूर्णांक i915_resume_चयनeroo(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret;

	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	ret = i915_drm_resume_early(&i915->drm);
	अगर (ret)
		वापस ret;

	वापस i915_drm_resume(&i915->drm);
पूर्ण

अटल पूर्णांक i915_pm_prepare(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);

	अगर (!i915) अणु
		dev_err(kdev, "DRM not initialized, aborting suspend.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	वापस i915_drm_prepare(&i915->drm);
पूर्ण

अटल पूर्णांक i915_pm_suspend(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);

	अगर (!i915) अणु
		dev_err(kdev, "DRM not initialized, aborting suspend.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	वापस i915_drm_suspend(&i915->drm);
पूर्ण

अटल पूर्णांक i915_pm_suspend_late(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);

	/*
	 * We have a suspend ordering issue with the snd-hda driver also
	 * requiring our device to be घातer up. Due to the lack of a
	 * parent/child relationship we currently solve this with an late
	 * suspend hook.
	 *
	 * FIXME: This should be solved with a special hdmi sink device or
	 * similar so that घातer करोमुख्यs can be employed.
	 */
	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	वापस i915_drm_suspend_late(&i915->drm, false);
पूर्ण

अटल पूर्णांक i915_pm_घातeroff_late(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);

	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	वापस i915_drm_suspend_late(&i915->drm, true);
पूर्ण

अटल पूर्णांक i915_pm_resume_early(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);

	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	वापस i915_drm_resume_early(&i915->drm);
पूर्ण

अटल पूर्णांक i915_pm_resume(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);

	अगर (i915->drm.चयन_घातer_state == DRM_SWITCH_POWER_OFF)
		वापस 0;

	वापस i915_drm_resume(&i915->drm);
पूर्ण

/* मुक्तze: beक्रमe creating the hibernation_image */
अटल पूर्णांक i915_pm_मुक्तze(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);
	पूर्णांक ret;

	अगर (i915->drm.चयन_घातer_state != DRM_SWITCH_POWER_OFF) अणु
		ret = i915_drm_suspend(&i915->drm);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = i915_gem_मुक्तze(i915);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक i915_pm_मुक्तze_late(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *i915 = kdev_to_i915(kdev);
	पूर्णांक ret;

	अगर (i915->drm.चयन_घातer_state != DRM_SWITCH_POWER_OFF) अणु
		ret = i915_drm_suspend_late(&i915->drm, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = i915_gem_मुक्तze_late(i915);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* thaw: called after creating the hibernation image, but beक्रमe turning off. */
अटल पूर्णांक i915_pm_thaw_early(काष्ठा device *kdev)
अणु
	वापस i915_pm_resume_early(kdev);
पूर्ण

अटल पूर्णांक i915_pm_thaw(काष्ठा device *kdev)
अणु
	वापस i915_pm_resume(kdev);
पूर्ण

/* restore: called after loading the hibernation image. */
अटल पूर्णांक i915_pm_restore_early(काष्ठा device *kdev)
अणु
	वापस i915_pm_resume_early(kdev);
पूर्ण

अटल पूर्णांक i915_pm_restore(काष्ठा device *kdev)
अणु
	वापस i915_pm_resume(kdev);
पूर्ण

अटल पूर्णांक पूर्णांकel_runसमय_suspend(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &dev_priv->runसमय_pm;
	पूर्णांक ret;

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !HAS_RUNTIME_PM(dev_priv)))
		वापस -ENODEV;

	drm_dbg_kms(&dev_priv->drm, "Suspending device\n");

	disable_rpm_wakeref_निश्चितs(rpm);

	/*
	 * We are safe here against re-faults, since the fault handler takes
	 * an RPM reference.
	 */
	i915_gem_runसमय_suspend(dev_priv);

	पूर्णांकel_gt_runसमय_suspend(&dev_priv->gt);

	पूर्णांकel_runसमय_pm_disable_पूर्णांकerrupts(dev_priv);

	पूर्णांकel_uncore_suspend(&dev_priv->uncore);

	पूर्णांकel_display_घातer_suspend(dev_priv);

	ret = vlv_suspend_complete(dev_priv);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"Runtime suspend failed, disabling it (%d)\n", ret);
		पूर्णांकel_uncore_runसमय_resume(&dev_priv->uncore);

		पूर्णांकel_runसमय_pm_enable_पूर्णांकerrupts(dev_priv);

		पूर्णांकel_gt_runसमय_resume(&dev_priv->gt);

		enable_rpm_wakeref_निश्चितs(rpm);

		वापस ret;
	पूर्ण

	enable_rpm_wakeref_निश्चितs(rpm);
	पूर्णांकel_runसमय_pm_driver_release(rpm);

	अगर (पूर्णांकel_uncore_arm_unclaimed_mmio_detection(&dev_priv->uncore))
		drm_err(&dev_priv->drm,
			"Unclaimed access detected prior to suspending\n");

	rpm->suspended = true;

	/*
	 * FIXME: We really should find a करोcument that references the arguments
	 * used below!
	 */
	अगर (IS_BROADWELL(dev_priv)) अणु
		/*
		 * On Broadwell, अगर we use PCI_D1 the PCH DDI ports will stop
		 * being detected, and the call we करो at पूर्णांकel_runसमय_resume()
		 * won't be able to restore them. Since PCI_D3hot matches the
		 * actual specअगरication and appears to be working, use it.
		 */
		पूर्णांकel_opregion_notअगरy_adapter(dev_priv, PCI_D3hot);
	पूर्ण अन्यथा अणु
		/*
		 * current versions of firmware which depend on this opregion
		 * notअगरication have repurposed the D1 definition to mean
		 * "runtime suspended" vs. what you would normally expect (D3)
		 * to distinguish it from notअगरications that might be sent via
		 * the suspend path.
		 */
		पूर्णांकel_opregion_notअगरy_adapter(dev_priv, PCI_D1);
	पूर्ण

	निश्चित_क्रमcewakes_inactive(&dev_priv->uncore);

	अगर (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv))
		पूर्णांकel_hpd_poll_enable(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "Device suspended\n");
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_runसमय_resume(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &dev_priv->runसमय_pm;
	पूर्णांक ret;

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !HAS_RUNTIME_PM(dev_priv)))
		वापस -ENODEV;

	drm_dbg_kms(&dev_priv->drm, "Resuming device\n");

	drm_WARN_ON_ONCE(&dev_priv->drm, atomic_पढ़ो(&rpm->wakeref_count));
	disable_rpm_wakeref_निश्चितs(rpm);

	पूर्णांकel_opregion_notअगरy_adapter(dev_priv, PCI_D0);
	rpm->suspended = false;
	अगर (पूर्णांकel_uncore_unclaimed_mmio(&dev_priv->uncore))
		drm_dbg(&dev_priv->drm,
			"Unclaimed access during suspend, bios?\n");

	पूर्णांकel_display_घातer_resume(dev_priv);

	ret = vlv_resume_prepare(dev_priv, true);

	पूर्णांकel_uncore_runसमय_resume(&dev_priv->uncore);

	पूर्णांकel_runसमय_pm_enable_पूर्णांकerrupts(dev_priv);

	/*
	 * No poपूर्णांक of rolling back things in हाल of an error, as the best
	 * we can करो is to hope that things will still work (and disable RPM).
	 */
	पूर्णांकel_gt_runसमय_resume(&dev_priv->gt);

	/*
	 * On VLV/CHV display पूर्णांकerrupts are part of the display
	 * घातer well, so hpd is reinitialized from there. For
	 * everyone अन्यथा करो it here.
	 */
	अगर (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv)) अणु
		पूर्णांकel_hpd_init(dev_priv);
		पूर्णांकel_hpd_poll_disable(dev_priv);
	पूर्ण

	पूर्णांकel_enable_ipc(dev_priv);

	enable_rpm_wakeref_निश्चितs(rpm);

	अगर (ret)
		drm_err(&dev_priv->drm,
			"Runtime resume failed, disabling it (%d)\n", ret);
	अन्यथा
		drm_dbg_kms(&dev_priv->drm, "Device resumed\n");

	वापस ret;
पूर्ण

स्थिर काष्ठा dev_pm_ops i915_pm_ops = अणु
	/*
	 * S0ix (via प्रणाली suspend) and S3 event handlers [PMSG_SUSPEND,
	 * PMSG_RESUME]
	 */
	.prepare = i915_pm_prepare,
	.suspend = i915_pm_suspend,
	.suspend_late = i915_pm_suspend_late,
	.resume_early = i915_pm_resume_early,
	.resume = i915_pm_resume,

	/*
	 * S4 event handlers
	 * @मुक्तze, @मुक्तze_late    : called (1) beक्रमe creating the
	 *                            hibernation image [PMSG_FREEZE] and
	 *                            (2) after rebooting, beक्रमe restoring
	 *                            the image [PMSG_QUIESCE]
	 * @thaw, @thaw_early       : called (1) after creating the hibernation
	 *                            image, beक्रमe writing it [PMSG_THAW]
	 *                            and (2) after failing to create or
	 *                            restore the image [PMSG_RECOVER]
	 * @घातeroff, @घातeroff_late: called after writing the hibernation
	 *                            image, beक्रमe rebooting [PMSG_HIBERNATE]
	 * @restore, @restore_early : called after rebooting and restoring the
	 *                            hibernation image [PMSG_RESTORE]
	 */
	.मुक्तze = i915_pm_मुक्तze,
	.मुक्तze_late = i915_pm_मुक्तze_late,
	.thaw_early = i915_pm_thaw_early,
	.thaw = i915_pm_thaw,
	.घातeroff = i915_pm_suspend,
	.घातeroff_late = i915_pm_घातeroff_late,
	.restore_early = i915_pm_restore_early,
	.restore = i915_pm_restore,

	/* S0ix (via runसमय suspend) event handlers */
	.runसमय_suspend = पूर्णांकel_runसमय_suspend,
	.runसमय_resume = पूर्णांकel_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा file_operations i915_driver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release_noglobal,
	.unlocked_ioctl = drm_ioctl,
	.mmap = i915_gem_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
	.compat_ioctl = i915_ioc32_compat_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक
i915_gem_reject_pin_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file)
अणु
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc i915_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(I915_INIT, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_FLUSH, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_FLIP, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_BATCHBUFFER, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_IRQ_EMIT, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_IRQ_WAIT, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_GETPARAM, i915_getparam_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_SETPARAM, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_ALLOC, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_FREE, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_INIT_HEAP, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_CMDBUFFER, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_DESTROY_HEAP,  drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_SET_VBLANK_PIPE,  drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_GET_VBLANK_PIPE,  drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_VBLANK_SWAP, drm_noop, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_HWS_ADDR, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_GEM_INIT, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_GEM_EXECBUFFER, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(I915_GEM_EXECBUFFER2_WR, i915_gem_execbuffer2_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_PIN, i915_gem_reject_pin_ioctl, DRM_AUTH|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_GEM_UNPIN, i915_gem_reject_pin_ioctl, DRM_AUTH|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_GEM_BUSY, i915_gem_busy_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_SET_CACHING, i915_gem_set_caching_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_GET_CACHING, i915_gem_get_caching_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_THROTTLE, i915_gem_throttle_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_ENTERVT, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_GEM_LEAVEVT, drm_noop, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(I915_GEM_CREATE, i915_gem_create_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_PREAD, i915_gem_pपढ़ो_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_PWRITE, i915_gem_pग_लिखो_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_MMAP, i915_gem_mmap_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_MMAP_OFFSET, i915_gem_mmap_offset_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_SET_DOMAIN, i915_gem_set_करोमुख्य_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_SW_FINISH, i915_gem_sw_finish_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_SET_TILING, i915_gem_set_tiling_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_GET_TILING, i915_gem_get_tiling_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_GET_APERTURE, i915_gem_get_aperture_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GET_PIPE_FROM_CRTC_ID, पूर्णांकel_get_pipe_from_crtc_id_ioctl, 0),
	DRM_IOCTL_DEF_DRV(I915_GEM_MADVISE, i915_gem_madvise_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_OVERLAY_PUT_IMAGE, पूर्णांकel_overlay_put_image_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF_DRV(I915_OVERLAY_ATTRS, पूर्णांकel_overlay_attrs_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF_DRV(I915_SET_SPRITE_COLORKEY, पूर्णांकel_sprite_set_colorkey_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF_DRV(I915_GET_SPRITE_COLORKEY, drm_noop, DRM_MASTER),
	DRM_IOCTL_DEF_DRV(I915_GEM_WAIT, i915_gem_रुको_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_CONTEXT_CREATE_EXT, i915_gem_context_create_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_CONTEXT_DESTROY, i915_gem_context_destroy_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_REG_READ, i915_reg_पढ़ो_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GET_RESET_STATS, i915_gem_context_reset_stats_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_USERPTR, i915_gem_userptr_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_CONTEXT_GETPARAM, i915_gem_context_getparam_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_CONTEXT_SETPARAM, i915_gem_context_setparam_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_PERF_OPEN, i915_perf_खोलो_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_PERF_ADD_CONFIG, i915_perf_add_config_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_PERF_REMOVE_CONFIG, i915_perf_हटाओ_config_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_QUERY, i915_query_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_VM_CREATE, i915_gem_vm_create_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(I915_GEM_VM_DESTROY, i915_gem_vm_destroy_ioctl, DRM_RENDER_ALLOW),
पूर्ण;

अटल स्थिर काष्ठा drm_driver driver = अणु
	/* Don't use MTRRs here; the Xserver or userspace app should
	 * deal with them क्रम Intel hardware.
	 */
	.driver_features =
	    DRIVER_GEM |
	    DRIVER_RENDER | DRIVER_MODESET | DRIVER_ATOMIC | DRIVER_SYNCOBJ |
	    DRIVER_SYNCOBJ_TIMELINE,
	.release = i915_driver_release,
	.खोलो = i915_driver_खोलो,
	.lastबंद = i915_driver_lastबंद,
	.postबंद = i915_driver_postबंद,

	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import = i915_gem_prime_import,

	.dumb_create = i915_gem_dumb_create,
	.dumb_map_offset = i915_gem_dumb_mmap_offset,

	.ioctls = i915_ioctls,
	.num_ioctls = ARRAY_SIZE(i915_ioctls),
	.fops = &i915_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;
