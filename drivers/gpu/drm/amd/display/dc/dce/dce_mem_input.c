<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#समावेश "dce_mem_input.h"
#समावेश "reg_helper.h"
#समावेश "basics/conversion.h"

#घोषणा CTX \
	dce_mi->base.ctx
#घोषणा REG(reg)\
	dce_mi->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dce_mi->shअगरts->field_name, dce_mi->masks->field_name

काष्ठा pte_setting अणु
	अचिन्हित पूर्णांक bpp;
	अचिन्हित पूर्णांक page_width;
	अचिन्हित पूर्णांक page_height;
	अचिन्हित अक्षर min_pte_beक्रमe_flip_horiz_scan;
	अचिन्हित अक्षर min_pte_beक्रमe_flip_vert_scan;
	अचिन्हित अक्षर pte_req_per_chunk;
	अचिन्हित अक्षर param_6;
	अचिन्हित अक्षर param_7;
	अचिन्हित अक्षर param_8;
पूर्ण;

क्रमागत mi_bits_per_pixel अणु
	mi_bpp_8 = 0,
	mi_bpp_16,
	mi_bpp_32,
	mi_bpp_64,
	mi_bpp_count,
पूर्ण;

क्रमागत mi_tiling_क्रमmat अणु
	mi_tiling_linear = 0,
	mi_tiling_1D,
	mi_tiling_2D,
	mi_tiling_count,
पूर्ण;

अटल स्थिर काष्ठा pte_setting pte_settings[mi_tiling_count][mi_bpp_count] = अणु
	[mi_tiling_linear] = अणु
		अणु  8, 4096, 1, 8, 0, 1, 0, 0, 0पूर्ण,
		अणु 16, 2048, 1, 8, 0, 1, 0, 0, 0पूर्ण,
		अणु 32, 1024, 1, 8, 0, 1, 0, 0, 0पूर्ण,
		अणु 64,  512, 1, 8, 0, 1, 0, 0, 0पूर्ण, /* new क्रम 64bpp from HW */
	पूर्ण,
	[mi_tiling_1D] = अणु
		अणु  8, 512, 8, 1, 0, 1, 0, 0, 0पूर्ण,  /* 0 क्रम invalid */
		अणु 16, 256, 8, 2, 0, 1, 0, 0, 0पूर्ण,
		अणु 32, 128, 8, 4, 0, 1, 0, 0, 0पूर्ण,
		अणु 64,  64, 8, 4, 0, 1, 0, 0, 0पूर्ण, /* fake */
	पूर्ण,
	[mi_tiling_2D] = अणु
		अणु  8, 64, 64,  8,  8, 1, 4, 0, 0पूर्ण,
		अणु 16, 64, 32,  8, 16, 1, 8, 0, 0पूर्ण,
		अणु 32, 32, 32, 16, 16, 1, 8, 0, 0पूर्ण,
		अणु 64,  8, 32, 16, 16, 1, 8, 0, 0पूर्ण, /* fake */
	पूर्ण,
पूर्ण;

अटल क्रमागत mi_bits_per_pixel get_mi_bpp(
		क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616)
		वापस mi_bpp_64;
	अन्यथा अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_GRPH_ARGB8888)
		वापस mi_bpp_32;
	अन्यथा अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_GRPH_ARGB1555)
		वापस mi_bpp_16;
	अन्यथा
		वापस mi_bpp_8;
पूर्ण

अटल क्रमागत mi_tiling_क्रमmat get_mi_tiling(
		जोड़ dc_tiling_info *tiling_info)
अणु
	चयन (tiling_info->gfx8.array_mode) अणु
	हाल DC_ARRAY_1D_TILED_THIN1:
	हाल DC_ARRAY_1D_TILED_THICK:
	हाल DC_ARRAY_PRT_TILED_THIN1:
		वापस mi_tiling_1D;
	हाल DC_ARRAY_2D_TILED_THIN1:
	हाल DC_ARRAY_2D_TILED_THICK:
	हाल DC_ARRAY_2D_TILED_X_THICK:
	हाल DC_ARRAY_PRT_2D_TILED_THIN1:
	हाल DC_ARRAY_PRT_2D_TILED_THICK:
		वापस mi_tiling_2D;
	हाल DC_ARRAY_LINEAR_GENERAL:
	हाल DC_ARRAY_LINEAR_ALLIGNED:
		वापस mi_tiling_linear;
	शेष:
		वापस mi_tiling_2D;
	पूर्ण
पूर्ण

