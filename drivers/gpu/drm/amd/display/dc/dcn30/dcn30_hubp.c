<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#समावेश "dcn30_hubp.h"

#समावेश "dm_services.h"
#समावेश "dce_calcs.h"
#समावेश "reg_helper.h"
#समावेश "basics/conversion.h"
#समावेश "dcn20/dcn20_hubp.h"
#समावेश "dcn21/dcn21_hubp.h"

#घोषणा REG(reg)\
	hubp2->hubp_regs->reg

#घोषणा CTX \
	hubp2->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubp2->hubp_shअगरt->field_name, hubp2->hubp_mask->field_name

व्योम hubp3_set_vm_प्रणाली_aperture_settings(काष्ठा hubp *hubp,
		काष्ठा vm_प्रणाली_aperture_param *apt)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	PHYSICAL_ADDRESS_LOC mc_vm_apt_शेष;
	PHYSICAL_ADDRESS_LOC mc_vm_apt_low;
	PHYSICAL_ADDRESS_LOC mc_vm_apt_high;

	// The क्रमmat of शेष addr is 48:12 of the 48 bit addr
	mc_vm_apt_शेष.quad_part = apt->sys_शेष.quad_part >> 12;

	// The क्रमmat of high/low are 48:18 of the 48 bit addr
	mc_vm_apt_low.quad_part = apt->sys_low.quad_part >> 18;
	mc_vm_apt_high.quad_part = apt->sys_high.quad_part >> 18;

	REG_SET(DCN_VM_SYSTEM_APERTURE_LOW_ADDR, 0,
			MC_VM_SYSTEM_APERTURE_LOW_ADDR, mc_vm_apt_low.quad_part);

	REG_SET(DCN_VM_SYSTEM_APERTURE_HIGH_ADDR, 0,
			MC_VM_SYSTEM_APERTURE_HIGH_ADDR, mc_vm_apt_high.quad_part);

	REG_SET_2(DCN_VM_MX_L1_TLB_CNTL, 0,
			ENABLE_L1_TLB, 1,
			SYSTEM_ACCESS_MODE, 0x3);
पूर्ण

