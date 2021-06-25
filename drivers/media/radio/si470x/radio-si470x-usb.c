<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  drivers/media/radio/si470x/radio-si470x-usb.c
 *
 *  USB driver क्रम radios with Silicon Lअसल Si470x FM Radio Receivers
 *
 *  Copyright (c) 2009 Tobias Lorenz <tobias.lorenz@gmx.net>
 */


/*
 * ToDo:
 * - add firmware करोwnload/update support
 */


/* driver definitions */
#घोषणा DRIVER_AUTHOR "Tobias Lorenz <tobias.lorenz@gmx.net>"
#घोषणा DRIVER_CARD "Silicon Labs Si470x FM Radio Receiver"
#घोषणा DRIVER_DESC "USB radio driver for Si470x FM Radio Receivers"
#घोषणा DRIVER_VERSION "1.0.10"

/* kernel includes */
#समावेश <linux/usb.h>
#समावेश <linux/hid.h>
#समावेश <linux/slab.h>

#समावेश "radio-si470x.h"


/* USB Device ID List */
अटल स्थिर काष्ठा usb_device_id si470x_usb_driver_id_table[] = अणु
	/* Silicon Lअसल USB FM Radio Reference Design */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x10c4, 0x818a, USB_CLASS_HID, 0, 0) पूर्ण,
	/* ADS/Tech FM Radio Receiver (क्रमmerly Instant FM Music) */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x06e1, 0xa155, USB_CLASS_HID, 0, 0) पूर्ण,
	/* KWorld USB FM Radio SnapMusic Mobile 700 (FM700) */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1b80, 0xd700, USB_CLASS_HID, 0, 0) पूर्ण,
	/* Sanei Electric, Inc. FM USB Radio (sold as DealExtreme.com PCear) */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x10c5, 0x819a, USB_CLASS_HID, 0, 0) पूर्ण,
	/* Axentia ALERT FM USB Receiver */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x12cf, 0x7111, USB_CLASS_HID, 0, 0) पूर्ण,
	/* Terminating entry */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, si470x_usb_driver_id_table);



/**************************************************************************
 * Module Parameters
 **************************************************************************/

/* Radio Nr */
अटल पूर्णांक radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0444);
MODULE_PARM_DESC(radio_nr, "Radio Nr");

/* USB समयout */
अटल अचिन्हित पूर्णांक usb_समयout = 500;
module_param(usb_समयout, uपूर्णांक, 0644);
MODULE_PARM_DESC(usb_समयout, "USB timeout (ms): *500*");

/* RDS buffer blocks */
अटल अचिन्हित पूर्णांक rds_buf = 100;
module_param(rds_buf, uपूर्णांक, 0444);
MODULE_PARM_DESC(rds_buf, "RDS buffer entries: *100*");

/* RDS maximum block errors */
अटल अचिन्हित लघु max_rds_errors = 1;
/* 0 means   0  errors requiring correction */
/* 1 means 1-2  errors requiring correction (used by original USBRadio.exe) */
/* 2 means 3-5  errors requiring correction */
/* 3 means   6+ errors or errors in checkword, correction not possible */
module_param(max_rds_errors, uलघु, 0644);
MODULE_PARM_DESC(max_rds_errors, "RDS maximum block errors: *1*");



/**************************************************************************
 * USB HID Reports
 **************************************************************************/

/* Reports 1-16 give direct पढ़ो/ग_लिखो access to the 16 Si470x रेजिस्टरs */
/* with the (REPORT_ID - 1) corresponding to the रेजिस्टर address across USB */
/* endpoपूर्णांक 0 using GET_REPORT and SET_REPORT */
#घोषणा REGISTER_REPORT_SIZE	(RADIO_REGISTER_SIZE + 1)
#घोषणा REGISTER_REPORT(reg)	((reg) + 1)

/* Report 17 gives direct पढ़ो/ग_लिखो access to the entire Si470x रेजिस्टर */
/* map across endpoपूर्णांक 0 using GET_REPORT and SET_REPORT */
#घोषणा ENTIRE_REPORT_SIZE	(RADIO_REGISTER_NUM * RADIO_REGISTER_SIZE + 1)
#घोषणा ENTIRE_REPORT		17

