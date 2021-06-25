<शैली गुरु>
/*
 * Copyright तऊ 1997-2003 by The XFree86 Project, Inc.
 * Copyright तऊ 2007 Dave Airlie
 * Copyright तऊ 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 * Copyright 2005-2006 Luc Verhaegen
 * Copyright (c) 2001, Andy Ritger  aritger@nvidia.com
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
 * Except as contained in this notice, the name of the copyright holder(s)
 * and author(s) shall not be used in advertising or otherwise to promote
 * the sale, use or other dealings in this Software without prior written
 * authorization from the copyright holder(s) and author(s).
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/export.h>

#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"

/**
 * drm_mode_debug_prपूर्णांकmodeline - prपूर्णांक a mode to dmesg
 * @mode: mode to prपूर्णांक
 *
 * Describe @mode using DRM_DEBUG.
 */
व्योम drm_mode_debug_prपूर्णांकmodeline(स्थिर काष्ठा drm_display_mode *mode)
अणु
	DRM_DEBUG_KMS("Modeline " DRM_MODE_FMT "\n", DRM_MODE_ARG(mode));
पूर्ण
EXPORT_SYMBOL(drm_mode_debug_prपूर्णांकmodeline);

/**
 * drm_mode_create - create a new display mode
 * @dev: DRM device
 *
 * Create a new, cleared drm_display_mode with kzalloc, allocate an ID क्रम it
 * and वापस it.
 *
 * Returns:
 * Poपूर्णांकer to new mode on success, शून्य on error.
 */
काष्ठा drm_display_mode *drm_mode_create(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_display_mode *nmode;

	nmode = kzalloc(माप(काष्ठा drm_display_mode), GFP_KERNEL);
	अगर (!nmode)
		वापस शून्य;

	वापस nmode;
पूर्ण
EXPORT_SYMBOL(drm_mode_create);

/**
 * drm_mode_destroy - हटाओ a mode
 * @dev: DRM device
 * @mode: mode to हटाओ
 *
 * Release @mode's unique ID, then मुक्त it @mode काष्ठाure itself using kमुक्त.
 */
व्योम drm_mode_destroy(काष्ठा drm_device *dev, काष्ठा drm_display_mode *mode)
अणु
	अगर (!mode)
		वापस;

	kमुक्त(mode);
पूर्ण
EXPORT_SYMBOL(drm_mode_destroy);

/**
 * drm_mode_probed_add - add a mode to a connector's probed_mode list
 * @connector: connector the new mode
 * @mode: mode data
 *
 * Add @mode to @connector's probed_mode list क्रम later use. This list should
 * then in a second step get filtered and all the modes actually supported by
 * the hardware moved to the @connector's modes list.
 */
व्योम drm_mode_probed_add(काष्ठा drm_connector *connector,
			 काष्ठा drm_display_mode *mode)
अणु
	WARN_ON(!mutex_is_locked(&connector->dev->mode_config.mutex));

	list_add_tail(&mode->head, &connector->probed_modes);
पूर्ण
EXPORT_SYMBOL(drm_mode_probed_add);

/**
 * drm_cvt_mode -create a modeline based on the CVT algorithm
 * @dev: drm device
 * @hdisplay: hdisplay size
 * @vdisplay: vdisplay size
 * @vrefresh: vrefresh rate
 * @reduced: whether to use reduced blanking
 * @पूर्णांकerlaced: whether to compute an पूर्णांकerlaced mode
 * @margins: whether to add margins (borders)
 *
 * This function is called to generate the modeline based on CVT algorithm
 * according to the hdisplay, vdisplay, vrefresh.
 * It is based from the VESA(TM) Coordinated Video Timing Generator by
 * Graham Loveridge April 9, 2003 available at
 * http://www.elo.utfsm.cl/~elo212/करोcs/CVTd6r1.xls 
 *
 * And it is copied from xf86CVTmode in xserver/hw/xमुक्त86/modes/xf86cvt.c.
 * What I have करोne is to translate it by using पूर्णांकeger calculation.
 *
 * Returns:
 * The modeline based on the CVT algorithm stored in a drm_display_mode object.
 * The display mode object is allocated with drm_mode_create(). Returns शून्य
 * when no mode could be allocated.
 */
काष्ठा drm_display_mode *drm_cvt_mode(काष्ठा drm_device *dev, पूर्णांक hdisplay,
				      पूर्णांक vdisplay, पूर्णांक vrefresh,
				      bool reduced, bool पूर्णांकerlaced, bool margins)
अणु
#घोषणा HV_FACTOR			1000
	/* 1) top/bottom margin size (% of height) - शेष: 1.8, */
#घोषणा	CVT_MARGIN_PERCENTAGE		18
	/* 2) अक्षरacter cell horizontal granularity (pixels) - शेष 8 */
#घोषणा	CVT_H_GRANULARITY		8
	/* 3) Minimum vertical porch (lines) - शेष 3 */
#घोषणा	CVT_MIN_V_PORCH			3
	/* 4) Minimum number of vertical back porch lines - शेष 6 */
#घोषणा	CVT_MIN_V_BPORCH		6
	/* Pixel Clock step (kHz) */
#घोषणा CVT_CLOCK_STEP			250
	काष्ठा drm_display_mode *drm_mode;
	अचिन्हित पूर्णांक vfieldrate, hperiod;
	पूर्णांक hdisplay_rnd, hmargin, vdisplay_rnd, vmargin, vsync;
	पूर्णांक पूर्णांकerlace;
	u64 पंचांगp;

	अगर (!hdisplay || !vdisplay)
		वापस शून्य;

	/* allocate the drm_display_mode काष्ठाure. If failure, we will
	 * वापस directly
	 */
	drm_mode = drm_mode_create(dev);
	अगर (!drm_mode)
		वापस शून्य;

	/* the CVT शेष refresh rate is 60Hz */
	अगर (!vrefresh)
		vrefresh = 60;

	/* the required field fresh rate */
	अगर (पूर्णांकerlaced)
		vfieldrate = vrefresh * 2;
	अन्यथा
		vfieldrate = vrefresh;

	/* horizontal pixels */
	hdisplay_rnd = hdisplay - (hdisplay % CVT_H_GRANULARITY);

	/* determine the left&right borders */
	hmargin = 0;
	अगर (margins) अणु
		hmargin = hdisplay_rnd * CVT_MARGIN_PERCENTAGE / 1000;
		hmargin -= hmargin % CVT_H_GRANULARITY;
	पूर्ण
	/* find the total active pixels */
	drm_mode->hdisplay = hdisplay_rnd + 2 * hmargin;

	/* find the number of lines per field */
	अगर (पूर्णांकerlaced)
		vdisplay_rnd = vdisplay / 2;
	अन्यथा
		vdisplay_rnd = vdisplay;

	/* find the top & bottom borders */
	vmargin = 0;
	अगर (margins)
		vmargin = vdisplay_rnd * CVT_MARGIN_PERCENTAGE / 1000;

	drm_mode->vdisplay = vdisplay + 2 * vmargin;

	/* Interlaced */
	अगर (पूर्णांकerlaced)
		पूर्णांकerlace = 1;
	अन्यथा
		पूर्णांकerlace = 0;

	/* Determine VSync Width from aspect ratio */
	अगर (!(vdisplay % 3) && ((vdisplay * 4 / 3) == hdisplay))
		vsync = 4;
	अन्यथा अगर (!(vdisplay % 9) && ((vdisplay * 16 / 9) == hdisplay))
		vsync = 5;
	अन्यथा अगर (!(vdisplay % 10) && ((vdisplay * 16 / 10) == hdisplay))
		vsync = 6;
	अन्यथा अगर (!(vdisplay % 4) && ((vdisplay * 5 / 4) == hdisplay))
		vsync = 7;
	अन्यथा अगर (!(vdisplay % 9) && ((vdisplay * 15 / 9) == hdisplay))
		vsync = 7;
	अन्यथा /* custom */
		vsync = 10;

	अगर (!reduced) अणु
		/* simplअगरy the GTF calculation */
		/* 4) Minimum समय of vertical sync + back porch पूर्णांकerval (तगs)
		 * शेष 550.0
		 */
		पूर्णांक पंचांगp1, पंचांगp2;
#घोषणा CVT_MIN_VSYNC_BP	550
		/* 3) Nominal HSync width (% of line period) - शेष 8 */
#घोषणा CVT_HSYNC_PERCENTAGE	8
		अचिन्हित पूर्णांक hblank_percentage;
		पूर्णांक vsyncandback_porch, __maybe_unused vback_porch, hblank;

		/* estimated the horizontal period */
		पंचांगp1 = HV_FACTOR * 1000000  -
				CVT_MIN_VSYNC_BP * HV_FACTOR * vfieldrate;
		पंचांगp2 = (vdisplay_rnd + 2 * vmargin + CVT_MIN_V_PORCH) * 2 +
				पूर्णांकerlace;
		hperiod = पंचांगp1 * 2 / (पंचांगp2 * vfieldrate);

		पंचांगp1 = CVT_MIN_VSYNC_BP * HV_FACTOR / hperiod + 1;
		/* 9. Find number of lines in sync + backporch */
		अगर (पंचांगp1 < (vsync + CVT_MIN_V_PORCH))
			vsyncandback_porch = vsync + CVT_MIN_V_PORCH;
		अन्यथा
			vsyncandback_porch = पंचांगp1;
		/* 10. Find number of lines in back porch */
		vback_porch = vsyncandback_porch - vsync;
		drm_mode->vtotal = vdisplay_rnd + 2 * vmargin +
				vsyncandback_porch + CVT_MIN_V_PORCH;
		/* 5) Definition of Horizontal blanking समय limitation */
		/* Gradient (%/kHz) - शेष 600 */
#घोषणा CVT_M_FACTOR	600
		/* Offset (%) - शेष 40 */
#घोषणा CVT_C_FACTOR	40
		/* Blanking समय scaling factor - शेष 128 */
#घोषणा CVT_K_FACTOR	128
		/* Scaling factor weighting - शेष 20 */
#घोषणा CVT_J_FACTOR	20
#घोषणा CVT_M_PRIME	(CVT_M_FACTOR * CVT_K_FACTOR / 256)
#घोषणा CVT_C_PRIME	((CVT_C_FACTOR - CVT_J_FACTOR) * CVT_K_FACTOR / 256 + \
			 CVT_J_FACTOR)
		/* 12. Find ideal blanking duty cycle from क्रमmula */
		hblank_percentage = CVT_C_PRIME * HV_FACTOR - CVT_M_PRIME *
					hperiod / 1000;
		/* 13. Blanking समय */
		अगर (hblank_percentage < 20 * HV_FACTOR)
			hblank_percentage = 20 * HV_FACTOR;
		hblank = drm_mode->hdisplay * hblank_percentage /
			 (100 * HV_FACTOR - hblank_percentage);
		hblank -= hblank % (2 * CVT_H_GRANULARITY);
		/* 14. find the total pixels per line */
		drm_mode->htotal = drm_mode->hdisplay + hblank;
		drm_mode->hsync_end = drm_mode->hdisplay + hblank / 2;
		drm_mode->hsync_start = drm_mode->hsync_end -
			(drm_mode->htotal * CVT_HSYNC_PERCENTAGE) / 100;
		drm_mode->hsync_start += CVT_H_GRANULARITY -
			drm_mode->hsync_start % CVT_H_GRANULARITY;
		/* fill the Vsync values */
		drm_mode->vsync_start = drm_mode->vdisplay + CVT_MIN_V_PORCH;
		drm_mode->vsync_end = drm_mode->vsync_start + vsync;
	पूर्ण अन्यथा अणु
		/* Reduced blanking */
		/* Minimum vertical blanking पूर्णांकerval समय (तगs)- शेष 460 */
