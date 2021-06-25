<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
 * Authors: Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश <drm/drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_vce.h"
#समावेश "cikd.h"

/* 1 second समयout */
#घोषणा VCE_IDLE_TIMEOUT	msecs_to_jअगरfies(1000)

/* Firmware Names */
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
#घोषणा FIRMWARE_BONAIRE	"amdgpu/bonaire_vce.bin"
#घोषणा FIRMWARE_KABINI	"amdgpu/kabini_vce.bin"
#घोषणा FIRMWARE_KAVERI	"amdgpu/kaveri_vce.bin"
#घोषणा FIRMWARE_HAWAII	"amdgpu/hawaii_vce.bin"
#घोषणा FIRMWARE_MULLINS	"amdgpu/mullins_vce.bin"
#पूर्ण_अगर
#घोषणा FIRMWARE_TONGA		"amdgpu/tonga_vce.bin"
#घोषणा FIRMWARE_CARRIZO	"amdgpu/carrizo_vce.bin"
#घोषणा FIRMWARE_FIJI		"amdgpu/fiji_vce.bin"
#घोषणा FIRMWARE_STONEY		"amdgpu/stoney_vce.bin"
#घोषणा FIRMWARE_POLARIS10	"amdgpu/polaris10_vce.bin"
#घोषणा FIRMWARE_POLARIS11	"amdgpu/polaris11_vce.bin"
#घोषणा FIRMWARE_POLARIS12	"amdgpu/polaris12_vce.bin"
#घोषणा FIRMWARE_VEGAM		"amdgpu/vegam_vce.bin"

#घोषणा FIRMWARE_VEGA10		"amdgpu/vega10_vce.bin"
#घोषणा FIRMWARE_VEGA12		"amdgpu/vega12_vce.bin"
#घोषणा FIRMWARE_VEGA20		"amdgpu/vega20_vce.bin"

#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
MODULE_FIRMWARE(FIRMWARE_BONAIRE);
MODULE_FIRMWARE(FIRMWARE_KABINI);
MODULE_FIRMWARE(FIRMWARE_KAVERI);
MODULE_FIRMWARE(FIRMWARE_HAWAII);
MODULE_FIRMWARE(FIRMWARE_MULLINS);
#पूर्ण_अगर
MODULE_FIRMWARE(FIRMWARE_TONGA);
MODULE_FIRMWARE(FIRMWARE_CARRIZO);
MODULE_FIRMWARE(FIRMWARE_FIJI);
MODULE_FIRMWARE(FIRMWARE_STONEY);
MODULE_FIRMWARE(FIRMWARE_POLARIS10);
MODULE_FIRMWARE(FIRMWARE_POLARIS11);
MODULE_FIRMWARE(FIRMWARE_POLARIS12);
MODULE_FIRMWARE(FIRMWARE_VEGAM);

MODULE_FIRMWARE(FIRMWARE_VEGA10);
MODULE_FIRMWARE(FIRMWARE_VEGA12);
MODULE_FIRMWARE(FIRMWARE_VEGA20);

अटल व्योम amdgpu_vce_idle_work_handler(काष्ठा work_काष्ठा *work);
अटल पूर्णांक amdgpu_vce_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
				     काष्ठा amdgpu_bo *bo,
				     काष्ठा dma_fence **fence);
अटल पूर्णांक amdgpu_vce_get_destroy_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
				      bool direct, काष्ठा dma_fence **fence);

/**
 * amdgpu_vce_init - allocate memory, load vce firmware
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @size: size क्रम the new BO
 *
 * First step to get VCE online, allocate memory and load the firmware
 */
पूर्णांक amdgpu_vce_sw_init(काष्ठा amdgpu_device *adev, अचिन्हित दीर्घ size)
अणु
	स्थिर अक्षर *fw_name;
	स्थिर काष्ठा common_firmware_header *hdr;
	अचिन्हित ucode_version, version_major, version_minor, binary_id;
	पूर्णांक i, r;

	चयन (adev->asic_type) अणु
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	हाल CHIP_BONAIRE:
		fw_name = FIRMWARE_BONAIRE;
		अवरोध;
	हाल CHIP_KAVERI:
		fw_name = FIRMWARE_KAVERI;
		अवरोध;
	हाल CHIP_KABINI:
		fw_name = FIRMWARE_KABINI;
		अवरोध;
	हाल CHIP_HAWAII:
		fw_name = FIRMWARE_HAWAII;
		अवरोध;
	हाल CHIP_MULLINS:
		fw_name = FIRMWARE_MULLINS;
		अवरोध;
