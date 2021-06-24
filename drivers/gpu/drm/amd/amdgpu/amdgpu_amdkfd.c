<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

#समावेश "amdgpu_amdkfd.h"
#समावेश "amd_shared.h"

#समावेश "amdgpu.h"
#समावेश "amdgpu_gfx.h"
#समावेश "amdgpu_dma_buf.h"
#समावेश <linux/module.h>
#समावेश <linux/dma-buf.h>
#समावेश "amdgpu_xgmi.h"
#समावेश <uapi/linux/kfd_ioctl.h>

/* Total memory size in प्रणाली memory and all GPU VRAM. Used to
 * estimate worst हाल amount of memory to reserve क्रम page tables
 */
uपूर्णांक64_t amdgpu_amdkfd_total_mem_size;

अटल bool kfd_initialized;

पूर्णांक amdgpu_amdkfd_init(व्योम)
अणु
	काष्ठा sysinfo si;
	पूर्णांक ret;

	si_meminfo(&si);
	amdgpu_amdkfd_total_mem_size = si.मुक्तram - si.मुक्तhigh;
	amdgpu_amdkfd_total_mem_size *= si.mem_unit;

	ret = kgd2kfd_init();
	amdgpu_amdkfd_gpuvm_init_mem_limits();
	kfd_initialized = !ret;

	वापस ret;
पूर्ण

व्योम amdgpu_amdkfd_fini(व्योम)
अणु
	अगर (kfd_initialized) अणु
		kgd2kfd_निकास();
		kfd_initialized = false;
	पूर्ण
पूर्ण

व्योम amdgpu_amdkfd_device_probe(काष्ठा amdgpu_device *adev)
अणु
	bool vf = amdgpu_sriov_vf(adev);

	अगर (!kfd_initialized)
		वापस;

	adev->kfd.dev = kgd2kfd_probe((काष्ठा kgd_dev *)adev,
				      adev->pdev, adev->asic_type, vf);

	अगर (adev->kfd.dev)
		amdgpu_amdkfd_total_mem_size += adev->gmc.real_vram_size;
पूर्ण

/**
 * amdgpu_करोorbell_get_kfd_info - Report करोorbell configuration required to
 *                                setup amdkfd
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @aperture_base: output वापसing करोorbell aperture base physical address
 * @aperture_size: output वापसing करोorbell aperture size in bytes
 * @start_offset: output वापसing # of करोorbell bytes reserved क्रम amdgpu.
 *
 * amdgpu and amdkfd share the करोorbell aperture. amdgpu sets it up,
 * takes करोorbells required क्रम its own rings and reports the setup to amdkfd.
 * amdgpu reserved करोorbells are at the start of the करोorbell aperture.
 */
अटल व्योम amdgpu_करोorbell_get_kfd_info(काष्ठा amdgpu_device *adev,
					 phys_addr_t *aperture_base,
					 माप_प्रकार *aperture_size,
					 माप_प्रकार *start_offset)
अणु
	/*
	 * The first num_करोorbells are used by amdgpu.
	 * amdkfd takes whatever's left in the aperture.
	 */
	अगर (adev->करोorbell.size > adev->करोorbell.num_करोorbells * माप(u32)) अणु
		*aperture_base = adev->करोorbell.base;
		*aperture_size = adev->करोorbell.size;
		*start_offset = adev->करोorbell.num_करोorbells * माप(u32);
	पूर्ण अन्यथा अणु
		*aperture_base = 0;
		*aperture_size = 0;
		*start_offset = 0;
	पूर्ण
पूर्ण

