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

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "core_types.h"
#समावेश "link_encoder.h"
#समावेश "dce_dmcu.h"
#समावेश "dm_services.h"
#समावेश "reg_helper.h"
#समावेश "fixed31_32.h"
#समावेश "dc.h"

#घोषणा TO_DCE_DMCU(dmcu)\
	container_of(dmcu, काष्ठा dce_dmcu, base)

#घोषणा REG(reg) \
	(dmcu_dce->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dmcu_dce->dmcu_shअगरt->field_name, dmcu_dce->dmcu_mask->field_name

#घोषणा CTX \
	dmcu_dce->base.ctx

/* PSR related commands */
#घोषणा PSR_ENABLE 0x20
#घोषणा PSR_EXIT 0x21
#घोषणा PSR_SET 0x23
#घोषणा PSR_SET_WAITLOOP 0x31
#घोषणा MCP_INIT_DMCU 0x88
#घोषणा MCP_INIT_IRAM 0x89
#घोषणा MCP_SYNC_PHY_LOCK 0x90
#घोषणा MCP_SYNC_PHY_UNLOCK 0x91
#घोषणा MCP_BL_SET_PWM_FRAC 0x6A  /* Enable or disable Fractional PWM */
#घोषणा CRC_WIN_NOTIFY 0x92
#घोषणा CRC_STOP_UPDATE 0x93
#घोषणा MCP_SEND_EDID_CEA 0xA0
#घोषणा EDID_CEA_CMD_ACK 1
#घोषणा EDID_CEA_CMD_NACK 2
#घोषणा MASTER_COMM_CNTL_REG__MASTER_COMM_INTERRUPT_MASK   0x00000001L

// PSP FW version
#घोषणा mmMP0_SMN_C2PMSG_58				0x1607A

//Register access policy version
#घोषणा mmMP0_SMN_C2PMSG_91				0x1609B

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल स्थिर uपूर्णांक32_t abm_gain_stepsize = 0x0060;
#पूर्ण_अगर

अटल bool dce_dmcu_init(काष्ठा dmcu *dmcu)
अणु
	// Do nothing
	वापस true;
पूर्ण

अटल bool dce_dmcu_load_iram(काष्ठा dmcu *dmcu,
		अचिन्हित पूर्णांक start_offset,
		स्थिर अक्षर *src,
		अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	अचिन्हित पूर्णांक count = 0;

	/* Enable ग_लिखो access to IRAM */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 1,
			IRAM_WR_ADDR_AUTO_INC, 1);

	REG_WAIT(DCI_MEM_PWR_STATUS, DMCU_IRAM_MEM_PWR_STATE, 0, 2, 10);

	REG_WRITE(DMCU_IRAM_WR_CTRL, start_offset);

	क्रम (count = 0; count < bytes; count++)
		REG_WRITE(DMCU_IRAM_WR_DATA, src[count]);

	/* Disable ग_लिखो access to IRAM to allow dynamic sleep state */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 0,
			IRAM_WR_ADDR_AUTO_INC, 0);

	वापस true;
पूर्ण

अटल व्योम dce_get_dmcu_psr_state(काष्ठा dmcu *dmcu, क्रमागत dc_psr_state *state)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	uपूर्णांक32_t psr_state_offset = 0xf0;

	/* Enable ग_लिखो access to IRAM */
	REG_UPDATE(DMCU_RAM_ACCESS_CTRL, IRAM_HOST_ACCESS_EN, 1);

	REG_WAIT(DCI_MEM_PWR_STATUS, DMCU_IRAM_MEM_PWR_STATE, 0, 2, 10);

	/* Write address to IRAM_RD_ADDR in DMCU_IRAM_RD_CTRL */
	REG_WRITE(DMCU_IRAM_RD_CTRL, psr_state_offset);

	/* Read data from IRAM_RD_DATA in DMCU_IRAM_RD_DATA*/
	*state = (क्रमागत dc_psr_state)REG_READ(DMCU_IRAM_RD_DATA);

	/* Disable ग_लिखो access to IRAM after finished using IRAM
	 * in order to allow dynamic sleep state
	 */
	REG_UPDATE(DMCU_RAM_ACCESS_CTRL, IRAM_HOST_ACCESS_EN, 0);
पूर्ण

