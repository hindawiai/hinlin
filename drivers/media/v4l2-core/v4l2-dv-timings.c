<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * v4l2-dv-timings - dv-timings helper functions
 *
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rational.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <linux/math64.h>
#समावेश <linux/hdmi.h>
#समावेश <media/cec.h>

MODULE_AUTHOR("Hans Verkuil");
MODULE_DESCRIPTION("V4L2 DV Timings Helper Functions");
MODULE_LICENSE("GPL");

स्थिर काष्ठा v4l2_dv_timings v4l2_dv_timings_presets[] = अणु
	V4L2_DV_BT_CEA_640X480P59_94,
	V4L2_DV_BT_CEA_720X480I59_94,
	V4L2_DV_BT_CEA_720X480P59_94,
	V4L2_DV_BT_CEA_720X576I50,
	V4L2_DV_BT_CEA_720X576P50,
	V4L2_DV_BT_CEA_1280X720P24,
	V4L2_DV_BT_CEA_1280X720P25,
	V4L2_DV_BT_CEA_1280X720P30,
	V4L2_DV_BT_CEA_1280X720P50,
	V4L2_DV_BT_CEA_1280X720P60,
	V4L2_DV_BT_CEA_1920X1080P24,
	V4L2_DV_BT_CEA_1920X1080P25,
	V4L2_DV_BT_CEA_1920X1080P30,
	V4L2_DV_BT_CEA_1920X1080I50,
	V4L2_DV_BT_CEA_1920X1080P50,
	V4L2_DV_BT_CEA_1920X1080I60,
	V4L2_DV_BT_CEA_1920X1080P60,
	V4L2_DV_BT_DMT_640X350P85,
	V4L2_DV_BT_DMT_640X400P85,
	V4L2_DV_BT_DMT_720X400P85,
	V4L2_DV_BT_DMT_640X480P72,
	V4L2_DV_BT_DMT_640X480P75,
	V4L2_DV_BT_DMT_640X480P85,
	V4L2_DV_BT_DMT_800X600P56,
	V4L2_DV_BT_DMT_800X600P60,
	V4L2_DV_BT_DMT_800X600P72,
	V4L2_DV_BT_DMT_800X600P75,
	V4L2_DV_BT_DMT_800X600P85,
	V4L2_DV_BT_DMT_800X600P120_RB,
	V4L2_DV_BT_DMT_848X480P60,
	V4L2_DV_BT_DMT_1024X768I43,
	V4L2_DV_BT_DMT_1024X768P60,
	V4L2_DV_BT_DMT_1024X768P70,
	V4L2_DV_BT_DMT_1024X768P75,
	V4L2_DV_BT_DMT_1024X768P85,
	V4L2_DV_BT_DMT_1024X768P120_RB,
	V4L2_DV_BT_DMT_1152X864P75,
	V4L2_DV_BT_DMT_1280X768P60_RB,
	V4L2_DV_BT_DMT_1280X768P60,
	V4L2_DV_BT_DMT_1280X768P75,
	V4L2_DV_BT_DMT_1280X768P85,
	V4L2_DV_BT_DMT_1280X768P120_RB,
	V4L2_DV_BT_DMT_1280X800P60_RB,
	V4L2_DV_BT_DMT_1280X800P60,
	V4L2_DV_BT_DMT_1280X800P75,
	V4L2_DV_BT_DMT_1280X800P85,
	V4L2_DV_BT_DMT_1280X800P120_RB,
	V4L2_DV_BT_DMT_1280X960P60,
	V4L2_DV_BT_DMT_1280X960P85,
	V4L2_DV_BT_DMT_1280X960P120_RB,
	V4L2_DV_BT_DMT_1280X1024P60,
	V4L2_DV_BT_DMT_1280X1024P75,
	V4L2_DV_BT_DMT_1280X1024P85,
	V4L2_DV_BT_DMT_1280X1024P120_RB,
	V4L2_DV_BT_DMT_1360X768P60,
	V4L2_DV_BT_DMT_1360X768P120_RB,
	V4L2_DV_BT_DMT_1366X768P60,
	V4L2_DV_BT_DMT_1366X768P60_RB,
	V4L2_DV_BT_DMT_1400X1050P60_RB,
	V4L2_DV_BT_DMT_1400X1050P60,
	V4L2_DV_BT_DMT_1400X1050P75,
	V4L2_DV_BT_DMT_1400X1050P85,
	V4L2_DV_BT_DMT_1400X1050P120_RB,
	V4L2_DV_BT_DMT_1440X900P60_RB,
	V4L2_DV_BT_DMT_1440X900P60,
	V4L2_DV_BT_DMT_1440X900P75,
	V4L2_DV_BT_DMT_1440X900P85,
	V4L2_DV_BT_DMT_1440X900P120_RB,
	V4L2_DV_BT_DMT_1600X900P60_RB,
	V4L2_DV_BT_DMT_1600X1200P60,
	V4L2_DV_BT_DMT_1600X1200P65,
	V4L2_DV_BT_DMT_1600X1200P70,
	V4L2_DV_BT_DMT_1600X1200P75,
	V4L2_DV_BT_DMT_1600X1200P85,
	V4L2_DV_BT_DMT_1600X1200P120_RB,
	V4L2_DV_BT_DMT_1680X1050P60_RB,
	V4L2_DV_BT_DMT_1680X1050P60,
	V4L2_DV_BT_DMT_1680X1050P75,
	V4L2_DV_BT_DMT_1680X1050P85,
	V4L2_DV_BT_DMT_1680X1050P120_RB,
	V4L2_DV_BT_DMT_1792X1344P60,
	V4L2_DV_BT_DMT_1792X1344P75,
	V4L2_DV_BT_DMT_1792X1344P120_RB,
	V4L2_DV_BT_DMT_1856X1392P60,
	V4L2_DV_BT_DMT_1856X1392P75,
	V4L2_DV_BT_DMT_1856X1392P120_RB,
	V4L2_DV_BT_DMT_1920X1200P60_RB,
	V4L2_DV_BT_DMT_1920X1200P60,
	V4L2_DV_BT_DMT_1920X1200P75,
	V4L2_DV_BT_DMT_1920X1200P85,
	V4L2_DV_BT_DMT_1920X1200P120_RB,
	V4L2_DV_BT_DMT_1920X1440P60,
	V4L2_DV_BT_DMT_1920X1440P75,
	V4L2_DV_BT_DMT_1920X1440P120_RB,
	V4L2_DV_BT_DMT_2048X1152P60_RB,
	V4L2_DV_BT_DMT_2560X1600P60_RB,
	V4L2_DV_BT_DMT_2560X1600P60,
	V4L2_DV_BT_DMT_2560X1600P75,
	V4L2_DV_BT_DMT_2560X1600P85,
	V4L2_DV_BT_DMT_2560X1600P120_RB,
	V4L2_DV_BT_CEA_3840X2160P24,
	V4L2_DV_BT_CEA_3840X2160P25,
	V4L2_DV_BT_CEA_3840X2160P30,
	V4L2_DV_BT_CEA_3840X2160P50,
	V4L2_DV_BT_CEA_3840X2160P60,
	V4L2_DV_BT_CEA_4096X2160P24,
	V4L2_DV_BT_CEA_4096X2160P25,
	V4L2_DV_BT_CEA_4096X2160P30,
	V4L2_DV_BT_CEA_4096X2160P50,
	V4L2_DV_BT_DMT_4096X2160P59_94_RB,
	V4L2_DV_BT_CEA_4096X2160P60,
	अणु पूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(v4l2_dv_timings_presets);

