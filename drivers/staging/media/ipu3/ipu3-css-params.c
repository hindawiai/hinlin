<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/device.h>

#समावेश "ipu3-css.h"
#समावेश "ipu3-css-fw.h"
#समावेश "ipu3-tables.h"
#समावेश "ipu3-css-params.h"

#घोषणा DIV_ROUND_CLOSEST_DOWN(a, b)	(((a) + ((b) / 2) - 1) / (b))
#घोषणा roundबंदst_करोwn(a, b)		(DIV_ROUND_CLOSEST_DOWN(a, b) * (b))

#घोषणा IPU3_UAPI_ANR_MAX_RESET		((1 << 12) - 1)
#घोषणा IPU3_UAPI_ANR_MIN_RESET		(((-1) << 12) + 1)

काष्ठा imgu_css_scaler_info अणु
	अचिन्हित पूर्णांक phase_step;	/* Same क्रम luma/chroma */
	पूर्णांक exp_shअगरt;

	अचिन्हित पूर्णांक phase_init;	/* luma/chroma dependent */
	पूर्णांक pad_left;
	पूर्णांक pad_right;
	पूर्णांक crop_left;
	पूर्णांक crop_top;
पूर्ण;

अटल अचिन्हित पूर्णांक imgu_css_scaler_get_exp(अचिन्हित पूर्णांक counter,
					    अचिन्हित पूर्णांक भागider)
अणु
	पूर्णांक i = fls(भागider) - fls(counter);

	अगर (i <= 0)
		वापस 0;

	अगर (भागider >> i < counter)
		i = i - 1;

	वापस i;
पूर्ण

/* Set up the CSS scaler look up table */
अटल व्योम
imgu_css_scaler_setup_lut(अचिन्हित पूर्णांक taps, अचिन्हित पूर्णांक input_width,
			  अचिन्हित पूर्णांक output_width, पूर्णांक phase_step_correction,
			  स्थिर पूर्णांक *coeffs, अचिन्हित पूर्णांक coeffs_size,
			  s8 coeff_lut[], काष्ठा imgu_css_scaler_info *info)
अणु
	पूर्णांक tap, phase, phase_sum_left, phase_sum_right;
	पूर्णांक exponent = imgu_css_scaler_get_exp(output_width, input_width);
	पूर्णांक mantissa = (1 << exponent) * output_width;
	अचिन्हित पूर्णांक phase_step, phase_taps;

	अगर (input_width == output_width) अणु
		क्रम (phase = 0; phase < IMGU_SCALER_PHASES; phase++) अणु
			phase_taps = phase * IMGU_SCALER_FILTER_TAPS;
			क्रम (tap = 0; tap < taps; tap++)
				coeff_lut[phase_taps + tap] = 0;
		पूर्ण

		info->phase_step = IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF);
		info->exp_shअगरt = 0;
		info->pad_left = 0;
		info->pad_right = 0;
		info->phase_init = 0;
		info->crop_left = 0;
		info->crop_top = 0;
		वापस;
	पूर्ण

	क्रम (phase = 0; phase < IMGU_SCALER_PHASES; phase++) अणु
		phase_taps = phase * IMGU_SCALER_FILTER_TAPS;
		क्रम (tap = 0; tap < taps; tap++) अणु
			/* flip table to क्रम convolution reverse indexing */
			s64 coeff = coeffs[coeffs_size -
				((tap * (coeffs_size / taps)) + phase) - 1];
			coeff *= mantissa;
			coeff = भाग64_दीर्घ(coeff, input_width);

			/* Add +"0.5" */
			coeff += 1 << (IMGU_SCALER_COEFF_BITS - 1);
			coeff >>= IMGU_SCALER_COEFF_BITS;
			coeff_lut[phase_taps + tap] = coeff;
		पूर्ण
	पूर्ण

	phase_step = IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF) *
			output_width / input_width;
	phase_step += phase_step_correction;
	phase_sum_left = (taps / 2 * IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF)) -
			(1 << (IMGU_SCALER_PHASE_COUNTER_PREC_REF - 1));
	phase_sum_right = (taps / 2 * IMGU_SCALER_PHASES *
			(1 << IMGU_SCALER_PHASE_COUNTER_PREC_REF)) +
			(1 << (IMGU_SCALER_PHASE_COUNTER_PREC_REF - 1));

	info->exp_shअगरt = IMGU_SCALER_MAX_EXPONENT_SHIFT - exponent;
	info->pad_left = (phase_sum_left % phase_step == 0) ?
		phase_sum_left / phase_step - 1 : phase_sum_left / phase_step;
	info->pad_right = (phase_sum_right % phase_step == 0) ?
		phase_sum_right / phase_step - 1 : phase_sum_right / phase_step;
	info->phase_init = phase_sum_left - phase_step * info->pad_left;
	info->phase_step = phase_step;
	info->crop_left = taps - 1;
	info->crop_top = taps - 1;
पूर्ण

/*
 * Calculates the exact output image width/height, based on phase_step setting
 * (must be perfectly aligned with hardware).
 */
अटल अचिन्हित पूर्णांक
imgu_css_scaler_calc_scaled_output(अचिन्हित पूर्णांक input,
				   काष्ठा imgu_css_scaler_info *info)
अणु
	अचिन्हित पूर्णांक arg1 = input * info->phase_step +
			(1 - IMGU_SCALER_TAPS_Y / 2) * IMGU_SCALER_FIR_PHASES -
			IMGU_SCALER_FIR_PHASES / (2 * IMGU_SCALER_PHASES);
	अचिन्हित पूर्णांक arg2 = ((IMGU_SCALER_TAPS_Y / 2) * IMGU_SCALER_FIR_PHASES +
			IMGU_SCALER_FIR_PHASES / (2 * IMGU_SCALER_PHASES)) *
			IMGU_SCALER_FIR_PHASES + info->phase_step / 2;

	वापस ((arg1 + (arg2 - IMGU_SCALER_FIR_PHASES * info->phase_step) /
		IMGU_SCALER_FIR_PHASES) / (2 * IMGU_SCALER_FIR_PHASES)) * 2;
पूर्ण

/*
 * Calculate the output width and height, given the luma
 * and chroma details of a scaler
 */
अटल व्योम
imgu_css_scaler_calc(u32 input_width, u32 input_height, u32 target_width,
		     u32 target_height, काष्ठा imgu_abi_osys_config *cfg,
		     काष्ठा imgu_css_scaler_info *info_luma,
		     काष्ठा imgu_css_scaler_info *info_chroma,
		     अचिन्हित पूर्णांक *output_width, अचिन्हित पूर्णांक *output_height,
		     अचिन्हित पूर्णांक *procmode)
अणु
	u32 out_width = target_width;
	u32 out_height = target_height;
	स्थिर अचिन्हित पूर्णांक height_alignment = 2;
	पूर्णांक phase_step_correction = -1;

	/*
	 * Calculate scaled output width. If the horizontal and vertical scaling
	 * factor is dअगरferent, then choose the biggest and crop off excess
	 * lines or columns after क्रमmatting.
	 */
	अगर (target_height * input_width > target_width * input_height)
		target_width = DIV_ROUND_UP(target_height * input_width,
					    input_height);

	अगर (input_width == target_width)
		*procmode = IMGU_ABI_OSYS_PROCMODE_BYPASS;
	अन्यथा
		*procmode = IMGU_ABI_OSYS_PROCMODE_DOWNSCALE;

	स_रखो(&cfg->scaler_coeffs_chroma, 0,
	       माप(cfg->scaler_coeffs_chroma));
	स_रखो(&cfg->scaler_coeffs_luma, 0, माप(cfg->scaler_coeffs_luma));
	करो अणु
		phase_step_correction++;

		imgu_css_scaler_setup_lut(IMGU_SCALER_TAPS_Y,
					  input_width, target_width,
					  phase_step_correction,
					  imgu_css_करोwnscale_4taps,
					  IMGU_SCALER_DOWNSCALE_4TAPS_LEN,
					  cfg->scaler_coeffs_luma, info_luma);

		imgu_css_scaler_setup_lut(IMGU_SCALER_TAPS_UV,
					  input_width, target_width,
					  phase_step_correction,
					  imgu_css_करोwnscale_2taps,
					  IMGU_SCALER_DOWNSCALE_2TAPS_LEN,
					  cfg->scaler_coeffs_chroma,
					  info_chroma);

		out_width = imgu_css_scaler_calc_scaled_output(input_width,
							       info_luma);
		out_height = imgu_css_scaler_calc_scaled_output(input_height,
								info_luma);
	पूर्ण जबतक ((out_width < target_width || out_height < target_height ||
		 !IS_ALIGNED(out_height, height_alignment)) &&
		 phase_step_correction <= 5);

	*output_width = out_width;
	*output_height = out_height;
पूर्ण

/********************** Osys routines क्रम scaler****************************/

अटल व्योम imgu_css_osys_set_क्रमmat(क्रमागत imgu_abi_frame_क्रमmat host_क्रमmat,
				     अचिन्हित पूर्णांक *osys_क्रमmat,
				     अचिन्हित पूर्णांक *osys_tiling)
अणु
	*osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_YUV420;
	*osys_tiling = IMGU_ABI_OSYS_TILING_NONE;

	चयन (host_क्रमmat) अणु
	हाल IMGU_ABI_FRAME_FORMAT_YUV420:
		*osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_YUV420;
		अवरोध;
	हाल IMGU_ABI_FRAME_FORMAT_YV12:
		*osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_YV12;
		अवरोध;
	हाल IMGU_ABI_FRAME_FORMAT_NV12:
		*osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_NV12;
		अवरोध;
	हाल IMGU_ABI_FRAME_FORMAT_NV16:
		*osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_NV16;
		अवरोध;
	हाल IMGU_ABI_FRAME_FORMAT_NV21:
		*osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_NV21;
		अवरोध;
	हाल IMGU_ABI_FRAME_FORMAT_NV12_TILEY:
		*osys_क्रमmat = IMGU_ABI_OSYS_FORMAT_NV12;
		*osys_tiling = IMGU_ABI_OSYS_TILING_Y;
		अवरोध;
	शेष:
		/* For now, assume use शेष values */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Function calculates input frame stripe offset, based
 * on output frame stripe offset and filter parameters.
 */
अटल पूर्णांक imgu_css_osys_calc_stripe_offset(पूर्णांक stripe_offset_out,
					    पूर्णांक fir_phases, पूर्णांक phase_init,
					    पूर्णांक phase_step, पूर्णांक pad_left)
अणु
	पूर्णांक stripe_offset_inp = stripe_offset_out * fir_phases -
				pad_left * phase_step;

	वापस DIV_ROUND_UP(stripe_offset_inp - phase_init, phase_step);
पूर्ण

/*
 * Calculate input frame phase, given the output frame
 * stripe offset and filter parameters
 */
अटल पूर्णांक imgu_css_osys_calc_stripe_phase_init(पूर्णांक stripe_offset_out,
						पूर्णांक fir_phases, पूर्णांक phase_init,
						पूर्णांक phase_step, पूर्णांक pad_left)
अणु
	पूर्णांक stripe_offset_inp =
		imgu_css_osys_calc_stripe_offset(stripe_offset_out,
						 fir_phases, phase_init,
						 phase_step, pad_left);

	वापस phase_init + ((pad_left + stripe_offset_inp) * phase_step) -
		stripe_offset_out * fir_phases;
पूर्ण

/*
 * This function calculates input frame stripe width,
 * based on output frame stripe offset and filter parameters
 */
अटल पूर्णांक imgu_css_osys_calc_inp_stripe_width(पूर्णांक stripe_width_out,
					       पूर्णांक fir_phases, पूर्णांक phase_init,
					       पूर्णांक phase_step, पूर्णांक fir_taps,
					       पूर्णांक pad_left, पूर्णांक pad_right)
अणु
	पूर्णांक stripe_width_inp = (stripe_width_out + fir_taps - 1) * fir_phases;

	stripe_width_inp = DIV_ROUND_UP(stripe_width_inp - phase_init,
					phase_step);

	वापस stripe_width_inp - pad_left - pad_right;
पूर्ण

/*
 * This function calculates output frame stripe width, basedi
 * on output frame stripe offset and filter parameters
 */
अटल पूर्णांक imgu_css_osys_out_stripe_width(पूर्णांक stripe_width_inp, पूर्णांक fir_phases,
					  पूर्णांक phase_init, पूर्णांक phase_step,
					  पूर्णांक fir_taps, पूर्णांक pad_left,
					  पूर्णांक pad_right, पूर्णांक column_offset)
अणु
	पूर्णांक stripe_width_out = (pad_left + stripe_width_inp +
				pad_right - column_offset) * phase_step;

	stripe_width_out = (stripe_width_out + phase_init) / fir_phases;

	वापस stripe_width_out - (fir_taps - 1);
पूर्ण

काष्ठा imgu_css_reso अणु
	अचिन्हित पूर्णांक input_width;
	अचिन्हित पूर्णांक input_height;
	क्रमागत imgu_abi_frame_क्रमmat input_क्रमmat;
	अचिन्हित पूर्णांक pin_width[IMGU_ABI_OSYS_PINS];
	अचिन्हित पूर्णांक pin_height[IMGU_ABI_OSYS_PINS];
	अचिन्हित पूर्णांक pin_stride[IMGU_ABI_OSYS_PINS];
	क्रमागत imgu_abi_frame_क्रमmat pin_क्रमmat[IMGU_ABI_OSYS_PINS];
	पूर्णांक chunk_width;
	पूर्णांक chunk_height;
	पूर्णांक block_height;
	पूर्णांक block_width;
पूर्ण;

काष्ठा imgu_css_frame_params अणु
	/* Output pins */
	अचिन्हित पूर्णांक enable;
	अचिन्हित पूर्णांक क्रमmat;
	अचिन्हित पूर्णांक flip;
	अचिन्हित पूर्णांक mirror;
	अचिन्हित पूर्णांक tiling;
	अचिन्हित पूर्णांक reduce_range;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक scaled;
	अचिन्हित पूर्णांक crop_left;
	अचिन्हित पूर्णांक crop_top;
पूर्ण;

काष्ठा imgu_css_stripe_params अणु
	अचिन्हित पूर्णांक processing_mode;
	अचिन्हित पूर्णांक phase_step;
	अचिन्हित पूर्णांक exp_shअगरt;
	अचिन्हित पूर्णांक phase_init_left_y;
	अचिन्हित पूर्णांक phase_init_left_uv;
	अचिन्हित पूर्णांक phase_init_top_y;
	अचिन्हित पूर्णांक phase_init_top_uv;
	अचिन्हित पूर्णांक pad_left_y;
	अचिन्हित पूर्णांक pad_left_uv;
	अचिन्हित पूर्णांक pad_right_y;
	अचिन्हित पूर्णांक pad_right_uv;
	अचिन्हित पूर्णांक pad_top_y;
	अचिन्हित पूर्णांक pad_top_uv;
	अचिन्हित पूर्णांक pad_bottom_y;
	अचिन्हित पूर्णांक pad_bottom_uv;
	अचिन्हित पूर्णांक crop_left_y;
	अचिन्हित पूर्णांक crop_top_y;
	अचिन्हित पूर्णांक crop_left_uv;
	अचिन्हित पूर्णांक crop_top_uv;
	अचिन्हित पूर्णांक start_column_y;
	अचिन्हित पूर्णांक start_column_uv;
	अचिन्हित पूर्णांक chunk_width;
	अचिन्हित पूर्णांक chunk_height;
	अचिन्हित पूर्णांक block_width;
	अचिन्हित पूर्णांक block_height;
	अचिन्हित पूर्णांक input_width;
	अचिन्हित पूर्णांक input_height;
	पूर्णांक output_width[IMGU_ABI_OSYS_PINS];
	पूर्णांक output_height[IMGU_ABI_OSYS_PINS];
	पूर्णांक output_offset[IMGU_ABI_OSYS_PINS];
पूर्ण;

/*
 * frame_params - size IMGU_ABI_OSYS_PINS
 * stripe_params - size IPU3_UAPI_MAX_STRIPES
 */
