<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम SanDisk SDDR-09 SmartMedia पढ़ोer
 *
 *   (c) 2000, 2001 Robert Baruch (स्वतःphile@starband.net)
 *   (c) 2002 Andries Brouwer (aeb@cwi.nl)
 * Developed with the assistance of:
 *   (c) 2002 Alan Stern <stern@rowland.org>
 *
 * The SanDisk SDDR-09 SmartMedia पढ़ोer uses the Shuttle EUSB-01 chip.
 * This chip is a programmable USB controller. In the SDDR-09, it has
 * been programmed to obey a certain limited set of SCSI commands.
 * This driver translates the "real" SCSI commands to the SDDR-09 SCSI
 * commands.
 */

/*
 * Known venकरोr commands: 12 bytes, first byte is opcode
 *
 * E7: पढ़ो scatter gather
 * E8: पढ़ो
 * E9: ग_लिखो
 * EA: erase
 * EB: reset
 * EC: पढ़ो status
 * ED: पढ़ो ID
 * EE: ग_लिखो CIS (?)
 * EF: compute checksum (?)
 */

#समावेश <linux/त्रुटिसं.स>
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

#घोषणा DRV_NAME "ums-sddr09"

MODULE_DESCRIPTION("Driver for SanDisk SDDR-09 SmartMedia reader");
MODULE_AUTHOR("Andries Brouwer <aeb@cwi.nl>, Robert Baruch <autophile@starband.net>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

अटल पूर्णांक usb_stor_sddr09_dpcm_init(काष्ठा us_data *us);
अटल पूर्णांक sddr09_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us);
अटल पूर्णांक usb_stor_sddr09_init(काष्ठा us_data *us);


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id sddr09_usb_ids[] = अणु
#	include "unusual_sddr09.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, sddr09_usb_ids);

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

अटल काष्ठा us_unusual_dev sddr09_unusual_dev_list[] = अणु
#	include "unusual_sddr09.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


#घोषणा लघु_pack(lsb,msb) ( ((u16)(lsb)) | ( ((u16)(msb))<<8 ) )
#घोषणा LSB_of(s) ((s)&0xFF)
#घोषणा MSB_of(s) ((s)>>8)

/*
 * First some stuff that करोes not beदीर्घ here:
 * data on SmartMedia and other cards, completely
 * unrelated to this driver.
 * Similar stuff occurs in <linux/mtd/nand_ids.h>.
 */

काष्ठा nand_flash_dev अणु
	पूर्णांक model_id;
	पूर्णांक chipshअगरt;		/* 1<<cs bytes total capacity */
	अक्षर pageshअगरt;		/* 1<<ps bytes in a page */
	अक्षर blockshअगरt;	/* 1<<bs pages in an erase block */
	अक्षर zoneshअगरt;		/* 1<<zs blocks in a zone */
				/* # of logical blocks is 125/128 of this */
	अक्षर pageadrlen;	/* length of an address in bytes - 1 */
पूर्ण;

/*
 * न_अंकD Flash Manufacturer ID Codes
 */
#घोषणा न_अंकD_MFR_AMD		0x01
#घोषणा न_अंकD_MFR_NATSEMI	0x8f
#घोषणा न_अंकD_MFR_TOSHIBA	0x98
#घोषणा न_अंकD_MFR_SAMSUNG	0xec

अटल अंतरभूत अक्षर *nand_flash_manufacturer(पूर्णांक manuf_id) अणु
	चयन(manuf_id) अणु
	हाल न_अंकD_MFR_AMD:
		वापस "AMD";
	हाल न_अंकD_MFR_NATSEMI:
		वापस "NATSEMI";
	हाल न_अंकD_MFR_TOSHIBA:
		वापस "Toshiba";
	हाल न_अंकD_MFR_SAMSUNG:
		वापस "Samsung";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/*
 * It looks like it is unnecessary to attach manufacturer to the
 * reमुख्यing data: SSFDC prescribes manufacturer-independent id codes.
 *
 * 256 MB न_अंकD flash has a 5-byte ID with 2nd byte 0xaa, 0xba, 0xca or 0xda.
 */

अटल काष्ठा nand_flash_dev nand_flash_ids[] = अणु
	/* न_अंकD flash */
	अणु 0x6e, 20, 8, 4, 8, 2पूर्ण,	/* 1 MB */
	अणु 0xe8, 20, 8, 4, 8, 2पूर्ण,	/* 1 MB */
	अणु 0xec, 20, 8, 4, 8, 2पूर्ण,	/* 1 MB */
	अणु 0x64, 21, 8, 4, 9, 2पूर्ण, 	/* 2 MB */
	अणु 0xea, 21, 8, 4, 9, 2पूर्ण,	/* 2 MB */
	अणु 0x6b, 22, 9, 4, 9, 2पूर्ण,	/* 4 MB */
	अणु 0xe3, 22, 9, 4, 9, 2पूर्ण,	/* 4 MB */
	अणु 0xe5, 22, 9, 4, 9, 2पूर्ण,	/* 4 MB */
	अणु 0xe6, 23, 9, 4, 10, 2पूर्ण,	/* 8 MB */
	अणु 0x73, 24, 9, 5, 10, 2पूर्ण,	/* 16 MB */
	अणु 0x75, 25, 9, 5, 10, 2पूर्ण,	/* 32 MB */
	अणु 0x76, 26, 9, 5, 10, 3पूर्ण,	/* 64 MB */
	अणु 0x79, 27, 9, 5, 10, 3पूर्ण,	/* 128 MB */

	/* MASK ROM */
	अणु 0x5d, 21, 9, 4, 8, 2पूर्ण,	/* 2 MB */
	अणु 0xd5, 22, 9, 4, 9, 2पूर्ण,	/* 4 MB */
	अणु 0xd6, 23, 9, 4, 10, 2पूर्ण,	/* 8 MB */
	अणु 0x57, 24, 9, 4, 11, 2पूर्ण,	/* 16 MB */
	अणु 0x58, 25, 9, 4, 12, 2पूर्ण,	/* 32 MB */
	अणु 0,पूर्ण
पूर्ण;

अटल काष्ठा nand_flash_dev *
nand_find_id(अचिन्हित अक्षर id) अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nand_flash_ids); i++)
		अगर (nand_flash_ids[i].model_id == id)
			वापस &(nand_flash_ids[i]);
	वापस शून्य;
पूर्ण

/*
 * ECC computation.
 */
अटल अचिन्हित अक्षर parity[256];
अटल अचिन्हित अक्षर ecc2[256];

अटल व्योम nand_init_ecc(व्योम) अणु
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
अटल व्योम nand_compute_ecc(अचिन्हित अक्षर *data, अचिन्हित अक्षर *ecc) अणु
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

अटल पूर्णांक nand_compare_ecc(अचिन्हित अक्षर *data, अचिन्हित अक्षर *ecc) अणु
	वापस (data[0] == ecc[0] && data[1] == ecc[1] && data[2] == ecc[2]);
पूर्ण

अटल व्योम nand_store_ecc(अचिन्हित अक्षर *data, अचिन्हित अक्षर *ecc) अणु
	स_नकल(data, ecc, 3);
पूर्ण

/*
 * The actual driver starts here.
 */

काष्ठा sddr09_card_info अणु
	अचिन्हित दीर्घ	capacity;	/* Size of card in bytes */
	पूर्णांक		pagesize;	/* Size of page in bytes */
	पूर्णांक		pageshअगरt;	/* log2 of pagesize */
	पूर्णांक		blocksize;	/* Size of block in pages */
	पूर्णांक		blockshअगरt;	/* log2 of blocksize */
	पूर्णांक		blockmask;	/* 2^blockshअगरt - 1 */
	पूर्णांक		*lba_to_pba;	/* logical to physical map */
	पूर्णांक		*pba_to_lba;	/* physical to logical map */
	पूर्णांक		lbact;		/* number of available pages */
	पूर्णांक		flags;
