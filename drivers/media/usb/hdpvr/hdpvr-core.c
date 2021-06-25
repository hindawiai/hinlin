<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hauppauge HD PVR USB driver
 *
 * Copyright (C) 2001-2004 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2008      Janne Grunau (j@jannau.net)
 * Copyright (C) 2008      John Poet
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-common.h>

#समावेश "hdpvr.h"

अटल पूर्णांक video_nr[HDPVR_MAX] = अणु[0 ... (HDPVR_MAX - 1)] = UNSETपूर्ण;
module_param_array(video_nr, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(video_nr, "video device number (-1=Auto)");

/* holds the number of currently रेजिस्टरed devices */
अटल atomic_t dev_nr = ATOMIC_INIT(-1);

पूर्णांक hdpvr_debug;
module_param(hdpvr_debug, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(hdpvr_debug, "enable debugging output");

अटल uपूर्णांक शेष_video_input = HDPVR_VIDEO_INPUTS;
module_param(शेष_video_input, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(शेष_video_input, "default video input: 0=Component / 1=S-Video / 2=Composite");

अटल uपूर्णांक शेष_audio_input = HDPVR_AUDIO_INPUTS;
module_param(शेष_audio_input, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(शेष_audio_input, "default audio input: 0=RCA back / 1=RCA front / 2=S/PDIF");

अटल bool boost_audio;
module_param(boost_audio, bool, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(boost_audio, "boost the audio signal");


/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id hdpvr_table[] = अणु
	अणु USB_DEVICE(HD_PVR_VENDOR_ID, HD_PVR_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(HD_PVR_VENDOR_ID, HD_PVR_PRODUCT_ID1) पूर्ण,
	अणु USB_DEVICE(HD_PVR_VENDOR_ID, HD_PVR_PRODUCT_ID2) पूर्ण,
	अणु USB_DEVICE(HD_PVR_VENDOR_ID, HD_PVR_PRODUCT_ID3) पूर्ण,
	अणु USB_DEVICE(HD_PVR_VENDOR_ID, HD_PVR_PRODUCT_ID4) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, hdpvr_table);


व्योम hdpvr_delete(काष्ठा hdpvr_device *dev)
अणु
	hdpvr_मुक्त_buffers(dev);
	usb_put_dev(dev->udev);
पूर्ण

अटल व्योम challenge(u8 *bytes)
अणु
	__le64 *i64P;
	u64 पंचांगp64;
	uपूर्णांक i, idx;

	क्रम (idx = 0; idx < 32; ++idx) अणु

		अगर (idx & 0x3)
			bytes[(idx >> 3) + 3] = bytes[(idx >> 2) & 0x3];

		चयन (idx & 0x3) अणु
		हाल 0x3:
			bytes[2] += bytes[3] * 4 + bytes[4] + bytes[5];
			bytes[4] += bytes[(idx & 0x1) * 2] * 9 + 9;
			अवरोध;
		हाल 0x1:
			bytes[0] *= 8;
			bytes[0] += 7*idx + 4;
			bytes[6] += bytes[3] * 3;
			अवरोध;
		हाल 0x0:
			bytes[3 - (idx >> 3)] = bytes[idx >> 2];
			bytes[5] += bytes[6] * 3;
			क्रम (i = 0; i < 3; i++)
				bytes[3] *= bytes[3] + 1;
			अवरोध;
		हाल 0x2:
			क्रम (i = 0; i < 3; i++)
				bytes[1] *= bytes[6] + 1;
			क्रम (i = 0; i < 3; i++) अणु
				i64P = (__le64 *)bytes;
				पंचांगp64 = le64_to_cpup(i64P);
				पंचांगp64 = पंचांगp64 + (पंचांगp64 << (bytes[7] & 0x0f));
				*i64P = cpu_to_le64(पंचांगp64);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* try to init the device like the winकरोws driver */
अटल पूर्णांक device_authorization(काष्ठा hdpvr_device *dev)
अणु

	पूर्णांक ret, retval = -ENOMEM;
	अक्षर request_type = 0x38, rcv_request = 0x81;
	अक्षर *response;

	mutex_lock(&dev->usbc_mutex);
	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      rcv_request, 0x80 | request_type,
			      0x0400, 0x0003,
			      dev->usbc_buf, 46,
			      10000);
	अगर (ret != 46) अणु
		v4l2_err(&dev->v4l2_dev,
			 "unexpected answer of status request, len %d\n", ret);
		जाओ unlock;
	पूर्ण
#अगर_घोषित HDPVR_DEBUG
	अन्यथा अणु
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "Status request returned, len %d: %46ph\n",
			 ret, dev->usbc_buf);
	पूर्ण
#पूर्ण_अगर

	dev->fw_ver = dev->usbc_buf[1];

	dev->usbc_buf[46] = '\0';
	v4l2_info(&dev->v4l2_dev, "firmware version 0x%x dated %s\n",
			  dev->fw_ver, &dev->usbc_buf[2]);

	अगर (dev->fw_ver > 0x15) अणु
		dev->options.brightness	= 0x80;
		dev->options.contrast	= 0x40;
		dev->options.hue	= 0xf;
		dev->options.saturation	= 0x40;
		dev->options.sharpness	= 0x80;
	पूर्ण

	चयन (dev->fw_ver) अणु
	हाल HDPVR_FIRMWARE_VERSION:
		dev->flags &= ~HDPVR_FLAG_AC3_CAP;
		अवरोध;
	हाल HDPVR_FIRMWARE_VERSION_AC3:
	हाल HDPVR_FIRMWARE_VERSION_0X12:
	हाल HDPVR_FIRMWARE_VERSION_0X15:
	हाल HDPVR_FIRMWARE_VERSION_0X1E:
		dev->flags |= HDPVR_FLAG_AC3_CAP;
		अवरोध;
	शेष:
		v4l2_info(&dev->v4l2_dev, "untested firmware, the driver might not work.\n");
		अगर (dev->fw_ver >= HDPVR_FIRMWARE_VERSION_AC3)
			dev->flags |= HDPVR_FLAG_AC3_CAP;
		अन्यथा
			dev->flags &= ~HDPVR_FLAG_AC3_CAP;
	पूर्ण

	response = dev->usbc_buf+38;
#अगर_घोषित HDPVR_DEBUG
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev, "challenge: %8ph\n",
		 response);
#पूर्ण_अगर
	challenge(response);
#अगर_घोषित HDPVR_DEBUG
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev, " response: %8ph\n",
		 response);
#पूर्ण_अगर

	msleep(100);
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0xd1, 0x00 | request_type,
			      0x0000, 0x0000,
			      response, 8,
			      10000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "magic request returned %d\n", ret);

	retval = ret != 8;
