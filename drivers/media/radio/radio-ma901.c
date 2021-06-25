<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the MasterKit MA901 USB FM radio. This device plugs
 * पूर्णांकo the USB port and an analog audio input or headphones, so this thing
 * only deals with initialization, frequency setting, volume.
 *
 * Copyright (c) 2012 Alexey Klimov <klimov.linux@gmail.com>
 */

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

#घोषणा DRIVER_AUTHOR "Alexey Klimov <klimov.linux@gmail.com>"
#घोषणा DRIVER_DESC "Masterkit MA901 USB FM radio driver"
#घोषणा DRIVER_VERSION "0.0.1"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

#घोषणा USB_MA901_VENDOR  0x16c0
#घोषणा USB_MA901_PRODUCT 0x05df

/* dev_warn macro with driver name */
#घोषणा MA901_DRIVER_NAME "radio-ma901"
#घोषणा ma901radio_dev_warn(dev, fmt, arg...)				\
		dev_warn(dev, MA901_DRIVER_NAME " - " fmt, ##arg)

#घोषणा ma901radio_dev_err(dev, fmt, arg...) \
		dev_err(dev, MA901_DRIVER_NAME " - " fmt, ##arg)

/* Probably USB_TIMEOUT should be modअगरied in module parameter */
#घोषणा BUFFER_LENGTH 8
#घोषणा USB_TIMEOUT 500

#घोषणा FREQ_MIN  87.5
#घोषणा FREQ_MAX 108.0
#घोषणा FREQ_MUL 16000

#घोषणा MA901_VOLUME_MAX 16
#घोषणा MA901_VOLUME_MIN 0

/* Commands that device should understand
 * List isn't full and will be updated with implementation of new functions
 */
#घोषणा MA901_RADIO_SET_FREQ		0x03
#घोषणा MA901_RADIO_SET_VOLUME		0x04
#घोषणा MA901_RADIO_SET_MONO_STEREO	0x05

/* Comक्रमtable defines क्रम ma901radio_set_stereo */
#घोषणा MA901_WANT_STEREO		0x50
#घोषणा MA901_WANT_MONO			0xd0

/* module parameter */
अटल पूर्णांक radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0);
MODULE_PARM_DESC(radio_nr, "Radio file number");

/* Data क्रम one (physical) device */
काष्ठा ma901radio_device अणु
	/* reference to USB and video device */
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;

	u8 *buffer;
	काष्ठा mutex lock;	/* buffer locking */
	पूर्णांक curfreq;
	u16 volume;
	पूर्णांक stereo;
	bool muted;
पूर्ण;

अटल अंतरभूत काष्ठा ma901radio_device *to_ma901radio_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा ma901radio_device, v4l2_dev);
पूर्ण

/* set a frequency, freq is defined by v4l's TUNER_LOW, i.e. 1/16th kHz */
अटल पूर्णांक ma901radio_set_freq(काष्ठा ma901radio_device *radio, पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक freq_send = 0x300 + (freq >> 5) / 25;
	पूर्णांक retval;

	radio->buffer[0] = 0x0a;
	radio->buffer[1] = MA901_RADIO_SET_FREQ;
	radio->buffer[2] = ((freq_send >> 8) & 0xff) + 0x80;
	radio->buffer[3] = freq_send & 0xff;
	radio->buffer[4] = 0x00;
	radio->buffer[5] = 0x00;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);
	अगर (retval < 0)
		वापस retval;

	radio->curfreq = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक ma901radio_set_volume(काष्ठा ma901radio_device *radio, u16 vol_to_set)
अणु
	पूर्णांक retval;

	radio->buffer[0] = 0x0a;
	radio->buffer[1] = MA901_RADIO_SET_VOLUME;
	radio->buffer[2] = 0xc2;
	radio->buffer[3] = vol_to_set + 0x20;
	radio->buffer[4] = 0x00;
	radio->buffer[5] = 0x00;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);
	अगर (retval < 0)
		वापस retval;

	radio->volume = vol_to_set;
	वापस retval;
