<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cx2341x - generic code क्रम cx23415/6/8 based devices
 *
 * Copyright (C) 2006 Hans Verkuil <hverkuil@xs4all.nl>
 */


#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <media/tuner.h>
#समावेश <media/drv-पूर्णांकf/cx2341x.h>
#समावेश <media/v4l2-common.h>

MODULE_DESCRIPTION("cx23415/6/8 driver");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

/********************** COMMON CODE *********************/

/* definitions क्रम audio properties bits 29-28 */
#घोषणा CX2341X_AUDIO_ENCODING_METHOD_MPEG	0
#घोषणा CX2341X_AUDIO_ENCODING_METHOD_AC3	1
#घोषणा CX2341X_AUDIO_ENCODING_METHOD_LPCM	2

अटल स्थिर अक्षर *cx2341x_get_name(u32 id)
अणु
	चयन (id) अणु
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		वापस "Spatial Filter Mode";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		वापस "Spatial Filter";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		वापस "Spatial Luma Filter Type";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		वापस "Spatial Chroma Filter Type";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		वापस "Temporal Filter Mode";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		वापस "Temporal Filter";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		वापस "Median Filter Type";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		वापस "Median Luma Filter Maximum";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		वापस "Median Luma Filter Minimum";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		वापस "Median Chroma Filter Maximum";
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		वापस "Median Chroma Filter Minimum";
	हाल V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		वापस "Insert Navigation Packets";
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर **cx2341x_get_menu(u32 id)
अणु
	अटल स्थिर अक्षर *cx2341x_video_spatial_filter_mode_menu[] = अणु
		"Manual",
		"Auto",
		शून्य
	पूर्ण;

	अटल स्थिर अक्षर *cx2341x_video_luma_spatial_filter_type_menu[] = अणु
		"Off",
		"1D Horizontal",
		"1D Vertical",
		"2D H/V Separable",
		"2D Symmetric non-separable",
		शून्य
	पूर्ण;

	अटल स्थिर अक्षर *cx2341x_video_chroma_spatial_filter_type_menu[] = अणु
		"Off",
		"1D Horizontal",
		शून्य
	पूर्ण;

	अटल स्थिर अक्षर *cx2341x_video_temporal_filter_mode_menu[] = अणु
		"Manual",
		"Auto",
		शून्य
	पूर्ण;

	अटल स्थिर अक्षर *cx2341x_video_median_filter_type_menu[] = अणु
		"Off",
		"Horizontal",
		"Vertical",
		"Horizontal/Vertical",
		"Diagonal",
		शून्य
	पूर्ण;

	चयन (id) अणु
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		वापस cx2341x_video_spatial_filter_mode_menu;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		वापस cx2341x_video_luma_spatial_filter_type_menu;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		वापस cx2341x_video_chroma_spatial_filter_type_menu;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		वापस cx2341x_video_temporal_filter_mode_menu;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		वापस cx2341x_video_median_filter_type_menu;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम cx2341x_ctrl_fill(u32 id, स्थिर अक्षर **name, क्रमागत v4l2_ctrl_type *type,
		    s32 *min, s32 *max, s32 *step, s32 *def, u32 *flags)
अणु
	*name = cx2341x_get_name(id);
	*flags = 0;

	चयन (id) अणु
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		*type = V4L2_CTRL_TYPE_MENU;
		*min = 0;
		*step = 0;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		*type = V4L2_CTRL_TYPE_BOOLEAN;
		*min = 0;
		*max = *step = 1;
		अवरोध;
	शेष:
		*type = V4L2_CTRL_TYPE_INTEGER;
		अवरोध;
	पूर्ण
	चयन (id) अणु
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		*flags |= V4L2_CTRL_FLAG_UPDATE;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		*flags |= V4L2_CTRL_FLAG_SLIDER;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ENCODING:
		*flags |= V4L2_CTRL_FLAG_READ_ONLY;
		अवरोध;
	पूर्ण
पूर्ण


/********************** OLD CODE *********************/

/* Must be sorted from low to high control ID! */
स्थिर u32 cx2341x_mpeg_ctrls[] = अणु
	V4L2_CID_CODEC_CLASS,
	V4L2_CID_MPEG_STREAM_TYPE,
	V4L2_CID_MPEG_STREAM_VBI_FMT,
	V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ,
	V4L2_CID_MPEG_AUDIO_ENCODING,
	V4L2_CID_MPEG_AUDIO_L2_BITRATE,
	V4L2_CID_MPEG_AUDIO_MODE,
	V4L2_CID_MPEG_AUDIO_MODE_EXTENSION,
	V4L2_CID_MPEG_AUDIO_EMPHASIS,
	V4L2_CID_MPEG_AUDIO_CRC,
	V4L2_CID_MPEG_AUDIO_MUTE,
	V4L2_CID_MPEG_AUDIO_AC3_BITRATE,
	V4L2_CID_MPEG_VIDEO_ENCODING,
	V4L2_CID_MPEG_VIDEO_ASPECT,
	V4L2_CID_MPEG_VIDEO_B_FRAMES,
	V4L2_CID_MPEG_VIDEO_GOP_SIZE,
	V4L2_CID_MPEG_VIDEO_GOP_CLOSURE,
	V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
	V4L2_CID_MPEG_VIDEO_BITRATE,
	V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
	V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION,
	V4L2_CID_MPEG_VIDEO_MUTE,
	V4L2_CID_MPEG_VIDEO_MUTE_YUV,
	V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE,
	V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER,
	V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE,
	V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE,
	V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE,
	V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER,
	V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE,
	V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM,
	V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP,
	V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM,
	V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP,
	V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS,
	0
पूर्ण;
EXPORT_SYMBOL(cx2341x_mpeg_ctrls);

अटल स्थिर काष्ठा cx2341x_mpeg_params शेष_params = अणु
	/* misc */
	.capabilities = 0,
	.port = CX2341X_PORT_MEMORY,
	.width = 720,
	.height = 480,
	.is_50hz = 0,

	/* stream */
	.stream_type = V4L2_MPEG_STREAM_TYPE_MPEG2_PS,
	.stream_vbi_fmt = V4L2_MPEG_STREAM_VBI_FMT_NONE,
	.stream_insert_nav_packets = 0,

	/* audio */
	.audio_sampling_freq = V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000,
	.audio_encoding = V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
	.audio_l2_bitrate = V4L2_MPEG_AUDIO_L2_BITRATE_224K,
	.audio_ac3_bitrate = V4L2_MPEG_AUDIO_AC3_BITRATE_224K,
	.audio_mode = V4L2_MPEG_AUDIO_MODE_STEREO,
	.audio_mode_extension = V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4,
	.audio_emphasis = V4L2_MPEG_AUDIO_EMPHASIS_NONE,
	.audio_crc = V4L2_MPEG_AUDIO_CRC_NONE,
	.audio_mute = 0,

	/* video */
	.video_encoding = V4L2_MPEG_VIDEO_ENCODING_MPEG_2,
	.video_aspect = V4L2_MPEG_VIDEO_ASPECT_4x3,
	.video_b_frames = 2,
	.video_gop_size = 12,
	.video_gop_closure = 1,
	.video_bitrate_mode = V4L2_MPEG_VIDEO_BITRATE_MODE_VBR,
	.video_bitrate = 6000000,
	.video_bitrate_peak = 8000000,
	.video_temporal_decimation = 0,
	.video_mute = 0,
	.video_mute_yuv = 0x008080,  /* YCbCr value क्रम black */

	/* encoding filters */
	.video_spatial_filter_mode =
		V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL,
	.video_spatial_filter = 0,
	.video_luma_spatial_filter_type =
		V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_HOR,
	.video_chroma_spatial_filter_type =
		V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR,
	.video_temporal_filter_mode =
		V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL,
	.video_temporal_filter = 8,
	.video_median_filter_type =
		V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF,
	.video_luma_median_filter_top = 255,
	.video_luma_median_filter_bottom = 0,
	.video_chroma_median_filter_top = 255,
	.video_chroma_median_filter_bottom = 0,
