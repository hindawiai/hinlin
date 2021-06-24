<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    V4L2 controls framework implementation.

    Copyright (C) 2010  Hans Verkuil <hverkuil@xs4all.nl>

 */

#घोषणा pr_fmt(fmt) "v4l2-ctrls: " fmt

#समावेश <linux/प्रकार.स>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ioctl.h>

#घोषणा dprपूर्णांकk(vdev, fmt, arg...) करो अणु					\
	अगर (!WARN_ON(!(vdev)) && ((vdev)->dev_debug & V4L2_DEV_DEBUG_CTRL)) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: %s: " fmt),		\
		       __func__, video_device_node_name(vdev), ##arg);	\
पूर्ण जबतक (0)

#घोषणा has_op(master, op) \
	(master->ops && master->ops->op)
#घोषणा call_op(master, op) \
	(has_op(master, op) ? master->ops->op(master) : 0)

अटल स्थिर जोड़ v4l2_ctrl_ptr ptr_null;

/* Internal temporary helper काष्ठा, one क्रम each v4l2_ext_control */
काष्ठा v4l2_ctrl_helper अणु
	/* Poपूर्णांकer to the control reference of the master control */
	काष्ठा v4l2_ctrl_ref *mref;
	/* The control ref corresponding to the v4l2_ext_control ID field. */
	काष्ठा v4l2_ctrl_ref *ref;
	/* v4l2_ext_control index of the next control beदीर्घing to the
	   same cluster, or 0 अगर there isn't any. */
	u32 next;
पूर्ण;

/* Small helper function to determine अगर the स्वतःcluster is set to manual
   mode. */
अटल bool is_cur_manual(स्थिर काष्ठा v4l2_ctrl *master)
अणु
	वापस master->is_स्वतः && master->cur.val == master->manual_mode_value;
पूर्ण

/* Same as above, but this checks the against the new value instead of the
   current value. */
अटल bool is_new_manual(स्थिर काष्ठा v4l2_ctrl *master)
अणु
	वापस master->is_स्वतः && master->val == master->manual_mode_value;
पूर्ण

/* Returns शून्य or a अक्षरacter poपूर्णांकer array containing the menu क्रम
   the given control ID. The poपूर्णांकer array ends with a शून्य poपूर्णांकer.
   An empty string signअगरies a menu entry that is invalid. This allows
   drivers to disable certain options अगर it is not supported. */
स्थिर अक्षर * स्थिर *v4l2_ctrl_get_menu(u32 id)
अणु
	अटल स्थिर अक्षर * स्थिर mpeg_audio_sampling_freq[] = अणु
		"44.1 kHz",
		"48 kHz",
		"32 kHz",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_encoding[] = अणु
		"MPEG-1/2 Layer I",
		"MPEG-1/2 Layer II",
		"MPEG-1/2 Layer III",
		"MPEG-2/4 AAC",
		"AC-3",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_l1_bitrate[] = अणु
		"32 kbps",
		"64 kbps",
		"96 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"288 kbps",
		"320 kbps",
		"352 kbps",
		"384 kbps",
		"416 kbps",
		"448 kbps",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_l2_bitrate[] = अणु
		"32 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		"384 kbps",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_l3_bitrate[] = अणु
		"32 kbps",
		"40 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_ac3_bitrate[] = अणु
		"32 kbps",
		"40 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		"384 kbps",
		"448 kbps",
		"512 kbps",
		"576 kbps",
		"640 kbps",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_mode[] = अणु
		"Stereo",
		"Joint Stereo",
		"Dual",
		"Mono",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_mode_extension[] = अणु
		"Bound 4",
		"Bound 8",
		"Bound 12",
		"Bound 16",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_emphasis[] = अणु
		"No Emphasis",
		"50/15 us",
		"CCITT J17",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_crc[] = अणु
		"No CRC",
		"16-bit CRC",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_audio_dec_playback[] = अणु
		"Auto",
		"Stereo",
		"Left",
		"Right",
		"Mono",
		"Swapped Stereo",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_video_encoding[] = अणु
		"MPEG-1",
		"MPEG-2",
		"MPEG-4 AVC",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_video_aspect[] = अणु
		"1x1",
		"4x3",
		"16x9",
		"2.21x1",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_video_bitrate_mode[] = अणु
		"Variable Bitrate",
		"Constant Bitrate",
		"Constant Quality",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_stream_type[] = अणु
		"MPEG-2 Program Stream",
		"MPEG-2 Transport Stream",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_stream_vbi_fmt[] = अणु
		"No VBI",
		"Private Packet, IVTV Format",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर camera_घातer_line_frequency[] = अणु
		"Disabled",
		"50 Hz",
		"60 Hz",
		"Auto",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर camera_exposure_स्वतः[] = अणु
		"Auto Mode",
		"Manual Mode",
		"Shutter Priority Mode",
		"Aperture Priority Mode",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर camera_exposure_metering[] = अणु
		"Average",
		"Center Weighted",
		"Spot",
		"Matrix",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर camera_स्वतः_focus_range[] = अणु
		"Auto",
		"Normal",
		"Macro",
		"Infinity",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर colorfx[] = अणु
		"None",
		"Black & White",
		"Sepia",
		"Negative",
		"Emboss",
		"Sketch",
		"Sky Blue",
		"Grass Green",
		"Skin Whiten",
		"Vivid",
		"Aqua",
		"Art Freeze",
		"Silhouette",
		"Solarization",
		"Antique",
		"Set Cb/Cr",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर स्वतः_n_preset_white_balance[] = अणु
		"Manual",
		"Auto",
		"Incandescent",
		"Fluorescent",
		"Fluorescent H",
		"Horizon",
		"Daylight",
		"Flash",
		"Cloudy",
		"Shade",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर camera_iso_sensitivity_स्वतः[] = अणु
		"Manual",
		"Auto",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर scene_mode[] = अणु
		"None",
		"Backlight",
		"Beach/Snow",
		"Candle Light",
		"Dusk/Dawn",
		"Fall Colors",
		"Fireworks",
		"Landscape",
		"Night",
		"Party/Indoor",
		"Portrait",
		"Sports",
		"Sunset",
		"Text",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर tune_emphasis[] = अणु
		"None",
		"50 Microseconds",
		"75 Microseconds",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर header_mode[] = अणु
		"Separate Buffer",
		"Joined With 1st Frame",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर multi_slice[] = अणु
		"Single",
		"Max Macroblocks",
		"Max Bytes",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर entropy_mode[] = अणु
		"CAVLC",
		"CABAC",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_h264_level[] = अणु
		"1",
		"1b",
		"1.1",
		"1.2",
		"1.3",
		"2",
		"2.1",
		"2.2",
		"3",
		"3.1",
		"3.2",
		"4",
		"4.1",
		"4.2",
		"5",
		"5.1",
		"5.2",
		"6.0",
		"6.1",
		"6.2",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर h264_loop_filter[] = अणु
		"Enabled",
		"Disabled",
		"Disabled at Slice Boundary",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर h264_profile[] = अणु
		"Baseline",
		"Constrained Baseline",
		"Main",
		"Extended",
		"High",
		"High 10",
		"High 422",
		"High 444 Predictive",
		"High 10 Intra",
		"High 422 Intra",
		"High 444 Intra",
		"CAVLC 444 Intra",
		"Scalable Baseline",
		"Scalable High",
		"Scalable High Intra",
		"Stereo High",
		"Multiview High",
		"Constrained High",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर vui_sar_idc[] = अणु
		"Unspecified",
		"1:1",
		"12:11",
		"10:11",
		"16:11",
		"40:33",
		"24:11",
		"20:11",
		"32:11",
		"80:33",
		"18:11",
		"15:11",
		"64:33",
		"160:99",
		"4:3",
		"3:2",
		"2:1",
		"Extended SAR",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर h264_fp_arrangement_type[] = अणु
		"Checkerboard",
		"Column",
		"Row",
		"Side by Side",
		"Top Bottom",
		"Temporal",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर h264_fmo_map_type[] = अणु
		"Interleaved Slices",
		"Scattered Slices",
		"Foreground with Leftover",
		"Box Out",
		"Raster Scan",
		"Wipe Scan",
		"Explicit",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर h264_decode_mode[] = अणु
		"Slice-Based",
		"Frame-Based",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर h264_start_code[] = अणु
		"No Start Code",
		"Annex B Start Code",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर h264_hierarchical_coding_type[] = अणु
		"Hier Coding B",
		"Hier Coding P",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_mpeg2_level[] = अणु
		"Low",
		"Main",
		"High 1440",
		"High",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg2_profile[] = अणु
		"Simple",
		"Main",
		"SNR Scalable",
		"Spatially Scalable",
		"High",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_mpeg4_level[] = अणु
		"0",
		"0b",
		"1",
		"2",
		"3",
		"3b",
		"4",
		"5",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg4_profile[] = अणु
		"Simple",
		"Advanced Simple",
		"Core",
		"Simple Scalable",
		"Advanced Coding Efficiency",
		शून्य,
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर vpx_golden_frame_sel[] = अणु
		"Use Previous Frame",
		"Use Previous Specific Frame",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर vp8_profile[] = अणु
		"0",
		"1",
		"2",
		"3",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर vp9_profile[] = अणु
		"0",
		"1",
		"2",
		"3",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर vp9_level[] = अणु
		"1",
		"1.1",
		"2",
		"2.1",
		"3",
		"3.1",
		"4",
		"4.1",
		"5",
		"5.1",
		"5.2",
		"6",
		"6.1",
		"6.2",
		शून्य,
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर flash_led_mode[] = अणु
		"Off",
		"Flash",
		"Torch",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर flash_strobe_source[] = अणु
		"Software",
		"External",
		शून्य,
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर jpeg_chroma_subsampling[] = अणु
		"4:4:4",
		"4:2:2",
		"4:2:0",
		"4:1:1",
		"4:1:0",
		"Gray",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर dv_tx_mode[] = अणु
		"DVI-D",
		"HDMI",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर dv_rgb_range[] = अणु
		"Automatic",
		"RGB Limited Range (16-235)",
		"RGB Full Range (0-255)",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर dv_it_content_type[] = अणु
		"Graphics",
		"Photo",
		"Cinema",
		"Game",
		"No IT Content",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर detect_md_mode[] = अणु
		"Disabled",
		"Global",
		"Threshold Grid",
		"Region Grid",
		शून्य,
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर hevc_profile[] = अणु
		"Main",
		"Main Still Picture",
		"Main 10",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_level[] = अणु
		"1",
		"2",
		"2.1",
		"3",
		"3.1",
		"4",
		"4.1",
		"5",
		"5.1",
		"5.2",
		"6",
		"6.1",
		"6.2",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_hierarchial_coding_type[] = अणु
		"B",
		"P",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_refresh_type[] = अणु
		"None",
		"CRA",
		"IDR",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_size_of_length_field[] = अणु
		"0",
		"1",
		"2",
		"4",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_tier[] = अणु
		"Main",
		"High",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_loop_filter_mode[] = अणु
		"Disabled",
		"Enabled",
		"Disabled at slice boundary",
		"NULL",
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_decode_mode[] = अणु
		"Slice-Based",
		"Frame-Based",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर hevc_start_code[] = अणु
		"No Start Code",
		"Annex B Start Code",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर camera_orientation[] = अणु
		"Front",
		"Back",
		"External",
		शून्य,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mpeg_video_frame_skip[] = अणु
		"Disabled",
		"Level Limit",
		"VBV/CPB Limit",
		शून्य,
	पूर्ण;

	चयन (id) अणु
	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		वापस mpeg_audio_sampling_freq;
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
		वापस mpeg_audio_encoding;
	हाल V4L2_CID_MPEG_AUDIO_L1_BITRATE:
		वापस mpeg_audio_l1_bitrate;
	हाल V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		वापस mpeg_audio_l2_bitrate;
	हाल V4L2_CID_MPEG_AUDIO_L3_BITRATE:
		वापस mpeg_audio_l3_bitrate;
	हाल V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		वापस mpeg_audio_ac3_bitrate;
	हाल V4L2_CID_MPEG_AUDIO_MODE:
		वापस mpeg_audio_mode;
	हाल V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		वापस mpeg_audio_mode_extension;
	हाल V4L2_CID_MPEG_AUDIO_EMPHASIS:
		वापस mpeg_audio_emphasis;
	हाल V4L2_CID_MPEG_AUDIO_CRC:
		वापस mpeg_audio_crc;
	हाल V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK:
	हाल V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK:
		वापस mpeg_audio_dec_playback;
	हाल V4L2_CID_MPEG_VIDEO_ENCODING:
		वापस mpeg_video_encoding;
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		वापस mpeg_video_aspect;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		वापस mpeg_video_bitrate_mode;
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		वापस mpeg_stream_type;
	हाल V4L2_CID_MPEG_STREAM_VBI_FMT:
		वापस mpeg_stream_vbi_fmt;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		वापस camera_घातer_line_frequency;
	हाल V4L2_CID_EXPOSURE_AUTO:
		वापस camera_exposure_स्वतः;
	हाल V4L2_CID_EXPOSURE_METERING:
		वापस camera_exposure_metering;
	हाल V4L2_CID_AUTO_FOCUS_RANGE:
		वापस camera_स्वतः_focus_range;
	हाल V4L2_CID_COLORFX:
		वापस colorfx;
	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		वापस स्वतः_n_preset_white_balance;
	हाल V4L2_CID_ISO_SENSITIVITY_AUTO:
		वापस camera_iso_sensitivity_स्वतः;
	हाल V4L2_CID_SCENE_MODE:
		वापस scene_mode;
	हाल V4L2_CID_TUNE_PREEMPHASIS:
		वापस tune_emphasis;
	हाल V4L2_CID_TUNE_DEEMPHASIS:
		वापस tune_emphasis;
	हाल V4L2_CID_FLASH_LED_MODE:
		वापस flash_led_mode;
	हाल V4L2_CID_FLASH_STROBE_SOURCE:
		वापस flash_strobe_source;
	हाल V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		वापस header_mode;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_SKIP_MODE:
		वापस mpeg_video_frame_skip;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
		वापस multi_slice;
	हाल V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		वापस entropy_mode;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		वापस mpeg_h264_level;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		वापस h264_loop_filter;
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
		वापस h264_profile;
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:
		वापस vui_sar_idc;
	हाल V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE:
		वापस h264_fp_arrangement_type;
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE:
		वापस h264_fmo_map_type;
	हाल V4L2_CID_STATELESS_H264_DECODE_MODE:
		वापस h264_decode_mode;
	हाल V4L2_CID_STATELESS_H264_START_CODE:
		वापस h264_start_code;
	हाल V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_TYPE:
		वापस h264_hierarchical_coding_type;
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL:
		वापस mpeg_mpeg2_level;
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_PROखाता:
		वापस mpeg2_profile;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		वापस mpeg_mpeg4_level;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:
		वापस mpeg4_profile;
	हाल V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:
		वापस vpx_golden_frame_sel;
	हाल V4L2_CID_MPEG_VIDEO_VP8_PROखाता:
		वापस vp8_profile;
	हाल V4L2_CID_MPEG_VIDEO_VP9_PROखाता:
		वापस vp9_profile;
	हाल V4L2_CID_MPEG_VIDEO_VP9_LEVEL:
		वापस vp9_level;
	हाल V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
		वापस jpeg_chroma_subsampling;
	हाल V4L2_CID_DV_TX_MODE:
		वापस dv_tx_mode;
	हाल V4L2_CID_DV_TX_RGB_RANGE:
	हाल V4L2_CID_DV_RX_RGB_RANGE:
		वापस dv_rgb_range;
	हाल V4L2_CID_DV_TX_IT_CONTENT_TYPE:
	हाल V4L2_CID_DV_RX_IT_CONTENT_TYPE:
		वापस dv_it_content_type;
	हाल V4L2_CID_DETECT_MD_MODE:
		वापस detect_md_mode;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_PROखाता:
		वापस hevc_profile;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:
		वापस hevc_level;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE:
		वापस hevc_hierarchial_coding_type;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE:
		वापस hevc_refresh_type;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD:
		वापस hevc_size_of_length_field;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TIER:
		वापस hevc_tier;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE:
		वापस hevc_loop_filter_mode;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_DECODE_MODE:
		वापस hevc_decode_mode;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_START_CODE:
		वापस hevc_start_code;
	हाल V4L2_CID_CAMERA_ORIENTATION:
		वापस camera_orientation;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_get_menu);

#घोषणा __v4l2_qmenu_पूर्णांक_len(arr, len) (अणु *(len) = ARRAY_SIZE(arr); arr; पूर्ण)
/*
 * Returns शून्य or an s64 type array containing the menu क्रम given
 * control ID. The total number of the menu items is वापसed in @len.
 */
स्थिर s64 *v4l2_ctrl_get_पूर्णांक_menu(u32 id, u32 *len)
अणु
	अटल स्थिर s64 qmenu_पूर्णांक_vpx_num_partitions[] = अणु
		1, 2, 4, 8,
	पूर्ण;

	अटल स्थिर s64 qmenu_पूर्णांक_vpx_num_ref_frames[] = अणु
		1, 2, 3,
	पूर्ण;

	चयन (id) अणु
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:
		वापस __v4l2_qmenu_पूर्णांक_len(qmenu_पूर्णांक_vpx_num_partitions, len);
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:
		वापस __v4l2_qmenu_पूर्णांक_len(qmenu_पूर्णांक_vpx_num_ref_frames, len);
	शेष:
		*len = 0;
		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_get_पूर्णांक_menu);

