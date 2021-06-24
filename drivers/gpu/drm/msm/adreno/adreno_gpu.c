<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 *
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/ascii85.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/mdt_loader.h>
#समावेश <soc/qcom/ocस्मृति.स>
#समावेश "adreno_gpu.h"
#समावेश "a6xx_gpu.h"
#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"

अटल bool zap_available = true;

अटल पूर्णांक zap_shader_load_mdt(काष्ठा msm_gpu *gpu, स्थिर अक्षर *fwname,
		u32 pasid)
अणु
	काष्ठा device *dev = &gpu->pdev->dev;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *चिन्हित_fwname = शून्य;
	काष्ठा device_node *np, *mem_np;
	काष्ठा resource r;
	phys_addr_t mem_phys;
	sमाप_प्रकार mem_size;
	व्योम *mem_region = शून्य;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_ARCH_QCOM)) अणु
		zap_available = false;
		वापस -EINVAL;
	पूर्ण

	np = of_get_child_by_name(dev->of_node, "zap-shader");
	अगर (!np) अणु
		zap_available = false;
		वापस -ENODEV;
	पूर्ण

	mem_np = of_parse_phandle(np, "memory-region", 0);
	of_node_put(np);
	अगर (!mem_np) अणु
		zap_available = false;
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(mem_np, 0, &r);
	of_node_put(mem_np);
	अगर (ret)
		वापस ret;

	mem_phys = r.start;

	/*
	 * Check क्रम a firmware-name property.  This is the new scheme
	 * to handle firmware that may be चिन्हित with device specअगरic
	 * keys, allowing us to have a dअगरferent zap fw path क्रम dअगरferent
	 * devices.
	 *
	 * If the firmware-name property is found, we bypass the
	 * adreno_request_fw() mechanism, because we करोn't need to handle
	 * the /lib/firmware/qcom/... vs /lib/firmware/... हाल.
	 *
	 * If the firmware-name property is not found, क्रम backwards
	 * compatibility we fall back to the fwname from the gpulist
	 * table.
	 */
	of_property_पढ़ो_string_index(np, "firmware-name", 0, &चिन्हित_fwname);
	अगर (चिन्हित_fwname) अणु
		fwname = चिन्हित_fwname;
		ret = request_firmware_direct(&fw, fwname, gpu->dev->dev);
		अगर (ret)
			fw = ERR_PTR(ret);
	पूर्ण अन्यथा अगर (fwname) अणु
		/* Request the MDT file from the शेष location: */
		fw = adreno_request_fw(to_adreno_gpu(gpu), fwname);
	पूर्ण अन्यथा अणु
		/*
		 * For new tarमाला_लो, we require the firmware-name property,
		 * अगर a zap-shader is required, rather than falling back
		 * to a firmware name specअगरied in gpulist.
		 *
		 * Because the firmware is चिन्हित with a (potentially)
		 * device specअगरic key, having the name come from gpulist
		 * was a bad idea, and is only provided क्रम backwards
		 * compatibility क्रम older tarमाला_लो.
		 */
		वापस -ENODEV;
	पूर्ण

	अगर (IS_ERR(fw)) अणु
		DRM_DEV_ERROR(dev, "Unable to load %s\n", fwname);
		वापस PTR_ERR(fw);
	पूर्ण

	/* Figure out how much memory we need */
	mem_size = qcom_mdt_get_size(fw);
	अगर (mem_size < 0) अणु
		ret = mem_size;
		जाओ out;
	पूर्ण

	अगर (mem_size > resource_size(&r)) अणु
		DRM_DEV_ERROR(dev,
			"memory region is too small to load the MDT\n");
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	/* Allocate memory क्रम the firmware image */
	mem_region = memremap(mem_phys, mem_size,  MEMREMAP_WC);
	अगर (!mem_region) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Load the rest of the MDT
	 *
	 * Note that we could be dealing with two dअगरferent paths, since
	 * with upstream linux-firmware it would be in a qcom/ subdir..
	 * adreno_request_fw() handles this, but qcom_mdt_load() करोes
	 * not.  But since we've alपढ़ोy gotten through adreno_request_fw()
	 * we know which of the two हालs it is:
	 */
	अगर (चिन्हित_fwname || (to_adreno_gpu(gpu)->fwloc == FW_LOCATION_LEGACY)) अणु
		ret = qcom_mdt_load(dev, fw, fwname, pasid,
				mem_region, mem_phys, mem_size, शून्य);
	पूर्ण अन्यथा अणु
		अक्षर *newname;

		newname = kaप्र_लिखो(GFP_KERNEL, "qcom/%s", fwname);

		ret = qcom_mdt_load(dev, fw, newname, pasid,
				mem_region, mem_phys, mem_size, शून्य);
		kमुक्त(newname);
	पूर्ण
	अगर (ret)
		जाओ out;

	/* Send the image to the secure world */
	ret = qcom_scm_pas_auth_and_reset(pasid);

	/*
	 * If the scm call वापसs -EOPNOTSUPP we assume that this target
	 * करोesn't need/support the zap shader so quietly fail
	 */
	अगर (ret == -EOPNOTSUPP)
		zap_available = false;
	अन्यथा अगर (ret)
		DRM_DEV_ERROR(dev, "Unable to authorize the image\n");