पूर्ण;
/* Map the control ID to the correct field in the cx2341x_mpeg_params
   काष्ठा. Return -EINVAL अगर the ID is unknown, अन्यथा वापस 0. */
अटल पूर्णांक cx2341x_get_ctrl(स्थिर काष्ठा cx2341x_mpeg_params *params,
		काष्ठा v4l2_ext_control *ctrl)
अणु
	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		ctrl->value = params->audio_sampling_freq;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
		ctrl->value = params->audio_encoding;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		ctrl->value = params->audio_l2_bitrate;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		ctrl->value = params->audio_ac3_bitrate;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_MODE:
		ctrl->value = params->audio_mode;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		ctrl->value = params->audio_mode_extension;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_EMPHASIS:
		ctrl->value = params->audio_emphasis;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_CRC:
		ctrl->value = params->audio_crc;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_MUTE:
		ctrl->value = params->audio_mute;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ENCODING:
		ctrl->value = params->video_encoding;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		ctrl->value = params->video_aspect;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
		ctrl->value = params->video_b_frames;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctrl->value = params->video_gop_size;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		ctrl->value = params->video_gop_closure;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctrl->value = params->video_bitrate_mode;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		ctrl->value = params->video_bitrate;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		ctrl->value = params->video_bitrate_peak;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		ctrl->value = params->video_temporal_decimation;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MUTE:
		ctrl->value = params->video_mute;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MUTE_YUV:
		ctrl->value = params->video_mute_yuv;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		ctrl->value = params->stream_type;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_VBI_FMT:
		ctrl->value = params->stream_vbi_fmt;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		ctrl->value = params->video_spatial_filter_mode;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		ctrl->value = params->video_spatial_filter;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		ctrl->value = params->video_luma_spatial_filter_type;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		ctrl->value = params->video_chroma_spatial_filter_type;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		ctrl->value = params->video_temporal_filter_mode;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		ctrl->value = params->video_temporal_filter;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		ctrl->value = params->video_median_filter_type;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		ctrl->value = params->video_luma_median_filter_top;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		ctrl->value = params->video_luma_median_filter_bottom;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		ctrl->value = params->video_chroma_median_filter_top;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		ctrl->value = params->video_chroma_median_filter_bottom;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		ctrl->value = params->stream_insert_nav_packets;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Map the control ID to the correct field in the cx2341x_mpeg_params
   काष्ठा. Return -EINVAL अगर the ID is unknown, अन्यथा वापस 0. */
अटल पूर्णांक cx2341x_set_ctrl(काष्ठा cx2341x_mpeg_params *params, पूर्णांक busy,
		काष्ठा v4l2_ext_control *ctrl)