अटल व्योम dce_dmcu_set_psr_enable(काष्ठा dmcu *dmcu, bool enable, bool रुको)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	अचिन्हित पूर्णांक dmcu_max_retry_on_रुको_reg_पढ़ोy = 801;
	अचिन्हित पूर्णांक dmcu_रुको_reg_पढ़ोy_पूर्णांकerval = 100;

	अचिन्हित पूर्णांक retryCount;
	क्रमागत dc_psr_state state = PSR_STATE0;

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
				dmcu_रुको_reg_पढ़ोy_पूर्णांकerval,
				dmcu_max_retry_on_रुको_reg_पढ़ोy);

	/* setDMCUParam_Cmd */
	अगर (enable)
		REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
				PSR_ENABLE);
	अन्यथा
		REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
				PSR_EXIT);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);
	अगर (रुको == true) अणु
		क्रम (retryCount = 0; retryCount <= 100; retryCount++) अणु
			dce_get_dmcu_psr_state(dmcu, &state);
			अगर (enable) अणु
				अगर (state != PSR_STATE0)
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (state == PSR_STATE0)
					अवरोध;
			पूर्ण
			udelay(10);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool dce_dmcu_setup_psr(काष्ठा dmcu *dmcu,
		काष्ठा dc_link *link,
		काष्ठा psr_context *psr_context)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	अचिन्हित पूर्णांक dmcu_max_retry_on_रुको_reg_पढ़ोy = 801;
	अचिन्हित पूर्णांक dmcu_रुको_reg_पढ़ोy_पूर्णांकerval = 100;

	जोड़ dce_dmcu_psr_config_data_reg1 masterCmdData1;
	जोड़ dce_dmcu_psr_config_data_reg2 masterCmdData2;
	जोड़ dce_dmcu_psr_config_data_reg3 masterCmdData3;

	link->link_enc->funcs->psr_program_dp_dphy_fast_training(link->link_enc,
			psr_context->psrExitLinkTrainingRequired);

	/* Enable अटल screen पूर्णांकerrupts क्रम PSR supported display */
	/* Disable the पूर्णांकerrupt coming from other displays. */
	REG_UPDATE_4(DMCU_INTERRUPT_TO_UC_EN_MASK,
			STATIC_SCREEN1_INT_TO_UC_EN, 0,
			STATIC_SCREEN2_INT_TO_UC_EN, 0,
			STATIC_SCREEN3_INT_TO_UC_EN, 0,
			STATIC_SCREEN4_INT_TO_UC_EN, 0);

	चयन (psr_context->controllerId) अणु
	/* Driver uses हाल 1 क्रम unconfigured */
	हाल 1:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN1_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 2:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN2_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 3:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN3_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 4:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN4_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 5:
		/* CZ/NL only has 4 CRTC!!
		 * really valid.
		 * There is no पूर्णांकerrupt enable mask क्रम these instances.
		 */
		अवरोध;
	हाल 6:
		/* CZ/NL only has 4 CRTC!!
		 * These are here because they are defined in HW regspec,
		 * but not really valid. There is no पूर्णांकerrupt enable mask
		 * क्रम these instances.
		 */
		अवरोध;
	शेष:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN1_INT_TO_UC_EN, 1);
		अवरोध;
	पूर्ण

	link->link_enc->funcs->psr_program_secondary_packet(link->link_enc,
			psr_context->sdpTransmitLineNumDeadline);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
					dmcu_रुको_reg_पढ़ोy_पूर्णांकerval,
					dmcu_max_retry_on_रुको_reg_पढ़ोy);

	/* setDMCUParam_PSRHostConfigData */
	masterCmdData1.u32All = 0;
	masterCmdData1.bits.समयhyst_frames = psr_context->समयhyst_frames;
	masterCmdData1.bits.hyst_lines = psr_context->hyst_lines;
	masterCmdData1.bits.rfb_update_स्वतः_en =
			psr_context->rfb_update_स्वतः_en;
	masterCmdData1.bits.dp_port_num = psr_context->transmitterId;
	masterCmdData1.bits.dcp_sel = psr_context->controllerId;
	masterCmdData1.bits.phy_type  = psr_context->phyType;
	masterCmdData1.bits.frame_cap_ind =
			psr_context->psrFrameCaptureIndicationReq;
	masterCmdData1.bits.aux_chan = psr_context->channel;
	masterCmdData1.bits.aux_repeat = psr_context->aux_repeats;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1),
					masterCmdData1.u32All);

	masterCmdData2.u32All = 0;
	masterCmdData2.bits.dig_fe = psr_context->engineId;
	masterCmdData2.bits.dig_be = psr_context->transmitterId;
	masterCmdData2.bits.skip_रुको_क्रम_pll_lock =
			psr_context->skipPsrWaitForPllLock;
	masterCmdData2.bits.frame_delay = psr_context->frame_delay;
	masterCmdData2.bits.smu_phy_id = psr_context->smuPhyId;
	masterCmdData2.bits.num_of_controllers =
			psr_context->numberOfControllers;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG2),
			masterCmdData2.u32All);

	masterCmdData3.u32All = 0;
	masterCmdData3.bits.psr_level = psr_context->psr_level.u32all;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG3),
			masterCmdData3.u32All);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG,
			MASTER_COMM_CMD_REG_BYTE0, PSR_SET);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	वापस true;
पूर्ण