/* Report 18 is used to send the lowest 6 Si470x रेजिस्टरs up the HID */
/* पूर्णांकerrupt endpoपूर्णांक 1 to Winकरोws every 20 milliseconds क्रम status */
#घोषणा RDS_REPORT_SIZE		(RDS_REGISTER_NUM * RADIO_REGISTER_SIZE + 1)
#घोषणा RDS_REPORT		18

/* Report 19: LED state */
#घोषणा LED_REPORT_SIZE		3
#घोषणा LED_REPORT		19

/* Report 19: stream */
#घोषणा STREAM_REPORT_SIZE	3
#घोषणा STREAM_REPORT		19

/* Report 20: scratch */
#घोषणा SCRATCH_PAGE_SIZE	63
#घोषणा SCRATCH_REPORT_SIZE	(SCRATCH_PAGE_SIZE + 1)
#घोषणा SCRATCH_REPORT		20

/* Reports 19-22: flash upgrade of the C8051F321 */
#घोषणा WRITE_REPORT_SIZE	4
#घोषणा WRITE_REPORT		19
#घोषणा FLASH_REPORT_SIZE	64
#घोषणा FLASH_REPORT		20
#घोषणा CRC_REPORT_SIZE		3
#घोषणा CRC_REPORT		21
#घोषणा RESPONSE_REPORT_SIZE	2
#घोषणा RESPONSE_REPORT		22

/* Report 23: currently unused, but can accept 60 byte reports on the HID */
/* पूर्णांकerrupt out endpoपूर्णांक 2 every 1 millisecond */
#घोषणा UNUSED_REPORT		23

#घोषणा MAX_REPORT_SIZE		64



/**************************************************************************
 * Software/Hardware Versions from Scratch Page
 **************************************************************************/
#घोषणा RADIO_HW_VERSION			1



/**************************************************************************
 * LED State Definitions
 **************************************************************************/
#घोषणा LED_COMMAND		0x35

#घोषणा NO_CHANGE_LED		0x00
#घोषणा ALL_COLOR_LED		0x01	/* streaming state */
#घोषणा BLINK_GREEN_LED		0x02	/* connect state */
#घोषणा BLINK_RED_LED		0x04
#घोषणा BLINK_ORANGE_LED	0x10	/* disconnect state */
#घोषणा SOLID_GREEN_LED		0x20	/* tuning/seeking state */
#घोषणा SOLID_RED_LED		0x40	/* bootload state */
#घोषणा SOLID_ORANGE_LED	0x80



/**************************************************************************
 * Stream State Definitions
 **************************************************************************/
#घोषणा STREAM_COMMAND	0x36
#घोषणा STREAM_VIDPID	0x00
#घोषणा STREAM_AUDIO	0xff



/**************************************************************************
 * Bootloader / Flash Commands
 **************************************************************************/

/* unique id sent to bootloader and required to put पूर्णांकo a bootload state */
#घोषणा UNIQUE_BL_ID		0x34

/* mask क्रम the flash data */
#घोषणा FLASH_DATA_MASK		0x55

/* bootloader commands */
#घोषणा GET_SW_VERSION_COMMAND	0x00
#घोषणा SET_PAGE_COMMAND	0x01
#घोषणा ERASE_PAGE_COMMAND	0x02
#घोषणा WRITE_PAGE_COMMAND	0x03
#घोषणा CRC_ON_PAGE_COMMAND	0x04
#घोषणा READ_FLASH_BYTE_COMMAND	0x05
#घोषणा RESET_DEVICE_COMMAND	0x06
#घोषणा GET_HW_VERSION_COMMAND	0x07
#घोषणा BLANK			0xff

/* bootloader command responses */
#घोषणा COMMAND_OK		0x01
#घोषणा COMMAND_FAILED		0x02
#घोषणा COMMAND_PENDING		0x03



/**************************************************************************
 * General Driver Functions - REGISTER_REPORTs
 **************************************************************************/