अणु
	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		अगर (busy)
			वापस -EBUSY;
		params->audio_sampling_freq = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
		अगर (busy)
			वापस -EBUSY;
		अगर (params->capabilities & CX2341X_CAP_HAS_AC3)
			अगर (ctrl->value != V4L2_MPEG_AUDIO_ENCODING_LAYER_2 &&
			    ctrl->value != V4L2_MPEG_AUDIO_ENCODING_AC3)
				वापस -दुस्फल;
		params->audio_encoding = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		अगर (busy)
			वापस -EBUSY;
		params->audio_l2_bitrate = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		अगर (busy)
			वापस -EBUSY;
		अगर (!(params->capabilities & CX2341X_CAP_HAS_AC3))
			वापस -EINVAL;
		params->audio_ac3_bitrate = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_MODE:
		params->audio_mode = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		params->audio_mode_extension = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_EMPHASIS:
		params->audio_emphasis = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_CRC:
		params->audio_crc = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_MUTE:
		params->audio_mute = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		params->video_aspect = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES: अणु
		पूर्णांक b = ctrl->value + 1;
		पूर्णांक gop = params->video_gop_size;
		params->video_b_frames = ctrl->value;
		params->video_gop_size = b * ((gop + b - 1) / b);
		/* Max GOP size = 34 */
		जबतक (params->video_gop_size > 34)
			params->video_gop_size -= b;
		अवरोध;
	पूर्ण
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE: अणु
		पूर्णांक b = params->video_b_frames + 1;
		पूर्णांक gop = ctrl->value;
		params->video_gop_size = b * ((gop + b - 1) / b);
		/* Max GOP size = 34 */
		जबतक (params->video_gop_size > 34)
			params->video_gop_size -= b;
		ctrl->value = params->video_gop_size;
		अवरोध;
	पूर्ण
	हाल V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		params->video_gop_closure = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		अगर (busy)
			वापस -EBUSY;
		/* MPEG-1 only allows CBR */
		अगर (params->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1 &&
		    ctrl->value != V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
			वापस -EINVAL;
		params->video_bitrate_mode = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		अगर (busy)
			वापस -EBUSY;
		params->video_bitrate = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		अगर (busy)
			वापस -EBUSY;
		params->video_bitrate_peak = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		params->video_temporal_decimation = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MUTE:
		params->video_mute = (ctrl->value != 0);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MUTE_YUV:
		params->video_mute_yuv = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		अगर (busy)
			वापस -EBUSY;
		params->stream_type = ctrl->value;
		params->video_encoding =
		    (params->stream_type == V4L2_MPEG_STREAM_TYPE_MPEG1_SS ||
		     params->stream_type == V4L2_MPEG_STREAM_TYPE_MPEG1_VCD) ?
			V4L2_MPEG_VIDEO_ENCODING_MPEG_1 :
			V4L2_MPEG_VIDEO_ENCODING_MPEG_2;
		अगर (params->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
			/* MPEG-1 implies CBR */
			params->video_bitrate_mode =
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_VBI_FMT:
		params->stream_vbi_fmt = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		params->video_spatial_filter_mode = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		params->video_spatial_filter = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		params->video_luma_spatial_filter_type = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		params->video_chroma_spatial_filter_type = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		params->video_temporal_filter_mode = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		params->video_temporal_filter = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		params->video_median_filter_type = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		params->video_luma_median_filter_top = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		params->video_luma_median_filter_bottom = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		params->video_chroma_median_filter_top = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		params->video_chroma_median_filter_bottom = ctrl->value;
		अवरोध;
	हाल V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		params->stream_insert_nav_packets = ctrl->value;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx2341x_ctrl_query_fill(काष्ठा v4l2_queryctrl *qctrl,
				   s32 min, s32 max, s32 step, s32 def)
अणु
	स्थिर अक्षर *name;

	चयन (qctrl->id) अणु
	/* MPEG controls */
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
	हाल V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		cx2341x_ctrl_fill(qctrl->id, &name, &qctrl->type,
				&min, &max, &step, &def, &qctrl->flags);
		qctrl->minimum = min;
		qctrl->maximum = max;
		qctrl->step = step;
		qctrl->शेष_value = def;
		qctrl->reserved[0] = qctrl->reserved[1] = 0;
		strscpy(qctrl->name, name, माप(qctrl->name));
		वापस 0;

	शेष:
		वापस v4l2_ctrl_query_fill(qctrl, min, max, step, def);
	पूर्ण
पूर्ण

पूर्णांक cx2341x_ctrl_query(स्थिर काष्ठा cx2341x_mpeg_params *params,
		       काष्ठा v4l2_queryctrl *qctrl)
अणु
	पूर्णांक err;

	चयन (qctrl->id) अणु
	हाल V4L2_CID_CODEC_CLASS:
		वापस v4l2_ctrl_query_fill(qctrl, 0, 0, 0, 0);
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		वापस v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_STREAM_TYPE_MPEG2_PS,
				V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD, 1,
				V4L2_MPEG_STREAM_TYPE_MPEG2_PS);

	हाल V4L2_CID_MPEG_STREAM_VBI_FMT:
		अगर (params->capabilities & CX2341X_CAP_HAS_SLICED_VBI)
			वापस v4l2_ctrl_query_fill(qctrl,
					V4L2_MPEG_STREAM_VBI_FMT_NONE,
					V4L2_MPEG_STREAM_VBI_FMT_IVTV, 1,
					V4L2_MPEG_STREAM_VBI_FMT_NONE);
		वापस cx2341x_ctrl_query_fill(qctrl,
				V4L2_MPEG_STREAM_VBI_FMT_NONE,
				V4L2_MPEG_STREAM_VBI_FMT_NONE, 1,
				शेष_params.stream_vbi_fmt);

	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		वापस v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000, 1,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000);

	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
		अगर (params->capabilities & CX2341X_CAP_HAS_AC3) अणु
			/*
			 * The state of L2 & AC3 bitrate controls can change
			 * when this control changes, but v4l2_ctrl_query_fill()
			 * alपढ़ोy sets V4L2_CTRL_FLAG_UPDATE क्रम
			 * V4L2_CID_MPEG_AUDIO_ENCODING, so we करोn't here.
			 */
			वापस v4l2_ctrl_query_fill(qctrl,
					V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
					V4L2_MPEG_AUDIO_ENCODING_AC3, 1,
					शेष_params.audio_encoding);
		पूर्ण

		वापस v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
				V4L2_MPEG_AUDIO_ENCODING_LAYER_2, 1,
				शेष_params.audio_encoding);

	हाल V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_L2_BITRATE_192K,
				V4L2_MPEG_AUDIO_L2_BITRATE_384K, 1,
				शेष_params.audio_l2_bitrate);
		अगर (err)
			वापस err;
		अगर (params->capabilities & CX2341X_CAP_HAS_AC3 &&
		    params->audio_encoding != V4L2_MPEG_AUDIO_ENCODING_LAYER_2)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_AUDIO_MODE:
		वापस v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_MODE_STEREO,
				V4L2_MPEG_AUDIO_MODE_MONO, 1,
				V4L2_MPEG_AUDIO_MODE_STEREO);

	हाल V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4,
				V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16, 1,
				V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4);
		अगर (err == 0 &&
		    params->audio_mode != V4L2_MPEG_AUDIO_MODE_JOINT_STEREO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस err;

	हाल V4L2_CID_MPEG_AUDIO_EMPHASIS:
		वापस v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_EMPHASIS_NONE,
				V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17, 1,
				V4L2_MPEG_AUDIO_EMPHASIS_NONE);

	हाल V4L2_CID_MPEG_AUDIO_CRC:
		वापस v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_CRC_NONE,
				V4L2_MPEG_AUDIO_CRC_CRC16, 1,
				V4L2_MPEG_AUDIO_CRC_NONE);

	हाल V4L2_CID_MPEG_AUDIO_MUTE:
		वापस v4l2_ctrl_query_fill(qctrl, 0, 1, 1, 0);

	हाल V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_AC3_BITRATE_48K,
				V4L2_MPEG_AUDIO_AC3_BITRATE_448K, 1,
				शेष_params.audio_ac3_bitrate);
		अगर (err)
			वापस err;
		अगर (params->capabilities & CX2341X_CAP_HAS_AC3) अणु
			अगर (params->audio_encoding !=
						   V4L2_MPEG_AUDIO_ENCODING_AC3)
				qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		पूर्ण अन्यथा
			qctrl->flags |= V4L2_CTRL_FLAG_DISABLED;
		वापस 0;

	हाल V4L2_CID_MPEG_VIDEO_ENCODING:
		/* this setting is पढ़ो-only क्रम the cx2341x since the
		   V4L2_CID_MPEG_STREAM_TYPE really determines the
		   MPEG-1/2 setting */
		err = v4l2_ctrl_query_fill(qctrl,
					   V4L2_MPEG_VIDEO_ENCODING_MPEG_1,
					   V4L2_MPEG_VIDEO_ENCODING_MPEG_2, 1,
					   V4L2_MPEG_VIDEO_ENCODING_MPEG_2);
		अगर (err == 0)
			qctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
		वापस err;

	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		वापस v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_VIDEO_ASPECT_1x1,
				V4L2_MPEG_VIDEO_ASPECT_221x100, 1,
				V4L2_MPEG_VIDEO_ASPECT_4x3);

	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
		वापस v4l2_ctrl_query_fill(qctrl, 0, 33, 1, 2);

	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		वापस v4l2_ctrl_query_fill(qctrl, 1, 34, 1,
				params->is_50hz ? 12 : 15);

	हाल V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		वापस v4l2_ctrl_query_fill(qctrl, 0, 1, 1, 1);

	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_VIDEO_BITRATE_MODE_VBR,
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 1,
				V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
		अगर (err == 0 &&
		    params->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस err;

	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		वापस v4l2_ctrl_query_fill(qctrl, 0, 27000000, 1, 6000000);

	हाल V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		err = v4l2_ctrl_query_fill(qctrl, 0, 27000000, 1, 8000000);
		अगर (err == 0 &&
		    params->video_bitrate_mode ==
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस err;

	हाल V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		वापस v4l2_ctrl_query_fill(qctrl, 0, 255, 1, 0);

	हाल V4L2_CID_MPEG_VIDEO_MUTE:
		वापस v4l2_ctrl_query_fill(qctrl, 0, 1, 1, 0);

	हाल V4L2_CID_MPEG_VIDEO_MUTE_YUV:  /* Init YUV (really YCbCr) to black */
		वापस v4l2_ctrl_query_fill(qctrl, 0, 0xffffff, 1, 0x008080);

	/* CX23415/6 specअगरic */
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		वापस cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL,
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO, 1,
			शेष_params.video_spatial_filter_mode);

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		cx2341x_ctrl_query_fill(qctrl, 0, 15, 1,
				शेष_params.video_spatial_filter);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		अगर (params->video_spatial_filter_mode ==
			    V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_OFF,
			V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_SYM_NON_SEPARABLE,
			1,
			शेष_params.video_luma_spatial_filter_type);
		अगर (params->video_spatial_filter_mode ==
			    V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		cx2341x_ctrl_query_fill(qctrl,
		    V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_OFF,
		    V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR,
		    1,
		    शेष_params.video_chroma_spatial_filter_type);
		अगर (params->video_spatial_filter_mode ==
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		वापस cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL,
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO, 1,
			शेष_params.video_temporal_filter_mode);

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		cx2341x_ctrl_query_fill(qctrl, 0, 31, 1,
				शेष_params.video_temporal_filter);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		अगर (params->video_temporal_filter_mode ==
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		वापस cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF,
			V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_DIAG, 1,
			शेष_params.video_median_filter_type);

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
				शेष_params.video_luma_median_filter_top);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		अगर (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
				शेष_params.video_luma_median_filter_bottom);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		अगर (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
				शेष_params.video_chroma_median_filter_top);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		अगर (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
			शेष_params.video_chroma_median_filter_bottom);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		अगर (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		वापस 0;

	हाल V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		वापस cx2341x_ctrl_query_fill(qctrl, 0, 1, 1,
				शेष_params.stream_insert_nav_packets);

	शेष:
		वापस -EINVAL;

	पूर्ण
पूर्ण
EXPORT_SYMBOL(cx2341x_ctrl_query);

स्थिर अक्षर * स्थिर *cx2341x_ctrl_get_menu(स्थिर काष्ठा cx2341x_mpeg_params *p, u32 id)
अणु
	अटल स्थिर अक्षर * स्थिर mpeg_stream_type_without_ts[] = अणु
		"MPEG-2 Program Stream",
		"",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		शून्य
	पूर्ण;

	अटल स्थिर अक्षर *mpeg_stream_type_with_ts[] = अणु
		"MPEG-2 Program Stream",
		"MPEG-2 Transport Stream",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		शून्य
	पूर्ण;

	अटल स्थिर अक्षर *mpeg_audio_encoding_l2_ac3[] = अणु
		"",
		"MPEG-1/2 Layer II",
		"",
		"",
		"AC-3",
		शून्य
	पूर्ण;

	चयन (id) अणु
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		वापस (p->capabilities & CX2341X_CAP_HAS_TS) ?
			mpeg_stream_type_with_ts : mpeg_stream_type_without_ts;
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
		वापस (p->capabilities & CX2341X_CAP_HAS_AC3) ?
			mpeg_audio_encoding_l2_ac3 : v4l2_ctrl_get_menu(id);
	हाल V4L2_CID_MPEG_AUDIO_L1_BITRATE:
	हाल V4L2_CID_MPEG_AUDIO_L3_BITRATE:
		वापस शून्य;
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	हाल V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		वापस cx2341x_get_menu(id);
	शेष:
		वापस v4l2_ctrl_get_menu(id);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cx2341x_ctrl_get_menu);

अटल व्योम cx2341x_calc_audio_properties(काष्ठा cx2341x_mpeg_params *params)
अणु
	params->audio_properties =
		(params->audio_sampling_freq << 0) |
		(params->audio_mode << 8) |
		(params->audio_mode_extension << 10) |
		(((params->audio_emphasis == V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17)
		  ? 3 : params->audio_emphasis) << 12) |
		(params->audio_crc << 14);

	अगर ((params->capabilities & CX2341X_CAP_HAS_AC3) &&
	    params->audio_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3) अणु
		params->audio_properties |=
			/* Not sure अगर this MPEG Layer II setting is required */
			((3 - V4L2_MPEG_AUDIO_ENCODING_LAYER_2) << 2) |
			(params->audio_ac3_bitrate << 4) |
			(CX2341X_AUDIO_ENCODING_METHOD_AC3 << 28);
	पूर्ण अन्यथा अणु
		/* Assuming MPEG Layer II */
		params->audio_properties |=
			((3 - params->audio_encoding) << 2) |
			((1 + params->audio_l2_bitrate) << 4);
	पूर्ण
पूर्ण

/* Check क्रम correctness of the ctrl's value based on the data from
   काष्ठा v4l2_queryctrl and the available menu items. Note that
   menu_items may be शून्य, in that हाल it is ignored. */
अटल पूर्णांक v4l2_ctrl_check(काष्ठा v4l2_ext_control *ctrl, काष्ठा v4l2_queryctrl *qctrl,
		स्थिर अक्षर * स्थिर *menu_items)
अणु
	अगर (qctrl->flags & V4L2_CTRL_FLAG_DISABLED)
		वापस -EINVAL;
	अगर (qctrl->flags & V4L2_CTRL_FLAG_GRABBED)
		वापस -EBUSY;
	अगर (qctrl->type == V4L2_CTRL_TYPE_STRING)
		वापस 0;
	अगर (qctrl->type == V4L2_CTRL_TYPE_BUTTON ||
	    qctrl->type == V4L2_CTRL_TYPE_INTEGER64 ||
	    qctrl->type == V4L2_CTRL_TYPE_CTRL_CLASS)
		वापस 0;
	अगर (ctrl->value < qctrl->minimum || ctrl->value > qctrl->maximum)
		वापस -दुस्फल;
	अगर (qctrl->type == V4L2_CTRL_TYPE_MENU && menu_items != शून्य) अणु
		अगर (menu_items[ctrl->value] == शून्य ||
		    menu_items[ctrl->value][0] == '\0')
			वापस -EINVAL;
	पूर्ण
	अगर (qctrl->type == V4L2_CTRL_TYPE_BITMASK &&
			(ctrl->value & ~qctrl->maximum))
		वापस -दुस्फल;
	वापस 0;
पूर्ण

पूर्णांक cx2341x_ext_ctrls(काष्ठा cx2341x_mpeg_params *params, पूर्णांक busy,
		  काष्ठा v4l2_ext_controls *ctrls, अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (cmd == VIDIOC_G_EXT_CTRLS) अणु
		क्रम (i = 0; i < ctrls->count; i++) अणु
			काष्ठा v4l2_ext_control *ctrl = ctrls->controls + i;

			err = cx2341x_get_ctrl(params, ctrl);
			अगर (err) अणु
				ctrls->error_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण
		वापस err;
	पूर्ण
	क्रम (i = 0; i < ctrls->count; i++) अणु
		काष्ठा v4l2_ext_control *ctrl = ctrls->controls + i;
		काष्ठा v4l2_queryctrl qctrl;
		स्थिर अक्षर * स्थिर *menu_items = शून्य;

		qctrl.id = ctrl->id;
		err = cx2341x_ctrl_query(params, &qctrl);
		अगर (err)
			अवरोध;
		अगर (qctrl.type == V4L2_CTRL_TYPE_MENU)
			menu_items = cx2341x_ctrl_get_menu(params, qctrl.id);
		err = v4l2_ctrl_check(ctrl, &qctrl, menu_items);
		अगर (err)
			अवरोध;
		err = cx2341x_set_ctrl(params, busy, ctrl);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (err == 0 &&
	    params->video_bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
	    params->video_bitrate_peak < params->video_bitrate) अणु
		err = -दुस्फल;
		ctrls->error_idx = ctrls->count;
	पूर्ण
	अगर (err)
		ctrls->error_idx = i;
	अन्यथा
		cx2341x_calc_audio_properties(params);
	वापस err;
पूर्ण
EXPORT_SYMBOL(cx2341x_ext_ctrls);

व्योम cx2341x_fill_शेषs(काष्ठा cx2341x_mpeg_params *p)
अणु
	*p = शेष_params;
	cx2341x_calc_audio_properties(p);
पूर्ण
EXPORT_SYMBOL(cx2341x_fill_शेषs);

अटल पूर्णांक cx2341x_api(व्योम *priv, cx2341x_mbox_func func,
		       u32 cmd, पूर्णांक args, ...)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	बहु_सूची vargs;
	पूर्णांक i;

	बहु_शुरू(vargs, args);

	क्रम (i = 0; i < args; i++)
		data[i] = बहु_तर्क(vargs, पूर्णांक);
	बहु_पूर्ण(vargs);
	वापस func(priv, cmd, args, 0, data);
पूर्ण

#घोषणा CMP_FIELD(__old, __new, __field) (__old->__field != __new->__field)

पूर्णांक cx2341x_update(व्योम *priv, cx2341x_mbox_func func,
		   स्थिर काष्ठा cx2341x_mpeg_params *old,
		   स्थिर काष्ठा cx2341x_mpeg_params *new)
अणु
	अटल पूर्णांक mpeg_stream_type[] = अणु
		0,	/* MPEG-2 PS */
		1,	/* MPEG-2 TS */
		2,	/* MPEG-1 SS */
		14,	/* DVD */
		11,	/* VCD */
		12,	/* SVCD */
	पूर्ण;
	पूर्णांक err;

	cx2341x_api(priv, func, CX2341X_ENC_SET_OUTPUT_PORT, 2, new->port, 0);

	अगर (!old ||
	    CMP_FIELD(old, new, is_50hz)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_FRAME_RATE, 1,
				  new->is_50hz);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!old ||
	    CMP_FIELD(old, new, width) ||
	    CMP_FIELD(old, new, height) ||
	    CMP_FIELD(old, new, video_encoding)) अणु
		u16 w = new->width;
		u16 h = new->height;

		अगर (new->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1) अणु
			w /= 2;
			h /= 2;
		पूर्ण
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_FRAME_SIZE, 2,
				  h, w);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, stream_type)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_STREAM_TYPE, 1,
				  mpeg_stream_type[new->stream_type]);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_aspect)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_ASPECT_RATIO, 1,
				  1 + new->video_aspect);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_b_frames) ||
	    CMP_FIELD(old, new, video_gop_size)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_GOP_PROPERTIES, 2,
				  new->video_gop_size, new->video_b_frames + 1);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_gop_closure)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_GOP_CLOSURE, 1,
				  new->video_gop_closure);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, audio_properties)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_AUDIO_PROPERTIES,
				  1, new->audio_properties);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, audio_mute)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_MUTE_AUDIO, 1,
				  new->audio_mute);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_bitrate_mode) ||
	    CMP_FIELD(old, new, video_bitrate) ||
	    CMP_FIELD(old, new, video_bitrate_peak)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_BIT_RATE, 5,
				  new->video_bitrate_mode, new->video_bitrate,
				  new->video_bitrate_peak / 400, 0, 0);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_spatial_filter_mode) ||
	    CMP_FIELD(old, new, video_temporal_filter_mode) ||
	    CMP_FIELD(old, new, video_median_filter_type)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_DNR_FILTER_MODE,
				  2,
				  new->video_spatial_filter_mode |
					(new->video_temporal_filter_mode << 1),
				  new->video_median_filter_type);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_luma_median_filter_bottom) ||
	    CMP_FIELD(old, new, video_luma_median_filter_top) ||
	    CMP_FIELD(old, new, video_chroma_median_filter_bottom) ||
	    CMP_FIELD(old, new, video_chroma_median_filter_top)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_CORING_LEVELS, 4,
				  new->video_luma_median_filter_bottom,
				  new->video_luma_median_filter_top,
				  new->video_chroma_median_filter_bottom,
				  new->video_chroma_median_filter_top);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_luma_spatial_filter_type) ||
	    CMP_FIELD(old, new, video_chroma_spatial_filter_type)) अणु
		err = cx2341x_api(priv, func,
				  CX2341X_ENC_SET_SPATIAL_FILTER_TYPE,
				  2, new->video_luma_spatial_filter_type,
				  new->video_chroma_spatial_filter_type);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_spatial_filter) ||
	    CMP_FIELD(old, new, video_temporal_filter)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_DNR_FILTER_PROPS,
				  2, new->video_spatial_filter,
				  new->video_temporal_filter);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_temporal_decimation)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_SET_FRAME_DROP_RATE,
				  1, new->video_temporal_decimation);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, video_mute) ||
	    (new->video_mute && CMP_FIELD(old, new, video_mute_yuv))) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_MUTE_VIDEO, 1,
				  new->video_mute | (new->video_mute_yuv << 8));
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!old ||
	    CMP_FIELD(old, new, stream_insert_nav_packets)) अणु
		err = cx2341x_api(priv, func, CX2341X_ENC_MISC, 2,
				  7, new->stream_insert_nav_packets);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx2341x_update);

