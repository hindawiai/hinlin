<शैली गुरु>
/*
 * Intel 5400 class Memory Controllers kernel module (Seaburg)
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Copyright (c) 2008 by:
 *	 Ben Woodard <woodard@redhat.com>
 *	 Mauro Carvalho Chehab
 *
 * Red Hat Inc. https://www.redhat.com
 *
 * Forked and adapted from the i5000_edac driver which was
 * written by Douglas Thompson Linux Networx <norsk5@xmission.com>
 *
 * This module is based on the following करोcument:
 *
 * Intel 5400 Chipset Memory Controller Hub (MCH) - Datasheet
 * 	http://developer.पूर्णांकel.com/design/chipsets/datashts/313070.hपंचांग
 *
 * This Memory Controller manages DDR2 FB-DIMMs. It has 2 branches, each with
 * 2 channels operating in lockstep no-mirror mode. Each channel can have up to
 * 4 dimm's, each with up to 8GB.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/edac.h>
#समावेश <linux/mmzone.h>

#समावेश "edac_module.h"

/*
 * Alter this version क्रम the I5400 module when modअगरications are made
 */
#घोषणा I5400_REVISION    " Ver: 1.0.0"

#घोषणा EDAC_MOD_STR      "i5400_edac"

#घोषणा i5400_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "i5400", fmt, ##arg)

#घोषणा i5400_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "i5400", fmt, ##arg)

/* Limits क्रम i5400 */
#घोषणा MAX_BRANCHES		2
#घोषणा CHANNELS_PER_BRANCH	2
#घोषणा DIMMS_PER_CHANNEL	4
#घोषणा	MAX_CHANNELS		(MAX_BRANCHES * CHANNELS_PER_BRANCH)

/* Device 16,
 * Function 0: System Address
 * Function 1: Memory Branch Map, Control, Errors Register
 * Function 2: FSB Error Registers
 *
 * All 3 functions of Device 16 (0,1,2) share the SAME DID and
 * uses PCI_DEVICE_ID_INTEL_5400_ERR क्रम device 16 (0,1,2),
 * PCI_DEVICE_ID_INTEL_5400_FBD0 and PCI_DEVICE_ID_INTEL_5400_FBD1
 * क्रम device 21 (0,1).
 */

	/* OFFSETS क्रम Function 0 */
#घोषणा		AMBASE			0x48 /* AMB Mem Mapped Reg Region Base */
#घोषणा		MAXCH			0x56 /* Max Channel Number */
#घोषणा		MAXDIMMPERCH		0x57 /* Max DIMM PER Channel Number */

	/* OFFSETS क्रम Function 1 */
#घोषणा		TOLM			0x6C
#घोषणा		REDMEMB			0x7C
#घोषणा			REC_ECC_LOCATOR_ODD(x)	((x) & 0x3fe00) /* bits [17:9] indicate ODD, [8:0]  indicate EVEN */
#घोषणा		MIR0			0x80
#घोषणा		MIR1			0x84
#घोषणा		AMIR0			0x8c
#घोषणा		AMIR1			0x90

	/* Fatal error रेजिस्टरs */
#घोषणा		FERR_FAT_FBD		0x98	/* also called as FERR_FAT_FB_DIMM at datasheet */
#घोषणा			FERR_FAT_FBDCHAN (3<<28)	/* channel index where the highest-order error occurred */

#घोषणा		NERR_FAT_FBD		0x9c
#घोषणा		FERR_NF_FBD		0xa0	/* also called as FERR_NFAT_FB_DIMM at datasheet */

	/* Non-fatal error रेजिस्टर */
#घोषणा		NERR_NF_FBD		0xa4

	/* Enable error mask */
#घोषणा		EMASK_FBD		0xa8

#घोषणा		ERR0_FBD		0xac
#घोषणा		ERR1_FBD		0xb0
#घोषणा		ERR2_FBD		0xb4
#घोषणा		MCERR_FBD		0xb8

	/* No OFFSETS क्रम Device 16 Function 2 */

/*
 * Device 21,
 * Function 0: Memory Map Branch 0
 *
 * Device 22,
 * Function 0: Memory Map Branch 1
 */

	/* OFFSETS क्रम Function 0 */
#घोषणा AMBPRESENT_0	0x64
#घोषणा AMBPRESENT_1	0x66
#घोषणा MTR0		0x80
#घोषणा MTR1		0x82
#घोषणा MTR2		0x84
#घोषणा MTR3		0x86

	/* OFFSETS क्रम Function 1 */
#घोषणा NRECFGLOG		0x74
#घोषणा RECFGLOG		0x78
#घोषणा NRECMEMA		0xbe
#घोषणा NRECMEMB		0xc0
#घोषणा NRECFB_DIMMA		0xc4
#घोषणा NRECFB_DIMMB		0xc8
#घोषणा NRECFB_DIMMC		0xcc
#घोषणा NRECFB_DIMMD		0xd0
#घोषणा NRECFB_DIMME		0xd4
#घोषणा NRECFB_DIMMF		0xd8
#घोषणा REDMEMA			0xdC
#घोषणा RECMEMA			0xf0
#घोषणा RECMEMB			0xf4
#घोषणा RECFB_DIMMA		0xf8
#घोषणा RECFB_DIMMB		0xec
#घोषणा RECFB_DIMMC		0xf0
#घोषणा RECFB_DIMMD		0xf4
#घोषणा RECFB_DIMME		0xf8
#घोषणा RECFB_DIMMF		0xfC

/*
 * Error indicator bits and masks
 * Error masks are according with Table 5-17 of i5400 datasheet
 */

क्रमागत error_mask अणु
	EMASK_M1  = 1<<0,  /* Memory Write error on non-redundant retry */
	EMASK_M2  = 1<<1,  /* Memory or FB-DIMM configuration CRC पढ़ो error */
	EMASK_M3  = 1<<2,  /* Reserved */
	EMASK_M4  = 1<<3,  /* Uncorrectable Data ECC on Replay */
	EMASK_M5  = 1<<4,  /* Aliased Uncorrectable Non-Mirrored Demand Data ECC */
	EMASK_M6  = 1<<5,  /* Unsupported on i5400 */
	EMASK_M7  = 1<<6,  /* Aliased Uncorrectable Resilver- or Spare-Copy Data ECC */
	EMASK_M8  = 1<<7,  /* Aliased Uncorrectable Patrol Data ECC */
	EMASK_M9  = 1<<8,  /* Non-Aliased Uncorrectable Non-Mirrored Demand Data ECC */
	EMASK_M10 = 1<<9,  /* Unsupported on i5400 */
	EMASK_M11 = 1<<10, /* Non-Aliased Uncorrectable Resilver- or Spare-Copy Data ECC  */
	EMASK_M12 = 1<<11, /* Non-Aliased Uncorrectable Patrol Data ECC */
	EMASK_M13 = 1<<12, /* Memory Write error on first attempt */
	EMASK_M14 = 1<<13, /* FB-DIMM Configuration Write error on first attempt */
	EMASK_M15 = 1<<14, /* Memory or FB-DIMM configuration CRC पढ़ो error */
	EMASK_M16 = 1<<15, /* Channel Failed-Over Occurred */
	EMASK_M17 = 1<<16, /* Correctable Non-Mirrored Demand Data ECC */
	EMASK_M18 = 1<<17, /* Unsupported on i5400 */
	EMASK_M19 = 1<<18, /* Correctable Resilver- or Spare-Copy Data ECC */
	EMASK_M20 = 1<<19, /* Correctable Patrol Data ECC */
	EMASK_M21 = 1<<20, /* FB-DIMM Northbound parity error on FB-DIMM Sync Status */
	EMASK_M22 = 1<<21, /* SPD protocol Error */
	EMASK_M23 = 1<<22, /* Non-Redundant Fast Reset Timeout */
	EMASK_M24 = 1<<23, /* Refresh error */
	EMASK_M25 = 1<<24, /* Memory Write error on redundant retry */
	EMASK_M26 = 1<<25, /* Redundant Fast Reset Timeout */
	EMASK_M27 = 1<<26, /* Correctable Counter Threshold Exceeded */
	EMASK_M28 = 1<<27, /* DIMM-Spare Copy Completed */
	EMASK_M29 = 1<<28, /* DIMM-Isolation Completed */
