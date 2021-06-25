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
#समावेश "resource.h"
#समावेश "mcif_wb.h"
#समावेश "dcn20_mmhubbub.h"


#घोषणा REG(reg)\
	mcअगर_wb20->mcअगर_wb_regs->reg

#घोषणा CTX \
	mcअगर_wb20->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	mcअगर_wb20->mcअगर_wb_shअगरt->field_name, mcअगर_wb20->mcअगर_wb_mask->field_name

#घोषणा MCIF_ADDR(addr) (((अचिन्हित दीर्घ दीर्घ)addr & 0xffffffffff) + 0xFE) >> 8
#घोषणा MCIF_ADDR_HIGH(addr) (अचिन्हित दीर्घ दीर्घ)addr >> 40

/* wbअगर programming guide:
 * 1. set up wbअगर parameter:
 *    अचिन्हित दीर्घ दीर्घ   luma_address[4];       //4 frame buffer
 *    अचिन्हित दीर्घ दीर्घ   chroma_address[4];
 *    अचिन्हित पूर्णांक	   luma_pitch;
 *    अचिन्हित पूर्णांक	   chroma_pitch;
 *    अचिन्हित पूर्णांक         warmup_pitch=0x10;     //256B align, the page size is 4KB when it is 0x10
 *    अचिन्हित पूर्णांक	   slice_lines;           //slice size
 *    अचिन्हित पूर्णांक         समय_per_pixel;        // समय per pixel, in ns
 *    अचिन्हित पूर्णांक         arbitration_slice;     // 0: 512 bytes 1: 1024 bytes 2: 2048 Bytes
 *    अचिन्हित पूर्णांक         max_scaled_समय;       // used क्रम QOS generation
 *    अचिन्हित पूर्णांक         swlock=0x0;
 *    अचिन्हित पूर्णांक         cli_watermark[4];      //4 group urgent watermark
 *    अचिन्हित पूर्णांक         pstate_watermark[4];   //4 group pstate watermark
 *    अचिन्हित पूर्णांक         sw_पूर्णांक_en;             // Software पूर्णांकerrupt enable, frame end and overflow
 *    अचिन्हित पूर्णांक         sw_slice_पूर्णांक_en;       // slice end पूर्णांकerrupt enable
 *    अचिन्हित पूर्णांक         sw_overrun_पूर्णांक_en;     // overrun error पूर्णांकerrupt enable
 *    अचिन्हित पूर्णांक         vce_पूर्णांक_en;            // VCE पूर्णांकerrupt enable, frame end and overflow
 *    अचिन्हित पूर्णांक         vce_slice_पूर्णांक_en;      // VCE slice end पूर्णांकerrupt enable, frame end and overflow
 *
 * 2. configure wbअगर रेजिस्टर
 *    a. call mmhubbub_config_wbअगर()
 *
 * 3. Enable wbअगर
 *    call set_wbअगर_bufmgr_enable();
 *
 * 4. wbअगर_dump_status(), option, क्रम debug purpose
 *    the bufmgr status can show the progress of ग_लिखो back, can be used क्रम debug purpose
 */