व्योम amdgpu_amdkfd_device_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	पूर्णांक last_valid_bit;

	अगर (adev->kfd.dev) अणु
		काष्ठा kgd2kfd_shared_resources gpu_resources = अणु
			.compute_vmid_biपंचांगap =
				((1 << AMDGPU_NUM_VMID) - 1) -
				((1 << adev->vm_manager.first_kfd_vmid) - 1),
			.num_pipe_per_mec = adev->gfx.mec.num_pipe_per_mec,
			.num_queue_per_pipe = adev->gfx.mec.num_queue_per_pipe,
			.gpuvm_size = min(adev->vm_manager.max_pfn
					  << AMDGPU_GPU_PAGE_SHIFT,
					  AMDGPU_GMC_HOLE_START),
			.drm_render_minor = adev_to_drm(adev)->render->index,
			.sdma_करोorbell_idx = adev->करोorbell_index.sdma_engine,

		पूर्ण;

		/* this is going to have a few of the MSBs set that we need to
		 * clear
		 */
		biपंचांगap_complement(gpu_resources.cp_queue_biपंचांगap,
				  adev->gfx.mec.queue_biपंचांगap,
				  KGD_MAX_QUEUES);

		/* According to linux/biपंचांगap.h we shouldn't use biपंचांगap_clear अगर
		 * nbits is not compile समय स्थिरant
		 */
		last_valid_bit = 1 /* only first MEC can have compute queues */
				* adev->gfx.mec.num_pipe_per_mec
				* adev->gfx.mec.num_queue_per_pipe;
		क्रम (i = last_valid_bit; i < KGD_MAX_QUEUES; ++i)
			clear_bit(i, gpu_resources.cp_queue_biपंचांगap);

		amdgpu_करोorbell_get_kfd_info(adev,
				&gpu_resources.करोorbell_physical_address,
				&gpu_resources.करोorbell_aperture_size,
				&gpu_resources.करोorbell_start_offset);

		/* Since SOC15, BIF starts to अटलally use the
		 * lower 12 bits of करोorbell addresses क्रम routing
		 * based on settings in रेजिस्टरs like
		 * SDMA0_DOORBELL_RANGE etc..
		 * In order to route a करोorbell to CP engine, the lower
		 * 12 bits of its address has to be outside the range
		 * set क्रम SDMA, VCN, and IH blocks.
		 */
		अगर (adev->asic_type >= CHIP_VEGA10) अणु
			gpu_resources.non_cp_करोorbells_start =
					adev->करोorbell_index.first_non_cp;
			gpu_resources.non_cp_करोorbells_end =
					adev->करोorbell_index.last_non_cp;
		पूर्ण

		adev->kfd.init_complete = kgd2kfd_device_init(adev->kfd.dev,
						adev_to_drm(adev), &gpu_resources);
	पूर्ण
पूर्ण

व्योम amdgpu_amdkfd_device_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->kfd.dev) अणु
		kgd2kfd_device_निकास(adev->kfd.dev);
		adev->kfd.dev = शून्य;
	पूर्ण
पूर्ण

व्योम amdgpu_amdkfd_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
		स्थिर व्योम *ih_ring_entry)
अणु
	अगर (adev->kfd.dev)
		kgd2kfd_पूर्णांकerrupt(adev->kfd.dev, ih_ring_entry);
पूर्ण

व्योम amdgpu_amdkfd_suspend(काष्ठा amdgpu_device *adev, bool run_pm)
अणु
	अगर (adev->kfd.dev)
		kgd2kfd_suspend(adev->kfd.dev, run_pm);
पूर्ण

पूर्णांक amdgpu_amdkfd_resume(काष्ठा amdgpu_device *adev, bool run_pm)
अणु
	पूर्णांक r = 0;

	अगर (adev->kfd.dev)
		r = kgd2kfd_resume(adev->kfd.dev, run_pm);

	वापस r;
पूर्ण

पूर्णांक amdgpu_amdkfd_pre_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r = 0;

	अगर (adev->kfd.dev)
		r = kgd2kfd_pre_reset(adev->kfd.dev);

	वापस r;
पूर्ण

पूर्णांक amdgpu_amdkfd_post_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r = 0;

	अगर (adev->kfd.dev)
		r = kgd2kfd_post_reset(adev->kfd.dev);

	वापस r;
पूर्ण

