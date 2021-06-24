<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Driver क्रम Xbox DVD Movie Playback Kit
// Copyright (c) 2018 by Benjamin Valentin <benpicco@googlemail.com>

/*
 *  Xbox DVD Movie Playback Kit USB IR करोngle support
 *
 *  The driver was derived from the ati_remote driver 2.2.1
 *          and used inक्रमmation from lirc_xbox.c
 *
 *          Copyright (c) 2011, 2012 Anssi Hannula <anssi.hannula@iki.fi>
 *          Copyright (c) 2004 Torrey Hoffman <thoffman@arnor.net>
 *          Copyright (c) 2002 Vladimir Dergachev
 *          Copyright (c) 2003-2004 Paul Miller <pmiller9@users.sourceक्रमge.net>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>
#समावेश <media/rc-core.h>

/*
 * Module and Version Inक्रमmation
 */
#घोषणा DRIVER_VERSION	"1.0.0"
#घोषणा DRIVER_AUTHOR	"Benjamin Valentin <benpicco@googlemail.com>"
#घोषणा DRIVER_DESC		"Xbox DVD USB Remote Control"

#घोषणा NAME_बफ_मानE      80    /* size of product name, path buffers */
#घोषणा DATA_बफ_मानE      8     /* size of URB data buffers */

/*
 * USB venकरोr ids क्रम XBOX DVD Dongles
 */
#घोषणा VENDOR_GAMESTER     0x040b
#घोषणा VENDOR_MICROSOFT    0x045e

अटल स्थिर काष्ठा usb_device_id xbox_remote_table[] = अणु
	/* Gamester Xbox DVD Movie Playback Kit IR */
	अणु
		USB_DEVICE(VENDOR_GAMESTER, 0x6521),
	पूर्ण,
	/* Microsoft Xbox DVD Movie Playback Kit IR */
	अणु
		USB_DEVICE(VENDOR_MICROSOFT, 0x0284),
	पूर्ण,
	अणुपूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, xbox_remote_table);

काष्ठा xbox_remote अणु
	काष्ठा rc_dev *rdev;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	काष्ठा urb *irq_urb;
	अचिन्हित अक्षर inbuf[DATA_बफ_मानE] __aligned(माप(u16));

	अक्षर rc_name[NAME_बफ_मानE];
	अक्षर rc_phys[NAME_बफ_मानE];
पूर्ण;

अटल पूर्णांक xbox_remote_rc_खोलो(काष्ठा rc_dev *rdev)
अणु
	काष्ठा xbox_remote *xbox_remote = rdev->priv;

	/* On first खोलो, submit the पढ़ो urb which was set up previously. */
	xbox_remote->irq_urb->dev = xbox_remote->udev;
	अगर (usb_submit_urb(xbox_remote->irq_urb, GFP_KERNEL)) अणु
		dev_err(&xbox_remote->पूर्णांकerface->dev,
			"%s: usb_submit_urb failed!\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xbox_remote_rc_बंद(काष्ठा rc_dev *rdev)
अणु
	काष्ठा xbox_remote *xbox_remote = rdev->priv;

	usb_समाप्त_urb(xbox_remote->irq_urb);
पूर्ण

/*
 * xbox_remote_report_input
 */
अटल व्योम xbox_remote_input_report(काष्ठा urb *urb)
अणु
	काष्ठा xbox_remote *xbox_remote = urb->context;
	अचिन्हित अक्षर *data = xbox_remote->inbuf;

	/*
	 * data[0] = 0x00
	 * data[1] = length - always 0x06
	 * data[2] = the key code
	 * data[3] = high part of key code
	 * data[4] = last_press_ms (low)
	 * data[5] = last_press_ms (high)
	 */

	/* Deal with strange looking inमाला_दो */
	अगर (urb->actual_length != 6 || urb->actual_length != data[1]) अणु
		dev_warn(&urb->dev->dev, "Weird data, len=%d: %*ph\n",
			 urb->actual_length, urb->actual_length, data);
		वापस;
	पूर्ण

	rc_keyकरोwn(xbox_remote->rdev, RC_PROTO_XBOX_DVD,
		   le16_to_cpup((__le16 *)(data + 2)), 0);
पूर्ण

/*
 * xbox_remote_irq_in
 */
अटल व्योम xbox_remote_irq_in(काष्ठा urb *urb)
अणु
	काष्ठा xbox_remote *xbox_remote = urb->context;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:			/* success */
		xbox_remote_input_report(urb);
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_dbg(&xbox_remote->पूर्णांकerface->dev,
			"%s: urb error status, unlink?\n",
			__func__);
		वापस;
	शेष:		/* error */
		dev_dbg(&xbox_remote->पूर्णांकerface->dev,
			"%s: Nonzero urb status %d\n",
			__func__, urb->status);
	पूर्ण

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&xbox_remote->पूर्णांकerface->dev,
			"%s: usb_submit_urb()=%d\n",
			__func__, retval);
पूर्ण

अटल व्योम xbox_remote_rc_init(काष्ठा xbox_remote *xbox_remote)
अणु
	काष्ठा rc_dev *rdev = xbox_remote->rdev;

	rdev->priv = xbox_remote;
	rdev->allowed_protocols = RC_PROTO_BIT_XBOX_DVD;
	rdev->driver_name = "xbox_remote";

	rdev->खोलो = xbox_remote_rc_खोलो;
	rdev->बंद = xbox_remote_rc_बंद;

	rdev->device_name = xbox_remote->rc_name;
	rdev->input_phys = xbox_remote->rc_phys;

	rdev->समयout = MS_TO_US(10);

	usb_to_input_id(xbox_remote->udev, &rdev->input_id);
	rdev->dev.parent = &xbox_remote->पूर्णांकerface->dev;
