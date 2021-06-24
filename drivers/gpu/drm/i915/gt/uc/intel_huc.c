<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016-2019 Intel Corporation
 */

#समावेश <linux/types.h>

#समावेश "gt/intel_gt.h"
#समावेश "intel_huc.h"
#समावेश "i915_drv.h"

/**
 * DOC: HuC
 *
 * The HuC is a dedicated microcontroller क्रम usage in media HEVC (High
 * Efficiency Video Coding) operations. Userspace can directly use the firmware
 * capabilities by adding HuC specअगरic commands to batch buffers.
 *
 * The kernel driver is only responsible क्रम loading the HuC firmware and
 * triggering its security authentication, which is perक्रमmed by the GuC. For
 * The GuC to correctly perक्रमm the authentication, the HuC binary must be
 * loaded beक्रमe the GuC one. Loading the HuC is optional; however, not using
 * the HuC might negatively impact घातer usage and/or perक्रमmance of media
 * workloads, depending on the use-हालs.
 *
 * See https://github.com/पूर्णांकel/media-driver क्रम the latest details on HuC
 * functionality.
 */

/**
 * DOC: HuC Memory Management
 *
 * Similarly to the GuC, the HuC can't करो any memory allocations on its own,
 * with the dअगरference being that the allocations क्रम HuC usage are handled by
 * the userspace driver instead of the kernel one. The HuC accesses the memory
 * via the PPGTT beदीर्घing to the context loaded on the VCS executing the
 * HuC-specअगरic commands.
 */

व्योम पूर्णांकel_huc_init_early(काष्ठा पूर्णांकel_huc *huc)
अणु
	काष्ठा drm_i915_निजी *i915 = huc_to_gt(huc)->i915;

	पूर्णांकel_uc_fw_init_early(&huc->fw, INTEL_UC_FW_TYPE_HUC);

	अगर (INTEL_GEN(i915) >= 11) अणु
		huc->status.reg = GEN11_HUC_KERNEL_LOAD_INFO;
		huc->status.mask = HUC_LOAD_SUCCESSFUL;
		huc->status.value = HUC_LOAD_SUCCESSFUL;
	पूर्ण अन्यथा अणु
		huc->status.reg = HUC_STATUS2;
		huc->status.mask = HUC_FW_VERIFIED;
		huc->status.value = HUC_FW_VERIFIED;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_huc_rsa_data_create(काष्ठा पूर्णांकel_huc *huc)
अणु
	काष्ठा पूर्णांकel_gt *gt = huc_to_gt(huc);
	काष्ठा पूर्णांकel_guc *guc = &gt->uc.guc;
	काष्ठा i915_vma *vma;
	माप_प्रकार copied;
	व्योम *vaddr;
	पूर्णांक err;

	err = i915_inject_probe_error(gt->i915, -ENXIO);
	अगर (err)
		वापस err;

	/*
	 * HuC firmware will sit above GUC_GGTT_TOP and will not map
	 * through GTT. Unक्रमtunately, this means GuC cannot perक्रमm
	 * the HuC auth. as the rsa offset now falls within the GuC
	 * inaccessible range. We resort to perma-pinning an additional
	 * vma within the accessible range that only contains the rsa
	 * signature. The GuC can use this extra pinning to perक्रमm
	 * the authentication since its GGTT offset will be GuC
	 * accessible.
	 */
	GEM_BUG_ON(huc->fw.rsa_size > PAGE_SIZE);
	vma = पूर्णांकel_guc_allocate_vma(guc, PAGE_SIZE);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	vaddr = i915_gem_object_pin_map_unlocked(vma->obj, I915_MAP_WB);
	अगर (IS_ERR(vaddr)) अणु
		i915_vma_unpin_and_release(&vma, 0);
		वापस PTR_ERR(vaddr);
	पूर्ण

	copied = पूर्णांकel_uc_fw_copy_rsa(&huc->fw, vaddr, vma->size);
	GEM_BUG_ON(copied < huc->fw.rsa_size);

	i915_gem_object_unpin_map(vma->obj);

	huc->rsa_data = vma;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_huc_rsa_data_destroy(काष्ठा पूर्णांकel_huc *huc)
अणु
	i915_vma_unpin_and_release(&huc->rsa_data, 0);
पूर्ण

पूर्णांक पूर्णांकel_huc_init(काष्ठा पूर्णांकel_huc *huc)
अणु
	काष्ठा drm_i915_निजी *i915 = huc_to_gt(huc)->i915;
	पूर्णांक err;

	err = पूर्णांकel_uc_fw_init(&huc->fw);
	अगर (err)
		जाओ out;

	/*
	 * HuC firmware image is outside GuC accessible range.
	 * Copy the RSA signature out of the image पूर्णांकo
	 * a perma-pinned region set aside क्रम it
	 */
	err = पूर्णांकel_huc_rsa_data_create(huc);
	अगर (err)
		जाओ out_fini;

	पूर्णांकel_uc_fw_change_status(&huc->fw, INTEL_UC_FIRMWARE_LOADABLE);

	वापस 0;

out_fini:
	पूर्णांकel_uc_fw_fini(&huc->fw);
out:
	i915_probe_error(i915, "failed with %d\n", err);
	वापस err;
पूर्ण

