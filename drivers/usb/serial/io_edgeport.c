<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Edgeport USB Serial Converter driver
 *
 * Copyright (C) 2000 Inside Out Networks, All rights reserved.
 * Copyright (C) 2001-2002 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 * Supports the following devices:
 *	Edgeport/4
 *	Edgeport/4t
 *	Edgeport/2
 *	Edgeport/4i
 *	Edgeport/2i
 *	Edgeport/421
 *	Edgeport/21
 *	Rapidport/4
 *	Edgeport/8
 *	Edgeport/2D8
 *	Edgeport/4D8
 *	Edgeport/8i
 *
 * For questions or problems with this driver, contact Inside Out
 * Networks technical support, or Peter Berger <pberger@brimson.com>,
 * or Al Borchers <alborchers@steinerpoपूर्णांक.com>.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/serial.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/रुको.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ihex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश "io_edgeport.h"
#समावेश "io_ionsp.h"		/* info क्रम the iosp messages */
#समावेश "io_16654.h"		/* 16654 UART defines */

#घोषणा DRIVER_AUTHOR "Greg Kroah-Hartman <greg@kroah.com> and David Iacovelli"
#घोषणा DRIVER_DESC "Edgeport USB Serial Driver"

#घोषणा MAX_NAME_LEN		64

#घोषणा OPEN_TIMEOUT		(5*HZ)		/* 5 seconds */

अटल स्थिर काष्ठा usb_device_id edgeport_2port_id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_2I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_421) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_21) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_2_DIN) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id edgeport_4port_id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_RAPIDPORT_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_4T) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_MT4X56USB) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_4I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_4_DIN) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_22I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_412_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_COMPATIBLE) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id edgeport_8port_id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_8) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_8I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_8R) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_8RR) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_412_8) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id Epic_port_id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0202) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0203) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0310) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0311) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0312) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A758) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A794) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A225) पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Devices that this driver supports */
अटल स्थिर काष्ठा usb_device_id id_table_combined[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_RAPIDPORT_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_4T) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_MT4X56USB) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_4I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_2I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_421) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_21) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_8) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_2_DIN) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_4_DIN) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_22I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_412_4) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_COMPATIBLE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION,	ION_DEVICE_ID_EDGEPORT_8I) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_8R) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_8RR) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ION, ION_DEVICE_ID_EDGEPORT_412_8) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0202) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0203) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0310) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0311) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_NCR, NCR_DEVICE_ID_EPIC_0312) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A758) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A794) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A225) पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table_combined);


/* receive port state */
क्रमागत RXSTATE अणु
	EXPECT_HDR1 = 0,    /* Expect header byte 1 */
	EXPECT_HDR2 = 1,    /* Expect header byte 2 */
	EXPECT_DATA = 2,    /* Expect 'RxBytesRemaining' data */
	EXPECT_HDR3 = 3,    /* Expect header byte 3 (क्रम status hdrs only) */
पूर्ण;


/* Transmit Fअगरo
 * This Transmit queue is an extension of the edgeport Rx buffer.
 * The maximum amount of data buffered in both the edgeport
 * Rx buffer (maxTxCredits) and this buffer will never exceed maxTxCredits.
 */
काष्ठा TxFअगरo अणु
	अचिन्हित पूर्णांक	head;	/* index to head poपूर्णांकer (ग_लिखो) */
	अचिन्हित पूर्णांक	tail;	/* index to tail poपूर्णांकer (पढ़ो)  */
	अचिन्हित पूर्णांक	count;	/* Bytes in queue */
	अचिन्हित पूर्णांक	size;	/* Max size of queue (equal to Max number of TxCredits) */
	अचिन्हित अक्षर	*fअगरo;	/* allocated Buffer */
पूर्ण;

/* This काष्ठाure holds all of the local port inक्रमmation */
काष्ठा edgeport_port अणु
	__u16			txCredits;		/* our current credits क्रम this port */
	__u16			maxTxCredits;		/* the max size of the port */

	काष्ठा TxFअगरo		txfअगरo;			/* transmit fअगरo -- size will be maxTxCredits */
	काष्ठा urb		*ग_लिखो_urb;		/* ग_लिखो URB क्रम this port */
	bool			ग_लिखो_in_progress;	/* 'true' जबतक a ग_लिखो URB is outstanding */
	spinlock_t		ep_lock;

	__u8			shaकरोwLCR;		/* last LCR value received */
	__u8			shaकरोwMCR;		/* last MCR value received */
	__u8			shaकरोwMSR;		/* last MSR value received */
	__u8			shaकरोwLSR;		/* last LSR value received */
	__u8			shaकरोwXonChar;		/* last value set as XON अक्षर in Edgeport */
	__u8			shaकरोwXoffChar;		/* last value set as XOFF अक्षर in Edgeport */
	__u8			validDataMask;
	__u32			baudRate;

	bool			खोलो;
	bool			खोलोPending;
	bool			commandPending;
	bool			बंदPending;
	bool			chaseResponsePending;

	रुको_queue_head_t	रुको_chase;		/* क्रम handling sleeping जबतक रुकोing क्रम chase to finish */
	रुको_queue_head_t	रुको_खोलो;		/* क्रम handling sleeping जबतक रुकोing क्रम खोलो to finish */
	रुको_queue_head_t	रुको_command;		/* क्रम handling sleeping जबतक रुकोing क्रम command to finish */

	काष्ठा usb_serial_port	*port;			/* loop back to the owner of this object */
पूर्ण;


/* This काष्ठाure holds all of the inभागidual device inक्रमmation */
काष्ठा edgeport_serial अणु
	अक्षर			name[MAX_NAME_LEN+2];		/* string name of this device */

	काष्ठा edge_manuf_descriptor	manuf_descriptor;	/* the manufacturer descriptor */
	काष्ठा edge_boot_descriptor	boot_descriptor;	/* the boot firmware descriptor */
	काष्ठा edgeport_product_info	product_info;		/* Product Info */
	काष्ठा edge_compatibility_descriptor epic_descriptor;	/* Edgeport compatible descriptor */
	पूर्णांक			is_epic;			/* flag अगर EPiC device or not */

	__u8			पूर्णांकerrupt_in_endpoपूर्णांक;		/* the पूर्णांकerrupt endpoपूर्णांक handle */
	अचिन्हित अक्षर		*पूर्णांकerrupt_in_buffer;		/* the buffer we use क्रम the पूर्णांकerrupt endpoपूर्णांक */
	काष्ठा urb		*पूर्णांकerrupt_पढ़ो_urb;		/* our पूर्णांकerrupt urb */

	__u8			bulk_in_endpoपूर्णांक;		/* the bulk in endpoपूर्णांक handle */
	अचिन्हित अक्षर		*bulk_in_buffer;		/* the buffer we use क्रम the bulk in endpoपूर्णांक */
	काष्ठा urb		*पढ़ो_urb;			/* our bulk पढ़ो urb */
	bool			पढ़ो_in_progress;
	spinlock_t		es_lock;

	__u8			bulk_out_endpoपूर्णांक;		/* the bulk out endpoपूर्णांक handle */

	__s16			rxBytesAvail;			/* the number of bytes that we need to पढ़ो from this device */

	क्रमागत RXSTATE		rxState;			/* the current state of the bulk receive processor */
	__u8			rxHeader1;			/* receive header byte 1 */
	__u8			rxHeader2;			/* receive header byte 2 */
	__u8			rxHeader3;			/* receive header byte 3 */
	__u8			rxPort;				/* the port that we are currently receiving data क्रम */
	__u8			rxStatusCode;			/* the receive status code */
	__u8			rxStatusParam;			/* the receive status paramater */
	__s16			rxBytesReमुख्यing;		/* the number of port bytes left to पढ़ो */
	काष्ठा usb_serial	*serial;			/* loop back to the owner of this object */
पूर्ण;

/* baud rate inक्रमmation */
काष्ठा भागisor_table_entry अणु
	__u32   BaudRate;
	__u16  Divisor;
पूर्ण;

/*
 * Define table of भागisors क्रम Rev A EdgePort/4 hardware
 * These assume a 3.6864MHz crystal, the standard /16, and
 * MCR.7 = 0.
 */

अटल स्थिर काष्ठा भागisor_table_entry भागisor_table[] = अणु
	अणु   50,		4608पूर्ण,
	अणु   75,		3072पूर्ण,
	अणु   110,	2095पूर्ण,	/* 2094.545455 => 230450   => .0217 % over */
	अणु   134,	1713पूर्ण,	/* 1713.011152 => 230398.5 => .00065% under */
	अणु   150,	1536पूर्ण,
	अणु   300,	768पूर्ण,
	अणु   600,	384पूर्ण,
	अणु   1200,	192पूर्ण,
	अणु   1800,	128पूर्ण,
	अणु   2400,	96पूर्ण,
	अणु   4800,	48पूर्ण,
	अणु   7200,	32पूर्ण,
	अणु   9600,	24पूर्ण,
	अणु   14400,	16पूर्ण,
	अणु   19200,	12पूर्ण,
	अणु   38400,	6पूर्ण,
	अणु   57600,	4पूर्ण,
	अणु   115200,	2पूर्ण,
	अणु   230400,	1पूर्ण,
पूर्ण;

/* Number of outstanding Command Write Urbs */
अटल atomic_t CmdUrbs = ATOMIC_INIT(0);


/* function prototypes */

अटल व्योम edge_बंद(काष्ठा usb_serial_port *port);

अटल व्योम  process_rcvd_data(काष्ठा edgeport_serial *edge_serial,
				अचिन्हित अक्षर *buffer, __u16 bufferLength);
अटल व्योम process_rcvd_status(काष्ठा edgeport_serial *edge_serial,
				__u8 byte2, __u8 byte3);
अटल व्योम edge_tty_recv(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *data,
		पूर्णांक length);
अटल व्योम handle_new_msr(काष्ठा edgeport_port *edge_port, __u8 newMsr);
अटल व्योम handle_new_lsr(काष्ठा edgeport_port *edge_port, __u8 lsrData,
				__u8 lsr, __u8 data);
अटल पूर्णांक  send_iosp_ext_cmd(काष्ठा edgeport_port *edge_port, __u8 command,
				__u8 param);
अटल पूर्णांक  calc_baud_rate_भागisor(काष्ठा device *dev, पूर्णांक baud_rate, पूर्णांक *भागisor);
अटल व्योम change_port_settings(काष्ठा tty_काष्ठा *tty,
				काष्ठा edgeport_port *edge_port,
				काष्ठा ktermios *old_termios);
अटल पूर्णांक  send_cmd_ग_लिखो_uart_रेजिस्टर(काष्ठा edgeport_port *edge_port,
				__u8 regNum, __u8 regValue);
अटल पूर्णांक  ग_लिखो_cmd_usb(काष्ठा edgeport_port *edge_port,
				अचिन्हित अक्षर *buffer, पूर्णांक ग_लिखोLength);
अटल व्योम send_more_port_data(काष्ठा edgeport_serial *edge_serial,
				काष्ठा edgeport_port *edge_port);

अटल पूर्णांक rom_ग_लिखो(काष्ठा usb_serial *serial, __u16 extAddr, __u16 addr,
					__u16 length, स्थिर __u8 *data);

/* ************************************************************************ */
/* ************************************************************************ */
/* ************************************************************************ */
/* ************************************************************************ */

/************************************************************************
 *									*
 * update_edgeport_E2PROM()	Compare current versions of		*
 *				Boot ROM and Manufacture 		*
 *				Descriptors with versions		*
 *				embedded in this driver			*
 *									*
 ************************************************************************/
अटल व्योम update_edgeport_E2PROM(काष्ठा edgeport_serial *edge_serial)
अणु
	काष्ठा device *dev = &edge_serial->serial->dev->dev;
	__u32 BootCurVer;
	__u32 BootNewVer;
	__u8 BootMajorVersion;
	__u8 BootMinorVersion;
	__u16 BootBuildNumber;
	__u32 Bootaddr;
	स्थिर काष्ठा ihex_binrec *rec;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	पूर्णांक response;

	चयन (edge_serial->product_info.iDownloadFile) अणु
	हाल EDGE_DOWNLOAD_खाता_I930:
		fw_name	= "edgeport/boot.fw";
		अवरोध;
	हाल EDGE_DOWNLOAD_खाता_80251:
		fw_name	= "edgeport/boot2.fw";
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	response = request_ihex_firmware(&fw, fw_name,
					 &edge_serial->serial->dev->dev);
	अगर (response) अणु
		dev_err(dev, "Failed to load image \"%s\" err %d\n",
		       fw_name, response);
		वापस;
	पूर्ण

	rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
	BootMajorVersion = rec->data[0];
	BootMinorVersion = rec->data[1];
	BootBuildNumber = (rec->data[2] << 8) | rec->data[3];

	/* Check Boot Image Version */
	BootCurVer = (edge_serial->boot_descriptor.MajorVersion << 24) +
		     (edge_serial->boot_descriptor.MinorVersion << 16) +
		      le16_to_cpu(edge_serial->boot_descriptor.BuildNumber);

	BootNewVer = (BootMajorVersion << 24) +
		     (BootMinorVersion << 16) +
		      BootBuildNumber;

	dev_dbg(dev, "Current Boot Image version %d.%d.%d\n",
	    edge_serial->boot_descriptor.MajorVersion,
	    edge_serial->boot_descriptor.MinorVersion,
	    le16_to_cpu(edge_serial->boot_descriptor.BuildNumber));


	अगर (BootNewVer > BootCurVer) अणु
		dev_dbg(dev, "**Update Boot Image from %d.%d.%d to %d.%d.%d\n",
		    edge_serial->boot_descriptor.MajorVersion,
		    edge_serial->boot_descriptor.MinorVersion,
		    le16_to_cpu(edge_serial->boot_descriptor.BuildNumber),
		    BootMajorVersion, BootMinorVersion, BootBuildNumber);

		dev_dbg(dev, "Downloading new Boot Image\n");

		क्रम (rec = ihex_next_binrec(rec); rec;
		     rec = ihex_next_binrec(rec)) अणु
			Bootaddr = be32_to_cpu(rec->addr);
			response = rom_ग_लिखो(edge_serial->serial,
					     Bootaddr >> 16,
					     Bootaddr & 0xFFFF,
					     be16_to_cpu(rec->len),
					     &rec->data[0]);
			अगर (response < 0) अणु
				dev_err(&edge_serial->serial->dev->dev,
					"rom_write failed (%x, %x, %d)\n",
					Bootaddr >> 16, Bootaddr & 0xFFFF,
					be16_to_cpu(rec->len));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Boot Image -- already up to date\n");
	पूर्ण
	release_firmware(fw);
पूर्ण

#अगर 0
/************************************************************************
 *
 *  Get string descriptor from device
 *
 ************************************************************************/
अटल पूर्णांक get_string_desc(काष्ठा usb_device *dev, पूर्णांक Id,
				काष्ठा usb_string_descriptor **pRetDesc)
