<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Datafab USB Compact Flash पढ़ोer
 *
 * datafab driver v0.1:
 *
 * First release
 *
 * Current development and मुख्यtenance by:
 *   (c) 2000 Jimmie Mayfield (mayfield+datafab@sackheads.org)
 *
 *   Many thanks to Robert Baruch क्रम the SanDisk SmartMedia पढ़ोer driver
 *   which I used as a ढाँचा क्रम this driver.
 *
 *   Some bugfixes and scatter-gather code by Gregory P. Smith 
 *   (greg-usb@electricrain.com)
 *
 *   Fix क्रम media change by Joerg Schneider (js@joergschneider.com)
 *
 * Other contributors:
 *   (c) 2002 Alan Stern <stern@rowland.org>
 */

/*
 * This driver attempts to support USB CompactFlash पढ़ोer/ग_लिखोr devices
 * based on Datafab USB-to-ATA chips.  It was specअगरically developed क्रम the 
 * Datafab MDCFE-B USB CompactFlash पढ़ोer but has since been found to work 
 * with a variety of Datafab-based devices from a number of manufacturers.
 * I've received a report of this driver working with a Datafab-based
 * SmartMedia device though please be aware that I'm personally unable to
 * test SmartMedia support.
 *
 * This driver supports पढ़ोing and writing.  If you're truly paranoid,
 * however, you can क्रमce the driver पूर्णांकo a ग_लिखो-रक्षित state by setting
 * the WP enable bits in datafab_handle_mode_sense().  See the comments
 * in that routine.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-datafab"

MODULE_DESCRIPTION("Driver for Datafab USB Compact Flash reader");
MODULE_AUTHOR("Jimmie Mayfield <mayfield+datafab@sackheads.org>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

काष्ठा datafab_info अणु
	अचिन्हित दीर्घ   sectors;	/* total sector count */
	अचिन्हित दीर्घ   ssize;		/* sector size in bytes */
	चिन्हित अक्षर	lun;		/* used क्रम dual-slot पढ़ोers */

	/* the following aren't used yet */
	अचिन्हित अक्षर   sense_key;
	अचिन्हित दीर्घ   sense_asc;	/* additional sense code */
	अचिन्हित दीर्घ   sense_ascq;	/* additional sense code qualअगरier */
पूर्ण;

अटल पूर्णांक datafab_determine_lun(काष्ठा us_data *us,
				 काष्ठा datafab_info *info);


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id datafab_usb_ids[] = अणु
#	include "unusual_datafab.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, datafab_usb_ids);

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

अटल काष्ठा us_unusual_dev datafab_unusual_dev_list[] = अणु
#	include "unusual_datafab.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


अटल अंतरभूत पूर्णांक
datafab_bulk_पढ़ो(काष्ठा us_data *us, अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len) अणु
	अगर (len == 0)
		वापस USB_STOR_XFER_GOOD;

	usb_stor_dbg(us, "len = %d\n", len);
	वापस usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
			data, len, शून्य);
पूर्ण


अटल अंतरभूत पूर्णांक
datafab_bulk_ग_लिखो(काष्ठा us_data *us, अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len) अणु
	अगर (len == 0)
		वापस USB_STOR_XFER_GOOD;

	usb_stor_dbg(us, "len = %d\n", len);
	वापस usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
			data, len, शून्य);
पूर्ण


अटल पूर्णांक datafab_पढ़ो_data(काष्ठा us_data *us,
			     काष्ठा datafab_info *info,
			     u32 sector,
			     u32 sectors)
