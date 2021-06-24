<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
/*
 * Authors:
 *    Christian Kथघnig <deathsimple@vodafone.de>
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश <drm/drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_uvd.h"
#समावेश "cikd.h"
#समावेश "uvd/uvd_4_2_d.h"

#समावेश "amdgpu_ras.h"

/* 1 second समयout */
#घोषणा UVD_IDLE_TIMEOUT	msecs_to_jअगरfies(1000)

/* Firmware versions क्रम VI */
#घोषणा FW_1_65_10	((1 << 24) | (65 << 16) | (10 << 8))
#घोषणा FW_1_87_11	((1 << 24) | (87 << 16) | (11 << 8))
#घोषणा FW_1_87_12	((1 << 24) | (87 << 16) | (12 << 8))
#घोषणा FW_1_37_15	((1 << 24) | (37 << 16) | (15 << 8))

/* Polaris10/11 firmware version */
#घोषणा FW_1_66_16	((1 << 24) | (66 << 16) | (16 << 8))

/* Firmware Names */
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
#घोषणा FIRMWARE_TAHITI		"amdgpu/tahiti_uvd.bin"
#घोषणा FIRMWARE_VERDE		"amdgpu/verde_uvd.bin"
#घोषणा FIRMWARE_PITCAIRN	"amdgpu/pitcairn_uvd.bin"
#घोषणा FIRMWARE_OLAND		"amdgpu/oland_uvd.bin"
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
#घोषणा FIRMWARE_BONAIRE	"amdgpu/bonaire_uvd.bin"
#घोषणा FIRMWARE_KABINI	"amdgpu/kabini_uvd.bin"
#घोषणा FIRMWARE_KAVERI	"amdgpu/kaveri_uvd.bin"
#घोषणा FIRMWARE_HAWAII	"amdgpu/hawaii_uvd.bin"
#घोषणा FIRMWARE_MULLINS	"amdgpu/mullins_uvd.bin"
#पूर्ण_अगर
#घोषणा FIRMWARE_TONGA		"amdgpu/tonga_uvd.bin"
#घोषणा FIRMWARE_CARRIZO	"amdgpu/carrizo_uvd.bin"
#घोषणा FIRMWARE_FIJI		"amdgpu/fiji_uvd.bin"
#घोषणा FIRMWARE_STONEY		"amdgpu/stoney_uvd.bin"
#घोषणा FIRMWARE_POLARIS10	"amdgpu/polaris10_uvd.bin"
#घोषणा FIRMWARE_POLARIS11	"amdgpu/polaris11_uvd.bin"
#घोषणा FIRMWARE_POLARIS12	"amdgpu/polaris12_uvd.bin"
#घोषणा FIRMWARE_VEGAM		"amdgpu/vegam_uvd.bin"

#घोषणा FIRMWARE_VEGA10		"amdgpu/vega10_uvd.bin"
#घोषणा FIRMWARE_VEGA12		"amdgpu/vega12_uvd.bin"
#घोषणा FIRMWARE_VEGA20		"amdgpu/vega20_uvd.bin"

/* These are common relative offsets क्रम all asics, from uvd_7_0_offset.h,  */
#घोषणा UVD_GPCOM_VCPU_CMD		0x03c3
#घोषणा UVD_GPCOM_VCPU_DATA0	0x03c4
#घोषणा UVD_GPCOM_VCPU_DATA1	0x03c5
#घोषणा UVD_NO_OP				0x03ff
#घोषणा UVD_BASE_SI				0x3800

/*
 * amdgpu_uvd_cs_ctx - Command submission parser context
 *
 * Used क्रम emulating भव memory support on UVD 4.2.
 */
काष्ठा amdgpu_uvd_cs_ctx अणु
	काष्ठा amdgpu_cs_parser *parser;
	अचिन्हित reg, count;
	अचिन्हित data0, data1;
	अचिन्हित idx;
	अचिन्हित ib_idx;

	/* करोes the IB has a msg command */
	bool has_msg_cmd;

	/* minimum buffer sizes */
	अचिन्हित *buf_sizes;
पूर्ण;

#अगर_घोषित CONFIG_DRM_AMDGPU_SI
MODULE_FIRMWARE(FIRMWARE_TAHITI);
MODULE_FIRMWARE(FIRMWARE_VERDE);
MODULE_FIRMWARE(FIRMWARE_PITCAIRN);
MODULE_FIRMWARE(FIRMWARE_OLAND);
#पूर्ण_अगर
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

अटल व्योम amdgpu_uvd_idle_work_handler(काष्ठा work_काष्ठा *work);

