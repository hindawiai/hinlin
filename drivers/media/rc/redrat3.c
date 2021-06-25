<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB RedRat3 IR Transceiver rc-core driver
 *
 * Copyright (c) 2011 by Jarod Wilson <jarod@redhat.com>
 *  based heavily on the work of Stephen Cox, with additional
 *  help from RedRat Ltd.
 *
 * This driver began lअगरe based an an old version of the first-generation
 * lirc_mceusb driver from the lirc 0.7.2 distribution. It was then
 * signअगरicantly rewritten by Stephen Cox with the aid of RedRat Ltd's
 * Chris Dodge.
 *
 * The driver was then ported to rc-core and signअगरicantly rewritten again,
 * by Jarod, using the in-kernel mceusb driver as a guide, after an initial
 * port efक्रमt was started by Stephen.
 *
 * TODO LIST:
 * - fix lirc not showing repeats properly
 * --
 *
 * The RedRat3 is a USB transceiver with both send & receive,
 * with 2 separate sensors available क्रम receive to enable
 * both good दीर्घ range reception क्रम general use, and good
 * लघु range reception when required क्रम learning a संकेत.
 *
 * http://www.redrat.co.uk/
 *
 * It uses its own little protocol to communicate, the required
 * parts of which are embedded within this driver.
 * --
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/device.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <media/rc-core.h>

/* Driver Inक्रमmation */
#घोषणा DRIVER_AUTHOR "Jarod Wilson <jarod@redhat.com>"
#घोषणा DRIVER_AUTHOR2 "The Dweller, Stephen Cox"
#घोषणा DRIVER_DESC "RedRat3 USB IR Transceiver Driver"
#घोषणा DRIVER_NAME "redrat3"

/* bulk data transfer types */
#घोषणा RR3_ERROR		0x01
#घोषणा RR3_MOD_SIGNAL_IN	0x20
#घोषणा RR3_MOD_SIGNAL_OUT	0x21

/* Get the RR firmware version */
#घोषणा RR3_FW_VERSION		0xb1
#घोषणा RR3_FW_VERSION_LEN	64
/* Send encoded संकेत bulk-sent earlier*/
#घोषणा RR3_TX_SEND_SIGNAL	0xb3
#घोषणा RR3_SET_IR_PARAM	0xb7
#घोषणा RR3_GET_IR_PARAM	0xb8
/* Blink the red LED on the device */
#घोषणा RR3_BLINK_LED		0xb9
/* Read serial number of device */
#घोषणा RR3_READ_SER_NO		0xba
#घोषणा RR3_SER_NO_LEN		4
/* Start capture with the RC receiver */
#घोषणा RR3_RC_DET_ENABLE	0xbb
/* Stop capture with the RC receiver */
#घोषणा RR3_RC_DET_DISABLE	0xbc
/* Start capture with the wideband receiver */
#घोषणा RR3_MODSIG_CAPTURE     0xb2
/* Return the status of RC detector capture */
#घोषणा RR3_RC_DET_STATUS	0xbd
/* Reset redrat */
#घोषणा RR3_RESET		0xa0

/* Max number of lengths in the संकेत. */
#घोषणा RR3_IR_IO_MAX_LENGTHS	0x01
/* Periods to measure mod. freq. */
#घोषणा RR3_IR_IO_PERIODS_MF	0x02
/* Size of memory क्रम मुख्य संकेत data */
#घोषणा RR3_IR_IO_SIG_MEM_SIZE	0x03
/* Delta value when measuring lengths */
#घोषणा RR3_IR_IO_LENGTH_FUZZ	0x04
/* Timeout क्रम end of संकेत detection */
#घोषणा RR3_IR_IO_SIG_TIMEOUT	0x05
/* Minimum value क्रम छोड़ो recognition. */
#घोषणा RR3_IR_IO_MIN_PAUSE	0x06

/* Clock freq. of EZ-USB chip */
#घोषणा RR3_CLK			24000000
/* Clock periods per समयr count */
#घोषणा RR3_CLK_PER_COUNT	12
/* (RR3_CLK / RR3_CLK_PER_COUNT) */
#घोषणा RR3_CLK_CONV_FACTOR	2000000
/* USB bulk-in wideband IR data endpoपूर्णांक address */
#घोषणा RR3_WIDE_IN_EP_ADDR	0x81
/* USB bulk-in narrowband IR data endpoपूर्णांक address */
#घोषणा RR3_NARROW_IN_EP_ADDR	0x82

/* Size of the fixed-length portion of the संकेत */
#घोषणा RR3_DRIVER_MAXLENS	255
#घोषणा RR3_MAX_SIG_SIZE	512
#घोषणा RR3_TIME_UNIT		50
#घोषणा RR3_END_OF_SIGNAL	0x7f
#घोषणा RR3_TX_TRAILER_LEN	2
#घोषणा RR3_RX_MIN_TIMEOUT	5
#घोषणा RR3_RX_MAX_TIMEOUT	2000

/* The 8051's CPUCS Register address */
#घोषणा RR3_CPUCS_REG_ADDR	0x7f92

#घोषणा USB_RR3USB_VENDOR_ID	0x112a
#घोषणा USB_RR3USB_PRODUCT_ID	0x0001
#घोषणा USB_RR3IIUSB_PRODUCT_ID	0x0005


/*
 * The redrat3 encodes an IR संकेत as set of dअगरferent lengths and a set
 * of indices पूर्णांकo those lengths. This sets how much two lengths must
 * dअगरfer beक्रमe they are considered distinct, the value is specअगरied
 * in microseconds.
 * Default 5, value 0 to 127.
 */