/* Return the control name. */
स्थिर अक्षर *v4l2_ctrl_get_name(u32 id)
अणु
	चयन (id) अणु
	/* USER controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_USER_CLASS:		वापस "User Controls";
	हाल V4L2_CID_BRIGHTNESS:		वापस "Brightness";
	हाल V4L2_CID_CONTRAST:			वापस "Contrast";
	हाल V4L2_CID_SATURATION:		वापस "Saturation";
	हाल V4L2_CID_HUE:			वापस "Hue";
	हाल V4L2_CID_AUDIO_VOLUME:		वापस "Volume";
	हाल V4L2_CID_AUDIO_BALANCE:		वापस "Balance";
	हाल V4L2_CID_AUDIO_BASS:		वापस "Bass";
	हाल V4L2_CID_AUDIO_TREBLE:		वापस "Treble";
	हाल V4L2_CID_AUDIO_MUTE:		वापस "Mute";
	हाल V4L2_CID_AUDIO_LOUDNESS:		वापस "Loudness";
	हाल V4L2_CID_BLACK_LEVEL:		वापस "Black Level";
	हाल V4L2_CID_AUTO_WHITE_BALANCE:	वापस "White Balance, Automatic";
	हाल V4L2_CID_DO_WHITE_BALANCE:		वापस "Do White Balance";
	हाल V4L2_CID_RED_BALANCE:		वापस "Red Balance";
	हाल V4L2_CID_BLUE_BALANCE:		वापस "Blue Balance";
	हाल V4L2_CID_GAMMA:			वापस "Gamma";
	हाल V4L2_CID_EXPOSURE:			वापस "Exposure";
	हाल V4L2_CID_AUTOGAIN:			वापस "Gain, Automatic";
	हाल V4L2_CID_GAIN:			वापस "Gain";
	हाल V4L2_CID_HFLIP:			वापस "Horizontal Flip";
	हाल V4L2_CID_VFLIP:			वापस "Vertical Flip";
	हाल V4L2_CID_POWER_LINE_FREQUENCY:	वापस "Power Line Frequency";
	हाल V4L2_CID_HUE_AUTO:			वापस "Hue, Automatic";
	हाल V4L2_CID_WHITE_BALANCE_TEMPERATURE: वापस "White Balance Temperature";
	हाल V4L2_CID_SHARPNESS:		वापस "Sharpness";
	हाल V4L2_CID_BACKLIGHT_COMPENSATION:	वापस "Backlight Compensation";
	हाल V4L2_CID_CHROMA_AGC:		वापस "Chroma AGC";
	हाल V4L2_CID_COLOR_KILLER:		वापस "Color Killer";
	हाल V4L2_CID_COLORFX:			वापस "Color Effects";
	हाल V4L2_CID_AUTOBRIGHTNESS:		वापस "Brightness, Automatic";
	हाल V4L2_CID_BAND_STOP_FILTER:		वापस "Band-Stop Filter";
	हाल V4L2_CID_ROTATE:			वापस "Rotate";
	हाल V4L2_CID_BG_COLOR:			वापस "Background Color";
	हाल V4L2_CID_CHROMA_GAIN:		वापस "Chroma Gain";
	हाल V4L2_CID_ILLUMINATORS_1:		वापस "Illuminator 1";
	हाल V4L2_CID_ILLUMINATORS_2:		वापस "Illuminator 2";
	हाल V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:	वापस "Min Number of Capture Buffers";
	हाल V4L2_CID_MIN_BUFFERS_FOR_OUTPUT:	वापस "Min Number of Output Buffers";
	हाल V4L2_CID_ALPHA_COMPONENT:		वापस "Alpha Component";
	हाल V4L2_CID_COLORFX_CBCR:		वापस "Color Effects, CbCr";

	/* Codec controls */
	/* The MPEG controls are applicable to all codec controls
	 * and the 'MPEG' part of the define is historical */
	/* Keep the order of the 'case's the same as in videodev2.h! */
	हाल V4L2_CID_CODEC_CLASS:		वापस "Codec Controls";
	हाल V4L2_CID_MPEG_STREAM_TYPE:		वापस "Stream Type";
	हाल V4L2_CID_MPEG_STREAM_PID_PMT:	वापस "Stream PMT Program ID";
	हाल V4L2_CID_MPEG_STREAM_PID_AUDIO:	वापस "Stream Audio Program ID";
	हाल V4L2_CID_MPEG_STREAM_PID_VIDEO:	वापस "Stream Video Program ID";
	हाल V4L2_CID_MPEG_STREAM_PID_PCR:	वापस "Stream PCR Program ID";
	हाल V4L2_CID_MPEG_STREAM_PES_ID_AUDIO: वापस "Stream PES Audio ID";
	हाल V4L2_CID_MPEG_STREAM_PES_ID_VIDEO: वापस "Stream PES Video ID";
	हाल V4L2_CID_MPEG_STREAM_VBI_FMT:	वापस "Stream VBI Format";
	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ: वापस "Audio Sampling Frequency";
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:	वापस "Audio Encoding";
	हाल V4L2_CID_MPEG_AUDIO_L1_BITRATE:	वापस "Audio Layer I Bitrate";
	हाल V4L2_CID_MPEG_AUDIO_L2_BITRATE:	वापस "Audio Layer II Bitrate";
	हाल V4L2_CID_MPEG_AUDIO_L3_BITRATE:	वापस "Audio Layer III Bitrate";
	हाल V4L2_CID_MPEG_AUDIO_MODE:		वापस "Audio Stereo Mode";
	हाल V4L2_CID_MPEG_AUDIO_MODE_EXTENSION: वापस "Audio Stereo Mode Extension";
	हाल V4L2_CID_MPEG_AUDIO_EMPHASIS:	वापस "Audio Emphasis";
	हाल V4L2_CID_MPEG_AUDIO_CRC:		वापस "Audio CRC";
	हाल V4L2_CID_MPEG_AUDIO_MUTE:		वापस "Audio Mute";
	हाल V4L2_CID_MPEG_AUDIO_AAC_BITRATE:	वापस "Audio AAC Bitrate";
	हाल V4L2_CID_MPEG_AUDIO_AC3_BITRATE:	वापस "Audio AC-3 Bitrate";
	हाल V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK:	वापस "Audio Playback";
	हाल V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK: वापस "Audio Multilingual Playback";
	हाल V4L2_CID_MPEG_VIDEO_ENCODING:	वापस "Video Encoding";
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:	वापस "Video Aspect";
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:	वापस "Video B Frames";
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:	वापस "Video GOP Size";
	हाल V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:	वापस "Video GOP Closure";
	हाल V4L2_CID_MPEG_VIDEO_PULLDOWN:	वापस "Video Pulldown";
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:	वापस "Video Bitrate Mode";
	हाल V4L2_CID_MPEG_VIDEO_CONSTANT_QUALITY:	वापस "Constant Quality";
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:	वापस "Video Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:	वापस "Video Peak Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION: वापस "Video Temporal Decimation";
	हाल V4L2_CID_MPEG_VIDEO_MUTE:		वापस "Video Mute";
	हाल V4L2_CID_MPEG_VIDEO_MUTE_YUV:	वापस "Video Mute YUV";
	हाल V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:	वापस "Decoder Slice Interface";
	हाल V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:	वापस "MPEG4 Loop Filter Enable";
	हाल V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:	वापस "Number of Intra Refresh MBs";
	हाल V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:		वापस "Frame Level Rate Control Enable";
	हाल V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:			वापस "H264 MB Level Rate Control";
	हाल V4L2_CID_MPEG_VIDEO_HEADER_MODE:			वापस "Sequence Header Mode";
	हाल V4L2_CID_MPEG_VIDEO_MAX_REF_PIC:			वापस "Max Number of Reference Pics";
	हाल V4L2_CID_MPEG_VIDEO_FRAME_SKIP_MODE:		वापस "Frame Skip Mode";
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY:		वापस "Display Delay";
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY_ENABLE:	वापस "Display Delay Enable";
	हाल V4L2_CID_MPEG_VIDEO_AU_DELIMITER:			वापस "Generate Access Unit Delimiters";
	हाल V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP:		वापस "H263 I-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP:		वापस "H263 P-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP:		वापस "H263 B-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H263_MIN_QP:			वापस "H263 Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H263_MAX_QP:			वापस "H263 Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:		वापस "H264 I-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:		वापस "H264 P-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:		वापस "H264 B-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_MAX_QP:			वापस "H264 Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_MIN_QP:			वापस "H264 Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM:		वापस "H264 8x8 Transform Enable";
	हाल V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE:			वापस "H264 CPB Buffer Size";
	हाल V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:		वापस "H264 Entropy Mode";
	हाल V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:			वापस "H264 I-Frame Period";
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:			वापस "H264 Level";
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:	वापस "H264 Loop Filter Alpha Offset";
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:		वापस "H264 Loop Filter Beta Offset";
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:		वापस "H264 Loop Filter Mode";
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:			वापस "H264 Profile";
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT:	वापस "Vertical Size of SAR";
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH:	वापस "Horizontal Size of SAR";
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE:		वापस "Aspect Ratio VUI Enable";
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:		वापस "VUI Aspect Ratio IDC";
	हाल V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING:	वापस "H264 Enable Frame Packing SEI";
	हाल V4L2_CID_MPEG_VIDEO_H264_SEI_FP_CURRENT_FRAME_0:	वापस "H264 Set Curr. Frame as Frame0";
	हाल V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE:	वापस "H264 FP Arrangement Type";
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO:			वापस "H264 Flexible MB Ordering";
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE:		वापस "H264 Map Type for FMO";
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO_SLICE_GROUP:		वापस "H264 FMO Number of Slice Groups";
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_सूचीECTION:	वापस "H264 FMO Direction of Change";
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_RATE:		वापस "H264 FMO Size of 1st Slice Grp";
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO_RUN_LENGTH:		वापस "H264 FMO No. of Consecutive MBs";
	हाल V4L2_CID_MPEG_VIDEO_H264_ASO:			वापस "H264 Arbitrary Slice Ordering";
	हाल V4L2_CID_MPEG_VIDEO_H264_ASO_SLICE_ORDER:		वापस "H264 ASO Slice Order";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING:	वापस "Enable H264 Hierarchical Coding";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_TYPE:	वापस "H264 Hierarchical Coding Type";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER:वापस "H264 Number of HC Layers";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER_QP:
								वापस "H264 Set QP Value for HC Layers";
	हाल V4L2_CID_MPEG_VIDEO_H264_CONSTRAINED_INTRA_PREDICTION:
								वापस "H264 Constrained Intra Pred";
	हाल V4L2_CID_MPEG_VIDEO_H264_CHROMA_QP_INDEX_OFFSET:	वापस "H264 Chroma QP Index Offset";
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_MIN_QP:		वापस "H264 I-Frame Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_MAX_QP:		वापस "H264 I-Frame Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_MIN_QP:		वापस "H264 P-Frame Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_MAX_QP:		वापस "H264 P-Frame Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_MIN_QP:		वापस "H264 B-Frame Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_MAX_QP:		वापस "H264 B-Frame Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIER_CODING_L0_BR:	वापस "H264 Hierarchical Lay 0 Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIER_CODING_L1_BR:	वापस "H264 Hierarchical Lay 1 Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIER_CODING_L2_BR:	वापस "H264 Hierarchical Lay 2 Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIER_CODING_L3_BR:	वापस "H264 Hierarchical Lay 3 Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIER_CODING_L4_BR:	वापस "H264 Hierarchical Lay 4 Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIER_CODING_L5_BR:	वापस "H264 Hierarchical Lay 5 Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_H264_HIER_CODING_L6_BR:	वापस "H264 Hierarchical Lay 6 Bitrate";
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL:			वापस "MPEG2 Level";
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_PROखाता:			वापस "MPEG2 Profile";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP:		वापस "MPEG4 I-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP:		वापस "MPEG4 P-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP:		वापस "MPEG4 B-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP:			वापस "MPEG4 Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP:			वापस "MPEG4 Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:			वापस "MPEG4 Level";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:			वापस "MPEG4 Profile";
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_QPEL:			वापस "Quarter Pixel Search Enable";
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:		वापस "Maximum Bytes in a Slice";
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:		वापस "Number of MBs in a Slice";
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:		वापस "Slice Partitioning Method";
	हाल V4L2_CID_MPEG_VIDEO_VBV_SIZE:			वापस "VBV Buffer Size";
	हाल V4L2_CID_MPEG_VIDEO_DEC_PTS:			वापस "Video Decoder PTS";
	हाल V4L2_CID_MPEG_VIDEO_DEC_FRAME:			वापस "Video Decoder Frame Count";
	हाल V4L2_CID_MPEG_VIDEO_DEC_CONCEAL_COLOR:		वापस "Video Decoder Conceal Color";
	हाल V4L2_CID_MPEG_VIDEO_VBV_DELAY:			वापस "Initial Delay for VBV Control";
	हाल V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE:		वापस "Horizontal MV Search Range";
	हाल V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE:		वापस "Vertical MV Search Range";
	हाल V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER:		वापस "Repeat Sequence Header";
	हाल V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:		वापस "Force Key Frame";
	हाल V4L2_CID_MPEG_VIDEO_BASELAYER_PRIORITY_ID:		वापस "Base Layer Priority ID";
	हाल V4L2_CID_MPEG_VIDEO_LTR_COUNT:			वापस "LTR Count";
	हाल V4L2_CID_MPEG_VIDEO_FRAME_LTR_INDEX:		वापस "Frame LTR Index";
	हाल V4L2_CID_MPEG_VIDEO_USE_LTR_FRAMES:		वापस "Use LTR Frames";
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS:		वापस "MPEG-2 Slice Parameters";
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION:		वापस "MPEG-2 Quantization Matrices";
	हाल V4L2_CID_FWHT_I_FRAME_QP:				वापस "FWHT I-Frame QP Value";
	हाल V4L2_CID_FWHT_P_FRAME_QP:				वापस "FWHT P-Frame QP Value";

	/* VPX controls */
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:		वापस "VPX Number of Partitions";
	हाल V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4:		वापस "VPX Intra Mode Decision Disable";
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:		वापस "VPX No. of Refs for P Frame";
	हाल V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL:		वापस "VPX Loop Filter Level Range";
	हाल V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS:		वापस "VPX Deblocking Effect Control";
	हाल V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD:	वापस "VPX Golden Frame Refresh Period";
	हाल V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:		वापस "VPX Golden Frame Indicator";
	हाल V4L2_CID_MPEG_VIDEO_VPX_MIN_QP:			वापस "VPX Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_VPX_MAX_QP:			वापस "VPX Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP:		वापस "VPX I-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP:		वापस "VPX P-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_VP8_PROखाता:			वापस "VP8 Profile";
	हाल V4L2_CID_MPEG_VIDEO_VP9_PROखाता:			वापस "VP9 Profile";
	हाल V4L2_CID_MPEG_VIDEO_VP9_LEVEL:			वापस "VP9 Level";

	/* HEVC controls */
	हाल V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP:		वापस "HEVC I-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP:		वापस "HEVC P-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP:		वापस "HEVC B-Frame QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP:			वापस "HEVC Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP:			वापस "HEVC Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_MIN_QP:		वापस "HEVC I-Frame Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_MAX_QP:		वापस "HEVC I-Frame Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_MIN_QP:		वापस "HEVC P-Frame Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_MAX_QP:		वापस "HEVC P-Frame Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_MIN_QP:		वापस "HEVC B-Frame Minimum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_MAX_QP:		वापस "HEVC B-Frame Maximum QP Value";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_PROखाता:			वापस "HEVC Profile";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:			वापस "HEVC Level";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TIER:			वापस "HEVC Tier";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_FRAME_RATE_RESOLUTION:	वापस "HEVC Frame Rate Resolution";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MAX_PARTITION_DEPTH:	वापस "HEVC Maximum Coding Unit Depth";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE:		वापस "HEVC Refresh Type";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_CONST_INTRA_PRED:		वापस "HEVC Constant Intra Prediction";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LOSSLESS_CU:		वापस "HEVC Lossless Encoding";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_WAVEFRONT:		वापस "HEVC Wavefront";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE:		वापस "HEVC Loop Filter";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_QP:			वापस "HEVC QP Values";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE:		वापस "HEVC Hierarchical Coding Type";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_LAYER:	वापस "HEVC Hierarchical Coding Layer";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP:	वापस "HEVC Hierarchical Layer 0 QP";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP:	वापस "HEVC Hierarchical Layer 1 QP";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP:	वापस "HEVC Hierarchical Layer 2 QP";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP:	वापस "HEVC Hierarchical Layer 3 QP";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP:	वापस "HEVC Hierarchical Layer 4 QP";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP:	वापस "HEVC Hierarchical Layer 5 QP";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP:	वापस "HEVC Hierarchical Layer 6 QP";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_BR:	वापस "HEVC Hierarchical Lay 0 BitRate";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_BR:	वापस "HEVC Hierarchical Lay 1 BitRate";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_BR:	वापस "HEVC Hierarchical Lay 2 BitRate";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_BR:	वापस "HEVC Hierarchical Lay 3 BitRate";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_BR:	वापस "HEVC Hierarchical Lay 4 BitRate";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_BR:	वापस "HEVC Hierarchical Lay 5 BitRate";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_BR:	वापस "HEVC Hierarchical Lay 6 BitRate";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_GENERAL_PB:		वापस "HEVC General PB";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TEMPORAL_ID:		वापस "HEVC Temporal ID";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_STRONG_SMOOTHING:		वापस "HEVC Strong Intra Smoothing";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_INTRA_PU_SPLIT:		वापस "HEVC Intra PU Split";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TMV_PREDICTION:		वापस "HEVC TMV Prediction";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MERGE_MV_MINUS1:	वापस "HEVC Max Num of Candidate MVs";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_WITHOUT_STARTCODE:	वापस "HEVC ENC Without Startcode";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_PERIOD:		वापस "HEVC Num of I-Frame b/w 2 IDR";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LF_BETA_OFFSET_DIV2:	वापस "HEVC Loop Filter Beta Offset";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LF_TC_OFFSET_DIV2:	वापस "HEVC Loop Filter TC Offset";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD:	वापस "HEVC Size of Length Field";
	हाल V4L2_CID_MPEG_VIDEO_REF_NUMBER_FOR_PFRAMES:	वापस "Reference Frames for a P-Frame";
	हाल V4L2_CID_MPEG_VIDEO_PREPEND_SPSPPS_TO_IDR:		वापस "Prepend SPS and PPS to IDR";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SPS:			वापस "HEVC Sequence Parameter Set";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_PPS:			वापस "HEVC Picture Parameter Set";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SLICE_PARAMS:		वापस "HEVC Slice Parameters";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_DECODE_MODE:		वापस "HEVC Decode Mode";
	हाल V4L2_CID_MPEG_VIDEO_HEVC_START_CODE:		वापस "HEVC Start Code";

	/* CAMERA controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_CAMERA_CLASS:		वापस "Camera Controls";
	हाल V4L2_CID_EXPOSURE_AUTO:		वापस "Auto Exposure";
	हाल V4L2_CID_EXPOSURE_ABSOLUTE:	वापस "Exposure Time, Absolute";
	हाल V4L2_CID_EXPOSURE_AUTO_PRIORITY:	वापस "Exposure, Dynamic Framerate";
	हाल V4L2_CID_PAN_RELATIVE:		वापस "Pan, Relative";
	हाल V4L2_CID_TILT_RELATIVE:		वापस "Tilt, Relative";
	हाल V4L2_CID_PAN_RESET:		वापस "Pan, Reset";
	हाल V4L2_CID_TILT_RESET:		वापस "Tilt, Reset";
	हाल V4L2_CID_PAN_ABSOLUTE:		वापस "Pan, Absolute";
	हाल V4L2_CID_TILT_ABSOLUTE:		वापस "Tilt, Absolute";
	हाल V4L2_CID_FOCUS_ABSOLUTE:		वापस "Focus, Absolute";
	हाल V4L2_CID_FOCUS_RELATIVE:		वापस "Focus, Relative";
	हाल V4L2_CID_FOCUS_AUTO:		वापस "Focus, Automatic Continuous";
	हाल V4L2_CID_ZOOM_ABSOLUTE:		वापस "Zoom, Absolute";
	हाल V4L2_CID_ZOOM_RELATIVE:		वापस "Zoom, Relative";
	हाल V4L2_CID_ZOOM_CONTINUOUS:		वापस "Zoom, Continuous";
	हाल V4L2_CID_PRIVACY:			वापस "Privacy";
	हाल V4L2_CID_IRIS_ABSOLUTE:		वापस "Iris, Absolute";
	हाल V4L2_CID_IRIS_RELATIVE:		वापस "Iris, Relative";
	हाल V4L2_CID_AUTO_EXPOSURE_BIAS:	वापस "Auto Exposure, Bias";
	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE: वापस "White Balance, Auto & Preset";
	हाल V4L2_CID_WIDE_DYNAMIC_RANGE:	वापस "Wide Dynamic Range";
	हाल V4L2_CID_IMAGE_STABILIZATION:	वापस "Image Stabilization";
	हाल V4L2_CID_ISO_SENSITIVITY:		वापस "ISO Sensitivity";
	हाल V4L2_CID_ISO_SENSITIVITY_AUTO:	वापस "ISO Sensitivity, Auto";
	हाल V4L2_CID_EXPOSURE_METERING:	वापस "Exposure, Metering Mode";
	हाल V4L2_CID_SCENE_MODE:		वापस "Scene Mode";
	हाल V4L2_CID_3A_LOCK:			वापस "3A Lock";
	हाल V4L2_CID_AUTO_FOCUS_START:		वापस "Auto Focus, Start";
	हाल V4L2_CID_AUTO_FOCUS_STOP:		वापस "Auto Focus, Stop";
	हाल V4L2_CID_AUTO_FOCUS_STATUS:	वापस "Auto Focus, Status";
	हाल V4L2_CID_AUTO_FOCUS_RANGE:		वापस "Auto Focus, Range";
	हाल V4L2_CID_PAN_SPEED:		वापस "Pan, Speed";
	हाल V4L2_CID_TILT_SPEED:		वापस "Tilt, Speed";
	हाल V4L2_CID_UNIT_CELL_SIZE:		वापस "Unit Cell Size";
	हाल V4L2_CID_CAMERA_ORIENTATION:	वापस "Camera Orientation";
	हाल V4L2_CID_CAMERA_SENSOR_ROTATION:	वापस "Camera Sensor Rotation";

	/* FM Radio Modulator controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_FM_TX_CLASS:		वापस "FM Radio Modulator Controls";
	हाल V4L2_CID_RDS_TX_DEVIATION:		वापस "RDS Signal Deviation";
	हाल V4L2_CID_RDS_TX_PI:		वापस "RDS Program ID";
	हाल V4L2_CID_RDS_TX_PTY:		वापस "RDS Program Type";
	हाल V4L2_CID_RDS_TX_PS_NAME:		वापस "RDS PS Name";
	हाल V4L2_CID_RDS_TX_RADIO_TEXT:	वापस "RDS Radio Text";
	हाल V4L2_CID_RDS_TX_MONO_STEREO:	वापस "RDS Stereo";
	हाल V4L2_CID_RDS_TX_ARTIFICIAL_HEAD:	वापस "RDS Artificial Head";
	हाल V4L2_CID_RDS_TX_COMPRESSED:	वापस "RDS Compressed";
	हाल V4L2_CID_RDS_TX_DYNAMIC_PTY:	वापस "RDS Dynamic PTY";
	हाल V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT: वापस "RDS Traffic Announcement";
	हाल V4L2_CID_RDS_TX_TRAFFIC_PROGRAM:	वापस "RDS Traffic Program";
	हाल V4L2_CID_RDS_TX_MUSIC_SPEECH:	वापस "RDS Music";
	हाल V4L2_CID_RDS_TX_ALT_FREQS_ENABLE:	वापस "RDS Enable Alt Frequencies";
	हाल V4L2_CID_RDS_TX_ALT_FREQS:		वापस "RDS Alternate Frequencies";
	हाल V4L2_CID_AUDIO_LIMITER_ENABLED:	वापस "Audio Limiter Feature Enabled";
	हाल V4L2_CID_AUDIO_LIMITER_RELEASE_TIME: वापस "Audio Limiter Release Time";
	हाल V4L2_CID_AUDIO_LIMITER_DEVIATION:	वापस "Audio Limiter Deviation";
	हाल V4L2_CID_AUDIO_COMPRESSION_ENABLED: वापस "Audio Compression Enabled";
	हाल V4L2_CID_AUDIO_COMPRESSION_GAIN:	वापस "Audio Compression Gain";
	हाल V4L2_CID_AUDIO_COMPRESSION_THRESHOLD: वापस "Audio Compression Threshold";
	हाल V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME: वापस "Audio Compression Attack Time";
	हाल V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME: वापस "Audio Compression Release Time";
	हाल V4L2_CID_PILOT_TONE_ENABLED:	वापस "Pilot Tone Feature Enabled";
	हाल V4L2_CID_PILOT_TONE_DEVIATION:	वापस "Pilot Tone Deviation";
	हाल V4L2_CID_PILOT_TONE_FREQUENCY:	वापस "Pilot Tone Frequency";
	हाल V4L2_CID_TUNE_PREEMPHASIS:		वापस "Pre-Emphasis";
	हाल V4L2_CID_TUNE_POWER_LEVEL:		वापस "Tune Power Level";
	हाल V4L2_CID_TUNE_ANTENNA_CAPACITOR:	वापस "Tune Antenna Capacitor";

	/* Flash controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_FLASH_CLASS:		वापस "Flash Controls";
	हाल V4L2_CID_FLASH_LED_MODE:		वापस "LED Mode";
	हाल V4L2_CID_FLASH_STROBE_SOURCE:	वापस "Strobe Source";
	हाल V4L2_CID_FLASH_STROBE:		वापस "Strobe";
	हाल V4L2_CID_FLASH_STROBE_STOP:	वापस "Stop Strobe";
	हाल V4L2_CID_FLASH_STROBE_STATUS:	वापस "Strobe Status";
	हाल V4L2_CID_FLASH_TIMEOUT:		वापस "Strobe Timeout";
	हाल V4L2_CID_FLASH_INTENSITY:		वापस "Intensity, Flash Mode";
	हाल V4L2_CID_FLASH_TORCH_INTENSITY:	वापस "Intensity, Torch Mode";
	हाल V4L2_CID_FLASH_INDICATOR_INTENSITY: वापस "Intensity, Indicator";
	हाल V4L2_CID_FLASH_FAULT:		वापस "Faults";
	हाल V4L2_CID_FLASH_CHARGE:		वापस "Charge";
	हाल V4L2_CID_FLASH_READY:		वापस "Ready to Strobe";

	/* JPEG encoder controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_JPEG_CLASS:		वापस "JPEG Compression Controls";
	हाल V4L2_CID_JPEG_CHROMA_SUBSAMPLING:	वापस "Chroma Subsampling";
	हाल V4L2_CID_JPEG_RESTART_INTERVAL:	वापस "Restart Interval";
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:	वापस "Compression Quality";
	हाल V4L2_CID_JPEG_ACTIVE_MARKER:	वापस "Active Markers";

	/* Image source controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_IMAGE_SOURCE_CLASS:	वापस "Image Source Controls";
	हाल V4L2_CID_VBLANK:			वापस "Vertical Blanking";
	हाल V4L2_CID_HBLANK:			वापस "Horizontal Blanking";
	हाल V4L2_CID_ANALOGUE_GAIN:		वापस "Analogue Gain";
	हाल V4L2_CID_TEST_PATTERN_RED:		वापस "Red Pixel Value";
	हाल V4L2_CID_TEST_PATTERN_GREENR:	वापस "Green (Red) Pixel Value";
	हाल V4L2_CID_TEST_PATTERN_BLUE:	वापस "Blue Pixel Value";
	हाल V4L2_CID_TEST_PATTERN_GREENB:	वापस "Green (Blue) Pixel Value";

	/* Image processing controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_IMAGE_PROC_CLASS:		वापस "Image Processing Controls";
	हाल V4L2_CID_LINK_FREQ:		वापस "Link Frequency";
	हाल V4L2_CID_PIXEL_RATE:		वापस "Pixel Rate";
	हाल V4L2_CID_TEST_PATTERN:		वापस "Test Pattern";
	हाल V4L2_CID_DEINTERLACING_MODE:	वापस "Deinterlacing Mode";
	हाल V4L2_CID_DIGITAL_GAIN:		वापस "Digital Gain";

	/* DV controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_DV_CLASS:			वापस "Digital Video Controls";
	हाल V4L2_CID_DV_TX_HOTPLUG:		वापस "Hotplug Present";
	हाल V4L2_CID_DV_TX_RXSENSE:		वापस "RxSense Present";
	हाल V4L2_CID_DV_TX_EDID_PRESENT:	वापस "EDID Present";
	हाल V4L2_CID_DV_TX_MODE:		वापस "Transmit Mode";
	हाल V4L2_CID_DV_TX_RGB_RANGE:		वापस "Tx RGB Quantization Range";
	हाल V4L2_CID_DV_TX_IT_CONTENT_TYPE:	वापस "Tx IT Content Type";
	हाल V4L2_CID_DV_RX_POWER_PRESENT:	वापस "Power Present";
	हाल V4L2_CID_DV_RX_RGB_RANGE:		वापस "Rx RGB Quantization Range";
	हाल V4L2_CID_DV_RX_IT_CONTENT_TYPE:	वापस "Rx IT Content Type";

	हाल V4L2_CID_FM_RX_CLASS:		वापस "FM Radio Receiver Controls";
	हाल V4L2_CID_TUNE_DEEMPHASIS:		वापस "De-Emphasis";
	हाल V4L2_CID_RDS_RECEPTION:		वापस "RDS Reception";
	हाल V4L2_CID_RF_TUNER_CLASS:		वापस "RF Tuner Controls";
	हाल V4L2_CID_RF_TUNER_RF_GAIN:		वापस "RF Gain";
	हाल V4L2_CID_RF_TUNER_LNA_GAIN_AUTO:	वापस "LNA Gain, Auto";
	हाल V4L2_CID_RF_TUNER_LNA_GAIN:	वापस "LNA Gain";
	हाल V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO:	वापस "Mixer Gain, Auto";
	हाल V4L2_CID_RF_TUNER_MIXER_GAIN:	वापस "Mixer Gain";
	हाल V4L2_CID_RF_TUNER_IF_GAIN_AUTO:	वापस "IF Gain, Auto";
	हाल V4L2_CID_RF_TUNER_IF_GAIN:		वापस "IF Gain";
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:	वापस "Bandwidth, Auto";
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:	वापस "Bandwidth";
	हाल V4L2_CID_RF_TUNER_PLL_LOCK:	वापस "PLL Lock";
	हाल V4L2_CID_RDS_RX_PTY:		वापस "RDS Program Type";
	हाल V4L2_CID_RDS_RX_PS_NAME:		वापस "RDS PS Name";
	हाल V4L2_CID_RDS_RX_RADIO_TEXT:	वापस "RDS Radio Text";
	हाल V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT: वापस "RDS Traffic Announcement";
	हाल V4L2_CID_RDS_RX_TRAFFIC_PROGRAM:	वापस "RDS Traffic Program";
	हाल V4L2_CID_RDS_RX_MUSIC_SPEECH:	वापस "RDS Music";

	/* Detection controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_DETECT_CLASS:		वापस "Detection Controls";
	हाल V4L2_CID_DETECT_MD_MODE:		वापस "Motion Detection Mode";
	हाल V4L2_CID_DETECT_MD_GLOBAL_THRESHOLD: वापस "MD Global Threshold";
	हाल V4L2_CID_DETECT_MD_THRESHOLD_GRID:	वापस "MD Threshold Grid";
	हाल V4L2_CID_DETECT_MD_REGION_GRID:	वापस "MD Region Grid";

	/* Stateless Codec controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_CODEC_STATELESS_CLASS:	वापस "Stateless Codec Controls";
	हाल V4L2_CID_STATELESS_H264_DECODE_MODE:		वापस "H264 Decode Mode";
	हाल V4L2_CID_STATELESS_H264_START_CODE:		वापस "H264 Start Code";
	हाल V4L2_CID_STATELESS_H264_SPS:			वापस "H264 Sequence Parameter Set";
	हाल V4L2_CID_STATELESS_H264_PPS:			वापस "H264 Picture Parameter Set";
	हाल V4L2_CID_STATELESS_H264_SCALING_MATRIX:		वापस "H264 Scaling Matrix";
	हाल V4L2_CID_STATELESS_H264_PRED_WEIGHTS:		वापस "H264 Prediction Weight Table";
	हाल V4L2_CID_STATELESS_H264_SLICE_PARAMS:		वापस "H264 Slice Parameters";
	हाल V4L2_CID_STATELESS_H264_DECODE_PARAMS:		वापस "H264 Decode Parameters";
	हाल V4L2_CID_STATELESS_FWHT_PARAMS:			वापस "FWHT Stateless Parameters";
	हाल V4L2_CID_STATELESS_VP8_FRAME:			वापस "VP8 Frame Parameters";

	/* Colorimetry controls */
	/* Keep the order of the 'case's the same as in v4l2-controls.h! */
	हाल V4L2_CID_COLORIMETRY_CLASS:	वापस "Colorimetry Controls";
	हाल V4L2_CID_COLORIMETRY_HDR10_CLL_INFO:		वापस "HDR10 Content Light Info";
	हाल V4L2_CID_COLORIMETRY_HDR10_MASTERING_DISPLAY:	वापस "HDR10 Mastering Display";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_get_name);

