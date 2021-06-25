<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Apple USB Touchpad (क्रम post-February 2005 PowerBooks and MacBooks) driver
 *
 * Copyright (C) 2001-2004 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2005-2008 Johannes Berg (johannes@sipsolutions.net)
 * Copyright (C) 2005-2008 Stelian Pop (stelian@popies.net)
 * Copyright (C) 2005      Frank Arnold (frank@scirocco-5v-turbo.de)
 * Copyright (C) 2005      Peter Osterlund (petero2@telia.com)
 * Copyright (C) 2005      Michael Hanselmann (linux-kernel@hansmi.ch)
 * Copyright (C) 2006      Nicolas Boichat (nicolas@boichat.ch)
 * Copyright (C) 2007-2008 Sven Anders (anders@anduras.de)
 *
 * Thanks to Alex Harper <basilisk@foobox.net> क्रम his inमाला_दो.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>

/*
 * Note: We try to keep the touchpad aspect ratio जबतक still करोing only
 * simple arithmetics:
 *	0 <= x <= (xsensors - 1) * xfact
 *	0 <= y <= (ysensors - 1) * yfact
 */
काष्ठा atp_info अणु
	पूर्णांक xsensors;				/* number of X sensors */
	पूर्णांक xsensors_17;			/* 17" models have more sensors */
	पूर्णांक ysensors;				/* number of Y sensors */
	पूर्णांक xfact;				/* X multiplication factor */
	पूर्णांक yfact;				/* Y multiplication factor */
	पूर्णांक datalen;				/* size of USB transfers */
	व्योम (*callback)(काष्ठा urb *);		/* callback function */
	पूर्णांक fuzz;				/* fuzz touchpad generates */
पूर्ण;

अटल व्योम atp_complete_geyser_1_2(काष्ठा urb *urb);
अटल व्योम atp_complete_geyser_3_4(काष्ठा urb *urb);

अटल स्थिर काष्ठा atp_info fountain_info = अणु
	.xsensors	= 16,
	.xsensors_17	= 26,
	.ysensors	= 16,
	.xfact		= 64,
	.yfact		= 43,
	.datalen	= 81,
	.callback	= atp_complete_geyser_1_2,
	.fuzz		= 16,
पूर्ण;

अटल स्थिर काष्ठा atp_info geyser1_info = अणु
	.xsensors	= 16,
	.xsensors_17	= 26,
	.ysensors	= 16,
	.xfact		= 64,
	.yfact		= 43,
	.datalen	= 81,
	.callback	= atp_complete_geyser_1_2,
	.fuzz		= 16,
पूर्ण;

अटल स्थिर काष्ठा atp_info geyser2_info = अणु
	.xsensors	= 15,
	.xsensors_17	= 20,
	.ysensors	= 9,
	.xfact		= 64,
	.yfact		= 43,
	.datalen	= 64,
	.callback	= atp_complete_geyser_1_2,
	.fuzz		= 0,
पूर्ण;

अटल स्थिर काष्ठा atp_info geyser3_info = अणु
	.xsensors	= 20,
	.ysensors	= 10,
	.xfact		= 64,
	.yfact		= 64,
	.datalen	= 64,
	.callback	= atp_complete_geyser_3_4,
	.fuzz		= 0,
पूर्ण;

अटल स्थिर काष्ठा atp_info geyser4_info = अणु
	.xsensors	= 20,
	.ysensors	= 10,
	.xfact		= 64,
	.yfact		= 64,
	.datalen	= 64,
	.callback	= atp_complete_geyser_3_4,
	.fuzz		= 0,
पूर्ण;

#घोषणा ATP_DEVICE(prod, info)					\
अणु								\
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE |		\
		       USB_DEVICE_ID_MATCH_INT_CLASS |		\
		       USB_DEVICE_ID_MATCH_INT_PROTOCOL,	\
	.idVenकरोr = 0x05ac, /* Apple */				\
	.idProduct = (prod),					\
	.bInterfaceClass = 0x03,				\
	.bInterfaceProtocol = 0x02,				\
	.driver_info = (अचिन्हित दीर्घ) &info,			\
पूर्ण

/*
 * Table of devices (Product IDs) that work with this driver.
 * (The names come from Info.plist in AppleUSBTrackpad.kext,
 *  According to Info.plist Geyser IV is the same as Geyser III.)
 */

