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

#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dc_dmub_srv.h"
#समावेश "panel_cntl.h"
#समावेश "dce_panel_cntl.h"
#समावेश "atom.h"

#घोषणा TO_DCE_PANEL_CNTL(panel_cntl)\
	container_of(panel_cntl, काष्ठा dce_panel_cntl, base)

#घोषणा CTX \
	dce_panel_cntl->base.ctx

#घोषणा DC_LOGGER \
	dce_panel_cntl->base.ctx->logger

#घोषणा REG(reg)\
	dce_panel_cntl->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dce_panel_cntl->shअगरt->field_name, dce_panel_cntl->mask->field_name

अटल अचिन्हित पूर्णांक dce_get_16_bit_backlight_from_pwm(काष्ठा panel_cntl *panel_cntl)
अणु
	uपूर्णांक64_t current_backlight;
	uपूर्णांक32_t round_result;
	uपूर्णांक32_t bl_period, bl_पूर्णांक_count;
	uपूर्णांक32_t bl_pwm, fractional_duty_cycle_en;
	uपूर्णांक32_t bl_period_mask, bl_pwm_mask;
	काष्ठा dce_panel_cntl *dce_panel_cntl = TO_DCE_PANEL_CNTL(panel_cntl);

	REG_READ(BL_PWM_PERIOD_CNTL);
	REG_GET(BL_PWM_PERIOD_CNTL, BL_PWM_PERIOD, &bl_period);
	REG_GET(BL_PWM_PERIOD_CNTL, BL_PWM_PERIOD_BITCNT, &bl_पूर्णांक_count);

	REG_READ(BL_PWM_CNTL);
	REG_GET(BL_PWM_CNTL, BL_ACTIVE_INT_FRAC_CNT, (uपूर्णांक32_t *)(&bl_pwm));
	REG_GET(BL_PWM_CNTL, BL_PWM_FRACTIONAL_EN, &fractional_duty_cycle_en);

	अगर (bl_पूर्णांक_count == 0)
		bl_पूर्णांक_count = 16;

	bl_period_mask = (1 << bl_पूर्णांक_count) - 1;
	bl_period &= bl_period_mask;

	bl_pwm_mask = bl_period_mask << (16 - bl_पूर्णांक_count);

	अगर (fractional_duty_cycle_en == 0)
		bl_pwm &= bl_pwm_mask;
	अन्यथा
		bl_pwm &= 0xFFFF;

	current_backlight = (uपूर्णांक64_t)bl_pwm << (1 + bl_पूर्णांक_count);

	अगर (bl_period == 0)
		bl_period = 0xFFFF;

	current_backlight = भाग_u64(current_backlight, bl_period);
	current_backlight = (current_backlight + 1) >> 1;

	current_backlight = (uपूर्णांक64_t)(current_backlight) * bl_period;

	round_result = (uपूर्णांक32_t)(current_backlight & 0xFFFFFFFF);

	round_result = (round_result >> (bl_पूर्णांक_count-1)) & 1;

	current_backlight >>= bl_पूर्णांक_count;
	current_backlight += round_result;

	वापस (uपूर्णांक32_t)(current_backlight);
पूर्ण