अटल bool is_vert_scan(क्रमागत dc_rotation_angle rotation)
अणु
	चयन (rotation) अणु
	हाल ROTATION_ANGLE_90:
	हाल ROTATION_ANGLE_270:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम dce_mi_program_pte_vm(
		काष्ठा mem_input *mi,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		जोड़ dc_tiling_info *tiling_info,
		क्रमागत dc_rotation_angle rotation)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	क्रमागत mi_bits_per_pixel mi_bpp = get_mi_bpp(क्रमmat);
	क्रमागत mi_tiling_क्रमmat mi_tiling = get_mi_tiling(tiling_info);
	स्थिर काष्ठा pte_setting *pte = &pte_settings[mi_tiling][mi_bpp];

	अचिन्हित पूर्णांक page_width = log_2(pte->page_width);
	अचिन्हित पूर्णांक page_height = log_2(pte->page_height);
	अचिन्हित पूर्णांक min_pte_beक्रमe_flip = is_vert_scan(rotation) ?
			pte->min_pte_beक्रमe_flip_vert_scan :
			pte->min_pte_beक्रमe_flip_horiz_scan;

	REG_UPDATE(GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT,
			GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT, 0x7f);

	REG_UPDATE_3(DVMM_PTE_CONTROL,
			DVMM_PAGE_WIDTH, page_width,
			DVMM_PAGE_HEIGHT, page_height,
			DVMM_MIN_PTE_BEFORE_FLIP, min_pte_beक्रमe_flip);

	REG_UPDATE_2(DVMM_PTE_ARB_CONTROL,
			DVMM_PTE_REQ_PER_CHUNK, pte->pte_req_per_chunk,
			DVMM_MAX_PTE_REQ_OUTSTANDING, 0x7f);
पूर्ण

अटल व्योम program_urgency_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t urgency_low_wm,
	uपूर्णांक32_t urgency_high_wm)
अणु
	REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
		URGENCY_WATERMARK_MASK, wm_select);

	REG_SET_2(DPG_PIPE_URGENCY_CONTROL, 0,
		URGENCY_LOW_WATERMARK, urgency_low_wm,
		URGENCY_HIGH_WATERMARK, urgency_high_wm);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_program_urgency_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t urgency_low_wm,
	uपूर्णांक32_t urgency_high_wm)
अणु
	REG_UPDATE(DPG_PIPE_ARBITRATION_CONTROL3,
		URGENCY_WATERMARK_MASK, wm_select);

	REG_SET_2(DPG_PIPE_URGENCY_CONTROL, 0,
		URGENCY_LOW_WATERMARK, urgency_low_wm,
		URGENCY_HIGH_WATERMARK, urgency_high_wm);
पूर्ण
#पूर्ण_अगर

अटल व्योम dce120_program_urgency_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t urgency_low_wm,
	uपूर्णांक32_t urgency_high_wm)
अणु
	REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
		URGENCY_WATERMARK_MASK, wm_select);

	REG_SET_2(DPG_PIPE_URGENCY_CONTROL, 0,
		URGENCY_LOW_WATERMARK, urgency_low_wm,
		URGENCY_HIGH_WATERMARK, urgency_high_wm);

	REG_SET_2(DPG_PIPE_URGENT_LEVEL_CONTROL, 0,
		URGENT_LEVEL_LOW_WATERMARK, urgency_low_wm,
		URGENT_LEVEL_HIGH_WATERMARK, urgency_high_wm);

पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_program_nbp_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t nbp_wm)
अणु
	REG_UPDATE(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_WATERMARK_MASK, wm_select);

	REG_UPDATE_3(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_ENABLE, 1,
		NB_PSTATE_CHANGE_URGENT_DURING_REQUEST, 1,
		NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, 1);

	REG_UPDATE(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_WATERMARK, nbp_wm);
पूर्ण
#पूर्ण_अगर

अटल व्योम program_nbp_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t nbp_wm)
अणु
	अगर (REG(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL)) अणु
		REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
				NB_PSTATE_CHANGE_WATERMARK_MASK, wm_select);

		REG_UPDATE_3(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL,
				NB_PSTATE_CHANGE_ENABLE, 1,
				NB_PSTATE_CHANGE_URGENT_DURING_REQUEST, 1,
				NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, 1);

		REG_UPDATE(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL,
				NB_PSTATE_CHANGE_WATERMARK, nbp_wm);
	पूर्ण

	अगर (REG(DPG_PIPE_LOW_POWER_CONTROL)) अणु
		REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
				PSTATE_CHANGE_WATERMARK_MASK, wm_select);

		REG_UPDATE_3(DPG_PIPE_LOW_POWER_CONTROL,
				PSTATE_CHANGE_ENABLE, 1,
				PSTATE_CHANGE_URGENT_DURING_REQUEST, 1,
				PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, 1);

		REG_UPDATE(DPG_PIPE_LOW_POWER_CONTROL,
				PSTATE_CHANGE_WATERMARK, nbp_wm);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_program_stutter_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t stutter_mark)
अणु
	REG_UPDATE(DPG_PIPE_STUTTER_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK, wm_select);

	REG_UPDATE(DPG_PIPE_STUTTER_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK, stutter_mark);
पूर्ण
#पूर्ण_अगर