/*
 * si470x_get_report - receive a HID report
 */
अटल पूर्णांक si470x_get_report(काष्ठा si470x_device *radio, व्योम *buf, पूर्णांक size)
अणु
	अचिन्हित अक्षर *report = buf;
	पूर्णांक retval;

	retval = usb_control_msg(radio->usbdev,
		usb_rcvctrlpipe(radio->usbdev, 0),
		HID_REQ_GET_REPORT,
		USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
		report[0], 2,
		buf, size, usb_समयout);

	अगर (retval < 0)
		dev_warn(&radio->पूर्णांकf->dev,
			"si470x_get_report: usb_control_msg returned %d\n",
			retval);
	वापस retval;
पूर्ण


/*
 * si470x_set_report - send a HID report
 */
अटल पूर्णांक si470x_set_report(काष्ठा si470x_device *radio, व्योम *buf, पूर्णांक size)
अणु
	अचिन्हित अक्षर *report = buf;
	पूर्णांक retval;

	retval = usb_control_msg(radio->usbdev,
		usb_sndctrlpipe(radio->usbdev, 0),
		HID_REQ_SET_REPORT,
		USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
		report[0], 2,
		buf, size, usb_समयout);

	अगर (retval < 0)
		dev_warn(&radio->पूर्णांकf->dev,
			"si470x_set_report: usb_control_msg returned %d\n",
			retval);
	वापस retval;
पूर्ण


/*
 * si470x_get_रेजिस्टर - पढ़ो रेजिस्टर
 */
अटल पूर्णांक si470x_get_रेजिस्टर(काष्ठा si470x_device *radio, पूर्णांक regnr)
अणु
	पूर्णांक retval;

	radio->usb_buf[0] = REGISTER_REPORT(regnr);

	retval = si470x_get_report(radio, radio->usb_buf, REGISTER_REPORT_SIZE);

	अगर (retval >= 0)
		radio->रेजिस्टरs[regnr] = get_unaligned_be16(&radio->usb_buf[1]);

	वापस (retval < 0) ? -EINVAL : 0;
पूर्ण


/*
 * si470x_set_रेजिस्टर - ग_लिखो रेजिस्टर
 */
अटल पूर्णांक si470x_set_रेजिस्टर(काष्ठा si470x_device *radio, पूर्णांक regnr)
अणु
	पूर्णांक retval;

	radio->usb_buf[0] = REGISTER_REPORT(regnr);
	put_unaligned_be16(radio->रेजिस्टरs[regnr], &radio->usb_buf[1]);

	retval = si470x_set_report(radio, radio->usb_buf, REGISTER_REPORT_SIZE);

	वापस (retval < 0) ? -EINVAL : 0;
पूर्ण



/**************************************************************************
 * General Driver Functions - ENTIRE_REPORT
 **************************************************************************/

/*
 * si470x_get_all_रेजिस्टरs - पढ़ो entire रेजिस्टरs
 */
अटल पूर्णांक si470x_get_all_रेजिस्टरs(काष्ठा si470x_device *radio)
अणु
	पूर्णांक retval;
	अचिन्हित अक्षर regnr;

	radio->usb_buf[0] = ENTIRE_REPORT;

	retval = si470x_get_report(radio, radio->usb_buf, ENTIRE_REPORT_SIZE);

	अगर (retval >= 0)
		क्रम (regnr = 0; regnr < RADIO_REGISTER_NUM; regnr++)
			radio->रेजिस्टरs[regnr] = get_unaligned_be16(
				&radio->usb_buf[regnr * RADIO_REGISTER_SIZE + 1]);

	वापस (retval < 0) ? -EINVAL : 0;
पूर्ण



/**************************************************************************
 * General Driver Functions - LED_REPORT
 **************************************************************************/

/*
 * si470x_set_led_state - sets the led state
 */
अटल पूर्णांक si470x_set_led_state(काष्ठा si470x_device *radio,
		अचिन्हित अक्षर led_state)