पूर्ण;

/*
 * Names to translate bit error पूर्णांकo something useful
 */
अटल स्थिर अक्षर *error_name[] = अणु
	[0]  = "Memory Write error on non-redundant retry",
	[1]  = "Memory or FB-DIMM configuration CRC read error",
	/* Reserved */
	[3]  = "Uncorrectable Data ECC on Replay",
	[4]  = "Aliased Uncorrectable Non-Mirrored Demand Data ECC",
	/* M6 Unsupported on i5400 */
	[6]  = "Aliased Uncorrectable Resilver- or Spare-Copy Data ECC",
	[7]  = "Aliased Uncorrectable Patrol Data ECC",
	[8]  = "Non-Aliased Uncorrectable Non-Mirrored Demand Data ECC",
	/* M10 Unsupported on i5400 */
	[10] = "Non-Aliased Uncorrectable Resilver- or Spare-Copy Data ECC",
	[11] = "Non-Aliased Uncorrectable Patrol Data ECC",
	[12] = "Memory Write error on first attempt",
	[13] = "FB-DIMM Configuration Write error on first attempt",
	[14] = "Memory or FB-DIMM configuration CRC read error",
	[15] = "Channel Failed-Over Occurred",
	[16] = "Correctable Non-Mirrored Demand Data ECC",
	/* M18 Unsupported on i5400 */
	[18] = "Correctable Resilver- or Spare-Copy Data ECC",
	[19] = "Correctable Patrol Data ECC",
	[20] = "FB-DIMM Northbound parity error on FB-DIMM Sync Status",
	[21] = "SPD protocol Error",
	[22] = "Non-Redundant Fast Reset Timeout",
	[23] = "Refresh error",
	[24] = "Memory Write error on redundant retry",
	[25] = "Redundant Fast Reset Timeout",
	[26] = "Correctable Counter Threshold Exceeded",
	[27] = "DIMM-Spare Copy Completed",
	[28] = "DIMM-Isolation Completed",
पूर्ण;

/* Fatal errors */
#घोषणा ERROR_FAT_MASK		(EMASK_M1 | \
				 EMASK_M2 | \
				 EMASK_M23)

/* Correctable errors */
#घोषणा ERROR_NF_CORRECTABLE	(EMASK_M27 | \
				 EMASK_M20 | \
				 EMASK_M19 | \
				 EMASK_M18 | \
				 EMASK_M17 | \
				 EMASK_M16)
#घोषणा ERROR_NF_DIMM_SPARE	(EMASK_M29 | \
				 EMASK_M28)
#घोषणा ERROR_NF_SPD_PROTOCOL	(EMASK_M22)
#घोषणा ERROR_NF_NORTH_CRC	(EMASK_M21)

/* Recoverable errors */
#घोषणा ERROR_NF_RECOVERABLE	(EMASK_M26 | \
				 EMASK_M25 | \
				 EMASK_M24 | \
				 EMASK_M15 | \
				 EMASK_M14 | \
				 EMASK_M13 | \
				 EMASK_M12 | \
				 EMASK_M11 | \
				 EMASK_M9  | \
				 EMASK_M8  | \
				 EMASK_M7  | \
				 EMASK_M5)

/* uncorrectable errors */
#घोषणा ERROR_NF_UNCORRECTABLE	(EMASK_M4)

/* mask to all non-fatal errors */
#घोषणा ERROR_NF_MASK		(ERROR_NF_CORRECTABLE   | \
				 ERROR_NF_UNCORRECTABLE | \
				 ERROR_NF_RECOVERABLE   | \
				 ERROR_NF_DIMM_SPARE    | \
				 ERROR_NF_SPD_PROTOCOL  | \
				 ERROR_NF_NORTH_CRC)

/*
 * Define error masks क्रम the several रेजिस्टरs
 */

/* Enable all fatal and non fatal errors */
#घोषणा ENABLE_EMASK_ALL	(ERROR_FAT_MASK | ERROR_NF_MASK)

/* mask क्रम fatal error रेजिस्टरs */
#घोषणा FERR_FAT_MASK ERROR_FAT_MASK

/* masks क्रम non-fatal error रेजिस्टर */
अटल अंतरभूत पूर्णांक to_nf_mask(अचिन्हित पूर्णांक mask)
अणु
	वापस (mask & EMASK_M29) | (mask >> 3);
पूर्ण;

अटल अंतरभूत पूर्णांक from_nf_ferr(अचिन्हित पूर्णांक mask)
अणु
	वापस (mask & EMASK_M29) |		/* Bit 28 */
	       (mask & ((1 << 28) - 1) << 3);	/* Bits 0 to 27 */
पूर्ण;

#घोषणा FERR_NF_MASK		to_nf_mask(ERROR_NF_MASK)
#घोषणा FERR_NF_CORRECTABLE	to_nf_mask(ERROR_NF_CORRECTABLE)
#घोषणा FERR_NF_DIMM_SPARE	to_nf_mask(ERROR_NF_DIMM_SPARE)
#घोषणा FERR_NF_SPD_PROTOCOL	to_nf_mask(ERROR_NF_SPD_PROTOCOL)
#घोषणा FERR_NF_NORTH_CRC	to_nf_mask(ERROR_NF_NORTH_CRC)
#घोषणा FERR_NF_RECOVERABLE	to_nf_mask(ERROR_NF_RECOVERABLE)
#घोषणा FERR_NF_UNCORRECTABLE	to_nf_mask(ERROR_NF_UNCORRECTABLE)

/* Defines to extract the vaious fields from the
 *	MTRx - Memory Technology Registers
 */
#घोषणा MTR_DIMMS_PRESENT(mtr)		((mtr) & (1 << 10))
#घोषणा MTR_DIMMS_ETHROTTLE(mtr)	((mtr) & (1 << 9))
#घोषणा MTR_DRAM_WIDTH(mtr)		(((mtr) & (1 << 8)) ? 8 : 4)
#घोषणा MTR_DRAM_BANKS(mtr)		(((mtr) & (1 << 6)) ? 8 : 4)
#घोषणा MTR_DRAM_BANKS_ADDR_BITS(mtr)	((MTR_DRAM_BANKS(mtr) == 8) ? 3 : 2)
#घोषणा MTR_DIMM_RANK(mtr)		(((mtr) >> 5) & 0x1)
#घोषणा MTR_DIMM_RANK_ADDR_BITS(mtr)	(MTR_DIMM_RANK(mtr) ? 2 : 1)
#घोषणा MTR_DIMM_ROWS(mtr)		(((mtr) >> 2) & 0x3)
#घोषणा MTR_DIMM_ROWS_ADDR_BITS(mtr)	(MTR_DIMM_ROWS(mtr) + 13)
#घोषणा MTR_DIMM_COLS(mtr)		((mtr) & 0x3)
#घोषणा MTR_DIMM_COLS_ADDR_BITS(mtr)	(MTR_DIMM_COLS(mtr) + 10)

