<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Adaptec AAC series RAID controller driver
 *	(c) Copyright 2001 Red Hat Inc.	<alan@redhat.com>
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver क्रम Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Sierra, Inc. (aacraid@pmc-sierra.com)
 *		 2016-2017 Microsemi Corp. (aacraid@microsemi.com)
 *
 * Module Name:
 *  aacraid.h
 *
 * Abstract: Contains all routines क्रम control of the aacraid driver
 */

#अगर_अघोषित _AACRAID_H_
#घोषणा _AACRAID_H_
#अगर_अघोषित dprपूर्णांकk
# define dprपूर्णांकk(x)
#पूर्ण_अगर
/* eg: अगर (nblank(dprपूर्णांकk(x))) */
#घोषणा _nblank(x) #x
#घोषणा nblank(x) _nblank(x)[0]

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/pci.h>
#समावेश <scsi/scsi_host.h>

/*------------------------------------------------------------------------------
 *              D E F I N E S
 *----------------------------------------------------------------------------*/

#घोषणा AAC_MAX_MSIX		32	/* vectors */
#घोषणा AAC_PCI_MSI_ENABLE	0x8000

क्रमागत अणु
	AAC_ENABLE_INTERRUPT	= 0x0,
	AAC_DISABLE_INTERRUPT,
	AAC_ENABLE_MSIX,
	AAC_DISABLE_MSIX,
	AAC_CLEAR_AIF_BIT,
	AAC_CLEAR_SYNC_BIT,
	AAC_ENABLE_INTX
पूर्ण;

#घोषणा AAC_INT_MODE_INTX		(1<<0)
#घोषणा AAC_INT_MODE_MSI		(1<<1)
#घोषणा AAC_INT_MODE_AIF		(1<<2)
#घोषणा AAC_INT_MODE_SYNC		(1<<3)
#घोषणा AAC_INT_MODE_MSIX		(1<<16)

#घोषणा AAC_INT_ENABLE_TYPE1_INTX	0xfffffffb
#घोषणा AAC_INT_ENABLE_TYPE1_MSIX	0xfffffffa
#घोषणा AAC_INT_DISABLE_ALL		0xffffffff

/* Bit definitions in IOA->Host Interrupt Register */
#घोषणा PMC_TRANSITION_TO_OPERATIONAL	(1<<31)
#घोषणा PMC_IOARCB_TRANSFER_FAILED	(1<<28)
#घोषणा PMC_IOA_UNIT_CHECK		(1<<27)
#घोषणा PMC_NO_HOST_RRQ_FOR_CMD_RESPONSE (1<<26)
#घोषणा PMC_CRITICAL_IOA_OP_IN_PROGRESS	(1<<25)
#घोषणा PMC_IOARRIN_LOST		(1<<4)
#घोषणा PMC_SYSTEM_BUS_MMIO_ERROR	(1<<3)
#घोषणा PMC_IOA_PROCESSOR_IN_ERROR_STATE (1<<2)
#घोषणा PMC_HOST_RRQ_VALID		(1<<1)
#घोषणा PMC_OPERATIONAL_STATUS		(1<<31)
#घोषणा PMC_ALLOW_MSIX_VECTOR0		(1<<0)

#घोषणा PMC_IOA_ERROR_INTERRUPTS	(PMC_IOARCB_TRANSFER_FAILED | \
					 PMC_IOA_UNIT_CHECK | \
					 PMC_NO_HOST_RRQ_FOR_CMD_RESPONSE | \
					 PMC_IOARRIN_LOST | \
					 PMC_SYSTEM_BUS_MMIO_ERROR | \
					 PMC_IOA_PROCESSOR_IN_ERROR_STATE)

#घोषणा PMC_ALL_INTERRUPT_BITS		(PMC_IOA_ERROR_INTERRUPTS | \
					 PMC_HOST_RRQ_VALID | \
					 PMC_TRANSITION_TO_OPERATIONAL | \
					 PMC_ALLOW_MSIX_VECTOR0)
#घोषणा	PMC_GLOBAL_INT_BIT2		0x00000004
#घोषणा	PMC_GLOBAL_INT_BIT0		0x00000001

#अगर_अघोषित AAC_DRIVER_BUILD
# define AAC_DRIVER_BUILD 50983
# define AAC_DRIVER_BRANCH "-custom"
#पूर्ण_अगर
#घोषणा MAXIMUM_NUM_CONTAINERS	32

#घोषणा AAC_NUM_MGT_FIB         8
#घोषणा AAC_NUM_IO_FIB		(1024 - AAC_NUM_MGT_FIB)
#घोषणा AAC_NUM_FIB		(AAC_NUM_IO_FIB + AAC_NUM_MGT_FIB)

#घोषणा AAC_MAX_LUN		256

#घोषणा AAC_MAX_HOSTPHYSMEMPAGES (0xfffff)
#घोषणा AAC_MAX_32BIT_SGBCOUNT	((अचिन्हित लघु)256)

#घोषणा AAC_DEBUG_INSTRUMENT_AIF_DELETE

#घोषणा AAC_MAX_NATIVE_TARGETS		1024
/* Thor: 5 phys. buses: #0: empty, 1-4: 256 tarमाला_लो each */
#घोषणा AAC_MAX_BUSES			5
#घोषणा AAC_MAX_TARGETS		256
#घोषणा AAC_BUS_TARGET_LOOP		(AAC_MAX_BUSES * AAC_MAX_TARGETS)
#घोषणा AAC_MAX_NATIVE_SIZE		2048
#घोषणा FW_ERROR_BUFFER_SIZE		512
#घोषणा AAC_SA_TIMEOUT			180
#घोषणा AAC_ARC_TIMEOUT			60

#घोषणा get_bus_number(x)	(x/AAC_MAX_TARGETS)
#घोषणा get_target_number(x)	(x%AAC_MAX_TARGETS)

/* Thor AIF events */
#घोषणा SA_AIF_HOTPLUG			(1<<1)
#घोषणा SA_AIF_HARDWARE		(1<<2)
#घोषणा SA_AIF_PDEV_CHANGE		(1<<4)
#घोषणा SA_AIF_LDEV_CHANGE		(1<<5)
#घोषणा SA_AIF_BPSTAT_CHANGE		(1<<30)
#घोषणा SA_AIF_BPCFG_CHANGE		(1<<31)

#घोषणा HBA_MAX_SG_EMBEDDED		28
#घोषणा HBA_MAX_SG_SEPARATE		90
#घोषणा HBA_SENSE_DATA_LEN_MAX		32
#घोषणा HBA_REQUEST_TAG_ERROR_FLAG	0x00000002
#घोषणा HBA_SGL_FLAGS_EXT		0x80000000UL

काष्ठा aac_hba_sgl अणु
	u32		addr_lo; /* Lower 32-bits of SGL element address */
	u32		addr_hi; /* Upper 32-bits of SGL element address */
	u32		len;	/* Length of SGL element in bytes */
	u32		flags;	/* SGL element flags */
पूर्ण;

क्रमागत अणु
	HBA_IU_TYPE_SCSI_CMD_REQ		= 0x40,
	HBA_IU_TYPE_SCSI_TM_REQ			= 0x41,
	HBA_IU_TYPE_SATA_REQ			= 0x42,
	HBA_IU_TYPE_RESP			= 0x60,
	HBA_IU_TYPE_COALESCED_RESP		= 0x61,
	HBA_IU_TYPE_INT_COALESCING_CFG_REQ	= 0x70
पूर्ण;

क्रमागत अणु
	HBA_CMD_BYTE1_DATA_सूची_IN		= 0x1,
	HBA_CMD_BYTE1_DATA_सूची_OUT		= 0x2,
	HBA_CMD_BYTE1_DATA_TYPE_DDR		= 0x4,
	HBA_CMD_BYTE1_CRYPTO_ENABLE		= 0x8
पूर्ण;

क्रमागत अणु
	HBA_CMD_BYTE1_BITOFF_DATA_सूची_IN	= 0x0,
	HBA_CMD_BYTE1_BITOFF_DATA_सूची_OUT,
	HBA_CMD_BYTE1_BITOFF_DATA_TYPE_DDR,
	HBA_CMD_BYTE1_BITOFF_CRYPTO_ENABLE
पूर्ण;

क्रमागत अणु
	HBA_RESP_DATAPRES_NO_DATA		= 0x0,
	HBA_RESP_DATAPRES_RESPONSE_DATA,
	HBA_RESP_DATAPRES_SENSE_DATA
पूर्ण;

क्रमागत अणु
	HBA_RESP_SVCRES_TASK_COMPLETE		= 0x0,
	HBA_RESP_SVCRES_FAILURE,
	HBA_RESP_SVCRES_TMF_COMPLETE,
	HBA_RESP_SVCRES_TMF_SUCCEEDED,
	HBA_RESP_SVCRES_TMF_REJECTED,
	HBA_RESP_SVCRES_TMF_LUN_INVALID
पूर्ण;

क्रमागत अणु
	HBA_RESP_STAT_IO_ERROR			= 0x1,
	HBA_RESP_STAT_IO_ABORTED,
	HBA_RESP_STAT_NO_PATH_TO_DEVICE,
	HBA_RESP_STAT_INVALID_DEVICE,
	HBA_RESP_STAT_HBAMODE_DISABLED		= 0xE,
	HBA_RESP_STAT_UNDERRUN			= 0x51,
	HBA_RESP_STAT_OVERRUN			= 0x75
पूर्ण;

काष्ठा aac_hba_cmd_req अणु
	u8	iu_type;	/* HBA inक्रमmation unit type */
	/*
	 * byte1:
	 * [1:0] सूची - 0=No data, 0x1 = IN, 0x2 = OUT
	 * [2]   TYPE - 0=PCI, 1=DDR
	 * [3]   CRYPTO_ENABLE - 0=Crypto disabled, 1=Crypto enabled
	 */
	u8	byte1;
	u8	reply_qid;	/* Host reply queue to post response to */
	u8	reserved1;
	__le32	it_nexus;	/* Device handle क्रम the request */
	__le32	request_id;	/* Sender context */
	/* Lower 32-bits of tweak value क्रम crypto enabled IOs */
	__le32	tweak_value_lo;
	u8	cdb[16];	/* SCSI CDB of the command */
	u8	lun[8];		/* SCSI LUN of the command */

	/* Total data length in bytes to be पढ़ो/written (अगर any) */
	__le32	data_length;

	/* [2:0] Task Attribute, [6:3] Command Priority */
	u8	attr_prio;

	/* Number of SGL elements embedded in the HBA req */
	u8	emb_data_desc_count;

	__le16	dek_index;	/* DEK index क्रम crypto enabled IOs */

	/* Lower 32-bits of reserved error data target location on the host */
	__le32	error_ptr_lo;

	/* Upper 32-bits of reserved error data target location on the host */
	__le32	error_ptr_hi;

	/* Length of reserved error data area on the host in bytes */
	__le32	error_length;

	/* Upper 32-bits of tweak value क्रम crypto enabled IOs */
	__le32	tweak_value_hi;

	काष्ठा aac_hba_sgl sge[HBA_MAX_SG_SEPARATE+2]; /* SG list space */

	/*
	 * काष्ठाure must not exceed
	 * AAC_MAX_NATIVE_SIZE-FW_ERROR_BUFFER_SIZE
	 */
पूर्ण;

/* Task Management Functions (TMF) */
#घोषणा HBA_TMF_ABORT_TASK	0x01
#घोषणा HBA_TMF_LUN_RESET	0x08

काष्ठा aac_hba_पंचांग_req अणु
	u8	iu_type;	/* HBA inक्रमmation unit type */
	u8	reply_qid;	/* Host reply queue to post response to */
	u8	पंचांगf;		/* Task management function */
	u8	reserved1;

	__le32	it_nexus;	/* Device handle क्रम the command */

	u8	lun[8];		/* SCSI LUN */

	/* Used to hold sender context. */
	__le32	request_id;	/* Sender context */
	__le32	reserved2;

	/* Request identअगरier of managed task */
	__le32	managed_request_id;	/* Sender context being managed */
	__le32	reserved3;

	/* Lower 32-bits of reserved error data target location on the host */
	__le32	error_ptr_lo;
	/* Upper 32-bits of reserved error data target location on the host */
	__le32	error_ptr_hi;
	/* Length of reserved error data area on the host in bytes */
	__le32	error_length;
पूर्ण;

काष्ठा aac_hba_reset_req अणु
	u8	iu_type;	/* HBA inक्रमmation unit type */
	/* 0 - reset specअगरied device, 1 - reset all devices */
	u8	reset_type;
	u8	reply_qid;	/* Host reply queue to post response to */
	u8	reserved1;

	__le32	it_nexus;	/* Device handle क्रम the command */
	__le32	request_id;	/* Sender context */
	/* Lower 32-bits of reserved error data target location on the host */
	__le32	error_ptr_lo;
	/* Upper 32-bits of reserved error data target location on the host */
	__le32	error_ptr_hi;
	/* Length of reserved error data area on the host in bytes */
	__le32	error_length;
पूर्ण;

काष्ठा aac_hba_resp अणु
	u8	iu_type;		/* HBA inक्रमmation unit type */
	u8	reserved1[3];
	__le32	request_identअगरier;	/* sender context */
	__le32	reserved2;
	u8	service_response;	/* SCSI service response */
	u8	status;			/* SCSI status */
	u8	datapres;	/* [1:0] - data present, [7:2] - reserved */
	u8	sense_response_data_len;	/* Sense/response data length */
	__le32	residual_count;		/* Residual data length in bytes */
	/* Sense/response data */
	u8	sense_response_buf[HBA_SENSE_DATA_LEN_MAX];
पूर्ण;

काष्ठा aac_native_hba अणु
	जोड़ अणु
		काष्ठा aac_hba_cmd_req cmd;
		काष्ठा aac_hba_पंचांग_req पंचांगr;
		u8 cmd_bytes[AAC_MAX_NATIVE_SIZE-FW_ERROR_BUFFER_SIZE];
	पूर्ण cmd;
	जोड़ अणु
		काष्ठा aac_hba_resp err;
		u8 resp_bytes[FW_ERROR_BUFFER_SIZE];
	पूर्ण resp;
पूर्ण;

#घोषणा CISS_REPORT_PHYSICAL_LUNS	0xc3
#घोषणा WRITE_HOST_WELLNESS		0xa5
#घोषणा CISS_IDENTIFY_PHYSICAL_DEVICE	0x15
#घोषणा BMIC_IN			0x26
#घोषणा BMIC_OUT			0x27

काष्ठा aac_ciss_phys_luns_resp अणु
	u8	list_length[4];		/* LUN list length (N-7, big endian) */
	u8	resp_flag;		/* extended response_flag */
	u8	reserved[3];
	काष्ठा _ciss_lun अणु
		u8	tid[3];		/* Target ID */
		u8	bus;		/* Bus, flag (bits 6,7) */
		u8	level3[2];
		u8	level2[2];
		u8	node_ident[16];	/* phys. node identअगरier */
	पूर्ण lun[1];			/* List of phys. devices */
पूर्ण;

/*
 * Interrupts
 */
#घोषणा AAC_MAX_HRRQ		64