अटल पूर्णांक imgu_css_osys_calc_frame_and_stripe_params(
		काष्ठा imgu_css *css, अचिन्हित पूर्णांक stripes,
		काष्ठा imgu_abi_osys_config *osys,
		काष्ठा imgu_css_scaler_info *scaler_luma,
		काष्ठा imgu_css_scaler_info *scaler_chroma,
		काष्ठा imgu_css_frame_params frame_params[],
		काष्ठा imgu_css_stripe_params stripe_params[],
		अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_css_reso reso;
	अचिन्हित पूर्णांक output_width, pin, s;
	u32 input_width, input_height, target_width, target_height;
	अचिन्हित पूर्णांक procmode = 0;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	input_width = css_pipe->rect[IPU3_CSS_RECT_GDC].width;
	input_height = css_pipe->rect[IPU3_CSS_RECT_GDC].height;
	target_width = css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	target_height = css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;

	/* Frame parameters */

	/* Input width क्रम Output System is output width of DVS (with GDC) */
	reso.input_width = css_pipe->rect[IPU3_CSS_RECT_GDC].width;

	/* Input height क्रम Output System is output height of DVS (with GDC) */
	reso.input_height = css_pipe->rect[IPU3_CSS_RECT_GDC].height;

	reso.input_क्रमmat =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].css_fmt->frame_क्रमmat;

	reso.pin_width[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	reso.pin_height[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	reso.pin_stride[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].width_pad;
	reso.pin_क्रमmat[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].css_fmt->frame_क्रमmat;

	reso.pin_width[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	reso.pin_height[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	reso.pin_stride[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].width_pad;
	reso.pin_क्रमmat[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].css_fmt->frame_क्रमmat;

	/* Configure the frame parameters क्रम all output pins */

	frame_params[IMGU_ABI_OSYS_PIN_OUT].width =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	frame_params[IMGU_ABI_OSYS_PIN_OUT].height =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	frame_params[IMGU_ABI_OSYS_PIN_VF].width =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	frame_params[IMGU_ABI_OSYS_PIN_VF].height =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	frame_params[IMGU_ABI_OSYS_PIN_VF].crop_top = 0;
	frame_params[IMGU_ABI_OSYS_PIN_VF].crop_left = 0;

	क्रम (pin = 0; pin < IMGU_ABI_OSYS_PINS; pin++) अणु
		पूर्णांक enable = 0;
		पूर्णांक scaled = 0;
		अचिन्हित पूर्णांक क्रमmat = 0;
		अचिन्हित पूर्णांक tiling = 0;

		frame_params[pin].flip = 0;
		frame_params[pin].mirror = 0;
		frame_params[pin].reduce_range = 0;
		अगर (reso.pin_width[pin] != 0 && reso.pin_height[pin] != 0) अणु
			enable = 1;
			अगर (pin == IMGU_ABI_OSYS_PIN_OUT) अणु
				अगर (reso.input_width < reso.pin_width[pin] ||
				    reso.input_height < reso.pin_height[pin])
					वापस -EINVAL;
				/*
				 * When input and output resolution is
				 * dअगरferent instead of scaling, cropping
				 * should happen. Determine the crop factor
				 * to करो the symmetric cropping
				 */
				frame_params[pin].crop_left = roundबंदst_करोwn(
						(reso.input_width -
						 reso.pin_width[pin]) / 2,
						 IMGU_OSYS_DMA_CROP_W_LIMIT);
				frame_params[pin].crop_top = roundबंदst_करोwn(
						(reso.input_height -
						 reso.pin_height[pin]) / 2,
						 IMGU_OSYS_DMA_CROP_H_LIMIT);
			पूर्ण अन्यथा अणु
				अगर (reso.pin_width[pin] != reso.input_width ||
				    reso.pin_height[pin] != reso.input_height) अणु
					/*
					 * If resolution is dअगरferent at input
					 * and output of OSYS, scaling is
					 * considered except when pin is MAIN.
					 * Later it will be decide whether
					 * scaler factor is 1 or other
					 * and cropping has to be करोne or not.
					 */
					scaled = 1;
				पूर्ण
			पूर्ण
			imgu_css_osys_set_क्रमmat(reso.pin_क्रमmat[pin], &क्रमmat,
						 &tiling);
		पूर्ण अन्यथा अणु
			enable = 0;
		पूर्ण
		frame_params[pin].enable = enable;
		frame_params[pin].क्रमmat = क्रमmat;
		frame_params[pin].tiling = tiling;
		frame_params[pin].stride = reso.pin_stride[pin];
		frame_params[pin].scaled = scaled;
	पूर्ण

	imgu_css_scaler_calc(input_width, input_height, target_width,
			     target_height, osys, scaler_luma, scaler_chroma,
			     &reso.pin_width[IMGU_ABI_OSYS_PIN_VF],
			     &reso.pin_height[IMGU_ABI_OSYS_PIN_VF], &procmode);
	dev_dbg(css->dev, "osys scaler procmode is %u", procmode);
	output_width = reso.pin_width[IMGU_ABI_OSYS_PIN_VF];

	अगर (output_width < reso.input_width / 2) अणु
		/* Scaling factor <= 0.5 */
		reso.chunk_width = IMGU_OSYS_BLOCK_WIDTH;
		reso.block_width = IMGU_OSYS_BLOCK_WIDTH;
	पूर्ण अन्यथा अणु /* 0.5 <= Scaling factor <= 1.0 */
		reso.chunk_width = IMGU_OSYS_BLOCK_WIDTH / 2;
		reso.block_width = IMGU_OSYS_BLOCK_WIDTH;
	पूर्ण

	अगर (output_width <= reso.input_width * 7 / 8) अणु
		/* Scaling factor <= 0.875 */
		reso.chunk_height = IMGU_OSYS_BLOCK_HEIGHT;
		reso.block_height = IMGU_OSYS_BLOCK_HEIGHT;
	पूर्ण अन्यथा अणु /* 1.0 <= Scaling factor <= 1.75 */
		reso.chunk_height = IMGU_OSYS_BLOCK_HEIGHT / 2;
		reso.block_height = IMGU_OSYS_BLOCK_HEIGHT;
	पूर्ण

	/*
	 * Calculate scaler configuration parameters based on input and output
	 * resolution.
	 */

	अगर (frame_params[IMGU_ABI_OSYS_PIN_VF].enable) अणु
		/*
		 * When aspect ratio is dअगरferent between target resolution and
		 * required resolution, determine the crop factor to करो
		 * symmetric cropping
		 */
		u32 w = reso.pin_width[IMGU_ABI_OSYS_PIN_VF] -
			frame_params[IMGU_ABI_OSYS_PIN_VF].width;
		u32 h = reso.pin_height[IMGU_ABI_OSYS_PIN_VF] -
			frame_params[IMGU_ABI_OSYS_PIN_VF].height;

		frame_params[IMGU_ABI_OSYS_PIN_VF].crop_left =
			roundबंदst_करोwn(w / 2, IMGU_OSYS_DMA_CROP_W_LIMIT);
		frame_params[IMGU_ABI_OSYS_PIN_VF].crop_top =
			roundबंदst_करोwn(h / 2, IMGU_OSYS_DMA_CROP_H_LIMIT);

		अगर (reso.input_height % 4 || reso.input_width % 8) अणु
			dev_err(css->dev, "OSYS input width is not multiple of 8 or\n");
			dev_err(css->dev, "height is not multiple of 4\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Stripe parameters */

	अगर (frame_params[IMGU_ABI_OSYS_PIN_VF].enable) अणु
		output_width = reso.pin_width[IMGU_ABI_OSYS_PIN_VF];
	पूर्ण अन्यथा अणु
		/*
		 * in हाल scaler output is not enabled
		 * take output width as input width since
		 * there is no scaling at मुख्य pin.
		 * Due to the fact that मुख्य pin can be dअगरferent
		 * from input resolution to osys in the हाल of cropping,
		 * मुख्य pin resolution is not taken.
		 */
		output_width = reso.input_width;
	पूर्ण

	क्रम (s = 0; s < stripes; s++) अणु
		पूर्णांक stripe_offset_inp_y = 0;
		पूर्णांक stripe_offset_inp_uv = 0;
		पूर्णांक stripe_offset_out_y = 0;
		पूर्णांक stripe_offset_out_uv = 0;
		पूर्णांक stripe_phase_init_y = scaler_luma->phase_init;
		पूर्णांक stripe_phase_init_uv = scaler_chroma->phase_init;
		पूर्णांक stripe_offset_blk_y = 0;
		पूर्णांक stripe_offset_blk_uv = 0;
		पूर्णांक stripe_offset_col_y = 0;
		पूर्णांक stripe_offset_col_uv = 0;
		पूर्णांक stripe_pad_left_y = scaler_luma->pad_left;
		पूर्णांक stripe_pad_left_uv = scaler_chroma->pad_left;
		पूर्णांक stripe_pad_right_y = scaler_luma->pad_right;
		पूर्णांक stripe_pad_right_uv = scaler_chroma->pad_right;
		पूर्णांक stripe_crop_left_y = scaler_luma->crop_left;
		पूर्णांक stripe_crop_left_uv = scaler_chroma->crop_left;
		पूर्णांक stripe_input_width_y = reso.input_width;
		पूर्णांक stripe_input_width_uv = 0;
		पूर्णांक stripe_output_width_y = output_width;
		पूर्णांक stripe_output_width_uv = 0;
		पूर्णांक chunk_न्यूनमान_y = 0;
		पूर्णांक chunk_न्यूनमान_uv = 0;
		पूर्णांक chunk_उच्चमान_uv = 0;

		अगर (stripes > 1) अणु
			अगर (s > 0) अणु
				/* Calculate stripe offsets */
				stripe_offset_out_y =
					output_width * s / stripes;
				stripe_offset_out_y =
					roundकरोwn(stripe_offset_out_y,
						  IPU3_UAPI_ISP_VEC_ELEMS);
				stripe_offset_out_uv = stripe_offset_out_y /
						IMGU_LUMA_TO_CHROMA_RATIO;
				stripe_offset_inp_y =
					imgu_css_osys_calc_stripe_offset(
						stripe_offset_out_y,
						IMGU_OSYS_FIR_PHASES,
						scaler_luma->phase_init,
						scaler_luma->phase_step,
						scaler_luma->pad_left);
				stripe_offset_inp_uv =
					imgu_css_osys_calc_stripe_offset(
						stripe_offset_out_uv,
						IMGU_OSYS_FIR_PHASES,
						scaler_chroma->phase_init,
						scaler_chroma->phase_step,
						scaler_chroma->pad_left);

				/* Calculate stripe phase init */
				stripe_phase_init_y =
					imgu_css_osys_calc_stripe_phase_init(
						stripe_offset_out_y,
						IMGU_OSYS_FIR_PHASES,
						scaler_luma->phase_init,
						scaler_luma->phase_step,
						scaler_luma->pad_left);
				stripe_phase_init_uv =
					imgu_css_osys_calc_stripe_phase_init(
						stripe_offset_out_uv,
						IMGU_OSYS_FIR_PHASES,
						scaler_chroma->phase_init,
						scaler_chroma->phase_step,
						scaler_chroma->pad_left);

				/*
				 * Chunk boundary corner हाल - luma and chroma
				 * start from dअगरferent input chunks.
				 */
				chunk_न्यूनमान_y = roundकरोwn(stripe_offset_inp_y,
							  reso.chunk_width);
				chunk_न्यूनमान_uv =
					roundकरोwn(stripe_offset_inp_uv,
						  reso.chunk_width /
						  IMGU_LUMA_TO_CHROMA_RATIO);

				अगर (chunk_न्यूनमान_y != chunk_न्यूनमान_uv *
				    IMGU_LUMA_TO_CHROMA_RATIO) अणु
					/*
					 * Match starting luma/chroma chunks.
					 * Decrease offset क्रम UV and add output
					 * cropping.
					 */
					stripe_offset_inp_uv -= 1;
					stripe_crop_left_uv += 1;
					stripe_phase_init_uv -=
						scaler_luma->phase_step;
					अगर (stripe_phase_init_uv < 0)
						stripe_phase_init_uv =
							stripe_phase_init_uv +
							IMGU_OSYS_FIR_PHASES;
				पूर्ण
				/*
				 * FW workaround क्रम a HW bug: अगर the first
				 * chroma pixel is generated exactly at the end
				 * of chunck scaler HW may not output the pixel
				 * क्रम करोwnscale factors smaller than 1.5
				 * (timing issue).
				 */
				chunk_उच्चमान_uv =
					roundup(stripe_offset_inp_uv,
						reso.chunk_width /
						IMGU_LUMA_TO_CHROMA_RATIO);

				अगर (stripe_offset_inp_uv ==
				    chunk_उच्चमान_uv - IMGU_OSYS_TAPS_UV) अणु
					/*
					 * Decrease input offset and add
					 * output cropping
					 */
					stripe_offset_inp_uv -= 1;
					stripe_phase_init_uv -=
						scaler_luma->phase_step;
					अगर (stripe_phase_init_uv < 0) अणु
						stripe_phase_init_uv +=
							IMGU_OSYS_FIR_PHASES;
						stripe_crop_left_uv += 1;
					पूर्ण
				पूर्ण

				/*
				 * Calculate block and column offsets क्रम the
				 * input stripe
				 */
				stripe_offset_blk_y =
					roundकरोwn(stripe_offset_inp_y,
						  IMGU_INPUT_BLOCK_WIDTH);
				stripe_offset_blk_uv =
					roundकरोwn(stripe_offset_inp_uv,
						  IMGU_INPUT_BLOCK_WIDTH /
						  IMGU_LUMA_TO_CHROMA_RATIO);
				stripe_offset_col_y = stripe_offset_inp_y -
							stripe_offset_blk_y;
				stripe_offset_col_uv = stripe_offset_inp_uv -
							stripe_offset_blk_uv;

				/* Left padding is only क्रम the first stripe */
				stripe_pad_left_y = 0;
				stripe_pad_left_uv = 0;
			पूर्ण

			/* Right padding is only क्रम the last stripe */
			अगर (s < stripes - 1) अणु
				पूर्णांक next_offset;

				stripe_pad_right_y = 0;
				stripe_pad_right_uv = 0;

				next_offset = output_width * (s + 1) / stripes;
				next_offset = roundकरोwn(next_offset, 64);
				stripe_output_width_y = next_offset -
							stripe_offset_out_y;
			पूर्ण अन्यथा अणु
				stripe_output_width_y = output_width -
							stripe_offset_out_y;
			पूर्ण

			/* Calculate target output stripe width */
			stripe_output_width_uv = stripe_output_width_y /
						IMGU_LUMA_TO_CHROMA_RATIO;
			/* Calculate input stripe width */
			stripe_input_width_y = stripe_offset_col_y +
				imgu_css_osys_calc_inp_stripe_width(
						stripe_output_width_y,
						IMGU_OSYS_FIR_PHASES,
						stripe_phase_init_y,
						scaler_luma->phase_step,
						IMGU_OSYS_TAPS_Y,
						stripe_pad_left_y,
						stripe_pad_right_y);

			stripe_input_width_uv = stripe_offset_col_uv +
				imgu_css_osys_calc_inp_stripe_width(
						stripe_output_width_uv,
						IMGU_OSYS_FIR_PHASES,
						stripe_phase_init_uv,
						scaler_chroma->phase_step,
						IMGU_OSYS_TAPS_UV,
						stripe_pad_left_uv,
						stripe_pad_right_uv);

			stripe_input_width_uv = max(DIV_ROUND_UP(
						    stripe_input_width_y,
						    IMGU_LUMA_TO_CHROMA_RATIO),
						    stripe_input_width_uv);

			stripe_input_width_y = stripe_input_width_uv *
						IMGU_LUMA_TO_CHROMA_RATIO;

			अगर (s >= stripes - 1) अणु
				stripe_input_width_y = reso.input_width -
					stripe_offset_blk_y;
				/*
				 * The scaler requires that the last stripe
				 * spans at least two input blocks.
				 */
			पूर्ण

			/*
			 * Spec: input stripe width must be a multiple of 8.
			 * Increase the input width and recalculate the output
			 * width. This may produce an extra column of junk
			 * blocks which will be overwritten by the
			 * next stripe.
			 */
			stripe_input_width_y = ALIGN(stripe_input_width_y, 8);
			stripe_output_width_y =
				imgu_css_osys_out_stripe_width(
						stripe_input_width_y,
						IMGU_OSYS_FIR_PHASES,
						stripe_phase_init_y,
						scaler_luma->phase_step,
						IMGU_OSYS_TAPS_Y,
						stripe_pad_left_y,
						stripe_pad_right_y,
						stripe_offset_col_y);

			stripe_output_width_y =
					roundकरोwn(stripe_output_width_y,
						  IMGU_LUMA_TO_CHROMA_RATIO);
		पूर्ण
		/*
		 * Following section executes and process parameters
		 * क्रम both हालs - Striping or No Striping.
		 */
		अणु
			अचिन्हित पूर्णांक i;
			पूर्णांक pin_scale = 0;
			/*Input resolution */

			stripe_params[s].input_width = stripe_input_width_y;
			stripe_params[s].input_height = reso.input_height;

			क्रम (i = 0; i < IMGU_ABI_OSYS_PINS; i++) अणु
				अगर (frame_params[i].scaled) अणु
					/*
					 * Output stripe resolution and offset
					 * as produced by the scaler; actual
					 * output resolution may be slightly
					 * smaller.
					 */
					stripe_params[s].output_width[i] =
						stripe_output_width_y;
					stripe_params[s].output_height[i] =
						reso.pin_height[i];
					stripe_params[s].output_offset[i] =
						stripe_offset_out_y;

					pin_scale += frame_params[i].scaled;
				पूर्ण अन्यथा अणु
					/* Unscaled pin */
					stripe_params[s].output_width[i] =
						stripe_params[s].input_width;
					stripe_params[s].output_height[i] =
						stripe_params[s].input_height;
					stripe_params[s].output_offset[i] =
						stripe_offset_blk_y;
				पूर्ण
			पूर्ण

			/* If no pin use scale, we use BYPASS mode */
			stripe_params[s].processing_mode = procmode;
			stripe_params[s].phase_step = scaler_luma->phase_step;
			stripe_params[s].exp_shअगरt = scaler_luma->exp_shअगरt;
			stripe_params[s].phase_init_left_y =
				stripe_phase_init_y;
			stripe_params[s].phase_init_left_uv =
				stripe_phase_init_uv;
			stripe_params[s].phase_init_top_y =
				scaler_luma->phase_init;
			stripe_params[s].phase_init_top_uv =
				scaler_chroma->phase_init;
			stripe_params[s].pad_left_y = stripe_pad_left_y;
			stripe_params[s].pad_left_uv = stripe_pad_left_uv;
			stripe_params[s].pad_right_y = stripe_pad_right_y;
			stripe_params[s].pad_right_uv = stripe_pad_right_uv;
			stripe_params[s].pad_top_y = scaler_luma->pad_left;
			stripe_params[s].pad_top_uv = scaler_chroma->pad_left;
			stripe_params[s].pad_bottom_y = scaler_luma->pad_right;
			stripe_params[s].pad_bottom_uv =
				scaler_chroma->pad_right;
			stripe_params[s].crop_left_y = stripe_crop_left_y;
			stripe_params[s].crop_top_y = scaler_luma->crop_top;
			stripe_params[s].crop_left_uv = stripe_crop_left_uv;
			stripe_params[s].crop_top_uv = scaler_chroma->crop_top;
			stripe_params[s].start_column_y = stripe_offset_col_y;
			stripe_params[s].start_column_uv = stripe_offset_col_uv;
			stripe_params[s].chunk_width = reso.chunk_width;
			stripe_params[s].chunk_height = reso.chunk_height;
			stripe_params[s].block_width = reso.block_width;
			stripe_params[s].block_height = reso.block_height;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function configures the Output Formatter System, given the number of
 * stripes, scaler luma and chrome parameters
 */
अटल पूर्णांक imgu_css_osys_calc(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
			      अचिन्हित पूर्णांक stripes,
			      काष्ठा imgu_abi_osys_config *osys,
			      काष्ठा imgu_css_scaler_info *scaler_luma,
			      काष्ठा imgu_css_scaler_info *scaler_chroma,
			      काष्ठा imgu_abi_stripes block_stripes[])
अणु
	काष्ठा imgu_css_frame_params frame_params[IMGU_ABI_OSYS_PINS];
	काष्ठा imgu_css_stripe_params stripe_params[IPU3_UAPI_MAX_STRIPES];
	काष्ठा imgu_abi_osys_क्रमmatter_params *param;
	अचिन्हित पूर्णांक pin, s;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	स_रखो(osys, 0, माप(*osys));

	/* Compute the frame and stripe params */
	अगर (imgu_css_osys_calc_frame_and_stripe_params(css, stripes, osys,
						       scaler_luma,
						       scaler_chroma,
						       frame_params,
						       stripe_params, pipe))
		वापस -EINVAL;

	/* Output क्रमmatter प्रणाली parameters */

	क्रम (s = 0; s < stripes; s++) अणु
		काष्ठा imgu_abi_osys_scaler_params *scaler =
					&osys->scaler[s].param;
		पूर्णांक fअगरo_addr_fmt = IMGU_FIFO_ADDR_SCALER_TO_FMT;
		पूर्णांक fअगरo_addr_ack = IMGU_FIFO_ADDR_SCALER_TO_SP;

		/* OUTPUT 0 / PIN 0 is only Scaler output */
		scaler->inp_buf_y_st_addr = IMGU_VMEM1_INP_BUF_ADDR;

		/*
		 * = (IMGU_OSYS_BLOCK_WIDTH / IMGU_VMEM1_ELEMS_PER_VEC)
		 * = (2 * IPU3_UAPI_ISP_VEC_ELEMS) /
		 *   (IMGU_HIVE_OF_SYS_OF_SYSTEM_NWAYS)
		 * = 2 * 64 / 32 = 4
		 */
		scaler->inp_buf_y_line_stride = IMGU_VMEM1_Y_STRIDE;
		/*
		 * = (IMGU_VMEM1_V_OFFSET + VMEM1_uv_size)
		 * = (IMGU_VMEM1_U_OFFSET + VMEM1_uv_size) +
		 *	(VMEM1_y_size / 4)
		 * = (VMEM1_y_size) + (VMEM1_y_size / 4) +
		 * (IMGU_OSYS_BLOCK_HEIGHT * IMGU_VMEM1_Y_STRIDE)/4
		 * = (IMGU_OSYS_BLOCK_HEIGHT * IMGU_VMEM1_Y_STRIDE)
		 */
		scaler->inp_buf_y_buffer_stride = IMGU_VMEM1_BUF_SIZE;
		scaler->inp_buf_u_st_addr = IMGU_VMEM1_INP_BUF_ADDR +
						IMGU_VMEM1_U_OFFSET;
		scaler->inp_buf_v_st_addr = IMGU_VMEM1_INP_BUF_ADDR +
						IMGU_VMEM1_V_OFFSET;
		scaler->inp_buf_uv_line_stride = IMGU_VMEM1_UV_STRIDE;
		scaler->inp_buf_uv_buffer_stride = IMGU_VMEM1_BUF_SIZE;
		scaler->inp_buf_chunk_width = stripe_params[s].chunk_width;
		scaler->inp_buf_nr_buffers = IMGU_OSYS_NUM_INPUT_BUFFERS;

		/* Output buffers */
		scaler->out_buf_y_st_addr = IMGU_VMEM1_INT_BUF_ADDR;
		scaler->out_buf_y_line_stride = stripe_params[s].block_width /
						IMGU_VMEM1_ELEMS_PER_VEC;
		scaler->out_buf_y_buffer_stride = IMGU_VMEM1_BUF_SIZE;
		scaler->out_buf_u_st_addr = IMGU_VMEM1_INT_BUF_ADDR +
						IMGU_VMEM1_U_OFFSET;
		scaler->out_buf_v_st_addr = IMGU_VMEM1_INT_BUF_ADDR +
						IMGU_VMEM1_V_OFFSET;
		scaler->out_buf_uv_line_stride = stripe_params[s].block_width /
						IMGU_VMEM1_ELEMS_PER_VEC / 2;
		scaler->out_buf_uv_buffer_stride = IMGU_VMEM1_BUF_SIZE;
		scaler->out_buf_nr_buffers = IMGU_OSYS_NUM_INTERM_BUFFERS;

		/* Intermediate buffers */
		scaler->पूर्णांक_buf_y_st_addr = IMGU_VMEM2_BUF_Y_ADDR;
		scaler->पूर्णांक_buf_y_line_stride = IMGU_VMEM2_BUF_Y_STRIDE;
		scaler->पूर्णांक_buf_u_st_addr = IMGU_VMEM2_BUF_U_ADDR;
		scaler->पूर्णांक_buf_v_st_addr = IMGU_VMEM2_BUF_V_ADDR;
		scaler->पूर्णांक_buf_uv_line_stride = IMGU_VMEM2_BUF_UV_STRIDE;
		scaler->पूर्णांक_buf_height = IMGU_VMEM2_LINES_PER_BLOCK;
		scaler->पूर्णांक_buf_chunk_width = stripe_params[s].chunk_height;
		scaler->पूर्णांक_buf_chunk_height = stripe_params[s].block_width;

		/* Context buffers */
		scaler->ctx_buf_hor_y_st_addr = IMGU_VMEM3_HOR_Y_ADDR;
		scaler->ctx_buf_hor_u_st_addr = IMGU_VMEM3_HOR_U_ADDR;
		scaler->ctx_buf_hor_v_st_addr = IMGU_VMEM3_HOR_V_ADDR;
		scaler->ctx_buf_ver_y_st_addr = IMGU_VMEM3_VER_Y_ADDR;
		scaler->ctx_buf_ver_u_st_addr = IMGU_VMEM3_VER_U_ADDR;
		scaler->ctx_buf_ver_v_st_addr = IMGU_VMEM3_VER_V_ADDR;

		/* Addresses क्रम release-input and process-output tokens */
		scaler->release_inp_buf_addr = fअगरo_addr_ack;
		scaler->release_inp_buf_en = 1;
		scaler->release_out_buf_en = 1;
		scaler->process_out_buf_addr = fअगरo_addr_fmt;

		/* Settings dimensions, padding, cropping */
		scaler->input_image_y_width = stripe_params[s].input_width;
		scaler->input_image_y_height = stripe_params[s].input_height;
		scaler->input_image_y_start_column =
					stripe_params[s].start_column_y;
		scaler->input_image_uv_start_column =
					stripe_params[s].start_column_uv;
		scaler->input_image_y_left_pad = stripe_params[s].pad_left_y;
		scaler->input_image_uv_left_pad = stripe_params[s].pad_left_uv;
		scaler->input_image_y_right_pad = stripe_params[s].pad_right_y;
		scaler->input_image_uv_right_pad =
					stripe_params[s].pad_right_uv;
		scaler->input_image_y_top_pad = stripe_params[s].pad_top_y;
		scaler->input_image_uv_top_pad = stripe_params[s].pad_top_uv;
		scaler->input_image_y_bottom_pad =
					stripe_params[s].pad_bottom_y;
		scaler->input_image_uv_bottom_pad =
					stripe_params[s].pad_bottom_uv;
		scaler->processing_mode = stripe_params[s].processing_mode;
		scaler->scaling_ratio = stripe_params[s].phase_step;
		scaler->y_left_phase_init = stripe_params[s].phase_init_left_y;
		scaler->uv_left_phase_init =
					stripe_params[s].phase_init_left_uv;
		scaler->y_top_phase_init = stripe_params[s].phase_init_top_y;
		scaler->uv_top_phase_init = stripe_params[s].phase_init_top_uv;
		scaler->coeffs_exp_shअगरt = stripe_params[s].exp_shअगरt;
		scaler->out_y_left_crop = stripe_params[s].crop_left_y;
		scaler->out_uv_left_crop = stripe_params[s].crop_left_uv;
		scaler->out_y_top_crop = stripe_params[s].crop_top_y;
		scaler->out_uv_top_crop = stripe_params[s].crop_top_uv;

		क्रम (pin = 0; pin < IMGU_ABI_OSYS_PINS; pin++) अणु
			पूर्णांक in_fअगरo_addr;
			पूर्णांक out_fअगरo_addr;
			पूर्णांक block_width_vecs;
			पूर्णांक input_width_s;
			पूर्णांक input_width_vecs;
			पूर्णांक input_buf_y_st_addr;
			पूर्णांक input_buf_u_st_addr;
			पूर्णांक input_buf_v_st_addr;
			पूर्णांक input_buf_y_line_stride;
			पूर्णांक input_buf_uv_line_stride;
			पूर्णांक output_buf_y_line_stride;
			पूर्णांक output_buf_uv_line_stride;
			पूर्णांक output_buf_nr_y_lines;
			पूर्णांक block_height;
			पूर्णांक block_width;
			काष्ठा imgu_abi_osys_frame_params *fr_pr;

			fr_pr = &osys->frame[pin].param;

			/* Frame parameters */
			fr_pr->enable = frame_params[pin].enable;
			fr_pr->क्रमmat = frame_params[pin].क्रमmat;
			fr_pr->mirror = frame_params[pin].mirror;
			fr_pr->flip = frame_params[pin].flip;
			fr_pr->tiling = frame_params[pin].tiling;
			fr_pr->width = frame_params[pin].width;
			fr_pr->height = frame_params[pin].height;
			fr_pr->stride = frame_params[pin].stride;
			fr_pr->scaled = frame_params[pin].scaled;

			/* Stripe parameters */
			osys->stripe[s].crop_top[pin] =
				frame_params[pin].crop_top;
			osys->stripe[s].input_width =
				stripe_params[s].input_width;
			osys->stripe[s].input_height =
				stripe_params[s].input_height;
			osys->stripe[s].block_height =
				stripe_params[s].block_height;
			osys->stripe[s].block_width =
				stripe_params[s].block_width;
			osys->stripe[s].output_width[pin] =
				stripe_params[s].output_width[pin];
			osys->stripe[s].output_height[pin] =
				stripe_params[s].output_height[pin];

			अगर (s == 0) अणु
				/* Only first stripe should करो left cropping */
				osys->stripe[s].crop_left[pin] =
					frame_params[pin].crop_left;
				osys->stripe[s].output_offset[pin] =
					stripe_params[s].output_offset[pin];
			पूर्ण अन्यथा अणु
				/*
				 * Stripe offset क्रम other strips should be
				 * adjusted according to the cropping करोne
				 * at the first strip
				 */
				osys->stripe[s].crop_left[pin] = 0;
				osys->stripe[s].output_offset[pin] =
					(stripe_params[s].output_offset[pin] -
					 osys->stripe[0].crop_left[pin]);
			पूर्ण

			अगर (!frame_params[pin].enable)
				जारी;

			/* Formatter: configurations */

			/*
			 * Get the dimensions of the input blocks of the
			 * क्रमmatter, which is the same as the output
			 * blocks of the scaler.
			 */
			अगर (frame_params[pin].scaled) अणु
				block_height = stripe_params[s].block_height;
				block_width = stripe_params[s].block_width;
			पूर्ण अन्यथा अणु
				block_height = IMGU_OSYS_BLOCK_HEIGHT;
				block_width = IMGU_OSYS_BLOCK_WIDTH;
			पूर्ण
			block_width_vecs =
					block_width / IMGU_VMEM1_ELEMS_PER_VEC;
			/*
			 * The input/output line stride depends on the
			 * block size.
			 */
			input_buf_y_line_stride = block_width_vecs;
			input_buf_uv_line_stride = block_width_vecs / 2;
			output_buf_y_line_stride = block_width_vecs;
			output_buf_uv_line_stride = block_width_vecs / 2;
			output_buf_nr_y_lines = block_height;
			अगर (frame_params[pin].क्रमmat ==
			    IMGU_ABI_OSYS_FORMAT_NV12 ||
			    frame_params[pin].क्रमmat ==
			    IMGU_ABI_OSYS_FORMAT_NV21)
				output_buf_uv_line_stride =
					output_buf_y_line_stride;

			/*
			 * Tiled outमाला_दो use a dअगरferent output buffer
			 * configuration. The input (= scaler output) block
			 * width translates to a tile height, and the block
			 * height to the tile width. The शेष block size of
			 * 128x32 maps exactly onto a 4kB tile (512x8) क्रम Y.
			 * For UV, the tile width is always half.
			 */
			अगर (frame_params[pin].tiling) अणु
				output_buf_nr_y_lines = 8;
				output_buf_y_line_stride = 512 /
					IMGU_VMEM1_ELEMS_PER_VEC;
				output_buf_uv_line_stride = 256 /
					IMGU_VMEM1_ELEMS_PER_VEC;
			पूर्ण

			/*
			 * Store the output buffer line stride. Will be
			 * used to compute buffer offsets in boundary
			 * conditions when output blocks are partially
			 * outside the image.
			 */
			osys->stripe[s].buf_stride[pin] =
				output_buf_y_line_stride *
				IMGU_HIVE_OF_SYS_OF_SYSTEM_NWAYS;
			अगर (frame_params[pin].scaled) अणु
				/*
				 * The input buffs are the पूर्णांकermediate
				 * buffers (scalers' output)
				 */
				input_buf_y_st_addr = IMGU_VMEM1_INT_BUF_ADDR;
				input_buf_u_st_addr = IMGU_VMEM1_INT_BUF_ADDR +
							IMGU_VMEM1_U_OFFSET;
				input_buf_v_st_addr = IMGU_VMEM1_INT_BUF_ADDR +
							IMGU_VMEM1_V_OFFSET;
			पूर्ण अन्यथा अणु
				/*
				 * The input bufferss are the buffers
				 * filled by the SP
				 */
				input_buf_y_st_addr = IMGU_VMEM1_INP_BUF_ADDR;
				input_buf_u_st_addr = IMGU_VMEM1_INP_BUF_ADDR +
							IMGU_VMEM1_U_OFFSET;
				input_buf_v_st_addr = IMGU_VMEM1_INP_BUF_ADDR +
							IMGU_VMEM1_V_OFFSET;
			पूर्ण

			/*
			 * The क्रमmatter input width must be rounded to
			 * the block width. Otherwise the क्रमmatter will
			 * not recognize the end of the line, resulting
			 * in incorrect tiling (प्रणाली may hang!) and
			 * possibly other problems.
			 */
			input_width_s =
				roundup(stripe_params[s].output_width[pin],
					block_width);
			input_width_vecs = input_width_s /
					IMGU_VMEM1_ELEMS_PER_VEC;
			out_fअगरo_addr = IMGU_FIFO_ADDR_FMT_TO_SP;
			/*
			 * Process-output tokens must be sent to the SP.
			 * When scaling, the release-input tokens can be
			 * sent directly to the scaler, otherwise the
			 * क्रमmatter should send them to the SP.
			 */
			अगर (frame_params[pin].scaled)
				in_fअगरo_addr = IMGU_FIFO_ADDR_FMT_TO_SCALER;
			अन्यथा
				in_fअगरo_addr = IMGU_FIFO_ADDR_FMT_TO_SP;

			/* Formatter */
			param = &osys->क्रमmatter[s][pin].param;

			param->क्रमmat = frame_params[pin].क्रमmat;
			param->flip = frame_params[pin].flip;
			param->mirror = frame_params[pin].mirror;
			param->tiling = frame_params[pin].tiling;
			param->reduce_range = frame_params[pin].reduce_range;
			param->alpha_blending = 0;
			param->release_inp_addr = in_fअगरo_addr;
			param->release_inp_en = 1;
			param->process_out_buf_addr = out_fअगरo_addr;
			param->image_width_vecs = input_width_vecs;
			param->image_height_lines =
				stripe_params[s].output_height[pin];
			param->inp_buff_y_st_addr = input_buf_y_st_addr;
			param->inp_buff_y_line_stride = input_buf_y_line_stride;
			param->inp_buff_y_buffer_stride = IMGU_VMEM1_BUF_SIZE;
			param->पूर्णांक_buff_u_st_addr = input_buf_u_st_addr;
			param->पूर्णांक_buff_v_st_addr = input_buf_v_st_addr;
			param->inp_buff_uv_line_stride =
				input_buf_uv_line_stride;
			param->inp_buff_uv_buffer_stride = IMGU_VMEM1_BUF_SIZE;
			param->out_buff_level = 0;
			param->out_buff_nr_y_lines = output_buf_nr_y_lines;
			param->out_buff_u_st_offset = IMGU_VMEM1_U_OFFSET;
			param->out_buff_v_st_offset = IMGU_VMEM1_V_OFFSET;
			param->out_buff_y_line_stride =
				output_buf_y_line_stride;
			param->out_buff_uv_line_stride =
				output_buf_uv_line_stride;
			param->hist_buff_st_addr = IMGU_VMEM1_HST_BUF_ADDR;
			param->hist_buff_line_stride =
				IMGU_VMEM1_HST_BUF_STRIDE;
			param->hist_buff_nr_lines = IMGU_VMEM1_HST_BUF_NLINES;
		पूर्ण
	पूर्ण

	block_stripes[0].offset = 0;
	अगर (stripes <= 1) अणु
		block_stripes[0].width = stripe_params[0].input_width;
		block_stripes[0].height = stripe_params[0].input_height;
	पूर्ण अन्यथा अणु
		काष्ठा imgu_fw_info *bi =
			&css->fwp->binary_header[css_pipe->bindex];
		अचिन्हित पूर्णांक sp_block_width =
				bi->info.isp.sp.block.block_width *
				IPU3_UAPI_ISP_VEC_ELEMS;

		block_stripes[0].width = roundup(stripe_params[0].input_width,
						 sp_block_width);
		block_stripes[1].offset =
			roundकरोwn(css_pipe->rect[IPU3_CSS_RECT_GDC].width -
				  stripe_params[1].input_width, sp_block_width);
		block_stripes[1].width =
			roundup(css_pipe->rect[IPU3_CSS_RECT_GDC].width -
				block_stripes[1].offset, sp_block_width);
		block_stripes[0].height = css_pipe->rect[IPU3_CSS_RECT_GDC].height;
		block_stripes[1].height = block_stripes[0].height;
	पूर्ण

	वापस 0;
पूर्ण

/*********************** Mostly 3A operations ******************************/

/*
 * This function creates a "TO-DO list" (operations) क्रम the sp code.
 *
 * There are 2 types of operations:
 * 1. Transfer: Issue DMA transfer request क्रम copying grid cells from DDR to
 *    accelerator space (NOTE that this space is limited) associated data:
 *    DDR address + accelerator's config set index(acc's address).
 *
 * 2. Issue "Process Lines Command" to shd accelerator
 *    associated data: #पंक्तिs + which config set to use (actually, accelerator
 *    will use x AND (x+1)%num_of_sets - NOTE that this implies the restriction
 *    of not touching config sets x & (x+1)%num_of_sets when process_lines(x)
 *    is active).
 *
 * Basically there are 2 types of operations "chunks":
 * 1. "initial chunk": Initially, we करो as much transfers as we can (and need)
 *    [0 - max sets(3) ] followed by 1 or 2 "process lines" operations.
 *
 * 2. "regular chunk" - 1 transfer followed by 1 process line operation.
 *    (in some हालs we might need additional transfer ate the last chunk).
 *
 * क्रम some हाल:
 * --> init
 *	tr (0)
 *	tr (1)
 *	tr (2)
 *	pl (0)
 *	pl (1)
 * --> ack (0)
 *	tr (3)
 *	pl (2)
 * --> ack (1)
 *	pl (3)
 * --> ack (2)
 *	करो nothing
 * --> ack (3)
 *	करो nothing
 */

अटल पूर्णांक
imgu_css_shd_ops_calc(काष्ठा imgu_abi_shd_पूर्णांकra_frame_operations_data *ops,
		      स्थिर काष्ठा ipu3_uapi_shd_grid_config *grid,
		      अचिन्हित पूर्णांक image_height)
अणु
	अचिन्हित पूर्णांक block_height = 1 << grid->block_height_log2;
	अचिन्हित पूर्णांक grid_height_per_slice = grid->grid_height_per_slice;
	अचिन्हित पूर्णांक set_height = grid_height_per_slice * block_height;

	/* We currently support only असल(y_start) > grid_height_per_slice */
	अचिन्हित पूर्णांक positive_y_start = (अचिन्हित पूर्णांक)-grid->y_start;
	अचिन्हित पूर्णांक first_process_lines =
				set_height - (positive_y_start % set_height);
	अचिन्हित पूर्णांक last_set_height;
	अचिन्हित पूर्णांक num_of_sets;

	काष्ठा imgu_abi_acc_operation *p_op;
	काष्ठा imgu_abi_acc_process_lines_cmd_data *p_pl;
	काष्ठा imgu_abi_shd_transfer_luts_set_data *p_tr;

	अचिन्हित पूर्णांक op_idx, pl_idx, tr_idx;
	अचिन्हित अक्षर tr_set_num, pl_cfg_set;

	/*
	 * When the number of lines क्रम the last process lines command
	 * is equal to a set height, we need another line of grid cell -
	 * additional transfer is required.
	 */
	अचिन्हित अक्षर last_tr = 0;

	/* Add "process lines" command to the list of operations */
	bool add_pl;
	/* Add DMA xfer (config set) command to the list of ops */
	bool add_tr;

	/*
	 * Available partial grid (the part that fits पूर्णांकo #IMGU_SHD_SETS sets)
	 * करोesn't cover whole frame - need to process in chunks
	 */
	अगर (image_height > first_process_lines) अणु
		last_set_height =
			(image_height - first_process_lines) % set_height;
		num_of_sets = last_set_height > 0 ?
			(image_height - first_process_lines) / set_height + 2 :
			(image_height - first_process_lines) / set_height + 1;
		last_tr = (set_height - last_set_height <= block_height ||
			   last_set_height == 0) ? 1 : 0;
	पूर्ण अन्यथा अणु /* partial grid covers whole frame */
		last_set_height = 0;
		num_of_sets = 1;
		first_process_lines = image_height;
		last_tr = set_height - image_height <= block_height ? 1 : 0;
	पूर्ण

	/* Init operations lists and counters */
	p_op = ops->operation_list;
	op_idx = 0;
	p_pl = ops->process_lines_data;
	pl_idx = 0;
	p_tr = ops->transfer_data;
	tr_idx = 0;

	स_रखो(ops, 0, माप(*ops));

	/* Cyclic counters that holds config set number [0,IMGU_SHD_SETS) */
	tr_set_num = 0;
	pl_cfg_set = 0;

	/*
	 * Always start with a transfer - process lines command must be
	 * initiated only after appropriate config sets are in place
	 * (2 configuration sets per process line command, except क्रम last one).
	 */
	add_pl = false;
	add_tr = true;

	जबतक (add_pl || add_tr) अणु
		/* Transfer ops */
		अगर (add_tr) अणु
			अगर (op_idx >= IMGU_ABI_SHD_MAX_OPERATIONS ||
			    tr_idx >= IMGU_ABI_SHD_MAX_TRANSFERS)
				वापस -EINVAL;
			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_TRANSFER_DATA;
			p_op[op_idx].op_indicator = IMGU_ABI_ACC_OP_IDLE;
			op_idx++;
			p_tr[tr_idx].set_number = tr_set_num;
			tr_idx++;
			tr_set_num = (tr_set_num + 1) % IMGU_SHD_SETS;
		पूर्ण

		/* Process-lines ops */
		अगर (add_pl) अणु
			अगर (op_idx >= IMGU_ABI_SHD_MAX_OPERATIONS ||
			    pl_idx >= IMGU_ABI_SHD_MAX_PROCESS_LINES)
				वापस -EINVAL;
			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_PROCESS_LINES;

			/*
			 * In हाल we have 2 process lines commands -
			 * करोn't stop after the first one
			 */
			अगर (pl_idx == 0 && num_of_sets != 1)
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_IDLE;
			/*
			 * Initiate last process lines command -
			 * end of operation list.
			 */
			अन्यथा अगर (pl_idx == num_of_sets - 1)
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_OPS;
			/*
			 * Intermediate process line command - end of operation
			 * "chunk" (meaning few "transfers" followed by few
			 * "process lines" commands).
			 */
			अन्यथा
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_ACK;

			op_idx++;

			/* first process line operation */
			अगर (pl_idx == 0)
				p_pl[pl_idx].lines = first_process_lines;
			/* Last process line operation */
			अन्यथा अगर (pl_idx == num_of_sets - 1 &&
				 last_set_height > 0)
				p_pl[pl_idx].lines = last_set_height;
			अन्यथा	/* "regular" process lines operation */
				p_pl[pl_idx].lines = set_height;

			p_pl[pl_idx].cfg_set = pl_cfg_set;
			pl_idx++;
			pl_cfg_set = (pl_cfg_set + 1) % IMGU_SHD_SETS;
		पूर्ण

		/*
		 * Initially, we always transfer
		 * min(IMGU_SHD_SETS, num_of_sets) - after that we fill in the
		 * corresponding process lines commands.
		 */
		अगर (tr_idx == IMGU_SHD_SETS ||
		    tr_idx == num_of_sets + last_tr) अणु
			add_tr = false;
			add_pl = true;
		पूर्ण

		/*
		 * We have finished the "initial" operations chunk -
		 * be पढ़ोy to get more chunks.
		 */
		अगर (pl_idx == 2) अणु
			add_tr = true;
			add_pl = true;
		पूर्ण

		/* Stop conditions क्रम each operation type */
		अगर (tr_idx == num_of_sets + last_tr)
			add_tr = false;
		अगर (pl_idx == num_of_sets)
			add_pl = false;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The follow handshake procotol is the same क्रम AF, AWB and AWB FR.
 *
 * क्रम n sets of meta-data, the flow is:
 * --> init
 *  process-lines  (0)
 *  process-lines  (1)	 eoc
 *  --> ack (0)
 *  पढ़ो-meta-data (0)
 *  process-lines  (2)	 eoc
 *  --> ack (1)
 *  पढ़ो-meta-data (1)
 *  process-lines  (3)	 eoc
 *  ...
 *
 *  --> ack (n-3)
 *  पढ़ो-meta-data (n-3)
 *  process-lines  (n-1) eoc
 *  --> ack (n-2)
 *  पढ़ो-meta-data (n-2) eoc
 *  --> ack (n-1)
 *  पढ़ो-meta-data (n-1) eof
 *
 * क्रम 2 sets we get:
 * --> init
 * pl (0)
 * pl (1) eoc
 * --> ack (0)
 * pl (2) - rest of image, अगर applicable)
 * rmd (0) eoc
 * --> ack (1)
 * rmd (1) eof
 * --> (ack (2))
 * करो nothing
 *
 * क्रम only one set:
 *
 * --> init
 * pl(0)   eoc
 * --> ack (0)
 * rmd (0) eof
 *
 * grid smaller than image हाल
 * क्रम example 128x128 grid (block size 8x8, 16x16 num of blocks)
 * start at (0,0)
 * 1st set holds 160 cells - 10 blocks vertical, 16 horizontal
 * => 1st process lines = 80
 * we're left with 128-80=48 lines (6 blocks vertical)
 * => 2nd process lines = 48
 * last process lines to cover the image - image_height - 128
 *
 * --> init
 * pl (0) first
 * pl (1) last-in-grid
 * --> ack (0)
 * rmd (0)
 * pl (2) after-grid
 * --> ack (1)
 * rmd (1) eof
 * --> ack (2)
 * करो nothing
 */
काष्ठा process_lines अणु
	अचिन्हित पूर्णांक image_height;
	अचिन्हित लघु grid_height;
	अचिन्हित लघु block_height;
	अचिन्हित लघु y_start;
	अचिन्हित अक्षर grid_height_per_slice;

	अचिन्हित लघु max_op; /* max operation */
	अचिन्हित लघु max_tr; /* max transaction */
	अचिन्हित अक्षर acc_enable;
पूर्ण;

/* Helper to config पूर्णांकra_frame_operations_data. */
अटल पूर्णांक
imgu_css_acc_process_lines(स्थिर काष्ठा process_lines *pl,
			   काष्ठा imgu_abi_acc_operation *p_op,
			   काष्ठा imgu_abi_acc_process_lines_cmd_data *p_pl,
			   काष्ठा imgu_abi_acc_transfer_op_data *p_tr)
अणु
	अचिन्हित लघु op_idx = 0, pl_idx = 0, tr_idx = 0;
	अचिन्हित अक्षर tr_set_num = 0, pl_cfg_set = 0;
	स्थिर अचिन्हित लघु grid_last_line =
			pl->y_start + pl->grid_height * pl->block_height;
	स्थिर अचिन्हित लघु process_lines =
			pl->grid_height_per_slice * pl->block_height;

	अचिन्हित पूर्णांक process_lines_after_grid;
	अचिन्हित लघु first_process_lines;
	अचिन्हित लघु last_process_lines_in_grid;

	अचिन्हित लघु num_of_process_lines;
	अचिन्हित लघु num_of_sets;

	अगर (pl->grid_height_per_slice == 0)
		वापस -EINVAL;

	अगर (pl->acc_enable && grid_last_line > pl->image_height)
		वापस -EINVAL;

	num_of_sets = pl->grid_height / pl->grid_height_per_slice;
	अगर (num_of_sets * pl->grid_height_per_slice < pl->grid_height)
		num_of_sets++;

	/* Account क्रम two line delay inside the FF */
	अगर (pl->max_op == IMGU_ABI_AF_MAX_OPERATIONS) अणु
		first_process_lines = process_lines + pl->y_start + 2;
		last_process_lines_in_grid =
			(grid_last_line - first_process_lines) -
			((num_of_sets - 2) * process_lines) + 4;
		process_lines_after_grid =
			pl->image_height - grid_last_line - 4;
	पूर्ण अन्यथा अणु
		first_process_lines = process_lines + pl->y_start;
		last_process_lines_in_grid =
			(grid_last_line - first_process_lines) -
			((num_of_sets - 2) * process_lines);
		process_lines_after_grid = pl->image_height - grid_last_line;
	पूर्ण

	num_of_process_lines = num_of_sets;
	अगर (process_lines_after_grid > 0)
		num_of_process_lines++;

	जबतक (tr_idx < num_of_sets || pl_idx < num_of_process_lines) अणु
		/* Read meta-data */
		अगर (pl_idx >= 2 || (pl_idx == 1 && num_of_sets == 1)) अणु
			अगर (op_idx >= pl->max_op || tr_idx >= pl->max_tr)
				वापस -EINVAL;

			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_TRANSFER_DATA;

			अगर (tr_idx == num_of_sets - 1)
				/* The last operation is always a tr */
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_OPS;
			अन्यथा अगर (tr_idx == num_of_sets - 2)
				अगर (process_lines_after_grid == 0)
					/*
					 * No additional pl op left -
					 * this op is left as lats of cycle
					 */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_END_OF_ACK;
				अन्यथा
					/*
					 * We still have to process-lines after
					 * the grid so have one more pl op
					 */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_IDLE;
			अन्यथा
				/* Default - usually there's a pl after a tr */
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_IDLE;

			op_idx++;
			अगर (p_tr) अणु
				p_tr[tr_idx].set_number = tr_set_num;
				tr_set_num = 1 - tr_set_num;
			पूर्ण
			tr_idx++;
		पूर्ण

		/* process_lines */
		अगर (pl_idx < num_of_process_lines) अणु
			अगर (op_idx >= pl->max_op || pl_idx >= pl->max_tr)
				वापस -EINVAL;

			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_PROCESS_LINES;
			अगर (pl_idx == 0)
				अगर (num_of_process_lines == 1)
					/* Only one pl op */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_END_OF_ACK;
				अन्यथा
					/* On init - करो two pl ops */
					p_op[op_idx].op_indicator =
						IMGU_ABI_ACC_OP_IDLE;
			अन्यथा
				/* Usually pl is the end of the ack cycle */
				p_op[op_idx].op_indicator =
					IMGU_ABI_ACC_OP_END_OF_ACK;

			op_idx++;

			अगर (pl_idx == 0)
				/* First process line */
				p_pl[pl_idx].lines = first_process_lines;
			अन्यथा अगर (pl_idx == num_of_sets - 1)
				/* Last in grid */
				p_pl[pl_idx].lines = last_process_lines_in_grid;
			अन्यथा अगर (pl_idx == num_of_process_lines - 1)
				/* After the grid */
				p_pl[pl_idx].lines = process_lines_after_grid;
			अन्यथा
				/* Inside the grid */
				p_pl[pl_idx].lines = process_lines;

			अगर (p_tr) अणु
				p_pl[pl_idx].cfg_set = pl_cfg_set;
				pl_cfg_set = 1 - pl_cfg_set;
			पूर्ण
			pl_idx++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imgu_css_af_ops_calc(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
				काष्ठा imgu_abi_af_config *af_config)
अणु
	काष्ठा imgu_abi_af_पूर्णांकra_frame_operations_data *to =
		&af_config->operations_data;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];

	काष्ठा process_lines pl = अणु
		.image_height = css_pipe->rect[IPU3_CSS_RECT_BDS].height,
		.grid_height = af_config->config.grid_cfg.height,
		.block_height =
			1 << af_config->config.grid_cfg.block_height_log2,
		.y_start = af_config->config.grid_cfg.y_start &
			IPU3_UAPI_GRID_START_MASK,
		.grid_height_per_slice =
			af_config->stripes[0].grid_cfg.height_per_slice,
		.max_op = IMGU_ABI_AF_MAX_OPERATIONS,
		.max_tr = IMGU_ABI_AF_MAX_TRANSFERS,
		.acc_enable = bi->info.isp.sp.enable.af,
	पूर्ण;

	वापस imgu_css_acc_process_lines(&pl, to->ops, to->process_lines_data,
					  शून्य);
पूर्ण

अटल पूर्णांक
imgu_css_awb_fr_ops_calc(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
			 काष्ठा imgu_abi_awb_fr_config *awb_fr_config)
अणु
	काष्ठा imgu_abi_awb_fr_पूर्णांकra_frame_operations_data *to =
		&awb_fr_config->operations_data;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];
	काष्ठा process_lines pl = अणु
		.image_height = css_pipe->rect[IPU3_CSS_RECT_BDS].height,
		.grid_height = awb_fr_config->config.grid_cfg.height,
		.block_height =
			1 << awb_fr_config->config.grid_cfg.block_height_log2,
		.y_start = awb_fr_config->config.grid_cfg.y_start &
			IPU3_UAPI_GRID_START_MASK,
		.grid_height_per_slice =
			awb_fr_config->stripes[0].grid_cfg.height_per_slice,
		.max_op = IMGU_ABI_AWB_FR_MAX_OPERATIONS,
		.max_tr = IMGU_ABI_AWB_FR_MAX_PROCESS_LINES,
		.acc_enable = bi->info.isp.sp.enable.awb_fr_acc,
	पूर्ण;

	वापस imgu_css_acc_process_lines(&pl, to->ops, to->process_lines_data,
					  शून्य);
पूर्ण

अटल पूर्णांक imgu_css_awb_ops_calc(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
				 काष्ठा imgu_abi_awb_config *awb_config)
अणु
	काष्ठा imgu_abi_awb_पूर्णांकra_frame_operations_data *to =
		&awb_config->operations_data;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];

	काष्ठा process_lines pl = अणु
		.image_height = css_pipe->rect[IPU3_CSS_RECT_BDS].height,
		.grid_height = awb_config->config.grid.height,
		.block_height =
			1 << awb_config->config.grid.block_height_log2,
		.y_start = awb_config->config.grid.y_start,
		.grid_height_per_slice =
			awb_config->stripes[0].grid.height_per_slice,
		.max_op = IMGU_ABI_AWB_MAX_OPERATIONS,
		.max_tr = IMGU_ABI_AWB_MAX_TRANSFERS,
		.acc_enable = bi->info.isp.sp.enable.awb_acc,
	पूर्ण;

	वापस imgu_css_acc_process_lines(&pl, to->ops, to->process_lines_data,
					  to->transfer_data);
पूर्ण

अटल u16 imgu_css_grid_end(u16 start, u8 width, u8 block_width_log2)
अणु
	वापस (start & IPU3_UAPI_GRID_START_MASK) +
		(width << block_width_log2) - 1;
पूर्ण

अटल व्योम imgu_css_grid_end_calc(काष्ठा ipu3_uapi_grid_config *grid_cfg)
अणु
	grid_cfg->x_end = imgu_css_grid_end(grid_cfg->x_start, grid_cfg->width,
					    grid_cfg->block_width_log2);
	grid_cfg->y_end = imgu_css_grid_end(grid_cfg->y_start, grid_cfg->height,
					    grid_cfg->block_height_log2);
पूर्ण

/****************** config computation *****************************/

अटल पूर्णांक imgu_css_cfg_acc_stripe(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
				   काष्ठा imgu_abi_acc_param *acc)
अणु
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	स्थिर काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];
	काष्ठा imgu_css_scaler_info scaler_luma, scaler_chroma;
	स्थिर अचिन्हित पूर्णांक stripes = bi->info.isp.sp.iterator.num_stripes;
	स्थिर अचिन्हित पूर्णांक f = IPU3_UAPI_ISP_VEC_ELEMS * 2;
	अचिन्हित पूर्णांक bds_ds, i;

	स_रखो(acc, 0, माप(*acc));

	/* acc_param: osys_config */

	अगर (imgu_css_osys_calc(css, pipe, stripes, &acc->osys, &scaler_luma,
			       &scaler_chroma, acc->stripe.block_stripes))
		वापस -EINVAL;

	/* acc_param: stripe data */

	/*
	 * For the striped हाल the approach is as follows:
	 * 1. करोwn-scaled stripes are calculated - with 128 overlap
	 *    (this is the मुख्य limiter thereक्रमe it's first)
	 * 2. input stripes are derived by up-scaling the करोwn-scaled stripes
	 *    (there are no alignment requirements on input stripes)
	 * 3. output stripes are derived from करोwn-scaled stripes too
	 */

	acc->stripe.num_of_stripes = stripes;
	acc->stripe.input_frame.width =
		css_pipe->queue[IPU3_CSS_QUEUE_IN].fmt.mpix.width;
	acc->stripe.input_frame.height =
		css_pipe->queue[IPU3_CSS_QUEUE_IN].fmt.mpix.height;
	acc->stripe.input_frame.bayer_order =
		css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayer_order;

	क्रम (i = 0; i < stripes; i++)
		acc->stripe.bds_out_stripes[i].height =
					css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	acc->stripe.bds_out_stripes[0].offset = 0;
	अगर (stripes <= 1) अणु
		acc->stripe.bds_out_stripes[0].width =
			ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width, f);
	पूर्ण अन्यथा अणु
		/* Image processing is भागided पूर्णांकo two stripes */
		acc->stripe.bds_out_stripes[0].width =
			acc->stripe.bds_out_stripes[1].width =
			(css_pipe->rect[IPU3_CSS_RECT_BDS].width / 2 & ~(f - 1)) + f;
		/*
		 * Sum of width of the two stripes should not be smaller
		 * than output width and must be even बार of overlapping
		 * unit f.
		 */
		अगर ((css_pipe->rect[IPU3_CSS_RECT_BDS].width / f & 1) !=
		    !!(css_pipe->rect[IPU3_CSS_RECT_BDS].width & (f - 1)))
			acc->stripe.bds_out_stripes[0].width += f;
		अगर ((css_pipe->rect[IPU3_CSS_RECT_BDS].width / f & 1) &&
		    (css_pipe->rect[IPU3_CSS_RECT_BDS].width & (f - 1))) अणु
			acc->stripe.bds_out_stripes[0].width += f;
			acc->stripe.bds_out_stripes[1].width += f;
		पूर्ण
		/* Overlap between stripes is IPU3_UAPI_ISP_VEC_ELEMS * 4 */
		acc->stripe.bds_out_stripes[1].offset =
			acc->stripe.bds_out_stripes[0].width - 2 * f;
	पूर्ण

	acc->stripe.effective_stripes[0].height =
				css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].height;
	acc->stripe.effective_stripes[0].offset = 0;
	acc->stripe.bds_out_stripes_no_overlap[0].height =
				css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	acc->stripe.bds_out_stripes_no_overlap[0].offset = 0;
	acc->stripe.output_stripes[0].height =
				css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	acc->stripe.output_stripes[0].offset = 0;
	अगर (stripes <= 1) अणु
		acc->stripe.करोwn_scaled_stripes[0].width =
				css_pipe->rect[IPU3_CSS_RECT_BDS].width;
		acc->stripe.करोwn_scaled_stripes[0].height =
				css_pipe->rect[IPU3_CSS_RECT_BDS].height;
		acc->stripe.करोwn_scaled_stripes[0].offset = 0;

		acc->stripe.effective_stripes[0].width =
				css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].width;
		acc->stripe.bds_out_stripes_no_overlap[0].width =
			ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width, f);

		acc->stripe.output_stripes[0].width =
			css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	पूर्ण अन्यथा अणु /* Two stripes */
		bds_ds = css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].width *
				IMGU_BDS_GRANULARITY /
				css_pipe->rect[IPU3_CSS_RECT_BDS].width;

		acc->stripe.करोwn_scaled_stripes[0] =
			acc->stripe.bds_out_stripes[0];
		acc->stripe.करोwn_scaled_stripes[1] =
			acc->stripe.bds_out_stripes[1];
		अगर (!IS_ALIGNED(css_pipe->rect[IPU3_CSS_RECT_BDS].width, f))
			acc->stripe.करोwn_scaled_stripes[1].width +=
				(css_pipe->rect[IPU3_CSS_RECT_BDS].width
				& (f - 1)) - f;

		acc->stripe.effective_stripes[0].width = bds_ds *
			acc->stripe.करोwn_scaled_stripes[0].width /
			IMGU_BDS_GRANULARITY;
		acc->stripe.effective_stripes[1].width = bds_ds *
			acc->stripe.करोwn_scaled_stripes[1].width /
			IMGU_BDS_GRANULARITY;
		acc->stripe.effective_stripes[1].height =
			css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].height;
		acc->stripe.effective_stripes[1].offset = bds_ds *
			acc->stripe.करोwn_scaled_stripes[1].offset /
			IMGU_BDS_GRANULARITY;

		acc->stripe.bds_out_stripes_no_overlap[0].width =
		acc->stripe.bds_out_stripes_no_overlap[1].offset =
			ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width, 2 * f) / 2;
		acc->stripe.bds_out_stripes_no_overlap[1].width =
			DIV_ROUND_UP(css_pipe->rect[IPU3_CSS_RECT_BDS].width, f)
			/ 2 * f;
		acc->stripe.bds_out_stripes_no_overlap[1].height =
			css_pipe->rect[IPU3_CSS_RECT_BDS].height;

		acc->stripe.output_stripes[0].width =
			acc->stripe.करोwn_scaled_stripes[0].width - f;
		acc->stripe.output_stripes[1].width =
			acc->stripe.करोwn_scaled_stripes[1].width - f;
		acc->stripe.output_stripes[1].height =
			css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
		acc->stripe.output_stripes[1].offset =
			acc->stripe.output_stripes[0].width;
	पूर्ण

	acc->stripe.output_प्रणाली_in_frame_width =
		css_pipe->rect[IPU3_CSS_RECT_GDC].width;
	acc->stripe.output_प्रणाली_in_frame_height =
		css_pipe->rect[IPU3_CSS_RECT_GDC].height;

	acc->stripe.effective_frame_width =
				css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].width;
	acc->stripe.bds_frame_width = css_pipe->rect[IPU3_CSS_RECT_BDS].width;
	acc->stripe.out_frame_width =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	acc->stripe.out_frame_height =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	acc->stripe.gdc_in_buffer_width =
		css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperline /
		css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].bytesperpixel;
	acc->stripe.gdc_in_buffer_height =
		css_pipe->aux_frames[IPU3_CSS_AUX_FRAME_REF].height;
	acc->stripe.gdc_in_buffer_offset_x = IMGU_GDC_BUF_X;
	acc->stripe.gdc_in_buffer_offset_y = IMGU_GDC_BUF_Y;
	acc->stripe.display_frame_width =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	acc->stripe.display_frame_height =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	acc->stripe.bds_aligned_frame_width =
		roundup(css_pipe->rect[IPU3_CSS_RECT_BDS].width,
			2 * IPU3_UAPI_ISP_VEC_ELEMS);

	अगर (stripes > 1)
		acc->stripe.half_overlap_vectors =
			IMGU_STRIPE_FIXED_HALF_OVERLAP;
	अन्यथा
		acc->stripe.half_overlap_vectors = 0;

	वापस 0;