अणु
	काष्ठा usb_string_descriptor StringDesc;
	काष्ठा usb_string_descriptor *pStringDesc;

	dev_dbg(&dev->dev, "%s - USB String ID = %d\n", __func__, Id);

	अगर (!usb_get_descriptor(dev, USB_DT_STRING, Id, &StringDesc,
						माप(StringDesc)))
		वापस 0;

	pStringDesc = kदो_स्मृति(StringDesc.bLength, GFP_KERNEL);
	अगर (!pStringDesc)
		वापस -1;

	अगर (!usb_get_descriptor(dev, USB_DT_STRING, Id, pStringDesc,
							StringDesc.bLength)) अणु
		kमुक्त(pStringDesc);
		वापस -1;
	पूर्ण

	*pRetDesc = pStringDesc;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम dump_product_info(काष्ठा edgeport_serial *edge_serial,
			      काष्ठा edgeport_product_info *product_info)
अणु
	काष्ठा device *dev = &edge_serial->serial->dev->dev;

	/* Dump Product Info काष्ठाure */
	dev_dbg(dev, "**Product Information:\n");
	dev_dbg(dev, "  ProductId             %x\n", product_info->ProductId);
	dev_dbg(dev, "  NumPorts              %d\n", product_info->NumPorts);
	dev_dbg(dev, "  ProdInfoVer           %d\n", product_info->ProdInfoVer);
	dev_dbg(dev, "  IsServer              %d\n", product_info->IsServer);
	dev_dbg(dev, "  IsRS232               %d\n", product_info->IsRS232);
	dev_dbg(dev, "  IsRS422               %d\n", product_info->IsRS422);
	dev_dbg(dev, "  IsRS485               %d\n", product_info->IsRS485);
	dev_dbg(dev, "  RomSize               %d\n", product_info->RomSize);
	dev_dbg(dev, "  RamSize               %d\n", product_info->RamSize);
	dev_dbg(dev, "  CpuRev                %x\n", product_info->CpuRev);
	dev_dbg(dev, "  BoardRev              %x\n", product_info->BoardRev);
	dev_dbg(dev, "  BootMajorVersion      %d.%d.%d\n",
		product_info->BootMajorVersion,
		product_info->BootMinorVersion,
		le16_to_cpu(product_info->BootBuildNumber));
	dev_dbg(dev, "  FirmwareMajorVersion  %d.%d.%d\n",
		product_info->FirmwareMajorVersion,
		product_info->FirmwareMinorVersion,
		le16_to_cpu(product_info->FirmwareBuildNumber));
	dev_dbg(dev, "  ManufactureDescDate   %d/%d/%d\n",
		product_info->ManufactureDescDate[0],
		product_info->ManufactureDescDate[1],
		product_info->ManufactureDescDate[2]+1900);
	dev_dbg(dev, "  iDownloadFile         0x%x\n",
		product_info->iDownloadFile);
	dev_dbg(dev, "  EpicVer               %d\n", product_info->EpicVer);
पूर्ण

अटल व्योम get_product_info(काष्ठा edgeport_serial *edge_serial)
अणु
	काष्ठा edgeport_product_info *product_info = &edge_serial->product_info;

	स_रखो(product_info, 0, माप(काष्ठा edgeport_product_info));

	product_info->ProductId = (__u16)(le16_to_cpu(edge_serial->serial->dev->descriptor.idProduct) & ~ION_DEVICE_ID_80251_NETCHIP);
	product_info->NumPorts = edge_serial->manuf_descriptor.NumPorts;
	product_info->ProdInfoVer = 0;

	product_info->RomSize = edge_serial->manuf_descriptor.RomSize;
	product_info->RamSize = edge_serial->manuf_descriptor.RamSize;
	product_info->CpuRev = edge_serial->manuf_descriptor.CpuRev;
	product_info->BoardRev = edge_serial->manuf_descriptor.BoardRev;

	product_info->BootMajorVersion =
				edge_serial->boot_descriptor.MajorVersion;
	product_info->BootMinorVersion =
				edge_serial->boot_descriptor.MinorVersion;
	product_info->BootBuildNumber =
				edge_serial->boot_descriptor.BuildNumber;

	स_नकल(product_info->ManufactureDescDate,
			edge_serial->manuf_descriptor.DescDate,
			माप(edge_serial->manuf_descriptor.DescDate));

	/* check अगर this is 2nd generation hardware */
	अगर (le16_to_cpu(edge_serial->serial->dev->descriptor.idProduct)
					    & ION_DEVICE_ID_80251_NETCHIP)
		product_info->iDownloadFile = EDGE_DOWNLOAD_खाता_80251;
	अन्यथा
		product_info->iDownloadFile = EDGE_DOWNLOAD_खाता_I930;

	/* Determine Product type and set appropriate flags */
	चयन (DEVICE_ID_FROM_USB_PRODUCT_ID(product_info->ProductId)) अणु
	हाल ION_DEVICE_ID_EDGEPORT_COMPATIBLE:
	हाल ION_DEVICE_ID_EDGEPORT_4T:
	हाल ION_DEVICE_ID_EDGEPORT_4:
	हाल ION_DEVICE_ID_EDGEPORT_2:
	हाल ION_DEVICE_ID_EDGEPORT_8_DUAL_CPU:
	हाल ION_DEVICE_ID_EDGEPORT_8:
	हाल ION_DEVICE_ID_EDGEPORT_421:
	हाल ION_DEVICE_ID_EDGEPORT_21:
	हाल ION_DEVICE_ID_EDGEPORT_2_DIN:
	हाल ION_DEVICE_ID_EDGEPORT_4_DIN:
	हाल ION_DEVICE_ID_EDGEPORT_16_DUAL_CPU:
		product_info->IsRS232 = 1;
		अवरोध;

	हाल ION_DEVICE_ID_EDGEPORT_2I:	/* Edgeport/2 RS422/RS485 */
		product_info->IsRS422 = 1;
		product_info->IsRS485 = 1;
		अवरोध;

	हाल ION_DEVICE_ID_EDGEPORT_8I:	/* Edgeport/4 RS422 */
	हाल ION_DEVICE_ID_EDGEPORT_4I:	/* Edgeport/4 RS422 */
		product_info->IsRS422 = 1;
		अवरोध;
	पूर्ण

	dump_product_info(edge_serial, product_info);
पूर्ण

अटल पूर्णांक get_epic_descriptor(काष्ठा edgeport_serial *ep)
अणु
	पूर्णांक result;
	काष्ठा usb_serial *serial = ep->serial;
	काष्ठा edgeport_product_info *product_info = &ep->product_info;
	काष्ठा edge_compatibility_descriptor *epic;
	काष्ठा edge_compatibility_bits *bits;
	काष्ठा device *dev = &serial->dev->dev;

	ep->is_epic = 0;

	epic = kदो_स्मृति(माप(*epic), GFP_KERNEL);
	अगर (!epic)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
				 USB_REQUEST_ION_GET_EPIC_DESC,
				 0xC0, 0x00, 0x00,
				 epic, माप(*epic),
				 300);
	अगर (result == माप(*epic)) अणु
		ep->is_epic = 1;
		स_नकल(&ep->epic_descriptor, epic, माप(*epic));
		स_रखो(product_info, 0, माप(काष्ठा edgeport_product_info));

		product_info->NumPorts = epic->NumPorts;
		product_info->ProdInfoVer = 0;
		product_info->FirmwareMajorVersion = epic->MajorVersion;
		product_info->FirmwareMinorVersion = epic->MinorVersion;
		product_info->FirmwareBuildNumber = epic->BuildNumber;
		product_info->iDownloadFile = epic->iDownloadFile;
		product_info->EpicVer = epic->EpicVer;
		product_info->Epic = epic->Supports;
		product_info->ProductId = ION_DEVICE_ID_EDGEPORT_COMPATIBLE;
		dump_product_info(ep, product_info);

		bits = &ep->epic_descriptor.Supports;
		dev_dbg(dev, "**EPIC descriptor:\n");
		dev_dbg(dev, "  VendEnableSuspend: %s\n", bits->VendEnableSuspend ? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPOpen         : %s\n", bits->IOSPOpen	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPClose        : %s\n", bits->IOSPClose	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPChase        : %s\n", bits->IOSPChase	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPSetRxFlow    : %s\n", bits->IOSPSetRxFlow	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPSetTxFlow    : %s\n", bits->IOSPSetTxFlow	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPSetXChar     : %s\n", bits->IOSPSetXChar	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPRxCheck      : %s\n", bits->IOSPRxCheck	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPSetClrBreak  : %s\n", bits->IOSPSetClrBreak	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPWriteMCR     : %s\n", bits->IOSPWriteMCR	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPWriteLCR     : %s\n", bits->IOSPWriteLCR	? "TRUE": "FALSE");
		dev_dbg(dev, "  IOSPSetBaudRate  : %s\n", bits->IOSPSetBaudRate	? "TRUE": "FALSE");
		dev_dbg(dev, "  TrueEdgeport     : %s\n", bits->TrueEdgeport	? "TRUE": "FALSE");

		result = 0;
	पूर्ण अन्यथा अगर (result >= 0) अणु
		dev_warn(&serial->पूर्णांकerface->dev, "short epic descriptor received: %d\n",
			 result);
		result = -EIO;
	पूर्ण

	kमुक्त(epic);

	वापस result;
पूर्ण


/************************************************************************/
/************************************************************************/
/*            U S B  C A L L B A C K   F U N C T I O N S                */
/*            U S B  C A L L B A C K   F U N C T I O N S                */
/************************************************************************/
/************************************************************************/

/*****************************************************************************
 * edge_पूर्णांकerrupt_callback
 *	this is the callback function क्रम when we have received data on the
 *	पूर्णांकerrupt endpoपूर्णांक.
 *****************************************************************************/
अटल व्योम edge_पूर्णांकerrupt_callback(काष्ठा urb *urb)
अणु
	काष्ठा edgeport_serial *edge_serial = urb->context;
	काष्ठा device *dev;
	काष्ठा edgeport_port *edge_port;
	काष्ठा usb_serial_port *port;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक length = urb->actual_length;
	अचिन्हित दीर्घ flags;
	पूर्णांक bytes_avail;
	पूर्णांक position;
	पूर्णांक txCredits;
	पूर्णांक portNumber;
	पूर्णांक result;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down with status: %d\n", __func__, status);
		वापस;
	शेष:
		dev_dbg(&urb->dev->dev, "%s - nonzero urb status received: %d\n", __func__, status);
		जाओ निकास;
	पूर्ण

	dev = &edge_serial->serial->dev->dev;

	/* process this पूर्णांकerrupt-पढ़ो even अगर there are no ports खोलो */
	अगर (length) अणु
		usb_serial_debug_data(dev, __func__, length, data);

		अगर (length > 1) अणु
			bytes_avail = data[0] | (data[1] << 8);
			अगर (bytes_avail) अणु
				spin_lock_irqsave(&edge_serial->es_lock, flags);
				edge_serial->rxBytesAvail += bytes_avail;
				dev_dbg(dev,
					"%s - bytes_avail=%d, rxBytesAvail=%d, read_in_progress=%d\n",
					__func__, bytes_avail,
					edge_serial->rxBytesAvail,
					edge_serial->पढ़ो_in_progress);

				अगर (edge_serial->rxBytesAvail > 0 &&
				    !edge_serial->पढ़ो_in_progress) अणु
					dev_dbg(dev, "%s - posting a read\n", __func__);
					edge_serial->पढ़ो_in_progress = true;

					/* we have pending bytes on the
					   bulk in pipe, send a request */
					result = usb_submit_urb(edge_serial->पढ़ो_urb, GFP_ATOMIC);
					अगर (result) अणु
						dev_err(dev,
							"%s - usb_submit_urb(read bulk) failed with result = %d\n",
							__func__, result);
						edge_serial->पढ़ो_in_progress = false;
					पूर्ण
				पूर्ण
				spin_unlock_irqrestore(&edge_serial->es_lock,
						       flags);
			पूर्ण
		पूर्ण
		/* grab the txcredits क्रम the ports अगर available */
		position = 2;
		portNumber = 0;
		जबतक ((position < length - 1) &&
				(portNumber < edge_serial->serial->num_ports)) अणु
			txCredits = data[position] | (data[position+1] << 8);
			अगर (txCredits) अणु
				port = edge_serial->serial->port[portNumber];
				edge_port = usb_get_serial_port_data(port);
				अगर (edge_port && edge_port->खोलो) अणु
					spin_lock_irqsave(&edge_port->ep_lock,
							  flags);
					edge_port->txCredits += txCredits;
					spin_unlock_irqrestore(&edge_port->ep_lock,
							       flags);
					dev_dbg(dev, "%s - txcredits for port%d = %d\n",
						__func__, portNumber,
						edge_port->txCredits);

					/* tell the tty driver that something
					   has changed */
					tty_port_tty_wakeup(&edge_port->port->port);
					/* Since we have more credit, check
					   अगर more data can be sent */
					send_more_port_data(edge_serial,
								edge_port);
				पूर्ण
			पूर्ण
			position += 2;
			++portNumber;
		पूर्ण
	पूर्ण

निकास:
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_err(&urb->dev->dev,
			"%s - Error %d submitting control urb\n",
						__func__, result);
पूर्ण


/*****************************************************************************
 * edge_bulk_in_callback
 *	this is the callback function क्रम when we have received data on the
 *	bulk in endpoपूर्णांक.
 *****************************************************************************/
अटल व्योम edge_bulk_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा edgeport_serial	*edge_serial = urb->context;
	काष्ठा device *dev;
	अचिन्हित अक्षर		*data = urb->transfer_buffer;
	पूर्णांक			retval;
	__u16			raw_data_length;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero read bulk status received: %d\n",
			__func__, status);
		edge_serial->पढ़ो_in_progress = false;
		वापस;
	पूर्ण

	अगर (urb->actual_length == 0) अणु
		dev_dbg(&urb->dev->dev, "%s - read bulk callback with no data\n", __func__);
		edge_serial->पढ़ो_in_progress = false;
		वापस;
	पूर्ण

	dev = &edge_serial->serial->dev->dev;
	raw_data_length = urb->actual_length;

	usb_serial_debug_data(dev, __func__, raw_data_length, data);

	spin_lock_irqsave(&edge_serial->es_lock, flags);

	/* decrement our rxBytes available by the number that we just got */
	edge_serial->rxBytesAvail -= raw_data_length;

	dev_dbg(dev, "%s - Received = %d, rxBytesAvail %d\n", __func__,
		raw_data_length, edge_serial->rxBytesAvail);

	process_rcvd_data(edge_serial, data, urb->actual_length);

	/* check to see अगर there's any more data क्रम us to पढ़ो */
	अगर (edge_serial->rxBytesAvail > 0) अणु
		dev_dbg(dev, "%s - posting a read\n", __func__);
		retval = usb_submit_urb(edge_serial->पढ़ो_urb, GFP_ATOMIC);
		अगर (retval) अणु
			dev_err(dev,
				"%s - usb_submit_urb(read bulk) failed, retval = %d\n",
				__func__, retval);
			edge_serial->पढ़ो_in_progress = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		edge_serial->पढ़ो_in_progress = false;
	पूर्ण

	spin_unlock_irqrestore(&edge_serial->es_lock, flags);
