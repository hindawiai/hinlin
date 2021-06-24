<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#समावेश <linux/module.h>

#समावेश <drm/drm_drv.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ras.h"
#समावेश "vi.h"
#समावेश "soc15.h"
#समावेश "nv.h"

#घोषणा POPULATE_UCODE_INFO(vf2pf_info, ucode, ver) \
	करो अणु \
		vf2pf_info->ucode_info[ucode].id = ucode; \
		vf2pf_info->ucode_info[ucode].version = ver; \
	पूर्ण जबतक (0)

bool amdgpu_virt_mmio_blocked(काष्ठा amdgpu_device *adev)
अणु
	/* By now all MMIO pages except mailbox are blocked */
	/* अगर blocking is enabled in hypervisor. Choose the */
	/* SCRATCH_REG0 to test. */
	वापस RREG32_NO_KIQ(0xc040) == 0xffffffff;
पूर्ण

व्योम amdgpu_virt_init_setting(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *ddev = adev_to_drm(adev);

	/* enable भव display */
	अगर (adev->mode_info.num_crtc == 0)
		adev->mode_info.num_crtc = 1;
	adev->enable_भव_display = true;
	ddev->driver_features &= ~DRIVER_ATOMIC;
	adev->cg_flags = 0;
	adev->pg_flags = 0;
पूर्ण

व्योम amdgpu_virt_kiq_reg_ग_लिखो_reg_रुको(काष्ठा amdgpu_device *adev,
					uपूर्णांक32_t reg0, uपूर्णांक32_t reg1,
					uपूर्णांक32_t ref, uपूर्णांक32_t mask)
अणु
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;
	काष्ठा amdgpu_ring *ring = &kiq->ring;
	चिन्हित दीर्घ r, cnt = 0;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t seq;

	spin_lock_irqsave(&kiq->ring_lock, flags);
	amdgpu_ring_alloc(ring, 32);
	amdgpu_ring_emit_reg_ग_लिखो_reg_रुको(ring, reg0, reg1,
					    ref, mask);
	r = amdgpu_fence_emit_polling(ring, &seq, MAX_KIQ_REG_WAIT);
	अगर (r)
		जाओ failed_unकरो;

	amdgpu_ring_commit(ring);
	spin_unlock_irqrestore(&kiq->ring_lock, flags);

	r = amdgpu_fence_रुको_polling(ring, seq, MAX_KIQ_REG_WAIT);

	/* करोn't रुको anymore क्रम IRQ context */
	अगर (r < 1 && in_पूर्णांकerrupt())
		जाओ failed_kiq;

	might_sleep();
	जबतक (r < 1 && cnt++ < MAX_KIQ_REG_TRY) अणु

		msleep(MAX_KIQ_REG_BAILOUT_INTERVAL);
		r = amdgpu_fence_रुको_polling(ring, seq, MAX_KIQ_REG_WAIT);
	पूर्ण

	अगर (cnt > MAX_KIQ_REG_TRY)
		जाओ failed_kiq;

	वापस;

failed_unकरो:
	amdgpu_ring_unकरो(ring);
	spin_unlock_irqrestore(&kiq->ring_lock, flags);
failed_kiq:
	dev_err(adev->dev, "failed to write reg %x wait reg %x\n", reg0, reg1);
पूर्ण

/**
 * amdgpu_virt_request_full_gpu() - request full gpu access
 * @adev:	amdgpu device.
 * @init:	is driver init समय.
 * When start to init/fini driver, first need to request full gpu access.
 * Return: Zero अगर request success, otherwise will वापस error.
 */
पूर्णांक amdgpu_virt_request_full_gpu(काष्ठा amdgpu_device *adev, bool init)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	पूर्णांक r;

	अगर (virt->ops && virt->ops->req_full_gpu) अणु
		r = virt->ops->req_full_gpu(adev, init);
		अगर (r)
			वापस r;

		adev->virt.caps &= ~AMDGPU_SRIOV_CAPS_RUNTIME;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_virt_release_full_gpu() - release full gpu access
 * @adev:	amdgpu device.
 * @init:	is driver init समय.
 * When finishing driver init/fini, need to release full gpu access.
 * Return: Zero अगर release success, otherwise will returen error.
 */
पूर्णांक amdgpu_virt_release_full_gpu(काष्ठा amdgpu_device *adev, bool init)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	पूर्णांक r;

	अगर (virt->ops && virt->ops->rel_full_gpu) अणु
		r = virt->ops->rel_full_gpu(adev, init);
		अगर (r)
			वापस r;

		adev->virt.caps |= AMDGPU_SRIOV_CAPS_RUNTIME;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_virt_reset_gpu() - reset gpu
 * @adev:	amdgpu device.
 * Send reset command to GPU hypervisor to reset GPU that VM is using
 * Return: Zero अगर reset success, otherwise will वापस error.
 */
पूर्णांक amdgpu_virt_reset_gpu(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	पूर्णांक r;

	अगर (virt->ops && virt->ops->reset_gpu) अणु
		r = virt->ops->reset_gpu(adev);
		अगर (r)
			वापस r;

		adev->virt.caps &= ~AMDGPU_SRIOV_CAPS_RUNTIME;
	पूर्ण

	वापस 0;
पूर्ण

व्योम amdgpu_virt_request_init_data(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;

	अगर (virt->ops && virt->ops->req_init_data)
		virt->ops->req_init_data(adev);

	अगर (adev->virt.req_init_data_ver > 0)
		DRM_INFO("host supports REQ_INIT_DATA handshake\n");
	अन्यथा
		DRM_WARN("host doesn't support REQ_INIT_DATA handshake\n");
पूर्ण

/**
 * amdgpu_virt_रुको_reset() - रुको क्रम reset gpu completed
 * @adev:	amdgpu device.
 * Wait क्रम GPU reset completed.
 * Return: Zero अगर reset success, otherwise will वापस error.
 */
पूर्णांक amdgpu_virt_रुको_reset(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;

	अगर (!virt->ops || !virt->ops->रुको_reset)
		वापस -EINVAL;

	वापस virt->ops->रुको_reset(adev);
पूर्ण

/**
 * amdgpu_virt_alloc_mm_table() - alloc memory क्रम mm table
 * @adev:	amdgpu device.
 * MM table is used by UVD and VCE क्रम its initialization
 * Return: Zero अगर allocate success.
 */
पूर्णांक amdgpu_virt_alloc_mm_table(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (!amdgpu_sriov_vf(adev) || adev->virt.mm_table.gpu_addr)
		वापस 0;

	r = amdgpu_bo_create_kernel(adev, PAGE_SIZE, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_VRAM,
				    &adev->virt.mm_table.bo,
				    &adev->virt.mm_table.gpu_addr,
				    (व्योम *)&adev->virt.mm_table.cpu_addr);
	अगर (r) अणु
		DRM_ERROR("failed to alloc mm table and error = %d.\n", r);
		वापस r;
	पूर्ण

	स_रखो((व्योम *)adev->virt.mm_table.cpu_addr, 0, PAGE_SIZE);
	DRM_INFO("MM table gpu addr = 0x%llx, cpu addr = %p.\n",
		 adev->virt.mm_table.gpu_addr,
		 adev->virt.mm_table.cpu_addr);
	वापस 0;
पूर्ण

/**
 * amdgpu_virt_मुक्त_mm_table() - मुक्त mm table memory
 * @adev:	amdgpu device.
 * Free MM table memory
 */
व्योम amdgpu_virt_मुक्त_mm_table(काष्ठा amdgpu_device *adev)
अणु
	अगर (!amdgpu_sriov_vf(adev) || !adev->virt.mm_table.gpu_addr)
		वापस;

	amdgpu_bo_मुक्त_kernel(&adev->virt.mm_table.bo,
			      &adev->virt.mm_table.gpu_addr,
			      (व्योम *)&adev->virt.mm_table.cpu_addr);
	adev->virt.mm_table.gpu_addr = 0;
पूर्ण


अचिन्हित पूर्णांक amd_sriov_msg_checksum(व्योम *obj,
				अचिन्हित दीर्घ obj_size,
				अचिन्हित पूर्णांक key,
				अचिन्हित पूर्णांक checksum)
अणु
	अचिन्हित पूर्णांक ret = key;
	अचिन्हित दीर्घ i = 0;
	अचिन्हित अक्षर *pos;

	pos = (अक्षर *)obj;
	/* calculate checksum */
	क्रम (i = 0; i < obj_size; ++i)
		ret += *(pos + i);
	/* minus the checksum itself */
	pos = (अक्षर *)&checksum;
	क्रम (i = 0; i < माप(checksum); ++i)
		ret -= *(pos + i);
	वापस ret;
पूर्ण

अटल पूर्णांक amdgpu_virt_init_ras_err_handler_data(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	काष्ठा amdgpu_virt_ras_err_handler_data **data = &virt->virt_eh_data;
	/* GPU will be marked bad on host अगर bp count more then 10,
	 * so alloc 512 is enough.
	 */
	अचिन्हित पूर्णांक align_space = 512;
	व्योम *bps = शून्य;
	काष्ठा amdgpu_bo **bps_bo = शून्य;

	*data = kदो_स्मृति(माप(काष्ठा amdgpu_virt_ras_err_handler_data), GFP_KERNEL);
	अगर (!*data)
		वापस -ENOMEM;

	bps = kदो_स्मृति_array(align_space, माप((*data)->bps), GFP_KERNEL);
	bps_bo = kदो_स्मृति_array(align_space, माप((*data)->bps_bo), GFP_KERNEL);

	अगर (!bps || !bps_bo) अणु
		kमुक्त(bps);
		kमुक्त(bps_bo);
		kमुक्त(*data);
		वापस -ENOMEM;
	पूर्ण

	(*data)->bps = bps;
	(*data)->bps_bo = bps_bo;
	(*data)->count = 0;
	(*data)->last_reserved = 0;

	virt->ras_init_करोne = true;

	वापस 0;
पूर्ण

अटल व्योम amdgpu_virt_ras_release_bp(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	काष्ठा amdgpu_virt_ras_err_handler_data *data = virt->virt_eh_data;
	काष्ठा amdgpu_bo *bo;
	पूर्णांक i;

	अगर (!data)
		वापस;

	क्रम (i = data->last_reserved - 1; i >= 0; i--) अणु
		bo = data->bps_bo[i];
		amdgpu_bo_मुक्त_kernel(&bo, शून्य, शून्य);
		data->bps_bo[i] = bo;
		data->last_reserved = i;
	पूर्ण
पूर्ण

व्योम amdgpu_virt_release_ras_err_handler_data(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	काष्ठा amdgpu_virt_ras_err_handler_data *data = virt->virt_eh_data;

	virt->ras_init_करोne = false;

	अगर (!data)
		वापस;

	amdgpu_virt_ras_release_bp(adev);

	kमुक्त(data->bps);
	kमुक्त(data->bps_bo);
	kमुक्त(data);
	virt->virt_eh_data = शून्य;
पूर्ण

अटल व्योम amdgpu_virt_ras_add_bps(काष्ठा amdgpu_device *adev,
		काष्ठा eeprom_table_record *bps, पूर्णांक pages)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	काष्ठा amdgpu_virt_ras_err_handler_data *data = virt->virt_eh_data;

	अगर (!data)
		वापस;

	स_नकल(&data->bps[data->count], bps, pages * माप(*data->bps));
	data->count += pages;
पूर्ण

अटल व्योम amdgpu_virt_ras_reserve_bps(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	काष्ठा amdgpu_virt_ras_err_handler_data *data = virt->virt_eh_data;
	काष्ठा amdgpu_bo *bo = शून्य;
	uपूर्णांक64_t bp;
	पूर्णांक i;

	अगर (!data)
		वापस;

	क्रम (i = data->last_reserved; i < data->count; i++) अणु
		bp = data->bps[i].retired_page;

		/* There are two हालs of reserve error should be ignored:
		 * 1) a ras bad page has been allocated (used by someone);
		 * 2) a ras bad page has been reserved (duplicate error injection
		 *    क्रम one page);
		 */
		अगर (amdgpu_bo_create_kernel_at(adev, bp << AMDGPU_GPU_PAGE_SHIFT,
					       AMDGPU_GPU_PAGE_SIZE,
					       AMDGPU_GEM_DOMAIN_VRAM,
					       &bo, शून्य))
			DRM_DEBUG("RAS WARN: reserve vram for retired page %llx fail\n", bp);

		data->bps_bo[i] = bo;
		data->last_reserved = i + 1;
		bo = शून्य;
	पूर्ण
पूर्ण

अटल bool amdgpu_virt_ras_check_bad_page(काष्ठा amdgpu_device *adev,
		uपूर्णांक64_t retired_page)
अणु
	काष्ठा amdgpu_virt *virt = &adev->virt;
	काष्ठा amdgpu_virt_ras_err_handler_data *data = virt->virt_eh_data;
	पूर्णांक i;

	अगर (!data)
		वापस true;

	क्रम (i = 0; i < data->count; i++)
		अगर (retired_page == data->bps[i].retired_page)
			वापस true;

	वापस false;
पूर्ण

अटल व्योम amdgpu_virt_add_bad_page(काष्ठा amdgpu_device *adev,
		uपूर्णांक64_t bp_block_offset, uपूर्णांक32_t bp_block_size)
अणु
	काष्ठा eeprom_table_record bp;
	uपूर्णांक64_t retired_page;
	uपूर्णांक32_t bp_idx, bp_cnt;

	अगर (bp_block_size) अणु
		bp_cnt = bp_block_size / माप(uपूर्णांक64_t);
		क्रम (bp_idx = 0; bp_idx < bp_cnt; bp_idx++) अणु
			retired_page = *(uपूर्णांक64_t *)(adev->mman.fw_vram_usage_va +
					bp_block_offset + bp_idx * माप(uपूर्णांक64_t));
			bp.retired_page = retired_page;

			अगर (amdgpu_virt_ras_check_bad_page(adev, retired_page))
				जारी;

			amdgpu_virt_ras_add_bps(adev, &bp, 1);

			amdgpu_virt_ras_reserve_bps(adev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_virt_पढ़ो_pf2vf_data(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amd_sriov_msg_pf2vf_info_header *pf2vf_info = adev->virt.fw_reserve.p_pf2vf;
	uपूर्णांक32_t checksum;
	uपूर्णांक32_t checkval;

	अगर (adev->virt.fw_reserve.p_pf2vf == शून्य)
		वापस -EINVAL;

	अगर (pf2vf_info->size > 1024) अणु
		DRM_ERROR("invalid pf2vf message size\n");
		वापस -EINVAL;
	पूर्ण

	चयन (pf2vf_info->version) अणु
	हाल 1:
		checksum = ((काष्ठा amdgim_pf2vf_info_v1 *)pf2vf_info)->checksum;
		checkval = amd_sriov_msg_checksum(
			adev->virt.fw_reserve.p_pf2vf, pf2vf_info->size,
			adev->virt.fw_reserve.checksum_key, checksum);
		अगर (checksum != checkval) अणु
			DRM_ERROR("invalid pf2vf message\n");
			वापस -EINVAL;
		पूर्ण

		adev->virt.gim_feature =
			((काष्ठा amdgim_pf2vf_info_v1 *)pf2vf_info)->feature_flags;
		अवरोध;
	हाल 2:
		/* TODO: missing key, need to add it later */
		checksum = ((काष्ठा amd_sriov_msg_pf2vf_info *)pf2vf_info)->checksum;
		checkval = amd_sriov_msg_checksum(
			adev->virt.fw_reserve.p_pf2vf, pf2vf_info->size,
			0, checksum);
		अगर (checksum != checkval) अणु
			DRM_ERROR("invalid pf2vf message\n");
			वापस -EINVAL;
		पूर्ण

		adev->virt.vf2pf_update_पूर्णांकerval_ms =
			((काष्ठा amd_sriov_msg_pf2vf_info *)pf2vf_info)->vf2pf_update_पूर्णांकerval_ms;
		adev->virt.gim_feature =
			((काष्ठा amd_sriov_msg_pf2vf_info *)pf2vf_info)->feature_flags.all;
		adev->virt.reg_access =
			((काष्ठा amd_sriov_msg_pf2vf_info *)pf2vf_info)->reg_access_flags.all;

		अवरोध;
	शेष:
		DRM_ERROR("invalid pf2vf version\n");
		वापस -EINVAL;
	पूर्ण

	/* correct too large or too little पूर्णांकerval value */
	अगर (adev->virt.vf2pf_update_पूर्णांकerval_ms < 200 || adev->virt.vf2pf_update_पूर्णांकerval_ms > 10000)
		adev->virt.vf2pf_update_पूर्णांकerval_ms = 2000;

	वापस 0;
पूर्ण

अटल व्योम amdgpu_virt_populate_vf2pf_ucode_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amd_sriov_msg_vf2pf_info *vf2pf_info;
	vf2pf_info = (काष्ठा amd_sriov_msg_vf2pf_info *) adev->virt.fw_reserve.p_vf2pf;

	अगर (adev->virt.fw_reserve.p_vf2pf == शून्य)
		वापस;

	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_VCE,      adev->vce.fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_UVD,      adev->uvd.fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_MC,       adev->gmc.fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_ME,       adev->gfx.me_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_PFP,      adev->gfx.pfp_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_CE,       adev->gfx.ce_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_RLC,      adev->gfx.rlc_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_RLC_SRLC, adev->gfx.rlc_srlc_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_RLC_SRLG, adev->gfx.rlc_srlg_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_RLC_SRLS, adev->gfx.rlc_srls_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_MEC,      adev->gfx.mec_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_MEC2,     adev->gfx.mec2_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_SOS,      adev->psp.sos_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_ASD,      adev->psp.asd_fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_TA_RAS,   adev->psp.ta_ras_ucode_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_TA_XGMI,  adev->psp.ta_xgmi_ucode_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_SMC,      adev->pm.fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_SDMA,     adev->sdma.instance[0].fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_SDMA2,    adev->sdma.instance[1].fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_VCN,      adev->vcn.fw_version);
	POPULATE_UCODE_INFO(vf2pf_info, AMD_SRIOV_UCODE_ID_DMCU,     adev->dm.dmcu_fw_version);
पूर्ण

अटल पूर्णांक amdgpu_virt_ग_लिखो_vf2pf_data(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amd_sriov_msg_vf2pf_info *vf2pf_info;
	काष्ठा tपंचांग_resource_manager *vram_man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);

	vf2pf_info = (काष्ठा amd_sriov_msg_vf2pf_info *) adev->virt.fw_reserve.p_vf2pf;

	अगर (adev->virt.fw_reserve.p_vf2pf == शून्य)
		वापस -EINVAL;

	स_रखो(vf2pf_info, 0, माप(काष्ठा amd_sriov_msg_vf2pf_info));

	vf2pf_info->header.size = माप(काष्ठा amd_sriov_msg_vf2pf_info);
	vf2pf_info->header.version = AMD_SRIOV_MSG_FW_VRAM_VF2PF_VER;

#अगर_घोषित MODULE
	अगर (THIS_MODULE->version != शून्य)
		म_नकल(vf2pf_info->driver_version, THIS_MODULE->version);
	अन्यथा
#पूर्ण_अगर
		म_नकल(vf2pf_info->driver_version, "N/A");

	vf2pf_info->pf2vf_version_required = 0; // no requirement, guest understands all
	vf2pf_info->driver_cert = 0;
	vf2pf_info->os_info.all = 0;

	vf2pf_info->fb_usage = amdgpu_vram_mgr_usage(vram_man) >> 20;
	vf2pf_info->fb_vis_usage = amdgpu_vram_mgr_vis_usage(vram_man) >> 20;
	vf2pf_info->fb_size = adev->gmc.real_vram_size >> 20;
	vf2pf_info->fb_vis_size = adev->gmc.visible_vram_size >> 20;

	amdgpu_virt_populate_vf2pf_ucode_info(adev);

	/* TODO: पढ़ो dynamic info */
	vf2pf_info->gfx_usage = 0;
	vf2pf_info->compute_usage = 0;
	vf2pf_info->encode_usage = 0;
	vf2pf_info->decode_usage = 0;

	vf2pf_info->checksum =
		amd_sriov_msg_checksum(
		vf2pf_info, vf2pf_info->header.size, 0, 0);

	वापस 0;
पूर्ण

अटल व्योम amdgpu_virt_update_vf2pf_work_item(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev = container_of(work, काष्ठा amdgpu_device, virt.vf2pf_work.work);
	पूर्णांक ret;

	ret = amdgpu_virt_पढ़ो_pf2vf_data(adev);
	अगर (ret)
		जाओ out;
	amdgpu_virt_ग_लिखो_vf2pf_data(adev);

out:
	schedule_delayed_work(&(adev->virt.vf2pf_work), adev->virt.vf2pf_update_पूर्णांकerval_ms);
पूर्ण

व्योम amdgpu_virt_fini_data_exchange(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->virt.vf2pf_update_पूर्णांकerval_ms != 0) अणु
		DRM_INFO("clean up the vf2pf work item\n");
		cancel_delayed_work_sync(&adev->virt.vf2pf_work);
		adev->virt.vf2pf_update_पूर्णांकerval_ms = 0;
	पूर्ण
पूर्ण

व्योम amdgpu_virt_init_data_exchange(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t bp_block_offset = 0;
	uपूर्णांक32_t bp_block_size = 0;
	काष्ठा amd_sriov_msg_pf2vf_info *pf2vf_v2 = शून्य;

	adev->virt.fw_reserve.p_pf2vf = शून्य;
	adev->virt.fw_reserve.p_vf2pf = शून्य;
	adev->virt.vf2pf_update_पूर्णांकerval_ms = 0;

	अगर (adev->mman.fw_vram_usage_va != शून्य) अणु
		adev->virt.vf2pf_update_पूर्णांकerval_ms = 2000;

		adev->virt.fw_reserve.p_pf2vf =
			(काष्ठा amd_sriov_msg_pf2vf_info_header *)
			(adev->mman.fw_vram_usage_va + (AMD_SRIOV_MSG_PF2VF_OFFSET_KB << 10));
		adev->virt.fw_reserve.p_vf2pf =
			(काष्ठा amd_sriov_msg_vf2pf_info_header *)
			(adev->mman.fw_vram_usage_va + (AMD_SRIOV_MSG_VF2PF_OFFSET_KB << 10));

		amdgpu_virt_पढ़ो_pf2vf_data(adev);
		amdgpu_virt_ग_लिखो_vf2pf_data(adev);

		/* bad page handling क्रम version 2 */
		अगर (adev->virt.fw_reserve.p_pf2vf->version == 2) अणु
				pf2vf_v2 = (काष्ठा amd_sriov_msg_pf2vf_info *)adev->virt.fw_reserve.p_pf2vf;

				bp_block_offset = ((uपूर्णांक64_t)pf2vf_v2->bp_block_offset_low & 0xFFFFFFFF) |
						((((uपूर्णांक64_t)pf2vf_v2->bp_block_offset_high) << 32) & 0xFFFFFFFF00000000);
				bp_block_size = pf2vf_v2->bp_block_size;

				अगर (bp_block_size && !adev->virt.ras_init_करोne)
					amdgpu_virt_init_ras_err_handler_data(adev);

				अगर (adev->virt.ras_init_करोne)
					amdgpu_virt_add_bad_page(adev, bp_block_offset, bp_block_size);
			पूर्ण
	पूर्ण अन्यथा अगर (adev->bios != शून्य) अणु
		adev->virt.fw_reserve.p_pf2vf =
			(काष्ठा amd_sriov_msg_pf2vf_info_header *)
			(adev->bios + (AMD_SRIOV_MSG_PF2VF_OFFSET_KB << 10));

		amdgpu_virt_पढ़ो_pf2vf_data(adev);

		वापस;
	पूर्ण

	अगर (adev->virt.vf2pf_update_पूर्णांकerval_ms != 0) अणु
		INIT_DELAYED_WORK(&adev->virt.vf2pf_work, amdgpu_virt_update_vf2pf_work_item);
		schedule_delayed_work(&(adev->virt.vf2pf_work), adev->virt.vf2pf_update_पूर्णांकerval_ms);
	पूर्ण
पूर्ण

व्योम amdgpu_detect_भवization(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t reg;

	चयन (adev->asic_type) अणु
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
		reg = RREG32(mmBIF_IOV_FUNC_IDENTIFIER);
		अवरोध;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA20:
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
		reg = RREG32(mmRCC_IOV_FUNC_IDENTIFIER);
		अवरोध;
	शेष: /* other chip करोesn't support SRIOV */
		reg = 0;
		अवरोध;
	पूर्ण

	अगर (reg & 1)
		adev->virt.caps |= AMDGPU_SRIOV_CAPS_IS_VF;

	अगर (reg & 0x80000000)
		adev->virt.caps |= AMDGPU_SRIOV_CAPS_ENABLE_IOV;

	अगर (!reg) अणु
		अगर (is_भव_machine())	/* passthrough mode exclus sriov mod */
			adev->virt.caps |= AMDGPU_PASSTHROUGH_MODE;
	पूर्ण

	/* we have the ability to check now */
	अगर (amdgpu_sriov_vf(adev)) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_TONGA:
		हाल CHIP_FIJI:
			vi_set_virt_ops(adev);
			अवरोध;
		हाल CHIP_VEGA10:
		हाल CHIP_VEGA20:
		हाल CHIP_ARCTURUS:
			soc15_set_virt_ops(adev);
			अवरोध;
		हाल CHIP_NAVI10:
		हाल CHIP_NAVI12:
		हाल CHIP_SIENNA_CICHLID:
			nv_set_virt_ops(adev);
			/* try send GPU_INIT_DATA request to host */
			amdgpu_virt_request_init_data(adev);
			अवरोध;
		शेष: /* other chip करोesn't support SRIOV */
			DRM_ERROR("Unknown asic type: %d!\n", adev->asic_type);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool amdgpu_virt_access_debugfs_is_mmio(काष्ठा amdgpu_device *adev)
अणु
	वापस amdgpu_sriov_is_debug(adev) ? true : false;
पूर्ण

अटल bool amdgpu_virt_access_debugfs_is_kiq(काष्ठा amdgpu_device *adev)
अणु
	वापस amdgpu_sriov_is_normal(adev) ? true : false;
पूर्ण

पूर्णांक amdgpu_virt_enable_access_debugfs(काष्ठा amdgpu_device *adev)
अणु
	अगर (!amdgpu_sriov_vf(adev) ||
	    amdgpu_virt_access_debugfs_is_kiq(adev))
		वापस 0;

	अगर (amdgpu_virt_access_debugfs_is_mmio(adev))
		adev->virt.caps &= ~AMDGPU_SRIOV_CAPS_RUNTIME;
	अन्यथा
		वापस -EPERM;

	वापस 0;
पूर्ण

व्योम amdgpu_virt_disable_access_debugfs(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_sriov_vf(adev))
		adev->virt.caps |= AMDGPU_SRIOV_CAPS_RUNTIME;
पूर्ण

क्रमागत amdgpu_sriov_vf_mode amdgpu_virt_get_sriov_vf_mode(काष्ठा amdgpu_device *adev)
अणु
	क्रमागत amdgpu_sriov_vf_mode mode;

	अगर (amdgpu_sriov_vf(adev)) अणु
		अगर (amdgpu_sriov_is_pp_one_vf(adev))
			mode = SRIOV_VF_MODE_ONE_VF;
		अन्यथा
			mode = SRIOV_VF_MODE_MULTI_VF;
	पूर्ण अन्यथा अणु
		mode = SRIOV_VF_MODE_BARE_METAL;
	पूर्ण

	वापस mode;
पूर्ण