पूर्ण

अटल व्योम imgu_css_cfg_acc_dvs(काष्ठा imgu_css *css,
				 काष्ठा imgu_abi_acc_param *acc,
				 अचिन्हित पूर्णांक pipe)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	/* Disable DVS statistics */
	acc->dvs_stat.operations_data.process_lines_data[0].lines =
				css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	acc->dvs_stat.operations_data.process_lines_data[0].cfg_set = 0;
	acc->dvs_stat.operations_data.ops[0].op_type =
		IMGU_ABI_ACC_OPTYPE_PROCESS_LINES;
	acc->dvs_stat.operations_data.ops[0].op_indicator =
		IMGU_ABI_ACC_OP_NO_OPS;
	क्रम (i = 0; i < IMGU_ABI_DVS_STAT_LEVELS; i++)
		acc->dvs_stat.cfg.grd_config[i].enable = 0;
पूर्ण

अटल व्योम acc_bds_per_stripe_data(काष्ठा imgu_css *css,
				    काष्ठा imgu_abi_acc_param *acc,
				    स्थिर पूर्णांक i, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];

	acc->bds.per_stripe.aligned_data[i].data.crop.hor_crop_en = 0;
	acc->bds.per_stripe.aligned_data[i].data.crop.hor_crop_start = 0;
	acc->bds.per_stripe.aligned_data[i].data.crop.hor_crop_end = 0;
	acc->bds.per_stripe.aligned_data[i].data.hor_ctrl0 =
		acc->bds.hor.hor_ctrl0;
	acc->bds.per_stripe.aligned_data[i].data.hor_ctrl0.out_frame_width =
		acc->stripe.करोwn_scaled_stripes[i].width;
	acc->bds.per_stripe.aligned_data[i].data.ver_ctrl1.out_frame_width =
		acc->stripe.करोwn_scaled_stripes[i].width;
	acc->bds.per_stripe.aligned_data[i].data.ver_ctrl1.out_frame_height =
		css_pipe->rect[IPU3_CSS_RECT_BDS].height;
