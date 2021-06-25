<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    cx23415/6/8 header containing common defines.

 */

#अगर_अघोषित CX2341X_H
#घोषणा CX2341X_H

#समावेश <media/v4l2-ctrls.h>

क्रमागत cx2341x_port अणु
	CX2341X_PORT_MEMORY    = 0,
	CX2341X_PORT_STREAMING = 1,
	CX2341X_PORT_SERIAL    = 2
पूर्ण;

क्रमागत cx2341x_cap अणु
	CX2341X_CAP_HAS_SLICED_VBI = 1 << 0,
	CX2341X_CAP_HAS_TS	   = 1 << 1,
	CX2341X_CAP_HAS_AC3	   = 1 << 2,
पूर्ण;

काष्ठा cx2341x_mpeg_params अणु
	/* misc */
	u32 capabilities;
	क्रमागत cx2341x_port port;
	u16 width;
	u16 height;
	u16 is_50hz;

	/* stream */
	क्रमागत v4l2_mpeg_stream_type stream_type;
	क्रमागत v4l2_mpeg_stream_vbi_fmt stream_vbi_fmt;
	u16 stream_insert_nav_packets;

	/* audio */
	क्रमागत v4l2_mpeg_audio_sampling_freq audio_sampling_freq;
	क्रमागत v4l2_mpeg_audio_encoding audio_encoding;
	क्रमागत v4l2_mpeg_audio_l2_bitrate audio_l2_bitrate;
	क्रमागत v4l2_mpeg_audio_ac3_bitrate audio_ac3_bitrate;
	क्रमागत v4l2_mpeg_audio_mode audio_mode;
	क्रमागत v4l2_mpeg_audio_mode_extension audio_mode_extension;
	क्रमागत v4l2_mpeg_audio_emphasis audio_emphasis;
	क्रमागत v4l2_mpeg_audio_crc audio_crc;
	u32 audio_properties;
	u16 audio_mute;

	/* video */
	क्रमागत v4l2_mpeg_video_encoding video_encoding;
	क्रमागत v4l2_mpeg_video_aspect video_aspect;
	u16 video_b_frames;
	u16 video_gop_size;
	u16 video_gop_closure;
	क्रमागत v4l2_mpeg_video_bitrate_mode video_bitrate_mode;
	u32 video_bitrate;
	u32 video_bitrate_peak;
	u16 video_temporal_decimation;
	u16 video_mute;
	u32 video_mute_yuv;

	/* encoding filters */
	क्रमागत v4l2_mpeg_cx2341x_video_spatial_filter_mode video_spatial_filter_mode;
	u16 video_spatial_filter;
	क्रमागत v4l2_mpeg_cx2341x_video_luma_spatial_filter_type video_luma_spatial_filter_type;
	क्रमागत v4l2_mpeg_cx2341x_video_chroma_spatial_filter_type video_chroma_spatial_filter_type;
	क्रमागत v4l2_mpeg_cx2341x_video_temporal_filter_mode video_temporal_filter_mode;
	u16 video_temporal_filter;
	क्रमागत v4l2_mpeg_cx2341x_video_median_filter_type video_median_filter_type;
	u16 video_luma_median_filter_top;
	u16 video_luma_median_filter_bottom;
	u16 video_chroma_median_filter_top;
	u16 video_chroma_median_filter_bottom;
पूर्ण;

#घोषणा CX2341X_MBOX_MAX_DATA 16

बाह्य स्थिर u32 cx2341x_mpeg_ctrls[];
प्रकार पूर्णांक (*cx2341x_mbox_func)(व्योम *priv, u32 cmd, पूर्णांक in, पूर्णांक out,
		u32 data[CX2341X_MBOX_MAX_DATA]);
पूर्णांक cx2341x_update(व्योम *priv, cx2341x_mbox_func func,
		स्थिर काष्ठा cx2341x_mpeg_params *old,
		स्थिर काष्ठा cx2341x_mpeg_params *new);
पूर्णांक cx2341x_ctrl_query(स्थिर काष्ठा cx2341x_mpeg_params *params,
		काष्ठा v4l2_queryctrl *qctrl);
