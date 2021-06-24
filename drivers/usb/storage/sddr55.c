<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम SanDisk SDDR-55 SmartMedia पढ़ोer
 *
 * SDDR55 driver v0.1:
 *
 * First release
 *
 * Current development and मुख्यtenance by:
 *   (c) 2002 Simon Munton
 */

#समावेश <linux/jअगरfies.h>
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

#घोषणा DRV_NAME "ums-sddr55"

MODULE_DESCRIPTION("Driver for SanDisk SDDR-55 SmartMedia reader");
MODULE_AUTHOR("Simon Munton");
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

अटल काष्ठा usb_device_id sddr55_usb_ids[] = अणु
#	include "unusual_sddr55.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, sddr55_usb_ids);

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

अटल काष्ठा us_unusual_dev sddr55_unusual_dev_list[] = अणु
#	include "unusual_sddr55.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


#घोषणा लघु_pack(lsb,msb) ( ((u16)(lsb)) | ( ((u16)(msb))<<8 ) )
#घोषणा LSB_of(s) ((s)&0xFF)
#घोषणा MSB_of(s) ((s)>>8)
#घोषणा PAGESIZE  512

#घोषणा set_sense_info(sk, asc, ascq)	\
    करो अणु				\
	info->sense_data[2] = sk;	\
	info->sense_data[12] = asc;	\
	info->sense_data[13] = ascq;	\
	पूर्ण जबतक (0)


काष्ठा sddr55_card_info अणु
	अचिन्हित दीर्घ	capacity;	/* Size of card in bytes */
	पूर्णांक		max_log_blks;	/* maximum number of logical blocks */
	पूर्णांक		pageshअगरt;	/* log2 of pagesize */
	पूर्णांक		smallpageshअगरt;	/* 1 अगर pagesize == 256 */
	पूर्णांक		blocksize;	/* Size of block in pages */
	पूर्णांक		blockshअगरt;	/* log2 of blocksize */
	पूर्णांक		blockmask;	/* 2^blockshअगरt - 1 */
	पूर्णांक		पढ़ो_only;	/* non zero अगर card is ग_लिखो रक्षित */
	पूर्णांक		क्रमce_पढ़ो_only;	/* non zero अगर we find a map error*/
	पूर्णांक		*lba_to_pba;	/* logical to physical map */
	पूर्णांक		*pba_to_lba;	/* physical to logical map */
	पूर्णांक		fatal_error;	/* set अगर we detect something nasty */
	अचिन्हित दीर्घ 	last_access;	/* number of jअगरfies since we last talked to device */
	अचिन्हित अक्षर   sense_data[18];
पूर्ण;


#घोषणा NOT_ALLOCATED		0xffffffff
#घोषणा BAD_BLOCK		0xffff
#घोषणा CIS_BLOCK		0x400
#घोषणा UNUSED_BLOCK		0x3ff

अटल पूर्णांक
sddr55_bulk_transport(काष्ठा us_data *us, पूर्णांक direction,
		      अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len) अणु
	काष्ठा sddr55_card_info *info = (काष्ठा sddr55_card_info *)us->extra;
	अचिन्हित पूर्णांक pipe = (direction == DMA_FROM_DEVICE) ?
			us->recv_bulk_pipe : us->send_bulk_pipe;

	अगर (!len)
		वापस USB_STOR_XFER_GOOD;
	info->last_access = jअगरfies;
	वापस usb_stor_bulk_transfer_buf(us, pipe, data, len, शून्य);
पूर्ण

/*
 * check अगर card inserted, अगर there is, update पढ़ो_only status
 * वापस non zero अगर no card
 */

