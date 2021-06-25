<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A driver क्रम the AverMedia MR 800 USB FM radio. This device plugs
 * पूर्णांकo both the USB and an analog audio input, so this thing
 * only deals with initialization and frequency setting, the
 * audio data has to be handled by a sound driver.
 *
 * Copyright (c) 2008 Alexey Klimov <klimov.linux@gmail.com>
 */

/*
 * Big thanks to authors and contributors of dsbr100.c and radio-si470x.c
 *
 * When work was looked pretty good, i discover this:
 * http://av-usbradio.sourceक्रमge.net/index.php
 * http://sourceक्रमge.net/projects/av-usbradio/
 * Latest release of theirs project was in 2005.
 * Probably, this driver could be improved through using their
 * achievements (specअगरications given).
 * Also, Faiकरोn Liambotis <paraव्योम@debian.org> wrote nice driver क्रम this radio
 * in 2007. He allowed to use his driver to improve current mr800 radio driver.
 * http://www.spinics.net/lists/linux-usb-devel/msg10109.hपंचांगl
 *
 * Version 0.01:	First working version.
 *			It's required to blacklist AverMedia USB Radio
 *			in usbhid/hid-quirks.c
 * Version 0.10:	A lot of cleanups and fixes: unpluging the device,
 *			few mutex locks were added, codinstyle issues, etc.
 *			Added stereo support. Thanks to
 *			Douglas Schilling Landgraf <करोugsland@gmail.com> and
 *			David Ellingsworth <david@identd.dyndns.org>
 *			क्रम discussion, help and support.
 * Version 0.11:	Converted to v4l2_device.
 *
 * Many things to करो:
 *	- Correct घातer management of device (suspend & resume)
 *	- Add code क्रम scanning and smooth tuning
 *	- Add code क्रम sensitivity value
 *	- Correct mistakes
 *	- In Japan another FREQ_MIN and FREQ_MAX
 */

/* kernel includes */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>

/* driver and module definitions */
#घोषणा DRIVER_AUTHOR "Alexey Klimov <klimov.linux@gmail.com>"
#घोषणा DRIVER_DESC "AverMedia MR 800 USB FM radio driver"
#घोषणा DRIVER_VERSION "0.1.2"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

#घोषणा USB_AMRADIO_VENDOR 0x07ca
#घोषणा USB_AMRADIO_PRODUCT 0xb800

/* dev_warn macro with driver name */
#घोषणा MR800_DRIVER_NAME "radio-mr800"
#घोषणा amradio_dev_warn(dev, fmt, arg...)				\
		dev_warn(dev, MR800_DRIVER_NAME " - " fmt, ##arg)

#घोषणा amradio_dev_err(dev, fmt, arg...) \
		dev_err(dev, MR800_DRIVER_NAME " - " fmt, ##arg)

/* Probably USB_TIMEOUT should be modअगरied in module parameter */
#घोषणा BUFFER_LENGTH 8
#घोषणा USB_TIMEOUT 500

/* Frequency limits in MHz -- these are European values.  For Japanese
devices, that would be 76 and 91.  */
#घोषणा FREQ_MIN  87.5
#घोषणा FREQ_MAX 108.0
#घोषणा FREQ_MUL 16000

/*
 * Commands that device should understand
 * List isn't full and will be updated with implementation of new functions
 */
#घोषणा AMRADIO_SET_FREQ	0xa4
#घोषणा AMRADIO_GET_READY_FLAG	0xa5
#घोषणा AMRADIO_GET_SIGNAL	0xa7
#घोषणा AMRADIO_GET_FREQ	0xa8
#घोषणा AMRADIO_SET_SEARCH_UP	0xa9
#घोषणा AMRADIO_SET_SEARCH_DOWN	0xaa
#घोषणा AMRADIO_SET_MUTE	0xab
#घोषणा AMRADIO_SET_RIGHT_MUTE	0xac
#घोषणा AMRADIO_SET_LEFT_MUTE	0xad
#घोषणा AMRADIO_SET_MONO	0xae
#घोषणा AMRADIO_SET_SEARCH_LVL	0xb0
#घोषणा AMRADIO_STOP_SEARCH	0xb1

/* Comक्रमtable defines क्रम amradio_set_stereo */
#घोषणा WANT_STEREO		0x00
#घोषणा WANT_MONO		0x01

/* module parameter */
अटल पूर्णांक radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0);
MODULE_PARM_DESC(radio_nr, "Radio Nr");

/* Data क्रम one (physical) device */
काष्ठा amradio_device अणु
	/* reference to USB and video device */
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;

	u8 *buffer;
	काष्ठा mutex lock;	/* buffer locking */
	पूर्णांक curfreq;
	पूर्णांक stereo;
	पूर्णांक muted;
पूर्ण;

अटल अंतरभूत काष्ठा amradio_device *to_amradio_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा amradio_device, v4l2_dev);
पूर्ण