#घोषणा CVT_RB_MIN_VBLANK	460
		/* Fixed number of घड़ीs क्रम horizontal sync */
#घोषणा CVT_RB_H_SYNC		32
		/* Fixed number of घड़ीs क्रम horizontal blanking */
#घोषणा CVT_RB_H_BLANK		160
		/* Fixed number of lines क्रम vertical front porch - शेष 3*/
#घोषणा CVT_RB_VFPORCH		3
		पूर्णांक vbilines;
		पूर्णांक पंचांगp1, पंचांगp2;
		/* 8. Estimate Horizontal period. */
		पंचांगp1 = HV_FACTOR * 1000000 -
			CVT_RB_MIN_VBLANK * HV_FACTOR * vfieldrate;
		पंचांगp2 = vdisplay_rnd + 2 * vmargin;
		hperiod = पंचांगp1 / (पंचांगp2 * vfieldrate);
		/* 9. Find number of lines in vertical blanking */
		vbilines = CVT_RB_MIN_VBLANK * HV_FACTOR / hperiod + 1;
		/* 10. Check अगर vertical blanking is sufficient */
		अगर (vbilines < (CVT_RB_VFPORCH + vsync + CVT_MIN_V_BPORCH))
			vbilines = CVT_RB_VFPORCH + vsync + CVT_MIN_V_BPORCH;
		/* 11. Find total number of lines in vertical field */
		drm_mode->vtotal = vdisplay_rnd + 2 * vmargin + vbilines;
		/* 12. Find total number of pixels in a line */
		drm_mode->htotal = drm_mode->hdisplay + CVT_RB_H_BLANK;
		/* Fill in HSync values */
		drm_mode->hsync_end = drm_mode->hdisplay + CVT_RB_H_BLANK / 2;
		drm_mode->hsync_start = drm_mode->hsync_end - CVT_RB_H_SYNC;
		/* Fill in VSync values */
		drm_mode->vsync_start = drm_mode->vdisplay + CVT_RB_VFPORCH;
		drm_mode->vsync_end = drm_mode->vsync_start + vsync;
	पूर्ण
	/* 15/13. Find pixel घड़ी frequency (kHz क्रम xf86) */
	पंचांगp = drm_mode->htotal; /* perक्रमm पूर्णांकermediate calcs in u64 */
	पंचांगp *= HV_FACTOR * 1000;
	करो_भाग(पंचांगp, hperiod);
	पंचांगp -= drm_mode->घड़ी % CVT_CLOCK_STEP;
	drm_mode->घड़ी = पंचांगp;
	/* 18/16. Find actual vertical frame frequency */
	/* ignore - just set the mode flag क्रम पूर्णांकerlaced */
	अगर (पूर्णांकerlaced) अणु
		drm_mode->vtotal *= 2;
		drm_mode->flags |= DRM_MODE_FLAG_INTERLACE;
	पूर्ण
	/* Fill the mode line name */
	drm_mode_set_name(drm_mode);
	अगर (reduced)
		drm_mode->flags |= (DRM_MODE_FLAG_PHSYNC |
					DRM_MODE_FLAG_NVSYNC);
	अन्यथा
		drm_mode->flags |= (DRM_MODE_FLAG_PVSYNC |
					DRM_MODE_FLAG_NHSYNC);

	वापस drm_mode;
पूर्ण
EXPORT_SYMBOL(drm_cvt_mode);

/**
 * drm_gtf_mode_complex - create the modeline based on the full GTF algorithm
 * @dev: drm device
 * @hdisplay: hdisplay size
 * @vdisplay: vdisplay size
 * @vrefresh: vrefresh rate.
 * @पूर्णांकerlaced: whether to compute an पूर्णांकerlaced mode
 * @margins: desired margin (borders) size
 * @GTF_M: extended GTF क्रमmula parameters
 * @GTF_2C: extended GTF क्रमmula parameters
 * @GTF_K: extended GTF क्रमmula parameters
 * @GTF_2J: extended GTF क्रमmula parameters
 *
 * GTF feature blocks specअगरy C and J in multiples of 0.5, so we pass them
 * in here multiplied by two.  For a C of 40, pass in 80.
 *
 * Returns:
 * The modeline based on the full GTF algorithm stored in a drm_display_mode object.
 * The display mode object is allocated with drm_mode_create(). Returns शून्य
 * when no mode could be allocated.
 */
काष्ठा drm_display_mode *
drm_gtf_mode_complex(काष्ठा drm_device *dev, पूर्णांक hdisplay, पूर्णांक vdisplay,
		     पूर्णांक vrefresh, bool पूर्णांकerlaced, पूर्णांक margins,
		     पूर्णांक GTF_M, पूर्णांक GTF_2C, पूर्णांक GTF_K, पूर्णांक GTF_2J)
अणु	/* 1) top/bottom margin size (% of height) - शेष: 1.8, */
#घोषणा	GTF_MARGIN_PERCENTAGE		18
	/* 2) अक्षरacter cell horizontal granularity (pixels) - शेष 8 */
#घोषणा	GTF_CELL_GRAN			8
	/* 3) Minimum vertical porch (lines) - शेष 3 */
#घोषणा	GTF_MIN_V_PORCH			1
	/* width of vsync in lines */
#घोषणा V_SYNC_RQD			3
	/* width of hsync as % of total line */
#घोषणा H_SYNC_PERCENT			8
	/* min समय of vsync + back porch (microsec) */
#घोषणा MIN_VSYNC_PLUS_BP		550
	/* C' and M' are part of the Blanking Duty Cycle computation */
