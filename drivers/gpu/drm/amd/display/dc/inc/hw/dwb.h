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

#अगर_अघोषित __DC_DWBC_H__
#घोषणा __DC_DWBC_H__

#समावेश "dal_types.h"
#समावेश "dc_hw_types.h"

#घोषणा DWB_SW_V2	1
#घोषणा DWB_MCIF_BUF_COUNT 4

/* क्रमward declaration of mcअगर_wb काष्ठा */
काष्ठा mcअगर_wb;


क्रमागत dwb_sw_version अणु
	dwb_ver_1_0 = 1,
	dwb_ver_2_0 = 2,
पूर्ण;

क्रमागत dwb_source अणु
	dwb_src_scl = 0,	/* क्रम DCE7x/9x, DCN won't support. */
	dwb_src_blnd,		/* क्रम DCE7x/9x */
	dwb_src_fmt,		/* क्रम DCE7x/9x */
	dwb_src_otg0 = 0x100,	/* क्रम DCN1.x/DCN2.x, रेजिस्टर: mmDWB_SOURCE_SELECT */
	dwb_src_otg1,		/* क्रम DCN1.x/DCN2.x */
	dwb_src_otg2,		/* क्रम DCN1.x/DCN2.x */
	dwb_src_otg3,		/* क्रम DCN1.x/DCN2.x */
पूर्ण;

/* DCN1.x, DCN2.x support 2 pipes */
क्रमागत dwb_pipe अणु
	dwb_pipe0 = 0,
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	dwb_pipe1,
#पूर्ण_अगर
	dwb_pipe_max_num,
पूर्ण;

क्रमागत dwb_frame_capture_enable अणु
	DWB_FRAME_CAPTURE_DISABLE = 0,
	DWB_FRAME_CAPTURE_ENABLE = 1,
पूर्ण;

क्रमागत wbscl_coef_filter_type_sel अणु
	WBSCL_COEF_LUMA_VERT_FILTER = 0,
	WBSCL_COEF_CHROMA_VERT_FILTER = 1,
	WBSCL_COEF_LUMA_HORZ_FILTER = 2,
	WBSCL_COEF_CHROMA_HORZ_FILTER = 3
पूर्ण;


#अगर defined(CONFIG_DRM_AMD_DC_DCN)
क्रमागत dwb_boundary_mode अणु
	DWBSCL_BOUNDARY_MODE_EDGE  = 0,
	DWBSCL_BOUNDARY_MODE_BLACK = 1
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
क्रमागत dwb_output_csc_mode अणु
	DWB_OUTPUT_CSC_DISABLE = 0,
	DWB_OUTPUT_CSC_COEF_A = 1,
	DWB_OUTPUT_CSC_COEF_B = 2
पूर्ण;

क्रमागत dwb_ogam_lut_mode अणु
	DWB_OGAM_MODE_BYPASS,
	DWB_OGAM_RAMA_LUT,
	DWB_OGAM_RAMB_LUT
पूर्ण;

क्रमागत dwb_color_volume अणु
	DWB_SRGB_BT709 = 0,	//SDR
	DWB_PQ = 1,	//HDR
	DWB_HLG = 2,	//HDR
पूर्ण;

क्रमागत dwb_color_space अणु
	DWB_SRGB = 0,	//SDR
	DWB_BT709 = 1,	//SDR
	DWB_BT2020 = 2,	//HDR
पूर्ण;

काष्ठा dwb_efc_hdr_metadata अणु
	/*display chromaticities and white poपूर्णांक in units of 0.00001 */
	अचिन्हित पूर्णांक	chromaticity_green_x;
	अचिन्हित पूर्णांक	chromaticity_green_y;
	अचिन्हित पूर्णांक	chromaticity_blue_x;
	अचिन्हित पूर्णांक	chromaticity_blue_y;
	अचिन्हित पूर्णांक	chromaticity_red_x;
	अचिन्हित पूर्णांक	chromaticity_red_y;
	अचिन्हित पूर्णांक	chromaticity_white_poपूर्णांक_x;
	अचिन्हित पूर्णांक	chromaticity_white_poपूर्णांक_y;

	/*in units of candelas per square meter */
	अचिन्हित पूर्णांक	min_luminance;
	अचिन्हित पूर्णांक	max_luminance;

	/*in units of nits */
	अचिन्हित पूर्णांक	maximum_content_light_level;
	अचिन्हित पूर्णांक	maximum_frame_average_light_level;
पूर्ण;

काष्ठा dwb_efc_display_settings अणु
	अचिन्हित पूर्णांक	inputColorVolume;
	अचिन्हित पूर्णांक	inputColorSpace;
	अचिन्हित पूर्णांक	inputBitDepthMinus8;
	काष्ठा dwb_efc_hdr_metadata	hdr_metadata;
	अचिन्हित पूर्णांक	dwbOutputBlack;	// 0 - Normal, 1 - Output Black