अटल bool dce_is_dmcu_initialized(काष्ठा dmcu *dmcu)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	अचिन्हित पूर्णांक dmcu_uc_reset;

	/* microcontroller is not running */
	REG_GET(DMCU_STATUS, UC_IN_RESET, &dmcu_uc_reset);

	/* DMCU is not running */
	अगर (dmcu_uc_reset)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम dce_psr_रुको_loop(
	काष्ठा dmcu *dmcu,
	अचिन्हित पूर्णांक रुको_loop_number)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	जोड़ dce_dmcu_psr_config_data_रुको_loop_reg1 masterCmdData1;

	अगर (dmcu->cached_रुको_loop_number == रुको_loop_number)
		वापस;

	/* DMCU is not running */
	अगर (!dce_is_dmcu_initialized(dmcu))
		वापस;

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	masterCmdData1.u32 = 0;
	masterCmdData1.bits.रुको_loop = रुको_loop_number;
	dmcu->cached_रुको_loop_number = रुको_loop_number;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1), masterCmdData1.u32);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, PSR_SET_WAITLOOP);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);
पूर्ण

अटल व्योम dce_get_psr_रुको_loop(
		काष्ठा dmcu *dmcu, अचिन्हित पूर्णांक *psr_रुको_loop_number)
अणु
	*psr_रुको_loop_number = dmcu->cached_रुको_loop_number;
	वापस;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल व्योम dcn10_get_dmcu_version(काष्ठा dmcu *dmcu)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	uपूर्णांक32_t dmcu_version_offset = 0xf1;

	/* Enable ग_लिखो access to IRAM */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 1,
			IRAM_RD_ADDR_AUTO_INC, 1);

	REG_WAIT(DMU_MEM_PWR_CNTL, DMCU_IRAM_MEM_PWR_STATE, 0, 2, 10);

	/* Write address to IRAM_RD_ADDR and पढ़ो from DATA रेजिस्टर */
	REG_WRITE(DMCU_IRAM_RD_CTRL, dmcu_version_offset);
	dmcu->dmcu_version.पूर्णांकerface_version = REG_READ(DMCU_IRAM_RD_DATA);
	dmcu->dmcu_version.abm_version = REG_READ(DMCU_IRAM_RD_DATA);
	dmcu->dmcu_version.psr_version = REG_READ(DMCU_IRAM_RD_DATA);
	dmcu->dmcu_version.build_version = ((REG_READ(DMCU_IRAM_RD_DATA) << 8) |
						REG_READ(DMCU_IRAM_RD_DATA));

	/* Disable ग_लिखो access to IRAM to allow dynamic sleep state */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 0,
			IRAM_RD_ADDR_AUTO_INC, 0);
पूर्ण

अटल व्योम dcn10_dmcu_enable_fractional_pwm(काष्ठा dmcu *dmcu,
		uपूर्णांक32_t fractional_pwm)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* Wait until microcontroller is पढ़ोy to process पूर्णांकerrupt */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 100, 800);

	/* Set PWM fractional enable/disable */
	REG_WRITE(MASTER_COMM_DATA_REG1, fractional_pwm);

	/* Set command to enable or disable fractional PWM microcontroller */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
			MCP_BL_SET_PWM_FRAC);

	/* Notअगरy microcontroller of new command */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* Ensure command has been executed beक्रमe continuing */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 100, 800);
पूर्ण

अटल bool dcn10_dmcu_init(काष्ठा dmcu *dmcu)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	स्थिर काष्ठा dc_config *config = &dmcu->ctx->dc->config;
	bool status = false;
	काष्ठा dc_context *ctx = dmcu->ctx;
	अचिन्हित पूर्णांक i;
	//  5 4 3 2 1 0
	//  F E D C B A - bit 0 is A, bit 5 is F
	अचिन्हित पूर्णांक tx_पूर्णांकerrupt_mask = 0;

	PERF_TRACE();
	/*  Definition of DC_DMCU_SCRATCH
	 *  0 : firmare not loaded
	 *  1 : PSP load DMCU FW but not initialized
	 *  2 : Firmware alपढ़ोy initialized
	 */
	dmcu->dmcu_state = REG_READ(DC_DMCU_SCRATCH);

	क्रम (i = 0; i < ctx->dc->link_count; i++) अणु
		अगर (ctx->dc->links[i]->link_enc->features.flags.bits.DP_IS_USB_C) अणु
			अगर (ctx->dc->links[i]->link_enc->transmitter >= TRANSMITTER_UNIPHY_A &&
					ctx->dc->links[i]->link_enc->transmitter <= TRANSMITTER_UNIPHY_F) अणु
				tx_पूर्णांकerrupt_mask |= 1 << ctx->dc->links[i]->link_enc->transmitter;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (dmcu->dmcu_state) अणु
	हाल DMCU_UNLOADED:
		status = false;
		अवरोध;
	हाल DMCU_LOADED_UNINITIALIZED:
		/* Wait until microcontroller is पढ़ोy to process पूर्णांकerrupt */
		REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 100, 800);

		/* Set initialized ramping boundary value */
		REG_WRITE(MASTER_COMM_DATA_REG1, 0xFFFF);

		/* Set backlight ramping stepsize */
		REG_WRITE(MASTER_COMM_DATA_REG2, abm_gain_stepsize);

		REG_WRITE(MASTER_COMM_DATA_REG3, tx_पूर्णांकerrupt_mask);

		/* Set command to initialize microcontroller */
		REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
			MCP_INIT_DMCU);

		/* Notअगरy microcontroller of new command */
		REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

		/* Ensure command has been executed beक्रमe continuing */
		REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 100, 800);

		// Check state is initialized
		dmcu->dmcu_state = REG_READ(DC_DMCU_SCRATCH);

		// If microcontroller is not in running state, fail
		अगर (dmcu->dmcu_state == DMCU_RUNNING) अणु
			/* Retrieve and cache the DMCU firmware version. */
			dcn10_get_dmcu_version(dmcu);

			/* Initialize DMCU to use fractional PWM or not */
			dcn10_dmcu_enable_fractional_pwm(dmcu,
				(config->disable_fractional_pwm == false) ? 1 : 0);
			status = true;
		पूर्ण अन्यथा अणु
			status = false;
		पूर्ण

		अवरोध;
	हाल DMCU_RUNNING:
		status = true;
		अवरोध;
	शेष:
		status = false;
		अवरोध;
	पूर्ण

	PERF_TRACE();
	वापस status;
