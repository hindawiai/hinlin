<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
#समावेश "dc.h"
#समावेश "mod_freesync.h"
#समावेश "core_types.h"

#घोषणा MOD_FREESYNC_MAX_CONCURRENT_STREAMS  32

#घोषणा MIN_REFRESH_RANGE 10
/* Refresh rate ramp at a fixed rate of 65 Hz/second */
#घोषणा STATIC_SCREEN_RAMP_DELTA_REFRESH_RATE_PER_FRAME ((1000 / 60) * 65)
/* Number of elements in the render बार cache array */
#घोषणा RENDER_TIMES_MAX_COUNT 10
/* Threshold to निकास/निकास BTR (to aव्योम frequent enter-निकासs at the lower limit) */
#घोषणा BTR_MAX_MARGIN 2500
/* Threshold to change BTR multiplier (to aव्योम frequent changes) */
#घोषणा BTR_DRIFT_MARGIN 2000
/* Threshold to निकास fixed refresh rate */
#घोषणा FIXED_REFRESH_EXIT_MARGIN_IN_HZ 1
/* Number of consecutive frames to check beक्रमe entering/निकासing fixed refresh */
#घोषणा FIXED_REFRESH_ENTER_FRAME_COUNT 5
#घोषणा FIXED_REFRESH_EXIT_FRAME_COUNT 10

काष्ठा core_मुक्तsync अणु
	काष्ठा mod_मुक्तsync खुला;
	काष्ठा dc *dc;
पूर्ण;

#घोषणा MOD_FREESYNC_TO_CORE(mod_मुक्तsync)\
		container_of(mod_मुक्तsync, काष्ठा core_मुक्तsync, खुला)

काष्ठा mod_मुक्तsync *mod_मुक्तsync_create(काष्ठा dc *dc)
अणु
	काष्ठा core_मुक्तsync *core_मुक्तsync =
			kzalloc(माप(काष्ठा core_मुक्तsync), GFP_KERNEL);

	अगर (core_मुक्तsync == शून्य)
		जाओ fail_alloc_context;

	अगर (dc == शून्य)
		जाओ fail_स्थिरruct;

	core_मुक्तsync->dc = dc;
	वापस &core_मुक्तsync->खुला;

fail_स्थिरruct:
	kमुक्त(core_मुक्तsync);

fail_alloc_context:
	वापस शून्य;
पूर्ण

व्योम mod_मुक्तsync_destroy(काष्ठा mod_मुक्तsync *mod_मुक्तsync)
अणु
	काष्ठा core_मुक्तsync *core_मुक्तsync = शून्य;
	अगर (mod_मुक्तsync == शून्य)
		वापस;
	core_मुक्तsync = MOD_FREESYNC_TO_CORE(mod_मुक्तsync);
	kमुक्त(core_मुक्तsync);
पूर्ण

#अगर 0 /* Unused currently */
अटल अचिन्हित पूर्णांक calc_refresh_in_uhz_from_duration(
		अचिन्हित पूर्णांक duration_in_ns)
अणु
	अचिन्हित पूर्णांक refresh_in_uhz =
			((अचिन्हित पूर्णांक)(भाग64_u64((1000000000ULL * 1000000),
					duration_in_ns)));
	वापस refresh_in_uhz;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक calc_duration_in_us_from_refresh_in_uhz(
		अचिन्हित पूर्णांक refresh_in_uhz)
अणु
	अचिन्हित पूर्णांक duration_in_us =
			((अचिन्हित पूर्णांक)(भाग64_u64((1000000000ULL * 1000),
					refresh_in_uhz)));
	वापस duration_in_us;
पूर्ण

अटल अचिन्हित पूर्णांक calc_duration_in_us_from_v_total(
		स्थिर काष्ठा dc_stream_state *stream,
		स्थिर काष्ठा mod_vrr_params *in_vrr,
		अचिन्हित पूर्णांक v_total)
अणु
	अचिन्हित पूर्णांक duration_in_us =
			(अचिन्हित पूर्णांक)(भाग64_u64(((अचिन्हित दीर्घ दीर्घ)(v_total)
				* 10000) * stream->timing.h_total,
					stream->timing.pix_clk_100hz));

	वापस duration_in_us;
पूर्ण

अचिन्हित पूर्णांक mod_मुक्तsync_calc_v_total_from_refresh(
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक refresh_in_uhz)
अणु
	अचिन्हित पूर्णांक v_total;
	अचिन्हित पूर्णांक frame_duration_in_ns;

	frame_duration_in_ns =
			((अचिन्हित पूर्णांक)(भाग64_u64((1000000000ULL * 1000000),
					refresh_in_uhz)));

	v_total = भाग64_u64(भाग64_u64(((अचिन्हित दीर्घ दीर्घ)(
			frame_duration_in_ns) * (stream->timing.pix_clk_100hz / 10)),
			stream->timing.h_total), 1000000);

	/* v_total cannot be less than nominal */
	अगर (v_total < stream->timing.v_total) अणु
		ASSERT(v_total < stream->timing.v_total);
		v_total = stream->timing.v_total;
	पूर्ण

	वापस v_total;
पूर्ण

अटल अचिन्हित पूर्णांक calc_v_total_from_duration(
		स्थिर काष्ठा dc_stream_state *stream,
		स्थिर काष्ठा mod_vrr_params *vrr,
		अचिन्हित पूर्णांक duration_in_us)
अणु
	अचिन्हित पूर्णांक v_total = 0;

	अगर (duration_in_us < vrr->min_duration_in_us)
		duration_in_us = vrr->min_duration_in_us;

	अगर (duration_in_us > vrr->max_duration_in_us)
		duration_in_us = vrr->max_duration_in_us;

	v_total = भाग64_u64(भाग64_u64(((अचिन्हित दीर्घ दीर्घ)(
				duration_in_us) * (stream->timing.pix_clk_100hz / 10)),
				stream->timing.h_total), 1000);

	/* v_total cannot be less than nominal */
	अगर (v_total < stream->timing.v_total) अणु
		ASSERT(v_total < stream->timing.v_total);
		v_total = stream->timing.v_total;
	पूर्ण

	वापस v_total;
पूर्ण

अटल व्योम update_v_total_क्रम_अटल_ramp(
		काष्ठा core_मुक्तsync *core_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा mod_vrr_params *in_out_vrr)