व्योम v4l2_ctrl_fill(u32 id, स्थिर अक्षर **name, क्रमागत v4l2_ctrl_type *type,
		    s64 *min, s64 *max, u64 *step, s64 *def, u32 *flags)
अणु
	*name = v4l2_ctrl_get_name(id);
	*flags = 0;

	चयन (id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
	हाल V4L2_CID_AUDIO_LOUDNESS:
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
	हाल V4L2_CID_AUTOGAIN:
	हाल V4L2_CID_HFLIP:
	हाल V4L2_CID_VFLIP:
	हाल V4L2_CID_HUE_AUTO:
	हाल V4L2_CID_CHROMA_AGC:
	हाल V4L2_CID_COLOR_KILLER:
	हाल V4L2_CID_AUTOBRIGHTNESS:
	हाल V4L2_CID_MPEG_AUDIO_MUTE:
	हाल V4L2_CID_MPEG_VIDEO_MUTE:
	हाल V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
	हाल V4L2_CID_MPEG_VIDEO_PULLDOWN:
	हाल V4L2_CID_EXPOSURE_AUTO_PRIORITY:
	हाल V4L2_CID_FOCUS_AUTO:
	हाल V4L2_CID_PRIVACY:
	हाल V4L2_CID_AUDIO_LIMITER_ENABLED:
	हाल V4L2_CID_AUDIO_COMPRESSION_ENABLED:
	हाल V4L2_CID_PILOT_TONE_ENABLED:
	हाल V4L2_CID_ILLUMINATORS_1:
	हाल V4L2_CID_ILLUMINATORS_2:
	हाल V4L2_CID_FLASH_STROBE_STATUS:
	हाल V4L2_CID_FLASH_CHARGE:
	हाल V4L2_CID_FLASH_READY:
	हाल V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
	हाल V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY_ENABLE:
	हाल V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
	हाल V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:
	हाल V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM:
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_QPEL:
	हाल V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER:
	हाल V4L2_CID_MPEG_VIDEO_AU_DELIMITER:
	हाल V4L2_CID_WIDE_DYNAMIC_RANGE:
	हाल V4L2_CID_IMAGE_STABILIZATION:
	हाल V4L2_CID_RDS_RECEPTION:
	हाल V4L2_CID_RF_TUNER_LNA_GAIN_AUTO:
	हाल V4L2_CID_RF_TUNER_MIXER_GAIN_AUTO:
	हाल V4L2_CID_RF_TUNER_IF_GAIN_AUTO:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:
	हाल V4L2_CID_RF_TUNER_PLL_LOCK:
	हाल V4L2_CID_RDS_TX_MONO_STEREO:
	हाल V4L2_CID_RDS_TX_ARTIFICIAL_HEAD:
	हाल V4L2_CID_RDS_TX_COMPRESSED:
	हाल V4L2_CID_RDS_TX_DYNAMIC_PTY:
	हाल V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT:
	हाल V4L2_CID_RDS_TX_TRAFFIC_PROGRAM:
	हाल V4L2_CID_RDS_TX_MUSIC_SPEECH:
	हाल V4L2_CID_RDS_TX_ALT_FREQS_ENABLE:
	हाल V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT:
	हाल V4L2_CID_RDS_RX_TRAFFIC_PROGRAM:
	हाल V4L2_CID_RDS_RX_MUSIC_SPEECH:
		*type = V4L2_CTRL_TYPE_BOOLEAN;
		*min = 0;
		*max = *step = 1;
		अवरोध;
	हाल V4L2_CID_ROTATE:
		*type = V4L2_CTRL_TYPE_INTEGER;
		*flags |= V4L2_CTRL_FLAG_MODIFY_LAYOUT;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE:
	हाल V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE:
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY:
		*type = V4L2_CTRL_TYPE_INTEGER;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_LTR_COUNT:
		*type = V4L2_CTRL_TYPE_INTEGER;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_LTR_INDEX:
		*type = V4L2_CTRL_TYPE_INTEGER;
		*flags |= V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_USE_LTR_FRAMES:
		*type = V4L2_CTRL_TYPE_BITMASK;
		*flags |= V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
	हाल V4L2_CID_PAN_RESET:
	हाल V4L2_CID_TILT_RESET:
	हाल V4L2_CID_FLASH_STROBE:
	हाल V4L2_CID_FLASH_STROBE_STOP:
	हाल V4L2_CID_AUTO_FOCUS_START:
	हाल V4L2_CID_AUTO_FOCUS_STOP:
	हाल V4L2_CID_DO_WHITE_BALANCE:
		*type = V4L2_CTRL_TYPE_BUTTON;
		*flags |= V4L2_CTRL_FLAG_WRITE_ONLY |
			  V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
		*min = *max = *step = *def = 0;
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
	हाल V4L2_CID_MPEG_AUDIO_L1_BITRATE:
	हाल V4L2_CID_MPEG_AUDIO_L2_BITRATE:
	हाल V4L2_CID_MPEG_AUDIO_L3_BITRATE:
	हाल V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
	हाल V4L2_CID_MPEG_AUDIO_MODE:
	हाल V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
	हाल V4L2_CID_MPEG_AUDIO_EMPHASIS:
	हाल V4L2_CID_MPEG_AUDIO_CRC:
	हाल V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK:
	हाल V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK:
	हाल V4L2_CID_MPEG_VIDEO_ENCODING:
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
	हाल V4L2_CID_MPEG_STREAM_TYPE:
	हाल V4L2_CID_MPEG_STREAM_VBI_FMT:
	हाल V4L2_CID_EXPOSURE_AUTO:
	हाल V4L2_CID_AUTO_FOCUS_RANGE:
	हाल V4L2_CID_COLORFX:
	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
	हाल V4L2_CID_TUNE_PREEMPHASIS:
	हाल V4L2_CID_FLASH_LED_MODE:
	हाल V4L2_CID_FLASH_STROBE_SOURCE:
	हाल V4L2_CID_MPEG_VIDEO_HEADER_MODE:
	हाल V4L2_CID_MPEG_VIDEO_FRAME_SKIP_MODE:
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
	हाल V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:
	हाल V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE:
	हाल V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE:
	हाल V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_TYPE:
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:
	हाल V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
	हाल V4L2_CID_ISO_SENSITIVITY_AUTO:
	हाल V4L2_CID_EXPOSURE_METERING:
	हाल V4L2_CID_SCENE_MODE:
	हाल V4L2_CID_DV_TX_MODE:
	हाल V4L2_CID_DV_TX_RGB_RANGE:
	हाल V4L2_CID_DV_TX_IT_CONTENT_TYPE:
	हाल V4L2_CID_DV_RX_RGB_RANGE:
	हाल V4L2_CID_DV_RX_IT_CONTENT_TYPE:
	हाल V4L2_CID_TEST_PATTERN:
	हाल V4L2_CID_DEINTERLACING_MODE:
	हाल V4L2_CID_TUNE_DEEMPHASIS:
	हाल V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:
	हाल V4L2_CID_MPEG_VIDEO_VP8_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_VP9_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_VP9_LEVEL:
	हाल V4L2_CID_DETECT_MD_MODE:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_TIER:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_DECODE_MODE:
	हाल V4L2_CID_MPEG_VIDEO_HEVC_START_CODE:
	हाल V4L2_CID_STATELESS_H264_DECODE_MODE:
	हाल V4L2_CID_STATELESS_H264_START_CODE:
	हाल V4L2_CID_CAMERA_ORIENTATION:
		*type = V4L2_CTRL_TYPE_MENU;
		अवरोध;
	हाल V4L2_CID_LINK_FREQ:
		*type = V4L2_CTRL_TYPE_INTEGER_MENU;
		अवरोध;
	हाल V4L2_CID_RDS_TX_PS_NAME:
	हाल V4L2_CID_RDS_TX_RADIO_TEXT:
	हाल V4L2_CID_RDS_RX_PS_NAME:
	हाल V4L2_CID_RDS_RX_RADIO_TEXT:
		*type = V4L2_CTRL_TYPE_STRING;
		अवरोध;
	हाल V4L2_CID_ISO_SENSITIVITY:
	हाल V4L2_CID_AUTO_EXPOSURE_BIAS:
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:
	हाल V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:
		*type = V4L2_CTRL_TYPE_INTEGER_MENU;
		अवरोध;
	हाल V4L2_CID_USER_CLASS:
	हाल V4L2_CID_CAMERA_CLASS:
	हाल V4L2_CID_CODEC_CLASS:
	हाल V4L2_CID_FM_TX_CLASS:
	हाल V4L2_CID_FLASH_CLASS:
	हाल V4L2_CID_JPEG_CLASS:
	हाल V4L2_CID_IMAGE_SOURCE_CLASS:
	हाल V4L2_CID_IMAGE_PROC_CLASS:
	हाल V4L2_CID_DV_CLASS:
	हाल V4L2_CID_FM_RX_CLASS:
	हाल V4L2_CID_RF_TUNER_CLASS:
	हाल V4L2_CID_DETECT_CLASS:
	हाल V4L2_CID_CODEC_STATELESS_CLASS:
	हाल V4L2_CID_COLORIMETRY_CLASS:
		*type = V4L2_CTRL_TYPE_CTRL_CLASS;
		/* You can neither पढ़ो nor ग_लिखो these */
		*flags |= V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_WRITE_ONLY;
		*min = *max = *step = *def = 0;
		अवरोध;
	हाल V4L2_CID_BG_COLOR:
		*type = V4L2_CTRL_TYPE_INTEGER;
		*step = 1;
		*min = 0;
		/* Max is calculated as RGB888 that is 2^24 */
		*max = 0xFFFFFF;
		अवरोध;
	हाल V4L2_CID_FLASH_FAULT:
	हाल V4L2_CID_JPEG_ACTIVE_MARKER:
	हाल V4L2_CID_3A_LOCK:
	हाल V4L2_CID_AUTO_FOCUS_STATUS:
	हाल V4L2_CID_DV_TX_HOTPLUG:
	हाल V4L2_CID_DV_TX_RXSENSE:
	हाल V4L2_CID_DV_TX_EDID_PRESENT:
	हाल V4L2_CID_DV_RX_POWER_PRESENT:
		*type = V4L2_CTRL_TYPE_BITMASK;
		अवरोध;
	हाल V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
	हाल V4L2_CID_MIN_BUFFERS_FOR_OUTPUT:
		*type = V4L2_CTRL_TYPE_INTEGER;
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DEC_PTS:
		*type = V4L2_CTRL_TYPE_INTEGER64;
		*flags |= V4L2_CTRL_FLAG_VOLATILE | V4L2_CTRL_FLAG_READ_ONLY;
		*min = *def = 0;
		*max = 0x1ffffffffLL;
		*step = 1;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DEC_FRAME:
		*type = V4L2_CTRL_TYPE_INTEGER64;
		*flags |= V4L2_CTRL_FLAG_VOLATILE | V4L2_CTRL_FLAG_READ_ONLY;
		*min = *def = 0;
		*max = 0x7fffffffffffffffLL;
		*step = 1;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DEC_CONCEAL_COLOR:
		*type = V4L2_CTRL_TYPE_INTEGER64;
		*min = 0;
		/* शेष क्रम 8 bit black, luma is 16, chroma is 128 */
		*def = 0x8000800010LL;
		*max = 0xffffffffffffLL;
		*step = 1;
		अवरोध;
	हाल V4L2_CID_PIXEL_RATE:
		*type = V4L2_CTRL_TYPE_INTEGER64;
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		अवरोध;
	हाल V4L2_CID_DETECT_MD_REGION_GRID:
		*type = V4L2_CTRL_TYPE_U8;
		अवरोध;
	हाल V4L2_CID_DETECT_MD_THRESHOLD_GRID:
		*type = V4L2_CTRL_TYPE_U16;
		अवरोध;
	हाल V4L2_CID_RDS_TX_ALT_FREQS:
		*type = V4L2_CTRL_TYPE_U32;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS:
		*type = V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION:
		*type = V4L2_CTRL_TYPE_MPEG2_QUANTIZATION;
		अवरोध;
	हाल V4L2_CID_STATELESS_FWHT_PARAMS:
		*type = V4L2_CTRL_TYPE_FWHT_PARAMS;
		अवरोध;
	हाल V4L2_CID_STATELESS_H264_SPS:
		*type = V4L2_CTRL_TYPE_H264_SPS;
		अवरोध;
	हाल V4L2_CID_STATELESS_H264_PPS:
		*type = V4L2_CTRL_TYPE_H264_PPS;
		अवरोध;
	हाल V4L2_CID_STATELESS_H264_SCALING_MATRIX:
		*type = V4L2_CTRL_TYPE_H264_SCALING_MATRIX;
		अवरोध;
	हाल V4L2_CID_STATELESS_H264_SLICE_PARAMS:
		*type = V4L2_CTRL_TYPE_H264_SLICE_PARAMS;
		अवरोध;
	हाल V4L2_CID_STATELESS_H264_DECODE_PARAMS:
		*type = V4L2_CTRL_TYPE_H264_DECODE_PARAMS;
		अवरोध;
	हाल V4L2_CID_STATELESS_H264_PRED_WEIGHTS:
		*type = V4L2_CTRL_TYPE_H264_PRED_WEIGHTS;
		अवरोध;
	हाल V4L2_CID_STATELESS_VP8_FRAME:
		*type = V4L2_CTRL_TYPE_VP8_FRAME;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SPS:
		*type = V4L2_CTRL_TYPE_HEVC_SPS;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_PPS:
		*type = V4L2_CTRL_TYPE_HEVC_PPS;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_SLICE_PARAMS:
		*type = V4L2_CTRL_TYPE_HEVC_SLICE_PARAMS;
		अवरोध;
	हाल V4L2_CID_UNIT_CELL_SIZE:
		*type = V4L2_CTRL_TYPE_AREA;
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		अवरोध;
	हाल V4L2_CID_COLORIMETRY_HDR10_CLL_INFO:
		*type = V4L2_CTRL_TYPE_HDR10_CLL_INFO;
		अवरोध;
	हाल V4L2_CID_COLORIMETRY_HDR10_MASTERING_DISPLAY:
		*type = V4L2_CTRL_TYPE_HDR10_MASTERING_DISPLAY;
		अवरोध;
	शेष:
		*type = V4L2_CTRL_TYPE_INTEGER;
		अवरोध;
	पूर्ण
	चयन (id) अणु
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
	हाल V4L2_CID_MPEG_AUDIO_MODE:
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		*flags |= V4L2_CTRL_FLAG_UPDATE;
		अवरोध;
	हाल V4L2_CID_AUDIO_VOLUME:
	हाल V4L2_CID_AUDIO_BALANCE:
	हाल V4L2_CID_AUDIO_BASS:
	हाल V4L2_CID_AUDIO_TREBLE:
	हाल V4L2_CID_BRIGHTNESS:
	हाल V4L2_CID_CONTRAST:
	हाल V4L2_CID_SATURATION:
	हाल V4L2_CID_HUE:
	हाल V4L2_CID_RED_BALANCE:
	हाल V4L2_CID_BLUE_BALANCE:
	हाल V4L2_CID_GAMMA:
	हाल V4L2_CID_SHARPNESS:
	हाल V4L2_CID_CHROMA_GAIN:
	हाल V4L2_CID_RDS_TX_DEVIATION:
	हाल V4L2_CID_AUDIO_LIMITER_RELEASE_TIME:
	हाल V4L2_CID_AUDIO_LIMITER_DEVIATION:
	हाल V4L2_CID_AUDIO_COMPRESSION_GAIN:
	हाल V4L2_CID_AUDIO_COMPRESSION_THRESHOLD:
	हाल V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME:
	हाल V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME:
	हाल V4L2_CID_PILOT_TONE_DEVIATION:
	हाल V4L2_CID_PILOT_TONE_FREQUENCY:
	हाल V4L2_CID_TUNE_POWER_LEVEL:
	हाल V4L2_CID_TUNE_ANTENNA_CAPACITOR:
	हाल V4L2_CID_RF_TUNER_RF_GAIN:
	हाल V4L2_CID_RF_TUNER_LNA_GAIN:
	हाल V4L2_CID_RF_TUNER_MIXER_GAIN:
	हाल V4L2_CID_RF_TUNER_IF_GAIN:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:
	हाल V4L2_CID_DETECT_MD_GLOBAL_THRESHOLD:
		*flags |= V4L2_CTRL_FLAG_SLIDER;
		अवरोध;
	हाल V4L2_CID_PAN_RELATIVE:
	हाल V4L2_CID_TILT_RELATIVE:
	हाल V4L2_CID_FOCUS_RELATIVE:
	हाल V4L2_CID_IRIS_RELATIVE:
	हाल V4L2_CID_ZOOM_RELATIVE:
		*flags |= V4L2_CTRL_FLAG_WRITE_ONLY |
			  V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
		अवरोध;
	हाल V4L2_CID_FLASH_STROBE_STATUS:
	हाल V4L2_CID_AUTO_FOCUS_STATUS:
	हाल V4L2_CID_FLASH_READY:
	हाल V4L2_CID_DV_TX_HOTPLUG:
	हाल V4L2_CID_DV_TX_RXSENSE:
	हाल V4L2_CID_DV_TX_EDID_PRESENT:
	हाल V4L2_CID_DV_RX_POWER_PRESENT:
	हाल V4L2_CID_DV_RX_IT_CONTENT_TYPE:
	हाल V4L2_CID_RDS_RX_PTY:
	हाल V4L2_CID_RDS_RX_PS_NAME:
	हाल V4L2_CID_RDS_RX_RADIO_TEXT:
	हाल V4L2_CID_RDS_RX_TRAFFIC_ANNOUNCEMENT:
	हाल V4L2_CID_RDS_RX_TRAFFIC_PROGRAM:
	हाल V4L2_CID_RDS_RX_MUSIC_SPEECH:
	हाल V4L2_CID_CAMERA_ORIENTATION:
	हाल V4L2_CID_CAMERA_SENSOR_ROTATION:
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		अवरोध;
	हाल V4L2_CID_RF_TUNER_PLL_LOCK:
		*flags |= V4L2_CTRL_FLAG_VOLATILE;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_fill);

अटल u32 user_flags(स्थिर काष्ठा v4l2_ctrl *ctrl)
अणु
	u32 flags = ctrl->flags;

	अगर (ctrl->is_ptr)
		flags |= V4L2_CTRL_FLAG_HAS_PAYLOAD;

	वापस flags;
पूर्ण

अटल व्योम fill_event(काष्ठा v4l2_event *ev, काष्ठा v4l2_ctrl *ctrl, u32 changes)
अणु
	स_रखो(ev, 0, माप(*ev));
	ev->type = V4L2_EVENT_CTRL;
	ev->id = ctrl->id;
	ev->u.ctrl.changes = changes;
	ev->u.ctrl.type = ctrl->type;
	ev->u.ctrl.flags = user_flags(ctrl);
	अगर (ctrl->is_ptr)
		ev->u.ctrl.value64 = 0;
	अन्यथा
		ev->u.ctrl.value64 = *ctrl->p_cur.p_s64;
	ev->u.ctrl.minimum = ctrl->minimum;
	ev->u.ctrl.maximum = ctrl->maximum;
	अगर (ctrl->type == V4L2_CTRL_TYPE_MENU
	    || ctrl->type == V4L2_CTRL_TYPE_INTEGER_MENU)
		ev->u.ctrl.step = 1;
	अन्यथा
		ev->u.ctrl.step = ctrl->step;
	ev->u.ctrl.शेष_value = ctrl->शेष_value;
पूर्ण

अटल व्योम send_event(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl *ctrl, u32 changes)
अणु
	काष्ठा v4l2_event ev;
	काष्ठा v4l2_subscribed_event *sev;

	अगर (list_empty(&ctrl->ev_subs))
		वापस;
	fill_event(&ev, ctrl, changes);

	list_क्रम_each_entry(sev, &ctrl->ev_subs, node)
		अगर (sev->fh != fh ||
		    (sev->flags & V4L2_EVENT_SUB_FL_ALLOW_FEEDBACK))
			v4l2_event_queue_fh(sev->fh, &ev);
पूर्ण

अटल bool std_equal(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
		      जोड़ v4l2_ctrl_ptr ptr1,
		      जोड़ v4l2_ctrl_ptr ptr2)
