<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* A driver क्रम the D-Link DSB-R100 USB radio and Gemtek USB Radio 21.
 * The device plugs पूर्णांकo both the USB and an analog audio input, so this thing
 * only deals with initialisation and frequency setting, the
 * audio data has to be handled by a sound driver.
 *
 * Major issue: I can't find out where the device reports the संकेत
 * strength, and indeed the winकरोws software appearantly just looks
 * at the stereo indicator as well.  So, scanning will only find
 * stereo stations.  Sad, but I can't help it.
 *
 * Also, the winकरोws program sends oodles of messages over to the
 * device, and I couldn't figure out their meaning.  My suspicion
 * is that they करोn't have any:-)
 *
 * You might find some पूर्णांकeresting stuff about this module at
 * http://unimut.fsk.uni-heidelberg.de/unimut/demi/dsbr
 *
 * Fully tested with the Keene USB FM Transmitter and the v4l2-compliance tool.
 *
 * Copyright (c) 2000 Markus Demleitner <msdemlei@cl.uni-heidelberg.de>
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/usb.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>

/*
 * Version Inक्रमmation
 */
MODULE_AUTHOR("Markus Demleitner <msdemlei@tucana.harvard.edu>");
MODULE_DESCRIPTION("D-Link DSB-R100 USB FM radio driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1.0");

#घोषणा DSB100_VENDOR 0x04b4
#घोषणा DSB100_PRODUCT 0x1002

/* Commands the device appears to understand */
#घोषणा DSB100_TUNE 1
#घोषणा DSB100_ONOFF 2

#घोषणा TB_LEN 16

/* Frequency limits in MHz -- these are European values.  For Japanese
devices, that would be 76 and 91.  */
#घोषणा FREQ_MIN  87.5
#घोषणा FREQ_MAX 108.0
#घोषणा FREQ_MUL 16000

#घोषणा v4l2_dev_to_radio(d) container_of(d, काष्ठा dsbr100_device, v4l2_dev)

अटल पूर्णांक radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0);

/* Data क्रम one (physical) device */
काष्ठा dsbr100_device अणु
	काष्ठा usb_device *usbdev;
	काष्ठा video_device videodev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;

	u8 *transfer_buffer;
	काष्ठा mutex v4l2_lock;
	पूर्णांक curfreq;
	bool stereo;
	bool muted;
पूर्ण;

/* Low-level device पूर्णांकerface begins here */

/* set a frequency, freq is defined by v4l's TUNER_LOW, i.e. 1/16th kHz */
अटल पूर्णांक dsbr100_setfreq(काष्ठा dsbr100_device *radio, अचिन्हित freq)
अणु
	अचिन्हित f = (freq / 16 * 80) / 1000 + 856;
	पूर्णांक retval = 0;

	अगर (!radio->muted) अणु
		retval = usb_control_msg(radio->usbdev,
				usb_rcvctrlpipe(radio->usbdev, 0),
				DSB100_TUNE,
				USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
				(f >> 8) & 0x00ff, f & 0xff,
				radio->transfer_buffer, 8, 300);
		अगर (retval >= 0)
			mdelay(1);
	पूर्ण

	अगर (retval >= 0) अणु
		radio->curfreq = freq;
		वापस 0;
	पूर्ण
	dev_err(&radio->usbdev->dev,
		"%s - usb_control_msg returned %i, request %i\n",
			__func__, retval, DSB100_TUNE);
	वापस retval;
पूर्ण

/* चयन on radio */
अटल पूर्णांक dsbr100_start(काष्ठा dsbr100_device *radio)
अणु
	पूर्णांक retval = usb_control_msg(radio->usbdev,
		usb_rcvctrlpipe(radio->usbdev, 0),
		DSB100_ONOFF,
		USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
		0x01, 0x00, radio->transfer_buffer, 8, 300);

	अगर (retval >= 0)
		वापस dsbr100_setfreq(radio, radio->curfreq);
	dev_err(&radio->usbdev->dev,
		"%s - usb_control_msg returned %i, request %i\n",
			__func__, retval, DSB100_ONOFF);
	वापस retval;

पूर्ण

/* चयन off radio */
अटल पूर्णांक dsbr100_stop(काष्ठा dsbr100_device *radio)
अणु
	पूर्णांक retval = usb_control_msg(radio->usbdev,
		usb_rcvctrlpipe(radio->usbdev, 0),
		DSB100_ONOFF,
		USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
		0x00, 0x00, radio->transfer_buffer, 8, 300);

	अगर (retval >= 0)
		वापस 0;
	dev_err(&radio->usbdev->dev,
		"%s - usb_control_msg returned %i, request %i\n",
			__func__, retval, DSB100_ONOFF);
	वापस retval;