अटल स्थिर काष्ठा usb_device_id atp_table[] = अणु
	/* PowerBooks Feb 2005, iBooks G4 */
	ATP_DEVICE(0x020e, fountain_info),	/* FOUNTAIN ANSI */
	ATP_DEVICE(0x020f, fountain_info),	/* FOUNTAIN ISO */
	ATP_DEVICE(0x030a, fountain_info),	/* FOUNTAIN TP ONLY */
	ATP_DEVICE(0x030b, geyser1_info),	/* GEYSER 1 TP ONLY */

	/* PowerBooks Oct 2005 */
	ATP_DEVICE(0x0214, geyser2_info),	/* GEYSER 2 ANSI */
	ATP_DEVICE(0x0215, geyser2_info),	/* GEYSER 2 ISO */
	ATP_DEVICE(0x0216, geyser2_info),	/* GEYSER 2 JIS */

	/* Core Duo MacBook & MacBook Pro */
	ATP_DEVICE(0x0217, geyser3_info),	/* GEYSER 3 ANSI */
	ATP_DEVICE(0x0218, geyser3_info),	/* GEYSER 3 ISO */
	ATP_DEVICE(0x0219, geyser3_info),	/* GEYSER 3 JIS */

	/* Core2 Duo MacBook & MacBook Pro */
	ATP_DEVICE(0x021a, geyser4_info),	/* GEYSER 4 ANSI */
	ATP_DEVICE(0x021b, geyser4_info),	/* GEYSER 4 ISO */
	ATP_DEVICE(0x021c, geyser4_info),	/* GEYSER 4 JIS */

	/* Core2 Duo MacBook3,1 */
	ATP_DEVICE(0x0229, geyser4_info),	/* GEYSER 4 HF ANSI */
	ATP_DEVICE(0x022a, geyser4_info),	/* GEYSER 4 HF ISO */
	ATP_DEVICE(0x022b, geyser4_info),	/* GEYSER 4 HF JIS */

	/* Terminating entry */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, atp_table);

/* maximum number of sensors */
#घोषणा ATP_XSENSORS	26
#घोषणा ATP_YSENSORS	16

/*
 * The largest possible bank of sensors with additional buffer of 4 extra values
 * on either side, क्रम an array of smoothed sensor values.
 */
#घोषणा ATP_SMOOTHSIZE	34

/* maximum pressure this driver will report */
#घोषणा ATP_PRESSURE	300

/*
 * Threshold क्रम the touchpad sensors. Any change less than ATP_THRESHOLD is
 * ignored.
 */
#घोषणा ATP_THRESHOLD	5

/*
 * How far we'll bitshअगरt our sensor values beक्रमe averaging them. Mitigates
 * rounding errors.
 */
#घोषणा ATP_SCALE	12

/* Geyser initialization स्थिरants */
#घोषणा ATP_GEYSER_MODE_READ_REQUEST_ID		1
#घोषणा ATP_GEYSER_MODE_WRITE_REQUEST_ID	9
#घोषणा ATP_GEYSER_MODE_REQUEST_VALUE		0x300
#घोषणा ATP_GEYSER_MODE_REQUEST_INDEX		0
#घोषणा ATP_GEYSER_MODE_VENDOR_VALUE		0x04

/**
 * क्रमागत atp_status_bits - status bit meanings
 *
 * These स्थिरants represent the meaning of the status bits.
 * (only Geyser 3/4)
 *
 * @ATP_STATUS_BUTTON: The button was pressed
 * @ATP_STATUS_BASE_UPDATE: Update of the base values (untouched pad)
 * @ATP_STATUS_FROM_RESET: Reset previously perक्रमmed
 */
क्रमागत atp_status_bits अणु
	ATP_STATUS_BUTTON	= BIT(0),
	ATP_STATUS_BASE_UPDATE	= BIT(2),
	ATP_STATUS_FROM_RESET	= BIT(4),
पूर्ण;

/* Structure to hold all of our device specअगरic stuff */
काष्ठा atp अणु
	अक्षर			phys[64];
	काष्ठा usb_device	*udev;		/* usb device */
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;		/* usb पूर्णांकerface */
	काष्ठा urb		*urb;		/* usb request block */
	u8			*data;		/* transferred data */
	काष्ठा input_dev	*input;		/* input dev */
	स्थिर काष्ठा atp_info	*info;		/* touchpad model */
	bool			खोलो;
	bool			valid;		/* are the samples valid? */
	bool			size_detect_करोne;
	bool			overflow_warned;
	पूर्णांक			fingers_old;	/* last reported finger count */
	पूर्णांक			x_old;		/* last reported x/y, */
	पूर्णांक			y_old;		/* used क्रम smoothing */
	चिन्हित अक्षर		xy_cur[ATP_XSENSORS + ATP_YSENSORS];
	चिन्हित अक्षर		xy_old[ATP_XSENSORS + ATP_YSENSORS];
	पूर्णांक			xy_acc[ATP_XSENSORS + ATP_YSENSORS];
	पूर्णांक			smooth[ATP_SMOOTHSIZE];
	पूर्णांक			smooth_पंचांगp[ATP_SMOOTHSIZE];
	पूर्णांक			idlecount;	/* number of empty packets */
	काष्ठा work_काष्ठा	work;
