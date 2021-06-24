<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * v4l2-dv-timings - Internal header with dv-timings helper functions
 *
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित __V4L2_DV_TIMINGS_H
#घोषणा __V4L2_DV_TIMINGS_H

#समावेश <linux/videodev2.h>

/**
 * v4l2_calc_समयperframe - helper function to calculate समयperframe based
 *	v4l2_dv_timings fields.
 * @t: Timings क्रम the video mode.
 *
 * Calculates the expected समयperframe using the pixel घड़ी value and
 * horizontal/vertical measures. This means that v4l2_dv_timings काष्ठाure
 * must be correctly and fully filled.
 */
काष्ठा v4l2_fract v4l2_calc_समयperframe(स्थिर काष्ठा v4l2_dv_timings *t);

/*
 * v4l2_dv_timings_presets: list of all dv_timings presets.
 */
बाह्य स्थिर काष्ठा v4l2_dv_timings v4l2_dv_timings_presets[];

/**
 * प्रकार v4l2_check_dv_timings_fnc - timings check callback
 *
 * @t: the v4l2_dv_timings काष्ठा.
 * @handle: a handle from the driver.
 *
 * Returns true अगर the given timings are valid.
 */
प्रकार bool v4l2_check_dv_timings_fnc(स्थिर काष्ठा v4l2_dv_timings *t, व्योम *handle);

/**
 * v4l2_valid_dv_timings() - are these timings valid?
 *
 * @t:	  the v4l2_dv_timings काष्ठा.
 * @cap: the v4l2_dv_timings_cap capabilities.
 * @fnc: callback to check अगर this timing is OK. May be शून्य.
 * @fnc_handle: a handle that is passed on to @fnc.
 *
 * Returns true अगर the given dv_timings काष्ठा is supported by the
 * hardware capabilities and the callback function (अगर non-शून्य), वापसs
 * false otherwise.
 */
bool v4l2_valid_dv_timings(स्थिर काष्ठा v4l2_dv_timings *t,
			   स्थिर काष्ठा v4l2_dv_timings_cap *cap,
			   v4l2_check_dv_timings_fnc fnc,
			   व्योम *fnc_handle);

/**
 * v4l2_क्रमागत_dv_timings_cap() - Helper function to क्रमागतerate possible DV
 *	 timings based on capabilities
 *
 * @t:	  the v4l2_क्रमागत_dv_timings काष्ठा.
 * @cap: the v4l2_dv_timings_cap capabilities.
 * @fnc: callback to check अगर this timing is OK. May be शून्य.
 * @fnc_handle: a handle that is passed on to @fnc.
 *
 * This क्रमागतerates dv_timings using the full list of possible CEA-861 and DMT
 * timings, filtering out any timings that are not supported based on the
 * hardware capabilities and the callback function (अगर non-शून्य).
 *
 * If a valid timing क्रम the given index is found, it will fill in @t and
 * वापस 0, otherwise it वापसs -EINVAL.
 */
पूर्णांक v4l2_क्रमागत_dv_timings_cap(काष्ठा v4l2_क्रमागत_dv_timings *t,
			     स्थिर काष्ठा v4l2_dv_timings_cap *cap,
			     v4l2_check_dv_timings_fnc fnc,
			     व्योम *fnc_handle);

/**
 * v4l2_find_dv_timings_cap() - Find the बंदst timings काष्ठा
 *
 * @t:	  the v4l2_क्रमागत_dv_timings काष्ठा.
 * @cap: the v4l2_dv_timings_cap capabilities.
 * @pघड़ी_delta: maximum delta between t->pixelघड़ी and the timing काष्ठा
 *		under consideration.
 * @fnc: callback to check अगर a given timings काष्ठा is OK. May be शून्य.
 * @fnc_handle: a handle that is passed on to @fnc.
 *
 * This function tries to map the given timings to an entry in the
 * full list of possible CEA-861 and DMT timings, filtering out any timings
 * that are not supported based on the hardware capabilities and the callback
 * function (अगर non-शून्य).
 *
 * On success it will fill in @t with the found timings and it वापसs true.
 * On failure it will वापस false.
 */
