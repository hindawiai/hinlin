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
#समावेश "dcn10_hubp.h"
#समावेश "dcn10_hubbub.h"
#समावेश "reg_helper.h"

#घोषणा CTX \
	hubbub1->base.ctx
#घोषणा DC_LOGGER \
	hubbub1->base.ctx->logger
#घोषणा REG(reg)\
	hubbub1->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubbub1->shअगरts->field_name, hubbub1->masks->field_name

व्योम hubbub1_wm_पढ़ो_state(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_wm *wm)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	काष्ठा dcn_hubbub_wm_set *s;

	स_रखो(wm, 0, माप(काष्ठा dcn_hubbub_wm));

	s = &wm->sets[0];
	s->wm_set = 0;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A);
	s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A);

	s = &wm->sets[1];
	s->wm_set = 1;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B);
	s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B);

	s = &wm->sets[2];
	s->wm_set = 2;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C);
	s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C);

	s = &wm->sets[3];
	s->wm_set = 3;
	s->data_urgent = REG_READ(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D);
	s->pte_meta_urgent = REG_READ(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D);
	अगर (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D)) अणु
		s->sr_enter = REG_READ(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D);
		s->sr_निकास = REG_READ(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D);
	पूर्ण
	s->dram_clk_chanage = REG_READ(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D);
पूर्ण

व्योम hubbub1_allow_self_refresh_control(काष्ठा hubbub *hubbub, bool allow)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	/*
	 * DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE = 1 means करो not allow stutter
	 * DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE = 0 means allow stutter
	 */

	REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_VALUE, 0,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE, !allow);
पूर्ण

bool hubbub1_is_allow_self_refresh_enabled(काष्ठा hubbub *hubbub)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uपूर्णांक32_t enable = 0;

	REG_GET(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE, &enable);

	वापस enable ? true : false;
पूर्ण