पूर्णांक amdgpu_uvd_sw_init(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित दीर्घ bo_size;
	स्थिर अक्षर *fw_name;
	स्थिर काष्ठा common_firmware_header *hdr;
	अचिन्हित family_id;
	पूर्णांक i, j, r;

	INIT_DELAYED_WORK(&adev->uvd.idle_work, amdgpu_uvd_idle_work_handler);

	चयन (adev->asic_type) अणु
#अगर_घोषित CONFIG_DRM_AMDGPU_SI
	हाल CHIP_TAHITI:
		fw_name = FIRMWARE_TAHITI;
		अवरोध;
	हाल CHIP_VERDE:
		fw_name = FIRMWARE_VERDE;
		अवरोध;
	हाल CHIP_PITCAIRN:
		fw_name = FIRMWARE_PITCAIRN;
		अवरोध;
	हाल CHIP_OLAND:
		fw_name = FIRMWARE_OLAND;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	हाल CHIP_BONAIRE:
		fw_name = FIRMWARE_BONAIRE;
		अवरोध;
	हाल CHIP_KABINI:
		fw_name = FIRMWARE_KABINI;
		अवरोध;
	हाल CHIP_KAVERI:
		fw_name = FIRMWARE_KAVERI;
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
	हाल CHIP_FIJI:
		fw_name = FIRMWARE_FIJI;
		अवरोध;
	हाल CHIP_CARRIZO:
		fw_name = FIRMWARE_CARRIZO;
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
	हाल CHIP_VEGA10:
		fw_name = FIRMWARE_VEGA10;
		अवरोध;
	हाल CHIP_VEGA12:
		fw_name = FIRMWARE_VEGA12;
		अवरोध;
	हाल CHIP_VEGAM:
		fw_name = FIRMWARE_VEGAM;
		अवरोध;
	हाल CHIP_VEGA20:
		fw_name = FIRMWARE_VEGA20;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	r = request_firmware(&adev->uvd.fw, fw_name, adev->dev);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_uvd: Can't load firmware \"%s\"\n",
			fw_name);
		वापस r;
	पूर्ण

	r = amdgpu_ucode_validate(adev->uvd.fw);
	अगर (r) अणु
		dev_err(adev->dev, "amdgpu_uvd: Can't validate firmware \"%s\"\n",
			fw_name);
		release_firmware(adev->uvd.fw);
		adev->uvd.fw = शून्य;
		वापस r;
	पूर्ण

	/* Set the शेष UVD handles that the firmware can handle */
	adev->uvd.max_handles = AMDGPU_DEFAULT_UVD_HANDLES;

	hdr = (स्थिर काष्ठा common_firmware_header *)adev->uvd.fw->data;
	family_id = le32_to_cpu(hdr->ucode_version) & 0xff;

	अगर (adev->asic_type < CHIP_VEGA20) अणु
		अचिन्हित version_major, version_minor;

		version_major = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xff;
		version_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
		DRM_INFO("Found UVD firmware Version: %u.%u Family ID: %u\n",
			version_major, version_minor, family_id);

		/*
		 * Limit the number of UVD handles depending on microcode major
		 * and minor versions. The firmware version which has 40 UVD
		 * instances support is 1.80. So all subsequent versions should
		 * also have the same support.
		 */
		अगर ((version_major > 0x01) ||
		    ((version_major == 0x01) && (version_minor >= 0x50)))
			adev->uvd.max_handles = AMDGPU_MAX_UVD_HANDLES;

		adev->uvd.fw_version = ((version_major << 24) | (version_minor << 16) |
					(family_id << 8));

		अगर ((adev->asic_type == CHIP_POLARIS10 ||
		     adev->asic_type == CHIP_POLARIS11) &&
		    (adev->uvd.fw_version < FW_1_66_16))
			DRM_ERROR("POLARIS10/11 UVD firmware version %u.%u is too old.\n",
				  version_major, version_minor);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक enc_major, enc_minor, dec_minor;

		dec_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
		enc_minor = (le32_to_cpu(hdr->ucode_version) >> 24) & 0x3f;
		enc_major = (le32_to_cpu(hdr->ucode_version) >> 30) & 0x3;
		DRM_INFO("Found UVD firmware ENC: %u.%u DEC: .%u Family ID: %u\n",
			enc_major, enc_minor, dec_minor, family_id);

		adev->uvd.max_handles = AMDGPU_MAX_UVD_HANDLES;

		adev->uvd.fw_version = le32_to_cpu(hdr->ucode_version);
	पूर्ण

	bo_size = AMDGPU_UVD_STACK_SIZE + AMDGPU_UVD_HEAP_SIZE
		  +  AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handles;
	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		bo_size += AMDGPU_GPU_PAGE_ALIGN(le32_to_cpu(hdr->ucode_size_bytes) + 8);

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; j++) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		r = amdgpu_bo_create_kernel(adev, bo_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_VRAM, &adev->uvd.inst[j].vcpu_bo,
					    &adev->uvd.inst[j].gpu_addr, &adev->uvd.inst[j].cpu_addr);
		अगर (r) अणु
			dev_err(adev->dev, "(%d) failed to allocate UVD bo\n", r);
			वापस r;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < adev->uvd.max_handles; ++i) अणु
		atomic_set(&adev->uvd.handles[i], 0);
		adev->uvd.filp[i] = शून्य;
	पूर्ण

	/* from uvd v5.0 HW addressing capacity increased to 64 bits */
	अगर (!amdgpu_device_ip_block_version_cmp(adev, AMD_IP_BLOCK_TYPE_UVD, 5, 0))
		adev->uvd.address_64_bit = true;

	चयन (adev->asic_type) अणु
	हाल CHIP_TONGA:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_65_10;
		अवरोध;
	हाल CHIP_CARRIZO:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_87_11;
		अवरोध;
	हाल CHIP_FIJI:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_87_12;
		अवरोध;
	हाल CHIP_STONEY:
		adev->uvd.use_ctx_buf = adev->uvd.fw_version >= FW_1_37_15;
		अवरोध;
	शेष:
		adev->uvd.use_ctx_buf = adev->asic_type >= CHIP_POLARIS10;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_uvd_sw_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	cancel_delayed_work_sync(&adev->uvd.idle_work);
	drm_sched_entity_destroy(&adev->uvd.entity);

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; ++j) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		kvमुक्त(adev->uvd.inst[j].saved_bo);

		amdgpu_bo_मुक्त_kernel(&adev->uvd.inst[j].vcpu_bo,
				      &adev->uvd.inst[j].gpu_addr,
				      (व्योम **)&adev->uvd.inst[j].cpu_addr);

		amdgpu_ring_fini(&adev->uvd.inst[j].ring);

		क्रम (i = 0; i < AMDGPU_MAX_UVD_ENC_RINGS; ++i)
			amdgpu_ring_fini(&adev->uvd.inst[j].ring_enc[i]);
	पूर्ण
	release_firmware(adev->uvd.fw);

	वापस 0;