#घोषणा	SDDR09_WP	1		/* ग_लिखो रक्षित */
पूर्ण;

/*
 * On my 16MB card, control blocks have size 64 (16 real control bytes,
 * and 48 junk bytes). In reality of course the card uses 16 control bytes,
 * so the पढ़ोer makes up the reमुख्यing 48. Don't know whether these numbers
 * depend on the card. For now a स्थिरant.
 */
#घोषणा CONTROL_SHIFT 6

/*
 * On my Combo CF/SM पढ़ोer, the SM पढ़ोer has LUN 1.
 * (and things fail with LUN 0).
 * It seems LUN is irrelevant क्रम others.
 */
#घोषणा LUN	1
#घोषणा	LUNBITS	(LUN << 5)

/*
 * LBA and PBA are अचिन्हित पूर्णांकs. Special values.
 */
#घोषणा UNDEF    0xffffffff
#घोषणा SPARE    0xfffffffe
#घोषणा UNUSABLE 0xfffffffd

अटल स्थिर पूर्णांक erase_bad_lba_entries = 0;

/* send venकरोr पूर्णांकerface command (0x41) */
/* called क्रम requests 0, 1, 8 */
अटल पूर्णांक
sddr09_send_command(काष्ठा us_data *us,
		    अचिन्हित अक्षर request,
		    अचिन्हित अक्षर direction,
		    अचिन्हित अक्षर *xfer_data,
		    अचिन्हित पूर्णांक xfer_len) अणु
	अचिन्हित पूर्णांक pipe;
	अचिन्हित अक्षर requesttype = (0x41 | direction);
	पूर्णांक rc;

	// Get the receive or send control pipe number

	अगर (direction == USB_सूची_IN)
		pipe = us->recv_ctrl_pipe;
	अन्यथा
		pipe = us->send_ctrl_pipe;

	rc = usb_stor_ctrl_transfer(us, pipe, request, requesttype,
				   0, 0, xfer_data, xfer_len);
	चयन (rc) अणु
		हाल USB_STOR_XFER_GOOD:	वापस 0;
		हाल USB_STOR_XFER_STALLED:	वापस -EPIPE;
		शेष:			वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक
sddr09_send_scsi_command(काष्ठा us_data *us,
			 अचिन्हित अक्षर *command,
			 अचिन्हित पूर्णांक command_len) अणु
	वापस sddr09_send_command(us, 0, USB_सूची_OUT, command, command_len);
पूर्ण

#अगर 0
/*
 * Test Unit Ready Command: 12 bytes.
 * byte 0: opcode: 00
 */
अटल पूर्णांक
sddr09_test_unit_पढ़ोy(काष्ठा us_data *us) अणु
	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक result;

	स_रखो(command, 0, 6);
	command[1] = LUNBITS;

	result = sddr09_send_scsi_command(us, command, 6);

	usb_stor_dbg(us, "sddr09_test_unit_ready returns %d\n", result);

	वापस result;
पूर्ण
#पूर्ण_अगर

/*
 * Request Sense Command: 12 bytes.
 * byte 0: opcode: 03
 * byte 4: data length
 */
अटल पूर्णांक
sddr09_request_sense(काष्ठा us_data *us, अचिन्हित अक्षर *sensebuf, पूर्णांक buflen) अणु
	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक result;

	स_रखो(command, 0, 12);
	command[0] = 0x03;
	command[1] = LUNBITS;
	command[4] = buflen;

	result = sddr09_send_scsi_command(us, command, 12);
	अगर (result)
		वापस result;

	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
			sensebuf, buflen, शून्य);
	वापस (result == USB_STOR_XFER_GOOD ? 0 : -EIO);
पूर्ण

/*
 * Read Command: 12 bytes.
 * byte 0: opcode: E8
 * byte 1: last two bits: 00: पढ़ो data, 01: पढ़ो blockwise control,
 *			10: पढ़ो both, 11: पढ़ो pagewise control.
 *	 It turns out we need values 20, 21, 22, 23 here (LUN 1).
 * bytes 2-5: address (पूर्णांकerpretation depends on byte 1, see below)
 * bytes 10-11: count (idem)
 *
 * A page has 512 data bytes and 64 control bytes (16 control and 48 junk).
 * A पढ़ो data command माला_लो data in 512-byte pages.
 * A पढ़ो control command माला_लो control in 64-byte chunks.
 * A पढ़ो both command माला_लो data+control in 576-byte chunks.
 *
 * Blocks are groups of 32 pages, and पढ़ो blockwise control jumps to the
 * next block, जबतक पढ़ो pagewise control jumps to the next page after
 * पढ़ोing a group of 64 control bytes.
 * [Here 512 = 1<<pageshअगरt, 32 = 1<<blockshअगरt, 64 is स्थिरant?]
 *
 * (1 MB and 2 MB cards are a bit dअगरferent, but I have only a 16 MB card.)
 */

अटल पूर्णांक
sddr09_पढ़ोX(काष्ठा us_data *us, पूर्णांक x, अचिन्हित दीर्घ fromaddress,
	     पूर्णांक nr_of_pages, पूर्णांक bulklen, अचिन्हित अक्षर *buf,
	     पूर्णांक use_sg) अणु

	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक result;

	command[0] = 0xE8;
	command[1] = LUNBITS | x;
	command[2] = MSB_of(fromaddress>>16);
	command[3] = LSB_of(fromaddress>>16); 
	command[4] = MSB_of(fromaddress & 0xFFFF);
	command[5] = LSB_of(fromaddress & 0xFFFF); 
	command[6] = 0;
	command[7] = 0;
	command[8] = 0;
	command[9] = 0;
	command[10] = MSB_of(nr_of_pages);
	command[11] = LSB_of(nr_of_pages);

	result = sddr09_send_scsi_command(us, command, 12);

	अगर (result) अणु
		usb_stor_dbg(us, "Result for send_control in sddr09_read2%d %d\n",
			     x, result);
		वापस result;
	पूर्ण

	result = usb_stor_bulk_transfer_sg(us, us->recv_bulk_pipe,
				       buf, bulklen, use_sg, शून्य);

	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Result for bulk_transfer in sddr09_read2%d %d\n",
			     x, result);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Read Data
 *
 * fromaddress counts data लघुs:
 * increasing it by 256 shअगरts the bytestream by 512 bytes;
 * the last 8 bits are ignored.
 *
 * nr_of_pages counts pages of size (1 << pageshअगरt).
 */
अटल पूर्णांक
sddr09_पढ़ो20(काष्ठा us_data *us, अचिन्हित दीर्घ fromaddress,
	      पूर्णांक nr_of_pages, पूर्णांक pageshअगरt, अचिन्हित अक्षर *buf, पूर्णांक use_sg) अणु
	पूर्णांक bulklen = nr_of_pages << pageshअगरt;

	/* The last 8 bits of fromaddress are ignored. */
	वापस sddr09_पढ़ोX(us, 0, fromaddress, nr_of_pages, bulklen,
			    buf, use_sg);
पूर्ण

/*
 * Read Blockwise Control
 *
 * fromaddress gives the starting position (as in पढ़ो data;
 * the last 8 bits are ignored); increasing it by 32*256 shअगरts
 * the output stream by 64 bytes.
 *
 * count counts control groups of size (1 << controlshअगरt).
 * For me, controlshअगरt = 6. Is this स्थिरant?
 *
 * After getting one control group, jump to the next block
 * (fromaddress += 8192).
 */