पूर्ण

अटल पूर्णांक ma901_set_stereo(काष्ठा ma901radio_device *radio, u8 stereo)
अणु
	पूर्णांक retval;

	radio->buffer[0] = 0x0a;
	radio->buffer[1] = MA901_RADIO_SET_MONO_STEREO;
	radio->buffer[2] = stereo;
	radio->buffer[3] = 0x00;
	radio->buffer[4] = 0x00;
	radio->buffer[5] = 0x00;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);

	अगर (retval < 0)
		वापस retval;

	अगर (stereo == MA901_WANT_STEREO)
		radio->stereo = V4L2_TUNER_MODE_STEREO;
	अन्यथा
		radio->stereo = V4L2_TUNER_MODE_MONO;

	वापस retval;
पूर्ण

/* Handle unplugging the device.
 * We call video_unरेजिस्टर_device in any हाल.
 * The last function called in this procedure is
 * usb_ma901radio_device_release.
 */
अटल व्योम usb_ma901radio_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ma901radio_device *radio = to_ma901radio_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	mutex_lock(&radio->lock);
	video_unरेजिस्टर_device(&radio->vdev);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->lock);
	v4l2_device_put(&radio->v4l2_dev);
पूर्ण

/* vidioc_querycap - query device capabilities */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा ma901radio_device *radio = video_drvdata(file);

	strscpy(v->driver, "radio-ma901", माप(v->driver));
	strscpy(v->card, "Masterkit MA901 USB FM Radio", माप(v->card));
	usb_make_path(radio->usbdev, v->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

/* vidioc_g_tuner - get tuner attributes */
अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *v)
अणु
	काष्ठा ma901radio_device *radio = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	v->संकेत = 0;

	/* TODO: the same words like in _probe() goes here.
	 * When receiving of stats will be implemented then we can call
	 * ma901radio_get_stat().
	 * retval = ma901radio_get_stat(radio, &is_stereo, &v->संकेत);
	 */

	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = FREQ_MIN * FREQ_MUL;
	v->rangehigh = FREQ_MAX * FREQ_MUL;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO;
	/* v->rxsubchans = is_stereo ? V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO; */
	v->audmode = radio->stereo ?
		V4L2_TUNER_MODE_STEREO : V4L2_TUNER_MODE_MONO;
	वापस 0;
पूर्ण

