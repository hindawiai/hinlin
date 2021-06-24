<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Transport & Protocol Driver क्रम In-System Design, Inc. ISD200 ASIC
 *
 * Current development and मुख्यtenance:
 *   (C) 2001-2002 Bjथघrn Stenberg (bjorn@haxx.se)
 *
 * Developed with the assistance of:
 *   (C) 2002 Alan Stern <stern@rowland.org>
 *
 * Initial work:
 *   (C) 2000 In-System Design, Inc. (support@in-प्रणाली.com)
 *
 * The ISD200 ASIC करोes not natively support ATA devices.  The chip
 * करोes implement an पूर्णांकerface, the ATA Command Block (ATACB) which provides
 * a means of passing ATA commands and ATA रेजिस्टर accesses to a device.
 *
 * History:
 *
 *  2002-10-19: Removed the specialized transfer routines.
 *		(Alan Stern <stern@rowland.harvard.edu>)
 *  2001-02-24: Removed lots of duplicate code and simplअगरied the काष्ठाure.
 *	      (bjorn@haxx.se)
 *  2002-01-16: Fixed endianness bug so it works on the ppc arch.
 *	      (Luc Saillard <luc@saillard.org>)
 *  2002-01-17: All bitfields हटाओd.
 *	      (bjorn@haxx.se)
 */


/* Include files */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ata.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/scatterlist.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-isd200"

