<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
#समावेश <linux/firmware.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_gfx.h"
#समावेश "amdgpu_rlc.h"

/**
 * amdgpu_gfx_rlc_enter_safe_mode - Set RLC पूर्णांकo safe mode
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set RLC enter पूर्णांकo safe mode अगर RLC is enabled and haven't in safe mode.
 */
व्योम amdgpu_gfx_rlc_enter_safe_mode(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->gfx.rlc.in_safe_mode)
		वापस;

	/* अगर RLC is not enabled, करो nothing */
	अगर (!adev->gfx.rlc.funcs->is_rlc_enabled(adev))
		वापस;

	अगर (adev->cg_flags &
	    (AMD_CG_SUPPORT_GFX_CGCG | AMD_CG_SUPPORT_GFX_MGCG |
	     AMD_CG_SUPPORT_GFX_3D_CGCG)) अणु
		adev->gfx.rlc.funcs->set_safe_mode(adev);
		adev->gfx.rlc.in_safe_mode = true;
	पूर्ण
पूर्ण

/**
 * amdgpu_gfx_rlc_निकास_safe_mode - Set RLC out of safe mode
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Set RLC निकास safe mode अगर RLC is enabled and have entered पूर्णांकo safe mode.
 */
व्योम amdgpu_gfx_rlc_निकास_safe_mode(काष्ठा amdgpu_device *adev)
अणु
	अगर (!(adev->gfx.rlc.in_safe_mode))
		वापस;

	/* अगर RLC is not enabled, करो nothing */
	अगर (!adev->gfx.rlc.funcs->is_rlc_enabled(adev))
		वापस;

	अगर (adev->cg_flags &
	    (AMD_CG_SUPPORT_GFX_CGCG | AMD_CG_SUPPORT_GFX_MGCG |
	     AMD_CG_SUPPORT_GFX_3D_CGCG)) अणु
		adev->gfx.rlc.funcs->unset_safe_mode(adev);
		adev->gfx.rlc.in_safe_mode = false;
	पूर्ण
पूर्ण

/**
 * amdgpu_gfx_rlc_init_sr - Init save restore block
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @dws: the size of save restore block
 *
 * Allocate and setup value to save restore block of rlc.
 * Returns 0 on succeess or negative error code अगर allocate failed.
 */
पूर्णांक amdgpu_gfx_rlc_init_sr(काष्ठा amdgpu_device *adev, u32 dws)
अणु
	स्थिर u32 *src_ptr;
	अस्थिर u32 *dst_ptr;
	u32 i;
	पूर्णांक r;

	/* allocate save restore block */
	r = amdgpu_bo_create_reserved(adev, dws * 4, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->gfx.rlc.save_restore_obj,
				      &adev->gfx.rlc.save_restore_gpu_addr,
				      (व्योम **)&adev->gfx.rlc.sr_ptr);
	अगर (r) अणु
		dev_warn(adev->dev, "(%d) create RLC sr bo failed\n", r);
		amdgpu_gfx_rlc_fini(adev);
		वापस r;
	पूर्ण

	/* ग_लिखो the sr buffer */
	src_ptr = adev->gfx.rlc.reg_list;
	dst_ptr = adev->gfx.rlc.sr_ptr;
	क्रम (i = 0; i < adev->gfx.rlc.reg_list_size; i++)
		dst_ptr[i] = cpu_to_le32(src_ptr[i]);
	amdgpu_bo_kunmap(adev->gfx.rlc.save_restore_obj);
	amdgpu_bo_unreserve(adev->gfx.rlc.save_restore_obj);

	वापस 0;
पूर्ण

/**
 * amdgpu_gfx_rlc_init_csb - Init clear state block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate and setup value to clear state block of rlc.
 * Returns 0 on succeess or negative error code अगर allocate failed.
 */