काष्ठा aac_ciss_identअगरy_pd अणु
	u8 scsi_bus;			/* SCSI Bus number on controller */
	u8 scsi_id;			/* SCSI ID on this bus */
	u16 block_size;			/* sector size in bytes */
	u32 total_blocks;		/* number क्रम sectors on drive */
	u32 reserved_blocks;		/* controller reserved (RIS) */
	u8 model[40];			/* Physical Drive Model */
	u8 serial_number[40];		/* Drive Serial Number */
	u8 firmware_revision[8];	/* drive firmware revision */
	u8 scsi_inquiry_bits;		/* inquiry byte 7 bits */
	u8 compaq_drive_stamp;		/* 0 means drive not stamped */
	u8 last_failure_reason;

	u8  flags;
	u8  more_flags;
	u8  scsi_lun;			/* SCSI LUN क्रम phys drive */
	u8  yet_more_flags;
	u8  even_more_flags;
	u32 spi_speed_rules;		/* SPI Speed :Ultra disable diagnose */
	u8  phys_connector[2];		/* connector number on controller */
	u8  phys_box_on_bus;		/* phys enclosure this drive resides */
	u8  phys_bay_in_box;		/* phys drv bay this drive resides */
	u32 rpm;			/* Drive rotational speed in rpm */
	u8  device_type;		/* type of drive */
	u8  sata_version;		/* only valid when drive_type is SATA */
	u64 big_total_block_count;
	u64 ris_starting_lba;
	u32 ris_size;
	u8  wwid[20];
	u8  controller_phy_map[32];
	u16 phy_count;
	u8  phy_connected_dev_type[256];
	u8  phy_to_drive_bay_num[256];
	u16 phy_to_attached_dev_index[256];
	u8  box_index;
	u8  spitfire_support;
	u16 extra_physical_drive_flags;
	u8  negotiated_link_rate[256];
	u8  phy_to_phy_map[256];
	u8  redundant_path_present_map;
	u8  redundant_path_failure_map;
	u8  active_path_number;
	u16 alternate_paths_phys_connector[8];
	u8  alternate_paths_phys_box_on_port[8];
	u8  multi_lun_device_lun_count;
	u8  minimum_good_fw_revision[8];
	u8  unique_inquiry_bytes[20];
	u8  current_temperature_degreesC;
	u8  temperature_threshold_degreesC;
	u8  max_temperature_degreesC;
	u8  logical_blocks_per_phys_block_exp;	/* phyblocksize = 512 * 2^exp */
	u16 current_queue_depth_limit;
	u8  चयन_name[10];
	u16 चयन_port;
	u8  alternate_paths_चयन_name[40];
	u8  alternate_paths_चयन_port[8];
	u16 घातer_on_hours;		/* valid only अगर gas gauge supported */
	u16 percent_endurance_used;	/* valid only अगर gas gauge supported. */
	u8  drive_authentication;
	u8  smart_carrier_authentication;
	u8  smart_carrier_app_fw_version;
	u8  smart_carrier_bootloader_fw_version;
	u8  SanitizeSecureEraseSupport;
	u8  DriveKeyFlags;
	u8  encryption_key_name[64];
	u32 misc_drive_flags;
	u16 dek_index;
	u16 drive_encryption_flags;
	u8  sanitize_maximum_समय[6];
	u8  connector_info_mode;
	u8  connector_info_number[4];
	u8  दीर्घ_connector_name[64];
	u8  device_unique_identअगरier[16];
	u8  padto_2K[17];
पूर्ण __packed;

/*
 * These macros convert from physical channels to भव channels
 */
#घोषणा CONTAINER_CHANNEL		(0)
#घोषणा NATIVE_CHANNEL			(1)
#घोषणा CONTAINER_TO_CHANNEL(cont)	(CONTAINER_CHANNEL)
#घोषणा CONTAINER_TO_ID(cont)		(cont)
#घोषणा CONTAINER_TO_LUN(cont)		(0)
#घोषणा ENCLOSURE_CHANNEL		(3)

#घोषणा PMC_DEVICE_S6	0x28b
#घोषणा PMC_DEVICE_S7	0x28c
#घोषणा PMC_DEVICE_S8	0x28d

#घोषणा aac_phys_to_logical(x)  ((x)+1)
#घोषणा aac_logical_to_phys(x)  ((x)?(x)-1:0)

/*
 * These macros are क्रम keeping track of
 * अक्षरacter device state.
 */
#घोषणा AAC_CHARDEV_UNREGISTERED	(-1)
#घोषणा AAC_CHARDEV_NEEDS_REINIT	(-2)

/* #घोषणा AAC_DETAILED_STATUS_INFO */

काष्ठा diskparm
अणु
	पूर्णांक heads;
	पूर्णांक sectors;
	पूर्णांक cylinders;
पूर्ण;


/*
 *	Firmware स्थिरants
 */

#घोषणा		CT_NONE			0
#घोषणा		CT_OK			218
#घोषणा		FT_खाताSYS	8	/* ADAPTEC's "FSA"(पंचांग) fileप्रणाली */
#घोषणा		FT_DRIVE	9	/* physical disk - addressable in scsi by bus/id/lun */

/*
 *	Host side memory scatter gather list
 *	Used by the adapter क्रम पढ़ो, ग_लिखो, and सूची_पढ़ोplus operations
 *	We have separate 32 and 64 bit version because even
 *	on 64 bit प्रणालीs not all cards support the 64 bit version
 */
काष्ठा sgentry अणु
	__le32	addr;	/* 32-bit address. */
	__le32	count;	/* Length. */
पूर्ण;

काष्ठा user_sgentry अणु
	u32	addr;	/* 32-bit address. */
	u32	count;	/* Length. */
पूर्ण;

काष्ठा sgentry64 अणु
	__le32	addr[2];	/* 64-bit addr. 2 pieces क्रम data alignment */
	__le32	count;	/* Length. */
पूर्ण;

काष्ठा user_sgentry64 अणु
	u32	addr[2];	/* 64-bit addr. 2 pieces क्रम data alignment */
	u32	count;	/* Length. */
पूर्ण;

काष्ठा sgentryraw अणु
	__le32		next;	/* reserved क्रम F/W use */
	__le32		prev;	/* reserved क्रम F/W use */
	__le32		addr[2];
	__le32		count;
	__le32		flags;	/* reserved क्रम F/W use */
पूर्ण;

काष्ठा user_sgentryraw अणु
	u32		next;	/* reserved क्रम F/W use */
	u32		prev;	/* reserved क्रम F/W use */
	u32		addr[2];
	u32		count;
	u32		flags;	/* reserved क्रम F/W use */
पूर्ण;

काष्ठा sge_ieee1212 अणु
	u32	addrLow;
	u32	addrHigh;
	u32	length;
	u32	flags;
पूर्ण;

/*
 *	SGMAP
 *
 *	This is the SGMAP काष्ठाure क्रम all commands that use
 *	32-bit addressing.
 */

काष्ठा sgmap अणु
	__le32		count;
	काष्ठा sgentry	sg[1];
पूर्ण;

काष्ठा user_sgmap अणु
	u32		count;
	काष्ठा user_sgentry	sg[1];
पूर्ण;

काष्ठा sgmap64 अणु
	__le32		count;
	काष्ठा sgentry64 sg[1];
पूर्ण;

काष्ठा user_sgmap64 अणु
	u32		count;
	काष्ठा user_sgentry64 sg[1];
पूर्ण;

काष्ठा sgmapraw अणु
	__le32		  count;
	काष्ठा sgentryraw sg[1];
पूर्ण;

काष्ठा user_sgmapraw अणु
	u32		  count;
	काष्ठा user_sgentryraw sg[1];
पूर्ण;

काष्ठा creation_info
अणु
	u8		buildnum;		/* e.g., 588 */
	u8		usec;			/* e.g., 588 */
	u8		via;			/* e.g., 1 = FSU,
						 *	 2 = API
						 */
	u8		year;			/* e.g., 1997 = 97 */
	__le32		date;			/*
						 * अचिन्हित	Month		:4;	// 1 - 12
						 * अचिन्हित	Day		:6;	// 1 - 32
						 * अचिन्हित	Hour		:6;	// 0 - 23
						 * अचिन्हित	Minute		:6;	// 0 - 60
						 * अचिन्हित	Second		:6;	// 0 - 60
						 */
	__le32		serial[2];			/* e.g., 0x1DEADB0BFAFAF001 */
पूर्ण;


/*
 *	Define all the स्थिरants needed क्रम the communication पूर्णांकerface
 */

/*
 *	Define how many queue entries each queue will have and the total
 *	number of entries क्रम the entire communication पूर्णांकerface. Also define
 *	how many queues we support.
 *
 *	This has to match the controller
 */

#घोषणा NUMBER_OF_COMM_QUEUES  8   // 4 command; 4 response
#घोषणा HOST_HIGH_CMD_ENTRIES  4
#घोषणा HOST_NORM_CMD_ENTRIES  8
#घोषणा ADAP_HIGH_CMD_ENTRIES  4
#घोषणा ADAP_NORM_CMD_ENTRIES  512
#घोषणा HOST_HIGH_RESP_ENTRIES 4
#घोषणा HOST_NORM_RESP_ENTRIES 512
#घोषणा ADAP_HIGH_RESP_ENTRIES 4
#घोषणा ADAP_NORM_RESP_ENTRIES 8

#घोषणा TOTAL_QUEUE_ENTRIES  \
    (HOST_NORM_CMD_ENTRIES + HOST_HIGH_CMD_ENTRIES + ADAP_NORM_CMD_ENTRIES + ADAP_HIGH_CMD_ENTRIES + \
	    HOST_NORM_RESP_ENTRIES + HOST_HIGH_RESP_ENTRIES + ADAP_NORM_RESP_ENTRIES + ADAP_HIGH_RESP_ENTRIES)


/*
 *	Set the queues on a 16 byte alignment
 */

#घोषणा QUEUE_ALIGNMENT		16

/*
 *	The queue headers define the Communication Region queues. These
 *	are physically contiguous and accessible by both the adapter and the
 *	host. Even though all queue headers are in the same contiguous block
 *	they will be represented as inभागidual units in the data काष्ठाures.
 */

काष्ठा aac_entry अणु
	__le32 size; /* Size in bytes of Fib which this QE poपूर्णांकs to */
	__le32 addr; /* Receiver address of the FIB */
पूर्ण;

/*
 *	The adapter assumes the ProducerIndex and ConsumerIndex are grouped
 *	adjacently and in that order.
 */

काष्ठा aac_qhdr अणु
	__le64 header_addr;/* Address to hand the adapter to access
			      to this queue head */
	__le32 *producer; /* The producer index क्रम this queue (host address) */
	__le32 *consumer; /* The consumer index क्रम this queue (host address) */
पूर्ण;

/*
 *	Define all the events which the adapter would like to notअगरy
 *	the host of.
 */

#घोषणा		HostNormCmdQue		1	/* Change in host normal priority command queue */
#घोषणा		HostHighCmdQue		2	/* Change in host high priority command queue */
#घोषणा		HostNormRespQue		3	/* Change in host normal priority response queue */
#घोषणा		HostHighRespQue		4	/* Change in host high priority response queue */
#घोषणा		AdapNormRespNotFull	5
#घोषणा		AdapHighRespNotFull	6
#घोषणा		AdapNormCmdNotFull	7
#घोषणा		AdapHighCmdNotFull	8
#घोषणा		SynchCommandComplete	9
#घोषणा		AdapInternalError	0xfe    /* The adapter detected an पूर्णांकernal error shutting करोwn */

/*
 *	Define all the events the host wishes to notअगरy the
 *	adapter of. The first four values much match the Qid the
 *	corresponding queue.
 */

#घोषणा		AdapNormCmdQue		2
#घोषणा		AdapHighCmdQue		3
#घोषणा		AdapNormRespQue		6
#घोषणा		AdapHighRespQue		7
#घोषणा		HostShutकरोwn		8
#घोषणा		HostPowerFail		9
#घोषणा		FatalCommError		10
#घोषणा		HostNormRespNotFull	11
#घोषणा		HostHighRespNotFull	12
#घोषणा		HostNormCmdNotFull	13
#घोषणा		HostHighCmdNotFull	14
#घोषणा		FastIo			15
#घोषणा		AdapPrपूर्णांकfDone		16

/*
 *	Define all the queues that the adapter and host use to communicate
 *	Number them to match the physical queue layout.
 */

क्रमागत aac_queue_types अणु
        HostNormCmdQueue = 0,	/* Adapter to host normal priority command traffic */
        HostHighCmdQueue,	/* Adapter to host high priority command traffic */
        AdapNormCmdQueue,	/* Host to adapter normal priority command traffic */
        AdapHighCmdQueue,	/* Host to adapter high priority command traffic */
        HostNormRespQueue,	/* Adapter to host normal priority response traffic */
        HostHighRespQueue,	/* Adapter to host high priority response traffic */
        AdapNormRespQueue,	/* Host to adapter normal priority response traffic */
        AdapHighRespQueue	/* Host to adapter high priority response traffic */
पूर्ण;

/*
 *	Assign type values to the FSA communication data काष्ठाures
 */

#घोषणा		FIB_MAGIC	0x0001
#घोषणा		FIB_MAGIC2	0x0004
#घोषणा		FIB_MAGIC2_64	0x0005

/*
 *	Define the priority levels the FSA communication routines support.
 */

#घोषणा		FsaNormal	1

/* transport FIB header (PMC) */
काष्ठा aac_fib_xporthdr अणु
	__le64	HostAddress;	/* FIB host address w/o xport header */
	__le32	Size;		/* FIB size excluding xport header */
	__le32	Handle;		/* driver handle to reference the FIB */
	__le64	Reserved[2];
पूर्ण;

#घोषणा		ALIGN32		32

/*
 * Define the FIB. The FIB is the where all the requested data and
 * command inक्रमmation are put to the application on the FSA adapter.
 */

काष्ठा aac_fibhdr अणु
	__le32 XferState;	/* Current transfer state क्रम this CCB */
	__le16 Command;		/* Routing inक्रमmation क्रम the destination */
	u8 StructType;		/* Type FIB */
	u8 Unused;		/* Unused */
	__le16 Size;		/* Size of this FIB in bytes */
	__le16 SenderSize;	/* Size of the FIB in the sender
				   (क्रम response sizing) */
	__le32 SenderFibAddress;  /* Host defined data in the FIB */
	जोड़ अणु
		__le32 ReceiverFibAddress;/* Logical address of this FIB क्रम
				     the adapter (old) */
		__le32 SenderFibAddressHigh;/* upper 32bit of phys. FIB address */
		__le32 TimeStamp;	/* otherwise बारtamp क्रम FW पूर्णांकernal use */
	पूर्ण u;
	__le32 Handle;		/* FIB handle used क्रम MSGU commnunication */
	u32 Previous;		/* FW पूर्णांकernal use */
	u32 Next;		/* FW पूर्णांकernal use */
पूर्ण;

काष्ठा hw_fib अणु
	काष्ठा aac_fibhdr header;
	u8 data[512-माप(काष्ठा aac_fibhdr)];	// Command specअगरic data
पूर्ण;

/*
 *	FIB commands
 */

#घोषणा		TestCommandResponse		1
#घोषणा		TestAdapterCommand		2
/*
 *	Lowlevel and comm commands
 */