अटल पूर्णांक sddr55_status(काष्ठा us_data *us)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *status = us->iobuf;
	काष्ठा sddr55_card_info *info = (काष्ठा sddr55_card_info *)us->extra;

	/* send command */
	स_रखो(command, 0, 8);
	command[5] = 0xB0;
	command[7] = 0x80;
	result = sddr55_bulk_transport(us,
		DMA_TO_DEVICE, command, 8);

	usb_stor_dbg(us, "Result for send_command in status %d\n", result);

	अगर (result != USB_STOR_XFER_GOOD) अणु
		set_sense_info (4, 0, 0);	/* hardware error */
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	result = sddr55_bulk_transport(us,
		DMA_FROM_DEVICE, status,	4);

	/* expect to get लघु transfer अगर no card fitted */
	अगर (result == USB_STOR_XFER_SHORT || result == USB_STOR_XFER_STALLED) अणु
		/* had a लघु transfer, no card inserted, मुक्त map memory */
		kमुक्त(info->lba_to_pba);
		kमुक्त(info->pba_to_lba);
		info->lba_to_pba = शून्य;
		info->pba_to_lba = शून्य;

		info->fatal_error = 0;
		info->क्रमce_पढ़ो_only = 0;

		set_sense_info (2, 0x3a, 0);	/* not पढ़ोy, medium not present */
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	अगर (result != USB_STOR_XFER_GOOD) अणु
		set_sense_info (4, 0, 0);	/* hardware error */
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण
	
	/* check ग_लिखो protect status */
	info->पढ़ो_only = (status[0] & 0x20);

	/* now पढ़ो status */
	result = sddr55_bulk_transport(us,
		DMA_FROM_DEVICE, status,	2);

	अगर (result != USB_STOR_XFER_GOOD) अणु
		set_sense_info (4, 0, 0);	/* hardware error */
	पूर्ण

	वापस (result == USB_STOR_XFER_GOOD ?
			USB_STOR_TRANSPORT_GOOD : USB_STOR_TRANSPORT_FAILED);
पूर्ण


अटल पूर्णांक sddr55_पढ़ो_data(काष्ठा us_data *us,
		अचिन्हित पूर्णांक lba,
		अचिन्हित पूर्णांक page,
		अचिन्हित लघु sectors) अणु

	पूर्णांक result = USB_STOR_TRANSPORT_GOOD;
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *status = us->iobuf;
	काष्ठा sddr55_card_info *info = (काष्ठा sddr55_card_info *)us->extra;
	अचिन्हित अक्षर *buffer;

	अचिन्हित पूर्णांक pba;
	अचिन्हित दीर्घ address;

	अचिन्हित लघु pages;
	अचिन्हित पूर्णांक len, offset;
	काष्ठा scatterlist *sg;

	// Since we only पढ़ो in one block at a समय, we have to create
	// a bounce buffer and move the data a piece at a समय between the
	// bounce buffer and the actual transfer buffer.

	len = min((अचिन्हित पूर्णांक) sectors, (अचिन्हित पूर्णांक) info->blocksize >>
			info->smallpageshअगरt) * PAGESIZE;
	buffer = kदो_स्मृति(len, GFP_NOIO);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR; /* out of memory */
	offset = 0;
	sg = शून्य;

	जबतक (sectors>0) अणु

		/* have we got to end? */
		अगर (lba >= info->max_log_blks)
			अवरोध;

		pba = info->lba_to_pba[lba];

		// Read as many sectors as possible in this block

		pages = min((अचिन्हित पूर्णांक) sectors << info->smallpageshअगरt,
				info->blocksize - page);
		len = pages << info->pageshअगरt;

		usb_stor_dbg(us, "Read %02X pages, from PBA %04X (LBA %04X) page %02X\n",
			     pages, pba, lba, page);

		अगर (pba == NOT_ALLOCATED) अणु
			/* no pba क्रम this lba, fill with zeroes */
			स_रखो (buffer, 0, len);
		पूर्ण अन्यथा अणु

			address = (pba << info->blockshअगरt) + page;

			command[0] = 0;
			command[1] = LSB_of(address>>16);
			command[2] = LSB_of(address>>8);
			command[3] = LSB_of(address);

			command[4] = 0;
			command[5] = 0xB0;
			command[6] = LSB_of(pages << (1 - info->smallpageshअगरt));
			command[7] = 0x85;

			/* send command */
			result = sddr55_bulk_transport(us,
				DMA_TO_DEVICE, command, 8);

			usb_stor_dbg(us, "Result for send_command in read_data %d\n",
				     result);

			अगर (result != USB_STOR_XFER_GOOD) अणु
				result = USB_STOR_TRANSPORT_ERROR;
				जाओ leave;
			पूर्ण

			/* पढ़ो data */
			result = sddr55_bulk_transport(us,
				DMA_FROM_DEVICE, buffer, len);

			अगर (result != USB_STOR_XFER_GOOD) अणु
				result = USB_STOR_TRANSPORT_ERROR;
				जाओ leave;
			पूर्ण

			/* now पढ़ो status */
			result = sddr55_bulk_transport(us,
				DMA_FROM_DEVICE, status, 2);

			अगर (result != USB_STOR_XFER_GOOD) अणु
				result = USB_STOR_TRANSPORT_ERROR;
				जाओ leave;
			पूर्ण

			/* check status क्रम error */
			अगर (status[0] == 0xff && status[1] == 0x4) अणु
				set_sense_info (3, 0x11, 0);
				result = USB_STOR_TRANSPORT_FAILED;
				जाओ leave;
			पूर्ण
		पूर्ण

		// Store the data in the transfer buffer
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, TO_XFER_BUF);

		page = 0;
		lba++;
		sectors -= pages >> info->smallpageshअगरt;
	पूर्ण

	result = USB_STOR_TRANSPORT_GOOD;