bool hubp3_program_surface_flip_and_addr(
	काष्ठा hubp *hubp,
	स्थिर काष्ठा dc_plane_address *address,
	bool flip_immediate)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	//program flip type
	REG_UPDATE(DCSURF_FLIP_CONTROL,
			SURFACE_FLIP_TYPE, flip_immediate);

	// Program VMID reg
	अगर (flip_immediate == 0)
		REG_UPDATE(VMID_SETTINGS_0,
			VMID, address->vmid);

	अगर (address->type == PLN_ADDR_TYPE_GRPH_STEREO) अणु
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_MODE_FOR_STEREOSYNC, 0x1);
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_IN_STEREOSYNC, 0x1);

	पूर्ण अन्यथा अणु
		// turn off stereo अगर not in stereo
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_MODE_FOR_STEREOSYNC, 0x0);
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_FLIP_IN_STEREOSYNC, 0x0);
	पूर्ण

	/* HW स्वतःmatically latch rest of address रेजिस्टर on ग_लिखो to
	 * DCSURF_PRIMARY_SURFACE_ADDRESS अगर SURFACE_UPDATE_LOCK is not used
	 *
	 * program high first and then the low addr, order matters!
	 */
	चयन (address->type) अणु
	हाल PLN_ADDR_TYPE_GRAPHICS:
		/* DCN1.0 करोes not support स्थिर color
		 * TODO: program DCHUBBUB_RET_PATH_DCC_CFGx_0/1
		 * base on address->grph.dcc_स्थिर_color
		 * x = 0, 2, 4, 6 क्रम pipe 0, 1, 2, 3 क्रम rgb and luma
		 * x = 1, 3, 5, 7 क्रम pipe 0, 1, 2, 3 क्रम chroma
		 */

		अगर (address->grph.addr.quad_part == 0)
			अवरोध;

		REG_UPDATE_2(DCSURF_SURFACE_CONTROL,
				PRIMARY_SURFACE_TMZ, address->पंचांगz_surface,
				PRIMARY_META_SURFACE_TMZ, address->पंचांगz_surface);

		अगर (address->grph.meta_addr.quad_part != 0) अणु
			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH,
					address->grph.meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
					PRIMARY_META_SURFACE_ADDRESS,
					address->grph.meta_addr.low_part);
		पूर्ण

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH,
				address->grph.addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
				PRIMARY_SURFACE_ADDRESS,
				address->grph.addr.low_part);
		अवरोध;
	हाल PLN_ADDR_TYPE_VIDEO_PROGRESSIVE:
		अगर (address->video_progressive.luma_addr.quad_part == 0
				|| address->video_progressive.chroma_addr.quad_part == 0)
			अवरोध;

		REG_UPDATE_4(DCSURF_SURFACE_CONTROL,
				PRIMARY_SURFACE_TMZ, address->पंचांगz_surface,
				PRIMARY_SURFACE_TMZ_C, address->पंचांगz_surface,
				PRIMARY_META_SURFACE_TMZ, address->पंचांगz_surface,
				PRIMARY_META_SURFACE_TMZ_C, address->पंचांगz_surface);

		अगर (address->video_progressive.luma_meta_addr.quad_part != 0) अणु
			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH_C, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH_C,
					address->video_progressive.chroma_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_C, 0,
					PRIMARY_META_SURFACE_ADDRESS_C,
					address->video_progressive.chroma_meta_addr.low_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH,
					address->video_progressive.luma_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
					PRIMARY_META_SURFACE_ADDRESS,
					address->video_progressive.luma_meta_addr.low_part);
		पूर्ण

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH_C, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH_C,
				address->video_progressive.chroma_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_C, 0,
				PRIMARY_SURFACE_ADDRESS_C,
				address->video_progressive.chroma_addr.low_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH,
				address->video_progressive.luma_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
				PRIMARY_SURFACE_ADDRESS,
				address->video_progressive.luma_addr.low_part);
		अवरोध;
	हाल PLN_ADDR_TYPE_GRPH_STEREO:
		अगर (address->grph_stereo.left_addr.quad_part == 0)
			अवरोध;
		अगर (address->grph_stereo.right_addr.quad_part == 0)
			अवरोध;

		REG_UPDATE_8(DCSURF_SURFACE_CONTROL,
				PRIMARY_SURFACE_TMZ, address->पंचांगz_surface,
				PRIMARY_SURFACE_TMZ_C, address->पंचांगz_surface,
				PRIMARY_META_SURFACE_TMZ, address->पंचांगz_surface,
				PRIMARY_META_SURFACE_TMZ_C, address->पंचांगz_surface,
				SECONDARY_SURFACE_TMZ, address->पंचांगz_surface,
				SECONDARY_SURFACE_TMZ_C, address->पंचांगz_surface,
				SECONDARY_META_SURFACE_TMZ, address->पंचांगz_surface,
				SECONDARY_META_SURFACE_TMZ_C, address->पंचांगz_surface);

		अगर (address->grph_stereo.right_meta_addr.quad_part != 0) अणु

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS_HIGH_C, 0,
				SECONDARY_META_SURFACE_ADDRESS_HIGH_C,
				address->grph_stereo.right_alpha_meta_addr.high_part);

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS_C, 0,
				SECONDARY_META_SURFACE_ADDRESS_C,
				address->grph_stereo.right_alpha_meta_addr.low_part);

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS_HIGH, 0,
					SECONDARY_META_SURFACE_ADDRESS_HIGH,
					address->grph_stereo.right_meta_addr.high_part);

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS, 0,
					SECONDARY_META_SURFACE_ADDRESS,
					address->grph_stereo.right_meta_addr.low_part);
		पूर्ण
		अगर (address->grph_stereo.left_meta_addr.quad_part != 0) अणु

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH_C, 0,
				PRIMARY_META_SURFACE_ADDRESS_HIGH_C,
				address->grph_stereo.left_alpha_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_C, 0,
				PRIMARY_META_SURFACE_ADDRESS_C,
				address->grph_stereo.left_alpha_meta_addr.low_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH,
					address->grph_stereo.left_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
					PRIMARY_META_SURFACE_ADDRESS,
					address->grph_stereo.left_meta_addr.low_part);
		पूर्ण

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS_HIGH_C, 0,
				SECONDARY_SURFACE_ADDRESS_HIGH_C,
				address->grph_stereo.right_alpha_addr.high_part);

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS_C, 0,
				SECONDARY_SURFACE_ADDRESS_C,
				address->grph_stereo.right_alpha_addr.low_part);

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS_HIGH, 0,
				SECONDARY_SURFACE_ADDRESS_HIGH,
				address->grph_stereo.right_addr.high_part);

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS, 0,
				SECONDARY_SURFACE_ADDRESS,
				address->grph_stereo.right_addr.low_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH_C, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH_C,
				address->grph_stereo.left_alpha_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_C, 0,
				PRIMARY_SURFACE_ADDRESS_C,
				address->grph_stereo.left_alpha_addr.low_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH,
				address->grph_stereo.left_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
				PRIMARY_SURFACE_ADDRESS,
				address->grph_stereo.left_addr.low_part);
		अवरोध;
	हाल PLN_ADDR_TYPE_RGBEA:
		अगर (address->rgbea.addr.quad_part == 0
				|| address->rgbea.alpha_addr.quad_part == 0)
			अवरोध;

		REG_UPDATE_4(DCSURF_SURFACE_CONTROL,
				PRIMARY_SURFACE_TMZ, address->पंचांगz_surface,
				PRIMARY_SURFACE_TMZ_C, address->पंचांगz_surface,
				PRIMARY_META_SURFACE_TMZ, address->पंचांगz_surface,
				PRIMARY_META_SURFACE_TMZ_C, address->पंचांगz_surface);

		अगर (address->rgbea.meta_addr.quad_part != 0) अणु

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH_C, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH_C,
					address->rgbea.alpha_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_C, 0,
					PRIMARY_META_SURFACE_ADDRESS_C,
					address->rgbea.alpha_meta_addr.low_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH,
					address->rgbea.meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
					PRIMARY_META_SURFACE_ADDRESS,
					address->rgbea.meta_addr.low_part);
		पूर्ण

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH_C, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH_C,
				address->rgbea.alpha_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_C, 0,
				PRIMARY_SURFACE_ADDRESS_C,
				address->rgbea.alpha_addr.low_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH,
				address->rgbea.addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
				PRIMARY_SURFACE_ADDRESS,
				address->rgbea.addr.low_part);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	hubp->request_address = *address;

	वापस true;