अटल व्योम mmhubbub2_config_mcअगर_buf(काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_buf_params *params,
		अचिन्हित पूर्णांक dest_height)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);

	/* sw lock buffer0~buffer3, शेष is 0 */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_LOCK, params->swlock);

	/* buffer address क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_Y, MCIF_WB_BUF_1_ADDR_Y, MCIF_ADDR(params->luma_address[0]));
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_Y_HIGH, MCIF_WB_BUF_1_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[0]));
	/* right eye sub-buffer address offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_Y_OFFSET, MCIF_WB_BUF_1_ADDR_Y_OFFSET, 0);

	/* buffer address क्रम Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_C, MCIF_WB_BUF_1_ADDR_C, MCIF_ADDR(params->chroma_address[0]));
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_C_HIGH, MCIF_WB_BUF_1_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[0]));
	/* right eye offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_C_OFFSET, MCIF_WB_BUF_1_ADDR_C_OFFSET, 0);

	/* buffer address क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_Y, MCIF_WB_BUF_2_ADDR_Y, MCIF_ADDR(params->luma_address[1]));
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_Y_HIGH, MCIF_WB_BUF_2_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[1]));
	/* right eye sub-buffer address offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_Y_OFFSET, MCIF_WB_BUF_2_ADDR_Y_OFFSET, 0);

	/* buffer address क्रम Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_C, MCIF_WB_BUF_2_ADDR_C, MCIF_ADDR(params->chroma_address[1]));
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_C_HIGH, MCIF_WB_BUF_2_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[1]));
	/* right eye offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_C_OFFSET, MCIF_WB_BUF_2_ADDR_C_OFFSET, 0);

	/* buffer address क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_Y, MCIF_WB_BUF_3_ADDR_Y, MCIF_ADDR(params->luma_address[2]));
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_Y_HIGH, MCIF_WB_BUF_3_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[2]));
	/* right eye sub-buffer address offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_Y_OFFSET, MCIF_WB_BUF_3_ADDR_Y_OFFSET, 0);

	/* buffer address क्रम Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_C, MCIF_WB_BUF_3_ADDR_C, MCIF_ADDR(params->chroma_address[2]));
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_C_HIGH, MCIF_WB_BUF_3_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[2]));
	/* right eye offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_C_OFFSET, MCIF_WB_BUF_3_ADDR_C_OFFSET, 0);

	/* buffer address क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_Y, MCIF_WB_BUF_4_ADDR_Y, MCIF_ADDR(params->luma_address[3]));
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_Y_HIGH, MCIF_WB_BUF_4_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[3]));
	/* right eye sub-buffer address offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_Y_OFFSET, MCIF_WB_BUF_4_ADDR_Y_OFFSET, 0);

	/* buffer address क्रम Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_C, MCIF_WB_BUF_4_ADDR_C, MCIF_ADDR(params->chroma_address[3]));
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_C_HIGH, MCIF_WB_BUF_4_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[3]));
	/* right eye offset क्रम packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_C_OFFSET, MCIF_WB_BUF_4_ADDR_C_OFFSET, 0);

	/* setup luma & chroma size
	 * should be enough to contain a whole frame Luma data,
	 * the programmed value is frame buffer size [27:8], 256-byte aligned
	 */
	REG_UPDATE(MCIF_WB_BUF_LUMA_SIZE, MCIF_WB_BUF_LUMA_SIZE, (params->luma_pitch>>8) * dest_height);
	REG_UPDATE(MCIF_WB_BUF_CHROMA_SIZE, MCIF_WB_BUF_CHROMA_SIZE, (params->chroma_pitch>>8) * dest_height);

	/* enable address fence */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUF_ADDR_FENCE_EN, 1);

	/* setup pitch, the programmed value is [15:8], 256B align */
	REG_UPDATE_2(MCIF_WB_BUF_PITCH, MCIF_WB_BUF_LUMA_PITCH, params->luma_pitch >> 8,
			MCIF_WB_BUF_CHROMA_PITCH, params->chroma_pitch >> 8);

	/* Set pitch क्रम MC cache warm up mode */
	/* Pitch is 256 bytes aligned. The शेष pitch is 4K */
	/* शेष is 0x10 */
	REG_UPDATE(MCIF_WB_WARM_UP_CNTL, MCIF_WB_PITCH_SIZE_WARMUP, params->warmup_pitch);
पूर्ण

अटल व्योम mmhubbub2_config_mcअगर_arb(काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_arb_params *params)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);

	/* Programmed by the video driver based on the CRTC timing (क्रम DWB) */
	REG_UPDATE(MCIF_WB_ARBITRATION_CONTROL, MCIF_WB_TIME_PER_PIXEL, params->समय_per_pixel);

	/* Programming dwb watermark */
	/* Watermark to generate urgent in MCIF_WB_CLI, value is determined by MCIF_WB_CLI_WATERMARK_MASK. */
	/* Program in ns. A क्रमmula will be provided in the pseuकरो code to calculate the value. */
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x0);
	/* urgent_watermarkA */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[0]);
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x1);
	/* urgent_watermarkB */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[1]);
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x2);
	/* urgent_watermarkC */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[2]);
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x3);
	/* urgent_watermarkD */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[3]);

	/* Programming nb pstate watermark */
	/* nbp_state_change_watermarkA */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x0);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[0]);
	/* nbp_state_change_watermarkB */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x1);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[1]);
	/* nbp_state_change_watermarkC */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x2);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[2]);
	/* nbp_state_change_watermarkD */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x3);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[3]);

	/* max_scaled_समय */
	REG_UPDATE(MULTI_LEVEL_QOS_CTRL, MAX_SCALED_TIME_TO_URGENT, params->max_scaled_समय);

	/* slice_lines */
	REG_UPDATE(MCIF_WB_BUFMGR_VCE_CONTROL, MCIF_WB_BUFMGR_SLICE_SIZE, params->slice_lines-1);

	/* Set arbitration unit क्रम Luma/Chroma */
	/* arb_unit=2 should be chosen क्रम more efficiency */
	/* Arbitration size, 0: 512 bytes 1: 1024 bytes 2: 2048 Bytes */
	REG_UPDATE(MCIF_WB_ARBITRATION_CONTROL, MCIF_WB_CLIENT_ARBITRATION_SLICE,  params->arbitration_slice);
पूर्ण

व्योम mmhubbub2_config_mcअगर_irq(काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_irq_params *params)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);

	/* Set पूर्णांकerrupt mask */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_INT_EN, params->sw_पूर्णांक_en);
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_SLICE_INT_EN, params->sw_slice_पूर्णांक_en);
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_OVERRUN_INT_EN,  params->sw_overrun_पूर्णांक_en);

	REG_UPDATE(MCIF_WB_BUFMGR_VCE_CONTROL, MCIF_WB_BUFMGR_VCE_INT_EN,  params->vce_पूर्णांक_en);
	REG_UPDATE(MCIF_WB_BUFMGR_VCE_CONTROL, MCIF_WB_BUFMGR_VCE_SLICE_INT_EN,  params->vce_slice_पूर्णांक_en);
पूर्ण