अणु
	पूर्णांक retval;

	radio->usb_buf[0] = LED_REPORT;
	radio->usb_buf[1] = LED_COMMAND;
	radio->usb_buf[2] = led_state;

	retval = si470x_set_report(radio, radio->usb_buf, LED_REPORT_SIZE);

	वापस (retval < 0) ? -EINVAL : 0;
पूर्ण



/**************************************************************************
 * General Driver Functions - SCRATCH_REPORT
 **************************************************************************/

/*
 * si470x_get_scratch_versions - माला_लो the scratch page and version infos
 */
अटल पूर्णांक si470x_get_scratch_page_versions(काष्ठा si470x_device *radio)
अणु
	पूर्णांक retval;

	radio->usb_buf[0] = SCRATCH_REPORT;

	retval = si470x_get_report(radio, radio->usb_buf, SCRATCH_REPORT_SIZE);

	अगर (retval < 0)
		dev_warn(&radio->पूर्णांकf->dev, "si470x_get_scratch: si470x_get_report returned %d\n",
			 retval);
	अन्यथा अणु
		radio->software_version = radio->usb_buf[1];
		radio->hardware_version = radio->usb_buf[2];
	पूर्ण

	वापस (retval < 0) ? -EINVAL : 0;
पूर्ण



/**************************************************************************
 * RDS Driver Functions
 **************************************************************************/

/*
 * si470x_पूर्णांक_in_callback - rds callback and processing function
 *
 * TODO: करो we need to use mutex locks in some sections?
 */
अटल व्योम si470x_पूर्णांक_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा si470x_device *radio = urb->context;
	पूर्णांक retval;
	अचिन्हित अक्षर regnr;
	अचिन्हित अक्षर blocknum;
	अचिन्हित लघु bler; /* rds block errors */
	अचिन्हित लघु rds;
	अचिन्हित अक्षर पंचांगpbuf[3];

	अगर (urb->status) अणु
		अगर (urb->status == -ENOENT ||
				urb->status == -ECONNRESET ||
				urb->status == -ESHUTDOWN) अणु
			वापस;
		पूर्ण अन्यथा अणु
			dev_warn(&radio->पूर्णांकf->dev,
			 "non-zero urb status (%d)\n", urb->status);
			जाओ resubmit; /* Maybe we can recover. */
		पूर्ण
	पूर्ण

	/* Someबार the device वापसs len 0 packets */
	अगर (urb->actual_length != RDS_REPORT_SIZE)
		जाओ resubmit;

	radio->रेजिस्टरs[STATUSRSSI] =
		get_unaligned_be16(&radio->पूर्णांक_in_buffer[1]);

	अगर (radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_STC)
		complete(&radio->completion);

	अगर ((radio->रेजिस्टरs[SYSCONFIG1] & SYSCONFIG1_RDS)) अणु
		/* Update RDS रेजिस्टरs with URB data */
		क्रम (regnr = 1; regnr < RDS_REGISTER_NUM; regnr++)
			radio->रेजिस्टरs[STATUSRSSI + regnr] =
			    get_unaligned_be16(&radio->पूर्णांक_in_buffer[
				regnr * RADIO_REGISTER_SIZE + 1]);
		/* get rds blocks */
		अगर ((radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_RDSR) == 0) अणु
			/* No RDS group पढ़ोy, better luck next समय */
			जाओ resubmit;
		पूर्ण
		अगर ((radio->रेजिस्टरs[STATUSRSSI] & STATUSRSSI_RDSS) == 0) अणु
			/* RDS decoder not synchronized */
			जाओ resubmit;
		पूर्ण
		क्रम (blocknum = 0; blocknum < 4; blocknum++) अणु
			चयन (blocknum) अणु
			शेष:
				bler = (radio->रेजिस्टरs[STATUSRSSI] &
						STATUSRSSI_BLERA) >> 9;
				rds = radio->रेजिस्टरs[RDSA];
				अवरोध;
			हाल 1:
				bler = (radio->रेजिस्टरs[READCHAN] &
						READCHAN_BLERB) >> 14;
				rds = radio->रेजिस्टरs[RDSB];
				अवरोध;
			हाल 2:
				bler = (radio->रेजिस्टरs[READCHAN] &
						READCHAN_BLERC) >> 12;
				rds = radio->रेजिस्टरs[RDSC];
				अवरोध;
			हाल 3:
				bler = (radio->रेजिस्टरs[READCHAN] &
						READCHAN_BLERD) >> 10;
				rds = radio->रेजिस्टरs[RDSD];
				अवरोध;
			पूर्ण

			/* Fill the V4L2 RDS buffer */
			put_unaligned_le16(rds, &पंचांगpbuf);
			पंचांगpbuf[2] = blocknum;		/* offset name */
			पंचांगpbuf[2] |= blocknum << 3;	/* received offset */
			अगर (bler > max_rds_errors)
				पंचांगpbuf[2] |= 0x80; /* uncorrectable errors */
			अन्यथा अगर (bler > 0)
				पंचांगpbuf[2] |= 0x40; /* corrected error(s) */

			/* copy RDS block to पूर्णांकernal buffer */
			स_नकल(&radio->buffer[radio->wr_index], &पंचांगpbuf, 3);
			radio->wr_index += 3;

			/* wrap ग_लिखो poपूर्णांकer */
			अगर (radio->wr_index >= radio->buf_size)
				radio->wr_index = 0;

			/* check क्रम overflow */
			अगर (radio->wr_index == radio->rd_index) अणु
				/* increment and wrap पढ़ो poपूर्णांकer */
				radio->rd_index += 3;
				अगर (radio->rd_index >= radio->buf_size)
					radio->rd_index = 0;
			पूर्ण
		पूर्ण
		अगर (radio->wr_index != radio->rd_index)
			wake_up_पूर्णांकerruptible(&radio->पढ़ो_queue);
	पूर्ण