/* This applies to FERR_NF_FB-DIMM as well as FERR_FAT_FB-DIMM */
अटल अंतरभूत पूर्णांक extract_fbdchan_indx(u32 x)
अणु
	वापस (x>>28) & 0x3;
पूर्ण

/* Device name and रेजिस्टर DID (Device ID) */
काष्ठा i5400_dev_info अणु
	स्थिर अक्षर *ctl_name;	/* name क्रम this device */
	u16 fsb_mapping_errors;	/* DID क्रम the branchmap,control */
पूर्ण;

/* Table of devices attributes supported by this driver */
अटल स्थिर काष्ठा i5400_dev_info i5400_devs[] = अणु
	अणु
		.ctl_name = "I5400",
		.fsb_mapping_errors = PCI_DEVICE_ID_INTEL_5400_ERR,
	पूर्ण,
पूर्ण;

काष्ठा i5400_dimm_info अणु
	पूर्णांक megabytes;		/* size, 0 means not present  */
पूर्ण;

/* driver निजी data काष्ठाure */
काष्ठा i5400_pvt अणु
	काष्ठा pci_dev *प्रणाली_address;		/* 16.0 */
	काष्ठा pci_dev *branchmap_werrors;	/* 16.1 */
	काष्ठा pci_dev *fsb_error_regs;		/* 16.2 */
	काष्ठा pci_dev *branch_0;		/* 21.0 */
	काष्ठा pci_dev *branch_1;		/* 22.0 */

	u16 tolm;				/* top of low memory */
	जोड़ अणु
		u64 ambase;				/* AMB BAR */
		काष्ठा अणु
			u32 ambase_bottom;
			u32 ambase_top;
		पूर्ण u __packed;
	पूर्ण;

	u16 mir0, mir1;

	u16 b0_mtr[DIMMS_PER_CHANNEL];	/* Memory Technlogy Reg */
	u16 b0_ambpresent0;			/* Branch 0, Channel 0 */
	u16 b0_ambpresent1;			/* Brnach 0, Channel 1 */

	u16 b1_mtr[DIMMS_PER_CHANNEL];	/* Memory Technlogy Reg */
	u16 b1_ambpresent0;			/* Branch 1, Channel 8 */
	u16 b1_ambpresent1;			/* Branch 1, Channel 1 */

	/* DIMM inक्रमmation matrix, allocating architecture maximums */
	काष्ठा i5400_dimm_info dimm_info[DIMMS_PER_CHANNEL][MAX_CHANNELS];

	/* Actual values क्रम this controller */
	पूर्णांक maxch;				/* Max channels */
	पूर्णांक maxdimmperch;			/* Max DIMMs per channel */
पूर्ण;

/* I5400 MCH error inक्रमmation retrieved from Hardware */
काष्ठा i5400_error_info अणु
	/* These रेजिस्टरs are always पढ़ो from the MC */
	u32 ferr_fat_fbd;	/* First Errors Fatal */
	u32 nerr_fat_fbd;	/* Next Errors Fatal */
	u32 ferr_nf_fbd;	/* First Errors Non-Fatal */
	u32 nerr_nf_fbd;	/* Next Errors Non-Fatal */

	/* These रेजिस्टरs are input ONLY अगर there was a Recoverable Error */
	u32 redmemb;		/* Recoverable Mem Data Error log B */
	u16 recmema;		/* Recoverable Mem Error log A */
	u32 recmemb;		/* Recoverable Mem Error log B */

	/* These रेजिस्टरs are input ONLY अगर there was a Non-Rec Error */
	u16 nrecmema;		/* Non-Recoverable Mem log A */
	u32 nrecmemb;		/* Non-Recoverable Mem log B */

पूर्ण;

/* note that nrec_rdwr changed from NRECMEMA to NRECMEMB between the 5000 and
   5400 better to use an अंतरभूत function than a macro in this हाल */
अटल अंतरभूत पूर्णांक nrec_bank(काष्ठा i5400_error_info *info)
अणु
	वापस ((info->nrecmema) >> 12) & 0x7;
पूर्ण
अटल अंतरभूत पूर्णांक nrec_rank(काष्ठा i5400_error_info *info)
अणु
	वापस ((info->nrecmema) >> 8) & 0xf;
पूर्ण
अटल अंतरभूत पूर्णांक nrec_buf_id(काष्ठा i5400_error_info *info)
अणु
	वापस ((info->nrecmema)) & 0xff;
पूर्ण
अटल अंतरभूत पूर्णांक nrec_rdwr(काष्ठा i5400_error_info *info)
अणु
	वापस (info->nrecmemb) >> 31;
पूर्ण
/* This applies to both NREC and REC string so it can be used with nrec_rdwr
   and rec_rdwr */
अटल अंतरभूत स्थिर अक्षर *rdwr_str(पूर्णांक rdwr)
अणु
	वापस rdwr ? "Write" : "Read";
पूर्ण
अटल अंतरभूत पूर्णांक nrec_cas(काष्ठा i5400_error_info *info)
अणु
	वापस ((info->nrecmemb) >> 16) & 0x1fff;
पूर्ण
अटल अंतरभूत पूर्णांक nrec_ras(काष्ठा i5400_error_info *info)
अणु
	वापस (info->nrecmemb) & 0xffff;
पूर्ण
अटल अंतरभूत पूर्णांक rec_bank(काष्ठा i5400_error_info *info)
अणु
	वापस ((info->recmema) >> 12) & 0x7;
पूर्ण
अटल अंतरभूत पूर्णांक rec_rank(काष्ठा i5400_error_info *info)
अणु
	वापस ((info->recmema) >> 8) & 0xf;
पूर्ण
अटल अंतरभूत पूर्णांक rec_rdwr(काष्ठा i5400_error_info *info)
अणु
	वापस (info->recmemb) >> 31;
पूर्ण
अटल अंतरभूत पूर्णांक rec_cas(काष्ठा i5400_error_info *info)
अणु
	वापस ((info->recmemb) >> 16) & 0x1fff;
पूर्ण
अटल अंतरभूत पूर्णांक rec_ras(काष्ठा i5400_error_info *info)
अणु
	वापस (info->recmemb) & 0xffff;
पूर्ण

अटल काष्ठा edac_pci_ctl_info *i5400_pci;

/*
 *	i5400_get_error_info	Retrieve the hardware error inक्रमmation from
 *				the hardware and cache it in the 'info'
 *				काष्ठाure
 */
अटल व्योम i5400_get_error_info(काष्ठा mem_ctl_info *mci,
				 काष्ठा i5400_error_info *info)
