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

#समावेश "radeon.h"
#समावेश "radeon_ucode.h"
#समावेश "r600d.h"

/* 1 second समयout */
#घोषणा UVD_IDLE_TIMEOUT_MS	1000

/* Firmware Names */
#घोषणा FIRMWARE_R600		"radeon/R600_uvd.bin"
#घोषणा FIRMWARE_RS780		"radeon/RS780_uvd.bin"
#घोषणा FIRMWARE_RV770		"radeon/RV770_uvd.bin"
#घोषणा FIRMWARE_RV710		"radeon/RV710_uvd.bin"
#घोषणा FIRMWARE_CYPRESS	"radeon/CYPRESS_uvd.bin"
#घोषणा FIRMWARE_SUMO		"radeon/SUMO_uvd.bin"
#घोषणा FIRMWARE_TAHITI		"radeon/TAHITI_uvd.bin"
#घोषणा FIRMWARE_BONAIRE_LEGACY	"radeon/BONAIRE_uvd.bin"
#घोषणा FIRMWARE_BONAIRE	"radeon/bonaire_uvd.bin"

MODULE_FIRMWARE(FIRMWARE_R600);
MODULE_FIRMWARE(FIRMWARE_RS780);
MODULE_FIRMWARE(FIRMWARE_RV770);
MODULE_FIRMWARE(FIRMWARE_RV710);
MODULE_FIRMWARE(FIRMWARE_CYPRESS);
MODULE_FIRMWARE(FIRMWARE_SUMO);
MODULE_FIRMWARE(FIRMWARE_TAHITI);
MODULE_FIRMWARE(FIRMWARE_BONAIRE_LEGACY);
MODULE_FIRMWARE(FIRMWARE_BONAIRE);

अटल व्योम radeon_uvd_idle_work_handler(काष्ठा work_काष्ठा *work);

