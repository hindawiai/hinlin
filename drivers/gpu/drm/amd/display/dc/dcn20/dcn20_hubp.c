<शैली गुरु>
/*
 * Copyright 2012-2021 Advanced Micro Devices, Inc.
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

#समावेश "dcn20_hubp.h"

#समावेश "dm_services.h"
#समावेश "dce_calcs.h"
#समावेश "reg_helper.h"
#समावेश "basics/conversion.h"

#घोषणा DC_LOGGER_INIT(logger)

#घोषणा REG(reg)\
	hubp2->hubp_regs->reg

#घोषणा CTX \
	hubp2->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubp2->hubp_shअगरt->field_name, hubp2->hubp_mask->field_name

व्योम hubp2_set_vm_प्रणाली_aperture_settings(काष्ठा hubp *hubp,
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

	REG_UPDATE_2(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB,
		DCN_VM_SYSTEM_APERTURE_DEFAULT_SYSTEM, 1, /* 1 = प्रणाली physical memory */
		DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB, mc_vm_apt_शेष.high_part);

	REG_SET(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB, 0,
			DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB, mc_vm_apt_शेष.low_part);

	REG_SET(DCN_VM_SYSTEM_APERTURE_LOW_ADDR, 0,
			MC_VM_SYSTEM_APERTURE_LOW_ADDR, mc_vm_apt_low.quad_part);

	REG_SET(DCN_VM_SYSTEM_APERTURE_HIGH_ADDR, 0,
			MC_VM_SYSTEM_APERTURE_HIGH_ADDR, mc_vm_apt_high.quad_part);

	REG_SET_2(DCN_VM_MX_L1_TLB_CNTL, 0,
			ENABLE_L1_TLB, 1,
			SYSTEM_ACCESS_MODE, 0x3);
पूर्ण

व्योम hubp2_program_deadline(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/* DLG - Per hubp */
	REG_SET_2(BLANK_OFFSET_0, 0,
		REFCYC_H_BLANK_END, dlg_attr->refcyc_h_blank_end,
		DLG_V_BLANK_END, dlg_attr->dlg_vblank_end);

	REG_SET(BLANK_OFFSET_1, 0,
		MIN_DST_Y_NEXT_START, dlg_attr->min_dst_y_next_start);

	REG_SET(DST_DIMENSIONS, 0,
		REFCYC_PER_HTOTAL, dlg_attr->refcyc_per_htotal);

	REG_SET_2(DST_AFTER_SCALER, 0,
		REFCYC_X_AFTER_SCALER, dlg_attr->refcyc_x_after_scaler,
		DST_Y_AFTER_SCALER, dlg_attr->dst_y_after_scaler);

	REG_SET(REF_FREQ_TO_PIX_FREQ, 0,
		REF_FREQ_TO_PIX_FREQ, dlg_attr->ref_freq_to_pix_freq);

	/* DLG - Per luma/chroma */
	REG_SET(VBLANK_PARAMETERS_1, 0,
		REFCYC_PER_PTE_GROUP_VBLANK_L, dlg_attr->refcyc_per_pte_group_vblank_l);

	अगर (REG(NOM_PARAMETERS_0))
		REG_SET(NOM_PARAMETERS_0, 0,
			DST_Y_PER_PTE_ROW_NOM_L, dlg_attr->dst_y_per_pte_row_nom_l);

	अगर (REG(NOM_PARAMETERS_1))
		REG_SET(NOM_PARAMETERS_1, 0,
			REFCYC_PER_PTE_GROUP_NOM_L, dlg_attr->refcyc_per_pte_group_nom_l);

	REG_SET(NOM_PARAMETERS_4, 0,
		DST_Y_PER_META_ROW_NOM_L, dlg_attr->dst_y_per_meta_row_nom_l);

	REG_SET(NOM_PARAMETERS_5, 0,
		REFCYC_PER_META_CHUNK_NOM_L, dlg_attr->refcyc_per_meta_chunk_nom_l);

	REG_SET_2(PER_LINE_DELIVERY, 0,
		REFCYC_PER_LINE_DELIVERY_L, dlg_attr->refcyc_per_line_delivery_l,
		REFCYC_PER_LINE_DELIVERY_C, dlg_attr->refcyc_per_line_delivery_c);

	REG_SET(VBLANK_PARAMETERS_2, 0,
		REFCYC_PER_PTE_GROUP_VBLANK_C, dlg_attr->refcyc_per_pte_group_vblank_c);

	अगर (REG(NOM_PARAMETERS_2))
		REG_SET(NOM_PARAMETERS_2, 0,
			DST_Y_PER_PTE_ROW_NOM_C, dlg_attr->dst_y_per_pte_row_nom_c);

	अगर (REG(NOM_PARAMETERS_3))
		REG_SET(NOM_PARAMETERS_3, 0,
			REFCYC_PER_PTE_GROUP_NOM_C, dlg_attr->refcyc_per_pte_group_nom_c);

	REG_SET(NOM_PARAMETERS_6, 0,
		DST_Y_PER_META_ROW_NOM_C, dlg_attr->dst_y_per_meta_row_nom_c);

	REG_SET(NOM_PARAMETERS_7, 0,
		REFCYC_PER_META_CHUNK_NOM_C, dlg_attr->refcyc_per_meta_chunk_nom_c);

	/* TTU - per hubp */
	REG_SET_2(DCN_TTU_QOS_WM, 0,
		QoS_LEVEL_LOW_WM, ttu_attr->qos_level_low_wm,
		QoS_LEVEL_HIGH_WM, ttu_attr->qos_level_high_wm);

	/* TTU - per luma/chroma */
	/* Assumed surf0 is luma and 1 is chroma */

	REG_SET_3(DCN_SURF0_TTU_CNTL0, 0,
		REFCYC_PER_REQ_DELIVERY, ttu_attr->refcyc_per_req_delivery_l,
		QoS_LEVEL_FIXED, ttu_attr->qos_level_fixed_l,
		QoS_RAMP_DISABLE, ttu_attr->qos_ramp_disable_l);

	REG_SET_3(DCN_SURF1_TTU_CNTL0, 0,
		REFCYC_PER_REQ_DELIVERY, ttu_attr->refcyc_per_req_delivery_c,
		QoS_LEVEL_FIXED, ttu_attr->qos_level_fixed_c,
		QoS_RAMP_DISABLE, ttu_attr->qos_ramp_disable_c);

	REG_SET_3(DCN_CUR0_TTU_CNTL0, 0,
		REFCYC_PER_REQ_DELIVERY, ttu_attr->refcyc_per_req_delivery_cur0,
		QoS_LEVEL_FIXED, ttu_attr->qos_level_fixed_cur0,
		QoS_RAMP_DISABLE, ttu_attr->qos_ramp_disable_cur0);

	REG_SET(FLIP_PARAMETERS_1, 0,
		REFCYC_PER_PTE_GROUP_FLIP_L, dlg_attr->refcyc_per_pte_group_flip_l);
पूर्ण

व्योम hubp2_vपढ़ोy_at_or_After_vsync(काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_pipe_dest_params_st *pipe_dest)
अणु
	uपूर्णांक32_t value = 0;
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	/* disable_dlg_test_mode Set 9th bit to 1 to disable "dv" mode */
	REG_WRITE(HUBPREQ_DEBUG_DB, 1 << 8);
	/*
	अगर (VSTARTUP_START - (VREADY_OFFSET+VUPDATE_WIDTH+VUPDATE_OFFSET)/htotal)
	<= OTG_V_BLANK_END
		Set HUBP_VREADY_AT_OR_AFTER_VSYNC = 1
	अन्यथा
		Set HUBP_VREADY_AT_OR_AFTER_VSYNC = 0
	*/
	अगर (pipe_dest->htotal != 0) अणु
		अगर ((pipe_dest->vstartup_start - (pipe_dest->vपढ़ोy_offset+pipe_dest->vupdate_width
			+ pipe_dest->vupdate_offset) / pipe_dest->htotal) <= pipe_dest->vblank_end) अणु
			value = 1;
		पूर्ण अन्यथा
			value = 0;
	पूर्ण

	REG_UPDATE(DCHUBP_CNTL, HUBP_VREADY_AT_OR_AFTER_VSYNC, value);
पूर्ण

व्योम hubp2_program_requestor(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_UPDATE(HUBPRET_CONTROL,
			DET_BUF_PLANE1_BASE_ADDRESS, rq_regs->plane1_base_address);
	REG_SET_4(DCN_EXPANSION_MODE, 0,
			DRQ_EXPANSION_MODE, rq_regs->drq_expansion_mode,
			PRQ_EXPANSION_MODE, rq_regs->prq_expansion_mode,
			MRQ_EXPANSION_MODE, rq_regs->mrq_expansion_mode,
			CRQ_EXPANSION_MODE, rq_regs->crq_expansion_mode);
	REG_SET_8(DCHUBP_REQ_SIZE_CONFIG, 0,
		CHUNK_SIZE, rq_regs->rq_regs_l.chunk_size,
		MIN_CHUNK_SIZE, rq_regs->rq_regs_l.min_chunk_size,
		META_CHUNK_SIZE, rq_regs->rq_regs_l.meta_chunk_size,
		MIN_META_CHUNK_SIZE, rq_regs->rq_regs_l.min_meta_chunk_size,
		DPTE_GROUP_SIZE, rq_regs->rq_regs_l.dpte_group_size,
		MPTE_GROUP_SIZE, rq_regs->rq_regs_l.mpte_group_size,
		SWATH_HEIGHT, rq_regs->rq_regs_l.swath_height,
		PTE_ROW_HEIGHT_LINEAR, rq_regs->rq_regs_l.pte_row_height_linear);
	REG_SET_8(DCHUBP_REQ_SIZE_CONFIG_C, 0,
		CHUNK_SIZE_C, rq_regs->rq_regs_c.chunk_size,
		MIN_CHUNK_SIZE_C, rq_regs->rq_regs_c.min_chunk_size,
		META_CHUNK_SIZE_C, rq_regs->rq_regs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, rq_regs->rq_regs_c.min_meta_chunk_size,
		DPTE_GROUP_SIZE_C, rq_regs->rq_regs_c.dpte_group_size,
		MPTE_GROUP_SIZE_C, rq_regs->rq_regs_c.mpte_group_size,
		SWATH_HEIGHT_C, rq_regs->rq_regs_c.swath_height,
		PTE_ROW_HEIGHT_LINEAR_C, rq_regs->rq_regs_c.pte_row_height_linear);
पूर्ण

अटल व्योम hubp2_setup(
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
	hubp2_program_requestor(hubp, rq_regs);
	hubp2_program_deadline(hubp, dlg_attr, ttu_attr);

पूर्ण

व्योम hubp2_setup_पूर्णांकerdependent(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_SET_2(PREFETCH_SETTINGS, 0,
			DST_Y_PREFETCH, dlg_attr->dst_y_prefetch,
			VRATIO_PREFETCH, dlg_attr->vratio_prefetch);

	REG_SET(PREFETCH_SETTINGS_C, 0,
			VRATIO_PREFETCH_C, dlg_attr->vratio_prefetch_c);

	REG_SET_2(VBLANK_PARAMETERS_0, 0,
		DST_Y_PER_VM_VBLANK, dlg_attr->dst_y_per_vm_vblank,
		DST_Y_PER_ROW_VBLANK, dlg_attr->dst_y_per_row_vblank);

	REG_SET_2(FLIP_PARAMETERS_0, 0,
		DST_Y_PER_VM_FLIP, dlg_attr->dst_y_per_vm_flip,
		DST_Y_PER_ROW_FLIP, dlg_attr->dst_y_per_row_flip);

	REG_SET(VBLANK_PARAMETERS_3, 0,
		REFCYC_PER_META_CHUNK_VBLANK_L, dlg_attr->refcyc_per_meta_chunk_vblank_l);

	REG_SET(VBLANK_PARAMETERS_4, 0,
		REFCYC_PER_META_CHUNK_VBLANK_C, dlg_attr->refcyc_per_meta_chunk_vblank_c);

	REG_SET(FLIP_PARAMETERS_2, 0,
		REFCYC_PER_META_CHUNK_FLIP_L, dlg_attr->refcyc_per_meta_chunk_flip_l);

	REG_SET_2(PER_LINE_DELIVERY_PRE, 0,
		REFCYC_PER_LINE_DELIVERY_PRE_L, dlg_attr->refcyc_per_line_delivery_pre_l,
		REFCYC_PER_LINE_DELIVERY_PRE_C, dlg_attr->refcyc_per_line_delivery_pre_c);

	REG_SET(DCN_SURF0_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE,
		ttu_attr->refcyc_per_req_delivery_pre_l);
	REG_SET(DCN_SURF1_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE,
		ttu_attr->refcyc_per_req_delivery_pre_c);
	REG_SET(DCN_CUR0_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE, ttu_attr->refcyc_per_req_delivery_pre_cur0);
	REG_SET(DCN_CUR1_TTU_CNTL1, 0,
		REFCYC_PER_REQ_DELIVERY_PRE, ttu_attr->refcyc_per_req_delivery_pre_cur1);

	REG_SET_2(DCN_GLOBAL_TTU_CNTL, 0,
		MIN_TTU_VBLANK, ttu_attr->min_ttu_vblank,
		QoS_LEVEL_FLIP, ttu_attr->qos_level_flip);
पूर्ण

/* DCN2 (GFX10), the following GFX fields are deprecated. They can be set but they will not be used:
 *	NUM_BANKS
 *	NUM_SE
 *	NUM_RB_PER_SE
 *	RB_ALIGNED
 * Other things can be शेषed, since they never change:
 *	PIPE_ALIGNED = 0
 *	META_LINEAR = 0
 * In GFX10, only these apply:
 *	PIPE_INTERLEAVE
 *	NUM_PIPES
 *	MAX_COMPRESSED_FRAGS
 *	SW_MODE
 */
अटल व्योम hubp2_program_tiling(
	काष्ठा dcn20_hubp *hubp2,
	स्थिर जोड़ dc_tiling_info *info,
	स्थिर क्रमागत surface_pixel_क्रमmat pixel_क्रमmat)
अणु
	REG_UPDATE_3(DCSURF_ADDR_CONFIG,
			NUM_PIPES, log_2(info->gfx9.num_pipes),
			PIPE_INTERLEAVE, info->gfx9.pipe_पूर्णांकerleave,
			MAX_COMPRESSED_FRAGS, log_2(info->gfx9.max_compressed_frags));

	REG_UPDATE_4(DCSURF_TILING_CONFIG,
			SW_MODE, info->gfx9.swizzle,
			META_LINEAR, 0,
			RB_ALIGNED, 0,
			PIPE_ALIGNED, 0);
पूर्ण

व्योम hubp2_program_size(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	स्थिर काष्ठा plane_size *plane_size,
	काष्ठा dc_plane_dcc_param *dcc)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uपूर्णांक32_t pitch, meta_pitch, pitch_c, meta_pitch_c;
	bool use_pitch_c = false;

	/* Program data and meta surface pitch (calculation from addrlib)
	 * 444 or 420 luma
	 */
	use_pitch_c = क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN
		&& क्रमmat < SURFACE_PIXEL_FORMAT_SUBSAMPLE_END;
	use_pitch_c = use_pitch_c
		|| (क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA);
	अगर (use_pitch_c) अणु
		ASSERT(plane_size->chroma_pitch != 0);
		/* Chroma pitch zero can cause प्रणाली hang! */

		pitch = plane_size->surface_pitch - 1;
		meta_pitch = dcc->meta_pitch - 1;
		pitch_c = plane_size->chroma_pitch - 1;
		meta_pitch_c = dcc->meta_pitch_c - 1;
	पूर्ण अन्यथा अणु
		pitch = plane_size->surface_pitch - 1;
		meta_pitch = dcc->meta_pitch - 1;
		pitch_c = 0;
		meta_pitch_c = 0;
	पूर्ण

	अगर (!dcc->enable) अणु
		meta_pitch = 0;
		meta_pitch_c = 0;
	पूर्ण

	REG_UPDATE_2(DCSURF_SURFACE_PITCH,
			PITCH, pitch, META_PITCH, meta_pitch);

	use_pitch_c = क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN;
	use_pitch_c = use_pitch_c
		|| (क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA);
	अगर (use_pitch_c)
		REG_UPDATE_2(DCSURF_SURFACE_PITCH_C,
			PITCH_C, pitch_c, META_PITCH_C, meta_pitch_c);
पूर्ण

व्योम hubp2_program_rotation(
	काष्ठा hubp *hubp,
	क्रमागत dc_rotation_angle rotation,
	bool horizontal_mirror)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uपूर्णांक32_t mirror;


	अगर (horizontal_mirror)
		mirror = 1;
	अन्यथा
		mirror = 0;

	/* Program rotation angle and horz mirror - no mirror */
	अगर (rotation == ROTATION_ANGLE_0)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 0,
				H_MIRROR_EN, mirror);
	अन्यथा अगर (rotation == ROTATION_ANGLE_90)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 1,
				H_MIRROR_EN, mirror);
	अन्यथा अगर (rotation == ROTATION_ANGLE_180)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 2,
				H_MIRROR_EN, mirror);
	अन्यथा अगर (rotation == ROTATION_ANGLE_270)
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				ROTATION_ANGLE, 3,
				H_MIRROR_EN, mirror);