पूर्ण

/*
 * Configure `acc' parameters. `acc_old' contains the old values (or is शून्य)
 * and `acc_user' contains new prospective values. `use' contains flags
 * telling which fields to take from the old values (or generate अगर it is शून्य)
 * and which to take from the new user values.
 */
पूर्णांक imgu_css_cfg_acc(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		     काष्ठा ipu3_uapi_flags *use,
		     काष्ठा imgu_abi_acc_param *acc,
		     काष्ठा imgu_abi_acc_param *acc_old,
		     काष्ठा ipu3_uapi_acc_param *acc_user)
अणु
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	स्थिर काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];
	स्थिर अचिन्हित पूर्णांक stripes = bi->info.isp.sp.iterator.num_stripes;
	स्थिर अचिन्हित पूर्णांक tnr_frame_width =
		acc->stripe.bds_aligned_frame_width;
	स्थिर अचिन्हित पूर्णांक min_overlap = 10;
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *pixm =
		&css_pipe->queue[IPU3_CSS_QUEUE_IN].fmt.mpix;
	स्थिर काष्ठा imgu_css_bds_config *cfg_bds;
	काष्ठा imgu_abi_input_feeder_data *feeder_data;

	अचिन्हित पूर्णांक bds_ds, ofs_x, ofs_y, i, width, height;
	u8 b_w_log2; /* Block width log2 */

	/* Update stripe using chroma and luma */

	अगर (imgu_css_cfg_acc_stripe(css, pipe, acc))
		वापस -EINVAL;

	/* acc_param: input_feeder_config */

	ofs_x = ((pixm->width -
		  css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].width) >> 1) & ~1;
	ofs_x += css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayer_order ==
		IMGU_ABI_BAYER_ORDER_RGGB ||
		css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayer_order ==
		IMGU_ABI_BAYER_ORDER_GBRG ? 1 : 0;
	ofs_y = ((pixm->height -
		  css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].height) >> 1) & ~1;
	ofs_y += css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayer_order ==
		IMGU_ABI_BAYER_ORDER_BGGR ||
		css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayer_order ==
		IMGU_ABI_BAYER_ORDER_GBRG ? 1 : 0;
	acc->input_feeder.data.row_stride = pixm->plane_fmt[0].bytesperline;
	acc->input_feeder.data.start_row_address =
		ofs_x / IMGU_PIXELS_PER_WORD * IMGU_BYTES_PER_WORD +
		ofs_y * acc->input_feeder.data.row_stride;
	acc->input_feeder.data.start_pixel = ofs_x % IMGU_PIXELS_PER_WORD;

	acc->input_feeder.data_per_stripe.input_feeder_data[0].data =
		acc->input_feeder.data;

	ofs_x += acc->stripe.effective_stripes[1].offset;

	feeder_data =
		&acc->input_feeder.data_per_stripe.input_feeder_data[1].data;
	feeder_data->row_stride = acc->input_feeder.data.row_stride;
	feeder_data->start_row_address =
		ofs_x / IMGU_PIXELS_PER_WORD * IMGU_BYTES_PER_WORD +
		ofs_y * acc->input_feeder.data.row_stride;
	feeder_data->start_pixel = ofs_x % IMGU_PIXELS_PER_WORD;

	/* acc_param: bnr_अटल_config */

	/*
	 * Originate from user or be the original शेष values अगर user has
	 * never set them beक्रमe, when user gives a new set of parameters,
	 * क्रम each chunk in the parameter काष्ठाure there is a flag use->xxx
	 * whether to use the user-provided parameter or not. If not, the
	 * parameter reमुख्यs unchanged in the driver:
	 * it's value is taken from acc_old.
	 */
	अगर (use && use->acc_bnr) अणु
		/* Take values from user */
		acc->bnr = acc_user->bnr;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->bnr = acc_old->bnr;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->bnr = imgu_css_bnr_शेषs;
	पूर्ण

	acc->bnr.column_size = tnr_frame_width;

	/* acc_param: bnr_अटल_config_green_disparity */

	अगर (use && use->acc_green_disparity) अणु
		/* Take values from user */
		acc->green_disparity = acc_user->green_disparity;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->green_disparity = acc_old->green_disparity;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		स_रखो(&acc->green_disparity, 0, माप(acc->green_disparity));
	पूर्ण

	/* acc_param: dm_config */

	अगर (use && use->acc_dm) अणु
		/* Take values from user */
		acc->dm = acc_user->dm;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->dm = acc_old->dm;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->dm = imgu_css_dm_शेषs;
	पूर्ण

	acc->dm.frame_width = tnr_frame_width;

	/* acc_param: ccm_mat_config */

	अगर (use && use->acc_ccm) अणु
		/* Take values from user */
		acc->ccm = acc_user->ccm;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->ccm = acc_old->ccm;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->ccm = imgu_css_ccm_शेषs;
	पूर्ण

	/* acc_param: gamma_config */

	अगर (use && use->acc_gamma) अणु
		/* Take values from user */
		acc->gamma = acc_user->gamma;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->gamma = acc_old->gamma;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->gamma.gc_ctrl.enable = 1;
		acc->gamma.gc_lut = imgu_css_gamma_lut;
	पूर्ण

	/* acc_param: csc_mat_config */

	अगर (use && use->acc_csc) अणु
		/* Take values from user */
		acc->csc = acc_user->csc;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->csc = acc_old->csc;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->csc = imgu_css_csc_शेषs;
	पूर्ण

	/* acc_param: cds_params */

	अगर (use && use->acc_cds) अणु
		/* Take values from user */
		acc->cds = acc_user->cds;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->cds = acc_old->cds;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->cds = imgu_css_cds_शेषs;
	पूर्ण

	/* acc_param: shd_config */

	अगर (use && use->acc_shd) अणु
		/* Take values from user */
		acc->shd.shd = acc_user->shd.shd;
		acc->shd.shd_lut = acc_user->shd.shd_lut;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->shd.shd = acc_old->shd.shd;
		acc->shd.shd_lut = acc_old->shd.shd_lut;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->shd.shd = imgu_css_shd_शेषs;
		स_रखो(&acc->shd.shd_lut, 0, माप(acc->shd.shd_lut));
	पूर्ण

	अगर (acc->shd.shd.grid.width <= 0)
		वापस -EINVAL;

	acc->shd.shd.grid.grid_height_per_slice =
		IMGU_ABI_SHD_MAX_CELLS_PER_SET / acc->shd.shd.grid.width;

	अगर (acc->shd.shd.grid.grid_height_per_slice <= 0)
		वापस -EINVAL;

	acc->shd.shd.general.init_set_vrt_offst_ul =
				(-acc->shd.shd.grid.y_start >>
				 acc->shd.shd.grid.block_height_log2) %
				acc->shd.shd.grid.grid_height_per_slice;

	अगर (imgu_css_shd_ops_calc(&acc->shd.shd_ops, &acc->shd.shd.grid,
				  css_pipe->rect[IPU3_CSS_RECT_BDS].height))
		वापस -EINVAL;

	/* acc_param: dvs_stat_config */
	imgu_css_cfg_acc_dvs(css, acc, pipe);

	/* acc_param: yuvp1_iefd_config */

	अगर (use && use->acc_iefd) अणु
		/* Take values from user */
		acc->iefd = acc_user->iefd;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->iefd = acc_old->iefd;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->iefd = imgu_css_iefd_शेषs;
	पूर्ण

	/* acc_param: yuvp1_yds_config yds_c0 */

	अगर (use && use->acc_yds_c0) अणु
		/* Take values from user */
		acc->yds_c0 = acc_user->yds_c0;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->yds_c0 = acc_old->yds_c0;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->yds_c0 = imgu_css_yds_शेषs;
	पूर्ण

	/* acc_param: yuvp1_chnr_config chnr_c0 */

	अगर (use && use->acc_chnr_c0) अणु
		/* Take values from user */
		acc->chnr_c0 = acc_user->chnr_c0;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->chnr_c0 = acc_old->chnr_c0;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->chnr_c0 = imgu_css_chnr_शेषs;
	पूर्ण

	/* acc_param: yuvp1_y_ee_nr_config */

	अगर (use && use->acc_y_ee_nr) अणु
		/* Take values from user */
		acc->y_ee_nr = acc_user->y_ee_nr;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->y_ee_nr = acc_old->y_ee_nr;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->y_ee_nr = imgu_css_y_ee_nr_शेषs;
	पूर्ण

	/* acc_param: yuvp1_yds_config yds */

	अगर (use && use->acc_yds) अणु
		/* Take values from user */
		acc->yds = acc_user->yds;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->yds = acc_old->yds;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->yds = imgu_css_yds_शेषs;
	पूर्ण

	/* acc_param: yuvp1_chnr_config chnr */

	अगर (use && use->acc_chnr) अणु
		/* Take values from user */
		acc->chnr = acc_user->chnr;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->chnr = acc_old->chnr;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->chnr = imgu_css_chnr_शेषs;
	पूर्ण

	/* acc_param: yuvp2_y_पंचांग_lut_अटल_config */

	क्रम (i = 0; i < IMGU_ABI_YUVP2_YTM_LUT_ENTRIES; i++)
		acc->yपंचांग.entries[i] = i * 32;
	acc->yपंचांग.enable = 0;	/* Always disabled on IPU3 */

	/* acc_param: yuvp1_yds_config yds2 */

	अगर (use && use->acc_yds2) अणु
		/* Take values from user */
		acc->yds2 = acc_user->yds2;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->yds2 = acc_old->yds2;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->yds2 = imgu_css_yds_शेषs;
	पूर्ण

	/* acc_param: yuvp2_tcc_अटल_config */

	अगर (use && use->acc_tcc) अणु
		/* Take values from user */
		acc->tcc = acc_user->tcc;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->tcc = acc_old->tcc;
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		स_रखो(&acc->tcc, 0, माप(acc->tcc));

		acc->tcc.gen_control.en = 1;
		acc->tcc.gen_control.blend_shअगरt = 3;
		acc->tcc.gen_control.gain_according_to_y_only = 1;
		acc->tcc.gen_control.gamma = 8;
		acc->tcc.gen_control.delta = 0;

		क्रम (i = 0; i < IPU3_UAPI_YUVP2_TCC_MACC_TABLE_ELEMENTS; i++) अणु
			acc->tcc.macc_table.entries[i].a = 1024;
			acc->tcc.macc_table.entries[i].b = 0;
			acc->tcc.macc_table.entries[i].c = 0;
			acc->tcc.macc_table.entries[i].d = 1024;
		पूर्ण

		acc->tcc.inv_y_lut.entries[6] = 1023;
		क्रम (i = 7; i < IPU3_UAPI_YUVP2_TCC_INV_Y_LUT_ELEMENTS; i++)
			acc->tcc.inv_y_lut.entries[i] = 1024 >> (i - 6);

		acc->tcc.gain_pcwl = imgu_css_tcc_gain_pcwl_lut;
		acc->tcc.r_sqr_lut = imgu_css_tcc_r_sqr_lut;
	पूर्ण

	/* acc_param: dpc_config */

	अगर (use && use->acc_dpc)
		वापस -EINVAL;	/* Not supported yet */

	/* Just disable by शेष */
	स_रखो(&acc->dpc, 0, माप(acc->dpc));

	/* acc_param: bds_config */

	bds_ds = (css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].height *
		  IMGU_BDS_GRANULARITY) / css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	अगर (bds_ds < IMGU_BDS_MIN_SF_INV ||
	    bds_ds - IMGU_BDS_MIN_SF_INV >= ARRAY_SIZE(imgu_css_bds_configs))
		वापस -EINVAL;

	cfg_bds = &imgu_css_bds_configs[bds_ds - IMGU_BDS_MIN_SF_INV];
	acc->bds.hor.hor_ctrl1.hor_crop_en = 0;
	acc->bds.hor.hor_ctrl1.hor_crop_start = 0;
	acc->bds.hor.hor_ctrl1.hor_crop_end = 0;
	acc->bds.hor.hor_ctrl0.sample_patrn_length =
				cfg_bds->sample_patrn_length;
	acc->bds.hor.hor_ctrl0.hor_ds_en = cfg_bds->hor_ds_en;
	acc->bds.hor.hor_ctrl0.min_clip_val = IMGU_BDS_MIN_CLIP_VAL;
	acc->bds.hor.hor_ctrl0.max_clip_val = IMGU_BDS_MAX_CLIP_VAL;
	acc->bds.hor.hor_ctrl0.out_frame_width =
				css_pipe->rect[IPU3_CSS_RECT_BDS].width;
	acc->bds.hor.hor_ptrn_arr = cfg_bds->ptrn_arr;
	acc->bds.hor.hor_phase_arr = cfg_bds->hor_phase_arr;
	acc->bds.hor.hor_ctrl2.input_frame_height =
				css_pipe->rect[IPU3_CSS_RECT_EFFECTIVE].height;
	acc->bds.ver.ver_ctrl0.min_clip_val = IMGU_BDS_MIN_CLIP_VAL;
	acc->bds.ver.ver_ctrl0.max_clip_val = IMGU_BDS_MAX_CLIP_VAL;
	acc->bds.ver.ver_ctrl0.sample_patrn_length =
				cfg_bds->sample_patrn_length;
	acc->bds.ver.ver_ctrl0.ver_ds_en = cfg_bds->ver_ds_en;
	acc->bds.ver.ver_ptrn_arr = cfg_bds->ptrn_arr;
	acc->bds.ver.ver_phase_arr = cfg_bds->ver_phase_arr;
	acc->bds.ver.ver_ctrl1.out_frame_width =
				css_pipe->rect[IPU3_CSS_RECT_BDS].width;
	acc->bds.ver.ver_ctrl1.out_frame_height =
				css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	क्रम (i = 0; i < stripes; i++)
		acc_bds_per_stripe_data(css, acc, i, pipe);

	acc->bds.enabled = cfg_bds->hor_ds_en || cfg_bds->ver_ds_en;

	/* acc_param: anr_config */

	अगर (use && use->acc_anr) अणु
		/* Take values from user */
		acc->anr.transक्रमm = acc_user->anr.transक्रमm;
		acc->anr.stitch.anr_stitch_en =
			acc_user->anr.stitch.anr_stitch_en;
		स_नकल(acc->anr.stitch.pyramid, acc_user->anr.stitch.pyramid,
		       माप(acc->anr.stitch.pyramid));
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->anr.transक्रमm = acc_old->anr.transक्रमm;
		acc->anr.stitch.anr_stitch_en =
			acc_old->anr.stitch.anr_stitch_en;
		स_नकल(acc->anr.stitch.pyramid, acc_old->anr.stitch.pyramid,
		       माप(acc->anr.stitch.pyramid));
	पूर्ण अन्यथा अणु
		/* Calculate from scratch */
		acc->anr = imgu_css_anr_शेषs;
	पूर्ण

	/* Always enabled */
	acc->anr.search.enable = 1;
	acc->anr.transक्रमm.enable = 1;
	acc->anr.tile2strm.enable = 1;
	acc->anr.tile2strm.frame_width =
		ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width, IMGU_ISP_VMEM_ALIGN);
	acc->anr.search.frame_width = acc->anr.tile2strm.frame_width;
	acc->anr.stitch.frame_width = acc->anr.tile2strm.frame_width;
	acc->anr.tile2strm.frame_height = css_pipe->rect[IPU3_CSS_RECT_BDS].height;
	acc->anr.search.frame_height = acc->anr.tile2strm.frame_height;
	acc->anr.stitch.frame_height = acc->anr.tile2strm.frame_height;

	width = ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width, IMGU_ISP_VMEM_ALIGN);
	height = css_pipe->rect[IPU3_CSS_RECT_BDS].height;

	अगर (acc->anr.transक्रमm.xreset + width > IPU3_UAPI_ANR_MAX_RESET)
		acc->anr.transक्रमm.xreset = IPU3_UAPI_ANR_MAX_RESET - width;
	अगर (acc->anr.transक्रमm.xreset < IPU3_UAPI_ANR_MIN_RESET)
		acc->anr.transक्रमm.xreset = IPU3_UAPI_ANR_MIN_RESET;

	अगर (acc->anr.transक्रमm.yreset + height > IPU3_UAPI_ANR_MAX_RESET)
		acc->anr.transक्रमm.yreset = IPU3_UAPI_ANR_MAX_RESET - height;
	अगर (acc->anr.transक्रमm.yreset < IPU3_UAPI_ANR_MIN_RESET)
		acc->anr.transक्रमm.yreset = IPU3_UAPI_ANR_MIN_RESET;

	/* acc_param: awb_fr_config */

	अगर (use && use->acc_awb_fr) अणु
		/* Take values from user */
		acc->awb_fr.config = acc_user->awb_fr;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->awb_fr.config = acc_old->awb_fr.config;
	पूर्ण अन्यथा अणु
		/* Set from scratch */
		acc->awb_fr.config = imgu_css_awb_fr_शेषs;
	पूर्ण

	imgu_css_grid_end_calc(&acc->awb_fr.config.grid_cfg);

	अगर (acc->awb_fr.config.grid_cfg.width <= 0)
		वापस -EINVAL;

	acc->awb_fr.config.grid_cfg.height_per_slice =
		IMGU_ABI_AWB_FR_MAX_CELLS_PER_SET /
		acc->awb_fr.config.grid_cfg.width;

	क्रम (i = 0; i < stripes; i++)
		acc->awb_fr.stripes[i] = acc->awb_fr.config;

	अगर (acc->awb_fr.config.grid_cfg.x_start >=
	    acc->stripe.करोwn_scaled_stripes[1].offset + min_overlap) अणु
		/* Enable only क्रम righपंचांगost stripe, disable left */
		acc->awb_fr.stripes[0].grid_cfg.y_start &=
					~IPU3_UAPI_GRID_Y_START_EN;
	पूर्ण अन्यथा अगर (acc->awb_fr.config.grid_cfg.x_end <=
		   acc->stripe.bds_out_stripes[0].width - min_overlap) अणु
		/* Enable only क्रम lefपंचांगost stripe, disable right */
		acc->awb_fr.stripes[1].grid_cfg.y_start &=
					~IPU3_UAPI_GRID_Y_START_EN;
	पूर्ण अन्यथा अणु
		/* Enable क्रम both stripes */
		u16 end; /* width क्रम grid end */

		acc->awb_fr.stripes[0].grid_cfg.width =
			(acc->stripe.bds_out_stripes[0].width - min_overlap -
			 acc->awb_fr.config.grid_cfg.x_start + 1) >>
			acc->awb_fr.config.grid_cfg.block_width_log2;
		acc->awb_fr.stripes[1].grid_cfg.width =
			acc->awb_fr.config.grid_cfg.width -
			acc->awb_fr.stripes[0].grid_cfg.width;

		b_w_log2 = acc->awb_fr.stripes[0].grid_cfg.block_width_log2;
		end = imgu_css_grid_end(acc->awb_fr.stripes[0].grid_cfg.x_start,
					acc->awb_fr.stripes[0].grid_cfg.width,
					b_w_log2);
		acc->awb_fr.stripes[0].grid_cfg.x_end = end;

		acc->awb_fr.stripes[1].grid_cfg.x_start =
			(acc->awb_fr.stripes[0].grid_cfg.x_end + 1 -
			 acc->stripe.करोwn_scaled_stripes[1].offset) &
			IPU3_UAPI_GRID_START_MASK;
		b_w_log2 = acc->awb_fr.stripes[1].grid_cfg.block_width_log2;
		end = imgu_css_grid_end(acc->awb_fr.stripes[1].grid_cfg.x_start,
					acc->awb_fr.stripes[1].grid_cfg.width,
					b_w_log2);
		acc->awb_fr.stripes[1].grid_cfg.x_end = end;

		/*
		 * To reduce complनिकासy of debubbling and loading
		 * statistics fix grid_height_per_slice to 1 क्रम both
		 * stripes.
		 */
		क्रम (i = 0; i < stripes; i++)
			acc->awb_fr.stripes[i].grid_cfg.height_per_slice = 1;
	पूर्ण

	अगर (imgu_css_awb_fr_ops_calc(css, pipe, &acc->awb_fr))
		वापस -EINVAL;

	/* acc_param: ae_config */

	अगर (use && use->acc_ae) अणु
		/* Take values from user */
		acc->ae.grid_cfg = acc_user->ae.grid_cfg;
		acc->ae.ae_ccm = acc_user->ae.ae_ccm;
		क्रम (i = 0; i < IPU3_UAPI_AE_WEIGHTS; i++)
			acc->ae.weights[i] = acc_user->ae.weights[i];
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->ae.grid_cfg = acc_old->ae.grid_cfg;
		acc->ae.ae_ccm = acc_old->ae.ae_ccm;
		क्रम (i = 0; i < IPU3_UAPI_AE_WEIGHTS; i++)
			acc->ae.weights[i] = acc_old->ae.weights[i];
	पूर्ण अन्यथा अणु
		/* Set from scratch */
		अटल स्थिर काष्ठा ipu3_uapi_ae_weight_elem
			weight_def = अणु 1, 1, 1, 1, 1, 1, 1, 1 पूर्ण;

		acc->ae.grid_cfg = imgu_css_ae_grid_शेषs;
		acc->ae.ae_ccm = imgu_css_ae_ccm_शेषs;
		क्रम (i = 0; i < IPU3_UAPI_AE_WEIGHTS; i++)
			acc->ae.weights[i] = weight_def;
	पूर्ण

	b_w_log2 = acc->ae.grid_cfg.block_width_log2;
	acc->ae.grid_cfg.x_end = imgu_css_grid_end(acc->ae.grid_cfg.x_start,
						   acc->ae.grid_cfg.width,
						   b_w_log2);
	b_w_log2 = acc->ae.grid_cfg.block_height_log2;
	acc->ae.grid_cfg.y_end = imgu_css_grid_end(acc->ae.grid_cfg.y_start,
						   acc->ae.grid_cfg.height,
						   b_w_log2);

	क्रम (i = 0; i < stripes; i++)
		acc->ae.stripes[i].grid = acc->ae.grid_cfg;

	अगर (acc->ae.grid_cfg.x_start >=
	    acc->stripe.करोwn_scaled_stripes[1].offset) अणु
		/* Enable only क्रम righपंचांगost stripe, disable left */
		acc->ae.stripes[0].grid.ae_en = 0;
	पूर्ण अन्यथा अगर (acc->ae.grid_cfg.x_end <=
		   acc->stripe.bds_out_stripes[0].width) अणु
		/* Enable only क्रम lefपंचांगost stripe, disable right */
		acc->ae.stripes[1].grid.ae_en = 0;
	पूर्ण अन्यथा अणु
		/* Enable क्रम both stripes */
		u8 b_w_log2;

		acc->ae.stripes[0].grid.width =
			(acc->stripe.bds_out_stripes[0].width -
			 acc->ae.grid_cfg.x_start + 1) >>
			acc->ae.grid_cfg.block_width_log2;

		acc->ae.stripes[1].grid.width =
			acc->ae.grid_cfg.width - acc->ae.stripes[0].grid.width;

		b_w_log2 = acc->ae.stripes[0].grid.block_width_log2;
		acc->ae.stripes[0].grid.x_end =
			imgu_css_grid_end(acc->ae.stripes[0].grid.x_start,
					  acc->ae.stripes[0].grid.width,
					  b_w_log2);

		acc->ae.stripes[1].grid.x_start =
			(acc->ae.stripes[0].grid.x_end + 1 -
			 acc->stripe.करोwn_scaled_stripes[1].offset) &
			IPU3_UAPI_GRID_START_MASK;
		b_w_log2 = acc->ae.stripes[1].grid.block_width_log2;
		acc->ae.stripes[1].grid.x_end =
			imgu_css_grid_end(acc->ae.stripes[1].grid.x_start,
					  acc->ae.stripes[1].grid.width,
					  b_w_log2);
	पूर्ण

	/* acc_param: af_config */

	अगर (use && use->acc_af) अणु
		/* Take values from user */
		acc->af.config.filter_config = acc_user->af.filter_config;
		acc->af.config.grid_cfg = acc_user->af.grid_cfg;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->af.config = acc_old->af.config;
	पूर्ण अन्यथा अणु
		/* Set from scratch */
		acc->af.config.filter_config =
				imgu_css_af_शेषs.filter_config;
		acc->af.config.grid_cfg = imgu_css_af_शेषs.grid_cfg;
	पूर्ण

	imgu_css_grid_end_calc(&acc->af.config.grid_cfg);

	अगर (acc->af.config.grid_cfg.width <= 0)
		वापस -EINVAL;

	acc->af.config.grid_cfg.height_per_slice =
		IMGU_ABI_AF_MAX_CELLS_PER_SET / acc->af.config.grid_cfg.width;
	acc->af.config.frame_size.width =
		ALIGN(css_pipe->rect[IPU3_CSS_RECT_BDS].width, IMGU_ISP_VMEM_ALIGN);
	acc->af.config.frame_size.height =
		css_pipe->rect[IPU3_CSS_RECT_BDS].height;

	अगर (acc->stripe.bds_out_stripes[0].width <= min_overlap)
		वापस -EINVAL;

	क्रम (i = 0; i < stripes; i++) अणु
		acc->af.stripes[i].grid_cfg = acc->af.config.grid_cfg;
		acc->af.stripes[i].frame_size.height =
				css_pipe->rect[IPU3_CSS_RECT_BDS].height;
		acc->af.stripes[i].frame_size.width =
			acc->stripe.bds_out_stripes[i].width;
	पूर्ण

	अगर (acc->af.config.grid_cfg.x_start >=
	    acc->stripe.करोwn_scaled_stripes[1].offset + min_overlap) अणु
		/* Enable only क्रम righपंचांगost stripe, disable left */
		acc->af.stripes[0].grid_cfg.y_start &=
			~IPU3_UAPI_GRID_Y_START_EN;
	पूर्ण अन्यथा अगर (acc->af.config.grid_cfg.x_end <=
		   acc->stripe.bds_out_stripes[0].width - min_overlap) अणु
		/* Enable only क्रम lefपंचांगost stripe, disable right */
		acc->af.stripes[1].grid_cfg.y_start &=
			~IPU3_UAPI_GRID_Y_START_EN;
	पूर्ण अन्यथा अणु
		/* Enable क्रम both stripes */

		acc->af.stripes[0].grid_cfg.width =
			(acc->stripe.bds_out_stripes[0].width - min_overlap -
			 acc->af.config.grid_cfg.x_start + 1) >>
			acc->af.config.grid_cfg.block_width_log2;
		acc->af.stripes[1].grid_cfg.width =
			acc->af.config.grid_cfg.width -
			acc->af.stripes[0].grid_cfg.width;

		b_w_log2 = acc->af.stripes[0].grid_cfg.block_width_log2;
		acc->af.stripes[0].grid_cfg.x_end =
			imgu_css_grid_end(acc->af.stripes[0].grid_cfg.x_start,
					  acc->af.stripes[0].grid_cfg.width,
					  b_w_log2);

		acc->af.stripes[1].grid_cfg.x_start =
			(acc->af.stripes[0].grid_cfg.x_end + 1 -
			 acc->stripe.करोwn_scaled_stripes[1].offset) &
			IPU3_UAPI_GRID_START_MASK;

		b_w_log2 = acc->af.stripes[1].grid_cfg.block_width_log2;
		acc->af.stripes[1].grid_cfg.x_end =
			imgu_css_grid_end(acc->af.stripes[1].grid_cfg.x_start,
					  acc->af.stripes[1].grid_cfg.width,
					  b_w_log2);

		/*
		 * To reduce complनिकासy of debubbling and loading statistics
		 * fix grid_height_per_slice to 1 क्रम both stripes
		 */
		क्रम (i = 0; i < stripes; i++)
			acc->af.stripes[i].grid_cfg.height_per_slice = 1;
	पूर्ण

	अगर (imgu_css_af_ops_calc(css, pipe, &acc->af))
		वापस -EINVAL;

	/* acc_param: awb_config */

	अगर (use && use->acc_awb) अणु
		/* Take values from user */
		acc->awb.config = acc_user->awb.config;
	पूर्ण अन्यथा अगर (acc_old) अणु
		/* Use old value */
		acc->awb.config = acc_old->awb.config;
	पूर्ण अन्यथा अणु
		/* Set from scratch */
		acc->awb.config = imgu_css_awb_शेषs;
	पूर्ण

	अगर (acc->awb.config.grid.width <= 0)
		वापस -EINVAL;

	acc->awb.config.grid.height_per_slice =
		IMGU_ABI_AWB_MAX_CELLS_PER_SET / acc->awb.config.grid.width,
	imgu_css_grid_end_calc(&acc->awb.config.grid);

	क्रम (i = 0; i < stripes; i++)
		acc->awb.stripes[i] = acc->awb.config;

	अगर (acc->awb.config.grid.x_start >=
	    acc->stripe.करोwn_scaled_stripes[1].offset + min_overlap) अणु
		/* Enable only क्रम righपंचांगost stripe, disable left */
		acc->awb.stripes[0].rgbs_thr_b &= ~IPU3_UAPI_AWB_RGBS_THR_B_EN;
	पूर्ण अन्यथा अगर (acc->awb.config.grid.x_end <=
		   acc->stripe.bds_out_stripes[0].width - min_overlap) अणु
		/* Enable only क्रम lefपंचांगost stripe, disable right */
		acc->awb.stripes[1].rgbs_thr_b &= ~IPU3_UAPI_AWB_RGBS_THR_B_EN;
	पूर्ण अन्यथा अणु
		/* Enable क्रम both stripes */

		acc->awb.stripes[0].grid.width =
			(acc->stripe.bds_out_stripes[0].width -
			 acc->awb.config.grid.x_start + 1) >>
			acc->awb.config.grid.block_width_log2;
		acc->awb.stripes[1].grid.width = acc->awb.config.grid.width -
				acc->awb.stripes[0].grid.width;

		b_w_log2 = acc->awb.stripes[0].grid.block_width_log2;
		acc->awb.stripes[0].grid.x_end =
			imgu_css_grid_end(acc->awb.stripes[0].grid.x_start,
					  acc->awb.stripes[0].grid.width,
					  b_w_log2);

		acc->awb.stripes[1].grid.x_start =
			(acc->awb.stripes[0].grid.x_end + 1 -
			 acc->stripe.करोwn_scaled_stripes[1].offset) &
			IPU3_UAPI_GRID_START_MASK;

		b_w_log2 = acc->awb.stripes[1].grid.block_width_log2;
		acc->awb.stripes[1].grid.x_end =
			imgu_css_grid_end(acc->awb.stripes[1].grid.x_start,
					  acc->awb.stripes[1].grid.width,
					  b_w_log2);

		/*
		 * To reduce complनिकासy of debubbling and loading statistics
		 * fix grid_height_per_slice to 1 क्रम both stripes
		 */
		क्रम (i = 0; i < stripes; i++)
			acc->awb.stripes[i].grid.height_per_slice = 1;
	पूर्ण

	अगर (imgu_css_awb_ops_calc(css, pipe, &acc->awb))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Fill the indicated काष्ठाure in `new_binary_params' from the possible
 * sources based on `use_user' flag: अगर the flag is false, copy from
 * `old_binary_params', or if the flag is true, copy from `user_setting'
 * and वापस शून्य (or error poपूर्णांकer on error).
 * If the flag is false and `old_binary_params' is शून्य, वापस poपूर्णांकer
 * to the काष्ठाure inside `new_binary_params'. In that हाल the caller
 * should calculate and fill the काष्ठाure from scratch.
 */
