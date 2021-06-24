<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Freecom USB/IDE adaptor
 *
 * Freecom v0.1:
 *
 * First release
 *
 * Current development and मुख्यtenance by:
 *   (C) 2000 David Brown <usb-storage@davidb.org>
 *
 * This driver was developed with inक्रमmation provided in FREECOM's USB
 * Programmers Reference Guide.  For further inक्रमmation contact Freecom
 * (https://www.मुक्तcom.de/)
 */

#समावेश <linux/module.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-freecom"

MODULE_DESCRIPTION("Driver for Freecom USB/IDE adaptor");
MODULE_AUTHOR("David Brown <usb-storage@davidb.org>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

#अगर_घोषित CONFIG_USB_STORAGE_DEBUG
अटल व्योम pdump(काष्ठा us_data *us, व्योम *ibuffer, पूर्णांक length);
#पूर्ण_अगर

/* Bits of HD_STATUS */
#घोषणा ERR_STAT		0x01
#घोषणा DRQ_STAT		0x08

/* All of the outgoing packets are 64 bytes दीर्घ. */
काष्ठा मुक्तcom_cb_wrap अणु
	u8    Type;		/* Command type. */
	u8    Timeout;		/* Timeout in seconds. */
	u8    Atapi[12];	/* An ATAPI packet. */
	u8    Filler[50];	/* Padding Data. */
पूर्ण;

काष्ठा मुक्तcom_xfer_wrap अणु
	u8    Type;		/* Command type. */
	u8    Timeout;		/* Timeout in seconds. */
	__le32   Count;		/* Number of bytes to transfer. */
	u8    Pad[58];
पूर्ण __attribute__ ((packed));

काष्ठा मुक्तcom_ide_out अणु
	u8    Type;		/* Type + IDE रेजिस्टर. */
	u8    Pad;
	__le16   Value;		/* Value to ग_लिखो. */
	u8    Pad2[60];
पूर्ण;

काष्ठा मुक्तcom_ide_in अणु
	u8    Type;		/* Type | IDE रेजिस्टर. */
	u8    Pad[63];
पूर्ण;

काष्ठा मुक्तcom_status अणु
	u8    Status;
	u8    Reason;
	__le16   Count;
	u8    Pad[60];
पूर्ण;

/*
 * Freecom stuffs the पूर्णांकerrupt status in the INDEX_STAT bit of the ide
 * रेजिस्टर.
 */
#घोषणा FCM_INT_STATUS		0x02 /* INDEX_STAT */
#घोषणा FCM_STATUS_BUSY		0x80

/*
 * These are the packet types.  The low bit indicates that this command
 * should रुको क्रम an पूर्णांकerrupt.
 */
#घोषणा FCM_PACKET_ATAPI	0x21
#घोषणा FCM_PACKET_STATUS	0x20

/*
 * Receive data from the IDE पूर्णांकerface.  The ATAPI packet has alपढ़ोy
 * रुकोed, so the data should be immediately available.
 */
#घोषणा FCM_PACKET_INPUT	0x81

/* Send data to the IDE पूर्णांकerface. */
#घोषणा FCM_PACKET_OUTPUT	0x01

/*
 * Write a value to an ide रेजिस्टर.  Or the ide रेजिस्टर to ग_लिखो after
 * munging the address a bit.
 */
#घोषणा FCM_PACKET_IDE_WRITE	0x40
#घोषणा FCM_PACKET_IDE_READ	0xC0

/* All packets (except क्रम status) are 64 bytes दीर्घ. */
#घोषणा FCM_PACKET_LENGTH		64
#घोषणा FCM_STATUS_PACKET_LENGTH	4

अटल पूर्णांक init_मुक्तcom(काष्ठा us_data *us);


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id मुक्तcom_usb_ids[] = अणु
#	include "unusual_freecom.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, मुक्तcom_usb_ids);

#अघोषित UNUSUAL_DEV

/*
 * The flags table
 */
#घोषणा UNUSUAL_DEV(idVenकरोr, idProduct, bcdDeviceMin, bcdDeviceMax, \
		    venकरोr_name, product_name, use_protocol, use_transport, \
		    init_function, Flags) \
अणु \
	.venकरोrName = venकरोr_name,	\
	.productName = product_name,	\
	.useProtocol = use_protocol,	\
	.useTransport = use_transport,	\
	.initFunction = init_function,	\
पूर्ण

अटल काष्ठा us_unusual_dev मुक्तcom_unusual_dev_list[] = अणु
#	include "unusual_freecom.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV

अटल पूर्णांक
मुक्तcom_पढ़ोdata (काष्ठा scsi_cmnd *srb, काष्ठा us_data *us,
		अचिन्हित पूर्णांक ipipe, अचिन्हित पूर्णांक opipe, पूर्णांक count)
अणु
	काष्ठा मुक्तcom_xfer_wrap *fxfr =
		(काष्ठा मुक्तcom_xfer_wrap *) us->iobuf;
	पूर्णांक result;

	fxfr->Type = FCM_PACKET_INPUT | 0x00;
	fxfr->Timeout = 0;    /* Short समयout क्रम debugging. */
	fxfr->Count = cpu_to_le32 (count);
	स_रखो (fxfr->Pad, 0, माप (fxfr->Pad));

	usb_stor_dbg(us, "Read data Freecom! (c=%d)\n", count);

	/* Issue the transfer command. */
	result = usb_stor_bulk_transfer_buf (us, opipe, fxfr,
			FCM_PACKET_LENGTH, शून्य);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Freecom readdata transport error\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* Now transfer all of our blocks. */
	usb_stor_dbg(us, "Start of read\n");
	result = usb_stor_bulk_srb(us, ipipe, srb);
	usb_stor_dbg(us, "freecom_readdata done!\n");

	अगर (result > USB_STOR_XFER_SHORT)
		वापस USB_STOR_TRANSPORT_ERROR;
	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक
मुक्तcom_ग_लिखोdata (काष्ठा scsi_cmnd *srb, काष्ठा us_data *us,
		पूर्णांक अचिन्हित ipipe, अचिन्हित पूर्णांक opipe, पूर्णांक count)
अणु
	काष्ठा मुक्तcom_xfer_wrap *fxfr =
		(काष्ठा मुक्तcom_xfer_wrap *) us->iobuf;
	पूर्णांक result;

	fxfr->Type = FCM_PACKET_OUTPUT | 0x00;
	fxfr->Timeout = 0;    /* Short समयout क्रम debugging. */
	fxfr->Count = cpu_to_le32 (count);
	स_रखो (fxfr->Pad, 0, माप (fxfr->Pad));

	usb_stor_dbg(us, "Write data Freecom! (c=%d)\n", count);

	/* Issue the transfer command. */
	result = usb_stor_bulk_transfer_buf (us, opipe, fxfr,
			FCM_PACKET_LENGTH, शून्य);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Freecom writedata transport error\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* Now transfer all of our blocks. */
	usb_stor_dbg(us, "Start of write\n");
	result = usb_stor_bulk_srb(us, opipe, srb);

	usb_stor_dbg(us, "freecom_writedata done!\n");
	अगर (result > USB_STOR_XFER_SHORT)
		वापस USB_STOR_TRANSPORT_ERROR;
	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Transport क्रम the Freecom USB/IDE adaptor.
 *
 */
अटल पूर्णांक मुक्तcom_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	काष्ठा मुक्तcom_cb_wrap *fcb;
	काष्ठा मुक्तcom_status  *fst;
	अचिन्हित पूर्णांक ipipe, opipe;		/* We need both pipes. */
	पूर्णांक result;
	अचिन्हित पूर्णांक partial;
	पूर्णांक length;

	fcb = (काष्ठा मुक्तcom_cb_wrap *) us->iobuf;
	fst = (काष्ठा मुक्तcom_status *) us->iobuf;

	usb_stor_dbg(us, "Freecom TRANSPORT STARTED\n");

	/* Get handles क्रम both transports. */
	opipe = us->send_bulk_pipe;
	ipipe = us->recv_bulk_pipe;

	/* The ATAPI Command always goes out first. */
	fcb->Type = FCM_PACKET_ATAPI | 0x00;
	fcb->Timeout = 0;
	स_नकल (fcb->Atapi, srb->cmnd, 12);
	स_रखो (fcb->Filler, 0, माप (fcb->Filler));

	US_DEBUG(pdump(us, srb->cmnd, 12));

	/* Send it out. */
	result = usb_stor_bulk_transfer_buf (us, opipe, fcb,
			FCM_PACKET_LENGTH, शून्य);

	/*
	 * The Freecom device will only fail अगर there is something wrong in
	 * USB land.  It वापसs the status in its own रेजिस्टरs, which
	 * come back in the bulk pipe.
	 */
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "freecom transport error\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/*
	 * There are बार we can optimize out this status पढ़ो, but it
	 * करोesn't hurt us to always करो it now.
	 */
	result = usb_stor_bulk_transfer_buf (us, ipipe, fst,
			FCM_STATUS_PACKET_LENGTH, &partial);
	usb_stor_dbg(us, "foo Status result %d %u\n", result, partial);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	US_DEBUG(pdump(us, (व्योम *)fst, partial));

	/*
	 * The firmware will समय-out commands after 20 seconds. Some commands
	 * can legitimately take दीर्घer than this, so we use a dअगरferent
	 * command that only रुकोs क्रम the पूर्णांकerrupt and then sends status,
	 * without having to send a new ATAPI command to the device.
	 *
	 * NOTE: There is some indication that a data transfer after a समयout
	 * may not work, but that is a condition that should never happen.
	 */
	जबतक (fst->Status & FCM_STATUS_BUSY) अणु
		usb_stor_dbg(us, "20 second USB/ATAPI bridge TIMEOUT occurred!\n");
		usb_stor_dbg(us, "fst->Status is %x\n", fst->Status);

		/* Get the status again */
		fcb->Type = FCM_PACKET_STATUS;
		fcb->Timeout = 0;
		स_रखो (fcb->Atapi, 0, माप(fcb->Atapi));
		स_रखो (fcb->Filler, 0, माप (fcb->Filler));

		/* Send it out. */
		result = usb_stor_bulk_transfer_buf (us, opipe, fcb,
				FCM_PACKET_LENGTH, शून्य);

		/*
		 * The Freecom device will only fail अगर there is something
		 * wrong in USB land.  It वापसs the status in its own
		 * रेजिस्टरs, which come back in the bulk pipe.
		 */
		अगर (result != USB_STOR_XFER_GOOD) अणु
			usb_stor_dbg(us, "freecom transport error\n");
			वापस USB_STOR_TRANSPORT_ERROR;
		पूर्ण

		/* get the data */
		result = usb_stor_bulk_transfer_buf (us, ipipe, fst,
				FCM_STATUS_PACKET_LENGTH, &partial);

		usb_stor_dbg(us, "bar Status result %d %u\n", result, partial);
		अगर (result != USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		US_DEBUG(pdump(us, (व्योम *)fst, partial));
	पूर्ण

	अगर (partial != 4)
		वापस USB_STOR_TRANSPORT_ERROR;
	अगर ((fst->Status & 1) != 0) अणु
		usb_stor_dbg(us, "operation failed\n");
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	/*
	 * The device might not have as much data available as we
	 * requested.  If you ask क्रम more than the device has, this पढ़ोs
	 * and such will hang.
	 */
	usb_stor_dbg(us, "Device indicates that it has %d bytes available\n",
		     le16_to_cpu(fst->Count));
	usb_stor_dbg(us, "SCSI requested %d\n", scsi_bufflen(srb));

	/* Find the length we desire to पढ़ो. */
	चयन (srb->cmnd[0]) अणु
	हाल INQUIRY:
	हाल REQUEST_SENSE:	/* 16 or 18 bytes? spec says 18, lots of devices only have 16 */
	हाल MODE_SENSE:
	हाल MODE_SENSE_10:
		length = le16_to_cpu(fst->Count);
		अवरोध;
	शेष:
		length = scsi_bufflen(srb);
	पूर्ण

	/* verअगरy that this amount is legal */
	अगर (length > scsi_bufflen(srb)) अणु
		length = scsi_bufflen(srb);
		usb_stor_dbg(us, "Truncating request to match buffer length: %d\n",
			     length);
	पूर्ण

	/*
	 * What we करो now depends on what direction the data is supposed to
	 * move in.
	 */

	चयन (us->srb->sc_data_direction) अणु
	हाल DMA_FROM_DEVICE:
		/* catch bogus "read 0 length" हाल */
		अगर (!length)
			अवरोध;
		/*
		 * Make sure that the status indicates that the device
		 * wants data as well.
		 */
		अगर ((fst->Status & DRQ_STAT) == 0 || (fst->Reason & 3) != 2) अणु
			usb_stor_dbg(us, "SCSI wants data, drive doesn't have any\n");
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण
		result = मुक्तcom_पढ़ोdata (srb, us, ipipe, opipe, length);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			वापस result;

		usb_stor_dbg(us, "Waiting for status\n");
		result = usb_stor_bulk_transfer_buf (us, ipipe, fst,
				FCM_PACKET_LENGTH, &partial);
		US_DEBUG(pdump(us, (व्योम *)fst, partial));

		अगर (partial != 4 || result > USB_STOR_XFER_SHORT)
			वापस USB_STOR_TRANSPORT_ERROR;
		अगर ((fst->Status & ERR_STAT) != 0) अणु
			usb_stor_dbg(us, "operation failed\n");
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण
		अगर ((fst->Reason & 3) != 3) अणु
			usb_stor_dbg(us, "Drive seems still hungry\n");
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण
		usb_stor_dbg(us, "Transfer happy\n");
		अवरोध;

	हाल DMA_TO_DEVICE:
		/* catch bogus "write 0 length" हाल */
		अगर (!length)
			अवरोध;
		/*
		 * Make sure the status indicates that the device wants to
		 * send us data.
		 */
		/* !!IMPLEMENT!! */
		result = मुक्तcom_ग_लिखोdata (srb, us, ipipe, opipe, length);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			वापस result;

		usb_stor_dbg(us, "Waiting for status\n");
		result = usb_stor_bulk_transfer_buf (us, ipipe, fst,
				FCM_PACKET_LENGTH, &partial);

		अगर (partial != 4 || result > USB_STOR_XFER_SHORT)
			वापस USB_STOR_TRANSPORT_ERROR;
		अगर ((fst->Status & ERR_STAT) != 0) अणु
			usb_stor_dbg(us, "operation failed\n");
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण
		अगर ((fst->Reason & 3) != 3) अणु
			usb_stor_dbg(us, "Drive seems still hungry\n");
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण

		usb_stor_dbg(us, "Transfer happy\n");
		अवरोध;


	हाल DMA_NONE:
		/* Easy, करो nothing. */
		अवरोध;

	शेष:
		/* should never hit here -- filtered in usb.c */
		usb_stor_dbg(us, "freecom unimplemented direction: %d\n",
			     us->srb->sc_data_direction);
		/* Return fail, SCSI seems to handle this better. */
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक init_मुक्तcom(काष्ठा us_data *us)
अणु
	पूर्णांक result;
	अक्षर *buffer = us->iobuf;

	/*
	 * The DMA-mapped I/O buffer is 64 bytes दीर्घ, just right क्रम
	 * all our packets.  No need to allocate any extra buffer space.
	 */

	result = usb_stor_control_msg(us, us->recv_ctrl_pipe,
			0x4c, 0xc0, 0x4346, 0x0, buffer, 0x20, 3*HZ);
	buffer[32] = '\0';
	usb_stor_dbg(us, "String returned from FC init is: %s\n", buffer);

	/*
	 * Special thanks to the people at Freecom क्रम providing me with
	 * this "magic sequence", which they use in their Winकरोws and MacOS
	 * drivers to make sure that all the attached perhiperals are
	 * properly reset.
	 */

	/* send reset */
	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
			0x4d, 0x40, 0x24d8, 0x0, शून्य, 0x0, 3*HZ);
	usb_stor_dbg(us, "result from activate reset is %d\n", result);

	/* रुको 250ms */
	msleep(250);

	/* clear reset */
	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
			0x4d, 0x40, 0x24f8, 0x0, शून्य, 0x0, 3*HZ);
	usb_stor_dbg(us, "result from clear reset is %d\n", result);

	/* रुको 3 seconds */
	msleep(3 * 1000);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक usb_stor_मुक्तcom_reset(काष्ठा us_data *us)