पूर्ण

अटल bool dcn21_dmcu_init(काष्ठा dmcu *dmcu)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	uपूर्णांक32_t dmcub_psp_version = REG_READ(DMCUB_SCRATCH15);

	अगर (dmcu->स्वतः_load_dmcu && dmcub_psp_version == 0) अणु
		वापस false;
	पूर्ण

	वापस dcn10_dmcu_init(dmcu);
पूर्ण

अटल bool dcn10_dmcu_load_iram(काष्ठा dmcu *dmcu,
		अचिन्हित पूर्णांक start_offset,
		स्थिर अक्षर *src,
		अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	अचिन्हित पूर्णांक count = 0;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस false;

	/* Enable ग_लिखो access to IRAM */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 1,
			IRAM_WR_ADDR_AUTO_INC, 1);

	REG_WAIT(DMU_MEM_PWR_CNTL, DMCU_IRAM_MEM_PWR_STATE, 0, 2, 10);

	REG_WRITE(DMCU_IRAM_WR_CTRL, start_offset);

	क्रम (count = 0; count < bytes; count++)
		REG_WRITE(DMCU_IRAM_WR_DATA, src[count]);

	/* Disable ग_लिखो access to IRAM to allow dynamic sleep state */
	REG_UPDATE_2(DMCU_RAM_ACCESS_CTRL,
			IRAM_HOST_ACCESS_EN, 0,
			IRAM_WR_ADDR_AUTO_INC, 0);

	/* Wait until microcontroller is पढ़ोy to process पूर्णांकerrupt */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 100, 800);

	/* Set command to संकेत IRAM is loaded and to initialize IRAM */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
			MCP_INIT_IRAM);

	/* Notअगरy microcontroller of new command */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* Ensure command has been executed beक्रमe continuing */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 100, 800);

	वापस true;
पूर्ण

अटल व्योम dcn10_get_dmcu_psr_state(काष्ठा dmcu *dmcu, क्रमागत dc_psr_state *state)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	uपूर्णांक32_t psr_state_offset = 0xf0;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस;

	/* Enable ग_लिखो access to IRAM */
	REG_UPDATE(DMCU_RAM_ACCESS_CTRL, IRAM_HOST_ACCESS_EN, 1);

	REG_WAIT(DMU_MEM_PWR_CNTL, DMCU_IRAM_MEM_PWR_STATE, 0, 2, 10);

	/* Write address to IRAM_RD_ADDR in DMCU_IRAM_RD_CTRL */
	REG_WRITE(DMCU_IRAM_RD_CTRL, psr_state_offset);

	/* Read data from IRAM_RD_DATA in DMCU_IRAM_RD_DATA*/
	*state = (क्रमागत dc_psr_state)REG_READ(DMCU_IRAM_RD_DATA);

	/* Disable ग_लिखो access to IRAM after finished using IRAM
	 * in order to allow dynamic sleep state
	 */
	REG_UPDATE(DMCU_RAM_ACCESS_CTRL, IRAM_HOST_ACCESS_EN, 0);
पूर्ण

अटल व्योम dcn10_dmcu_set_psr_enable(काष्ठा dmcu *dmcu, bool enable, bool रुको)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	अचिन्हित पूर्णांक dmcu_max_retry_on_रुको_reg_पढ़ोy = 801;
	अचिन्हित पूर्णांक dmcu_रुको_reg_पढ़ोy_पूर्णांकerval = 100;

	अचिन्हित पूर्णांक retryCount;
	क्रमागत dc_psr_state state = PSR_STATE0;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस;

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
				dmcu_रुको_reg_पढ़ोy_पूर्णांकerval,
				dmcu_max_retry_on_रुको_reg_पढ़ोy);

	/* setDMCUParam_Cmd */
	अगर (enable)
		REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
				PSR_ENABLE);
	अन्यथा
		REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
				PSR_EXIT);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* Below loops 1000 x 500us = 500 ms.
	 *  Exit PSR may need to रुको 1-2 frames to घातer up. Timeout after at
	 *  least a few frames. Should never hit the max retry निश्चित below.
	 */
	अगर (रुको == true) अणु
		क्रम (retryCount = 0; retryCount <= 1000; retryCount++) अणु
			dcn10_get_dmcu_psr_state(dmcu, &state);
			अगर (enable) अणु
				अगर (state != PSR_STATE0)
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (state == PSR_STATE0)
					अवरोध;
			पूर्ण
			udelay(500);
		पूर्ण

		/* निश्चित अगर max retry hit */
		अगर (retryCount >= 1000)
			ASSERT(0);
	पूर्ण