#पूर्ण_अगर
	हाल CHIP_TONGA:
		fw_name = FIRMWARE_TONGA;
		अवरोध;
	हाल CHIP_CARRIZO:
		fw_name = FIRMWARE_CARRIZO;
		अवरोध;
	हाल CHIP_FIJI:
		fw_name = FIRMWARE_FIJI;
		अवरोध;
	हाल CHIP_STONEY:
		fw_name = FIRMWARE_STONEY;
		अवरोध;
	हाल CHIP_POLARIS10:
		fw_name = FIRMWARE_POLARIS10;
		अवरोध;
	हाल CHIP_POLARIS11:
		fw_name = FIRMWARE_POLARIS11;
		अवरोध;
	हाल CHIP_POLARIS12:
		fw_name = FIRMWARE_POLARIS12;
		अवरोध;
	हाल CHIP_VEGAM:
		fw_name = FIRMWARE_VEGAM;
		अवरोध;
	हाल CHIP_VEGA10:
		fw_name = FIRMWARE_VEGA10;
		अवरोध;
	हाल CHIP_VEGA12:
		fw_name = FIRMWARE_VEGA12;
		अवरोध;
	हाल CHIP_VEGA20:
		fw_name = FIRMWARE_VEGA20;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	r = request_firmware(&adev->vce.fw, fw_name, adev->dev);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_vce: Can't load firmware \"%s\"\n",
			fw_name);
		वापस r;
	पूर्ण

	r = amdgpu_ucode_validate(adev->vce.fw);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_vce: Can't validate firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->vce.fw);
		adev->vce.fw = शून्य;
		वापस r;
	पूर्ण

	hdr = (स्थिर काष्ठा common_firmware_header *)adev->vce.fw->data;

	ucode_version = le32_to_cpu(hdr->ucode_version);
	version_major = (ucode_version >> 20) & 0xfff;
	version_minor = (ucode_version >> 8) & 0xfff;
	binary_id = ucode_version & 0xff;
	DRM_INFO("Found VCE firmware Version: %d.%d Binary ID: %d\n",
		version_major, version_minor, binary_id);
	adev->vce.fw_version = ((version_major << 24) | (version_minor << 16) |
				(binary_id << 8));

	r = amdgpu_bo_create_kernel(adev, size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_VRAM, &adev->vce.vcpu_bo,
				    &adev->vce.gpu_addr, &adev->vce.cpu_addr);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to allocate VCE bo\n", r);
		वापस r;
	पूर्ण

	क्रम (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) अणु
		atomic_set(&adev->vce.handles[i], 0);
		adev->vce.filp[i] = शून्य;
	पूर्ण

	INIT_DELAYED_WORK(&adev->vce.idle_work, amdgpu_vce_idle_work_handler);
	mutex_init(&adev->vce.idle_mutex);

	वापस 0;
पूर्ण

/**
 * amdgpu_vce_fini - मुक्त memory
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Last step on VCE tearकरोwn, मुक्त firmware memory
 */
