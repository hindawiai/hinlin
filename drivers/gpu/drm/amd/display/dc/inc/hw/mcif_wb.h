<शैली गुरु>
/* Copyright 2012-17 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_MCIF_WB_H__
#घोषणा __DC_MCIF_WB_H__

#समावेश "dc_hw_types.h"


क्रमागत mmhubbub_wbअगर_mode अणु
	PACKED_444 = 0,
	PACKED_444_FP16 = 1,
	PLANAR_420_8BPC = 2,
	PLANAR_420_10BPC = 3
पूर्ण;

काष्ठा mcअगर_arb_params अणु

	अचिन्हित पूर्णांक		समय_per_pixel;
	अचिन्हित पूर्णांक		cli_watermark[4];
	अचिन्हित पूर्णांक		pstate_watermark[4];
	अचिन्हित पूर्णांक		arbitration_slice;
	अचिन्हित पूर्णांक		slice_lines;
	अचिन्हित पूर्णांक		max_scaled_समय;
	अचिन्हित पूर्णांक		dram_speed_change_duration;
पूर्ण;

काष्ठा mcअगर_irq_params अणु
	अचिन्हित पूर्णांक		sw_पूर्णांक_en;
	अचिन्हित पूर्णांक		sw_slice_पूर्णांक_en;
	अचिन्हित पूर्णांक		sw_overrun_पूर्णांक_en;
	अचिन्हित पूर्णांक		vce_पूर्णांक_en;
	अचिन्हित पूर्णांक		vce_slice_पूर्णांक_en;
पूर्ण;


/* / - mcअगर_wb_frame_dump_info is the info of the dumping WB data */
काष्ठा mcअगर_wb_frame_dump_info अणु
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		luma_pitch;
	अचिन्हित पूर्णांक		chroma_pitch;
	क्रमागत dwb_scaler_mode	क्रमmat;
पूर्ण;

काष्ठा mcअगर_wb अणु
	स्थिर काष्ठा mcअगर_wb_funcs *funcs;
	काष्ठा dc_context *ctx;
	पूर्णांक inst;
पूर्ण;

काष्ठा mcअगर_wb_funcs अणु

	व्योम (*warmup_mcअगर)(
		काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_warmup_params *params);
	व्योम (*enable_mcअगर)(काष्ठा mcअगर_wb *mcअगर_wb);

	व्योम (*disable_mcअगर)(काष्ठा mcअगर_wb *mcअगर_wb);

	व्योम (*config_mcअगर_buf)(
		काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_buf_params *params,
		अचिन्हित पूर्णांक dest_height);

	 व्योम (*config_mcअगर_arb)(
		काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_arb_params *params);

	 व्योम (*config_mcअगर_irq)(
		काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_irq_params *params);

	व्योम (*dump_frame)(
		काष्ठा mcअगर_wb *mcअगर_wb,
		काष्ठा mcअगर_buf_params *mcअगर_params,
		क्रमागत dwb_scaler_mode out_क्रमmat,
		अचिन्हित पूर्णांक dest_width,
		अचिन्हित पूर्णांक dest_height,
		काष्ठा mcअगर_wb_frame_dump_info *dump_info,
		अचिन्हित अक्षर *luma_buffer,
		अचिन्हित अक्षर *chroma_buffer,
		अचिन्हित अक्षर *dest_luma_buffer,
		अचिन्हित अक्षर *dest_chroma_buffer);
पूर्ण;

#पूर्ण_अगर