#घोषणा		LastTestCommand			100
#घोषणा		ReinitHostNormCommandQueue	101
#घोषणा		ReinitHostHighCommandQueue	102
#घोषणा		ReinitHostHighRespQueue		103
#घोषणा		ReinitHostNormRespQueue		104
#घोषणा		ReinitAdapNormCommandQueue	105
#घोषणा		ReinitAdapHighCommandQueue	107
#घोषणा		ReinitAdapHighRespQueue		108
#घोषणा		ReinitAdapNormRespQueue		109
#घोषणा		InterfaceShutकरोwn		110
#घोषणा		DmaCommandFib			120
#घोषणा		StartProfile			121
#घोषणा		TermProfile			122
#घोषणा		SpeedTest			123
#घोषणा		TakeABreakPt			124
#घोषणा		RequestPerfData			125
#घोषणा		SetInterruptDefTimer		126
#घोषणा		SetInterruptDefCount		127
#घोषणा		GetInterruptDefStatus		128
#घोषणा		LastCommCommand			129
/*
 *	Fileप्रणाली commands
 */
#घोषणा		NuFileSystem			300
#घोषणा		UFS				301
#घोषणा		HostFileSystem			302
#घोषणा		LastFileSystemCommand		303
/*
 *	Container Commands
 */
#घोषणा		ContainerCommand		500
#घोषणा		ContainerCommand64		501
#घोषणा		ContainerRawIo			502
#घोषणा		ContainerRawIo2			503
/*
 *	Scsi Port commands (scsi passthrough)
 */
#घोषणा		ScsiPortCommand			600
#घोषणा		ScsiPortCommand64		601
/*
 *	Misc house keeping and generic adapter initiated commands
 */
#घोषणा		AअगरRequest			700
#घोषणा		CheckRevision			701
#घोषणा		FsaHostShutकरोwn			702
#घोषणा		RequestAdapterInfo		703
#घोषणा		IsAdapterPaused			704
#घोषणा		SendHostTime			705
#घोषणा		RequestSupplementAdapterInfo	706
#घोषणा		LastMiscCommand			707

/*
 * Commands that will target the failover level on the FSA adapter
 */

क्रमागत fib_xfer_state अणु
	HostOwned			= (1<<0),
	AdapterOwned			= (1<<1),
	FibInitialized			= (1<<2),
	FibEmpty			= (1<<3),
	AllocatedFromPool		= (1<<4),
	SentFromHost			= (1<<5),
	SentFromAdapter			= (1<<6),
	ResponseExpected		= (1<<7),
	NoResponseExpected		= (1<<8),
	AdapterProcessed		= (1<<9),
	HostProcessed			= (1<<10),
	HighPriority			= (1<<11),
	NormalPriority			= (1<<12),
	Async				= (1<<13),
	AsyncIo				= (1<<13),	// rpbfix: हटाओ with new regime
	PageFileIo			= (1<<14),	// rpbfix: हटाओ with new regime
	ShutकरोwnRequest			= (1<<15),
	LazyWrite			= (1<<16),	// rpbfix: हटाओ with new regime
	AdapterMicroFib			= (1<<17),
	BIOSFibPath			= (1<<18),
	FastResponseCapable		= (1<<19),
	ApiFib				= (1<<20),	/* Its an API Fib */
	/* PMC NEW COMM: There is no more AIF data pending */
	NoMoreAअगरDataAvailable		= (1<<21)
पूर्ण;

/*
 *	The following defines needs to be updated any समय there is an
 *	incompatible change made to the aac_init काष्ठाure.
 */

#घोषणा ADAPTER_INIT_STRUCT_REVISION		3
#घोषणा ADAPTER_INIT_STRUCT_REVISION_4		4 // rocket science
#घोषणा ADAPTER_INIT_STRUCT_REVISION_6		6 /* PMC src */
#घोषणा ADAPTER_INIT_STRUCT_REVISION_7		7 /* Denali */
#घोषणा ADAPTER_INIT_STRUCT_REVISION_8		8 // Thor

जोड़ aac_init
अणु
	काष्ठा _r7 अणु
		__le32	init_काष्ठा_revision;
		__le32	no_of_msix_vectors;
		__le32	fsrev;
		__le32	comm_header_address;
		__le32	fast_io_comm_area_address;
		__le32	adapter_fibs_physical_address;
		__le32	adapter_fibs_भव_address;
		__le32	adapter_fibs_size;
		__le32	adapter_fib_align;
		__le32	म_लिखोbuf;
		__le32	म_लिखोbufsiz;
		/* number of 4k pages of host phys. mem. */
		__le32	host_phys_mem_pages;
		/* number of seconds since 1970. */
		__le32	host_elapsed_seconds;
		/* ADAPTER_INIT_STRUCT_REVISION_4 begins here */
		__le32	init_flags;	/* flags क्रम supported features */
#घोषणा INITFLAGS_NEW_COMM_SUPPORTED	0x00000001
#घोषणा INITFLAGS_DRIVER_USES_UTC_TIME	0x00000010
#घोषणा INITFLAGS_DRIVER_SUPPORTS_PM	0x00000020
#घोषणा INITFLAGS_NEW_COMM_TYPE1_SUPPORTED	0x00000040
#घोषणा INITFLAGS_FAST_JBOD_SUPPORTED	0x00000080
#घोषणा INITFLAGS_NEW_COMM_TYPE2_SUPPORTED	0x00000100
#घोषणा INITFLAGS_DRIVER_SUPPORTS_HBA_MODE  0x00000400
		__le32	max_io_commands;	/* max outstanding commands */
		__le32	max_io_size;	/* largest I/O command */
		__le32	max_fib_size;	/* largest FIB to adapter */
		/* ADAPTER_INIT_STRUCT_REVISION_5 begins here */
		__le32	max_num_aअगर;	/* max number of aअगर */
		/* ADAPTER_INIT_STRUCT_REVISION_6 begins here */
		/* Host RRQ (response queue) क्रम SRC */
		__le32	host_rrq_addr_low;
		__le32	host_rrq_addr_high;
	पूर्ण r7;
	काष्ठा _r8 अणु
		/* ADAPTER_INIT_STRUCT_REVISION_8 */
		__le32	init_काष्ठा_revision;
		__le32	rr_queue_count;
		__le32	host_elapsed_seconds; /* number of secs since 1970. */
		__le32	init_flags;
		__le32	max_io_size;	/* largest I/O command */
		__le32	max_num_aअगर;	/* max number of aअगर */
		__le32	reserved1;
		__le32	reserved2;
		काष्ठा _rrq अणु
			__le32	host_addr_low;
			__le32	host_addr_high;
			__le16	msix_id;
			__le16	element_count;
			__le16	comp_thresh;
			__le16	unused;
		पूर्ण rrq[1];		/* up to 64 RRQ addresses */
	पूर्ण r8;
पूर्ण;

क्रमागत aac_log_level अणु
	LOG_AAC_INIT			= 10,
	LOG_AAC_INFORMATIONAL		= 20,
	LOG_AAC_WARNING			= 30,
	LOG_AAC_LOW_ERROR		= 40,
	LOG_AAC_MEDIUM_ERROR		= 50,
	LOG_AAC_HIGH_ERROR		= 60,
	LOG_AAC_PANIC			= 70,
	LOG_AAC_DEBUG			= 80,
	LOG_AAC_WINDBG_PRINT		= 90
पूर्ण;

#घोषणा FSAFS_NTC_GET_ADAPTER_FIB_CONTEXT	0x030b
#घोषणा FSAFS_NTC_FIB_CONTEXT			0x030c

काष्ठा aac_dev;
काष्ठा fib;
काष्ठा scsi_cmnd;

काष्ठा adapter_ops
अणु
	/* Low level operations */
	व्योम (*adapter_पूर्णांकerrupt)(काष्ठा aac_dev *dev);
	व्योम (*adapter_notअगरy)(काष्ठा aac_dev *dev, u32 event);
	व्योम (*adapter_disable_पूर्णांक)(काष्ठा aac_dev *dev);
	व्योम (*adapter_enable_पूर्णांक)(काष्ठा aac_dev *dev);
	पूर्णांक  (*adapter_sync_cmd)(काष्ठा aac_dev *dev, u32 command, u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 *status, u32 *r1, u32 *r2, u32 *r3, u32 *r4);
	पूर्णांक  (*adapter_check_health)(काष्ठा aac_dev *dev);
	पूर्णांक  (*adapter_restart)(काष्ठा aac_dev *dev, पूर्णांक bled, u8 reset_type);
	व्योम (*adapter_start)(काष्ठा aac_dev *dev);
	/* Transport operations */
	पूर्णांक  (*adapter_ioremap)(काष्ठा aac_dev * dev, u32 size);
	irq_handler_t adapter_पूर्णांकr;
	/* Packet operations */
	पूर्णांक  (*adapter_deliver)(काष्ठा fib * fib);
	पूर्णांक  (*adapter_bounds)(काष्ठा aac_dev * dev, काष्ठा scsi_cmnd * cmd, u64 lba);
	पूर्णांक  (*adapter_पढ़ो)(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count);
	पूर्णांक  (*adapter_ग_लिखो)(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd, u64 lba, u32 count, पूर्णांक fua);
	पूर्णांक  (*adapter_scsi)(काष्ठा fib * fib, काष्ठा scsi_cmnd * cmd);
	/* Administrative operations */
	पूर्णांक  (*adapter_comm)(काष्ठा aac_dev * dev, पूर्णांक comm);
पूर्ण;

/*
 *	Define which पूर्णांकerrupt handler needs to be installed
 */

काष्ठा aac_driver_ident
अणु
	पूर्णांक	(*init)(काष्ठा aac_dev *dev);
	अक्षर *	name;
	अक्षर *	vname;
	अक्षर *	model;
	u16	channels;
	पूर्णांक	quirks;
पूर्ण;
/*
 * Some adapter firmware needs communication memory
 * below 2gig. This tells the init function to set the
 * dma mask such that fib memory will be allocated where the
 * adapter firmware can get to it.
 */
#घोषणा AAC_QUIRK_31BIT	0x0001

/*
 * Some adapter firmware, when the raid card's cache is turned off, can not
 * split up scatter gathers in order to deal with the limits of the
 * underlying CHIM. This limit is 34 scatter gather elements.
 */
#घोषणा AAC_QUIRK_34SG	0x0002

/*
 * This adapter is a slave (no Firmware)
 */
#घोषणा AAC_QUIRK_SLAVE 0x0004

/*
 * This adapter is a master.
 */
#घोषणा AAC_QUIRK_MASTER 0x0008

/*
 * Some adapter firmware perक्रमm poorly when it must split up scatter gathers
 * in order to deal with the limits of the underlying CHIM. This limit in this
 * class of adapters is 17 scatter gather elements.
 */
#घोषणा AAC_QUIRK_17SG	0x0010

/*
 *	Some adapter firmware करोes not support 64 bit scsi passthrough
 * commands.
 */
#घोषणा AAC_QUIRK_SCSI_32	0x0020

/*
 * SRC based adapters support the AअगरReqEvent functions
 */
#घोषणा AAC_QUIRK_SRC 0x0040

/*
 *	The adapter पूर्णांकerface specs all queues to be located in the same
 *	physically contiguous block. The host काष्ठाure that defines the
 *	commuication queues will assume they are each a separate physically
 *	contiguous memory region that will support them all being one big
 *	contiguous block.
 *	There is a command and response queue क्रम each level and direction of
 *	commuication. These regions are accessed by both the host and adapter.
 */

काष्ठा aac_queue अणु
	u64			logical;	/*address we give the adapter */
	काष्ठा aac_entry	*base;		/*प्रणाली भव address */
	काष्ठा aac_qhdr		headers;	/*producer,consumer q headers*/
	u32			entries;	/*Number of queue entries */
	रुको_queue_head_t	qfull;		/*Event to रुको on अगर q full */
	रुको_queue_head_t	cmdपढ़ोy;	/*Cmd पढ़ोy from the adapter */
		/* This is only valid क्रम adapter to host command queues. */
	spinlock_t		*lock;		/* Spinlock क्रम this queue must take this lock beक्रमe accessing the lock */
	spinlock_t		lockdata;	/* Actual lock (used only on one side of the lock) */
	काष्ठा list_head	cmdq;		/* A queue of FIBs which need to be prcessed by the FS thपढ़ो. This is */
						/* only valid क्रम command queues which receive entries from the adapter. */
	/* Number of entries on outstanding queue. */
	atomic_t		numpending;
	काष्ठा aac_dev *	dev;		/* Back poपूर्णांकer to adapter काष्ठाure */
पूर्ण;

/*
 *	Message queues. The order here is important, see also the
 *	queue type ordering
 */

काष्ठा aac_queue_block
अणु
	काष्ठा aac_queue queue[8];
पूर्ण;

/*
 *	SaP1 Message Unit Registers
 */

काष्ठा sa_drawbridge_CSR अणु
				/*	Offset	|  Name */
	__le32	reserved[10];	/*	00h-27h |  Reserved */
	u8	LUT_Offset;	/*	28h	|  Lookup Table Offset */
	u8	reserved1[3];	/*	29h-2bh	|  Reserved */
	__le32	LUT_Data;	/*	2ch	|  Looup Table Data */
	__le32	reserved2[26];	/*	30h-97h	|  Reserved */
	__le16	PRICLEARIRQ;	/*	98h	|  Primary Clear Irq */
	__le16	SECCLEARIRQ;	/*	9ah	|  Secondary Clear Irq */
	__le16	PRISETIRQ;	/*	9ch	|  Primary Set Irq */
	__le16	SECSETIRQ;	/*	9eh	|  Secondary Set Irq */
	__le16	PRICLEARIRQMASK;/*	a0h	|  Primary Clear Irq Mask */
	__le16	SECCLEARIRQMASK;/*	a2h	|  Secondary Clear Irq Mask */
	__le16	PRISETIRQMASK;	/*	a4h	|  Primary Set Irq Mask */
	__le16	SECSETIRQMASK;	/*	a6h	|  Secondary Set Irq Mask */
	__le32	MAILBOX0;	/*	a8h	|  Scratchpad 0 */
	__le32	MAILBOX1;	/*	ach	|  Scratchpad 1 */
	__le32	MAILBOX2;	/*	b0h	|  Scratchpad 2 */
	__le32	MAILBOX3;	/*	b4h	|  Scratchpad 3 */
	__le32	MAILBOX4;	/*	b8h	|  Scratchpad 4 */
	__le32	MAILBOX5;	/*	bch	|  Scratchpad 5 */
	__le32	MAILBOX6;	/*	c0h	|  Scratchpad 6 */
	__le32	MAILBOX7;	/*	c4h	|  Scratchpad 7 */
	__le32	ROM_Setup_Data;	/*	c8h	|  Rom Setup and Data */
	__le32	ROM_Control_Addr;/*	cch	|  Rom Control and Address */
	__le32	reserved3[12];	/*	d0h-ffh	|  reserved */
	__le32	LUT[64];	/*    100h-1ffh	|  Lookup Table Entries */
पूर्ण;

#घोषणा Mailbox0	SaDbCSR.MAILBOX0
#घोषणा Mailbox1	SaDbCSR.MAILBOX1
#घोषणा Mailbox2	SaDbCSR.MAILBOX2
#घोषणा Mailbox3	SaDbCSR.MAILBOX3
#घोषणा Mailbox4	SaDbCSR.MAILBOX4
#घोषणा Mailbox5	SaDbCSR.MAILBOX5
#घोषणा Mailbox6	SaDbCSR.MAILBOX6
#घोषणा Mailbox7	SaDbCSR.MAILBOX7

