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

#समावेश <linux/slab.h>

#समावेश "resource.h"
#समावेश "dm_services.h"
#समावेश "dce_calcs.h"
#समावेश "dc.h"
#समावेश "core_types.h"
#समावेश "dal_asic_id.h"
#समावेश "calcs_logger.h"

/*
 * NOTE:
 *   This file is gcc-parseable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */

/*******************************************************************************
 * Private Functions
 ******************************************************************************/

अटल क्रमागत bw_calcs_version bw_calcs_version_from_asic_id(काष्ठा hw_asic_id asic_id)
अणु
	चयन (asic_id.chip_family) अणु

	हाल FAMILY_CZ:
		अगर (ASIC_REV_IS_STONEY(asic_id.hw_पूर्णांकernal_rev))
			वापस BW_CALCS_VERSION_STONEY;
		वापस BW_CALCS_VERSION_CARRIZO;

	हाल FAMILY_VI:
		अगर (ASIC_REV_IS_POLARIS12_V(asic_id.hw_पूर्णांकernal_rev))
			वापस BW_CALCS_VERSION_POLARIS12;
		अगर (ASIC_REV_IS_POLARIS10_P(asic_id.hw_पूर्णांकernal_rev))
			वापस BW_CALCS_VERSION_POLARIS10;
		अगर (ASIC_REV_IS_POLARIS11_M(asic_id.hw_पूर्णांकernal_rev))
			वापस BW_CALCS_VERSION_POLARIS11;
		अगर (ASIC_REV_IS_VEGAM(asic_id.hw_पूर्णांकernal_rev))
			वापस BW_CALCS_VERSION_VEGAM;
		वापस BW_CALCS_VERSION_INVALID;

	हाल FAMILY_AI:
		वापस BW_CALCS_VERSION_VEGA10;

	शेष:
		वापस BW_CALCS_VERSION_INVALID;
	पूर्ण
पूर्ण

अटल व्योम calculate_bandwidth(
	स्थिर काष्ठा bw_calcs_dceip *dceip,
	स्थिर काष्ठा bw_calcs_vbios *vbios,
	काष्ठा bw_calcs_data *data)

