<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STK1160 driver
 *
 * Copyright (C) 2012 Ezequiel Garcia
 * <elezegarcia--a.t--gmail.com>
 *
 * Based on Easycap driver by R.M. Thomas
 *	Copyright (C) 2010 R.M. Thomas
 *	<rmthomas--a.t--sciolus.org>
 *
 * TODO:
 *
 * 1. Support stream at lower speed: lower frame rate or lower frame size.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश <linux/usb.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <media/i2c/saa7115.h>

#समावेश "stk1160.h"
#समावेश "stk1160-reg.h"

अटल अचिन्हित पूर्णांक input;
module_param(input, पूर्णांक, 0644);
MODULE_PARM_DESC(input, "Set default input");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ezequiel Garcia");
MODULE_DESCRIPTION("STK1160 driver");

/* Devices supported by this driver */
अटल स्थिर काष्ठा usb_device_id stk1160_id_table[] = अणु
	अणु USB_DEVICE(0x05e1, 0x0408) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, stk1160_id_table);

/* saa7113 I2C address */
अटल अचिन्हित लघु saa7113_addrs[] = अणु
	0x4a >> 1,
	I2C_CLIENT_END
पूर्ण;

/*
 * Read/Write stk रेजिस्टरs
 */
पूर्णांक stk1160_पढ़ो_reg(काष्ठा stk1160 *dev, u16 reg, u8 *value)
अणु
	पूर्णांक ret;
	पूर्णांक pipe = usb_rcvctrlpipe(dev->udev, 0);
	u8 *buf;

	*value = 0;

	buf = kदो_स्मृति(माप(u8), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	ret = usb_control_msg(dev->udev, pipe, 0x00,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x00, reg, buf, माप(u8), HZ);
	अगर (ret < 0) अणु
		stk1160_err("read failed on reg 0x%x (%d)\n",
			reg, ret);
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	*value = *buf;
	kमुक्त(buf);
	वापस 0;
पूर्ण

पूर्णांक stk1160_ग_लिखो_reg(काष्ठा stk1160 *dev, u16 reg, u16 value)
अणु
	पूर्णांक ret;
	पूर्णांक pipe = usb_sndctrlpipe(dev->udev, 0);

	ret =  usb_control_msg(dev->udev, pipe, 0x01,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, reg, शून्य, 0, HZ);
	अगर (ret < 0) अणु
		stk1160_err("write failed on reg 0x%x (%d)\n",
			reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम stk1160_select_input(काष्ठा stk1160 *dev)
अणु
	पूर्णांक route;
	अटल स्थिर u8 gctrl[] = अणु
		0x98, 0x90, 0x88, 0x80, 0x98
	पूर्ण;

	अगर (dev->ctl_input == STK1160_SVIDEO_INPUT)
		route = SAA7115_SVIDEO3;
	अन्यथा
		route = SAA7115_COMPOSITE0;

	अगर (dev->ctl_input < ARRAY_SIZE(gctrl)) अणु
		v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_routing,
				route, 0, 0);
		stk1160_ग_लिखो_reg(dev, STK1160_GCTRL, gctrl[dev->ctl_input]);
	पूर्ण
पूर्ण

/* TODO: We should अवरोध this पूर्णांकo pieces */
अटल व्योम stk1160_reg_reset(काष्ठा stk1160 *dev)
अणु
	पूर्णांक i;

	अटल स्थिर काष्ठा regval ctl[] = अणु
		अणुSTK1160_GCTRL+2, 0x0078पूर्ण,

		अणुSTK1160_RMCTL+1, 0x0000पूर्ण,
		अणुSTK1160_RMCTL+3, 0x0002पूर्ण,

		अणुSTK1160_PLLSO,   0x0010पूर्ण,
		अणुSTK1160_PLLSO+1, 0x0000पूर्ण,
		अणुSTK1160_PLLSO+2, 0x0014पूर्ण,
		अणुSTK1160_PLLSO+3, 0x000Eपूर्ण,

		अणुSTK1160_PLLFD,   0x0046पूर्ण,

		/* Timing generator setup */
		अणुSTK1160_TIGEN,   0x0012पूर्ण,
		अणुSTK1160_TICTL,   0x002Dपूर्ण,
		अणुSTK1160_TICTL+1, 0x0001पूर्ण,
		अणुSTK1160_TICTL+2, 0x0000पूर्ण,
		अणुSTK1160_TICTL+3, 0x0000पूर्ण,
		अणुSTK1160_TIGEN,   0x0080पूर्ण,

		अणु0xffff, 0xffffपूर्ण
	पूर्ण;

	क्रम (i = 0; ctl[i].reg != 0xffff; i++)
		stk1160_ग_लिखो_reg(dev, ctl[i].reg, ctl[i].val);
पूर्ण

अटल व्योम stk1160_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा stk1160 *dev = container_of(v4l2_dev, काष्ठा stk1160, v4l2_dev);

	stk1160_dbg("releasing all resources\n");

	stk1160_i2c_unरेजिस्टर(dev);

	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	mutex_destroy(&dev->v4l_lock);
	mutex_destroy(&dev->vb_queue_lock);
	kमुक्त(dev->alt_max_pkt_size);
	kमुक्त(dev);
पूर्ण

/* high bandwidth multiplier, as encoded in highspeed endpoपूर्णांक descriptors */
#घोषणा hb_mult(wMaxPacketSize) (1 + (((wMaxPacketSize) >> 11) & 0x03))

/*
 * Scan usb पूर्णांकerface and populate max_pkt_size array
 * with inक्रमmation on each alternate setting.
 * The array should be allocated by the caller.
 */
अटल पूर्णांक stk1160_scan_usb(काष्ठा usb_पूर्णांकerface *पूर्णांकf, काष्ठा usb_device *udev,
		अचिन्हित पूर्णांक *max_pkt_size)
अणु
	पूर्णांक i, e, sizedescr, size, अगरnum;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;

	bool has_video = false, has_audio = false;
	स्थिर अक्षर *speed;

	अगरnum = पूर्णांकf->altsetting[0].desc.bInterfaceNumber;

	/* Get endpoपूर्णांकs */
	क्रम (i = 0; i < पूर्णांकf->num_altsetting; i++) अणु

		क्रम (e = 0; e < पूर्णांकf->altsetting[i].desc.bNumEndpoपूर्णांकs; e++) अणु

			/* This isn't clear enough, at least to me */
			desc = &पूर्णांकf->altsetting[i].endpoपूर्णांक[e].desc;
			sizedescr = le16_to_cpu(desc->wMaxPacketSize);
			size = sizedescr & 0x7ff;

			अगर (udev->speed == USB_SPEED_HIGH)
				size = size * hb_mult(sizedescr);

			अगर (usb_endpoपूर्णांक_xfer_isoc(desc) &&
			    usb_endpoपूर्णांक_dir_in(desc)) अणु
				चयन (desc->bEndpoपूर्णांकAddress) अणु
				हाल STK1160_EP_AUDIO:
					has_audio = true;
					अवरोध;
				हाल STK1160_EP_VIDEO:
					has_video = true;
					max_pkt_size[i] = size;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Is this even possible? */
	अगर (!(has_audio || has_video)) अणु
		dev_err(&udev->dev, "no audio or video endpoints found\n");
		वापस -ENODEV;
	पूर्ण

	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
		speed = "1.5";
		अवरोध;
	हाल USB_SPEED_FULL:
		speed = "12";
		अवरोध;
	हाल USB_SPEED_HIGH:
		speed = "480";
		अवरोध;
	शेष:
		speed = "unknown";
	पूर्ण

	dev_info(&udev->dev, "New device %s %s @ %s Mbps (%04x:%04x, interface %d, class %d)\n",
		udev->manufacturer ? udev->manufacturer : "",
		udev->product ? udev->product : "",
		speed,
		le16_to_cpu(udev->descriptor.idVenकरोr),
		le16_to_cpu(udev->descriptor.idProduct),
		अगरnum,
		पूर्णांकf->altsetting->desc.bInterfaceNumber);

	/* This should never happen, since we rejected audio पूर्णांकerfaces */
	अगर (has_audio)
		dev_warn(&udev->dev, "audio पूर्णांकerface %d found.\न\
				This is not implemented by this driver,\
				you should use snd-usb-audio instead\न", अगरnum);

	अगर (has_video)
		dev_info(&udev->dev, "video interface %d found\n",
				अगरnum);

	/*
	 * Make sure we have 480 Mbps of bandwidth, otherwise things like
	 * video stream wouldn't likely work, since 12 Mbps is generally
	 * not enough even क्रम most streams.
	 */
	अगर (udev->speed != USB_SPEED_HIGH)
		dev_warn(&udev->dev, "must be connected to a high-speed USB 2.0 port\न\
				You may not be able to stream video smoothly\न");

	वापस 0;
पूर्ण

अटल पूर्णांक stk1160_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक rc = 0;

	अचिन्हित पूर्णांक *alt_max_pkt_size;	/* array of wMaxPacketSize */
	काष्ठा usb_device *udev;
	काष्ठा stk1160 *dev;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	/*
	 * Since usb audio class is supported by snd-usb-audio,
	 * we reject audio पूर्णांकerface.
	 */
	अगर (पूर्णांकerface->altsetting[0].desc.bInterfaceClass == USB_CLASS_AUDIO)
		वापस -ENODEV;

	/* Alloc an array क्रम all possible max_pkt_size */
	alt_max_pkt_size = kदो_स्मृति_array(पूर्णांकerface->num_altsetting,
					 माप(alt_max_pkt_size[0]),
					 GFP_KERNEL);
	अगर (alt_max_pkt_size == शून्य)
		वापस -ENOMEM;

	/*
	 * Scan usb possibilities and populate alt_max_pkt_size array.
	 * Also, check अगर device speed is fast enough.
	 */
	rc = stk1160_scan_usb(पूर्णांकerface, udev, alt_max_pkt_size);
	अगर (rc < 0) अणु
		kमुक्त(alt_max_pkt_size);
		वापस rc;
	पूर्ण

	dev = kzalloc(माप(काष्ठा stk1160), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		kमुक्त(alt_max_pkt_size);
		वापस -ENOMEM;
	पूर्ण

	dev->alt_max_pkt_size = alt_max_pkt_size;
	dev->udev = udev;
	dev->num_alt = पूर्णांकerface->num_altsetting;
	dev->ctl_input = input;

	/* We save काष्ठा device क्रम debug purposes only */
	dev->dev = &पूर्णांकerface->dev;

	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	/* initialize videobuf2 stuff */
	rc = stk1160_vb2_setup(dev);
	अगर (rc < 0)
		जाओ मुक्त_err;

	/*
	 * There is no need to take any locks here in probe
	 * because we रेजिस्टर the device node as the *last* thing.
	 */
	spin_lock_init(&dev->buf_lock);
	mutex_init(&dev->v4l_lock);
	mutex_init(&dev->vb_queue_lock);

	rc = v4l2_ctrl_handler_init(&dev->ctrl_handler, 0);
	अगर (rc) अणु
		stk1160_err("v4l2_ctrl_handler_init failed (%d)\n", rc);
		जाओ मुक्त_err;
	पूर्ण

	/*
	 * We obtain a v4l2_dev but defer
	 * registration of video device node as the last thing.
	 * There is no need to set the name अगर we give a device काष्ठा
	 */
	dev->v4l2_dev.release = stk1160_release;
	dev->v4l2_dev.ctrl_handler = &dev->ctrl_handler;
	rc = v4l2_device_रेजिस्टर(dev->dev, &dev->v4l2_dev);
	अगर (rc) अणु
		stk1160_err("v4l2_device_register failed (%d)\n", rc);
		जाओ मुक्त_ctrl;
	पूर्ण

	rc = stk1160_i2c_रेजिस्टर(dev);
	अगर (rc < 0)
		जाओ unreg_v4l2;

	/*
	 * To the best of my knowledge stk1160 boards only have
	 * saa7113, but it करोesn't hurt to support them all.
	 */
	dev->sd_saa7115 = v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
		"saa7115_auto", 0, saa7113_addrs);

	/* i2c reset saa711x */
	v4l2_device_call_all(&dev->v4l2_dev, 0, core, reset, 0);
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 0);

	/* reset stk1160 to शेष values */
	stk1160_reg_reset(dev);

	/* select शेष input */
	stk1160_select_input(dev);

	stk1160_ac97_setup(dev);

	rc = stk1160_video_रेजिस्टर(dev);
	अगर (rc < 0)
		जाओ unreg_i2c;

	वापस 0;

