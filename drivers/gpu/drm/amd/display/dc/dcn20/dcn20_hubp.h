<शैली गुरु>
/*
 * Copyright 2012-17 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#अगर_अघोषित __DC_MEM_INPUT_DCN20_H__
#घोषणा __DC_MEM_INPUT_DCN20_H__

#समावेश "../dcn10/dcn10_hubp.h"

#घोषणा TO_DCN20_HUBP(hubp)\
	container_of(hubp, काष्ठा dcn20_hubp, base)

#घोषणा HUBP_REG_LIST_DCN2_COMMON(id)\
	HUBP_REG_LIST_DCN(id),\
	HUBP_REG_LIST_DCN_VM(id),\
	SRI(PREFETCH_SETTINGS, HUBPREQ, id),\
	SRI(PREFETCH_SETTINGS_C, HUBPREQ, id),\
	SRI(DCN_VM_SYSTEM_APERTURE_LOW_ADDR, HUBPREQ, id),\
	SRI(DCN_VM_SYSTEM_APERTURE_HIGH_ADDR, HUBPREQ, id),\
	SRI(CURSOR_SETTINGS, HUBPREQ, id), \
	SRI(CURSOR_SURFACE_ADDRESS_HIGH, CURSOR0_, id), \
	SRI(CURSOR_SURFACE_ADDRESS, CURSOR0_, id), \
	SRI(CURSOR_SIZE, CURSOR0_, id), \
	SRI(CURSOR_CONTROL, CURSOR0_, id), \
	SRI(CURSOR_POSITION, CURSOR0_, id), \
	SRI(CURSOR_HOT_SPOT, CURSOR0_, id), \
	SRI(CURSOR_DST_OFFSET, CURSOR0_, id), \
	SRI(DMDATA_ADDRESS_HIGH, CURSOR0_, id), \
	SRI(DMDATA_ADDRESS_LOW, CURSOR0_, id), \
	SRI(DMDATA_CNTL, CURSOR0_, id), \
	SRI(DMDATA_SW_CNTL, CURSOR0_, id), \
	SRI(DMDATA_QOS_CNTL, CURSOR0_, id), \
	SRI(DMDATA_SW_DATA, CURSOR0_, id), \
	SRI(DMDATA_STATUS, CURSOR0_, id),\
	SRI(FLIP_PARAMETERS_0, HUBPREQ, id),\
	SRI(FLIP_PARAMETERS_1, HUBPREQ, id),\
	SRI(FLIP_PARAMETERS_2, HUBPREQ, id),\
	SRI(DCN_CUR1_TTU_CNTL0, HUBPREQ, id),\
	SRI(DCN_CUR1_TTU_CNTL1, HUBPREQ, id),\
	SRI(DCSURF_FLIP_CONTROL2, HUBPREQ, id), \
	SRI(VMID_SETTINGS_0, HUBPREQ, id)

#घोषणा HUBP_REG_LIST_DCN20(id)\
	HUBP_REG_LIST_DCN2_COMMON(id),\
	SR(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB),\
	SR(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB)

#घोषणा HUBP_MASK_SH_LIST_DCN2_SHARE_COMMON(mask_sh)\
	HUBP_MASK_SH_LIST_DCN_SHARE_COMMON(mask_sh),\
	HUBP_MASK_SH_LIST_DCN_VM(mask_sh),\
	HUBP_SF(HUBP0_DCSURF_SURFACE_CONFIG, ROTATION_ANGLE, mask_sh),\
	HUBP_SF(HUBP0_DCSURF_SURFACE_CONFIG, H_MIRROR_EN, mask_sh),\
	HUBP_SF(HUBPREQ0_PREFETCH_SETTINGS, DST_Y_PREFETCH, mask_sh),\
	HUBP_SF(HUBPREQ0_PREFETCH_SETTINGS, VRATIO_PREFETCH, mask_sh),\
	HUBP_SF(HUBPREQ0_PREFETCH_SETTINGS_C, VRATIO_PREFETCH_C, mask_sh),\
	HUBP_SF(HUBPREQ0_DCN_VM_SYSTEM_APERTURE_LOW_ADDR, MC_VM_SYSTEM_APERTURE_LOW_ADDR, mask_sh),\
	HUBP_SF(HUBPREQ0_DCN_VM_SYSTEM_APERTURE_HIGH_ADDR, MC_VM_SYSTEM_APERTURE_HIGH_ADDR, mask_sh),\
	HUBP_SF(HUBPREQ0_CURSOR_SETTINGS, CURSOR0_DST_Y_OFFSET, mask_sh), \
	HUBP_SF(HUBPREQ0_CURSOR_SETTINGS, CURSOR0_CHUNK_HDL_ADJUST, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_SURFACE_ADDRESS_HIGH, CURSOR_SURFACE_ADDRESS_HIGH, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_SURFACE_ADDRESS, CURSOR_SURFACE_ADDRESS, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_SIZE, CURSOR_WIDTH, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_SIZE, CURSOR_HEIGHT, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_MODE, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_2X_MAGNIFY, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_PITCH, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_LINES_PER_CHUNK, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_CONTROL, CURSOR_ENABLE, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_POSITION, CURSOR_X_POSITION, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_POSITION, CURSOR_Y_POSITION, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_HOT_SPOT, CURSOR_HOT_SPOT_X, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_HOT_SPOT, CURSOR_HOT_SPOT_Y, mask_sh), \
	HUBP_SF(CURSOR0_0_CURSOR_DST_OFFSET, CURSOR_DST_X_OFFSET, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_ADDRESS_HIGH, DMDATA_ADDRESS_HIGH, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_CNTL, DMDATA_MODE, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_CNTL, DMDATA_UPDATED, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_CNTL, DMDATA_REPEAT, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_CNTL, DMDATA_SIZE, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_SW_CNTL, DMDATA_SW_UPDATED, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_SW_CNTL, DMDATA_SW_REPEAT, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_SW_CNTL, DMDATA_SW_SIZE, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_QOS_CNTL, DMDATA_QOS_MODE, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_QOS_CNTL, DMDATA_QOS_LEVEL, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_QOS_CNTL, DMDATA_DL_DELTA, mask_sh), \
	HUBP_SF(CURSOR0_0_DMDATA_STATUS, DMDATA_DONE, mask_sh),\
	HUBP_SF(HUBPREQ0_FLIP_PARAMETERS_0, DST_Y_PER_VM_FLIP, mask_sh),\
	HUBP_SF(HUBPREQ0_FLIP_PARAMETERS_0, DST_Y_PER_ROW_FLIP, mask_sh),\
	HUBP_SF(HUBPREQ0_FLIP_PARAMETERS_1, REFCYC_PER_PTE_GROUP_FLIP_L, mask_sh),\
	HUBP_SF(HUBPREQ0_FLIP_PARAMETERS_2, REFCYC_PER_META_CHUNK_FLIP_L, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_CNTL, HUBP_VREADY_AT_OR_AFTER_VSYNC, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_CNTL, HUBP_DISABLE_STOP_DATA_DURING_VM, mask_sh),\
	HUBP_SF(HUBPREQ0_DCSURF_FLIP_CONTROL, HUBPREQ_MASTER_UPDATE_LOCK_STATUS, mask_sh),\
	HUBP_SF(HUBPREQ0_DCSURF_FLIP_CONTROL2, SURFACE_GSL_ENABLE, mask_sh),\
	HUBP_SF(HUBPREQ0_DCSURF_FLIP_CONTROL2, SURFACE_TRIPLE_BUFFER_ENABLE, mask_sh),\
	HUBP_SF(HUBPREQ0_VMID_SETTINGS_0, VMID, mask_sh)

/*DCN2.x and DCN1.x*/
#घोषणा HUBP_MASK_SH_LIST_DCN2_COMMON(mask_sh)\
	HUBP_MASK_SH_LIST_DCN2_SHARE_COMMON(mask_sh),\
	HUBP_SF(HUBP0_DCSURF_TILING_CONFIG, RB_ALIGNED, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_REQ_SIZE_CONFIG, MPTE_GROUP_SIZE, mask_sh),\
	HUBP_SF(HUBP0_DCHUBP_REQ_SIZE_CONFIG_C, MPTE_GROUP_SIZE_C, mask_sh)