पूर्ण;

#घोषणा dbg_dump(msg, tab) \
	अगर (debug > 1) अणु						\
		पूर्णांक __i;						\
		prपूर्णांकk(KERN_DEBUG "appletouch: %s", msg);		\
		क्रम (__i = 0; __i < ATP_XSENSORS + ATP_YSENSORS; __i++)	\
			prपूर्णांकk(" %02x", tab[__i]);			\
		prपूर्णांकk("\n");						\
	पूर्ण

#घोषणा dprपूर्णांकk(क्रमmat, a...)						\
	करो अणु								\
		अगर (debug)						\
			prपूर्णांकk(KERN_DEBUG क्रमmat, ##a);			\
	पूर्ण जबतक (0)

MODULE_AUTHOR("Johannes Berg");
MODULE_AUTHOR("Stelian Pop");
MODULE_AUTHOR("Frank Arnold");
MODULE_AUTHOR("Michael Hanselmann");
MODULE_AUTHOR("Sven Anders");
MODULE_DESCRIPTION("Apple PowerBook and MacBook USB touchpad driver");
MODULE_LICENSE("GPL");

/*
 * Make the threshold a module parameter
 */
अटल पूर्णांक threshold = ATP_THRESHOLD;
module_param(threshold, पूर्णांक, 0644);
MODULE_PARM_DESC(threshold, "Discard any change in data from a sensor"
			    " (the trackpad has many of these sensors)"
			    " less than this value.");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Activate debugging output");

/*
 * By शेष newer Geyser devices send standard USB HID mouse
 * packets (Report ID 2). This code changes device mode, so it
 * sends raw sensor reports (Report ID 5).
 */
अटल पूर्णांक atp_geyser_init(काष्ठा atp *dev)
अणु
	काष्ठा usb_device *udev = dev->udev;
	अक्षर *data;
	पूर्णांक size;
	पूर्णांक i;
	पूर्णांक ret;

	data = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!data) अणु
		dev_err(&dev->पूर्णांकf->dev, "Out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	size = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			ATP_GEYSER_MODE_READ_REQUEST_ID,
			USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			ATP_GEYSER_MODE_REQUEST_VALUE,
			ATP_GEYSER_MODE_REQUEST_INDEX, data, 8, 5000);

	अगर (size != 8) अणु
		dprपूर्णांकk("atp_geyser_init: read error\n");
		क्रम (i = 0; i < 8; i++)
			dprपूर्णांकk("appletouch[%d]: %d\n", i, data[i]);

		dev_err(&dev->पूर्णांकf->dev, "Failed to read mode from device.\n");
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	/* Apply the mode चयन */
	data[0] = ATP_GEYSER_MODE_VENDOR_VALUE;

	size = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			ATP_GEYSER_MODE_WRITE_REQUEST_ID,
			USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			ATP_GEYSER_MODE_REQUEST_VALUE,
			ATP_GEYSER_MODE_REQUEST_INDEX, data, 8, 5000);

	अगर (size != 8) अणु
		dprपूर्णांकk("atp_geyser_init: write error\n");
		क्रम (i = 0; i < 8; i++)
			dprपूर्णांकk("appletouch[%d]: %d\n", i, data[i]);

		dev_err(&dev->पूर्णांकf->dev, "Failed to request geyser raw mode\n");
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण
	ret = 0;
out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण

/*
 * Reinitialise the device. This usually stops stream of empty packets
 * coming from it.
 */
अटल व्योम atp_reinit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atp *dev = container_of(work, काष्ठा atp, work);
	पूर्णांक retval;

	dprपूर्णांकk("appletouch: putting appletouch to sleep (reinit)\n");
	atp_geyser_init(dev);

	retval = usb_submit_urb(dev->urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->पूर्णांकf->dev,
			"atp_reinit: usb_submit_urb failed with error %d\n",
			retval);
पूर्ण

अटल पूर्णांक atp_calculate_असल(काष्ठा atp *dev, पूर्णांक offset, पूर्णांक nb_sensors,
			     पूर्णांक fact, पूर्णांक *z, पूर्णांक *fingers)