unlock:
	mutex_unlock(&dev->usbc_mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक hdpvr_device_init(काष्ठा hdpvr_device *dev)
अणु
	पूर्णांक ret;
	u8 *buf;

	अगर (device_authorization(dev))
		वापस -EACCES;

	/* शेष options क्रम init */
	hdpvr_set_options(dev);

	/* set filter options */
	mutex_lock(&dev->usbc_mutex);
	buf = dev->usbc_buf;
	buf[0] = 0x03; buf[1] = 0x03; buf[2] = 0x00; buf[3] = 0x00;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0x01, 0x38,
			      CTRL_LOW_PASS_FILTER_VALUE, CTRL_DEFAULT_INDEX,
			      buf, 4,
			      1000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "control request returned %d\n", ret);
	mutex_unlock(&dev->usbc_mutex);

	/* enable fan and bling leds */
	mutex_lock(&dev->usbc_mutex);
	buf[0] = 0x1;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0xd4, 0x38, 0, 0, buf, 1,
			      1000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "control request returned %d\n", ret);

	/* boost analog audio */
	buf[0] = boost_audio;
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0xd5, 0x38, 0, 0, buf, 1,
			      1000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "control request returned %d\n", ret);
	mutex_unlock(&dev->usbc_mutex);

	dev->status = STATUS_IDLE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdpvr_options hdpvr_शेष_options = अणु
	.video_std	= HDPVR_60HZ,
	.video_input	= HDPVR_COMPONENT,
	.audio_input	= HDPVR_RCA_BACK,
	.bitrate	= 65, /* 6 mbps */
	.peak_bitrate	= 90, /* 9 mbps */
	.bitrate_mode	= HDPVR_CONSTANT,
	.gop_mode	= HDPVR_SIMPLE_IDR_GOP,
	.audio_codec	= V4L2_MPEG_AUDIO_ENCODING_AAC,
	/* original picture controls क्रम firmware version <= 0x15 */
	/* updated in device_authorization() क्रम newer firmware */
	.brightness	= 0x86,
	.contrast	= 0x80,
	.hue		= 0x80,
	.saturation	= 0x80,
	.sharpness	= 0x80,