पूर्णांक radeon_uvd_init(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित दीर्घ bo_size;
	स्थिर अक्षर *fw_name = शून्य, *legacy_fw_name = शून्य;
	पूर्णांक i, r;

	INIT_DELAYED_WORK(&rdev->uvd.idle_work, radeon_uvd_idle_work_handler);

	चयन (rdev->family) अणु
	हाल CHIP_RV610:
	हाल CHIP_RV630:
	हाल CHIP_RV670:
	हाल CHIP_RV620:
	हाल CHIP_RV635:
		legacy_fw_name = FIRMWARE_R600;
		अवरोध;

	हाल CHIP_RS780:
	हाल CHIP_RS880:
		legacy_fw_name = FIRMWARE_RS780;
		अवरोध;

	हाल CHIP_RV770:
		legacy_fw_name = FIRMWARE_RV770;
		अवरोध;

	हाल CHIP_RV710:
	हाल CHIP_RV730:
	हाल CHIP_RV740:
		legacy_fw_name = FIRMWARE_RV710;
		अवरोध;

	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
	हाल CHIP_JUNIPER:
	हाल CHIP_REDWOOD:
	हाल CHIP_CEDAR:
		legacy_fw_name = FIRMWARE_CYPRESS;
		अवरोध;

	हाल CHIP_SUMO:
	हाल CHIP_SUMO2:
	हाल CHIP_PALM:
	हाल CHIP_CAYMAN:
	हाल CHIP_BARTS:
	हाल CHIP_TURKS:
	हाल CHIP_CAICOS:
		legacy_fw_name = FIRMWARE_SUMO;
		अवरोध;

	हाल CHIP_TAHITI:
	हाल CHIP_VERDE:
	हाल CHIP_PITCAIRN:
	हाल CHIP_ARUBA:
	हाल CHIP_OLAND:
		legacy_fw_name = FIRMWARE_TAHITI;
		अवरोध;

	हाल CHIP_BONAIRE:
	हाल CHIP_KABINI:
	हाल CHIP_KAVERI:
	हाल CHIP_HAWAII:
	हाल CHIP_MULLINS:
		legacy_fw_name = FIRMWARE_BONAIRE_LEGACY;
		fw_name = FIRMWARE_BONAIRE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	rdev->uvd.fw_header_present = false;
	rdev->uvd.max_handles = RADEON_DEFAULT_UVD_HANDLES;
	अगर (fw_name) अणु
		/* Let's try to load the newer firmware first */
		r = request_firmware(&rdev->uvd_fw, fw_name, rdev->dev);
		अगर (r) अणु
			dev_err(rdev->dev, "radeon_uvd: Can't load firmware \"%s\"\n",
				fw_name);
		पूर्ण अन्यथा अणु
			काष्ठा common_firmware_header *hdr = (व्योम *)rdev->uvd_fw->data;
			अचिन्हित version_major, version_minor, family_id;

			r = radeon_ucode_validate(rdev->uvd_fw);
			अगर (r)
				वापस r;

			rdev->uvd.fw_header_present = true;

			family_id = le32_to_cpu(hdr->ucode_version) & 0xff;
			version_major = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xff;
			version_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
			DRM_INFO("Found UVD firmware Version: %u.%u Family ID: %u\n",
				 version_major, version_minor, family_id);

			/*
			 * Limit the number of UVD handles depending on
			 * microcode major and minor versions.
			 */
			अगर ((version_major >= 0x01) && (version_minor >= 0x37))
				rdev->uvd.max_handles = RADEON_MAX_UVD_HANDLES;
		पूर्ण
	पूर्ण

	/*
	 * In हाल there is only legacy firmware, or we encounter an error
	 * जबतक loading the new firmware, we fall back to loading the legacy
	 * firmware now.
	 */
	अगर (!fw_name || r) अणु
		r = request_firmware(&rdev->uvd_fw, legacy_fw_name, rdev->dev);
		अगर (r) अणु
			dev_err(rdev->dev, "radeon_uvd: Can't load firmware \"%s\"\n",
				legacy_fw_name);
			वापस r;
		पूर्ण
	पूर्ण

	bo_size = RADEON_GPU_PAGE_ALIGN(rdev->uvd_fw->size + 8) +
		  RADEON_UVD_STACK_SIZE + RADEON_UVD_HEAP_SIZE +
		  RADEON_UVD_SESSION_SIZE * rdev->uvd.max_handles;
	r = radeon_bo_create(rdev, bo_size, PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, शून्य,
			     शून्य, &rdev->uvd.vcpu_bo);
	अगर (r) अणु
		dev_err(rdev->dev, "(%d) failed to allocate UVD bo\n", r);
		वापस r;
	पूर्ण

	r = radeon_bo_reserve(rdev->uvd.vcpu_bo, false);
	अगर (r) अणु
		radeon_bo_unref(&rdev->uvd.vcpu_bo);
		dev_err(rdev->dev, "(%d) failed to reserve UVD bo\n", r);
		वापस r;
	पूर्ण

	r = radeon_bo_pin(rdev->uvd.vcpu_bo, RADEON_GEM_DOMAIN_VRAM,
			  &rdev->uvd.gpu_addr);
	अगर (r) अणु
		radeon_bo_unreserve(rdev->uvd.vcpu_bo);
		radeon_bo_unref(&rdev->uvd.vcpu_bo);
		dev_err(rdev->dev, "(%d) UVD bo pin failed\n", r);
		वापस r;
	पूर्ण

	r = radeon_bo_kmap(rdev->uvd.vcpu_bo, &rdev->uvd.cpu_addr);
	अगर (r) अणु
		dev_err(rdev->dev, "(%d) UVD map failed\n", r);
		वापस r;
	पूर्ण

	radeon_bo_unreserve(rdev->uvd.vcpu_bo);

	क्रम (i = 0; i < rdev->uvd.max_handles; ++i) अणु
		atomic_set(&rdev->uvd.handles[i], 0);
		rdev->uvd.filp[i] = शून्य;
		rdev->uvd.img_size[i] = 0;
	पूर्ण

	वापस 0;
पूर्ण

व्योम radeon_uvd_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->uvd.vcpu_bo == शून्य)
		वापस;

	r = radeon_bo_reserve(rdev->uvd.vcpu_bo, false);
	अगर (!r) अणु
		radeon_bo_kunmap(rdev->uvd.vcpu_bo);
		radeon_bo_unpin(rdev->uvd.vcpu_bo);
		radeon_bo_unreserve(rdev->uvd.vcpu_bo);
	पूर्ण

	radeon_bo_unref(&rdev->uvd.vcpu_bo);

	radeon_ring_fini(rdev, &rdev->ring[R600_RING_TYPE_UVD_INDEX]);

	release_firmware(rdev->uvd_fw);
पूर्ण