व्योम amdgpu_amdkfd_gpu_reset(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	अगर (amdgpu_device_should_recover_gpu(adev))
		amdgpu_device_gpu_recover(adev, शून्य);
पूर्ण

पूर्णांक amdgpu_amdkfd_alloc_gtt_mem(काष्ठा kgd_dev *kgd, माप_प्रकार size,
				व्योम **mem_obj, uपूर्णांक64_t *gpu_addr,
				व्योम **cpu_ptr, bool cp_mqd_gfx9)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	काष्ठा amdgpu_bo *bo = शून्य;
	काष्ठा amdgpu_bo_param bp;
	पूर्णांक r;
	व्योम *cpu_ptr_पंचांगp = शून्य;

	स_रखो(&bp, 0, माप(bp));
	bp.size = size;
	bp.byte_align = PAGE_SIZE;
	bp.करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;
	bp.flags = AMDGPU_GEM_CREATE_CPU_GTT_USWC;
	bp.type = tपंचांग_bo_type_kernel;
	bp.resv = शून्य;
	bp.bo_ptr_size = माप(काष्ठा amdgpu_bo);

	अगर (cp_mqd_gfx9)
		bp.flags |= AMDGPU_GEM_CREATE_CP_MQD_GFX9;

	r = amdgpu_bo_create(adev, &bp, &bo);
	अगर (r) अणु
		dev_err(adev->dev,
			"failed to allocate BO for amdkfd (%d)\n", r);
		वापस r;
	पूर्ण

	/* map the buffer */
	r = amdgpu_bo_reserve(bo, true);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to reserve bo for amdkfd\n", r);
		जाओ allocate_mem_reserve_bo_failed;
	पूर्ण

	r = amdgpu_bo_pin(bo, AMDGPU_GEM_DOMAIN_GTT);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to pin bo for amdkfd\n", r);
		जाओ allocate_mem_pin_bo_failed;
	पूर्ण

	r = amdgpu_tपंचांग_alloc_gart(&bo->tbo);
	अगर (r) अणु
		dev_err(adev->dev, "%p bind failed\n", bo);
		जाओ allocate_mem_kmap_bo_failed;
	पूर्ण

	r = amdgpu_bo_kmap(bo, &cpu_ptr_पंचांगp);
	अगर (r) अणु
		dev_err(adev->dev,
			"(%d) failed to map bo to kernel for amdkfd\n", r);
		जाओ allocate_mem_kmap_bo_failed;
	पूर्ण

	*mem_obj = bo;
	*gpu_addr = amdgpu_bo_gpu_offset(bo);
	*cpu_ptr = cpu_ptr_पंचांगp;

	amdgpu_bo_unreserve(bo);

	वापस 0;

allocate_mem_kmap_bo_failed:
	amdgpu_bo_unpin(bo);
allocate_mem_pin_bo_failed:
	amdgpu_bo_unreserve(bo);
allocate_mem_reserve_bo_failed:
	amdgpu_bo_unref(&bo);

	वापस r;
पूर्ण

व्योम amdgpu_amdkfd_मुक्त_gtt_mem(काष्ठा kgd_dev *kgd, व्योम *mem_obj)
अणु
	काष्ठा amdgpu_bo *bo = (काष्ठा amdgpu_bo *) mem_obj;

	amdgpu_bo_reserve(bo, true);
	amdgpu_bo_kunmap(bo);
	amdgpu_bo_unpin(bo);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&(bo));
पूर्ण

पूर्णांक amdgpu_amdkfd_alloc_gws(काष्ठा kgd_dev *kgd, माप_प्रकार size,
				व्योम **mem_obj)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	काष्ठा amdgpu_bo *bo = शून्य;
	काष्ठा amdgpu_bo_user *ubo;
	काष्ठा amdgpu_bo_param bp;
	पूर्णांक r;

	स_रखो(&bp, 0, माप(bp));
	bp.size = size;
	bp.byte_align = 1;
	bp.करोमुख्य = AMDGPU_GEM_DOMAIN_GWS;
	bp.flags = AMDGPU_GEM_CREATE_NO_CPU_ACCESS;
	bp.type = tपंचांग_bo_type_device;
	bp.resv = शून्य;
	bp.bo_ptr_size = माप(काष्ठा amdgpu_bo);

	r = amdgpu_bo_create_user(adev, &bp, &ubo);
	अगर (r) अणु
		dev_err(adev->dev,
			"failed to allocate gws BO for amdkfd (%d)\n", r);
		वापस r;
	पूर्ण

	bo = &ubo->bo;
	*mem_obj = bo;
	वापस 0;
पूर्ण