/* vidioc_s_tuner - set tuner attributes */
अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा ma901radio_device *radio = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	/* mono/stereo selector */
	चयन (v->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		वापस ma901_set_stereo(radio, MA901_WANT_MONO);
	शेष:
		वापस ma901_set_stereo(radio, MA901_WANT_STEREO);
	पूर्ण
पूर्ण

/* vidioc_s_frequency - set tuner radio frequency */
अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा ma901radio_device *radio = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;

	वापस ma901radio_set_freq(radio, clamp_t(अचिन्हित, f->frequency,
				FREQ_MIN * FREQ_MUL, FREQ_MAX * FREQ_MUL));
पूर्ण

/* vidioc_g_frequency - get tuner radio frequency */
अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा ma901radio_device *radio = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->frequency = radio->curfreq;

	वापस 0;
पूर्ण

अटल पूर्णांक usb_ma901radio_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ma901radio_device *radio =
		container_of(ctrl->handler, काष्ठा ma901radio_device, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_VOLUME:     /* set volume */
		वापस ma901radio_set_volume(radio, (u16)ctrl->val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* TODO: Should we really need to implement suspend and resume functions?
 * Radio has it's own memory and will जारी playing अगर घातer is present
 * on usb port and on resume it will start to play again based on freq, volume
 * values in device memory.
 */
अटल पूर्णांक usb_ma901radio_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक usb_ma901radio_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops usb_ma901radio_ctrl_ops = अणु
	.s_ctrl = usb_ma901radio_s_ctrl,
पूर्ण;

/* File प्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations usb_ma901radio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops usb_ma901radio_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल व्योम usb_ma901radio_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा ma901radio_device *radio = to_ma901radio_dev(v4l2_dev);

	v4l2_ctrl_handler_मुक्त(&radio->hdl);
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
	kमुक्त(radio->buffer);
	kमुक्त(radio);
पूर्ण

/* check अगर the device is present and रेजिस्टर with v4l and usb अगर it is */
अटल पूर्णांक usb_ma901radio_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा ma901radio_device *radio;
	पूर्णांक retval = 0;

	/* Masterkit MA901 usb radio has the same USB ID as many others
	 * Aपंचांगel V-USB devices. Let's make additional checks to be sure
	 * that this is our device.
	 */

	अगर (dev->product && dev->manufacturer &&
		(म_भेदन(dev->product, "MA901", 5) != 0
		|| म_भेदन(dev->manufacturer, "www.masterkit.ru", 16) != 0))
		वापस -ENODEV;

	radio = kzalloc(माप(काष्ठा ma901radio_device), GFP_KERNEL);
	अगर (!radio) अणु
		dev_err(&पूर्णांकf->dev, "kzalloc for ma901radio_device failed\n");
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

	/* TODO:It looks like this radio करोesn't have mute/unmute control
	 * and winकरोws program just emulate it using volume control.
	 * Let's plan to करो the same in this driver.
	 *
	 * v4l2_ctrl_new_std(&radio->hdl, &usb_ma901radio_ctrl_ops,
	 *		  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	 */

	v4l2_ctrl_new_std(&radio->hdl, &usb_ma901radio_ctrl_ops,
			  V4L2_CID_AUDIO_VOLUME, MA901_VOLUME_MIN,
			  MA901_VOLUME_MAX, 1, MA901_VOLUME_MAX);

	अगर (radio->hdl.error) अणु
		retval = radio->hdl.error;
		dev_err(&पूर्णांकf->dev, "couldn't register control\n");
		जाओ err_ctrl;
	पूर्ण
	mutex_init(&radio->lock);

	radio->v4l2_dev.ctrl_handler = &radio->hdl;
	radio->v4l2_dev.release = usb_ma901radio_release;
	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		माप(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_ma901radio_fops;
	radio->vdev.ioctl_ops = &usb_ma901radio_ioctl_ops;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.lock = &radio->lock;
	radio->vdev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;

	radio->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	radio->पूर्णांकf = पूर्णांकf;
	usb_set_पूर्णांकfdata(पूर्णांकf, &radio->v4l2_dev);
	radio->curfreq = 95.21 * FREQ_MUL;

	video_set_drvdata(&radio->vdev, radio);

	/* TODO: we can get some statistics (freq, volume) from device
	 * but it's not implemented yet. After insertion in usb-port radio
	 * setups frequency and starts playing without any initialization.
	 * So we करोn't call usb_ma901radio_init/get_stat() here.
	 * retval = usb_ma901radio_init(radio);
	 */

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
अटल स्थिर काष्ठा usb_device_id usb_ma901radio_device_table[] = अणु
	अणु USB_DEVICE_AND_INTERFACE_INFO(USB_MA901_VENDOR, USB_MA901_PRODUCT,
							USB_CLASS_HID, 0, 0) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_ma901radio_device_table);

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver usb_ma901radio_driver = अणु
	.name			= MA901_DRIVER_NAME,
	.probe			= usb_ma901radio_probe,
	.disconnect		= usb_ma901radio_disconnect,
	.suspend		= usb_ma901radio_suspend,
	.resume			= usb_ma901radio_resume,
	.reset_resume		= usb_ma901radio_resume,
	.id_table		= usb_ma901radio_device_table,
पूर्ण;

module_usb_driver(usb_ma901radio_driver);