पूर्ण

अटल व्योम hubp3_program_tiling(
	काष्ठा dcn20_hubp *hubp2,
	स्थिर जोड़ dc_tiling_info *info,
	स्थिर क्रमागत surface_pixel_क्रमmat pixel_क्रमmat)
अणु
	REG_UPDATE_4(DCSURF_ADDR_CONFIG,
		NUM_PIPES, log_2(info->gfx9.num_pipes),
		PIPE_INTERLEAVE, info->gfx9.pipe_पूर्णांकerleave,
		MAX_COMPRESSED_FRAGS, log_2(info->gfx9.max_compressed_frags),
		NUM_PKRS, log_2(info->gfx9.num_pkrs));

	REG_UPDATE_3(DCSURF_TILING_CONFIG,
			SW_MODE, info->gfx9.swizzle,
			META_LINEAR, info->gfx9.meta_linear,
			PIPE_ALIGNED, info->gfx9.pipe_aligned);

पूर्ण

व्योम hubp3_dcc_control(काष्ठा hubp *hubp, bool enable,
		क्रमागत hubp_ind_block_size blk_size)
अणु
	uपूर्णांक32_t dcc_en = enable ? 1 : 0;
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_UPDATE_4(DCSURF_SURFACE_CONTROL,
			PRIMARY_SURFACE_DCC_EN, dcc_en,
			PRIMARY_SURFACE_DCC_IND_BLK, blk_size,
			SECONDARY_SURFACE_DCC_EN, dcc_en,
			SECONDARY_SURFACE_DCC_IND_BLK, blk_size);
पूर्ण

