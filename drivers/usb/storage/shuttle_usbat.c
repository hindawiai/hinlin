<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम SCM Microप्रणालीs (a.k.a. Shuttle) USB-ATAPI cable
 *
 * Current development and मुख्यtenance by:
 *   (c) 2000, 2001 Robert Baruch (स्वतःphile@starband.net)
 *   (c) 2004, 2005 Daniel Drake <dsd@gentoo.org>
 *
 * Developed with the assistance of:
 *   (c) 2002 Alan Stern <stern@rowland.org>
 *
 * Flash support based on earlier work by:
 *   (c) 2002 Thomas Kreiling <usbdev@sm04.de>
 *
 * Many originally ATAPI devices were slightly modअगरied to meet the USB
 * market by using some kind of translation from ATAPI to USB on the host,
 * and the peripheral would translate from USB back to ATAPI.
 *
 * SCM Microप्रणालीs (www.scmmicro.com) makes a device, sold to OEM's only, 
 * which करोes the USB-to-ATAPI conversion.  By obtaining the data sheet on
 * their device under nondisclosure agreement, I have been able to ग_लिखो
 * this driver क्रम Linux.
 *
 * The chip used in the device can also be used क्रम EPP and ISA translation
 * as well. This driver is only guaranteed to work with the ATAPI
 * translation.
 *
 * See the Kconfig help text क्रम a list of devices known to be supported by
 * this driver.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/cdrom.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-usbat"

MODULE_DESCRIPTION("Driver for SCM Microsystems (a.k.a. Shuttle) USB-ATAPI cable");
MODULE_AUTHOR("Daniel Drake <dsd@gentoo.org>, Robert Baruch <autophile@starband.net>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

/* Supported device types */
#घोषणा USBAT_DEV_HP8200	0x01
#घोषणा USBAT_DEV_FLASH		0x02

#घोषणा USBAT_EPP_PORT		0x10
#घोषणा USBAT_EPP_REGISTER	0x30
#घोषणा USBAT_ATA		0x40
#घोषणा USBAT_ISA		0x50

/* Commands (need to be logically OR'd with an access type */
#घोषणा USBAT_CMD_READ_REG		0x00
#घोषणा USBAT_CMD_WRITE_REG		0x01
#घोषणा USBAT_CMD_READ_BLOCK	0x02
#घोषणा USBAT_CMD_WRITE_BLOCK	0x03
#घोषणा USBAT_CMD_COND_READ_BLOCK	0x04
#घोषणा USBAT_CMD_COND_WRITE_BLOCK	0x05
#घोषणा USBAT_CMD_WRITE_REGS	0x07

/* Commands (these करोn't need an access type) */
#घोषणा USBAT_CMD_EXEC_CMD	0x80
#घोषणा USBAT_CMD_SET_FEAT	0x81
#घोषणा USBAT_CMD_UIO		0x82

/* Methods of accessing UIO रेजिस्टर */
#घोषणा USBAT_UIO_READ	1
#घोषणा USBAT_UIO_WRITE	0

/* Qualअगरier bits */
#घोषणा USBAT_QUAL_FCQ	0x20	/* full compare */
#घोषणा USBAT_QUAL_ALQ	0x10	/* स्वतः load subcount */

/* USBAT Flash Media status types */
#घोषणा USBAT_FLASH_MEDIA_NONE	0
#घोषणा USBAT_FLASH_MEDIA_CF	1

/* USBAT Flash Media change types */
#घोषणा USBAT_FLASH_MEDIA_SAME	0
#घोषणा USBAT_FLASH_MEDIA_CHANGED	1

/* USBAT ATA रेजिस्टरs */
#घोषणा USBAT_ATA_DATA      0x10  /* पढ़ो/ग_लिखो data (R/W) */
#घोषणा USBAT_ATA_FEATURES  0x11  /* set features (W) */
#घोषणा USBAT_ATA_ERROR     0x11  /* error (R) */
#घोषणा USBAT_ATA_SECCNT    0x12  /* sector count (R/W) */
#घोषणा USBAT_ATA_SECNUM    0x13  /* sector number (R/W) */
#घोषणा USBAT_ATA_LBA_ME    0x14  /* cylinder low (R/W) */
#घोषणा USBAT_ATA_LBA_HI    0x15  /* cylinder high (R/W) */
#घोषणा USBAT_ATA_DEVICE    0x16  /* head/device selection (R/W) */
#घोषणा USBAT_ATA_STATUS    0x17  /* device status (R) */
#घोषणा USBAT_ATA_CMD       0x17  /* device command (W) */
#घोषणा USBAT_ATA_ALTSTATUS 0x0E  /* status (no clear IRQ) (R) */

/* USBAT User I/O Data रेजिस्टरs */
#घोषणा USBAT_UIO_EPAD		0x80 /* Enable Peripheral Control Signals */
#घोषणा USBAT_UIO_CDT		0x40 /* Card Detect (Read Only) */
				     /* CDT = ACKD & !UI1 & !UI0 */
#घोषणा USBAT_UIO_1		0x20 /* I/O 1 */
#घोषणा USBAT_UIO_0		0x10 /* I/O 0 */
#घोषणा USBAT_UIO_EPP_ATA	0x08 /* 1=EPP mode, 0=ATA mode */
#घोषणा USBAT_UIO_UI1		0x04 /* Input 1 */
#घोषणा USBAT_UIO_UI0		0x02 /* Input 0 */
#घोषणा USBAT_UIO_INTR_ACK	0x01 /* Interrupt (ATA/ISA)/Acknowledge (EPP) */

/* USBAT User I/O Enable रेजिस्टरs */
#घोषणा USBAT_UIO_DRVRST	0x80 /* Reset Peripheral */
#घोषणा USBAT_UIO_ACKD		0x40 /* Enable Card Detect */
#घोषणा USBAT_UIO_OE1		0x20 /* I/O 1 set=output/clr=input */
				     /* If ACKD=1, set OE1 to 1 also. */
#घोषणा USBAT_UIO_OE0		0x10 /* I/O 0 set=output/clr=input */
#घोषणा USBAT_UIO_ADPRST	0x01 /* Reset SCM chip */

/* USBAT Features */
#घोषणा USBAT_FEAT_ETEN	0x80	/* External trigger enable */
#घोषणा USBAT_FEAT_U1	0x08
#घोषणा USBAT_FEAT_U0	0x04
#घोषणा USBAT_FEAT_ET1	0x02
#घोषणा USBAT_FEAT_ET2	0x01

काष्ठा usbat_info अणु
	पूर्णांक devicetype;

	/* Used क्रम Flash पढ़ोers only */
	अचिन्हित दीर्घ sectors;     /* total sector count */
	अचिन्हित दीर्घ ssize;       /* sector size in bytes */

	अचिन्हित अक्षर sense_key;
	अचिन्हित दीर्घ sense_asc;   /* additional sense code */
	अचिन्हित दीर्घ sense_ascq;  /* additional sense code qualअगरier */
पूर्ण;

#घोषणा लघु_pack(LSB,MSB) ( ((u16)(LSB)) | ( ((u16)(MSB))<<8 ) )
#घोषणा LSB_of(s) ((s)&0xFF)
#घोषणा MSB_of(s) ((s)>>8)

अटल पूर्णांक transferred = 0;

अटल पूर्णांक usbat_flash_transport(काष्ठा scsi_cmnd * srb, काष्ठा us_data *us);
अटल पूर्णांक usbat_hp8200e_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us);

