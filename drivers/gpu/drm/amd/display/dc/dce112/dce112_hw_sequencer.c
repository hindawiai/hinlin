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
#समावेश "dce112_hw_sequencer.h"

#समावेश "dce110/dce110_hw_sequencer.h"

/* include DCE11.2 रेजिस्टर header files */
#समावेश "dce/dce_11_2_d.h"
#समावेश "dce/dce_11_2_sh_mask.h"

काष्ठा dce112_hw_seq_reg_offsets अणु
	uपूर्णांक32_t crtc;
पूर्ण;


अटल स्थिर काष्ठा dce112_hw_seq_reg_offsets reg_offsets[] = अणु
अणु
	.crtc = (mmCRTC0_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC1_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC2_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC3_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC4_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC5_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण
पूर्ण;
#घोषणा HW_REG_CRTC(reg, id)\
	(reg + reg_offsets[id].crtc)

/*******************************************************************************
 * Private definitions
 ******************************************************************************/

अटल व्योम dce112_init_pte(काष्ठा dc_context *ctx)
अणु
	uपूर्णांक32_t addr;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t chunk_पूर्णांक = 0;
	uपूर्णांक32_t chunk_mul = 0;

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

अटल bool dce112_enable_display_घातer_gating(
	काष्ठा dc *dc,
	uपूर्णांक8_t controller_id,
	काष्ठा dc_bios *dcb,
	क्रमागत pipe_gating_control घातer_gating)
अणु
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

	अगर (घातer_gating != PIPE_GATING_CONTROL_INIT || controller_id == 0)अणु

		bp_result = dcb->funcs->enable_disp_घातer_gating(
						dcb, controller_id + 1, cntl);

		/* Revert MASTER_UPDATE_MODE to 0 because bios sets it 2
		 * by शेष when command table is called
		 */
		dm_ग_लिखो_reg(ctx,
			HW_REG_CRTC(mmCRTC_MASTER_UPDATE_MODE, controller_id),
			0);
	पूर्ण

	अगर (घातer_gating != PIPE_GATING_CONTROL_ENABLE)
		dce112_init_pte(ctx);

	अगर (bp_result == BP_RESULT_OK)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

व्योम dce112_hw_sequencer_स्थिरruct(काष्ठा dc *dc)
अणु
	/* All रेजिस्टरs used by dce11.2 match those in dce11 in offset and
	 * काष्ठाure
	 */
	dce110_hw_sequencer_स्थिरruct(dc);
	dc->hwseq->funcs.enable_display_घातer_gating = dce112_enable_display_घातer_gating;
पूर्ण