अटल पूर्णांक amradio_send_cmd(काष्ठा amradio_device *radio, u8 cmd, u8 arg,
		u8 *extra, u8 extralen, bool reply)
अणु
	पूर्णांक retval;
	पूर्णांक size;

	radio->buffer[0] = 0x00;
	radio->buffer[1] = 0x55;
	radio->buffer[2] = 0xaa;
	radio->buffer[3] = extralen;
	radio->buffer[4] = cmd;
	radio->buffer[5] = arg;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = extra || reply ? 8 : 0;

	retval = usb_bulk_msg(radio->usbdev, usb_sndपूर्णांकpipe(radio->usbdev, 2),
		radio->buffer, BUFFER_LENGTH, &size, USB_TIMEOUT);

	अगर (retval < 0 || size != BUFFER_LENGTH) अणु
		अगर (video_is_रेजिस्टरed(&radio->vdev))
			amradio_dev_warn(&radio->vdev.dev,
					"cmd %02x failed\n", cmd);
		वापस retval ? retval : -EIO;
	पूर्ण
	अगर (!extra && !reply)
		वापस 0;

	अगर (extra) अणु
		स_नकल(radio->buffer, extra, extralen);
		स_रखो(radio->buffer + extralen, 0, 8 - extralen);
		retval = usb_bulk_msg(radio->usbdev, usb_sndपूर्णांकpipe(radio->usbdev, 2),
			radio->buffer, BUFFER_LENGTH, &size, USB_TIMEOUT);
	पूर्ण अन्यथा अणु
		स_रखो(radio->buffer, 0, 8);
		retval = usb_bulk_msg(radio->usbdev, usb_rcvbulkpipe(radio->usbdev, 0x81),
			radio->buffer, BUFFER_LENGTH, &size, USB_TIMEOUT);
	पूर्ण
	अगर (retval == 0 && size == BUFFER_LENGTH)
		वापस 0;
	अगर (video_is_रेजिस्टरed(&radio->vdev) && cmd != AMRADIO_GET_READY_FLAG)
		amradio_dev_warn(&radio->vdev.dev, "follow-up to cmd %02x failed\n", cmd);
	वापस retval ? retval : -EIO;
पूर्ण

/* चयन on/off the radio. Send 8 bytes to device */
अटल पूर्णांक amradio_set_mute(काष्ठा amradio_device *radio, bool mute)
अणु
	पूर्णांक ret = amradio_send_cmd(radio,
			AMRADIO_SET_MUTE, mute, शून्य, 0, false);

	अगर (!ret)
		radio->muted = mute;
	वापस ret;
पूर्ण