#घोषणा DoorbellReg_p SaDbCSR.PRISETIRQ
#घोषणा DoorbellReg_s SaDbCSR.SECSETIRQ
#घोषणा DoorbellClrReg_p SaDbCSR.PRICLEARIRQ


#घोषणा	DOORBELL_0	0x0001
#घोषणा DOORBELL_1	0x0002
#घोषणा DOORBELL_2	0x0004
#घोषणा DOORBELL_3	0x0008
#घोषणा DOORBELL_4	0x0010
#घोषणा DOORBELL_5	0x0020
#घोषणा DOORBELL_6	0x0040


#घोषणा Prपूर्णांकfReady	DOORBELL_5
#घोषणा Prपूर्णांकfDone	DOORBELL_5

काष्ठा sa_रेजिस्टरs अणु
	काष्ठा sa_drawbridge_CSR	SaDbCSR;			/* 98h - c4h */
पूर्ण;


#घोषणा SA_INIT_NUM_MSIXVECTORS		1
#घोषणा SA_MINIPORT_REVISION		SA_INIT_NUM_MSIXVECTORS

#घोषणा sa_पढ़ोw(AEP, CSR)		पढ़ोl(&((AEP)->regs.sa->CSR))
#घोषणा sa_पढ़ोl(AEP, CSR)		पढ़ोl(&((AEP)->regs.sa->CSR))
#घोषणा sa_ग_लिखोw(AEP, CSR, value)	ग_लिखोw(value, &((AEP)->regs.sa->CSR))
#घोषणा sa_ग_लिखोl(AEP, CSR, value)	ग_लिखोl(value, &((AEP)->regs.sa->CSR))

/*
 *	Rx Message Unit Registers
 */

काष्ठा rx_mu_रेजिस्टरs अणु
			    /*	Local  | PCI*| Name */
	__le32	ARSR;	    /*	1300h  | 00h | APIC Register Select Register */
	__le32	reserved0;  /*	1304h  | 04h | Reserved */
	__le32	AWR;	    /*	1308h  | 08h | APIC Winकरोw Register */
	__le32	reserved1;  /*	130Ch  | 0Ch | Reserved */
	__le32	IMRx[2];    /*	1310h  | 10h | Inbound Message Registers */
	__le32	OMRx[2];    /*	1318h  | 18h | Outbound Message Registers */
	__le32	IDR;	    /*	1320h  | 20h | Inbound Doorbell Register */
	__le32	IISR;	    /*	1324h  | 24h | Inbound Interrupt
						Status Register */
	__le32	IIMR;	    /*	1328h  | 28h | Inbound Interrupt
						Mask Register */
	__le32	ODR;	    /*	132Ch  | 2Ch | Outbound Doorbell Register */
	__le32	OISR;	    /*	1330h  | 30h | Outbound Interrupt
						Status Register */
	__le32	OIMR;	    /*	1334h  | 34h | Outbound Interrupt
						Mask Register */
	__le32	reserved2;  /*	1338h  | 38h | Reserved */
	__le32	reserved3;  /*	133Ch  | 3Ch | Reserved */
	__le32	InboundQueue;/*	1340h  | 40h | Inbound Queue Port relative to firmware */
	__le32	OutboundQueue;/*1344h  | 44h | Outbound Queue Port relative to firmware */
			    /* * Must access through ATU Inbound
				 Translation Winकरोw */
पूर्ण;

काष्ठा rx_inbound अणु
	__le32	Mailbox[8];
पूर्ण;

#घोषणा	INBOUNDDOORBELL_0	0x00000001
#घोषणा INBOUNDDOORBELL_1	0x00000002
#घोषणा INBOUNDDOORBELL_2	0x00000004
#घोषणा INBOUNDDOORBELL_3	0x00000008
#घोषणा INBOUNDDOORBELL_4	0x00000010
#घोषणा INBOUNDDOORBELL_5	0x00000020
#घोषणा INBOUNDDOORBELL_6	0x00000040

#घोषणा	OUTBOUNDDOORBELL_0	0x00000001
#घोषणा OUTBOUNDDOORBELL_1	0x00000002
#घोषणा OUTBOUNDDOORBELL_2	0x00000004
#घोषणा OUTBOUNDDOORBELL_3	0x00000008
#घोषणा OUTBOUNDDOORBELL_4	0x00000010

#घोषणा InboundDoorbellReg	MUnit.IDR
#घोषणा OutboundDoorbellReg	MUnit.ODR

काष्ठा rx_रेजिस्टरs अणु
	काष्ठा rx_mu_रेजिस्टरs		MUnit;		/* 1300h - 1347h */
	__le32				reserved1[2];	/* 1348h - 134ch */
	काष्ठा rx_inbound		IndexRegs;
पूर्ण;

#घोषणा rx_पढ़ोb(AEP, CSR)		पढ़ोb(&((AEP)->regs.rx->CSR))
#घोषणा rx_पढ़ोl(AEP, CSR)		पढ़ोl(&((AEP)->regs.rx->CSR))
#घोषणा rx_ग_लिखोb(AEP, CSR, value)	ग_लिखोb(value, &((AEP)->regs.rx->CSR))
#घोषणा rx_ग_लिखोl(AEP, CSR, value)	ग_लिखोl(value, &((AEP)->regs.rx->CSR))

/*
 *	Rkt Message Unit Registers (same as Rx, except a larger reserve region)
 */

#घोषणा rkt_mu_रेजिस्टरs rx_mu_रेजिस्टरs
#घोषणा rkt_inbound rx_inbound

काष्ठा rkt_रेजिस्टरs अणु
	काष्ठा rkt_mu_रेजिस्टरs		MUnit;		 /* 1300h - 1347h */
	__le32				reserved1[1006]; /* 1348h - 22fch */
	काष्ठा rkt_inbound		IndexRegs;	 /* 2300h - */
पूर्ण;

#घोषणा rkt_पढ़ोb(AEP, CSR)		पढ़ोb(&((AEP)->regs.rkt->CSR))
#घोषणा rkt_पढ़ोl(AEP, CSR)		पढ़ोl(&((AEP)->regs.rkt->CSR))
#घोषणा rkt_ग_लिखोb(AEP, CSR, value)	ग_लिखोb(value, &((AEP)->regs.rkt->CSR))
#घोषणा rkt_ग_लिखोl(AEP, CSR, value)	ग_लिखोl(value, &((AEP)->regs.rkt->CSR))

/*
 * PMC SRC message unit रेजिस्टरs
 */

#घोषणा src_inbound rx_inbound

काष्ठा src_mu_रेजिस्टरs अणु
				/*  PCI*| Name */
	__le32	reserved0[6];	/*  00h | Reserved */
	__le32	IOAR[2];	/*  18h | IOA->host पूर्णांकerrupt रेजिस्टर */
	__le32	IDR;		/*  20h | Inbound Doorbell Register */
	__le32	IISR;		/*  24h | Inbound Int. Status Register */
	__le32	reserved1[3];	/*  28h | Reserved */
	__le32	OIMR;		/*  34h | Outbound Int. Mask Register */
	__le32	reserved2[25];  /*  38h | Reserved */
	__le32	ODR_R;		/*  9ch | Outbound Doorbell Read */
	__le32	ODR_C;		/*  a0h | Outbound Doorbell Clear */
	__le32	reserved3[3];	/*  a4h | Reserved */
	__le32	SCR0;		/*  b0h | Scratchpad 0 */
	__le32	reserved4[2];	/*  b4h | Reserved */
	__le32	OMR;		/*  bch | Outbound Message Register */
	__le32	IQ_L;		/*  c0h | Inbound Queue (Low address) */
	__le32	IQ_H;		/*  c4h | Inbound Queue (High address) */
	__le32	ODR_MSI;	/*  c8h | MSI रेजिस्टर क्रम sync./AIF */
	__le32  reserved5;	/*  cch | Reserved */
	__le32	IQN_L;		/*  d0h | Inbound (native cmd) low  */
	__le32	IQN_H;		/*  d4h | Inbound (native cmd) high */
पूर्ण;

काष्ठा src_रेजिस्टरs अणु
	काष्ठा src_mu_रेजिस्टरs MUnit;	/* 00h - cbh */
	जोड़ अणु
		काष्ठा अणु
			__le32 reserved1[130786];	/* d8h - 7fc5fh */
			काष्ठा src_inbound IndexRegs;	/* 7fc60h */
		पूर्ण tupelo;
		काष्ठा अणु
			__le32 reserved1[970];		/* d8h - fffh */
			काष्ठा src_inbound IndexRegs;	/* 1000h */
		पूर्ण denali;
	पूर्ण u;
पूर्ण;

#घोषणा src_पढ़ोb(AEP, CSR)		पढ़ोb(&((AEP)->regs.src.bar0->CSR))
#घोषणा src_पढ़ोl(AEP, CSR)		पढ़ोl(&((AEP)->regs.src.bar0->CSR))
#घोषणा src_ग_लिखोb(AEP, CSR, value)	ग_लिखोb(value, \
						&((AEP)->regs.src.bar0->CSR))
#घोषणा src_ग_लिखोl(AEP, CSR, value)	ग_लिखोl(value, \
						&((AEP)->regs.src.bar0->CSR))
#अगर defined(ग_लिखोq)
#घोषणा	src_ग_लिखोq(AEP, CSR, value)	ग_लिखोq(value, \
						&((AEP)->regs.src.bar0->CSR))
#पूर्ण_अगर

#घोषणा SRC_ODR_SHIFT		12
#घोषणा SRC_IDR_SHIFT		9
#घोषणा SRC_MSI_READ_MASK	0x1000

प्रकार व्योम (*fib_callback)(व्योम *ctxt, काष्ठा fib *fibctx);

काष्ठा aac_fib_context अणु
	s16			type;		// used क्रम verअगरication of काष्ठाure
	s16			size;
	u32			unique;		// unique value representing this context
	uदीर्घ			jअगरfies;	// used क्रम cleanup - dmb changed to uदीर्घ
	काष्ठा list_head	next;		// used to link context's पूर्णांकo a linked list
	काष्ठा completion	completion;	// this is used to रुको क्रम the next fib to arrive.
	पूर्णांक			रुको;		// Set to true when thपढ़ो is in WaitForSingleObject
	अचिन्हित दीर्घ		count;		// total number of FIBs on FibList
	काष्ठा list_head	fib_list;	// this holds fibs and their attachd hw_fibs
पूर्ण;

काष्ठा sense_data अणु
	u8 error_code;		/* 70h (current errors), 71h(deferred errors) */
	u8 valid:1;		/* A valid bit of one indicates that the inक्रमmation  */
				/* field contains valid inक्रमmation as defined in the
				 * SCSI-2 Standard.
				 */
	u8 segment_number;	/* Only used क्रम COPY, COMPARE, or COPY AND VERIFY Commands */
	u8 sense_key:4;		/* Sense Key */
	u8 reserved:1;
	u8 ILI:1;		/* Incorrect Length Indicator */
	u8 EOM:1;		/* End Of Medium - reserved क्रम अक्रमom access devices */
	u8 filemark:1;		/* Filemark - reserved क्रम अक्रमom access devices */

	u8 inक्रमmation[4];	/* क्रम direct-access devices, contains the अचिन्हित
				 * logical block address or residue associated with
				 * the sense key
				 */
	u8 add_sense_len;	/* number of additional sense bytes to follow this field */
	u8 cmnd_info[4];	/* not used */
	u8 ASC;			/* Additional Sense Code */
	u8 ASCQ;		/* Additional Sense Code Qualअगरier */
	u8 FRUC;		/* Field Replaceable Unit Code - not used */
	u8 bit_ptr:3;		/* indicates which byte of the CDB or parameter data
				 * was in error
				 */
	u8 BPV:1;		/* bit poपूर्णांकer valid (BPV): 1- indicates that
				 * the bit_ptr field has valid value
				 */
	u8 reserved2:2;
	u8 CD:1;		/* command data bit: 1- illegal parameter in CDB.
				 * 0- illegal parameter in data.
				 */
	u8 SKSV:1;
	u8 field_ptr[2];	/* byte of the CDB or parameter data in error */
पूर्ण;

काष्ठा fsa_dev_info अणु
	u64		last;
	u64		size;
	u32		type;
	u32		config_रुकोing_on;
	अचिन्हित दीर्घ	config_रुकोing_stamp;
	u16		queue_depth;
	u8		config_needed;
	u8		valid;
	u8		ro;
	u8		locked;
	u8		deleted;
	अक्षर		devname[8];
	काष्ठा sense_data sense_data;
	u32		block_size;
	u8		identअगरier[16];
पूर्ण;

काष्ठा fib अणु
	व्योम			*next;	/* this is used by the allocator */
	s16			type;
	s16			size;
	/*
	 *	The Adapter that this I/O is destined क्रम.
	 */
	काष्ठा aac_dev		*dev;
	/*
	 *	This is the event the sendfib routine will रुको on अगर the
	 *	caller did not pass one and this is synch io.
	 */
	काष्ठा completion	event_रुको;
	spinlock_t		event_lock;

	u32			करोne;	/* माला_लो set to 1 when fib is complete */
	fib_callback		callback;
	व्योम			*callback_data;
	u32			flags; // u32 dmb was uदीर्घ
	/*
	 *	And क्रम the पूर्णांकernal issue/reply queues (we may be able
	 *	to merge these two)
	 */
	काष्ठा list_head	fiblink;
	व्योम			*data;
	u32			vector_no;
	काष्ठा hw_fib		*hw_fib_va;	/* also used क्रम native */
	dma_addr_t		hw_fib_pa;	/* physical address of hw_fib*/
	dma_addr_t		hw_sgl_pa;	/* extra sgl क्रम native */
	dma_addr_t		hw_error_pa;	/* error buffer क्रम native */
	u32			hbacmd_size;	/* cmd size क्रम native */
पूर्ण;

#घोषणा AAC_INIT			0
#घोषणा AAC_RESCAN			1

#घोषणा AAC_DEVTYPE_RAID_MEMBER	1
#घोषणा AAC_DEVTYPE_ARC_RAW		2
#घोषणा AAC_DEVTYPE_NATIVE_RAW		3

#घोषणा AAC_RESCAN_DELAY		(10 * HZ)

काष्ठा aac_hba_map_info अणु
	__le32	rmw_nexus;		/* nexus क्रम native HBA devices */
	u8		devtype;	/* device type */
	s8		reset_state;	/* 0 - no reset, 1..x - */
					/* after xth TM LUN reset */
	u16		qd_limit;
	u32		scan_counter;
	काष्ठा aac_ciss_identअगरy_pd  *safw_identअगरy_resp;
पूर्ण;

/*
 *	Adapter Inक्रमmation Block
 *
 *	This is वापसed by the RequestAdapterInfo block
 */

काष्ठा aac_adapter_info
अणु
	__le32	platक्रमm;
	__le32	cpu;
	__le32	subcpu;
	__le32	घड़ी;
	__le32	execmem;
	__le32	buffermem;
	__le32	totalmem;
	__le32	kernelrev;
	__le32	kernelbuild;
	__le32	monitorrev;
	__le32	monitorbuild;
	__le32	hwrev;
	__le32	hwbuild;
	__le32	biosrev;
	__le32	biosbuild;
	__le32	cluster;
	__le32	clusterchannelmask;
	__le32	serial[2];
	__le32	battery;
	__le32	options;
	__le32	OEM;