अटल स्थिर अक्षर *cx2341x_menu_item(स्थिर काष्ठा cx2341x_mpeg_params *p, u32 id)
अणु
	स्थिर अक्षर * स्थिर *menu = cx2341x_ctrl_get_menu(p, id);
	काष्ठा v4l2_ext_control ctrl;

	अगर (menu == शून्य)
		जाओ invalid;
	ctrl.id = id;
	अगर (cx2341x_get_ctrl(p, &ctrl))
		जाओ invalid;
	जबतक (ctrl.value-- && *menu) menu++;
	अगर (*menu == शून्य)
		जाओ invalid;
	वापस *menu;

invalid:
	वापस "<invalid>";
पूर्ण

व्योम cx2341x_log_status(स्थिर काष्ठा cx2341x_mpeg_params *p, स्थिर अक्षर *prefix)
अणु
	पूर्णांक is_mpeg1 = p->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1;

	/* Stream */
	prपूर्णांकk(KERN_INFO "%s: Stream: %s",
		prefix,
		cx2341x_menu_item(p, V4L2_CID_MPEG_STREAM_TYPE));
	अगर (p->stream_insert_nav_packets)
		prपूर्णांकk(KERN_CONT " (with navigation packets)");
	prपूर्णांकk(KERN_CONT "\n");
	prपूर्णांकk(KERN_INFO "%s: VBI Format: %s\n",
		prefix,
		cx2341x_menu_item(p, V4L2_CID_MPEG_STREAM_VBI_FMT));

	/* Video */
	prपूर्णांकk(KERN_INFO "%s: Video:  %dx%d, %d fps%s\n",
		prefix,
		p->width / (is_mpeg1 ? 2 : 1), p->height / (is_mpeg1 ? 2 : 1),
		p->is_50hz ? 25 : 30,
		(p->video_mute) ? " (muted)" : "");
	prपूर्णांकk(KERN_INFO "%s: Video:  %s, %s, %s, %d",
		prefix,
		cx2341x_menu_item(p, V4L2_CID_MPEG_VIDEO_ENCODING),
		cx2341x_menu_item(p, V4L2_CID_MPEG_VIDEO_ASPECT),
		cx2341x_menu_item(p, V4L2_CID_MPEG_VIDEO_BITRATE_MODE),
		p->video_bitrate);
	अगर (p->video_bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR)
		prपूर्णांकk(KERN_CONT ", Peak %d", p->video_bitrate_peak);
	prपूर्णांकk(KERN_CONT "\n");
	prपूर्णांकk(KERN_INFO
		"%s: Video:  GOP Size %d, %d B-Frames, %sGOP Closure\n",
		prefix,
		p->video_gop_size, p->video_b_frames,
		p->video_gop_closure ? "" : "No ");
	अगर (p->video_temporal_decimation)
		prपूर्णांकk(KERN_INFO "%s: Video: Temporal Decimation %d\n",
			prefix, p->video_temporal_decimation);

	/* Audio */
	prपूर्णांकk(KERN_INFO "%s: Audio:  %s, %s, %s, %s%s",
		prefix,
		cx2341x_menu_item(p, V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ),
		cx2341x_menu_item(p, V4L2_CID_MPEG_AUDIO_ENCODING),
		cx2341x_menu_item(p,
			   p->audio_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3
					      ? V4L2_CID_MPEG_AUDIO_AC3_BITRATE
					      : V4L2_CID_MPEG_AUDIO_L2_BITRATE),
		cx2341x_menu_item(p, V4L2_CID_MPEG_AUDIO_MODE),
		p->audio_mute ? " (muted)" : "");
	अगर (p->audio_mode == V4L2_MPEG_AUDIO_MODE_JOINT_STEREO)
		prपूर्णांकk(KERN_CONT ", %s", cx2341x_menu_item(p,
				V4L2_CID_MPEG_AUDIO_MODE_EXTENSION));
	prपूर्णांकk(KERN_CONT ", %s, %s\n",
		cx2341x_menu_item(p, V4L2_CID_MPEG_AUDIO_EMPHASIS),
		cx2341x_menu_item(p, V4L2_CID_MPEG_AUDIO_CRC));

	/* Encoding filters */
	prपूर्णांकk(KERN_INFO "%s: Spatial Filter:  %s, Luma %s, Chroma %s, %d\n",
		prefix,
		cx2341x_menu_item(p,
		    V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE),
		cx2341x_menu_item(p,
		    V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE),
		cx2341x_menu_item(p,
		    V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE),
		p->video_spatial_filter);

	prपूर्णांकk(KERN_INFO "%s: Temporal Filter: %s, %d\n",
		prefix,
		cx2341x_menu_item(p,
			V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE),
		p->video_temporal_filter);
	prपूर्णांकk(KERN_INFO
		"%s: Median Filter:   %s, Luma [%d, %d], Chroma [%d, %d]\n",
		prefix,
		cx2341x_menu_item(p,
			V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE),
		p->video_luma_median_filter_bottom,
		p->video_luma_median_filter_top,
		p->video_chroma_median_filter_bottom,
		p->video_chroma_median_filter_top);