अटल पूर्णांक init_usbat_cd(काष्ठा us_data *us);
अटल पूर्णांक init_usbat_flash(काष्ठा us_data *us);


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id usbat_usb_ids[] = अणु
#	include "unusual_usbat.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, usbat_usb_ids);

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

अटल काष्ठा us_unusual_dev usbat_unusual_dev_list[] = अणु
#	include "unusual_usbat.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV

/*
 * Convenience function to produce an ATA पढ़ो/ग_लिखो sectors command
 * Use cmd=0x20 क्रम पढ़ो, cmd=0x30 क्रम ग_लिखो
 */
अटल व्योम usbat_pack_ata_sector_cmd(अचिन्हित अक्षर *buf,
					अचिन्हित अक्षर thisसमय,
					u32 sector, अचिन्हित अक्षर cmd)
अणु
	buf[0] = 0;
	buf[1] = thisसमय;
	buf[2] = sector & 0xFF;
	buf[3] = (sector >>  8) & 0xFF;
	buf[4] = (sector >> 16) & 0xFF;
	buf[5] = 0xE0 | ((sector >> 24) & 0x0F);
	buf[6] = cmd;
पूर्ण

/*
 * Convenience function to get the device type (flash or hp8200)
 */
अटल पूर्णांक usbat_get_device_type(काष्ठा us_data *us)
अणु
	वापस ((काष्ठा usbat_info*)us->extra)->devicetype;
पूर्ण

/*
 * Read a रेजिस्टर from the device
 */
अटल पूर्णांक usbat_पढ़ो(काष्ठा us_data *us,
		      अचिन्हित अक्षर access,
		      अचिन्हित अक्षर reg,
		      अचिन्हित अक्षर *content)
अणु
	वापस usb_stor_ctrl_transfer(us,
		us->recv_ctrl_pipe,
		access | USBAT_CMD_READ_REG,
		0xC0,
		(u16)reg,
		0,
		content,
		1);
पूर्ण

/*
 * Write to a रेजिस्टर on the device
 */
अटल पूर्णांक usbat_ग_लिखो(काष्ठा us_data *us,
		       अचिन्हित अक्षर access,
		       अचिन्हित अक्षर reg,
		       अचिन्हित अक्षर content)
अणु
	वापस usb_stor_ctrl_transfer(us,
		us->send_ctrl_pipe,
		access | USBAT_CMD_WRITE_REG,
		0x40,
		लघु_pack(reg, content),
		0,
		शून्य,
		0);
पूर्ण

/*
 * Convenience function to perक्रमm a bulk पढ़ो
 */
अटल पूर्णांक usbat_bulk_पढ़ो(काष्ठा us_data *us,
			   व्योम* buf,
			   अचिन्हित पूर्णांक len,
			   पूर्णांक use_sg)
अणु
	अगर (len == 0)
		वापस USB_STOR_XFER_GOOD;

	usb_stor_dbg(us, "len = %d\n", len);
	वापस usb_stor_bulk_transfer_sg(us, us->recv_bulk_pipe, buf, len, use_sg, शून्य);
पूर्ण

/*
 * Convenience function to perक्रमm a bulk ग_लिखो
 */
अटल पूर्णांक usbat_bulk_ग_लिखो(काष्ठा us_data *us,
			    व्योम* buf,
			    अचिन्हित पूर्णांक len,
			    पूर्णांक use_sg)
अणु
	अगर (len == 0)
		वापस USB_STOR_XFER_GOOD;

	usb_stor_dbg(us, "len = %d\n", len);
	वापस usb_stor_bulk_transfer_sg(us, us->send_bulk_pipe, buf, len, use_sg, शून्य);
पूर्ण

/*
 * Some USBAT-specअगरic commands can only be executed over a command transport
 * This transport allows one (len=8) or two (len=16) venकरोr-specअगरic commands
 * to be executed.
 */
अटल पूर्णांक usbat_execute_command(काष्ठा us_data *us,
								 अचिन्हित अक्षर *commands,
								 अचिन्हित पूर्णांक len)
अणु
	वापस usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
								  USBAT_CMD_EXEC_CMD, 0x40, 0, 0,
								  commands, len);
पूर्ण

/*
 * Read the status रेजिस्टर
 */
अटल पूर्णांक usbat_get_status(काष्ठा us_data *us, अचिन्हित अक्षर *status)
अणु
	पूर्णांक rc;
	rc = usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_STATUS, status);

	usb_stor_dbg(us, "0x%02X\n", *status);
	वापस rc;
पूर्ण

/*
 * Check the device status
 */
अटल पूर्णांक usbat_check_status(काष्ठा us_data *us)
अणु
	अचिन्हित अक्षर *reply = us->iobuf;
	पूर्णांक rc;

	rc = usbat_get_status(us, reply);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_FAILED;

	/* error/check condition (0x51 is ok) */
	अगर (*reply & 0x01 && *reply != 0x51)
		वापस USB_STOR_TRANSPORT_FAILED;

	/* device fault */
	अगर (*reply & 0x20)
		वापस USB_STOR_TRANSPORT_FAILED;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Stores critical inक्रमmation in पूर्णांकernal रेजिस्टरs in preparation क्रम the execution
 * of a conditional usbat_पढ़ो_blocks or usbat_ग_लिखो_blocks call.
 */
अटल पूर्णांक usbat_set_shuttle_features(काष्ठा us_data *us,
				      अचिन्हित अक्षर बाह्यal_trigger,
				      अचिन्हित अक्षर epp_control,
				      अचिन्हित अक्षर mask_byte,
				      अचिन्हित अक्षर test_pattern,
				      अचिन्हित अक्षर subcountH,
				      अचिन्हित अक्षर subcountL)
अणु
	अचिन्हित अक्षर *command = us->iobuf;

	command[0] = 0x40;
	command[1] = USBAT_CMD_SET_FEAT;

	/*
	 * The only bit relevant to ATA access is bit 6
	 * which defines 8 bit data access (set) or 16 bit (unset)
	 */
	command[2] = epp_control;

	/*
	 * If FCQ is set in the qualअगरier (defined in R/W cmd), then bits U0, U1,
	 * ET1 and ET2 define an बाह्यal event to be checked क्रम on event of a
	 * _पढ़ो_blocks or _ग_लिखो_blocks operation. The पढ़ो/ग_लिखो will not take
	 * place unless the defined trigger संकेत is active.
	 */
	command[3] = बाह्यal_trigger;

	/*
	 * The resultant byte of the mask operation (see mask_byte) is compared क्रम
	 * equivalence with this test pattern. If equal, the पढ़ो/ग_लिखो will take
	 * place.
	 */
	command[4] = test_pattern;

	/*
	 * This value is logically ANDed with the status रेजिस्टर field specअगरied
	 * in the पढ़ो/ग_लिखो command.
	 */
	command[5] = mask_byte;

	/*
	 * If ALQ is set in the qualअगरier, this field contains the address of the
	 * रेजिस्टरs where the byte count should be पढ़ो क्रम transferring the data.
	 * If ALQ is not set, then this field contains the number of bytes to be
	 * transferred.
	 */
	command[6] = subcountL;
	command[7] = subcountH;

	वापस usbat_execute_command(us, command, 8);
पूर्ण

/*
 * Block, रुकोing क्रम an ATA device to become not busy or to report
 * an error condition.
 */
