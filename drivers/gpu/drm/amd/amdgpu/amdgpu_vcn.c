<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_vcn.h"
#समावेश "soc15d.h"

/* Firmware Names */
#घोषणा FIRMWARE_RAVEN		"amdgpu/raven_vcn.bin"
#घोषणा FIRMWARE_PICASSO	"amdgpu/picasso_vcn.bin"
#घोषणा FIRMWARE_RAVEN2		"amdgpu/raven2_vcn.bin"
#घोषणा FIRMWARE_ARCTURUS	"amdgpu/arcturus_vcn.bin"
#घोषणा FIRMWARE_RENOIR		"amdgpu/renoir_vcn.bin"
#घोषणा FIRMWARE_GREEN_SARDINE	"amdgpu/green_sardine_vcn.bin"
#घोषणा FIRMWARE_NAVI10		"amdgpu/navi10_vcn.bin"
#घोषणा FIRMWARE_NAVI14		"amdgpu/navi14_vcn.bin"
#घोषणा FIRMWARE_NAVI12		"amdgpu/navi12_vcn.bin"
#घोषणा FIRMWARE_SIENNA_CICHLID	"amdgpu/sienna_cichlid_vcn.bin"
#घोषणा FIRMWARE_NAVY_FLOUNDER	"amdgpu/navy_flounder_vcn.bin"
#घोषणा FIRMWARE_VANGOGH	"amdgpu/vangogh_vcn.bin"
#घोषणा FIRMWARE_DIMGREY_CAVEFISH	"amdgpu/dimgrey_cavefish_vcn.bin"
#घोषणा FIRMWARE_ALDEBARAN	"amdgpu/aldebaran_vcn.bin"

MODULE_FIRMWARE(FIRMWARE_RAVEN);
MODULE_FIRMWARE(FIRMWARE_PICASSO);
MODULE_FIRMWARE(FIRMWARE_RAVEN2);
MODULE_FIRMWARE(FIRMWARE_ARCTURUS);
MODULE_FIRMWARE(FIRMWARE_RENOIR);
MODULE_FIRMWARE(FIRMWARE_GREEN_SARDINE);
MODULE_FIRMWARE(FIRMWARE_ALDEBARAN);
MODULE_FIRMWARE(FIRMWARE_NAVI10);
MODULE_FIRMWARE(FIRMWARE_NAVI14);
MODULE_FIRMWARE(FIRMWARE_NAVI12);
MODULE_FIRMWARE(FIRMWARE_SIENNA_CICHLID);
MODULE_FIRMWARE(FIRMWARE_NAVY_FLOUNDER);
MODULE_FIRMWARE(FIRMWARE_VANGOGH);
MODULE_FIRMWARE(FIRMWARE_DIMGREY_CAVEFISH);

अटल व्योम amdgpu_vcn_idle_work_handler(काष्ठा work_काष्ठा *work);