resubmit:
	/* Resubmit अगर we're still running. */
	अगर (radio->पूर्णांक_in_running && radio->usbdev) अणु
		retval = usb_submit_urb(radio->पूर्णांक_in_urb, GFP_ATOMIC);
		अगर (retval) अणु
			dev_warn(&radio->पूर्णांकf->dev,
			       "resubmitting urb failed (%d)", retval);
			radio->पूर्णांक_in_running = 0;
		पूर्ण
	पूर्ण
	radio->status_rssi_स्वतः_update = radio->पूर्णांक_in_running;
पूर्ण


अटल पूर्णांक si470x_fops_खोलो(काष्ठा file *file)
अणु
	वापस v4l2_fh_खोलो(file);
पूर्ण

अटल पूर्णांक si470x_fops_release(काष्ठा file *file)
अणु
	वापस v4l2_fh_release(file);
पूर्ण

अटल व्योम si470x_usb_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा si470x_device *radio =
		container_of(v4l2_dev, काष्ठा si470x_device, v4l2_dev);

	usb_मुक्त_urb(radio->पूर्णांक_in_urb);
	v4l2_ctrl_handler_मुक्त(&radio->hdl);
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
	kमुक्त(radio->पूर्णांक_in_buffer);
	kमुक्त(radio->buffer);
	kमुक्त(radio->usb_buf);
	kमुक्त(radio);
पूर्ण


/**************************************************************************
 * Video4Linux Interface
 **************************************************************************/

/*
 * si470x_vidioc_querycap - query device capabilities
 */
अटल पूर्णांक si470x_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_capability *capability)
अणु
	काष्ठा si470x_device *radio = video_drvdata(file);

	strscpy(capability->driver, DRIVER_NAME, माप(capability->driver));
	strscpy(capability->card, DRIVER_CARD, माप(capability->card));
	usb_make_path(radio->usbdev, capability->bus_info,
			माप(capability->bus_info));
	वापस 0;
पूर्ण