पूर्ण

अटल bool dcn10_dmcu_setup_psr(काष्ठा dmcu *dmcu,
		काष्ठा dc_link *link,
		काष्ठा psr_context *psr_context)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	अचिन्हित पूर्णांक dmcu_max_retry_on_रुको_reg_पढ़ोy = 801;
	अचिन्हित पूर्णांक dmcu_रुको_reg_पढ़ोy_पूर्णांकerval = 100;

	जोड़ dce_dmcu_psr_config_data_reg1 masterCmdData1;
	जोड़ dce_dmcu_psr_config_data_reg2 masterCmdData2;
	जोड़ dce_dmcu_psr_config_data_reg3 masterCmdData3;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस false;

	link->link_enc->funcs->psr_program_dp_dphy_fast_training(link->link_enc,
			psr_context->psrExitLinkTrainingRequired);

	/* Enable अटल screen पूर्णांकerrupts क्रम PSR supported display */
	/* Disable the पूर्णांकerrupt coming from other displays. */
	REG_UPDATE_4(DMCU_INTERRUPT_TO_UC_EN_MASK,
			STATIC_SCREEN1_INT_TO_UC_EN, 0,
			STATIC_SCREEN2_INT_TO_UC_EN, 0,
			STATIC_SCREEN3_INT_TO_UC_EN, 0,
			STATIC_SCREEN4_INT_TO_UC_EN, 0);

	चयन (psr_context->controllerId) अणु
	/* Driver uses हाल 1 क्रम unconfigured */
	हाल 1:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN1_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 2:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN2_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 3:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN3_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 4:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN4_INT_TO_UC_EN, 1);
		अवरोध;
	हाल 5:
		/* CZ/NL only has 4 CRTC!!
		 * really valid.
		 * There is no पूर्णांकerrupt enable mask क्रम these instances.
		 */
		अवरोध;
	हाल 6:
		/* CZ/NL only has 4 CRTC!!
		 * These are here because they are defined in HW regspec,
		 * but not really valid. There is no पूर्णांकerrupt enable mask
		 * क्रम these instances.
		 */
		अवरोध;
	शेष:
		REG_UPDATE(DMCU_INTERRUPT_TO_UC_EN_MASK,
				STATIC_SCREEN1_INT_TO_UC_EN, 1);
		अवरोध;
	पूर्ण

	link->link_enc->funcs->psr_program_secondary_packet(link->link_enc,
			psr_context->sdpTransmitLineNumDeadline);

	अगर (psr_context->allow_smu_optimizations)
		REG_UPDATE(SMU_INTERRUPT_CONTROL, DC_SMU_INT_ENABLE, 1);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
			dmcu_रुको_reg_पढ़ोy_पूर्णांकerval,
			dmcu_max_retry_on_रुको_reg_पढ़ोy);

	/* setDMCUParam_PSRHostConfigData */
	masterCmdData1.u32All = 0;
	masterCmdData1.bits.समयhyst_frames = psr_context->समयhyst_frames;
	masterCmdData1.bits.hyst_lines = psr_context->hyst_lines;
	masterCmdData1.bits.rfb_update_स्वतः_en =
			psr_context->rfb_update_स्वतः_en;
	masterCmdData1.bits.dp_port_num = psr_context->transmitterId;
	masterCmdData1.bits.dcp_sel = psr_context->controllerId;
	masterCmdData1.bits.phy_type  = psr_context->phyType;
	masterCmdData1.bits.frame_cap_ind =
			psr_context->psrFrameCaptureIndicationReq;
	masterCmdData1.bits.aux_chan = psr_context->channel;
	masterCmdData1.bits.aux_repeat = psr_context->aux_repeats;
	masterCmdData1.bits.allow_smu_optimizations = psr_context->allow_smu_optimizations;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1),
					masterCmdData1.u32All);

	masterCmdData2.u32All = 0;
	masterCmdData2.bits.dig_fe = psr_context->engineId;
	masterCmdData2.bits.dig_be = psr_context->transmitterId;
	masterCmdData2.bits.skip_रुको_क्रम_pll_lock =
			psr_context->skipPsrWaitForPllLock;
	masterCmdData2.bits.frame_delay = psr_context->frame_delay;
	masterCmdData2.bits.smu_phy_id = psr_context->smuPhyId;
	masterCmdData2.bits.num_of_controllers =
			psr_context->numberOfControllers;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG2),
			masterCmdData2.u32All);

	masterCmdData3.u32All = 0;
	masterCmdData3.bits.psr_level = psr_context->psr_level.u32all;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG3),
			masterCmdData3.u32All);


	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG,
			MASTER_COMM_CMD_REG_BYTE0, PSR_SET);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	वापस true;