व्योम hubp3_dcc_control_sienna_cichlid(काष्ठा hubp *hubp,
		काष्ठा dc_plane_dcc_param *dcc)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/*Workaround until UMD fix the new dcc_ind_blk पूर्णांकerface */
	अगर (dcc->independent_64b_blks && dcc->dcc_ind_blk == 0)
		dcc->dcc_ind_blk = 1;
	अगर (dcc->independent_64b_blks_c && dcc->dcc_ind_blk_c == 0)
		dcc->dcc_ind_blk_c = 1;

	REG_UPDATE_6(DCSURF_SURFACE_CONTROL,
		PRIMARY_SURFACE_DCC_EN, dcc->enable,
		PRIMARY_SURFACE_DCC_IND_BLK, dcc->dcc_ind_blk,
		PRIMARY_SURFACE_DCC_IND_BLK_C, dcc->dcc_ind_blk_c,
		SECONDARY_SURFACE_DCC_EN, dcc->enable,
		SECONDARY_SURFACE_DCC_IND_BLK, dcc->dcc_ind_blk,
		SECONDARY_SURFACE_DCC_IND_BLK_C, dcc->dcc_ind_blk_c);
पूर्ण

व्योम hubp3_dmdata_set_attributes(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_dmdata_attributes *attr)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/*always HW mode */
	REG_UPDATE(DMDATA_CNTL,
			DMDATA_MODE, 1);

	/* क्रम DMDATA flip, need to use SURFACE_UPDATE_LOCK */
	REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_UPDATE_LOCK, 1);

	/* toggle DMDATA_UPDATED and set repeat and size */
	REG_UPDATE(DMDATA_CNTL,
			DMDATA_UPDATED, 0);
	REG_UPDATE_3(DMDATA_CNTL,
			DMDATA_UPDATED, 1,
			DMDATA_REPEAT, attr->dmdata_repeat,
			DMDATA_SIZE, attr->dmdata_size);

	/* set DMDATA address */
	REG_WRITE(DMDATA_ADDRESS_LOW, attr->address.low_part);
	REG_UPDATE(DMDATA_ADDRESS_HIGH,
			DMDATA_ADDRESS_HIGH, attr->address.high_part);

	REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_UPDATE_LOCK, 0);

पूर्ण


व्योम hubp3_program_surface_config(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	जोड़ dc_tiling_info *tiling_info,
	काष्ठा plane_size *plane_size,
	क्रमागत dc_rotation_angle rotation,
	काष्ठा dc_plane_dcc_param *dcc,
	bool horizontal_mirror,
	अचिन्हित पूर्णांक compat_level)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	hubp3_dcc_control_sienna_cichlid(hubp, dcc);
	hubp3_program_tiling(hubp2, tiling_info, क्रमmat);
	hubp2_program_size(hubp, क्रमmat, plane_size, dcc);
	hubp2_program_rotation(hubp, rotation, horizontal_mirror);
	hubp2_program_pixel_क्रमmat(hubp, क्रमmat);
पूर्ण