अटल पूर्णांक length_fuzz = 5;
module_param(length_fuzz, uपूर्णांक, 0644);
MODULE_PARM_DESC(length_fuzz, "Length Fuzz (0-127)");

/*
 * When receiving a continuous ir stream (क्रम example when a user is
 * holding a button करोwn on a remote), this specअगरies the minimum size
 * of a space when the redrat3 sends a irdata packet to the host. Specअगरied
 * in milliseconds. Default value 18ms.
 * The value can be between 2 and 30 inclusive.
 */
अटल पूर्णांक minimum_छोड़ो = 18;
module_param(minimum_छोड़ो, uपूर्णांक, 0644);
MODULE_PARM_DESC(minimum_छोड़ो, "Minimum Pause in ms (2-30)");

/*
 * The carrier frequency is measured during the first pulse of the IR
 * संकेत. The larger the number of periods used To measure, the more
 * accurate the result is likely to be, however some संकेतs have लघु
 * initial pulses, so in some हाल it may be necessary to reduce this value.
 * Default 8, value 1 to 255.
 */
अटल पूर्णांक periods_measure_carrier = 8;
module_param(periods_measure_carrier, uपूर्णांक, 0644);
MODULE_PARM_DESC(periods_measure_carrier, "Number of Periods to Measure Carrier (1-255)");


काष्ठा redrat3_header अणु
	__be16 length;
	__be16 transfer_type;
पूर्ण __packed;

/* sending and receiving irdata */
काष्ठा redrat3_irdata अणु
	काष्ठा redrat3_header header;
	__be32 छोड़ो;
	__be16 mod_freq_count;
	__be16 num_periods;
	__u8 max_lengths;
	__u8 no_lengths;
	__be16 max_sig_size;
	__be16 sig_size;
	__u8 no_repeats;
	__be16 lens[RR3_DRIVER_MAXLENS]; /* not aligned */
	__u8 sigdata[RR3_MAX_SIG_SIZE];
पूर्ण __packed;

/* firmware errors */
काष्ठा redrat3_error अणु
	काष्ठा redrat3_header header;
	__be16 fw_error;
पूर्ण __packed;

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id redrat3_dev_table[] = अणु
	/* Original version of the RedRat3 */
	अणुUSB_DEVICE(USB_RR3USB_VENDOR_ID, USB_RR3USB_PRODUCT_ID)पूर्ण,
	/* Second Version/release of the RedRat3 - RetRat3-II */
	अणुUSB_DEVICE(USB_RR3USB_VENDOR_ID, USB_RR3IIUSB_PRODUCT_ID)पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;

/* Structure to hold all of our device specअगरic stuff */
काष्ठा redrat3_dev अणु
	/* core device bits */
	काष्ठा rc_dev *rc;
	काष्ठा device *dev;

	/* led control */
	काष्ठा led_classdev led;
	atomic_t flash;
	काष्ठा usb_ctrlrequest flash_control;
	काष्ठा urb *flash_urb;
	u8 flash_in_buf;

	/* learning */
	bool wideband;
	काष्ठा usb_ctrlrequest learn_control;
	काष्ठा urb *learn_urb;
	u8 learn_buf;

	/* save off the usb device poपूर्णांकer */
	काष्ठा usb_device *udev;

	/* the receive endpoपूर्णांक */
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_narrow;
	/* the buffer to receive data */
	व्योम *bulk_in_buf;
	/* urb used to पढ़ो ir data */
	काष्ठा urb *narrow_urb;
	काष्ठा urb *wide_urb;

	/* the send endpoपूर्णांक */
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_out;

	/* usb dma */
	dma_addr_t dma_in;

	/* Is the device currently transmitting?*/
	bool transmitting;

	/* store क्रम current packet */
	काष्ठा redrat3_irdata irdata;
	u16 bytes_पढ़ो;

	u32 carrier;

	अक्षर name[64];
	अक्षर phys[64];
पूर्ण;