/* set a frequency, freq is defined by v4l's TUNER_LOW, i.e. 1/16th kHz */
अटल पूर्णांक amradio_set_freq(काष्ठा amradio_device *radio, पूर्णांक freq)
अणु
	अचिन्हित लघु freq_send;
	u8 buf[3];
	पूर्णांक retval;

	/* we need to be sure that frequency isn't out of range */
	freq = clamp_t(अचिन्हित, freq, FREQ_MIN * FREQ_MUL, FREQ_MAX * FREQ_MUL);
	freq_send = 0x10 + (freq >> 3) / 25;

	/* frequency is calculated from freq_send and placed in first 2 bytes */
	buf[0] = (freq_send >> 8) & 0xff;
	buf[1] = freq_send & 0xff;
	buf[2] = 0x01;

	retval = amradio_send_cmd(radio, AMRADIO_SET_FREQ, 0, buf, 3, false);
	अगर (retval)
		वापस retval;
	radio->curfreq = freq;
	msleep(40);
	वापस 0;
पूर्ण

अटल पूर्णांक amradio_set_stereo(काष्ठा amradio_device *radio, bool stereo)
अणु
	पूर्णांक ret = amradio_send_cmd(radio,
			AMRADIO_SET_MONO, !stereo, शून्य, 0, false);

	अगर (!ret)
		radio->stereo = stereo;
	वापस ret;
पूर्ण

अटल पूर्णांक amradio_get_stat(काष्ठा amradio_device *radio, bool *is_stereo, u32 *संकेत)
अणु
	पूर्णांक ret = amradio_send_cmd(radio,
			AMRADIO_GET_SIGNAL, 0, शून्य, 0, true);

	अगर (ret)
		वापस ret;
	*is_stereo = radio->buffer[2] >> 7;
	*संकेत = (radio->buffer[3] & 0xf0) << 8;
	वापस 0;
पूर्ण

/* Handle unplugging the device.
 * We call video_unरेजिस्टर_device in any हाल.
 * The last function called in this procedure is
 * usb_amradio_device_release.
 */
अटल व्योम usb_amradio_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा amradio_device *radio = to_amradio_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	mutex_lock(&radio->lock);
	video_unरेजिस्टर_device(&radio->vdev);
	amradio_set_mute(radio, true);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->lock);
	v4l2_device_put(&radio->v4l2_dev);
पूर्ण

/* vidioc_querycap - query device capabilities */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा amradio_device *radio = video_drvdata(file);

	strscpy(v->driver, "radio-mr800", माप(v->driver));
	strscpy(v->card, "AverMedia MR 800 USB FM Radio", माप(v->card));
	usb_make_path(radio->usbdev, v->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

/* vidioc_g_tuner - get tuner attributes */
अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *v)
अणु
	काष्ठा amradio_device *radio = video_drvdata(file);
	bool is_stereo = false;
	पूर्णांक retval;

	अगर (v->index > 0)
		वापस -EINVAL;

	v->संकेत = 0;
	retval = amradio_get_stat(radio, &is_stereo, &v->संकेत);
	अगर (retval)
		वापस retval;

	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = FREQ_MIN * FREQ_MUL;
	v->rangehigh = FREQ_MAX * FREQ_MUL;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_HWSEEK_WRAP;
	v->rxsubchans = is_stereo ? V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO;
	v->audmode = radio->stereo ?
		V4L2_TUNER_MODE_STEREO : V4L2_TUNER_MODE_MONO;
	वापस 0;
पूर्ण