MODULE_DESCRIPTION("Driver for In-System Design, Inc. ISD200 ASIC");
MODULE_AUTHOR("Bjथघrn Stenberg <bjorn@haxx.se>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

अटल पूर्णांक isd200_Initialization(काष्ठा us_data *us);


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id isd200_usb_ids[] = अणु
#	include "unusual_isd200.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, isd200_usb_ids);

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

अटल काष्ठा us_unusual_dev isd200_unusual_dev_list[] = अणु
#	include "unusual_isd200.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV

/* Timeout defines (in Seconds) */

#घोषणा ISD200_ENUM_BSY_TIMEOUT		35
#घोषणा ISD200_ENUM_DETECT_TIMEOUT      30
#घोषणा ISD200_DEFAULT_TIMEOUT		30

/* device flags */
#घोषणा DF_ATA_DEVICE		0x0001
#घोषणा DF_MEDIA_STATUS_ENABLED	0x0002
#घोषणा DF_REMOVABLE_MEDIA	0x0004

/* capability bit definitions */
#घोषणा CAPABILITY_DMA		0x01
#घोषणा CAPABILITY_LBA		0x02

/* command_setX bit definitions */
#घोषणा COMMANDSET_REMOVABLE	0x02
#घोषणा COMMANDSET_MEDIA_STATUS 0x10

/* ATA Venकरोr Specअगरic defines */
#घोषणा ATA_ADDRESS_DEVHEAD_STD      0xa0
#घोषणा ATA_ADDRESS_DEVHEAD_LBA_MODE 0x40    
#घोषणा ATA_ADDRESS_DEVHEAD_SLAVE    0x10

/* Action Select bits */
#घोषणा ACTION_SELECT_0	     0x01
#घोषणा ACTION_SELECT_1	     0x02
#घोषणा ACTION_SELECT_2	     0x04
#घोषणा ACTION_SELECT_3	     0x08
#घोषणा ACTION_SELECT_4	     0x10
#घोषणा ACTION_SELECT_5	     0x20
#घोषणा ACTION_SELECT_6	     0x40
#घोषणा ACTION_SELECT_7	     0x80

/* Register Select bits */
#घोषणा REG_ALTERNATE_STATUS	0x01
#घोषणा REG_DEVICE_CONTROL	0x01
#घोषणा REG_ERROR		0x02
#घोषणा REG_FEATURES		0x02
#घोषणा REG_SECTOR_COUNT	0x04
#घोषणा REG_SECTOR_NUMBER	0x08
#घोषणा REG_CYLINDER_LOW	0x10
#घोषणा REG_CYLINDER_HIGH	0x20
#घोषणा REG_DEVICE_HEAD		0x40
#घोषणा REG_STATUS		0x80
#घोषणा REG_COMMAND		0x80

/* ATA रेजिस्टरs offset definitions */
#घोषणा ATA_REG_ERROR_OFFSET		1
#घोषणा ATA_REG_LCYL_OFFSET		4
#घोषणा ATA_REG_HCYL_OFFSET		5
#घोषणा ATA_REG_STATUS_OFFSET		7

/* ATA error definitions not in <linux/hdreg.h> */
#घोषणा ATA_ERROR_MEDIA_CHANGE		0x20

/* ATA command definitions not in <linux/hdreg.h> */
#घोषणा ATA_COMMAND_GET_MEDIA_STATUS	0xDA
#घोषणा ATA_COMMAND_MEDIA_EJECT		0xED

/* ATA drive control definitions */
#घोषणा ATA_DC_DISABLE_INTERRUPTS	0x02
#घोषणा ATA_DC_RESET_CONTROLLER		0x04
#घोषणा ATA_DC_REENABLE_CONTROLLER	0x00

/*
 *  General purpose वापस codes
 */ 

#घोषणा ISD200_ERROR		-1
#घोषणा ISD200_GOOD		 0

/*
 * Transport वापस codes
 */

#घोषणा ISD200_TRANSPORT_GOOD       0   /* Transport good, command good     */
#घोषणा ISD200_TRANSPORT_FAILED     1   /* Transport good, command failed   */
#घोषणा ISD200_TRANSPORT_ERROR      2   /* Transport bad (i.e. device dead) */

/* driver action codes */
#घोषणा	ACTION_READ_STATUS	0
#घोषणा	ACTION_RESET		1
#घोषणा	ACTION_REENABLE		2
#घोषणा	ACTION_SOFT_RESET	3
#घोषणा	ACTION_ENUM		4
#घोषणा	ACTION_IDENTIFY		5


/*
 * ata_cdb काष्ठा
 */


जोड़ ata_cdb अणु
	काष्ठा अणु
		अचिन्हित अक्षर SignatureByte0;
		अचिन्हित अक्षर SignatureByte1;
		अचिन्हित अक्षर ActionSelect;
		अचिन्हित अक्षर RegisterSelect;
		अचिन्हित अक्षर TransferBlockSize;
		अचिन्हित अक्षर WriteData3F6;
		अचिन्हित अक्षर WriteData1F1;
		अचिन्हित अक्षर WriteData1F2;
		अचिन्हित अक्षर WriteData1F3;
		अचिन्हित अक्षर WriteData1F4;
		अचिन्हित अक्षर WriteData1F5;
		अचिन्हित अक्षर WriteData1F6;
		अचिन्हित अक्षर WriteData1F7;
		अचिन्हित अक्षर Reserved[3];
	पूर्ण generic;

	काष्ठा अणु
		अचिन्हित अक्षर SignatureByte0;
		अचिन्हित अक्षर SignatureByte1;
		अचिन्हित अक्षर ActionSelect;
		अचिन्हित अक्षर RegisterSelect;
		अचिन्हित अक्षर TransferBlockSize;
		अचिन्हित अक्षर AlternateStatusByte;
		अचिन्हित अक्षर ErrorByte;
		अचिन्हित अक्षर SectorCountByte;
		अचिन्हित अक्षर SectorNumberByte;
		अचिन्हित अक्षर CylinderLowByte;
		अचिन्हित अक्षर CylinderHighByte;
		अचिन्हित अक्षर DeviceHeadByte;
		अचिन्हित अक्षर StatusByte;
		अचिन्हित अक्षर Reserved[3];
	पूर्ण पढ़ो;

	काष्ठा अणु
		अचिन्हित अक्षर SignatureByte0;
		अचिन्हित अक्षर SignatureByte1;
		अचिन्हित अक्षर ActionSelect;
		अचिन्हित अक्षर RegisterSelect;
		अचिन्हित अक्षर TransferBlockSize;
		अचिन्हित अक्षर DeviceControlByte;
		अचिन्हित अक्षर FeaturesByte;
		अचिन्हित अक्षर SectorCountByte;
		अचिन्हित अक्षर SectorNumberByte;
		अचिन्हित अक्षर CylinderLowByte;
		अचिन्हित अक्षर CylinderHighByte;
		अचिन्हित अक्षर DeviceHeadByte;
		अचिन्हित अक्षर CommandByte;
		अचिन्हित अक्षर Reserved[3];
	पूर्ण ग_लिखो;
पूर्ण;


/*
 * Inquiry data काष्ठाure. This is the data वापसed from the target
 * after it receives an inquiry.
 *
 * This काष्ठाure may be extended by the number of bytes specअगरied
 * in the field AdditionalLength. The defined size स्थिरant only
 * includes fields through ProductRevisionLevel.
 */

/*
 * DeviceType field
 */
#घोषणा सूचीECT_ACCESS_DEVICE	    0x00    /* disks */
#घोषणा DEVICE_REMOVABLE		0x80

काष्ठा inquiry_data अणु
   	अचिन्हित अक्षर DeviceType;
	अचिन्हित अक्षर DeviceTypeModअगरier;
	अचिन्हित अक्षर Versions;
	अचिन्हित अक्षर Format; 
	अचिन्हित अक्षर AdditionalLength;
	अचिन्हित अक्षर Reserved[2];
	अचिन्हित अक्षर Capability;
	अचिन्हित अक्षर VenकरोrId[8];
	अचिन्हित अक्षर ProductId[16];
	अचिन्हित अक्षर ProductRevisionLevel[4];
	अचिन्हित अक्षर VenकरोrSpecअगरic[20];
	अचिन्हित अक्षर Reserved3[40];
पूर्ण __attribute__ ((packed));

/*
 * INQUIRY data buffer size
 */

#घोषणा INQUIRYDATABUFFERSIZE 36


/*
 * ISD200 CONFIG data काष्ठा
 */

#घोषणा ATACFG_TIMING	  0x0f
#घोषणा ATACFG_ATAPI_RESET     0x10
#घोषणा ATACFG_MASTER	  0x20
#घोषणा ATACFG_BLOCKSIZE       0xa0

#घोषणा ATACFGE_LAST_LUN       0x07
#घोषणा ATACFGE_DESC_OVERRIDE  0x08
#घोषणा ATACFGE_STATE_SUSPEND  0x10
#घोषणा ATACFGE_SKIP_BOOT      0x20
#घोषणा ATACFGE_CONF_DESC2     0x40
#घोषणा ATACFGE_INIT_STATUS    0x80

#घोषणा CFG_CAPABILITY_SRST    0x01

काष्ठा isd200_config अणु
	अचिन्हित अक्षर EventNotअगरication;
	अचिन्हित अक्षर ExternalClock;
	अचिन्हित अक्षर ATAInitTimeout;
	अचिन्हित अक्षर ATAConfig;
	अचिन्हित अक्षर ATAMajorCommand;
	अचिन्हित अक्षर ATAMinorCommand;
	अचिन्हित अक्षर ATAExtraConfig;
	अचिन्हित अक्षर Capability;
पूर्ण__attribute__ ((packed));


/*
 * ISD200 driver inक्रमmation काष्ठा
 */

काष्ठा isd200_info अणु
	काष्ठा inquiry_data InquiryData;
	u16 *id;
	काष्ठा isd200_config ConfigData;
	अचिन्हित अक्षर *RegsBuf;
	अचिन्हित अक्षर ATARegs[8];
	अचिन्हित अक्षर DeviceHead;
	अचिन्हित अक्षर DeviceFlags;

	/* maximum number of LUNs supported */
	अचिन्हित अक्षर MaxLUNs;
	अचिन्हित अक्षर cmnd[BLK_MAX_CDB];
	काष्ठा scsi_cmnd srb;
	काष्ठा scatterlist sg;
पूर्ण;


/*
 * Read Capacity Data - वापसed in Big Endian क्रमmat
 */

काष्ठा पढ़ो_capacity_data अणु
	__be32 LogicalBlockAddress;
	__be32 BytesPerBlock;
पूर्ण;

/*
 * Read Block Limits Data - वापसed in Big Endian क्रमmat
 * This काष्ठाure वापसs the maximum and minimum block
 * size क्रम a TAPE device.
 */

काष्ठा पढ़ो_block_limits अणु
	अचिन्हित अक्षर Reserved;
	अचिन्हित अक्षर BlockMaximumSize[3];
	अचिन्हित अक्षर BlockMinimumSize[2];
पूर्ण;


/*
 * Sense Data Format
 */

#घोषणा SENSE_ERRCODE	   0x7f
#घोषणा SENSE_ERRCODE_VALID     0x80
#घोषणा SENSE_FLAG_SENSE_KEY    0x0f
#घोषणा SENSE_FLAG_BAD_LENGTH   0x20
#घोषणा SENSE_FLAG_END_OF_MEDIA 0x40
#घोषणा SENSE_FLAG_खाता_MARK    0x80
काष्ठा sense_data अणु
	अचिन्हित अक्षर ErrorCode;
	अचिन्हित अक्षर SegmentNumber;
	अचिन्हित अक्षर Flags;
	अचिन्हित अक्षर Inक्रमmation[4];
	अचिन्हित अक्षर AdditionalSenseLength;
	अचिन्हित अक्षर CommandSpecअगरicInक्रमmation[4];
	अचिन्हित अक्षर AdditionalSenseCode;
	अचिन्हित अक्षर AdditionalSenseCodeQualअगरier;
	अचिन्हित अक्षर FieldReplaceableUnitCode;
	अचिन्हित अक्षर SenseKeySpecअगरic[3];
पूर्ण __attribute__ ((packed));

/*
 * Default request sense buffer size
 */

#घोषणा SENSE_BUFFER_SIZE 18

/***********************************************************************
 * Helper routines
 ***********************************************************************/

/**************************************************************************
 * isd200_build_sense
 *									 
 *  Builds an artअगरicial sense buffer to report the results of a 
 *  failed command.
 *								       
 * RETURNS:
 *    व्योम
 */
अटल व्योम isd200_build_sense(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	काष्ठा sense_data *buf = (काष्ठा sense_data *) &srb->sense_buffer[0];
	अचिन्हित अक्षर error = info->ATARegs[ATA_REG_ERROR_OFFSET];

	अगर(error & ATA_ERROR_MEDIA_CHANGE) अणु
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags = UNIT_ATTENTION;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualअगरier = 0;
	पूर्ण अन्यथा अगर (error & ATA_MCR) अणु
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags =  UNIT_ATTENTION;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualअगरier = 0;
	पूर्ण अन्यथा अगर (error & ATA_TRK0NF) अणु
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags =  NOT_READY;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualअगरier = 0;
	पूर्ण अन्यथा अगर (error & ATA_UNC) अणु
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags =  DATA_PROTECT;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualअगरier = 0;
	पूर्ण अन्यथा अणु
		buf->ErrorCode = 0;
		buf->AdditionalSenseLength = 0;
		buf->Flags =  0;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualअगरier = 0;
	पूर्ण
पूर्ण


/***********************************************************************
 * Transport routines
 ***********************************************************************/

/**************************************************************************
 *  isd200_set_srb(), isd200_srb_set_bufflen()
 *
 * Two helpers to facilitate in initialization of scsi_cmnd काष्ठाure
 * Will need to change when काष्ठा scsi_cmnd changes
 */
अटल व्योम isd200_set_srb(काष्ठा isd200_info *info,
	क्रमागत dma_data_direction dir, व्योम* buff, अचिन्हित bufflen)
अणु
	काष्ठा scsi_cmnd *srb = &info->srb;

	अगर (buff)
		sg_init_one(&info->sg, buff, bufflen);

	srb->sc_data_direction = dir;
	srb->sdb.table.sgl = buff ? &info->sg : शून्य;
	srb->sdb.length = bufflen;
	srb->sdb.table.nents = buff ? 1 : 0;
पूर्ण

अटल व्योम isd200_srb_set_bufflen(काष्ठा scsi_cmnd *srb, अचिन्हित bufflen)
अणु
	srb->sdb.length = bufflen;
पूर्ण


/**************************************************************************
 *  isd200_action
 *
 * Routine क्रम sending commands to the isd200
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_action( काष्ठा us_data *us, पूर्णांक action, 
			  व्योम* poपूर्णांकer, पूर्णांक value )
अणु
	जोड़ ata_cdb ata;
	/* अटल to prevent this large काष्ठा being placed on the valuable stack */
	अटल काष्ठा scsi_device srb_dev;
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	काष्ठा scsi_cmnd *srb = &info->srb;
	पूर्णांक status;

	स_रखो(&ata, 0, माप(ata));
	srb->cmnd = info->cmnd;
	srb->device = &srb_dev;

	ata.generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
	ata.generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
	ata.generic.TransferBlockSize = 1;

	चयन ( action ) अणु
	हाल ACTION_READ_STATUS:
		usb_stor_dbg(us, "   isd200_action(READ_STATUS)\n");
		ata.generic.ActionSelect = ACTION_SELECT_0|ACTION_SELECT_2;
		ata.generic.RegisterSelect =
		  REG_CYLINDER_LOW | REG_CYLINDER_HIGH |
		  REG_STATUS | REG_ERROR;
		isd200_set_srb(info, DMA_FROM_DEVICE, poपूर्णांकer, value);
		अवरोध;

	हाल ACTION_ENUM:
		usb_stor_dbg(us, "   isd200_action(ENUM,0x%02x)\n", value);
		ata.generic.ActionSelect = ACTION_SELECT_1|ACTION_SELECT_2|
					   ACTION_SELECT_3|ACTION_SELECT_4|
					   ACTION_SELECT_5;
		ata.generic.RegisterSelect = REG_DEVICE_HEAD;
		ata.ग_लिखो.DeviceHeadByte = value;
		isd200_set_srb(info, DMA_NONE, शून्य, 0);
		अवरोध;

	हाल ACTION_RESET:
		usb_stor_dbg(us, "   isd200_action(RESET)\n");
		ata.generic.ActionSelect = ACTION_SELECT_1|ACTION_SELECT_2|
					   ACTION_SELECT_3|ACTION_SELECT_4;
		ata.generic.RegisterSelect = REG_DEVICE_CONTROL;
		ata.ग_लिखो.DeviceControlByte = ATA_DC_RESET_CONTROLLER;
		isd200_set_srb(info, DMA_NONE, शून्य, 0);
		अवरोध;

	हाल ACTION_REENABLE:
		usb_stor_dbg(us, "   isd200_action(REENABLE)\n");
		ata.generic.ActionSelect = ACTION_SELECT_1|ACTION_SELECT_2|
					   ACTION_SELECT_3|ACTION_SELECT_4;
		ata.generic.RegisterSelect = REG_DEVICE_CONTROL;
		ata.ग_लिखो.DeviceControlByte = ATA_DC_REENABLE_CONTROLLER;
		isd200_set_srb(info, DMA_NONE, शून्य, 0);
		अवरोध;

	हाल ACTION_SOFT_RESET:
		usb_stor_dbg(us, "   isd200_action(SOFT_RESET)\n");
		ata.generic.ActionSelect = ACTION_SELECT_1|ACTION_SELECT_5;
		ata.generic.RegisterSelect = REG_DEVICE_HEAD | REG_COMMAND;
		ata.ग_लिखो.DeviceHeadByte = info->DeviceHead;
		ata.ग_लिखो.CommandByte = ATA_CMD_DEV_RESET;
		isd200_set_srb(info, DMA_NONE, शून्य, 0);
		अवरोध;

	हाल ACTION_IDENTIFY:
		usb_stor_dbg(us, "   isd200_action(IDENTIFY)\n");
		ata.generic.RegisterSelect = REG_COMMAND;
		ata.ग_लिखो.CommandByte = ATA_CMD_ID_ATA;
		isd200_set_srb(info, DMA_FROM_DEVICE, info->id,
				ATA_ID_WORDS * 2);
		अवरोध;

	शेष:
		usb_stor_dbg(us, "Error: Undefined action %d\n", action);
		वापस ISD200_ERROR;
	पूर्ण

	स_नकल(srb->cmnd, &ata, माप(ata.generic));
	srb->cmd_len = माप(ata.generic);
	status = usb_stor_Bulk_transport(srb, us);
	अगर (status == USB_STOR_TRANSPORT_GOOD)
		status = ISD200_GOOD;
	अन्यथा अणु
		usb_stor_dbg(us, "   isd200_action(0x%02x) error: %d\n",
			     action, status);
		status = ISD200_ERROR;
		/* need to reset device here */
	पूर्ण

	वापस status;
पूर्ण

/**************************************************************************
 * isd200_पढ़ो_regs
 *									 
 * Read ATA Registers
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_पढ़ो_regs( काष्ठा us_data *us )
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	पूर्णांक retStatus = ISD200_GOOD;
	पूर्णांक transferStatus;

	usb_stor_dbg(us, "Entering isd200_IssueATAReadRegs\n");

	transferStatus = isd200_action( us, ACTION_READ_STATUS,
				    info->RegsBuf, माप(info->ATARegs) );
	अगर (transferStatus != ISD200_TRANSPORT_GOOD) अणु
		usb_stor_dbg(us, "   Error reading ATA registers\n");
		retStatus = ISD200_ERROR;
	पूर्ण अन्यथा अणु
		स_नकल(info->ATARegs, info->RegsBuf, माप(info->ATARegs));
		usb_stor_dbg(us, "   Got ATA Register[ATA_REG_ERROR_OFFSET] = 0x%x\n",
			     info->ATARegs[ATA_REG_ERROR_OFFSET]);
	पूर्ण

	वापस retStatus;
पूर्ण


/**************************************************************************
 * Invoke the transport and basic error-handling/recovery methods
 *
 * This is used by the protocol layers to actually send the message to
 * the device and receive the response.
 */
अटल व्योम isd200_invoke_transport( काष्ठा us_data *us, 
			      काष्ठा scsi_cmnd *srb, 
			      जोड़ ata_cdb *ataCdb )
अणु
	पूर्णांक need_स्वतः_sense = 0;
	पूर्णांक transferStatus;
	पूर्णांक result;

	/* send the command to the transport layer */
	स_नकल(srb->cmnd, ataCdb, माप(ataCdb->generic));
	srb->cmd_len = माप(ataCdb->generic);
	transferStatus = usb_stor_Bulk_transport(srb, us);

	/*
	 * अगर the command माला_लो पातed by the higher layers, we need to
	 * लघु-circuit all other processing
	 */
	अगर (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) अणु
		usb_stor_dbg(us, "-- command was aborted\n");
		जाओ Handle_Abort;
	पूर्ण

	चयन (transferStatus) अणु

	हाल USB_STOR_TRANSPORT_GOOD:
		/* Indicate a good result */
		srb->result = SAM_STAT_GOOD;
		अवरोध;

	हाल USB_STOR_TRANSPORT_NO_SENSE:
		usb_stor_dbg(us, "-- transport indicates protocol failure\n");
		srb->result = SAM_STAT_CHECK_CONDITION;
		वापस;

	हाल USB_STOR_TRANSPORT_FAILED:
		usb_stor_dbg(us, "-- transport indicates command failure\n");
		need_स्वतः_sense = 1;
		अवरोध;

	हाल USB_STOR_TRANSPORT_ERROR:
		usb_stor_dbg(us, "-- transport indicates transport error\n");
		srb->result = DID_ERROR << 16;
		/* Need reset here */
		वापस;
    
	शेष:
		usb_stor_dbg(us, "-- transport indicates unknown error\n");
		srb->result = DID_ERROR << 16;
		/* Need reset here */
		वापस;
	पूर्ण

	अगर ((scsi_get_resid(srb) > 0) &&
	    !((srb->cmnd[0] == REQUEST_SENSE) ||
	      (srb->cmnd[0] == INQUIRY) ||
	      (srb->cmnd[0] == MODE_SENSE) ||
	      (srb->cmnd[0] == LOG_SENSE) ||
	      (srb->cmnd[0] == MODE_SENSE_10))) अणु
		usb_stor_dbg(us, "-- unexpectedly short transfer\n");
		need_स्वतः_sense = 1;
	पूर्ण

	अगर (need_स्वतः_sense) अणु
		result = isd200_पढ़ो_regs(us);
		अगर (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) अणु
			usb_stor_dbg(us, "-- auto-sense aborted\n");
			जाओ Handle_Abort;
		पूर्ण
		अगर (result == ISD200_GOOD) अणु
			isd200_build_sense(us, srb);
			srb->result = SAM_STAT_CHECK_CONDITION;

			/* If things are really okay, then let's show that */
			अगर ((srb->sense_buffer[2] & 0xf) == 0x0)
				srb->result = SAM_STAT_GOOD;
		पूर्ण अन्यथा अणु
			srb->result = DID_ERROR << 16;
			/* Need reset here */
		पूर्ण
	पूर्ण

	/*
	 * Regardless of स्वतः-sense, अगर we _know_ we have an error
	 * condition, show that in the result code
	 */
	अगर (transferStatus == USB_STOR_TRANSPORT_FAILED)
		srb->result = SAM_STAT_CHECK_CONDITION;
	वापस;

	/*
	 * पात processing: the bulk-only transport requires a reset
	 * following an पात
	 */
	Handle_Abort:
	srb->result = DID_ABORT << 16;

	/* permit the reset transfer to take place */
	clear_bit(US_FLIDX_ABORTING, &us->dflags);
	/* Need reset here */
पूर्ण

#अगर_घोषित CONFIG_USB_STORAGE_DEBUG
अटल व्योम isd200_log_config(काष्ठा us_data *us, काष्ठा isd200_info *info)
अणु
	usb_stor_dbg(us, "      Event Notification: 0x%x\n",
		     info->ConfigData.EventNotअगरication);
	usb_stor_dbg(us, "      External Clock: 0x%x\n",
		     info->ConfigData.ExternalClock);
	usb_stor_dbg(us, "      ATA Init Timeout: 0x%x\n",
		     info->ConfigData.ATAInitTimeout);
	usb_stor_dbg(us, "      ATAPI Command Block Size: 0x%x\n",
		     (info->ConfigData.ATAConfig & ATACFG_BLOCKSIZE) >> 6);
	usb_stor_dbg(us, "      Master/Slave Selection: 0x%x\n",
		     info->ConfigData.ATAConfig & ATACFG_MASTER);
	usb_stor_dbg(us, "      ATAPI Reset: 0x%x\n",
		     info->ConfigData.ATAConfig & ATACFG_ATAPI_RESET);
	usb_stor_dbg(us, "      ATA Timing: 0x%x\n",
		     info->ConfigData.ATAConfig & ATACFG_TIMING);
	usb_stor_dbg(us, "      ATA Major Command: 0x%x\n",
		     info->ConfigData.ATAMajorCommand);
	usb_stor_dbg(us, "      ATA Minor Command: 0x%x\n",
		     info->ConfigData.ATAMinorCommand);
	usb_stor_dbg(us, "      Init Status: 0x%x\n",
		     info->ConfigData.ATAExtraConfig & ATACFGE_INIT_STATUS);
	usb_stor_dbg(us, "      Config Descriptor 2: 0x%x\n",
		     info->ConfigData.ATAExtraConfig & ATACFGE_CONF_DESC2);
	usb_stor_dbg(us, "      Skip Device Boot: 0x%x\n",
		     info->ConfigData.ATAExtraConfig & ATACFGE_SKIP_BOOT);
	usb_stor_dbg(us, "      ATA 3 State Suspend: 0x%x\n",
		     info->ConfigData.ATAExtraConfig & ATACFGE_STATE_SUSPEND);
	usb_stor_dbg(us, "      Descriptor Override: 0x%x\n",
		     info->ConfigData.ATAExtraConfig & ATACFGE_DESC_OVERRIDE);
	usb_stor_dbg(us, "      Last LUN Identifier: 0x%x\n",
		     info->ConfigData.ATAExtraConfig & ATACFGE_LAST_LUN);
	usb_stor_dbg(us, "      SRST Enable: 0x%x\n",
		     info->ConfigData.ATAExtraConfig & CFG_CAPABILITY_SRST);
पूर्ण
#पूर्ण_अगर

/**************************************************************************
 * isd200_ग_लिखो_config
 *									 
 * Write the ISD200 Configuration data
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_ग_लिखो_config( काष्ठा us_data *us ) 
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	पूर्णांक retStatus = ISD200_GOOD;
	पूर्णांक result;

#अगर_घोषित CONFIG_USB_STORAGE_DEBUG
	usb_stor_dbg(us, "Entering isd200_write_config\n");
	usb_stor_dbg(us, "   Writing the following ISD200 Config Data:\n");
	isd200_log_config(us, info);
#पूर्ण_अगर

	/* let's send the command via the control pipe */
	result = usb_stor_ctrl_transfer(
		us, 
		us->send_ctrl_pipe,
		0x01, 
		USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
		0x0000, 
		0x0002, 
		(व्योम *) &info->ConfigData, 
		माप(info->ConfigData));

	अगर (result >= 0) अणु
		usb_stor_dbg(us, "   ISD200 Config Data was written successfully\n");
	पूर्ण अन्यथा अणु
		usb_stor_dbg(us, "   Request to write ISD200 Config Data failed!\n");
		retStatus = ISD200_ERROR;
	पूर्ण

	usb_stor_dbg(us, "Leaving isd200_write_config %08X\n", retStatus);
	वापस retStatus;
पूर्ण


/**************************************************************************
 * isd200_पढ़ो_config
 *									 
 * Reads the ISD200 Configuration data
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_पढ़ो_config( काष्ठा us_data *us ) 
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	पूर्णांक retStatus = ISD200_GOOD;
	पूर्णांक result;

	usb_stor_dbg(us, "Entering isd200_read_config\n");

	/* पढ़ो the configuration inक्रमmation from ISD200.  Use this to */
	/* determine what the special ATA CDB bytes are.		*/

	result = usb_stor_ctrl_transfer(
		us, 
		us->recv_ctrl_pipe,
		0x02, 
		USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
		0x0000, 
		0x0002, 
		(व्योम *) &info->ConfigData, 
		माप(info->ConfigData));


	अगर (result >= 0) अणु
		usb_stor_dbg(us, "   Retrieved the following ISD200 Config Data:\n");
#अगर_घोषित CONFIG_USB_STORAGE_DEBUG
		isd200_log_config(us, info);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		usb_stor_dbg(us, "   Request to get ISD200 Config Data failed!\n");
		retStatus = ISD200_ERROR;
	पूर्ण

	usb_stor_dbg(us, "Leaving isd200_read_config %08X\n", retStatus);
	वापस retStatus;
पूर्ण


/**************************************************************************
 * isd200_atapi_soft_reset
 *									 
 * Perक्रमm an Atapi Soft Reset on the device
 *
 * RETURNS:
 *    NT status code
 */
अटल पूर्णांक isd200_atapi_soft_reset( काष्ठा us_data *us ) 
अणु
	पूर्णांक retStatus = ISD200_GOOD;
	पूर्णांक transferStatus;

	usb_stor_dbg(us, "Entering isd200_atapi_soft_reset\n");

	transferStatus = isd200_action( us, ACTION_SOFT_RESET, शून्य, 0 );
	अगर (transferStatus != ISD200_TRANSPORT_GOOD) अणु
		usb_stor_dbg(us, "   Error issuing Atapi Soft Reset\n");
		retStatus = ISD200_ERROR;
	पूर्ण

	usb_stor_dbg(us, "Leaving isd200_atapi_soft_reset %08X\n", retStatus);
	वापस retStatus;
पूर्ण


/**************************************************************************
 * isd200_srst
 *									 
 * Perक्रमm an SRST on the device
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_srst( काष्ठा us_data *us ) 
अणु
	पूर्णांक retStatus = ISD200_GOOD;
	पूर्णांक transferStatus;

	usb_stor_dbg(us, "Entering isd200_SRST\n");

	transferStatus = isd200_action( us, ACTION_RESET, शून्य, 0 );

	/* check to see अगर this request failed */
	अगर (transferStatus != ISD200_TRANSPORT_GOOD) अणु
		usb_stor_dbg(us, "   Error issuing SRST\n");
		retStatus = ISD200_ERROR;
	पूर्ण अन्यथा अणु
		/* delay 10ms to give the drive a chance to see it */
		msleep(10);

		transferStatus = isd200_action( us, ACTION_REENABLE, शून्य, 0 );
		अगर (transferStatus != ISD200_TRANSPORT_GOOD) अणु
			usb_stor_dbg(us, "   Error taking drive out of reset\n");
			retStatus = ISD200_ERROR;
		पूर्ण अन्यथा अणु
			/* delay 50ms to give the drive a chance to recover after SRST */
			msleep(50);
		पूर्ण
	पूर्ण

	usb_stor_dbg(us, "Leaving isd200_srst %08X\n", retStatus);
	वापस retStatus;
पूर्ण


/**************************************************************************
 * isd200_try_क्रमागत
 *									 
 * Helper function क्रम isd200_manual_क्रमागत(). Does ENUM and READ_STATUS
 * and tries to analyze the status रेजिस्टरs
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_try_क्रमागत(काष्ठा us_data *us, अचिन्हित अक्षर master_slave,
			   पूर्णांक detect )
अणु
	पूर्णांक status = ISD200_GOOD;
	अचिन्हित दीर्घ endTime;
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	अचिन्हित अक्षर *regs = info->RegsBuf;
	पूर्णांक recheckAsMaster = 0;

	अगर ( detect )
		endTime = jअगरfies + ISD200_ENUM_DETECT_TIMEOUT * HZ;
	अन्यथा
		endTime = jअगरfies + ISD200_ENUM_BSY_TIMEOUT * HZ;

	/* loop until we detect !BSY or समयout */
	जबतक(1) अणु

		status = isd200_action( us, ACTION_ENUM, शून्य, master_slave );
		अगर ( status != ISD200_GOOD )
			अवरोध;

		status = isd200_action( us, ACTION_READ_STATUS, 
					regs, 8 );
		अगर ( status != ISD200_GOOD )
			अवरोध;

		अगर (!detect) अणु
			अगर (regs[ATA_REG_STATUS_OFFSET] & ATA_BUSY) अणु
				usb_stor_dbg(us, "   %s status is still BSY, try again...\n",
					     master_slave == ATA_ADDRESS_DEVHEAD_STD ?
					     "Master" : "Slave");
			पूर्ण अन्यथा अणु
				usb_stor_dbg(us, "   %s status !BSY, continue with next operation\n",
					     master_slave == ATA_ADDRESS_DEVHEAD_STD ?
					     "Master" : "Slave");
				अवरोध;
			पूर्ण
		पूर्ण
		/* check क्रम ATA_BUSY and */
		/* ATA_DF (workaround ATA Zip drive) and */
		/* ATA_ERR (workaround क्रम Archos CD-ROM) */
		अन्यथा अगर (regs[ATA_REG_STATUS_OFFSET] &
			 (ATA_BUSY | ATA_DF | ATA_ERR)) अणु
			usb_stor_dbg(us, "   Status indicates it is not ready, try again...\n");
		पूर्ण
		/* check क्रम DRDY, ATA devices set DRDY after SRST */
		अन्यथा अगर (regs[ATA_REG_STATUS_OFFSET] & ATA_DRDY) अणु
			usb_stor_dbg(us, "   Identified ATA device\n");
			info->DeviceFlags |= DF_ATA_DEVICE;
			info->DeviceHead = master_slave;
			अवरोध;
		पूर्ण 
		/*
		 * check Cylinder High/Low to
		 * determine अगर it is an ATAPI device
		 */
		अन्यथा अगर (regs[ATA_REG_HCYL_OFFSET] == 0xEB &&
			 regs[ATA_REG_LCYL_OFFSET] == 0x14) अणु
			/*
			 * It seems that the RICOH
			 * MP6200A CD/RW drive will
			 * report itself okay as a
			 * slave when it is really a
			 * master. So this check again
			 * as a master device just to
			 * make sure it करोesn't report
			 * itself okay as a master also
			 */
			अगर ((master_slave & ATA_ADDRESS_DEVHEAD_SLAVE) &&
			    !recheckAsMaster) अणु
				usb_stor_dbg(us, "   Identified ATAPI device as slave.  Rechecking again as master\n");
				recheckAsMaster = 1;
				master_slave = ATA_ADDRESS_DEVHEAD_STD;
			पूर्ण अन्यथा अणु
				usb_stor_dbg(us, "   Identified ATAPI device\n");
				info->DeviceHead = master_slave;
			      
				status = isd200_atapi_soft_reset(us);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "   Not ATA, not ATAPI - Weird\n");
			अवरोध;
		पूर्ण

		/* check क्रम समयout on this request */
		अगर (समय_after_eq(jअगरfies, endTime)) अणु
			अगर (!detect)
				usb_stor_dbg(us, "   BSY check timeout, just continue with next operation...\n");
			अन्यथा
				usb_stor_dbg(us, "   Device detect timeout!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**************************************************************************
 * isd200_manual_क्रमागत
 *									 
 * Determines अगर the drive attached is an ATA or ATAPI and अगर it is a
 * master or slave.
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_manual_क्रमागत(काष्ठा us_data *us)
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	पूर्णांक retStatus = ISD200_GOOD;

	usb_stor_dbg(us, "Entering isd200_manual_enum\n");

	retStatus = isd200_पढ़ो_config(us);
	अगर (retStatus == ISD200_GOOD) अणु
		पूर्णांक isslave;
		/* master or slave? */
		retStatus = isd200_try_क्रमागत( us, ATA_ADDRESS_DEVHEAD_STD, 0);
		अगर (retStatus == ISD200_GOOD)
			retStatus = isd200_try_क्रमागत( us, ATA_ADDRESS_DEVHEAD_SLAVE, 0);

		अगर (retStatus == ISD200_GOOD) अणु
			retStatus = isd200_srst(us);
			अगर (retStatus == ISD200_GOOD)
				/* ata or atapi? */
				retStatus = isd200_try_क्रमागत( us, ATA_ADDRESS_DEVHEAD_STD, 1);
		पूर्ण

		isslave = (info->DeviceHead & ATA_ADDRESS_DEVHEAD_SLAVE) ? 1 : 0;
		अगर (!(info->ConfigData.ATAConfig & ATACFG_MASTER)) अणु
			usb_stor_dbg(us, "   Setting Master/Slave selection to %d\n",
				     isslave);
			info->ConfigData.ATAConfig &= 0x3f;
			info->ConfigData.ATAConfig |= (isslave<<6);
			retStatus = isd200_ग_लिखो_config(us);
		पूर्ण
	पूर्ण

	usb_stor_dbg(us, "Leaving isd200_manual_enum %08X\n", retStatus);
	वापस(retStatus);
पूर्ण

अटल व्योम isd200_fix_driveid(u16 *id)
अणु
#अगर_अघोषित __LITTLE_ENDIAN
# अगरdef __BIG_ENDIAN
	पूर्णांक i;

	क्रम (i = 0; i < ATA_ID_WORDS; i++)
		id[i] = __le16_to_cpu(id[i]);
# अन्यथा
#  error "Please fix <asm/byteorder.h>"
# endअगर
#पूर्ण_अगर
पूर्ण

अटल व्योम isd200_dump_driveid(काष्ठा us_data *us, u16 *id)
अणु
	usb_stor_dbg(us, "   Identify Data Structure:\n");
	usb_stor_dbg(us, "      config = 0x%x\n",	id[ATA_ID_CONFIG]);
	usb_stor_dbg(us, "      cyls = 0x%x\n",		id[ATA_ID_CYLS]);
	usb_stor_dbg(us, "      heads = 0x%x\n",	id[ATA_ID_HEADS]);
	usb_stor_dbg(us, "      track_bytes = 0x%x\n",	id[4]);
	usb_stor_dbg(us, "      sector_bytes = 0x%x\n", id[5]);
	usb_stor_dbg(us, "      sectors = 0x%x\n",	id[ATA_ID_SECTORS]);
	usb_stor_dbg(us, "      serial_no[0] = 0x%x\n", *(अक्षर *)&id[ATA_ID_SERNO]);
	usb_stor_dbg(us, "      buf_type = 0x%x\n",	id[20]);
	usb_stor_dbg(us, "      buf_size = 0x%x\n",	id[ATA_ID_BUF_SIZE]);
	usb_stor_dbg(us, "      ecc_bytes = 0x%x\n",	id[22]);
	usb_stor_dbg(us, "      fw_rev[0] = 0x%x\n",	*(अक्षर *)&id[ATA_ID_FW_REV]);
	usb_stor_dbg(us, "      model[0] = 0x%x\n",	*(अक्षर *)&id[ATA_ID_PROD]);
	usb_stor_dbg(us, "      max_multsect = 0x%x\n", id[ATA_ID_MAX_MULTSECT] & 0xff);
	usb_stor_dbg(us, "      dword_io = 0x%x\n",	id[ATA_ID_DWORD_IO]);
	usb_stor_dbg(us, "      capability = 0x%x\n",	id[ATA_ID_CAPABILITY] >> 8);
	usb_stor_dbg(us, "      tPIO = 0x%x\n",	  id[ATA_ID_OLD_PIO_MODES] >> 8);
	usb_stor_dbg(us, "      tDMA = 0x%x\n",	  id[ATA_ID_OLD_DMA_MODES] >> 8);
	usb_stor_dbg(us, "      field_valid = 0x%x\n",	id[ATA_ID_FIELD_VALID]);
	usb_stor_dbg(us, "      cur_cyls = 0x%x\n",	id[ATA_ID_CUR_CYLS]);
	usb_stor_dbg(us, "      cur_heads = 0x%x\n",	id[ATA_ID_CUR_HEADS]);
	usb_stor_dbg(us, "      cur_sectors = 0x%x\n",	id[ATA_ID_CUR_SECTORS]);
	usb_stor_dbg(us, "      cur_capacity = 0x%x\n", ata_id_u32(id, 57));
	usb_stor_dbg(us, "      multsect = 0x%x\n",	id[ATA_ID_MULTSECT] & 0xff);
	usb_stor_dbg(us, "      lba_capacity = 0x%x\n", ata_id_u32(id, ATA_ID_LBA_CAPACITY));
	usb_stor_dbg(us, "      command_set_1 = 0x%x\n", id[ATA_ID_COMMAND_SET_1]);
	usb_stor_dbg(us, "      command_set_2 = 0x%x\n", id[ATA_ID_COMMAND_SET_2]);
पूर्ण

/**************************************************************************
 * isd200_get_inquiry_data
 *
 * Get inquiry data
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_get_inquiry_data( काष्ठा us_data *us )
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	पूर्णांक retStatus = ISD200_GOOD;
	u16 *id = info->id;

	usb_stor_dbg(us, "Entering isd200_get_inquiry_data\n");

	/* set शेष to Master */
	info->DeviceHead = ATA_ADDRESS_DEVHEAD_STD;

	/* attempt to manually क्रमागतerate this device */
	retStatus = isd200_manual_क्रमागत(us);
	अगर (retStatus == ISD200_GOOD) अणु
		पूर्णांक transferStatus;

		/* check क्रम an ATA device */
		अगर (info->DeviceFlags & DF_ATA_DEVICE) अणु
			/* this must be an ATA device */
			/* perक्रमm an ATA Command Identअगरy */
			transferStatus = isd200_action( us, ACTION_IDENTIFY,
							id, ATA_ID_WORDS * 2);
			अगर (transferStatus != ISD200_TRANSPORT_GOOD) अणु
				/* Error issuing ATA Command Identअगरy */
				usb_stor_dbg(us, "   Error issuing ATA Command Identify\n");
				retStatus = ISD200_ERROR;
			पूर्ण अन्यथा अणु
				/* ATA Command Identअगरy successful */
				पूर्णांक i;
				__be16 *src;
				__u16 *dest;

				isd200_fix_driveid(id);
				isd200_dump_driveid(us, id);

				स_रखो(&info->InquiryData, 0, माप(info->InquiryData));

				/* Standard IDE पूर्णांकerface only supports disks */
				info->InquiryData.DeviceType = सूचीECT_ACCESS_DEVICE;

				/* The length must be at least 36 (5 + 31) */
				info->InquiryData.AdditionalLength = 0x1F;

				अगर (id[ATA_ID_COMMAND_SET_1] & COMMANDSET_MEDIA_STATUS) अणु
					/* set the removable bit */
					info->InquiryData.DeviceTypeModअगरier = DEVICE_REMOVABLE;
					info->DeviceFlags |= DF_REMOVABLE_MEDIA;
				पूर्ण

				/* Fill in venकरोr identअगरication fields */
				src = (__be16 *)&id[ATA_ID_PROD];
				dest = (__u16*)info->InquiryData.VenकरोrId;
				क्रम (i = 0; i < 4; i++)
					dest[i] = be16_to_cpu(src[i]);

				src = (__be16 *)&id[ATA_ID_PROD + 8/2];
				dest = (__u16*)info->InquiryData.ProductId;
				क्रम (i=0;i<8;i++)
					dest[i] = be16_to_cpu(src[i]);

				src = (__be16 *)&id[ATA_ID_FW_REV];
				dest = (__u16*)info->InquiryData.ProductRevisionLevel;
				क्रम (i=0;i<2;i++)
					dest[i] = be16_to_cpu(src[i]);

				/* determine अगर it supports Media Status Notअगरication */
				अगर (id[ATA_ID_COMMAND_SET_2] & COMMANDSET_MEDIA_STATUS) अणु
					usb_stor_dbg(us, "   Device supports Media Status Notification\n");

					/*
					 * Indicate that it is enabled, even
					 * though it is not.
					 * This allows the lock/unlock of the
					 * media to work correctly.
					 */
					info->DeviceFlags |= DF_MEDIA_STATUS_ENABLED;
				पूर्ण
				अन्यथा
					info->DeviceFlags &= ~DF_MEDIA_STATUS_ENABLED;

			पूर्ण
		पूर्ण अन्यथा अणु
			/* 
			 * this must be an ATAPI device 
			 * use an ATAPI protocol (Transparent SCSI)
			 */
			us->protocol_name = "Transparent SCSI";
			us->proto_handler = usb_stor_transparent_scsi_command;

			usb_stor_dbg(us, "Protocol changed to: %s\n",
				     us->protocol_name);
	    
			/* Free driver काष्ठाure */
			us->extra_deकाष्ठाor(info);
			kमुक्त(info);
			us->extra = शून्य;
			us->extra_deकाष्ठाor = शून्य;
		पूर्ण
	पूर्ण

	usb_stor_dbg(us, "Leaving isd200_get_inquiry_data %08X\n", retStatus);

	वापस(retStatus);
पूर्ण

/**************************************************************************
 * isd200_scsi_to_ata
 *									 
 * Translate SCSI commands to ATA commands.
 *
 * RETURNS:
 *    1 अगर the command needs to be sent to the transport layer
 *    0 otherwise
 */
अटल पूर्णांक isd200_scsi_to_ata(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us,
			      जोड़ ata_cdb * ataCdb)
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *)us->extra;
	u16 *id = info->id;
	पूर्णांक sendToTransport = 1;
	अचिन्हित अक्षर sectnum, head;
	अचिन्हित लघु cylinder;
	अचिन्हित दीर्घ lba;
	अचिन्हित दीर्घ blockCount;
	अचिन्हित अक्षर senseData[8] = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	स_रखो(ataCdb, 0, माप(जोड़ ata_cdb));

	/* SCSI Command */
	चयन (srb->cmnd[0]) अणु
	हाल INQUIRY:
		usb_stor_dbg(us, "   ATA OUT - INQUIRY\n");

		/* copy InquiryData */
		usb_stor_set_xfer_buf((अचिन्हित अक्षर *) &info->InquiryData,
				माप(info->InquiryData), srb);
		srb->result = SAM_STAT_GOOD;
		sendToTransport = 0;
		अवरोध;

	हाल MODE_SENSE:
		usb_stor_dbg(us, "   ATA OUT - SCSIOP_MODE_SENSE\n");

		/* Initialize the वापस buffer */
		usb_stor_set_xfer_buf(senseData, माप(senseData), srb);

		अगर (info->DeviceFlags & DF_MEDIA_STATUS_ENABLED)
		अणु
			ataCdb->generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
			ataCdb->generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
			ataCdb->generic.TransferBlockSize = 1;
			ataCdb->generic.RegisterSelect = REG_COMMAND;
			ataCdb->ग_लिखो.CommandByte = ATA_COMMAND_GET_MEDIA_STATUS;
			isd200_srb_set_bufflen(srb, 0);
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "   Media Status not supported, just report okay\n");
			srb->result = SAM_STAT_GOOD;
			sendToTransport = 0;
		पूर्ण
		अवरोध;

	हाल TEST_UNIT_READY:
		usb_stor_dbg(us, "   ATA OUT - SCSIOP_TEST_UNIT_READY\n");

		अगर (info->DeviceFlags & DF_MEDIA_STATUS_ENABLED)
		अणु
			ataCdb->generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
			ataCdb->generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
			ataCdb->generic.TransferBlockSize = 1;
			ataCdb->generic.RegisterSelect = REG_COMMAND;
			ataCdb->ग_लिखो.CommandByte = ATA_COMMAND_GET_MEDIA_STATUS;
			isd200_srb_set_bufflen(srb, 0);
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "   Media Status not supported, just report okay\n");
			srb->result = SAM_STAT_GOOD;
			sendToTransport = 0;
		पूर्ण
		अवरोध;

	हाल READ_CAPACITY:
	अणु
		अचिन्हित दीर्घ capacity;
		काष्ठा पढ़ो_capacity_data पढ़ोCapacityData;

		usb_stor_dbg(us, "   ATA OUT - SCSIOP_READ_CAPACITY\n");

		अगर (ata_id_has_lba(id))
			capacity = ata_id_u32(id, ATA_ID_LBA_CAPACITY) - 1;
		अन्यथा
			capacity = (id[ATA_ID_HEADS] * id[ATA_ID_CYLS] *
				    id[ATA_ID_SECTORS]) - 1;

		पढ़ोCapacityData.LogicalBlockAddress = cpu_to_be32(capacity);
		पढ़ोCapacityData.BytesPerBlock = cpu_to_be32(0x200);

		usb_stor_set_xfer_buf((अचिन्हित अक्षर *) &पढ़ोCapacityData,
				माप(पढ़ोCapacityData), srb);
		srb->result = SAM_STAT_GOOD;
		sendToTransport = 0;
	पूर्ण
	अवरोध;

	हाल READ_10:
		usb_stor_dbg(us, "   ATA OUT - SCSIOP_READ\n");

		lba = be32_to_cpu(*(__be32 *)&srb->cmnd[2]);
		blockCount = (अचिन्हित दीर्घ)srb->cmnd[7]<<8 | (अचिन्हित दीर्घ)srb->cmnd[8];

		अगर (ata_id_has_lba(id)) अणु
			sectnum = (अचिन्हित अक्षर)(lba);
			cylinder = (अचिन्हित लघु)(lba>>8);
			head = ATA_ADDRESS_DEVHEAD_LBA_MODE | (अचिन्हित अक्षर)(lba>>24 & 0x0F);
		पूर्ण अन्यथा अणु
			sectnum = (u8)((lba % id[ATA_ID_SECTORS]) + 1);
			cylinder = (u16)(lba / (id[ATA_ID_SECTORS] *
					id[ATA_ID_HEADS]));
			head = (u8)((lba / id[ATA_ID_SECTORS]) %
					id[ATA_ID_HEADS]);
		पूर्ण
		ataCdb->generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
		ataCdb->generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
		ataCdb->generic.TransferBlockSize = 1;
		ataCdb->generic.RegisterSelect =
		  REG_SECTOR_COUNT | REG_SECTOR_NUMBER |
		  REG_CYLINDER_LOW | REG_CYLINDER_HIGH |
		  REG_DEVICE_HEAD  | REG_COMMAND;
		ataCdb->ग_लिखो.SectorCountByte = (अचिन्हित अक्षर)blockCount;
		ataCdb->ग_लिखो.SectorNumberByte = sectnum;
		ataCdb->ग_लिखो.CylinderHighByte = (अचिन्हित अक्षर)(cylinder>>8);
		ataCdb->ग_लिखो.CylinderLowByte = (अचिन्हित अक्षर)cylinder;
		ataCdb->ग_लिखो.DeviceHeadByte = (head | ATA_ADDRESS_DEVHEAD_STD);
		ataCdb->ग_लिखो.CommandByte = ATA_CMD_PIO_READ;
		अवरोध;

	हाल WRITE_10:
		usb_stor_dbg(us, "   ATA OUT - SCSIOP_WRITE\n");

		lba = be32_to_cpu(*(__be32 *)&srb->cmnd[2]);
		blockCount = (अचिन्हित दीर्घ)srb->cmnd[7]<<8 | (अचिन्हित दीर्घ)srb->cmnd[8];

		अगर (ata_id_has_lba(id)) अणु
			sectnum = (अचिन्हित अक्षर)(lba);
			cylinder = (अचिन्हित लघु)(lba>>8);
			head = ATA_ADDRESS_DEVHEAD_LBA_MODE | (अचिन्हित अक्षर)(lba>>24 & 0x0F);
		पूर्ण अन्यथा अणु
			sectnum = (u8)((lba % id[ATA_ID_SECTORS]) + 1);
			cylinder = (u16)(lba / (id[ATA_ID_SECTORS] *
					id[ATA_ID_HEADS]));
			head = (u8)((lba / id[ATA_ID_SECTORS]) %
					id[ATA_ID_HEADS]);
		पूर्ण
		ataCdb->generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
		ataCdb->generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
		ataCdb->generic.TransferBlockSize = 1;
		ataCdb->generic.RegisterSelect =
		  REG_SECTOR_COUNT | REG_SECTOR_NUMBER |
		  REG_CYLINDER_LOW | REG_CYLINDER_HIGH |
		  REG_DEVICE_HEAD  | REG_COMMAND;
		ataCdb->ग_लिखो.SectorCountByte = (अचिन्हित अक्षर)blockCount;
		ataCdb->ग_लिखो.SectorNumberByte = sectnum;
		ataCdb->ग_लिखो.CylinderHighByte = (अचिन्हित अक्षर)(cylinder>>8);
		ataCdb->ग_लिखो.CylinderLowByte = (अचिन्हित अक्षर)cylinder;
		ataCdb->ग_लिखो.DeviceHeadByte = (head | ATA_ADDRESS_DEVHEAD_STD);
		ataCdb->ग_लिखो.CommandByte = ATA_CMD_PIO_WRITE;
		अवरोध;

	हाल ALLOW_MEDIUM_REMOVAL:
		usb_stor_dbg(us, "   ATA OUT - SCSIOP_MEDIUM_REMOVAL\n");

		अगर (info->DeviceFlags & DF_REMOVABLE_MEDIA) अणु
			usb_stor_dbg(us, "   srb->cmnd[4] = 0x%X\n",
				     srb->cmnd[4]);
	    
			ataCdb->generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
			ataCdb->generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
			ataCdb->generic.TransferBlockSize = 1;
			ataCdb->generic.RegisterSelect = REG_COMMAND;
			ataCdb->ग_लिखो.CommandByte = (srb->cmnd[4] & 0x1) ?
				ATA_CMD_MEDIA_LOCK : ATA_CMD_MEDIA_UNLOCK;
			isd200_srb_set_bufflen(srb, 0);
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "   Not removable media, just report okay\n");
			srb->result = SAM_STAT_GOOD;
			sendToTransport = 0;
		पूर्ण
		अवरोध;

	हाल START_STOP:    
		usb_stor_dbg(us, "   ATA OUT - SCSIOP_START_STOP_UNIT\n");
		usb_stor_dbg(us, "   srb->cmnd[4] = 0x%X\n", srb->cmnd[4]);

		अगर ((srb->cmnd[4] & 0x3) == 0x2) अणु
			usb_stor_dbg(us, "   Media Eject\n");
			ataCdb->generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
			ataCdb->generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
			ataCdb->generic.TransferBlockSize = 0;
			ataCdb->generic.RegisterSelect = REG_COMMAND;
			ataCdb->ग_लिखो.CommandByte = ATA_COMMAND_MEDIA_EJECT;
		पूर्ण अन्यथा अगर ((srb->cmnd[4] & 0x3) == 0x1) अणु
			usb_stor_dbg(us, "   Get Media Status\n");
			ataCdb->generic.SignatureByte0 = info->ConfigData.ATAMajorCommand;
			ataCdb->generic.SignatureByte1 = info->ConfigData.ATAMinorCommand;
			ataCdb->generic.TransferBlockSize = 1;
			ataCdb->generic.RegisterSelect = REG_COMMAND;
			ataCdb->ग_लिखो.CommandByte = ATA_COMMAND_GET_MEDIA_STATUS;
			isd200_srb_set_bufflen(srb, 0);
		पूर्ण अन्यथा अणु
			usb_stor_dbg(us, "   Nothing to do, just report okay\n");
			srb->result = SAM_STAT_GOOD;
			sendToTransport = 0;
		पूर्ण
		अवरोध;

	शेष:
		usb_stor_dbg(us, "Unsupported SCSI command - 0x%X\n",
			     srb->cmnd[0]);
		srb->result = DID_ERROR << 16;
		sendToTransport = 0;
		अवरोध;
	पूर्ण

	वापस(sendToTransport);
