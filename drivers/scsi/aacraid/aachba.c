<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Adaptec AAC series RAID controller driver
 *	(c) Copyright 2001 Red Hat Inc.
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver क्रम Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Sierra, Inc. (aacraid@pmc-sierra.com)
 *		 2016-2017 Microsemi Corp. (aacraid@microsemi.com)
 *
 * Module Name:
 *  aachba.c
 *
 * Abstract: Contains Interfaces to manage IOs.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/highस्मृति.स> /* For flush_kernel_dcache_page */
#समावेश <linux/module.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश "aacraid.h"

/* values क्रम inqd_pdt: Peripheral device type in plain English */
#घोषणा	INQD_PDT_DA	0x00	/* Direct-access (DISK) device */
#घोषणा	INQD_PDT_PROC	0x03	/* Processor device */
#घोषणा	INQD_PDT_CHNGR	0x08	/* Changer (jukebox, scsi2) */
#घोषणा	INQD_PDT_COMM	0x09	/* Communication device (scsi2) */
#घोषणा	INQD_PDT_NOLUN2 0x1f	/* Unknown Device (scsi2) */
#घोषणा	INQD_PDT_NOLUN	0x7f	/* Logical Unit Not Present */

#घोषणा	INQD_PDT_DMASK	0x1F	/* Peripheral Device Type Mask */
#घोषणा	INQD_PDT_QMASK	0xE0	/* Peripheral Device Qualअगरer Mask */

/*
 *	Sense codes
 */

#घोषणा SENCODE_NO_SENSE			0x00
#घोषणा SENCODE_END_OF_DATA			0x00
#घोषणा SENCODE_BECOMING_READY			0x04
#घोषणा SENCODE_INIT_CMD_REQUIRED		0x04
#घोषणा SENCODE_UNRECOVERED_READ_ERROR		0x11
#घोषणा SENCODE_PARAM_LIST_LENGTH_ERROR		0x1A
#घोषणा SENCODE_INVALID_COMMAND			0x20
#घोषणा SENCODE_LBA_OUT_OF_RANGE		0x21
#घोषणा SENCODE_INVALID_CDB_FIELD		0x24
#घोषणा SENCODE_LUN_NOT_SUPPORTED		0x25
#घोषणा SENCODE_INVALID_PARAM_FIELD		0x26
#घोषणा SENCODE_PARAM_NOT_SUPPORTED		0x26
#घोषणा SENCODE_PARAM_VALUE_INVALID		0x26
#घोषणा SENCODE_RESET_OCCURRED			0x29
#घोषणा SENCODE_LUN_NOT_SELF_CONFIGURED_YET	0x3E
#घोषणा SENCODE_INQUIRY_DATA_CHANGED		0x3F
#घोषणा SENCODE_SAVING_PARAMS_NOT_SUPPORTED	0x39
#घोषणा SENCODE_DIAGNOSTIC_FAILURE		0x40
#घोषणा SENCODE_INTERNAL_TARGET_FAILURE		0x44
#घोषणा SENCODE_INVALID_MESSAGE_ERROR		0x49
#घोषणा SENCODE_LUN_FAILED_SELF_CONFIG		0x4c
#घोषणा SENCODE_OVERLAPPED_COMMAND		0x4E

/*
 *	Additional sense codes
 */

#घोषणा ASENCODE_NO_SENSE			0x00
#घोषणा ASENCODE_END_OF_DATA			0x05
#घोषणा ASENCODE_BECOMING_READY			0x01
#घोषणा ASENCODE_INIT_CMD_REQUIRED		0x02
#घोषणा ASENCODE_PARAM_LIST_LENGTH_ERROR	0x00
#घोषणा ASENCODE_INVALID_COMMAND		0x00
#घोषणा ASENCODE_LBA_OUT_OF_RANGE		0x00
#घोषणा ASENCODE_INVALID_CDB_FIELD		0x00
#घोषणा ASENCODE_LUN_NOT_SUPPORTED		0x00
#घोषणा ASENCODE_INVALID_PARAM_FIELD		0x00
#घोषणा ASENCODE_PARAM_NOT_SUPPORTED		0x01
#घोषणा ASENCODE_PARAM_VALUE_INVALID		0x02
#घोषणा ASENCODE_RESET_OCCURRED			0x00
#घोषणा ASENCODE_LUN_NOT_SELF_CONFIGURED_YET	0x00
#घोषणा ASENCODE_INQUIRY_DATA_CHANGED		0x03
#घोषणा ASENCODE_SAVING_PARAMS_NOT_SUPPORTED	0x00
#घोषणा ASENCODE_DIAGNOSTIC_FAILURE		0x80
#घोषणा ASENCODE_INTERNAL_TARGET_FAILURE	0x00
#घोषणा ASENCODE_INVALID_MESSAGE_ERROR		0x00
#घोषणा ASENCODE_LUN_FAILED_SELF_CONFIG		0x00
#घोषणा ASENCODE_OVERLAPPED_COMMAND		0x00

#घोषणा BYTE0(x) (अचिन्हित अक्षर)(x)
#घोषणा BYTE1(x) (अचिन्हित अक्षर)((x) >> 8)
#घोषणा BYTE2(x) (अचिन्हित अक्षर)((x) >> 16)
#घोषणा BYTE3(x) (अचिन्हित अक्षर)((x) >> 24)

/* MODE_SENSE data क्रमmat */
प्रकार काष्ठा अणु
	काष्ठा अणु
		u8	data_length;
		u8	med_type;
		u8	dev_par;
		u8	bd_length;
	पूर्ण __attribute__((packed)) hd;
	काष्ठा अणु
		u8	dens_code;
		u8	block_count[3];
		u8	reserved;
		u8	block_length[3];
	पूर्ण __attribute__((packed)) bd;
		u8	mpc_buf[3];
पूर्ण __attribute__((packed)) aac_modep_data;

/* MODE_SENSE_10 data क्रमmat */
प्रकार काष्ठा अणु
	काष्ठा अणु
		u8	data_length[2];
		u8	med_type;
		u8	dev_par;
		u8	rsrvd[2];
		u8	bd_length[2];
	पूर्ण __attribute__((packed)) hd;
	काष्ठा अणु
		u8	dens_code;
		u8	block_count[3];
		u8	reserved;
		u8	block_length[3];
	पूर्ण __attribute__((packed)) bd;
		u8	mpc_buf[3];
पूर्ण __attribute__((packed)) aac_modep10_data;

/*------------------------------------------------------------------------------
 *              S T R U C T S / T Y P E D E F S
 *----------------------------------------------------------------------------*/
/* SCSI inquiry data */
काष्ठा inquiry_data अणु
	u8 inqd_pdt;	/* Peripheral qualअगरier | Peripheral Device Type */
	u8 inqd_dtq;	/* RMB | Device Type Qualअगरier */
	u8 inqd_ver;	/* ISO version | ECMA version | ANSI-approved version */
	u8 inqd_rdf;	/* AENC | TrmIOP | Response data क्रमmat */
	u8 inqd_len;	/* Additional length (n-4) */
	u8 inqd_pad1[2];/* Reserved - must be zero */
	u8 inqd_pad2;	/* RelAdr | WBus32 | WBus16 |  Sync  | Linked |Reserved| CmdQue | SftRe */
	u8 inqd_vid[8];	/* Venकरोr ID */
	u8 inqd_pid[16];/* Product ID */
	u8 inqd_prl[4];	/* Product Revision Level */
पूर्ण;

/* Added क्रम VPD 0x83 */
काष्ठा  tvpd_id_descriptor_type_1 अणु
	u8 codeset:4;		/* VPD_CODE_SET */
	u8 reserved:4;
	u8 identअगरiertype:4;	/* VPD_IDENTIFIER_TYPE */
	u8 reserved2:4;
	u8 reserved3;
	u8 identअगरierlength;
	u8 venid[8];
	u8 productid[16];
	u8 serialnumber[8];	/* SN in ASCII */

पूर्ण;

काष्ठा tvpd_id_descriptor_type_2 अणु
	u8 codeset:4;		/* VPD_CODE_SET */
	u8 reserved:4;
	u8 identअगरiertype:4;	/* VPD_IDENTIFIER_TYPE */
	u8 reserved2:4;
	u8 reserved3;
	u8 identअगरierlength;
	काष्ठा teu64id अणु
		u32 Serial;
		 /* The serial number supposed to be 40 bits,
		  * bit we only support 32, so make the last byte zero. */
		u8 reserved;
		u8 venid[3];
	पूर्ण eu64id;

पूर्ण;

काष्ठा tvpd_id_descriptor_type_3 अणु
	u8 codeset : 4;          /* VPD_CODE_SET */
	u8 reserved : 4;
	u8 identअगरiertype : 4;   /* VPD_IDENTIFIER_TYPE */
	u8 reserved2 : 4;
	u8 reserved3;
	u8 identअगरierlength;
	u8 Identअगरier[16];
पूर्ण;

काष्ठा tvpd_page83 अणु
	u8 DeviceType:5;
	u8 DeviceTypeQualअगरier:3;
	u8 PageCode;
	u8 reserved;
	u8 PageLength;
	काष्ठा tvpd_id_descriptor_type_1 type1;
	काष्ठा tvpd_id_descriptor_type_2 type2;
	काष्ठा tvpd_id_descriptor_type_3 type3;
पूर्ण;

/*
 *              M O D U L E   G L O B A L S
 */

अटल दीर्घ aac_build_sg(काष्ठा scsi_cmnd *scsicmd, काष्ठा sgmap *sgmap);
अटल दीर्घ aac_build_sg64(काष्ठा scsi_cmnd *scsicmd, काष्ठा sgmap64 *psg);
अटल दीर्घ aac_build_sgraw(काष्ठा scsi_cmnd *scsicmd, काष्ठा sgmapraw *psg);
अटल दीर्घ aac_build_sgraw2(काष्ठा scsi_cmnd *scsicmd,
				काष्ठा aac_raw_io2 *rio2, पूर्णांक sg_max);
अटल दीर्घ aac_build_sghba(काष्ठा scsi_cmnd *scsicmd,
				काष्ठा aac_hba_cmd_req *hbacmd,
				पूर्णांक sg_max, u64 sg_address);
अटल पूर्णांक aac_convert_sgraw2(काष्ठा aac_raw_io2 *rio2,
				पूर्णांक pages, पूर्णांक nseg, पूर्णांक nseg_new);
अटल पूर्णांक aac_send_srb_fib(काष्ठा scsi_cmnd* scsicmd);
अटल पूर्णांक aac_send_hba_fib(काष्ठा scsi_cmnd *scsicmd);
#अगर_घोषित AAC_DETAILED_STATUS_INFO
अटल अक्षर *aac_get_status_string(u32 status);
#पूर्ण_अगर

/*
 *	Non dasd selection is handled entirely in aachba now
 */

अटल पूर्णांक nondasd = -1;
अटल पूर्णांक aac_cache = 2;	/* WCE=0 to aव्योम perक्रमmance problems */
अटल पूर्णांक dacmode = -1;
पूर्णांक aac_msi;
पूर्णांक aac_commit = -1;
पूर्णांक startup_समयout = 180;
पूर्णांक aअगर_समयout = 120;
पूर्णांक aac_sync_mode;  /* Only Sync. transfer - disabled */
अटल पूर्णांक aac_convert_sgl = 1;	/* convert non-conक्रमmable s/g list - enabled */

