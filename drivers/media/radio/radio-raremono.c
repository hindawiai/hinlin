<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/usb.h>
#समावेश <linux/hid.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>

/*
 * 'Thanko's Raremono' is a Japanese si4734-based AM/FM/SW USB receiver:
 *
 * http://www.raremono.jp/product/484.hपंचांगl/
 *
 * The USB protocol has been reversed engineered using wireshark, initially
 * by Dinesh Ram <dinesh.ram@cern.ch> and finished by Hans Verkuil
 * <hverkuil@xs4all.nl>.
 *
 * Sadly the firmware used in this product hides lots of goodies since the
 * si4734 has more features than are supported by the firmware. Oh well...
 */

/* driver and module definitions */
MODULE_AUTHOR("Hans Verkuil <hverkuil@xs4all.nl>");
MODULE_DESCRIPTION("Thanko's Raremono AM/FM/SW Receiver USB driver");
MODULE_LICENSE("GPL v2");

/*
 * The Device announces itself as Cygnal Integrated Products, Inc.
 *
 * The venकरोr and product IDs (and in fact all other lsusb inक्रमmation as
 * well) are identical to the si470x Silicon Lअसल USB FM Radio Reference
 * Design board, even though this card has a si4734 device. Clearly the
 * designer of this product never bothered to change the USB IDs.
 */

/* USB Device ID List */
अटल स्थिर काष्ठा usb_device_id usb_raremono_device_table[] = अणु
	अणुUSB_DEVICE_AND_INTERFACE_INFO(0x10c4, 0x818a, USB_CLASS_HID, 0, 0) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_raremono_device_table);

#घोषणा BUFFER_LENGTH 64

/* Timeout is set to a high value, could probably be reduced. Need more tests */
#घोषणा USB_TIMEOUT 10000

/* Frequency limits in KHz */
#घोषणा FM_FREQ_RANGE_LOW	64000
#घोषणा FM_FREQ_RANGE_HIGH	108000

#घोषणा AM_FREQ_RANGE_LOW	520
#घोषणा AM_FREQ_RANGE_HIGH	1710

#घोषणा SW_FREQ_RANGE_LOW	2300
#घोषणा SW_FREQ_RANGE_HIGH	26100

क्रमागत अणु BAND_FM, BAND_AM, BAND_SW पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands[] = अणु
	/* Band FM */
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 0,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			      V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = FM_FREQ_RANGE_LOW * 16,
		.rangehigh  = FM_FREQ_RANGE_HIGH * 16,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
	/* Band AM */
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 1,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = AM_FREQ_RANGE_LOW * 16,
		.rangehigh  = AM_FREQ_RANGE_HIGH * 16,
		.modulation = V4L2_BAND_MODULATION_AM,
	पूर्ण,
	/* Band SW */
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 2,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = SW_FREQ_RANGE_LOW * 16,
		.rangehigh  = SW_FREQ_RANGE_HIGH * 16,
		.modulation = V4L2_BAND_MODULATION_AM,
	पूर्ण,
पूर्ण;

काष्ठा raremono_device अणु
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा mutex lock;

	u8 *buffer;
	u32 band;
	अचिन्हित curfreq;
पूर्ण;

अटल अंतरभूत काष्ठा raremono_device *to_raremono_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा raremono_device, v4l2_dev);
पूर्ण

/* Set frequency. */
अटल पूर्णांक raremono_cmd_मुख्य(काष्ठा raremono_device *radio, अचिन्हित band, अचिन्हित freq)
अणु
	अचिन्हित band_offset;
	पूर्णांक ret;

	चयन (band) अणु
	हाल BAND_FM:
		band_offset = 1;
		freq /= 10;
		अवरोध;
	हाल BAND_AM:
		band_offset = 0;
		अवरोध;
	शेष:
		band_offset = 2;
		अवरोध;
	पूर्ण
	radio->buffer[0] = 0x04 + band_offset;
	radio->buffer[1] = freq >> 8;
	radio->buffer[2] = freq & 0xff;

	ret = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
			HID_REQ_SET_REPORT,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
			0x0300 + radio->buffer[0], 2,
			radio->buffer, 3, USB_TIMEOUT);

	अगर (ret < 0) अणु
		dev_warn(radio->v4l2_dev.dev, "%s failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण
	radio->curfreq = (band == BAND_FM) ? freq * 10 : freq;
	वापस 0;
पूर्ण

/* Handle unplugging the device.
 * We call video_unरेजिस्टर_device in any हाल.
 * The last function called in this procedure is
 * usb_raremono_device_release.
 */
अटल व्योम usb_raremono_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा raremono_device *radio = to_raremono_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	dev_info(&पूर्णांकf->dev, "Thanko's Raremono disconnected\n");

	mutex_lock(&radio->lock);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	video_unरेजिस्टर_device(&radio->vdev);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->lock);
	v4l2_device_put(&radio->v4l2_dev);
पूर्ण