अटल व्योम *imgu_css_cfg_copy(काष्ठा imgu_css *css,
			       अचिन्हित पूर्णांक pipe, bool use_user,
			       व्योम *user_setting, व्योम *old_binary_params,
			       व्योम *new_binary_params,
			       क्रमागत imgu_abi_memories m,
			       काष्ठा imgu_fw_isp_parameter *par,
			       माप_प्रकार par_size)
अणु
	स्थिर क्रमागत imgu_abi_param_class c = IMGU_ABI_PARAM_CLASS_PARAM;
	व्योम *new_setting, *old_setting;

	new_setting = imgu_css_fw_pipeline_params(css, pipe, c, m, par,
						  par_size, new_binary_params);
	अगर (!new_setting)
		वापस ERR_PTR(-EPROTO);	/* Corrupted firmware */

	अगर (use_user) अणु
		/* Take new user parameters */
		स_नकल(new_setting, user_setting, par_size);
	पूर्ण अन्यथा अगर (old_binary_params) अणु
		/* Take previous value */
		old_setting = imgu_css_fw_pipeline_params(css, pipe, c, m, par,
							  par_size,
							  old_binary_params);
		अगर (!old_setting)
			वापस ERR_PTR(-EPROTO);
		स_नकल(new_setting, old_setting, par_size);
	पूर्ण अन्यथा अणु
		वापस new_setting;	/* Need to calculate */
	पूर्ण

	वापस शून्य;		/* Copied from other value */
