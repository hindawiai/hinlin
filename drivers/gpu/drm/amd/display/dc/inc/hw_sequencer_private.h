<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_HW_SEQUENCER_PRIVATE_H__
#घोषणा __DC_HW_SEQUENCER_PRIVATE_H__

#समावेश "dc_types.h"

क्रमागत pipe_gating_control अणु
	PIPE_GATING_CONTROL_DISABLE = 0,
	PIPE_GATING_CONTROL_ENABLE,
	PIPE_GATING_CONTROL_INIT
पूर्ण;

काष्ठा dce_hwseq_wa अणु
	bool blnd_crtc_trigger;
	bool DEGVIDCN10_253;
	bool false_optc_underflow;
	bool DEGVIDCN10_254;
	bool DEGVIDCN21;
	bool disallow_self_refresh_during_multi_plane_transition;
पूर्ण;

काष्ठा hwseq_wa_state अणु
	bool DEGVIDCN10_253_applied;
	bool disallow_self_refresh_during_multi_plane_transition_applied;
	अचिन्हित पूर्णांक disallow_self_refresh_during_multi_plane_transition_applied_on_frame;
पूर्ण;

काष्ठा pipe_ctx;
काष्ठा dc_state;
काष्ठा dc_stream_status;
काष्ठा dc_ग_लिखोback_info;
काष्ठा dchub_init_data;
काष्ठा dc_अटल_screen_params;
काष्ठा resource_pool;
काष्ठा resource_context;
काष्ठा stream_resource;
काष्ठा dc_phy_addr_space_config;
काष्ठा dc_भव_addr_space_config;
काष्ठा hubp;
काष्ठा dpp;
काष्ठा dce_hwseq;
काष्ठा timing_generator;
काष्ठा tg_color;
काष्ठा output_pixel_processor;

काष्ठा hwseq_निजी_funcs अणु

	व्योम (*disable_stream_gating)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*enable_stream_gating)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*init_pipes)(काष्ठा dc *dc, काष्ठा dc_state *context);
	व्योम (*reset_hw_ctx_wrap)(काष्ठा dc *dc, काष्ठा dc_state *context);
	व्योम (*update_plane_addr)(स्थिर काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*plane_atomic_disconnect)(काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*update_mpcc)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
	bool (*set_input_transfer_func)(काष्ठा dc *dc,
				काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_plane_state *plane_state);
	bool (*set_output_transfer_func)(काष्ठा dc *dc,
				काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_stream_state *stream);
	व्योम (*घातer_करोwn)(काष्ठा dc *dc);
	व्योम (*enable_display_pipe_घड़ी_gating)(काष्ठा dc_context *ctx,
					bool घड़ी_gating);
	bool (*enable_display_घातer_gating)(काष्ठा dc *dc,
					uपूर्णांक8_t controller_id,
					काष्ठा dc_bios *dcb,
					क्रमागत pipe_gating_control घातer_gating);
	व्योम (*blank_pixel_data)(काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx,
			bool blank);
	क्रमागत dc_status (*enable_stream_timing)(
			काष्ठा pipe_ctx *pipe_ctx,
			काष्ठा dc_state *context,
			काष्ठा dc *dc);
	व्योम (*edp_backlight_control)(काष्ठा dc_link *link,
			bool enable);
	व्योम (*setup_vupdate_पूर्णांकerrupt)(काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx);
	bool (*did_underflow_occur)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*init_blank)(काष्ठा dc *dc, काष्ठा timing_generator *tg);
	व्योम (*disable_vga)(काष्ठा dce_hwseq *hws);
	व्योम (*bios_golden_init)(काष्ठा dc *dc);
	व्योम (*plane_atomic_घातer_करोwn)(काष्ठा dc *dc,
			काष्ठा dpp *dpp,
			काष्ठा hubp *hubp);
	व्योम (*plane_atomic_disable)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*enable_घातer_gating_plane)(काष्ठा dce_hwseq *hws,
		bool enable);
	व्योम (*dpp_pg_control)(काष्ठा dce_hwseq *hws,
			अचिन्हित पूर्णांक dpp_inst,
			bool घातer_on);
	व्योम (*hubp_pg_control)(काष्ठा dce_hwseq *hws,
			अचिन्हित पूर्णांक hubp_inst,
			bool घातer_on);
	व्योम (*dsc_pg_control)(काष्ठा dce_hwseq *hws,
			अचिन्हित पूर्णांक dsc_inst,
			bool घातer_on);
	व्योम (*update_odm)(काष्ठा dc *dc, काष्ठा dc_state *context,
			काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*program_all_ग_लिखोback_pipes_in_tree)(काष्ठा dc *dc,
			स्थिर काष्ठा dc_stream_state *stream,
			काष्ठा dc_state *context);
	bool (*s0i3_golden_init_wa)(काष्ठा dc *dc);
	व्योम (*get_surface_visual_confirm_color)(
			स्थिर काष्ठा pipe_ctx *pipe_ctx,
			काष्ठा tg_color *color);
	व्योम (*get_hdr_visual_confirm_color)(काष्ठा pipe_ctx *pipe_ctx,
			काष्ठा tg_color *color);
	व्योम (*set_hdr_multiplier)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*verअगरy_allow_pstate_change_high)(काष्ठा dc *dc);
	व्योम (*program_pipe)(काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx,
			काष्ठा dc_state *context);
	bool (*रुको_क्रम_blank_complete)(काष्ठा output_pixel_processor *opp);
	व्योम (*dccg_init)(काष्ठा dce_hwseq *hws);
	bool (*set_blend_lut)(काष्ठा pipe_ctx *pipe_ctx,
			स्थिर काष्ठा dc_plane_state *plane_state);
	bool (*set_shaper_3dlut)(काष्ठा pipe_ctx *pipe_ctx,
			स्थिर काष्ठा dc_plane_state *plane_state);
	व्योम (*PLAT_58856_wa)(काष्ठा dc_state *context,
			काष्ठा pipe_ctx *pipe_ctx);
पूर्ण;

काष्ठा dce_hwseq अणु
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा dce_hwseq_रेजिस्टरs *regs;
	स्थिर काष्ठा dce_hwseq_shअगरt *shअगरts;
	स्थिर काष्ठा dce_hwseq_mask *masks;
	काष्ठा dce_hwseq_wa wa;
	काष्ठा hwseq_wa_state wa_state;
	काष्ठा hwseq_निजी_funcs funcs;

पूर्ण;

#पूर्ण_अगर /* __DC_HW_SEQUENCER_PRIVATE_H__ */
