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

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "sid.h"

/* 1 second समयout */
#घोषणा VCE_IDLE_TIMEOUT_MS	1000

/* Firmware Names */
#घोषणा FIRMWARE_TAHITI	"radeon/TAHITI_vce.bin"
#घोषणा FIRMWARE_BONAIRE	"radeon/BONAIRE_vce.bin"

MODULE_FIRMWARE(FIRMWARE_TAHITI);
MODULE_FIRMWARE(FIRMWARE_BONAIRE);

अटल व्योम radeon_vce_idle_work_handler(काष्ठा work_काष्ठा *work);

/**
 * radeon_vce_init - allocate memory, load vce firmware
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * First step to get VCE online, allocate memory and load the firmware
 */
पूर्णांक radeon_vce_init(काष्ठा radeon_device *rdev)
अणु
	अटल स्थिर अक्षर *fw_version = "[ATI LIB=VCEFW,";
	अटल स्थिर अक्षर *fb_version = "[ATI LIB=VCEFWSTATS,";
	अचिन्हित दीर्घ size;
	स्थिर अक्षर *fw_name, *c;
	uपूर्णांक8_t start, mid, end;
	पूर्णांक i, r;

	INIT_DELAYED_WORK(&rdev->vce.idle_work, radeon_vce_idle_work_handler);

	चयन (rdev->family) अणु
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
	हाल CHIP_ARUBA:
		fw_name = FIRMWARE_TAHITI;
		अवरोध;

	हाल CHIP_BONAIRE:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_HAWAII:
	हाल CHIP_MULLINS:
		fw_name = FIRMWARE_BONAIRE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	r = request_firmware(&rdev->vce_fw, fw_name, rdev->dev);
	अगर (r) अणु
		dev_err(rdev->dev, "radeon_vce: Can't load firmware \"%s\"\n",
			fw_name);
		वापस r;
	पूर्ण

	/* search क्रम firmware version */

	size = rdev->vce_fw->size - म_माप(fw_version) - 9;
	c = rdev->vce_fw->data;
	क्रम (;size > 0; --size, ++c)
		अगर (म_भेदन(c, fw_version, म_माप(fw_version)) == 0)
			अवरोध;

	अगर (size == 0)
		वापस -EINVAL;

	c += म_माप(fw_version);
	अगर (माला_पूछो(c, "%2hhd.%2hhd.%2hhd]", &start, &mid, &end) != 3)
		वापस -EINVAL;

	/* search क्रम feedback version */

	size = rdev->vce_fw->size - म_माप(fb_version) - 3;
	c = rdev->vce_fw->data;
	क्रम (;size > 0; --size, ++c)
		अगर (म_भेदन(c, fb_version, म_माप(fb_version)) == 0)
			अवरोध;

	अगर (size == 0)
		वापस -EINVAL;

	c += म_माप(fb_version);
	अगर (माला_पूछो(c, "%2u]", &rdev->vce.fb_version) != 1)
		वापस -EINVAL;

	DRM_INFO("Found VCE firmware/feedback version %d.%d.%d / %d!\n",
		 start, mid, end, rdev->vce.fb_version);

	rdev->vce.fw_version = (start << 24) | (mid << 16) | (end << 8);

	/* we can only work with this fw version क्रम now */
	अगर ((rdev->vce.fw_version != ((40 << 24) | (2 << 16) | (2 << 8))) &&
	    (rdev->vce.fw_version != ((50 << 24) | (0 << 16) | (1 << 8))) &&
	    (rdev->vce.fw_version != ((50 << 24) | (1 << 16) | (2 << 8))))
		वापस -EINVAL;

	/* allocate firmware, stack and heap BO */

	अगर (rdev->family < CHIP_BONAIRE)
		size = vce_v1_0_bo_size(rdev);
	अन्यथा
		size = vce_v2_0_bo_size(rdev);
	r = radeon_bo_create(rdev, size, PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, शून्य, शून्य,
			     &rdev->vce.vcpu_bo);
	अगर (r) अणु
		dev_err(rdev->dev, "(%d) failed to allocate VCE bo\n", r);
		वापस r;
	पूर्ण

	r = radeon_bo_reserve(rdev->vce.vcpu_bo, false);
	अगर (r) अणु
		radeon_bo_unref(&rdev->vce.vcpu_bo);
		dev_err(rdev->dev, "(%d) failed to reserve VCE bo\n", r);
		वापस r;
	पूर्ण

	r = radeon_bo_pin(rdev->vce.vcpu_bo, RADEON_GEM_DOMAIN_VRAM,
			  &rdev->vce.gpu_addr);
	radeon_bo_unreserve(rdev->vce.vcpu_bo);
	अगर (r) अणु
		radeon_bo_unref(&rdev->vce.vcpu_bo);
		dev_err(rdev->dev, "(%d) VCE bo pin failed\n", r);
		वापस r;
	पूर्ण

	क्रम (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) अणु
		atomic_set(&rdev->vce.handles[i], 0);
		rdev->vce.filp[i] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * radeon_vce_fini - मुक्त memory
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Last step on VCE tearकरोwn, मुक्त firmware memory
 */