अणु
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *buffer;
	अचिन्हित अक्षर  thisसमय;
	अचिन्हित पूर्णांक totallen, alloclen;
	पूर्णांक len, result;
	अचिन्हित पूर्णांक sg_offset = 0;
	काष्ठा scatterlist *sg = शून्य;

	// we're working in LBA mode.  according to the ATA spec, 
	// we can support up to 28-bit addressing.  I करोn't know अगर Datafab
	// supports beyond 24-bit addressing.  It's kind of hard to test 
	// since it requires > 8GB CF card.
	//
	अगर (sectors > 0x0FFFFFFF)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (info->lun == -1) अणु
		result = datafab_determine_lun(us, info);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			वापस result;
	पूर्ण

	totallen = sectors * info->ssize;

	// Since we करोn't पढ़ो more than 64 KB at a समय, we have to create
	// a bounce buffer and move the data a piece at a समय between the
	// bounce buffer and the actual transfer buffer.

	alloclen = min(totallen, 65536u);
	buffer = kदो_स्मृति(alloclen, GFP_NOIO);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	करो अणु
		// loop, never allocate or transfer more than 64k at once
		// (min(128k, 255*info->ssize) is the real limit)

		len = min(totallen, alloclen);
		thisसमय = (len / info->ssize) & 0xff;

		command[0] = 0;
		command[1] = thisसमय;
		command[2] = sector & 0xFF;
		command[3] = (sector >> 8) & 0xFF;
		command[4] = (sector >> 16) & 0xFF;

		command[5] = 0xE0 + (info->lun << 4);
		command[5] |= (sector >> 24) & 0x0F;
		command[6] = 0x20;
		command[7] = 0x01;

		// send the पढ़ो command
		result = datafab_bulk_ग_लिखो(us, command, 8);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		// पढ़ो the result
		result = datafab_bulk_पढ़ो(us, buffer, len);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		// Store the data in the transfer buffer
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				 &sg, &sg_offset, TO_XFER_BUF);

		sector += thisसमय;
		totallen -= len;
	पूर्ण जबतक (totallen > 0);

	kमुक्त(buffer);
	वापस USB_STOR_TRANSPORT_GOOD;

 leave:
	kमुक्त(buffer);
	वापस USB_STOR_TRANSPORT_ERROR;
पूर्ण


अटल पूर्णांक datafab_ग_लिखो_data(काष्ठा us_data *us,
			      काष्ठा datafab_info *info,
			      u32 sector,
			      u32 sectors)
अणु
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *reply = us->iobuf;
	अचिन्हित अक्षर *buffer;
	अचिन्हित अक्षर thisसमय;
	अचिन्हित पूर्णांक totallen, alloclen;
	पूर्णांक len, result;
	अचिन्हित पूर्णांक sg_offset = 0;
	काष्ठा scatterlist *sg = शून्य;

	// we're working in LBA mode.  according to the ATA spec, 
	// we can support up to 28-bit addressing.  I करोn't know अगर Datafab
	// supports beyond 24-bit addressing.  It's kind of hard to test 
	// since it requires > 8GB CF card.
	//
	अगर (sectors > 0x0FFFFFFF)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (info->lun == -1) अणु
		result = datafab_determine_lun(us, info);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			वापस result;
	पूर्ण

	totallen = sectors * info->ssize;

	// Since we करोn't ग_लिखो more than 64 KB at a समय, we have to create
	// a bounce buffer and move the data a piece at a समय between the
	// bounce buffer and the actual transfer buffer.

	alloclen = min(totallen, 65536u);
	buffer = kदो_स्मृति(alloclen, GFP_NOIO);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	करो अणु
		// loop, never allocate or transfer more than 64k at once
		// (min(128k, 255*info->ssize) is the real limit)

		len = min(totallen, alloclen);
		thisसमय = (len / info->ssize) & 0xff;

		// Get the data from the transfer buffer
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &sg_offset, FROM_XFER_BUF);

		command[0] = 0;
		command[1] = thisसमय;
		command[2] = sector & 0xFF;
		command[3] = (sector >> 8) & 0xFF;
		command[4] = (sector >> 16) & 0xFF;

		command[5] = 0xE0 + (info->lun << 4);
		command[5] |= (sector >> 24) & 0x0F;
		command[6] = 0x30;
		command[7] = 0x02;

		// send the command
		result = datafab_bulk_ग_लिखो(us, command, 8);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		// send the data
		result = datafab_bulk_ग_लिखो(us, buffer, len);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		// पढ़ो the result
		result = datafab_bulk_पढ़ो(us, reply, 2);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		अगर (reply[0] != 0x50 && reply[1] != 0) अणु
			usb_stor_dbg(us, "Gah! write return code: %02x %02x\n",
				     reply[0], reply[1]);
			जाओ leave;
		पूर्ण

		sector += thisसमय;
		totallen -= len;
	पूर्ण जबतक (totallen > 0);

	kमुक्त(buffer);
	वापस USB_STOR_TRANSPORT_GOOD;

 leave:
	kमुक्त(buffer);
	वापस USB_STOR_TRANSPORT_ERROR;
पूर्ण


अटल पूर्णांक datafab_determine_lun(काष्ठा us_data *us,
				 काष्ठा datafab_info *info)