पूर्ण;

अटल पूर्णांक hdpvr_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा hdpvr_device *dev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
#अगर IS_ENABLED(CONFIG_I2C)
	काष्ठा i2c_client *client;
#पूर्ण_अगर
	माप_प्रकार buffer_size;
	पूर्णांक i;
	पूर्णांक dev_num;
	पूर्णांक retval = -ENOMEM;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		dev_err(&पूर्णांकerface->dev, "Out of memory\n");
		जाओ error;
	पूर्ण

	/* init video transfer queues first of all */
	/* to prevent oops in hdpvr_delete() on error paths */
	INIT_LIST_HEAD(&dev->मुक्त_buff_list);
	INIT_LIST_HEAD(&dev->rec_buff_list);

	/* रेजिस्टर v4l2_device early so it can be used क्रम prपूर्णांकks */
	अगर (v4l2_device_रेजिस्टर(&पूर्णांकerface->dev, &dev->v4l2_dev)) अणु
		dev_err(&पूर्णांकerface->dev, "v4l2_device_register failed\n");
		जाओ error_मुक्त_dev;
	पूर्ण

	mutex_init(&dev->io_mutex);
	mutex_init(&dev->i2c_mutex);
	mutex_init(&dev->usbc_mutex);
	dev->usbc_buf = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!dev->usbc_buf) अणु
		v4l2_err(&dev->v4l2_dev, "Out of memory\n");
		जाओ error_v4l2_unरेजिस्टर;
	पूर्ण

	init_रुकोqueue_head(&dev->रुको_buffer);
	init_रुकोqueue_head(&dev->रुको_data);

	dev->options = hdpvr_शेष_options;

	अगर (शेष_video_input < HDPVR_VIDEO_INPUTS)
		dev->options.video_input = शेष_video_input;

	अगर (शेष_audio_input < HDPVR_AUDIO_INPUTS) अणु
		dev->options.audio_input = शेष_audio_input;
		अगर (शेष_audio_input == HDPVR_SPDIF)
			dev->options.audio_codec =
				V4L2_MPEG_AUDIO_ENCODING_AC3;
	पूर्ण

	dev->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	/* set up the endpoपूर्णांक inक्रमmation */
	/* use only the first bulk-in and bulk-out endpoपूर्णांकs */
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (!dev->bulk_in_endpoपूर्णांकAddr &&
		    usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक)) अणु
			/* USB पूर्णांकerface description is buggy, reported max
			 * packet size is 512 bytes, winकरोws driver uses 8192 */
			buffer_size = 8192;
			dev->bulk_in_size = buffer_size;
			dev->bulk_in_endpoपूर्णांकAddr = endpoपूर्णांक->bEndpoपूर्णांकAddress;
		पूर्ण

	पूर्ण
	अगर (!dev->bulk_in_endpoपूर्णांकAddr) अणु
		v4l2_err(&dev->v4l2_dev, "Could not find bulk-in endpoint\n");
		जाओ error_put_usb;
	पूर्ण

	/* init the device */
	अगर (hdpvr_device_init(dev)) अणु
		v4l2_err(&dev->v4l2_dev, "device init failed\n");
		जाओ error_put_usb;
	पूर्ण

	mutex_lock(&dev->io_mutex);
	अगर (hdpvr_alloc_buffers(dev, NUM_BUFFERS)) अणु
		mutex_unlock(&dev->io_mutex);
		v4l2_err(&dev->v4l2_dev,
			 "allocating transfer buffers failed\n");
		जाओ error_put_usb;
	पूर्ण
	mutex_unlock(&dev->io_mutex);