व्योम radeon_vce_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->vce.vcpu_bo == शून्य)
		वापस;

	radeon_bo_unref(&rdev->vce.vcpu_bo);

	release_firmware(rdev->vce_fw);
पूर्ण

/**
 * radeon_vce_suspend - unpin VCE fw memory
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 */
पूर्णांक radeon_vce_suspend(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (rdev->vce.vcpu_bo == शून्य)
		वापस 0;

	क्रम (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i)
		अगर (atomic_पढ़ो(&rdev->vce.handles[i]))
			अवरोध;

	अगर (i == RADEON_MAX_VCE_HANDLES)
		वापस 0;

	/* TODO: suspending running encoding sessions isn't supported */
	वापस -EINVAL;
पूर्ण

/**
 * radeon_vce_resume - pin VCE fw memory
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 */
पूर्णांक radeon_vce_resume(काष्ठा radeon_device *rdev)
अणु
	व्योम *cpu_addr;
	पूर्णांक r;

	अगर (rdev->vce.vcpu_bo == शून्य)
		वापस -EINVAL;

	r = radeon_bo_reserve(rdev->vce.vcpu_bo, false);
	अगर (r) अणु
		dev_err(rdev->dev, "(%d) failed to reserve VCE bo\n", r);
		वापस r;
	पूर्ण

	r = radeon_bo_kmap(rdev->vce.vcpu_bo, &cpu_addr);
	अगर (r) अणु
		radeon_bo_unreserve(rdev->vce.vcpu_bo);
		dev_err(rdev->dev, "(%d) VCE map failed\n", r);
		वापस r;
	पूर्ण

	स_रखो(cpu_addr, 0, radeon_bo_size(rdev->vce.vcpu_bo));
	अगर (rdev->family < CHIP_BONAIRE)
		r = vce_v1_0_load_fw(rdev, cpu_addr);
	अन्यथा
		स_नकल(cpu_addr, rdev->vce_fw->data, rdev->vce_fw->size);

	radeon_bo_kunmap(rdev->vce.vcpu_bo);

	radeon_bo_unreserve(rdev->vce.vcpu_bo);

	वापस r;
पूर्ण

/**
 * radeon_vce_idle_work_handler - घातer off VCE
 *
 * @work: poपूर्णांकer to work काष्ठाure
 *
 * घातer of VCE when it's not used any more
 */
अटल व्योम radeon_vce_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_device *rdev =
		container_of(work, काष्ठा radeon_device, vce.idle_work.work);

	अगर ((radeon_fence_count_emitted(rdev, TN_RING_TYPE_VCE1_INDEX) == 0) &&
	    (radeon_fence_count_emitted(rdev, TN_RING_TYPE_VCE2_INDEX) == 0)) अणु
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			radeon_dpm_enable_vce(rdev, false);
		पूर्ण अन्यथा अणु
			radeon_set_vce_घड़ीs(rdev, 0, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&rdev->vce.idle_work,
				      msecs_to_jअगरfies(VCE_IDLE_TIMEOUT_MS));
	पूर्ण
पूर्ण

/**
 * radeon_vce_note_usage - घातer up VCE
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Make sure VCE is घातerd up when we want to use it
 */
व्योम radeon_vce_note_usage(काष्ठा radeon_device *rdev)
अणु
	bool streams_changed = false;
	bool set_घड़ीs = !cancel_delayed_work_sync(&rdev->vce.idle_work);
	set_घड़ीs &= schedule_delayed_work(&rdev->vce.idle_work,
					    msecs_to_jअगरfies(VCE_IDLE_TIMEOUT_MS));

	अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
		/* XXX figure out अगर the streams changed */
		streams_changed = false;
	पूर्ण

	अगर (set_घड़ीs || streams_changed) अणु
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			radeon_dpm_enable_vce(rdev, true);
		पूर्ण अन्यथा अणु
			radeon_set_vce_घड़ीs(rdev, 53300, 40000);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * radeon_vce_मुक्त_handles - मुक्त still खोलो VCE handles
 *
 * @rdev: radeon_device poपूर्णांकer
 * @filp: drm file poपूर्णांकer
 *
 * Close all VCE handles still खोलो by this file poपूर्णांकer
 */
व्योम radeon_vce_मुक्त_handles(काष्ठा radeon_device *rdev, काष्ठा drm_file *filp)
अणु
	पूर्णांक i, r;
	क्रम (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) अणु
		uपूर्णांक32_t handle = atomic_पढ़ो(&rdev->vce.handles[i]);
		अगर (!handle || rdev->vce.filp[i] != filp)
			जारी;

		radeon_vce_note_usage(rdev);

		r = radeon_vce_get_destroy_msg(rdev, TN_RING_TYPE_VCE1_INDEX,
					       handle, शून्य);
		अगर (r)
			DRM_ERROR("Error destroying VCE handle (%d)!\n", r);

		rdev->vce.filp[i] = शून्य;
		atomic_set(&rdev->vce.handles[i], 0);
	पूर्ण
पूर्ण

/**
 * radeon_vce_get_create_msg - generate a VCE create msg
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring we should submit the msg to
 * @handle: VCE session handle to use
 * @fence: optional fence to वापस
 *
 * Open up a stream क्रम HW test
 */
पूर्णांक radeon_vce_get_create_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			      uपूर्णांक32_t handle, काष्ठा radeon_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 1024;
	काष्ठा radeon_ib ib;
	uपूर्णांक64_t dummy;
	पूर्णांक i, r;

	r = radeon_ib_get(rdev, ring, &ib, शून्य, ib_size_dw * 4);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		वापस r;
	पूर्ण

	dummy = ib.gpu_addr + 1024;

	/* stitch together an VCE create msg */
	ib.length_dw = 0;
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x0000000c); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000001); /* session cmd */
	ib.ptr[ib.length_dw++] = cpu_to_le32(handle);

	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000030); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x01000001); /* create cmd */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000000);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000042);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x0000000a);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000001);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000080);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000060);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000100);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000100);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x0000000c);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000000);

	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000014); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x05000005); /* feedback buffer */
	ib.ptr[ib.length_dw++] = cpu_to_le32(upper_32_bits(dummy));
	ib.ptr[ib.length_dw++] = cpu_to_le32(dummy);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000001);

	क्रम (i = ib.length_dw; i < ib_size_dw; ++i)
		ib.ptr[i] = cpu_to_le32(0x0);

	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r)
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);


	अगर (fence)
		*fence = radeon_fence_ref(ib.fence);

	radeon_ib_मुक्त(rdev, &ib);

	वापस r;