अणु
	स्थिर पूर्णांक32_t pixels_per_chunk = 512;
	स्थिर पूर्णांक32_t high = 2;
	स्थिर पूर्णांक32_t mid = 1;
	स्थिर पूर्णांक32_t low = 0;
	स्थिर uपूर्णांक32_t s_low = 0;
	स्थिर uपूर्णांक32_t s_mid1 = 1;
	स्थिर uपूर्णांक32_t s_mid2 = 2;
	स्थिर uपूर्णांक32_t s_mid3 = 3;
	स्थिर uपूर्णांक32_t s_mid4 = 4;
	स्थिर uपूर्णांक32_t s_mid5 = 5;
	स्थिर uपूर्णांक32_t s_mid6 = 6;
	स्थिर uपूर्णांक32_t s_high = 7;
	स्थिर uपूर्णांक32_t dmअगर_chunk_buff_margin = 1;

	uपूर्णांक32_t max_chunks_fbc_mode;
	पूर्णांक32_t num_cursor_lines;

	पूर्णांक32_t i, j, k;
	काष्ठा bw_fixed *yclk;
	काष्ठा bw_fixed *sclk;
	bool d0_underlay_enable;
	bool d1_underlay_enable;
	bool fbc_enabled;
	bool lpt_enabled;
	क्रमागत bw_defines sclk_message;
	क्रमागत bw_defines yclk_message;
	क्रमागत bw_defines *tiling_mode;
	क्रमागत bw_defines *surface_type;
	क्रमागत bw_defines voltage;
	क्रमागत bw_defines pipe_check;
	क्रमागत bw_defines hsr_check;
	क्रमागत bw_defines vsr_check;
	क्रमागत bw_defines lb_size_check;
	क्रमागत bw_defines fbc_check;
	क्रमागत bw_defines rotation_check;
	क्रमागत bw_defines mode_check;
	क्रमागत bw_defines nbp_state_change_enable_blank;
	/*initialize variables*/
	पूर्णांक32_t number_of_displays_enabled = 0;
	पूर्णांक32_t number_of_displays_enabled_with_margin = 0;
	पूर्णांक32_t number_of_aligned_displays_with_no_margin = 0;

	yclk = kसुस्मृति(3, माप(*yclk), GFP_KERNEL);
	अगर (!yclk)
		वापस;

	sclk = kसुस्मृति(8, माप(*sclk), GFP_KERNEL);
	अगर (!sclk)
		जाओ मुक्त_yclk;

	tiling_mode = kसुस्मृति(maximum_number_of_surfaces, माप(*tiling_mode), GFP_KERNEL);
	अगर (!tiling_mode)
		जाओ मुक्त_sclk;

	surface_type = kसुस्मृति(maximum_number_of_surfaces, माप(*surface_type), GFP_KERNEL);
	अगर (!surface_type)
		जाओ मुक्त_tiling_mode;

	yclk[low] = vbios->low_yclk;
	yclk[mid] = vbios->mid_yclk;
	yclk[high] = vbios->high_yclk;
	sclk[s_low] = vbios->low_sclk;
	sclk[s_mid1] = vbios->mid1_sclk;
	sclk[s_mid2] = vbios->mid2_sclk;
	sclk[s_mid3] = vbios->mid3_sclk;
	sclk[s_mid4] = vbios->mid4_sclk;
	sclk[s_mid5] = vbios->mid5_sclk;
	sclk[s_mid6] = vbios->mid6_sclk;
	sclk[s_high] = vbios->high_sclk;
	/*''''''''''''''''''*/
	/* surface assignment:*/
	/* 0: d0 underlay or underlay luma*/
	/* 1: d0 underlay chroma*/
	/* 2: d1 underlay or underlay luma*/
	/* 3: d1 underlay chroma*/
	/* 4: d0 graphics*/
	/* 5: d1 graphics*/
	/* 6: d2 graphics*/
	/* 7: d3 graphics, same mode as d2*/
	/* 8: d4 graphics, same mode as d2*/
	/* 9: d5 graphics, same mode as d2*/
	/* ...*/
	/* maximum_number_of_surfaces-2: d1 display_ग_लिखो_back420 luma*/
	/* maximum_number_of_surfaces-1: d1 display_ग_लिखो_back420 chroma*/
	/* underlay luma and chroma surface parameters from spपढ़ोsheet*/




	अगर (data->d0_underlay_mode == bw_def_none)
		d0_underlay_enable = false;
	अन्यथा
		d0_underlay_enable = true;
	अगर (data->d1_underlay_mode == bw_def_none)
		d1_underlay_enable = false;
	अन्यथा
		d1_underlay_enable = true;
	data->number_of_underlay_surfaces = d0_underlay_enable + d1_underlay_enable;
	चयन (data->underlay_surface_type) अणु
	हाल bw_def_420:
		surface_type[0] = bw_def_underlay420_luma;
		surface_type[2] = bw_def_underlay420_luma;
		data->bytes_per_pixel[0] = 1;
		data->bytes_per_pixel[2] = 1;
		surface_type[1] = bw_def_underlay420_chroma;
		surface_type[3] = bw_def_underlay420_chroma;
		data->bytes_per_pixel[1] = 2;
		data->bytes_per_pixel[3] = 2;
		data->lb_size_per_component[0] = dceip->underlay420_luma_lb_size_per_component;
		data->lb_size_per_component[1] = dceip->underlay420_chroma_lb_size_per_component;
		data->lb_size_per_component[2] = dceip->underlay420_luma_lb_size_per_component;
		data->lb_size_per_component[3] = dceip->underlay420_chroma_lb_size_per_component;
		अवरोध;
	हाल bw_def_422:
		surface_type[0] = bw_def_underlay422;
		surface_type[2] = bw_def_underlay422;
		data->bytes_per_pixel[0] = 2;
		data->bytes_per_pixel[2] = 2;
		data->lb_size_per_component[0] = dceip->underlay422_lb_size_per_component;
		data->lb_size_per_component[2] = dceip->underlay422_lb_size_per_component;
		अवरोध;
	शेष:
		surface_type[0] = bw_def_underlay444;
		surface_type[2] = bw_def_underlay444;
		data->bytes_per_pixel[0] = 4;
		data->bytes_per_pixel[2] = 4;
		data->lb_size_per_component[0] = dceip->lb_size_per_component444;
		data->lb_size_per_component[2] = dceip->lb_size_per_component444;
		अवरोध;
	पूर्ण
	अगर (d0_underlay_enable) अणु
		चयन (data->underlay_surface_type) अणु
		हाल bw_def_420:
			data->enable[0] = 1;
			data->enable[1] = 1;
			अवरोध;
		शेष:
			data->enable[0] = 1;
			data->enable[1] = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		data->enable[0] = 0;
		data->enable[1] = 0;
	पूर्ण
	अगर (d1_underlay_enable) अणु
		चयन (data->underlay_surface_type) अणु
		हाल bw_def_420:
			data->enable[2] = 1;
			data->enable[3] = 1;
			अवरोध;
		शेष:
			data->enable[2] = 1;
			data->enable[3] = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		data->enable[2] = 0;
		data->enable[3] = 0;
	पूर्ण
	data->use_alpha[0] = 0;
	data->use_alpha[1] = 0;
	data->use_alpha[2] = 0;
	data->use_alpha[3] = 0;
	data->scatter_gather_enable_क्रम_pipe[0] = vbios->scatter_gather_enable;
	data->scatter_gather_enable_क्रम_pipe[1] = vbios->scatter_gather_enable;
	data->scatter_gather_enable_क्रम_pipe[2] = vbios->scatter_gather_enable;
	data->scatter_gather_enable_क्रम_pipe[3] = vbios->scatter_gather_enable;
	/*underlay0 same and graphics display pipe0*/
	data->पूर्णांकerlace_mode[0] = data->पूर्णांकerlace_mode[4];
	data->पूर्णांकerlace_mode[1] = data->पूर्णांकerlace_mode[4];
	/*underlay1 same and graphics display pipe1*/
	data->पूर्णांकerlace_mode[2] = data->पूर्णांकerlace_mode[5];
	data->पूर्णांकerlace_mode[3] = data->पूर्णांकerlace_mode[5];
	/*underlay0 same and graphics display pipe0*/
	data->h_total[0] = data->h_total[4];
	data->v_total[0] = data->v_total[4];
	data->h_total[1] = data->h_total[4];
	data->v_total[1] = data->v_total[4];
	/*underlay1 same and graphics display pipe1*/
	data->h_total[2] = data->h_total[5];
	data->v_total[2] = data->v_total[5];
	data->h_total[3] = data->h_total[5];
	data->v_total[3] = data->v_total[5];
	/*underlay0 same and graphics display pipe0*/
	data->pixel_rate[0] = data->pixel_rate[4];
	data->pixel_rate[1] = data->pixel_rate[4];
	/*underlay1 same and graphics display pipe1*/
	data->pixel_rate[2] = data->pixel_rate[5];
	data->pixel_rate[3] = data->pixel_rate[5];
	अगर ((data->underlay_tiling_mode == bw_def_array_linear_general || data->underlay_tiling_mode == bw_def_array_linear_aligned)) अणु
		tiling_mode[0] = bw_def_linear;
		tiling_mode[1] = bw_def_linear;
		tiling_mode[2] = bw_def_linear;
		tiling_mode[3] = bw_def_linear;
	पूर्ण
	अन्यथा अणु
		tiling_mode[0] = bw_def_landscape;
		tiling_mode[1] = bw_def_landscape;
		tiling_mode[2] = bw_def_landscape;
		tiling_mode[3] = bw_def_landscape;
	पूर्ण
	data->lb_bpc[0] = data->underlay_lb_bpc;
	data->lb_bpc[1] = data->underlay_lb_bpc;
	data->lb_bpc[2] = data->underlay_lb_bpc;
	data->lb_bpc[3] = data->underlay_lb_bpc;
	data->compression_rate[0] = bw_पूर्णांक_to_fixed(1);
	data->compression_rate[1] = bw_पूर्णांक_to_fixed(1);
	data->compression_rate[2] = bw_पूर्णांक_to_fixed(1);
	data->compression_rate[3] = bw_पूर्णांक_to_fixed(1);
	data->access_one_channel_only[0] = 0;
	data->access_one_channel_only[1] = 0;
	data->access_one_channel_only[2] = 0;
	data->access_one_channel_only[3] = 0;
	data->cursor_width_pixels[0] = bw_पूर्णांक_to_fixed(0);
	data->cursor_width_pixels[1] = bw_पूर्णांक_to_fixed(0);
	data->cursor_width_pixels[2] = bw_पूर्णांक_to_fixed(0);
	data->cursor_width_pixels[3] = bw_पूर्णांक_to_fixed(0);
	/* graphics surface parameters from spपढ़ोsheet*/
	fbc_enabled = false;
	lpt_enabled = false;
	क्रम (i = 4; i <= maximum_number_of_surfaces - 3; i++) अणु
		अगर (i < data->number_of_displays + 4) अणु
			अगर (i == 4 && data->d0_underlay_mode == bw_def_underlay_only) अणु
				data->enable[i] = 0;
				data->use_alpha[i] = 0;
			पूर्ण
			अन्यथा अगर (i == 4 && data->d0_underlay_mode == bw_def_blend) अणु
				data->enable[i] = 1;
				data->use_alpha[i] = 1;
			पूर्ण
			अन्यथा अगर (i == 4) अणु
				data->enable[i] = 1;
				data->use_alpha[i] = 0;
			पूर्ण
			अन्यथा अगर (i == 5 && data->d1_underlay_mode == bw_def_underlay_only) अणु
				data->enable[i] = 0;
				data->use_alpha[i] = 0;
			पूर्ण
			अन्यथा अगर (i == 5 && data->d1_underlay_mode == bw_def_blend) अणु
				data->enable[i] = 1;
				data->use_alpha[i] = 1;
			पूर्ण
			अन्यथा अणु
				data->enable[i] = 1;
				data->use_alpha[i] = 0;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			data->enable[i] = 0;
			data->use_alpha[i] = 0;
		पूर्ण
		data->scatter_gather_enable_क्रम_pipe[i] = vbios->scatter_gather_enable;
		surface_type[i] = bw_def_graphics;
		data->lb_size_per_component[i] = dceip->lb_size_per_component444;
		अगर (data->graphics_tiling_mode == bw_def_array_linear_general || data->graphics_tiling_mode == bw_def_array_linear_aligned) अणु
			tiling_mode[i] = bw_def_linear;
		पूर्ण
		अन्यथा अणु
			tiling_mode[i] = bw_def_tiled;
		पूर्ण
		data->lb_bpc[i] = data->graphics_lb_bpc;
		अगर ((data->fbc_en[i] == 1 && (dceip->argb_compression_support || data->d0_underlay_mode != bw_def_blended))) अणु
			data->compression_rate[i] = bw_पूर्णांक_to_fixed(vbios->average_compression_rate);
			data->access_one_channel_only[i] = data->lpt_en[i];
		पूर्ण
		अन्यथा अणु
			data->compression_rate[i] = bw_पूर्णांक_to_fixed(1);
			data->access_one_channel_only[i] = 0;
		पूर्ण
		अगर (data->fbc_en[i] == 1) अणु
			fbc_enabled = true;
			अगर (data->lpt_en[i] == 1) अणु
				lpt_enabled = true;
			पूर्ण
		पूर्ण
		data->cursor_width_pixels[i] = bw_पूर्णांक_to_fixed(vbios->cursor_width);
	पूर्ण
	/* display_ग_लिखो_back420*/
	data->scatter_gather_enable_क्रम_pipe[maximum_number_of_surfaces - 2] = 0;
	data->scatter_gather_enable_क्रम_pipe[maximum_number_of_surfaces - 1] = 0;
	अगर (data->d1_display_ग_लिखो_back_dwb_enable == 1) अणु
		data->enable[maximum_number_of_surfaces - 2] = 1;
		data->enable[maximum_number_of_surfaces - 1] = 1;
	पूर्ण
	अन्यथा अणु
		data->enable[maximum_number_of_surfaces - 2] = 0;
		data->enable[maximum_number_of_surfaces - 1] = 0;
	पूर्ण
	surface_type[maximum_number_of_surfaces - 2] = bw_def_display_ग_लिखो_back420_luma;
	surface_type[maximum_number_of_surfaces - 1] = bw_def_display_ग_लिखो_back420_chroma;
	data->lb_size_per_component[maximum_number_of_surfaces - 2] = dceip->underlay420_luma_lb_size_per_component;
	data->lb_size_per_component[maximum_number_of_surfaces - 1] = dceip->underlay420_chroma_lb_size_per_component;
	data->bytes_per_pixel[maximum_number_of_surfaces - 2] = 1;
	data->bytes_per_pixel[maximum_number_of_surfaces - 1] = 2;
	data->पूर्णांकerlace_mode[maximum_number_of_surfaces - 2] = data->पूर्णांकerlace_mode[5];
	data->पूर्णांकerlace_mode[maximum_number_of_surfaces - 1] = data->पूर्णांकerlace_mode[5];
	data->h_taps[maximum_number_of_surfaces - 2] = bw_पूर्णांक_to_fixed(1);
	data->h_taps[maximum_number_of_surfaces - 1] = bw_पूर्णांक_to_fixed(1);
	data->v_taps[maximum_number_of_surfaces - 2] = bw_पूर्णांक_to_fixed(1);
	data->v_taps[maximum_number_of_surfaces - 1] = bw_पूर्णांक_to_fixed(1);
	data->rotation_angle[maximum_number_of_surfaces - 2] = bw_पूर्णांक_to_fixed(0);
	data->rotation_angle[maximum_number_of_surfaces - 1] = bw_पूर्णांक_to_fixed(0);
	tiling_mode[maximum_number_of_surfaces - 2] = bw_def_linear;
	tiling_mode[maximum_number_of_surfaces - 1] = bw_def_linear;
	data->lb_bpc[maximum_number_of_surfaces - 2] = 8;
	data->lb_bpc[maximum_number_of_surfaces - 1] = 8;
	data->compression_rate[maximum_number_of_surfaces - 2] = bw_पूर्णांक_to_fixed(1);
	data->compression_rate[maximum_number_of_surfaces - 1] = bw_पूर्णांक_to_fixed(1);
	data->access_one_channel_only[maximum_number_of_surfaces - 2] = 0;
	data->access_one_channel_only[maximum_number_of_surfaces - 1] = 0;
	/*assume display pipe1 has dwb enabled*/
	data->h_total[maximum_number_of_surfaces - 2] = data->h_total[5];
	data->h_total[maximum_number_of_surfaces - 1] = data->h_total[5];
	data->v_total[maximum_number_of_surfaces - 2] = data->v_total[5];
	data->v_total[maximum_number_of_surfaces - 1] = data->v_total[5];
	data->pixel_rate[maximum_number_of_surfaces - 2] = data->pixel_rate[5];
	data->pixel_rate[maximum_number_of_surfaces - 1] = data->pixel_rate[5];
	data->src_width[maximum_number_of_surfaces - 2] = data->src_width[5];
	data->src_width[maximum_number_of_surfaces - 1] = data->src_width[5];
	data->src_height[maximum_number_of_surfaces - 2] = data->src_height[5];
	data->src_height[maximum_number_of_surfaces - 1] = data->src_height[5];
	data->pitch_in_pixels[maximum_number_of_surfaces - 2] = data->src_width[5];
	data->pitch_in_pixels[maximum_number_of_surfaces - 1] = data->src_width[5];
	data->h_scale_ratio[maximum_number_of_surfaces - 2] = bw_पूर्णांक_to_fixed(1);
	data->h_scale_ratio[maximum_number_of_surfaces - 1] = bw_पूर्णांक_to_fixed(1);
	data->v_scale_ratio[maximum_number_of_surfaces - 2] = bw_पूर्णांक_to_fixed(1);
	data->v_scale_ratio[maximum_number_of_surfaces - 1] = bw_पूर्णांक_to_fixed(1);
	data->stereo_mode[maximum_number_of_surfaces - 2] = bw_def_mono;
	data->stereo_mode[maximum_number_of_surfaces - 1] = bw_def_mono;
	data->cursor_width_pixels[maximum_number_of_surfaces - 2] = bw_पूर्णांक_to_fixed(0);
	data->cursor_width_pixels[maximum_number_of_surfaces - 1] = bw_पूर्णांक_to_fixed(0);
	data->use_alpha[maximum_number_of_surfaces - 2] = 0;
	data->use_alpha[maximum_number_of_surfaces - 1] = 0;
	/*mode check calculations:*/
	/* mode within dce ip capabilities*/
	/* fbc*/
	/* hsr*/
	/* vsr*/
	/* lb size*/
	/*effective scaling source and ratios:*/
	/*क्रम graphics, non-stereo, non-पूर्णांकerlace surfaces when the size of the source and destination are the same, only one tap is used*/
	/*420 chroma has half the width, height, horizontal and vertical scaling ratios than luma*/
	/*rotating a graphic or underlay surface swaps the width, height, horizontal and vertical scaling ratios*/
	/*in top-bottom stereo mode there is 2:1 vertical करोwnscaling क्रम each eye*/
	/*in side-by-side stereo mode there is 2:1 horizontal करोwnscaling क्रम each eye*/
	/*in पूर्णांकerlace mode there is 2:1 vertical करोwnscaling क्रम each field*/
	/*in panning or bezel adjusपंचांगent mode the source width has an extra 128 pixels*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_equ(data->h_scale_ratio[i], bw_पूर्णांक_to_fixed(1)) && bw_equ(data->v_scale_ratio[i], bw_पूर्णांक_to_fixed(1)) && surface_type[i] == bw_def_graphics && data->stereo_mode[i] == bw_def_mono && data->पूर्णांकerlace_mode[i] == 0) अणु
				data->h_taps[i] = bw_पूर्णांक_to_fixed(1);
				data->v_taps[i] = bw_पूर्णांक_to_fixed(1);
			पूर्ण
			अगर (surface_type[i] == bw_def_display_ग_लिखो_back420_chroma || surface_type[i] == bw_def_underlay420_chroma) अणु
				data->pitch_in_pixels_after_surface_type[i] = bw_भाग(data->pitch_in_pixels[i], bw_पूर्णांक_to_fixed(2));
				data->src_width_after_surface_type = bw_भाग(data->src_width[i], bw_पूर्णांक_to_fixed(2));
				data->src_height_after_surface_type = bw_भाग(data->src_height[i], bw_पूर्णांक_to_fixed(2));
				data->hsr_after_surface_type = bw_भाग(data->h_scale_ratio[i], bw_पूर्णांक_to_fixed(2));
				data->vsr_after_surface_type = bw_भाग(data->v_scale_ratio[i], bw_पूर्णांक_to_fixed(2));
			पूर्ण
			अन्यथा अणु
				data->pitch_in_pixels_after_surface_type[i] = data->pitch_in_pixels[i];
				data->src_width_after_surface_type = data->src_width[i];
				data->src_height_after_surface_type = data->src_height[i];
				data->hsr_after_surface_type = data->h_scale_ratio[i];
				data->vsr_after_surface_type = data->v_scale_ratio[i];
			पूर्ण
			अगर ((bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(90)) || bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(270))) && surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->src_width_after_rotation = data->src_height_after_surface_type;
				data->src_height_after_rotation = data->src_width_after_surface_type;
				data->hsr_after_rotation = data->vsr_after_surface_type;
				data->vsr_after_rotation = data->hsr_after_surface_type;
			पूर्ण
			अन्यथा अणु
				data->src_width_after_rotation = data->src_width_after_surface_type;
				data->src_height_after_rotation = data->src_height_after_surface_type;
				data->hsr_after_rotation = data->hsr_after_surface_type;
				data->vsr_after_rotation = data->vsr_after_surface_type;
			पूर्ण
			चयन (data->stereo_mode[i]) अणु
			हाल bw_def_top_bottom:
				data->source_width_pixels[i] = data->src_width_after_rotation;
				data->source_height_pixels = bw_mul(bw_पूर्णांक_to_fixed(2), data->src_height_after_rotation);
				data->hsr_after_stereo = data->hsr_after_rotation;
				data->vsr_after_stereo = bw_mul(bw_पूर्णांक_to_fixed(1), data->vsr_after_rotation);
				अवरोध;
			हाल bw_def_side_by_side:
				data->source_width_pixels[i] = bw_mul(bw_पूर्णांक_to_fixed(2), data->src_width_after_rotation);
				data->source_height_pixels = data->src_height_after_rotation;
				data->hsr_after_stereo = bw_mul(bw_पूर्णांक_to_fixed(1), data->hsr_after_rotation);
				data->vsr_after_stereo = data->vsr_after_rotation;
				अवरोध;
			शेष:
				data->source_width_pixels[i] = data->src_width_after_rotation;
				data->source_height_pixels = data->src_height_after_rotation;
				data->hsr_after_stereo = data->hsr_after_rotation;
				data->vsr_after_stereo = data->vsr_after_rotation;
				अवरोध;
			पूर्ण
			data->hsr[i] = data->hsr_after_stereo;
			अगर (data->पूर्णांकerlace_mode[i]) अणु
				data->vsr[i] = bw_mul(data->vsr_after_stereo, bw_पूर्णांक_to_fixed(2));
			पूर्ण
			अन्यथा अणु
				data->vsr[i] = data->vsr_after_stereo;
			पूर्ण
			अगर (data->panning_and_bezel_adjusपंचांगent != bw_def_none) अणु
				data->source_width_rounded_up_to_chunks[i] = bw_add(bw_न्यूनमान2(bw_sub(data->source_width_pixels[i], bw_पूर्णांक_to_fixed(1)), bw_पूर्णांक_to_fixed(128)), bw_पूर्णांक_to_fixed(256));
			पूर्ण
			अन्यथा अणु
				data->source_width_rounded_up_to_chunks[i] = bw_उच्चमान2(data->source_width_pixels[i], bw_पूर्णांक_to_fixed(128));
			पूर्ण
			data->source_height_rounded_up_to_chunks[i] = data->source_height_pixels;
		पूर्ण
	पूर्ण
	/*mode support checks:*/
	/*the number of graphics and underlay pipes is limited by the ip support*/
	/*maximum horizontal and vertical scale ratio is 4, and should not exceed the number of taps*/
	/*क्रम करोwnscaling with the pre-करोwnscaler, the horizontal scale ratio must be more than the उच्चमानing of one quarter of the number of taps*/
	/*the pre-करोwnscaler reduces the line buffer source by the horizontal scale ratio*/
	/*the number of lines in the line buffer has to exceed the number of vertical taps*/
	/*the size of the line in the line buffer is the product of the source width and the bits per component, rounded up to a multiple of 48*/
	/*the size of the line in the line buffer in the हाल of 10 bit per component is the product of the source width rounded up to multiple of 8 and 30.023438 / 3, rounded up to a multiple of 48*/
	/*the size of the line in the line buffer in the हाल of 8 bit per component is the product of the source width rounded up to multiple of 8 and 30.023438 / 3, rounded up to a multiple of 48*/
	/*frame buffer compression is not supported with stereo mode, rotation, or non- 888 क्रमmats*/
	/*rotation is not supported with linear of stereo modes*/
	अगर (dceip->number_of_graphics_pipes >= data->number_of_displays && dceip->number_of_underlay_pipes >= data->number_of_underlay_surfaces && !(dceip->display_ग_लिखो_back_supported == 0 && data->d1_display_ग_लिखो_back_dwb_enable == 1)) अणु
		pipe_check = bw_def_ok;
	पूर्ण
	अन्यथा अणु
		pipe_check = bw_def_notok;
	पूर्ण
	hsr_check = bw_def_ok;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_neq(data->hsr[i], bw_पूर्णांक_to_fixed(1))) अणु
				अगर (bw_mtn(data->hsr[i], bw_पूर्णांक_to_fixed(4))) अणु
					hsr_check = bw_def_hsr_mtn_4;
				पूर्ण
				अन्यथा अणु
					अगर (bw_mtn(data->hsr[i], data->h_taps[i])) अणु
						hsr_check = bw_def_hsr_mtn_h_taps;
					पूर्ण
					अन्यथा अणु
						अगर (dceip->pre_करोwnscaler_enabled == 1 && bw_mtn(data->hsr[i], bw_पूर्णांक_to_fixed(1)) && bw_leq(data->hsr[i], bw_उच्चमान2(bw_भाग(data->h_taps[i], bw_पूर्णांक_to_fixed(4)), bw_पूर्णांक_to_fixed(1)))) अणु
							hsr_check = bw_def_उच्चमानing__h_taps_भाग_4___meq_hsr;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	vsr_check = bw_def_ok;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_neq(data->vsr[i], bw_पूर्णांक_to_fixed(1))) अणु
				अगर (bw_mtn(data->vsr[i], bw_पूर्णांक_to_fixed(4))) अणु
					vsr_check = bw_def_vsr_mtn_4;
				पूर्ण
				अन्यथा अणु
					अगर (bw_mtn(data->vsr[i], data->v_taps[i])) अणु
						vsr_check = bw_def_vsr_mtn_v_taps;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	lb_size_check = bw_def_ok;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर ((dceip->pre_करोwnscaler_enabled && bw_mtn(data->hsr[i], bw_पूर्णांक_to_fixed(1)))) अणु
				data->source_width_in_lb = bw_भाग(data->source_width_pixels[i], data->hsr[i]);
			पूर्ण
			अन्यथा अणु
				data->source_width_in_lb = data->source_width_pixels[i];
			पूर्ण
			चयन (data->lb_bpc[i]) अणु
			हाल 8:
				data->lb_line_pitch = bw_उच्चमान2(bw_mul(bw_भाग(bw_frc_to_fixed(2401171875ul, 100000000), bw_पूर्णांक_to_fixed(3)), bw_उच्चमान2(data->source_width_in_lb, bw_पूर्णांक_to_fixed(8))), bw_पूर्णांक_to_fixed(48));
				अवरोध;
			हाल 10:
				data->lb_line_pitch = bw_उच्चमान2(bw_mul(bw_भाग(bw_frc_to_fixed(300234375, 10000000), bw_पूर्णांक_to_fixed(3)), bw_उच्चमान2(data->source_width_in_lb, bw_पूर्णांक_to_fixed(8))), bw_पूर्णांक_to_fixed(48));
				अवरोध;
			शेष:
				data->lb_line_pitch = bw_उच्चमान2(bw_mul(bw_पूर्णांक_to_fixed(data->lb_bpc[i]), data->source_width_in_lb), bw_पूर्णांक_to_fixed(48));
				अवरोध;
			पूर्ण
			data->lb_partitions[i] = bw_न्यूनमान2(bw_भाग(data->lb_size_per_component[i], data->lb_line_pitch), bw_पूर्णांक_to_fixed(1));
			/*clamp the partitions to the maxium number supported by the lb*/
			अगर ((surface_type[i] != bw_def_graphics || dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching == 1)) अणु
				data->lb_partitions_max[i] = bw_पूर्णांक_to_fixed(10);
			पूर्ण
			अन्यथा अणु
				data->lb_partitions_max[i] = bw_पूर्णांक_to_fixed(7);
			पूर्ण
			data->lb_partitions[i] = bw_min2(data->lb_partitions_max[i], data->lb_partitions[i]);
			अगर (bw_mtn(bw_add(data->v_taps[i], bw_पूर्णांक_to_fixed(1)), data->lb_partitions[i])) अणु
				lb_size_check = bw_def_notok;
			पूर्ण
		पूर्ण
	पूर्ण
	fbc_check = bw_def_ok;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i] && data->fbc_en[i] == 1 && (bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(90)) || bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(270)) || data->stereo_mode[i] != bw_def_mono || data->bytes_per_pixel[i] != 4)) अणु
			fbc_check = bw_def_invalid_rotation_or_bpp_or_stereo;
		पूर्ण
	पूर्ण
	rotation_check = bw_def_ok;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर ((bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(90)) || bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(270))) && (tiling_mode[i] == bw_def_linear || data->stereo_mode[i] != bw_def_mono)) अणु
				rotation_check = bw_def_invalid_linear_or_stereo_mode;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (pipe_check == bw_def_ok && hsr_check == bw_def_ok && vsr_check == bw_def_ok && lb_size_check == bw_def_ok && fbc_check == bw_def_ok && rotation_check == bw_def_ok) अणु
		mode_check = bw_def_ok;
	पूर्ण
	अन्यथा अणु
		mode_check = bw_def_notok;
	पूर्ण
	/*number of memory channels क्रम ग_लिखो-back client*/
	data->number_of_dram_wrchannels = vbios->number_of_dram_channels;
	data->number_of_dram_channels = vbios->number_of_dram_channels;
	/*modअगरy number of memory channels अगर lpt mode is enabled*/
	/* low घातer tiling mode रेजिस्टर*/
	/* 0 = use channel 0*/
	/* 1 = use channel 0 and 1*/
	/* 2 = use channel 0,1,2,3*/
	अगर ((fbc_enabled == 1 && lpt_enabled == 1)) अणु
		अगर (vbios->memory_type == bw_def_hbm)
			data->dram_efficiency = bw_frc_to_fixed(5, 10);
		अन्यथा
			data->dram_efficiency = bw_पूर्णांक_to_fixed(1);


		अगर (dceip->low_घातer_tiling_mode == 0) अणु
			data->number_of_dram_channels = 1;
		पूर्ण
		अन्यथा अगर (dceip->low_घातer_tiling_mode == 1) अणु
			data->number_of_dram_channels = 2;
		पूर्ण
		अन्यथा अगर (dceip->low_घातer_tiling_mode == 2) अणु
			data->number_of_dram_channels = 4;
		पूर्ण
		अन्यथा अणु
			data->number_of_dram_channels = 1;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (vbios->memory_type == bw_def_hbm)
			data->dram_efficiency = bw_frc_to_fixed(5, 10);
		अन्यथा
			data->dram_efficiency = bw_frc_to_fixed(8, 10);
	पूर्ण
	/*memory request size and latency hiding:*/
	/*request size is normally 64 byte, 2-line पूर्णांकerleaved, with full latency hiding*/
	/*the display ग_लिखो-back requests are single line*/
	/*क्रम tiled graphics surfaces, or undelay surfaces with width higher than the maximum size क्रम full efficiency, request size is 32 byte in 8 and 16 bpp or अगर the rotation is orthogonal to the tiling grain. only half is useful of the bytes in the request size in 8 bpp or in 32 bpp अगर the rotation is orthogonal to the tiling grain.*/
	/*क्रम undelay surfaces with width lower than the maximum size क्रम full efficiency, requests are 4-line पूर्णांकerleaved in 16bpp अगर the rotation is parallel to the tiling grain, and 8-line पूर्णांकerleaved with 4-line latency hiding in 8bpp or अगर the rotation is orthogonal to the tiling grain.*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर ((bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(90)) || bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(270)))) अणु
				अगर ((i < 4)) अणु
					/*underlay portrait tiling mode is not supported*/
					data->orthogonal_rotation[i] = 1;
				पूर्ण
				अन्यथा अणु
					/*graphics portrait tiling mode*/
					अगर (data->graphics_micro_tile_mode == bw_def_rotated_micro_tiling) अणु
						data->orthogonal_rotation[i] = 0;
					पूर्ण
					अन्यथा अणु
						data->orthogonal_rotation[i] = 1;
					पूर्ण
				पूर्ण
			पूर्ण
			अन्यथा अणु
				अगर ((i < 4)) अणु
					/*underlay landscape tiling mode is only supported*/
					अगर (data->underlay_micro_tile_mode == bw_def_display_micro_tiling) अणु
						data->orthogonal_rotation[i] = 0;
					पूर्ण
					अन्यथा अणु
						data->orthogonal_rotation[i] = 1;
					पूर्ण
				पूर्ण
				अन्यथा अणु
					/*graphics landscape tiling mode*/
					अगर (data->graphics_micro_tile_mode == bw_def_display_micro_tiling) अणु
						data->orthogonal_rotation[i] = 0;
					पूर्ण
					अन्यथा अणु
						data->orthogonal_rotation[i] = 1;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(90)) || bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(270))) अणु
				data->underlay_maximum_source_efficient_क्रम_tiling = dceip->underlay_maximum_height_efficient_क्रम_tiling;
			पूर्ण
			अन्यथा अणु
				data->underlay_maximum_source_efficient_क्रम_tiling = dceip->underlay_maximum_width_efficient_क्रम_tiling;
			पूर्ण
			अगर (surface_type[i] == bw_def_display_ग_लिखो_back420_luma || surface_type[i] == bw_def_display_ग_लिखो_back420_chroma) अणु
				data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
				data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
				data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(1);
				data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(1);
			पूर्ण
			अन्यथा अगर (tiling_mode[i] == bw_def_linear) अणु
				data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
				data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
				data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(2);
				data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(2);
			पूर्ण
			अन्यथा अणु
				अगर (surface_type[i] == bw_def_graphics || (bw_mtn(data->source_width_rounded_up_to_chunks[i], bw_उच्चमान2(data->underlay_maximum_source_efficient_क्रम_tiling, bw_पूर्णांक_to_fixed(256))))) अणु
					चयन (data->bytes_per_pixel[i]) अणु
					हाल 8:
						data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(2);
						data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(2);
						अगर (data->orthogonal_rotation[i]) अणु
							data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(32);
							data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(32);
						पूर्ण
						अन्यथा अणु
							data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
							data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
						पूर्ण
						अवरोध;
					हाल 4:
						अगर (data->orthogonal_rotation[i]) अणु
							data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(2);
							data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(2);
							data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(32);
							data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(16);
						पूर्ण
						अन्यथा अणु
							data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(2);
							data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(2);
							data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
							data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
						पूर्ण
						अवरोध;
					हाल 2:
						data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(2);
						data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(2);
						data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(32);
						data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(32);
						अवरोध;
					शेष:
						data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(2);
						data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(2);
						data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(32);
						data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(16);
						अवरोध;
					पूर्ण
				पूर्ण
				अन्यथा अणु
					data->bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
					data->useful_bytes_per_request[i] = bw_पूर्णांक_to_fixed(64);
					अगर (data->orthogonal_rotation[i]) अणु
						data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(8);
						data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(4);
					पूर्ण
					अन्यथा अणु
						चयन (data->bytes_per_pixel[i]) अणु
						हाल 4:
							data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(2);
							data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(2);
							अवरोध;
						हाल 2:
							data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(4);
							data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(4);
							अवरोध;
						शेष:
							data->lines_पूर्णांकerleaved_in_mem_access[i] = bw_पूर्णांक_to_fixed(8);
							data->latency_hiding_lines[i] = bw_पूर्णांक_to_fixed(4);
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*requested peak bandwidth:*/
	/*the peak request-per-second bandwidth is the product of the maximum source lines in per line out in the beginning*/
	/*and in the middle of the frame, the ratio of the source width to the line समय, the ratio of line पूर्णांकerleaving*/
	/*in memory to lines of latency hiding, and the ratio of bytes per pixel to useful bytes per request.*/
	/**/
	/*अगर the dmअगर data buffer size holds more than vta_ps worth of source lines, then only vsr is used.*/
	/*the peak bandwidth is the peak request-per-second bandwidth बार the request size.*/
	/**/
	/*the line buffer lines in per line out in the beginning of the frame is the vertical filter initialization value*/
	/*rounded up to even and भागided by the line बार क्रम initialization, which is normally three.*/
	/*the line buffer lines in per line out in the middle of the frame is at least one, or the vertical scale ratio,*/
	/*rounded up to line pairs अगर not करोing line buffer prefetching.*/
	/**/
	/*the non-prefetching rounding up of the vertical scale ratio can also be करोne up to 1 (क्रम a 0,2 pattern), 4/3 (क्रम a 0,2,2 pattern),*/
	/*6/4 (क्रम a 0,2,2,2 pattern), or 3 (क्रम a 2,4 pattern).*/
	/**/
	/*the scaler vertical filter initialization value is calculated by the hardware as the न्यूनमान of the average of the*/
	/*vertical scale ratio and the number of vertical taps increased by one.  add one more क्रम possible odd line*/
	/*panning/bezel adjusपंचांगent mode.*/
	/**/
	/*क्रम the bottom पूर्णांकerlace field an extra 50% of the vertical scale ratio is considered क्रम this calculation.*/
	/*in top-bottom stereo mode software has to set the filter initialization value manually and explicitly limit it to 4.*/
	/*furthermore, there is only one line समय क्रम initialization.*/
	/**/
	/*line buffer prefetching is करोne when the number of lines in the line buffer exceeds the number of taps plus*/
	/*the उच्चमानing of the vertical scale ratio.*/
	/**/
	/*multi-line buffer prefetching is only करोne in the graphics pipe when the scaler is disabled or when upscaling and the vsr <= 0.8.'*/
	/**/
	/*the horizontal blank and chunk granularity factor is indirectly used indicate the पूर्णांकerval of समय required to transfer the source pixels.*/
	/*the denominator of this term represents the total number of destination output pixels required क्रम the input source pixels.*/
	/*it applies when the lines in per line out is not 2 or 4.  it करोes not apply when there is a line buffer between the scl and blnd.*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->v_filter_init[i] = bw_न्यूनमान2(bw_भाग((bw_add(bw_add(bw_add(bw_पूर्णांक_to_fixed(1), data->v_taps[i]), data->vsr[i]), bw_mul(bw_mul(bw_पूर्णांक_to_fixed(data->पूर्णांकerlace_mode[i]), bw_frc_to_fixed(5, 10)), data->vsr[i]))), bw_पूर्णांक_to_fixed(2)), bw_पूर्णांक_to_fixed(1));
			अगर (data->panning_and_bezel_adjusपंचांगent == bw_def_any_lines) अणु
				data->v_filter_init[i] = bw_add(data->v_filter_init[i], bw_पूर्णांक_to_fixed(1));
			पूर्ण
			अगर (data->stereo_mode[i] == bw_def_top_bottom) अणु
				data->v_filter_init[i] = bw_min2(data->v_filter_init[i], bw_पूर्णांक_to_fixed(4));
			पूर्ण
			अगर (data->stereo_mode[i] == bw_def_top_bottom) अणु
				data->num_lines_at_frame_start = bw_पूर्णांक_to_fixed(1);
			पूर्ण
			अन्यथा अणु
				data->num_lines_at_frame_start = bw_पूर्णांक_to_fixed(3);
			पूर्ण
			अगर ((bw_mtn(data->vsr[i], bw_पूर्णांक_to_fixed(1)) && surface_type[i] == bw_def_graphics) || data->panning_and_bezel_adjusपंचांगent == bw_def_any_lines) अणु
				data->line_buffer_prefetch[i] = 0;
			पूर्ण
			अन्यथा अगर ((((dceip->underlay_करोwnscale_prefetch_enabled == 1 && surface_type[i] != bw_def_graphics) || surface_type[i] == bw_def_graphics) && (bw_mtn(data->lb_partitions[i], bw_add(data->v_taps[i], bw_उच्चमान2(data->vsr[i], bw_पूर्णांक_to_fixed(1))))))) अणु
				data->line_buffer_prefetch[i] = 1;
			पूर्ण
			अन्यथा अणु
				data->line_buffer_prefetch[i] = 0;
			पूर्ण
			data->lb_lines_in_per_line_out_in_beginning_of_frame[i] = bw_भाग(bw_उच्चमान2(data->v_filter_init[i], bw_पूर्णांक_to_fixed(dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb)), data->num_lines_at_frame_start);
			अगर (data->line_buffer_prefetch[i] == 1) अणु
				data->lb_lines_in_per_line_out_in_middle_of_frame[i] = bw_max2(bw_पूर्णांक_to_fixed(1), data->vsr[i]);
			पूर्ण
			अन्यथा अगर (bw_leq(data->vsr[i], bw_पूर्णांक_to_fixed(1))) अणु
				data->lb_lines_in_per_line_out_in_middle_of_frame[i] = bw_पूर्णांक_to_fixed(1);
			पूर्ण अन्यथा अगर (bw_leq(data->vsr[i],
					bw_frc_to_fixed(4, 3))) अणु
				data->lb_lines_in_per_line_out_in_middle_of_frame[i] = bw_भाग(bw_पूर्णांक_to_fixed(4), bw_पूर्णांक_to_fixed(3));
			पूर्ण अन्यथा अगर (bw_leq(data->vsr[i],
					bw_frc_to_fixed(6, 4))) अणु
				data->lb_lines_in_per_line_out_in_middle_of_frame[i] = bw_भाग(bw_पूर्णांक_to_fixed(6), bw_पूर्णांक_to_fixed(4));
			पूर्ण
			अन्यथा अगर (bw_leq(data->vsr[i], bw_पूर्णांक_to_fixed(2))) अणु
				data->lb_lines_in_per_line_out_in_middle_of_frame[i] = bw_पूर्णांक_to_fixed(2);
			पूर्ण
			अन्यथा अगर (bw_leq(data->vsr[i], bw_पूर्णांक_to_fixed(3))) अणु
				data->lb_lines_in_per_line_out_in_middle_of_frame[i] = bw_पूर्णांक_to_fixed(3);
			पूर्ण
			अन्यथा अणु
				data->lb_lines_in_per_line_out_in_middle_of_frame[i] = bw_पूर्णांक_to_fixed(4);
			पूर्ण
			अगर (data->line_buffer_prefetch[i] == 1 || bw_equ(data->lb_lines_in_per_line_out_in_middle_of_frame[i], bw_पूर्णांक_to_fixed(2)) || bw_equ(data->lb_lines_in_per_line_out_in_middle_of_frame[i], bw_पूर्णांक_to_fixed(4))) अणु
				data->horizontal_blank_and_chunk_granularity_factor[i] = bw_पूर्णांक_to_fixed(1);
			पूर्ण
			अन्यथा अणु
				data->horizontal_blank_and_chunk_granularity_factor[i] = bw_भाग(data->h_total[i], (bw_भाग((bw_add(data->h_total[i], bw_भाग((bw_sub(data->source_width_pixels[i], bw_पूर्णांक_to_fixed(dceip->chunk_width))), data->hsr[i]))), bw_पूर्णांक_to_fixed(2))));
			पूर्ण
			data->request_bandwidth[i] = bw_भाग(bw_mul(bw_भाग(bw_mul(bw_भाग(bw_mul(bw_max2(data->lb_lines_in_per_line_out_in_beginning_of_frame[i], data->lb_lines_in_per_line_out_in_middle_of_frame[i]), data->source_width_rounded_up_to_chunks[i]), (bw_भाग(data->h_total[i], data->pixel_rate[i]))), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->useful_bytes_per_request[i]), data->lines_पूर्णांकerleaved_in_mem_access[i]), data->latency_hiding_lines[i]);
			data->display_bandwidth[i] = bw_mul(data->request_bandwidth[i], data->bytes_per_request[i]);
		पूर्ण
	पूर्ण
	/*outstanding chunk request limit*/
	/*अगर underlay buffer sharing is enabled, the data buffer size क्रम underlay in 422 or 444 is the sum of the luma and chroma data buffer sizes.*/
	/*underlay buffer sharing mode is only permitted in orthogonal rotation modes.*/
	/**/
	/*अगर there is only one display enabled, the dmअगर data buffer size क्रम the graphics surface is increased by concatenating the adjacent buffers.*/
	/**/
	/*the memory chunk size in bytes is 1024 क्रम the ग_लिखोback, and 256 बार the memory line पूर्णांकerleaving and the bytes per pixel क्रम graphics*/
	/*and underlay.*/
	/**/
	/*the pipe chunk size uses 2 क्रम line पूर्णांकerleaving, except क्रम the ग_लिखो back, in which हाल it is 1.*/
	/*graphics and underlay data buffer size is adjusted (limited) using the outstanding chunk request limit अगर there is more than one*/
	/*display enabled or अगर the dmअगर request buffer is not large enough क्रम the total data buffer size.*/
	/*the outstanding chunk request limit is the उच्चमानing of the adjusted data buffer size भागided by the chunk size in bytes*/
	/*the adjusted data buffer size is the product of the display bandwidth and the minimum effective data buffer size in terms of समय,*/
	/*rounded up to the chunk size in bytes, but should not exceed the original data buffer size*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर ((dceip->dmअगर_pipe_en_fbc_chunk_tracker + 3 == i && fbc_enabled == 0 && tiling_mode[i] != bw_def_linear)) अणु
				data->max_chunks_non_fbc_mode[i] = 128 - dmअगर_chunk_buff_margin;
			पूर्ण
			अन्यथा अणु
				data->max_chunks_non_fbc_mode[i] = 16 - dmअगर_chunk_buff_margin;
			पूर्ण
		पूर्ण
		अगर (data->fbc_en[i] == 1) अणु
			max_chunks_fbc_mode = 128 - dmअगर_chunk_buff_margin;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			चयन (surface_type[i]) अणु
			हाल bw_def_display_ग_लिखो_back420_luma:
				data->data_buffer_size[i] = bw_पूर्णांक_to_fixed(dceip->display_ग_लिखो_back420_luma_mcअगरwr_buffer_size);
				अवरोध;
			हाल bw_def_display_ग_लिखो_back420_chroma:
				data->data_buffer_size[i] = bw_पूर्णांक_to_fixed(dceip->display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size);
				अवरोध;
			हाल bw_def_underlay420_luma:
				data->data_buffer_size[i] = bw_पूर्णांक_to_fixed(dceip->underlay_luma_dmअगर_size);
				अवरोध;
			हाल bw_def_underlay420_chroma:
				data->data_buffer_size[i] = bw_भाग(bw_पूर्णांक_to_fixed(dceip->underlay_chroma_dmअगर_size), bw_पूर्णांक_to_fixed(2));
				अवरोध;
			हाल bw_def_underlay422:हाल bw_def_underlay444:
				अगर (data->orthogonal_rotation[i] == 0) अणु
					data->data_buffer_size[i] = bw_पूर्णांक_to_fixed(dceip->underlay_luma_dmअगर_size);
				पूर्ण
				अन्यथा अणु
					data->data_buffer_size[i] = bw_add(bw_पूर्णांक_to_fixed(dceip->underlay_luma_dmअगर_size), bw_पूर्णांक_to_fixed(dceip->underlay_chroma_dmअगर_size));
				पूर्ण
				अवरोध;
			शेष:
				अगर (data->fbc_en[i] == 1) अणु
					/*data_buffer_size(i) = max_dmअगर_buffer_allocated * graphics_dmअगर_size*/
					अगर (data->number_of_displays == 1) अणु
						data->data_buffer_size[i] = bw_min2(bw_mul(bw_mul(bw_पूर्णांक_to_fixed(max_chunks_fbc_mode), bw_पूर्णांक_to_fixed(pixels_per_chunk)), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), bw_mul(bw_पूर्णांक_to_fixed(dceip->max_dmअगर_buffer_allocated), bw_पूर्णांक_to_fixed(dceip->graphics_dmअगर_size)));
					पूर्ण
					अन्यथा अणु
						data->data_buffer_size[i] = bw_min2(bw_mul(bw_mul(bw_पूर्णांक_to_fixed(max_chunks_fbc_mode), bw_पूर्णांक_to_fixed(pixels_per_chunk)), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), bw_पूर्णांक_to_fixed(dceip->graphics_dmअगर_size));
					पूर्ण
				पूर्ण
				अन्यथा अणु
					/*the effective dmअगर buffer size in non-fbc mode is limited by the 16 entry chunk tracker*/
					अगर (data->number_of_displays == 1) अणु
						data->data_buffer_size[i] = bw_min2(bw_mul(bw_mul(bw_पूर्णांक_to_fixed(data->max_chunks_non_fbc_mode[i]), bw_पूर्णांक_to_fixed(pixels_per_chunk)), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), bw_mul(bw_पूर्णांक_to_fixed(dceip->max_dmअगर_buffer_allocated), bw_पूर्णांक_to_fixed(dceip->graphics_dmअगर_size)));
					पूर्ण
					अन्यथा अणु
						data->data_buffer_size[i] = bw_min2(bw_mul(bw_mul(bw_पूर्णांक_to_fixed(data->max_chunks_non_fbc_mode[i]), bw_पूर्णांक_to_fixed(pixels_per_chunk)), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), bw_पूर्णांक_to_fixed(dceip->graphics_dmअगर_size));
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
			अगर (surface_type[i] == bw_def_display_ग_लिखो_back420_luma || surface_type[i] == bw_def_display_ग_लिखो_back420_chroma) अणु
				data->memory_chunk_size_in_bytes[i] = bw_पूर्णांक_to_fixed(1024);
				data->pipe_chunk_size_in_bytes[i] = bw_पूर्णांक_to_fixed(1024);
			पूर्ण
			अन्यथा अणु
				data->memory_chunk_size_in_bytes[i] = bw_mul(bw_mul(bw_पूर्णांक_to_fixed(dceip->chunk_width), data->lines_पूर्णांकerleaved_in_mem_access[i]), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]));
				data->pipe_chunk_size_in_bytes[i] = bw_mul(bw_mul(bw_पूर्णांक_to_fixed(dceip->chunk_width), bw_पूर्णांक_to_fixed(dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb)), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]));
			पूर्ण
		पूर्ण
	पूर्ण
	data->min_dmअगर_size_in_समय = bw_पूर्णांक_to_fixed(9999);
	data->min_mcअगरwr_size_in_समय = bw_पूर्णांक_to_fixed(9999);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
				अगर (bw_ltn(bw_भाग(bw_भाग(bw_mul(data->data_buffer_size[i], data->bytes_per_request[i]), data->useful_bytes_per_request[i]), data->display_bandwidth[i]), data->min_dmअगर_size_in_समय)) अणु
					data->min_dmअगर_size_in_समय = bw_भाग(bw_भाग(bw_mul(data->data_buffer_size[i], data->bytes_per_request[i]), data->useful_bytes_per_request[i]), data->display_bandwidth[i]);
				पूर्ण
			पूर्ण
			अन्यथा अणु
				अगर (bw_ltn(bw_भाग(bw_भाग(bw_mul(data->data_buffer_size[i], data->bytes_per_request[i]), data->useful_bytes_per_request[i]), data->display_bandwidth[i]), data->min_mcअगरwr_size_in_समय)) अणु
					data->min_mcअगरwr_size_in_समय = bw_भाग(bw_भाग(bw_mul(data->data_buffer_size[i], data->bytes_per_request[i]), data->useful_bytes_per_request[i]), data->display_bandwidth[i]);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	data->total_requests_क्रम_dmअगर_size = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i] && surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
			data->total_requests_क्रम_dmअगर_size = bw_add(data->total_requests_क्रम_dmअगर_size, bw_भाग(data->data_buffer_size[i], data->useful_bytes_per_request[i]));
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma && dceip->limit_excessive_outstanding_dmअगर_requests && (data->number_of_displays > 1 || bw_mtn(data->total_requests_क्रम_dmअगर_size, dceip->dmअगर_request_buffer_size))) अणु
				data->adjusted_data_buffer_size[i] = bw_min2(data->data_buffer_size[i], bw_उच्चमान2(bw_mul(data->min_dmअगर_size_in_समय, data->display_bandwidth[i]), data->memory_chunk_size_in_bytes[i]));
			पूर्ण
			अन्यथा अणु
				data->adjusted_data_buffer_size[i] = data->data_buffer_size[i];
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (data->number_of_displays == 1 && data->number_of_underlay_surfaces == 0) अणु
				/*set maximum chunk limit अगर only one graphic pipe is enabled*/
				data->outstanding_chunk_request_limit[i] = bw_पूर्णांक_to_fixed(127);
			पूर्ण
			अन्यथा अणु
				data->outstanding_chunk_request_limit[i] = bw_उच्चमान2(bw_भाग(data->adjusted_data_buffer_size[i], data->pipe_chunk_size_in_bytes[i]), bw_पूर्णांक_to_fixed(1));
				/*clamp maximum chunk limit in the graphic display pipe*/
				अगर (i >= 4) अणु
					data->outstanding_chunk_request_limit[i] = bw_max2(bw_पूर्णांक_to_fixed(127), data->outstanding_chunk_request_limit[i]);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*outstanding pte request limit*/
	/*in tiling mode with no rotation the sg pte requests are 8 useful pt_es, the sg row height is the page height and the sg page width x height is 64x64 क्रम 8bpp, 64x32 क्रम 16 bpp, 32x32 क्रम 32 bpp*/
	/*in tiling mode with rotation the sg pte requests are only one useful pte, and the sg row height is also the page height, but the sg page width and height are swapped*/
	/*in linear mode the pte requests are 8 useful pt_es, the sg page width is 4096 भागided by the bytes per pixel, the sg page height is 1, but there is just one row whose height is the lines of pte prefetching*/
	/*the outstanding pte request limit is obtained by multiplying the outstanding chunk request limit by the peak pte request to eviction limiting ratio, rounding up to पूर्णांकeger, multiplying by the pte requests per chunk, and rounding up to पूर्णांकeger again*/
	/*अगर not using peak pte request to eviction limiting, the outstanding pte request limit is the pte requests in the vblank*/
	/*the pte requests in the vblank is the product of the number of pte request rows बार the number of pte requests in a row*/
	/*the number of pte requests in a row is the quotient of the source width भागided by 256, multiplied by the pte requests per chunk, rounded up to even, multiplied by the scatter-gather row height and भागided by the scatter-gather page height*/
	/*the pte requests per chunk is 256 भागided by the scatter-gather page width and the useful pt_es per pte request*/
	अगर (data->number_of_displays > 1 || (bw_neq(data->rotation_angle[4], bw_पूर्णांक_to_fixed(0)) && bw_neq(data->rotation_angle[4], bw_पूर्णांक_to_fixed(180)))) अणु
		data->peak_pte_request_to_eviction_ratio_limiting = dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display;
	पूर्ण
	अन्यथा अणु
		data->peak_pte_request_to_eviction_ratio_limiting = dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation;
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i] && data->scatter_gather_enable_क्रम_pipe[i] == 1) अणु
			अगर (tiling_mode[i] == bw_def_linear) अणु
				data->useful_pte_per_pte_request = bw_पूर्णांक_to_fixed(8);
				data->scatter_gather_page_width[i] = bw_भाग(bw_पूर्णांक_to_fixed(4096), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]));
				data->scatter_gather_page_height[i] = bw_पूर्णांक_to_fixed(1);
				data->scatter_gather_pte_request_rows = bw_पूर्णांक_to_fixed(1);
				data->scatter_gather_row_height = bw_पूर्णांक_to_fixed(dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode);
			पूर्ण
			अन्यथा अगर (bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(0)) || bw_equ(data->rotation_angle[i], bw_पूर्णांक_to_fixed(180))) अणु
				data->useful_pte_per_pte_request = bw_पूर्णांक_to_fixed(8);
				चयन (data->bytes_per_pixel[i]) अणु
				हाल 4:
					data->scatter_gather_page_width[i] = bw_पूर्णांक_to_fixed(32);
					data->scatter_gather_page_height[i] = bw_पूर्णांक_to_fixed(32);
					अवरोध;
				हाल 2:
					data->scatter_gather_page_width[i] = bw_पूर्णांक_to_fixed(64);
					data->scatter_gather_page_height[i] = bw_पूर्णांक_to_fixed(32);
					अवरोध;
				शेष:
					data->scatter_gather_page_width[i] = bw_पूर्णांक_to_fixed(64);
					data->scatter_gather_page_height[i] = bw_पूर्णांक_to_fixed(64);
					अवरोध;
				पूर्ण
				data->scatter_gather_pte_request_rows = bw_पूर्णांक_to_fixed(dceip->scatter_gather_pte_request_rows_in_tiling_mode);
				data->scatter_gather_row_height = data->scatter_gather_page_height[i];
			पूर्ण
			अन्यथा अणु
				data->useful_pte_per_pte_request = bw_पूर्णांक_to_fixed(1);
				चयन (data->bytes_per_pixel[i]) अणु
				हाल 4:
					data->scatter_gather_page_width[i] = bw_पूर्णांक_to_fixed(32);
					data->scatter_gather_page_height[i] = bw_पूर्णांक_to_fixed(32);
					अवरोध;
				हाल 2:
					data->scatter_gather_page_width[i] = bw_पूर्णांक_to_fixed(32);
					data->scatter_gather_page_height[i] = bw_पूर्णांक_to_fixed(64);
					अवरोध;
				शेष:
					data->scatter_gather_page_width[i] = bw_पूर्णांक_to_fixed(64);
					data->scatter_gather_page_height[i] = bw_पूर्णांक_to_fixed(64);
					अवरोध;
				पूर्ण
				data->scatter_gather_pte_request_rows = bw_पूर्णांक_to_fixed(dceip->scatter_gather_pte_request_rows_in_tiling_mode);
				data->scatter_gather_row_height = data->scatter_gather_page_height[i];
			पूर्ण
			data->pte_request_per_chunk[i] = bw_भाग(bw_भाग(bw_पूर्णांक_to_fixed(dceip->chunk_width), data->scatter_gather_page_width[i]), data->useful_pte_per_pte_request);
			data->scatter_gather_pte_requests_in_row[i] = bw_भाग(bw_mul(bw_उच्चमान2(bw_mul(bw_भाग(data->source_width_rounded_up_to_chunks[i], bw_पूर्णांक_to_fixed(dceip->chunk_width)), data->pte_request_per_chunk[i]), bw_पूर्णांक_to_fixed(1)), data->scatter_gather_row_height), data->scatter_gather_page_height[i]);
			data->scatter_gather_pte_requests_in_vblank = bw_mul(data->scatter_gather_pte_request_rows, data->scatter_gather_pte_requests_in_row[i]);
			अगर (bw_equ(data->peak_pte_request_to_eviction_ratio_limiting, bw_पूर्णांक_to_fixed(0))) अणु
				data->scatter_gather_pte_request_limit[i] = data->scatter_gather_pte_requests_in_vblank;
			पूर्ण
			अन्यथा अणु
				data->scatter_gather_pte_request_limit[i] = bw_max2(dceip->minimum_outstanding_pte_request_limit, bw_min2(data->scatter_gather_pte_requests_in_vblank, bw_उच्चमान2(bw_mul(bw_mul(bw_भाग(bw_उच्चमान2(data->adjusted_data_buffer_size[i], data->memory_chunk_size_in_bytes[i]), data->memory_chunk_size_in_bytes[i]), data->pte_request_per_chunk[i]), data->peak_pte_request_to_eviction_ratio_limiting), bw_पूर्णांक_to_fixed(1))));
			पूर्ण
		पूर्ण
	पूर्ण
	/*pitch padding recommended क्रम efficiency in linear mode*/
	/*in linear mode graphics or underlay with scatter gather, a pitch that is a multiple of the channel पूर्णांकerleave (256 bytes) बार the channel-bank rotation is not efficient*/
	/*अगर that is the हाल it is recommended to pad the pitch by at least 256 pixels*/
	data->inefficient_linear_pitch_in_bytes = bw_mul(bw_mul(bw_पूर्णांक_to_fixed(256), bw_पूर्णांक_to_fixed(vbios->number_of_dram_banks)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels));

	/*pixel transfer समय*/
	/*the dmअगर and mcअगरwr yclk(pclk) required is the one that allows the transfer of all pipe's data buffer size in memory in the समय क्रम data transfer*/
	/*क्रम dmअगर, pte and cursor requests have to be included.*/
	/*the dram data requirement is द्विगुनd when the data request size in bytes is less than the dram channel width बार the burst size (8)*/
	/*the dram data requirement is also multiplied by the number of channels in the हाल of low घातer tiling*/
	/*the page बंद-खोलो समय is determined by trc and the number of page बंद-खोलोs*/
	/*in tiled mode graphics or underlay with scatter-gather enabled the bytes per page बंद-खोलो is the product of the memory line पूर्णांकerleave बार the maximum of the scatter-gather page width and the product of the tile width (8 pixels) बार the number of channels बार the number of banks.*/
	/*in linear mode graphics or underlay with scatter-gather enabled and inefficient pitch, the bytes per page बंद-खोलो is the line request alternation slice, because dअगरferent lines are in completely dअगरferent 4k address bases.*/
	/*otherwise, the bytes page बंद-खोलो is the chunk size because that is the arbitration slice.*/
	/*pte requests are grouped by pte requests per chunk अगर that is more than 1. each group costs a page बंद-खोलो समय क्रम dmअगर पढ़ोs*/
	/*cursor requests outstanding are limited to a group of two source lines. each group costs a page बंद-खोलो समय क्रम dmअगर पढ़ोs*/
	/*the display पढ़ोs and ग_लिखोs समय क्रम data transfer is the minimum data or cursor buffer size in समय minus the mc urgent latency*/
	/*the mc urgent latency is experienced more than one समय अगर the number of dmअगर requests in the data buffer exceeds the request buffer size plus the request slots reserved क्रम dmअगर in the dram channel arbiter queues*/
	/*the dispclk required is the maximum क्रम all surfaces of the maximum of the source pixels क्रम first output pixel बार the throughput factor, भागided by the pixels per dispclk, and भागided by the minimum latency hiding minus the dram speed/p-state change latency minus the burst समय, and the source pixels क्रम last output pixel, बार the throughput factor, भागided by the pixels per dispclk, and भागided by the minimum latency hiding minus the dram speed/p-state change latency minus the burst समय, plus the active समय.*/
	/*the data burst समय is the maximum of the total page बंद-खोलो समय, total dmअगर/mcअगरwr buffer size in memory भागided by the dram bandwidth, and the total dmअगर/mcअगरwr buffer size in memory भागided by the 32 byte sclk data bus bandwidth, each multiplied by its efficiency.*/
	/*the source line transfer समय is the maximum क्रम all surfaces of the maximum of the burst समय plus the urgent latency बार the न्यूनमान of the data required भागided by the buffer size क्रम the fist pixel, and the burst समय plus the urgent latency बार the न्यूनमान of the data required भागided by the buffer size क्रम the last pixel plus the active समय.*/
	/*the source pixels क्रम the first output pixel is 512 अगर the scaler vertical filter initialization value is greater than 2, and it is 4 बार the source width अगर it is greater than 4.*/
	/*the source pixels क्रम the last output pixel is the source width बार the scaler vertical filter initialization value rounded up to even*/
	/*the source data क्रम these pixels is the number of pixels बार the bytes per pixel बार the bytes per request भागided by the useful bytes per request.*/
	data->cursor_total_data = bw_पूर्णांक_to_fixed(0);
	data->cursor_total_request_groups = bw_पूर्णांक_to_fixed(0);
	data->scatter_gather_total_pte_requests = bw_पूर्णांक_to_fixed(0);
	data->scatter_gather_total_pte_request_groups = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->cursor_total_data = bw_add(data->cursor_total_data, bw_mul(bw_mul(bw_पूर्णांक_to_fixed(2), data->cursor_width_pixels[i]), bw_पूर्णांक_to_fixed(4)));
			अगर (dceip->large_cursor == 1) अणु
				data->cursor_total_request_groups = bw_add(data->cursor_total_request_groups, bw_पूर्णांक_to_fixed((dceip->cursor_max_outstanding_group_num + 1)));
			पूर्ण
			अन्यथा अणु
				data->cursor_total_request_groups = bw_add(data->cursor_total_request_groups, bw_उच्चमान2(bw_भाग(data->cursor_width_pixels[i], dceip->cursor_chunk_width), bw_पूर्णांक_to_fixed(1)));
			पूर्ण
			अगर (data->scatter_gather_enable_क्रम_pipe[i]) अणु
				data->scatter_gather_total_pte_requests = bw_add(data->scatter_gather_total_pte_requests, data->scatter_gather_pte_request_limit[i]);
				data->scatter_gather_total_pte_request_groups = bw_add(data->scatter_gather_total_pte_request_groups, bw_उच्चमान2(bw_भाग(data->scatter_gather_pte_request_limit[i], bw_उच्चमान2(data->pte_request_per_chunk[i], bw_पूर्णांक_to_fixed(1))), bw_पूर्णांक_to_fixed(1)));
			पूर्ण
		पूर्ण
	पूर्ण
	data->tile_width_in_pixels = bw_पूर्णांक_to_fixed(8);
	data->dmअगर_total_number_of_data_request_page_बंद_खोलो = bw_पूर्णांक_to_fixed(0);
	data->mcअगरwr_total_number_of_data_request_page_बंद_खोलो = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (data->scatter_gather_enable_क्रम_pipe[i] == 1 && tiling_mode[i] != bw_def_linear) अणु
				data->bytes_per_page_बंद_खोलो = bw_mul(data->lines_पूर्णांकerleaved_in_mem_access[i], bw_max2(bw_mul(bw_mul(bw_mul(bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]), data->tile_width_in_pixels), bw_पूर्णांक_to_fixed(vbios->number_of_dram_banks)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels)), bw_mul(bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]), data->scatter_gather_page_width[i])));
			पूर्ण
			अन्यथा अगर (data->scatter_gather_enable_क्रम_pipe[i] == 1 && tiling_mode[i] == bw_def_linear && bw_equ(bw_mod((bw_mul(data->pitch_in_pixels_after_surface_type[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]))), data->inefficient_linear_pitch_in_bytes), bw_पूर्णांक_to_fixed(0))) अणु
				data->bytes_per_page_बंद_खोलो = dceip->linear_mode_line_request_alternation_slice;
			पूर्ण
			अन्यथा अणु
				data->bytes_per_page_बंद_खोलो = data->memory_chunk_size_in_bytes[i];
			पूर्ण
			अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->dmअगर_total_number_of_data_request_page_बंद_खोलो = bw_add(data->dmअगर_total_number_of_data_request_page_बंद_खोलो, bw_भाग(bw_उच्चमान2(data->adjusted_data_buffer_size[i], data->memory_chunk_size_in_bytes[i]), data->bytes_per_page_बंद_खोलो));
			पूर्ण
			अन्यथा अणु
				data->mcअगरwr_total_number_of_data_request_page_बंद_खोलो = bw_add(data->mcअगरwr_total_number_of_data_request_page_बंद_खोलो, bw_भाग(bw_उच्चमान2(data->adjusted_data_buffer_size[i], data->memory_chunk_size_in_bytes[i]), data->bytes_per_page_बंद_खोलो));
			पूर्ण
		पूर्ण
	पूर्ण
	data->dmअगर_total_page_बंद_खोलो_समय = bw_भाग(bw_mul((bw_add(bw_add(data->dmअगर_total_number_of_data_request_page_बंद_खोलो, data->scatter_gather_total_pte_request_groups), data->cursor_total_request_groups)), vbios->trc), bw_पूर्णांक_to_fixed(1000));
	data->mcअगरwr_total_page_बंद_खोलो_समय = bw_भाग(bw_mul(data->mcअगरwr_total_number_of_data_request_page_बंद_खोलो, vbios->trc), bw_पूर्णांक_to_fixed(1000));
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->adjusted_data_buffer_size_in_memory[i] = bw_भाग(bw_mul(data->adjusted_data_buffer_size[i], data->bytes_per_request[i]), data->useful_bytes_per_request[i]);
		पूर्ण
	पूर्ण
	data->total_requests_क्रम_adjusted_dmअगर_size = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->total_requests_क्रम_adjusted_dmअगर_size = bw_add(data->total_requests_क्रम_adjusted_dmअगर_size, bw_भाग(data->adjusted_data_buffer_size[i], data->useful_bytes_per_request[i]));
			पूर्ण
		पूर्ण
	पूर्ण
	data->total_dmअगरmc_urgent_trips = bw_उच्चमान2(bw_भाग(data->total_requests_क्रम_adjusted_dmअगर_size, (bw_add(dceip->dmअगर_request_buffer_size, bw_पूर्णांक_to_fixed(vbios->number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel * data->number_of_dram_channels)))), bw_पूर्णांक_to_fixed(1));
	data->total_dmअगरmc_urgent_latency = bw_mul(vbios->dmअगरmc_urgent_latency, data->total_dmअगरmc_urgent_trips);
	data->total_display_पढ़ोs_required_data = bw_पूर्णांक_to_fixed(0);
	data->total_display_पढ़ोs_required_dram_access_data = bw_पूर्णांक_to_fixed(0);
	data->total_display_ग_लिखोs_required_data = bw_पूर्णांक_to_fixed(0);
	data->total_display_ग_लिखोs_required_dram_access_data = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->display_पढ़ोs_required_data = data->adjusted_data_buffer_size_in_memory[i];
				/*क्रम hbm memories, each channel is split पूर्णांकo 2 pseuकरो-channels that are each 64 bits in width.  each*/
				/*pseuकरो-channel may be पढ़ो independently of one another.*/
				/*the पढ़ो burst length (bl) क्रम hbm memories is 4, so each पढ़ो command will access 32 bytes of data.*/
				/*the 64 or 32 byte sized data is stored in one pseuकरो-channel.*/
				/*it will take 4 memclk cycles or 8 yclk cycles to fetch 64 bytes of data from the hbm memory (2 पढ़ो commands).*/
				/*it will take 2 memclk cycles or 4 yclk cycles to fetch 32 bytes of data from the hbm memory (1 पढ़ो command).*/
				/*क्रम gddr5/ddr4 memories, there is additional overhead अगर the size of the request is smaller than 64 bytes.*/
				/*the पढ़ो burst length (bl) क्रम gddr5/ddr4 memories is 8, regardless of the size of the data request.*/
				/*thereक्रमe it will require 8 cycles to fetch 64 or 32 bytes of data from the memory.*/
				/*the memory efficiency will be 50% क्रम the 32 byte sized data.*/
				अगर (vbios->memory_type == bw_def_hbm) अणु
					data->display_पढ़ोs_required_dram_access_data = data->adjusted_data_buffer_size_in_memory[i];
				पूर्ण
				अन्यथा अणु
					data->display_पढ़ोs_required_dram_access_data = bw_mul(data->adjusted_data_buffer_size_in_memory[i], bw_उच्चमान2(bw_भाग(bw_पूर्णांक_to_fixed((8 * vbios->dram_channel_width_in_bits / 8)), data->bytes_per_request[i]), bw_पूर्णांक_to_fixed(1)));
				पूर्ण
				data->total_display_पढ़ोs_required_data = bw_add(data->total_display_पढ़ोs_required_data, data->display_पढ़ोs_required_data);
				data->total_display_पढ़ोs_required_dram_access_data = bw_add(data->total_display_पढ़ोs_required_dram_access_data, data->display_पढ़ोs_required_dram_access_data);
			पूर्ण
			अन्यथा अणु
				data->total_display_ग_लिखोs_required_data = bw_add(data->total_display_ग_लिखोs_required_data, data->adjusted_data_buffer_size_in_memory[i]);
				data->total_display_ग_लिखोs_required_dram_access_data = bw_add(data->total_display_ग_लिखोs_required_dram_access_data, bw_mul(data->adjusted_data_buffer_size_in_memory[i], bw_उच्चमान2(bw_भाग(bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits), data->bytes_per_request[i]), bw_पूर्णांक_to_fixed(1))));
			पूर्ण
		पूर्ण
	पूर्ण
	data->total_display_पढ़ोs_required_data = bw_add(bw_add(data->total_display_पढ़ोs_required_data, data->cursor_total_data), bw_mul(data->scatter_gather_total_pte_requests, bw_पूर्णांक_to_fixed(64)));
	data->total_display_पढ़ोs_required_dram_access_data = bw_add(bw_add(data->total_display_पढ़ोs_required_dram_access_data, data->cursor_total_data), bw_mul(data->scatter_gather_total_pte_requests, bw_पूर्णांक_to_fixed(64)));
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_mtn(data->v_filter_init[i], bw_पूर्णांक_to_fixed(4))) अणु
				data->src_pixels_क्रम_first_output_pixel[i] = bw_mul(bw_पूर्णांक_to_fixed(4), data->source_width_rounded_up_to_chunks[i]);
			पूर्ण
			अन्यथा अणु
				अगर (bw_mtn(data->v_filter_init[i], bw_पूर्णांक_to_fixed(2))) अणु
					data->src_pixels_क्रम_first_output_pixel[i] = bw_पूर्णांक_to_fixed(512);
				पूर्ण
				अन्यथा अणु
					data->src_pixels_क्रम_first_output_pixel[i] = bw_पूर्णांक_to_fixed(0);
				पूर्ण
			पूर्ण
			data->src_data_क्रम_first_output_pixel[i] = bw_भाग(bw_mul(bw_mul(data->src_pixels_क्रम_first_output_pixel[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->bytes_per_request[i]), data->useful_bytes_per_request[i]);
			data->src_pixels_क्रम_last_output_pixel[i] = bw_mul(data->source_width_rounded_up_to_chunks[i], bw_max2(bw_उच्चमान2(data->v_filter_init[i], bw_पूर्णांक_to_fixed(dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb)), bw_mul(bw_उच्चमान2(data->vsr[i], bw_पूर्णांक_to_fixed(dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb)), data->horizontal_blank_and_chunk_granularity_factor[i])));
			data->src_data_क्रम_last_output_pixel[i] = bw_भाग(bw_mul(bw_mul(bw_mul(data->source_width_rounded_up_to_chunks[i], bw_max2(bw_उच्चमान2(data->v_filter_init[i], bw_पूर्णांक_to_fixed(dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb)), data->lines_पूर्णांकerleaved_in_mem_access[i])), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->bytes_per_request[i]), data->useful_bytes_per_request[i]);
			data->active_समय[i] = bw_भाग(bw_भाग(data->source_width_rounded_up_to_chunks[i], data->hsr[i]), data->pixel_rate[i]);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= 2; i++) अणु
		क्रम (j = 0; j <= 7; j++) अणु
			data->dmअगर_burst_समय[i][j] = bw_max3(data->dmअगर_total_page_बंद_खोलो_समय, bw_भाग(data->total_display_पढ़ोs_required_dram_access_data, (bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[i]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels)))), bw_भाग(data->total_display_पढ़ोs_required_data, (bw_mul(bw_mul(sclk[j], vbios->data_वापस_bus_width), bw_frc_to_fixed(dceip->percent_of_ideal_port_bw_received_after_urgent_latency, 100)))));
			अगर (data->d1_display_ग_लिखो_back_dwb_enable == 1) अणु
				data->mcअगरwr_burst_समय[i][j] = bw_max3(data->mcअगरwr_total_page_बंद_खोलो_समय, bw_भाग(data->total_display_ग_लिखोs_required_dram_access_data, (bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[i]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_wrchannels)))), bw_भाग(data->total_display_ग_लिखोs_required_data, (bw_mul(sclk[j], vbios->data_वापस_bus_width))));
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		क्रम (j = 0; j <= 2; j++) अणु
			क्रम (k = 0; k <= 7; k++) अणु
				अगर (data->enable[i]) अणु
					अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
						/*समय to transfer data from the dmअगर buffer to the lb.  since the mc to dmअगर transfer समय overlaps*/
						/*with the dmअगर to lb transfer समय, only समय to transfer the last chunk  is considered.*/
						data->dmअगर_buffer_transfer_समय[i] = bw_mul(data->source_width_rounded_up_to_chunks[i], (bw_भाग(dceip->lb_ग_लिखो_pixels_per_dispclk, (bw_भाग(vbios->low_voltage_max_dispclk, dceip->display_pipe_throughput_factor)))));
						data->line_source_transfer_समय[i][j][k] = bw_max2(bw_mul((bw_add(data->total_dmअगरmc_urgent_latency, data->dmअगर_burst_समय[j][k])), bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_first_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1))), bw_sub(bw_add(bw_mul((bw_add(data->total_dmअगरmc_urgent_latency, data->dmअगर_burst_समय[j][k])), bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_last_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1))), data->dmअगर_buffer_transfer_समय[i]), data->active_समय[i]));
						/*during an mclk चयन the requests from the dce ip are stored in the gmc/arb.  these requests should be serviced immediately*/
						/*after the mclk चयन sequence and not incur an urgent latency penalty.  it is assumed that the gmc/arb can hold up to 256 requests*/
						/*per memory channel.  अगर the dce ip is urgent after the mclk चयन sequence, all pending requests and subsequent requests should be*/
						/*immediately serviced without a gap in the urgent requests.*/
						/*the latency incurred would be the समय to issue the requests and वापस the data क्रम the first or last output pixel.*/
						अगर (surface_type[i] == bw_def_graphics) अणु
							चयन (data->lb_bpc[i]) अणु
							हाल 6:
								data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency6_bit_per_component;
								अवरोध;
							हाल 8:
								data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency8_bit_per_component;
								अवरोध;
							हाल 10:
								data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency10_bit_per_component;
								अवरोध;
							शेष:
								data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency12_bit_per_component;
								अवरोध;
							पूर्ण
							अगर (data->use_alpha[i] == 1) अणु
								data->v_scaler_efficiency = bw_min2(data->v_scaler_efficiency, dceip->alpha_vscaler_efficiency);
							पूर्ण
						पूर्ण
						अन्यथा अणु
							चयन (data->lb_bpc[i]) अणु
							हाल 6:
								data->v_scaler_efficiency = dceip->underlay_vscaler_efficiency6_bit_per_component;
								अवरोध;
							हाल 8:
								data->v_scaler_efficiency = dceip->underlay_vscaler_efficiency8_bit_per_component;
								अवरोध;
							हाल 10:
								data->v_scaler_efficiency = dceip->underlay_vscaler_efficiency10_bit_per_component;
								अवरोध;
							शेष:
								data->v_scaler_efficiency = bw_पूर्णांक_to_fixed(3);
								अवरोध;
							पूर्ण
						पूर्ण
						अगर (dceip->pre_करोwnscaler_enabled && bw_mtn(data->hsr[i], bw_पूर्णांक_to_fixed(1))) अणु
							data->scaler_limits_factor = bw_max2(bw_भाग(data->v_taps[i], data->v_scaler_efficiency), bw_भाग(data->source_width_rounded_up_to_chunks[i], data->h_total[i]));
						पूर्ण
						अन्यथा अणु
							data->scaler_limits_factor = bw_max3(bw_पूर्णांक_to_fixed(1), bw_उच्चमान2(bw_भाग(data->h_taps[i], bw_पूर्णांक_to_fixed(4)), bw_पूर्णांक_to_fixed(1)), bw_mul(data->hsr[i], bw_max2(bw_भाग(data->v_taps[i], data->v_scaler_efficiency), bw_पूर्णांक_to_fixed(1))));
						पूर्ण
						data->dram_speed_change_line_source_transfer_समय[i][j][k] = bw_mul(bw_पूर्णांक_to_fixed(2), bw_max2((bw_add((bw_भाग(data->src_data_क्रम_first_output_pixel[i], bw_min2(bw_mul(data->bytes_per_request[i], sclk[k]), bw_भाग(bw_mul(bw_mul(data->bytes_per_request[i], data->pixel_rate[i]), data->scaler_limits_factor), bw_पूर्णांक_to_fixed(2))))), (bw_mul(data->dmअगर_burst_समय[j][k], bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_first_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1)))))), (bw_add((bw_भाग(data->src_data_क्रम_last_output_pixel[i], bw_min2(bw_mul(data->bytes_per_request[i], sclk[k]), bw_भाग(bw_mul(bw_mul(data->bytes_per_request[i], data->pixel_rate[i]), data->scaler_limits_factor), bw_पूर्णांक_to_fixed(2))))), (bw_sub(bw_mul(data->dmअगर_burst_समय[j][k], bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_last_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1))), data->active_समय[i]))))));
					पूर्ण
					अन्यथा अणु
						data->line_source_transfer_समय[i][j][k] = bw_max2(bw_mul((bw_add(vbios->mcअगरwrmc_urgent_latency, data->mcअगरwr_burst_समय[j][k])), bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_first_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1))), bw_sub(bw_mul((bw_add(vbios->mcअगरwrmc_urgent_latency, data->mcअगरwr_burst_समय[j][k])), bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_last_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1))), data->active_समय[i]));
						/*during an mclk चयन the requests from the dce ip are stored in the gmc/arb.  these requests should be serviced immediately*/
						/*after the mclk चयन sequence and not incur an urgent latency penalty.  it is assumed that the gmc/arb can hold up to 256 requests*/
						/*per memory channel.  अगर the dce ip is urgent after the mclk चयन sequence, all pending requests and subsequent requests should be*/
						/*immediately serviced without a gap in the urgent requests.*/
						/*the latency incurred would be the समय to issue the requests and वापस the data क्रम the first or last output pixel.*/
						data->dram_speed_change_line_source_transfer_समय[i][j][k] = bw_max2((bw_add((bw_भाग(data->src_data_क्रम_first_output_pixel[i], bw_min2(bw_mul(data->bytes_per_request[i], sclk[k]), bw_भाग(bw_mul(data->bytes_per_request[i], vbios->low_voltage_max_dispclk), bw_पूर्णांक_to_fixed(2))))), (bw_mul(data->mcअगरwr_burst_समय[j][k], bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_first_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1)))))), (bw_add((bw_भाग(data->src_data_क्रम_last_output_pixel[i], bw_min2(bw_mul(data->bytes_per_request[i], sclk[k]), bw_भाग(bw_mul(data->bytes_per_request[i], vbios->low_voltage_max_dispclk), bw_पूर्णांक_to_fixed(2))))), (bw_sub(bw_mul(data->mcअगरwr_burst_समय[j][k], bw_न्यूनमान2(bw_भाग(data->src_data_क्रम_last_output_pixel[i], data->adjusted_data_buffer_size_in_memory[i]), bw_पूर्णांक_to_fixed(1))), data->active_समय[i])))));
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*cpu c-state and p-state change enable*/
	/*क्रम cpu p-state change to be possible क्रम a yclk(pclk) and sclk level the dispclk required has to be enough क्रम the blackout duration*/
	/*क्रम cpu c-state change to be possible क्रम a yclk(pclk) and sclk level the dispclk required has to be enough क्रम the blackout duration and recovery*/
	/*condition क्रम the blackout duration:*/
	/* minimum latency hiding > blackout duration + dmअगर burst समय + line source transfer समय*/
	/*condition क्रम the blackout recovery:*/
	/* recovery समय >  dmअगर burst समय + 2 * urgent latency*/
	/* recovery समय > (display bw * blackout duration  + (2 * urgent latency + dmअगर burst समय)*dispclk - dmअगर size )*/
	/*                  / (dispclk - display bw)*/
	/*the minimum latency hiding is the minimum क्रम all pipes of one screen line समय, plus one more line समय अगर करोing lb prefetch, plus the dmअगर data buffer size equivalent in समय, minus the urgent latency.*/
	/*the minimum latency hiding is  further limited by the cursor.  the cursor latency hiding is the number of lines of the cursor buffer, minus one अगर the करोwnscaling is less than two, or minus three अगर it is more*/

	/*initialize variables*/
	number_of_displays_enabled = 0;
	number_of_displays_enabled_with_margin = 0;
	क्रम (k = 0; k <= maximum_number_of_surfaces - 1; k++) अणु
		अगर (data->enable[k]) अणु
			number_of_displays_enabled = number_of_displays_enabled + 1;
		पूर्ण
		data->display_pstate_change_enable[k] = 0;
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर ((bw_equ(dceip->stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor, bw_पूर्णांक_to_fixed(0)) && bw_mtn(data->cursor_width_pixels[i], bw_पूर्णांक_to_fixed(0)))) अणु
				अगर (bw_ltn(data->vsr[i], bw_पूर्णांक_to_fixed(2))) अणु
					data->cursor_latency_hiding[i] = bw_भाग(bw_भाग(bw_mul((bw_sub(dceip->cursor_dcp_buffer_lines, bw_पूर्णांक_to_fixed(1))), data->h_total[i]), data->vsr[i]), data->pixel_rate[i]);
				पूर्ण
				अन्यथा अणु
					data->cursor_latency_hiding[i] = bw_भाग(bw_भाग(bw_mul((bw_sub(dceip->cursor_dcp_buffer_lines, bw_पूर्णांक_to_fixed(3))), data->h_total[i]), data->vsr[i]), data->pixel_rate[i]);
				पूर्ण
			पूर्ण
			अन्यथा अणु
				data->cursor_latency_hiding[i] = bw_पूर्णांक_to_fixed(9999);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching == 1 && (bw_equ(data->vsr[i], bw_पूर्णांक_to_fixed(1)) || (bw_leq(data->vsr[i], bw_frc_to_fixed(8, 10)) && bw_leq(data->v_taps[i], bw_पूर्णांक_to_fixed(2)) && data->lb_bpc[i] == 8)) && surface_type[i] == bw_def_graphics) अणु
				अगर (number_of_displays_enabled > 2)
					data->minimum_latency_hiding[i] = bw_sub(bw_भाग(bw_mul((bw_भाग((bw_add(bw_sub(data->lb_partitions[i], bw_पूर्णांक_to_fixed(2)), bw_भाग(bw_भाग(data->data_buffer_size[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->source_width_pixels[i]))), data->vsr[i])), data->h_total[i]), data->pixel_rate[i]), data->total_dmअगरmc_urgent_latency);
				अन्यथा
					data->minimum_latency_hiding[i] = bw_sub(bw_भाग(bw_mul((bw_भाग((bw_add(bw_sub(data->lb_partitions[i], bw_पूर्णांक_to_fixed(1)), bw_भाग(bw_भाग(data->data_buffer_size[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->source_width_pixels[i]))), data->vsr[i])), data->h_total[i]), data->pixel_rate[i]), data->total_dmअगरmc_urgent_latency);
			पूर्ण
			अन्यथा अणु
				data->minimum_latency_hiding[i] = bw_sub(bw_भाग(bw_mul((bw_भाग((bw_add(bw_पूर्णांक_to_fixed(1 + data->line_buffer_prefetch[i]), bw_भाग(bw_भाग(data->data_buffer_size[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->source_width_pixels[i]))), data->vsr[i])), data->h_total[i]), data->pixel_rate[i]), data->total_dmअगरmc_urgent_latency);
			पूर्ण
			data->minimum_latency_hiding_with_cursor[i] = bw_min2(data->minimum_latency_hiding[i], data->cursor_latency_hiding[i]);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= 2; i++) अणु
		क्रम (j = 0; j <= 7; j++) अणु
			data->blackout_duration_margin[i][j] = bw_पूर्णांक_to_fixed(9999);
			data->dispclk_required_क्रम_blackout_duration[i][j] = bw_पूर्णांक_to_fixed(0);
			data->dispclk_required_क्रम_blackout_recovery[i][j] = bw_पूर्णांक_to_fixed(0);
			क्रम (k = 0; k <= maximum_number_of_surfaces - 1; k++) अणु
				अगर (data->enable[k] && bw_mtn(vbios->blackout_duration, bw_पूर्णांक_to_fixed(0))) अणु
					अगर (surface_type[k] != bw_def_display_ग_लिखो_back420_luma && surface_type[k] != bw_def_display_ग_लिखो_back420_chroma) अणु
						data->blackout_duration_margin[i][j] = bw_min2(data->blackout_duration_margin[i][j], bw_sub(bw_sub(bw_sub(data->minimum_latency_hiding_with_cursor[k], vbios->blackout_duration), data->dmअगर_burst_समय[i][j]), data->line_source_transfer_समय[k][i][j]));
						data->dispclk_required_क्रम_blackout_duration[i][j] = bw_max3(data->dispclk_required_क्रम_blackout_duration[i][j], bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_first_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_sub(bw_sub(data->minimum_latency_hiding_with_cursor[k], vbios->blackout_duration), data->dmअगर_burst_समय[i][j]))), bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_last_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_add(bw_sub(bw_sub(data->minimum_latency_hiding_with_cursor[k], vbios->blackout_duration), data->dmअगर_burst_समय[i][j]), data->active_समय[k]))));
						अगर (bw_leq(vbios->maximum_blackout_recovery_समय, bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[i][j]))) अणु
							data->dispclk_required_क्रम_blackout_recovery[i][j] = bw_पूर्णांक_to_fixed(9999);
						पूर्ण
						अन्यथा अगर (bw_ltn(data->adjusted_data_buffer_size[k], bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), (bw_add(vbios->blackout_duration, bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[i][j])))))) अणु
							data->dispclk_required_क्रम_blackout_recovery[i][j] = bw_max2(data->dispclk_required_क्रम_blackout_recovery[i][j], bw_भाग(bw_mul(bw_भाग(bw_भाग((bw_sub(bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), (bw_add(vbios->blackout_duration, vbios->maximum_blackout_recovery_समय))), data->adjusted_data_buffer_size[k])), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[k])), (bw_sub(vbios->maximum_blackout_recovery_समय, bw_sub(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[i][j])))), data->latency_hiding_lines[k]), data->lines_पूर्णांकerleaved_in_mem_access[k]));
						पूर्ण
					पूर्ण
					अन्यथा अणु
						data->blackout_duration_margin[i][j] = bw_min2(data->blackout_duration_margin[i][j], bw_sub(bw_sub(bw_sub(bw_sub(data->minimum_latency_hiding_with_cursor[k], vbios->blackout_duration), data->dmअगर_burst_समय[i][j]), data->mcअगरwr_burst_समय[i][j]), data->line_source_transfer_समय[k][i][j]));
						data->dispclk_required_क्रम_blackout_duration[i][j] = bw_max3(data->dispclk_required_क्रम_blackout_duration[i][j], bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_first_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_sub(bw_sub(bw_sub(data->minimum_latency_hiding_with_cursor[k], vbios->blackout_duration), data->dmअगर_burst_समय[i][j]), data->mcअगरwr_burst_समय[i][j]))), bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_last_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_add(bw_sub(bw_sub(bw_sub(data->minimum_latency_hiding_with_cursor[k], vbios->blackout_duration), data->dmअगर_burst_समय[i][j]), data->mcअगरwr_burst_समय[i][j]), data->active_समय[k]))));
						अगर (bw_ltn(vbios->maximum_blackout_recovery_समय, bw_add(bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), vbios->mcअगरwrmc_urgent_latency), data->dmअगर_burst_समय[i][j]), data->mcअगरwr_burst_समय[i][j]))) अणु
							data->dispclk_required_क्रम_blackout_recovery[i][j] = bw_पूर्णांक_to_fixed(9999);
						पूर्ण
						अन्यथा अगर (bw_ltn(data->adjusted_data_buffer_size[k], bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), (bw_add(vbios->blackout_duration, bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[i][j])))))) अणु
							data->dispclk_required_क्रम_blackout_recovery[i][j] = bw_max2(data->dispclk_required_क्रम_blackout_recovery[i][j], bw_भाग(bw_mul(bw_भाग(bw_भाग((bw_sub(bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), (bw_add(vbios->blackout_duration, vbios->maximum_blackout_recovery_समय))), data->adjusted_data_buffer_size[k])), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[k])), (bw_sub(vbios->maximum_blackout_recovery_समय, (bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[i][j]))))), data->latency_hiding_lines[k]), data->lines_पूर्णांकerleaved_in_mem_access[k]));
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (bw_mtn(data->blackout_duration_margin[high][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[high][s_high], vbios->high_voltage_max_dispclk)) अणु
		data->cpup_state_change_enable = bw_def_yes;
		अगर (bw_ltn(data->dispclk_required_क्रम_blackout_recovery[high][s_high], vbios->high_voltage_max_dispclk)) अणु
			data->cpuc_state_change_enable = bw_def_yes;
		पूर्ण
		अन्यथा अणु
			data->cpuc_state_change_enable = bw_def_no;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		data->cpup_state_change_enable = bw_def_no;
		data->cpuc_state_change_enable = bw_def_no;
	पूर्ण
	/*nb p-state change enable*/
	/*क्रम dram speed/p-state change to be possible क्रम a yclk(pclk) and sclk level there has to be positive margin and the dispclk required has to be*/
	/*below the maximum.*/
	/*the dram speed/p-state change margin is the minimum क्रम all surfaces of the maximum latency hiding minus the dram speed/p-state change latency,*/
	/*minus the dmअगर burst समय, minus the source line transfer समय*/
	/*the maximum latency hiding is the minimum latency hiding plus one source line used क्रम de-tiling in the line buffer, plus half the urgent latency*/
	/*अगर stutter and dram घड़ी state change are gated beक्रमe cursor then the cursor latency hiding करोes not limit stutter or dram घड़ी state change*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			/*maximum_latency_hiding(i) = minimum_latency_hiding(i) + 1 / vsr(i) **/
			/*      h_total(i) / pixel_rate(i) + 0.5 * total_dmअगरmc_urgent_latency*/
			data->maximum_latency_hiding[i] = bw_add(data->minimum_latency_hiding[i],
				bw_mul(bw_frc_to_fixed(5, 10), data->total_dmअगरmc_urgent_latency));
			data->maximum_latency_hiding_with_cursor[i] = bw_min2(data->maximum_latency_hiding[i], data->cursor_latency_hiding[i]);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= 2; i++) अणु
		क्रम (j = 0; j <= 7; j++) अणु
			data->min_dram_speed_change_margin[i][j] = bw_पूर्णांक_to_fixed(9999);
			data->dram_speed_change_margin = bw_पूर्णांक_to_fixed(9999);
			data->dispclk_required_क्रम_dram_speed_change[i][j] = bw_पूर्णांक_to_fixed(0);
			data->num_displays_with_margin[i][j] = 0;
			क्रम (k = 0; k <= maximum_number_of_surfaces - 1; k++) अणु
				अगर (data->enable[k]) अणु
					अगर (surface_type[k] != bw_def_display_ग_लिखो_back420_luma && surface_type[k] != bw_def_display_ग_लिखो_back420_chroma) अणु
						data->dram_speed_change_margin = bw_sub(bw_sub(bw_sub(data->maximum_latency_hiding_with_cursor[k], vbios->nbp_state_change_latency), data->dmअगर_burst_समय[i][j]), data->dram_speed_change_line_source_transfer_समय[k][i][j]);
						अगर ((bw_mtn(data->dram_speed_change_margin, bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dram_speed_change_margin, bw_पूर्णांक_to_fixed(9999)))) अणु
							/*determine the minimum dram घड़ी change margin क्रम each set of घड़ी frequencies*/
							data->min_dram_speed_change_margin[i][j] = bw_min2(data->min_dram_speed_change_margin[i][j], data->dram_speed_change_margin);
							/*compute the maximum घड़ी frequuency required क्रम the dram घड़ी change at each set of घड़ी frequencies*/
							data->dispclk_required_क्रम_dram_speed_change_pipe[i][j] = bw_max2(bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_first_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_sub(bw_sub(bw_sub(data->maximum_latency_hiding_with_cursor[k], vbios->nbp_state_change_latency), data->dmअगर_burst_समय[i][j]), data->dram_speed_change_line_source_transfer_समय[k][i][j]))), bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_last_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_add(bw_sub(bw_sub(bw_sub(data->maximum_latency_hiding_with_cursor[k], vbios->nbp_state_change_latency), data->dmअगर_burst_समय[i][j]), data->dram_speed_change_line_source_transfer_समय[k][i][j]), data->active_समय[k]))));
							अगर ((bw_ltn(data->dispclk_required_क्रम_dram_speed_change_pipe[i][j], vbios->high_voltage_max_dispclk))) अणु
								data->display_pstate_change_enable[k] = 1;
								data->num_displays_with_margin[i][j] = data->num_displays_with_margin[i][j] + 1;
								data->dispclk_required_क्रम_dram_speed_change[i][j] = bw_max2(data->dispclk_required_क्रम_dram_speed_change[i][j], data->dispclk_required_क्रम_dram_speed_change_pipe[i][j]);
							पूर्ण
						पूर्ण
					पूर्ण
					अन्यथा अणु
						data->dram_speed_change_margin = bw_sub(bw_sub(bw_sub(bw_sub(data->maximum_latency_hiding_with_cursor[k], vbios->nbp_state_change_latency), data->dmअगर_burst_समय[i][j]), data->mcअगरwr_burst_समय[i][j]), data->dram_speed_change_line_source_transfer_समय[k][i][j]);
						अगर ((bw_mtn(data->dram_speed_change_margin, bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dram_speed_change_margin, bw_पूर्णांक_to_fixed(9999)))) अणु
							/*determine the minimum dram घड़ी change margin क्रम each display pipe*/
							data->min_dram_speed_change_margin[i][j] = bw_min2(data->min_dram_speed_change_margin[i][j], data->dram_speed_change_margin);
							/*compute the maximum घड़ी frequuency required क्रम the dram घड़ी change at each set of घड़ी frequencies*/
							data->dispclk_required_क्रम_dram_speed_change_pipe[i][j] = bw_max2(bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_first_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_sub(bw_sub(bw_sub(bw_sub(data->maximum_latency_hiding_with_cursor[k], vbios->nbp_state_change_latency), data->dmअगर_burst_समय[i][j]), data->dram_speed_change_line_source_transfer_समय[k][i][j]), data->mcअगरwr_burst_समय[i][j]))), bw_भाग(bw_भाग(bw_mul(data->src_pixels_क्रम_last_output_pixel[k], dceip->display_pipe_throughput_factor), dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_add(bw_sub(bw_sub(bw_sub(bw_sub(data->maximum_latency_hiding_with_cursor[k], vbios->nbp_state_change_latency), data->dmअगर_burst_समय[i][j]), data->dram_speed_change_line_source_transfer_समय[k][i][j]), data->mcअगरwr_burst_समय[i][j]), data->active_समय[k]))));
							अगर ((bw_ltn(data->dispclk_required_क्रम_dram_speed_change_pipe[i][j], vbios->high_voltage_max_dispclk))) अणु
								data->display_pstate_change_enable[k] = 1;
								data->num_displays_with_margin[i][j] = data->num_displays_with_margin[i][j] + 1;
								data->dispclk_required_क्रम_dram_speed_change[i][j] = bw_max2(data->dispclk_required_क्रम_dram_speed_change[i][j], data->dispclk_required_क्रम_dram_speed_change_pipe[i][j]);
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*determine the number of displays with margin to चयन in the v_active region*/
	क्रम (k = 0; k <= maximum_number_of_surfaces - 1; k++) अणु
		अगर (data->enable[k] == 1 && data->display_pstate_change_enable[k] == 1) अणु
			number_of_displays_enabled_with_margin = number_of_displays_enabled_with_margin + 1;
		पूर्ण
	पूर्ण
	/*determine the number of displays that करोn't have any dram घड़ी change margin, but*/
	/*have the same resolution.  these displays can चयन in a common vblank region अगर*/
	/*their frames are aligned.*/
	data->min_vblank_dram_speed_change_margin = bw_पूर्णांक_to_fixed(9999);
	क्रम (k = 0; k <= maximum_number_of_surfaces - 1; k++) अणु
		अगर (data->enable[k]) अणु
			अगर (surface_type[k] != bw_def_display_ग_लिखो_back420_luma && surface_type[k] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->v_blank_dram_speed_change_margin[k] = bw_sub(bw_sub(bw_sub(bw_भाग(bw_mul((bw_sub(data->v_total[k], bw_sub(bw_भाग(data->src_height[k], data->v_scale_ratio[k]), bw_पूर्णांक_to_fixed(4)))), data->h_total[k]), data->pixel_rate[k]), vbios->nbp_state_change_latency), data->dmअगर_burst_समय[low][s_low]), data->dram_speed_change_line_source_transfer_समय[k][low][s_low]);
				data->min_vblank_dram_speed_change_margin = bw_min2(data->min_vblank_dram_speed_change_margin, data->v_blank_dram_speed_change_margin[k]);
			पूर्ण
			अन्यथा अणु
				data->v_blank_dram_speed_change_margin[k] = bw_sub(bw_sub(bw_sub(bw_sub(bw_भाग(bw_mul((bw_sub(data->v_total[k], bw_sub(bw_भाग(data->src_height[k], data->v_scale_ratio[k]), bw_पूर्णांक_to_fixed(4)))), data->h_total[k]), data->pixel_rate[k]), vbios->nbp_state_change_latency), data->dmअगर_burst_समय[low][s_low]), data->mcअगरwr_burst_समय[low][s_low]), data->dram_speed_change_line_source_transfer_समय[k][low][s_low]);
				data->min_vblank_dram_speed_change_margin = bw_min2(data->min_vblank_dram_speed_change_margin, data->v_blank_dram_speed_change_margin[k]);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		data->displays_with_same_mode[i] = bw_पूर्णांक_to_fixed(0);
		अगर (data->enable[i] == 1 && data->display_pstate_change_enable[i] == 0 && bw_mtn(data->v_blank_dram_speed_change_margin[i], bw_पूर्णांक_to_fixed(0))) अणु
			क्रम (j = 0; j <= maximum_number_of_surfaces - 1; j++) अणु
				अगर ((i == j || data->display_synchronization_enabled) && (data->enable[j] == 1 && bw_equ(data->source_width_rounded_up_to_chunks[i], data->source_width_rounded_up_to_chunks[j]) && bw_equ(data->source_height_rounded_up_to_chunks[i], data->source_height_rounded_up_to_chunks[j]) && bw_equ(data->vsr[i], data->vsr[j]) && bw_equ(data->hsr[i], data->hsr[j]) && bw_equ(data->pixel_rate[i], data->pixel_rate[j]))) अणु
					data->displays_with_same_mode[i] = bw_add(data->displays_with_same_mode[i], bw_पूर्णांक_to_fixed(1));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*compute the maximum number of aligned displays with no margin*/
	number_of_aligned_displays_with_no_margin = 0;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		number_of_aligned_displays_with_no_margin = bw_fixed_to_पूर्णांक(bw_max2(bw_पूर्णांक_to_fixed(number_of_aligned_displays_with_no_margin), data->displays_with_same_mode[i]));
	पूर्ण
	/*dram घड़ी change is possible, अगर all displays have positive margin except क्रम one display or a group of*/
	/*aligned displays with the same timing.*/
	/*the display(s) with the negative margin can be चयनed in the v_blank region जबतक the other*/
	/*displays are in v_blank or v_active.*/
	अगर (number_of_displays_enabled_with_margin > 0 && (number_of_displays_enabled_with_margin + number_of_aligned_displays_with_no_margin) == number_of_displays_enabled && bw_mtn(data->min_dram_speed_change_margin[high][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[high][s_high], bw_पूर्णांक_to_fixed(9999)) && bw_ltn(data->dispclk_required_क्रम_dram_speed_change[high][s_high], vbios->high_voltage_max_dispclk)) अणु
		data->nbp_state_change_enable = bw_def_yes;
	पूर्ण
	अन्यथा अणु
		data->nbp_state_change_enable = bw_def_no;
	पूर्ण
	/*dram घड़ी change is possible only in vblank अगर all displays are aligned and have no margin*/
	अगर (number_of_aligned_displays_with_no_margin == number_of_displays_enabled) अणु
		nbp_state_change_enable_blank = bw_def_yes;
	पूर्ण
	अन्यथा अणु
		nbp_state_change_enable_blank = bw_def_no;
	पूर्ण

	/*average bandwidth*/
	/*the average bandwidth with no compression is the vertical active समय is the source width बार the bytes per pixel भागided by the line समय, multiplied by the vertical scale ratio and the ratio of bytes per request भागided by the useful bytes per request.*/
	/*the average bandwidth with compression is the same, भागided by the compression ratio*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->average_bandwidth_no_compression[i] = bw_भाग(bw_mul(bw_mul(bw_भाग(bw_mul(data->source_width_rounded_up_to_chunks[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), (bw_भाग(data->h_total[i], data->pixel_rate[i]))), data->vsr[i]), data->bytes_per_request[i]), data->useful_bytes_per_request[i]);
			data->average_bandwidth[i] = bw_भाग(data->average_bandwidth_no_compression[i], data->compression_rate[i]);
		पूर्ण
	पूर्ण
	data->total_average_bandwidth_no_compression = bw_पूर्णांक_to_fixed(0);
	data->total_average_bandwidth = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->total_average_bandwidth_no_compression = bw_add(data->total_average_bandwidth_no_compression, data->average_bandwidth_no_compression[i]);
			data->total_average_bandwidth = bw_add(data->total_average_bandwidth, data->average_bandwidth[i]);
		पूर्ण
	पूर्ण

	/*required yclk(pclk)*/
	/*yclk requirement only makes sense अगर the dmअगर and mcअगरwr data total page बंद-खोलो समय is less than the समय क्रम data transfer and the total pte requests fit in the scatter-gather saw queque size*/
	/*अगर that is the हाल, the yclk requirement is the maximum of the ones required by dmअगर and mcअगरwr, and the high/low yclk(pclk) is chosen accordingly*/
	/*high yclk(pclk) has to be selected when dram speed/p-state change is not possible.*/
	data->min_cursor_memory_पूर्णांकerface_buffer_size_in_समय = bw_पूर्णांक_to_fixed(9999);
	/* number of cursor lines stored in the cursor data वापस buffer*/
	num_cursor_lines = 0;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_mtn(data->cursor_width_pixels[i], bw_पूर्णांक_to_fixed(0))) अणु
				/*compute number of cursor lines stored in data वापस buffer*/
				अगर (bw_leq(data->cursor_width_pixels[i], bw_पूर्णांक_to_fixed(64)) && dceip->large_cursor == 1) अणु
					num_cursor_lines = 4;
				पूर्ण
				अन्यथा अणु
					num_cursor_lines = 2;
				पूर्ण
				data->min_cursor_memory_पूर्णांकerface_buffer_size_in_समय = bw_min2(data->min_cursor_memory_पूर्णांकerface_buffer_size_in_समय, bw_भाग(bw_mul(bw_भाग(bw_पूर्णांक_to_fixed(num_cursor_lines), data->vsr[i]), data->h_total[i]), data->pixel_rate[i]));
			पूर्ण
		पूर्ण
	पूर्ण
	/*compute minimum समय to पढ़ो one chunk from the dmअगर buffer*/
	अगर (number_of_displays_enabled > 2) अणु
		data->chunk_request_delay = 0;
	पूर्ण
	अन्यथा अणु
		data->chunk_request_delay = bw_fixed_to_पूर्णांक(bw_भाग(bw_पूर्णांक_to_fixed(512), vbios->high_voltage_max_dispclk));
	पूर्ण
	data->min_पढ़ो_buffer_size_in_समय = bw_min2(data->min_cursor_memory_पूर्णांकerface_buffer_size_in_समय, data->min_dmअगर_size_in_समय);
	data->display_पढ़ोs_समय_क्रम_data_transfer = bw_sub(bw_sub(data->min_पढ़ो_buffer_size_in_समय, data->total_dmअगरmc_urgent_latency), bw_पूर्णांक_to_fixed(data->chunk_request_delay));
	data->display_ग_लिखोs_समय_क्रम_data_transfer = bw_sub(data->min_mcअगरwr_size_in_समय, vbios->mcअगरwrmc_urgent_latency);
	data->dmअगर_required_dram_bandwidth = bw_भाग(data->total_display_पढ़ोs_required_dram_access_data, data->display_पढ़ोs_समय_क्रम_data_transfer);
	data->mcअगरwr_required_dram_bandwidth = bw_भाग(data->total_display_ग_लिखोs_required_dram_access_data, data->display_ग_लिखोs_समय_क्रम_data_transfer);
	data->required_dmअगरmc_urgent_latency_क्रम_page_बंद_खोलो = bw_भाग((bw_sub(data->min_पढ़ो_buffer_size_in_समय, data->dmअगर_total_page_बंद_खोलो_समय)), data->total_dmअगरmc_urgent_trips);
	data->required_mcअगरmcwr_urgent_latency = bw_sub(data->min_mcअगरwr_size_in_समय, data->mcअगरwr_total_page_बंद_खोलो_समय);
	अगर (bw_mtn(data->scatter_gather_total_pte_requests, dceip->maximum_total_outstanding_pte_requests_allowed_by_saw)) अणु
		data->required_dram_bandwidth_gbyte_per_second = bw_पूर्णांक_to_fixed(9999);
		yclk_message = bw_def_exceeded_allowed_outstanding_pte_req_queue_size;
		data->y_clk_level = high;
		data->dram_bandwidth = bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[high]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels));
	पूर्ण
	अन्यथा अगर (bw_mtn(vbios->dmअगरmc_urgent_latency, data->required_dmअगरmc_urgent_latency_क्रम_page_बंद_खोलो) || bw_mtn(vbios->mcअगरwrmc_urgent_latency, data->required_mcअगरmcwr_urgent_latency)) अणु
		data->required_dram_bandwidth_gbyte_per_second = bw_पूर्णांक_to_fixed(9999);
		yclk_message = bw_def_exceeded_allowed_page_बंद_खोलो;
		data->y_clk_level = high;
		data->dram_bandwidth = bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[high]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels));
	पूर्ण
	अन्यथा अणु
		data->required_dram_bandwidth_gbyte_per_second = bw_भाग(bw_max2(data->dmअगर_required_dram_bandwidth, data->mcअगरwr_required_dram_bandwidth), bw_पूर्णांक_to_fixed(1000));
		अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation, 100),yclk[low]),bw_भाग(bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits),bw_पूर्णांक_to_fixed(8))),bw_पूर्णांक_to_fixed(vbios->number_of_dram_channels)))
				&& bw_ltn(bw_mul(data->required_dram_bandwidth_gbyte_per_second, bw_पूर्णांक_to_fixed(1000)), bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[low]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels))) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[low][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[low][s_high], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[low][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[low][s_high], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[low][s_high], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[low][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[low][s_high], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[low][s_high], vbios->high_voltage_max_dispclk) && data->num_displays_with_margin[low][s_high] == number_of_displays_enabled_with_margin))) अणु
			yclk_message = bw_fixed_to_पूर्णांक(vbios->low_yclk);
			data->y_clk_level = low;
			data->dram_bandwidth = bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[low]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels));
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation, 100),yclk[mid]),bw_भाग(bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits),bw_पूर्णांक_to_fixed(8))),bw_पूर्णांक_to_fixed(vbios->number_of_dram_channels)))
				&& bw_ltn(bw_mul(data->required_dram_bandwidth_gbyte_per_second, bw_पूर्णांक_to_fixed(1000)), bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[mid]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels))) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[mid][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[mid][s_high], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[mid][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[mid][s_high], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[mid][s_high], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[mid][s_high], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[mid][s_high], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[mid][s_high], vbios->high_voltage_max_dispclk) && data->num_displays_with_margin[mid][s_high] == number_of_displays_enabled_with_margin))) अणु
			yclk_message = bw_fixed_to_पूर्णांक(vbios->mid_yclk);
			data->y_clk_level = mid;
			data->dram_bandwidth = bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[mid]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels));
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation, 100),yclk[high]),bw_भाग(bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits),bw_पूर्णांक_to_fixed(8))),bw_पूर्णांक_to_fixed(vbios->number_of_dram_channels)))
				&& bw_ltn(bw_mul(data->required_dram_bandwidth_gbyte_per_second, bw_पूर्णांक_to_fixed(1000)), bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[high]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels)))) अणु
			yclk_message = bw_fixed_to_पूर्णांक(vbios->high_yclk);
			data->y_clk_level = high;
			data->dram_bandwidth = bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[high]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels));
		पूर्ण
		अन्यथा अणु
			yclk_message = bw_def_exceeded_allowed_maximum_bw;
			data->y_clk_level = high;
			data->dram_bandwidth = bw_mul(bw_भाग(bw_mul(bw_mul(data->dram_efficiency, yclk[high]), bw_पूर्णांक_to_fixed(vbios->dram_channel_width_in_bits)), bw_पूर्णांक_to_fixed(8)), bw_पूर्णांक_to_fixed(data->number_of_dram_channels));
		पूर्ण
	पूर्ण
	/*required sclk*/
	/*sclk requirement only makes sense अगर the total pte requests fit in the scatter-gather saw queque size*/
	/*अगर that is the हाल, the sclk requirement is the maximum of the ones required by dmअगर and mcअगरwr, and the high/mid/low sclk is chosen accordingly, unless that choice results in क्रमesaking dram speed/nb p-state change.*/
	/*the dmअगर and mcअगरwr sclk required is the one that allows the transfer of all pipe's data buffer size through the sclk bus in the समय क्रम data transfer*/
	/*क्रम dmअगर, pte and cursor requests have to be included.*/
	data->dmअगर_required_sclk = bw_भाग(bw_भाग(data->total_display_पढ़ोs_required_data, data->display_पढ़ोs_समय_क्रम_data_transfer), (bw_mul(vbios->data_वापस_bus_width, bw_frc_to_fixed(dceip->percent_of_ideal_port_bw_received_after_urgent_latency, 100))));
	data->mcअगरwr_required_sclk = bw_भाग(bw_भाग(data->total_display_ग_लिखोs_required_data, data->display_ग_लिखोs_समय_क्रम_data_transfer), vbios->data_वापस_bus_width);
	अगर (bw_mtn(data->scatter_gather_total_pte_requests, dceip->maximum_total_outstanding_pte_requests_allowed_by_saw)) अणु
		data->required_sclk = bw_पूर्णांक_to_fixed(9999);
		sclk_message = bw_def_exceeded_allowed_outstanding_pte_req_queue_size;
		data->sclk_level = s_high;
	पूर्ण
	अन्यथा अगर (bw_mtn(vbios->dmअगरmc_urgent_latency, data->required_dmअगरmc_urgent_latency_क्रम_page_बंद_खोलो) || bw_mtn(vbios->mcअगरwrmc_urgent_latency, data->required_mcअगरmcwr_urgent_latency)) अणु
		data->required_sclk = bw_पूर्णांक_to_fixed(9999);
		sclk_message = bw_def_exceeded_allowed_page_बंद_खोलो;
		data->sclk_level = s_high;
	पूर्ण
	अन्यथा अणु
		data->required_sclk = bw_max2(data->dmअगर_required_sclk, data->mcअगरwr_required_sclk);
		अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[low]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_low]) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_low], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_low], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_low], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_low], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][s_low], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[data->y_clk_level][s_low], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[data->y_clk_level][s_low], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][s_low], vbios->low_voltage_max_dispclk) && data->num_displays_with_margin[data->y_clk_level][s_low] == number_of_displays_enabled_with_margin))) अणु
			sclk_message = bw_def_low;
			data->sclk_level = s_low;
			data->required_sclk = vbios->low_sclk;
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[mid]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_mid1]) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid1], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid1], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid1], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid1], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][s_mid1], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid1], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid1], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][s_mid1], vbios->mid_voltage_max_dispclk) && data->num_displays_with_margin[data->y_clk_level][s_mid1] == number_of_displays_enabled_with_margin))) अणु
			sclk_message = bw_def_mid;
			data->sclk_level = s_mid1;
			data->required_sclk = vbios->mid1_sclk;
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[s_mid2]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_mid2]) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid2], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid2], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid2], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid2], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][s_mid2], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid2], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid2], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][s_mid2], vbios->mid_voltage_max_dispclk) && data->num_displays_with_margin[data->y_clk_level][s_mid2] == number_of_displays_enabled_with_margin))) अणु
			sclk_message = bw_def_mid;
			data->sclk_level = s_mid2;
			data->required_sclk = vbios->mid2_sclk;
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[s_mid3]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_mid3]) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid3], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid3], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid3], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid3], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][s_mid3], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid3], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid3], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][s_mid3], vbios->mid_voltage_max_dispclk) && data->num_displays_with_margin[data->y_clk_level][s_mid3] == number_of_displays_enabled_with_margin))) अणु
			sclk_message = bw_def_mid;
			data->sclk_level = s_mid3;
			data->required_sclk = vbios->mid3_sclk;
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[s_mid4]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_mid4]) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid4], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid4], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid4], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid4], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][s_mid4], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid4], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid4], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][s_mid4], vbios->mid_voltage_max_dispclk) && data->num_displays_with_margin[data->y_clk_level][s_mid4] == number_of_displays_enabled_with_margin))) अणु
			sclk_message = bw_def_mid;
			data->sclk_level = s_mid4;
			data->required_sclk = vbios->mid4_sclk;
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[s_mid5]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_mid5]) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid5], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid5], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid5], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid5], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][s_mid5], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid5], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid5], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][s_mid5], vbios->mid_voltage_max_dispclk) && data->num_displays_with_margin[data->y_clk_level][s_mid5] == number_of_displays_enabled_with_margin))) अणु
			sclk_message = bw_def_mid;
			data->sclk_level = s_mid5;
			data->required_sclk = vbios->mid5_sclk;
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[s_mid6]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_mid6]) && (data->cpup_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid6], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid6], vbios->high_voltage_max_dispclk))) && (data->cpuc_state_change_enable == bw_def_no || (bw_mtn(data->blackout_duration_margin[data->y_clk_level][s_mid6], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][s_mid6], vbios->high_voltage_max_dispclk) && bw_ltn(data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][s_mid6], vbios->high_voltage_max_dispclk))) && (!data->increase_voltage_to_support_mclk_चयन || data->nbp_state_change_enable == bw_def_no || (bw_mtn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid6], bw_पूर्णांक_to_fixed(0)) && bw_ltn(data->min_dram_speed_change_margin[data->y_clk_level][s_mid6], bw_पूर्णांक_to_fixed(9999)) && bw_leq(data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][s_mid6], vbios->high_voltage_max_dispclk) && data->num_displays_with_margin[data->y_clk_level][s_mid6] == number_of_displays_enabled_with_margin))) अणु
			sclk_message = bw_def_mid;
			data->sclk_level = s_mid6;
			data->required_sclk = vbios->mid6_sclk;
		पूर्ण
		अन्यथा अगर (bw_ltn(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[s_high]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_high])) अणु
			sclk_message = bw_def_high;
			data->sclk_level = s_high;
			data->required_sclk = vbios->high_sclk;
		पूर्ण
		अन्यथा अगर (bw_meq(data->total_average_bandwidth_no_compression, bw_mul(bw_mul(bw_frc_to_fixed(dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation, 100),sclk[s_high]),vbios->data_वापस_bus_width))
				&& bw_ltn(data->required_sclk, sclk[s_high])) अणु
			sclk_message = bw_def_high;
			data->sclk_level = s_high;
			data->required_sclk = vbios->high_sclk;
		पूर्ण
		अन्यथा अणु
			sclk_message = bw_def_exceeded_allowed_maximum_sclk;
			data->sclk_level = s_high;
			/*required_sclk = high_sclk*/
		पूर्ण
	पूर्ण
	/*dispclk*/
	/*अगर dispclk is set to the maximum, ramping is not required.  dispclk required without ramping is less than the dispclk required with ramping.*/
	/*अगर dispclk required without ramping is more than the maximum dispclk, that is the dispclk required, and the mode is not supported*/
	/*अगर that करोes not happen, but dispclk required with ramping is more than the maximum dispclk, dispclk required is just the maximum dispclk*/
	/*अगर that करोes not happen either, dispclk required is the dispclk required with ramping.*/
	/*dispclk required without ramping is the maximum of the one required क्रम display pipe pixel throughput, क्रम scaler throughput, क्रम total पढ़ो request thrrougput and क्रम dram/np p-state change अगर enabled.*/
	/*the display pipe pixel throughput is the maximum of lines in per line out in the beginning of the frame and lines in per line out in the middle of the frame multiplied by the horizontal blank and chunk granularity factor, altogether multiplied by the ratio of the source width to the line समय, भागided by the line buffer pixels per dispclk throughput, and multiplied by the display pipe throughput factor.*/
	/*the horizontal blank and chunk granularity factor is the ratio of the line समय भागided by the line समय minus half the horizontal blank and chunk समय.  it applies when the lines in per line out is not 2 or 4.*/
	/*the dispclk required क्रम scaler throughput is the product of the pixel rate and the scaling limits factor.*/
	/*the dispclk required क्रम total पढ़ो request throughput is the product of the peak request-per-second bandwidth and the dispclk cycles per request, भागided by the request efficiency.*/
	/*क्रम the dispclk required with ramping, instead of multiplying just the pipe throughput by the display pipe throughput factor, we multiply the scaler and pipe throughput by the ramping factor.*/
	/*the scaling limits factor is the product of the horizontal scale ratio, and the ratio of the vertical taps भागided by the scaler efficiency clamped to at least 1.*/
	/*the scaling limits factor itself it also clamped to at least 1*/
	/*अगर करोing करोwnscaling with the pre-करोwnscaler enabled, the horizontal scale ratio should not be considered above (use "1")*/
	data->करोwnspपढ़ो_factor = bw_add(bw_पूर्णांक_to_fixed(1), bw_भाग(vbios->करोwn_spपढ़ो_percentage, bw_पूर्णांक_to_fixed(100)));
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (surface_type[i] == bw_def_graphics) अणु
				चयन (data->lb_bpc[i]) अणु
				हाल 6:
					data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency6_bit_per_component;
					अवरोध;
				हाल 8:
					data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency8_bit_per_component;
					अवरोध;
				हाल 10:
					data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency10_bit_per_component;
					अवरोध;
				शेष:
					data->v_scaler_efficiency = dceip->graphics_vscaler_efficiency12_bit_per_component;
					अवरोध;
				पूर्ण
				अगर (data->use_alpha[i] == 1) अणु
					data->v_scaler_efficiency = bw_min2(data->v_scaler_efficiency, dceip->alpha_vscaler_efficiency);
				पूर्ण
			पूर्ण
			अन्यथा अणु
				चयन (data->lb_bpc[i]) अणु
				हाल 6:
					data->v_scaler_efficiency = dceip->underlay_vscaler_efficiency6_bit_per_component;
					अवरोध;
				हाल 8:
					data->v_scaler_efficiency = dceip->underlay_vscaler_efficiency8_bit_per_component;
					अवरोध;
				हाल 10:
					data->v_scaler_efficiency = dceip->underlay_vscaler_efficiency10_bit_per_component;
					अवरोध;
				शेष:
					data->v_scaler_efficiency = dceip->underlay_vscaler_efficiency12_bit_per_component;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (dceip->pre_करोwnscaler_enabled && bw_mtn(data->hsr[i], bw_पूर्णांक_to_fixed(1))) अणु
				data->scaler_limits_factor = bw_max2(bw_भाग(data->v_taps[i], data->v_scaler_efficiency), bw_भाग(data->source_width_rounded_up_to_chunks[i], data->h_total[i]));
			पूर्ण
			अन्यथा अणु
				data->scaler_limits_factor = bw_max3(bw_पूर्णांक_to_fixed(1), bw_उच्चमान2(bw_भाग(data->h_taps[i], bw_पूर्णांक_to_fixed(4)), bw_पूर्णांक_to_fixed(1)), bw_mul(data->hsr[i], bw_max2(bw_भाग(data->v_taps[i], data->v_scaler_efficiency), bw_पूर्णांक_to_fixed(1))));
			पूर्ण
			data->display_pipe_pixel_throughput = bw_भाग(bw_भाग(bw_mul(bw_max2(data->lb_lines_in_per_line_out_in_beginning_of_frame[i], bw_mul(data->lb_lines_in_per_line_out_in_middle_of_frame[i], data->horizontal_blank_and_chunk_granularity_factor[i])), data->source_width_rounded_up_to_chunks[i]), (bw_भाग(data->h_total[i], data->pixel_rate[i]))), dceip->lb_ग_लिखो_pixels_per_dispclk);
			data->dispclk_required_without_ramping[i] = bw_mul(data->करोwnspपढ़ो_factor, bw_max2(bw_mul(data->pixel_rate[i], data->scaler_limits_factor), bw_mul(dceip->display_pipe_throughput_factor, data->display_pipe_pixel_throughput)));
			data->dispclk_required_with_ramping[i] = bw_mul(dceip->dispclk_ramping_factor, bw_max2(bw_mul(data->pixel_rate[i], data->scaler_limits_factor), data->display_pipe_pixel_throughput));
		पूर्ण
	पूर्ण
	data->total_dispclk_required_with_ramping = bw_पूर्णांक_to_fixed(0);
	data->total_dispclk_required_without_ramping = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_ltn(data->total_dispclk_required_with_ramping, data->dispclk_required_with_ramping[i])) अणु
				data->total_dispclk_required_with_ramping = data->dispclk_required_with_ramping[i];
			पूर्ण
			अगर (bw_ltn(data->total_dispclk_required_without_ramping, data->dispclk_required_without_ramping[i])) अणु
				data->total_dispclk_required_without_ramping = data->dispclk_required_without_ramping[i];
			पूर्ण
		पूर्ण
	पूर्ण
	data->total_पढ़ो_request_bandwidth = bw_पूर्णांक_to_fixed(0);
	data->total_ग_लिखो_request_bandwidth = bw_पूर्णांक_to_fixed(0);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->total_पढ़ो_request_bandwidth = bw_add(data->total_पढ़ो_request_bandwidth, data->request_bandwidth[i]);
			पूर्ण
			अन्यथा अणु
				data->total_ग_लिखो_request_bandwidth = bw_add(data->total_ग_लिखो_request_bandwidth, data->request_bandwidth[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	data->dispclk_required_क्रम_total_पढ़ो_request_bandwidth = bw_भाग(bw_mul(data->total_पढ़ो_request_bandwidth, dceip->dispclk_per_request), dceip->request_efficiency);
	data->total_dispclk_required_with_ramping_with_request_bandwidth = bw_max2(data->total_dispclk_required_with_ramping, data->dispclk_required_क्रम_total_पढ़ो_request_bandwidth);
	data->total_dispclk_required_without_ramping_with_request_bandwidth = bw_max2(data->total_dispclk_required_without_ramping, data->dispclk_required_क्रम_total_पढ़ो_request_bandwidth);
	अगर (data->cpuc_state_change_enable == bw_def_yes) अणु
		data->total_dispclk_required_with_ramping_with_request_bandwidth = bw_max3(data->total_dispclk_required_with_ramping_with_request_bandwidth, data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][data->sclk_level], data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][data->sclk_level]);
		data->total_dispclk_required_without_ramping_with_request_bandwidth = bw_max3(data->total_dispclk_required_without_ramping_with_request_bandwidth, data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][data->sclk_level], data->dispclk_required_क्रम_blackout_recovery[data->y_clk_level][data->sclk_level]);
	पूर्ण
	अगर (data->cpup_state_change_enable == bw_def_yes) अणु
		data->total_dispclk_required_with_ramping_with_request_bandwidth = bw_max2(data->total_dispclk_required_with_ramping_with_request_bandwidth, data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][data->sclk_level]);
		data->total_dispclk_required_without_ramping_with_request_bandwidth = bw_max2(data->total_dispclk_required_without_ramping_with_request_bandwidth, data->dispclk_required_क्रम_blackout_duration[data->y_clk_level][data->sclk_level]);
	पूर्ण
	अगर (data->nbp_state_change_enable == bw_def_yes && data->increase_voltage_to_support_mclk_चयन) अणु
		data->total_dispclk_required_with_ramping_with_request_bandwidth = bw_max2(data->total_dispclk_required_with_ramping_with_request_bandwidth, data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][data->sclk_level]);
		data->total_dispclk_required_without_ramping_with_request_bandwidth = bw_max2(data->total_dispclk_required_without_ramping_with_request_bandwidth, data->dispclk_required_क्रम_dram_speed_change[data->y_clk_level][data->sclk_level]);
	पूर्ण
	अगर (bw_ltn(data->total_dispclk_required_with_ramping_with_request_bandwidth, vbios->high_voltage_max_dispclk)) अणु
		data->dispclk = data->total_dispclk_required_with_ramping_with_request_bandwidth;
	पूर्ण
	अन्यथा अगर (bw_ltn(data->total_dispclk_required_without_ramping_with_request_bandwidth, vbios->high_voltage_max_dispclk)) अणु
		data->dispclk = vbios->high_voltage_max_dispclk;
	पूर्ण
	अन्यथा अणु
		data->dispclk = data->total_dispclk_required_without_ramping_with_request_bandwidth;
	पूर्ण
	/* required core voltage*/
	/* the core voltage required is low अगर sclk, yclk(pclk)and dispclk are within the low limits*/
	/* otherwise, the core voltage required is medium अगर yclk (pclk) is within the low limit and sclk and dispclk are within the medium limit*/
	/* otherwise, the core voltage required is high अगर the three घड़ीs are within the high limits*/
	/* otherwise, or अगर the mode is not supported, core voltage requirement is not applicable*/
	अगर (pipe_check == bw_def_notok) अणु
		voltage = bw_def_na;
	पूर्ण
	अन्यथा अगर (mode_check == bw_def_notok) अणु
		voltage = bw_def_notok;
	पूर्ण
	अन्यथा अगर (bw_equ(bw_पूर्णांक_to_fixed(yclk_message), vbios->low_yclk) && sclk_message == bw_def_low && bw_ltn(data->dispclk, vbios->low_voltage_max_dispclk)) अणु
		voltage = bw_def_0_72;
	पूर्ण
	अन्यथा अगर ((bw_equ(bw_पूर्णांक_to_fixed(yclk_message), vbios->low_yclk) || bw_equ(bw_पूर्णांक_to_fixed(yclk_message), vbios->mid_yclk)) && (sclk_message == bw_def_low || sclk_message == bw_def_mid) && bw_ltn(data->dispclk, vbios->mid_voltage_max_dispclk)) अणु
		voltage = bw_def_0_8;
	पूर्ण
	अन्यथा अगर ((bw_equ(bw_पूर्णांक_to_fixed(yclk_message), vbios->low_yclk) || bw_equ(bw_पूर्णांक_to_fixed(yclk_message), vbios->mid_yclk) || bw_equ(bw_पूर्णांक_to_fixed(yclk_message), vbios->high_yclk)) && (sclk_message == bw_def_low || sclk_message == bw_def_mid || sclk_message == bw_def_high) && bw_leq(data->dispclk, vbios->high_voltage_max_dispclk)) अणु
		अगर ((data->nbp_state_change_enable == bw_def_no && nbp_state_change_enable_blank == bw_def_no)) अणु
			voltage = bw_def_high_no_nbp_state_change;
		पूर्ण
		अन्यथा अणु
			voltage = bw_def_0_9;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		voltage = bw_def_notok;
	पूर्ण
	अगर (voltage == bw_def_0_72) अणु
		data->max_phyclk = vbios->low_voltage_max_phyclk;
	पूर्ण
	अन्यथा अगर (voltage == bw_def_0_8) अणु
		data->max_phyclk = vbios->mid_voltage_max_phyclk;
	पूर्ण
	अन्यथा अणु
		data->max_phyclk = vbios->high_voltage_max_phyclk;
	पूर्ण
	/*required blackout recovery समय*/
	data->blackout_recovery_समय = bw_पूर्णांक_to_fixed(0);
	क्रम (k = 0; k <= maximum_number_of_surfaces - 1; k++) अणु
		अगर (data->enable[k] && bw_mtn(vbios->blackout_duration, bw_पूर्णांक_to_fixed(0)) && data->cpup_state_change_enable == bw_def_yes) अणु
			अगर (surface_type[k] != bw_def_display_ग_लिखो_back420_luma && surface_type[k] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->blackout_recovery_समय = bw_max2(data->blackout_recovery_समय, bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[data->y_clk_level][data->sclk_level]));
				अगर (bw_ltn(data->adjusted_data_buffer_size[k], bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), (bw_add(vbios->blackout_duration, bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[data->y_clk_level][data->sclk_level])))))) अणु
					data->blackout_recovery_समय = bw_max2(data->blackout_recovery_समय, bw_भाग((bw_add(bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), vbios->blackout_duration), bw_sub(bw_भाग(bw_mul(bw_mul(bw_mul((bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), data->total_dmअगरmc_urgent_latency), data->dmअगर_burst_समय[data->y_clk_level][data->sclk_level])), data->dispclk), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[k])), data->lines_पूर्णांकerleaved_in_mem_access[k]), data->latency_hiding_lines[k]), data->adjusted_data_buffer_size[k]))), (bw_sub(bw_भाग(bw_mul(bw_mul(data->dispclk, bw_पूर्णांक_to_fixed(data->bytes_per_pixel[k])), data->lines_पूर्णांकerleaved_in_mem_access[k]), data->latency_hiding_lines[k]), bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k])))));
				पूर्ण
			पूर्ण
			अन्यथा अणु
				data->blackout_recovery_समय = bw_max2(data->blackout_recovery_समय, bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), vbios->mcअगरwrmc_urgent_latency), data->mcअगरwr_burst_समय[data->y_clk_level][data->sclk_level]));
				अगर (bw_ltn(data->adjusted_data_buffer_size[k], bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), (bw_add(vbios->blackout_duration, bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), vbios->mcअगरwrmc_urgent_latency), data->mcअगरwr_burst_समय[data->y_clk_level][data->sclk_level])))))) अणु
					data->blackout_recovery_समय = bw_max2(data->blackout_recovery_समय, bw_भाग((bw_add(bw_mul(bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k]), vbios->blackout_duration), bw_sub(bw_भाग(bw_mul(bw_mul(bw_mul((bw_add(bw_add(bw_mul(bw_पूर्णांक_to_fixed(2), vbios->mcअगरwrmc_urgent_latency), data->dmअगर_burst_समय[data->y_clk_level][data->sclk_level]), data->mcअगरwr_burst_समय[data->y_clk_level][data->sclk_level])), data->dispclk), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[k])), data->lines_पूर्णांकerleaved_in_mem_access[k]), data->latency_hiding_lines[k]), data->adjusted_data_buffer_size[k]))), (bw_sub(bw_भाग(bw_mul(bw_mul(data->dispclk, bw_पूर्णांक_to_fixed(data->bytes_per_pixel[k])), data->lines_पूर्णांकerleaved_in_mem_access[k]), data->latency_hiding_lines[k]), bw_भाग(bw_mul(data->display_bandwidth[k], data->useful_bytes_per_request[k]), data->bytes_per_request[k])))));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*sclk deep sleep*/
	/*during self-refresh, sclk can be reduced to dispclk भागided by the minimum pixels in the data fअगरo entry, with 15% margin, but shoudl not be set to less than the request bandwidth.*/
	/*the data fअगरo entry is 16 pixels क्रम the ग_लिखोback, 64 bytes/bytes_per_pixel क्रम the graphics, 16 pixels क्रम the parallel rotation underlay,*/
	/*and 16 bytes/bytes_per_pixel क्रम the orthogonal rotation underlay.*/
	/*in parallel mode (underlay pipe), the data पढ़ो from the dmअगरv buffer is variable and based on the pixel depth (8bbp - 16 bytes, 16 bpp - 32 bytes, 32 bpp - 64 bytes)*/
	/*in orthogonal mode (underlay pipe), the data पढ़ो from the dmअगरv buffer is fixed at 16 bytes.*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (surface_type[i] == bw_def_display_ग_लिखो_back420_luma || surface_type[i] == bw_def_display_ग_लिखो_back420_chroma) अणु
				data->pixels_per_data_fअगरo_entry[i] = bw_पूर्णांक_to_fixed(16);
			पूर्ण
			अन्यथा अगर (surface_type[i] == bw_def_graphics) अणु
				data->pixels_per_data_fअगरo_entry[i] = bw_भाग(bw_पूर्णांक_to_fixed(64), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]));
			पूर्ण
			अन्यथा अगर (data->orthogonal_rotation[i] == 0) अणु
				data->pixels_per_data_fअगरo_entry[i] = bw_पूर्णांक_to_fixed(16);
			पूर्ण
			अन्यथा अणु
				data->pixels_per_data_fअगरo_entry[i] = bw_भाग(bw_पूर्णांक_to_fixed(16), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i]));
			पूर्ण
		पूर्ण
	पूर्ण
	data->min_pixels_per_data_fअगरo_entry = bw_पूर्णांक_to_fixed(9999);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_mtn(data->min_pixels_per_data_fअगरo_entry, data->pixels_per_data_fअगरo_entry[i])) अणु
				data->min_pixels_per_data_fअगरo_entry = data->pixels_per_data_fअगरo_entry[i];
			पूर्ण
		पूर्ण
	पूर्ण
	data->sclk_deep_sleep = bw_max2(bw_भाग(bw_mul(data->dispclk, bw_frc_to_fixed(115, 100)), data->min_pixels_per_data_fअगरo_entry), data->total_पढ़ो_request_bandwidth);
	/*urgent, stutter and nb-p_state watermark*/
	/*the urgent watermark is the maximum of the urgent trip समय plus the pixel transfer समय, the urgent trip बार to get data क्रम the first pixel, and the urgent trip बार to get data क्रम the last pixel.*/
	/*the stutter निकास watermark is the self refresh निकास समय plus the maximum of the data burst समय plus the pixel transfer समय, the data burst बार to get data क्रम the first pixel, and the data burst बार to get data क्रम the last pixel.  it करोes not apply to the ग_लिखोback.*/
	/*the nb p-state change watermark is the dram speed/p-state change समय plus the maximum of the data burst समय plus the pixel transfer समय, the data burst बार to get data क्रम the first pixel, and the data burst बार to get data क्रम the last pixel.*/
	/*the pixel transfer समय is the maximum of the समय to transfer the source pixels required क्रम the first output pixel, and the समय to transfer the pixels क्रम the last output pixel minus the active line समय.*/
	/*blackout_duration is added to the urgent watermark*/
	data->chunk_request_समय = bw_पूर्णांक_to_fixed(0);
	data->cursor_request_समय = bw_पूर्णांक_to_fixed(0);
	/*compute total समय to request one chunk from each active display pipe*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->chunk_request_समय = bw_add(data->chunk_request_समय, (bw_भाग((bw_भाग(bw_पूर्णांक_to_fixed(pixels_per_chunk * data->bytes_per_pixel[i]), data->useful_bytes_per_request[i])), bw_min2(sclk[data->sclk_level], bw_भाग(data->dispclk, bw_पूर्णांक_to_fixed(2))))));
		पूर्ण
	पूर्ण
	/*compute total समय to request cursor data*/
	data->cursor_request_समय = (bw_भाग(data->cursor_total_data, (bw_mul(bw_पूर्णांक_to_fixed(32), sclk[data->sclk_level]))));
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->line_source_pixels_transfer_समय = bw_max2(bw_भाग(bw_भाग(data->src_pixels_क्रम_first_output_pixel[i], dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_भाग(data->dispclk, dceip->display_pipe_throughput_factor))), bw_sub(bw_भाग(bw_भाग(data->src_pixels_क्रम_last_output_pixel[i], dceip->lb_ग_लिखो_pixels_per_dispclk), (bw_भाग(data->dispclk, dceip->display_pipe_throughput_factor))), data->active_समय[i]));
			अगर (surface_type[i] != bw_def_display_ग_लिखो_back420_luma && surface_type[i] != bw_def_display_ग_लिखो_back420_chroma) अणु
				data->urgent_watermark[i] = bw_add(bw_add(bw_add(bw_add(bw_add(data->total_dmअगरmc_urgent_latency, data->dmअगर_burst_समय[data->y_clk_level][data->sclk_level]), bw_max2(data->line_source_pixels_transfer_समय, data->line_source_transfer_समय[i][data->y_clk_level][data->sclk_level])), vbios->blackout_duration), data->chunk_request_समय), data->cursor_request_समय);
				data->stutter_निकास_watermark[i] = bw_add(bw_sub(vbios->stutter_self_refresh_निकास_latency, data->total_dmअगरmc_urgent_latency), data->urgent_watermark[i]);
				data->stutter_entry_watermark[i] = bw_add(bw_sub(bw_add(vbios->stutter_self_refresh_निकास_latency, vbios->stutter_self_refresh_entry_latency), data->total_dmअगरmc_urgent_latency), data->urgent_watermark[i]);
				/*unconditionally हटाओ black out समय from the nb p_state watermark*/
				अगर (data->display_pstate_change_enable[i] == 1) अणु
					data->nbp_state_change_watermark[i] = bw_add(bw_add(vbios->nbp_state_change_latency, data->dmअगर_burst_समय[data->y_clk_level][data->sclk_level]), bw_max2(data->line_source_pixels_transfer_समय, data->dram_speed_change_line_source_transfer_समय[i][data->y_clk_level][data->sclk_level]));
				पूर्ण
				अन्यथा अणु
					/*maximize the watermark to क्रमce the चयन in the vb_lank region of the frame*/
					data->nbp_state_change_watermark[i] = bw_पूर्णांक_to_fixed(131000);
				पूर्ण
			पूर्ण
			अन्यथा अणु
				data->urgent_watermark[i] = bw_add(bw_add(bw_add(bw_add(bw_add(vbios->mcअगरwrmc_urgent_latency, data->mcअगरwr_burst_समय[data->y_clk_level][data->sclk_level]), bw_max2(data->line_source_pixels_transfer_समय, data->line_source_transfer_समय[i][data->y_clk_level][data->sclk_level])), vbios->blackout_duration), data->chunk_request_समय), data->cursor_request_समय);
				data->stutter_निकास_watermark[i] = bw_पूर्णांक_to_fixed(0);
				data->stutter_entry_watermark[i] = bw_पूर्णांक_to_fixed(0);
				अगर (data->display_pstate_change_enable[i] == 1) अणु
					data->nbp_state_change_watermark[i] = bw_add(bw_add(vbios->nbp_state_change_latency, data->mcअगरwr_burst_समय[data->y_clk_level][data->sclk_level]), bw_max2(data->line_source_pixels_transfer_समय, data->dram_speed_change_line_source_transfer_समय[i][data->y_clk_level][data->sclk_level]));
				पूर्ण
				अन्यथा अणु
					/*maximize the watermark to क्रमce the चयन in the vb_lank region of the frame*/
					data->nbp_state_change_watermark[i] = bw_पूर्णांक_to_fixed(131000);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*stutter mode enable*/
	/*in the multi-display हाल the stutter निकास or entry watermark cannot exceed the minimum latency hiding capabilities of the*/
	/*display pipe.*/
	data->stutter_mode_enable = data->cpuc_state_change_enable;
	अगर (data->number_of_displays > 1) अणु
		क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
			अगर (data->enable[i]) अणु
				अगर ((bw_mtn(data->stutter_निकास_watermark[i], data->minimum_latency_hiding[i]) || bw_mtn(data->stutter_entry_watermark[i], data->minimum_latency_hiding[i]))) अणु
					data->stutter_mode_enable = bw_def_no;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*perक्रमmance metrics*/
	/* display पढ़ो access efficiency (%)*/
	/* display ग_लिखो back access efficiency (%)*/
	/* stutter efficiency (%)*/
	/* extra underlay pitch recommended क्रम efficiency (pixels)*/
	/* immediate flip समय (us)*/
	/* latency क्रम other clients due to urgent display पढ़ो (us)*/
	/* latency क्रम other clients due to urgent display ग_लिखो (us)*/
	/* average bandwidth consumed by display (no compression) (gb/s)*/
	/* required dram  bandwidth (gb/s)*/
	/* required sclk (m_hz)*/
	/* required rd urgent latency (us)*/
	/* nb p-state change margin (us)*/
	/*dmअगर and mcअगरwr dram access efficiency*/
	/*is the ratio between the ideal dram access समय (which is the data buffer size in memory भागided by the dram bandwidth), and the actual समय which is the total page बंद-खोलो समय.  but it cannot exceed the dram efficiency provided by the memory subप्रणाली*/
	data->dmअगरdram_access_efficiency = bw_min2(bw_भाग(bw_भाग(data->total_display_पढ़ोs_required_dram_access_data, data->dram_bandwidth), data->dmअगर_total_page_बंद_खोलो_समय), bw_पूर्णांक_to_fixed(1));
	अगर (bw_mtn(data->total_display_ग_लिखोs_required_dram_access_data, bw_पूर्णांक_to_fixed(0))) अणु
		data->mcअगरwrdram_access_efficiency = bw_min2(bw_भाग(bw_भाग(data->total_display_ग_लिखोs_required_dram_access_data, data->dram_bandwidth), data->mcअगरwr_total_page_बंद_खोलो_समय), bw_पूर्णांक_to_fixed(1));
	पूर्ण
	अन्यथा अणु
		data->mcअगरwrdram_access_efficiency = bw_पूर्णांक_to_fixed(0);
	पूर्ण
	/*stutter efficiency*/
	/*the stutter efficiency is the frame-average समय in self-refresh भागided by the frame-average stutter cycle duration.  only applies अगर the display ग_लिखो-back is not enabled.*/
	/*the frame-average stutter cycle used is the minimum क्रम all pipes of the frame-average data buffer size in समय, बार the compression rate*/
	/*the frame-average समय in self-refresh is the stutter cycle minus the self refresh निकास latency and the burst समय*/
	/*the stutter cycle is the dmअगर buffer size reduced by the excess of the stutter निकास watermark over the lb size in समय.*/
	/*the burst समय is the data needed during the stutter cycle भागided by the available bandwidth*/
	/*compute the समय पढ़ो all the data from the dmअगर buffer to the lb (dram refresh period)*/
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->stutter_refresh_duration[i] = bw_sub(bw_mul(bw_भाग(bw_भाग(bw_mul(bw_भाग(bw_भाग(data->adjusted_data_buffer_size[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->source_width_rounded_up_to_chunks[i]), data->h_total[i]), data->vsr[i]), data->pixel_rate[i]), data->compression_rate[i]), bw_max2(bw_पूर्णांक_to_fixed(0), bw_sub(data->stutter_निकास_watermark[i], bw_भाग(bw_mul((bw_sub(data->lb_partitions[i], bw_पूर्णांक_to_fixed(1))), data->h_total[i]), data->pixel_rate[i]))));
			data->stutter_dmअगर_buffer_size[i] = bw_भाग(bw_mul(bw_mul(bw_भाग(bw_mul(bw_mul(data->stutter_refresh_duration[i], bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])), data->source_width_rounded_up_to_chunks[i]), data->h_total[i]), data->vsr[i]), data->pixel_rate[i]), data->compression_rate[i]);
		पूर्ण
	पूर्ण
	data->min_stutter_refresh_duration = bw_पूर्णांक_to_fixed(9999);
	data->total_stutter_dmअगर_buffer_size = 0;
	data->total_bytes_requested = 0;
	data->min_stutter_dmअगर_buffer_size = 9999;
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			अगर (bw_mtn(data->min_stutter_refresh_duration, data->stutter_refresh_duration[i])) अणु
				data->min_stutter_refresh_duration = data->stutter_refresh_duration[i];
				data->total_bytes_requested = bw_fixed_to_पूर्णांक(bw_add(bw_पूर्णांक_to_fixed(data->total_bytes_requested), (bw_mul(bw_mul(data->source_height_rounded_up_to_chunks[i], data->source_width_rounded_up_to_chunks[i]), bw_पूर्णांक_to_fixed(data->bytes_per_pixel[i])))));
				data->min_stutter_dmअगर_buffer_size = bw_fixed_to_पूर्णांक(data->stutter_dmअगर_buffer_size[i]);
			पूर्ण
			data->total_stutter_dmअगर_buffer_size = bw_fixed_to_पूर्णांक(bw_add(data->stutter_dmअगर_buffer_size[i], bw_पूर्णांक_to_fixed(data->total_stutter_dmअगर_buffer_size)));
		पूर्ण
	पूर्ण
	data->stutter_burst_समय = bw_भाग(bw_पूर्णांक_to_fixed(data->total_stutter_dmअगर_buffer_size), bw_mul(sclk[data->sclk_level], vbios->data_वापस_bus_width));
	data->num_stutter_bursts = data->total_bytes_requested / data->min_stutter_dmअगर_buffer_size;
	data->total_stutter_cycle_duration = bw_add(bw_add(data->min_stutter_refresh_duration, vbios->stutter_self_refresh_निकास_latency), data->stutter_burst_समय);
	data->समय_in_self_refresh = data->min_stutter_refresh_duration;
	अगर (data->d1_display_ग_लिखो_back_dwb_enable == 1) अणु
		data->stutter_efficiency = bw_पूर्णांक_to_fixed(0);
	पूर्ण
	अन्यथा अगर (bw_ltn(data->समय_in_self_refresh, bw_पूर्णांक_to_fixed(0))) अणु
		data->stutter_efficiency = bw_पूर्णांक_to_fixed(0);
	पूर्ण
	अन्यथा अणु
		/*compute stutter efficiency assuming 60 hz refresh rate*/
		data->stutter_efficiency = bw_max2(bw_पूर्णांक_to_fixed(0), bw_mul((bw_sub(bw_पूर्णांक_to_fixed(1), (bw_भाग(bw_mul((bw_add(vbios->stutter_self_refresh_निकास_latency, data->stutter_burst_समय)), bw_पूर्णांक_to_fixed(data->num_stutter_bursts)), bw_frc_to_fixed(166666667, 10000))))), bw_पूर्णांक_to_fixed(100)));
	पूर्ण
	/*immediate flip समय*/
	/*अगर scatter gather is enabled, the immediate flip takes a number of urgent memory trips equivalent to the pte requests in a row भागided by the pte request limit.*/
	/*otherwise, it may take just one urgenr memory trip*/
	data->worst_number_of_trips_to_memory = bw_पूर्णांक_to_fixed(1);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i] && data->scatter_gather_enable_क्रम_pipe[i] == 1) अणु
			data->number_of_trips_to_memory_क्रम_getting_apte_row[i] = bw_उच्चमान2(bw_भाग(data->scatter_gather_pte_requests_in_row[i], data->scatter_gather_pte_request_limit[i]), bw_पूर्णांक_to_fixed(1));
			अगर (bw_ltn(data->worst_number_of_trips_to_memory, data->number_of_trips_to_memory_क्रम_getting_apte_row[i])) अणु
				data->worst_number_of_trips_to_memory = data->number_of_trips_to_memory_क्रम_getting_apte_row[i];
			पूर्ण
		पूर्ण
	पूर्ण
	data->immediate_flip_समय = bw_mul(data->worst_number_of_trips_to_memory, data->total_dmअगरmc_urgent_latency);
	/*worst latency क्रम other clients*/
	/*it is the urgent latency plus the urgent burst समय*/
	data->latency_क्रम_non_dmअगर_clients = bw_add(data->total_dmअगरmc_urgent_latency, data->dmअगर_burst_समय[data->y_clk_level][data->sclk_level]);
	अगर (data->d1_display_ग_लिखो_back_dwb_enable == 1) अणु
		data->latency_क्रम_non_mcअगरwr_clients = bw_add(vbios->mcअगरwrmc_urgent_latency, dceip->mcअगरwr_all_surfaces_burst_समय);
	पूर्ण
	अन्यथा अणु
		data->latency_क्रम_non_mcअगरwr_clients = bw_पूर्णांक_to_fixed(0);
	पूर्ण
	/*dmअगर mc urgent latency supported in high sclk and yclk*/
	data->dmअगरmc_urgent_latency_supported_in_high_sclk_and_yclk = bw_भाग((bw_sub(data->min_पढ़ो_buffer_size_in_समय, data->dmअगर_burst_समय[high][s_high])), data->total_dmअगरmc_urgent_trips);
	/*dram speed/p-state change margin*/
	/*in the multi-display हाल the nb p-state change watermark cannot exceed the average lb size plus the dmअगर size or the cursor dcp buffer size*/
	data->v_blank_nbp_state_dram_speed_change_latency_supported = bw_पूर्णांक_to_fixed(99999);
	data->nbp_state_dram_speed_change_latency_supported = bw_पूर्णांक_to_fixed(99999);
	क्रम (i = 0; i <= maximum_number_of_surfaces - 1; i++) अणु
		अगर (data->enable[i]) अणु
			data->nbp_state_dram_speed_change_latency_supported = bw_min2(data->nbp_state_dram_speed_change_latency_supported, bw_add(bw_sub(data->maximum_latency_hiding_with_cursor[i], data->nbp_state_change_watermark[i]), vbios->nbp_state_change_latency));
			data->v_blank_nbp_state_dram_speed_change_latency_supported = bw_min2(data->v_blank_nbp_state_dram_speed_change_latency_supported, bw_add(bw_sub(bw_भाग(bw_mul((bw_sub(data->v_total[i], bw_sub(bw_भाग(data->src_height[i], data->v_scale_ratio[i]), bw_पूर्णांक_to_fixed(4)))), data->h_total[i]), data->pixel_rate[i]), data->nbp_state_change_watermark[i]), vbios->nbp_state_change_latency));
		पूर्ण
	पूर्ण
	/*sclk required vs urgent latency*/
	क्रम (i = 1; i <= 5; i++) अणु
		data->display_पढ़ोs_समय_क्रम_data_transfer_and_urgent_latency = bw_sub(data->min_पढ़ो_buffer_size_in_समय, bw_mul(data->total_dmअगरmc_urgent_trips, bw_पूर्णांक_to_fixed(i)));
		अगर (pipe_check == bw_def_ok && (bw_mtn(data->display_पढ़ोs_समय_क्रम_data_transfer_and_urgent_latency, data->dmअगर_total_page_बंद_खोलो_समय))) अणु
			data->dmअगर_required_sclk_क्रम_urgent_latency[i] = bw_भाग(bw_भाग(data->total_display_पढ़ोs_required_data, data->display_पढ़ोs_समय_क्रम_data_transfer_and_urgent_latency), (bw_mul(vbios->data_वापस_bus_width, bw_frc_to_fixed(dceip->percent_of_ideal_port_bw_received_after_urgent_latency, 100))));
		पूर्ण
		अन्यथा अणु
			data->dmअगर_required_sclk_क्रम_urgent_latency[i] = bw_पूर्णांक_to_fixed(bw_def_na);
		पूर्ण
	पूर्ण
	/*output link bit per pixel supported*/
	क्रम (k = 0; k <= maximum_number_of_surfaces - 1; k++) अणु
		data->output_bpphdmi[k] = bw_def_na;
		data->output_bppdp4_lane_hbr[k] = bw_def_na;
		data->output_bppdp4_lane_hbr2[k] = bw_def_na;
		data->output_bppdp4_lane_hbr3[k] = bw_def_na;
		अगर (data->enable[k]) अणु
			data->output_bpphdmi[k] = bw_fixed_to_पूर्णांक(bw_mul(bw_भाग(bw_min2(bw_पूर्णांक_to_fixed(600), data->max_phyclk), data->pixel_rate[k]), bw_पूर्णांक_to_fixed(24)));
			अगर (bw_meq(data->max_phyclk, bw_पूर्णांक_to_fixed(270))) अणु
				data->output_bppdp4_lane_hbr[k] = bw_fixed_to_पूर्णांक(bw_mul(bw_भाग(bw_mul(bw_पूर्णांक_to_fixed(270), bw_पूर्णांक_to_fixed(4)), data->pixel_rate[k]), bw_पूर्णांक_to_fixed(8)));
			पूर्ण
			अगर (bw_meq(data->max_phyclk, bw_पूर्णांक_to_fixed(540))) अणु
				data->output_bppdp4_lane_hbr2[k] = bw_fixed_to_पूर्णांक(bw_mul(bw_भाग(bw_mul(bw_पूर्णांक_to_fixed(540), bw_पूर्णांक_to_fixed(4)), data->pixel_rate[k]), bw_पूर्णांक_to_fixed(8)));
			पूर्ण
			अगर (bw_meq(data->max_phyclk, bw_पूर्णांक_to_fixed(810))) अणु
				data->output_bppdp4_lane_hbr3[k] = bw_fixed_to_पूर्णांक(bw_mul(bw_भाग(bw_mul(bw_पूर्णांक_to_fixed(810), bw_पूर्णांक_to_fixed(4)), data->pixel_rate[k]), bw_पूर्णांक_to_fixed(8)));
			पूर्ण
		पूर्ण
	पूर्ण

	kमुक्त(surface_type);