bool v4l2_find_dv_timings_cap(काष्ठा v4l2_dv_timings *t,
			      स्थिर काष्ठा v4l2_dv_timings_cap *cap,
			      अचिन्हित pघड़ी_delta,
			      v4l2_check_dv_timings_fnc fnc,
			      व्योम *fnc_handle);

/**
 * v4l2_find_dv_timings_cea861_vic() - find timings based on CEA-861 VIC
 * @t:		the timings data.
 * @vic:	CEA-861 VIC code
 *
 * On success it will fill in @t with the found timings and it वापसs true.
 * On failure it will वापस false.
 */
bool v4l2_find_dv_timings_cea861_vic(काष्ठा v4l2_dv_timings *t, u8 vic);

/**
 * v4l2_match_dv_timings() - करो two timings match?
 *
 * @measured:	  the measured timings data.
 * @standard:	  the timings according to the standard.
 * @pघड़ी_delta: maximum delta in Hz between standard->pixelघड़ी and
 *		the measured timings.
 * @match_reduced_fps: अगर true, then fail अगर V4L2_DV_FL_REDUCED_FPS करोes not
 * match.
 *
 * Returns true अगर the two timings match, वापसs false otherwise.
 */
bool v4l2_match_dv_timings(स्थिर काष्ठा v4l2_dv_timings *measured,
			   स्थिर काष्ठा v4l2_dv_timings *standard,
			   अचिन्हित pघड़ी_delta, bool match_reduced_fps);

/**
 * v4l2_prपूर्णांक_dv_timings() - log the contents of a dv_timings काष्ठा
 * @dev_prefix:device prefix क्रम each log line.
 * @prefix:	additional prefix क्रम each log line, may be शून्य.
 * @t:		the timings data.
 * @detailed:	अगर true, give a detailed log.
 */
व्योम v4l2_prपूर्णांक_dv_timings(स्थिर अक्षर *dev_prefix, स्थिर अक्षर *prefix,
			   स्थिर काष्ठा v4l2_dv_timings *t, bool detailed);

/**
 * v4l2_detect_cvt - detect अगर the given timings follow the CVT standard
 *
 * @frame_height: the total height of the frame (including blanking) in lines.
 * @hfreq: the horizontal frequency in Hz.
 * @vsync: the height of the vertical sync in lines.
 * @active_width: active width of image (करोes not include blanking). This
 * inक्रमmation is needed only in हाल of version 2 of reduced blanking.
 * In other हालs, this parameter करोes not have any effect on timings.
 * @polarities: the horizontal and vertical polarities (same as काष्ठा
 *		v4l2_bt_timings polarities).
 * @पूर्णांकerlaced: अगर this flag is true, it indicates पूर्णांकerlaced क्रमmat
 * @fmt: the resulting timings.
 *
 * This function will attempt to detect अगर the given values correspond to a
 * valid CVT क्रमmat. If so, then it will वापस true, and fmt will be filled
 * in with the found CVT timings.
 */
bool v4l2_detect_cvt(अचिन्हित frame_height, अचिन्हित hfreq, अचिन्हित vsync,
		अचिन्हित active_width, u32 polarities, bool पूर्णांकerlaced,
		काष्ठा v4l2_dv_timings *fmt);

/**
 * v4l2_detect_gtf - detect अगर the given timings follow the GTF standard
 *
 * @frame_height: the total height of the frame (including blanking) in lines.
 * @hfreq: the horizontal frequency in Hz.
 * @vsync: the height of the vertical sync in lines.
 * @polarities: the horizontal and vertical polarities (same as काष्ठा
 *		v4l2_bt_timings polarities).
 * @पूर्णांकerlaced: अगर this flag is true, it indicates पूर्णांकerlaced क्रमmat
 * @aspect: preferred aspect ratio. GTF has no method of determining the
 *		aspect ratio in order to derive the image width from the
 *		image height, so it has to be passed explicitly. Usually
 *		the native screen aspect ratio is used क्रम this. If it
 *		is not filled in correctly, then 16:9 will be assumed.
 * @fmt: the resulting timings.
 *
 * This function will attempt to detect अगर the given values correspond to a
 * valid GTF क्रमmat. If so, then it will वापस true, and fmt will be filled
 * in with the found GTF timings.
 */