पूर्ण


/*****************************************************************************
 * edge_bulk_out_data_callback
 *	this is the callback function क्रम when we have finished sending
 *	serial data on the bulk out endpoपूर्णांक.
 *****************************************************************************/
अटल व्योम edge_bulk_out_data_callback(काष्ठा urb *urb)
अणु
	काष्ठा edgeport_port *edge_port = urb->context;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev,
			"%s - nonzero write bulk status received: %d\n",
			__func__, status);
	पूर्ण

	अगर (edge_port->खोलो)
		tty_port_tty_wakeup(&edge_port->port->port);

	/* Release the Write URB */
	edge_port->ग_लिखो_in_progress = false;

	/* Check अगर more data needs to be sent */
	send_more_port_data((काष्ठा edgeport_serial *)
		(usb_get_serial_data(edge_port->port->serial)), edge_port);
पूर्ण


/*****************************************************************************
 * BulkOutCmdCallback
 *	this is the callback function क्रम when we have finished sending a
 *	command	on the bulk out endpoपूर्णांक.
 *****************************************************************************/
अटल व्योम edge_bulk_out_cmd_callback(काष्ठा urb *urb)
अणु
	काष्ठा edgeport_port *edge_port = urb->context;
	पूर्णांक status = urb->status;

	atomic_dec(&CmdUrbs);
	dev_dbg(&urb->dev->dev, "%s - FREE URB %p (outstanding %d)\n",
		__func__, urb, atomic_पढ़ो(&CmdUrbs));


	/* clean up the transfer buffer */
	kमुक्त(urb->transfer_buffer);

	/* Free the command urb */
	usb_मुक्त_urb(urb);

	अगर (status) अणु
		dev_dbg(&urb->dev->dev,
			"%s - nonzero write bulk status received: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	/* tell the tty driver that something has changed */
	अगर (edge_port->खोलो)
		tty_port_tty_wakeup(&edge_port->port->port);

	/* we have completed the command */
	edge_port->commandPending = false;
	wake_up(&edge_port->रुको_command);
पूर्ण


/*****************************************************************************
 * Driver tty पूर्णांकerface functions
 *****************************************************************************/

/*****************************************************************************
 * SerialOpen
 *	this function is called by the tty driver when a port is खोलोed
 *	If successful, we वापस 0
 *	Otherwise we वापस a negative error number.
 *****************************************************************************/
अटल पूर्णांक edge_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	काष्ठा device *dev = &port->dev;
	काष्ठा usb_serial *serial;
	काष्ठा edgeport_serial *edge_serial;
	पूर्णांक response;

	अगर (edge_port == शून्य)
		वापस -ENODEV;

	/* see अगर we've set up our endpoint info yet (can't set it up
	   in edge_startup as the काष्ठाures were not set up at that समय.) */
	serial = port->serial;
	edge_serial = usb_get_serial_data(serial);
	अगर (edge_serial == शून्य)
		वापस -ENODEV;
	अगर (edge_serial->पूर्णांकerrupt_in_buffer == शून्य) अणु
		काष्ठा usb_serial_port *port0 = serial->port[0];

		/* not set up yet, so करो it now */
		edge_serial->पूर्णांकerrupt_in_buffer =
					port0->पूर्णांकerrupt_in_buffer;
		edge_serial->पूर्णांकerrupt_in_endpoपूर्णांक =
					port0->पूर्णांकerrupt_in_endpoपूर्णांकAddress;
		edge_serial->पूर्णांकerrupt_पढ़ो_urb = port0->पूर्णांकerrupt_in_urb;
		edge_serial->bulk_in_buffer = port0->bulk_in_buffer;
		edge_serial->bulk_in_endpoपूर्णांक =
					port0->bulk_in_endpoपूर्णांकAddress;
		edge_serial->पढ़ो_urb = port0->पढ़ो_urb;
		edge_serial->bulk_out_endpoपूर्णांक =
					port0->bulk_out_endpoपूर्णांकAddress;

		/* set up our पूर्णांकerrupt urb */
		usb_fill_पूर्णांक_urb(edge_serial->पूर्णांकerrupt_पढ़ो_urb,
		      serial->dev,
		      usb_rcvपूर्णांकpipe(serial->dev,
				port0->पूर्णांकerrupt_in_endpoपूर्णांकAddress),
		      port0->पूर्णांकerrupt_in_buffer,
		      edge_serial->पूर्णांकerrupt_पढ़ो_urb->transfer_buffer_length,
		      edge_पूर्णांकerrupt_callback, edge_serial,
		      edge_serial->पूर्णांकerrupt_पढ़ो_urb->पूर्णांकerval);

		/* set up our bulk in urb */
		usb_fill_bulk_urb(edge_serial->पढ़ो_urb, serial->dev,
			usb_rcvbulkpipe(serial->dev,
				port0->bulk_in_endpoपूर्णांकAddress),
			port0->bulk_in_buffer,
			edge_serial->पढ़ो_urb->transfer_buffer_length,
			edge_bulk_in_callback, edge_serial);
		edge_serial->पढ़ो_in_progress = false;

		/* start पूर्णांकerrupt पढ़ो क्रम this edgeport
		 * this पूर्णांकerrupt will जारी as दीर्घ
		 * as the edgeport is connected */
		response = usb_submit_urb(edge_serial->पूर्णांकerrupt_पढ़ो_urb,
								GFP_KERNEL);
		अगर (response) अणु
			dev_err(dev, "%s - Error %d submitting control urb\n",
				__func__, response);
		पूर्ण
	पूर्ण

	/* initialize our रुको queues */
	init_रुकोqueue_head(&edge_port->रुको_खोलो);
	init_रुकोqueue_head(&edge_port->रुको_chase);
	init_रुकोqueue_head(&edge_port->रुको_command);

	/* initialize our port settings */
	edge_port->txCredits = 0;	/* Can't send any data yet */
	/* Must always set this bit to enable पूर्णांकs! */
	edge_port->shaकरोwMCR = MCR_MASTER_IE;
	edge_port->chaseResponsePending = false;

	/* send a खोलो port command */
	edge_port->खोलोPending = true;
	edge_port->खोलो        = false;
	response = send_iosp_ext_cmd(edge_port, IOSP_CMD_OPEN_PORT, 0);

	अगर (response < 0) अणु
		dev_err(dev, "%s - error sending open port command\n", __func__);
		edge_port->खोलोPending = false;
		वापस -ENODEV;
	पूर्ण

	/* now रुको क्रम the port to be completely खोलोed */
	रुको_event_समयout(edge_port->रुको_खोलो, !edge_port->खोलोPending,
								OPEN_TIMEOUT);

	अगर (!edge_port->खोलो) अणु
		/* खोलो समयd out */
		dev_dbg(dev, "%s - open timedout\n", __func__);
		edge_port->खोलोPending = false;
		वापस -ENODEV;
	पूर्ण

	/* create the txfअगरo */
	edge_port->txfअगरo.head	= 0;
	edge_port->txfअगरo.tail	= 0;
	edge_port->txfअगरo.count	= 0;
	edge_port->txfअगरo.size	= edge_port->maxTxCredits;
	edge_port->txfअगरo.fअगरo	= kदो_स्मृति(edge_port->maxTxCredits, GFP_KERNEL);

	अगर (!edge_port->txfअगरo.fअगरo) अणु
		edge_बंद(port);
		वापस -ENOMEM;
	पूर्ण

	/* Allocate a URB क्रम the ग_लिखो */
	edge_port->ग_लिखो_urb = usb_alloc_urb(0, GFP_KERNEL);
	edge_port->ग_लिखो_in_progress = false;

	अगर (!edge_port->ग_लिखो_urb) अणु
		edge_बंद(port);
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(dev, "%s - Initialize TX fifo to %d bytes\n",
		__func__, edge_port->maxTxCredits);

	वापस 0;
पूर्ण


/************************************************************************
 *
 * block_until_chase_response
 *
 *	This function will block the बंद until one of the following:
 *		1. Response to our Chase comes from Edgeport
 *		2. A समयout of 10 seconds without activity has expired
 *		   (1K of Edgeport data @ 2400 baud ==> 4 sec to empty)
 *
 ************************************************************************/
अटल व्योम block_until_chase_response(काष्ठा edgeport_port *edge_port)
अणु
	काष्ठा device *dev = &edge_port->port->dev;
	DEFINE_WAIT(रुको);
	__u16 lastCredits;
	पूर्णांक समयout = 1*HZ;
	पूर्णांक loop = 10;

	जबतक (1) अणु
		/* Save Last credits */
		lastCredits = edge_port->txCredits;

		/* Did we get our Chase response */
		अगर (!edge_port->chaseResponsePending) अणु
			dev_dbg(dev, "%s - Got Chase Response\n", __func__);

			/* did we get all of our credit back? */
			अगर (edge_port->txCredits == edge_port->maxTxCredits) अणु
				dev_dbg(dev, "%s - Got all credits\n", __func__);
				वापस;
			पूर्ण
		पूर्ण

		/* Block the thपढ़ो क्रम a जबतक */
		prepare_to_रुको(&edge_port->रुको_chase, &रुको,
						TASK_UNINTERRUPTIBLE);
		schedule_समयout(समयout);
		finish_रुको(&edge_port->रुको_chase, &रुको);

		अगर (lastCredits == edge_port->txCredits) अणु
			/* No activity.. count करोwn. */
			loop--;
			अगर (loop == 0) अणु
				edge_port->chaseResponsePending = false;
				dev_dbg(dev, "%s - Chase TIMEOUT\n", __func__);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Reset समयout value back to 10 seconds */
			dev_dbg(dev, "%s - Last %d, Current %d\n", __func__,
					lastCredits, edge_port->txCredits);
			loop = 10;
		पूर्ण
	पूर्ण
पूर्ण


/************************************************************************
 *
 * block_until_tx_empty
 *
 *	This function will block the बंद until one of the following:
 *		1. TX count are 0
 *		2. The edgeport has stopped
 *		3. A समयout of 3 seconds without activity has expired
 *
 ************************************************************************/
अटल व्योम block_until_tx_empty(काष्ठा edgeport_port *edge_port)
अणु
	काष्ठा device *dev = &edge_port->port->dev;
	DEFINE_WAIT(रुको);
	काष्ठा TxFअगरo *fअगरo = &edge_port->txfअगरo;
	__u32 lastCount;
	पूर्णांक समयout = HZ/10;
	पूर्णांक loop = 30;

	जबतक (1) अणु
		/* Save Last count */
		lastCount = fअगरo->count;

		/* Is the Edgeport Buffer empty? */
		अगर (lastCount == 0) अणु
			dev_dbg(dev, "%s - TX Buffer Empty\n", __func__);
			वापस;
		पूर्ण

		/* Block the thपढ़ो क्रम a जबतक */
		prepare_to_रुको(&edge_port->रुको_chase, &रुको,
						TASK_UNINTERRUPTIBLE);
		schedule_समयout(समयout);
		finish_रुको(&edge_port->रुको_chase, &रुको);

		dev_dbg(dev, "%s wait\n", __func__);

		अगर (lastCount == fअगरo->count) अणु
			/* No activity.. count करोwn. */
			loop--;
			अगर (loop == 0) अणु
				dev_dbg(dev, "%s - TIMEOUT\n", __func__);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Reset समयout value back to seconds */
			loop = 30;
		पूर्ण
	पूर्ण
पूर्ण


/*****************************************************************************
 * edge_बंद
 *	this function is called by the tty driver when a port is बंदd
 *****************************************************************************/
अटल व्योम edge_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_serial *edge_serial;
	काष्ठा edgeport_port *edge_port;
	पूर्णांक status;

	edge_serial = usb_get_serial_data(port->serial);
	edge_port = usb_get_serial_port_data(port);
	अगर (edge_serial == शून्य || edge_port == शून्य)
		वापस;

	/* block until tx is empty */
	block_until_tx_empty(edge_port);

	edge_port->बंदPending = true;

	अगर (!edge_serial->is_epic ||
	    edge_serial->epic_descriptor.Supports.IOSPChase) अणु
		/* flush and chase */
		edge_port->chaseResponsePending = true;

		dev_dbg(&port->dev, "%s - Sending IOSP_CMD_CHASE_PORT\n", __func__);
		status = send_iosp_ext_cmd(edge_port, IOSP_CMD_CHASE_PORT, 0);
		अगर (status == 0)
			/* block until chase finished */
			block_until_chase_response(edge_port);
		अन्यथा
			edge_port->chaseResponsePending = false;
	पूर्ण

	अगर (!edge_serial->is_epic ||
	    edge_serial->epic_descriptor.Supports.IOSPClose) अणु
	       /* बंद the port */
		dev_dbg(&port->dev, "%s - Sending IOSP_CMD_CLOSE_PORT\n", __func__);
		send_iosp_ext_cmd(edge_port, IOSP_CMD_CLOSE_PORT, 0);
	पूर्ण

	/* port->बंद = true; */
	edge_port->बंदPending = false;
	edge_port->खोलो = false;
	edge_port->खोलोPending = false;

	usb_समाप्त_urb(edge_port->ग_लिखो_urb);

	अगर (edge_port->ग_लिखो_urb) अणु
		/* अगर this urb had a transfer buffer alपढ़ोy
				(old transfer) मुक्त it */
		kमुक्त(edge_port->ग_लिखो_urb->transfer_buffer);
		usb_मुक्त_urb(edge_port->ग_लिखो_urb);
		edge_port->ग_लिखो_urb = शून्य;
	पूर्ण
	kमुक्त(edge_port->txfअगरo.fअगरo);
	edge_port->txfअगरo.fअगरo = शून्य;
पूर्ण

/*****************************************************************************
 * SerialWrite
 *	this function is called by the tty driver when data should be written
 *	to the port.
 *	If successful, we वापस the number of bytes written, otherwise we
 *	वापस a negative error number.
 *****************************************************************************/
अटल पूर्णांक edge_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
					स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	काष्ठा TxFअगरo *fअगरo;
	पूर्णांक copySize;
	पूर्णांक bytesleft;
	पूर्णांक firsthalf;
	पूर्णांक secondhalf;
	अचिन्हित दीर्घ flags;

	अगर (edge_port == शून्य)
		वापस -ENODEV;

	/* get a poपूर्णांकer to the Tx fअगरo */
	fअगरo = &edge_port->txfअगरo;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	/* calculate number of bytes to put in fअगरo */
	copySize = min((अचिन्हित पूर्णांक)count,
				(edge_port->txCredits - fअगरo->count));

	dev_dbg(&port->dev, "%s of %d byte(s) Fifo room  %d -- will copy %d bytes\n",
		__func__, count, edge_port->txCredits - fअगरo->count, copySize);

	/* catch ग_लिखोs of 0 bytes which the tty driver likes to give us,
	   and when txCredits is empty */
	अगर (copySize == 0) अणु
		dev_dbg(&port->dev, "%s - copySize = Zero\n", __func__);
		जाओ finish_ग_लिखो;
	पूर्ण

	/* queue the data
	 * since we can never overflow the buffer we करो not have to check क्रम a
	 * full condition
	 *
	 * the copy is करोne is two parts -- first fill to the end of the buffer
	 * then copy the reset from the start of the buffer
	 */
	bytesleft = fअगरo->size - fअगरo->head;
	firsthalf = min(bytesleft, copySize);
	dev_dbg(&port->dev, "%s - copy %d bytes of %d into fifo \n", __func__,
		firsthalf, bytesleft);

	/* now copy our data */
	स_नकल(&fअगरo->fअगरo[fअगरo->head], data, firsthalf);
	usb_serial_debug_data(&port->dev, __func__, firsthalf, &fअगरo->fअगरo[fअगरo->head]);

	/* update the index and size */
	fअगरo->head  += firsthalf;
	fअगरo->count += firsthalf;

	/* wrap the index */
	अगर (fअगरo->head == fअगरo->size)
		fअगरo->head = 0;

	secondhalf = copySize-firsthalf;

	अगर (secondhalf) अणु
		dev_dbg(&port->dev, "%s - copy rest of data %d\n", __func__, secondhalf);
		स_नकल(&fअगरo->fअगरo[fअगरo->head], &data[firsthalf], secondhalf);
		usb_serial_debug_data(&port->dev, __func__, secondhalf, &fअगरo->fअगरo[fअगरo->head]);
		/* update the index and size */
		fअगरo->count += secondhalf;
		fअगरo->head  += secondhalf;
		/* No need to check क्रम wrap since we can not get to end of
		 * the fअगरo in this part
		 */
	पूर्ण

finish_ग_लिखो:
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	send_more_port_data((काष्ठा edgeport_serial *)
			usb_get_serial_data(port->serial), edge_port);

	dev_dbg(&port->dev, "%s wrote %d byte(s) TxCredits %d, Fifo %d\n",
		__func__, copySize, edge_port->txCredits, fअगरo->count);

	वापस copySize;
पूर्ण


/************************************************************************
 *
 * send_more_port_data()
 *
 *	This routine attempts to ग_लिखो additional UART transmit data
 *	to a port over the USB bulk pipe. It is called (1) when new
 *	data has been written to a port's TxBuffer from higher layers
 *	(2) when the peripheral sends us additional TxCredits indicating
 *	that it can accept more	Tx data क्रम a given port; and (3) when
 *	a bulk ग_लिखो completes successfully and we want to see अगर we
 *	can transmit more.
 *
 ************************************************************************/
अटल व्योम send_more_port_data(काष्ठा edgeport_serial *edge_serial,
					काष्ठा edgeport_port *edge_port)
अणु
	काष्ठा TxFअगरo	*fअगरo = &edge_port->txfअगरo;
	काष्ठा device	*dev = &edge_port->port->dev;
	काष्ठा urb	*urb;
	अचिन्हित अक्षर	*buffer;
	पूर्णांक		status;
	पूर्णांक		count;
	पूर्णांक		bytesleft;
	पूर्णांक		firsthalf;
	पूर्णांक		secondhalf;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);

	अगर (edge_port->ग_लिखो_in_progress ||
	    !edge_port->खोलो             ||
	    (fअगरo->count == 0)) अणु
		dev_dbg(dev, "%s EXIT - fifo %d, PendingWrite = %d\n",
			__func__, fअगरo->count, edge_port->ग_लिखो_in_progress);
		जाओ निकास_send;
	पूर्ण

	/* since the amount of data in the fअगरo will always fit पूर्णांकo the
	 * edgeport buffer we करो not need to check the ग_लिखो length
	 *
	 * Do we have enough credits क्रम this port to make it worthजबतक
	 * to bother queueing a ग_लिखो. If it's too small, say a few bytes,
	 * it's better to रुको क्रम more credits so we can करो a larger ग_लिखो.
	 */
	अगर (edge_port->txCredits < EDGE_FW_GET_TX_CREDITS_SEND_THRESHOLD(edge_port->maxTxCredits, EDGE_FW_BULK_MAX_PACKET_SIZE)) अणु
		dev_dbg(dev, "%s Not enough credit - fifo %d TxCredit %d\n",
			__func__, fअगरo->count, edge_port->txCredits);
		जाओ निकास_send;
	पूर्ण

	/* lock this ग_लिखो */
	edge_port->ग_लिखो_in_progress = true;

	/* get a poपूर्णांकer to the ग_लिखो_urb */
	urb = edge_port->ग_लिखो_urb;

	/* make sure transfer buffer is मुक्तd */
	kमुक्त(urb->transfer_buffer);
	urb->transfer_buffer = शून्य;

	/* build the data header क्रम the buffer and port that we are about
	   to send out */
	count = fअगरo->count;
	buffer = kदो_स्मृति(count+2, GFP_ATOMIC);
	अगर (!buffer) अणु
		edge_port->ग_लिखो_in_progress = false;
		जाओ निकास_send;
	पूर्ण
	buffer[0] = IOSP_BUILD_DATA_HDR1(edge_port->port->port_number, count);
	buffer[1] = IOSP_BUILD_DATA_HDR2(edge_port->port->port_number, count);

	/* now copy our data */
	bytesleft =  fअगरo->size - fअगरo->tail;
	firsthalf = min(bytesleft, count);
	स_नकल(&buffer[2], &fअगरo->fअगरo[fअगरo->tail], firsthalf);
	fअगरo->tail  += firsthalf;
	fअगरo->count -= firsthalf;
	अगर (fअगरo->tail == fअगरo->size)
		fअगरo->tail = 0;

	secondhalf = count-firsthalf;
	अगर (secondhalf) अणु
		स_नकल(&buffer[2+firsthalf], &fअगरo->fअगरo[fअगरo->tail],
								secondhalf);
		fअगरo->tail  += secondhalf;
		fअगरo->count -= secondhalf;
	पूर्ण

	अगर (count)
		usb_serial_debug_data(&edge_port->port->dev, __func__, count, &buffer[2]);

	/* fill up the urb with all of our data and submit it */
	usb_fill_bulk_urb(urb, edge_serial->serial->dev,
			usb_sndbulkpipe(edge_serial->serial->dev,
					edge_serial->bulk_out_endpoपूर्णांक),
			buffer, count+2,
			edge_bulk_out_data_callback, edge_port);

	/* decrement the number of credits we have by the number we just sent */
	edge_port->txCredits -= count;
	edge_port->port->icount.tx += count;

	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		/* something went wrong */
		dev_err_console(edge_port->port,
			"%s - usb_submit_urb(write bulk) failed, status = %d, data lost\n",
				__func__, status);
		edge_port->ग_लिखो_in_progress = false;

		/* revert the credits as something bad happened. */
		edge_port->txCredits += count;
		edge_port->port->icount.tx -= count;
	पूर्ण
	dev_dbg(dev, "%s wrote %d byte(s) TxCredit %d, Fifo %d\n",
		__func__, count, edge_port->txCredits, fअगरo->count);

