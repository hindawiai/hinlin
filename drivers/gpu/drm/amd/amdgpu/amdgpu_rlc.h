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
 *
 */

#अगर_अघोषित __AMDGPU_RLC_H__
#घोषणा __AMDGPU_RLC_H__

#समावेश "clearstate_defs.h"

/* firmware ID used in rlc toc */
प्रकार क्रमागत _FIRMWARE_ID_ अणु
	FIRMWARE_ID_INVALID					= 0,
	FIRMWARE_ID_RLC_G_UCODE					= 1,
	FIRMWARE_ID_RLC_TOC					= 2,
	FIRMWARE_ID_RLCG_SCRATCH                                = 3,
	FIRMWARE_ID_RLC_SRM_ARAM                                = 4,
	FIRMWARE_ID_RLC_SRM_INDEX_ADDR                          = 5,
	FIRMWARE_ID_RLC_SRM_INDEX_DATA                          = 6,
	FIRMWARE_ID_RLC_P_UCODE                                 = 7,
	FIRMWARE_ID_RLC_V_UCODE                                 = 8,
	FIRMWARE_ID_RLX6_UCODE                                  = 9,
	FIRMWARE_ID_RLX6_DRAM_BOOT                              = 10,
	FIRMWARE_ID_GLOBAL_TAP_DELAYS                           = 11,
	FIRMWARE_ID_SE0_TAP_DELAYS                              = 12,
	FIRMWARE_ID_SE1_TAP_DELAYS                              = 13,
	FIRMWARE_ID_GLOBAL_SE0_SE1_SKEW_DELAYS                  = 14,
	FIRMWARE_ID_SDMA0_UCODE                                 = 15,
	FIRMWARE_ID_SDMA0_JT                                    = 16,
	FIRMWARE_ID_SDMA1_UCODE                                 = 17,
	FIRMWARE_ID_SDMA1_JT                                    = 18,
	FIRMWARE_ID_CP_CE                                       = 19,
	FIRMWARE_ID_CP_PFP                                      = 20,
	FIRMWARE_ID_CP_ME                                       = 21,
	FIRMWARE_ID_CP_MEC                                      = 22,
	FIRMWARE_ID_CP_MES                                      = 23,
	FIRMWARE_ID_MES_STACK                                   = 24,
	FIRMWARE_ID_RLC_SRM_DRAM_SR                             = 25,
	FIRMWARE_ID_RLCG_SCRATCH_SR                             = 26,
	FIRMWARE_ID_RLCP_SCRATCH_SR                             = 27,
	FIRMWARE_ID_RLCV_SCRATCH_SR                             = 28,
	FIRMWARE_ID_RLX6_DRAM_SR                                = 29,
	FIRMWARE_ID_SDMA0_PG_CONTEXT                            = 30,
	FIRMWARE_ID_SDMA1_PG_CONTEXT                            = 31,
	FIRMWARE_ID_GLOBAL_MUX_SELECT_RAM                       = 32,
	FIRMWARE_ID_SE0_MUX_SELECT_RAM                          = 33,
	FIRMWARE_ID_SE1_MUX_SELECT_RAM                          = 34,
	FIRMWARE_ID_ACCUM_CTRL_RAM                              = 35,
	FIRMWARE_ID_RLCP_CAM                                    = 36,
	FIRMWARE_ID_RLC_SPP_CAM_EXT                             = 37,
	FIRMWARE_ID_MAX                                         = 38,
पूर्ण FIRMWARE_ID;

प्रकार काष्ठा _RLC_TABLE_OF_CONTENT अणु
	जोड़ अणु
		अचिन्हित पूर्णांक	DW0;
		काष्ठा अणु
			अचिन्हित पूर्णांक	offset		: 25;
			अचिन्हित पूर्णांक	id		: 7;
		पूर्ण;
	पूर्ण;

	जोड़ अणु
		अचिन्हित पूर्णांक	DW1;
		काष्ठा अणु
			अचिन्हित पूर्णांक	load_at_boot		: 1;
			अचिन्हित पूर्णांक	load_at_vddgfx		: 1;
			अचिन्हित पूर्णांक	load_at_reset		: 1;
			अचिन्हित पूर्णांक	memory_destination	: 2;
			अचिन्हित पूर्णांक	vfflr_image_code	: 4;
			अचिन्हित पूर्णांक	load_mode_direct	: 1;
			अचिन्हित पूर्णांक	save_क्रम_vddgfx		: 1;
			अचिन्हित पूर्णांक	save_क्रम_vfflr		: 1;
			अचिन्हित पूर्णांक	reserved		: 1;
			अचिन्हित पूर्णांक	चिन्हित_source		: 1;
			अचिन्हित पूर्णांक	size			: 18;
		पूर्ण;
	पूर्ण;

	जोड़ अणु
		अचिन्हित पूर्णांक	DW2;
		काष्ठा अणु
			अचिन्हित पूर्णांक	indirect_addr_reg	: 16;
			अचिन्हित पूर्णांक	index			: 16;
		पूर्ण;
	पूर्ण;

	जोड़ अणु
		अचिन्हित पूर्णांक	DW3;
		काष्ठा अणु
			अचिन्हित पूर्णांक	indirect_data_reg	: 16;
			अचिन्हित पूर्णांक	indirect_start_offset	: 16;
		पूर्ण;
	पूर्ण;
