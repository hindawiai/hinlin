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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"


#समावेश "dc_types.h"
#समावेश "core_types.h"

#समावेश "include/grph_object_id.h"
#समावेश "include/logger_interface.h"

#समावेश "dce_clock_source.h"
#समावेश "clk_mgr.h"

#समावेश "reg_helper.h"

#घोषणा REG(reg)\
	(clk_src->regs->reg)

#घोषणा CTX \
	clk_src->base.ctx

#घोषणा DC_LOGGER_INIT()

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	clk_src->cs_shअगरt->field_name, clk_src->cs_mask->field_name

#घोषणा FRACT_FB_DIVIDER_DEC_POINTS_MAX_NUM 6
#घोषणा CALC_PLL_CLK_SRC_ERR_TOLERANCE 1
#घोषणा MAX_PLL_CALC_ERROR 0xFFFFFFFF

#घोषणा NUM_ELEMENTS(a) (माप(a) / माप((a)[0]))

अटल स्थिर काष्ठा spपढ़ो_spectrum_data *get_ss_data_entry(
		काष्ठा dce110_clk_src *clk_src,
		क्रमागत संकेत_type संकेत,
		uपूर्णांक32_t pix_clk_khz)
अणु

	uपूर्णांक32_t entrys_num;
	uपूर्णांक32_t i;
	काष्ठा spपढ़ो_spectrum_data *ss_parm = शून्य;
	काष्ठा spपढ़ो_spectrum_data *ret = शून्य;

	चयन (संकेत) अणु
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		ss_parm = clk_src->dvi_ss_params;
		entrys_num = clk_src->dvi_ss_params_cnt;
		अवरोध;

	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		ss_parm = clk_src->hdmi_ss_params;
		entrys_num = clk_src->hdmi_ss_params_cnt;
		अवरोध;

	हाल SIGNAL_TYPE_LVDS:
		ss_parm = clk_src->lvds_ss_params;
		entrys_num = clk_src->lvds_ss_params_cnt;
		अवरोध;

	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
	हाल SIGNAL_TYPE_EDP:
	हाल SIGNAL_TYPE_VIRTUAL:
		ss_parm = clk_src->dp_ss_params;
		entrys_num = clk_src->dp_ss_params_cnt;
		अवरोध;

	शेष:
		ss_parm = शून्य;
		entrys_num = 0;
		अवरोध;
	पूर्ण

	अगर (ss_parm == शून्य)
		वापस ret;

	क्रम (i = 0; i < entrys_num; ++i, ++ss_parm) अणु
		अगर (ss_parm->freq_range_khz >= pix_clk_khz) अणु
			ret = ss_parm;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * calculate_fb_and_fractional_fb_भागider - Calculates feedback and fractional
 *                                          feedback भागiders values
 *
 * @calc_pll_cs:	    Poपूर्णांकer to घड़ी source inक्रमmation
 * @target_pix_clk_100hz:   Desired frequency in 100 Hz
 * @ref_भागider:            Reference भागider (alपढ़ोy known)
 * @post_भागider:           Post Divider (alपढ़ोy known)
 * @feedback_भागider_param: Poपूर्णांकer where to store
 *			    calculated feedback भागider value
 * @fract_feedback_भागider_param: Poपूर्णांकer where to store
 *			    calculated fract feedback भागider value
 *
 * वापस:
 * It fills the locations poपूर्णांकed by feedback_भागider_param
 *					and fract_feedback_भागider_param
 * It वापसs	- true अगर feedback भागider not 0
 *		- false should never happen)
 */
अटल bool calculate_fb_and_fractional_fb_भागider(
		काष्ठा calc_pll_घड़ी_source *calc_pll_cs,
		uपूर्णांक32_t target_pix_clk_100hz,
		uपूर्णांक32_t ref_भागider,
		uपूर्णांक32_t post_भागider,
		uपूर्णांक32_t *feedback_भागider_param,
		uपूर्णांक32_t *fract_feedback_भागider_param)
अणु
	uपूर्णांक64_t feedback_भागider;

	feedback_भागider =
		(uपूर्णांक64_t)target_pix_clk_100hz * ref_भागider * post_भागider;
	feedback_भागider *= 10;
	/* additional factor, since we भागide by 10 afterwards */
	feedback_भागider *= (uपूर्णांक64_t)(calc_pll_cs->fract_fb_भागider_factor);
	feedback_भागider = भाग_u64(feedback_भागider, calc_pll_cs->ref_freq_khz * 10ull);

/*Round to the number of precision
 * The following code replace the old code (ullfeedbackDivider + 5)/10
 * क्रम example अगर the dअगरference between the number
 * of fractional feedback decimal poपूर्णांक and the fractional FB Divider precision
 * is 2 then the equation becomes (ullfeedbackDivider + 5*100) / (10*100))*/

	feedback_भागider += 5ULL *
			    calc_pll_cs->fract_fb_भागider_precision_factor;
	feedback_भागider =
		भाग_u64(feedback_भागider,
			calc_pll_cs->fract_fb_भागider_precision_factor * 10);
	feedback_भागider *= (uपूर्णांक64_t)
			(calc_pll_cs->fract_fb_भागider_precision_factor);

	*feedback_भागider_param =
		भाग_u64_rem(
			feedback_भागider,
			calc_pll_cs->fract_fb_भागider_factor,
			fract_feedback_भागider_param);

	अगर (*feedback_भागider_param != 0)
		वापस true;
	वापस false;
पूर्ण

/**
 * calc_fb_भागider_checking_tolerance - Calculates Feedback and
 *                                      Fractional Feedback भागider values
 *		                        क्रम passed Reference and Post भागider,
 *                                      checking क्रम tolerance.
 * @calc_pll_cs:	Poपूर्णांकer to घड़ी source inक्रमmation
 * @pll_settings:	Poपूर्णांकer to PLL settings
 * @ref_भागider:	Reference भागider (alपढ़ोy known)
 * @post_भागider:	Post Divider (alपढ़ोy known)
 * @tolerance:		Tolerance क्रम Calculated Pixel Clock to be within
 *
 * वापस:
 *  It fills the PLLSettings काष्ठाure with PLL Dividers values
 *  अगर calculated values are within required tolerance
 *  It वापसs	- true अगर error is within tolerance
 *		- false अगर error is not within tolerance
 */
अटल bool calc_fb_भागider_checking_tolerance(
		काष्ठा calc_pll_घड़ी_source *calc_pll_cs,
		काष्ठा pll_settings *pll_settings,
		uपूर्णांक32_t ref_भागider,
		uपूर्णांक32_t post_भागider,
		uपूर्णांक32_t tolerance)
अणु
	uपूर्णांक32_t feedback_भागider;
	uपूर्णांक32_t fract_feedback_भागider;
	uपूर्णांक32_t actual_calculated_घड़ी_100hz;
	uपूर्णांक32_t असल_err;
	uपूर्णांक64_t actual_calc_clk_100hz;

	calculate_fb_and_fractional_fb_भागider(
			calc_pll_cs,
			pll_settings->adjusted_pix_clk_100hz,
			ref_भागider,
			post_भागider,
			&feedback_भागider,
			&fract_feedback_भागider);

	/*Actual calculated value*/
	actual_calc_clk_100hz = (uपूर्णांक64_t)feedback_भागider *
					calc_pll_cs->fract_fb_भागider_factor +
							fract_feedback_भागider;
	actual_calc_clk_100hz *= calc_pll_cs->ref_freq_khz * 10;
	actual_calc_clk_100hz =
		भाग_u64(actual_calc_clk_100hz,
			ref_भागider * post_भागider *
				calc_pll_cs->fract_fb_भागider_factor);

	actual_calculated_घड़ी_100hz = (uपूर्णांक32_t)(actual_calc_clk_100hz);

	असल_err = (actual_calculated_घड़ी_100hz >
					pll_settings->adjusted_pix_clk_100hz)
			? actual_calculated_घड़ी_100hz -
					pll_settings->adjusted_pix_clk_100hz
			: pll_settings->adjusted_pix_clk_100hz -
						actual_calculated_घड़ी_100hz;

	अगर (असल_err <= tolerance) अणु
		/*found good values*/
		pll_settings->reference_freq = calc_pll_cs->ref_freq_khz;
		pll_settings->reference_भागider = ref_भागider;
		pll_settings->feedback_भागider = feedback_भागider;
		pll_settings->fract_feedback_भागider = fract_feedback_भागider;
		pll_settings->pix_clk_post_भागider = post_भागider;
		pll_settings->calculated_pix_clk_100hz =
			actual_calculated_घड़ी_100hz;
		pll_settings->vco_freq =
			भाग_u64((u64)actual_calculated_घड़ी_100hz * post_भागider, 10);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool calc_pll_भागiders_in_range(
		काष्ठा calc_pll_घड़ी_source *calc_pll_cs,
		काष्ठा pll_settings *pll_settings,
		uपूर्णांक32_t min_ref_भागider,
		uपूर्णांक32_t max_ref_भागider,
		uपूर्णांक32_t min_post_भागider,
		uपूर्णांक32_t max_post_भागider,
		uपूर्णांक32_t err_tolerance)