अटल व्योम redrat3_dump_fw_error(काष्ठा redrat3_dev *rr3, पूर्णांक code)
अणु
	अगर (!rr3->transmitting && (code != 0x40))
		dev_info(rr3->dev, "fw error code 0x%02x: ", code);

	चयन (code) अणु
	हाल 0x00:
		pr_cont("No Error\n");
		अवरोध;

	/* Codes 0x20 through 0x2f are IR Firmware Errors */
	हाल 0x20:
		pr_cont("Initial signal pulse not long enough to measure carrier frequency\n");
		अवरोध;
	हाल 0x21:
		pr_cont("Not enough length values allocated for signal\n");
		अवरोध;
	हाल 0x22:
		pr_cont("Not enough memory allocated for signal data\n");
		अवरोध;
	हाल 0x23:
		pr_cont("Too many signal repeats\n");
		अवरोध;
	हाल 0x28:
		pr_cont("Insufficient memory available for IR signal data memory allocation\n");
		अवरोध;
	हाल 0x29:
		pr_cont("Insufficient memory available for IrDa signal data memory allocation\n");
		अवरोध;

	/* Codes 0x30 through 0x3f are USB Firmware Errors */
	हाल 0x30:
		pr_cont("Insufficient memory available for bulk transfer structure\n");
		अवरोध;

	/*
	 * Other error codes... These are primarily errors that can occur in
	 * the control messages sent to the redrat
	 */
	हाल 0x40:
		अगर (!rr3->transmitting)
			pr_cont("Signal capture has been terminated\n");
		अवरोध;
	हाल 0x41:
		pr_cont("Attempt to set/get and unknown signal I/O algorithm parameter\n");
		अवरोध;
	हाल 0x42:
		pr_cont("Signal capture already started\n");
		अवरोध;

	शेष:
		pr_cont("Unknown Error\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 redrat3_val_to_mod_freq(काष्ठा redrat3_irdata *irdata)
अणु
	u32 mod_freq = 0;
	u16 mod_freq_count = be16_to_cpu(irdata->mod_freq_count);

	अगर (mod_freq_count != 0)
		mod_freq = (RR3_CLK * be16_to_cpu(irdata->num_periods)) /
			(mod_freq_count * RR3_CLK_PER_COUNT);

	वापस mod_freq;
पूर्ण

/* this function scales करोwn the figures क्रम the same result... */
अटल u32 redrat3_len_to_us(u32 length)
अणु
	u32 biglen = length * 1000;
	u32 भागisor = (RR3_CLK_CONV_FACTOR) / 1000;
	u32 result = (u32) (biglen / भागisor);

	/* करोn't allow zero lengths to go back, अवरोधs lirc */
	वापस result ? result : 1;
पूर्ण

/*
 * convert us back पूर्णांकo redrat3 lengths
 *
 * length * 1000   length * 1000000
 * ------------- = ---------------- = micro
 * rr3clk / 1000       rr3clk

 * 6 * 2       4 * 3        micro * rr3clk          micro * rr3clk / 1000
 * ----- = 4   ----- = 6    -------------- = len    ---------------------
 *   3           2             1000000                    1000
 */
अटल u32 redrat3_us_to_len(u32 microsec)
अणु
	u32 result;
	u32 भागisor;

	microsec = (microsec > IR_MAX_DURATION) ? IR_MAX_DURATION : microsec;
	भागisor = (RR3_CLK_CONV_FACTOR / 1000);
	result = (u32)(microsec * भागisor) / 1000;

	/* करोn't allow zero lengths to go back, अवरोधs lirc */
	वापस result ? result : 1;
पूर्ण

अटल व्योम redrat3_process_ir_data(काष्ठा redrat3_dev *rr3)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक i, sig_size, offset, val;
	u32 mod_freq;

	dev = rr3->dev;

	mod_freq = redrat3_val_to_mod_freq(&rr3->irdata);
	dev_dbg(dev, "Got mod_freq of %u\n", mod_freq);
	अगर (mod_freq && rr3->wideband) अणु
		काष्ठा ir_raw_event ev = अणु
			.carrier_report = 1,
			.carrier = mod_freq
		पूर्ण;

		ir_raw_event_store(rr3->rc, &ev);
	पूर्ण

	/* process each rr3 encoded byte पूर्णांकo an पूर्णांक */
	sig_size = be16_to_cpu(rr3->irdata.sig_size);
	क्रम (i = 0; i < sig_size; i++) अणु
		offset = rr3->irdata.sigdata[i];
		val = get_unaligned_be16(&rr3->irdata.lens[offset]);

		/* we should always get pulse/space/pulse/space samples */
		अगर (i % 2)
			rawir.pulse = false;
		अन्यथा
			rawir.pulse = true;

		rawir.duration = redrat3_len_to_us(val);
		/* cap the value to IR_MAX_DURATION */
		rawir.duration = (rawir.duration > IR_MAX_DURATION) ?
				 IR_MAX_DURATION : rawir.duration;

		dev_dbg(dev, "storing %s with duration %d (i: %d)\n",
			rawir.pulse ? "pulse" : "space", rawir.duration, i);
		ir_raw_event_store_with_filter(rr3->rc, &rawir);
	पूर्ण

	/* add a trailing space */
	rawir.pulse = false;
	rawir.समयout = true;
	rawir.duration = rr3->rc->समयout;
	dev_dbg(dev, "storing trailing timeout with duration %d\n",
							rawir.duration);
	ir_raw_event_store_with_filter(rr3->rc, &rawir);

	dev_dbg(dev, "calling ir_raw_event_handle\n");
	ir_raw_event_handle(rr3->rc);
पूर्ण

/* Util fn to send rr3 cmds */
अटल पूर्णांक redrat3_send_cmd(पूर्णांक cmd, काष्ठा redrat3_dev *rr3)
अणु
	काष्ठा usb_device *udev;
	u8 *data;
	पूर्णांक res;

	data = kzalloc(माप(u8), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	udev = rr3->udev;
	res = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), cmd,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			      0x0000, 0x0000, data, माप(u8), HZ * 10);

	अगर (res < 0) अणु
		dev_err(rr3->dev, "%s: Error sending rr3 cmd res %d, data %d",
			__func__, res, *data);
		res = -EIO;
	पूर्ण अन्यथा
		res = data[0];

	kमुक्त(data);

	वापस res;
पूर्ण