/* vidioc_s_tuner - set tuner attributes */
अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा amradio_device *radio = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	/* mono/stereo selector */
	चयन (v->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		वापस amradio_set_stereo(radio, WANT_MONO);
	शेष:
		वापस amradio_set_stereo(radio, WANT_STEREO);
	पूर्ण
पूर्ण

/* vidioc_s_frequency - set tuner radio frequency */
अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा amradio_device *radio = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	वापस amradio_set_freq(radio, f->frequency);
पूर्ण

/* vidioc_g_frequency - get tuner radio frequency */
अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा amradio_device *radio = video_drvdata(file);

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = radio->curfreq;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_hw_freq_seek(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_hw_freq_seek *seek)
अणु
	अटल u8 buf[8] = अणु
		0x3d, 0x32, 0x0f, 0x08, 0x3d, 0x32, 0x0f, 0x08
	पूर्ण;
	काष्ठा amradio_device *radio = video_drvdata(file);
	अचिन्हित दीर्घ समयout;
	पूर्णांक retval;

	अगर (seek->tuner != 0 || !seek->wrap_around)
		वापस -EINVAL;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EWOULDBLOCK;

	retval = amradio_send_cmd(radio,
			AMRADIO_SET_SEARCH_LVL, 0, buf, 8, false);
	अगर (retval)
		वापस retval;
	amradio_set_freq(radio, radio->curfreq);
	retval = amradio_send_cmd(radio,
		seek->seek_upward ? AMRADIO_SET_SEARCH_UP : AMRADIO_SET_SEARCH_DOWN,
		0, शून्य, 0, false);
	अगर (retval)
		वापस retval;
	समयout = jअगरfies + msecs_to_jअगरfies(30000);
	क्रम (;;) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			retval = -ENODATA;
			अवरोध;
		पूर्ण
		अगर (schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(10))) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		retval = amradio_send_cmd(radio, AMRADIO_GET_READY_FLAG,
				0, शून्य, 0, true);
		अगर (retval)
			जारी;
		amradio_send_cmd(radio, AMRADIO_GET_FREQ, 0, शून्य, 0, true);
		अगर (radio->buffer[1] || radio->buffer[2]) अणु
			/* To check: someबार radio->curfreq is set to out of range value */
			radio->curfreq = (radio->buffer[1] << 8) | radio->buffer[2];
			radio->curfreq = (radio->curfreq - 0x10) * 200;
			amradio_send_cmd(radio, AMRADIO_STOP_SEARCH,
					0, शून्य, 0, false);
			amradio_set_freq(radio, radio->curfreq);
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	amradio_send_cmd(radio, AMRADIO_STOP_SEARCH, 0, शून्य, 0, false);
	amradio_set_freq(radio, radio->curfreq);
	वापस retval;
पूर्ण

