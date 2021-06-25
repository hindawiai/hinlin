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

#अगर_अघोषित __DAL_COMMAND_TABLE_H__
#घोषणा __DAL_COMMAND_TABLE_H__

काष्ठा bios_parser;
काष्ठा bp_encoder_control;

काष्ठा cmd_tbl अणु
	क्रमागत bp_result (*dig_encoder_control)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_encoder_control *control);
	क्रमागत bp_result (*encoder_control_dig1)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_encoder_control *control);
	क्रमागत bp_result (*encoder_control_dig2)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_encoder_control *control);
	क्रमागत bp_result (*transmitter_control)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_transmitter_control *control);
	क्रमागत bp_result (*set_pixel_घड़ी)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_pixel_घड़ी_parameters *bp_params);
	क्रमागत bp_result (*enable_spपढ़ो_spectrum_on_ppll)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_spपढ़ो_spectrum_parameters *bp_params,
		bool enable);
	क्रमागत bp_result (*adjust_display_pll)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_adjust_pixel_घड़ी_parameters *bp_params);
	क्रमागत bp_result (*dac1_encoder_control)(
		काष्ठा bios_parser *bp,
		bool enable,
		uपूर्णांक32_t pixel_घड़ी,
		uपूर्णांक8_t dac_standard);
	क्रमागत bp_result (*dac2_encoder_control)(
		काष्ठा bios_parser *bp,
		bool enable,
		uपूर्णांक32_t pixel_घड़ी,
		uपूर्णांक8_t dac_standard);
	क्रमागत bp_result (*dac1_output_control)(
		काष्ठा bios_parser *bp,
		bool enable);
	क्रमागत bp_result (*dac2_output_control)(
		काष्ठा bios_parser *bp,
		bool enable);
	क्रमागत bp_result (*set_crtc_timing)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_hw_crtc_timing_parameters *bp_params);
	क्रमागत bp_result (*enable_crtc)(
		काष्ठा bios_parser *bp,
		क्रमागत controller_id controller_id,
		bool enable);
	क्रमागत bp_result (*enable_crtc_mem_req)(
		काष्ठा bios_parser *bp,
		क्रमागत controller_id controller_id,
		bool enable);
	क्रमागत bp_result (*program_घड़ी)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_pixel_घड़ी_parameters *bp_params);
	क्रमागत bp_result (*बाह्यal_encoder_control)(
			काष्ठा bios_parser *bp,
			काष्ठा bp_बाह्यal_encoder_control *cntl);
	क्रमागत bp_result (*enable_disp_घातer_gating)(
		काष्ठा bios_parser *bp,
		क्रमागत controller_id crtc_id,
		क्रमागत bp_pipe_control_action action);
	क्रमागत bp_result (*set_dce_घड़ी)(
		काष्ठा bios_parser *bp,
		काष्ठा bp_set_dce_घड़ी_parameters *bp_params);
पूर्ण;

व्योम dal_bios_parser_init_cmd_tbl(काष्ठा bios_parser *bp);

#पूर्ण_अगर
