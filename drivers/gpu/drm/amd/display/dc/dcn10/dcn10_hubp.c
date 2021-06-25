<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
#समावेश "dm_services.h"
#समावेश "dce_calcs.h"
#समावेश "reg_helper.h"
#समावेश "basics/conversion.h"
#समावेश "dcn10_hubp.h"

#घोषणा REG(reg)\
	hubp1->hubp_regs->reg

#घोषणा CTX \
	hubp1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubp1->hubp_shअगरt->field_name, hubp1->hubp_mask->field_name

व्योम hubp1_set_blank(काष्ठा hubp *hubp, bool blank)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

अटल व्योम hubp1_disconnect(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE(DCHUBP_CNTL,
			HUBP_TTU_DISABLE, 1);

	REG_UPDATE(CURSOR_CONTROL,
			CURSOR_ENABLE, 0);
पूर्ण

अटल व्योम hubp1_disable_control(काष्ठा hubp *hubp, bool disable_hubp)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uपूर्णांक32_t disable = disable_hubp ? 1 : 0;

	REG_UPDATE(DCHUBP_CNTL,
			HUBP_DISABLE, disable);
पूर्ण

अटल अचिन्हित पूर्णांक hubp1_get_underflow_status(काष्ठा hubp *hubp)
अणु
	uपूर्णांक32_t hubp_underflow = 0;
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_GET(DCHUBP_CNTL,
		HUBP_UNDERFLOW_STATUS,
		&hubp_underflow);

	वापस hubp_underflow;
पूर्ण


व्योम hubp1_clear_underflow(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE(DCHUBP_CNTL, HUBP_UNDERFLOW_CLEAR, 1);
पूर्ण

अटल व्योम hubp1_set_hubp_blank_en(काष्ठा hubp *hubp, bool blank)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uपूर्णांक32_t blank_en = blank ? 1 : 0;

	REG_UPDATE(DCHUBP_CNTL, HUBP_BLANK_EN, blank_en);
पूर्ण

व्योम hubp1_vपढ़ोy_workaround(काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_pipe_dest_params_st *pipe_dest)
अणु
	uपूर्णांक32_t value = 0;
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	/* set HBUBREQ_DEBUG_DB[12] = 1 */
	value = REG_READ(HUBPREQ_DEBUG_DB);

	/* hack mode disable */
	value |= 0x100;
	value &= ~0x1000;

	अगर ((pipe_dest->vstartup_start - 2*(pipe_dest->vपढ़ोy_offset+pipe_dest->vupdate_width
		+ pipe_dest->vupdate_offset) / pipe_dest->htotal) <= pipe_dest->vblank_end) अणु
		/* अगर (eco_fix_needed(otg_global_sync_timing)
		 * set HBUBREQ_DEBUG_DB[12] = 1 */
		value |= 0x1000;
	पूर्ण

	REG_WRITE(HUBPREQ_DEBUG_DB, value);
पूर्ण

व्योम hubp1_program_tiling(
	काष्ठा hubp *hubp,
	स्थिर जोड़ dc_tiling_info *info,
	स्थिर क्रमागत surface_pixel_क्रमmat pixel_क्रमmat)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE_6(DCSURF_ADDR_CONFIG,
			NUM_PIPES, log_2(info->gfx9.num_pipes),
			NUM_BANKS, log_2(info->gfx9.num_banks),
			PIPE_INTERLEAVE, info->gfx9.pipe_पूर्णांकerleave,
			NUM_SE, log_2(info->gfx9.num_shader_engines),
			NUM_RB_PER_SE, log_2(info->gfx9.num_rb_per_se),
			MAX_COMPRESSED_FRAGS, log_2(info->gfx9.max_compressed_frags));

	REG_UPDATE_4(DCSURF_TILING_CONFIG,
			SW_MODE, info->gfx9.swizzle,
			META_LINEAR, info->gfx9.meta_linear,
			RB_ALIGNED, info->gfx9.rb_aligned,
			PIPE_ALIGNED, info->gfx9.pipe_aligned);
पूर्ण

व्योम hubp1_program_size(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	स्थिर काष्ठा plane_size *plane_size,
	काष्ठा dc_plane_dcc_param *dcc)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uपूर्णांक32_t pitch, meta_pitch, pitch_c, meta_pitch_c;

	/* Program data and meta surface pitch (calculation from addrlib)
	 * 444 or 420 luma
	 */
	अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN && क्रमmat < SURFACE_PIXEL_FORMAT_SUBSAMPLE_END) अणु
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

	अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		REG_UPDATE_2(DCSURF_SURFACE_PITCH_C,
			PITCH_C, pitch_c, META_PITCH_C, meta_pitch_c);
पूर्ण

व्योम hubp1_program_rotation(
	काष्ठा hubp *hubp,
	क्रमागत dc_rotation_angle rotation,
	bool horizontal_mirror)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

व्योम hubp1_program_pixel_क्रमmat(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

bool hubp1_program_surface_flip_and_addr(
	काष्ठा hubp *hubp,
	स्थिर काष्ठा dc_plane_address *address,
	bool flip_immediate)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);


	//program flip type
	REG_UPDATE(DCSURF_FLIP_CONTROL,
			SURFACE_FLIP_TYPE, flip_immediate);


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

व्योम hubp1_dcc_control(काष्ठा hubp *hubp, bool enable,
		क्रमागत hubp_ind_block_size independent_64b_blks)
अणु
	uपूर्णांक32_t dcc_en = enable ? 1 : 0;
	uपूर्णांक32_t dcc_ind_64b_blk = independent_64b_blks ? 1 : 0;
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE_4(DCSURF_SURFACE_CONTROL,
			PRIMARY_SURFACE_DCC_EN, dcc_en,
			PRIMARY_SURFACE_DCC_IND_64B_BLK, dcc_ind_64b_blk,
			SECONDARY_SURFACE_DCC_EN, dcc_en,
			SECONDARY_SURFACE_DCC_IND_64B_BLK, dcc_ind_64b_blk);
पूर्ण

व्योम hubp1_program_surface_config(
	काष्ठा hubp *hubp,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	जोड़ dc_tiling_info *tiling_info,
	काष्ठा plane_size *plane_size,
	क्रमागत dc_rotation_angle rotation,
	काष्ठा dc_plane_dcc_param *dcc,
	bool horizontal_mirror,
	अचिन्हित पूर्णांक compat_level)
अणु
	hubp1_dcc_control(hubp, dcc->enable, dcc->independent_64b_blks);
	hubp1_program_tiling(hubp, tiling_info, क्रमmat);
	hubp1_program_size(hubp, क्रमmat, plane_size, dcc);
	hubp1_program_rotation(hubp, rotation, horizontal_mirror);
	hubp1_program_pixel_क्रमmat(hubp, क्रमmat);
पूर्ण

व्योम hubp1_program_requestor(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

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


व्योम hubp1_program_deadline(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

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
पूर्ण

अटल व्योम hubp1_setup(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr,
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs,
		काष्ठा _vcs_dpi_display_pipe_dest_params_st *pipe_dest)
अणु
	/* otg is locked when this func is called. Register are द्विगुन buffered.
	 * disable the requestors is not needed
	 */
	hubp1_program_requestor(hubp, rq_regs);
	hubp1_program_deadline(hubp, dlg_attr, ttu_attr);
	hubp1_vपढ़ोy_workaround(hubp, pipe_dest);
पूर्ण

अटल व्योम hubp1_setup_पूर्णांकerdependent(
		काष्ठा hubp *hubp,
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_attr,
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_attr)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_SET_2(PREFETCH_SETTINS, 0,
		DST_Y_PREFETCH, dlg_attr->dst_y_prefetch,
		VRATIO_PREFETCH, dlg_attr->vratio_prefetch);

	REG_SET(PREFETCH_SETTINS_C, 0,
		VRATIO_PREFETCH_C, dlg_attr->vratio_prefetch_c);

	REG_SET_2(VBLANK_PARAMETERS_0, 0,
		DST_Y_PER_VM_VBLANK, dlg_attr->dst_y_per_vm_vblank,
		DST_Y_PER_ROW_VBLANK, dlg_attr->dst_y_per_row_vblank);

	REG_SET(VBLANK_PARAMETERS_3, 0,
		REFCYC_PER_META_CHUNK_VBLANK_L, dlg_attr->refcyc_per_meta_chunk_vblank_l);

	REG_SET(VBLANK_PARAMETERS_4, 0,
		REFCYC_PER_META_CHUNK_VBLANK_C, dlg_attr->refcyc_per_meta_chunk_vblank_c);

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

	REG_SET_2(DCN_GLOBAL_TTU_CNTL, 0,
		MIN_TTU_VBLANK, ttu_attr->min_ttu_vblank,
		QoS_LEVEL_FLIP, ttu_attr->qos_level_flip);
पूर्ण

bool hubp1_is_flip_pending(काष्ठा hubp *hubp)
अणु
	uपूर्णांक32_t flip_pending = 0;
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

uपूर्णांक32_t aperture_शेष_प्रणाली = 1;
uपूर्णांक32_t context0_शेष_प्रणाली; /* = 0;*/

अटल व्योम hubp1_set_vm_प्रणाली_aperture_settings(काष्ठा hubp *hubp,
		काष्ठा vm_प्रणाली_aperture_param *apt)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	PHYSICAL_ADDRESS_LOC mc_vm_apt_शेष;
	PHYSICAL_ADDRESS_LOC mc_vm_apt_low;
	PHYSICAL_ADDRESS_LOC mc_vm_apt_high;

	mc_vm_apt_शेष.quad_part = apt->sys_शेष.quad_part >> 12;
	mc_vm_apt_low.quad_part = apt->sys_low.quad_part >> 12;
	mc_vm_apt_high.quad_part = apt->sys_high.quad_part >> 12;

	REG_SET_2(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB, 0,
		MC_VM_SYSTEM_APERTURE_DEFAULT_SYSTEM, aperture_शेष_प्रणाली, /* 1 = प्रणाली physical memory */
		MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB, mc_vm_apt_शेष.high_part);
	REG_SET(DCN_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB, 0,
		MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB, mc_vm_apt_शेष.low_part);

	REG_SET(DCN_VM_SYSTEM_APERTURE_LOW_ADDR_MSB, 0,
			MC_VM_SYSTEM_APERTURE_LOW_ADDR_MSB, mc_vm_apt_low.high_part);
	REG_SET(DCN_VM_SYSTEM_APERTURE_LOW_ADDR_LSB, 0,
			MC_VM_SYSTEM_APERTURE_LOW_ADDR_LSB, mc_vm_apt_low.low_part);

	REG_SET(DCN_VM_SYSTEM_APERTURE_HIGH_ADDR_MSB, 0,
			MC_VM_SYSTEM_APERTURE_HIGH_ADDR_MSB, mc_vm_apt_high.high_part);
	REG_SET(DCN_VM_SYSTEM_APERTURE_HIGH_ADDR_LSB, 0,
			MC_VM_SYSTEM_APERTURE_HIGH_ADDR_LSB, mc_vm_apt_high.low_part);
पूर्ण

अटल व्योम hubp1_set_vm_context0_settings(काष्ठा hubp *hubp,
		स्थिर काष्ठा vm_context0_param *vm0)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	/* pte base */
	REG_SET(DCN_VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_MSB, 0,
			VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_MSB, vm0->pte_base.high_part);
	REG_SET(DCN_VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LSB, 0,
			VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LSB, vm0->pte_base.low_part);

	/* pte start */
	REG_SET(DCN_VM_CONTEXT0_PAGE_TABLE_START_ADDR_MSB, 0,
			VM_CONTEXT0_PAGE_TABLE_START_ADDR_MSB, vm0->pte_start.high_part);
	REG_SET(DCN_VM_CONTEXT0_PAGE_TABLE_START_ADDR_LSB, 0,
			VM_CONTEXT0_PAGE_TABLE_START_ADDR_LSB, vm0->pte_start.low_part);

	/* pte end */
	REG_SET(DCN_VM_CONTEXT0_PAGE_TABLE_END_ADDR_MSB, 0,
			VM_CONTEXT0_PAGE_TABLE_END_ADDR_MSB, vm0->pte_end.high_part);
	REG_SET(DCN_VM_CONTEXT0_PAGE_TABLE_END_ADDR_LSB, 0,
			VM_CONTEXT0_PAGE_TABLE_END_ADDR_LSB, vm0->pte_end.low_part);

	/* fault handling */
	REG_SET_2(DCN_VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR_MSB, 0,
			VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR_MSB, vm0->fault_शेष.high_part,
			VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_SYSTEM, context0_शेष_प्रणाली);
	REG_SET(DCN_VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR_LSB, 0,
			VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR_LSB, vm0->fault_शेष.low_part);

	/* control: enable VM PTE*/
	REG_SET_2(DCN_VM_MX_L1_TLB_CNTL, 0,
			ENABLE_L1_TLB, 1,
			SYSTEM_ACCESS_MODE, 3);
पूर्ण

व्योम min_set_viewport(
	काष्ठा hubp *hubp,
	स्थिर काष्ठा rect *viewport,
	स्थिर काष्ठा rect *viewport_c)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_SET_2(DCSURF_PRI_VIEWPORT_DIMENSION, 0,
		  PRI_VIEWPORT_WIDTH, viewport->width,
		  PRI_VIEWPORT_HEIGHT, viewport->height);

	REG_SET_2(DCSURF_PRI_VIEWPORT_START, 0,
		  PRI_VIEWPORT_X_START, viewport->x,
		  PRI_VIEWPORT_Y_START, viewport->y);

	/*क्रम stereo*/
	REG_SET_2(DCSURF_SEC_VIEWPORT_DIMENSION, 0,
		  SEC_VIEWPORT_WIDTH, viewport->width,
		  SEC_VIEWPORT_HEIGHT, viewport->height);

	REG_SET_2(DCSURF_SEC_VIEWPORT_START, 0,
		  SEC_VIEWPORT_X_START, viewport->x,
		  SEC_VIEWPORT_Y_START, viewport->y);

	/* DC supports NV12 only at the moment */
	REG_SET_2(DCSURF_PRI_VIEWPORT_DIMENSION_C, 0,
		  PRI_VIEWPORT_WIDTH_C, viewport_c->width,
		  PRI_VIEWPORT_HEIGHT_C, viewport_c->height);

	REG_SET_2(DCSURF_PRI_VIEWPORT_START_C, 0,
		  PRI_VIEWPORT_X_START_C, viewport_c->x,
		  PRI_VIEWPORT_Y_START_C, viewport_c->y);

	REG_SET_2(DCSURF_SEC_VIEWPORT_DIMENSION_C, 0,
		  SEC_VIEWPORT_WIDTH_C, viewport_c->width,
		  SEC_VIEWPORT_HEIGHT_C, viewport_c->height);

	REG_SET_2(DCSURF_SEC_VIEWPORT_START_C, 0,
		  SEC_VIEWPORT_X_START_C, viewport_c->x,
		  SEC_VIEWPORT_Y_START_C, viewport_c->y);
पूर्ण

व्योम hubp1_पढ़ो_state_common(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	काष्ठा dcn_hubp_state *s = &hubp1->state;
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

व्योम hubp1_पढ़ो_state(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	काष्ठा dcn_hubp_state *s = &hubp1->state;
	काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs = &s->rq_regs;

	hubp1_पढ़ो_state_common(hubp);

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
क्रमागत cursor_pitch hubp1_get_cursor_pitch(अचिन्हित पूर्णांक pitch)
अणु
	क्रमागत cursor_pitch hw_pitch;

	चयन (pitch) अणु
	हाल 64:
		hw_pitch = CURSOR_PITCH_64_PIXELS;
		अवरोध;
	हाल 128:
		hw_pitch = CURSOR_PITCH_128_PIXELS;
		अवरोध;
	हाल 256:
		hw_pitch = CURSOR_PITCH_256_PIXELS;
		अवरोध;
	शेष:
		DC_ERR("Invalid cursor pitch of %d. "
				"Only 64/128/256 is supported on DCN.\n", pitch);
		hw_pitch = CURSOR_PITCH_64_PIXELS;
		अवरोध;
	पूर्ण
	वापस hw_pitch;
पूर्ण

अटल क्रमागत cursor_lines_per_chunk hubp1_get_lines_per_chunk(
		अचिन्हित पूर्णांक cur_width,
		क्रमागत dc_cursor_color_क्रमmat क्रमmat)
अणु
	क्रमागत cursor_lines_per_chunk line_per_chunk;

	अगर (क्रमmat == CURSOR_MODE_MONO)
		/* impl B. expansion in CUR Buffer पढ़ोer */
		line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
	अन्यथा अगर (cur_width <= 32)
		line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
	अन्यथा अगर (cur_width <= 64)
		line_per_chunk = CURSOR_LINE_PER_CHUNK_8;
	अन्यथा अगर (cur_width <= 128)
		line_per_chunk = CURSOR_LINE_PER_CHUNK_4;
	अन्यथा
		line_per_chunk = CURSOR_LINE_PER_CHUNK_2;

	वापस line_per_chunk;
पूर्ण

व्योम hubp1_cursor_set_attributes(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_cursor_attributes *attr)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	क्रमागत cursor_pitch hw_pitch = hubp1_get_cursor_pitch(attr->pitch);
	क्रमागत cursor_lines_per_chunk lpc = hubp1_get_lines_per_chunk(
			attr->width, attr->color_क्रमmat);

	hubp->curs_attr = *attr;

	REG_UPDATE(CURSOR_SURFACE_ADDRESS_HIGH,
			CURSOR_SURFACE_ADDRESS_HIGH, attr->address.high_part);
	REG_UPDATE(CURSOR_SURFACE_ADDRESS,
			CURSOR_SURFACE_ADDRESS, attr->address.low_part);

	REG_UPDATE_2(CURSOR_SIZE,
			CURSOR_WIDTH, attr->width,
			CURSOR_HEIGHT, attr->height);

	REG_UPDATE_3(CURSOR_CONTROL,
			CURSOR_MODE, attr->color_क्रमmat,
			CURSOR_PITCH, hw_pitch,
			CURSOR_LINES_PER_CHUNK, lpc);

	REG_SET_2(CURSOR_SETTINS, 0,
			/* no shअगरt of the cursor HDL schedule */
			CURSOR0_DST_Y_OFFSET, 0,
			 /* used to shअगरt the cursor chunk request deadline */
			CURSOR0_CHUNK_HDL_ADJUST, 3);
पूर्ण

व्योम hubp1_cursor_set_position(
		काष्ठा hubp *hubp,
		स्थिर काष्ठा dc_cursor_position *pos,
		स्थिर काष्ठा dc_cursor_mi_param *param)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
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

व्योम hubp1_clk_cntl(काष्ठा hubp *hubp, bool enable)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	uपूर्णांक32_t clk_enable = enable ? 1 : 0;

	REG_UPDATE(HUBP_CLK_CNTL, HUBP_CLOCK_ENABLE, clk_enable);
पूर्ण

व्योम hubp1_vtg_sel(काष्ठा hubp *hubp, uपूर्णांक32_t otg_inst)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE(DCHUBP_CNTL, HUBP_VTG_SEL, otg_inst);
पूर्ण

bool hubp1_in_blank(काष्ठा hubp *hubp)
अणु
	uपूर्णांक32_t in_blank;
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_GET(DCHUBP_CNTL, HUBP_IN_BLANK, &in_blank);
	वापस in_blank ? true : false;
पूर्ण

व्योम hubp1_soft_reset(काष्ठा hubp *hubp, bool reset)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE(DCHUBP_CNTL, HUBP_DISABLE, reset ? 1 : 0);
पूर्ण

व्योम hubp1_set_flip_पूर्णांक(काष्ठा hubp *hubp)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE(DCSURF_SURFACE_FLIP_INTERRUPT,
		SURFACE_FLIP_INT_MASK, 1);

	वापस;
पूर्ण

व्योम hubp1_init(काष्ठा hubp *hubp)
अणु
	//करो nothing
पूर्ण
अटल स्थिर काष्ठा hubp_funcs dcn10_hubp_funcs = अणु
	.hubp_program_surface_flip_and_addr =
			hubp1_program_surface_flip_and_addr,
	.hubp_program_surface_config =
			hubp1_program_surface_config,
	.hubp_is_flip_pending = hubp1_is_flip_pending,
	.hubp_setup = hubp1_setup,
	.hubp_setup_पूर्णांकerdependent = hubp1_setup_पूर्णांकerdependent,
	.hubp_set_vm_प्रणाली_aperture_settings = hubp1_set_vm_प्रणाली_aperture_settings,
	.hubp_set_vm_context0_settings = hubp1_set_vm_context0_settings,
	.set_blank = hubp1_set_blank,
	.dcc_control = hubp1_dcc_control,
	.mem_program_viewport = min_set_viewport,
	.set_hubp_blank_en = hubp1_set_hubp_blank_en,
	.set_cursor_attributes	= hubp1_cursor_set_attributes,
	.set_cursor_position	= hubp1_cursor_set_position,
	.hubp_disconnect = hubp1_disconnect,
	.hubp_clk_cntl = hubp1_clk_cntl,
	.hubp_vtg_sel = hubp1_vtg_sel,
	.hubp_पढ़ो_state = hubp1_पढ़ो_state,
	.hubp_clear_underflow = hubp1_clear_underflow,
	.hubp_disable_control =  hubp1_disable_control,
	.hubp_get_underflow_status = hubp1_get_underflow_status,
	.hubp_init = hubp1_init,

	.dmdata_set_attributes = शून्य,
	.dmdata_load = शून्य,
	.hubp_soft_reset = hubp1_soft_reset,
	.hubp_in_blank = hubp1_in_blank,
	.hubp_set_flip_पूर्णांक = hubp1_set_flip_पूर्णांक,
पूर्ण;

/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

व्योम dcn10_hubp_स्थिरruct(
	काष्ठा dcn10_hubp *hubp1,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn_mi_रेजिस्टरs *hubp_regs,
	स्थिर काष्ठा dcn_mi_shअगरt *hubp_shअगरt,
	स्थिर काष्ठा dcn_mi_mask *hubp_mask)
अणु
	hubp1->base.funcs = &dcn10_hubp_funcs;
	hubp1->base.ctx = ctx;
	hubp1->hubp_regs = hubp_regs;
	hubp1->hubp_shअगरt = hubp_shअगरt;
	hubp1->hubp_mask = hubp_mask;
	hubp1->base.inst = inst;
	hubp1->base.opp_id = OPP_ID_INVALID;
	hubp1->base.mpcc_id = 0xf;
पूर्ण