पूर्णांक amdgpu_vce_sw_fini(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	अगर (adev->vce.vcpu_bo == शून्य)
		वापस 0;

	cancel_delayed_work_sync(&adev->vce.idle_work);
	drm_sched_entity_destroy(&adev->vce.entity);

	amdgpu_bo_मुक्त_kernel(&adev->vce.vcpu_bo, &adev->vce.gpu_addr,
		(व्योम **)&adev->vce.cpu_addr);

	क्रम (i = 0; i < adev->vce.num_rings; i++)
		amdgpu_ring_fini(&adev->vce.ring[i]);

	release_firmware(adev->vce.fw);
	mutex_destroy(&adev->vce.idle_mutex);

	वापस 0;
पूर्ण

/**
 * amdgpu_vce_entity_init - init entity
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 */
पूर्णांक amdgpu_vce_entity_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	काष्ठा drm_gpu_scheduler *sched;
	पूर्णांक r;

	ring = &adev->vce.ring[0];
	sched = &ring->sched;
	r = drm_sched_entity_init(&adev->vce.entity, DRM_SCHED_PRIORITY_NORMAL,
				  &sched, 1, शून्य);
	अगर (r != 0) अणु
		DRM_ERROR("Failed setting up VCE run queue.\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_vce_suspend - unpin VCE fw memory
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 */
पूर्णांक amdgpu_vce_suspend(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	cancel_delayed_work_sync(&adev->vce.idle_work);

	अगर (adev->vce.vcpu_bo == शून्य)
		वापस 0;

	क्रम (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i)
		अगर (atomic_पढ़ो(&adev->vce.handles[i]))
			अवरोध;

	अगर (i == AMDGPU_MAX_VCE_HANDLES)
		वापस 0;

	/* TODO: suspending running encoding sessions isn't supported */
	वापस -EINVAL;
पूर्ण

/**
 * amdgpu_vce_resume - pin VCE fw memory
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 */
पूर्णांक amdgpu_vce_resume(काष्ठा amdgpu_device *adev)
अणु
	व्योम *cpu_addr;
	स्थिर काष्ठा common_firmware_header *hdr;
	अचिन्हित offset;
	पूर्णांक r;

	अगर (adev->vce.vcpu_bo == शून्य)
		वापस -EINVAL;

	r = amdgpu_bo_reserve(adev->vce.vcpu_bo, false);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to reserve VCE bo\n", r);
		वापस r;
	पूर्ण

	r = amdgpu_bo_kmap(adev->vce.vcpu_bo, &cpu_addr);
	अगर (r) अणु
		amdgpu_bo_unreserve(adev->vce.vcpu_bo);
		dev_err(adev->dev, "(%d) VCE map failed\n", r);
		वापस r;
	पूर्ण

	hdr = (स्थिर काष्ठा common_firmware_header *)adev->vce.fw->data;
	offset = le32_to_cpu(hdr->ucode_array_offset_bytes);
	स_नकल_toio(cpu_addr, adev->vce.fw->data + offset,
		    adev->vce.fw->size - offset);

	amdgpu_bo_kunmap(adev->vce.vcpu_bo);

	amdgpu_bo_unreserve(adev->vce.vcpu_bo);

	वापस 0;
पूर्ण

/**
 * amdgpu_vce_idle_work_handler - घातer off VCE
 *
 * @work: poपूर्णांकer to work काष्ठाure
 *
 * घातer of VCE when it's not used any more
 */
अटल व्योम amdgpu_vce_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device, vce.idle_work.work);
	अचिन्हित i, count = 0;

	क्रम (i = 0; i < adev->vce.num_rings; i++)
		count += amdgpu_fence_count_emitted(&adev->vce.ring[i]);

	अगर (count == 0) अणु
		अगर (adev->pm.dpm_enabled) अणु
			amdgpu_dpm_enable_vce(adev, false);
		पूर्ण अन्यथा अणु
			amdgpu_asic_set_vce_घड़ीs(adev, 0, 0);
			amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_PG_STATE_GATE);
			amdgpu_device_ip_set_घड़ीgating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_CG_STATE_GATE);
		पूर्ण
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&adev->vce.idle_work, VCE_IDLE_TIMEOUT);
	पूर्ण
पूर्ण

/**
 * amdgpu_vce_ring_begin_use - घातer up VCE
 *
 * @ring: amdgpu ring
 *
 * Make sure VCE is घातerd up when we want to use it
 */
व्योम amdgpu_vce_ring_begin_use(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	bool set_घड़ीs;

	अगर (amdgpu_sriov_vf(adev))
		वापस;

	mutex_lock(&adev->vce.idle_mutex);
	set_घड़ीs = !cancel_delayed_work_sync(&adev->vce.idle_work);
	अगर (set_घड़ीs) अणु
		अगर (adev->pm.dpm_enabled) अणु
			amdgpu_dpm_enable_vce(adev, true);
		पूर्ण अन्यथा अणु
			amdgpu_asic_set_vce_घड़ीs(adev, 53300, 40000);
			amdgpu_device_ip_set_घड़ीgating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_CG_STATE_UNGATE);
			amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_PG_STATE_UNGATE);

		पूर्ण
	पूर्ण
	mutex_unlock(&adev->vce.idle_mutex);
पूर्ण

/**
 * amdgpu_vce_ring_end_use - घातer VCE करोwn
 *
 * @ring: amdgpu ring
 *
 * Schedule work to घातer VCE करोwn again
 */
व्योम amdgpu_vce_ring_end_use(काष्ठा amdgpu_ring *ring)
अणु
	अगर (!amdgpu_sriov_vf(ring->adev))
		schedule_delayed_work(&ring->adev->vce.idle_work, VCE_IDLE_TIMEOUT);
पूर्ण

/**
 * amdgpu_vce_मुक्त_handles - मुक्त still खोलो VCE handles
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @filp: drm file poपूर्णांकer
 *
 * Close all VCE handles still खोलो by this file poपूर्णांकer
 */