अटल uपूर्णांक32_t dce_panel_cntl_hw_init(काष्ठा panel_cntl *panel_cntl)
अणु
	काष्ठा dce_panel_cntl *dce_panel_cntl = TO_DCE_PANEL_CNTL(panel_cntl);
	uपूर्णांक32_t value;
	uपूर्णांक32_t current_backlight;

	/* It must not be 0, so we have to restore them
	 * Bios bug w/a - period resets to zero,
	 * restoring to cache values which is always correct
	 */
	REG_GET(BL_PWM_CNTL, BL_ACTIVE_INT_FRAC_CNT, &value);

	अगर (panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_CNTL != 0) अणु
		REG_WRITE(BL_PWM_CNTL,
				panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_CNTL);
		REG_WRITE(BL_PWM_CNTL2,
				panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_CNTL2);
		REG_WRITE(BL_PWM_PERIOD_CNTL,
				panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_PERIOD_CNTL);
		REG_UPDATE(PWRSEQ_REF_DIV,
			BL_PWM_REF_DIV,
			panel_cntl->stored_backlight_रेजिस्टरs.LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV);
	पूर्ण अन्यथा अगर ((value != 0) && (value != 1)) अणु
		panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_CNTL =
				REG_READ(BL_PWM_CNTL);
		panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_CNTL2 =
				REG_READ(BL_PWM_CNTL2);
		panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_PERIOD_CNTL =
				REG_READ(BL_PWM_PERIOD_CNTL);

		REG_GET(PWRSEQ_REF_DIV, BL_PWM_REF_DIV,
				&panel_cntl->stored_backlight_रेजिस्टरs.LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV);
	पूर्ण अन्यथा अणु
		/* TODO: Note: This should not really happen since VBIOS
		 * should have initialized PWM रेजिस्टरs on boot.
		 */
		REG_WRITE(BL_PWM_CNTL, 0x8000FA00);
		REG_WRITE(BL_PWM_PERIOD_CNTL, 0x000C0FA0);
	पूर्ण

	// Have driver take backlight control
	// TakeBacklightControl(true)
	value = REG_READ(BIOS_SCRATCH_2);
	value |= ATOM_S2_VRI_BRIGHT_ENABLE;
	REG_WRITE(BIOS_SCRATCH_2, value);

	// Enable the backlight output
	REG_UPDATE(BL_PWM_CNTL, BL_PWM_EN, 1);

	// Unlock group 2 backlight रेजिस्टरs
	REG_UPDATE(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_REG_LOCK, 0);

	current_backlight = dce_get_16_bit_backlight_from_pwm(panel_cntl);

	वापस current_backlight;
पूर्ण

अटल bool dce_is_panel_backlight_on(काष्ठा panel_cntl *panel_cntl)
अणु
	काष्ठा dce_panel_cntl *dce_panel_cntl = TO_DCE_PANEL_CNTL(panel_cntl);
	uपूर्णांक32_t blon, blon_ovrd, pwrseq_target_state;

	REG_GET_2(PWRSEQ_CNTL, LVTMA_BLON, &blon, LVTMA_BLON_OVRD, &blon_ovrd);
	REG_GET(PWRSEQ_CNTL, LVTMA_PWRSEQ_TARGET_STATE, &pwrseq_target_state);

	अगर (blon_ovrd)
		वापस blon;
	अन्यथा
		वापस pwrseq_target_state;
पूर्ण

अटल bool dce_is_panel_घातered_on(काष्ठा panel_cntl *panel_cntl)
अणु
	काष्ठा dce_panel_cntl *dce_panel_cntl = TO_DCE_PANEL_CNTL(panel_cntl);
	uपूर्णांक32_t pwr_seq_state, dig_on, dig_on_ovrd;

	REG_GET(PWRSEQ_STATE, LVTMA_PWRSEQ_TARGET_STATE_R, &pwr_seq_state);

	REG_GET_2(PWRSEQ_CNTL, LVTMA_DIGON, &dig_on, LVTMA_DIGON_OVRD, &dig_on_ovrd);

	वापस (pwr_seq_state == 1) || (dig_on == 1 && dig_on_ovrd == 1);
पूर्ण

अटल व्योम dce_store_backlight_level(काष्ठा panel_cntl *panel_cntl)
अणु
	काष्ठा dce_panel_cntl *dce_panel_cntl = TO_DCE_PANEL_CNTL(panel_cntl);

	panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_CNTL =
		REG_READ(BL_PWM_CNTL);
	panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_CNTL2 =
		REG_READ(BL_PWM_CNTL2);
	panel_cntl->stored_backlight_रेजिस्टरs.BL_PWM_PERIOD_CNTL =
		REG_READ(BL_PWM_PERIOD_CNTL);

	REG_GET(PWRSEQ_REF_DIV, BL_PWM_REF_DIV,
		&panel_cntl->stored_backlight_रेजिस्टरs.LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV);
पूर्ण

अटल व्योम dce_driver_set_backlight(काष्ठा panel_cntl *panel_cntl,
		uपूर्णांक32_t backlight_pwm_u16_16)