/* Enables the दीर्घ range detector and starts async receive */
अटल पूर्णांक redrat3_enable_detector(काष्ठा redrat3_dev *rr3)
अणु
	काष्ठा device *dev = rr3->dev;
	u8 ret;

	ret = redrat3_send_cmd(RR3_RC_DET_ENABLE, rr3);
	अगर (ret != 0)
		dev_dbg(dev, "%s: unexpected ret of %d\n",
			__func__, ret);

	ret = redrat3_send_cmd(RR3_RC_DET_STATUS, rr3);
	अगर (ret != 1) अणु
		dev_err(dev, "%s: detector status: %d, should be 1\n",
			__func__, ret);
		वापस -EIO;
	पूर्ण

	ret = usb_submit_urb(rr3->narrow_urb, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(rr3->dev, "narrow band urb failed: %d", ret);
		वापस ret;
	पूर्ण

	ret = usb_submit_urb(rr3->wide_urb, GFP_KERNEL);
	अगर (ret)
		dev_err(rr3->dev, "wide band urb failed: %d", ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम redrat3_delete(काष्ठा redrat3_dev *rr3,
				  काष्ठा usb_device *udev)
अणु
	usb_समाप्त_urb(rr3->narrow_urb);
	usb_समाप्त_urb(rr3->wide_urb);
	usb_समाप्त_urb(rr3->flash_urb);
	usb_समाप्त_urb(rr3->learn_urb);
	usb_मुक्त_urb(rr3->narrow_urb);
	usb_मुक्त_urb(rr3->wide_urb);
	usb_मुक्त_urb(rr3->flash_urb);
	usb_मुक्त_urb(rr3->learn_urb);
	usb_मुक्त_coherent(udev, le16_to_cpu(rr3->ep_narrow->wMaxPacketSize),
			  rr3->bulk_in_buf, rr3->dma_in);

	kमुक्त(rr3);
पूर्ण

अटल u32 redrat3_get_समयout(काष्ठा redrat3_dev *rr3)
अणु
	__be32 *पंचांगp;
	u32 समयout = MS_TO_US(150); /* a sane शेष, अगर things go haywire */
	पूर्णांक len, ret, pipe;

	len = माप(*पंचांगp);
	पंचांगp = kzalloc(len, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस समयout;

	pipe = usb_rcvctrlpipe(rr3->udev, 0);
	ret = usb_control_msg(rr3->udev, pipe, RR3_GET_IR_PARAM,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			      RR3_IR_IO_SIG_TIMEOUT, 0, पंचांगp, len, HZ * 5);
	अगर (ret != len)
		dev_warn(rr3->dev, "Failed to read timeout from hardware\n");
	अन्यथा अणु
		समयout = redrat3_len_to_us(be32_to_cpup(पंचांगp));

		dev_dbg(rr3->dev, "Got timeout of %d ms\n", समयout / 1000);
	पूर्ण

	kमुक्त(पंचांगp);

	वापस समयout;
पूर्ण

अटल पूर्णांक redrat3_set_समयout(काष्ठा rc_dev *rc_dev, अचिन्हित पूर्णांक समयoutus)
अणु
	काष्ठा redrat3_dev *rr3 = rc_dev->priv;
	काष्ठा usb_device *udev = rr3->udev;
	काष्ठा device *dev = rr3->dev;
	__be32 *समयout;
	पूर्णांक ret;

	समयout = kदो_स्मृति(माप(*समयout), GFP_KERNEL);
	अगर (!समयout)
		वापस -ENOMEM;

	*समयout = cpu_to_be32(redrat3_us_to_len(समयoutus));
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), RR3_SET_IR_PARAM,
		     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
		     RR3_IR_IO_SIG_TIMEOUT, 0, समयout, माप(*समयout),
		     HZ * 25);
	dev_dbg(dev, "set ir parm timeout %d ret 0x%02x\n",
						be32_to_cpu(*समयout), ret);

	अगर (ret == माप(*समयout))
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;

	kमुक्त(समयout);

	वापस ret;
पूर्ण

अटल व्योम redrat3_reset(काष्ठा redrat3_dev *rr3)
अणु
	काष्ठा usb_device *udev = rr3->udev;
	काष्ठा device *dev = rr3->dev;
	पूर्णांक rc, rxpipe, txpipe;
	u8 *val;
	माप_प्रकार स्थिर len = माप(*val);

	rxpipe = usb_rcvctrlpipe(udev, 0);
	txpipe = usb_sndctrlpipe(udev, 0);

	val = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!val)
		वापस;

	*val = 0x01;
	rc = usb_control_msg(udev, rxpipe, RR3_RESET,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			     RR3_CPUCS_REG_ADDR, 0, val, len, HZ * 25);
	dev_dbg(dev, "reset returned 0x%02x\n", rc);

	*val = length_fuzz;
	rc = usb_control_msg(udev, txpipe, RR3_SET_IR_PARAM,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			     RR3_IR_IO_LENGTH_FUZZ, 0, val, len, HZ * 25);
	dev_dbg(dev, "set ir parm len fuzz %d rc 0x%02x\n", *val, rc);

	*val = (65536 - (minimum_छोड़ो * 2000)) / 256;
	rc = usb_control_msg(udev, txpipe, RR3_SET_IR_PARAM,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			     RR3_IR_IO_MIN_PAUSE, 0, val, len, HZ * 25);
	dev_dbg(dev, "set ir parm min pause %d rc 0x%02x\n", *val, rc);

	*val = periods_measure_carrier;
	rc = usb_control_msg(udev, txpipe, RR3_SET_IR_PARAM,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			     RR3_IR_IO_PERIODS_MF, 0, val, len, HZ * 25);
	dev_dbg(dev, "set ir parm periods measure carrier %d rc 0x%02x", *val,
									rc);

	*val = RR3_DRIVER_MAXLENS;
	rc = usb_control_msg(udev, txpipe, RR3_SET_IR_PARAM,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
			     RR3_IR_IO_MAX_LENGTHS, 0, val, len, HZ * 25);
	dev_dbg(dev, "set ir parm max lens %d rc 0x%02x\n", *val, rc);

	kमुक्त(val);
पूर्ण