bool hubbub1_verअगरy_allow_pstate_change_high(
	काष्ठा hubbub *hubbub)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	/* pstate latency is ~20us so अगर we रुको over 40us and pstate allow
	 * still not निश्चितed, we are probably stuck and going to hang
	 *
	 * TODO: Figure out why it takes ~100us on linux
	 * pstate takes around ~100us (up to 200us) on linux. Unknown currently
	 * as to why it takes that दीर्घ on linux
	 */
	स्थिर अचिन्हित पूर्णांक pstate_रुको_समयout_us = 200;
	स्थिर अचिन्हित पूर्णांक pstate_रुको_expected_समयout_us = 180;
	अटल अचिन्हित पूर्णांक max_sampled_pstate_रुको_us; /* data collection */
	अटल bool क्रमced_pstate_allow; /* help with revert wa */

	अचिन्हित पूर्णांक debug_data;
	अचिन्हित पूर्णांक i;

	अगर (क्रमced_pstate_allow) अणु
		/* we hacked to क्रमce pstate allow to prevent hang last समय
		 * we verअगरy_allow_pstate_change_high.  so disable क्रमce
		 * here so we can check status
		 */
		REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_VALUE, 0,
			     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_ENABLE, 0);
		क्रमced_pstate_allow = false;
	पूर्ण

	/* The following table only applies to DCN1 and DCN2,
	 * क्रम newer DCNs, need to consult with HW IP folks to पढ़ो RTL
	 * HUBBUB:DCHUBBUB_TEST_ARB_DEBUG10 DCHUBBUBDEBUGIND:0xB
	 * description
	 * 0:     Pipe0 Plane0 Allow Pstate Change
	 * 1:     Pipe0 Plane1 Allow Pstate Change
	 * 2:     Pipe0 Cursor0 Allow Pstate Change
	 * 3:     Pipe0 Cursor1 Allow Pstate Change
	 * 4:     Pipe1 Plane0 Allow Pstate Change
	 * 5:     Pipe1 Plane1 Allow Pstate Change
	 * 6:     Pipe1 Cursor0 Allow Pstate Change
	 * 7:     Pipe1 Cursor1 Allow Pstate Change
	 * 8:     Pipe2 Plane0 Allow Pstate Change
	 * 9:     Pipe2 Plane1 Allow Pstate Change
	 * 10:    Pipe2 Cursor0 Allow Pstate Change
	 * 11:    Pipe2 Cursor1 Allow Pstate Change
	 * 12:    Pipe3 Plane0 Allow Pstate Change
	 * 13:    Pipe3 Plane1 Allow Pstate Change
	 * 14:    Pipe3 Cursor0 Allow Pstate Change
	 * 15:    Pipe3 Cursor1 Allow Pstate Change
	 * 16:    Pipe4 Plane0 Allow Pstate Change
	 * 17:    Pipe4 Plane1 Allow Pstate Change
	 * 18:    Pipe4 Cursor0 Allow Pstate Change
	 * 19:    Pipe4 Cursor1 Allow Pstate Change
	 * 20:    Pipe5 Plane0 Allow Pstate Change
	 * 21:    Pipe5 Plane1 Allow Pstate Change
	 * 22:    Pipe5 Cursor0 Allow Pstate Change
	 * 23:    Pipe5 Cursor1 Allow Pstate Change
	 * 24:    Pipe6 Plane0 Allow Pstate Change
	 * 25:    Pipe6 Plane1 Allow Pstate Change
	 * 26:    Pipe6 Cursor0 Allow Pstate Change
	 * 27:    Pipe6 Cursor1 Allow Pstate Change
	 * 28:    WB0 Allow Pstate Change
	 * 29:    WB1 Allow Pstate Change
	 * 30:    Arbiter's allow_pstate_change
	 * 31:    SOC pstate change request
	 */

	REG_WRITE(DCHUBBUB_TEST_DEBUG_INDEX, hubbub1->debug_test_index_pstate);

	क्रम (i = 0; i < pstate_रुको_समयout_us; i++) अणु
		debug_data = REG_READ(DCHUBBUB_TEST_DEBUG_DATA);

		अगर (debug_data & (1 << 30)) अणु

			अगर (i > pstate_रुको_expected_समयout_us)
				DC_LOG_WARNING("pstate took longer than expected ~%dus\n",
						i);

			वापस true;
		पूर्ण
		अगर (max_sampled_pstate_रुको_us < i)
			max_sampled_pstate_रुको_us = i;

		udelay(1);
	पूर्ण

	/* क्रमce pstate allow to prevent प्रणाली hang
	 * and अवरोध to debugger to investigate
	 */
	REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
		     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_VALUE, 1,
		     DCHUBBUB_ARB_ALLOW_PSTATE_CHANGE_FORCE_ENABLE, 1);
	क्रमced_pstate_allow = true;

	DC_LOG_WARNING("pstate TEST_DEBUG_DATA: 0x%X\n",
			debug_data);

	वापस false;
पूर्ण

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


व्योम hubbub1_wm_change_req_wa(काष्ठा hubbub *hubbub)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	REG_UPDATE_SEQ_2(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, 0,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, 1);
पूर्ण