अटल व्योम dce120_program_stutter_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t stutter_mark,
	uपूर्णांक32_t stutter_entry)
अणु
	REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK, wm_select);

	अगर (REG(DPG_PIPE_STUTTER_CONTROL2))
		REG_UPDATE_2(DPG_PIPE_STUTTER_CONTROL2,
				STUTTER_EXIT_SELF_REFRESH_WATERMARK, stutter_mark,
				STUTTER_ENTER_SELF_REFRESH_WATERMARK, stutter_entry);
	अन्यथा
		REG_UPDATE_2(DPG_PIPE_STUTTER_CONTROL,
				STUTTER_EXIT_SELF_REFRESH_WATERMARK, stutter_mark,
				STUTTER_ENTER_SELF_REFRESH_WATERMARK, stutter_entry);
पूर्ण

अटल व्योम program_stutter_watermark(
	काष्ठा dce_mem_input *dce_mi,
	uपूर्णांक32_t wm_select,
	uपूर्णांक32_t stutter_mark)
अणु
	REG_UPDATE(DPG_WATERMARK_MASK_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK, wm_select);

	अगर (REG(DPG_PIPE_STUTTER_CONTROL2))
		REG_UPDATE(DPG_PIPE_STUTTER_CONTROL2,
				STUTTER_EXIT_SELF_REFRESH_WATERMARK, stutter_mark);
	अन्यथा
		REG_UPDATE(DPG_PIPE_STUTTER_CONTROL,
				STUTTER_EXIT_SELF_REFRESH_WATERMARK, stutter_mark);
पूर्ण

