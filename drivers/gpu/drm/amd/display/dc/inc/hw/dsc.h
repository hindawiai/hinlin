<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __DAL_DSC_H__
#घोषणा __DAL_DSC_H__

#समावेश "dc_dsc.h"
#समावेश "dc_hw_types.h"
#समावेश "dc_types.h"
/* करो not include any other headers
 * or अन्यथा it might अवरोध Edid Utility functionality.
 */


/* Input parameters क्रम configuring DSC from the outside of DSC */
काष्ठा dsc_config अणु
	uपूर्णांक32_t pic_width;
	uपूर्णांक32_t pic_height;
	क्रमागत dc_pixel_encoding pixel_encoding;
	क्रमागत dc_color_depth color_depth;  /* Bits per component */
	bool is_odm;
	काष्ठा dc_dsc_config dc_dsc_cfg;
पूर्ण;


/* Output parameters क्रम configuring DSC-related part of OPTC */
काष्ठा dsc_optc_config अणु
	uपूर्णांक32_t slice_width; /* Slice width in pixels */
	uपूर्णांक32_t bytes_per_pixel; /* Bytes per pixel in u3.28 क्रमmat */
	bool is_pixel_क्रमmat_444; /* 'true' if pixel format is 'RGB 444' or 'Simple YCbCr 4:2:2' (4:2:2 upsampled to 4:4:4)' */
पूर्ण;


काष्ठा dcn_dsc_state अणु
	uपूर्णांक32_t dsc_घड़ी_en;
	uपूर्णांक32_t dsc_slice_width;
	uपूर्णांक32_t dsc_bits_per_pixel;
	uपूर्णांक32_t dsc_slice_height;
	uपूर्णांक32_t dsc_pic_width;
	uपूर्णांक32_t dsc_pic_height;
	uपूर्णांक32_t dsc_slice_bpg_offset;
	uपूर्णांक32_t dsc_chunk_size;
पूर्ण;


/* DSC encoder capabilities
 * They dअगरfer from the DPCD DSC caps because they are based on AMD DSC encoder caps.
 */
जोड़ dsc_enc_slice_caps अणु
	काष्ठा अणु
		uपूर्णांक8_t NUM_SLICES_1 : 1;
		uपूर्णांक8_t NUM_SLICES_2 : 1;
		uपूर्णांक8_t NUM_SLICES_3 : 1; /* This one is not per DSC spec, but our encoder supports it */
		uपूर्णांक8_t NUM_SLICES_4 : 1;
		uपूर्णांक8_t NUM_SLICES_8 : 1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

काष्ठा dsc_enc_caps अणु
	uपूर्णांक8_t dsc_version;
	जोड़ dsc_enc_slice_caps slice_caps;
	पूर्णांक32_t lb_bit_depth;
	bool is_block_pred_supported;
	जोड़ dsc_color_क्रमmats color_क्रमmats;
	जोड़ dsc_color_depth color_depth;
	पूर्णांक32_t max_total_throughput_mps; /* Maximum total throughput with all the slices combined */
	पूर्णांक32_t max_slice_width;
	uपूर्णांक32_t bpp_increment_भाग; /* bpp increment भागisor, e.g. अगर 16, it's 1/16th of a bit */
पूर्ण;

काष्ठा dsc_funcs अणु
	व्योम (*dsc_get_enc_caps)(काष्ठा dsc_enc_caps *dsc_enc_caps, पूर्णांक pixel_घड़ी_100Hz);
	व्योम (*dsc_पढ़ो_state)(काष्ठा display_stream_compressor *dsc, काष्ठा dcn_dsc_state *s);
	bool (*dsc_validate_stream)(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg);
	व्योम (*dsc_set_config)(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg,
			काष्ठा dsc_optc_config *dsc_optc_cfg);
	bool (*dsc_get_packed_pps)(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg,
			uपूर्णांक8_t *dsc_packed_pps);
	व्योम (*dsc_enable)(काष्ठा display_stream_compressor *dsc, पूर्णांक opp_pipe);
	व्योम (*dsc_disable)(काष्ठा display_stream_compressor *dsc);
पूर्ण;

#पूर्ण_अगर