bool v4l2_valid_dv_timings(स्थिर काष्ठा v4l2_dv_timings *t,
			   स्थिर काष्ठा v4l2_dv_timings_cap *dvcap,
			   v4l2_check_dv_timings_fnc fnc,
			   व्योम *fnc_handle)
अणु
	स्थिर काष्ठा v4l2_bt_timings *bt = &t->bt;
	स्थिर काष्ठा v4l2_bt_timings_cap *cap = &dvcap->bt;
	u32 caps = cap->capabilities;

	अगर (t->type != V4L2_DV_BT_656_1120)
		वापस false;
	अगर (t->type != dvcap->type ||
	    bt->height < cap->min_height ||
	    bt->height > cap->max_height ||
	    bt->width < cap->min_width ||
	    bt->width > cap->max_width ||
	    bt->pixelघड़ी < cap->min_pixelघड़ी ||
	    bt->pixelघड़ी > cap->max_pixelघड़ी ||
	    (!(caps & V4L2_DV_BT_CAP_CUSTOM) &&
	     cap->standards && bt->standards &&
	     !(bt->standards & cap->standards)) ||
	    (bt->पूर्णांकerlaced && !(caps & V4L2_DV_BT_CAP_INTERLACED)) ||
	    (!bt->पूर्णांकerlaced && !(caps & V4L2_DV_BT_CAP_PROGRESSIVE)))
		वापस false;
	वापस fnc == शून्य || fnc(t, fnc_handle);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_valid_dv_timings);

पूर्णांक v4l2_क्रमागत_dv_timings_cap(काष्ठा v4l2_क्रमागत_dv_timings *t,
			     स्थिर काष्ठा v4l2_dv_timings_cap *cap,
			     v4l2_check_dv_timings_fnc fnc,
			     व्योम *fnc_handle)
अणु
	u32 i, idx;

	स_रखो(t->reserved, 0, माप(t->reserved));
	क्रम (i = idx = 0; v4l2_dv_timings_presets[i].bt.width; i++) अणु
		अगर (v4l2_valid_dv_timings(v4l2_dv_timings_presets + i, cap,
					  fnc, fnc_handle) &&
		    idx++ == t->index) अणु
			t->timings = v4l2_dv_timings_presets[i];
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_क्रमागत_dv_timings_cap);

bool v4l2_find_dv_timings_cap(काष्ठा v4l2_dv_timings *t,
			      स्थिर काष्ठा v4l2_dv_timings_cap *cap,
			      अचिन्हित pघड़ी_delta,
			      v4l2_check_dv_timings_fnc fnc,
			      व्योम *fnc_handle)
अणु
	पूर्णांक i;

	अगर (!v4l2_valid_dv_timings(t, cap, fnc, fnc_handle))
		वापस false;

	क्रम (i = 0; i < v4l2_dv_timings_presets[i].bt.width; i++) अणु
		अगर (v4l2_valid_dv_timings(v4l2_dv_timings_presets + i, cap,
					  fnc, fnc_handle) &&
		    v4l2_match_dv_timings(t, v4l2_dv_timings_presets + i,
					  pघड़ी_delta, false)) अणु
			u32 flags = t->bt.flags & V4L2_DV_FL_REDUCED_FPS;

			*t = v4l2_dv_timings_presets[i];
			अगर (can_reduce_fps(&t->bt))
				t->bt.flags |= flags;

			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_find_dv_timings_cap);

bool v4l2_find_dv_timings_cea861_vic(काष्ठा v4l2_dv_timings *t, u8 vic)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < v4l2_dv_timings_presets[i].bt.width; i++) अणु
		स्थिर काष्ठा v4l2_bt_timings *bt =
			&v4l2_dv_timings_presets[i].bt;

		अगर ((bt->flags & V4L2_DV_FL_HAS_CEA861_VIC) &&
		    bt->cea861_vic == vic) अणु
			*t = v4l2_dv_timings_presets[i];
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_find_dv_timings_cea861_vic);

/**
 * v4l2_match_dv_timings - check अगर two timings match
 * @t1: compare this v4l2_dv_timings काष्ठा...
 * @t2: with this काष्ठा.
 * @pघड़ी_delta: the allowed pixelघड़ी deviation.
 * @match_reduced_fps: अगर true, then fail अगर V4L2_DV_FL_REDUCED_FPS करोes not
 *	match.
 *
 * Compare t1 with t2 with a given margin of error क्रम the pixelघड़ी.
 */
bool v4l2_match_dv_timings(स्थिर काष्ठा v4l2_dv_timings *t1,
			   स्थिर काष्ठा v4l2_dv_timings *t2,
			   अचिन्हित pघड़ी_delta, bool match_reduced_fps)
अणु
	अगर (t1->type != t2->type || t1->type != V4L2_DV_BT_656_1120)
		वापस false;
	अगर (t1->bt.width == t2->bt.width &&
	    t1->bt.height == t2->bt.height &&
	    t1->bt.पूर्णांकerlaced == t2->bt.पूर्णांकerlaced &&
	    t1->bt.polarities == t2->bt.polarities &&
	    t1->bt.pixelघड़ी >= t2->bt.pixelघड़ी - pघड़ी_delta &&
	    t1->bt.pixelघड़ी <= t2->bt.pixelघड़ी + pघड़ी_delta &&
	    t1->bt.hfrontporch == t2->bt.hfrontporch &&
	    t1->bt.hsync == t2->bt.hsync &&
	    t1->bt.hbackporch == t2->bt.hbackporch &&
	    t1->bt.vfrontporch == t2->bt.vfrontporch &&
	    t1->bt.vsync == t2->bt.vsync &&
	    t1->bt.vbackporch == t2->bt.vbackporch &&
	    (!match_reduced_fps ||
	     (t1->bt.flags & V4L2_DV_FL_REDUCED_FPS) ==
		(t2->bt.flags & V4L2_DV_FL_REDUCED_FPS)) &&
	    (!t1->bt.पूर्णांकerlaced ||
		(t1->bt.il_vfrontporch == t2->bt.il_vfrontporch &&
		 t1->bt.il_vsync == t2->bt.il_vsync &&
		 t1->bt.il_vbackporch == t2->bt.il_vbackporch)))
		वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_match_dv_timings);

