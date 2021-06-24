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

#समावेश "dcn302_hwseq.h"

#समावेश "dce/dce_hwseq.h"

#समावेश "reg_helper.h"
#समावेश "dc.h"

#घोषणा DC_LOGGER_INIT(logger)

#घोषणा CTX \
	hws->ctx
#घोषणा REG(reg)\
	hws->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name


व्योम dcn302_dpp_pg_control(काष्ठा dce_hwseq *hws, अचिन्हित पूर्णांक dpp_inst, bool घातer_on)
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
		/*
		 * Do not घातer gate DPP4, should be left at HW शेष, घातer on permanently.
		 * PG on Pipe4 is De-featured, attempting to put it to PG state may result in hard
		 * reset.
		 * REG_UPDATE(DOMAIN9_PG_CONFIG,
		 *		DOMAIN9_POWER_GATE, घातer_gate);
		 *
		 * REG_WAIT(DOMAIN9_PG_STATUS,
		 *		DOMAIN9_PGFSM_PWR_STATUS, pwr_status,
		 *		1, 1000);
		 */
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण
पूर्ण

व्योम dcn302_hubp_pg_control(काष्ठा dce_hwseq *hws, अचिन्हित पूर्णांक hubp_inst, bool घातer_on)
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
		/*
		 * Do not घातer gate DCHUB4, should be left at HW शेष, घातer on permanently.
		 * PG on Pipe4 is De-featured, attempting to put it to PG state may result in hard
		 * reset.
		 * REG_UPDATE(DOMAIN8_PG_CONFIG,
		 *		DOMAIN8_POWER_GATE, घातer_gate);
		 *
		 * REG_WAIT(DOMAIN8_PG_STATUS,
		 *		DOMAIN8_PGFSM_PWR_STATUS, pwr_status,
		 *		1, 1000);
		 */
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण
पूर्ण

व्योम dcn302_dsc_pg_control(काष्ठा dce_hwseq *hws, अचिन्हित पूर्णांक dsc_inst, bool घातer_on)
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
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	अगर (org_ip_request_cntl == 0)
		REG_SET(DC_IP_REQUEST_CNTL, 0, IP_REQUEST_EN, 0);
पूर्ण