अणु
	// Dual-slot पढ़ोers can be thought of as dual-LUN devices.
	// We need to determine which card slot is being used.
	// We'll send an IDENTIFY DEVICE command and see which LUN responds...
	//
	// There might be a better way of करोing this?

	अटल अचिन्हित अक्षर scommand[8] = अणु 0, 1, 0, 0, 0, 0xa0, 0xec, 1 पूर्ण;
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *buf;
	पूर्णांक count = 0, rc;

	अगर (!info)
		वापस USB_STOR_TRANSPORT_ERROR;

	स_नकल(command, scommand, 8);
	buf = kदो_स्मृति(512, GFP_NOIO);
	अगर (!buf)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "locating...\n");

	// we'll try 3 बार beक्रमe giving up...
	//
	जबतक (count++ < 3) अणु
		command[5] = 0xa0;

		rc = datafab_bulk_ग_लिखो(us, command, 8);
		अगर (rc != USB_STOR_XFER_GOOD) अणु
			rc = USB_STOR_TRANSPORT_ERROR;
			जाओ leave;
		पूर्ण

		rc = datafab_bulk_पढ़ो(us, buf, 512);
		अगर (rc == USB_STOR_XFER_GOOD) अणु
			info->lun = 0;
			rc = USB_STOR_TRANSPORT_GOOD;
			जाओ leave;
		पूर्ण

		command[5] = 0xb0;

		rc = datafab_bulk_ग_लिखो(us, command, 8);
		अगर (rc != USB_STOR_XFER_GOOD) अणु
			rc = USB_STOR_TRANSPORT_ERROR;
			जाओ leave;
		पूर्ण

		rc = datafab_bulk_पढ़ो(us, buf, 512);
		अगर (rc == USB_STOR_XFER_GOOD) अणु
			info->lun = 1;
			rc = USB_STOR_TRANSPORT_GOOD;
			जाओ leave;
		पूर्ण

		msleep(20);
	पूर्ण

	rc = USB_STOR_TRANSPORT_ERROR;

 leave:
	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल पूर्णांक datafab_id_device(काष्ठा us_data *us,
			     काष्ठा datafab_info *info)
अणु
	// this is a variation of the ATA "IDENTIFY DEVICE" command...according
	// to the ATA spec, 'Sector Count' isn't used but the Winकरोws driver
	// sets this bit so we करो too...
	//
	अटल अचिन्हित अक्षर scommand[8] = अणु 0, 1, 0, 0, 0, 0xa0, 0xec, 1 पूर्ण;
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *reply;
	पूर्णांक rc;

	अगर (!info)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (info->lun == -1) अणु
		rc = datafab_determine_lun(us, info);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;
	पूर्ण

	स_नकल(command, scommand, 8);
	reply = kदो_स्मृति(512, GFP_NOIO);
	अगर (!reply)
		वापस USB_STOR_TRANSPORT_ERROR;

	command[5] += (info->lun << 4);

	rc = datafab_bulk_ग_लिखो(us, command, 8);
	अगर (rc != USB_STOR_XFER_GOOD) अणु
		rc = USB_STOR_TRANSPORT_ERROR;
		जाओ leave;
	पूर्ण

	// we'll go ahead and extract the media capacity while we're here...
	//
	rc = datafab_bulk_पढ़ो(us, reply, 512);
	अगर (rc == USB_STOR_XFER_GOOD) अणु
		// capacity is at word offset 57-58
		//
		info->sectors = ((u32)(reply[117]) << 24) | 
				((u32)(reply[116]) << 16) |
				((u32)(reply[115]) <<  8) | 
				((u32)(reply[114])      );
		rc = USB_STOR_TRANSPORT_GOOD;
		जाओ leave;
	पूर्ण

	rc = USB_STOR_TRANSPORT_ERROR;

 leave:
	kमुक्त(reply);
	वापस rc;
पूर्ण


अटल पूर्णांक datafab_handle_mode_sense(काष्ठा us_data *us,
				     काष्ठा scsi_cmnd * srb, 
				     पूर्णांक sense_6)