leave:
	kमुक्त(buffer);

	वापस result;
पूर्ण

अटल पूर्णांक sddr55_ग_लिखो_data(काष्ठा us_data *us,
		अचिन्हित पूर्णांक lba,
		अचिन्हित पूर्णांक page,
		अचिन्हित लघु sectors) अणु

	पूर्णांक result = USB_STOR_TRANSPORT_GOOD;
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *status = us->iobuf;
	काष्ठा sddr55_card_info *info = (काष्ठा sddr55_card_info *)us->extra;
	अचिन्हित अक्षर *buffer;

	अचिन्हित पूर्णांक pba;
	अचिन्हित पूर्णांक new_pba;
	अचिन्हित दीर्घ address;

	अचिन्हित लघु pages;
	पूर्णांक i;
	अचिन्हित पूर्णांक len, offset;
	काष्ठा scatterlist *sg;

	/* check अगर we are allowed to ग_लिखो */
	अगर (info->पढ़ो_only || info->क्रमce_पढ़ो_only) अणु
		set_sense_info (7, 0x27, 0);	/* पढ़ो only */
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	// Since we only ग_लिखो one block at a समय, we have to create
	// a bounce buffer and move the data a piece at a समय between the
	// bounce buffer and the actual transfer buffer.

	len = min((अचिन्हित पूर्णांक) sectors, (अचिन्हित पूर्णांक) info->blocksize >>
			info->smallpageshअगरt) * PAGESIZE;
	buffer = kदो_स्मृति(len, GFP_NOIO);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;
	offset = 0;
	sg = शून्य;

	जबतक (sectors > 0) अणु

		/* have we got to end? */
		अगर (lba >= info->max_log_blks)
			अवरोध;

		pba = info->lba_to_pba[lba];

		// Write as many sectors as possible in this block

		pages = min((अचिन्हित पूर्णांक) sectors << info->smallpageshअगरt,
				info->blocksize - page);
		len = pages << info->pageshअगरt;

		// Get the data from the transfer buffer
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, FROM_XFER_BUF);

		usb_stor_dbg(us, "Write %02X pages, to PBA %04X (LBA %04X) page %02X\n",
			     pages, pba, lba, page);
			
		command[4] = 0;

		अगर (pba == NOT_ALLOCATED) अणु
			/* no pba allocated क्रम this lba, find a मुक्त pba to use */

			पूर्णांक max_pba = (info->max_log_blks / 250 ) * 256;
			पूर्णांक found_count = 0;
			पूर्णांक found_pba = -1;

			/* set pba to first block in zone lba is in */
			pba = (lba / 1000) * 1024;

			usb_stor_dbg(us, "No PBA for LBA %04X\n", lba);

			अगर (max_pba > 1024)
				max_pba = 1024;

			/*
			 * Scan through the map looking क्रम an unused block
			 * leave 16 unused blocks at start (or as many as
			 * possible) since the sddr55 seems to reuse a used
			 * block when it shouldn't if we don't leave space.
			 */
			क्रम (i = 0; i < max_pba; i++, pba++) अणु
				अगर (info->pba_to_lba[pba] == UNUSED_BLOCK) अणु
					found_pba = pba;
					अगर (found_count++ > 16)
						अवरोध;
				पूर्ण
			पूर्ण

			pba = found_pba;

			अगर (pba == -1) अणु
				/* oh dear */
				usb_stor_dbg(us, "Couldn't find unallocated block\n");

				set_sense_info (3, 0x31, 0);	/* medium error */
				result = USB_STOR_TRANSPORT_FAILED;
				जाओ leave;
			पूर्ण

			usb_stor_dbg(us, "Allocating PBA %04X for LBA %04X\n",
				     pba, lba);

			/* set writing to unallocated block flag */
			command[4] = 0x40;
		पूर्ण

		address = (pba << info->blockshअगरt) + page;

		command[1] = LSB_of(address>>16);
		command[2] = LSB_of(address>>8); 
		command[3] = LSB_of(address);

		/* set the lba पूर्णांकo the command, modulo 1000 */
		command[0] = LSB_of(lba % 1000);
		command[6] = MSB_of(lba % 1000);

		command[4] |= LSB_of(pages >> info->smallpageshअगरt);
		command[5] = 0xB0;
		command[7] = 0x86;

		/* send command */
		result = sddr55_bulk_transport(us,
			DMA_TO_DEVICE, command, 8);

		अगर (result != USB_STOR_XFER_GOOD) अणु
			usb_stor_dbg(us, "Result for send_command in write_data %d\n",
				     result);

			/* set_sense_info is superfluous here? */
			set_sense_info (3, 0x3, 0);/* peripheral ग_लिखो error */
			result = USB_STOR_TRANSPORT_FAILED;
			जाओ leave;
		पूर्ण

		/* send the data */
		result = sddr55_bulk_transport(us,
			DMA_TO_DEVICE, buffer, len);

		अगर (result != USB_STOR_XFER_GOOD) अणु
			usb_stor_dbg(us, "Result for send_data in write_data %d\n",
				     result);

			/* set_sense_info is superfluous here? */
			set_sense_info (3, 0x3, 0);/* peripheral ग_लिखो error */
			result = USB_STOR_TRANSPORT_FAILED;
			जाओ leave;
		पूर्ण

		/* now पढ़ो status */
		result = sddr55_bulk_transport(us, DMA_FROM_DEVICE, status, 6);

		अगर (result != USB_STOR_XFER_GOOD) अणु
			usb_stor_dbg(us, "Result for get_status in write_data %d\n",
				     result);

			/* set_sense_info is superfluous here? */
			set_sense_info (3, 0x3, 0);/* peripheral ग_लिखो error */
			result = USB_STOR_TRANSPORT_FAILED;
			जाओ leave;
		पूर्ण

		new_pba = (status[3] + (status[4] << 8) + (status[5] << 16))
						  >> info->blockshअगरt;

		/* check status क्रम error */
		अगर (status[0] == 0xff && status[1] == 0x4) अणु
			info->pba_to_lba[new_pba] = BAD_BLOCK;

			set_sense_info (3, 0x0c, 0);
			result = USB_STOR_TRANSPORT_FAILED;
			जाओ leave;
		पूर्ण

		usb_stor_dbg(us, "Updating maps for LBA %04X: old PBA %04X, new PBA %04X\n",
			     lba, pba, new_pba);

		/* update the lba<->pba maps, note new_pba might be the same as pba */
		info->lba_to_pba[lba] = new_pba;
		info->pba_to_lba[pba] = UNUSED_BLOCK;

		/* check that new_pba wasn't alपढ़ोy being used */
		अगर (info->pba_to_lba[new_pba] != UNUSED_BLOCK) अणु
			prपूर्णांकk(KERN_ERR "sddr55 error: new PBA %04X already in use for LBA %04X\n",
				new_pba, info->pba_to_lba[new_pba]);
			info->fatal_error = 1;
			set_sense_info (3, 0x31, 0);
			result = USB_STOR_TRANSPORT_FAILED;
			जाओ leave;
		पूर्ण

		/* update the pba<->lba maps क्रम new_pba */
		info->pba_to_lba[new_pba] = lba % 1000;

		page = 0;
		lba++;
		sectors -= pages >> info->smallpageshअगरt;
	पूर्ण
	result = USB_STOR_TRANSPORT_GOOD;

 leave:
	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल पूर्णांक sddr55_पढ़ो_deviceID(काष्ठा us_data *us,
		अचिन्हित अक्षर *manufacturerID,
		अचिन्हित अक्षर *deviceID) अणु

	पूर्णांक result;
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *content = us->iobuf;

	स_रखो(command, 0, 8);
	command[5] = 0xB0;
	command[7] = 0x84;
	result = sddr55_bulk_transport(us, DMA_TO_DEVICE, command, 8);

	usb_stor_dbg(us, "Result of send_control for device ID is %d\n",
		     result);

	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	result = sddr55_bulk_transport(us,
		DMA_FROM_DEVICE, content, 4);

	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	*manufacturerID = content[0];
	*deviceID = content[1];

	अगर (content[0] != 0xff)	अणु
    		result = sddr55_bulk_transport(us,
			DMA_FROM_DEVICE, content, 2);
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण


