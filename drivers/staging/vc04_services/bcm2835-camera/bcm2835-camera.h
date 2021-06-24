<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 *
 * core driver device
 */

#घोषणा V4L2_CTRL_COUNT 29 /* number of v4l controls */

क्रमागत अणु
	COMP_CAMERA = 0,
	COMP_PREVIEW,
	COMP_IMAGE_ENCODE,
	COMP_VIDEO_ENCODE,
	COMP_COUNT
पूर्ण;

क्रमागत अणु
	CAM_PORT_PREVIEW = 0,
	CAM_PORT_VIDEO,
	CAM_PORT_CAPTURE,
	CAM_PORT_COUNT
पूर्ण;

बाह्य पूर्णांक bcm2835_v4l2_debug;

काष्ठा bm2835_mmal_dev अणु
	/* v4l2 devices */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा mutex mutex;

	/* controls */
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *ctrls[V4L2_CTRL_COUNT];
	क्रमागत v4l2_scene_mode scene_mode;
	काष्ठा mmal_colourfx colourfx;
	पूर्णांक hflip;
	पूर्णांक vflip;
	पूर्णांक red_gain;
	पूर्णांक blue_gain;
	क्रमागत mmal_parameter_exposuremode exposure_mode_user;
	क्रमागत v4l2_exposure_स्वतः_type exposure_mode_v4l2_user;
	/* active exposure mode may dअगरfer अगर selected via a scene mode */
	क्रमागत mmal_parameter_exposuremode exposure_mode_active;
	क्रमागत mmal_parameter_exposuremeteringmode metering_mode;
	अचिन्हित पूर्णांक manual_shutter_speed;
	bool exp_स्वतः_priority;
	bool manual_iso_enabled;
	u32 iso;

	/* allocated mmal instance and components */
	काष्ठा vchiq_mmal_instance *instance;
	काष्ठा vchiq_mmal_component *component[COMP_COUNT];
	पूर्णांक camera_use_count;

	काष्ठा v4l2_winकरोw overlay;

	काष्ठा अणु
		अचिन्हित पूर्णांक width;  /* width */
		अचिन्हित पूर्णांक height;  /* height */
		अचिन्हित पूर्णांक stride;  /* stride */
		अचिन्हित पूर्णांक buffersize; /* buffer size with padding */
		काष्ठा mmal_fmt *fmt;
		काष्ठा v4l2_fract समयperframe;

		/* H264 encode bitrate */
		पूर्णांक encode_bitrate;
		/* H264 bitrate mode. CBR/VBR */
		पूर्णांक encode_bitrate_mode;
		/* H264 profile */
		क्रमागत v4l2_mpeg_video_h264_profile enc_profile;
		/* H264 level */
		क्रमागत v4l2_mpeg_video_h264_level enc_level;
		/* JPEG Q-factor */
		पूर्णांक q_factor;

		काष्ठा vb2_queue vb_vidq;

		/* VC start बारtamp क्रम streaming */
		s64 vc_start_बारtamp;
		/* Kernel start बारtamp क्रम streaming */
		kसमय_प्रकार kernel_start_ts;
		/* Sequence number of last buffer */
		u32 sequence;

		काष्ठा vchiq_mmal_port *port; /* port being used क्रम capture */
		/* camera port being used क्रम capture */
		काष्ठा vchiq_mmal_port *camera_port;
		/* component being used क्रम encode */
		काष्ठा vchiq_mmal_component *encode_component;
		/* number of frames reमुख्यing which driver should capture */
		अचिन्हित पूर्णांक frame_count;
		/* last frame completion */
		काष्ठा completion frame_cmplt;

	पूर्ण capture;

	अचिन्हित पूर्णांक camera_num;
	अचिन्हित पूर्णांक max_width;
	अचिन्हित पूर्णांक max_height;
	अचिन्हित पूर्णांक rgb_bgr_swapped;
पूर्ण;

पूर्णांक bm2835_mmal_init_controls(
			काष्ठा bm2835_mmal_dev *dev,
			काष्ठा v4l2_ctrl_handler *hdl);

पूर्णांक bm2835_mmal_set_all_camera_controls(काष्ठा bm2835_mmal_dev *dev);
पूर्णांक set_framerate_params(काष्ठा bm2835_mmal_dev *dev);

/* Debug helpers */

#घोषणा v4l2_dump_pix_क्रमmat(level, debug, dev, pix_fmt, desc)	\
अणु	\
	v4l2_dbg(level, debug, dev,	\
"%s: w %u h %u field %u pfmt 0x%x bpl %u sz_img %u colorspace 0x%x priv %u\n", \
		desc,	\
		(pix_fmt)->width, (pix_fmt)->height, (pix_fmt)->field,	\
		(pix_fmt)->pixelक्रमmat, (pix_fmt)->bytesperline,	\
		(pix_fmt)->sizeimage, (pix_fmt)->colorspace, (pix_fmt)->priv); \
पूर्ण

#घोषणा v4l2_dump_win_क्रमmat(level, debug, dev, win_fmt, desc)	\
अणु	\
	v4l2_dbg(level, debug, dev,	\
"%s: w %u h %u l %u t %u  field %u chromakey %06X clip %p " \
"clipcount %u bitmap %p\n", \
		desc,	\
		(win_fmt)->w.width, (win_fmt)->w.height, \
		(win_fmt)->w.left, (win_fmt)->w.top, \
		(win_fmt)->field,	\
		(win_fmt)->chromakey,	\
		(win_fmt)->clips, (win_fmt)->clipcount,	\
		(win_fmt)->biपंचांगap); \
पूर्ण