bool hubbub1_program_urgent_watermarks(
		काष्ठा hubbub *hubbub,
		काष्ठा dcn_watermark_set *watermarks,
		अचिन्हित पूर्णांक refclk_mhz,
		bool safe_to_lower)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uपूर्णांक32_t prog_wm_value;
	bool wm_pending = false;

	/* Repeat क्रम water mark set A, B, C and D. */
	/* घड़ी state A */
	अगर (safe_to_lower || watermarks->a.urgent_ns > hubbub1->watermarks.a.urgent_ns) अणु
		hubbub1->watermarks.a.urgent_ns = watermarks->a.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->a.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->a.urgent_ns < hubbub1->watermarks.a.urgent_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->a.pte_meta_urgent_ns > hubbub1->watermarks.a.pte_meta_urgent_ns) अणु
		hubbub1->watermarks.a.pte_meta_urgent_ns = watermarks->a.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->a.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.pte_meta_urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->a.pte_meta_urgent_ns < hubbub1->watermarks.a.pte_meta_urgent_ns)
		wm_pending = true;

	/* घड़ी state B */
	अगर (safe_to_lower || watermarks->b.urgent_ns > hubbub1->watermarks.b.urgent_ns) अणु
		hubbub1->watermarks.b.urgent_ns = watermarks->b.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->b.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->b.urgent_ns < hubbub1->watermarks.b.urgent_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->b.pte_meta_urgent_ns > hubbub1->watermarks.b.pte_meta_urgent_ns) अणु
		hubbub1->watermarks.b.pte_meta_urgent_ns = watermarks->b.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->b.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.pte_meta_urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->b.pte_meta_urgent_ns < hubbub1->watermarks.b.pte_meta_urgent_ns)
		wm_pending = true;

	/* घड़ी state C */
	अगर (safe_to_lower || watermarks->c.urgent_ns > hubbub1->watermarks.c.urgent_ns) अणु
		hubbub1->watermarks.c.urgent_ns = watermarks->c.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->c.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->c.urgent_ns < hubbub1->watermarks.c.urgent_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->c.pte_meta_urgent_ns > hubbub1->watermarks.c.pte_meta_urgent_ns) अणु
		hubbub1->watermarks.c.pte_meta_urgent_ns = watermarks->c.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->c.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.pte_meta_urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->c.pte_meta_urgent_ns < hubbub1->watermarks.c.pte_meta_urgent_ns)
		wm_pending = true;

	/* घड़ी state D */
	अगर (safe_to_lower || watermarks->d.urgent_ns > hubbub1->watermarks.d.urgent_ns) अणु
		hubbub1->watermarks.d.urgent_ns = watermarks->d.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->d.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->d.urgent_ns < hubbub1->watermarks.d.urgent_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->d.pte_meta_urgent_ns > hubbub1->watermarks.d.pte_meta_urgent_ns) अणु
		hubbub1->watermarks.d.pte_meta_urgent_ns = watermarks->d.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->d.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.pte_meta_urgent_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->d.pte_meta_urgent_ns < hubbub1->watermarks.d.pte_meta_urgent_ns)
		wm_pending = true;

	वापस wm_pending;
पूर्ण