पूर्णांक amdgpu_vcn_sw_init(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित दीर्घ bo_size;
	स्थिर अक्षर *fw_name;
	स्थिर काष्ठा common_firmware_header *hdr;
	अचिन्हित अक्षर fw_check;
	पूर्णांक i, r;

	INIT_DELAYED_WORK(&adev->vcn.idle_work, amdgpu_vcn_idle_work_handler);
	mutex_init(&adev->vcn.vcn_pg_lock);
	mutex_init(&adev->vcn.vcn1_jpeg1_workaround);
	atomic_set(&adev->vcn.total_submission_cnt, 0);
	क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++)
		atomic_set(&adev->vcn.inst[i].dpg_enc_submission_cnt, 0);

	चयन (adev->asic_type) अणु
	हाल CHIP_RAVEN:
		अगर (adev->apu_flags & AMD_APU_IS_RAVEN2)
			fw_name = FIRMWARE_RAVEN2;
		अन्यथा अगर (adev->apu_flags & AMD_APU_IS_PICASSO)
			fw_name = FIRMWARE_PICASSO;
		अन्यथा
			fw_name = FIRMWARE_RAVEN;
		अवरोध;
	हाल CHIP_ARCTURUS:
		fw_name = FIRMWARE_ARCTURUS;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_RENOIR:
		अगर (adev->apu_flags & AMD_APU_IS_RENOIR)
			fw_name = FIRMWARE_RENOIR;
		अन्यथा
			fw_name = FIRMWARE_GREEN_SARDINE;

		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_ALDEBARAN:
		fw_name = FIRMWARE_ALDEBARAN;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_NAVI10:
		fw_name = FIRMWARE_NAVI10;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_NAVI14:
		fw_name = FIRMWARE_NAVI14;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_NAVI12:
		fw_name = FIRMWARE_NAVI12;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		fw_name = FIRMWARE_SIENNA_CICHLID;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		fw_name = FIRMWARE_NAVY_FLOUNDER;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	हाल CHIP_VANGOGH:
		fw_name = FIRMWARE_VANGOGH;
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		fw_name = FIRMWARE_DIMGREY_CAVEFISH;
		अगर ((adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) &&
		    (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG))
			adev->vcn.indirect_sram = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	r = request_firmware(&adev->vcn.fw, fw_name, adev->dev);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_vcn: Can't load firmware \"%s\"\n",
			fw_name);
		वापस r;
	पूर्ण

	r = amdgpu_ucode_validate(adev->vcn.fw);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_vcn: Can't validate firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->vcn.fw);
		adev->vcn.fw = शून्य;
		वापस r;
	पूर्ण

	hdr = (स्थिर काष्ठा common_firmware_header *)adev->vcn.fw->data;
	adev->vcn.fw_version = le32_to_cpu(hdr->ucode_version);

	/* Bit 20-23, it is encode major and non-zero क्रम new naming convention.
	 * This field is part of version minor and DRM_DISABLED_FLAG in old naming
	 * convention. Since the l:wq!atest version minor is 0x5B and DRM_DISABLED_FLAG
	 * is zero in old naming convention, this field is always zero so far.
	 * These four bits are used to tell which naming convention is present.
	 */
	fw_check = (le32_to_cpu(hdr->ucode_version) >> 20) & 0xf;
	अगर (fw_check) अणु
		अचिन्हित पूर्णांक dec_ver, enc_major, enc_minor, vep, fw_rev;

		fw_rev = le32_to_cpu(hdr->ucode_version) & 0xfff;
		enc_minor = (le32_to_cpu(hdr->ucode_version) >> 12) & 0xff;
		enc_major = fw_check;
		dec_ver = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xf;
		vep = (le32_to_cpu(hdr->ucode_version) >> 28) & 0xf;
		DRM_INFO("Found VCN firmware Version ENC: %u.%u DEC: %u VEP: %u Revision: %u\n",
			enc_major, enc_minor, dec_ver, vep, fw_rev);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक version_major, version_minor, family_id;

		family_id = le32_to_cpu(hdr->ucode_version) & 0xff;
		version_major = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xff;
		version_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
		DRM_INFO("Found VCN firmware Version: %u.%u Family ID: %u\n",
			version_major, version_minor, family_id);
	पूर्ण

	bo_size = AMDGPU_VCN_STACK_SIZE + AMDGPU_VCN_CONTEXT_SIZE;
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		bo_size += AMDGPU_GPU_PAGE_ALIGN(le32_to_cpu(hdr->ucode_size_bytes) + 8);
	bo_size += AMDGPU_GPU_PAGE_ALIGN(माप(काष्ठा amdgpu_fw_shared));

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		r = amdgpu_bo_create_kernel(adev, bo_size, PAGE_SIZE,
						AMDGPU_GEM_DOMAIN_VRAM, &adev->vcn.inst[i].vcpu_bo,
						&adev->vcn.inst[i].gpu_addr, &adev->vcn.inst[i].cpu_addr);
		अगर (r) अणु
			dev_err(adev->dev, "(%d) failed to allocate vcn bo\n", r);
			वापस r;
		पूर्ण

		adev->vcn.inst[i].fw_shared_cpu_addr = adev->vcn.inst[i].cpu_addr +
				bo_size - AMDGPU_GPU_PAGE_ALIGN(माप(काष्ठा amdgpu_fw_shared));
		adev->vcn.inst[i].fw_shared_gpu_addr = adev->vcn.inst[i].gpu_addr +
				bo_size - AMDGPU_GPU_PAGE_ALIGN(माप(काष्ठा amdgpu_fw_shared));

		अगर (adev->vcn.indirect_sram) अणु
			r = amdgpu_bo_create_kernel(adev, 64 * 2 * 4, PAGE_SIZE,
					AMDGPU_GEM_DOMAIN_VRAM, &adev->vcn.inst[i].dpg_sram_bo,
					&adev->vcn.inst[i].dpg_sram_gpu_addr, &adev->vcn.inst[i].dpg_sram_cpu_addr);
			अगर (r) अणु
				dev_err(adev->dev, "VCN %d (%d) failed to allocate DPG bo\n", i, r);
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_vcn_sw_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	क्रम (j = 0; j < adev->vcn.num_vcn_inst; ++j) अणु
		अगर (adev->vcn.harvest_config & (1 << j))
			जारी;

		अगर (adev->vcn.indirect_sram) अणु
			amdgpu_bo_मुक्त_kernel(&adev->vcn.inst[j].dpg_sram_bo,
						  &adev->vcn.inst[j].dpg_sram_gpu_addr,
						  (व्योम **)&adev->vcn.inst[j].dpg_sram_cpu_addr);
		पूर्ण
		kvमुक्त(adev->vcn.inst[j].saved_bo);

		amdgpu_bo_मुक्त_kernel(&adev->vcn.inst[j].vcpu_bo,
					  &adev->vcn.inst[j].gpu_addr,
					  (व्योम **)&adev->vcn.inst[j].cpu_addr);

		amdgpu_ring_fini(&adev->vcn.inst[j].ring_dec);

		क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i)
			amdgpu_ring_fini(&adev->vcn.inst[j].ring_enc[i]);
	पूर्ण

	release_firmware(adev->vcn.fw);
	mutex_destroy(&adev->vcn.vcn1_jpeg1_workaround);
	mutex_destroy(&adev->vcn.vcn_pg_lock);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_vcn_suspend(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित size;
	व्योम *ptr;
	पूर्णांक i;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		अगर (adev->vcn.inst[i].vcpu_bo == शून्य)
			वापस 0;

		size = amdgpu_bo_size(adev->vcn.inst[i].vcpu_bo);
		ptr = adev->vcn.inst[i].cpu_addr;

		adev->vcn.inst[i].saved_bo = kvदो_स्मृति(size, GFP_KERNEL);
		अगर (!adev->vcn.inst[i].saved_bo)
			वापस -ENOMEM;

		स_नकल_fromio(adev->vcn.inst[i].saved_bo, ptr, size);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक amdgpu_vcn_resume(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित size;
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		अगर (adev->vcn.inst[i].vcpu_bo == शून्य)
			वापस -EINVAL;

		size = amdgpu_bo_size(adev->vcn.inst[i].vcpu_bo);
		ptr = adev->vcn.inst[i].cpu_addr;

		अगर (adev->vcn.inst[i].saved_bo != शून्य) अणु
			स_नकल_toio(ptr, adev->vcn.inst[i].saved_bo, size);
			kvमुक्त(adev->vcn.inst[i].saved_bo);
			adev->vcn.inst[i].saved_bo = शून्य;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा common_firmware_header *hdr;
			अचिन्हित offset;

			hdr = (स्थिर काष्ठा common_firmware_header *)adev->vcn.fw->data;
			अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) अणु
				offset = le32_to_cpu(hdr->ucode_array_offset_bytes);
				स_नकल_toio(adev->vcn.inst[i].cpu_addr, adev->vcn.fw->data + offset,
					    le32_to_cpu(hdr->ucode_size_bytes));
				size -= le32_to_cpu(hdr->ucode_size_bytes);
				ptr += le32_to_cpu(hdr->ucode_size_bytes);
			पूर्ण
			स_रखो_io(ptr, 0, size);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम amdgpu_vcn_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device, vcn.idle_work.work);
	अचिन्हित पूर्णांक fences = 0, fence[AMDGPU_MAX_VCN_INSTANCES] = अणु0पूर्ण;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक r = 0;

	क्रम (j = 0; j < adev->vcn.num_vcn_inst; ++j) अणु
		अगर (adev->vcn.harvest_config & (1 << j))
			जारी;

		क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
			fence[j] += amdgpu_fence_count_emitted(&adev->vcn.inst[j].ring_enc[i]);
		पूर्ण

		अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)	अणु
			काष्ठा dpg_छोड़ो_state new_state;

			अगर (fence[j] ||
				unlikely(atomic_पढ़ो(&adev->vcn.inst[j].dpg_enc_submission_cnt)))
				new_state.fw_based = VCN_DPG_STATE__PAUSE;
			अन्यथा
				new_state.fw_based = VCN_DPG_STATE__UNPAUSE;

			adev->vcn.छोड़ो_dpg_mode(adev, j, &new_state);
		पूर्ण

		fence[j] += amdgpu_fence_count_emitted(&adev->vcn.inst[j].ring_dec);
		fences += fence[j];
	पूर्ण

	अगर (!fences && !atomic_पढ़ो(&adev->vcn.total_submission_cnt)) अणु
		amdgpu_gfx_off_ctrl(adev, true);
		amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCN,
		       AMD_PG_STATE_GATE);
		r = amdgpu_dpm_चयन_घातer_profile(adev, PP_SMC_POWER_PROखाता_VIDEO,
				false);
		अगर (r)
			dev_warn(adev->dev, "(%d) failed to disable video power profile mode\n", r);
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&adev->vcn.idle_work, VCN_IDLE_TIMEOUT);
	पूर्ण
