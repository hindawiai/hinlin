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
#समावेश <linux/delay.h>

#समावेश "dm_services.h"
#समावेश "basics/dc_common.h"
#समावेश "dm_helpers.h"
#समावेश "core_types.h"
#समावेश "resource.h"
#समावेश "dcn20_resource.h"
#समावेश "dcn20_hwseq.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "dcn20_dsc.h"
#समावेश "dcn20_optc.h"
#समावेश "abm.h"
#समावेश "clk_mgr.h"
#समावेश "dmcu.h"
#समावेश "hubp.h"
#समावेश "timing_generator.h"
#समावेश "opp.h"
#समावेश "ipp.h"
#समावेश "mpc.h"
#समावेश "mcif_wb.h"
#समावेश "dchubbub.h"
#समावेश "reg_helper.h"
#समावेश "dcn10/dcn10_cm_common.h"
#समावेश "dc_link_dp.h"
#समावेश "vm_helper.h"
#समावेश "dccg.h"
#समावेश "dc_dmub_srv.h"
#समावेश "dce/dmub_hw_lock_mgr.h"

#घोषणा DC_LOGGER_INIT(logger)

#घोषणा CTX \
	hws->ctx
#घोषणा REG(reg)\
	hws->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name

अटल पूर्णांक find_मुक्त_gsl_group(स्थिर काष्ठा dc *dc)
अणु
	अगर (dc->res_pool->gsl_groups.gsl_0 == 0)
		वापस 1;
	अगर (dc->res_pool->gsl_groups.gsl_1 == 0)
		वापस 2;
	अगर (dc->res_pool->gsl_groups.gsl_2 == 0)
		वापस 3;

	वापस 0;
पूर्ण

/* NOTE: This is not a generic setup_gsl function (hence the suffix as_lock)
 * This is only used to lock pipes in pipe splitting हाल with immediate flip
 * Ordinary MPC/OTG locks suppress VUPDATE which करोesn't help with immediate,
 * so we get tearing with मुक्तsync since we cannot flip multiple pipes
 * atomically.
 * We use GSL क्रम this:
 * - immediate flip: find first available GSL group अगर not alपढ़ोy asचिन्हित
 *                   program gsl with that group, set current OTG as master
 *                   and always us 0x4 = AND of flip_पढ़ोy from all pipes
 * - vsync flip: disable GSL अगर used
 *
 * Groups in stream_res are stored as +1 from HW रेजिस्टरs, i.e.
 * gsl_0 <=> pipe_ctx->stream_res.gsl_group == 1
 * Using a magic value like -1 would require tracking all inits/resets
 */
अटल व्योम dcn20_setup_gsl_group_as_lock(
		स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		bool enable)
अणु
	काष्ठा gsl_params gsl;
	पूर्णांक group_idx;

	स_रखो(&gsl, 0, माप(काष्ठा gsl_params));

	अगर (enable) अणु
		/* वापस अगर group alपढ़ोy asचिन्हित since GSL was set up
		 * क्रम vsync flip, we would unassign so it can't be "left over"
		 */
		अगर (pipe_ctx->stream_res.gsl_group > 0)
			वापस;

		group_idx = find_मुक्त_gsl_group(dc);
		ASSERT(group_idx != 0);
		pipe_ctx->stream_res.gsl_group = group_idx;

		/* set gsl group reg field and mark resource used */
		चयन (group_idx) अणु
		हाल 1:
			gsl.gsl0_en = 1;
			dc->res_pool->gsl_groups.gsl_0 = 1;
			अवरोध;
		हाल 2:
			gsl.gsl1_en = 1;
			dc->res_pool->gsl_groups.gsl_1 = 1;
			अवरोध;
		हाल 3:
			gsl.gsl2_en = 1;
			dc->res_pool->gsl_groups.gsl_2 = 1;
			अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			वापस; // invalid हाल
		पूर्ण
		gsl.gsl_master_en = 1;
	पूर्ण अन्यथा अणु
		group_idx = pipe_ctx->stream_res.gsl_group;
		अगर (group_idx == 0)
			वापस; // अगर not in use, just वापस

		pipe_ctx->stream_res.gsl_group = 0;

		/* unset gsl group reg field and mark resource मुक्त */
		चयन (group_idx) अणु
		हाल 1:
			gsl.gsl0_en = 0;
			dc->res_pool->gsl_groups.gsl_0 = 0;
			अवरोध;
		हाल 2:
			gsl.gsl1_en = 0;
			dc->res_pool->gsl_groups.gsl_1 = 0;
			अवरोध;
		हाल 3:
			gsl.gsl2_en = 0;
			dc->res_pool->gsl_groups.gsl_2 = 0;
			अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			वापस;
		पूर्ण
		gsl.gsl_master_en = 0;
	पूर्ण

	/* at this poपूर्णांक we want to program whether it's to enable or disable */
	अगर (pipe_ctx->stream_res.tg->funcs->set_gsl != शून्य &&
		pipe_ctx->stream_res.tg->funcs->set_gsl_source_select != शून्य) अणु
		pipe_ctx->stream_res.tg->funcs->set_gsl(
			pipe_ctx->stream_res.tg,
			&gsl);

		pipe_ctx->stream_res.tg->funcs->set_gsl_source_select(
			pipe_ctx->stream_res.tg, group_idx,	enable ? 4 : 0);
	पूर्ण अन्यथा
		BREAK_TO_DEBUGGER();
पूर्ण

व्योम dcn20_set_flip_control_gsl(
		काष्ठा pipe_ctx *pipe_ctx,
		bool flip_immediate)
अणु
	अगर (pipe_ctx && pipe_ctx->plane_res.hubp->funcs->hubp_set_flip_control_surface_gsl)
		pipe_ctx->plane_res.hubp->funcs->hubp_set_flip_control_surface_gsl(
				pipe_ctx->plane_res.hubp, flip_immediate);

पूर्ण

व्योम dcn20_enable_घातer_gating_plane(
	काष्ठा dce_hwseq *hws,
	bool enable)
अणु
	bool क्रमce_on = true; /* disable घातer gating */

	अगर (enable)
		क्रमce_on = false;

	/* DCHUBP0/1/2/3/4/5 */
	REG_UPDATE(DOMAIN0_PG_CONFIG, DOMAIN0_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN2_PG_CONFIG, DOMAIN2_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN4_PG_CONFIG, DOMAIN4_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN6_PG_CONFIG, DOMAIN6_POWER_FORCEON, क्रमce_on);
	अगर (REG(DOMAIN8_PG_CONFIG))
		REG_UPDATE(DOMAIN8_PG_CONFIG, DOMAIN8_POWER_FORCEON, क्रमce_on);
	अगर (REG(DOMAIN10_PG_CONFIG))
		REG_UPDATE(DOMAIN10_PG_CONFIG, DOMAIN8_POWER_FORCEON, क्रमce_on);

	/* DPP0/1/2/3/4/5 */
	REG_UPDATE(DOMAIN1_PG_CONFIG, DOMAIN1_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN3_PG_CONFIG, DOMAIN3_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN5_PG_CONFIG, DOMAIN5_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN7_PG_CONFIG, DOMAIN7_POWER_FORCEON, क्रमce_on);
	अगर (REG(DOMAIN9_PG_CONFIG))
		REG_UPDATE(DOMAIN9_PG_CONFIG, DOMAIN9_POWER_FORCEON, क्रमce_on);
	अगर (REG(DOMAIN11_PG_CONFIG))
		REG_UPDATE(DOMAIN11_PG_CONFIG, DOMAIN9_POWER_FORCEON, क्रमce_on);

	/* DCS0/1/2/3/4/5 */
	REG_UPDATE(DOMAIN16_PG_CONFIG, DOMAIN16_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN17_PG_CONFIG, DOMAIN17_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN18_PG_CONFIG, DOMAIN18_POWER_FORCEON, क्रमce_on);
	अगर (REG(DOMAIN19_PG_CONFIG))
		REG_UPDATE(DOMAIN19_PG_CONFIG, DOMAIN19_POWER_FORCEON, क्रमce_on);
	अगर (REG(DOMAIN20_PG_CONFIG))
		REG_UPDATE(DOMAIN20_PG_CONFIG, DOMAIN20_POWER_FORCEON, क्रमce_on);
	अगर (REG(DOMAIN21_PG_CONFIG))
		REG_UPDATE(DOMAIN21_PG_CONFIG, DOMAIN21_POWER_FORCEON, क्रमce_on);
पूर्ण

व्योम dcn20_dccg_init(काष्ठा dce_hwseq *hws)
अणु
	/*
	 * set MICROSECOND_TIME_BASE_DIV
	 * 100Mhz refclk -> 0x120264
	 * 27Mhz refclk -> 0x12021b
	 * 48Mhz refclk -> 0x120230
	 *
	 */
	REG_WRITE(MICROSECOND_TIME_BASE_DIV, 0x120264);

	/*
	 * set MILLISECOND_TIME_BASE_DIV
	 * 100Mhz refclk -> 0x1186a0
	 * 27Mhz refclk -> 0x106978
	 * 48Mhz refclk -> 0x10bb80
	 *
	 */
	REG_WRITE(MILLISECOND_TIME_BASE_DIV, 0x1186a0);

	/* This value is dependent on the hardware pipeline delay so set once per SOC */
	REG_WRITE(DISPCLK_FREQ_CHANGE_CNTL, 0x801003c);
पूर्ण

व्योम dcn20_disable_vga(
	काष्ठा dce_hwseq *hws)
अणु
	REG_WRITE(D1VGA_CONTROL, 0);
	REG_WRITE(D2VGA_CONTROL, 0);
	REG_WRITE(D3VGA_CONTROL, 0);
	REG_WRITE(D4VGA_CONTROL, 0);
	REG_WRITE(D5VGA_CONTROL, 0);
	REG_WRITE(D6VGA_CONTROL, 0);
पूर्ण

व्योम dcn20_program_triple_buffer(
	स्थिर काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe_ctx,
	bool enable_triple_buffer)
अणु
	अगर (pipe_ctx->plane_res.hubp && pipe_ctx->plane_res.hubp->funcs) अणु
		pipe_ctx->plane_res.hubp->funcs->hubp_enable_tripleBuffer(
			pipe_ctx->plane_res.hubp,
			enable_triple_buffer);
	पूर्ण
पूर्ण

/* Blank pixel data during initialization */
व्योम dcn20_init_blank(
		काष्ठा dc *dc,
		काष्ठा timing_generator *tg)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	क्रमागत dc_color_space color_space;
	काष्ठा tg_color black_color = अणु0पूर्ण;
	काष्ठा output_pixel_processor *opp = शून्य;
	काष्ठा output_pixel_processor *bottom_opp = शून्य;
	uपूर्णांक32_t num_opps, opp_id_src0, opp_id_src1;
	uपूर्णांक32_t otg_active_width, otg_active_height;

	/* program opp dpg blank color */
	color_space = COLOR_SPACE_SRGB;
	color_space_to_black_color(dc, color_space, &black_color);

	/* get the OTG active size */
	tg->funcs->get_otg_active_size(tg,
			&otg_active_width,
			&otg_active_height);

	/* get the OPTC source */
	tg->funcs->get_optc_source(tg, &num_opps, &opp_id_src0, &opp_id_src1);

	अगर (opp_id_src0 >= dc->res_pool->res_cap->num_opp) अणु
		ASSERT(false);
		वापस;
	पूर्ण
	opp = dc->res_pool->opps[opp_id_src0];

	अगर (num_opps == 2) अणु
		otg_active_width = otg_active_width / 2;

		अगर (opp_id_src1 >= dc->res_pool->res_cap->num_opp) अणु
			ASSERT(false);
			वापस;
		पूर्ण
		bottom_opp = dc->res_pool->opps[opp_id_src1];
	पूर्ण

	opp->funcs->opp_set_disp_pattern_generator(
			opp,
			CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR,
			CONTROLLER_DP_COLOR_SPACE_UDEFINED,
			COLOR_DEPTH_UNDEFINED,
			&black_color,
			otg_active_width,
			otg_active_height,
			0);

	अगर (num_opps == 2) अणु
		bottom_opp->funcs->opp_set_disp_pattern_generator(
				bottom_opp,
				CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR,
				CONTROLLER_DP_COLOR_SPACE_UDEFINED,
				COLOR_DEPTH_UNDEFINED,
				&black_color,
				otg_active_width,
				otg_active_height,
				0);
	पूर्ण

	hws->funcs.रुको_क्रम_blank_complete(opp);
पूर्ण

व्योम dcn20_dsc_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक dsc_inst,
		bool घातer_on)