व्योम v4l2_prपूर्णांक_dv_timings(स्थिर अक्षर *dev_prefix, स्थिर अक्षर *prefix,
			   स्थिर काष्ठा v4l2_dv_timings *t, bool detailed)
अणु
	स्थिर काष्ठा v4l2_bt_timings *bt = &t->bt;
	u32 htot, vtot;
	u32 fps;

	अगर (t->type != V4L2_DV_BT_656_1120)
		वापस;

	htot = V4L2_DV_BT_FRAME_WIDTH(bt);
	vtot = V4L2_DV_BT_FRAME_HEIGHT(bt);
	अगर (bt->पूर्णांकerlaced)
		vtot /= 2;

	fps = (htot * vtot) > 0 ? भाग_u64((100 * (u64)bt->pixelघड़ी),
				  (htot * vtot)) : 0;

	अगर (prefix == शून्य)
		prefix = "";

	pr_info("%s: %s%ux%u%s%u.%02u (%ux%u)\n", dev_prefix, prefix,
		bt->width, bt->height, bt->पूर्णांकerlaced ? "i" : "p",
		fps / 100, fps % 100, htot, vtot);

	अगर (!detailed)
		वापस;

	pr_info("%s: horizontal: fp = %u, %ssync = %u, bp = %u\n",
			dev_prefix, bt->hfrontporch,
			(bt->polarities & V4L2_DV_HSYNC_POS_POL) ? "+" : "-",
			bt->hsync, bt->hbackporch);
	pr_info("%s: vertical: fp = %u, %ssync = %u, bp = %u\n",
			dev_prefix, bt->vfrontporch,
			(bt->polarities & V4L2_DV_VSYNC_POS_POL) ? "+" : "-",
			bt->vsync, bt->vbackporch);
	अगर (bt->पूर्णांकerlaced)
		pr_info("%s: vertical bottom field: fp = %u, %ssync = %u, bp = %u\n",
			dev_prefix, bt->il_vfrontporch,
			(bt->polarities & V4L2_DV_VSYNC_POS_POL) ? "+" : "-",
			bt->il_vsync, bt->il_vbackporch);
	pr_info("%s: pixelclock: %llu\n", dev_prefix, bt->pixelघड़ी);
	pr_info("%s: flags (0x%x):%s%s%s%s%s%s%s%s%s%s\n",
			dev_prefix, bt->flags,
			(bt->flags & V4L2_DV_FL_REDUCED_BLANKING) ?
			" REDUCED_BLANKING" : "",
			((bt->flags & V4L2_DV_FL_REDUCED_BLANKING) &&
			 bt->vsync == 8) ? " (V2)" : "",
			(bt->flags & V4L2_DV_FL_CAN_REDUCE_FPS) ?
			" CAN_REDUCE_FPS" : "",
			(bt->flags & V4L2_DV_FL_REDUCED_FPS) ?
			" REDUCED_FPS" : "",
			(bt->flags & V4L2_DV_FL_HALF_LINE) ?
			" HALF_LINE" : "",
			(bt->flags & V4L2_DV_FL_IS_CE_VIDEO) ?
			" CE_VIDEO" : "",
			(bt->flags & V4L2_DV_FL_FIRST_FIELD_EXTRA_LINE) ?
			" FIRST_FIELD_EXTRA_LINE" : "",
			(bt->flags & V4L2_DV_FL_HAS_PICTURE_ASPECT) ?
			" HAS_PICTURE_ASPECT" : "",
			(bt->flags & V4L2_DV_FL_HAS_CEA861_VIC) ?
			" HAS_CEA861_VIC" : "",
			(bt->flags & V4L2_DV_FL_HAS_HDMI_VIC) ?
			" HAS_HDMI_VIC" : "");
	pr_info("%s: standards (0x%x):%s%s%s%s%s\n", dev_prefix, bt->standards,
			(bt->standards & V4L2_DV_BT_STD_CEA861) ?  " CEA" : "",
			(bt->standards & V4L2_DV_BT_STD_DMT) ?  " DMT" : "",
			(bt->standards & V4L2_DV_BT_STD_CVT) ?  " CVT" : "",
			(bt->standards & V4L2_DV_BT_STD_GTF) ?  " GTF" : "",
			(bt->standards & V4L2_DV_BT_STD_SDI) ?  " SDI" : "");
	अगर (bt->flags & V4L2_DV_FL_HAS_PICTURE_ASPECT)
		pr_info("%s: picture aspect (hor:vert): %u:%u\n", dev_prefix,
			bt->picture_aspect.numerator,
			bt->picture_aspect.denominator);
	अगर (bt->flags & V4L2_DV_FL_HAS_CEA861_VIC)
		pr_info("%s: CEA-861 VIC: %u\n", dev_prefix, bt->cea861_vic);
	अगर (bt->flags & V4L2_DV_FL_HAS_HDMI_VIC)
		pr_info("%s: HDMI VIC: %u\n", dev_prefix, bt->hdmi_vic);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_prपूर्णांक_dv_timings);

काष्ठा v4l2_fract v4l2_dv_timings_aspect_ratio(स्थिर काष्ठा v4l2_dv_timings *t)
अणु
	काष्ठा v4l2_fract ratio = अणु 1, 1 पूर्ण;
	अचिन्हित दीर्घ n, d;

	अगर (t->type != V4L2_DV_BT_656_1120)
		वापस ratio;
	अगर (!(t->bt.flags & V4L2_DV_FL_HAS_PICTURE_ASPECT))
		वापस ratio;

	ratio.numerator = t->bt.width * t->bt.picture_aspect.denominator;
	ratio.denominator = t->bt.height * t->bt.picture_aspect.numerator;

	rational_best_approximation(ratio.numerator, ratio.denominator,
				    ratio.numerator, ratio.denominator, &n, &d);
	ratio.numerator = n;
	ratio.denominator = d;
	वापस ratio;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_dv_timings_aspect_ratio);