पूर्ण

व्योम amdgpu_vcn_ring_begin_use(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	पूर्णांक r = 0;

	atomic_inc(&adev->vcn.total_submission_cnt);

	अगर (!cancel_delayed_work_sync(&adev->vcn.idle_work)) अणु
		amdgpu_gfx_off_ctrl(adev, false);
		r = amdgpu_dpm_चयन_घातer_profile(adev, PP_SMC_POWER_PROखाता_VIDEO,
				true);
		अगर (r)
			dev_warn(adev->dev, "(%d) failed to switch to video power profile mode\n", r);
	पूर्ण

	mutex_lock(&adev->vcn.vcn_pg_lock);
	amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCN,
	       AMD_PG_STATE_UNGATE);

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)	अणु
		काष्ठा dpg_छोड़ो_state new_state;

		अगर (ring->funcs->type == AMDGPU_RING_TYPE_VCN_ENC) अणु
			atomic_inc(&adev->vcn.inst[ring->me].dpg_enc_submission_cnt);
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक fences = 0;
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i)
				fences += amdgpu_fence_count_emitted(&adev->vcn.inst[ring->me].ring_enc[i]);

			अगर (fences || atomic_पढ़ो(&adev->vcn.inst[ring->me].dpg_enc_submission_cnt))
				new_state.fw_based = VCN_DPG_STATE__PAUSE;
			अन्यथा
				new_state.fw_based = VCN_DPG_STATE__UNPAUSE;
		पूर्ण

		adev->vcn.छोड़ो_dpg_mode(adev, ring->me, &new_state);
	पूर्ण
	mutex_unlock(&adev->vcn.vcn_pg_lock);