अटल पूर्णांक si470x_start_usb(काष्ठा si470x_device *radio)
अणु
	पूर्णांक retval;

	/* initialize पूर्णांकerrupt urb */
	usb_fill_पूर्णांक_urb(radio->पूर्णांक_in_urb, radio->usbdev,
			usb_rcvपूर्णांकpipe(radio->usbdev,
				radio->पूर्णांक_in_endpoपूर्णांक->bEndpoपूर्णांकAddress),
			radio->पूर्णांक_in_buffer,
			le16_to_cpu(radio->पूर्णांक_in_endpoपूर्णांक->wMaxPacketSize),
			si470x_पूर्णांक_in_callback,
			radio,
			radio->पूर्णांक_in_endpoपूर्णांक->bInterval);

	radio->पूर्णांक_in_running = 1;
	mb();

	retval = usb_submit_urb(radio->पूर्णांक_in_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_info(&radio->पूर्णांकf->dev,
				"submitting int urb failed (%d)\n", retval);
		radio->पूर्णांक_in_running = 0;
	पूर्ण
	radio->status_rssi_स्वतः_update = radio->पूर्णांक_in_running;

	/* start radio */
	retval = si470x_start(radio);
	अगर (retval < 0)
		वापस retval;

	v4l2_ctrl_handler_setup(&radio->hdl);

	वापस retval;
पूर्ण

/**************************************************************************
 * USB Interface
 **************************************************************************/

/*
 * si470x_usb_driver_probe - probe क्रम the device
 */
अटल पूर्णांक si470x_usb_driver_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा si470x_device *radio;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक i, पूर्णांक_end_size, retval;
	अचिन्हित अक्षर version_warning = 0;

	/* निजी data allocation and initialization */
	radio = kzalloc(माप(काष्ठा si470x_device), GFP_KERNEL);
	अगर (!radio) अणु
		retval = -ENOMEM;
		जाओ err_initial;
	पूर्ण
	radio->usb_buf = kदो_स्मृति(MAX_REPORT_SIZE, GFP_KERNEL);
	अगर (radio->usb_buf == शून्य) अणु
		retval = -ENOMEM;
		जाओ err_radio;
	पूर्ण
	radio->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	radio->पूर्णांकf = पूर्णांकf;
	radio->band = 1; /* Default to 76 - 108 MHz */
	mutex_init(&radio->lock);
	init_completion(&radio->completion);

	radio->get_रेजिस्टर = si470x_get_रेजिस्टर;
	radio->set_रेजिस्टर = si470x_set_रेजिस्टर;
	radio->fops_खोलो = si470x_fops_खोलो;
	radio->fops_release = si470x_fops_release;
	radio->vidioc_querycap = si470x_vidioc_querycap;

	अगरace_desc = पूर्णांकf->cur_altsetting;

	/* Set up पूर्णांकerrupt endpoपूर्णांक inक्रमmation. */
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
			radio->पूर्णांक_in_endpoपूर्णांक = endpoपूर्णांक;
	पूर्ण
	अगर (!radio->पूर्णांक_in_endpoपूर्णांक) अणु
		dev_info(&पूर्णांकf->dev, "could not find interrupt in endpoint\n");
		retval = -EIO;
		जाओ err_usbbuf;
	पूर्ण

	पूर्णांक_end_size = le16_to_cpu(radio->पूर्णांक_in_endpoपूर्णांक->wMaxPacketSize);

	radio->पूर्णांक_in_buffer = kदो_स्मृति(पूर्णांक_end_size, GFP_KERNEL);
	अगर (!radio->पूर्णांक_in_buffer) अणु
		dev_info(&पूर्णांकf->dev, "could not allocate int_in_buffer");
		retval = -ENOMEM;
		जाओ err_usbbuf;
	पूर्ण

	radio->पूर्णांक_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!radio->पूर्णांक_in_urb) अणु
		retval = -ENOMEM;
		जाओ err_पूर्णांकbuffer;
	पूर्ण

	radio->v4l2_dev.release = si470x_usb_release;

	/*
	 * The si470x SiLअसल reference design uses the same USB IDs as
	 * 'Thanko's Raremono' si4734 based receiver. So check here which we
	 * have: attempt to पढ़ो the device ID from the si470x: the lower 12
	 * bits should be 0x0242 क्रम the si470x.
	 *
	 * We use this check to determine which device we are dealing with.
	 */
	अगर (id->idVenकरोr == 0x10c4 && id->idProduct == 0x818a) अणु
		retval = usb_control_msg(radio->usbdev,
				usb_rcvctrlpipe(radio->usbdev, 0),
				HID_REQ_GET_REPORT,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
				1, 2,
				radio->usb_buf, 3, 500);
		अगर (retval != 3 ||
		    (get_unaligned_be16(&radio->usb_buf[1]) & 0xfff) != 0x0242) अणु
			dev_info(&पूर्णांकf->dev, "this is not a si470x device.\n");
			retval = -ENODEV;
			जाओ err_urb;
		पूर्ण
	पूर्ण

	retval = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &radio->v4l2_dev);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register v4l2_device\n");
		जाओ err_urb;
	पूर्ण

	v4l2_ctrl_handler_init(&radio->hdl, 2);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&radio->hdl, &si470x_ctrl_ops,
			  V4L2_CID_AUDIO_VOLUME, 0, 15, 1, 15);
	अगर (radio->hdl.error) अणु
		retval = radio->hdl.error;
		dev_err(&पूर्णांकf->dev, "couldn't register control\n");
		जाओ err_dev;
	पूर्ण
	radio->videodev = si470x_viddev_ढाँचा;
	radio->videodev.ctrl_handler = &radio->hdl;
	radio->videodev.lock = &radio->lock;
	radio->videodev.v4l2_dev = &radio->v4l2_dev;
	radio->videodev.release = video_device_release_empty;
	radio->videodev.device_caps =
		V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_READWRITE | V4L2_CAP_TUNER |
		V4L2_CAP_RADIO | V4L2_CAP_RDS_CAPTURE;
	video_set_drvdata(&radio->videodev, radio);

	/* get device and chip versions */
	अगर (si470x_get_all_रेजिस्टरs(radio) < 0) अणु
		retval = -EIO;
		जाओ err_ctrl;
	पूर्ण
	dev_info(&पूर्णांकf->dev, "DeviceID=0x%4.4hx ChipID=0x%4.4hx\n",
			radio->रेजिस्टरs[DEVICEID], radio->रेजिस्टरs[SI_CHIPID]);
	अगर ((radio->रेजिस्टरs[SI_CHIPID] & SI_CHIPID_FIRMWARE) < RADIO_FW_VERSION) अणु
		dev_warn(&पूर्णांकf->dev,
			"This driver is known to work with firmware version %hu,\n",
			RADIO_FW_VERSION);
		dev_warn(&पूर्णांकf->dev,
			"but the device has firmware version %hu.\n",
			radio->रेजिस्टरs[SI_CHIPID] & SI_CHIPID_FIRMWARE);
		version_warning = 1;
	पूर्ण

	/* get software and hardware versions */
	अगर (si470x_get_scratch_page_versions(radio) < 0) अणु
		retval = -EIO;
		जाओ err_ctrl;
	पूर्ण
	dev_info(&पूर्णांकf->dev, "software version %d, hardware version %d\n",
			radio->software_version, radio->hardware_version);
	अगर (radio->hardware_version < RADIO_HW_VERSION) अणु
		dev_warn(&पूर्णांकf->dev,
			"This driver is known to work with hardware version %hu,\n",
			RADIO_HW_VERSION);
		dev_warn(&पूर्णांकf->dev,
			"but the device has hardware version %hu.\n",
			radio->hardware_version);
		version_warning = 1;
	पूर्ण

	/* give out version warning */
	अगर (version_warning == 1) अणु
		dev_warn(&पूर्णांकf->dev,
			"If you have some trouble using this driver,\n");
		dev_warn(&पूर्णांकf->dev,
			"please report to V4L ML at linux-media@vger.kernel.org\n");
	पूर्ण

	/* set led to connect state */
	si470x_set_led_state(radio, BLINK_GREEN_LED);

	/* rds buffer allocation */
	radio->buf_size = rds_buf * 3;
	radio->buffer = kदो_स्मृति(radio->buf_size, GFP_KERNEL);
	अगर (!radio->buffer) अणु
		retval = -EIO;
		जाओ err_ctrl;
	पूर्ण

	/* rds buffer configuration */
	radio->wr_index = 0;
	radio->rd_index = 0;
	init_रुकोqueue_head(&radio->पढ़ो_queue);
	usb_set_पूर्णांकfdata(पूर्णांकf, radio);

	/* start radio */
	retval = si470x_start_usb(radio);
	अगर (retval < 0)
		जाओ err_buf;

	/* set initial frequency */
	si470x_set_freq(radio, 87.5 * FREQ_MUL); /* available in all regions */

	/* रेजिस्टर video device */
	retval = video_रेजिस्टर_device(&radio->videodev, VFL_TYPE_RADIO,
			radio_nr);
	अगर (retval) अणु
		dev_err(&पूर्णांकf->dev, "Could not register video device\n");
		जाओ err_all;
	पूर्ण

	वापस 0;