/*DCN2.0 specअगरic*/
#घोषणा HUBP_MASK_SH_LIST_DCN20(mask_sh)\
	HUBP_MASK_SH_LIST_DCN2_COMMON(mask_sh),\
	HUBP_SF(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB, DCN_VM_SYSTEM_APERTURE_DEFAULT_SYSTEM, mask_sh),\
	HUBP_SF(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB, DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB, mask_sh),\
	HUBP_SF(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB, DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB, mask_sh)

/*DCN2.x */
#घोषणा DCN2_HUBP_REG_COMMON_VARIABLE_LIST \
	HUBP_COMMON_REG_VARIABLE_LIST; \
	uपूर्णांक32_t DMDATA_ADDRESS_HIGH; \
	uपूर्णांक32_t DMDATA_ADDRESS_LOW; \
	uपूर्णांक32_t DMDATA_CNTL; \
	uपूर्णांक32_t DMDATA_SW_CNTL; \
	uपूर्णांक32_t DMDATA_QOS_CNTL; \
	uपूर्णांक32_t DMDATA_SW_DATA; \
	uपूर्णांक32_t DMDATA_STATUS;\
	uपूर्णांक32_t DCSURF_FLIP_CONTROL2;\
	uपूर्णांक32_t FLIP_PARAMETERS_0;\
	uपूर्णांक32_t FLIP_PARAMETERS_1;\
	uपूर्णांक32_t FLIP_PARAMETERS_2;\
	uपूर्णांक32_t DCN_CUR1_TTU_CNTL0;\
	uपूर्णांक32_t DCN_CUR1_TTU_CNTL1;\
	uपूर्णांक32_t VMID_SETTINGS_0


