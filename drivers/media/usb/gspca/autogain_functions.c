<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Functions क्रम स्वतः gain.
 *
 * Copyright (C) 2010-2012 Hans de Goede <hdegoede@redhat.com>
 */
#समावेश "gspca.h"

/* स्वतः gain and exposure algorithm based on the knee algorithm described here:
   http://ytse.tricolour.net/करोcs/LowLightOptimization.hपंचांगl

   Returns 0 अगर no changes were made, 1 अगर the gain and or exposure settings
   where changed. */
पूर्णांक gspca_expo_स्वतःgain(
			काष्ठा gspca_dev *gspca_dev,
			पूर्णांक avg_lum,
			पूर्णांक desired_avg_lum,
			पूर्णांक deadzone,
			पूर्णांक gain_knee,
			पूर्णांक exposure_knee)
अणु
	s32 gain, orig_gain, exposure, orig_exposure;
	पूर्णांक i, steps, retval = 0;

	अगर (v4l2_ctrl_g_ctrl(gspca_dev->स्वतःgain) == 0)
		वापस 0;

	orig_gain = gain = v4l2_ctrl_g_ctrl(gspca_dev->gain);
	orig_exposure = exposure = v4l2_ctrl_g_ctrl(gspca_dev->exposure);

	/* If we are of a multiple of deadzone, करो multiple steps to reach the
	   desired lumination fast (with the risc of a slight overshoot) */
	steps = असल(desired_avg_lum - avg_lum) / deadzone;

	gspca_dbg(gspca_dev, D_FRAM, "autogain: lum: %d, desired: %d, steps: %d\n",
		  avg_lum, desired_avg_lum, steps);

	क्रम (i = 0; i < steps; i++) अणु
		अगर (avg_lum > desired_avg_lum) अणु
			अगर (gain > gain_knee)
				gain--;
			अन्यथा अगर (exposure > exposure_knee)
				exposure--;
			अन्यथा अगर (gain > gspca_dev->gain->शेष_value)
				gain--;
			अन्यथा अगर (exposure > gspca_dev->exposure->minimum)
				exposure--;
			अन्यथा अगर (gain > gspca_dev->gain->minimum)
				gain--;
			अन्यथा
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (gain < gspca_dev->gain->शेष_value)
				gain++;
			अन्यथा अगर (exposure < exposure_knee)
				exposure++;
			अन्यथा अगर (gain < gain_knee)
				gain++;
			अन्यथा अगर (exposure < gspca_dev->exposure->maximum)
				exposure++;
			अन्यथा अगर (gain < gspca_dev->gain->maximum)
				gain++;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (gain != orig_gain) अणु
		v4l2_ctrl_s_ctrl(gspca_dev->gain, gain);
		retval = 1;
	पूर्ण
	अगर (exposure != orig_exposure) अणु
		v4l2_ctrl_s_ctrl(gspca_dev->exposure, exposure);
		retval = 1;
	पूर्ण

	अगर (retval)
		gspca_dbg(gspca_dev, D_FRAM, "autogain: changed gain: %d, expo: %d\n",
			  gain, exposure);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(gspca_expo_स्वतःgain);

/* Autogain + exposure algorithm क्रम cameras with a coarse exposure control
   (usually this means we can only control the घड़ीभाग to change exposure)
   As changing the घड़ीभाग so that the fps drops from 30 to 15 fps क्रम
   example, will lead to a huge exposure change (it effectively द्विगुनs),
   this algorithm normally tries to only adjust the gain (between 40 and
   80 %) and अगर that करोes not help, only then changes exposure. This leads
   to a much more stable image then using the knee algorithm which at
   certain poपूर्णांकs of the knee graph will only try to adjust exposure,
   which leads to oscillating as one exposure step is huge.

   Returns 0 अगर no changes were made, 1 अगर the gain and or exposure settings
   where changed. */
पूर्णांक gspca_coarse_grained_expo_स्वतःgain(
			काष्ठा gspca_dev *gspca_dev,
			पूर्णांक avg_lum,
			पूर्णांक desired_avg_lum,
			पूर्णांक deadzone)
अणु
	s32 gain_low, gain_high, gain, orig_gain, exposure, orig_exposure;
	पूर्णांक steps, retval = 0;

	अगर (v4l2_ctrl_g_ctrl(gspca_dev->स्वतःgain) == 0)
		वापस 0;

	orig_gain = gain = v4l2_ctrl_g_ctrl(gspca_dev->gain);
	orig_exposure = exposure = v4l2_ctrl_g_ctrl(gspca_dev->exposure);

	gain_low  = (s32)(gspca_dev->gain->maximum - gspca_dev->gain->minimum) /
		    5 * 2 + gspca_dev->gain->minimum;
	gain_high = (s32)(gspca_dev->gain->maximum - gspca_dev->gain->minimum) /
		    5 * 4 + gspca_dev->gain->minimum;

	/* If we are of a multiple of deadzone, करो multiple steps to reach the
	   desired lumination fast (with the risc of a slight overshoot) */
	steps = (desired_avg_lum - avg_lum) / deadzone;

	gspca_dbg(gspca_dev, D_FRAM, "autogain: lum: %d, desired: %d, steps: %d\n",
		  avg_lum, desired_avg_lum, steps);

	अगर ((gain + steps) > gain_high &&
	    exposure < gspca_dev->exposure->maximum) अणु
		gain = gain_high;
		gspca_dev->exp_too_low_cnt++;
		gspca_dev->exp_too_high_cnt = 0;
	पूर्ण अन्यथा अगर ((gain + steps) < gain_low &&
		   exposure > gspca_dev->exposure->minimum) अणु
		gain = gain_low;
		gspca_dev->exp_too_high_cnt++;
		gspca_dev->exp_too_low_cnt = 0;
	पूर्ण अन्यथा अणु
		gain += steps;
		अगर (gain > gspca_dev->gain->maximum)
			gain = gspca_dev->gain->maximum;
		अन्यथा अगर (gain < gspca_dev->gain->minimum)
			gain = gspca_dev->gain->minimum;
		gspca_dev->exp_too_high_cnt = 0;
		gspca_dev->exp_too_low_cnt = 0;
	पूर्ण

	अगर (gspca_dev->exp_too_high_cnt > 3) अणु
		exposure--;
		gspca_dev->exp_too_high_cnt = 0;
	पूर्ण अन्यथा अगर (gspca_dev->exp_too_low_cnt > 3) अणु
		exposure++;
		gspca_dev->exp_too_low_cnt = 0;
	पूर्ण

	अगर (gain != orig_gain) अणु
		v4l2_ctrl_s_ctrl(gspca_dev->gain, gain);
		retval = 1;
	पूर्ण
	अगर (exposure != orig_exposure) अणु
		v4l2_ctrl_s_ctrl(gspca_dev->exposure, exposure);
		retval = 1;
	पूर्ण

	अगर (retval)
		gspca_dbg(gspca_dev, D_FRAM, "autogain: changed gain: %d, expo: %d\n",
			  gain, exposure);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(gspca_coarse_grained_expo_स्वतःgain);