अणु
	पूर्णांक i, pass;

	/*
	 * Use offset to poपूर्णांक xy_sensors at the first value in dev->xy_acc
	 * क्रम whichever dimension we're looking at this particular go-round.
	 */
	पूर्णांक *xy_sensors = dev->xy_acc + offset;

	/* values to calculate mean */
	पूर्णांक pcum = 0, psum = 0;
	पूर्णांक is_increasing = 0;

	*fingers = 0;

	क्रम (i = 0; i < nb_sensors; i++) अणु
		अगर (xy_sensors[i] < threshold) अणु
			अगर (is_increasing)
				is_increasing = 0;

		/*
		 * Makes the finger detection more versatile.  For example,
		 * two fingers with no gap will be detected.  Also, my
		 * tests show it less likely to have पूर्णांकermittent loss
		 * of multiple finger पढ़ोings जबतक moving around (scrolling).
		 *
		 * Changes the multiple finger detection to counting humps on
		 * sensors (transitions from nonincreasing to increasing)
		 * instead of counting transitions from low sensors (no
		 * finger पढ़ोing) to high sensors (finger above
		 * sensor)
		 *
		 * - Jason Parekh <jasonparekh@gmail.com>
		 */

		पूर्ण अन्यथा अगर (i < 1 ||
		    (!is_increasing && xy_sensors[i - 1] < xy_sensors[i])) अणु
			(*fingers)++;
			is_increasing = 1;
		पूर्ण अन्यथा अगर (i > 0 && (xy_sensors[i - 1] - xy_sensors[i] > threshold)) अणु
			is_increasing = 0;
		पूर्ण
	पूर्ण

	अगर (*fingers < 1)     /* No need to जारी अगर no fingers are found. */
		वापस 0;

	/*
	 * Use a smoothed version of sensor data क्रम movement calculations, to
	 * combat noise without needing to rely so heavily on a threshold.
	 * This improves tracking.
	 *
	 * The smoothed array is bigger than the original so that the smoothing
	 * करोesn't result in edge values being truncated.
	 */

	स_रखो(dev->smooth, 0, 4 * माप(dev->smooth[0]));
	/* Pull base values, scaled up to help aव्योम truncation errors. */
	क्रम (i = 0; i < nb_sensors; i++)
		dev->smooth[i + 4] = xy_sensors[i] << ATP_SCALE;
	स_रखो(&dev->smooth[nb_sensors + 4], 0, 4 * माप(dev->smooth[0]));

	क्रम (pass = 0; pass < 4; pass++) अणु
		/* Handle edge. */
		dev->smooth_पंचांगp[0] = (dev->smooth[0] + dev->smooth[1]) / 2;

		/* Average values with neighbors. */
		क्रम (i = 1; i < nb_sensors + 7; i++)
			dev->smooth_पंचांगp[i] = (dev->smooth[i - 1] +
					      dev->smooth[i] * 2 +
					      dev->smooth[i + 1]) / 4;

		/* Handle other edge. */
		dev->smooth_पंचांगp[i] = (dev->smooth[i - 1] + dev->smooth[i]) / 2;

		स_नकल(dev->smooth, dev->smooth_पंचांगp, माप(dev->smooth));
	पूर्ण

	क्रम (i = 0; i < nb_sensors + 8; i++) अणु
		/*
		 * Skip values अगर they're small enough to be truncated to 0
		 * by scale. Mostly noise.
		 */
		अगर ((dev->smooth[i] >> ATP_SCALE) > 0) अणु
			pcum += dev->smooth[i] * i;
			psum += dev->smooth[i];
		पूर्ण
	पूर्ण

	अगर (psum > 0) अणु
		*z = psum >> ATP_SCALE;        /* Scale करोwn pressure output. */
		वापस pcum * fact / psum;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम atp_report_fingers(काष्ठा input_dev *input, पूर्णांक fingers)