अटल पूर्णांक
sddr09_पढ़ो21(काष्ठा us_data *us, अचिन्हित दीर्घ fromaddress,
	      पूर्णांक count, पूर्णांक controlshअगरt, अचिन्हित अक्षर *buf, पूर्णांक use_sg) अणु

	पूर्णांक bulklen = (count << controlshअगरt);
	वापस sddr09_पढ़ोX(us, 1, fromaddress, count, bulklen,
			    buf, use_sg);
पूर्ण

/*
 * Read both Data and Control
 *
 * fromaddress counts data लघुs, ignoring control:
 * increasing it by 256 shअगरts the bytestream by 576 = 512+64 bytes;
 * the last 8 bits are ignored.
 *
 * nr_of_pages counts pages of size (1 << pageshअगरt) + (1 << controlshअगरt).
 */
अटल पूर्णांक
sddr09_पढ़ो22(काष्ठा us_data *us, अचिन्हित दीर्घ fromaddress,
	      पूर्णांक nr_of_pages, पूर्णांक pageshअगरt, अचिन्हित अक्षर *buf, पूर्णांक use_sg) अणु

	पूर्णांक bulklen = (nr_of_pages << pageshअगरt) + (nr_of_pages << CONTROL_SHIFT);
	usb_stor_dbg(us, "reading %d pages, %d bytes\n", nr_of_pages, bulklen);
	वापस sddr09_पढ़ोX(us, 2, fromaddress, nr_of_pages, bulklen,
			    buf, use_sg);
पूर्ण

#अगर 0
/*
 * Read Pagewise Control
 *
 * fromaddress gives the starting position (as in पढ़ो data;
 * the last 8 bits are ignored); increasing it by 256 shअगरts
 * the output stream by 64 bytes.
 *
 * count counts control groups of size (1 << controlshअगरt).
 * For me, controlshअगरt = 6. Is this स्थिरant?
 *
 * After getting one control group, jump to the next page
 * (fromaddress += 256).
 */
अटल पूर्णांक
sddr09_पढ़ो23(काष्ठा us_data *us, अचिन्हित दीर्घ fromaddress,
	      पूर्णांक count, पूर्णांक controlshअगरt, अचिन्हित अक्षर *buf, पूर्णांक use_sg) अणु

	पूर्णांक bulklen = (count << controlshअगरt);
	वापस sddr09_पढ़ोX(us, 3, fromaddress, count, bulklen,
			    buf, use_sg);
पूर्ण
#पूर्ण_अगर

/*
 * Erase Command: 12 bytes.
 * byte 0: opcode: EA
 * bytes 6-9: erase address (big-endian, counting लघुs, sector aligned).
 * 
 * Always precisely one block is erased; bytes 2-5 and 10-11 are ignored.
 * The byte address being erased is 2*Eaddress.
 * The CIS cannot be erased.
 */
अटल पूर्णांक
sddr09_erase(काष्ठा us_data *us, अचिन्हित दीर्घ Eaddress) अणु
	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक result;

	usb_stor_dbg(us, "erase address %lu\n", Eaddress);

	स_रखो(command, 0, 12);
	command[0] = 0xEA;
	command[1] = LUNBITS;
	command[6] = MSB_of(Eaddress>>16);
	command[7] = LSB_of(Eaddress>>16);
	command[8] = MSB_of(Eaddress & 0xFFFF);
	command[9] = LSB_of(Eaddress & 0xFFFF);

	result = sddr09_send_scsi_command(us, command, 12);

	अगर (result)
		usb_stor_dbg(us, "Result for send_control in sddr09_erase %d\n",
			     result);

	वापस result;
पूर्ण

/*
 * Write CIS Command: 12 bytes.
 * byte 0: opcode: EE
 * bytes 2-5: ग_लिखो address in लघुs
 * bytes 10-11: sector count
 *
 * This ग_लिखोs at the indicated address. Don't know how it dअगरfers
 * from E9. Maybe it करोes not erase? However, it will also ग_लिखो to
 * the CIS.
 *
 * When two such commands on the same page follow each other directly,
 * the second one is not करोne.
 */

/*
 * Write Command: 12 bytes.
 * byte 0: opcode: E9
 * bytes 2-5: ग_लिखो address (big-endian, counting लघुs, sector aligned).
 * bytes 6-9: erase address (big-endian, counting लघुs, sector aligned).
 * bytes 10-11: sector count (big-endian, in 512-byte sectors).
 *
 * If ग_लिखो address equals erase address, the erase is करोne first,
 * otherwise the ग_लिखो is करोne first. When erase address equals zero
 * no erase is करोne?
 */
अटल पूर्णांक
sddr09_ग_लिखोX(काष्ठा us_data *us,
	      अचिन्हित दीर्घ Waddress, अचिन्हित दीर्घ Eaddress,
	      पूर्णांक nr_of_pages, पूर्णांक bulklen, अचिन्हित अक्षर *buf, पूर्णांक use_sg) अणु

	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक result;

	command[0] = 0xE9;
	command[1] = LUNBITS;

	command[2] = MSB_of(Waddress>>16);
	command[3] = LSB_of(Waddress>>16);
	command[4] = MSB_of(Waddress & 0xFFFF);
	command[5] = LSB_of(Waddress & 0xFFFF);

	command[6] = MSB_of(Eaddress>>16);
	command[7] = LSB_of(Eaddress>>16);
	command[8] = MSB_of(Eaddress & 0xFFFF);
	command[9] = LSB_of(Eaddress & 0xFFFF);

	command[10] = MSB_of(nr_of_pages);
	command[11] = LSB_of(nr_of_pages);

	result = sddr09_send_scsi_command(us, command, 12);

	अगर (result) अणु
		usb_stor_dbg(us, "Result for send_control in sddr09_writeX %d\n",
			     result);
		वापस result;
	पूर्ण

	result = usb_stor_bulk_transfer_sg(us, us->send_bulk_pipe,
				       buf, bulklen, use_sg, शून्य);

	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Result for bulk_transfer in sddr09_writeX %d\n",
			     result);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* erase address, ग_लिखो same address */
अटल पूर्णांक
sddr09_ग_लिखो_inplace(काष्ठा us_data *us, अचिन्हित दीर्घ address,
		     पूर्णांक nr_of_pages, पूर्णांक pageshअगरt, अचिन्हित अक्षर *buf,
		     पूर्णांक use_sg) अणु
	पूर्णांक bulklen = (nr_of_pages << pageshअगरt) + (nr_of_pages << CONTROL_SHIFT);
	वापस sddr09_ग_लिखोX(us, address, address, nr_of_pages, bulklen,
			     buf, use_sg);
पूर्ण

#अगर 0
/*
 * Read Scatter Gather Command: 3+4n bytes.
 * byte 0: opcode E7
 * byte 2: n
 * bytes 4i-1,4i,4i+1: page address
 * byte 4i+2: page count
 * (i=1..n)
 *
 * This पढ़ोs several pages from the card to a single memory buffer.
 * The last two bits of byte 1 have the same meaning as क्रम E8.
 */