पूर्ण;

#पूर्ण_अगर
काष्ठा dwb_warmup_params अणु
	bool	warmup_en;	/* false: normal mode, true: enable pattern generator */
	bool	warmup_mode;	/* false: 420, true: 444 */
	bool	warmup_depth;	/* false: 8bit, true: 10bit */
	पूर्णांक	warmup_data;	/* Data to be sent by pattern generator (same क्रम each pixel component) */
	पूर्णांक	warmup_width;	/* Pattern width (pixels) */
	पूर्णांक	warmup_height;	/* Pattern height (lines) */
पूर्ण;

काष्ठा dwb_caps अणु
	क्रमागत dce_version hw_version;	/* DCN engine version. */
	क्रमागत dwb_sw_version sw_version;	/* DWB sw implementation version. */
	अचिन्हित पूर्णांक	reserved[6];	/* Reserved क्रम future use, MUST BE 0. */
	अचिन्हित पूर्णांक	adapter_id;
	अचिन्हित पूर्णांक	num_pipes;	/* number of DWB pipes */
	काष्ठा अणु
		अचिन्हित पूर्णांक support_dwb	:1;
		अचिन्हित पूर्णांक support_ogam	:1;
		अचिन्हित पूर्णांक support_wbscl	:1;
		अचिन्हित पूर्णांक support_ocsc	:1;
		अचिन्हित पूर्णांक support_stereo :1;
	पूर्ण caps;
	अचिन्हित पूर्णांक	 reserved2[9];	/* Reserved क्रम future use, MUST BE 0. */
पूर्ण;

काष्ठा dwbc अणु
	स्थिर काष्ठा dwbc_funcs *funcs;
	काष्ठा dc_context *ctx;
	पूर्णांक inst;
	काष्ठा mcअगर_wb *mcअगर;
	bool status;
	पूर्णांक inputSrcSelect;
	bool dwb_output_black;
	क्रमागत dc_transfer_func_predefined tf;
	क्रमागत dc_color_space output_color_space;
	bool dwb_is_efc_transition;
	bool dwb_is_drc;
	पूर्णांक wb_src_plane_inst;/*hubp, mpcc, inst*/
	bool update_privacymask;
	uपूर्णांक32_t mask_id;
        पूर्णांक otg_inst;
        bool mvc_cfg;
पूर्ण;

काष्ठा dwbc_funcs अणु
	bool (*get_caps)(
		काष्ठा dwbc *dwbc,
		काष्ठा dwb_caps *caps);

	bool (*enable)(
		काष्ठा dwbc *dwbc,
		काष्ठा dc_dwb_params *params);

	bool (*disable)(काष्ठा dwbc *dwbc);

	bool (*update)(
		काष्ठा dwbc *dwbc,
		काष्ठा dc_dwb_params *params);

	bool (*is_enabled)(
		काष्ठा dwbc *dwbc);

	व्योम (*set_stereo)(
		काष्ठा dwbc *dwbc,
		काष्ठा dwb_stereo_params *stereo_params);

	व्योम (*set_new_content)(
		काष्ठा dwbc *dwbc,
		bool is_new_content);


	व्योम (*set_warmup)(
		काष्ठा dwbc *dwbc,
		काष्ठा dwb_warmup_params *warmup_params);


#अगर defined(CONFIG_DRM_AMD_DC_DCN)

	व्योम (*dwb_program_output_csc)(
		काष्ठा dwbc *dwbc,
		क्रमागत dc_color_space color_space,
		क्रमागत dwb_output_csc_mode mode);

	bool (*dwb_ogam_set_output_transfer_func)(
		काष्ठा dwbc *dwbc,
		स्थिर काष्ठा dc_transfer_func *in_transfer_func_dwb_ogam);

	व्योम (*get_privacy_mask)(
		काष्ठा dwbc *dwbc, uपूर्णांक32_t *mask_id);

	व्योम (*set_privacy_mask)(
		काष्ठा dwbc *dwbc, uपूर्णांक32_t mask_id);

	//TODO: merge with output_transfer_func?
	bool (*dwb_ogam_set_input_transfer_func)(
		काष्ठा dwbc *dwbc,
		स्थिर काष्ठा dc_transfer_func *in_transfer_func_dwb_ogam);
#पूर्ण_अगर
	bool (*get_dwb_status)(
		काष्ठा dwbc *dwbc);
	व्योम (*dwb_set_scaler)(
		काष्ठा dwbc *dwbc,
		काष्ठा dc_dwb_params *params);
पूर्ण;

#पूर्ण_अगर
