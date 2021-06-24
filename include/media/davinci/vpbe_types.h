<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Texas Instruments Inc
 */
#अगर_अघोषित _VPBE_TYPES_H
#घोषणा _VPBE_TYPES_H

क्रमागत vpbe_version अणु
	VPBE_VERSION_1 = 1,
	VPBE_VERSION_2,
	VPBE_VERSION_3,
पूर्ण;

/* vpbe_timing_type - Timing types used in vpbe device */
क्रमागत vpbe_enc_timings_type अणु
	VPBE_ENC_STD = 0x1,
	VPBE_ENC_DV_TIMINGS = 0x4,
	/* Used when set timings through FB device पूर्णांकerface */
	VPBE_ENC_TIMINGS_INVALID = 0x8,
पूर्ण;

/*
 * काष्ठा vpbe_enc_mode_info
 * @name: ptr to name string of the standard, "NTSC", "PAL" etc
 * @std: standard or non-standard mode. 1 - standard, 0 - nonstandard
 * @पूर्णांकerlaced: 1 - पूर्णांकerlaced, 0 - non पूर्णांकerlaced/progressive
 * @xres: x or horizontal resolution of the display
 * @yres: y or vertical resolution of the display
 * @fps: frame per second
 * @left_margin: left margin of the display
 * @right_margin: right margin of the display
 * @upper_margin: upper margin of the display
 * @lower_margin: lower margin of the display
 * @hsync_len: h-sync length
 * @vsync_len: v-sync length
 * @flags: bit field: bit usage is करोcumented below
 *
 * Description:
 *  Structure holding timing and resolution inक्रमmation of a standard.
 * Used by vpbe_device to set required non-standard timing in the
 * venc when lcd controller output is connected to a बाह्यal encoder.
 * A table of timings is मुख्यtained in vpbe device to set this in
 * venc when बाह्यal encoder is connected to lcd controller output.
 * Encoder may provide a g_dv_timings() API to override these values
 * as needed.
 *
 *  Notes
 *  ------
 *  अगर_type should be used only by encoder manager and encoder.
 *  flags usage
 *     b0 (LSB) - hsync polarity, 0 - negative, 1 - positive
 *     b1       - vsync polarity, 0 - negative, 1 - positive
 *     b2       - field id polarity, 0 - negative, 1  - positive
 */
काष्ठा vpbe_enc_mode_info अणु
	अचिन्हित अक्षर *name;
	क्रमागत vpbe_enc_timings_type timings_type;
	v4l2_std_id std_id;
	काष्ठा v4l2_dv_timings dv_timings;
	अचिन्हित पूर्णांक पूर्णांकerlaced;
	अचिन्हित पूर्णांक xres;
	अचिन्हित पूर्णांक yres;
	काष्ठा v4l2_fract aspect;
	काष्ठा v4l2_fract fps;
	अचिन्हित पूर्णांक left_margin;
	अचिन्हित पूर्णांक right_margin;
	अचिन्हित पूर्णांक upper_margin;
	अचिन्हित पूर्णांक lower_margin;
	अचिन्हित पूर्णांक hsync_len;
	अचिन्हित पूर्णांक vsync_len;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#पूर्ण_अगर