अणु
	अचिन्हित पूर्णांक v_total = 0;
	अचिन्हित पूर्णांक current_duration_in_us =
			calc_duration_in_us_from_v_total(
				stream, in_out_vrr,
				in_out_vrr->adjust.v_total_max);
	अचिन्हित पूर्णांक target_duration_in_us =
			calc_duration_in_us_from_refresh_in_uhz(
				in_out_vrr->fixed.target_refresh_in_uhz);
	bool ramp_direction_is_up = (current_duration_in_us >
				target_duration_in_us) ? true : false;

	/* Calculate ratio between new and current frame duration with 3 digit */
	अचिन्हित पूर्णांक frame_duration_ratio = भाग64_u64(1000000,
		(1000 +  भाग64_u64(((अचिन्हित दीर्घ दीर्घ)(
		STATIC_SCREEN_RAMP_DELTA_REFRESH_RATE_PER_FRAME) *
		current_duration_in_us),
		1000000)));

	/* Calculate delta between new and current frame duration in us */
	अचिन्हित पूर्णांक frame_duration_delta = भाग64_u64(((अचिन्हित दीर्घ दीर्घ)(
		current_duration_in_us) *
		(1000 - frame_duration_ratio)), 1000);

	/* Adjust frame duration delta based on ratio between current and
	 * standard frame duration (frame duration at 60 Hz refresh rate).
	 */
	अचिन्हित पूर्णांक ramp_rate_पूर्णांकerpolated = भाग64_u64(((अचिन्हित दीर्घ दीर्घ)(
		frame_duration_delta) * current_duration_in_us), 16666);

	/* Going to a higher refresh rate (lower frame duration) */
	अगर (ramp_direction_is_up) अणु
		/* Reduce frame duration */
		current_duration_in_us -= ramp_rate_पूर्णांकerpolated;

		/* Adjust क्रम frame duration below min */
		अगर (current_duration_in_us <= target_duration_in_us) अणु
			in_out_vrr->fixed.ramping_active = false;
			in_out_vrr->fixed.ramping_करोne = true;
			current_duration_in_us =
				calc_duration_in_us_from_refresh_in_uhz(
				in_out_vrr->fixed.target_refresh_in_uhz);
		पूर्ण
	/* Going to a lower refresh rate (larger frame duration) */
	पूर्ण अन्यथा अणु
		/* Increase frame duration */
		current_duration_in_us += ramp_rate_पूर्णांकerpolated;

		/* Adjust क्रम frame duration above max */
		अगर (current_duration_in_us >= target_duration_in_us) अणु
			in_out_vrr->fixed.ramping_active = false;
			in_out_vrr->fixed.ramping_करोne = true;
			current_duration_in_us =
				calc_duration_in_us_from_refresh_in_uhz(
				in_out_vrr->fixed.target_refresh_in_uhz);
		पूर्ण
	पूर्ण

	v_total = भाग64_u64(भाग64_u64(((अचिन्हित दीर्घ दीर्घ)(
			current_duration_in_us) * (stream->timing.pix_clk_100hz / 10)),
				stream->timing.h_total), 1000);

	/* v_total cannot be less than nominal */
	अगर (v_total < stream->timing.v_total)
		v_total = stream->timing.v_total;

	in_out_vrr->adjust.v_total_min = v_total;
	in_out_vrr->adjust.v_total_max = v_total;
पूर्ण

अटल व्योम apply_below_the_range(काष्ठा core_मुक्तsync *core_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक last_render_समय_in_us,
		काष्ठा mod_vrr_params *in_out_vrr)
अणु
	अचिन्हित पूर्णांक inserted_frame_duration_in_us = 0;
	अचिन्हित पूर्णांक mid_poपूर्णांक_frames_उच्चमान = 0;
	अचिन्हित पूर्णांक mid_poपूर्णांक_frames_न्यूनमान = 0;
	अचिन्हित पूर्णांक frame_समय_in_us = 0;
	अचिन्हित पूर्णांक delta_from_mid_poपूर्णांक_in_us_1 = 0xFFFFFFFF;
	अचिन्हित पूर्णांक delta_from_mid_poपूर्णांक_in_us_2 = 0xFFFFFFFF;
	अचिन्हित पूर्णांक frames_to_insert = 0;
	अचिन्हित पूर्णांक delta_from_mid_poपूर्णांक_delta_in_us;
	अचिन्हित पूर्णांक max_render_समय_in_us =
			in_out_vrr->max_duration_in_us - in_out_vrr->btr.margin_in_us;

	/* Program BTR */
	अगर ((last_render_समय_in_us + in_out_vrr->btr.margin_in_us / 2) < max_render_समय_in_us) अणु
		/* Exit Below the Range */
		अगर (in_out_vrr->btr.btr_active) अणु
			in_out_vrr->btr.frame_counter = 0;
			in_out_vrr->btr.btr_active = false;
		पूर्ण
	पूर्ण अन्यथा अगर (last_render_समय_in_us > (max_render_समय_in_us + in_out_vrr->btr.margin_in_us / 2)) अणु
		/* Enter Below the Range */
		अगर (!in_out_vrr->btr.btr_active) अणु
			in_out_vrr->btr.btr_active = true;
		पूर्ण
	पूर्ण

	/* BTR set to "not active" so disengage */
	अगर (!in_out_vrr->btr.btr_active) अणु
		in_out_vrr->btr.inserted_duration_in_us = 0;
		in_out_vrr->btr.frames_to_insert = 0;
		in_out_vrr->btr.frame_counter = 0;

		/* Restore FreeSync */
		in_out_vrr->adjust.v_total_min =
			mod_मुक्तsync_calc_v_total_from_refresh(stream,
				in_out_vrr->max_refresh_in_uhz);
		in_out_vrr->adjust.v_total_max =
			mod_मुक्तsync_calc_v_total_from_refresh(stream,
				in_out_vrr->min_refresh_in_uhz);
	/* BTR set to "active" so engage */
	पूर्ण अन्यथा अणु

		/* Calculate number of midPoपूर्णांक frames that could fit within
		 * the render समय पूर्णांकerval - take उच्चमान of this value
		 */
		mid_poपूर्णांक_frames_उच्चमान = (last_render_समय_in_us +
				in_out_vrr->btr.mid_poपूर्णांक_in_us - 1) /
					in_out_vrr->btr.mid_poपूर्णांक_in_us;

		अगर (mid_poपूर्णांक_frames_उच्चमान > 0) अणु
			frame_समय_in_us = last_render_समय_in_us /
				mid_poपूर्णांक_frames_उच्चमान;
			delta_from_mid_poपूर्णांक_in_us_1 =
				(in_out_vrr->btr.mid_poपूर्णांक_in_us >
				frame_समय_in_us) ?
				(in_out_vrr->btr.mid_poपूर्णांक_in_us - frame_समय_in_us) :
				(frame_समय_in_us - in_out_vrr->btr.mid_poपूर्णांक_in_us);
		पूर्ण

		/* Calculate number of midPoपूर्णांक frames that could fit within
		 * the render समय पूर्णांकerval - take न्यूनमान of this value
		 */
		mid_poपूर्णांक_frames_न्यूनमान = last_render_समय_in_us /
				in_out_vrr->btr.mid_poपूर्णांक_in_us;

		अगर (mid_poपूर्णांक_frames_न्यूनमान > 0) अणु

			frame_समय_in_us = last_render_समय_in_us /
				mid_poपूर्णांक_frames_न्यूनमान;
			delta_from_mid_poपूर्णांक_in_us_2 =
				(in_out_vrr->btr.mid_poपूर्णांक_in_us >
				frame_समय_in_us) ?
				(in_out_vrr->btr.mid_poपूर्णांक_in_us - frame_समय_in_us) :
				(frame_समय_in_us - in_out_vrr->btr.mid_poपूर्णांक_in_us);
		पूर्ण

		/* Choose number of frames to insert based on how बंद it
		 * can get to the mid poपूर्णांक of the variable range.
		 *  - Delta क्रम CEIL: delta_from_mid_poपूर्णांक_in_us_1
		 *  - Delta क्रम FLOOR: delta_from_mid_poपूर्णांक_in_us_2
		 */
		अगर ((last_render_समय_in_us / mid_poपूर्णांक_frames_उच्चमान) < in_out_vrr->min_duration_in_us) अणु
			/* Check क्रम out of range.
			 * If using CEIL produces a value that is out of range,
			 * then we are क्रमced to use FLOOR.
			 */
			frames_to_insert = mid_poपूर्णांक_frames_न्यूनमान;
		पूर्ण अन्यथा अगर (mid_poपूर्णांक_frames_न्यूनमान < 2) अणु
			/* Check अगर FLOOR would result in non-LFC. In this हाल
			 * choose to use CEIL
			 */
			frames_to_insert = mid_poपूर्णांक_frames_उच्चमान;
		पूर्ण अन्यथा अगर (delta_from_mid_poपूर्णांक_in_us_1 < delta_from_mid_poपूर्णांक_in_us_2) अणु
			/* If choosing CEIL results in a frame duration that is
			 * बंदr to the mid poपूर्णांक of the range.
			 * Choose CEIL
			 */
			frames_to_insert = mid_poपूर्णांक_frames_उच्चमान;
		पूर्ण अन्यथा अणु
			/* If choosing FLOOR results in a frame duration that is
			 * बंदr to the mid poपूर्णांक of the range.
			 * Choose FLOOR
			 */
			frames_to_insert = mid_poपूर्णांक_frames_न्यूनमान;
		पूर्ण

		/* Prefer current frame multiplier when BTR is enabled unless it drअगरts
		 * too far from the midpoपूर्णांक
		 */
		अगर (delta_from_mid_poपूर्णांक_in_us_1 < delta_from_mid_poपूर्णांक_in_us_2) अणु
			delta_from_mid_poपूर्णांक_delta_in_us = delta_from_mid_poपूर्णांक_in_us_2 -
					delta_from_mid_poपूर्णांक_in_us_1;
		पूर्ण अन्यथा अणु
			delta_from_mid_poपूर्णांक_delta_in_us = delta_from_mid_poपूर्णांक_in_us_1 -
					delta_from_mid_poपूर्णांक_in_us_2;
		पूर्ण
		अगर (in_out_vrr->btr.frames_to_insert != 0 &&
				delta_from_mid_poपूर्णांक_delta_in_us < BTR_DRIFT_MARGIN) अणु
			अगर (((last_render_समय_in_us / in_out_vrr->btr.frames_to_insert) <
					max_render_समय_in_us) &&
				((last_render_समय_in_us / in_out_vrr->btr.frames_to_insert) >
					in_out_vrr->min_duration_in_us))
				frames_to_insert = in_out_vrr->btr.frames_to_insert;
		पूर्ण

		/* Either we've calculated the number of frames to insert,
		 * or we need to insert min duration frames
		 */
		अगर (last_render_समय_in_us / frames_to_insert <
				in_out_vrr->min_duration_in_us)अणु
			frames_to_insert -= (frames_to_insert > 1) ?
					1 : 0;
		पूर्ण

		अगर (frames_to_insert > 0)
			inserted_frame_duration_in_us = last_render_समय_in_us /
							frames_to_insert;

		अगर (inserted_frame_duration_in_us < in_out_vrr->min_duration_in_us)
			inserted_frame_duration_in_us = in_out_vrr->min_duration_in_us;

		/* Cache the calculated variables */
		in_out_vrr->btr.inserted_duration_in_us =
			inserted_frame_duration_in_us;
		in_out_vrr->btr.frames_to_insert = frames_to_insert;
		in_out_vrr->btr.frame_counter = frames_to_insert;
	पूर्ण