निकास_send:
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);
पूर्ण


/*****************************************************************************
 * edge_ग_लिखो_room
 *	this function is called by the tty driver when it wants to know how
 *	many bytes of data we can accept क्रम a specअगरic port. If successful,
 *	we वापस the amount of room that we have क्रम this port	(the txCredits)
 *	otherwise we वापस a negative error number.
 *****************************************************************************/
अटल पूर्णांक edge_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक room;
	अचिन्हित दीर्घ flags;

	अगर (edge_port == शून्य)
		वापस 0;
	अगर (edge_port->बंदPending)
		वापस 0;

	अगर (!edge_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस 0;
	पूर्ण

	/* total of both buffers is still txCredit */
	spin_lock_irqsave(&edge_port->ep_lock, flags);
	room = edge_port->txCredits - edge_port->txfअगरo.count;
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, room);
	वापस room;
पूर्ण


/*****************************************************************************
 * edge_अक्षरs_in_buffer
 *	this function is called by the tty driver when it wants to know how
 *	many bytes of data we currently have outstanding in the port (data that
 *	has been written, but hasn't made it out the port yet)
 *	If successful, we वापस the number of bytes left to be written in the
 *	प्रणाली,
 *	Otherwise we वापस a negative error number.
 *****************************************************************************/
अटल पूर्णांक edge_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक num_अक्षरs;
	अचिन्हित दीर्घ flags;

	अगर (edge_port == शून्य)
		वापस 0;
	अगर (edge_port->बंदPending)
		वापस 0;

	अगर (!edge_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&edge_port->ep_lock, flags);
	num_अक्षरs = edge_port->maxTxCredits - edge_port->txCredits +
						edge_port->txfअगरo.count;
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);
	अगर (num_अक्षरs) अणु
		dev_dbg(&port->dev, "%s - returns %d\n", __func__, num_अक्षरs);
	पूर्ण

	वापस num_अक्षरs;
पूर्ण


/*****************************************************************************
 * SerialThrottle
 *	this function is called by the tty driver when it wants to stop the data
 *	being पढ़ो from the port.
 *****************************************************************************/