#घोषणा GTF_C_PRIME	((((GTF_2C - GTF_2J) * GTF_K / 256) + GTF_2J) / 2)
#घोषणा GTF_M_PRIME	(GTF_K * GTF_M / 256)
	काष्ठा drm_display_mode *drm_mode;
	अचिन्हित पूर्णांक hdisplay_rnd, vdisplay_rnd, vfieldrate_rqd;
	पूर्णांक top_margin, bottom_margin;
	पूर्णांक पूर्णांकerlace;
	अचिन्हित पूर्णांक hfreq_est;
	पूर्णांक vsync_plus_bp, __maybe_unused vback_porch;
	अचिन्हित पूर्णांक vtotal_lines, __maybe_unused vfieldrate_est;
	अचिन्हित पूर्णांक __maybe_unused hperiod;
	अचिन्हित पूर्णांक vfield_rate, __maybe_unused vframe_rate;
	पूर्णांक left_margin, right_margin;
	अचिन्हित पूर्णांक total_active_pixels, ideal_duty_cycle;
	अचिन्हित पूर्णांक hblank, total_pixels, pixel_freq;
	पूर्णांक hsync, hfront_porch, vodd_front_porch_lines;
	अचिन्हित पूर्णांक पंचांगp1, पंचांगp2;

	अगर (!hdisplay || !vdisplay)
		वापस शून्य;

	drm_mode = drm_mode_create(dev);
	अगर (!drm_mode)
		वापस शून्य;

	/* 1. In order to give correct results, the number of horizontal
	 * pixels requested is first processed to ensure that it is भागisible
	 * by the अक्षरacter size, by rounding it to the nearest अक्षरacter
	 * cell boundary:
	 */
	hdisplay_rnd = (hdisplay + GTF_CELL_GRAN / 2) / GTF_CELL_GRAN;
	hdisplay_rnd = hdisplay_rnd * GTF_CELL_GRAN;

	/* 2. If पूर्णांकerlace is requested, the number of vertical lines assumed
	 * by the calculation must be halved, as the computation calculates
	 * the number of vertical lines per field.
	 */
	अगर (पूर्णांकerlaced)
		vdisplay_rnd = vdisplay / 2;
	अन्यथा
		vdisplay_rnd = vdisplay;

	/* 3. Find the frame rate required: */
	अगर (पूर्णांकerlaced)
		vfieldrate_rqd = vrefresh * 2;
	अन्यथा
		vfieldrate_rqd = vrefresh;

	/* 4. Find number of lines in Top margin: */
	top_margin = 0;
	अगर (margins)
		top_margin = (vdisplay_rnd * GTF_MARGIN_PERCENTAGE + 500) /
				1000;
	/* 5. Find number of lines in bottom margin: */
	bottom_margin = top_margin;

	/* 6. If पूर्णांकerlace is required, then set variable पूर्णांकerlace: */
	अगर (पूर्णांकerlaced)
		पूर्णांकerlace = 1;
	अन्यथा
		पूर्णांकerlace = 0;

	/* 7. Estimate the Horizontal frequency */
	अणु
		पंचांगp1 = (1000000  - MIN_VSYNC_PLUS_BP * vfieldrate_rqd) / 500;
		पंचांगp2 = (vdisplay_rnd + 2 * top_margin + GTF_MIN_V_PORCH) *
				2 + पूर्णांकerlace;
		hfreq_est = (पंचांगp2 * 1000 * vfieldrate_rqd) / पंचांगp1;
	पूर्ण

	/* 8. Find the number of lines in V sync + back porch */
	/* [V SYNC+BP] = RINT(([MIN VSYNC+BP] * hfreq_est / 1000000)) */
	vsync_plus_bp = MIN_VSYNC_PLUS_BP * hfreq_est / 1000;
	vsync_plus_bp = (vsync_plus_bp + 500) / 1000;
	/*  9. Find the number of lines in V back porch alone: */
	vback_porch = vsync_plus_bp - V_SYNC_RQD;
	/*  10. Find the total number of lines in Vertical field period: */
	vtotal_lines = vdisplay_rnd + top_margin + bottom_margin +
			vsync_plus_bp + GTF_MIN_V_PORCH;
	/*  11. Estimate the Vertical field frequency: */
	vfieldrate_est = hfreq_est / vtotal_lines;
	/*  12. Find the actual horizontal period: */
	hperiod = 1000000 / (vfieldrate_rqd * vtotal_lines);

	/*  13. Find the actual Vertical field frequency: */
	vfield_rate = hfreq_est / vtotal_lines;
	/*  14. Find the Vertical frame frequency: */
	अगर (पूर्णांकerlaced)
		vframe_rate = vfield_rate / 2;
	अन्यथा
		vframe_rate = vfield_rate;
	/*  15. Find number of pixels in left margin: */
	अगर (margins)
		left_margin = (hdisplay_rnd * GTF_MARGIN_PERCENTAGE + 500) /
				1000;
	अन्यथा
		left_margin = 0;

	/* 16.Find number of pixels in right margin: */
	right_margin = left_margin;
	/* 17.Find total number of active pixels in image and left and right */
	total_active_pixels = hdisplay_rnd + left_margin + right_margin;
	/* 18.Find the ideal blanking duty cycle from blanking duty cycle */
	ideal_duty_cycle = GTF_C_PRIME * 1000 -
				(GTF_M_PRIME * 1000000 / hfreq_est);
	/* 19.Find the number of pixels in the blanking समय to the nearest
	 * द्विगुन अक्षरacter cell: */
	hblank = total_active_pixels * ideal_duty_cycle /
			(100000 - ideal_duty_cycle);
	hblank = (hblank + GTF_CELL_GRAN) / (2 * GTF_CELL_GRAN);
	hblank = hblank * 2 * GTF_CELL_GRAN;
	/* 20.Find total number of pixels: */
	total_pixels = total_active_pixels + hblank;
	/* 21.Find pixel घड़ी frequency: */
	pixel_freq = total_pixels * hfreq_est / 1000;
	/* Stage 1 computations are now complete; I should really pass
	 * the results to another function and करो the Stage 2 computations,
	 * but I only need a few more values so I'll just append the
	 * computations here क्रम now */
	/* 17. Find the number of pixels in the horizontal sync period: */
	hsync = H_SYNC_PERCENT * total_pixels / 100;
	hsync = (hsync + GTF_CELL_GRAN / 2) / GTF_CELL_GRAN;
	hsync = hsync * GTF_CELL_GRAN;
	/* 18. Find the number of pixels in horizontal front porch period */
	hfront_porch = hblank / 2 - hsync;
	/*  36. Find the number of lines in the odd front porch period: */
	vodd_front_porch_lines = GTF_MIN_V_PORCH ;

	/* finally, pack the results in the mode काष्ठा */
	drm_mode->hdisplay = hdisplay_rnd;
	drm_mode->hsync_start = hdisplay_rnd + hfront_porch;
	drm_mode->hsync_end = drm_mode->hsync_start + hsync;
	drm_mode->htotal = total_pixels;
	drm_mode->vdisplay = vdisplay_rnd;
	drm_mode->vsync_start = vdisplay_rnd + vodd_front_porch_lines;
	drm_mode->vsync_end = drm_mode->vsync_start + V_SYNC_RQD;
	drm_mode->vtotal = vtotal_lines;

	drm_mode->घड़ी = pixel_freq;

	अगर (पूर्णांकerlaced) अणु
		drm_mode->vtotal *= 2;
		drm_mode->flags |= DRM_MODE_FLAG_INTERLACE;
	पूर्ण

	drm_mode_set_name(drm_mode);
	अगर (GTF_M == 600 && GTF_2C == 80 && GTF_K == 128 && GTF_2J == 40)
		drm_mode->flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		drm_mode->flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC;

	वापस drm_mode;
पूर्ण
EXPORT_SYMBOL(drm_gtf_mode_complex);

/**
 * drm_gtf_mode - create the modeline based on the GTF algorithm
 * @dev: drm device
 * @hdisplay: hdisplay size
 * @vdisplay: vdisplay size
 * @vrefresh: vrefresh rate.
 * @पूर्णांकerlaced: whether to compute an पूर्णांकerlaced mode
 * @margins: desired margin (borders) size
 *
 * वापस the modeline based on GTF algorithm
 *
 * This function is to create the modeline based on the GTF algorithm.
 * Generalized Timing Formula is derived from:
 *
 *	GTF Spपढ़ोsheet by Andy Morrish (1/5/97)
 *	available at https://www.vesa.org
 *
 * And it is copied from the file of xserver/hw/xमुक्त86/modes/xf86gtf.c.
 * What I have करोne is to translate it by using पूर्णांकeger calculation.
 * I also refer to the function of fb_get_mode in the file of
 * drivers/video/fbmon.c
 *
 * Standard GTF parameters::
 *
 *     M = 600
 *     C = 40
 *     K = 128
 *     J = 20
 *
 * Returns:
 * The modeline based on the GTF algorithm stored in a drm_display_mode object.
 * The display mode object is allocated with drm_mode_create(). Returns शून्य
 * when no mode could be allocated.
 */
काष्ठा drm_display_mode *
drm_gtf_mode(काष्ठा drm_device *dev, पूर्णांक hdisplay, पूर्णांक vdisplay, पूर्णांक vrefresh,
	     bool पूर्णांकerlaced, पूर्णांक margins)
अणु
	वापस drm_gtf_mode_complex(dev, hdisplay, vdisplay, vrefresh,
				    पूर्णांकerlaced, margins,
				    600, 40 * 2, 128, 20 * 2);
पूर्ण
EXPORT_SYMBOL(drm_gtf_mode);

#अगर_घोषित CONFIG_VIDEOMODE_HELPERS
/**
 * drm_display_mode_from_videomode - fill in @dmode using @vm,
 * @vm: videomode काष्ठाure to use as source
 * @dmode: drm_display_mode काष्ठाure to use as destination
 *
 * Fills out @dmode using the display mode specअगरied in @vm.
 */
व्योम drm_display_mode_from_videomode(स्थिर काष्ठा videomode *vm,
				     काष्ठा drm_display_mode *dmode)
अणु
	dmode->hdisplay = vm->hactive;
	dmode->hsync_start = dmode->hdisplay + vm->hfront_porch;
	dmode->hsync_end = dmode->hsync_start + vm->hsync_len;
	dmode->htotal = dmode->hsync_end + vm->hback_porch;

	dmode->vdisplay = vm->vactive;
	dmode->vsync_start = dmode->vdisplay + vm->vfront_porch;
	dmode->vsync_end = dmode->vsync_start + vm->vsync_len;
	dmode->vtotal = dmode->vsync_end + vm->vback_porch;

	dmode->घड़ी = vm->pixelघड़ी / 1000;

	dmode->flags = 0;
	अगर (vm->flags & DISPLAY_FLAGS_HSYNC_HIGH)
		dmode->flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा अगर (vm->flags & DISPLAY_FLAGS_HSYNC_LOW)
		dmode->flags |= DRM_MODE_FLAG_NHSYNC;
	अगर (vm->flags & DISPLAY_FLAGS_VSYNC_HIGH)
		dmode->flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा अगर (vm->flags & DISPLAY_FLAGS_VSYNC_LOW)
		dmode->flags |= DRM_MODE_FLAG_NVSYNC;
	अगर (vm->flags & DISPLAY_FLAGS_INTERLACED)
		dmode->flags |= DRM_MODE_FLAG_INTERLACE;
	अगर (vm->flags & DISPLAY_FLAGS_DOUBLESCAN)
		dmode->flags |= DRM_MODE_FLAG_DBLSCAN;
	अगर (vm->flags & DISPLAY_FLAGS_DOUBLECLK)
		dmode->flags |= DRM_MODE_FLAG_DBLCLK;
	drm_mode_set_name(dmode);
पूर्ण
EXPORT_SYMBOL_GPL(drm_display_mode_from_videomode);

/**
 * drm_display_mode_to_videomode - fill in @vm using @dmode,
 * @dmode: drm_display_mode काष्ठाure to use as source
 * @vm: videomode काष्ठाure to use as destination
 *
 * Fills out @vm using the display mode specअगरied in @dmode.
 */
व्योम drm_display_mode_to_videomode(स्थिर काष्ठा drm_display_mode *dmode,
				   काष्ठा videomode *vm)
अणु
	vm->hactive = dmode->hdisplay;
	vm->hfront_porch = dmode->hsync_start - dmode->hdisplay;
	vm->hsync_len = dmode->hsync_end - dmode->hsync_start;
	vm->hback_porch = dmode->htotal - dmode->hsync_end;

	vm->vactive = dmode->vdisplay;
	vm->vfront_porch = dmode->vsync_start - dmode->vdisplay;
	vm->vsync_len = dmode->vsync_end - dmode->vsync_start;
	vm->vback_porch = dmode->vtotal - dmode->vsync_end;

	vm->pixelघड़ी = dmode->घड़ी * 1000;

	vm->flags = 0;
	अगर (dmode->flags & DRM_MODE_FLAG_PHSYNC)
		vm->flags |= DISPLAY_FLAGS_HSYNC_HIGH;
	अन्यथा अगर (dmode->flags & DRM_MODE_FLAG_NHSYNC)
		vm->flags |= DISPLAY_FLAGS_HSYNC_LOW;
	अगर (dmode->flags & DRM_MODE_FLAG_PVSYNC)
		vm->flags |= DISPLAY_FLAGS_VSYNC_HIGH;
	अन्यथा अगर (dmode->flags & DRM_MODE_FLAG_NVSYNC)
		vm->flags |= DISPLAY_FLAGS_VSYNC_LOW;
	अगर (dmode->flags & DRM_MODE_FLAG_INTERLACE)
		vm->flags |= DISPLAY_FLAGS_INTERLACED;
	अगर (dmode->flags & DRM_MODE_FLAG_DBLSCAN)
		vm->flags |= DISPLAY_FLAGS_DOUBLESCAN;
	अगर (dmode->flags & DRM_MODE_FLAG_DBLCLK)
		vm->flags |= DISPLAY_FLAGS_DOUBLECLK;