व्योम amdgpu_vce_मुक्त_handles(काष्ठा amdgpu_device *adev, काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_ring *ring = &adev->vce.ring[0];
	पूर्णांक i, r;
	क्रम (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) अणु
		uपूर्णांक32_t handle = atomic_पढ़ो(&adev->vce.handles[i]);

		अगर (!handle || adev->vce.filp[i] != filp)
			जारी;

		r = amdgpu_vce_get_destroy_msg(ring, handle, false, शून्य);
		अगर (r)
			DRM_ERROR("Error destroying VCE handle (%d)!\n", r);

		adev->vce.filp[i] = शून्य;
		atomic_set(&adev->vce.handles[i], 0);
	पूर्ण
पूर्ण

/**
 * amdgpu_vce_get_create_msg - generate a VCE create msg
 *
 * @ring: ring we should submit the msg to
 * @handle: VCE session handle to use
 * @bo: amdgpu object क्रम which we query the offset
 * @fence: optional fence to वापस
 *
 * Open up a stream क्रम HW test
 */
अटल पूर्णांक amdgpu_vce_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
				     काष्ठा amdgpu_bo *bo,
				     काष्ठा dma_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 1024;
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

	/* stitch together an VCE create msg */
	ib->length_dw = 0;
	ib->ptr[ib->length_dw++] = 0x0000000c; /* len */
	ib->ptr[ib->length_dw++] = 0x00000001; /* session cmd */
	ib->ptr[ib->length_dw++] = handle;

	अगर ((ring->adev->vce.fw_version >> 24) >= 52)
		ib->ptr[ib->length_dw++] = 0x00000040; /* len */
	अन्यथा
		ib->ptr[ib->length_dw++] = 0x00000030; /* len */
	ib->ptr[ib->length_dw++] = 0x01000001; /* create cmd */
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = 0x00000042;
	ib->ptr[ib->length_dw++] = 0x0000000a;
	ib->ptr[ib->length_dw++] = 0x00000001;
	ib->ptr[ib->length_dw++] = 0x00000080;
	ib->ptr[ib->length_dw++] = 0x00000060;
	ib->ptr[ib->length_dw++] = 0x00000100;
	ib->ptr[ib->length_dw++] = 0x00000100;
	ib->ptr[ib->length_dw++] = 0x0000000c;
	ib->ptr[ib->length_dw++] = 0x00000000;
	अगर ((ring->adev->vce.fw_version >> 24) >= 52) अणु
		ib->ptr[ib->length_dw++] = 0x00000000;
		ib->ptr[ib->length_dw++] = 0x00000000;
		ib->ptr[ib->length_dw++] = 0x00000000;
		ib->ptr[ib->length_dw++] = 0x00000000;
	पूर्ण

	ib->ptr[ib->length_dw++] = 0x00000014; /* len */
	ib->ptr[ib->length_dw++] = 0x05000005; /* feedback buffer */
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = addr;
	ib->ptr[ib->length_dw++] = 0x00000001;

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

/**
 * amdgpu_vce_get_destroy_msg - generate a VCE destroy msg
 *
 * @ring: ring we should submit the msg to
 * @handle: VCE session handle to use
 * @direct: direct or delayed pool
 * @fence: optional fence to वापस
 *
 * Close up a stream क्रम HW test or अगर userspace failed to करो so
 */
अटल पूर्णांक amdgpu_vce_get_destroy_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
				      bool direct, काष्ठा dma_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 1024;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	काष्ठा dma_fence *f = शून्य;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(ring->adev, ib_size_dw * 4,
				     direct ? AMDGPU_IB_POOL_सूचीECT :
				     AMDGPU_IB_POOL_DELAYED, &job);
	अगर (r)
		वापस r;

	ib = &job->ibs[0];

	/* stitch together an VCE destroy msg */
	ib->length_dw = 0;
	ib->ptr[ib->length_dw++] = 0x0000000c; /* len */
	ib->ptr[ib->length_dw++] = 0x00000001; /* session cmd */
	ib->ptr[ib->length_dw++] = handle;

	ib->ptr[ib->length_dw++] = 0x00000020; /* len */
	ib->ptr[ib->length_dw++] = 0x00000002; /* task info */
	ib->ptr[ib->length_dw++] = 0xffffffff; /* next task info, set to 0xffffffff अगर no */
	ib->ptr[ib->length_dw++] = 0x00000001; /* destroy session */
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = 0xffffffff; /* feedback is not needed, set to 0xffffffff and firmware will not output feedback */
	ib->ptr[ib->length_dw++] = 0x00000000;

	ib->ptr[ib->length_dw++] = 0x00000008; /* len */
	ib->ptr[ib->length_dw++] = 0x02000001; /* destroy cmd */

	क्रम (i = ib->length_dw; i < ib_size_dw; ++i)
		ib->ptr[i] = 0x0;

	अगर (direct)
		r = amdgpu_job_submit_direct(job, ring, &f);
	अन्यथा
		r = amdgpu_job_submit(job, &ring->adev->vce.entity,
				      AMDGPU_FENCE_OWNER_UNDEFINED, &f);
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

/**
 * amdgpu_vce_cs_validate_bo - make sure not to cross 4GB boundary
 *
 * @p: parser context
 * @ib_idx: indirect buffer to use
 * @lo: address of lower dword
 * @hi: address of higher dword
 * @size: minimum size
 * @index: bs/fb index
 *
 * Make sure that no BO cross a 4GB boundary.
 */
अटल पूर्णांक amdgpu_vce_validate_bo(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx,
				  पूर्णांक lo, पूर्णांक hi, अचिन्हित size, पूर्णांक32_t index)
अणु
	पूर्णांक64_t offset = ((uपूर्णांक64_t)size) * ((पूर्णांक64_t)index);
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा amdgpu_bo_va_mapping *mapping;
	अचिन्हित i, fpfn, lpfn;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक64_t addr;
	पूर्णांक r;

	addr = ((uपूर्णांक64_t)amdgpu_get_ib_value(p, ib_idx, lo)) |
	       ((uपूर्णांक64_t)amdgpu_get_ib_value(p, ib_idx, hi)) << 32;
	अगर (index >= 0) अणु
		addr += offset;
		fpfn = PAGE_ALIGN(offset) >> PAGE_SHIFT;
		lpfn = 0x100000000ULL >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		fpfn = 0;
		lpfn = (0x100000000ULL - PAGE_ALIGN(offset)) >> PAGE_SHIFT;
	पूर्ण

	r = amdgpu_cs_find_mapping(p, addr, &bo, &mapping);
	अगर (r) अणु
		DRM_ERROR("Can't find BO for addr 0x%010Lx %d %d %d %d\n",
			  addr, lo, hi, size, index);
		वापस r;
	पूर्ण

	क्रम (i = 0; i < bo->placement.num_placement; ++i) अणु
		bo->placements[i].fpfn = max(bo->placements[i].fpfn, fpfn);
		bo->placements[i].lpfn = bo->placements[i].lpfn ?
			min(bo->placements[i].lpfn, lpfn) : lpfn;
	पूर्ण
	वापस tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
पूर्ण


/**
 * amdgpu_vce_cs_reloc - command submission relocation
 *
 * @p: parser context
 * @ib_idx: indirect buffer to use
 * @lo: address of lower dword
 * @hi: address of higher dword
 * @size: minimum size
 * @index: bs/fb index
 *
 * Patch relocation inside command stream with real buffer address
 */
अटल पूर्णांक amdgpu_vce_cs_reloc(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx,
			       पूर्णांक lo, पूर्णांक hi, अचिन्हित size, uपूर्णांक32_t index)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक64_t addr;
	पूर्णांक r;

	अगर (index == 0xffffffff)
		index = 0;

	addr = ((uपूर्णांक64_t)amdgpu_get_ib_value(p, ib_idx, lo)) |
	       ((uपूर्णांक64_t)amdgpu_get_ib_value(p, ib_idx, hi)) << 32;
	addr += ((uपूर्णांक64_t)size) * ((uपूर्णांक64_t)index);

	r = amdgpu_cs_find_mapping(p, addr, &bo, &mapping);
	अगर (r) अणु
		DRM_ERROR("Can't find BO for addr 0x%010Lx %d %d %d %d\n",
			  addr, lo, hi, size, index);
		वापस r;
	पूर्ण

	अगर ((addr + (uपूर्णांक64_t)size) >
	    (mapping->last + 1) * AMDGPU_GPU_PAGE_SIZE) अणु
		DRM_ERROR("BO too small for addr 0x%010Lx %d %d\n",
			  addr, lo, hi);
		वापस -EINVAL;
	पूर्ण

	addr -= mapping->start * AMDGPU_GPU_PAGE_SIZE;
	addr += amdgpu_bo_gpu_offset(bo);
	addr -= ((uपूर्णांक64_t)size) * ((uपूर्णांक64_t)index);

	amdgpu_set_ib_value(p, ib_idx, lo, lower_32_bits(addr));
	amdgpu_set_ib_value(p, ib_idx, hi, upper_32_bits(addr));

	वापस 0;
पूर्ण

/**
 * amdgpu_vce_validate_handle - validate stream handle
 *
 * @p: parser context
 * @handle: handle to validate
 * @allocated: allocated a new handle?
 *
 * Validates the handle and वापस the found session index or -EINVAL
 * we we करोn't have another मुक्त session index.
 */
अटल पूर्णांक amdgpu_vce_validate_handle(काष्ठा amdgpu_cs_parser *p,
				      uपूर्णांक32_t handle, uपूर्णांक32_t *allocated)
अणु
	अचिन्हित i;

	/* validate the handle */
	क्रम (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) अणु
		अगर (atomic_पढ़ो(&p->adev->vce.handles[i]) == handle) अणु
			अगर (p->adev->vce.filp[i] != p->filp) अणु
				DRM_ERROR("VCE handle collision detected!\n");
				वापस -EINVAL;
			पूर्ण
			वापस i;
		पूर्ण
	पूर्ण

	/* handle not found try to alloc a new one */
	क्रम (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i) अणु
		अगर (!atomic_cmpxchg(&p->adev->vce.handles[i], 0, handle)) अणु
			p->adev->vce.filp[i] = p->filp;
			p->adev->vce.img_size[i] = 0;
			*allocated |= 1 << i;
			वापस i;
		पूर्ण
	पूर्ण

	DRM_ERROR("No more free VCE handles!\n");
	वापस -EINVAL;
पूर्ण

/**
 * amdgpu_vce_cs_parse - parse and validate the command stream
 *
 * @p: parser context
 * @ib_idx: indirect buffer to use
 */
पूर्णांक amdgpu_vce_ring_parse_cs(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx)
अणु
	काष्ठा amdgpu_ib *ib = &p->job->ibs[ib_idx];
	अचिन्हित fb_idx = 0, bs_idx = 0;
	पूर्णांक session_idx = -1;
	uपूर्णांक32_t destroyed = 0;
	uपूर्णांक32_t created = 0;
	uपूर्णांक32_t allocated = 0;
	uपूर्णांक32_t पंचांगp, handle = 0;
	uपूर्णांक32_t *size = &पंचांगp;
	अचिन्हित idx;
	पूर्णांक i, r = 0;

	p->job->vm = शून्य;
	ib->gpu_addr = amdgpu_sa_bo_gpu_addr(ib->sa_bo);

	क्रम (idx = 0; idx < ib->length_dw;) अणु
		uपूर्णांक32_t len = amdgpu_get_ib_value(p, ib_idx, idx);
		uपूर्णांक32_t cmd = amdgpu_get_ib_value(p, ib_idx, idx + 1);

		अगर ((len < 8) || (len & 3)) अणु
			DRM_ERROR("invalid VCE command length (%d)!\n", len);
			r = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (cmd) अणु
		हाल 0x00000002: /* task info */
			fb_idx = amdgpu_get_ib_value(p, ib_idx, idx + 6);
			bs_idx = amdgpu_get_ib_value(p, ib_idx, idx + 7);
			अवरोध;

		हाल 0x03000001: /* encode */
			r = amdgpu_vce_validate_bo(p, ib_idx, idx + 10,
						   idx + 9, 0, 0);
			अगर (r)
				जाओ out;

			r = amdgpu_vce_validate_bo(p, ib_idx, idx + 12,
						   idx + 11, 0, 0);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x05000001: /* context buffer */
			r = amdgpu_vce_validate_bo(p, ib_idx, idx + 3,
						   idx + 2, 0, 0);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x05000004: /* video bitstream buffer */
			पंचांगp = amdgpu_get_ib_value(p, ib_idx, idx + 4);
			r = amdgpu_vce_validate_bo(p, ib_idx, idx + 3, idx + 2,
						   पंचांगp, bs_idx);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x05000005: /* feedback buffer */
			r = amdgpu_vce_validate_bo(p, ib_idx, idx + 3, idx + 2,
						   4096, fb_idx);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x0500000d: /* MV buffer */
			r = amdgpu_vce_validate_bo(p, ib_idx, idx + 3,
							idx + 2, 0, 0);
			अगर (r)
				जाओ out;

			r = amdgpu_vce_validate_bo(p, ib_idx, idx + 8,
							idx + 7, 0, 0);
			अगर (r)
				जाओ out;
			अवरोध;
		पूर्ण

		idx += len / 4;
	पूर्ण

	क्रम (idx = 0; idx < ib->length_dw;) अणु
		uपूर्णांक32_t len = amdgpu_get_ib_value(p, ib_idx, idx);
		uपूर्णांक32_t cmd = amdgpu_get_ib_value(p, ib_idx, idx + 1);

		चयन (cmd) अणु
		हाल 0x00000001: /* session */
			handle = amdgpu_get_ib_value(p, ib_idx, idx + 2);
			session_idx = amdgpu_vce_validate_handle(p, handle,
								 &allocated);
			अगर (session_idx < 0) अणु
				r = session_idx;
				जाओ out;
			पूर्ण
			size = &p->adev->vce.img_size[session_idx];
			अवरोध;

		हाल 0x00000002: /* task info */
			fb_idx = amdgpu_get_ib_value(p, ib_idx, idx + 6);
			bs_idx = amdgpu_get_ib_value(p, ib_idx, idx + 7);
			अवरोध;

		हाल 0x01000001: /* create */
			created |= 1 << session_idx;
			अगर (destroyed & (1 << session_idx)) अणु
				destroyed &= ~(1 << session_idx);
				allocated |= 1 << session_idx;

			पूर्ण अन्यथा अगर (!(allocated & (1 << session_idx))) अणु
				DRM_ERROR("Handle already in use!\n");
				r = -EINVAL;
				जाओ out;
			पूर्ण

			*size = amdgpu_get_ib_value(p, ib_idx, idx + 8) *
				amdgpu_get_ib_value(p, ib_idx, idx + 10) *
				8 * 3 / 2;
			अवरोध;

		हाल 0x04000001: /* config extension */
		हाल 0x04000002: /* pic control */
		हाल 0x04000005: /* rate control */
		हाल 0x04000007: /* motion estimation */
		हाल 0x04000008: /* rकरो */
		हाल 0x04000009: /* vui */
		हाल 0x05000002: /* auxiliary buffer */
		हाल 0x05000009: /* घड़ी table */
			अवरोध;

		हाल 0x0500000c: /* hw config */
			चयन (p->adev->asic_type) अणु
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
			हाल CHIP_KAVERI:
			हाल CHIP_MULLINS:
#पूर्ण_अगर
			हाल CHIP_CARRIZO:
				अवरोध;
			शेष:
				r = -EINVAL;
				जाओ out;
			पूर्ण
			अवरोध;

		हाल 0x03000001: /* encode */
			r = amdgpu_vce_cs_reloc(p, ib_idx, idx + 10, idx + 9,
						*size, 0);
			अगर (r)
				जाओ out;

			r = amdgpu_vce_cs_reloc(p, ib_idx, idx + 12, idx + 11,
						*size / 3, 0);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x02000001: /* destroy */
			destroyed |= 1 << session_idx;
			अवरोध;

		हाल 0x05000001: /* context buffer */
			r = amdgpu_vce_cs_reloc(p, ib_idx, idx + 3, idx + 2,
						*size * 2, 0);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x05000004: /* video bitstream buffer */
			पंचांगp = amdgpu_get_ib_value(p, ib_idx, idx + 4);
			r = amdgpu_vce_cs_reloc(p, ib_idx, idx + 3, idx + 2,
						पंचांगp, bs_idx);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x05000005: /* feedback buffer */
			r = amdgpu_vce_cs_reloc(p, ib_idx, idx + 3, idx + 2,
						4096, fb_idx);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x0500000d: /* MV buffer */
			r = amdgpu_vce_cs_reloc(p, ib_idx, idx + 3,
							idx + 2, *size, 0);
			अगर (r)
				जाओ out;

			r = amdgpu_vce_cs_reloc(p, ib_idx, idx + 8,
							idx + 7, *size / 12, 0);
			अगर (r)
				जाओ out;
			अवरोध;

		शेष:
			DRM_ERROR("invalid VCE command (0x%x)!\n", cmd);
			r = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (session_idx == -1) अणु
			DRM_ERROR("no session command at start of IB\n");
			r = -EINVAL;
			जाओ out;
		पूर्ण

		idx += len / 4;
	पूर्ण

	अगर (allocated & ~created) अणु
		DRM_ERROR("New session without create command!\n");
		r = -ENOENT;
	पूर्ण

out:
	अगर (!r) अणु
		/* No error, मुक्त all destroyed handle slots */
		पंचांगp = destroyed;
	पूर्ण अन्यथा अणु
		/* Error during parsing, मुक्त all allocated handle slots */
		पंचांगp = allocated;
	पूर्ण

	क्रम (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i)
		अगर (पंचांगp & (1 << i))
			atomic_set(&p->adev->vce.handles[i], 0);

	वापस r;
पूर्ण

/**
 * amdgpu_vce_cs_parse_vm - parse the command stream in VM mode
 *
 * @p: parser context
 * @ib_idx: indirect buffer to use
 */
पूर्णांक amdgpu_vce_ring_parse_cs_vm(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx)
अणु
	काष्ठा amdgpu_ib *ib = &p->job->ibs[ib_idx];
	पूर्णांक session_idx = -1;
	uपूर्णांक32_t destroyed = 0;
	uपूर्णांक32_t created = 0;
	uपूर्णांक32_t allocated = 0;
	uपूर्णांक32_t पंचांगp, handle = 0;
	पूर्णांक i, r = 0, idx = 0;

	जबतक (idx < ib->length_dw) अणु
		uपूर्णांक32_t len = amdgpu_get_ib_value(p, ib_idx, idx);
		uपूर्णांक32_t cmd = amdgpu_get_ib_value(p, ib_idx, idx + 1);

		अगर ((len < 8) || (len & 3)) अणु
			DRM_ERROR("invalid VCE command length (%d)!\n", len);
			r = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (cmd) अणु
		हाल 0x00000001: /* session */
			handle = amdgpu_get_ib_value(p, ib_idx, idx + 2);
			session_idx = amdgpu_vce_validate_handle(p, handle,
								 &allocated);
			अगर (session_idx < 0) अणु
				r = session_idx;
				जाओ out;
			पूर्ण
			अवरोध;

		हाल 0x01000001: /* create */
			created |= 1 << session_idx;
			अगर (destroyed & (1 << session_idx)) अणु
				destroyed &= ~(1 << session_idx);
				allocated |= 1 << session_idx;

			पूर्ण अन्यथा अगर (!(allocated & (1 << session_idx))) अणु
				DRM_ERROR("Handle already in use!\n");
				r = -EINVAL;
				जाओ out;
			पूर्ण

			अवरोध;

		हाल 0x02000001: /* destroy */
			destroyed |= 1 << session_idx;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (session_idx == -1) अणु
			DRM_ERROR("no session command at start of IB\n");
			r = -EINVAL;
			जाओ out;
		पूर्ण

		idx += len / 4;
	पूर्ण

	अगर (allocated & ~created) अणु
		DRM_ERROR("New session without create command!\n");
		r = -ENOENT;
	पूर्ण

out:
	अगर (!r) अणु
		/* No error, मुक्त all destroyed handle slots */
		पंचांगp = destroyed;
		amdgpu_ib_मुक्त(p->adev, ib, शून्य);
	पूर्ण अन्यथा अणु
		/* Error during parsing, मुक्त all allocated handle slots */
		पंचांगp = allocated;
	पूर्ण

	क्रम (i = 0; i < AMDGPU_MAX_VCE_HANDLES; ++i)
		अगर (पंचांगp & (1 << i))
			atomic_set(&p->adev->vce.handles[i], 0);

	वापस r;
पूर्ण

/**
 * amdgpu_vce_ring_emit_ib - execute indirect buffer
 *
 * @ring: engine to use
 * @job: job to retrieve vmid from
 * @ib: the IB to execute
 * @flags: unused
 *
 */
व्योम amdgpu_vce_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				काष्ठा amdgpu_job *job,
				काष्ठा amdgpu_ib *ib,
				uपूर्णांक32_t flags)