व्योम mmhubbub2_enable_mcअगर(काष्ठा mcअगर_wb *mcअगर_wb)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);

	/* Enable Mcअगरwb */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_ENABLE, 1);
पूर्ण

व्योम mmhubbub2_disable_mcअगर(काष्ठा mcअगर_wb *mcअगर_wb)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);

	/* disable buffer manager */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_ENABLE, 0);
पूर्ण

/* set which group of pstate watermark to use and set wbअगर watermark change request */
/*
अटल व्योम mmhubbub2_wbअगर_watermark_change_req(काष्ठा mcअगर_wb *mcअगर_wb, अचिन्हित पूर्णांक wm_set)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);
	uपूर्णांक32_t change_req;

	REG_GET(SMU_WM_CONTROL, MCIF_WB0_WM_CHG_REQ, &change_req);
	change_req = (change_req == 0) ? 1 : 0;
	REG_UPDATE(SMU_WM_CONTROL, MCIF_WB0_WM_CHG_SEL, wm_set);
	REG_UPDATE(SMU_WM_CONTROL, MCIF_WB0_WM_CHG_REQ, change_req);
पूर्ण
*/
/* Set watermark change पूर्णांकerrupt disable bit */
/*
अटल व्योम mmhubbub2_set_wbअगर_watermark_change_पूर्णांक_disable(काष्ठा mcअगर_wb *mcअगर_wb, अचिन्हित पूर्णांक ack_पूर्णांक_dis)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);

	REG_UPDATE(SMU_WM_CONTROL, MCIF_WB0_WM_CHG_ACK_INT_DIS, ack_पूर्णांक_dis);
पूर्ण
*/
/* Read watermark change पूर्णांकerrupt status */
/*
अचिन्हित पूर्णांक mmhubbub2_get_wbअगर_watermark_change_पूर्णांक_status(काष्ठा mcअगर_wb *mcअगर_wb)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);
	uपूर्णांक32_t irq_status;

	REG_GET(SMU_WM_CONTROL, MCIF_WB0_WM_CHG_ACK_INT_STATUS, &irq_status);
	वापस irq_status;
पूर्ण
*/

व्योम mcअगरwb2_dump_frame(काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_buf_params *mcअगर_params,
		क्रमागत dwb_scaler_mode out_क्रमmat,
		अचिन्हित पूर्णांक dest_width,
		अचिन्हित पूर्णांक dest_height,
		काष्ठा mcअगर_wb_frame_dump_info *dump_info,
		अचिन्हित अक्षर *luma_buffer,
		अचिन्हित अक्षर *chroma_buffer,
		अचिन्हित अक्षर *dest_luma_buffer,
		अचिन्हित अक्षर *dest_chroma_buffer)
अणु
	काष्ठा dcn20_mmhubbub *mcअगर_wb20 = TO_DCN20_MMHUBBUB(mcअगर_wb);

	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_LOCK, 0xf);

	स_नकल(dest_luma_buffer,   luma_buffer,   mcअगर_params->luma_pitch * dest_height);
	स_नकल(dest_chroma_buffer, chroma_buffer, mcअगर_params->chroma_pitch * dest_height / 2);

	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_LOCK, 0x0);

	dump_info->क्रमmat	= out_क्रमmat;
	dump_info->width	= dest_width;
	dump_info->height	= dest_height;
	dump_info->luma_pitch	= mcअगर_params->luma_pitch;
	dump_info->chroma_pitch	= mcअगर_params->chroma_pitch;
	dump_info->size		= dest_height * (mcअगर_params->luma_pitch + mcअगर_params->chroma_pitch);
पूर्ण

स्थिर काष्ठा mcअगर_wb_funcs dcn20_mmhubbub_funcs = अणु
	.enable_mcअगर		= mmhubbub2_enable_mcअगर,
	.disable_mcअगर		= mmhubbub2_disable_mcअगर,
	.config_mcअगर_buf	= mmhubbub2_config_mcअगर_buf,
	.config_mcअगर_arb	= mmhubbub2_config_mcअगर_arb,
	.config_mcअगर_irq	= mmhubbub2_config_mcअगर_irq,
	.dump_frame		= mcअगरwb2_dump_frame,
पूर्ण;

व्योम dcn20_mmhubbub_स्थिरruct(काष्ठा dcn20_mmhubbub *mcअगर_wb20,
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dcn20_mmhubbub_रेजिस्टरs *mcअगर_wb_regs,
		स्थिर काष्ठा dcn20_mmhubbub_shअगरt *mcअगर_wb_shअगरt,
		स्थिर काष्ठा dcn20_mmhubbub_mask *mcअगर_wb_mask,
		पूर्णांक inst)
अणु
	mcअगर_wb20->base.ctx = ctx;

	mcअगर_wb20->base.inst = inst;
	mcअगर_wb20->base.funcs = &dcn20_mmhubbub_funcs;

	mcअगर_wb20->mcअगर_wb_regs = mcअगर_wb_regs;
	mcअगर_wb20->mcअगर_wb_shअगरt = mcअगर_wb_shअगरt;
	mcअगर_wb20->mcअगर_wb_mask = mcअगर_wb_mask;
पूर्ण