पूर्ण
EXPORT_SYMBOL_GPL(drm_display_mode_to_videomode);

/**
 * drm_bus_flags_from_videomode - extract inक्रमmation about pixelclk and
 * DE polarity from videomode and store it in a separate variable
 * @vm: videomode काष्ठाure to use
 * @bus_flags: inक्रमmation about pixelclk, sync and DE polarity will be stored
 * here
 *
 * Sets DRM_BUS_FLAG_DE_(LOW|HIGH),  DRM_BUS_FLAG_PIXDATA_DRIVE_(POS|NEG)EDGE
 * and DISPLAY_FLAGS_SYNC_(POS|NEG)EDGE in @bus_flags according to DISPLAY_FLAGS
 * found in @vm
 */
व्योम drm_bus_flags_from_videomode(स्थिर काष्ठा videomode *vm, u32 *bus_flags)
अणु
	*bus_flags = 0;
	अगर (vm->flags & DISPLAY_FLAGS_PIXDATA_POSEDGE)
		*bus_flags |= DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE;
	अगर (vm->flags & DISPLAY_FLAGS_PIXDATA_NEGEDGE)
		*bus_flags |= DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE;

	अगर (vm->flags & DISPLAY_FLAGS_SYNC_POSEDGE)
		*bus_flags |= DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE;
	अगर (vm->flags & DISPLAY_FLAGS_SYNC_NEGEDGE)
		*bus_flags |= DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE;

	अगर (vm->flags & DISPLAY_FLAGS_DE_LOW)
		*bus_flags |= DRM_BUS_FLAG_DE_LOW;
	अगर (vm->flags & DISPLAY_FLAGS_DE_HIGH)
		*bus_flags |= DRM_BUS_FLAG_DE_HIGH;
पूर्ण
EXPORT_SYMBOL_GPL(drm_bus_flags_from_videomode);

#अगर_घोषित CONFIG_OF
/**
 * of_get_drm_display_mode - get a drm_display_mode from devicetree
 * @np: device_node with the timing specअगरication
 * @dmode: will be set to the वापस value
 * @bus_flags: inक्रमmation about pixelclk, sync and DE polarity
 * @index: index पूर्णांकo the list of display timings in devicetree
 *
 * This function is expensive and should only be used, अगर only one mode is to be
 * पढ़ो from DT. To get multiple modes start with of_get_display_timings and
 * work with that instead.
 *
 * Returns:
 * 0 on success, a negative त्रुटि_सं code when no of videomode node was found.
 */
पूर्णांक of_get_drm_display_mode(काष्ठा device_node *np,
			    काष्ठा drm_display_mode *dmode, u32 *bus_flags,
			    पूर्णांक index)
अणु
	काष्ठा videomode vm;
	पूर्णांक ret;

	ret = of_get_videomode(np, &vm, index);
	अगर (ret)
		वापस ret;

	drm_display_mode_from_videomode(&vm, dmode);
	अगर (bus_flags)
		drm_bus_flags_from_videomode(&vm, bus_flags);

	pr_debug("%pOF: got %dx%d display mode\n",
		np, vm.hactive, vm.vactive);
	drm_mode_debug_prपूर्णांकmodeline(dmode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_drm_display_mode);
#पूर्ण_अगर /* CONFIG_OF */
#पूर्ण_अगर /* CONFIG_VIDEOMODE_HELPERS */

/**
 * drm_mode_set_name - set the name on a mode
 * @mode: name will be set in this mode
 *
 * Set the name of @mode to a standard क्रमmat which is <hdisplay>x<vdisplay>
 * with an optional 'i' suffix क्रम पूर्णांकerlaced modes.
 */
व्योम drm_mode_set_name(काष्ठा drm_display_mode *mode)
अणु
	bool पूर्णांकerlaced = !!(mode->flags & DRM_MODE_FLAG_INTERLACE);

	snम_लिखो(mode->name, DRM_DISPLAY_MODE_LEN, "%dx%d%s",
		 mode->hdisplay, mode->vdisplay,
		 पूर्णांकerlaced ? "i" : "");
पूर्ण
EXPORT_SYMBOL(drm_mode_set_name);

/**
 * drm_mode_vrefresh - get the vrefresh of a mode
 * @mode: mode
 *
 * Returns:
 * @modes's vrefresh rate in Hz, rounded to the nearest पूर्णांकeger. Calculates the
 * value first अगर it is not yet set.
 */
