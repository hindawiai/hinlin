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

#समावेश "dm_services.h"
#समावेश "dc.h"
#समावेश "core_types.h"
#समावेश "dce120_hw_sequencer.h"
#समावेश "dce/dce_hwseq.h"

#समावेश "dce110/dce110_hw_sequencer.h"

#समावेश "dce/dce_12_0_offset.h"
#समावेश "dce/dce_12_0_sh_mask.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"
#समावेश "reg_helper.h"

#घोषणा CTX \
	hws->ctx
#घोषणा REG(reg)\
	hws->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name

काष्ठा dce120_hw_seq_reg_offsets अणु
	uपूर्णांक32_t crtc;
पूर्ण;

#अगर 0
अटल स्थिर काष्ठा dce120_hw_seq_reg_offsets reg_offsets[] = अणु
अणु
	.crtc = (mmCRTC0_CRTC_GSL_CONTROL - mmCRTC0_CRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC1_CRTC_GSL_CONTROL - mmCRTC0_CRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC2_CRTC_GSL_CONTROL - mmCRTC0_CRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC3_CRTC_GSL_CONTROL - mmCRTC0_CRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC4_CRTC_GSL_CONTROL - mmCRTC0_CRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC5_CRTC_GSL_CONTROL - mmCRTC0_CRTC_GSL_CONTROL),
पूर्ण
पूर्ण;

#घोषणा HW_REG_CRTC(reg, id)\
	(reg + reg_offsets[id].crtc)

#घोषणा CNTL_ID(controller_id)\
	controller_id
/*******************************************************************************
 * Private definitions
 ******************************************************************************/
अटल व्योम dce120_init_pte(काष्ठा dc_context *ctx, uपूर्णांक8_t controller_id)
अणु
	uपूर्णांक32_t addr;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t chunk_पूर्णांक = 0;
	uपूर्णांक32_t chunk_mul = 0;
/*
	addr = mmDCP0_DVMM_PTE_CONTROL + controller_id *
			(mmDCP1_DVMM_PTE_CONTROL- mmDCP0_DVMM_PTE_CONTROL);

	value = dm_पढ़ो_reg(ctx, addr);

	set_reg_field_value(
			value, 0, DCP, controller_id,
			DVMM_PTE_CONTROL,
			DVMM_USE_SINGLE_PTE);

	set_reg_field_value_soc15(
			value, 1, DCP, controller_id,
			DVMM_PTE_CONTROL,
			DVMM_PTE_BUFFER_MODE0);

	set_reg_field_value_soc15(
			value, 1, DCP, controller_id,
			DVMM_PTE_CONTROL,
			DVMM_PTE_BUFFER_MODE1);

	dm_ग_लिखो_reg(ctx, addr, value);*/

	addr = mmDVMM_PTE_REQ;
	value = dm_पढ़ो_reg(ctx, addr);

	chunk_पूर्णांक = get_reg_field_value(
		value,
		DVMM_PTE_REQ,
		HFLIP_PTEREQ_PER_CHUNK_INT);

	chunk_mul = get_reg_field_value(
		value,
		DVMM_PTE_REQ,
		HFLIP_PTEREQ_PER_CHUNK_MULTIPLIER);

	अगर (chunk_पूर्णांक != 0x4 || chunk_mul != 0x4) अणु

		set_reg_field_value(
			value,
			255,
			DVMM_PTE_REQ,
			MAX_PTEREQ_TO_ISSUE);

		set_reg_field_value(
			value,
			4,
			DVMM_PTE_REQ,
			HFLIP_PTEREQ_PER_CHUNK_INT);

		set_reg_field_value(
			value,
			4,
			DVMM_PTE_REQ,
			HFLIP_PTEREQ_PER_CHUNK_MULTIPLIER);

		dm_ग_लिखो_reg(ctx, addr, value);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल bool dce120_enable_display_घातer_gating(
	काष्ठा dc *dc,
	uपूर्णांक8_t controller_id,
	काष्ठा dc_bios *dcb,
	क्रमागत pipe_gating_control घातer_gating)
अणु
	/* disable क्रम bringup */