पूर्ण

व्योम hubp2_dcc_control(काष्ठा hubp *hubp, bool enable,
		क्रमागत hubp_ind_block_size independent_64b_blks)
अणु
	uपूर्णांक32_t dcc_en = enable ? 1 : 0;
	uपूर्णांक32_t dcc_ind_64b_blk = independent_64b_blks ? 1 : 0;
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_UPDATE_4(DCSURF_SURFACE_CONTROL,
			PRIMARY_SURFACE_DCC_EN, dcc_en,
			PRIMARY_SURFACE_DCC_IND_64B_BLK, dcc_ind_64b_blk,
			SECONDARY_SURFACE_DCC_EN, dcc_en,
			SECONDARY_SURFACE_DCC_IND_64B_BLK, dcc_ind_64b_blk);
पूर्ण

व्योम hubp2_program_pixel_क्रमmat(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uपूर्णांक32_t red_bar = 3;
	uपूर्णांक32_t blue_bar = 2;

	/* swap क्रम ABGR क्रमmat */
	अगर (क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR8888
			|| क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010
			|| क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS
			|| क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F) अणु
		red_bar = 2;
		blue_bar = 3;
	पूर्ण

	REG_UPDATE_2(HUBPRET_CONTROL,
			CROSSBAR_SRC_CB_B, blue_bar,
			CROSSBAR_SRC_CR_R, red_bar);

	/* Mapping is same as ipp programming (cnvc) */

	चयन (क्रमmat)	अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 1);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 3);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 8);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 10);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 22);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:/*we use crossbar alपढ़ोy*/
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 24);
		अवरोध;

	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 65);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 64);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 67);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 66);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_AYCrCb8888:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 12);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 112);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 113);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 114);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 118);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT:
		REG_UPDATE(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 119);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE:
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 116,
				ALPHA_PLANE_EN, 0);
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA:
		REG_UPDATE_2(DCSURF_SURFACE_CONFIG,
				SURFACE_PIXEL_FORMAT, 116,
				ALPHA_PLANE_EN, 1);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	/* करोn't see the need of program the xbar in DCN 1.0 */
पूर्ण

