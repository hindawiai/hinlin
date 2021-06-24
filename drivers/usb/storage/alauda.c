<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Alauda-based card पढ़ोers
 *
 * Current development and मुख्यtenance by:
 *   (c) 2005 Daniel Drake <dsd@gentoo.org>
 *
 * The 'Alauda' is a chip manufacturered by RATOC क्रम OEM use.
 *
 * Alauda implements a venकरोr-specअगरic command set to access two media पढ़ोer
 * ports (XD, SmartMedia). This driver converts SCSI commands to the commands
 * which are accepted by these devices.
 *
 * The driver was developed through reverse-engineering, with the help of the
 * sddr09 driver which has many similarities, and with some help from the
 * (very old) venकरोr-supplied GPL sma03 driver.
 *
 * For protocol info, see http://alauda.sourceक्रमge.net
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-alauda"

MODULE_DESCRIPTION("Driver for Alauda-based card readers");
MODULE_AUTHOR("Daniel Drake <dsd@gentoo.org>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

/*
 * Status bytes
 */
#घोषणा ALAUDA_STATUS_ERROR		0x01
#घोषणा ALAUDA_STATUS_READY		0x40

/*
 * Control opcodes (क्रम request field)
 */
#घोषणा ALAUDA_GET_XD_MEDIA_STATUS	0x08
#घोषणा ALAUDA_GET_SM_MEDIA_STATUS	0x98
#घोषणा ALAUDA_ACK_XD_MEDIA_CHANGE	0x0a
#घोषणा ALAUDA_ACK_SM_MEDIA_CHANGE	0x9a
#घोषणा ALAUDA_GET_XD_MEDIA_SIG		0x86
#घोषणा ALAUDA_GET_SM_MEDIA_SIG		0x96

/*
 * Bulk command identity (byte 0)
 */
#घोषणा ALAUDA_BULK_CMD			0x40

/*
 * Bulk opcodes (byte 1)
 */
#घोषणा ALAUDA_BULK_GET_REDU_DATA	0x85
#घोषणा ALAUDA_BULK_READ_BLOCK		0x94
#घोषणा ALAUDA_BULK_ERASE_BLOCK		0xa3
#घोषणा ALAUDA_BULK_WRITE_BLOCK		0xb4
#घोषणा ALAUDA_BULK_GET_STATUS2		0xb7
#घोषणा ALAUDA_BULK_RESET_MEDIA		0xe0

/*
 * Port to operate on (byte 8)
 */
#घोषणा ALAUDA_PORT_XD			0x00
#घोषणा ALAUDA_PORT_SM			0x01

/*
 * LBA and PBA are अचिन्हित पूर्णांकs. Special values.
 */
#घोषणा UNDEF    0xffff
#घोषणा SPARE    0xfffe
#घोषणा UNUSABLE 0xfffd

काष्ठा alauda_media_info अणु
	अचिन्हित दीर्घ capacity;		/* total media size in bytes */
	अचिन्हित पूर्णांक pagesize;		/* page size in bytes */
	अचिन्हित पूर्णांक blocksize;		/* number of pages per block */
	अचिन्हित पूर्णांक uzonesize;		/* number of usable blocks per zone */
	अचिन्हित पूर्णांक zonesize;		/* number of blocks per zone */
	अचिन्हित पूर्णांक blockmask;		/* mask to get page from address */

	अचिन्हित अक्षर pageshअगरt;
	अचिन्हित अक्षर blockshअगरt;
	अचिन्हित अक्षर zoneshअगरt;

	u16 **lba_to_pba;		/* logical to physical block map */
	u16 **pba_to_lba;		/* physical to logical block map */
पूर्ण;

काष्ठा alauda_info अणु
	काष्ठा alauda_media_info port[2];
	पूर्णांक wr_ep;			/* endpoपूर्णांक to ग_लिखो data out of */

	अचिन्हित अक्षर sense_key;
	अचिन्हित दीर्घ sense_asc;	/* additional sense code */
	अचिन्हित दीर्घ sense_ascq;	/* additional sense code qualअगरier */
पूर्ण;

#घोषणा लघु_pack(lsb,msb) ( ((u16)(lsb)) | ( ((u16)(msb))<<8 ) )
#घोषणा LSB_of(s) ((s)&0xFF)
#घोषणा MSB_of(s) ((s)>>8)

#घोषणा MEDIA_PORT(us) us->srb->device->lun
#घोषणा MEDIA_INFO(us) ((काष्ठा alauda_info *)us->extra)->port[MEDIA_PORT(us)]

#घोषणा PBA_LO(pba) ((pba & 0xF) << 5)
#घोषणा PBA_HI(pba) (pba >> 3)
#घोषणा PBA_ZONE(pba) (pba >> 11)

अटल पूर्णांक init_alauda(काष्ठा us_data *us);


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id alauda_usb_ids[] = अणु
#	include "unusual_alauda.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, alauda_usb_ids);

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

अटल काष्ठा us_unusual_dev alauda_unusual_dev_list[] = अणु
#	include "unusual_alauda.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


/*
 * Media handling
 */

काष्ठा alauda_card_info अणु
	अचिन्हित अक्षर id;		/* id byte */
	अचिन्हित अक्षर chipshअगरt;	/* 1<<cs bytes total capacity */
	अचिन्हित अक्षर pageshअगरt;	/* 1<<ps bytes in a page */
	अचिन्हित अक्षर blockshअगरt;	/* 1<<bs pages per block */
	अचिन्हित अक्षर zoneshअगरt;	/* 1<<zs blocks per zone */
पूर्ण;

अटल काष्ठा alauda_card_info alauda_card_ids[] = अणु
	/* न_अंकD flash */
	अणु 0x6e, 20, 8, 4, 8पूर्ण,	/* 1 MB */
	अणु 0xe8, 20, 8, 4, 8पूर्ण,	/* 1 MB */
	अणु 0xec, 20, 8, 4, 8पूर्ण,	/* 1 MB */
	अणु 0x64, 21, 8, 4, 9पूर्ण, 	/* 2 MB */
	अणु 0xea, 21, 8, 4, 9पूर्ण,	/* 2 MB */
	अणु 0x6b, 22, 9, 4, 9पूर्ण,	/* 4 MB */
	अणु 0xe3, 22, 9, 4, 9पूर्ण,	/* 4 MB */
	अणु 0xe5, 22, 9, 4, 9पूर्ण,	/* 4 MB */
	अणु 0xe6, 23, 9, 4, 10पूर्ण,	/* 8 MB */
	अणु 0x73, 24, 9, 5, 10पूर्ण,	/* 16 MB */
	अणु 0x75, 25, 9, 5, 10पूर्ण,	/* 32 MB */
	अणु 0x76, 26, 9, 5, 10पूर्ण,	/* 64 MB */
	अणु 0x79, 27, 9, 5, 10पूर्ण,	/* 128 MB */
	अणु 0x71, 28, 9, 5, 10पूर्ण,	/* 256 MB */

	/* MASK ROM */
	अणु 0x5d, 21, 9, 4, 8पूर्ण,	/* 2 MB */
	अणु 0xd5, 22, 9, 4, 9पूर्ण,	/* 4 MB */
	अणु 0xd6, 23, 9, 4, 10पूर्ण,	/* 8 MB */
	अणु 0x57, 24, 9, 4, 11पूर्ण,	/* 16 MB */
	अणु 0x58, 25, 9, 4, 12पूर्ण,	/* 32 MB */
	अणु 0,पूर्ण
पूर्ण;

अटल काष्ठा alauda_card_info *alauda_card_find_id(अचिन्हित अक्षर id)
अणु
	पूर्णांक i;

	क्रम (i = 0; alauda_card_ids[i].id != 0; i++)
		अगर (alauda_card_ids[i].id == id)
			वापस &(alauda_card_ids[i]);
	वापस शून्य;
पूर्ण

/*
 * ECC computation.
 */

अटल अचिन्हित अक्षर parity[256];
अटल अचिन्हित अक्षर ecc2[256];

अटल व्योम nand_init_ecc(व्योम)
अणु
	पूर्णांक i, j, a;

	parity[0] = 0;
	क्रम (i = 1; i < 256; i++)
		parity[i] = (parity[i&(i-1)] ^ 1);

	क्रम (i = 0; i < 256; i++) अणु
		a = 0;
		क्रम (j = 0; j < 8; j++) अणु
			अगर (i & (1<<j)) अणु
				अगर ((j & 1) == 0)
					a ^= 0x04;
				अगर ((j & 2) == 0)
					a ^= 0x10;
				अगर ((j & 4) == 0)
					a ^= 0x40;
			पूर्ण
		पूर्ण
		ecc2[i] = ~(a ^ (a<<1) ^ (parity[i] ? 0xa8 : 0));
	पूर्ण
पूर्ण

/* compute 3-byte ecc on 256 bytes */
अटल व्योम nand_compute_ecc(अचिन्हित अक्षर *data, अचिन्हित अक्षर *ecc)
अणु
	पूर्णांक i, j, a;
	अचिन्हित अक्षर par = 0, bit, bits[8] = अणु0पूर्ण;

	/* collect 16 checksum bits */
	क्रम (i = 0; i < 256; i++) अणु
		par ^= data[i];
		bit = parity[data[i]];
		क्रम (j = 0; j < 8; j++)
			अगर ((i & (1<<j)) == 0)
				bits[j] ^= bit;
	पूर्ण

	/* put 4+4+4 = 12 bits in the ecc */
	a = (bits[3] << 6) + (bits[2] << 4) + (bits[1] << 2) + bits[0];
	ecc[0] = ~(a ^ (a<<1) ^ (parity[par] ? 0xaa : 0));

	a = (bits[7] << 6) + (bits[6] << 4) + (bits[5] << 2) + bits[4];
	ecc[1] = ~(a ^ (a<<1) ^ (parity[par] ? 0xaa : 0));

	ecc[2] = ecc2[par];
पूर्ण

अटल पूर्णांक nand_compare_ecc(अचिन्हित अक्षर *data, अचिन्हित अक्षर *ecc)
अणु
	वापस (data[0] == ecc[0] && data[1] == ecc[1] && data[2] == ecc[2]);
पूर्ण

अटल व्योम nand_store_ecc(अचिन्हित अक्षर *data, अचिन्हित अक्षर *ecc)
अणु
	स_नकल(data, ecc, 3);
पूर्ण

/*
 * Alauda driver
 */

/*
 * Forget our PBA <---> LBA mappings क्रम a particular port
 */
अटल व्योम alauda_मुक्त_maps (काष्ठा alauda_media_info *media_info)
अणु
	अचिन्हित पूर्णांक shअगरt = media_info->zoneshअगरt
		+ media_info->blockshअगरt + media_info->pageshअगरt;
	अचिन्हित पूर्णांक num_zones = media_info->capacity >> shअगरt;
	अचिन्हित पूर्णांक i;

	अगर (media_info->lba_to_pba != शून्य)
		क्रम (i = 0; i < num_zones; i++) अणु
			kमुक्त(media_info->lba_to_pba[i]);
			media_info->lba_to_pba[i] = शून्य;
		पूर्ण

	अगर (media_info->pba_to_lba != शून्य)
		क्रम (i = 0; i < num_zones; i++) अणु
			kमुक्त(media_info->pba_to_lba[i]);
			media_info->pba_to_lba[i] = शून्य;
		पूर्ण
पूर्ण

/*
 * Returns 2 bytes of status data
 * The first byte describes media status, and second byte describes करोor status
 */
अटल पूर्णांक alauda_get_media_status(काष्ठा us_data *us, अचिन्हित अक्षर *data)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर command;

	अगर (MEDIA_PORT(us) == ALAUDA_PORT_XD)
		command = ALAUDA_GET_XD_MEDIA_STATUS;
	अन्यथा
		command = ALAUDA_GET_SM_MEDIA_STATUS;

	rc = usb_stor_ctrl_transfer(us, us->recv_ctrl_pipe,
		command, 0xc0, 0, 1, data, 2);

	usb_stor_dbg(us, "Media status %02X %02X\n", data[0], data[1]);

	वापस rc;
पूर्ण

/*
 * Clears the "media was changed" bit so that we know when it changes again
 * in the future.
 */
अटल पूर्णांक alauda_ack_media(काष्ठा us_data *us)
अणु
	अचिन्हित अक्षर command;

	अगर (MEDIA_PORT(us) == ALAUDA_PORT_XD)
		command = ALAUDA_ACK_XD_MEDIA_CHANGE;
	अन्यथा
		command = ALAUDA_ACK_SM_MEDIA_CHANGE;

	वापस usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
		command, 0x40, 0, 1, शून्य, 0);
