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


#समावेश "dm_services.h"
#समावेश "reg_helper.h"
#समावेश "dcn30_hubbub.h"


#घोषणा CTX \
	hubbub1->base.ctx
#घोषणा DC_LOGGER \
	hubbub1->base.ctx->logger
#घोषणा REG(reg)\
	hubbub1->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubbub1->shअगरts->field_name, hubbub1->masks->field_name

#अगर_घोषित NUM_VMID
#अघोषित NUM_VMID
#पूर्ण_अगर
#घोषणा NUM_VMID 16


अटल uपूर्णांक32_t convert_and_clamp(
	uपूर्णांक32_t wm_ns,
	uपूर्णांक32_t refclk_mhz,
	uपूर्णांक32_t clamp_value)
अणु
	uपूर्णांक32_t ret_val = 0;
	ret_val = wm_ns * refclk_mhz;
	ret_val /= 1000;

	अगर (ret_val > clamp_value)
		ret_val = clamp_value;

	वापस ret_val;
पूर्ण

पूर्णांक hubbub3_init_dchub_sys_ctx(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_phys_addr_config *pa_config)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	काष्ठा dcn_vmid_page_table_config phys_config;

	REG_SET(DCN_VM_FB_LOCATION_BASE, 0,
			FB_BASE, pa_config->प्रणाली_aperture.fb_base >> 24);
	REG_SET(DCN_VM_FB_LOCATION_TOP, 0,
			FB_TOP, pa_config->प्रणाली_aperture.fb_top >> 24);
	REG_SET(DCN_VM_FB_OFFSET, 0,
			FB_OFFSET, pa_config->प्रणाली_aperture.fb_offset >> 24);
	REG_SET(DCN_VM_AGP_BOT, 0,
			AGP_BOT, pa_config->प्रणाली_aperture.agp_bot >> 24);
	REG_SET(DCN_VM_AGP_TOP, 0,
			AGP_TOP, pa_config->प्रणाली_aperture.agp_top >> 24);
	REG_SET(DCN_VM_AGP_BASE, 0,
			AGP_BASE, pa_config->प्रणाली_aperture.agp_base >> 24);

	अगर (pa_config->gart_config.page_table_start_addr != pa_config->gart_config.page_table_end_addr) अणु
		phys_config.page_table_start_addr = pa_config->gart_config.page_table_start_addr >> 12;
		phys_config.page_table_end_addr = pa_config->gart_config.page_table_end_addr >> 12;
		phys_config.page_table_base_addr = pa_config->gart_config.page_table_base_addr;
		phys_config.depth = 0;
		phys_config.block_size = 0;
		// Init VMID 0 based on PA config
		dcn20_vmid_setup(&hubbub1->vmid[0], &phys_config);
	पूर्ण

	वापस NUM_VMID;
पूर्ण