पूर्ण

/**
 * amdgpu_uvd_entity_init - init entity
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 */
पूर्णांक amdgpu_uvd_entity_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	काष्ठा drm_gpu_scheduler *sched;
	पूर्णांक r;

	ring = &adev->uvd.inst[0].ring;
	sched = &ring->sched;
	r = drm_sched_entity_init(&adev->uvd.entity, DRM_SCHED_PRIORITY_NORMAL,
				  &sched, 1, शून्य);
	अगर (r) अणु
		DRM_ERROR("Failed setting up UVD kernel entity.\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_uvd_suspend(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित size;
	व्योम *ptr;
	पूर्णांक i, j;
	bool in_ras_पूर्णांकr = amdgpu_ras_पूर्णांकr_triggered();

	cancel_delayed_work_sync(&adev->uvd.idle_work);

	/* only valid क्रम physical mode */
	अगर (adev->asic_type < CHIP_POLARIS10) अणु
		क्रम (i = 0; i < adev->uvd.max_handles; ++i)
			अगर (atomic_पढ़ो(&adev->uvd.handles[i]))
				अवरोध;

		अगर (i == adev->uvd.max_handles)
			वापस 0;
	पूर्ण

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; ++j) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		अगर (adev->uvd.inst[j].vcpu_bo == शून्य)
			जारी;

		size = amdgpu_bo_size(adev->uvd.inst[j].vcpu_bo);
		ptr = adev->uvd.inst[j].cpu_addr;

		adev->uvd.inst[j].saved_bo = kvदो_स्मृति(size, GFP_KERNEL);
		अगर (!adev->uvd.inst[j].saved_bo)
			वापस -ENOMEM;

		/* re-ग_लिखो 0 since err_event_athub will corrupt VCPU buffer */
		अगर (in_ras_पूर्णांकr)
			स_रखो(adev->uvd.inst[j].saved_bo, 0, size);
		अन्यथा
			स_नकल_fromio(adev->uvd.inst[j].saved_bo, ptr, size);
	पूर्ण

	अगर (in_ras_पूर्णांकr)
		DRM_WARN("UVD VCPU state may lost due to RAS ERREVENT_ATHUB_INTERRUPT\n");

	वापस 0;
पूर्ण

पूर्णांक amdgpu_uvd_resume(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित size;
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < adev->uvd.num_uvd_inst; i++) अणु
		अगर (adev->uvd.harvest_config & (1 << i))
			जारी;
		अगर (adev->uvd.inst[i].vcpu_bo == शून्य)
			वापस -EINVAL;

		size = amdgpu_bo_size(adev->uvd.inst[i].vcpu_bo);
		ptr = adev->uvd.inst[i].cpu_addr;

		अगर (adev->uvd.inst[i].saved_bo != शून्य) अणु
			स_नकल_toio(ptr, adev->uvd.inst[i].saved_bo, size);
			kvमुक्त(adev->uvd.inst[i].saved_bo);
			adev->uvd.inst[i].saved_bo = शून्य;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा common_firmware_header *hdr;
			अचिन्हित offset;

			hdr = (स्थिर काष्ठा common_firmware_header *)adev->uvd.fw->data;
			अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) अणु
				offset = le32_to_cpu(hdr->ucode_array_offset_bytes);
				स_नकल_toio(adev->uvd.inst[i].cpu_addr, adev->uvd.fw->data + offset,
					    le32_to_cpu(hdr->ucode_size_bytes));
				size -= le32_to_cpu(hdr->ucode_size_bytes);
				ptr += le32_to_cpu(hdr->ucode_size_bytes);
			पूर्ण
			स_रखो_io(ptr, 0, size);
			/* to restore uvd fence seq */
			amdgpu_fence_driver_क्रमce_completion(&adev->uvd.inst[i].ring);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम amdgpu_uvd_मुक्त_handles(काष्ठा amdgpu_device *adev, काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_ring *ring = &adev->uvd.inst[0].ring;
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->uvd.max_handles; ++i) अणु
		uपूर्णांक32_t handle = atomic_पढ़ो(&adev->uvd.handles[i]);

		अगर (handle != 0 && adev->uvd.filp[i] == filp) अणु
			काष्ठा dma_fence *fence;

			r = amdgpu_uvd_get_destroy_msg(ring, handle, false,
						       &fence);
			अगर (r) अणु
				DRM_ERROR("Error destroying UVD %d!\n", r);
				जारी;
			पूर्ण

			dma_fence_रुको(fence, false);
			dma_fence_put(fence);

			adev->uvd.filp[i] = शून्य;
			atomic_set(&adev->uvd.handles[i], 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम amdgpu_uvd_क्रमce_पूर्णांकo_uvd_segment(काष्ठा amdgpu_bo *abo)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < abo->placement.num_placement; ++i) अणु
		abo->placements[i].fpfn = 0 >> PAGE_SHIFT;
		abo->placements[i].lpfn = (256 * 1024 * 1024) >> PAGE_SHIFT;
	पूर्ण
पूर्ण

अटल u64 amdgpu_uvd_get_addr_from_ctx(काष्ठा amdgpu_uvd_cs_ctx *ctx)
अणु
	uपूर्णांक32_t lo, hi;
	uपूर्णांक64_t addr;

	lo = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->data0);
	hi = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->data1);
	addr = ((uपूर्णांक64_t)lo) | (((uपूर्णांक64_t)hi) << 32);

	वापस addr;
पूर्ण