err_all:
	usb_समाप्त_urb(radio->पूर्णांक_in_urb);
err_buf:
	kमुक्त(radio->buffer);
err_ctrl:
	v4l2_ctrl_handler_मुक्त(&radio->hdl);
err_dev:
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
err_urb:
	usb_मुक्त_urb(radio->पूर्णांक_in_urb);
err_पूर्णांकbuffer:
	kमुक्त(radio->पूर्णांक_in_buffer);
err_usbbuf:
	kमुक्त(radio->usb_buf);
err_radio:
	kमुक्त(radio);
err_initial:
	वापस retval;
पूर्ण


/*
 * si470x_usb_driver_suspend - suspend the device
 */
अटल पूर्णांक si470x_usb_driver_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		pm_message_t message)
अणु
	काष्ठा si470x_device *radio = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_info(&पूर्णांकf->dev, "suspending now...\n");

	/* shutकरोwn पूर्णांकerrupt handler */
	अगर (radio->पूर्णांक_in_running) अणु
		radio->पूर्णांक_in_running = 0;
		अगर (radio->पूर्णांक_in_urb)
			usb_समाप्त_urb(radio->पूर्णांक_in_urb);
	पूर्ण

	/* cancel पढ़ो processes */
	wake_up_पूर्णांकerruptible(&radio->पढ़ो_queue);

	/* stop radio */
	si470x_stop(radio);
	वापस 0;