अटल पूर्णांक
sddr09_पढ़ो_sg_test_only(काष्ठा us_data *us) अणु
	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक result, bulklen, nsg, ct;
	अचिन्हित अक्षर *buf;
	अचिन्हित दीर्घ address;

	nsg = bulklen = 0;
	command[0] = 0xE7;
	command[1] = LUNBITS;
	command[2] = 0;
	address = 040000; ct = 1;
	nsg++;
	bulklen += (ct << 9);
	command[4*nsg+2] = ct;
	command[4*nsg+1] = ((address >> 9) & 0xFF);
	command[4*nsg+0] = ((address >> 17) & 0xFF);
	command[4*nsg-1] = ((address >> 25) & 0xFF);

	address = 0340000; ct = 1;
	nsg++;
	bulklen += (ct << 9);
	command[4*nsg+2] = ct;
	command[4*nsg+1] = ((address >> 9) & 0xFF);
	command[4*nsg+0] = ((address >> 17) & 0xFF);
	command[4*nsg-1] = ((address >> 25) & 0xFF);

	address = 01000000; ct = 2;
	nsg++;
	bulklen += (ct << 9);
	command[4*nsg+2] = ct;
	command[4*nsg+1] = ((address >> 9) & 0xFF);
	command[4*nsg+0] = ((address >> 17) & 0xFF);
	command[4*nsg-1] = ((address >> 25) & 0xFF);

	command[2] = nsg;

	result = sddr09_send_scsi_command(us, command, 4*nsg+3);

	अगर (result) अणु
		usb_stor_dbg(us, "Result for send_control in sddr09_read_sg %d\n",
			     result);
		वापस result;
	पूर्ण

	buf = kदो_स्मृति(bulklen, GFP_NOIO);
	अगर (!buf)
		वापस -ENOMEM;

	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
				       buf, bulklen, शून्य);
	kमुक्त(buf);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Result for bulk_transfer in sddr09_read_sg %d\n",
			     result);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Read Status Command: 12 bytes.
 * byte 0: opcode: EC
 *
 * Returns 64 bytes, all zero except क्रम the first.
 * bit 0: 1: Error
 * bit 5: 1: Suspended
 * bit 6: 1: Ready
 * bit 7: 1: Not ग_लिखो-रक्षित
 */

अटल पूर्णांक
sddr09_पढ़ो_status(काष्ठा us_data *us, अचिन्हित अक्षर *status) अणु

	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *data = us->iobuf;
	पूर्णांक result;

	usb_stor_dbg(us, "Reading status...\n");

	स_रखो(command, 0, 12);
	command[0] = 0xEC;
	command[1] = LUNBITS;

	result = sddr09_send_scsi_command(us, command, 12);
	अगर (result)
		वापस result;

	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
				       data, 64, शून्य);
	*status = data[0];
	वापस (result == USB_STOR_XFER_GOOD ? 0 : -EIO);
पूर्ण

अटल पूर्णांक
sddr09_पढ़ो_data(काष्ठा us_data *us,
		 अचिन्हित दीर्घ address,
		 अचिन्हित पूर्णांक sectors) अणु

	काष्ठा sddr09_card_info *info = (काष्ठा sddr09_card_info *) us->extra;
	अचिन्हित अक्षर *buffer;
	अचिन्हित पूर्णांक lba, maxlba, pba;
	अचिन्हित पूर्णांक page, pages;
	अचिन्हित पूर्णांक len, offset;
	काष्ठा scatterlist *sg;
	पूर्णांक result;

	// Figure out the initial LBA and page
	lba = address >> info->blockshअगरt;
	page = (address & info->blockmask);
	maxlba = info->capacity >> (info->pageshअगरt + info->blockshअगरt);
	अगर (lba >= maxlba)
		वापस -EIO;

	// Since we only पढ़ो in one block at a समय, we have to create
	// a bounce buffer and move the data a piece at a समय between the
	// bounce buffer and the actual transfer buffer.

	len = min(sectors, (अचिन्हित पूर्णांक) info->blocksize) * info->pagesize;
	buffer = kदो_स्मृति(len, GFP_NOIO);
	अगर (!buffer)
		वापस -ENOMEM;

	// This could be made much more efficient by checking क्रम
	// contiguous LBA's. Another exercise left to the student.

	result = 0;
	offset = 0;
	sg = शून्य;

	जबतक (sectors > 0) अणु

		/* Find number of pages we can पढ़ो in this block */
		pages = min(sectors, info->blocksize - page);
		len = pages << info->pageshअगरt;

		/* Not overflowing capacity? */
		अगर (lba >= maxlba) अणु
			usb_stor_dbg(us, "Error: Requested lba %u exceeds maximum %u\n",
				     lba, maxlba);
			result = -EIO;
			अवरोध;
		पूर्ण

		/* Find where this lba lives on disk */
		pba = info->lba_to_pba[lba];

		अगर (pba == UNDEF) अणु	/* this lba was never written */

			usb_stor_dbg(us, "Read %d zero pages (LBA %d) page %d\n",
				     pages, lba, page);

			/*
			 * This is not really an error. It just means
			 * that the block has never been written.
			 * Instead of वापसing an error
			 * it is better to वापस all zero data.
			 */

			स_रखो(buffer, 0, len);

		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "Read %d pages, from PBA %d (LBA %d) page %d\n",
				     pages, pba, lba, page);

			address = ((pba << info->blockshअगरt) + page) << 
				info->pageshअगरt;

			result = sddr09_पढ़ो20(us, address>>1,
					pages, info->pageshअगरt, buffer, 0);
			अगर (result)
				अवरोध;
		पूर्ण

		// Store the data in the transfer buffer
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, TO_XFER_BUF);

		page = 0;
		lba++;
		sectors -= pages;
	पूर्ण

	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल अचिन्हित पूर्णांक
sddr09_find_unused_pba(काष्ठा sddr09_card_info *info, अचिन्हित पूर्णांक lba) अणु
	अटल अचिन्हित पूर्णांक lastpba = 1;
	पूर्णांक zonestart, end, i;

	zonestart = (lba/1000) << 10;
	end = info->capacity >> (info->blockshअगरt + info->pageshअगरt);
	end -= zonestart;
	अगर (end > 1024)
		end = 1024;

	क्रम (i = lastpba+1; i < end; i++) अणु
		अगर (info->pba_to_lba[zonestart+i] == UNDEF) अणु
			lastpba = i;
			वापस zonestart+i;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= lastpba; i++) अणु
		अगर (info->pba_to_lba[zonestart+i] == UNDEF) अणु
			lastpba = i;
			वापस zonestart+i;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
sddr09_ग_लिखो_lba(काष्ठा us_data *us, अचिन्हित पूर्णांक lba,
		 अचिन्हित पूर्णांक page, अचिन्हित पूर्णांक pages,
		 अचिन्हित अक्षर *ptr, अचिन्हित अक्षर *blockbuffer) अणु

	काष्ठा sddr09_card_info *info = (काष्ठा sddr09_card_info *) us->extra;
	अचिन्हित दीर्घ address;
	अचिन्हित पूर्णांक pba, lbap;
	अचिन्हित पूर्णांक pagelen;
	अचिन्हित अक्षर *bptr, *cptr, *xptr;
	अचिन्हित अक्षर ecc[3];
	पूर्णांक i, result;

	lbap = ((lba % 1000) << 1) | 0x1000;
	अगर (parity[MSB_of(lbap) ^ LSB_of(lbap)])
		lbap ^= 1;
	pba = info->lba_to_pba[lba];

	अगर (pba == UNDEF) अणु
		pba = sddr09_find_unused_pba(info, lba);
		अगर (!pba) अणु
			prपूर्णांकk(KERN_WARNING
			       "sddr09_write_lba: Out of unused blocks\n");
			वापस -ENOSPC;
		पूर्ण
		info->pba_to_lba[pba] = lba;
		info->lba_to_pba[lba] = pba;
	पूर्ण

	अगर (pba == 1) अणु
		/*
		 * Maybe it is impossible to ग_लिखो to PBA 1.
		 * Fake success, but करोn't करो anything.
		 */
		prपूर्णांकk(KERN_WARNING "sddr09: avoid writing to pba 1\n");
		वापस 0;
	पूर्ण

	pagelen = (1 << info->pageshअगरt) + (1 << CONTROL_SHIFT);

	/* पढ़ो old contents */
	address = (pba << (info->pageshअगरt + info->blockshअगरt));
	result = sddr09_पढ़ो22(us, address>>1, info->blocksize,
			       info->pageshअगरt, blockbuffer, 0);
	अगर (result)
		वापस result;

	/* check old contents and fill lba */
	क्रम (i = 0; i < info->blocksize; i++) अणु
		bptr = blockbuffer + i*pagelen;
		cptr = bptr + info->pagesize;
		nand_compute_ecc(bptr, ecc);
		अगर (!nand_compare_ecc(cptr+13, ecc)) अणु
			usb_stor_dbg(us, "Warning: bad ecc in page %d- of pba %d\n",
				     i, pba);
			nand_store_ecc(cptr+13, ecc);
		पूर्ण
		nand_compute_ecc(bptr+(info->pagesize / 2), ecc);
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
		bptr = blockbuffer + i*pagelen;
		cptr = bptr + info->pagesize;
		स_नकल(bptr, xptr, info->pagesize);
		xptr += info->pagesize;
		nand_compute_ecc(bptr, ecc);
		nand_store_ecc(cptr+13, ecc);
		nand_compute_ecc(bptr+(info->pagesize / 2), ecc);
		nand_store_ecc(cptr+8, ecc);
	पूर्ण

	usb_stor_dbg(us, "Rewrite PBA %d (LBA %d)\n", pba, lba);

	result = sddr09_ग_लिखो_inplace(us, address>>1, info->blocksize,
				      info->pageshअगरt, blockbuffer, 0);

	usb_stor_dbg(us, "sddr09_write_inplace returns %d\n", result);