स्थिर अक्षर * स्थिर *cx2341x_ctrl_get_menu(स्थिर काष्ठा cx2341x_mpeg_params *p, u32 id);
पूर्णांक cx2341x_ext_ctrls(काष्ठा cx2341x_mpeg_params *params, पूर्णांक busy,
		काष्ठा v4l2_ext_controls *ctrls, अचिन्हित पूर्णांक cmd);
व्योम cx2341x_fill_शेषs(काष्ठा cx2341x_mpeg_params *p);
व्योम cx2341x_log_status(स्थिर काष्ठा cx2341x_mpeg_params *p, स्थिर अक्षर *prefix);

काष्ठा cx2341x_handler;

काष्ठा cx2341x_handler_ops अणु
	/* needed क्रम the video घड़ी freq */
	पूर्णांक (*s_audio_sampling_freq)(काष्ठा cx2341x_handler *hdl, u32 val);
	/* needed क्रम dualwatch */
	पूर्णांक (*s_audio_mode)(काष्ठा cx2341x_handler *hdl, u32 val);
	/* needed क्रम setting up the video resolution */
	पूर्णांक (*s_video_encoding)(काष्ठा cx2341x_handler *hdl, u32 val);
	/* needed क्रम setting up the sliced vbi insertion data काष्ठाures */
	पूर्णांक (*s_stream_vbi_fmt)(काष्ठा cx2341x_handler *hdl, u32 val);
पूर्ण;

काष्ठा cx2341x_handler अणु
	u32 capabilities;
	क्रमागत cx2341x_port port;
	u16 width;
	u16 height;
	u16 is_50hz;
	u32 audio_properties;

	काष्ठा v4l2_ctrl_handler hdl;
	व्योम *priv;
	cx2341x_mbox_func func;
	स्थिर काष्ठा cx2341x_handler_ops *ops;

	काष्ठा v4l2_ctrl *stream_vbi_fmt;

	काष्ठा अणु
		/* audio cluster */
		काष्ठा v4l2_ctrl *audio_sampling_freq;
		काष्ठा v4l2_ctrl *audio_encoding;
		काष्ठा v4l2_ctrl *audio_l2_bitrate;
		काष्ठा v4l2_ctrl *audio_mode;
		काष्ठा v4l2_ctrl *audio_mode_extension;
		काष्ठा v4l2_ctrl *audio_emphasis;
		काष्ठा v4l2_ctrl *audio_crc;
		काष्ठा v4l2_ctrl *audio_ac3_bitrate;
	पूर्ण;

	काष्ठा अणु
		/* video gop cluster */
		काष्ठा v4l2_ctrl *video_b_frames;
		काष्ठा v4l2_ctrl *video_gop_size;
	पूर्ण;

	काष्ठा अणु
		/* stream type cluster */
		काष्ठा v4l2_ctrl *stream_type;
		काष्ठा v4l2_ctrl *video_encoding;
		काष्ठा v4l2_ctrl *video_bitrate_mode;
		काष्ठा v4l2_ctrl *video_bitrate;
		काष्ठा v4l2_ctrl *video_bitrate_peak;
	पूर्ण;

	काष्ठा अणु
		/* video mute cluster */
		काष्ठा v4l2_ctrl *video_mute;
		काष्ठा v4l2_ctrl *video_mute_yuv;
	पूर्ण;

	काष्ठा अणु
		/* video filter mode cluster */
		काष्ठा v4l2_ctrl *video_spatial_filter_mode;
		काष्ठा v4l2_ctrl *video_temporal_filter_mode;
		काष्ठा v4l2_ctrl *video_median_filter_type;
	पूर्ण;

	काष्ठा अणु
		/* video filter type cluster */
		काष्ठा v4l2_ctrl *video_luma_spatial_filter_type;
		काष्ठा v4l2_ctrl *video_chroma_spatial_filter_type;
	पूर्ण;

	काष्ठा  अणु
		/* video filter cluster */
		काष्ठा v4l2_ctrl *video_spatial_filter;
		काष्ठा v4l2_ctrl *video_temporal_filter;
	पूर्ण;

	काष्ठा अणु
		/* video median cluster */
		काष्ठा v4l2_ctrl *video_luma_median_filter_top;
		काष्ठा v4l2_ctrl *video_luma_median_filter_bottom;
		काष्ठा v4l2_ctrl *video_chroma_median_filter_top;
		काष्ठा v4l2_ctrl *video_chroma_median_filter_bottom;
	पूर्ण;
