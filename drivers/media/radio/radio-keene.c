<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2012 Hans Verkuil <hverkuil@xs4all.nl>
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
MODULE_AUTHOR("Hans Verkuil <hverkuil@xs4all.nl>");
MODULE_DESCRIPTION("Keene FM Transmitter driver");
MODULE_LICENSE("GPL");

/* Actually, it advertises itself as a Logitech */
#घोषणा USB_KEENE_VENDOR 0x046d
#घोषणा USB_KEENE_PRODUCT 0x0a0e

/* Probably USB_TIMEOUT should be modअगरied in module parameter */
#घोषणा BUFFER_LENGTH 8
#घोषणा USB_TIMEOUT 500

/* Frequency limits in MHz */
#घोषणा FREQ_MIN  76U
#घोषणा FREQ_MAX 108U
#घोषणा FREQ_MUL 16000U

/* USB Device ID List */
अटल स्थिर काष्ठा usb_device_id usb_keene_device_table[] = अणु
	अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_KEENE_VENDOR, USB_KEENE_PRODUCT,
							USB_CLASS_HID, 0, 0) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_keene_device_table);

काष्ठा keene_device अणु
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा mutex lock;

	u8 *buffer;
	अचिन्हित curfreq;
	u8 tx;
	u8 pa;
	bool stereo;
	bool muted;
	bool preemph_75_us;
पूर्ण;

अटल अंतरभूत काष्ठा keene_device *to_keene_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा keene_device, v4l2_dev);
पूर्ण

/* Set frequency (अगर non-0), PA, mute and turn on/off the FM transmitter. */
अटल पूर्णांक keene_cmd_मुख्य(काष्ठा keene_device *radio, अचिन्हित freq, bool play)
अणु
	अचिन्हित लघु freq_send = freq ? (freq - 76 * 16000) / 800 : 0;
	पूर्णांक ret;

	radio->buffer[0] = 0x00;
	radio->buffer[1] = 0x50;
	radio->buffer[2] = (freq_send >> 8) & 0xff;
	radio->buffer[3] = freq_send & 0xff;
	radio->buffer[4] = radio->pa;
	/* If bit 4 is set, then tune to the frequency.
	   If bit 3 is set, then unmute; अगर bit 2 is set, then mute.
	   If bit 1 is set, then enter idle mode; अगर bit 0 is set,
	   then enter transmit mode.
	 */
	radio->buffer[5] = (radio->muted ? 4 : 8) | (play ? 1 : 2) |
							(freq ? 0x10 : 0);
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	ret = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
		9, 0x21, 0x200, 2, radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);

	अगर (ret < 0) अणु
		dev_warn(&radio->vdev.dev, "%s failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण
	अगर (freq)
		radio->curfreq = freq;
	वापस 0;
पूर्ण

/* Set TX, stereo and preemphasis mode (50 us vs 75 us). */
अटल पूर्णांक keene_cmd_set(काष्ठा keene_device *radio)
अणु
	पूर्णांक ret;

	radio->buffer[0] = 0x00;
	radio->buffer[1] = 0x51;
	radio->buffer[2] = radio->tx;
	/* If bit 0 is set, then transmit mono, otherwise stereo.
	   If bit 2 is set, then enable 75 us preemphasis, otherwise
	   it is 50 us. */
	radio->buffer[3] = (radio->stereo ? 0 : 1) | (radio->preemph_75_us ? 4 : 0);
	radio->buffer[4] = 0x00;
	radio->buffer[5] = 0x00;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	ret = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
		9, 0x21, 0x200, 2, radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);

	अगर (ret < 0) अणु
		dev_warn(&radio->vdev.dev, "%s failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Handle unplugging the device.
 * We call video_unरेजिस्टर_device in any हाल.
 * The last function called in this procedure is
 * usb_keene_device_release.
 */
अटल व्योम usb_keene_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा keene_device *radio = to_keene_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	mutex_lock(&radio->lock);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	video_unरेजिस्टर_device(&radio->vdev);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->lock);
	v4l2_device_put(&radio->v4l2_dev);
पूर्ण

अटल पूर्णांक usb_keene_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा keene_device *radio = to_keene_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	वापस keene_cmd_मुख्य(radio, 0, false);
पूर्ण