अणु
	prपूर्णांकk (KERN_CRIT "freecom reset called\n");

	/* We करोn't really have this feature. */
	वापस FAILED;
पूर्ण

#अगर_घोषित CONFIG_USB_STORAGE_DEBUG
अटल व्योम pdump(काष्ठा us_data *us, व्योम *ibuffer, पूर्णांक length)
अणु
	अटल अक्षर line[80];
	पूर्णांक offset = 0;
	अचिन्हित अक्षर *buffer = (अचिन्हित अक्षर *) ibuffer;
	पूर्णांक i, j;
	पूर्णांक from, base;

	offset = 0;
	क्रम (i = 0; i < length; i++) अणु
		अगर ((i & 15) == 0) अणु
			अगर (i > 0) अणु
				offset += प्र_लिखो (line+offset, " - ");
				क्रम (j = i - 16; j < i; j++) अणु
					अगर (buffer[j] >= 32 && buffer[j] <= 126)
						line[offset++] = buffer[j];
					अन्यथा
						line[offset++] = '.';
				पूर्ण
				line[offset] = 0;
				usb_stor_dbg(us, "%s\n", line);
				offset = 0;
			पूर्ण
			offset += प्र_लिखो (line+offset, "%08x:", i);
		पूर्ण अन्यथा अगर ((i & 7) == 0) अणु
			offset += प्र_लिखो (line+offset, " -");
		पूर्ण
		offset += प्र_लिखो (line+offset, " %02x", buffer[i] & 0xff);
	पूर्ण

	/* Add the last "chunk" of data. */
	from = (length - 1) % 16;
	base = ((length - 1) / 16) * 16;

	क्रम (i = from + 1; i < 16; i++)
		offset += प्र_लिखो (line+offset, "   ");
	अगर (from < 8)
		offset += प्र_लिखो (line+offset, "  ");
	offset += प्र_लिखो (line+offset, " - ");

	क्रम (i = 0; i <= from; i++) अणु
		अगर (buffer[base+i] >= 32 && buffer[base+i] <= 126)
			line[offset++] = buffer[base+i];
		अन्यथा
			line[offset++] = '.';
	पूर्ण
	line[offset] = 0;
	usb_stor_dbg(us, "%s\n", line);
	offset = 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा मुक्तcom_host_ढाँचा;

अटल पूर्णांक मुक्तcom_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - मुक्तcom_usb_ids) + मुक्तcom_unusual_dev_list,
			&मुक्तcom_host_ढाँचा);
	अगर (result)
		वापस result;

	us->transport_name = "Freecom";
	us->transport = मुक्तcom_transport;
	us->transport_reset = usb_stor_मुक्तcom_reset;
	us->max_lun = 0;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver मुक्तcom_driver = अणु
	.name =		DRV_NAME,
	.probe =	मुक्तcom_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	मुक्तcom_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(मुक्तcom_driver, मुक्तcom_host_ढाँचा, DRV_NAME);
