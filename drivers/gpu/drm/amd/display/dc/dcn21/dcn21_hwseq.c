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

#समावेश "dm_services.h"
#समावेश "dm_helpers.h"
#समावेश "core_types.h"
#समावेश "resource.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dcn21_hwseq.h"
#समावेश "vmid.h"
#समावेश "reg_helper.h"
#समावेश "hw/clk_mgr.h"
#समावेश "dc_dmub_srv.h"
#समावेश "abm.h"


#घोषणा DC_LOGGER_INIT(logger)

#घोषणा CTX \
	hws->ctx
#घोषणा REG(reg)\
	hws->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name

/* Temporary पढ़ो settings, future will get values from kmd directly */
अटल व्योम mmhub_update_page_table_config(काष्ठा dcn_hubbub_phys_addr_config *config,
		काष्ठा dce_hwseq *hws)
अणु
	uपूर्णांक32_t page_table_base_hi;
	uपूर्णांक32_t page_table_base_lo;

	REG_GET(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32,
			PAGE_सूचीECTORY_ENTRY_HI32, &page_table_base_hi);
	REG_GET(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32,
			PAGE_सूचीECTORY_ENTRY_LO32, &page_table_base_lo);

	config->gart_config.page_table_base_addr = ((uपूर्णांक64_t)page_table_base_hi << 32) | page_table_base_lo;

पूर्ण

पूर्णांक dcn21_init_sys_ctx(काष्ठा dce_hwseq *hws, काष्ठा dc *dc, काष्ठा dc_phy_addr_space_config *pa_config)
अणु
	काष्ठा dcn_hubbub_phys_addr_config config;

	config.प्रणाली_aperture.fb_top = pa_config->प्रणाली_aperture.fb_top;
	config.प्रणाली_aperture.fb_offset = pa_config->प्रणाली_aperture.fb_offset;
	config.प्रणाली_aperture.fb_base = pa_config->प्रणाली_aperture.fb_base;
	config.प्रणाली_aperture.agp_top = pa_config->प्रणाली_aperture.agp_top;
	config.प्रणाली_aperture.agp_bot = pa_config->प्रणाली_aperture.agp_bot;
	config.प्रणाली_aperture.agp_base = pa_config->प्रणाली_aperture.agp_base;
	config.gart_config.page_table_start_addr = pa_config->gart_config.page_table_start_addr;
	config.gart_config.page_table_end_addr = pa_config->gart_config.page_table_end_addr;
	config.gart_config.page_table_base_addr = pa_config->gart_config.page_table_base_addr;

	mmhub_update_page_table_config(&config, hws);

	वापस dc->res_pool->hubbub->funcs->init_dchub_sys_ctx(dc->res_pool->hubbub, &config);
पूर्ण

// work around क्रम Renoir s0i3, अगर रेजिस्टर is programmed, bypass golden init.

bool dcn21_s0i3_golden_init_wa(काष्ठा dc *dc)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	uपूर्णांक32_t value = 0;

	value = REG_READ(MICROSECOND_TIME_BASE_DIV);

	वापस value != 0x00120464;
पूर्ण

