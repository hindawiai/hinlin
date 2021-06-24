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

#अगर_अघोषित __DC_CLOCK_SOURCE_H__
#घोषणा __DC_CLOCK_SOURCE_H__

#समावेश "dc_types.h"
#समावेश "include/grph_object_id.h"
#समावेश "include/bios_parser_types.h"

काष्ठा घड़ी_source;

काष्ठा spपढ़ो_spectrum_data अणु
	uपूर्णांक32_t percentage;		/*> In unit of 0.01% or 0.001%*/
	uपूर्णांक32_t percentage_भागider;	/*> 100 or 1000	*/
	uपूर्णांक32_t freq_range_khz;
	uपूर्णांक32_t modulation_freq_hz;

	काष्ठा spपढ़ो_spectrum_flags flags;
पूर्ण;

काष्ठा delta_sigma_data अणु
	uपूर्णांक32_t feedback_amount;
	uपूर्णांक32_t nfrac_amount;
	uपूर्णांक32_t ds_frac_size;
	uपूर्णांक32_t ds_frac_amount;
पूर्ण;

/**
 *  Pixel Clock Parameters काष्ठाure
 *  These parameters are required as input
 *  when calculating Pixel Clock Dividers क्रम requested Pixel Clock
 */
काष्ठा pixel_clk_flags अणु
	uपूर्णांक32_t ENABLE_SS:1;
	uपूर्णांक32_t DISPLAY_BLANKED:1;
	uपूर्णांक32_t PROGRAM_PIXEL_CLOCK:1;
	uपूर्णांक32_t PROGRAM_ID_CLOCK:1;
	uपूर्णांक32_t SUPPORT_YCBCR420:1;
पूर्ण;

/**
 *  Display Port HW De spपढ़ो of Reference Clock related Parameters काष्ठाure
 *  Store it once at boot क्रम later usage
  */
काष्ठा csdp_ref_clk_ds_params अणु
	bool hw_dso_n_dp_ref_clk;
/* Flag क्रम HW De Spपढ़ो enabled (अगर enabled SS on DP Reference Clock)*/
	uपूर्णांक32_t avg_dp_ref_clk_khz;
/* Average DP Reference घड़ी (in KHz)*/
	uपूर्णांक32_t ss_percentage_on_dp_ref_clk;
/* DP Reference घड़ी SS percentage
 * (not to be mixed with DP IDCLK SS from PLL Settings)*/
	uपूर्णांक32_t ss_percentage_भागider;
/* DP Reference घड़ी SS percentage भागider */
पूर्ण;

काष्ठा pixel_clk_params अणु
	uपूर्णांक32_t requested_pix_clk_100hz;
/*> Requested Pixel Clock
 * (based on Video Timing standard used क्रम requested mode)*/
	uपूर्णांक32_t requested_sym_clk; /* in KHz */
/*> Requested Sym Clock (relevant only क्रम display port)*/
	uपूर्णांक32_t dp_ref_clk; /* in KHz */
/*> DP reference घड़ी - calculated only क्रम DP संकेत क्रम specअगरic हालs*/
	काष्ठा graphics_object_id encoder_object_id;
/*> Encoder object Id - needed by VBIOS Exec table*/
	क्रमागत संकेत_type संकेत_type;
/*> संकेतType -> Encoder Mode - needed by VBIOS Exec table*/
	क्रमागत controller_id controller_id;
/*> ControllerId - which controller using this PLL*/
	क्रमागत dc_color_depth color_depth;
	काष्ठा csdp_ref_clk_ds_params de_spपढ़ो_params;
/*> de-spपढ़ो info, relevant only क्रम on-the-fly tune-up pixel rate*/
	क्रमागत dc_pixel_encoding pixel_encoding;
	काष्ठा pixel_clk_flags flags;
पूर्ण;

/**
 *  Pixel Clock Dividers काष्ठाure with desired Pixel Clock
 *  (adjusted after VBIOS exec table),
 *  with actually calculated Clock and reference Crystal frequency
 */