पूर्ण
EXPORT_SYMBOL(cx2341x_log_status);



/********************** NEW CODE *********************/

अटल अंतरभूत काष्ठा cx2341x_handler *to_cxhdl(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा cx2341x_handler, hdl);
पूर्ण

अटल पूर्णांक cx2341x_hdl_api(काष्ठा cx2341x_handler *hdl,
		       u32 cmd, पूर्णांक args, ...)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	बहु_सूची vargs;
	पूर्णांक i;

	बहु_शुरू(vargs, args);

	क्रम (i = 0; i < args; i++)
		data[i] = बहु_तर्क(vargs, पूर्णांक);
	बहु_पूर्ण(vargs);
	वापस hdl->func(hdl->priv, cmd, args, 0, data);
पूर्ण

/* ctrl->handler->lock is held, so it is safe to access cur.val */
अटल अंतरभूत पूर्णांक cx2341x_neq(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस ctrl && ctrl->val != ctrl->cur.val;
पूर्ण

अटल पूर्णांक cx2341x_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा cx2341x_handler *hdl = to_cxhdl(ctrl);
	s32 val = ctrl->val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES: अणु
		/* video gop cluster */
		पूर्णांक b = val + 1;
		पूर्णांक gop = hdl->video_gop_size->val;

		gop = b * ((gop + b - 1) / b);

		/* Max GOP size = 34 */
		जबतक (gop > 34)
			gop -= b;
		hdl->video_gop_size->val = gop;
		अवरोध;
	पूर्ण

	हाल V4L2_CID_MPEG_STREAM_TYPE:
		/* stream type cluster */
		hdl->video_encoding->val =
		    (hdl->stream_type->val == V4L2_MPEG_STREAM_TYPE_MPEG1_SS ||
		     hdl->stream_type->val == V4L2_MPEG_STREAM_TYPE_MPEG1_VCD) ?
			V4L2_MPEG_VIDEO_ENCODING_MPEG_1 :
			V4L2_MPEG_VIDEO_ENCODING_MPEG_2;
		अगर (hdl->video_encoding->val == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
			/* MPEG-1 implies CBR */
			hdl->video_bitrate_mode->val =
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR;
		/* peak bitrate shall be >= normal bitrate */
		अगर (hdl->video_bitrate_mode->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
		    hdl->video_bitrate_peak->val < hdl->video_bitrate->val)
			hdl->video_bitrate_peak->val = hdl->video_bitrate->val;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx2341x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अटल स्थिर पूर्णांक mpeg_stream_type[] = अणु
		0,	/* MPEG-2 PS */
		1,	/* MPEG-2 TS */
		2,	/* MPEG-1 SS */
		14,	/* DVD */
		11,	/* VCD */
		12,	/* SVCD */
	पूर्ण;
	काष्ठा cx2341x_handler *hdl = to_cxhdl(ctrl);
	s32 val = ctrl->val;
	u32 props;
	पूर्णांक err;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_STREAM_VBI_FMT:
		अगर (hdl->ops && hdl->ops->s_stream_vbi_fmt)
			वापस hdl->ops->s_stream_vbi_fmt(hdl, val);
		वापस 0;

	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		वापस cx2341x_hdl_api(hdl,
			CX2341X_ENC_SET_ASPECT_RATIO, 1, val + 1);

	हाल V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		वापस cx2341x_hdl_api(hdl, CX2341X_ENC_SET_GOP_CLOSURE, 1, val);

	हाल V4L2_CID_MPEG_AUDIO_MUTE:
		वापस cx2341x_hdl_api(hdl, CX2341X_ENC_MUTE_AUDIO, 1, val);

	हाल V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		वापस cx2341x_hdl_api(hdl,
			CX2341X_ENC_SET_FRAME_DROP_RATE, 1, val);

	हाल V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		वापस cx2341x_hdl_api(hdl, CX2341X_ENC_MISC, 2, 7, val);

	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		/* audio properties cluster */
		props = (hdl->audio_sampling_freq->val << 0) |
			(hdl->audio_mode->val << 8) |
			(hdl->audio_mode_extension->val << 10) |
			(hdl->audio_crc->val << 14);
		अगर (hdl->audio_emphasis->val == V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17)
			props |= 3 << 12;
		अन्यथा
			props |= hdl->audio_emphasis->val << 12;

		अगर (hdl->audio_encoding->val == V4L2_MPEG_AUDIO_ENCODING_AC3) अणु
			props |=
#अगर 1
				/* Not sure अगर this MPEG Layer II setting is required */
				((3 - V4L2_MPEG_AUDIO_ENCODING_LAYER_2) << 2) |
#पूर्ण_अगर
				(hdl->audio_ac3_bitrate->val << 4) |
				(CX2341X_AUDIO_ENCODING_METHOD_AC3 << 28);
		पूर्ण अन्यथा अणु
			/* Assuming MPEG Layer II */
			props |=
				((3 - hdl->audio_encoding->val) << 2) |
				((1 + hdl->audio_l2_bitrate->val) << 4);
		पूर्ण
		err = cx2341x_hdl_api(hdl,
				CX2341X_ENC_SET_AUDIO_PROPERTIES, 1, props);
		अगर (err)
			वापस err;

		hdl->audio_properties = props;
		अगर (hdl->audio_ac3_bitrate) अणु
			पूर्णांक is_ac3 = hdl->audio_encoding->val ==
						V4L2_MPEG_AUDIO_ENCODING_AC3;

			v4l2_ctrl_activate(hdl->audio_ac3_bitrate, is_ac3);
			v4l2_ctrl_activate(hdl->audio_l2_bitrate, !is_ac3);
		पूर्ण
		v4l2_ctrl_activate(hdl->audio_mode_extension,
			hdl->audio_mode->val == V4L2_MPEG_AUDIO_MODE_JOINT_STEREO);
		अगर (cx2341x_neq(hdl->audio_sampling_freq) &&
		    hdl->ops && hdl->ops->s_audio_sampling_freq)
			वापस hdl->ops->s_audio_sampling_freq(hdl, hdl->audio_sampling_freq->val);
		अगर (cx2341x_neq(hdl->audio_mode) &&
		    hdl->ops && hdl->ops->s_audio_mode)
			वापस hdl->ops->s_audio_mode(hdl, hdl->audio_mode->val);
		वापस 0;

	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
		/* video gop cluster */
		वापस cx2341x_hdl_api(hdl, CX2341X_ENC_SET_GOP_PROPERTIES, 2,
				hdl->video_gop_size->val,
				hdl->video_b_frames->val + 1);

	हाल V4L2_CID_MPEG_STREAM_TYPE:
		/* stream type cluster */
		err = cx2341x_hdl_api(hdl,
			CX2341X_ENC_SET_STREAM_TYPE, 1, mpeg_stream_type[val]);
		अगर (err)
			वापस err;

		err = cx2341x_hdl_api(hdl, CX2341X_ENC_SET_BIT_RATE, 5,
				hdl->video_bitrate_mode->val,
				hdl->video_bitrate->val,
				hdl->video_bitrate_peak->val / 400, 0, 0);
		अगर (err)
			वापस err;

		v4l2_ctrl_activate(hdl->video_bitrate_mode,
			hdl->video_encoding->val != V4L2_MPEG_VIDEO_ENCODING_MPEG_1);
		v4l2_ctrl_activate(hdl->video_bitrate_peak,
			hdl->video_bitrate_mode->val != V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);
		अगर (cx2341x_neq(hdl->video_encoding) &&
		    hdl->ops && hdl->ops->s_video_encoding)
			वापस hdl->ops->s_video_encoding(hdl, hdl->video_encoding->val);
		वापस 0;

	हाल V4L2_CID_MPEG_VIDEO_MUTE:
		/* video mute cluster */
		वापस cx2341x_hdl_api(hdl, CX2341X_ENC_MUTE_VIDEO, 1,
				hdl->video_mute->val |
					(hdl->video_mute_yuv->val << 8));

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE: अणु
		पूर्णांक active_filter;

		/* video filter mode */
		err = cx2341x_hdl_api(hdl, CX2341X_ENC_SET_DNR_FILTER_MODE, 2,
				hdl->video_spatial_filter_mode->val |
					(hdl->video_temporal_filter_mode->val << 1),
				hdl->video_median_filter_type->val);
		अगर (err)
			वापस err;

		active_filter = hdl->video_spatial_filter_mode->val !=
				V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO;
		v4l2_ctrl_activate(hdl->video_spatial_filter, active_filter);
		v4l2_ctrl_activate(hdl->video_luma_spatial_filter_type, active_filter);
		v4l2_ctrl_activate(hdl->video_chroma_spatial_filter_type, active_filter);
		active_filter = hdl->video_temporal_filter_mode->val !=
				V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO;
		v4l2_ctrl_activate(hdl->video_temporal_filter, active_filter);
		active_filter = hdl->video_median_filter_type->val !=
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF;
		v4l2_ctrl_activate(hdl->video_luma_median_filter_bottom, active_filter);
		v4l2_ctrl_activate(hdl->video_luma_median_filter_top, active_filter);
		v4l2_ctrl_activate(hdl->video_chroma_median_filter_bottom, active_filter);
		v4l2_ctrl_activate(hdl->video_chroma_median_filter_top, active_filter);
		वापस 0;
	पूर्ण

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		/* video filter type cluster */
		वापस cx2341x_hdl_api(hdl,
				CX2341X_ENC_SET_SPATIAL_FILTER_TYPE, 2,
				hdl->video_luma_spatial_filter_type->val,
				hdl->video_chroma_spatial_filter_type->val);

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		/* video filter cluster */
		वापस cx2341x_hdl_api(hdl, CX2341X_ENC_SET_DNR_FILTER_PROPS, 2,
				hdl->video_spatial_filter->val,
				hdl->video_temporal_filter->val);

	हाल V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		/* video median cluster */
		वापस cx2341x_hdl_api(hdl, CX2341X_ENC_SET_CORING_LEVELS, 4,
				hdl->video_luma_median_filter_bottom->val,
				hdl->video_luma_median_filter_top->val,
				hdl->video_chroma_median_filter_bottom->val,
				hdl->video_chroma_median_filter_top->val);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops cx2341x_ops = अणु
	.try_ctrl = cx2341x_try_ctrl,
	.s_ctrl = cx2341x_s_ctrl,
पूर्ण;

अटल काष्ठा v4l2_ctrl *cx2341x_ctrl_new_custom(काष्ठा v4l2_ctrl_handler *hdl,
			u32 id, s32 min, s32 max, s32 step, s32 def)
अणु
	काष्ठा v4l2_ctrl_config cfg;

	स_रखो(&cfg, 0, माप(cfg));
	cx2341x_ctrl_fill(id, &cfg.name, &cfg.type, &min, &max, &step, &def, &cfg.flags);
	cfg.ops = &cx2341x_ops;
	cfg.id = id;
	cfg.min = min;
	cfg.max = max;
	cfg.def = def;
	अगर (cfg.type == V4L2_CTRL_TYPE_MENU) अणु
		cfg.step = 0;
		cfg.menu_skip_mask = step;
		cfg.qmenu = cx2341x_get_menu(id);
	पूर्ण अन्यथा अणु
		cfg.step = step;
		cfg.menu_skip_mask = 0;
	पूर्ण
	वापस v4l2_ctrl_new_custom(hdl, &cfg, शून्य);
पूर्ण

अटल काष्ठा v4l2_ctrl *cx2341x_ctrl_new_std(काष्ठा v4l2_ctrl_handler *hdl,
			u32 id, s32 min, s32 max, s32 step, s32 def)
अणु
	वापस v4l2_ctrl_new_std(hdl, &cx2341x_ops, id, min, max, step, def);
पूर्ण

अटल काष्ठा v4l2_ctrl *cx2341x_ctrl_new_menu(काष्ठा v4l2_ctrl_handler *hdl,
			u32 id, s32 max, s32 mask, s32 def)
अणु
	वापस v4l2_ctrl_new_std_menu(hdl, &cx2341x_ops, id, max, mask, def);
पूर्ण

पूर्णांक cx2341x_handler_init(काष्ठा cx2341x_handler *cxhdl,
			 अचिन्हित nr_of_controls_hपूर्णांक)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &cxhdl->hdl;
	u32 caps = cxhdl->capabilities;
	पूर्णांक has_sliced_vbi = caps & CX2341X_CAP_HAS_SLICED_VBI;
	पूर्णांक has_ac3 = caps & CX2341X_CAP_HAS_AC3;
	पूर्णांक has_ts = caps & CX2341X_CAP_HAS_TS;

	cxhdl->width = 720;
	cxhdl->height = 480;

	v4l2_ctrl_handler_init(hdl, nr_of_controls_hपूर्णांक);

	/* Add controls in ascending control ID order क्रम fastest
	   insertion समय. */
	cxhdl->stream_type = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_STREAM_TYPE,
			V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD, has_ts ? 0 : 2,
			V4L2_MPEG_STREAM_TYPE_MPEG2_PS);
	cxhdl->stream_vbi_fmt = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_STREAM_VBI_FMT,
			V4L2_MPEG_STREAM_VBI_FMT_IVTV, has_sliced_vbi ? 0 : 2,
			V4L2_MPEG_STREAM_VBI_FMT_NONE);
	cxhdl->audio_sampling_freq = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ,
			V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000, 0,
			V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000);
	cxhdl->audio_encoding = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_AUDIO_ENCODING,
			V4L2_MPEG_AUDIO_ENCODING_AC3, has_ac3 ? ~0x12 : ~0x2,
			V4L2_MPEG_AUDIO_ENCODING_LAYER_2);
	cxhdl->audio_l2_bitrate = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_AUDIO_L2_BITRATE,
			V4L2_MPEG_AUDIO_L2_BITRATE_384K, 0x1ff,
			V4L2_MPEG_AUDIO_L2_BITRATE_224K);
	cxhdl->audio_mode = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_AUDIO_MODE,
			V4L2_MPEG_AUDIO_MODE_MONO, 0,
			V4L2_MPEG_AUDIO_MODE_STEREO);
	cxhdl->audio_mode_extension = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_AUDIO_MODE_EXTENSION,
			V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16, 0,
			V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4);
	cxhdl->audio_emphasis = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_AUDIO_EMPHASIS,
			V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17, 0,
			V4L2_MPEG_AUDIO_EMPHASIS_NONE);
	cxhdl->audio_crc = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_AUDIO_CRC,
			V4L2_MPEG_AUDIO_CRC_CRC16, 0,
			V4L2_MPEG_AUDIO_CRC_NONE);

	cx2341x_ctrl_new_std(hdl, V4L2_CID_MPEG_AUDIO_MUTE, 0, 1, 1, 0);
	अगर (has_ac3)
		cxhdl->audio_ac3_bitrate = cx2341x_ctrl_new_menu(hdl,
				V4L2_CID_MPEG_AUDIO_AC3_BITRATE,
				V4L2_MPEG_AUDIO_AC3_BITRATE_448K, 0x03,
				V4L2_MPEG_AUDIO_AC3_BITRATE_224K);
	cxhdl->video_encoding = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_VIDEO_ENCODING,
			V4L2_MPEG_VIDEO_ENCODING_MPEG_2, 0,
			V4L2_MPEG_VIDEO_ENCODING_MPEG_2);
	cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_VIDEO_ASPECT,
			V4L2_MPEG_VIDEO_ASPECT_221x100, 0,
			V4L2_MPEG_VIDEO_ASPECT_4x3);
	cxhdl->video_b_frames = cx2341x_ctrl_new_std(hdl,
			V4L2_CID_MPEG_VIDEO_B_FRAMES, 0, 33, 1, 2);
	cxhdl->video_gop_size = cx2341x_ctrl_new_std(hdl,
			V4L2_CID_MPEG_VIDEO_GOP_SIZE,
			1, 34, 1, cxhdl->is_50hz ? 12 : 15);
	cx2341x_ctrl_new_std(hdl, V4L2_CID_MPEG_VIDEO_GOP_CLOSURE, 0, 1, 1, 1);
	cxhdl->video_bitrate_mode = cx2341x_ctrl_new_menu(hdl,
			V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
			V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 0,
			V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
	cxhdl->video_bitrate = cx2341x_ctrl_new_std(hdl,
			V4L2_CID_MPEG_VIDEO_BITRATE,
			0, 27000000, 1, 6000000);
	cxhdl->video_bitrate_peak = cx2341x_ctrl_new_std(hdl,
			V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
			0, 27000000, 1, 8000000);
	cx2341x_ctrl_new_std(hdl,
			V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION, 0, 255, 1, 0);
	cxhdl->video_mute = cx2341x_ctrl_new_std(hdl,
			V4L2_CID_MPEG_VIDEO_MUTE, 0, 1, 1, 0);
	cxhdl->video_mute_yuv = cx2341x_ctrl_new_std(hdl,
			V4L2_CID_MPEG_VIDEO_MUTE_YUV, 0, 0xffffff, 1, 0x008080);

	/* CX23415/6 specअगरic */
	cxhdl->video_spatial_filter_mode = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE,
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL,
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO, 0,
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL);
	cxhdl->video_spatial_filter = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER,
			0, 15, 1, 0);
	cxhdl->video_luma_spatial_filter_type = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE,
			V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_OFF,
			V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_SYM_NON_SEPARABLE,
			0,
			V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_1D_HOR);
	cxhdl->video_chroma_spatial_filter_type = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE,
			V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_OFF,
			V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR,
			0,
			V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR);
	cxhdl->video_temporal_filter_mode = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE,
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL,
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO,
			0,
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL);
	cxhdl->video_temporal_filter = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER,
			0, 31, 1, 8);
	cxhdl->video_median_filter_type = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE,
			V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF,
			V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_DIAG,
			0,
			V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF);
	cxhdl->video_luma_median_filter_bottom = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM,
			0, 255, 1, 0);
	cxhdl->video_luma_median_filter_top = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP,
			0, 255, 1, 255);
	cxhdl->video_chroma_median_filter_bottom = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM,
			0, 255, 1, 0);
	cxhdl->video_chroma_median_filter_top = cx2341x_ctrl_new_custom(hdl,
			V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP,
			0, 255, 1, 255);
	cx2341x_ctrl_new_custom(hdl, V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS,
			0, 1, 1, 0);

	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण

	v4l2_ctrl_cluster(8, &cxhdl->audio_sampling_freq);
	v4l2_ctrl_cluster(2, &cxhdl->video_b_frames);
	v4l2_ctrl_cluster(5, &cxhdl->stream_type);
	v4l2_ctrl_cluster(2, &cxhdl->video_mute);
	v4l2_ctrl_cluster(3, &cxhdl->video_spatial_filter_mode);
	v4l2_ctrl_cluster(2, &cxhdl->video_luma_spatial_filter_type);
	v4l2_ctrl_cluster(2, &cxhdl->video_spatial_filter);
	v4l2_ctrl_cluster(4, &cxhdl->video_luma_median_filter_top);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx2341x_handler_init);