पूर्ण

/**
 * radeon_vce_get_destroy_msg - generate a VCE destroy msg
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring we should submit the msg to
 * @handle: VCE session handle to use
 * @fence: optional fence to वापस
 *
 * Close up a stream क्रम HW test or अगर userspace failed to करो so
 */
पूर्णांक radeon_vce_get_destroy_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			       uपूर्णांक32_t handle, काष्ठा radeon_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 1024;
	काष्ठा radeon_ib ib;
	uपूर्णांक64_t dummy;
	पूर्णांक i, r;

	r = radeon_ib_get(rdev, ring, &ib, शून्य, ib_size_dw * 4);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		वापस r;
	पूर्ण

	dummy = ib.gpu_addr + 1024;

	/* stitch together an VCE destroy msg */
	ib.length_dw = 0;
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x0000000c); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000001); /* session cmd */
	ib.ptr[ib.length_dw++] = cpu_to_le32(handle);

	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000014); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x05000005); /* feedback buffer */
	ib.ptr[ib.length_dw++] = cpu_to_le32(upper_32_bits(dummy));
	ib.ptr[ib.length_dw++] = cpu_to_le32(dummy);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000001);

	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000008); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x02000001); /* destroy cmd */

	क्रम (i = ib.length_dw; i < ib_size_dw; ++i)
		ib.ptr[i] = cpu_to_le32(0x0);

	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
	पूर्ण

	अगर (fence)
		*fence = radeon_fence_ref(ib.fence);

	radeon_ib_मुक्त(rdev, &ib);

	वापस r;