पूर्ण

/*
 * Configure VMEM0 parameters (late binding parameters).
 */
पूर्णांक imgu_css_cfg_vmem0(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		       काष्ठा ipu3_uapi_flags *use,
		       व्योम *vmem0, व्योम *vmem0_old,
		       काष्ठा ipu3_uapi_params *user)
अणु
	स्थिर काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css->pipes[pipe].bindex];
	काष्ठा imgu_fw_param_memory_offsets *pofs = (व्योम *)css->fwp +
		bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_PARAM];
	काष्ठा ipu3_uapi_isp_lin_vmem_params *lin_vmem = शून्य;
	काष्ठा ipu3_uapi_isp_tnr3_vmem_params *tnr_vmem = शून्य;
	काष्ठा ipu3_uapi_isp_xnr3_vmem_params *xnr_vmem = शून्य;
	स्थिर क्रमागत imgu_abi_param_class c = IMGU_ABI_PARAM_CLASS_PARAM;
	स्थिर क्रमागत imgu_abi_memories m = IMGU_ABI_MEM_ISP_VMEM0;
	अचिन्हित पूर्णांक i;

	/* Configure VMEM0 */

	स_रखो(vmem0, 0, bi->info.isp.sp.mem_initializers.params[c][m].size);

	/* Configure Linearization VMEM0 parameters */

	lin_vmem = imgu_css_cfg_copy(css, pipe, use && use->lin_vmem_params,
				     &user->lin_vmem_params, vmem0_old, vmem0,
				     m, &pofs->vmem.lin, माप(*lin_vmem));
	अगर (!IS_ERR_OR_शून्य(lin_vmem)) अणु
		/* Generate parameter from scratch */
		क्रम (i = 0; i < IPU3_UAPI_LIN_LUT_SIZE; i++) अणु
			lin_vmem->lin_lutlow_gr[i] = 32 * i;
			lin_vmem->lin_lutlow_r[i] = 32 * i;
			lin_vmem->lin_lutlow_b[i] = 32 * i;
			lin_vmem->lin_lutlow_gb[i] = 32 * i;

			lin_vmem->lin_lutdअगर_gr[i] = 32;
			lin_vmem->lin_lutdअगर_r[i] = 32;
			lin_vmem->lin_lutdअगर_b[i] = 32;
			lin_vmem->lin_lutdअगर_gb[i] = 32;
		पूर्ण
	पूर्ण

	/* Configure TNR3 VMEM parameters */
	अगर (css->pipes[pipe].pipe_id == IPU3_CSS_PIPE_ID_VIDEO) अणु
		tnr_vmem = imgu_css_cfg_copy(css, pipe,
					     use && use->tnr3_vmem_params,
					     &user->tnr3_vmem_params,
					     vmem0_old, vmem0, m,
					     &pofs->vmem.tnr3,
					     माप(*tnr_vmem));
		अगर (!IS_ERR_OR_शून्य(tnr_vmem)) अणु
			/* Generate parameter from scratch */
			क्रम (i = 0; i < IPU3_UAPI_ISP_TNR3_VMEM_LEN; i++)
				tnr_vmem->sigma[i] = 256;
		पूर्ण
	पूर्ण
	i = IPU3_UAPI_ISP_TNR3_VMEM_LEN;

	/* Configure XNR3 VMEM parameters */

	xnr_vmem = imgu_css_cfg_copy(css, pipe, use && use->xnr3_vmem_params,
				     &user->xnr3_vmem_params, vmem0_old, vmem0,
				     m, &pofs->vmem.xnr3, माप(*xnr_vmem));
	अगर (!IS_ERR_OR_शून्य(xnr_vmem)) अणु
		xnr_vmem->x[i] = imgu_css_xnr3_vmem_शेषs.x
			[i % IMGU_XNR3_VMEM_LUT_LEN];
		xnr_vmem->a[i] = imgu_css_xnr3_vmem_शेषs.a
			[i % IMGU_XNR3_VMEM_LUT_LEN];
		xnr_vmem->b[i] = imgu_css_xnr3_vmem_शेषs.b
			[i % IMGU_XNR3_VMEM_LUT_LEN];
		xnr_vmem->c[i] = imgu_css_xnr3_vmem_शेषs.c
			[i % IMGU_XNR3_VMEM_LUT_LEN];
	पूर्ण

	वापस IS_ERR(lin_vmem) || IS_ERR(tnr_vmem) || IS_ERR(xnr_vmem) ?
		-EPROTO : 0;