अणु
	चयन (ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_BUTTON:
		वापस false;
	हाल V4L2_CTRL_TYPE_STRING:
		idx *= ctrl->elem_size;
		/* strings are always 0-terminated */
		वापस !म_भेद(ptr1.p_अक्षर + idx, ptr2.p_अक्षर + idx);
	हाल V4L2_CTRL_TYPE_INTEGER64:
		वापस ptr1.p_s64[idx] == ptr2.p_s64[idx];
	हाल V4L2_CTRL_TYPE_U8:
		वापस ptr1.p_u8[idx] == ptr2.p_u8[idx];
	हाल V4L2_CTRL_TYPE_U16:
		वापस ptr1.p_u16[idx] == ptr2.p_u16[idx];
	हाल V4L2_CTRL_TYPE_U32:
		वापस ptr1.p_u32[idx] == ptr2.p_u32[idx];
	शेष:
		अगर (ctrl->is_पूर्णांक)
			वापस ptr1.p_s32[idx] == ptr2.p_s32[idx];
		idx *= ctrl->elem_size;
		वापस !स_भेद(ptr1.p_स्थिर + idx, ptr2.p_स्थिर + idx,
			       ctrl->elem_size);
	पूर्ण
पूर्ण

अटल व्योम std_init_compound(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
			      जोड़ v4l2_ctrl_ptr ptr)
अणु
	काष्ठा v4l2_ctrl_mpeg2_slice_params *p_mpeg2_slice_params;
	काष्ठा v4l2_ctrl_vp8_frame *p_vp8_frame;
	काष्ठा v4l2_ctrl_fwht_params *p_fwht_params;
	व्योम *p = ptr.p + idx * ctrl->elem_size;

	अगर (ctrl->p_def.p_स्थिर)
		स_नकल(p, ctrl->p_def.p_स्थिर, ctrl->elem_size);
	अन्यथा
		स_रखो(p, 0, ctrl->elem_size);

	/*
	 * The cast is needed to get rid of a gcc warning complaining that
	 * V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS is not part of the
	 * v4l2_ctrl_type क्रमागत.
	 */
	चयन ((u32)ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS:
		p_mpeg2_slice_params = p;
		/* 4:2:0 */
		p_mpeg2_slice_params->sequence.chroma_क्रमmat = 1;
		/* पूर्णांकerlaced top field */
		p_mpeg2_slice_params->picture.picture_काष्ठाure = 1;
		p_mpeg2_slice_params->picture.picture_coding_type =
					V4L2_MPEG2_PICTURE_CODING_TYPE_I;
		अवरोध;
	हाल V4L2_CTRL_TYPE_VP8_FRAME:
		p_vp8_frame = p;
		p_vp8_frame->num_dct_parts = 1;
		अवरोध;
	हाल V4L2_CTRL_TYPE_FWHT_PARAMS:
		p_fwht_params = p;
		p_fwht_params->version = V4L2_FWHT_VERSION;
		p_fwht_params->width = 1280;
		p_fwht_params->height = 720;
		p_fwht_params->flags = V4L2_FWHT_FL_PIXENC_YUV |
			(2 << V4L2_FWHT_FL_COMPONENTS_NUM_OFFSET);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम std_init(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
		     जोड़ v4l2_ctrl_ptr ptr)
अणु
	चयन (ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_STRING:
		idx *= ctrl->elem_size;
		स_रखो(ptr.p_अक्षर + idx, ' ', ctrl->minimum);
		ptr.p_अक्षर[idx + ctrl->minimum] = '\0';
		अवरोध;
	हाल V4L2_CTRL_TYPE_INTEGER64:
		ptr.p_s64[idx] = ctrl->शेष_value;
		अवरोध;
	हाल V4L2_CTRL_TYPE_INTEGER:
	हाल V4L2_CTRL_TYPE_INTEGER_MENU:
	हाल V4L2_CTRL_TYPE_MENU:
	हाल V4L2_CTRL_TYPE_BITMASK:
	हाल V4L2_CTRL_TYPE_BOOLEAN:
		ptr.p_s32[idx] = ctrl->शेष_value;
		अवरोध;
	हाल V4L2_CTRL_TYPE_BUTTON:
	हाल V4L2_CTRL_TYPE_CTRL_CLASS:
		ptr.p_s32[idx] = 0;
		अवरोध;
	हाल V4L2_CTRL_TYPE_U8:
		ptr.p_u8[idx] = ctrl->शेष_value;
		अवरोध;
	हाल V4L2_CTRL_TYPE_U16:
		ptr.p_u16[idx] = ctrl->शेष_value;
		अवरोध;
	हाल V4L2_CTRL_TYPE_U32:
		ptr.p_u32[idx] = ctrl->शेष_value;
		अवरोध;
	शेष:
		std_init_compound(ctrl, idx, ptr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम std_log(स्थिर काष्ठा v4l2_ctrl *ctrl)
अणु
	जोड़ v4l2_ctrl_ptr ptr = ctrl->p_cur;

	अगर (ctrl->is_array) अणु
		अचिन्हित i;

		क्रम (i = 0; i < ctrl->nr_of_dims; i++)
			pr_cont("[%u]", ctrl->dims[i]);
		pr_cont(" ");
	पूर्ण

	चयन (ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER:
		pr_cont("%d", *ptr.p_s32);
		अवरोध;
	हाल V4L2_CTRL_TYPE_BOOLEAN:
		pr_cont("%s", *ptr.p_s32 ? "true" : "false");
		अवरोध;
	हाल V4L2_CTRL_TYPE_MENU:
		pr_cont("%s", ctrl->qmenu[*ptr.p_s32]);
		अवरोध;
	हाल V4L2_CTRL_TYPE_INTEGER_MENU:
		pr_cont("%lld", ctrl->qmenu_पूर्णांक[*ptr.p_s32]);
		अवरोध;
	हाल V4L2_CTRL_TYPE_BITMASK:
		pr_cont("0x%08x", *ptr.p_s32);
		अवरोध;
	हाल V4L2_CTRL_TYPE_INTEGER64:
		pr_cont("%lld", *ptr.p_s64);
		अवरोध;
	हाल V4L2_CTRL_TYPE_STRING:
		pr_cont("%s", ptr.p_अक्षर);
		अवरोध;
	हाल V4L2_CTRL_TYPE_U8:
		pr_cont("%u", (अचिन्हित)*ptr.p_u8);
		अवरोध;
	हाल V4L2_CTRL_TYPE_U16:
		pr_cont("%u", (अचिन्हित)*ptr.p_u16);
		अवरोध;
	हाल V4L2_CTRL_TYPE_U32:
		pr_cont("%u", (अचिन्हित)*ptr.p_u32);
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_SPS:
		pr_cont("H264_SPS");
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_PPS:
		pr_cont("H264_PPS");
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_SCALING_MATRIX:
		pr_cont("H264_SCALING_MATRIX");
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_SLICE_PARAMS:
		pr_cont("H264_SLICE_PARAMS");
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_DECODE_PARAMS:
		pr_cont("H264_DECODE_PARAMS");
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_PRED_WEIGHTS:
		pr_cont("H264_PRED_WEIGHTS");
		अवरोध;
	हाल V4L2_CTRL_TYPE_FWHT_PARAMS:
		pr_cont("FWHT_PARAMS");
		अवरोध;
	हाल V4L2_CTRL_TYPE_VP8_FRAME:
		pr_cont("VP8_FRAME");
		अवरोध;
	हाल V4L2_CTRL_TYPE_HDR10_CLL_INFO:
		pr_cont("HDR10_CLL_INFO");
		अवरोध;
	हाल V4L2_CTRL_TYPE_HDR10_MASTERING_DISPLAY:
		pr_cont("HDR10_MASTERING_DISPLAY");
		अवरोध;
	शेष:
		pr_cont("unknown type %d", ctrl->type);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Round towards the बंदst legal value. Be careful when we are
 * बंद to the maximum range of the control type to prevent
 * wrap-arounds.
 */
#घोषणा ROUND_TO_RANGE(val, offset_type, ctrl)			\
(अणु								\
	offset_type offset;					\
	अगर ((ctrl)->maximum >= 0 &&				\
	    val >= (ctrl)->maximum - (s32)((ctrl)->step / 2))	\
		val = (ctrl)->maximum;				\
	अन्यथा							\
		val += (s32)((ctrl)->step / 2);			\
	val = clamp_t(typeof(val), val,				\
		      (ctrl)->minimum, (ctrl)->maximum);	\
	offset = (val) - (ctrl)->minimum;			\
	offset = (ctrl)->step * (offset / (u32)(ctrl)->step);	\
	val = (ctrl)->minimum + offset;				\
	0;							\
पूर्ण)

/* Validate a new control */

#घोषणा zero_padding(s) \
	स_रखो(&(s).padding, 0, माप((s).padding))
#घोषणा zero_reserved(s) \
	स_रखो(&(s).reserved, 0, माप((s).reserved))

/*
 * Compound controls validation requires setting unused fields/flags to zero
 * in order to properly detect unchanged controls with std_equal's स_भेद.
 */
अटल पूर्णांक std_validate_compound(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
				 जोड़ v4l2_ctrl_ptr ptr)
अणु
	काष्ठा v4l2_ctrl_mpeg2_slice_params *p_mpeg2_slice_params;
	काष्ठा v4l2_ctrl_vp8_frame *p_vp8_frame;
	काष्ठा v4l2_ctrl_fwht_params *p_fwht_params;
	काष्ठा v4l2_ctrl_h264_sps *p_h264_sps;
	काष्ठा v4l2_ctrl_h264_pps *p_h264_pps;
	काष्ठा v4l2_ctrl_h264_pred_weights *p_h264_pred_weights;
	काष्ठा v4l2_ctrl_h264_slice_params *p_h264_slice_params;
	काष्ठा v4l2_ctrl_h264_decode_params *p_h264_dec_params;
	काष्ठा v4l2_ctrl_hevc_sps *p_hevc_sps;
	काष्ठा v4l2_ctrl_hevc_pps *p_hevc_pps;
	काष्ठा v4l2_ctrl_hevc_slice_params *p_hevc_slice_params;
	काष्ठा v4l2_ctrl_hdr10_mastering_display *p_hdr10_mastering;
	काष्ठा v4l2_area *area;
	व्योम *p = ptr.p + idx * ctrl->elem_size;
	अचिन्हित पूर्णांक i;

	चयन ((u32)ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS:
		p_mpeg2_slice_params = p;

		चयन (p_mpeg2_slice_params->sequence.chroma_क्रमmat) अणु
		हाल 1: /* 4:2:0 */
		हाल 2: /* 4:2:2 */
		हाल 3: /* 4:4:4 */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (p_mpeg2_slice_params->picture.पूर्णांकra_dc_precision) अणु
		हाल 0: /* 8 bits */
		हाल 1: /* 9 bits */
		हाल 2: /* 10 bits */
		हाल 3: /* 11 bits */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (p_mpeg2_slice_params->picture.picture_काष्ठाure) अणु
		हाल 1: /* पूर्णांकerlaced top field */
		हाल 2: /* पूर्णांकerlaced bottom field */
		हाल 3: /* progressive */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (p_mpeg2_slice_params->picture.picture_coding_type) अणु
		हाल V4L2_MPEG2_PICTURE_CODING_TYPE_I:
		हाल V4L2_MPEG2_PICTURE_CODING_TYPE_P:
		हाल V4L2_MPEG2_PICTURE_CODING_TYPE_B:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अवरोध;

	हाल V4L2_CTRL_TYPE_MPEG2_QUANTIZATION:
		अवरोध;

	हाल V4L2_CTRL_TYPE_FWHT_PARAMS:
		p_fwht_params = p;
		अगर (p_fwht_params->version < V4L2_FWHT_VERSION)
			वापस -EINVAL;
		अगर (!p_fwht_params->width || !p_fwht_params->height)
			वापस -EINVAL;
		अवरोध;

	हाल V4L2_CTRL_TYPE_H264_SPS:
		p_h264_sps = p;

		/* Some syntax elements are only conditionally valid */
		अगर (p_h264_sps->pic_order_cnt_type != 0) अणु
			p_h264_sps->log2_max_pic_order_cnt_lsb_minus4 = 0;
		पूर्ण अन्यथा अगर (p_h264_sps->pic_order_cnt_type != 1) अणु
			p_h264_sps->num_ref_frames_in_pic_order_cnt_cycle = 0;
			p_h264_sps->offset_क्रम_non_ref_pic = 0;
			p_h264_sps->offset_क्रम_top_to_bottom_field = 0;
			स_रखो(&p_h264_sps->offset_क्रम_ref_frame, 0,
			       माप(p_h264_sps->offset_क्रम_ref_frame));
		पूर्ण

		अगर (!V4L2_H264_SPS_HAS_CHROMA_FORMAT(p_h264_sps)) अणु
			p_h264_sps->chroma_क्रमmat_idc = 1;
			p_h264_sps->bit_depth_luma_minus8 = 0;
			p_h264_sps->bit_depth_chroma_minus8 = 0;

			p_h264_sps->flags &=
				~V4L2_H264_SPS_FLAG_QPPRIME_Y_ZERO_TRANSFORM_BYPASS;

			अगर (p_h264_sps->chroma_क्रमmat_idc < 3)
				p_h264_sps->flags &=
					~V4L2_H264_SPS_FLAG_SEPARATE_COLOUR_PLANE;
		पूर्ण

		अगर (p_h264_sps->flags & V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY)
			p_h264_sps->flags &=
				~V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD;

		/*
		 * Chroma 4:2:2 क्रमmat require at least High 4:2:2 profile.
		 *
		 * The H264 specअगरication and well-known parser implementations
		 * use profile-idc values directly, as that is clearer and
		 * less ambiguous. We करो the same here.
		 */
		अगर (p_h264_sps->profile_idc < 122 &&
		    p_h264_sps->chroma_क्रमmat_idc > 1)
			वापस -EINVAL;
		/* Chroma 4:4:4 क्रमmat require at least High 4:2:2 profile */
		अगर (p_h264_sps->profile_idc < 244 &&
		    p_h264_sps->chroma_क्रमmat_idc > 2)
			वापस -EINVAL;
		अगर (p_h264_sps->chroma_क्रमmat_idc > 3)
			वापस -EINVAL;

		अगर (p_h264_sps->bit_depth_luma_minus8 > 6)
			वापस -EINVAL;
		अगर (p_h264_sps->bit_depth_chroma_minus8 > 6)
			वापस -EINVAL;
		अगर (p_h264_sps->log2_max_frame_num_minus4 > 12)
			वापस -EINVAL;
		अगर (p_h264_sps->pic_order_cnt_type > 2)
			वापस -EINVAL;
		अगर (p_h264_sps->log2_max_pic_order_cnt_lsb_minus4 > 12)
			वापस -EINVAL;
		अगर (p_h264_sps->max_num_ref_frames > V4L2_H264_REF_LIST_LEN)
			वापस -EINVAL;
		अवरोध;

	हाल V4L2_CTRL_TYPE_H264_PPS:
		p_h264_pps = p;

		अगर (p_h264_pps->num_slice_groups_minus1 > 7)
			वापस -EINVAL;
		अगर (p_h264_pps->num_ref_idx_l0_शेष_active_minus1 >
		    (V4L2_H264_REF_LIST_LEN - 1))
			वापस -EINVAL;
		अगर (p_h264_pps->num_ref_idx_l1_शेष_active_minus1 >
		    (V4L2_H264_REF_LIST_LEN - 1))
			वापस -EINVAL;
		अगर (p_h264_pps->weighted_bipred_idc > 2)
			वापस -EINVAL;
		/*
		 * pic_init_qp_minus26 shall be in the range of
		 * -(26 + QpBdOffset_y) to +25, inclusive,
		 *  where QpBdOffset_y is 6 * bit_depth_luma_minus8
		 */
		अगर (p_h264_pps->pic_init_qp_minus26 < -62 ||
		    p_h264_pps->pic_init_qp_minus26 > 25)
			वापस -EINVAL;
		अगर (p_h264_pps->pic_init_qs_minus26 < -26 ||
		    p_h264_pps->pic_init_qs_minus26 > 25)
			वापस -EINVAL;
		अगर (p_h264_pps->chroma_qp_index_offset < -12 ||
		    p_h264_pps->chroma_qp_index_offset > 12)
			वापस -EINVAL;
		अगर (p_h264_pps->second_chroma_qp_index_offset < -12 ||
		    p_h264_pps->second_chroma_qp_index_offset > 12)
			वापस -EINVAL;
		अवरोध;

	हाल V4L2_CTRL_TYPE_H264_SCALING_MATRIX:
		अवरोध;

	हाल V4L2_CTRL_TYPE_H264_PRED_WEIGHTS:
		p_h264_pred_weights = p;

		अगर (p_h264_pred_weights->luma_log2_weight_denom > 7)
			वापस -EINVAL;
		अगर (p_h264_pred_weights->chroma_log2_weight_denom > 7)
			वापस -EINVAL;
		अवरोध;

	हाल V4L2_CTRL_TYPE_H264_SLICE_PARAMS:
		p_h264_slice_params = p;

		अगर (p_h264_slice_params->slice_type != V4L2_H264_SLICE_TYPE_B)
			p_h264_slice_params->flags &=
				~V4L2_H264_SLICE_FLAG_सूचीECT_SPATIAL_MV_PRED;

		अगर (p_h264_slice_params->colour_plane_id > 2)
			वापस -EINVAL;
		अगर (p_h264_slice_params->cabac_init_idc > 2)
			वापस -EINVAL;
		अगर (p_h264_slice_params->disable_deblocking_filter_idc > 2)
			वापस -EINVAL;
		अगर (p_h264_slice_params->slice_alpha_c0_offset_भाग2 < -6 ||
		    p_h264_slice_params->slice_alpha_c0_offset_भाग2 > 6)
			वापस -EINVAL;
		अगर (p_h264_slice_params->slice_beta_offset_भाग2 < -6 ||
		    p_h264_slice_params->slice_beta_offset_भाग2 > 6)
			वापस -EINVAL;

		अगर (p_h264_slice_params->slice_type == V4L2_H264_SLICE_TYPE_I ||
		    p_h264_slice_params->slice_type == V4L2_H264_SLICE_TYPE_SI)
			p_h264_slice_params->num_ref_idx_l0_active_minus1 = 0;
		अगर (p_h264_slice_params->slice_type != V4L2_H264_SLICE_TYPE_B)
			p_h264_slice_params->num_ref_idx_l1_active_minus1 = 0;

		अगर (p_h264_slice_params->num_ref_idx_l0_active_minus1 >
		    (V4L2_H264_REF_LIST_LEN - 1))
			वापस -EINVAL;
		अगर (p_h264_slice_params->num_ref_idx_l1_active_minus1 >
		    (V4L2_H264_REF_LIST_LEN - 1))
			वापस -EINVAL;
		zero_reserved(*p_h264_slice_params);
		अवरोध;

	हाल V4L2_CTRL_TYPE_H264_DECODE_PARAMS:
		p_h264_dec_params = p;

		अगर (p_h264_dec_params->nal_ref_idc > 3)
			वापस -EINVAL;
		क्रम (i = 0; i < V4L2_H264_NUM_DPB_ENTRIES; i++) अणु
			काष्ठा v4l2_h264_dpb_entry *dpb_entry =
				&p_h264_dec_params->dpb[i];

			zero_reserved(*dpb_entry);
		पूर्ण
		zero_reserved(*p_h264_dec_params);
		अवरोध;

	हाल V4L2_CTRL_TYPE_VP8_FRAME:
		p_vp8_frame = p;

		चयन (p_vp8_frame->num_dct_parts) अणु
		हाल 1:
		हाल 2:
		हाल 4:
		हाल 8:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		zero_padding(p_vp8_frame->segment);
		zero_padding(p_vp8_frame->lf);
		zero_padding(p_vp8_frame->quant);
		zero_padding(p_vp8_frame->entropy);
		zero_padding(p_vp8_frame->coder_state);
		अवरोध;

	हाल V4L2_CTRL_TYPE_HEVC_SPS:
		p_hevc_sps = p;

		अगर (!(p_hevc_sps->flags & V4L2_HEVC_SPS_FLAG_PCM_ENABLED)) अणु
			p_hevc_sps->pcm_sample_bit_depth_luma_minus1 = 0;
			p_hevc_sps->pcm_sample_bit_depth_chroma_minus1 = 0;
			p_hevc_sps->log2_min_pcm_luma_coding_block_size_minus3 = 0;
			p_hevc_sps->log2_dअगरf_max_min_pcm_luma_coding_block_size = 0;
		पूर्ण

		अगर (!(p_hevc_sps->flags &
		      V4L2_HEVC_SPS_FLAG_LONG_TERM_REF_PICS_PRESENT))
			p_hevc_sps->num_दीर्घ_term_ref_pics_sps = 0;
		अवरोध;

	हाल V4L2_CTRL_TYPE_HEVC_PPS:
		p_hevc_pps = p;

		अगर (!(p_hevc_pps->flags &
		      V4L2_HEVC_PPS_FLAG_CU_QP_DELTA_ENABLED))
			p_hevc_pps->dअगरf_cu_qp_delta_depth = 0;

		अगर (!(p_hevc_pps->flags & V4L2_HEVC_PPS_FLAG_TILES_ENABLED)) अणु
			p_hevc_pps->num_tile_columns_minus1 = 0;
			p_hevc_pps->num_tile_rows_minus1 = 0;
			स_रखो(&p_hevc_pps->column_width_minus1, 0,
			       माप(p_hevc_pps->column_width_minus1));
			स_रखो(&p_hevc_pps->row_height_minus1, 0,
			       माप(p_hevc_pps->row_height_minus1));

			p_hevc_pps->flags &=
				~V4L2_HEVC_PPS_FLAG_LOOP_FILTER_ACROSS_TILES_ENABLED;
		पूर्ण

		अगर (p_hevc_pps->flags &
		    V4L2_HEVC_PPS_FLAG_PPS_DISABLE_DEBLOCKING_FILTER) अणु
			p_hevc_pps->pps_beta_offset_भाग2 = 0;
			p_hevc_pps->pps_tc_offset_भाग2 = 0;
		पूर्ण

		zero_padding(*p_hevc_pps);
		अवरोध;

	हाल V4L2_CTRL_TYPE_HEVC_SLICE_PARAMS:
		p_hevc_slice_params = p;

		अगर (p_hevc_slice_params->num_active_dpb_entries >
		    V4L2_HEVC_DPB_ENTRIES_NUM_MAX)
			वापस -EINVAL;

		zero_padding(p_hevc_slice_params->pred_weight_table);

		क्रम (i = 0; i < p_hevc_slice_params->num_active_dpb_entries;
		     i++) अणु
			काष्ठा v4l2_hevc_dpb_entry *dpb_entry =
				&p_hevc_slice_params->dpb[i];

			zero_padding(*dpb_entry);
		पूर्ण

		zero_padding(*p_hevc_slice_params);
		अवरोध;

	हाल V4L2_CTRL_TYPE_HDR10_CLL_INFO:
		अवरोध;

	हाल V4L2_CTRL_TYPE_HDR10_MASTERING_DISPLAY:
		p_hdr10_mastering = p;

		क्रम (i = 0; i < 3; ++i) अणु
			अगर (p_hdr10_mastering->display_primaries_x[i] <
				V4L2_HDR10_MASTERING_PRIMARIES_X_LOW ||
			    p_hdr10_mastering->display_primaries_x[i] >
				V4L2_HDR10_MASTERING_PRIMARIES_X_HIGH ||
			    p_hdr10_mastering->display_primaries_y[i] <
				V4L2_HDR10_MASTERING_PRIMARIES_Y_LOW ||
			    p_hdr10_mastering->display_primaries_y[i] >
				V4L2_HDR10_MASTERING_PRIMARIES_Y_HIGH)
				वापस -EINVAL;
		पूर्ण

		अगर (p_hdr10_mastering->white_poपूर्णांक_x <
			V4L2_HDR10_MASTERING_WHITE_POINT_X_LOW ||
		    p_hdr10_mastering->white_poपूर्णांक_x >
			V4L2_HDR10_MASTERING_WHITE_POINT_X_HIGH ||
		    p_hdr10_mastering->white_poपूर्णांक_y <
			V4L2_HDR10_MASTERING_WHITE_POINT_Y_LOW ||
		    p_hdr10_mastering->white_poपूर्णांक_y >
			V4L2_HDR10_MASTERING_WHITE_POINT_Y_HIGH)
			वापस -EINVAL;

		अगर (p_hdr10_mastering->max_display_mastering_luminance <
			V4L2_HDR10_MASTERING_MAX_LUMA_LOW ||
		    p_hdr10_mastering->max_display_mastering_luminance >
			V4L2_HDR10_MASTERING_MAX_LUMA_HIGH ||
		    p_hdr10_mastering->min_display_mastering_luminance <
			V4L2_HDR10_MASTERING_MIN_LUMA_LOW ||
		    p_hdr10_mastering->min_display_mastering_luminance >
			V4L2_HDR10_MASTERING_MIN_LUMA_HIGH)
			वापस -EINVAL;

		/* The following restriction comes from ITU-T Rec. H.265 spec */
		अगर (p_hdr10_mastering->max_display_mastering_luminance ==
			V4L2_HDR10_MASTERING_MAX_LUMA_LOW &&
		    p_hdr10_mastering->min_display_mastering_luminance ==
			V4L2_HDR10_MASTERING_MIN_LUMA_HIGH)
			वापस -EINVAL;

		अवरोध;

	हाल V4L2_CTRL_TYPE_AREA:
		area = p;
		अगर (!area->width || !area->height)
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक std_validate(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
			जोड़ v4l2_ctrl_ptr ptr)
अणु
	माप_प्रकार len;
	u64 offset;
	s64 val;

	चयन ((u32)ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER:
		वापस ROUND_TO_RANGE(ptr.p_s32[idx], u32, ctrl);
	हाल V4L2_CTRL_TYPE_INTEGER64:
		/*
		 * We can't use the ROUND_TO_RANGE define here due to
		 * the u64 भागide that needs special care.
		 */
		val = ptr.p_s64[idx];
		अगर (ctrl->maximum >= 0 && val >= ctrl->maximum - (s64)(ctrl->step / 2))
			val = ctrl->maximum;
		अन्यथा
			val += (s64)(ctrl->step / 2);
		val = clamp_t(s64, val, ctrl->minimum, ctrl->maximum);
		offset = val - ctrl->minimum;
		करो_भाग(offset, ctrl->step);
		ptr.p_s64[idx] = ctrl->minimum + offset * ctrl->step;
		वापस 0;
	हाल V4L2_CTRL_TYPE_U8:
		वापस ROUND_TO_RANGE(ptr.p_u8[idx], u8, ctrl);
	हाल V4L2_CTRL_TYPE_U16:
		वापस ROUND_TO_RANGE(ptr.p_u16[idx], u16, ctrl);
	हाल V4L2_CTRL_TYPE_U32:
		वापस ROUND_TO_RANGE(ptr.p_u32[idx], u32, ctrl);

	हाल V4L2_CTRL_TYPE_BOOLEAN:
		ptr.p_s32[idx] = !!ptr.p_s32[idx];
		वापस 0;

	हाल V4L2_CTRL_TYPE_MENU:
	हाल V4L2_CTRL_TYPE_INTEGER_MENU:
		अगर (ptr.p_s32[idx] < ctrl->minimum || ptr.p_s32[idx] > ctrl->maximum)
			वापस -दुस्फल;
		अगर (ptr.p_s32[idx] < BITS_PER_LONG_LONG &&
		    (ctrl->menu_skip_mask & BIT_ULL(ptr.p_s32[idx])))
			वापस -EINVAL;
		अगर (ctrl->type == V4L2_CTRL_TYPE_MENU &&
		    ctrl->qmenu[ptr.p_s32[idx]][0] == '\0')
			वापस -EINVAL;
		वापस 0;

	हाल V4L2_CTRL_TYPE_BITMASK:
		ptr.p_s32[idx] &= ctrl->maximum;
		वापस 0;

	हाल V4L2_CTRL_TYPE_BUTTON:
	हाल V4L2_CTRL_TYPE_CTRL_CLASS:
		ptr.p_s32[idx] = 0;
		वापस 0;

	हाल V4L2_CTRL_TYPE_STRING:
		idx *= ctrl->elem_size;
		len = म_माप(ptr.p_अक्षर + idx);
		अगर (len < ctrl->minimum)
			वापस -दुस्फल;
		अगर ((len - (u32)ctrl->minimum) % (u32)ctrl->step)
			वापस -दुस्फल;
		वापस 0;

	शेष:
		वापस std_validate_compound(ctrl, idx, ptr);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_type_ops std_type_ops = अणु
	.equal = std_equal,
	.init = std_init,
	.log = std_log,
	.validate = std_validate,
पूर्ण;

/* Helper function: copy the given control value back to the caller */
अटल पूर्णांक ptr_to_user(काष्ठा v4l2_ext_control *c,
		       काष्ठा v4l2_ctrl *ctrl,
		       जोड़ v4l2_ctrl_ptr ptr)
अणु
	u32 len;

	अगर (ctrl->is_ptr && !ctrl->is_string)
		वापस copy_to_user(c->ptr, ptr.p_स्थिर, c->size) ?
		       -EFAULT : 0;

	चयन (ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_STRING:
		len = म_माप(ptr.p_अक्षर);
		अगर (c->size < len + 1) अणु
			c->size = ctrl->elem_size;
			वापस -ENOSPC;
		पूर्ण
		वापस copy_to_user(c->string, ptr.p_अक्षर, len + 1) ?
		       -EFAULT : 0;
	हाल V4L2_CTRL_TYPE_INTEGER64:
		c->value64 = *ptr.p_s64;
		अवरोध;
	शेष:
		c->value = *ptr.p_s32;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Helper function: copy the current control value back to the caller */
अटल पूर्णांक cur_to_user(काष्ठा v4l2_ext_control *c,
		       काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस ptr_to_user(c, ctrl, ctrl->p_cur);
पूर्ण

/* Helper function: copy the new control value back to the caller */
अटल पूर्णांक new_to_user(काष्ठा v4l2_ext_control *c,
		       काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस ptr_to_user(c, ctrl, ctrl->p_new);
पूर्ण

/* Helper function: copy the request value back to the caller */
अटल पूर्णांक req_to_user(काष्ठा v4l2_ext_control *c,
		       काष्ठा v4l2_ctrl_ref *ref)
अणु
	वापस ptr_to_user(c, ref->ctrl, ref->p_req);
पूर्ण

/* Helper function: copy the initial control value back to the caller */
अटल पूर्णांक def_to_user(काष्ठा v4l2_ext_control *c, काष्ठा v4l2_ctrl *ctrl)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < ctrl->elems; idx++)
		ctrl->type_ops->init(ctrl, idx, ctrl->p_new);

	वापस ptr_to_user(c, ctrl, ctrl->p_new);
पूर्ण

/* Helper function: copy the caller-provider value to the given control value */
अटल पूर्णांक user_to_ptr(काष्ठा v4l2_ext_control *c,
		       काष्ठा v4l2_ctrl *ctrl,
		       जोड़ v4l2_ctrl_ptr ptr)
अणु
	पूर्णांक ret;
	u32 size;

	ctrl->is_new = 1;
	अगर (ctrl->is_ptr && !ctrl->is_string) अणु
		अचिन्हित idx;

		ret = copy_from_user(ptr.p, c->ptr, c->size) ? -EFAULT : 0;
		अगर (ret || !ctrl->is_array)
			वापस ret;
		क्रम (idx = c->size / ctrl->elem_size; idx < ctrl->elems; idx++)
			ctrl->type_ops->init(ctrl, idx, ptr);
		वापस 0;
	पूर्ण

	चयन (ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER64:
		*ptr.p_s64 = c->value64;
		अवरोध;
	हाल V4L2_CTRL_TYPE_STRING:
		size = c->size;
		अगर (size == 0)
			वापस -दुस्फल;
		अगर (size > ctrl->maximum + 1)
			size = ctrl->maximum + 1;
		ret = copy_from_user(ptr.p_अक्षर, c->string, size) ? -EFAULT : 0;
		अगर (!ret) अणु
			अक्षर last = ptr.p_अक्षर[size - 1];

			ptr.p_अक्षर[size - 1] = 0;
			/* If the string was दीर्घer than ctrl->maximum,
			   then वापस an error. */
			अगर (म_माप(ptr.p_अक्षर) == ctrl->maximum && last)
				वापस -दुस्फल;
		पूर्ण
		वापस ret;
	शेष:
		*ptr.p_s32 = c->value;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Helper function: copy the caller-provider value as the new control value */
अटल पूर्णांक user_to_new(काष्ठा v4l2_ext_control *c,
		       काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस user_to_ptr(c, ctrl, ctrl->p_new);
पूर्ण

/* Copy the one value to another. */
अटल व्योम ptr_to_ptr(काष्ठा v4l2_ctrl *ctrl,
		       जोड़ v4l2_ctrl_ptr from, जोड़ v4l2_ctrl_ptr to)
अणु
	अगर (ctrl == शून्य)
		वापस;
	स_नकल(to.p, from.p_स्थिर, ctrl->elems * ctrl->elem_size);
पूर्ण

/* Copy the new value to the current value. */
अटल व्योम new_to_cur(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl *ctrl, u32 ch_flags)
अणु
	bool changed;

	अगर (ctrl == शून्य)
		वापस;

	/* has_changed is set by cluster_changed */
	changed = ctrl->has_changed;
	अगर (changed)
		ptr_to_ptr(ctrl, ctrl->p_new, ctrl->p_cur);

	अगर (ch_flags & V4L2_EVENT_CTRL_CH_FLAGS) अणु
		/* Note: CH_FLAGS is only set क्रम स्वतः clusters. */
		ctrl->flags &=
			~(V4L2_CTRL_FLAG_INACTIVE | V4L2_CTRL_FLAG_VOLATILE);
		अगर (!is_cur_manual(ctrl->cluster[0])) अणु
			ctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
			अगर (ctrl->cluster[0]->has_अस्थिरs)
				ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
		पूर्ण
		fh = शून्य;
	पूर्ण
	अगर (changed || ch_flags) अणु
		/* If a control was changed that was not one of the controls
		   modअगरied by the application, then send the event to all. */
		अगर (!ctrl->is_new)
			fh = शून्य;
		send_event(fh, ctrl,
			(changed ? V4L2_EVENT_CTRL_CH_VALUE : 0) | ch_flags);
		अगर (ctrl->call_notअगरy && changed && ctrl->handler->notअगरy)
			ctrl->handler->notअगरy(ctrl, ctrl->handler->notअगरy_priv);
	पूर्ण
पूर्ण

/* Copy the current value to the new value */
अटल व्योम cur_to_new(काष्ठा v4l2_ctrl *ctrl)
अणु
	अगर (ctrl == शून्य)
		वापस;
	ptr_to_ptr(ctrl, ctrl->p_cur, ctrl->p_new);
पूर्ण

/* Copy the new value to the request value */
अटल व्योम new_to_req(काष्ठा v4l2_ctrl_ref *ref)
अणु
	अगर (!ref)
		वापस;
	ptr_to_ptr(ref->ctrl, ref->ctrl->p_new, ref->p_req);
	ref->valid_p_req = true;
पूर्ण

/* Copy the current value to the request value */
अटल व्योम cur_to_req(काष्ठा v4l2_ctrl_ref *ref)
अणु
	अगर (!ref)
		वापस;
	ptr_to_ptr(ref->ctrl, ref->ctrl->p_cur, ref->p_req);
	ref->valid_p_req = true;
पूर्ण

/* Copy the request value to the new value */
अटल व्योम req_to_new(काष्ठा v4l2_ctrl_ref *ref)
अणु
	अगर (!ref)
		वापस;
	अगर (ref->valid_p_req)
		ptr_to_ptr(ref->ctrl, ref->p_req, ref->ctrl->p_new);
	अन्यथा
		ptr_to_ptr(ref->ctrl, ref->ctrl->p_cur, ref->ctrl->p_new);
पूर्ण

/* Return non-zero अगर one or more of the controls in the cluster has a new
   value that dअगरfers from the current value. */
अटल पूर्णांक cluster_changed(काष्ठा v4l2_ctrl *master)
अणु
	bool changed = false;
	अचिन्हित idx;
	पूर्णांक i;

	क्रम (i = 0; i < master->ncontrols; i++) अणु
		काष्ठा v4l2_ctrl *ctrl = master->cluster[i];
		bool ctrl_changed = false;

		अगर (ctrl == शून्य)
			जारी;

		अगर (ctrl->flags & V4L2_CTRL_FLAG_EXECUTE_ON_WRITE)
			changed = ctrl_changed = true;

		/*
		 * Set has_changed to false to aव्योम generating
		 * the event V4L2_EVENT_CTRL_CH_VALUE
		 */
		अगर (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE) अणु
			ctrl->has_changed = false;
			जारी;
		पूर्ण

		क्रम (idx = 0; !ctrl_changed && idx < ctrl->elems; idx++)
			ctrl_changed = !ctrl->type_ops->equal(ctrl, idx,
				ctrl->p_cur, ctrl->p_new);
		ctrl->has_changed = ctrl_changed;
		changed |= ctrl->has_changed;
	पूर्ण
	वापस changed;
पूर्ण

/* Control range checking */
अटल पूर्णांक check_range(क्रमागत v4l2_ctrl_type type,
		s64 min, s64 max, u64 step, s64 def)
अणु
	चयन (type) अणु
	हाल V4L2_CTRL_TYPE_BOOLEAN:
		अगर (step != 1 || max > 1 || min < 0)
			वापस -दुस्फल;
		fallthrough;
	हाल V4L2_CTRL_TYPE_U8:
	हाल V4L2_CTRL_TYPE_U16:
	हाल V4L2_CTRL_TYPE_U32:
	हाल V4L2_CTRL_TYPE_INTEGER:
	हाल V4L2_CTRL_TYPE_INTEGER64:
		अगर (step == 0 || min > max || def < min || def > max)
			वापस -दुस्फल;
		वापस 0;
	हाल V4L2_CTRL_TYPE_BITMASK:
		अगर (step || min || !max || (def & ~max))
			वापस -दुस्फल;
		वापस 0;
	हाल V4L2_CTRL_TYPE_MENU:
	हाल V4L2_CTRL_TYPE_INTEGER_MENU:
		अगर (min > max || def < min || def > max)
			वापस -दुस्फल;
		/* Note: step == menu_skip_mask क्रम menu controls.
		   So here we check अगर the शेष value is masked out. */
		अगर (step && ((1 << def) & step))
			वापस -EINVAL;
		वापस 0;
	हाल V4L2_CTRL_TYPE_STRING:
		अगर (min > max || min < 0 || step < 1 || def)
			वापस -दुस्फल;
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Validate a new control */
अटल पूर्णांक validate_new(स्थिर काष्ठा v4l2_ctrl *ctrl, जोड़ v4l2_ctrl_ptr p_new)
अणु
	अचिन्हित idx;
	पूर्णांक err = 0;

	क्रम (idx = 0; !err && idx < ctrl->elems; idx++)
		err = ctrl->type_ops->validate(ctrl, idx, p_new);
	वापस err;
पूर्ण

अटल अंतरभूत u32 node2id(काष्ठा list_head *node)
अणु
	वापस list_entry(node, काष्ठा v4l2_ctrl_ref, node)->ctrl->id;
पूर्ण

/* Set the handler's error code if it wasn't set earlier alपढ़ोy */
अटल अंतरभूत पूर्णांक handler_set_err(काष्ठा v4l2_ctrl_handler *hdl, पूर्णांक err)
अणु
	अगर (hdl->error == 0)
		hdl->error = err;
	वापस err;
पूर्ण

/* Initialize the handler */
पूर्णांक v4l2_ctrl_handler_init_class(काष्ठा v4l2_ctrl_handler *hdl,
				 अचिन्हित nr_of_controls_hपूर्णांक,
				 काष्ठा lock_class_key *key, स्थिर अक्षर *name)
अणु
	mutex_init(&hdl->_lock);
	hdl->lock = &hdl->_lock;
	lockdep_set_class_and_name(hdl->lock, key, name);
	INIT_LIST_HEAD(&hdl->ctrls);
	INIT_LIST_HEAD(&hdl->ctrl_refs);
	INIT_LIST_HEAD(&hdl->requests);
	INIT_LIST_HEAD(&hdl->requests_queued);
	hdl->request_is_queued = false;
	hdl->nr_of_buckets = 1 + nr_of_controls_hपूर्णांक / 8;
	hdl->buckets = kvदो_स्मृति_array(hdl->nr_of_buckets,
				      माप(hdl->buckets[0]),
				      GFP_KERNEL | __GFP_ZERO);
	hdl->error = hdl->buckets ? 0 : -ENOMEM;
	media_request_object_init(&hdl->req_obj);
	वापस hdl->error;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_handler_init_class);

/* Free all controls and control refs */
व्योम v4l2_ctrl_handler_मुक्त(काष्ठा v4l2_ctrl_handler *hdl)
अणु
	काष्ठा v4l2_ctrl_ref *ref, *next_ref;
	काष्ठा v4l2_ctrl *ctrl, *next_ctrl;
	काष्ठा v4l2_subscribed_event *sev, *next_sev;

	अगर (hdl == शून्य || hdl->buckets == शून्य)
		वापस;

	/*
	 * If the मुख्य handler is मुक्तd and it is used by handler objects in
	 * outstanding requests, then unbind and put those objects beक्रमe
	 * मुक्तing the मुख्य handler.
	 *
	 * The मुख्य handler can be identअगरied by having a शून्य ops poपूर्णांकer in
	 * the request object.
	 */
	अगर (!hdl->req_obj.ops && !list_empty(&hdl->requests)) अणु
		काष्ठा v4l2_ctrl_handler *req, *next_req;

		list_क्रम_each_entry_safe(req, next_req, &hdl->requests, requests) अणु
			media_request_object_unbind(&req->req_obj);
			media_request_object_put(&req->req_obj);
		पूर्ण
	पूर्ण
	mutex_lock(hdl->lock);
	/* Free all nodes */
	list_क्रम_each_entry_safe(ref, next_ref, &hdl->ctrl_refs, node) अणु
		list_del(&ref->node);
		kमुक्त(ref);
	पूर्ण
	/* Free all controls owned by the handler */
	list_क्रम_each_entry_safe(ctrl, next_ctrl, &hdl->ctrls, node) अणु
		list_del(&ctrl->node);
		list_क्रम_each_entry_safe(sev, next_sev, &ctrl->ev_subs, node)
			list_del(&sev->node);
		kvमुक्त(ctrl);
	पूर्ण
	kvमुक्त(hdl->buckets);
	hdl->buckets = शून्य;
	hdl->cached = शून्य;
	hdl->error = 0;
	mutex_unlock(hdl->lock);
	mutex_destroy(&hdl->_lock);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_handler_मुक्त);

/* For backwards compatibility: V4L2_CID_PRIVATE_BASE should no दीर्घer
   be used except in G_CTRL, S_CTRL, QUERYCTRL and QUERYMENU when dealing
   with applications that करो not use the NEXT_CTRL flag.

   We just find the n-th निजी user control. It's O(N), but that should not
   be an issue in this particular हाल. */
अटल काष्ठा v4l2_ctrl_ref *find_निजी_ref(
		काष्ठा v4l2_ctrl_handler *hdl, u32 id)
अणु
	काष्ठा v4l2_ctrl_ref *ref;

	id -= V4L2_CID_PRIVATE_BASE;
	list_क्रम_each_entry(ref, &hdl->ctrl_refs, node) अणु
		/* Search क्रम निजी user controls that are compatible with
		   VIDIOC_G/S_CTRL. */
		अगर (V4L2_CTRL_ID2WHICH(ref->ctrl->id) == V4L2_CTRL_CLASS_USER &&
		    V4L2_CTRL_DRIVER_PRIV(ref->ctrl->id)) अणु
			अगर (!ref->ctrl->is_पूर्णांक)
				जारी;
			अगर (id == 0)
				वापस ref;
			id--;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* Find a control with the given ID. */
अटल काष्ठा v4l2_ctrl_ref *find_ref(काष्ठा v4l2_ctrl_handler *hdl, u32 id)
अणु
	काष्ठा v4l2_ctrl_ref *ref;
	पूर्णांक bucket;

	id &= V4L2_CTRL_ID_MASK;

	/* Old-style निजी controls need special handling */
	अगर (id >= V4L2_CID_PRIVATE_BASE)
		वापस find_निजी_ref(hdl, id);
	bucket = id % hdl->nr_of_buckets;

	/* Simple optimization: cache the last control found */
	अगर (hdl->cached && hdl->cached->ctrl->id == id)
		वापस hdl->cached;

	/* Not in cache, search the hash */
	ref = hdl->buckets ? hdl->buckets[bucket] : शून्य;
	जबतक (ref && ref->ctrl->id != id)
		ref = ref->next;

	अगर (ref)
		hdl->cached = ref; /* cache it! */
	वापस ref;
पूर्ण

/* Find a control with the given ID. Take the handler's lock first. */
अटल काष्ठा v4l2_ctrl_ref *find_ref_lock(
		काष्ठा v4l2_ctrl_handler *hdl, u32 id)
अणु
	काष्ठा v4l2_ctrl_ref *ref = शून्य;

	अगर (hdl) अणु
		mutex_lock(hdl->lock);
		ref = find_ref(hdl, id);
		mutex_unlock(hdl->lock);
	पूर्ण
	वापस ref;
पूर्ण

/* Find a control with the given ID. */
काष्ठा v4l2_ctrl *v4l2_ctrl_find(काष्ठा v4l2_ctrl_handler *hdl, u32 id)
अणु
	काष्ठा v4l2_ctrl_ref *ref = find_ref_lock(hdl, id);

	वापस ref ? ref->ctrl : शून्य;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_find);

/* Allocate a new v4l2_ctrl_ref and hook it पूर्णांकo the handler. */
अटल पूर्णांक handler_new_ref(काष्ठा v4l2_ctrl_handler *hdl,
			   काष्ठा v4l2_ctrl *ctrl,
			   काष्ठा v4l2_ctrl_ref **ctrl_ref,
			   bool from_other_dev, bool allocate_req)
अणु
	काष्ठा v4l2_ctrl_ref *ref;
	काष्ठा v4l2_ctrl_ref *new_ref;
	u32 id = ctrl->id;
	u32 class_ctrl = V4L2_CTRL_ID2WHICH(id) | 1;
	पूर्णांक bucket = id % hdl->nr_of_buckets;	/* which bucket to use */
	अचिन्हित पूर्णांक size_extra_req = 0;

	अगर (ctrl_ref)
		*ctrl_ref = शून्य;

	/*
	 * Automatically add the control class अगर it is not yet present and
	 * the new control is not a compound control.
	 */
	अगर (ctrl->type < V4L2_CTRL_COMPOUND_TYPES &&
	    id != class_ctrl && find_ref_lock(hdl, class_ctrl) == शून्य)
		अगर (!v4l2_ctrl_new_std(hdl, शून्य, class_ctrl, 0, 0, 0, 0))
			वापस hdl->error;

	अगर (hdl->error)
		वापस hdl->error;

	अगर (allocate_req)
		size_extra_req = ctrl->elems * ctrl->elem_size;
	new_ref = kzalloc(माप(*new_ref) + size_extra_req, GFP_KERNEL);
	अगर (!new_ref)
		वापस handler_set_err(hdl, -ENOMEM);
	new_ref->ctrl = ctrl;
	new_ref->from_other_dev = from_other_dev;
	अगर (size_extra_req)
		new_ref->p_req.p = &new_ref[1];

	INIT_LIST_HEAD(&new_ref->node);

	mutex_lock(hdl->lock);

	/* Add immediately at the end of the list अगर the list is empty, or अगर
	   the last element in the list has a lower ID.
	   This ensures that when elements are added in ascending order the
	   insertion is an O(1) operation. */
	अगर (list_empty(&hdl->ctrl_refs) || id > node2id(hdl->ctrl_refs.prev)) अणु
		list_add_tail(&new_ref->node, &hdl->ctrl_refs);
		जाओ insert_in_hash;
	पूर्ण

	/* Find insert position in sorted list */
	list_क्रम_each_entry(ref, &hdl->ctrl_refs, node) अणु
		अगर (ref->ctrl->id < id)
			जारी;
		/* Don't add duplicates */
		अगर (ref->ctrl->id == id) अणु
			kमुक्त(new_ref);
			जाओ unlock;
		पूर्ण
		list_add(&new_ref->node, ref->node.prev);
		अवरोध;
	पूर्ण

insert_in_hash:
	/* Insert the control node in the hash */
	new_ref->next = hdl->buckets[bucket];
	hdl->buckets[bucket] = new_ref;
	अगर (ctrl_ref)
		*ctrl_ref = new_ref;
	अगर (ctrl->handler == hdl) अणु
		/* By शेष each control starts in a cluster of its own.
		 * new_ref->ctrl is basically a cluster array with one
		 * element, so that's perfect to use as the cluster poपूर्णांकer.
		 * But only करो this क्रम the handler that owns the control.
		 */
		ctrl->cluster = &new_ref->ctrl;
		ctrl->ncontrols = 1;
	पूर्ण

unlock:
	mutex_unlock(hdl->lock);
	वापस 0;
पूर्ण

/* Add a new control */
अटल काष्ठा v4l2_ctrl *v4l2_ctrl_new(काष्ठा v4l2_ctrl_handler *hdl,
			स्थिर काष्ठा v4l2_ctrl_ops *ops,
			स्थिर काष्ठा v4l2_ctrl_type_ops *type_ops,
			u32 id, स्थिर अक्षर *name, क्रमागत v4l2_ctrl_type type,
			s64 min, s64 max, u64 step, s64 def,
			स्थिर u32 dims[V4L2_CTRL_MAX_DIMS], u32 elem_size,
			u32 flags, स्थिर अक्षर * स्थिर *qmenu,
			स्थिर s64 *qmenu_पूर्णांक, स्थिर जोड़ v4l2_ctrl_ptr p_def,
			व्योम *priv)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	अचिन्हित sz_extra;
	अचिन्हित nr_of_dims = 0;
	अचिन्हित elems = 1;
	bool is_array;
	अचिन्हित tot_ctrl_size;
	अचिन्हित idx;
	व्योम *data;
	पूर्णांक err;

	अगर (hdl->error)
		वापस शून्य;

	जबतक (dims && dims[nr_of_dims]) अणु
		elems *= dims[nr_of_dims];
		nr_of_dims++;
		अगर (nr_of_dims == V4L2_CTRL_MAX_DIMS)
			अवरोध;
	पूर्ण
	is_array = nr_of_dims > 0;

	/* Prefill elem_size क्रम all types handled by std_type_ops */
	चयन ((u32)type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER64:
		elem_size = माप(s64);
		अवरोध;
	हाल V4L2_CTRL_TYPE_STRING:
		elem_size = max + 1;
		अवरोध;
	हाल V4L2_CTRL_TYPE_U8:
		elem_size = माप(u8);
		अवरोध;
	हाल V4L2_CTRL_TYPE_U16:
		elem_size = माप(u16);
		अवरोध;
	हाल V4L2_CTRL_TYPE_U32:
		elem_size = माप(u32);
		अवरोध;
	हाल V4L2_CTRL_TYPE_MPEG2_SLICE_PARAMS:
		elem_size = माप(काष्ठा v4l2_ctrl_mpeg2_slice_params);
		अवरोध;
	हाल V4L2_CTRL_TYPE_MPEG2_QUANTIZATION:
		elem_size = माप(काष्ठा v4l2_ctrl_mpeg2_quantization);
		अवरोध;
	हाल V4L2_CTRL_TYPE_FWHT_PARAMS:
		elem_size = माप(काष्ठा v4l2_ctrl_fwht_params);
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_SPS:
		elem_size = माप(काष्ठा v4l2_ctrl_h264_sps);
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_PPS:
		elem_size = माप(काष्ठा v4l2_ctrl_h264_pps);
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_SCALING_MATRIX:
		elem_size = माप(काष्ठा v4l2_ctrl_h264_scaling_matrix);
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_SLICE_PARAMS:
		elem_size = माप(काष्ठा v4l2_ctrl_h264_slice_params);
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_DECODE_PARAMS:
		elem_size = माप(काष्ठा v4l2_ctrl_h264_decode_params);
		अवरोध;
	हाल V4L2_CTRL_TYPE_H264_PRED_WEIGHTS:
		elem_size = माप(काष्ठा v4l2_ctrl_h264_pred_weights);
		अवरोध;
	हाल V4L2_CTRL_TYPE_VP8_FRAME:
		elem_size = माप(काष्ठा v4l2_ctrl_vp8_frame);
		अवरोध;
	हाल V4L2_CTRL_TYPE_HEVC_SPS:
		elem_size = माप(काष्ठा v4l2_ctrl_hevc_sps);
		अवरोध;
	हाल V4L2_CTRL_TYPE_HEVC_PPS:
		elem_size = माप(काष्ठा v4l2_ctrl_hevc_pps);
		अवरोध;
	हाल V4L2_CTRL_TYPE_HEVC_SLICE_PARAMS:
		elem_size = माप(काष्ठा v4l2_ctrl_hevc_slice_params);
		अवरोध;
	हाल V4L2_CTRL_TYPE_HDR10_CLL_INFO:
		elem_size = माप(काष्ठा v4l2_ctrl_hdr10_cll_info);
		अवरोध;
	हाल V4L2_CTRL_TYPE_HDR10_MASTERING_DISPLAY:
		elem_size = माप(काष्ठा v4l2_ctrl_hdr10_mastering_display);
		अवरोध;
	हाल V4L2_CTRL_TYPE_AREA:
		elem_size = माप(काष्ठा v4l2_area);
		अवरोध;
	शेष:
		अगर (type < V4L2_CTRL_COMPOUND_TYPES)
			elem_size = माप(s32);
		अवरोध;
	पूर्ण
	tot_ctrl_size = elem_size * elems;

	/* Sanity checks */
	अगर (id == 0 || name == शून्य || !elem_size ||
	    id >= V4L2_CID_PRIVATE_BASE ||
	    (type == V4L2_CTRL_TYPE_MENU && qmenu == शून्य) ||
	    (type == V4L2_CTRL_TYPE_INTEGER_MENU && qmenu_पूर्णांक == शून्य)) अणु
		handler_set_err(hdl, -दुस्फल);
		वापस शून्य;
	पूर्ण
	err = check_range(type, min, max, step, def);
	अगर (err) अणु
		handler_set_err(hdl, err);
		वापस शून्य;
	पूर्ण
	अगर (is_array &&
	    (type == V4L2_CTRL_TYPE_BUTTON ||
	     type == V4L2_CTRL_TYPE_CTRL_CLASS)) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण

	sz_extra = 0;
	अगर (type == V4L2_CTRL_TYPE_BUTTON)
		flags |= V4L2_CTRL_FLAG_WRITE_ONLY |
			V4L2_CTRL_FLAG_EXECUTE_ON_WRITE;
	अन्यथा अगर (type == V4L2_CTRL_TYPE_CTRL_CLASS)
		flags |= V4L2_CTRL_FLAG_READ_ONLY;
	अन्यथा अगर (type == V4L2_CTRL_TYPE_INTEGER64 ||
		 type == V4L2_CTRL_TYPE_STRING ||
		 type >= V4L2_CTRL_COMPOUND_TYPES ||
		 is_array)
		sz_extra += 2 * tot_ctrl_size;

	अगर (type >= V4L2_CTRL_COMPOUND_TYPES && p_def.p_स्थिर)
		sz_extra += elem_size;

	ctrl = kvzalloc(माप(*ctrl) + sz_extra, GFP_KERNEL);
	अगर (ctrl == शून्य) अणु
		handler_set_err(hdl, -ENOMEM);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&ctrl->node);
	INIT_LIST_HEAD(&ctrl->ev_subs);
	ctrl->handler = hdl;
	ctrl->ops = ops;
	ctrl->type_ops = type_ops ? type_ops : &std_type_ops;
	ctrl->id = id;
	ctrl->name = name;
	ctrl->type = type;
	ctrl->flags = flags;
	ctrl->minimum = min;
	ctrl->maximum = max;
	ctrl->step = step;
	ctrl->शेष_value = def;
	ctrl->is_string = !is_array && type == V4L2_CTRL_TYPE_STRING;
	ctrl->is_ptr = is_array || type >= V4L2_CTRL_COMPOUND_TYPES || ctrl->is_string;
	ctrl->is_पूर्णांक = !ctrl->is_ptr && type != V4L2_CTRL_TYPE_INTEGER64;
	ctrl->is_array = is_array;
	ctrl->elems = elems;
	ctrl->nr_of_dims = nr_of_dims;
	अगर (nr_of_dims)
		स_नकल(ctrl->dims, dims, nr_of_dims * माप(dims[0]));
	ctrl->elem_size = elem_size;
	अगर (type == V4L2_CTRL_TYPE_MENU)
		ctrl->qmenu = qmenu;
	अन्यथा अगर (type == V4L2_CTRL_TYPE_INTEGER_MENU)
		ctrl->qmenu_पूर्णांक = qmenu_पूर्णांक;
	ctrl->priv = priv;
	ctrl->cur.val = ctrl->val = def;
	data = &ctrl[1];

	अगर (!ctrl->is_पूर्णांक) अणु
		ctrl->p_new.p = data;
		ctrl->p_cur.p = data + tot_ctrl_size;
	पूर्ण अन्यथा अणु
		ctrl->p_new.p = &ctrl->val;
		ctrl->p_cur.p = &ctrl->cur.val;
	पूर्ण

	अगर (type >= V4L2_CTRL_COMPOUND_TYPES && p_def.p_स्थिर) अणु
		ctrl->p_def.p = ctrl->p_cur.p + tot_ctrl_size;
		स_नकल(ctrl->p_def.p, p_def.p_स्थिर, elem_size);
	पूर्ण

	क्रम (idx = 0; idx < elems; idx++) अणु
		ctrl->type_ops->init(ctrl, idx, ctrl->p_cur);
		ctrl->type_ops->init(ctrl, idx, ctrl->p_new);
	पूर्ण

	अगर (handler_new_ref(hdl, ctrl, शून्य, false, false)) अणु
		kvमुक्त(ctrl);
		वापस शून्य;
	पूर्ण
	mutex_lock(hdl->lock);
	list_add_tail(&ctrl->node, &hdl->ctrls);
	mutex_unlock(hdl->lock);
	वापस ctrl;
पूर्ण

काष्ठा v4l2_ctrl *v4l2_ctrl_new_custom(काष्ठा v4l2_ctrl_handler *hdl,
			स्थिर काष्ठा v4l2_ctrl_config *cfg, व्योम *priv)
अणु
	bool is_menu;
	काष्ठा v4l2_ctrl *ctrl;
	स्थिर अक्षर *name = cfg->name;
	स्थिर अक्षर * स्थिर *qmenu = cfg->qmenu;
	स्थिर s64 *qmenu_पूर्णांक = cfg->qmenu_पूर्णांक;
	क्रमागत v4l2_ctrl_type type = cfg->type;
	u32 flags = cfg->flags;
	s64 min = cfg->min;
	s64 max = cfg->max;
	u64 step = cfg->step;
	s64 def = cfg->def;

	अगर (name == शून्य)
		v4l2_ctrl_fill(cfg->id, &name, &type, &min, &max, &step,
								&def, &flags);

	is_menu = (type == V4L2_CTRL_TYPE_MENU ||
		   type == V4L2_CTRL_TYPE_INTEGER_MENU);
	अगर (is_menu)
		WARN_ON(step);
	अन्यथा
		WARN_ON(cfg->menu_skip_mask);
	अगर (type == V4L2_CTRL_TYPE_MENU && !qmenu) अणु
		qmenu = v4l2_ctrl_get_menu(cfg->id);
	पूर्ण अन्यथा अगर (type == V4L2_CTRL_TYPE_INTEGER_MENU && !qmenu_पूर्णांक) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण

	ctrl = v4l2_ctrl_new(hdl, cfg->ops, cfg->type_ops, cfg->id, name,
			type, min, max,
			is_menu ? cfg->menu_skip_mask : step, def,
			cfg->dims, cfg->elem_size,
			flags, qmenu, qmenu_पूर्णांक, cfg->p_def, priv);
	अगर (ctrl)
		ctrl->is_निजी = cfg->is_निजी;
	वापस ctrl;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_new_custom);

/* Helper function क्रम standard non-menu controls */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std(काष्ठा v4l2_ctrl_handler *hdl,
			स्थिर काष्ठा v4l2_ctrl_ops *ops,
			u32 id, s64 min, s64 max, u64 step, s64 def)
अणु
	स्थिर अक्षर *name;
	क्रमागत v4l2_ctrl_type type;
	u32 flags;

	v4l2_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);
	अगर (type == V4L2_CTRL_TYPE_MENU ||
	    type == V4L2_CTRL_TYPE_INTEGER_MENU ||
	    type >= V4L2_CTRL_COMPOUND_TYPES) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण
	वापस v4l2_ctrl_new(hdl, ops, शून्य, id, name, type,
			     min, max, step, def, शून्य, 0,
			     flags, शून्य, शून्य, ptr_null, शून्य);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_new_std);

/* Helper function क्रम standard menu controls */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std_menu(काष्ठा v4l2_ctrl_handler *hdl,
			स्थिर काष्ठा v4l2_ctrl_ops *ops,
			u32 id, u8 _max, u64 mask, u8 _def)
अणु
	स्थिर अक्षर * स्थिर *qmenu = शून्य;
	स्थिर s64 *qmenu_पूर्णांक = शून्य;
	अचिन्हित पूर्णांक qmenu_पूर्णांक_len = 0;
	स्थिर अक्षर *name;
	क्रमागत v4l2_ctrl_type type;
	s64 min;
	s64 max = _max;
	s64 def = _def;
	u64 step;
	u32 flags;

	v4l2_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);

	अगर (type == V4L2_CTRL_TYPE_MENU)
		qmenu = v4l2_ctrl_get_menu(id);
	अन्यथा अगर (type == V4L2_CTRL_TYPE_INTEGER_MENU)
		qmenu_पूर्णांक = v4l2_ctrl_get_पूर्णांक_menu(id, &qmenu_पूर्णांक_len);

	अगर ((!qmenu && !qmenu_पूर्णांक) || (qmenu_पूर्णांक && max > qmenu_पूर्णांक_len)) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण
	वापस v4l2_ctrl_new(hdl, ops, शून्य, id, name, type,
			     0, max, mask, def, शून्य, 0,
			     flags, qmenu, qmenu_पूर्णांक, ptr_null, शून्य);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_new_std_menu);

/* Helper function क्रम standard menu controls with driver defined menu */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std_menu_items(काष्ठा v4l2_ctrl_handler *hdl,
			स्थिर काष्ठा v4l2_ctrl_ops *ops, u32 id, u8 _max,
			u64 mask, u8 _def, स्थिर अक्षर * स्थिर *qmenu)
अणु
	क्रमागत v4l2_ctrl_type type;
	स्थिर अक्षर *name;
	u32 flags;
	u64 step;
	s64 min;
	s64 max = _max;
	s64 def = _def;

	/* v4l2_ctrl_new_std_menu_items() should only be called क्रम
	 * standard controls without a standard menu.
	 */
	अगर (v4l2_ctrl_get_menu(id)) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण

	v4l2_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);
	अगर (type != V4L2_CTRL_TYPE_MENU || qmenu == शून्य) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण
	वापस v4l2_ctrl_new(hdl, ops, शून्य, id, name, type,
			     0, max, mask, def, शून्य, 0,
			     flags, qmenu, शून्य, ptr_null, शून्य);

पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_new_std_menu_items);

/* Helper function क्रम standard compound controls */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std_compound(काष्ठा v4l2_ctrl_handler *hdl,
				स्थिर काष्ठा v4l2_ctrl_ops *ops, u32 id,
				स्थिर जोड़ v4l2_ctrl_ptr p_def)
अणु
	स्थिर अक्षर *name;
	क्रमागत v4l2_ctrl_type type;
	u32 flags;
	s64 min, max, step, def;

	v4l2_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);
	अगर (type < V4L2_CTRL_COMPOUND_TYPES) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण
	वापस v4l2_ctrl_new(hdl, ops, शून्य, id, name, type,
			     min, max, step, def, शून्य, 0,
			     flags, शून्य, शून्य, p_def, शून्य);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_new_std_compound);