पूर्ण

अटल व्योम apply_fixed_refresh(काष्ठा core_मुक्तsync *core_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक last_render_समय_in_us,
		काष्ठा mod_vrr_params *in_out_vrr)
अणु
	bool update = false;
	अचिन्हित पूर्णांक max_render_समय_in_us = in_out_vrr->max_duration_in_us;

	/* Compute the निकास refresh rate and निकास frame duration */
	अचिन्हित पूर्णांक निकास_refresh_rate_in_milli_hz = ((1000000000/max_render_समय_in_us)
			+ (1000*FIXED_REFRESH_EXIT_MARGIN_IN_HZ));
	अचिन्हित पूर्णांक निकास_frame_duration_in_us = 1000000000/निकास_refresh_rate_in_milli_hz;

	अगर (last_render_समय_in_us < निकास_frame_duration_in_us) अणु
		/* Exit Fixed Refresh mode */
		अगर (in_out_vrr->fixed.fixed_active) अणु
			in_out_vrr->fixed.frame_counter++;

			अगर (in_out_vrr->fixed.frame_counter >
					FIXED_REFRESH_EXIT_FRAME_COUNT) अणु
				in_out_vrr->fixed.frame_counter = 0;
				in_out_vrr->fixed.fixed_active = false;
				in_out_vrr->fixed.target_refresh_in_uhz = 0;
				update = true;
			पूर्ण
		पूर्ण अन्यथा
			in_out_vrr->fixed.frame_counter = 0;
	पूर्ण अन्यथा अगर (last_render_समय_in_us > max_render_समय_in_us) अणु
		/* Enter Fixed Refresh mode */
		अगर (!in_out_vrr->fixed.fixed_active) अणु
			in_out_vrr->fixed.frame_counter++;

			अगर (in_out_vrr->fixed.frame_counter >
					FIXED_REFRESH_ENTER_FRAME_COUNT) अणु
				in_out_vrr->fixed.frame_counter = 0;
				in_out_vrr->fixed.fixed_active = true;
				in_out_vrr->fixed.target_refresh_in_uhz =
						in_out_vrr->max_refresh_in_uhz;
				update = true;
			पूर्ण
		पूर्ण अन्यथा
			in_out_vrr->fixed.frame_counter = 0;
	पूर्ण

	अगर (update) अणु
		अगर (in_out_vrr->fixed.fixed_active) अणु
			in_out_vrr->adjust.v_total_min =
				mod_मुक्तsync_calc_v_total_from_refresh(
				stream, in_out_vrr->max_refresh_in_uhz);
			in_out_vrr->adjust.v_total_max =
					in_out_vrr->adjust.v_total_min;
		पूर्ण अन्यथा अणु
			in_out_vrr->adjust.v_total_min =
				mod_मुक्तsync_calc_v_total_from_refresh(stream,
					in_out_vrr->max_refresh_in_uhz);
			in_out_vrr->adjust.v_total_max =
				mod_मुक्तsync_calc_v_total_from_refresh(stream,
					in_out_vrr->min_refresh_in_uhz);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool vrr_settings_require_update(काष्ठा core_मुक्तsync *core_मुक्तsync,
		काष्ठा mod_मुक्तsync_config *in_config,
		अचिन्हित पूर्णांक min_refresh_in_uhz,
		अचिन्हित पूर्णांक max_refresh_in_uhz,
		काष्ठा mod_vrr_params *in_vrr)