/**
 * amdgpu_uvd_cs_pass1 - first parsing round
 *
 * @ctx: UVD parser context
 *
 * Make sure UVD message and feedback buffers are in VRAM and
 * nobody is violating an 256MB boundary.
 */
अटल पूर्णांक amdgpu_uvd_cs_pass1(काष्ठा amdgpu_uvd_cs_ctx *ctx)
अणु
	काष्ठा tपंचांग_operation_ctx tctx = अणु false, false पूर्ण;
	काष्ठा amdgpu_bo_va_mapping *mapping;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक32_t cmd;
	uपूर्णांक64_t addr = amdgpu_uvd_get_addr_from_ctx(ctx);
	पूर्णांक r = 0;

	r = amdgpu_cs_find_mapping(ctx->parser, addr, &bo, &mapping);
	अगर (r) अणु
		DRM_ERROR("Can't find BO for addr 0x%08Lx\n", addr);
		वापस r;
	पूर्ण

	अगर (!ctx->parser->adev->uvd.address_64_bit) अणु
		/* check अगर it's a message or feedback command */
		cmd = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->idx) >> 1;
		अगर (cmd == 0x0 || cmd == 0x3) अणु
			/* yes, क्रमce it पूर्णांकo VRAM */
			uपूर्णांक32_t करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;
			amdgpu_bo_placement_from_करोमुख्य(bo, करोमुख्य);
		पूर्ण
		amdgpu_uvd_क्रमce_पूर्णांकo_uvd_segment(bo);

		r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &tctx);
	पूर्ण

	वापस r;
पूर्ण

/**
 * amdgpu_uvd_cs_msg_decode - handle UVD decode message
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @msg: poपूर्णांकer to message काष्ठाure
 * @buf_sizes: placeholder to put the dअगरferent buffer lengths
 *
 * Peek पूर्णांकo the decode message and calculate the necessary buffer sizes.
 */
अटल पूर्णांक amdgpu_uvd_cs_msg_decode(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *msg,
	अचिन्हित buf_sizes[])