अणु
	काष्ठा i5400_pvt *pvt;
	u32 value;

	pvt = mci->pvt_info;

	/* पढ़ो in the 1st FATAL error रेजिस्टर */
	pci_पढ़ो_config_dword(pvt->branchmap_werrors, FERR_FAT_FBD, &value);

	/* Mask only the bits that the करोc says are valid
	 */
	value &= (FERR_FAT_FBDCHAN | FERR_FAT_MASK);

	/* If there is an error, then पढ़ो in the
	   NEXT FATAL error रेजिस्टर and the Memory Error Log Register A
	 */
	अगर (value & FERR_FAT_MASK) अणु
		info->ferr_fat_fbd = value;

		/* harvest the various error data we need */
		pci_पढ़ो_config_dword(pvt->branchmap_werrors,
				NERR_FAT_FBD, &info->nerr_fat_fbd);
		pci_पढ़ो_config_word(pvt->branchmap_werrors,
				NRECMEMA, &info->nrecmema);
		pci_पढ़ो_config_dword(pvt->branchmap_werrors,
				NRECMEMB, &info->nrecmemb);

		/* Clear the error bits, by writing them back */
		pci_ग_लिखो_config_dword(pvt->branchmap_werrors,
				FERR_FAT_FBD, value);
	पूर्ण अन्यथा अणु
		info->ferr_fat_fbd = 0;
		info->nerr_fat_fbd = 0;
		info->nrecmema = 0;
		info->nrecmemb = 0;
	पूर्ण

	/* पढ़ो in the 1st NON-FATAL error रेजिस्टर */
	pci_पढ़ो_config_dword(pvt->branchmap_werrors, FERR_NF_FBD, &value);

	/* If there is an error, then पढ़ो in the 1st NON-FATAL error
	 * रेजिस्टर as well */
	अगर (value & FERR_NF_MASK) अणु
		info->ferr_nf_fbd = value;

		/* harvest the various error data we need */
		pci_पढ़ो_config_dword(pvt->branchmap_werrors,
				NERR_NF_FBD, &info->nerr_nf_fbd);
		pci_पढ़ो_config_word(pvt->branchmap_werrors,
				RECMEMA, &info->recmema);
		pci_पढ़ो_config_dword(pvt->branchmap_werrors,
				RECMEMB, &info->recmemb);
		pci_पढ़ो_config_dword(pvt->branchmap_werrors,
				REDMEMB, &info->redmemb);

		/* Clear the error bits, by writing them back */
		pci_ग_लिखो_config_dword(pvt->branchmap_werrors,
				FERR_NF_FBD, value);
	पूर्ण अन्यथा अणु
		info->ferr_nf_fbd = 0;
		info->nerr_nf_fbd = 0;
		info->recmema = 0;
		info->recmemb = 0;
		info->redmemb = 0;
	पूर्ण
पूर्ण

/*
 * i5400_proccess_non_recoverable_info(काष्ठा mem_ctl_info *mci,
 * 					काष्ठा i5400_error_info *info,
 * 					पूर्णांक handle_errors);
 *
 *	handle the Intel FATAL and unrecoverable errors, अगर any
 */
अटल व्योम i5400_proccess_non_recoverable_info(काष्ठा mem_ctl_info *mci,
				    काष्ठा i5400_error_info *info,
				    अचिन्हित दीर्घ allErrors)
अणु
	अक्षर msg[EDAC_MC_LABEL_LEN + 1 + 90 + 80];
	पूर्णांक branch;
	पूर्णांक channel;
	पूर्णांक bank;
	पूर्णांक buf_id;
	पूर्णांक rank;
	पूर्णांक rdwr;
	पूर्णांक ras, cas;
	पूर्णांक errnum;
	अक्षर *type = शून्य;
	क्रमागत hw_event_mc_err_type tp_event = HW_EVENT_ERR_UNCORRECTED;

	अगर (!allErrors)
		वापस;		/* अगर no error, वापस now */

	अगर (allErrors &  ERROR_FAT_MASK) अणु
		type = "FATAL";
		tp_event = HW_EVENT_ERR_FATAL;
	पूर्ण अन्यथा अगर (allErrors & FERR_NF_UNCORRECTABLE)
		type = "NON-FATAL uncorrected";
	अन्यथा
		type = "NON-FATAL recoverable";

	/* ONLY ONE of the possible error bits will be set, as per the करोcs */

	branch = extract_fbdchan_indx(info->ferr_fat_fbd);
	channel = branch;

	/* Use the NON-Recoverable macros to extract data */
	bank = nrec_bank(info);
	rank = nrec_rank(info);
	buf_id = nrec_buf_id(info);
	rdwr = nrec_rdwr(info);
	ras = nrec_ras(info);
	cas = nrec_cas(info);

	edac_dbg(0, "\t\t%s DIMM= %d  Channels= %d,%d  (Branch= %d DRAM Bank= %d Buffer ID = %d rdwr= %s ras= %d cas= %d)\n",
		 type, rank, channel, channel + 1, branch >> 1, bank,
		 buf_id, rdwr_str(rdwr), ras, cas);

	/* Only 1 bit will be on */
	errnum = find_first_bit(&allErrors, ARRAY_SIZE(error_name));

	/* Form out message */
	snम_लिखो(msg, माप(msg),
		 "Bank=%d Buffer ID = %d RAS=%d CAS=%d Err=0x%lx (%s)",
		 bank, buf_id, ras, cas, allErrors, error_name[errnum]);

	edac_mc_handle_error(tp_event, mci, 1, 0, 0, 0,
			     branch >> 1, -1, rank,
			     rdwr ? "Write error" : "Read error",
			     msg);
पूर्ण

/*
 * i5400_process_fatal_error_info(काष्ठा mem_ctl_info *mci,
 * 				काष्ठा i5400_error_info *info,
 * 				पूर्णांक handle_errors);
 *
 *	handle the Intel NON-FATAL errors, अगर any
 */
अटल व्योम i5400_process_nonfatal_error_info(काष्ठा mem_ctl_info *mci,
					काष्ठा i5400_error_info *info)
अणु
	अक्षर msg[EDAC_MC_LABEL_LEN + 1 + 90 + 80];
	अचिन्हित दीर्घ allErrors;
	पूर्णांक branch;
	पूर्णांक channel;
	पूर्णांक bank;
	पूर्णांक rank;
	पूर्णांक rdwr;
	पूर्णांक ras, cas;
	पूर्णांक errnum;

	/* mask off the Error bits that are possible */
	allErrors = from_nf_ferr(info->ferr_nf_fbd & FERR_NF_MASK);
	अगर (!allErrors)
		वापस;		/* अगर no error, वापस now */

	/* ONLY ONE of the possible error bits will be set, as per the करोcs */

	अगर (allErrors & (ERROR_NF_UNCORRECTABLE | ERROR_NF_RECOVERABLE)) अणु
		i5400_proccess_non_recoverable_info(mci, info, allErrors);
		वापस;
	पूर्ण

	/* Correctable errors */
	अगर (allErrors & ERROR_NF_CORRECTABLE) अणु
		edac_dbg(0, "\tCorrected bits= 0x%lx\n", allErrors);

		branch = extract_fbdchan_indx(info->ferr_nf_fbd);

		channel = 0;
		अगर (REC_ECC_LOCATOR_ODD(info->redmemb))
			channel = 1;

		/* Convert channel to be based from zero, instead of
		 * from branch base of 0 */
		channel += branch;

		bank = rec_bank(info);
		rank = rec_rank(info);
		rdwr = rec_rdwr(info);
		ras = rec_ras(info);
		cas = rec_cas(info);

		/* Only 1 bit will be on */
		errnum = find_first_bit(&allErrors, ARRAY_SIZE(error_name));

		edac_dbg(0, "\t\tDIMM= %d Channel= %d  (Branch %d DRAM Bank= %d rdwr= %s ras= %d cas= %d)\n",
			 rank, channel, branch >> 1, bank,
			 rdwr_str(rdwr), ras, cas);

		/* Form out message */
		snम_लिखो(msg, माप(msg),
			 "Corrected error (Branch=%d DRAM-Bank=%d RDWR=%s "
			 "RAS=%d CAS=%d, CE Err=0x%lx (%s))",
			 branch >> 1, bank, rdwr_str(rdwr), ras, cas,
			 allErrors, error_name[errnum]);

		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0,
				     branch >> 1, channel % 2, rank,
				     rdwr ? "Write error" : "Read error",
				     msg);

		वापस;
	पूर्ण

	/* Miscellaneous errors */
	errnum = find_first_bit(&allErrors, ARRAY_SIZE(error_name));

	branch = extract_fbdchan_indx(info->ferr_nf_fbd);

	i5400_mc_prपूर्णांकk(mci, KERN_EMERG,
			"Non-Fatal misc error (Branch=%d Err=%#lx (%s))",
			branch >> 1, allErrors, error_name[errnum]);