व्योम dcn21_निकास_optimized_pwr_state(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	dc->clk_mgr->funcs->update_घड़ीs(
			dc->clk_mgr,
			context,
			false);
पूर्ण

व्योम dcn21_optimize_pwr_state(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	dc->clk_mgr->funcs->update_घड़ीs(
			dc->clk_mgr,
			context,
			true);
पूर्ण

/* If user hotplug a HDMI monitor जबतक in monitor off,
 * OS will करो a mode set (with output timing) but keep output off.
 * In this हाल DAL will ask vbios to घातer up the pll in the PHY.
 * If user unplug the monitor (जबतक we are on monitor off) or
 * प्रणाली attempt to enter modern standby (which we will disable PLL),
 * PHY will hang on the next mode set attempt.
 * अगर enable PLL follow by disable PLL (without executing lane enable/disable),
 * RDPCS_PHY_DP_MPLLB_STATE reमुख्यs 1,
 * which indicate that PLL disable attempt actually didn't go through.
 * As a workaround, insert PHY lane enable/disable beक्रमe PLL disable.
 */
व्योम dcn21_PLAT_58856_wa(काष्ठा dc_state *context, काष्ठा pipe_ctx *pipe_ctx)
अणु
	अगर (!pipe_ctx->stream->dpms_off)
		वापस;

	pipe_ctx->stream->dpms_off = false;
	core_link_enable_stream(context, pipe_ctx);
	core_link_disable_stream(pipe_ctx);
	pipe_ctx->stream->dpms_off = true;
पूर्ण

अटल bool dmub_abm_set_pipe(काष्ठा abm *abm, uपूर्णांक32_t otg_inst, uपूर्णांक32_t option, uपूर्णांक32_t panel_inst)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = abm->ctx;
	uपूर्णांक32_t ramping_boundary = 0xFFFF;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.abm_set_pipe.header.type = DMUB_CMD__ABM;
	cmd.abm_set_pipe.header.sub_type = DMUB_CMD__ABM_SET_PIPE;
	cmd.abm_set_pipe.abm_set_pipe_data.otg_inst = otg_inst;
	cmd.abm_set_pipe.abm_set_pipe_data.set_pipe_option = option;
	cmd.abm_set_pipe.abm_set_pipe_data.panel_inst = panel_inst;
	cmd.abm_set_pipe.abm_set_pipe_data.ramping_boundary = ramping_boundary;
	cmd.abm_set_pipe.header.payload_bytes = माप(काष्ठा dmub_cmd_abm_set_pipe_data);

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);

	वापस true;
पूर्ण

व्योम dcn21_set_abm_immediate_disable(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा abm *abm = pipe_ctx->stream_res.abm;
	uपूर्णांक32_t otg_inst = pipe_ctx->stream_res.tg->inst;
	काष्ठा panel_cntl *panel_cntl = pipe_ctx->stream->link->panel_cntl;

	काष्ठा dmcu *dmcu = pipe_ctx->stream->ctx->dc->res_pool->dmcu;

	अगर (dmcu) अणु
		dce110_set_abm_immediate_disable(pipe_ctx);
		वापस;
	पूर्ण

	अगर (abm && panel_cntl) अणु
		dmub_abm_set_pipe(abm, otg_inst, SET_ABM_PIPE_IMMEDIATELY_DISABLE,
				panel_cntl->inst);
		panel_cntl->funcs->store_backlight_level(panel_cntl);
	पूर्ण
पूर्ण

व्योम dcn21_set_pipe(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा abm *abm = pipe_ctx->stream_res.abm;
	uपूर्णांक32_t otg_inst = pipe_ctx->stream_res.tg->inst;
	काष्ठा panel_cntl *panel_cntl = pipe_ctx->stream->link->panel_cntl;
	काष्ठा dmcu *dmcu = pipe_ctx->stream->ctx->dc->res_pool->dmcu;

	अगर (dmcu) अणु
		dce110_set_pipe(pipe_ctx);
		वापस;
	पूर्ण

	अगर (abm && panel_cntl)
		dmub_abm_set_pipe(abm, otg_inst, SET_ABM_PIPE_NORMAL, panel_cntl->inst);
पूर्ण

bool dcn21_set_backlight_level(काष्ठा pipe_ctx *pipe_ctx,
		uपूर्णांक32_t backlight_pwm_u16_16,
		uपूर्णांक32_t frame_ramp)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = pipe_ctx->stream->ctx;
	काष्ठा abm *abm = pipe_ctx->stream_res.abm;
	uपूर्णांक32_t otg_inst = pipe_ctx->stream_res.tg->inst;
	काष्ठा panel_cntl *panel_cntl = pipe_ctx->stream->link->panel_cntl;

	अगर (dc->dc->res_pool->dmcu) अणु
		dce110_set_backlight_level(pipe_ctx, backlight_pwm_u16_16, frame_ramp);
		वापस true;
	पूर्ण

	अगर (abm && panel_cntl)
		dmub_abm_set_pipe(abm, otg_inst, SET_ABM_PIPE_NORMAL, panel_cntl->inst);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.abm_set_backlight.header.type = DMUB_CMD__ABM;
	cmd.abm_set_backlight.header.sub_type = DMUB_CMD__ABM_SET_BACKLIGHT;
	cmd.abm_set_backlight.abm_set_backlight_data.frame_ramp = frame_ramp;
	cmd.abm_set_backlight.abm_set_backlight_data.backlight_user_level = backlight_pwm_u16_16;
	cmd.abm_set_backlight.abm_set_backlight_data.version = DMUB_CMD_ABM_SET_BACKLIGHT_VERSION_1;
	cmd.abm_set_backlight.abm_set_backlight_data.panel_mask = (0x01 << panel_cntl->inst);
	cmd.abm_set_backlight.header.payload_bytes = माप(काष्ठा dmub_cmd_abm_set_backlight_data);

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);

	वापस true;
पूर्ण

bool dcn21_is_abm_supported(काष्ठा dc *dc,
		काष्ठा dc_state *context, काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream == stream &&
				(pipe_ctx->prev_odm_pipe == शून्य && pipe_ctx->next_odm_pipe == शून्य))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