bool hubbub1_program_stutter_watermarks(
		काष्ठा hubbub *hubbub,
		काष्ठा dcn_watermark_set *watermarks,
		अचिन्हित पूर्णांक refclk_mhz,
		bool safe_to_lower)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uपूर्णांक32_t prog_wm_value;
	bool wm_pending = false;

	/* घड़ी state A */
	अगर (safe_to_lower || watermarks->a.cstate_pstate.cstate_enter_plus_निकास_ns
			> hubbub1->watermarks.a.cstate_pstate.cstate_enter_plus_निकास_ns) अणु
		hubbub1->watermarks.a.cstate_pstate.cstate_enter_plus_निकास_ns =
				watermarks->a.cstate_pstate.cstate_enter_plus_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->a.cstate_pstate.cstate_enter_plus_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A, 0,
				DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.cstate_pstate.cstate_enter_plus_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->a.cstate_pstate.cstate_enter_plus_निकास_ns
			< hubbub1->watermarks.a.cstate_pstate.cstate_enter_plus_निकास_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->a.cstate_pstate.cstate_निकास_ns
			> hubbub1->watermarks.a.cstate_pstate.cstate_निकास_ns) अणु
		hubbub1->watermarks.a.cstate_pstate.cstate_निकास_ns =
				watermarks->a.cstate_pstate.cstate_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->a.cstate_pstate.cstate_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A, 0,
				DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.cstate_pstate.cstate_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->a.cstate_pstate.cstate_निकास_ns
			< hubbub1->watermarks.a.cstate_pstate.cstate_निकास_ns)
		wm_pending = true;

	/* घड़ी state B */
	अगर (safe_to_lower || watermarks->b.cstate_pstate.cstate_enter_plus_निकास_ns
			> hubbub1->watermarks.b.cstate_pstate.cstate_enter_plus_निकास_ns) अणु
		hubbub1->watermarks.b.cstate_pstate.cstate_enter_plus_निकास_ns =
				watermarks->b.cstate_pstate.cstate_enter_plus_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->b.cstate_pstate.cstate_enter_plus_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B, 0,
				DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.cstate_pstate.cstate_enter_plus_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->b.cstate_pstate.cstate_enter_plus_निकास_ns
			< hubbub1->watermarks.b.cstate_pstate.cstate_enter_plus_निकास_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->b.cstate_pstate.cstate_निकास_ns
			> hubbub1->watermarks.b.cstate_pstate.cstate_निकास_ns) अणु
		hubbub1->watermarks.b.cstate_pstate.cstate_निकास_ns =
				watermarks->b.cstate_pstate.cstate_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->b.cstate_pstate.cstate_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B, 0,
				DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.cstate_pstate.cstate_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->b.cstate_pstate.cstate_निकास_ns
			< hubbub1->watermarks.b.cstate_pstate.cstate_निकास_ns)
		wm_pending = true;

	/* घड़ी state C */
	अगर (safe_to_lower || watermarks->c.cstate_pstate.cstate_enter_plus_निकास_ns
			> hubbub1->watermarks.c.cstate_pstate.cstate_enter_plus_निकास_ns) अणु
		hubbub1->watermarks.c.cstate_pstate.cstate_enter_plus_निकास_ns =
				watermarks->c.cstate_pstate.cstate_enter_plus_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->c.cstate_pstate.cstate_enter_plus_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C, 0,
				DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.cstate_pstate.cstate_enter_plus_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->c.cstate_pstate.cstate_enter_plus_निकास_ns
			< hubbub1->watermarks.c.cstate_pstate.cstate_enter_plus_निकास_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->c.cstate_pstate.cstate_निकास_ns
			> hubbub1->watermarks.c.cstate_pstate.cstate_निकास_ns) अणु
		hubbub1->watermarks.c.cstate_pstate.cstate_निकास_ns =
				watermarks->c.cstate_pstate.cstate_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->c.cstate_pstate.cstate_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C, 0,
				DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.cstate_pstate.cstate_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->c.cstate_pstate.cstate_निकास_ns
			< hubbub1->watermarks.c.cstate_pstate.cstate_निकास_ns)
		wm_pending = true;

	/* घड़ी state D */
	अगर (safe_to_lower || watermarks->d.cstate_pstate.cstate_enter_plus_निकास_ns
			> hubbub1->watermarks.d.cstate_pstate.cstate_enter_plus_निकास_ns) अणु
		hubbub1->watermarks.d.cstate_pstate.cstate_enter_plus_निकास_ns =
				watermarks->d.cstate_pstate.cstate_enter_plus_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->d.cstate_pstate.cstate_enter_plus_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D, 0,
				DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.cstate_pstate.cstate_enter_plus_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->d.cstate_pstate.cstate_enter_plus_निकास_ns
			< hubbub1->watermarks.d.cstate_pstate.cstate_enter_plus_निकास_ns)
		wm_pending = true;

	अगर (safe_to_lower || watermarks->d.cstate_pstate.cstate_निकास_ns
			> hubbub1->watermarks.d.cstate_pstate.cstate_निकास_ns) अणु
		hubbub1->watermarks.d.cstate_pstate.cstate_निकास_ns =
				watermarks->d.cstate_pstate.cstate_निकास_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->d.cstate_pstate.cstate_निकास_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D, 0,
				DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.cstate_pstate.cstate_निकास_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->d.cstate_pstate.cstate_निकास_ns
			< hubbub1->watermarks.d.cstate_pstate.cstate_निकास_ns)
		wm_pending = true;

	वापस wm_pending;
पूर्ण

