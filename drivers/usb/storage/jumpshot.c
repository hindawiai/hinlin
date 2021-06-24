<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Lexar "Jumpshot" Compact Flash पढ़ोer
 *
 * jumpshot driver v0.1:
 *
 * First release
 *
 * Current development and मुख्यtenance by:
 *   (c) 2000 Jimmie Mayfield (mayfield+usb@sackheads.org)
 *
 *   Many thanks to Robert Baruch क्रम the SanDisk SmartMedia पढ़ोer driver
 *   which I used as a ढाँचा क्रम this driver.
 *
 *   Some bugfixes and scatter-gather code by Gregory P. Smith 
 *   (greg-usb@electricrain.com)
 *
 *   Fix क्रम media change by Joerg Schneider (js@joergschneider.com)
 *
 * Developed with the assistance of:
 *
 *   (C) 2002 Alan Stern <stern@rowland.org>
 */
 
 /*
  * This driver attempts to support the Lexar Jumpshot USB CompactFlash 
  * पढ़ोer.  Like many other USB CompactFlash पढ़ोers, the Jumpshot contains
  * a USB-to-ATA chip. 
  *
  * This driver supports पढ़ोing and writing.  If you're truly paranoid,
  * however, you can क्रमce the driver पूर्णांकo a ग_लिखो-रक्षित state by setting
  * the WP enable bits in jumpshot_handle_mode_sense.  See the comments
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

#घोषणा DRV_NAME "ums-jumpshot"

MODULE_DESCRIPTION("Driver for Lexar \"Jumpshot\" Compact Flash reader");
MODULE_AUTHOR("Jimmie Mayfield <mayfield+usb@sackheads.org>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id jumpshot_usb_ids[] = अणु
#	include "unusual_jumpshot.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, jumpshot_usb_ids);

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

अटल काष्ठा us_unusual_dev jumpshot_unusual_dev_list[] = अणु
#	include "unusual_jumpshot.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


काष्ठा jumpshot_info अणु
   अचिन्हित दीर्घ   sectors;     /* total sector count */
   अचिन्हित दीर्घ   ssize;       /* sector size in bytes */

   /* the following aren't used yet */
   अचिन्हित अक्षर   sense_key;
   अचिन्हित दीर्घ   sense_asc;   /* additional sense code */
   अचिन्हित दीर्घ   sense_ascq;  /* additional sense code qualअगरier */
पूर्ण;

अटल अंतरभूत पूर्णांक jumpshot_bulk_पढ़ो(काष्ठा us_data *us,
				     अचिन्हित अक्षर *data, 
				     अचिन्हित पूर्णांक len)
अणु
	अगर (len == 0)
		वापस USB_STOR_XFER_GOOD;

	usb_stor_dbg(us, "len = %d\n", len);
	वापस usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
			data, len, शून्य);
पूर्ण


अटल अंतरभूत पूर्णांक jumpshot_bulk_ग_लिखो(काष्ठा us_data *us,
				      अचिन्हित अक्षर *data, 
				      अचिन्हित पूर्णांक len)
अणु
	अगर (len == 0)
		वापस USB_STOR_XFER_GOOD;

	usb_stor_dbg(us, "len = %d\n", len);
	वापस usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
			data, len, शून्य);
पूर्ण


अटल पूर्णांक jumpshot_get_status(काष्ठा us_data  *us)
अणु
	पूर्णांक rc;

	अगर (!us)
		वापस USB_STOR_TRANSPORT_ERROR;

	// send the setup
	rc = usb_stor_ctrl_transfer(us, us->recv_ctrl_pipe,
				   0, 0xA0, 0, 7, us->iobuf, 1);

	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (us->iobuf[0] != 0x50) अणु
		usb_stor_dbg(us, "0x%2x\n", us->iobuf[0]);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक jumpshot_पढ़ो_data(काष्ठा us_data *us,
			      काष्ठा jumpshot_info *info,
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
	// we can support up to 28-bit addressing.  I करोn't know अगर Jumpshot
	// supports beyond 24-bit addressing.  It's kind of hard to test 
	// since it requires > 8GB CF card.

	अगर (sector > 0x0FFFFFFF)
		वापस USB_STOR_TRANSPORT_ERROR;

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
		command[3] = (sector >>  8) & 0xFF;
		command[4] = (sector >> 16) & 0xFF;

		command[5] = 0xE0 | ((sector >> 24) & 0x0F);
		command[6] = 0x20;

		// send the setup + command
		result = usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
					       0, 0x20, 0, 1, command, 7);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		// पढ़ो the result
		result = jumpshot_bulk_पढ़ो(us, buffer, len);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		usb_stor_dbg(us, "%d bytes\n", len);

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