पूर्ण;

पूर्णांक cx2341x_handler_init(काष्ठा cx2341x_handler *cxhdl,
			 अचिन्हित nr_of_controls_hपूर्णांक);
व्योम cx2341x_handler_set_50hz(काष्ठा cx2341x_handler *cxhdl, पूर्णांक is_50hz);
पूर्णांक cx2341x_handler_setup(काष्ठा cx2341x_handler *cxhdl);
व्योम cx2341x_handler_set_busy(काष्ठा cx2341x_handler *cxhdl, पूर्णांक busy);

/* Firmware names */
#घोषणा CX2341X_FIRM_ENC_खाताNAME "v4l-cx2341x-enc.fw"
/* Decoder firmware क्रम the cx23415 only */
#घोषणा CX2341X_FIRM_DEC_खाताNAME "v4l-cx2341x-dec.fw"

/* Firmware API commands */

/* MPEG decoder API, specअगरic to the cx23415 */
#घोषणा CX2341X_DEC_PING_FW			0x00
#घोषणा CX2341X_DEC_START_PLAYBACK		0x01
#घोषणा CX2341X_DEC_STOP_PLAYBACK		0x02
#घोषणा CX2341X_DEC_SET_PLAYBACK_SPEED		0x03
#घोषणा CX2341X_DEC_STEP_VIDEO			0x05
#घोषणा CX2341X_DEC_SET_DMA_BLOCK_SIZE		0x08
#घोषणा CX2341X_DEC_GET_XFER_INFO		0x09
#घोषणा CX2341X_DEC_GET_DMA_STATUS		0x0a
#घोषणा CX2341X_DEC_SCHED_DMA_FROM_HOST		0x0b
#घोषणा CX2341X_DEC_PAUSE_PLAYBACK		0x0d
#घोषणा CX2341X_DEC_HALT_FW			0x0e
#घोषणा CX2341X_DEC_SET_STANDARD		0x10
#घोषणा CX2341X_DEC_GET_VERSION			0x11
#घोषणा CX2341X_DEC_SET_STREAM_INPUT		0x14
#घोषणा CX2341X_DEC_GET_TIMING_INFO		0x15
#घोषणा CX2341X_DEC_SET_AUDIO_MODE		0x16
#घोषणा CX2341X_DEC_SET_EVENT_NOTIFICATION	0x17
#घोषणा CX2341X_DEC_SET_DISPLAY_BUFFERS		0x18
#घोषणा CX2341X_DEC_EXTRACT_VBI			0x19
#घोषणा CX2341X_DEC_SET_DECODER_SOURCE		0x1a
#घोषणा CX2341X_DEC_SET_PREBUFFERING		0x1e

