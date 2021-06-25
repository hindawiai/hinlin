<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#समावेश <linux/slab.h>

#समावेश "dal_asic_id.h"
#समावेश "dc_types.h"
#समावेश "dccg.h"
#समावेश "clk_mgr_internal.h"

#समावेश "dce100/dce_clk_mgr.h"
#समावेश "dce110/dce110_clk_mgr.h"
#समावेश "dce112/dce112_clk_mgr.h"
#समावेश "dce120/dce120_clk_mgr.h"
#समावेश "dce60/dce60_clk_mgr.h"
#समावेश "dcn10/rv1_clk_mgr.h"
#समावेश "dcn10/rv2_clk_mgr.h"
#समावेश "dcn20/dcn20_clk_mgr.h"
#समावेश "dcn21/rn_clk_mgr.h"
#समावेश "dcn30/dcn30_clk_mgr.h"
#समावेश "dcn301/vg_clk_mgr.h"


पूर्णांक clk_mgr_helper_get_active_display_cnt(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i, display_count;

	display_count = 0;
	क्रम (i = 0; i < context->stream_count; i++) अणु
		स्थिर काष्ठा dc_stream_state *stream = context->streams[i];

		/*
		 * Only notअगरy active stream or भव stream.
		 * Need to notअगरy भव stream to work around
		 * headless हाल. HPD करोes not fire when प्रणाली is in
		 * S0i2.
		 */
		अगर (!stream->dpms_off || stream->संकेत == SIGNAL_TYPE_VIRTUAL)
			display_count++;
	पूर्ण

	वापस display_count;
पूर्ण

पूर्णांक clk_mgr_helper_get_active_plane_cnt(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i, total_plane_count;

	total_plane_count = 0;
	क्रम (i = 0; i < context->stream_count; i++) अणु
		स्थिर काष्ठा dc_stream_status stream_status = context->stream_status[i];

		/*
		 * Sum up plane_count क्रम all streams ( active and भव ).
		 */
		total_plane_count += stream_status.plane_count;
	पूर्ण

	वापस total_plane_count;
पूर्ण

व्योम clk_mgr_निकास_optimized_pwr_state(स्थिर काष्ठा dc *dc, काष्ठा clk_mgr *clk_mgr)
अणु
	काष्ठा dc_link *edp_links[MAX_NUM_EDP];
	काष्ठा dc_link *edp_link = शून्य;
	पूर्णांक edp_num;

	get_edp_links(dc, edp_links, &edp_num);
	अगर (dc->hwss.निकास_optimized_pwr_state)
		dc->hwss.निकास_optimized_pwr_state(dc, dc->current_state);

	अगर (edp_num) अणु
		edp_link = edp_links[0];
		clk_mgr->psr_allow_active_cache = edp_link->psr_settings.psr_allow_active;
		dc_link_set_psr_allow_active(edp_link, false, false, false);
	पूर्ण

पूर्ण

व्योम clk_mgr_optimize_pwr_state(स्थिर काष्ठा dc *dc, काष्ठा clk_mgr *clk_mgr)
अणु
	काष्ठा dc_link *edp_links[MAX_NUM_EDP];
	काष्ठा dc_link *edp_link = शून्य;
	पूर्णांक edp_num;

	get_edp_links(dc, edp_links, &edp_num);
	अगर (edp_num) अणु
		edp_link = edp_links[0];
		dc_link_set_psr_allow_active(edp_link,
				clk_mgr->psr_allow_active_cache, false, false);
	पूर्ण

	अगर (dc->hwss.optimize_pwr_state)
		dc->hwss.optimize_pwr_state(dc, dc->current_state);

पूर्ण

काष्ठा clk_mgr *dc_clk_mgr_create(काष्ठा dc_context *ctx, काष्ठा pp_smu_funcs *pp_smu, काष्ठा dccg *dccg)
अणु
	काष्ठा hw_asic_id asic_id = ctx->asic_id;

	चयन (asic_id.chip_family) अणु
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल FAMILY_SI: अणु
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

		अगर (clk_mgr == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस शून्य;
		पूर्ण
		dce60_clk_mgr_स्थिरruct(ctx, clk_mgr);
		dce_clk_mgr_स्थिरruct(ctx, clk_mgr);
		वापस &clk_mgr->base;
	पूर्ण
#पूर्ण_अगर
	हाल FAMILY_CI:
	हाल FAMILY_KV: अणु
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

		अगर (clk_mgr == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस शून्य;
		पूर्ण
		dce_clk_mgr_स्थिरruct(ctx, clk_mgr);
		वापस &clk_mgr->base;
	पूर्ण
	हाल FAMILY_CZ: अणु
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

		अगर (clk_mgr == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस शून्य;
		पूर्ण
		dce110_clk_mgr_स्थिरruct(ctx, clk_mgr);
		वापस &clk_mgr->base;
	पूर्ण
	हाल FAMILY_VI: अणु
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

		अगर (clk_mgr == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस शून्य;
		पूर्ण
		अगर (ASIC_REV_IS_TONGA_P(asic_id.hw_पूर्णांकernal_rev) ||
				ASIC_REV_IS_FIJI_P(asic_id.hw_पूर्णांकernal_rev)) अणु
			dce_clk_mgr_स्थिरruct(ctx, clk_mgr);
			वापस &clk_mgr->base;
		पूर्ण
		अगर (ASIC_REV_IS_POLARIS10_P(asic_id.hw_पूर्णांकernal_rev) ||
				ASIC_REV_IS_POLARIS11_M(asic_id.hw_पूर्णांकernal_rev) ||
				ASIC_REV_IS_POLARIS12_V(asic_id.hw_पूर्णांकernal_rev)) अणु
			dce112_clk_mgr_स्थिरruct(ctx, clk_mgr);
			वापस &clk_mgr->base;
		पूर्ण
		अगर (ASIC_REV_IS_VEGAM(asic_id.hw_पूर्णांकernal_rev)) अणु
			dce112_clk_mgr_स्थिरruct(ctx, clk_mgr);
			वापस &clk_mgr->base;
		पूर्ण
		वापस &clk_mgr->base;
	पूर्ण
	हाल FAMILY_AI: अणु
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

		अगर (clk_mgr == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस शून्य;
		पूर्ण
		अगर (ASICREV_IS_VEGA20_P(asic_id.hw_पूर्णांकernal_rev))
			dce121_clk_mgr_स्थिरruct(ctx, clk_mgr);
		अन्यथा
			dce120_clk_mgr_स्थिरruct(ctx, clk_mgr);
		वापस &clk_mgr->base;
	पूर्ण
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल FAMILY_RV: अणु
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

		अगर (clk_mgr == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस शून्य;
		पूर्ण

		अगर (ASICREV_IS_RENOIR(asic_id.hw_पूर्णांकernal_rev)) अणु
			rn_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu, dccg);
			वापस &clk_mgr->base;
		पूर्ण

		अगर (ASICREV_IS_GREEN_SARDINE(asic_id.hw_पूर्णांकernal_rev)) अणु
			rn_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu, dccg);
			वापस &clk_mgr->base;
		पूर्ण
		अगर (ASICREV_IS_RAVEN2(asic_id.hw_पूर्णांकernal_rev)) अणु
			rv2_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu);
			वापस &clk_mgr->base;
		पूर्ण
		अगर (ASICREV_IS_RAVEN(asic_id.hw_पूर्णांकernal_rev) ||
				ASICREV_IS_PICASSO(asic_id.hw_पूर्णांकernal_rev)) अणु
			rv1_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu);
			वापस &clk_mgr->base;
		पूर्ण
		वापस &clk_mgr->base;
	पूर्ण
	हाल FAMILY_NV: अणु
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

		अगर (clk_mgr == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस शून्य;
		पूर्ण
		अगर (ASICREV_IS_SIENNA_CICHLID_P(asic_id.hw_पूर्णांकernal_rev)) अणु
			dcn3_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu, dccg);
			वापस &clk_mgr->base;
		पूर्ण
		अगर (ASICREV_IS_DIMGREY_CAVEFISH_P(asic_id.hw_पूर्णांकernal_rev)) अणु
			dcn3_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu, dccg);
			वापस &clk_mgr->base;
		पूर्ण
		dcn20_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu, dccg);
		वापस &clk_mgr->base;
	पूर्ण
	हाल FAMILY_VGH:
		अगर (ASICREV_IS_VANGOGH(asic_id.hw_पूर्णांकernal_rev)) अणु
			काष्ठा clk_mgr_vgh *clk_mgr = kzalloc(माप(*clk_mgr), GFP_KERNEL);

			अगर (clk_mgr == शून्य) अणु
				BREAK_TO_DEBUGGER();
				वापस शून्य;
			पूर्ण
			vg_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu, dccg);
			वापस &clk_mgr->base.base;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		ASSERT(0); /* Unknown Asic */
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम dc_destroy_clk_mgr(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	चयन (clk_mgr_base->ctx->asic_id.chip_family) अणु
	हाल FAMILY_NV:
		अगर (ASICREV_IS_SIENNA_CICHLID_P(clk_mgr_base->ctx->asic_id.hw_पूर्णांकernal_rev)) अणु
			dcn3_clk_mgr_destroy(clk_mgr);
		पूर्ण
		अगर (ASICREV_IS_DIMGREY_CAVEFISH_P(clk_mgr_base->ctx->asic_id.hw_पूर्णांकernal_rev)) अणु
			dcn3_clk_mgr_destroy(clk_mgr);
		पूर्ण
		अवरोध;

	हाल FAMILY_VGH:
		अगर (ASICREV_IS_VANGOGH(clk_mgr_base->ctx->asic_id.hw_पूर्णांकernal_rev))
			vg_clk_mgr_destroy(clk_mgr);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	kमुक्त(clk_mgr);
पूर्ण