अटल पूर्णांक jumpshot_ग_लिखो_data(काष्ठा us_data *us,
			       काष्ठा jumpshot_info *info,
			       u32 sector,
			       u32 sectors)
अणु
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *buffer;
	अचिन्हित अक्षर  thisसमय;
	अचिन्हित पूर्णांक totallen, alloclen;
	पूर्णांक len, result, रुकोcount;
	अचिन्हित पूर्णांक sg_offset = 0;
	काष्ठा scatterlist *sg = शून्य;

	// we're working in LBA mode.  according to the ATA spec, 
	// we can support up to 28-bit addressing.  I करोn't know अगर Jumpshot
	// supports beyond 24-bit addressing.  It's kind of hard to test 
	// since it requires > 8GB CF card.
	//
	अगर (sector > 0x0FFFFFFF)
		वापस USB_STOR_TRANSPORT_ERROR;

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
		command[3] = (sector >>  8) & 0xFF;
		command[4] = (sector >> 16) & 0xFF;

		command[5] = 0xE0 | ((sector >> 24) & 0x0F);
		command[6] = 0x30;

		// send the setup + command
		result = usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
			0, 0x20, 0, 1, command, 7);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		// send the data
		result = jumpshot_bulk_ग_लिखो(us, buffer, len);
		अगर (result != USB_STOR_XFER_GOOD)
			जाओ leave;

		// पढ़ो the result.  apparently the bulk ग_लिखो can complete
		// beक्रमe the jumpshot drive is finished writing.  so we loop
		// here until we get a good वापस code
		रुकोcount = 0;
		करो अणु
			result = jumpshot_get_status(us);
			अगर (result != USB_STOR_TRANSPORT_GOOD) अणु
				// I have not experimented to find the smallest value.
				//
				msleep(50); 
			पूर्ण
		पूर्ण जबतक ((result != USB_STOR_TRANSPORT_GOOD) && (रुकोcount < 10));

		अगर (result != USB_STOR_TRANSPORT_GOOD)
			usb_stor_dbg(us, "Gah!  Waitcount = 10.  Bad write!?\n");

		sector += thisसमय;
		totallen -= len;
	पूर्ण जबतक (totallen > 0);

	kमुक्त(buffer);
	वापस result;

 leave:
	kमुक्त(buffer);
	वापस USB_STOR_TRANSPORT_ERROR;
पूर्ण

अटल पूर्णांक jumpshot_id_device(काष्ठा us_data *us,
			      काष्ठा jumpshot_info *info)