पूर्ण


/**************************************************************************
 * isd200_मुक्त_info
 *
 * Frees the driver काष्ठाure.
 */
अटल व्योम isd200_मुक्त_info_ptrs(व्योम *info_)
अणु
	काष्ठा isd200_info *info = (काष्ठा isd200_info *) info_;

	अगर (info) अणु
		kमुक्त(info->id);
		kमुक्त(info->RegsBuf);
		kमुक्त(info->srb.sense_buffer);
	पूर्ण
पूर्ण

/**************************************************************************
 * isd200_init_info
 *									 
 * Allocates (अगर necessary) and initializes the driver काष्ठाure.
 *
 * RETURNS:
 *    ISD status code
 */
अटल पूर्णांक isd200_init_info(काष्ठा us_data *us)
अणु
	काष्ठा isd200_info *info;

	info = kzalloc(माप(काष्ठा isd200_info), GFP_KERNEL);
	अगर (!info)
		वापस ISD200_ERROR;

	info->id = kzalloc(ATA_ID_WORDS * 2, GFP_KERNEL);
	info->RegsBuf = kदो_स्मृति(माप(info->ATARegs), GFP_KERNEL);
	info->srb.sense_buffer = kदो_स्मृति(SCSI_SENSE_BUFFERSIZE, GFP_KERNEL);

	अगर (!info->id || !info->RegsBuf || !info->srb.sense_buffer) अणु
		isd200_मुक्त_info_ptrs(info);
		kमुक्त(info);
		वापस ISD200_ERROR;
	पूर्ण

	us->extra = info;
	us->extra_deकाष्ठाor = isd200_मुक्त_info_ptrs;

	वापस ISD200_GOOD;