अणु
	अगर (in_vrr->state != in_config->state) अणु
		वापस true;
	पूर्ण अन्यथा अगर (in_vrr->state == VRR_STATE_ACTIVE_FIXED &&
			in_vrr->fixed.target_refresh_in_uhz !=
					in_config->fixed_refresh_in_uhz) अणु
		वापस true;
	पूर्ण अन्यथा अगर (in_vrr->min_refresh_in_uhz != min_refresh_in_uhz) अणु
		वापस true;
	पूर्ण अन्यथा अगर (in_vrr->max_refresh_in_uhz != max_refresh_in_uhz) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool mod_मुक्तsync_get_vmin_vmax(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक *vmin,
		अचिन्हित पूर्णांक *vmax)
अणु
	*vmin = stream->adjust.v_total_min;
	*vmax = stream->adjust.v_total_max;

	वापस true;
पूर्ण

bool mod_मुक्तsync_get_v_position(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक *nom_v_pos,
		अचिन्हित पूर्णांक *v_pos)
अणु
	काष्ठा core_मुक्तsync *core_मुक्तsync = शून्य;
	काष्ठा crtc_position position;

	अगर (mod_मुक्तsync == शून्य)
		वापस false;

	core_मुक्तsync = MOD_FREESYNC_TO_CORE(mod_मुक्तsync);

	अगर (dc_stream_get_crtc_position(core_मुक्तsync->dc, &stream, 1,
					&position.vertical_count,
					&position.nominal_vcount)) अणु

		*nom_v_pos = position.nominal_vcount;
		*v_pos = position.vertical_count;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम build_vrr_infopacket_data_v1(स्थिर काष्ठा mod_vrr_params *vrr,
		काष्ठा dc_info_packet *infopacket)
अणु
	/* PB1 = 0x1A (24bit AMD IEEE OUI (0x00001A) - Byte 0) */
	infopacket->sb[1] = 0x1A;

	/* PB2 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 1) */
	infopacket->sb[2] = 0x00;

	/* PB3 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 2) */
	infopacket->sb[3] = 0x00;

	/* PB4 = Reserved */

	/* PB5 = Reserved */

	/* PB6 = [Bits 7:3 = Reserved] */

	/* PB6 = [Bit 0 = FreeSync Supported] */
	अगर (vrr->state != VRR_STATE_UNSUPPORTED)
		infopacket->sb[6] |= 0x01;

	/* PB6 = [Bit 1 = FreeSync Enabled] */
	अगर (vrr->state != VRR_STATE_DISABLED &&
			vrr->state != VRR_STATE_UNSUPPORTED)
		infopacket->sb[6] |= 0x02;

	/* PB6 = [Bit 2 = FreeSync Active] */
	अगर (vrr->state != VRR_STATE_DISABLED &&
			vrr->state != VRR_STATE_UNSUPPORTED)
		infopacket->sb[6] |= 0x04;

	// For v1 & 2 infoframes program nominal अगर non-fs mode, otherwise full range
	/* PB7 = FreeSync Minimum refresh rate (Hz) */
	अगर (vrr->state == VRR_STATE_ACTIVE_VARIABLE ||
			vrr->state == VRR_STATE_ACTIVE_FIXED) अणु
		infopacket->sb[7] = (अचिन्हित अक्षर)((vrr->min_refresh_in_uhz + 500000) / 1000000);
	पूर्ण अन्यथा अणु
		infopacket->sb[7] = (अचिन्हित अक्षर)((vrr->max_refresh_in_uhz + 500000) / 1000000);
	पूर्ण

	/* PB8 = FreeSync Maximum refresh rate (Hz)
	 * Note: We should never go above the field rate of the mode timing set.
	 */
	infopacket->sb[8] = (अचिन्हित अक्षर)((vrr->max_refresh_in_uhz + 500000) / 1000000);

	/* FreeSync HDR */
	infopacket->sb[9] = 0;
	infopacket->sb[10] = 0;
पूर्ण

अटल व्योम build_vrr_infopacket_data_v3(स्थिर काष्ठा mod_vrr_params *vrr,
		काष्ठा dc_info_packet *infopacket)
अणु
	अचिन्हित पूर्णांक min_refresh;
	अचिन्हित पूर्णांक max_refresh;
	अचिन्हित पूर्णांक fixed_refresh;
	अचिन्हित पूर्णांक min_programmed;
	अचिन्हित पूर्णांक max_programmed;

	/* PB1 = 0x1A (24bit AMD IEEE OUI (0x00001A) - Byte 0) */
	infopacket->sb[1] = 0x1A;

	/* PB2 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 1) */
	infopacket->sb[2] = 0x00;

	/* PB3 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 2) */
	infopacket->sb[3] = 0x00;

	/* PB4 = Reserved */

	/* PB5 = Reserved */

	/* PB6 = [Bits 7:3 = Reserved] */

	/* PB6 = [Bit 0 = FreeSync Supported] */
	अगर (vrr->state != VRR_STATE_UNSUPPORTED)
		infopacket->sb[6] |= 0x01;

	/* PB6 = [Bit 1 = FreeSync Enabled] */
	अगर (vrr->state != VRR_STATE_DISABLED &&
			vrr->state != VRR_STATE_UNSUPPORTED)
		infopacket->sb[6] |= 0x02;

	/* PB6 = [Bit 2 = FreeSync Active] */
	अगर (vrr->state == VRR_STATE_ACTIVE_VARIABLE ||
			vrr->state == VRR_STATE_ACTIVE_FIXED)
		infopacket->sb[6] |= 0x04;

	min_refresh = (vrr->min_refresh_in_uhz + 500000) / 1000000;
	max_refresh = (vrr->max_refresh_in_uhz + 500000) / 1000000;
	fixed_refresh = (vrr->fixed_refresh_in_uhz + 500000) / 1000000;

	min_programmed = (vrr->state == VRR_STATE_ACTIVE_FIXED) ? fixed_refresh :
			(vrr->state == VRR_STATE_ACTIVE_VARIABLE) ? min_refresh :
			(vrr->state == VRR_STATE_INACTIVE) ? min_refresh :
			max_refresh; // Non-fs हाल, program nominal range

	max_programmed = (vrr->state == VRR_STATE_ACTIVE_FIXED) ? fixed_refresh :
			(vrr->state == VRR_STATE_ACTIVE_VARIABLE) ? max_refresh :
			max_refresh;// Non-fs हाल, program nominal range

	/* PB7 = FreeSync Minimum refresh rate (Hz) */
	infopacket->sb[7] = min_programmed & 0xFF;

	/* PB8 = FreeSync Maximum refresh rate (Hz) */
	infopacket->sb[8] = max_programmed & 0xFF;

	/* PB11 : MSB FreeSync Minimum refresh rate [Hz] - bits 9:8 */
	infopacket->sb[11] = (min_programmed >> 8) & 0x03;

	/* PB12 : MSB FreeSync Maximum refresh rate [Hz] - bits 9:8 */
	infopacket->sb[12] = (max_programmed >> 8) & 0x03;

	/* PB16 : Reserved bits 7:1, FixedRate bit 0 */
	infopacket->sb[16] = (vrr->state == VRR_STATE_ACTIVE_FIXED) ? 1 : 0;

	//FreeSync HDR
	infopacket->sb[9] = 0;
	infopacket->sb[10] = 0;