अटल पूर्णांक usb_amradio_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा amradio_device *radio =
		container_of(ctrl->handler, काष्ठा amradio_device, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		वापस amradio_set_mute(radio, ctrl->val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक usb_amradio_init(काष्ठा amradio_device *radio)
अणु
	पूर्णांक retval;

	retval = amradio_set_mute(radio, true);
	अगर (retval)
		जाओ out_err;
	retval = amradio_set_stereo(radio, true);
	अगर (retval)
		जाओ out_err;
	retval = amradio_set_freq(radio, radio->curfreq);
	अगर (retval)
		जाओ out_err;
	वापस 0;

out_err:
	amradio_dev_err(&radio->vdev.dev, "initialization failed\n");
	वापस retval;
पूर्ण

/* Suspend device - stop device. Need to be checked and fixed */
अटल पूर्णांक usb_amradio_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा amradio_device *radio = to_amradio_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	mutex_lock(&radio->lock);
	अगर (!radio->muted) अणु
		amradio_set_mute(radio, true);
		radio->muted = false;
	पूर्ण
	mutex_unlock(&radio->lock);

	dev_info(&पूर्णांकf->dev, "going into suspend..\n");
	वापस 0;
पूर्ण

/* Resume device - start device. Need to be checked and fixed */
अटल पूर्णांक usb_amradio_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा amradio_device *radio = to_amradio_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	mutex_lock(&radio->lock);
	amradio_set_stereo(radio, radio->stereo);
	amradio_set_freq(radio, radio->curfreq);

	अगर (!radio->muted)
		amradio_set_mute(radio, false);

	mutex_unlock(&radio->lock);

	dev_info(&पूर्णांकf->dev, "coming out of suspend..\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops usb_amradio_ctrl_ops = अणु
	.s_ctrl = usb_amradio_s_ctrl,
पूर्ण;

/* File प्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations usb_amradio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops usb_amradio_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_s_hw_freq_seek = vidioc_s_hw_freq_seek,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल व्योम usb_amradio_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा amradio_device *radio = to_amradio_dev(v4l2_dev);

	/* मुक्त rest memory */
	v4l2_ctrl_handler_मुक्त(&radio->hdl);
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
	kमुक्त(radio->buffer);
	kमुक्त(radio);
पूर्ण

/* check अगर the device is present and रेजिस्टर with v4l and usb अगर it is */
अटल पूर्णांक usb_amradio_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा amradio_device *radio;
	पूर्णांक retval;

	radio = kzalloc(माप(काष्ठा amradio_device), GFP_KERNEL);

	अगर (!radio) अणु
		dev_err(&पूर्णांकf->dev, "kmalloc for amradio_device failed\n");
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	radio->buffer = kदो_स्मृति(BUFFER_LENGTH, GFP_KERNEL);

	अगर (!radio->buffer) अणु
		dev_err(&पूर्णांकf->dev, "kmalloc for radio->buffer failed\n");
		retval = -ENOMEM;
		जाओ err_nobuf;
	पूर्ण

	retval = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &radio->v4l2_dev);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register v4l2_device\n");
		जाओ err_v4l2;
	पूर्ण

	v4l2_ctrl_handler_init(&radio->hdl, 1);
	v4l2_ctrl_new_std(&radio->hdl, &usb_amradio_ctrl_ops,
			  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	अगर (radio->hdl.error) अणु
		retval = radio->hdl.error;
		dev_err(&पूर्णांकf->dev, "couldn't register control\n");
		जाओ err_ctrl;
	पूर्ण
	mutex_init(&radio->lock);

	radio->v4l2_dev.ctrl_handler = &radio->hdl;
	radio->v4l2_dev.release = usb_amradio_release;
	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		माप(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_amradio_fops;
	radio->vdev.ioctl_ops = &usb_amradio_ioctl_ops;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.lock = &radio->lock;
	radio->vdev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER |
				  V4L2_CAP_HW_FREQ_SEEK;

	radio->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	radio->पूर्णांकf = पूर्णांकf;
	usb_set_पूर्णांकfdata(पूर्णांकf, &radio->v4l2_dev);
	radio->curfreq = 95.16 * FREQ_MUL;

	video_set_drvdata(&radio->vdev, radio);
	retval = usb_amradio_init(radio);
	अगर (retval)
		जाओ err_vdev;

	retval = video_रेजिस्टर_device(&radio->vdev, VFL_TYPE_RADIO,
					radio_nr);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "could not register video device\n");
		जाओ err_vdev;
	पूर्ण

	वापस 0;

err_vdev:
	v4l2_ctrl_handler_मुक्त(&radio->hdl);
err_ctrl:
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
err_v4l2:
	kमुक्त(radio->buffer);
err_nobuf:
	kमुक्त(radio);
err:
	वापस retval;
पूर्ण

/* USB Device ID List */
अटल स्थिर काष्ठा usb_device_id usb_amradio_device_table[] = अणु
	अणु USB_DEVICE_AND_INTERFACE_INFO(USB_AMRADIO_VENDOR, USB_AMRADIO_PRODUCT,
							USB_CLASS_HID, 0, 0) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_amradio_device_table);

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver usb_amradio_driver = अणु
	.name			= MR800_DRIVER_NAME,
	.probe			= usb_amradio_probe,
	.disconnect		= usb_amradio_disconnect,
	.suspend		= usb_amradio_suspend,
	.resume			= usb_amradio_resume,
	.reset_resume		= usb_amradio_resume,
	.id_table		= usb_amradio_device_table,
पूर्ण;

module_usb_driver(usb_amradio_driver);