#अगर 0
	क्रमागत bp_result bp_result = BP_RESULT_OK;
	क्रमागत bp_pipe_control_action cntl;
	काष्ठा dc_context *ctx = dc->ctx;

	अगर (IS_FPGA_MAXIMUS_DC(ctx->dce_environment))
		वापस true;

	अगर (घातer_gating == PIPE_GATING_CONTROL_INIT)
		cntl = ASIC_PIPE_INIT;
	अन्यथा अगर (घातer_gating == PIPE_GATING_CONTROL_ENABLE)
		cntl = ASIC_PIPE_ENABLE;
	अन्यथा
		cntl = ASIC_PIPE_DISABLE;

	अगर (घातer_gating != PIPE_GATING_CONTROL_INIT || controller_id == 0) अणु

		bp_result = dcb->funcs->enable_disp_घातer_gating(
						dcb, controller_id + 1, cntl);

		/* Revert MASTER_UPDATE_MODE to 0 because bios sets it 2
		 * by शेष when command table is called
		 */
		dm_ग_लिखो_reg(ctx,
			HW_REG_CRTC(mmCRTC0_CRTC_MASTER_UPDATE_MODE, controller_id),
			0);
	पूर्ण

	अगर (घातer_gating != PIPE_GATING_CONTROL_ENABLE)
		dce120_init_pte(ctx, controller_id);

	अगर (bp_result == BP_RESULT_OK)
		वापस true;
	अन्यथा
		वापस false;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल व्योम dce120_update_dchub(
	काष्ठा dce_hwseq *hws,
	काष्ठा dchub_init_data *dh_data)
अणु
	/* TODO: port code from dal2 */
	चयन (dh_data->fb_mode) अणु
	हाल FRAME_BUFFER_MODE_ZFB_ONLY:
		/*For ZFB हाल need to put DCHUB FB BASE and TOP upside करोwn to indicate ZFB mode*/
		REG_UPDATE_2(DCHUB_FB_LOCATION,
				FB_TOP, 0,
				FB_BASE, 0x0FFFF);

		REG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr + dh_data->zfb_size_in_byte - 1) >> 22);
		अवरोध;
	हाल FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL:
		/*Should not touch FB LOCATION (करोne by VBIOS on AsicInit table)*/
		REG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, dh_data->zfb_phys_addr_base >> 22);

		REG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, dh_data->zfb_mc_base_addr >> 22);

		REG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, (dh_data->zfb_mc_base_addr + dh_data->zfb_size_in_byte - 1) >> 22);
		अवरोध;
	हाल FRAME_BUFFER_MODE_LOCAL_ONLY:
		/*Should not touch FB LOCATION (करोne by VBIOS on AsicInit table)*/
		REG_UPDATE(DCHUB_AGP_BASE,
				AGP_BASE, 0);

		REG_UPDATE(DCHUB_AGP_BOT,
				AGP_BOT, 0x03FFFF);

		REG_UPDATE(DCHUB_AGP_TOP,
				AGP_TOP, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dh_data->dchub_initialzied = true;
	dh_data->dchub_info_valid = false;
पूर्ण

/**
 * dce121_xgmi_enabled() - Check अगर xGMI is enabled
 * @hws: DCE hardware sequencer object
 *
 * Return true अगर xGMI is enabled. False otherwise.
 */
bool dce121_xgmi_enabled(काष्ठा dce_hwseq *hws)
अणु
	uपूर्णांक32_t pf_max_region;

	REG_GET(MC_VM_XGMI_LFB_CNTL, PF_MAX_REGION, &pf_max_region);
	/* PF_MAX_REGION == 0 means xgmi is disabled */
	वापस !!pf_max_region;
पूर्ण

व्योम dce120_hw_sequencer_स्थिरruct(काष्ठा dc *dc)
अणु
	/* All रेजिस्टरs used by dce11.2 match those in dce11 in offset and
	 * काष्ठाure
	 */
	dce110_hw_sequencer_स्थिरruct(dc);
	dc->hwseq->funcs.enable_display_घातer_gating = dce120_enable_display_घातer_gating;
	dc->hwss.update_dchub = dce120_update_dchub;
पूर्ण