पूर्ण

अटल व्योम build_vrr_infopacket_fs2_data(क्रमागत color_transfer_func app_tf,
		काष्ठा dc_info_packet *infopacket)
अणु
	अगर (app_tf != TRANSFER_FUNC_UNKNOWN) अणु
		infopacket->valid = true;

		infopacket->sb[6] |= 0x08;  // PB6 = [Bit 3 = Native Color Active]

		अगर (app_tf == TRANSFER_FUNC_GAMMA_22) अणु
			infopacket->sb[9] |= 0x04;  // PB6 = [Bit 2 = Gamma 2.2 EOTF Active]
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम build_vrr_infopacket_header_v1(क्रमागत संकेत_type संकेत,
		काष्ठा dc_info_packet *infopacket,
		अचिन्हित पूर्णांक *payload_size)
अणु
	अगर (dc_is_hdmi_संकेत(संकेत)) अणु

		/* HEADER */

		/* HB0  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb0 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB1  = Version = 0x01 */
		infopacket->hb1 = 0x01;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Length = 0x08] */
		infopacket->hb2 = 0x08;

		*payload_size = 0x08;

	पूर्ण अन्यथा अगर (dc_is_dp_संकेत(संकेत)) अणु

		/* HEADER */

		/* HB0  = Secondary-data Packet ID = 0 - Only non-zero
		 *	  when used to associate audio related info packets
		 */
		infopacket->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb1 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Least signअगरicant eight bits -
		 *	  For INFOFRAME, the value must be 1Bh]
		 */
		infopacket->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFRAME SDP Version Number = 0x1]
		 *	  [Bits 1:0 = Most signअगरicant two bits = 0x00]
		 */
		infopacket->hb3 = 0x04;

		*payload_size = 0x1B;
	पूर्ण
पूर्ण

अटल व्योम build_vrr_infopacket_header_v2(क्रमागत संकेत_type संकेत,
		काष्ठा dc_info_packet *infopacket,
		अचिन्हित पूर्णांक *payload_size)
अणु
	अगर (dc_is_hdmi_संकेत(संकेत)) अणु

		/* HEADER */

		/* HB0  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb0 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB1  = Version = 0x02 */
		infopacket->hb1 = 0x02;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Length = 0x09] */
		infopacket->hb2 = 0x09;

		*payload_size = 0x0A;

	पूर्ण अन्यथा अगर (dc_is_dp_संकेत(संकेत)) अणु

		/* HEADER */

		/* HB0  = Secondary-data Packet ID = 0 - Only non-zero
		 *	  when used to associate audio related info packets
		 */
		infopacket->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb1 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Least signअगरicant eight bits -
		 *	  For INFOFRAME, the value must be 1Bh]
		 */
		infopacket->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFRAME SDP Version Number = 0x2]
		 *	  [Bits 1:0 = Most signअगरicant two bits = 0x00]
		 */
		infopacket->hb3 = 0x08;

		*payload_size = 0x1B;
	पूर्ण
पूर्ण

अटल व्योम build_vrr_infopacket_header_v3(क्रमागत संकेत_type संकेत,
		काष्ठा dc_info_packet *infopacket,
		अचिन्हित पूर्णांक *payload_size)
अणु
	अचिन्हित अक्षर version;

	version = 3;
	अगर (dc_is_hdmi_संकेत(संकेत)) अणु

		/* HEADER */

		/* HB0  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb0 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB1  = Version = 0x03 */
		infopacket->hb1 = version;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Length] */
		*payload_size = 0x10;
		infopacket->hb2 = *payload_size - 1; //-1 क्रम checksum

	पूर्ण अन्यथा अगर (dc_is_dp_संकेत(संकेत)) अणु

		/* HEADER */

		/* HB0  = Secondary-data Packet ID = 0 - Only non-zero
		 *	  when used to associate audio related info packets
		 */
		infopacket->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb1 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Least signअगरicant eight bits -
		 *	  For INFOFRAME, the value must be 1Bh]
		 */
		infopacket->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFRAME SDP Version Number = 0x2]
		 *	  [Bits 1:0 = Most signअगरicant two bits = 0x00]
		 */

		infopacket->hb3 = (version & 0x3F) << 2;

		*payload_size = 0x1B;
	पूर्ण
पूर्ण

अटल व्योम build_vrr_infopacket_checksum(अचिन्हित पूर्णांक *payload_size,
		काष्ठा dc_info_packet *infopacket)
अणु
	/* Calculate checksum */
	अचिन्हित पूर्णांक idx = 0;
	अचिन्हित अक्षर checksum = 0;

	checksum += infopacket->hb0;
	checksum += infopacket->hb1;
	checksum += infopacket->hb2;
	checksum += infopacket->hb3;

	क्रम (idx = 1; idx <= *payload_size; idx++)
		checksum += infopacket->sb[idx];

	/* PB0 = Checksum (one byte complement) */
	infopacket->sb[0] = (अचिन्हित अक्षर)(0x100 - checksum);

	infopacket->valid = true;
पूर्ण

अटल व्योम build_vrr_infopacket_v1(क्रमागत संकेत_type संकेत,
		स्थिर काष्ठा mod_vrr_params *vrr,
		काष्ठा dc_info_packet *infopacket)
अणु
	/* SPD info packet क्रम FreeSync */
	अचिन्हित पूर्णांक payload_size = 0;

	build_vrr_infopacket_header_v1(संकेत, infopacket, &payload_size);
	build_vrr_infopacket_data_v1(vrr, infopacket);
	build_vrr_infopacket_checksum(&payload_size, infopacket);

	infopacket->valid = true;
पूर्ण

अटल व्योम build_vrr_infopacket_v2(क्रमागत संकेत_type संकेत,
		स्थिर काष्ठा mod_vrr_params *vrr,
		क्रमागत color_transfer_func app_tf,
		काष्ठा dc_info_packet *infopacket)
अणु
	अचिन्हित पूर्णांक payload_size = 0;

	build_vrr_infopacket_header_v2(संकेत, infopacket, &payload_size);
	build_vrr_infopacket_data_v1(vrr, infopacket);

	build_vrr_infopacket_fs2_data(app_tf, infopacket);

	build_vrr_infopacket_checksum(&payload_size, infopacket);

	infopacket->valid = true;
पूर्ण
#अगर_अघोषित TRIM_FSFT
अटल व्योम build_vrr_infopacket_fast_transport_data(
	bool ftActive,
	अचिन्हित पूर्णांक ftOutputRate,
	काष्ठा dc_info_packet *infopacket)
अणु
	/* PB9 : bit7 - fast transport Active*/
	अचिन्हित अक्षर activeBit = (ftActive) ? 1 << 7 : 0;

	infopacket->sb[1] &= ~activeBit;  //clear bit
	infopacket->sb[1] |=  activeBit;  //set bit

	/* PB13 : Target Output Pixel Rate [kHz] - bits 7:0  */
	infopacket->sb[13] = ftOutputRate & 0xFF;

	/* PB14 : Target Output Pixel Rate [kHz] - bits 15:8  */
	infopacket->sb[14] = (ftOutputRate >> 8) & 0xFF;

	/* PB15 : Target Output Pixel Rate [kHz] - bits 23:16  */
	infopacket->sb[15] = (ftOutputRate >> 16) & 0xFF;