/** v4l2_calc_समयperframe - helper function to calculate समयperframe based
 *	v4l2_dv_timings fields.
 * @t - Timings क्रम the video mode.
 *
 * Calculates the expected समयperframe using the pixel घड़ी value and
 * horizontal/vertical measures. This means that v4l2_dv_timings काष्ठाure
 * must be correctly and fully filled.
 */
काष्ठा v4l2_fract v4l2_calc_समयperframe(स्थिर काष्ठा v4l2_dv_timings *t)
अणु
	स्थिर काष्ठा v4l2_bt_timings *bt = &t->bt;
	काष्ठा v4l2_fract fps_fract = अणु 1, 1 पूर्ण;
	अचिन्हित दीर्घ n, d;
	u32 htot, vtot, fps;
	u64 pclk;

	अगर (t->type != V4L2_DV_BT_656_1120)
		वापस fps_fract;

	htot = V4L2_DV_BT_FRAME_WIDTH(bt);
	vtot = V4L2_DV_BT_FRAME_HEIGHT(bt);
	pclk = bt->pixelघड़ी;

	अगर ((bt->flags & V4L2_DV_FL_CAN_DETECT_REDUCED_FPS) &&
	    (bt->flags & V4L2_DV_FL_REDUCED_FPS))
		pclk = भाग_u64(pclk * 1000ULL, 1001);

	fps = (htot * vtot) > 0 ? भाग_u64((100 * pclk), (htot * vtot)) : 0;
	अगर (!fps)
		वापस fps_fract;

	rational_best_approximation(fps, 100, fps, 100, &n, &d);

	fps_fract.numerator = d;
	fps_fract.denominator = n;
	वापस fps_fract;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_calc_समयperframe);

/*
 * CVT defines
 * Based on Coordinated Video Timings Standard
 * version 1.1 September 10, 2003
 */

#घोषणा CVT_PXL_CLK_GRAN	250000	/* pixel घड़ी granularity */
#घोषणा CVT_PXL_CLK_GRAN_RB_V2 1000	/* granularity क्रम reduced blanking v2*/

/* Normal blanking */
#घोषणा CVT_MIN_V_BPORCH	7	/* lines */
#घोषणा CVT_MIN_V_PORCH_RND	3	/* lines */
#घोषणा CVT_MIN_VSYNC_BP	550	/* min समय of vsync + back porch (us) */
#घोषणा CVT_HSYNC_PERCENT       8       /* nominal hsync as percentage of line */

/* Normal blanking क्रम CVT uses GTF to calculate horizontal blanking */
#घोषणा CVT_CELL_GRAN		8	/* अक्षरacter cell granularity */
#घोषणा CVT_M			600	/* blanking क्रमmula gradient */
#घोषणा CVT_C			40	/* blanking क्रमmula offset */
#घोषणा CVT_K			128	/* blanking क्रमmula scaling factor */
#घोषणा CVT_J			20	/* blanking क्रमmula scaling factor */
#घोषणा CVT_C_PRIME (((CVT_C - CVT_J) * CVT_K / 256) + CVT_J)
#घोषणा CVT_M_PRIME (CVT_K * CVT_M / 256)

/* Reduced Blanking */
#घोषणा CVT_RB_MIN_V_BPORCH    7       /* lines  */
#घोषणा CVT_RB_V_FPORCH        3       /* lines  */
#घोषणा CVT_RB_MIN_V_BLANK   460       /* us     */
#घोषणा CVT_RB_H_SYNC         32       /* pixels */
#घोषणा CVT_RB_H_BLANK       160       /* pixels */
/* Reduce blanking Version 2 */
#घोषणा CVT_RB_V2_H_BLANK     80       /* pixels */
#घोषणा CVT_RB_MIN_V_FPORCH    3       /* lines  */
#घोषणा CVT_RB_V2_MIN_V_FPORCH 1       /* lines  */
#घोषणा CVT_RB_V_BPORCH        6       /* lines  */

/** v4l2_detect_cvt - detect अगर the given timings follow the CVT standard
 * @frame_height - the total height of the frame (including blanking) in lines.
 * @hfreq - the horizontal frequency in Hz.
 * @vsync - the height of the vertical sync in lines.
 * @active_width - active width of image (करोes not include blanking). This
 * inक्रमmation is needed only in हाल of version 2 of reduced blanking.
 * In other हालs, this parameter करोes not have any effect on timings.
 * @polarities - the horizontal and vertical polarities (same as काष्ठा
 *		v4l2_bt_timings polarities).
 * @पूर्णांकerlaced - अगर this flag is true, it indicates पूर्णांकerlaced क्रमmat
 * @fmt - the resulting timings.
 *
 * This function will attempt to detect अगर the given values correspond to a
 * valid CVT क्रमmat. If so, then it will वापस true, and fmt will be filled
 * in with the found CVT timings.
 */
bool v4l2_detect_cvt(अचिन्हित frame_height,
		     अचिन्हित hfreq,
		     अचिन्हित vsync,
		     अचिन्हित active_width,
		     u32 polarities,
		     bool पूर्णांकerlaced,
		     काष्ठा v4l2_dv_timings *fmt)