पूर्ण

व्योम amdgpu_vcn_ring_end_use(काष्ठा amdgpu_ring *ring)
अणु
	अगर (ring->adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG &&
		ring->funcs->type == AMDGPU_RING_TYPE_VCN_ENC)
		atomic_dec(&ring->adev->vcn.inst[ring->me].dpg_enc_submission_cnt);

	atomic_dec(&ring->adev->vcn.total_submission_cnt);

	schedule_delayed_work(&ring->adev->vcn.idle_work, VCN_IDLE_TIMEOUT);
पूर्ण

पूर्णांक amdgpu_vcn_dec_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	/* VCN in SRIOV करोes not support direct रेजिस्टर पढ़ो/ग_लिखो */
	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	WREG32(adev->vcn.inst[ring->me].बाह्यal.scratch9, 0xCAFEDEAD);
	r = amdgpu_ring_alloc(ring, 3);
	अगर (r)
		वापस r;
	amdgpu_ring_ग_लिखो(ring, PACKET0(adev->vcn.पूर्णांकernal.scratch9, 0));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32(adev->vcn.inst[ring->me].बाह्यal.scratch9);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

पूर्णांक amdgpu_vcn_dec_sw_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t rptr;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	r = amdgpu_ring_alloc(ring, 16);
	अगर (r)
		वापस r;

	rptr = amdgpu_ring_get_rptr(ring);

	amdgpu_ring_ग_लिखो(ring, VCN_DEC_SW_CMD_END);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (amdgpu_ring_get_rptr(ring) != rptr)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_vcn_dec_send_msg(काष्ठा amdgpu_ring *ring,
				   काष्ठा amdgpu_bo *bo,
				   काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा dma_fence *f = शून्य;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	uपूर्णांक64_t addr;
	व्योम *msg = शून्य;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(adev, 64,
					AMDGPU_IB_POOL_सूचीECT, &job);
	अगर (r)
		जाओ err;

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);
	msg = amdgpu_bo_kptr(bo);
	ib->ptr[0] = PACKET0(adev->vcn.पूर्णांकernal.data0, 0);
	ib->ptr[1] = addr;
	ib->ptr[2] = PACKET0(adev->vcn.पूर्णांकernal.data1, 0);
	ib->ptr[3] = addr >> 32;
	ib->ptr[4] = PACKET0(adev->vcn.पूर्णांकernal.cmd, 0);
	ib->ptr[5] = 0;
	क्रम (i = 6; i < 16; i += 2) अणु
		ib->ptr[i] = PACKET0(adev->vcn.पूर्णांकernal.nop, 0);
		ib->ptr[i+1] = 0;
	पूर्ण
	ib->length_dw = 16;

	r = amdgpu_job_submit_direct(job, ring, &f);
	अगर (r)
		जाओ err_मुक्त;

	amdgpu_bo_fence(bo, f, false);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_मुक्त_kernel(&bo, शून्य, (व्योम **)&msg);

	अगर (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	वापस 0;

err_मुक्त:
	amdgpu_job_मुक्त(job);

err:
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_मुक्त_kernel(&bo, शून्य, (व्योम **)&msg);
	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_vcn_dec_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
					 काष्ठा amdgpu_bo **bo)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t *msg;
	पूर्णांक r, i;

	*bo = शून्य;
	r = amdgpu_bo_create_reserved(adev, 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      bo, शून्य, (व्योम **)&msg);
	अगर (r)
		वापस r;

	msg[0] = cpu_to_le32(0x00000028);
	msg[1] = cpu_to_le32(0x00000038);
	msg[2] = cpu_to_le32(0x00000001);
	msg[3] = cpu_to_le32(0x00000000);
	msg[4] = cpu_to_le32(handle);
	msg[5] = cpu_to_le32(0x00000000);
	msg[6] = cpu_to_le32(0x00000001);
	msg[7] = cpu_to_le32(0x00000028);
	msg[8] = cpu_to_le32(0x00000010);
	msg[9] = cpu_to_le32(0x00000000);
	msg[10] = cpu_to_le32(0x00000007);
	msg[11] = cpu_to_le32(0x00000000);
	msg[12] = cpu_to_le32(0x00000780);
	msg[13] = cpu_to_le32(0x00000440);
	क्रम (i = 14; i < 1024; ++i)
		msg[i] = cpu_to_le32(0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_vcn_dec_get_destroy_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
					  काष्ठा amdgpu_bo **bo)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t *msg;
	पूर्णांक r, i;

	*bo = शून्य;
	r = amdgpu_bo_create_reserved(adev, 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      bo, शून्य, (व्योम **)&msg);
	अगर (r)
		वापस r;

	msg[0] = cpu_to_le32(0x00000028);
	msg[1] = cpu_to_le32(0x00000018);
	msg[2] = cpu_to_le32(0x00000000);
	msg[3] = cpu_to_le32(0x00000002);
	msg[4] = cpu_to_le32(handle);
	msg[5] = cpu_to_le32(0x00000000);
	क्रम (i = 6; i < 1024; ++i)
		msg[i] = cpu_to_le32(0x0);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_vcn_dec_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा amdgpu_bo *bo;
	दीर्घ r;

	r = amdgpu_vcn_dec_get_create_msg(ring, 1, &bo);
	अगर (r)
		जाओ error;

	r = amdgpu_vcn_dec_send_msg(ring, bo, शून्य);
	अगर (r)
		जाओ error;
	r = amdgpu_vcn_dec_get_destroy_msg(ring, 1, &bo);
	अगर (r)
		जाओ error;

	r = amdgpu_vcn_dec_send_msg(ring, bo, &fence);
	अगर (r)
		जाओ error;

	r = dma_fence_रुको_समयout(fence, false, समयout);
	अगर (r == 0)
		r = -ETIMEDOUT;
	अन्यथा अगर (r > 0)
		r = 0;

	dma_fence_put(fence);