पूर्णांक amdgpu_gfx_rlc_init_csb(काष्ठा amdgpu_device *adev)
अणु
	u32 dws;
	पूर्णांक r;

	/* allocate clear state block */
	adev->gfx.rlc.clear_state_size = dws = adev->gfx.rlc.funcs->get_csb_size(adev);
	r = amdgpu_bo_create_kernel(adev, dws * 4, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->gfx.rlc.clear_state_obj,
				      &adev->gfx.rlc.clear_state_gpu_addr,
				      (व्योम **)&adev->gfx.rlc.cs_ptr);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to create rlc csb bo\n", r);
		amdgpu_gfx_rlc_fini(adev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_gfx_rlc_init_cpt - Init cp table
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate and setup value to cp table of rlc.
 * Returns 0 on succeess or negative error code अगर allocate failed.
 */
पूर्णांक amdgpu_gfx_rlc_init_cpt(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = amdgpu_bo_create_reserved(adev, adev->gfx.rlc.cp_table_size,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->gfx.rlc.cp_table_obj,
				      &adev->gfx.rlc.cp_table_gpu_addr,
				      (व्योम **)&adev->gfx.rlc.cp_table_ptr);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to create cp table bo\n", r);
		amdgpu_gfx_rlc_fini(adev);
		वापस r;
	पूर्ण

	/* set up the cp table */
	amdgpu_gfx_rlc_setup_cp_table(adev);
	amdgpu_bo_kunmap(adev->gfx.rlc.cp_table_obj);
	amdgpu_bo_unreserve(adev->gfx.rlc.cp_table_obj);

	वापस 0;
पूर्ण

/**
 * amdgpu_gfx_rlc_setup_cp_table - setup cp the buffer of cp table
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Write cp firmware data पूर्णांकo cp table.
 */
व्योम amdgpu_gfx_rlc_setup_cp_table(काष्ठा amdgpu_device *adev)
अणु
	स्थिर __le32 *fw_data;
	अस्थिर u32 *dst_ptr;
	पूर्णांक me, i, max_me;
	u32 bo_offset = 0;
	u32 table_offset, table_size;

	max_me = adev->gfx.rlc.funcs->get_cp_table_num(adev);

	/* ग_लिखो the cp table buffer */
	dst_ptr = adev->gfx.rlc.cp_table_ptr;
	क्रम (me = 0; me < max_me; me++) अणु
		अगर (me == 0) अणु
			स्थिर काष्ठा gfx_firmware_header_v1_0 *hdr =
				(स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
			fw_data = (स्थिर __le32 *)
				(adev->gfx.ce_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		पूर्ण अन्यथा अगर (me == 1) अणु
			स्थिर काष्ठा gfx_firmware_header_v1_0 *hdr =
				(स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
			fw_data = (स्थिर __le32 *)
				(adev->gfx.pfp_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		पूर्ण अन्यथा अगर (me == 2) अणु
			स्थिर काष्ठा gfx_firmware_header_v1_0 *hdr =
				(स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;
			fw_data = (स्थिर __le32 *)
				(adev->gfx.me_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		पूर्ण अन्यथा अगर (me == 3) अणु
			स्थिर काष्ठा gfx_firmware_header_v1_0 *hdr =
				(स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
			fw_data = (स्थिर __le32 *)
				(adev->gfx.mec_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		पूर्ण अन्यथा  अगर (me == 4) अणु
			स्थिर काष्ठा gfx_firmware_header_v1_0 *hdr =
				(स्थिर काष्ठा gfx_firmware_header_v1_0 *)adev->gfx.mec2_fw->data;
			fw_data = (स्थिर __le32 *)
				(adev->gfx.mec2_fw->data +
				 le32_to_cpu(hdr->header.ucode_array_offset_bytes));
			table_offset = le32_to_cpu(hdr->jt_offset);
			table_size = le32_to_cpu(hdr->jt_size);
		पूर्ण

		क्रम (i = 0; i < table_size; i ++) अणु
			dst_ptr[bo_offset + i] =
				cpu_to_le32(le32_to_cpu(fw_data[table_offset + i]));
		पूर्ण

		bo_offset += table_size;
	पूर्ण
पूर्ण

/**
 * amdgpu_gfx_rlc_fini - Free BO which used क्रम RLC
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Free three BO which is used क्रम rlc_save_restore_block, rlc_clear_state_block
 * and rlc_jump_table_block.
 */
व्योम amdgpu_gfx_rlc_fini(काष्ठा amdgpu_device *adev)
अणु
	/* save restore block */
	अगर (adev->gfx.rlc.save_restore_obj) अणु
		amdgpu_bo_मुक्त_kernel(&adev->gfx.rlc.save_restore_obj,
				      &adev->gfx.rlc.save_restore_gpu_addr,
				      (व्योम **)&adev->gfx.rlc.sr_ptr);
	पूर्ण

	/* clear state block */
	amdgpu_bo_मुक्त_kernel(&adev->gfx.rlc.clear_state_obj,
			      &adev->gfx.rlc.clear_state_gpu_addr,
			      (व्योम **)&adev->gfx.rlc.cs_ptr);

	/* jump table block */
	amdgpu_bo_मुक्त_kernel(&adev->gfx.rlc.cp_table_obj,
			      &adev->gfx.rlc.cp_table_gpu_addr,
			      (व्योम **)&adev->gfx.rlc.cp_table_ptr);
पूर्ण