अणु
	पूर्णांक  v_fp, v_bp, h_fp, h_bp, hsync;
	पूर्णांक  frame_width, image_height, image_width;
	bool reduced_blanking;
	bool rb_v2 = false;
	अचिन्हित pix_clk;

	अगर (vsync < 4 || vsync > 8)
		वापस false;

	अगर (polarities == V4L2_DV_VSYNC_POS_POL)
		reduced_blanking = false;
	अन्यथा अगर (polarities == V4L2_DV_HSYNC_POS_POL)
		reduced_blanking = true;
	अन्यथा
		वापस false;

	अगर (reduced_blanking && vsync == 8)
		rb_v2 = true;

	अगर (rb_v2 && active_width == 0)
		वापस false;

	अगर (!rb_v2 && vsync > 7)
		वापस false;

	अगर (hfreq == 0)
		वापस false;

	/* Vertical */
	अगर (reduced_blanking) अणु
		अगर (rb_v2) अणु
			v_bp = CVT_RB_V_BPORCH;
			v_fp = (CVT_RB_MIN_V_BLANK * hfreq) / 1000000 + 1;
			v_fp -= vsync + v_bp;

			अगर (v_fp < CVT_RB_V2_MIN_V_FPORCH)
				v_fp = CVT_RB_V2_MIN_V_FPORCH;
		पूर्ण अन्यथा अणु
			v_fp = CVT_RB_V_FPORCH;
			v_bp = (CVT_RB_MIN_V_BLANK * hfreq) / 1000000 + 1;
			v_bp -= vsync + v_fp;

			अगर (v_bp < CVT_RB_MIN_V_BPORCH)
				v_bp = CVT_RB_MIN_V_BPORCH;
		पूर्ण
	पूर्ण अन्यथा अणु
		v_fp = CVT_MIN_V_PORCH_RND;
		v_bp = (CVT_MIN_VSYNC_BP * hfreq) / 1000000 + 1 - vsync;

		अगर (v_bp < CVT_MIN_V_BPORCH)
			v_bp = CVT_MIN_V_BPORCH;
	पूर्ण

	अगर (पूर्णांकerlaced)
		image_height = (frame_height - 2 * v_fp - 2 * vsync - 2 * v_bp) & ~0x1;
	अन्यथा
		image_height = (frame_height - v_fp - vsync - v_bp + 1) & ~0x1;

	अगर (image_height < 0)
		वापस false;

	/* Aspect ratio based on vsync */
	चयन (vsync) अणु
	हाल 4:
		image_width = (image_height * 4) / 3;
		अवरोध;
	हाल 5:
		image_width = (image_height * 16) / 9;
		अवरोध;
	हाल 6:
		image_width = (image_height * 16) / 10;
		अवरोध;
	हाल 7:
		/* special हाल */
		अगर (image_height == 1024)
			image_width = (image_height * 5) / 4;
		अन्यथा अगर (image_height == 768)
			image_width = (image_height * 15) / 9;
		अन्यथा
			वापस false;
		अवरोध;
	हाल 8:
		image_width = active_width;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (!rb_v2)
		image_width = image_width & ~7;

	/* Horizontal */
	अगर (reduced_blanking) अणु
		पूर्णांक h_blank;
		पूर्णांक clk_gran;

		h_blank = rb_v2 ? CVT_RB_V2_H_BLANK : CVT_RB_H_BLANK;
		clk_gran = rb_v2 ? CVT_PXL_CLK_GRAN_RB_V2 : CVT_PXL_CLK_GRAN;

		pix_clk = (image_width + h_blank) * hfreq;
		pix_clk = (pix_clk / clk_gran) * clk_gran;

		h_bp  = h_blank / 2;
		hsync = CVT_RB_H_SYNC;
		h_fp  = h_blank - h_bp - hsync;

		frame_width = image_width + h_blank;
	पूर्ण अन्यथा अणु
		अचिन्हित ideal_duty_cycle_per_myriad =
			100 * CVT_C_PRIME - (CVT_M_PRIME * 100000) / hfreq;
		पूर्णांक h_blank;

		अगर (ideal_duty_cycle_per_myriad < 2000)
			ideal_duty_cycle_per_myriad = 2000;

		h_blank = image_width * ideal_duty_cycle_per_myriad /
					(10000 - ideal_duty_cycle_per_myriad);
		h_blank = (h_blank / (2 * CVT_CELL_GRAN)) * 2 * CVT_CELL_GRAN;

		pix_clk = (image_width + h_blank) * hfreq;
		pix_clk = (pix_clk / CVT_PXL_CLK_GRAN) * CVT_PXL_CLK_GRAN;

		h_bp = h_blank / 2;
		frame_width = image_width + h_blank;

		hsync = frame_width * CVT_HSYNC_PERCENT / 100;
		hsync = (hsync / CVT_CELL_GRAN) * CVT_CELL_GRAN;
		h_fp = h_blank - hsync - h_bp;
	पूर्ण

	fmt->type = V4L2_DV_BT_656_1120;
	fmt->bt.polarities = polarities;
	fmt->bt.width = image_width;
	fmt->bt.height = image_height;
	fmt->bt.hfrontporch = h_fp;
	fmt->bt.vfrontporch = v_fp;
	fmt->bt.hsync = hsync;
	fmt->bt.vsync = vsync;
	fmt->bt.hbackporch = frame_width - image_width - h_fp - hsync;

	अगर (!पूर्णांकerlaced) अणु
		fmt->bt.vbackporch = frame_height - image_height - v_fp - vsync;
		fmt->bt.पूर्णांकerlaced = V4L2_DV_PROGRESSIVE;
	पूर्ण अन्यथा अणु
		fmt->bt.vbackporch = (frame_height - image_height - 2 * v_fp -
				      2 * vsync) / 2;
		fmt->bt.il_vbackporch = frame_height - image_height - 2 * v_fp -
					2 * vsync - fmt->bt.vbackporch;
		fmt->bt.il_vfrontporch = v_fp;
		fmt->bt.il_vsync = vsync;
		fmt->bt.flags |= V4L2_DV_FL_HALF_LINE;
		fmt->bt.पूर्णांकerlaced = V4L2_DV_INTERLACED;
	पूर्ण

	fmt->bt.pixelघड़ी = pix_clk;
	fmt->bt.standards = V4L2_DV_BT_STD_CVT;

	अगर (reduced_blanking)
		fmt->bt.flags |= V4L2_DV_FL_REDUCED_BLANKING;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_detect_cvt);

/*
 * GTF defines
 * Based on Generalized Timing Formula Standard
 * Version 1.1 September 2, 1999
 */

#घोषणा GTF_PXL_CLK_GRAN	250000	/* pixel घड़ी granularity */

#घोषणा GTF_MIN_VSYNC_BP	550	/* min समय of vsync + back porch (us) */
#घोषणा GTF_V_FP		1	/* vertical front porch (lines) */
#घोषणा GTF_CELL_GRAN		8	/* अक्षरacter cell granularity */

/* Default */
#घोषणा GTF_D_M			600	/* blanking क्रमmula gradient */
#घोषणा GTF_D_C			40	/* blanking क्रमmula offset */
#घोषणा GTF_D_K			128	/* blanking क्रमmula scaling factor */
#घोषणा GTF_D_J			20	/* blanking क्रमmula scaling factor */
#घोषणा GTF_D_C_PRIME ((((GTF_D_C - GTF_D_J) * GTF_D_K) / 256) + GTF_D_J)
#घोषणा GTF_D_M_PRIME ((GTF_D_K * GTF_D_M) / 256)

/* Secondary */
#घोषणा GTF_S_M			3600	/* blanking क्रमmula gradient */
#घोषणा GTF_S_C			40	/* blanking क्रमmula offset */
#घोषणा GTF_S_K			128	/* blanking क्रमmula scaling factor */
#घोषणा GTF_S_J			35	/* blanking क्रमmula scaling factor */
#घोषणा GTF_S_C_PRIME ((((GTF_S_C - GTF_S_J) * GTF_S_K) / 256) + GTF_S_J)
#घोषणा GTF_S_M_PRIME ((GTF_S_K * GTF_S_M) / 256)