पूर्ण;

काष्ठा aac_supplement_adapter_info
अणु
	u8	adapter_type_text[17+1];
	u8	pad[2];
	__le32	flash_memory_byte_size;
	__le32	flash_image_id;
	__le32	max_number_ports;
	__le32	version;
	__le32	feature_bits;
	u8	slot_number;
	u8	reserved_pad0[3];
	u8	build_date[12];
	__le32	current_number_ports;
	काष्ठा अणु
		u8	assembly_pn[8];
		u8	fru_pn[8];
		u8	battery_fru_pn[8];
		u8	ec_version_string[8];
		u8	tsid[12];
	पूर्ण	vpd_info;
	__le32	flash_firmware_revision;
	__le32	flash_firmware_build;
	__le32	raid_type_morph_options;
	__le32	flash_firmware_boot_revision;
	__le32	flash_firmware_boot_build;
	u8	mfg_pcba_serial_no[12];
	u8	mfg_wwn_name[8];
	__le32	supported_options2;
	__le32	काष्ठा_expansion;
	/* StructExpansion == 1 */
	__le32	feature_bits3;
	__le32	supported_perक्रमmance_modes;
	u8	host_bus_type;		/* uses HOST_BUS_TYPE_xxx defines */
	u8	host_bus_width;		/* actual width in bits or links */
	u16	host_bus_speed;		/* actual bus speed/link rate in MHz */
	u8	max_rrc_drives;		/* max. number of ITP-RRC drives/pool */
	u8	max_disk_xtasks;	/* max. possible num of DiskX Tasks */

	u8	cpld_ver_loaded;
	u8	cpld_ver_in_flash;

	__le64	max_rrc_capacity;
	__le32	compiled_max_hist_log_level;
	u8	custom_board_name[12];
	u16	supported_cntlr_mode;	/* identअगरy supported controller mode */
	u16	reserved_क्रम_future16;
	__le32	supported_options3;	/* reserved क्रम future options */

	__le16	virt_device_bus;		/* virt. SCSI device क्रम Thor */
	__le16	virt_device_target;
	__le16	virt_device_lun;
	__le16	unused;
	__le32	reserved_क्रम_future_growth[68];

पूर्ण;
#घोषणा AAC_FEATURE_FALCON	cpu_to_le32(0x00000010)
#घोषणा AAC_FEATURE_JBOD	cpu_to_le32(0x08000000)
/* SupportedOptions2 */
#घोषणा AAC_OPTION_MU_RESET		cpu_to_le32(0x00000001)
#घोषणा AAC_OPTION_IGNORE_RESET		cpu_to_le32(0x00000002)
#घोषणा AAC_OPTION_POWER_MANAGEMENT	cpu_to_le32(0x00000004)
#घोषणा AAC_OPTION_DOORBELL_RESET	cpu_to_le32(0x00004000)
/* 4KB sector size */
#घोषणा AAC_OPTION_VARIABLE_BLOCK_SIZE	cpu_to_le32(0x00040000)
/* 240 simple volume support */
#घोषणा AAC_OPTION_SUPPORTED_240_VOLUMES cpu_to_le32(0x10000000)
/*
 * Supports FIB dump sync command send prior to IOP_RESET
 */
#घोषणा AAC_OPTION_SUPPORTED3_IOP_RESET_FIB_DUMP	cpu_to_le32(0x00004000)
#घोषणा AAC_SIS_VERSION_V3	3
#घोषणा AAC_SIS_SLOT_UNKNOWN	0xFF

#घोषणा GetBusInfo 0x00000009
काष्ठा aac_bus_info अणु
	__le32	Command;	/* VM_Ioctl */
	__le32	ObjType;	/* FT_DRIVE */
	__le32	MethodId;	/* 1 = SCSI Layer */
	__le32	ObjectId;	/* Handle */
	__le32	CtlCmd;		/* GetBusInfo */
पूर्ण;

काष्ठा aac_bus_info_response अणु
	__le32	Status;		/* ST_OK */
	__le32	ObjType;
	__le32	MethodId;	/* unused */
	__le32	ObjectId;	/* unused */
	__le32	CtlCmd;		/* unused */
	__le32	ProbeComplete;
	__le32	BusCount;
	__le32	Tarमाला_लोPerBus;
	u8	InitiatorBusId[10];
	u8	BusValid[10];
पूर्ण;

/*
 * Battery platक्रमms
 */
#घोषणा AAC_BAT_REQ_PRESENT	(1)
#घोषणा AAC_BAT_REQ_NOTPRESENT	(2)
#घोषणा AAC_BAT_OPT_PRESENT	(3)
#घोषणा AAC_BAT_OPT_NOTPRESENT	(4)
#घोषणा AAC_BAT_NOT_SUPPORTED	(5)
/*
 * cpu types
 */
#घोषणा AAC_CPU_SIMULATOR	(1)
#घोषणा AAC_CPU_I960		(2)
#घोषणा AAC_CPU_STRONGARM	(3)

/*
 * Supported Options
 */
#घोषणा AAC_OPT_SNAPSHOT		cpu_to_le32(1)
#घोषणा AAC_OPT_CLUSTERS		cpu_to_le32(1<<1)
#घोषणा AAC_OPT_WRITE_CACHE		cpu_to_le32(1<<2)
#घोषणा AAC_OPT_64BIT_DATA		cpu_to_le32(1<<3)
#घोषणा AAC_OPT_HOST_TIME_FIB		cpu_to_le32(1<<4)
#घोषणा AAC_OPT_RAID50			cpu_to_le32(1<<5)
#घोषणा AAC_OPT_4GB_WINDOW		cpu_to_le32(1<<6)
#घोषणा AAC_OPT_SCSI_UPGRADEABLE	cpu_to_le32(1<<7)
#घोषणा AAC_OPT_SOFT_ERR_REPORT		cpu_to_le32(1<<8)
#घोषणा AAC_OPT_SUPPORTED_RECONDITION	cpu_to_le32(1<<9)
#घोषणा AAC_OPT_SGMAP_HOST64		cpu_to_le32(1<<10)
#घोषणा AAC_OPT_ALARM			cpu_to_le32(1<<11)
#घोषणा AAC_OPT_NONDASD			cpu_to_le32(1<<12)
#घोषणा AAC_OPT_SCSI_MANAGED		cpu_to_le32(1<<13)
#घोषणा AAC_OPT_RAID_SCSI_MODE		cpu_to_le32(1<<14)
#घोषणा AAC_OPT_SUPPLEMENT_ADAPTER_INFO	cpu_to_le32(1<<16)
#घोषणा AAC_OPT_NEW_COMM		cpu_to_le32(1<<17)
#घोषणा AAC_OPT_NEW_COMM_64		cpu_to_le32(1<<18)
#घोषणा AAC_OPT_EXTENDED		cpu_to_le32(1<<23)
#घोषणा AAC_OPT_NATIVE_HBA		cpu_to_le32(1<<25)
#घोषणा AAC_OPT_NEW_COMM_TYPE1		cpu_to_le32(1<<28)
#घोषणा AAC_OPT_NEW_COMM_TYPE2		cpu_to_le32(1<<29)
#घोषणा AAC_OPT_NEW_COMM_TYPE3		cpu_to_le32(1<<30)
#घोषणा AAC_OPT_NEW_COMM_TYPE4		cpu_to_le32(1<<31)

#घोषणा AAC_COMM_PRODUCER		0
#घोषणा AAC_COMM_MESSAGE		1
#घोषणा AAC_COMM_MESSAGE_TYPE1		3
#घोषणा AAC_COMM_MESSAGE_TYPE2		4
#घोषणा AAC_COMM_MESSAGE_TYPE3		5

#घोषणा AAC_EXTOPT_SA_FIRMWARE		cpu_to_le32(1<<1)
#घोषणा AAC_EXTOPT_SOFT_RESET		cpu_to_le32(1<<16)

/* MSIX context */
काष्ठा aac_msix_ctx अणु
	पूर्णांक		vector_no;
	काष्ठा aac_dev	*dev;
पूर्ण;

काष्ठा aac_dev
अणु
	काष्ठा list_head	entry;
	स्थिर अक्षर		*name;
	पूर्णांक			id;

	/*
	 *	negotiated FIB settings
	 */
	अचिन्हित पूर्णांक		max_fib_size;
	अचिन्हित पूर्णांक		sg_tablesize;
	अचिन्हित पूर्णांक		max_num_aअगर;

	अचिन्हित पूर्णांक		max_cmd_size;	/* max_fib_size or MAX_NATIVE */

	/*
	 *	Map क्रम 128 fib objects (64k)
	 */
	dma_addr_t		hw_fib_pa;	/* also used क्रम native cmd */
	काष्ठा hw_fib		*hw_fib_va;	/* also used क्रम native cmd */
	काष्ठा hw_fib		*aअगर_base_va;
	/*
	 *	Fib Headers
	 */
	काष्ठा fib              *fibs;

	काष्ठा fib		*मुक्त_fib;
	spinlock_t		fib_lock;

	काष्ठा mutex		ioctl_mutex;
	काष्ठा mutex		scan_mutex;
	काष्ठा aac_queue_block *queues;
	/*
	 *	The user API will use an IOCTL to रेजिस्टर itself to receive
	 *	FIBs from the adapter.  The following list is used to keep
	 *	track of all the thपढ़ोs that have requested these FIBs.  The
	 *	mutex is used to synchronize access to all data associated
	 *	with the adapter fibs.
	 */
	काष्ठा list_head	fib_list;

	काष्ठा adapter_ops	a_ops;
	अचिन्हित दीर्घ		fsrev;		/* Main driver's revision number */

	resource_माप_प्रकार		base_start;	/* मुख्य IO base */
	resource_माप_प्रकार		dbg_base;	/* address of UART
						 * debug buffer */

	resource_माप_प्रकार		base_size, dbg_size;	/* Size of
							 *  mapped in region */
	/*
	 * Holds initialization info
	 * to communicate with adapter
	 */
	जोड़ aac_init		*init;
	dma_addr_t		init_pa;	/* Holds physical address of the init काष्ठा */
	/* response queue (अगर AAC_COMM_MESSAGE_TYPE1) */
	__le32			*host_rrq;
	dma_addr_t		host_rrq_pa;	/* phys. address */
	/* index पूर्णांकo rrq buffer */
	u32			host_rrq_idx[AAC_MAX_MSIX];
	atomic_t		rrq_outstanding[AAC_MAX_MSIX];
	u32			fibs_pushed_no;
	काष्ठा pci_dev		*pdev;		/* Our PCI पूर्णांकerface */
	/* poपूर्णांकer to buffer used क्रम म_लिखो's from the adapter */
	व्योम			*म_लिखोbuf;
	व्योम			*comm_addr;	/* Base address of Comm area */
	dma_addr_t		comm_phys;	/* Physical Address of Comm area */
	माप_प्रकार			comm_size;

	काष्ठा Scsi_Host	*scsi_host_ptr;
	पूर्णांक			maximum_num_containers;
	पूर्णांक			maximum_num_physicals;
	पूर्णांक			maximum_num_channels;
	काष्ठा fsa_dev_info	*fsa_dev;
	काष्ठा task_काष्ठा	*thपढ़ो;
	काष्ठा delayed_work	safw_rescan_work;
	काष्ठा delayed_work	src_reinit_aअगर_worker;
	पूर्णांक			cardtype;
	/*
	 *This lock will protect the two 32-bit
	 *ग_लिखोs to the Inbound Queue
	 */
	spinlock_t		iq_lock;

	/*
	 *	The following is the device specअगरic extension.
	 */
#अगर_अघोषित AAC_MIN_FOOTPRINT_SIZE
#	define AAC_MIN_FOOTPRINT_SIZE 8192
#	define AAC_MIN_SRC_BAR0_SIZE 0x400000
#	define AAC_MIN_SRC_BAR1_SIZE 0x800
#	define AAC_MIN_SRCV_BAR0_SIZE 0x100000
#	define AAC_MIN_SRCV_BAR1_SIZE 0x400
#पूर्ण_अगर
	जोड़
	अणु
		काष्ठा sa_रेजिस्टरs __iomem *sa;
		काष्ठा rx_रेजिस्टरs __iomem *rx;
		काष्ठा rkt_रेजिस्टरs __iomem *rkt;
		काष्ठा अणु
			काष्ठा src_रेजिस्टरs __iomem *bar0;
			अक्षर __iomem *bar1;
		पूर्ण src;
	पूर्ण regs;
	अस्थिर व्योम __iomem *base, *dbg_base_mapped;
	अस्थिर काष्ठा rx_inbound __iomem *IndexRegs;
	u32			OIMR; /* Mask Register Cache */
	/*
	 *	AIF thपढ़ो states
	 */
	u32			aअगर_thपढ़ो;
	काष्ठा aac_adapter_info adapter_info;
	काष्ठा aac_supplement_adapter_info supplement_adapter_info;
	/* These are in adapter info but they are in the io flow so
	 * lets अवरोध them out so we करोn't have to करो an AND to check them
	 */
	u8			nondasd_support;
	u8			jbod;
	u8			cache_रक्षित;
	u8			dac_support;
	u8			needs_dac;
	u8			raid_scsi_mode;
	u8			comm_पूर्णांकerface;
	u8			raw_io_पूर्णांकerface;
	u8			raw_io_64;
	u8			म_लिखो_enabled;
	u8			in_reset;
	u8			in_soft_reset;
	u8			msi;
	u8			sa_firmware;
	पूर्णांक			management_fib_count;
	spinlock_t		manage_lock;
	spinlock_t		sync_lock;
	पूर्णांक			sync_mode;
	काष्ठा fib		*sync_fib;
	काष्ठा list_head	sync_fib_list;
	u32			करोorbell_mask;
	u32			max_msix;	/* max. MSI-X vectors */
	u32			vector_cap;	/* MSI-X vector capab.*/
	पूर्णांक			msi_enabled;	/* MSI/MSI-X enabled */
	atomic_t		msix_counter;
	u32			scan_counter;
	काष्ठा msix_entry	msixentry[AAC_MAX_MSIX];
	काष्ठा aac_msix_ctx	aac_msix[AAC_MAX_MSIX]; /* context */
	काष्ठा aac_hba_map_info	hba_map[AAC_MAX_BUSES][AAC_MAX_TARGETS];
	काष्ठा aac_ciss_phys_luns_resp *safw_phys_luns;
	u8			adapter_shutकरोwn;
	u32			handle_pci_error;
	bool			init_reset;
	u8			soft_reset_support;
पूर्ण;

#घोषणा aac_adapter_पूर्णांकerrupt(dev) \
	(dev)->a_ops.adapter_पूर्णांकerrupt(dev)

#घोषणा aac_adapter_notअगरy(dev, event) \
	(dev)->a_ops.adapter_notअगरy(dev, event)

#घोषणा aac_adapter_disable_पूर्णांक(dev) \
	(dev)->a_ops.adapter_disable_पूर्णांक(dev)

#घोषणा aac_adapter_enable_पूर्णांक(dev) \
	(dev)->a_ops.adapter_enable_पूर्णांक(dev)