पूर्ण
#पूर्ण_अगर

अटल व्योम build_vrr_infopacket_v3(क्रमागत संकेत_type संकेत,
		स्थिर काष्ठा mod_vrr_params *vrr,
#अगर_अघोषित TRIM_FSFT
		bool ftActive, अचिन्हित पूर्णांक ftOutputRate,
#पूर्ण_अगर
		क्रमागत color_transfer_func app_tf,
		काष्ठा dc_info_packet *infopacket)
अणु
	अचिन्हित पूर्णांक payload_size = 0;

	build_vrr_infopacket_header_v3(संकेत, infopacket, &payload_size);
	build_vrr_infopacket_data_v3(vrr, infopacket);

	build_vrr_infopacket_fs2_data(app_tf, infopacket);

#अगर_अघोषित TRIM_FSFT
	build_vrr_infopacket_fast_transport_data(
			ftActive,
			ftOutputRate,
			infopacket);
#पूर्ण_अगर

	build_vrr_infopacket_checksum(&payload_size, infopacket);

	infopacket->valid = true;
पूर्ण

अटल व्योम build_vrr_infopacket_sdp_v1_3(क्रमागत vrr_packet_type packet_type,
										काष्ठा dc_info_packet *infopacket)
अणु
	uपूर्णांक8_t idx = 0, size = 0;

	size = ((packet_type == PACKET_TYPE_FS_V1) ? 0x08 :
			(packet_type == PACKET_TYPE_FS_V3) ? 0x10 :
												0x09);

	क्रम (idx = infopacket->hb2; idx > 1; idx--) // Data Byte Count: 0x1B
		infopacket->sb[idx] = infopacket->sb[idx-1];

	infopacket->sb[1] = size;                         // Length
	infopacket->sb[0] = (infopacket->hb3 >> 2) & 0x3F;//Version
	infopacket->hb3   = (0x13 << 2);                  // Header,SDP 1.3
	infopacket->hb2   = 0x1D;
पूर्ण

व्योम mod_मुक्तsync_build_vrr_infopacket(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		स्थिर काष्ठा mod_vrr_params *vrr,
		क्रमागत vrr_packet_type packet_type,
		क्रमागत color_transfer_func app_tf,
		काष्ठा dc_info_packet *infopacket,
		bool pack_sdp_v1_3)
अणु
	/* SPD info packet क्रम FreeSync
	 * VTEM info packet क्रम HdmiVRR
	 * Check अगर Freesync is supported. Return अगर false. If true,
	 * set the corresponding bit in the info packet
	 */
	अगर (!vrr->send_info_frame)
		वापस;

	चयन (packet_type) अणु
	हाल PACKET_TYPE_FS_V3:
#अगर_अघोषित TRIM_FSFT
		// always populate with pixel rate.
		build_vrr_infopacket_v3(
				stream->संकेत, vrr,
				stream->timing.flags.FAST_TRANSPORT,
				(stream->timing.flags.FAST_TRANSPORT) ?
						stream->timing.fast_transport_output_rate_100hz :
						stream->timing.pix_clk_100hz,
				app_tf, infopacket);
#अन्यथा
		build_vrr_infopacket_v3(stream->संकेत, vrr, app_tf, infopacket);
#पूर्ण_अगर
		अवरोध;
	हाल PACKET_TYPE_FS_V2:
		build_vrr_infopacket_v2(stream->संकेत, vrr, app_tf, infopacket);
		अवरोध;
	हाल PACKET_TYPE_VRR:
	हाल PACKET_TYPE_FS_V1:
	शेष:
		build_vrr_infopacket_v1(stream->संकेत, vrr, infopacket);
	पूर्ण

	अगर (true == pack_sdp_v1_3 &&
		true == dc_is_dp_संकेत(stream->संकेत) &&
		packet_type != PACKET_TYPE_VRR &&
		packet_type != PACKET_TYPE_VTEM)
		build_vrr_infopacket_sdp_v1_3(packet_type, infopacket);
पूर्ण

व्योम mod_मुक्तsync_build_vrr_params(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा mod_मुक्तsync_config *in_config,
		काष्ठा mod_vrr_params *in_out_vrr)
अणु
	काष्ठा core_मुक्तsync *core_मुक्तsync = शून्य;
	अचिन्हित दीर्घ दीर्घ nominal_field_rate_in_uhz = 0;
	अचिन्हित दीर्घ दीर्घ rounded_nominal_in_uhz = 0;
	अचिन्हित पूर्णांक refresh_range = 0;
	अचिन्हित दीर्घ दीर्घ min_refresh_in_uhz = 0;
	अचिन्हित दीर्घ दीर्घ max_refresh_in_uhz = 0;

	अगर (mod_मुक्तsync == शून्य)
		वापस;

	core_मुक्तsync = MOD_FREESYNC_TO_CORE(mod_मुक्तsync);

	/* Calculate nominal field rate क्रम stream */
	nominal_field_rate_in_uhz =
			mod_मुक्तsync_calc_nominal_field_rate(stream);

	min_refresh_in_uhz = in_config->min_refresh_in_uhz;
	max_refresh_in_uhz = in_config->max_refresh_in_uhz;

	/* Full range may be larger than current video timing, so cap at nominal */
	अगर (max_refresh_in_uhz > nominal_field_rate_in_uhz)
		max_refresh_in_uhz = nominal_field_rate_in_uhz;

	/* Full range may be larger than current video timing, so cap at nominal */
	अगर (min_refresh_in_uhz > max_refresh_in_uhz)
		min_refresh_in_uhz = max_refresh_in_uhz;

	/* If a monitor reports exactly max refresh of 2x of min, enक्रमce it on nominal */
	rounded_nominal_in_uhz =
			भाग_u64(nominal_field_rate_in_uhz + 50000, 100000) * 100000;
	अगर (in_config->max_refresh_in_uhz == (2 * in_config->min_refresh_in_uhz) &&
		in_config->max_refresh_in_uhz == rounded_nominal_in_uhz)
		min_refresh_in_uhz = भाग_u64(nominal_field_rate_in_uhz, 2);

	अगर (!vrr_settings_require_update(core_मुक्तsync,
			in_config, (अचिन्हित पूर्णांक)min_refresh_in_uhz, (अचिन्हित पूर्णांक)max_refresh_in_uhz,
			in_out_vrr))
		वापस;

	in_out_vrr->state = in_config->state;
	in_out_vrr->send_info_frame = in_config->vsअगर_supported;

	अगर (in_config->state == VRR_STATE_UNSUPPORTED) अणु
		in_out_vrr->state = VRR_STATE_UNSUPPORTED;
		in_out_vrr->supported = false;
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;

		वापस;

	पूर्ण अन्यथा अणु
		in_out_vrr->min_refresh_in_uhz = (अचिन्हित पूर्णांक)min_refresh_in_uhz;
		in_out_vrr->max_duration_in_us =
				calc_duration_in_us_from_refresh_in_uhz(
						(अचिन्हित पूर्णांक)min_refresh_in_uhz);

		in_out_vrr->max_refresh_in_uhz = (अचिन्हित पूर्णांक)max_refresh_in_uhz;
		in_out_vrr->min_duration_in_us =
				calc_duration_in_us_from_refresh_in_uhz(
						(अचिन्हित पूर्णांक)max_refresh_in_uhz);

		अगर (in_config->state == VRR_STATE_ACTIVE_FIXED)
			in_out_vrr->fixed_refresh_in_uhz = in_config->fixed_refresh_in_uhz;
		अन्यथा
			in_out_vrr->fixed_refresh_in_uhz = 0;

		refresh_range = भाग_u64(in_out_vrr->max_refresh_in_uhz + 500000, 1000000) -