पूर्ण


/*
 * si470x_usb_driver_resume - resume the device
 */
अटल पूर्णांक si470x_usb_driver_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा si470x_device *radio = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;

	dev_info(&पूर्णांकf->dev, "resuming now...\n");

	/* start radio */
	ret = si470x_start_usb(radio);
	अगर (ret == 0)
		v4l2_ctrl_handler_setup(&radio->hdl);

	वापस ret;
पूर्ण


/*
 * si470x_usb_driver_disconnect - disconnect the device
 */
अटल व्योम si470x_usb_driver_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा si470x_device *radio = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&radio->lock);
	v4l2_device_disconnect(&radio->v4l2_dev);
	video_unरेजिस्टर_device(&radio->videodev);
	usb_समाप्त_urb(radio->पूर्णांक_in_urb);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	mutex_unlock(&radio->lock);
	v4l2_device_put(&radio->v4l2_dev);
पूर्ण


/*
 * si470x_usb_driver - usb driver पूर्णांकerface
 *
 * A note on suspend/resume: this driver had only empty suspend/resume
 * functions, and when I tried to test suspend/resume it always disconnected
 * instead of resuming (using my ADS InstantFM stick). So I've decided to
 * हटाओ these callbacks until someone अन्यथा with better hardware can
 * implement and test this.
 */
अटल काष्ठा usb_driver si470x_usb_driver = अणु
	.name			= DRIVER_NAME,
	.probe			= si470x_usb_driver_probe,
	.disconnect		= si470x_usb_driver_disconnect,
	.suspend		= si470x_usb_driver_suspend,
	.resume			= si470x_usb_driver_resume,
	.reset_resume		= si470x_usb_driver_resume,
	.id_table		= si470x_usb_driver_id_table,
पूर्ण;

module_usb_driver(si470x_usb_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