bool hubbub1_program_pstate_watermarks(
		काष्ठा hubbub *hubbub,
		काष्ठा dcn_watermark_set *watermarks,
		अचिन्हित पूर्णांक refclk_mhz,
		bool safe_to_lower)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uपूर्णांक32_t prog_wm_value;
	bool wm_pending = false;

	/* घड़ी state A */
	अगर (safe_to_lower || watermarks->a.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.a.cstate_pstate.pstate_change_ns) अणु
		hubbub1->watermarks.a.cstate_pstate.pstate_change_ns =
				watermarks->a.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->a.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->a.cstate_pstate.pstate_change_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->a.cstate_pstate.pstate_change_ns
			< hubbub1->watermarks.a.cstate_pstate.pstate_change_ns)
		wm_pending = true;

	/* घड़ी state B */
	अगर (safe_to_lower || watermarks->b.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.b.cstate_pstate.pstate_change_ns) अणु
		hubbub1->watermarks.b.cstate_pstate.pstate_change_ns =
				watermarks->b.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->b.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->b.cstate_pstate.pstate_change_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->b.cstate_pstate.pstate_change_ns
			< hubbub1->watermarks.b.cstate_pstate.pstate_change_ns)
		wm_pending = true;

	/* घड़ी state C */
	अगर (safe_to_lower || watermarks->c.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.c.cstate_pstate.pstate_change_ns) अणु
		hubbub1->watermarks.c.cstate_pstate.pstate_change_ns =
				watermarks->c.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->c.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->c.cstate_pstate.pstate_change_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->c.cstate_pstate.pstate_change_ns
			< hubbub1->watermarks.c.cstate_pstate.pstate_change_ns)
		wm_pending = true;

	/* घड़ी state D */
	अगर (safe_to_lower || watermarks->d.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.d.cstate_pstate.pstate_change_ns) अणु
		hubbub1->watermarks.d.cstate_pstate.pstate_change_ns =
				watermarks->d.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->d.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->d.cstate_pstate.pstate_change_ns, prog_wm_value);
	पूर्ण अन्यथा अगर (watermarks->d.cstate_pstate.pstate_change_ns
			< hubbub1->watermarks.d.cstate_pstate.pstate_change_ns)
		wm_pending = true;

	वापस wm_pending;
पूर्ण