अटल व्योम redrat3_get_firmware_rev(काष्ठा redrat3_dev *rr3)
अणु
	पूर्णांक rc;
	अक्षर *buffer;

	buffer = kसुस्मृति(RR3_FW_VERSION_LEN + 1, माप(*buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस;

	rc = usb_control_msg(rr3->udev, usb_rcvctrlpipe(rr3->udev, 0),
			     RR3_FW_VERSION,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			     0, 0, buffer, RR3_FW_VERSION_LEN, HZ * 5);

	अगर (rc >= 0)
		dev_info(rr3->dev, "Firmware rev: %s", buffer);
	अन्यथा
		dev_err(rr3->dev, "Problem fetching firmware ID\n");

	kमुक्त(buffer);
पूर्ण

अटल व्योम redrat3_पढ़ो_packet_start(काष्ठा redrat3_dev *rr3, अचिन्हित len)
अणु
	काष्ठा redrat3_header *header = rr3->bulk_in_buf;
	अचिन्हित pktlen, pkttype;

	/* grab the Length and type of transfer */
	pktlen = be16_to_cpu(header->length);
	pkttype = be16_to_cpu(header->transfer_type);

	अगर (pktlen > माप(rr3->irdata)) अणु
		dev_warn(rr3->dev, "packet length %u too large\n", pktlen);
		वापस;
	पूर्ण

	चयन (pkttype) अणु
	हाल RR3_ERROR:
		अगर (len >= माप(काष्ठा redrat3_error)) अणु
			काष्ठा redrat3_error *error = rr3->bulk_in_buf;
			अचिन्हित fw_error = be16_to_cpu(error->fw_error);
			redrat3_dump_fw_error(rr3, fw_error);
		पूर्ण
		अवरोध;

	हाल RR3_MOD_SIGNAL_IN:
		स_नकल(&rr3->irdata, rr3->bulk_in_buf, len);
		rr3->bytes_पढ़ो = len;
		dev_dbg(rr3->dev, "bytes_read %d, pktlen %d\n",
			rr3->bytes_पढ़ो, pktlen);
		अवरोध;

	शेष:
		dev_dbg(rr3->dev, "ignoring packet with type 0x%02x, len of %d, 0x%02x\n",
						pkttype, len, pktlen);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम redrat3_पढ़ो_packet_जारी(काष्ठा redrat3_dev *rr3, अचिन्हित len)
अणु
	व्योम *irdata = &rr3->irdata;

	अगर (len + rr3->bytes_पढ़ो > माप(rr3->irdata)) अणु
		dev_warn(rr3->dev, "too much data for packet\n");
		rr3->bytes_पढ़ो = 0;
		वापस;
	पूर्ण

	स_नकल(irdata + rr3->bytes_पढ़ो, rr3->bulk_in_buf, len);

	rr3->bytes_पढ़ो += len;
	dev_dbg(rr3->dev, "bytes_read %d, pktlen %d\n", rr3->bytes_पढ़ो,
				 be16_to_cpu(rr3->irdata.header.length));
पूर्ण

/* gather IR data from incoming urb, process it when we have enough */
अटल पूर्णांक redrat3_get_ir_data(काष्ठा redrat3_dev *rr3, अचिन्हित len)
अणु
	काष्ठा device *dev = rr3->dev;
	अचिन्हित pkttype;
	पूर्णांक ret = 0;

	अगर (rr3->bytes_पढ़ो == 0 && len >= माप(काष्ठा redrat3_header)) अणु
		redrat3_पढ़ो_packet_start(rr3, len);
	पूर्ण अन्यथा अगर (rr3->bytes_पढ़ो != 0) अणु
		redrat3_पढ़ो_packet_जारी(rr3, len);
	पूर्ण अन्यथा अगर (rr3->bytes_पढ़ो == 0) अणु
		dev_err(dev, "error: no packet data read\n");
		ret = -ENODATA;
		जाओ out;
	पूर्ण

	अगर (rr3->bytes_पढ़ो < be16_to_cpu(rr3->irdata.header.length) +
						माप(काष्ठा redrat3_header))
		/* we're still accumulating data */
		वापस 0;

	/* अगर we get here, we've got IR data to decode */
	pkttype = be16_to_cpu(rr3->irdata.header.transfer_type);
	अगर (pkttype == RR3_MOD_SIGNAL_IN)
		redrat3_process_ir_data(rr3);
	अन्यथा
		dev_dbg(dev, "discarding non-signal data packet (type 0x%02x)\n",
								pkttype);

out:
	rr3->bytes_पढ़ो = 0;
	वापस ret;
पूर्ण

/* callback function from USB when async USB request has completed */
अटल व्योम redrat3_handle_async(काष्ठा urb *urb)
अणु
	काष्ठा redrat3_dev *rr3 = urb->context;
	पूर्णांक ret;

	चयन (urb->status) अणु
	हाल 0:
		ret = redrat3_get_ir_data(rr3, urb->actual_length);
		अगर (!ret && rr3->wideband && !rr3->learn_urb->hcpriv) अणु
			ret = usb_submit_urb(rr3->learn_urb, GFP_ATOMIC);
			अगर (ret)
				dev_err(rr3->dev, "Failed to submit learning urb: %d",
									ret);
		पूर्ण

		अगर (!ret) अणु
			/* no error, prepare to पढ़ो more */
			ret = usb_submit_urb(urb, GFP_ATOMIC);
			अगर (ret)
				dev_err(rr3->dev, "Failed to resubmit urb: %d",
									ret);
		पूर्ण
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;

	हाल -EPIPE:
	शेष:
		dev_warn(rr3->dev, "Error: urb status = %d\n", urb->status);
		rr3->bytes_पढ़ो = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल u16 mod_freq_to_val(अचिन्हित पूर्णांक mod_freq)
अणु
	पूर्णांक mult = 6000000;

	/* Clk used in mod. freq. generation is CLK24/4. */
	वापस 65536 - (mult / mod_freq);
पूर्ण

अटल पूर्णांक redrat3_set_tx_carrier(काष्ठा rc_dev *rcdev, u32 carrier)
अणु
	काष्ठा redrat3_dev *rr3 = rcdev->priv;
	काष्ठा device *dev = rr3->dev;

	dev_dbg(dev, "Setting modulation frequency to %u", carrier);
	अगर (carrier == 0)
		वापस -EINVAL;

	rr3->carrier = carrier;

	वापस 0;
पूर्ण

अटल पूर्णांक redrat3_transmit_ir(काष्ठा rc_dev *rcdev, अचिन्हित *txbuf,
				अचिन्हित count)
अणु
	काष्ठा redrat3_dev *rr3 = rcdev->priv;
	काष्ठा device *dev = rr3->dev;
	काष्ठा redrat3_irdata *irdata = शून्य;
	पूर्णांक ret, ret_len;
	पूर्णांक lencheck, cur_sample_len, pipe;
	पूर्णांक *sample_lens = शून्य;
	u8 curlencheck = 0;
	अचिन्हित i, sendbuf_len;

	अगर (rr3->transmitting) अणु
		dev_warn(dev, "%s: transmitter already in use\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	अगर (count > RR3_MAX_SIG_SIZE - RR3_TX_TRAILER_LEN)
		वापस -EINVAL;

	/* rr3 will disable rc detector on transmit */
	rr3->transmitting = true;

	sample_lens = kसुस्मृति(RR3_DRIVER_MAXLENS,
			      माप(*sample_lens),
			      GFP_KERNEL);
	अगर (!sample_lens)
		वापस -ENOMEM;

	irdata = kzalloc(माप(*irdata), GFP_KERNEL);
	अगर (!irdata) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		cur_sample_len = redrat3_us_to_len(txbuf[i]);
		अगर (cur_sample_len > 0xffff) अणु
			dev_warn(dev, "transmit period of %uus truncated to %uus\n",
					txbuf[i], redrat3_len_to_us(0xffff));
			cur_sample_len = 0xffff;
		पूर्ण
		क्रम (lencheck = 0; lencheck < curlencheck; lencheck++) अणु
			अगर (sample_lens[lencheck] == cur_sample_len)
				अवरोध;
		पूर्ण
		अगर (lencheck == curlencheck) अणु
			dev_dbg(dev, "txbuf[%d]=%u, pos %d, enc %u\n",
				i, txbuf[i], curlencheck, cur_sample_len);
			अगर (curlencheck < RR3_DRIVER_MAXLENS) अणु
				/* now convert the value to a proper
				 * rr3 value.. */
				sample_lens[curlencheck] = cur_sample_len;
				put_unaligned_be16(cur_sample_len,
						&irdata->lens[curlencheck]);
				curlencheck++;
			पूर्ण अन्यथा अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
		irdata->sigdata[i] = lencheck;
	पूर्ण

	irdata->sigdata[count] = RR3_END_OF_SIGNAL;
	irdata->sigdata[count + 1] = RR3_END_OF_SIGNAL;

	sendbuf_len = दुरत्व(काष्ठा redrat3_irdata,
					sigdata[count + RR3_TX_TRAILER_LEN]);
	/* fill in our packet header */
	irdata->header.length = cpu_to_be16(sendbuf_len -
						माप(काष्ठा redrat3_header));
	irdata->header.transfer_type = cpu_to_be16(RR3_MOD_SIGNAL_OUT);
	irdata->छोड़ो = cpu_to_be32(redrat3_len_to_us(100));
	irdata->mod_freq_count = cpu_to_be16(mod_freq_to_val(rr3->carrier));
	irdata->no_lengths = curlencheck;
	irdata->sig_size = cpu_to_be16(count + RR3_TX_TRAILER_LEN);

	pipe = usb_sndbulkpipe(rr3->udev, rr3->ep_out->bEndpoपूर्णांकAddress);
	ret = usb_bulk_msg(rr3->udev, pipe, irdata,
			    sendbuf_len, &ret_len, 10 * HZ);
	dev_dbg(dev, "sent %d bytes, (ret %d)\n", ret_len, ret);

	/* now tell the hardware to transmit what we sent it */
	pipe = usb_rcvctrlpipe(rr3->udev, 0);
	ret = usb_control_msg(rr3->udev, pipe, RR3_TX_SEND_SIGNAL,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			      0, 0, irdata, 2, HZ * 10);

	अगर (ret < 0)
		dev_err(dev, "Error: control msg send failed, rc %d\n", ret);
	अन्यथा
		ret = count;

out:
	kमुक्त(irdata);
	kमुक्त(sample_lens);

	rr3->transmitting = false;
	/* rr3 re-enables rc detector because it was enabled beक्रमe */

	वापस ret;
पूर्ण

अटल व्योम redrat3_brightness_set(काष्ठा led_classdev *led_dev, क्रमागत
						led_brightness brightness)
अणु
	काष्ठा redrat3_dev *rr3 = container_of(led_dev, काष्ठा redrat3_dev,
									led);

	अगर (brightness != LED_OFF && atomic_cmpxchg(&rr3->flash, 0, 1) == 0) अणु
		पूर्णांक ret = usb_submit_urb(rr3->flash_urb, GFP_ATOMIC);
		अगर (ret != 0) अणु
			dev_dbg(rr3->dev, "%s: unexpected ret of %d\n",
				__func__, ret);
			atomic_set(&rr3->flash, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक redrat3_wideband_receiver(काष्ठा rc_dev *rcdev, पूर्णांक enable)
अणु
	काष्ठा redrat3_dev *rr3 = rcdev->priv;
	पूर्णांक ret = 0;

	rr3->wideband = enable != 0;

	अगर (enable) अणु
		ret = usb_submit_urb(rr3->learn_urb, GFP_KERNEL);
		अगर (ret)
			dev_err(rr3->dev, "Failed to submit learning urb: %d",
									ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम redrat3_learn_complete(काष्ठा urb *urb)
अणु
	काष्ठा redrat3_dev *rr3 = urb->context;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;
	हाल -EPIPE:
	शेष:
		dev_err(rr3->dev, "Error: learn urb status = %d", urb->status);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम redrat3_led_complete(काष्ठा urb *urb)
अणु
	काष्ठा redrat3_dev *rr3 = urb->context;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;
	हाल -EPIPE:
	शेष:
		dev_dbg(rr3->dev, "Error: urb status = %d\n", urb->status);
		अवरोध;
	पूर्ण

	rr3->led.brightness = LED_OFF;
	atomic_dec(&rr3->flash);
पूर्ण

अटल काष्ठा rc_dev *redrat3_init_rc_dev(काष्ठा redrat3_dev *rr3)
अणु
	काष्ठा device *dev = rr3->dev;
	काष्ठा rc_dev *rc;
	पूर्णांक ret;
	u16 prod = le16_to_cpu(rr3->udev->descriptor.idProduct);

	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rc)
		वापस शून्य;

	snम_लिखो(rr3->name, माप(rr3->name),
		 "RedRat3%s Infrared Remote Transceiver",
		 prod == USB_RR3IIUSB_PRODUCT_ID ? "-II" : "");

	usb_make_path(rr3->udev, rr3->phys, माप(rr3->phys));

	rc->device_name = rr3->name;
	rc->input_phys = rr3->phys;
	usb_to_input_id(rr3->udev, &rc->input_id);
	rc->dev.parent = dev;
	rc->priv = rr3;
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->min_समयout = MS_TO_US(RR3_RX_MIN_TIMEOUT);
	rc->max_समयout = MS_TO_US(RR3_RX_MAX_TIMEOUT);
	rc->समयout = redrat3_get_समयout(rr3);
	rc->s_समयout = redrat3_set_समयout;
	rc->tx_ir = redrat3_transmit_ir;
	rc->s_tx_carrier = redrat3_set_tx_carrier;
	rc->s_carrier_report = redrat3_wideband_receiver;
	rc->driver_name = DRIVER_NAME;
	rc->rx_resolution = 2;
	rc->map_name = RC_MAP_HAUPPAUGE;

	ret = rc_रेजिस्टर_device(rc);
	अगर (ret < 0) अणु
		dev_err(dev, "remote dev registration failed\n");
		जाओ out;
	पूर्ण

	वापस rc;

out:
	rc_मुक्त_device(rc);
	वापस शून्य;
पूर्ण

अटल पूर्णांक redrat3_dev_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा usb_host_पूर्णांकerface *uhi;
	काष्ठा redrat3_dev *rr3;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_narrow = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_wide = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_out = शून्य;
	u8 addr, attrs;
	पूर्णांक pipe, i;
	पूर्णांक retval = -ENOMEM;

	uhi = पूर्णांकf->cur_altsetting;

	/* find our bulk-in and bulk-out endpoपूर्णांकs */
	क्रम (i = 0; i < uhi->desc.bNumEndpoपूर्णांकs; ++i) अणु
		ep = &uhi->endpoपूर्णांक[i].desc;
		addr = ep->bEndpoपूर्णांकAddress;
		attrs = ep->bmAttributes;

		अगर (((addr & USB_ENDPOINT_सूची_MASK) == USB_सूची_IN) &&
		    ((attrs & USB_ENDPOINT_XFERTYPE_MASK) ==
		     USB_ENDPOINT_XFER_BULK)) अणु
			dev_dbg(dev, "found bulk-in endpoint at 0x%02x\n",
				ep->bEndpoपूर्णांकAddress);
			/* data comes in on 0x82, 0x81 is क्रम learning */
			अगर (ep->bEndpoपूर्णांकAddress == RR3_NARROW_IN_EP_ADDR)
				ep_narrow = ep;
			अगर (ep->bEndpoपूर्णांकAddress == RR3_WIDE_IN_EP_ADDR)
				ep_wide = ep;
		पूर्ण

		अगर ((ep_out == शून्य) &&
		    ((addr & USB_ENDPOINT_सूची_MASK) == USB_सूची_OUT) &&
		    ((attrs & USB_ENDPOINT_XFERTYPE_MASK) ==
		     USB_ENDPOINT_XFER_BULK)) अणु
			dev_dbg(dev, "found bulk-out endpoint at 0x%02x\n",
				ep->bEndpoपूर्णांकAddress);
			ep_out = ep;
		पूर्ण
	पूर्ण

	अगर (!ep_narrow || !ep_out || !ep_wide) अणु
		dev_err(dev, "Couldn't find all endpoints\n");
		retval = -ENODEV;
		जाओ no_endpoपूर्णांकs;
	पूर्ण

	/* allocate memory क्रम our device state and initialize it */
	rr3 = kzalloc(माप(*rr3), GFP_KERNEL);
	अगर (!rr3)
		जाओ no_endpoपूर्णांकs;

	rr3->dev = &पूर्णांकf->dev;
	rr3->ep_narrow = ep_narrow;
	rr3->ep_out = ep_out;
	rr3->udev = udev;

	/* set up bulk-in endpoपूर्णांक */
	rr3->narrow_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!rr3->narrow_urb)
		जाओ redrat_मुक्त;

	rr3->wide_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!rr3->wide_urb)
		जाओ redrat_मुक्त;

	rr3->bulk_in_buf = usb_alloc_coherent(udev,
		le16_to_cpu(ep_narrow->wMaxPacketSize),
		GFP_KERNEL, &rr3->dma_in);
	अगर (!rr3->bulk_in_buf)
		जाओ redrat_मुक्त;

	pipe = usb_rcvbulkpipe(udev, ep_narrow->bEndpoपूर्णांकAddress);
	usb_fill_bulk_urb(rr3->narrow_urb, udev, pipe, rr3->bulk_in_buf,
		le16_to_cpu(ep_narrow->wMaxPacketSize),
		redrat3_handle_async, rr3);
	rr3->narrow_urb->transfer_dma = rr3->dma_in;
	rr3->narrow_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	pipe = usb_rcvbulkpipe(udev, ep_wide->bEndpoपूर्णांकAddress);
	usb_fill_bulk_urb(rr3->wide_urb, udev, pipe, rr3->bulk_in_buf,
		le16_to_cpu(ep_narrow->wMaxPacketSize),
		redrat3_handle_async, rr3);
	rr3->wide_urb->transfer_dma = rr3->dma_in;
	rr3->wide_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	redrat3_reset(rr3);
	redrat3_get_firmware_rev(rr3);

	/* शेष.. will get overridden by any sends with a freq defined */
	rr3->carrier = 38000;

	atomic_set(&rr3->flash, 0);
	rr3->flash_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!rr3->flash_urb)
		जाओ redrat_मुक्त;

	/* learn urb */
	rr3->learn_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!rr3->learn_urb)
		जाओ redrat_मुक्त;

	/* setup packet is 'c0 b2 0000 0000 0001' */
	rr3->learn_control.bRequestType = 0xc0;
	rr3->learn_control.bRequest = RR3_MODSIG_CAPTURE;
	rr3->learn_control.wLength = cpu_to_le16(1);

	usb_fill_control_urb(rr3->learn_urb, udev, usb_rcvctrlpipe(udev, 0),
			(अचिन्हित अक्षर *)&rr3->learn_control,
			&rr3->learn_buf, माप(rr3->learn_buf),
			redrat3_learn_complete, rr3);

	/* setup packet is 'c0 b9 0000 0000 0001' */
	rr3->flash_control.bRequestType = 0xc0;
	rr3->flash_control.bRequest = RR3_BLINK_LED;
	rr3->flash_control.wLength = cpu_to_le16(1);

	usb_fill_control_urb(rr3->flash_urb, udev, usb_rcvctrlpipe(udev, 0),
			(अचिन्हित अक्षर *)&rr3->flash_control,
			&rr3->flash_in_buf, माप(rr3->flash_in_buf),
			redrat3_led_complete, rr3);

	/* led control */
	rr3->led.name = "redrat3:red:feedback";
	rr3->led.शेष_trigger = "rc-feedback";
	rr3->led.brightness_set = redrat3_brightness_set;
	retval = led_classdev_रेजिस्टर(&पूर्णांकf->dev, &rr3->led);
	अगर (retval)
		जाओ redrat_मुक्त;

	rr3->rc = redrat3_init_rc_dev(rr3);
	अगर (!rr3->rc) अणु
		retval = -ENOMEM;
		जाओ led_मुक्त;
	पूर्ण

	/* might be all we need to करो? */
	retval = redrat3_enable_detector(rr3);
	अगर (retval < 0)
		जाओ led_मुक्त;

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकf, rr3);

	वापस 0;