अणु
	input_report_key(input, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(input, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(input, BTN_TOOL_TRIPLETAP, fingers > 2);
पूर्ण

/* Check URB status and क्रम correct length of data package */

#घोषणा ATP_URB_STATUS_SUCCESS		0
#घोषणा ATP_URB_STATUS_ERROR		1
#घोषणा ATP_URB_STATUS_ERROR_FATAL	2

अटल पूर्णांक atp_status_check(काष्ठा urb *urb)
अणु
	काष्ठा atp *dev = urb->context;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -EOVERFLOW:
		अगर (!dev->overflow_warned) अणु
			dev_warn(&पूर्णांकf->dev,
				"appletouch: OVERFLOW with data length %d, actual length is %d\n",
				dev->info->datalen, dev->urb->actual_length);
			dev->overflow_warned = true;
		पूर्ण
		fallthrough;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* This urb is terminated, clean up */
		dev_dbg(&पूर्णांकf->dev,
			"atp_complete: urb shutting down with status: %d\n",
			urb->status);
		वापस ATP_URB_STATUS_ERROR_FATAL;

	शेष:
		dev_dbg(&पूर्णांकf->dev,
			"atp_complete: nonzero urb status received: %d\n",
			urb->status);
		वापस ATP_URB_STATUS_ERROR;
	पूर्ण

	/* drop incomplete datasets */
	अगर (dev->urb->actual_length != dev->info->datalen) अणु
		dprपूर्णांकk("appletouch: incomplete data package"
			" (first byte: %d, length: %d).\n",
			dev->data[0], dev->urb->actual_length);
		वापस ATP_URB_STATUS_ERROR;
	पूर्ण

	वापस ATP_URB_STATUS_SUCCESS;
पूर्ण

अटल व्योम atp_detect_size(काष्ठा atp *dev)
अणु
	पूर्णांक i;

	/* 17" Powerbooks have extra X sensors */
	क्रम (i = dev->info->xsensors; i < ATP_XSENSORS; i++) अणु
		अगर (dev->xy_cur[i]) अणु

			dev_info(&dev->पूर्णांकf->dev,
				"appletouch: 17\" model detected.\n");

			input_set_असल_params(dev->input, ABS_X, 0,
					     (dev->info->xsensors_17 - 1) *
							dev->info->xfact - 1,
					     dev->info->fuzz, 0);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * USB पूर्णांकerrupt callback functions
 */

/* Interrupt function क्रम older touchpads: FOUNTAIN/GEYSER1/GEYSER2 */

अटल व्योम atp_complete_geyser_1_2(काष्ठा urb *urb)
अणु
	पूर्णांक x, y, x_z, y_z, x_f, y_f;
	पूर्णांक retval, i, j;
	पूर्णांक key, fingers;
	काष्ठा atp *dev = urb->context;
	पूर्णांक status = atp_status_check(urb);

	अगर (status == ATP_URB_STATUS_ERROR_FATAL)
		वापस;
	अन्यथा अगर (status == ATP_URB_STATUS_ERROR)
		जाओ निकास;

	/* reorder the sensors values */
	अगर (dev->info == &geyser2_info) अणु
		स_रखो(dev->xy_cur, 0, माप(dev->xy_cur));

		/*
		 * The values are laid out like this:
		 * Y1, Y2, -, Y3, Y4, -, ..., X1, X2, -, X3, X4, -, ...
		 * '-' is an unused value.
		 */

		/* पढ़ो X values */
		क्रम (i = 0, j = 19; i < 20; i += 2, j += 3) अणु
			dev->xy_cur[i] = dev->data[j];
			dev->xy_cur[i + 1] = dev->data[j + 1];
		पूर्ण

		/* पढ़ो Y values */
		क्रम (i = 0, j = 1; i < 9; i += 2, j += 3) अणु
			dev->xy_cur[ATP_XSENSORS + i] = dev->data[j];
			dev->xy_cur[ATP_XSENSORS + i + 1] = dev->data[j + 1];
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 8; i++) अणु
			/* X values */
			dev->xy_cur[i +  0] = dev->data[5 * i +  2];
			dev->xy_cur[i +  8] = dev->data[5 * i +  4];
			dev->xy_cur[i + 16] = dev->data[5 * i + 42];
			अगर (i < 2)
				dev->xy_cur[i + 24] = dev->data[5 * i + 44];

			/* Y values */
			dev->xy_cur[ATP_XSENSORS + i] = dev->data[5 * i +  1];
			dev->xy_cur[ATP_XSENSORS + i + 8] = dev->data[5 * i + 3];
		पूर्ण
	पूर्ण

	dbg_dump("sample", dev->xy_cur);

	अगर (!dev->valid) अणु
		/* first sample */
		dev->valid = true;
		dev->x_old = dev->y_old = -1;

		/* Store first sample */
		स_नकल(dev->xy_old, dev->xy_cur, माप(dev->xy_old));

		/* Perक्रमm size detection, अगर not करोne alपढ़ोy */
		अगर (unlikely(!dev->size_detect_करोne)) अणु
			atp_detect_size(dev);
			dev->size_detect_करोne = true;
			जाओ निकास;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ATP_XSENSORS + ATP_YSENSORS; i++) अणु
		/* accumulate the change */
		चिन्हित अक्षर change = dev->xy_old[i] - dev->xy_cur[i];
		dev->xy_acc[i] -= change;

		/* prevent करोwn drअगरting */
		अगर (dev->xy_acc[i] < 0)
			dev->xy_acc[i] = 0;
	पूर्ण

	स_नकल(dev->xy_old, dev->xy_cur, माप(dev->xy_old));

	dbg_dump("accumulator", dev->xy_acc);

	x = atp_calculate_असल(dev, 0, ATP_XSENSORS,
			      dev->info->xfact, &x_z, &x_f);
	y = atp_calculate_असल(dev, ATP_XSENSORS, ATP_YSENSORS,
			      dev->info->yfact, &y_z, &y_f);
	key = dev->data[dev->info->datalen - 1] & ATP_STATUS_BUTTON;

	fingers = max(x_f, y_f);

	अगर (x && y && fingers == dev->fingers_old) अणु
		अगर (dev->x_old != -1) अणु
			x = (dev->x_old * 7 + x) >> 3;
			y = (dev->y_old * 7 + y) >> 3;
			dev->x_old = x;
			dev->y_old = y;

			अगर (debug > 1)
				prपूर्णांकk(KERN_DEBUG "appletouch: "
					"X: %3d Y: %3d Xz: %3d Yz: %3d\n",
					x, y, x_z, y_z);

			input_report_key(dev->input, BTN_TOUCH, 1);
			input_report_असल(dev->input, ABS_X, x);
			input_report_असल(dev->input, ABS_Y, y);
			input_report_असल(dev->input, ABS_PRESSURE,
					 min(ATP_PRESSURE, x_z + y_z));
			atp_report_fingers(dev->input, fingers);
		पूर्ण
		dev->x_old = x;
		dev->y_old = y;

	पूर्ण अन्यथा अगर (!x && !y) अणु

		dev->x_old = dev->y_old = -1;
		dev->fingers_old = 0;
		input_report_key(dev->input, BTN_TOUCH, 0);
		input_report_असल(dev->input, ABS_PRESSURE, 0);
		atp_report_fingers(dev->input, 0);

		/* reset the accumulator on release */
		स_रखो(dev->xy_acc, 0, माप(dev->xy_acc));
	पूर्ण

	अगर (fingers != dev->fingers_old)
		dev->x_old = dev->y_old = -1;
	dev->fingers_old = fingers;

	input_report_key(dev->input, BTN_LEFT, key);
	input_sync(dev->input);

 निकास:
	retval = usb_submit_urb(dev->urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->पूर्णांकf->dev,
			"atp_complete: usb_submit_urb failed with result %d\n",
			retval);