अणु
	uपूर्णांक32_t घातer_gate = घातer_on ? 0 : 1;
	uपूर्णांक32_t pwr_status = घातer_on ? 0 : 2;
	uपूर्णांक32_t org_ip_request_cntl = 0;

	अगर (hws->ctx->dc->debug.disable_dsc_घातer_gate)
		वापस;

	अगर (REG(DOMAIN16_PG_CONFIG) == 0)
		वापस;

	REG_GET(DC_IP_REQUEST_CNTL, IP_REQUEST_EN, &org_ip_request_cntl);
	अगर (org_ip_request_cntl == 0)
		REG_SET(DC_IP_REQUEST_CNTL, 0, IP_REQUEST_EN, 1);

	चयन (dsc_inst) अणु
	हाल 0: /* DSC0 */
		REG_UPDATE(DOMAIN16_PG_CONFIG,
				DOMAIN16_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN16_PG_STATUS,
				DOMAIN16_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 1: /* DSC1 */
		REG_UPDATE(DOMAIN17_PG_CONFIG,
				DOMAIN17_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN17_PG_STATUS,
				DOMAIN17_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 2: /* DSC2 */
		REG_UPDATE(DOMAIN18_PG_CONFIG,
				DOMAIN18_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN18_PG_STATUS,
				DOMAIN18_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 3: /* DSC3 */
		REG_UPDATE(DOMAIN19_PG_CONFIG,
				DOMAIN19_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN19_PG_STATUS,
				DOMAIN19_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 4: /* DSC4 */
		REG_UPDATE(DOMAIN20_PG_CONFIG,
				DOMAIN20_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN20_PG_STATUS,
				DOMAIN20_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 5: /* DSC5 */
		REG_UPDATE(DOMAIN21_PG_CONFIG,
				DOMAIN21_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN21_PG_STATUS,
				DOMAIN21_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	अगर (org_ip_request_cntl == 0)
		REG_SET(DC_IP_REQUEST_CNTL, 0, IP_REQUEST_EN, 0);
पूर्ण

व्योम dcn20_dpp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक dpp_inst,
		bool घातer_on)
अणु
	uपूर्णांक32_t घातer_gate = घातer_on ? 0 : 1;
	uपूर्णांक32_t pwr_status = घातer_on ? 0 : 2;

	अगर (hws->ctx->dc->debug.disable_dpp_घातer_gate)
		वापस;
	अगर (REG(DOMAIN1_PG_CONFIG) == 0)
		वापस;

	चयन (dpp_inst) अणु
	हाल 0: /* DPP0 */
		REG_UPDATE(DOMAIN1_PG_CONFIG,
				DOMAIN1_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN1_PG_STATUS,
				DOMAIN1_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 1: /* DPP1 */
		REG_UPDATE(DOMAIN3_PG_CONFIG,
				DOMAIN3_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN3_PG_STATUS,
				DOMAIN3_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 2: /* DPP2 */
		REG_UPDATE(DOMAIN5_PG_CONFIG,
				DOMAIN5_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN5_PG_STATUS,
				DOMAIN5_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 3: /* DPP3 */
		REG_UPDATE(DOMAIN7_PG_CONFIG,
				DOMAIN7_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN7_PG_STATUS,
				DOMAIN7_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 4: /* DPP4 */
		REG_UPDATE(DOMAIN9_PG_CONFIG,
				DOMAIN9_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN9_PG_STATUS,
				DOMAIN9_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 5: /* DPP5 */
		/*
		 * Do not घातer gate DPP5, should be left at HW शेष, घातer on permanently.
		 * PG on Pipe5 is De-featured, attempting to put it to PG state may result in hard
		 * reset.
		 * REG_UPDATE(DOMAIN11_PG_CONFIG,
		 *		DOMAIN11_POWER_GATE, घातer_gate);
		 *
		 * REG_WAIT(DOMAIN11_PG_STATUS,
		 *		DOMAIN11_PGFSM_PWR_STATUS, pwr_status,
		 * 		1, 1000);
		 */
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण
पूर्ण


व्योम dcn20_hubp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक hubp_inst,
		bool घातer_on)
अणु
	uपूर्णांक32_t घातer_gate = घातer_on ? 0 : 1;
	uपूर्णांक32_t pwr_status = घातer_on ? 0 : 2;

	अगर (hws->ctx->dc->debug.disable_hubp_घातer_gate)
		वापस;
	अगर (REG(DOMAIN0_PG_CONFIG) == 0)
		वापस;

	चयन (hubp_inst) अणु
	हाल 0: /* DCHUBP0 */
		REG_UPDATE(DOMAIN0_PG_CONFIG,
				DOMAIN0_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN0_PG_STATUS,
				DOMAIN0_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 1: /* DCHUBP1 */
		REG_UPDATE(DOMAIN2_PG_CONFIG,
				DOMAIN2_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN2_PG_STATUS,
				DOMAIN2_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 2: /* DCHUBP2 */
		REG_UPDATE(DOMAIN4_PG_CONFIG,
				DOMAIN4_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN4_PG_STATUS,
				DOMAIN4_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 3: /* DCHUBP3 */
		REG_UPDATE(DOMAIN6_PG_CONFIG,
				DOMAIN6_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN6_PG_STATUS,
				DOMAIN6_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 4: /* DCHUBP4 */
		REG_UPDATE(DOMAIN8_PG_CONFIG,
				DOMAIN8_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN8_PG_STATUS,
				DOMAIN8_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 5: /* DCHUBP5 */
		/*
		 * Do not घातer gate DCHUB5, should be left at HW शेष, घातer on permanently.
		 * PG on Pipe5 is De-featured, attempting to put it to PG state may result in hard
		 * reset.
		 * REG_UPDATE(DOMAIN10_PG_CONFIG,
		 *		DOMAIN10_POWER_GATE, घातer_gate);
		 *
		 * REG_WAIT(DOMAIN10_PG_STATUS,
		 *		DOMAIN10_PGFSM_PWR_STATUS, pwr_status,
		 *		1, 1000);
		 */
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण
पूर्ण


/* disable HW used by plane.
 * note:  cannot disable until disconnect is complete
 */
व्योम dcn20_plane_atomic_disable(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा dpp *dpp = pipe_ctx->plane_res.dpp;

	dc->hwss.रुको_क्रम_mpcc_disconnect(dc, dc->res_pool, pipe_ctx);

	/* In flip immediate with pipe splitting हाल GSL is used क्रम
	 * synchronization so we must disable it when the plane is disabled.
	 */
	अगर (pipe_ctx->stream_res.gsl_group != 0)
		dcn20_setup_gsl_group_as_lock(dc, pipe_ctx, false);

	dc->hwss.set_flip_control_gsl(pipe_ctx, false);

	hubp->funcs->hubp_clk_cntl(hubp, false);

	dpp->funcs->dpp_dppclk_control(dpp, false, false);

	hubp->घातer_gated = true;

	hws->funcs.plane_atomic_घातer_करोwn(dc,
			pipe_ctx->plane_res.dpp,
			pipe_ctx->plane_res.hubp);

	pipe_ctx->stream = शून्य;
	स_रखो(&pipe_ctx->stream_res, 0, माप(pipe_ctx->stream_res));
	स_रखो(&pipe_ctx->plane_res, 0, माप(pipe_ctx->plane_res));
	pipe_ctx->top_pipe = शून्य;
	pipe_ctx->bottom_pipe = शून्य;
	pipe_ctx->plane_state = शून्य;
पूर्ण


व्योम dcn20_disable_plane(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (!pipe_ctx->plane_res.hubp || pipe_ctx->plane_res.hubp->घातer_gated)
		वापस;

	dcn20_plane_atomic_disable(dc, pipe_ctx);

	DC_LOG_DC("Power down front end %d\n",
					pipe_ctx->pipe_idx);
पूर्ण

अटल पूर्णांक calc_mpc_flow_ctrl_cnt(स्थिर काष्ठा dc_stream_state *stream,
		पूर्णांक opp_cnt)
अणु
	bool hblank_halved = optc2_is_two_pixels_per_contaपूर्णांकer(&stream->timing);
	पूर्णांक flow_ctrl_cnt;

	अगर (opp_cnt >= 2)
		hblank_halved = true;

	flow_ctrl_cnt = stream->timing.h_total - stream->timing.h_addressable -
			stream->timing.h_border_left -
			stream->timing.h_border_right;

	अगर (hblank_halved)
		flow_ctrl_cnt /= 2;

	/* ODM combine 4:1 हाल */
	अगर (opp_cnt == 4)
		flow_ctrl_cnt /= 2;

	वापस flow_ctrl_cnt;
पूर्ण

क्रमागत dc_status dcn20_enable_stream_timing(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context,
		काष्ठा dc *dc)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा drr_params params = अणु0पूर्ण;
	अचिन्हित पूर्णांक event_triggers = 0;
	काष्ठा pipe_ctx *odm_pipe;
	पूर्णांक opp_cnt = 1;
	पूर्णांक opp_inst[MAX_PIPES] = अणु pipe_ctx->stream_res.opp->inst पूर्ण;
	bool पूर्णांकerlace = stream->timing.flags.INTERLACE;
	पूर्णांक i;
	काष्ठा mpc_dwb_flow_control flow_control;
	काष्ठा mpc *mpc = dc->res_pool->mpc;
	bool rate_control_2x_pclk = (पूर्णांकerlace || optc2_is_two_pixels_per_contaपूर्णांकer(&stream->timing));

	/* by upper caller loop, pipe0 is parent pipe and be called first.
	 * back end is set up by क्रम pipe0. Other children pipe share back end
	 * with pipe 0. No program is needed.
	 */
	अगर (pipe_ctx->top_pipe != शून्य)
		वापस DC_OK;

	/* TODO check अगर timing_changed, disable stream अगर timing changed */

	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) अणु
		opp_inst[opp_cnt] = odm_pipe->stream_res.opp->inst;
		opp_cnt++;
	पूर्ण

	अगर (opp_cnt > 1)
		pipe_ctx->stream_res.tg->funcs->set_odm_combine(
				pipe_ctx->stream_res.tg,
				opp_inst, opp_cnt,
				&pipe_ctx->stream->timing);

	/* HW program guide assume display alपढ़ोy disable
	 * by unplug sequence. OTG assume stop.
	 */
	pipe_ctx->stream_res.tg->funcs->enable_optc_घड़ी(pipe_ctx->stream_res.tg, true);

	अगर (false == pipe_ctx->घड़ी_source->funcs->program_pix_clk(
			pipe_ctx->घड़ी_source,
			&pipe_ctx->stream_res.pix_clk_params,
			&pipe_ctx->pll_settings)) अणु
		BREAK_TO_DEBUGGER();
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	अगर (dc->hwseq->funcs.PLAT_58856_wa && (!dc_is_dp_संकेत(stream->संकेत)))
		dc->hwseq->funcs.PLAT_58856_wa(context, pipe_ctx);

	pipe_ctx->stream_res.tg->funcs->program_timing(
			pipe_ctx->stream_res.tg,
			&stream->timing,
			pipe_ctx->pipe_dlg_param.vपढ़ोy_offset,
			pipe_ctx->pipe_dlg_param.vstartup_start,
			pipe_ctx->pipe_dlg_param.vupdate_offset,
			pipe_ctx->pipe_dlg_param.vupdate_width,
			pipe_ctx->stream->संकेत,
			true);

	rate_control_2x_pclk = rate_control_2x_pclk || opp_cnt > 1;
	flow_control.flow_ctrl_mode = 0;
	flow_control.flow_ctrl_cnt0 = 0x80;
	flow_control.flow_ctrl_cnt1 = calc_mpc_flow_ctrl_cnt(stream, opp_cnt);
	अगर (mpc->funcs->set_out_rate_control) अणु
		क्रम (i = 0; i < opp_cnt; ++i) अणु
			mpc->funcs->set_out_rate_control(
					mpc, opp_inst[i],
					true,
					rate_control_2x_pclk,
					&flow_control);
		पूर्ण
	पूर्ण

	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		odm_pipe->stream_res.opp->funcs->opp_pipe_घड़ी_control(
				odm_pipe->stream_res.opp,
				true);

	pipe_ctx->stream_res.opp->funcs->opp_pipe_घड़ी_control(
			pipe_ctx->stream_res.opp,
			true);

	hws->funcs.blank_pixel_data(dc, pipe_ctx, true);

	/* VTG is  within DCHUB command block. DCFCLK is always on */
	अगर (false == pipe_ctx->stream_res.tg->funcs->enable_crtc(pipe_ctx->stream_res.tg)) अणु
		BREAK_TO_DEBUGGER();
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	hws->funcs.रुको_क्रम_blank_complete(pipe_ctx->stream_res.opp);

	params.vertical_total_min = stream->adjust.v_total_min;
	params.vertical_total_max = stream->adjust.v_total_max;
	params.vertical_total_mid = stream->adjust.v_total_mid;
	params.vertical_total_mid_frame_num = stream->adjust.v_total_mid_frame_num;
	अगर (pipe_ctx->stream_res.tg->funcs->set_drr)
		pipe_ctx->stream_res.tg->funcs->set_drr(
			pipe_ctx->stream_res.tg, &params);

	// DRR should set trigger event to monitor surface update event
	अगर (stream->adjust.v_total_min != 0 && stream->adjust.v_total_max != 0)
		event_triggers = 0x80;
	/* Event triggers and num frames initialized क्रम DRR, but can be
	 * later updated क्रम PSR use. Note DRR trigger events are generated
	 * regardless of whether num frames met.
	 */
	अगर (pipe_ctx->stream_res.tg->funcs->set_अटल_screen_control)
		pipe_ctx->stream_res.tg->funcs->set_अटल_screen_control(
				pipe_ctx->stream_res.tg, event_triggers, 2);

	/* TODO program crtc source select क्रम non-भव संकेत*/
	/* TODO program FMT */
	/* TODO setup link_enc */
	/* TODO set stream attributes */
	/* TODO program audio */
	/* TODO enable stream अगर timing changed */
	/* TODO unblank stream अगर DP */

	वापस DC_OK;
पूर्ण

व्योम dcn20_program_output_csc(काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत dc_color_space colorspace,
		uपूर्णांक16_t *matrix,
		पूर्णांक opp_id)
अणु
	काष्ठा mpc *mpc = dc->res_pool->mpc;
	क्रमागत mpc_output_csc_mode ocsc_mode = MPC_OUTPUT_CSC_COEF_A;
	पूर्णांक mpcc_id = pipe_ctx->plane_res.hubp->inst;

	अगर (mpc->funcs->घातer_on_mpc_mem_pwr)
		mpc->funcs->घातer_on_mpc_mem_pwr(mpc, mpcc_id, true);

	अगर (pipe_ctx->stream->csc_color_matrix.enable_adjusपंचांगent == true) अणु
		अगर (mpc->funcs->set_output_csc != शून्य)
			mpc->funcs->set_output_csc(mpc,
					opp_id,
					matrix,
					ocsc_mode);
	पूर्ण अन्यथा अणु
		अगर (mpc->funcs->set_ocsc_शेष != शून्य)
			mpc->funcs->set_ocsc_शेष(mpc,
					opp_id,
					colorspace,
					ocsc_mode);
	पूर्ण
पूर्ण

bool dcn20_set_output_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक mpcc_id = pipe_ctx->plane_res.hubp->inst;
	काष्ठा mpc *mpc = pipe_ctx->stream_res.opp->ctx->dc->res_pool->mpc;
	काष्ठा pwl_params *params = शून्य;
	/*
	 * program OGAM only क्रम the top pipe
	 * अगर there is a pipe split then fix diagnostic is required:
	 * how to pass OGAM parameter क्रम stream.
	 * अगर programming क्रम all pipes is required then हटाओ condition
	 * pipe_ctx->top_pipe == शून्य ,but then fix the diagnostic.
	 */
	अगर (mpc->funcs->घातer_on_mpc_mem_pwr)
		mpc->funcs->घातer_on_mpc_mem_pwr(mpc, mpcc_id, true);
	अगर (pipe_ctx->top_pipe == शून्य
			&& mpc->funcs->set_output_gamma && stream->out_transfer_func) अणु
		अगर (stream->out_transfer_func->type == TF_TYPE_HWPWL)
			params = &stream->out_transfer_func->pwl;
		अन्यथा अगर (pipe_ctx->stream->out_transfer_func->type ==
			TF_TYPE_DISTRIBUTED_POINTS &&
			cm_helper_translate_curve_to_hw_क्रमmat(
			stream->out_transfer_func,
			&mpc->blender_params, false))
			params = &mpc->blender_params;
		/*
		 * there is no ROM
		 */
		अगर (stream->out_transfer_func->type == TF_TYPE_PREDEFINED)
			BREAK_TO_DEBUGGER();
	पूर्ण
	/*
	 * अगर above अगर is not executed then 'params' equal to 0 and set in bypass
	 */
	mpc->funcs->set_output_gamma(mpc, mpcc_id, params);

	वापस true;
पूर्ण

bool dcn20_set_blend_lut(
	काष्ठा pipe_ctx *pipe_ctx, स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा dpp *dpp_base = pipe_ctx->plane_res.dpp;
	bool result = true;
	काष्ठा pwl_params *blend_lut = शून्य;

	अगर (plane_state->blend_tf) अणु
		अगर (plane_state->blend_tf->type == TF_TYPE_HWPWL)
			blend_lut = &plane_state->blend_tf->pwl;
		अन्यथा अगर (plane_state->blend_tf->type == TF_TYPE_DISTRIBUTED_POINTS) अणु
			cm_helper_translate_curve_to_hw_क्रमmat(
					plane_state->blend_tf,
					&dpp_base->regamma_params, false);
			blend_lut = &dpp_base->regamma_params;
		पूर्ण
	पूर्ण
	result = dpp_base->funcs->dpp_program_blnd_lut(dpp_base, blend_lut);

	वापस result;
पूर्ण

bool dcn20_set_shaper_3dlut(
	काष्ठा pipe_ctx *pipe_ctx, स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा dpp *dpp_base = pipe_ctx->plane_res.dpp;
	bool result = true;
	काष्ठा pwl_params *shaper_lut = शून्य;

	अगर (plane_state->in_shaper_func) अणु
		अगर (plane_state->in_shaper_func->type == TF_TYPE_HWPWL)
			shaper_lut = &plane_state->in_shaper_func->pwl;
		अन्यथा अगर (plane_state->in_shaper_func->type == TF_TYPE_DISTRIBUTED_POINTS) अणु
			cm_helper_translate_curve_to_hw_क्रमmat(
					plane_state->in_shaper_func,
					&dpp_base->shaper_params, true);
			shaper_lut = &dpp_base->shaper_params;
		पूर्ण
	पूर्ण

	result = dpp_base->funcs->dpp_program_shaper_lut(dpp_base, shaper_lut);
	अगर (plane_state->lut3d_func &&
		plane_state->lut3d_func->state.bits.initialized == 1)
		result = dpp_base->funcs->dpp_program_3dlut(dpp_base,
								&plane_state->lut3d_func->lut_3d);
	अन्यथा
		result = dpp_base->funcs->dpp_program_3dlut(dpp_base, शून्य);

	वापस result;
पूर्ण

bool dcn20_set_input_transfer_func(काष्ठा dc *dc,
				काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा dpp *dpp_base = pipe_ctx->plane_res.dpp;
	स्थिर काष्ठा dc_transfer_func *tf = शून्य;
	bool result = true;
	bool use_degamma_ram = false;

	अगर (dpp_base == शून्य || plane_state == शून्य)
		वापस false;

	hws->funcs.set_shaper_3dlut(pipe_ctx, plane_state);
	hws->funcs.set_blend_lut(pipe_ctx, plane_state);

	अगर (plane_state->in_transfer_func)
		tf = plane_state->in_transfer_func;


	अगर (tf == शून्य) अणु
		dpp_base->funcs->dpp_set_degamma(dpp_base,
				IPP_DEGAMMA_MODE_BYPASS);
		वापस true;
	पूर्ण

	अगर (tf->type == TF_TYPE_HWPWL || tf->type == TF_TYPE_DISTRIBUTED_POINTS)
		use_degamma_ram = true;

	अगर (use_degamma_ram == true) अणु
		अगर (tf->type == TF_TYPE_HWPWL)
			dpp_base->funcs->dpp_program_degamma_pwl(dpp_base,
					&tf->pwl);
		अन्यथा अगर (tf->type == TF_TYPE_DISTRIBUTED_POINTS) अणु
			cm_helper_translate_curve_to_degamma_hw_क्रमmat(tf,
					&dpp_base->degamma_params);
			dpp_base->funcs->dpp_program_degamma_pwl(dpp_base,
				&dpp_base->degamma_params);
		पूर्ण
		वापस true;
	पूर्ण
	/* handle here the optimized हालs when de-gamma ROM could be used.
	 *
	 */
	अगर (tf->type == TF_TYPE_PREDEFINED) अणु
		चयन (tf->tf) अणु
		हाल TRANSFER_FUNCTION_SRGB:
			dpp_base->funcs->dpp_set_degamma(dpp_base,
					IPP_DEGAMMA_MODE_HW_sRGB);
			अवरोध;
		हाल TRANSFER_FUNCTION_BT709:
			dpp_base->funcs->dpp_set_degamma(dpp_base,
					IPP_DEGAMMA_MODE_HW_xvYCC);
			अवरोध;
		हाल TRANSFER_FUNCTION_LINEAR:
			dpp_base->funcs->dpp_set_degamma(dpp_base,
					IPP_DEGAMMA_MODE_BYPASS);
			अवरोध;
		हाल TRANSFER_FUNCTION_PQ:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_USER_PWL);
			cm_helper_translate_curve_to_degamma_hw_क्रमmat(tf, &dpp_base->degamma_params);
			dpp_base->funcs->dpp_program_degamma_pwl(dpp_base, &dpp_base->degamma_params);
			result = true;
			अवरोध;
		शेष:
			result = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (tf->type == TF_TYPE_BYPASS)
		dpp_base->funcs->dpp_set_degamma(dpp_base,
				IPP_DEGAMMA_MODE_BYPASS);
	अन्यथा अणु
		/*
		 * अगर we are here, we did not handle correctly.
		 * fix is required क्रम this use हाल
		 */
		BREAK_TO_DEBUGGER();
		dpp_base->funcs->dpp_set_degamma(dpp_base,
				IPP_DEGAMMA_MODE_BYPASS);
	पूर्ण

	वापस result;
पूर्ण

व्योम dcn20_update_odm(काष्ठा dc *dc, काष्ठा dc_state *context, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा pipe_ctx *odm_pipe;
	पूर्णांक opp_cnt = 1;
	पूर्णांक opp_inst[MAX_PIPES] = अणु pipe_ctx->stream_res.opp->inst पूर्ण;

	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) अणु
		opp_inst[opp_cnt] = odm_pipe->stream_res.opp->inst;
		opp_cnt++;
	पूर्ण

	अगर (opp_cnt > 1)
		pipe_ctx->stream_res.tg->funcs->set_odm_combine(
				pipe_ctx->stream_res.tg,
				opp_inst, opp_cnt,
				&pipe_ctx->stream->timing);
	अन्यथा
		pipe_ctx->stream_res.tg->funcs->set_odm_bypass(
				pipe_ctx->stream_res.tg, &pipe_ctx->stream->timing);
पूर्ण

व्योम dcn20_blank_pixel_data(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		bool blank)
अणु
	काष्ठा tg_color black_color = अणु0पूर्ण;
	काष्ठा stream_resource *stream_res = &pipe_ctx->stream_res;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	क्रमागत dc_color_space color_space = stream->output_color_space;
	क्रमागत controller_dp_test_pattern test_pattern = CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR;
	क्रमागत controller_dp_color_space test_pattern_color_space = CONTROLLER_DP_COLOR_SPACE_UDEFINED;
	काष्ठा pipe_ctx *odm_pipe;
	पूर्णांक odm_cnt = 1;

	पूर्णांक width = stream->timing.h_addressable + stream->timing.h_border_left + stream->timing.h_border_right;
	पूर्णांक height = stream->timing.v_addressable + stream->timing.v_border_bottom + stream->timing.v_border_top;

	अगर (stream->link->test_pattern_enabled)
		वापस;

	/* get opp dpg blank color */
	color_space_to_black_color(dc, color_space, &black_color);

	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		odm_cnt++;

	width = width / odm_cnt;

	अगर (blank) अणु
		dc->hwss.set_abm_immediate_disable(pipe_ctx);

		अगर (dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE) अणु
			test_pattern = CONTROLLER_DP_TEST_PATTERN_COLORSQUARES;
			test_pattern_color_space = CONTROLLER_DP_COLOR_SPACE_RGB;
		पूर्ण
	पूर्ण अन्यथा अणु
		test_pattern = CONTROLLER_DP_TEST_PATTERN_VIDEOMODE;
	पूर्ण

	dc->hwss.set_disp_pattern_generator(dc,
			pipe_ctx,
			test_pattern,
			test_pattern_color_space,
			stream->timing.display_color_depth,
			&black_color,
			width,
			height,
			0);

	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) अणु
		dc->hwss.set_disp_pattern_generator(dc,
				odm_pipe,
				dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE && blank ?
						CONTROLLER_DP_TEST_PATTERN_COLORRAMP : test_pattern,
				test_pattern_color_space,
				stream->timing.display_color_depth,
				&black_color,
				width,
				height,
				0);
	पूर्ण

	अगर (!blank)
		अगर (stream_res->abm) अणु
			dc->hwss.set_pipe(pipe_ctx);
			stream_res->abm->funcs->set_abm_level(stream_res->abm, stream->abm_level);
		पूर्ण
पूर्ण


अटल व्योम dcn20_घातer_on_plane(
	काष्ठा dce_hwseq *hws,
	काष्ठा pipe_ctx *pipe_ctx)
अणु
	DC_LOGGER_INIT(hws->ctx->logger);
	अगर (REG(DC_IP_REQUEST_CNTL)) अणु
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 1);

		अगर (hws->funcs.dpp_pg_control)
			hws->funcs.dpp_pg_control(hws, pipe_ctx->plane_res.dpp->inst, true);

		अगर (hws->funcs.hubp_pg_control)
			hws->funcs.hubp_pg_control(hws, pipe_ctx->plane_res.hubp->inst, true);

		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 0);
		DC_LOG_DEBUG(
				"Un-gated front end for pipe %d\n", pipe_ctx->plane_res.hubp->inst);
	पूर्ण
पूर्ण

व्योम dcn20_enable_plane(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा dc_state *context)
अणु
	//अगर (dc->debug.sanity_checks) अणु
	//	dcn10_verअगरy_allow_pstate_change_high(dc);
	//पूर्ण
	dcn20_घातer_on_plane(dc->hwseq, pipe_ctx);

	/* enable DCFCLK current DCHUB */
	pipe_ctx->plane_res.hubp->funcs->hubp_clk_cntl(pipe_ctx->plane_res.hubp, true);

	/* initialize HUBP on घातer up */
	pipe_ctx->plane_res.hubp->funcs->hubp_init(pipe_ctx->plane_res.hubp);

	/* make sure OPP_PIPE_CLOCK_EN = 1 */
	pipe_ctx->stream_res.opp->funcs->opp_pipe_घड़ी_control(
			pipe_ctx->stream_res.opp,
			true);

/* TODO: enable/disable in dm as per update type.
	अगर (plane_state) अणु
		DC_LOG_DC(dc->ctx->logger,
				"Pipe:%d 0x%x: addr hi:0x%x, "
				"addr low:0x%x, "
				"src: %d, %d, %d,"
				" %d; dst: %d, %d, %d, %d;\n",
				pipe_ctx->pipe_idx,
				plane_state,
				plane_state->address.grph.addr.high_part,
				plane_state->address.grph.addr.low_part,
				plane_state->src_rect.x,
				plane_state->src_rect.y,
				plane_state->src_rect.width,
				plane_state->src_rect.height,
				plane_state->dst_rect.x,
				plane_state->dst_rect.y,
				plane_state->dst_rect.width,
				plane_state->dst_rect.height);

		DC_LOG_DC(dc->ctx->logger,
				"Pipe %d: width, height, x, y         format:%d\n"
				"viewport:%d, %d, %d, %d\n"
				"recout:  %d, %d, %d, %d\n",
				pipe_ctx->pipe_idx,
				plane_state->क्रमmat,
				pipe_ctx->plane_res.scl_data.viewport.width,
				pipe_ctx->plane_res.scl_data.viewport.height,
				pipe_ctx->plane_res.scl_data.viewport.x,
				pipe_ctx->plane_res.scl_data.viewport.y,
				pipe_ctx->plane_res.scl_data.recout.width,
				pipe_ctx->plane_res.scl_data.recout.height,
				pipe_ctx->plane_res.scl_data.recout.x,
				pipe_ctx->plane_res.scl_data.recout.y);
		prपूर्णांक_rq_dlg_ttu(dc, pipe_ctx);
	पूर्ण
*/
	अगर (dc->vm_pa_config.valid) अणु
		काष्ठा vm_प्रणाली_aperture_param apt;

		apt.sys_शेष.quad_part = 0;

		apt.sys_low.quad_part = dc->vm_pa_config.प्रणाली_aperture.start_addr;
		apt.sys_high.quad_part = dc->vm_pa_config.प्रणाली_aperture.end_addr;

		// Program प्रणाली aperture settings
		pipe_ctx->plane_res.hubp->funcs->hubp_set_vm_प्रणाली_aperture_settings(pipe_ctx->plane_res.hubp, &apt);
	पूर्ण

	अगर (!pipe_ctx->top_pipe
		&& pipe_ctx->plane_state
		&& pipe_ctx->plane_state->flip_पूर्णांक_enabled
		&& pipe_ctx->plane_res.hubp->funcs->hubp_set_flip_पूर्णांक)
			pipe_ctx->plane_res.hubp->funcs->hubp_set_flip_पूर्णांक(pipe_ctx->plane_res.hubp);

//	अगर (dc->debug.sanity_checks) अणु
//		dcn10_verअगरy_allow_pstate_change_high(dc);
//	पूर्ण
पूर्ण

व्योम dcn20_pipe_control_lock(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe,
	bool lock)
अणु
	काष्ठा pipe_ctx *temp_pipe;
	bool flip_immediate = false;

	/* use TG master update lock to lock everything on the TG
	 * thereक्रमe only top pipe need to lock
	 */
	अगर (!pipe || pipe->top_pipe)
		वापस;

	अगर (pipe->plane_state != शून्य)
		flip_immediate = pipe->plane_state->flip_immediate;

	अगर  (pipe->stream_res.gsl_group > 0) अणु
	    temp_pipe = pipe->bottom_pipe;
	    जबतक (!flip_immediate && temp_pipe) अणु
		    अगर (temp_pipe->plane_state != शून्य)
			    flip_immediate = temp_pipe->plane_state->flip_immediate;
		    temp_pipe = temp_pipe->bottom_pipe;
	    पूर्ण
	पूर्ण

	अगर (flip_immediate && lock) अणु
		स्थिर पूर्णांक TIMEOUT_FOR_FLIP_PENDING = 100000;
		पूर्णांक i;

		temp_pipe = pipe;
		जबतक (temp_pipe) अणु
			अगर (temp_pipe->plane_state && temp_pipe->plane_state->flip_immediate) अणु
				क्रम (i = 0; i < TIMEOUT_FOR_FLIP_PENDING; ++i) अणु
					अगर (!temp_pipe->plane_res.hubp->funcs->hubp_is_flip_pending(temp_pipe->plane_res.hubp))
						अवरोध;
					udelay(1);
				पूर्ण

				/* no reason it should take this दीर्घ क्रम immediate flips */
				ASSERT(i != TIMEOUT_FOR_FLIP_PENDING);
			पूर्ण
			temp_pipe = temp_pipe->bottom_pipe;
		पूर्ण
	पूर्ण

	/* In flip immediate and pipe splitting हाल, we need to use GSL
	 * क्रम synchronization. Only करो setup on locking and on flip type change.
	 */
	अगर (lock && (pipe->bottom_pipe != शून्य || !flip_immediate))
		अगर ((flip_immediate && pipe->stream_res.gsl_group == 0) ||
		    (!flip_immediate && pipe->stream_res.gsl_group > 0))
			dcn20_setup_gsl_group_as_lock(dc, pipe, flip_immediate);

	अगर (pipe->plane_state != शून्य)
		flip_immediate = pipe->plane_state->flip_immediate;

	temp_pipe = pipe->bottom_pipe;
	जबतक (flip_immediate && temp_pipe) अणु
	    अगर (temp_pipe->plane_state != शून्य)
		flip_immediate = temp_pipe->plane_state->flip_immediate;
	    temp_pipe = temp_pipe->bottom_pipe;
	पूर्ण

	अगर (!lock && pipe->stream_res.gsl_group > 0 && pipe->plane_state &&
		!flip_immediate)
	    dcn20_setup_gsl_group_as_lock(dc, pipe, false);

	अगर (pipe->stream && should_use_dmub_lock(pipe->stream->link)) अणु
		जोड़ dmub_hw_lock_flags hw_locks = अणु 0 पूर्ण;
		काष्ठा dmub_hw_lock_inst_flags inst_flags = अणु 0 पूर्ण;

		hw_locks.bits.lock_pipe = 1;
		inst_flags.otg_inst =  pipe->stream_res.tg->inst;

		अगर (pipe->plane_state != शून्य)
			hw_locks.bits.triple_buffer_lock = pipe->plane_state->triplebuffer_flips;

		dmub_hw_lock_mgr_cmd(dc->ctx->dmub_srv,
					lock,
					&hw_locks,
					&inst_flags);
	पूर्ण अन्यथा अगर (pipe->plane_state != शून्य && pipe->plane_state->triplebuffer_flips) अणु
		अगर (lock)
			pipe->stream_res.tg->funcs->triplebuffer_lock(pipe->stream_res.tg);
		अन्यथा
			pipe->stream_res.tg->funcs->triplebuffer_unlock(pipe->stream_res.tg);
	पूर्ण अन्यथा अणु
		अगर (lock)
			pipe->stream_res.tg->funcs->lock(pipe->stream_res.tg);
		अन्यथा
			pipe->stream_res.tg->funcs->unlock(pipe->stream_res.tg);
	पूर्ण
पूर्ण

अटल व्योम dcn20_detect_pipe_changes(काष्ठा pipe_ctx *old_pipe, काष्ठा pipe_ctx *new_pipe)
अणु
	new_pipe->update_flags.raw = 0;

	/* Exit on unchanged, unused pipe */
	अगर (!old_pipe->plane_state && !new_pipe->plane_state)
		वापस;
	/* Detect pipe enable/disable */
	अगर (!old_pipe->plane_state && new_pipe->plane_state) अणु
		new_pipe->update_flags.bits.enable = 1;
		new_pipe->update_flags.bits.mpcc = 1;
		new_pipe->update_flags.bits.dppclk = 1;
		new_pipe->update_flags.bits.hubp_पूर्णांकerdependent = 1;
		new_pipe->update_flags.bits.hubp_rq_dlg_ttu = 1;
		new_pipe->update_flags.bits.gamut_remap = 1;
		new_pipe->update_flags.bits.scaler = 1;
		new_pipe->update_flags.bits.viewport = 1;
		अगर (!new_pipe->top_pipe && !new_pipe->prev_odm_pipe) अणु
			new_pipe->update_flags.bits.odm = 1;
			new_pipe->update_flags.bits.global_sync = 1;
		पूर्ण
		वापस;
	पूर्ण
	अगर (old_pipe->plane_state && !new_pipe->plane_state) अणु
		new_pipe->update_flags.bits.disable = 1;
		वापस;
	पूर्ण

	/* Detect plane change */
	अगर (old_pipe->plane_state != new_pipe->plane_state) अणु
		new_pipe->update_flags.bits.plane_changed = true;
	पूर्ण

	/* Detect top pipe only changes */
	अगर (!new_pipe->top_pipe && !new_pipe->prev_odm_pipe) अणु
		/* Detect odm changes */
		अगर ((old_pipe->next_odm_pipe && new_pipe->next_odm_pipe
			&& old_pipe->next_odm_pipe->pipe_idx != new_pipe->next_odm_pipe->pipe_idx)
				|| (!old_pipe->next_odm_pipe && new_pipe->next_odm_pipe)
				|| (old_pipe->next_odm_pipe && !new_pipe->next_odm_pipe)
				|| old_pipe->stream_res.opp != new_pipe->stream_res.opp)
			new_pipe->update_flags.bits.odm = 1;

		/* Detect global sync changes */
		अगर (old_pipe->pipe_dlg_param.vपढ़ोy_offset != new_pipe->pipe_dlg_param.vपढ़ोy_offset
				|| old_pipe->pipe_dlg_param.vstartup_start != new_pipe->pipe_dlg_param.vstartup_start
				|| old_pipe->pipe_dlg_param.vupdate_offset != new_pipe->pipe_dlg_param.vupdate_offset
				|| old_pipe->pipe_dlg_param.vupdate_width != new_pipe->pipe_dlg_param.vupdate_width)
			new_pipe->update_flags.bits.global_sync = 1;
	पूर्ण

	/*
	 * Detect opp / tg change, only set on change, not on enable
	 * Assume mpcc inst = pipe index, अगर not this code needs to be updated
	 * since mpcc is what is affected by these. In fact all of our sequence
	 * makes this assumption at the moment with how hubp reset is matched to
	 * same index mpcc reset.
	 */
	अगर (old_pipe->stream_res.opp != new_pipe->stream_res.opp)
		new_pipe->update_flags.bits.opp_changed = 1;
	अगर (old_pipe->stream_res.tg != new_pipe->stream_res.tg)
		new_pipe->update_flags.bits.tg_changed = 1;

	/*
	 * Detect mpcc blending changes, only dpp inst and opp matter here,
	 * mpccs getting हटाओd/inserted update connected ones during their own
	 * programming
	 */
	अगर (old_pipe->plane_res.dpp != new_pipe->plane_res.dpp
			|| old_pipe->stream_res.opp != new_pipe->stream_res.opp)
		new_pipe->update_flags.bits.mpcc = 1;

	/* Detect dppclk change */
	अगर (old_pipe->plane_res.bw.dppclk_khz != new_pipe->plane_res.bw.dppclk_khz)
		new_pipe->update_flags.bits.dppclk = 1;

	/* Check क्रम scl update */
	अगर (स_भेद(&old_pipe->plane_res.scl_data, &new_pipe->plane_res.scl_data, माप(काष्ठा scaler_data)))
			new_pipe->update_flags.bits.scaler = 1;
	/* Check क्रम vp update */
	अगर (स_भेद(&old_pipe->plane_res.scl_data.viewport, &new_pipe->plane_res.scl_data.viewport, माप(काष्ठा rect))
			|| स_भेद(&old_pipe->plane_res.scl_data.viewport_c,
				&new_pipe->plane_res.scl_data.viewport_c, माप(काष्ठा rect)))
		new_pipe->update_flags.bits.viewport = 1;

	/* Detect dlg/ttu/rq updates */
	अणु
		काष्ठा _vcs_dpi_display_dlg_regs_st old_dlg_attr = old_pipe->dlg_regs;
		काष्ठा _vcs_dpi_display_ttu_regs_st old_ttu_attr = old_pipe->ttu_regs;
		काष्ठा _vcs_dpi_display_dlg_regs_st *new_dlg_attr = &new_pipe->dlg_regs;
		काष्ठा _vcs_dpi_display_ttu_regs_st *new_ttu_attr = &new_pipe->ttu_regs;

		/* Detect pipe पूर्णांकerdependent updates */
		अगर (old_dlg_attr.dst_y_prefetch != new_dlg_attr->dst_y_prefetch ||
				old_dlg_attr.vratio_prefetch != new_dlg_attr->vratio_prefetch ||
				old_dlg_attr.vratio_prefetch_c != new_dlg_attr->vratio_prefetch_c ||
				old_dlg_attr.dst_y_per_vm_vblank != new_dlg_attr->dst_y_per_vm_vblank ||
				old_dlg_attr.dst_y_per_row_vblank != new_dlg_attr->dst_y_per_row_vblank ||
				old_dlg_attr.dst_y_per_vm_flip != new_dlg_attr->dst_y_per_vm_flip ||
				old_dlg_attr.dst_y_per_row_flip != new_dlg_attr->dst_y_per_row_flip ||
				old_dlg_attr.refcyc_per_meta_chunk_vblank_l != new_dlg_attr->refcyc_per_meta_chunk_vblank_l ||
				old_dlg_attr.refcyc_per_meta_chunk_vblank_c != new_dlg_attr->refcyc_per_meta_chunk_vblank_c ||
				old_dlg_attr.refcyc_per_meta_chunk_flip_l != new_dlg_attr->refcyc_per_meta_chunk_flip_l ||
				old_dlg_attr.refcyc_per_line_delivery_pre_l != new_dlg_attr->refcyc_per_line_delivery_pre_l ||
				old_dlg_attr.refcyc_per_line_delivery_pre_c != new_dlg_attr->refcyc_per_line_delivery_pre_c ||
				old_ttu_attr.refcyc_per_req_delivery_pre_l != new_ttu_attr->refcyc_per_req_delivery_pre_l ||
				old_ttu_attr.refcyc_per_req_delivery_pre_c != new_ttu_attr->refcyc_per_req_delivery_pre_c ||
				old_ttu_attr.refcyc_per_req_delivery_pre_cur0 != new_ttu_attr->refcyc_per_req_delivery_pre_cur0 ||
				old_ttu_attr.refcyc_per_req_delivery_pre_cur1 != new_ttu_attr->refcyc_per_req_delivery_pre_cur1 ||
				old_ttu_attr.min_ttu_vblank != new_ttu_attr->min_ttu_vblank ||
				old_ttu_attr.qos_level_flip != new_ttu_attr->qos_level_flip) अणु
			old_dlg_attr.dst_y_prefetch = new_dlg_attr->dst_y_prefetch;
			old_dlg_attr.vratio_prefetch = new_dlg_attr->vratio_prefetch;
			old_dlg_attr.vratio_prefetch_c = new_dlg_attr->vratio_prefetch_c;
			old_dlg_attr.dst_y_per_vm_vblank = new_dlg_attr->dst_y_per_vm_vblank;
			old_dlg_attr.dst_y_per_row_vblank = new_dlg_attr->dst_y_per_row_vblank;
			old_dlg_attr.dst_y_per_vm_flip = new_dlg_attr->dst_y_per_vm_flip;
			old_dlg_attr.dst_y_per_row_flip = new_dlg_attr->dst_y_per_row_flip;
			old_dlg_attr.refcyc_per_meta_chunk_vblank_l = new_dlg_attr->refcyc_per_meta_chunk_vblank_l;
			old_dlg_attr.refcyc_per_meta_chunk_vblank_c = new_dlg_attr->refcyc_per_meta_chunk_vblank_c;
			old_dlg_attr.refcyc_per_meta_chunk_flip_l = new_dlg_attr->refcyc_per_meta_chunk_flip_l;
			old_dlg_attr.refcyc_per_line_delivery_pre_l = new_dlg_attr->refcyc_per_line_delivery_pre_l;
			old_dlg_attr.refcyc_per_line_delivery_pre_c = new_dlg_attr->refcyc_per_line_delivery_pre_c;
			old_ttu_attr.refcyc_per_req_delivery_pre_l = new_ttu_attr->refcyc_per_req_delivery_pre_l;
			old_ttu_attr.refcyc_per_req_delivery_pre_c = new_ttu_attr->refcyc_per_req_delivery_pre_c;
			old_ttu_attr.refcyc_per_req_delivery_pre_cur0 = new_ttu_attr->refcyc_per_req_delivery_pre_cur0;
			old_ttu_attr.refcyc_per_req_delivery_pre_cur1 = new_ttu_attr->refcyc_per_req_delivery_pre_cur1;
			old_ttu_attr.min_ttu_vblank = new_ttu_attr->min_ttu_vblank;
			old_ttu_attr.qos_level_flip = new_ttu_attr->qos_level_flip;
			new_pipe->update_flags.bits.hubp_पूर्णांकerdependent = 1;
		पूर्ण
		/* Detect any other updates to ttu/rq/dlg */
		अगर (स_भेद(&old_dlg_attr, &new_pipe->dlg_regs, माप(old_dlg_attr)) ||
				स_भेद(&old_ttu_attr, &new_pipe->ttu_regs, माप(old_ttu_attr)) ||
				स_भेद(&old_pipe->rq_regs, &new_pipe->rq_regs, माप(old_pipe->rq_regs)))
			new_pipe->update_flags.bits.hubp_rq_dlg_ttu = 1;
	पूर्ण
पूर्ण

अटल व्योम dcn20_update_dchubp_dpp(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा dpp *dpp = pipe_ctx->plane_res.dpp;
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	bool viewport_changed = false;

	अगर (pipe_ctx->update_flags.bits.dppclk)
		dpp->funcs->dpp_dppclk_control(dpp, false, true);

	/* TODO: Need input parameter to tell current DCHUB pipe tie to which OTG
	 * VTG is within DCHUBBUB which is commond block share by each pipe HUBP.
	 * VTG is 1:1 mapping with OTG. Each pipe HUBP will select which VTG
	 */
	अगर (pipe_ctx->update_flags.bits.hubp_rq_dlg_ttu) अणु
		hubp->funcs->hubp_vtg_sel(hubp, pipe_ctx->stream_res.tg->inst);

		hubp->funcs->hubp_setup(
			hubp,
			&pipe_ctx->dlg_regs,
			&pipe_ctx->ttu_regs,
			&pipe_ctx->rq_regs,
			&pipe_ctx->pipe_dlg_param);
	पूर्ण
	अगर (pipe_ctx->update_flags.bits.hubp_पूर्णांकerdependent)
		hubp->funcs->hubp_setup_पूर्णांकerdependent(
			hubp,
			&pipe_ctx->dlg_regs,
			&pipe_ctx->ttu_regs);

	अगर (pipe_ctx->update_flags.bits.enable ||
			pipe_ctx->update_flags.bits.plane_changed ||
			plane_state->update_flags.bits.bpp_change ||
			plane_state->update_flags.bits.input_csc_change ||
			plane_state->update_flags.bits.color_space_change ||
			plane_state->update_flags.bits.coeff_reduction_change) अणु
		काष्ठा dc_bias_and_scale bns_params = अणु0पूर्ण;

		// program the input csc
		dpp->funcs->dpp_setup(dpp,
				plane_state->क्रमmat,
				EXPANSION_MODE_ZERO,
				plane_state->input_csc_color_matrix,
				plane_state->color_space,
				शून्य);

		अगर (dpp->funcs->dpp_program_bias_and_scale) अणु
			//TODO :क्रम CNVC set scale and bias रेजिस्टरs अगर necessary
			build_prescale_params(&bns_params, plane_state);
			dpp->funcs->dpp_program_bias_and_scale(dpp, &bns_params);
		पूर्ण
	पूर्ण

	अगर (pipe_ctx->update_flags.bits.mpcc
			|| pipe_ctx->update_flags.bits.plane_changed
			|| plane_state->update_flags.bits.global_alpha_change
			|| plane_state->update_flags.bits.per_pixel_alpha_change) अणु
		// MPCC inst is equal to pipe index in practice
		पूर्णांक mpcc_inst = hubp->inst;
		पूर्णांक opp_inst;
		पूर्णांक opp_count = dc->res_pool->pipe_count;

		क्रम (opp_inst = 0; opp_inst < opp_count; opp_inst++) अणु
			अगर (dc->res_pool->opps[opp_inst]->mpcc_disconnect_pending[mpcc_inst]) अणु
				dc->res_pool->mpc->funcs->रुको_क्रम_idle(dc->res_pool->mpc, mpcc_inst);
				dc->res_pool->opps[opp_inst]->mpcc_disconnect_pending[mpcc_inst] = false;
				अवरोध;
			पूर्ण
		पूर्ण
		hws->funcs.update_mpcc(dc, pipe_ctx);
	पूर्ण

	अगर (pipe_ctx->update_flags.bits.scaler ||
			plane_state->update_flags.bits.scaling_change ||
			plane_state->update_flags.bits.position_change ||
			plane_state->update_flags.bits.per_pixel_alpha_change ||
			pipe_ctx->stream->update_flags.bits.scaling) अणु
		pipe_ctx->plane_res.scl_data.lb_params.alpha_en = pipe_ctx->plane_state->per_pixel_alpha;
		ASSERT(pipe_ctx->plane_res.scl_data.lb_params.depth == LB_PIXEL_DEPTH_30BPP);
		/* scaler configuration */
		pipe_ctx->plane_res.dpp->funcs->dpp_set_scaler(
				pipe_ctx->plane_res.dpp, &pipe_ctx->plane_res.scl_data);
	पूर्ण

	अगर (pipe_ctx->update_flags.bits.viewport ||
			(context == dc->current_state && plane_state->update_flags.bits.position_change) ||
			(context == dc->current_state && plane_state->update_flags.bits.scaling_change) ||
			(context == dc->current_state && pipe_ctx->stream->update_flags.bits.scaling)) अणु

		hubp->funcs->mem_program_viewport(
			hubp,
			&pipe_ctx->plane_res.scl_data.viewport,
			&pipe_ctx->plane_res.scl_data.viewport_c);
		viewport_changed = true;
	पूर्ण

	/* Any updates are handled in dc पूर्णांकerface, just need to apply existing क्रम plane enable */
	अगर ((pipe_ctx->update_flags.bits.enable || pipe_ctx->update_flags.bits.opp_changed ||
			pipe_ctx->update_flags.bits.scaler || viewport_changed == true) &&
			pipe_ctx->stream->cursor_attributes.address.quad_part != 0) अणु
		dc->hwss.set_cursor_position(pipe_ctx);
		dc->hwss.set_cursor_attribute(pipe_ctx);

		अगर (dc->hwss.set_cursor_sdr_white_level)
			dc->hwss.set_cursor_sdr_white_level(pipe_ctx);
	पूर्ण

	/* Any updates are handled in dc पूर्णांकerface, just need
	 * to apply existing क्रम plane enable / opp change */
	अगर (pipe_ctx->update_flags.bits.enable || pipe_ctx->update_flags.bits.opp_changed
			|| pipe_ctx->stream->update_flags.bits.gamut_remap
			|| pipe_ctx->stream->update_flags.bits.out_csc) अणु
		/* dpp/cm gamut remap*/
		dc->hwss.program_gamut_remap(pipe_ctx);

		/*call the dcn2 method which uses mpc csc*/
		dc->hwss.program_output_csc(dc,
				pipe_ctx,
				pipe_ctx->stream->output_color_space,
				pipe_ctx->stream->csc_color_matrix.matrix,
				hubp->opp_id);
	पूर्ण

	अगर (pipe_ctx->update_flags.bits.enable ||
			pipe_ctx->update_flags.bits.plane_changed ||
			pipe_ctx->update_flags.bits.opp_changed ||
			plane_state->update_flags.bits.pixel_क्रमmat_change ||
			plane_state->update_flags.bits.horizontal_mirror_change ||
			plane_state->update_flags.bits.rotation_change ||
			plane_state->update_flags.bits.swizzle_change ||
			plane_state->update_flags.bits.dcc_change ||
			plane_state->update_flags.bits.bpp_change ||
			plane_state->update_flags.bits.scaling_change ||
			plane_state->update_flags.bits.plane_size_change) अणु
		काष्ठा plane_size size = plane_state->plane_size;

		size.surface_size = pipe_ctx->plane_res.scl_data.viewport;
		hubp->funcs->hubp_program_surface_config(
			hubp,
			plane_state->क्रमmat,
			&plane_state->tiling_info,
			&size,
			plane_state->rotation,
			&plane_state->dcc,
			plane_state->horizontal_mirror,
			0);
		hubp->घातer_gated = false;
	पूर्ण

	अगर (pipe_ctx->update_flags.bits.enable ||
		pipe_ctx->update_flags.bits.plane_changed ||
		plane_state->update_flags.bits.addr_update)
		hws->funcs.update_plane_addr(dc, pipe_ctx);



	अगर (pipe_ctx->update_flags.bits.enable)
		hubp->funcs->set_blank(hubp, false);
पूर्ण


अटल व्योम dcn20_program_pipe(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	/* Only need to unblank on top pipe */
	अगर ((pipe_ctx->update_flags.bits.enable || pipe_ctx->stream->update_flags.bits.abm_level)
			&& !pipe_ctx->top_pipe && !pipe_ctx->prev_odm_pipe)
		hws->funcs.blank_pixel_data(dc, pipe_ctx, !pipe_ctx->plane_state->visible);

	/* Only update TG on top pipe */
	अगर (pipe_ctx->update_flags.bits.global_sync && !pipe_ctx->top_pipe
			&& !pipe_ctx->prev_odm_pipe) अणु

		pipe_ctx->stream_res.tg->funcs->program_global_sync(
				pipe_ctx->stream_res.tg,
				pipe_ctx->pipe_dlg_param.vपढ़ोy_offset,
				pipe_ctx->pipe_dlg_param.vstartup_start,
				pipe_ctx->pipe_dlg_param.vupdate_offset,
				pipe_ctx->pipe_dlg_param.vupdate_width);

		pipe_ctx->stream_res.tg->funcs->रुको_क्रम_state(pipe_ctx->stream_res.tg, CRTC_STATE_VBLANK);
		pipe_ctx->stream_res.tg->funcs->रुको_क्रम_state(pipe_ctx->stream_res.tg, CRTC_STATE_VACTIVE);

		pipe_ctx->stream_res.tg->funcs->set_vtg_params(
				pipe_ctx->stream_res.tg, &pipe_ctx->stream->timing, true);

		अगर (hws->funcs.setup_vupdate_पूर्णांकerrupt)
			hws->funcs.setup_vupdate_पूर्णांकerrupt(dc, pipe_ctx);
	पूर्ण

	अगर (pipe_ctx->update_flags.bits.odm)
		hws->funcs.update_odm(dc, context, pipe_ctx);

	अगर (pipe_ctx->update_flags.bits.enable) अणु
		dcn20_enable_plane(dc, pipe_ctx, context);
		अगर (dc->res_pool->hubbub->funcs->क्रमce_wm_propagate_to_pipes)
			dc->res_pool->hubbub->funcs->क्रमce_wm_propagate_to_pipes(dc->res_pool->hubbub);
	पूर्ण

	अगर (pipe_ctx->update_flags.raw || pipe_ctx->plane_state->update_flags.raw || pipe_ctx->stream->update_flags.raw)
		dcn20_update_dchubp_dpp(dc, pipe_ctx, context);

	अगर (pipe_ctx->update_flags.bits.enable
			|| pipe_ctx->plane_state->update_flags.bits.hdr_mult)
		hws->funcs.set_hdr_multiplier(pipe_ctx);

	अगर (pipe_ctx->update_flags.bits.enable ||
			pipe_ctx->plane_state->update_flags.bits.in_transfer_func_change ||
			pipe_ctx->plane_state->update_flags.bits.gamma_change)
		hws->funcs.set_input_transfer_func(dc, pipe_ctx, pipe_ctx->plane_state);

	/* dcn10_translate_regamma_to_hw_क्रमmat takes 750us to finish
	 * only करो gamma programming क्रम घातering on, पूर्णांकernal स_भेद to aव्योम
	 * updating on slave planes
	 */
	अगर (pipe_ctx->update_flags.bits.enable || pipe_ctx->stream->update_flags.bits.out_tf)
		hws->funcs.set_output_transfer_func(dc, pipe_ctx, pipe_ctx->stream);

	/* If the pipe has been enabled or has a dअगरferent opp, we
	 * should reprogram the fmt. This deals with हालs where
	 * पूर्णांकeration between mpc and odm combine on dअगरferent streams
	 * causes a dअगरferent pipe to be chosen to odm combine with.
	 */
	अगर (pipe_ctx->update_flags.bits.enable
	    || pipe_ctx->update_flags.bits.opp_changed) अणु

		pipe_ctx->stream_res.opp->funcs->opp_set_dyn_expansion(
			pipe_ctx->stream_res.opp,
			COLOR_SPACE_YCBCR601,
			pipe_ctx->stream->timing.display_color_depth,
			pipe_ctx->stream->संकेत);

		pipe_ctx->stream_res.opp->funcs->opp_program_fmt(
			pipe_ctx->stream_res.opp,
			&pipe_ctx->stream->bit_depth_params,
			&pipe_ctx->stream->clamping);
	पूर्ण
पूर्ण

व्योम dcn20_program_front_end_क्रम_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	DC_LOGGER_INIT(dc->ctx->logger);

	/* Carry over GSL groups in हाल the context is changing. */
       क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
               काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
               काष्ठा pipe_ctx *old_pipe_ctx =
                       &dc->current_state->res_ctx.pipe_ctx[i];

               अगर (pipe_ctx->stream == old_pipe_ctx->stream)
                       pipe_ctx->stream_res.gsl_group =
                               old_pipe_ctx->stream_res.gsl_group;
       पूर्ण

	अगर (dc->hwss.program_triplebuffer != शून्य && dc->debug.enable_tri_buf) अणु
		क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
			काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

			अगर (!pipe_ctx->top_pipe && !pipe_ctx->prev_odm_pipe && pipe_ctx->plane_state) अणु
				ASSERT(!pipe_ctx->plane_state->triplebuffer_flips);
				/*turn off triple buffer क्रम full update*/
				dc->hwss.program_triplebuffer(
						dc, pipe_ctx, pipe_ctx->plane_state->triplebuffer_flips);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Set pipe update flags and lock pipes */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		dcn20_detect_pipe_changes(&dc->current_state->res_ctx.pipe_ctx[i],
				&context->res_ctx.pipe_ctx[i]);

	/* OTG blank beक्रमe disabling all front ends */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (context->res_ctx.pipe_ctx[i].update_flags.bits.disable
				&& !context->res_ctx.pipe_ctx[i].top_pipe
				&& !context->res_ctx.pipe_ctx[i].prev_odm_pipe
				&& context->res_ctx.pipe_ctx[i].stream)
			hws->funcs.blank_pixel_data(dc, &context->res_ctx.pipe_ctx[i], true);


	/* Disconnect mpcc */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (context->res_ctx.pipe_ctx[i].update_flags.bits.disable
				|| context->res_ctx.pipe_ctx[i].update_flags.bits.opp_changed) अणु
			hws->funcs.plane_atomic_disconnect(dc, &dc->current_state->res_ctx.pipe_ctx[i]);
			DC_LOG_DC("Reset mpcc for pipe %d\n", dc->current_state->res_ctx.pipe_ctx[i].pipe_idx);
		पूर्ण

	/*
	 * Program all updated pipes, order matters क्रम mpcc setup. Start with
	 * top pipe and program all pipes that follow in order
	 */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		अगर (pipe->plane_state && !pipe->top_pipe) अणु
			जबतक (pipe) अणु
				dcn20_program_pipe(dc, pipe, context);
				pipe = pipe->bottom_pipe;
			पूर्ण
			/* Program secondary blending tree and ग_लिखोback pipes */
			pipe = &context->res_ctx.pipe_ctx[i];
			अगर (!pipe->prev_odm_pipe && pipe->stream->num_wb_info > 0
					&& (pipe->update_flags.raw || pipe->plane_state->update_flags.raw || pipe->stream->update_flags.raw)
					&& hws->funcs.program_all_ग_लिखोback_pipes_in_tree)
				hws->funcs.program_all_ग_लिखोback_pipes_in_tree(dc, pipe->stream, context);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn20_post_unlock_program_front_end(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	स्थिर अचिन्हित पूर्णांक TIMEOUT_FOR_PIPE_ENABLE_MS = 100;
	काष्ठा dce_hwseq *hwseq = dc->hwseq;

	DC_LOGGER_INIT(dc->ctx->logger);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (context->res_ctx.pipe_ctx[i].update_flags.bits.disable)
			dc->hwss.disable_plane(dc, &dc->current_state->res_ctx.pipe_ctx[i]);

	/*
	 * If we are enabling a pipe, we need to रुको क्रम pending clear as this is a critical
	 * part of the enable operation otherwise, DM may request an immediate flip which
	 * will cause HW to perक्रमm an "immediate enable" (as opposed to "vsync enable") which
	 * is unsupported on DCN.
	 */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		अगर (pipe->plane_state && !pipe->top_pipe && pipe->update_flags.bits.enable) अणु
			काष्ठा hubp *hubp = pipe->plane_res.hubp;
			पूर्णांक j = 0;

			क्रम (j = 0; j < TIMEOUT_FOR_PIPE_ENABLE_MS*1000
					&& hubp->funcs->hubp_is_flip_pending(hubp); j++)
				mdelay(1);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *mpcc_pipe;

		अगर (pipe->vtp_locked) अणु
			dc->hwseq->funcs.रुको_क्रम_blank_complete(pipe->stream_res.opp);
			pipe->plane_res.hubp->funcs->set_blank(pipe->plane_res.hubp, true);
			pipe->vtp_locked = false;

			क्रम (mpcc_pipe = pipe->bottom_pipe; mpcc_pipe; mpcc_pipe = mpcc_pipe->bottom_pipe)
				mpcc_pipe->plane_res.hubp->funcs->set_blank(mpcc_pipe->plane_res.hubp, true);

			क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
				अगर (context->res_ctx.pipe_ctx[i].update_flags.bits.disable)
					dc->hwss.disable_plane(dc, &dc->current_state->res_ctx.pipe_ctx[i]);
		पूर्ण
	पूर्ण
	/* WA to apply WM setting*/
	अगर (hwseq->wa.DEGVIDCN21)
		dc->res_pool->hubbub->funcs->apply_DEDCN21_147_wa(dc->res_pool->hubbub);


	/* WA क्रम stutter underflow during MPO transitions when adding 2nd plane */
	अगर (hwseq->wa.disallow_self_refresh_during_multi_plane_transition) अणु

		अगर (dc->current_state->stream_status[0].plane_count == 1 &&
				context->stream_status[0].plane_count > 1) अणु

			काष्ठा timing_generator *tg = dc->res_pool->timing_generators[0];

			dc->res_pool->hubbub->funcs->allow_self_refresh_control(dc->res_pool->hubbub, false);

			hwseq->wa_state.disallow_self_refresh_during_multi_plane_transition_applied = true;
			hwseq->wa_state.disallow_self_refresh_during_multi_plane_transition_applied_on_frame = tg->funcs->get_frame_count(tg);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn20_prepare_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	काष्ठा hubbub *hubbub = dc->res_pool->hubbub;

	dc->clk_mgr->funcs->update_घड़ीs(
			dc->clk_mgr,
			context,
			false);

	/* program dchubbub watermarks */
	dc->wm_optimized_required = hubbub->funcs->program_watermarks(hubbub,
					&context->bw_ctx.bw.dcn.watermarks,
					dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000,
					false);
पूर्ण

व्योम dcn20_optimize_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	काष्ठा hubbub *hubbub = dc->res_pool->hubbub;

	/* program dchubbub watermarks */
	hubbub->funcs->program_watermarks(hubbub,
					&context->bw_ctx.bw.dcn.watermarks,
					dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000,
					true);

	dc->clk_mgr->funcs->update_घड़ीs(
			dc->clk_mgr,
			context,
			true);
पूर्ण

bool dcn20_update_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	/* recalculate DML parameters */
	अगर (!dc->res_pool->funcs->validate_bandwidth(dc, context, false))
		वापस false;

	/* apply updated bandwidth parameters */
	dc->hwss.prepare_bandwidth(dc, context);

	/* update hubp configs क्रम all pipes */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->plane_state == शून्य)
			जारी;

		अगर (pipe_ctx->top_pipe == शून्य) अणु
			bool blank = !is_pipe_tree_visible(pipe_ctx);

			pipe_ctx->stream_res.tg->funcs->program_global_sync(
					pipe_ctx->stream_res.tg,
					pipe_ctx->pipe_dlg_param.vपढ़ोy_offset,
					pipe_ctx->pipe_dlg_param.vstartup_start,
					pipe_ctx->pipe_dlg_param.vupdate_offset,
					pipe_ctx->pipe_dlg_param.vupdate_width);

			pipe_ctx->stream_res.tg->funcs->set_vtg_params(
					pipe_ctx->stream_res.tg, &pipe_ctx->stream->timing, false);

			अगर (pipe_ctx->prev_odm_pipe == शून्य)
				hws->funcs.blank_pixel_data(dc, pipe_ctx, blank);

			अगर (hws->funcs.setup_vupdate_पूर्णांकerrupt)
				hws->funcs.setup_vupdate_पूर्णांकerrupt(dc, pipe_ctx);
		पूर्ण

		pipe_ctx->plane_res.hubp->funcs->hubp_setup(
				pipe_ctx->plane_res.hubp,
					&pipe_ctx->dlg_regs,
					&pipe_ctx->ttu_regs,
					&pipe_ctx->rq_regs,
					&pipe_ctx->pipe_dlg_param);
	पूर्ण

	वापस true;
पूर्ण

व्योम dcn20_enable_ग_लिखोback(
		काष्ठा dc *dc,
		काष्ठा dc_ग_लिखोback_info *wb_info,
		काष्ठा dc_state *context)
अणु
	काष्ठा dwbc *dwb;
	काष्ठा mcअगर_wb *mcअगर_wb;
	काष्ठा timing_generator *optc;

	ASSERT(wb_info->dwb_pipe_inst < MAX_DWB_PIPES);
	ASSERT(wb_info->wb_enabled);
	dwb = dc->res_pool->dwbc[wb_info->dwb_pipe_inst];
	mcअगर_wb = dc->res_pool->mcअगर_wb[wb_info->dwb_pipe_inst];

	/* set the OPTC source mux */
	optc = dc->res_pool->timing_generators[dwb->otg_inst];
	optc->funcs->set_dwb_source(optc, wb_info->dwb_pipe_inst);
	/* set MCIF_WB buffer and arbitration configuration */
	mcअगर_wb->funcs->config_mcअगर_buf(mcअगर_wb, &wb_info->mcअगर_buf_params, wb_info->dwb_params.dest_height);
	mcअगर_wb->funcs->config_mcअगर_arb(mcअगर_wb, &context->bw_ctx.bw.dcn.bw_ग_लिखोback.mcअगर_wb_arb[wb_info->dwb_pipe_inst]);
	/* Enable MCIF_WB */
	mcअगर_wb->funcs->enable_mcअगर(mcअगर_wb);
	/* Enable DWB */
	dwb->funcs->enable(dwb, &wb_info->dwb_params);
	/* TODO: add sequence to enable/disable warmup */
पूर्ण

व्योम dcn20_disable_ग_लिखोback(
		काष्ठा dc *dc,
		अचिन्हित पूर्णांक dwb_pipe_inst)
अणु
	काष्ठा dwbc *dwb;
	काष्ठा mcअगर_wb *mcअगर_wb;

	ASSERT(dwb_pipe_inst < MAX_DWB_PIPES);
	dwb = dc->res_pool->dwbc[dwb_pipe_inst];
	mcअगर_wb = dc->res_pool->mcअगर_wb[dwb_pipe_inst];

	dwb->funcs->disable(dwb);
	mcअगर_wb->funcs->disable_mcअगर(mcअगर_wb);
पूर्ण

bool dcn20_रुको_क्रम_blank_complete(
		काष्ठा output_pixel_processor *opp)
अणु
	पूर्णांक counter;

	क्रम (counter = 0; counter < 1000; counter++) अणु
		अगर (opp->funcs->dpg_is_blanked(opp))
			अवरोध;

		udelay(100);
	पूर्ण

	अगर (counter == 1000) अणु
		dm_error("DC: failed to blank crtc!\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool dcn20_dmdata_status_करोne(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;

	अगर (!hubp)
		वापस false;
	वापस hubp->funcs->dmdata_status_करोne(hubp);
पूर्ण

व्योम dcn20_disable_stream_gating(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;

	अगर (pipe_ctx->stream_res.dsc) अणु
		काष्ठा pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;

		hws->funcs.dsc_pg_control(hws, pipe_ctx->stream_res.dsc->inst, true);
		जबतक (odm_pipe) अणु
			hws->funcs.dsc_pg_control(hws, odm_pipe->stream_res.dsc->inst, true);
			odm_pipe = odm_pipe->next_odm_pipe;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn20_enable_stream_gating(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;

	अगर (pipe_ctx->stream_res.dsc) अणु
		काष्ठा pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;

		hws->funcs.dsc_pg_control(hws, pipe_ctx->stream_res.dsc->inst, false);
		जबतक (odm_pipe) अणु
			hws->funcs.dsc_pg_control(hws, odm_pipe->stream_res.dsc->inst, false);
			odm_pipe = odm_pipe->next_odm_pipe;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn20_set_dmdata_attributes(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_dmdata_attributes attr = अणु 0 पूर्ण;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;

	attr.dmdata_mode = DMDATA_HW_MODE;
	attr.dmdata_size =
		dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत) ? 32 : 36;
	attr.address.quad_part =
			pipe_ctx->stream->dmdata_address.quad_part;
	attr.dmdata_dl_delta = 0;
	attr.dmdata_qos_mode = 0;
	attr.dmdata_qos_level = 0;
	attr.dmdata_repeat = 1; /* always repeat */
	attr.dmdata_updated = 1;
	attr.dmdata_sw_data = शून्य;

	hubp->funcs->dmdata_set_attributes(hubp, &attr);
पूर्ण

व्योम dcn20_init_vm_ctx(
		काष्ठा dce_hwseq *hws,
		काष्ठा dc *dc,
		काष्ठा dc_भव_addr_space_config *va_config,
		पूर्णांक vmid)
अणु
	काष्ठा dcn_hubbub_virt_addr_config config;

	अगर (vmid == 0) अणु
		ASSERT(0); /* VMID cannot be 0 क्रम vm context */
		वापस;
	पूर्ण

	config.page_table_start_addr = va_config->page_table_start_addr;
	config.page_table_end_addr = va_config->page_table_end_addr;
	config.page_table_block_size = va_config->page_table_block_size_in_bytes;
	config.page_table_depth = va_config->page_table_depth;
	config.page_table_base_addr = va_config->page_table_base_addr;

	dc->res_pool->hubbub->funcs->init_vm_ctx(dc->res_pool->hubbub, &config, vmid);
पूर्ण

पूर्णांक dcn20_init_sys_ctx(काष्ठा dce_hwseq *hws, काष्ठा dc *dc, काष्ठा dc_phy_addr_space_config *pa_config)
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
	config.page_table_शेष_page_addr = pa_config->page_table_शेष_page_addr;

	वापस dc->res_pool->hubbub->funcs->init_dchub_sys_ctx(dc->res_pool->hubbub, &config);
पूर्ण

अटल bool patch_address_क्रम_sbs_tb_stereo(
		काष्ठा pipe_ctx *pipe_ctx, PHYSICAL_ADDRESS_LOC *addr)
अणु
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	bool sec_split = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->plane_state == pipe_ctx->plane_state;
	अगर (sec_split && plane_state->address.type == PLN_ADDR_TYPE_GRPH_STEREO &&
			(pipe_ctx->stream->timing.timing_3d_क्रमmat ==
			TIMING_3D_FORMAT_SIDE_BY_SIDE ||
			pipe_ctx->stream->timing.timing_3d_क्रमmat ==
			TIMING_3D_FORMAT_TOP_AND_BOTTOM)) अणु
		*addr = plane_state->address.grph_stereo.left_addr;
		plane_state->address.grph_stereo.left_addr =
				plane_state->address.grph_stereo.right_addr;
		वापस true;
	पूर्ण

	अगर (pipe_ctx->stream->view_क्रमmat != VIEW_3D_FORMAT_NONE &&
			plane_state->address.type != PLN_ADDR_TYPE_GRPH_STEREO) अणु
		plane_state->address.type = PLN_ADDR_TYPE_GRPH_STEREO;
		plane_state->address.grph_stereo.right_addr =
				plane_state->address.grph_stereo.left_addr;
		plane_state->address.grph_stereo.right_meta_addr =
				plane_state->address.grph_stereo.left_meta_addr;
	पूर्ण
	वापस false;
पूर्ण

व्योम dcn20_update_plane_addr(स्थिर काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	bool addr_patched = false;
	PHYSICAL_ADDRESS_LOC addr;
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;

	अगर (plane_state == शून्य)
		वापस;

	addr_patched = patch_address_क्रम_sbs_tb_stereo(pipe_ctx, &addr);

	// Call Helper to track VMID use
	vm_helper_mark_vmid_used(dc->vm_helper, plane_state->address.vmid, pipe_ctx->plane_res.hubp->inst);

	pipe_ctx->plane_res.hubp->funcs->hubp_program_surface_flip_and_addr(
			pipe_ctx->plane_res.hubp,
			&plane_state->address,
			plane_state->flip_immediate);

	plane_state->status.requested_address = plane_state->address;

	अगर (plane_state->flip_immediate)
		plane_state->status.current_address = plane_state->address;

	अगर (addr_patched)
		pipe_ctx->plane_state->address.grph_stereo.left_addr = addr;
पूर्ण

व्योम dcn20_unblank_stream(काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_link_settings *link_settings)
अणु
	काष्ठा encoder_unblank_param params = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	काष्ठा dce_hwseq *hws = link->dc->hwseq;
	काष्ठा pipe_ctx *odm_pipe;

	params.opp_cnt = 1;
	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) अणु
		params.opp_cnt++;
	पूर्ण
	/* only 3 items below are used by unblank */
	params.timing = pipe_ctx->stream->timing;

	params.link_settings.link_rate = link_settings->link_rate;

	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत)) अणु
		अगर (optc2_is_two_pixels_per_contaपूर्णांकer(&stream->timing) || params.opp_cnt > 1)
			params.timing.pix_clk_100hz /= 2;
		pipe_ctx->stream_res.stream_enc->funcs->dp_set_odm_combine(
				pipe_ctx->stream_res.stream_enc, params.opp_cnt > 1);
		pipe_ctx->stream_res.stream_enc->funcs->dp_unblank(pipe_ctx->stream_res.stream_enc, &params);
	पूर्ण

	अगर (link->local_sink && link->local_sink->sink_संकेत == SIGNAL_TYPE_EDP) अणु
		hws->funcs.edp_backlight_control(link, true);
	पूर्ण
पूर्ण

व्योम dcn20_setup_vupdate_पूर्णांकerrupt(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;
	पूर्णांक start_line = dc->hwss.get_vupdate_offset_from_vsync(pipe_ctx);

	अगर (start_line < 0)
		start_line = 0;

	अगर (tg->funcs->setup_vertical_पूर्णांकerrupt2)
		tg->funcs->setup_vertical_पूर्णांकerrupt2(tg, start_line);
पूर्ण

अटल व्योम dcn20_reset_back_end_क्रम_pipe(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dc_link *link;
	DC_LOGGER_INIT(dc->ctx->logger);
	अगर (pipe_ctx->stream_res.stream_enc == शून्य) अणु
		pipe_ctx->stream = शून्य;
		वापस;
	पूर्ण

	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		link = pipe_ctx->stream->link;
		/* DPMS may alपढ़ोy disable or */
		/* dpms_off status is incorrect due to fastboot
		 * feature. When प्रणाली resume from S4 with second
		 * screen only, the dpms_off would be true but
		 * VBIOS lit up eDP, so check link status too.
		 */
		अगर (!pipe_ctx->stream->dpms_off || link->link_status.link_active)
			core_link_disable_stream(pipe_ctx);
		अन्यथा अगर (pipe_ctx->stream_res.audio)
			dc->hwss.disable_audio_stream(pipe_ctx);

		/* मुक्त acquired resources */
		अगर (pipe_ctx->stream_res.audio) अणु
			/*disable az_endpoपूर्णांक*/
			pipe_ctx->stream_res.audio->funcs->az_disable(pipe_ctx->stream_res.audio);

			/*मुक्त audio*/
			अगर (dc->caps.dynamic_audio == true) अणु
				/*we have to dynamic arbitrate the audio endpoपूर्णांकs*/
				/*we मुक्त the resource, need reset is_audio_acquired*/
				update_audio_usage(&dc->current_state->res_ctx, dc->res_pool,
						pipe_ctx->stream_res.audio, false);
				pipe_ctx->stream_res.audio = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	अन्यथा अगर (pipe_ctx->stream_res.dsc) अणु
		dp_set_dsc_enable(pipe_ctx, false);
	पूर्ण

	/* by upper caller loop, parent pipe: pipe0, will be reset last.
	 * back end share by all pipes and will be disable only when disable
	 * parent pipe.
	 */
	अगर (pipe_ctx->top_pipe == शून्य) अणु

		dc->hwss.set_abm_immediate_disable(pipe_ctx);

		pipe_ctx->stream_res.tg->funcs->disable_crtc(pipe_ctx->stream_res.tg);

		pipe_ctx->stream_res.tg->funcs->enable_optc_घड़ी(pipe_ctx->stream_res.tg, false);
		अगर (pipe_ctx->stream_res.tg->funcs->set_odm_bypass)
			pipe_ctx->stream_res.tg->funcs->set_odm_bypass(
					pipe_ctx->stream_res.tg, &pipe_ctx->stream->timing);

		अगर (pipe_ctx->stream_res.tg->funcs->set_drr)
			pipe_ctx->stream_res.tg->funcs->set_drr(
					pipe_ctx->stream_res.tg, शून्य);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (&dc->current_state->res_ctx.pipe_ctx[i] == pipe_ctx)
			अवरोध;

	अगर (i == dc->res_pool->pipe_count)
		वापस;

	pipe_ctx->stream = शून्य;
	DC_LOG_DEBUG("Reset back end for pipe %d, tg:%d\n",
					pipe_ctx->pipe_idx, pipe_ctx->stream_res.tg->inst);
पूर्ण

व्योम dcn20_reset_hw_ctx_wrap(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	/* Reset Back End*/
	क्रम (i = dc->res_pool->pipe_count - 1; i >= 0 ; i--) अणु
		काष्ठा pipe_ctx *pipe_ctx_old =
			&dc->current_state->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (!pipe_ctx_old->stream)
			जारी;

		अगर (pipe_ctx_old->top_pipe || pipe_ctx_old->prev_odm_pipe)
			जारी;

		अगर (!pipe_ctx->stream ||
				pipe_need_reprogram(pipe_ctx_old, pipe_ctx)) अणु
			काष्ठा घड़ी_source *old_clk = pipe_ctx_old->घड़ी_source;

			dcn20_reset_back_end_क्रम_pipe(dc, pipe_ctx_old, dc->current_state);
			अगर (hws->funcs.enable_stream_gating)
				hws->funcs.enable_stream_gating(dc, pipe_ctx);
			अगर (old_clk)
				old_clk->funcs->cs_घातer_करोwn(old_clk);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn20_get_mpctree_visual_confirm_color(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा tg_color *color)
अणु
	स्थिर काष्ठा tg_color pipe_colors[6] = अणु
			अणुMAX_TG_COLOR_VALUE, 0, 0पूर्ण, // red
			अणुMAX_TG_COLOR_VALUE, MAX_TG_COLOR_VALUE / 4, 0पूर्ण, // orange
			अणुMAX_TG_COLOR_VALUE, MAX_TG_COLOR_VALUE, 0पूर्ण, // yellow
			अणु0, MAX_TG_COLOR_VALUE, 0पूर्ण, // green
			अणु0, 0, MAX_TG_COLOR_VALUEपूर्ण, // blue
			अणुMAX_TG_COLOR_VALUE / 2, 0, MAX_TG_COLOR_VALUE / 2पूर्ण, // purple
	पूर्ण;

	काष्ठा pipe_ctx *top_pipe = pipe_ctx;

	जबतक (top_pipe->top_pipe) अणु
		top_pipe = top_pipe->top_pipe;
	पूर्ण

	*color = pipe_colors[top_pipe->pipe_idx];
पूर्ण

व्योम dcn20_update_mpcc(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा mpcc_blnd_cfg blnd_cfg = अणु अणु0पूर्ण पूर्ण;
	bool per_pixel_alpha = pipe_ctx->plane_state->per_pixel_alpha;
	पूर्णांक mpcc_id;
	काष्ठा mpcc *new_mpcc;
	काष्ठा mpc *mpc = dc->res_pool->mpc;
	काष्ठा mpc_tree *mpc_tree_params = &(pipe_ctx->stream_res.opp->mpc_tree_params);

	// input to MPCC is always RGB, by शेष leave black_color at 0
	अगर (dc->debug.visual_confirm == VISUAL_CONFIRM_HDR) अणु
		hws->funcs.get_hdr_visual_confirm_color(pipe_ctx, &blnd_cfg.black_color);
	पूर्ण अन्यथा अगर (dc->debug.visual_confirm == VISUAL_CONFIRM_SURFACE) अणु
		hws->funcs.get_surface_visual_confirm_color(pipe_ctx, &blnd_cfg.black_color);
	पूर्ण अन्यथा अगर (dc->debug.visual_confirm == VISUAL_CONFIRM_MPCTREE) अणु
		dcn20_get_mpctree_visual_confirm_color(pipe_ctx, &blnd_cfg.black_color);
	पूर्ण

	अगर (per_pixel_alpha)
		blnd_cfg.alpha_mode = MPCC_ALPHA_BLEND_MODE_PER_PIXEL_ALPHA;
	अन्यथा
		blnd_cfg.alpha_mode = MPCC_ALPHA_BLEND_MODE_GLOBAL_ALPHA;

	blnd_cfg.overlap_only = false;
	blnd_cfg.global_gain = 0xff;

	अगर (pipe_ctx->plane_state->global_alpha)
		blnd_cfg.global_alpha = pipe_ctx->plane_state->global_alpha_value;
	अन्यथा
		blnd_cfg.global_alpha = 0xff;

	blnd_cfg.background_color_bpc = 4;
	blnd_cfg.bottom_gain_mode = 0;
	blnd_cfg.top_gain = 0x1f000;
	blnd_cfg.bottom_inside_gain = 0x1f000;
	blnd_cfg.bottom_outside_gain = 0x1f000;
	blnd_cfg.pre_multiplied_alpha = per_pixel_alpha;
	अगर (pipe_ctx->plane_state->क्रमmat
			== SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA)
		blnd_cfg.pre_multiplied_alpha = false;

	/*
	 * TODO: हटाओ hack
	 * Note: currently there is a bug in init_hw such that
	 * on resume from hibernate, BIOS sets up MPCC0, and
	 * we करो mpcc_हटाओ but the mpcc cannot go to idle
	 * after हटाओ. This cause us to pick mpcc1 here,
	 * which causes a pstate hang क्रम yet unknown reason.
	 */
	mpcc_id = hubp->inst;

	/* If there is no full update, करोn't need to touch MPC tree*/
	अगर (!pipe_ctx->plane_state->update_flags.bits.full_update &&
		!pipe_ctx->update_flags.bits.mpcc) अणु
		mpc->funcs->update_blending(mpc, &blnd_cfg, mpcc_id);
		वापस;
	पूर्ण

	/* check अगर this MPCC is alपढ़ोy being used */
	new_mpcc = mpc->funcs->get_mpcc_क्रम_dpp(mpc_tree_params, mpcc_id);
	/* हटाओ MPCC अगर being used */
	अगर (new_mpcc != शून्य)
		mpc->funcs->हटाओ_mpcc(mpc, mpc_tree_params, new_mpcc);
	अन्यथा
		अगर (dc->debug.sanity_checks)
			mpc->funcs->निश्चित_mpcc_idle_beक्रमe_connect(
					dc->res_pool->mpc, mpcc_id);

	/* Call MPC to insert new plane */
	new_mpcc = mpc->funcs->insert_plane(dc->res_pool->mpc,
			mpc_tree_params,
			&blnd_cfg,
			शून्य,
			शून्य,
			hubp->inst,
			mpcc_id);

	ASSERT(new_mpcc != शून्य);
	hubp->opp_id = pipe_ctx->stream_res.opp->inst;
	hubp->mpcc_id = mpcc_id;
पूर्ण

व्योम dcn20_enable_stream(काष्ठा pipe_ctx *pipe_ctx)
अणु
	क्रमागत dc_lane_count lane_count =
		pipe_ctx->stream->link->cur_link_settings.lane_count;

	काष्ठा dc_crtc_timing *timing = &pipe_ctx->stream->timing;
	काष्ठा dc_link *link = pipe_ctx->stream->link;

	uपूर्णांक32_t active_total_with_borders;
	uपूर्णांक32_t early_control = 0;
	काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;

	/* For MST, there are multiply stream go to only one link.
	 * connect DIG back_end to front_end जबतक enable_stream and
	 * disconnect them during disable_stream
	 * BY this, it is logic clean to separate stream and link
	 */
	link->link_enc->funcs->connect_dig_be_to_fe(link->link_enc,
						    pipe_ctx->stream_res.stream_enc->id, true);

	अगर (pipe_ctx->plane_state && pipe_ctx->plane_state->flip_immediate != 1) अणु
		अगर (link->dc->hwss.program_dmdata_engine)
			link->dc->hwss.program_dmdata_engine(pipe_ctx);
	पूर्ण

	link->dc->hwss.update_info_frame(pipe_ctx);

	/* enable early control to aव्योम corruption on DP monitor*/
	active_total_with_borders =
			timing->h_addressable
				+ timing->h_border_left
				+ timing->h_border_right;

	अगर (lane_count != 0)
		early_control = active_total_with_borders % lane_count;

	अगर (early_control == 0)
		early_control = lane_count;

	tg->funcs->set_early_control(tg, early_control);

	/* enable audio only within mode set */
	अगर (pipe_ctx->stream_res.audio != शून्य) अणु
		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_enable(pipe_ctx->stream_res.stream_enc);
	पूर्ण
पूर्ण

व्योम dcn20_program_dmdata_engine(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state    *stream     = pipe_ctx->stream;
	काष्ठा hubp               *hubp       = pipe_ctx->plane_res.hubp;
	bool                       enable     = false;
	काष्ठा stream_encoder     *stream_enc = pipe_ctx->stream_res.stream_enc;
	क्रमागत dynamic_metadata_mode mode       = dc_is_dp_संकेत(stream->संकेत)
							? dmdata_dp
							: dmdata_hdmi;

	/* अगर using dynamic meta, करोn't set up generic infopackets */
	अगर (pipe_ctx->stream->dmdata_address.quad_part != 0) अणु
		pipe_ctx->stream_res.encoder_info_frame.hdrsmd.valid = false;
		enable = true;
	पूर्ण

	अगर (!hubp)
		वापस;

	अगर (!stream_enc || !stream_enc->funcs->set_dynamic_metadata)
		वापस;

	stream_enc->funcs->set_dynamic_metadata(stream_enc, enable,
						hubp->inst, mode);
पूर्ण

व्योम dcn20_fpga_init_hw(काष्ठा dc *dc)
अणु
	पूर्णांक i, j;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा resource_pool *res_pool = dc->res_pool;
	काष्ठा dc_state  *context = dc->current_state;

	अगर (dc->clk_mgr && dc->clk_mgr->funcs->init_घड़ीs)
		dc->clk_mgr->funcs->init_घड़ीs(dc->clk_mgr);

	// Initialize the dccg
	अगर (res_pool->dccg->funcs->dccg_init)
		res_pool->dccg->funcs->dccg_init(res_pool->dccg);

	//Enable ability to घातer gate / करोn't क्रमce घातer on permanently
	hws->funcs.enable_घातer_gating_plane(hws, true);

	// Specअगरic to FPGA dccg and रेजिस्टरs
	REG_WRITE(RBBMIF_TIMEOUT_DIS, 0xFFFFFFFF);
	REG_WRITE(RBBMIF_TIMEOUT_DIS_2, 0xFFFFFFFF);

	hws->funcs.dccg_init(hws);

	REG_UPDATE(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_REFDIV, 2);
	REG_UPDATE(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_ENABLE, 1);
	अगर (REG(REFCLK_CNTL))
		REG_WRITE(REFCLK_CNTL, 0);
	//


	/* Blank pixel data with OPP DPG */
	क्रम (i = 0; i < dc->res_pool->timing_generator_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];

		अगर (tg->funcs->is_tg_enabled(tg))
			dcn20_init_blank(dc, tg);
	पूर्ण

	क्रम (i = 0; i < res_pool->timing_generator_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];

		अगर (tg->funcs->is_tg_enabled(tg))
			tg->funcs->lock(tg);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा dpp *dpp = res_pool->dpps[i];

		dpp->funcs->dpp_reset(dpp);
	पूर्ण

	/* Reset all MPCC muxes */
	res_pool->mpc->funcs->mpc_init(res_pool->mpc);

	/* initialize OPP mpc_tree parameter */
	क्रम (i = 0; i < dc->res_pool->res_cap->num_opp; i++) अणु
		res_pool->opps[i]->mpc_tree_params.opp_id = res_pool->opps[i]->inst;
		res_pool->opps[i]->mpc_tree_params.opp_list = शून्य;
		क्रम (j = 0; j < MAX_PIPES; j++)
			res_pool->opps[i]->mpcc_disconnect_pending[j] = false;
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		काष्ठा hubp *hubp = dc->res_pool->hubps[i];
		काष्ठा dpp *dpp = dc->res_pool->dpps[i];

		pipe_ctx->stream_res.tg = tg;
		pipe_ctx->pipe_idx = i;

		pipe_ctx->plane_res.hubp = hubp;
		pipe_ctx->plane_res.dpp = dpp;
		pipe_ctx->plane_res.mpcc_inst = dpp->inst;
		hubp->mpcc_id = dpp->inst;
		hubp->opp_id = OPP_ID_INVALID;
		hubp->घातer_gated = false;
		pipe_ctx->stream_res.opp = शून्य;

		hubp->funcs->hubp_init(hubp);

		//dc->res_pool->opps[i]->mpc_tree_params.opp_id = dc->res_pool->opps[i]->inst;
		//dc->res_pool->opps[i]->mpc_tree_params.opp_list = शून्य;
		dc->res_pool->opps[i]->mpcc_disconnect_pending[pipe_ctx->plane_res.mpcc_inst] = true;
		pipe_ctx->stream_res.opp = dc->res_pool->opps[i];
		/*to करो*/
		hws->funcs.plane_atomic_disconnect(dc, pipe_ctx);
	पूर्ण

	/* initialize DWB poपूर्णांकer to MCIF_WB */
	क्रम (i = 0; i < res_pool->res_cap->num_dwb; i++)
		res_pool->dwbc[i]->mcअगर = res_pool->mcअगर_wb[i];

	क्रम (i = 0; i < dc->res_pool->timing_generator_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];

		अगर (tg->funcs->is_tg_enabled(tg))
			tg->funcs->unlock(tg);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		dc->hwss.disable_plane(dc, pipe_ctx);

		pipe_ctx->stream_res.tg = शून्य;
		pipe_ctx->plane_res.hubp = शून्य;
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->timing_generator_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];

		tg->funcs->tg_init(tg);
	पूर्ण
पूर्ण
#अगर_अघोषित TRIM_FSFT
bool dcn20_optimize_timing_क्रम_fsft(काष्ठा dc *dc,
		काष्ठा dc_crtc_timing *timing,
		अचिन्हित पूर्णांक max_input_rate_in_khz)
अणु
	अचिन्हित पूर्णांक old_v_front_porch;
	अचिन्हित पूर्णांक old_v_total;
	अचिन्हित पूर्णांक max_input_rate_in_100hz;
	अचिन्हित दीर्घ दीर्घ new_v_total;

	max_input_rate_in_100hz = max_input_rate_in_khz * 10;
	अगर (max_input_rate_in_100hz < timing->pix_clk_100hz)
		वापस false;

	old_v_total = timing->v_total;
	old_v_front_porch = timing->v_front_porch;

	timing->fast_transport_output_rate_100hz = timing->pix_clk_100hz;
	timing->pix_clk_100hz = max_input_rate_in_100hz;

	new_v_total = भाग_u64((अचिन्हित दीर्घ दीर्घ)old_v_total * max_input_rate_in_100hz, timing->pix_clk_100hz);

	timing->v_total = new_v_total;
	timing->v_front_porch = old_v_front_porch + (timing->v_total - old_v_total);
	वापस true;
पूर्ण
#पूर्ण_अगर

व्योम dcn20_set_disp_pattern_generator(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत controller_dp_test_pattern test_pattern,
		क्रमागत controller_dp_color_space color_space,
		क्रमागत dc_color_depth color_depth,
		स्थिर काष्ठा tg_color *solid_color,
		पूर्णांक width, पूर्णांक height, पूर्णांक offset)
अणु
	pipe_ctx->stream_res.opp->funcs->opp_set_disp_pattern_generator(pipe_ctx->stream_res.opp, test_pattern,
			color_space, color_depth, solid_color, width, height, offset);
पूर्ण