/* Helper function क्रम standard पूर्णांकeger menu controls */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_पूर्णांक_menu(काष्ठा v4l2_ctrl_handler *hdl,
			स्थिर काष्ठा v4l2_ctrl_ops *ops,
			u32 id, u8 _max, u8 _def, स्थिर s64 *qmenu_पूर्णांक)
अणु
	स्थिर अक्षर *name;
	क्रमागत v4l2_ctrl_type type;
	s64 min;
	u64 step;
	s64 max = _max;
	s64 def = _def;
	u32 flags;

	v4l2_ctrl_fill(id, &name, &type, &min, &max, &step, &def, &flags);
	अगर (type != V4L2_CTRL_TYPE_INTEGER_MENU) अणु
		handler_set_err(hdl, -EINVAL);
		वापस शून्य;
	पूर्ण
	वापस v4l2_ctrl_new(hdl, ops, शून्य, id, name, type,
			     0, max, 0, def, शून्य, 0,
			     flags, शून्य, qmenu_पूर्णांक, ptr_null, शून्य);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_new_पूर्णांक_menu);

/* Add the controls from another handler to our own. */
पूर्णांक v4l2_ctrl_add_handler(काष्ठा v4l2_ctrl_handler *hdl,
			  काष्ठा v4l2_ctrl_handler *add,
			  bool (*filter)(स्थिर काष्ठा v4l2_ctrl *ctrl),
			  bool from_other_dev)