अटल पूर्णांक usbat_रुको_not_busy(काष्ठा us_data *us, पूर्णांक minutes)
अणु
	पूर्णांक i;
	पूर्णांक result;
	अचिन्हित अक्षर *status = us->iobuf;

	/*
	 * Synchronizing cache on a CDR could take a heck of a दीर्घ समय,
	 * but probably not more than 10 minutes or so. On the other hand,
	 * करोing a full blank on a CDRW at speed 1 will take about 75
	 * minutes!
	 */

	क्रम (i=0; i<1200+minutes*60; i++) अणु

 		result = usbat_get_status(us, status);

		अगर (result!=USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;
		अगर (*status & 0x01) अणु /* check condition */
			result = usbat_पढ़ो(us, USBAT_ATA, 0x10, status);
			वापस USB_STOR_TRANSPORT_FAILED;
		पूर्ण
		अगर (*status & 0x20) /* device fault */
			वापस USB_STOR_TRANSPORT_FAILED;

		अगर ((*status & 0x80)==0x00) अणु /* not busy */
			usb_stor_dbg(us, "Waited not busy for %d steps\n", i);
			वापस USB_STOR_TRANSPORT_GOOD;
		पूर्ण

		अगर (i<500)
			msleep(10); /* 5 seconds */
		अन्यथा अगर (i<700)
			msleep(50); /* 10 seconds */
		अन्यथा अगर (i<1200)
			msleep(100); /* 50 seconds */
		अन्यथा
			msleep(1000); /* X minutes */
	पूर्ण

	usb_stor_dbg(us, "Waited not busy for %d minutes, timing out\n",
		     minutes);
	वापस USB_STOR_TRANSPORT_FAILED;
पूर्ण

/*
 * Read block data from the data रेजिस्टर
 */
अटल पूर्णांक usbat_पढ़ो_block(काष्ठा us_data *us,
			    व्योम* buf,
			    अचिन्हित लघु len,
			    पूर्णांक use_sg)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *command = us->iobuf;

	अगर (!len)
		वापस USB_STOR_TRANSPORT_GOOD;

	command[0] = 0xC0;
	command[1] = USBAT_ATA | USBAT_CMD_READ_BLOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;
	command[6] = LSB_of(len);
	command[7] = MSB_of(len);

	result = usbat_execute_command(us, command, 8);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	result = usbat_bulk_पढ़ो(us, buf, len, use_sg);
	वापस (result == USB_STOR_XFER_GOOD ?
			USB_STOR_TRANSPORT_GOOD : USB_STOR_TRANSPORT_ERROR);
पूर्ण

/*
 * Write block data via the data रेजिस्टर
 */
अटल पूर्णांक usbat_ग_लिखो_block(काष्ठा us_data *us,
			     अचिन्हित अक्षर access,
			     व्योम* buf,
			     अचिन्हित लघु len,
			     पूर्णांक minutes,
			     पूर्णांक use_sg)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *command = us->iobuf;

	अगर (!len)
		वापस USB_STOR_TRANSPORT_GOOD;

	command[0] = 0x40;
	command[1] = access | USBAT_CMD_WRITE_BLOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;
	command[6] = LSB_of(len);
	command[7] = MSB_of(len);

	result = usbat_execute_command(us, command, 8);

	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	result = usbat_bulk_ग_लिखो(us, buf, len, use_sg);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस usbat_रुको_not_busy(us, minutes);
पूर्ण

/*
 * Process पढ़ो and ग_लिखो requests
 */
अटल पूर्णांक usbat_hp8200e_rw_block_test(काष्ठा us_data *us,
				       अचिन्हित अक्षर access,
				       अचिन्हित अक्षर *रेजिस्टरs,
				       अचिन्हित अक्षर *data_out,
				       अचिन्हित लघु num_रेजिस्टरs,
				       अचिन्हित अक्षर data_reg,
				       अचिन्हित अक्षर status_reg,
				       अचिन्हित अक्षर समयout,
				       अचिन्हित अक्षर qualअगरier,
				       पूर्णांक direction,
				       व्योम *buf,
				       अचिन्हित लघु len,
				       पूर्णांक use_sg,
				       पूर्णांक minutes)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक pipe = (direction == DMA_FROM_DEVICE) ?
			us->recv_bulk_pipe : us->send_bulk_pipe;

	अचिन्हित अक्षर *command = us->iobuf;
	पूर्णांक i, j;
	पूर्णांक cmdlen;
	अचिन्हित अक्षर *data = us->iobuf;
	अचिन्हित अक्षर *status = us->iobuf;

	BUG_ON(num_रेजिस्टरs > US_IOBUF_SIZE/2);

	क्रम (i=0; i<20; i++) अणु

		/*
		 * The first समय we send the full command, which consists
		 * of करोwnloading the SCSI command followed by करोwnloading
		 * the data via a ग_लिखो-and-test.  Any other समय we only
		 * send the command to करोwnload the data -- the SCSI command
		 * is still 'active' in some sense in the device.
		 * 
		 * We're only going to try sending the data 10 बार. After
		 * that, we just वापस a failure.
		 */

		अगर (i==0) अणु
			cmdlen = 16;
			/*
			 * Write to multiple रेजिस्टरs
			 * Not really sure the 0x07, 0x17, 0xfc, 0xe7 is
			 * necessary here, but that's what came out of the
			 * trace every single समय.
			 */
			command[0] = 0x40;
			command[1] = access | USBAT_CMD_WRITE_REGS;
			command[2] = 0x07;
			command[3] = 0x17;
			command[4] = 0xFC;
			command[5] = 0xE7;
			command[6] = LSB_of(num_रेजिस्टरs*2);
			command[7] = MSB_of(num_रेजिस्टरs*2);
		पूर्ण अन्यथा
			cmdlen = 8;

		/* Conditionally पढ़ो or ग_लिखो blocks */
		command[cmdlen-8] = (direction==DMA_TO_DEVICE ? 0x40 : 0xC0);
		command[cmdlen-7] = access |
				(direction==DMA_TO_DEVICE ?
				 USBAT_CMD_COND_WRITE_BLOCK : USBAT_CMD_COND_READ_BLOCK);
		command[cmdlen-6] = data_reg;
		command[cmdlen-5] = status_reg;
		command[cmdlen-4] = समयout;
		command[cmdlen-3] = qualअगरier;
		command[cmdlen-2] = LSB_of(len);
		command[cmdlen-1] = MSB_of(len);

		result = usbat_execute_command(us, command, cmdlen);

		अगर (result != USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (i==0) अणु

			क्रम (j=0; j<num_रेजिस्टरs; j++) अणु
				data[j<<1] = रेजिस्टरs[j];
				data[1+(j<<1)] = data_out[j];
			पूर्ण

			result = usbat_bulk_ग_लिखो(us, data, num_रेजिस्टरs*2, 0);
			अगर (result != USB_STOR_XFER_GOOD)
				वापस USB_STOR_TRANSPORT_ERROR;

		पूर्ण

		result = usb_stor_bulk_transfer_sg(us,
			pipe, buf, len, use_sg, शून्य);

		/*
		 * If we get a stall on the bulk करोwnload, we'll retry
		 * the bulk करोwnload -- but not the SCSI command because
		 * in some sense the SCSI command is still 'active' and
		 * रुकोing क्रम the data. Don't ask me why this should be;
		 * I'm only following what the Winकरोze driver did.
		 *
		 * Note that a stall क्रम the test-and-पढ़ो/ग_लिखो command means
		 * that the test failed. In this हाल we're testing to make
		 * sure that the device is error-मुक्त
		 * (i.e. bit 0 -- CHK -- of status is 0). The most likely
		 * hypothesis is that the USBAT chip somehow knows what
		 * the device will accept, but करोesn't give the device any
		 * data until all data is received. Thus, the device would
		 * still be रुकोing क्रम the first byte of data अगर a stall
		 * occurs, even अगर the stall implies that some data was
		 * transferred.
		 */

		अगर (result == USB_STOR_XFER_SHORT ||
				result == USB_STOR_XFER_STALLED) अणु

			/*
			 * If we're पढ़ोing and we stalled, then clear
			 * the bulk output pipe only the first समय.
			 */

			अगर (direction==DMA_FROM_DEVICE && i==0) अणु
				अगर (usb_stor_clear_halt(us,
						us->send_bulk_pipe) < 0)
					वापस USB_STOR_TRANSPORT_ERROR;
			पूर्ण

			/*
			 * Read status: is the device angry, or just busy?
			 */

 			result = usbat_पढ़ो(us, USBAT_ATA, 
				direction==DMA_TO_DEVICE ?
					USBAT_ATA_STATUS : USBAT_ATA_ALTSTATUS,
				status);

			अगर (result!=USB_STOR_XFER_GOOD)
				वापस USB_STOR_TRANSPORT_ERROR;
			अगर (*status & 0x01) /* check condition */
				वापस USB_STOR_TRANSPORT_FAILED;
			अगर (*status & 0x20) /* device fault */
				वापस USB_STOR_TRANSPORT_FAILED;

			usb_stor_dbg(us, "Redoing %s\n",
				     direction == DMA_TO_DEVICE
				     ? "write" : "read");

		पूर्ण अन्यथा अगर (result != USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;
		अन्यथा
			वापस usbat_रुको_not_busy(us, minutes);

	पूर्ण

	usb_stor_dbg(us, "Bummer! %s bulk data 20 times failed\n",
		     direction == DMA_TO_DEVICE ? "Writing" : "Reading");

	वापस USB_STOR_TRANSPORT_FAILED;
पूर्ण

/*
 * Write to multiple रेजिस्टरs:
 * Allows us to ग_लिखो specअगरic data to any रेजिस्टरs. The data to be written
 * माला_लो packed in this sequence: reg0, data0, reg1, data1, ..., regN, dataN
 * which माला_लो sent through bulk out.
 * Not deचिन्हित क्रम large transfers of data!
 */
अटल पूर्णांक usbat_multiple_ग_लिखो(काष्ठा us_data *us,
				अचिन्हित अक्षर *रेजिस्टरs,
				अचिन्हित अक्षर *data_out,
				अचिन्हित लघु num_रेजिस्टरs)
अणु
	पूर्णांक i, result;
	अचिन्हित अक्षर *data = us->iobuf;
	अचिन्हित अक्षर *command = us->iobuf;

	BUG_ON(num_रेजिस्टरs > US_IOBUF_SIZE/2);

	/* Write to multiple रेजिस्टरs, ATA access */
	command[0] = 0x40;
	command[1] = USBAT_ATA | USBAT_CMD_WRITE_REGS;

	/* No relevance */
	command[2] = 0;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;

	/* Number of bytes to be transferred (incl. addresses and data) */
	command[6] = LSB_of(num_रेजिस्टरs*2);
	command[7] = MSB_of(num_रेजिस्टरs*2);

	/* The setup command */
	result = usbat_execute_command(us, command, 8);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* Create the reg/data, reg/data sequence */
	क्रम (i=0; i<num_रेजिस्टरs; i++) अणु
		data[i<<1] = रेजिस्टरs[i];
		data[1+(i<<1)] = data_out[i];
	पूर्ण

	/* Send the data */
	result = usbat_bulk_ग_लिखो(us, data, num_रेजिस्टरs*2, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (usbat_get_device_type(us) == USBAT_DEV_HP8200)
		वापस usbat_रुको_not_busy(us, 0);
	अन्यथा
		वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Conditionally पढ़ो blocks from device:
 * Allows us to पढ़ो blocks from a specअगरic data रेजिस्टर, based upon the
 * condition that a status रेजिस्टर can be successfully masked with a status
 * qualअगरier. If this condition is not initially met, the पढ़ो will रुको
 * up until a maximum amount of समय has elapsed, as specअगरied by समयout.
 * The पढ़ो will start when the condition is met, otherwise the command पातs.
 *
 * The qualअगरier defined here is not the value that is masked, it defines
 * conditions क्रम the ग_लिखो to take place. The actual masked qualअगरier (and
 * other related details) are defined beक्रमehand with _set_shuttle_features().
 */
अटल पूर्णांक usbat_पढ़ो_blocks(काष्ठा us_data *us,
			     व्योम* buffer,
			     पूर्णांक len,
			     पूर्णांक use_sg)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *command = us->iobuf;

	command[0] = 0xC0;
	command[1] = USBAT_ATA | USBAT_CMD_COND_READ_BLOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = USBAT_ATA_STATUS;
	command[4] = 0xFD; /* Timeout (ms); */
	command[5] = USBAT_QUAL_FCQ;
	command[6] = LSB_of(len);
	command[7] = MSB_of(len);

	/* Multiple block पढ़ो setup command */
	result = usbat_execute_command(us, command, 8);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_FAILED;
	
	/* Read the blocks we just asked क्रम */
	result = usbat_bulk_पढ़ो(us, buffer, len, use_sg);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_FAILED;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Conditionally ग_लिखो blocks to device:
 * Allows us to ग_लिखो blocks to a specअगरic data रेजिस्टर, based upon the
 * condition that a status रेजिस्टर can be successfully masked with a status
 * qualअगरier. If this condition is not initially met, the ग_लिखो will रुको
 * up until a maximum amount of समय has elapsed, as specअगरied by समयout.
 * The पढ़ो will start when the condition is met, otherwise the command पातs.
 *
 * The qualअगरier defined here is not the value that is masked, it defines
 * conditions क्रम the ग_लिखो to take place. The actual masked qualअगरier (and
 * other related details) are defined beक्रमehand with _set_shuttle_features().
 */
अटल पूर्णांक usbat_ग_लिखो_blocks(काष्ठा us_data *us,
			      व्योम* buffer,
			      पूर्णांक len,
			      पूर्णांक use_sg)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *command = us->iobuf;

	command[0] = 0x40;
	command[1] = USBAT_ATA | USBAT_CMD_COND_WRITE_BLOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = USBAT_ATA_STATUS;
	command[4] = 0xFD; /* Timeout (ms) */
	command[5] = USBAT_QUAL_FCQ;
	command[6] = LSB_of(len);
	command[7] = MSB_of(len);

	/* Multiple block ग_लिखो setup command */
	result = usbat_execute_command(us, command, 8);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_FAILED;
	
	/* Write the data */
	result = usbat_bulk_ग_लिखो(us, buffer, len, use_sg);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_FAILED;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Read the User IO रेजिस्टर
 */
अटल पूर्णांक usbat_पढ़ो_user_io(काष्ठा us_data *us, अचिन्हित अक्षर *data_flags)
अणु
	पूर्णांक result;

	result = usb_stor_ctrl_transfer(us,
		us->recv_ctrl_pipe,
		USBAT_CMD_UIO,
		0xC0,
		0,
		0,
		data_flags,
		USBAT_UIO_READ);

	usb_stor_dbg(us, "UIO register reads %02X\n", *data_flags);

	वापस result;
पूर्ण

/*
 * Write to the User IO रेजिस्टर
 */
अटल पूर्णांक usbat_ग_लिखो_user_io(काष्ठा us_data *us,
			       अचिन्हित अक्षर enable_flags,
			       अचिन्हित अक्षर data_flags)
अणु
	वापस usb_stor_ctrl_transfer(us,
		us->send_ctrl_pipe,
		USBAT_CMD_UIO,
		0x40,
		लघु_pack(enable_flags, data_flags),
		0,
		शून्य,
		USBAT_UIO_WRITE);
पूर्ण

/*
 * Reset the device
 * Often needed on media change.
 */
अटल पूर्णांक usbat_device_reset(काष्ठा us_data *us)
अणु
	पूर्णांक rc;

	/*
	 * Reset peripheral, enable peripheral control संकेतs
	 * (bring reset संकेत up)
	 */
	rc = usbat_ग_लिखो_user_io(us,
							 USBAT_UIO_DRVRST | USBAT_UIO_OE1 | USBAT_UIO_OE0,
							 USBAT_UIO_EPAD | USBAT_UIO_1);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;
			
	/*
	 * Enable peripheral control संकेतs
	 * (bring reset संकेत करोwn)
	 */
	rc = usbat_ग_लिखो_user_io(us,
							 USBAT_UIO_OE1  | USBAT_UIO_OE0,
							 USBAT_UIO_EPAD | USBAT_UIO_1);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Enable card detect
 */
अटल पूर्णांक usbat_device_enable_cdt(काष्ठा us_data *us)
अणु
	पूर्णांक rc;

	/* Enable peripheral control संकेतs and card detect */
	rc = usbat_ग_लिखो_user_io(us,
							 USBAT_UIO_ACKD | USBAT_UIO_OE1  | USBAT_UIO_OE0,
							 USBAT_UIO_EPAD | USBAT_UIO_1);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Determine अगर media is present.
 */
अटल पूर्णांक usbat_flash_check_media_present(काष्ठा us_data *us,
					   अचिन्हित अक्षर *uio)
अणु
	अगर (*uio & USBAT_UIO_UI0) अणु
		usb_stor_dbg(us, "no media detected\n");
		वापस USBAT_FLASH_MEDIA_NONE;
	पूर्ण

	वापस USBAT_FLASH_MEDIA_CF;
पूर्ण

/*
 * Determine अगर media has changed since last operation
 */
अटल पूर्णांक usbat_flash_check_media_changed(काष्ठा us_data *us,
					   अचिन्हित अक्षर *uio)
अणु
	अगर (*uio & USBAT_UIO_0) अणु
		usb_stor_dbg(us, "media change detected\n");
		वापस USBAT_FLASH_MEDIA_CHANGED;
	पूर्ण

	वापस USBAT_FLASH_MEDIA_SAME;
पूर्ण

/*
 * Check क्रम media change / no media and handle the situation appropriately
 */
अटल पूर्णांक usbat_flash_check_media(काष्ठा us_data *us,
				   काष्ठा usbat_info *info)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर *uio = us->iobuf;

	rc = usbat_पढ़ो_user_io(us, uio);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* Check क्रम media existence */
	rc = usbat_flash_check_media_present(us, uio);
	अगर (rc == USBAT_FLASH_MEDIA_NONE) अणु
		info->sense_key = 0x02;
		info->sense_asc = 0x3A;
		info->sense_ascq = 0x00;
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	/* Check क्रम media change */
	rc = usbat_flash_check_media_changed(us, uio);
	अगर (rc == USBAT_FLASH_MEDIA_CHANGED) अणु

		/* Reset and re-enable card detect */
		rc = usbat_device_reset(us);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;
		rc = usbat_device_enable_cdt(us);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		msleep(50);

		rc = usbat_पढ़ो_user_io(us, uio);
		अगर (rc != USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;
		
		info->sense_key = UNIT_ATTENTION;
		info->sense_asc = 0x28;
		info->sense_ascq = 0x00;
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Determine whether we are controlling a flash-based पढ़ोer/ग_लिखोr,
 * or a HP8200-based CD drive.
 * Sets transport functions as appropriate.
 */
अटल पूर्णांक usbat_identअगरy_device(काष्ठा us_data *us,
				 काष्ठा usbat_info *info)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर status;

	अगर (!us || !info)
		वापस USB_STOR_TRANSPORT_ERROR;

	rc = usbat_device_reset(us);
	अगर (rc != USB_STOR_TRANSPORT_GOOD)
		वापस rc;
	msleep(500);

	/*
	 * In attempt to distinguish between HP CDRW's and Flash पढ़ोers, we now
	 * execute the IDENTIFY PACKET DEVICE command. On ATA devices (i.e. flash
	 * पढ़ोers), this command should fail with error. On ATAPI devices (i.e.
	 * CDROM drives), it should succeed.
	 */
	rc = usbat_ग_लिखो(us, USBAT_ATA, USBAT_ATA_CMD, 0xA1);
 	अगर (rc != USB_STOR_XFER_GOOD)
 		वापस USB_STOR_TRANSPORT_ERROR;

	rc = usbat_get_status(us, &status);
 	अगर (rc != USB_STOR_XFER_GOOD)
 		वापस USB_STOR_TRANSPORT_ERROR;

	/* Check क्रम error bit, or अगर the command 'fell through' */
	अगर (status == 0xA1 || !(status & 0x01)) अणु
		/* Device is HP 8200 */
		usb_stor_dbg(us, "Detected HP8200 CDRW\n");
		info->devicetype = USBAT_DEV_HP8200;
	पूर्ण अन्यथा अणु
		/* Device is a CompactFlash पढ़ोer/ग_लिखोr */
		usb_stor_dbg(us, "Detected Flash reader/writer\n");
		info->devicetype = USBAT_DEV_FLASH;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Set the transport function based on the device type
 */
अटल पूर्णांक usbat_set_transport(काष्ठा us_data *us,
			       काष्ठा usbat_info *info,
			       पूर्णांक devicetype)
अणु

	अगर (!info->devicetype)
		info->devicetype = devicetype;

	अगर (!info->devicetype)
		usbat_identअगरy_device(us, info);

	चयन (info->devicetype) अणु
	शेष:
		वापस USB_STOR_TRANSPORT_ERROR;

	हाल  USBAT_DEV_HP8200:
		us->transport = usbat_hp8200e_transport;
		अवरोध;

	हाल USBAT_DEV_FLASH:
		us->transport = usbat_flash_transport;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Read the media capacity
 */
अटल पूर्णांक usbat_flash_get_sector_count(काष्ठा us_data *us,
					काष्ठा usbat_info *info)
अणु
	अचिन्हित अक्षर रेजिस्टरs[3] = अणु
		USBAT_ATA_SECCNT,
		USBAT_ATA_DEVICE,
		USBAT_ATA_CMD,
	पूर्ण;
	अचिन्हित अक्षर  command[3] = अणु 0x01, 0xA0, 0xEC पूर्ण;
	अचिन्हित अक्षर *reply;
	अचिन्हित अक्षर status;
	पूर्णांक rc;

	अगर (!us || !info)
		वापस USB_STOR_TRANSPORT_ERROR;

	reply = kदो_स्मृति(512, GFP_NOIO);
	अगर (!reply)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* ATA command : IDENTIFY DEVICE */
	rc = usbat_multiple_ग_लिखो(us, रेजिस्टरs, command, 3);
	अगर (rc != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Gah! identify_device failed\n");
		rc = USB_STOR_TRANSPORT_ERROR;
		जाओ leave;
	पूर्ण

	/* Read device status */
	अगर (usbat_get_status(us, &status) != USB_STOR_XFER_GOOD) अणु
		rc = USB_STOR_TRANSPORT_ERROR;
		जाओ leave;
	पूर्ण

	msleep(100);

	/* Read the device identअगरication data */
	rc = usbat_पढ़ो_block(us, reply, 512, 0);
	अगर (rc != USB_STOR_TRANSPORT_GOOD)
		जाओ leave;

	info->sectors = ((u32)(reply[117]) << 24) |
		((u32)(reply[116]) << 16) |
		((u32)(reply[115]) <<  8) |
		((u32)(reply[114])      );

	rc = USB_STOR_TRANSPORT_GOOD;

 leave:
	kमुक्त(reply);
	वापस rc;
पूर्ण

/*
 * Read data from device
 */
अटल पूर्णांक usbat_flash_पढ़ो_data(काष्ठा us_data *us,
								 काष्ठा usbat_info *info,
								 u32 sector,
								 u32 sectors)
अणु
	अचिन्हित अक्षर रेजिस्टरs[7] = अणु
		USBAT_ATA_FEATURES,
		USBAT_ATA_SECCNT,
		USBAT_ATA_SECNUM,
		USBAT_ATA_LBA_ME,
		USBAT_ATA_LBA_HI,
		USBAT_ATA_DEVICE,
		USBAT_ATA_STATUS,
	पूर्ण;
	अचिन्हित अक्षर command[7];
	अचिन्हित अक्षर *buffer;
	अचिन्हित अक्षर  thisसमय;
	अचिन्हित पूर्णांक totallen, alloclen;
	पूर्णांक len, result;
	अचिन्हित पूर्णांक sg_offset = 0;
	काष्ठा scatterlist *sg = शून्य;

	result = usbat_flash_check_media(us, info);
	अगर (result != USB_STOR_TRANSPORT_GOOD)
		वापस result;

	/*
	 * we're working in LBA mode.  according to the ATA spec,
	 * we can support up to 28-bit addressing.  I करोn't know अगर Jumpshot
	 * supports beyond 24-bit addressing.  It's kind of hard to test
	 * since it requires > 8GB CF card.
	 */

	अगर (sector > 0x0FFFFFFF)
		वापस USB_STOR_TRANSPORT_ERROR;

	totallen = sectors * info->ssize;

	/*
	 * Since we करोn't पढ़ो more than 64 KB at a समय, we have to create
	 * a bounce buffer and move the data a piece at a समय between the
	 * bounce buffer and the actual transfer buffer.
	 */

	alloclen = min(totallen, 65536u);
	buffer = kदो_स्मृति(alloclen, GFP_NOIO);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	करो अणु
		/*
		 * loop, never allocate or transfer more than 64k at once
		 * (min(128k, 255*info->ssize) is the real limit)
		 */
		len = min(totallen, alloclen);
		thisसमय = (len / info->ssize) & 0xff;
 
		/* ATA command 0x20 (READ SECTORS) */
		usbat_pack_ata_sector_cmd(command, thisसमय, sector, 0x20);

		/* Write/execute ATA पढ़ो command */
		result = usbat_multiple_ग_लिखो(us, रेजिस्टरs, command, 7);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			जाओ leave;

		/* Read the data we just requested */
		result = usbat_पढ़ो_blocks(us, buffer, len, 0);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			जाओ leave;
  	 
		usb_stor_dbg(us, "%d bytes\n", len);
	
		/* Store the data in the transfer buffer */
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

/*
 * Write data to device
 */
अटल पूर्णांक usbat_flash_ग_लिखो_data(काष्ठा us_data *us,
								  काष्ठा usbat_info *info,
								  u32 sector,
								  u32 sectors)
अणु
	अचिन्हित अक्षर रेजिस्टरs[7] = अणु
		USBAT_ATA_FEATURES,
		USBAT_ATA_SECCNT,
		USBAT_ATA_SECNUM,
		USBAT_ATA_LBA_ME,
		USBAT_ATA_LBA_HI,
		USBAT_ATA_DEVICE,
		USBAT_ATA_STATUS,
	पूर्ण;
	अचिन्हित अक्षर command[7];
	अचिन्हित अक्षर *buffer;
	अचिन्हित अक्षर  thisसमय;
	अचिन्हित पूर्णांक totallen, alloclen;
	पूर्णांक len, result;
	अचिन्हित पूर्णांक sg_offset = 0;
	काष्ठा scatterlist *sg = शून्य;

	result = usbat_flash_check_media(us, info);
	अगर (result != USB_STOR_TRANSPORT_GOOD)
		वापस result;

	/*
	 * we're working in LBA mode.  according to the ATA spec,
	 * we can support up to 28-bit addressing.  I करोn't know अगर the device
	 * supports beyond 24-bit addressing.  It's kind of hard to test
	 * since it requires > 8GB media.
	 */

	अगर (sector > 0x0FFFFFFF)
		वापस USB_STOR_TRANSPORT_ERROR;

	totallen = sectors * info->ssize;

	/*
	 * Since we करोn't ग_लिखो more than 64 KB at a समय, we have to create
	 * a bounce buffer and move the data a piece at a समय between the
	 * bounce buffer and the actual transfer buffer.
	 */

	alloclen = min(totallen, 65536u);
	buffer = kदो_स्मृति(alloclen, GFP_NOIO);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	करो अणु
		/*
		 * loop, never allocate or transfer more than 64k at once
		 * (min(128k, 255*info->ssize) is the real limit)
		 */
		len = min(totallen, alloclen);
		thisसमय = (len / info->ssize) & 0xff;

		/* Get the data from the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, us->srb,
					 &sg, &sg_offset, FROM_XFER_BUF);

		/* ATA command 0x30 (WRITE SECTORS) */
		usbat_pack_ata_sector_cmd(command, thisसमय, sector, 0x30);

		/* Write/execute ATA ग_लिखो command */
		result = usbat_multiple_ग_लिखो(us, रेजिस्टरs, command, 7);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			जाओ leave;

		/* Write the data */
		result = usbat_ग_लिखो_blocks(us, buffer, len, 0);
		अगर (result != USB_STOR_TRANSPORT_GOOD)
			जाओ leave;

		sector += thisसमय;
		totallen -= len;
	पूर्ण जबतक (totallen > 0);

	kमुक्त(buffer);
	वापस result;

leave:
	kमुक्त(buffer);
	वापस USB_STOR_TRANSPORT_ERROR;
पूर्ण

/*
 * Squeeze a potentially huge (> 65535 byte) पढ़ो10 command पूर्णांकo
 * a little ( <= 65535 byte) ATAPI pipe
 */
अटल पूर्णांक usbat_hp8200e_handle_पढ़ो10(काष्ठा us_data *us,
				       अचिन्हित अक्षर *रेजिस्टरs,
				       अचिन्हित अक्षर *data,
				       काष्ठा scsi_cmnd *srb)
अणु
	पूर्णांक result = USB_STOR_TRANSPORT_GOOD;
	अचिन्हित अक्षर *buffer;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक sector;
	अचिन्हित पूर्णांक sg_offset = 0;
	काष्ठा scatterlist *sg = शून्य;

	usb_stor_dbg(us, "transfersize %d\n", srb->transfersize);

	अगर (scsi_bufflen(srb) < 0x10000) अणु

		result = usbat_hp8200e_rw_block_test(us, USBAT_ATA, 
			रेजिस्टरs, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD,
			(USBAT_QUAL_FCQ | USBAT_QUAL_ALQ),
			DMA_FROM_DEVICE,
			scsi_sglist(srb),
			scsi_bufflen(srb), scsi_sg_count(srb), 1);

		वापस result;
	पूर्ण

	/*
	 * Since we're requesting more data than we can handle in
	 * a single पढ़ो command (max is 64k-1), we will perक्रमm
	 * multiple पढ़ोs, but each पढ़ो must be in multiples of
	 * a sector.  Luckily the sector size is in srb->transfersize
	 * (see linux/drivers/scsi/sr.c).
	 */

	अगर (data[7+0] == GPCMD_READ_CD) अणु
		len = लघु_pack(data[7+9], data[7+8]);
		len <<= 16;
		len |= data[7+7];
		usb_stor_dbg(us, "GPCMD_READ_CD: len %d\n", len);
		srb->transfersize = scsi_bufflen(srb)/len;
	पूर्ण

	अगर (!srb->transfersize)  अणु
		srb->transfersize = 2048; /* A guess */
		usb_stor_dbg(us, "transfersize 0, forcing %d\n",
			     srb->transfersize);
	पूर्ण

	/*
	 * Since we only पढ़ो in one block at a समय, we have to create
	 * a bounce buffer and move the data a piece at a समय between the
	 * bounce buffer and the actual transfer buffer.
	 */

	len = (65535/srb->transfersize) * srb->transfersize;
	usb_stor_dbg(us, "Max read is %d bytes\n", len);
	len = min(len, scsi_bufflen(srb));
	buffer = kदो_स्मृति(len, GFP_NOIO);
	अगर (buffer == शून्य) /* bloody hell! */
		वापस USB_STOR_TRANSPORT_FAILED;
	sector = लघु_pack(data[7+3], data[7+2]);
	sector <<= 16;
	sector |= लघु_pack(data[7+5], data[7+4]);
	transferred = 0;

	जबतक (transferred != scsi_bufflen(srb)) अणु

		अगर (len > scsi_bufflen(srb) - transferred)
			len = scsi_bufflen(srb) - transferred;

		data[3] = len&0xFF; 	  /* (cylL) = expected length (L) */
		data[4] = (len>>8)&0xFF;  /* (cylH) = expected length (H) */

		/* Fix up the SCSI command sector and num sectors */

		data[7+2] = MSB_of(sector>>16); /* SCSI command sector */
		data[7+3] = LSB_of(sector>>16);
		data[7+4] = MSB_of(sector&0xFFFF);
		data[7+5] = LSB_of(sector&0xFFFF);
		अगर (data[7+0] == GPCMD_READ_CD)
			data[7+6] = 0;
		data[7+7] = MSB_of(len / srb->transfersize); /* SCSI command */
		data[7+8] = LSB_of(len / srb->transfersize); /* num sectors */

		result = usbat_hp8200e_rw_block_test(us, USBAT_ATA, 
			रेजिस्टरs, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD, 
			(USBAT_QUAL_FCQ | USBAT_QUAL_ALQ),
			DMA_FROM_DEVICE,
			buffer,
			len, 0, 1);

		अगर (result != USB_STOR_TRANSPORT_GOOD)
			अवरोध;

		/* Store the data in the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, srb,
				 &sg, &sg_offset, TO_XFER_BUF);

		/* Update the amount transferred and the sector number */

		transferred += len;
		sector += len / srb->transfersize;

	पूर्ण /* जबतक transferred != scsi_bufflen(srb) */

	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल पूर्णांक usbat_select_and_test_रेजिस्टरs(काष्ठा us_data *us)
अणु
	पूर्णांक selector;
	अचिन्हित अक्षर *status = us->iobuf;

	/* try device = master, then device = slave. */
	क्रम (selector = 0xA0; selector <= 0xB0; selector += 0x10) अणु
		अगर (usbat_ग_लिखो(us, USBAT_ATA, USBAT_ATA_DEVICE, selector) !=
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_STATUS, status) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_DEVICE, status) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_LBA_HI, status) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_ग_लिखो(us, USBAT_ATA, USBAT_ATA_LBA_ME, 0x55) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_ग_लिखो(us, USBAT_ATA, USBAT_ATA_LBA_HI, 0xAA) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;

		अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
				USB_STOR_XFER_GOOD)
			वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Initialize the USBAT processor and the storage device
 */
अटल पूर्णांक init_usbat(काष्ठा us_data *us, पूर्णांक devicetype)
अणु
	पूर्णांक rc;
	काष्ठा usbat_info *info;
	अचिन्हित अक्षर subcountH = USBAT_ATA_LBA_HI;
	अचिन्हित अक्षर subcountL = USBAT_ATA_LBA_ME;
	अचिन्हित अक्षर *status = us->iobuf;

	us->extra = kzalloc(माप(काष्ठा usbat_info), GFP_NOIO);
	अगर (!us->extra)
		वापस 1;

	info = (काष्ठा usbat_info *) (us->extra);

	/* Enable peripheral control संकेतs */
	rc = usbat_ग_लिखो_user_io(us,
				 USBAT_UIO_OE1 | USBAT_UIO_OE0,
				 USBAT_UIO_EPAD | USBAT_UIO_1);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "INIT 1\n");

	msleep(2000);

	rc = usbat_पढ़ो_user_io(us, status);
	अगर (rc != USB_STOR_TRANSPORT_GOOD)
		वापस rc;

	usb_stor_dbg(us, "INIT 2\n");

	rc = usbat_पढ़ो_user_io(us, status);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	rc = usbat_पढ़ो_user_io(us, status);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "INIT 3\n");

	rc = usbat_select_and_test_रेजिस्टरs(us);
	अगर (rc != USB_STOR_TRANSPORT_GOOD)
		वापस rc;

	usb_stor_dbg(us, "INIT 4\n");

	rc = usbat_पढ़ो_user_io(us, status);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "INIT 5\n");

	/* Enable peripheral control संकेतs and card detect */
	rc = usbat_device_enable_cdt(us);
	अगर (rc != USB_STOR_TRANSPORT_GOOD)
		वापस rc;

	usb_stor_dbg(us, "INIT 6\n");

	rc = usbat_पढ़ो_user_io(us, status);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "INIT 7\n");

	msleep(1400);

	rc = usbat_पढ़ो_user_io(us, status);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "INIT 8\n");

	rc = usbat_select_and_test_रेजिस्टरs(us);
	अगर (rc != USB_STOR_TRANSPORT_GOOD)
		वापस rc;

	usb_stor_dbg(us, "INIT 9\n");

	/* At this poपूर्णांक, we need to detect which device we are using */
	अगर (usbat_set_transport(us, info, devicetype))
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "INIT 10\n");

	अगर (usbat_get_device_type(us) == USBAT_DEV_FLASH) अणु 
		subcountH = 0x02;
		subcountL = 0x00;
	पूर्ण
	rc = usbat_set_shuttle_features(us, (USBAT_FEAT_ETEN | USBAT_FEAT_ET2 | USBAT_FEAT_ET1),
									0x00, 0x88, 0x08, subcountH, subcountL);
	अगर (rc != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	usb_stor_dbg(us, "INIT 11\n");

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

/*
 * Transport क्रम the HP 8200e
 */
अटल पूर्णांक usbat_hp8200e_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *status = us->iobuf;
	अचिन्हित अक्षर रेजिस्टरs[32];
	अचिन्हित अक्षर data[32];
	अचिन्हित पूर्णांक len;
	पूर्णांक i;

	len = scsi_bufflen(srb);

	/*
	 * Send A0 (ATA PACKET COMMAND).
	 * Note: I guess we're never going to get any of the ATA
	 * commands... just ATA Packet Commands.
 	 */

	रेजिस्टरs[0] = USBAT_ATA_FEATURES;
	रेजिस्टरs[1] = USBAT_ATA_SECCNT;
	रेजिस्टरs[2] = USBAT_ATA_SECNUM;
	रेजिस्टरs[3] = USBAT_ATA_LBA_ME;
	रेजिस्टरs[4] = USBAT_ATA_LBA_HI;
	रेजिस्टरs[5] = USBAT_ATA_DEVICE;
	रेजिस्टरs[6] = USBAT_ATA_CMD;
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = len&0xFF; 		/* (cylL) = expected length (L) */
	data[4] = (len>>8)&0xFF; 	/* (cylH) = expected length (H) */
	data[5] = 0xB0; 		/* (device sel) = slave */
	data[6] = 0xA0; 		/* (command) = ATA PACKET COMMAND */

	क्रम (i=7; i<19; i++) अणु
		रेजिस्टरs[i] = 0x10;
		data[i] = (i-7 >= srb->cmd_len) ? 0 : srb->cmnd[i-7];
	पूर्ण

	result = usbat_get_status(us, status);
	usb_stor_dbg(us, "Status = %02X\n", *status);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;
	अगर (srb->cmnd[0] == TEST_UNIT_READY)
		transferred = 0;

	अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु

		result = usbat_hp8200e_rw_block_test(us, USBAT_ATA, 
			रेजिस्टरs, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD,
			(USBAT_QUAL_FCQ | USBAT_QUAL_ALQ),
			DMA_TO_DEVICE,
			scsi_sglist(srb),
			len, scsi_sg_count(srb), 10);

		अगर (result == USB_STOR_TRANSPORT_GOOD) अणु
			transferred += len;
			usb_stor_dbg(us, "Wrote %08X bytes\n", transferred);
		पूर्ण

		वापस result;

	पूर्ण अन्यथा अगर (srb->cmnd[0] == READ_10 ||
		   srb->cmnd[0] == GPCMD_READ_CD) अणु

		वापस usbat_hp8200e_handle_पढ़ो10(us, रेजिस्टरs, data, srb);

	पूर्ण

	अगर (len > 0xFFFF) अणु
		usb_stor_dbg(us, "Error: len = %08X... what do I do now?\n",
			     len);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	result = usbat_multiple_ग_लिखो(us, रेजिस्टरs, data, 7);

	अगर (result != USB_STOR_TRANSPORT_GOOD)
		वापस result;

	/*
	 * Write the 12-byte command header.
	 *
	 * If the command is BLANK then set the समयr क्रम 75 minutes.
	 * Otherwise set it क्रम 10 minutes.
	 *
	 * NOTE: THE 8200 DOCUMENTATION STATES THAT BLANKING A CDRW
	 * AT SPEED 4 IS UNRELIABLE!!!
	 */

	result = usbat_ग_लिखो_block(us, USBAT_ATA, srb->cmnd, 12,
				   srb->cmnd[0] == GPCMD_BLANK ? 75 : 10, 0);

	अगर (result != USB_STOR_TRANSPORT_GOOD)
		वापस result;

	/* If there is response data to be पढ़ो in then करो it here. */

	अगर (len != 0 && (srb->sc_data_direction == DMA_FROM_DEVICE)) अणु

		/* How many bytes to पढ़ो in? Check cylL रेजिस्टर */

		अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
		    	USB_STOR_XFER_GOOD) अणु
			वापस USB_STOR_TRANSPORT_ERROR;
		पूर्ण

		अगर (len > 0xFF) अणु /* need to पढ़ो cylH also */
			len = *status;
			अगर (usbat_पढ़ो(us, USBAT_ATA, USBAT_ATA_LBA_HI, status) !=
				    USB_STOR_XFER_GOOD) अणु
				वापस USB_STOR_TRANSPORT_ERROR;
			पूर्ण
			len += ((अचिन्हित पूर्णांक) *status)<<8;
		पूर्ण
		अन्यथा
			len = *status;


		result = usbat_पढ़ो_block(us, scsi_sglist(srb), len,
			                                   scsi_sg_count(srb));
	पूर्ण

	वापस result;