/** v4l2_detect_gtf - detect अगर the given timings follow the GTF standard
 * @frame_height - the total height of the frame (including blanking) in lines.
 * @hfreq - the horizontal frequency in Hz.
 * @vsync - the height of the vertical sync in lines.
 * @polarities - the horizontal and vertical polarities (same as काष्ठा
 *		v4l2_bt_timings polarities).
 * @पूर्णांकerlaced - अगर this flag is true, it indicates पूर्णांकerlaced क्रमmat
 * @aspect - preferred aspect ratio. GTF has no method of determining the
 *		aspect ratio in order to derive the image width from the
 *		image height, so it has to be passed explicitly. Usually
 *		the native screen aspect ratio is used क्रम this. If it
 *		is not filled in correctly, then 16:9 will be assumed.
 * @fmt - the resulting timings.
 *
 * This function will attempt to detect अगर the given values correspond to a
 * valid GTF क्रमmat. If so, then it will वापस true, and fmt will be filled
 * in with the found GTF timings.
 */
bool v4l2_detect_gtf(अचिन्हित frame_height,
		अचिन्हित hfreq,
		अचिन्हित vsync,
		u32 polarities,
		bool पूर्णांकerlaced,
		काष्ठा v4l2_fract aspect,
		काष्ठा v4l2_dv_timings *fmt)
अणु
	पूर्णांक pix_clk;
	पूर्णांक  v_fp, v_bp, h_fp, hsync;
	पूर्णांक frame_width, image_height, image_width;
	bool शेष_gtf;
	पूर्णांक h_blank;

	अगर (vsync != 3)
		वापस false;

	अगर (polarities == V4L2_DV_VSYNC_POS_POL)
		शेष_gtf = true;
	अन्यथा अगर (polarities == V4L2_DV_HSYNC_POS_POL)
		शेष_gtf = false;
	अन्यथा
		वापस false;

	अगर (hfreq == 0)
		वापस false;

	/* Vertical */
	v_fp = GTF_V_FP;
	v_bp = (GTF_MIN_VSYNC_BP * hfreq + 500000) / 1000000 - vsync;
	अगर (पूर्णांकerlaced)
		image_height = (frame_height - 2 * v_fp - 2 * vsync - 2 * v_bp) & ~0x1;
	अन्यथा
		image_height = (frame_height - v_fp - vsync - v_bp + 1) & ~0x1;

	अगर (image_height < 0)
		वापस false;

	अगर (aspect.numerator == 0 || aspect.denominator == 0) अणु
		aspect.numerator = 16;
		aspect.denominator = 9;
	पूर्ण
	image_width = ((image_height * aspect.numerator) / aspect.denominator);
	image_width = (image_width + GTF_CELL_GRAN/2) & ~(GTF_CELL_GRAN - 1);

	/* Horizontal */
	अगर (शेष_gtf) अणु
		u64 num;
		u32 den;

		num = ((image_width * GTF_D_C_PRIME * (u64)hfreq) -
		      ((u64)image_width * GTF_D_M_PRIME * 1000));
		den = (hfreq * (100 - GTF_D_C_PRIME) + GTF_D_M_PRIME * 1000) *
		      (2 * GTF_CELL_GRAN);
		h_blank = भाग_u64((num + (den >> 1)), den);
		h_blank *= (2 * GTF_CELL_GRAN);
	पूर्ण अन्यथा अणु
		u64 num;
		u32 den;

		num = ((image_width * GTF_S_C_PRIME * (u64)hfreq) -
		      ((u64)image_width * GTF_S_M_PRIME * 1000));
		den = (hfreq * (100 - GTF_S_C_PRIME) + GTF_S_M_PRIME * 1000) *
		      (2 * GTF_CELL_GRAN);
		h_blank = भाग_u64((num + (den >> 1)), den);
		h_blank *= (2 * GTF_CELL_GRAN);
	पूर्ण

	frame_width = image_width + h_blank;

	pix_clk = (image_width + h_blank) * hfreq;
	pix_clk = pix_clk / GTF_PXL_CLK_GRAN * GTF_PXL_CLK_GRAN;

	hsync = (frame_width * 8 + 50) / 100;
	hsync = DIV_ROUND_CLOSEST(hsync, GTF_CELL_GRAN) * GTF_CELL_GRAN;

	h_fp = h_blank / 2 - hsync;

	fmt->type = V4L2_DV_BT_656_1120;
	fmt->bt.polarities = polarities;
	fmt->bt.width = image_width;
	fmt->bt.height = image_height;
	fmt->bt.hfrontporch = h_fp;
	fmt->bt.vfrontporch = v_fp;
	fmt->bt.hsync = hsync;
	fmt->bt.vsync = vsync;
	fmt->bt.hbackporch = frame_width - image_width - h_fp - hsync;

	अगर (!पूर्णांकerlaced) अणु
		fmt->bt.vbackporch = frame_height - image_height - v_fp - vsync;
		fmt->bt.पूर्णांकerlaced = V4L2_DV_PROGRESSIVE;
	पूर्ण अन्यथा अणु
		fmt->bt.vbackporch = (frame_height - image_height - 2 * v_fp -
				      2 * vsync) / 2;
		fmt->bt.il_vbackporch = frame_height - image_height - 2 * v_fp -
					2 * vsync - fmt->bt.vbackporch;
		fmt->bt.il_vfrontporch = v_fp;
		fmt->bt.il_vsync = vsync;
		fmt->bt.flags |= V4L2_DV_FL_HALF_LINE;
		fmt->bt.पूर्णांकerlaced = V4L2_DV_INTERLACED;
	पूर्ण

	fmt->bt.pixelघड़ी = pix_clk;
	fmt->bt.standards = V4L2_DV_BT_STD_GTF;

	अगर (!शेष_gtf)
		fmt->bt.flags |= V4L2_DV_FL_REDUCED_BLANKING;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_detect_gtf);

/** v4l2_calc_aspect_ratio - calculate the aspect ratio based on bytes
 *	0x15 and 0x16 from the EDID.
 * @hor_landscape - byte 0x15 from the EDID.
 * @vert_portrait - byte 0x16 from the EDID.
 *
 * Determines the aspect ratio from the EDID.
 * See VESA Enhanced EDID standard, release A, rev 2, section 3.6.2:
 * "Horizontal and Vertical Screen Size or Aspect Ratio"
 */