अणु
	काष्ठा v4l2_ctrl_ref *ref;
	पूर्णांक ret = 0;

	/* Do nothing अगर either handler is शून्य or अगर they are the same */
	अगर (!hdl || !add || hdl == add)
		वापस 0;
	अगर (hdl->error)
		वापस hdl->error;
	mutex_lock(add->lock);
	list_क्रम_each_entry(ref, &add->ctrl_refs, node) अणु
		काष्ठा v4l2_ctrl *ctrl = ref->ctrl;

		/* Skip handler-निजी controls. */
		अगर (ctrl->is_निजी)
			जारी;
		/* And control classes */
		अगर (ctrl->type == V4L2_CTRL_TYPE_CTRL_CLASS)
			जारी;
		/* Filter any unwanted controls */
		अगर (filter && !filter(ctrl))
			जारी;
		ret = handler_new_ref(hdl, ctrl, शून्य, from_other_dev, false);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(add->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_add_handler);

bool v4l2_ctrl_radio_filter(स्थिर काष्ठा v4l2_ctrl *ctrl)
अणु
	अगर (V4L2_CTRL_ID2WHICH(ctrl->id) == V4L2_CTRL_CLASS_FM_TX)
		वापस true;
	अगर (V4L2_CTRL_ID2WHICH(ctrl->id) == V4L2_CTRL_CLASS_FM_RX)
		वापस true;
	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
	हाल V4L2_CID_AUDIO_VOLUME:
	हाल V4L2_CID_AUDIO_BALANCE:
	हाल V4L2_CID_AUDIO_BASS:
	हाल V4L2_CID_AUDIO_TREBLE:
	हाल V4L2_CID_AUDIO_LOUDNESS:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_radio_filter);

/* Cluster controls */
व्योम v4l2_ctrl_cluster(अचिन्हित ncontrols, काष्ठा v4l2_ctrl **controls)
अणु
	bool has_अस्थिरs = false;
	पूर्णांक i;

	/* The first control is the master control and it must not be शून्य */
	अगर (WARN_ON(ncontrols == 0 || controls[0] == शून्य))
		वापस;

	क्रम (i = 0; i < ncontrols; i++) अणु
		अगर (controls[i]) अणु
			controls[i]->cluster = controls;
			controls[i]->ncontrols = ncontrols;
			अगर (controls[i]->flags & V4L2_CTRL_FLAG_VOLATILE)
				has_अस्थिरs = true;
		पूर्ण
	पूर्ण
	controls[0]->has_अस्थिरs = has_अस्थिरs;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_cluster);

व्योम v4l2_ctrl_स्वतः_cluster(अचिन्हित ncontrols, काष्ठा v4l2_ctrl **controls,
			    u8 manual_val, bool set_अस्थिर)
अणु
	काष्ठा v4l2_ctrl *master = controls[0];
	u32 flag = 0;
	पूर्णांक i;

	v4l2_ctrl_cluster(ncontrols, controls);
	WARN_ON(ncontrols <= 1);
	WARN_ON(manual_val < master->minimum || manual_val > master->maximum);
	WARN_ON(set_अस्थिर && !has_op(master, g_अस्थिर_ctrl));
	master->is_स्वतः = true;
	master->has_अस्थिरs = set_अस्थिर;
	master->manual_mode_value = manual_val;
	master->flags |= V4L2_CTRL_FLAG_UPDATE;

	अगर (!is_cur_manual(master))
		flag = V4L2_CTRL_FLAG_INACTIVE |
			(set_अस्थिर ? V4L2_CTRL_FLAG_VOLATILE : 0);

	क्रम (i = 1; i < ncontrols; i++)
		अगर (controls[i])
			controls[i]->flags |= flag;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_स्वतः_cluster);

/* Activate/deactivate a control. */
व्योम v4l2_ctrl_activate(काष्ठा v4l2_ctrl *ctrl, bool active)
अणु
	/* invert since the actual flag is called 'inactive' */
	bool inactive = !active;
	bool old;

	अगर (ctrl == शून्य)
		वापस;

	अगर (inactive)
		/* set V4L2_CTRL_FLAG_INACTIVE */
		old = test_and_set_bit(4, &ctrl->flags);
	अन्यथा
		/* clear V4L2_CTRL_FLAG_INACTIVE */
		old = test_and_clear_bit(4, &ctrl->flags);
	अगर (old != inactive)
		send_event(शून्य, ctrl, V4L2_EVENT_CTRL_CH_FLAGS);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_activate);

व्योम __v4l2_ctrl_grab(काष्ठा v4l2_ctrl *ctrl, bool grabbed)
अणु
	bool old;

	अगर (ctrl == शून्य)
		वापस;

	lockdep_निश्चित_held(ctrl->handler->lock);

	अगर (grabbed)
		/* set V4L2_CTRL_FLAG_GRABBED */
		old = test_and_set_bit(1, &ctrl->flags);
	अन्यथा
		/* clear V4L2_CTRL_FLAG_GRABBED */
		old = test_and_clear_bit(1, &ctrl->flags);
	अगर (old != grabbed)
		send_event(शून्य, ctrl, V4L2_EVENT_CTRL_CH_FLAGS);
पूर्ण
EXPORT_SYMBOL(__v4l2_ctrl_grab);

/* Log the control name and value */
अटल व्योम log_ctrl(स्थिर काष्ठा v4l2_ctrl *ctrl,
		     स्थिर अक्षर *prefix, स्थिर अक्षर *colon)
अणु
	अगर (ctrl->flags & (V4L2_CTRL_FLAG_DISABLED | V4L2_CTRL_FLAG_WRITE_ONLY))
		वापस;
	अगर (ctrl->type == V4L2_CTRL_TYPE_CTRL_CLASS)
		वापस;

	pr_info("%s%s%s: ", prefix, colon, ctrl->name);

	ctrl->type_ops->log(ctrl);

	अगर (ctrl->flags & (V4L2_CTRL_FLAG_INACTIVE |
			   V4L2_CTRL_FLAG_GRABBED |
			   V4L2_CTRL_FLAG_VOLATILE)) अणु
		अगर (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
			pr_cont(" inactive");
		अगर (ctrl->flags & V4L2_CTRL_FLAG_GRABBED)
			pr_cont(" grabbed");
		अगर (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE)
			pr_cont(" volatile");
	पूर्ण
	pr_cont("\n");
पूर्ण

/* Log all controls owned by the handler */
व्योम v4l2_ctrl_handler_log_status(काष्ठा v4l2_ctrl_handler *hdl,
				  स्थिर अक्षर *prefix)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	स्थिर अक्षर *colon = "";
	पूर्णांक len;

	अगर (hdl == शून्य)
		वापस;
	अगर (prefix == शून्य)
		prefix = "";
	len = म_माप(prefix);
	अगर (len && prefix[len - 1] != ' ')
		colon = ": ";
	mutex_lock(hdl->lock);
	list_क्रम_each_entry(ctrl, &hdl->ctrls, node)
		अगर (!(ctrl->flags & V4L2_CTRL_FLAG_DISABLED))
			log_ctrl(ctrl, prefix, colon);
	mutex_unlock(hdl->lock);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_handler_log_status);

पूर्णांक v4l2_ctrl_subdev_log_status(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_ctrl_handler_log_status(sd->ctrl_handler, sd->name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_subdev_log_status);

/* Call s_ctrl क्रम all controls owned by the handler */
पूर्णांक __v4l2_ctrl_handler_setup(काष्ठा v4l2_ctrl_handler *hdl)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret = 0;

	अगर (hdl == शून्य)
		वापस 0;

	lockdep_निश्चित_held(hdl->lock);

	list_क्रम_each_entry(ctrl, &hdl->ctrls, node)
		ctrl->करोne = false;

	list_क्रम_each_entry(ctrl, &hdl->ctrls, node) अणु
		काष्ठा v4l2_ctrl *master = ctrl->cluster[0];
		पूर्णांक i;

		/* Skip अगर this control was alपढ़ोy handled by a cluster. */
		/* Skip button controls and पढ़ो-only controls. */
		अगर (ctrl->करोne || ctrl->type == V4L2_CTRL_TYPE_BUTTON ||
		    (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY))
			जारी;

		क्रम (i = 0; i < master->ncontrols; i++) अणु
			अगर (master->cluster[i]) अणु
				cur_to_new(master->cluster[i]);
				master->cluster[i]->is_new = 1;
				master->cluster[i]->करोne = true;
			पूर्ण
		पूर्ण
		ret = call_op(master, s_ctrl);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__v4l2_ctrl_handler_setup);

पूर्णांक v4l2_ctrl_handler_setup(काष्ठा v4l2_ctrl_handler *hdl)
अणु
	पूर्णांक ret;

	अगर (hdl == शून्य)
		वापस 0;

	mutex_lock(hdl->lock);
	ret = __v4l2_ctrl_handler_setup(hdl);
	mutex_unlock(hdl->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_handler_setup);

/* Implement VIDIOC_QUERY_EXT_CTRL */
पूर्णांक v4l2_query_ext_ctrl(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा v4l2_query_ext_ctrl *qc)
अणु
	स्थिर अचिन्हित next_flags = V4L2_CTRL_FLAG_NEXT_CTRL | V4L2_CTRL_FLAG_NEXT_COMPOUND;
	u32 id = qc->id & V4L2_CTRL_ID_MASK;
	काष्ठा v4l2_ctrl_ref *ref;
	काष्ठा v4l2_ctrl *ctrl;

	अगर (hdl == शून्य)
		वापस -EINVAL;

	mutex_lock(hdl->lock);

	/* Try to find it */
	ref = find_ref(hdl, id);

	अगर ((qc->id & next_flags) && !list_empty(&hdl->ctrl_refs)) अणु
		bool is_compound;
		/* Match any control that is not hidden */
		अचिन्हित mask = 1;
		bool match = false;

		अगर ((qc->id & next_flags) == V4L2_CTRL_FLAG_NEXT_COMPOUND) अणु
			/* Match any hidden control */
			match = true;
		पूर्ण अन्यथा अगर ((qc->id & next_flags) == next_flags) अणु
			/* Match any control, compound or not */
			mask = 0;
		पूर्ण

		/* Find the next control with ID > qc->id */

		/* Did we reach the end of the control list? */
		अगर (id >= node2id(hdl->ctrl_refs.prev)) अणु
			ref = शून्य; /* Yes, so there is no next control */
		पूर्ण अन्यथा अगर (ref) अणु
			/* We found a control with the given ID, so just get
			   the next valid one in the list. */
			list_क्रम_each_entry_जारी(ref, &hdl->ctrl_refs, node) अणु
				is_compound = ref->ctrl->is_array ||
					ref->ctrl->type >= V4L2_CTRL_COMPOUND_TYPES;
				अगर (id < ref->ctrl->id &&
				    (is_compound & mask) == match)
					अवरोध;
			पूर्ण
			अगर (&ref->node == &hdl->ctrl_refs)
				ref = शून्य;
		पूर्ण अन्यथा अणु
			/* No control with the given ID exists, so start
			   searching क्रम the next largest ID. We know there
			   is one, otherwise the first 'if' above would have
			   been true. */
			list_क्रम_each_entry(ref, &hdl->ctrl_refs, node) अणु
				is_compound = ref->ctrl->is_array ||
					ref->ctrl->type >= V4L2_CTRL_COMPOUND_TYPES;
				अगर (id < ref->ctrl->id &&
				    (is_compound & mask) == match)
					अवरोध;
			पूर्ण
			अगर (&ref->node == &hdl->ctrl_refs)
				ref = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(hdl->lock);

	अगर (!ref)
		वापस -EINVAL;

	ctrl = ref->ctrl;
	स_रखो(qc, 0, माप(*qc));
	अगर (id >= V4L2_CID_PRIVATE_BASE)
		qc->id = id;
	अन्यथा
		qc->id = ctrl->id;
	strscpy(qc->name, ctrl->name, माप(qc->name));
	qc->flags = user_flags(ctrl);
	qc->type = ctrl->type;
	qc->elem_size = ctrl->elem_size;
	qc->elems = ctrl->elems;
	qc->nr_of_dims = ctrl->nr_of_dims;
	स_नकल(qc->dims, ctrl->dims, qc->nr_of_dims * माप(qc->dims[0]));
	qc->minimum = ctrl->minimum;
	qc->maximum = ctrl->maximum;
	qc->शेष_value = ctrl->शेष_value;
	अगर (ctrl->type == V4L2_CTRL_TYPE_MENU
	    || ctrl->type == V4L2_CTRL_TYPE_INTEGER_MENU)
		qc->step = 1;
	अन्यथा
		qc->step = ctrl->step;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_query_ext_ctrl);

/* Implement VIDIOC_QUERYCTRL */
पूर्णांक v4l2_queryctrl(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा v4l2_queryctrl *qc)
अणु
	काष्ठा v4l2_query_ext_ctrl qec = अणु qc->id पूर्ण;
	पूर्णांक rc;

	rc = v4l2_query_ext_ctrl(hdl, &qec);
	अगर (rc)
		वापस rc;

	qc->id = qec.id;
	qc->type = qec.type;
	qc->flags = qec.flags;
	strscpy(qc->name, qec.name, माप(qc->name));
	चयन (qc->type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER:
	हाल V4L2_CTRL_TYPE_BOOLEAN:
	हाल V4L2_CTRL_TYPE_MENU:
	हाल V4L2_CTRL_TYPE_INTEGER_MENU:
	हाल V4L2_CTRL_TYPE_STRING:
	हाल V4L2_CTRL_TYPE_BITMASK:
		qc->minimum = qec.minimum;
		qc->maximum = qec.maximum;
		qc->step = qec.step;
		qc->शेष_value = qec.शेष_value;
		अवरोध;
	शेष:
		qc->minimum = 0;
		qc->maximum = 0;
		qc->step = 0;
		qc->शेष_value = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_queryctrl);

/* Implement VIDIOC_QUERYMENU */
पूर्णांक v4l2_querymenu(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा v4l2_querymenu *qm)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	u32 i = qm->index;

	ctrl = v4l2_ctrl_find(hdl, qm->id);
	अगर (!ctrl)
		वापस -EINVAL;

	qm->reserved = 0;
	/* Sanity checks */
	चयन (ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_MENU:
		अगर (ctrl->qmenu == शून्य)
			वापस -EINVAL;
		अवरोध;
	हाल V4L2_CTRL_TYPE_INTEGER_MENU:
		अगर (ctrl->qmenu_पूर्णांक == शून्य)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (i < ctrl->minimum || i > ctrl->maximum)
		वापस -EINVAL;

	/* Use mask to see अगर this menu item should be skipped */
	अगर (ctrl->menu_skip_mask & (1ULL << i))
		वापस -EINVAL;
	/* Empty menu items should also be skipped */
	अगर (ctrl->type == V4L2_CTRL_TYPE_MENU) अणु
		अगर (ctrl->qmenu[i] == शून्य || ctrl->qmenu[i][0] == '\0')
			वापस -EINVAL;
		strscpy(qm->name, ctrl->qmenu[i], माप(qm->name));
	पूर्ण अन्यथा अणु
		qm->value = ctrl->qmenu_पूर्णांक[i];
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_querymenu);

अटल पूर्णांक v4l2_ctrl_request_clone(काष्ठा v4l2_ctrl_handler *hdl,
				   स्थिर काष्ठा v4l2_ctrl_handler *from)
अणु
	काष्ठा v4l2_ctrl_ref *ref;
	पूर्णांक err = 0;

	अगर (WARN_ON(!hdl || hdl == from))
		वापस -EINVAL;

	अगर (hdl->error)
		वापस hdl->error;

	WARN_ON(hdl->lock != &hdl->_lock);

	mutex_lock(from->lock);
	list_क्रम_each_entry(ref, &from->ctrl_refs, node) अणु
		काष्ठा v4l2_ctrl *ctrl = ref->ctrl;
		काष्ठा v4l2_ctrl_ref *new_ref;

		/* Skip refs inherited from other devices */
		अगर (ref->from_other_dev)
			जारी;
		err = handler_new_ref(hdl, ctrl, &new_ref, false, true);
		अगर (err)
			अवरोध;
	पूर्ण
	mutex_unlock(from->lock);
	वापस err;