unreg_i2c:
	stk1160_i2c_unरेजिस्टर(dev);
unreg_v4l2:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
मुक्त_err:
	kमुक्त(alt_max_pkt_size);
	kमुक्त(dev);

	वापस rc;
पूर्ण

अटल व्योम stk1160_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा stk1160 *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	/*
	 * Wait until all current v4l2 operation are finished
	 * then deallocate resources
	 */
	mutex_lock(&dev->vb_queue_lock);
	mutex_lock(&dev->v4l_lock);

	/* Here is the only place where isoc get released */
	stk1160_uninit_isoc(dev);

	stk1160_clear_queue(dev);

	video_unरेजिस्टर_device(&dev->vdev);
	v4l2_device_disconnect(&dev->v4l2_dev);

	/* This way current users can detect device is gone */
	dev->udev = शून्य;

	mutex_unlock(&dev->v4l_lock);
	mutex_unlock(&dev->vb_queue_lock);

	/*
	 * This calls stk1160_release अगर it's the last reference.
	 * Otherwise, release is postponed until there are no users left.
	 */
	v4l2_device_put(&dev->v4l2_dev);
पूर्ण

अटल काष्ठा usb_driver stk1160_usb_driver = अणु
	.name = "stk1160",
	.id_table = stk1160_id_table,
	.probe = stk1160_probe,
	.disconnect = stk1160_disconnect,
पूर्ण;

module_usb_driver(stk1160_usb_driver);
