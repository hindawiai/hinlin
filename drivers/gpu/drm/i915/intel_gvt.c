<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "i915_drv.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_gvt.h"
#समावेश "gvt/gvt.h"

/**
 * DOC: Intel GVT-g host support
 *
 * Intel GVT-g is a graphics भवization technology which shares the
 * GPU among multiple भव machines on a समय-sharing basis. Each
 * भव machine is presented a भव GPU (vGPU), which has equivalent
 * features as the underlying physical GPU (pGPU), so i915 driver can run
 * seamlessly in a भव machine.
 *
 * To भवize GPU resources GVT-g driver depends on hypervisor technology
 * e.g KVM/VFIO/mdev, Xen, etc. to provide resource access trapping capability
 * and be भवized within GVT-g device module. More architectural design
 * करोc is available on https://01.org/group/2230/करोcumentation-list.
 */

अटल bool is_supported_device(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_BROADWELL(dev_priv))
		वापस true;
	अगर (IS_SKYLAKE(dev_priv))
		वापस true;
	अगर (IS_KABYLAKE(dev_priv))
		वापस true;
	अगर (IS_BROXTON(dev_priv))
		वापस true;
	अगर (IS_COFFEELAKE(dev_priv))
		वापस true;
	अगर (IS_COMETLAKE(dev_priv))
		वापस true;

	वापस false;
पूर्ण

/**
 * पूर्णांकel_gvt_sanitize_options - sanitize GVT related options
 * @dev_priv: drm i915 निजी data
 *
 * This function is called at the i915 options sanitize stage.
 */
व्योम पूर्णांकel_gvt_sanitize_options(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!dev_priv->params.enable_gvt)
		वापस;

	अगर (पूर्णांकel_vgpu_active(dev_priv)) अणु
		drm_info(&dev_priv->drm, "GVT-g is disabled for guest\n");
		जाओ bail;
	पूर्ण

	अगर (!is_supported_device(dev_priv)) अणु
		drm_info(&dev_priv->drm,
			 "Unsupported device. GVT-g is disabled\n");
		जाओ bail;
	पूर्ण

	वापस;
bail:
	dev_priv->params.enable_gvt = 0;
पूर्ण

/**
 * पूर्णांकel_gvt_init - initialize GVT components
 * @dev_priv: drm i915 निजी data
 *
 * This function is called at the initialization stage to create a GVT device.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_gvt_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	अगर (i915_inject_probe_failure(dev_priv))
		वापस -ENODEV;

	अगर (!dev_priv->params.enable_gvt) अणु
		drm_dbg(&dev_priv->drm,
			"GVT-g is disabled by kernel params\n");
		वापस 0;
	पूर्ण

	अगर (पूर्णांकel_uc_wants_guc_submission(&dev_priv->gt.uc)) अणु
		drm_err(&dev_priv->drm,
			"i915 GVT-g loading failed due to Graphics virtualization is not yet supported with GuC submission\n");
		वापस -EIO;
	पूर्ण

	ret = पूर्णांकel_gvt_init_device(dev_priv);
	अगर (ret) अणु
		drm_dbg(&dev_priv->drm, "Fail to init GVT device\n");
		जाओ bail;
	पूर्ण

	वापस 0;

bail:
	dev_priv->params.enable_gvt = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_gvt_active(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस dev_priv->gvt;
पूर्ण

/**
 * पूर्णांकel_gvt_driver_हटाओ - cleanup GVT components when i915 driver is
 *			     unbinding
 * @dev_priv: drm i915 निजी *
 *
 * This function is called at the i915 driver unloading stage, to shutकरोwn
 * GVT components and release the related resources.
 */
व्योम पूर्णांकel_gvt_driver_हटाओ(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!पूर्णांकel_gvt_active(dev_priv))
		वापस;

	पूर्णांकel_gvt_clean_device(dev_priv);
पूर्ण

/**
 * पूर्णांकel_gvt_resume - GVT resume routine wapper
 *
 * @dev_priv: drm i915 निजी *
 *
 * This function is called at the i915 driver resume stage to restore required
 * HW status क्रम GVT so that vGPU can जारी running after resumed.
 */
व्योम पूर्णांकel_gvt_resume(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (पूर्णांकel_gvt_active(dev_priv))
		पूर्णांकel_gvt_pm_resume(dev_priv->gvt);
पूर्ण