पूर्ण

/*
 *	i5400_process_error_info	Process the error info that is
 *	in the 'info' काष्ठाure, previously retrieved from hardware
 */
अटल व्योम i5400_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i5400_error_info *info)
अणु	u32 allErrors;

	/* First handle any fatal errors that occurred */
	allErrors = (info->ferr_fat_fbd & FERR_FAT_MASK);
	i5400_proccess_non_recoverable_info(mci, info, allErrors);

	/* now handle any non-fatal errors that occurred */
	i5400_process_nonfatal_error_info(mci, info);
पूर्ण

/*
 *	i5400_clear_error	Retrieve any error from the hardware
 *				but करो NOT process that error.
 *				Used क्रम 'clearing' out of previous errors
 *				Called by the Core module.
 */
अटल व्योम i5400_clear_error(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5400_error_info info;

	i5400_get_error_info(mci, &info);
पूर्ण

/*
 *	i5400_check_error	Retrieve and process errors reported by the
 *				hardware. Called by the Core module.
 */
अटल व्योम i5400_check_error(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5400_error_info info;

	i5400_get_error_info(mci, &info);
	i5400_process_error_info(mci, &info);
पूर्ण

/*
 *	i5400_put_devices	'put' all the devices that we have
 *				reserved via 'get'
 */
अटल व्योम i5400_put_devices(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5400_pvt *pvt;

	pvt = mci->pvt_info;

	/* Decrement usage count क्रम devices */
	pci_dev_put(pvt->branch_1);
	pci_dev_put(pvt->branch_0);
	pci_dev_put(pvt->fsb_error_regs);
	pci_dev_put(pvt->branchmap_werrors);
पूर्ण

/*
 *	i5400_get_devices	Find and perक्रमm 'get' operation on the MCH's
 *			device/functions we want to reference क्रम this driver
 *
 *			Need to 'get' device 16 func 1 and func 2
 */
अटल पूर्णांक i5400_get_devices(काष्ठा mem_ctl_info *mci, पूर्णांक dev_idx)
अणु
	काष्ठा i5400_pvt *pvt;
	काष्ठा pci_dev *pdev;

	pvt = mci->pvt_info;
	pvt->branchmap_werrors = शून्य;
	pvt->fsb_error_regs = शून्य;
	pvt->branch_0 = शून्य;
	pvt->branch_1 = शून्य;

	/* Attempt to 'get' the MCH रेजिस्टर we want */
	pdev = शून्य;
	जबतक (1) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_5400_ERR, pdev);
		अगर (!pdev) अणु
			/* End of list, leave */
			i5400_prपूर्णांकk(KERN_ERR,
				"'system address,Process Bus' "
				"device not found:"
				"vendor 0x%x device 0x%x ERR func 1 "
				"(broken BIOS?)\n",
				PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_5400_ERR);
			वापस -ENODEV;
		पूर्ण

		/* Store device 16 func 1 */
		अगर (PCI_FUNC(pdev->devfn) == 1)
			अवरोध;
	पूर्ण
	pvt->branchmap_werrors = pdev;

	pdev = शून्य;
	जबतक (1) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_5400_ERR, pdev);
		अगर (!pdev) अणु
			/* End of list, leave */
			i5400_prपूर्णांकk(KERN_ERR,
				"'system address,Process Bus' "
				"device not found:"
				"vendor 0x%x device 0x%x ERR func 2 "
				"(broken BIOS?)\n",
				PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_5400_ERR);

			pci_dev_put(pvt->branchmap_werrors);
			वापस -ENODEV;
		पूर्ण

		/* Store device 16 func 2 */
		अगर (PCI_FUNC(pdev->devfn) == 2)
			अवरोध;
	पूर्ण
	pvt->fsb_error_regs = pdev;

	edac_dbg(1, "System Address, processor bus- PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->प्रणाली_address),
		 pvt->प्रणाली_address->venकरोr, pvt->प्रणाली_address->device);
	edac_dbg(1, "Branchmap, control and errors - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->branchmap_werrors),
		 pvt->branchmap_werrors->venकरोr,
		 pvt->branchmap_werrors->device);
	edac_dbg(1, "FSB Error Regs - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->fsb_error_regs),
		 pvt->fsb_error_regs->venकरोr, pvt->fsb_error_regs->device);

	pvt->branch_0 = pci_get_device(PCI_VENDOR_ID_INTEL,
				       PCI_DEVICE_ID_INTEL_5400_FBD0, शून्य);
	अगर (!pvt->branch_0) अणु
		i5400_prपूर्णांकk(KERN_ERR,
			"MC: 'BRANCH 0' device not found:"
			"vendor 0x%x device 0x%x Func 0 (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_5400_FBD0);

		pci_dev_put(pvt->fsb_error_regs);
		pci_dev_put(pvt->branchmap_werrors);
		वापस -ENODEV;
	पूर्ण

	/* If this device claims to have more than 2 channels then
	 * fetch Branch 1's inक्रमmation
	 */
	अगर (pvt->maxch < CHANNELS_PER_BRANCH)
		वापस 0;

	pvt->branch_1 = pci_get_device(PCI_VENDOR_ID_INTEL,
				       PCI_DEVICE_ID_INTEL_5400_FBD1, शून्य);
	अगर (!pvt->branch_1) अणु
		i5400_prपूर्णांकk(KERN_ERR,
			"MC: 'BRANCH 1' device not found:"
			"vendor 0x%x device 0x%x Func 0 "
			"(broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_5400_FBD1);

		pci_dev_put(pvt->branch_0);
		pci_dev_put(pvt->fsb_error_regs);
		pci_dev_put(pvt->branchmap_werrors);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	determine_amb_present
 *
 *		the inक्रमmation is contained in DIMMS_PER_CHANNEL dअगरferent
 *		रेजिस्टरs determining which of the DIMMS_PER_CHANNEL requires
 *              knowing which channel is in question
 *
 *	2 branches, each with 2 channels
 *		b0_ambpresent0 क्रम channel '0'
 *		b0_ambpresent1 क्रम channel '1'
 *		b1_ambpresent0 क्रम channel '2'
 *		b1_ambpresent1 क्रम channel '3'
 */
अटल पूर्णांक determine_amb_present_reg(काष्ठा i5400_pvt *pvt, पूर्णांक channel)
अणु
	पूर्णांक amb_present;

	अगर (channel < CHANNELS_PER_BRANCH) अणु
		अगर (channel & 0x1)
			amb_present = pvt->b0_ambpresent1;
		अन्यथा
			amb_present = pvt->b0_ambpresent0;
	पूर्ण अन्यथा अणु
		अगर (channel & 0x1)
			amb_present = pvt->b1_ambpresent1;
		अन्यथा
			amb_present = pvt->b1_ambpresent0;
	पूर्ण

	वापस amb_present;
पूर्ण

/*
 * determine_mtr(pvt, dimm, channel)
 *
 * वापस the proper MTR रेजिस्टर as determine by the dimm and desired channel
 */
अटल पूर्णांक determine_mtr(काष्ठा i5400_pvt *pvt, पूर्णांक dimm, पूर्णांक channel)
अणु
	पूर्णांक mtr;
	पूर्णांक n;

	/* There is one MTR क्रम each slot pair of FB-DIMMs,
	   Each slot pair may be at branch 0 or branch 1.
	 */
	n = dimm;

	अगर (n >= DIMMS_PER_CHANNEL) अणु
		edac_dbg(0, "ERROR: trying to access an invalid dimm: %d\n",
			 dimm);
		वापस 0;
	पूर्ण

	अगर (channel < CHANNELS_PER_BRANCH)
		mtr = pvt->b0_mtr[n];
	अन्यथा
		mtr = pvt->b1_mtr[n];

	वापस mtr;
पूर्ण

/*
 */
अटल व्योम decode_mtr(पूर्णांक slot_row, u16 mtr)
अणु
	पूर्णांक ans;

	ans = MTR_DIMMS_PRESENT(mtr);

	edac_dbg(2, "\tMTR%d=0x%x:  DIMMs are %sPresent\n",
		 slot_row, mtr, ans ? "" : "NOT ");
	अगर (!ans)
		वापस;

	edac_dbg(2, "\t\tWIDTH: x%d\n", MTR_DRAM_WIDTH(mtr));

	edac_dbg(2, "\t\tELECTRICAL THROTTLING is %s\n",
		 MTR_DIMMS_ETHROTTLE(mtr) ? "enabled" : "disabled");

	edac_dbg(2, "\t\tNUMBANK: %d bank(s)\n", MTR_DRAM_BANKS(mtr));
	edac_dbg(2, "\t\tNUMRANK: %s\n",
		 MTR_DIMM_RANK(mtr) ? "double" : "single");
	edac_dbg(2, "\t\tNUMROW: %s\n",
		 MTR_DIMM_ROWS(mtr) == 0 ? "8,192 - 13 rows" :
		 MTR_DIMM_ROWS(mtr) == 1 ? "16,384 - 14 rows" :
		 MTR_DIMM_ROWS(mtr) == 2 ? "32,768 - 15 rows" :
		 "65,536 - 16 rows");
	edac_dbg(2, "\t\tNUMCOL: %s\n",
		 MTR_DIMM_COLS(mtr) == 0 ? "1,024 - 10 columns" :
		 MTR_DIMM_COLS(mtr) == 1 ? "2,048 - 11 columns" :
		 MTR_DIMM_COLS(mtr) == 2 ? "4,096 - 12 columns" :
		 "reserved");
पूर्ण

अटल व्योम handle_channel(काष्ठा i5400_pvt *pvt, पूर्णांक dimm, पूर्णांक channel,
			काष्ठा i5400_dimm_info *dinfo)
अणु
	पूर्णांक mtr;
	पूर्णांक amb_present_reg;
	पूर्णांक addrBits;

	mtr = determine_mtr(pvt, dimm, channel);
	अगर (MTR_DIMMS_PRESENT(mtr)) अणु
		amb_present_reg = determine_amb_present_reg(pvt, channel);

		/* Determine अगर there is a DIMM present in this DIMM slot */
		अगर (amb_present_reg & (1 << dimm)) अणु
			/* Start with the number of bits क्रम a Bank
			 * on the DRAM */
			addrBits = MTR_DRAM_BANKS_ADDR_BITS(mtr);
			/* Add thक्रमागतber of ROW bits */
			addrBits += MTR_DIMM_ROWS_ADDR_BITS(mtr);
			/* add the number of COLUMN bits */
			addrBits += MTR_DIMM_COLS_ADDR_BITS(mtr);
			/* add the number of RANK bits */
			addrBits += MTR_DIMM_RANK(mtr);

			addrBits += 6;	/* add 64 bits per DIMM */
			addrBits -= 20;	/* भागide by 2^^20 */
			addrBits -= 3;	/* 8 bits per bytes */

			dinfo->megabytes = 1 << addrBits;
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	calculate_dimm_size
 *
 *	also will output a DIMM matrix map, अगर debug is enabled, क्रम viewing
 *	how the DIMMs are populated
 */
अटल व्योम calculate_dimm_size(काष्ठा i5400_pvt *pvt)
अणु
	काष्ठा i5400_dimm_info *dinfo;
	पूर्णांक dimm, max_dimms;
	अक्षर *p, *mem_buffer;
	पूर्णांक space, n;
	पूर्णांक channel, branch;

	/* ================= Generate some debug output ================= */
	space = PAGE_SIZE;
	mem_buffer = p = kदो_स्मृति(space, GFP_KERNEL);
	अगर (p == शून्य) अणु
		i5400_prपूर्णांकk(KERN_ERR, "MC: %s:%s() kmalloc() failed\n",
			__खाता__, __func__);
		वापस;
	पूर्ण

	/* Scan all the actual DIMMS
	 * and calculate the inक्रमmation क्रम each DIMM
	 * Start with the highest dimm first, to display it first
	 * and work toward the 0th dimm
	 */
	max_dimms = pvt->maxdimmperch;
	क्रम (dimm = max_dimms - 1; dimm >= 0; dimm--) अणु

		/* on an odd dimm, first output a 'boundary' marker,
		 * then reset the message buffer  */
		अगर (dimm & 0x1) अणु
			n = snम_लिखो(p, space, "---------------------------"
					"-------------------------------");
			p += n;
			space -= n;
			edac_dbg(2, "%s\n", mem_buffer);
			p = mem_buffer;
			space = PAGE_SIZE;
		पूर्ण
		n = snम_लिखो(p, space, "dimm %2d    ", dimm);
		p += n;
		space -= n;

		क्रम (channel = 0; channel < pvt->maxch; channel++) अणु
			dinfo = &pvt->dimm_info[dimm][channel];
			handle_channel(pvt, dimm, channel, dinfo);
			n = snम_लिखो(p, space, "%4d MB   | ", dinfo->megabytes);
			p += n;
			space -= n;
		पूर्ण
		edac_dbg(2, "%s\n", mem_buffer);
		p = mem_buffer;
		space = PAGE_SIZE;
	पूर्ण

	/* Output the last bottom 'boundary' marker */
	n = snम_लिखो(p, space, "---------------------------"
			"-------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", mem_buffer);
	p = mem_buffer;
	space = PAGE_SIZE;

	/* now output the 'channel' labels */
	n = snम_लिखो(p, space, "           ");
	p += n;
	space -= n;
	क्रम (channel = 0; channel < pvt->maxch; channel++) अणु
		n = snम_लिखो(p, space, "channel %d | ", channel);
		p += n;
		space -= n;
	पूर्ण

	space -= n;
	edac_dbg(2, "%s\n", mem_buffer);
	p = mem_buffer;
	space = PAGE_SIZE;

	n = snम_लिखो(p, space, "           ");
	p += n;
	क्रम (branch = 0; branch < MAX_BRANCHES; branch++) अणु
		n = snम_लिखो(p, space, "       branch %d       | ", branch);
		p += n;
		space -= n;
	पूर्ण

	/* output the last message and मुक्त buffer */
	edac_dbg(2, "%s\n", mem_buffer);
	kमुक्त(mem_buffer);
पूर्ण

/*
 *	i5400_get_mc_regs	पढ़ो in the necessary रेजिस्टरs and
 *				cache locally
 *
 *			Fills in the निजी data members
 */
अटल व्योम i5400_get_mc_regs(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5400_pvt *pvt;
	u32 actual_tolm;
	u16 limit;
	पूर्णांक slot_row;
	पूर्णांक way0, way1;

	pvt = mci->pvt_info;

	pci_पढ़ो_config_dword(pvt->प्रणाली_address, AMBASE,
			&pvt->u.ambase_bottom);
	pci_पढ़ो_config_dword(pvt->प्रणाली_address, AMBASE + माप(u32),
			&pvt->u.ambase_top);

	edac_dbg(2, "AMBASE= 0x%lx  MAXCH= %d  MAX-DIMM-Per-CH= %d\n",
		 (दीर्घ अचिन्हित पूर्णांक)pvt->ambase, pvt->maxch, pvt->maxdimmperch);

	/* Get the Branch Map regs */
	pci_पढ़ो_config_word(pvt->branchmap_werrors, TOLM, &pvt->tolm);
	pvt->tolm >>= 12;
	edac_dbg(2, "\nTOLM (number of 256M regions) =%u (0x%x)\n",
		 pvt->tolm, pvt->tolm);

	actual_tolm = (u32) ((1000l * pvt->tolm) >> (30 - 28));
	edac_dbg(2, "Actual TOLM byte addr=%u.%03u GB (0x%x)\n",
		 actual_tolm/1000, actual_tolm % 1000, pvt->tolm << 28);

	pci_पढ़ो_config_word(pvt->branchmap_werrors, MIR0, &pvt->mir0);
	pci_पढ़ो_config_word(pvt->branchmap_werrors, MIR1, &pvt->mir1);

	/* Get the MIR[0-1] regs */
	limit = (pvt->mir0 >> 4) & 0x0fff;
	way0 = pvt->mir0 & 0x1;
	way1 = pvt->mir0 & 0x2;
	edac_dbg(2, "MIR0: limit= 0x%x  WAY1= %u  WAY0= %x\n",
		 limit, way1, way0);
	limit = (pvt->mir1 >> 4) & 0xfff;
	way0 = pvt->mir1 & 0x1;
	way1 = pvt->mir1 & 0x2;
	edac_dbg(2, "MIR1: limit= 0x%x  WAY1= %u  WAY0= %x\n",
		 limit, way1, way0);

	/* Get the set of MTR[0-3] regs by each branch */
	क्रम (slot_row = 0; slot_row < DIMMS_PER_CHANNEL; slot_row++) अणु
		पूर्णांक where = MTR0 + (slot_row * माप(u16));

		/* Branch 0 set of MTR रेजिस्टरs */
		pci_पढ़ो_config_word(pvt->branch_0, where,
				&pvt->b0_mtr[slot_row]);

		edac_dbg(2, "MTR%d where=0x%x B0 value=0x%x\n",
			 slot_row, where, pvt->b0_mtr[slot_row]);

		अगर (pvt->maxch < CHANNELS_PER_BRANCH) अणु
			pvt->b1_mtr[slot_row] = 0;
			जारी;
		पूर्ण

		/* Branch 1 set of MTR रेजिस्टरs */
		pci_पढ़ो_config_word(pvt->branch_1, where,
				&pvt->b1_mtr[slot_row]);
		edac_dbg(2, "MTR%d where=0x%x B1 value=0x%x\n",
			 slot_row, where, pvt->b1_mtr[slot_row]);
	पूर्ण

	/* Read and dump branch 0's MTRs */
	edac_dbg(2, "Memory Technology Registers:\n");
	edac_dbg(2, "   Branch 0:\n");
	क्रम (slot_row = 0; slot_row < DIMMS_PER_CHANNEL; slot_row++)
		decode_mtr(slot_row, pvt->b0_mtr[slot_row]);

	pci_पढ़ो_config_word(pvt->branch_0, AMBPRESENT_0,
			&pvt->b0_ambpresent0);
	edac_dbg(2, "\t\tAMB-Branch 0-present0 0x%x:\n", pvt->b0_ambpresent0);
	pci_पढ़ो_config_word(pvt->branch_0, AMBPRESENT_1,
			&pvt->b0_ambpresent1);
	edac_dbg(2, "\t\tAMB-Branch 0-present1 0x%x:\n", pvt->b0_ambpresent1);

	/* Only अगर we have 2 branchs (4 channels) */
	अगर (pvt->maxch < CHANNELS_PER_BRANCH) अणु
		pvt->b1_ambpresent0 = 0;
		pvt->b1_ambpresent1 = 0;
	पूर्ण अन्यथा अणु
		/* Read and dump  branch 1's MTRs */
		edac_dbg(2, "   Branch 1:\n");
		क्रम (slot_row = 0; slot_row < DIMMS_PER_CHANNEL; slot_row++)
			decode_mtr(slot_row, pvt->b1_mtr[slot_row]);

		pci_पढ़ो_config_word(pvt->branch_1, AMBPRESENT_0,
				&pvt->b1_ambpresent0);
		edac_dbg(2, "\t\tAMB-Branch 1-present0 0x%x:\n",
			 pvt->b1_ambpresent0);
		pci_पढ़ो_config_word(pvt->branch_1, AMBPRESENT_1,
				&pvt->b1_ambpresent1);
		edac_dbg(2, "\t\tAMB-Branch 1-present1 0x%x:\n",
			 pvt->b1_ambpresent1);
	पूर्ण

	/* Go and determine the size of each DIMM and place in an
	 * orderly matrix */
	calculate_dimm_size(pvt);
पूर्ण

/*
 *	i5400_init_dimms	Initialize the 'dimms' table within
 *				the mci control	काष्ठाure with the
 *				addressing of memory.
 *
 *	वापस:
 *		0	success
 *		1	no actual memory found on this MC
 */
अटल पूर्णांक i5400_init_dimms(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5400_pvt *pvt;
	काष्ठा dimm_info *dimm;
	पूर्णांक ndimms;
	पूर्णांक mtr;
	पूर्णांक size_mb;
	पूर्णांक  channel, slot;

	pvt = mci->pvt_info;

	ndimms = 0;

	/*
	 * FIXME: हटाओ  pvt->dimm_info[slot][channel] and use the 3
	 * layers here.
	 */
	क्रम (channel = 0; channel < mci->layers[0].size * mci->layers[1].size;
	     channel++) अणु
		क्रम (slot = 0; slot < mci->layers[2].size; slot++) अणु
			mtr = determine_mtr(pvt, slot, channel);

			/* अगर no DIMMS on this slot, जारी */
			अगर (!MTR_DIMMS_PRESENT(mtr))
				जारी;

			dimm = edac_get_dimm(mci, channel / 2, channel % 2, slot);

			size_mb =  pvt->dimm_info[slot][channel].megabytes;

			edac_dbg(2, "dimm (branch %d channel %d slot %d): %d.%03d GB\n",
				 channel / 2, channel % 2, slot,
				 size_mb / 1000, size_mb % 1000);

			dimm->nr_pages = size_mb << 8;
			dimm->grain = 8;
			dimm->dtype = MTR_DRAM_WIDTH(mtr) == 8 ?
				      DEV_X8 : DEV_X4;
			dimm->mtype = MEM_FB_DDR2;
			/*
			 * The eccc mechanism is SDDC (aka SECC), with
			 * is similar to Chipसमाप्त.
			 */
			dimm->edac_mode = MTR_DRAM_WIDTH(mtr) == 8 ?
					  EDAC_S8ECD8ED : EDAC_S4ECD4ED;
			ndimms++;
		पूर्ण
	पूर्ण

	/*
	 * When just one memory is provided, it should be at location (0,0,0).
	 * With such single-DIMM mode, the SDCC algorithm degrades to SECDEC+.
	 */
	अगर (ndimms == 1)
		mci->dimms[0]->edac_mode = EDAC_SECDED;

	वापस (ndimms == 0);
पूर्ण

/*
 *	i5400_enable_error_reporting
 *			Turn on the memory reporting features of the hardware
 */
अटल व्योम i5400_enable_error_reporting(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5400_pvt *pvt;
	u32 fbd_error_mask;

	pvt = mci->pvt_info;

	/* Read the FBD Error Mask Register */
	pci_पढ़ो_config_dword(pvt->branchmap_werrors, EMASK_FBD,
			&fbd_error_mask);

	/* Enable with a '0' */
	fbd_error_mask &= ~(ENABLE_EMASK_ALL);

	pci_ग_लिखो_config_dword(pvt->branchmap_werrors, EMASK_FBD,
			fbd_error_mask);
पूर्ण

/*
 *	i5400_probe1	Probe क्रम ONE instance of device to see अगर it is
 *			present.
 *	वापस:
 *		0 क्रम FOUND a device
 *		< 0 क्रम error code
 */
अटल पूर्णांक i5400_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा i5400_pvt *pvt;
	काष्ठा edac_mc_layer layers[3];

	अगर (dev_idx >= ARRAY_SIZE(i5400_devs))
		वापस -EINVAL;

	edac_dbg(0, "MC: pdev bus %u dev=0x%x fn=0x%x\n",
		 pdev->bus->number,
		 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));

	/* We only are looking क्रम func 0 of the set */
	अगर (PCI_FUNC(pdev->devfn) != 0)
		वापस -ENODEV;

	/*
	 * allocate a new MC control काष्ठाure
	 *
	 * This drivers uses the DIMM slot as "csrow" and the rest as "channel".
	 */
	layers[0].type = EDAC_MC_LAYER_BRANCH;
	layers[0].size = MAX_BRANCHES;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = CHANNELS_PER_BRANCH;
	layers[1].is_virt_csrow = false;
	layers[2].type = EDAC_MC_LAYER_SLOT;
	layers[2].size = DIMMS_PER_CHANNEL;
	layers[2].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(0, "MC: mci = %p\n", mci);

	mci->pdev = &pdev->dev;	/* record ptr  to the generic device */

	pvt = mci->pvt_info;
	pvt->प्रणाली_address = pdev;	/* Record this device in our निजी */
	pvt->maxch = MAX_CHANNELS;
	pvt->maxdimmperch = DIMMS_PER_CHANNEL;

	/* 'get' the pci devices we want to reserve क्रम our use */
	अगर (i5400_get_devices(mci, dev_idx))
		जाओ fail0;

	/* Time to get serious */
	i5400_get_mc_regs(mci);	/* retrieve the hardware रेजिस्टरs */

	mci->mc_idx = 0;
	mci->mtype_cap = MEM_FLAG_FB_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "i5400_edac.c";
	mci->ctl_name = i5400_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = शून्य;

	/* Set the function poपूर्णांकer to an actual operation function */
	mci->edac_check = i5400_check_error;

	/* initialize the MC control काष्ठाure 'dimms' table
	 * with the mapping and control inक्रमmation */
	अगर (i5400_init_dimms(mci)) अणु
		edac_dbg(0, "MC: Setting mci->edac_cap to EDAC_FLAG_NONE because i5400_init_dimms() returned nonzero value\n");
		mci->edac_cap = EDAC_FLAG_NONE;	/* no dimms found */
	पूर्ण अन्यथा अणु
		edac_dbg(1, "MC: Enable error reporting now\n");
		i5400_enable_error_reporting(mci);
	पूर्ण

	/* add this new MC control काष्ठाure to EDAC's list of MCs */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		/* FIXME: perhaps some code should go here that disables error
		 * reporting अगर we just enabled it
		 */
		जाओ fail1;
	पूर्ण

	i5400_clear_error(mci);

	/* allocating generic PCI control info */
	i5400_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!i5400_pci) अणु
		prपूर्णांकk(KERN_WARNING
			"%s(): Unable to create PCI control\n",
			__func__);
		prपूर्णांकk(KERN_WARNING
			"%s(): PCI error report via EDAC not setup\n",
			__func__);
	पूर्ण

	वापस 0;

	/* Error निकास unwinding stack */
fail1:

	i5400_put_devices(mci);

fail0:
	edac_mc_मुक्त(mci);
	वापस -ENODEV;
पूर्ण

/*
 *	i5400_init_one	स्थिरructor क्रम one instance of device
 *
 * 	वापसs:
 *		negative on error
 *		count (>= 0)
 */
अटल पूर्णांक i5400_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc;

	edac_dbg(0, "MC:\n");

	/* wake up device */
	rc = pci_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* now probe and enable the device */
	वापस i5400_probe1(pdev, id->driver_data);
पूर्ण

/*
 *	i5400_हटाओ_one	deकाष्ठाor क्रम one instance of device
 *
 */
अटल व्योम i5400_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	अगर (i5400_pci)
		edac_pci_release_generic_ctl(i5400_pci);

	mci = edac_mc_del_mc(&pdev->dev);
	अगर (!mci)
		वापस;

	/* retrieve references to resources, and मुक्त those resources */
	i5400_put_devices(mci);

	pci_disable_device(pdev);

	edac_mc_मुक्त(mci);
पूर्ण

/*
 *	pci_device_id	table क्रम which devices we are looking क्रम
 *
 *	The "E500P" device is the first device supported.
 */
अटल स्थिर काष्ठा pci_device_id i5400_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_5400_ERR)पूर्ण,
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i5400_pci_tbl);

/*
 *	i5400_driver	pci_driver काष्ठाure क्रम this module
 *
 */
अटल काष्ठा pci_driver i5400_driver = अणु
	.name = "i5400_edac",
	.probe = i5400_init_one,
	.हटाओ = i5400_हटाओ_one,
	.id_table = i5400_pci_tbl,
पूर्ण;

/*
 *	i5400_init		Module entry function
 *			Try to initialize this module क्रम its devices
 */
अटल पूर्णांक __init i5400_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(2, "MC:\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&i5400_driver);

	वापस (pci_rc < 0) ? pci_rc : 0;
पूर्ण

/*
 *	i5400_निकास()	Module निकास function
 *			Unरेजिस्टर the driver
 */
अटल व्योम __निकास i5400_निकास(व्योम)
अणु
	edac_dbg(2, "MC:\n");
	pci_unरेजिस्टर_driver(&i5400_driver);
पूर्ण

module_init(i5400_init);
module_निकास(i5400_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Woodard <woodard@redhat.com>");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_AUTHOR("Red Hat Inc. (https://www.redhat.com)");
MODULE_DESCRIPTION("MC Driver for Intel I5400 memory controllers - "
		   I5400_REVISION);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