व्योम hubp2_program_surface_config(
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

	hubp2_dcc_control(hubp, dcc->enable, dcc->independent_64b_blks);
	hubp2_program_tiling(hubp2, tiling_info, क्रमmat);
	hubp2_program_size(hubp, क्रमmat, plane_size, dcc);
	hubp2_program_rotation(hubp, rotation, horizontal_mirror);
	hubp2_program_pixel_क्रमmat(hubp, क्रमmat);
पूर्ण

क्रमागत cursor_lines_per_chunk hubp2_get_lines_per_chunk(
	अचिन्हित पूर्णांक cursor_width,
	क्रमागत dc_cursor_color_क्रमmat cursor_mode)
अणु
	क्रमागत cursor_lines_per_chunk line_per_chunk = CURSOR_LINE_PER_CHUNK_16;

	अगर (cursor_mode == CURSOR_MODE_MONO)
		line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
	अन्यथा अगर (cursor_mode == CURSOR_MODE_COLOR_1BIT_AND ||
		 cursor_mode == CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA ||
		 cursor_mode == CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA) अणु
		अगर (cursor_width >= 1   && cursor_width <= 32)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
		अन्यथा अगर (cursor_width >= 33  && cursor_width <= 64)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_8;
		अन्यथा अगर (cursor_width >= 65  && cursor_width <= 128)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_4;
		अन्यथा अगर (cursor_width >= 129 && cursor_width <= 256)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_2;
	पूर्ण अन्यथा अगर (cursor_mode == CURSOR_MODE_COLOR_64BIT_FP_PRE_MULTIPLIED ||
		   cursor_mode == CURSOR_MODE_COLOR_64BIT_FP_UN_PRE_MULTIPLIED) अणु
		अगर (cursor_width >= 1   && cursor_width <= 16)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
		अन्यथा अगर (cursor_width >= 17  && cursor_width <= 32)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_8;
		अन्यथा अगर (cursor_width >= 33  && cursor_width <= 64)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_4;
		अन्यथा अगर (cursor_width >= 65 && cursor_width <= 128)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_2;
		अन्यथा अगर (cursor_width >= 129 && cursor_width <= 256)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_1;
	पूर्ण

	वापस line_per_chunk;
पूर्ण

व्योम hubp2_cursor_set_attributes(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_cursor_attributes *attr)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	क्रमागत cursor_pitch hw_pitch = hubp1_get_cursor_pitch(attr->pitch);
	क्रमागत cursor_lines_per_chunk lpc = hubp2_get_lines_per_chunk(
			attr->width, attr->color_क्रमmat);

	hubp->curs_attr = *attr;

	REG_UPDATE(CURSOR_SURFACE_ADDRESS_HIGH,
			CURSOR_SURFACE_ADDRESS_HIGH, attr->address.high_part);
	REG_UPDATE(CURSOR_SURFACE_ADDRESS,
			CURSOR_SURFACE_ADDRESS, attr->address.low_part);

	REG_UPDATE_2(CURSOR_SIZE,
			CURSOR_WIDTH, attr->width,
			CURSOR_HEIGHT, attr->height);

	REG_UPDATE_4(CURSOR_CONTROL,
			CURSOR_MODE, attr->color_क्रमmat,
			CURSOR_2X_MAGNIFY, attr->attribute_flags.bits.ENABLE_MAGNIFICATION,
			CURSOR_PITCH, hw_pitch,
			CURSOR_LINES_PER_CHUNK, lpc);

	REG_SET_2(CURSOR_SETTINGS, 0,
			/* no shअगरt of the cursor HDL schedule */
			CURSOR0_DST_Y_OFFSET, 0,
			 /* used to shअगरt the cursor chunk request deadline */
			CURSOR0_CHUNK_HDL_ADJUST, 3);
पूर्ण

व्योम hubp2_dmdata_set_attributes(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_dmdata_attributes *attr)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	अगर (attr->dmdata_mode == DMDATA_HW_MODE) अणु
		/* set to HW mode */
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

	पूर्ण अन्यथा अणु
		/* set to SW mode beक्रमe loading data */
		REG_SET(DMDATA_CNTL, 0,
				DMDATA_MODE, 0);
		/* toggle DMDATA_SW_UPDATED to start loading sequence */
		REG_UPDATE(DMDATA_SW_CNTL,
				DMDATA_SW_UPDATED, 0);
		REG_UPDATE_3(DMDATA_SW_CNTL,
				DMDATA_SW_UPDATED, 1,
				DMDATA_SW_REPEAT, attr->dmdata_repeat,
				DMDATA_SW_SIZE, attr->dmdata_size);
		/* load data पूर्णांकo hubp dmdata buffer */
		hubp2_dmdata_load(hubp, attr->dmdata_size, attr->dmdata_sw_data);
	पूर्ण

	/* Note that DL_DELTA must be programmed अगर we want to use TTU mode */
	REG_SET_3(DMDATA_QOS_CNTL, 0,
			DMDATA_QOS_MODE, attr->dmdata_qos_mode,
			DMDATA_QOS_LEVEL, attr->dmdata_qos_level,
			DMDATA_DL_DELTA, attr->dmdata_dl_delta);
पूर्ण

व्योम hubp2_dmdata_load(
		काष्ठा hubp *hubp,
		uपूर्णांक32_t dmdata_sw_size,
		स्थिर uपूर्णांक32_t *dmdata_sw_data)
अणु
	पूर्णांक i;
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/* load dmdata पूर्णांकo HUBP buffer in SW mode */
	क्रम (i = 0; i < dmdata_sw_size / 4; i++)
		REG_WRITE(DMDATA_SW_DATA, dmdata_sw_data[i]);
पूर्ण

bool hubp2_dmdata_status_करोne(काष्ठा hubp *hubp)
अणु
	uपूर्णांक32_t status;
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_GET(DMDATA_STATUS, DMDATA_DONE, &status);
	वापस (status == 1);
पूर्ण

bool hubp2_program_surface_flip_and_addr(
	काष्ठा hubp *hubp,
	स्थिर काष्ठा dc_plane_address *address,
	bool flip_immediate)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	//program flip type
	REG_UPDATE(DCSURF_FLIP_CONTROL,
			SURFACE_FLIP_TYPE, flip_immediate);

	// Program VMID reg
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

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS_HIGH, 0,
					SECONDARY_META_SURFACE_ADDRESS_HIGH,
					address->grph_stereo.right_meta_addr.high_part);

			REG_SET(DCSURF_SECONDARY_META_SURFACE_ADDRESS, 0,
					SECONDARY_META_SURFACE_ADDRESS,
					address->grph_stereo.right_meta_addr.low_part);
		पूर्ण
		अगर (address->grph_stereo.left_meta_addr.quad_part != 0) अणु

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS_HIGH, 0,
					PRIMARY_META_SURFACE_ADDRESS_HIGH,
					address->grph_stereo.left_meta_addr.high_part);

			REG_SET(DCSURF_PRIMARY_META_SURFACE_ADDRESS, 0,
					PRIMARY_META_SURFACE_ADDRESS,
					address->grph_stereo.left_meta_addr.low_part);
		पूर्ण

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS_HIGH, 0,
				SECONDARY_SURFACE_ADDRESS_HIGH,
				address->grph_stereo.right_addr.high_part);

		REG_SET(DCSURF_SECONDARY_SURFACE_ADDRESS, 0,
				SECONDARY_SURFACE_ADDRESS,
				address->grph_stereo.right_addr.low_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
				PRIMARY_SURFACE_ADDRESS_HIGH,
				address->grph_stereo.left_addr.high_part);

		REG_SET(DCSURF_PRIMARY_SURFACE_ADDRESS, 0,
				PRIMARY_SURFACE_ADDRESS,
				address->grph_stereo.left_addr.low_part);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	hubp->request_address = *address;

	वापस true;
पूर्ण

व्योम hubp2_enable_triplebuffer(
	काष्ठा hubp *hubp,
	bool enable)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uपूर्णांक32_t triple_buffer_en = 0;
	bool tri_buffer_en;

	REG_GET(DCSURF_FLIP_CONTROL2, SURFACE_TRIPLE_BUFFER_ENABLE, &triple_buffer_en);
	tri_buffer_en = (triple_buffer_en == 1);
	अगर (tri_buffer_en != enable) अणु
		REG_UPDATE(DCSURF_FLIP_CONTROL2,
			SURFACE_TRIPLE_BUFFER_ENABLE, enable ? DC_TRIPLEBUFFER_ENABLE : DC_TRIPLEBUFFER_DISABLE);
	पूर्ण
पूर्ण

bool hubp2_is_triplebuffer_enabled(
	काष्ठा hubp *hubp)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uपूर्णांक32_t triple_buffer_en = 0;

	REG_GET(DCSURF_FLIP_CONTROL2, SURFACE_TRIPLE_BUFFER_ENABLE, &triple_buffer_en);

	वापस (bool)triple_buffer_en;
पूर्ण

व्योम hubp2_set_flip_control_surface_gsl(काष्ठा hubp *hubp, bool enable)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_UPDATE(DCSURF_FLIP_CONTROL2, SURFACE_GSL_ENABLE, enable ? 1 : 0);
पूर्ण

bool hubp2_is_flip_pending(काष्ठा hubp *hubp)
अणु
	uपूर्णांक32_t flip_pending = 0;
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	काष्ठा dc_plane_address earliest_inuse_address;

	अगर (hubp && hubp->घातer_gated)
		वापस false;

	REG_GET(DCSURF_FLIP_CONTROL,
			SURFACE_FLIP_PENDING, &flip_pending);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE,
			SURFACE_EARLIEST_INUSE_ADDRESS, &earliest_inuse_address.grph.addr.low_part);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE_HIGH,
			SURFACE_EARLIEST_INUSE_ADDRESS_HIGH, &earliest_inuse_address.grph.addr.high_part);

	अगर (flip_pending)
		वापस true;

	अगर (earliest_inuse_address.grph.addr.quad_part != hubp->request_address.grph.addr.quad_part)
		वापस true;

	वापस false;
पूर्ण

