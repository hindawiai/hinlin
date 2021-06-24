<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश <linux/firmware.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा SD_INIT1_FIRMWARE "ene-ub6250/sd_init1.bin"
#घोषणा SD_INIT2_FIRMWARE "ene-ub6250/sd_init2.bin"
#घोषणा SD_RW_FIRMWARE "ene-ub6250/sd_rdwr.bin"
#घोषणा MS_INIT_FIRMWARE "ene-ub6250/ms_init.bin"
#घोषणा MSP_RW_FIRMWARE "ene-ub6250/msp_rdwr.bin"
#घोषणा MS_RW_FIRMWARE "ene-ub6250/ms_rdwr.bin"

#घोषणा DRV_NAME "ums_eneub6250"

MODULE_DESCRIPTION("Driver for ENE UB6250 reader");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);
MODULE_FIRMWARE(SD_INIT1_FIRMWARE);
MODULE_FIRMWARE(SD_INIT2_FIRMWARE);
MODULE_FIRMWARE(SD_RW_FIRMWARE);
MODULE_FIRMWARE(MS_INIT_FIRMWARE);
MODULE_FIRMWARE(MSP_RW_FIRMWARE);
MODULE_FIRMWARE(MS_RW_FIRMWARE);

/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
	.driver_info = (flags)पूर्ण

अटल काष्ठा usb_device_id ene_ub6250_usb_ids[] = अणु
#	include "unusual_ene_ub6250.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, ene_ub6250_usb_ids);

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

अटल काष्ठा us_unusual_dev ene_ub6250_unusual_dev_list[] = अणु
#	include "unusual_ene_ub6250.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV



/* ENE bin code len */
#घोषणा ENE_BIN_CODE_LEN    0x800
/* EnE HW Register */
#घोषणा REG_CARD_STATUS     0xFF83
#घोषणा REG_HW_TRAP1        0xFF89

/* SRB Status */
#घोषणा SS_SUCCESS		0x000000	/* No Sense */
#घोषणा SS_NOT_READY		0x023A00	/* Medium not present */
#घोषणा SS_MEDIUM_ERR		0x031100	/* Unrecovered पढ़ो error */
#घोषणा SS_HW_ERR		0x040800	/* Communication failure */
#घोषणा SS_ILLEGAL_REQUEST	0x052000	/* Invalid command */
#घोषणा SS_UNIT_ATTENTION	0x062900	/* Reset occurred */

/* ENE Load FW Pattern */
#घोषणा SD_INIT1_PATTERN   1
#घोषणा SD_INIT2_PATTERN   2
#घोषणा SD_RW_PATTERN      3
#घोषणा MS_INIT_PATTERN    4
#घोषणा MSP_RW_PATTERN     5
#घोषणा MS_RW_PATTERN      6
#घोषणा SM_INIT_PATTERN    7
#घोषणा SM_RW_PATTERN      8

#घोषणा Fसूची_WRITE         0
#घोषणा Fसूची_READ          1

/* For MS Card */

/* Status Register 1 */
#घोषणा MS_REG_ST1_MB           0x80    /* media busy */
#घोषणा MS_REG_ST1_FB1          0x40    /* flush busy 1 */
#घोषणा MS_REG_ST1_DTER         0x20    /* error on data(corrected) */
#घोषणा MS_REG_ST1_UCDT         0x10    /* unable to correct data */
#घोषणा MS_REG_ST1_EXER         0x08    /* error on extra(corrected) */
#घोषणा MS_REG_ST1_UCEX         0x04    /* unable to correct extra */
#घोषणा MS_REG_ST1_FGER         0x02    /* error on overग_लिखो flag(corrected) */
#घोषणा MS_REG_ST1_UCFG         0x01    /* unable to correct overग_लिखो flag */
#घोषणा MS_REG_ST1_DEFAULT	(MS_REG_ST1_MB | MS_REG_ST1_FB1 | MS_REG_ST1_DTER | MS_REG_ST1_UCDT | MS_REG_ST1_EXER | MS_REG_ST1_UCEX | MS_REG_ST1_FGER | MS_REG_ST1_UCFG)

/* Overग_लिखो Area */
#घोषणा MS_REG_OVR_BKST		0x80            /* block status */
#घोषणा MS_REG_OVR_BKST_OK	MS_REG_OVR_BKST     /* OK */
#घोषणा MS_REG_OVR_BKST_NG	0x00            /* NG */
#घोषणा MS_REG_OVR_PGST0	0x40            /* page status */
#घोषणा MS_REG_OVR_PGST1	0x20
#घोषणा MS_REG_OVR_PGST_MASK	(MS_REG_OVR_PGST0 | MS_REG_OVR_PGST1)
#घोषणा MS_REG_OVR_PGST_OK	(MS_REG_OVR_PGST0 | MS_REG_OVR_PGST1) /* OK */
#घोषणा MS_REG_OVR_PGST_NG	MS_REG_OVR_PGST1                      /* NG */
#घोषणा MS_REG_OVR_PGST_DATA_ERROR	0x00        /* data error */
#घोषणा MS_REG_OVR_UDST			0x10        /* update status */
#घोषणा MS_REG_OVR_UDST_UPDATING	0x00        /* updating */
#घोषणा MS_REG_OVR_UDST_NO_UPDATE	MS_REG_OVR_UDST
#घोषणा MS_REG_OVR_RESERVED	0x08
#घोषणा MS_REG_OVR_DEFAULT	(MS_REG_OVR_BKST_OK | MS_REG_OVR_PGST_OK | MS_REG_OVR_UDST_NO_UPDATE | MS_REG_OVR_RESERVED)

/* Management Flag */
#घोषणा MS_REG_MNG_SCMS0	0x20    /* serial copy management प्रणाली */
#घोषणा MS_REG_MNG_SCMS1	0x10
#घोषणा MS_REG_MNG_SCMS_MASK		(MS_REG_MNG_SCMS0 | MS_REG_MNG_SCMS1)
#घोषणा MS_REG_MNG_SCMS_COPY_OK		(MS_REG_MNG_SCMS0 | MS_REG_MNG_SCMS1)
#घोषणा MS_REG_MNG_SCMS_ONE_COPY	MS_REG_MNG_SCMS1
#घोषणा MS_REG_MNG_SCMS_NO_COPY	0x00
#घोषणा MS_REG_MNG_ATFLG	0x08    /* address transfer table flag */
#घोषणा MS_REG_MNG_ATFLG_OTHER	MS_REG_MNG_ATFLG    /* other */
#घोषणा MS_REG_MNG_ATFLG_ATTBL	0x00	/* address transfer table */
#घोषणा MS_REG_MNG_SYSFLG	0x04	/* प्रणाली flag */
#घोषणा MS_REG_MNG_SYSFLG_USER	MS_REG_MNG_SYSFLG   /* user block */
#घोषणा MS_REG_MNG_SYSFLG_BOOT	0x00	/* प्रणाली block */
#घोषणा MS_REG_MNG_RESERVED	0xc3
#घोषणा MS_REG_MNG_DEFAULT	(MS_REG_MNG_SCMS_COPY_OK | MS_REG_MNG_ATFLG_OTHER | MS_REG_MNG_SYSFLG_USER | MS_REG_MNG_RESERVED)


#घोषणा MS_MAX_PAGES_PER_BLOCK		32
#घोषणा MS_MAX_INITIAL_ERROR_BLOCKS 	10
#घोषणा MS_LIB_BITS_PER_BYTE		8

#घोषणा MS_SYSINF_FORMAT_FAT		1
#घोषणा MS_SYSINF_USAGE_GENERAL		0

#घोषणा MS_SYSINF_MSCLASS_TYPE_1	1
#घोषणा MS_SYSINF_PAGE_SIZE		MS_BYTES_PER_PAGE /* fixed */

#घोषणा MS_SYSINF_CARDTYPE_RDONLY	1
#घोषणा MS_SYSINF_CARDTYPE_RDWR		2
#घोषणा MS_SYSINF_CARDTYPE_HYBRID	3
#घोषणा MS_SYSINF_SECURITY		0x01
#घोषणा MS_SYSINF_SECURITY_NO_SUPPORT	MS_SYSINF_SECURITY
#घोषणा MS_SYSINF_SECURITY_SUPPORT	0

#घोषणा MS_SYSINF_RESERVED1		1
#घोषणा MS_SYSINF_RESERVED2		1

#घोषणा MS_SYSENT_TYPE_INVALID_BLOCK	0x01
#घोषणा MS_SYSENT_TYPE_CIS_IDI		0x0a    /* CIS/IDI */

#घोषणा SIZE_OF_KIRO		1024
#घोषणा BYTE_MASK		0xff

/* ms error code */
#घोषणा MS_STATUS_WRITE_PROTECT	0x0106
#घोषणा MS_STATUS_SUCCESS	0x0000
#घोषणा MS_ERROR_FLASH_READ	0x8003
#घोषणा MS_ERROR_FLASH_ERASE	0x8005
#घोषणा MS_LB_ERROR		0xfff0
#घोषणा MS_LB_BOOT_BLOCK	0xfff1
#घोषणा MS_LB_INITIAL_ERROR	0xfff2
#घोषणा MS_STATUS_SUCCESS_WITH_ECC 0xfff3
#घोषणा MS_LB_ACQUIRED_ERROR	0xfff4
#घोषणा MS_LB_NOT_USED_ERASED	0xfff5
#घोषणा MS_NOCARD_ERROR		0xfff8
#घोषणा MS_NO_MEMORY_ERROR	0xfff9
#घोषणा MS_STATUS_INT_ERROR	0xfffa
#घोषणा MS_STATUS_ERROR		0xfffe
#घोषणा MS_LB_NOT_USED		0xffff

#घोषणा MS_REG_MNG_SYSFLG	0x04    /* प्रणाली flag */
#घोषणा MS_REG_MNG_SYSFLG_USER	MS_REG_MNG_SYSFLG   /* user block */

#घोषणा MS_BOOT_BLOCK_ID                        0x0001
#घोषणा MS_BOOT_BLOCK_FORMAT_VERSION            0x0100
#घोषणा MS_BOOT_BLOCK_DATA_ENTRIES              2

#घोषणा MS_NUMBER_OF_SYSTEM_ENTRY       	4
#घोषणा MS_NUMBER_OF_BOOT_BLOCK			2
#घोषणा MS_BYTES_PER_PAGE			512
#घोषणा MS_LOGICAL_BLOCKS_PER_SEGMENT		496
#घोषणा MS_LOGICAL_BLOCKS_IN_1ST_SEGMENT        494

#घोषणा MS_PHYSICAL_BLOCKS_PER_SEGMENT		0x200 /* 512 */
#घोषणा MS_PHYSICAL_BLOCKS_PER_SEGMENT_MASK     0x1ff

/* overग_लिखो area */
#घोषणा MS_REG_OVR_BKST		0x80		/* block status */
#घोषणा MS_REG_OVR_BKST_OK	MS_REG_OVR_BKST	/* OK */
#घोषणा MS_REG_OVR_BKST_NG	0x00            /* NG */

/* Status Register 1 */
#घोषणा MS_REG_ST1_DTER		0x20	/* error on data(corrected) */
#घोषणा MS_REG_ST1_EXER		0x08	/* error on extra(corrected) */
#घोषणा MS_REG_ST1_FGER		0x02	/* error on overग_लिखो flag(corrected) */

/* MemoryStick Register */
/* Status Register 0 */
#घोषणा MS_REG_ST0_WP		0x01	/* ग_लिखो रक्षित */
#घोषणा MS_REG_ST0_WP_ON	MS_REG_ST0_WP

#घोषणा MS_LIB_CTRL_RDONLY      0
#घोषणा MS_LIB_CTRL_WRPROTECT   1

/*dphy->log table */
#घोषणा ms_libconv_to_logical(pdx, PhyBlock) (((PhyBlock) >= (pdx)->MS_Lib.NumberOfPhyBlock) ? MS_STATUS_ERROR : (pdx)->MS_Lib.Phy2LogMap[PhyBlock])
#घोषणा ms_libconv_to_physical(pdx, LogBlock) (((LogBlock) >= (pdx)->MS_Lib.NumberOfLogBlock) ? MS_STATUS_ERROR : (pdx)->MS_Lib.Log2PhyMap[LogBlock])