अटल व्योम edge_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	अगर (edge_port == शून्य)
		वापस;

	अगर (!edge_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	/* अगर we are implementing XON/XOFF, send the stop अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर stop_अक्षर = STOP_CHAR(tty);
		status = edge_ग_लिखो(tty, port, &stop_अक्षर, 1);
		अगर (status <= 0)
			वापस;
	पूर्ण

	/* अगर we are implementing RTS/CTS, toggle that line */
	अगर (C_CRTSCTS(tty)) अणु
		edge_port->shaकरोwMCR &= ~MCR_RTS;
		status = send_cmd_ग_लिखो_uart_रेजिस्टर(edge_port, MCR,
							edge_port->shaकरोwMCR);
		अगर (status != 0)
			वापस;
	पूर्ण
पूर्ण


/*****************************************************************************
 * edge_unthrottle
 *	this function is called by the tty driver when it wants to resume the
 *	data being पढ़ो from the port (called after SerialThrottle is called)
 *****************************************************************************/
अटल व्योम edge_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	अगर (edge_port == शून्य)
		वापस;

	अगर (!edge_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	/* अगर we are implementing XON/XOFF, send the start अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर start_अक्षर = START_CHAR(tty);
		status = edge_ग_लिखो(tty, port, &start_अक्षर, 1);
		अगर (status <= 0)
			वापस;
	पूर्ण
	/* अगर we are implementing RTS/CTS, toggle that line */
	अगर (C_CRTSCTS(tty)) अणु
		edge_port->shaकरोwMCR |= MCR_RTS;
		send_cmd_ग_लिखो_uart_रेजिस्टर(edge_port, MCR,
						edge_port->shaकरोwMCR);
	पूर्ण
पूर्ण


/*****************************************************************************
 * SerialSetTermios
 *	this function is called by the tty driver when it wants to change
 * the termios काष्ठाure
 *****************************************************************************/
अटल व्योम edge_set_termios(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);

	अगर (edge_port == शून्य)
		वापस;

	अगर (!edge_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	/* change the port settings to the new ones specअगरied */
	change_port_settings(tty, edge_port, old_termios);
पूर्ण


/*****************************************************************************
 * get_lsr_info - get line status रेजिस्टर info
 *
 * Purpose: Let user call ioctl() to get info when the UART physically
 * 	    is emptied.  On bus types like RS485, the transmitter must
 * 	    release the bus after transmitting. This must be करोne when
 * 	    the transmit shअगरt रेजिस्टर is empty, not be करोne when the
 * 	    transmit holding रेजिस्टर is empty.  This functionality
 * 	    allows an RS485 driver to be written in user space.
 *****************************************************************************/
अटल पूर्णांक get_lsr_info(काष्ठा edgeport_port *edge_port,
						अचिन्हित पूर्णांक __user *value)
अणु
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);
	अगर (edge_port->maxTxCredits == edge_port->txCredits &&
	    edge_port->txfअगरo.count == 0) अणु
		dev_dbg(&edge_port->port->dev, "%s -- Empty\n", __func__);
		result = TIOCSER_TEMT;
	पूर्ण
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	अगर (copy_to_user(value, &result, माप(पूर्णांक)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक edge_tiocmset(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक mcr;

	mcr = edge_port->shaकरोwMCR;
	अगर (set & TIOCM_RTS)
		mcr |= MCR_RTS;
	अगर (set & TIOCM_DTR)
		mcr |= MCR_DTR;
	अगर (set & TIOCM_LOOP)
		mcr |= MCR_LOOPBACK;

	अगर (clear & TIOCM_RTS)
		mcr &= ~MCR_RTS;
	अगर (clear & TIOCM_DTR)
		mcr &= ~MCR_DTR;
	अगर (clear & TIOCM_LOOP)
		mcr &= ~MCR_LOOPBACK;

	edge_port->shaकरोwMCR = mcr;

	send_cmd_ग_लिखो_uart_रेजिस्टर(edge_port, MCR, edge_port->shaकरोwMCR);

	वापस 0;
पूर्ण

अटल पूर्णांक edge_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित पूर्णांक msr;
	अचिन्हित पूर्णांक mcr;

	msr = edge_port->shaकरोwMSR;
	mcr = edge_port->shaकरोwMCR;
	result = ((mcr & MCR_DTR)	? TIOCM_DTR: 0)	  /* 0x002 */
		  | ((mcr & MCR_RTS)	? TIOCM_RTS: 0)   /* 0x004 */
		  | ((msr & EDGEPORT_MSR_CTS)	? TIOCM_CTS: 0)   /* 0x020 */
		  | ((msr & EDGEPORT_MSR_CD)	? TIOCM_CAR: 0)   /* 0x040 */
		  | ((msr & EDGEPORT_MSR_RI)	? TIOCM_RI:  0)   /* 0x080 */
		  | ((msr & EDGEPORT_MSR_DSR)	? TIOCM_DSR: 0);  /* 0x100 */

	वापस result;
पूर्ण

/*****************************************************************************
 * SerialIoctl
 *	this function handles any ioctl calls to the driver
 *****************************************************************************/
अटल पूर्णांक edge_ioctl(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);

	चयन (cmd) अणु
	हाल TIOCSERGETLSR:
		dev_dbg(&port->dev, "%s TIOCSERGETLSR\n", __func__);
		वापस get_lsr_info(edge_port, (अचिन्हित पूर्णांक __user *) arg);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण


/*****************************************************************************
 * SerialBreak
 *	this function sends a अवरोध to the port
 *****************************************************************************/
अटल व्योम edge_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा edgeport_port *edge_port = usb_get_serial_port_data(port);
	काष्ठा edgeport_serial *edge_serial = usb_get_serial_data(port->serial);
	पूर्णांक status;

	अगर (!edge_serial->is_epic ||
	    edge_serial->epic_descriptor.Supports.IOSPChase) अणु
		/* flush and chase */
		edge_port->chaseResponsePending = true;

		dev_dbg(&port->dev, "%s - Sending IOSP_CMD_CHASE_PORT\n", __func__);
		status = send_iosp_ext_cmd(edge_port, IOSP_CMD_CHASE_PORT, 0);
		अगर (status == 0) अणु
			/* block until chase finished */
			block_until_chase_response(edge_port);
		पूर्ण अन्यथा अणु
			edge_port->chaseResponsePending = false;
		पूर्ण
	पूर्ण

	अगर (!edge_serial->is_epic ||
	    edge_serial->epic_descriptor.Supports.IOSPSetClrBreak) अणु
		अगर (अवरोध_state == -1) अणु
			dev_dbg(&port->dev, "%s - Sending IOSP_CMD_SET_BREAK\n", __func__);
			status = send_iosp_ext_cmd(edge_port,
						IOSP_CMD_SET_BREAK, 0);
		पूर्ण अन्यथा अणु
			dev_dbg(&port->dev, "%s - Sending IOSP_CMD_CLEAR_BREAK\n", __func__);
			status = send_iosp_ext_cmd(edge_port,
						IOSP_CMD_CLEAR_BREAK, 0);
		पूर्ण
		अगर (status)
			dev_dbg(&port->dev, "%s - error sending break set/clear command.\n",
				__func__);
	पूर्ण
पूर्ण


/*****************************************************************************
 * process_rcvd_data
 *	this function handles the data received on the bulk in pipe.
 *****************************************************************************/
अटल व्योम process_rcvd_data(काष्ठा edgeport_serial *edge_serial,
				अचिन्हित अक्षर *buffer, __u16 bufferLength)
अणु
	काष्ठा usb_serial *serial = edge_serial->serial;
	काष्ठा device *dev = &serial->dev->dev;
	काष्ठा usb_serial_port *port;
	काष्ठा edgeport_port *edge_port;
	__u16 lastBufferLength;
	__u16 rxLen;

	lastBufferLength = bufferLength + 1;

	जबतक (bufferLength > 0) अणु
		/* failsafe inहाल we get a message that we करोn't understand */
		अगर (lastBufferLength == bufferLength) अणु
			dev_dbg(dev, "%s - stuck in loop, exiting it.\n", __func__);
			अवरोध;
		पूर्ण
		lastBufferLength = bufferLength;

		चयन (edge_serial->rxState) अणु
		हाल EXPECT_HDR1:
			edge_serial->rxHeader1 = *buffer;
			++buffer;
			--bufferLength;

			अगर (bufferLength == 0) अणु
				edge_serial->rxState = EXPECT_HDR2;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल EXPECT_HDR2:
			edge_serial->rxHeader2 = *buffer;
			++buffer;
			--bufferLength;

			dev_dbg(dev, "%s - Hdr1=%02X Hdr2=%02X\n", __func__,
				edge_serial->rxHeader1, edge_serial->rxHeader2);
			/* Process depending on whether this header is
			 * data or status */

			अगर (IS_CMD_STAT_HDR(edge_serial->rxHeader1)) अणु
				/* Decode this status header and go to
				 * EXPECT_HDR1 (अगर we can process the status
				 * with only 2 bytes), or go to EXPECT_HDR3 to
				 * get the third byte. */
				edge_serial->rxPort =
				    IOSP_GET_HDR_PORT(edge_serial->rxHeader1);
				edge_serial->rxStatusCode =
				    IOSP_GET_STATUS_CODE(
						edge_serial->rxHeader1);

				अगर (!IOSP_STATUS_IS_2BYTE(
						edge_serial->rxStatusCode)) अणु
					/* This status needs additional bytes.
					 * Save what we have and then रुको क्रम
					 * more data.
					 */
					edge_serial->rxStatusParam
						= edge_serial->rxHeader2;
					edge_serial->rxState = EXPECT_HDR3;
					अवरोध;
				पूर्ण
				/* We have all the header bytes, process the
				   status now */
				process_rcvd_status(edge_serial,
						edge_serial->rxHeader2, 0);
				edge_serial->rxState = EXPECT_HDR1;
				अवरोध;
			पूर्ण

			edge_serial->rxPort = IOSP_GET_HDR_PORT(edge_serial->rxHeader1);
			edge_serial->rxBytesReमुख्यing = IOSP_GET_HDR_DATA_LEN(edge_serial->rxHeader1,
									      edge_serial->rxHeader2);
			dev_dbg(dev, "%s - Data for Port %u Len %u\n", __func__,
				edge_serial->rxPort,
				edge_serial->rxBytesReमुख्यing);

			अगर (bufferLength == 0) अणु
				edge_serial->rxState = EXPECT_DATA;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल EXPECT_DATA: /* Expect data */
			अगर (bufferLength < edge_serial->rxBytesReमुख्यing) अणु
				rxLen = bufferLength;
				/* Expect data to start next buffer */
				edge_serial->rxState = EXPECT_DATA;
			पूर्ण अन्यथा अणु
				/* BufLen >= RxBytesReमुख्यing */
				rxLen = edge_serial->rxBytesReमुख्यing;
				/* Start another header next समय */
				edge_serial->rxState = EXPECT_HDR1;
			पूर्ण

			bufferLength -= rxLen;
			edge_serial->rxBytesReमुख्यing -= rxLen;

			/* spit this data back पूर्णांकo the tty driver अगर this
			   port is खोलो */
			अगर (rxLen && edge_serial->rxPort < serial->num_ports) अणु
				port = serial->port[edge_serial->rxPort];
				edge_port = usb_get_serial_port_data(port);
				अगर (edge_port && edge_port->खोलो) अणु
					dev_dbg(dev, "%s - Sending %d bytes to TTY for port %d\n",
						__func__, rxLen,
						edge_serial->rxPort);
					edge_tty_recv(edge_port->port, buffer,
							rxLen);
					edge_port->port->icount.rx += rxLen;
				पूर्ण
			पूर्ण
			buffer += rxLen;
			अवरोध;

		हाल EXPECT_HDR3:	/* Expect 3rd byte of status header */
			edge_serial->rxHeader3 = *buffer;
			++buffer;
			--bufferLength;

			/* We have all the header bytes, process the
			   status now */
			process_rcvd_status(edge_serial,
				edge_serial->rxStatusParam,
				edge_serial->rxHeader3);
			edge_serial->rxState = EXPECT_HDR1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण


/*****************************************************************************
 * process_rcvd_status
 *	this function handles the any status messages received on the
 *	bulk in pipe.
 *****************************************************************************/
अटल व्योम process_rcvd_status(काष्ठा edgeport_serial *edge_serial,
						__u8 byte2, __u8 byte3)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा edgeport_port *edge_port;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा device *dev;
	__u8 code = edge_serial->rxStatusCode;

	/* चयन the port poपूर्णांकer to the one being currently talked about */
	अगर (edge_serial->rxPort >= edge_serial->serial->num_ports)
		वापस;
	port = edge_serial->serial->port[edge_serial->rxPort];
	edge_port = usb_get_serial_port_data(port);
	अगर (edge_port == शून्य) अणु
		dev_err(&edge_serial->serial->dev->dev,
			"%s - edge_port == NULL for port %d\n",
					__func__, edge_serial->rxPort);
		वापस;
	पूर्ण
	dev = &port->dev;

	अगर (code == IOSP_EXT_STATUS) अणु
		चयन (byte2) अणु
		हाल IOSP_EXT_STATUS_CHASE_RSP:
			/* we want to करो EXT status regardless of port
			 * खोलो/बंदd */
			dev_dbg(dev, "%s - Port %u EXT CHASE_RSP Data = %02x\n",
				__func__, edge_serial->rxPort, byte3);
			/* Currently, the only EXT_STATUS is Chase, so process
			 * here instead of one more call to one more subroutine
			 * If/when more EXT_STATUS, there'll be more work to करो
			 * Also, we currently clear flag and बंद the port
			 * regardless of content of above's Byte3.
			 * We could choose to करो something अन्यथा when Byte3 says
			 * Timeout on Chase from Edgeport, like रुको दीर्घer in
			 * block_until_chase_response, but क्रम now we करोn't.
			 */
			edge_port->chaseResponsePending = false;
			wake_up(&edge_port->रुको_chase);
			वापस;

		हाल IOSP_EXT_STATUS_RX_CHECK_RSP:
			dev_dbg(dev, "%s ========== Port %u CHECK_RSP Sequence = %02x =============\n",
				__func__, edge_serial->rxPort, byte3);
			/* Port->RxCheckRsp = true; */
			वापस;
		पूर्ण
	पूर्ण

	अगर (code == IOSP_STATUS_OPEN_RSP) अणु
		edge_port->txCredits = GET_TX_BUFFER_SIZE(byte3);
		edge_port->maxTxCredits = edge_port->txCredits;
		dev_dbg(dev, "%s - Port %u Open Response Initial MSR = %02x TxBufferSize = %d\n",
			__func__, edge_serial->rxPort, byte2, edge_port->txCredits);
		handle_new_msr(edge_port, byte2);

		/* send the current line settings to the port so we are
		   in sync with any further termios calls */
		tty = tty_port_tty_get(&edge_port->port->port);
		अगर (tty) अणु
			change_port_settings(tty,
				edge_port, &tty->termios);
			tty_kref_put(tty);
		पूर्ण

		/* we have completed the खोलो */
		edge_port->खोलोPending = false;
		edge_port->खोलो = true;
		wake_up(&edge_port->रुको_खोलो);
		वापस;
	पूर्ण

	/* If port is बंदd, silently discard all rcvd status. We can
	 * have हालs where buffered status is received AFTER the बंद
	 * port command is sent to the Edgeport.
	 */
	अगर (!edge_port->खोलो || edge_port->बंदPending)
		वापस;

	चयन (code) अणु
	/* Not currently sent by Edgeport */
	हाल IOSP_STATUS_LSR:
		dev_dbg(dev, "%s - Port %u LSR Status = %02x\n",
			__func__, edge_serial->rxPort, byte2);
		handle_new_lsr(edge_port, false, byte2, 0);
		अवरोध;

	हाल IOSP_STATUS_LSR_DATA:
		dev_dbg(dev, "%s - Port %u LSR Status = %02x, Data = %02x\n",
			__func__, edge_serial->rxPort, byte2, byte3);
		/* byte2 is LSR Register */
		/* byte3 is broken data byte */
		handle_new_lsr(edge_port, true, byte2, byte3);
		अवरोध;
	/*
	 *	हाल IOSP_EXT_4_STATUS:
	 *		dev_dbg(dev, "%s - Port %u LSR Status = %02x Data = %02x\n",
	 *			__func__, edge_serial->rxPort, byte2, byte3);
	 *		अवरोध;
	 */
	हाल IOSP_STATUS_MSR:
		dev_dbg(dev, "%s - Port %u MSR Status = %02x\n",
			__func__, edge_serial->rxPort, byte2);
		/*
		 * Process this new modem status and generate appropriate
		 * events, etc, based on the new status. This routine
		 * also saves the MSR in Port->ShaकरोwMsr.
		 */
		handle_new_msr(edge_port, byte2);
		अवरोध;

	शेष:
		dev_dbg(dev, "%s - Unrecognized IOSP status code %u\n", __func__, code);
		अवरोध;
	पूर्ण
पूर्ण


/*****************************************************************************
 * edge_tty_recv
 *	this function passes data on to the tty flip buffer
 *****************************************************************************/
अटल व्योम edge_tty_recv(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *data,
		पूर्णांक length)
अणु
	पूर्णांक cnt;

	cnt = tty_insert_flip_string(&port->port, data, length);
	अगर (cnt < length) अणु
		dev_err(&port->dev, "%s - dropping data, %d bytes lost\n",
				__func__, length - cnt);
	पूर्ण
	data += cnt;
	length -= cnt;

	tty_flip_buffer_push(&port->port);
पूर्ण


/*****************************************************************************
 * handle_new_msr
 *	this function handles any change to the msr रेजिस्टर क्रम a port.
 *****************************************************************************/
अटल व्योम handle_new_msr(काष्ठा edgeport_port *edge_port, __u8 newMsr)
अणु
	काष्ठा  async_icount *icount;

	अगर (newMsr & (EDGEPORT_MSR_DELTA_CTS | EDGEPORT_MSR_DELTA_DSR |
			EDGEPORT_MSR_DELTA_RI | EDGEPORT_MSR_DELTA_CD)) अणु
		icount = &edge_port->port->icount;

		/* update input line counters */
		अगर (newMsr & EDGEPORT_MSR_DELTA_CTS)
			icount->cts++;
		अगर (newMsr & EDGEPORT_MSR_DELTA_DSR)
			icount->dsr++;
		अगर (newMsr & EDGEPORT_MSR_DELTA_CD)
			icount->dcd++;
		अगर (newMsr & EDGEPORT_MSR_DELTA_RI)
			icount->rng++;
		wake_up_पूर्णांकerruptible(&edge_port->port->port.delta_msr_रुको);
	पूर्ण

	/* Save the new modem status */
	edge_port->shaकरोwMSR = newMsr & 0xf0;
पूर्ण


/*****************************************************************************
 * handle_new_lsr
 *	this function handles any change to the lsr रेजिस्टर क्रम a port.
 *****************************************************************************/
अटल व्योम handle_new_lsr(काष्ठा edgeport_port *edge_port, __u8 lsrData,
							__u8 lsr, __u8 data)
अणु
	__u8 newLsr = (__u8) (lsr & (__u8)
		(LSR_OVER_ERR | LSR_PAR_ERR | LSR_FRM_ERR | LSR_BREAK));
	काष्ठा async_icount *icount;

	edge_port->shaकरोwLSR = lsr;

	अगर (newLsr & LSR_BREAK) अणु
		/*
		 * Parity and Framing errors only count अगर they
		 * occur exclusive of a अवरोध being
		 * received.
		 */
		newLsr &= (__u8)(LSR_OVER_ERR | LSR_BREAK);
	पूर्ण

	/* Place LSR data byte पूर्णांकo Rx buffer */
	अगर (lsrData)
		edge_tty_recv(edge_port->port, &data, 1);

	/* update input line counters */
	icount = &edge_port->port->icount;
	अगर (newLsr & LSR_BREAK)
		icount->brk++;
	अगर (newLsr & LSR_OVER_ERR)
		icount->overrun++;
	अगर (newLsr & LSR_PAR_ERR)
		icount->parity++;
	अगर (newLsr & LSR_FRM_ERR)
		icount->frame++;
पूर्ण


/****************************************************************************
 * sram_ग_लिखो
 *	ग_लिखोs a number of bytes to the Edgeport device's sram starting at the
 *	given address.
 *	If successful वापसs the number of bytes written, otherwise it वापसs
 *	a negative error number of the problem.
 ****************************************************************************/
अटल पूर्णांक sram_ग_लिखो(काष्ठा usb_serial *serial, __u16 extAddr, __u16 addr,
					__u16 length, स्थिर __u8 *data)
अणु
	पूर्णांक result;
	__u16 current_length;
	अचिन्हित अक्षर *transfer_buffer;

	dev_dbg(&serial->dev->dev, "%s - %x, %x, %d\n", __func__, extAddr, addr, length);

	transfer_buffer =  kदो_स्मृति(64, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	/* need to split these ग_लिखोs up पूर्णांकo 64 byte chunks */
	result = 0;
	जबतक (length > 0) अणु
		अगर (length > 64)
			current_length = 64;
		अन्यथा
			current_length = length;

/*		dev_dbg(&serial->dev->dev, "%s - writing %x, %x, %d\n", __func__, extAddr, addr, current_length); */
		स_नकल(transfer_buffer, data, current_length);
		result = usb_control_msg(serial->dev,
					usb_sndctrlpipe(serial->dev, 0),
					USB_REQUEST_ION_WRITE_RAM,
					0x40, addr, extAddr, transfer_buffer,
					current_length, 300);
		अगर (result < 0)
			अवरोध;
		length -= current_length;
		addr += current_length;
		data += current_length;
	पूर्ण

	kमुक्त(transfer_buffer);
	वापस result;
पूर्ण


/****************************************************************************
 * rom_ग_लिखो
 *	ग_लिखोs a number of bytes to the Edgeport device's ROM starting at the
 *	given address.
 *	If successful वापसs the number of bytes written, otherwise it वापसs
 *	a negative error number of the problem.
 ****************************************************************************/
अटल पूर्णांक rom_ग_लिखो(काष्ठा usb_serial *serial, __u16 extAddr, __u16 addr,
					__u16 length, स्थिर __u8 *data)
अणु
	पूर्णांक result;
	__u16 current_length;
	अचिन्हित अक्षर *transfer_buffer;

	transfer_buffer =  kदो_स्मृति(64, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	/* need to split these ग_लिखोs up पूर्णांकo 64 byte chunks */
	result = 0;
	जबतक (length > 0) अणु
		अगर (length > 64)
			current_length = 64;
		अन्यथा
			current_length = length;
		स_नकल(transfer_buffer, data, current_length);
		result = usb_control_msg(serial->dev,
					usb_sndctrlpipe(serial->dev, 0),
					USB_REQUEST_ION_WRITE_ROM, 0x40,
					addr, extAddr,
					transfer_buffer, current_length, 300);
		अगर (result < 0)
			अवरोध;
		length -= current_length;
		addr += current_length;
		data += current_length;
	पूर्ण

	kमुक्त(transfer_buffer);
	वापस result;
पूर्ण


/****************************************************************************
 * rom_पढ़ो
 *	पढ़ोs a number of bytes from the Edgeport device starting at the given
 *	address.
 *	Returns zero on success or a negative error number.
 ****************************************************************************/
अटल पूर्णांक rom_पढ़ो(काष्ठा usb_serial *serial, __u16 extAddr,
					__u16 addr, __u16 length, __u8 *data)
अणु
	पूर्णांक result;
	__u16 current_length;
	अचिन्हित अक्षर *transfer_buffer;

	transfer_buffer =  kदो_स्मृति(64, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	/* need to split these पढ़ोs up पूर्णांकo 64 byte chunks */
	result = 0;
	जबतक (length > 0) अणु
		अगर (length > 64)
			current_length = 64;
		अन्यथा
			current_length = length;
		result = usb_control_msg(serial->dev,
					usb_rcvctrlpipe(serial->dev, 0),
					USB_REQUEST_ION_READ_ROM,
					0xC0, addr, extAddr, transfer_buffer,
					current_length, 300);
		अगर (result < current_length) अणु
			अगर (result >= 0)
				result = -EIO;
			अवरोध;
		पूर्ण
		स_नकल(data, transfer_buffer, current_length);
		length -= current_length;
		addr += current_length;
		data += current_length;

		result = 0;
	पूर्ण

	kमुक्त(transfer_buffer);
	वापस result;
पूर्ण


/****************************************************************************
 * send_iosp_ext_cmd
 *	Is used to send a IOSP message to the Edgeport device
 ****************************************************************************/
अटल पूर्णांक send_iosp_ext_cmd(काष्ठा edgeport_port *edge_port,
						__u8 command, __u8 param)
अणु
	अचिन्हित अक्षर   *buffer;
	अचिन्हित अक्षर   *currentCommand;
	पूर्णांक             length = 0;
	पूर्णांक             status = 0;

	buffer = kदो_स्मृति(10, GFP_ATOMIC);
	अगर (!buffer)
		वापस -ENOMEM;

	currentCommand = buffer;

	MAKE_CMD_EXT_CMD(&currentCommand, &length, edge_port->port->port_number,
			 command, param);

	status = ग_लिखो_cmd_usb(edge_port, buffer, length);
	अगर (status) अणु
		/* something bad happened, let's मुक्त up the memory */
		kमुक्त(buffer);
	पूर्ण

	वापस status;
पूर्ण


/*****************************************************************************
 * ग_लिखो_cmd_usb
 *	this function ग_लिखोs the given buffer out to the bulk ग_लिखो endpoपूर्णांक.
 *****************************************************************************/
अटल पूर्णांक ग_लिखो_cmd_usb(काष्ठा edgeport_port *edge_port,
					अचिन्हित अक्षर *buffer, पूर्णांक length)
अणु
	काष्ठा edgeport_serial *edge_serial =
				usb_get_serial_data(edge_port->port->serial);
	काष्ठा device *dev = &edge_port->port->dev;
	पूर्णांक status = 0;
	काष्ठा urb *urb;

	usb_serial_debug_data(dev, __func__, length, buffer);

	/* Allocate our next urb */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		वापस -ENOMEM;

	atomic_inc(&CmdUrbs);
	dev_dbg(dev, "%s - ALLOCATE URB %p (outstanding %d)\n",
		__func__, urb, atomic_पढ़ो(&CmdUrbs));

	usb_fill_bulk_urb(urb, edge_serial->serial->dev,
			usb_sndbulkpipe(edge_serial->serial->dev,
					edge_serial->bulk_out_endpoपूर्णांक),
			buffer, length, edge_bulk_out_cmd_callback, edge_port);

	edge_port->commandPending = true;
	status = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (status) अणु
		/* something went wrong */
		dev_err(dev, "%s - usb_submit_urb(write command) failed, status = %d\n",
			__func__, status);
		usb_मुक्त_urb(urb);
		atomic_dec(&CmdUrbs);
		वापस status;
	पूर्ण

#अगर 0
	रुको_event(&edge_port->रुको_command, !edge_port->commandPending);

	अगर (edge_port->commandPending) अणु
		/* command समयd out */
		dev_dbg(dev, "%s - command timed out\n", __func__);
		status = -EINVAL;
	पूर्ण
#पूर्ण_अगर
	वापस status;
पूर्ण


/*****************************************************************************
 * send_cmd_ग_लिखो_baud_rate
 *	this function sends the proper command to change the baud rate of the
 *	specअगरied port.
 *****************************************************************************/
अटल पूर्णांक send_cmd_ग_लिखो_baud_rate(काष्ठा edgeport_port *edge_port,
								पूर्णांक baudRate)
अणु
	काष्ठा edgeport_serial *edge_serial =
				usb_get_serial_data(edge_port->port->serial);
	काष्ठा device *dev = &edge_port->port->dev;
	अचिन्हित अक्षर *cmdBuffer;
	अचिन्हित अक्षर *currCmd;
	पूर्णांक cmdLen = 0;
	पूर्णांक भागisor;
	पूर्णांक status;
	u32 number = edge_port->port->port_number;

	अगर (edge_serial->is_epic &&
	    !edge_serial->epic_descriptor.Supports.IOSPSetBaudRate) अणु
		dev_dbg(dev, "SendCmdWriteBaudRate - NOT Setting baud rate for port, baud = %d\n",
			baudRate);
		वापस 0;
	पूर्ण

	dev_dbg(dev, "%s - baud = %d\n", __func__, baudRate);

	status = calc_baud_rate_भागisor(dev, baudRate, &भागisor);
	अगर (status) अणु
		dev_err(dev, "%s - bad baud rate\n", __func__);
		वापस status;
	पूर्ण

	/* Alloc memory क्रम the string of commands. */
	cmdBuffer =  kदो_स्मृति(0x100, GFP_ATOMIC);
	अगर (!cmdBuffer)
		वापस -ENOMEM;

	currCmd = cmdBuffer;

	/* Enable access to भागisor latch */
	MAKE_CMD_WRITE_REG(&currCmd, &cmdLen, number, LCR, LCR_DL_ENABLE);

	/* Write the भागisor itself */
	MAKE_CMD_WRITE_REG(&currCmd, &cmdLen, number, DLL, LOW8(भागisor));
	MAKE_CMD_WRITE_REG(&currCmd, &cmdLen, number, DLM, HIGH8(भागisor));

	/* Restore original value to disable access to भागisor latch */
	MAKE_CMD_WRITE_REG(&currCmd, &cmdLen, number, LCR,
						edge_port->shaकरोwLCR);

	status = ग_लिखो_cmd_usb(edge_port, cmdBuffer, cmdLen);
	अगर (status) अणु
		/* something bad happened, let's मुक्त up the memory */
		kमुक्त(cmdBuffer);
	पूर्ण

	वापस status;
पूर्ण


/*****************************************************************************
 * calc_baud_rate_भागisor
 *	this function calculates the proper baud rate भागisor क्रम the specअगरied
 *	baud rate.
 *****************************************************************************/
अटल पूर्णांक calc_baud_rate_भागisor(काष्ठा device *dev, पूर्णांक baudrate, पूर्णांक *भागisor)
अणु
	पूर्णांक i;
	__u16 custom;

	क्रम (i = 0; i < ARRAY_SIZE(भागisor_table); i++) अणु
		अगर (भागisor_table[i].BaudRate == baudrate) अणु
			*भागisor = भागisor_table[i].Divisor;
			वापस 0;
		पूर्ण
	पूर्ण

	/* We have tried all of the standard baud rates
	 * lets try to calculate the भागisor क्रम this baud rate
	 * Make sure the baud rate is reasonable */
	अगर (baudrate > 50 && baudrate < 230400) अणु
		/* get भागisor */
		custom = (__u16)((230400L + baudrate/2) / baudrate);

		*भागisor = custom;

		dev_dbg(dev, "%s - Baud %d = %d\n", __func__, baudrate, custom);
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण


/*****************************************************************************
 * send_cmd_ग_लिखो_uart_रेजिस्टर
 *  this function builds up a uart रेजिस्टर message and sends to the device.
 *****************************************************************************/
अटल पूर्णांक send_cmd_ग_लिखो_uart_रेजिस्टर(काष्ठा edgeport_port *edge_port,
						__u8 regNum, __u8 regValue)
अणु
	काष्ठा edgeport_serial *edge_serial =
				usb_get_serial_data(edge_port->port->serial);
	काष्ठा device *dev = &edge_port->port->dev;
	अचिन्हित अक्षर *cmdBuffer;
	अचिन्हित अक्षर *currCmd;
	अचिन्हित दीर्घ cmdLen = 0;
	पूर्णांक status;

	dev_dbg(dev, "%s - write to %s register 0x%02x\n",
		(regNum == MCR) ? "MCR" : "LCR", __func__, regValue);

	अगर (edge_serial->is_epic &&
	    !edge_serial->epic_descriptor.Supports.IOSPWriteMCR &&
	    regNum == MCR) अणु
		dev_dbg(dev, "SendCmdWriteUartReg - Not writing to MCR Register\n");
		वापस 0;
	पूर्ण

	अगर (edge_serial->is_epic &&
	    !edge_serial->epic_descriptor.Supports.IOSPWriteLCR &&
	    regNum == LCR) अणु
		dev_dbg(dev, "SendCmdWriteUartReg - Not writing to LCR Register\n");
		वापस 0;
	पूर्ण

	/* Alloc memory क्रम the string of commands. */
	cmdBuffer = kदो_स्मृति(0x10, GFP_ATOMIC);
	अगर (cmdBuffer == शून्य)
		वापस -ENOMEM;

	currCmd = cmdBuffer;

	/* Build a cmd in the buffer to ग_लिखो the given रेजिस्टर */
	MAKE_CMD_WRITE_REG(&currCmd, &cmdLen, edge_port->port->port_number,
			   regNum, regValue);

	status = ग_लिखो_cmd_usb(edge_port, cmdBuffer, cmdLen);
	अगर (status) अणु
		/* something bad happened, let's मुक्त up the memory */
		kमुक्त(cmdBuffer);
	पूर्ण

	वापस status;
पूर्ण


/*****************************************************************************
 * change_port_settings
 *	This routine is called to set the UART on the device to match the
 *	specअगरied new settings.
 *****************************************************************************/

अटल व्योम change_port_settings(काष्ठा tty_काष्ठा *tty,
	काष्ठा edgeport_port *edge_port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा device *dev = &edge_port->port->dev;
	काष्ठा edgeport_serial *edge_serial =
			usb_get_serial_data(edge_port->port->serial);
	पूर्णांक baud;
	अचिन्हित cflag;
	__u8 mask = 0xff;
	__u8 lData;
	__u8 lParity;
	__u8 lStop;
	__u8 rxFlow;
	__u8 txFlow;
	पूर्णांक status;

	अगर (!edge_port->खोलो &&
	    !edge_port->खोलोPending) अणु
		dev_dbg(dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	cflag = tty->termios.c_cflag;

	चयन (cflag & CSIZE) अणु
	हाल CS5:
		lData = LCR_BITS_5; mask = 0x1f;
		dev_dbg(dev, "%s - data bits = 5\n", __func__);
		अवरोध;
	हाल CS6:
		lData = LCR_BITS_6; mask = 0x3f;
		dev_dbg(dev, "%s - data bits = 6\n", __func__);
		अवरोध;
	हाल CS7:
		lData = LCR_BITS_7; mask = 0x7f;
		dev_dbg(dev, "%s - data bits = 7\n", __func__);
		अवरोध;
	शेष:
	हाल CS8:
		lData = LCR_BITS_8;
		dev_dbg(dev, "%s - data bits = 8\n", __func__);
		अवरोध;
	पूर्ण

	lParity = LCR_PAR_NONE;
	अगर (cflag & PARENB) अणु
		अगर (cflag & CMSPAR) अणु
			अगर (cflag & PARODD) अणु
				lParity = LCR_PAR_MARK;
				dev_dbg(dev, "%s - parity = mark\n", __func__);
			पूर्ण अन्यथा अणु
				lParity = LCR_PAR_SPACE;
				dev_dbg(dev, "%s - parity = space\n", __func__);
			पूर्ण
		पूर्ण अन्यथा अगर (cflag & PARODD) अणु
			lParity = LCR_PAR_ODD;
			dev_dbg(dev, "%s - parity = odd\n", __func__);
		पूर्ण अन्यथा अणु
			lParity = LCR_PAR_EVEN;
			dev_dbg(dev, "%s - parity = even\n", __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s - parity = none\n", __func__);
	पूर्ण

	अगर (cflag & CSTOPB) अणु
		lStop = LCR_STOP_2;
		dev_dbg(dev, "%s - stop bits = 2\n", __func__);
	पूर्ण अन्यथा अणु
		lStop = LCR_STOP_1;
		dev_dbg(dev, "%s - stop bits = 1\n", __func__);
	पूर्ण

	/* figure out the flow control settings */
	rxFlow = txFlow = 0x00;
	अगर (cflag & CRTSCTS) अणु
		rxFlow |= IOSP_RX_FLOW_RTS;
		txFlow |= IOSP_TX_FLOW_CTS;
		dev_dbg(dev, "%s - RTS/CTS is enabled\n", __func__);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s - RTS/CTS is disabled\n", __func__);
	पूर्ण

	/* अगर we are implementing XON/XOFF, set the start and stop अक्षरacter
	   in the device */
	अगर (I_IXOFF(tty) || I_IXON(tty)) अणु
		अचिन्हित अक्षर stop_अक्षर  = STOP_CHAR(tty);
		अचिन्हित अक्षर start_अक्षर = START_CHAR(tty);

		अगर (!edge_serial->is_epic ||
		    edge_serial->epic_descriptor.Supports.IOSPSetXChar) अणु
			send_iosp_ext_cmd(edge_port,
					IOSP_CMD_SET_XON_CHAR, start_अक्षर);
			send_iosp_ext_cmd(edge_port,
					IOSP_CMD_SET_XOFF_CHAR, stop_अक्षर);
		पूर्ण

		/* अगर we are implementing INBOUND XON/XOFF */
		अगर (I_IXOFF(tty)) अणु
			rxFlow |= IOSP_RX_FLOW_XON_XOFF;
			dev_dbg(dev, "%s - INBOUND XON/XOFF is enabled, XON = %2x, XOFF = %2x\n",
				__func__, start_अक्षर, stop_अक्षर);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "%s - INBOUND XON/XOFF is disabled\n", __func__);
		पूर्ण

		/* अगर we are implementing OUTBOUND XON/XOFF */
		अगर (I_IXON(tty)) अणु
			txFlow |= IOSP_TX_FLOW_XON_XOFF;
			dev_dbg(dev, "%s - OUTBOUND XON/XOFF is enabled, XON = %2x, XOFF = %2x\n",
				__func__, start_अक्षर, stop_अक्षर);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "%s - OUTBOUND XON/XOFF is disabled\n", __func__);
		पूर्ण
	पूर्ण

	/* Set flow control to the configured value */
	अगर (!edge_serial->is_epic ||
	    edge_serial->epic_descriptor.Supports.IOSPSetRxFlow)
		send_iosp_ext_cmd(edge_port, IOSP_CMD_SET_RX_FLOW, rxFlow);
	अगर (!edge_serial->is_epic ||
	    edge_serial->epic_descriptor.Supports.IOSPSetTxFlow)
		send_iosp_ext_cmd(edge_port, IOSP_CMD_SET_TX_FLOW, txFlow);


	edge_port->shaकरोwLCR &= ~(LCR_BITS_MASK | LCR_STOP_MASK | LCR_PAR_MASK);
	edge_port->shaकरोwLCR |= (lData | lParity | lStop);

	edge_port->validDataMask = mask;

	/* Send the updated LCR value to the EdgePort */
	status = send_cmd_ग_लिखो_uart_रेजिस्टर(edge_port, LCR,
							edge_port->shaकरोwLCR);
	अगर (status != 0)
		वापस;

	/* set up the MCR रेजिस्टर and send it to the EdgePort */
	edge_port->shaकरोwMCR = MCR_MASTER_IE;
	अगर (cflag & CBAUD)
		edge_port->shaकरोwMCR |= (MCR_DTR | MCR_RTS);

	status = send_cmd_ग_लिखो_uart_रेजिस्टर(edge_port, MCR,
						edge_port->shaकरोwMCR);
	अगर (status != 0)
		वापस;

	/* Determine भागisor based on baud rate */
	baud = tty_get_baud_rate(tty);
	अगर (!baud) अणु
		/* pick a शेष, any शेष... */
		baud = 9600;
	पूर्ण

	dev_dbg(dev, "%s - baud rate = %d\n", __func__, baud);
	status = send_cmd_ग_लिखो_baud_rate(edge_port, baud);
	अगर (status == -1) अणु
		/* Speed change was not possible - put back the old speed */
		baud = tty_termios_baud_rate(old_termios);
		tty_encode_baud_rate(tty, baud, baud);
	पूर्ण
पूर्ण


/****************************************************************************
 * unicode_to_ascii
 *	Turns a string from Unicode पूर्णांकo ASCII.
 *	Doesn't करो a good job with any अक्षरacters that are outside the normal
 *	ASCII range, but it's only क्रम debugging...
 *	NOTE: expects the unicode in LE क्रमmat
 ****************************************************************************/
अटल व्योम unicode_to_ascii(अक्षर *string, पूर्णांक buflen,
					__le16 *unicode, पूर्णांक unicode_size)
अणु
	पूर्णांक i;

	अगर (buflen <= 0)	/* never happens, but... */
		वापस;
	--buflen;		/* space क्रम nul */

	क्रम (i = 0; i < unicode_size; i++) अणु
		अगर (i >= buflen)
			अवरोध;
		string[i] = (अक्षर)(le16_to_cpu(unicode[i]));
	पूर्ण
	string[i] = 0x00;
पूर्ण


/****************************************************************************
 * get_manufacturing_desc
 *	पढ़ोs in the manufacturing descriptor and stores it पूर्णांकo the serial
 *	काष्ठाure.
 ****************************************************************************/
अटल व्योम get_manufacturing_desc(काष्ठा edgeport_serial *edge_serial)
अणु
	काष्ठा device *dev = &edge_serial->serial->dev->dev;
	पूर्णांक response;

	dev_dbg(dev, "getting manufacturer descriptor\n");

	response = rom_पढ़ो(edge_serial->serial,
				(EDGE_MANUF_DESC_ADDR & 0xffff0000) >> 16,
				(__u16)(EDGE_MANUF_DESC_ADDR & 0x0000ffff),
				EDGE_MANUF_DESC_LEN,
				(__u8 *)(&edge_serial->manuf_descriptor));

	अगर (response < 0) अणु
		dev_err(dev, "error in getting manufacturer descriptor: %d\n",
				response);
	पूर्ण अन्यथा अणु
		अक्षर string[30];
		dev_dbg(dev, "**Manufacturer Descriptor\n");
		dev_dbg(dev, "  RomSize:        %dK\n",
			edge_serial->manuf_descriptor.RomSize);
		dev_dbg(dev, "  RamSize:        %dK\n",
			edge_serial->manuf_descriptor.RamSize);
		dev_dbg(dev, "  CpuRev:         %d\n",
			edge_serial->manuf_descriptor.CpuRev);
		dev_dbg(dev, "  BoardRev:       %d\n",
			edge_serial->manuf_descriptor.BoardRev);
		dev_dbg(dev, "  NumPorts:       %d\n",
			edge_serial->manuf_descriptor.NumPorts);
		dev_dbg(dev, "  DescDate:       %d/%d/%d\n",
			edge_serial->manuf_descriptor.DescDate[0],
			edge_serial->manuf_descriptor.DescDate[1],
			edge_serial->manuf_descriptor.DescDate[2]+1900);
		unicode_to_ascii(string, माप(string),
			edge_serial->manuf_descriptor.SerialNumber,
			edge_serial->manuf_descriptor.SerNumLength/2);
		dev_dbg(dev, "  SerialNumber: %s\n", string);
		unicode_to_ascii(string, माप(string),
			edge_serial->manuf_descriptor.AssemblyNumber,
			edge_serial->manuf_descriptor.AssemblyNumLength/2);
		dev_dbg(dev, "  AssemblyNumber: %s\n", string);
		unicode_to_ascii(string, माप(string),
		    edge_serial->manuf_descriptor.OemAssyNumber,
		    edge_serial->manuf_descriptor.OemAssyNumLength/2);
		dev_dbg(dev, "  OemAssyNumber:  %s\n", string);
		dev_dbg(dev, "  UartType:       %d\n",
			edge_serial->manuf_descriptor.UartType);
		dev_dbg(dev, "  IonPid:         %d\n",
			edge_serial->manuf_descriptor.IonPid);
		dev_dbg(dev, "  IonConfig:      %d\n",
			edge_serial->manuf_descriptor.IonConfig);
	पूर्ण
पूर्ण


/****************************************************************************
 * get_boot_desc
 *	पढ़ोs in the bootloader descriptor and stores it पूर्णांकo the serial
 *	काष्ठाure.
 ****************************************************************************/
अटल व्योम get_boot_desc(काष्ठा edgeport_serial *edge_serial)
अणु
	काष्ठा device *dev = &edge_serial->serial->dev->dev;
	पूर्णांक response;

	dev_dbg(dev, "getting boot descriptor\n");

	response = rom_पढ़ो(edge_serial->serial,
				(EDGE_BOOT_DESC_ADDR & 0xffff0000) >> 16,
				(__u16)(EDGE_BOOT_DESC_ADDR & 0x0000ffff),
				EDGE_BOOT_DESC_LEN,
				(__u8 *)(&edge_serial->boot_descriptor));

	अगर (response < 0) अणु
		dev_err(dev, "error in getting boot descriptor: %d\n",
				response);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "**Boot Descriptor:\n");
		dev_dbg(dev, "  BootCodeLength: %d\n",
			le16_to_cpu(edge_serial->boot_descriptor.BootCodeLength));
		dev_dbg(dev, "  MajorVersion:   %d\n",
			edge_serial->boot_descriptor.MajorVersion);
		dev_dbg(dev, "  MinorVersion:   %d\n",
			edge_serial->boot_descriptor.MinorVersion);
		dev_dbg(dev, "  BuildNumber:    %d\n",
			le16_to_cpu(edge_serial->boot_descriptor.BuildNumber));
		dev_dbg(dev, "  Capabilities:   0x%x\n",
		      le16_to_cpu(edge_serial->boot_descriptor.Capabilities));
		dev_dbg(dev, "  UConfig0:       %d\n",
			edge_serial->boot_descriptor.UConfig0);
		dev_dbg(dev, "  UConfig1:       %d\n",
			edge_serial->boot_descriptor.UConfig1);
	पूर्ण
पूर्ण


/****************************************************************************
 * load_application_firmware
 *	This is called to load the application firmware to the device
 ****************************************************************************/
अटल व्योम load_application_firmware(काष्ठा edgeport_serial *edge_serial)
अणु
	काष्ठा device *dev = &edge_serial->serial->dev->dev;
	स्थिर काष्ठा ihex_binrec *rec;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name;
	स्थिर अक्षर *fw_info;
	पूर्णांक response;
	__u32 Operaddr;
	__u16 build;

	चयन (edge_serial->product_info.iDownloadFile) अणु
		हाल EDGE_DOWNLOAD_खाता_I930:
			fw_info = "downloading firmware version (930)";
			fw_name	= "edgeport/down.fw";
			अवरोध;

		हाल EDGE_DOWNLOAD_खाता_80251:
			fw_info = "downloading firmware version (80251)";
			fw_name	= "edgeport/down2.fw";
			अवरोध;

		हाल EDGE_DOWNLOAD_खाता_NONE:
			dev_dbg(dev, "No download file specified, skipping download\n");
			वापस;

		शेष:
			वापस;
	पूर्ण

	response = request_ihex_firmware(&fw, fw_name,
				    &edge_serial->serial->dev->dev);
	अगर (response) अणु
		dev_err(dev, "Failed to load image \"%s\" err %d\n",
		       fw_name, response);
		वापस;
	पूर्ण

	rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
	build = (rec->data[2] << 8) | rec->data[3];

	dev_dbg(dev, "%s %d.%d.%d\n", fw_info, rec->data[0], rec->data[1], build);

	edge_serial->product_info.FirmwareMajorVersion = rec->data[0];
	edge_serial->product_info.FirmwareMinorVersion = rec->data[1];
	edge_serial->product_info.FirmwareBuildNumber = cpu_to_le16(build);

	क्रम (rec = ihex_next_binrec(rec); rec;
	     rec = ihex_next_binrec(rec)) अणु
		Operaddr = be32_to_cpu(rec->addr);
		response = sram_ग_लिखो(edge_serial->serial,
				     Operaddr >> 16,
				     Operaddr & 0xFFFF,
				     be16_to_cpu(rec->len),
				     &rec->data[0]);
		अगर (response < 0) अणु
			dev_err(&edge_serial->serial->dev->dev,
				"sram_write failed (%x, %x, %d)\n",
				Operaddr >> 16, Operaddr & 0xFFFF,
				be16_to_cpu(rec->len));
			अवरोध;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "sending exec_dl_code\n");
	response = usb_control_msg (edge_serial->serial->dev,
				    usb_sndctrlpipe(edge_serial->serial->dev, 0),
				    USB_REQUEST_ION_EXEC_DL_CODE,
				    0x40, 0x4000, 0x0001, शून्य, 0, 3000);

	release_firmware(fw);
पूर्ण


/****************************************************************************
 * edge_startup
 ****************************************************************************/
अटल पूर्णांक edge_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा edgeport_serial *edge_serial;
	काष्ठा usb_device *dev;
	काष्ठा device *ddev = &serial->dev->dev;
	पूर्णांक i;
	पूर्णांक response;
	bool पूर्णांकerrupt_in_found;
	bool bulk_in_found;
	bool bulk_out_found;
	अटल स्थिर __u32 descriptor[3] = अणु	EDGE_COMPATIBILITY_MASK0,
						EDGE_COMPATIBILITY_MASK1,
						EDGE_COMPATIBILITY_MASK2 पूर्ण;

	dev = serial->dev;

	/* create our निजी serial काष्ठाure */
	edge_serial = kzalloc(माप(काष्ठा edgeport_serial), GFP_KERNEL);
	अगर (!edge_serial)
		वापस -ENOMEM;

	spin_lock_init(&edge_serial->es_lock);
	edge_serial->serial = serial;
	usb_set_serial_data(serial, edge_serial);

	/* get the name क्रम the device from the device */
	i = usb_string(dev, dev->descriptor.iManufacturer,
	    &edge_serial->name[0], MAX_NAME_LEN+1);
	अगर (i < 0)
		i = 0;
	edge_serial->name[i++] = ' ';
	usb_string(dev, dev->descriptor.iProduct,
	    &edge_serial->name[i], MAX_NAME_LEN+2 - i);

	dev_info(&serial->dev->dev, "%s detected\n", edge_serial->name);

	/* Read the epic descriptor */
	अगर (get_epic_descriptor(edge_serial) < 0) अणु
		/* स_नकल descriptor to Supports काष्ठाures */
		स_नकल(&edge_serial->epic_descriptor.Supports, descriptor,
		       माप(काष्ठा edge_compatibility_bits));

		/* get the manufacturing descriptor क्रम this device */
		get_manufacturing_desc(edge_serial);

		/* get the boot descriptor */
		get_boot_desc(edge_serial);

		get_product_info(edge_serial);
	पूर्ण

	/* set the number of ports from the manufacturing description */
	/* serial->num_ports = serial->product_info.NumPorts; */
	अगर ((!edge_serial->is_epic) &&
	    (edge_serial->product_info.NumPorts != serial->num_ports)) अणु
		dev_warn(ddev,
			"Device Reported %d serial ports vs. core thinking we have %d ports, email greg@kroah.com this information.\n",
			 edge_serial->product_info.NumPorts,
			 serial->num_ports);
	पूर्ण

	dev_dbg(ddev, "%s - time 1 %ld\n", __func__, jअगरfies);

	/* If not an EPiC device */
	अगर (!edge_serial->is_epic) अणु
		/* now load the application firmware पूर्णांकo this device */
		load_application_firmware(edge_serial);

		dev_dbg(ddev, "%s - time 2 %ld\n", __func__, jअगरfies);

		/* Check current Edgeport EEPROM and update अगर necessary */
		update_edgeport_E2PROM(edge_serial);

		dev_dbg(ddev, "%s - time 3 %ld\n", __func__, jअगरfies);

		/* set the configuration to use #1 */
/*		dev_dbg(ddev, "set_configuration 1\n"); */
/*		usb_set_configuration (dev, 1); */
	पूर्ण
	dev_dbg(ddev, "  FirmwareMajorVersion  %d.%d.%d\n",
	    edge_serial->product_info.FirmwareMajorVersion,
	    edge_serial->product_info.FirmwareMinorVersion,
	    le16_to_cpu(edge_serial->product_info.FirmwareBuildNumber));

	/* we set up the poपूर्णांकers to the endpoपूर्णांकs in the edge_खोलो function,
	 * as the काष्ठाures aren't created yet. */

	response = 0;

	अगर (edge_serial->is_epic) अणु
		काष्ठा usb_host_पूर्णांकerface *alt;

		alt = serial->पूर्णांकerface->cur_altsetting;

		/* EPIC thing, set up our पूर्णांकerrupt polling now and our पढ़ो
		 * urb, so that the device knows it really is connected. */
		पूर्णांकerrupt_in_found = bulk_in_found = bulk_out_found = false;
		क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; ++i) अणु
			काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
			पूर्णांक buffer_size;

			endpoपूर्णांक = &alt->endpoपूर्णांक[i].desc;
			buffer_size = usb_endpoपूर्णांक_maxp(endpoपूर्णांक);
			अगर (!पूर्णांकerrupt_in_found &&
			    (usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))) अणु
				/* we found a पूर्णांकerrupt in endpoपूर्णांक */
				dev_dbg(ddev, "found interrupt in\n");

				/* not set up yet, so करो it now */
				edge_serial->पूर्णांकerrupt_पढ़ो_urb =
						usb_alloc_urb(0, GFP_KERNEL);
				अगर (!edge_serial->पूर्णांकerrupt_पढ़ो_urb) अणु
					response = -ENOMEM;
					अवरोध;
				पूर्ण

				edge_serial->पूर्णांकerrupt_in_buffer =
					kदो_स्मृति(buffer_size, GFP_KERNEL);
				अगर (!edge_serial->पूर्णांकerrupt_in_buffer) अणु
					response = -ENOMEM;
					अवरोध;
				पूर्ण
				edge_serial->पूर्णांकerrupt_in_endpoपूर्णांक =
						endpoपूर्णांक->bEndpoपूर्णांकAddress;

				/* set up our पूर्णांकerrupt urb */
				usb_fill_पूर्णांक_urb(
					edge_serial->पूर्णांकerrupt_पढ़ो_urb,
					dev,
					usb_rcvपूर्णांकpipe(dev,
						endpoपूर्णांक->bEndpoपूर्णांकAddress),
					edge_serial->पूर्णांकerrupt_in_buffer,
					buffer_size,
					edge_पूर्णांकerrupt_callback,
					edge_serial,
					endpoपूर्णांक->bInterval);

				पूर्णांकerrupt_in_found = true;
			पूर्ण

			अगर (!bulk_in_found &&
				(usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक))) अणु
				/* we found a bulk in endpoपूर्णांक */
				dev_dbg(ddev, "found bulk in\n");

				/* not set up yet, so करो it now */
				edge_serial->पढ़ो_urb =
						usb_alloc_urb(0, GFP_KERNEL);
				अगर (!edge_serial->पढ़ो_urb) अणु
					response = -ENOMEM;
					अवरोध;
				पूर्ण

				edge_serial->bulk_in_buffer =
					kदो_स्मृति(buffer_size, GFP_KERNEL);
				अगर (!edge_serial->bulk_in_buffer) अणु
					response = -ENOMEM;
					अवरोध;
				पूर्ण
				edge_serial->bulk_in_endpoपूर्णांक =
						endpoपूर्णांक->bEndpoपूर्णांकAddress;

				/* set up our bulk in urb */
				usb_fill_bulk_urb(edge_serial->पढ़ो_urb, dev,
					usb_rcvbulkpipe(dev,
						endpoपूर्णांक->bEndpoपूर्णांकAddress),
					edge_serial->bulk_in_buffer,
					usb_endpoपूर्णांक_maxp(endpoपूर्णांक),
					edge_bulk_in_callback,
					edge_serial);
				bulk_in_found = true;
			पूर्ण

			अगर (!bulk_out_found &&
			    (usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक))) अणु
				/* we found a bulk out endpoपूर्णांक */
				dev_dbg(ddev, "found bulk out\n");
				edge_serial->bulk_out_endpoपूर्णांक =
						endpoपूर्णांक->bEndpoपूर्णांकAddress;
				bulk_out_found = true;
			पूर्ण
		पूर्ण

		अगर (response || !पूर्णांकerrupt_in_found || !bulk_in_found ||
							!bulk_out_found) अणु
			अगर (!response) अणु
				dev_err(ddev, "expected endpoints not found\n");
				response = -ENODEV;
			पूर्ण

			जाओ error;
		पूर्ण

		/* start पूर्णांकerrupt पढ़ो क्रम this edgeport this पूर्णांकerrupt will
		 * जारी as दीर्घ as the edgeport is connected */
		response = usb_submit_urb(edge_serial->पूर्णांकerrupt_पढ़ो_urb,
								GFP_KERNEL);
		अगर (response) अणु
			dev_err(ddev, "%s - Error %d submitting control urb\n",
				__func__, response);

			जाओ error;
		पूर्ण
	पूर्ण
	वापस response;

error:
	usb_मुक्त_urb(edge_serial->पूर्णांकerrupt_पढ़ो_urb);
	kमुक्त(edge_serial->पूर्णांकerrupt_in_buffer);

	usb_मुक्त_urb(edge_serial->पढ़ो_urb);
	kमुक्त(edge_serial->bulk_in_buffer);

	kमुक्त(edge_serial);

	वापस response;
पूर्ण


/****************************************************************************
 * edge_disconnect
 *	This function is called whenever the device is हटाओd from the usb bus.
 ****************************************************************************/
अटल व्योम edge_disconnect(काष्ठा usb_serial *serial)
अणु
	काष्ठा edgeport_serial *edge_serial = usb_get_serial_data(serial);

	अगर (edge_serial->is_epic) अणु
		usb_समाप्त_urb(edge_serial->पूर्णांकerrupt_पढ़ो_urb);
		usb_समाप्त_urb(edge_serial->पढ़ो_urb);
	पूर्ण
पूर्ण


/****************************************************************************
 * edge_release
 *	This function is called when the device काष्ठाure is deallocated.
 ****************************************************************************/
अटल व्योम edge_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा edgeport_serial *edge_serial = usb_get_serial_data(serial);

	अगर (edge_serial->is_epic) अणु
		usb_समाप्त_urb(edge_serial->पूर्णांकerrupt_पढ़ो_urb);
		usb_मुक्त_urb(edge_serial->पूर्णांकerrupt_पढ़ो_urb);
		kमुक्त(edge_serial->पूर्णांकerrupt_in_buffer);

		usb_समाप्त_urb(edge_serial->पढ़ो_urb);
		usb_मुक्त_urb(edge_serial->पढ़ो_urb);
		kमुक्त(edge_serial->bulk_in_buffer);
	पूर्ण

	kमुक्त(edge_serial);
पूर्ण

अटल पूर्णांक edge_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_port *edge_port;

	edge_port = kzalloc(माप(*edge_port), GFP_KERNEL);
	अगर (!edge_port)
		वापस -ENOMEM;

	spin_lock_init(&edge_port->ep_lock);
	edge_port->port = port;

	usb_set_serial_port_data(port, edge_port);

	वापस 0;
पूर्ण

अटल व्योम edge_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा edgeport_port *edge_port;

	edge_port = usb_get_serial_port_data(port);
	kमुक्त(edge_port);
पूर्ण

अटल काष्ठा usb_serial_driver edgeport_2port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "edgeport_2",
	पूर्ण,
	.description		= "Edgeport 2 port adapter",
	.id_table		= edgeport_2port_id_table,
	.num_ports		= 2,
	.num_bulk_in		= 1,
	.num_bulk_out		= 1,
	.num_पूर्णांकerrupt_in	= 1,
	.खोलो			= edge_खोलो,
	.बंद			= edge_बंद,
	.throttle		= edge_throttle,
	.unthrottle		= edge_unthrottle,
	.attach			= edge_startup,
	.disconnect		= edge_disconnect,
	.release		= edge_release,
	.port_probe		= edge_port_probe,
	.port_हटाओ		= edge_port_हटाओ,
	.ioctl			= edge_ioctl,
	.set_termios		= edge_set_termios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.ग_लिखो			= edge_ग_लिखो,
	.ग_लिखो_room		= edge_ग_लिखो_room,
	.अक्षरs_in_buffer	= edge_अक्षरs_in_buffer,
	.अवरोध_ctl		= edge_अवरोध,
	.पढ़ो_पूर्णांक_callback	= edge_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= edge_bulk_in_callback,
	.ग_लिखो_bulk_callback	= edge_bulk_out_data_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver edgeport_4port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "edgeport_4",
	पूर्ण,
	.description		= "Edgeport 4 port adapter",
	.id_table		= edgeport_4port_id_table,
	.num_ports		= 4,
	.num_bulk_in		= 1,
	.num_bulk_out		= 1,
	.num_पूर्णांकerrupt_in	= 1,
	.खोलो			= edge_खोलो,
	.बंद			= edge_बंद,
	.throttle		= edge_throttle,
	.unthrottle		= edge_unthrottle,
	.attach			= edge_startup,
	.disconnect		= edge_disconnect,
	.release		= edge_release,
	.port_probe		= edge_port_probe,
	.port_हटाओ		= edge_port_हटाओ,
	.ioctl			= edge_ioctl,
	.set_termios		= edge_set_termios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.ग_लिखो			= edge_ग_लिखो,
	.ग_लिखो_room		= edge_ग_लिखो_room,
	.अक्षरs_in_buffer	= edge_अक्षरs_in_buffer,
	.अवरोध_ctl		= edge_अवरोध,
	.पढ़ो_पूर्णांक_callback	= edge_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= edge_bulk_in_callback,
	.ग_लिखो_bulk_callback	= edge_bulk_out_data_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver edgeport_8port_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "edgeport_8",
	पूर्ण,
	.description		= "Edgeport 8 port adapter",
	.id_table		= edgeport_8port_id_table,
	.num_ports		= 8,
	.num_bulk_in		= 1,
	.num_bulk_out		= 1,
	.num_पूर्णांकerrupt_in	= 1,
	.खोलो			= edge_खोलो,
	.बंद			= edge_बंद,
	.throttle		= edge_throttle,
	.unthrottle		= edge_unthrottle,
	.attach			= edge_startup,
	.disconnect		= edge_disconnect,
	.release		= edge_release,
	.port_probe		= edge_port_probe,
	.port_हटाओ		= edge_port_हटाओ,
	.ioctl			= edge_ioctl,
	.set_termios		= edge_set_termios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.ग_लिखो			= edge_ग_लिखो,
	.ग_लिखो_room		= edge_ग_लिखो_room,
	.अक्षरs_in_buffer	= edge_अक्षरs_in_buffer,
	.अवरोध_ctl		= edge_अवरोध,
	.पढ़ो_पूर्णांक_callback	= edge_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= edge_bulk_in_callback,
	.ग_लिखो_bulk_callback	= edge_bulk_out_data_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver epic_device = अणु
	.driver = अणु
		.owner		= THIS_MODULE,
		.name		= "epic",
	पूर्ण,
	.description		= "EPiC device",
	.id_table		= Epic_port_id_table,
	.num_ports		= 1,
	.num_bulk_in		= 1,
	.num_bulk_out		= 1,
	.num_पूर्णांकerrupt_in	= 1,
	.खोलो			= edge_खोलो,
	.बंद			= edge_बंद,
	.throttle		= edge_throttle,
	.unthrottle		= edge_unthrottle,
	.attach			= edge_startup,
	.disconnect		= edge_disconnect,
	.release		= edge_release,
	.port_probe		= edge_port_probe,
	.port_हटाओ		= edge_port_हटाओ,
	.ioctl			= edge_ioctl,
	.set_termios		= edge_set_termios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiरुको		= usb_serial_generic_tiocmiरुको,
	.get_icount		= usb_serial_generic_get_icount,
	.ग_लिखो			= edge_ग_लिखो,
	.ग_लिखो_room		= edge_ग_लिखो_room,
	.अक्षरs_in_buffer	= edge_अक्षरs_in_buffer,
	.अवरोध_ctl		= edge_अवरोध,
	.पढ़ो_पूर्णांक_callback	= edge_पूर्णांकerrupt_callback,
	.पढ़ो_bulk_callback	= edge_bulk_in_callback,
	.ग_लिखो_bulk_callback	= edge_bulk_out_data_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&edgeport_2port_device, &edgeport_4port_device,
	&edgeport_8port_device, &epic_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table_combined);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("edgeport/boot.fw");
MODULE_FIRMWARE("edgeport/boot2.fw");
MODULE_FIRMWARE("edgeport/down.fw");
MODULE_FIRMWARE("edgeport/down2.fw");