अणु
	uपूर्णांक32_t backlight_16bit;
	uपूर्णांक32_t masked_pwm_period;
	uपूर्णांक8_t bit_count;
	uपूर्णांक64_t active_duty_cycle;
	uपूर्णांक32_t pwm_period_bitcnt;
	काष्ठा dce_panel_cntl *dce_panel_cntl = TO_DCE_PANEL_CNTL(panel_cntl);

	/*
	 * 1. Find  16 bit backlight active duty cycle, where 0 <= backlight
	 * active duty cycle <= backlight period
	 */

	/* 1.1 Apply biपंचांगask क्रम backlight period value based on value of BITCNT
	 */
	REG_GET_2(BL_PWM_PERIOD_CNTL,
			BL_PWM_PERIOD_BITCNT, &pwm_period_bitcnt,
			BL_PWM_PERIOD, &masked_pwm_period);

	अगर (pwm_period_bitcnt == 0)
		bit_count = 16;
	अन्यथा
		bit_count = pwm_period_bitcnt;

	/* e.g. maskedPwmPeriod = 0x24 when bitCount is 6 */
	masked_pwm_period = masked_pwm_period & ((1 << bit_count) - 1);

	/* 1.2 Calculate पूर्णांकeger active duty cycle required upper 16 bits
	 * contain पूर्णांकeger component, lower 16 bits contain fractional component
	 * of active duty cycle e.g. 0x21BDC0 = 0xEFF0 * 0x24
	 */
	active_duty_cycle = backlight_pwm_u16_16 * masked_pwm_period;

	/* 1.3 Calculate 16 bit active duty cycle from पूर्णांकeger and fractional
	 * components shअगरt by bitCount then mask 16 bits and add rounding bit
	 * from MSB of fraction e.g. 0x86F7 = ((0x21BDC0 >> 6) & 0xFFF) + 0
	 */
	backlight_16bit = active_duty_cycle >> bit_count;
	backlight_16bit &= 0xFFFF;
	backlight_16bit += (active_duty_cycle >> (bit_count - 1)) & 0x1;

	/*
	 * 2. Program रेजिस्टर with updated value
	 */

	/* 2.1 Lock group 2 backlight रेजिस्टरs */

	REG_UPDATE_2(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_IGNORE_MASTER_LOCK_EN, 1,
			BL_PWM_GRP1_REG_LOCK, 1);

	// 2.2 Write new active duty cycle
	REG_UPDATE(BL_PWM_CNTL, BL_ACTIVE_INT_FRAC_CNT, backlight_16bit);

	/* 2.3 Unlock group 2 backlight रेजिस्टरs */
	REG_UPDATE(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_REG_LOCK, 0);

	/* 3 Wait क्रम pending bit to be cleared */
	REG_WAIT(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_REG_UPDATE_PENDING, 0,
			1, 10000);
पूर्ण

अटल व्योम dce_panel_cntl_destroy(काष्ठा panel_cntl **panel_cntl)
अणु
	काष्ठा dce_panel_cntl *dce_panel_cntl = TO_DCE_PANEL_CNTL(*panel_cntl);

	kमुक्त(dce_panel_cntl);
	*panel_cntl = शून्य;
पूर्ण

अटल स्थिर काष्ठा panel_cntl_funcs dce_link_panel_cntl_funcs = अणु
	.destroy = dce_panel_cntl_destroy,
	.hw_init = dce_panel_cntl_hw_init,
	.is_panel_backlight_on = dce_is_panel_backlight_on,
	.is_panel_घातered_on = dce_is_panel_घातered_on,
	.store_backlight_level = dce_store_backlight_level,
	.driver_set_backlight = dce_driver_set_backlight,
	.get_current_backlight = dce_get_16_bit_backlight_from_pwm,
पूर्ण;

व्योम dce_panel_cntl_स्थिरruct(
	काष्ठा dce_panel_cntl *dce_panel_cntl,
	स्थिर काष्ठा panel_cntl_init_data *init_data,
	स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_panel_cntl_shअगरt *shअगरt,
	स्थिर काष्ठा dce_panel_cntl_mask *mask)
अणु
	काष्ठा panel_cntl *base = &dce_panel_cntl->base;

	base->stored_backlight_रेजिस्टरs.BL_PWM_CNTL = 0;
	base->stored_backlight_रेजिस्टरs.BL_PWM_CNTL2 = 0;
	base->stored_backlight_रेजिस्टरs.BL_PWM_PERIOD_CNTL = 0;
	base->stored_backlight_रेजिस्टरs.LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV = 0;

	dce_panel_cntl->regs = regs;
	dce_panel_cntl->shअगरt = shअगरt;
	dce_panel_cntl->mask = mask;

	dce_panel_cntl->base.funcs = &dce_link_panel_cntl_funcs;
	dce_panel_cntl->base.ctx = init_data->ctx;
	dce_panel_cntl->base.inst = init_data->inst;
पूर्ण