+				भाग_u64(in_out_vrr->min_refresh_in_uhz + 500000, 1000000);

		in_out_vrr->supported = true;
	पूर्ण

	in_out_vrr->fixed.ramping_active = in_config->ramping;

	in_out_vrr->btr.btr_enabled = in_config->btr;

	अगर (in_out_vrr->max_refresh_in_uhz < (2 * in_out_vrr->min_refresh_in_uhz))
		in_out_vrr->btr.btr_enabled = false;
	अन्यथा अणु
		in_out_vrr->btr.margin_in_us = in_out_vrr->max_duration_in_us -
				2 * in_out_vrr->min_duration_in_us;
		अगर (in_out_vrr->btr.margin_in_us > BTR_MAX_MARGIN)
			in_out_vrr->btr.margin_in_us = BTR_MAX_MARGIN;
	पूर्ण

	in_out_vrr->btr.btr_active = false;
	in_out_vrr->btr.inserted_duration_in_us = 0;
	in_out_vrr->btr.frames_to_insert = 0;
	in_out_vrr->btr.frame_counter = 0;
	in_out_vrr->fixed.fixed_active = false;
	in_out_vrr->fixed.target_refresh_in_uhz = 0;

	in_out_vrr->btr.mid_poपूर्णांक_in_us =
				(in_out_vrr->min_duration_in_us +
				 in_out_vrr->max_duration_in_us) / 2;

	अगर (in_out_vrr->state == VRR_STATE_UNSUPPORTED) अणु
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	पूर्ण अन्यथा अगर (in_out_vrr->state == VRR_STATE_DISABLED) अणु
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	पूर्ण अन्यथा अगर (in_out_vrr->state == VRR_STATE_INACTIVE) अणु
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	पूर्ण अन्यथा अगर (in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE &&
			refresh_range >= MIN_REFRESH_RANGE) अणु

		in_out_vrr->adjust.v_total_min =
			mod_मुक्तsync_calc_v_total_from_refresh(stream,
				in_out_vrr->max_refresh_in_uhz);
		in_out_vrr->adjust.v_total_max =
			mod_मुक्तsync_calc_v_total_from_refresh(stream,
				in_out_vrr->min_refresh_in_uhz);
	पूर्ण अन्यथा अगर (in_out_vrr->state == VRR_STATE_ACTIVE_FIXED) अणु
		in_out_vrr->fixed.target_refresh_in_uhz =
				in_out_vrr->fixed_refresh_in_uhz;
		अगर (in_out_vrr->fixed.ramping_active &&
				in_out_vrr->fixed.fixed_active) अणु
			/* Do not update vtotals अगर ramping is alपढ़ोy active
			 * in order to जारी ramp from current refresh.
			 */
			in_out_vrr->fixed.fixed_active = true;
		पूर्ण अन्यथा अणु
			in_out_vrr->fixed.fixed_active = true;
			in_out_vrr->adjust.v_total_min =
				mod_मुक्तsync_calc_v_total_from_refresh(stream,
					in_out_vrr->fixed.target_refresh_in_uhz);
			in_out_vrr->adjust.v_total_max =
				in_out_vrr->adjust.v_total_min;
		पूर्ण
	पूर्ण अन्यथा अणु
		in_out_vrr->state = VRR_STATE_INACTIVE;
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	पूर्ण
पूर्ण

व्योम mod_मुक्तsync_handle_preflip(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_plane_state *plane,
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक curr_समय_stamp_in_us,
		काष्ठा mod_vrr_params *in_out_vrr)
अणु
	काष्ठा core_मुक्तsync *core_मुक्तsync = शून्य;
	अचिन्हित पूर्णांक last_render_समय_in_us = 0;
	अचिन्हित पूर्णांक average_render_समय_in_us = 0;

	अगर (mod_मुक्तsync == शून्य)
		वापस;

	core_मुक्तsync = MOD_FREESYNC_TO_CORE(mod_मुक्तsync);

	अगर (in_out_vrr->supported &&
			in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE) अणु
		अचिन्हित पूर्णांक i = 0;
		अचिन्हित पूर्णांक oldest_index = plane->समय.index + 1;

		अगर (oldest_index >= DC_PLANE_UPDATE_TIMES_MAX)
			oldest_index = 0;

		last_render_समय_in_us = curr_समय_stamp_in_us -
				plane->समय.prev_update_समय_in_us;

		/* Sum off all entries except oldest one */
		क्रम (i = 0; i < DC_PLANE_UPDATE_TIMES_MAX; i++) अणु
			average_render_समय_in_us +=
					plane->समय.समय_elapsed_in_us[i];
		पूर्ण
		average_render_समय_in_us -=
				plane->समय.समय_elapsed_in_us[oldest_index];

		/* Add render समय क्रम current flip */
		average_render_समय_in_us += last_render_समय_in_us;
		average_render_समय_in_us /= DC_PLANE_UPDATE_TIMES_MAX;

		अगर (in_out_vrr->btr.btr_enabled) अणु
			apply_below_the_range(core_मुक्तsync,
					stream,
					last_render_समय_in_us,
					in_out_vrr);
		पूर्ण अन्यथा अणु
			apply_fixed_refresh(core_मुक्तsync,
				stream,
				last_render_समय_in_us,
				in_out_vrr);
		पूर्ण

	पूर्ण
पूर्ण