पूर्ण RLC_TABLE_OF_CONTENT;

#घोषणा RLC_TOC_MAX_SIZE		64

काष्ठा amdgpu_rlc_funcs अणु
	bool (*is_rlc_enabled)(काष्ठा amdgpu_device *adev);
	व्योम (*set_safe_mode)(काष्ठा amdgpu_device *adev);
	व्योम (*unset_safe_mode)(काष्ठा amdgpu_device *adev);
	पूर्णांक  (*init)(काष्ठा amdgpu_device *adev);
	u32  (*get_csb_size)(काष्ठा amdgpu_device *adev);
	व्योम (*get_csb_buffer)(काष्ठा amdgpu_device *adev, अस्थिर u32 *buffer);
	पूर्णांक  (*get_cp_table_num)(काष्ठा amdgpu_device *adev);
	पूर्णांक  (*resume)(काष्ठा amdgpu_device *adev);
	व्योम (*stop)(काष्ठा amdgpu_device *adev);
	व्योम (*reset)(काष्ठा amdgpu_device *adev);
	व्योम (*start)(काष्ठा amdgpu_device *adev);
	व्योम (*update_spm_vmid)(काष्ठा amdgpu_device *adev, अचिन्हित vmid);
	व्योम (*rlcg_wreg)(काष्ठा amdgpu_device *adev, u32 offset, u32 v, u32 flag);
	u32 (*rlcg_rreg)(काष्ठा amdgpu_device *adev, u32 offset, u32 flag);
	bool (*is_rlcg_access_range)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg);
पूर्ण;

काष्ठा amdgpu_rlc अणु
	/* क्रम घातer gating */
	काष्ठा amdgpu_bo        *save_restore_obj;
	uपूर्णांक64_t                save_restore_gpu_addr;
	अस्थिर uपूर्णांक32_t       *sr_ptr;
	स्थिर u32               *reg_list;
	u32                     reg_list_size;
	/* क्रम clear state */
	काष्ठा amdgpu_bo        *clear_state_obj;
	uपूर्णांक64_t                clear_state_gpu_addr;
	अस्थिर uपूर्णांक32_t       *cs_ptr;
	स्थिर काष्ठा cs_section_def   *cs_data;
	u32                     clear_state_size;
	/* क्रम cp tables */
	काष्ठा amdgpu_bo        *cp_table_obj;
	uपूर्णांक64_t                cp_table_gpu_addr;
	अस्थिर uपूर्णांक32_t       *cp_table_ptr;
	u32                     cp_table_size;

	/* safe mode क्रम updating CG/PG state */
	bool in_safe_mode;
	स्थिर काष्ठा amdgpu_rlc_funcs *funcs;

	/* क्रम firmware data */
	u32 save_and_restore_offset;
	u32 clear_state_descriptor_offset;
	u32 avail_scratch_ram_locations;
	u32 reg_restore_list_size;
	u32 reg_list_क्रमmat_start;
	u32 reg_list_क्रमmat_separate_start;
	u32 starting_offsets_start;
	u32 reg_list_क्रमmat_size_bytes;
	u32 reg_list_size_bytes;
	u32 reg_list_क्रमmat_direct_reg_list_length;
	u32 save_restore_list_cntl_size_bytes;
	u32 save_restore_list_gpm_size_bytes;
	u32 save_restore_list_srm_size_bytes;
	u32 rlc_iram_ucode_size_bytes;
	u32 rlc_dram_ucode_size_bytes;

	u32 *रेजिस्टर_list_क्रमmat;
	u32 *रेजिस्टर_restore;
	u8 *save_restore_list_cntl;
	u8 *save_restore_list_gpm;
	u8 *save_restore_list_srm;
	u8 *rlc_iram_ucode;
	u8 *rlc_dram_ucode;

	bool is_rlc_v2_1;

	/* क्रम rlc स्वतःload */
	काष्ठा amdgpu_bo	*rlc_स्वतःload_bo;
	u64			rlc_स्वतःload_gpu_addr;
	व्योम			*rlc_स्वतःload_ptr;

	/* rlc toc buffer */
	काष्ठा amdgpu_bo	*rlc_toc_bo;
	uपूर्णांक64_t		rlc_toc_gpu_addr;
	व्योम			*rlc_toc_buf;
पूर्ण;

व्योम amdgpu_gfx_rlc_enter_safe_mode(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gfx_rlc_निकास_safe_mode(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gfx_rlc_init_sr(काष्ठा amdgpu_device *adev, u32 dws);
पूर्णांक amdgpu_gfx_rlc_init_csb(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gfx_rlc_init_cpt(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gfx_rlc_setup_cp_table(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gfx_rlc_fini(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