काष्ठा v4l2_fract v4l2_calc_aspect_ratio(u8 hor_landscape, u8 vert_portrait)
अणु
	काष्ठा v4l2_fract aspect = अणु 16, 9 पूर्ण;
	u8 ratio;

	/* Nothing filled in, fallback to 16:9 */
	अगर (!hor_landscape && !vert_portrait)
		वापस aspect;
	/* Both filled in, so they are पूर्णांकerpreted as the screen size in cm */
	अगर (hor_landscape && vert_portrait) अणु
		aspect.numerator = hor_landscape;
		aspect.denominator = vert_portrait;
		वापस aspect;
	पूर्ण
	/* Only one is filled in, so पूर्णांकerpret them as a ratio:
	   (val + 99) / 100 */
	ratio = hor_landscape | vert_portrait;
	/* Change some rounded values पूर्णांकo the exact aspect ratio */
	अगर (ratio == 79) अणु
		aspect.numerator = 16;
		aspect.denominator = 9;
	पूर्ण अन्यथा अगर (ratio == 34) अणु
		aspect.numerator = 4;
		aspect.denominator = 3;
	पूर्ण अन्यथा अगर (ratio == 68) अणु
		aspect.numerator = 15;
		aspect.denominator = 9;
	पूर्ण अन्यथा अणु
		aspect.numerator = hor_landscape + 99;
		aspect.denominator = 100;
	पूर्ण
	अगर (hor_landscape)
		वापस aspect;
	/* The aspect ratio is क्रम portrait, so swap numerator and denominator */
	swap(aspect.denominator, aspect.numerator);
	वापस aspect;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_calc_aspect_ratio);

/** v4l2_hdmi_rx_colorimetry - determine HDMI colorimetry inक्रमmation
 *	based on various InfoFrames.
 * @avi: the AVI InfoFrame
 * @hdmi: the HDMI Venकरोr InfoFrame, may be शून्य
 * @height: the frame height
 *
 * Determines the HDMI colorimetry inक्रमmation, i.e. how the HDMI
 * pixel color data should be पूर्णांकerpreted.
 *
 * Note that some of the newer features (DCI-P3, HDR) are not yet
 * implemented: the hdmi.h header needs to be updated to the HDMI 2.0
 * and CTA-861-G standards.
 */
काष्ठा v4l2_hdmi_colorimetry
v4l2_hdmi_rx_colorimetry(स्थिर काष्ठा hdmi_avi_infoframe *avi,
			 स्थिर काष्ठा hdmi_venकरोr_infoframe *hdmi,
			 अचिन्हित पूर्णांक height)
अणु
	काष्ठा v4l2_hdmi_colorimetry c = अणु
		V4L2_COLORSPACE_SRGB,
		V4L2_YCBCR_ENC_DEFAULT,
		V4L2_QUANTIZATION_FULL_RANGE,
		V4L2_XFER_FUNC_SRGB
	पूर्ण;
	bool is_ce = avi->video_code || (hdmi && hdmi->vic);
	bool is_sdtv = height <= 576;
	bool शेष_is_lim_range_rgb = avi->video_code > 1;

	चयन (avi->colorspace) अणु
	हाल HDMI_COLORSPACE_RGB:
		/* RGB pixel encoding */
		चयन (avi->colorimetry) अणु
		हाल HDMI_COLORIMETRY_EXTENDED:
			चयन (avi->extended_colorimetry) अणु
			हाल HDMI_EXTENDED_COLORIMETRY_OPRGB:
				c.colorspace = V4L2_COLORSPACE_OPRGB;
				c.xfer_func = V4L2_XFER_FUNC_OPRGB;
				अवरोध;
			हाल HDMI_EXTENDED_COLORIMETRY_BT2020:
				c.colorspace = V4L2_COLORSPACE_BT2020;
				c.xfer_func = V4L2_XFER_FUNC_709;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		चयन (avi->quantization_range) अणु
		हाल HDMI_QUANTIZATION_RANGE_LIMITED:
			c.quantization = V4L2_QUANTIZATION_LIM_RANGE;
			अवरोध;
		हाल HDMI_QUANTIZATION_RANGE_FULL:
			अवरोध;
		शेष:
			अगर (शेष_is_lim_range_rgb)
				c.quantization = V4L2_QUANTIZATION_LIM_RANGE;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		/* YCbCr pixel encoding */
		c.quantization = V4L2_QUANTIZATION_LIM_RANGE;
		चयन (avi->colorimetry) अणु
		हाल HDMI_COLORIMETRY_NONE:
			अगर (!is_ce)
				अवरोध;
			अगर (is_sdtv) अणु
				c.colorspace = V4L2_COLORSPACE_SMPTE170M;
				c.ycbcr_enc = V4L2_YCBCR_ENC_601;
			पूर्ण अन्यथा अणु
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_709;
			पूर्ण
			c.xfer_func = V4L2_XFER_FUNC_709;
			अवरोध;
		हाल HDMI_COLORIMETRY_ITU_601:
			c.colorspace = V4L2_COLORSPACE_SMPTE170M;
			c.ycbcr_enc = V4L2_YCBCR_ENC_601;
			c.xfer_func = V4L2_XFER_FUNC_709;
			अवरोध;
		हाल HDMI_COLORIMETRY_ITU_709:
			c.colorspace = V4L2_COLORSPACE_REC709;
			c.ycbcr_enc = V4L2_YCBCR_ENC_709;
			c.xfer_func = V4L2_XFER_FUNC_709;
			अवरोध;
		हाल HDMI_COLORIMETRY_EXTENDED:
			चयन (avi->extended_colorimetry) अणु
			हाल HDMI_EXTENDED_COLORIMETRY_XV_YCC_601:
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_XV709;
				c.xfer_func = V4L2_XFER_FUNC_709;
				अवरोध;
			हाल HDMI_EXTENDED_COLORIMETRY_XV_YCC_709:
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_XV601;
				c.xfer_func = V4L2_XFER_FUNC_709;
				अवरोध;
			हाल HDMI_EXTENDED_COLORIMETRY_S_YCC_601:
				c.colorspace = V4L2_COLORSPACE_SRGB;
				c.ycbcr_enc = V4L2_YCBCR_ENC_601;
				c.xfer_func = V4L2_XFER_FUNC_SRGB;
				अवरोध;
			हाल HDMI_EXTENDED_COLORIMETRY_OPYCC_601:
				c.colorspace = V4L2_COLORSPACE_OPRGB;
				c.ycbcr_enc = V4L2_YCBCR_ENC_601;
				c.xfer_func = V4L2_XFER_FUNC_OPRGB;
				अवरोध;
			हाल HDMI_EXTENDED_COLORIMETRY_BT2020:
				c.colorspace = V4L2_COLORSPACE_BT2020;
				c.ycbcr_enc = V4L2_YCBCR_ENC_BT2020;
				c.xfer_func = V4L2_XFER_FUNC_709;
				अवरोध;
			हाल HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM:
				c.colorspace = V4L2_COLORSPACE_BT2020;
				c.ycbcr_enc = V4L2_YCBCR_ENC_BT2020_CONST_LUM;
				c.xfer_func = V4L2_XFER_FUNC_709;
				अवरोध;
			शेष: /* fall back to ITU_709 */
				c.colorspace = V4L2_COLORSPACE_REC709;
				c.ycbcr_enc = V4L2_YCBCR_ENC_709;
				c.xfer_func = V4L2_XFER_FUNC_709;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		/*
		 * YCC Quantization Range संकेतing is more-or-less broken,
		 * let's just ignore this.
		 */
		अवरोध;
	पूर्ण
	वापस c;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_hdmi_rx_colorimetry);