पूर्णांक radeon_uvd_suspend(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, r;

	अगर (rdev->uvd.vcpu_bo == शून्य)
		वापस 0;

	क्रम (i = 0; i < rdev->uvd.max_handles; ++i) अणु
		uपूर्णांक32_t handle = atomic_पढ़ो(&rdev->uvd.handles[i]);
		अगर (handle != 0) अणु
			काष्ठा radeon_fence *fence;

			radeon_uvd_note_usage(rdev);

			r = radeon_uvd_get_destroy_msg(rdev,
				R600_RING_TYPE_UVD_INDEX, handle, &fence);
			अगर (r) अणु
				DRM_ERROR("Error destroying UVD (%d)!\n", r);
				जारी;
			पूर्ण

			radeon_fence_रुको(fence, false);
			radeon_fence_unref(&fence);

			rdev->uvd.filp[i] = शून्य;
			atomic_set(&rdev->uvd.handles[i], 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक radeon_uvd_resume(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित size;
	व्योम *ptr;

	अगर (rdev->uvd.vcpu_bo == शून्य)
		वापस -EINVAL;

	स_नकल_toio((व्योम __iomem *)rdev->uvd.cpu_addr, rdev->uvd_fw->data, rdev->uvd_fw->size);

	size = radeon_bo_size(rdev->uvd.vcpu_bo);
	size -= rdev->uvd_fw->size;

	ptr = rdev->uvd.cpu_addr;
	ptr += rdev->uvd_fw->size;

	स_रखो_io((व्योम __iomem *)ptr, 0, size);

	वापस 0;
पूर्ण

व्योम radeon_uvd_क्रमce_पूर्णांकo_uvd_segment(काष्ठा radeon_bo *rbo,
				       uपूर्णांक32_t allowed_करोमुख्यs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rbo->placement.num_placement; ++i) अणु
		rbo->placements[i].fpfn = 0 >> PAGE_SHIFT;
		rbo->placements[i].lpfn = (256 * 1024 * 1024) >> PAGE_SHIFT;
	पूर्ण

	/* If it must be in VRAM it must be in the first segment as well */
	अगर (allowed_करोमुख्यs == RADEON_GEM_DOMAIN_VRAM)
		वापस;

	/* पात अगर we alपढ़ोy have more than one placement */
	अगर (rbo->placement.num_placement > 1)
		वापस;

	/* add another 256MB segment */
	rbo->placements[1] = rbo->placements[0];
	rbo->placements[1].fpfn += (256 * 1024 * 1024) >> PAGE_SHIFT;
	rbo->placements[1].lpfn += (256 * 1024 * 1024) >> PAGE_SHIFT;
	rbo->placement.num_placement++;
	rbo->placement.num_busy_placement++;
पूर्ण

व्योम radeon_uvd_मुक्त_handles(काष्ठा radeon_device *rdev, काष्ठा drm_file *filp)
अणु
	पूर्णांक i, r;
	क्रम (i = 0; i < rdev->uvd.max_handles; ++i) अणु
		uपूर्णांक32_t handle = atomic_पढ़ो(&rdev->uvd.handles[i]);
		अगर (handle != 0 && rdev->uvd.filp[i] == filp) अणु
			काष्ठा radeon_fence *fence;

			radeon_uvd_note_usage(rdev);

			r = radeon_uvd_get_destroy_msg(rdev,
				R600_RING_TYPE_UVD_INDEX, handle, &fence);
			अगर (r) अणु
				DRM_ERROR("Error destroying UVD (%d)!\n", r);
				जारी;
			पूर्ण

			radeon_fence_रुको(fence, false);
			radeon_fence_unref(&fence);

			rdev->uvd.filp[i] = शून्य;
			atomic_set(&rdev->uvd.handles[i], 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_uvd_cs_msg_decode(uपूर्णांक32_t *msg, अचिन्हित buf_sizes[])
अणु
	अचिन्हित stream_type = msg[4];
	अचिन्हित width = msg[6];
	अचिन्हित height = msg[7];
	अचिन्हित dpb_size = msg[9];
	अचिन्हित pitch = msg[28];

	अचिन्हित width_in_mb = width / 16;
	अचिन्हित height_in_mb = ALIGN(height / 16, 2);

	अचिन्हित image_size, पंचांगp, min_dpb_size;

	image_size = width * height;
	image_size += image_size / 2;
	image_size = ALIGN(image_size, 1024);

	चयन (stream_type) अणु
	हाल 0: /* H264 */

		/* reference picture buffer */
		min_dpb_size = image_size * 17;

		/* macroblock context buffer */
		min_dpb_size += width_in_mb * height_in_mb * 17 * 192;

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
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_uvd_validate_codec(काष्ठा radeon_cs_parser *p,
				     अचिन्हित stream_type)
अणु
	चयन (stream_type) अणु
	हाल 0: /* H264 */
	हाल 1: /* VC1 */
		/* always supported */
		वापस 0;

	हाल 3: /* MPEG2 */
	हाल 4: /* MPEG4 */
		/* only since UVD 3 */
		अगर (p->rdev->family >= CHIP_PALM)
			वापस 0;

		fallthrough;
	शेष:
		DRM_ERROR("UVD codec not supported by hardware %d!\n",
			  stream_type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_uvd_cs_msg(काष्ठा radeon_cs_parser *p, काष्ठा radeon_bo *bo,
			     अचिन्हित offset, अचिन्हित buf_sizes[])
अणु
	पूर्णांक32_t *msg, msg_type, handle;
	अचिन्हित img_size = 0;
	काष्ठा dma_fence *f;
	व्योम *ptr;

	पूर्णांक i, r;

	अगर (offset & 0x3F) अणु
		DRM_ERROR("UVD messages must be 64 byte aligned!\n");
		वापस -EINVAL;
	पूर्ण

	f = dma_resv_get_excl(bo->tbo.base.resv);
	अगर (f) अणु
		r = radeon_fence_रुको((काष्ठा radeon_fence *)f, false);
		अगर (r) अणु
			DRM_ERROR("Failed waiting for UVD message (%d)!\n", r);
			वापस r;
		पूर्ण
	पूर्ण

	r = radeon_bo_kmap(bo, &ptr);
	अगर (r) अणु
		DRM_ERROR("Failed mapping the UVD message (%d)!\n", r);
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
		img_size = msg[7] * msg[8];

		r = radeon_uvd_validate_codec(p, msg[4]);
		radeon_bo_kunmap(bo);
		अगर (r)
			वापस r;

		/* try to alloc a new handle */
		क्रम (i = 0; i < p->rdev->uvd.max_handles; ++i) अणु
			अगर (atomic_पढ़ो(&p->rdev->uvd.handles[i]) == handle) अणु
				DRM_ERROR("Handle 0x%x already in use!\n", handle);
				वापस -EINVAL;
			पूर्ण

			अगर (!atomic_cmpxchg(&p->rdev->uvd.handles[i], 0, handle)) अणु
				p->rdev->uvd.filp[i] = p->filp;
				p->rdev->uvd.img_size[i] = img_size;
				वापस 0;
			पूर्ण
		पूर्ण

		DRM_ERROR("No more free UVD handles!\n");
		वापस -EINVAL;

	हाल 1:
		/* it's a decode msg, validate codec and calc buffer sizes */
		r = radeon_uvd_validate_codec(p, msg[4]);
		अगर (!r)
			r = radeon_uvd_cs_msg_decode(msg, buf_sizes);
		radeon_bo_kunmap(bo);
		अगर (r)
			वापस r;

		/* validate the handle */
		क्रम (i = 0; i < p->rdev->uvd.max_handles; ++i) अणु
			अगर (atomic_पढ़ो(&p->rdev->uvd.handles[i]) == handle) अणु
				अगर (p->rdev->uvd.filp[i] != p->filp) अणु
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
		क्रम (i = 0; i < p->rdev->uvd.max_handles; ++i)
			atomic_cmpxchg(&p->rdev->uvd.handles[i], handle, 0);
		radeon_bo_kunmap(bo);
		वापस 0;

	शेष:

		DRM_ERROR("Illegal UVD message type (%d)!\n", msg_type);
		वापस -EINVAL;
	पूर्ण

	BUG();
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक radeon_uvd_cs_reloc(काष्ठा radeon_cs_parser *p,
			       पूर्णांक data0, पूर्णांक data1,
			       अचिन्हित buf_sizes[], bool *has_msg_cmd)
अणु
	काष्ठा radeon_cs_chunk *relocs_chunk;
	काष्ठा radeon_bo_list *reloc;
	अचिन्हित idx, cmd, offset;
	uपूर्णांक64_t start, end;
	पूर्णांक r;

	relocs_chunk = p->chunk_relocs;
	offset = radeon_get_ib_value(p, data0);
	idx = radeon_get_ib_value(p, data1);
	अगर (idx >= relocs_chunk->length_dw) अणु
		DRM_ERROR("Relocs at %d after relocations chunk end %d !\n",
			  idx, relocs_chunk->length_dw);
		वापस -EINVAL;
	पूर्ण

	reloc = &p->relocs[(idx / 4)];
	start = reloc->gpu_offset;
	end = start + radeon_bo_size(reloc->robj);
	start += offset;

	p->ib.ptr[data0] = start & 0xFFFFFFFF;
	p->ib.ptr[data1] = start >> 32;

	cmd = radeon_get_ib_value(p, p->idx) >> 1;

	अगर (cmd < 0x4) अणु
		अगर (end <= start) अणु
			DRM_ERROR("invalid reloc offset %X!\n", offset);
			वापस -EINVAL;
		पूर्ण
		अगर ((end - start) < buf_sizes[cmd]) अणु
			DRM_ERROR("buffer (%d) to small (%d / %d)!\n", cmd,
				  (अचिन्हित)(end - start), buf_sizes[cmd]);
			वापस -EINVAL;
		पूर्ण

	पूर्ण अन्यथा अगर (cmd != 0x100) अणु
		DRM_ERROR("invalid UVD command %X!\n", cmd);
		वापस -EINVAL;
	पूर्ण

	अगर ((start >> 28) != ((end - 1) >> 28)) अणु
		DRM_ERROR("reloc %LX-%LX crossing 256MB boundary!\n",
			  start, end);
		वापस -EINVAL;
	पूर्ण

	/* TODO: is this still necessary on NI+ ? */
	अगर ((cmd == 0 || cmd == 0x3) &&
	    (start >> 28) != (p->rdev->uvd.gpu_addr >> 28)) अणु
		DRM_ERROR("msg/fb buffer %LX-%LX out of 256MB segment!\n",
			  start, end);
		वापस -EINVAL;
	पूर्ण

	अगर (cmd == 0) अणु
		अगर (*has_msg_cmd) अणु
			DRM_ERROR("More than one message in a UVD-IB!\n");
			वापस -EINVAL;
		पूर्ण
		*has_msg_cmd = true;
		r = radeon_uvd_cs_msg(p, reloc->robj, offset, buf_sizes);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (!*has_msg_cmd) अणु
		DRM_ERROR("Message needed before other commands are send!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक radeon_uvd_cs_reg(काष्ठा radeon_cs_parser *p,
			     काष्ठा radeon_cs_packet *pkt,
			     पूर्णांक *data0, पूर्णांक *data1,
			     अचिन्हित buf_sizes[],
			     bool *has_msg_cmd)
अणु
	पूर्णांक i, r;

	p->idx++;
	क्रम (i = 0; i <= pkt->count; ++i) अणु
		चयन (pkt->reg + i*4) अणु
		हाल UVD_GPCOM_VCPU_DATA0:
			*data0 = p->idx;
			अवरोध;
		हाल UVD_GPCOM_VCPU_DATA1:
			*data1 = p->idx;
			अवरोध;
		हाल UVD_GPCOM_VCPU_CMD:
			r = radeon_uvd_cs_reloc(p, *data0, *data1,
						buf_sizes, has_msg_cmd);
			अगर (r)
				वापस r;
			अवरोध;
		हाल UVD_ENGINE_CNTL:
		हाल UVD_NO_OP:
			अवरोध;
		शेष:
			DRM_ERROR("Invalid reg 0x%X!\n",
				  pkt->reg + i*4);
			वापस -EINVAL;
		पूर्ण
		p->idx++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक radeon_uvd_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_packet pkt;
	पूर्णांक r, data0 = 0, data1 = 0;

	/* करोes the IB has a msg command */
	bool has_msg_cmd = false;

	/* minimum buffer sizes */
	अचिन्हित buf_sizes[] = अणु
		[0x00000000]	=	2048,
		[0x00000001]	=	32 * 1024 * 1024,
		[0x00000002]	=	2048 * 1152 * 3,
		[0x00000003]	=	2048,
	पूर्ण;

	अगर (p->chunk_ib->length_dw % 16) अणु
		DRM_ERROR("UVD IB length (%d) not 16 dwords aligned!\n",
			  p->chunk_ib->length_dw);
		वापस -EINVAL;
	पूर्ण

	अगर (p->chunk_relocs == शून्य) अणु
		DRM_ERROR("No relocation chunk !\n");
		वापस -EINVAL;
	पूर्ण


	करो अणु
		r = radeon_cs_packet_parse(p, &pkt, p->idx);
		अगर (r)
			वापस r;
		चयन (pkt.type) अणु
		हाल RADEON_PACKET_TYPE0:
			r = radeon_uvd_cs_reg(p, &pkt, &data0, &data1,
					      buf_sizes, &has_msg_cmd);
			अगर (r)
				वापस r;
			अवरोध;
		हाल RADEON_PACKET_TYPE2:
			p->idx += pkt.count + 2;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown packet type %d !\n", pkt.type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (p->idx < p->chunk_ib->length_dw);

	अगर (!has_msg_cmd) अणु
		DRM_ERROR("UVD-IBs need a msg command!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक radeon_uvd_send_msg(काष्ठा radeon_device *rdev,
			       पूर्णांक ring, uपूर्णांक64_t addr,
			       काष्ठा radeon_fence **fence)
अणु
	काष्ठा radeon_ib ib;
	पूर्णांक i, r;

	r = radeon_ib_get(rdev, ring, &ib, शून्य, 64);
	अगर (r)
		वापस r;

	ib.ptr[0] = PACKET0(UVD_GPCOM_VCPU_DATA0, 0);
	ib.ptr[1] = addr;
	ib.ptr[2] = PACKET0(UVD_GPCOM_VCPU_DATA1, 0);
	ib.ptr[3] = addr >> 32;
	ib.ptr[4] = PACKET0(UVD_GPCOM_VCPU_CMD, 0);
	ib.ptr[5] = 0;
	क्रम (i = 6; i < 16; i += 2) अणु
		ib.ptr[i] = PACKET0(UVD_NO_OP, 0);
		ib.ptr[i+1] = 0;
	पूर्ण
	ib.length_dw = 16;

	r = radeon_ib_schedule(rdev, &ib, शून्य, false);

	अगर (fence)
		*fence = radeon_fence_ref(ib.fence);

	radeon_ib_मुक्त(rdev, &ib);
	वापस r;
पूर्ण

/*
 * multiple fence commands without any stream commands in between can
 * crash the vcpu so just try to emmit a dummy create/destroy msg to
 * aव्योम this
 */
पूर्णांक radeon_uvd_get_create_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			      uपूर्णांक32_t handle, काष्ठा radeon_fence **fence)
अणु
	/* we use the last page of the vcpu bo क्रम the UVD message */
	uपूर्णांक64_t offs = radeon_bo_size(rdev->uvd.vcpu_bo) -
		RADEON_GPU_PAGE_SIZE;

	uपूर्णांक32_t __iomem *msg = (व्योम __iomem *)(rdev->uvd.cpu_addr + offs);
	uपूर्णांक64_t addr = rdev->uvd.gpu_addr + offs;

	पूर्णांक r, i;

	r = radeon_bo_reserve(rdev->uvd.vcpu_bo, true);
	अगर (r)
		वापस r;

	/* stitch together an UVD create msg */
	ग_लिखोl(cpu_to_le32(0x00000de4), &msg[0]);
	ग_लिखोl(0x0, (व्योम __iomem *)&msg[1]);
	ग_लिखोl(cpu_to_le32(handle), &msg[2]);
	ग_लिखोl(0x0, &msg[3]);
	ग_लिखोl(0x0, &msg[4]);
	ग_लिखोl(0x0, &msg[5]);
	ग_लिखोl(0x0, &msg[6]);
	ग_लिखोl(cpu_to_le32(0x00000780), &msg[7]);
	ग_लिखोl(cpu_to_le32(0x00000440), &msg[8]);
	ग_लिखोl(0x0, &msg[9]);
	ग_लिखोl(cpu_to_le32(0x01b37000), &msg[10]);
	क्रम (i = 11; i < 1024; ++i)
		ग_लिखोl(0x0, &msg[i]);

	r = radeon_uvd_send_msg(rdev, ring, addr, fence);
	radeon_bo_unreserve(rdev->uvd.vcpu_bo);
	वापस r;
पूर्ण

पूर्णांक radeon_uvd_get_destroy_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			       uपूर्णांक32_t handle, काष्ठा radeon_fence **fence)
अणु
	/* we use the last page of the vcpu bo क्रम the UVD message */
	uपूर्णांक64_t offs = radeon_bo_size(rdev->uvd.vcpu_bo) -
		RADEON_GPU_PAGE_SIZE;

	uपूर्णांक32_t __iomem *msg = (व्योम __iomem *)(rdev->uvd.cpu_addr + offs);
	uपूर्णांक64_t addr = rdev->uvd.gpu_addr + offs;

	पूर्णांक r, i;

	r = radeon_bo_reserve(rdev->uvd.vcpu_bo, true);
	अगर (r)
		वापस r;

	/* stitch together an UVD destroy msg */
	ग_लिखोl(cpu_to_le32(0x00000de4), &msg[0]);
	ग_लिखोl(cpu_to_le32(0x00000002), &msg[1]);
	ग_लिखोl(cpu_to_le32(handle), &msg[2]);
	ग_लिखोl(0x0, &msg[3]);
	क्रम (i = 4; i < 1024; ++i)
		ग_लिखोl(0x0, &msg[i]);

	r = radeon_uvd_send_msg(rdev, ring, addr, fence);
	radeon_bo_unreserve(rdev->uvd.vcpu_bo);
	वापस r;
पूर्ण

/**
 * radeon_uvd_count_handles - count number of खोलो streams
 *
 * @rdev: radeon_device poपूर्णांकer
 * @sd: number of SD streams
 * @hd: number of HD streams
 *
 * Count the number of खोलो SD/HD streams as a hपूर्णांक क्रम घातer mangement
 */
अटल व्योम radeon_uvd_count_handles(काष्ठा radeon_device *rdev,
				     अचिन्हित *sd, अचिन्हित *hd)
अणु
	अचिन्हित i;

	*sd = 0;
	*hd = 0;

	क्रम (i = 0; i < rdev->uvd.max_handles; ++i) अणु
		अगर (!atomic_पढ़ो(&rdev->uvd.handles[i]))
			जारी;

		अगर (rdev->uvd.img_size[i] >= 720*576)
			++(*hd);
		अन्यथा
			++(*sd);
	पूर्ण
पूर्ण

अटल व्योम radeon_uvd_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_device *rdev =
		container_of(work, काष्ठा radeon_device, uvd.idle_work.work);

	अगर (radeon_fence_count_emitted(rdev, R600_RING_TYPE_UVD_INDEX) == 0) अणु
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			radeon_uvd_count_handles(rdev, &rdev->pm.dpm.sd,
						 &rdev->pm.dpm.hd);
			radeon_dpm_enable_uvd(rdev, false);
		पूर्ण अन्यथा अणु
			radeon_set_uvd_घड़ीs(rdev, 0, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&rdev->uvd.idle_work,
				      msecs_to_jअगरfies(UVD_IDLE_TIMEOUT_MS));
	पूर्ण
पूर्ण

व्योम radeon_uvd_note_usage(काष्ठा radeon_device *rdev)
अणु
	bool streams_changed = false;
	bool set_घड़ीs = !cancel_delayed_work_sync(&rdev->uvd.idle_work);
	set_घड़ीs &= schedule_delayed_work(&rdev->uvd.idle_work,
					    msecs_to_jअगरfies(UVD_IDLE_TIMEOUT_MS));

	अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
		अचिन्हित hd = 0, sd = 0;
		radeon_uvd_count_handles(rdev, &sd, &hd);
		अगर ((rdev->pm.dpm.sd != sd) ||
		    (rdev->pm.dpm.hd != hd)) अणु
			rdev->pm.dpm.sd = sd;
			rdev->pm.dpm.hd = hd;
			/* disable this क्रम now */
			/*streams_changed = true;*/
		पूर्ण
	पूर्ण

	अगर (set_घड़ीs || streams_changed) अणु
		अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
			radeon_dpm_enable_uvd(rdev, true);
		पूर्ण अन्यथा अणु
			radeon_set_uvd_घड़ीs(rdev, 53300, 40000);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित radeon_uvd_calc_upll_post_भाग(अचिन्हित vco_freq,
					      अचिन्हित target_freq,
					      अचिन्हित pd_min,
					      अचिन्हित pd_even)
अणु
	अचिन्हित post_भाग = vco_freq / target_freq;

	/* adjust to post भागider minimum value */
	अगर (post_भाग < pd_min)
		post_भाग = pd_min;

	/* we alway need a frequency less than or equal the target */
	अगर ((vco_freq / post_भाग) > target_freq)
		post_भाग += 1;

	/* post भागiders above a certain value must be even */
	अगर (post_भाग > pd_even && post_भाग % 2)
		post_भाग += 1;

	वापस post_भाग;
पूर्ण

/**
 * radeon_uvd_calc_upll_भागiders - calc UPLL घड़ी भागiders
 *
 * @rdev: radeon_device poपूर्णांकer
 * @vclk: wanted VCLK
 * @dclk: wanted DCLK
 * @vco_min: minimum VCO frequency
 * @vco_max: maximum VCO frequency
 * @fb_factor: factor to multiply vco freq with
 * @fb_mask: limit and biपंचांगask क्रम feedback भागider
 * @pd_min: post भागider minimum
 * @pd_max: post भागider maximum
 * @pd_even: post भागider must be even above this value
 * @optimal_fb_भाग: resulting feedback भागider
 * @optimal_vclk_भाग: resulting vclk post भागider
 * @optimal_dclk_भाग: resulting dclk post भागider
 *
 * Calculate भागiders क्रम UVDs UPLL (R6xx-SI, except APUs).
 * Returns zero on success -EINVAL on error.
 */
पूर्णांक radeon_uvd_calc_upll_भागiders(काष्ठा radeon_device *rdev,
				  अचिन्हित vclk, अचिन्हित dclk,
				  अचिन्हित vco_min, अचिन्हित vco_max,
				  अचिन्हित fb_factor, अचिन्हित fb_mask,
				  अचिन्हित pd_min, अचिन्हित pd_max,
				  अचिन्हित pd_even,
				  अचिन्हित *optimal_fb_भाग,
				  अचिन्हित *optimal_vclk_भाग,
				  अचिन्हित *optimal_dclk_भाग)
अणु
	अचिन्हित vco_freq, ref_freq = rdev->घड़ी.spll.reference_freq;

	/* start off with something large */
	अचिन्हित optimal_score = ~0;

	/* loop through vco from low to high */
	vco_min = max(max(vco_min, vclk), dclk);
	क्रम (vco_freq = vco_min; vco_freq <= vco_max; vco_freq += 100) अणु

		uपूर्णांक64_t fb_भाग = (uपूर्णांक64_t)vco_freq * fb_factor;
		अचिन्हित vclk_भाग, dclk_भाग, score;

		करो_भाग(fb_भाग, ref_freq);

		/* fb भाग out of range ? */
		अगर (fb_भाग > fb_mask)
			अवरोध; /* it can oly get worse */

		fb_भाग &= fb_mask;

		/* calc vclk भागider with current vco freq */
		vclk_भाग = radeon_uvd_calc_upll_post_भाग(vco_freq, vclk,
							 pd_min, pd_even);
		अगर (vclk_भाग > pd_max)
			अवरोध; /* vco is too big, it has to stop */

		/* calc dclk भागider with current vco freq */
		dclk_भाग = radeon_uvd_calc_upll_post_भाग(vco_freq, dclk,
							 pd_min, pd_even);
		अगर (dclk_भाग > pd_max)
			अवरोध; /* vco is too big, it has to stop */

		/* calc score with current vco freq */
		score = vclk - (vco_freq / vclk_भाग) + dclk - (vco_freq / dclk_भाग);

		/* determine अगर this vco setting is better than current optimal settings */
		अगर (score < optimal_score) अणु
			*optimal_fb_भाग = fb_भाग;
			*optimal_vclk_भाग = vclk_भाग;
			*optimal_dclk_भाग = dclk_भाग;
			optimal_score = score;
			अगर (optimal_score == 0)
				अवरोध; /* it can't get better than this */
		पूर्ण
	पूर्ण

	/* did we found a valid setup ? */
	अगर (optimal_score == ~0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक radeon_uvd_send_upll_ctlreq(काष्ठा radeon_device *rdev,
				अचिन्हित cg_upll_func_cntl)
अणु
	अचिन्हित i;

	/* make sure UPLL_CTLREQ is deनिश्चितed */
	WREG32_P(cg_upll_func_cntl, 0, ~UPLL_CTLREQ_MASK);

	mdelay(10);

	/* निश्चित UPLL_CTLREQ */
	WREG32_P(cg_upll_func_cntl, UPLL_CTLREQ_MASK, ~UPLL_CTLREQ_MASK);

	/* रुको क्रम CTLACK and CTLACK2 to get निश्चितed */
	क्रम (i = 0; i < 100; ++i) अणु
		uपूर्णांक32_t mask = UPLL_CTLACK_MASK | UPLL_CTLACK2_MASK;
		अगर ((RREG32(cg_upll_func_cntl) & mask) == mask)
			अवरोध;
		mdelay(10);
	पूर्ण

	/* deनिश्चित UPLL_CTLREQ */
	WREG32_P(cg_upll_func_cntl, 0, ~UPLL_CTLREQ_MASK);

	अगर (i == 100) अणु
		DRM_ERROR("Timeout setting UVD clocks!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