पूर्ण

/*
 * Configure DMEM0 parameters (late binding parameters).
 */
पूर्णांक imgu_css_cfg_dmem0(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		       काष्ठा ipu3_uapi_flags *use,
		       व्योम *dmem0, व्योम *dmem0_old,
		       काष्ठा ipu3_uapi_params *user)
अणु
	काष्ठा imgu_css_pipe *css_pipe = &css->pipes[pipe];
	स्थिर काष्ठा imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];
	काष्ठा imgu_fw_param_memory_offsets *pofs = (व्योम *)css->fwp +
		bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_PARAM];

	काष्ठा ipu3_uapi_isp_tnr3_params *tnr_dmem = शून्य;
	काष्ठा ipu3_uapi_isp_xnr3_params *xnr_dmem;

	स्थिर क्रमागत imgu_abi_param_class c = IMGU_ABI_PARAM_CLASS_PARAM;
	स्थिर क्रमागत imgu_abi_memories m = IMGU_ABI_MEM_ISP_DMEM0;

	/* Configure DMEM0 */

	स_रखो(dmem0, 0, bi->info.isp.sp.mem_initializers.params[c][m].size);

	/* Configure TNR3 DMEM0 parameters */
	अगर (css_pipe->pipe_id == IPU3_CSS_PIPE_ID_VIDEO) अणु
		tnr_dmem = imgu_css_cfg_copy(css, pipe,
					     use && use->tnr3_dmem_params,
					     &user->tnr3_dmem_params,
					     dmem0_old, dmem0, m,
					     &pofs->dmem.tnr3,
					     माप(*tnr_dmem));
		अगर (!IS_ERR_OR_शून्य(tnr_dmem)) अणु
			/* Generate parameter from scratch */
			tnr_dmem->knee_y1 = 768;
			tnr_dmem->knee_y2 = 1280;
		पूर्ण
	पूर्ण

	/* Configure XNR3 DMEM0 parameters */

	xnr_dmem = imgu_css_cfg_copy(css, pipe, use && use->xnr3_dmem_params,
				     &user->xnr3_dmem_params, dmem0_old, dmem0,
				     m, &pofs->dmem.xnr3, माप(*xnr_dmem));
	अगर (!IS_ERR_OR_शून्य(xnr_dmem)) अणु
		/* Generate parameter from scratch */
		xnr_dmem->alpha.y0 = 2047;
		xnr_dmem->alpha.u0 = 2047;
		xnr_dmem->alpha.v0 = 2047;
	पूर्ण

	वापस IS_ERR(tnr_dmem) || IS_ERR(xnr_dmem) ? -EPROTO : 0;