काष्ठा pll_settings अणु
	uपूर्णांक32_t actual_pix_clk_100hz;
	uपूर्णांक32_t adjusted_pix_clk_100hz;
	uपूर्णांक32_t calculated_pix_clk_100hz;
	uपूर्णांक32_t vco_freq;
	uपूर्णांक32_t reference_freq;
	uपूर्णांक32_t reference_भागider;
	uपूर्णांक32_t feedback_भागider;
	uपूर्णांक32_t fract_feedback_भागider;
	uपूर्णांक32_t pix_clk_post_भागider;
	uपूर्णांक32_t ss_percentage;
	bool use_बाह्यal_clk;
पूर्ण;

काष्ठा calc_pll_घड़ी_source_init_data अणु
	काष्ठा dc_bios *bp;
	uपूर्णांक32_t min_pix_clk_pll_post_भागider;
	uपूर्णांक32_t max_pix_clk_pll_post_भागider;
	uपूर्णांक32_t min_pll_ref_भागider;
	uपूर्णांक32_t max_pll_ref_भागider;
	uपूर्णांक32_t min_override_input_pxl_clk_pll_freq_khz;
/* अगर not 0, override the firmware info */

	uपूर्णांक32_t max_override_input_pxl_clk_pll_freq_khz;
/* अगर not 0, override the firmware info */

	uपूर्णांक32_t num_fract_fb_भागider_decimal_poपूर्णांक;
/* number of decimal poपूर्णांक क्रम fractional feedback भागider value */

	uपूर्णांक32_t num_fract_fb_भागider_decimal_poपूर्णांक_precision;
/* number of decimal poपूर्णांक to round off क्रम fractional feedback भागider value*/
	काष्ठा dc_context *ctx;

पूर्ण;

काष्ठा calc_pll_घड़ी_source अणु
	uपूर्णांक32_t ref_freq_khz;
	uपूर्णांक32_t min_pix_घड़ी_pll_post_भागider;
	uपूर्णांक32_t max_pix_घड़ी_pll_post_भागider;
	uपूर्णांक32_t min_pll_ref_भागider;
	uपूर्णांक32_t max_pll_ref_भागider;

	uपूर्णांक32_t max_vco_khz;
	uपूर्णांक32_t min_vco_khz;
	uपूर्णांक32_t min_pll_input_freq_khz;
	uपूर्णांक32_t max_pll_input_freq_khz;

	uपूर्णांक32_t fract_fb_भागider_decimal_poपूर्णांकs_num;
	uपूर्णांक32_t fract_fb_भागider_factor;
	uपूर्णांक32_t fract_fb_भागider_precision;
	uपूर्णांक32_t fract_fb_भागider_precision_factor;
	काष्ठा dc_context *ctx;
पूर्ण;

काष्ठा घड़ी_source_funcs अणु
	bool (*cs_घातer_करोwn)(
			काष्ठा घड़ी_source *);
	bool (*program_pix_clk)(काष्ठा घड़ी_source *,
			काष्ठा pixel_clk_params *, काष्ठा pll_settings *);
	uपूर्णांक32_t (*get_pix_clk_भागiders)(
			काष्ठा घड़ी_source *,
			काष्ठा pixel_clk_params *,
			काष्ठा pll_settings *);
	bool (*get_pixel_clk_frequency_100hz)(
			स्थिर काष्ठा घड़ी_source *घड़ी_source,
			अचिन्हित पूर्णांक inst,
			अचिन्हित पूर्णांक *pixel_clk_khz);
	bool (*override_dp_pix_clk)(
			काष्ठा घड़ी_source *घड़ी_source,
			अचिन्हित पूर्णांक inst,
			अचिन्हित पूर्णांक pixel_clk,
			अचिन्हित पूर्णांक ref_clk);
पूर्ण;

काष्ठा घड़ी_source अणु
	स्थिर काष्ठा घड़ी_source_funcs *funcs;
	काष्ठा dc_context *ctx;
	क्रमागत घड़ी_source_id id;
	bool dp_clk_src;
पूर्ण;

#पूर्ण_अगर