व्योम mod_मुक्तsync_handle_v_update(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा mod_vrr_params *in_out_vrr)
अणु
	काष्ठा core_मुक्तsync *core_मुक्तsync = शून्य;

	अगर ((mod_मुक्तsync == शून्य) || (stream == शून्य) || (in_out_vrr == शून्य))
		वापस;

	core_मुक्तsync = MOD_FREESYNC_TO_CORE(mod_मुक्तsync);

	अगर (in_out_vrr->supported == false)
		वापस;

	/* Below the Range Logic */

	/* Only execute अगर in fullscreen mode */
	अगर (in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE &&
					in_out_vrr->btr.btr_active) अणु
		/* TODO: pass in flag क्रम Pre-DCE12 ASIC
		 * in order क्रम frame variable duration to take affect,
		 * it needs to be करोne one VSYNC early, which is at
		 * frameCounter == 1.
		 * For DCE12 and newer updates to V_TOTAL_MIN/MAX
		 * will take affect on current frame
		 */
		अगर (in_out_vrr->btr.frames_to_insert ==
				in_out_vrr->btr.frame_counter) अणु
			in_out_vrr->adjust.v_total_min =
				calc_v_total_from_duration(stream,
				in_out_vrr,
				in_out_vrr->btr.inserted_duration_in_us);
			in_out_vrr->adjust.v_total_max =
				in_out_vrr->adjust.v_total_min;
		पूर्ण

		अगर (in_out_vrr->btr.frame_counter > 0)
			in_out_vrr->btr.frame_counter--;

		/* Restore FreeSync */
		अगर (in_out_vrr->btr.frame_counter == 0) अणु
			in_out_vrr->adjust.v_total_min =
				mod_मुक्तsync_calc_v_total_from_refresh(stream,
				in_out_vrr->max_refresh_in_uhz);
			in_out_vrr->adjust.v_total_max =
				mod_मुक्तsync_calc_v_total_from_refresh(stream,
				in_out_vrr->min_refresh_in_uhz);
		पूर्ण
	पूर्ण

	/* If in fullscreen मुक्तsync mode or in video, करो not program
	 * अटल screen ramp values
	 */
	अगर (in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE)
		in_out_vrr->fixed.ramping_active = false;

	/* Gradual Static Screen Ramping Logic
	 * Execute अगर ramp is active and user enabled मुक्तsync अटल screen
	 */
	अगर (in_out_vrr->state == VRR_STATE_ACTIVE_FIXED &&
				in_out_vrr->fixed.ramping_active) अणु
		update_v_total_क्रम_अटल_ramp(
				core_मुक्तsync, stream, in_out_vrr);
	पूर्ण
पूर्ण

व्योम mod_मुक्तsync_get_settings(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा mod_vrr_params *vrr,
		अचिन्हित पूर्णांक *v_total_min, अचिन्हित पूर्णांक *v_total_max,
		अचिन्हित पूर्णांक *event_triggers,
		अचिन्हित पूर्णांक *winकरोw_min, अचिन्हित पूर्णांक *winकरोw_max,
		अचिन्हित पूर्णांक *lfc_mid_poपूर्णांक_in_us,
		अचिन्हित पूर्णांक *inserted_frames,
		अचिन्हित पूर्णांक *inserted_duration_in_us)
अणु
	अगर (mod_मुक्तsync == शून्य)
		वापस;

	अगर (vrr->supported) अणु
		*v_total_min = vrr->adjust.v_total_min;
		*v_total_max = vrr->adjust.v_total_max;
		*event_triggers = 0;
		*lfc_mid_poपूर्णांक_in_us = vrr->btr.mid_poपूर्णांक_in_us;
		*inserted_frames = vrr->btr.frames_to_insert;
		*inserted_duration_in_us = vrr->btr.inserted_duration_in_us;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ दीर्घ mod_मुक्तsync_calc_nominal_field_rate(
			स्थिर काष्ठा dc_stream_state *stream)
अणु
	अचिन्हित दीर्घ दीर्घ nominal_field_rate_in_uhz = 0;
	अचिन्हित पूर्णांक total = stream->timing.h_total * stream->timing.v_total;

	/* Calculate nominal field rate क्रम stream, rounded up to nearest पूर्णांकeger */
	nominal_field_rate_in_uhz = stream->timing.pix_clk_100hz;
	nominal_field_rate_in_uhz *= 100000000ULL;

	nominal_field_rate_in_uhz =	भाग_u64(nominal_field_rate_in_uhz, total);

	वापस nominal_field_rate_in_uhz;
पूर्ण

अचिन्हित दीर्घ दीर्घ mod_मुक्तsync_calc_field_rate_from_timing(
		अचिन्हित पूर्णांक vtotal, अचिन्हित पूर्णांक htotal, अचिन्हित पूर्णांक pix_clk)
अणु
	अचिन्हित दीर्घ दीर्घ field_rate_in_uhz = 0;
	अचिन्हित पूर्णांक total = htotal * vtotal;

	/* Calculate nominal field rate क्रम stream, rounded up to nearest पूर्णांकeger */
	field_rate_in_uhz = pix_clk;
	field_rate_in_uhz *= 1000000ULL;

	field_rate_in_uhz =	भाग_u64(field_rate_in_uhz, total);

	वापस field_rate_in_uhz;
पूर्ण

bool mod_मुक्तsync_is_valid_range(uपूर्णांक32_t min_refresh_cap_in_uhz,
		uपूर्णांक32_t max_refresh_cap_in_uhz,
		uपूर्णांक32_t nominal_field_rate_in_uhz) 
अणु

	/* Typically nominal refresh calculated can have some fractional part.
	 * Allow क्रम some rounding error of actual video timing by taking न्यूनमान
	 * of caps and request. Round the nominal refresh rate.
	 *
	 * Dividing will convert everything to units in Hz although input
	 * variable name is in uHz!
	 *
	 * Also note, this takes care of rounding error on the nominal refresh
	 * so by rounding error we only expect it to be off by a small amount,
	 * such as < 0.1 Hz. i.e. 143.9xxx or 144.1xxx.
	 *
	 * Example 1. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Request Min = 40 Hz, Max = 144 Hz
	 *                    Nominal = 143.5x Hz rounded to 144 Hz
	 *            This function should allow this as valid request
	 *
	 * Example 2. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Request Min = 40 Hz, Max = 144 Hz
	 *                    Nominal = 144.4x Hz rounded to 144 Hz
	 *            This function should allow this as valid request
	 *
	 * Example 3. Caps    Min = 40 Hz, Max = 144 Hz
	 *            Request Min = 40 Hz, Max = 144 Hz
	 *                    Nominal = 120.xx Hz rounded to 120 Hz
	 *            This function should वापस NOT valid since the requested
	 *            max is greater than current timing's nominal
	 *
	 * Example 4. Caps    Min = 40 Hz, Max = 120 Hz
	 *            Request Min = 40 Hz, Max = 120 Hz
	 *                    Nominal = 144.xx Hz rounded to 144 Hz
	 *            This function should वापस NOT valid since the nominal
	 *            is greater than the capability's max refresh
	 */
	nominal_field_rate_in_uhz =
			भाग_u64(nominal_field_rate_in_uhz + 500000, 1000000);
	min_refresh_cap_in_uhz /= 1000000;
	max_refresh_cap_in_uhz /= 1000000;

	/* Check nominal is within range */
	अगर (nominal_field_rate_in_uhz > max_refresh_cap_in_uhz ||
		nominal_field_rate_in_uhz < min_refresh_cap_in_uhz)
		वापस false;

	/* If nominal is less than max, limit the max allowed refresh rate */
	अगर (nominal_field_rate_in_uhz < max_refresh_cap_in_uhz)
		max_refresh_cap_in_uhz = nominal_field_rate_in_uhz;

	/* Check min is within range */
	अगर (min_refresh_cap_in_uhz > max_refresh_cap_in_uhz)
		वापस false;

	/* For variable range, check क्रम at least 10 Hz range */
	अगर (nominal_field_rate_in_uhz - min_refresh_cap_in_uhz < 10)
		वापस false;

	वापस true;
पूर्ण