/* MPEG encoder API */
#घोषणा CX2341X_ENC_PING_FW			0x80
#घोषणा CX2341X_ENC_START_CAPTURE		0x81
#घोषणा CX2341X_ENC_STOP_CAPTURE		0x82
#घोषणा CX2341X_ENC_SET_AUDIO_ID		0x89
#घोषणा CX2341X_ENC_SET_VIDEO_ID		0x8b
#घोषणा CX2341X_ENC_SET_PCR_ID			0x8d
#घोषणा CX2341X_ENC_SET_FRAME_RATE		0x8f
#घोषणा CX2341X_ENC_SET_FRAME_SIZE		0x91
#घोषणा CX2341X_ENC_SET_BIT_RATE		0x95
#घोषणा CX2341X_ENC_SET_GOP_PROPERTIES		0x97
#घोषणा CX2341X_ENC_SET_ASPECT_RATIO		0x99
#घोषणा CX2341X_ENC_SET_DNR_FILTER_MODE		0x9b
#घोषणा CX2341X_ENC_SET_DNR_FILTER_PROPS	0x9d
#घोषणा CX2341X_ENC_SET_CORING_LEVELS		0x9f
#घोषणा CX2341X_ENC_SET_SPATIAL_FILTER_TYPE	0xa1
#घोषणा CX2341X_ENC_SET_VBI_LINE		0xb7
#घोषणा CX2341X_ENC_SET_STREAM_TYPE		0xb9
#घोषणा CX2341X_ENC_SET_OUTPUT_PORT		0xbb
#घोषणा CX2341X_ENC_SET_AUDIO_PROPERTIES	0xbd
#घोषणा CX2341X_ENC_HALT_FW			0xc3
#घोषणा CX2341X_ENC_GET_VERSION			0xc4
#घोषणा CX2341X_ENC_SET_GOP_CLOSURE		0xc5
#घोषणा CX2341X_ENC_GET_SEQ_END			0xc6
#घोषणा CX2341X_ENC_SET_PGM_INDEX_INFO		0xc7
#घोषणा CX2341X_ENC_SET_VBI_CONFIG		0xc8
#घोषणा CX2341X_ENC_SET_DMA_BLOCK_SIZE		0xc9
#घोषणा CX2341X_ENC_GET_PREV_DMA_INFO_MB_10	0xca
#घोषणा CX2341X_ENC_GET_PREV_DMA_INFO_MB_9	0xcb
#घोषणा CX2341X_ENC_SCHED_DMA_TO_HOST		0xcc
#घोषणा CX2341X_ENC_INITIALIZE_INPUT		0xcd
#घोषणा CX2341X_ENC_SET_FRAME_DROP_RATE		0xd0
#घोषणा CX2341X_ENC_PAUSE_ENCODER		0xd2
#घोषणा CX2341X_ENC_REFRESH_INPUT		0xd3
#घोषणा CX2341X_ENC_SET_COPYRIGHT		0xd4
#घोषणा CX2341X_ENC_SET_EVENT_NOTIFICATION	0xd5
#घोषणा CX2341X_ENC_SET_NUM_VSYNC_LINES		0xd6
#घोषणा CX2341X_ENC_SET_PLACEHOLDER		0xd7
#घोषणा CX2341X_ENC_MUTE_VIDEO			0xd9
#घोषणा CX2341X_ENC_MUTE_AUDIO			0xda
#घोषणा CX2341X_ENC_SET_VERT_CROP_LINE		0xdb
#घोषणा CX2341X_ENC_MISC			0xdc

/* OSD API, specअगरic to the cx23415 */
#घोषणा CX2341X_OSD_GET_FRAMEBUFFER		0x41
#घोषणा CX2341X_OSD_GET_PIXEL_FORMAT		0x42
#घोषणा CX2341X_OSD_SET_PIXEL_FORMAT		0x43
#घोषणा CX2341X_OSD_GET_STATE			0x44
#घोषणा CX2341X_OSD_SET_STATE			0x45
#घोषणा CX2341X_OSD_GET_OSD_COORDS		0x46
#घोषणा CX2341X_OSD_SET_OSD_COORDS		0x47
#घोषणा CX2341X_OSD_GET_SCREEN_COORDS		0x48
#घोषणा CX2341X_OSD_SET_SCREEN_COORDS		0x49
#घोषणा CX2341X_OSD_GET_GLOBAL_ALPHA		0x4a
#घोषणा CX2341X_OSD_SET_GLOBAL_ALPHA		0x4b
#घोषणा CX2341X_OSD_SET_BLEND_COORDS		0x4c
#घोषणा CX2341X_OSD_GET_FLICKER_STATE		0x4f
#घोषणा CX2341X_OSD_SET_FLICKER_STATE		0x50
#घोषणा CX2341X_OSD_BLT_COPY			0x52
#घोषणा CX2341X_OSD_BLT_FILL			0x53
#घोषणा CX2341X_OSD_BLT_TEXT			0x54
#घोषणा CX2341X_OSD_SET_FRAMEBUFFER_WINDOW	0x56
#घोषणा CX2341X_OSD_SET_CHROMA_KEY		0x60
#घोषणा CX2341X_OSD_GET_ALPHA_CONTENT_INDEX	0x61
#घोषणा CX2341X_OSD_SET_ALPHA_CONTENT_INDEX	0x62

#पूर्ण_अगर /* CX2341X_H */