व्योम cx2341x_handler_set_50hz(काष्ठा cx2341x_handler *cxhdl, पूर्णांक is_50hz)
अणु
	cxhdl->is_50hz = is_50hz;
	cxhdl->video_gop_size->शेष_value = cxhdl->is_50hz ? 12 : 15;
पूर्ण
EXPORT_SYMBOL(cx2341x_handler_set_50hz);

पूर्णांक cx2341x_handler_setup(काष्ठा cx2341x_handler *cxhdl)
अणु
	पूर्णांक h = cxhdl->height;
	पूर्णांक w = cxhdl->width;
	पूर्णांक err;

	err = cx2341x_hdl_api(cxhdl, CX2341X_ENC_SET_OUTPUT_PORT, 2, cxhdl->port, 0);
	अगर (err)
		वापस err;
	err = cx2341x_hdl_api(cxhdl, CX2341X_ENC_SET_FRAME_RATE, 1, cxhdl->is_50hz);
	अगर (err)
		वापस err;

	अगर (v4l2_ctrl_g_ctrl(cxhdl->video_encoding) == V4L2_MPEG_VIDEO_ENCODING_MPEG_1) अणु
		w /= 2;
		h /= 2;
	पूर्ण
	err = cx2341x_hdl_api(cxhdl, CX2341X_ENC_SET_FRAME_SIZE, 2, h, w);
	अगर (err)
		वापस err;
	वापस v4l2_ctrl_handler_setup(&cxhdl->hdl);
पूर्ण
EXPORT_SYMBOL(cx2341x_handler_setup);

व्योम cx2341x_handler_set_busy(काष्ठा cx2341x_handler *cxhdl, पूर्णांक busy)
अणु
	v4l2_ctrl_grab(cxhdl->audio_sampling_freq, busy);
	v4l2_ctrl_grab(cxhdl->audio_encoding, busy);
	v4l2_ctrl_grab(cxhdl->audio_l2_bitrate, busy);
	v4l2_ctrl_grab(cxhdl->audio_ac3_bitrate, busy);
	v4l2_ctrl_grab(cxhdl->stream_vbi_fmt, busy);
	v4l2_ctrl_grab(cxhdl->stream_type, busy);
	v4l2_ctrl_grab(cxhdl->video_bitrate_mode, busy);
	v4l2_ctrl_grab(cxhdl->video_bitrate, busy);
	v4l2_ctrl_grab(cxhdl->video_bitrate_peak, busy);
पूर्ण
EXPORT_SYMBOL(cx2341x_handler_set_busy);