#घोषणा DCN21_HUBP_REG_COMMON_VARIABLE_LIST \
	DCN2_HUBP_REG_COMMON_VARIABLE_LIST; \
	uपूर्णांक32_t FLIP_PARAMETERS_3;\
	uपूर्णांक32_t FLIP_PARAMETERS_4;\
	uपूर्णांक32_t FLIP_PARAMETERS_5;\
	uपूर्णांक32_t FLIP_PARAMETERS_6;\
	uपूर्णांक32_t VBLANK_PARAMETERS_5;\
	uपूर्णांक32_t VBLANK_PARAMETERS_6

#घोषणा DCN30_HUBP_REG_COMMON_VARIABLE_LIST \
	DCN21_HUBP_REG_COMMON_VARIABLE_LIST;\
	uपूर्णांक32_t DCN_DMDATA_VM_CNTL

#घोषणा DCN2_HUBP_REG_FIELD_VARIABLE_LIST(type) \
	DCN_HUBP_REG_FIELD_BASE_LIST(type); \
	type DMDATA_ADDRESS_HIGH;\
	type DMDATA_MODE;\
	type DMDATA_UPDATED;\
	type DMDATA_REPEAT;\
	type DMDATA_SIZE;\
	type DMDATA_SW_UPDATED;\
	type DMDATA_SW_REPEAT;\
	type DMDATA_SW_SIZE;\
	type DMDATA_QOS_MODE;\
	type DMDATA_QOS_LEVEL;\
	type DMDATA_DL_DELTA;\
	type DMDATA_DONE;\
	type DST_Y_PER_VM_FLIP;\
	type DST_Y_PER_ROW_FLIP;\
	type REFCYC_PER_PTE_GROUP_FLIP_L;\
	type REFCYC_PER_META_CHUNK_FLIP_L;\
	type HUBP_VREADY_AT_OR_AFTER_VSYNC;\
	type HUBP_DISABLE_STOP_DATA_DURING_VM;\
	type HUBPREQ_MASTER_UPDATE_LOCK_STATUS;\
	type SURFACE_GSL_ENABLE;\
	type SURFACE_TRIPLE_BUFFER_ENABLE;\
	type VMID

#घोषणा DCN21_HUBP_REG_FIELD_VARIABLE_LIST(type) \
	DCN2_HUBP_REG_FIELD_VARIABLE_LIST(type);\
	type REFCYC_PER_VM_GROUP_FLIP;\
	type REFCYC_PER_VM_REQ_FLIP;\
	type REFCYC_PER_VM_GROUP_VBLANK;\
	type REFCYC_PER_VM_REQ_VBLANK;\
	type REFCYC_PER_PTE_GROUP_FLIP_C; \
	type REFCYC_PER_META_CHUNK_FLIP_C; \
	type VM_GROUP_SIZE

#घोषणा DCN30_HUBP_REG_FIELD_VARIABLE_LIST(type) \
	DCN21_HUBP_REG_FIELD_VARIABLE_LIST(type);\
	type PRIMARY_SURFACE_DCC_IND_BLK;\
	type SECONDARY_SURFACE_DCC_IND_BLK;\
	type PRIMARY_SURFACE_DCC_IND_BLK_C;\
	type SECONDARY_SURFACE_DCC_IND_BLK_C;\
	type ALPHA_PLANE_EN;\
	type REFCYC_PER_VM_DMDATA;\
	type DMDATA_VM_FAULT_STATUS;\
	type DMDATA_VM_FAULT_STATUS_CLEAR; \
	type DMDATA_VM_UNDERFLOW_STATUS;\
	type DMDATA_VM_LATE_STATUS;\
	type DMDATA_VM_UNDERFLOW_STATUS_CLEAR; \
	type DMDATA_VM_DONE; \
	type CROSSBAR_SRC_Y_G; \
	type CROSSBAR_SRC_ALPHA; \
	type PACK_3TO2_ELEMENT_DISABLE; \
	type ROW_TTU_MODE; \
	type NUM_PKRS