पूर्ण

/**
 * radeon_vce_cs_reloc - command submission relocation
 *
 * @p: parser context
 * @lo: address of lower dword
 * @hi: address of higher dword
 * @size: size of checker क्रम relocation buffer
 *
 * Patch relocation inside command stream with real buffer address
 */
पूर्णांक radeon_vce_cs_reloc(काष्ठा radeon_cs_parser *p, पूर्णांक lo, पूर्णांक hi,
			अचिन्हित size)
अणु
	काष्ठा radeon_cs_chunk *relocs_chunk;
	काष्ठा radeon_bo_list *reloc;
	uपूर्णांक64_t start, end, offset;
	अचिन्हित idx;

	relocs_chunk = p->chunk_relocs;
	offset = radeon_get_ib_value(p, lo);
	idx = radeon_get_ib_value(p, hi);

	अगर (idx >= relocs_chunk->length_dw) अणु
		DRM_ERROR("Relocs at %d after relocations chunk end %d !\n",
			  idx, relocs_chunk->length_dw);
		वापस -EINVAL;
	पूर्ण

	reloc = &p->relocs[(idx / 4)];
	start = reloc->gpu_offset;
	end = start + radeon_bo_size(reloc->robj);
	start += offset;

	p->ib.ptr[lo] = start & 0xFFFFFFFF;
	p->ib.ptr[hi] = start >> 32;

	अगर (end <= start) अणु
		DRM_ERROR("invalid reloc offset %llX!\n", offset);
		वापस -EINVAL;
	पूर्ण
	अगर ((end - start) < size) अणु
		DRM_ERROR("buffer to small (%d / %d)!\n",
			(अचिन्हित)(end - start), size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * radeon_vce_validate_handle - validate stream handle
 *
 * @p: parser context
 * @handle: handle to validate
 * @allocated: allocated a new handle?
 *
 * Validates the handle and वापस the found session index or -EINVAL
 * we we करोn't have another मुक्त session index.
 */
अटल पूर्णांक radeon_vce_validate_handle(काष्ठा radeon_cs_parser *p,
				      uपूर्णांक32_t handle, bool *allocated)
अणु
	अचिन्हित i;

	*allocated = false;

	/* validate the handle */
	क्रम (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) अणु
		अगर (atomic_पढ़ो(&p->rdev->vce.handles[i]) == handle) अणु
			अगर (p->rdev->vce.filp[i] != p->filp) अणु
				DRM_ERROR("VCE handle collision detected!\n");
				वापस -EINVAL;
			पूर्ण
			वापस i;
		पूर्ण
	पूर्ण

	/* handle not found try to alloc a new one */
	क्रम (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) अणु
		अगर (!atomic_cmpxchg(&p->rdev->vce.handles[i], 0, handle)) अणु
			p->rdev->vce.filp[i] = p->filp;
			p->rdev->vce.img_size[i] = 0;
			*allocated = true;
			वापस i;
		पूर्ण
	पूर्ण

	DRM_ERROR("No more free VCE handles!\n");
	वापस -EINVAL;
पूर्ण

/**
 * radeon_vce_cs_parse - parse and validate the command stream
 *
 * @p: parser context
 *
 */
पूर्णांक radeon_vce_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	पूर्णांक session_idx = -1;
	bool destroyed = false, created = false, allocated = false;
	uपूर्णांक32_t पंचांगp, handle = 0;
	uपूर्णांक32_t *size = &पंचांगp;
	पूर्णांक i, r = 0;

	जबतक (p->idx < p->chunk_ib->length_dw) अणु
		uपूर्णांक32_t len = radeon_get_ib_value(p, p->idx);
		uपूर्णांक32_t cmd = radeon_get_ib_value(p, p->idx + 1);

		अगर ((len < 8) || (len & 3)) अणु
			DRM_ERROR("invalid VCE command length (%d)!\n", len);
			r = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (destroyed) अणु
			DRM_ERROR("No other command allowed after destroy!\n");
			r = -EINVAL;
			जाओ out;
		पूर्ण

		चयन (cmd) अणु
		हाल 0x00000001: // session
			handle = radeon_get_ib_value(p, p->idx + 2);
			session_idx = radeon_vce_validate_handle(p, handle,
								 &allocated);
			अगर (session_idx < 0)
				वापस session_idx;
			size = &p->rdev->vce.img_size[session_idx];
			अवरोध;

		हाल 0x00000002: // task info
			अवरोध;

		हाल 0x01000001: // create
			created = true;
			अगर (!allocated) अणु
				DRM_ERROR("Handle already in use!\n");
				r = -EINVAL;
				जाओ out;
			पूर्ण

			*size = radeon_get_ib_value(p, p->idx + 8) *
				radeon_get_ib_value(p, p->idx + 10) *
				8 * 3 / 2;
			अवरोध;

		हाल 0x04000001: // config extension
		हाल 0x04000002: // pic control
		हाल 0x04000005: // rate control
		हाल 0x04000007: // motion estimation
		हाल 0x04000008: // rकरो
		हाल 0x04000009: // vui
			अवरोध;

		हाल 0x03000001: // encode
			r = radeon_vce_cs_reloc(p, p->idx + 10, p->idx + 9,
						*size);
			अगर (r)
				जाओ out;

			r = radeon_vce_cs_reloc(p, p->idx + 12, p->idx + 11,
						*size / 3);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x02000001: // destroy
			destroyed = true;
			अवरोध;

		हाल 0x05000001: // context buffer
			r = radeon_vce_cs_reloc(p, p->idx + 3, p->idx + 2,
						*size * 2);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x05000004: // video bitstream buffer
			पंचांगp = radeon_get_ib_value(p, p->idx + 4);
			r = radeon_vce_cs_reloc(p, p->idx + 3, p->idx + 2,
						पंचांगp);
			अगर (r)
				जाओ out;
			अवरोध;

		हाल 0x05000005: // feedback buffer
			r = radeon_vce_cs_reloc(p, p->idx + 3, p->idx + 2,
						4096);
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

		p->idx += len / 4;
	पूर्ण

	अगर (allocated && !created) अणु
		DRM_ERROR("New session without create command!\n");
		r = -ENOENT;
	पूर्ण

out:
	अगर ((!r && destroyed) || (r && allocated)) अणु
		/*
		 * IB contains a destroy msg or we have allocated an
		 * handle and got an error, anyway मुक्त the handle
		 */
		क्रम (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i)
			atomic_cmpxchg(&p->rdev->vce.handles[i], handle, 0);
	पूर्ण

	वापस r;
पूर्ण

/**
 * radeon_vce_semaphore_emit - emit a semaphore command
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: engine to use
 * @semaphore: address of semaphore
 * @emit_रुको: true=emit रुको, false=emit संकेत
 *
 */
bool radeon_vce_semaphore_emit(काष्ठा radeon_device *rdev,
			       काष्ठा radeon_ring *ring,
			       काष्ठा radeon_semaphore *semaphore,
			       bool emit_रुको)
अणु
	uपूर्णांक64_t addr = semaphore->gpu_addr;

	radeon_ring_ग_लिखो(ring, cpu_to_le32(VCE_CMD_SEMAPHORE));
	radeon_ring_ग_लिखो(ring, cpu_to_le32((addr >> 3) & 0x000FFFFF));
	radeon_ring_ग_लिखो(ring, cpu_to_le32((addr >> 23) & 0x000FFFFF));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(0x01003000 | (emit_रुको ? 1 : 0)));
	अगर (!emit_रुको)
		radeon_ring_ग_लिखो(ring, cpu_to_le32(VCE_CMD_END));

	वापस true;