व्योम पूर्णांकel_huc_fini(काष्ठा पूर्णांकel_huc *huc)
अणु
	अगर (!पूर्णांकel_uc_fw_is_loadable(&huc->fw))
		वापस;

	पूर्णांकel_huc_rsa_data_destroy(huc);
	पूर्णांकel_uc_fw_fini(&huc->fw);
पूर्ण

/**
 * पूर्णांकel_huc_auth() - Authenticate HuC uCode
 * @huc: पूर्णांकel_huc काष्ठाure
 *
 * Called after HuC and GuC firmware loading during पूर्णांकel_uc_init_hw().
 *
 * This function invokes the GuC action to authenticate the HuC firmware,
 * passing the offset of the RSA signature to पूर्णांकel_guc_auth_huc(). It then
 * रुकोs क्रम up to 50ms क्रम firmware verअगरication ACK.
 */
पूर्णांक पूर्णांकel_huc_auth(काष्ठा पूर्णांकel_huc *huc)
अणु
	काष्ठा पूर्णांकel_gt *gt = huc_to_gt(huc);
	काष्ठा पूर्णांकel_guc *guc = &gt->uc.guc;
	पूर्णांक ret;

	GEM_BUG_ON(पूर्णांकel_huc_is_authenticated(huc));

	अगर (!पूर्णांकel_uc_fw_is_loaded(&huc->fw))
		वापस -ENOEXEC;

	ret = i915_inject_probe_error(gt->i915, -ENXIO);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकel_guc_auth_huc(guc,
				 पूर्णांकel_guc_ggtt_offset(guc, huc->rsa_data));
	अगर (ret) अणु
		DRM_ERROR("HuC: GuC did not ack Auth request %d\n", ret);
		जाओ fail;
	पूर्ण

	/* Check authentication status, it should be करोne by now */
	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर(gt->uncore,
					huc->status.reg,
					huc->status.mask,
					huc->status.value,
					2, 50, शून्य);
	अगर (ret) अणु
		DRM_ERROR("HuC: Firmware not verified %d\n", ret);
		जाओ fail;
	पूर्ण

	पूर्णांकel_uc_fw_change_status(&huc->fw, INTEL_UC_FIRMWARE_RUNNING);
	वापस 0;

fail:
	i915_probe_error(gt->i915, "HuC: Authentication failed %d\n", ret);
	पूर्णांकel_uc_fw_change_status(&huc->fw, INTEL_UC_FIRMWARE_FAIL);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_huc_check_status() - check HuC status
 * @huc: पूर्णांकel_huc काष्ठाure
 *
 * This function पढ़ोs status रेजिस्टर to verअगरy अगर HuC
 * firmware was successfully loaded.
 *
 * Returns:
 *  * -ENODEV अगर HuC is not present on this platक्रमm,
 *  * -EOPNOTSUPP अगर HuC firmware is disabled,
 *  * -ENOPKG अगर HuC firmware was not installed,
 *  * -ENOEXEC अगर HuC firmware is invalid or mismatched,
 *  * 0 अगर HuC firmware is not running,
 *  * 1 अगर HuC firmware is authenticated and running.
 */
पूर्णांक पूर्णांकel_huc_check_status(काष्ठा पूर्णांकel_huc *huc)
अणु
	काष्ठा पूर्णांकel_gt *gt = huc_to_gt(huc);
	पूर्णांकel_wakeref_t wakeref;
	u32 status = 0;

	चयन (__पूर्णांकel_uc_fw_status(&huc->fw)) अणु
	हाल INTEL_UC_FIRMWARE_NOT_SUPPORTED:
		वापस -ENODEV;
	हाल INTEL_UC_FIRMWARE_DISABLED:
		वापस -EOPNOTSUPP;
	हाल INTEL_UC_FIRMWARE_MISSING:
		वापस -ENOPKG;
	हाल INTEL_UC_FIRMWARE_ERROR:
		वापस -ENOEXEC;
	शेष:
		अवरोध;
	पूर्ण

	with_पूर्णांकel_runसमय_pm(gt->uncore->rpm, wakeref)
		status = पूर्णांकel_uncore_पढ़ो(gt->uncore, huc->status.reg);

	वापस (status & huc->status.mask) == huc->status.value;
पूर्ण

/**
 * पूर्णांकel_huc_load_status - dump inक्रमmation about HuC load status
 * @huc: the HuC
 * @p: the &drm_prपूर्णांकer
 *
 * Pretty prपूर्णांकer क्रम HuC load status.
 */
व्योम पूर्णांकel_huc_load_status(काष्ठा पूर्णांकel_huc *huc, काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा पूर्णांकel_gt *gt = huc_to_gt(huc);
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_huc_is_supported(huc)) अणु
		drm_म_लिखो(p, "HuC not supported\n");
		वापस;
	पूर्ण

	अगर (!पूर्णांकel_huc_is_wanted(huc)) अणु
		drm_म_लिखो(p, "HuC disabled\n");
		वापस;
	पूर्ण

	पूर्णांकel_uc_fw_dump(&huc->fw, p);

	with_पूर्णांकel_runसमय_pm(gt->uncore->rpm, wakeref)
		drm_म_लिखो(p, "HuC status: 0x%08x\n",
			   पूर्णांकel_uncore_पढ़ो(gt->uncore, huc->status.reg));
पूर्ण