पूर्ण

अटल व्योम dcn10_psr_रुको_loop(
	काष्ठा dmcu *dmcu,
	अचिन्हित पूर्णांक रुको_loop_number)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	जोड़ dce_dmcu_psr_config_data_रुको_loop_reg1 masterCmdData1;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस;

	अगर (रुको_loop_number != 0) अणु
	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	masterCmdData1.u32 = 0;
	masterCmdData1.bits.रुको_loop = रुको_loop_number;
	dmcu->cached_रुको_loop_number = रुको_loop_number;
	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1), masterCmdData1.u32);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, PSR_SET_WAITLOOP);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);
	पूर्ण
पूर्ण

अटल व्योम dcn10_get_psr_रुको_loop(
		काष्ठा dmcu *dmcu, अचिन्हित पूर्णांक *psr_रुको_loop_number)
अणु
	*psr_रुको_loop_number = dmcu->cached_रुको_loop_number;
	वापस;
पूर्ण

अटल bool dcn10_is_dmcu_initialized(काष्ठा dmcu *dmcu)
अणु
	/* microcontroller is not running */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस false;
	वापस true;
पूर्ण



अटल bool dcn20_lock_phy(काष्ठा dmcu *dmcu)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस false;

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, MCP_SYNC_PHY_LOCK);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	वापस true;
पूर्ण

अटल bool dcn20_unlock_phy(काष्ठा dmcu *dmcu)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस false;

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, MCP_SYNC_PHY_UNLOCK);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	वापस true;
पूर्ण

अटल bool dcn10_send_edid_cea(काष्ठा dmcu *dmcu,
		पूर्णांक offset,
		पूर्णांक total_length,
		uपूर्णांक8_t *data,
		पूर्णांक length)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	uपूर्णांक32_t header, data1, data2;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस false;

	अगर (length > 8 || length <= 0)
		वापस false;

	header = ((uपूर्णांक32_t)offset & 0xFFFF) << 16 | (total_length & 0xFFFF);
	data1 = (((uपूर्णांक32_t)data[0]) << 24) | (((uपूर्णांक32_t)data[1]) << 16) |
		(((uपूर्णांक32_t)data[2]) << 8) | ((uपूर्णांक32_t)data[3]);
	data2 = (((uपूर्णांक32_t)data[4]) << 24) | (((uपूर्णांक32_t)data[5]) << 16) |
		(((uपूर्णांक32_t)data[6]) << 8) | ((uपूर्णांक32_t)data[7]);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0, MCP_SEND_EDID_CEA);

	REG_WRITE(MASTER_COMM_DATA_REG1, header);
	REG_WRITE(MASTER_COMM_DATA_REG2, data1);
	REG_WRITE(MASTER_COMM_DATA_REG3, data2);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0, 1, 10000);

	वापस true;
पूर्ण

अटल bool dcn10_get_scp_results(काष्ठा dmcu *dmcu,
		uपूर्णांक32_t *cmd,
		uपूर्णांक32_t *data1,
		uपूर्णांक32_t *data2,
		uपूर्णांक32_t *data3)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस false;

	*cmd = REG_READ(SLAVE_COMM_CMD_REG);
	*data1 =  REG_READ(SLAVE_COMM_DATA_REG1);
	*data2 =  REG_READ(SLAVE_COMM_DATA_REG2);
	*data3 =  REG_READ(SLAVE_COMM_DATA_REG3);

	/* clear SCP पूर्णांकerrupt */
	REG_UPDATE(SLAVE_COMM_CNTL_REG, SLAVE_COMM_INTERRUPT, 0);

	वापस true;
पूर्ण

अटल bool dcn10_recv_amd_vsdb(काष्ठा dmcu *dmcu,
		पूर्णांक *version,
		पूर्णांक *min_frame_rate,
		पूर्णांक *max_frame_rate)
अणु
	uपूर्णांक32_t data[4];
	पूर्णांक cmd, ack, len;

	अगर (!dcn10_get_scp_results(dmcu, &data[0], &data[1], &data[2], &data[3]))
		वापस false;

	cmd = data[0] & 0x3FF;
	len = (data[0] >> 10) & 0x3F;
	ack = data[1];

	अगर (cmd != MCP_SEND_EDID_CEA || ack != EDID_CEA_CMD_ACK || len != 12)
		वापस false;

	अगर ((data[2] & 0xFF)) अणु
		*version = (data[2] >> 8) & 0xFF;
		*min_frame_rate = (data[3] >> 16) & 0xFFFF;
		*max_frame_rate = data[3] & 0xFFFF;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool dcn10_recv_edid_cea_ack(काष्ठा dmcu *dmcu, पूर्णांक *offset)
अणु
	uपूर्णांक32_t data[4];
	पूर्णांक cmd, ack;

	अगर (!dcn10_get_scp_results(dmcu,
				&data[0], &data[1], &data[2], &data[3]))
		वापस false;

	cmd = data[0] & 0x3FF;
	ack = data[1];

	अगर (cmd != MCP_SEND_EDID_CEA)
		वापस false;

	अगर (ack == EDID_CEA_CMD_ACK)
		वापस true;

	*offset = data[2]; /* nack */
	वापस false;