व्योम amdgpu_amdkfd_मुक्त_gws(काष्ठा kgd_dev *kgd, व्योम *mem_obj)
अणु
	काष्ठा amdgpu_bo *bo = (काष्ठा amdgpu_bo *)mem_obj;

	amdgpu_bo_unref(&bo);
पूर्ण

uपूर्णांक32_t amdgpu_amdkfd_get_fw_version(काष्ठा kgd_dev *kgd,
				      क्रमागत kgd_engine_type type)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	चयन (type) अणु
	हाल KGD_ENGINE_PFP:
		वापस adev->gfx.pfp_fw_version;

	हाल KGD_ENGINE_ME:
		वापस adev->gfx.me_fw_version;

	हाल KGD_ENGINE_CE:
		वापस adev->gfx.ce_fw_version;

	हाल KGD_ENGINE_MEC1:
		वापस adev->gfx.mec_fw_version;

	हाल KGD_ENGINE_MEC2:
		वापस adev->gfx.mec2_fw_version;

	हाल KGD_ENGINE_RLC:
		वापस adev->gfx.rlc_fw_version;

	हाल KGD_ENGINE_SDMA1:
		वापस adev->sdma.instance[0].fw_version;

	हाल KGD_ENGINE_SDMA2:
		वापस adev->sdma.instance[1].fw_version;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

व्योम amdgpu_amdkfd_get_local_mem_info(काष्ठा kgd_dev *kgd,
				      काष्ठा kfd_local_mem_info *mem_info)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	स_रखो(mem_info, 0, माप(*mem_info));

	mem_info->local_mem_size_खुला = adev->gmc.visible_vram_size;
	mem_info->local_mem_size_निजी = adev->gmc.real_vram_size -
						adev->gmc.visible_vram_size;

	mem_info->vram_width = adev->gmc.vram_width;

	pr_debug("Address base: %pap public 0x%llx private 0x%llx\n",
			&adev->gmc.aper_base,
			mem_info->local_mem_size_खुला,
			mem_info->local_mem_size_निजी);

	अगर (amdgpu_sriov_vf(adev))
		mem_info->mem_clk_max = adev->घड़ी.शेष_mclk / 100;
	अन्यथा अगर (adev->pm.dpm_enabled) अणु
		अगर (amdgpu_emu_mode == 1)
			mem_info->mem_clk_max = 0;
		अन्यथा
			mem_info->mem_clk_max = amdgpu_dpm_get_mclk(adev, false) / 100;
	पूर्ण अन्यथा
		mem_info->mem_clk_max = 100;
पूर्ण