#घोषणा aac_adapter_sync_cmd(dev, command, p1, p2, p3, p4, p5, p6, status, r1, r2, r3, r4) \
	(dev)->a_ops.adapter_sync_cmd(dev, command, p1, p2, p3, p4, p5, p6, status, r1, r2, r3, r4)

#घोषणा aac_adapter_restart(dev, bled, reset_type) \
	((dev)->a_ops.adapter_restart(dev, bled, reset_type))

#घोषणा aac_adapter_start(dev) \
	((dev)->a_ops.adapter_start(dev))

#घोषणा aac_adapter_ioremap(dev, size) \
	(dev)->a_ops.adapter_ioremap(dev, size)

#घोषणा aac_adapter_deliver(fib) \
	((fib)->dev)->a_ops.adapter_deliver(fib)

#घोषणा aac_adapter_bounds(dev,cmd,lba) \
	dev->a_ops.adapter_bounds(dev,cmd,lba)

#घोषणा aac_adapter_पढ़ो(fib,cmd,lba,count) \
	((fib)->dev)->a_ops.adapter_पढ़ो(fib,cmd,lba,count)

#घोषणा aac_adapter_ग_लिखो(fib,cmd,lba,count,fua) \
	((fib)->dev)->a_ops.adapter_ग_लिखो(fib,cmd,lba,count,fua)

#घोषणा aac_adapter_scsi(fib,cmd) \
	((fib)->dev)->a_ops.adapter_scsi(fib,cmd)

#घोषणा aac_adapter_comm(dev,comm) \
	(dev)->a_ops.adapter_comm(dev, comm)

#घोषणा FIB_CONTEXT_FLAG_TIMED_OUT		(0x00000001)
#घोषणा FIB_CONTEXT_FLAG			(0x00000002)
#घोषणा FIB_CONTEXT_FLAG_WAIT			(0x00000004)
#घोषणा FIB_CONTEXT_FLAG_FASTRESP		(0x00000008)
#घोषणा FIB_CONTEXT_FLAG_NATIVE_HBA		(0x00000010)
#घोषणा FIB_CONTEXT_FLAG_NATIVE_HBA_TMF	(0x00000020)
#घोषणा FIB_CONTEXT_FLAG_SCSI_CMD	(0x00000040)
#घोषणा FIB_CONTEXT_FLAG_EH_RESET	(0x00000080)

/*
 *	Define the command values
 */

#घोषणा		Null			0
#घोषणा		GetAttributes		1
#घोषणा		SetAttributes		2
#घोषणा		Lookup			3
#घोषणा		ReadLink		4
#घोषणा		Read			5
#घोषणा		Write			6
#घोषणा		Create			7
#घोषणा		MakeDirectory		8
#घोषणा		SymbolicLink		9
#घोषणा		MakeNode		10
#घोषणा		Removex			11
#घोषणा		RemoveDirectoryx	12
#घोषणा		Rename			13
#घोषणा		Link			14
#घोषणा		ReadDirectory		15
#घोषणा		ReadDirectoryPlus	16
#घोषणा		FileSystemStatus	17
#घोषणा		FileSystemInfo		18
#घोषणा		PathConfigure		19
#घोषणा		Commit			20
#घोषणा		Mount			21
#घोषणा		UnMount			22
#घोषणा		Newfs			23
#घोषणा		FsCheck			24
#घोषणा		FsSync			25
#घोषणा		SimReadWrite		26
#घोषणा		SetFileSystemStatus	27
#घोषणा		BlockRead		28
#घोषणा		BlockWrite		29
#घोषणा		NvramIoctl		30
#घोषणा		FsSyncWait		31
#घोषणा		ClearArchiveBit		32
#घोषणा		SetAcl			33
#घोषणा		GetAcl			34
#घोषणा		AssignAcl		35
#घोषणा		FaultInsertion		36	/* Fault Insertion Command */
#घोषणा		CrazyCache		37	/* Crazycache */

#घोषणा		MAX_FSACOMMAND_NUM	38


/*
 *	Define the status वापसs. These are very unixlike although
 *	most are not in fact used
 */

#घोषणा		ST_OK		0
#घोषणा		ST_PERM		1
#घोषणा		ST_NOENT	2
#घोषणा		ST_IO		5
#घोषणा		ST_NXIO		6
#घोषणा		ST_E2BIG	7
#घोषणा		ST_MEDERR	8
#घोषणा		ST_ACCES	13
#घोषणा		ST_EXIST	17
#घोषणा		ST_XDEV		18
#घोषणा		ST_NODEV	19
#घोषणा		ST_NOTसूची	20
#घोषणा		ST_ISसूची	21
#घोषणा		ST_INVAL	22
#घोषणा		ST_FBIG		27
#घोषणा		ST_NOSPC	28
#घोषणा		ST_ROFS		30
#घोषणा		ST_MLINK	31
#घोषणा		ST_WOULDBLOCK	35
#घोषणा		ST_NAMETOOLONG	63
#घोषणा		ST_NOTEMPTY	66
#घोषणा		ST_DQUOT	69
#घोषणा		ST_STALE	70
#घोषणा		ST_REMOTE	71
#घोषणा		ST_NOT_READY	72
#घोषणा		ST_BADHANDLE	10001
#घोषणा		ST_NOT_SYNC	10002
#घोषणा		ST_BAD_COOKIE	10003
#घोषणा		ST_NOTSUPP	10004
#घोषणा		ST_TOOSMALL	10005
#घोषणा		ST_SERVERFAULT	10006
#घोषणा		ST_BADTYPE	10007
#घोषणा		ST_JUKEBOX	10008
#घोषणा		ST_NOTMOUNTED	10009
#घोषणा		ST_MAINTMODE	10010
#घोषणा		ST_STALEACL	10011

/*
 *	On ग_लिखोs how करोes the client want the data written.
 */

#घोषणा	CACHE_CSTABLE		1
#घोषणा CACHE_UNSTABLE		2

/*
 *	Lets the client know at which level the data was committed on
 *	a ग_लिखो request
 */

#घोषणा	CMखाता_SYNCH_NVRAM	1
#घोषणा	CMDATA_SYNCH_NVRAM	2
#घोषणा	CMखाता_SYNCH		3
#घोषणा CMDATA_SYNCH		4
#घोषणा CMUNSTABLE		5

#घोषणा	RIO_TYPE_WRITE 			0x0000
#घोषणा	RIO_TYPE_READ			0x0001
#घोषणा	RIO_SUREWRITE			0x0008

#घोषणा RIO2_IO_TYPE			0x0003
#घोषणा RIO2_IO_TYPE_WRITE		0x0000
#घोषणा RIO2_IO_TYPE_READ		0x0001
#घोषणा RIO2_IO_TYPE_VERIFY		0x0002
#घोषणा RIO2_IO_ERROR			0x0004
#घोषणा RIO2_IO_SUREWRITE		0x0008
#घोषणा RIO2_SGL_CONFORMANT		0x0010
#घोषणा RIO2_SG_FORMAT			0xF000
#घोषणा RIO2_SG_FORMAT_ARC		0x0000
#घोषणा RIO2_SG_FORMAT_SRL		0x1000
#घोषणा RIO2_SG_FORMAT_IEEE1212		0x2000

काष्ठा aac_पढ़ो
अणु
	__le32		command;
	__le32		cid;
	__le32		block;
	__le32		count;
	काष्ठा sgmap	sg;	// Must be last in काष्ठा because it is variable
पूर्ण;

काष्ठा aac_पढ़ो64
अणु
	__le32		command;
	__le16		cid;
	__le16		sector_count;
	__le32		block;
	__le16		pad;
	__le16		flags;
	काष्ठा sgmap64	sg;	// Must be last in काष्ठा because it is variable
पूर्ण;

काष्ठा aac_पढ़ो_reply
अणु
	__le32		status;
	__le32		count;
पूर्ण;

काष्ठा aac_ग_लिखो
अणु
	__le32		command;
	__le32		cid;
	__le32		block;
	__le32		count;
	__le32		stable;	// Not used
	काष्ठा sgmap	sg;	// Must be last in काष्ठा because it is variable
पूर्ण;

काष्ठा aac_ग_लिखो64
अणु
	__le32		command;
	__le16		cid;
	__le16		sector_count;
	__le32		block;
	__le16		pad;
	__le16		flags;
	काष्ठा sgmap64	sg;	// Must be last in काष्ठा because it is variable
पूर्ण;
काष्ठा aac_ग_लिखो_reply
अणु
	__le32		status;
	__le32		count;
	__le32		committed;
पूर्ण;

काष्ठा aac_raw_io
अणु
	__le32		block[2];
	__le32		count;
	__le16		cid;
	__le16		flags;		/* 00 W, 01 R */
	__le16		bpTotal;	/* reserved क्रम F/W use */
	__le16		bpComplete;	/* reserved क्रम F/W use */
	काष्ठा sgmapraw	sg;
पूर्ण;

काष्ठा aac_raw_io2 अणु
	__le32		blockLow;
	__le32		blockHigh;
	__le32		byteCount;
	__le16		cid;
	__le16		flags;		/* RIO2 flags */
	__le32		sgeFirstSize;	/* size of first sge el. */
	__le32		sgeNominalSize;	/* size of 2nd sge el. (अगर conक्रमmant) */
	u8		sgeCnt;		/* only 8 bits required */
	u8		bpTotal;	/* reserved क्रम F/W use */
	u8		bpComplete;	/* reserved क्रम F/W use */
	u8		sgeFirstIndex;	/* reserved क्रम F/W use */
	u8		unused[4];
	काष्ठा sge_ieee1212	sge[1];
पूर्ण;

#घोषणा CT_FLUSH_CACHE 129
काष्ठा aac_synchronize अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_FLUSH_CACHE */
	__le32		cid;
	__le32		parm1;
	__le32		parm2;
	__le32		parm3;
	__le32		parm4;
	__le32		count;	/* माप(((काष्ठा aac_synchronize_reply *)शून्य)->data) */
पूर्ण;

काष्ठा aac_synchronize_reply अणु
	__le32		dummy0;
	__le32		dummy1;
	__le32		status;	/* CT_OK */
	__le32		parm1;
	__le32		parm2;
	__le32		parm3;
	__le32		parm4;
	__le32		parm5;
	u8		data[16];
पूर्ण;

#घोषणा CT_POWER_MANAGEMENT	245
#घोषणा CT_PM_START_UNIT	2
#घोषणा CT_PM_STOP_UNIT		3
#घोषणा CT_PM_UNIT_IMMEDIATE	1
काष्ठा aac_घातer_management अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_POWER_MANAGEMENT */
	__le32		sub;		/* CT_PM_* */
	__le32		cid;
	__le32		parm;		/* CT_PM_sub_* */
पूर्ण;

#घोषणा CT_PAUSE_IO    65
#घोषणा CT_RELEASE_IO  66
काष्ठा aac_छोड़ो अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_PAUSE_IO */
	__le32		समयout;	/* 10ms ticks */
	__le32		min;
	__le32		noRescan;
	__le32		parm3;
	__le32		parm4;
	__le32		count;	/* माप(((काष्ठा aac_छोड़ो_reply *)शून्य)->data) */
पूर्ण;

काष्ठा aac_srb
अणु
	__le32		function;
	__le32		channel;
	__le32		id;
	__le32		lun;
	__le32		समयout;
	__le32		flags;
	__le32		count;		// Data xfer size
	__le32		retry_limit;
	__le32		cdb_size;
	u8		cdb[16];
	काष्ठा	sgmap	sg;
पूर्ण;

/*
 * This and associated data काष्ठाs are used by the
 * ioctl caller and are in cpu order.
 */
काष्ठा user_aac_srb
अणु
	u32		function;
	u32		channel;
	u32		id;
	u32		lun;
	u32		समयout;
	u32		flags;
	u32		count;		// Data xfer size
	u32		retry_limit;
	u32		cdb_size;
	u8		cdb[16];
	काष्ठा	user_sgmap	sg;
पूर्ण;

#घोषणा		AAC_SENSE_BUFFERSIZE	 30

काष्ठा aac_srb_reply
अणु
	__le32		status;
	__le32		srb_status;
	__le32		scsi_status;
	__le32		data_xfer_length;
	__le32		sense_data_size;
	u8		sense_data[AAC_SENSE_BUFFERSIZE]; // Can this be SCSI_SENSE_BUFFERSIZE
पूर्ण;

काष्ठा aac_srb_unit अणु
	काष्ठा aac_srb		srb;
	काष्ठा aac_srb_reply	srb_reply;
पूर्ण;

/*
 * SRB Flags
 */
#घोषणा		SRB_NoDataXfer		 0x0000
#घोषणा		SRB_DisableDisconnect	 0x0004
#घोषणा		SRB_DisableSynchTransfer 0x0008
#घोषणा		SRB_BypassFrozenQueue	 0x0010
#घोषणा		SRB_DisableAutosense	 0x0020
#घोषणा		SRB_DataIn		 0x0040
#घोषणा		SRB_DataOut		 0x0080

/*
 * SRB Functions - set in aac_srb->function
 */
#घोषणा	SRBF_ExecuteScsi	0x0000
#घोषणा	SRBF_ClaimDevice	0x0001
#घोषणा	SRBF_IO_Control		0x0002
#घोषणा	SRBF_ReceiveEvent	0x0003
#घोषणा	SRBF_ReleaseQueue	0x0004
#घोषणा	SRBF_AttachDevice	0x0005
#घोषणा	SRBF_ReleaseDevice	0x0006
#घोषणा	SRBF_Shutकरोwn		0x0007
#घोषणा	SRBF_Flush		0x0008
#घोषणा	SRBF_AbortCommand	0x0010
#घोषणा	SRBF_ReleaseRecovery	0x0011
#घोषणा	SRBF_ResetBus		0x0012
#घोषणा	SRBF_ResetDevice	0x0013
#घोषणा	SRBF_TerminateIO	0x0014
#घोषणा	SRBF_FlushQueue		0x0015
#घोषणा	SRBF_RemoveDevice	0x0016
#घोषणा	SRBF_Doमुख्यValidation	0x0017

/*
 * SRB SCSI Status - set in aac_srb->scsi_status
 */
#घोषणा SRB_STATUS_PENDING                  0x00
#घोषणा SRB_STATUS_SUCCESS                  0x01
#घोषणा SRB_STATUS_ABORTED                  0x02
#घोषणा SRB_STATUS_ABORT_FAILED             0x03
#घोषणा SRB_STATUS_ERROR                    0x04
#घोषणा SRB_STATUS_BUSY                     0x05
#घोषणा SRB_STATUS_INVALID_REQUEST          0x06
#घोषणा SRB_STATUS_INVALID_PATH_ID          0x07
#घोषणा SRB_STATUS_NO_DEVICE                0x08
#घोषणा SRB_STATUS_TIMEOUT                  0x09
#घोषणा SRB_STATUS_SELECTION_TIMEOUT        0x0A
#घोषणा SRB_STATUS_COMMAND_TIMEOUT          0x0B
#घोषणा SRB_STATUS_MESSAGE_REJECTED         0x0D
#घोषणा SRB_STATUS_BUS_RESET                0x0E
#घोषणा SRB_STATUS_PARITY_ERROR             0x0F
#घोषणा SRB_STATUS_REQUEST_SENSE_FAILED     0x10
#घोषणा SRB_STATUS_NO_HBA                   0x11
#घोषणा SRB_STATUS_DATA_OVERRUN             0x12
#घोषणा SRB_STATUS_UNEXPECTED_BUS_FREE      0x13
#घोषणा SRB_STATUS_PHASE_SEQUENCE_FAILURE   0x14
#घोषणा SRB_STATUS_BAD_SRB_BLOCK_LENGTH     0x15
#घोषणा SRB_STATUS_REQUEST_FLUSHED          0x16
#घोषणा SRB_STATUS_DELAYED_RETRY	    0x17
#घोषणा SRB_STATUS_INVALID_LUN              0x20
#घोषणा SRB_STATUS_INVALID_TARGET_ID        0x21
#घोषणा SRB_STATUS_BAD_FUNCTION             0x22
#घोषणा SRB_STATUS_ERROR_RECOVERY           0x23
#घोषणा SRB_STATUS_NOT_STARTED		    0x24
#घोषणा SRB_STATUS_NOT_IN_USE		    0x30
#घोषणा SRB_STATUS_FORCE_ABORT		    0x31
#घोषणा SRB_STATUS_DOMAIN_VALIDATION_FAIL   0x32