अणु
	अचिन्हित stream_type = msg[4];
	अचिन्हित width = msg[6];
	अचिन्हित height = msg[7];
	अचिन्हित dpb_size = msg[9];
	अचिन्हित pitch = msg[28];
	अचिन्हित level = msg[57];

	अचिन्हित width_in_mb = width / 16;
	अचिन्हित height_in_mb = ALIGN(height / 16, 2);
	अचिन्हित fs_in_mb = width_in_mb * height_in_mb;

	अचिन्हित image_size, पंचांगp, min_dpb_size, num_dpb_buffer;
	अचिन्हित min_ctx_size = ~0;

	image_size = width * height;
	image_size += image_size / 2;
	image_size = ALIGN(image_size, 1024);

	चयन (stream_type) अणु
	हाल 0: /* H264 */
		चयन(level) अणु
		हाल 30:
			num_dpb_buffer = 8100 / fs_in_mb;
			अवरोध;
		हाल 31:
			num_dpb_buffer = 18000 / fs_in_mb;
			अवरोध;
		हाल 32:
			num_dpb_buffer = 20480 / fs_in_mb;
			अवरोध;
		हाल 41:
			num_dpb_buffer = 32768 / fs_in_mb;
			अवरोध;
		हाल 42:
			num_dpb_buffer = 34816 / fs_in_mb;
			अवरोध;
		हाल 50:
			num_dpb_buffer = 110400 / fs_in_mb;
			अवरोध;
		हाल 51:
			num_dpb_buffer = 184320 / fs_in_mb;
			अवरोध;
		शेष:
			num_dpb_buffer = 184320 / fs_in_mb;
			अवरोध;
		पूर्ण
		num_dpb_buffer++;
		अगर (num_dpb_buffer > 17)
			num_dpb_buffer = 17;

		/* reference picture buffer */
		min_dpb_size = image_size * num_dpb_buffer;

		/* macroblock context buffer */
		min_dpb_size += width_in_mb * height_in_mb * num_dpb_buffer * 192;

		/* IT surface buffer */
		min_dpb_size += width_in_mb * height_in_mb * 32;
		अवरोध;

	हाल 1: /* VC1 */

		/* reference picture buffer */
		min_dpb_size = image_size * 3;

		/* CONTEXT_BUFFER */
		min_dpb_size += width_in_mb * height_in_mb * 128;

		/* IT surface buffer */
		min_dpb_size += width_in_mb * 64;

		/* DB surface buffer */
		min_dpb_size += width_in_mb * 128;

		/* BP */
		पंचांगp = max(width_in_mb, height_in_mb);
		min_dpb_size += ALIGN(पंचांगp * 7 * 16, 64);
		अवरोध;

	हाल 3: /* MPEG2 */

		/* reference picture buffer */
		min_dpb_size = image_size * 3;
		अवरोध;

	हाल 4: /* MPEG4 */

		/* reference picture buffer */
		min_dpb_size = image_size * 3;

		/* CM */
		min_dpb_size += width_in_mb * height_in_mb * 64;

		/* IT surface buffer */
		min_dpb_size += ALIGN(width_in_mb * height_in_mb * 32, 64);
		अवरोध;

	हाल 7: /* H264 Perf */
		चयन(level) अणु
		हाल 30:
			num_dpb_buffer = 8100 / fs_in_mb;
			अवरोध;
		हाल 31:
			num_dpb_buffer = 18000 / fs_in_mb;
			अवरोध;
		हाल 32:
			num_dpb_buffer = 20480 / fs_in_mb;
			अवरोध;
		हाल 41:
			num_dpb_buffer = 32768 / fs_in_mb;
			अवरोध;
		हाल 42:
			num_dpb_buffer = 34816 / fs_in_mb;
			अवरोध;
		हाल 50:
			num_dpb_buffer = 110400 / fs_in_mb;
			अवरोध;
		हाल 51:
			num_dpb_buffer = 184320 / fs_in_mb;
			अवरोध;
		शेष:
			num_dpb_buffer = 184320 / fs_in_mb;
			अवरोध;
		पूर्ण
		num_dpb_buffer++;
		अगर (num_dpb_buffer > 17)
			num_dpb_buffer = 17;

		/* reference picture buffer */
		min_dpb_size = image_size * num_dpb_buffer;

		अगर (!adev->uvd.use_ctx_buf)अणु
			/* macroblock context buffer */
			min_dpb_size +=
				width_in_mb * height_in_mb * num_dpb_buffer * 192;

			/* IT surface buffer */
			min_dpb_size += width_in_mb * height_in_mb * 32;
		पूर्ण अन्यथा अणु
			/* macroblock context buffer */
			min_ctx_size =
				width_in_mb * height_in_mb * num_dpb_buffer * 192;
		पूर्ण
		अवरोध;

	हाल 8: /* MJPEG */
		min_dpb_size = 0;
		अवरोध;

	हाल 16: /* H265 */
		image_size = (ALIGN(width, 16) * ALIGN(height, 16) * 3) / 2;
		image_size = ALIGN(image_size, 256);

		num_dpb_buffer = (le32_to_cpu(msg[59]) & 0xff) + 2;
		min_dpb_size = image_size * num_dpb_buffer;
		min_ctx_size = ((width + 255) / 16) * ((height + 255) / 16)
					   * 16 * num_dpb_buffer + 52 * 1024;
		अवरोध;

	शेष:
		DRM_ERROR("UVD codec not handled %d!\n", stream_type);
		वापस -EINVAL;
	पूर्ण

	अगर (width > pitch) अणु
		DRM_ERROR("Invalid UVD decoding target pitch!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dpb_size < min_dpb_size) अणु
		DRM_ERROR("Invalid dpb_size in UVD message (%d / %d)!\n",
			  dpb_size, min_dpb_size);
		वापस -EINVAL;
	पूर्ण

	buf_sizes[0x1] = dpb_size;
	buf_sizes[0x2] = image_size;
	buf_sizes[0x4] = min_ctx_size;
	/* store image width to adjust nb memory pstate */
	adev->uvd.decode_image_width = width;
	वापस 0;
पूर्ण

/**
 * amdgpu_uvd_cs_msg - handle UVD message
 *
 * @ctx: UVD parser context
 * @bo: buffer object containing the message
 * @offset: offset पूर्णांकo the buffer object
 *
 * Peek पूर्णांकo the UVD message and extract the session id.
 * Make sure that we करोn't खोलो up to many sessions.
 */
अटल पूर्णांक amdgpu_uvd_cs_msg(काष्ठा amdgpu_uvd_cs_ctx *ctx,
			     काष्ठा amdgpu_bo *bo, अचिन्हित offset)
अणु
	काष्ठा amdgpu_device *adev = ctx->parser->adev;
	पूर्णांक32_t *msg, msg_type, handle;
	व्योम *ptr;
	दीर्घ r;
	पूर्णांक i;

	अगर (offset & 0x3F) अणु
		DRM_ERROR("UVD messages must be 64 byte aligned!\n");
		वापस -EINVAL;
	पूर्ण

	r = amdgpu_bo_kmap(bo, &ptr);
	अगर (r) अणु
		DRM_ERROR("Failed mapping the UVD) message (%ld)!\n", r);
		वापस r;
	पूर्ण

	msg = ptr + offset;

	msg_type = msg[1];
	handle = msg[2];

	अगर (handle == 0) अणु
		DRM_ERROR("Invalid UVD handle!\n");
		वापस -EINVAL;
	पूर्ण

	चयन (msg_type) अणु
	हाल 0:
		/* it's a create msg, calc image size (width * height) */
		amdgpu_bo_kunmap(bo);

		/* try to alloc a new handle */
		क्रम (i = 0; i < adev->uvd.max_handles; ++i) अणु
			अगर (atomic_पढ़ो(&adev->uvd.handles[i]) == handle) अणु
				DRM_ERROR(")Handle 0x%x already in use!\n",
					  handle);
				वापस -EINVAL;
			पूर्ण

			अगर (!atomic_cmpxchg(&adev->uvd.handles[i], 0, handle)) अणु
				adev->uvd.filp[i] = ctx->parser->filp;
				वापस 0;
			पूर्ण
		पूर्ण

		DRM_ERROR("No more free UVD handles!\n");
		वापस -ENOSPC;

	हाल 1:
		/* it's a decode msg, calc buffer sizes */
		r = amdgpu_uvd_cs_msg_decode(adev, msg, ctx->buf_sizes);
		amdgpu_bo_kunmap(bo);
		अगर (r)
			वापस r;

		/* validate the handle */
		क्रम (i = 0; i < adev->uvd.max_handles; ++i) अणु
			अगर (atomic_पढ़ो(&adev->uvd.handles[i]) == handle) अणु
				अगर (adev->uvd.filp[i] != ctx->parser->filp) अणु
					DRM_ERROR("UVD handle collision detected!\n");
					वापस -EINVAL;
				पूर्ण
				वापस 0;
			पूर्ण
		पूर्ण

		DRM_ERROR("Invalid UVD handle 0x%x!\n", handle);
		वापस -ENOENT;

	हाल 2:
		/* it's a destroy msg, मुक्त the handle */
		क्रम (i = 0; i < adev->uvd.max_handles; ++i)
			atomic_cmpxchg(&adev->uvd.handles[i], handle, 0);
		amdgpu_bo_kunmap(bo);
		वापस 0;

	शेष:
		DRM_ERROR("Illegal UVD message type (%d)!\n", msg_type);
		वापस -EINVAL;
	पूर्ण
	BUG();
	वापस -EINVAL;
पूर्ण

/**
 * amdgpu_uvd_cs_pass2 - second parsing round
 *
 * @ctx: UVD parser context
 *
 * Patch buffer addresses, make sure buffer sizes are correct.
 */
अटल पूर्णांक amdgpu_uvd_cs_pass2(काष्ठा amdgpu_uvd_cs_ctx *ctx)
अणु
	काष्ठा amdgpu_bo_va_mapping *mapping;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक32_t cmd;
	uपूर्णांक64_t start, end;
	uपूर्णांक64_t addr = amdgpu_uvd_get_addr_from_ctx(ctx);
	पूर्णांक r;

	r = amdgpu_cs_find_mapping(ctx->parser, addr, &bo, &mapping);
	अगर (r) अणु
		DRM_ERROR("Can't find BO for addr 0x%08Lx\n", addr);
		वापस r;
	पूर्ण

	start = amdgpu_bo_gpu_offset(bo);

	end = (mapping->last + 1 - mapping->start);
	end = end * AMDGPU_GPU_PAGE_SIZE + start;

	addr -= mapping->start * AMDGPU_GPU_PAGE_SIZE;
	start += addr;

	amdgpu_set_ib_value(ctx->parser, ctx->ib_idx, ctx->data0,
			    lower_32_bits(start));
	amdgpu_set_ib_value(ctx->parser, ctx->ib_idx, ctx->data1,
			    upper_32_bits(start));

	cmd = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->idx) >> 1;
	अगर (cmd < 0x4) अणु
		अगर ((end - start) < ctx->buf_sizes[cmd]) अणु
			DRM_ERROR("buffer (%d) to small (%d / %d)!\n", cmd,
				  (अचिन्हित)(end - start),
				  ctx->buf_sizes[cmd]);
			वापस -EINVAL;
		पूर्ण

	पूर्ण अन्यथा अगर (cmd == 0x206) अणु
		अगर ((end - start) < ctx->buf_sizes[4]) अणु
			DRM_ERROR("buffer (%d) to small (%d / %d)!\n", cmd,
					  (अचिन्हित)(end - start),
					  ctx->buf_sizes[4]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर ((cmd != 0x100) && (cmd != 0x204)) अणु
		DRM_ERROR("invalid UVD command %X!\n", cmd);
		वापस -EINVAL;
	पूर्ण

	अगर (!ctx->parser->adev->uvd.address_64_bit) अणु
		अगर ((start >> 28) != ((end - 1) >> 28)) अणु
			DRM_ERROR("reloc %LX-%LX crossing 256MB boundary!\n",
				  start, end);
			वापस -EINVAL;
		पूर्ण

		अगर ((cmd == 0 || cmd == 0x3) &&
		    (start >> 28) != (ctx->parser->adev->uvd.inst->gpu_addr >> 28)) अणु
			DRM_ERROR("msg/fb buffer %LX-%LX out of 256MB segment!\n",
				  start, end);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (cmd == 0) अणु
		ctx->has_msg_cmd = true;
		r = amdgpu_uvd_cs_msg(ctx, bo, addr);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (!ctx->has_msg_cmd) अणु
		DRM_ERROR("Message needed before other commands are send!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_uvd_cs_reg - parse रेजिस्टर ग_लिखोs
 *
 * @ctx: UVD parser context
 * @cb: callback function
 *
 * Parse the रेजिस्टर ग_लिखोs, call cb on each complete command.
 */
अटल पूर्णांक amdgpu_uvd_cs_reg(काष्ठा amdgpu_uvd_cs_ctx *ctx,
			     पूर्णांक (*cb)(काष्ठा amdgpu_uvd_cs_ctx *ctx))
अणु
	काष्ठा amdgpu_ib *ib = &ctx->parser->job->ibs[ctx->ib_idx];
	पूर्णांक i, r;

	ctx->idx++;
	क्रम (i = 0; i <= ctx->count; ++i) अणु
		अचिन्हित reg = ctx->reg + i;

		अगर (ctx->idx >= ib->length_dw) अणु
			DRM_ERROR("Register command after end of CS!\n");
			वापस -EINVAL;
		पूर्ण

		चयन (reg) अणु
		हाल mmUVD_GPCOM_VCPU_DATA0:
			ctx->data0 = ctx->idx;
			अवरोध;
		हाल mmUVD_GPCOM_VCPU_DATA1:
			ctx->data1 = ctx->idx;
			अवरोध;
		हाल mmUVD_GPCOM_VCPU_CMD:
			r = cb(ctx);
			अगर (r)
				वापस r;
			अवरोध;
		हाल mmUVD_ENGINE_CNTL:
		हाल mmUVD_NO_OP:
			अवरोध;
		शेष:
			DRM_ERROR("Invalid reg 0x%X!\n", reg);
			वापस -EINVAL;
		पूर्ण
		ctx->idx++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_uvd_cs_packets - parse UVD packets
 *
 * @ctx: UVD parser context
 * @cb: callback function
 *
 * Parse the command stream packets.
 */
अटल पूर्णांक amdgpu_uvd_cs_packets(काष्ठा amdgpu_uvd_cs_ctx *ctx,
				 पूर्णांक (*cb)(काष्ठा amdgpu_uvd_cs_ctx *ctx))
अणु
	काष्ठा amdgpu_ib *ib = &ctx->parser->job->ibs[ctx->ib_idx];
	पूर्णांक r;

	क्रम (ctx->idx = 0 ; ctx->idx < ib->length_dw; ) अणु
		uपूर्णांक32_t cmd = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->idx);
		अचिन्हित type = CP_PACKET_GET_TYPE(cmd);
		चयन (type) अणु
		हाल PACKET_TYPE0:
			ctx->reg = CP_PACKET0_GET_REG(cmd);
			ctx->count = CP_PACKET_GET_COUNT(cmd);
			r = amdgpu_uvd_cs_reg(ctx, cb);
			अगर (r)
				वापस r;
			अवरोध;
		हाल PACKET_TYPE2:
			++ctx->idx;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown packet type %d !\n", type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_uvd_ring_parse_cs - UVD command submission parser
 *
 * @parser: Command submission parser context
 * @ib_idx: Which indirect buffer to use
 *
 * Parse the command stream, patch in addresses as necessary.
 */
पूर्णांक amdgpu_uvd_ring_parse_cs(काष्ठा amdgpu_cs_parser *parser, uपूर्णांक32_t ib_idx)
अणु
	काष्ठा amdgpu_uvd_cs_ctx ctx = अणुपूर्ण;
	अचिन्हित buf_sizes[] = अणु
		[0x00000000]	=	2048,
		[0x00000001]	=	0xFFFFFFFF,
		[0x00000002]	=	0xFFFFFFFF,
		[0x00000003]	=	2048,
		[0x00000004]	=	0xFFFFFFFF,
	पूर्ण;
	काष्ठा amdgpu_ib *ib = &parser->job->ibs[ib_idx];
	पूर्णांक r;

	parser->job->vm = शून्य;
	ib->gpu_addr = amdgpu_sa_bo_gpu_addr(ib->sa_bo);

	अगर (ib->length_dw % 16) अणु
		DRM_ERROR("UVD IB length (%d) not 16 dwords aligned!\n",
			  ib->length_dw);
		वापस -EINVAL;
	पूर्ण

	ctx.parser = parser;
	ctx.buf_sizes = buf_sizes;
	ctx.ib_idx = ib_idx;

	/* first round only required on chips without UVD 64 bit address support */
	अगर (!parser->adev->uvd.address_64_bit) अणु
		/* first round, make sure the buffers are actually in the UVD segment */
		r = amdgpu_uvd_cs_packets(&ctx, amdgpu_uvd_cs_pass1);
		अगर (r)
			वापस r;
	पूर्ण

	/* second round, patch buffer addresses पूर्णांकo the command stream */
	r = amdgpu_uvd_cs_packets(&ctx, amdgpu_uvd_cs_pass2);
	अगर (r)
		वापस r;

	अगर (!ctx.has_msg_cmd) अणु
		DRM_ERROR("UVD-IBs need a msg command!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_uvd_send_msg(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_bo *bo,
			       bool direct, काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा dma_fence *f = शून्य;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	uपूर्णांक32_t data[4];
	uपूर्णांक64_t addr;
	दीर्घ r;
	पूर्णांक i;
	अचिन्हित offset_idx = 0;
	अचिन्हित offset[3] = अणु UVD_BASE_SI, 0, 0 पूर्ण;

	amdgpu_bo_kunmap(bo);
	amdgpu_bo_unpin(bo);

	अगर (!ring->adev->uvd.address_64_bit) अणु
		काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;

		amdgpu_bo_placement_from_करोमुख्य(bo, AMDGPU_GEM_DOMAIN_VRAM);
		amdgpu_uvd_क्रमce_पूर्णांकo_uvd_segment(bo);
		r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
		अगर (r)
			जाओ err;
	पूर्ण

	r = amdgpu_job_alloc_with_ib(adev, 64, direct ? AMDGPU_IB_POOL_सूचीECT :
				     AMDGPU_IB_POOL_DELAYED, &job);
	अगर (r)
		जाओ err;

	अगर (adev->asic_type >= CHIP_VEGA10) अणु
		offset_idx = 1 + ring->me;
		offset[1] = adev->reg_offset[UVD_HWIP][0][1];
		offset[2] = adev->reg_offset[UVD_HWIP][1][1];
	पूर्ण

	data[0] = PACKET0(offset[offset_idx] + UVD_GPCOM_VCPU_DATA0, 0);
	data[1] = PACKET0(offset[offset_idx] + UVD_GPCOM_VCPU_DATA1, 0);
	data[2] = PACKET0(offset[offset_idx] + UVD_GPCOM_VCPU_CMD, 0);
	data[3] = PACKET0(offset[offset_idx] + UVD_NO_OP, 0);

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);
	ib->ptr[0] = data[0];
	ib->ptr[1] = addr;
	ib->ptr[2] = data[1];
	ib->ptr[3] = addr >> 32;
	ib->ptr[4] = data[2];
	ib->ptr[5] = 0;
	क्रम (i = 6; i < 16; i += 2) अणु
		ib->ptr[i] = data[3];
		ib->ptr[i+1] = 0;
	पूर्ण
	ib->length_dw = 16;

	अगर (direct) अणु
		r = dma_resv_रुको_समयout_rcu(bo->tbo.base.resv,
							true, false,
							msecs_to_jअगरfies(10));
		अगर (r == 0)
			r = -ETIMEDOUT;
		अगर (r < 0)
			जाओ err_मुक्त;

		r = amdgpu_job_submit_direct(job, ring, &f);
		अगर (r)
			जाओ err_मुक्त;
	पूर्ण अन्यथा अणु
		r = amdgpu_sync_resv(adev, &job->sync, bo->tbo.base.resv,
				     AMDGPU_SYNC_ALWAYS,
				     AMDGPU_FENCE_OWNER_UNDEFINED);
		अगर (r)
			जाओ err_मुक्त;

		r = amdgpu_job_submit(job, &adev->uvd.entity,
				      AMDGPU_FENCE_OWNER_UNDEFINED, &f);
		अगर (r)
			जाओ err_मुक्त;
	पूर्ण

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

/* multiple fence commands without any stream commands in between can
   crash the vcpu so just try to emmit a dummy create/destroy msg to
   aव्योम this */
पूर्णांक amdgpu_uvd_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
			      काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_bo *bo = शून्य;
	uपूर्णांक32_t *msg;
	पूर्णांक r, i;

	r = amdgpu_bo_create_reserved(adev, 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT,
				      &bo, शून्य, (व्योम **)&msg);
	अगर (r)
		वापस r;

	/* stitch together an UVD create msg */
	msg[0] = cpu_to_le32(0x00000de4);
	msg[1] = cpu_to_le32(0x00000000);
	msg[2] = cpu_to_le32(handle);
	msg[3] = cpu_to_le32(0x00000000);
	msg[4] = cpu_to_le32(0x00000000);
	msg[5] = cpu_to_le32(0x00000000);
	msg[6] = cpu_to_le32(0x00000000);
	msg[7] = cpu_to_le32(0x00000780);
	msg[8] = cpu_to_le32(0x00000440);
	msg[9] = cpu_to_le32(0x00000000);
	msg[10] = cpu_to_le32(0x01b37000);
	क्रम (i = 11; i < 1024; ++i)
		msg[i] = cpu_to_le32(0x0);

	वापस amdgpu_uvd_send_msg(ring, bo, true, fence);
पूर्ण

पूर्णांक amdgpu_uvd_get_destroy_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
			       bool direct, काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_bo *bo = शून्य;
	uपूर्णांक32_t *msg;
	पूर्णांक r, i;

	r = amdgpu_bo_create_reserved(adev, 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT,
				      &bo, शून्य, (व्योम **)&msg);
	अगर (r)
		वापस r;

	/* stitch together an UVD destroy msg */
	msg[0] = cpu_to_le32(0x00000de4);
	msg[1] = cpu_to_le32(0x00000002);
	msg[2] = cpu_to_le32(handle);
	msg[3] = cpu_to_le32(0x00000000);
	क्रम (i = 4; i < 1024; ++i)
		msg[i] = cpu_to_le32(0x0);

	वापस amdgpu_uvd_send_msg(ring, bo, direct, fence);
पूर्ण

अटल व्योम amdgpu_uvd_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device, uvd.idle_work.work);
	अचिन्हित fences = 0, i, j;

	क्रम (i = 0; i < adev->uvd.num_uvd_inst; ++i) अणु
		अगर (adev->uvd.harvest_config & (1 << i))
			जारी;
		fences += amdgpu_fence_count_emitted(&adev->uvd.inst[i].ring);
		क्रम (j = 0; j < adev->uvd.num_enc_rings; ++j) अणु
			fences += amdgpu_fence_count_emitted(&adev->uvd.inst[i].ring_enc[j]);
		पूर्ण
	पूर्ण

	अगर (fences == 0) अणु
		अगर (adev->pm.dpm_enabled) अणु
			amdgpu_dpm_enable_uvd(adev, false);
		पूर्ण अन्यथा अणु
			amdgpu_asic_set_uvd_घड़ीs(adev, 0, 0);
			/* shutकरोwn the UVD block */
			amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
							       AMD_PG_STATE_GATE);
			amdgpu_device_ip_set_घड़ीgating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
							       AMD_CG_STATE_GATE);
		पूर्ण
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&adev->uvd.idle_work, UVD_IDLE_TIMEOUT);
	पूर्ण