अटल व्योम hubp3_program_deadline(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	hubp2_program_deadline(hubp, dlg_attr, ttu_attr);
	REG_UPDATE(DCN_DMDATA_VM_CNTL,
			REFCYC_PER_VM_DMDATA, dlg_attr->refcyc_per_vm_dmdata);
पूर्ण

व्योम hubp3_पढ़ो_state(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	काष्ठा dcn_hubp_state *s = &hubp2->state;
	काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs = &s->rq_regs;

	hubp2_पढ़ो_state_common(hubp);

	REG_GET_7(DCHUBP_REQ_SIZE_CONFIG,
		CHUNK_SIZE, &rq_regs->rq_regs_l.chunk_size,
		MIN_CHUNK_SIZE, &rq_regs->rq_regs_l.min_chunk_size,
		META_CHUNK_SIZE, &rq_regs->rq_regs_l.meta_chunk_size,
		MIN_META_CHUNK_SIZE, &rq_regs->rq_regs_l.min_meta_chunk_size,
		DPTE_GROUP_SIZE, &rq_regs->rq_regs_l.dpte_group_size,
		SWATH_HEIGHT, &rq_regs->rq_regs_l.swath_height,
		PTE_ROW_HEIGHT_LINEAR, &rq_regs->rq_regs_l.pte_row_height_linear);

	REG_GET_7(DCHUBP_REQ_SIZE_CONFIG_C,
		CHUNK_SIZE_C, &rq_regs->rq_regs_c.chunk_size,
		MIN_CHUNK_SIZE_C, &rq_regs->rq_regs_c.min_chunk_size,
		META_CHUNK_SIZE_C, &rq_regs->rq_regs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, &rq_regs->rq_regs_c.min_meta_chunk_size,
		DPTE_GROUP_SIZE_C, &rq_regs->rq_regs_c.dpte_group_size,
		SWATH_HEIGHT_C, &rq_regs->rq_regs_c.swath_height,
		PTE_ROW_HEIGHT_LINEAR_C, &rq_regs->rq_regs_c.pte_row_height_linear);

पूर्ण

व्योम hubp3_setup(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr,
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs,
		काष्ठा _vcs_dpi_display_pipe_dest_params_st *pipe_dest)
अणु
	/* otg is locked when this func is called. Register are द्विगुन buffered.
	 * disable the requestors is not needed
	 */
	hubp2_vपढ़ोy_at_or_After_vsync(hubp, pipe_dest);
	hubp21_program_requestor(hubp, rq_regs);
	hubp3_program_deadline(hubp, dlg_attr, ttu_attr);
पूर्ण

व्योम hubp3_init(काष्ठा hubp *hubp)
अणु
	// DEDCN21-133: Inconsistent row starting line क्रम flip between DPTE and Meta
	// This is a chicken bit to enable the ECO fix.

	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	//hubp[i].HUBPREQ_DEBUG.HUBPREQ_DEBUG[26] = 1;
	REG_WRITE(HUBPREQ_DEBUG, 1 << 26);
पूर्ण

अटल काष्ठा hubp_funcs dcn30_hubp_funcs = अणु
	.hubp_enable_tripleBuffer = hubp2_enable_triplebuffer,
	.hubp_is_triplebuffer_enabled = hubp2_is_triplebuffer_enabled,
	.hubp_program_surface_flip_and_addr = hubp3_program_surface_flip_and_addr,
	.hubp_program_surface_config = hubp3_program_surface_config,
	.hubp_is_flip_pending = hubp2_is_flip_pending,
	.hubp_setup = hubp3_setup,
	.hubp_setup_पूर्णांकerdependent = hubp2_setup_पूर्णांकerdependent,
	.hubp_set_vm_प्रणाली_aperture_settings = hubp3_set_vm_प्रणाली_aperture_settings,
	.set_blank = hubp2_set_blank,
	.dcc_control = hubp3_dcc_control,
	.mem_program_viewport = min_set_viewport,
	.set_cursor_attributes	= hubp2_cursor_set_attributes,
	.set_cursor_position	= hubp2_cursor_set_position,
	.hubp_clk_cntl = hubp2_clk_cntl,
	.hubp_vtg_sel = hubp2_vtg_sel,
	.dmdata_set_attributes = hubp3_dmdata_set_attributes,
	.dmdata_load = hubp2_dmdata_load,
	.dmdata_status_करोne = hubp2_dmdata_status_करोne,
	.hubp_पढ़ो_state = hubp3_पढ़ो_state,
	.hubp_clear_underflow = hubp2_clear_underflow,
	.hubp_set_flip_control_surface_gsl = hubp2_set_flip_control_surface_gsl,
	.hubp_init = hubp3_init,
	.hubp_in_blank = hubp1_in_blank,
	.hubp_soft_reset = hubp1_soft_reset,
	.hubp_set_flip_पूर्णांक = hubp1_set_flip_पूर्णांक,
पूर्ण;

bool hubp3_स्थिरruct(
	काष्ठा dcn20_hubp *hubp2,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn_hubp2_रेजिस्टरs *hubp_regs,
	स्थिर काष्ठा dcn_hubp2_shअगरt *hubp_shअगरt,
	स्थिर काष्ठा dcn_hubp2_mask *hubp_mask)
अणु
	hubp2->base.funcs = &dcn30_hubp_funcs;
	hubp2->base.ctx = ctx;
	hubp2->hubp_regs = hubp_regs;
	hubp2->hubp_shअगरt = hubp_shअगरt;
	hubp2->hubp_mask = hubp_mask;
	hubp2->base.inst = inst;
	hubp2->base.opp_id = OPP_ID_INVALID;
	hubp2->base.mpcc_id = 0xf;

	वापस true;
पूर्ण