पूर्ण

#पूर्ण_अगर //(CONFIG_DRM_AMD_DC_DCN)

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
अटल व्योम dcn10_क्रमward_crc_winकरोw(काष्ठा dmcu *dmcu,
					काष्ठा crc_region *crc_win,
					काष्ठा otg_phy_mux *mux_mapping)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	अचिन्हित पूर्णांक dmcu_max_retry_on_रुको_reg_पढ़ोy = 801;
	अचिन्हित पूर्णांक dmcu_रुको_reg_पढ़ोy_पूर्णांकerval = 100;
	अचिन्हित पूर्णांक crc_start = 0, crc_end = 0, otg_phy_mux = 0;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस;

	अगर (!crc_win)
		वापस;

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
				dmcu_रुको_reg_पढ़ोy_पूर्णांकerval,
				dmcu_max_retry_on_रुको_reg_पढ़ोy);

	/* build up nitअगरication data */
	crc_start = (((अचिन्हित पूर्णांक) crc_win->x_start) << 16) | crc_win->y_start;
	crc_end = (((अचिन्हित पूर्णांक) crc_win->x_end) << 16) | crc_win->y_end;
	otg_phy_mux =
		(((अचिन्हित पूर्णांक) mux_mapping->otg_output_num) << 16) | mux_mapping->phy_output_num;

	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1),
					crc_start);

	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG2),
			crc_end);

	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG3),
			otg_phy_mux);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
				CRC_WIN_NOTIFY);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);
पूर्ण

अटल व्योम dcn10_stop_crc_win_update(काष्ठा dmcu *dmcu,
					काष्ठा otg_phy_mux *mux_mapping)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	अचिन्हित पूर्णांक dmcu_max_retry_on_रुको_reg_पढ़ोy = 801;
	अचिन्हित पूर्णांक dmcu_रुको_reg_पढ़ोy_पूर्णांकerval = 100;
	अचिन्हित पूर्णांक otg_phy_mux = 0;

	/* If microcontroller is not running, करो nothing */
	अगर (dmcu->dmcu_state != DMCU_RUNNING)
		वापस;

	/* रुकोDMCUReadyForCmd */
	REG_WAIT(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 0,
				dmcu_रुको_reg_पढ़ोy_पूर्णांकerval,
				dmcu_max_retry_on_रुको_reg_पढ़ोy);

	/* build up nitअगरication data */
	otg_phy_mux =
		(((अचिन्हित पूर्णांक) mux_mapping->otg_output_num) << 16) | mux_mapping->phy_output_num;

	dm_ग_लिखो_reg(dmcu->ctx, REG(MASTER_COMM_DATA_REG1),
					otg_phy_mux);

	/* setDMCUParam_Cmd */
	REG_UPDATE(MASTER_COMM_CMD_REG, MASTER_COMM_CMD_REG_BYTE0,
				CRC_STOP_UPDATE);

	/* notअगरyDMCUMsg */
	REG_UPDATE(MASTER_COMM_CNTL_REG, MASTER_COMM_INTERRUPT, 1);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dmcu_funcs dce_funcs = अणु
	.dmcu_init = dce_dmcu_init,
	.load_iram = dce_dmcu_load_iram,
	.set_psr_enable = dce_dmcu_set_psr_enable,
	.setup_psr = dce_dmcu_setup_psr,
	.get_psr_state = dce_get_dmcu_psr_state,
	.set_psr_रुको_loop = dce_psr_रुको_loop,
	.get_psr_रुको_loop = dce_get_psr_रुको_loop,
	.is_dmcu_initialized = dce_is_dmcu_initialized
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल स्थिर काष्ठा dmcu_funcs dcn10_funcs = अणु
	.dmcu_init = dcn10_dmcu_init,
	.load_iram = dcn10_dmcu_load_iram,
	.set_psr_enable = dcn10_dmcu_set_psr_enable,
	.setup_psr = dcn10_dmcu_setup_psr,
	.get_psr_state = dcn10_get_dmcu_psr_state,
	.set_psr_रुको_loop = dcn10_psr_रुको_loop,
	.get_psr_रुको_loop = dcn10_get_psr_रुको_loop,
	.send_edid_cea = dcn10_send_edid_cea,
	.recv_amd_vsdb = dcn10_recv_amd_vsdb,
	.recv_edid_cea_ack = dcn10_recv_edid_cea_ack,
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	.क्रमward_crc_winकरोw = dcn10_क्रमward_crc_winकरोw,
	.stop_crc_win_update = dcn10_stop_crc_win_update,
#पूर्ण_अगर
	.is_dmcu_initialized = dcn10_is_dmcu_initialized
पूर्ण;