अटल पूर्णांक sddr55_reset(काष्ठा us_data *us)
अणु
	वापस 0;
पूर्ण


अटल अचिन्हित दीर्घ sddr55_get_capacity(काष्ठा us_data *us) अणु

	अचिन्हित अक्षर manufacturerID;
	अचिन्हित अक्षर deviceID;
	पूर्णांक result;
	काष्ठा sddr55_card_info *info = (काष्ठा sddr55_card_info *)us->extra;

	usb_stor_dbg(us, "Reading capacity...\n");

	result = sddr55_पढ़ो_deviceID(us,
		&manufacturerID,
		&deviceID);

	usb_stor_dbg(us, "Result of read_deviceID is %d\n", result);

	अगर (result != USB_STOR_XFER_GOOD)
		वापस 0;

	usb_stor_dbg(us, "Device ID = %02X\n", deviceID);
	usb_stor_dbg(us, "Manuf  ID = %02X\n", manufacturerID);

	info->pageshअगरt = 9;
	info->smallpageshअगरt = 0;
	info->blocksize = 16;
	info->blockshअगरt = 4;
	info->blockmask = 15;

	चयन (deviceID) अणु

	हाल 0x6e: // 1MB
	हाल 0xe8:
	हाल 0xec:
		info->pageshअगरt = 8;
		info->smallpageshअगरt = 1;
		वापस 0x00100000;

	हाल 0xea: // 2MB
	हाल 0x64:
		info->pageshअगरt = 8;
		info->smallpageshअगरt = 1;
		fallthrough;
	हाल 0x5d: // 5d is a ROM card with pagesize 512.
		वापस 0x00200000;

	हाल 0xe3: // 4MB
	हाल 0xe5:
	हाल 0x6b:
	हाल 0xd5:
		वापस 0x00400000;

	हाल 0xe6: // 8MB
	हाल 0xd6:
		वापस 0x00800000;

	हाल 0x73: // 16MB
		info->blocksize = 32;
		info->blockshअगरt = 5;
		info->blockmask = 31;
		वापस 0x01000000;

	हाल 0x75: // 32MB
		info->blocksize = 32;
		info->blockshअगरt = 5;
		info->blockmask = 31;
		वापस 0x02000000;

	हाल 0x76: // 64MB
		info->blocksize = 32;
		info->blockshअगरt = 5;
		info->blockmask = 31;
		वापस 0x04000000;

	हाल 0x79: // 128MB
		info->blocksize = 32;
		info->blockshअगरt = 5;
		info->blockmask = 31;
		वापस 0x08000000;

	शेष: // unknown
		वापस 0;

	पूर्ण