पूर्ण

अटल पूर्णांक xbox_remote_initialize(काष्ठा xbox_remote *xbox_remote,
				  काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक_in)
अणु
	काष्ठा usb_device *udev = xbox_remote->udev;
	पूर्णांक pipe, maxp;

	/* Set up irq_urb */
	pipe = usb_rcvपूर्णांकpipe(udev, endpoपूर्णांक_in->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = (maxp > DATA_बफ_मानE) ? DATA_बफ_मानE : maxp;

	usb_fill_पूर्णांक_urb(xbox_remote->irq_urb, udev, pipe, xbox_remote->inbuf,
			 maxp, xbox_remote_irq_in, xbox_remote,
			 endpoपूर्णांक_in->bInterval);

	वापस 0;
पूर्ण

/*
 * xbox_remote_probe
 */
अटल पूर्णांक xbox_remote_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *अगरace_host = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक_in;
	काष्ठा xbox_remote *xbox_remote;
	काष्ठा rc_dev *rc_dev;
	पूर्णांक err = -ENOMEM;

	// why is there also a device with no endpoपूर्णांकs?
	अगर (अगरace_host->desc.bNumEndpoपूर्णांकs == 0)
		वापस -ENODEV;

	अगर (अगरace_host->desc.bNumEndpoपूर्णांकs != 1) अणु
		pr_err("%s: Unexpected desc.bNumEndpoints: %d\n",
		       __func__, अगरace_host->desc.bNumEndpoपूर्णांकs);
		वापस -ENODEV;
	पूर्ण

	endpoपूर्णांक_in = &अगरace_host->endpoपूर्णांक[0].desc;

	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक_in)) अणु
		pr_err("%s: Unexpected endpoint_in\n", __func__);
		वापस -ENODEV;
	पूर्ण
	अगर (le16_to_cpu(endpoपूर्णांक_in->wMaxPacketSize) == 0) अणु
		pr_err("%s: endpoint_in message size==0?\n", __func__);
		वापस -ENODEV;
	पूर्ण

	xbox_remote = kzalloc(माप(*xbox_remote), GFP_KERNEL);
	rc_dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!xbox_remote || !rc_dev)
		जाओ निकास_मुक्त_dev_rdev;

	/* Allocate URB buffer */
	xbox_remote->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!xbox_remote->irq_urb)
		जाओ निकास_मुक्त_buffers;

	xbox_remote->udev = udev;
	xbox_remote->rdev = rc_dev;
	xbox_remote->पूर्णांकerface = पूर्णांकerface;

	usb_make_path(udev, xbox_remote->rc_phys, माप(xbox_remote->rc_phys));

	strlcat(xbox_remote->rc_phys, "/input0", माप(xbox_remote->rc_phys));

	snम_लिखो(xbox_remote->rc_name, माप(xbox_remote->rc_name), "%s%s%s",
		 udev->manufacturer ?: "",
		 udev->manufacturer && udev->product ? " " : "",
		 udev->product ?: "");

	अगर (!म_माप(xbox_remote->rc_name))
		snम_लिखो(xbox_remote->rc_name, माप(xbox_remote->rc_name),
			 DRIVER_DESC "(%04x,%04x)",
			 le16_to_cpu(xbox_remote->udev->descriptor.idVenकरोr),
			 le16_to_cpu(xbox_remote->udev->descriptor.idProduct));

	rc_dev->map_name = RC_MAP_XBOX_DVD; /* शेष map */

	xbox_remote_rc_init(xbox_remote);

	/* Device Hardware Initialization */
	err = xbox_remote_initialize(xbox_remote, endpoपूर्णांक_in);
	अगर (err)
		जाओ निकास_समाप्त_urbs;

	/* Set up and रेजिस्टर rc device */
	err = rc_रेजिस्टर_device(xbox_remote->rdev);
	अगर (err)
		जाओ निकास_समाप्त_urbs;

	usb_set_पूर्णांकfdata(पूर्णांकerface, xbox_remote);

	वापस 0;

निकास_समाप्त_urbs:
	usb_समाप्त_urb(xbox_remote->irq_urb);
निकास_मुक्त_buffers:
	usb_मुक्त_urb(xbox_remote->irq_urb);
निकास_मुक्त_dev_rdev:
	rc_मुक्त_device(rc_dev);
	kमुक्त(xbox_remote);

	वापस err;
पूर्ण

/*
 * xbox_remote_disconnect
 */
अटल व्योम xbox_remote_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा xbox_remote *xbox_remote;

	xbox_remote = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	अगर (!xbox_remote) अणु
		dev_warn(&पूर्णांकerface->dev, "%s - null device?\n", __func__);
		वापस;
	पूर्ण

	usb_समाप्त_urb(xbox_remote->irq_urb);
	rc_unरेजिस्टर_device(xbox_remote->rdev);
	usb_मुक्त_urb(xbox_remote->irq_urb);
	kमुक्त(xbox_remote);
पूर्ण

/* usb specअगरic object to रेजिस्टर with the usb subप्रणाली */
अटल काष्ठा usb_driver xbox_remote_driver = अणु
	.name         = "xbox_remote",
	.probe        = xbox_remote_probe,
	.disconnect   = xbox_remote_disconnect,
	.id_table     = xbox_remote_table,
पूर्ण;

module_usb_driver(xbox_remote_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
