<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 */

#समावेश "gem/i915_gem_mman.h"
#समावेश "gt/intel_engine_user.h"

#समावेश "i915_drv.h"
#समावेश "i915_perf.h"

पूर्णांक i915_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	स्थिर काष्ठा sseu_dev_info *sseu = &i915->gt.info.sseu;
	drm_i915_getparam_t *param = data;
	पूर्णांक value;

	चयन (param->param) अणु
	हाल I915_PARAM_IRQ_ACTIVE:
	हाल I915_PARAM_ALLOW_BATCHBUFFER:
	हाल I915_PARAM_LAST_DISPATCH:
	हाल I915_PARAM_HAS_EXEC_CONSTANTS:
		/* Reject all old ums/dri params. */
		वापस -ENODEV;
	हाल I915_PARAM_CHIPSET_ID:
		value = pdev->device;
		अवरोध;
	हाल I915_PARAM_REVISION:
		value = pdev->revision;
		अवरोध;
	हाल I915_PARAM_NUM_FENCES_AVAIL:
		value = i915->ggtt.num_fences;
		अवरोध;
	हाल I915_PARAM_HAS_OVERLAY:
		value = !!i915->overlay;
		अवरोध;
	हाल I915_PARAM_HAS_BSD:
		value = !!पूर्णांकel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_VIDEO, 0);
		अवरोध;
	हाल I915_PARAM_HAS_BLT:
		value = !!पूर्णांकel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_COPY, 0);
		अवरोध;
	हाल I915_PARAM_HAS_VEBOX:
		value = !!पूर्णांकel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_VIDEO_ENHANCE, 0);
		अवरोध;
	हाल I915_PARAM_HAS_BSD2:
		value = !!पूर्णांकel_engine_lookup_user(i915,
						   I915_ENGINE_CLASS_VIDEO, 1);
		अवरोध;
	हाल I915_PARAM_HAS_LLC:
		value = HAS_LLC(i915);
		अवरोध;
	हाल I915_PARAM_HAS_WT:
		value = HAS_WT(i915);
		अवरोध;
	हाल I915_PARAM_HAS_ALIASING_PPGTT:
		value = INTEL_PPGTT(i915);
		अवरोध;
	हाल I915_PARAM_HAS_SEMAPHORES:
		value = !!(i915->caps.scheduler & I915_SCHEDULER_CAP_SEMAPHORES);
		अवरोध;
	हाल I915_PARAM_HAS_SECURE_BATCHES:
		value = HAS_SECURE_BATCHES(i915) && capable(CAP_SYS_ADMIN);
		अवरोध;
	हाल I915_PARAM_CMD_PARSER_VERSION:
		value = i915_cmd_parser_get_version(i915);
		अवरोध;
	हाल I915_PARAM_SUBSLICE_TOTAL:
		value = पूर्णांकel_sseu_subslice_total(sseu);
		अगर (!value)
			वापस -ENODEV;
		अवरोध;
	हाल I915_PARAM_EU_TOTAL:
		value = sseu->eu_total;
		अगर (!value)
			वापस -ENODEV;
		अवरोध;
	हाल I915_PARAM_HAS_GPU_RESET:
		value = i915->params.enable_hangcheck &&
			पूर्णांकel_has_gpu_reset(&i915->gt);
		अगर (value && पूर्णांकel_has_reset_engine(&i915->gt))
			value = 2;
		अवरोध;
	हाल I915_PARAM_HAS_RESOURCE_STREAMER:
		value = 0;
		अवरोध;
	हाल I915_PARAM_HAS_POOLED_EU:
		value = HAS_POOLED_EU(i915);
		अवरोध;
	हाल I915_PARAM_MIN_EU_IN_POOL:
		value = sseu->min_eu_in_pool;
		अवरोध;
	हाल I915_PARAM_HUC_STATUS:
		value = पूर्णांकel_huc_check_status(&i915->gt.uc.huc);
		अगर (value < 0)
			वापस value;
		अवरोध;
	हाल I915_PARAM_MMAP_GTT_VERSION:
		/* Though we've started our numbering from 1, and so class all
		 * earlier versions as 0, in effect their value is undefined as
		 * the ioctl will report EINVAL क्रम the unknown param!
		 */
		value = i915_gem_mmap_gtt_version();
		अवरोध;
	हाल I915_PARAM_HAS_SCHEDULER:
		value = i915->caps.scheduler;
		अवरोध;

	हाल I915_PARAM_MMAP_VERSION:
		/* Remember to bump this अगर the version changes! */
	हाल I915_PARAM_HAS_GEM:
	हाल I915_PARAM_HAS_PAGEFLIPPING:
	हाल I915_PARAM_HAS_EXECBUF2: /* depends on GEM */
	हाल I915_PARAM_HAS_RELAXED_FENCING:
	हाल I915_PARAM_HAS_COHERENT_RINGS:
	हाल I915_PARAM_HAS_RELAXED_DELTA:
	हाल I915_PARAM_HAS_GEN7_SOL_RESET:
	हाल I915_PARAM_HAS_WAIT_TIMEOUT:
	हाल I915_PARAM_HAS_PRIME_VMAP_FLUSH:
	हाल I915_PARAM_HAS_PINNED_BATCHES:
	हाल I915_PARAM_HAS_EXEC_NO_RELOC:
	हाल I915_PARAM_HAS_EXEC_HANDLE_LUT:
	हाल I915_PARAM_HAS_COHERENT_PHYS_GTT:
	हाल I915_PARAM_HAS_EXEC_SOFTPIN:
	हाल I915_PARAM_HAS_EXEC_ASYNC:
	हाल I915_PARAM_HAS_EXEC_FENCE:
	हाल I915_PARAM_HAS_EXEC_CAPTURE:
	हाल I915_PARAM_HAS_EXEC_BATCH_FIRST:
	हाल I915_PARAM_HAS_EXEC_FENCE_ARRAY:
	हाल I915_PARAM_HAS_EXEC_SUBMIT_FENCE:
	हाल I915_PARAM_HAS_EXEC_TIMELINE_FENCES:
		/* For the समय being all of these are always true;
		 * अगर some supported hardware करोes not have one of these
		 * features this value needs to be provided from
		 * INTEL_INFO(), a feature macro, or similar.
		 */
		value = 1;
		अवरोध;
	हाल I915_PARAM_HAS_CONTEXT_ISOLATION:
		value = पूर्णांकel_engines_has_context_isolation(i915);
		अवरोध;
	हाल I915_PARAM_SLICE_MASK:
		value = sseu->slice_mask;
		अगर (!value)
			वापस -ENODEV;
		अवरोध;
	हाल I915_PARAM_SUBSLICE_MASK:
		value = sseu->subslice_mask[0];
		अगर (!value)
			वापस -ENODEV;
		अवरोध;
	हाल I915_PARAM_CS_TIMESTAMP_FREQUENCY:
		value = i915->gt.घड़ी_frequency;
		अवरोध;
	हाल I915_PARAM_MMAP_GTT_COHERENT:
		value = INTEL_INFO(i915)->has_coherent_ggtt;
		अवरोध;
	हाल I915_PARAM_PERF_REVISION:
		value = i915_perf_ioctl_version();
		अवरोध;
	शेष:
		DRM_DEBUG("Unknown parameter %d\n", param->param);
		वापस -EINVAL;
	पूर्ण

	अगर (put_user(value, param->value))
		वापस -EFAULT;

	वापस 0;
पूर्ण