पूर्ण

अटल व्योम v4l2_ctrl_request_queue(काष्ठा media_request_object *obj)
अणु
	काष्ठा v4l2_ctrl_handler *hdl =
		container_of(obj, काष्ठा v4l2_ctrl_handler, req_obj);
	काष्ठा v4l2_ctrl_handler *मुख्य_hdl = obj->priv;

	mutex_lock(मुख्य_hdl->lock);
	list_add_tail(&hdl->requests_queued, &मुख्य_hdl->requests_queued);
	hdl->request_is_queued = true;
	mutex_unlock(मुख्य_hdl->lock);
पूर्ण

अटल व्योम v4l2_ctrl_request_unbind(काष्ठा media_request_object *obj)
अणु
	काष्ठा v4l2_ctrl_handler *hdl =
		container_of(obj, काष्ठा v4l2_ctrl_handler, req_obj);
	काष्ठा v4l2_ctrl_handler *मुख्य_hdl = obj->priv;

	mutex_lock(मुख्य_hdl->lock);
	list_del_init(&hdl->requests);
	अगर (hdl->request_is_queued) अणु
		list_del_init(&hdl->requests_queued);
		hdl->request_is_queued = false;
	पूर्ण
	mutex_unlock(मुख्य_hdl->lock);
पूर्ण

अटल व्योम v4l2_ctrl_request_release(काष्ठा media_request_object *obj)
अणु
	काष्ठा v4l2_ctrl_handler *hdl =
		container_of(obj, काष्ठा v4l2_ctrl_handler, req_obj);

	v4l2_ctrl_handler_मुक्त(hdl);
	kमुक्त(hdl);
पूर्ण

अटल स्थिर काष्ठा media_request_object_ops req_ops = अणु
	.queue = v4l2_ctrl_request_queue,
	.unbind = v4l2_ctrl_request_unbind,
	.release = v4l2_ctrl_request_release,
पूर्ण;

काष्ठा v4l2_ctrl_handler *v4l2_ctrl_request_hdl_find(काष्ठा media_request *req,
					काष्ठा v4l2_ctrl_handler *parent)
अणु
	काष्ठा media_request_object *obj;

	अगर (WARN_ON(req->state != MEDIA_REQUEST_STATE_VALIDATING &&
		    req->state != MEDIA_REQUEST_STATE_QUEUED))
		वापस शून्य;

	obj = media_request_object_find(req, &req_ops, parent);
	अगर (obj)
		वापस container_of(obj, काष्ठा v4l2_ctrl_handler, req_obj);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_ctrl_request_hdl_find);

काष्ठा v4l2_ctrl *
v4l2_ctrl_request_hdl_ctrl_find(काष्ठा v4l2_ctrl_handler *hdl, u32 id)
अणु
	काष्ठा v4l2_ctrl_ref *ref = find_ref_lock(hdl, id);

	वापस (ref && ref->valid_p_req) ? ref->ctrl : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_ctrl_request_hdl_ctrl_find);

अटल पूर्णांक v4l2_ctrl_request_bind(काष्ठा media_request *req,
			   काष्ठा v4l2_ctrl_handler *hdl,
			   काष्ठा v4l2_ctrl_handler *from)
अणु
	पूर्णांक ret;

	ret = v4l2_ctrl_request_clone(hdl, from);

	अगर (!ret) अणु
		ret = media_request_object_bind(req, &req_ops,
						from, false, &hdl->req_obj);
		अगर (!ret) अणु
			mutex_lock(from->lock);
			list_add_tail(&hdl->requests, &from->requests);
			mutex_unlock(from->lock);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Some general notes on the atomic requirements of VIDIOC_G/TRY/S_EXT_CTRLS:

   It is not a fully atomic operation, just best-efक्रमt only. After all, अगर
   multiple controls have to be set through multiple i2c ग_लिखोs (क्रम example)
   then some initial ग_लिखोs may succeed जबतक others fail. Thus leaving the
   प्रणाली in an inconsistent state. The question is how much efक्रमt you are
   willing to spend on trying to make something atomic that really isn't.

   From the poपूर्णांक of view of an application the मुख्य requirement is that
   when you call VIDIOC_S_EXT_CTRLS and some values are invalid then an
   error should be वापसed without actually affecting any controls.

   If all the values are correct, then it is acceptable to just give up
   in हाल of low-level errors.

   It is important though that the application can tell when only a partial
   configuration was करोne. The way we करो that is through the error_idx field
   of काष्ठा v4l2_ext_controls: अगर that is equal to the count field then no
   controls were affected. Otherwise all controls beक्रमe that index were
   successful in perक्रमming their 'get' or 'set' operation, the control at
   the given index failed, and you करोn't know what happened with the controls
   after the failed one. Since अगर they were part of a control cluster they
   could have been successfully processed (अगर a cluster member was encountered
   at index < error_idx), they could have failed (अगर a cluster member was at
   error_idx), or they may not have been processed yet (अगर the first cluster
   member appeared after error_idx).

   It is all fairly theoretical, though. In practice all you can करो is to
   bail out. If error_idx == count, then it is an application bug. If
   error_idx < count then it is only an application bug अगर the error code was
   EBUSY. That usually means that something started streaming just when you
   tried to set the controls. In all other हालs it is a driver/hardware
   problem and all you can करो is to retry or bail out.

   Note that these rules करो not apply to VIDIOC_TRY_EXT_CTRLS: since that
   never modअगरies controls the error_idx is just set to whatever control
   has an invalid value.
 */

/* Prepare क्रम the extended g/s/try functions.
   Find the controls in the control array and करो some basic checks. */
अटल पूर्णांक prepare_ext_ctrls(काष्ठा v4l2_ctrl_handler *hdl,
			     काष्ठा v4l2_ext_controls *cs,
			     काष्ठा v4l2_ctrl_helper *helpers,
			     काष्ठा video_device *vdev,
			     bool get)
अणु
	काष्ठा v4l2_ctrl_helper *h;
	bool have_clusters = false;
	u32 i;

	क्रम (i = 0, h = helpers; i < cs->count; i++, h++) अणु
		काष्ठा v4l2_ext_control *c = &cs->controls[i];
		काष्ठा v4l2_ctrl_ref *ref;
		काष्ठा v4l2_ctrl *ctrl;
		u32 id = c->id & V4L2_CTRL_ID_MASK;

		cs->error_idx = i;

		अगर (cs->which &&
		    cs->which != V4L2_CTRL_WHICH_DEF_VAL &&
		    cs->which != V4L2_CTRL_WHICH_REQUEST_VAL &&
		    V4L2_CTRL_ID2WHICH(id) != cs->which) अणु
			dprपूर्णांकk(vdev,
				"invalid which 0x%x or control id 0x%x\n",
				cs->which, id);
			वापस -EINVAL;
		पूर्ण

		/* Old-style निजी controls are not allowed क्रम
		   extended controls */
		अगर (id >= V4L2_CID_PRIVATE_BASE) अणु
			dprपूर्णांकk(vdev,
				"old-style private controls not allowed\n");
			वापस -EINVAL;
		पूर्ण
		ref = find_ref_lock(hdl, id);
		अगर (ref == शून्य) अणु
			dprपूर्णांकk(vdev, "cannot find control id 0x%x\n", id);
			वापस -EINVAL;
		पूर्ण
		h->ref = ref;
		ctrl = ref->ctrl;
		अगर (ctrl->flags & V4L2_CTRL_FLAG_DISABLED) अणु
			dprपूर्णांकk(vdev, "control id 0x%x is disabled\n", id);
			वापस -EINVAL;
		पूर्ण

		अगर (ctrl->cluster[0]->ncontrols > 1)
			have_clusters = true;
		अगर (ctrl->cluster[0] != ctrl)
			ref = find_ref_lock(hdl, ctrl->cluster[0]->id);
		अगर (ctrl->is_ptr && !ctrl->is_string) अणु
			अचिन्हित tot_size = ctrl->elems * ctrl->elem_size;

			अगर (c->size < tot_size) अणु
				/*
				 * In the get हाल the application first
				 * queries to obtain the size of the control.
				 */
				अगर (get) अणु
					c->size = tot_size;
					वापस -ENOSPC;
				पूर्ण
				dprपूर्णांकk(vdev,
					"pointer control id 0x%x size too small, %d bytes but %d bytes needed\n",
					id, c->size, tot_size);
				वापस -EFAULT;
			पूर्ण
			c->size = tot_size;
		पूर्ण
		/* Store the ref to the master control of the cluster */
		h->mref = ref;
		/* Initially set next to 0, meaning that there is no other
		   control in this helper array beदीर्घing to the same
		   cluster */
		h->next = 0;
	पूर्ण

	/* We are करोne अगर there were no controls that beदीर्घ to a multi-
	   control cluster. */
	अगर (!have_clusters)
		वापस 0;

	/* The code below figures out in O(n) समय which controls in the list
	   beदीर्घ to the same cluster. */

	/* This has to be करोne with the handler lock taken. */
	mutex_lock(hdl->lock);

	/* First zero the helper field in the master control references */
	क्रम (i = 0; i < cs->count; i++)
		helpers[i].mref->helper = शून्य;
	क्रम (i = 0, h = helpers; i < cs->count; i++, h++) अणु
		काष्ठा v4l2_ctrl_ref *mref = h->mref;

		/* If the mref->helper is set, then it poपूर्णांकs to an earlier
		   helper that beदीर्घs to the same cluster. */
		अगर (mref->helper) अणु
			/* Set the next field of mref->helper to the current
			   index: this means that that earlier helper now
			   poपूर्णांकs to the next helper in the same cluster. */
			mref->helper->next = i;
			/* mref should be set only क्रम the first helper in the
			   cluster, clear the others. */
			h->mref = शून्य;
		पूर्ण
		/* Poपूर्णांक the mref helper to the current helper काष्ठा. */
		mref->helper = h;
	पूर्ण
	mutex_unlock(hdl->lock);
	वापस 0;
पूर्ण

/* Handles the corner हाल where cs->count == 0. It checks whether the
   specअगरied control class exists. If that class ID is 0, then it checks
   whether there are any controls at all. */
अटल पूर्णांक class_check(काष्ठा v4l2_ctrl_handler *hdl, u32 which)
अणु
	अगर (which == 0 || which == V4L2_CTRL_WHICH_DEF_VAL ||
	    which == V4L2_CTRL_WHICH_REQUEST_VAL)
		वापस 0;
	वापस find_ref_lock(hdl, which | 1) ? 0 : -EINVAL;
पूर्ण

/*
 * Get extended controls. Allocates the helpers array अगर needed.
 *
 * Note that v4l2_g_ext_ctrls_common() with 'which' set to
 * V4L2_CTRL_WHICH_REQUEST_VAL is only called अगर the request was
 * completed, and in that हाल valid_p_req is true क्रम all controls.
 */
अटल पूर्णांक v4l2_g_ext_ctrls_common(काष्ठा v4l2_ctrl_handler *hdl,
				   काष्ठा v4l2_ext_controls *cs,
				   काष्ठा video_device *vdev)
अणु
	काष्ठा v4l2_ctrl_helper helper[4];
	काष्ठा v4l2_ctrl_helper *helpers = helper;
	पूर्णांक ret;
	पूर्णांक i, j;
	bool is_शेष, is_request;

	is_शेष = (cs->which == V4L2_CTRL_WHICH_DEF_VAL);
	is_request = (cs->which == V4L2_CTRL_WHICH_REQUEST_VAL);

	cs->error_idx = cs->count;
	cs->which = V4L2_CTRL_ID2WHICH(cs->which);

	अगर (hdl == शून्य)
		वापस -EINVAL;

	अगर (cs->count == 0)
		वापस class_check(hdl, cs->which);

	अगर (cs->count > ARRAY_SIZE(helper)) अणु
		helpers = kvदो_स्मृति_array(cs->count, माप(helper[0]),
					 GFP_KERNEL);
		अगर (helpers == शून्य)
			वापस -ENOMEM;
	पूर्ण

	ret = prepare_ext_ctrls(hdl, cs, helpers, vdev, true);
	cs->error_idx = cs->count;

	क्रम (i = 0; !ret && i < cs->count; i++)
		अगर (helpers[i].ref->ctrl->flags & V4L2_CTRL_FLAG_WRITE_ONLY)
			ret = -EACCES;

	क्रम (i = 0; !ret && i < cs->count; i++) अणु
		काष्ठा v4l2_ctrl *master;
		bool is_अस्थिर = false;
		u32 idx = i;

		अगर (helpers[i].mref == शून्य)
			जारी;

		master = helpers[i].mref->ctrl;
		cs->error_idx = i;

		v4l2_ctrl_lock(master);

		/*
		 * g_अस्थिर_ctrl will update the new control values.
		 * This makes no sense क्रम V4L2_CTRL_WHICH_DEF_VAL and
		 * V4L2_CTRL_WHICH_REQUEST_VAL. In the हाल of requests
		 * it is v4l2_ctrl_request_complete() that copies the
		 * अस्थिर controls at the समय of request completion
		 * to the request, so you करोn't want to करो that again.
		 */
		अगर (!is_शेष && !is_request &&
		    ((master->flags & V4L2_CTRL_FLAG_VOLATILE) ||
		    (master->has_अस्थिरs && !is_cur_manual(master)))) अणु
			क्रम (j = 0; j < master->ncontrols; j++)
				cur_to_new(master->cluster[j]);
			ret = call_op(master, g_अस्थिर_ctrl);
			is_अस्थिर = true;
		पूर्ण

		अगर (ret) अणु
			v4l2_ctrl_unlock(master);
			अवरोध;
		पूर्ण

		/*
		 * Copy the शेष value (अगर is_शेष is true), the
		 * request value (अगर is_request is true and p_req is valid),
		 * the new अस्थिर value (अगर is_अस्थिर is true) or the
		 * current value.
		 */
		करो अणु
			काष्ठा v4l2_ctrl_ref *ref = helpers[idx].ref;

			अगर (is_शेष)
				ret = def_to_user(cs->controls + idx, ref->ctrl);
			अन्यथा अगर (is_request && ref->valid_p_req)
				ret = req_to_user(cs->controls + idx, ref);
			अन्यथा अगर (is_अस्थिर)
				ret = new_to_user(cs->controls + idx, ref->ctrl);
			अन्यथा
				ret = cur_to_user(cs->controls + idx, ref->ctrl);
			idx = helpers[idx].next;
		पूर्ण जबतक (!ret && idx);

		v4l2_ctrl_unlock(master);
	पूर्ण

	अगर (cs->count > ARRAY_SIZE(helper))
		kvमुक्त(helpers);
	वापस ret;
पूर्ण

अटल काष्ठा media_request_object *
v4l2_ctrls_find_req_obj(काष्ठा v4l2_ctrl_handler *hdl,
			काष्ठा media_request *req, bool set)
अणु
	काष्ठा media_request_object *obj;
	काष्ठा v4l2_ctrl_handler *new_hdl;
	पूर्णांक ret;

	अगर (IS_ERR(req))
		वापस ERR_CAST(req);

	अगर (set && WARN_ON(req->state != MEDIA_REQUEST_STATE_UPDATING))
		वापस ERR_PTR(-EBUSY);

	obj = media_request_object_find(req, &req_ops, hdl);
	अगर (obj)
		वापस obj;
	अगर (!set)
		वापस ERR_PTR(-ENOENT);

	new_hdl = kzalloc(माप(*new_hdl), GFP_KERNEL);
	अगर (!new_hdl)
		वापस ERR_PTR(-ENOMEM);

	obj = &new_hdl->req_obj;
	ret = v4l2_ctrl_handler_init(new_hdl, (hdl->nr_of_buckets - 1) * 8);
	अगर (!ret)
		ret = v4l2_ctrl_request_bind(req, new_hdl, hdl);
	अगर (ret) अणु
		kमुक्त(new_hdl);

		वापस ERR_PTR(ret);
	पूर्ण

	media_request_object_get(obj);
	वापस obj;
पूर्ण

पूर्णांक v4l2_g_ext_ctrls(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा video_device *vdev,
		     काष्ठा media_device *mdev, काष्ठा v4l2_ext_controls *cs)
अणु
	काष्ठा media_request_object *obj = शून्य;
	काष्ठा media_request *req = शून्य;
	पूर्णांक ret;

	अगर (cs->which == V4L2_CTRL_WHICH_REQUEST_VAL) अणु
		अगर (!mdev || cs->request_fd < 0)
			वापस -EINVAL;

		req = media_request_get_by_fd(mdev, cs->request_fd);
		अगर (IS_ERR(req))
			वापस PTR_ERR(req);

		अगर (req->state != MEDIA_REQUEST_STATE_COMPLETE) अणु
			media_request_put(req);
			वापस -EACCES;
		पूर्ण

		ret = media_request_lock_क्रम_access(req);
		अगर (ret) अणु
			media_request_put(req);
			वापस ret;
		पूर्ण

		obj = v4l2_ctrls_find_req_obj(hdl, req, false);
		अगर (IS_ERR(obj)) अणु
			media_request_unlock_क्रम_access(req);
			media_request_put(req);
			वापस PTR_ERR(obj);
		पूर्ण

		hdl = container_of(obj, काष्ठा v4l2_ctrl_handler,
				   req_obj);
	पूर्ण

	ret = v4l2_g_ext_ctrls_common(hdl, cs, vdev);

	अगर (obj) अणु
		media_request_unlock_क्रम_access(req);
		media_request_object_put(obj);
		media_request_put(req);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_g_ext_ctrls);

/* Helper function to get a single control */
अटल पूर्णांक get_ctrl(काष्ठा v4l2_ctrl *ctrl, काष्ठा v4l2_ext_control *c)
अणु
	काष्ठा v4l2_ctrl *master = ctrl->cluster[0];
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Compound controls are not supported. The new_to_user() and
	 * cur_to_user() calls below would need to be modअगरied not to access
	 * userspace memory when called from get_ctrl().
	 */
	अगर (!ctrl->is_पूर्णांक && ctrl->type != V4L2_CTRL_TYPE_INTEGER64)
		वापस -EINVAL;

	अगर (ctrl->flags & V4L2_CTRL_FLAG_WRITE_ONLY)
		वापस -EACCES;

	v4l2_ctrl_lock(master);
	/* g_अस्थिर_ctrl will update the current control values */
	अगर (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE) अणु
		क्रम (i = 0; i < master->ncontrols; i++)
			cur_to_new(master->cluster[i]);
		ret = call_op(master, g_अस्थिर_ctrl);
		new_to_user(c, ctrl);
	पूर्ण अन्यथा अणु
		cur_to_user(c, ctrl);
	पूर्ण
	v4l2_ctrl_unlock(master);
	वापस ret;
पूर्ण

पूर्णांक v4l2_g_ctrl(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा v4l2_control *control)
अणु
	काष्ठा v4l2_ctrl *ctrl = v4l2_ctrl_find(hdl, control->id);
	काष्ठा v4l2_ext_control c;
	पूर्णांक ret;

	अगर (ctrl == शून्य || !ctrl->is_पूर्णांक)
		वापस -EINVAL;
	ret = get_ctrl(ctrl, &c);
	control->value = c.value;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_g_ctrl);

s32 v4l2_ctrl_g_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_ext_control c;

	/* It's a driver bug अगर this happens. */
	अगर (WARN_ON(!ctrl->is_पूर्णांक))
		वापस 0;
	c.value = 0;
	get_ctrl(ctrl, &c);
	वापस c.value;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_g_ctrl);

s64 v4l2_ctrl_g_ctrl_पूर्णांक64(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_ext_control c;

	/* It's a driver bug अगर this happens. */
	अगर (WARN_ON(ctrl->is_ptr || ctrl->type != V4L2_CTRL_TYPE_INTEGER64))
		वापस 0;
	c.value64 = 0;
	get_ctrl(ctrl, &c);
	वापस c.value64;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_g_ctrl_पूर्णांक64);


/* Core function that calls try/s_ctrl and ensures that the new value is
   copied to the current value on a set.
   Must be called with ctrl->handler->lock held. */
अटल पूर्णांक try_or_set_cluster(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl *master,
			      bool set, u32 ch_flags)
अणु
	bool update_flag;
	पूर्णांक ret;
	पूर्णांक i;

	/* Go through the cluster and either validate the new value or
	   (अगर no new value was set), copy the current value to the new
	   value, ensuring a consistent view क्रम the control ops when
	   called. */
	क्रम (i = 0; i < master->ncontrols; i++) अणु
		काष्ठा v4l2_ctrl *ctrl = master->cluster[i];

		अगर (ctrl == शून्य)
			जारी;

		अगर (!ctrl->is_new) अणु
			cur_to_new(ctrl);
			जारी;
		पूर्ण
		/* Check again: it may have changed since the
		   previous check in try_or_set_ext_ctrls(). */
		अगर (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED))
			वापस -EBUSY;
	पूर्ण

	ret = call_op(master, try_ctrl);

	/* Don't set अगर there is no change */
	अगर (ret || !set || !cluster_changed(master))
		वापस ret;
	ret = call_op(master, s_ctrl);
	अगर (ret)
		वापस ret;

	/* If OK, then make the new values permanent. */
	update_flag = is_cur_manual(master) != is_new_manual(master);

	क्रम (i = 0; i < master->ncontrols; i++) अणु
		/*
		 * If we चयन from स्वतः to manual mode, and this cluster
		 * contains अस्थिर controls, then all non-master controls
		 * have to be marked as changed. The 'new' value contains
		 * the अस्थिर value (obtained by update_from_स्वतः_cluster),
		 * which now has to become the current value.
		 */
		अगर (i && update_flag && is_new_manual(master) &&
		    master->has_अस्थिरs && master->cluster[i])
			master->cluster[i]->has_changed = true;

		new_to_cur(fh, master->cluster[i], ch_flags |
			((update_flag && i > 0) ? V4L2_EVENT_CTRL_CH_FLAGS : 0));
	पूर्ण
	वापस 0;
पूर्ण

/* Validate controls. */
अटल पूर्णांक validate_ctrls(काष्ठा v4l2_ext_controls *cs,
			  काष्ठा v4l2_ctrl_helper *helpers,
			  काष्ठा video_device *vdev,
			  bool set)
अणु
	अचिन्हित i;
	पूर्णांक ret = 0;

	cs->error_idx = cs->count;
	क्रम (i = 0; i < cs->count; i++) अणु
		काष्ठा v4l2_ctrl *ctrl = helpers[i].ref->ctrl;
		जोड़ v4l2_ctrl_ptr p_new;

		cs->error_idx = i;

		अगर (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY) अणु
			dprपूर्णांकk(vdev,
				"control id 0x%x is read-only\n",
				ctrl->id);
			वापस -EACCES;
		पूर्ण
		/* This test is also करोne in try_set_control_cluster() which
		   is called in atomic context, so that has the final say,
		   but it makes sense to करो an up-front check as well. Once
		   an error occurs in try_set_control_cluster() some other
		   controls may have been set alपढ़ोy and we want to करो a
		   best-efक्रमt to aव्योम that. */
		अगर (set && (ctrl->flags & V4L2_CTRL_FLAG_GRABBED)) अणु
			dprपूर्णांकk(vdev,
				"control id 0x%x is grabbed, cannot set\n",
				ctrl->id);
			वापस -EBUSY;
		पूर्ण
		/*
		 * Skip validation क्रम now अगर the payload needs to be copied
		 * from userspace पूर्णांकo kernelspace. We'll validate those later.
		 */
		अगर (ctrl->is_ptr)
			जारी;
		अगर (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
			p_new.p_s64 = &cs->controls[i].value64;
		अन्यथा
			p_new.p_s32 = &cs->controls[i].value;
		ret = validate_new(ctrl, p_new);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Obtain the current अस्थिर values of an स्वतःcluster and mark them
   as new. */
अटल व्योम update_from_स्वतः_cluster(काष्ठा v4l2_ctrl *master)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < master->ncontrols; i++)
		cur_to_new(master->cluster[i]);
	अगर (!call_op(master, g_अस्थिर_ctrl))
		क्रम (i = 1; i < master->ncontrols; i++)
			अगर (master->cluster[i])
				master->cluster[i]->is_new = 1;
पूर्ण

/* Try or try-and-set controls */
अटल पूर्णांक try_set_ext_ctrls_common(काष्ठा v4l2_fh *fh,
				    काष्ठा v4l2_ctrl_handler *hdl,
				    काष्ठा v4l2_ext_controls *cs,
				    काष्ठा video_device *vdev, bool set)