out:
	अगर (mem_region)
		memunmap(mem_region);

	release_firmware(fw);

	वापस ret;
पूर्ण

पूर्णांक adreno_zap_shader_load(काष्ठा msm_gpu *gpu, u32 pasid)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा platक्रमm_device *pdev = gpu->pdev;

	/* Short cut अगर we determine the zap shader isn't available/needed */
	अगर (!zap_available)
		वापस -ENODEV;

	/* We need SCM to be able to load the firmware */
	अगर (!qcom_scm_is_available()) अणु
		DRM_DEV_ERROR(&pdev->dev, "SCM is not available\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	वापस zap_shader_load_mdt(gpu, adreno_gpu->info->zapfw, pasid);
पूर्ण

व्योम adreno_set_llc_attributes(काष्ठा iommu_करोमुख्य *iommu)
अणु
	iommu_set_pgtable_quirks(iommu, IO_PGTABLE_QUIRK_ARM_OUTER_WBWA);
पूर्ण

काष्ठा msm_gem_address_space *
adreno_iommu_create_address_space(काष्ठा msm_gpu *gpu,
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iommu_करोमुख्य *iommu;
	काष्ठा msm_mmu *mmu;
	काष्ठा msm_gem_address_space *aspace;
	u64 start, size;

	iommu = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!iommu)
		वापस शून्य;

	mmu = msm_iommu_new(&pdev->dev, iommu);
	अगर (IS_ERR(mmu)) अणु
		iommu_करोमुख्य_मुक्त(iommu);
		वापस ERR_CAST(mmu);
	पूर्ण

	/*
	 * Use the aperture start or SZ_16M, whichever is greater. This will
	 * ensure that we align with the allocated pagetable range जबतक still
	 * allowing room in the lower 32 bits क्रम GMEM and whatnot
	 */
	start = max_t(u64, SZ_16M, iommu->geometry.aperture_start);
	size = iommu->geometry.aperture_end - start + 1;

	aspace = msm_gem_address_space_create(mmu, "gpu",
		start & GENMASK_ULL(48, 0), size);

	अगर (IS_ERR(aspace) && !IS_ERR(mmu))
		mmu->funcs->destroy(mmu);

	वापस aspace;
पूर्ण

पूर्णांक adreno_get_param(काष्ठा msm_gpu *gpu, uपूर्णांक32_t param, uपूर्णांक64_t *value)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);

	चयन (param) अणु
	हाल MSM_PARAM_GPU_ID:
		*value = adreno_gpu->info->revn;
		वापस 0;
	हाल MSM_PARAM_GMEM_SIZE:
		*value = adreno_gpu->gmem;
		वापस 0;
	हाल MSM_PARAM_GMEM_BASE:
		*value = !adreno_is_a650(adreno_gpu) ? 0x100000 : 0;
		वापस 0;
	हाल MSM_PARAM_CHIP_ID:
		*value = adreno_gpu->rev.patchid |
				(adreno_gpu->rev.minor << 8) |
				(adreno_gpu->rev.major << 16) |
				(adreno_gpu->rev.core << 24);
		वापस 0;
	हाल MSM_PARAM_MAX_FREQ:
		*value = adreno_gpu->base.fast_rate;
		वापस 0;
	हाल MSM_PARAM_TIMESTAMP:
		अगर (adreno_gpu->funcs->get_बारtamp) अणु
			पूर्णांक ret;

			pm_runसमय_get_sync(&gpu->pdev->dev);
			ret = adreno_gpu->funcs->get_बारtamp(gpu, value);
			pm_runसमय_put_स्वतःsuspend(&gpu->pdev->dev);

			वापस ret;
		पूर्ण
		वापस -EINVAL;
	हाल MSM_PARAM_NR_RINGS:
		*value = gpu->nr_rings;
		वापस 0;
	हाल MSM_PARAM_PP_PGTABLE:
		*value = 0;
		वापस 0;
	हाल MSM_PARAM_FAULTS:
		*value = gpu->global_faults;
		वापस 0;
	हाल MSM_PARAM_SUSPENDS:
		*value = gpu->suspend_count;
		वापस 0;
	शेष:
		DBG("%s: invalid param: %u", gpu->name, param);
		वापस -EINVAL;
	पूर्ण