bool hubbub3_program_watermarks(
		काष्ठा hubbub *hubbub,
		काष्ठा dcn_watermark_set *watermarks,
		अचिन्हित पूर्णांक refclk_mhz,
		bool safe_to_lower)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	bool wm_pending = false;

	अगर (hubbub21_program_urgent_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	अगर (hubbub21_program_stutter_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	अगर (hubbub21_program_pstate_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	/*
	 * The DCHub arbiter has a mechanism to dynamically rate limit the DCHub request stream to the fabric.
	 * If the memory controller is fully utilized and the DCHub requestors are
	 * well ahead of their amortized schedule, then it is safe to prevent the next winner
	 * from being committed and sent to the fabric.
	 * The utilization of the memory controller is approximated by ensuring that
	 * the number of outstanding requests is greater than a threshold specअगरied
	 * by the ARB_MIN_REQ_OUTSTANDING. To determine that the DCHub requestors are well ahead of the amortized schedule,
	 * the slack of the next winner is compared with the ARB_SAT_LEVEL in DLG RefClk cycles.
	 *
	 * TODO: Revisit request limit after figure out right number. request limit क्रम Renoir isn't decided yet, set maximum value (0x1FF)
	 * to turn off it क्रम now.
	 */
	REG_SET(DCHUBBUB_ARB_SAT_LEVEL, 0,
			DCHUBBUB_ARB_SAT_LEVEL, 60 * refclk_mhz);
	REG_UPDATE(DCHUBBUB_ARB_DF_REQ_OUTSTAND,
			DCHUBBUB_ARB_MIN_REQ_OUTSTAND, 0x1FF);

	hubbub1_allow_self_refresh_control(hubbub, !hubbub->ctx->dc->debug.disable_stutter);

	वापस wm_pending;
पूर्ण

bool hubbub3_dcc_support_swizzle(
		क्रमागत swizzle_mode_values swizzle,
		अचिन्हित पूर्णांक bytes_per_element,
		क्रमागत segment_order *segment_order_horz,
		क्रमागत segment_order *segment_order_vert)
अणु
	bool standard_swizzle = false;
	bool display_swizzle = false;
	bool render_swizzle = false;

	चयन (swizzle) अणु
	हाल DC_SW_4KB_S:
	हाल DC_SW_64KB_S:
	हाल DC_SW_VAR_S:
	हाल DC_SW_4KB_S_X:
	हाल DC_SW_64KB_S_X:
	हाल DC_SW_VAR_S_X:
		standard_swizzle = true;
		अवरोध;
	हाल DC_SW_4KB_R:
	हाल DC_SW_64KB_R:
	हाल DC_SW_VAR_R:
	हाल DC_SW_4KB_R_X:
	हाल DC_SW_64KB_R_X:
	हाल DC_SW_VAR_R_X:
		render_swizzle = true;
		अवरोध;
	हाल DC_SW_4KB_D:
	हाल DC_SW_64KB_D:
	हाल DC_SW_VAR_D:
	हाल DC_SW_4KB_D_X:
	हाल DC_SW_64KB_D_X:
	हाल DC_SW_VAR_D_X:
		display_swizzle = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (standard_swizzle) अणु
		अगर (bytes_per_element == 1) अणु
			*segment_order_horz = segment_order__contiguous;
			*segment_order_vert = segment_order__na;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 2) अणु
			*segment_order_horz = segment_order__non_contiguous;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 4) अणु
			*segment_order_horz = segment_order__non_contiguous;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 8) अणु
			*segment_order_horz = segment_order__na;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
	पूर्ण
	अगर (render_swizzle) अणु
		अगर (bytes_per_element == 1) अणु
			*segment_order_horz = segment_order__contiguous;
			*segment_order_vert = segment_order__na;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 2) अणु
			*segment_order_horz = segment_order__non_contiguous;
			*segment_order_vert = segment_order__contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 4) अणु
			*segment_order_horz = segment_order__contiguous;
			*segment_order_vert = segment_order__non_contiguous;
			वापस true;
		पूर्ण
		अगर (bytes_per_element == 8) अणु
			*segment_order_horz = segment_order__contiguous;
			*segment_order_vert = segment_order__non_contiguous;
			वापस true;
		पूर्ण
	पूर्ण
	अगर (display_swizzle && bytes_per_element == 8) अणु
		*segment_order_horz = segment_order__contiguous;
		*segment_order_vert = segment_order__non_contiguous;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hubbub3_get_blk256_size(अचिन्हित पूर्णांक *blk256_width, अचिन्हित पूर्णांक *blk256_height,
		अचिन्हित पूर्णांक bytes_per_element)
अणु
	/* copied from DML.  might want to refactor DML to leverage from DML */
	/* DML : get_blk256_size */
	अगर (bytes_per_element == 1) अणु
		*blk256_width = 16;
		*blk256_height = 16;
	पूर्ण अन्यथा अगर (bytes_per_element == 2) अणु
		*blk256_width = 16;
		*blk256_height = 8;
	पूर्ण अन्यथा अगर (bytes_per_element == 4) अणु
		*blk256_width = 8;
		*blk256_height = 8;
	पूर्ण अन्यथा अगर (bytes_per_element == 8) अणु
		*blk256_width = 8;
		*blk256_height = 4;
	पूर्ण
पूर्ण

अटल व्योम hubbub3_det_request_size(
		अचिन्हित पूर्णांक detile_buf_size,
		अचिन्हित पूर्णांक height,
		अचिन्हित पूर्णांक width,
		अचिन्हित पूर्णांक bpe,
		bool *req128_horz_wc,
		bool *req128_vert_wc)