अणु
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_IB);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

/**
 * amdgpu_vce_ring_emit_fence - add a fence command to the ring
 *
 * @ring: engine to use
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 */
व्योम amdgpu_vce_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				अचिन्हित flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, VCE_CMD_FENCE);
	amdgpu_ring_ग_लिखो(ring, addr);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_TRAP);
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_END);
पूर्ण

/**
 * amdgpu_vce_ring_test_ring - test अगर VCE ring is working
 *
 * @ring: the engine to test on
 *
 */
पूर्णांक amdgpu_vce_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t rptr;
	अचिन्हित i;
	पूर्णांक r, समयout = adev->usec_समयout;

	/* skip ring test क्रम sriov*/
	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	r = amdgpu_ring_alloc(ring, 16);
	अगर (r)
		वापस r;

	rptr = amdgpu_ring_get_rptr(ring);

	amdgpu_ring_ग_लिखो(ring, VCE_CMD_END);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < समयout; i++) अणु
		अगर (amdgpu_ring_get_rptr(ring) != rptr)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

/**
 * amdgpu_vce_ring_test_ib - test अगर VCE IBs are working
 *
 * @ring: the engine to test on
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 */
पूर्णांक amdgpu_vce_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा amdgpu_bo *bo = शून्य;
	दीर्घ r;

	/* skip vce ring1/2 ib test क्रम now, since it's not reliable */
	अगर (ring != &ring->adev->vce.ring[0])
		वापस 0;

	r = amdgpu_bo_create_reserved(ring->adev, 512, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &bo, शून्य, शून्य);
	अगर (r)
		वापस r;

	r = amdgpu_vce_get_create_msg(ring, 1, bo, शून्य);
	अगर (r)
		जाओ error;

	r = amdgpu_vce_get_destroy_msg(ring, 1, true, &fence);
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