/**
 * v4l2_get_edid_phys_addr() - find and वापस the physical address
 *
 * @edid:	poपूर्णांकer to the EDID data
 * @size:	size in bytes of the EDID data
 * @offset:	If not %शून्य then the location of the physical address
 *		bytes in the EDID will be वापसed here. This is set to 0
 *		अगर there is no physical address found.
 *
 * Return: the physical address or CEC_PHYS_ADDR_INVALID अगर there is none.
 */
u16 v4l2_get_edid_phys_addr(स्थिर u8 *edid, अचिन्हित पूर्णांक size,
			    अचिन्हित पूर्णांक *offset)
अणु
	अचिन्हित पूर्णांक loc = cec_get_edid_spa_location(edid, size);

	अगर (offset)
		*offset = loc;
	अगर (loc == 0)
		वापस CEC_PHYS_ADDR_INVALID;
	वापस (edid[loc] << 8) | edid[loc + 1];
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_get_edid_phys_addr);

/**
 * v4l2_set_edid_phys_addr() - find and set the physical address
 *
 * @edid:	poपूर्णांकer to the EDID data
 * @size:	size in bytes of the EDID data
 * @phys_addr:	the new physical address
 *
 * This function finds the location of the physical address in the EDID
 * and fills in the given physical address and updates the checksum
 * at the end of the EDID block. It करोes nothing अगर the EDID करोesn't
 * contain a physical address.
 */
व्योम v4l2_set_edid_phys_addr(u8 *edid, अचिन्हित पूर्णांक size, u16 phys_addr)
अणु
	अचिन्हित पूर्णांक loc = cec_get_edid_spa_location(edid, size);
	u8 sum = 0;
	अचिन्हित पूर्णांक i;

	अगर (loc == 0)
		वापस;
	edid[loc] = phys_addr >> 8;
	edid[loc + 1] = phys_addr & 0xff;
	loc &= ~0x7f;

	/* update the checksum */
	क्रम (i = loc; i < loc + 127; i++)
		sum += edid[i];
	edid[i] = 256 - sum;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_set_edid_phys_addr);

/**
 * v4l2_phys_addr_क्रम_input() - calculate the PA क्रम an input
 *
 * @phys_addr:	the physical address of the parent
 * @input:	the number of the input port, must be between 1 and 15
 *
 * This function calculates a new physical address based on the input
 * port number. For example:
 *
 * PA = 0.0.0.0 and input = 2 becomes 2.0.0.0
 *
 * PA = 3.0.0.0 and input = 1 becomes 3.1.0.0
 *
 * PA = 3.2.1.0 and input = 5 becomes 3.2.1.5
 *
 * PA = 3.2.1.3 and input = 5 becomes f.f.f.f since it maxed out the depth.
 *
 * Return: the new physical address or CEC_PHYS_ADDR_INVALID.
 */
u16 v4l2_phys_addr_क्रम_input(u16 phys_addr, u8 input)
अणु
	/* Check अगर input is sane */
	अगर (WARN_ON(input == 0 || input > 0xf))
		वापस CEC_PHYS_ADDR_INVALID;

	अगर (phys_addr == 0)
		वापस input << 12;

	अगर ((phys_addr & 0x0fff) == 0)
		वापस phys_addr | (input << 8);

	अगर ((phys_addr & 0x00ff) == 0)
		वापस phys_addr | (input << 4);

	अगर ((phys_addr & 0x000f) == 0)
		वापस phys_addr | input;

	/*
	 * All nibbles are used so no valid physical addresses can be asचिन्हित
	 * to the input.
	 */
	वापस CEC_PHYS_ADDR_INVALID;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_phys_addr_क्रम_input);

/**
 * v4l2_phys_addr_validate() - validate a physical address from an EDID
 *
 * @phys_addr:	the physical address to validate
 * @parent:	अगर not %शून्य, then this is filled with the parents PA.
 * @port:	अगर not %शून्य, then this is filled with the input port.
 *
 * This validates a physical address as पढ़ो from an EDID. If the
 * PA is invalid (such as 1.0.1.0 since '0' is only allowed at the end),
 * then it will वापस -EINVAL.
 *
 * The parent PA is passed पूर्णांकo %parent and the input port is passed पूर्णांकo
 * %port. For example:
 *
 * PA = 0.0.0.0: has parent 0.0.0.0 and input port 0.
 *
 * PA = 1.0.0.0: has parent 0.0.0.0 and input port 1.
 *
 * PA = 3.2.0.0: has parent 3.0.0.0 and input port 2.
 *
 * PA = f.f.f.f: has parent f.f.f.f and input port 0.
 *
 * Return: 0 अगर the PA is valid, -EINVAL अगर not.
 */
पूर्णांक v4l2_phys_addr_validate(u16 phys_addr, u16 *parent, u16 *port)
अणु
	पूर्णांक i;

	अगर (parent)
		*parent = phys_addr;
	अगर (port)
		*port = 0;
	अगर (phys_addr == CEC_PHYS_ADDR_INVALID)
		वापस 0;
	क्रम (i = 0; i < 16; i += 4)
		अगर (phys_addr & (0xf << i))
			अवरोध;
	अगर (i == 16)
		वापस 0;
	अगर (parent)
		*parent = phys_addr & (0xfff0 << i);
	अगर (port)
		*port = (phys_addr >> i) & 0xf;
	क्रम (i += 4; i < 16; i += 4)
		अगर ((phys_addr & (0xf << i)) == 0)
			वापस -EINVAL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_phys_addr_validate);
