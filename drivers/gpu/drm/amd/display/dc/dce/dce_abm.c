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

#समावेश "dce_abm.h"
#समावेश "dm_services.h"
#समावेश "reg_helper.h"
#समावेश "fixed31_32.h"
#समावेश "dc.h"

#समावेश "atom.h"


#घोषणा TO_DCE_ABM(abm)\
	container_of(abm, काष्ठा dce_abm, base)

#घोषणा REG(reg) \
	(abm_dce->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	abm_dce->abm_shअगरt->field_name, abm_dce->abm_mask->field_name

#घोषणा DC_LOGGER \
	abm->ctx->logger
#घोषणा CTX \
	abm_dce->base.ctx

#घोषणा MCP_ABM_LEVEL_SET 0x65
#घोषणा MCP_ABM_PIPE_SET 0x66
#घोषणा MCP_BL_SET 0x67

#घोषणा MCP_DISABLE_ABM_IMMEDIATELY 255

अटल bool dce_abm_set_pipe(काष्ठा abm *abm, uपूर्णांक32_t controller_id, uपूर्णांक32_t panel_inst)
अणु
	काष्ठा dce_abm *abm_dce = TO_DCE_ABM(abm);
	uपूर्णांक32_t rampingBoundary = 0xFFFF;

	अगर (abm->dmcu_is_running == false)
		वापस true;

	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
			1, 80000);

	/* set ramping boundary */
	REG_WRITE(MASTER_COMM_DATA_REG1, rampingBoundary);

	/* setDMCUParam_Pipe */
	REG_UPDATE_2(MASTER_COMM_CMD_REG,
			MASTER_COMM_CMD_REG_BYTE0, MCP_ABM_PIPE_SET,
			MASTER_COMM_CMD_REG_BYTE1, controller_id);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
			1, 80000);

	वापस true;
पूर्ण

अटल व्योम dmcu_set_backlight_level(
	काष्ठा dce_abm *abm_dce,
	uपूर्णांक32_t backlight_pwm_u16_16,
	uपूर्णांक32_t frame_ramp,
	uपूर्णांक32_t controller_id,
	uपूर्णांक32_t panel_id)
अणु
	अचिन्हित पूर्णांक backlight_8_bit = 0;
	uपूर्णांक32_t s2;

	अगर (backlight_pwm_u16_16 & 0x10000)
		// Check क्रम max backlight condition
		backlight_8_bit = 0xFF;
	अन्यथा
		// Take MSB of fractional part since backlight is not max
		backlight_8_bit = (backlight_pwm_u16_16 >> 8) & 0xFF;

	dce_abm_set_pipe(&abm_dce->base, controller_id, panel_id);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT,
			0, 1, 80000);

	/* setDMCUParam_BL */
	REG_UPDATE(BL1_PWM_USER_LEVEL, BL1_PWM_USER_LEVEL, backlight_pwm_u16_16);

	/* ग_लिखो ramp */
	अगर (controller_id == 0)
		frame_ramp = 0;
	REG_WRITE(MASTER_COMM_DATA_REG1, frame_ramp);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, MCP_BL_SET);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* UpdateRequestedBacklightLevel */
	s2 = REG_READ(BIOS_SCRATCH_2);

	s2 &= ~ATOM_S2_CURRENT_BL_LEVEL_MASK;
	backlight_8_bit &= (ATOM_S2_CURRENT_BL_LEVEL_MASK >>
				ATOM_S2_CURRENT_BL_LEVEL_SHIFT);
	s2 |= (backlight_8_bit << ATOM_S2_CURRENT_BL_LEVEL_SHIFT);

	REG_WRITE(BIOS_SCRATCH_2, s2);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT,
			0, 1, 80000);
पूर्ण

अटल व्योम dce_abm_init(काष्ठा abm *abm, uपूर्णांक32_t backlight)
अणु
	काष्ठा dce_abm *abm_dce = TO_DCE_ABM(abm);

	REG_WRITE(DC_ABM1_HG_SAMPLE_RATE, 0x103);
	REG_WRITE(DC_ABM1_HG_SAMPLE_RATE, 0x101);
	REG_WRITE(DC_ABM1_LS_SAMPLE_RATE, 0x103);
	REG_WRITE(DC_ABM1_LS_SAMPLE_RATE, 0x101);
	REG_WRITE(BL1_PWM_BL_UPDATE_SAMPLE_RATE, 0x101);

	REG_SET_3(DC_ABM1_HG_MISC_CTRL, 0,
			ABM1_HG_NUM_OF_BINS_SEL, 0,
			ABM1_HG_VMAX_SEL, 1,
			ABM1_HG_BIN_BITWIDTH_SIZE_SEL, 0);

	REG_SET_3(DC_ABM1_IPCSC_COEFF_SEL, 0,
			ABM1_IPCSC_COEFF_SEL_R, 2,
			ABM1_IPCSC_COEFF_SEL_G, 4,
			ABM1_IPCSC_COEFF_SEL_B, 2);

	REG_UPDATE(BL1_PWM_CURRENT_ABM_LEVEL,
			BL1_PWM_CURRENT_ABM_LEVEL, backlight);

	REG_UPDATE(BL1_PWM_TARGET_ABM_LEVEL,
			BL1_PWM_TARGET_ABM_LEVEL, backlight);

	REG_UPDATE(BL1_PWM_USER_LEVEL,
			BL1_PWM_USER_LEVEL, backlight);

	REG_UPDATE_2(DC_ABM1_LS_MIN_MAX_PIXEL_VALUE_THRES,
			ABM1_LS_MIN_PIXEL_VALUE_THRES, 0,
			ABM1_LS_MAX_PIXEL_VALUE_THRES, 1000);

	REG_SET_3(DC_ABM1_HGLS_REG_READ_PROGRESS, 0,
			ABM1_HG_REG_READ_MISSED_FRAME_CLEAR, 1,
			ABM1_LS_REG_READ_MISSED_FRAME_CLEAR, 1,
			ABM1_BL_REG_READ_MISSED_FRAME_CLEAR, 1);