व्योम hubp2_set_blank(काष्ठा hubp *hubp, bool blank)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uपूर्णांक32_t blank_en = blank ? 1 : 0;

	REG_UPDATE_2(DCHUBP_CNTL,
			HUBP_BLANK_EN, blank_en,
			HUBP_TTU_DISABLE, blank_en);

	अगर (blank) अणु
		uपूर्णांक32_t reg_val = REG_READ(DCHUBP_CNTL);

		अगर (reg_val) अणु
			/* init sequence workaround: in हाल HUBP is
			 * घातer gated, this रुको would समयout.
			 *
			 * we just wrote reg_val to non-0, अगर it stay 0
			 * it means HUBP is gated
			 */
			REG_WAIT(DCHUBP_CNTL,
					HUBP_NO_OUTSTANDING_REQ, 1,
					1, 200);
		पूर्ण

		hubp->mpcc_id = 0xf;
		hubp->opp_id = OPP_ID_INVALID;
	पूर्ण
पूर्ण

व्योम hubp2_cursor_set_position(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_cursor_position *pos,
		स्थिर काष्ठा dc_cursor_mi_param *param)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	पूर्णांक src_x_offset = pos->x - pos->x_hotspot - param->viewport.x;
	पूर्णांक src_y_offset = pos->y - pos->y_hotspot - param->viewport.y;
	पूर्णांक x_hotspot = pos->x_hotspot;
	पूर्णांक y_hotspot = pos->y_hotspot;
	पूर्णांक cursor_height = (पूर्णांक)hubp->curs_attr.height;
	पूर्णांक cursor_width = (पूर्णांक)hubp->curs_attr.width;
	uपूर्णांक32_t dst_x_offset;
	uपूर्णांक32_t cur_en = pos->enable ? 1 : 0;

	/*
	 * Guard aganst cursor_set_position() from being called with invalid
	 * attributes
	 *
	 * TODO: Look at combining cursor_set_position() and
	 * cursor_set_attributes() पूर्णांकo cursor_update()
	 */
	अगर (hubp->curs_attr.address.quad_part == 0)
		वापस;

	// Rotated cursor width/height and hotspots tweaks क्रम offset calculation
	अगर (param->rotation == ROTATION_ANGLE_90 || param->rotation == ROTATION_ANGLE_270) अणु
		swap(cursor_height, cursor_width);
		अगर (param->rotation == ROTATION_ANGLE_90) अणु
			src_x_offset = pos->x - pos->y_hotspot - param->viewport.x;
			src_y_offset = pos->y - pos->x_hotspot - param->viewport.y;
		पूर्ण
	पूर्ण अन्यथा अगर (param->rotation == ROTATION_ANGLE_180) अणु
		src_x_offset = pos->x - param->viewport.x;
		src_y_offset = pos->y - param->viewport.y;
	पूर्ण

	अगर (param->mirror) अणु
		x_hotspot = param->viewport.width - x_hotspot;
		src_x_offset = param->viewport.x + param->viewport.width - src_x_offset;
	पूर्ण

	dst_x_offset = (src_x_offset >= 0) ? src_x_offset : 0;
	dst_x_offset *= param->ref_clk_khz;
	dst_x_offset /= param->pixel_clk_khz;

	ASSERT(param->h_scale_ratio.value);

	अगर (param->h_scale_ratio.value)
		dst_x_offset = dc_fixpt_न्यूनमान(dc_fixpt_भाग(
				dc_fixpt_from_पूर्णांक(dst_x_offset),
				param->h_scale_ratio));

	अगर (src_x_offset >= (पूर्णांक)param->viewport.width)
		cur_en = 0;  /* not visible beyond right edge*/

	अगर (src_x_offset + cursor_width <= 0)
		cur_en = 0;  /* not visible beyond left edge*/

	अगर (src_y_offset >= (पूर्णांक)param->viewport.height)
		cur_en = 0;  /* not visible beyond bottom edge*/

	अगर (src_y_offset + cursor_height <= 0)
		cur_en = 0;  /* not visible beyond top edge*/

	अगर (cur_en && REG_READ(CURSOR_SURFACE_ADDRESS) == 0)
		hubp->funcs->set_cursor_attributes(hubp, &hubp->curs_attr);

	REG_UPDATE(CURSOR_CONTROL,
			CURSOR_ENABLE, cur_en);

	REG_SET_2(CURSOR_POSITION, 0,
			CURSOR_X_POSITION, pos->x,
			CURSOR_Y_POSITION, pos->y);

	REG_SET_2(CURSOR_HOT_SPOT, 0,
			CURSOR_HOT_SPOT_X, x_hotspot,
			CURSOR_HOT_SPOT_Y, y_hotspot);

	REG_SET(CURSOR_DST_OFFSET, 0,
			CURSOR_DST_X_OFFSET, dst_x_offset);
	/* TODO Handle surface pixel क्रमmats other than 4:4:4 */
पूर्ण

व्योम hubp2_clk_cntl(काष्ठा hubp *hubp, bool enable)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uपूर्णांक32_t clk_enable = enable ? 1 : 0;

	REG_UPDATE(HUBP_CLK_CNTL, HUBP_CLOCK_ENABLE, clk_enable);
पूर्ण

व्योम hubp2_vtg_sel(काष्ठा hubp *hubp, uपूर्णांक32_t otg_inst)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_UPDATE(DCHUBP_CNTL, HUBP_VTG_SEL, otg_inst);
पूर्ण