पूर्ण

/**************************************************************************
 * Initialization क्रम the ISD200 
 */

अटल पूर्णांक isd200_Initialization(काष्ठा us_data *us)
अणु
	usb_stor_dbg(us, "ISD200 Initialization...\n");

	/* Initialize ISD200 info काष्ठा */

	अगर (isd200_init_info(us) == ISD200_ERROR) अणु
		usb_stor_dbg(us, "ERROR Initializing ISD200 Info struct\n");
	पूर्ण अन्यथा अणु
		/* Get device specअगरic data */

		अगर (isd200_get_inquiry_data(us) != ISD200_GOOD)
			usb_stor_dbg(us, "ISD200 Initialization Failure\n");
		अन्यथा
			usb_stor_dbg(us, "ISD200 Initialization complete\n");
	पूर्ण

	वापस 0;
पूर्ण


/**************************************************************************
 * Protocol and Transport क्रम the ISD200 ASIC
 *
 * This protocol and transport are क्रम ATA devices connected to an ISD200
 * ASIC.  An ATAPI device that is connected as a slave device will be
 * detected in the driver initialization function and the protocol will
 * be changed to an ATAPI protocol (Transparent SCSI).
 *
 */

अटल व्योम isd200_ata_command(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक sendToTransport, orig_bufflen;
	जोड़ ata_cdb ataCdb;

	/* Make sure driver was initialized */

	अगर (us->extra == शून्य) अणु
		usb_stor_dbg(us, "ERROR Driver not initialized\n");
		srb->result = DID_ERROR << 16;
		वापस;
	पूर्ण

	scsi_set_resid(srb, 0);
	/* scsi_bufflen might change in protocol translation to ata */
	orig_bufflen = scsi_bufflen(srb);
	sendToTransport = isd200_scsi_to_ata(srb, us, &ataCdb);

	/* send the command to the transport layer */
	अगर (sendToTransport)
		isd200_invoke_transport(us, srb, &ataCdb);

	isd200_srb_set_bufflen(srb, orig_bufflen);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा isd200_host_ढाँचा;

अटल पूर्णांक isd200_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - isd200_usb_ids) + isd200_unusual_dev_list,
			&isd200_host_ढाँचा);
	अगर (result)
		वापस result;

	us->protocol_name = "ISD200 ATA/ATAPI";
	us->proto_handler = isd200_ata_command;

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver isd200_driver = अणु
	.name =		DRV_NAME,
	.probe =	isd200_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	isd200_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(isd200_driver, isd200_host_ढाँचा, DRV_NAME);