bool v4l2_detect_gtf(अचिन्हित frame_height, अचिन्हित hfreq, अचिन्हित vsync,
		u32 polarities, bool पूर्णांकerlaced, काष्ठा v4l2_fract aspect,
		काष्ठा v4l2_dv_timings *fmt);

/**
 * v4l2_calc_aspect_ratio - calculate the aspect ratio based on bytes
 *	0x15 and 0x16 from the EDID.
 *
 * @hor_landscape: byte 0x15 from the EDID.
 * @vert_portrait: byte 0x16 from the EDID.
 *
 * Determines the aspect ratio from the EDID.
 * See VESA Enhanced EDID standard, release A, rev 2, section 3.6.2:
 * "Horizontal and Vertical Screen Size or Aspect Ratio"
 */
काष्ठा v4l2_fract v4l2_calc_aspect_ratio(u8 hor_landscape, u8 vert_portrait);

/**
 * v4l2_dv_timings_aspect_ratio - calculate the aspect ratio based on the
 *	v4l2_dv_timings inक्रमmation.
 *
 * @t: the timings data.
 */
काष्ठा v4l2_fract v4l2_dv_timings_aspect_ratio(स्थिर काष्ठा v4l2_dv_timings *t);

/**
 * can_reduce_fps - check अगर conditions क्रम reduced fps are true.
 * @bt: v4l2 timing काष्ठाure
 *
 * For dअगरferent timings reduced fps is allowed अगर the following conditions
 * are met:
 *
 *   - For CVT timings: अगर reduced blanking v2 (vsync == 8) is true.
 *   - For CEA861 timings: अगर %V4L2_DV_FL_CAN_REDUCE_FPS flag is true.
 */
अटल अंतरभूत  bool can_reduce_fps(काष्ठा v4l2_bt_timings *bt)
अणु
	अगर ((bt->standards & V4L2_DV_BT_STD_CVT) && (bt->vsync == 8))
		वापस true;

	अगर ((bt->standards & V4L2_DV_BT_STD_CEA861) &&
	    (bt->flags & V4L2_DV_FL_CAN_REDUCE_FPS))
		वापस true;

	वापस false;
पूर्ण

/**
 * काष्ठा v4l2_hdmi_colorimetry - describes the HDMI colorimetry inक्रमmation
 * @colorspace:		क्रमागत v4l2_colorspace, the colorspace
 * @ycbcr_enc:		क्रमागत v4l2_ycbcr_encoding, Y'CbCr encoding
 * @quantization:	क्रमागत v4l2_quantization, colorspace quantization
 * @xfer_func:		क्रमागत v4l2_xfer_func, colorspace transfer function
 */
काष्ठा v4l2_hdmi_colorimetry अणु
	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization quantization;
	क्रमागत v4l2_xfer_func xfer_func;
पूर्ण;

काष्ठा hdmi_avi_infoframe;
काष्ठा hdmi_venकरोr_infoframe;

काष्ठा v4l2_hdmi_colorimetry
v4l2_hdmi_rx_colorimetry(स्थिर काष्ठा hdmi_avi_infoframe *avi,
			 स्थिर काष्ठा hdmi_venकरोr_infoframe *hdmi,
			 अचिन्हित पूर्णांक height);

u16 v4l2_get_edid_phys_addr(स्थिर u8 *edid, अचिन्हित पूर्णांक size,
			    अचिन्हित पूर्णांक *offset);
व्योम v4l2_set_edid_phys_addr(u8 *edid, अचिन्हित पूर्णांक size, u16 phys_addr);
u16 v4l2_phys_addr_क्रम_input(u16 phys_addr, u8 input);
पूर्णांक v4l2_phys_addr_validate(u16 phys_addr, u16 *parent, u16 *port);

#पूर्ण_अगर
