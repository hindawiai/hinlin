<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#समावेश "dmub_abm.h"
#समावेश "dce_abm.h"
#समावेश "dc.h"
#समावेश "dc_dmub_srv.h"
#समावेश "dmub/dmub_srv.h"
#समावेश "core_types.h"
#समावेश "dm_services.h"
#समावेश "reg_helper.h"
#समावेश "fixed31_32.h"

#समावेश "atom.h"

#घोषणा TO_DMUB_ABM(abm)\
	container_of(abm, काष्ठा dce_abm, base)

#घोषणा REG(reg) \
	(dce_abm->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dce_abm->abm_shअगरt->field_name, dce_abm->abm_mask->field_name

#घोषणा CTX \
	dce_abm->base.ctx

#घोषणा DISABLE_ABM_IMMEDIATELY 255



अटल व्योम dmub_abm_enable_fractional_pwm(काष्ठा dc_context *dc)
अणु
	जोड़ dmub_rb_cmd cmd;
	uपूर्णांक32_t fractional_pwm = (dc->dc->config.disable_fractional_pwm == false) ? 1 : 0;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.abm_set_pwm_frac.header.type = DMUB_CMD__ABM;
	cmd.abm_set_pwm_frac.header.sub_type = DMUB_CMD__ABM_SET_PWM_FRAC;
	cmd.abm_set_pwm_frac.abm_set_pwm_frac_data.fractional_pwm = fractional_pwm;
	cmd.abm_set_pwm_frac.header.payload_bytes = माप(काष्ठा dmub_cmd_abm_set_pwm_frac_data);

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);
पूर्ण

अटल व्योम dmub_abm_init(काष्ठा abm *abm, uपूर्णांक32_t backlight)
अणु
	काष्ठा dce_abm *dce_abm = TO_DMUB_ABM(abm);

	REG_WRITE(DC_ABM1_HG_SAMPLE_RATE, 0x3);
	REG_WRITE(DC_ABM1_HG_SAMPLE_RATE, 0x1);
	REG_WRITE(DC_ABM1_LS_SAMPLE_RATE, 0x3);
	REG_WRITE(DC_ABM1_LS_SAMPLE_RATE, 0x1);
	REG_WRITE(BL1_PWM_BL_UPDATE_SAMPLE_RATE, 0x1);

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

	dmub_abm_enable_fractional_pwm(abm->ctx);
पूर्ण

अटल अचिन्हित पूर्णांक dmub_abm_get_current_backlight(काष्ठा abm *abm)
अणु
	काष्ठा dce_abm *dce_abm = TO_DMUB_ABM(abm);
	अचिन्हित पूर्णांक backlight = REG_READ(BL1_PWM_CURRENT_ABM_LEVEL);

	/* वापस backlight in hardware क्रमmat which is अचिन्हित 17 bits, with
	 * 1 bit पूर्णांकeger and 16 bit fractional
	 */
	वापस backlight;
पूर्ण

अटल अचिन्हित पूर्णांक dmub_abm_get_target_backlight(काष्ठा abm *abm)
अणु
	काष्ठा dce_abm *dce_abm = TO_DMUB_ABM(abm);
	अचिन्हित पूर्णांक backlight = REG_READ(BL1_PWM_TARGET_ABM_LEVEL);

	/* वापस backlight in hardware क्रमmat which is अचिन्हित 17 bits, with
	 * 1 bit पूर्णांकeger and 16 bit fractional
	 */
	वापस backlight;
पूर्ण

अटल bool dmub_abm_set_level(काष्ठा abm *abm, uपूर्णांक32_t level)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = abm->ctx;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.abm_set_level.header.type = DMUB_CMD__ABM;
	cmd.abm_set_level.header.sub_type = DMUB_CMD__ABM_SET_LEVEL;
	cmd.abm_set_level.abm_set_level_data.level = level;
	cmd.abm_set_level.header.payload_bytes = माप(काष्ठा dmub_cmd_abm_set_level_data);

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);

	वापस true;
पूर्ण

अटल bool dmub_abm_init_config(काष्ठा abm *abm,
	स्थिर अक्षर *src,
	अचिन्हित पूर्णांक bytes)
अणु
	जोड़ dmub_rb_cmd cmd;
	काष्ठा dc_context *dc = abm->ctx;

	// TODO: Optimize by only पढ़ोing back final 4 bytes
	dmub_flush_buffer_mem(&dc->dmub_srv->dmub->scratch_mem_fb);

	// Copy iramtable पूर्णांकo cw7
	स_नकल(dc->dmub_srv->dmub->scratch_mem_fb.cpu_addr, (व्योम *)src, bytes);

	स_रखो(&cmd, 0, माप(cmd));
	// Fw will copy from cw7 to fw_state
	cmd.abm_init_config.header.type = DMUB_CMD__ABM;
	cmd.abm_init_config.header.sub_type = DMUB_CMD__ABM_INIT_CONFIG;
	cmd.abm_init_config.abm_init_config_data.src.quad_part = dc->dmub_srv->dmub->scratch_mem_fb.gpu_addr;
	cmd.abm_init_config.abm_init_config_data.bytes = bytes;
	cmd.abm_init_config.header.payload_bytes = माप(काष्ठा dmub_cmd_abm_init_config_data);

	dc_dmub_srv_cmd_queue(dc->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->dmub_srv);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा abm_funcs abm_funcs = अणु
	.abm_init = dmub_abm_init,
	.set_abm_level = dmub_abm_set_level,
	.get_current_backlight = dmub_abm_get_current_backlight,
	.get_target_backlight = dmub_abm_get_target_backlight,
	.init_abm_config = dmub_abm_init_config,
पूर्ण;

अटल व्योम dmub_abm_स्थिरruct(
	काष्ठा dce_abm *abm_dce,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_abm_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_abm_shअगरt *abm_shअगरt,
	स्थिर काष्ठा dce_abm_mask *abm_mask)
अणु
	काष्ठा abm *base = &abm_dce->base;

	base->ctx = ctx;
	base->funcs = &abm_funcs;
	base->dmcu_is_running = false;

	abm_dce->regs = regs;
	abm_dce->abm_shअगरt = abm_shअगरt;
	abm_dce->abm_mask = abm_mask;
पूर्ण

काष्ठा abm *dmub_abm_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_abm_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_abm_shअगरt *abm_shअगरt,
	स्थिर काष्ठा dce_abm_mask *abm_mask)
अणु
	काष्ठा dce_abm *abm_dce = kzalloc(माप(*abm_dce), GFP_KERNEL);

	अगर (abm_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dmub_abm_स्थिरruct(abm_dce, ctx, regs, abm_shअगरt, abm_mask);

	वापस &abm_dce->base;
पूर्ण

व्योम dmub_abm_destroy(काष्ठा abm **abm)
अणु
	काष्ठा dce_abm *abm_dce = TO_DMUB_ABM(*abm);

	kमुक्त(abm_dce);
	*abm = शून्य;
पूर्ण