पूर्ण

अटल पूर्णांक sddr55_पढ़ो_map(काष्ठा us_data *us) अणु

	काष्ठा sddr55_card_info *info = (काष्ठा sddr55_card_info *)(us->extra);
	पूर्णांक numblocks;
	अचिन्हित अक्षर *buffer;
	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक i;
	अचिन्हित लघु lba;
	अचिन्हित लघु max_lba;
	पूर्णांक result;

	अगर (!info->capacity)
		वापस -1;

	numblocks = info->capacity >> (info->blockshअगरt + info->pageshअगरt);
	
	buffer = kदो_स्मृति_array(numblocks, 2, GFP_NOIO );
	
	अगर (!buffer)
		वापस -1;

	स_रखो(command, 0, 8);
	command[5] = 0xB0;
	command[6] = numblocks * 2 / 256;
	command[7] = 0x8A;

	result = sddr55_bulk_transport(us, DMA_TO_DEVICE, command, 8);

	अगर ( result != USB_STOR_XFER_GOOD) अणु
		kमुक्त (buffer);
		वापस -1;
	पूर्ण

	result = sddr55_bulk_transport(us, DMA_FROM_DEVICE, buffer, numblocks * 2);

	अगर ( result != USB_STOR_XFER_GOOD) अणु
		kमुक्त (buffer);
		वापस -1;
	पूर्ण

	result = sddr55_bulk_transport(us, DMA_FROM_DEVICE, command, 2);

	अगर ( result != USB_STOR_XFER_GOOD) अणु
		kमुक्त (buffer);
		वापस -1;
	पूर्ण

	kमुक्त(info->lba_to_pba);
	kमुक्त(info->pba_to_lba);
	info->lba_to_pba = kदो_स्मृति_array(numblocks, माप(पूर्णांक), GFP_NOIO);
	info->pba_to_lba = kदो_स्मृति_array(numblocks, माप(पूर्णांक), GFP_NOIO);

	अगर (info->lba_to_pba == शून्य || info->pba_to_lba == शून्य) अणु
		kमुक्त(info->lba_to_pba);
		kमुक्त(info->pba_to_lba);
		info->lba_to_pba = शून्य;
		info->pba_to_lba = शून्य;
		kमुक्त(buffer);
		वापस -1;
	पूर्ण

	स_रखो(info->lba_to_pba, 0xff, numblocks*माप(पूर्णांक));
	स_रखो(info->pba_to_lba, 0xff, numblocks*माप(पूर्णांक));

	/* set maximum lba */
	max_lba = info->max_log_blks;
	अगर (max_lba > 1000)
		max_lba = 1000;

	/*
	 * Each block is 64 bytes of control data, so block i is located in
	 * scatterlist block i*64/128k = i*(2^6)*(2^-17) = i*(2^-11)
	 */

	क्रम (i=0; i<numblocks; i++) अणु
		पूर्णांक zone = i / 1024;

		lba = लघु_pack(buffer[i * 2], buffer[i * 2 + 1]);

			/*
			 * Every 1024 physical blocks ("zone"), the LBA numbers
			 * go back to zero, but are within a higher
			 * block of LBA's. Also, there is a maximum of
			 * 1000 LBA's per zone. In other words, in PBA
			 * 1024-2047 you will find LBA 0-999 which are
			 * really LBA 1000-1999. Yes, this wastes 24
			 * physical blocks per zone. Go figure. 
			 * These devices can have blocks go bad, so there
			 * are 24 spare blocks to use when blocks करो go bad.
			 */

			/*
			 * SDDR55 वापसs 0xffff क्रम a bad block, and 0x400 क्रम the 
			 * CIS block. (Is this true क्रम cards 8MB or less??)
			 * Record these in the physical to logical map
			 */ 

		info->pba_to_lba[i] = lba;

		अगर (lba >= max_lba) अणु
			जारी;
		पूर्ण
		
		अगर (info->lba_to_pba[lba + zone * 1000] != NOT_ALLOCATED &&
		    !info->क्रमce_पढ़ो_only) अणु
			prपूर्णांकk(KERN_WARNING
			       "sddr55: map inconsistency at LBA %04X\n",
			       lba + zone * 1000);
			info->क्रमce_पढ़ो_only = 1;
		पूर्ण

		अगर (lba<0x10 || (lba>=0x3E0 && lba<0x3EF))
			usb_stor_dbg(us, "LBA %04X <-> PBA %04X\n", lba, i);

		info->lba_to_pba[lba + zone * 1000] = i;
	पूर्ण

	kमुक्त(buffer);
	वापस 0;