/*
 * Object-Server / Volume-Manager Dispatch Classes
 */

#घोषणा		VM_Null			0
#घोषणा		VM_NameServe		1
#घोषणा		VM_ContainerConfig	2
#घोषणा		VM_Ioctl		3
#घोषणा		VM_Fileप्रणालीIoctl	4
#घोषणा		VM_CloseAll		5
#घोषणा		VM_CtBlockRead		6
#घोषणा		VM_CtBlockWrite		7
#घोषणा		VM_SliceBlockRead	8	/* raw access to configured "storage objects" */
#घोषणा		VM_SliceBlockWrite	9
#घोषणा		VM_DriveBlockRead	10	/* raw access to physical devices */
#घोषणा		VM_DriveBlockWrite	11
#घोषणा		VM_EnclosureMgt		12	/* enclosure management */
#घोषणा		VM_Unused		13	/* used to be diskset management */
#घोषणा		VM_CtBlockVerअगरy	14
#घोषणा		VM_CtPerf		15	/* perक्रमmance test */
#घोषणा		VM_CtBlockRead64	16
#घोषणा		VM_CtBlockWrite64	17
#घोषणा		VM_CtBlockVerअगरy64	18
#घोषणा		VM_CtHostRead64		19
#घोषणा		VM_CtHostWrite64	20
#घोषणा		VM_DrvErrTblLog		21
#घोषणा		VM_NameServe64		22
#घोषणा		VM_NameServeAllBlk	30

#घोषणा		MAX_VMCOMMAND_NUM	23	/* used क्रम sizing stats array - leave last */

/*
 *	Descriptive inक्रमmation (eg, vital stats)
 *	that a content manager might report.  The
 *	FileArray fileप्रणाली component is one example
 *	of a content manager.  Raw mode might be
 *	another.
 */

काष्ठा aac_fsinfo अणु
	__le32  fsTotalSize;	/* Consumed by fs, incl. metadata */
	__le32  fsBlockSize;
	__le32  fsFragSize;
	__le32  fsMaxExtendSize;
	__le32  fsSpaceUnits;
	__le32  fsMaxNumFiles;
	__le32  fsNumFreeFiles;
	__le32  fsInodeDensity;
पूर्ण;	/* valid अगरf ObjType == FT_खाताSYS && !(ContentState & FSCS_NOTCLEAN) */

काष्ठा  aac_blockdevinfo अणु
	__le32	block_size;
	__le32  logical_phys_map;
	u8	identअगरier[16];
पूर्ण;

जोड़ aac_contentinfo अणु
	काष्ठा	aac_fsinfo		filesys;
	काष्ठा	aac_blockdevinfo	bdevinfo;
पूर्ण;

/*
 *	Query क्रम Container Configuration Status
 */

#घोषणा CT_GET_CONFIG_STATUS 147
काष्ठा aac_get_config_status अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_GET_CONFIG_STATUS */
	__le32		parm1;
	__le32		parm2;
	__le32		parm3;
	__le32		parm4;
	__le32		parm5;
	__le32		count;	/* माप(((काष्ठा aac_get_config_status_resp *)शून्य)->data) */
पूर्ण;

#घोषणा CFACT_CONTINUE 0
#घोषणा CFACT_PAUSE    1
#घोषणा CFACT_ABORT    2
काष्ठा aac_get_config_status_resp अणु
	__le32		response; /* ST_OK */
	__le32		dummy0;
	__le32		status;	/* CT_OK */
	__le32		parm1;
	__le32		parm2;
	__le32		parm3;
	__le32		parm4;
	__le32		parm5;
	काष्ठा अणु
		__le32	action; /* CFACT_CONTINUE, CFACT_PAUSE or CFACT_ABORT */
		__le16	flags;
		__le16	count;
	पूर्ण		data;
पूर्ण;

/*
 *	Accept the configuration as-is
 */

#घोषणा CT_COMMIT_CONFIG 152

काष्ठा aac_commit_config अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_COMMIT_CONFIG */
पूर्ण;

/*
 *	Query क्रम Container Configuration Status
 */

#घोषणा CT_GET_CONTAINER_COUNT 4
काष्ठा aac_get_container_count अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_GET_CONTAINER_COUNT */
पूर्ण;

काष्ठा aac_get_container_count_resp अणु
	__le32		response; /* ST_OK */
	__le32		dummy0;
	__le32		MaxContainers;
	__le32		ContainerSwitchEntries;
	__le32		MaxPartitions;
	__le32		MaxSimpleVolumes;
पूर्ण;


/*
 *	Query क्रम "mountable" objects, ie, objects that are typically
 *	associated with a drive letter on the client (host) side.
 */

काष्ठा aac_mntent अणु
	__le32			oid;
	u8			name[16];	/* अगर applicable */
	काष्ठा creation_info	create_info;	/* अगर applicable */
	__le32			capacity;
	__le32			vol;		/* substrate काष्ठाure */
	__le32			obj;		/* FT_खाताSYS, etc. */
	__le32			state;		/* unपढ़ोy क्रम mounting,
						   पढ़ोonly, etc. */
	जोड़ aac_contentinfo	fileinfo;	/* Info specअगरic to content
						   manager (eg, fileप्रणाली) */
	__le32			altoid;		/* != oid <==> snapshot or
						   broken mirror exists */
	__le32			capacityhigh;
पूर्ण;

#घोषणा FSCS_NOTCLEAN	0x0001  /* fsck is necessary beक्रमe mounting */
#घोषणा FSCS_READONLY	0x0002	/* possible result of broken mirror */
#घोषणा FSCS_HIDDEN	0x0004	/* should be ignored - set during a clear */
#घोषणा FSCS_NOT_READY	0x0008	/* Array spinning up to fulfil request */

काष्ठा aac_query_mount अणु
	__le32		command;
	__le32		type;
	__le32		count;
पूर्ण;

काष्ठा aac_mount अणु
	__le32		status;
	__le32		type;           /* should be same as that requested */
	__le32		count;
	काष्ठा aac_mntent mnt[1];
पूर्ण;

#घोषणा CT_READ_NAME 130
काष्ठा aac_get_name अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_READ_NAME */
	__le32		cid;
	__le32		parm1;
	__le32		parm2;
	__le32		parm3;
	__le32		parm4;
	__le32		count;	/* माप(((काष्ठा aac_get_name_resp *)शून्य)->data) */
पूर्ण;

काष्ठा aac_get_name_resp अणु
	__le32		dummy0;
	__le32		dummy1;
	__le32		status;	/* CT_OK */
	__le32		parm1;
	__le32		parm2;
	__le32		parm3;
	__le32		parm4;
	__le32		parm5;
	u8		data[17];
पूर्ण;

#घोषणा CT_CID_TO_32BITS_UID 165
काष्ठा aac_get_serial अणु
	__le32		command;	/* VM_ContainerConfig */
	__le32		type;		/* CT_CID_TO_32BITS_UID */
	__le32		cid;
पूर्ण;

काष्ठा aac_get_serial_resp अणु
	__le32		dummy0;
	__le32		dummy1;
	__le32		status;	/* CT_OK */
	__le32		uid;
पूर्ण;

/*
 * The following command is sent to shut करोwn each container.
 */

काष्ठा aac_बंद अणु
	__le32	command;
	__le32	cid;
पूर्ण;

काष्ठा aac_query_disk
अणु
	s32	cnum;
	s32	bus;
	s32	id;
	s32	lun;
	u32	valid;
	u32	locked;
	u32	deleted;
	s32	instance;
	s8	name[10];
	u32	unmapped;
पूर्ण;

काष्ठा aac_delete_disk अणु
	u32	disknum;
	u32	cnum;
पूर्ण;

काष्ठा fib_ioctl
अणु
	u32	fibctx;
	s32	रुको;
	अक्षर	__user *fib;
पूर्ण;

काष्ठा revision
अणु
	u32 compat;
	__le32 version;
	__le32 build;
पूर्ण;


/*
 *	Ugly - non Linux like ioctl coding क्रम back compat.
 */

#घोषणा CTL_CODE(function, method) (                 \
    (4<< 16) | ((function) << 2) | (method) \
)

/*
 *	Define the method codes क्रम how buffers are passed क्रम I/O and FS
 *	controls
 */

#घोषणा METHOD_BUFFERED                 0
#घोषणा METHOD_NEITHER                  3

/*
 *	Fileप्रणाली ioctls
 */

#घोषणा FSACTL_SENDFIB				CTL_CODE(2050, METHOD_BUFFERED)
#घोषणा FSACTL_SEND_RAW_SRB			CTL_CODE(2067, METHOD_BUFFERED)
#घोषणा FSACTL_DELETE_DISK			0x163
#घोषणा FSACTL_QUERY_DISK			0x173
#घोषणा FSACTL_OPEN_GET_ADAPTER_FIB		CTL_CODE(2100, METHOD_BUFFERED)
#घोषणा FSACTL_GET_NEXT_ADAPTER_FIB		CTL_CODE(2101, METHOD_BUFFERED)
#घोषणा FSACTL_CLOSE_GET_ADAPTER_FIB		CTL_CODE(2102, METHOD_BUFFERED)
#घोषणा FSACTL_MINIPORT_REV_CHECK               CTL_CODE(2107, METHOD_BUFFERED)
#घोषणा FSACTL_GET_PCI_INFO			CTL_CODE(2119, METHOD_BUFFERED)
#घोषणा FSACTL_FORCE_DELETE_DISK		CTL_CODE(2120, METHOD_NEITHER)
#घोषणा FSACTL_GET_CONTAINERS			2131
#घोषणा FSACTL_SEND_LARGE_FIB			CTL_CODE(2138, METHOD_BUFFERED)
#घोषणा FSACTL_RESET_IOP			CTL_CODE(2140, METHOD_BUFFERED)
#घोषणा FSACTL_GET_HBA_INFO			CTL_CODE(2150, METHOD_BUFFERED)
/* flags defined क्रम IOP & HW SOFT RESET */
#घोषणा HW_IOP_RESET				0x01
#घोषणा HW_SOFT_RESET				0x02
#घोषणा IOP_HWSOFT_RESET			(HW_IOP_RESET | HW_SOFT_RESET)
/* HW Soft Reset रेजिस्टर offset */
#घोषणा IBW_SWR_OFFSET				0x4000
#घोषणा SOFT_RESET_TIME			60



काष्ठा aac_common
अणु
	/*
	 *	If this value is set to 1 then पूर्णांकerrupt moderation will occur
	 *	in the base commuication support.
	 */
	u32 irq_mod;
	u32 peak_fibs;
	u32 zero_fibs;
	u32 fib_समयouts;
	/*
	 *	Statistical counters in debug mode
	 */
#अगर_घोषित DBG
	u32 FibsSent;
	u32 FibRecved;
	u32 NativeSent;
	u32 NativeRecved;
	u32 NoResponseSent;
	u32 NoResponseRecved;
	u32 AsyncSent;
	u32 AsyncRecved;
	u32 NormalSent;
	u32 NormalRecved;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा aac_common aac_config;

/*
 * This is क्रम management ioctl purpose only.
 */
काष्ठा aac_hba_info अणु

	u8	driver_name[50];
	u8	adapter_number;
	u8	प्रणाली_io_bus_number;
	u8	device_number;
	u32	function_number;
	u32	venकरोr_id;
	u32	device_id;
	u32	sub_venकरोr_id;
	u32	sub_प्रणाली_id;
	u32	mapped_base_address_size;
	u32	base_physical_address_high_part;
	u32	base_physical_address_low_part;

	u32	max_command_size;
	u32	max_fib_size;
	u32	max_scatter_gather_from_os;
	u32	max_scatter_gather_to_fw;
	u32	max_outstanding_fibs;

	u32	queue_start_threshold;
	u32	queue_dump_threshold;
	u32	max_io_size_queued;
	u32	outstanding_io;

	u32	firmware_build_number;
	u32	bios_build_number;
	u32	driver_build_number;
	u32	serial_number_high_part;
	u32	serial_number_low_part;
	u32	supported_options;
	u32	feature_bits;
	u32	currentnumber_ports;

	u8	new_comm_पूर्णांकerface:1;
	u8	new_commands_supported:1;
	u8	disable_passthrough:1;
	u8	expose_non_dasd:1;
	u8	queue_allowed:1;
	u8	bled_check_enabled:1;
	u8	reserved1:1;
	u8	reserted2:1;

	u32	reserved3[10];

पूर्ण;

/*
 *	The following macro is used when sending and receiving FIBs. It is
 *	only used क्रम debugging.
 */

#अगर_घोषित DBG
#घोषणा	FIB_COUNTER_INCREMENT(counter)		(counter)++
#अन्यथा
#घोषणा	FIB_COUNTER_INCREMENT(counter)
#पूर्ण_अगर

/*
 *	Adapter direct commands
 *	Monitor/Kernel API
 */

#घोषणा	BREAKPOINT_REQUEST		0x00000004
#घोषणा	INIT_STRUCT_BASE_ADDRESS	0x00000005
#घोषणा READ_PERMANENT_PARAMETERS	0x0000000a
#घोषणा WRITE_PERMANENT_PARAMETERS	0x0000000b
#घोषणा HOST_CRASHING			0x0000000d
#घोषणा	SEND_SYNCHRONOUS_FIB		0x0000000c
#घोषणा COMMAND_POST_RESULTS		0x00000014
#घोषणा GET_ADAPTER_PROPERTIES		0x00000019
#घोषणा GET_DRIVER_BUFFER_PROPERTIES	0x00000023
#घोषणा RCV_TEMP_READINGS		0x00000025
#घोषणा GET_COMM_PREFERRED_SETTINGS	0x00000026
#घोषणा IOP_RESET_FW_FIB_DUMP		0x00000034
#घोषणा DROP_IO			0x00000035
#घोषणा IOP_RESET			0x00001000
#घोषणा IOP_RESET_ALWAYS		0x00001001
#घोषणा RE_INIT_ADAPTER		0x000000ee

#घोषणा IOP_SRC_RESET_MASK		0x00000100