अटल स्थिर काष्ठा dmcu_funcs dcn20_funcs = अणु
	.dmcu_init = dcn10_dmcu_init,
	.load_iram = dcn10_dmcu_load_iram,
	.set_psr_enable = dcn10_dmcu_set_psr_enable,
	.setup_psr = dcn10_dmcu_setup_psr,
	.get_psr_state = dcn10_get_dmcu_psr_state,
	.set_psr_रुको_loop = dcn10_psr_रुको_loop,
	.get_psr_रुको_loop = dcn10_get_psr_रुको_loop,
	.is_dmcu_initialized = dcn10_is_dmcu_initialized,
	.lock_phy = dcn20_lock_phy,
	.unlock_phy = dcn20_unlock_phy
पूर्ण;

अटल स्थिर काष्ठा dmcu_funcs dcn21_funcs = अणु
	.dmcu_init = dcn21_dmcu_init,
	.load_iram = dcn10_dmcu_load_iram,
	.set_psr_enable = dcn10_dmcu_set_psr_enable,
	.setup_psr = dcn10_dmcu_setup_psr,
	.get_psr_state = dcn10_get_dmcu_psr_state,
	.set_psr_रुको_loop = dcn10_psr_रुको_loop,
	.get_psr_रुको_loop = dcn10_get_psr_रुको_loop,
	.is_dmcu_initialized = dcn10_is_dmcu_initialized,
	.lock_phy = dcn20_lock_phy,
	.unlock_phy = dcn20_unlock_phy
पूर्ण;
#पूर्ण_अगर

अटल व्योम dce_dmcu_स्थिरruct(
	काष्ठा dce_dmcu *dmcu_dce,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask)
अणु
	काष्ठा dmcu *base = &dmcu_dce->base;

	base->ctx = ctx;
	base->funcs = &dce_funcs;
	base->cached_रुको_loop_number = 0;

	dmcu_dce->regs = regs;
	dmcu_dce->dmcu_shअगरt = dmcu_shअगरt;
	dmcu_dce->dmcu_mask = dmcu_mask;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल व्योम dcn21_dmcu_स्थिरruct(
		काष्ठा dce_dmcu *dmcu_dce,
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
		स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
		स्थिर काष्ठा dce_dmcu_mask *dmcu_mask)
अणु
	uपूर्णांक32_t psp_version = 0;

	dce_dmcu_स्थिरruct(dmcu_dce, ctx, regs, dmcu_shअगरt, dmcu_mask);

	अगर (!IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) अणु
		psp_version = dm_पढ़ो_reg(ctx, mmMP0_SMN_C2PMSG_58);
		dmcu_dce->base.स्वतः_load_dmcu = ((psp_version & 0x00FF00FF) > 0x00110029);
		dmcu_dce->base.psp_version = psp_version;
	पूर्ण
पूर्ण
#पूर्ण_अगर

काष्ठा dmcu *dce_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask)
अणु
	काष्ठा dce_dmcu *dmcu_dce = kzalloc(माप(*dmcu_dce), GFP_KERNEL);

	अगर (dmcu_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dce_dmcu_स्थिरruct(
		dmcu_dce, ctx, regs, dmcu_shअगरt, dmcu_mask);

	dmcu_dce->base.funcs = &dce_funcs;

	वापस &dmcu_dce->base;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
काष्ठा dmcu *dcn10_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask)
अणु
	काष्ठा dce_dmcu *dmcu_dce = kzalloc(माप(*dmcu_dce), GFP_ATOMIC);

	अगर (dmcu_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dce_dmcu_स्थिरruct(
		dmcu_dce, ctx, regs, dmcu_shअगरt, dmcu_mask);

	dmcu_dce->base.funcs = &dcn10_funcs;

	वापस &dmcu_dce->base;
पूर्ण

काष्ठा dmcu *dcn20_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask)
अणु
	काष्ठा dce_dmcu *dmcu_dce = kzalloc(माप(*dmcu_dce), GFP_ATOMIC);

	अगर (dmcu_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dce_dmcu_स्थिरruct(
		dmcu_dce, ctx, regs, dmcu_shअगरt, dmcu_mask);

	dmcu_dce->base.funcs = &dcn20_funcs;

	वापस &dmcu_dce->base;
पूर्ण

काष्ठा dmcu *dcn21_dmcu_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dce_dmcu_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_dmcu_shअगरt *dmcu_shअगरt,
	स्थिर काष्ठा dce_dmcu_mask *dmcu_mask)
अणु
	काष्ठा dce_dmcu *dmcu_dce = kzalloc(माप(*dmcu_dce), GFP_ATOMIC);

	अगर (dmcu_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn21_dmcu_स्थिरruct(
		dmcu_dce, ctx, regs, dmcu_shअगरt, dmcu_mask);

	dmcu_dce->base.funcs = &dcn21_funcs;

	वापस &dmcu_dce->base;
पूर्ण
#पूर्ण_अगर

व्योम dce_dmcu_destroy(काष्ठा dmcu **dmcu)
अणु
	काष्ठा dce_dmcu *dmcu_dce = TO_DCE_DMCU(*dmcu);

	kमुक्त(dmcu_dce);
	*dmcu = शून्य;
पूर्ण