अणु
	अचिन्हित पूर्णांक blk256_height = 0;
	अचिन्हित पूर्णांक blk256_width = 0;
	अचिन्हित पूर्णांक swath_bytes_horz_wc, swath_bytes_vert_wc;

	hubbub3_get_blk256_size(&blk256_width, &blk256_height, bpe);

	swath_bytes_horz_wc = width * blk256_height * bpe;
	swath_bytes_vert_wc = height * blk256_width * bpe;

	*req128_horz_wc = (2 * swath_bytes_horz_wc <= detile_buf_size) ?
			false : /* full 256B request */
			true; /* half 128b request */

	*req128_vert_wc = (2 * swath_bytes_vert_wc <= detile_buf_size) ?
			false : /* full 256B request */
			true; /* half 128b request */
पूर्ण

bool hubbub3_get_dcc_compression_cap(काष्ठा hubbub *hubbub,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output)
अणु
	काष्ठा dc *dc = hubbub->ctx->dc;
	/* implement section 1.6.2.1 of DCN1_Programming_Guide.करोcx */
	क्रमागत dcc_control dcc_control;
	अचिन्हित पूर्णांक bpe;
	क्रमागत segment_order segment_order_horz, segment_order_vert;
	bool req128_horz_wc, req128_vert_wc;

	स_रखो(output, 0, माप(*output));

	अगर (dc->debug.disable_dcc == DCC_DISABLE)
		वापस false;

	अगर (!hubbub->funcs->dcc_support_pixel_क्रमmat(input->क्रमmat,
			&bpe))
		वापस false;

	अगर (!hubbub->funcs->dcc_support_swizzle(input->swizzle_mode, bpe,
			&segment_order_horz, &segment_order_vert))
		वापस false;

	hubbub3_det_request_size(TO_DCN20_HUBBUB(hubbub)->detile_buf_size,
			input->surface_size.height,  input->surface_size.width,
			bpe, &req128_horz_wc, &req128_vert_wc);

	अगर (!req128_horz_wc && !req128_vert_wc) अणु
		dcc_control = dcc_control__256_256_xxx;
	पूर्ण अन्यथा अगर (input->scan == SCAN_सूचीECTION_HORIZONTAL) अणु
		अगर (!req128_horz_wc)
			dcc_control = dcc_control__256_256_xxx;
		अन्यथा अगर (segment_order_horz == segment_order__contiguous)
			dcc_control = dcc_control__128_128_xxx;
		अन्यथा
			dcc_control = dcc_control__256_64_64;
	पूर्ण अन्यथा अगर (input->scan == SCAN_सूचीECTION_VERTICAL) अणु
		अगर (!req128_vert_wc)
			dcc_control = dcc_control__256_256_xxx;
		अन्यथा अगर (segment_order_vert == segment_order__contiguous)
			dcc_control = dcc_control__128_128_xxx;
		अन्यथा
			dcc_control = dcc_control__256_64_64;
	पूर्ण अन्यथा अणु
		अगर ((req128_horz_wc &&
			segment_order_horz == segment_order__non_contiguous) ||
			(req128_vert_wc &&
			segment_order_vert == segment_order__non_contiguous))
			/* access_dir not known, must use most स्थिरraining */
			dcc_control = dcc_control__256_64_64;
		अन्यथा
			/* reg128 is true क्रम either horz and vert
			 * but segment_order is contiguous
			 */
			dcc_control = dcc_control__128_128_xxx;
	पूर्ण

	/* Exception क्रम 64KB_R_X */
	अगर ((bpe == 2) && (input->swizzle_mode == DC_SW_64KB_R_X))
		dcc_control = dcc_control__128_128_xxx;

	अगर (dc->debug.disable_dcc == DCC_HALF_REQ_DISALBE &&
		dcc_control != dcc_control__256_256_xxx)
		वापस false;

	चयन (dcc_control) अणु
	हाल dcc_control__256_256_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 256;
		output->grph.rgb.independent_64b_blks = false;
		output->grph.rgb.dcc_controls.dcc_256_256_unस्थिरrained = 1;
		output->grph.rgb.dcc_controls.dcc_256_128_128 = 1;
		अवरोध;
	हाल dcc_control__128_128_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 128;
		output->grph.rgb.max_compressed_blk_size = 128;
		output->grph.rgb.independent_64b_blks = false;
		output->grph.rgb.dcc_controls.dcc_128_128_uncontrained = 1;
		output->grph.rgb.dcc_controls.dcc_256_128_128 = 1;
		अवरोध;
	हाल dcc_control__256_64_64:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 64;
		output->grph.rgb.independent_64b_blks = true;
		output->grph.rgb.dcc_controls.dcc_256_64_64 = 1;
		अवरोध;
	हाल dcc_control__256_128_128:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 128;
		output->grph.rgb.independent_64b_blks = false;
		output->grph.rgb.dcc_controls.dcc_256_128_128 = 1;
		अवरोध;
	पूर्ण
	output->capable = true;
	output->स्थिर_color_support = true;

	वापस true;