पूर्ण

/*
 * Retrieves a 4-byte media signature, which indicates manufacturer, capacity,
 * and some other details.
 */
अटल पूर्णांक alauda_get_media_signature(काष्ठा us_data *us, अचिन्हित अक्षर *data)
अणु
	अचिन्हित अक्षर command;

	अगर (MEDIA_PORT(us) == ALAUDA_PORT_XD)
		command = ALAUDA_GET_XD_MEDIA_SIG;
	अन्यथा
		command = ALAUDA_GET_SM_MEDIA_SIG;

	वापस usb_stor_ctrl_transfer(us, us->recv_ctrl_pipe,
		command, 0xc0, 0, 0, data, 4);
पूर्ण

/*
 * Resets the media status (but not the whole device?)
 */
अटल पूर्णांक alauda_reset_media(काष्ठा us_data *us)
अणु
	अचिन्हित अक्षर *command = us->iobuf;

	स_रखो(command, 0, 9);
	command[0] = ALAUDA_BULK_CMD;
	command[1] = ALAUDA_BULK_RESET_MEDIA;
	command[8] = MEDIA_PORT(us);

	वापस usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, शून्य);
पूर्ण

/*
 * Examines the media and deduces capacity, etc.
 */
अटल पूर्णांक alauda_init_media(काष्ठा us_data *us)
अणु
	अचिन्हित अक्षर *data = us->iobuf;
	पूर्णांक पढ़ोy = 0;
	काष्ठा alauda_card_info *media_info;
	अचिन्हित पूर्णांक num_zones;

	जबतक (पढ़ोy == 0) अणु
		msleep(20);

		अगर (alauda_get_media_status(us, data) != USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (data[0] & 0x10)
			पढ़ोy = 1;
	पूर्ण

	usb_stor_dbg(us, "We are ready for action!\n");

	अगर (alauda_ack_media(us) != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	msleep(10);

	अगर (alauda_get_media_status(us, data) != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (data[0] != 0x14) अणु
		usb_stor_dbg(us, "Media not ready after ack\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	अगर (alauda_get_media_signature(us, data) != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "Media signature: %4ph\n", data);
	media_info = alauda_card_find_id(data[1]);
	अगर (media_info == शून्य) अणु
		pr_warn("alauda_init_media: Unrecognised media signature: %4ph\n",
			data);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	MEDIA_INFO(us).capacity = 1 << media_info->chipshअगरt;
	usb_stor_dbg(us, "Found media with capacity: %ldMB\n",
		     MEDIA_INFO(us).capacity >> 20);

	MEDIA_INFO(us).pageshअगरt = media_info->pageshअगरt;
	MEDIA_INFO(us).blockshअगरt = media_info->blockshअगरt;
	MEDIA_INFO(us).zoneshअगरt = media_info->zoneshअगरt;

	MEDIA_INFO(us).pagesize = 1 << media_info->pageshअगरt;
	MEDIA_INFO(us).blocksize = 1 << media_info->blockshअगरt;
	MEDIA_INFO(us).zonesize = 1 << media_info->zoneshअगरt;

	MEDIA_INFO(us).uzonesize = ((1 << media_info->zoneshअगरt) / 128) * 125;
	MEDIA_INFO(us).blockmask = MEDIA_INFO(us).blocksize - 1;

	num_zones = MEDIA_INFO(us).capacity >> (MEDIA_INFO(us).zoneshअगरt
		+ MEDIA_INFO(us).blockshअगरt + MEDIA_INFO(us).pageshअगरt);
	MEDIA_INFO(us).pba_to_lba = kसुस्मृति(num_zones, माप(u16*), GFP_NOIO);
	MEDIA_INFO(us).lba_to_pba = kसुस्मृति(num_zones, माप(u16*), GFP_NOIO);

	अगर (alauda_reset_media(us) != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Examines the media status and करोes the right thing when the media has gone,
 * appeared, or changed.
 */
अटल पूर्णांक alauda_check_media(काष्ठा us_data *us)
अणु
	काष्ठा alauda_info *info = (काष्ठा alauda_info *) us->extra;
	अचिन्हित अक्षर status[2];

	alauda_get_media_status(us, status);

	/* Check क्रम no media or करोor खोलो */
	अगर ((status[0] & 0x80) || ((status[0] & 0x1F) == 0x10)
		|| ((status[1] & 0x01) == 0)) अणु
		usb_stor_dbg(us, "No media, or door open\n");
		alauda_मुक्त_maps(&MEDIA_INFO(us));
		info->sense_key = 0x02;
		info->sense_asc = 0x3A;
		info->sense_ascq = 0x00;
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	/* Check क्रम media change */
	अगर (status[0] & 0x08) अणु
		usb_stor_dbg(us, "Media change detected\n");
		alauda_मुक्त_maps(&MEDIA_INFO(us));
		alauda_init_media(us);

		info->sense_key = UNIT_ATTENTION;
		info->sense_asc = 0x28;
		info->sense_ascq = 0x00;
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Checks the status from the 2nd status रेजिस्टर
 * Returns 3 bytes of status data, only the first is known
 */
अटल पूर्णांक alauda_check_status2(काष्ठा us_data *us)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर command[] = अणु
		ALAUDA_BULK_CMD, ALAUDA_BULK_GET_STATUS2,
		0, 0, 0, 0, 3, 0, MEDIA_PORT(us)
	पूर्ण;
	अचिन्हित अक्षर data[3];

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	rc = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
		data, 3, शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	usb_stor_dbg(us, "%3ph\n", data);
	अगर (data[0] & ALAUDA_STATUS_ERROR)
		वापस USB_STOR_XFER_ERROR;

	वापस USB_STOR_XFER_GOOD;
पूर्ण

/*
 * Gets the redundancy data क्रम the first page of a PBA
 * Returns 16 bytes.
 */
अटल पूर्णांक alauda_get_redu_data(काष्ठा us_data *us, u16 pba, अचिन्हित अक्षर *data)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर command[] = अणु
		ALAUDA_BULK_CMD, ALAUDA_BULK_GET_REDU_DATA,
		PBA_HI(pba), PBA_ZONE(pba), 0, PBA_LO(pba), 0, 0, MEDIA_PORT(us)
	पूर्ण;

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	वापस usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
		data, 16, शून्य);
पूर्ण

/*
 * Finds the first unused PBA in a zone
 * Returns the असलolute PBA of an unused PBA, or 0 अगर none found.
 */
अटल u16 alauda_find_unused_pba(काष्ठा alauda_media_info *info,
	अचिन्हित पूर्णांक zone)
अणु
	u16 *pba_to_lba = info->pba_to_lba[zone];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < info->zonesize; i++)
		अगर (pba_to_lba[i] == UNDEF)
			वापस (zone << info->zoneshअगरt) + i;

	वापस 0;
पूर्ण

/*
 * Reads the redundancy data क्रम all PBA's in a zone
 * Produces lba <--> pba mappings
 */
अटल पूर्णांक alauda_पढ़ो_map(काष्ठा us_data *us, अचिन्हित पूर्णांक zone)
अणु
	अचिन्हित अक्षर *data = us->iobuf;
	पूर्णांक result;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक zonesize = MEDIA_INFO(us).zonesize;
	अचिन्हित पूर्णांक uzonesize = MEDIA_INFO(us).uzonesize;
	अचिन्हित पूर्णांक lba_offset, lba_real, blocknum;
	अचिन्हित पूर्णांक zone_base_lba = zone * uzonesize;
	अचिन्हित पूर्णांक zone_base_pba = zone * zonesize;
	u16 *lba_to_pba = kसुस्मृति(zonesize, माप(u16), GFP_NOIO);
	u16 *pba_to_lba = kसुस्मृति(zonesize, माप(u16), GFP_NOIO);
	अगर (lba_to_pba == शून्य || pba_to_lba == शून्य) अणु
		result = USB_STOR_TRANSPORT_ERROR;
		जाओ error;
	पूर्ण

	usb_stor_dbg(us, "Mapping blocks for zone %d\n", zone);

	/* 1024 PBA's per zone */
	क्रम (i = 0; i < zonesize; i++)
		lba_to_pba[i] = pba_to_lba[i] = UNDEF;

	क्रम (i = 0; i < zonesize; i++) अणु
		blocknum = zone_base_pba + i;

		result = alauda_get_redu_data(us, blocknum, data);
		अगर (result != USB_STOR_XFER_GOOD) अणु
			result = USB_STOR_TRANSPORT_ERROR;
			जाओ error;
		पूर्ण

		/* special PBAs have control field 0^16 */
		क्रम (j = 0; j < 16; j++)
			अगर (data[j] != 0)
				जाओ nonz;
		pba_to_lba[i] = UNUSABLE;
		usb_stor_dbg(us, "PBA %d has no logical mapping\n", blocknum);
		जारी;

	nonz:
		/* unwritten PBAs have control field FF^16 */
		क्रम (j = 0; j < 16; j++)
			अगर (data[j] != 0xff)
				जाओ nonff;
		जारी;

	nonff:
		/* normal PBAs start with six FFs */
		अगर (j < 6) अणु
			usb_stor_dbg(us, "PBA %d has no logical mapping: reserved area = %02X%02X%02X%02X data status %02X block status %02X\n",
				     blocknum,
				     data[0], data[1], data[2], data[3],
				     data[4], data[5]);
			pba_to_lba[i] = UNUSABLE;
			जारी;
		पूर्ण

		अगर ((data[6] >> 4) != 0x01) अणु
			usb_stor_dbg(us, "PBA %d has invalid address field %02X%02X/%02X%02X\n",
				     blocknum, data[6], data[7],
				     data[11], data[12]);
			pba_to_lba[i] = UNUSABLE;
			जारी;
		पूर्ण

		/* check even parity */
		अगर (parity[data[6] ^ data[7]]) अणु
			prपूर्णांकk(KERN_WARNING
			       "alauda_read_map: Bad parity in LBA for block %d"
			       " (%02X %02X)\n", i, data[6], data[7]);
			pba_to_lba[i] = UNUSABLE;
			जारी;
		पूर्ण

		lba_offset = लघु_pack(data[7], data[6]);
		lba_offset = (lba_offset & 0x07FF) >> 1;
		lba_real = lba_offset + zone_base_lba;

		/*
		 * Every 1024 physical blocks ("zone"), the LBA numbers
		 * go back to zero, but are within a higher block of LBA's.
		 * Also, there is a maximum of 1000 LBA's per zone.
		 * In other words, in PBA 1024-2047 you will find LBA 0-999
		 * which are really LBA 1000-1999. This allows क्रम 24 bad
		 * or special physical blocks per zone.
		 */

		अगर (lba_offset >= uzonesize) अणु
			prपूर्णांकk(KERN_WARNING
			       "alauda_read_map: Bad low LBA %d for block %d\n",
			       lba_real, blocknum);
			जारी;
		पूर्ण

		अगर (lba_to_pba[lba_offset] != UNDEF) अणु
			prपूर्णांकk(KERN_WARNING
			       "alauda_read_map: "
			       "LBA %d seen for PBA %d and %d\n",
			       lba_real, lba_to_pba[lba_offset], blocknum);
			जारी;
		पूर्ण

		pba_to_lba[i] = lba_real;
		lba_to_pba[lba_offset] = blocknum;
		जारी;
	पूर्ण

	MEDIA_INFO(us).lba_to_pba[zone] = lba_to_pba;
	MEDIA_INFO(us).pba_to_lba[zone] = pba_to_lba;
	result = 0;
	जाओ out;

error:
	kमुक्त(lba_to_pba);
	kमुक्त(pba_to_lba);
out:
	वापस result;
पूर्ण

/*
 * Checks to see whether we have alपढ़ोy mapped a certain zone
 * If we haven't, the map is generated
 */
अटल व्योम alauda_ensure_map_क्रम_zone(काष्ठा us_data *us, अचिन्हित पूर्णांक zone)
अणु
	अगर (MEDIA_INFO(us).lba_to_pba[zone] == शून्य
		|| MEDIA_INFO(us).pba_to_lba[zone] == शून्य)
		alauda_पढ़ो_map(us, zone);
पूर्ण

/*
 * Erases an entire block
 */
अटल पूर्णांक alauda_erase_block(काष्ठा us_data *us, u16 pba)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर command[] = अणु
		ALAUDA_BULK_CMD, ALAUDA_BULK_ERASE_BLOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_LO(pba), 0x02, 0, MEDIA_PORT(us)
	पूर्ण;
	अचिन्हित अक्षर buf[2];

	usb_stor_dbg(us, "Erasing PBA %d\n", pba);

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	rc = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
		buf, 2, शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	usb_stor_dbg(us, "Erase result: %02X %02X\n", buf[0], buf[1]);
	वापस rc;
पूर्ण

/*
 * Reads data from a certain offset page inside a PBA, including पूर्णांकerleaved
 * redundancy data. Returns (pagesize+64)*pages bytes in data.
 */
अटल पूर्णांक alauda_पढ़ो_block_raw(काष्ठा us_data *us, u16 pba,
		अचिन्हित पूर्णांक page, अचिन्हित पूर्णांक pages, अचिन्हित अक्षर *data)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर command[] = अणु
		ALAUDA_BULK_CMD, ALAUDA_BULK_READ_BLOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_LO(pba) + page, pages, 0, MEDIA_PORT(us)
	पूर्ण;

	usb_stor_dbg(us, "pba %d page %d count %d\n", pba, page, pages);

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	वापस usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
		data, (MEDIA_INFO(us).pagesize + 64) * pages, शून्य);
पूर्ण

/*
 * Reads data from a certain offset page inside a PBA, excluding redundancy
 * data. Returns pagesize*pages bytes in data. Note that data must be big enough
 * to hold (pagesize+64)*pages bytes of data, but you can ignore those 'extra'
 * trailing bytes outside this function.
 */
अटल पूर्णांक alauda_पढ़ो_block(काष्ठा us_data *us, u16 pba,
		अचिन्हित पूर्णांक page, अचिन्हित पूर्णांक pages, अचिन्हित अक्षर *data)
अणु
	पूर्णांक i, rc;
	अचिन्हित पूर्णांक pagesize = MEDIA_INFO(us).pagesize;

	rc = alauda_पढ़ो_block_raw(us, pba, page, pages, data);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	/* Cut out the redundancy data */
	क्रम (i = 0; i < pages; i++) अणु
		पूर्णांक dest_offset = i * pagesize;
		पूर्णांक src_offset = i * (pagesize + 64);
		स_हटाओ(data + dest_offset, data + src_offset, pagesize);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Writes an entire block of data and checks status after ग_लिखो.
 * Redundancy data must be alपढ़ोy included in data. Data should be
 * (pagesize+64)*blocksize bytes in length.
 */
अटल पूर्णांक alauda_ग_लिखो_block(काष्ठा us_data *us, u16 pba, अचिन्हित अक्षर *data)
अणु
	पूर्णांक rc;
	काष्ठा alauda_info *info = (काष्ठा alauda_info *) us->extra;
	अचिन्हित अक्षर command[] = अणु
		ALAUDA_BULK_CMD, ALAUDA_BULK_WRITE_BLOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_LO(pba), 32, 0, MEDIA_PORT(us)
	पूर्ण;

	usb_stor_dbg(us, "pba %d\n", pba);

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	rc = usb_stor_bulk_transfer_buf(us, info->wr_ep, data,
		(MEDIA_INFO(us).pagesize + 64) * MEDIA_INFO(us).blocksize,
		शून्य);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस rc;

	वापस alauda_check_status2(us);
पूर्ण

/*
 * Write some data to a specअगरic LBA.
 */
अटल पूर्णांक alauda_ग_लिखो_lba(काष्ठा us_data *us, u16 lba,
		 अचिन्हित पूर्णांक page, अचिन्हित पूर्णांक pages,
		 अचिन्हित अक्षर *ptr, अचिन्हित अक्षर *blockbuffer)
अणु
	u16 pba, lbap, new_pba;
	अचिन्हित अक्षर *bptr, *cptr, *xptr;
	अचिन्हित अक्षर ecc[3];
	पूर्णांक i, result;
	अचिन्हित पूर्णांक uzonesize = MEDIA_INFO(us).uzonesize;
	अचिन्हित पूर्णांक zonesize = MEDIA_INFO(us).zonesize;
	अचिन्हित पूर्णांक pagesize = MEDIA_INFO(us).pagesize;
	अचिन्हित पूर्णांक blocksize = MEDIA_INFO(us).blocksize;
	अचिन्हित पूर्णांक lba_offset = lba % uzonesize;
	अचिन्हित पूर्णांक new_pba_offset;
	अचिन्हित पूर्णांक zone = lba / uzonesize;

	alauda_ensure_map_क्रम_zone(us, zone);

	pba = MEDIA_INFO(us).lba_to_pba[zone][lba_offset];
	अगर (pba == 1) अणु
		/*
		 * Maybe it is impossible to ग_लिखो to PBA 1.
		 * Fake success, but करोn't करो anything.
		 */
		prपूर्णांकk(KERN_WARNING
		       "alauda_write_lba: avoid writing to pba 1\n");
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	new_pba = alauda_find_unused_pba(&MEDIA_INFO(us), zone);
	अगर (!new_pba) अणु
		prपूर्णांकk(KERN_WARNING
		       "alauda_write_lba: Out of unused blocks\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* पढ़ो old contents */
	अगर (pba != UNDEF) अणु
		result = alauda_पढ़ो_block_raw(us, pba, 0,
			blocksize, blockbuffer);
		अगर (result != USB_STOR_XFER_GOOD)
			वापस result;
	पूर्ण अन्यथा अणु
		स_रखो(blockbuffer, 0, blocksize * (pagesize + 64));
	पूर्ण

	lbap = (lba_offset << 1) | 0x1000;
	अगर (parity[MSB_of(lbap) ^ LSB_of(lbap)])
		lbap ^= 1;

	/* check old contents and fill lba */
	क्रम (i = 0; i < blocksize; i++) अणु
		bptr = blockbuffer + (i * (pagesize + 64));
		cptr = bptr + pagesize;
		nand_compute_ecc(bptr, ecc);
		अगर (!nand_compare_ecc(cptr+13, ecc)) अणु
			usb_stor_dbg(us, "Warning: bad ecc in page %d- of pba %d\n",
				     i, pba);
			nand_store_ecc(cptr+13, ecc);
		पूर्ण
		nand_compute_ecc(bptr + (pagesize / 2), ecc);
		अगर (!nand_compare_ecc(cptr+8, ecc)) अणु
			usb_stor_dbg(us, "Warning: bad ecc in page %d+ of pba %d\n",
				     i, pba);
			nand_store_ecc(cptr+8, ecc);
		पूर्ण
		cptr[6] = cptr[11] = MSB_of(lbap);
		cptr[7] = cptr[12] = LSB_of(lbap);
	पूर्ण

	/* copy in new stuff and compute ECC */
	xptr = ptr;
	क्रम (i = page; i < page+pages; i++) अणु
		bptr = blockbuffer + (i * (pagesize + 64));
		cptr = bptr + pagesize;
		स_नकल(bptr, xptr, pagesize);
		xptr += pagesize;
		nand_compute_ecc(bptr, ecc);
		nand_store_ecc(cptr+13, ecc);
		nand_compute_ecc(bptr + (pagesize / 2), ecc);
		nand_store_ecc(cptr+8, ecc);
	पूर्ण

	result = alauda_ग_लिखो_block(us, new_pba, blockbuffer);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस result;

	new_pba_offset = new_pba - (zone * zonesize);
	MEDIA_INFO(us).pba_to_lba[zone][new_pba_offset] = lba;
	MEDIA_INFO(us).lba_to_pba[zone][lba_offset] = new_pba;
	usb_stor_dbg(us, "Remapped LBA %d to PBA %d\n", lba, new_pba);

	अगर (pba != UNDEF) अणु
		अचिन्हित पूर्णांक pba_offset = pba - (zone * zonesize);
		result = alauda_erase_block(us, pba);
		अगर (result != USB_STOR_XFER_GOOD)
			वापस result;
		MEDIA_INFO(us).pba_to_lba[zone][pba_offset] = UNDEF;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Read data from a specअगरic sector address
 */
अटल पूर्णांक alauda_पढ़ो_data(काष्ठा us_data *us, अचिन्हित दीर्घ address,
		अचिन्हित पूर्णांक sectors)
अणु
	अचिन्हित अक्षर *buffer;
	u16 lba, max_lba;
	अचिन्हित पूर्णांक page, len, offset;
	अचिन्हित पूर्णांक blockshअगरt = MEDIA_INFO(us).blockshअगरt;
	अचिन्हित पूर्णांक pageshअगरt = MEDIA_INFO(us).pageshअगरt;
	अचिन्हित पूर्णांक blocksize = MEDIA_INFO(us).blocksize;
	अचिन्हित पूर्णांक pagesize = MEDIA_INFO(us).pagesize;
	अचिन्हित पूर्णांक uzonesize = MEDIA_INFO(us).uzonesize;
	काष्ठा scatterlist *sg;
	पूर्णांक result;

	/*
	 * Since we only पढ़ो in one block at a समय, we have to create
	 * a bounce buffer and move the data a piece at a समय between the
	 * bounce buffer and the actual transfer buffer.
	 * We make this buffer big enough to hold temporary redundancy data,
	 * which we use when पढ़ोing the data blocks.
	 */

	len = min(sectors, blocksize) * (pagesize + 64);
	buffer = kदो_स्मृति(len, GFP_NOIO);
	अगर (!buffer)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* Figure out the initial LBA and page */
	lba = address >> blockshअगरt;
	page = (address & MEDIA_INFO(us).blockmask);
	max_lba = MEDIA_INFO(us).capacity >> (blockshअगरt + pageshअगरt);

	result = USB_STOR_TRANSPORT_GOOD;
	offset = 0;
	sg = शून्य;

	जबतक (sectors > 0) अणु
		अचिन्हित पूर्णांक zone = lba / uzonesize; /* पूर्णांकeger भागision */
		अचिन्हित पूर्णांक lba_offset = lba - (zone * uzonesize);
		अचिन्हित पूर्णांक pages;
		u16 pba;
		alauda_ensure_map_क्रम_zone(us, zone);

		/* Not overflowing capacity? */
		अगर (lba >= max_lba) अणु
			usb_stor_dbg(us, "Error: Requested lba %u exceeds maximum %u\n",
				     lba, max_lba);
			result = USB_STOR_TRANSPORT_ERROR;
			अवरोध;
		पूर्ण

		/* Find number of pages we can पढ़ो in this block */
		pages = min(sectors, blocksize - page);
		len = pages << pageshअगरt;

		/* Find where this lba lives on disk */
		pba = MEDIA_INFO(us).lba_to_pba[zone][lba_offset];

		अगर (pba == UNDEF) अणु	/* this lba was never written */
			usb_stor_dbg(us, "Read %d zero pages (LBA %d) page %d\n",
				     pages, lba, page);

			/*
			 * This is not really an error. It just means
			 * that the block has never been written.
			 * Instead of वापसing USB_STOR_TRANSPORT_ERROR
			 * it is better to वापस all zero data.
			 */

			स_रखो(buffer, 0, len);
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "Read %d pages, from PBA %d (LBA %d) page %d\n",
				     pages, pba, lba, page);

			result = alauda_पढ़ो_block(us, pba, page, pages, buffer);
			अगर (result != USB_STOR_TRANSPORT_GOOD)
				अवरोध;
		पूर्ण

		/* Store the data in the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, TO_XFER_BUF);

		page = 0;
		lba++;
		sectors -= pages;
	पूर्ण

	kमुक्त(buffer);
	वापस result;
पूर्ण

/*
 * Write data to a specअगरic sector address
 */
अटल पूर्णांक alauda_ग_लिखो_data(काष्ठा us_data *us, अचिन्हित दीर्घ address,
		अचिन्हित पूर्णांक sectors)
अणु
	अचिन्हित अक्षर *buffer, *blockbuffer;
	अचिन्हित पूर्णांक page, len, offset;
	अचिन्हित पूर्णांक blockshअगरt = MEDIA_INFO(us).blockshअगरt;
	अचिन्हित पूर्णांक pageshअगरt = MEDIA_INFO(us).pageshअगरt;
	अचिन्हित पूर्णांक blocksize = MEDIA_INFO(us).blocksize;
	अचिन्हित पूर्णांक pagesize = MEDIA_INFO(us).pagesize;
	काष्ठा scatterlist *sg;
	u16 lba, max_lba;
	पूर्णांक result;

	/*
	 * Since we करोn't ग_लिखो the user data directly to the device,
	 * we have to create a bounce buffer and move the data a piece
	 * at a समय between the bounce buffer and the actual transfer buffer.
	 */

	len = min(sectors, blocksize) * pagesize;
	buffer = kदो_स्मृति(len, GFP_NOIO);
	अगर (!buffer)
		वापस USB_STOR_TRANSPORT_ERROR;

	/*
	 * We also need a temporary block buffer, where we पढ़ो in the old data,
	 * overग_लिखो parts with the new data, and manipulate the redundancy data
	 */
	blockbuffer = kदो_स्मृति_array(pagesize + 64, blocksize, GFP_NOIO);
	अगर (!blockbuffer) अणु
		kमुक्त(buffer);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* Figure out the initial LBA and page */
	lba = address >> blockshअगरt;
	page = (address & MEDIA_INFO(us).blockmask);
	max_lba = MEDIA_INFO(us).capacity >> (pageshअगरt + blockshअगरt);

	result = USB_STOR_TRANSPORT_GOOD;
	offset = 0;
	sg = शून्य;

	जबतक (sectors > 0) अणु
		/* Write as many sectors as possible in this block */
		अचिन्हित पूर्णांक pages = min(sectors, blocksize - page);
		len = pages << pageshअगरt;

		/* Not overflowing capacity? */
		अगर (lba >= max_lba) अणु
			usb_stor_dbg(us, "Requested lba %u exceeds maximum %u\n",
				     lba, max_lba);
			result = USB_STOR_TRANSPORT_ERROR;
			अवरोध;
		पूर्ण

		/* Get the data from the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, FROM_XFER_BUF);

		result = alauda_ग_लिखो_lba(us, lba, page, pages, buffer,
			blockbuffer);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			अवरोध;

		page = 0;
		lba++;
		sectors -= pages;
	पूर्ण

	kमुक्त(buffer);
	kमुक्त(blockbuffer);
	वापस result;
पूर्ण

/*
 * Our पूर्णांकerface with the rest of the world
 */

अटल व्योम alauda_info_deकाष्ठाor(व्योम *extra)
अणु
	काष्ठा alauda_info *info = (काष्ठा alauda_info *) extra;
	पूर्णांक port;

	अगर (!info)
		वापस;

	क्रम (port = 0; port < 2; port++) अणु
		काष्ठा alauda_media_info *media_info = &info->port[port];

		alauda_मुक्त_maps(media_info);
		kमुक्त(media_info->lba_to_pba);
		kमुक्त(media_info->pba_to_lba);
	पूर्ण
पूर्ण

/*
 * Initialize alauda_info काष्ठा and find the data-ग_लिखो endpoपूर्णांक
 */
अटल पूर्णांक init_alauda(काष्ठा us_data *us)
अणु
	काष्ठा alauda_info *info;
	काष्ठा usb_host_पूर्णांकerface *altsetting = us->pusb_पूर्णांकf->cur_altsetting;
	nand_init_ecc();

	us->extra = kzalloc(माप(काष्ठा alauda_info), GFP_NOIO);
	अगर (!us->extra)
		वापस USB_STOR_TRANSPORT_ERROR;

	info = (काष्ठा alauda_info *) us->extra;
	us->extra_deकाष्ठाor = alauda_info_deकाष्ठाor;

	info->wr_ep = usb_sndbulkpipe(us->pusb_dev,
		altsetting->endpoपूर्णांक[0].desc.bEndpoपूर्णांकAddress
		& USB_ENDPOINT_NUMBER_MASK);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक alauda_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक rc;
	काष्ठा alauda_info *info = (काष्ठा alauda_info *) us->extra;
	अचिन्हित अक्षर *ptr = us->iobuf;
	अटल अचिन्हित अक्षर inquiry_response[36] = अणु
		0x00, 0x80, 0x00, 0x01, 0x1F, 0x00, 0x00, 0x00
	पूर्ण;

	अगर (srb->cmnd[0] == INQUIRY) अणु
		usb_stor_dbg(us, "INQUIRY - Returning bogus response\n");
		स_नकल(ptr, inquiry_response, माप(inquiry_response));
		fill_inquiry_response(us, ptr, 36);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == TEST_UNIT_READY) अणु
		usb_stor_dbg(us, "TEST_UNIT_READY\n");
		वापस alauda_check_media(us);
	पूर्ण

	अगर (srb->cmnd[0] == READ_CAPACITY) अणु
		अचिन्हित पूर्णांक num_zones;
		अचिन्हित दीर्घ capacity;

		rc = alauda_check_media(us);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		num_zones = MEDIA_INFO(us).capacity >> (MEDIA_INFO(us).zoneshअगरt
			+ MEDIA_INFO(us).blockshअगरt + MEDIA_INFO(us).pageshअगरt);

		capacity = num_zones * MEDIA_INFO(us).uzonesize
			* MEDIA_INFO(us).blocksize;

		/* Report capacity and page size */
		((__be32 *) ptr)[0] = cpu_to_be32(capacity - 1);
		((__be32 *) ptr)[1] = cpu_to_be32(512);

		usb_stor_set_xfer_buf(ptr, 8, srb);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == READ_10) अणु
		अचिन्हित पूर्णांक page, pages;

		rc = alauda_check_media(us);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		page = लघु_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= लघु_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = लघु_pack(srb->cmnd[8], srb->cmnd[7]);

		usb_stor_dbg(us, "READ_10: page %d pagect %d\n", page, pages);

		वापस alauda_पढ़ो_data(us, page, pages);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_10) अणु
		अचिन्हित पूर्णांक page, pages;

		rc = alauda_check_media(us);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		page = लघु_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= लघु_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = लघु_pack(srb->cmnd[8], srb->cmnd[7]);

		usb_stor_dbg(us, "WRITE_10: page %d pagect %d\n", page, pages);

		वापस alauda_ग_लिखो_data(us, page, pages);
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

	अगर (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL) अणु
		/*
		 * sure.  whatever.  not like we can stop the user from popping
		 * the media out of the device (no locking करोors, etc)
		 */
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	usb_stor_dbg(us, "Gah! Unknown command: %d (0x%x)\n",
		     srb->cmnd[0], srb->cmnd[0]);
	info->sense_key = 0x05;
	info->sense_asc = 0x20;
	info->sense_ascq = 0x00;
	वापस USB_STOR_TRANSPORT_FAILED;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा alauda_host_ढाँचा;

अटल पूर्णांक alauda_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - alauda_usb_ids) + alauda_unusual_dev_list,
			&alauda_host_ढाँचा);
	अगर (result)
		वापस result;

	us->transport_name  = "Alauda Control/Bulk";
	us->transport = alauda_transport;
	us->transport_reset = usb_stor_Bulk_reset;
	us->max_lun = 1;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver alauda_driver = अणु
	.name =		DRV_NAME,
	.probe =	alauda_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	alauda_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(alauda_driver, alauda_host_ढाँचा, DRV_NAME);