पूर्ण


अटल व्योम sddr55_card_info_deकाष्ठाor(व्योम *extra) अणु
	काष्ठा sddr55_card_info *info = (काष्ठा sddr55_card_info *)extra;

	अगर (!extra)
		वापस;

	kमुक्त(info->lba_to_pba);
	kमुक्त(info->pba_to_lba);
पूर्ण


/*
 * Transport क्रम the Sandisk SDDR-55
 */
अटल पूर्णांक sddr55_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक result;
	अटल अचिन्हित अक्षर inquiry_response[8] = अणु
		0x00, 0x80, 0x00, 0x02, 0x1F, 0x00, 0x00, 0x00
	पूर्ण;
 	// ग_लिखो-रक्षित क्रम now, no block descriptor support
	अटल अचिन्हित अक्षर mode_page_01[20] = अणु
		0x0, 0x12, 0x00, 0x80, 0x0, 0x0, 0x0, 0x0,
		0x01, 0x0A,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अचिन्हित अक्षर *ptr = us->iobuf;
	अचिन्हित दीर्घ capacity;
	अचिन्हित पूर्णांक lba;
	अचिन्हित पूर्णांक pba;
	अचिन्हित पूर्णांक page;
	अचिन्हित लघु pages;
	काष्ठा sddr55_card_info *info;

	अगर (!us->extra) अणु
		us->extra = kzalloc(
			माप(काष्ठा sddr55_card_info), GFP_NOIO);
		अगर (!us->extra)
			वापस USB_STOR_TRANSPORT_ERROR;
		us->extra_deकाष्ठाor = sddr55_card_info_deकाष्ठाor;
	पूर्ण

	info = (काष्ठा sddr55_card_info *)(us->extra);

	अगर (srb->cmnd[0] == REQUEST_SENSE) अणु
		usb_stor_dbg(us, "request sense %02x/%02x/%02x\n",
			     info->sense_data[2],
			     info->sense_data[12],
			     info->sense_data[13]);

		स_नकल (ptr, info->sense_data, माप info->sense_data);
		ptr[0] = 0x70;
		ptr[7] = 11;
		usb_stor_set_xfer_buf (ptr, माप info->sense_data, srb);
		स_रखो (info->sense_data, 0, माप info->sense_data);

		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	स_रखो (info->sense_data, 0, माप info->sense_data);

	/*
	 * Dummy up a response क्रम INQUIRY since SDDR55 करोesn't
	 * respond to INQUIRY commands
	 */

	अगर (srb->cmnd[0] == INQUIRY) अणु
		स_नकल(ptr, inquiry_response, 8);
		fill_inquiry_response(us, ptr, 36);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	/*
	 * only check card status अगर the map isn't allocated, ie no card seen yet
	 * or अगर it's been over half a second since we last accessed it
	 */
	अगर (info->lba_to_pba == शून्य || समय_after(jअगरfies, info->last_access + HZ/2)) अणु

		/* check to see अगर a card is fitted */
		result = sddr55_status (us);
		अगर (result) अणु
			result = sddr55_status (us);
			अगर (!result) अणु
			set_sense_info (6, 0x28, 0);	/* new media, set unit attention, not पढ़ोy to पढ़ोy */
			पूर्ण
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	/*
	 * अगर we detected a problem with the map when writing,
	 * करोn't allow any more access
	 */
	अगर (info->fatal_error) अणु

		set_sense_info (3, 0x31, 0);
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	अगर (srb->cmnd[0] == READ_CAPACITY) अणु

		capacity = sddr55_get_capacity(us);

		अगर (!capacity) अणु
			set_sense_info (3, 0x30, 0); /* incompatible medium */
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण

		info->capacity = capacity;

		/*
		 * figure out the maximum logical block number, allowing क्रम
		 * the fact that only 250 out of every 256 are used
		 */
		info->max_log_blks = ((info->capacity >> (info->pageshअगरt + info->blockshअगरt)) / 256) * 250;

		/*
		 * Last page in the card, adjust as we only use 250 out of
		 * every 256 pages
		 */
		capacity = (capacity / 256) * 250;

		capacity /= PAGESIZE;
		capacity--;

		((__be32 *) ptr)[0] = cpu_to_be32(capacity);
		((__be32 *) ptr)[1] = cpu_to_be32(PAGESIZE);
		usb_stor_set_xfer_buf(ptr, 8, srb);

		sddr55_पढ़ो_map(us);

		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == MODE_SENSE_10) अणु

		स_नकल(ptr, mode_page_01, माप mode_page_01);
		ptr[3] = (info->पढ़ो_only || info->क्रमce_पढ़ो_only) ? 0x80 : 0;
		usb_stor_set_xfer_buf(ptr, माप(mode_page_01), srb);

		अगर ( (srb->cmnd[2] & 0x3F) == 0x01 ) अणु
			usb_stor_dbg(us, "Dummy up request for mode page 1\n");
			वापस USB_STOR_TRANSPORT_GOOD;

		पूर्ण अन्यथा अगर ( (srb->cmnd[2] & 0x3F) == 0x3F ) अणु
			usb_stor_dbg(us, "Dummy up request for all mode pages\n");
			वापस USB_STOR_TRANSPORT_GOOD;
		पूर्ण

		set_sense_info (5, 0x24, 0);	/* invalid field in command */
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	अगर (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL) अणु

		usb_stor_dbg(us, "%s medium removal. Not that I can do anything about it...\n",
			     (srb->cmnd[4]&0x03) ? "Prevent" : "Allow");

		वापस USB_STOR_TRANSPORT_GOOD;

	पूर्ण

	अगर (srb->cmnd[0] == READ_10 || srb->cmnd[0] == WRITE_10) अणु

		page = लघु_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= लघु_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = लघु_pack(srb->cmnd[8], srb->cmnd[7]);

		page <<= info->smallpageshअगरt;

		// convert page to block and page-within-block

		lba = page >> info->blockshअगरt;
		page = page & info->blockmask;

		// locate physical block corresponding to logical block

		अगर (lba >= info->max_log_blks) अणु

			usb_stor_dbg(us, "Error: Requested LBA %04X exceeds maximum block %04X\n",
				     lba, info->max_log_blks - 1);

			set_sense_info (5, 0x24, 0);	/* invalid field in command */

			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण

		pba = info->lba_to_pba[lba];

		अगर (srb->cmnd[0] == WRITE_10) अणु
			usb_stor_dbg(us, "WRITE_10: write block %04X (LBA %04X) page %01X pages %d\n",
				     pba, lba, page, pages);

			वापस sddr55_ग_लिखो_data(us, lba, page, pages);
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "READ_10: read block %04X (LBA %04X) page %01X pages %d\n",
				     pba, lba, page, pages);

			वापस sddr55_पढ़ो_data(us, lba, page, pages);
		पूर्ण
	पूर्ण


	अगर (srb->cmnd[0] == TEST_UNIT_READY) अणु
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == START_STOP) अणु
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	set_sense_info (5, 0x20, 0);	/* illegal command */

	वापस USB_STOR_TRANSPORT_FAILED; // FIXME: sense buffer?
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sddr55_host_ढाँचा;

अटल पूर्णांक sddr55_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - sddr55_usb_ids) + sddr55_unusual_dev_list,
			&sddr55_host_ढाँचा);
	अगर (result)
		वापस result;

	us->transport_name = "SDDR55";
	us->transport = sddr55_transport;
	us->transport_reset = sddr55_reset;
	us->max_lun = 0;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver sddr55_driver = अणु
	.name =		DRV_NAME,
	.probe =	sddr55_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	sddr55_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(sddr55_driver, sddr55_host_ढाँचा, DRV_NAME);