error:
	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_vcn_dec_sw_send_msg(काष्ठा amdgpu_ring *ring,
				   काष्ठा amdgpu_bo *bo,
				   काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_vcn_decode_buffer *decode_buffer = शून्य;
	स्थिर अचिन्हित पूर्णांक ib_size_dw = 64;
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा dma_fence *f = शून्य;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	uपूर्णांक64_t addr;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(adev, ib_size_dw * 4,
				AMDGPU_IB_POOL_सूचीECT, &job);
	अगर (r)
		जाओ err;

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);
	ib->length_dw = 0;

	ib->ptr[ib->length_dw++] = माप(काष्ठा amdgpu_vcn_decode_buffer) + 8;
	ib->ptr[ib->length_dw++] = cpu_to_le32(AMDGPU_VCN_IB_FLAG_DECODE_BUFFER);
	decode_buffer = (काष्ठा amdgpu_vcn_decode_buffer *)&(ib->ptr[ib->length_dw]);
	ib->length_dw += माप(काष्ठा amdgpu_vcn_decode_buffer) / 4;
	स_रखो(decode_buffer, 0, माप(काष्ठा amdgpu_vcn_decode_buffer));

	decode_buffer->valid_buf_flag |= cpu_to_le32(AMDGPU_VCN_CMD_FLAG_MSG_BUFFER);
	decode_buffer->msg_buffer_address_hi = cpu_to_le32(addr >> 32);
	decode_buffer->msg_buffer_address_lo = cpu_to_le32(addr);

	क्रम (i = ib->length_dw; i < ib_size_dw; ++i)
		ib->ptr[i] = 0x0;

	r = amdgpu_job_submit_direct(job, ring, &f);
	अगर (r)
		जाओ err_मुक्त;

	amdgpu_bo_fence(bo, f, false);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&bo);

	अगर (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	वापस 0;

err_मुक्त:
	amdgpu_job_मुक्त(job);

err:
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&bo);
	वापस r;