अणु
	अटल अचिन्हित अक्षर rw_err_page[12] = अणु
		0x1, 0xA, 0x21, 1, 0, 0, 0, 0, 1, 0, 0, 0
	पूर्ण;
	अटल अचिन्हित अक्षर cache_page[12] = अणु
		0x8, 0xA, 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0
	पूर्ण;
	अटल अचिन्हित अक्षर rbac_page[12] = अणु
		0x1B, 0xA, 0, 0x81, 0, 0, 0, 0, 0, 0, 0, 0
	पूर्ण;
	अटल अचिन्हित अक्षर समयr_page[8] = अणु
		0x1C, 0x6, 0, 0, 0, 0
	पूर्ण;
	अचिन्हित अक्षर pc, page_code;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा datafab_info *info = (काष्ठा datafab_info *) (us->extra);
	अचिन्हित अक्षर *ptr = us->iobuf;

	// most of this stuff is just a hack to get things working.  the
	// datafab पढ़ोer करोesn't present a SCSI पूर्णांकerface so we
	// fudge the SCSI commands...
	//

	pc = srb->cmnd[2] >> 6;
	page_code = srb->cmnd[2] & 0x3F;

	चयन (pc) अणु
	   हाल 0x0:
		   usb_stor_dbg(us, "Current values\n");
		अवरोध;
	   हाल 0x1:
		   usb_stor_dbg(us, "Changeable values\n");
		अवरोध;
	   हाल 0x2:
		   usb_stor_dbg(us, "Default values\n");
		अवरोध;
	   हाल 0x3:
		   usb_stor_dbg(us, "Saves values\n");
		अवरोध;
	पूर्ण

	स_रखो(ptr, 0, 8);
	अगर (sense_6) अणु
		ptr[2] = 0x00;		// WP enable: 0x80
		i = 4;
	पूर्ण अन्यथा अणु
		ptr[3] = 0x00;		// WP enable: 0x80
		i = 8;
	पूर्ण

	चयन (page_code) अणु
	   शेष:
		// venकरोr-specअगरic mode
		info->sense_key = 0x05;
		info->sense_asc = 0x24;
		info->sense_ascq = 0x00;
		वापस USB_STOR_TRANSPORT_FAILED;

	   हाल 0x1:
		स_नकल(ptr + i, rw_err_page, माप(rw_err_page));
		i += माप(rw_err_page);
		अवरोध;

	   हाल 0x8:
		स_नकल(ptr + i, cache_page, माप(cache_page));
		i += माप(cache_page);
		अवरोध;

	   हाल 0x1B:
		स_नकल(ptr + i, rbac_page, माप(rbac_page));
		i += माप(rbac_page);
		अवरोध;

	   हाल 0x1C:
		स_नकल(ptr + i, समयr_page, माप(समयr_page));
		i += माप(समयr_page);
		अवरोध;

	   हाल 0x3F:		// retrieve all pages
		स_नकल(ptr + i, समयr_page, माप(समयr_page));
		i += माप(समयr_page);
		स_नकल(ptr + i, rbac_page, माप(rbac_page));
		i += माप(rbac_page);
		स_नकल(ptr + i, cache_page, माप(cache_page));
		i += माप(cache_page);
		स_नकल(ptr + i, rw_err_page, माप(rw_err_page));
		i += माप(rw_err_page);
		अवरोध;
	पूर्ण

	अगर (sense_6)
		ptr[0] = i - 1;
	अन्यथा
		((__be16 *) ptr)[0] = cpu_to_be16(i - 2);
	usb_stor_set_xfer_buf(ptr, i, srb);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल व्योम datafab_info_deकाष्ठाor(व्योम *extra)
अणु
	// this routine is a placeholder...
	// currently, we करोn't allocate any extra memory so we're okay
पूर्ण