अणु
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *reply;
	पूर्णांक 	 rc;

	अगर (!info)
		वापस USB_STOR_TRANSPORT_ERROR;

	command[0] = 0xE0;
	command[1] = 0xEC;
	reply = kदो_स्मृति(512, GFP_NOIO);
	अगर (!reply)
		वापस USB_STOR_TRANSPORT_ERROR;

	// send the setup
	rc = usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
				   0, 0x20, 0, 6, command, 2);

	अगर (rc != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Gah! send_control for read_capacity failed\n");
		rc = USB_STOR_TRANSPORT_ERROR;
		जाओ leave;
	पूर्ण

	// पढ़ो the reply
	rc = jumpshot_bulk_पढ़ो(us, reply, 512);
	अगर (rc != USB_STOR_XFER_GOOD) अणु
		rc = USB_STOR_TRANSPORT_ERROR;
		जाओ leave;
	पूर्ण

	info->sectors = ((u32)(reply[117]) << 24) |
			((u32)(reply[116]) << 16) |
			((u32)(reply[115]) <<  8) |
			((u32)(reply[114])      );

	rc = USB_STOR_TRANSPORT_GOOD;

 leave:
	kमुक्त(reply);
	वापस rc;
पूर्ण

अटल पूर्णांक jumpshot_handle_mode_sense(काष्ठा us_data *us,
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
	काष्ठा jumpshot_info *info = (काष्ठा jumpshot_info *) (us->extra);
	अचिन्हित अक्षर *ptr = us->iobuf;

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
	   हाल 0x0:
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

	   हाल 0x3F:
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


अटल व्योम jumpshot_info_deकाष्ठाor(व्योम *extra)
अणु
	// this routine is a placeholder...
	// currently, we करोn't allocate any extra blocks so we're okay
पूर्ण



// Transport क्रम the Lexar 'Jumpshot'
//
अटल पूर्णांक jumpshot_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	काष्ठा jumpshot_info *info;
	पूर्णांक rc;
	अचिन्हित दीर्घ block, blocks;
	अचिन्हित अक्षर *ptr = us->iobuf;
	अटल अचिन्हित अक्षर inquiry_response[8] = अणु
		0x00, 0x80, 0x00, 0x01, 0x1F, 0x00, 0x00, 0x00
	पूर्ण;

	अगर (!us->extra) अणु
		us->extra = kzalloc(माप(काष्ठा jumpshot_info), GFP_NOIO);
		अगर (!us->extra)
			वापस USB_STOR_TRANSPORT_ERROR;

		us->extra_deकाष्ठाor = jumpshot_info_deकाष्ठाor;
	पूर्ण

	info = (काष्ठा jumpshot_info *) (us->extra);

	अगर (srb->cmnd[0] == INQUIRY) अणु
		usb_stor_dbg(us, "INQUIRY - Returning bogus response\n");
		स_नकल(ptr, inquiry_response, माप(inquiry_response));
		fill_inquiry_response(us, ptr, 36);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == READ_CAPACITY) अणु
		info->ssize = 0x200;  // hard coded 512 byte sectors as per ATA spec

		rc = jumpshot_get_status(us);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		rc = jumpshot_id_device(us, info);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		usb_stor_dbg(us, "READ_CAPACITY:  %ld sectors, %ld bytes per sector\n",
			     info->sectors, info->ssize);

		// build the reply
		//
		((__be32 *) ptr)[0] = cpu_to_be32(info->sectors - 1);
		((__be32 *) ptr)[1] = cpu_to_be32(info->ssize);
		usb_stor_set_xfer_buf(ptr, 8, srb);

		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == MODE_SELECT_10) अणु
		usb_stor_dbg(us, "Gah! MODE_SELECT_10\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	अगर (srb->cmnd[0] == READ_10) अणु
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[7]) << 8) | ((u32)(srb->cmnd[8]));

		usb_stor_dbg(us, "READ_10: read block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस jumpshot_पढ़ो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == READ_12) अणु
		// I करोn't think we'll ever see a READ_12 but support it anyway...
		//
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[6]) << 24) | ((u32)(srb->cmnd[7]) << 16) |
			 ((u32)(srb->cmnd[8]) <<  8) | ((u32)(srb->cmnd[9]));

		usb_stor_dbg(us, "READ_12: read block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस jumpshot_पढ़ो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_10) अणु
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[7]) << 8) | ((u32)(srb->cmnd[8]));

		usb_stor_dbg(us, "WRITE_10: write block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस jumpshot_ग_लिखो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_12) अणु
		// I करोn't think we'll ever see a WRITE_12 but support it anyway...
		//
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
			((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[6]) << 24) | ((u32)(srb->cmnd[7]) << 16) |
			 ((u32)(srb->cmnd[8]) <<  8) | ((u32)(srb->cmnd[9]));

		usb_stor_dbg(us, "WRITE_12: write block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस jumpshot_ग_लिखो_data(us, info, block, blocks);
	पूर्ण


	अगर (srb->cmnd[0] == TEST_UNIT_READY) अणु
		usb_stor_dbg(us, "TEST_UNIT_READY\n");
		वापस jumpshot_get_status(us);
	पूर्ण

	अगर (srb->cmnd[0] == REQUEST_SENSE) अणु
		usb_stor_dbg(us, "REQUEST_SENSE\n");

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
		वापस jumpshot_handle_mode_sense(us, srb, 1);
	पूर्ण

	अगर (srb->cmnd[0] == MODE_SENSE_10) अणु
		usb_stor_dbg(us, "MODE_SENSE_10 detected\n");
		वापस jumpshot_handle_mode_sense(us, srb, 0);
	पूर्ण

	अगर (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL) अणु
		/*
		 * sure.  whatever.  not like we can stop the user from popping
		 * the media out of the device (no locking करोors, etc)
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
		 * the first jumpshot_id_device after a media change वापसs
		 * an error (determined experimentally)
		 */
		rc = jumpshot_id_device(us, info);
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

अटल काष्ठा scsi_host_ढाँचा jumpshot_host_ढाँचा;

अटल पूर्णांक jumpshot_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - jumpshot_usb_ids) + jumpshot_unusual_dev_list,
			&jumpshot_host_ढाँचा);
	अगर (result)
		वापस result;

	us->transport_name  = "Lexar Jumpshot Control/Bulk";
	us->transport = jumpshot_transport;
	us->transport_reset = usb_stor_Bulk_reset;
	us->max_lun = 1;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver jumpshot_driver = अणु
	.name =		DRV_NAME,
	.probe =	jumpshot_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	jumpshot_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(jumpshot_driver, jumpshot_host_ढाँचा, DRV_NAME);