अणु
	काष्ठा v4l2_ctrl_helper helper[4];
	काष्ठा v4l2_ctrl_helper *helpers = helper;
	अचिन्हित i, j;
	पूर्णांक ret;

	cs->error_idx = cs->count;

	/* Default value cannot be changed */
	अगर (cs->which == V4L2_CTRL_WHICH_DEF_VAL) अणु
		dprपूर्णांकk(vdev, "%s: cannot change default value\n",
			video_device_node_name(vdev));
		वापस -EINVAL;
	पूर्ण

	cs->which = V4L2_CTRL_ID2WHICH(cs->which);

	अगर (hdl == शून्य) अणु
		dprपूर्णांकk(vdev, "%s: invalid null control handler\n",
			video_device_node_name(vdev));
		वापस -EINVAL;
	पूर्ण

	अगर (cs->count == 0)
		वापस class_check(hdl, cs->which);

	अगर (cs->count > ARRAY_SIZE(helper)) अणु
		helpers = kvदो_स्मृति_array(cs->count, माप(helper[0]),
					 GFP_KERNEL);
		अगर (!helpers)
			वापस -ENOMEM;
	पूर्ण
	ret = prepare_ext_ctrls(hdl, cs, helpers, vdev, false);
	अगर (!ret)
		ret = validate_ctrls(cs, helpers, vdev, set);
	अगर (ret && set)
		cs->error_idx = cs->count;
	क्रम (i = 0; !ret && i < cs->count; i++) अणु
		काष्ठा v4l2_ctrl *master;
		u32 idx = i;

		अगर (helpers[i].mref == शून्य)
			जारी;

		cs->error_idx = i;
		master = helpers[i].mref->ctrl;
		v4l2_ctrl_lock(master);

		/* Reset the 'is_new' flags of the cluster */
		क्रम (j = 0; j < master->ncontrols; j++)
			अगर (master->cluster[j])
				master->cluster[j]->is_new = 0;

		/* For अस्थिर स्वतःclusters that are currently in स्वतः mode
		   we need to discover अगर it will be set to manual mode.
		   If so, then we have to copy the current अस्थिर values
		   first since those will become the new manual values (which
		   may be overwritten by explicit new values from this set
		   of controls). */
		अगर (master->is_स्वतः && master->has_अस्थिरs &&
						!is_cur_manual(master)) अणु
			/* Pick an initial non-manual value */
			s32 new_स्वतः_val = master->manual_mode_value + 1;
			u32 पंचांगp_idx = idx;

			करो अणु
				/* Check अगर the स्वतः control is part of the
				   list, and remember the new value. */
				अगर (helpers[पंचांगp_idx].ref->ctrl == master)
					new_स्वतः_val = cs->controls[पंचांगp_idx].value;
				पंचांगp_idx = helpers[पंचांगp_idx].next;
			पूर्ण जबतक (पंचांगp_idx);
			/* If the new value == the manual value, then copy
			   the current अस्थिर values. */
			अगर (new_स्वतः_val == master->manual_mode_value)
				update_from_स्वतः_cluster(master);
		पूर्ण

		/* Copy the new caller-supplied control values.
		   user_to_new() sets 'is_new' to 1. */
		करो अणु
			काष्ठा v4l2_ctrl *ctrl = helpers[idx].ref->ctrl;

			ret = user_to_new(cs->controls + idx, ctrl);
			अगर (!ret && ctrl->is_ptr) अणु
				ret = validate_new(ctrl, ctrl->p_new);
				अगर (ret)
					dprपूर्णांकk(vdev,
						"failed to validate control %s (%d)\n",
						v4l2_ctrl_get_name(ctrl->id), ret);
			पूर्ण
			idx = helpers[idx].next;
		पूर्ण जबतक (!ret && idx);

		अगर (!ret)
			ret = try_or_set_cluster(fh, master,
						 !hdl->req_obj.req && set, 0);
		अगर (!ret && hdl->req_obj.req && set) अणु
			क्रम (j = 0; j < master->ncontrols; j++) अणु
				काष्ठा v4l2_ctrl_ref *ref =
					find_ref(hdl, master->cluster[j]->id);

				new_to_req(ref);
			पूर्ण
		पूर्ण

		/* Copy the new values back to userspace. */
		अगर (!ret) अणु
			idx = i;
			करो अणु
				ret = new_to_user(cs->controls + idx,
						helpers[idx].ref->ctrl);
				idx = helpers[idx].next;
			पूर्ण जबतक (!ret && idx);
		पूर्ण
		v4l2_ctrl_unlock(master);
	पूर्ण

	अगर (cs->count > ARRAY_SIZE(helper))
		kvमुक्त(helpers);
	वापस ret;
पूर्ण

अटल पूर्णांक try_set_ext_ctrls(काष्ठा v4l2_fh *fh,
			     काष्ठा v4l2_ctrl_handler *hdl,
			     काष्ठा video_device *vdev,
			     काष्ठा media_device *mdev,
			     काष्ठा v4l2_ext_controls *cs, bool set)
अणु
	काष्ठा media_request_object *obj = शून्य;
	काष्ठा media_request *req = शून्य;
	पूर्णांक ret;

	अगर (cs->which == V4L2_CTRL_WHICH_REQUEST_VAL) अणु
		अगर (!mdev) अणु
			dprपूर्णांकk(vdev, "%s: missing media device\n",
				video_device_node_name(vdev));
			वापस -EINVAL;
		पूर्ण

		अगर (cs->request_fd < 0) अणु
			dprपूर्णांकk(vdev, "%s: invalid request fd %d\n",
				video_device_node_name(vdev), cs->request_fd);
			वापस -EINVAL;
		पूर्ण

		req = media_request_get_by_fd(mdev, cs->request_fd);
		अगर (IS_ERR(req)) अणु
			dprपूर्णांकk(vdev, "%s: cannot find request fd %d\n",
				video_device_node_name(vdev), cs->request_fd);
			वापस PTR_ERR(req);
		पूर्ण

		ret = media_request_lock_क्रम_update(req);
		अगर (ret) अणु
			dprपूर्णांकk(vdev, "%s: cannot lock request fd %d\n",
				video_device_node_name(vdev), cs->request_fd);
			media_request_put(req);
			वापस ret;
		पूर्ण

		obj = v4l2_ctrls_find_req_obj(hdl, req, set);
		अगर (IS_ERR(obj)) अणु
			dprपूर्णांकk(vdev,
				"%s: cannot find request object for request fd %d\n",
				video_device_node_name(vdev),
				cs->request_fd);
			media_request_unlock_क्रम_update(req);
			media_request_put(req);
			वापस PTR_ERR(obj);
		पूर्ण
		hdl = container_of(obj, काष्ठा v4l2_ctrl_handler,
				   req_obj);
	पूर्ण

	ret = try_set_ext_ctrls_common(fh, hdl, cs, vdev, set);
	अगर (ret)
		dprपूर्णांकk(vdev,
			"%s: try_set_ext_ctrls_common failed (%d)\n",
			video_device_node_name(vdev), ret);

	अगर (obj) अणु
		media_request_unlock_क्रम_update(req);
		media_request_object_put(obj);
		media_request_put(req);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक v4l2_try_ext_ctrls(काष्ठा v4l2_ctrl_handler *hdl,
		       काष्ठा video_device *vdev,
		       काष्ठा media_device *mdev,
		       काष्ठा v4l2_ext_controls *cs)
अणु
	वापस try_set_ext_ctrls(शून्य, hdl, vdev, mdev, cs, false);
पूर्ण
EXPORT_SYMBOL(v4l2_try_ext_ctrls);

पूर्णांक v4l2_s_ext_ctrls(काष्ठा v4l2_fh *fh,
		     काष्ठा v4l2_ctrl_handler *hdl,
		     काष्ठा video_device *vdev,
		     काष्ठा media_device *mdev,
		     काष्ठा v4l2_ext_controls *cs)
अणु
	वापस try_set_ext_ctrls(fh, hdl, vdev, mdev, cs, true);
पूर्ण
EXPORT_SYMBOL(v4l2_s_ext_ctrls);

/* Helper function क्रम VIDIOC_S_CTRL compatibility */
अटल पूर्णांक set_ctrl(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl *ctrl, u32 ch_flags)
अणु
	काष्ठा v4l2_ctrl *master = ctrl->cluster[0];
	पूर्णांक ret;
	पूर्णांक i;

	/* Reset the 'is_new' flags of the cluster */
	क्रम (i = 0; i < master->ncontrols; i++)
		अगर (master->cluster[i])
			master->cluster[i]->is_new = 0;

	ret = validate_new(ctrl, ctrl->p_new);
	अगर (ret)
		वापस ret;

	/* For स्वतःclusters with अस्थिरs that are चयनed from स्वतः to
	   manual mode we have to update the current अस्थिर values since
	   those will become the initial manual values after such a चयन. */
	अगर (master->is_स्वतः && master->has_अस्थिरs && ctrl == master &&
	    !is_cur_manual(master) && ctrl->val == master->manual_mode_value)
		update_from_स्वतः_cluster(master);

	ctrl->is_new = 1;
	वापस try_or_set_cluster(fh, master, true, ch_flags);
पूर्ण

/* Helper function क्रम VIDIOC_S_CTRL compatibility */
अटल पूर्णांक set_ctrl_lock(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl *ctrl,
			 काष्ठा v4l2_ext_control *c)
अणु
	पूर्णांक ret;

	v4l2_ctrl_lock(ctrl);
	user_to_new(c, ctrl);
	ret = set_ctrl(fh, ctrl, 0);
	अगर (!ret)
		cur_to_user(c, ctrl);
	v4l2_ctrl_unlock(ctrl);
	वापस ret;
पूर्ण

पूर्णांक v4l2_s_ctrl(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl_handler *hdl,
					काष्ठा v4l2_control *control)
अणु
	काष्ठा v4l2_ctrl *ctrl = v4l2_ctrl_find(hdl, control->id);
	काष्ठा v4l2_ext_control c = अणु control->id पूर्ण;
	पूर्णांक ret;

	अगर (ctrl == शून्य || !ctrl->is_पूर्णांक)
		वापस -EINVAL;

	अगर (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY)
		वापस -EACCES;

	c.value = control->value;
	ret = set_ctrl_lock(fh, ctrl, &c);
	control->value = c.value;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_s_ctrl);

पूर्णांक __v4l2_ctrl_s_ctrl(काष्ठा v4l2_ctrl *ctrl, s32 val)
अणु
	lockdep_निश्चित_held(ctrl->handler->lock);

	/* It's a driver bug अगर this happens. */
	अगर (WARN_ON(!ctrl->is_पूर्णांक))
		वापस -EINVAL;
	ctrl->val = val;
	वापस set_ctrl(शून्य, ctrl, 0);
पूर्ण
EXPORT_SYMBOL(__v4l2_ctrl_s_ctrl);

पूर्णांक __v4l2_ctrl_s_ctrl_पूर्णांक64(काष्ठा v4l2_ctrl *ctrl, s64 val)
अणु
	lockdep_निश्चित_held(ctrl->handler->lock);

	/* It's a driver bug अगर this happens. */
	अगर (WARN_ON(ctrl->is_ptr || ctrl->type != V4L2_CTRL_TYPE_INTEGER64))
		वापस -EINVAL;
	*ctrl->p_new.p_s64 = val;
	वापस set_ctrl(शून्य, ctrl, 0);
पूर्ण
EXPORT_SYMBOL(__v4l2_ctrl_s_ctrl_पूर्णांक64);

पूर्णांक __v4l2_ctrl_s_ctrl_string(काष्ठा v4l2_ctrl *ctrl, स्थिर अक्षर *s)
अणु
	lockdep_निश्चित_held(ctrl->handler->lock);

	/* It's a driver bug अगर this happens. */
	अगर (WARN_ON(ctrl->type != V4L2_CTRL_TYPE_STRING))
		वापस -EINVAL;
	strscpy(ctrl->p_new.p_अक्षर, s, ctrl->maximum + 1);
	वापस set_ctrl(शून्य, ctrl, 0);
पूर्ण
EXPORT_SYMBOL(__v4l2_ctrl_s_ctrl_string);

पूर्णांक __v4l2_ctrl_s_ctrl_compound(काष्ठा v4l2_ctrl *ctrl,
				क्रमागत v4l2_ctrl_type type, स्थिर व्योम *p)
अणु
	lockdep_निश्चित_held(ctrl->handler->lock);

	/* It's a driver bug अगर this happens. */
	अगर (WARN_ON(ctrl->type != type))
		वापस -EINVAL;
	स_नकल(ctrl->p_new.p, p, ctrl->elems * ctrl->elem_size);
	वापस set_ctrl(शून्य, ctrl, 0);
पूर्ण
EXPORT_SYMBOL(__v4l2_ctrl_s_ctrl_compound);

व्योम v4l2_ctrl_request_complete(काष्ठा media_request *req,
				काष्ठा v4l2_ctrl_handler *मुख्य_hdl)
अणु
	काष्ठा media_request_object *obj;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_ctrl_ref *ref;

	अगर (!req || !मुख्य_hdl)
		वापस;

	/*
	 * Note that it is valid अगर nothing was found. It means
	 * that this request करोesn't have any controls and so just
	 * wants to leave the controls unchanged.
	 */
	obj = media_request_object_find(req, &req_ops, मुख्य_hdl);
	अगर (!obj)
		वापस;
	hdl = container_of(obj, काष्ठा v4l2_ctrl_handler, req_obj);

	list_क्रम_each_entry(ref, &hdl->ctrl_refs, node) अणु
		काष्ठा v4l2_ctrl *ctrl = ref->ctrl;
		काष्ठा v4l2_ctrl *master = ctrl->cluster[0];
		अचिन्हित पूर्णांक i;

		अगर (ctrl->flags & V4L2_CTRL_FLAG_VOLATILE) अणु
			v4l2_ctrl_lock(master);
			/* g_अस्थिर_ctrl will update the current control values */
			क्रम (i = 0; i < master->ncontrols; i++)
				cur_to_new(master->cluster[i]);
			call_op(master, g_अस्थिर_ctrl);
			new_to_req(ref);
			v4l2_ctrl_unlock(master);
			जारी;
		पूर्ण
		अगर (ref->valid_p_req)
			जारी;

		/* Copy the current control value पूर्णांकo the request */
		v4l2_ctrl_lock(ctrl);
		cur_to_req(ref);
		v4l2_ctrl_unlock(ctrl);
	पूर्ण

	mutex_lock(मुख्य_hdl->lock);
	WARN_ON(!hdl->request_is_queued);
	list_del_init(&hdl->requests_queued);
	hdl->request_is_queued = false;
	mutex_unlock(मुख्य_hdl->lock);
	media_request_object_complete(obj);
	media_request_object_put(obj);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_request_complete);

पूर्णांक v4l2_ctrl_request_setup(काष्ठा media_request *req,
			     काष्ठा v4l2_ctrl_handler *मुख्य_hdl)
अणु
	काष्ठा media_request_object *obj;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_ctrl_ref *ref;
	पूर्णांक ret = 0;

	अगर (!req || !मुख्य_hdl)
		वापस 0;

	अगर (WARN_ON(req->state != MEDIA_REQUEST_STATE_QUEUED))
		वापस -EBUSY;

	/*
	 * Note that it is valid अगर nothing was found. It means
	 * that this request करोesn't have any controls and so just
	 * wants to leave the controls unchanged.
	 */
	obj = media_request_object_find(req, &req_ops, मुख्य_hdl);
	अगर (!obj)
		वापस 0;
	अगर (obj->completed) अणु
		media_request_object_put(obj);
		वापस -EBUSY;
	पूर्ण
	hdl = container_of(obj, काष्ठा v4l2_ctrl_handler, req_obj);

	list_क्रम_each_entry(ref, &hdl->ctrl_refs, node)
		ref->req_करोne = false;

	list_क्रम_each_entry(ref, &hdl->ctrl_refs, node) अणु
		काष्ठा v4l2_ctrl *ctrl = ref->ctrl;
		काष्ठा v4l2_ctrl *master = ctrl->cluster[0];
		bool have_new_data = false;
		पूर्णांक i;

		/*
		 * Skip अगर this control was alपढ़ोy handled by a cluster.
		 * Skip button controls and पढ़ो-only controls.
		 */
		अगर (ref->req_करोne || (ctrl->flags & V4L2_CTRL_FLAG_READ_ONLY))
			जारी;

		v4l2_ctrl_lock(master);
		क्रम (i = 0; i < master->ncontrols; i++) अणु
			अगर (master->cluster[i]) अणु
				काष्ठा v4l2_ctrl_ref *r =
					find_ref(hdl, master->cluster[i]->id);

				अगर (r->valid_p_req) अणु
					have_new_data = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!have_new_data) अणु
			v4l2_ctrl_unlock(master);
			जारी;
		पूर्ण

		क्रम (i = 0; i < master->ncontrols; i++) अणु
			अगर (master->cluster[i]) अणु
				काष्ठा v4l2_ctrl_ref *r =
					find_ref(hdl, master->cluster[i]->id);

				req_to_new(r);
				master->cluster[i]->is_new = 1;
				r->req_करोne = true;
			पूर्ण
		पूर्ण
		/*
		 * For अस्थिर स्वतःclusters that are currently in स्वतः mode
		 * we need to discover अगर it will be set to manual mode.
		 * If so, then we have to copy the current अस्थिर values
		 * first since those will become the new manual values (which
		 * may be overwritten by explicit new values from this set
		 * of controls).
		 */
		अगर (master->is_स्वतः && master->has_अस्थिरs &&
		    !is_cur_manual(master)) अणु
			s32 new_स्वतः_val = *master->p_new.p_s32;

			/*
			 * If the new value == the manual value, then copy
			 * the current अस्थिर values.
			 */
			अगर (new_स्वतः_val == master->manual_mode_value)
				update_from_स्वतः_cluster(master);
		पूर्ण

		ret = try_or_set_cluster(शून्य, master, true, 0);
		v4l2_ctrl_unlock(master);

		अगर (ret)
			अवरोध;
	पूर्ण

	media_request_object_put(obj);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_request_setup);

व्योम v4l2_ctrl_notअगरy(काष्ठा v4l2_ctrl *ctrl, v4l2_ctrl_notअगरy_fnc notअगरy, व्योम *priv)
अणु
	अगर (ctrl == शून्य)
		वापस;
	अगर (notअगरy == शून्य) अणु
		ctrl->call_notअगरy = 0;
		वापस;
	पूर्ण
	अगर (WARN_ON(ctrl->handler->notअगरy && ctrl->handler->notअगरy != notअगरy))
		वापस;
	ctrl->handler->notअगरy = notअगरy;
	ctrl->handler->notअगरy_priv = priv;
	ctrl->call_notअगरy = 1;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_notअगरy);

पूर्णांक __v4l2_ctrl_modअगरy_range(काष्ठा v4l2_ctrl *ctrl,
			s64 min, s64 max, u64 step, s64 def)
अणु
	bool value_changed;
	bool range_changed = false;
	पूर्णांक ret;

	lockdep_निश्चित_held(ctrl->handler->lock);

	चयन (ctrl->type) अणु
	हाल V4L2_CTRL_TYPE_INTEGER:
	हाल V4L2_CTRL_TYPE_INTEGER64:
	हाल V4L2_CTRL_TYPE_BOOLEAN:
	हाल V4L2_CTRL_TYPE_MENU:
	हाल V4L2_CTRL_TYPE_INTEGER_MENU:
	हाल V4L2_CTRL_TYPE_BITMASK:
	हाल V4L2_CTRL_TYPE_U8:
	हाल V4L2_CTRL_TYPE_U16:
	हाल V4L2_CTRL_TYPE_U32:
		अगर (ctrl->is_array)
			वापस -EINVAL;
		ret = check_range(ctrl->type, min, max, step, def);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर ((ctrl->minimum != min) || (ctrl->maximum != max) ||
		(ctrl->step != step) || ctrl->शेष_value != def) अणु
		range_changed = true;
		ctrl->minimum = min;
		ctrl->maximum = max;
		ctrl->step = step;
		ctrl->शेष_value = def;
	पूर्ण
	cur_to_new(ctrl);
	अगर (validate_new(ctrl, ctrl->p_new)) अणु
		अगर (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
			*ctrl->p_new.p_s64 = def;
		अन्यथा
			*ctrl->p_new.p_s32 = def;
	पूर्ण

	अगर (ctrl->type == V4L2_CTRL_TYPE_INTEGER64)
		value_changed = *ctrl->p_new.p_s64 != *ctrl->p_cur.p_s64;
	अन्यथा
		value_changed = *ctrl->p_new.p_s32 != *ctrl->p_cur.p_s32;
	अगर (value_changed)
		ret = set_ctrl(शून्य, ctrl, V4L2_EVENT_CTRL_CH_RANGE);
	अन्यथा अगर (range_changed)
		send_event(शून्य, ctrl, V4L2_EVENT_CTRL_CH_RANGE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__v4l2_ctrl_modअगरy_range);

अटल पूर्णांक v4l2_ctrl_add_event(काष्ठा v4l2_subscribed_event *sev, अचिन्हित elems)
अणु
	काष्ठा v4l2_ctrl *ctrl = v4l2_ctrl_find(sev->fh->ctrl_handler, sev->id);

	अगर (ctrl == शून्य)
		वापस -EINVAL;

	v4l2_ctrl_lock(ctrl);
	list_add_tail(&sev->node, &ctrl->ev_subs);
	अगर (ctrl->type != V4L2_CTRL_TYPE_CTRL_CLASS &&
	    (sev->flags & V4L2_EVENT_SUB_FL_SEND_INITIAL)) अणु
		काष्ठा v4l2_event ev;
		u32 changes = V4L2_EVENT_CTRL_CH_FLAGS;

		अगर (!(ctrl->flags & V4L2_CTRL_FLAG_WRITE_ONLY))
			changes |= V4L2_EVENT_CTRL_CH_VALUE;
		fill_event(&ev, ctrl, changes);
		/* Mark the queue as active, allowing this initial
		   event to be accepted. */
		sev->elems = elems;
		v4l2_event_queue_fh(sev->fh, &ev);
	पूर्ण
	v4l2_ctrl_unlock(ctrl);
	वापस 0;
पूर्ण

अटल व्योम v4l2_ctrl_del_event(काष्ठा v4l2_subscribed_event *sev)
अणु
	काष्ठा v4l2_ctrl *ctrl = v4l2_ctrl_find(sev->fh->ctrl_handler, sev->id);

	अगर (ctrl == शून्य)
		वापस;

	v4l2_ctrl_lock(ctrl);
	list_del(&sev->node);
	v4l2_ctrl_unlock(ctrl);
पूर्ण

व्योम v4l2_ctrl_replace(काष्ठा v4l2_event *old, स्थिर काष्ठा v4l2_event *new)
अणु
	u32 old_changes = old->u.ctrl.changes;

	old->u.ctrl = new->u.ctrl;
	old->u.ctrl.changes |= old_changes;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_replace);

व्योम v4l2_ctrl_merge(स्थिर काष्ठा v4l2_event *old, काष्ठा v4l2_event *new)
अणु
	new->u.ctrl.changes |= old->u.ctrl.changes;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_merge);

स्थिर काष्ठा v4l2_subscribed_event_ops v4l2_ctrl_sub_ev_ops = अणु
	.add = v4l2_ctrl_add_event,
	.del = v4l2_ctrl_del_event,
	.replace = v4l2_ctrl_replace,
	.merge = v4l2_ctrl_merge,
पूर्ण;
EXPORT_SYMBOL(v4l2_ctrl_sub_ev_ops);

पूर्णांक v4l2_ctrl_log_status(काष्ठा file *file, व्योम *fh)
अणु
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा v4l2_fh *vfh = file->निजी_data;

	अगर (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) && vfd->v4l2_dev)
		v4l2_ctrl_handler_log_status(vfh->ctrl_handler,
			vfd->v4l2_dev->name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_log_status);

पूर्णांक v4l2_ctrl_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type == V4L2_EVENT_CTRL)
		वापस v4l2_event_subscribe(fh, sub, 0, &v4l2_ctrl_sub_ev_ops);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_subscribe_event);

पूर्णांक v4l2_ctrl_subdev_subscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				     काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (!sd->ctrl_handler)
		वापस -EINVAL;
	वापस v4l2_ctrl_subscribe_event(fh, sub);
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_subdev_subscribe_event);

__poll_t v4l2_ctrl_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;

	poll_रुको(file, &fh->रुको, रुको);
	अगर (v4l2_event_pending(fh))
		वापस EPOLLPRI;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_poll);

पूर्णांक v4l2_ctrl_new_fwnode_properties(काष्ठा v4l2_ctrl_handler *hdl,
				    स्थिर काष्ठा v4l2_ctrl_ops *ctrl_ops,
				    स्थिर काष्ठा v4l2_fwnode_device_properties *p)
अणु
	अगर (p->orientation != V4L2_FWNODE_PROPERTY_UNSET) अणु
		u32 orientation_ctrl;

		चयन (p->orientation) अणु
		हाल V4L2_FWNODE_ORIENTATION_FRONT:
			orientation_ctrl = V4L2_CAMERA_ORIENTATION_FRONT;
			अवरोध;
		हाल V4L2_FWNODE_ORIENTATION_BACK:
			orientation_ctrl = V4L2_CAMERA_ORIENTATION_BACK;
			अवरोध;
		हाल V4L2_FWNODE_ORIENTATION_EXTERNAL:
			orientation_ctrl = V4L2_CAMERA_ORIENTATION_EXTERNAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (!v4l2_ctrl_new_std_menu(hdl, ctrl_ops,
					    V4L2_CID_CAMERA_ORIENTATION,
					    V4L2_CAMERA_ORIENTATION_EXTERNAL, 0,
					    orientation_ctrl))
			वापस hdl->error;
	पूर्ण

	अगर (p->rotation != V4L2_FWNODE_PROPERTY_UNSET) अणु
		अगर (!v4l2_ctrl_new_std(hdl, ctrl_ops,
				       V4L2_CID_CAMERA_SENSOR_ROTATION,
				       p->rotation, p->rotation, 1,
				       p->rotation))
			वापस hdl->error;
	पूर्ण

	वापस hdl->error;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_new_fwnode_properties);