पूर्ण

/*
 * Transport क्रम USBAT02-based CompactFlash and similar storage devices
 */
अटल पूर्णांक usbat_flash_transport(काष्ठा scsi_cmnd * srb, काष्ठा us_data *us)
अणु
	पूर्णांक rc;
	काष्ठा usbat_info *info = (काष्ठा usbat_info *) (us->extra);
	अचिन्हित दीर्घ block, blocks;
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

	अगर (srb->cmnd[0] == READ_CAPACITY) अणु
		rc = usbat_flash_check_media(us, info);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		rc = usbat_flash_get_sector_count(us, info);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		/* hard coded 512 byte sectors as per ATA spec */
		info->ssize = 0x200;
		usb_stor_dbg(us, "READ_CAPACITY: %ld sectors, %ld bytes per sector\n",
			     info->sectors, info->ssize);

		/*
		 * build the reply
		 * note: must वापस the sector number of the last sector,
		 * *not* the total number of sectors
		 */
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
		वापस usbat_flash_पढ़ो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == READ_12) अणु
		/*
		 * I करोn't think we'll ever see a READ_12 but support it anyway
		 */
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
		        ((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[6]) << 24) | ((u32)(srb->cmnd[7]) << 16) |
		         ((u32)(srb->cmnd[8]) <<  8) | ((u32)(srb->cmnd[9]));

		usb_stor_dbg(us, "READ_12: read block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस usbat_flash_पढ़ो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_10) अणु
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
		        ((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[7]) << 8) | ((u32)(srb->cmnd[8]));

		usb_stor_dbg(us, "WRITE_10: write block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस usbat_flash_ग_लिखो_data(us, info, block, blocks);
	पूर्ण

	अगर (srb->cmnd[0] == WRITE_12) अणु
		/*
		 * I करोn't think we'll ever see a WRITE_12 but support it anyway
		 */
		block = ((u32)(srb->cmnd[2]) << 24) | ((u32)(srb->cmnd[3]) << 16) |
		        ((u32)(srb->cmnd[4]) <<  8) | ((u32)(srb->cmnd[5]));

		blocks = ((u32)(srb->cmnd[6]) << 24) | ((u32)(srb->cmnd[7]) << 16) |
		         ((u32)(srb->cmnd[8]) <<  8) | ((u32)(srb->cmnd[9]));

		usb_stor_dbg(us, "WRITE_12: write block 0x%04lx  count %ld\n",
			     block, blocks);
		वापस usbat_flash_ग_लिखो_data(us, info, block, blocks);
	पूर्ण


	अगर (srb->cmnd[0] == TEST_UNIT_READY) अणु
		usb_stor_dbg(us, "TEST_UNIT_READY\n");

		rc = usbat_flash_check_media(us, info);
		अगर (rc != USB_STOR_TRANSPORT_GOOD)
			वापस rc;

		वापस usbat_check_status(us);
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

अटल पूर्णांक init_usbat_cd(काष्ठा us_data *us)
अणु
	वापस init_usbat(us, USBAT_DEV_HP8200);
पूर्ण

अटल पूर्णांक init_usbat_flash(काष्ठा us_data *us)
अणु
	वापस init_usbat(us, USBAT_DEV_FLASH);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा usbat_host_ढाँचा;

अटल पूर्णांक usbat_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - usbat_usb_ids) + usbat_unusual_dev_list,
			&usbat_host_ढाँचा);
	अगर (result)
		वापस result;

	/*
	 * The actual transport will be determined later by the
	 * initialization routine; this is just a placeholder.
	 */
	us->transport_name = "Shuttle USBAT";
	us->transport = usbat_flash_transport;
	us->transport_reset = usb_stor_CB_reset;
	us->max_lun = 0;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver usbat_driver = अणु
	.name =		DRV_NAME,
	.probe =	usbat_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	usbat_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(usbat_driver, usbat_host_ढाँचा, DRV_NAME);