अटल व्योम dce_mi_program_display_marks(
	काष्ठा mem_input *mi,
	काष्ठा dce_watermarks nbp,
	काष्ठा dce_watermarks stutter_निकास,
	काष्ठा dce_watermarks stutter_enter,
	काष्ठा dce_watermarks urgent,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	uपूर्णांक32_t stutter_en = mi->ctx->dc->debug.disable_stutter ? 0 : 1;

	program_urgency_watermark(dce_mi, 2, /* set a */
			urgent.a_mark, total_dest_line_समय_ns);
	program_urgency_watermark(dce_mi, 1, /* set d */
			urgent.d_mark, total_dest_line_समय_ns);

	REG_UPDATE_2(DPG_PIPE_STUTTER_CONTROL,
		STUTTER_ENABLE, stutter_en,
		STUTTER_IGNORE_FBC, 1);
	program_nbp_watermark(dce_mi, 2, nbp.a_mark); /* set a */
	program_nbp_watermark(dce_mi, 1, nbp.d_mark); /* set d */

	program_stutter_watermark(dce_mi, 2, stutter_निकास.a_mark); /* set a */
	program_stutter_watermark(dce_mi, 1, stutter_निकास.d_mark); /* set d */
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_mi_program_display_marks(
	काष्ठा mem_input *mi,
	काष्ठा dce_watermarks nbp,
	काष्ठा dce_watermarks stutter_निकास,
	काष्ठा dce_watermarks stutter_enter,
	काष्ठा dce_watermarks urgent,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	uपूर्णांक32_t stutter_en = mi->ctx->dc->debug.disable_stutter ? 0 : 1;

	dce60_program_urgency_watermark(dce_mi, 2, /* set a */
			urgent.a_mark, total_dest_line_समय_ns);
	dce60_program_urgency_watermark(dce_mi, 1, /* set d */
			urgent.d_mark, total_dest_line_समय_ns);

	REG_UPDATE_2(DPG_PIPE_STUTTER_CONTROL,
		STUTTER_ENABLE, stutter_en,
		STUTTER_IGNORE_FBC, 1);
	dce60_program_nbp_watermark(dce_mi, 2, nbp.a_mark); /* set a */
	dce60_program_nbp_watermark(dce_mi, 1, nbp.d_mark); /* set d */

	dce60_program_stutter_watermark(dce_mi, 2, stutter_निकास.a_mark); /* set a */
	dce60_program_stutter_watermark(dce_mi, 1, stutter_निकास.d_mark); /* set d */
पूर्ण
#पूर्ण_अगर

अटल व्योम dce112_mi_program_display_marks(काष्ठा mem_input *mi,
	काष्ठा dce_watermarks nbp,
	काष्ठा dce_watermarks stutter_निकास,
	काष्ठा dce_watermarks stutter_entry,
	काष्ठा dce_watermarks urgent,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	uपूर्णांक32_t stutter_en = mi->ctx->dc->debug.disable_stutter ? 0 : 1;

	program_urgency_watermark(dce_mi, 0, /* set a */
			urgent.a_mark, total_dest_line_समय_ns);
	program_urgency_watermark(dce_mi, 1, /* set b */
			urgent.b_mark, total_dest_line_समय_ns);
	program_urgency_watermark(dce_mi, 2, /* set c */
			urgent.c_mark, total_dest_line_समय_ns);
	program_urgency_watermark(dce_mi, 3, /* set d */
			urgent.d_mark, total_dest_line_समय_ns);

	REG_UPDATE_2(DPG_PIPE_STUTTER_CONTROL,
		STUTTER_ENABLE, stutter_en,
		STUTTER_IGNORE_FBC, 1);
	program_nbp_watermark(dce_mi, 0, nbp.a_mark); /* set a */
	program_nbp_watermark(dce_mi, 1, nbp.b_mark); /* set b */
	program_nbp_watermark(dce_mi, 2, nbp.c_mark); /* set c */
	program_nbp_watermark(dce_mi, 3, nbp.d_mark); /* set d */

	program_stutter_watermark(dce_mi, 0, stutter_निकास.a_mark); /* set a */
	program_stutter_watermark(dce_mi, 1, stutter_निकास.b_mark); /* set b */
	program_stutter_watermark(dce_mi, 2, stutter_निकास.c_mark); /* set c */
	program_stutter_watermark(dce_mi, 3, stutter_निकास.d_mark); /* set d */
पूर्ण

अटल व्योम dce120_mi_program_display_marks(काष्ठा mem_input *mi,
	काष्ठा dce_watermarks nbp,
	काष्ठा dce_watermarks stutter_निकास,
	काष्ठा dce_watermarks stutter_entry,
	काष्ठा dce_watermarks urgent,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	uपूर्णांक32_t stutter_en = mi->ctx->dc->debug.disable_stutter ? 0 : 1;

	dce120_program_urgency_watermark(dce_mi, 0, /* set a */
			urgent.a_mark, total_dest_line_समय_ns);
	dce120_program_urgency_watermark(dce_mi, 1, /* set b */
			urgent.b_mark, total_dest_line_समय_ns);
	dce120_program_urgency_watermark(dce_mi, 2, /* set c */
			urgent.c_mark, total_dest_line_समय_ns);
	dce120_program_urgency_watermark(dce_mi, 3, /* set d */
			urgent.d_mark, total_dest_line_समय_ns);

	REG_UPDATE_2(DPG_PIPE_STUTTER_CONTROL,
		STUTTER_ENABLE, stutter_en,
		STUTTER_IGNORE_FBC, 1);
	program_nbp_watermark(dce_mi, 0, nbp.a_mark); /* set a */
	program_nbp_watermark(dce_mi, 1, nbp.b_mark); /* set b */
	program_nbp_watermark(dce_mi, 2, nbp.c_mark); /* set c */
	program_nbp_watermark(dce_mi, 3, nbp.d_mark); /* set d */

	dce120_program_stutter_watermark(dce_mi, 0, stutter_निकास.a_mark, stutter_entry.a_mark); /* set a */
	dce120_program_stutter_watermark(dce_mi, 1, stutter_निकास.b_mark, stutter_entry.b_mark); /* set b */
	dce120_program_stutter_watermark(dce_mi, 2, stutter_निकास.c_mark, stutter_entry.c_mark); /* set c */
	dce120_program_stutter_watermark(dce_mi, 3, stutter_निकास.d_mark, stutter_entry.d_mark); /* set d */
पूर्ण

अटल व्योम program_tiling(
	काष्ठा dce_mem_input *dce_mi, स्थिर जोड़ dc_tiling_info *info)
अणु
	अगर (dce_mi->masks->GRPH_SW_MODE) अणु /* GFX9 */
		REG_UPDATE_6(GRPH_CONTROL,
				GRPH_SW_MODE, info->gfx9.swizzle,
				GRPH_NUM_BANKS, log_2(info->gfx9.num_banks),
				GRPH_NUM_SHADER_ENGINES, log_2(info->gfx9.num_shader_engines),
				GRPH_NUM_PIPES, log_2(info->gfx9.num_pipes),
				GRPH_COLOR_EXPANSION_MODE, 1,
				GRPH_SE_ENABLE, info->gfx9.shaderEnable);
		/* TODO: DCP0_GRPH_CONTROL__GRPH_SE_ENABLE where to get info
		GRPH_SE_ENABLE, 1,
		GRPH_Z, 0);
		 */
	पूर्ण

	अगर (dce_mi->masks->GRPH_MICRO_TILE_MODE) अणु /* GFX8 */
		REG_UPDATE_9(GRPH_CONTROL,
				GRPH_NUM_BANKS, info->gfx8.num_banks,
				GRPH_BANK_WIDTH, info->gfx8.bank_width,
				GRPH_BANK_HEIGHT, info->gfx8.bank_height,
				GRPH_MACRO_TILE_ASPECT, info->gfx8.tile_aspect,
				GRPH_TILE_SPLIT, info->gfx8.tile_split,
				GRPH_MICRO_TILE_MODE, info->gfx8.tile_mode,
				GRPH_PIPE_CONFIG, info->gfx8.pipe_config,
				GRPH_ARRAY_MODE, info->gfx8.array_mode,
				GRPH_COLOR_EXPANSION_MODE, 1);
		/* 01 - DCP_GRPH_COLOR_EXPANSION_MODE_ZEXP: zero expansion क्रम YCbCr */
		/*
				GRPH_Z, 0);
				*/
	पूर्ण

	अगर (dce_mi->masks->GRPH_ARRAY_MODE) अणु /* GFX6 but reuses gfx8 काष्ठा */
		REG_UPDATE_8(GRPH_CONTROL,
				GRPH_NUM_BANKS, info->gfx8.num_banks,
				GRPH_BANK_WIDTH, info->gfx8.bank_width,
				GRPH_BANK_HEIGHT, info->gfx8.bank_height,
				GRPH_MACRO_TILE_ASPECT, info->gfx8.tile_aspect,
				GRPH_TILE_SPLIT, info->gfx8.tile_split,
				/* DCE6 has no GRPH_MICRO_TILE_MODE mask */
				GRPH_PIPE_CONFIG, info->gfx8.pipe_config,
				GRPH_ARRAY_MODE, info->gfx8.array_mode,
				GRPH_COLOR_EXPANSION_MODE, 1);
		/* 01 - DCP_GRPH_COLOR_EXPANSION_MODE_ZEXP: zero expansion क्रम YCbCr */
		/*
				GRPH_Z, 0);
				*/
	पूर्ण
पूर्ण


अटल व्योम program_size_and_rotation(
	काष्ठा dce_mem_input *dce_mi,
	क्रमागत dc_rotation_angle rotation,
	स्थिर काष्ठा plane_size *plane_size)
अणु
	स्थिर काष्ठा rect *in_rect = &plane_size->surface_size;
	काष्ठा rect hw_rect = plane_size->surface_size;
	स्थिर uपूर्णांक32_t rotation_angles[ROTATION_ANGLE_COUNT] = अणु
			[ROTATION_ANGLE_0] = 0,
			[ROTATION_ANGLE_90] = 1,
			[ROTATION_ANGLE_180] = 2,
			[ROTATION_ANGLE_270] = 3,
	पूर्ण;

	अगर (rotation == ROTATION_ANGLE_90 || rotation == ROTATION_ANGLE_270) अणु
		hw_rect.x = in_rect->y;
		hw_rect.y = in_rect->x;

		hw_rect.height = in_rect->width;
		hw_rect.width = in_rect->height;
	पूर्ण

	REG_SET(GRPH_X_START, 0,
			GRPH_X_START, hw_rect.x);

	REG_SET(GRPH_Y_START, 0,
			GRPH_Y_START, hw_rect.y);

	REG_SET(GRPH_X_END, 0,
			GRPH_X_END, hw_rect.width);

	REG_SET(GRPH_Y_END, 0,
			GRPH_Y_END, hw_rect.height);

	REG_SET(GRPH_PITCH, 0,
			GRPH_PITCH, plane_size->surface_pitch);

	REG_SET(HW_ROTATION, 0,
			GRPH_ROTATION_ANGLE, rotation_angles[rotation]);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_program_size(
	काष्ठा dce_mem_input *dce_mi,
	क्रमागत dc_rotation_angle rotation, /* not used in DCE6 */
	स्थिर काष्ठा plane_size *plane_size)
अणु
	काष्ठा rect hw_rect = plane_size->surface_size;
	/* DCE6 has no HW rotation, skip rotation_angles declaration */

	/* DCE6 has no HW rotation, skip ROTATION_ANGLE_* processing */

	REG_SET(GRPH_X_START, 0,
			GRPH_X_START, hw_rect.x);

	REG_SET(GRPH_Y_START, 0,
			GRPH_Y_START, hw_rect.y);

	REG_SET(GRPH_X_END, 0,
			GRPH_X_END, hw_rect.width);

	REG_SET(GRPH_Y_END, 0,
			GRPH_Y_END, hw_rect.height);

	REG_SET(GRPH_PITCH, 0,
			GRPH_PITCH, plane_size->surface_pitch);

	/* DCE6 has no HW_ROTATION रेजिस्टर, skip setting rotation_angles */
पूर्ण
#पूर्ण_अगर

अटल व्योम program_grph_pixel_क्रमmat(
	काष्ठा dce_mem_input *dce_mi,
	क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	uपूर्णांक32_t red_xbar = 0, blue_xbar = 0; /* no swap */
	uपूर्णांक32_t grph_depth = 0, grph_क्रमmat = 0;
	uपूर्णांक32_t sign = 0, भग्नing = 0;

	अगर (क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 ||
			/*toकरो: करोesn't look like we handle BGRA here,
			 *  should problem swap endian*/
		क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 ||
		क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS ||
		क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F) अणु
		/* ABGR क्रमmats */
		red_xbar = 2;
		blue_xbar = 2;
	पूर्ण

	REG_SET_2(GRPH_SWAP_CNTL, 0,
			GRPH_RED_CROSSBAR, red_xbar,
			GRPH_BLUE_CROSSBAR, blue_xbar);

	चयन (क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
		grph_depth = 0;
		grph_क्रमmat = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		grph_depth = 1;
		grph_क्रमmat = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		grph_depth = 1;
		grph_क्रमmat = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		grph_depth = 2;
		grph_क्रमmat = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		grph_depth = 2;
		grph_क्रमmat = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		sign = 1;
		भग्नing = 1;
		fallthrough;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F: /* shouldn't this get भग्न too? */
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		grph_depth = 3;
		grph_क्रमmat = 0;
		अवरोध;
	शेष:
		DC_ERR("unsupported grph pixel format");
		अवरोध;
	पूर्ण

	REG_UPDATE_2(GRPH_CONTROL,
			GRPH_DEPTH, grph_depth,
			GRPH_FORMAT, grph_क्रमmat);

	REG_UPDATE_4(PRESCALE_GRPH_CONTROL,
			GRPH_PRESCALE_SELECT, भग्नing,
			GRPH_PRESCALE_R_SIGN, sign,
			GRPH_PRESCALE_G_SIGN, sign,
			GRPH_PRESCALE_B_SIGN, sign);
पूर्ण

अटल व्योम dce_mi_program_surface_config(
	काष्ठा mem_input *mi,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	जोड़ dc_tiling_info *tiling_info,
	काष्ठा plane_size *plane_size,
	क्रमागत dc_rotation_angle rotation,
	काष्ठा dc_plane_dcc_param *dcc,
	bool horizontal_mirror)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	REG_UPDATE(GRPH_ENABLE, GRPH_ENABLE, 1);

	program_tiling(dce_mi, tiling_info);
	program_size_and_rotation(dce_mi, rotation, plane_size);

	अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_GRPH_BEGIN &&
		क्रमmat < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		program_grph_pixel_क्रमmat(dce_mi, क्रमmat);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_mi_program_surface_config(
	काष्ठा mem_input *mi,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	जोड़ dc_tiling_info *tiling_info,
	काष्ठा plane_size *plane_size,
	क्रमागत dc_rotation_angle rotation, /* not used in DCE6 */
	काष्ठा dc_plane_dcc_param *dcc,
	bool horizontal_mirror)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	REG_UPDATE(GRPH_ENABLE, GRPH_ENABLE, 1);

	program_tiling(dce_mi, tiling_info);
	dce60_program_size(dce_mi, rotation, plane_size);

	अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_GRPH_BEGIN &&
		क्रमmat < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		program_grph_pixel_क्रमmat(dce_mi, क्रमmat);
पूर्ण
#पूर्ण_अगर

अटल uपूर्णांक32_t get_dmअगर_चयन_समय_us(
	uपूर्णांक32_t h_total,
	uपूर्णांक32_t v_total,
	uपूर्णांक32_t pix_clk_khz)
अणु
	uपूर्णांक32_t frame_समय;
	uपूर्णांक32_t pixels_per_second;
	uपूर्णांक32_t pixels_per_frame;
	uपूर्णांक32_t refresh_rate;
	स्थिर uपूर्णांक32_t us_in_sec = 1000000;
	स्थिर uपूर्णांक32_t min_single_frame_समय_us = 30000;
	/*वापस द्विगुन of frame समय*/
	स्थिर uपूर्णांक32_t single_frame_समय_multiplier = 2;

	अगर (!h_total || v_total || !pix_clk_khz)
		वापस single_frame_समय_multiplier * min_single_frame_समय_us;

	/*TODO: should we use pixel क्रमmat normalized pixel घड़ी here?*/
	pixels_per_second = pix_clk_khz * 1000;
	pixels_per_frame = h_total * v_total;

	अगर (!pixels_per_second || !pixels_per_frame) अणु
		/* aव्योम भागision by zero */
		ASSERT(pixels_per_frame);
		ASSERT(pixels_per_second);
		वापस single_frame_समय_multiplier * min_single_frame_समय_us;
	पूर्ण

	refresh_rate = pixels_per_second / pixels_per_frame;

	अगर (!refresh_rate) अणु
		/* aव्योम भागision by zero*/
		ASSERT(refresh_rate);
		वापस single_frame_समय_multiplier * min_single_frame_समय_us;
	पूर्ण

	frame_समय = us_in_sec / refresh_rate;

	अगर (frame_समय < min_single_frame_समय_us)
		frame_समय = min_single_frame_समय_us;

	frame_समय *= single_frame_समय_multiplier;

	वापस frame_समय;
पूर्ण

अटल व्योम dce_mi_allocate_dmअगर(
	काष्ठा mem_input *mi,
	uपूर्णांक32_t h_total,
	uपूर्णांक32_t v_total,
	uपूर्णांक32_t pix_clk_khz,
	uपूर्णांक32_t total_stream_num)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	स्थिर uपूर्णांक32_t retry_delay = 10;
	uपूर्णांक32_t retry_count = get_dmअगर_चयन_समय_us(
			h_total,
			v_total,
			pix_clk_khz) / retry_delay;

	uपूर्णांक32_t pix_dur;
	uपूर्णांक32_t buffers_allocated;
	uपूर्णांक32_t dmअगर_buffer_control;

	dmअगर_buffer_control = REG_GET(DMIF_BUFFER_CONTROL,
			DMIF_BUFFERS_ALLOCATED, &buffers_allocated);

	अगर (buffers_allocated == 2)
		वापस;

	REG_SET(DMIF_BUFFER_CONTROL, dmअगर_buffer_control,
			DMIF_BUFFERS_ALLOCATED, 2);

	REG_WAIT(DMIF_BUFFER_CONTROL,
			DMIF_BUFFERS_ALLOCATION_COMPLETED, 1,
			retry_delay, retry_count);

	अगर (pix_clk_khz != 0) अणु
		pix_dur = 1000000000ULL / pix_clk_khz;

		REG_UPDATE(DPG_PIPE_ARBITRATION_CONTROL1,
			PIXEL_DURATION, pix_dur);
	पूर्ण

	अगर (dce_mi->wa.single_head_rdreq_dmअगर_limit) अणु
		uपूर्णांक32_t enable =  (total_stream_num > 1) ? 0 :
				dce_mi->wa.single_head_rdreq_dmअगर_limit;

		REG_UPDATE(MC_HUB_RDREQ_DMIF_LIMIT,
				ENABLE, enable);
	पूर्ण
पूर्ण

अटल व्योम dce_mi_मुक्त_dmअगर(
		काष्ठा mem_input *mi,
		uपूर्णांक32_t total_stream_num)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	uपूर्णांक32_t buffers_allocated;
	uपूर्णांक32_t dmअगर_buffer_control;

	dmअगर_buffer_control = REG_GET(DMIF_BUFFER_CONTROL,
			DMIF_BUFFERS_ALLOCATED, &buffers_allocated);

	अगर (buffers_allocated == 0)
		वापस;

	REG_SET(DMIF_BUFFER_CONTROL, dmअगर_buffer_control,
			DMIF_BUFFERS_ALLOCATED, 0);

	REG_WAIT(DMIF_BUFFER_CONTROL,
			DMIF_BUFFERS_ALLOCATION_COMPLETED, 1,
			10, 3500);

	अगर (dce_mi->wa.single_head_rdreq_dmअगर_limit) अणु
		uपूर्णांक32_t enable =  (total_stream_num > 1) ? 0 :
				dce_mi->wa.single_head_rdreq_dmअगर_limit;

		REG_UPDATE(MC_HUB_RDREQ_DMIF_LIMIT,
				ENABLE, enable);
	पूर्ण
पूर्ण


अटल व्योम program_sec_addr(
	काष्ठा dce_mem_input *dce_mi,
	PHYSICAL_ADDRESS_LOC address)
अणु
	/*high रेजिस्टर MUST be programmed first*/
	REG_SET(GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, 0,
		GRPH_SECONDARY_SURFACE_ADDRESS_HIGH,
		address.high_part);

	REG_SET_2(GRPH_SECONDARY_SURFACE_ADDRESS, 0,
		GRPH_SECONDARY_SURFACE_ADDRESS, address.low_part >> 8,
		GRPH_SECONDARY_DFQ_ENABLE, 0);
पूर्ण

अटल व्योम program_pri_addr(
	काष्ठा dce_mem_input *dce_mi,
	PHYSICAL_ADDRESS_LOC address)
अणु
	/*high रेजिस्टर MUST be programmed first*/
	REG_SET(GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, 0,
		GRPH_PRIMARY_SURFACE_ADDRESS_HIGH,
		address.high_part);

	REG_SET(GRPH_PRIMARY_SURFACE_ADDRESS, 0,
		GRPH_PRIMARY_SURFACE_ADDRESS,
		address.low_part >> 8);
पूर्ण


अटल bool dce_mi_is_flip_pending(काष्ठा mem_input *mem_input)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mem_input);
	uपूर्णांक32_t update_pending;

	REG_GET(GRPH_UPDATE, GRPH_SURFACE_UPDATE_PENDING, &update_pending);
	अगर (update_pending)
		वापस true;

	mem_input->current_address = mem_input->request_address;
	वापस false;
पूर्ण

अटल bool dce_mi_program_surface_flip_and_addr(
	काष्ठा mem_input *mem_input,
	स्थिर काष्ठा dc_plane_address *address,
	bool flip_immediate)
अणु
	काष्ठा dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mem_input);

	REG_UPDATE(GRPH_UPDATE, GRPH_UPDATE_LOCK, 1);

	REG_UPDATE(
		GRPH_FLIP_CONTROL,
		GRPH_SURFACE_UPDATE_H_RETRACE_EN, flip_immediate ? 1 : 0);

	चयन (address->type) अणु
	हाल PLN_ADDR_TYPE_GRAPHICS:
		अगर (address->grph.addr.quad_part == 0)
			अवरोध;
		program_pri_addr(dce_mi, address->grph.addr);
		अवरोध;
	हाल PLN_ADDR_TYPE_GRPH_STEREO:
		अगर (address->grph_stereo.left_addr.quad_part == 0 ||
		    address->grph_stereo.right_addr.quad_part == 0)
			अवरोध;
		program_pri_addr(dce_mi, address->grph_stereo.left_addr);
		program_sec_addr(dce_mi, address->grph_stereo.right_addr);
		अवरोध;
	शेष:
		/* not supported */
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	mem_input->request_address = *address;

	अगर (flip_immediate)
		mem_input->current_address = *address;

	REG_UPDATE(GRPH_UPDATE, GRPH_UPDATE_LOCK, 0);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा mem_input_funcs dce_mi_funcs = अणु
	.mem_input_program_display_marks = dce_mi_program_display_marks,
	.allocate_mem_input = dce_mi_allocate_dmअगर,
	.मुक्त_mem_input = dce_mi_मुक्त_dmअगर,
	.mem_input_program_surface_flip_and_addr =
			dce_mi_program_surface_flip_and_addr,
	.mem_input_program_pte_vm = dce_mi_program_pte_vm,
	.mem_input_program_surface_config =
			dce_mi_program_surface_config,
	.mem_input_is_flip_pending = dce_mi_is_flip_pending
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल स्थिर काष्ठा mem_input_funcs dce60_mi_funcs = अणु
	.mem_input_program_display_marks = dce60_mi_program_display_marks,
	.allocate_mem_input = dce_mi_allocate_dmअगर,
	.मुक्त_mem_input = dce_mi_मुक्त_dmअगर,
	.mem_input_program_surface_flip_and_addr =
			dce_mi_program_surface_flip_and_addr,
	.mem_input_program_pte_vm = dce_mi_program_pte_vm,
	.mem_input_program_surface_config =
			dce60_mi_program_surface_config,
	.mem_input_is_flip_pending = dce_mi_is_flip_pending
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा mem_input_funcs dce112_mi_funcs = अणु
	.mem_input_program_display_marks = dce112_mi_program_display_marks,
	.allocate_mem_input = dce_mi_allocate_dmअगर,
	.मुक्त_mem_input = dce_mi_मुक्त_dmअगर,
	.mem_input_program_surface_flip_and_addr =
			dce_mi_program_surface_flip_and_addr,
	.mem_input_program_pte_vm = dce_mi_program_pte_vm,
	.mem_input_program_surface_config =
			dce_mi_program_surface_config,
	.mem_input_is_flip_pending = dce_mi_is_flip_pending
पूर्ण;

अटल स्थिर काष्ठा mem_input_funcs dce120_mi_funcs = अणु
	.mem_input_program_display_marks = dce120_mi_program_display_marks,
	.allocate_mem_input = dce_mi_allocate_dmअगर,
	.मुक्त_mem_input = dce_mi_मुक्त_dmअगर,
	.mem_input_program_surface_flip_and_addr =
			dce_mi_program_surface_flip_and_addr,
	.mem_input_program_pte_vm = dce_mi_program_pte_vm,
	.mem_input_program_surface_config =
			dce_mi_program_surface_config,
	.mem_input_is_flip_pending = dce_mi_is_flip_pending
पूर्ण;

व्योम dce_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask)
अणु
	dce_mi->base.ctx = ctx;

	dce_mi->base.inst = inst;
	dce_mi->base.funcs = &dce_mi_funcs;

	dce_mi->regs = regs;
	dce_mi->shअगरts = mi_shअगरt;
	dce_mi->masks = mi_mask;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
व्योम dce60_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask)
अणु
	dce_mem_input_स्थिरruct(dce_mi, ctx, inst, regs, mi_shअगरt, mi_mask);
	dce_mi->base.funcs = &dce60_mi_funcs;
पूर्ण
#पूर्ण_अगर

व्योम dce112_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask)
अणु
	dce_mem_input_स्थिरruct(dce_mi, ctx, inst, regs, mi_shअगरt, mi_mask);
	dce_mi->base.funcs = &dce112_mi_funcs;
पूर्ण

व्योम dce120_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask)
अणु
	dce_mem_input_स्थिरruct(dce_mi, ctx, inst, regs, mi_shअगरt, mi_mask);
	dce_mi->base.funcs = &dce120_mi_funcs;
पूर्ण