पूर्ण

/* वापस the device status.  This is, in effect, just whether it
sees a stereo संकेत or not.  Pity. */
अटल व्योम dsbr100_माला_लोtat(काष्ठा dsbr100_device *radio)
अणु
	पूर्णांक retval = usb_control_msg(radio->usbdev,
		usb_rcvctrlpipe(radio->usbdev, 0),
		USB_REQ_GET_STATUS,
		USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
		0x00, 0x24, radio->transfer_buffer, 8, 300);

	अगर (retval < 0) अणु
		radio->stereo = false;
		dev_err(&radio->usbdev->dev,
			"%s - usb_control_msg returned %i, request %i\n",
				__func__, retval, USB_REQ_GET_STATUS);
	पूर्ण अन्यथा अणु
		radio->stereo = !(radio->transfer_buffer[0] & 0x01);
	पूर्ण
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा dsbr100_device *radio = video_drvdata(file);

	strscpy(v->driver, "dsbr100", माप(v->driver));
	strscpy(v->card, "D-Link R-100 USB FM Radio", माप(v->card));
	usb_make_path(radio->usbdev, v->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *v)
अणु
	काष्ठा dsbr100_device *radio = video_drvdata(file);

	अगर (v->index > 0)
		वापस -EINVAL;

	dsbr100_माला_लोtat(radio);
	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = FREQ_MIN * FREQ_MUL;
	v->rangehigh = FREQ_MAX * FREQ_MUL;
	v->rxsubchans = radio->stereo ? V4L2_TUNER_SUB_STEREO :
		V4L2_TUNER_SUB_MONO;
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO;
	v->audmode = V4L2_TUNER_MODE_STEREO;
	v->संकेत = radio->stereo ? 0xffff : 0;     /* We can't get the संकेत strength */
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *v)
अणु
	वापस v->index ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा dsbr100_device *radio = video_drvdata(file);

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	वापस dsbr100_setfreq(radio, clamp_t(अचिन्हित, f->frequency,
			FREQ_MIN * FREQ_MUL, FREQ_MAX * FREQ_MUL));
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा dsbr100_device *radio = video_drvdata(file);

	अगर (f->tuner)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = radio->curfreq;
	वापस 0;
पूर्ण

अटल पूर्णांक usb_dsbr100_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा dsbr100_device *radio =
		container_of(ctrl->handler, काष्ठा dsbr100_device, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		radio->muted = ctrl->val;
		वापस radio->muted ? dsbr100_stop(radio) : dsbr100_start(radio);
	पूर्ण
	वापस -EINVAL;
पूर्ण


/* USB subप्रणाली पूर्णांकerface begins here */

/*
 * Handle unplugging of the device.
 * We call video_unरेजिस्टर_device in any हाल.
 * The last function called in this procedure is
 * usb_dsbr100_video_device_release
 */
अटल व्योम usb_dsbr100_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dsbr100_device *radio = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&radio->v4l2_lock);
	/*
	 * Disconnect is also called on unload, and in that हाल we need to
	 * mute the device. This call will silently fail अगर it is called
	 * after a physical disconnect.
	 */
	usb_control_msg(radio->usbdev,
		usb_rcvctrlpipe(radio->usbdev, 0),
		DSB100_ONOFF,
		USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
		0x00, 0x00, radio->transfer_buffer, 8, 300);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	video_unरेजिस्टर_device(&radio->videodev);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->v4l2_lock);
	v4l2_device_put(&radio->v4l2_dev);
पूर्ण


/* Suspend device - stop device. */
अटल पूर्णांक usb_dsbr100_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा dsbr100_device *radio = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&radio->v4l2_lock);
	अगर (!radio->muted && dsbr100_stop(radio) < 0)
		dev_warn(&पूर्णांकf->dev, "dsbr100_stop failed\n");
	mutex_unlock(&radio->v4l2_lock);

	dev_info(&पूर्णांकf->dev, "going into suspend..\n");
	वापस 0;
पूर्ण