#अगर IS_ENABLED(CONFIG_I2C)
	retval = hdpvr_रेजिस्टर_i2c_adapter(dev);
	अगर (retval < 0) अणु
		v4l2_err(&dev->v4l2_dev, "i2c adapter register failed\n");
		जाओ error_मुक्त_buffers;
	पूर्ण

	client = hdpvr_रेजिस्टर_ir_i2c(dev);
	अगर (IS_ERR(client)) अणु
		v4l2_err(&dev->v4l2_dev, "i2c IR device register failed\n");
		retval = PTR_ERR(client);
		जाओ reg_fail;
	पूर्ण
#पूर्ण_अगर

	dev_num = atomic_inc_वापस(&dev_nr);
	अगर (dev_num >= HDPVR_MAX) अणु
		v4l2_err(&dev->v4l2_dev,
			 "max device number reached, device register failed\n");
		atomic_dec(&dev_nr);
		retval = -ENODEV;
		जाओ reg_fail;
	पूर्ण

	retval = hdpvr_रेजिस्टर_videodev(dev, &पूर्णांकerface->dev,
				    video_nr[dev_num]);
	अगर (retval < 0) अणु
		v4l2_err(&dev->v4l2_dev, "registering videodev failed\n");
		जाओ reg_fail;
	पूर्ण

	/* let the user know what node this device is now attached to */
	v4l2_info(&dev->v4l2_dev, "device now attached to %s\n",
		  video_device_node_name(&dev->video_dev));
	वापस 0;

reg_fail:
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_adapter(&dev->i2c_adapter);
error_मुक्त_buffers:
#पूर्ण_अगर
	hdpvr_मुक्त_buffers(dev);
error_put_usb:
	usb_put_dev(dev->udev);
	kमुक्त(dev->usbc_buf);
error_v4l2_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
error_मुक्त_dev:
	kमुक्त(dev);
error:
	वापस retval;
पूर्ण

अटल व्योम hdpvr_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा hdpvr_device *dev = to_hdpvr_dev(usb_get_पूर्णांकfdata(पूर्णांकerface));

	v4l2_info(&dev->v4l2_dev, "device %s disconnected\n",
		  video_device_node_name(&dev->video_dev));
	/* prevent more I/O from starting and stop any ongoing */
	mutex_lock(&dev->io_mutex);
	dev->status = STATUS_DISCONNECTED;
	wake_up_पूर्णांकerruptible(&dev->रुको_data);
	wake_up_पूर्णांकerruptible(&dev->रुको_buffer);
	mutex_unlock(&dev->io_mutex);
	v4l2_device_disconnect(&dev->v4l2_dev);
	msleep(100);
	flush_work(&dev->worker);
	mutex_lock(&dev->io_mutex);
	hdpvr_cancel_queue(dev);
	mutex_unlock(&dev->io_mutex);
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_adapter(&dev->i2c_adapter);
#पूर्ण_अगर
	video_unरेजिस्टर_device(&dev->video_dev);
	atomic_dec(&dev_nr);
पूर्ण


अटल काष्ठा usb_driver hdpvr_usb_driver = अणु
	.name =		"hdpvr",
	.probe =	hdpvr_probe,
	.disconnect =	hdpvr_disconnect,
	.id_table =	hdpvr_table,
पूर्ण;

module_usb_driver(hdpvr_usb_driver);

MODULE_LICENSE("GPL");
MODULE_VERSION("0.2.1");
MODULE_AUTHOR("Janne Grunau");
MODULE_DESCRIPTION("Hauppauge HD PVR driver");