अणु
	uपूर्णांक32_t ref_भागider;
	uपूर्णांक32_t post_भागider;
	uपूर्णांक32_t tolerance;

/* This is err_tolerance / 10000 = 0.0025 - acceptable error of 0.25%
 * This is errorTolerance / 10000 = 0.0001 - acceptable error of 0.01%*/
	tolerance = (pll_settings->adjusted_pix_clk_100hz * err_tolerance) /
									100000;
	अगर (tolerance < CALC_PLL_CLK_SRC_ERR_TOLERANCE)
		tolerance = CALC_PLL_CLK_SRC_ERR_TOLERANCE;

	क्रम (
			post_भागider = max_post_भागider;
			post_भागider >= min_post_भागider;
			--post_भागider) अणु
		क्रम (
				ref_भागider = min_ref_भागider;
				ref_भागider <= max_ref_भागider;
				++ref_भागider) अणु
			अगर (calc_fb_भागider_checking_tolerance(
					calc_pll_cs,
					pll_settings,
					ref_भागider,
					post_भागider,
					tolerance)) अणु
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल uपूर्णांक32_t calculate_pixel_घड़ी_pll_भागiders(
		काष्ठा calc_pll_घड़ी_source *calc_pll_cs,
		काष्ठा pll_settings *pll_settings)
अणु
	uपूर्णांक32_t err_tolerance;
	uपूर्णांक32_t min_post_भागider;
	uपूर्णांक32_t max_post_भागider;
	uपूर्णांक32_t min_ref_भागider;
	uपूर्णांक32_t max_ref_भागider;

	अगर (pll_settings->adjusted_pix_clk_100hz == 0) अणु
		DC_LOG_ERROR(
			"%s Bad requested pixel clock", __func__);
		वापस MAX_PLL_CALC_ERROR;
	पूर्ण

/* 1) Find Post भागider ranges */
	अगर (pll_settings->pix_clk_post_भागider) अणु
		min_post_भागider = pll_settings->pix_clk_post_भागider;
		max_post_भागider = pll_settings->pix_clk_post_भागider;
	पूर्ण अन्यथा अणु
		min_post_भागider = calc_pll_cs->min_pix_घड़ी_pll_post_भागider;
		अगर (min_post_भागider * pll_settings->adjusted_pix_clk_100hz <
						calc_pll_cs->min_vco_khz * 10) अणु
			min_post_भागider = calc_pll_cs->min_vco_khz * 10 /
					pll_settings->adjusted_pix_clk_100hz;
			अगर ((min_post_भागider *
					pll_settings->adjusted_pix_clk_100hz) <
						calc_pll_cs->min_vco_khz * 10)
				min_post_भागider++;
		पूर्ण

		max_post_भागider = calc_pll_cs->max_pix_घड़ी_pll_post_भागider;
		अगर (max_post_भागider * pll_settings->adjusted_pix_clk_100hz
				> calc_pll_cs->max_vco_khz * 10)
			max_post_भागider = calc_pll_cs->max_vco_khz * 10 /
					pll_settings->adjusted_pix_clk_100hz;
	पूर्ण

/* 2) Find Reference भागider ranges
 * When SS is enabled, or क्रम Display Port even without SS,
 * pll_settings->referenceDivider is not zero.
 * So calculate PPLL FB and fractional FB भागider
 * using the passed reference भागider*/

	अगर (pll_settings->reference_भागider) अणु
		min_ref_भागider = pll_settings->reference_भागider;
		max_ref_भागider = pll_settings->reference_भागider;
	पूर्ण अन्यथा अणु
		min_ref_भागider = ((calc_pll_cs->ref_freq_khz
				/ calc_pll_cs->max_pll_input_freq_khz)
				> calc_pll_cs->min_pll_ref_भागider)
			? calc_pll_cs->ref_freq_khz
					/ calc_pll_cs->max_pll_input_freq_khz
			: calc_pll_cs->min_pll_ref_भागider;

		max_ref_भागider = ((calc_pll_cs->ref_freq_khz
				/ calc_pll_cs->min_pll_input_freq_khz)
				< calc_pll_cs->max_pll_ref_भागider)
			? calc_pll_cs->ref_freq_khz /
					calc_pll_cs->min_pll_input_freq_khz
			: calc_pll_cs->max_pll_ref_भागider;
	पूर्ण

/* If some parameters are invalid we could have scenario when  "min">"max"
 * which produced endless loop later.
 * We should investigate why we get the wrong parameters.
 * But to follow the similar logic when "adjustedPixelClock" is set to be 0
 * it is better to वापस here than cause प्रणाली hang/watchकरोg समयout later.
 *  ## SVS Wed 15 Jul 2009 */

	अगर (min_post_भागider > max_post_भागider) अणु
		DC_LOG_ERROR(
			"%s Post divider range is invalid", __func__);
		वापस MAX_PLL_CALC_ERROR;
	पूर्ण

	अगर (min_ref_भागider > max_ref_भागider) अणु
		DC_LOG_ERROR(
			"%s Reference divider range is invalid", __func__);
		वापस MAX_PLL_CALC_ERROR;
	पूर्ण

/* 3) Try to find PLL भागiders given ranges
 * starting with minimal error tolerance.
 * Increase error tolerance until PLL भागiders found*/
	err_tolerance = MAX_PLL_CALC_ERROR;

	जबतक (!calc_pll_भागiders_in_range(
			calc_pll_cs,
			pll_settings,
			min_ref_भागider,
			max_ref_भागider,
			min_post_भागider,
			max_post_भागider,
			err_tolerance))
		err_tolerance += (err_tolerance > 10)
				? (err_tolerance / 10)
				: 1;

	वापस err_tolerance;
पूर्ण