पूर्ण

/* Generate unity morphing table without morphing effect */
व्योम imgu_css_cfg_gdc_table(काष्ठा imgu_abi_gdc_warp_param *gdc,
			    पूर्णांक frame_in_x, पूर्णांक frame_in_y,
			    पूर्णांक frame_out_x, पूर्णांक frame_out_y,
			    पूर्णांक env_w, पूर्णांक env_h)
अणु
	अटल स्थिर अचिन्हित पूर्णांक FRAC_BITS = IMGU_ABI_GDC_FRAC_BITS;
	अटल स्थिर अचिन्हित पूर्णांक XMEM_ALIGN = 1 << 4;
	स्थिर अचिन्हित पूर्णांक XMEM_ALIGN_MASK = ~(XMEM_ALIGN - 1);
	अटल स्थिर अचिन्हित पूर्णांक BCI_ENV = 4;
	अटल स्थिर अचिन्हित पूर्णांक BYP = 2;	/* Bytes per pixel */
	स्थिर अचिन्हित पूर्णांक OFFSET_X = 2 * IMGU_DVS_BLOCK_W + env_w + 1;
	स्थिर अचिन्हित पूर्णांक OFFSET_Y = IMGU_DVS_BLOCK_H + env_h + 1;

	काष्ठा imgu_abi_gdc_warp_param gdc_luma, gdc_chroma;

	अचिन्हित पूर्णांक blocks_x = ALIGN(DIV_ROUND_UP(frame_out_x,
						   IMGU_DVS_BLOCK_W), 2);
	अचिन्हित पूर्णांक blocks_y = DIV_ROUND_UP(frame_out_y, IMGU_DVS_BLOCK_H);
	अचिन्हित पूर्णांक y0, x0, x1, x, y;

	/* Global luma settings */
	gdc_luma.origin_x = 0;
	gdc_luma.origin_y = 0;
	gdc_luma.p0_x = (OFFSET_X - (OFFSET_X & XMEM_ALIGN_MASK)) << FRAC_BITS;
	gdc_luma.p0_y = 0;
	gdc_luma.p1_x = gdc_luma.p0_x + (IMGU_DVS_BLOCK_W << FRAC_BITS);
	gdc_luma.p1_y = gdc_luma.p0_y;
	gdc_luma.p2_x = gdc_luma.p0_x;
	gdc_luma.p2_y = gdc_luma.p0_y + (IMGU_DVS_BLOCK_H << FRAC_BITS);
	gdc_luma.p3_x = gdc_luma.p1_x;
	gdc_luma.p3_y = gdc_luma.p2_y;

	gdc_luma.in_block_width = IMGU_DVS_BLOCK_W + BCI_ENV +
					OFFSET_X - (OFFSET_X & XMEM_ALIGN_MASK);
	gdc_luma.in_block_width_a = DIV_ROUND_UP(gdc_luma.in_block_width,
						 IPU3_UAPI_ISP_VEC_ELEMS);
	gdc_luma.in_block_width_b = DIV_ROUND_UP(gdc_luma.in_block_width,
						 IMGU_ABI_ISP_DDR_WORD_BYTES /
						 BYP);
	gdc_luma.in_block_height = IMGU_DVS_BLOCK_H + BCI_ENV;
	gdc_luma.padding = 0;

	/* Global chroma settings */
	gdc_chroma.origin_x = 0;
	gdc_chroma.origin_y = 0;
	gdc_chroma.p0_x = (OFFSET_X / 2 - (OFFSET_X / 2 & XMEM_ALIGN_MASK)) <<
			   FRAC_BITS;
	gdc_chroma.p0_y = 0;
	gdc_chroma.p1_x = gdc_chroma.p0_x + (IMGU_DVS_BLOCK_W << FRAC_BITS);
	gdc_chroma.p1_y = gdc_chroma.p0_y;
	gdc_chroma.p2_x = gdc_chroma.p0_x;
	gdc_chroma.p2_y = gdc_chroma.p0_y + (IMGU_DVS_BLOCK_H / 2 << FRAC_BITS);
	gdc_chroma.p3_x = gdc_chroma.p1_x;
	gdc_chroma.p3_y = gdc_chroma.p2_y;

	gdc_chroma.in_block_width = IMGU_DVS_BLOCK_W + BCI_ENV;
	gdc_chroma.in_block_width_a = DIV_ROUND_UP(gdc_chroma.in_block_width,
						   IPU3_UAPI_ISP_VEC_ELEMS);
	gdc_chroma.in_block_width_b = DIV_ROUND_UP(gdc_chroma.in_block_width,
						   IMGU_ABI_ISP_DDR_WORD_BYTES /
						   BYP);
	gdc_chroma.in_block_height = IMGU_DVS_BLOCK_H / 2 + BCI_ENV;
	gdc_chroma.padding = 0;

	/* Calculate block offsets क्रम luma and chroma */
	क्रम (y0 = 0; y0 < blocks_y; y0++) अणु
		क्रम (x0 = 0; x0 < blocks_x / 2; x0++) अणु
			क्रम (x1 = 0; x1 < 2; x1++) अणु
				/* Luma blocks */
				x = (x0 * 2 + x1) * IMGU_DVS_BLOCK_W + OFFSET_X;
				x &= XMEM_ALIGN_MASK;
				y = y0 * IMGU_DVS_BLOCK_H + OFFSET_Y;
				*gdc = gdc_luma;
				gdc->in_addr_offset =
					(y * frame_in_x + x) * BYP;
				gdc++;
			पूर्ण

			/* Chroma block */
			x = x0 * IMGU_DVS_BLOCK_W + OFFSET_X / 2;
			x &= XMEM_ALIGN_MASK;
			y = y0 * (IMGU_DVS_BLOCK_H / 2) + OFFSET_Y / 2;
			*gdc = gdc_chroma;
			gdc->in_addr_offset = (y * frame_in_x + x) * BYP;
			gdc++;
		पूर्ण
	पूर्ण
पूर्ण
