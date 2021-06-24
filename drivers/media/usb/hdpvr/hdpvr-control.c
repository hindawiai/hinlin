<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hauppauge HD PVR USB driver - video 4 linux 2 पूर्णांकerface
 *
 * Copyright (C) 2008      Janne Grunau (j@jannau.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>

#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-common.h>

#समावेश "hdpvr.h"


पूर्णांक hdpvr_config_call(काष्ठा hdpvr_device *dev, uपूर्णांक value, u8 valbuf)
अणु
	पूर्णांक ret;
	अक्षर request_type = 0x38, snd_request = 0x01;

	mutex_lock(&dev->usbc_mutex);
	dev->usbc_buf[0] = valbuf;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      snd_request, 0x00 | request_type,
			      value, CTRL_DEFAULT_INDEX,
			      dev->usbc_buf, 1, 10000);

	mutex_unlock(&dev->usbc_mutex);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "config call request for value 0x%x returned %d\n", value,
		 ret);

	वापस ret < 0 ? ret : 0;
पूर्ण

पूर्णांक get_video_info(काष्ठा hdpvr_device *dev, काष्ठा hdpvr_video_info *vidinf)
अणु
	पूर्णांक ret;

	vidinf->valid = false;
	mutex_lock(&dev->usbc_mutex);
	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      0x81, 0x80 | 0x38,
			      0x1400, 0x0003,
			      dev->usbc_buf, 5,
			      1000);

#अगर_घोषित HDPVR_DEBUG
	अगर (hdpvr_debug & MSG_INFO)
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "get video info returned: %d, %5ph\n", ret,
			 dev->usbc_buf);
#पूर्ण_अगर
	mutex_unlock(&dev->usbc_mutex);

	अगर (ret < 0)
		वापस ret;

	vidinf->width	= dev->usbc_buf[1] << 8 | dev->usbc_buf[0];
	vidinf->height	= dev->usbc_buf[3] << 8 | dev->usbc_buf[2];
	vidinf->fps	= dev->usbc_buf[4];
	vidinf->valid   = vidinf->width && vidinf->height && vidinf->fps;

	वापस 0;
पूर्ण

पूर्णांक get_input_lines_info(काष्ठा hdpvr_device *dev)
अणु
	पूर्णांक ret, lines;

	mutex_lock(&dev->usbc_mutex);
	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      0x81, 0x80 | 0x38,
			      0x1800, 0x0003,
			      dev->usbc_buf, 3,
			      1000);

#अगर_घोषित HDPVR_DEBUG
	अगर (hdpvr_debug & MSG_INFO)
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "get input lines info returned: %d, %3ph\n", ret,
			 dev->usbc_buf);
#अन्यथा
	(व्योम)ret;	/* suppress compiler warning */
#पूर्ण_अगर
	lines = dev->usbc_buf[1] << 8 | dev->usbc_buf[0];
	mutex_unlock(&dev->usbc_mutex);
	वापस lines;
पूर्ण


पूर्णांक hdpvr_set_bitrate(काष्ठा hdpvr_device *dev)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->usbc_mutex);
	स_रखो(dev->usbc_buf, 0, 4);
	dev->usbc_buf[0] = dev->options.bitrate;
	dev->usbc_buf[2] = dev->options.peak_bitrate;

	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0x01, 0x38, CTRL_BITRATE_VALUE,
			      CTRL_DEFAULT_INDEX, dev->usbc_buf, 4, 1000);
	mutex_unlock(&dev->usbc_mutex);

	वापस ret;
पूर्ण

पूर्णांक hdpvr_set_audio(काष्ठा hdpvr_device *dev, u8 input,
		    क्रमागत v4l2_mpeg_audio_encoding codec)
अणु
	पूर्णांक ret = 0;

	अगर (dev->flags & HDPVR_FLAG_AC3_CAP) अणु
		mutex_lock(&dev->usbc_mutex);
		स_रखो(dev->usbc_buf, 0, 2);
		dev->usbc_buf[0] = input;
		अगर (codec == V4L2_MPEG_AUDIO_ENCODING_AAC)
			dev->usbc_buf[1] = 0;
		अन्यथा अगर (codec == V4L2_MPEG_AUDIO_ENCODING_AC3)
			dev->usbc_buf[1] = 1;
		अन्यथा अणु
			mutex_unlock(&dev->usbc_mutex);
			v4l2_err(&dev->v4l2_dev, "invalid audio codec %d\n",
				 codec);
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		ret = usb_control_msg(dev->udev,
				      usb_sndctrlpipe(dev->udev, 0),
				      0x01, 0x38, CTRL_AUDIO_INPUT_VALUE,
				      CTRL_DEFAULT_INDEX, dev->usbc_buf, 2,
				      1000);
		mutex_unlock(&dev->usbc_mutex);
		अगर (ret == 2)
			ret = 0;
	पूर्ण अन्यथा
		ret = hdpvr_config_call(dev, CTRL_AUDIO_INPUT_VALUE, input);
error:
	वापस ret;
पूर्ण

पूर्णांक hdpvr_set_options(काष्ठा hdpvr_device *dev)
अणु
	hdpvr_config_call(dev, CTRL_VIDEO_STD_TYPE, dev->options.video_std);

	hdpvr_config_call(dev, CTRL_VIDEO_INPUT_VALUE,
			 dev->options.video_input+1);

	hdpvr_set_audio(dev, dev->options.audio_input+1,
		       dev->options.audio_codec);

	hdpvr_set_bitrate(dev);
	hdpvr_config_call(dev, CTRL_BITRATE_MODE_VALUE,
			 dev->options.bitrate_mode);
	hdpvr_config_call(dev, CTRL_GOP_MODE_VALUE, dev->options.gop_mode);

	hdpvr_config_call(dev, CTRL_BRIGHTNESS, dev->options.brightness);
	hdpvr_config_call(dev, CTRL_CONTRAST,   dev->options.contrast);
	hdpvr_config_call(dev, CTRL_HUE,        dev->options.hue);
	hdpvr_config_call(dev, CTRL_SATURATION, dev->options.saturation);
	hdpvr_config_call(dev, CTRL_SHARPNESS,  dev->options.sharpness);

	वापस 0;
पूर्ण