अटल bool pll_adjust_pix_clk(
		काष्ठा dce110_clk_src *clk_src,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	uपूर्णांक32_t actual_pix_clk_100hz = 0;
	uपूर्णांक32_t requested_clk_100hz = 0;
	काष्ठा bp_adjust_pixel_घड़ी_parameters bp_adjust_pixel_घड़ी_params = अणु
							0 पूर्ण;
	क्रमागत bp_result bp_result;
	चयन (pix_clk_params->संकेत_type) अणु
	हाल SIGNAL_TYPE_HDMI_TYPE_A: अणु
		requested_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		अगर (pix_clk_params->pixel_encoding != PIXEL_ENCODING_YCBCR422) अणु
			चयन (pix_clk_params->color_depth) अणु
			हाल COLOR_DEPTH_101010:
				requested_clk_100hz = (requested_clk_100hz * 5) >> 2;
				अवरोध; /* x1.25*/
			हाल COLOR_DEPTH_121212:
				requested_clk_100hz = (requested_clk_100hz * 6) >> 2;
				अवरोध; /* x1.5*/
			हाल COLOR_DEPTH_161616:
				requested_clk_100hz = requested_clk_100hz * 2;
				अवरोध; /* x2.0*/
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		actual_pix_clk_100hz = requested_clk_100hz;
	पूर्ण
		अवरोध;

	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
	हाल SIGNAL_TYPE_EDP:
		requested_clk_100hz = pix_clk_params->requested_sym_clk * 10;
		actual_pix_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		अवरोध;

	शेष:
		requested_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		actual_pix_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
		अवरोध;
	पूर्ण

	bp_adjust_pixel_घड़ी_params.pixel_घड़ी = requested_clk_100hz / 10;
	bp_adjust_pixel_घड़ी_params.
		encoder_object_id = pix_clk_params->encoder_object_id;
	bp_adjust_pixel_घड़ी_params.संकेत_type = pix_clk_params->संकेत_type;
	bp_adjust_pixel_घड़ी_params.
		ss_enable = pix_clk_params->flags.ENABLE_SS;
	bp_result = clk_src->bios->funcs->adjust_pixel_घड़ी(
			clk_src->bios, &bp_adjust_pixel_घड़ी_params);
	अगर (bp_result == BP_RESULT_OK) अणु
		pll_settings->actual_pix_clk_100hz = actual_pix_clk_100hz;
		pll_settings->adjusted_pix_clk_100hz =
			bp_adjust_pixel_घड़ी_params.adjusted_pixel_घड़ी * 10;
		pll_settings->reference_भागider =
			bp_adjust_pixel_घड़ी_params.reference_भागider;
		pll_settings->pix_clk_post_भागider =
			bp_adjust_pixel_घड़ी_params.pixel_घड़ी_post_भागider;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Calculate PLL Dividers क्रम given Clock Value.
 * First will call VBIOS Adjust Exec table to check अगर requested Pixel घड़ी
 * will be Adjusted based on usage.
 * Then it will calculate PLL Dividers क्रम this Adjusted घड़ी using preferred
 * method (Maximum VCO frequency).
 *
 * \लeturn
 *     Calculation error in units of 0.01%
 */

अटल uपूर्णांक32_t dce110_get_pix_clk_भागiders_helper (
		काष्ठा dce110_clk_src *clk_src,
		काष्ठा pll_settings *pll_settings,
		काष्ठा pixel_clk_params *pix_clk_params)
अणु
	uपूर्णांक32_t field = 0;
	uपूर्णांक32_t pll_calc_error = MAX_PLL_CALC_ERROR;
	DC_LOGGER_INIT();
	/* Check अगर reference घड़ी is बाह्यal (not pcie/xtalin)
	* HW Dce80 spec:
	* 00 - PCIE_REFCLK, 01 - XTALIN,    02 - GENERICA,    03 - GENERICB
	* 04 - HSYNCA,      05 - GENLK_CLK, 06 - PCIE_REFCLK, 07 - DVOCLK0 */
	REG_GET(PLL_CNTL, PLL_REF_DIV_SRC, &field);
	pll_settings->use_बाह्यal_clk = (field > 1);

	/* VBIOS by शेष enables DP SS (spपढ़ो on IDCLK) क्रम DCE 8.0 always
	 * (we करो not care any more from SI क्रम some older DP Sink which
	 * करोes not report SS support, no known issues) */
	अगर ((pix_clk_params->flags.ENABLE_SS) ||
			(dc_is_dp_संकेत(pix_clk_params->संकेत_type))) अणु

		स्थिर काष्ठा spपढ़ो_spectrum_data *ss_data = get_ss_data_entry(
					clk_src,
					pix_clk_params->संकेत_type,
					pll_settings->adjusted_pix_clk_100hz / 10);

		अगर (शून्य != ss_data)
			pll_settings->ss_percentage = ss_data->percentage;
	पूर्ण

	/* Check VBIOS AdjustPixelClock Exec table */
	अगर (!pll_adjust_pix_clk(clk_src, pix_clk_params, pll_settings)) अणु
		/* Should never happen, ASSERT and fill up values to be able
		 * to जारी. */
		DC_LOG_ERROR(
			"%s: Failed to adjust pixel clock!!", __func__);
		pll_settings->actual_pix_clk_100hz =
				pix_clk_params->requested_pix_clk_100hz;
		pll_settings->adjusted_pix_clk_100hz =
				pix_clk_params->requested_pix_clk_100hz;

		अगर (dc_is_dp_संकेत(pix_clk_params->संकेत_type))
			pll_settings->adjusted_pix_clk_100hz = 1000000;
	पूर्ण

	/* Calculate Dividers */
	अगर (pix_clk_params->संकेत_type == SIGNAL_TYPE_HDMI_TYPE_A)
		/*Calculate Dividers by HDMI object, no SS हाल or SS हाल */
		pll_calc_error =
			calculate_pixel_घड़ी_pll_भागiders(
					&clk_src->calc_pll_hdmi,
					pll_settings);
	अन्यथा
		/*Calculate Dividers by शेष object, no SS हाल or SS हाल */
		pll_calc_error =
			calculate_pixel_घड़ी_pll_भागiders(
					&clk_src->calc_pll,
					pll_settings);

	वापस pll_calc_error;
पूर्ण

अटल व्योम dce112_get_pix_clk_भागiders_helper (
		काष्ठा dce110_clk_src *clk_src,
		काष्ठा pll_settings *pll_settings,
		काष्ठा pixel_clk_params *pix_clk_params)
अणु
	uपूर्णांक32_t actual_pixel_घड़ी_100hz;

	actual_pixel_घड़ी_100hz = pix_clk_params->requested_pix_clk_100hz;
	/* Calculate Dividers */
	अगर (pix_clk_params->संकेत_type == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		चयन (pix_clk_params->color_depth) अणु
		हाल COLOR_DEPTH_101010:
			actual_pixel_घड़ी_100hz = (actual_pixel_घड़ी_100hz * 5) >> 2;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			actual_pixel_घड़ी_100hz = (actual_pixel_घड़ी_100hz * 6) >> 2;
			अवरोध;
		हाल COLOR_DEPTH_161616:
			actual_pixel_घड़ी_100hz = actual_pixel_घड़ी_100hz * 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	pll_settings->actual_pix_clk_100hz = actual_pixel_घड़ी_100hz;
	pll_settings->adjusted_pix_clk_100hz = actual_pixel_घड़ी_100hz;
	pll_settings->calculated_pix_clk_100hz = pix_clk_params->requested_pix_clk_100hz;
पूर्ण

अटल uपूर्णांक32_t dce110_get_pix_clk_भागiders(
		काष्ठा घड़ी_source *cs,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(cs);
	uपूर्णांक32_t pll_calc_error = MAX_PLL_CALC_ERROR;
	DC_LOGGER_INIT();

	अगर (pix_clk_params == शून्य || pll_settings == शून्य
			|| pix_clk_params->requested_pix_clk_100hz == 0) अणु
		DC_LOG_ERROR(
			"%s: Invalid parameters!!\n", __func__);
		वापस pll_calc_error;
	पूर्ण

	स_रखो(pll_settings, 0, माप(*pll_settings));

	अगर (cs->id == CLOCK_SOURCE_ID_DP_DTO ||
			cs->id == CLOCK_SOURCE_ID_EXTERNAL) अणु
		pll_settings->adjusted_pix_clk_100hz = clk_src->ext_clk_khz * 10;
		pll_settings->calculated_pix_clk_100hz = clk_src->ext_clk_khz * 10;
		pll_settings->actual_pix_clk_100hz =
					pix_clk_params->requested_pix_clk_100hz;
		वापस 0;
	पूर्ण

	pll_calc_error = dce110_get_pix_clk_भागiders_helper(clk_src,
			pll_settings, pix_clk_params);

	वापस pll_calc_error;
पूर्ण

अटल uपूर्णांक32_t dce112_get_pix_clk_भागiders(
		काष्ठा घड़ी_source *cs,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(cs);
	DC_LOGGER_INIT();

	अगर (pix_clk_params == शून्य || pll_settings == शून्य
			|| pix_clk_params->requested_pix_clk_100hz == 0) अणु
		DC_LOG_ERROR(
			"%s: Invalid parameters!!\n", __func__);
		वापस -1;
	पूर्ण

	स_रखो(pll_settings, 0, माप(*pll_settings));

	अगर (cs->id == CLOCK_SOURCE_ID_DP_DTO ||
			cs->id == CLOCK_SOURCE_ID_EXTERNAL) अणु
		pll_settings->adjusted_pix_clk_100hz = clk_src->ext_clk_khz * 10;
		pll_settings->calculated_pix_clk_100hz = clk_src->ext_clk_khz * 10;
		pll_settings->actual_pix_clk_100hz =
					pix_clk_params->requested_pix_clk_100hz;
		वापस -1;
	पूर्ण

	dce112_get_pix_clk_भागiders_helper(clk_src,
			pll_settings, pix_clk_params);

	वापस 0;
पूर्ण

अटल bool disable_spपढ़ो_spectrum(काष्ठा dce110_clk_src *clk_src)
अणु
	क्रमागत bp_result result;
	काष्ठा bp_spपढ़ो_spectrum_parameters bp_ss_params = अणु0पूर्ण;

	bp_ss_params.pll_id = clk_src->base.id;

	/*Call ASICControl to process ATOMBIOS Exec table*/
	result = clk_src->bios->funcs->enable_spपढ़ो_spectrum_on_ppll(
			clk_src->bios,
			&bp_ss_params,
			false);

	वापस result == BP_RESULT_OK;
पूर्ण

अटल bool calculate_ss(
		स्थिर काष्ठा pll_settings *pll_settings,
		स्थिर काष्ठा spपढ़ो_spectrum_data *ss_data,
		काष्ठा delta_sigma_data *ds_data)
अणु
	काष्ठा fixed31_32 fb_भाग;
	काष्ठा fixed31_32 ss_amount;
	काष्ठा fixed31_32 ss_nslip_amount;
	काष्ठा fixed31_32 ss_ds_frac_amount;
	काष्ठा fixed31_32 ss_step_size;
	काष्ठा fixed31_32 modulation_समय;

	अगर (ds_data == शून्य)
		वापस false;
	अगर (ss_data == शून्य)
		वापस false;
	अगर (ss_data->percentage == 0)
		वापस false;
	अगर (pll_settings == शून्य)
		वापस false;

	स_रखो(ds_data, 0, माप(काष्ठा delta_sigma_data));

	/* compute SS_AMOUNT_FBDIV & SS_AMOUNT_NFRAC_SLIP & SS_AMOUNT_DSFRAC*/
	/* 6 decimal poपूर्णांक support in fractional feedback भागider */
	fb_भाग  = dc_fixpt_from_fraction(
		pll_settings->fract_feedback_भागider, 1000000);
	fb_भाग = dc_fixpt_add_पूर्णांक(fb_भाग, pll_settings->feedback_भागider);

	ds_data->ds_frac_amount = 0;
	/*spपढ़ोSpectrumPercentage is in the unit of .01%,
	 * so have to भागided by 100 * 100*/
	ss_amount = dc_fixpt_mul(
		fb_भाग, dc_fixpt_from_fraction(ss_data->percentage,
					100 * ss_data->percentage_भागider));
	ds_data->feedback_amount = dc_fixpt_न्यूनमान(ss_amount);

	ss_nslip_amount = dc_fixpt_sub(ss_amount,
		dc_fixpt_from_पूर्णांक(ds_data->feedback_amount));
	ss_nslip_amount = dc_fixpt_mul_पूर्णांक(ss_nslip_amount, 10);
	ds_data->nfrac_amount = dc_fixpt_न्यूनमान(ss_nslip_amount);

	ss_ds_frac_amount = dc_fixpt_sub(ss_nslip_amount,
		dc_fixpt_from_पूर्णांक(ds_data->nfrac_amount));
	ss_ds_frac_amount = dc_fixpt_mul_पूर्णांक(ss_ds_frac_amount, 65536);
	ds_data->ds_frac_amount = dc_fixpt_न्यूनमान(ss_ds_frac_amount);

	/* compute SS_STEP_SIZE_DSFRAC */
	modulation_समय = dc_fixpt_from_fraction(
		pll_settings->reference_freq * 1000,
		pll_settings->reference_भागider * ss_data->modulation_freq_hz);

	अगर (ss_data->flags.CENTER_SPREAD)
		modulation_समय = dc_fixpt_भाग_पूर्णांक(modulation_समय, 4);
	अन्यथा
		modulation_समय = dc_fixpt_भाग_पूर्णांक(modulation_समय, 2);

	ss_step_size = dc_fixpt_भाग(ss_amount, modulation_समय);
	/* SS_STEP_SIZE_DSFRAC_DEC = Int(SS_STEP_SIZE * 2 ^ 16 * 10)*/
	ss_step_size = dc_fixpt_mul_पूर्णांक(ss_step_size, 65536 * 10);
	ds_data->ds_frac_size =  dc_fixpt_न्यूनमान(ss_step_size);

	वापस true;
पूर्ण

अटल bool enable_spपढ़ो_spectrum(
		काष्ठा dce110_clk_src *clk_src,
		क्रमागत संकेत_type संकेत, काष्ठा pll_settings *pll_settings)
अणु
	काष्ठा bp_spपढ़ो_spectrum_parameters bp_params = अणु0पूर्ण;
	काष्ठा delta_sigma_data d_s_data;
	स्थिर काष्ठा spपढ़ो_spectrum_data *ss_data = शून्य;

	ss_data = get_ss_data_entry(
			clk_src,
			संकेत,
			pll_settings->calculated_pix_clk_100hz / 10);

/* Pixel घड़ी PLL has been programmed to generate desired pixel घड़ी,
 * now enable SS on pixel घड़ी */
/* TODO is it OK to वापस true not करोing anything ??*/
	अगर (ss_data != शून्य && pll_settings->ss_percentage != 0) अणु
		अगर (calculate_ss(pll_settings, ss_data, &d_s_data)) अणु
			bp_params.ds.feedback_amount =
					d_s_data.feedback_amount;
			bp_params.ds.nfrac_amount =
					d_s_data.nfrac_amount;
			bp_params.ds.ds_frac_size = d_s_data.ds_frac_size;
			bp_params.ds_frac_amount =
					d_s_data.ds_frac_amount;
			bp_params.flags.DS_TYPE = 1;
			bp_params.pll_id = clk_src->base.id;
			bp_params.percentage = ss_data->percentage;
			अगर (ss_data->flags.CENTER_SPREAD)
				bp_params.flags.CENTER_SPREAD = 1;
			अगर (ss_data->flags.EXTERNAL_SS)
				bp_params.flags.EXTERNAL_SS = 1;

			अगर (BP_RESULT_OK !=
				clk_src->bios->funcs->
					enable_spपढ़ो_spectrum_on_ppll(
							clk_src->bios,
							&bp_params,
							true))
				वापस false;
		पूर्ण अन्यथा
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम dce110_program_pixel_clk_resync(
		काष्ठा dce110_clk_src *clk_src,
		क्रमागत संकेत_type संकेत_type,
		क्रमागत dc_color_depth colordepth)
अणु
	REG_UPDATE(RESYNC_CNTL,
			DCCG_DEEP_COLOR_CNTL1, 0);
	/*
	 24 bit mode: TMDS घड़ी = 1.0 x pixel घड़ी  (1:1)
	 30 bit mode: TMDS घड़ी = 1.25 x pixel घड़ी (5:4)
	 36 bit mode: TMDS घड़ी = 1.5 x pixel घड़ी  (3:2)
	 48 bit mode: TMDS घड़ी = 2 x pixel घड़ी    (2:1)
	 */
	अगर (संकेत_type != SIGNAL_TYPE_HDMI_TYPE_A)
		वापस;

	चयन (colordepth) अणु
	हाल COLOR_DEPTH_888:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 0);
		अवरोध;
	हाल COLOR_DEPTH_101010:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 1);
		अवरोध;
	हाल COLOR_DEPTH_121212:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 2);
		अवरोध;
	हाल COLOR_DEPTH_161616:
		REG_UPDATE(RESYNC_CNTL,
				DCCG_DEEP_COLOR_CNTL1, 3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dce112_program_pixel_clk_resync(
		काष्ठा dce110_clk_src *clk_src,
		क्रमागत संकेत_type संकेत_type,
		क्रमागत dc_color_depth colordepth,
		bool enable_ycbcr420)
अणु
	uपूर्णांक32_t deep_color_cntl = 0;
	uपूर्णांक32_t द्विगुन_rate_enable = 0;

	/*
	 24 bit mode: TMDS घड़ी = 1.0 x pixel घड़ी  (1:1)
	 30 bit mode: TMDS घड़ी = 1.25 x pixel घड़ी (5:4)
	 36 bit mode: TMDS घड़ी = 1.5 x pixel घड़ी  (3:2)
	 48 bit mode: TMDS घड़ी = 2 x pixel घड़ी    (2:1)
	 */
	अगर (संकेत_type == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		द्विगुन_rate_enable = enable_ycbcr420 ? 1 : 0;

		चयन (colordepth) अणु
		हाल COLOR_DEPTH_888:
			deep_color_cntl = 0;
			अवरोध;
		हाल COLOR_DEPTH_101010:
			deep_color_cntl = 1;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			deep_color_cntl = 2;
			अवरोध;
		हाल COLOR_DEPTH_161616:
			deep_color_cntl = 3;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (clk_src->cs_mask->PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE)
		REG_UPDATE_2(PIXCLK_RESYNC_CNTL,
				PHYPLLA_DCCG_DEEP_COLOR_CNTL, deep_color_cntl,
				PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE, द्विगुन_rate_enable);
	अन्यथा
		REG_UPDATE(PIXCLK_RESYNC_CNTL,
				PHYPLLA_DCCG_DEEP_COLOR_CNTL, deep_color_cntl);

पूर्ण

अटल bool dce110_program_pix_clk(
		काष्ठा घड़ी_source *घड़ी_source,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(घड़ी_source);
	काष्ठा bp_pixel_घड़ी_parameters bp_pc_params = अणु0पूर्ण;

	/* First disable SS
	 * ATOMBIOS will enable by शेष SS on PLL क्रम DP,
	 * करो not disable it here
	 */
	अगर (घड़ी_source->id != CLOCK_SOURCE_ID_EXTERNAL &&
			!dc_is_dp_संकेत(pix_clk_params->संकेत_type) &&
			घड़ी_source->ctx->dce_version <= DCE_VERSION_11_0)
		disable_spपढ़ो_spectrum(clk_src);

	/*ATOMBIOS expects pixel rate adjusted by deep color ratio)*/
	bp_pc_params.controller_id = pix_clk_params->controller_id;
	bp_pc_params.pll_id = घड़ी_source->id;
	bp_pc_params.target_pixel_घड़ी_100hz = pll_settings->actual_pix_clk_100hz;
	bp_pc_params.encoder_object_id = pix_clk_params->encoder_object_id;
	bp_pc_params.संकेत_type = pix_clk_params->संकेत_type;

	bp_pc_params.reference_भागider = pll_settings->reference_भागider;
	bp_pc_params.feedback_भागider = pll_settings->feedback_भागider;
	bp_pc_params.fractional_feedback_भागider =
			pll_settings->fract_feedback_भागider;
	bp_pc_params.pixel_घड़ी_post_भागider =
			pll_settings->pix_clk_post_भागider;
	bp_pc_params.flags.SET_EXTERNAL_REF_DIV_SRC =
					pll_settings->use_बाह्यal_clk;

	चयन (pix_clk_params->color_depth) अणु
	हाल COLOR_DEPTH_101010:
		bp_pc_params.color_depth = TRANSMITTER_COLOR_DEPTH_30;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		bp_pc_params.color_depth = TRANSMITTER_COLOR_DEPTH_36;
		अवरोध;
	हाल COLOR_DEPTH_161616:
		bp_pc_params.color_depth = TRANSMITTER_COLOR_DEPTH_48;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (clk_src->bios->funcs->set_pixel_घड़ी(
			clk_src->bios, &bp_pc_params) != BP_RESULT_OK)
		वापस false;
	/* Enable SS
	 * ATOMBIOS will enable by शेष SS क्रम DP on PLL ( DP ID घड़ी),
	 * based on HW display PLL team, SS control settings should be programmed
	 * during PLL Reset, but they करो not have effect
	 * until SS_EN is निश्चितed.*/
	अगर (घड़ी_source->id != CLOCK_SOURCE_ID_EXTERNAL
			&& !dc_is_dp_संकेत(pix_clk_params->संकेत_type)) अणु

		अगर (pix_clk_params->flags.ENABLE_SS)
			अगर (!enable_spपढ़ो_spectrum(clk_src,
							pix_clk_params->संकेत_type,
							pll_settings))
				वापस false;

		/* Resync deep color DTO */
		dce110_program_pixel_clk_resync(clk_src,
					pix_clk_params->संकेत_type,
					pix_clk_params->color_depth);
	पूर्ण

	वापस true;
पूर्ण

अटल bool dce112_program_pix_clk(
		काष्ठा घड़ी_source *घड़ी_source,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(घड़ी_source);
	काष्ठा bp_pixel_घड़ी_parameters bp_pc_params = अणु0पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (IS_FPGA_MAXIMUS_DC(घड़ी_source->ctx->dce_environment)) अणु
		अचिन्हित पूर्णांक inst = pix_clk_params->controller_id - CONTROLLER_ID_D0;
		अचिन्हित dp_dto_ref_100hz = 7000000;
		अचिन्हित घड़ी_100hz = pll_settings->actual_pix_clk_100hz;

		/* Set DTO values: phase = target घड़ी, modulo = reference घड़ी */
		REG_WRITE(PHASE[inst], घड़ी_100hz);
		REG_WRITE(MODULO[inst], dp_dto_ref_100hz);

		/* Enable DTO */
		REG_UPDATE(PIXEL_RATE_CNTL[inst], DP_DTO0_ENABLE, 1);
		वापस true;
	पूर्ण
#पूर्ण_अगर
	/* First disable SS
	 * ATOMBIOS will enable by शेष SS on PLL क्रम DP,
	 * करो not disable it here
	 */
	अगर (घड़ी_source->id != CLOCK_SOURCE_ID_EXTERNAL &&
			!dc_is_dp_संकेत(pix_clk_params->संकेत_type) &&
			घड़ी_source->ctx->dce_version <= DCE_VERSION_11_0)
		disable_spपढ़ो_spectrum(clk_src);

	/*ATOMBIOS expects pixel rate adjusted by deep color ratio)*/
	bp_pc_params.controller_id = pix_clk_params->controller_id;
	bp_pc_params.pll_id = घड़ी_source->id;
	bp_pc_params.target_pixel_घड़ी_100hz = pll_settings->actual_pix_clk_100hz;
	bp_pc_params.encoder_object_id = pix_clk_params->encoder_object_id;
	bp_pc_params.संकेत_type = pix_clk_params->संकेत_type;

	अगर (घड़ी_source->id != CLOCK_SOURCE_ID_DP_DTO) अणु
		bp_pc_params.flags.SET_GENLOCK_REF_DIV_SRC =
						pll_settings->use_बाह्यal_clk;
		bp_pc_params.flags.SET_XTALIN_REF_SRC =
						!pll_settings->use_बाह्यal_clk;
		अगर (pix_clk_params->flags.SUPPORT_YCBCR420) अणु
			bp_pc_params.flags.SUPPORT_YUV_420 = 1;
		पूर्ण
	पूर्ण
	अगर (clk_src->bios->funcs->set_pixel_घड़ी(
			clk_src->bios, &bp_pc_params) != BP_RESULT_OK)
		वापस false;
	/* Resync deep color DTO */
	अगर (घड़ी_source->id != CLOCK_SOURCE_ID_DP_DTO)
		dce112_program_pixel_clk_resync(clk_src,
					pix_clk_params->संकेत_type,
					pix_clk_params->color_depth,
					pix_clk_params->flags.SUPPORT_YCBCR420);

	वापस true;
पूर्ण


अटल bool dce110_घड़ी_source_घातer_करोwn(
		काष्ठा घड़ी_source *clk_src)
अणु
	काष्ठा dce110_clk_src *dce110_clk_src = TO_DCE110_CLK_SRC(clk_src);
	क्रमागत bp_result bp_result;
	काष्ठा bp_pixel_घड़ी_parameters bp_pixel_घड़ी_params = अणु0पूर्ण;

	अगर (clk_src->dp_clk_src)
		वापस true;

	/* If Pixel Clock is 0 it means Power Down Pll*/
	bp_pixel_घड़ी_params.controller_id = CONTROLLER_ID_UNDEFINED;
	bp_pixel_घड़ी_params.pll_id = clk_src->id;
	bp_pixel_घड़ी_params.flags.FORCE_PROGRAMMING_OF_PLL = 1;

	/*Call ASICControl to process ATOMBIOS Exec table*/
	bp_result = dce110_clk_src->bios->funcs->set_pixel_घड़ी(
			dce110_clk_src->bios,
			&bp_pixel_घड़ी_params);

	वापस bp_result == BP_RESULT_OK;
पूर्ण

अटल bool get_pixel_clk_frequency_100hz(
		स्थिर काष्ठा घड़ी_source *घड़ी_source,
		अचिन्हित पूर्णांक inst,
		अचिन्हित पूर्णांक *pixel_clk_khz)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(घड़ी_source);
	अचिन्हित पूर्णांक घड़ी_hz = 0;
	अचिन्हित पूर्णांक modulo_hz = 0;

	अगर (घड़ी_source->id == CLOCK_SOURCE_ID_DP_DTO) अणु
		घड़ी_hz = REG_READ(PHASE[inst]);

		अगर (घड़ी_source->ctx->dc->hwss.enable_vblanks_synchronization &&
			घड़ी_source->ctx->dc->config.vblank_alignment_max_frame_समय_dअगरf > 0) अणु
			/* NOTE: In हाल VBLANK syncronization is enabled, MODULO may
			 * not be programmed equal to DPREFCLK
			 */
			modulo_hz = REG_READ(MODULO[inst]);
			*pixel_clk_khz = भाग_u64((uपूर्णांक64_t)घड़ी_hz*
				घड़ी_source->ctx->dc->clk_mgr->dprefclk_khz*10,
				modulo_hz);
		पूर्ण अन्यथा अणु
			/* NOTE: There is agreement with VBIOS here that MODULO is
			 * programmed equal to DPREFCLK, in which हाल PHASE will be
			 * equivalent to pixel घड़ी.
			 */
			*pixel_clk_khz = घड़ी_hz / 100;
		पूर्ण
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
/* this table is use to find *1.001 and /1.001 pixel rates from non-precise pixel rate */
स्थिर काष्ठा pixel_rate_range_table_entry video_optimized_pixel_rates[] = अणु
	// /1.001 rates
	अणु25170, 25180, 25200, 1000, 1001पूर्ण,	//25.2MHz   ->   25.17
	अणु59340, 59350, 59400, 1000, 1001पूर्ण,	//59.4Mhz   ->   59.340
	अणु74170, 74180, 74250, 1000, 1001पूर्ण,	//74.25Mhz  ->   74.1758
	अणु125870, 125880, 126000, 1000, 1001पूर्ण,	//126Mhz    ->  125.87
	अणु148350, 148360, 148500, 1000, 1001पूर्ण,	//148.5Mhz  ->  148.3516
	अणु167830, 167840, 168000, 1000, 1001पूर्ण,	//168Mhz    ->  167.83
	अणु222520, 222530, 222750, 1000, 1001पूर्ण,	//222.75Mhz ->  222.527
	अणु257140, 257150, 257400, 1000, 1001पूर्ण,	//257.4Mhz  ->  257.1429
	अणु296700, 296710, 297000, 1000, 1001पूर्ण,	//297Mhz    ->  296.7033
	अणु342850, 342860, 343200, 1000, 1001पूर्ण,	//343.2Mhz  ->  342.857
	अणु395600, 395610, 396000, 1000, 1001पूर्ण,	//396Mhz    ->  395.6
	अणु409090, 409100, 409500, 1000, 1001पूर्ण,	//409.5Mhz  ->  409.091
	अणु445050, 445060, 445500, 1000, 1001पूर्ण,	//445.5Mhz  ->  445.055
	अणु467530, 467540, 468000, 1000, 1001पूर्ण,	//468Mhz    ->  467.5325
	अणु519230, 519240, 519750, 1000, 1001पूर्ण,	//519.75Mhz ->  519.231
	अणु525970, 525980, 526500, 1000, 1001पूर्ण,	//526.5Mhz  ->  525.974
	अणु545450, 545460, 546000, 1000, 1001पूर्ण,	//546Mhz    ->  545.455
	अणु593400, 593410, 594000, 1000, 1001पूर्ण,	//594Mhz    ->  593.4066
	अणु623370, 623380, 624000, 1000, 1001पूर्ण,	//624Mhz    ->  623.377
	अणु692300, 692310, 693000, 1000, 1001पूर्ण,	//693Mhz    ->  692.308
	अणु701290, 701300, 702000, 1000, 1001पूर्ण,	//702Mhz    ->  701.2987
	अणु791200, 791210, 792000, 1000, 1001पूर्ण,	//792Mhz    ->  791.209
	अणु890100, 890110, 891000, 1000, 1001पूर्ण,	//891Mhz    ->  890.1099
	अणु1186810, 1186820, 1188000, 1000, 1001पूर्ण,//1188Mhz   -> 1186.8131

	// *1.001 rates
	अणु27020, 27030, 27000, 1001, 1000पूर्ण, //27Mhz
	अणु54050, 54060, 54000, 1001, 1000पूर्ण, //54Mhz
	अणु108100, 108110, 108000, 1001, 1000पूर्ण,//108Mhz
पूर्ण;

स्थिर काष्ठा pixel_rate_range_table_entry *look_up_in_video_optimized_rate_tlb(
		अचिन्हित पूर्णांक pixel_rate_khz)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ELEMENTS(video_optimized_pixel_rates); i++) अणु
		स्थिर काष्ठा pixel_rate_range_table_entry *e = &video_optimized_pixel_rates[i];

		अगर (e->range_min_khz <= pixel_rate_khz && pixel_rate_khz <= e->range_max_khz) अणु
			वापस e;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल bool dcn20_program_pix_clk(
		काष्ठा घड़ी_source *घड़ी_source,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(घड़ी_source);
	अचिन्हित पूर्णांक inst = pix_clk_params->controller_id - CONTROLLER_ID_D0;

	dce112_program_pix_clk(घड़ी_source, pix_clk_params, pll_settings);

	अगर (घड़ी_source->ctx->dc->hwss.enable_vblanks_synchronization &&
			घड़ी_source->ctx->dc->config.vblank_alignment_max_frame_समय_dअगरf > 0) अणु
		/* NOTE: In हाल VBLANK syncronization is enabled,
		 * we need to set modulo to शेष DPREFCLK first
		 * dce112_program_pix_clk करोes not set शेष DPREFCLK
		 */
		REG_WRITE(MODULO[inst],
			घड़ी_source->ctx->dc->clk_mgr->dprefclk_khz*1000);
	पूर्ण
	वापस true;
पूर्ण

अटल bool dcn20_override_dp_pix_clk(
		काष्ठा घड़ी_source *घड़ी_source,
		अचिन्हित पूर्णांक inst,
		अचिन्हित पूर्णांक pixel_clk,
		अचिन्हित पूर्णांक ref_clk)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(घड़ी_source);

	REG_UPDATE(PIXEL_RATE_CNTL[inst], DP_DTO0_ENABLE, 0);
	REG_WRITE(PHASE[inst], pixel_clk);
	REG_WRITE(MODULO[inst], ref_clk);
	REG_UPDATE(PIXEL_RATE_CNTL[inst], DP_DTO0_ENABLE, 1);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा घड़ी_source_funcs dcn20_clk_src_funcs = अणु
	.cs_घातer_करोwn = dce110_घड़ी_source_घातer_करोwn,
	.program_pix_clk = dcn20_program_pix_clk,
	.get_pix_clk_भागiders = dce112_get_pix_clk_भागiders,
	.get_pixel_clk_frequency_100hz = get_pixel_clk_frequency_100hz,
	.override_dp_pix_clk = dcn20_override_dp_pix_clk
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल bool dcn3_program_pix_clk(
		काष्ठा घड़ी_source *घड़ी_source,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	काष्ठा dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(घड़ी_source);
	अचिन्हित पूर्णांक inst = pix_clk_params->controller_id - CONTROLLER_ID_D0;
	अचिन्हित पूर्णांक dp_dto_ref_khz = घड़ी_source->ctx->dc->clk_mgr->dprefclk_khz;
	स्थिर काष्ठा pixel_rate_range_table_entry *e =
			look_up_in_video_optimized_rate_tlb(pix_clk_params->requested_pix_clk_100hz / 10);

	// For these संकेत types Driver to program DP_DTO without calling VBIOS Command table
	अगर (dc_is_dp_संकेत(pix_clk_params->संकेत_type)) अणु
		अगर (e) अणु
			/* Set DTO values: phase = target घड़ी, modulo = reference घड़ी*/
			REG_WRITE(PHASE[inst], e->target_pixel_rate_khz * e->mult_factor);
			REG_WRITE(MODULO[inst], dp_dto_ref_khz * e->भाग_factor);
		पूर्ण अन्यथा अणु
			/* Set DTO values: phase = target घड़ी, modulo = reference घड़ी*/
			REG_WRITE(PHASE[inst], pll_settings->actual_pix_clk_100hz * 100);
			REG_WRITE(MODULO[inst], dp_dto_ref_khz * 1000);
		पूर्ण
		REG_UPDATE(PIXEL_RATE_CNTL[inst], DP_DTO0_ENABLE, 1);
	पूर्ण अन्यथा
		// For other संकेत types(HDMI_TYPE_A, DVI) Driver still to call VBIOS Command table
		dce112_program_pix_clk(घड़ी_source, pix_clk_params, pll_settings);

	वापस true;
पूर्ण

अटल uपूर्णांक32_t dcn3_get_pix_clk_भागiders(
		काष्ठा घड़ी_source *cs,
		काष्ठा pixel_clk_params *pix_clk_params,
		काष्ठा pll_settings *pll_settings)
अणु
	अचिन्हित दीर्घ दीर्घ actual_pix_clk_100Hz = pix_clk_params->requested_pix_clk_100hz;
	काष्ठा dce110_clk_src *clk_src;

	clk_src = TO_DCE110_CLK_SRC(cs);
	DC_LOGGER_INIT();

	अगर (pix_clk_params == शून्य || pll_settings == शून्य
			|| pix_clk_params->requested_pix_clk_100hz == 0) अणु
		DC_LOG_ERROR(
			"%s: Invalid parameters!!\n", __func__);
		वापस -1;
	पूर्ण

	स_रखो(pll_settings, 0, माप(*pll_settings));
	/* Adjust क्रम HDMI Type A deep color */
	अगर (pix_clk_params->संकेत_type == SIGNAL_TYPE_HDMI_TYPE_A) अणु
		चयन (pix_clk_params->color_depth) अणु
		हाल COLOR_DEPTH_101010:
			actual_pix_clk_100Hz = (actual_pix_clk_100Hz * 5) >> 2;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			actual_pix_clk_100Hz = (actual_pix_clk_100Hz * 6) >> 2;
			अवरोध;
		हाल COLOR_DEPTH_161616:
			actual_pix_clk_100Hz = actual_pix_clk_100Hz * 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	pll_settings->actual_pix_clk_100hz = (अचिन्हित पूर्णांक) actual_pix_clk_100Hz;
	pll_settings->adjusted_pix_clk_100hz = (अचिन्हित पूर्णांक) actual_pix_clk_100Hz;
	pll_settings->calculated_pix_clk_100hz = (अचिन्हित पूर्णांक) actual_pix_clk_100Hz;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा घड़ी_source_funcs dcn3_clk_src_funcs = अणु
	.cs_घातer_करोwn = dce110_घड़ी_source_घातer_करोwn,
	.program_pix_clk = dcn3_program_pix_clk,
	.get_pix_clk_भागiders = dcn3_get_pix_clk_भागiders,
	.get_pixel_clk_frequency_100hz = get_pixel_clk_frequency_100hz
पूर्ण;
#पूर्ण_अगर
/*****************************************/
/* Conकाष्ठाor                           */
/*****************************************/

अटल स्थिर काष्ठा घड़ी_source_funcs dce112_clk_src_funcs = अणु
	.cs_घातer_करोwn = dce110_घड़ी_source_घातer_करोwn,
	.program_pix_clk = dce112_program_pix_clk,
	.get_pix_clk_भागiders = dce112_get_pix_clk_भागiders,
	.get_pixel_clk_frequency_100hz = get_pixel_clk_frequency_100hz
पूर्ण;
अटल स्थिर काष्ठा घड़ी_source_funcs dce110_clk_src_funcs = अणु
	.cs_घातer_करोwn = dce110_घड़ी_source_घातer_करोwn,
	.program_pix_clk = dce110_program_pix_clk,
	.get_pix_clk_भागiders = dce110_get_pix_clk_भागiders,
	.get_pixel_clk_frequency_100hz = get_pixel_clk_frequency_100hz
पूर्ण;


अटल व्योम get_ss_info_from_atombios(
		काष्ठा dce110_clk_src *clk_src,
		क्रमागत as_संकेत_type as_संकेत,
		काष्ठा spपढ़ो_spectrum_data *spपढ़ो_spectrum_data[],
		uपूर्णांक32_t *ss_entries_num)
अणु
	क्रमागत bp_result bp_result = BP_RESULT_FAILURE;
	काष्ठा spपढ़ो_spectrum_info *ss_info;
	काष्ठा spपढ़ो_spectrum_data *ss_data;
	काष्ठा spपढ़ो_spectrum_info *ss_info_cur;
	काष्ठा spपढ़ो_spectrum_data *ss_data_cur;
	uपूर्णांक32_t i;
	DC_LOGGER_INIT();
	अगर (ss_entries_num == शून्य) अणु
		DC_LOG_SYNC(
			"Invalid entry !!!\n");
		वापस;
	पूर्ण
	अगर (spपढ़ो_spectrum_data == शून्य) अणु
		DC_LOG_SYNC(
			"Invalid array pointer!!!\n");
		वापस;
	पूर्ण

	spपढ़ो_spectrum_data[0] = शून्य;
	*ss_entries_num = 0;

	*ss_entries_num = clk_src->bios->funcs->get_ss_entry_number(
			clk_src->bios,
			as_संकेत);

	अगर (*ss_entries_num == 0)
		वापस;

	ss_info = kसुस्मृति(*ss_entries_num,
			  माप(काष्ठा spपढ़ो_spectrum_info),
			  GFP_KERNEL);
	ss_info_cur = ss_info;
	अगर (ss_info == शून्य)
		वापस;

	ss_data = kसुस्मृति(*ss_entries_num,
			  माप(काष्ठा spपढ़ो_spectrum_data),
			  GFP_KERNEL);
	अगर (ss_data == शून्य)
		जाओ out_मुक्त_info;

	क्रम (i = 0, ss_info_cur = ss_info;
		i < (*ss_entries_num);
		++i, ++ss_info_cur) अणु

		bp_result = clk_src->bios->funcs->get_spपढ़ो_spectrum_info(
				clk_src->bios,
				as_संकेत,
				i,
				ss_info_cur);

		अगर (bp_result != BP_RESULT_OK)
			जाओ out_मुक्त_data;
	पूर्ण

	क्रम (i = 0, ss_info_cur = ss_info, ss_data_cur = ss_data;
		i < (*ss_entries_num);
		++i, ++ss_info_cur, ++ss_data_cur) अणु

		अगर (ss_info_cur->type.STEP_AND_DELAY_INFO != false) अणु
			DC_LOG_SYNC(
				"Invalid ATOMBIOS SS Table!!!\n");
			जाओ out_मुक्त_data;
		पूर्ण

		/* क्रम HDMI check SS percentage,
		 * अगर it is > 6 (0.06%), the ATOMBIOS table info is invalid*/
		अगर (as_संकेत == AS_SIGNAL_TYPE_HDMI
				&& ss_info_cur->spपढ़ो_spectrum_percentage > 6)अणु
			/* invalid input, करो nothing */
			DC_LOG_SYNC(
				"Invalid SS percentage ");
			DC_LOG_SYNC(
				"for HDMI in ATOMBIOS info Table!!!\n");
			जारी;
		पूर्ण
		अगर (ss_info_cur->spपढ़ो_percentage_भागider == 1000) अणु
			/* Keep previous precision from ATOMBIOS क्रम these
			* in हाल new precision set by ATOMBIOS क्रम these
			* (otherwise all code in DCE specअगरic classes
			* क्रम all previous ASICs would need
			* to be updated क्रम SS calculations,
			* Audio SS compensation and DP DTO SS compensation
			* which assumes fixed SS percentage Divider = 100)*/
			ss_info_cur->spपढ़ो_spectrum_percentage /= 10;
			ss_info_cur->spपढ़ो_percentage_भागider = 100;
		पूर्ण

		ss_data_cur->freq_range_khz = ss_info_cur->target_घड़ी_range;
		ss_data_cur->percentage =
				ss_info_cur->spपढ़ो_spectrum_percentage;
		ss_data_cur->percentage_भागider =
				ss_info_cur->spपढ़ो_percentage_भागider;
		ss_data_cur->modulation_freq_hz =
				ss_info_cur->spपढ़ो_spectrum_range;

		अगर (ss_info_cur->type.CENTER_MODE)
			ss_data_cur->flags.CENTER_SPREAD = 1;

		अगर (ss_info_cur->type.EXTERNAL)
			ss_data_cur->flags.EXTERNAL_SS = 1;

	पूर्ण

	*spपढ़ो_spectrum_data = ss_data;
	kमुक्त(ss_info);
	वापस;

out_मुक्त_data:
	kमुक्त(ss_data);
	*ss_entries_num = 0;
out_मुक्त_info:
	kमुक्त(ss_info);
पूर्ण

अटल व्योम ss_info_from_atombios_create(
	काष्ठा dce110_clk_src *clk_src)
अणु
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_DISPLAY_PORT,
		&clk_src->dp_ss_params,
		&clk_src->dp_ss_params_cnt);
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_HDMI,
		&clk_src->hdmi_ss_params,
		&clk_src->hdmi_ss_params_cnt);
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_DVI,
		&clk_src->dvi_ss_params,
		&clk_src->dvi_ss_params_cnt);
	get_ss_info_from_atombios(
		clk_src,
		AS_SIGNAL_TYPE_LVDS,
		&clk_src->lvds_ss_params,
		&clk_src->lvds_ss_params_cnt);
पूर्ण

अटल bool calc_pll_max_vco_स्थिरruct(
			काष्ठा calc_pll_घड़ी_source *calc_pll_cs,
			काष्ठा calc_pll_घड़ी_source_init_data *init_data)
अणु
	uपूर्णांक32_t i;
	काष्ठा dc_firmware_info *fw_info;
	अगर (calc_pll_cs == शून्य ||
			init_data == शून्य ||
			init_data->bp == शून्य)
		वापस false;

	अगर (!init_data->bp->fw_info_valid)
		वापस false;

	fw_info = &init_data->bp->fw_info;
	calc_pll_cs->ctx = init_data->ctx;
	calc_pll_cs->ref_freq_khz = fw_info->pll_info.crystal_frequency;
	calc_pll_cs->min_vco_khz =
			fw_info->pll_info.min_output_pxl_clk_pll_frequency;
	calc_pll_cs->max_vco_khz =
			fw_info->pll_info.max_output_pxl_clk_pll_frequency;

	अगर (init_data->max_override_input_pxl_clk_pll_freq_khz != 0)
		calc_pll_cs->max_pll_input_freq_khz =
			init_data->max_override_input_pxl_clk_pll_freq_khz;
	अन्यथा
		calc_pll_cs->max_pll_input_freq_khz =
			fw_info->pll_info.max_input_pxl_clk_pll_frequency;

	अगर (init_data->min_override_input_pxl_clk_pll_freq_khz != 0)
		calc_pll_cs->min_pll_input_freq_khz =
			init_data->min_override_input_pxl_clk_pll_freq_khz;
	अन्यथा
		calc_pll_cs->min_pll_input_freq_khz =
			fw_info->pll_info.min_input_pxl_clk_pll_frequency;

	calc_pll_cs->min_pix_घड़ी_pll_post_भागider =
			init_data->min_pix_clk_pll_post_भागider;
	calc_pll_cs->max_pix_घड़ी_pll_post_भागider =
			init_data->max_pix_clk_pll_post_भागider;
	calc_pll_cs->min_pll_ref_भागider =
			init_data->min_pll_ref_भागider;
	calc_pll_cs->max_pll_ref_भागider =
			init_data->max_pll_ref_भागider;

	अगर (init_data->num_fract_fb_भागider_decimal_poपूर्णांक == 0 ||
		init_data->num_fract_fb_भागider_decimal_poपूर्णांक_precision >
				init_data->num_fract_fb_भागider_decimal_poपूर्णांक) अणु
		DC_LOG_ERROR(
			"The dec point num or precision is incorrect!");
		वापस false;
	पूर्ण
	अगर (init_data->num_fract_fb_भागider_decimal_poपूर्णांक_precision == 0) अणु
		DC_LOG_ERROR(
			"Incorrect fract feedback divider precision num!");
		वापस false;
	पूर्ण

	calc_pll_cs->fract_fb_भागider_decimal_poपूर्णांकs_num =
				init_data->num_fract_fb_भागider_decimal_poपूर्णांक;
	calc_pll_cs->fract_fb_भागider_precision =
			init_data->num_fract_fb_भागider_decimal_poपूर्णांक_precision;
	calc_pll_cs->fract_fb_भागider_factor = 1;
	क्रम (i = 0; i < calc_pll_cs->fract_fb_भागider_decimal_poपूर्णांकs_num; ++i)
		calc_pll_cs->fract_fb_भागider_factor *= 10;

	calc_pll_cs->fract_fb_भागider_precision_factor = 1;
	क्रम (
		i = 0;
		i < (calc_pll_cs->fract_fb_भागider_decimal_poपूर्णांकs_num -
				calc_pll_cs->fract_fb_भागider_precision);
		++i)
		calc_pll_cs->fract_fb_भागider_precision_factor *= 10;

	वापस true;
पूर्ण

bool dce110_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask)
अणु
	काष्ठा calc_pll_घड़ी_source_init_data calc_pll_cs_init_data_hdmi;
	काष्ठा calc_pll_घड़ी_source_init_data calc_pll_cs_init_data;

	clk_src->base.ctx = ctx;
	clk_src->bios = bios;
	clk_src->base.id = id;
	clk_src->base.funcs = &dce110_clk_src_funcs;

	clk_src->regs = regs;
	clk_src->cs_shअगरt = cs_shअगरt;
	clk_src->cs_mask = cs_mask;

	अगर (!clk_src->bios->fw_info_valid) अणु
		ASSERT_CRITICAL(false);
		जाओ unexpected_failure;
	पूर्ण

	clk_src->ext_clk_khz = clk_src->bios->fw_info.बाह्यal_घड़ी_source_frequency_क्रम_dp;

	/* काष्ठाure normally used with PLL ranges from ATOMBIOS; DS on by शेष */
	calc_pll_cs_init_data.bp = bios;
	calc_pll_cs_init_data.min_pix_clk_pll_post_भागider = 1;
	calc_pll_cs_init_data.max_pix_clk_pll_post_भागider =
			clk_src->cs_mask->PLL_POST_DIV_PIXCLK;
	calc_pll_cs_init_data.min_pll_ref_भागider =	1;
	calc_pll_cs_init_data.max_pll_ref_भागider =	clk_src->cs_mask->PLL_REF_DIV;
	/* when 0 use minInputPxlClkPLLFrequencyInKHz from firmwareInfo*/
	calc_pll_cs_init_data.min_override_input_pxl_clk_pll_freq_khz =	0;
	/* when 0 use maxInputPxlClkPLLFrequencyInKHz from firmwareInfo*/
	calc_pll_cs_init_data.max_override_input_pxl_clk_pll_freq_khz =	0;
	/*numberOfFractFBDividerDecimalPoपूर्णांकs*/
	calc_pll_cs_init_data.num_fract_fb_भागider_decimal_poपूर्णांक =
			FRACT_FB_DIVIDER_DEC_POINTS_MAX_NUM;
	/*number of decimal poपूर्णांक to round off क्रम fractional feedback भागider value*/
	calc_pll_cs_init_data.num_fract_fb_भागider_decimal_poपूर्णांक_precision =
			FRACT_FB_DIVIDER_DEC_POINTS_MAX_NUM;
	calc_pll_cs_init_data.ctx =	ctx;

	/*काष्ठाure क्रम HDMI, no SS or SS% <= 0.06% क्रम 27 MHz Ref घड़ी */
	calc_pll_cs_init_data_hdmi.bp = bios;
	calc_pll_cs_init_data_hdmi.min_pix_clk_pll_post_भागider = 1;
	calc_pll_cs_init_data_hdmi.max_pix_clk_pll_post_भागider =
			clk_src->cs_mask->PLL_POST_DIV_PIXCLK;
	calc_pll_cs_init_data_hdmi.min_pll_ref_भागider = 1;
	calc_pll_cs_init_data_hdmi.max_pll_ref_भागider = clk_src->cs_mask->PLL_REF_DIV;
	/* when 0 use minInputPxlClkPLLFrequencyInKHz from firmwareInfo*/
	calc_pll_cs_init_data_hdmi.min_override_input_pxl_clk_pll_freq_khz = 13500;
	/* when 0 use maxInputPxlClkPLLFrequencyInKHz from firmwareInfo*/
	calc_pll_cs_init_data_hdmi.max_override_input_pxl_clk_pll_freq_khz = 27000;
	/*numberOfFractFBDividerDecimalPoपूर्णांकs*/
	calc_pll_cs_init_data_hdmi.num_fract_fb_भागider_decimal_poपूर्णांक =
			FRACT_FB_DIVIDER_DEC_POINTS_MAX_NUM;
	/*number of decimal poपूर्णांक to round off क्रम fractional feedback भागider value*/
	calc_pll_cs_init_data_hdmi.num_fract_fb_भागider_decimal_poपूर्णांक_precision =
			FRACT_FB_DIVIDER_DEC_POINTS_MAX_NUM;
	calc_pll_cs_init_data_hdmi.ctx = ctx;

	clk_src->ref_freq_khz = clk_src->bios->fw_info.pll_info.crystal_frequency;

	अगर (clk_src->base.id == CLOCK_SOURCE_ID_EXTERNAL)
		वापस true;

	/* PLL only from here on */
	ss_info_from_atombios_create(clk_src);

	अगर (!calc_pll_max_vco_स्थिरruct(
			&clk_src->calc_pll,
			&calc_pll_cs_init_data)) अणु
		ASSERT_CRITICAL(false);
		जाओ unexpected_failure;
	पूर्ण


	calc_pll_cs_init_data_hdmi.
			min_override_input_pxl_clk_pll_freq_khz = clk_src->ref_freq_khz/2;
	calc_pll_cs_init_data_hdmi.
			max_override_input_pxl_clk_pll_freq_khz = clk_src->ref_freq_khz;


	अगर (!calc_pll_max_vco_स्थिरruct(
			&clk_src->calc_pll_hdmi, &calc_pll_cs_init_data_hdmi)) अणु
		ASSERT_CRITICAL(false);
		जाओ unexpected_failure;
	पूर्ण

	वापस true;

unexpected_failure:
	वापस false;
पूर्ण

bool dce112_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask)
अणु
	clk_src->base.ctx = ctx;
	clk_src->bios = bios;
	clk_src->base.id = id;
	clk_src->base.funcs = &dce112_clk_src_funcs;

	clk_src->regs = regs;
	clk_src->cs_shअगरt = cs_shअगरt;
	clk_src->cs_mask = cs_mask;

	अगर (!clk_src->bios->fw_info_valid) अणु
		ASSERT_CRITICAL(false);
		वापस false;
	पूर्ण

	clk_src->ext_clk_khz = clk_src->bios->fw_info.बाह्यal_घड़ी_source_frequency_क्रम_dp;

	वापस true;
पूर्ण

bool dcn20_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask)
अणु
	bool ret = dce112_clk_src_स्थिरruct(clk_src, ctx, bios, id, regs, cs_shअगरt, cs_mask);

	clk_src->base.funcs = &dcn20_clk_src_funcs;

	वापस ret;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
bool dcn3_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask)
अणु
	bool ret = dce112_clk_src_स्थिरruct(clk_src, ctx, bios, id, regs, cs_shअगरt, cs_mask);

	clk_src->base.funcs = &dcn3_clk_src_funcs;

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
bool dcn301_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask)
अणु
	bool ret = dce112_clk_src_स्थिरruct(clk_src, ctx, bios, id, regs, cs_shअगरt, cs_mask);

	clk_src->base.funcs = &dcn3_clk_src_funcs;

	वापस ret;
पूर्ण
#पूर्ण_अगर