पूर्ण

/* Interrupt function क्रम older touchpads: GEYSER3/GEYSER4 */

अटल व्योम atp_complete_geyser_3_4(काष्ठा urb *urb)
अणु
	पूर्णांक x, y, x_z, y_z, x_f, y_f;
	पूर्णांक retval, i, j;
	पूर्णांक key, fingers;
	काष्ठा atp *dev = urb->context;
	पूर्णांक status = atp_status_check(urb);

	अगर (status == ATP_URB_STATUS_ERROR_FATAL)
		वापस;
	अन्यथा अगर (status == ATP_URB_STATUS_ERROR)
		जाओ निकास;

	/* Reorder the sensors values:
	 *
	 * The values are laid out like this:
	 * -, Y1, Y2, -, Y3, Y4, -, ..., -, X1, X2, -, X3, X4, ...
	 * '-' is an unused value.
	 */

	/* पढ़ो X values */
	क्रम (i = 0, j = 19; i < 20; i += 2, j += 3) अणु
		dev->xy_cur[i] = dev->data[j + 1];
		dev->xy_cur[i + 1] = dev->data[j + 2];
	पूर्ण
	/* पढ़ो Y values */
	क्रम (i = 0, j = 1; i < 9; i += 2, j += 3) अणु
		dev->xy_cur[ATP_XSENSORS + i] = dev->data[j + 1];
		dev->xy_cur[ATP_XSENSORS + i + 1] = dev->data[j + 2];
	पूर्ण

	dbg_dump("sample", dev->xy_cur);

	/* Just update the base values (i.e. touchpad in untouched state) */
	अगर (dev->data[dev->info->datalen - 1] & ATP_STATUS_BASE_UPDATE) अणु

		dprपूर्णांकk("appletouch: updated base values\n");

		स_नकल(dev->xy_old, dev->xy_cur, माप(dev->xy_old));
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < ATP_XSENSORS + ATP_YSENSORS; i++) अणु
		/* calculate the change */
		dev->xy_acc[i] = dev->xy_cur[i] - dev->xy_old[i];

		/* this is a round-robin value, so couple with that */
		अगर (dev->xy_acc[i] > 127)
			dev->xy_acc[i] -= 256;

		अगर (dev->xy_acc[i] < -127)
			dev->xy_acc[i] += 256;

		/* prevent करोwn drअगरting */
		अगर (dev->xy_acc[i] < 0)
			dev->xy_acc[i] = 0;
	पूर्ण

	dbg_dump("accumulator", dev->xy_acc);

	x = atp_calculate_असल(dev, 0, ATP_XSENSORS,
			      dev->info->xfact, &x_z, &x_f);
	y = atp_calculate_असल(dev, ATP_XSENSORS, ATP_YSENSORS,
			      dev->info->yfact, &y_z, &y_f);

	key = dev->data[dev->info->datalen - 1] & ATP_STATUS_BUTTON;

	fingers = max(x_f, y_f);

	अगर (x && y && fingers == dev->fingers_old) अणु
		अगर (dev->x_old != -1) अणु
			x = (dev->x_old * 7 + x) >> 3;
			y = (dev->y_old * 7 + y) >> 3;
			dev->x_old = x;
			dev->y_old = y;

			अगर (debug > 1)
				prपूर्णांकk(KERN_DEBUG "appletouch: X: %3d Y: %3d "
				       "Xz: %3d Yz: %3d\n",
				       x, y, x_z, y_z);

			input_report_key(dev->input, BTN_TOUCH, 1);
			input_report_असल(dev->input, ABS_X, x);
			input_report_असल(dev->input, ABS_Y, y);
			input_report_असल(dev->input, ABS_PRESSURE,
					 min(ATP_PRESSURE, x_z + y_z));
			atp_report_fingers(dev->input, fingers);
		पूर्ण
		dev->x_old = x;
		dev->y_old = y;

	पूर्ण अन्यथा अगर (!x && !y) अणु

		dev->x_old = dev->y_old = -1;
		dev->fingers_old = 0;
		input_report_key(dev->input, BTN_TOUCH, 0);
		input_report_असल(dev->input, ABS_PRESSURE, 0);
		atp_report_fingers(dev->input, 0);

		/* reset the accumulator on release */
		स_रखो(dev->xy_acc, 0, माप(dev->xy_acc));
	पूर्ण

	अगर (fingers != dev->fingers_old)
		dev->x_old = dev->y_old = -1;
	dev->fingers_old = fingers;

	input_report_key(dev->input, BTN_LEFT, key);
	input_sync(dev->input);

	/*
	 * Geysers 3/4 will जारी to send packets continually after
	 * the first touch unless reinitialised. Do so अगर it's been
	 * idle क्रम a जबतक in order to aव्योम waking the kernel up
	 * several hundred बार a second.
	 */

	/*
	 * Button must not be pressed when entering suspend,
	 * otherwise we will never release the button.
	 */
	अगर (!x && !y && !key) अणु
		dev->idlecount++;
		अगर (dev->idlecount == 10) अणु
			dev->x_old = dev->y_old = -1;
			dev->idlecount = 0;
			schedule_work(&dev->work);
			/* Don't resubmit urb here, रुको क्रम reinit */
			वापस;
		पूर्ण
	पूर्ण अन्यथा
		dev->idlecount = 0;

 निकास:
	retval = usb_submit_urb(dev->urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->पूर्णांकf->dev,
			"atp_complete: usb_submit_urb failed with result %d\n",
			retval);