#घोषणा ms_lib_ctrl_set(pdx, Flag)	((pdx)->MS_Lib.flags |= (1 << (Flag)))
#घोषणा ms_lib_ctrl_reset(pdx, Flag)	((pdx)->MS_Lib.flags &= ~(1 << (Flag)))
#घोषणा ms_lib_ctrl_check(pdx, Flag)	((pdx)->MS_Lib.flags & (1 << (Flag)))

#घोषणा ms_lib_iswritable(pdx) ((ms_lib_ctrl_check((pdx), MS_LIB_CTRL_RDONLY) == 0) && (ms_lib_ctrl_check(pdx, MS_LIB_CTRL_WRPROTECT) == 0))
#घोषणा ms_lib_clear_pagemap(pdx) स_रखो((pdx)->MS_Lib.pagemap, 0, माप((pdx)->MS_Lib.pagemap))
#घोषणा memstick_logaddr(logadr1, logadr0) ((((u16)(logadr1)) << 8) | (logadr0))


काष्ठा SD_STATUS अणु
	u8    Insert:1;
	u8    Ready:1;
	u8    MediaChange:1;
	u8    IsMMC:1;
	u8    HiCapacity:1;
	u8    HiSpeed:1;
	u8    WtP:1;
	u8    Reserved:1;
पूर्ण;

काष्ठा MS_STATUS अणु
	u8    Insert:1;
	u8    Ready:1;
	u8    MediaChange:1;
	u8    IsMSPro:1;
	u8    IsMSPHG:1;
	u8    Reserved1:1;
	u8    WtP:1;
	u8    Reserved2:1;
पूर्ण;

काष्ठा SM_STATUS अणु
	u8    Insert:1;
	u8    Ready:1;
	u8    MediaChange:1;
	u8    Reserved:3;
	u8    WtP:1;
	u8    IsMS:1;
पूर्ण;

काष्ठा ms_bootblock_cis अणु
	u8 bCistplDEVICE[6];    /* 0 */
	u8 bCistplDEVICE0C[6];  /* 6 */
	u8 bCistplJEDECC[4];    /* 12 */
	u8 bCistplMANFID[6];    /* 16 */
	u8 bCistplVER1[32];     /* 22 */
	u8 bCistplFUNCID[4];    /* 54 */
	u8 bCistplFUNCE0[4];    /* 58 */
	u8 bCistplFUNCE1[5];    /* 62 */
	u8 bCistplCONF[7];      /* 67 */
	u8 bCistplCFTBLENT0[10];/* 74 */
	u8 bCistplCFTBLENT1[8]; /* 84 */
	u8 bCistplCFTBLENT2[12];/* 92 */
	u8 bCistplCFTBLENT3[8]; /* 104 */
	u8 bCistplCFTBLENT4[17];/* 112 */
	u8 bCistplCFTBLENT5[8]; /* 129 */
	u8 bCistplCFTBLENT6[17];/* 137 */
	u8 bCistplCFTBLENT7[8]; /* 154 */
	u8 bCistplNOLINK[3];    /* 162 */
पूर्ण ;

काष्ठा ms_bootblock_idi अणु
#घोषणा MS_IDI_GENERAL_CONF 0x848A
	u16 wIDIgeneralConfiguration;	/* 0 */
	u16 wIDInumberOfCylinder;	/* 1 */
	u16 wIDIreserved0;		/* 2 */
	u16 wIDInumberOfHead;		/* 3 */
	u16 wIDIbytesPerTrack;		/* 4 */
	u16 wIDIbytesPerSector;		/* 5 */
	u16 wIDIsectorsPerTrack;	/* 6 */
	u16 wIDItotalSectors[2];	/* 7-8  high,low */
	u16 wIDIreserved1[11];		/* 9-19 */
	u16 wIDIbufferType;		/* 20 */
	u16 wIDIbufferSize;		/* 21 */
	u16 wIDIदीर्घCmdECC;		/* 22 */
	u16 wIDIfirmVersion[4];		/* 23-26 */
	u16 wIDImodelName[20];		/* 27-46 */
	u16 wIDIreserved2;		/* 47 */
	u16 wIDIदीर्घWordSupported;	/* 48 */
	u16 wIDIdmaSupported;		/* 49 */
	u16 wIDIreserved3;		/* 50 */
	u16 wIDIpioTiming;		/* 51 */
	u16 wIDIdmaTiming;		/* 52 */
	u16 wIDItransferParameter;	/* 53 */
	u16 wIDIक्रमmattedCylinder;	/* 54 */
	u16 wIDIक्रमmattedHead;		/* 55 */
	u16 wIDIक्रमmattedSectorsPerTrack;/* 56 */
	u16 wIDIक्रमmattedTotalSectors[2];/* 57-58 */
	u16 wIDImultiSector;		/* 59 */
	u16 wIDIlbaSectors[2];		/* 60-61 */
	u16 wIDIsingleWordDMA;		/* 62 */
	u16 wIDImultiWordDMA;		/* 63 */
	u16 wIDIreserved4[192];		/* 64-255 */
पूर्ण;

काष्ठा ms_bootblock_sysent_rec अणु
	u32 dwStart;
	u32 dwSize;
	u8 bType;
	u8 bReserved[3];
पूर्ण;

काष्ठा ms_bootblock_sysent अणु
	काष्ठा ms_bootblock_sysent_rec entry[MS_NUMBER_OF_SYSTEM_ENTRY];
पूर्ण;

काष्ठा ms_bootblock_sysinf अणु
	u8 bMsClass;			/* must be 1 */
	u8 bCardType;			/* see below */
	u16 wBlockSize;			/* n KB */
	u16 wBlockNumber;		/* number of physical block */
	u16 wTotalBlockNumber;		/* number of logical block */
	u16 wPageSize;			/* must be 0x200 */
	u8 bExtraSize;			/* 0x10 */
	u8 bSecuritySupport;
	u8 bAssemblyDate[8];
	u8 bFactoryArea[4];
	u8 bAssemblyMakerCode;
	u8 bAssemblyMachineCode[3];
	u16 wMemoryMakerCode;
	u16 wMemoryDeviceCode;
	u16 wMemorySize;
	u8 bReserved1;
	u8 bReserved2;
	u8 bVCC;
	u8 bVPP;
	u16 wControllerChipNumber;
	u16 wControllerFunction;	/* New MS */
	u8 bReserved3[9];		/* New MS */
	u8 bParallelSupport;		/* New MS */
	u16 wFormatValue;		/* New MS */
	u8 bFormatType;
	u8 bUsage;
	u8 bDeviceType;
	u8 bReserved4[22];
	u8 bFUValue3;
	u8 bFUValue4;
	u8 bReserved5[15];
पूर्ण;

काष्ठा ms_bootblock_header अणु
	u16 wBlockID;
	u16 wFormatVersion;
	u8 bReserved1[184];
	u8 bNumberOfDataEntry;
	u8 bReserved2[179];
पूर्ण;

काष्ठा ms_bootblock_page0 अणु
	काष्ठा ms_bootblock_header header;
	काष्ठा ms_bootblock_sysent sysent;
	काष्ठा ms_bootblock_sysinf sysinf;
पूर्ण;

काष्ठा ms_bootblock_cis_idi अणु
	जोड़ अणु
		काष्ठा ms_bootblock_cis cis;
		u8 dmy[256];
	पूर्ण cis;

	जोड़ अणु
		काष्ठा ms_bootblock_idi idi;
		u8 dmy[256];
	पूर्ण idi;

पूर्ण;

/* ENE MS Lib काष्ठा */
काष्ठा ms_lib_type_extdat अणु
	u8 reserved;
	u8 पूर्णांकr;
	u8 status0;
	u8 status1;
	u8 ovrflg;
	u8 mngflg;
	u16 logadr;
पूर्ण;

काष्ठा ms_lib_ctrl अणु
	u32 flags;
	u32 BytesPerSector;
	u32 NumberOfCylinder;
	u32 SectorsPerCylinder;
	u16 cardType;			/* R/W, RO, Hybrid */
	u16 blockSize;
	u16 PagesPerBlock;
	u16 NumberOfPhyBlock;
	u16 NumberOfLogBlock;
	u16 NumberOfSegment;
	u16 *Phy2LogMap;		/* phy2log table */
	u16 *Log2PhyMap;		/* log2phy table */
	u16 wrtblk;
	अचिन्हित अक्षर *pagemap[(MS_MAX_PAGES_PER_BLOCK + (MS_LIB_BITS_PER_BYTE-1)) / MS_LIB_BITS_PER_BYTE];
	अचिन्हित अक्षर *blkpag;
	काष्ठा ms_lib_type_extdat *blkext;
	अचिन्हित अक्षर copybuf[512];
पूर्ण;


/* SD Block Length */
/* 2^9 = 512 Bytes, The HW maximum पढ़ो/ग_लिखो data length */
#घोषणा SD_BLOCK_LEN  9

काष्ठा ene_ub6250_info अणु

	/* I/O bounce buffer */
	u8		*bbuf;

	/* क्रम 6250 code */
	काष्ठा SD_STATUS	SD_Status;
	काष्ठा MS_STATUS	MS_Status;
	काष्ठा SM_STATUS	SM_Status;

	/* ----- SD Control Data ---------------- */
	/*SD_REGISTER SD_Regs; */
	u16		SD_Block_Mult;
	u8		SD_READ_BL_LEN;
	u16		SD_C_SIZE;
	u8		SD_C_SIZE_MULT;

	/* SD/MMC New spec. */
	u8		SD_SPEC_VER;
	u8		SD_CSD_VER;
	u8		SD20_HIGH_CAPACITY;
	u32		HC_C_SIZE;
	u8		MMC_SPEC_VER;
	u8		MMC_BusWidth;
	u8		MMC_HIGH_CAPACITY;

	/*----- MS Control Data ---------------- */
	bool		MS_SWWP;
	u32		MSP_TotalBlock;
	काष्ठा ms_lib_ctrl MS_Lib;
	bool		MS_IsRWPage;
	u16		MS_Model;

	/*----- SM Control Data ---------------- */
	u8		SM_DeviceID;
	u8		SM_CardID;

	अचिन्हित अक्षर	*testbuf;
	u8		BIN_FLAG;
	u32		bl_num;
	पूर्णांक		SrbStatus;

	/*------Power Managerment ---------------*/
	bool		Power_IsResum;
पूर्ण;

अटल पूर्णांक ene_sd_init(काष्ठा us_data *us);
अटल पूर्णांक ene_ms_init(काष्ठा us_data *us);
अटल पूर्णांक ene_load_bincode(काष्ठा us_data *us, अचिन्हित अक्षर flag);

अटल व्योम ene_ub6250_info_deकाष्ठाor(व्योम *extra)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) extra;

	अगर (!extra)
		वापस;
	kमुक्त(info->bbuf);
पूर्ण