/*
 * Linux Video पूर्णांकerface
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा raremono_device *radio = video_drvdata(file);

	strscpy(v->driver, "radio-raremono", माप(v->driver));
	strscpy(v->card, "Thanko's Raremono", माप(v->card));
	usb_make_path(radio->usbdev, v->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency_band *band)
अणु
	अगर (band->tuner != 0)
		वापस -EINVAL;

	अगर (band->index >= ARRAY_SIZE(bands))
		वापस -EINVAL;

	*band = bands[band->index];

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_tuner *v)
अणु
	काष्ठा raremono_device *radio = video_drvdata(file);
	पूर्णांक ret;

	अगर (v->index > 0)
		वापस -EINVAL;

	strscpy(v->name, "AM/FM/SW", माप(v->name));
	v->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_FREQ_BANDS;
	v->rangelow = AM_FREQ_RANGE_LOW * 16;
	v->rangehigh = FM_FREQ_RANGE_HIGH * 16;
	v->rxsubchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_MONO;
	v->audmode = (radio->curfreq < FM_FREQ_RANGE_LOW) ?
		V4L2_TUNER_MODE_MONO : V4L2_TUNER_MODE_STEREO;
	स_रखो(radio->buffer, 1, BUFFER_LENGTH);
	ret = usb_control_msg(radio->usbdev, usb_rcvctrlpipe(radio->usbdev, 0),
			1, 0xa1, 0x030d, 2, radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);

	अगर (ret < 0) अणु
		dev_warn(radio->v4l2_dev.dev, "%s failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण
	v->संकेत = ((radio->buffer[1] & 0xf) << 8 | radio->buffer[2]) << 4;
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
	काष्ठा raremono_device *radio = video_drvdata(file);
	u32 freq;
	अचिन्हित band;

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	अगर (f->frequency >= (FM_FREQ_RANGE_LOW + SW_FREQ_RANGE_HIGH) * 8)
		band = BAND_FM;
	अन्यथा अगर (f->frequency <= (AM_FREQ_RANGE_HIGH + SW_FREQ_RANGE_LOW) * 8)
		band = BAND_AM;
	अन्यथा
		band = BAND_SW;

	freq = clamp_t(u32, f->frequency, bands[band].rangelow, bands[band].rangehigh);
	वापस raremono_cmd_मुख्य(radio, band, freq / 16);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा raremono_device *radio = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = radio->curfreq * 16;
	वापस 0;
पूर्ण

अटल व्योम raremono_device_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा raremono_device *radio = to_raremono_dev(v4l2_dev);

	kमुक्त(radio->buffer);
	kमुक्त(radio);
पूर्ण

/* File प्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations usb_raremono_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = v4l2_fh_release,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops usb_raremono_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,
	.vidioc_g_tuner = vidioc_g_tuner,
	.vidioc_s_tuner = vidioc_s_tuner,
	.vidioc_g_frequency = vidioc_g_frequency,
	.vidioc_s_frequency = vidioc_s_frequency,
	.vidioc_क्रमागत_freq_bands = vidioc_क्रमागत_freq_bands,
पूर्ण;

/* check अगर the device is present and रेजिस्टर with v4l and usb अगर it is */
अटल पूर्णांक usb_raremono_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा raremono_device *radio;
	पूर्णांक retval = 0;

	radio = kzalloc(माप(*radio), GFP_KERNEL);
	अगर (!radio)
		वापस -ENOMEM;
	radio->buffer = kदो_स्मृति(BUFFER_LENGTH, GFP_KERNEL);
	अगर (!radio->buffer) अणु
		kमुक्त(radio);
		वापस -ENOMEM;
	पूर्ण

	radio->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	radio->पूर्णांकf = पूर्णांकf;

	/*
	 * This device uses the same USB IDs as the si470x SiLअसल reference
	 * design. So करो an additional check: attempt to पढ़ो the device ID
	 * from the si470x: the lower 12 bits are 0x0242 क्रम the si470x. The
	 * Raremono always वापसs 0x0800 (the meaning of that is unknown, but
	 * at least it works).
	 *
	 * We use this check to determine which device we are dealing with.
	 */
	msleep(20);
	retval = usb_control_msg(radio->usbdev,
		usb_rcvctrlpipe(radio->usbdev, 0),
		HID_REQ_GET_REPORT,
		USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
		1, 2,
		radio->buffer, 3, 500);
	अगर (retval != 3 ||
	    (get_unaligned_be16(&radio->buffer[1]) & 0xfff) == 0x0242) अणु
		dev_info(&पूर्णांकf->dev, "this is not Thanko's Raremono.\n");
		retval = -ENODEV;
		जाओ मुक्त_mem;
	पूर्ण

	dev_info(&पूर्णांकf->dev, "Thanko's Raremono connected: (%04X:%04X)\n",
			id->idVenकरोr, id->idProduct);

	retval = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &radio->v4l2_dev);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register v4l2_device\n");
		जाओ मुक्त_mem;
	पूर्ण

	mutex_init(&radio->lock);

	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		माप(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_raremono_fops;
	radio->vdev.ioctl_ops = &usb_raremono_ioctl_ops;
	radio->vdev.lock = &radio->lock;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;
	radio->v4l2_dev.release = raremono_device_release;

	usb_set_पूर्णांकfdata(पूर्णांकf, &radio->v4l2_dev);

	video_set_drvdata(&radio->vdev, radio);

	raremono_cmd_मुख्य(radio, BAND_FM, 95160);

	retval = video_रेजिस्टर_device(&radio->vdev, VFL_TYPE_RADIO, -1);
	अगर (retval == 0) अणु
		dev_info(&पूर्णांकf->dev, "V4L2 device registered as %s\n",
				video_device_node_name(&radio->vdev));
		वापस 0;
	पूर्ण
	dev_err(&पूर्णांकf->dev, "could not register video device\n");
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);

मुक्त_mem:
	kमुक्त(radio->buffer);
	kमुक्त(radio);
	वापस retval;
पूर्ण

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver usb_raremono_driver = अणु
	.name			= "radio-raremono",
	.probe			= usb_raremono_probe,
	.disconnect		= usb_raremono_disconnect,
	.id_table		= usb_raremono_device_table,
पूर्ण;

module_usb_driver(usb_raremono_driver);