#अगर 0
	अणु
		अचिन्हित अक्षर status = 0;
		पूर्णांक result2 = sddr09_पढ़ो_status(us, &status);
		अगर (result2)
			usb_stor_dbg(us, "cannot read status\n");
		अन्यथा अगर (status != 0xc0)
			usb_stor_dbg(us, "status after write: 0x%x\n", status);
	पूर्ण
#पूर्ण_अगर

#अगर 0
	अणु
		पूर्णांक result2 = sddr09_test_unit_पढ़ोy(us);
	पूर्ण
#पूर्ण_अगर

	वापस result;
पूर्ण

अटल पूर्णांक
sddr09_ग_लिखो_data(काष्ठा us_data *us,
		  अचिन्हित दीर्घ address,
		  अचिन्हित पूर्णांक sectors) अणु

	काष्ठा sddr09_card_info *info = (काष्ठा sddr09_card_info *) us->extra;
	अचिन्हित पूर्णांक lba, maxlba, page, pages;
	अचिन्हित पूर्णांक pagelen, blocklen;
	अचिन्हित अक्षर *blockbuffer;
	अचिन्हित अक्षर *buffer;
	अचिन्हित पूर्णांक len, offset;
	काष्ठा scatterlist *sg;
	पूर्णांक result;

	/* Figure out the initial LBA and page */
	lba = address >> info->blockshअगरt;
	page = (address & info->blockmask);
	maxlba = info->capacity >> (info->pageshअगरt + info->blockshअगरt);
	अगर (lba >= maxlba)
		वापस -EIO;

	/*
	 * blockbuffer is used क्रम पढ़ोing in the old data, overwriting
	 * with the new data, and perक्रमming ECC calculations
	 */

	/*
	 * TODO: instead of करोing kदो_स्मृति/kमुक्त क्रम each ग_लिखो,
	 * add a bufferpoपूर्णांकer to the info काष्ठाure
	 */

	pagelen = (1 << info->pageshअगरt) + (1 << CONTROL_SHIFT);
	blocklen = (pagelen << info->blockshअगरt);
	blockbuffer = kदो_स्मृति(blocklen, GFP_NOIO);
	अगर (!blockbuffer)
		वापस -ENOMEM;

	/*
	 * Since we करोn't ग_लिखो the user data directly to the device,
	 * we have to create a bounce buffer and move the data a piece
	 * at a समय between the bounce buffer and the actual transfer buffer.
	 */

	len = min(sectors, (अचिन्हित पूर्णांक) info->blocksize) * info->pagesize;
	buffer = kदो_स्मृति(len, GFP_NOIO);
	अगर (!buffer) अणु
		kमुक्त(blockbuffer);
		वापस -ENOMEM;
	पूर्ण

	result = 0;
	offset = 0;
	sg = शून्य;

	जबतक (sectors > 0) अणु

		/* Write as many sectors as possible in this block */

		pages = min(sectors, info->blocksize - page);
		len = (pages << info->pageshअगरt);

		/* Not overflowing capacity? */
		अगर (lba >= maxlba) अणु
			usb_stor_dbg(us, "Error: Requested lba %u exceeds maximum %u\n",
				     lba, maxlba);
			result = -EIO;
			अवरोध;
		पूर्ण

		/* Get the data from the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, FROM_XFER_BUF);

		result = sddr09_ग_लिखो_lba(us, lba, page, pages,
				buffer, blockbuffer);
		अगर (result)
			अवरोध;

		page = 0;
		lba++;
		sectors -= pages;
	पूर्ण

	kमुक्त(buffer);
	kमुक्त(blockbuffer);

	वापस result;
पूर्ण

अटल पूर्णांक
sddr09_पढ़ो_control(काष्ठा us_data *us,
		अचिन्हित दीर्घ address,
		अचिन्हित पूर्णांक blocks,
		अचिन्हित अक्षर *content,
		पूर्णांक use_sg) अणु

	usb_stor_dbg(us, "Read control address %lu, blocks %d\n",
		     address, blocks);

	वापस sddr09_पढ़ो21(us, address, blocks,
			     CONTROL_SHIFT, content, use_sg);
पूर्ण

/*
 * Read Device ID Command: 12 bytes.
 * byte 0: opcode: ED
 *
 * Returns 2 bytes: Manufacturer ID and Device ID.
 * On more recent cards 3 bytes: the third byte is an option code A5
 * signअगरying that the secret command to पढ़ो an 128-bit ID is available.
 * On still more recent cards 4 bytes: the fourth byte C0 means that
 * a second पढ़ो ID cmd is available.
 */
अटल पूर्णांक
sddr09_पढ़ो_deviceID(काष्ठा us_data *us, अचिन्हित अक्षर *deviceID) अणु
	अचिन्हित अक्षर *command = us->iobuf;
	अचिन्हित अक्षर *content = us->iobuf;
	पूर्णांक result, i;

	स_रखो(command, 0, 12);
	command[0] = 0xED;
	command[1] = LUNBITS;

	result = sddr09_send_scsi_command(us, command, 12);
	अगर (result)
		वापस result;

	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
			content, 64, शून्य);

	क्रम (i = 0; i < 4; i++)
		deviceID[i] = content[i];

	वापस (result == USB_STOR_XFER_GOOD ? 0 : -EIO);
पूर्ण

अटल पूर्णांक
sddr09_get_wp(काष्ठा us_data *us, काष्ठा sddr09_card_info *info) अणु
	पूर्णांक result;
	अचिन्हित अक्षर status;
	स्थिर अक्षर *wp_fmt;

	result = sddr09_पढ़ो_status(us, &status);
	अगर (result) अणु
		usb_stor_dbg(us, "read_status fails\n");
		वापस result;
	पूर्ण
	अगर ((status & 0x80) == 0) अणु
		info->flags |= SDDR09_WP;	/* ग_लिखो रक्षित */
		wp_fmt = " WP";
	पूर्ण अन्यथा अणु
		wp_fmt = "";
	पूर्ण
	usb_stor_dbg(us, "status 0x%02X%s%s%s%s\n", status, wp_fmt,
		     status & 0x40 ? " Ready" : "",
		     status & LUNBITS ? " Suspended" : "",
		     status & 0x01 ? " Error" : "");

	वापस 0;