काष्ठा dcn_hubp2_रेजिस्टरs अणु
	DCN30_HUBP_REG_COMMON_VARIABLE_LIST;
पूर्ण;

काष्ठा dcn_hubp2_shअगरt अणु
	DCN30_HUBP_REG_FIELD_VARIABLE_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn_hubp2_mask अणु
	DCN30_HUBP_REG_FIELD_VARIABLE_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn20_hubp अणु
	काष्ठा hubp base;
	काष्ठा dcn_hubp_state state;
	स्थिर काष्ठा dcn_hubp2_रेजिस्टरs *hubp_regs;
	स्थिर काष्ठा dcn_hubp2_shअगरt *hubp_shअगरt;
	स्थिर काष्ठा dcn_hubp2_mask *hubp_mask;
पूर्ण;

bool hubp2_स्थिरruct(
		काष्ठा dcn20_hubp *hubp2,
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t inst,
		स्थिर काष्ठा dcn_hubp2_रेजिस्टरs *hubp_regs,
		स्थिर काष्ठा dcn_hubp2_shअगरt *hubp_shअगरt,
		स्थिर काष्ठा dcn_hubp2_mask *hubp_mask);

व्योम hubp2_setup_पूर्णांकerdependent(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr);

व्योम hubp2_vपढ़ोy_at_or_After_vsync(काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_pipe_dest_params_st *pipe_dest);

व्योम hubp2_cursor_set_attributes(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_cursor_attributes *attr);

व्योम hubp2_set_vm_प्रणाली_aperture_settings(काष्ठा hubp *hubp,
		काष्ठा vm_प्रणाली_aperture_param *apt);

क्रमागत cursor_lines_per_chunk hubp2_get_lines_per_chunk(
		अचिन्हित पूर्णांक cursor_width,
		क्रमागत dc_cursor_color_क्रमmat cursor_mode);

व्योम hubp2_dmdata_set_attributes(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_dmdata_attributes *attr);

व्योम hubp2_dmdata_load(
		काष्ठा hubp *hubp,
		uपूर्णांक32_t dmdata_sw_size,
		स्थिर uपूर्णांक32_t *dmdata_sw_data);

bool hubp2_dmdata_status_करोne(काष्ठा hubp *hubp);

व्योम hubp2_enable_triplebuffer(
		काष्ठा hubp *hubp,
		bool enable);

bool hubp2_is_triplebuffer_enabled(
		काष्ठा hubp *hubp);

व्योम hubp2_set_flip_control_surface_gsl(काष्ठा hubp *hubp, bool enable);

व्योम hubp2_program_deadline(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr);

bool hubp2_program_surface_flip_and_addr(
	काष्ठा hubp *hubp,
	स्थिर काष्ठा dc_plane_address *address,
	bool flip_immediate);

व्योम hubp2_dcc_control(काष्ठा hubp *hubp, bool enable,
		क्रमागत hubp_ind_block_size independent_64b_blks);

व्योम hubp2_program_size(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	स्थिर काष्ठा plane_size *plane_size,
	काष्ठा dc_plane_dcc_param *dcc);

व्योम hubp2_program_rotation(
	काष्ठा hubp *hubp,
	क्रमागत dc_rotation_angle rotation,
	bool horizontal_mirror);

व्योम hubp2_program_pixel_क्रमmat(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat);

व्योम hubp2_program_surface_config(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	जोड़ dc_tiling_info *tiling_info,
	काष्ठा plane_size *plane_size,
	क्रमागत dc_rotation_angle rotation,
	काष्ठा dc_plane_dcc_param *dcc,
	bool horizontal_mirror,
	अचिन्हित पूर्णांक compat_level);

bool hubp2_is_flip_pending(काष्ठा hubp *hubp);

व्योम hubp2_set_blank(काष्ठा hubp *hubp, bool blank);

व्योम hubp2_cursor_set_position(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_cursor_position *pos,
		स्थिर काष्ठा dc_cursor_mi_param *param);

व्योम hubp2_clk_cntl(काष्ठा hubp *hubp, bool enable);

व्योम hubp2_vtg_sel(काष्ठा hubp *hubp, uपूर्णांक32_t otg_inst);

व्योम hubp2_clear_underflow(काष्ठा hubp *hubp);

व्योम hubp2_पढ़ो_state_common(काष्ठा hubp *hubp);

व्योम hubp2_पढ़ो_state(काष्ठा hubp *hubp);

#पूर्ण_अगर /* __DC_MEM_INPUT_DCN20_H__ */