पूर्णांक drm_mode_vrefresh(स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक num, den;

	अगर (mode->htotal == 0 || mode->vtotal == 0)
		वापस 0;

	num = mode->घड़ी;
	den = mode->htotal * mode->vtotal;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		num *= 2;
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		den *= 2;
	अगर (mode->vscan > 1)
		den *= mode->vscan;

	वापस DIV_ROUND_CLOSEST_ULL(mul_u32_u32(num, 1000), den);
पूर्ण
EXPORT_SYMBOL(drm_mode_vrefresh);

/**
 * drm_mode_get_hv_timing - Fetches hdisplay/vdisplay क्रम given mode
 * @mode: mode to query
 * @hdisplay: hdisplay value to fill in
 * @vdisplay: vdisplay value to fill in
 *
 * The vdisplay value will be द्विगुनd अगर the specअगरied mode is a stereo mode of
 * the appropriate layout.
 */
व्योम drm_mode_get_hv_timing(स्थिर काष्ठा drm_display_mode *mode,
			    पूर्णांक *hdisplay, पूर्णांक *vdisplay)
अणु
	काष्ठा drm_display_mode adjusted = *mode;

	drm_mode_set_crtcinfo(&adjusted, CRTC_STEREO_DOUBLE_ONLY);
	*hdisplay = adjusted.crtc_hdisplay;
	*vdisplay = adjusted.crtc_vdisplay;
पूर्ण
EXPORT_SYMBOL(drm_mode_get_hv_timing);

/**
 * drm_mode_set_crtcinfo - set CRTC modesetting timing parameters
 * @p: mode
 * @adjust_flags: a combination of adjusपंचांगent flags
 *
 * Setup the CRTC modesetting timing parameters क्रम @p, adjusting अगर necessary.
 *
 * - The CRTC_INTERLACE_HALVE_V flag can be used to halve vertical timings of
 *   पूर्णांकerlaced modes.
 * - The CRTC_STEREO_DOUBLE flag can be used to compute the timings क्रम
 *   buffers containing two eyes (only adjust the timings when needed, eg. क्रम
 *   "frame packing" or "side by side full").
 * - The CRTC_NO_DBLSCAN and CRTC_NO_VSCAN flags request that adjusपंचांगent *not*
 *   be perक्रमmed क्रम द्विगुनscan and vscan > 1 modes respectively.
 */
व्योम drm_mode_set_crtcinfo(काष्ठा drm_display_mode *p, पूर्णांक adjust_flags)
अणु
	अगर (!p)
		वापस;

	p->crtc_घड़ी = p->घड़ी;
	p->crtc_hdisplay = p->hdisplay;
	p->crtc_hsync_start = p->hsync_start;
	p->crtc_hsync_end = p->hsync_end;
	p->crtc_htotal = p->htotal;
	p->crtc_hskew = p->hskew;
	p->crtc_vdisplay = p->vdisplay;
	p->crtc_vsync_start = p->vsync_start;
	p->crtc_vsync_end = p->vsync_end;
	p->crtc_vtotal = p->vtotal;

	अगर (p->flags & DRM_MODE_FLAG_INTERLACE) अणु
		अगर (adjust_flags & CRTC_INTERLACE_HALVE_V) अणु
			p->crtc_vdisplay /= 2;
			p->crtc_vsync_start /= 2;
			p->crtc_vsync_end /= 2;
			p->crtc_vtotal /= 2;
		पूर्ण
	पूर्ण

	अगर (!(adjust_flags & CRTC_NO_DBLSCAN)) अणु
		अगर (p->flags & DRM_MODE_FLAG_DBLSCAN) अणु
			p->crtc_vdisplay *= 2;
			p->crtc_vsync_start *= 2;
			p->crtc_vsync_end *= 2;
			p->crtc_vtotal *= 2;
		पूर्ण
	पूर्ण

	अगर (!(adjust_flags & CRTC_NO_VSCAN)) अणु
		अगर (p->vscan > 1) अणु
			p->crtc_vdisplay *= p->vscan;
			p->crtc_vsync_start *= p->vscan;
			p->crtc_vsync_end *= p->vscan;
			p->crtc_vtotal *= p->vscan;
		पूर्ण
	पूर्ण

	अगर (adjust_flags & CRTC_STEREO_DOUBLE) अणु
		अचिन्हित पूर्णांक layout = p->flags & DRM_MODE_FLAG_3D_MASK;

		चयन (layout) अणु
		हाल DRM_MODE_FLAG_3D_FRAME_PACKING:
			p->crtc_घड़ी *= 2;
			p->crtc_vdisplay += p->crtc_vtotal;
			p->crtc_vsync_start += p->crtc_vtotal;
			p->crtc_vsync_end += p->crtc_vtotal;
			p->crtc_vtotal += p->crtc_vtotal;
			अवरोध;
		पूर्ण
	पूर्ण

	p->crtc_vblank_start = min(p->crtc_vsync_start, p->crtc_vdisplay);
	p->crtc_vblank_end = max(p->crtc_vsync_end, p->crtc_vtotal);
	p->crtc_hblank_start = min(p->crtc_hsync_start, p->crtc_hdisplay);
	p->crtc_hblank_end = max(p->crtc_hsync_end, p->crtc_htotal);
पूर्ण
EXPORT_SYMBOL(drm_mode_set_crtcinfo);

/**
 * drm_mode_copy - copy the mode
 * @dst: mode to overग_लिखो
 * @src: mode to copy
 *
 * Copy an existing mode पूर्णांकo another mode, preserving the object id and
 * list head of the destination mode.
 */
व्योम drm_mode_copy(काष्ठा drm_display_mode *dst, स्थिर काष्ठा drm_display_mode *src)
अणु
	काष्ठा list_head head = dst->head;

	*dst = *src;
	dst->head = head;
पूर्ण
EXPORT_SYMBOL(drm_mode_copy);

/**
 * drm_mode_duplicate - allocate and duplicate an existing mode
 * @dev: drm_device to allocate the duplicated mode क्रम
 * @mode: mode to duplicate
 *
 * Just allocate a new mode, copy the existing mode पूर्णांकo it, and वापस
 * a poपूर्णांकer to it.  Used to create new instances of established modes.
 *
 * Returns:
 * Poपूर्णांकer to duplicated mode on success, शून्य on error.
 */
काष्ठा drm_display_mode *drm_mode_duplicate(काष्ठा drm_device *dev,
					    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_display_mode *nmode;

	nmode = drm_mode_create(dev);
	अगर (!nmode)
		वापस शून्य;

	drm_mode_copy(nmode, mode);

	वापस nmode;
पूर्ण
EXPORT_SYMBOL(drm_mode_duplicate);

अटल bool drm_mode_match_timings(स्थिर काष्ठा drm_display_mode *mode1,
				   स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस mode1->hdisplay == mode2->hdisplay &&
		mode1->hsync_start == mode2->hsync_start &&
		mode1->hsync_end == mode2->hsync_end &&
		mode1->htotal == mode2->htotal &&
		mode1->hskew == mode2->hskew &&
		mode1->vdisplay == mode2->vdisplay &&
		mode1->vsync_start == mode2->vsync_start &&
		mode1->vsync_end == mode2->vsync_end &&
		mode1->vtotal == mode2->vtotal &&
		mode1->vscan == mode2->vscan;
पूर्ण

अटल bool drm_mode_match_घड़ी(स्थिर काष्ठा drm_display_mode *mode1,
				  स्थिर काष्ठा drm_display_mode *mode2)
अणु
	/*
	 * करो घड़ी check convert to PICOS
	 * so fb modes get matched the same
	 */
	अगर (mode1->घड़ी && mode2->घड़ी)
		वापस KHZ2PICOS(mode1->घड़ी) == KHZ2PICOS(mode2->घड़ी);
	अन्यथा
		वापस mode1->घड़ी == mode2->घड़ी;
पूर्ण

अटल bool drm_mode_match_flags(स्थिर काष्ठा drm_display_mode *mode1,
				 स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस (mode1->flags & ~DRM_MODE_FLAG_3D_MASK) ==
		(mode2->flags & ~DRM_MODE_FLAG_3D_MASK);
पूर्ण

अटल bool drm_mode_match_3d_flags(स्थिर काष्ठा drm_display_mode *mode1,
				    स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस (mode1->flags & DRM_MODE_FLAG_3D_MASK) ==
		(mode2->flags & DRM_MODE_FLAG_3D_MASK);
पूर्ण

अटल bool drm_mode_match_aspect_ratio(स्थिर काष्ठा drm_display_mode *mode1,
					स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस mode1->picture_aspect_ratio == mode2->picture_aspect_ratio;
पूर्ण

/**
 * drm_mode_match - test modes क्रम (partial) equality
 * @mode1: first mode
 * @mode2: second mode
 * @match_flags: which parts need to match (DRM_MODE_MATCH_*)
 *
 * Check to see अगर @mode1 and @mode2 are equivalent.
 *
 * Returns:
 * True अगर the modes are (partially) equal, false otherwise.
 */
bool drm_mode_match(स्थिर काष्ठा drm_display_mode *mode1,
		    स्थिर काष्ठा drm_display_mode *mode2,
		    अचिन्हित पूर्णांक match_flags)
अणु
	अगर (!mode1 && !mode2)
		वापस true;

	अगर (!mode1 || !mode2)
		वापस false;

	अगर (match_flags & DRM_MODE_MATCH_TIMINGS &&
	    !drm_mode_match_timings(mode1, mode2))
		वापस false;

	अगर (match_flags & DRM_MODE_MATCH_CLOCK &&
	    !drm_mode_match_घड़ी(mode1, mode2))
		वापस false;

	अगर (match_flags & DRM_MODE_MATCH_FLAGS &&
	    !drm_mode_match_flags(mode1, mode2))
		वापस false;

	अगर (match_flags & DRM_MODE_MATCH_3D_FLAGS &&
	    !drm_mode_match_3d_flags(mode1, mode2))
		वापस false;

	अगर (match_flags & DRM_MODE_MATCH_ASPECT_RATIO &&
	    !drm_mode_match_aspect_ratio(mode1, mode2))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_mode_match);

/**
 * drm_mode_equal - test modes क्रम equality
 * @mode1: first mode
 * @mode2: second mode
 *
 * Check to see अगर @mode1 and @mode2 are equivalent.
 *
 * Returns:
 * True अगर the modes are equal, false otherwise.
 */
bool drm_mode_equal(स्थिर काष्ठा drm_display_mode *mode1,
		    स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस drm_mode_match(mode1, mode2,
			      DRM_MODE_MATCH_TIMINGS |
			      DRM_MODE_MATCH_CLOCK |
			      DRM_MODE_MATCH_FLAGS |
			      DRM_MODE_MATCH_3D_FLAGS|
			      DRM_MODE_MATCH_ASPECT_RATIO);
पूर्ण
EXPORT_SYMBOL(drm_mode_equal);

/**
 * drm_mode_equal_no_घड़ीs - test modes क्रम equality
 * @mode1: first mode
 * @mode2: second mode
 *
 * Check to see अगर @mode1 and @mode2 are equivalent, but
 * करोn't check the pixel घड़ीs.
 *
 * Returns:
 * True अगर the modes are equal, false otherwise.
 */
bool drm_mode_equal_no_घड़ीs(स्थिर काष्ठा drm_display_mode *mode1,
			      स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस drm_mode_match(mode1, mode2,
			      DRM_MODE_MATCH_TIMINGS |
			      DRM_MODE_MATCH_FLAGS |
			      DRM_MODE_MATCH_3D_FLAGS);
पूर्ण
EXPORT_SYMBOL(drm_mode_equal_no_घड़ीs);

/**
 * drm_mode_equal_no_घड़ीs_no_stereo - test modes क्रम equality
 * @mode1: first mode
 * @mode2: second mode
 *
 * Check to see अगर @mode1 and @mode2 are equivalent, but
 * करोn't check the pixel घड़ीs nor the stereo layout.
 *
 * Returns:
 * True अगर the modes are equal, false otherwise.
 */
bool drm_mode_equal_no_घड़ीs_no_stereo(स्थिर काष्ठा drm_display_mode *mode1,
					स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस drm_mode_match(mode1, mode2,
			      DRM_MODE_MATCH_TIMINGS |
			      DRM_MODE_MATCH_FLAGS);
पूर्ण
EXPORT_SYMBOL(drm_mode_equal_no_घड़ीs_no_stereo);

अटल क्रमागत drm_mode_status
drm_mode_validate_basic(स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->type & ~DRM_MODE_TYPE_ALL)
		वापस MODE_BAD;

	अगर (mode->flags & ~DRM_MODE_FLAG_ALL)
		वापस MODE_BAD;

	अगर ((mode->flags & DRM_MODE_FLAG_3D_MASK) > DRM_MODE_FLAG_3D_MAX)
		वापस MODE_BAD;

	अगर (mode->घड़ी == 0)
		वापस MODE_CLOCK_LOW;

	अगर (mode->hdisplay == 0 ||
	    mode->hsync_start < mode->hdisplay ||
	    mode->hsync_end < mode->hsync_start ||
	    mode->htotal < mode->hsync_end)
		वापस MODE_H_ILLEGAL;

	अगर (mode->vdisplay == 0 ||
	    mode->vsync_start < mode->vdisplay ||
	    mode->vsync_end < mode->vsync_start ||
	    mode->vtotal < mode->vsync_end)
		वापस MODE_V_ILLEGAL;

	वापस MODE_OK;
पूर्ण

/**
 * drm_mode_validate_driver - make sure the mode is somewhat sane
 * @dev: drm device
 * @mode: mode to check
 *
 * First करो basic validation on the mode, and then allow the driver
 * to check क्रम device/driver specअगरic limitations via the optional
 * &drm_mode_config_helper_funcs.mode_valid hook.
 *
 * Returns:
 * The mode status
 */
क्रमागत drm_mode_status
drm_mode_validate_driver(काष्ठा drm_device *dev,
			स्थिर काष्ठा drm_display_mode *mode)
अणु
	क्रमागत drm_mode_status status;

	status = drm_mode_validate_basic(mode);
	अगर (status != MODE_OK)
		वापस status;

	अगर (dev->mode_config.funcs->mode_valid)
		वापस dev->mode_config.funcs->mode_valid(dev, mode);
	अन्यथा
		वापस MODE_OK;
पूर्ण
EXPORT_SYMBOL(drm_mode_validate_driver);

/**
 * drm_mode_validate_size - make sure modes adhere to size स्थिरraपूर्णांकs
 * @mode: mode to check
 * @maxX: maximum width
 * @maxY: maximum height
 *
 * This function is a helper which can be used to validate modes against size
 * limitations of the DRM device/connector. If a mode is too big its status
 * member is updated with the appropriate validation failure code. The list
 * itself is not changed.
 *
 * Returns:
 * The mode status
 */
क्रमागत drm_mode_status
drm_mode_validate_size(स्थिर काष्ठा drm_display_mode *mode,
		       पूर्णांक maxX, पूर्णांक maxY)
अणु
	अगर (maxX > 0 && mode->hdisplay > maxX)
		वापस MODE_VIRTUAL_X;

	अगर (maxY > 0 && mode->vdisplay > maxY)
		वापस MODE_VIRTUAL_Y;

	वापस MODE_OK;
पूर्ण
EXPORT_SYMBOL(drm_mode_validate_size);

/**
 * drm_mode_validate_ycbcr420 - add 'ycbcr420-only' modes only when allowed
 * @mode: mode to check
 * @connector: drm connector under action
 *
 * This function is a helper which can be used to filter out any YCBCR420
 * only mode, when the source करोesn't support it.
 *
 * Returns:
 * The mode status
 */
क्रमागत drm_mode_status
drm_mode_validate_ycbcr420(स्थिर काष्ठा drm_display_mode *mode,
			   काष्ठा drm_connector *connector)
अणु
	u8 vic = drm_match_cea_mode(mode);
	क्रमागत drm_mode_status status = MODE_OK;
	काष्ठा drm_hdmi_info *hdmi = &connector->display_info.hdmi;

	अगर (test_bit(vic, hdmi->y420_vdb_modes)) अणु
		अगर (!connector->ycbcr_420_allowed)
			status = MODE_NO_420;
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL(drm_mode_validate_ycbcr420);

#घोषणा MODE_STATUS(status) [MODE_ ## status + 3] = #status

अटल स्थिर अक्षर * स्थिर drm_mode_status_names[] = अणु
	MODE_STATUS(OK),
	MODE_STATUS(HSYNC),
	MODE_STATUS(VSYNC),
	MODE_STATUS(H_ILLEGAL),
	MODE_STATUS(V_ILLEGAL),
	MODE_STATUS(BAD_WIDTH),
	MODE_STATUS(NOMODE),
	MODE_STATUS(NO_INTERLACE),
	MODE_STATUS(NO_DBLESCAN),
	MODE_STATUS(NO_VSCAN),
	MODE_STATUS(MEM),
	MODE_STATUS(VIRTUAL_X),
	MODE_STATUS(VIRTUAL_Y),
	MODE_STATUS(MEM_VIRT),
	MODE_STATUS(NOCLOCK),
	MODE_STATUS(CLOCK_HIGH),
	MODE_STATUS(CLOCK_LOW),
	MODE_STATUS(CLOCK_RANGE),
	MODE_STATUS(BAD_HVALUE),
	MODE_STATUS(BAD_VVALUE),
	MODE_STATUS(BAD_VSCAN),
	MODE_STATUS(HSYNC_NARROW),
	MODE_STATUS(HSYNC_WIDE),
	MODE_STATUS(HBLANK_NARROW),
	MODE_STATUS(HBLANK_WIDE),
	MODE_STATUS(VSYNC_NARROW),
	MODE_STATUS(VSYNC_WIDE),
	MODE_STATUS(VBLANK_NARROW),
	MODE_STATUS(VBLANK_WIDE),
	MODE_STATUS(PANEL),
	MODE_STATUS(INTERLACE_WIDTH),
	MODE_STATUS(ONE_WIDTH),
	MODE_STATUS(ONE_HEIGHT),
	MODE_STATUS(ONE_SIZE),
	MODE_STATUS(NO_REDUCED),
	MODE_STATUS(NO_STEREO),
	MODE_STATUS(NO_420),
	MODE_STATUS(STALE),
	MODE_STATUS(BAD),
	MODE_STATUS(ERROR),
पूर्ण;

#अघोषित MODE_STATUS

स्थिर अक्षर *drm_get_mode_status_name(क्रमागत drm_mode_status status)
अणु
	पूर्णांक index = status + 3;

	अगर (WARN_ON(index < 0 || index >= ARRAY_SIZE(drm_mode_status_names)))
		वापस "";

	वापस drm_mode_status_names[index];
पूर्ण

/**
 * drm_mode_prune_invalid - हटाओ invalid modes from mode list
 * @dev: DRM device
 * @mode_list: list of modes to check
 * @verbose: be verbose about it
 *
 * This helper function can be used to prune a display mode list after
 * validation has been completed. All modes whose status is not MODE_OK will be
 * हटाओd from the list, and अगर @verbose the status code and mode name is also
 * prपूर्णांकed to dmesg.
 */
व्योम drm_mode_prune_invalid(काष्ठा drm_device *dev,
			    काष्ठा list_head *mode_list, bool verbose)
अणु
	काष्ठा drm_display_mode *mode, *t;

	list_क्रम_each_entry_safe(mode, t, mode_list, head) अणु
		अगर (mode->status != MODE_OK) अणु
			list_del(&mode->head);
			अगर (verbose) अणु
				drm_mode_debug_prपूर्णांकmodeline(mode);
				DRM_DEBUG_KMS("Not using %s mode: %s\n",
					      mode->name,
					      drm_get_mode_status_name(mode->status));
			पूर्ण
			drm_mode_destroy(dev, mode);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_mode_prune_invalid);

/**
 * drm_mode_compare - compare modes क्रम favorability
 * @priv: unused
 * @lh_a: list_head क्रम first mode
 * @lh_b: list_head क्रम second mode
 *
 * Compare two modes, given by @lh_a and @lh_b, वापसing a value indicating
 * which is better.
 *
 * Returns:
 * Negative अगर @lh_a is better than @lh_b, zero अगर they're equivalent, or
 * positive अगर @lh_b is better than @lh_a.
 */
अटल पूर्णांक drm_mode_compare(व्योम *priv, स्थिर काष्ठा list_head *lh_a,
			    स्थिर काष्ठा list_head *lh_b)
अणु
	काष्ठा drm_display_mode *a = list_entry(lh_a, काष्ठा drm_display_mode, head);
	काष्ठा drm_display_mode *b = list_entry(lh_b, काष्ठा drm_display_mode, head);
	पूर्णांक dअगरf;

	dअगरf = ((b->type & DRM_MODE_TYPE_PREFERRED) != 0) -
		((a->type & DRM_MODE_TYPE_PREFERRED) != 0);
	अगर (dअगरf)
		वापस dअगरf;
	dअगरf = b->hdisplay * b->vdisplay - a->hdisplay * a->vdisplay;
	अगर (dअगरf)
		वापस dअगरf;

	dअगरf = drm_mode_vrefresh(b) - drm_mode_vrefresh(a);
	अगर (dअगरf)
		वापस dअगरf;

	dअगरf = b->घड़ी - a->घड़ी;
	वापस dअगरf;
पूर्ण

/**
 * drm_mode_sort - sort mode list
 * @mode_list: list of drm_display_mode काष्ठाures to sort
 *
 * Sort @mode_list by favorability, moving good modes to the head of the list.
 */
व्योम drm_mode_sort(काष्ठा list_head *mode_list)
अणु
	list_sort(शून्य, mode_list, drm_mode_compare);
पूर्ण
EXPORT_SYMBOL(drm_mode_sort);

/**
 * drm_connector_list_update - update the mode list क्रम the connector
 * @connector: the connector to update
 *
 * This moves the modes from the @connector probed_modes list
 * to the actual mode list. It compares the probed mode against the current
 * list and only adds dअगरferent/new modes.
 *
 * This is just a helper functions करोesn't validate any modes itself and also
 * करोesn't prune any invalid modes. Callers need to करो that themselves.
 */
व्योम drm_connector_list_update(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *pmode, *pt;

	WARN_ON(!mutex_is_locked(&connector->dev->mode_config.mutex));

	list_क्रम_each_entry_safe(pmode, pt, &connector->probed_modes, head) अणु
		काष्ठा drm_display_mode *mode;
		bool found_it = false;

		/* go through current modes checking क्रम the new probed mode */
		list_क्रम_each_entry(mode, &connector->modes, head) अणु
			अगर (!drm_mode_equal(pmode, mode))
				जारी;

			found_it = true;

			/*
			 * If the old matching mode is stale (ie. left over
			 * from a previous probe) just replace it outright.
			 * Otherwise just merge the type bits between all
			 * equal probed modes.
			 *
			 * If two probed modes are considered equal, pick the
			 * actual timings from the one that's marked as
			 * preferred (in हाल the match isn't 100%). If
			 * multiple or zero preferred modes are present, favor
			 * the mode added to the probed_modes list first.
			 */
			अगर (mode->status == MODE_STALE) अणु
				drm_mode_copy(mode, pmode);
			पूर्ण अन्यथा अगर ((mode->type & DRM_MODE_TYPE_PREFERRED) == 0 &&
				   (pmode->type & DRM_MODE_TYPE_PREFERRED) != 0) अणु
				pmode->type |= mode->type;
				drm_mode_copy(mode, pmode);
			पूर्ण अन्यथा अणु
				mode->type |= pmode->type;
			पूर्ण

			list_del(&pmode->head);
			drm_mode_destroy(connector->dev, pmode);
			अवरोध;
		पूर्ण

		अगर (!found_it) अणु
			list_move_tail(&pmode->head, &connector->modes);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_connector_list_update);

अटल पूर्णांक drm_mode_parse_cmdline_bpp(स्थिर अक्षर *str, अक्षर **end_ptr,
				      काष्ठा drm_cmdline_mode *mode)
अणु
	अचिन्हित पूर्णांक bpp;

	अगर (str[0] != '-')
		वापस -EINVAL;

	str++;
	bpp = simple_म_से_दीर्घ(str, end_ptr, 10);
	अगर (*end_ptr == str)
		वापस -EINVAL;

	mode->bpp = bpp;
	mode->bpp_specअगरied = true;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_mode_parse_cmdline_refresh(स्थिर अक्षर *str, अक्षर **end_ptr,
					  काष्ठा drm_cmdline_mode *mode)
अणु
	अचिन्हित पूर्णांक refresh;

	अगर (str[0] != '@')
		वापस -EINVAL;

	str++;
	refresh = simple_म_से_दीर्घ(str, end_ptr, 10);
	अगर (*end_ptr == str)
		वापस -EINVAL;

	mode->refresh = refresh;
	mode->refresh_specअगरied = true;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_mode_parse_cmdline_extra(स्थिर अक्षर *str, पूर्णांक length,
					bool मुक्तstanding,
					स्थिर काष्ठा drm_connector *connector,
					काष्ठा drm_cmdline_mode *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length; i++) अणु
		चयन (str[i]) अणु
		हाल 'i':
			अगर (मुक्तstanding)
				वापस -EINVAL;

			mode->पूर्णांकerlace = true;
			अवरोध;
		हाल 'm':
			अगर (मुक्तstanding)
				वापस -EINVAL;

			mode->margins = true;
			अवरोध;
		हाल 'D':
			अगर (mode->क्रमce != DRM_FORCE_UNSPECIFIED)
				वापस -EINVAL;

			अगर ((connector->connector_type != DRM_MODE_CONNECTOR_DVII) &&
			    (connector->connector_type != DRM_MODE_CONNECTOR_HDMIB))
				mode->क्रमce = DRM_FORCE_ON;
			अन्यथा
				mode->क्रमce = DRM_FORCE_ON_DIGITAL;
			अवरोध;
		हाल 'd':
			अगर (mode->क्रमce != DRM_FORCE_UNSPECIFIED)
				वापस -EINVAL;

			mode->क्रमce = DRM_FORCE_OFF;
			अवरोध;
		हाल 'e':
			अगर (mode->क्रमce != DRM_FORCE_UNSPECIFIED)
				वापस -EINVAL;

			mode->क्रमce = DRM_FORCE_ON;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drm_mode_parse_cmdline_res_mode(स्थिर अक्षर *str, अचिन्हित पूर्णांक length,
					   bool extras,
					   स्थिर काष्ठा drm_connector *connector,
					   काष्ठा drm_cmdline_mode *mode)
अणु
	स्थिर अक्षर *str_start = str;
	bool rb = false, cvt = false;
	पूर्णांक xres = 0, yres = 0;
	पूर्णांक reमुख्यing, i;
	अक्षर *end_ptr;

	xres = simple_म_से_दीर्घ(str, &end_ptr, 10);
	अगर (end_ptr == str)
		वापस -EINVAL;

	अगर (end_ptr[0] != 'x')
		वापस -EINVAL;
	end_ptr++;

	str = end_ptr;
	yres = simple_म_से_दीर्घ(str, &end_ptr, 10);
	अगर (end_ptr == str)
		वापस -EINVAL;

	reमुख्यing = length - (end_ptr - str_start);
	अगर (reमुख्यing < 0)
		वापस -EINVAL;

	क्रम (i = 0; i < reमुख्यing; i++) अणु
		चयन (end_ptr[i]) अणु
		हाल 'M':
			cvt = true;
			अवरोध;
		हाल 'R':
			rb = true;
			अवरोध;
		शेष:
			/*
			 * Try to pass that to our extras parsing
			 * function to handle the हाल where the
			 * extras are directly after the resolution
			 */
			अगर (extras) अणु
				पूर्णांक ret = drm_mode_parse_cmdline_extra(end_ptr + i,
								       1,
								       false,
								       connector,
								       mode);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	mode->xres = xres;
	mode->yres = yres;
	mode->cvt = cvt;
	mode->rb = rb;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_mode_parse_cmdline_पूर्णांक(स्थिर अक्षर *delim, अचिन्हित पूर्णांक *पूर्णांक_ret)
अणु
	स्थिर अक्षर *value;
	अक्षर *endp;

	/*
	 * delim must poपूर्णांक to the '=', otherwise it is a syntax error and
	 * अगर delim poपूर्णांकs to the terminating zero, then delim + 1 wil poपूर्णांक
	 * past the end of the string.
	 */
	अगर (*delim != '=')
		वापस -EINVAL;

	value = delim + 1;
	*पूर्णांक_ret = simple_म_से_दीर्घ(value, &endp, 10);

	/* Make sure we have parsed something */
	अगर (endp == value)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_mode_parse_panel_orientation(स्थिर अक्षर *delim,
					    काष्ठा drm_cmdline_mode *mode)
अणु
	स्थिर अक्षर *value;

	अगर (*delim != '=')
		वापस -EINVAL;

	value = delim + 1;
	delim = म_अक्षर(value, ',');
	अगर (!delim)
		delim = value + म_माप(value);

	अगर (!म_भेदन(value, "normal", delim - value))
		mode->panel_orientation = DRM_MODE_PANEL_ORIENTATION_NORMAL;
	अन्यथा अगर (!म_भेदन(value, "upside_down", delim - value))
		mode->panel_orientation = DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP;
	अन्यथा अगर (!म_भेदन(value, "left_side_up", delim - value))
		mode->panel_orientation = DRM_MODE_PANEL_ORIENTATION_LEFT_UP;
	अन्यथा अगर (!म_भेदन(value, "right_side_up", delim - value))
		mode->panel_orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_mode_parse_cmdline_options(स्थिर अक्षर *str,
					  bool मुक्तstanding,
					  स्थिर काष्ठा drm_connector *connector,
					  काष्ठा drm_cmdline_mode *mode)
अणु
	अचिन्हित पूर्णांक deg, margin, rotation = 0;
	स्थिर अक्षर *delim, *option, *sep;

	option = str;
	करो अणु
		delim = म_अक्षर(option, '=');
		अगर (!delim) अणु
			delim = म_अक्षर(option, ',');

			अगर (!delim)
				delim = option + म_माप(option);
		पूर्ण

		अगर (!म_भेदन(option, "rotate", delim - option)) अणु
			अगर (drm_mode_parse_cmdline_पूर्णांक(delim, &deg))
				वापस -EINVAL;

			चयन (deg) अणु
			हाल 0:
				rotation |= DRM_MODE_ROTATE_0;
				अवरोध;

			हाल 90:
				rotation |= DRM_MODE_ROTATE_90;
				अवरोध;

			हाल 180:
				rotation |= DRM_MODE_ROTATE_180;
				अवरोध;

			हाल 270:
				rotation |= DRM_MODE_ROTATE_270;
				अवरोध;

			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(option, "reflect_x", delim - option)) अणु
			rotation |= DRM_MODE_REFLECT_X;
		पूर्ण अन्यथा अगर (!म_भेदन(option, "reflect_y", delim - option)) अणु
			rotation |= DRM_MODE_REFLECT_Y;
		पूर्ण अन्यथा अगर (!म_भेदन(option, "margin_right", delim - option)) अणु
			अगर (drm_mode_parse_cmdline_पूर्णांक(delim, &margin))
				वापस -EINVAL;

			mode->tv_margins.right = margin;
		पूर्ण अन्यथा अगर (!म_भेदन(option, "margin_left", delim - option)) अणु
			अगर (drm_mode_parse_cmdline_पूर्णांक(delim, &margin))
				वापस -EINVAL;

			mode->tv_margins.left = margin;
		पूर्ण अन्यथा अगर (!म_भेदन(option, "margin_top", delim - option)) अणु
			अगर (drm_mode_parse_cmdline_पूर्णांक(delim, &margin))
				वापस -EINVAL;

			mode->tv_margins.top = margin;
		पूर्ण अन्यथा अगर (!म_भेदन(option, "margin_bottom", delim - option)) अणु
			अगर (drm_mode_parse_cmdline_पूर्णांक(delim, &margin))
				वापस -EINVAL;

			mode->tv_margins.bottom = margin;
		पूर्ण अन्यथा अगर (!म_भेदन(option, "panel_orientation", delim - option)) अणु
			अगर (drm_mode_parse_panel_orientation(delim, mode))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		sep = म_अक्षर(delim, ',');
		option = sep + 1;
	पूर्ण जबतक (sep);

	अगर (rotation && मुक्तstanding)
		वापस -EINVAL;

	अगर (!(rotation & DRM_MODE_ROTATE_MASK))
		rotation |= DRM_MODE_ROTATE_0;

	/* Make sure there is exactly one rotation defined */
	अगर (!is_घातer_of_2(rotation & DRM_MODE_ROTATE_MASK))
		वापस -EINVAL;

	mode->rotation_reflection = rotation;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर drm_named_modes_whitelist[] = अणु
	"NTSC",
	"PAL",
पूर्ण;

/**
 * drm_mode_parse_command_line_क्रम_connector - parse command line modeline क्रम connector
 * @mode_option: optional per connector mode option
 * @connector: connector to parse modeline क्रम
 * @mode: pपुनः_स्मृतिated drm_cmdline_mode काष्ठाure to fill out
 *
 * This parses @mode_option command line modeline क्रम modes and options to
 * configure the connector. If @mode_option is शून्य the शेष command line
 * modeline in fb_mode_option will be parsed instead.
 *
 * This uses the same parameters as the fb modedb.c, except क्रम an extra
 * क्रमce-enable, क्रमce-enable-digital and क्रमce-disable bit at the end::
 *
 *	<xres>x<yres>[M][R][-<bpp>][@<refresh>][i][m][eDd]
 *
 * Additionals options can be provided following the mode, using a comma to
 * separate each option. Valid options can be found in
 * Documentation/fb/modedb.rst.
 *
 * The पूर्णांकermediate drm_cmdline_mode काष्ठाure is required to store additional
 * options from the command line modline like the क्रमce-enable/disable flag.
 *
 * Returns:
 * True अगर a valid modeline has been parsed, false otherwise.
 */
bool drm_mode_parse_command_line_क्रम_connector(स्थिर अक्षर *mode_option,
					       स्थिर काष्ठा drm_connector *connector,
					       काष्ठा drm_cmdline_mode *mode)
अणु
	स्थिर अक्षर *name;
	bool मुक्तstanding = false, parse_extras = false;
	अचिन्हित पूर्णांक bpp_off = 0, refresh_off = 0, options_off = 0;
	अचिन्हित पूर्णांक mode_end = 0;
	स्थिर अक्षर *bpp_ptr = शून्य, *refresh_ptr = शून्य, *extra_ptr = शून्य;
	स्थिर अक्षर *options_ptr = शून्य;
	अक्षर *bpp_end_ptr = शून्य, *refresh_end_ptr = शून्य;
	पूर्णांक i, len, ret;

	स_रखो(mode, 0, माप(*mode));
	mode->panel_orientation = DRM_MODE_PANEL_ORIENTATION_UNKNOWN;

	अगर (!mode_option)
		वापस false;

	name = mode_option;

	/* Try to locate the bpp and refresh specअगरiers, अगर any */
	bpp_ptr = म_अक्षर(name, '-');
	अगर (bpp_ptr)
		bpp_off = bpp_ptr - name;

	refresh_ptr = म_अक्षर(name, '@');
	अगर (refresh_ptr)
		refresh_off = refresh_ptr - name;

	/* Locate the start of named options */
	options_ptr = म_अक्षर(name, ',');
	अगर (options_ptr)
		options_off = options_ptr - name;

	/* Locate the end of the name / resolution, and parse it */
	अगर (bpp_ptr) अणु
		mode_end = bpp_off;
	पूर्ण अन्यथा अगर (refresh_ptr) अणु
		mode_end = refresh_off;
	पूर्ण अन्यथा अगर (options_ptr) अणु
		mode_end = options_off;
		parse_extras = true;
	पूर्ण अन्यथा अणु
		mode_end = म_माप(name);
		parse_extras = true;
	पूर्ण

	/* First check क्रम a named mode */
	क्रम (i = 0; i < ARRAY_SIZE(drm_named_modes_whitelist); i++) अणु
		ret = str_has_prefix(name, drm_named_modes_whitelist[i]);
		अगर (ret == mode_end) अणु
			अगर (refresh_ptr)
				वापस false; /* named + refresh is invalid */

			म_नकल(mode->name, drm_named_modes_whitelist[i]);
			mode->specअगरied = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* No named mode? Check क्रम a normal mode argument, e.g. 1024x768 */
	अगर (!mode->specअगरied && है_अंक(name[0])) अणु
		ret = drm_mode_parse_cmdline_res_mode(name, mode_end,
						      parse_extras,
						      connector,
						      mode);
		अगर (ret)
			वापस false;

		mode->specअगरied = true;
	पूर्ण

	/* No mode? Check क्रम मुक्तstanding extras and/or options */
	अगर (!mode->specअगरied) अणु
		अचिन्हित पूर्णांक len = म_माप(mode_option);

		अगर (bpp_ptr || refresh_ptr)
			वापस false; /* syntax error */

		अगर (len == 1 || (len >= 2 && mode_option[1] == ','))
			extra_ptr = mode_option;
		अन्यथा
			options_ptr = mode_option - 1;

		मुक्तstanding = true;
	पूर्ण

	अगर (bpp_ptr) अणु
		ret = drm_mode_parse_cmdline_bpp(bpp_ptr, &bpp_end_ptr, mode);
		अगर (ret)
			वापस false;

		mode->bpp_specअगरied = true;
	पूर्ण

	अगर (refresh_ptr) अणु
		ret = drm_mode_parse_cmdline_refresh(refresh_ptr,
						     &refresh_end_ptr, mode);
		अगर (ret)
			वापस false;

		mode->refresh_specअगरied = true;
	पूर्ण

	/*
	 * Locate the end of the bpp / refresh, and parse the extras
	 * अगर relevant
	 */
	अगर (bpp_ptr && refresh_ptr)
		extra_ptr = max(bpp_end_ptr, refresh_end_ptr);
	अन्यथा अगर (bpp_ptr)
		extra_ptr = bpp_end_ptr;
	अन्यथा अगर (refresh_ptr)
		extra_ptr = refresh_end_ptr;

	अगर (extra_ptr) अणु
		अगर (options_ptr)
			len = options_ptr - extra_ptr;
		अन्यथा
			len = म_माप(extra_ptr);

		ret = drm_mode_parse_cmdline_extra(extra_ptr, len, मुक्तstanding,
						   connector, mode);
		अगर (ret)
			वापस false;
	पूर्ण

	अगर (options_ptr) अणु
		ret = drm_mode_parse_cmdline_options(options_ptr + 1,
						     मुक्तstanding,
						     connector, mode);
		अगर (ret)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_mode_parse_command_line_क्रम_connector);

/**
 * drm_mode_create_from_cmdline_mode - convert a command line modeline पूर्णांकo a DRM display mode
 * @dev: DRM device to create the new mode क्रम
 * @cmd: input command line modeline
 *
 * Returns:
 * Poपूर्णांकer to converted mode on success, शून्य on error.
 */
काष्ठा drm_display_mode *
drm_mode_create_from_cmdline_mode(काष्ठा drm_device *dev,
				  काष्ठा drm_cmdline_mode *cmd)
अणु
	काष्ठा drm_display_mode *mode;

	अगर (cmd->xres == 0 || cmd->yres == 0)
		वापस शून्य;

	अगर (cmd->cvt)
		mode = drm_cvt_mode(dev,
				    cmd->xres, cmd->yres,
				    cmd->refresh_specअगरied ? cmd->refresh : 60,
				    cmd->rb, cmd->पूर्णांकerlace,
				    cmd->margins);
	अन्यथा
		mode = drm_gtf_mode(dev,
				    cmd->xres, cmd->yres,
				    cmd->refresh_specअगरied ? cmd->refresh : 60,
				    cmd->पूर्णांकerlace,
				    cmd->margins);
	अगर (!mode)
		वापस शून्य;

	mode->type |= DRM_MODE_TYPE_USERDEF;
	/* fix up 1368x768: GFT/CVT can't express 1366 width due to alignment */
	अगर (cmd->xres == 1366)
		drm_mode_fixup_1366x768(mode);
	drm_mode_set_crtcinfo(mode, CRTC_INTERLACE_HALVE_V);
	वापस mode;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_from_cmdline_mode);

/**
 * drm_mode_convert_to_umode - convert a drm_display_mode पूर्णांकo a modeinfo
 * @out: drm_mode_modeinfo काष्ठा to वापस to the user
 * @in: drm_display_mode to use
 *
 * Convert a drm_display_mode पूर्णांकo a drm_mode_modeinfo काष्ठाure to वापस to
 * the user.
 */
व्योम drm_mode_convert_to_umode(काष्ठा drm_mode_modeinfo *out,
			       स्थिर काष्ठा drm_display_mode *in)
अणु
	out->घड़ी = in->घड़ी;
	out->hdisplay = in->hdisplay;
	out->hsync_start = in->hsync_start;
	out->hsync_end = in->hsync_end;
	out->htotal = in->htotal;
	out->hskew = in->hskew;
	out->vdisplay = in->vdisplay;
	out->vsync_start = in->vsync_start;
	out->vsync_end = in->vsync_end;
	out->vtotal = in->vtotal;
	out->vscan = in->vscan;
	out->vrefresh = drm_mode_vrefresh(in);
	out->flags = in->flags;
	out->type = in->type;

	चयन (in->picture_aspect_ratio) अणु
	हाल HDMI_PICTURE_ASPECT_4_3:
		out->flags |= DRM_MODE_FLAG_PIC_AR_4_3;
		अवरोध;
	हाल HDMI_PICTURE_ASPECT_16_9:
		out->flags |= DRM_MODE_FLAG_PIC_AR_16_9;
		अवरोध;
	हाल HDMI_PICTURE_ASPECT_64_27:
		out->flags |= DRM_MODE_FLAG_PIC_AR_64_27;
		अवरोध;
	हाल HDMI_PICTURE_ASPECT_256_135:
		out->flags |= DRM_MODE_FLAG_PIC_AR_256_135;
		अवरोध;
	शेष:
		WARN(1, "Invalid aspect ratio (0%x) on mode\n",
		     in->picture_aspect_ratio);
		fallthrough;
	हाल HDMI_PICTURE_ASPECT_NONE:
		out->flags |= DRM_MODE_FLAG_PIC_AR_NONE;
		अवरोध;
	पूर्ण

	म_नकलन(out->name, in->name, DRM_DISPLAY_MODE_LEN);
	out->name[DRM_DISPLAY_MODE_LEN-1] = 0;
पूर्ण

/**
 * drm_mode_convert_umode - convert a modeinfo पूर्णांकo a drm_display_mode
 * @dev: drm device
 * @out: drm_display_mode to वापस to the user
 * @in: drm_mode_modeinfo to use
 *
 * Convert a drm_mode_modeinfo पूर्णांकo a drm_display_mode काष्ठाure to वापस to
 * the caller.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_convert_umode(काष्ठा drm_device *dev,
			   काष्ठा drm_display_mode *out,
			   स्थिर काष्ठा drm_mode_modeinfo *in)
अणु
	अगर (in->घड़ी > पूर्णांक_उच्च || in->vrefresh > पूर्णांक_उच्च)
		वापस -दुस्फल;

	out->घड़ी = in->घड़ी;
	out->hdisplay = in->hdisplay;
	out->hsync_start = in->hsync_start;
	out->hsync_end = in->hsync_end;
	out->htotal = in->htotal;
	out->hskew = in->hskew;
	out->vdisplay = in->vdisplay;
	out->vsync_start = in->vsync_start;
	out->vsync_end = in->vsync_end;
	out->vtotal = in->vtotal;
	out->vscan = in->vscan;
	out->flags = in->flags;
	/*
	 * Old xf86-video-vmware (possibly others too) used to
	 * leave 'type' unititialized. Just ignore any bits we
	 * करोn't like. It's a just hपूर्णांक after all, and more
	 * useful क्रम the kernel->userspace direction anyway.
	 */
	out->type = in->type & DRM_MODE_TYPE_ALL;
	म_नकलन(out->name, in->name, DRM_DISPLAY_MODE_LEN);
	out->name[DRM_DISPLAY_MODE_LEN-1] = 0;

	/* Clearing picture aspect ratio bits from out flags,
	 * as the aspect-ratio inक्रमmation is not stored in
	 * flags क्रम kernel-mode, but in picture_aspect_ratio.
	 */
	out->flags &= ~DRM_MODE_FLAG_PIC_AR_MASK;

	चयन (in->flags & DRM_MODE_FLAG_PIC_AR_MASK) अणु
	हाल DRM_MODE_FLAG_PIC_AR_4_3:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3;
		अवरोध;
	हाल DRM_MODE_FLAG_PIC_AR_16_9:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_16_9;
		अवरोध;
	हाल DRM_MODE_FLAG_PIC_AR_64_27:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_64_27;
		अवरोध;
	हाल DRM_MODE_FLAG_PIC_AR_256_135:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_256_135;
		अवरोध;
	हाल DRM_MODE_FLAG_PIC_AR_NONE:
		out->picture_aspect_ratio = HDMI_PICTURE_ASPECT_NONE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	out->status = drm_mode_validate_driver(dev, out);
	अगर (out->status != MODE_OK)
		वापस -EINVAL;

	drm_mode_set_crtcinfo(out, CRTC_INTERLACE_HALVE_V);

	वापस 0;
पूर्ण

/**
 * drm_mode_is_420_only - अगर a given videomode can be only supported in YCBCR420
 * output क्रमmat
 *
 * @display: display under action
 * @mode: video mode to be tested.
 *
 * Returns:
 * true अगर the mode can be supported in YCBCR420 क्रमmat
 * false अगर not.
 */
bool drm_mode_is_420_only(स्थिर काष्ठा drm_display_info *display,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	u8 vic = drm_match_cea_mode(mode);

	वापस test_bit(vic, display->hdmi.y420_vdb_modes);
पूर्ण
EXPORT_SYMBOL(drm_mode_is_420_only);

/**
 * drm_mode_is_420_also - अगर a given videomode can be supported in YCBCR420
 * output क्रमmat also (aदीर्घ with RGB/YCBCR444/422)
 *
 * @display: display under action.
 * @mode: video mode to be tested.
 *
 * Returns:
 * true अगर the mode can be support YCBCR420 क्रमmat
 * false अगर not.
 */
bool drm_mode_is_420_also(स्थिर काष्ठा drm_display_info *display,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	u8 vic = drm_match_cea_mode(mode);

	वापस test_bit(vic, display->hdmi.y420_cmdb_modes);
पूर्ण
EXPORT_SYMBOL(drm_mode_is_420_also);
/**
 * drm_mode_is_420 - अगर a given videomode can be supported in YCBCR420
 * output क्रमmat
 *
 * @display: display under action.
 * @mode: video mode to be tested.
 *
 * Returns:
 * true अगर the mode can be supported in YCBCR420 क्रमmat
 * false अगर not.
 */
bool drm_mode_is_420(स्थिर काष्ठा drm_display_info *display,
		     स्थिर काष्ठा drm_display_mode *mode)
अणु
	वापस drm_mode_is_420_only(display, mode) ||
		drm_mode_is_420_also(display, mode);
पूर्ण
EXPORT_SYMBOL(drm_mode_is_420);