// Transport क्रम the Datafab MDCFE-B
//
अटल पूर्णांक datafab_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	काष्ठा datafab_info *info;
	पूर्णांक rc;
	अचिन्हित दीर्घ block, blocks;
	अचिन्हित अक्षर *ptr = us->iobuf;
	अटल अचिन्हित अक्षर inquiry_reply[8] = अणु
		0x00, 0x80, 0x00, 0x01, 0x1F, 0x00, 0x00, 0x00
	पूर्ण;

	अगर (!us->extra) अणु
		us->extra = kzalloc(माप(काष्ठा datafab_info), GFP_NOIO);
		अगर (!us->extra)
			वापस USB_STOR_TRANSPORT_ERROR;

		us->extra_deकाष्ठाor = datafab_info_deकाष्ठाor;
  		((काष्ठा datafab_info *)us->extra)->lun = -1;
	पूर्ण

	info = (काष्ठा datafab_info *) (us->extra);

	अगर (srb->cmnd[0] == INQUIRY) अणु
		usb_stor_dbg(us, "INQUIRY - Returning bogus response\n");
		स_नकल(ptr, inquiry_reply, माप(inquiry_reply));
		fill_inquiry_response(us, ptr, 36);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == READ_CAPACITY) अणु
		info->ssize = 0x200;  // hard coded 512 byte sectors as per ATA spec
		rc = datafab_id_device(us, info);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		usb_stor_dbg(us, "READ_CAPACITY:  %ld sectors, %ld bytes per sector\n",
			     info->sectors, info->ssize);

		// build the reply
		// we need the last sector, not the number of sectors
		((__be32 *) ptr)[0] = cpu_to_be32(info->sectors - 1);
		((__be32 *) ptr)[1] = cpu_to_be32(info->ssize);
		usb_stor_set_xfer_buf(ptr, 8, srb);

		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == MODE_SELECT_10) अणु
		usb_stor_dbg(us, "Gah! MODE_SELECT_10\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	// करोn't bother implementing READ_6 or WRITE_6.
	//
	अगर (srb->cmnd[0] == READ_10) अणु
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[7]) << 8) | ((u32)(srb->cmnd[8]));

		usb_stor_dbg(us, "READ_10: read block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस datafab_पढ़ो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == READ_12) अणु
		// we'll probably never see a READ_12 but we'll करो it anyway...
		//
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[6]) << 24) | ((u32)(srb->cmnd[7]) << 16) |
			 ((u32)(srb->cmnd[8]) <<  8) | ((u32)(srb->cmnd[9]));

		usb_stor_dbg(us, "READ_12: read block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस datafab_पढ़ो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_10) अणु
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[7]) << 8) | ((u32)(srb->cmnd[8]));

		usb_stor_dbg(us, "WRITE_10: write block 0x%04lx count %ld\n",
			     block, blocks);
		वापस datafab_ग_लिखो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_12) अणु
		// we'll probably never see a WRITE_12 but we'll करो it anyway...
		//
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[6]) << 24) | ((u32)(srb->cmnd[7]) << 16) |
			 ((u32)(srb->cmnd[8]) <<  8) | ((u32)(srb->cmnd[9]));

		usb_stor_dbg(us, "WRITE_12: write block 0x%04lx count %ld\n",
			     block, blocks);
		वापस datafab_ग_लिखो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == TEST_UNIT_READY) अणु
		usb_stor_dbg(us, "TEST_UNIT_READY\n");
		वापस datafab_id_device(us, info);
	पूर्ण

	अगर (srb->cmnd[0] == REQUEST_SENSE) अणु
		usb_stor_dbg(us, "REQUEST_SENSE - Returning faked response\n");

		// this response is pretty bogus right now.  eventually अगर necessary
		// we can set the correct sense data.  so far though it hasn't been
		// necessary
		//
		स_रखो(ptr, 0, 18);
		ptr[0] = 0xF0;
		ptr[2] = info->sense_key;
		ptr[7] = 11;
		ptr[12] = info->sense_asc;
		ptr[13] = info->sense_ascq;
		usb_stor_set_xfer_buf(ptr, 18, srb);

		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == MODE_SENSE) अणु
		usb_stor_dbg(us, "MODE_SENSE_6 detected\n");
		वापस datafab_handle_mode_sense(us, srb, 1);
	पूर्ण

	अगर (srb->cmnd[0] == MODE_SENSE_10) अणु
		usb_stor_dbg(us, "MODE_SENSE_10 detected\n");
		वापस datafab_handle_mode_sense(us, srb, 0);
	पूर्ण

	अगर (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL) अणु
		/*
		 * sure.  whatever.  not like we can stop the user from
		 * popping the media out of the device (no locking करोors, etc)
		 */
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == START_STOP) अणु
		/*
		 * this is used by sd.c'check_scsidisk_media_change to detect
		 * media change
		 */
		usb_stor_dbg(us, "START_STOP\n");
		/*
		 * the first datafab_id_device after a media change वापसs
		 * an error (determined experimentally)
		 */
		rc = datafab_id_device(us, info);
		अगर (rc == USB_STOR_TRANSPORT_GOOD) अणु
			info->sense_key = NO_SENSE;
			srb->result = SUCCESS;
		पूर्ण अन्यथा अणु
			info->sense_key = UNIT_ATTENTION;
			srb->result = SAM_STAT_CHECK_CONDITION;
		पूर्ण
		वापस rc;
	पूर्ण

	usb_stor_dbg(us, "Gah! Unknown command: %d (0x%x)\n",
		     srb->cmnd[0], srb->cmnd[0]);
	info->sense_key = 0x05;
	info->sense_asc = 0x20;
	info->sense_ascq = 0x00;
	वापस USB_STOR_TRANSPORT_FAILED;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा datafab_host_ढाँचा;

अटल पूर्णांक datafab_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - datafab_usb_ids) + datafab_unusual_dev_list,
			&datafab_host_ढाँचा);
	अगर (result)
		वापस result;

	us->transport_name  = "Datafab Bulk-Only";
	us->transport = datafab_transport;
	us->transport_reset = usb_stor_Bulk_reset;
	us->max_lun = 1;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver datafab_driver = अणु
	.name =		DRV_NAME,
	.probe =	datafab_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	datafab_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(datafab_driver, datafab_host_ढाँचा, DRV_NAME);