/*
 *	Adapter Status Register
 *
 *  Phase Staus mailbox is 32bits:
 *	<31:16> = Phase Status
 *	<15:0>  = Phase
 *
 *	The adapter reports is present state through the phase.  Only
 *	a single phase should be ever be set.  Each phase can have multiple
 *	phase status bits to provide more detailed inक्रमmation about the
 *	state of the board.  Care should be taken to ensure that any phase
 *	status bits that are set when changing the phase are also valid
 *	क्रम the new phase or be cleared out.  Adapter software (monitor,
 *	अगरlash, kernel) is responsible क्रम properly मुख्यtining the phase
 *	status mailbox when it is running.
 *
 *	MONKER_API Phases
 *
 *	Phases are bit oriented.  It is NOT valid  to have multiple bits set
 */

#घोषणा	SELF_TEST_FAILED		0x00000004
#घोषणा	MONITOR_PANIC			0x00000020
#घोषणा	KERNEL_BOOTING			0x00000040
#घोषणा	KERNEL_UP_AND_RUNNING		0x00000080
#घोषणा	KERNEL_PANIC			0x00000100
#घोषणा	FLASH_UPD_PENDING		0x00002000
#घोषणा	FLASH_UPD_SUCCESS		0x00004000
#घोषणा	FLASH_UPD_FAILED		0x00008000
#घोषणा	INVALID_OMR			0xffffffff
#घोषणा	FWUPD_TIMEOUT			(5 * 60)

/*
 *	Doorbell bit defines
 */

#घोषणा DoorBellSyncCmdAvailable	(1<<0)	/* Host -> Adapter */
#घोषणा DoorBellPrपूर्णांकfDone		(1<<5)	/* Host -> Adapter */
#घोषणा DoorBellAdapterNormCmdReady	(1<<1)	/* Adapter -> Host */
#घोषणा DoorBellAdapterNormRespReady	(1<<2)	/* Adapter -> Host */
#घोषणा DoorBellAdapterNormCmdNotFull	(1<<3)	/* Adapter -> Host */
#घोषणा DoorBellAdapterNormRespNotFull	(1<<4)	/* Adapter -> Host */
#घोषणा DoorBellPrपूर्णांकfReady		(1<<5)	/* Adapter -> Host */
#घोषणा DoorBellAअगरPending		(1<<6)	/* Adapter -> Host */

/* PMC specअगरic outbound करोorbell bits */
#घोषणा PmDoorBellResponseSent		(1<<1)	/* Adapter -> Host */

/*
 *	For FIB communication, we need all of the following things
 *	to send back to the user.
 */

#घोषणा		AअगरCmdEventNotअगरy	1	/* Notअगरy of event */
#घोषणा			AअगरEnConfigChange	3	/* Adapter configuration change */
#घोषणा			AअगरEnContainerChange	4	/* Container configuration change */
#घोषणा			AअगरEnDeviceFailure	5	/* SCSI device failed */
#घोषणा			AअगरEnEnclosureManagement 13	/* EM_DRIVE_* */
#घोषणा				EM_DRIVE_INSERTION	31
#घोषणा				EM_DRIVE_REMOVAL	32
#घोषणा			EM_SES_DRIVE_INSERTION	33
#घोषणा			EM_SES_DRIVE_REMOVAL	26
#घोषणा			AअगरEnBatteryEvent	14	/* Change in Battery State */
#घोषणा			AअगरEnAddContainer	15	/* A new array was created */
#घोषणा			AअगरEnDeleteContainer	16	/* A container was deleted */
#घोषणा			AअगरEnExpEvent		23	/* Firmware Event Log */
#घोषणा			AअगरExeFirmwarePanic	3	/* Firmware Event Panic */
#घोषणा			AअगरHighPriority		3	/* Highest Priority Event */
#घोषणा			AअगरEnAddJBOD		30	/* JBOD created */
#घोषणा			AअगरEnDeleteJBOD		31	/* JBOD deleted */

#घोषणा			AअगरBuManagerEvent		42 /* Bu management*/
#घोषणा			AअगरBuCacheDataLoss		10
#घोषणा			AअगरBuCacheDataRecover	11

#घोषणा		AअगरCmdJobProgress	2	/* Progress report */
#घोषणा			AअगरJobCtrZero	101	/* Array Zero progress */
#घोषणा			AअगरJobStsSuccess 1	/* Job completes */
#घोषणा			AअगरJobStsRunning 102	/* Job running */
#घोषणा		AअगरCmdAPIReport		3	/* Report from other user of API */
#घोषणा		AअगरCmdDriverNotअगरy	4	/* Notअगरy host driver of event */
#घोषणा			AअगरDenMorphComplete 200	/* A morph operation completed */
#घोषणा			AअगरDenVolumeExtendComplete 201 /* A volume extend completed */
#घोषणा		AअगरReqJobList		100	/* Gets back complete job list */
#घोषणा		AअगरReqJobsForCtr	101	/* Gets back jobs क्रम specअगरic container */
#घोषणा		AअगरReqJobsForScsi	102	/* Gets back jobs क्रम specअगरic SCSI device */
#घोषणा		AअगरReqJobReport		103	/* Gets back a specअगरic job report or list of them */
#घोषणा		AअगरReqTerminateJob	104	/* Terminates job */
#घोषणा		AअगरReqSuspendJob	105	/* Suspends a job */
#घोषणा		AअगरReqResumeJob		106	/* Resumes a job */
#घोषणा		AअगरReqSendAPIReport	107	/* API generic report requests */
#घोषणा		AअगरReqAPIJobStart	108	/* Start a job from the API */
#घोषणा		AअगरReqAPIJobUpdate	109	/* Update a job report from the API */
#घोषणा		AअगरReqAPIJobFinish	110	/* Finish a job from the API */

/* PMC NEW COMM: Request the event data */
#घोषणा		AअगरReqEvent		200
#घोषणा		AअगरRawDeviceRemove	203	/* RAW device deleted */
#घोषणा		AअगरNativeDeviceAdd	204	/* native HBA device added */
#घोषणा		AअगरNativeDeviceRemove	205	/* native HBA device हटाओd */


/*
 *	Adapter Initiated FIB command काष्ठाures. Start with the adapter
 *	initiated FIBs that really come from the adapter, and get responded
 *	to by the host.
 */

काष्ठा aac_aअगरcmd अणु
	__le32 command;		/* Tell host what type of notअगरy this is */
	__le32 seqnum;		/* To allow ordering of reports (अगर necessary) */
	u8 data[1];		/* Undefined length (from kernel viewpoपूर्णांक) */
पूर्ण;

/**
 *	Convert capacity to cylinders
 *	accounting क्रम the fact capacity could be a 64 bit value
 *
 */
अटल अंतरभूत अचिन्हित पूर्णांक cap_to_cyls(sector_t capacity, अचिन्हित भागisor)
अणु
	sector_भाग(capacity, भागisor);
	वापस capacity;
पूर्ण

अटल अंतरभूत पूर्णांक aac_pci_offline(काष्ठा aac_dev *dev)
अणु
	वापस pci_channel_offline(dev->pdev) || dev->handle_pci_error;
पूर्ण

अटल अंतरभूत पूर्णांक aac_adapter_check_health(काष्ठा aac_dev *dev)
अणु
	अगर (unlikely(aac_pci_offline(dev)))
		वापस -1;

	वापस (dev)->a_ops.adapter_check_health(dev);
पूर्ण


पूर्णांक aac_scan_host(काष्ठा aac_dev *dev);

अटल अंतरभूत व्योम aac_schedule_safw_scan_worker(काष्ठा aac_dev *dev)
अणु
	schedule_delayed_work(&dev->safw_rescan_work, AAC_RESCAN_DELAY);
पूर्ण

अटल अंतरभूत व्योम aac_schedule_src_reinit_aअगर_worker(काष्ठा aac_dev *dev)
अणु
	schedule_delayed_work(&dev->src_reinit_aअगर_worker, AAC_RESCAN_DELAY);
पूर्ण

अटल अंतरभूत व्योम aac_safw_rescan_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aac_dev *dev = container_of(to_delayed_work(work),
		काष्ठा aac_dev, safw_rescan_work);

	रुको_event(dev->scsi_host_ptr->host_रुको,
		!scsi_host_in_recovery(dev->scsi_host_ptr));

	aac_scan_host(dev);
पूर्ण

अटल अंतरभूत व्योम aac_cancel_rescan_worker(काष्ठा aac_dev *dev)
अणु
	cancel_delayed_work_sync(&dev->safw_rescan_work);
	cancel_delayed_work_sync(&dev->src_reinit_aअगर_worker);
पूर्ण

/* SCp.phase values */
#घोषणा AAC_OWNER_MIDLEVEL	0x101
#घोषणा AAC_OWNER_LOWLEVEL	0x102
#घोषणा AAC_OWNER_ERROR_HANDLER	0x103
#घोषणा AAC_OWNER_FIRMWARE	0x106

व्योम aac_safw_rescan_worker(काष्ठा work_काष्ठा *work);
व्योम aac_src_reinit_aअगर_worker(काष्ठा work_काष्ठा *work);
पूर्णांक aac_acquire_irq(काष्ठा aac_dev *dev);
व्योम aac_मुक्त_irq(काष्ठा aac_dev *dev);
पूर्णांक aac_setup_safw_adapter(काष्ठा aac_dev *dev);
स्थिर अक्षर *aac_driverinfo(काष्ठा Scsi_Host *);
व्योम aac_fib_vector_assign(काष्ठा aac_dev *dev);
काष्ठा fib *aac_fib_alloc(काष्ठा aac_dev *dev);
काष्ठा fib *aac_fib_alloc_tag(काष्ठा aac_dev *dev, काष्ठा scsi_cmnd *scmd);
पूर्णांक aac_fib_setup(काष्ठा aac_dev *dev);
व्योम aac_fib_map_मुक्त(काष्ठा aac_dev *dev);
व्योम aac_fib_मुक्त(काष्ठा fib * context);
व्योम aac_fib_init(काष्ठा fib * context);
व्योम aac_म_लिखो(काष्ठा aac_dev *dev, u32 val);
पूर्णांक aac_fib_send(u16 command, काष्ठा fib * context, अचिन्हित दीर्घ size, पूर्णांक priority, पूर्णांक रुको, पूर्णांक reply, fib_callback callback, व्योम *ctxt);
पूर्णांक aac_hba_send(u8 command, काष्ठा fib *context,
		fib_callback callback, व्योम *ctxt);
पूर्णांक aac_consumer_get(काष्ठा aac_dev * dev, काष्ठा aac_queue * q, काष्ठा aac_entry **entry);
व्योम aac_consumer_मुक्त(काष्ठा aac_dev * dev, काष्ठा aac_queue * q, u32 qnum);
पूर्णांक aac_fib_complete(काष्ठा fib * context);
व्योम aac_hba_callback(व्योम *context, काष्ठा fib *fibptr);
#घोषणा fib_data(fibctx) ((व्योम *)(fibctx)->hw_fib_va->data)
काष्ठा aac_dev *aac_init_adapter(काष्ठा aac_dev *dev);
व्योम aac_src_access_devreg(काष्ठा aac_dev *dev, पूर्णांक mode);
व्योम aac_set_पूर्णांकx_mode(काष्ठा aac_dev *dev);
पूर्णांक aac_get_config_status(काष्ठा aac_dev *dev, पूर्णांक commit_flag);
पूर्णांक aac_get_containers(काष्ठा aac_dev *dev);
पूर्णांक aac_scsi_cmd(काष्ठा scsi_cmnd *cmd);
पूर्णांक aac_dev_ioctl(काष्ठा aac_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
#अगर_अघोषित shost_to_class
#घोषणा shost_to_class(shost) &shost->shost_dev
#पूर्ण_अगर
sमाप_प्रकार aac_get_serial_number(काष्ठा device *dev, अक्षर *buf);
पूर्णांक aac_करो_ioctl(काष्ठा aac_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg);
पूर्णांक aac_rx_init(काष्ठा aac_dev *dev);
पूर्णांक aac_rkt_init(काष्ठा aac_dev *dev);
पूर्णांक aac_nark_init(काष्ठा aac_dev *dev);
पूर्णांक aac_sa_init(काष्ठा aac_dev *dev);
पूर्णांक aac_src_init(काष्ठा aac_dev *dev);
पूर्णांक aac_srcv_init(काष्ठा aac_dev *dev);
पूर्णांक aac_queue_get(काष्ठा aac_dev * dev, u32 * index, u32 qid, काष्ठा hw_fib * hw_fib, पूर्णांक रुको, काष्ठा fib * fibptr, अचिन्हित दीर्घ *nonotअगरy);
व्योम aac_define_पूर्णांक_mode(काष्ठा aac_dev *dev);
अचिन्हित पूर्णांक aac_response_normal(काष्ठा aac_queue * q);
अचिन्हित पूर्णांक aac_command_normal(काष्ठा aac_queue * q);
अचिन्हित पूर्णांक aac_पूर्णांकr_normal(काष्ठा aac_dev *dev, u32 Index,
			पूर्णांक isAअगर, पूर्णांक isFastResponse,
			काष्ठा hw_fib *aअगर_fib);
पूर्णांक aac_reset_adapter(काष्ठा aac_dev *dev, पूर्णांक क्रमced, u8 reset_type);
पूर्णांक aac_check_health(काष्ठा aac_dev * dev);
पूर्णांक aac_command_thपढ़ो(व्योम *data);
पूर्णांक aac_बंद_fib_context(काष्ठा aac_dev * dev, काष्ठा aac_fib_context *fibctx);
पूर्णांक aac_fib_adapter_complete(काष्ठा fib * fibptr, अचिन्हित लघु size);
काष्ठा aac_driver_ident* aac_get_driver_ident(पूर्णांक devtype);
पूर्णांक aac_get_adapter_info(काष्ठा aac_dev* dev);
पूर्णांक aac_send_shutकरोwn(काष्ठा aac_dev *dev);
पूर्णांक aac_probe_container(काष्ठा aac_dev *dev, पूर्णांक cid);
पूर्णांक _aac_rx_init(काष्ठा aac_dev *dev);
पूर्णांक aac_rx_select_comm(काष्ठा aac_dev *dev, पूर्णांक comm);
पूर्णांक aac_rx_deliver_producer(काष्ठा fib * fib);
व्योम aac_reinit_aअगर(काष्ठा aac_dev *aac, अचिन्हित पूर्णांक index);

अटल अंतरभूत पूर्णांक aac_is_src(काष्ठा aac_dev *dev)
अणु
	u16 device = dev->pdev->device;

	अगर (device == PMC_DEVICE_S6 ||
		device == PMC_DEVICE_S7 ||
		device == PMC_DEVICE_S8)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक aac_supports_2T(काष्ठा aac_dev *dev)
अणु
	वापस (dev->adapter_info.options & AAC_OPT_NEW_COMM_64);
पूर्ण

अक्षर * get_container_type(अचिन्हित type);
बाह्य पूर्णांक numacb;
बाह्य अक्षर aac_driver_version[];
बाह्य पूर्णांक startup_समयout;
बाह्य पूर्णांक aअगर_समयout;
बाह्य पूर्णांक expose_physicals;
बाह्य पूर्णांक aac_reset_devices;
बाह्य पूर्णांक aac_msi;
बाह्य पूर्णांक aac_commit;
बाह्य पूर्णांक update_पूर्णांकerval;
बाह्य पूर्णांक check_पूर्णांकerval;
बाह्य पूर्णांक aac_check_reset;
बाह्य पूर्णांक aac_fib_dump;
#पूर्ण_अगर
