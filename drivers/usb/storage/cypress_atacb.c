<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Support क्रम emulating SAT (ata pass through) on devices based
 *       on the Cypress USB/ATA bridge supporting ATACB.
 *
 * Copyright (c) 2008 Matthieu Castet (castet.matthieu@मुक्त.fr)
 */

#समावेश <linux/module.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <linux/ata.h>

#समावेश "usb.h"
#समावेश "protocol.h"
#समावेश "scsiglue.h"
#समावेश "debug.h"

#घोषणा DRV_NAME "ums-cypress"

MODULE_DESCRIPTION("SAT support for Cypress USB/ATA bridges with ATACB");
MODULE_AUTHOR("Matthieu Castet <castet.matthieu@free.fr>");
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

अटल काष्ठा usb_device_id cypress_usb_ids[] = अणु
#	include "unusual_cypress.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, cypress_usb_ids);

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

अटल काष्ठा us_unusual_dev cypress_unusual_dev_list[] = अणु
#	include "unusual_cypress.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


/*
 * ATACB is a protocol used on cypress usb<->ata bridge to
 * send raw ATA command over mass storage
 * There is a ATACB2 protocol that support LBA48 on newer chip.
 * More info that be found on cy7c68310_8.pdf and cy7c68300c_8.pdf
 * datasheet from cypress.com.
 */