व्योम hubp2_clear_underflow(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	REG_UPDATE(DCHUBP_CNTL, HUBP_UNDERFLOW_CLEAR, 1);
पूर्ण

व्योम hubp2_पढ़ो_state_common(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	काष्ठा dcn_hubp_state *s = &hubp2->state;
	काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr = &s->dlg_attr;
	काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr = &s->ttu_attr;
	काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs = &s->rq_regs;

	/* Requester */
	REG_GET(HUBPRET_CONTROL,
			DET_BUF_PLANE1_BASE_ADDRESS, &rq_regs->plane1_base_address);
	REG_GET_4(DCN_EXPANSION_MODE,
			DRQ_EXPANSION_MODE, &rq_regs->drq_expansion_mode,
			PRQ_EXPANSION_MODE, &rq_regs->prq_expansion_mode,
			MRQ_EXPANSION_MODE, &rq_regs->mrq_expansion_mode,
			CRQ_EXPANSION_MODE, &rq_regs->crq_expansion_mode);

	/* DLG - Per hubp */
	REG_GET_2(BLANK_OFFSET_0,
		REFCYC_H_BLANK_END, &dlg_attr->refcyc_h_blank_end,
		DLG_V_BLANK_END, &dlg_attr->dlg_vblank_end);

	REG_GET(BLANK_OFFSET_1,
		MIN_DST_Y_NEXT_START, &dlg_attr->min_dst_y_next_start);

	REG_GET(DST_DIMENSIONS,
		REFCYC_PER_HTOTAL, &dlg_attr->refcyc_per_htotal);

	REG_GET_2(DST_AFTER_SCALER,
		REFCYC_X_AFTER_SCALER, &dlg_attr->refcyc_x_after_scaler,
		DST_Y_AFTER_SCALER, &dlg_attr->dst_y_after_scaler);

	अगर (REG(PREFETCH_SETTINS))
		REG_GET_2(PREFETCH_SETTINS,
			DST_Y_PREFETCH, &dlg_attr->dst_y_prefetch,
			VRATIO_PREFETCH, &dlg_attr->vratio_prefetch);
	अन्यथा
		REG_GET_2(PREFETCH_SETTINGS,
			DST_Y_PREFETCH, &dlg_attr->dst_y_prefetch,
			VRATIO_PREFETCH, &dlg_attr->vratio_prefetch);

	REG_GET_2(VBLANK_PARAMETERS_0,
		DST_Y_PER_VM_VBLANK, &dlg_attr->dst_y_per_vm_vblank,
		DST_Y_PER_ROW_VBLANK, &dlg_attr->dst_y_per_row_vblank);

	REG_GET(REF_FREQ_TO_PIX_FREQ,
		REF_FREQ_TO_PIX_FREQ, &dlg_attr->ref_freq_to_pix_freq);

	/* DLG - Per luma/chroma */
	REG_GET(VBLANK_PARAMETERS_1,
		REFCYC_PER_PTE_GROUP_VBLANK_L, &dlg_attr->refcyc_per_pte_group_vblank_l);

	REG_GET(VBLANK_PARAMETERS_3,
		REFCYC_PER_META_CHUNK_VBLANK_L, &dlg_attr->refcyc_per_meta_chunk_vblank_l);

	अगर (REG(NOM_PARAMETERS_0))
		REG_GET(NOM_PARAMETERS_0,
			DST_Y_PER_PTE_ROW_NOM_L, &dlg_attr->dst_y_per_pte_row_nom_l);

	अगर (REG(NOM_PARAMETERS_1))
		REG_GET(NOM_PARAMETERS_1,
			REFCYC_PER_PTE_GROUP_NOM_L, &dlg_attr->refcyc_per_pte_group_nom_l);

	REG_GET(NOM_PARAMETERS_4,
		DST_Y_PER_META_ROW_NOM_L, &dlg_attr->dst_y_per_meta_row_nom_l);

	REG_GET(NOM_PARAMETERS_5,
		REFCYC_PER_META_CHUNK_NOM_L, &dlg_attr->refcyc_per_meta_chunk_nom_l);

	REG_GET_2(PER_LINE_DELIVERY_PRE,
		REFCYC_PER_LINE_DELIVERY_PRE_L, &dlg_attr->refcyc_per_line_delivery_pre_l,
		REFCYC_PER_LINE_DELIVERY_PRE_C, &dlg_attr->refcyc_per_line_delivery_pre_c);

	REG_GET_2(PER_LINE_DELIVERY,
		REFCYC_PER_LINE_DELIVERY_L, &dlg_attr->refcyc_per_line_delivery_l,
		REFCYC_PER_LINE_DELIVERY_C, &dlg_attr->refcyc_per_line_delivery_c);

	अगर (REG(PREFETCH_SETTINS_C))
		REG_GET(PREFETCH_SETTINS_C,
			VRATIO_PREFETCH_C, &dlg_attr->vratio_prefetch_c);
	अन्यथा
		REG_GET(PREFETCH_SETTINGS_C,
			VRATIO_PREFETCH_C, &dlg_attr->vratio_prefetch_c);

	REG_GET(VBLANK_PARAMETERS_2,
		REFCYC_PER_PTE_GROUP_VBLANK_C, &dlg_attr->refcyc_per_pte_group_vblank_c);

	REG_GET(VBLANK_PARAMETERS_4,
		REFCYC_PER_META_CHUNK_VBLANK_C, &dlg_attr->refcyc_per_meta_chunk_vblank_c);

	अगर (REG(NOM_PARAMETERS_2))
		REG_GET(NOM_PARAMETERS_2,
			DST_Y_PER_PTE_ROW_NOM_C, &dlg_attr->dst_y_per_pte_row_nom_c);

	अगर (REG(NOM_PARAMETERS_3))
		REG_GET(NOM_PARAMETERS_3,
			REFCYC_PER_PTE_GROUP_NOM_C, &dlg_attr->refcyc_per_pte_group_nom_c);

	REG_GET(NOM_PARAMETERS_6,
		DST_Y_PER_META_ROW_NOM_C, &dlg_attr->dst_y_per_meta_row_nom_c);

	REG_GET(NOM_PARAMETERS_7,
		REFCYC_PER_META_CHUNK_NOM_C, &dlg_attr->refcyc_per_meta_chunk_nom_c);

	/* TTU - per hubp */
	REG_GET_2(DCN_TTU_QOS_WM,
		QoS_LEVEL_LOW_WM, &ttu_attr->qos_level_low_wm,
		QoS_LEVEL_HIGH_WM, &ttu_attr->qos_level_high_wm);

	REG_GET_2(DCN_GLOBAL_TTU_CNTL,
		MIN_TTU_VBLANK, &ttu_attr->min_ttu_vblank,
		QoS_LEVEL_FLIP, &ttu_attr->qos_level_flip);

	/* TTU - per luma/chroma */
	/* Assumed surf0 is luma and 1 is chroma */

	REG_GET_3(DCN_SURF0_TTU_CNTL0,
		REFCYC_PER_REQ_DELIVERY, &ttu_attr->refcyc_per_req_delivery_l,
		QoS_LEVEL_FIXED, &ttu_attr->qos_level_fixed_l,
		QoS_RAMP_DISABLE, &ttu_attr->qos_ramp_disable_l);

	REG_GET(DCN_SURF0_TTU_CNTL1,
		REFCYC_PER_REQ_DELIVERY_PRE,
		&ttu_attr->refcyc_per_req_delivery_pre_l);

	REG_GET_3(DCN_SURF1_TTU_CNTL0,
		REFCYC_PER_REQ_DELIVERY, &ttu_attr->refcyc_per_req_delivery_c,
		QoS_LEVEL_FIXED, &ttu_attr->qos_level_fixed_c,
		QoS_RAMP_DISABLE, &ttu_attr->qos_ramp_disable_c);

	REG_GET(DCN_SURF1_TTU_CNTL1,
		REFCYC_PER_REQ_DELIVERY_PRE,
		&ttu_attr->refcyc_per_req_delivery_pre_c);

	/* Rest of hubp */
	REG_GET(DCSURF_SURFACE_CONFIG,
			SURFACE_PIXEL_FORMAT, &s->pixel_क्रमmat);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE_HIGH,
			SURFACE_EARLIEST_INUSE_ADDRESS_HIGH, &s->inuse_addr_hi);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE,
			SURFACE_EARLIEST_INUSE_ADDRESS, &s->inuse_addr_lo);

	REG_GET_2(DCSURF_PRI_VIEWPORT_DIMENSION,
			PRI_VIEWPORT_WIDTH, &s->viewport_width,
			PRI_VIEWPORT_HEIGHT, &s->viewport_height);

	REG_GET_2(DCSURF_SURFACE_CONFIG,
			ROTATION_ANGLE, &s->rotation_angle,
			H_MIRROR_EN, &s->h_mirror_en);

	REG_GET(DCSURF_TILING_CONFIG,
			SW_MODE, &s->sw_mode);

	REG_GET(DCSURF_SURFACE_CONTROL,
			PRIMARY_SURFACE_DCC_EN, &s->dcc_en);

	REG_GET_3(DCHUBP_CNTL,
			HUBP_BLANK_EN, &s->blank_en,
			HUBP_TTU_DISABLE, &s->ttu_disable,
			HUBP_UNDERFLOW_STATUS, &s->underflow_status);

	REG_GET(HUBP_CLK_CNTL,
			HUBP_CLOCK_ENABLE, &s->घड़ी_en);

	REG_GET(DCN_GLOBAL_TTU_CNTL,
			MIN_TTU_VBLANK, &s->min_ttu_vblank);

	REG_GET_2(DCN_TTU_QOS_WM,
			QoS_LEVEL_LOW_WM, &s->qos_level_low_wm,
			QoS_LEVEL_HIGH_WM, &s->qos_level_high_wm);

पूर्ण