पूर्ण

व्योम hubbub3_क्रमce_wm_propagate_to_pipes(काष्ठा hubbub *hubbub)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uपूर्णांक32_t refclk_mhz = hubbub->ctx->dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000;
	uपूर्णांक32_t prog_wm_value = convert_and_clamp(hubbub1->watermarks.a.urgent_ns,
			refclk_mhz, 0x1fffff);

	REG_SET_2(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, 0,
			DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, prog_wm_value,
			DCHUBBUB_ARB_VM_ROW_URGENCY_WATERMARK_A, prog_wm_value);
पूर्ण

व्योम hubbub3_क्रमce_pstate_change_control(काष्ठा hubbub *hubbub,
		bool क्रमce, bool allow)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_VALUE, allow,
			DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_ENABLE, क्रमce);
पूर्ण

/* Copy values from WM set A to all other sets */
व्योम hubbub3_init_watermarks(काष्ठा hubbub *hubbub)
अणु
	काष्ठा dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	uपूर्णांक32_t reg;

	reg = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A);
	REG_WRITE(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, reg);
	REG_WRITE(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, reg);
	REG_WRITE(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, reg);

	reg = REG_READ(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_A);
	REG_WRITE(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_B, reg);
	REG_WRITE(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_C, reg);
	REG_WRITE(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_D, reg);

	reg = REG_READ(DCHUBBUB_ARB_FRAC_URG_BW_NOM_A);
	REG_WRITE(DCHUBBUB_ARB_FRAC_URG_BW_NOM_B, reg);
	REG_WRITE(DCHUBBUB_ARB_FRAC_URG_BW_NOM_C, reg);
	REG_WRITE(DCHUBBUB_ARB_FRAC_URG_BW_NOM_D, reg);

	reg = REG_READ(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_A);
	REG_WRITE(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_B, reg);
	REG_WRITE(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_C, reg);
	REG_WRITE(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_D, reg);

	reg = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B, reg);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C, reg);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D, reg);

	reg = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B, reg);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C, reg);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D, reg);

	reg = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, reg);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, reg);
	REG_WRITE(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, reg);
पूर्ण

अटल स्थिर काष्ठा hubbub_funcs hubbub30_funcs = अणु
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub3_init_dchub_sys_ctx,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_support_swizzle = hubbub3_dcc_support_swizzle,
	.dcc_support_pixel_क्रमmat = hubbub2_dcc_support_pixel_क्रमmat,
	.get_dcc_compression_cap = hubbub3_get_dcc_compression_cap,
	.wm_पढ़ो_state = hubbub21_wm_पढ़ो_state,
	.get_dchub_ref_freq = hubbub2_get_dchub_ref_freq,
	.program_watermarks = hubbub3_program_watermarks,
	.allow_self_refresh_control = hubbub1_allow_self_refresh_control,
	.is_allow_self_refresh_enabled = hubbub1_is_allow_self_refresh_enabled,
	.क्रमce_wm_propagate_to_pipes = hubbub3_क्रमce_wm_propagate_to_pipes,
	.क्रमce_pstate_change_control = hubbub3_क्रमce_pstate_change_control,
	.init_watermarks = hubbub3_init_watermarks,
पूर्ण;

व्योम hubbub3_स्थिरruct(काष्ठा dcn20_hubbub *hubbub3,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_hubbub_रेजिस्टरs *hubbub_regs,
	स्थिर काष्ठा dcn_hubbub_shअगरt *hubbub_shअगरt,
	स्थिर काष्ठा dcn_hubbub_mask *hubbub_mask)
अणु
	hubbub3->base.ctx = ctx;
	hubbub3->base.funcs = &hubbub30_funcs;
	hubbub3->regs = hubbub_regs;
	hubbub3->shअगरts = hubbub_shअगरt;
	hubbub3->masks = hubbub_mask;

	hubbub3->debug_test_index_pstate = 0xB;
	hubbub3->detile_buf_size = 184 * 1024; /* 184KB क्रम DCN3 */
पूर्ण