अटल व्योम cypress_atacb_passthrough(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	अचिन्हित अक्षर save_cmnd[MAX_COMMAND_SIZE];

	अगर (likely(srb->cmnd[0] != ATA_16 && srb->cmnd[0] != ATA_12)) अणु
		usb_stor_transparent_scsi_command(srb, us);
		वापस;
	पूर्ण

	स_नकल(save_cmnd, srb->cmnd, माप(save_cmnd));
	स_रखो(srb->cmnd, 0, MAX_COMMAND_SIZE);

	/* check अगर we support the command */
	अगर (save_cmnd[1] >> 5) /* MULTIPLE_COUNT */
		जाओ invalid_fld;
	/* check protocol */
	चयन ((save_cmnd[1] >> 1) & 0xf) अणु
	हाल 3: /*no DATA */
	हाल 4: /* PIO in */
	हाल 5: /* PIO out */
		अवरोध;
	शेष:
		जाओ invalid_fld;
	पूर्ण

	/* first build the ATACB command */
	srb->cmd_len = 16;

	srb->cmnd[0] = 0x24; /*
			      * bVSCBSignature : venकरोr-specअगरic command
			      * this value can change, but most(all ?) manufacturers
			      * keep the cypress शेष : 0x24
			      */
	srb->cmnd[1] = 0x24; /* bVSCBSubCommand : 0x24 क्रम ATACB */

	srb->cmnd[3] = 0xff - 1; /*
				  * features, sector count, lba low, lba med
				  * lba high, device, command are valid
				  */
	srb->cmnd[4] = 1; /* TransferBlockCount : 512 */

	अगर (save_cmnd[0] == ATA_16) अणु
		srb->cmnd[ 6] = save_cmnd[ 4]; /* features */
		srb->cmnd[ 7] = save_cmnd[ 6]; /* sector count */
		srb->cmnd[ 8] = save_cmnd[ 8]; /* lba low */
		srb->cmnd[ 9] = save_cmnd[10]; /* lba med */
		srb->cmnd[10] = save_cmnd[12]; /* lba high */
		srb->cmnd[11] = save_cmnd[13]; /* device */
		srb->cmnd[12] = save_cmnd[14]; /* command */

		अगर (save_cmnd[1] & 0x01) अणु/* extended bit set क्रम LBA48 */
			/* this could be supported by atacb2 */
			अगर (save_cmnd[3] || save_cmnd[5] || save_cmnd[7] || save_cmnd[9]
					|| save_cmnd[11])
				जाओ invalid_fld;
		पूर्ण
	पूर्ण अन्यथा अणु /* ATA12 */
		srb->cmnd[ 6] = save_cmnd[3]; /* features */
		srb->cmnd[ 7] = save_cmnd[4]; /* sector count */
		srb->cmnd[ 8] = save_cmnd[5]; /* lba low */
		srb->cmnd[ 9] = save_cmnd[6]; /* lba med */
		srb->cmnd[10] = save_cmnd[7]; /* lba high */
		srb->cmnd[11] = save_cmnd[8]; /* device */
		srb->cmnd[12] = save_cmnd[9]; /* command */

	पूर्ण
	/* Filter SET_FEATURES - XFER MODE command */
	अगर ((srb->cmnd[12] == ATA_CMD_SET_FEATURES)
			&& (srb->cmnd[6] == SETFEATURES_XFER))
		जाओ invalid_fld;

	अगर (srb->cmnd[12] == ATA_CMD_ID_ATA || srb->cmnd[12] == ATA_CMD_ID_ATAPI)
		srb->cmnd[2] |= (1<<7); /* set  IdentअगरyPacketDevice क्रम these cmds */


	usb_stor_transparent_scsi_command(srb, us);

	/* अगर the device करोesn't support ATACB */
	अगर (srb->result == SAM_STAT_CHECK_CONDITION &&
			स_भेद(srb->sense_buffer, usb_stor_sense_invalidCDB,
				माप(usb_stor_sense_invalidCDB)) == 0) अणु
		usb_stor_dbg(us, "cypress atacb not supported ???\n");
		जाओ end;
	पूर्ण

	/*
	 * अगर ck_cond flags is set, and there wasn't critical error,
	 * build the special sense
	 */
	अगर ((srb->result != (DID_ERROR << 16) &&
				srb->result != (DID_ABORT << 16)) &&
			save_cmnd[2] & 0x20) अणु
		काष्ठा scsi_eh_save ses;
		अचिन्हित अक्षर regs[8];
		अचिन्हित अक्षर *sb = srb->sense_buffer;
		अचिन्हित अक्षर *desc = sb + 8;
		पूर्णांक पंचांगp_result;

		/* build the command क्रम पढ़ोing the ATA रेजिस्टरs */
		scsi_eh_prep_cmnd(srb, &ses, शून्य, 0, माप(regs));

		/*
		 * we use the same command as beक्रमe, but we set
		 * the पढ़ो taskfile bit, क्रम not executing atacb command,
		 * but पढ़ोing रेजिस्टर selected in srb->cmnd[4]
		 */
		srb->cmd_len = 16;
		srb->cmnd = ses.cmnd;
		srb->cmnd[2] = 1;

		usb_stor_transparent_scsi_command(srb, us);
		स_नकल(regs, srb->sense_buffer, माप(regs));
		पंचांगp_result = srb->result;
		scsi_eh_restore_cmnd(srb, &ses);
		/* we fail to get रेजिस्टरs, report invalid command */
		अगर (पंचांगp_result != SAM_STAT_GOOD)
			जाओ invalid_fld;

		/* build the sense */
		स_रखो(sb, 0, SCSI_SENSE_BUFFERSIZE);

		/* set sk, asc क्रम a good command */
		sb[1] = RECOVERED_ERROR;
		sb[2] = 0; /* ATA PASS THROUGH INFORMATION AVAILABLE */
		sb[3] = 0x1D;

		/*
		 * XXX we should generate sk, asc, ascq from status and error
		 * regs
		 * (see 11.1 Error translation ATA device error to SCSI error
		 * map, and ata_to_sense_error from libata.)
		 */

		/* Sense data is current and क्रमmat is descriptor. */
		sb[0] = 0x72;
		desc[0] = 0x09; /* ATA_RETURN_DESCRIPTOR */

		/* set length of additional sense data */
		sb[7] = 14;
		desc[1] = 12;

		/* Copy रेजिस्टरs पूर्णांकo sense buffer. */
		desc[ 2] = 0x00;
		desc[ 3] = regs[1];  /* features */
		desc[ 5] = regs[2];  /* sector count */
		desc[ 7] = regs[3];  /* lba low */
		desc[ 9] = regs[4];  /* lba med */
		desc[11] = regs[5];  /* lba high */
		desc[12] = regs[6];  /* device */
		desc[13] = regs[7];  /* command */

		srb->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;
	पूर्ण
	जाओ end;
invalid_fld:
	srb->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	स_नकल(srb->sense_buffer,
			usb_stor_sense_invalidCDB,
			माप(usb_stor_sense_invalidCDB));
end:
	स_नकल(srb->cmnd, save_cmnd, माप(save_cmnd));
	अगर (srb->cmnd[0] == ATA_12)
		srb->cmd_len = 12;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cypress_host_ढाँचा;

अटल पूर्णांक cypress_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;
	काष्ठा usb_device *device;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - cypress_usb_ids) + cypress_unusual_dev_list,
			&cypress_host_ढाँचा);
	अगर (result)
		वापस result;

	/*
	 * Among CY7C68300 chips, the A revision करोes not support Cypress ATACB
	 * Filter out this revision from EEPROM शेष descriptor values
	 */
	device = पूर्णांकerface_to_usbdev(पूर्णांकf);
	अगर (device->descriptor.iManufacturer != 0x38 ||
	    device->descriptor.iProduct != 0x4e ||
	    device->descriptor.iSerialNumber != 0x64) अणु
		us->protocol_name = "Transparent SCSI with Cypress ATACB";
		us->proto_handler = cypress_atacb_passthrough;
	पूर्ण अन्यथा अणु
		us->protocol_name = "Transparent SCSI";
		us->proto_handler = usb_stor_transparent_scsi_command;
	पूर्ण

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver cypress_driver = अणु
	.name =		DRV_NAME,
	.probe =	cypress_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	cypress_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(cypress_driver, cypress_host_ढाँचा, DRV_NAME);