पूर्ण

/**
 * radeon_vce_ib_execute - execute indirect buffer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: the IB to execute
 *
 */
व्योम radeon_vce_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	radeon_ring_ग_लिखो(ring, cpu_to_le32(VCE_CMD_IB));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(ib->gpu_addr));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(upper_32_bits(ib->gpu_addr)));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(ib->length_dw));
पूर्ण

/**
 * radeon_vce_fence_emit - add a fence command to the ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: the fence
 *
 */
व्योम radeon_vce_fence_emit(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	uपूर्णांक64_t addr = rdev->fence_drv[fence->ring].gpu_addr;

	radeon_ring_ग_लिखो(ring, cpu_to_le32(VCE_CMD_FENCE));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(addr));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(upper_32_bits(addr)));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(fence->seq));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(VCE_CMD_TRAP));
	radeon_ring_ग_लिखो(ring, cpu_to_le32(VCE_CMD_END));
पूर्ण

/**
 * radeon_vce_ring_test - test अगर VCE ring is working
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: the engine to test on
 *
 */
पूर्णांक radeon_vce_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	uपूर्णांक32_t rptr = vce_v1_0_get_rptr(rdev, ring);
	अचिन्हित i;
	पूर्णांक r;

	r = radeon_ring_lock(rdev, ring, 16);
	अगर (r) अणु
		DRM_ERROR("radeon: vce failed to lock ring %d (%d).\n",
			  ring->idx, r);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, cpu_to_le32(VCE_CMD_END));
	radeon_ring_unlock_commit(rdev, ring, false);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (vce_v1_0_get_rptr(rdev, ring) != rptr)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ring test on %d succeeded in %d usecs\n",
			 ring->idx, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ring %d test failed\n",
			 ring->idx);
		r = -ETIMEDOUT;
	पूर्ण

	वापस r;
पूर्ण

/**
 * radeon_vce_ib_test - test अगर VCE IBs are working
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: the engine to test on
 *
 */
पूर्णांक radeon_vce_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	काष्ठा radeon_fence *fence = शून्य;
	पूर्णांक r;

	r = radeon_vce_get_create_msg(rdev, ring->idx, 1, शून्य);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get create msg (%d).\n", r);
		जाओ error;
	पूर्ण

	r = radeon_vce_get_destroy_msg(rdev, ring->idx, 1, &fence);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get destroy ib (%d).\n", r);
		जाओ error;
	पूर्ण

	r = radeon_fence_रुको_समयout(fence, false, usecs_to_jअगरfies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	अगर (r < 0) अणु
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
	पूर्ण अन्यथा अगर (r == 0) अणु
		DRM_ERROR("radeon: fence wait timed out.\n");
		r = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		DRM_INFO("ib test on ring %d succeeded\n", ring->idx);
		r = 0;
	पूर्ण
error:
	radeon_fence_unref(&fence);
	वापस r;
पूर्ण