/* Resume device - start device. */
अटल पूर्णांक usb_dsbr100_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dsbr100_device *radio = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&radio->v4l2_lock);
	अगर (!radio->muted && dsbr100_start(radio) < 0)
		dev_warn(&पूर्णांकf->dev, "dsbr100_start failed\n");
	mutex_unlock(&radio->v4l2_lock);

	dev_info(&पूर्णांकf->dev, "coming out of suspend..\n");
	वापस 0;
पूर्ण

/* मुक्त data काष्ठाures */
अटल व्योम usb_dsbr100_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा dsbr100_device *radio = v4l2_dev_to_radio(v4l2_dev);

	v4l2_ctrl_handler_मुक्त(&radio->hdl);
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
	kमुक्त(radio->transfer_buffer);
	kमुक्त(radio);
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops usb_dsbr100_ctrl_ops = अणु
	.s_ctrl = usb_dsbr100_s_ctrl,
पूर्ण;

/* File प्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations usb_dsbr100_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= video_ioctl2,
	.खोलो           = v4l2_fh_खोलो,
	.release        = v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops usb_dsbr100_ioctl_ops = अणु
	.vidioc_querycap    = vidioc_querycap,
	.vidioc_g_tuner     = vidioc_g_tuner,
	.vidioc_s_tuner     = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/* check अगर the device is present and रेजिस्टर with v4l and usb अगर it is */
अटल पूर्णांक usb_dsbr100_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा dsbr100_device *radio;
	काष्ठा v4l2_device *v4l2_dev;
	पूर्णांक retval;

	radio = kzalloc(माप(काष्ठा dsbr100_device), GFP_KERNEL);

	अगर (!radio)
		वापस -ENOMEM;

	radio->transfer_buffer = kदो_स्मृति(TB_LEN, GFP_KERNEL);

	अगर (!(radio->transfer_buffer)) अणु
		kमुक्त(radio);
		वापस -ENOMEM;
	पूर्ण

	v4l2_dev = &radio->v4l2_dev;
	v4l2_dev->release = usb_dsbr100_release;

	retval = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, v4l2_dev);
	अगर (retval < 0) अणु
		v4l2_err(v4l2_dev, "couldn't register v4l2_device\n");
		जाओ err_reg_dev;
	पूर्ण

	v4l2_ctrl_handler_init(&radio->hdl, 1);
	v4l2_ctrl_new_std(&radio->hdl, &usb_dsbr100_ctrl_ops,
			  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	अगर (radio->hdl.error) अणु
		retval = radio->hdl.error;
		v4l2_err(v4l2_dev, "couldn't register control\n");
		जाओ err_reg_ctrl;
	पूर्ण
	mutex_init(&radio->v4l2_lock);
	strscpy(radio->videodev.name, v4l2_dev->name,
		माप(radio->videodev.name));
	radio->videodev.v4l2_dev = v4l2_dev;
	radio->videodev.fops = &usb_dsbr100_fops;
	radio->videodev.ioctl_ops = &usb_dsbr100_ioctl_ops;
	radio->videodev.release = video_device_release_empty;
	radio->videodev.lock = &radio->v4l2_lock;
	radio->videodev.ctrl_handler = &radio->hdl;
	radio->videodev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;

	radio->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	radio->curfreq = FREQ_MIN * FREQ_MUL;
	radio->muted = true;

	video_set_drvdata(&radio->videodev, radio);
	usb_set_पूर्णांकfdata(पूर्णांकf, radio);

	retval = video_रेजिस्टर_device(&radio->videodev, VFL_TYPE_RADIO, radio_nr);
	अगर (retval == 0)
		वापस 0;
	v4l2_err(v4l2_dev, "couldn't register video device\n");

err_reg_ctrl:
	v4l2_ctrl_handler_मुक्त(&radio->hdl);
	v4l2_device_unरेजिस्टर(v4l2_dev);
err_reg_dev:
	kमुक्त(radio->transfer_buffer);
	kमुक्त(radio);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा usb_device_id usb_dsbr100_device_table[] = अणु
	अणु USB_DEVICE(DSB100_VENDOR, DSB100_PRODUCT) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_dsbr100_device_table);

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver usb_dsbr100_driver = अणु
	.name			= "dsbr100",
	.probe			= usb_dsbr100_probe,
	.disconnect		= usb_dsbr100_disconnect,
	.id_table		= usb_dsbr100_device_table,
	.suspend		= usb_dsbr100_suspend,
	.resume			= usb_dsbr100_resume,
	.reset_resume		= usb_dsbr100_resume,
पूर्ण;

module_usb_driver(usb_dsbr100_driver);