मुक्त_tiling_mode:
	kमुक्त(tiling_mode);
मुक्त_yclk:
	kमुक्त(yclk);
मुक्त_sclk:
	kमुक्त(sclk);
पूर्ण

/*******************************************************************************
 * Public functions
 ******************************************************************************/
व्योम bw_calcs_init(काष्ठा bw_calcs_dceip *bw_dceip,
	काष्ठा bw_calcs_vbios *bw_vbios,
	काष्ठा hw_asic_id asic_id)
अणु
	काष्ठा bw_calcs_dceip *dceip;
	काष्ठा bw_calcs_vbios *vbios;

	क्रमागत bw_calcs_version version = bw_calcs_version_from_asic_id(asic_id);

	dceip = kzalloc(माप(*dceip), GFP_KERNEL);
	अगर (!dceip)
		वापस;

	vbios = kzalloc(माप(*vbios), GFP_KERNEL);
	अगर (!vbios) अणु
		kमुक्त(dceip);
		वापस;
	पूर्ण

	dceip->version = version;

	चयन (version) अणु
	हाल BW_CALCS_VERSION_CARRIZO:
		vbios->memory_type = bw_def_gddr5;
		vbios->dram_channel_width_in_bits = 64;
		vbios->number_of_dram_channels = asic_id.vram_width / vbios->dram_channel_width_in_bits;
		vbios->number_of_dram_banks = 8;
		vbios->high_yclk = bw_पूर्णांक_to_fixed(1600);
		vbios->mid_yclk = bw_पूर्णांक_to_fixed(1600);
		vbios->low_yclk = bw_frc_to_fixed(66666, 100);
		vbios->low_sclk = bw_पूर्णांक_to_fixed(200);
		vbios->mid1_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid2_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid3_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid4_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid5_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid6_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->high_sclk = bw_frc_to_fixed(62609, 100);
		vbios->low_voltage_max_dispclk = bw_पूर्णांक_to_fixed(352);
		vbios->mid_voltage_max_dispclk = bw_पूर्णांक_to_fixed(467);
		vbios->high_voltage_max_dispclk = bw_पूर्णांक_to_fixed(643);
		vbios->low_voltage_max_phyclk = bw_पूर्णांक_to_fixed(540);
		vbios->mid_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->high_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->data_वापस_bus_width = bw_पूर्णांक_to_fixed(32);
		vbios->trc = bw_पूर्णांक_to_fixed(50);
		vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(4);
		vbios->stutter_self_refresh_निकास_latency = bw_frc_to_fixed(153, 10);
		vbios->stutter_self_refresh_entry_latency = bw_पूर्णांक_to_fixed(0);
		vbios->nbp_state_change_latency = bw_frc_to_fixed(19649, 1000);
		vbios->mcअगरwrmc_urgent_latency = bw_पूर्णांक_to_fixed(10);
		vbios->scatter_gather_enable = true;
		vbios->करोwn_spपढ़ो_percentage = bw_frc_to_fixed(5, 10);
		vbios->cursor_width = 32;
		vbios->average_compression_rate = 4;
		vbios->number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel = 256;
		vbios->blackout_duration = bw_पूर्णांक_to_fixed(0); /* us */
		vbios->maximum_blackout_recovery_समय = bw_पूर्णांक_to_fixed(0);

		dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip->large_cursor = false;
		dceip->dmअगर_request_buffer_size = bw_पूर्णांक_to_fixed(768);
		dceip->dmअगर_pipe_en_fbc_chunk_tracker = false;
		dceip->cursor_max_outstanding_group_num = 1;
		dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb = 2;
		dceip->chunk_width = 256;
		dceip->number_of_graphics_pipes = 3;
		dceip->number_of_underlay_pipes = 1;
		dceip->low_घातer_tiling_mode = 0;
		dceip->display_ग_लिखो_back_supported = false;
		dceip->argb_compression_support = false;
		dceip->underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip->underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->underlay_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip->graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->graphics_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->alpha_vscaler_efficiency = bw_पूर्णांक_to_fixed(3);
		dceip->max_dmअगर_buffer_allocated = 2;
		dceip->graphics_dmअगर_size = 12288;
		dceip->underlay_luma_dmअगर_size = 19456;
		dceip->underlay_chroma_dmअगर_size = 23552;
		dceip->pre_करोwnscaler_enabled = true;
		dceip->underlay_करोwnscale_prefetch_enabled = true;
		dceip->lb_ग_लिखो_pixels_per_dispclk = bw_पूर्णांक_to_fixed(1);
		dceip->lb_size_per_component444 = bw_पूर्णांक_to_fixed(82176);
		dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching = false;
		dceip->stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor =
			bw_पूर्णांक_to_fixed(0);
		dceip->underlay420_luma_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->underlay420_chroma_lb_size_per_component =
			bw_पूर्णांक_to_fixed(164352);
		dceip->underlay422_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->cursor_chunk_width = bw_पूर्णांक_to_fixed(64);
		dceip->cursor_dcp_buffer_lines = bw_पूर्णांक_to_fixed(4);
		dceip->underlay_maximum_width_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1920);
		dceip->underlay_maximum_height_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1080);
		dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_पूर्णांक_to_fixed(25);
		dceip->minimum_outstanding_pte_request_limit = bw_पूर्णांक_to_fixed(
			2);
		dceip->maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_पूर्णांक_to_fixed(128);
		dceip->limit_excessive_outstanding_dmअगर_requests = true;
		dceip->linear_mode_line_request_alternation_slice =
			bw_पूर्णांक_to_fixed(64);
		dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip->display_ग_लिखो_back420_luma_mcअगरwr_buffer_size = 12288;
		dceip->display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size = 8192;
		dceip->request_efficiency = bw_frc_to_fixed(8, 10);
		dceip->dispclk_per_request = bw_पूर्णांक_to_fixed(2);
		dceip->dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip->display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip->scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip->mcअगरwr_all_surfaces_burst_समय = bw_पूर्णांक_to_fixed(0); /* toकरो: this is a bug*/
		अवरोध;
	हाल BW_CALCS_VERSION_POLARIS10:
		/* TODO: Treat VEGAM the same as P10 क्रम now
		 * Need to tune the para क्रम VEGAM अगर needed */
	हाल BW_CALCS_VERSION_VEGAM:
		vbios->memory_type = bw_def_gddr5;
		vbios->dram_channel_width_in_bits = 32;
		vbios->number_of_dram_channels = asic_id.vram_width / vbios->dram_channel_width_in_bits;
		vbios->number_of_dram_banks = 8;
		vbios->high_yclk = bw_पूर्णांक_to_fixed(6000);
		vbios->mid_yclk = bw_पूर्णांक_to_fixed(3200);
		vbios->low_yclk = bw_पूर्णांक_to_fixed(1000);
		vbios->low_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid1_sclk = bw_पूर्णांक_to_fixed(400);
		vbios->mid2_sclk = bw_पूर्णांक_to_fixed(500);
		vbios->mid3_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid4_sclk = bw_पूर्णांक_to_fixed(700);
		vbios->mid5_sclk = bw_पूर्णांक_to_fixed(800);
		vbios->mid6_sclk = bw_पूर्णांक_to_fixed(974);
		vbios->high_sclk = bw_पूर्णांक_to_fixed(1154);
		vbios->low_voltage_max_dispclk = bw_पूर्णांक_to_fixed(459);
		vbios->mid_voltage_max_dispclk = bw_पूर्णांक_to_fixed(654);
		vbios->high_voltage_max_dispclk = bw_पूर्णांक_to_fixed(1108);
		vbios->low_voltage_max_phyclk = bw_पूर्णांक_to_fixed(540);
		vbios->mid_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->high_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->data_वापस_bus_width = bw_पूर्णांक_to_fixed(32);
		vbios->trc = bw_पूर्णांक_to_fixed(48);
		vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(3);
		vbios->stutter_self_refresh_निकास_latency = bw_पूर्णांक_to_fixed(5);
		vbios->stutter_self_refresh_entry_latency = bw_पूर्णांक_to_fixed(0);
		vbios->nbp_state_change_latency = bw_पूर्णांक_to_fixed(45);
		vbios->mcअगरwrmc_urgent_latency = bw_पूर्णांक_to_fixed(10);
		vbios->scatter_gather_enable = true;
		vbios->करोwn_spपढ़ो_percentage = bw_frc_to_fixed(5, 10);
		vbios->cursor_width = 32;
		vbios->average_compression_rate = 4;
		vbios->number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel = 256;
		vbios->blackout_duration = bw_पूर्णांक_to_fixed(0); /* us */
		vbios->maximum_blackout_recovery_समय = bw_पूर्णांक_to_fixed(0);

		dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip->large_cursor = false;
		dceip->dmअगर_request_buffer_size = bw_पूर्णांक_to_fixed(768);
		dceip->dmअगर_pipe_en_fbc_chunk_tracker = false;
		dceip->cursor_max_outstanding_group_num = 1;
		dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb = 2;
		dceip->chunk_width = 256;
		dceip->number_of_graphics_pipes = 6;
		dceip->number_of_underlay_pipes = 0;
		dceip->low_घातer_tiling_mode = 0;
		dceip->display_ग_लिखो_back_supported = false;
		dceip->argb_compression_support = true;
		dceip->underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip->underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->underlay_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip->graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->graphics_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->alpha_vscaler_efficiency = bw_पूर्णांक_to_fixed(3);
		dceip->max_dmअगर_buffer_allocated = 4;
		dceip->graphics_dmअगर_size = 12288;
		dceip->underlay_luma_dmअगर_size = 19456;
		dceip->underlay_chroma_dmअगर_size = 23552;
		dceip->pre_करोwnscaler_enabled = true;
		dceip->underlay_करोwnscale_prefetch_enabled = true;
		dceip->lb_ग_लिखो_pixels_per_dispclk = bw_पूर्णांक_to_fixed(1);
		dceip->lb_size_per_component444 = bw_पूर्णांक_to_fixed(245952);
		dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching = true;
		dceip->stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor =
			bw_पूर्णांक_to_fixed(1);
		dceip->underlay420_luma_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->underlay420_chroma_lb_size_per_component =
			bw_पूर्णांक_to_fixed(164352);
		dceip->underlay422_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->cursor_chunk_width = bw_पूर्णांक_to_fixed(64);
		dceip->cursor_dcp_buffer_lines = bw_पूर्णांक_to_fixed(4);
		dceip->underlay_maximum_width_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1920);
		dceip->underlay_maximum_height_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1080);
		dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_पूर्णांक_to_fixed(25);
		dceip->minimum_outstanding_pte_request_limit = bw_पूर्णांक_to_fixed(
			2);
		dceip->maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_पूर्णांक_to_fixed(128);
		dceip->limit_excessive_outstanding_dmअगर_requests = true;
		dceip->linear_mode_line_request_alternation_slice =
			bw_पूर्णांक_to_fixed(64);
		dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip->display_ग_लिखो_back420_luma_mcअगरwr_buffer_size = 12288;
		dceip->display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size = 8192;
		dceip->request_efficiency = bw_frc_to_fixed(8, 10);
		dceip->dispclk_per_request = bw_पूर्णांक_to_fixed(2);
		dceip->dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip->display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip->scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip->mcअगरwr_all_surfaces_burst_समय = bw_पूर्णांक_to_fixed(0);
		अवरोध;
	हाल BW_CALCS_VERSION_POLARIS11:
		vbios->memory_type = bw_def_gddr5;
		vbios->dram_channel_width_in_bits = 32;
		vbios->number_of_dram_channels = asic_id.vram_width / vbios->dram_channel_width_in_bits;
		vbios->number_of_dram_banks = 8;
		vbios->high_yclk = bw_पूर्णांक_to_fixed(6000);
		vbios->mid_yclk = bw_पूर्णांक_to_fixed(3200);
		vbios->low_yclk = bw_पूर्णांक_to_fixed(1000);
		vbios->low_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid1_sclk = bw_पूर्णांक_to_fixed(400);
		vbios->mid2_sclk = bw_पूर्णांक_to_fixed(500);
		vbios->mid3_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid4_sclk = bw_पूर्णांक_to_fixed(700);
		vbios->mid5_sclk = bw_पूर्णांक_to_fixed(800);
		vbios->mid6_sclk = bw_पूर्णांक_to_fixed(974);
		vbios->high_sclk = bw_पूर्णांक_to_fixed(1154);
		vbios->low_voltage_max_dispclk = bw_पूर्णांक_to_fixed(459);
		vbios->mid_voltage_max_dispclk = bw_पूर्णांक_to_fixed(654);
		vbios->high_voltage_max_dispclk = bw_पूर्णांक_to_fixed(1108);
		vbios->low_voltage_max_phyclk = bw_पूर्णांक_to_fixed(540);
		vbios->mid_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->high_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->data_वापस_bus_width = bw_पूर्णांक_to_fixed(32);
		vbios->trc = bw_पूर्णांक_to_fixed(48);
		अगर (vbios->number_of_dram_channels == 2) // 64-bit
			vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(4);
		अन्यथा
			vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(3);
		vbios->stutter_self_refresh_निकास_latency = bw_पूर्णांक_to_fixed(5);
		vbios->stutter_self_refresh_entry_latency = bw_पूर्णांक_to_fixed(0);
		vbios->nbp_state_change_latency = bw_पूर्णांक_to_fixed(45);
		vbios->mcअगरwrmc_urgent_latency = bw_पूर्णांक_to_fixed(10);
		vbios->scatter_gather_enable = true;
		vbios->करोwn_spपढ़ो_percentage = bw_frc_to_fixed(5, 10);
		vbios->cursor_width = 32;
		vbios->average_compression_rate = 4;
		vbios->number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel = 256;
		vbios->blackout_duration = bw_पूर्णांक_to_fixed(0); /* us */
		vbios->maximum_blackout_recovery_समय = bw_पूर्णांक_to_fixed(0);

		dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip->large_cursor = false;
		dceip->dmअगर_request_buffer_size = bw_पूर्णांक_to_fixed(768);
		dceip->dmअगर_pipe_en_fbc_chunk_tracker = false;
		dceip->cursor_max_outstanding_group_num = 1;
		dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb = 2;
		dceip->chunk_width = 256;
		dceip->number_of_graphics_pipes = 5;
		dceip->number_of_underlay_pipes = 0;
		dceip->low_घातer_tiling_mode = 0;
		dceip->display_ग_लिखो_back_supported = false;
		dceip->argb_compression_support = true;
		dceip->underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip->underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->underlay_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip->graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->graphics_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->alpha_vscaler_efficiency = bw_पूर्णांक_to_fixed(3);
		dceip->max_dmअगर_buffer_allocated = 4;
		dceip->graphics_dmअगर_size = 12288;
		dceip->underlay_luma_dmअगर_size = 19456;
		dceip->underlay_chroma_dmअगर_size = 23552;
		dceip->pre_करोwnscaler_enabled = true;
		dceip->underlay_करोwnscale_prefetch_enabled = true;
		dceip->lb_ग_लिखो_pixels_per_dispclk = bw_पूर्णांक_to_fixed(1);
		dceip->lb_size_per_component444 = bw_पूर्णांक_to_fixed(245952);
		dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching = true;
		dceip->stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor =
			bw_पूर्णांक_to_fixed(1);
		dceip->underlay420_luma_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->underlay420_chroma_lb_size_per_component =
			bw_पूर्णांक_to_fixed(164352);
		dceip->underlay422_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->cursor_chunk_width = bw_पूर्णांक_to_fixed(64);
		dceip->cursor_dcp_buffer_lines = bw_पूर्णांक_to_fixed(4);
		dceip->underlay_maximum_width_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1920);
		dceip->underlay_maximum_height_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1080);
		dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_पूर्णांक_to_fixed(25);
		dceip->minimum_outstanding_pte_request_limit = bw_पूर्णांक_to_fixed(
			2);
		dceip->maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_पूर्णांक_to_fixed(128);
		dceip->limit_excessive_outstanding_dmअगर_requests = true;
		dceip->linear_mode_line_request_alternation_slice =
			bw_पूर्णांक_to_fixed(64);
		dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip->display_ग_लिखो_back420_luma_mcअगरwr_buffer_size = 12288;
		dceip->display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size = 8192;
		dceip->request_efficiency = bw_frc_to_fixed(8, 10);
		dceip->dispclk_per_request = bw_पूर्णांक_to_fixed(2);
		dceip->dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip->display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip->scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip->mcअगरwr_all_surfaces_burst_समय = bw_पूर्णांक_to_fixed(0);
		अवरोध;
	हाल BW_CALCS_VERSION_POLARIS12:
		vbios->memory_type = bw_def_gddr5;
		vbios->dram_channel_width_in_bits = 32;
		vbios->number_of_dram_channels = asic_id.vram_width / vbios->dram_channel_width_in_bits;
		vbios->number_of_dram_banks = 8;
		vbios->high_yclk = bw_पूर्णांक_to_fixed(6000);
		vbios->mid_yclk = bw_पूर्णांक_to_fixed(3200);
		vbios->low_yclk = bw_पूर्णांक_to_fixed(1000);
		vbios->low_sclk = bw_पूर्णांक_to_fixed(678);
		vbios->mid1_sclk = bw_पूर्णांक_to_fixed(864);
		vbios->mid2_sclk = bw_पूर्णांक_to_fixed(900);
		vbios->mid3_sclk = bw_पूर्णांक_to_fixed(920);
		vbios->mid4_sclk = bw_पूर्णांक_to_fixed(940);
		vbios->mid5_sclk = bw_पूर्णांक_to_fixed(960);
		vbios->mid6_sclk = bw_पूर्णांक_to_fixed(980);
		vbios->high_sclk = bw_पूर्णांक_to_fixed(1049);
		vbios->low_voltage_max_dispclk = bw_पूर्णांक_to_fixed(459);
		vbios->mid_voltage_max_dispclk = bw_पूर्णांक_to_fixed(654);
		vbios->high_voltage_max_dispclk = bw_पूर्णांक_to_fixed(1108);
		vbios->low_voltage_max_phyclk = bw_पूर्णांक_to_fixed(540);
		vbios->mid_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->high_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->data_वापस_bus_width = bw_पूर्णांक_to_fixed(32);
		vbios->trc = bw_पूर्णांक_to_fixed(48);
		अगर (vbios->number_of_dram_channels == 2) // 64-bit
			vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(4);
		अन्यथा
			vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(3);
		vbios->stutter_self_refresh_निकास_latency = bw_पूर्णांक_to_fixed(5);
		vbios->stutter_self_refresh_entry_latency = bw_पूर्णांक_to_fixed(0);
		vbios->nbp_state_change_latency = bw_पूर्णांक_to_fixed(250);
		vbios->mcअगरwrmc_urgent_latency = bw_पूर्णांक_to_fixed(10);
		vbios->scatter_gather_enable = false;
		vbios->करोwn_spपढ़ो_percentage = bw_frc_to_fixed(5, 10);
		vbios->cursor_width = 32;
		vbios->average_compression_rate = 4;
		vbios->number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel = 256;
		vbios->blackout_duration = bw_पूर्णांक_to_fixed(0); /* us */
		vbios->maximum_blackout_recovery_समय = bw_पूर्णांक_to_fixed(0);

		dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip->large_cursor = false;
		dceip->dmअगर_request_buffer_size = bw_पूर्णांक_to_fixed(768);
		dceip->dmअगर_pipe_en_fbc_chunk_tracker = false;
		dceip->cursor_max_outstanding_group_num = 1;
		dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb = 2;
		dceip->chunk_width = 256;
		dceip->number_of_graphics_pipes = 5;
		dceip->number_of_underlay_pipes = 0;
		dceip->low_घातer_tiling_mode = 0;
		dceip->display_ग_लिखो_back_supported = true;
		dceip->argb_compression_support = true;
		dceip->underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip->underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->underlay_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip->graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->graphics_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->alpha_vscaler_efficiency = bw_पूर्णांक_to_fixed(3);
		dceip->max_dmअगर_buffer_allocated = 4;
		dceip->graphics_dmअगर_size = 12288;
		dceip->underlay_luma_dmअगर_size = 19456;
		dceip->underlay_chroma_dmअगर_size = 23552;
		dceip->pre_करोwnscaler_enabled = true;
		dceip->underlay_करोwnscale_prefetch_enabled = true;
		dceip->lb_ग_लिखो_pixels_per_dispclk = bw_पूर्णांक_to_fixed(1);
		dceip->lb_size_per_component444 = bw_पूर्णांक_to_fixed(245952);
		dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching = true;
		dceip->stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor =
			bw_पूर्णांक_to_fixed(1);
		dceip->underlay420_luma_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->underlay420_chroma_lb_size_per_component =
			bw_पूर्णांक_to_fixed(164352);
		dceip->underlay422_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->cursor_chunk_width = bw_पूर्णांक_to_fixed(64);
		dceip->cursor_dcp_buffer_lines = bw_पूर्णांक_to_fixed(4);
		dceip->underlay_maximum_width_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1920);
		dceip->underlay_maximum_height_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1080);
		dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_पूर्णांक_to_fixed(25);
		dceip->minimum_outstanding_pte_request_limit = bw_पूर्णांक_to_fixed(
			2);
		dceip->maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_पूर्णांक_to_fixed(128);
		dceip->limit_excessive_outstanding_dmअगर_requests = true;
		dceip->linear_mode_line_request_alternation_slice =
			bw_पूर्णांक_to_fixed(64);
		dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip->display_ग_लिखो_back420_luma_mcअगरwr_buffer_size = 12288;
		dceip->display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size = 8192;
		dceip->request_efficiency = bw_frc_to_fixed(8, 10);
		dceip->dispclk_per_request = bw_पूर्णांक_to_fixed(2);
		dceip->dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip->display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip->scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip->mcअगरwr_all_surfaces_burst_समय = bw_पूर्णांक_to_fixed(0);
		अवरोध;
	हाल BW_CALCS_VERSION_STONEY:
		vbios->memory_type = bw_def_gddr5;
		vbios->dram_channel_width_in_bits = 64;
		vbios->number_of_dram_channels = asic_id.vram_width / vbios->dram_channel_width_in_bits;
		vbios->number_of_dram_banks = 8;
		vbios->high_yclk = bw_पूर्णांक_to_fixed(1866);
		vbios->mid_yclk = bw_पूर्णांक_to_fixed(1866);
		vbios->low_yclk = bw_पूर्णांक_to_fixed(1333);
		vbios->low_sclk = bw_पूर्णांक_to_fixed(200);
		vbios->mid1_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid2_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid3_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid4_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid5_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid6_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->high_sclk = bw_पूर्णांक_to_fixed(800);
		vbios->low_voltage_max_dispclk = bw_पूर्णांक_to_fixed(352);
		vbios->mid_voltage_max_dispclk = bw_पूर्णांक_to_fixed(467);
		vbios->high_voltage_max_dispclk = bw_पूर्णांक_to_fixed(643);
		vbios->low_voltage_max_phyclk = bw_पूर्णांक_to_fixed(540);
		vbios->mid_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->high_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->data_वापस_bus_width = bw_पूर्णांक_to_fixed(32);
		vbios->trc = bw_पूर्णांक_to_fixed(50);
		vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(4);
		vbios->stutter_self_refresh_निकास_latency = bw_frc_to_fixed(158, 10);
		vbios->stutter_self_refresh_entry_latency = bw_पूर्णांक_to_fixed(0);
		vbios->nbp_state_change_latency = bw_frc_to_fixed(2008, 100);
		vbios->mcअगरwrmc_urgent_latency = bw_पूर्णांक_to_fixed(10);
		vbios->scatter_gather_enable = true;
		vbios->करोwn_spपढ़ो_percentage = bw_frc_to_fixed(5, 10);
		vbios->cursor_width = 32;
		vbios->average_compression_rate = 4;
		vbios->number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel = 256;
		vbios->blackout_duration = bw_पूर्णांक_to_fixed(0); /* us */
		vbios->maximum_blackout_recovery_समय = bw_पूर्णांक_to_fixed(0);

		dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip->large_cursor = false;
		dceip->dmअगर_request_buffer_size = bw_पूर्णांक_to_fixed(768);
		dceip->dmअगर_pipe_en_fbc_chunk_tracker = false;
		dceip->cursor_max_outstanding_group_num = 1;
		dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb = 2;
		dceip->chunk_width = 256;
		dceip->number_of_graphics_pipes = 2;
		dceip->number_of_underlay_pipes = 1;
		dceip->low_घातer_tiling_mode = 0;
		dceip->display_ग_लिखो_back_supported = false;
		dceip->argb_compression_support = true;
		dceip->underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip->underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->underlay_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip->graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->graphics_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->alpha_vscaler_efficiency = bw_पूर्णांक_to_fixed(3);
		dceip->max_dmअगर_buffer_allocated = 2;
		dceip->graphics_dmअगर_size = 12288;
		dceip->underlay_luma_dmअगर_size = 19456;
		dceip->underlay_chroma_dmअगर_size = 23552;
		dceip->pre_करोwnscaler_enabled = true;
		dceip->underlay_करोwnscale_prefetch_enabled = true;
		dceip->lb_ग_लिखो_pixels_per_dispclk = bw_पूर्णांक_to_fixed(1);
		dceip->lb_size_per_component444 = bw_पूर्णांक_to_fixed(82176);
		dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching = false;
		dceip->stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor =
			bw_पूर्णांक_to_fixed(0);
		dceip->underlay420_luma_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->underlay420_chroma_lb_size_per_component =
			bw_पूर्णांक_to_fixed(164352);
		dceip->underlay422_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->cursor_chunk_width = bw_पूर्णांक_to_fixed(64);
		dceip->cursor_dcp_buffer_lines = bw_पूर्णांक_to_fixed(4);
		dceip->underlay_maximum_width_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1920);
		dceip->underlay_maximum_height_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1080);
		dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_पूर्णांक_to_fixed(25);
		dceip->minimum_outstanding_pte_request_limit = bw_पूर्णांक_to_fixed(
			2);
		dceip->maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_पूर्णांक_to_fixed(128);
		dceip->limit_excessive_outstanding_dmअगर_requests = true;
		dceip->linear_mode_line_request_alternation_slice =
			bw_पूर्णांक_to_fixed(64);
		dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip->display_ग_लिखो_back420_luma_mcअगरwr_buffer_size = 12288;
		dceip->display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size = 8192;
		dceip->request_efficiency = bw_frc_to_fixed(8, 10);
		dceip->dispclk_per_request = bw_पूर्णांक_to_fixed(2);
		dceip->dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip->display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip->scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip->mcअगरwr_all_surfaces_burst_समय = bw_पूर्णांक_to_fixed(0);
		अवरोध;
	हाल BW_CALCS_VERSION_VEGA10:
		vbios->memory_type = bw_def_hbm;
		vbios->dram_channel_width_in_bits = 128;
		vbios->number_of_dram_channels = asic_id.vram_width / vbios->dram_channel_width_in_bits;
		vbios->number_of_dram_banks = 16;
		vbios->high_yclk = bw_पूर्णांक_to_fixed(2400);
		vbios->mid_yclk = bw_पूर्णांक_to_fixed(1700);
		vbios->low_yclk = bw_पूर्णांक_to_fixed(1000);
		vbios->low_sclk = bw_पूर्णांक_to_fixed(300);
		vbios->mid1_sclk = bw_पूर्णांक_to_fixed(350);
		vbios->mid2_sclk = bw_पूर्णांक_to_fixed(400);
		vbios->mid3_sclk = bw_पूर्णांक_to_fixed(500);
		vbios->mid4_sclk = bw_पूर्णांक_to_fixed(600);
		vbios->mid5_sclk = bw_पूर्णांक_to_fixed(700);
		vbios->mid6_sclk = bw_पूर्णांक_to_fixed(760);
		vbios->high_sclk = bw_पूर्णांक_to_fixed(776);
		vbios->low_voltage_max_dispclk = bw_पूर्णांक_to_fixed(460);
		vbios->mid_voltage_max_dispclk = bw_पूर्णांक_to_fixed(670);
		vbios->high_voltage_max_dispclk = bw_पूर्णांक_to_fixed(1133);
		vbios->low_voltage_max_phyclk = bw_पूर्णांक_to_fixed(540);
		vbios->mid_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->high_voltage_max_phyclk = bw_पूर्णांक_to_fixed(810);
		vbios->data_वापस_bus_width = bw_पूर्णांक_to_fixed(32);
		vbios->trc = bw_पूर्णांक_to_fixed(48);
		vbios->dmअगरmc_urgent_latency = bw_पूर्णांक_to_fixed(3);
		vbios->stutter_self_refresh_निकास_latency = bw_frc_to_fixed(75, 10);
		vbios->stutter_self_refresh_entry_latency = bw_frc_to_fixed(19, 10);
		vbios->nbp_state_change_latency = bw_पूर्णांक_to_fixed(39);
		vbios->mcअगरwrmc_urgent_latency = bw_पूर्णांक_to_fixed(10);
		vbios->scatter_gather_enable = false;
		vbios->करोwn_spपढ़ो_percentage = bw_frc_to_fixed(5, 10);
		vbios->cursor_width = 32;
		vbios->average_compression_rate = 4;
		vbios->number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel = 8;
		vbios->blackout_duration = bw_पूर्णांक_to_fixed(0); /* us */
		vbios->maximum_blackout_recovery_समय = bw_पूर्णांक_to_fixed(0);

		dceip->max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation = 100;
		dceip->percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip->large_cursor = false;
		dceip->dmअगर_request_buffer_size = bw_पूर्णांक_to_fixed(2304);
		dceip->dmअगर_pipe_en_fbc_chunk_tracker = true;
		dceip->cursor_max_outstanding_group_num = 1;
		dceip->lines_पूर्णांकerleaved_पूर्णांकo_lb = 2;
		dceip->chunk_width = 256;
		dceip->number_of_graphics_pipes = 6;
		dceip->number_of_underlay_pipes = 0;
		dceip->low_घातer_tiling_mode = 0;
		dceip->display_ग_लिखो_back_supported = true;
		dceip->argb_compression_support = true;
		dceip->underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip->underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->underlay_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip->graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip->graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip->graphics_vscaler_efficiency12_bit_per_component =
			bw_पूर्णांक_to_fixed(3);
		dceip->alpha_vscaler_efficiency = bw_पूर्णांक_to_fixed(3);
		dceip->max_dmअगर_buffer_allocated = 4;
		dceip->graphics_dmअगर_size = 24576;
		dceip->underlay_luma_dmअगर_size = 19456;
		dceip->underlay_chroma_dmअगर_size = 23552;
		dceip->pre_करोwnscaler_enabled = true;
		dceip->underlay_करोwnscale_prefetch_enabled = false;
		dceip->lb_ग_लिखो_pixels_per_dispclk = bw_पूर्णांक_to_fixed(1);
		dceip->lb_size_per_component444 = bw_पूर्णांक_to_fixed(245952);
		dceip->graphics_lb_noकरोwnscaling_multi_line_prefetching = true;
		dceip->stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor =
			bw_पूर्णांक_to_fixed(1);
		dceip->underlay420_luma_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->underlay420_chroma_lb_size_per_component =
			bw_पूर्णांक_to_fixed(164352);
		dceip->underlay422_lb_size_per_component = bw_पूर्णांक_to_fixed(
			82176);
		dceip->cursor_chunk_width = bw_पूर्णांक_to_fixed(64);
		dceip->cursor_dcp_buffer_lines = bw_पूर्णांक_to_fixed(4);
		dceip->underlay_maximum_width_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1920);
		dceip->underlay_maximum_height_efficient_क्रम_tiling =
			bw_पूर्णांक_to_fixed(1080);
		dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_पूर्णांक_to_fixed(25);
		dceip->minimum_outstanding_pte_request_limit = bw_पूर्णांक_to_fixed(
			2);
		dceip->maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_पूर्णांक_to_fixed(128);
		dceip->limit_excessive_outstanding_dmअगर_requests = true;
		dceip->linear_mode_line_request_alternation_slice =
			bw_पूर्णांक_to_fixed(64);
		dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip->display_ग_लिखो_back420_luma_mcअगरwr_buffer_size = 12288;
		dceip->display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size = 8192;
		dceip->request_efficiency = bw_frc_to_fixed(8, 10);
		dceip->dispclk_per_request = bw_पूर्णांक_to_fixed(2);
		dceip->dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip->display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip->scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip->mcअगरwr_all_surfaces_burst_समय = bw_पूर्णांक_to_fixed(0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	*bw_dceip = *dceip;
	*bw_vbios = *vbios;

	kमुक्त(dceip);
	kमुक्त(vbios);
पूर्ण

/*
 * Compare calculated (required) घड़ीs against the घड़ीs available at
 * maximum voltage (max Perक्रमmance Level).
 */
अटल bool is_display_configuration_supported(
	स्थिर काष्ठा bw_calcs_vbios *vbios,
	स्थिर काष्ठा dce_bw_output *calcs_output)
अणु
	uपूर्णांक32_t पूर्णांक_max_clk;

	पूर्णांक_max_clk = bw_fixed_to_पूर्णांक(vbios->high_voltage_max_dispclk);
	पूर्णांक_max_clk *= 1000; /* MHz to kHz */
	अगर (calcs_output->dispclk_khz > पूर्णांक_max_clk)
		वापस false;

	पूर्णांक_max_clk = bw_fixed_to_पूर्णांक(vbios->high_sclk);
	पूर्णांक_max_clk *= 1000; /* MHz to kHz */
	अगर (calcs_output->sclk_khz > पूर्णांक_max_clk)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम populate_initial_data(
	स्थिर काष्ठा pipe_ctx pipe[], पूर्णांक pipe_count, काष्ठा bw_calcs_data *data)
अणु
	पूर्णांक i, j;
	पूर्णांक num_displays = 0;

	data->underlay_surface_type = bw_def_420;
	data->panning_and_bezel_adjusपंचांगent = bw_def_none;
	data->graphics_lb_bpc = 10;
	data->underlay_lb_bpc = 8;
	data->underlay_tiling_mode = bw_def_tiled;
	data->graphics_tiling_mode = bw_def_tiled;
	data->underlay_micro_tile_mode = bw_def_display_micro_tiling;
	data->graphics_micro_tile_mode = bw_def_display_micro_tiling;
	data->increase_voltage_to_support_mclk_चयन = true;

	/* Pipes with underlay first */
	क्रम (i = 0; i < pipe_count; i++) अणु
		अगर (!pipe[i].stream || !pipe[i].bottom_pipe)
			जारी;

		ASSERT(pipe[i].plane_state);

		अगर (num_displays == 0) अणु
			अगर (!pipe[i].plane_state->visible)
				data->d0_underlay_mode = bw_def_underlay_only;
			अन्यथा
				data->d0_underlay_mode = bw_def_blend;
		पूर्ण अन्यथा अणु
			अगर (!pipe[i].plane_state->visible)
				data->d1_underlay_mode = bw_def_underlay_only;
			अन्यथा
				data->d1_underlay_mode = bw_def_blend;
		पूर्ण

		data->fbc_en[num_displays + 4] = false;
		data->lpt_en[num_displays + 4] = false;
		data->h_total[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->timing.h_total);
		data->v_total[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->timing.v_total);
		data->pixel_rate[num_displays + 4] = bw_frc_to_fixed(pipe[i].stream->timing.pix_clk_100hz, 10000);
		data->src_width[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.viewport.width);
		data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
		data->src_height[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.viewport.height);
		data->h_taps[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.taps.h_taps);
		data->v_taps[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.taps.v_taps);
		data->h_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.horz.value);
		data->v_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.vert.value);
		चयन (pipe[i].plane_state->rotation) अणु
		हाल ROTATION_ANGLE_0:
			data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(0);
			अवरोध;
		हाल ROTATION_ANGLE_90:
			data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(90);
			अवरोध;
		हाल ROTATION_ANGLE_180:
			data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(180);
			अवरोध;
		हाल ROTATION_ANGLE_270:
			data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(270);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		चयन (pipe[i].plane_state->क्रमmat) अणु
		हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
			data->bytes_per_pixel[num_displays + 4] = 2;
			अवरोध;
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
		हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
			data->bytes_per_pixel[num_displays + 4] = 4;
			अवरोध;
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
			data->bytes_per_pixel[num_displays + 4] = 8;
			अवरोध;
		शेष:
			data->bytes_per_pixel[num_displays + 4] = 4;
			अवरोध;
		पूर्ण
		data->पूर्णांकerlace_mode[num_displays + 4] = false;
		data->stereo_mode[num_displays + 4] = bw_def_mono;


		क्रम (j = 0; j < 2; j++) अणु
			data->fbc_en[num_displays * 2 + j] = false;
			data->lpt_en[num_displays * 2 + j] = false;

			data->src_height[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.viewport.height);
			data->src_width[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.viewport.width);
			data->pitch_in_pixels[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(
					pipe[i].bottom_pipe->plane_state->plane_size.surface_pitch);
			data->h_taps[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.taps.h_taps);
			data->v_taps[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.taps.v_taps);
			data->h_scale_ratio[num_displays * 2 + j] = fixed31_32_to_bw_fixed(
					pipe[i].bottom_pipe->plane_res.scl_data.ratios.horz.value);
			data->v_scale_ratio[num_displays * 2 + j] = fixed31_32_to_bw_fixed(
					pipe[i].bottom_pipe->plane_res.scl_data.ratios.vert.value);
			चयन (pipe[i].bottom_pipe->plane_state->rotation) अणु
			हाल ROTATION_ANGLE_0:
				data->rotation_angle[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(0);
				अवरोध;
			हाल ROTATION_ANGLE_90:
				data->rotation_angle[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(90);
				अवरोध;
			हाल ROTATION_ANGLE_180:
				data->rotation_angle[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(180);
				अवरोध;
			हाल ROTATION_ANGLE_270:
				data->rotation_angle[num_displays * 2 + j] = bw_पूर्णांक_to_fixed(270);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			data->stereo_mode[num_displays * 2 + j] = bw_def_mono;
		पूर्ण

		num_displays++;
	पूर्ण

	/* Pipes without underlay after */
	क्रम (i = 0; i < pipe_count; i++) अणु
		अचिन्हित पूर्णांक pixel_घड़ी_100hz;
		अगर (!pipe[i].stream || pipe[i].bottom_pipe)
			जारी;


		data->fbc_en[num_displays + 4] = false;
		data->lpt_en[num_displays + 4] = false;
		data->h_total[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->timing.h_total);
		data->v_total[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->timing.v_total);
		pixel_घड़ी_100hz = pipe[i].stream->timing.pix_clk_100hz;
		अगर (pipe[i].stream->timing.timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
			pixel_घड़ी_100hz *= 2;
		data->pixel_rate[num_displays + 4] = bw_frc_to_fixed(pixel_घड़ी_100hz, 10000);
		अगर (pipe[i].plane_state) अणु
			data->src_width[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.viewport.width);
			data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
			data->src_height[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.viewport.height);
			data->h_taps[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.taps.h_taps);
			data->v_taps[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].plane_res.scl_data.taps.v_taps);
			data->h_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.horz.value);
			data->v_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.vert.value);
			चयन (pipe[i].plane_state->rotation) अणु
			हाल ROTATION_ANGLE_0:
				data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(0);
				अवरोध;
			हाल ROTATION_ANGLE_90:
				data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(90);
				अवरोध;
			हाल ROTATION_ANGLE_180:
				data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(180);
				अवरोध;
			हाल ROTATION_ANGLE_270:
				data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(270);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			चयन (pipe[i].plane_state->क्रमmat) अणु
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
			हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
				data->bytes_per_pixel[num_displays + 4] = 2;
				अवरोध;
			हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
				data->bytes_per_pixel[num_displays + 4] = 4;
				अवरोध;
			हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
				data->bytes_per_pixel[num_displays + 4] = 8;
				अवरोध;
			शेष:
				data->bytes_per_pixel[num_displays + 4] = 4;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (pipe[i].stream->dst.width != 0 &&
					pipe[i].stream->dst.height != 0 &&
					pipe[i].stream->src.width != 0 &&
					pipe[i].stream->src.height != 0) अणु
			data->src_width[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->src.width);
			data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
			data->src_height[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->src.height);
			data->h_taps[num_displays + 4] = pipe[i].stream->src.width == pipe[i].stream->dst.width ? bw_पूर्णांक_to_fixed(1) : bw_पूर्णांक_to_fixed(2);
			data->v_taps[num_displays + 4] = pipe[i].stream->src.height == pipe[i].stream->dst.height ? bw_पूर्णांक_to_fixed(1) : bw_पूर्णांक_to_fixed(2);
			data->h_scale_ratio[num_displays + 4] = bw_frc_to_fixed(pipe[i].stream->src.width, pipe[i].stream->dst.width);
			data->v_scale_ratio[num_displays + 4] = bw_frc_to_fixed(pipe[i].stream->src.height, pipe[i].stream->dst.height);
			data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(0);
			data->bytes_per_pixel[num_displays + 4] = 4;
		पूर्ण अन्यथा अणु
			data->src_width[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->timing.h_addressable);
			data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
			data->src_height[num_displays + 4] = bw_पूर्णांक_to_fixed(pipe[i].stream->timing.v_addressable);
			data->h_taps[num_displays + 4] = bw_पूर्णांक_to_fixed(1);
			data->v_taps[num_displays + 4] = bw_पूर्णांक_to_fixed(1);
			data->h_scale_ratio[num_displays + 4] = bw_पूर्णांक_to_fixed(1);
			data->v_scale_ratio[num_displays + 4] = bw_पूर्णांक_to_fixed(1);
			data->rotation_angle[num_displays + 4] = bw_पूर्णांक_to_fixed(0);
			data->bytes_per_pixel[num_displays + 4] = 4;
		पूर्ण

		data->पूर्णांकerlace_mode[num_displays + 4] = false;
		data->stereo_mode[num_displays + 4] = bw_def_mono;
		num_displays++;
	पूर्ण

	data->number_of_displays = num_displays;
पूर्ण

अटल bool all_displays_in_sync(स्थिर काष्ठा pipe_ctx pipe[],
				 पूर्णांक pipe_count)
अणु
	स्थिर काष्ठा pipe_ctx *active_pipes[MAX_PIPES];
	पूर्णांक i, num_active_pipes = 0;

	क्रम (i = 0; i < pipe_count; i++) अणु
		अगर (!pipe[i].stream || pipe[i].top_pipe)
			जारी;

		active_pipes[num_active_pipes++] = &pipe[i];
	पूर्ण

	अगर (!num_active_pipes)
		वापस false;

	क्रम (i = 1; i < num_active_pipes; ++i) अणु
		अगर (!resource_are_streams_timing_synchronizable(
			    active_pipes[0]->stream, active_pipes[i]->stream)) अणु
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/*
 * Return:
 *	true -	Display(s) configuration supported.
 *		In this हाल 'calcs_output' contains data क्रम HW programming
 *	false - Display(s) configuration not supported (not enough bandwidth).
 */
bool bw_calcs(काष्ठा dc_context *ctx,
	स्थिर काष्ठा bw_calcs_dceip *dceip,
	स्थिर काष्ठा bw_calcs_vbios *vbios,
	स्थिर काष्ठा pipe_ctx pipe[],
	पूर्णांक pipe_count,
	काष्ठा dce_bw_output *calcs_output)
अणु
	काष्ठा bw_calcs_data *data = kzalloc(माप(काष्ठा bw_calcs_data),
					     GFP_KERNEL);
	अगर (!data)
		वापस false;

	populate_initial_data(pipe, pipe_count, data);

	अगर (ctx->dc->config.multi_mon_pp_mclk_चयन)
		calcs_output->all_displays_in_sync = all_displays_in_sync(pipe, pipe_count);
	अन्यथा
		calcs_output->all_displays_in_sync = false;

	अगर (data->number_of_displays != 0) अणु
		uपूर्णांक8_t yclk_lvl;
		काष्ठा bw_fixed high_sclk = vbios->high_sclk;
		काष्ठा bw_fixed mid1_sclk = vbios->mid1_sclk;
		काष्ठा bw_fixed mid2_sclk = vbios->mid2_sclk;
		काष्ठा bw_fixed mid3_sclk = vbios->mid3_sclk;
		काष्ठा bw_fixed mid4_sclk = vbios->mid4_sclk;
		काष्ठा bw_fixed mid5_sclk = vbios->mid5_sclk;
		काष्ठा bw_fixed mid6_sclk = vbios->mid6_sclk;
		काष्ठा bw_fixed low_sclk = vbios->low_sclk;
		काष्ठा bw_fixed high_yclk = vbios->high_yclk;
		काष्ठा bw_fixed mid_yclk = vbios->mid_yclk;
		काष्ठा bw_fixed low_yclk = vbios->low_yclk;

		अगर (ctx->dc->debug.bandwidth_calcs_trace) अणु
			prपूर्णांक_bw_calcs_dceip(ctx, dceip);
			prपूर्णांक_bw_calcs_vbios(ctx, vbios);
			prपूर्णांक_bw_calcs_data(ctx, data);
		पूर्ण
		calculate_bandwidth(dceip, vbios, data);

		yclk_lvl = data->y_clk_level;

		calcs_output->nbp_state_change_enable =
			data->nbp_state_change_enable;
		calcs_output->cpuc_state_change_enable =
				data->cpuc_state_change_enable;
		calcs_output->cpup_state_change_enable =
				data->cpup_state_change_enable;
		calcs_output->stutter_mode_enable =
				data->stutter_mode_enable;
		calcs_output->dispclk_khz =
			bw_fixed_to_पूर्णांक(bw_mul(data->dispclk,
					bw_पूर्णांक_to_fixed(1000)));
		calcs_output->blackout_recovery_समय_us =
			bw_fixed_to_पूर्णांक(data->blackout_recovery_समय);
		calcs_output->sclk_khz =
			bw_fixed_to_पूर्णांक(bw_mul(data->required_sclk,
					bw_पूर्णांक_to_fixed(1000)));
		calcs_output->sclk_deep_sleep_khz =
			bw_fixed_to_पूर्णांक(bw_mul(data->sclk_deep_sleep,
					bw_पूर्णांक_to_fixed(1000)));
		अगर (yclk_lvl == 0)
			calcs_output->yclk_khz = bw_fixed_to_पूर्णांक(
				bw_mul(low_yclk, bw_पूर्णांक_to_fixed(1000)));
		अन्यथा अगर (yclk_lvl == 1)
			calcs_output->yclk_khz = bw_fixed_to_पूर्णांक(
				bw_mul(mid_yclk, bw_पूर्णांक_to_fixed(1000)));
		अन्यथा
			calcs_output->yclk_khz = bw_fixed_to_पूर्णांक(
				bw_mul(high_yclk, bw_पूर्णांक_to_fixed(1000)));

		/* units: nanosecond, 16bit storage. */

		calcs_output->nbp_state_change_wm_ns[0].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->nbp_state_change_wm_ns[1].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->nbp_state_change_wm_ns[2].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[6], bw_पूर्णांक_to_fixed(1000)));

		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->nbp_state_change_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
							nbp_state_change_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->nbp_state_change_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->nbp_state_change_wm_ns[5].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[9], bw_पूर्णांक_to_fixed(1000)));



		calcs_output->stutter_निकास_wm_ns[0].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_निकास_wm_ns[1].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_निकास_wm_ns[2].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->stutter_निकास_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->stutter_निकास_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->stutter_निकास_wm_ns[5].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		calcs_output->stutter_entry_wm_ns[0].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_entry_wm_ns[1].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_entry_wm_ns[2].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->stutter_entry_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->stutter_entry_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->stutter_entry_wm_ns[5].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		calcs_output->urgent_wm_ns[0].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->urgent_wm_ns[1].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->urgent_wm_ns[2].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->urgent_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->urgent_wm_ns[3].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[4].a_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->urgent_wm_ns[5].a_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		अगर (dceip->version != BW_CALCS_VERSION_CARRIZO) अणु
			((काष्ठा bw_calcs_vbios *)vbios)->low_sclk = mid3_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid1_sclk = mid3_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid2_sclk = mid3_sclk;
			calculate_bandwidth(dceip, vbios, data);

			calcs_output->nbp_state_change_wm_ns[0].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[4],bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[1].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[5], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[2].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[6], bw_पूर्णांक_to_fixed(1000)));

			अगर (ctx->dc->caps.max_slave_planes) अणु
				calcs_output->nbp_state_change_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[0], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->nbp_state_change_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[1], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण अन्यथा अणु
				calcs_output->nbp_state_change_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[7], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->nbp_state_change_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[8], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण
			calcs_output->nbp_state_change_wm_ns[5].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[9], bw_पूर्णांक_to_fixed(1000)));



			calcs_output->stutter_निकास_wm_ns[0].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[4], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[1].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[5], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[2].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[6], bw_पूर्णांक_to_fixed(1000)));
			अगर (ctx->dc->caps.max_slave_planes) अणु
				calcs_output->stutter_निकास_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[0], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->stutter_निकास_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[1], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण अन्यथा अणु
				calcs_output->stutter_निकास_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[7], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->stutter_निकास_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[8], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण
			calcs_output->stutter_निकास_wm_ns[5].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[9], bw_पूर्णांक_to_fixed(1000)));

			calcs_output->stutter_entry_wm_ns[0].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[4], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[1].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[5], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[2].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[6], bw_पूर्णांक_to_fixed(1000)));
			अगर (ctx->dc->caps.max_slave_planes) अणु
				calcs_output->stutter_entry_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_entry_watermark[0], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->stutter_entry_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_entry_watermark[1], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण अन्यथा अणु
				calcs_output->stutter_entry_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_entry_watermark[7], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->stutter_entry_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_entry_watermark[8], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण
			calcs_output->stutter_entry_wm_ns[5].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[9], bw_पूर्णांक_to_fixed(1000)));

			calcs_output->urgent_wm_ns[0].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[4], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[1].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[5], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[2].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[6], bw_पूर्णांक_to_fixed(1000)));
			अगर (ctx->dc->caps.max_slave_planes) अणु
				calcs_output->urgent_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[0], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->urgent_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[1], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण अन्यथा अणु
				calcs_output->urgent_wm_ns[3].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[7], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->urgent_wm_ns[4].b_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[8], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण
			calcs_output->urgent_wm_ns[5].b_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[9], bw_पूर्णांक_to_fixed(1000)));

			((काष्ठा bw_calcs_vbios *)vbios)->low_sclk = low_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid1_sclk = mid1_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid2_sclk = mid2_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->low_yclk = mid_yclk;
			calculate_bandwidth(dceip, vbios, data);

			calcs_output->nbp_state_change_wm_ns[0].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[4], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[1].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[5], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[2].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[6], bw_पूर्णांक_to_fixed(1000)));
			अगर (ctx->dc->caps.max_slave_planes) अणु
				calcs_output->nbp_state_change_wm_ns[3].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[0], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->nbp_state_change_wm_ns[4].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[1], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण अन्यथा अणु
				calcs_output->nbp_state_change_wm_ns[3].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[7], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->nbp_state_change_wm_ns[4].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						nbp_state_change_watermark[8], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण
			calcs_output->nbp_state_change_wm_ns[5].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[9], bw_पूर्णांक_to_fixed(1000)));


			calcs_output->stutter_निकास_wm_ns[0].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[4], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[1].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[5], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[2].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[6], bw_पूर्णांक_to_fixed(1000)));
			अगर (ctx->dc->caps.max_slave_planes) अणु
				calcs_output->stutter_निकास_wm_ns[3].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[0], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->stutter_निकास_wm_ns[4].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[1], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण अन्यथा अणु
				calcs_output->stutter_निकास_wm_ns[3].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[7], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->stutter_निकास_wm_ns[4].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						stutter_निकास_watermark[8], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण
			calcs_output->stutter_निकास_wm_ns[5].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		calcs_output->stutter_entry_wm_ns[0].c_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_entry_wm_ns[1].c_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_entry_wm_ns[2].c_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->stutter_entry_wm_ns[3].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[4].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->stutter_entry_wm_ns[3].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[4].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->stutter_entry_wm_ns[5].c_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[9], bw_पूर्णांक_to_fixed(1000)));

			calcs_output->urgent_wm_ns[0].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[4], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[1].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[5], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[2].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[6], bw_पूर्णांक_to_fixed(1000)));
			अगर (ctx->dc->caps.max_slave_planes) अणु
				calcs_output->urgent_wm_ns[3].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[0], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->urgent_wm_ns[4].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[1], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण अन्यथा अणु
				calcs_output->urgent_wm_ns[3].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[7], bw_पूर्णांक_to_fixed(1000)));
				calcs_output->urgent_wm_ns[4].c_mark =
					bw_fixed_to_पूर्णांक(bw_mul(data->
						urgent_watermark[8], bw_पूर्णांक_to_fixed(1000)));
			पूर्ण
			calcs_output->urgent_wm_ns[5].c_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[9], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण

		अगर (dceip->version == BW_CALCS_VERSION_CARRIZO) अणु
			((काष्ठा bw_calcs_vbios *)vbios)->low_yclk = high_yclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid_yclk = high_yclk;
			((काष्ठा bw_calcs_vbios *)vbios)->low_sclk = high_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid1_sclk = high_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid2_sclk = high_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid3_sclk = high_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid4_sclk = high_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid5_sclk = high_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid6_sclk = high_sclk;
		पूर्ण अन्यथा अणु
			((काष्ठा bw_calcs_vbios *)vbios)->low_yclk = mid_yclk;
			((काष्ठा bw_calcs_vbios *)vbios)->low_sclk = mid3_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid1_sclk = mid3_sclk;
			((काष्ठा bw_calcs_vbios *)vbios)->mid2_sclk = mid3_sclk;
		पूर्ण

		calculate_bandwidth(dceip, vbios, data);

		calcs_output->nbp_state_change_wm_ns[0].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->nbp_state_change_wm_ns[1].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->nbp_state_change_wm_ns[2].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->nbp_state_change_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->nbp_state_change_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->nbp_state_change_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					nbp_state_change_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->nbp_state_change_wm_ns[5].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				nbp_state_change_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		calcs_output->stutter_निकास_wm_ns[0].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_निकास_wm_ns[1].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_निकास_wm_ns[2].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->stutter_निकास_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->stutter_निकास_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_निकास_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_निकास_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->stutter_निकास_wm_ns[5].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_निकास_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		calcs_output->stutter_entry_wm_ns[0].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_entry_wm_ns[1].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->stutter_entry_wm_ns[2].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->stutter_entry_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->stutter_entry_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->stutter_entry_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					stutter_entry_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->stutter_entry_wm_ns[5].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				stutter_entry_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		calcs_output->urgent_wm_ns[0].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[4], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->urgent_wm_ns[1].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[5], bw_पूर्णांक_to_fixed(1000)));
		calcs_output->urgent_wm_ns[2].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[6], bw_पूर्णांक_to_fixed(1000)));
		अगर (ctx->dc->caps.max_slave_planes) अणु
			calcs_output->urgent_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[0], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[1], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण अन्यथा अणु
			calcs_output->urgent_wm_ns[3].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[7], bw_पूर्णांक_to_fixed(1000)));
			calcs_output->urgent_wm_ns[4].d_mark =
				bw_fixed_to_पूर्णांक(bw_mul(data->
					urgent_watermark[8], bw_पूर्णांक_to_fixed(1000)));
		पूर्ण
		calcs_output->urgent_wm_ns[5].d_mark =
			bw_fixed_to_पूर्णांक(bw_mul(data->
				urgent_watermark[9], bw_पूर्णांक_to_fixed(1000)));

		((काष्ठा bw_calcs_vbios *)vbios)->low_yclk = low_yclk;
		((काष्ठा bw_calcs_vbios *)vbios)->mid_yclk = mid_yclk;
		((काष्ठा bw_calcs_vbios *)vbios)->low_sclk = low_sclk;
		((काष्ठा bw_calcs_vbios *)vbios)->mid1_sclk = mid1_sclk;
		((काष्ठा bw_calcs_vbios *)vbios)->mid2_sclk = mid2_sclk;
		((काष्ठा bw_calcs_vbios *)vbios)->mid3_sclk = mid3_sclk;
		((काष्ठा bw_calcs_vbios *)vbios)->mid4_sclk = mid4_sclk;
		((काष्ठा bw_calcs_vbios *)vbios)->mid5_sclk = mid5_sclk;
		((काष्ठा bw_calcs_vbios *)vbios)->mid6_sclk = mid6_sclk;
		((काष्ठा bw_calcs_vbios *)vbios)->high_sclk = high_sclk;
	पूर्ण अन्यथा अणु
		calcs_output->nbp_state_change_enable = true;
		calcs_output->cpuc_state_change_enable = true;
		calcs_output->cpup_state_change_enable = true;
		calcs_output->stutter_mode_enable = true;
		calcs_output->dispclk_khz = 0;
		calcs_output->sclk_khz = 0;
	पूर्ण

	kमुक्त(data);

	वापस is_display_configuration_supported(vbios, calcs_output);
पूर्ण