पूर्ण

अटल अचिन्हित पूर्णांक dce_abm_get_current_backlight(काष्ठा abm *abm)
अणु
	काष्ठा dce_abm *abm_dce = TO_DCE_ABM(abm);
	अचिन्हित पूर्णांक backlight = REG_READ(BL1_PWM_CURRENT_ABM_LEVEL);

	/* वापस backlight in hardware क्रमmat which is अचिन्हित 17 bits, with
	 * 1 bit पूर्णांकeger and 16 bit fractional
	 */
	वापस backlight;
पूर्ण

अटल अचिन्हित पूर्णांक dce_abm_get_target_backlight(काष्ठा abm *abm)
अणु
	काष्ठा dce_abm *abm_dce = TO_DCE_ABM(abm);
	अचिन्हित पूर्णांक backlight = REG_READ(BL1_PWM_TARGET_ABM_LEVEL);

	/* वापस backlight in hardware क्रमmat which is अचिन्हित 17 bits, with
	 * 1 bit पूर्णांकeger and 16 bit fractional
	 */
	वापस backlight;
पूर्ण

अटल bool dce_abm_set_level(काष्ठा abm *abm, uपूर्णांक32_t level)
अणु
	काष्ठा dce_abm *abm_dce = TO_DCE_ABM(abm);

	अगर (abm->dmcu_is_running == false)
		वापस true;

	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
			1, 80000);

	/* setDMCUParam_ABMLevel */
	REG_UPDATE_2(MASTER_COMM_CMD_REG,
			MASTER_COMM_CMD_REG_BYTE0, MCP_ABM_LEVEL_SET,
			MASTER_COMM_CMD_REG_BYTE2, level);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	वापस true;
पूर्ण

अटल bool dce_abm_immediate_disable(काष्ठा abm *abm, uपूर्णांक32_t panel_inst)
अणु
	अगर (abm->dmcu_is_running == false)
		वापस true;

	dce_abm_set_pipe(abm, MCP_DISABLE_ABM_IMMEDIATELY, panel_inst);

	वापस true;
पूर्ण

अटल bool dce_abm_set_backlight_level_pwm(
		काष्ठा abm *abm,
		अचिन्हित पूर्णांक backlight_pwm_u16_16,
		अचिन्हित पूर्णांक frame_ramp,
		अचिन्हित पूर्णांक controller_id,
		अचिन्हित पूर्णांक panel_inst)
अणु
	काष्ठा dce_abm *abm_dce = TO_DCE_ABM(abm);

	DC_LOG_BACKLIGHT("New Backlight level: %d (0x%X)\n",
			backlight_pwm_u16_16, backlight_pwm_u16_16);

	dmcu_set_backlight_level(abm_dce,
			backlight_pwm_u16_16,
			frame_ramp,
			controller_id,
			panel_inst);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा abm_funcs dce_funcs = अणु
	.abm_init = dce_abm_init,
	.set_abm_level = dce_abm_set_level,
	.set_pipe = dce_abm_set_pipe,
	.set_backlight_level_pwm = dce_abm_set_backlight_level_pwm,
	.get_current_backlight = dce_abm_get_current_backlight,
	.get_target_backlight = dce_abm_get_target_backlight,
	.init_abm_config = शून्य,
	.set_abm_immediate_disable = dce_abm_immediate_disable,
पूर्ण;

अटल व्योम dce_abm_स्थिरruct(
	काष्ठा dce_abm *abm_dce,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_abm_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_abm_shअगरt *abm_shअगरt,
	स्थिर काष्ठा dce_abm_mask *abm_mask)
अणु
	काष्ठा abm *base = &abm_dce->base;

	base->ctx = ctx;
	base->funcs = &dce_funcs;
	base->dmcu_is_running = false;

	abm_dce->regs = regs;
	abm_dce->abm_shअगरt = abm_shअगरt;
	abm_dce->abm_mask = abm_mask;
पूर्ण

काष्ठा abm *dce_abm_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_abm_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_abm_shअगरt *abm_shअगरt,
	स्थिर काष्ठा dce_abm_mask *abm_mask)
अणु
	काष्ठा dce_abm *abm_dce = kzalloc(माप(*abm_dce), GFP_ATOMIC);

	अगर (abm_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dce_abm_स्थिरruct(abm_dce, ctx, regs, abm_shअगरt, abm_mask);

	abm_dce->base.funcs = &dce_funcs;

	वापस &abm_dce->base;
पूर्ण

व्योम dce_abm_destroy(काष्ठा abm **abm)
अणु
	काष्ठा dce_abm *abm_dce = TO_DCE_ABM(*abm);

	kमुक्त(abm_dce);
	*abm = शून्य;
पूर्ण