पूर्ण

#अगर 0
/*
 * Reset Command: 12 bytes.
 * byte 0: opcode: EB
 */
अटल पूर्णांक
sddr09_reset(काष्ठा us_data *us) अणु

	अचिन्हित अक्षर *command = us->iobuf;

	स_रखो(command, 0, 12);
	command[0] = 0xEB;
	command[1] = LUNBITS;

	वापस sddr09_send_scsi_command(us, command, 12);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा nand_flash_dev *
sddr09_get_cardinfo(काष्ठा us_data *us, अचिन्हित अक्षर flags) अणु
	काष्ठा nand_flash_dev *cardinfo;
	अचिन्हित अक्षर deviceID[4];
	अक्षर blurbtxt[256];
	पूर्णांक result;

	usb_stor_dbg(us, "Reading capacity...\n");

	result = sddr09_पढ़ो_deviceID(us, deviceID);

	अगर (result) अणु
		usb_stor_dbg(us, "Result of read_deviceID is %d\n", result);
		prपूर्णांकk(KERN_WARNING "sddr09: could not read card info\n");
		वापस शून्य;
	पूर्ण

	प्र_लिखो(blurbtxt, "sddr09: Found Flash card, ID = %4ph", deviceID);

	/* Byte 0 is the manufacturer */
	प्र_लिखो(blurbtxt + म_माप(blurbtxt),
		": Manuf. %s",
		nand_flash_manufacturer(deviceID[0]));

	/* Byte 1 is the device type */
	cardinfo = nand_find_id(deviceID[1]);
	अगर (cardinfo) अणु
		/*
		 * MB or MiB? It is neither. A 16 MB card has
		 * 17301504 raw bytes, of which 16384000 are
		 * usable क्रम user data.
		 */
		प्र_लिखो(blurbtxt + म_माप(blurbtxt),
			", %d MB", 1<<(cardinfo->chipshअगरt - 20));
	पूर्ण अन्यथा अणु
		प्र_लिखो(blurbtxt + म_माप(blurbtxt),
			", type unrecognized");
	पूर्ण

	/* Byte 2 is code to संकेत availability of 128-bit ID */
	अगर (deviceID[2] == 0xa5) अणु
		प्र_लिखो(blurbtxt + म_माप(blurbtxt),
			", 128-bit ID");
	पूर्ण

	/* Byte 3 announces the availability of another पढ़ो ID command */
	अगर (deviceID[3] == 0xc0) अणु
		प्र_लिखो(blurbtxt + म_माप(blurbtxt),
			", extra cmd");
	पूर्ण

	अगर (flags & SDDR09_WP)
		प्र_लिखो(blurbtxt + म_माप(blurbtxt),
			", WP");

	prपूर्णांकk(KERN_WARNING "%s\n", blurbtxt);

	वापस cardinfo;
पूर्ण

अटल पूर्णांक
sddr09_पढ़ो_map(काष्ठा us_data *us) अणु

	काष्ठा sddr09_card_info *info = (काष्ठा sddr09_card_info *) us->extra;
	पूर्णांक numblocks, alloc_len, alloc_blocks;
	पूर्णांक i, j, result;
	अचिन्हित अक्षर *buffer, *buffer_end, *ptr;
	अचिन्हित पूर्णांक lba, lbact;

	अगर (!info->capacity)
		वापस -1;

	/*
	 * size of a block is 1 << (blockshअगरt + pageshअगरt) bytes
	 * भागide पूर्णांकo the total capacity to get the number of blocks
	 */

	numblocks = info->capacity >> (info->blockshअगरt + info->pageshअगरt);

	/*
	 * पढ़ो 64 bytes क्रम every block (actually 1 << CONTROL_SHIFT)
	 * but only use a 64 KB buffer
	 * buffer size used must be a multiple of (1 << CONTROL_SHIFT)
	 */
#घोषणा SDDR09_READ_MAP_BUFSZ 65536

	alloc_blocks = min(numblocks, SDDR09_READ_MAP_BUFSZ >> CONTROL_SHIFT);
	alloc_len = (alloc_blocks << CONTROL_SHIFT);
	buffer = kदो_स्मृति(alloc_len, GFP_NOIO);
	अगर (!buffer) अणु
		result = -1;
		जाओ करोne;
	पूर्ण
	buffer_end = buffer + alloc_len;

#अघोषित SDDR09_READ_MAP_BUFSZ

	kमुक्त(info->lba_to_pba);
	kमुक्त(info->pba_to_lba);
	info->lba_to_pba = kदो_स्मृति_array(numblocks, माप(पूर्णांक), GFP_NOIO);
	info->pba_to_lba = kदो_स्मृति_array(numblocks, माप(पूर्णांक), GFP_NOIO);

	अगर (info->lba_to_pba == शून्य || info->pba_to_lba == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "sddr09_read_map: out of memory\n");
		result = -1;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < numblocks; i++)
		info->lba_to_pba[i] = info->pba_to_lba[i] = UNDEF;

	/*
	 * Define lba-pba translation table
	 */

	ptr = buffer_end;
	क्रम (i = 0; i < numblocks; i++) अणु
		ptr += (1 << CONTROL_SHIFT);
		अगर (ptr >= buffer_end) अणु
			अचिन्हित दीर्घ address;

			address = i << (info->pageshअगरt + info->blockshअगरt);
			result = sddr09_पढ़ो_control(
				us, address>>1,
				min(alloc_blocks, numblocks - i),
				buffer, 0);
			अगर (result) अणु
				result = -1;
				जाओ करोne;
			पूर्ण
			ptr = buffer;
		पूर्ण

		अगर (i == 0 || i == 1) अणु
			info->pba_to_lba[i] = UNUSABLE;
			जारी;
		पूर्ण

		/* special PBAs have control field 0^16 */
		क्रम (j = 0; j < 16; j++)
			अगर (ptr[j] != 0)
				जाओ nonz;
		info->pba_to_lba[i] = UNUSABLE;
		prपूर्णांकk(KERN_WARNING "sddr09: PBA %d has no logical mapping\n",
		       i);
		जारी;

	nonz:
		/* unwritten PBAs have control field FF^16 */
		क्रम (j = 0; j < 16; j++)
			अगर (ptr[j] != 0xff)
				जाओ nonff;
		जारी;

	nonff:
		/* normal PBAs start with six FFs */
		अगर (j < 6) अणु
			prपूर्णांकk(KERN_WARNING
			       "sddr09: PBA %d has no logical mapping: "
			       "reserved area = %02X%02X%02X%02X "
			       "data status %02X block status %02X\n",
			       i, ptr[0], ptr[1], ptr[2], ptr[3],
			       ptr[4], ptr[5]);
			info->pba_to_lba[i] = UNUSABLE;
			जारी;
		पूर्ण

		अगर ((ptr[6] >> 4) != 0x01) अणु
			prपूर्णांकk(KERN_WARNING
			       "sddr09: PBA %d has invalid address field "
			       "%02X%02X/%02X%02X\n",
			       i, ptr[6], ptr[7], ptr[11], ptr[12]);
			info->pba_to_lba[i] = UNUSABLE;
			जारी;
		पूर्ण

		/* check even parity */
		अगर (parity[ptr[6] ^ ptr[7]]) अणु
			prपूर्णांकk(KERN_WARNING
			       "sddr09: Bad parity in LBA for block %d"
			       " (%02X %02X)\n", i, ptr[6], ptr[7]);
			info->pba_to_lba[i] = UNUSABLE;
			जारी;
		पूर्ण

		lba = लघु_pack(ptr[7], ptr[6]);
		lba = (lba & 0x07FF) >> 1;

		/*
		 * Every 1024 physical blocks ("zone"), the LBA numbers
		 * go back to zero, but are within a higher block of LBA's.
		 * Also, there is a maximum of 1000 LBA's per zone.
		 * In other words, in PBA 1024-2047 you will find LBA 0-999
		 * which are really LBA 1000-1999. This allows क्रम 24 bad
		 * or special physical blocks per zone.
		 */

		अगर (lba >= 1000) अणु
			prपूर्णांकk(KERN_WARNING
			       "sddr09: Bad low LBA %d for block %d\n",
			       lba, i);
			जाओ possibly_erase;
		पूर्ण

		lba += 1000*(i/0x400);

		अगर (info->lba_to_pba[lba] != UNDEF) अणु
			prपूर्णांकk(KERN_WARNING
			       "sddr09: LBA %d seen for PBA %d and %d\n",
			       lba, info->lba_to_pba[lba], i);
			जाओ possibly_erase;
		पूर्ण

		info->pba_to_lba[i] = lba;
		info->lba_to_pba[lba] = i;
		जारी;

	possibly_erase:
		अगर (erase_bad_lba_entries) अणु
			अचिन्हित दीर्घ address;

			address = (i << (info->pageshअगरt + info->blockshअगरt));
			sddr09_erase(us, address>>1);
			info->pba_to_lba[i] = UNDEF;
		पूर्ण अन्यथा
			info->pba_to_lba[i] = UNUSABLE;
	पूर्ण

	/*
	 * Approximate capacity. This is not entirely correct yet,
	 * since a zone with less than 1000 usable pages leads to
	 * missing LBAs. Especially अगर it is the last zone, some
	 * LBAs can be past capacity.
	 */
	lbact = 0;
	क्रम (i = 0; i < numblocks; i += 1024) अणु
		पूर्णांक ct = 0;

		क्रम (j = 0; j < 1024 && i+j < numblocks; j++) अणु
			अगर (info->pba_to_lba[i+j] != UNUSABLE) अणु
				अगर (ct >= 1000)
					info->pba_to_lba[i+j] = SPARE;
				अन्यथा
					ct++;
			पूर्ण
		पूर्ण
		lbact += ct;
	पूर्ण
	info->lbact = lbact;
	usb_stor_dbg(us, "Found %d LBA's\n", lbact);
	result = 0;

 करोne:
	अगर (result != 0) अणु
		kमुक्त(info->lba_to_pba);
		kमुक्त(info->pba_to_lba);
		info->lba_to_pba = शून्य;
		info->pba_to_lba = शून्य;
	पूर्ण
	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल व्योम