led_मुक्त:
	led_classdev_unरेजिस्टर(&rr3->led);
redrat_मुक्त:
	redrat3_delete(rr3, rr3->udev);

no_endpoपूर्णांकs:
	वापस retval;
पूर्ण

अटल व्योम redrat3_dev_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा redrat3_dev *rr3 = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	rc_unरेजिस्टर_device(rr3->rc);
	led_classdev_unरेजिस्टर(&rr3->led);
	redrat3_delete(rr3, udev);
पूर्ण

अटल पूर्णांक redrat3_dev_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा redrat3_dev *rr3 = usb_get_पूर्णांकfdata(पूर्णांकf);

	led_classdev_suspend(&rr3->led);
	usb_समाप्त_urb(rr3->narrow_urb);
	usb_समाप्त_urb(rr3->wide_urb);
	usb_समाप्त_urb(rr3->flash_urb);
	वापस 0;
पूर्ण

अटल पूर्णांक redrat3_dev_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा redrat3_dev *rr3 = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (usb_submit_urb(rr3->narrow_urb, GFP_ATOMIC))
		वापस -EIO;
	अगर (usb_submit_urb(rr3->wide_urb, GFP_ATOMIC))
		वापस -EIO;
	led_classdev_resume(&rr3->led);
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver redrat3_dev_driver = अणु
	.name		= DRIVER_NAME,
	.probe		= redrat3_dev_probe,
	.disconnect	= redrat3_dev_disconnect,
	.suspend	= redrat3_dev_suspend,
	.resume		= redrat3_dev_resume,
	.reset_resume	= redrat3_dev_resume,
	.id_table	= redrat3_dev_table
पूर्ण;

module_usb_driver(redrat3_dev_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_AUTHOR(DRIVER_AUTHOR2);
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, redrat3_dev_table);