अटल पूर्णांक usb_keene_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा keene_device *radio = to_keene_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	mdelay(50);
	keene_cmd_set(radio);
	keene_cmd_मुख्य(radio, radio->curfreq, true);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा keene_device *radio = video_drvdata(file);

	strscpy(v->driver, "radio-keene", माप(v->driver));
	strscpy(v->card, "Keene FM Transmitter", माप(v->card));
	usb_make_path(radio->usbdev, v->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_modulator(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_modulator *v)
अणु
	काष्ठा keene_device *radio = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	strscpy(v->name, "FM", माप(v->name));
	v->rangelow = FREQ_MIN * FREQ_MUL;
	v->rangehigh = FREQ_MAX * FREQ_MUL;
	v->txsubchans = radio->stereo ? V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_modulator(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_modulator *v)
अणु
	काष्ठा keene_device *radio = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	radio->stereo = (v->txsubchans == V4L2_TUNER_SUB_STEREO);
	वापस keene_cmd_set(radio);
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा keene_device *radio = video_drvdata(file);
	अचिन्हित freq = f->frequency;

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;
	freq = clamp(freq, FREQ_MIN * FREQ_MUL, FREQ_MAX * FREQ_MUL);
	वापस keene_cmd_मुख्य(radio, freq, true);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा keene_device *radio = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = radio->curfreq;
	वापस 0;
पूर्ण

अटल पूर्णांक keene_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अटल स्थिर u8 db2tx[] = अणु
	     /*	 -15,  -12,   -9,   -6,   -3,    0 dB */
		0x03, 0x13, 0x02, 0x12, 0x22, 0x32,
	     /*	   3,    6,    9,   12,   15,   18 dB */
		0x21, 0x31, 0x20, 0x30, 0x40, 0x50
	पूर्ण;
	काष्ठा keene_device *radio =
		container_of(ctrl->handler, काष्ठा keene_device, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		radio->muted = ctrl->val;
		वापस keene_cmd_मुख्य(radio, 0, true);

	हाल V4L2_CID_TUNE_POWER_LEVEL:
		/* To go from dBuV to the रेजिस्टर value we apply the
		   following क्रमmula: */
		radio->pa = (ctrl->val - 71) * 100 / 62;
		वापस keene_cmd_मुख्य(radio, 0, true);

	हाल V4L2_CID_TUNE_PREEMPHASIS:
		radio->preemph_75_us = ctrl->val == V4L2_PREEMPHASIS_75_uS;
		वापस keene_cmd_set(radio);

	हाल V4L2_CID_AUDIO_COMPRESSION_GAIN:
		radio->tx = db2tx[(ctrl->val - (s32)ctrl->minimum) / (s32)ctrl->step];
		वापस keene_cmd_set(radio);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* File प्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations usb_keene_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops keene_ctrl_ops = अणु
	.s_ctrl = keene_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops usb_keene_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_modulator = vidioc_g_modulator,
	.vidioc_s_modulator = vidioc_s_modulator,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल व्योम usb_keene_video_device_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा keene_device *radio = to_keene_dev(v4l2_dev);

	/* मुक्त rest memory */
	v4l2_ctrl_handler_मुक्त(&radio->hdl);
	kमुक्त(radio->buffer);
	kमुक्त(radio);
पूर्ण

/* check अगर the device is present and रेजिस्टर with v4l and usb अगर it is */
अटल पूर्णांक usb_keene_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा keene_device *radio;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक retval = 0;

	/*
	 * The Keene FM transmitter USB device has the same USB ID as
	 * the Logitech AudioHub Speaker, but it should ignore the hid.
	 * Check अगर the name is that of the Keene device.
	 * If not, then someone connected the AudioHub and we shouldn't
	 * attempt to handle this driver.
	 * For reference: the product name of the AudioHub is
	 * "AudioHub Speaker".
	 */
	अगर (dev->product && म_भेद(dev->product, "B-LINK USB Audio  "))
		वापस -ENODEV;

	radio = kzalloc(माप(काष्ठा keene_device), GFP_KERNEL);
	अगर (radio)
		radio->buffer = kदो_स्मृति(BUFFER_LENGTH, GFP_KERNEL);

	अगर (!radio || !radio->buffer) अणु
		dev_err(&पूर्णांकf->dev, "kmalloc for keene_device failed\n");
		kमुक्त(radio);
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	hdl = &radio->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &keene_ctrl_ops, V4L2_CID_AUDIO_MUTE,
			0, 1, 1, 0);
	v4l2_ctrl_new_std_menu(hdl, &keene_ctrl_ops, V4L2_CID_TUNE_PREEMPHASIS,
			V4L2_PREEMPHASIS_75_uS, 1, V4L2_PREEMPHASIS_50_uS);
	v4l2_ctrl_new_std(hdl, &keene_ctrl_ops, V4L2_CID_TUNE_POWER_LEVEL,
			84, 118, 1, 118);
	v4l2_ctrl_new_std(hdl, &keene_ctrl_ops, V4L2_CID_AUDIO_COMPRESSION_GAIN,
			-15, 18, 3, 0);
	radio->pa = 118;
	radio->tx = 0x32;
	radio->stereo = true;
	अगर (hdl->error) अणु
		retval = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		जाओ err_v4l2;
	पूर्ण
	retval = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &radio->v4l2_dev);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register v4l2_device\n");
		जाओ err_v4l2;
	पूर्ण

	mutex_init(&radio->lock);

	radio->v4l2_dev.ctrl_handler = hdl;
	radio->v4l2_dev.release = usb_keene_video_device_release;
	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		माप(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_keene_fops;
	radio->vdev.ioctl_ops = &usb_keene_ioctl_ops;
	radio->vdev.lock = &radio->lock;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.vfl_dir = VFL_सूची_TX;
	radio->vdev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_MODULATOR;

	radio->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	radio->पूर्णांकf = पूर्णांकf;
	usb_set_पूर्णांकfdata(पूर्णांकf, &radio->v4l2_dev);

	video_set_drvdata(&radio->vdev, radio);

	/* at least 11ms is needed in order to settle hardware */
	msleep(20);
	keene_cmd_मुख्य(radio, 95.16 * FREQ_MUL, false);

	retval = video_रेजिस्टर_device(&radio->vdev, VFL_TYPE_RADIO, -1);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "could not register video device\n");
		जाओ err_vdev;
	पूर्ण
	v4l2_ctrl_handler_setup(hdl);
	dev_info(&पूर्णांकf->dev, "V4L2 device registered as %s\n",
			video_device_node_name(&radio->vdev));
	वापस 0;

err_vdev:
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
err_v4l2:
	kमुक्त(radio->buffer);
	kमुक्त(radio);
err:
	वापस retval;
पूर्ण

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver usb_keene_driver = अणु
	.name			= "radio-keene",
	.probe			= usb_keene_probe,
	.disconnect		= usb_keene_disconnect,
	.id_table		= usb_keene_device_table,
	.suspend		= usb_keene_suspend,
	.resume			= usb_keene_resume,
	.reset_resume		= usb_keene_resume,
पूर्ण;

module_usb_driver(usb_keene_driver);