bool hubbub1_program_watermarks(
		काष्ठा hubbub *hubbub,
		काष्ठा dcn_watermark_set *watermarks,
		अचिन्हित पूर्णांक refclk_mhz,
		bool safe_to_lower)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	bool wm_pending = false;
	/*
	 * Need to clamp to max of the रेजिस्टर values (i.e. no wrap)
	 * क्रम dcn1, all wm रेजिस्टरs are 21-bit wide
	 */
	अगर (hubbub1_program_urgent_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	अगर (hubbub1_program_stutter_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	अगर (hubbub1_program_pstate_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower))
		wm_pending = true;

	REG_UPDATE(DCHUBBUB_ARB_SAT_LEVEL,
			DCHUBBUB_ARB_SAT_LEVEL, 60 * refclk_mhz);
	REG_UPDATE(DCHUBBUB_ARB_DF_REQ_OUTSTAND,
			DCHUBBUB_ARB_MIN_REQ_OUTSTAND, 68);

	hubbub1_allow_self_refresh_control(hubbub, !hubbub->ctx->dc->debug.disable_stutter);

#अगर 0
	REG_UPDATE_2(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_DONE_INTERRUPT_DISABLE, 1,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, 1);
#पूर्ण_अगर
	वापस wm_pending;
पूर्ण

व्योम hubbub1_update_dchub(
	काष्ठा hubbub *hubbub,
	काष्ठा dchub_init_data *dh_data)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	अगर (REG(DCHUBBUB_SDPIF_FB_TOP) == 0) अणु
		ASSERT(false);
		/*should not come here*/
		वापस;
	पूर्ण
	/* TODO: port code from dal2 */
	चयन (dh_data->fb_mode) अणु
	हाल FRAME_BUFFER_MODE_ZFB_ONLY:
		/*For ZFB हाल need to put DCHUB FB BASE and TOP upside करोwn to indicate ZFB mode*/
		REG_UPDATE(DCHUBBUB_SDPIF_FB_TOP,
				SDPIF_FB_TOP, 0);

		REG_UPDATE(DCHUBBUB_SDPIF_FB_BASE,
				SDPIF_FB_BASE, 0x0FFFF);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 22);
		अवरोध;
	हाल FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL:
		/*Should not touch FB LOCATION (करोne by VBIOS on AsicInit table)*/

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, (dh_data->zfb_mc_base_addr +
						dh_data->zfb_size_in_byte - 1) >> 22);
		अवरोध;
	हाल FRAME_BUFFER_MODE_LOCAL_ONLY:
		/*Should not touch FB LOCATION (करोne by VBIOS on AsicInit table)*/
		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BASE,
				SDPIF_AGP_BASE, 0);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_BOT,
				SDPIF_AGP_BOT, 0X03FFFF);

		REG_UPDATE(DCHUBBUB_SDPIF_AGP_TOP,
				SDPIF_AGP_TOP, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dh_data->dchub_initialzied = true;
	dh_data->dchub_info_valid = false;
पूर्ण

व्योम hubbub1_toggle_watermark_change_req(काष्ठा hubbub *hubbub)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	uपूर्णांक32_t watermark_change_req;

	REG_GET(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, &watermark_change_req);

	अगर (watermark_change_req)
		watermark_change_req = 0;
	अन्यथा
		watermark_change_req = 1;

	REG_UPDATE(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, watermark_change_req);
पूर्ण

व्योम hubbub1_soft_reset(काष्ठा hubbub *hubbub, bool reset)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	uपूर्णांक32_t reset_en = reset ? 1 : 0;

	REG_UPDATE(DCHUBBUB_SOFT_RESET,
			DCHUBBUB_GLOBAL_SOFT_RESET, reset_en);
पूर्ण

अटल bool hubbub1_dcc_support_swizzle(
		क्रमागत swizzle_mode_values swizzle,
		अचिन्हित पूर्णांक bytes_per_element,
		क्रमागत segment_order *segment_order_horz,
		क्रमागत segment_order *segment_order_vert)
अणु
	bool standard_swizzle = false;
	bool display_swizzle = false;

	चयन (swizzle) अणु
	हाल DC_SW_4KB_S:
	हाल DC_SW_64KB_S:
	हाल DC_SW_VAR_S:
	हाल DC_SW_4KB_S_X:
	हाल DC_SW_64KB_S_X:
	हाल DC_SW_VAR_S_X:
		standard_swizzle = true;
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

	अगर (bytes_per_element == 1 && standard_swizzle) अणु
		*segment_order_horz = segment_order__contiguous;
		*segment_order_vert = segment_order__na;
		वापस true;
	पूर्ण
	अगर (bytes_per_element == 2 && standard_swizzle) अणु
		*segment_order_horz = segment_order__non_contiguous;
		*segment_order_vert = segment_order__contiguous;
		वापस true;
	पूर्ण
	अगर (bytes_per_element == 4 && standard_swizzle) अणु
		*segment_order_horz = segment_order__non_contiguous;
		*segment_order_vert = segment_order__contiguous;
		वापस true;
	पूर्ण
	अगर (bytes_per_element == 8 && standard_swizzle) अणु
		*segment_order_horz = segment_order__na;
		*segment_order_vert = segment_order__contiguous;
		वापस true;
	पूर्ण
	अगर (bytes_per_element == 8 && display_swizzle) अणु
		*segment_order_horz = segment_order__contiguous;
		*segment_order_vert = segment_order__non_contiguous;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hubbub1_dcc_support_pixel_क्रमmat(
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		अचिन्हित पूर्णांक *bytes_per_element)
अणु
	/* DML: get_bytes_per_element */
	चयन (क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		*bytes_per_element = 2;
		वापस true;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		*bytes_per_element = 4;
		वापस true;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		*bytes_per_element = 8;
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम hubbub1_get_blk256_size(अचिन्हित पूर्णांक *blk256_width, अचिन्हित पूर्णांक *blk256_height,
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

अटल व्योम hubbub1_det_request_size(
		अचिन्हित पूर्णांक height,
		अचिन्हित पूर्णांक width,
		अचिन्हित पूर्णांक bpe,
		bool *req128_horz_wc,
		bool *req128_vert_wc)
अणु
	अचिन्हित पूर्णांक detile_buf_size = 164 * 1024;  /* 164KB क्रम DCN1.0 */

	अचिन्हित पूर्णांक blk256_height = 0;
	अचिन्हित पूर्णांक blk256_width = 0;
	अचिन्हित पूर्णांक swath_bytes_horz_wc, swath_bytes_vert_wc;

	hubbub1_get_blk256_size(&blk256_width, &blk256_height, bpe);

	swath_bytes_horz_wc = width * blk256_height * bpe;
	swath_bytes_vert_wc = height * blk256_width * bpe;

	*req128_horz_wc = (2 * swath_bytes_horz_wc <= detile_buf_size) ?
			false : /* full 256B request */
			true; /* half 128b request */

	*req128_vert_wc = (2 * swath_bytes_vert_wc <= detile_buf_size) ?
			false : /* full 256B request */
			true; /* half 128b request */
पूर्ण

अटल bool hubbub1_get_dcc_compression_cap(काष्ठा hubbub *hubbub,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	काष्ठा dc *dc = hubbub1->base.ctx->dc;

	/* implement section 1.6.2.1 of DCN1_Programming_Guide.करोcx */
	क्रमागत dcc_control dcc_control;
	अचिन्हित पूर्णांक bpe;
	क्रमागत segment_order segment_order_horz, segment_order_vert;
	bool req128_horz_wc, req128_vert_wc;

	स_रखो(output, 0, माप(*output));

	अगर (dc->debug.disable_dcc == DCC_DISABLE)
		वापस false;

	अगर (!hubbub1->base.funcs->dcc_support_pixel_क्रमmat(input->क्रमmat, &bpe))
		वापस false;

	अगर (!hubbub1->base.funcs->dcc_support_swizzle(input->swizzle_mode, bpe,
			&segment_order_horz, &segment_order_vert))
		वापस false;

	hubbub1_det_request_size(input->surface_size.height,  input->surface_size.width,
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

	अगर (dc->debug.disable_dcc == DCC_HALF_REQ_DISALBE &&
		dcc_control != dcc_control__256_256_xxx)
		वापस false;

	चयन (dcc_control) अणु
	हाल dcc_control__256_256_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 256;
		output->grph.rgb.independent_64b_blks = false;
		अवरोध;
	हाल dcc_control__128_128_xxx:
		output->grph.rgb.max_uncompressed_blk_size = 128;
		output->grph.rgb.max_compressed_blk_size = 128;
		output->grph.rgb.independent_64b_blks = false;
		अवरोध;
	हाल dcc_control__256_64_64:
		output->grph.rgb.max_uncompressed_blk_size = 256;
		output->grph.rgb.max_compressed_blk_size = 64;
		output->grph.rgb.independent_64b_blks = true;
		अवरोध;
	शेष:
		ASSERT(false);
		अवरोध;
	पूर्ण

	output->capable = true;
	output->स्थिर_color_support = false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा hubbub_funcs hubbub1_funcs = अणु
	.update_dchub = hubbub1_update_dchub,
	.dcc_support_swizzle = hubbub1_dcc_support_swizzle,
	.dcc_support_pixel_क्रमmat = hubbub1_dcc_support_pixel_क्रमmat,
	.get_dcc_compression_cap = hubbub1_get_dcc_compression_cap,
	.wm_पढ़ो_state = hubbub1_wm_पढ़ो_state,
	.program_watermarks = hubbub1_program_watermarks,
	.is_allow_self_refresh_enabled = hubbub1_is_allow_self_refresh_enabled,
	.allow_self_refresh_control = hubbub1_allow_self_refresh_control,
पूर्ण;

व्योम hubbub1_स्थिरruct(काष्ठा hubbub *hubbub,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_hubbub_रेजिस्टरs *hubbub_regs,
	स्थिर काष्ठा dcn_hubbub_shअगरt *hubbub_shअगरt,
	स्थिर काष्ठा dcn_hubbub_mask *hubbub_mask)
अणु
	काष्ठा dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);

	hubbub1->base.ctx = ctx;

	hubbub1->base.funcs = &hubbub1_funcs;

	hubbub1->regs = hubbub_regs;
	hubbub1->shअगरts = hubbub_shअगरt;
	hubbub1->masks = hubbub_mask;

	hubbub1->debug_test_index_pstate = 0x7;
	अगर (ctx->dce_version == DCN_VERSION_1_01)
		hubbub1->debug_test_index_pstate = 0xB;
पूर्ण