व्योम hubp2_पढ़ो_state(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	काष्ठा dcn_hubp_state *s = &hubp2->state;
	काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs = &s->rq_regs;

	hubp2_पढ़ो_state_common(hubp);

	REG_GET_8(DCHUBP_REQ_SIZE_CONFIG,
		CHUNK_SIZE, &rq_regs->rq_regs_l.chunk_size,
		MIN_CHUNK_SIZE, &rq_regs->rq_regs_l.min_chunk_size,
		META_CHUNK_SIZE, &rq_regs->rq_regs_l.meta_chunk_size,
		MIN_META_CHUNK_SIZE, &rq_regs->rq_regs_l.min_meta_chunk_size,
		DPTE_GROUP_SIZE, &rq_regs->rq_regs_l.dpte_group_size,
		MPTE_GROUP_SIZE, &rq_regs->rq_regs_l.mpte_group_size,
		SWATH_HEIGHT, &rq_regs->rq_regs_l.swath_height,
		PTE_ROW_HEIGHT_LINEAR, &rq_regs->rq_regs_l.pte_row_height_linear);

	REG_GET_8(DCHUBP_REQ_SIZE_CONFIG_C,
		CHUNK_SIZE_C, &rq_regs->rq_regs_c.chunk_size,
		MIN_CHUNK_SIZE_C, &rq_regs->rq_regs_c.min_chunk_size,
		META_CHUNK_SIZE_C, &rq_regs->rq_regs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, &rq_regs->rq_regs_c.min_meta_chunk_size,
		DPTE_GROUP_SIZE_C, &rq_regs->rq_regs_c.dpte_group_size,
		MPTE_GROUP_SIZE_C, &rq_regs->rq_regs_c.mpte_group_size,
		SWATH_HEIGHT_C, &rq_regs->rq_regs_c.swath_height,
		PTE_ROW_HEIGHT_LINEAR_C, &rq_regs->rq_regs_c.pte_row_height_linear);

पूर्ण

व्योम hubp2_validate_dml_output(काष्ठा hubp *hubp,
		काष्ठा dc_context *ctx,
		काष्ठा _vcs_dpi_display_rq_regs_st *dml_rq_regs,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dml_dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *dml_ttu_attr)
अणु
	काष्ठा dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	काष्ठा _vcs_dpi_display_rq_regs_st rq_regs = अणु0पूर्ण;
	काष्ठा _vcs_dpi_display_dlg_regs_st dlg_attr = अणु0पूर्ण;
	काष्ठा _vcs_dpi_display_ttu_regs_st ttu_attr = अणु0पूर्ण;
	DC_LOGGER_INIT(ctx->logger);
	DC_LOG_DEBUG("DML Validation | Running Validation");

	/* Requestor Regs */
	REG_GET(HUBPRET_CONTROL,
		DET_BUF_PLANE1_BASE_ADDRESS, &rq_regs.plane1_base_address);
	REG_GET_4(DCN_EXPANSION_MODE,
		DRQ_EXPANSION_MODE, &rq_regs.drq_expansion_mode,
		PRQ_EXPANSION_MODE, &rq_regs.prq_expansion_mode,
		MRQ_EXPANSION_MODE, &rq_regs.mrq_expansion_mode,
		CRQ_EXPANSION_MODE, &rq_regs.crq_expansion_mode);
	REG_GET_8(DCHUBP_REQ_SIZE_CONFIG,
		CHUNK_SIZE, &rq_regs.rq_regs_l.chunk_size,
		MIN_CHUNK_SIZE, &rq_regs.rq_regs_l.min_chunk_size,
		META_CHUNK_SIZE, &rq_regs.rq_regs_l.meta_chunk_size,
		MIN_META_CHUNK_SIZE, &rq_regs.rq_regs_l.min_meta_chunk_size,
		DPTE_GROUP_SIZE, &rq_regs.rq_regs_l.dpte_group_size,
		MPTE_GROUP_SIZE, &rq_regs.rq_regs_l.mpte_group_size,
		SWATH_HEIGHT, &rq_regs.rq_regs_l.swath_height,
		PTE_ROW_HEIGHT_LINEAR, &rq_regs.rq_regs_l.pte_row_height_linear);
	REG_GET_8(DCHUBP_REQ_SIZE_CONFIG_C,
		CHUNK_SIZE_C, &rq_regs.rq_regs_c.chunk_size,
		MIN_CHUNK_SIZE_C, &rq_regs.rq_regs_c.min_chunk_size,
		META_CHUNK_SIZE_C, &rq_regs.rq_regs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, &rq_regs.rq_regs_c.min_meta_chunk_size,
		DPTE_GROUP_SIZE_C, &rq_regs.rq_regs_c.dpte_group_size,
		MPTE_GROUP_SIZE_C, &rq_regs.rq_regs_c.mpte_group_size,
		SWATH_HEIGHT_C, &rq_regs.rq_regs_c.swath_height,
		PTE_ROW_HEIGHT_LINEAR_C, &rq_regs.rq_regs_c.pte_row_height_linear);

	अगर (rq_regs.plane1_base_address != dml_rq_regs->plane1_base_address)
		DC_LOG_DEBUG("DML Validation | HUBPRET_CONTROL:DET_BUF_PLANE1_BASE_ADDRESS - Expected: %u  Actual: %u\n",
				dml_rq_regs->plane1_base_address, rq_regs.plane1_base_address);
	अगर (rq_regs.drq_expansion_mode != dml_rq_regs->drq_expansion_mode)
		DC_LOG_DEBUG("DML Validation | DCN_EXPANSION_MODE:DRQ_EXPANSION_MODE - Expected: %u  Actual: %u\n",
				dml_rq_regs->drq_expansion_mode, rq_regs.drq_expansion_mode);
	अगर (rq_regs.prq_expansion_mode != dml_rq_regs->prq_expansion_mode)
		DC_LOG_DEBUG("DML Validation | DCN_EXPANSION_MODE:MRQ_EXPANSION_MODE - Expected: %u  Actual: %u\n",
				dml_rq_regs->prq_expansion_mode, rq_regs.prq_expansion_mode);
	अगर (rq_regs.mrq_expansion_mode != dml_rq_regs->mrq_expansion_mode)
		DC_LOG_DEBUG("DML Validation | DCN_EXPANSION_MODE:DET_BUF_PLANE1_BASE_ADDRESS - Expected: %u  Actual: %u\n",
				dml_rq_regs->mrq_expansion_mode, rq_regs.mrq_expansion_mode);
	अगर (rq_regs.crq_expansion_mode != dml_rq_regs->crq_expansion_mode)
		DC_LOG_DEBUG("DML Validation | DCN_EXPANSION_MODE:CRQ_EXPANSION_MODE - Expected: %u  Actual: %u\n",
				dml_rq_regs->crq_expansion_mode, rq_regs.crq_expansion_mode);

	अगर (rq_regs.rq_regs_l.chunk_size != dml_rq_regs->rq_regs_l.chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:CHUNK_SIZE - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.chunk_size, rq_regs.rq_regs_l.chunk_size);
	अगर (rq_regs.rq_regs_l.min_chunk_size != dml_rq_regs->rq_regs_l.min_chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:MIN_CHUNK_SIZE - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.min_chunk_size, rq_regs.rq_regs_l.min_chunk_size);
	अगर (rq_regs.rq_regs_l.meta_chunk_size != dml_rq_regs->rq_regs_l.meta_chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:META_CHUNK_SIZE - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.meta_chunk_size, rq_regs.rq_regs_l.meta_chunk_size);
	अगर (rq_regs.rq_regs_l.min_meta_chunk_size != dml_rq_regs->rq_regs_l.min_meta_chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:MIN_META_CHUNK_SIZE - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.min_meta_chunk_size, rq_regs.rq_regs_l.min_meta_chunk_size);
	अगर (rq_regs.rq_regs_l.dpte_group_size != dml_rq_regs->rq_regs_l.dpte_group_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:DPTE_GROUP_SIZE - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.dpte_group_size, rq_regs.rq_regs_l.dpte_group_size);
	अगर (rq_regs.rq_regs_l.mpte_group_size != dml_rq_regs->rq_regs_l.mpte_group_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:MPTE_GROUP_SIZE - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.mpte_group_size, rq_regs.rq_regs_l.mpte_group_size);
	अगर (rq_regs.rq_regs_l.swath_height != dml_rq_regs->rq_regs_l.swath_height)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:SWATH_HEIGHT - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.swath_height, rq_regs.rq_regs_l.swath_height);
	अगर (rq_regs.rq_regs_l.pte_row_height_linear != dml_rq_regs->rq_regs_l.pte_row_height_linear)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG_C:PTE_ROW_HEIGHT_LINEAR - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_l.pte_row_height_linear, rq_regs.rq_regs_l.pte_row_height_linear);

	अगर (rq_regs.rq_regs_c.chunk_size != dml_rq_regs->rq_regs_c.chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:CHUNK_SIZE_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.chunk_size, rq_regs.rq_regs_c.chunk_size);
	अगर (rq_regs.rq_regs_c.min_chunk_size != dml_rq_regs->rq_regs_c.min_chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:MIN_CHUNK_SIZE_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.min_chunk_size, rq_regs.rq_regs_c.min_chunk_size);
	अगर (rq_regs.rq_regs_c.meta_chunk_size != dml_rq_regs->rq_regs_c.meta_chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:META_CHUNK_SIZE_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.meta_chunk_size, rq_regs.rq_regs_c.meta_chunk_size);
	अगर (rq_regs.rq_regs_c.min_meta_chunk_size != dml_rq_regs->rq_regs_c.min_meta_chunk_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:MIN_META_CHUNK_SIZE_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.min_meta_chunk_size, rq_regs.rq_regs_c.min_meta_chunk_size);
	अगर (rq_regs.rq_regs_c.dpte_group_size != dml_rq_regs->rq_regs_c.dpte_group_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:DPTE_GROUP_SIZE_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.dpte_group_size, rq_regs.rq_regs_c.dpte_group_size);
	अगर (rq_regs.rq_regs_c.mpte_group_size != dml_rq_regs->rq_regs_c.mpte_group_size)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:MPTE_GROUP_SIZE_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.mpte_group_size, rq_regs.rq_regs_c.mpte_group_size);
	अगर (rq_regs.rq_regs_c.swath_height != dml_rq_regs->rq_regs_c.swath_height)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:SWATH_HEIGHT_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.swath_height, rq_regs.rq_regs_c.swath_height);
	अगर (rq_regs.rq_regs_c.pte_row_height_linear != dml_rq_regs->rq_regs_c.pte_row_height_linear)
		DC_LOG_DEBUG("DML Validation | DCHUBP_REQ_SIZE_CONFIG:PTE_ROW_HEIGHT_LINEAR_C - Expected: %u  Actual: %u\n",
				dml_rq_regs->rq_regs_c.pte_row_height_linear, rq_regs.rq_regs_c.pte_row_height_linear);

	/* DLG - Per hubp */
	REG_GET_2(BLANK_OFFSET_0,
		REFCYC_H_BLANK_END, &dlg_attr.refcyc_h_blank_end,
		DLG_V_BLANK_END, &dlg_attr.dlg_vblank_end);
	REG_GET(BLANK_OFFSET_1,
		MIN_DST_Y_NEXT_START, &dlg_attr.min_dst_y_next_start);
	REG_GET(DST_DIMENSIONS,
		REFCYC_PER_HTOTAL, &dlg_attr.refcyc_per_htotal);
	REG_GET_2(DST_AFTER_SCALER,
		REFCYC_X_AFTER_SCALER, &dlg_attr.refcyc_x_after_scaler,
		DST_Y_AFTER_SCALER, &dlg_attr.dst_y_after_scaler);
	REG_GET(REF_FREQ_TO_PIX_FREQ,
		REF_FREQ_TO_PIX_FREQ, &dlg_attr.ref_freq_to_pix_freq);

	अगर (dlg_attr.refcyc_h_blank_end != dml_dlg_attr->refcyc_h_blank_end)
		DC_LOG_DEBUG("DML Validation | BLANK_OFFSET_0:REFCYC_H_BLANK_END - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_h_blank_end, dlg_attr.refcyc_h_blank_end);
	अगर (dlg_attr.dlg_vblank_end != dml_dlg_attr->dlg_vblank_end)
		DC_LOG_DEBUG("DML Validation | BLANK_OFFSET_0:DLG_V_BLANK_END - Expected: %u  Actual: %u\n",
				dml_dlg_attr->dlg_vblank_end, dlg_attr.dlg_vblank_end);
	अगर (dlg_attr.min_dst_y_next_start != dml_dlg_attr->min_dst_y_next_start)
		DC_LOG_DEBUG("DML Validation | BLANK_OFFSET_1:MIN_DST_Y_NEXT_START - Expected: %u  Actual: %u\n",
				dml_dlg_attr->min_dst_y_next_start, dlg_attr.min_dst_y_next_start);
	अगर (dlg_attr.refcyc_per_htotal != dml_dlg_attr->refcyc_per_htotal)
		DC_LOG_DEBUG("DML Validation | DST_DIMENSIONS:REFCYC_PER_HTOTAL - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_htotal, dlg_attr.refcyc_per_htotal);
	अगर (dlg_attr.refcyc_x_after_scaler != dml_dlg_attr->refcyc_x_after_scaler)
		DC_LOG_DEBUG("DML Validation | DST_AFTER_SCALER:REFCYC_X_AFTER_SCALER - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_x_after_scaler, dlg_attr.refcyc_x_after_scaler);
	अगर (dlg_attr.dst_y_after_scaler != dml_dlg_attr->dst_y_after_scaler)
		DC_LOG_DEBUG("DML Validation | DST_AFTER_SCALER:DST_Y_AFTER_SCALER - Expected: %u  Actual: %u\n",
				dml_dlg_attr->dst_y_after_scaler, dlg_attr.dst_y_after_scaler);
	अगर (dlg_attr.ref_freq_to_pix_freq != dml_dlg_attr->ref_freq_to_pix_freq)
		DC_LOG_DEBUG("DML Validation | REF_FREQ_TO_PIX_FREQ:REF_FREQ_TO_PIX_FREQ - Expected: %u  Actual: %u\n",
				dml_dlg_attr->ref_freq_to_pix_freq, dlg_attr.ref_freq_to_pix_freq);

	/* DLG - Per luma/chroma */
	REG_GET(VBLANK_PARAMETERS_1,
		REFCYC_PER_PTE_GROUP_VBLANK_L, &dlg_attr.refcyc_per_pte_group_vblank_l);
	अगर (REG(NOM_PARAMETERS_0))
		REG_GET(NOM_PARAMETERS_0,
			DST_Y_PER_PTE_ROW_NOM_L, &dlg_attr.dst_y_per_pte_row_nom_l);
	अगर (REG(NOM_PARAMETERS_1))
		REG_GET(NOM_PARAMETERS_1,
			REFCYC_PER_PTE_GROUP_NOM_L, &dlg_attr.refcyc_per_pte_group_nom_l);
	REG_GET(NOM_PARAMETERS_4,
		DST_Y_PER_META_ROW_NOM_L, &dlg_attr.dst_y_per_meta_row_nom_l);
	REG_GET(NOM_PARAMETERS_5,
		REFCYC_PER_META_CHUNK_NOM_L, &dlg_attr.refcyc_per_meta_chunk_nom_l);
	REG_GET_2(PER_LINE_DELIVERY,
		REFCYC_PER_LINE_DELIVERY_L, &dlg_attr.refcyc_per_line_delivery_l,
		REFCYC_PER_LINE_DELIVERY_C, &dlg_attr.refcyc_per_line_delivery_c);
	REG_GET_2(PER_LINE_DELIVERY_PRE,
		REFCYC_PER_LINE_DELIVERY_PRE_L, &dlg_attr.refcyc_per_line_delivery_pre_l,
		REFCYC_PER_LINE_DELIVERY_PRE_C, &dlg_attr.refcyc_per_line_delivery_pre_c);
	REG_GET(VBLANK_PARAMETERS_2,
		REFCYC_PER_PTE_GROUP_VBLANK_C, &dlg_attr.refcyc_per_pte_group_vblank_c);
	अगर (REG(NOM_PARAMETERS_2))
		REG_GET(NOM_PARAMETERS_2,
			DST_Y_PER_PTE_ROW_NOM_C, &dlg_attr.dst_y_per_pte_row_nom_c);
	अगर (REG(NOM_PARAMETERS_3))
		REG_GET(NOM_PARAMETERS_3,
			REFCYC_PER_PTE_GROUP_NOM_C, &dlg_attr.refcyc_per_pte_group_nom_c);
	REG_GET(NOM_PARAMETERS_6,
		DST_Y_PER_META_ROW_NOM_C, &dlg_attr.dst_y_per_meta_row_nom_c);
	REG_GET(NOM_PARAMETERS_7,
		REFCYC_PER_META_CHUNK_NOM_C, &dlg_attr.refcyc_per_meta_chunk_nom_c);
	REG_GET(VBLANK_PARAMETERS_3,
			REFCYC_PER_META_CHUNK_VBLANK_L, &dlg_attr.refcyc_per_meta_chunk_vblank_l);
	REG_GET(VBLANK_PARAMETERS_4,
			REFCYC_PER_META_CHUNK_VBLANK_C, &dlg_attr.refcyc_per_meta_chunk_vblank_c);

	अगर (dlg_attr.refcyc_per_pte_group_vblank_l != dml_dlg_attr->refcyc_per_pte_group_vblank_l)
		DC_LOG_DEBUG("DML Validation | VBLANK_PARAMETERS_1:REFCYC_PER_PTE_GROUP_VBLANK_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_pte_group_vblank_l, dlg_attr.refcyc_per_pte_group_vblank_l);
	अगर (dlg_attr.dst_y_per_pte_row_nom_l != dml_dlg_attr->dst_y_per_pte_row_nom_l)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_0:DST_Y_PER_PTE_ROW_NOM_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->dst_y_per_pte_row_nom_l, dlg_attr.dst_y_per_pte_row_nom_l);
	अगर (dlg_attr.refcyc_per_pte_group_nom_l != dml_dlg_attr->refcyc_per_pte_group_nom_l)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_1:REFCYC_PER_PTE_GROUP_NOM_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_pte_group_nom_l, dlg_attr.refcyc_per_pte_group_nom_l);
	अगर (dlg_attr.dst_y_per_meta_row_nom_l != dml_dlg_attr->dst_y_per_meta_row_nom_l)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_4:DST_Y_PER_META_ROW_NOM_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->dst_y_per_meta_row_nom_l, dlg_attr.dst_y_per_meta_row_nom_l);
	अगर (dlg_attr.refcyc_per_meta_chunk_nom_l != dml_dlg_attr->refcyc_per_meta_chunk_nom_l)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_5:REFCYC_PER_META_CHUNK_NOM_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_meta_chunk_nom_l, dlg_attr.refcyc_per_meta_chunk_nom_l);
	अगर (dlg_attr.refcyc_per_line_delivery_l != dml_dlg_attr->refcyc_per_line_delivery_l)
		DC_LOG_DEBUG("DML Validation | PER_LINE_DELIVERY:REFCYC_PER_LINE_DELIVERY_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_line_delivery_l, dlg_attr.refcyc_per_line_delivery_l);
	अगर (dlg_attr.refcyc_per_line_delivery_c != dml_dlg_attr->refcyc_per_line_delivery_c)
		DC_LOG_DEBUG("DML Validation | PER_LINE_DELIVERY:REFCYC_PER_LINE_DELIVERY_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_line_delivery_c, dlg_attr.refcyc_per_line_delivery_c);
	अगर (dlg_attr.refcyc_per_pte_group_vblank_c != dml_dlg_attr->refcyc_per_pte_group_vblank_c)
		DC_LOG_DEBUG("DML Validation | VBLANK_PARAMETERS_2:REFCYC_PER_PTE_GROUP_VBLANK_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_pte_group_vblank_c, dlg_attr.refcyc_per_pte_group_vblank_c);
	अगर (dlg_attr.dst_y_per_pte_row_nom_c != dml_dlg_attr->dst_y_per_pte_row_nom_c)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_2:DST_Y_PER_PTE_ROW_NOM_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->dst_y_per_pte_row_nom_c, dlg_attr.dst_y_per_pte_row_nom_c);
	अगर (dlg_attr.refcyc_per_pte_group_nom_c != dml_dlg_attr->refcyc_per_pte_group_nom_c)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_3:REFCYC_PER_PTE_GROUP_NOM_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_pte_group_nom_c, dlg_attr.refcyc_per_pte_group_nom_c);
	अगर (dlg_attr.dst_y_per_meta_row_nom_c != dml_dlg_attr->dst_y_per_meta_row_nom_c)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_6:DST_Y_PER_META_ROW_NOM_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->dst_y_per_meta_row_nom_c, dlg_attr.dst_y_per_meta_row_nom_c);
	अगर (dlg_attr.refcyc_per_meta_chunk_nom_c != dml_dlg_attr->refcyc_per_meta_chunk_nom_c)
		DC_LOG_DEBUG("DML Validation | NOM_PARAMETERS_7:REFCYC_PER_META_CHUNK_NOM_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_meta_chunk_nom_c, dlg_attr.refcyc_per_meta_chunk_nom_c);
	अगर (dlg_attr.refcyc_per_line_delivery_pre_l != dml_dlg_attr->refcyc_per_line_delivery_pre_l)
		DC_LOG_DEBUG("DML Validation | PER_LINE_DELIVERY_PRE:REFCYC_PER_LINE_DELIVERY_PRE_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_line_delivery_pre_l, dlg_attr.refcyc_per_line_delivery_pre_l);
	अगर (dlg_attr.refcyc_per_line_delivery_pre_c != dml_dlg_attr->refcyc_per_line_delivery_pre_c)
		DC_LOG_DEBUG("DML Validation | PER_LINE_DELIVERY_PRE:REFCYC_PER_LINE_DELIVERY_PRE_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_line_delivery_pre_c, dlg_attr.refcyc_per_line_delivery_pre_c);
	अगर (dlg_attr.refcyc_per_meta_chunk_vblank_l != dml_dlg_attr->refcyc_per_meta_chunk_vblank_l)
		DC_LOG_DEBUG("DML Validation | VBLANK_PARAMETERS_3:REFCYC_PER_META_CHUNK_VBLANK_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_meta_chunk_vblank_l, dlg_attr.refcyc_per_meta_chunk_vblank_l);
	अगर (dlg_attr.refcyc_per_meta_chunk_vblank_c != dml_dlg_attr->refcyc_per_meta_chunk_vblank_c)
		DC_LOG_DEBUG("DML Validation | VBLANK_PARAMETERS_4:REFCYC_PER_META_CHUNK_VBLANK_C - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_meta_chunk_vblank_c, dlg_attr.refcyc_per_meta_chunk_vblank_c);

	/* TTU - per hubp */
	REG_GET_2(DCN_TTU_QOS_WM,
		QoS_LEVEL_LOW_WM, &ttu_attr.qos_level_low_wm,
		QoS_LEVEL_HIGH_WM, &ttu_attr.qos_level_high_wm);

	अगर (ttu_attr.qos_level_low_wm != dml_ttu_attr->qos_level_low_wm)
		DC_LOG_DEBUG("DML Validation | DCN_TTU_QOS_WM:QoS_LEVEL_LOW_WM - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_level_low_wm, ttu_attr.qos_level_low_wm);
	अगर (ttu_attr.qos_level_high_wm != dml_ttu_attr->qos_level_high_wm)
		DC_LOG_DEBUG("DML Validation | DCN_TTU_QOS_WM:QoS_LEVEL_HIGH_WM - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_level_high_wm, ttu_attr.qos_level_high_wm);

	/* TTU - per luma/chroma */
	/* Assumed surf0 is luma and 1 is chroma */
	REG_GET_3(DCN_SURF0_TTU_CNTL0,
		REFCYC_PER_REQ_DELIVERY, &ttu_attr.refcyc_per_req_delivery_l,
		QoS_LEVEL_FIXED, &ttu_attr.qos_level_fixed_l,
		QoS_RAMP_DISABLE, &ttu_attr.qos_ramp_disable_l);
	REG_GET_3(DCN_SURF1_TTU_CNTL0,
		REFCYC_PER_REQ_DELIVERY, &ttu_attr.refcyc_per_req_delivery_c,
		QoS_LEVEL_FIXED, &ttu_attr.qos_level_fixed_c,
		QoS_RAMP_DISABLE, &ttu_attr.qos_ramp_disable_c);
	REG_GET_3(DCN_CUR0_TTU_CNTL0,
		REFCYC_PER_REQ_DELIVERY, &ttu_attr.refcyc_per_req_delivery_cur0,
		QoS_LEVEL_FIXED, &ttu_attr.qos_level_fixed_cur0,
		QoS_RAMP_DISABLE, &ttu_attr.qos_ramp_disable_cur0);
	REG_GET(FLIP_PARAMETERS_1,
		REFCYC_PER_PTE_GROUP_FLIP_L, &dlg_attr.refcyc_per_pte_group_flip_l);
	REG_GET(DCN_CUR0_TTU_CNTL1,
			REFCYC_PER_REQ_DELIVERY_PRE, &ttu_attr.refcyc_per_req_delivery_pre_cur0);
	REG_GET(DCN_CUR1_TTU_CNTL1,
			REFCYC_PER_REQ_DELIVERY_PRE, &ttu_attr.refcyc_per_req_delivery_pre_cur1);
	REG_GET(DCN_SURF0_TTU_CNTL1,
			REFCYC_PER_REQ_DELIVERY_PRE, &ttu_attr.refcyc_per_req_delivery_pre_l);
	REG_GET(DCN_SURF1_TTU_CNTL1,
			REFCYC_PER_REQ_DELIVERY_PRE, &ttu_attr.refcyc_per_req_delivery_pre_c);

	अगर (ttu_attr.refcyc_per_req_delivery_l != dml_ttu_attr->refcyc_per_req_delivery_l)
		DC_LOG_DEBUG("DML Validation | DCN_SURF0_TTU_CNTL0:REFCYC_PER_REQ_DELIVERY - Expected: %u  Actual: %u\n",
				dml_ttu_attr->refcyc_per_req_delivery_l, ttu_attr.refcyc_per_req_delivery_l);
	अगर (ttu_attr.qos_level_fixed_l != dml_ttu_attr->qos_level_fixed_l)
		DC_LOG_DEBUG("DML Validation | DCN_SURF0_TTU_CNTL0:QoS_LEVEL_FIXED - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_level_fixed_l, ttu_attr.qos_level_fixed_l);
	अगर (ttu_attr.qos_ramp_disable_l != dml_ttu_attr->qos_ramp_disable_l)
		DC_LOG_DEBUG("DML Validation | DCN_SURF0_TTU_CNTL0:QoS_RAMP_DISABLE - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_ramp_disable_l, ttu_attr.qos_ramp_disable_l);
	अगर (ttu_attr.refcyc_per_req_delivery_c != dml_ttu_attr->refcyc_per_req_delivery_c)
		DC_LOG_DEBUG("DML Validation | DCN_SURF1_TTU_CNTL0:REFCYC_PER_REQ_DELIVERY - Expected: %u  Actual: %u\n",
				dml_ttu_attr->refcyc_per_req_delivery_c, ttu_attr.refcyc_per_req_delivery_c);
	अगर (ttu_attr.qos_level_fixed_c != dml_ttu_attr->qos_level_fixed_c)
		DC_LOG_DEBUG("DML Validation | DCN_SURF1_TTU_CNTL0:QoS_LEVEL_FIXED - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_level_fixed_c, ttu_attr.qos_level_fixed_c);
	अगर (ttu_attr.qos_ramp_disable_c != dml_ttu_attr->qos_ramp_disable_c)
		DC_LOG_DEBUG("DML Validation | DCN_SURF1_TTU_CNTL0:QoS_RAMP_DISABLE - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_ramp_disable_c, ttu_attr.qos_ramp_disable_c);
	अगर (ttu_attr.refcyc_per_req_delivery_cur0 != dml_ttu_attr->refcyc_per_req_delivery_cur0)
		DC_LOG_DEBUG("DML Validation | DCN_CUR0_TTU_CNTL0:REFCYC_PER_REQ_DELIVERY - Expected: %u  Actual: %u\n",
				dml_ttu_attr->refcyc_per_req_delivery_cur0, ttu_attr.refcyc_per_req_delivery_cur0);
	अगर (ttu_attr.qos_level_fixed_cur0 != dml_ttu_attr->qos_level_fixed_cur0)
		DC_LOG_DEBUG("DML Validation | DCN_CUR0_TTU_CNTL0:QoS_LEVEL_FIXED - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_level_fixed_cur0, ttu_attr.qos_level_fixed_cur0);
	अगर (ttu_attr.qos_ramp_disable_cur0 != dml_ttu_attr->qos_ramp_disable_cur0)
		DC_LOG_DEBUG("DML Validation | DCN_CUR0_TTU_CNTL0:QoS_RAMP_DISABLE - Expected: %u  Actual: %u\n",
				dml_ttu_attr->qos_ramp_disable_cur0, ttu_attr.qos_ramp_disable_cur0);
	अगर (dlg_attr.refcyc_per_pte_group_flip_l != dml_dlg_attr->refcyc_per_pte_group_flip_l)
		DC_LOG_DEBUG("DML Validation | FLIP_PARAMETERS_1:REFCYC_PER_PTE_GROUP_FLIP_L - Expected: %u  Actual: %u\n",
				dml_dlg_attr->refcyc_per_pte_group_flip_l, dlg_attr.refcyc_per_pte_group_flip_l);
	अगर (ttu_attr.refcyc_per_req_delivery_pre_cur0 != dml_ttu_attr->refcyc_per_req_delivery_pre_cur0)
		DC_LOG_DEBUG("DML Validation | DCN_CUR0_TTU_CNTL1:REFCYC_PER_REQ_DELIVERY_PRE - Expected: %u  Actual: %u\n",
				dml_ttu_attr->refcyc_per_req_delivery_pre_cur0, ttu_attr.refcyc_per_req_delivery_pre_cur0);
	अगर (ttu_attr.refcyc_per_req_delivery_pre_cur1 != dml_ttu_attr->refcyc_per_req_delivery_pre_cur1)
		DC_LOG_DEBUG("DML Validation | DCN_CUR1_TTU_CNTL1:REFCYC_PER_REQ_DELIVERY_PRE - Expected: %u  Actual: %u\n",
				dml_ttu_attr->refcyc_per_req_delivery_pre_cur1, ttu_attr.refcyc_per_req_delivery_pre_cur1);
	अगर (ttu_attr.refcyc_per_req_delivery_pre_l != dml_ttu_attr->refcyc_per_req_delivery_pre_l)
		DC_LOG_DEBUG("DML Validation | DCN_SURF0_TTU_CNTL1:REFCYC_PER_REQ_DELIVERY_PRE - Expected: %u  Actual: %u\n",
				dml_ttu_attr->refcyc_per_req_delivery_pre_l, ttu_attr.refcyc_per_req_delivery_pre_l);
	अगर (ttu_attr.refcyc_per_req_delivery_pre_c != dml_ttu_attr->refcyc_per_req_delivery_pre_c)
		DC_LOG_DEBUG("DML Validation | DCN_SURF1_TTU_CNTL1:REFCYC_PER_REQ_DELIVERY_PRE - Expected: %u  Actual: %u\n",
				dml_ttu_attr->refcyc_per_req_delivery_pre_c, ttu_attr.refcyc_per_req_delivery_pre_c);
पूर्ण

अटल काष्ठा hubp_funcs dcn20_hubp_funcs = अणु
	.hubp_enable_tripleBuffer = hubp2_enable_triplebuffer,
	.hubp_is_triplebuffer_enabled = hubp2_is_triplebuffer_enabled,
	.hubp_program_surface_flip_and_addr = hubp2_program_surface_flip_and_addr,
	.hubp_program_surface_config = hubp2_program_surface_config,
	.hubp_is_flip_pending = hubp2_is_flip_pending,
	.hubp_setup = hubp2_setup,
	.hubp_setup_पूर्णांकerdependent = hubp2_setup_पूर्णांकerdependent,
	.hubp_set_vm_प्रणाली_aperture_settings = hubp2_set_vm_प्रणाली_aperture_settings,
	.set_blank = hubp2_set_blank,
	.dcc_control = hubp2_dcc_control,
	.mem_program_viewport = min_set_viewport,
	.set_cursor_attributes	= hubp2_cursor_set_attributes,
	.set_cursor_position	= hubp2_cursor_set_position,
	.hubp_clk_cntl = hubp2_clk_cntl,
	.hubp_vtg_sel = hubp2_vtg_sel,
	.dmdata_set_attributes = hubp2_dmdata_set_attributes,
	.dmdata_load = hubp2_dmdata_load,
	.dmdata_status_करोne = hubp2_dmdata_status_करोne,
	.hubp_पढ़ो_state = hubp2_पढ़ो_state,
	.hubp_clear_underflow = hubp2_clear_underflow,
	.hubp_set_flip_control_surface_gsl = hubp2_set_flip_control_surface_gsl,
	.hubp_init = hubp1_init,
	.validate_dml_output = hubp2_validate_dml_output,
	.hubp_in_blank = hubp1_in_blank,
	.hubp_soft_reset = hubp1_soft_reset,
	.hubp_set_flip_पूर्णांक = hubp1_set_flip_पूर्णांक,
पूर्ण;


bool hubp2_स्थिरruct(
	काष्ठा dcn20_hubp *hubp2,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn_hubp2_रेजिस्टरs *hubp_regs,
	स्थिर काष्ठा dcn_hubp2_shअगरt *hubp_shअगरt,
	स्थिर काष्ठा dcn_hubp2_mask *hubp_mask)
अणु
	hubp2->base.funcs = &dcn20_hubp_funcs;
	hubp2->base.ctx = ctx;
	hubp2->hubp_regs = hubp_regs;
	hubp2->hubp_shअगरt = hubp_shअगरt;
	hubp2->hubp_mask = hubp_mask;
	hubp2->base.inst = inst;
	hubp2->base.opp_id = OPP_ID_INVALID;
	hubp2->base.mpcc_id = 0xf;

	वापस true;
पूर्ण