uपूर्णांक64_t amdgpu_amdkfd_get_gpu_घड़ी_counter(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	अगर (adev->gfx.funcs->get_gpu_घड़ी_counter)
		वापस adev->gfx.funcs->get_gpu_घड़ी_counter(adev);
	वापस 0;
पूर्ण

uपूर्णांक32_t amdgpu_amdkfd_get_max_engine_घड़ी_in_mhz(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	/* the sclk is in quantas of 10kHz */
	अगर (amdgpu_sriov_vf(adev))
		वापस adev->घड़ी.शेष_sclk / 100;
	अन्यथा अगर (adev->pm.dpm_enabled)
		वापस amdgpu_dpm_get_sclk(adev, false) / 100;
	अन्यथा
		वापस 100;
पूर्ण

व्योम amdgpu_amdkfd_get_cu_info(काष्ठा kgd_dev *kgd, काष्ठा kfd_cu_info *cu_info)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	काष्ठा amdgpu_cu_info acu_info = adev->gfx.cu_info;

	स_रखो(cu_info, 0, माप(*cu_info));
	अगर (माप(cu_info->cu_biपंचांगap) != माप(acu_info.biपंचांगap))
		वापस;

	cu_info->cu_active_number = acu_info.number;
	cu_info->cu_ao_mask = acu_info.ao_cu_mask;
	स_नकल(&cu_info->cu_biपंचांगap[0], &acu_info.biपंचांगap[0],
	       माप(acu_info.biपंचांगap));
	cu_info->num_shader_engines = adev->gfx.config.max_shader_engines;
	cu_info->num_shader_arrays_per_engine = adev->gfx.config.max_sh_per_se;
	cu_info->num_cu_per_sh = adev->gfx.config.max_cu_per_sh;
	cu_info->simd_per_cu = acu_info.simd_per_cu;
	cu_info->max_waves_per_simd = acu_info.max_waves_per_simd;
	cu_info->wave_front_size = acu_info.wave_front_size;
	cu_info->max_scratch_slots_per_cu = acu_info.max_scratch_slots_per_cu;
	cu_info->lds_size = acu_info.lds_size;
पूर्ण

पूर्णांक amdgpu_amdkfd_get_dmabuf_info(काष्ठा kgd_dev *kgd, पूर्णांक dma_buf_fd,
				  काष्ठा kgd_dev **dma_buf_kgd,
				  uपूर्णांक64_t *bo_size, व्योम *metadata_buffer,
				  माप_प्रकार buffer_size, uपूर्णांक32_t *metadata_size,
				  uपूर्णांक32_t *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	काष्ठा dma_buf *dma_buf;
	काष्ठा drm_gem_object *obj;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक64_t metadata_flags;
	पूर्णांक r = -EINVAL;

	dma_buf = dma_buf_get(dma_buf_fd);
	अगर (IS_ERR(dma_buf))
		वापस PTR_ERR(dma_buf);

	अगर (dma_buf->ops != &amdgpu_dmabuf_ops)
		/* Can't handle non-graphics buffers */
		जाओ out_put;

	obj = dma_buf->priv;
	अगर (obj->dev->driver != adev_to_drm(adev)->driver)
		/* Can't handle buffers from dअगरferent drivers */
		जाओ out_put;

	adev = drm_to_adev(obj->dev);
	bo = gem_to_amdgpu_bo(obj);
	अगर (!(bo->preferred_करोमुख्यs & (AMDGPU_GEM_DOMAIN_VRAM |
				    AMDGPU_GEM_DOMAIN_GTT)))
		/* Only VRAM and GTT BOs are supported */
		जाओ out_put;

	r = 0;
	अगर (dma_buf_kgd)
		*dma_buf_kgd = (काष्ठा kgd_dev *)adev;
	अगर (bo_size)
		*bo_size = amdgpu_bo_size(bo);
	अगर (metadata_buffer)
		r = amdgpu_bo_get_metadata(bo, metadata_buffer, buffer_size,
					   metadata_size, &metadata_flags);
	अगर (flags) अणु
		*flags = (bo->preferred_करोमुख्यs & AMDGPU_GEM_DOMAIN_VRAM) ?
				KFD_IOC_ALLOC_MEM_FLAGS_VRAM
				: KFD_IOC_ALLOC_MEM_FLAGS_GTT;

		अगर (bo->flags & AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED)
			*flags |= KFD_IOC_ALLOC_MEM_FLAGS_PUBLIC;
	पूर्ण

out_put:
	dma_buf_put(dma_buf);
	वापस r;
पूर्ण

uपूर्णांक64_t amdgpu_amdkfd_get_vram_usage(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	काष्ठा tपंचांग_resource_manager *vram_man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);

	वापस amdgpu_vram_mgr_usage(vram_man);
पूर्ण

uपूर्णांक64_t amdgpu_amdkfd_get_hive_id(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	वापस adev->gmc.xgmi.hive_id;
पूर्ण

uपूर्णांक64_t amdgpu_amdkfd_get_unique_id(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	वापस adev->unique_id;
पूर्ण

uपूर्णांक8_t amdgpu_amdkfd_get_xgmi_hops_count(काष्ठा kgd_dev *dst, काष्ठा kgd_dev *src)
अणु
	काष्ठा amdgpu_device *peer_adev = (काष्ठा amdgpu_device *)src;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)dst;
	पूर्णांक ret = amdgpu_xgmi_get_hops_count(adev, peer_adev);

	अगर (ret < 0) अणु
		DRM_ERROR("amdgpu: failed to get  xgmi hops count between node %d and %d. ret = %d\n",
			adev->gmc.xgmi.physical_node_id,
			peer_adev->gmc.xgmi.physical_node_id, ret);
		ret = 0;
	पूर्ण
	वापस  (uपूर्णांक8_t)ret;
पूर्ण

uपूर्णांक64_t amdgpu_amdkfd_get_mmio_remap_phys_addr(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	वापस adev->rmmio_remap.bus_addr;
पूर्ण

uपूर्णांक32_t amdgpu_amdkfd_get_num_gws(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	वापस adev->gds.gws_size;
पूर्ण

uपूर्णांक32_t amdgpu_amdkfd_get_asic_rev_id(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	वापस adev->rev_id;
पूर्ण

पूर्णांक amdgpu_amdkfd_get_noretry(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	वापस adev->gmc.noretry;
पूर्ण

पूर्णांक amdgpu_amdkfd_submit_ib(काष्ठा kgd_dev *kgd, क्रमागत kgd_engine_type engine,
				uपूर्णांक32_t vmid, uपूर्णांक64_t gpu_addr,
				uपूर्णांक32_t *ib_cmd, uपूर्णांक32_t ib_len)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	काष्ठा amdgpu_ring *ring;
	काष्ठा dma_fence *f = शून्य;
	पूर्णांक ret;

	चयन (engine) अणु
	हाल KGD_ENGINE_MEC1:
		ring = &adev->gfx.compute_ring[0];
		अवरोध;
	हाल KGD_ENGINE_SDMA1:
		ring = &adev->sdma.instance[0].ring;
		अवरोध;
	हाल KGD_ENGINE_SDMA2:
		ring = &adev->sdma.instance[1].ring;
		अवरोध;
	शेष:
		pr_err("Invalid engine in IB submission: %d\n", engine);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = amdgpu_job_alloc(adev, 1, &job, शून्य);
	अगर (ret)
		जाओ err;

	ib = &job->ibs[0];
	स_रखो(ib, 0, माप(काष्ठा amdgpu_ib));

	ib->gpu_addr = gpu_addr;
	ib->ptr = ib_cmd;
	ib->length_dw = ib_len;
	/* This works क्रम NO_HWS. TODO: need to handle without knowing VMID */
	job->vmid = vmid;

	ret = amdgpu_ib_schedule(ring, 1, ib, job, &f);

	अगर (ret) अणु
		DRM_ERROR("amdgpu: failed to schedule IB.\n");
		जाओ err_ib_sched;
	पूर्ण

	ret = dma_fence_रुको(f, false);

err_ib_sched:
	dma_fence_put(f);
	amdgpu_job_मुक्त(job);
err:
	वापस ret;
पूर्ण

व्योम amdgpu_amdkfd_set_compute_idle(काष्ठा kgd_dev *kgd, bool idle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	amdgpu_dpm_चयन_घातer_profile(adev,
					PP_SMC_POWER_PROखाता_COMPUTE,
					!idle);
पूर्ण

bool amdgpu_amdkfd_is_kfd_vmid(काष्ठा amdgpu_device *adev, u32 vmid)
अणु
	अगर (adev->kfd.dev)
		वापस vmid >= adev->vm_manager.first_kfd_vmid;

	वापस false;
पूर्ण

पूर्णांक amdgpu_amdkfd_flush_gpu_tlb_vmid(काष्ठा kgd_dev *kgd, uपूर्णांक16_t vmid)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	अगर (adev->family == AMDGPU_FAMILY_AI) अणु
		पूर्णांक i;

		क्रम (i = 0; i < adev->num_vmhubs; i++)
			amdgpu_gmc_flush_gpu_tlb(adev, vmid, i, 0);
	पूर्ण अन्यथा अणु
		amdgpu_gmc_flush_gpu_tlb(adev, vmid, AMDGPU_GFXHUB_0, 0);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_amdkfd_flush_gpu_tlb_pasid(काष्ठा kgd_dev *kgd, uपूर्णांक16_t pasid)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;
	स्थिर uपूर्णांक32_t flush_type = 0;
	bool all_hub = false;

	अगर (adev->family == AMDGPU_FAMILY_AI)
		all_hub = true;

	वापस amdgpu_gmc_flush_gpu_tlb_pasid(adev, pasid, flush_type, all_hub);
पूर्ण

bool amdgpu_amdkfd_have_atomics_support(काष्ठा kgd_dev *kgd)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)kgd;

	वापस adev->have_atomics_support;
पूर्ण