पूर्ण

स्थिर काष्ठा firmware *
adreno_request_fw(काष्ठा adreno_gpu *adreno_gpu, स्थिर अक्षर *fwname)
अणु
	काष्ठा drm_device *drm = adreno_gpu->base.dev;
	स्थिर काष्ठा firmware *fw = शून्य;
	अक्षर *newname;
	पूर्णांक ret;

	newname = kaप्र_लिखो(GFP_KERNEL, "qcom/%s", fwname);
	अगर (!newname)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Try first to load from qcom/$fwfile using a direct load (to aव्योम
	 * a potential समयout रुकोing क्रम usermode helper)
	 */
	अगर ((adreno_gpu->fwloc == FW_LOCATION_UNKNOWN) ||
	    (adreno_gpu->fwloc == FW_LOCATION_NEW)) अणु

		ret = request_firmware_direct(&fw, newname, drm->dev);
		अगर (!ret) अणु
			DRM_DEV_INFO(drm->dev, "loaded %s from new location\n",
				newname);
			adreno_gpu->fwloc = FW_LOCATION_NEW;
			जाओ out;
		पूर्ण अन्यथा अगर (adreno_gpu->fwloc != FW_LOCATION_UNKNOWN) अणु
			DRM_DEV_ERROR(drm->dev, "failed to load %s: %d\n",
				newname, ret);
			fw = ERR_PTR(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Then try the legacy location without qcom/ prefix
	 */
	अगर ((adreno_gpu->fwloc == FW_LOCATION_UNKNOWN) ||
	    (adreno_gpu->fwloc == FW_LOCATION_LEGACY)) अणु

		ret = request_firmware_direct(&fw, fwname, drm->dev);
		अगर (!ret) अणु
			DRM_DEV_INFO(drm->dev, "loaded %s from legacy location\n",
				newname);
			adreno_gpu->fwloc = FW_LOCATION_LEGACY;
			जाओ out;
		पूर्ण अन्यथा अगर (adreno_gpu->fwloc != FW_LOCATION_UNKNOWN) अणु
			DRM_DEV_ERROR(drm->dev, "failed to load %s: %d\n",
				fwname, ret);
			fw = ERR_PTR(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Finally fall back to request_firmware() क्रम हालs where the
	 * usermode helper is needed (I think मुख्यly android)
	 */
	अगर ((adreno_gpu->fwloc == FW_LOCATION_UNKNOWN) ||
	    (adreno_gpu->fwloc == FW_LOCATION_HELPER)) अणु

		ret = request_firmware(&fw, newname, drm->dev);
		अगर (!ret) अणु
			DRM_DEV_INFO(drm->dev, "loaded %s with helper\n",
				newname);
			adreno_gpu->fwloc = FW_LOCATION_HELPER;
			जाओ out;
		पूर्ण अन्यथा अगर (adreno_gpu->fwloc != FW_LOCATION_UNKNOWN) अणु
			DRM_DEV_ERROR(drm->dev, "failed to load %s: %d\n",
				newname, ret);
			fw = ERR_PTR(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	DRM_DEV_ERROR(drm->dev, "failed to load %s\n", fwname);
	fw = ERR_PTR(-ENOENT);
out:
	kमुक्त(newname);
	वापस fw;
पूर्ण

पूर्णांक adreno_load_fw(काष्ठा adreno_gpu *adreno_gpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adreno_gpu->info->fw); i++) अणु
		स्थिर काष्ठा firmware *fw;

		अगर (!adreno_gpu->info->fw[i])
			जारी;

		/* Skip अगर the firmware has alपढ़ोy been loaded */
		अगर (adreno_gpu->fw[i])
			जारी;

		fw = adreno_request_fw(adreno_gpu, adreno_gpu->info->fw[i]);
		अगर (IS_ERR(fw))
			वापस PTR_ERR(fw);

		adreno_gpu->fw[i] = fw;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा drm_gem_object *adreno_fw_create_bo(काष्ठा msm_gpu *gpu,
		स्थिर काष्ठा firmware *fw, u64 *iova)
अणु
	काष्ठा drm_gem_object *bo;
	व्योम *ptr;

	ptr = msm_gem_kernel_new_locked(gpu->dev, fw->size - 4,
		MSM_BO_UNCACHED | MSM_BO_GPU_READONLY, gpu->aspace, &bo, iova);

	अगर (IS_ERR(ptr))
		वापस ERR_CAST(ptr);

	स_नकल(ptr, &fw->data[4], fw->size - 4);

	msm_gem_put_vaddr(bo);

	वापस bo;
पूर्ण

पूर्णांक adreno_hw_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक ret, i;

	DBG("%s", gpu->name);

	ret = adreno_load_fw(adreno_gpu);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		काष्ठा msm_ringbuffer *ring = gpu->rb[i];

		अगर (!ring)
			जारी;

		ring->cur = ring->start;
		ring->next = ring->start;

		/* reset completed fence seqno: */
		ring->memptrs->fence = ring->fctx->completed_fence;
		ring->memptrs->rptr = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Use this helper to पढ़ो rptr, since a430 करोesn't update rptr in memory */
अटल uपूर्णांक32_t get_rptr(काष्ठा adreno_gpu *adreno_gpu,
		काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;

	वापस gpu->funcs->get_rptr(gpu, ring);
पूर्ण

काष्ठा msm_ringbuffer *adreno_active_ring(काष्ठा msm_gpu *gpu)
अणु
	वापस gpu->rb[0];
पूर्ण

व्योम adreno_recover(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा drm_device *dev = gpu->dev;
	पूर्णांक ret;

	// XXX pm-runसमय??  we *need* the device to be off after this
	// so maybe continuing to call ->pm_suspend/resume() is better?

	gpu->funcs->pm_suspend(gpu);
	gpu->funcs->pm_resume(gpu);

	ret = msm_gpu_hw_init(gpu);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "gpu hw init failed: %d\n", ret);
		/* hmm, oh well? */
	पूर्ण
पूर्ण

व्योम adreno_flush(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring, u32 reg)
अणु
	uपूर्णांक32_t wptr;

	/* Copy the shaकरोw to the actual रेजिस्टर */
	ring->cur = ring->next;

	/*
	 * Mask wptr value that we calculate to fit in the HW range. This is
	 * to account क्रम the possibility that the last command fit exactly पूर्णांकo
	 * the ringbuffer and rb->next hasn't wrapped to zero yet
	 */
	wptr = get_wptr(ring);

	/* ensure ग_लिखोs to ringbuffer have hit प्रणाली memory: */
	mb();

	gpu_ग_लिखो(gpu, reg, wptr);
पूर्ण

bool adreno_idle(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	uपूर्णांक32_t wptr = get_wptr(ring);

	/* रुको क्रम CP to drain ringbuffer: */
	अगर (!spin_until(get_rptr(adreno_gpu, ring) == wptr))
		वापस true;

	/* TODO maybe we need to reset GPU here to recover from hang? */
	DRM_ERROR("%s: timeout waiting to drain ringbuffer %d rptr/wptr = %X/%X\n",
		gpu->name, ring->id, get_rptr(adreno_gpu, ring), wptr);

	वापस false;
पूर्ण

पूर्णांक adreno_gpu_state_get(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक i, count = 0;

	kref_init(&state->ref);

	kसमय_get_real_ts64(&state->समय);

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		पूर्णांक size = 0, j;

		state->ring[i].fence = gpu->rb[i]->memptrs->fence;
		state->ring[i].iova = gpu->rb[i]->iova;
		state->ring[i].seqno = gpu->rb[i]->seqno;
		state->ring[i].rptr = get_rptr(adreno_gpu, gpu->rb[i]);
		state->ring[i].wptr = get_wptr(gpu->rb[i]);

		/* Copy at least 'wptr' dwords of the data */
		size = state->ring[i].wptr;

		/* After wptr find the last non zero dword to save space */
		क्रम (j = state->ring[i].wptr; j < MSM_GPU_RINGBUFFER_SZ >> 2; j++)
			अगर (gpu->rb[i]->start[j])
				size = j + 1;

		अगर (size) अणु
			state->ring[i].data = kvदो_स्मृति(size << 2, GFP_KERNEL);
			अगर (state->ring[i].data) अणु
				स_नकल(state->ring[i].data, gpu->rb[i]->start, size << 2);
				state->ring[i].data_size = size << 2;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Some tarमाला_लो prefer to collect their own रेजिस्टरs */
	अगर (!adreno_gpu->रेजिस्टरs)
		वापस 0;

	/* Count the number of रेजिस्टरs */
	क्रम (i = 0; adreno_gpu->रेजिस्टरs[i] != ~0; i += 2)
		count += adreno_gpu->रेजिस्टरs[i + 1] -
			adreno_gpu->रेजिस्टरs[i] + 1;

	state->रेजिस्टरs = kसुस्मृति(count * 2, माप(u32), GFP_KERNEL);
	अगर (state->रेजिस्टरs) अणु
		पूर्णांक pos = 0;

		क्रम (i = 0; adreno_gpu->रेजिस्टरs[i] != ~0; i += 2) अणु
			u32 start = adreno_gpu->रेजिस्टरs[i];
			u32 end   = adreno_gpu->रेजिस्टरs[i + 1];
			u32 addr;

			क्रम (addr = start; addr <= end; addr++) अणु
				state->रेजिस्टरs[pos++] = addr;
				state->रेजिस्टरs[pos++] = gpu_पढ़ो(gpu, addr);
			पूर्ण
		पूर्ण

		state->nr_रेजिस्टरs = count;
	पूर्ण

	वापस 0;
पूर्ण

व्योम adreno_gpu_state_destroy(काष्ठा msm_gpu_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(state->ring); i++)
		kvमुक्त(state->ring[i].data);

	क्रम (i = 0; state->bos && i < state->nr_bos; i++)
		kvमुक्त(state->bos[i].data);

	kमुक्त(state->bos);
	kमुक्त(state->comm);
	kमुक्त(state->cmd);
	kमुक्त(state->रेजिस्टरs);
पूर्ण

अटल व्योम adreno_gpu_state_kref_destroy(काष्ठा kref *kref)
अणु
	काष्ठा msm_gpu_state *state = container_of(kref,
		काष्ठा msm_gpu_state, ref);

	adreno_gpu_state_destroy(state);
	kमुक्त(state);
पूर्ण

पूर्णांक adreno_gpu_state_put(काष्ठा msm_gpu_state *state)
अणु
	अगर (IS_ERR_OR_शून्य(state))
		वापस 1;

	वापस kref_put(&state->ref, adreno_gpu_state_kref_destroy);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COREDUMP)

अटल अक्षर *adreno_gpu_ascii85_encode(u32 *src, माप_प्रकार len)
अणु
	व्योम *buf;
	माप_प्रकार buf_itr = 0, buffer_size;
	अक्षर out[ASCII85_BUFSZ];
	दीर्घ l;
	पूर्णांक i;

	अगर (!src || !len)
		वापस शून्य;

	l = ascii85_encode_len(len);

	/*
	 * Ascii85 outमाला_दो either a 5 byte string or a 1 byte string. So we
	 * account क्रम the worst हाल of 5 bytes per dword plus the 1 क्रम '\0'
	 */
	buffer_size = (l * 5) + 1;

	buf = kvदो_स्मृति(buffer_size, GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	क्रम (i = 0; i < l; i++)
		buf_itr += scnम_लिखो(buf + buf_itr, buffer_size - buf_itr, "%s",
				ascii85_encode(src[i], out));

	वापस buf;
पूर्ण

/* len is expected to be in bytes */
अटल व्योम adreno_show_object(काष्ठा drm_prपूर्णांकer *p, व्योम **ptr, पूर्णांक len,
		bool *encoded)
अणु
	अगर (!*ptr || !len)
		वापस;

	अगर (!*encoded) अणु
		दीर्घ datalen, i;
		u32 *buf = *ptr;

		/*
		 * Only dump the non-zero part of the buffer - rarely will
		 * any data completely fill the entire allocated size of
		 * the buffer.
		 */
		क्रम (datalen = 0, i = 0; i < len >> 2; i++)
			अगर (buf[i])
				datalen = ((i + 1) << 2);

		/*
		 * If we reach here, then the originally captured binary buffer
		 * will be replaced with the ascii85 encoded string
		 */
		*ptr = adreno_gpu_ascii85_encode(buf, datalen);

		kvमुक्त(buf);

		*encoded = true;
	पूर्ण

	अगर (!*ptr)
		वापस;

	drm_माला_दो(p, "    data: !!ascii85 |\n");
	drm_माला_दो(p, "     ");

	drm_माला_दो(p, *ptr);

	drm_माला_दो(p, "\n");
पूर्ण

व्योम adreno_show(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(state))
		वापस;

	drm_म_लिखो(p, "revision: %d (%d.%d.%d.%d)\n",
			adreno_gpu->info->revn, adreno_gpu->rev.core,
			adreno_gpu->rev.major, adreno_gpu->rev.minor,
			adreno_gpu->rev.patchid);

	drm_म_लिखो(p, "rbbm-status: 0x%08x\n", state->rbbm_status);

	drm_माला_दो(p, "ringbuffer:\n");

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		drm_म_लिखो(p, "  - id: %d\n", i);
		drm_म_लिखो(p, "    iova: 0x%016llx\n", state->ring[i].iova);
		drm_म_लिखो(p, "    last-fence: %d\n", state->ring[i].seqno);
		drm_म_लिखो(p, "    retired-fence: %d\n", state->ring[i].fence);
		drm_म_लिखो(p, "    rptr: %d\n", state->ring[i].rptr);
		drm_म_लिखो(p, "    wptr: %d\n", state->ring[i].wptr);
		drm_म_लिखो(p, "    size: %d\n", MSM_GPU_RINGBUFFER_SZ);

		adreno_show_object(p, &state->ring[i].data,
			state->ring[i].data_size, &state->ring[i].encoded);
	पूर्ण

	अगर (state->bos) अणु
		drm_माला_दो(p, "bos:\n");

		क्रम (i = 0; i < state->nr_bos; i++) अणु
			drm_म_लिखो(p, "  - iova: 0x%016llx\n",
				state->bos[i].iova);
			drm_म_लिखो(p, "    size: %zd\n", state->bos[i].size);

			adreno_show_object(p, &state->bos[i].data,
				state->bos[i].size, &state->bos[i].encoded);
		पूर्ण
	पूर्ण

	अगर (state->nr_रेजिस्टरs) अणु
		drm_माला_दो(p, "registers:\n");

		क्रम (i = 0; i < state->nr_रेजिस्टरs; i++) अणु
			drm_म_लिखो(p, "  - { offset: 0x%04x, value: 0x%08x }\n",
				state->रेजिस्टरs[i * 2] << 2,
				state->रेजिस्टरs[(i * 2) + 1]);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* Dump common gpu status and scratch रेजिस्टरs on any hang, to make
 * the hangcheck logs more useful.  The scratch रेजिस्टरs seem always
 * safe to पढ़ो when GPU has hung (unlike some other regs, depending
 * on how the GPU hung), and they are useful to match up to cmdstream
 * dumps when debugging hangs:
 */
व्योम adreno_dump_info(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक i;

	prपूर्णांकk("revision: %d (%d.%d.%d.%d)\n",
			adreno_gpu->info->revn, adreno_gpu->rev.core,
			adreno_gpu->rev.major, adreno_gpu->rev.minor,
			adreno_gpu->rev.patchid);

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		काष्ठा msm_ringbuffer *ring = gpu->rb[i];

		prपूर्णांकk("rb %d: fence:    %d/%d\n", i,
			ring->memptrs->fence,
			ring->seqno);

		prपूर्णांकk("rptr:     %d\n", get_rptr(adreno_gpu, ring));
		prपूर्णांकk("rb wptr:  %d\n", get_wptr(ring));
	पूर्ण
पूर्ण

/* would be nice to not have to duplicate the _show() stuff with prपूर्णांकk(): */
व्योम adreno_dump(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक i;

	अगर (!adreno_gpu->रेजिस्टरs)
		वापस;

	/* dump these out in a क्रमm that can be parsed by demsm: */
	prपूर्णांकk("IO:region %s 00000000 00020000\n", gpu->name);
	क्रम (i = 0; adreno_gpu->रेजिस्टरs[i] != ~0; i += 2) अणु
		uपूर्णांक32_t start = adreno_gpu->रेजिस्टरs[i];
		uपूर्णांक32_t end   = adreno_gpu->रेजिस्टरs[i+1];
		uपूर्णांक32_t addr;

		क्रम (addr = start; addr <= end; addr++) अणु
			uपूर्णांक32_t val = gpu_पढ़ो(gpu, addr);
			prपूर्णांकk("IO:R %08x %08x\n", addr<<2, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t ring_मुक्तwords(काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(ring->gpu);
	uपूर्णांक32_t size = MSM_GPU_RINGBUFFER_SZ >> 2;
	/* Use ring->next to calculate मुक्त size */
	uपूर्णांक32_t wptr = ring->next - ring->start;
	uपूर्णांक32_t rptr = get_rptr(adreno_gpu, ring);
	वापस (rptr + (size - 1) - wptr) % size;
पूर्ण

व्योम adreno_रुको_ring(काष्ठा msm_ringbuffer *ring, uपूर्णांक32_t ndwords)
अणु
	अगर (spin_until(ring_मुक्तwords(ring) >= ndwords))
		DRM_DEV_ERROR(ring->gpu->dev->dev,
			"timeout waiting for space in ringbuffer %d\n",
			ring->id);
पूर्ण

/* Get legacy घातerlevels from qcom,gpu-pwrlevels and populate the opp table */
अटल पूर्णांक adreno_get_legacy_pwrlevels(काष्ठा device *dev)
अणु
	काष्ठा device_node *child, *node;
	पूर्णांक ret;

	node = of_get_compatible_child(dev->of_node, "qcom,gpu-pwrlevels");
	अगर (!node) अणु
		DRM_DEV_DEBUG(dev, "Could not find the GPU powerlevels\n");
		वापस -ENXIO;
	पूर्ण

	क्रम_each_child_of_node(node, child) अणु
		अचिन्हित पूर्णांक val;

		ret = of_property_पढ़ो_u32(child, "qcom,gpu-freq", &val);
		अगर (ret)
			जारी;

		/*
		 * Skip the पूर्णांकentionally bogus घड़ी value found at the bottom
		 * of most legacy frequency tables
		 */
		अगर (val != 27000000)
			dev_pm_opp_add(dev, val, 0);
	पूर्ण

	of_node_put(node);

	वापस 0;
पूर्ण

अटल व्योम adreno_get_pwrlevels(काष्ठा device *dev,
		काष्ठा msm_gpu *gpu)
अणु
	अचिन्हित दीर्घ freq = अच_दीर्घ_उच्च;
	काष्ठा dev_pm_opp *opp;
	पूर्णांक ret;

	gpu->fast_rate = 0;

	/* You करोwn with OPP? */
	अगर (!of_find_property(dev->of_node, "operating-points-v2", शून्य))
		ret = adreno_get_legacy_pwrlevels(dev);
	अन्यथा अणु
		ret = dev_pm_opp_of_add_table(dev);
		अगर (ret)
			DRM_DEV_ERROR(dev, "Unable to set the OPP table\n");
	पूर्ण

	अगर (!ret) अणु
		/* Find the fastest defined rate */
		opp = dev_pm_opp_find_freq_न्यूनमान(dev, &freq);
		अगर (!IS_ERR(opp)) अणु
			gpu->fast_rate = freq;
			dev_pm_opp_put(opp);
		पूर्ण
	पूर्ण

	अगर (!gpu->fast_rate) अणु
		dev_warn(dev,
			"Could not find a clock rate. Using a reasonable default\n");
		/* Pick a suitably safe घड़ी speed क्रम any target */
		gpu->fast_rate = 200000000;
	पूर्ण

	DBG("fast_rate=%u, slow_rate=27000000", gpu->fast_rate);
पूर्ण

पूर्णांक adreno_gpu_ocmem_init(काष्ठा device *dev, काष्ठा adreno_gpu *adreno_gpu,
			  काष्ठा adreno_ocmem *adreno_ocmem)
अणु
	काष्ठा ocmem_buf *ocmem_hdl;
	काष्ठा ocmem *ocmem;

	ocmem = of_get_ocmem(dev);
	अगर (IS_ERR(ocmem)) अणु
		अगर (PTR_ERR(ocmem) == -ENODEV) अणु
			/*
			 * Return success since either the ocmem property was
			 * not specअगरied in device tree, or ocmem support is
			 * not compiled पूर्णांकo the kernel.
			 */
			वापस 0;
		पूर्ण

		वापस PTR_ERR(ocmem);
	पूर्ण

	ocmem_hdl = ocmem_allocate(ocmem, OCMEM_GRAPHICS, adreno_gpu->gmem);
	अगर (IS_ERR(ocmem_hdl))
		वापस PTR_ERR(ocmem_hdl);

	adreno_ocmem->ocmem = ocmem;
	adreno_ocmem->base = ocmem_hdl->addr;
	adreno_ocmem->hdl = ocmem_hdl;
	adreno_gpu->gmem = ocmem_hdl->len;

	वापस 0;
पूर्ण

व्योम adreno_gpu_ocmem_cleanup(काष्ठा adreno_ocmem *adreno_ocmem)
अणु
	अगर (adreno_ocmem && adreno_ocmem->base)
		ocmem_मुक्त(adreno_ocmem->ocmem, OCMEM_GRAPHICS,
			   adreno_ocmem->hdl);
पूर्ण

पूर्णांक adreno_gpu_init(काष्ठा drm_device *drm, काष्ठा platक्रमm_device *pdev,
		काष्ठा adreno_gpu *adreno_gpu,
		स्थिर काष्ठा adreno_gpu_funcs *funcs, पूर्णांक nr_rings)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा adreno_platक्रमm_config *config = dev->platक्रमm_data;
	काष्ठा msm_gpu_config adreno_gpu_config  = अणु 0 पूर्ण;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;

	adreno_gpu->funcs = funcs;
	adreno_gpu->info = adreno_info(config->rev);
	adreno_gpu->gmem = adreno_gpu->info->gmem;
	adreno_gpu->revn = adreno_gpu->info->revn;
	adreno_gpu->rev = config->rev;

	adreno_gpu_config.ioname = "kgsl_3d0_reg_memory";

	adreno_gpu_config.nr_rings = nr_rings;

	adreno_get_pwrlevels(dev, gpu);

	pm_runसमय_set_स्वतःsuspend_delay(dev,
		adreno_gpu->info->inactive_period);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	वापस msm_gpu_init(drm, pdev, &adreno_gpu->base, &funcs->base,
			adreno_gpu->info->name, &adreno_gpu_config);
पूर्ण

व्योम adreno_gpu_cleanup(काष्ठा adreno_gpu *adreno_gpu)
अणु
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;
	काष्ठा msm_drm_निजी *priv = gpu->dev->dev_निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adreno_gpu->info->fw); i++)
		release_firmware(adreno_gpu->fw[i]);

	pm_runसमय_disable(&priv->gpu_pdev->dev);

	msm_gpu_cleanup(&adreno_gpu->base);

	icc_put(gpu->icc_path);
	icc_put(gpu->ocmem_icc_path);
पूर्ण