अटल पूर्णांक ene_send_scsi_cmd(काष्ठा us_data *us, u8 fDir, व्योम *buf, पूर्णांक use_sg)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा bulk_cs_wrap *bcs = (काष्ठा bulk_cs_wrap *) us->iobuf;

	पूर्णांक result;
	अचिन्हित पूर्णांक residue;
	अचिन्हित पूर्णांक cswlen = 0, partial = 0;
	अचिन्हित पूर्णांक transfer_length = bcb->DataTransferLength;

	/* usb_stor_dbg(us, "transport --- ene_send_scsi_cmd\n"); */
	/* send cmd to out endpoपूर्णांक */
	result = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
					    bcb, US_BULK_CB_WRAP_LEN, शून्य);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "send cmd to out endpoint fail ---\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	अगर (buf) अणु
		अचिन्हित पूर्णांक pipe = fDir;

		अगर (fDir  == Fसूची_READ)
			pipe = us->recv_bulk_pipe;
		अन्यथा
			pipe = us->send_bulk_pipe;

		/* Bulk */
		अगर (use_sg) अणु
			result = usb_stor_bulk_srb(us, pipe, us->srb);
		पूर्ण अन्यथा अणु
			result = usb_stor_bulk_transfer_sg(us, pipe, buf,
						transfer_length, 0, &partial);
		पूर्ण
		अगर (result != USB_STOR_XFER_GOOD) अणु
			usb_stor_dbg(us, "data transfer fail ---\n");
			वापस USB_STOR_TRANSPORT_ERROR;
		पूर्ण
	पूर्ण

	/* Get CSW क्रम device status */
	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe, bcs,
					    US_BULK_CS_WRAP_LEN, &cswlen);

	अगर (result == USB_STOR_XFER_SHORT && cswlen == 0) अणु
		usb_stor_dbg(us, "Received 0-length CSW; retrying...\n");
		result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
					    bcs, US_BULK_CS_WRAP_LEN, &cswlen);
	पूर्ण

	अगर (result == USB_STOR_XFER_STALLED) अणु
		/* get the status again */
		usb_stor_dbg(us, "Attempting to get CSW (2nd try)...\n");
		result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
						bcs, US_BULK_CS_WRAP_LEN, शून्य);
	पूर्ण

	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* check bulk status */
	residue = le32_to_cpu(bcs->Residue);

	/*
	 * try to compute the actual residue, based on how much data
	 * was really transferred and what the device tells us
	 */
	अगर (residue && !(us->fflags & US_FL_IGNORE_RESIDUE)) अणु
		residue = min(residue, transfer_length);
		अगर (us->srb != शून्य)
			scsi_set_resid(us->srb, max(scsi_get_resid(us->srb),
								residue));
	पूर्ण

	अगर (bcs->Status != US_BULK_STAT_OK)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक करो_scsi_request_sense(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	अचिन्हित अक्षर buf[18];

	स_रखो(buf, 0, 18);
	buf[0] = 0x70;				/* Current error */
	buf[2] = info->SrbStatus >> 16;		/* Sense key */
	buf[7] = 10;				/* Additional length */
	buf[12] = info->SrbStatus >> 8;		/* ASC */
	buf[13] = info->SrbStatus;		/* ASCQ */

	usb_stor_set_xfer_buf(buf, माप(buf), srb);
	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक करो_scsi_inquiry(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	अचिन्हित अक्षर data_ptr[36] = अणु
		0x00, 0x00, 0x02, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x55,
		0x53, 0x42, 0x32, 0x2E, 0x30, 0x20, 0x20, 0x43, 0x61,
		0x72, 0x64, 0x52, 0x65, 0x61, 0x64, 0x65, 0x72, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30 पूर्ण;

	usb_stor_set_xfer_buf(data_ptr, 36, srb);
	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक sd_scsi_test_unit_पढ़ोy(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर (info->SD_Status.Insert && info->SD_Status.Ready)
		वापस USB_STOR_TRANSPORT_GOOD;
	अन्यथा अणु
		ene_sd_init(us);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक sd_scsi_mode_sense(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	अचिन्हित अक्षर mediaNoWP[12] = अणु
		0x0b, 0x00, 0x00, 0x08, 0x00, 0x00,
		0x71, 0xc0, 0x00, 0x00, 0x02, 0x00 पूर्ण;
	अचिन्हित अक्षर mediaWP[12]   = अणु
		0x0b, 0x00, 0x80, 0x08, 0x00, 0x00,
		0x71, 0xc0, 0x00, 0x00, 0x02, 0x00 पूर्ण;

	अगर (info->SD_Status.WtP)
		usb_stor_set_xfer_buf(mediaWP, 12, srb);
	अन्यथा
		usb_stor_set_xfer_buf(mediaNoWP, 12, srb);


	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक sd_scsi_पढ़ो_capacity(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	u32	bl_num;
	u32	bl_len;
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित अक्षर    buf[8];
	काष्ठा scatterlist *sg = शून्य;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	usb_stor_dbg(us, "sd_scsi_read_capacity\n");
	अगर (info->SD_Status.HiCapacity) अणु
		bl_len = 0x200;
		अगर (info->SD_Status.IsMMC)
			bl_num = info->HC_C_SIZE-1;
		अन्यथा
			bl_num = (info->HC_C_SIZE + 1) * 1024 - 1;
	पूर्ण अन्यथा अणु
		bl_len = 1 << (info->SD_READ_BL_LEN);
		bl_num = info->SD_Block_Mult * (info->SD_C_SIZE + 1)
				* (1 << (info->SD_C_SIZE_MULT + 2)) - 1;
	पूर्ण
	info->bl_num = bl_num;
	usb_stor_dbg(us, "bl_len = %x\n", bl_len);
	usb_stor_dbg(us, "bl_num = %x\n", bl_num);

	/*srb->request_bufflen = 8; */
	buf[0] = (bl_num >> 24) & 0xff;
	buf[1] = (bl_num >> 16) & 0xff;
	buf[2] = (bl_num >> 8) & 0xff;
	buf[3] = (bl_num >> 0) & 0xff;
	buf[4] = (bl_len >> 24) & 0xff;
	buf[5] = (bl_len >> 16) & 0xff;
	buf[6] = (bl_len >> 8) & 0xff;
	buf[7] = (bl_len >> 0) & 0xff;

	usb_stor_access_xfer_buf(buf, 8, srb, &sg, &offset, TO_XFER_BUF);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक sd_scsi_पढ़ो(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *cdb = srb->cmnd;
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	u32 bn = ((cdb[2] << 24) & 0xff000000) | ((cdb[3] << 16) & 0x00ff0000) |
		 ((cdb[4] << 8) & 0x0000ff00) | ((cdb[5] << 0) & 0x000000ff);
	u16 blen = ((cdb[7] << 8) & 0xff00) | ((cdb[8] << 0) & 0x00ff);
	u32 bnByte = bn * 0x200;
	u32 blenByte = blen * 0x200;

	अगर (bn > info->bl_num)
		वापस USB_STOR_TRANSPORT_ERROR;

	result = ene_load_bincode(us, SD_RW_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Load SD RW pattern Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	अगर (info->SD_Status.HiCapacity)
		bnByte = bn;

	/* set up the command wrapper */
	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = blenByte;
	bcb->Flags  = US_BULK_FLAG_IN;
	bcb->CDB[0] = 0xF1;
	bcb->CDB[5] = (अचिन्हित अक्षर)(bnByte);
	bcb->CDB[4] = (अचिन्हित अक्षर)(bnByte>>8);
	bcb->CDB[3] = (अचिन्हित अक्षर)(bnByte>>16);
	bcb->CDB[2] = (अचिन्हित अक्षर)(bnByte>>24);

	result = ene_send_scsi_cmd(us, Fसूची_READ, scsi_sglist(srb), 1);
	वापस result;
पूर्ण

अटल पूर्णांक sd_scsi_ग_लिखो(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *cdb = srb->cmnd;
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	u32 bn = ((cdb[2] << 24) & 0xff000000) | ((cdb[3] << 16) & 0x00ff0000) |
		 ((cdb[4] << 8) & 0x0000ff00) | ((cdb[5] << 0) & 0x000000ff);
	u16 blen = ((cdb[7] << 8) & 0xff00) | ((cdb[8] << 0) & 0x00ff);
	u32 bnByte = bn * 0x200;
	u32 blenByte = blen * 0x200;

	अगर (bn > info->bl_num)
		वापस USB_STOR_TRANSPORT_ERROR;

	result = ene_load_bincode(us, SD_RW_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Load SD RW pattern Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	अगर (info->SD_Status.HiCapacity)
		bnByte = bn;

	/* set up the command wrapper */
	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = blenByte;
	bcb->Flags  = 0x00;
	bcb->CDB[0] = 0xF0;
	bcb->CDB[5] = (अचिन्हित अक्षर)(bnByte);
	bcb->CDB[4] = (अचिन्हित अक्षर)(bnByte>>8);
	bcb->CDB[3] = (अचिन्हित अक्षर)(bnByte>>16);
	bcb->CDB[2] = (अचिन्हित अक्षर)(bnByte>>24);

	result = ene_send_scsi_cmd(us, Fसूची_WRITE, scsi_sglist(srb), 1);
	वापस result;
पूर्ण

/*
 * ENE MS Card
 */

अटल पूर्णांक ms_lib_set_logicalpair(काष्ठा us_data *us, u16 logblk, u16 phyblk)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर ((logblk >= info->MS_Lib.NumberOfLogBlock) || (phyblk >= info->MS_Lib.NumberOfPhyBlock))
		वापस (u32)-1;

	info->MS_Lib.Phy2LogMap[phyblk] = logblk;
	info->MS_Lib.Log2PhyMap[logblk] = phyblk;

	वापस 0;
पूर्ण

अटल पूर्णांक ms_lib_set_logicalblockmark(काष्ठा us_data *us, u16 phyblk, u16 mark)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर (phyblk >= info->MS_Lib.NumberOfPhyBlock)
		वापस (u32)-1;

	info->MS_Lib.Phy2LogMap[phyblk] = mark;

	वापस 0;
पूर्ण

अटल पूर्णांक ms_lib_set_initialerrorblock(काष्ठा us_data *us, u16 phyblk)
अणु
	वापस ms_lib_set_logicalblockmark(us, phyblk, MS_LB_INITIAL_ERROR);
पूर्ण

अटल पूर्णांक ms_lib_set_bootblockmark(काष्ठा us_data *us, u16 phyblk)
अणु
	वापस ms_lib_set_logicalblockmark(us, phyblk, MS_LB_BOOT_BLOCK);
पूर्ण

अटल पूर्णांक ms_lib_मुक्त_logicalmap(काष्ठा us_data *us)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	kमुक्त(info->MS_Lib.Phy2LogMap);
	info->MS_Lib.Phy2LogMap = शून्य;

	kमुक्त(info->MS_Lib.Log2PhyMap);
	info->MS_Lib.Log2PhyMap = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक ms_lib_alloc_logicalmap(काष्ठा us_data *us)
अणु
	u32  i;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	info->MS_Lib.Phy2LogMap = kदो_स्मृति_array(info->MS_Lib.NumberOfPhyBlock,
						माप(u16),
						GFP_KERNEL);
	info->MS_Lib.Log2PhyMap = kदो_स्मृति_array(info->MS_Lib.NumberOfLogBlock,
						माप(u16),
						GFP_KERNEL);

	अगर ((info->MS_Lib.Phy2LogMap == शून्य) || (info->MS_Lib.Log2PhyMap == शून्य)) अणु
		ms_lib_मुक्त_logicalmap(us);
		वापस (u32)-1;
	पूर्ण

	क्रम (i = 0; i < info->MS_Lib.NumberOfPhyBlock; i++)
		info->MS_Lib.Phy2LogMap[i] = MS_LB_NOT_USED;

	क्रम (i = 0; i < info->MS_Lib.NumberOfLogBlock; i++)
		info->MS_Lib.Log2PhyMap[i] = MS_LB_NOT_USED;

	वापस 0;
पूर्ण

अटल व्योम ms_lib_clear_ग_लिखोbuf(काष्ठा us_data *us)
अणु
	पूर्णांक i;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	info->MS_Lib.wrtblk = (u16)-1;
	ms_lib_clear_pagemap(info);

	अगर (info->MS_Lib.blkpag)
		स_रखो(info->MS_Lib.blkpag, 0xff, info->MS_Lib.PagesPerBlock * info->MS_Lib.BytesPerSector);

	अगर (info->MS_Lib.blkext) अणु
		क्रम (i = 0; i < info->MS_Lib.PagesPerBlock; i++) अणु
			info->MS_Lib.blkext[i].status1 = MS_REG_ST1_DEFAULT;
			info->MS_Lib.blkext[i].ovrflg = MS_REG_OVR_DEFAULT;
			info->MS_Lib.blkext[i].mngflg = MS_REG_MNG_DEFAULT;
			info->MS_Lib.blkext[i].logadr = MS_LB_NOT_USED;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ms_count_मुक्तblock(काष्ठा us_data *us, u16 PhyBlock)
अणु
	u32 Ende, Count;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	Ende = PhyBlock + MS_PHYSICAL_BLOCKS_PER_SEGMENT;
	क्रम (Count = 0; PhyBlock < Ende; PhyBlock++) अणु
		चयन (info->MS_Lib.Phy2LogMap[PhyBlock]) अणु
		हाल MS_LB_NOT_USED:
		हाल MS_LB_NOT_USED_ERASED:
			Count++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस Count;
पूर्ण

अटल पूर्णांक ms_पढ़ो_पढ़ोpage(काष्ठा us_data *us, u32 PhyBlockAddr,
		u8 PageNum, u32 *PageBuf, काष्ठा ms_lib_type_extdat *ExtraDat)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;
	पूर्णांक result;
	u32 bn = PhyBlockAddr * 0x20 + PageNum;

	result = ene_load_bincode(us, MS_RW_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* Read Page Data */
	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags      = US_BULK_FLAG_IN;
	bcb->CDB[0]     = 0xF1;

	bcb->CDB[1]     = 0x02; /* in init.c ENE_MSInit() is 0x01 */

	bcb->CDB[5]     = (अचिन्हित अक्षर)(bn);
	bcb->CDB[4]     = (अचिन्हित अक्षर)(bn>>8);
	bcb->CDB[3]     = (अचिन्हित अक्षर)(bn>>16);
	bcb->CDB[2]     = (अचिन्हित अक्षर)(bn>>24);

	result = ene_send_scsi_cmd(us, Fसूची_READ, PageBuf, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;


	/* Read Extra Data */
	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x4;
	bcb->Flags      = US_BULK_FLAG_IN;
	bcb->CDB[0]     = 0xF1;
	bcb->CDB[1]     = 0x03;

	bcb->CDB[5]     = (अचिन्हित अक्षर)(PageNum);
	bcb->CDB[4]     = (अचिन्हित अक्षर)(PhyBlockAddr);
	bcb->CDB[3]     = (अचिन्हित अक्षर)(PhyBlockAddr>>8);
	bcb->CDB[2]     = (अचिन्हित अक्षर)(PhyBlockAddr>>16);
	bcb->CDB[6]     = 0x01;

	result = ene_send_scsi_cmd(us, Fसूची_READ, bbuf, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	ExtraDat->reserved = 0;
	ExtraDat->पूर्णांकr     = 0x80;  /* Not yet,fireware support */
	ExtraDat->status0  = 0x10;  /* Not yet,fireware support */

	ExtraDat->status1  = 0x00;  /* Not yet,fireware support */
	ExtraDat->ovrflg   = bbuf[0];
	ExtraDat->mngflg   = bbuf[1];
	ExtraDat->logadr   = memstick_logaddr(bbuf[2], bbuf[3]);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_lib_process_bootblock(काष्ठा us_data *us, u16 PhyBlock, u8 *PageData)
अणु
	काष्ठा ms_bootblock_sysent *SysEntry;
	काष्ठा ms_bootblock_sysinf *SysInfo;
	u32 i, result;
	u8 PageNumber;
	u8 *PageBuffer;
	काष्ठा ms_lib_type_extdat ExtraData;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	PageBuffer = kदो_स्मृति(MS_BYTES_PER_PAGE, GFP_KERNEL);
	अगर (PageBuffer == शून्य)
		वापस (u32)-1;

	result = (u32)-1;

	SysInfo = &(((काष्ठा ms_bootblock_page0 *)PageData)->sysinf);

	अगर ((SysInfo->bMsClass != MS_SYSINF_MSCLASS_TYPE_1) ||
		(be16_to_cpu(SysInfo->wPageSize) != MS_SYSINF_PAGE_SIZE) ||
		((SysInfo->bSecuritySupport & MS_SYSINF_SECURITY) == MS_SYSINF_SECURITY_SUPPORT) ||
		(SysInfo->bReserved1 != MS_SYSINF_RESERVED1) ||
		(SysInfo->bReserved2 != MS_SYSINF_RESERVED2) ||
		(SysInfo->bFormatType != MS_SYSINF_FORMAT_FAT) ||
		(SysInfo->bUsage != MS_SYSINF_USAGE_GENERAL))
		जाओ निकास;
		/* */
	चयन (info->MS_Lib.cardType = SysInfo->bCardType) अणु
	हाल MS_SYSINF_CARDTYPE_RDONLY:
		ms_lib_ctrl_set(info, MS_LIB_CTRL_RDONLY);
		अवरोध;
	हाल MS_SYSINF_CARDTYPE_RDWR:
		ms_lib_ctrl_reset(info, MS_LIB_CTRL_RDONLY);
		अवरोध;
	हाल MS_SYSINF_CARDTYPE_HYBRID:
	शेष:
		जाओ निकास;
	पूर्ण

	info->MS_Lib.blockSize = be16_to_cpu(SysInfo->wBlockSize);
	info->MS_Lib.NumberOfPhyBlock = be16_to_cpu(SysInfo->wBlockNumber);
	info->MS_Lib.NumberOfLogBlock = be16_to_cpu(SysInfo->wTotalBlockNumber)-2;
	info->MS_Lib.PagesPerBlock = info->MS_Lib.blockSize * SIZE_OF_KIRO / MS_BYTES_PER_PAGE;
	info->MS_Lib.NumberOfSegment = info->MS_Lib.NumberOfPhyBlock / MS_PHYSICAL_BLOCKS_PER_SEGMENT;
	info->MS_Model = be16_to_cpu(SysInfo->wMemorySize);

	/*Allocate to all number of logicalblock and physicalblock */
	अगर (ms_lib_alloc_logicalmap(us))
		जाओ निकास;

	/* Mark the book block */
	ms_lib_set_bootblockmark(us, PhyBlock);

	SysEntry = &(((काष्ठा ms_bootblock_page0 *)PageData)->sysent);

	क्रम (i = 0; i < MS_NUMBER_OF_SYSTEM_ENTRY; i++) अणु
		u32  EntryOffset, EntrySize;

		EntryOffset = be32_to_cpu(SysEntry->entry[i].dwStart);

		अगर (EntryOffset == 0xffffff)
			जारी;
		EntrySize = be32_to_cpu(SysEntry->entry[i].dwSize);

		अगर (EntrySize == 0)
			जारी;

		अगर (EntryOffset + MS_BYTES_PER_PAGE + EntrySize > info->MS_Lib.blockSize * (u32)SIZE_OF_KIRO)
			जारी;

		अगर (i == 0) अणु
			u8 PrevPageNumber = 0;
			u16 phyblk;

			अगर (SysEntry->entry[i].bType != MS_SYSENT_TYPE_INVALID_BLOCK)
				जाओ निकास;

			जबतक (EntrySize > 0) अणु

				PageNumber = (u8)(EntryOffset / MS_BYTES_PER_PAGE + 1);
				अगर (PageNumber != PrevPageNumber) अणु
					चयन (ms_पढ़ो_पढ़ोpage(us, PhyBlock, PageNumber, (u32 *)PageBuffer, &ExtraData)) अणु
					हाल MS_STATUS_SUCCESS:
						अवरोध;
					हाल MS_STATUS_WRITE_PROTECT:
					हाल MS_ERROR_FLASH_READ:
					हाल MS_STATUS_ERROR:
					शेष:
						जाओ निकास;
					पूर्ण

					PrevPageNumber = PageNumber;
				पूर्ण

				phyblk = be16_to_cpu(*(u16 *)(PageBuffer + (EntryOffset % MS_BYTES_PER_PAGE)));
				अगर (phyblk < 0x0fff)
					ms_lib_set_initialerrorblock(us, phyblk);

				EntryOffset += 2;
				EntrySize -= 2;
			पूर्ण
		पूर्ण अन्यथा अगर (i == 1) अणु  /* CIS/IDI */
			काष्ठा ms_bootblock_idi *idi;

			अगर (SysEntry->entry[i].bType != MS_SYSENT_TYPE_CIS_IDI)
				जाओ निकास;

			चयन (ms_पढ़ो_पढ़ोpage(us, PhyBlock, (u8)(EntryOffset / MS_BYTES_PER_PAGE + 1), (u32 *)PageBuffer, &ExtraData)) अणु
			हाल MS_STATUS_SUCCESS:
				अवरोध;
			हाल MS_STATUS_WRITE_PROTECT:
			हाल MS_ERROR_FLASH_READ:
			हाल MS_STATUS_ERROR:
			शेष:
				जाओ निकास;
			पूर्ण

			idi = &((काष्ठा ms_bootblock_cis_idi *)(PageBuffer + (EntryOffset % MS_BYTES_PER_PAGE)))->idi.idi;
			अगर (le16_to_cpu(idi->wIDIgeneralConfiguration) != MS_IDI_GENERAL_CONF)
				जाओ निकास;

			info->MS_Lib.BytesPerSector = le16_to_cpu(idi->wIDIbytesPerSector);
			अगर (info->MS_Lib.BytesPerSector != MS_BYTES_PER_PAGE)
				जाओ निकास;
		पूर्ण
	पूर्ण /* End क्रम .. */

	result = 0;

निकास:
	अगर (result)
		ms_lib_मुक्त_logicalmap(us);

	kमुक्त(PageBuffer);

	result = 0;
	वापस result;
पूर्ण

अटल व्योम ms_lib_मुक्त_ग_लिखोbuf(काष्ठा us_data *us)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	info->MS_Lib.wrtblk = (u16)-1; /* set to -1 */

	/* स_रखो((fकरोExt)->MS_Lib.pagemap, 0, माप((fकरोExt)->MS_Lib.pagemap)) */

	ms_lib_clear_pagemap(info); /* (pdx)->MS_Lib.pagemap स_रखो 0 in ms.h */

	अगर (info->MS_Lib.blkpag) अणु
		kमुक्त(info->MS_Lib.blkpag);  /* Arnold test ... */
		info->MS_Lib.blkpag = शून्य;
	पूर्ण

	अगर (info->MS_Lib.blkext) अणु
		kमुक्त(info->MS_Lib.blkext);  /* Arnold test ... */
		info->MS_Lib.blkext = शून्य;
	पूर्ण
पूर्ण


अटल व्योम ms_lib_मुक्त_allocatedarea(काष्ठा us_data *us)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	ms_lib_मुक्त_ग_लिखोbuf(us); /* Free MS_Lib.pagemap */
	ms_lib_मुक्त_logicalmap(us); /* kमुक्त MS_Lib.Phy2LogMap and MS_Lib.Log2PhyMap */

	/* set काष्ठा us poपूर्णांक flag to 0 */
	info->MS_Lib.flags = 0;
	info->MS_Lib.BytesPerSector = 0;
	info->MS_Lib.SectorsPerCylinder = 0;

	info->MS_Lib.cardType = 0;
	info->MS_Lib.blockSize = 0;
	info->MS_Lib.PagesPerBlock = 0;

	info->MS_Lib.NumberOfPhyBlock = 0;
	info->MS_Lib.NumberOfLogBlock = 0;
पूर्ण


अटल पूर्णांक ms_lib_alloc_ग_लिखोbuf(काष्ठा us_data *us)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	info->MS_Lib.wrtblk = (u16)-1;

	info->MS_Lib.blkpag = kदो_स्मृति_array(info->MS_Lib.PagesPerBlock,
					    info->MS_Lib.BytesPerSector,
					    GFP_KERNEL);
	info->MS_Lib.blkext = kदो_स्मृति_array(info->MS_Lib.PagesPerBlock,
					    माप(काष्ठा ms_lib_type_extdat),
					    GFP_KERNEL);

	अगर ((info->MS_Lib.blkpag == शून्य) || (info->MS_Lib.blkext == शून्य)) अणु
		ms_lib_मुक्त_ग_लिखोbuf(us);
		वापस (u32)-1;
	पूर्ण

	ms_lib_clear_ग_लिखोbuf(us);

	वापस 0;
पूर्ण

अटल पूर्णांक ms_lib_क्रमce_setlogical_pair(काष्ठा us_data *us, u16 logblk, u16 phyblk)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर (logblk == MS_LB_NOT_USED)
		वापस 0;

	अगर ((logblk >= info->MS_Lib.NumberOfLogBlock) ||
		(phyblk >= info->MS_Lib.NumberOfPhyBlock))
		वापस (u32)-1;

	info->MS_Lib.Phy2LogMap[phyblk] = logblk;
	info->MS_Lib.Log2PhyMap[logblk] = phyblk;

	वापस 0;
पूर्ण

अटल पूर्णांक ms_पढ़ो_copyblock(काष्ठा us_data *us, u16 oldphy, u16 newphy,
			u16 PhyBlockAddr, u8 PageNum, अचिन्हित अक्षर *buf, u16 len)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	पूर्णांक result;

	result = ene_load_bincode(us, MS_RW_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200*len;
	bcb->Flags = 0x00;
	bcb->CDB[0] = 0xF0;
	bcb->CDB[1] = 0x08;
	bcb->CDB[4] = (अचिन्हित अक्षर)(oldphy);
	bcb->CDB[3] = (अचिन्हित अक्षर)(oldphy>>8);
	bcb->CDB[2] = 0; /* (BYTE)(oldphy>>16) */
	bcb->CDB[7] = (अचिन्हित अक्षर)(newphy);
	bcb->CDB[6] = (अचिन्हित अक्षर)(newphy>>8);
	bcb->CDB[5] = 0; /* (BYTE)(newphy>>16) */
	bcb->CDB[9] = (अचिन्हित अक्षर)(PhyBlockAddr);
	bcb->CDB[8] = (अचिन्हित अक्षर)(PhyBlockAddr>>8);
	bcb->CDB[10] = PageNum;

	result = ene_send_scsi_cmd(us, Fसूची_WRITE, buf, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_पढ़ो_eraseblock(काष्ठा us_data *us, u32 PhyBlockAddr)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	पूर्णांक result;
	u32 bn = PhyBlockAddr;

	result = ene_load_bincode(us, MS_RW_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags = US_BULK_FLAG_IN;
	bcb->CDB[0] = 0xF2;
	bcb->CDB[1] = 0x06;
	bcb->CDB[4] = (अचिन्हित अक्षर)(bn);
	bcb->CDB[3] = (अचिन्हित अक्षर)(bn>>8);
	bcb->CDB[2] = (अचिन्हित अक्षर)(bn>>16);

	result = ene_send_scsi_cmd(us, Fसूची_READ, शून्य, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_lib_check_disableblock(काष्ठा us_data *us, u16 PhyBlock)
अणु
	अचिन्हित अक्षर *PageBuf = शून्य;
	u16 result = MS_STATUS_SUCCESS;
	u16 blk, index = 0;
	काष्ठा ms_lib_type_extdat extdat;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	PageBuf = kदो_स्मृति(MS_BYTES_PER_PAGE, GFP_KERNEL);
	अगर (PageBuf == शून्य) अणु
		result = MS_NO_MEMORY_ERROR;
		जाओ निकास;
	पूर्ण

	ms_पढ़ो_पढ़ोpage(us, PhyBlock, 1, (u32 *)PageBuf, &extdat);
	करो अणु
		blk = be16_to_cpu(PageBuf[index]);
		अगर (blk == MS_LB_NOT_USED)
			अवरोध;
		अगर (blk == info->MS_Lib.Log2PhyMap[0]) अणु
			result = MS_ERROR_FLASH_READ;
			अवरोध;
		पूर्ण
		index++;
	पूर्ण जबतक (1);

निकास:
	kमुक्त(PageBuf);
	वापस result;
पूर्ण

अटल पूर्णांक ms_lib_setacquired_errorblock(काष्ठा us_data *us, u16 phyblk)
अणु
	u16 log;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर (phyblk >= info->MS_Lib.NumberOfPhyBlock)
		वापस (u32)-1;

	log = info->MS_Lib.Phy2LogMap[phyblk];

	अगर (log < info->MS_Lib.NumberOfLogBlock)
		info->MS_Lib.Log2PhyMap[log] = MS_LB_NOT_USED;

	अगर (info->MS_Lib.Phy2LogMap[phyblk] != MS_LB_INITIAL_ERROR)
		info->MS_Lib.Phy2LogMap[phyblk] = MS_LB_ACQUIRED_ERROR;

	वापस 0;
पूर्ण

अटल पूर्णांक ms_lib_overग_लिखो_extra(काष्ठा us_data *us, u32 PhyBlockAddr,
				u8 PageNum, u8 Overग_लिखोFlag)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	पूर्णांक result;

	result = ene_load_bincode(us, MS_RW_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x4;
	bcb->Flags = US_BULK_FLAG_IN;
	bcb->CDB[0] = 0xF2;
	bcb->CDB[1] = 0x05;
	bcb->CDB[5] = (अचिन्हित अक्षर)(PageNum);
	bcb->CDB[4] = (अचिन्हित अक्षर)(PhyBlockAddr);
	bcb->CDB[3] = (अचिन्हित अक्षर)(PhyBlockAddr>>8);
	bcb->CDB[2] = (अचिन्हित अक्षर)(PhyBlockAddr>>16);
	bcb->CDB[6] = Overग_लिखोFlag;
	bcb->CDB[7] = 0xFF;
	bcb->CDB[8] = 0xFF;
	bcb->CDB[9] = 0xFF;

	result = ene_send_scsi_cmd(us, Fसूची_READ, शून्य, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_lib_error_phyblock(काष्ठा us_data *us, u16 phyblk)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर (phyblk >= info->MS_Lib.NumberOfPhyBlock)
		वापस MS_STATUS_ERROR;

	ms_lib_setacquired_errorblock(us, phyblk);

	अगर (ms_lib_iswritable(info))
		वापस ms_lib_overग_लिखो_extra(us, phyblk, 0, (u8)(~MS_REG_OVR_BKST & BYTE_MASK));

	वापस MS_STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_lib_erase_phyblock(काष्ठा us_data *us, u16 phyblk)
अणु
	u16 log;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर (phyblk >= info->MS_Lib.NumberOfPhyBlock)
		वापस MS_STATUS_ERROR;

	log = info->MS_Lib.Phy2LogMap[phyblk];

	अगर (log < info->MS_Lib.NumberOfLogBlock)
		info->MS_Lib.Log2PhyMap[log] = MS_LB_NOT_USED;

	info->MS_Lib.Phy2LogMap[phyblk] = MS_LB_NOT_USED;

	अगर (ms_lib_iswritable(info)) अणु
		चयन (ms_पढ़ो_eraseblock(us, phyblk)) अणु
		हाल MS_STATUS_SUCCESS:
			info->MS_Lib.Phy2LogMap[phyblk] = MS_LB_NOT_USED_ERASED;
			वापस MS_STATUS_SUCCESS;
		हाल MS_ERROR_FLASH_ERASE:
		हाल MS_STATUS_INT_ERROR:
			ms_lib_error_phyblock(us, phyblk);
			वापस MS_ERROR_FLASH_ERASE;
		हाल MS_STATUS_ERROR:
		शेष:
			ms_lib_ctrl_set(info, MS_LIB_CTRL_RDONLY); /* MS_LibCtrlSet will used by ENE_MSInit ,need check, and why us to info*/
			ms_lib_setacquired_errorblock(us, phyblk);
			वापस MS_STATUS_ERROR;
		पूर्ण
	पूर्ण

	ms_lib_setacquired_errorblock(us, phyblk);

	वापस MS_STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक ms_lib_पढ़ो_extra(काष्ठा us_data *us, u32 PhyBlock,
				u8 PageNum, काष्ठा ms_lib_type_extdat *ExtraDat)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;
	पूर्णांक result;

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x4;
	bcb->Flags      = US_BULK_FLAG_IN;
	bcb->CDB[0]     = 0xF1;
	bcb->CDB[1]     = 0x03;
	bcb->CDB[5]     = (अचिन्हित अक्षर)(PageNum);
	bcb->CDB[4]     = (अचिन्हित अक्षर)(PhyBlock);
	bcb->CDB[3]     = (अचिन्हित अक्षर)(PhyBlock>>8);
	bcb->CDB[2]     = (अचिन्हित अक्षर)(PhyBlock>>16);
	bcb->CDB[6]     = 0x01;

	result = ene_send_scsi_cmd(us, Fसूची_READ, bbuf, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	ExtraDat->reserved = 0;
	ExtraDat->पूर्णांकr     = 0x80;  /* Not yet, रुकोing क्रम fireware support */
	ExtraDat->status0  = 0x10;  /* Not yet, रुकोing क्रम fireware support */
	ExtraDat->status1  = 0x00;  /* Not yet, रुकोing क्रम fireware support */
	ExtraDat->ovrflg   = bbuf[0];
	ExtraDat->mngflg   = bbuf[1];
	ExtraDat->logadr   = memstick_logaddr(bbuf[2], bbuf[3]);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_liद्वा_खोज_block_from_physical(काष्ठा us_data *us, u16 phyblk)
अणु
	u16 blk;
	काष्ठा ms_lib_type_extdat extdat; /* need check */
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;


	अगर (phyblk >= info->MS_Lib.NumberOfPhyBlock)
		वापस MS_LB_ERROR;

	क्रम (blk = phyblk + 1; blk != phyblk; blk++) अणु
		अगर ((blk & MS_PHYSICAL_BLOCKS_PER_SEGMENT_MASK) == 0)
			blk -= MS_PHYSICAL_BLOCKS_PER_SEGMENT;

		अगर (info->MS_Lib.Phy2LogMap[blk] == MS_LB_NOT_USED_ERASED) अणु
			वापस blk;
		पूर्ण अन्यथा अगर (info->MS_Lib.Phy2LogMap[blk] == MS_LB_NOT_USED) अणु
			चयन (ms_lib_पढ़ो_extra(us, blk, 0, &extdat)) अणु
			हाल MS_STATUS_SUCCESS:
			हाल MS_STATUS_SUCCESS_WITH_ECC:
				अवरोध;
			हाल MS_NOCARD_ERROR:
				वापस MS_NOCARD_ERROR;
			हाल MS_STATUS_INT_ERROR:
				वापस MS_LB_ERROR;
			हाल MS_ERROR_FLASH_READ:
			शेष:
				ms_lib_setacquired_errorblock(us, blk);
				जारी;
			पूर्ण /* End चयन */

			अगर ((extdat.ovrflg & MS_REG_OVR_BKST) != MS_REG_OVR_BKST_OK) अणु
				ms_lib_setacquired_errorblock(us, blk);
				जारी;
			पूर्ण

			चयन (ms_lib_erase_phyblock(us, blk)) अणु
			हाल MS_STATUS_SUCCESS:
				वापस blk;
			हाल MS_STATUS_ERROR:
				वापस MS_LB_ERROR;
			हाल MS_ERROR_FLASH_ERASE:
			शेष:
				ms_lib_error_phyblock(us, blk);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण /* End क्रम */

	वापस MS_LB_ERROR;
पूर्ण
अटल पूर्णांक ms_liद्वा_खोज_block_from_logical(काष्ठा us_data *us, u16 logblk)
अणु
	u16 phyblk;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	phyblk = ms_libconv_to_physical(info, logblk);
	अगर (phyblk >= MS_LB_ERROR) अणु
		अगर (logblk >= info->MS_Lib.NumberOfLogBlock)
			वापस MS_LB_ERROR;

		phyblk = (logblk + MS_NUMBER_OF_BOOT_BLOCK) / MS_LOGICAL_BLOCKS_PER_SEGMENT;
		phyblk *= MS_PHYSICAL_BLOCKS_PER_SEGMENT;
		phyblk += MS_PHYSICAL_BLOCKS_PER_SEGMENT - 1;
	पूर्ण

	वापस ms_liद्वा_खोज_block_from_physical(us, phyblk);
पूर्ण

अटल पूर्णांक ms_scsi_test_unit_पढ़ोy(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *)(us->extra);

	/* pr_info("MS_SCSI_Test_Unit_Ready\n"); */
	अगर (info->MS_Status.Insert && info->MS_Status.Ready) अणु
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण अन्यथा अणु
		ene_ms_init(us);
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_scsi_mode_sense(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	अचिन्हित अक्षर mediaNoWP[12] = अणु
		0x0b, 0x00, 0x00, 0x08, 0x00, 0x00,
		0x71, 0xc0, 0x00, 0x00, 0x02, 0x00 पूर्ण;
	अचिन्हित अक्षर mediaWP[12]   = अणु
		0x0b, 0x00, 0x80, 0x08, 0x00, 0x00,
		0x71, 0xc0, 0x00, 0x00, 0x02, 0x00 पूर्ण;

	अगर (info->MS_Status.WtP)
		usb_stor_set_xfer_buf(mediaWP, 12, srb);
	अन्यथा
		usb_stor_set_xfer_buf(mediaNoWP, 12, srb);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_scsi_पढ़ो_capacity(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	u32   bl_num;
	u16    bl_len;
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित अक्षर    buf[8];
	काष्ठा scatterlist *sg = शून्य;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	usb_stor_dbg(us, "ms_scsi_read_capacity\n");
	bl_len = 0x200;
	अगर (info->MS_Status.IsMSPro)
		bl_num = info->MSP_TotalBlock - 1;
	अन्यथा
		bl_num = info->MS_Lib.NumberOfLogBlock * info->MS_Lib.blockSize * 2 - 1;

	info->bl_num = bl_num;
	usb_stor_dbg(us, "bl_len = %x\n", bl_len);
	usb_stor_dbg(us, "bl_num = %x\n", bl_num);

	/*srb->request_bufflen = 8; */
	buf[0] = (bl_num >> 24) & 0xff;
	buf[1] = (bl_num >> 16) & 0xff;
	buf[2] = (bl_num >> 8) & 0xff;
	buf[3] = (bl_num >> 0) & 0xff;
	buf[4] = (bl_len >> 24) & 0xff;
	buf[5] = (bl_len >> 16) & 0xff;
	buf[6] = (bl_len >> 8) & 0xff;
	buf[7] = (bl_len >> 0) & 0xff;

	usb_stor_access_xfer_buf(buf, 8, srb, &sg, &offset, TO_XFER_BUF);

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल व्योम ms_lib_phy_to_log_range(u16 PhyBlock, u16 *LogStart, u16 *LogEnde)
अणु
	PhyBlock /= MS_PHYSICAL_BLOCKS_PER_SEGMENT;

	अगर (PhyBlock) अणु
		*LogStart = MS_LOGICAL_BLOCKS_IN_1ST_SEGMENT + (PhyBlock - 1) * MS_LOGICAL_BLOCKS_PER_SEGMENT;/*496*/
		*LogEnde = *LogStart + MS_LOGICAL_BLOCKS_PER_SEGMENT;/*496*/
	पूर्ण अन्यथा अणु
		*LogStart = 0;
		*LogEnde = MS_LOGICAL_BLOCKS_IN_1ST_SEGMENT;/*494*/
	पूर्ण
पूर्ण

अटल पूर्णांक ms_lib_पढ़ो_extrablock(काष्ठा us_data *us, u32 PhyBlock,
	u8 PageNum, u8 blen, व्योम *buf)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	पूर्णांक     result;

	/* Read Extra Data */
	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x4 * blen;
	bcb->Flags      = US_BULK_FLAG_IN;
	bcb->CDB[0]     = 0xF1;
	bcb->CDB[1]     = 0x03;
	bcb->CDB[5]     = (अचिन्हित अक्षर)(PageNum);
	bcb->CDB[4]     = (अचिन्हित अक्षर)(PhyBlock);
	bcb->CDB[3]     = (अचिन्हित अक्षर)(PhyBlock>>8);
	bcb->CDB[2]     = (अचिन्हित अक्षर)(PhyBlock>>16);
	bcb->CDB[6]     = blen;

	result = ene_send_scsi_cmd(us, Fसूची_READ, buf, 0);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ms_lib_scan_logicalblocknumber(काष्ठा us_data *us, u16 btBlk1st)
अणु
	u16 PhyBlock, newblk, i;
	u16 LogStart, LogEnde;
	काष्ठा ms_lib_type_extdat extdat;
	u32 count = 0, index = 0;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;

	क्रम (PhyBlock = 0; PhyBlock < info->MS_Lib.NumberOfPhyBlock;) अणु
		ms_lib_phy_to_log_range(PhyBlock, &LogStart, &LogEnde);

		क्रम (i = 0; i < MS_PHYSICAL_BLOCKS_PER_SEGMENT; i++, PhyBlock++) अणु
			चयन (ms_libconv_to_logical(info, PhyBlock)) अणु
			हाल MS_STATUS_ERROR:
				जारी;
			शेष:
				अवरोध;
			पूर्ण

			अगर (count == PhyBlock) अणु
				ms_lib_पढ़ो_extrablock(us, PhyBlock, 0, 0x80,
						bbuf);
				count += 0x80;
			पूर्ण
			index = (PhyBlock % 0x80) * 4;

			extdat.ovrflg = bbuf[index];
			extdat.mngflg = bbuf[index+1];
			extdat.logadr = memstick_logaddr(bbuf[index+2],
					bbuf[index+3]);

			अगर ((extdat.ovrflg & MS_REG_OVR_BKST) != MS_REG_OVR_BKST_OK) अणु
				ms_lib_setacquired_errorblock(us, PhyBlock);
				जारी;
			पूर्ण

			अगर ((extdat.mngflg & MS_REG_MNG_ATFLG) == MS_REG_MNG_ATFLG_ATTBL) अणु
				ms_lib_erase_phyblock(us, PhyBlock);
				जारी;
			पूर्ण

			अगर (extdat.logadr != MS_LB_NOT_USED) अणु
				अगर ((extdat.logadr < LogStart) || (LogEnde <= extdat.logadr)) अणु
					ms_lib_erase_phyblock(us, PhyBlock);
					जारी;
				पूर्ण

				newblk = ms_libconv_to_physical(info, extdat.logadr);

				अगर (newblk != MS_LB_NOT_USED) अणु
					अगर (extdat.logadr == 0) अणु
						ms_lib_set_logicalpair(us, extdat.logadr, PhyBlock);
						अगर (ms_lib_check_disableblock(us, btBlk1st)) अणु
							ms_lib_set_logicalpair(us, extdat.logadr, newblk);
							जारी;
						पूर्ण
					पूर्ण

					ms_lib_पढ़ो_extra(us, newblk, 0, &extdat);
					अगर ((extdat.ovrflg & MS_REG_OVR_UDST) == MS_REG_OVR_UDST_UPDATING) अणु
						ms_lib_erase_phyblock(us, PhyBlock);
						जारी;
					पूर्ण अन्यथा अणु
						ms_lib_erase_phyblock(us, newblk);
					पूर्ण
				पूर्ण

				ms_lib_set_logicalpair(us, extdat.logadr, PhyBlock);
			पूर्ण
		पूर्ण
	पूर्ण /* End क्रम ... */

	वापस MS_STATUS_SUCCESS;
पूर्ण


अटल पूर्णांक ms_scsi_पढ़ो(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *cdb = srb->cmnd;
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	u32 bn = ((cdb[2] << 24) & 0xff000000) | ((cdb[3] << 16) & 0x00ff0000) |
		((cdb[4] << 8) & 0x0000ff00) | ((cdb[5] << 0) & 0x000000ff);
	u16 blen = ((cdb[7] << 8) & 0xff00) | ((cdb[8] << 0) & 0x00ff);
	u32 blenByte = blen * 0x200;

	अगर (bn > info->bl_num)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (info->MS_Status.IsMSPro) अणु
		result = ene_load_bincode(us, MSP_RW_PATTERN);
		अगर (result != USB_STOR_XFER_GOOD) अणु
			usb_stor_dbg(us, "Load MPS RW pattern Fail !!\n");
			वापस USB_STOR_TRANSPORT_ERROR;
		पूर्ण

		/* set up the command wrapper */
		स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
		bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
		bcb->DataTransferLength = blenByte;
		bcb->Flags  = US_BULK_FLAG_IN;
		bcb->CDB[0] = 0xF1;
		bcb->CDB[1] = 0x02;
		bcb->CDB[5] = (अचिन्हित अक्षर)(bn);
		bcb->CDB[4] = (अचिन्हित अक्षर)(bn>>8);
		bcb->CDB[3] = (अचिन्हित अक्षर)(bn>>16);
		bcb->CDB[2] = (अचिन्हित अक्षर)(bn>>24);

		result = ene_send_scsi_cmd(us, Fसूची_READ, scsi_sglist(srb), 1);
	पूर्ण अन्यथा अणु
		व्योम *buf;
		पूर्णांक offset = 0;
		u16 phyblk, logblk;
		u8 PageNum;
		u16 len;
		u32 blkno;

		buf = kदो_स्मृति(blenByte, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस USB_STOR_TRANSPORT_ERROR;

		result = ene_load_bincode(us, MS_RW_PATTERN);
		अगर (result != USB_STOR_XFER_GOOD) अणु
			pr_info("Load MS RW pattern Fail !!\n");
			result = USB_STOR_TRANSPORT_ERROR;
			जाओ निकास;
		पूर्ण

		logblk  = (u16)(bn / info->MS_Lib.PagesPerBlock);
		PageNum = (u8)(bn % info->MS_Lib.PagesPerBlock);

		जबतक (1) अणु
			अगर (blen > (info->MS_Lib.PagesPerBlock-PageNum))
				len = info->MS_Lib.PagesPerBlock-PageNum;
			अन्यथा
				len = blen;

			phyblk = ms_libconv_to_physical(info, logblk);
			blkno  = phyblk * 0x20 + PageNum;

			/* set up the command wrapper */
			स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
			bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
			bcb->DataTransferLength = 0x200 * len;
			bcb->Flags  = US_BULK_FLAG_IN;
			bcb->CDB[0] = 0xF1;
			bcb->CDB[1] = 0x02;
			bcb->CDB[5] = (अचिन्हित अक्षर)(blkno);
			bcb->CDB[4] = (अचिन्हित अक्षर)(blkno>>8);
			bcb->CDB[3] = (अचिन्हित अक्षर)(blkno>>16);
			bcb->CDB[2] = (अचिन्हित अक्षर)(blkno>>24);

			result = ene_send_scsi_cmd(us, Fसूची_READ, buf+offset, 0);
			अगर (result != USB_STOR_XFER_GOOD) अणु
				pr_info("MS_SCSI_Read --- result = %x\n", result);
				result = USB_STOR_TRANSPORT_ERROR;
				जाओ निकास;
			पूर्ण

			blen -= len;
			अगर (blen <= 0)
				अवरोध;
			logblk++;
			PageNum = 0;
			offset += MS_BYTES_PER_PAGE*len;
		पूर्ण
		usb_stor_set_xfer_buf(buf, blenByte, srb);
निकास:
		kमुक्त(buf);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक ms_scsi_ग_लिखो(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	पूर्णांक result;
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	अचिन्हित अक्षर *cdb = srb->cmnd;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	u32 bn = ((cdb[2] << 24) & 0xff000000) |
			((cdb[3] << 16) & 0x00ff0000) |
			((cdb[4] << 8) & 0x0000ff00) |
			((cdb[5] << 0) & 0x000000ff);
	u16 blen = ((cdb[7] << 8) & 0xff00) | ((cdb[8] << 0) & 0x00ff);
	u32 blenByte = blen * 0x200;

	अगर (bn > info->bl_num)
		वापस USB_STOR_TRANSPORT_ERROR;

	अगर (info->MS_Status.IsMSPro) अणु
		result = ene_load_bincode(us, MSP_RW_PATTERN);
		अगर (result != USB_STOR_XFER_GOOD) अणु
			pr_info("Load MSP RW pattern Fail !!\n");
			वापस USB_STOR_TRANSPORT_ERROR;
		पूर्ण

		/* set up the command wrapper */
		स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
		bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
		bcb->DataTransferLength = blenByte;
		bcb->Flags  = 0x00;
		bcb->CDB[0] = 0xF0;
		bcb->CDB[1] = 0x04;
		bcb->CDB[5] = (अचिन्हित अक्षर)(bn);
		bcb->CDB[4] = (अचिन्हित अक्षर)(bn>>8);
		bcb->CDB[3] = (अचिन्हित अक्षर)(bn>>16);
		bcb->CDB[2] = (अचिन्हित अक्षर)(bn>>24);

		result = ene_send_scsi_cmd(us, Fसूची_WRITE, scsi_sglist(srb), 1);
	पूर्ण अन्यथा अणु
		व्योम *buf;
		पूर्णांक offset = 0;
		u16 PhyBlockAddr;
		u8 PageNum;
		u16 len, oldphy, newphy;

		buf = kदो_स्मृति(blenByte, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस USB_STOR_TRANSPORT_ERROR;
		usb_stor_set_xfer_buf(buf, blenByte, srb);

		result = ene_load_bincode(us, MS_RW_PATTERN);
		अगर (result != USB_STOR_XFER_GOOD) अणु
			pr_info("Load MS RW pattern Fail !!\n");
			result = USB_STOR_TRANSPORT_ERROR;
			जाओ निकास;
		पूर्ण

		PhyBlockAddr = (u16)(bn / info->MS_Lib.PagesPerBlock);
		PageNum      = (u8)(bn % info->MS_Lib.PagesPerBlock);

		जबतक (1) अणु
			अगर (blen > (info->MS_Lib.PagesPerBlock-PageNum))
				len = info->MS_Lib.PagesPerBlock-PageNum;
			अन्यथा
				len = blen;

			oldphy = ms_libconv_to_physical(info, PhyBlockAddr); /* need check us <-> info */
			newphy = ms_liद्वा_खोज_block_from_logical(us, PhyBlockAddr);

			result = ms_पढ़ो_copyblock(us, oldphy, newphy, PhyBlockAddr, PageNum, buf+offset, len);

			अगर (result != USB_STOR_XFER_GOOD) अणु
				pr_info("MS_SCSI_Write --- result = %x\n", result);
				result =  USB_STOR_TRANSPORT_ERROR;
				जाओ निकास;
			पूर्ण

			info->MS_Lib.Phy2LogMap[oldphy] = MS_LB_NOT_USED_ERASED;
			ms_lib_क्रमce_setlogical_pair(us, PhyBlockAddr, newphy);

			blen -= len;
			अगर (blen <= 0)
				अवरोध;
			PhyBlockAddr++;
			PageNum = 0;
			offset += MS_BYTES_PER_PAGE*len;
		पूर्ण
निकास:
		kमुक्त(buf);
	पूर्ण
	वापस result;
पूर्ण

/*
 * ENE MS Card
 */

अटल पूर्णांक ene_get_card_type(काष्ठा us_data *us, u16 index, व्योम *buf)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	पूर्णांक result;

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength	= 0x01;
	bcb->Flags			= US_BULK_FLAG_IN;
	bcb->CDB[0]			= 0xED;
	bcb->CDB[2]			= (अचिन्हित अक्षर)(index>>8);
	bcb->CDB[3]			= (अचिन्हित अक्षर)index;

	result = ene_send_scsi_cmd(us, Fसूची_READ, buf, 0);
	वापस result;
पूर्ण

अटल पूर्णांक ene_get_card_status(काष्ठा us_data *us, u8 *buf)
अणु
	u16 पंचांगpreg;
	u32 reg4b;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	/*usb_stor_dbg(us, "transport --- ENE_ReadSDReg\n");*/
	reg4b = *(u32 *)&buf[0x18];
	info->SD_READ_BL_LEN = (u8)((reg4b >> 8) & 0x0f);

	पंचांगpreg = (u16) reg4b;
	reg4b = *(u32 *)(&buf[0x14]);
	अगर (info->SD_Status.HiCapacity && !info->SD_Status.IsMMC)
		info->HC_C_SIZE = (reg4b >> 8) & 0x3fffff;

	info->SD_C_SIZE = ((पंचांगpreg & 0x03) << 10) | (u16)(reg4b >> 22);
	info->SD_C_SIZE_MULT = (u8)(reg4b >> 7)  & 0x07;
	अगर (info->SD_Status.HiCapacity && info->SD_Status.IsMMC)
		info->HC_C_SIZE = *(u32 *)(&buf[0x100]);

	अगर (info->SD_READ_BL_LEN > SD_BLOCK_LEN) अणु
		info->SD_Block_Mult = 1 << (info->SD_READ_BL_LEN-SD_BLOCK_LEN);
		info->SD_READ_BL_LEN = SD_BLOCK_LEN;
	पूर्ण अन्यथा अणु
		info->SD_Block_Mult = 1;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ene_load_bincode(काष्ठा us_data *us, अचिन्हित अक्षर flag)
अणु
	पूर्णांक err;
	अक्षर *fw_name = शून्य;
	अचिन्हित अक्षर *buf = शून्य;
	स्थिर काष्ठा firmware *sd_fw = शून्य;
	पूर्णांक result = USB_STOR_TRANSPORT_ERROR;
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	अगर (info->BIN_FLAG == flag)
		वापस USB_STOR_TRANSPORT_GOOD;

	चयन (flag) अणु
	/* For SD */
	हाल SD_INIT1_PATTERN:
		usb_stor_dbg(us, "SD_INIT1_PATTERN\n");
		fw_name = SD_INIT1_FIRMWARE;
		अवरोध;
	हाल SD_INIT2_PATTERN:
		usb_stor_dbg(us, "SD_INIT2_PATTERN\n");
		fw_name = SD_INIT2_FIRMWARE;
		अवरोध;
	हाल SD_RW_PATTERN:
		usb_stor_dbg(us, "SD_RW_PATTERN\n");
		fw_name = SD_RW_FIRMWARE;
		अवरोध;
	/* For MS */
	हाल MS_INIT_PATTERN:
		usb_stor_dbg(us, "MS_INIT_PATTERN\n");
		fw_name = MS_INIT_FIRMWARE;
		अवरोध;
	हाल MSP_RW_PATTERN:
		usb_stor_dbg(us, "MSP_RW_PATTERN\n");
		fw_name = MSP_RW_FIRMWARE;
		अवरोध;
	हाल MS_RW_PATTERN:
		usb_stor_dbg(us, "MS_RW_PATTERN\n");
		fw_name = MS_RW_FIRMWARE;
		अवरोध;
	शेष:
		usb_stor_dbg(us, "----------- Unknown PATTERN ----------\n");
		जाओ nofw;
	पूर्ण

	err = request_firmware(&sd_fw, fw_name, &us->pusb_dev->dev);
	अगर (err) अणु
		usb_stor_dbg(us, "load firmware %s failed\n", fw_name);
		जाओ nofw;
	पूर्ण
	buf = kmemdup(sd_fw->data, sd_fw->size, GFP_KERNEL);
	अगर (buf == शून्य)
		जाओ nofw;

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = sd_fw->size;
	bcb->Flags = 0x00;
	bcb->CDB[0] = 0xEF;

	result = ene_send_scsi_cmd(us, Fसूची_WRITE, buf, 0);
	अगर (us->srb != शून्य)
		scsi_set_resid(us->srb, 0);
	info->BIN_FLAG = flag;
	kमुक्त(buf);

nofw:
	release_firmware(sd_fw);
	वापस result;
पूर्ण

अटल पूर्णांक ms_card_init(काष्ठा us_data *us)
अणु
	u32 result;
	u16 TmpBlock;
	अचिन्हित अक्षर *PageBuffer0 = शून्य, *PageBuffer1 = शून्य;
	काष्ठा ms_lib_type_extdat extdat;
	u16 btBlk1st, btBlk2nd;
	u32 btBlk1stErred;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;

	prपूर्णांकk(KERN_INFO "MS_CardInit start\n");

	ms_lib_मुक्त_allocatedarea(us); /* Clean buffer and set काष्ठा us_data flag to 0 */

	/* get two PageBuffer */
	PageBuffer0 = kदो_स्मृति(MS_BYTES_PER_PAGE, GFP_KERNEL);
	PageBuffer1 = kदो_स्मृति(MS_BYTES_PER_PAGE, GFP_KERNEL);
	अगर ((PageBuffer0 == शून्य) || (PageBuffer1 == शून्य)) अणु
		result = MS_NO_MEMORY_ERROR;
		जाओ निकास;
	पूर्ण

	btBlk1st = btBlk2nd = MS_LB_NOT_USED;
	btBlk1stErred = 0;

	क्रम (TmpBlock = 0; TmpBlock < MS_MAX_INITIAL_ERROR_BLOCKS+2; TmpBlock++) अणु

		चयन (ms_पढ़ो_पढ़ोpage(us, TmpBlock, 0, (u32 *)PageBuffer0, &extdat)) अणु
		हाल MS_STATUS_SUCCESS:
			अवरोध;
		हाल MS_STATUS_INT_ERROR:
			अवरोध;
		हाल MS_STATUS_ERROR:
		शेष:
			जारी;
		पूर्ण

		अगर ((extdat.ovrflg & MS_REG_OVR_BKST) == MS_REG_OVR_BKST_NG)
			जारी;

		अगर (((extdat.mngflg & MS_REG_MNG_SYSFLG) == MS_REG_MNG_SYSFLG_USER) ||
			(be16_to_cpu(((काष्ठा ms_bootblock_page0 *)PageBuffer0)->header.wBlockID) != MS_BOOT_BLOCK_ID) ||
			(be16_to_cpu(((काष्ठा ms_bootblock_page0 *)PageBuffer0)->header.wFormatVersion) != MS_BOOT_BLOCK_FORMAT_VERSION) ||
			(((काष्ठा ms_bootblock_page0 *)PageBuffer0)->header.bNumberOfDataEntry != MS_BOOT_BLOCK_DATA_ENTRIES))
				जारी;

		अगर (btBlk1st != MS_LB_NOT_USED) अणु
			btBlk2nd = TmpBlock;
			अवरोध;
		पूर्ण

		btBlk1st = TmpBlock;
		स_नकल(PageBuffer1, PageBuffer0, MS_BYTES_PER_PAGE);
		अगर (extdat.status1 & (MS_REG_ST1_DTER | MS_REG_ST1_EXER | MS_REG_ST1_FGER))
			btBlk1stErred = 1;
	पूर्ण

	अगर (btBlk1st == MS_LB_NOT_USED) अणु
		result = MS_STATUS_ERROR;
		जाओ निकास;
	पूर्ण

	/* ग_लिखो protect */
	अगर ((extdat.status0 & MS_REG_ST0_WP) == MS_REG_ST0_WP_ON)
		ms_lib_ctrl_set(info, MS_LIB_CTRL_WRPROTECT);

	result = MS_STATUS_ERROR;
	/* 1st Boot Block */
	अगर (btBlk1stErred == 0)
		result = ms_lib_process_bootblock(us, btBlk1st, PageBuffer1);
		/* 1st */
	/* 2nd Boot Block */
	अगर (result && (btBlk2nd != MS_LB_NOT_USED))
		result = ms_lib_process_bootblock(us, btBlk2nd, PageBuffer0);

	अगर (result) अणु
		result = MS_STATUS_ERROR;
		जाओ निकास;
	पूर्ण

	क्रम (TmpBlock = 0; TmpBlock < btBlk1st; TmpBlock++)
		info->MS_Lib.Phy2LogMap[TmpBlock] = MS_LB_INITIAL_ERROR;

	info->MS_Lib.Phy2LogMap[btBlk1st] = MS_LB_BOOT_BLOCK;

	अगर (btBlk2nd != MS_LB_NOT_USED) अणु
		क्रम (TmpBlock = btBlk1st + 1; TmpBlock < btBlk2nd; TmpBlock++)
			info->MS_Lib.Phy2LogMap[TmpBlock] = MS_LB_INITIAL_ERROR;

		info->MS_Lib.Phy2LogMap[btBlk2nd] = MS_LB_BOOT_BLOCK;
	पूर्ण

	result = ms_lib_scan_logicalblocknumber(us, btBlk1st);
	अगर (result)
		जाओ निकास;

	क्रम (TmpBlock = MS_PHYSICAL_BLOCKS_PER_SEGMENT;
		TmpBlock < info->MS_Lib.NumberOfPhyBlock;
		TmpBlock += MS_PHYSICAL_BLOCKS_PER_SEGMENT) अणु
		अगर (ms_count_मुक्तblock(us, TmpBlock) == 0) अणु
			ms_lib_ctrl_set(info, MS_LIB_CTRL_WRPROTECT);
			अवरोध;
		पूर्ण
	पूर्ण

	/* ग_लिखो */
	अगर (ms_lib_alloc_ग_लिखोbuf(us)) अणु
		result = MS_NO_MEMORY_ERROR;
		जाओ निकास;
	पूर्ण

	result = MS_STATUS_SUCCESS;

निकास:
	kमुक्त(PageBuffer1);
	kमुक्त(PageBuffer0);

	prपूर्णांकk(KERN_INFO "MS_CardInit end\n");
	वापस result;
पूर्ण

अटल पूर्णांक ene_ms_init(काष्ठा us_data *us)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	पूर्णांक result;
	u16 MSP_BlockSize, MSP_UserAreaBlocks;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;

	prपूर्णांकk(KERN_INFO "transport --- ENE_MSInit\n");

	/* the same part to test ENE */

	result = ene_load_bincode(us, MS_INIT_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		prपूर्णांकk(KERN_ERR "Load MS Init Code Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags      = US_BULK_FLAG_IN;
	bcb->CDB[0]     = 0xF1;
	bcb->CDB[1]     = 0x01;

	result = ene_send_scsi_cmd(us, Fसूची_READ, bbuf, 0);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		prपूर्णांकk(KERN_ERR "Execution MS Init Code Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण
	/* the same part to test ENE */
	info->MS_Status = *(काष्ठा MS_STATUS *) bbuf;

	अगर (info->MS_Status.Insert && info->MS_Status.Ready) अणु
		prपूर्णांकk(KERN_INFO "Insert     = %x\n", info->MS_Status.Insert);
		prपूर्णांकk(KERN_INFO "Ready      = %x\n", info->MS_Status.Ready);
		prपूर्णांकk(KERN_INFO "IsMSPro    = %x\n", info->MS_Status.IsMSPro);
		prपूर्णांकk(KERN_INFO "IsMSPHG    = %x\n", info->MS_Status.IsMSPHG);
		prपूर्णांकk(KERN_INFO "WtP= %x\n", info->MS_Status.WtP);
		अगर (info->MS_Status.IsMSPro) अणु
			MSP_BlockSize      = (bbuf[6] << 8) | bbuf[7];
			MSP_UserAreaBlocks = (bbuf[10] << 8) | bbuf[11];
			info->MSP_TotalBlock = MSP_BlockSize * MSP_UserAreaBlocks;
		पूर्ण अन्यथा अणु
			ms_card_init(us); /* Card is MS (to ms.c)*/
		पूर्ण
		usb_stor_dbg(us, "MS Init Code OK !!\n");
	पूर्ण अन्यथा अणु
		usb_stor_dbg(us, "MS Card Not Ready --- %x\n", bbuf[0]);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ene_sd_init(काष्ठा us_data *us)
अणु
	पूर्णांक result;
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;

	usb_stor_dbg(us, "transport --- ENE_SDInit\n");
	/* SD Init Part-1 */
	result = ene_load_bincode(us, SD_INIT1_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Load SD Init Code Part-1 Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->Flags = US_BULK_FLAG_IN;
	bcb->CDB[0] = 0xF2;

	result = ene_send_scsi_cmd(us, Fसूची_READ, शून्य, 0);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Execution SD Init Code Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* SD Init Part-2 */
	result = ene_load_bincode(us, SD_INIT2_PATTERN);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Load SD Init Code Part-2 Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	स_रखो(bcb, 0, माप(काष्ठा bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags              = US_BULK_FLAG_IN;
	bcb->CDB[0]             = 0xF1;

	result = ene_send_scsi_cmd(us, Fसूची_READ, bbuf, 0);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_dbg(us, "Execution SD Init Code Fail !!\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	info->SD_Status =  *(काष्ठा SD_STATUS *) bbuf;
	अगर (info->SD_Status.Insert && info->SD_Status.Ready) अणु
		काष्ठा SD_STATUS *s = &info->SD_Status;

		ene_get_card_status(us, bbuf);
		usb_stor_dbg(us, "Insert     = %x\n", s->Insert);
		usb_stor_dbg(us, "Ready      = %x\n", s->Ready);
		usb_stor_dbg(us, "IsMMC      = %x\n", s->IsMMC);
		usb_stor_dbg(us, "HiCapacity = %x\n", s->HiCapacity);
		usb_stor_dbg(us, "HiSpeed    = %x\n", s->HiSpeed);
		usb_stor_dbg(us, "WtP        = %x\n", s->WtP);
	पूर्ण अन्यथा अणु
		usb_stor_dbg(us, "SD Card Not Ready --- %x\n", bbuf[0]);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण
	वापस USB_STOR_TRANSPORT_GOOD;
पूर्ण


अटल पूर्णांक ene_init(काष्ठा us_data *us)
अणु
	पूर्णांक result;
	u8  misc_reg03;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *)(us->extra);
	u8 *bbuf = info->bbuf;

	result = ene_get_card_type(us, REG_CARD_STATUS, bbuf);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	misc_reg03 = bbuf[0];
	अगर (misc_reg03 & 0x01) अणु
		अगर (!info->SD_Status.Ready) अणु
			result = ene_sd_init(us);
			अगर (result != USB_STOR_XFER_GOOD)
				वापस USB_STOR_TRANSPORT_ERROR;
		पूर्ण
	पूर्ण
	अगर (misc_reg03 & 0x02) अणु
		अगर (!info->MS_Status.Ready) अणु
			result = ene_ms_init(us);
			अगर (result != USB_STOR_XFER_GOOD)
				वापस USB_STOR_TRANSPORT_ERROR;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

/*----- sd_scsi_irp() ---------*/
अटल पूर्णांक sd_scsi_irp(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	पूर्णांक    result;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *)us->extra;

	चयन (srb->cmnd[0]) अणु
	हाल TEST_UNIT_READY:
		result = sd_scsi_test_unit_पढ़ोy(us, srb);
		अवरोध; /* 0x00 */
	हाल REQUEST_SENSE:
		result = करो_scsi_request_sense(us, srb);
		अवरोध; /* 0x03 */
	हाल INQUIRY:
		result = करो_scsi_inquiry(us, srb);
		अवरोध; /* 0x12 */
	हाल MODE_SENSE:
		result = sd_scsi_mode_sense(us, srb);
		अवरोध; /* 0x1A */
	/*
	हाल START_STOP:
		result = SD_SCSI_Start_Stop(us, srb);
		अवरोध; //0x1B
	*/
	हाल READ_CAPACITY:
		result = sd_scsi_पढ़ो_capacity(us, srb);
		अवरोध; /* 0x25 */
	हाल READ_10:
		result = sd_scsi_पढ़ो(us, srb);
		अवरोध; /* 0x28 */
	हाल WRITE_10:
		result = sd_scsi_ग_लिखो(us, srb);
		अवरोध; /* 0x2A */
	शेष:
		info->SrbStatus = SS_ILLEGAL_REQUEST;
		result = USB_STOR_TRANSPORT_FAILED;
		अवरोध;
	पूर्ण
	अगर (result == USB_STOR_TRANSPORT_GOOD)
		info->SrbStatus = SS_SUCCESS;
	वापस result;
पूर्ण

/*
 * ms_scsi_irp()
 */
अटल पूर्णांक ms_scsi_irp(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	पूर्णांक result;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *)us->extra;

	चयन (srb->cmnd[0]) अणु
	हाल TEST_UNIT_READY:
		result = ms_scsi_test_unit_पढ़ोy(us, srb);
		अवरोध; /* 0x00 */
	हाल REQUEST_SENSE:
		result = करो_scsi_request_sense(us, srb);
		अवरोध; /* 0x03 */
	हाल INQUIRY:
		result = करो_scsi_inquiry(us, srb);
		अवरोध; /* 0x12 */
	हाल MODE_SENSE:
		result = ms_scsi_mode_sense(us, srb);
		अवरोध; /* 0x1A */
	हाल READ_CAPACITY:
		result = ms_scsi_पढ़ो_capacity(us, srb);
		अवरोध; /* 0x25 */
	हाल READ_10:
		result = ms_scsi_पढ़ो(us, srb);
		अवरोध; /* 0x28 */
	हाल WRITE_10:
		result = ms_scsi_ग_लिखो(us, srb);
		अवरोध;  /* 0x2A */
	शेष:
		info->SrbStatus = SS_ILLEGAL_REQUEST;
		result = USB_STOR_TRANSPORT_FAILED;
		अवरोध;
	पूर्ण
	अगर (result == USB_STOR_TRANSPORT_GOOD)
		info->SrbStatus = SS_SUCCESS;
	वापस result;
पूर्ण

अटल पूर्णांक ene_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक result = USB_STOR_XFER_GOOD;
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *)(us->extra);

	/*US_DEBUG(usb_stor_show_command(us, srb)); */
	scsi_set_resid(srb, 0);
	अगर (unlikely(!(info->SD_Status.Ready || info->MS_Status.Ready)))
		result = ene_init(us);
	अगर (result == USB_STOR_XFER_GOOD) अणु
		result = USB_STOR_TRANSPORT_ERROR;
		अगर (info->SD_Status.Ready)
			result = sd_scsi_irp(us, srb);

		अगर (info->MS_Status.Ready)
			result = ms_scsi_irp(us, srb);
	पूर्ण
	वापस result;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ene_ub6250_host_ढाँचा;

अटल पूर्णांक ene_ub6250_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक result;
	u8  misc_reg03;
	काष्ठा us_data *us;
	काष्ठा ene_ub6250_info *info;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
		   (id - ene_ub6250_usb_ids) + ene_ub6250_unusual_dev_list,
		   &ene_ub6250_host_ढाँचा);
	अगर (result)
		वापस result;

	/* FIXME: where should the code alloc extra buf ? */
	us->extra = kzalloc(माप(काष्ठा ene_ub6250_info), GFP_KERNEL);
	अगर (!us->extra)
		वापस -ENOMEM;
	us->extra_deकाष्ठाor = ene_ub6250_info_deकाष्ठाor;

	info = (काष्ठा ene_ub6250_info *)(us->extra);
	info->bbuf = kदो_स्मृति(512, GFP_KERNEL);
	अगर (!info->bbuf) अणु
		kमुक्त(us->extra);
		वापस -ENOMEM;
	पूर्ण

	us->transport_name = "ene_ub6250";
	us->transport = ene_transport;
	us->max_lun = 0;

	result = usb_stor_probe2(us);
	अगर (result)
		वापस result;

	/* probe card type */
	result = ene_get_card_type(us, REG_CARD_STATUS, info->bbuf);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		usb_stor_disconnect(पूर्णांकf);
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	misc_reg03 = info->bbuf[0];
	अगर (!(misc_reg03 & 0x01)) अणु
		pr_info("ums_eneub6250: This driver only supports SD/MS cards. "
			"It does not support SM cards.\n");
	पूर्ण

	वापस result;
पूर्ण


#अगर_घोषित CONFIG_PM

अटल पूर्णांक ene_ub6250_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	u8 पंचांगp = 0;
	काष्ठा us_data *us = usb_get_पूर्णांकfdata(अगरace);
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *)(us->extra);

	mutex_lock(&us->dev_mutex);

	अगर (us->suspend_resume_hook)
		(us->suspend_resume_hook)(us, US_RESUME);

	mutex_unlock(&us->dev_mutex);

	info->Power_IsResum = true;
	/*info->SD_Status.Ready = 0; */
	info->SD_Status = *(काष्ठा SD_STATUS *)&पंचांगp;
	info->MS_Status = *(काष्ठा MS_STATUS *)&पंचांगp;
	info->SM_Status = *(काष्ठा SM_STATUS *)&पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक ene_ub6250_reset_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	u8 पंचांगp = 0;
	काष्ठा us_data *us = usb_get_पूर्णांकfdata(अगरace);
	काष्ठा ene_ub6250_info *info = (काष्ठा ene_ub6250_info *)(us->extra);

	/* Report the reset to the SCSI core */
	usb_stor_reset_resume(अगरace);

	/*
	 * FIXME: Notअगरy the subdrivers that they need to reinitialize
	 * the device
	 */
	info->Power_IsResum = true;
	/*info->SD_Status.Ready = 0; */
	info->SD_Status = *(काष्ठा SD_STATUS *)&पंचांगp;
	info->MS_Status = *(काष्ठा MS_STATUS *)&पंचांगp;
	info->SM_Status = *(काष्ठा SM_STATUS *)&पंचांगp;

	वापस 0;
पूर्ण

#अन्यथा

#घोषणा ene_ub6250_resume		शून्य
#घोषणा ene_ub6250_reset_resume		शून्य

#पूर्ण_अगर

अटल काष्ठा usb_driver ene_ub6250_driver = अणु
	.name =		DRV_NAME,
	.probe =	ene_ub6250_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	ene_ub6250_resume,
	.reset_resume =	ene_ub6250_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	ene_ub6250_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(ene_ub6250_driver, ene_ub6250_host_ढाँचा, DRV_NAME);