sddr09_card_info_deकाष्ठाor(व्योम *extra) अणु
	काष्ठा sddr09_card_info *info = (काष्ठा sddr09_card_info *)extra;

	अगर (!info)
		वापस;

	kमुक्त(info->lba_to_pba);
	kमुक्त(info->pba_to_lba);
पूर्ण

अटल पूर्णांक
sddr09_common_init(काष्ठा us_data *us) अणु
	पूर्णांक result;

	/* set the configuration -- STALL is an acceptable response here */
	अगर (us->pusb_dev->actconfig->desc.bConfigurationValue != 1) अणु
		usb_stor_dbg(us, "active config #%d != 1 ??\n",
			     us->pusb_dev->actconfig->desc.bConfigurationValue);
		वापस -EINVAL;
	पूर्ण

	result = usb_reset_configuration(us->pusb_dev);
	usb_stor_dbg(us, "Result of usb_reset_configuration is %d\n", result);
	अगर (result == -EPIPE) अणु
		usb_stor_dbg(us, "-- stall on control interface\n");
	पूर्ण अन्यथा अगर (result != 0) अणु
		/* it's not a stall, but another error -- समय to bail */
		usb_stor_dbg(us, "-- Unknown error.  Rejecting device\n");
		वापस -EINVAL;
	पूर्ण

	us->extra = kzalloc(माप(काष्ठा sddr09_card_info), GFP_NOIO);
	अगर (!us->extra)
		वापस -ENOMEM;
	us->extra_deकाष्ठाor = sddr09_card_info_deकाष्ठाor;

	nand_init_ecc();
	वापस 0;
पूर्ण


/*
 * This is needed at a very early stage. If this is not listed in the
 * unusual devices list but called from here then LUN 0 of the combo पढ़ोer
 * is not recognized. But I करो not know what precisely these calls करो.
 */
अटल पूर्णांक
usb_stor_sddr09_dpcm_init(काष्ठा us_data *us) अणु
	पूर्णांक result;
	अचिन्हित अक्षर *data = us->iobuf;

	result = sddr09_common_init(us);
	अगर (result)
		वापस result;

	result = sddr09_send_command(us, 0x01, USB_सूची_IN, data, 2);
	अगर (result) अणु
		usb_stor_dbg(us, "send_command fails\n");
		वापस result;
	पूर्ण

	usb_stor_dbg(us, "%02X %02X\n", data[0], data[1]);
	// get 07 02

	result = sddr09_send_command(us, 0x08, USB_सूची_IN, data, 2);
	अगर (result) अणु
		usb_stor_dbg(us, "2nd send_command fails\n");
		वापस result;
	पूर्ण

	usb_stor_dbg(us, "%02X %02X\n", data[0], data[1]);
	// get 07 00

	result = sddr09_request_sense(us, data, 18);
	अगर (result == 0 && data[2] != 0) अणु
		पूर्णांक j;
		क्रम (j=0; j<18; j++)
			prपूर्णांकk(" %02X", data[j]);
		prपूर्णांकk("\n");
		// get 70 00 00 00 00 00 00 * 00 00 00 00 00 00
		// 70: current command
		// sense key 0, sense code 0, extd sense code 0
		// additional transfer length * = माप(data) - 7
		// Or: 70 00 06 00 00 00 00 0b 00 00 00 00 28 00 00 00 00 00
		// sense key 06, sense code 28: unit attention,
		// not पढ़ोy to पढ़ोy transition
	पूर्ण

	// test unit पढ़ोy

	वापस 0;		/* not result */
पूर्ण

/*
 * Transport क्रम the Microtech DPCM-USB
 */
अटल पूर्णांक dpcm_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक ret;

	usb_stor_dbg(us, "LUN=%d\n", (u8)srb->device->lun);

	चयन (srb->device->lun) अणु
	हाल 0:

		/*
		 * LUN 0 corresponds to the CompactFlash card पढ़ोer.
		 */
		ret = usb_stor_CB_transport(srb, us);
		अवरोध;

	हाल 1:

		/*
		 * LUN 1 corresponds to the SmartMedia card पढ़ोer.
		 */

		/*
		 * Set the LUN to 0 (just in हाल).
		 */
		srb->device->lun = 0;
		ret = sddr09_transport(srb, us);
		srb->device->lun = 1;
		अवरोध;

	शेष:
	    usb_stor_dbg(us, "Invalid LUN %d\n", (u8)srb->device->lun);
		ret = USB_STOR_TRANSPORT_ERROR;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण


/*
 * Transport क्रम the Sandisk SDDR-09
 */