पूर्ण

व्योम amdgpu_uvd_ring_begin_use(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	bool set_घड़ीs;

	अगर (amdgpu_sriov_vf(adev))
		वापस;

	set_घड़ीs = !cancel_delayed_work_sync(&adev->uvd.idle_work);
	अगर (set_घड़ीs) अणु
		अगर (adev->pm.dpm_enabled) अणु
			amdgpu_dpm_enable_uvd(adev, true);
		पूर्ण अन्यथा अणु
			amdgpu_asic_set_uvd_घड़ीs(adev, 53300, 40000);
			amdgpu_device_ip_set_घड़ीgating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
							       AMD_CG_STATE_UNGATE);
			amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
							       AMD_PG_STATE_UNGATE);
		पूर्ण
	पूर्ण
पूर्ण

व्योम amdgpu_uvd_ring_end_use(काष्ठा amdgpu_ring *ring)
अणु
	अगर (!amdgpu_sriov_vf(ring->adev))
		schedule_delayed_work(&ring->adev->uvd.idle_work, UVD_IDLE_TIMEOUT);
पूर्ण

/**
 * amdgpu_uvd_ring_test_ib - test ib execution
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 * Test अगर we can successfully execute an IB
 */
पूर्णांक amdgpu_uvd_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence;
	दीर्घ r;

	r = amdgpu_uvd_get_create_msg(ring, 1, शून्य);
	अगर (r)
		जाओ error;

	r = amdgpu_uvd_get_destroy_msg(ring, 1, true, &fence);
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

/**
 * amdgpu_uvd_used_handles - वापसs used UVD handles
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Returns the number of UVD handles in use
 */
uपूर्णांक32_t amdgpu_uvd_used_handles(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t used_handles = 0;

	क्रम (i = 0; i < adev->uvd.max_handles; ++i) अणु
		/*
		 * Handles can be मुक्तd in any order, and not
		 * necessarily linear. So we need to count
		 * all non-zero handles.
		 */
		अगर (atomic_पढ़ो(&adev->uvd.handles[i]))
			used_handles++;
	पूर्ण

	वापस used_handles;
पूर्ण