पूर्ण

अटल पूर्णांक atp_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा atp *dev = input_get_drvdata(input);

	अगर (usb_submit_urb(dev->urb, GFP_KERNEL))
		वापस -EIO;

	dev->खोलो = true;
	वापस 0;
पूर्ण

अटल व्योम atp_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा atp *dev = input_get_drvdata(input);

	usb_समाप्त_urb(dev->urb);
	cancel_work_sync(&dev->work);
	dev->खोलो = false;
पूर्ण

अटल पूर्णांक atp_handle_geyser(काष्ठा atp *dev)
अणु
	अगर (dev->info != &fountain_info) अणु
		/* चयन to raw sensor mode */
		अगर (atp_geyser_init(dev))
			वापस -EIO;

		dev_info(&dev->पूर्णांकf->dev, "Geyser mode initialized.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atp_probe(काष्ठा usb_पूर्णांकerface *अगरace,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा atp *dev;
	काष्ठा input_dev *input_dev;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(अगरace);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक पूर्णांक_in_endpoपूर्णांकAddr = 0;
	पूर्णांक i, error = -ENOMEM;
	स्थिर काष्ठा atp_info *info = (स्थिर काष्ठा atp_info *)id->driver_info;

	/* set up the endpoपूर्णांक inक्रमmation */
	/* use only the first पूर्णांकerrupt-in endpoपूर्णांक */
	अगरace_desc = अगरace->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (!पूर्णांक_in_endpoपूर्णांकAddr && usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक)) अणु
			/* we found an पूर्णांकerrupt in endpoपूर्णांक */
			पूर्णांक_in_endpoपूर्णांकAddr = endpoपूर्णांक->bEndpoपूर्णांकAddress;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!पूर्णांक_in_endpoपूर्णांकAddr) अणु
		dev_err(&अगरace->dev, "Could not find int-in endpoint\n");
		वापस -EIO;
	पूर्ण

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(काष्ठा atp), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!dev || !input_dev) अणु
		dev_err(&अगरace->dev, "Out of memory\n");
		जाओ err_मुक्त_devs;
	पूर्ण

	dev->udev = udev;
	dev->पूर्णांकf = अगरace;
	dev->input = input_dev;
	dev->info = info;
	dev->overflow_warned = false;

	dev->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->urb)
		जाओ err_मुक्त_devs;

	dev->data = usb_alloc_coherent(dev->udev, dev->info->datalen, GFP_KERNEL,
				       &dev->urb->transfer_dma);
	अगर (!dev->data)
		जाओ err_मुक्त_urb;

	usb_fill_पूर्णांक_urb(dev->urb, udev,
			 usb_rcvपूर्णांकpipe(udev, पूर्णांक_in_endpoपूर्णांकAddr),
			 dev->data, dev->info->datalen,
			 dev->info->callback, dev, 1);

	error = atp_handle_geyser(dev);
	अगर (error)
		जाओ err_मुक्त_buffer;

	usb_make_path(udev, dev->phys, माप(dev->phys));
	strlcat(dev->phys, "/input0", माप(dev->phys));

	input_dev->name = "appletouch";
	input_dev->phys = dev->phys;
	usb_to_input_id(dev->udev, &input_dev->id);
	input_dev->dev.parent = &अगरace->dev;

	input_set_drvdata(input_dev, dev);

	input_dev->खोलो = atp_खोलो;
	input_dev->बंद = atp_बंद;

	set_bit(EV_ABS, input_dev->evbit);

	input_set_असल_params(input_dev, ABS_X, 0,
			     (dev->info->xsensors - 1) * dev->info->xfact - 1,
			     dev->info->fuzz, 0);
	input_set_असल_params(input_dev, ABS_Y, 0,
			     (dev->info->ysensors - 1) * dev->info->yfact - 1,
			     dev->info->fuzz, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, 0, ATP_PRESSURE, 0, 0);

	set_bit(EV_KEY, input_dev->evbit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_FINGER, input_dev->keybit);
	set_bit(BTN_TOOL_DOUBLETAP, input_dev->keybit);
	set_bit(BTN_TOOL_TRIPLETAP, input_dev->keybit);
	set_bit(BTN_LEFT, input_dev->keybit);

	error = input_रेजिस्टर_device(dev->input);
	अगर (error)
		जाओ err_मुक्त_buffer;

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(अगरace, dev);

	INIT_WORK(&dev->work, atp_reinit);

	वापस 0;

 err_मुक्त_buffer:
	usb_मुक्त_coherent(dev->udev, dev->info->datalen,
			  dev->data, dev->urb->transfer_dma);
 err_मुक्त_urb:
	usb_मुक्त_urb(dev->urb);
 err_मुक्त_devs:
	usb_set_पूर्णांकfdata(अगरace, शून्य);
	kमुक्त(dev);
	input_मुक्त_device(input_dev);
	वापस error;