अटल पूर्णांक sddr09_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	अटल अचिन्हित अक्षर sensekey = 0, sensecode = 0;
	अटल अचिन्हित अक्षर havefakesense = 0;
	पूर्णांक result, i;
	अचिन्हित अक्षर *ptr = us->iobuf;
	अचिन्हित दीर्घ capacity;
	अचिन्हित पूर्णांक page, pages;

	काष्ठा sddr09_card_info *info;

	अटल अचिन्हित अक्षर inquiry_response[8] = अणु
		0x00, 0x80, 0x00, 0x02, 0x1F, 0x00, 0x00, 0x00
	पूर्ण;

	/* note: no block descriptor support */
	अटल अचिन्हित अक्षर mode_page_01[19] = अणु
		0x00, 0x0F, 0x00, 0x0, 0x0, 0x0, 0x00,
		0x01, 0x0A,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;

	info = (काष्ठा sddr09_card_info *)us->extra;

	अगर (srb->cmnd[0] == REQUEST_SENSE && havefakesense) अणु
		/* क्रम a faked command, we have to follow with a faked sense */
		स_रखो(ptr, 0, 18);
		ptr[0] = 0x70;
		ptr[2] = sensekey;
		ptr[7] = 11;
		ptr[12] = sensecode;
		usb_stor_set_xfer_buf(ptr, 18, srb);
		sensekey = sensecode = havefakesense = 0;
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	havefakesense = 1;

	/*
	 * Dummy up a response क्रम INQUIRY since SDDR09 करोesn't
	 * respond to INQUIRY commands
	 */

	अगर (srb->cmnd[0] == INQUIRY) अणु
		स_नकल(ptr, inquiry_response, 8);
		fill_inquiry_response(us, ptr, 36);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == READ_CAPACITY) अणु
		काष्ठा nand_flash_dev *cardinfo;

		sddr09_get_wp(us, info);	/* पढ़ो WP bit */

		cardinfo = sddr09_get_cardinfo(us, info->flags);
		अगर (!cardinfo) अणु
			/* probably no media */
		init_error:
			sensekey = 0x02;	/* not पढ़ोy */
			sensecode = 0x3a;	/* medium not present */
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण

		info->capacity = (1 << cardinfo->chipshअगरt);
		info->pageshअगरt = cardinfo->pageshअगरt;
		info->pagesize = (1 << info->pageshअगरt);
		info->blockshअगरt = cardinfo->blockshअगरt;
		info->blocksize = (1 << info->blockshअगरt);
		info->blockmask = info->blocksize - 1;

		// map initialization, must follow get_cardinfo()
		अगर (sddr09_पढ़ो_map(us)) अणु
			/* probably out of memory */
			जाओ init_error;
		पूर्ण

		// Report capacity

		capacity = (info->lbact << info->blockshअगरt) - 1;

		((__be32 *) ptr)[0] = cpu_to_be32(capacity);

		// Report page size

		((__be32 *) ptr)[1] = cpu_to_be32(info->pagesize);
		usb_stor_set_xfer_buf(ptr, 8, srb);

		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	अगर (srb->cmnd[0] == MODE_SENSE_10) अणु
		पूर्णांक modepage = (srb->cmnd[2] & 0x3F);

		/*
		 * They ask क्रम the Read/Write error recovery page,
		 * or क्रम all pages.
		 */
		/* %% We should check DBD %% */
		अगर (modepage == 0x01 || modepage == 0x3F) अणु
			usb_stor_dbg(us, "Dummy up request for mode page 0x%x\n",
				     modepage);

			स_नकल(ptr, mode_page_01, माप(mode_page_01));
			((__be16*)ptr)[0] = cpu_to_be16(माप(mode_page_01) - 2);
			ptr[3] = (info->flags & SDDR09_WP) ? 0x80 : 0;
			usb_stor_set_xfer_buf(ptr, माप(mode_page_01), srb);
			वापस USB_STOR_TRANSPORT_GOOD;
		पूर्ण

		sensekey = 0x05;	/* illegal request */
		sensecode = 0x24;	/* invalid field in CDB */
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	अगर (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL)
		वापस USB_STOR_TRANSPORT_GOOD;

	havefakesense = 0;

	अगर (srb->cmnd[0] == READ_10) अणु

		page = लघु_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= लघु_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = लघु_pack(srb->cmnd[8], srb->cmnd[7]);

		usb_stor_dbg(us, "READ_10: read page %d pagect %d\n",
			     page, pages);

		result = sddr09_पढ़ो_data(us, page, pages);
		वापस (result == 0 ? USB_STOR_TRANSPORT_GOOD :
				USB_STOR_TRANSPORT_ERROR);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_10) अणु

		page = लघु_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= लघु_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = लघु_pack(srb->cmnd[8], srb->cmnd[7]);

		usb_stor_dbg(us, "WRITE_10: write page %d pagect %d\n",
			     page, pages);

		result = sddr09_ग_लिखो_data(us, page, pages);
		वापस (result == 0 ? USB_STOR_TRANSPORT_GOOD :
				USB_STOR_TRANSPORT_ERROR);
	पूर्ण

	/*
	 * catch-all क्रम all other commands, except
	 * pass TEST_UNIT_READY and REQUEST_SENSE through
	 */
	अगर (srb->cmnd[0] != TEST_UNIT_READY &&
	    srb->cmnd[0] != REQUEST_SENSE) अणु
		sensekey = 0x05;	/* illegal request */
		sensecode = 0x20;	/* invalid command */
		havefakesense = 1;
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	क्रम (; srb->cmd_len<12; srb->cmd_len++)
		srb->cmnd[srb->cmd_len] = 0;

	srb->cmnd[1] = LUNBITS;

	ptr[0] = 0;
	क्रम (i=0; i<12; i++)
		प्र_लिखो(ptr+म_माप(ptr), "%02X ", srb->cmnd[i]);

	usb_stor_dbg(us, "Send control for command %s\n", ptr);

	result = sddr09_send_scsi_command(us, srb->cmnd, 12);
	अगर (result) अणु
		usb_stor_dbg(us, "sddr09_send_scsi_command returns %d\n",
			     result);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	अगर (scsi_bufflen(srb) == 0)
		वापस USB_STOR_TRANSPORT_GOOD;

	अगर (srb->sc_data_direction == DMA_TO_DEVICE ||
	    srb->sc_data_direction == DMA_FROM_DEVICE) अणु
		अचिन्हित पूर्णांक pipe = (srb->sc_data_direction == DMA_TO_DEVICE)
				? us->send_bulk_pipe : us->recv_bulk_pipe;

		usb_stor_dbg(us, "%s %d bytes\n",
			     (srb->sc_data_direction == DMA_TO_DEVICE) ?
			     "sending" : "receiving",
			     scsi_bufflen(srb));

		result = usb_stor_bulk_srb(us, pipe, srb);

		वापस (result == USB_STOR_XFER_GOOD ?
			USB_STOR_TRANSPORT_GOOD : USB_STOR_TRANSPORT_ERROR);
	पूर्ण 

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Initialization routine क्रम the sddr09 subdriver
 */
अटल पूर्णांक
usb_stor_sddr09_init(काष्ठा us_data *us) अणु
	वापस sddr09_common_init(us);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sddr09_host_ढाँचा;

अटल पूर्णांक sddr09_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - sddr09_usb_ids) + sddr09_unusual_dev_list,
			&sddr09_host_ढाँचा);
	अगर (result)
		वापस result;

	अगर (us->protocol == USB_PR_DPCM_USB) अणु
		us->transport_name = "Control/Bulk-EUSB/SDDR09";
		us->transport = dpcm_transport;
		us->transport_reset = usb_stor_CB_reset;
		us->max_lun = 1;
	पूर्ण अन्यथा अणु
		us->transport_name = "EUSB/SDDR09";
		us->transport = sddr09_transport;
		us->transport_reset = usb_stor_CB_reset;
		us->max_lun = 0;
	पूर्ण

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver sddr09_driver = अणु
	.name =		DRV_NAME,
	.probe =	sddr09_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	sddr09_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(sddr09_driver, sddr09_host_ढाँचा, DRV_NAME);