module_param(aac_sync_mode, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(aac_sync_mode, "Force sync. transfer mode"
	" 0=off, 1=on");
module_param(aac_convert_sgl, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(aac_convert_sgl, "Convert non-conformable s/g list"
	" 0=off, 1=on");
module_param(nondasd, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(nondasd, "Control scanning of hba for nondasd devices."
	" 0=off, 1=on");
module_param_named(cache, aac_cache, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(cache, "Disable Queue Flush commands:\n"
	"\tbit 0 - Disable FUA in WRITE SCSI commands\n"
	"\tbit 1 - Disable SYNCHRONIZE_CACHE SCSI command\n"
	"\tbit 2 - Disable only if Battery is protecting Cache");
module_param(dacmode, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(dacmode, "Control whether dma addressing is using 64 bit DAC."
	" 0=off, 1=on");
module_param_named(commit, aac_commit, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(commit, "Control whether a COMMIT_CONFIG is issued to the"
	" adapter for foreign arrays.\n"
	"This is typically needed in systems that do not have a BIOS."
	" 0=off, 1=on");
module_param_named(msi, aac_msi, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(msi, "IRQ handling."
	" 0=PIC(default), 1=MSI, 2=MSI-X)");
module_param(startup_समयout, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(startup_समयout, "The duration of time in seconds to wait for"
	" adapter to have it's kernel up and\n"
	"running. This is typically adjusted for large systems that do not"
	" have a BIOS.");
module_param(aअगर_समयout, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(aअगर_समयout, "The duration of time in seconds to wait for"
	" applications to pick up AIFs before\n"
	"deregistering them. This is typically adjusted for heavily burdened"
	" systems.");

पूर्णांक aac_fib_dump;
module_param(aac_fib_dump, पूर्णांक, 0644);
MODULE_PARM_DESC(aac_fib_dump, "Dump controller fibs prior to IOP_RESET 0=off, 1=on");

पूर्णांक numacb = -1;
module_param(numacb, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(numacb, "Request a limit to the number of adapter control"
	" blocks (FIB) allocated. Valid values are 512 and down. Default is"
	" to use suggestion from Firmware.");

अटल पूर्णांक acbsize = -1;
module_param(acbsize, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(acbsize, "Request a specific adapter control block (FIB)"
	" size. Valid values are 512, 2048, 4096 and 8192. Default is to use"
	" suggestion from Firmware.");

पूर्णांक update_पूर्णांकerval = 30 * 60;
module_param(update_पूर्णांकerval, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(update_पूर्णांकerval, "Interval in seconds between time sync"
	" updates issued to adapter.");

पूर्णांक check_पूर्णांकerval = 60;
module_param(check_पूर्णांकerval, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(check_पूर्णांकerval, "Interval in seconds between adapter health"
	" checks.");

पूर्णांक aac_check_reset = 1;
module_param_named(check_reset, aac_check_reset, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(check_reset, "If adapter fails health check, reset the"
	" adapter. a value of -1 forces the reset to adapters programmed to"
	" ignore it.");

पूर्णांक expose_physicals = -1;
module_param(expose_physicals, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(expose_physicals, "Expose physical components of the arrays."
	" -1=protect 0=off, 1=on");

पूर्णांक aac_reset_devices;
module_param_named(reset_devices, aac_reset_devices, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(reset_devices, "Force an adapter reset at initialization.");

अटल पूर्णांक aac_wwn = 1;
module_param_named(wwn, aac_wwn, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(wwn, "Select a WWN type for the arrays:\n"
	"\t0 - Disable\n"
	"\t1 - Array Meta Data Signature (default)\n"
	"\t2 - Adapter Serial Number");


अटल अंतरभूत पूर्णांक aac_valid_context(काष्ठा scsi_cmnd *scsicmd,
		काष्ठा fib *fibptr) अणु
	काष्ठा scsi_device *device;

	अगर (unlikely(!scsicmd || !scsicmd->scsi_करोne)) अणु
		dprपूर्णांकk((KERN_WARNING "aac_valid_context: scsi command corrupt\n"));
		aac_fib_complete(fibptr);
		वापस 0;
	पूर्ण
	scsicmd->SCp.phase = AAC_OWNER_MIDLEVEL;
	device = scsicmd->device;
	अगर (unlikely(!device)) अणु
		dprपूर्णांकk((KERN_WARNING "aac_valid_context: scsi device corrupt\n"));
		aac_fib_complete(fibptr);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	aac_get_config_status	-	check the adapter configuration
 *	@dev: aac driver data
 *	@commit_flag: क्रमce sending CT_COMMIT_CONFIG
 *
 *	Query config status, and commit the configuration अगर needed.
 */
पूर्णांक aac_get_config_status(काष्ठा aac_dev *dev, पूर्णांक commit_flag)
अणु
	पूर्णांक status = 0;
	काष्ठा fib * fibptr;

	अगर (!(fibptr = aac_fib_alloc(dev)))
		वापस -ENOMEM;

	aac_fib_init(fibptr);
	अणु
		काष्ठा aac_get_config_status *dinfo;
		dinfo = (काष्ठा aac_get_config_status *) fib_data(fibptr);

		dinfo->command = cpu_to_le32(VM_ContainerConfig);
		dinfo->type = cpu_to_le32(CT_GET_CONFIG_STATUS);
		dinfo->count = cpu_to_le32(माप(((काष्ठा aac_get_config_status_resp *)शून्य)->data));
	पूर्ण

	status = aac_fib_send(ContainerCommand,
			    fibptr,
			    माप (काष्ठा aac_get_config_status),
			    FsaNormal,
			    1, 1,
			    शून्य, शून्य);
	अगर (status < 0) अणु
		prपूर्णांकk(KERN_WARNING "aac_get_config_status: SendFIB failed.\n");
	पूर्ण अन्यथा अणु
		काष्ठा aac_get_config_status_resp *reply
		  = (काष्ठा aac_get_config_status_resp *) fib_data(fibptr);
		dprपूर्णांकk((KERN_WARNING
		  "aac_get_config_status: response=%d status=%d action=%d\n",
		  le32_to_cpu(reply->response),
		  le32_to_cpu(reply->status),
		  le32_to_cpu(reply->data.action)));
		अगर ((le32_to_cpu(reply->response) != ST_OK) ||
		     (le32_to_cpu(reply->status) != CT_OK) ||
		     (le32_to_cpu(reply->data.action) > CFACT_PAUSE)) अणु
			prपूर्णांकk(KERN_WARNING "aac_get_config_status: Will not issue the Commit Configuration\n");
			status = -EINVAL;
		पूर्ण
	पूर्ण
	/* Do not set XferState to zero unless receives a response from F/W */
	अगर (status >= 0)
		aac_fib_complete(fibptr);

	/* Send a CT_COMMIT_CONFIG to enable discovery of devices */
	अगर (status >= 0) अणु
		अगर ((aac_commit == 1) || commit_flag) अणु
			काष्ठा aac_commit_config * dinfo;
			aac_fib_init(fibptr);
			dinfo = (काष्ठा aac_commit_config *) fib_data(fibptr);

			dinfo->command = cpu_to_le32(VM_ContainerConfig);
			dinfo->type = cpu_to_le32(CT_COMMIT_CONFIG);

			status = aac_fib_send(ContainerCommand,
				    fibptr,
				    माप (काष्ठा aac_commit_config),
				    FsaNormal,
				    1, 1,
				    शून्य, शून्य);
			/* Do not set XferState to zero unless
			 * receives a response from F/W */
			अगर (status >= 0)
				aac_fib_complete(fibptr);
		पूर्ण अन्यथा अगर (aac_commit == 0) अणु
			prपूर्णांकk(KERN_WARNING
			  "aac_get_config_status: Foreign device configurations are being ignored\n");
		पूर्ण
	पूर्ण
	/* FIB should be मुक्तd only after getting the response from the F/W */
	अगर (status != -ERESTARTSYS)
		aac_fib_मुक्त(fibptr);
	वापस status;
पूर्ण

अटल व्योम aac_expose_phy_device(काष्ठा scsi_cmnd *scsicmd)
अणु
	अक्षर inq_data;
	scsi_sg_copy_to_buffer(scsicmd,  &inq_data, माप(inq_data));
	अगर ((inq_data & 0x20) && (inq_data & 0x1f) == TYPE_DISK) अणु
		inq_data &= 0xdf;
		scsi_sg_copy_from_buffer(scsicmd, &inq_data, माप(inq_data));
	पूर्ण
पूर्ण

/**
 *	aac_get_containers	-	list containers
 *	@dev: aac driver data
 *
 *	Make a list of all containers on this controller
 */
पूर्णांक aac_get_containers(काष्ठा aac_dev *dev)
अणु
	काष्ठा fsa_dev_info *fsa_dev_ptr;
	u32 index;
	पूर्णांक status = 0;
	काष्ठा fib * fibptr;
	काष्ठा aac_get_container_count *dinfo;
	काष्ठा aac_get_container_count_resp *dresp;
	पूर्णांक maximum_num_containers = MAXIMUM_NUM_CONTAINERS;

	अगर (!(fibptr = aac_fib_alloc(dev)))
		वापस -ENOMEM;

	aac_fib_init(fibptr);
	dinfo = (काष्ठा aac_get_container_count *) fib_data(fibptr);
	dinfo->command = cpu_to_le32(VM_ContainerConfig);
	dinfo->type = cpu_to_le32(CT_GET_CONTAINER_COUNT);

	status = aac_fib_send(ContainerCommand,
		    fibptr,
		    माप (काष्ठा aac_get_container_count),
		    FsaNormal,
		    1, 1,
		    शून्य, शून्य);
	अगर (status >= 0) अणु
		dresp = (काष्ठा aac_get_container_count_resp *)fib_data(fibptr);
		maximum_num_containers = le32_to_cpu(dresp->ContainerSwitchEntries);
		अगर (fibptr->dev->supplement_adapter_info.supported_options2 &
		    AAC_OPTION_SUPPORTED_240_VOLUMES) अणु
			maximum_num_containers =
				le32_to_cpu(dresp->MaxSimpleVolumes);
		पूर्ण
		aac_fib_complete(fibptr);
	पूर्ण
	/* FIB should be मुक्तd only after getting the response from the F/W */
	अगर (status != -ERESTARTSYS)
		aac_fib_मुक्त(fibptr);

	अगर (maximum_num_containers < MAXIMUM_NUM_CONTAINERS)
		maximum_num_containers = MAXIMUM_NUM_CONTAINERS;
	अगर (dev->fsa_dev == शून्य ||
		dev->maximum_num_containers != maximum_num_containers) अणु

		fsa_dev_ptr = dev->fsa_dev;

		dev->fsa_dev = kसुस्मृति(maximum_num_containers,
					माप(*fsa_dev_ptr), GFP_KERNEL);

		kमुक्त(fsa_dev_ptr);
		fsa_dev_ptr = शून्य;


		अगर (!dev->fsa_dev)
			वापस -ENOMEM;

		dev->maximum_num_containers = maximum_num_containers;
	पूर्ण
	क्रम (index = 0; index < dev->maximum_num_containers; index++) अणु
		dev->fsa_dev[index].devname[0] = '\0';
		dev->fsa_dev[index].valid = 0;

		status = aac_probe_container(dev, index);

		अगर (status < 0) अणु
			prपूर्णांकk(KERN_WARNING "aac_get_containers: SendFIB failed.\n");
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम get_container_name_callback(व्योम *context, काष्ठा fib * fibptr)
अणु
	काष्ठा aac_get_name_resp * get_name_reply;
	काष्ठा scsi_cmnd * scsicmd;

	scsicmd = (काष्ठा scsi_cmnd *) context;

	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	dprपूर्णांकk((KERN_DEBUG "get_container_name_callback[cpu %d]: t = %ld.\n", smp_processor_id(), jअगरfies));
	BUG_ON(fibptr == शून्य);

	get_name_reply = (काष्ठा aac_get_name_resp *) fib_data(fibptr);
	/* Failure is irrelevant, using शेष value instead */
	अगर ((le32_to_cpu(get_name_reply->status) == CT_OK)
	 && (get_name_reply->data[0] != '\0')) अणु
		अक्षर *sp = get_name_reply->data;
		पूर्णांक data_size = माप_field(काष्ठा aac_get_name_resp, data);

		sp[data_size - 1] = '\0';
		जबतक (*sp == ' ')
			++sp;
		अगर (*sp) अणु
			काष्ठा inquiry_data inq;
			अक्षर d[माप(((काष्ठा inquiry_data *)शून्य)->inqd_pid)];
			पूर्णांक count = माप(d);
			अक्षर *dp = d;
			करो अणु
				*dp++ = (*sp) ? *sp++ : ' ';
			पूर्ण जबतक (--count > 0);

			scsi_sg_copy_to_buffer(scsicmd, &inq, माप(inq));
			स_नकल(inq.inqd_pid, d, माप(d));
			scsi_sg_copy_from_buffer(scsicmd, &inq, माप(inq));
		पूर्ण
	पूर्ण

	scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;

	aac_fib_complete(fibptr);
	scsicmd->scsi_करोne(scsicmd);
पूर्ण

/*
 *	aac_get_container_name	-	get container name, none blocking.
 */
अटल पूर्णांक aac_get_container_name(काष्ठा scsi_cmnd * scsicmd)
अणु
	पूर्णांक status;
	पूर्णांक data_size;
	काष्ठा aac_get_name *dinfo;
	काष्ठा fib * cmd_fibcontext;
	काष्ठा aac_dev * dev;

	dev = (काष्ठा aac_dev *)scsicmd->device->host->hostdata;

	data_size = माप_field(काष्ठा aac_get_name_resp, data);

	cmd_fibcontext = aac_fib_alloc_tag(dev, scsicmd);

	aac_fib_init(cmd_fibcontext);
	dinfo = (काष्ठा aac_get_name *) fib_data(cmd_fibcontext);
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;

	dinfo->command = cpu_to_le32(VM_ContainerConfig);
	dinfo->type = cpu_to_le32(CT_READ_NAME);
	dinfo->cid = cpu_to_le32(scmd_id(scsicmd));
	dinfo->count = cpu_to_le32(data_size - 1);

	status = aac_fib_send(ContainerCommand,
		  cmd_fibcontext,
		  माप(काष्ठा aac_get_name_resp),
		  FsaNormal,
		  0, 1,
		  (fib_callback)get_container_name_callback,
		  (व्योम *) scsicmd);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	prपूर्णांकk(KERN_WARNING "aac_get_container_name: aac_fib_send failed with status: %d.\n", status);
	aac_fib_complete(cmd_fibcontext);
	वापस -1;
पूर्ण

अटल पूर्णांक aac_probe_container_callback2(काष्ठा scsi_cmnd * scsicmd)
अणु
	काष्ठा fsa_dev_info *fsa_dev_ptr = ((काष्ठा aac_dev *)(scsicmd->device->host->hostdata))->fsa_dev;

	अगर ((fsa_dev_ptr[scmd_id(scsicmd)].valid & 1))
		वापस aac_scsi_cmd(scsicmd);

	scsicmd->result = DID_NO_CONNECT << 16;
	scsicmd->scsi_करोne(scsicmd);
	वापस 0;
पूर्ण

अटल व्योम _aac_probe_container2(व्योम * context, काष्ठा fib * fibptr)
अणु
	काष्ठा fsa_dev_info *fsa_dev_ptr;
	पूर्णांक (*callback)(काष्ठा scsi_cmnd *);
	काष्ठा scsi_cmnd * scsicmd = (काष्ठा scsi_cmnd *)context;
	पूर्णांक i;


	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	scsicmd->SCp.Status = 0;
	fsa_dev_ptr = fibptr->dev->fsa_dev;
	अगर (fsa_dev_ptr) अणु
		काष्ठा aac_mount * dresp = (काष्ठा aac_mount *) fib_data(fibptr);
		__le32 sup_options2;

		fsa_dev_ptr += scmd_id(scsicmd);
		sup_options2 =
			fibptr->dev->supplement_adapter_info.supported_options2;

		अगर ((le32_to_cpu(dresp->status) == ST_OK) &&
		    (le32_to_cpu(dresp->mnt[0].vol) != CT_NONE) &&
		    (le32_to_cpu(dresp->mnt[0].state) != FSCS_HIDDEN)) अणु
			अगर (!(sup_options2 & AAC_OPTION_VARIABLE_BLOCK_SIZE)) अणु
				dresp->mnt[0].fileinfo.bdevinfo.block_size = 0x200;
				fsa_dev_ptr->block_size = 0x200;
			पूर्ण अन्यथा अणु
				fsa_dev_ptr->block_size =
					le32_to_cpu(dresp->mnt[0].fileinfo.bdevinfo.block_size);
			पूर्ण
			क्रम (i = 0; i < 16; i++)
				fsa_dev_ptr->identअगरier[i] =
					dresp->mnt[0].fileinfo.bdevinfo
								.identअगरier[i];
			fsa_dev_ptr->valid = 1;
			/* sense_key holds the current state of the spin-up */
			अगर (dresp->mnt[0].state & cpu_to_le32(FSCS_NOT_READY))
				fsa_dev_ptr->sense_data.sense_key = NOT_READY;
			अन्यथा अगर (fsa_dev_ptr->sense_data.sense_key == NOT_READY)
				fsa_dev_ptr->sense_data.sense_key = NO_SENSE;
			fsa_dev_ptr->type = le32_to_cpu(dresp->mnt[0].vol);
			fsa_dev_ptr->size
			  = ((u64)le32_to_cpu(dresp->mnt[0].capacity)) +
			    (((u64)le32_to_cpu(dresp->mnt[0].capacityhigh)) << 32);
			fsa_dev_ptr->ro = ((le32_to_cpu(dresp->mnt[0].state) & FSCS_READONLY) != 0);
		पूर्ण
		अगर ((fsa_dev_ptr->valid & 1) == 0)
			fsa_dev_ptr->valid = 0;
		scsicmd->SCp.Status = le32_to_cpu(dresp->count);
	पूर्ण
	aac_fib_complete(fibptr);
	aac_fib_मुक्त(fibptr);
	callback = (पूर्णांक (*)(काष्ठा scsi_cmnd *))(scsicmd->SCp.ptr);
	scsicmd->SCp.ptr = शून्य;
	(*callback)(scsicmd);
	वापस;
पूर्ण

अटल व्योम _aac_probe_container1(व्योम * context, काष्ठा fib * fibptr)
अणु
	काष्ठा scsi_cmnd * scsicmd;
	काष्ठा aac_mount * dresp;
	काष्ठा aac_query_mount *dinfo;
	पूर्णांक status;

	dresp = (काष्ठा aac_mount *) fib_data(fibptr);
	अगर (!aac_supports_2T(fibptr->dev)) अणु
		dresp->mnt[0].capacityhigh = 0;
		अगर ((le32_to_cpu(dresp->status) == ST_OK) &&
			(le32_to_cpu(dresp->mnt[0].vol) != CT_NONE)) अणु
			_aac_probe_container2(context, fibptr);
			वापस;
		पूर्ण
	पूर्ण
	scsicmd = (काष्ठा scsi_cmnd *) context;

	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	aac_fib_init(fibptr);

	dinfo = (काष्ठा aac_query_mount *)fib_data(fibptr);

	अगर (fibptr->dev->supplement_adapter_info.supported_options2 &
	    AAC_OPTION_VARIABLE_BLOCK_SIZE)
		dinfo->command = cpu_to_le32(VM_NameServeAllBlk);
	अन्यथा
		dinfo->command = cpu_to_le32(VM_NameServe64);

	dinfo->count = cpu_to_le32(scmd_id(scsicmd));
	dinfo->type = cpu_to_le32(FT_खाताSYS);
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;

	status = aac_fib_send(ContainerCommand,
			  fibptr,
			  माप(काष्ठा aac_query_mount),
			  FsaNormal,
			  0, 1,
			  _aac_probe_container2,
			  (व्योम *) scsicmd);
	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status < 0 && status != -EINPROGRESS) अणु
		/* Inherit results from VM_NameServe, अगर any */
		dresp->status = cpu_to_le32(ST_OK);
		_aac_probe_container2(context, fibptr);
	पूर्ण
पूर्ण

अटल पूर्णांक _aac_probe_container(काष्ठा scsi_cmnd * scsicmd, पूर्णांक (*callback)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा fib * fibptr;
	पूर्णांक status = -ENOMEM;

	अगर ((fibptr = aac_fib_alloc((काष्ठा aac_dev *)scsicmd->device->host->hostdata))) अणु
		काष्ठा aac_query_mount *dinfo;

		aac_fib_init(fibptr);

		dinfo = (काष्ठा aac_query_mount *)fib_data(fibptr);

		अगर (fibptr->dev->supplement_adapter_info.supported_options2 &
		    AAC_OPTION_VARIABLE_BLOCK_SIZE)
			dinfo->command = cpu_to_le32(VM_NameServeAllBlk);
		अन्यथा
			dinfo->command = cpu_to_le32(VM_NameServe);

		dinfo->count = cpu_to_le32(scmd_id(scsicmd));
		dinfo->type = cpu_to_le32(FT_खाताSYS);
		scsicmd->SCp.ptr = (अक्षर *)callback;
		scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;

		status = aac_fib_send(ContainerCommand,
			  fibptr,
			  माप(काष्ठा aac_query_mount),
			  FsaNormal,
			  0, 1,
			  _aac_probe_container1,
			  (व्योम *) scsicmd);
		/*
		 *	Check that the command queued to the controller
		 */
		अगर (status == -EINPROGRESS)
			वापस 0;

		अगर (status < 0) अणु
			scsicmd->SCp.ptr = शून्य;
			aac_fib_complete(fibptr);
			aac_fib_मुक्त(fibptr);
		पूर्ण
	पूर्ण
	अगर (status < 0) अणु
		काष्ठा fsa_dev_info *fsa_dev_ptr = ((काष्ठा aac_dev *)(scsicmd->device->host->hostdata))->fsa_dev;
		अगर (fsa_dev_ptr) अणु
			fsa_dev_ptr += scmd_id(scsicmd);
			अगर ((fsa_dev_ptr->valid & 1) == 0) अणु
				fsa_dev_ptr->valid = 0;
				वापस (*callback)(scsicmd);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 *	aac_probe_container_callback1	-	query a logical volume
 *	@scsicmd: the scsi command block
 *
 *	Queries the controller about the given volume. The volume inक्रमmation
 *	is updated in the काष्ठा fsa_dev_info काष्ठाure rather than वापसed.
 */
अटल पूर्णांक aac_probe_container_callback1(काष्ठा scsi_cmnd * scsicmd)
अणु
	scsicmd->device = शून्य;
	वापस 0;
पूर्ण

अटल व्योम aac_probe_container_scsi_करोne(काष्ठा scsi_cmnd *scsi_cmnd)
अणु
	aac_probe_container_callback1(scsi_cmnd);
पूर्ण

पूर्णांक aac_probe_container(काष्ठा aac_dev *dev, पूर्णांक cid)
अणु
	काष्ठा scsi_cmnd *scsicmd = kदो_स्मृति(माप(*scsicmd), GFP_KERNEL);
	काष्ठा scsi_device *scsidev = kदो_स्मृति(माप(*scsidev), GFP_KERNEL);
	पूर्णांक status;

	अगर (!scsicmd || !scsidev) अणु
		kमुक्त(scsicmd);
		kमुक्त(scsidev);
		वापस -ENOMEM;
	पूर्ण
	scsicmd->scsi_करोne = aac_probe_container_scsi_करोne;

	scsicmd->device = scsidev;
	scsidev->sdev_state = 0;
	scsidev->id = cid;
	scsidev->host = dev->scsi_host_ptr;

	अगर (_aac_probe_container(scsicmd, aac_probe_container_callback1) == 0)
		जबतक (scsicmd->device == scsidev)
			schedule();
	kमुक्त(scsidev);
	status = scsicmd->SCp.Status;
	kमुक्त(scsicmd);
	वापस status;
पूर्ण

/* Local Structure to set SCSI inquiry data strings */
काष्ठा scsi_inq अणु
	अक्षर vid[8];         /* Venकरोr ID */
	अक्षर pid[16];        /* Product ID */
	अक्षर prl[4];         /* Product Revision Level */
पूर्ण;

/**
 *	inqम_नकल	-	string merge
 *	@a:	string to copy from
 *	@b:	string to copy to
 *
 *	Copy a String from one location to another
 *	without copying \0
 */

अटल व्योम inqम_नकल(अक्षर *a, अक्षर *b)
अणु

	जबतक (*a != (अक्षर)0)
		*b++ = *a++;
पूर्ण

अटल अक्षर *container_types[] = अणु
	"None",
	"Volume",
	"Mirror",
	"Stripe",
	"RAID5",
	"SSRW",
	"SSRO",
	"Morph",
	"Legacy",
	"RAID4",
	"RAID10",
	"RAID00",
	"V-MIRRORS",
	"PSEUDO R4",
	"RAID50",
	"RAID5D",
	"RAID5D0",
	"RAID1E",
	"RAID6",
	"RAID60",
	"Unknown"
पूर्ण;

अक्षर * get_container_type(अचिन्हित tindex)
अणु
	अगर (tindex >= ARRAY_SIZE(container_types))
		tindex = ARRAY_SIZE(container_types) - 1;
	वापस container_types[tindex];
पूर्ण

/* Function: setinqstr
 *
 * Arguments: [1] poपूर्णांकer to व्योम [1] पूर्णांक
 *
 * Purpose: Sets SCSI inquiry data strings क्रम venकरोr, product
 * and revision level. Allows strings to be set in platक्रमm dependent
 * files instead of in OS dependent driver source.
 */

अटल व्योम setinqstr(काष्ठा aac_dev *dev, व्योम *data, पूर्णांक tindex)
अणु
	काष्ठा scsi_inq *str;
	काष्ठा aac_supplement_adapter_info *sup_adap_info;

	sup_adap_info = &dev->supplement_adapter_info;
	str = (काष्ठा scsi_inq *)(data); /* cast data to scsi inq block */
	स_रखो(str, ' ', माप(*str));

	अगर (sup_adap_info->adapter_type_text[0]) अणु
		पूर्णांक c;
		अक्षर *cp;
		अक्षर *cname = kmemdup(sup_adap_info->adapter_type_text,
				माप(sup_adap_info->adapter_type_text),
								GFP_ATOMIC);
		अगर (!cname)
			वापस;

		cp = cname;
		अगर ((cp[0] == 'A') && (cp[1] == 'O') && (cp[2] == 'C'))
			inqम_नकल("SMC", str->vid);
		अन्यथा अणु
			c = माप(str->vid);
			जबतक (*cp && *cp != ' ' && --c)
				++cp;
			c = *cp;
			*cp = '\0';
			inqम_नकल(cname, str->vid);
			*cp = c;
			जबतक (*cp && *cp != ' ')
				++cp;
		पूर्ण
		जबतक (*cp == ' ')
			++cp;
		/* last six अक्षरs reserved क्रम vol type */
		अगर (म_माप(cp) > माप(str->pid))
			cp[माप(str->pid)] = '\0';
		inqम_नकल (cp, str->pid);

		kमुक्त(cname);
	पूर्ण अन्यथा अणु
		काष्ठा aac_driver_ident *mp = aac_get_driver_ident(dev->cardtype);

		inqम_नकल (mp->vname, str->vid);
		/* last six अक्षरs reserved क्रम vol type */
		inqम_नकल (mp->model, str->pid);
	पूर्ण

	अगर (tindex < ARRAY_SIZE(container_types))अणु
		अक्षर *findit = str->pid;

		क्रम ( ; *findit != ' '; findit++); /* walk till we find a space */
		/* RAID is superfluous in the context of a RAID device */
		अगर (स_भेद(findit-4, "RAID", 4) == 0)
			*(findit -= 4) = ' ';
		अगर (((findit - str->pid) + म_माप(container_types[tindex]))
		 < (माप(str->pid) + माप(str->prl)))
			inqम_नकल (container_types[tindex], findit + 1);
	पूर्ण
	inqम_नकल ("V1.0", str->prl);
पूर्ण

अटल व्योम build_vpd83_type3(काष्ठा tvpd_page83 *vpdpage83data,
		काष्ठा aac_dev *dev, काष्ठा scsi_cmnd *scsicmd)
अणु
	पूर्णांक container;

	vpdpage83data->type3.codeset = 1;
	vpdpage83data->type3.identअगरiertype = 3;
	vpdpage83data->type3.identअगरierlength = माप(vpdpage83data->type3)
			- 4;

	क्रम (container = 0; container < dev->maximum_num_containers;
			container++) अणु

		अगर (scmd_id(scsicmd) == container) अणु
			स_नकल(vpdpage83data->type3.Identअगरier,
					dev->fsa_dev[container].identअगरier,
					16);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_container_serial_callback(व्योम *context, काष्ठा fib * fibptr)
अणु
	काष्ठा aac_get_serial_resp * get_serial_reply;
	काष्ठा scsi_cmnd * scsicmd;

	BUG_ON(fibptr == शून्य);

	scsicmd = (काष्ठा scsi_cmnd *) context;
	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	get_serial_reply = (काष्ठा aac_get_serial_resp *) fib_data(fibptr);
	/* Failure is irrelevant, using शेष value instead */
	अगर (le32_to_cpu(get_serial_reply->status) == CT_OK) अणु
		/*Check to see अगर it's क्रम VPD 0x83 or 0x80 */
		अगर (scsicmd->cmnd[2] == 0x83) अणु
			/* vpd page 0x83 - Device Identअगरication Page */
			काष्ठा aac_dev *dev;
			पूर्णांक i;
			काष्ठा tvpd_page83 vpdpage83data;

			dev = (काष्ठा aac_dev *)scsicmd->device->host->hostdata;

			स_रखो(((u8 *)&vpdpage83data), 0,
			       माप(vpdpage83data));

			/* सूचीECT_ACCESS_DEVIC */
			vpdpage83data.DeviceType = 0;
			/* DEVICE_CONNECTED */
			vpdpage83data.DeviceTypeQualअगरier = 0;
			/* VPD_DEVICE_IDENTIFIERS */
			vpdpage83data.PageCode = 0x83;
			vpdpage83data.reserved = 0;
			vpdpage83data.PageLength =
				माप(vpdpage83data.type1) +
				माप(vpdpage83data.type2);

			/* VPD 83 Type 3 is not supported क्रम ARC */
			अगर (dev->sa_firmware)
				vpdpage83data.PageLength +=
				माप(vpdpage83data.type3);

			/* T10 Venकरोr Identअगरier Field Format */
			/* VpdcodesetAscii */
			vpdpage83data.type1.codeset = 2;
			/* VpdIdentअगरierTypeVenकरोrId */
			vpdpage83data.type1.identअगरiertype = 1;
			vpdpage83data.type1.identअगरierlength =
				माप(vpdpage83data.type1) - 4;

			/* "ADAPTEC " क्रम adaptec */
			स_नकल(vpdpage83data.type1.venid,
				"ADAPTEC ",
				माप(vpdpage83data.type1.venid));
			स_नकल(vpdpage83data.type1.productid,
				"ARRAY           ",
				माप(
				vpdpage83data.type1.productid));

			/* Convert to ascii based serial number.
			 * The LSB is the the end.
			 */
			क्रम (i = 0; i < 8; i++) अणु
				u8 temp =
					(u8)((get_serial_reply->uid >> ((7 - i) * 4)) & 0xF);
				अगर (temp  > 0x9) अणु
					vpdpage83data.type1.serialnumber[i] =
							'A' + (temp - 0xA);
				पूर्ण अन्यथा अणु
					vpdpage83data.type1.serialnumber[i] =
							'0' + temp;
				पूर्ण
			पूर्ण

			/* VpdCodeSetBinary */
			vpdpage83data.type2.codeset = 1;
			/* VpdidentअगरiertypeEUI64 */
			vpdpage83data.type2.identअगरiertype = 2;
			vpdpage83data.type2.identअगरierlength =
				माप(vpdpage83data.type2) - 4;

			vpdpage83data.type2.eu64id.venid[0] = 0xD0;
			vpdpage83data.type2.eu64id.venid[1] = 0;
			vpdpage83data.type2.eu64id.venid[2] = 0;

			vpdpage83data.type2.eu64id.Serial =
							get_serial_reply->uid;
			vpdpage83data.type2.eu64id.reserved = 0;

			/*
			 * VpdIdentअगरierTypeFCPHName
			 * VPD 0x83 Type 3 not supported क्रम ARC
			 */
			अगर (dev->sa_firmware) अणु
				build_vpd83_type3(&vpdpage83data,
						dev, scsicmd);
			पूर्ण

			/* Move the inquiry data to the response buffer. */
			scsi_sg_copy_from_buffer(scsicmd, &vpdpage83data,
						 माप(vpdpage83data));
		पूर्ण अन्यथा अणु
			/* It must be क्रम VPD 0x80 */
			अक्षर sp[13];
			/* EVPD bit set */
			sp[0] = INQD_PDT_DA;
			sp[1] = scsicmd->cmnd[2];
			sp[2] = 0;
			sp[3] = snम_लिखो(sp+4, माप(sp)-4, "%08X",
				le32_to_cpu(get_serial_reply->uid));
			scsi_sg_copy_from_buffer(scsicmd, sp,
						 माप(sp));
		पूर्ण
	पूर्ण

	scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;

	aac_fib_complete(fibptr);
	scsicmd->scsi_करोne(scsicmd);
पूर्ण

/*
 *	aac_get_container_serial - get container serial, none blocking.
 */
अटल पूर्णांक aac_get_container_serial(काष्ठा scsi_cmnd * scsicmd)
अणु
	पूर्णांक status;
	काष्ठा aac_get_serial *dinfo;
	काष्ठा fib * cmd_fibcontext;
	काष्ठा aac_dev * dev;

	dev = (काष्ठा aac_dev *)scsicmd->device->host->hostdata;

	cmd_fibcontext = aac_fib_alloc_tag(dev, scsicmd);

	aac_fib_init(cmd_fibcontext);
	dinfo = (काष्ठा aac_get_serial *) fib_data(cmd_fibcontext);

	dinfo->command = cpu_to_le32(VM_ContainerConfig);
	dinfo->type = cpu_to_le32(CT_CID_TO_32BITS_UID);
	dinfo->cid = cpu_to_le32(scmd_id(scsicmd));
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;

	status = aac_fib_send(ContainerCommand,
		  cmd_fibcontext,
		  माप(काष्ठा aac_get_serial_resp),
		  FsaNormal,
		  0, 1,
		  (fib_callback) get_container_serial_callback,
		  (व्योम *) scsicmd);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	prपूर्णांकk(KERN_WARNING "aac_get_container_serial: aac_fib_send failed with status: %d.\n", status);
	aac_fib_complete(cmd_fibcontext);
	वापस -1;
पूर्ण

/* Function: setinqserial
 *
 * Arguments: [1] poपूर्णांकer to व्योम [1] पूर्णांक
 *
 * Purpose: Sets SCSI Unit Serial number.
 *          This is a fake. We should पढ़ो a proper
 *          serial number from the container. <SuSE>But
 *          without करोcs it's quite hard to करो it :-)
 *          So this will have to करो in the meanसमय.</SuSE>
 */

अटल पूर्णांक setinqserial(काष्ठा aac_dev *dev, व्योम *data, पूर्णांक cid)
अणु
	/*
	 *	This अवरोधs array migration.
	 */
	वापस snम_लिखो((अक्षर *)(data), माप(काष्ठा scsi_inq) - 4, "%08X%02X",
			le32_to_cpu(dev->adapter_info.serial[0]), cid);
पूर्ण

अटल अंतरभूत व्योम set_sense(काष्ठा sense_data *sense_data, u8 sense_key,
	u8 sense_code, u8 a_sense_code, u8 bit_poपूर्णांकer, u16 field_poपूर्णांकer)
अणु
	u8 *sense_buf = (u8 *)sense_data;
	/* Sense data valid, err code 70h */
	sense_buf[0] = 0x70; /* No info field */
	sense_buf[1] = 0;	/* Segment number, always zero */

	sense_buf[2] = sense_key;	/* Sense key */

	sense_buf[12] = sense_code;	/* Additional sense code */
	sense_buf[13] = a_sense_code;	/* Additional sense code qualअगरier */

	अगर (sense_key == ILLEGAL_REQUEST) अणु
		sense_buf[7] = 10;	/* Additional sense length */

		sense_buf[15] = bit_poपूर्णांकer;
		/* Illegal parameter is in the parameter block */
		अगर (sense_code == SENCODE_INVALID_CDB_FIELD)
			sense_buf[15] |= 0xc0;/* Std sense key specअगरic field */
		/* Illegal parameter is in the CDB block */
		sense_buf[16] = field_poपूर्णांकer >> 8;	/* MSB */
		sense_buf[17] = field_poपूर्णांकer;		/* LSB */
	पूर्ण अन्यथा
		sense_buf[7] = 6;	/* Additional sense length */
पूर्ण

अटल पूर्णांक aac_bounds_32(काष्ठा aac_dev * dev, काष्ठा scsi_cmnd * cmd, u64 lba)
अणु
	अगर (lba & 0xffffffff00000000LL) अणु
		पूर्णांक cid = scmd_id(cmd);
		dprपूर्णांकk((KERN_DEBUG "aacraid: Illegal lba\n"));
		cmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data,
		  HARDWARE_ERROR, SENCODE_INTERNAL_TARGET_FAILURE,
		  ASENCODE_INTERNAL_TARGET_FAILURE, 0, 0);
		स_नकल(cmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
		cmd->scsi_करोne(cmd);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aac_bounds_64(काष्ठा aac_dev * dev, काष्ठा scsi_cmnd * cmd, u64 lba)
अणु
	वापस 0;
पूर्ण

अटल व्योम io_callback(व्योम *context, काष्ठा fib * fibptr);

अटल पूर्णांक aac_पढ़ो_raw_io(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count)
अणु
	काष्ठा aac_dev *dev = fib->dev;
	u16 fibsize, command;
	दीर्घ ret;

	aac_fib_init(fib);
	अगर ((dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE2 ||
		dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3) &&
		!dev->sync_mode) अणु
		काष्ठा aac_raw_io2 *पढ़ोcmd2;
		पढ़ोcmd2 = (काष्ठा aac_raw_io2 *) fib_data(fib);
		स_रखो(पढ़ोcmd2, 0, माप(काष्ठा aac_raw_io2));
		पढ़ोcmd2->blockLow = cpu_to_le32((u32)(lba&0xffffffff));
		पढ़ोcmd2->blockHigh = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		पढ़ोcmd2->byteCount = cpu_to_le32(count *
			dev->fsa_dev[scmd_id(cmd)].block_size);
		पढ़ोcmd2->cid = cpu_to_le16(scmd_id(cmd));
		पढ़ोcmd2->flags = cpu_to_le16(RIO2_IO_TYPE_READ);
		ret = aac_build_sgraw2(cmd, पढ़ोcmd2,
				dev->scsi_host_ptr->sg_tablesize);
		अगर (ret < 0)
			वापस ret;
		command = ContainerRawIo2;
		fibsize = माप(काष्ठा aac_raw_io2) +
			((le32_to_cpu(पढ़ोcmd2->sgeCnt)-1) * माप(काष्ठा sge_ieee1212));
	पूर्ण अन्यथा अणु
		काष्ठा aac_raw_io *पढ़ोcmd;
		पढ़ोcmd = (काष्ठा aac_raw_io *) fib_data(fib);
		पढ़ोcmd->block[0] = cpu_to_le32((u32)(lba&0xffffffff));
		पढ़ोcmd->block[1] = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		पढ़ोcmd->count = cpu_to_le32(count *
			dev->fsa_dev[scmd_id(cmd)].block_size);
		पढ़ोcmd->cid = cpu_to_le16(scmd_id(cmd));
		पढ़ोcmd->flags = cpu_to_le16(RIO_TYPE_READ);
		पढ़ोcmd->bpTotal = 0;
		पढ़ोcmd->bpComplete = 0;
		ret = aac_build_sgraw(cmd, &पढ़ोcmd->sg);
		अगर (ret < 0)
			वापस ret;
		command = ContainerRawIo;
		fibsize = माप(काष्ठा aac_raw_io) +
			((le32_to_cpu(पढ़ोcmd->sg.count)-1) * माप(काष्ठा sgentryraw));
	पूर्ण

	BUG_ON(fibsize > (fib->dev->max_fib_size - माप(काष्ठा aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(command,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_पढ़ो_block64(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count)
अणु
	u16 fibsize;
	काष्ठा aac_पढ़ो64 *पढ़ोcmd;
	दीर्घ ret;

	aac_fib_init(fib);
	पढ़ोcmd = (काष्ठा aac_पढ़ो64 *) fib_data(fib);
	पढ़ोcmd->command = cpu_to_le32(VM_CtHostRead64);
	पढ़ोcmd->cid = cpu_to_le16(scmd_id(cmd));
	पढ़ोcmd->sector_count = cpu_to_le16(count);
	पढ़ोcmd->block = cpu_to_le32((u32)(lba&0xffffffff));
	पढ़ोcmd->pad   = 0;
	पढ़ोcmd->flags = 0;

	ret = aac_build_sg64(cmd, &पढ़ोcmd->sg);
	अगर (ret < 0)
		वापस ret;
	fibsize = माप(काष्ठा aac_पढ़ो64) +
		((le32_to_cpu(पढ़ोcmd->sg.count) - 1) *
		 माप (काष्ठा sgentry64));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				माप(काष्ठा aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(ContainerCommand64,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_पढ़ो_block(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count)
अणु
	u16 fibsize;
	काष्ठा aac_पढ़ो *पढ़ोcmd;
	काष्ठा aac_dev *dev = fib->dev;
	दीर्घ ret;

	aac_fib_init(fib);
	पढ़ोcmd = (काष्ठा aac_पढ़ो *) fib_data(fib);
	पढ़ोcmd->command = cpu_to_le32(VM_CtBlockRead);
	पढ़ोcmd->cid = cpu_to_le32(scmd_id(cmd));
	पढ़ोcmd->block = cpu_to_le32((u32)(lba&0xffffffff));
	पढ़ोcmd->count = cpu_to_le32(count *
		dev->fsa_dev[scmd_id(cmd)].block_size);

	ret = aac_build_sg(cmd, &पढ़ोcmd->sg);
	अगर (ret < 0)
		वापस ret;
	fibsize = माप(काष्ठा aac_पढ़ो) +
			((le32_to_cpu(पढ़ोcmd->sg.count) - 1) *
			 माप (काष्ठा sgentry));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				माप(काष्ठा aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(ContainerCommand,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_ग_लिखो_raw_io(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count, पूर्णांक fua)
अणु
	काष्ठा aac_dev *dev = fib->dev;
	u16 fibsize, command;
	दीर्घ ret;

	aac_fib_init(fib);
	अगर ((dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE2 ||
		dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3) &&
		!dev->sync_mode) अणु
		काष्ठा aac_raw_io2 *ग_लिखोcmd2;
		ग_लिखोcmd2 = (काष्ठा aac_raw_io2 *) fib_data(fib);
		स_रखो(ग_लिखोcmd2, 0, माप(काष्ठा aac_raw_io2));
		ग_लिखोcmd2->blockLow = cpu_to_le32((u32)(lba&0xffffffff));
		ग_लिखोcmd2->blockHigh = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		ग_लिखोcmd2->byteCount = cpu_to_le32(count *
			dev->fsa_dev[scmd_id(cmd)].block_size);
		ग_लिखोcmd2->cid = cpu_to_le16(scmd_id(cmd));
		ग_लिखोcmd2->flags = (fua && ((aac_cache & 5) != 1) &&
						   (((aac_cache & 5) != 5) || !fib->dev->cache_रक्षित)) ?
			cpu_to_le16(RIO2_IO_TYPE_WRITE|RIO2_IO_SUREWRITE) :
			cpu_to_le16(RIO2_IO_TYPE_WRITE);
		ret = aac_build_sgraw2(cmd, ग_लिखोcmd2,
				dev->scsi_host_ptr->sg_tablesize);
		अगर (ret < 0)
			वापस ret;
		command = ContainerRawIo2;
		fibsize = माप(काष्ठा aac_raw_io2) +
			((le32_to_cpu(ग_लिखोcmd2->sgeCnt)-1) * माप(काष्ठा sge_ieee1212));
	पूर्ण अन्यथा अणु
		काष्ठा aac_raw_io *ग_लिखोcmd;
		ग_लिखोcmd = (काष्ठा aac_raw_io *) fib_data(fib);
		ग_लिखोcmd->block[0] = cpu_to_le32((u32)(lba&0xffffffff));
		ग_लिखोcmd->block[1] = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		ग_लिखोcmd->count = cpu_to_le32(count *
			dev->fsa_dev[scmd_id(cmd)].block_size);
		ग_लिखोcmd->cid = cpu_to_le16(scmd_id(cmd));
		ग_लिखोcmd->flags = (fua && ((aac_cache & 5) != 1) &&
						   (((aac_cache & 5) != 5) || !fib->dev->cache_रक्षित)) ?
			cpu_to_le16(RIO_TYPE_WRITE|RIO_SUREWRITE) :
			cpu_to_le16(RIO_TYPE_WRITE);
		ग_लिखोcmd->bpTotal = 0;
		ग_लिखोcmd->bpComplete = 0;
		ret = aac_build_sgraw(cmd, &ग_लिखोcmd->sg);
		अगर (ret < 0)
			वापस ret;
		command = ContainerRawIo;
		fibsize = माप(काष्ठा aac_raw_io) +
			((le32_to_cpu(ग_लिखोcmd->sg.count)-1) * माप (काष्ठा sgentryraw));
	पूर्ण

	BUG_ON(fibsize > (fib->dev->max_fib_size - माप(काष्ठा aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(command,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_ग_लिखो_block64(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count, पूर्णांक fua)
अणु
	u16 fibsize;
	काष्ठा aac_ग_लिखो64 *ग_लिखोcmd;
	दीर्घ ret;

	aac_fib_init(fib);
	ग_लिखोcmd = (काष्ठा aac_ग_लिखो64 *) fib_data(fib);
	ग_लिखोcmd->command = cpu_to_le32(VM_CtHostWrite64);
	ग_लिखोcmd->cid = cpu_to_le16(scmd_id(cmd));
	ग_लिखोcmd->sector_count = cpu_to_le16(count);
	ग_लिखोcmd->block = cpu_to_le32((u32)(lba&0xffffffff));
	ग_लिखोcmd->pad	= 0;
	ग_लिखोcmd->flags	= 0;

	ret = aac_build_sg64(cmd, &ग_लिखोcmd->sg);
	अगर (ret < 0)
		वापस ret;
	fibsize = माप(काष्ठा aac_ग_लिखो64) +
		((le32_to_cpu(ग_लिखोcmd->sg.count) - 1) *
		 माप (काष्ठा sgentry64));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				माप(काष्ठा aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(ContainerCommand64,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_ग_लिखो_block(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count, पूर्णांक fua)
अणु
	u16 fibsize;
	काष्ठा aac_ग_लिखो *ग_लिखोcmd;
	काष्ठा aac_dev *dev = fib->dev;
	दीर्घ ret;

	aac_fib_init(fib);
	ग_लिखोcmd = (काष्ठा aac_ग_लिखो *) fib_data(fib);
	ग_लिखोcmd->command = cpu_to_le32(VM_CtBlockWrite);
	ग_लिखोcmd->cid = cpu_to_le32(scmd_id(cmd));
	ग_लिखोcmd->block = cpu_to_le32((u32)(lba&0xffffffff));
	ग_लिखोcmd->count = cpu_to_le32(count *
		dev->fsa_dev[scmd_id(cmd)].block_size);
	ग_लिखोcmd->sg.count = cpu_to_le32(1);
	/* ->stable is not used - it did mean which type of ग_लिखो */

	ret = aac_build_sg(cmd, &ग_लिखोcmd->sg);
	अगर (ret < 0)
		वापस ret;
	fibsize = माप(काष्ठा aac_ग_लिखो) +
		((le32_to_cpu(ग_लिखोcmd->sg.count) - 1) *
		 माप (काष्ठा sgentry));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				माप(काष्ठा aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(ContainerCommand,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (व्योम *) cmd);
पूर्ण

अटल काष्ठा aac_srb * aac_scsi_common(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd)
अणु
	काष्ठा aac_srb * srbcmd;
	u32 flag;
	u32 समयout;
	काष्ठा aac_dev *dev = fib->dev;

	aac_fib_init(fib);
	चयन(cmd->sc_data_direction)अणु
	हाल DMA_TO_DEVICE:
		flag = SRB_DataOut;
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		flag = SRB_DataIn | SRB_DataOut;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		flag = SRB_DataIn;
		अवरोध;
	हाल DMA_NONE:
	शेष:	/* shuts up some versions of gcc */
		flag = SRB_NoDataXfer;
		अवरोध;
	पूर्ण

	srbcmd = (काष्ठा aac_srb*) fib_data(fib);
	srbcmd->function = cpu_to_le32(SRBF_ExecuteScsi);
	srbcmd->channel  = cpu_to_le32(aac_logical_to_phys(scmd_channel(cmd)));
	srbcmd->id       = cpu_to_le32(scmd_id(cmd));
	srbcmd->lun      = cpu_to_le32(cmd->device->lun);
	srbcmd->flags    = cpu_to_le32(flag);
	समयout = cmd->request->समयout/HZ;
	अगर (समयout == 0)
		समयout = (dev->sa_firmware ? AAC_SA_TIMEOUT : AAC_ARC_TIMEOUT);
	srbcmd->समयout  = cpu_to_le32(समयout);  // समयout in seconds
	srbcmd->retry_limit = 0; /* Obsolete parameter */
	srbcmd->cdb_size = cpu_to_le32(cmd->cmd_len);
	वापस srbcmd;
पूर्ण

अटल काष्ठा aac_hba_cmd_req *aac_स्थिरruct_hbacmd(काष्ठा fib *fib,
							काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा aac_hba_cmd_req *hbacmd;
	काष्ठा aac_dev *dev;
	पूर्णांक bus, target;
	u64 address;

	dev = (काष्ठा aac_dev *)cmd->device->host->hostdata;

	hbacmd = (काष्ठा aac_hba_cmd_req *)fib->hw_fib_va;
	स_रखो(hbacmd, 0, 96);	/* माप(*hbacmd) is not necessary */
	/* iu_type is a parameter of aac_hba_send */
	चयन (cmd->sc_data_direction) अणु
	हाल DMA_TO_DEVICE:
		hbacmd->byte1 = 2;
		अवरोध;
	हाल DMA_FROM_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		hbacmd->byte1 = 1;
		अवरोध;
	हाल DMA_NONE:
	शेष:
		अवरोध;
	पूर्ण
	hbacmd->lun[1] = cpu_to_le32(cmd->device->lun);

	bus = aac_logical_to_phys(scmd_channel(cmd));
	target = scmd_id(cmd);
	hbacmd->it_nexus = dev->hba_map[bus][target].rmw_nexus;

	/* we fill in reply_qid later in aac_src_deliver_message */
	/* we fill in iu_type, request_id later in aac_hba_send */
	/* we fill in emb_data_desc_count later in aac_build_sghba */

	स_नकल(hbacmd->cdb, cmd->cmnd, cmd->cmd_len);
	hbacmd->data_length = cpu_to_le32(scsi_bufflen(cmd));

	address = (u64)fib->hw_error_pa;
	hbacmd->error_ptr_hi = cpu_to_le32((u32)(address >> 32));
	hbacmd->error_ptr_lo = cpu_to_le32((u32)(address & 0xffffffff));
	hbacmd->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);

	वापस hbacmd;
पूर्ण

अटल व्योम aac_srb_callback(व्योम *context, काष्ठा fib * fibptr);

अटल पूर्णांक aac_scsi_64(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd)
अणु
	u16 fibsize;
	काष्ठा aac_srb * srbcmd = aac_scsi_common(fib, cmd);
	दीर्घ ret;

	ret = aac_build_sg64(cmd, (काष्ठा sgmap64 *) &srbcmd->sg);
	अगर (ret < 0)
		वापस ret;
	srbcmd->count = cpu_to_le32(scsi_bufflen(cmd));

	स_रखो(srbcmd->cdb, 0, माप(srbcmd->cdb));
	स_नकल(srbcmd->cdb, cmd->cmnd, cmd->cmd_len);
	/*
	 *	Build Scatter/Gather list
	 */
	fibsize = माप (काष्ठा aac_srb) - माप (काष्ठा sgentry) +
		((le32_to_cpu(srbcmd->sg.count) & 0xff) *
		 माप (काष्ठा sgentry64));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				माप(काष्ठा aac_fibhdr)));

	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(ScsiPortCommand64, fib,
				fibsize, FsaNormal, 0, 1,
				  (fib_callback) aac_srb_callback,
				  (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_scsi_32(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd)
अणु
	u16 fibsize;
	काष्ठा aac_srb * srbcmd = aac_scsi_common(fib, cmd);
	दीर्घ ret;

	ret = aac_build_sg(cmd, (काष्ठा sgmap *)&srbcmd->sg);
	अगर (ret < 0)
		वापस ret;
	srbcmd->count = cpu_to_le32(scsi_bufflen(cmd));

	स_रखो(srbcmd->cdb, 0, माप(srbcmd->cdb));
	स_नकल(srbcmd->cdb, cmd->cmnd, cmd->cmd_len);
	/*
	 *	Build Scatter/Gather list
	 */
	fibsize = माप (काष्ठा aac_srb) +
		(((le32_to_cpu(srbcmd->sg.count) & 0xff) - 1) *
		 माप (काष्ठा sgentry));
	BUG_ON (fibsize > (fib->dev->max_fib_size -
				माप(काष्ठा aac_fibhdr)));

	/*
	 *	Now send the Fib to the adapter
	 */
	वापस aac_fib_send(ScsiPortCommand, fib, fibsize, FsaNormal, 0, 1,
				  (fib_callback) aac_srb_callback, (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_scsi_32_64(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd)
अणु
	अगर ((माप(dma_addr_t) > 4) && fib->dev->needs_dac &&
	    (fib->dev->adapter_info.options & AAC_OPT_SGMAP_HOST64))
		वापस FAILED;
	वापस aac_scsi_32(fib, cmd);
पूर्ण

अटल पूर्णांक aac_adapter_hba(काष्ठा fib *fib, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा aac_hba_cmd_req *hbacmd = aac_स्थिरruct_hbacmd(fib, cmd);
	काष्ठा aac_dev *dev;
	दीर्घ ret;

	dev = (काष्ठा aac_dev *)cmd->device->host->hostdata;

	ret = aac_build_sghba(cmd, hbacmd,
		dev->scsi_host_ptr->sg_tablesize, (u64)fib->hw_sgl_pa);
	अगर (ret < 0)
		वापस ret;

	/*
	 *	Now send the HBA command to the adapter
	 */
	fib->hbacmd_size = 64 + le32_to_cpu(hbacmd->emb_data_desc_count) *
		माप(काष्ठा aac_hba_sgl);

	वापस aac_hba_send(HBA_IU_TYPE_SCSI_CMD_REQ, fib,
				  (fib_callback) aac_hba_callback,
				  (व्योम *) cmd);
पूर्ण

अटल पूर्णांक aac_send_safw_bmic_cmd(काष्ठा aac_dev *dev,
	काष्ठा aac_srb_unit *srbu, व्योम *xfer_buf, पूर्णांक xfer_len)
अणु
	काष्ठा fib	*fibptr;
	dma_addr_t	addr;
	पूर्णांक		rcode;
	पूर्णांक		fibsize;
	काष्ठा aac_srb	*srb;
	काष्ठा aac_srb_reply *srb_reply;
	काष्ठा sgmap64	*sg64;
	u32 vbus;
	u32 vid;

	अगर (!dev->sa_firmware)
		वापस 0;

	/* allocate FIB */
	fibptr = aac_fib_alloc(dev);
	अगर (!fibptr)
		वापस -ENOMEM;

	aac_fib_init(fibptr);
	fibptr->hw_fib_va->header.XferState &=
		~cpu_to_le32(FastResponseCapable);

	fibsize  = माप(काष्ठा aac_srb) - माप(काष्ठा sgentry) +
						माप(काष्ठा sgentry64);

	/* allocate DMA buffer क्रम response */
	addr = dma_map_single(&dev->pdev->dev, xfer_buf, xfer_len,
							DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&dev->pdev->dev, addr)) अणु
		rcode = -ENOMEM;
		जाओ fib_error;
	पूर्ण

	srb = fib_data(fibptr);
	स_नकल(srb, &srbu->srb, माप(काष्ठा aac_srb));

	vbus = (u32)le16_to_cpu(
			dev->supplement_adapter_info.virt_device_bus);
	vid  = (u32)le16_to_cpu(
			dev->supplement_adapter_info.virt_device_target);

	/* set the common request fields */
	srb->channel		= cpu_to_le32(vbus);
	srb->id			= cpu_to_le32(vid);
	srb->lun		= 0;
	srb->function		= cpu_to_le32(SRBF_ExecuteScsi);
	srb->समयout		= 0;
	srb->retry_limit	= 0;
	srb->cdb_size		= cpu_to_le32(16);
	srb->count		= cpu_to_le32(xfer_len);

	sg64 = (काष्ठा sgmap64 *)&srb->sg;
	sg64->count		= cpu_to_le32(1);
	sg64->sg[0].addr[1]	= cpu_to_le32(upper_32_bits(addr));
	sg64->sg[0].addr[0]	= cpu_to_le32(lower_32_bits(addr));
	sg64->sg[0].count	= cpu_to_le32(xfer_len);

	/*
	 * Copy the updated data क्रम other dumping or other usage अगर needed
	 */
	स_नकल(&srbu->srb, srb, माप(काष्ठा aac_srb));

	/* issue request to the controller */
	rcode = aac_fib_send(ScsiPortCommand64, fibptr, fibsize, FsaNormal,
					1, 1, शून्य, शून्य);

	अगर (rcode == -ERESTARTSYS)
		rcode = -ERESTART;

	अगर (unlikely(rcode < 0))
		जाओ bmic_error;

	srb_reply = (काष्ठा aac_srb_reply *)fib_data(fibptr);
	स_नकल(&srbu->srb_reply, srb_reply, माप(काष्ठा aac_srb_reply));

bmic_error:
	dma_unmap_single(&dev->pdev->dev, addr, xfer_len, DMA_BIसूचीECTIONAL);
fib_error:
	aac_fib_complete(fibptr);
	aac_fib_मुक्त(fibptr);
	वापस rcode;
पूर्ण

अटल व्योम aac_set_safw_target_qd(काष्ठा aac_dev *dev, पूर्णांक bus, पूर्णांक target)
अणु

	काष्ठा aac_ciss_identअगरy_pd *identअगरy_resp;

	अगर (dev->hba_map[bus][target].devtype != AAC_DEVTYPE_NATIVE_RAW)
		वापस;

	identअगरy_resp = dev->hba_map[bus][target].safw_identअगरy_resp;
	अगर (identअगरy_resp == शून्य) अणु
		dev->hba_map[bus][target].qd_limit = 32;
		वापस;
	पूर्ण

	अगर (identअगरy_resp->current_queue_depth_limit <= 0 ||
		identअगरy_resp->current_queue_depth_limit > 255)
		dev->hba_map[bus][target].qd_limit = 32;
	अन्यथा
		dev->hba_map[bus][target].qd_limit =
			identअगरy_resp->current_queue_depth_limit;
पूर्ण

अटल पूर्णांक aac_issue_safw_bmic_identअगरy(काष्ठा aac_dev *dev,
	काष्ठा aac_ciss_identअगरy_pd **identअगरy_resp, u32 bus, u32 target)
अणु
	पूर्णांक rcode = -ENOMEM;
	पूर्णांक datasize;
	काष्ठा aac_srb_unit srbu;
	काष्ठा aac_srb *srbcmd;
	काष्ठा aac_ciss_identअगरy_pd *identअगरy_reply;

	datasize = माप(काष्ठा aac_ciss_identअगरy_pd);
	identअगरy_reply = kदो_स्मृति(datasize, GFP_KERNEL);
	अगर (!identअगरy_reply)
		जाओ out;

	स_रखो(&srbu, 0, माप(काष्ठा aac_srb_unit));

	srbcmd = &srbu.srb;
	srbcmd->flags	= cpu_to_le32(SRB_DataIn);
	srbcmd->cdb[0]	= 0x26;
	srbcmd->cdb[2]	= (u8)((AAC_MAX_LUN + target) & 0x00FF);
	srbcmd->cdb[6]	= CISS_IDENTIFY_PHYSICAL_DEVICE;

	rcode = aac_send_safw_bmic_cmd(dev, &srbu, identअगरy_reply, datasize);
	अगर (unlikely(rcode < 0))
		जाओ mem_मुक्त_all;

	*identअगरy_resp = identअगरy_reply;

out:
	वापस rcode;
mem_मुक्त_all:
	kमुक्त(identअगरy_reply);
	जाओ out;
पूर्ण

अटल अंतरभूत व्योम aac_मुक्त_safw_ciss_luns(काष्ठा aac_dev *dev)
अणु
	kमुक्त(dev->safw_phys_luns);
	dev->safw_phys_luns = शून्य;
पूर्ण

/**
 *	aac_get_safw_ciss_luns() - Process topology change
 *	@dev:		aac_dev काष्ठाure
 *
 *	Execute a CISS REPORT PHYS LUNS and process the results पूर्णांकo
 *	the current hba_map.
 */
अटल पूर्णांक aac_get_safw_ciss_luns(काष्ठा aac_dev *dev)
अणु
	पूर्णांक rcode = -ENOMEM;
	पूर्णांक datasize;
	काष्ठा aac_srb *srbcmd;
	काष्ठा aac_srb_unit srbu;
	काष्ठा aac_ciss_phys_luns_resp *phys_luns;

	datasize = माप(काष्ठा aac_ciss_phys_luns_resp) +
		(AAC_MAX_TARGETS - 1) * माप(काष्ठा _ciss_lun);
	phys_luns = kदो_स्मृति(datasize, GFP_KERNEL);
	अगर (phys_luns == शून्य)
		जाओ out;

	स_रखो(&srbu, 0, माप(काष्ठा aac_srb_unit));

	srbcmd = &srbu.srb;
	srbcmd->flags	= cpu_to_le32(SRB_DataIn);
	srbcmd->cdb[0]	= CISS_REPORT_PHYSICAL_LUNS;
	srbcmd->cdb[1]	= 2; /* extended reporting */
	srbcmd->cdb[8]	= (u8)(datasize >> 8);
	srbcmd->cdb[9]	= (u8)(datasize);

	rcode = aac_send_safw_bmic_cmd(dev, &srbu, phys_luns, datasize);
	अगर (unlikely(rcode < 0))
		जाओ mem_मुक्त_all;

	अगर (phys_luns->resp_flag != 2) अणु
		rcode = -ENOMSG;
		जाओ mem_मुक्त_all;
	पूर्ण

	dev->safw_phys_luns = phys_luns;

out:
	वापस rcode;
mem_मुक्त_all:
	kमुक्त(phys_luns);
	जाओ out;
पूर्ण

अटल अंतरभूत u32 aac_get_safw_phys_lun_count(काष्ठा aac_dev *dev)
अणु
	वापस get_unaligned_be32(&dev->safw_phys_luns->list_length[0])/24;
पूर्ण

अटल अंतरभूत u32 aac_get_safw_phys_bus(काष्ठा aac_dev *dev, पूर्णांक lun)
अणु
	वापस dev->safw_phys_luns->lun[lun].level2[1] & 0x3f;
पूर्ण

अटल अंतरभूत u32 aac_get_safw_phys_target(काष्ठा aac_dev *dev, पूर्णांक lun)
अणु
	वापस dev->safw_phys_luns->lun[lun].level2[0];
पूर्ण

अटल अंतरभूत u32 aac_get_safw_phys_expose_flag(काष्ठा aac_dev *dev, पूर्णांक lun)
अणु
	वापस dev->safw_phys_luns->lun[lun].bus >> 6;
पूर्ण

अटल अंतरभूत u32 aac_get_safw_phys_attribs(काष्ठा aac_dev *dev, पूर्णांक lun)
अणु
	वापस dev->safw_phys_luns->lun[lun].node_ident[9];
पूर्ण

अटल अंतरभूत u32 aac_get_safw_phys_nexus(काष्ठा aac_dev *dev, पूर्णांक lun)
अणु
	वापस *((u32 *)&dev->safw_phys_luns->lun[lun].node_ident[12]);
पूर्ण

अटल अंतरभूत व्योम aac_मुक्त_safw_identअगरy_resp(काष्ठा aac_dev *dev,
						पूर्णांक bus, पूर्णांक target)
अणु
	kमुक्त(dev->hba_map[bus][target].safw_identअगरy_resp);
	dev->hba_map[bus][target].safw_identअगरy_resp = शून्य;
पूर्ण

अटल अंतरभूत व्योम aac_मुक्त_safw_all_identअगरy_resp(काष्ठा aac_dev *dev,
	पूर्णांक lun_count)
अणु
	पूर्णांक luns;
	पूर्णांक i;
	u32 bus;
	u32 target;

	luns = aac_get_safw_phys_lun_count(dev);

	अगर (luns < lun_count)
		lun_count = luns;
	अन्यथा अगर (lun_count < 0)
		lun_count = luns;

	क्रम (i = 0; i < lun_count; i++) अणु
		bus = aac_get_safw_phys_bus(dev, i);
		target = aac_get_safw_phys_target(dev, i);

		aac_मुक्त_safw_identअगरy_resp(dev, bus, target);
	पूर्ण
पूर्ण

अटल पूर्णांक aac_get_safw_attr_all_tarमाला_लो(काष्ठा aac_dev *dev)
अणु
	पूर्णांक i;
	पूर्णांक rcode = 0;
	u32 lun_count;
	u32 bus;
	u32 target;
	काष्ठा aac_ciss_identअगरy_pd *identअगरy_resp = शून्य;

	lun_count = aac_get_safw_phys_lun_count(dev);

	क्रम (i = 0; i < lun_count; ++i) अणु

		bus = aac_get_safw_phys_bus(dev, i);
		target = aac_get_safw_phys_target(dev, i);

		rcode = aac_issue_safw_bmic_identअगरy(dev,
						&identअगरy_resp, bus, target);

		अगर (unlikely(rcode < 0))
			जाओ मुक्त_identअगरy_resp;

		dev->hba_map[bus][target].safw_identअगरy_resp = identअगरy_resp;
	पूर्ण

out:
	वापस rcode;
मुक्त_identअगरy_resp:
	aac_मुक्त_safw_all_identअगरy_resp(dev, i);
	जाओ out;
पूर्ण

/**
 *	aac_set_safw_attr_all_tarमाला_लो-	update current hba map with data from FW
 *	@dev:	aac_dev काष्ठाure
 *
 *	Update our hba map with the inक्रमmation gathered from the FW
 */
अटल व्योम aac_set_safw_attr_all_tarमाला_लो(काष्ठा aac_dev *dev)
अणु
	/* ok and extended reporting */
	u32 lun_count, nexus;
	u32 i, bus, target;
	u8 expose_flag, attribs;

	lun_count = aac_get_safw_phys_lun_count(dev);

	dev->scan_counter++;

	क्रम (i = 0; i < lun_count; ++i) अणु

		bus = aac_get_safw_phys_bus(dev, i);
		target = aac_get_safw_phys_target(dev, i);
		expose_flag = aac_get_safw_phys_expose_flag(dev, i);
		attribs = aac_get_safw_phys_attribs(dev, i);
		nexus = aac_get_safw_phys_nexus(dev, i);

		अगर (bus >= AAC_MAX_BUSES || target >= AAC_MAX_TARGETS)
			जारी;

		अगर (expose_flag != 0) अणु
			dev->hba_map[bus][target].devtype =
				AAC_DEVTYPE_RAID_MEMBER;
			जारी;
		पूर्ण

		अगर (nexus != 0 && (attribs & 8)) अणु
			dev->hba_map[bus][target].devtype =
				AAC_DEVTYPE_NATIVE_RAW;
			dev->hba_map[bus][target].rmw_nexus =
					nexus;
		पूर्ण अन्यथा
			dev->hba_map[bus][target].devtype =
				AAC_DEVTYPE_ARC_RAW;

		dev->hba_map[bus][target].scan_counter = dev->scan_counter;

		aac_set_safw_target_qd(dev, bus, target);
	पूर्ण
पूर्ण

अटल पूर्णांक aac_setup_safw_tarमाला_लो(काष्ठा aac_dev *dev)
अणु
	पूर्णांक rcode = 0;

	rcode = aac_get_containers(dev);
	अगर (unlikely(rcode < 0))
		जाओ out;

	rcode = aac_get_safw_ciss_luns(dev);
	अगर (unlikely(rcode < 0))
		जाओ out;

	rcode = aac_get_safw_attr_all_tarमाला_लो(dev);
	अगर (unlikely(rcode < 0))
		जाओ मुक्त_ciss_luns;

	aac_set_safw_attr_all_tarमाला_लो(dev);

	aac_मुक्त_safw_all_identअगरy_resp(dev, -1);
मुक्त_ciss_luns:
	aac_मुक्त_safw_ciss_luns(dev);
out:
	वापस rcode;
पूर्ण

पूर्णांक aac_setup_safw_adapter(काष्ठा aac_dev *dev)
अणु
	वापस aac_setup_safw_tarमाला_लो(dev);
पूर्ण

पूर्णांक aac_get_adapter_info(काष्ठा aac_dev* dev)
अणु
	काष्ठा fib* fibptr;
	पूर्णांक rcode;
	u32 पंचांगp, bus, target;
	काष्ठा aac_adapter_info *info;
	काष्ठा aac_bus_info *command;
	काष्ठा aac_bus_info_response *bus_info;

	अगर (!(fibptr = aac_fib_alloc(dev)))
		वापस -ENOMEM;

	aac_fib_init(fibptr);
	info = (काष्ठा aac_adapter_info *) fib_data(fibptr);
	स_रखो(info,0,माप(*info));

	rcode = aac_fib_send(RequestAdapterInfo,
			 fibptr,
			 माप(*info),
			 FsaNormal,
			 -1, 1, /* First `पूर्णांकerrupt' command uses special रुको */
			 शून्य,
			 शून्य);

	अगर (rcode < 0) अणु
		/* FIB should be मुक्तd only after
		 * getting the response from the F/W */
		अगर (rcode != -ERESTARTSYS) अणु
			aac_fib_complete(fibptr);
			aac_fib_मुक्त(fibptr);
		पूर्ण
		वापस rcode;
	पूर्ण
	स_नकल(&dev->adapter_info, info, माप(*info));

	dev->supplement_adapter_info.virt_device_bus = 0xffff;
	अगर (dev->adapter_info.options & AAC_OPT_SUPPLEMENT_ADAPTER_INFO) अणु
		काष्ठा aac_supplement_adapter_info * sinfo;

		aac_fib_init(fibptr);

		sinfo = (काष्ठा aac_supplement_adapter_info *) fib_data(fibptr);

		स_रखो(sinfo,0,माप(*sinfo));

		rcode = aac_fib_send(RequestSupplementAdapterInfo,
				 fibptr,
				 माप(*sinfo),
				 FsaNormal,
				 1, 1,
				 शून्य,
				 शून्य);

		अगर (rcode >= 0)
			स_नकल(&dev->supplement_adapter_info, sinfo, माप(*sinfo));
		अगर (rcode == -ERESTARTSYS) अणु
			fibptr = aac_fib_alloc(dev);
			अगर (!fibptr)
				वापस -ENOMEM;
		पूर्ण

	पूर्ण

	/* reset all previous mapped devices (i.e. क्रम init. after IOP_RESET) */
	क्रम (bus = 0; bus < AAC_MAX_BUSES; bus++) अणु
		क्रम (target = 0; target < AAC_MAX_TARGETS; target++) अणु
			dev->hba_map[bus][target].devtype = 0;
			dev->hba_map[bus][target].qd_limit = 0;
		पूर्ण
	पूर्ण

	/*
	 * GetBusInfo
	 */

	aac_fib_init(fibptr);

	bus_info = (काष्ठा aac_bus_info_response *) fib_data(fibptr);

	स_रखो(bus_info, 0, माप(*bus_info));

	command = (काष्ठा aac_bus_info *)bus_info;

	command->Command = cpu_to_le32(VM_Ioctl);
	command->ObjType = cpu_to_le32(FT_DRIVE);
	command->MethodId = cpu_to_le32(1);
	command->CtlCmd = cpu_to_le32(GetBusInfo);

	rcode = aac_fib_send(ContainerCommand,
			 fibptr,
			 माप (*bus_info),
			 FsaNormal,
			 1, 1,
			 शून्य, शून्य);

	/* reasoned शेष */
	dev->maximum_num_physicals = 16;
	अगर (rcode >= 0 && le32_to_cpu(bus_info->Status) == ST_OK) अणु
		dev->maximum_num_physicals = le32_to_cpu(bus_info->Tarमाला_लोPerBus);
		dev->maximum_num_channels = le32_to_cpu(bus_info->BusCount);
	पूर्ण

	अगर (!dev->in_reset) अणु
		अक्षर buffer[16];
		पंचांगp = le32_to_cpu(dev->adapter_info.kernelrev);
		prपूर्णांकk(KERN_INFO "%s%d: kernel %d.%d-%d[%d] %.*s\n",
			dev->name,
			dev->id,
			पंचांगp>>24,
			(पंचांगp>>16)&0xff,
			पंचांगp&0xff,
			le32_to_cpu(dev->adapter_info.kernelbuild),
			(पूर्णांक)माप(dev->supplement_adapter_info.build_date),
			dev->supplement_adapter_info.build_date);
		पंचांगp = le32_to_cpu(dev->adapter_info.monitorrev);
		prपूर्णांकk(KERN_INFO "%s%d: monitor %d.%d-%d[%d]\n",
			dev->name, dev->id,
			पंचांगp>>24,(पंचांगp>>16)&0xff,पंचांगp&0xff,
			le32_to_cpu(dev->adapter_info.monitorbuild));
		पंचांगp = le32_to_cpu(dev->adapter_info.biosrev);
		prपूर्णांकk(KERN_INFO "%s%d: bios %d.%d-%d[%d]\n",
			dev->name, dev->id,
			पंचांगp>>24,(पंचांगp>>16)&0xff,पंचांगp&0xff,
			le32_to_cpu(dev->adapter_info.biosbuild));
		buffer[0] = '\0';
		अगर (aac_get_serial_number(
		  shost_to_class(dev->scsi_host_ptr), buffer))
			prपूर्णांकk(KERN_INFO "%s%d: serial %s",
			  dev->name, dev->id, buffer);
		अगर (dev->supplement_adapter_info.vpd_info.tsid[0]) अणु
			prपूर्णांकk(KERN_INFO "%s%d: TSID %.*s\n",
			  dev->name, dev->id,
			  (पूर्णांक)माप(dev->supplement_adapter_info
							.vpd_info.tsid),
				dev->supplement_adapter_info.vpd_info.tsid);
		पूर्ण
		अगर (!aac_check_reset || ((aac_check_reset == 1) &&
		  (dev->supplement_adapter_info.supported_options2 &
		  AAC_OPTION_IGNORE_RESET))) अणु
			prपूर्णांकk(KERN_INFO "%s%d: Reset Adapter Ignored\n",
			  dev->name, dev->id);
		पूर्ण
	पूर्ण

	dev->cache_रक्षित = 0;
	dev->jbod = ((dev->supplement_adapter_info.feature_bits &
		AAC_FEATURE_JBOD) != 0);
	dev->nondasd_support = 0;
	dev->raid_scsi_mode = 0;
	अगर(dev->adapter_info.options & AAC_OPT_NONDASD)
		dev->nondasd_support = 1;

	/*
	 * If the firmware supports ROMB RAID/SCSI mode and we are currently
	 * in RAID/SCSI mode, set the flag. For now अगर in this mode we will
	 * क्रमce nondasd support on. If we decide to allow the non-dasd flag
	 * additional changes changes will have to be made to support
	 * RAID/SCSI.  the function aac_scsi_cmd in this module will have to be
	 * changed to support the new dev->raid_scsi_mode flag instead of
	 * leaching off of the dev->nondasd_support flag. Also in linit.c the
	 * function aac_detect will have to be modअगरied where it sets up the
	 * max number of channels based on the aac->nondasd_support flag only.
	 */
	अगर ((dev->adapter_info.options & AAC_OPT_SCSI_MANAGED) &&
	    (dev->adapter_info.options & AAC_OPT_RAID_SCSI_MODE)) अणु
		dev->nondasd_support = 1;
		dev->raid_scsi_mode = 1;
	पूर्ण
	अगर (dev->raid_scsi_mode != 0)
		prपूर्णांकk(KERN_INFO "%s%d: ROMB RAID/SCSI mode enabled\n",
				dev->name, dev->id);

	अगर (nondasd != -1)
		dev->nondasd_support = (nondasd!=0);
	अगर (dev->nondasd_support && !dev->in_reset)
		prपूर्णांकk(KERN_INFO "%s%d: Non-DASD support enabled.\n",dev->name, dev->id);

	अगर (dma_get_required_mask(&dev->pdev->dev) > DMA_BIT_MASK(32))
		dev->needs_dac = 1;
	dev->dac_support = 0;
	अगर ((माप(dma_addr_t) > 4) && dev->needs_dac &&
	    (dev->adapter_info.options & AAC_OPT_SGMAP_HOST64)) अणु
		अगर (!dev->in_reset)
			prपूर्णांकk(KERN_INFO "%s%d: 64bit support enabled.\n",
				dev->name, dev->id);
		dev->dac_support = 1;
	पूर्ण

	अगर(dacmode != -1) अणु
		dev->dac_support = (dacmode!=0);
	पूर्ण

	/* aव्योम problems with AAC_QUIRK_SCSI_32 controllers */
	अगर (dev->dac_support &&	(aac_get_driver_ident(dev->cardtype)->quirks
		& AAC_QUIRK_SCSI_32)) अणु
		dev->nondasd_support = 0;
		dev->jbod = 0;
		expose_physicals = 0;
	पूर्ण

	अगर (dev->dac_support) अणु
		अगर (!dma_set_mask(&dev->pdev->dev, DMA_BIT_MASK(64))) अणु
			अगर (!dev->in_reset)
				dev_info(&dev->pdev->dev, "64 Bit DAC enabled\n");
		पूर्ण अन्यथा अगर (!dma_set_mask(&dev->pdev->dev, DMA_BIT_MASK(32))) अणु
			dev_info(&dev->pdev->dev, "DMA mask set failed, 64 Bit DAC disabled\n");
			dev->dac_support = 0;
		पूर्ण अन्यथा अणु
			dev_info(&dev->pdev->dev, "No suitable DMA available\n");
			rcode = -ENOMEM;
		पूर्ण
	पूर्ण
	/*
	 * Deal with configuring क्रम the inभागidualized limits of each packet
	 * पूर्णांकerface.
	 */
	dev->a_ops.adapter_scsi = (dev->dac_support)
	  ? ((aac_get_driver_ident(dev->cardtype)->quirks & AAC_QUIRK_SCSI_32)
				? aac_scsi_32_64
				: aac_scsi_64)
				: aac_scsi_32;
	अगर (dev->raw_io_पूर्णांकerface) अणु
		dev->a_ops.adapter_bounds = (dev->raw_io_64)
					? aac_bounds_64
					: aac_bounds_32;
		dev->a_ops.adapter_पढ़ो = aac_पढ़ो_raw_io;
		dev->a_ops.adapter_ग_लिखो = aac_ग_लिखो_raw_io;
	पूर्ण अन्यथा अणु
		dev->a_ops.adapter_bounds = aac_bounds_32;
		dev->scsi_host_ptr->sg_tablesize = (dev->max_fib_size -
			माप(काष्ठा aac_fibhdr) -
			माप(काष्ठा aac_ग_लिखो) + माप(काष्ठा sgentry)) /
				माप(काष्ठा sgentry);
		अगर (dev->dac_support) अणु
			dev->a_ops.adapter_पढ़ो = aac_पढ़ो_block64;
			dev->a_ops.adapter_ग_लिखो = aac_ग_लिखो_block64;
			/*
			 * 38 scatter gather elements
			 */
			dev->scsi_host_ptr->sg_tablesize =
				(dev->max_fib_size -
				माप(काष्ठा aac_fibhdr) -
				माप(काष्ठा aac_ग_लिखो64) +
				माप(काष्ठा sgentry64)) /
					माप(काष्ठा sgentry64);
		पूर्ण अन्यथा अणु
			dev->a_ops.adapter_पढ़ो = aac_पढ़ो_block;
			dev->a_ops.adapter_ग_लिखो = aac_ग_लिखो_block;
		पूर्ण
		dev->scsi_host_ptr->max_sectors = AAC_MAX_32BIT_SGBCOUNT;
		अगर (!(dev->adapter_info.options & AAC_OPT_NEW_COMM)) अणु
			/*
			 * Worst हाल size that could cause sg overflow when
			 * we अवरोध up SG elements that are larger than 64KB.
			 * Would be nice अगर we could tell the SCSI layer what
			 * the maximum SG element size can be. Worst हाल is
			 * (sg_tablesize-1) 4KB elements with one 64KB
			 * element.
			 *	32bit -> 468 or 238KB	64bit -> 424 or 212KB
			 */
			dev->scsi_host_ptr->max_sectors =
			  (dev->scsi_host_ptr->sg_tablesize * 8) + 112;
		पूर्ण
	पूर्ण
	अगर (!dev->sync_mode && dev->sa_firmware &&
		dev->scsi_host_ptr->sg_tablesize > HBA_MAX_SG_SEPARATE)
		dev->scsi_host_ptr->sg_tablesize = dev->sg_tablesize =
			HBA_MAX_SG_SEPARATE;

	/* FIB should be मुक्तd only after getting the response from the F/W */
	अगर (rcode != -ERESTARTSYS) अणु
		aac_fib_complete(fibptr);
		aac_fib_मुक्त(fibptr);
	पूर्ण

	वापस rcode;
पूर्ण


अटल व्योम io_callback(व्योम *context, काष्ठा fib * fibptr)
अणु
	काष्ठा aac_dev *dev;
	काष्ठा aac_पढ़ो_reply *पढ़ोreply;
	काष्ठा scsi_cmnd *scsicmd;
	u32 cid;

	scsicmd = (काष्ठा scsi_cmnd *) context;

	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	dev = fibptr->dev;
	cid = scmd_id(scsicmd);

	अगर (nblank(dprपूर्णांकk(x))) अणु
		u64 lba;
		चयन (scsicmd->cmnd[0]) अणु
		हाल WRITE_6:
		हाल READ_6:
			lba = ((scsicmd->cmnd[1] & 0x1F) << 16) |
			    (scsicmd->cmnd[2] << 8) | scsicmd->cmnd[3];
			अवरोध;
		हाल WRITE_16:
		हाल READ_16:
			lba = ((u64)scsicmd->cmnd[2] << 56) |
			      ((u64)scsicmd->cmnd[3] << 48) |
			      ((u64)scsicmd->cmnd[4] << 40) |
			      ((u64)scsicmd->cmnd[5] << 32) |
			      ((u64)scsicmd->cmnd[6] << 24) |
			      (scsicmd->cmnd[7] << 16) |
			      (scsicmd->cmnd[8] << 8) | scsicmd->cmnd[9];
			अवरोध;
		हाल WRITE_12:
		हाल READ_12:
			lba = ((u64)scsicmd->cmnd[2] << 24) |
			      (scsicmd->cmnd[3] << 16) |
			      (scsicmd->cmnd[4] << 8) | scsicmd->cmnd[5];
			अवरोध;
		शेष:
			lba = ((u64)scsicmd->cmnd[2] << 24) |
			       (scsicmd->cmnd[3] << 16) |
			       (scsicmd->cmnd[4] << 8) | scsicmd->cmnd[5];
			अवरोध;
		पूर्ण
		prपूर्णांकk(KERN_DEBUG
		  "io_callback[cpu %d]: lba = %llu, t = %ld.\n",
		  smp_processor_id(), (अचिन्हित दीर्घ दीर्घ)lba, jअगरfies);
	पूर्ण

	BUG_ON(fibptr == शून्य);

	scsi_dma_unmap(scsicmd);

	पढ़ोreply = (काष्ठा aac_पढ़ो_reply *)fib_data(fibptr);
	चयन (le32_to_cpu(पढ़ोreply->status)) अणु
	हाल ST_OK:
		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		dev->fsa_dev[cid].sense_data.sense_key = NO_SENSE;
		अवरोध;
	हाल ST_NOT_READY:
		scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data, NOT_READY,
		  SENCODE_BECOMING_READY, ASENCODE_BECOMING_READY, 0, 0);
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
		अवरोध;
	हाल ST_MEDERR:
		scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data, MEDIUM_ERROR,
		  SENCODE_UNRECOVERED_READ_ERROR, ASENCODE_NO_SENSE, 0, 0);
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
		अवरोध;
	शेष:
#अगर_घोषित AAC_DETAILED_STATUS_INFO
		prपूर्णांकk(KERN_WARNING "io_callback: io failed, status = %d\n",
		  le32_to_cpu(पढ़ोreply->status));
#पूर्ण_अगर
		scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data,
		  HARDWARE_ERROR, SENCODE_INTERNAL_TARGET_FAILURE,
		  ASENCODE_INTERNAL_TARGET_FAILURE, 0, 0);
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
		अवरोध;
	पूर्ण
	aac_fib_complete(fibptr);

	scsicmd->scsi_करोne(scsicmd);
पूर्ण

अटल पूर्णांक aac_पढ़ो(काष्ठा scsi_cmnd * scsicmd)
अणु
	u64 lba;
	u32 count;
	पूर्णांक status;
	काष्ठा aac_dev *dev;
	काष्ठा fib * cmd_fibcontext;
	पूर्णांक cid;

	dev = (काष्ठा aac_dev *)scsicmd->device->host->hostdata;
	/*
	 *	Get block address and transfer length
	 */
	चयन (scsicmd->cmnd[0]) अणु
	हाल READ_6:
		dprपूर्णांकk((KERN_DEBUG "aachba: received a read(6) command on id %d.\n", scmd_id(scsicmd)));

		lba = ((scsicmd->cmnd[1] & 0x1F) << 16) |
			(scsicmd->cmnd[2] << 8) | scsicmd->cmnd[3];
		count = scsicmd->cmnd[4];

		अगर (count == 0)
			count = 256;
		अवरोध;
	हाल READ_16:
		dprपूर्णांकk((KERN_DEBUG "aachba: received a read(16) command on id %d.\n", scmd_id(scsicmd)));

		lba =	((u64)scsicmd->cmnd[2] << 56) |
			((u64)scsicmd->cmnd[3] << 48) |
			((u64)scsicmd->cmnd[4] << 40) |
			((u64)scsicmd->cmnd[5] << 32) |
			((u64)scsicmd->cmnd[6] << 24) |
			(scsicmd->cmnd[7] << 16) |
			(scsicmd->cmnd[8] << 8) | scsicmd->cmnd[9];
		count = (scsicmd->cmnd[10] << 24) |
			(scsicmd->cmnd[11] << 16) |
			(scsicmd->cmnd[12] << 8) | scsicmd->cmnd[13];
		अवरोध;
	हाल READ_12:
		dprपूर्णांकk((KERN_DEBUG "aachba: received a read(12) command on id %d.\n", scmd_id(scsicmd)));

		lba = ((u64)scsicmd->cmnd[2] << 24) |
			(scsicmd->cmnd[3] << 16) |
			(scsicmd->cmnd[4] << 8) | scsicmd->cmnd[5];
		count = (scsicmd->cmnd[6] << 24) |
			(scsicmd->cmnd[7] << 16) |
			(scsicmd->cmnd[8] << 8) | scsicmd->cmnd[9];
		अवरोध;
	शेष:
		dprपूर्णांकk((KERN_DEBUG "aachba: received a read(10) command on id %d.\n", scmd_id(scsicmd)));

		lba = ((u64)scsicmd->cmnd[2] << 24) |
			(scsicmd->cmnd[3] << 16) |
			(scsicmd->cmnd[4] << 8) | scsicmd->cmnd[5];
		count = (scsicmd->cmnd[7] << 8) | scsicmd->cmnd[8];
		अवरोध;
	पूर्ण

	अगर ((lba + count) > (dev->fsa_dev[scmd_id(scsicmd)].size)) अणु
		cid = scmd_id(scsicmd);
		dprपूर्णांकk((KERN_DEBUG "aacraid: Illegal lba\n"));
		scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data,
			  ILLEGAL_REQUEST, SENCODE_LBA_OUT_OF_RANGE,
			  ASENCODE_INTERNAL_TARGET_FAILURE, 0, 0);
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
		scsicmd->scsi_करोne(scsicmd);
		वापस 0;
	पूर्ण

	dprपूर्णांकk((KERN_DEBUG "aac_read[cpu %d]: lba = %llu, t = %ld.\n",
	  smp_processor_id(), (अचिन्हित दीर्घ दीर्घ)lba, jअगरfies));
	अगर (aac_adapter_bounds(dev,scsicmd,lba))
		वापस 0;
	/*
	 *	Alocate and initialize a Fib
	 */
	cmd_fibcontext = aac_fib_alloc_tag(dev, scsicmd);
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;
	status = aac_adapter_पढ़ो(cmd_fibcontext, scsicmd, lba, count);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	prपूर्णांकk(KERN_WARNING "aac_read: aac_fib_send failed with status: %d.\n", status);
	/*
	 *	For some reason, the Fib didn't queue, वापस QUEUE_FULL
	 */
	scsicmd->result = DID_OK << 16 | SAM_STAT_TASK_SET_FULL;
	scsicmd->scsi_करोne(scsicmd);
	aac_fib_complete(cmd_fibcontext);
	aac_fib_मुक्त(cmd_fibcontext);
	वापस 0;
पूर्ण

अटल पूर्णांक aac_ग_लिखो(काष्ठा scsi_cmnd * scsicmd)
अणु
	u64 lba;
	u32 count;
	पूर्णांक fua;
	पूर्णांक status;
	काष्ठा aac_dev *dev;
	काष्ठा fib * cmd_fibcontext;
	पूर्णांक cid;

	dev = (काष्ठा aac_dev *)scsicmd->device->host->hostdata;
	/*
	 *	Get block address and transfer length
	 */
	अगर (scsicmd->cmnd[0] == WRITE_6)	/* 6 byte command */
	अणु
		lba = ((scsicmd->cmnd[1] & 0x1F) << 16) | (scsicmd->cmnd[2] << 8) | scsicmd->cmnd[3];
		count = scsicmd->cmnd[4];
		अगर (count == 0)
			count = 256;
		fua = 0;
	पूर्ण अन्यथा अगर (scsicmd->cmnd[0] == WRITE_16) अणु /* 16 byte command */
		dprपूर्णांकk((KERN_DEBUG "aachba: received a write(16) command on id %d.\n", scmd_id(scsicmd)));

		lba =	((u64)scsicmd->cmnd[2] << 56) |
			((u64)scsicmd->cmnd[3] << 48) |
			((u64)scsicmd->cmnd[4] << 40) |
			((u64)scsicmd->cmnd[5] << 32) |
			((u64)scsicmd->cmnd[6] << 24) |
			(scsicmd->cmnd[7] << 16) |
			(scsicmd->cmnd[8] << 8) | scsicmd->cmnd[9];
		count = (scsicmd->cmnd[10] << 24) | (scsicmd->cmnd[11] << 16) |
			(scsicmd->cmnd[12] << 8) | scsicmd->cmnd[13];
		fua = scsicmd->cmnd[1] & 0x8;
	पूर्ण अन्यथा अगर (scsicmd->cmnd[0] == WRITE_12) अणु /* 12 byte command */
		dprपूर्णांकk((KERN_DEBUG "aachba: received a write(12) command on id %d.\n", scmd_id(scsicmd)));

		lba = ((u64)scsicmd->cmnd[2] << 24) | (scsicmd->cmnd[3] << 16)
		    | (scsicmd->cmnd[4] << 8) | scsicmd->cmnd[5];
		count = (scsicmd->cmnd[6] << 24) | (scsicmd->cmnd[7] << 16)
		      | (scsicmd->cmnd[8] << 8) | scsicmd->cmnd[9];
		fua = scsicmd->cmnd[1] & 0x8;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk((KERN_DEBUG "aachba: received a write(10) command on id %d.\n", scmd_id(scsicmd)));
		lba = ((u64)scsicmd->cmnd[2] << 24) | (scsicmd->cmnd[3] << 16) | (scsicmd->cmnd[4] << 8) | scsicmd->cmnd[5];
		count = (scsicmd->cmnd[7] << 8) | scsicmd->cmnd[8];
		fua = scsicmd->cmnd[1] & 0x8;
	पूर्ण

	अगर ((lba + count) > (dev->fsa_dev[scmd_id(scsicmd)].size)) अणु
		cid = scmd_id(scsicmd);
		dprपूर्णांकk((KERN_DEBUG "aacraid: Illegal lba\n"));
		scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data,
			  ILLEGAL_REQUEST, SENCODE_LBA_OUT_OF_RANGE,
			  ASENCODE_INTERNAL_TARGET_FAILURE, 0, 0);
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
		scsicmd->scsi_करोne(scsicmd);
		वापस 0;
	पूर्ण

	dprपूर्णांकk((KERN_DEBUG "aac_write[cpu %d]: lba = %llu, t = %ld.\n",
	  smp_processor_id(), (अचिन्हित दीर्घ दीर्घ)lba, jअगरfies));
	अगर (aac_adapter_bounds(dev,scsicmd,lba))
		वापस 0;
	/*
	 *	Allocate and initialize a Fib then setup a BlockWrite command
	 */
	cmd_fibcontext = aac_fib_alloc_tag(dev, scsicmd);
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;
	status = aac_adapter_ग_लिखो(cmd_fibcontext, scsicmd, lba, count, fua);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	prपूर्णांकk(KERN_WARNING "aac_write: aac_fib_send failed with status: %d\n", status);
	/*
	 *	For some reason, the Fib didn't queue, वापस QUEUE_FULL
	 */
	scsicmd->result = DID_OK << 16 | SAM_STAT_TASK_SET_FULL;
	scsicmd->scsi_करोne(scsicmd);

	aac_fib_complete(cmd_fibcontext);
	aac_fib_मुक्त(cmd_fibcontext);
	वापस 0;
पूर्ण

अटल व्योम synchronize_callback(व्योम *context, काष्ठा fib *fibptr)
अणु
	काष्ठा aac_synchronize_reply *synchronizereply;
	काष्ठा scsi_cmnd *cmd = context;

	अगर (!aac_valid_context(cmd, fibptr))
		वापस;

	dprपूर्णांकk((KERN_DEBUG "synchronize_callback[cpu %d]: t = %ld.\n",
				smp_processor_id(), jअगरfies));
	BUG_ON(fibptr == शून्य);


	synchronizereply = fib_data(fibptr);
	अगर (le32_to_cpu(synchronizereply->status) == CT_OK)
		cmd->result = DID_OK << 16 | SAM_STAT_GOOD;
	अन्यथा अणु
		काष्ठा scsi_device *sdev = cmd->device;
		काष्ठा aac_dev *dev = fibptr->dev;
		u32 cid = sdev_id(sdev);
		prपूर्णांकk(KERN_WARNING
		     "synchronize_callback: synchronize failed, status = %d\n",
		     le32_to_cpu(synchronizereply->status));
		cmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data,
		  HARDWARE_ERROR, SENCODE_INTERNAL_TARGET_FAILURE,
		  ASENCODE_INTERNAL_TARGET_FAILURE, 0, 0);
		स_नकल(cmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
	पूर्ण

	aac_fib_complete(fibptr);
	aac_fib_मुक्त(fibptr);
	cmd->scsi_करोne(cmd);
पूर्ण

अटल पूर्णांक aac_synchronize(काष्ठा scsi_cmnd *scsicmd)
अणु
	पूर्णांक status;
	काष्ठा fib *cmd_fibcontext;
	काष्ठा aac_synchronize *synchronizecmd;
	काष्ठा scsi_device *sdev = scsicmd->device;
	काष्ठा aac_dev *aac;

	aac = (काष्ठा aac_dev *)sdev->host->hostdata;
	अगर (aac->in_reset)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/*
	 *	Allocate and initialize a Fib
	 */
	cmd_fibcontext = aac_fib_alloc_tag(aac, scsicmd);

	aac_fib_init(cmd_fibcontext);

	synchronizecmd = fib_data(cmd_fibcontext);
	synchronizecmd->command = cpu_to_le32(VM_ContainerConfig);
	synchronizecmd->type = cpu_to_le32(CT_FLUSH_CACHE);
	synchronizecmd->cid = cpu_to_le32(scmd_id(scsicmd));
	synchronizecmd->count =
	     cpu_to_le32(माप(((काष्ठा aac_synchronize_reply *)शून्य)->data));
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;

	/*
	 *	Now send the Fib to the adapter
	 */
	status = aac_fib_send(ContainerCommand,
		  cmd_fibcontext,
		  माप(काष्ठा aac_synchronize),
		  FsaNormal,
		  0, 1,
		  (fib_callback)synchronize_callback,
		  (व्योम *)scsicmd);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	prपूर्णांकk(KERN_WARNING
		"aac_synchronize: aac_fib_send failed with status: %d.\n", status);
	aac_fib_complete(cmd_fibcontext);
	aac_fib_मुक्त(cmd_fibcontext);
	वापस SCSI_MLQUEUE_HOST_BUSY;
पूर्ण

अटल व्योम aac_start_stop_callback(व्योम *context, काष्ठा fib *fibptr)
अणु
	काष्ठा scsi_cmnd *scsicmd = context;

	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	BUG_ON(fibptr == शून्य);

	scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;

	aac_fib_complete(fibptr);
	aac_fib_मुक्त(fibptr);
	scsicmd->scsi_करोne(scsicmd);
पूर्ण

अटल पूर्णांक aac_start_stop(काष्ठा scsi_cmnd *scsicmd)
अणु
	पूर्णांक status;
	काष्ठा fib *cmd_fibcontext;
	काष्ठा aac_घातer_management *pmcmd;
	काष्ठा scsi_device *sdev = scsicmd->device;
	काष्ठा aac_dev *aac = (काष्ठा aac_dev *)sdev->host->hostdata;

	अगर (!(aac->supplement_adapter_info.supported_options2 &
	      AAC_OPTION_POWER_MANAGEMENT)) अणु
		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		scsicmd->scsi_करोne(scsicmd);
		वापस 0;
	पूर्ण

	अगर (aac->in_reset)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/*
	 *	Allocate and initialize a Fib
	 */
	cmd_fibcontext = aac_fib_alloc_tag(aac, scsicmd);

	aac_fib_init(cmd_fibcontext);

	pmcmd = fib_data(cmd_fibcontext);
	pmcmd->command = cpu_to_le32(VM_ContainerConfig);
	pmcmd->type = cpu_to_le32(CT_POWER_MANAGEMENT);
	/* Eject bit ignored, not relevant */
	pmcmd->sub = (scsicmd->cmnd[4] & 1) ?
		cpu_to_le32(CT_PM_START_UNIT) : cpu_to_le32(CT_PM_STOP_UNIT);
	pmcmd->cid = cpu_to_le32(sdev_id(sdev));
	pmcmd->parm = (scsicmd->cmnd[1] & 1) ?
		cpu_to_le32(CT_PM_UNIT_IMMEDIATE) : 0;
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;

	/*
	 *	Now send the Fib to the adapter
	 */
	status = aac_fib_send(ContainerCommand,
		  cmd_fibcontext,
		  माप(काष्ठा aac_घातer_management),
		  FsaNormal,
		  0, 1,
		  (fib_callback)aac_start_stop_callback,
		  (व्योम *)scsicmd);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	aac_fib_complete(cmd_fibcontext);
	aac_fib_मुक्त(cmd_fibcontext);
	वापस SCSI_MLQUEUE_HOST_BUSY;
पूर्ण

/**
 *	aac_scsi_cmd()		-	Process SCSI command
 *	@scsicmd:		SCSI command block
 *
 *	Emulate a SCSI command and queue the required request क्रम the
 *	aacraid firmware.
 */

पूर्णांक aac_scsi_cmd(काष्ठा scsi_cmnd * scsicmd)
अणु
	u32 cid, bus;
	काष्ठा Scsi_Host *host = scsicmd->device->host;
	काष्ठा aac_dev *dev = (काष्ठा aac_dev *)host->hostdata;
	काष्ठा fsa_dev_info *fsa_dev_ptr = dev->fsa_dev;

	अगर (fsa_dev_ptr == शून्य)
		वापस -1;
	/*
	 *	If the bus, id or lun is out of range, वापस fail
	 *	Test करोes not apply to ID 16, the pseuकरो id क्रम the controller
	 *	itself.
	 */
	cid = scmd_id(scsicmd);
	अगर (cid != host->this_id) अणु
		अगर (scmd_channel(scsicmd) == CONTAINER_CHANNEL) अणु
			अगर((cid >= dev->maximum_num_containers) ||
					(scsicmd->device->lun != 0)) अणु
				scsicmd->result = DID_NO_CONNECT << 16;
				जाओ scsi_करोne_ret;
			पूर्ण

			/*
			 *	If the target container करोesn't exist, it may have
			 *	been newly created
			 */
			अगर (((fsa_dev_ptr[cid].valid & 1) == 0) ||
			  (fsa_dev_ptr[cid].sense_data.sense_key ==
			   NOT_READY)) अणु
				चयन (scsicmd->cmnd[0]) अणु
				हाल SERVICE_ACTION_IN_16:
					अगर (!(dev->raw_io_पूर्णांकerface) ||
					    !(dev->raw_io_64) ||
					    ((scsicmd->cmnd[1] & 0x1f) != SAI_READ_CAPACITY_16))
						अवरोध;
					fallthrough;
				हाल INQUIRY:
				हाल READ_CAPACITY:
				हाल TEST_UNIT_READY:
					अगर (dev->in_reset)
						वापस -1;
					वापस _aac_probe_container(scsicmd,
							aac_probe_container_callback2);
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु  /* check क्रम physical non-dasd devices */
			bus = aac_logical_to_phys(scmd_channel(scsicmd));

			अगर (bus < AAC_MAX_BUSES && cid < AAC_MAX_TARGETS &&
				dev->hba_map[bus][cid].devtype
					== AAC_DEVTYPE_NATIVE_RAW) अणु
				अगर (dev->in_reset)
					वापस -1;
				वापस aac_send_hba_fib(scsicmd);
			पूर्ण अन्यथा अगर (dev->nondasd_support || expose_physicals ||
				dev->jbod) अणु
				अगर (dev->in_reset)
					वापस -1;
				वापस aac_send_srb_fib(scsicmd);
			पूर्ण अन्यथा अणु
				scsicmd->result = DID_NO_CONNECT << 16;
				जाओ scsi_करोne_ret;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * अन्यथा Command क्रम the controller itself
	 */
	अन्यथा अगर ((scsicmd->cmnd[0] != INQUIRY) &&	/* only INQUIRY & TUR cmnd supported क्रम controller */
		(scsicmd->cmnd[0] != TEST_UNIT_READY))
	अणु
		dprपूर्णांकk((KERN_WARNING "Only INQUIRY & TUR command supported for controller, rcvd = 0x%x.\n", scsicmd->cmnd[0]));
		scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data,
		  ILLEGAL_REQUEST, SENCODE_INVALID_COMMAND,
		  ASENCODE_INVALID_COMMAND, 0, 0);
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
		       min_t(माप_प्रकार, माप(dev->fsa_dev[cid].sense_data),
			     SCSI_SENSE_BUFFERSIZE));
		जाओ scsi_करोne_ret;
	पूर्ण

	चयन (scsicmd->cmnd[0]) अणु
	हाल READ_6:
	हाल READ_10:
	हाल READ_12:
	हाल READ_16:
		अगर (dev->in_reset)
			वापस -1;
		वापस aac_पढ़ो(scsicmd);

	हाल WRITE_6:
	हाल WRITE_10:
	हाल WRITE_12:
	हाल WRITE_16:
		अगर (dev->in_reset)
			वापस -1;
		वापस aac_ग_लिखो(scsicmd);

	हाल SYNCHRONIZE_CACHE:
		अगर (((aac_cache & 6) == 6) && dev->cache_रक्षित) अणु
			scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
			अवरोध;
		पूर्ण
		/* Issue FIB to tell Firmware to flush it's cache */
		अगर ((aac_cache & 6) != 2)
			वापस aac_synchronize(scsicmd);
		fallthrough;
	हाल INQUIRY:
	अणु
		काष्ठा inquiry_data inq_data;

		dprपूर्णांकk((KERN_DEBUG "INQUIRY command, ID: %d.\n", cid));
		स_रखो(&inq_data, 0, माप (काष्ठा inquiry_data));

		अगर ((scsicmd->cmnd[1] & 0x1) && aac_wwn) अणु
			अक्षर *arr = (अक्षर *)&inq_data;

			/* EVPD bit set */
			arr[0] = (scmd_id(scsicmd) == host->this_id) ?
			  INQD_PDT_PROC : INQD_PDT_DA;
			अगर (scsicmd->cmnd[2] == 0) अणु
				/* supported vital product data pages */
				arr[3] = 3;
				arr[4] = 0x0;
				arr[5] = 0x80;
				arr[6] = 0x83;
				arr[1] = scsicmd->cmnd[2];
				scsi_sg_copy_from_buffer(scsicmd, &inq_data,
							 माप(inq_data));
				scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
			पूर्ण अन्यथा अगर (scsicmd->cmnd[2] == 0x80) अणु
				/* unit serial number page */
				arr[3] = setinqserial(dev, &arr[4],
				  scmd_id(scsicmd));
				arr[1] = scsicmd->cmnd[2];
				scsi_sg_copy_from_buffer(scsicmd, &inq_data,
							 माप(inq_data));
				अगर (aac_wwn != 2)
					वापस aac_get_container_serial(
						scsicmd);
				scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
			पूर्ण अन्यथा अगर (scsicmd->cmnd[2] == 0x83) अणु
				/* vpd page 0x83 - Device Identअगरication Page */
				अक्षर *sno = (अक्षर *)&inq_data;
				sno[3] = setinqserial(dev, &sno[4],
						      scmd_id(scsicmd));
				अगर (aac_wwn != 2)
					वापस aac_get_container_serial(
						scsicmd);
				scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
			पूर्ण अन्यथा अणु
				/* vpd page not implemented */
				scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
				set_sense(&dev->fsa_dev[cid].sense_data,
				  ILLEGAL_REQUEST, SENCODE_INVALID_CDB_FIELD,
				  ASENCODE_NO_SENSE, 7, 2);
				स_नकल(scsicmd->sense_buffer,
				  &dev->fsa_dev[cid].sense_data,
				  min_t(माप_प्रकार,
					माप(dev->fsa_dev[cid].sense_data),
					SCSI_SENSE_BUFFERSIZE));
			पूर्ण
			अवरोध;
		पूर्ण
		inq_data.inqd_ver = 2;	/* claim compliance to SCSI-2 */
		inq_data.inqd_rdf = 2;	/* A response data क्रमmat value of two indicates that the data shall be in the क्रमmat specअगरied in SCSI-2 */
		inq_data.inqd_len = 31;
		/*Format क्रम "pad2" is  RelAdr | WBus32 | WBus16 |  Sync  | Linked |Reserved| CmdQue | SftRe */
		inq_data.inqd_pad2= 0x32 ;	 /*WBus16|Sync|CmdQue */
		/*
		 *	Set the Venकरोr, Product, and Revision Level
		 *	see: <venकरोr>.c i.e. aac.c
		 */
		अगर (cid == host->this_id) अणु
			setinqstr(dev, (व्योम *) (inq_data.inqd_vid), ARRAY_SIZE(container_types));
			inq_data.inqd_pdt = INQD_PDT_PROC;	/* Processor device */
			scsi_sg_copy_from_buffer(scsicmd, &inq_data,
						 माप(inq_data));
			scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
			अवरोध;
		पूर्ण
		अगर (dev->in_reset)
			वापस -1;
		setinqstr(dev, (व्योम *) (inq_data.inqd_vid), fsa_dev_ptr[cid].type);
		inq_data.inqd_pdt = INQD_PDT_DA;	/* Direct/अक्रमom access device */
		scsi_sg_copy_from_buffer(scsicmd, &inq_data, माप(inq_data));
		वापस aac_get_container_name(scsicmd);
	पूर्ण
	हाल SERVICE_ACTION_IN_16:
		अगर (!(dev->raw_io_पूर्णांकerface) ||
		    !(dev->raw_io_64) ||
		    ((scsicmd->cmnd[1] & 0x1f) != SAI_READ_CAPACITY_16))
			अवरोध;
	अणु
		u64 capacity;
		अक्षर cp[13];
		अचिन्हित पूर्णांक alloc_len;

		dprपूर्णांकk((KERN_DEBUG "READ CAPACITY_16 command.\n"));
		capacity = fsa_dev_ptr[cid].size - 1;
		cp[0] = (capacity >> 56) & 0xff;
		cp[1] = (capacity >> 48) & 0xff;
		cp[2] = (capacity >> 40) & 0xff;
		cp[3] = (capacity >> 32) & 0xff;
		cp[4] = (capacity >> 24) & 0xff;
		cp[5] = (capacity >> 16) & 0xff;
		cp[6] = (capacity >> 8) & 0xff;
		cp[7] = (capacity >> 0) & 0xff;
		cp[8] = (fsa_dev_ptr[cid].block_size >> 24) & 0xff;
		cp[9] = (fsa_dev_ptr[cid].block_size >> 16) & 0xff;
		cp[10] = (fsa_dev_ptr[cid].block_size >> 8) & 0xff;
		cp[11] = (fsa_dev_ptr[cid].block_size) & 0xff;
		cp[12] = 0;

		alloc_len = ((scsicmd->cmnd[10] << 24)
			     + (scsicmd->cmnd[11] << 16)
			     + (scsicmd->cmnd[12] << 8) + scsicmd->cmnd[13]);

		alloc_len = min_t(माप_प्रकार, alloc_len, माप(cp));
		scsi_sg_copy_from_buffer(scsicmd, cp, alloc_len);
		अगर (alloc_len < scsi_bufflen(scsicmd))
			scsi_set_resid(scsicmd,
				       scsi_bufflen(scsicmd) - alloc_len);

		/* Do not cache partition table क्रम arrays */
		scsicmd->device->removable = 1;

		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		अवरोध;
	पूर्ण

	हाल READ_CAPACITY:
	अणु
		u32 capacity;
		अक्षर cp[8];

		dprपूर्णांकk((KERN_DEBUG "READ CAPACITY command.\n"));
		अगर (fsa_dev_ptr[cid].size <= 0x100000000ULL)
			capacity = fsa_dev_ptr[cid].size - 1;
		अन्यथा
			capacity = (u32)-1;

		cp[0] = (capacity >> 24) & 0xff;
		cp[1] = (capacity >> 16) & 0xff;
		cp[2] = (capacity >> 8) & 0xff;
		cp[3] = (capacity >> 0) & 0xff;
		cp[4] = (fsa_dev_ptr[cid].block_size >> 24) & 0xff;
		cp[5] = (fsa_dev_ptr[cid].block_size >> 16) & 0xff;
		cp[6] = (fsa_dev_ptr[cid].block_size >> 8) & 0xff;
		cp[7] = (fsa_dev_ptr[cid].block_size) & 0xff;
		scsi_sg_copy_from_buffer(scsicmd, cp, माप(cp));
		/* Do not cache partition table क्रम arrays */
		scsicmd->device->removable = 1;
		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		अवरोध;
	पूर्ण

	हाल MODE_SENSE:
	अणु
		पूर्णांक mode_buf_length = 4;
		u32 capacity;
		aac_modep_data mpd;

		अगर (fsa_dev_ptr[cid].size <= 0x100000000ULL)
			capacity = fsa_dev_ptr[cid].size - 1;
		अन्यथा
			capacity = (u32)-1;

		dprपूर्णांकk((KERN_DEBUG "MODE SENSE command.\n"));
		स_रखो((अक्षर *)&mpd, 0, माप(aac_modep_data));

		/* Mode data length */
		mpd.hd.data_length = माप(mpd.hd) - 1;
		/* Medium type - शेष */
		mpd.hd.med_type = 0;
		/* Device-specअगरic param,
		   bit 8: 0/1 = ग_लिखो enabled/रक्षित
		   bit 4: 0/1 = FUA enabled */
		mpd.hd.dev_par = 0;

		अगर (dev->raw_io_पूर्णांकerface && ((aac_cache & 5) != 1))
			mpd.hd.dev_par = 0x10;
		अगर (scsicmd->cmnd[1] & 0x8)
			mpd.hd.bd_length = 0;	/* Block descriptor length */
		अन्यथा अणु
			mpd.hd.bd_length = माप(mpd.bd);
			mpd.hd.data_length += mpd.hd.bd_length;
			mpd.bd.block_length[0] =
				(fsa_dev_ptr[cid].block_size >> 16) & 0xff;
			mpd.bd.block_length[1] =
				(fsa_dev_ptr[cid].block_size >> 8) &  0xff;
			mpd.bd.block_length[2] =
				fsa_dev_ptr[cid].block_size  & 0xff;

			mpd.mpc_buf[0] = scsicmd->cmnd[2];
			अगर (scsicmd->cmnd[2] == 0x1C) अणु
				/* page length */
				mpd.mpc_buf[1] = 0xa;
				/* Mode data length */
				mpd.hd.data_length = 23;
			पूर्ण अन्यथा अणु
				/* Mode data length */
				mpd.hd.data_length = 15;
			पूर्ण

			अगर (capacity > 0xffffff) अणु
				mpd.bd.block_count[0] = 0xff;
				mpd.bd.block_count[1] = 0xff;
				mpd.bd.block_count[2] = 0xff;
			पूर्ण अन्यथा अणु
				mpd.bd.block_count[0] = (capacity >> 16) & 0xff;
				mpd.bd.block_count[1] = (capacity >> 8) & 0xff;
				mpd.bd.block_count[2] = capacity  & 0xff;
			पूर्ण
		पूर्ण
		अगर (((scsicmd->cmnd[2] & 0x3f) == 8) ||
		  ((scsicmd->cmnd[2] & 0x3f) == 0x3f)) अणु
			mpd.hd.data_length += 3;
			mpd.mpc_buf[0] = 8;
			mpd.mpc_buf[1] = 1;
			mpd.mpc_buf[2] = ((aac_cache & 6) == 2)
				? 0 : 0x04; /* WCE */
			mode_buf_length = माप(mpd);
		पूर्ण

		अगर (mode_buf_length > scsicmd->cmnd[4])
			mode_buf_length = scsicmd->cmnd[4];
		अन्यथा
			mode_buf_length = माप(mpd);
		scsi_sg_copy_from_buffer(scsicmd,
					 (अक्षर *)&mpd,
					 mode_buf_length);
		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		अवरोध;
	पूर्ण
	हाल MODE_SENSE_10:
	अणु
		u32 capacity;
		पूर्णांक mode_buf_length = 8;
		aac_modep10_data mpd10;

		अगर (fsa_dev_ptr[cid].size <= 0x100000000ULL)
			capacity = fsa_dev_ptr[cid].size - 1;
		अन्यथा
			capacity = (u32)-1;

		dprपूर्णांकk((KERN_DEBUG "MODE SENSE 10 byte command.\n"));
		स_रखो((अक्षर *)&mpd10, 0, माप(aac_modep10_data));
		/* Mode data length (MSB) */
		mpd10.hd.data_length[0] = 0;
		/* Mode data length (LSB) */
		mpd10.hd.data_length[1] = माप(mpd10.hd) - 1;
		/* Medium type - शेष */
		mpd10.hd.med_type = 0;
		/* Device-specअगरic param,
		   bit 8: 0/1 = ग_लिखो enabled/रक्षित
		   bit 4: 0/1 = FUA enabled */
		mpd10.hd.dev_par = 0;

		अगर (dev->raw_io_पूर्णांकerface && ((aac_cache & 5) != 1))
			mpd10.hd.dev_par = 0x10;
		mpd10.hd.rsrvd[0] = 0;	/* reserved */
		mpd10.hd.rsrvd[1] = 0;	/* reserved */
		अगर (scsicmd->cmnd[1] & 0x8) अणु
			/* Block descriptor length (MSB) */
			mpd10.hd.bd_length[0] = 0;
			/* Block descriptor length (LSB) */
			mpd10.hd.bd_length[1] = 0;
		पूर्ण अन्यथा अणु
			mpd10.hd.bd_length[0] = 0;
			mpd10.hd.bd_length[1] = माप(mpd10.bd);

			mpd10.hd.data_length[1] += mpd10.hd.bd_length[1];

			mpd10.bd.block_length[0] =
				(fsa_dev_ptr[cid].block_size >> 16) & 0xff;
			mpd10.bd.block_length[1] =
				(fsa_dev_ptr[cid].block_size >> 8) & 0xff;
			mpd10.bd.block_length[2] =
				fsa_dev_ptr[cid].block_size  & 0xff;

			अगर (capacity > 0xffffff) अणु
				mpd10.bd.block_count[0] = 0xff;
				mpd10.bd.block_count[1] = 0xff;
				mpd10.bd.block_count[2] = 0xff;
			पूर्ण अन्यथा अणु
				mpd10.bd.block_count[0] =
					(capacity >> 16) & 0xff;
				mpd10.bd.block_count[1] =
					(capacity >> 8) & 0xff;
				mpd10.bd.block_count[2] =
					capacity  & 0xff;
			पूर्ण
		पूर्ण
		अगर (((scsicmd->cmnd[2] & 0x3f) == 8) ||
		  ((scsicmd->cmnd[2] & 0x3f) == 0x3f)) अणु
			mpd10.hd.data_length[1] += 3;
			mpd10.mpc_buf[0] = 8;
			mpd10.mpc_buf[1] = 1;
			mpd10.mpc_buf[2] = ((aac_cache & 6) == 2)
				? 0 : 0x04; /* WCE */
			mode_buf_length = माप(mpd10);
			अगर (mode_buf_length > scsicmd->cmnd[8])
				mode_buf_length = scsicmd->cmnd[8];
		पूर्ण
		scsi_sg_copy_from_buffer(scsicmd,
					 (अक्षर *)&mpd10,
					 mode_buf_length);

		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		अवरोध;
	पूर्ण
	हाल REQUEST_SENSE:
		dprपूर्णांकk((KERN_DEBUG "REQUEST SENSE command.\n"));
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
				माप(काष्ठा sense_data));
		स_रखो(&dev->fsa_dev[cid].sense_data, 0,
				माप(काष्ठा sense_data));
		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		अवरोध;

	हाल ALLOW_MEDIUM_REMOVAL:
		dprपूर्णांकk((KERN_DEBUG "LOCK command.\n"));
		अगर (scsicmd->cmnd[4])
			fsa_dev_ptr[cid].locked = 1;
		अन्यथा
			fsa_dev_ptr[cid].locked = 0;

		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		अवरोध;
	/*
	 *	These commands are all No-Ops
	 */
	हाल TEST_UNIT_READY:
		अगर (fsa_dev_ptr[cid].sense_data.sense_key == NOT_READY) अणु
			scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
			set_sense(&dev->fsa_dev[cid].sense_data,
				  NOT_READY, SENCODE_BECOMING_READY,
				  ASENCODE_BECOMING_READY, 0, 0);
			स_नकल(scsicmd->sense_buffer,
			       &dev->fsa_dev[cid].sense_data,
			       min_t(माप_प्रकार,
				     माप(dev->fsa_dev[cid].sense_data),
				     SCSI_SENSE_BUFFERSIZE));
			अवरोध;
		पूर्ण
		fallthrough;
	हाल RESERVE:
	हाल RELEASE:
	हाल REZERO_UNIT:
	हाल REASSIGN_BLOCKS:
	हाल SEEK_10:
		scsicmd->result = DID_OK << 16 | SAM_STAT_GOOD;
		अवरोध;

	हाल START_STOP:
		वापस aac_start_stop(scsicmd);

	शेष:
	/*
	 *	Unhandled commands
	 */
		dprपूर्णांकk((KERN_WARNING "Unhandled SCSI Command: 0x%x.\n",
				scsicmd->cmnd[0]));
		scsicmd->result = DID_OK << 16 | SAM_STAT_CHECK_CONDITION;
		set_sense(&dev->fsa_dev[cid].sense_data,
			  ILLEGAL_REQUEST, SENCODE_INVALID_COMMAND,
			  ASENCODE_INVALID_COMMAND, 0, 0);
		स_नकल(scsicmd->sense_buffer, &dev->fsa_dev[cid].sense_data,
				min_t(माप_प्रकार,
				      माप(dev->fsa_dev[cid].sense_data),
				      SCSI_SENSE_BUFFERSIZE));
	पूर्ण

scsi_करोne_ret:

	scsicmd->scsi_करोne(scsicmd);
	वापस 0;
पूर्ण

अटल पूर्णांक query_disk(काष्ठा aac_dev *dev, व्योम __user *arg)
अणु
	काष्ठा aac_query_disk qd;
	काष्ठा fsa_dev_info *fsa_dev_ptr;

	fsa_dev_ptr = dev->fsa_dev;
	अगर (!fsa_dev_ptr)
		वापस -EBUSY;
	अगर (copy_from_user(&qd, arg, माप (काष्ठा aac_query_disk)))
		वापस -EFAULT;
	अगर (qd.cnum == -1) अणु
		अगर (qd.id < 0 || qd.id >= dev->maximum_num_containers)
			वापस -EINVAL;
		qd.cnum = qd.id;
	पूर्ण अन्यथा अगर ((qd.bus == -1) && (qd.id == -1) && (qd.lun == -1)) अणु
		अगर (qd.cnum < 0 || qd.cnum >= dev->maximum_num_containers)
			वापस -EINVAL;
		qd.instance = dev->scsi_host_ptr->host_no;
		qd.bus = 0;
		qd.id = CONTAINER_TO_ID(qd.cnum);
		qd.lun = CONTAINER_TO_LUN(qd.cnum);
	पूर्ण
	अन्यथा वापस -EINVAL;

	qd.valid = fsa_dev_ptr[qd.cnum].valid != 0;
	qd.locked = fsa_dev_ptr[qd.cnum].locked;
	qd.deleted = fsa_dev_ptr[qd.cnum].deleted;

	अगर (fsa_dev_ptr[qd.cnum].devname[0] == '\0')
		qd.unmapped = 1;
	अन्यथा
		qd.unmapped = 0;

	strlcpy(qd.name, fsa_dev_ptr[qd.cnum].devname,
	  min(माप(qd.name), माप(fsa_dev_ptr[qd.cnum].devname) + 1));

	अगर (copy_to_user(arg, &qd, माप (काष्ठा aac_query_disk)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमce_delete_disk(काष्ठा aac_dev *dev, व्योम __user *arg)
अणु
	काष्ठा aac_delete_disk dd;
	काष्ठा fsa_dev_info *fsa_dev_ptr;

	fsa_dev_ptr = dev->fsa_dev;
	अगर (!fsa_dev_ptr)
		वापस -EBUSY;

	अगर (copy_from_user(&dd, arg, माप (काष्ठा aac_delete_disk)))
		वापस -EFAULT;

	अगर (dd.cnum >= dev->maximum_num_containers)
		वापस -EINVAL;
	/*
	 *	Mark this container as being deleted.
	 */
	fsa_dev_ptr[dd.cnum].deleted = 1;
	/*
	 *	Mark the container as no दीर्घer valid
	 */
	fsa_dev_ptr[dd.cnum].valid = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक delete_disk(काष्ठा aac_dev *dev, व्योम __user *arg)
अणु
	काष्ठा aac_delete_disk dd;
	काष्ठा fsa_dev_info *fsa_dev_ptr;

	fsa_dev_ptr = dev->fsa_dev;
	अगर (!fsa_dev_ptr)
		वापस -EBUSY;

	अगर (copy_from_user(&dd, arg, माप (काष्ठा aac_delete_disk)))
		वापस -EFAULT;

	अगर (dd.cnum >= dev->maximum_num_containers)
		वापस -EINVAL;
	/*
	 *	If the container is locked, it can not be deleted by the API.
	 */
	अगर (fsa_dev_ptr[dd.cnum].locked)
		वापस -EBUSY;
	अन्यथा अणु
		/*
		 *	Mark the container as no दीर्घer being valid.
		 */
		fsa_dev_ptr[dd.cnum].valid = 0;
		fsa_dev_ptr[dd.cnum].devname[0] = '\0';
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक aac_dev_ioctl(काष्ठा aac_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	चयन (cmd) अणु
	हाल FSACTL_QUERY_DISK:
		वापस query_disk(dev, arg);
	हाल FSACTL_DELETE_DISK:
		वापस delete_disk(dev, arg);
	हाल FSACTL_FORCE_DELETE_DISK:
		वापस क्रमce_delete_disk(dev, arg);
	हाल FSACTL_GET_CONTAINERS:
		वापस aac_get_containers(dev);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/**
 * aac_srb_callback
 * @context: the context set in the fib - here it is scsi cmd
 * @fibptr: poपूर्णांकer to the fib
 *
 * Handles the completion of a scsi command to a non dasd device
 */
अटल व्योम aac_srb_callback(व्योम *context, काष्ठा fib * fibptr)
अणु
	काष्ठा aac_srb_reply *srbreply;
	काष्ठा scsi_cmnd *scsicmd;

	scsicmd = (काष्ठा scsi_cmnd *) context;

	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	BUG_ON(fibptr == शून्य);

	srbreply = (काष्ठा aac_srb_reply *) fib_data(fibptr);

	scsicmd->sense_buffer[0] = '\0';  /* Initialize sense valid flag to false */

	अगर (fibptr->flags & FIB_CONTEXT_FLAG_FASTRESP) अणु
		/* fast response */
		srbreply->srb_status = cpu_to_le32(SRB_STATUS_SUCCESS);
		srbreply->scsi_status = cpu_to_le32(SAM_STAT_GOOD);
	पूर्ण अन्यथा अणु
		/*
		 *	Calculate resid क्रम sg
		 */
		scsi_set_resid(scsicmd, scsi_bufflen(scsicmd)
				   - le32_to_cpu(srbreply->data_xfer_length));
	पूर्ण


	scsi_dma_unmap(scsicmd);

	/* expose physical device अगर expose_physicald flag is on */
	अगर (scsicmd->cmnd[0] == INQUIRY && !(scsicmd->cmnd[1] & 0x01)
	  && expose_physicals > 0)
		aac_expose_phy_device(scsicmd);

	/*
	 * First check the fib status
	 */

	अगर (le32_to_cpu(srbreply->status) != ST_OK) अणु
		पूर्णांक len;

		pr_warn("aac_srb_callback: srb failed, status = %d\n",
				le32_to_cpu(srbreply->status));
		len = min_t(u32, le32_to_cpu(srbreply->sense_data_size),
			    SCSI_SENSE_BUFFERSIZE);
		scsicmd->result = DID_ERROR << 16 | SAM_STAT_CHECK_CONDITION;
		स_नकल(scsicmd->sense_buffer,
				srbreply->sense_data, len);
	पूर्ण

	/*
	 * Next check the srb status
	 */
	चयन ((le32_to_cpu(srbreply->srb_status))&0x3f) अणु
	हाल SRB_STATUS_ERROR_RECOVERY:
	हाल SRB_STATUS_PENDING:
	हाल SRB_STATUS_SUCCESS:
		scsicmd->result = DID_OK << 16;
		अवरोध;
	हाल SRB_STATUS_DATA_OVERRUN:
		चयन (scsicmd->cmnd[0]) अणु
		हाल  READ_6:
		हाल  WRITE_6:
		हाल  READ_10:
		हाल  WRITE_10:
		हाल  READ_12:
		हाल  WRITE_12:
		हाल  READ_16:
		हाल  WRITE_16:
			अगर (le32_to_cpu(srbreply->data_xfer_length)
						< scsicmd->underflow)
				pr_warn("aacraid: SCSI CMD underflow\n");
			अन्यथा
				pr_warn("aacraid: SCSI CMD Data Overrun\n");
			scsicmd->result = DID_ERROR << 16;
			अवरोध;
		हाल INQUIRY:
			scsicmd->result = DID_OK << 16;
			अवरोध;
		शेष:
			scsicmd->result = DID_OK << 16;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SRB_STATUS_ABORTED:
		scsicmd->result = DID_ABORT << 16;
		अवरोध;
	हाल SRB_STATUS_ABORT_FAILED:
		/*
		 * Not sure about this one - but assuming the
		 * hba was trying to पात क्रम some reason
		 */
		scsicmd->result = DID_ERROR << 16;
		अवरोध;
	हाल SRB_STATUS_PARITY_ERROR:
		scsicmd->result = DID_PARITY << 16;
		अवरोध;
	हाल SRB_STATUS_NO_DEVICE:
	हाल SRB_STATUS_INVALID_PATH_ID:
	हाल SRB_STATUS_INVALID_TARGET_ID:
	हाल SRB_STATUS_INVALID_LUN:
	हाल SRB_STATUS_SELECTION_TIMEOUT:
		scsicmd->result = DID_NO_CONNECT << 16;
		अवरोध;

	हाल SRB_STATUS_COMMAND_TIMEOUT:
	हाल SRB_STATUS_TIMEOUT:
		scsicmd->result = DID_TIME_OUT << 16;
		अवरोध;

	हाल SRB_STATUS_BUSY:
		scsicmd->result = DID_BUS_BUSY << 16;
		अवरोध;

	हाल SRB_STATUS_BUS_RESET:
		scsicmd->result = DID_RESET << 16;
		अवरोध;

	हाल SRB_STATUS_MESSAGE_REJECTED:
		scsicmd->result = DID_ERROR << 16;
		अवरोध;
	हाल SRB_STATUS_REQUEST_FLUSHED:
	हाल SRB_STATUS_ERROR:
	हाल SRB_STATUS_INVALID_REQUEST:
	हाल SRB_STATUS_REQUEST_SENSE_FAILED:
	हाल SRB_STATUS_NO_HBA:
	हाल SRB_STATUS_UNEXPECTED_BUS_FREE:
	हाल SRB_STATUS_PHASE_SEQUENCE_FAILURE:
	हाल SRB_STATUS_BAD_SRB_BLOCK_LENGTH:
	हाल SRB_STATUS_DELAYED_RETRY:
	हाल SRB_STATUS_BAD_FUNCTION:
	हाल SRB_STATUS_NOT_STARTED:
	हाल SRB_STATUS_NOT_IN_USE:
	हाल SRB_STATUS_FORCE_ABORT:
	हाल SRB_STATUS_DOMAIN_VALIDATION_FAIL:
	शेष:
#अगर_घोषित AAC_DETAILED_STATUS_INFO
		pr_info("aacraid: SRB ERROR(%u) %s scsi cmd 0x%x -scsi status 0x%x\n",
			le32_to_cpu(srbreply->srb_status) & 0x3F,
			aac_get_status_string(
				le32_to_cpu(srbreply->srb_status) & 0x3F),
			scsicmd->cmnd[0],
			le32_to_cpu(srbreply->scsi_status));
#पूर्ण_अगर
		/*
		 * When the CC bit is SET by the host in ATA pass thru CDB,
		 *  driver is supposed to वापस DID_OK
		 *
		 * When the CC bit is RESET by the host, driver should
		 *  वापस DID_ERROR
		 */
		अगर ((scsicmd->cmnd[0] == ATA_12)
			|| (scsicmd->cmnd[0] == ATA_16)) अणु

			अगर (scsicmd->cmnd[2] & (0x01 << 5)) अणु
				scsicmd->result = DID_OK << 16;
			पूर्ण अन्यथा अणु
				scsicmd->result = DID_ERROR << 16;
			पूर्ण
		पूर्ण अन्यथा अणु
			scsicmd->result = DID_ERROR << 16;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (le32_to_cpu(srbreply->scsi_status)
			== SAM_STAT_CHECK_CONDITION) अणु
		पूर्णांक len;

		scsicmd->result |= SAM_STAT_CHECK_CONDITION;
		len = min_t(u32, le32_to_cpu(srbreply->sense_data_size),
			    SCSI_SENSE_BUFFERSIZE);
#अगर_घोषित AAC_DETAILED_STATUS_INFO
		pr_warn("aac_srb_callback: check condition, status = %d len=%d\n",
					le32_to_cpu(srbreply->status), len);
#पूर्ण_अगर
		स_नकल(scsicmd->sense_buffer,
				srbreply->sense_data, len);
	पूर्ण

	/*
	 * OR in the scsi status (alपढ़ोy shअगरted up a bit)
	 */
	scsicmd->result |= le32_to_cpu(srbreply->scsi_status);

	aac_fib_complete(fibptr);
	scsicmd->scsi_करोne(scsicmd);
पूर्ण

अटल व्योम hba_resp_task_complete(काष्ठा aac_dev *dev,
					काष्ठा scsi_cmnd *scsicmd,
					काष्ठा aac_hba_resp *err) अणु

	scsicmd->result = err->status;
	/* set residual count */
	scsi_set_resid(scsicmd, le32_to_cpu(err->residual_count));

	चयन (err->status) अणु
	हाल SAM_STAT_GOOD:
		scsicmd->result |= DID_OK << 16;
		अवरोध;
	हाल SAM_STAT_CHECK_CONDITION:
	अणु
		पूर्णांक len;

		len = min_t(u8, err->sense_response_data_len,
			SCSI_SENSE_BUFFERSIZE);
		अगर (len)
			स_नकल(scsicmd->sense_buffer,
				err->sense_response_buf, len);
		scsicmd->result |= DID_OK << 16;
		अवरोध;
	पूर्ण
	हाल SAM_STAT_BUSY:
		scsicmd->result |= DID_BUS_BUSY << 16;
		अवरोध;
	हाल SAM_STAT_TASK_ABORTED:
		scsicmd->result |= DID_ABORT << 16;
		अवरोध;
	हाल SAM_STAT_RESERVATION_CONFLICT:
	हाल SAM_STAT_TASK_SET_FULL:
	शेष:
		scsicmd->result |= DID_ERROR << 16;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hba_resp_task_failure(काष्ठा aac_dev *dev,
					काष्ठा scsi_cmnd *scsicmd,
					काष्ठा aac_hba_resp *err)
अणु
	चयन (err->status) अणु
	हाल HBA_RESP_STAT_HBAMODE_DISABLED:
	अणु
		u32 bus, cid;

		bus = aac_logical_to_phys(scmd_channel(scsicmd));
		cid = scmd_id(scsicmd);
		अगर (dev->hba_map[bus][cid].devtype == AAC_DEVTYPE_NATIVE_RAW) अणु
			dev->hba_map[bus][cid].devtype = AAC_DEVTYPE_ARC_RAW;
			dev->hba_map[bus][cid].rmw_nexus = 0xffffffff;
		पूर्ण
		scsicmd->result = DID_NO_CONNECT << 16;
		अवरोध;
	पूर्ण
	हाल HBA_RESP_STAT_IO_ERROR:
	हाल HBA_RESP_STAT_NO_PATH_TO_DEVICE:
		scsicmd->result = DID_OK << 16 | SAM_STAT_BUSY;
		अवरोध;
	हाल HBA_RESP_STAT_IO_ABORTED:
		scsicmd->result = DID_ABORT << 16;
		अवरोध;
	हाल HBA_RESP_STAT_INVALID_DEVICE:
		scsicmd->result = DID_NO_CONNECT << 16;
		अवरोध;
	हाल HBA_RESP_STAT_UNDERRUN:
		/* UNDERRUN is OK */
		scsicmd->result = DID_OK << 16;
		अवरोध;
	हाल HBA_RESP_STAT_OVERRUN:
	शेष:
		scsicmd->result = DID_ERROR << 16;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * aac_hba_callback
 * @context: the context set in the fib - here it is scsi cmd
 * @fibptr: poपूर्णांकer to the fib
 *
 * Handles the completion of a native HBA scsi command
 */
व्योम aac_hba_callback(व्योम *context, काष्ठा fib *fibptr)
अणु
	काष्ठा aac_dev *dev;
	काष्ठा scsi_cmnd *scsicmd;

	काष्ठा aac_hba_resp *err =
			&((काष्ठा aac_native_hba *)fibptr->hw_fib_va)->resp.err;

	scsicmd = (काष्ठा scsi_cmnd *) context;

	अगर (!aac_valid_context(scsicmd, fibptr))
		वापस;

	WARN_ON(fibptr == शून्य);
	dev = fibptr->dev;

	अगर (!(fibptr->flags & FIB_CONTEXT_FLAG_NATIVE_HBA_TMF))
		scsi_dma_unmap(scsicmd);

	अगर (fibptr->flags & FIB_CONTEXT_FLAG_FASTRESP) अणु
		/* fast response */
		scsicmd->result = DID_OK << 16;
		जाओ out;
	पूर्ण

	चयन (err->service_response) अणु
	हाल HBA_RESP_SVCRES_TASK_COMPLETE:
		hba_resp_task_complete(dev, scsicmd, err);
		अवरोध;
	हाल HBA_RESP_SVCRES_FAILURE:
		hba_resp_task_failure(dev, scsicmd, err);
		अवरोध;
	हाल HBA_RESP_SVCRES_TMF_REJECTED:
		scsicmd->result = DID_ERROR << 16;
		अवरोध;
	हाल HBA_RESP_SVCRES_TMF_LUN_INVALID:
		scsicmd->result = DID_NO_CONNECT << 16;
		अवरोध;
	हाल HBA_RESP_SVCRES_TMF_COMPLETE:
	हाल HBA_RESP_SVCRES_TMF_SUCCEEDED:
		scsicmd->result = DID_OK << 16;
		अवरोध;
	शेष:
		scsicmd->result = DID_ERROR << 16;
		अवरोध;
	पूर्ण

out:
	aac_fib_complete(fibptr);

	अगर (fibptr->flags & FIB_CONTEXT_FLAG_NATIVE_HBA_TMF)
		scsicmd->SCp.sent_command = 1;
	अन्यथा
		scsicmd->scsi_करोne(scsicmd);
पूर्ण

/**
 * aac_send_srb_fib
 * @scsicmd: the scsi command block
 *
 * This routine will क्रमm a FIB and fill in the aac_srb from the
 * scsicmd passed in.
 */
अटल पूर्णांक aac_send_srb_fib(काष्ठा scsi_cmnd* scsicmd)
अणु
	काष्ठा fib* cmd_fibcontext;
	काष्ठा aac_dev* dev;
	पूर्णांक status;

	dev = (काष्ठा aac_dev *)scsicmd->device->host->hostdata;
	अगर (scmd_id(scsicmd) >= dev->maximum_num_physicals ||
			scsicmd->device->lun > 7) अणु
		scsicmd->result = DID_NO_CONNECT << 16;
		scsicmd->scsi_करोne(scsicmd);
		वापस 0;
	पूर्ण

	/*
	 *	Allocate and initialize a Fib then setup a BlockWrite command
	 */
	cmd_fibcontext = aac_fib_alloc_tag(dev, scsicmd);
	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;
	status = aac_adapter_scsi(cmd_fibcontext, scsicmd);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	prपूर्णांकk(KERN_WARNING "aac_srb: aac_fib_send failed with status: %d\n", status);
	aac_fib_complete(cmd_fibcontext);
	aac_fib_मुक्त(cmd_fibcontext);

	वापस -1;
पूर्ण

/**
 * aac_send_hba_fib
 * @scsicmd: the scsi command block
 *
 * This routine will क्रमm a FIB and fill in the aac_hba_cmd_req from the
 * scsicmd passed in.
 */
अटल पूर्णांक aac_send_hba_fib(काष्ठा scsi_cmnd *scsicmd)
अणु
	काष्ठा fib *cmd_fibcontext;
	काष्ठा aac_dev *dev;
	पूर्णांक status;

	dev = shost_priv(scsicmd->device->host);
	अगर (scmd_id(scsicmd) >= dev->maximum_num_physicals ||
			scsicmd->device->lun > AAC_MAX_LUN - 1) अणु
		scsicmd->result = DID_NO_CONNECT << 16;
		scsicmd->scsi_करोne(scsicmd);
		वापस 0;
	पूर्ण

	/*
	 *	Allocate and initialize a Fib then setup a BlockWrite command
	 */
	cmd_fibcontext = aac_fib_alloc_tag(dev, scsicmd);
	अगर (!cmd_fibcontext)
		वापस -1;

	scsicmd->SCp.phase = AAC_OWNER_FIRMWARE;
	status = aac_adapter_hba(cmd_fibcontext, scsicmd);

	/*
	 *	Check that the command queued to the controller
	 */
	अगर (status == -EINPROGRESS)
		वापस 0;

	pr_warn("aac_hba_cmd_req: aac_fib_send failed with status: %d\n",
		status);
	aac_fib_complete(cmd_fibcontext);
	aac_fib_मुक्त(cmd_fibcontext);

	वापस -1;
पूर्ण


अटल दीर्घ aac_build_sg(काष्ठा scsi_cmnd *scsicmd, काष्ठा sgmap *psg)
अणु
	अचिन्हित दीर्घ byte_count = 0;
	पूर्णांक nseg;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	// Get rid of old data
	psg->count = 0;
	psg->sg[0].addr = 0;
	psg->sg[0].count = 0;

	nseg = scsi_dma_map(scsicmd);
	अगर (nseg <= 0)
		वापस nseg;

	psg->count = cpu_to_le32(nseg);

	scsi_क्रम_each_sg(scsicmd, sg, nseg, i) अणु
		psg->sg[i].addr = cpu_to_le32(sg_dma_address(sg));
		psg->sg[i].count = cpu_to_le32(sg_dma_len(sg));
		byte_count += sg_dma_len(sg);
	पूर्ण
	/* hba wants the size to be exact */
	अगर (byte_count > scsi_bufflen(scsicmd)) अणु
		u32 temp = le32_to_cpu(psg->sg[i-1].count) -
			(byte_count - scsi_bufflen(scsicmd));
		psg->sg[i-1].count = cpu_to_le32(temp);
		byte_count = scsi_bufflen(scsicmd);
	पूर्ण
	/* Check क्रम command underflow */
	अगर (scsicmd->underflow && (byte_count < scsicmd->underflow)) अणु
		prपूर्णांकk(KERN_WARNING"aacraid: cmd len %08lX cmd underflow %08X\n",
		       byte_count, scsicmd->underflow);
	पूर्ण

	वापस byte_count;
पूर्ण


अटल दीर्घ aac_build_sg64(काष्ठा scsi_cmnd *scsicmd, काष्ठा sgmap64 *psg)
अणु
	अचिन्हित दीर्घ byte_count = 0;
	u64 addr;
	पूर्णांक nseg;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	// Get rid of old data
	psg->count = 0;
	psg->sg[0].addr[0] = 0;
	psg->sg[0].addr[1] = 0;
	psg->sg[0].count = 0;

	nseg = scsi_dma_map(scsicmd);
	अगर (nseg <= 0)
		वापस nseg;

	scsi_क्रम_each_sg(scsicmd, sg, nseg, i) अणु
		पूर्णांक count = sg_dma_len(sg);
		addr = sg_dma_address(sg);
		psg->sg[i].addr[0] = cpu_to_le32(addr & 0xffffffff);
		psg->sg[i].addr[1] = cpu_to_le32(addr>>32);
		psg->sg[i].count = cpu_to_le32(count);
		byte_count += count;
	पूर्ण
	psg->count = cpu_to_le32(nseg);
	/* hba wants the size to be exact */
	अगर (byte_count > scsi_bufflen(scsicmd)) अणु
		u32 temp = le32_to_cpu(psg->sg[i-1].count) -
			(byte_count - scsi_bufflen(scsicmd));
		psg->sg[i-1].count = cpu_to_le32(temp);
		byte_count = scsi_bufflen(scsicmd);
	पूर्ण
	/* Check क्रम command underflow */
	अगर (scsicmd->underflow && (byte_count < scsicmd->underflow)) अणु
		prपूर्णांकk(KERN_WARNING"aacraid: cmd len %08lX cmd underflow %08X\n",
		       byte_count, scsicmd->underflow);
	पूर्ण

	वापस byte_count;
पूर्ण

अटल दीर्घ aac_build_sgraw(काष्ठा scsi_cmnd *scsicmd, काष्ठा sgmapraw *psg)
अणु
	अचिन्हित दीर्घ byte_count = 0;
	पूर्णांक nseg;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	// Get rid of old data
	psg->count = 0;
	psg->sg[0].next = 0;
	psg->sg[0].prev = 0;
	psg->sg[0].addr[0] = 0;
	psg->sg[0].addr[1] = 0;
	psg->sg[0].count = 0;
	psg->sg[0].flags = 0;

	nseg = scsi_dma_map(scsicmd);
	अगर (nseg <= 0)
		वापस nseg;

	scsi_क्रम_each_sg(scsicmd, sg, nseg, i) अणु
		पूर्णांक count = sg_dma_len(sg);
		u64 addr = sg_dma_address(sg);
		psg->sg[i].next = 0;
		psg->sg[i].prev = 0;
		psg->sg[i].addr[1] = cpu_to_le32((u32)(addr>>32));
		psg->sg[i].addr[0] = cpu_to_le32((u32)(addr & 0xffffffff));
		psg->sg[i].count = cpu_to_le32(count);
		psg->sg[i].flags = 0;
		byte_count += count;
	पूर्ण
	psg->count = cpu_to_le32(nseg);
	/* hba wants the size to be exact */
	अगर (byte_count > scsi_bufflen(scsicmd)) अणु
		u32 temp = le32_to_cpu(psg->sg[i-1].count) -
			(byte_count - scsi_bufflen(scsicmd));
		psg->sg[i-1].count = cpu_to_le32(temp);
		byte_count = scsi_bufflen(scsicmd);
	पूर्ण
	/* Check क्रम command underflow */
	अगर (scsicmd->underflow && (byte_count < scsicmd->underflow)) अणु
		prपूर्णांकk(KERN_WARNING"aacraid: cmd len %08lX cmd underflow %08X\n",
		       byte_count, scsicmd->underflow);
	पूर्ण

	वापस byte_count;
पूर्ण

अटल दीर्घ aac_build_sgraw2(काष्ठा scsi_cmnd *scsicmd,
				काष्ठा aac_raw_io2 *rio2, पूर्णांक sg_max)
अणु
	अचिन्हित दीर्घ byte_count = 0;
	पूर्णांक nseg;
	काष्ठा scatterlist *sg;
	पूर्णांक i, conक्रमmable = 0;
	u32 min_size = PAGE_SIZE, cur_size;

	nseg = scsi_dma_map(scsicmd);
	अगर (nseg <= 0)
		वापस nseg;

	scsi_क्रम_each_sg(scsicmd, sg, nseg, i) अणु
		पूर्णांक count = sg_dma_len(sg);
		u64 addr = sg_dma_address(sg);

		BUG_ON(i >= sg_max);
		rio2->sge[i].addrHigh = cpu_to_le32((u32)(addr>>32));
		rio2->sge[i].addrLow = cpu_to_le32((u32)(addr & 0xffffffff));
		cur_size = cpu_to_le32(count);
		rio2->sge[i].length = cur_size;
		rio2->sge[i].flags = 0;
		अगर (i == 0) अणु
			conक्रमmable = 1;
			rio2->sgeFirstSize = cur_size;
		पूर्ण अन्यथा अगर (i == 1) अणु
			rio2->sgeNominalSize = cur_size;
			min_size = cur_size;
		पूर्ण अन्यथा अगर ((i+1) < nseg && cur_size != rio2->sgeNominalSize) अणु
			conक्रमmable = 0;
			अगर (cur_size < min_size)
				min_size = cur_size;
		पूर्ण
		byte_count += count;
	पूर्ण

	/* hba wants the size to be exact */
	अगर (byte_count > scsi_bufflen(scsicmd)) अणु
		u32 temp = le32_to_cpu(rio2->sge[i-1].length) -
			(byte_count - scsi_bufflen(scsicmd));
		rio2->sge[i-1].length = cpu_to_le32(temp);
		byte_count = scsi_bufflen(scsicmd);
	पूर्ण

	rio2->sgeCnt = cpu_to_le32(nseg);
	rio2->flags |= cpu_to_le16(RIO2_SG_FORMAT_IEEE1212);
	/* not conक्रमmable: evaluate required sg elements */
	अगर (!conक्रमmable) अणु
		पूर्णांक j, nseg_new = nseg, err_found;
		क्रम (i = min_size / PAGE_SIZE; i >= 1; --i) अणु
			err_found = 0;
			nseg_new = 2;
			क्रम (j = 1; j < nseg - 1; ++j) अणु
				अगर (rio2->sge[j].length % (i*PAGE_SIZE)) अणु
					err_found = 1;
					अवरोध;
				पूर्ण
				nseg_new += (rio2->sge[j].length / (i*PAGE_SIZE));
			पूर्ण
			अगर (!err_found)
				अवरोध;
		पूर्ण
		अगर (i > 0 && nseg_new <= sg_max) अणु
			पूर्णांक ret = aac_convert_sgraw2(rio2, i, nseg, nseg_new);

			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा
		rio2->flags |= cpu_to_le16(RIO2_SGL_CONFORMANT);

	/* Check क्रम command underflow */
	अगर (scsicmd->underflow && (byte_count < scsicmd->underflow)) अणु
		prपूर्णांकk(KERN_WARNING"aacraid: cmd len %08lX cmd underflow %08X\n",
		       byte_count, scsicmd->underflow);
	पूर्ण

	वापस byte_count;
पूर्ण

अटल पूर्णांक aac_convert_sgraw2(काष्ठा aac_raw_io2 *rio2, पूर्णांक pages, पूर्णांक nseg, पूर्णांक nseg_new)
अणु
	काष्ठा sge_ieee1212 *sge;
	पूर्णांक i, j, pos;
	u32 addr_low;

	अगर (aac_convert_sgl == 0)
		वापस 0;

	sge = kदो_स्मृति_array(nseg_new, माप(काष्ठा sge_ieee1212), GFP_ATOMIC);
	अगर (sge == शून्य)
		वापस -ENOMEM;

	क्रम (i = 1, pos = 1; i < nseg-1; ++i) अणु
		क्रम (j = 0; j < rio2->sge[i].length / (pages * PAGE_SIZE); ++j) अणु
			addr_low = rio2->sge[i].addrLow + j * pages * PAGE_SIZE;
			sge[pos].addrLow = addr_low;
			sge[pos].addrHigh = rio2->sge[i].addrHigh;
			अगर (addr_low < rio2->sge[i].addrLow)
				sge[pos].addrHigh++;
			sge[pos].length = pages * PAGE_SIZE;
			sge[pos].flags = 0;
			pos++;
		पूर्ण
	पूर्ण
	sge[pos] = rio2->sge[nseg-1];
	स_नकल(&rio2->sge[1], &sge[1], (nseg_new-1)*माप(काष्ठा sge_ieee1212));

	kमुक्त(sge);
	rio2->sgeCnt = cpu_to_le32(nseg_new);
	rio2->flags |= cpu_to_le16(RIO2_SGL_CONFORMANT);
	rio2->sgeNominalSize = pages * PAGE_SIZE;
	वापस 0;
पूर्ण

अटल दीर्घ aac_build_sghba(काष्ठा scsi_cmnd *scsicmd,
			काष्ठा aac_hba_cmd_req *hbacmd,
			पूर्णांक sg_max,
			u64 sg_address)
अणु
	अचिन्हित दीर्घ byte_count = 0;
	पूर्णांक nseg;
	काष्ठा scatterlist *sg;
	पूर्णांक i;
	u32 cur_size;
	काष्ठा aac_hba_sgl *sge;

	nseg = scsi_dma_map(scsicmd);
	अगर (nseg <= 0) अणु
		byte_count = nseg;
		जाओ out;
	पूर्ण

	अगर (nseg > HBA_MAX_SG_EMBEDDED)
		sge = &hbacmd->sge[2];
	अन्यथा
		sge = &hbacmd->sge[0];

	scsi_क्रम_each_sg(scsicmd, sg, nseg, i) अणु
		पूर्णांक count = sg_dma_len(sg);
		u64 addr = sg_dma_address(sg);

		WARN_ON(i >= sg_max);
		sge->addr_hi = cpu_to_le32((u32)(addr>>32));
		sge->addr_lo = cpu_to_le32((u32)(addr & 0xffffffff));
		cur_size = cpu_to_le32(count);
		sge->len = cur_size;
		sge->flags = 0;
		byte_count += count;
		sge++;
	पूर्ण

	sge--;
	/* hba wants the size to be exact */
	अगर (byte_count > scsi_bufflen(scsicmd)) अणु
		u32 temp;

		temp = le32_to_cpu(sge->len) - byte_count
						- scsi_bufflen(scsicmd);
		sge->len = cpu_to_le32(temp);
		byte_count = scsi_bufflen(scsicmd);
	पूर्ण

	अगर (nseg <= HBA_MAX_SG_EMBEDDED) अणु
		hbacmd->emb_data_desc_count = cpu_to_le32(nseg);
		sge->flags = cpu_to_le32(0x40000000);
	पूर्ण अन्यथा अणु
		/* not embedded */
		hbacmd->sge[0].flags = cpu_to_le32(0x80000000);
		hbacmd->emb_data_desc_count = (u8)cpu_to_le32(1);
		hbacmd->sge[0].addr_hi = (u32)cpu_to_le32(sg_address >> 32);
		hbacmd->sge[0].addr_lo =
			cpu_to_le32((u32)(sg_address & 0xffffffff));
	पूर्ण

	/* Check क्रम command underflow */
	अगर (scsicmd->underflow && (byte_count < scsicmd->underflow)) अणु
		pr_warn("aacraid: cmd len %08lX cmd underflow %08X\n",
				byte_count, scsicmd->underflow);
	पूर्ण
out:
	वापस byte_count;
पूर्ण

#अगर_घोषित AAC_DETAILED_STATUS_INFO

काष्ठा aac_srb_status_info अणु
	u32	status;
	अक्षर	*str;
पूर्ण;


अटल काष्ठा aac_srb_status_info srb_status_info[] = अणु
	अणु SRB_STATUS_PENDING,		"Pending Status"पूर्ण,
	अणु SRB_STATUS_SUCCESS,		"Success"पूर्ण,
	अणु SRB_STATUS_ABORTED,		"Aborted Command"पूर्ण,
	अणु SRB_STATUS_ABORT_FAILED,	"Abort Failed"पूर्ण,
	अणु SRB_STATUS_ERROR,		"Error Event"पूर्ण,
	अणु SRB_STATUS_BUSY,		"Device Busy"पूर्ण,
	अणु SRB_STATUS_INVALID_REQUEST,	"Invalid Request"पूर्ण,
	अणु SRB_STATUS_INVALID_PATH_ID,	"Invalid Path ID"पूर्ण,
	अणु SRB_STATUS_NO_DEVICE,		"No Device"पूर्ण,
	अणु SRB_STATUS_TIMEOUT,		"Timeout"पूर्ण,
	अणु SRB_STATUS_SELECTION_TIMEOUT,	"Selection Timeout"पूर्ण,
	अणु SRB_STATUS_COMMAND_TIMEOUT,	"Command Timeout"पूर्ण,
	अणु SRB_STATUS_MESSAGE_REJECTED,	"Message Rejected"पूर्ण,
	अणु SRB_STATUS_BUS_RESET,		"Bus Reset"पूर्ण,
	अणु SRB_STATUS_PARITY_ERROR,	"Parity Error"पूर्ण,
	अणु SRB_STATUS_REQUEST_SENSE_FAILED,"Request Sense Failed"पूर्ण,
	अणु SRB_STATUS_NO_HBA,		"No HBA"पूर्ण,
	अणु SRB_STATUS_DATA_OVERRUN,	"Data Overrun/Data Underrun"पूर्ण,
	अणु SRB_STATUS_UNEXPECTED_BUS_FREE,"Unexpected Bus Free"पूर्ण,
	अणु SRB_STATUS_PHASE_SEQUENCE_FAILURE,"Phase Error"पूर्ण,
	अणु SRB_STATUS_BAD_SRB_BLOCK_LENGTH,"Bad Srb Block Length"पूर्ण,
	अणु SRB_STATUS_REQUEST_FLUSHED,	"Request Flushed"पूर्ण,
	अणु SRB_STATUS_DELAYED_RETRY,	"Delayed Retry"पूर्ण,
	अणु SRB_STATUS_INVALID_LUN,	"Invalid LUN"पूर्ण,
	अणु SRB_STATUS_INVALID_TARGET_ID,	"Invalid TARGET ID"पूर्ण,
	अणु SRB_STATUS_BAD_FUNCTION,	"Bad Function"पूर्ण,
	अणु SRB_STATUS_ERROR_RECOVERY,	"Error Recovery"पूर्ण,
	अणु SRB_STATUS_NOT_STARTED,	"Not Started"पूर्ण,
	अणु SRB_STATUS_NOT_IN_USE,	"Not In Use"पूर्ण,
	अणु SRB_STATUS_FORCE_ABORT,	"Force Abort"पूर्ण,
	अणु SRB_STATUS_DOMAIN_VALIDATION_FAIL,"Domain Validation Failure"पूर्ण,
	अणु 0xff,				"Unknown Error"पूर्ण
पूर्ण;

अक्षर *aac_get_status_string(u32 status)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(srb_status_info); i++)
		अगर (srb_status_info[i].status == status)
			वापस srb_status_info[i].str;

	वापस "Bad Status Code";
पूर्ण

#पूर्ण_अगर