पूर्ण

अटल व्योम atp_disconnect(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा atp *dev = usb_get_पूर्णांकfdata(अगरace);

	usb_set_पूर्णांकfdata(अगरace, शून्य);
	अगर (dev) अणु
		usb_समाप्त_urb(dev->urb);
		input_unरेजिस्टर_device(dev->input);
		usb_मुक्त_coherent(dev->udev, dev->info->datalen,
				  dev->data, dev->urb->transfer_dma);
		usb_मुक्त_urb(dev->urb);
		kमुक्त(dev);
	पूर्ण
	dev_info(&अगरace->dev, "input: appletouch disconnected\n");
पूर्ण

अटल पूर्णांक atp_recover(काष्ठा atp *dev)
अणु
	पूर्णांक error;

	error = atp_handle_geyser(dev);
	अगर (error)
		वापस error;

	अगर (dev->खोलो && usb_submit_urb(dev->urb, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक atp_suspend(काष्ठा usb_पूर्णांकerface *अगरace, pm_message_t message)
अणु
	काष्ठा atp *dev = usb_get_पूर्णांकfdata(अगरace);

	usb_समाप्त_urb(dev->urb);
	वापस 0;
पूर्ण

अटल पूर्णांक atp_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा atp *dev = usb_get_पूर्णांकfdata(अगरace);

	अगर (dev->खोलो && usb_submit_urb(dev->urb, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक atp_reset_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा atp *dev = usb_get_पूर्णांकfdata(अगरace);

	वापस atp_recover(dev);
पूर्ण

अटल काष्ठा usb_driver atp_driver = अणु
	.name		= "appletouch",
	.probe		= atp_probe,
	.disconnect	= atp_disconnect,
	.suspend	= atp_suspend,
	.resume		= atp_resume,
	.reset_resume	= atp_reset_resume,
	.id_table	= atp_table,
पूर्ण;

module_usb_driver(atp_driver);