पूर्ण

पूर्णांक amdgpu_vcn_dec_sw_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा amdgpu_bo *bo;
	दीर्घ r;

	r = amdgpu_vcn_dec_get_create_msg(ring, 1, &bo);
	अगर (r)
		जाओ error;

	r = amdgpu_vcn_dec_sw_send_msg(ring, bo, शून्य);
	अगर (r)
		जाओ error;
	r = amdgpu_vcn_dec_get_destroy_msg(ring, 1, &bo);
	अगर (r)
		जाओ error;

	r = amdgpu_vcn_dec_sw_send_msg(ring, bo, &fence);
	अगर (r)
		जाओ error;

	r = dma_fence_रुको_समयout(fence, false, समयout);
	अगर (r == 0)
		r = -ETIMEDOUT;
	अन्यथा अगर (r > 0)
		r = 0;

	dma_fence_put(fence);
error:
	वापस r;
पूर्ण

पूर्णांक amdgpu_vcn_enc_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t rptr;
	अचिन्हित i;
	पूर्णांक r;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	r = amdgpu_ring_alloc(ring, 16);
	अगर (r)
		वापस r;

	rptr = amdgpu_ring_get_rptr(ring);

	amdgpu_ring_ग_लिखो(ring, VCN_ENC_CMD_END);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (amdgpu_ring_get_rptr(ring) != rptr)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_vcn_enc_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
					 काष्ठा amdgpu_bo *bo,
					 काष्ठा dma_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 16;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	काष्ठा dma_fence *f = शून्य;
	uपूर्णांक64_t addr;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(ring->adev, ib_size_dw * 4,
					AMDGPU_IB_POOL_सूचीECT, &job);
	अगर (r)
		वापस r;

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);

	ib->length_dw = 0;
	ib->ptr[ib->length_dw++] = 0x00000018;
	ib->ptr[ib->length_dw++] = 0x00000001; /* session info */
	ib->ptr[ib->length_dw++] = handle;
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = addr;
	ib->ptr[ib->length_dw++] = 0x0000000b;

	ib->ptr[ib->length_dw++] = 0x00000014;
	ib->ptr[ib->length_dw++] = 0x00000002; /* task info */
	ib->ptr[ib->length_dw++] = 0x0000001c;
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = 0x00000000;

	ib->ptr[ib->length_dw++] = 0x00000008;
	ib->ptr[ib->length_dw++] = 0x08000001; /* op initialize */

	क्रम (i = ib->length_dw; i < ib_size_dw; ++i)
		ib->ptr[i] = 0x0;

	r = amdgpu_job_submit_direct(job, ring, &f);
	अगर (r)
		जाओ err;

	अगर (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	वापस 0;

err:
	amdgpu_job_मुक्त(job);
	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_vcn_enc_get_destroy_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
					  काष्ठा amdgpu_bo *bo,
					  काष्ठा dma_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 16;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	काष्ठा dma_fence *f = शून्य;
	uपूर्णांक64_t addr;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(ring->adev, ib_size_dw * 4,
					AMDGPU_IB_POOL_सूचीECT, &job);
	अगर (r)
		वापस r;

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);

	ib->length_dw = 0;
	ib->ptr[ib->length_dw++] = 0x00000018;
	ib->ptr[ib->length_dw++] = 0x00000001;
	ib->ptr[ib->length_dw++] = handle;
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = addr;
	ib->ptr[ib->length_dw++] = 0x0000000b;

	ib->ptr[ib->length_dw++] = 0x00000014;
	ib->ptr[ib->length_dw++] = 0x00000002;
	ib->ptr[ib->length_dw++] = 0x0000001c;
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = 0x00000000;

	ib->ptr[ib->length_dw++] = 0x00000008;
	ib->ptr[ib->length_dw++] = 0x08000002; /* op बंद session */

	क्रम (i = ib->length_dw; i < ib_size_dw; ++i)
		ib->ptr[i] = 0x0;

	r = amdgpu_job_submit_direct(job, ring, &f);
	अगर (r)
		जाओ err;

	अगर (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	वापस 0;

err:
	amdgpu_job_मुक्त(job);
	वापस r;
पूर्ण

पूर्णांक amdgpu_vcn_enc_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा amdgpu_bo *bo = शून्य;
	दीर्घ r;

	r = amdgpu_bo_create_reserved(ring->adev, 128 * 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &bo, शून्य, शून्य);
	अगर (r)
		वापस r;

	r = amdgpu_vcn_enc_get_create_msg(ring, 1, bo, शून्य);
	अगर (r)
		जाओ error;

	r = amdgpu_vcn_enc_get_destroy_msg(ring, 1, bo, &fence);
	अगर (r)
		जाओ error;

	r = dma_fence_रुको_समयout(fence, false, समयout);
	अगर (r == 0)
		r = -ETIMEDOUT;
	अन्यथा अगर (r > 0)
		r = 0;

error:
	dma_fence_put(fence);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_मुक्त_kernel(&bo, शून्य, शून्य);

	वापस r;
पूर्ण
