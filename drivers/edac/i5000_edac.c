<शैली गुरु>
/*
 * Intel 5000(P/V/X) class Memory Controllers kernel module
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Douglas Thompson Linux Networx (http://lnxi.com)
 *	norsk5@xmission.com
 *
 * This module is based on the following करोcument:
 *
 * Intel 5000X Chipset Memory Controller Hub (MCH) - Datasheet
 * 	http://developer.पूर्णांकel.com/design/chipsets/datashts/313070.hपंचांग
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/edac.h>
#समावेश <यंत्र/mmzone.h>

#समावेश "edac_module.h"

/*
 * Alter this version क्रम the I5000 module when modअगरications are made
 */
#घोषणा I5000_REVISION    " Ver: 2.0.12"
#घोषणा EDAC_MOD_STR      "i5000_edac"

#घोषणा i5000_prपूर्णांकk(level, fmt, arg...) \
        edac_prपूर्णांकk(level, "i5000", fmt, ##arg)

#घोषणा i5000_mc_prपूर्णांकk(mci, level, fmt, arg...) \
        edac_mc_chipset_prपूर्णांकk(mci, level, "i5000", fmt, ##arg)

#अगर_अघोषित PCI_DEVICE_ID_INTEL_FBD_0
#घोषणा PCI_DEVICE_ID_INTEL_FBD_0	0x25F5
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_INTEL_FBD_1
#घोषणा PCI_DEVICE_ID_INTEL_FBD_1	0x25F6
#पूर्ण_अगर

/* Device 16,
 * Function 0: System Address
 * Function 1: Memory Branch Map, Control, Errors Register
 * Function 2: FSB Error Registers
 *
 * All 3 functions of Device 16 (0,1,2) share the SAME DID
 */
#घोषणा	PCI_DEVICE_ID_INTEL_I5000_DEV16	0x25F0

/* OFFSETS क्रम Function 0 */

/* OFFSETS क्रम Function 1 */
#घोषणा		AMBASE			0x48
#घोषणा		MAXCH			0x56
#घोषणा		MAXDIMMPERCH		0x57
#घोषणा		TOLM			0x6C
#घोषणा		REDMEMB			0x7C
#घोषणा			RED_ECC_LOCATOR(x)	((x) & 0x3FFFF)
#घोषणा			REC_ECC_LOCATOR_EVEN(x)	((x) & 0x001FF)
#घोषणा			REC_ECC_LOCATOR_ODD(x)	((x) & 0x3FE00)
#घोषणा		MIR0			0x80
#घोषणा		MIR1			0x84
#घोषणा		MIR2			0x88
#घोषणा		AMIR0			0x8C
#घोषणा		AMIR1			0x90
#घोषणा		AMIR2			0x94

#घोषणा		FERR_FAT_FBD		0x98
#घोषणा		NERR_FAT_FBD		0x9C
#घोषणा			EXTRACT_FBDCHAN_INDX(x)	(((x)>>28) & 0x3)
#घोषणा			FERR_FAT_FBDCHAN 0x30000000
#घोषणा			FERR_FAT_M3ERR	0x00000004
#घोषणा			FERR_FAT_M2ERR	0x00000002
#घोषणा			FERR_FAT_M1ERR	0x00000001
#घोषणा			FERR_FAT_MASK	(FERR_FAT_M1ERR | \
						FERR_FAT_M2ERR | \
						FERR_FAT_M3ERR)

#घोषणा		FERR_NF_FBD		0xA0

/* Thermal and SPD or BFD errors */
#घोषणा			FERR_NF_M28ERR	0x01000000
#घोषणा			FERR_NF_M27ERR	0x00800000
#घोषणा			FERR_NF_M26ERR	0x00400000
#घोषणा			FERR_NF_M25ERR	0x00200000
#घोषणा			FERR_NF_M24ERR	0x00100000
#घोषणा			FERR_NF_M23ERR	0x00080000
#घोषणा			FERR_NF_M22ERR	0x00040000
#घोषणा			FERR_NF_M21ERR	0x00020000

/* Correctable errors */
#घोषणा			FERR_NF_M20ERR	0x00010000
#घोषणा			FERR_NF_M19ERR	0x00008000
#घोषणा			FERR_NF_M18ERR	0x00004000
#घोषणा			FERR_NF_M17ERR	0x00002000

/* Non-Retry or redundant Retry errors */
#घोषणा			FERR_NF_M16ERR	0x00001000
#घोषणा			FERR_NF_M15ERR	0x00000800
#घोषणा			FERR_NF_M14ERR	0x00000400
#घोषणा			FERR_NF_M13ERR	0x00000200

/* Uncorrectable errors */
#घोषणा			FERR_NF_M12ERR	0x00000100
#घोषणा			FERR_NF_M11ERR	0x00000080
#घोषणा			FERR_NF_M10ERR	0x00000040
#घोषणा			FERR_NF_M9ERR	0x00000020
#घोषणा			FERR_NF_M8ERR	0x00000010
#घोषणा			FERR_NF_M7ERR	0x00000008
#घोषणा			FERR_NF_M6ERR	0x00000004
#घोषणा			FERR_NF_M5ERR	0x00000002
#घोषणा			FERR_NF_M4ERR	0x00000001

#घोषणा			FERR_NF_UNCORRECTABLE	(FERR_NF_M12ERR | \
							FERR_NF_M11ERR | \
							FERR_NF_M10ERR | \
							FERR_NF_M9ERR | \
							FERR_NF_M8ERR | \
							FERR_NF_M7ERR | \
							FERR_NF_M6ERR | \
							FERR_NF_M5ERR | \
							FERR_NF_M4ERR)
#घोषणा			FERR_NF_CORRECTABLE	(FERR_NF_M20ERR | \
							FERR_NF_M19ERR | \
							FERR_NF_M18ERR | \
							FERR_NF_M17ERR)
#घोषणा			FERR_NF_DIMM_SPARE	(FERR_NF_M27ERR | \
							FERR_NF_M28ERR)
#घोषणा			FERR_NF_THERMAL		(FERR_NF_M26ERR | \
							FERR_NF_M25ERR | \
							FERR_NF_M24ERR | \
							FERR_NF_M23ERR)
#घोषणा			FERR_NF_SPD_PROTOCOL	(FERR_NF_M22ERR)
#घोषणा			FERR_NF_NORTH_CRC	(FERR_NF_M21ERR)
#घोषणा			FERR_NF_NON_RETRY	(FERR_NF_M13ERR | \
							FERR_NF_M14ERR | \
							FERR_NF_M15ERR)

#घोषणा		NERR_NF_FBD		0xA4
#घोषणा			FERR_NF_MASK		(FERR_NF_UNCORRECTABLE | \
							FERR_NF_CORRECTABLE | \
							FERR_NF_DIMM_SPARE | \
							FERR_NF_THERMAL | \
							FERR_NF_SPD_PROTOCOL | \
							FERR_NF_NORTH_CRC | \
							FERR_NF_NON_RETRY)

#घोषणा		EMASK_FBD		0xA8
#घोषणा			EMASK_FBD_M28ERR	0x08000000
#घोषणा			EMASK_FBD_M27ERR	0x04000000
#घोषणा			EMASK_FBD_M26ERR	0x02000000
#घोषणा			EMASK_FBD_M25ERR	0x01000000
#घोषणा			EMASK_FBD_M24ERR	0x00800000
#घोषणा			EMASK_FBD_M23ERR	0x00400000
#घोषणा			EMASK_FBD_M22ERR	0x00200000
#घोषणा			EMASK_FBD_M21ERR	0x00100000
#घोषणा			EMASK_FBD_M20ERR	0x00080000
#घोषणा			EMASK_FBD_M19ERR	0x00040000
#घोषणा			EMASK_FBD_M18ERR	0x00020000
#घोषणा			EMASK_FBD_M17ERR	0x00010000

#घोषणा			EMASK_FBD_M15ERR	0x00004000
#घोषणा			EMASK_FBD_M14ERR	0x00002000
#घोषणा			EMASK_FBD_M13ERR	0x00001000
#घोषणा			EMASK_FBD_M12ERR	0x00000800
#घोषणा			EMASK_FBD_M11ERR	0x00000400
#घोषणा			EMASK_FBD_M10ERR	0x00000200
#घोषणा			EMASK_FBD_M9ERR		0x00000100
#घोषणा			EMASK_FBD_M8ERR		0x00000080
#घोषणा			EMASK_FBD_M7ERR		0x00000040
#घोषणा			EMASK_FBD_M6ERR		0x00000020
#घोषणा			EMASK_FBD_M5ERR		0x00000010
#घोषणा			EMASK_FBD_M4ERR		0x00000008
#घोषणा			EMASK_FBD_M3ERR		0x00000004
#घोषणा			EMASK_FBD_M2ERR		0x00000002
#घोषणा			EMASK_FBD_M1ERR		0x00000001

#घोषणा			ENABLE_EMASK_FBD_FATAL_ERRORS	(EMASK_FBD_M1ERR | \
							EMASK_FBD_M2ERR | \
							EMASK_FBD_M3ERR)

#घोषणा 		ENABLE_EMASK_FBD_UNCORRECTABLE	(EMASK_FBD_M4ERR | \
							EMASK_FBD_M5ERR | \
							EMASK_FBD_M6ERR | \
							EMASK_FBD_M7ERR | \
							EMASK_FBD_M8ERR | \
							EMASK_FBD_M9ERR | \
							EMASK_FBD_M10ERR | \
							EMASK_FBD_M11ERR | \
							EMASK_FBD_M12ERR)
#घोषणा 		ENABLE_EMASK_FBD_CORRECTABLE	(EMASK_FBD_M17ERR | \
							EMASK_FBD_M18ERR | \
							EMASK_FBD_M19ERR | \
							EMASK_FBD_M20ERR)
#घोषणा			ENABLE_EMASK_FBD_DIMM_SPARE	(EMASK_FBD_M27ERR | \
							EMASK_FBD_M28ERR)
#घोषणा			ENABLE_EMASK_FBD_THERMALS	(EMASK_FBD_M26ERR | \
							EMASK_FBD_M25ERR | \
							EMASK_FBD_M24ERR | \
							EMASK_FBD_M23ERR)
#घोषणा			ENABLE_EMASK_FBD_SPD_PROTOCOL	(EMASK_FBD_M22ERR)
#घोषणा			ENABLE_EMASK_FBD_NORTH_CRC	(EMASK_FBD_M21ERR)
#घोषणा			ENABLE_EMASK_FBD_NON_RETRY	(EMASK_FBD_M15ERR | \
							EMASK_FBD_M14ERR | \
							EMASK_FBD_M13ERR)

#घोषणा		ENABLE_EMASK_ALL	(ENABLE_EMASK_FBD_NON_RETRY | \
					ENABLE_EMASK_FBD_NORTH_CRC | \
					ENABLE_EMASK_FBD_SPD_PROTOCOL | \
					ENABLE_EMASK_FBD_THERMALS | \
					ENABLE_EMASK_FBD_DIMM_SPARE | \
					ENABLE_EMASK_FBD_FATAL_ERRORS | \
					ENABLE_EMASK_FBD_CORRECTABLE | \
					ENABLE_EMASK_FBD_UNCORRECTABLE)

#घोषणा		ERR0_FBD		0xAC
#घोषणा		ERR1_FBD		0xB0
#घोषणा		ERR2_FBD		0xB4
#घोषणा		MCERR_FBD		0xB8
#घोषणा		NRECMEMA		0xBE
#घोषणा			NREC_BANK(x)		(((x)>>12) & 0x7)
#घोषणा			NREC_RDWR(x)		(((x)>>11) & 1)
#घोषणा			NREC_RANK(x)		(((x)>>8) & 0x7)
#घोषणा		NRECMEMB		0xC0
#घोषणा			NREC_CAS(x)		(((x)>>16) & 0xFFF)
#घोषणा			NREC_RAS(x)		((x) & 0x7FFF)
#घोषणा		NRECFGLOG		0xC4
#घोषणा		NREEECFBDA		0xC8
#घोषणा		NREEECFBDB		0xCC
#घोषणा		NREEECFBDC		0xD0
#घोषणा		NREEECFBDD		0xD4
#घोषणा		NREEECFBDE		0xD8
#घोषणा		REDMEMA			0xDC
#घोषणा		RECMEMA			0xE2
#घोषणा			REC_BANK(x)		(((x)>>12) & 0x7)
#घोषणा			REC_RDWR(x)		(((x)>>11) & 1)
#घोषणा			REC_RANK(x)		(((x)>>8) & 0x7)
#घोषणा		RECMEMB			0xE4
#घोषणा			REC_CAS(x)		(((x)>>16) & 0xFFFFFF)
#घोषणा			REC_RAS(x)		((x) & 0x7FFF)
#घोषणा		RECFGLOG		0xE8
#घोषणा		RECFBDA			0xEC
#घोषणा		RECFBDB			0xF0
#घोषणा		RECFBDC			0xF4
#घोषणा		RECFBDD			0xF8
#घोषणा		RECFBDE			0xFC

/* OFFSETS क्रम Function 2 */

/*
 * Device 21,
 * Function 0: Memory Map Branch 0
 *
 * Device 22,
 * Function 0: Memory Map Branch 1
 */
#घोषणा PCI_DEVICE_ID_I5000_BRANCH_0	0x25F5
#घोषणा PCI_DEVICE_ID_I5000_BRANCH_1	0x25F6

#घोषणा AMB_PRESENT_0	0x64
#घोषणा AMB_PRESENT_1	0x66
#घोषणा MTR0		0x80
#घोषणा MTR1		0x84
#घोषणा MTR2		0x88
#घोषणा MTR3		0x8C

#घोषणा NUM_MTRS		4
#घोषणा CHANNELS_PER_BRANCH	2
#घोषणा MAX_BRANCHES		2

/* Defines to extract the various fields from the
 *	MTRx - Memory Technology Registers
 */
#घोषणा MTR_DIMMS_PRESENT(mtr)		((mtr) & (0x1 << 8))
#घोषणा MTR_DRAM_WIDTH(mtr)		((((mtr) >> 6) & 0x1) ? 8 : 4)
#घोषणा MTR_DRAM_BANKS(mtr)		((((mtr) >> 5) & 0x1) ? 8 : 4)
#घोषणा MTR_DRAM_BANKS_ADDR_BITS(mtr)	((MTR_DRAM_BANKS(mtr) == 8) ? 3 : 2)
#घोषणा MTR_DIMM_RANK(mtr)		(((mtr) >> 4) & 0x1)
#घोषणा MTR_DIMM_RANK_ADDR_BITS(mtr)	(MTR_DIMM_RANK(mtr) ? 2 : 1)
#घोषणा MTR_DIMM_ROWS(mtr)		(((mtr) >> 2) & 0x3)
#घोषणा MTR_DIMM_ROWS_ADDR_BITS(mtr)	(MTR_DIMM_ROWS(mtr) + 13)
#घोषणा MTR_DIMM_COLS(mtr)		((mtr) & 0x3)
#घोषणा MTR_DIMM_COLS_ADDR_BITS(mtr)	(MTR_DIMM_COLS(mtr) + 10)

/* enables the report of miscellaneous messages as CE errors - शेष off */
अटल पूर्णांक misc_messages;

/* Enumeration of supported devices */
क्रमागत i5000_chips अणु
	I5000P = 0,
	I5000V = 1,		/* future */
	I5000X = 2		/* future */
पूर्ण;

/* Device name and रेजिस्टर DID (Device ID) */
काष्ठा i5000_dev_info अणु
	स्थिर अक्षर *ctl_name;	/* name क्रम this device */
	u16 fsb_mapping_errors;	/* DID क्रम the branchmap,control */
पूर्ण;

/* Table of devices attributes supported by this driver */
अटल स्थिर काष्ठा i5000_dev_info i5000_devs[] = अणु
	[I5000P] = अणु
		.ctl_name = "I5000",
		.fsb_mapping_errors = PCI_DEVICE_ID_INTEL_I5000_DEV16,
	पूर्ण,
पूर्ण;

काष्ठा i5000_dimm_info अणु
	पूर्णांक megabytes;		/* size, 0 means not present  */
	पूर्णांक dual_rank;
पूर्ण;

#घोषणा	MAX_CHANNELS	6	/* max possible channels */
#घोषणा MAX_CSROWS	(8*2)	/* max possible csrows per channel */

/* driver निजी data काष्ठाure */
काष्ठा i5000_pvt अणु
	काष्ठा pci_dev *प्रणाली_address;	/* 16.0 */
	काष्ठा pci_dev *branchmap_werrors;	/* 16.1 */
	काष्ठा pci_dev *fsb_error_regs;	/* 16.2 */
	काष्ठा pci_dev *branch_0;	/* 21.0 */
	काष्ठा pci_dev *branch_1;	/* 22.0 */

	u16 tolm;		/* top of low memory */
	जोड़ अणु
		u64 ambase;		/* AMB BAR */
		काष्ठा अणु
			u32 ambase_bottom;
			u32 ambase_top;
		पूर्ण u __packed;
	पूर्ण;

	u16 mir0, mir1, mir2;

	u16 b0_mtr[NUM_MTRS];	/* Memory Technlogy Reg */
	u16 b0_ambpresent0;	/* Branch 0, Channel 0 */
	u16 b0_ambpresent1;	/* Brnach 0, Channel 1 */

	u16 b1_mtr[NUM_MTRS];	/* Memory Technlogy Reg */
	u16 b1_ambpresent0;	/* Branch 1, Channel 8 */
	u16 b1_ambpresent1;	/* Branch 1, Channel 1 */

	/* DIMM inक्रमmation matrix, allocating architecture maximums */
	काष्ठा i5000_dimm_info dimm_info[MAX_CSROWS][MAX_CHANNELS];

	/* Actual values क्रम this controller */
	पूर्णांक maxch;		/* Max channels */
	पूर्णांक maxdimmperch;	/* Max DIMMs per channel */
पूर्ण;

/* I5000 MCH error inक्रमmation retrieved from Hardware */
काष्ठा i5000_error_info अणु

	/* These रेजिस्टरs are always पढ़ो from the MC */
	u32 ferr_fat_fbd;	/* First Errors Fatal */
	u32 nerr_fat_fbd;	/* Next Errors Fatal */
	u32 ferr_nf_fbd;	/* First Errors Non-Fatal */
	u32 nerr_nf_fbd;	/* Next Errors Non-Fatal */

	/* These रेजिस्टरs are input ONLY अगर there was a Recoverable  Error */
	u32 redmemb;		/* Recoverable Mem Data Error log B */
	u16 recmema;		/* Recoverable Mem Error log A */
	u32 recmemb;		/* Recoverable Mem Error log B */

	/* These रेजिस्टरs are input ONLY अगर there was a
	 * Non-Recoverable Error */
	u16 nrecmema;		/* Non-Recoverable Mem log A */
	u32 nrecmemb;		/* Non-Recoverable Mem log B */

पूर्ण;

अटल काष्ठा edac_pci_ctl_info *i5000_pci;

/*
 *	i5000_get_error_info	Retrieve the hardware error inक्रमmation from
 *				the hardware and cache it in the 'info'
 *				काष्ठाure
 */
अटल व्योम i5000_get_error_info(काष्ठा mem_ctl_info *mci,
				 काष्ठा i5000_error_info *info)
अणु
	काष्ठा i5000_pvt *pvt;
	u32 value;

	pvt = mci->pvt_info;

	/* पढ़ो in the 1st FATAL error रेजिस्टर */
	pci_पढ़ो_config_dword(pvt->branchmap_werrors, FERR_FAT_FBD, &value);

	/* Mask only the bits that the करोc says are valid
	 */
	value &= (FERR_FAT_FBDCHAN | FERR_FAT_MASK);

	/* If there is an error, then पढ़ो in the */
	/* NEXT FATAL error रेजिस्टर and the Memory Error Log Register A */
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
 * i5000_process_fatal_error_info(काष्ठा mem_ctl_info *mci,
 * 					काष्ठा i5000_error_info *info,
 * 					पूर्णांक handle_errors);
 *
 *	handle the Intel FATAL errors, अगर any
 */
अटल व्योम i5000_process_fatal_error_info(काष्ठा mem_ctl_info *mci,
					काष्ठा i5000_error_info *info,
					पूर्णांक handle_errors)
अणु
	अक्षर msg[EDAC_MC_LABEL_LEN + 1 + 160];
	अक्षर *specअगरic = शून्य;
	u32 allErrors;
	पूर्णांक channel;
	पूर्णांक bank;
	पूर्णांक rank;
	पूर्णांक rdwr;
	पूर्णांक ras, cas;

	/* mask off the Error bits that are possible */
	allErrors = (info->ferr_fat_fbd & FERR_FAT_MASK);
	अगर (!allErrors)
		वापस;		/* अगर no error, वापस now */

	channel = EXTRACT_FBDCHAN_INDX(info->ferr_fat_fbd);

	/* Use the NON-Recoverable macros to extract data */
	bank = NREC_BANK(info->nrecmema);
	rank = NREC_RANK(info->nrecmema);
	rdwr = NREC_RDWR(info->nrecmema);
	ras = NREC_RAS(info->nrecmemb);
	cas = NREC_CAS(info->nrecmemb);

	edac_dbg(0, "\t\tCSROW= %d  Channel= %d (DRAM Bank= %d rdwr= %s ras= %d cas= %d)\n",
		 rank, channel, bank,
		 rdwr ? "Write" : "Read", ras, cas);

	/* Only 1 bit will be on */
	चयन (allErrors) अणु
	हाल FERR_FAT_M1ERR:
		specअगरic = "Alert on non-redundant retry or fast "
				"reset timeout";
		अवरोध;
	हाल FERR_FAT_M2ERR:
		specअगरic = "Northbound CRC error on non-redundant "
				"retry";
		अवरोध;
	हाल FERR_FAT_M3ERR:
		अणु
		अटल पूर्णांक करोne;

		/*
		 * This error is generated to inक्रमm that the पूर्णांकelligent
		 * throttling is disabled and the temperature passed the
		 * specअगरied middle poपूर्णांक. Since this is something the BIOS
		 * should take care of, we'll warn only once to aव्योम
		 * worthlessly flooding the log.
		 */
		अगर (करोne)
			वापस;
		करोne++;

		specअगरic = ">Tmid Thermal event with intelligent "
			   "throttling disabled";
		पूर्ण
		अवरोध;
	पूर्ण

	/* Form out message */
	snम_लिखो(msg, माप(msg),
		 "Bank=%d RAS=%d CAS=%d FATAL Err=0x%x (%s)",
		 bank, ras, cas, allErrors, specअगरic);

	/* Call the helper to output message */
	edac_mc_handle_error(HW_EVENT_ERR_FATAL, mci, 1, 0, 0, 0,
			     channel >> 1, channel & 1, rank,
			     rdwr ? "Write error" : "Read error",
			     msg);
पूर्ण

/*
 * i5000_process_fatal_error_info(काष्ठा mem_ctl_info *mci,
 * 				काष्ठा i5000_error_info *info,
 * 				पूर्णांक handle_errors);
 *
 *	handle the Intel NON-FATAL errors, अगर any
 */
अटल व्योम i5000_process_nonfatal_error_info(काष्ठा mem_ctl_info *mci,
					काष्ठा i5000_error_info *info,
					पूर्णांक handle_errors)
अणु
	अक्षर msg[EDAC_MC_LABEL_LEN + 1 + 170];
	अक्षर *specअगरic = शून्य;
	u32 allErrors;
	u32 ue_errors;
	u32 ce_errors;
	u32 misc_errors;
	पूर्णांक branch;
	पूर्णांक channel;
	पूर्णांक bank;
	पूर्णांक rank;
	पूर्णांक rdwr;
	पूर्णांक ras, cas;

	/* mask off the Error bits that are possible */
	allErrors = (info->ferr_nf_fbd & FERR_NF_MASK);
	अगर (!allErrors)
		वापस;		/* अगर no error, वापस now */

	/* ONLY ONE of the possible error bits will be set, as per the करोcs */
	ue_errors = allErrors & FERR_NF_UNCORRECTABLE;
	अगर (ue_errors) अणु
		edac_dbg(0, "\tUncorrected bits= 0x%x\n", ue_errors);

		branch = EXTRACT_FBDCHAN_INDX(info->ferr_nf_fbd);

		/*
		 * According with i5000 datasheet, bit 28 has no signअगरicance
		 * क्रम errors M4Err-M12Err and M17Err-M21Err, on FERR_NF_FBD
		 */
		channel = branch & 2;

		bank = NREC_BANK(info->nrecmema);
		rank = NREC_RANK(info->nrecmema);
		rdwr = NREC_RDWR(info->nrecmema);
		ras = NREC_RAS(info->nrecmemb);
		cas = NREC_CAS(info->nrecmemb);

		edac_dbg(0, "\t\tCSROW= %d  Channels= %d,%d  (Branch= %d DRAM Bank= %d rdwr= %s ras= %d cas= %d)\n",
			 rank, channel, channel + 1, branch >> 1, bank,
			 rdwr ? "Write" : "Read", ras, cas);

		चयन (ue_errors) अणु
		हाल FERR_NF_M12ERR:
			specअगरic = "Non-Aliased Uncorrectable Patrol Data ECC";
			अवरोध;
		हाल FERR_NF_M11ERR:
			specअगरic = "Non-Aliased Uncorrectable Spare-Copy "
					"Data ECC";
			अवरोध;
		हाल FERR_NF_M10ERR:
			specअगरic = "Non-Aliased Uncorrectable Mirrored Demand "
					"Data ECC";
			अवरोध;
		हाल FERR_NF_M9ERR:
			specअगरic = "Non-Aliased Uncorrectable Non-Mirrored "
					"Demand Data ECC";
			अवरोध;
		हाल FERR_NF_M8ERR:
			specअगरic = "Aliased Uncorrectable Patrol Data ECC";
			अवरोध;
		हाल FERR_NF_M7ERR:
			specअगरic = "Aliased Uncorrectable Spare-Copy Data ECC";
			अवरोध;
		हाल FERR_NF_M6ERR:
			specअगरic = "Aliased Uncorrectable Mirrored Demand "
					"Data ECC";
			अवरोध;
		हाल FERR_NF_M5ERR:
			specअगरic = "Aliased Uncorrectable Non-Mirrored Demand "
					"Data ECC";
			अवरोध;
		हाल FERR_NF_M4ERR:
			specअगरic = "Uncorrectable Data ECC on Replay";
			अवरोध;
		पूर्ण

		/* Form out message */
		snम_लिखो(msg, माप(msg),
			 "Rank=%d Bank=%d RAS=%d CAS=%d, UE Err=0x%x (%s)",
			 rank, bank, ras, cas, ue_errors, specअगरic);

		/* Call the helper to output message */
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				channel >> 1, -1, rank,
				rdwr ? "Write error" : "Read error",
				msg);
	पूर्ण

	/* Check correctable errors */
	ce_errors = allErrors & FERR_NF_CORRECTABLE;
	अगर (ce_errors) अणु
		edac_dbg(0, "\tCorrected bits= 0x%x\n", ce_errors);

		branch = EXTRACT_FBDCHAN_INDX(info->ferr_nf_fbd);

		channel = 0;
		अगर (REC_ECC_LOCATOR_ODD(info->redmemb))
			channel = 1;

		/* Convert channel to be based from zero, instead of
		 * from branch base of 0 */
		channel += branch;

		bank = REC_BANK(info->recmema);
		rank = REC_RANK(info->recmema);
		rdwr = REC_RDWR(info->recmema);
		ras = REC_RAS(info->recmemb);
		cas = REC_CAS(info->recmemb);

		edac_dbg(0, "\t\tCSROW= %d Channel= %d  (Branch %d DRAM Bank= %d rdwr= %s ras= %d cas= %d)\n",
			 rank, channel, branch >> 1, bank,
			 rdwr ? "Write" : "Read", ras, cas);

		चयन (ce_errors) अणु
		हाल FERR_NF_M17ERR:
			specअगरic = "Correctable Non-Mirrored Demand Data ECC";
			अवरोध;
		हाल FERR_NF_M18ERR:
			specअगरic = "Correctable Mirrored Demand Data ECC";
			अवरोध;
		हाल FERR_NF_M19ERR:
			specअगरic = "Correctable Spare-Copy Data ECC";
			अवरोध;
		हाल FERR_NF_M20ERR:
			specअगरic = "Correctable Patrol Data ECC";
			अवरोध;
		पूर्ण

		/* Form out message */
		snम_लिखो(msg, माप(msg),
			 "Rank=%d Bank=%d RDWR=%s RAS=%d "
			 "CAS=%d, CE Err=0x%x (%s))", branch >> 1, bank,
			 rdwr ? "Write" : "Read", ras, cas, ce_errors,
			 specअगरic);

		/* Call the helper to output message */
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0,
				channel >> 1, channel % 2, rank,
				rdwr ? "Write error" : "Read error",
				msg);
	पूर्ण

	अगर (!misc_messages)
		वापस;

	misc_errors = allErrors & (FERR_NF_NON_RETRY | FERR_NF_NORTH_CRC |
				   FERR_NF_SPD_PROTOCOL | FERR_NF_DIMM_SPARE);
	अगर (misc_errors) अणु
		चयन (misc_errors) अणु
		हाल FERR_NF_M13ERR:
			specअगरic = "Non-Retry or Redundant Retry FBD Memory "
					"Alert or Redundant Fast Reset Timeout";
			अवरोध;
		हाल FERR_NF_M14ERR:
			specअगरic = "Non-Retry or Redundant Retry FBD "
					"Configuration Alert";
			अवरोध;
		हाल FERR_NF_M15ERR:
			specअगरic = "Non-Retry or Redundant Retry FBD "
					"Northbound CRC error on read data";
			अवरोध;
		हाल FERR_NF_M21ERR:
			specअगरic = "FBD Northbound CRC error on "
					"FBD Sync Status";
			अवरोध;
		हाल FERR_NF_M22ERR:
			specअगरic = "SPD protocol error";
			अवरोध;
		हाल FERR_NF_M27ERR:
			specअगरic = "DIMM-spare copy started";
			अवरोध;
		हाल FERR_NF_M28ERR:
			specअगरic = "DIMM-spare copy completed";
			अवरोध;
		पूर्ण
		branch = EXTRACT_FBDCHAN_INDX(info->ferr_nf_fbd);

		/* Form out message */
		snम_लिखो(msg, माप(msg),
			 "Err=%#x (%s)", misc_errors, specअगरic);

		/* Call the helper to output message */
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0,
				branch >> 1, -1, -1,
				"Misc error", msg);
	पूर्ण
पूर्ण

/*
 *	i5000_process_error_info	Process the error info that is
 *	in the 'info' काष्ठाure, previously retrieved from hardware
 */
अटल व्योम i5000_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i5000_error_info *info,
				पूर्णांक handle_errors)
अणु
	/* First handle any fatal errors that occurred */
	i5000_process_fatal_error_info(mci, info, handle_errors);

	/* now handle any non-fatal errors that occurred */
	i5000_process_nonfatal_error_info(mci, info, handle_errors);
पूर्ण

/*
 *	i5000_clear_error	Retrieve any error from the hardware
 *				but करो NOT process that error.
 *				Used क्रम 'clearing' out of previous errors
 *				Called by the Core module.
 */
अटल व्योम i5000_clear_error(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5000_error_info info;

	i5000_get_error_info(mci, &info);
पूर्ण

/*
 *	i5000_check_error	Retrieve and process errors reported by the
 *				hardware. Called by the Core module.
 */
अटल व्योम i5000_check_error(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5000_error_info info;

	i5000_get_error_info(mci, &info);
	i5000_process_error_info(mci, &info, 1);
पूर्ण

/*
 *	i5000_get_devices	Find and perक्रमm 'get' operation on the MCH's
 *			device/functions we want to reference क्रम this driver
 *
 *			Need to 'get' device 16 func 1 and func 2
 */
अटल पूर्णांक i5000_get_devices(काष्ठा mem_ctl_info *mci, पूर्णांक dev_idx)
अणु
	//स्थिर काष्ठा i5000_dev_info *i5000_dev = &i5000_devs[dev_idx];
	काष्ठा i5000_pvt *pvt;
	काष्ठा pci_dev *pdev;

	pvt = mci->pvt_info;

	/* Attempt to 'get' the MCH रेजिस्टर we want */
	pdev = शून्य;
	जबतक (1) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_I5000_DEV16, pdev);

		/* End of list, leave */
		अगर (pdev == शून्य) अणु
			i5000_prपूर्णांकk(KERN_ERR,
				"'system address,Process Bus' "
				"device not found:"
				"vendor 0x%x device 0x%x FUNC 1 "
				"(broken BIOS?)\n",
				PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_I5000_DEV16);

			वापस 1;
		पूर्ण

		/* Scan क्रम device 16 func 1 */
		अगर (PCI_FUNC(pdev->devfn) == 1)
			अवरोध;
	पूर्ण

	pvt->branchmap_werrors = pdev;

	/* Attempt to 'get' the MCH रेजिस्टर we want */
	pdev = शून्य;
	जबतक (1) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_I5000_DEV16, pdev);

		अगर (pdev == शून्य) अणु
			i5000_prपूर्णांकk(KERN_ERR,
				"MC: 'branchmap,control,errors' "
				"device not found:"
				"vendor 0x%x device 0x%x Func 2 "
				"(broken BIOS?)\n",
				PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_I5000_DEV16);

			pci_dev_put(pvt->branchmap_werrors);
			वापस 1;
		पूर्ण

		/* Scan क्रम device 16 func 1 */
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

	pdev = शून्य;
	pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_I5000_BRANCH_0, pdev);

	अगर (pdev == शून्य) अणु
		i5000_prपूर्णांकk(KERN_ERR,
			"MC: 'BRANCH 0' device not found:"
			"vendor 0x%x device 0x%x Func 0 (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_I5000_BRANCH_0);

		pci_dev_put(pvt->branchmap_werrors);
		pci_dev_put(pvt->fsb_error_regs);
		वापस 1;
	पूर्ण

	pvt->branch_0 = pdev;

	/* If this device claims to have more than 2 channels then
	 * fetch Branch 1's inक्रमmation
	 */
	अगर (pvt->maxch >= CHANNELS_PER_BRANCH) अणु
		pdev = शून्य;
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_I5000_BRANCH_1, pdev);

		अगर (pdev == शून्य) अणु
			i5000_prपूर्णांकk(KERN_ERR,
				"MC: 'BRANCH 1' device not found:"
				"vendor 0x%x device 0x%x Func 0 "
				"(broken BIOS?)\n",
				PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_I5000_BRANCH_1);

			pci_dev_put(pvt->branchmap_werrors);
			pci_dev_put(pvt->fsb_error_regs);
			pci_dev_put(pvt->branch_0);
			वापस 1;
		पूर्ण

		pvt->branch_1 = pdev;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	i5000_put_devices	'put' all the devices that we have
 *				reserved via 'get'
 */
अटल व्योम i5000_put_devices(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5000_pvt *pvt;

	pvt = mci->pvt_info;

	pci_dev_put(pvt->branchmap_werrors);	/* FUNC 1 */
	pci_dev_put(pvt->fsb_error_regs);	/* FUNC 2 */
	pci_dev_put(pvt->branch_0);	/* DEV 21 */

	/* Only अगर more than 2 channels करो we release the second branch */
	अगर (pvt->maxch >= CHANNELS_PER_BRANCH)
		pci_dev_put(pvt->branch_1);	/* DEV 22 */
पूर्ण

/*
 *	determine_amb_resent
 *
 *		the inक्रमmation is contained in NUM_MTRS dअगरferent रेजिस्टरs
 *		determineing which of the NUM_MTRS requires knowing
 *		which channel is in question
 *
 *	2 branches, each with 2 channels
 *		b0_ambpresent0 क्रम channel '0'
 *		b0_ambpresent1 क्रम channel '1'
 *		b1_ambpresent0 क्रम channel '2'
 *		b1_ambpresent1 क्रम channel '3'
 */
अटल पूर्णांक determine_amb_present_reg(काष्ठा i5000_pvt *pvt, पूर्णांक channel)
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
 * determine_mtr(pvt, csrow, channel)
 *
 *	वापस the proper MTR रेजिस्टर as determine by the csrow and channel desired
 */
अटल पूर्णांक determine_mtr(काष्ठा i5000_pvt *pvt, पूर्णांक slot, पूर्णांक channel)
अणु
	पूर्णांक mtr;

	अगर (channel < CHANNELS_PER_BRANCH)
		mtr = pvt->b0_mtr[slot];
	अन्यथा
		mtr = pvt->b1_mtr[slot];

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
	edac_dbg(2, "\t\tNUMBANK: %d bank(s)\n", MTR_DRAM_BANKS(mtr));
	edac_dbg(2, "\t\tNUMRANK: %s\n",
		 MTR_DIMM_RANK(mtr) ? "double" : "single");
	edac_dbg(2, "\t\tNUMROW: %s\n",
		 MTR_DIMM_ROWS(mtr) == 0 ? "8,192 - 13 rows" :
		 MTR_DIMM_ROWS(mtr) == 1 ? "16,384 - 14 rows" :
		 MTR_DIMM_ROWS(mtr) == 2 ? "32,768 - 15 rows" :
		 "reserved");
	edac_dbg(2, "\t\tNUMCOL: %s\n",
		 MTR_DIMM_COLS(mtr) == 0 ? "1,024 - 10 columns" :
		 MTR_DIMM_COLS(mtr) == 1 ? "2,048 - 11 columns" :
		 MTR_DIMM_COLS(mtr) == 2 ? "4,096 - 12 columns" :
		 "reserved");
पूर्ण

अटल व्योम handle_channel(काष्ठा i5000_pvt *pvt, पूर्णांक slot, पूर्णांक channel,
			काष्ठा i5000_dimm_info *dinfo)
अणु
	पूर्णांक mtr;
	पूर्णांक amb_present_reg;
	पूर्णांक addrBits;

	mtr = determine_mtr(pvt, slot, channel);
	अगर (MTR_DIMMS_PRESENT(mtr)) अणु
		amb_present_reg = determine_amb_present_reg(pvt, channel);

		/* Determine अगर there is a DIMM present in this DIMM slot */
		अगर (amb_present_reg) अणु
			dinfo->dual_rank = MTR_DIMM_RANK(mtr);

			/* Start with the number of bits क्रम a Bank
				* on the DRAM */
			addrBits = MTR_DRAM_BANKS_ADDR_BITS(mtr);
			/* Add the number of ROW bits */
			addrBits += MTR_DIMM_ROWS_ADDR_BITS(mtr);
			/* add the number of COLUMN bits */
			addrBits += MTR_DIMM_COLS_ADDR_BITS(mtr);

			/* Dual-rank memories have twice the size */
			अगर (dinfo->dual_rank)
				addrBits++;

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
अटल व्योम calculate_dimm_size(काष्ठा i5000_pvt *pvt)
अणु
	काष्ठा i5000_dimm_info *dinfo;
	पूर्णांक slot, channel, branch;
	अक्षर *p, *mem_buffer;
	पूर्णांक space, n;

	/* ================= Generate some debug output ================= */
	space = PAGE_SIZE;
	mem_buffer = p = kदो_स्मृति(space, GFP_KERNEL);
	अगर (p == शून्य) अणु
		i5000_prपूर्णांकk(KERN_ERR, "MC: %s:%s() kmalloc() failed\n",
			__खाता__, __func__);
		वापस;
	पूर्ण

	/* Scan all the actual slots
	 * and calculate the inक्रमmation क्रम each DIMM
	 * Start with the highest slot first, to display it first
	 * and work toward the 0th slot
	 */
	क्रम (slot = pvt->maxdimmperch - 1; slot >= 0; slot--) अणु

		/* on an odd slot, first output a 'boundary' marker,
		 * then reset the message buffer  */
		अगर (slot & 0x1) अणु
			n = snम_लिखो(p, space, "--------------------------"
				"--------------------------------");
			p += n;
			space -= n;
			edac_dbg(2, "%s\n", mem_buffer);
			p = mem_buffer;
			space = PAGE_SIZE;
		पूर्ण
		n = snम_लिखो(p, space, "slot %2d    ", slot);
		p += n;
		space -= n;

		क्रम (channel = 0; channel < pvt->maxch; channel++) अणु
			dinfo = &pvt->dimm_info[slot][channel];
			handle_channel(pvt, slot, channel, dinfo);
			अगर (dinfo->megabytes)
				n = snम_लिखो(p, space, "%4d MB %dR| ",
					     dinfo->megabytes, dinfo->dual_rank + 1);
			अन्यथा
				n = snम_लिखो(p, space, "%4d MB   | ", 0);
			p += n;
			space -= n;
		पूर्ण
		p += n;
		space -= n;
		edac_dbg(2, "%s\n", mem_buffer);
		p = mem_buffer;
		space = PAGE_SIZE;
	पूर्ण

	/* Output the last bottom 'boundary' marker */
	n = snम_लिखो(p, space, "--------------------------"
		"--------------------------------");
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
 *	i5000_get_mc_regs	पढ़ो in the necessary रेजिस्टरs and
 *				cache locally
 *
 *			Fills in the निजी data members
 */
अटल व्योम i5000_get_mc_regs(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5000_pvt *pvt;
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
	edac_dbg(2, "TOLM (number of 256M regions) =%u (0x%x)\n",
		 pvt->tolm, pvt->tolm);

	actual_tolm = pvt->tolm << 28;
	edac_dbg(2, "Actual TOLM byte addr=%u (0x%x)\n",
		 actual_tolm, actual_tolm);

	pci_पढ़ो_config_word(pvt->branchmap_werrors, MIR0, &pvt->mir0);
	pci_पढ़ो_config_word(pvt->branchmap_werrors, MIR1, &pvt->mir1);
	pci_पढ़ो_config_word(pvt->branchmap_werrors, MIR2, &pvt->mir2);

	/* Get the MIR[0-2] regs */
	limit = (pvt->mir0 >> 4) & 0x0FFF;
	way0 = pvt->mir0 & 0x1;
	way1 = pvt->mir0 & 0x2;
	edac_dbg(2, "MIR0: limit= 0x%x  WAY1= %u  WAY0= %x\n",
		 limit, way1, way0);
	limit = (pvt->mir1 >> 4) & 0x0FFF;
	way0 = pvt->mir1 & 0x1;
	way1 = pvt->mir1 & 0x2;
	edac_dbg(2, "MIR1: limit= 0x%x  WAY1= %u  WAY0= %x\n",
		 limit, way1, way0);
	limit = (pvt->mir2 >> 4) & 0x0FFF;
	way0 = pvt->mir2 & 0x1;
	way1 = pvt->mir2 & 0x2;
	edac_dbg(2, "MIR2: limit= 0x%x  WAY1= %u  WAY0= %x\n",
		 limit, way1, way0);

	/* Get the MTR[0-3] regs */
	क्रम (slot_row = 0; slot_row < NUM_MTRS; slot_row++) अणु
		पूर्णांक where = MTR0 + (slot_row * माप(u32));

		pci_पढ़ो_config_word(pvt->branch_0, where,
				&pvt->b0_mtr[slot_row]);

		edac_dbg(2, "MTR%d where=0x%x B0 value=0x%x\n",
			 slot_row, where, pvt->b0_mtr[slot_row]);

		अगर (pvt->maxch >= CHANNELS_PER_BRANCH) अणु
			pci_पढ़ो_config_word(pvt->branch_1, where,
					&pvt->b1_mtr[slot_row]);
			edac_dbg(2, "MTR%d where=0x%x B1 value=0x%x\n",
				 slot_row, where, pvt->b1_mtr[slot_row]);
		पूर्ण अन्यथा अणु
			pvt->b1_mtr[slot_row] = 0;
		पूर्ण
	पूर्ण

	/* Read and dump branch 0's MTRs */
	edac_dbg(2, "Memory Technology Registers:\n");
	edac_dbg(2, "   Branch 0:\n");
	क्रम (slot_row = 0; slot_row < NUM_MTRS; slot_row++) अणु
		decode_mtr(slot_row, pvt->b0_mtr[slot_row]);
	पूर्ण
	pci_पढ़ो_config_word(pvt->branch_0, AMB_PRESENT_0,
			&pvt->b0_ambpresent0);
	edac_dbg(2, "\t\tAMB-Branch 0-present0 0x%x:\n", pvt->b0_ambpresent0);
	pci_पढ़ो_config_word(pvt->branch_0, AMB_PRESENT_1,
			&pvt->b0_ambpresent1);
	edac_dbg(2, "\t\tAMB-Branch 0-present1 0x%x:\n", pvt->b0_ambpresent1);

	/* Only अगर we have 2 branchs (4 channels) */
	अगर (pvt->maxch < CHANNELS_PER_BRANCH) अणु
		pvt->b1_ambpresent0 = 0;
		pvt->b1_ambpresent1 = 0;
	पूर्ण अन्यथा अणु
		/* Read and dump  branch 1's MTRs */
		edac_dbg(2, "   Branch 1:\n");
		क्रम (slot_row = 0; slot_row < NUM_MTRS; slot_row++) अणु
			decode_mtr(slot_row, pvt->b1_mtr[slot_row]);
		पूर्ण
		pci_पढ़ो_config_word(pvt->branch_1, AMB_PRESENT_0,
				&pvt->b1_ambpresent0);
		edac_dbg(2, "\t\tAMB-Branch 1-present0 0x%x:\n",
			 pvt->b1_ambpresent0);
		pci_पढ़ो_config_word(pvt->branch_1, AMB_PRESENT_1,
				&pvt->b1_ambpresent1);
		edac_dbg(2, "\t\tAMB-Branch 1-present1 0x%x:\n",
			 pvt->b1_ambpresent1);
	पूर्ण

	/* Go and determine the size of each DIMM and place in an
	 * orderly matrix */
	calculate_dimm_size(pvt);
पूर्ण

/*
 *	i5000_init_csrows	Initialize the 'csrows' table within
 *				the mci control	काष्ठाure with the
 *				addressing of memory.
 *
 *	वापस:
 *		0	success
 *		1	no actual memory found on this MC
 */
अटल पूर्णांक i5000_init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5000_pvt *pvt;
	काष्ठा dimm_info *dimm;
	पूर्णांक empty;
	पूर्णांक max_csrows;
	पूर्णांक mtr;
	पूर्णांक csrow_megs;
	पूर्णांक channel;
	पूर्णांक slot;

	pvt = mci->pvt_info;
	max_csrows = pvt->maxdimmperch * 2;

	empty = 1;		/* Assume NO memory */

	/*
	 * FIXME: The memory layout used to map slot/channel पूर्णांकo the
	 * real memory architecture is weird: branch+slot are "csrows"
	 * and channel is channel. That required an extra array (dimm_info)
	 * to map the dimms. A good cleanup would be to हटाओ this array,
	 * and करो a loop here with branch, channel, slot
	 */
	क्रम (slot = 0; slot < max_csrows; slot++) अणु
		क्रम (channel = 0; channel < pvt->maxch; channel++) अणु

			mtr = determine_mtr(pvt, slot, channel);

			अगर (!MTR_DIMMS_PRESENT(mtr))
				जारी;

			dimm = edac_get_dimm(mci, channel / MAX_BRANCHES,
					     channel % MAX_BRANCHES, slot);

			csrow_megs = pvt->dimm_info[slot][channel].megabytes;
			dimm->grain = 8;

			/* Assume DDR2 क्रम now */
			dimm->mtype = MEM_FB_DDR2;

			/* ask what device type on this row */
			अगर (MTR_DRAM_WIDTH(mtr) == 8)
				dimm->dtype = DEV_X8;
			अन्यथा
				dimm->dtype = DEV_X4;

			dimm->edac_mode = EDAC_S8ECD8ED;
			dimm->nr_pages = csrow_megs << 8;
		पूर्ण

		empty = 0;
	पूर्ण

	वापस empty;
पूर्ण

/*
 *	i5000_enable_error_reporting
 *			Turn on the memory reporting features of the hardware
 */
अटल व्योम i5000_enable_error_reporting(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5000_pvt *pvt;
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
 * i5000_get_dimm_and_channel_counts(pdev, &nr_csrows, &num_channels)
 *
 *	ask the device how many channels are present and how many CSROWS
 *	 as well
 */
अटल व्योम i5000_get_dimm_and_channel_counts(काष्ठा pci_dev *pdev,
					पूर्णांक *num_dimms_per_channel,
					पूर्णांक *num_channels)
अणु
	u8 value;

	/* Need to retrieve just how many channels and dimms per channel are
	 * supported on this memory controller
	 */
	pci_पढ़ो_config_byte(pdev, MAXDIMMPERCH, &value);
	*num_dimms_per_channel = (पूर्णांक)value;

	pci_पढ़ो_config_byte(pdev, MAXCH, &value);
	*num_channels = (पूर्णांक)value;
पूर्ण

/*
 *	i5000_probe1	Probe क्रम ONE instance of device to see अगर it is
 *			present.
 *	वापस:
 *		0 क्रम FOUND a device
 *		< 0 क्रम error code
 */
अटल पूर्णांक i5000_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[3];
	काष्ठा i5000_pvt *pvt;
	पूर्णांक num_channels;
	पूर्णांक num_dimms_per_channel;

	edac_dbg(0, "MC: pdev bus %u dev=0x%x fn=0x%x\n",
		 pdev->bus->number,
		 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));

	/* We only are looking क्रम func 0 of the set */
	अगर (PCI_FUNC(pdev->devfn) != 0)
		वापस -ENODEV;

	/* Ask the devices क्रम the number of CSROWS and CHANNELS so
	 * that we can calculate the memory resources, etc
	 *
	 * The Chipset will report what it can handle which will be greater
	 * or equal to what the motherboard manufacturer will implement.
	 *
	 * As we करोn't have a motherboard identअगरication routine to determine
	 * actual number of slots/dimms per channel, we thus utilize the
	 * resource as specअगरied by the chipset. Thus, we might have
	 * have more DIMMs per channel than actually on the mobo, but this
	 * allows the driver to support up to the chipset max, without
	 * some fancy mobo determination.
	 */
	i5000_get_dimm_and_channel_counts(pdev, &num_dimms_per_channel,
					&num_channels);

	edac_dbg(0, "MC: Number of Branches=2 Channels= %d  DIMMS= %d\n",
		 num_channels, num_dimms_per_channel);

	/* allocate a new MC control काष्ठाure */

	layers[0].type = EDAC_MC_LAYER_BRANCH;
	layers[0].size = MAX_BRANCHES;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = num_channels / MAX_BRANCHES;
	layers[1].is_virt_csrow = false;
	layers[2].type = EDAC_MC_LAYER_SLOT;
	layers[2].size = num_dimms_per_channel;
	layers[2].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(0, "MC: mci = %p\n", mci);

	mci->pdev = &pdev->dev;	/* record ptr  to the generic device */

	pvt = mci->pvt_info;
	pvt->प्रणाली_address = pdev;	/* Record this device in our निजी */
	pvt->maxch = num_channels;
	pvt->maxdimmperch = num_dimms_per_channel;

	/* 'get' the pci devices we want to reserve क्रम our use */
	अगर (i5000_get_devices(mci, dev_idx))
		जाओ fail0;

	/* Time to get serious */
	i5000_get_mc_regs(mci);	/* retrieve the hardware रेजिस्टरs */

	mci->mc_idx = 0;
	mci->mtype_cap = MEM_FLAG_FB_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "i5000_edac.c";
	mci->ctl_name = i5000_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = शून्य;

	/* Set the function poपूर्णांकer to an actual operation function */
	mci->edac_check = i5000_check_error;

	/* initialize the MC control काष्ठाure 'csrows' table
	 * with the mapping and control inक्रमmation */
	अगर (i5000_init_csrows(mci)) अणु
		edac_dbg(0, "MC: Setting mci->edac_cap to EDAC_FLAG_NONE because i5000_init_csrows() returned nonzero value\n");
		mci->edac_cap = EDAC_FLAG_NONE;	/* no csrows found */
	पूर्ण अन्यथा अणु
		edac_dbg(1, "MC: Enable error reporting now\n");
		i5000_enable_error_reporting(mci);
	पूर्ण

	/* add this new MC control काष्ठाure to EDAC's list of MCs */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		/* FIXME: perhaps some code should go here that disables error
		 * reporting अगर we just enabled it
		 */
		जाओ fail1;
	पूर्ण

	i5000_clear_error(mci);

	/* allocating generic PCI control info */
	i5000_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!i5000_pci) अणु
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

	i5000_put_devices(mci);

fail0:
	edac_mc_मुक्त(mci);
	वापस -ENODEV;
पूर्ण

/*
 *	i5000_init_one	स्थिरructor क्रम one instance of device
 *
 * 	वापसs:
 *		negative on error
 *		count (>= 0)
 */
अटल पूर्णांक i5000_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc;

	edac_dbg(0, "MC:\n");

	/* wake up device */
	rc = pci_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* now probe and enable the device */
	वापस i5000_probe1(pdev, id->driver_data);
पूर्ण

/*
 *	i5000_हटाओ_one	deकाष्ठाor क्रम one instance of device
 *
 */
अटल व्योम i5000_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	अगर (i5000_pci)
		edac_pci_release_generic_ctl(i5000_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	/* retrieve references to resources, and मुक्त those resources */
	i5000_put_devices(mci);
	edac_mc_मुक्त(mci);
पूर्ण

/*
 *	pci_device_id	table क्रम which devices we are looking क्रम
 *
 *	The "E500P" device is the first device supported.
 */
अटल स्थिर काष्ठा pci_device_id i5000_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_I5000_DEV16),
	 .driver_data = I5000Pपूर्ण,

	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i5000_pci_tbl);

/*
 *	i5000_driver	pci_driver काष्ठाure क्रम this module
 *
 */
अटल काष्ठा pci_driver i5000_driver = अणु
	.name = KBUILD_BASENAME,
	.probe = i5000_init_one,
	.हटाओ = i5000_हटाओ_one,
	.id_table = i5000_pci_tbl,
पूर्ण;

/*
 *	i5000_init		Module entry function
 *			Try to initialize this module क्रम its devices
 */
अटल पूर्णांक __init i5000_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(2, "MC:\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&i5000_driver);

	वापस (pci_rc < 0) ? pci_rc : 0;
पूर्ण

/*
 *	i5000_निकास()	Module निकास function
 *			Unरेजिस्टर the driver
 */
अटल व्योम __निकास i5000_निकास(व्योम)
अणु
	edac_dbg(2, "MC:\n");
	pci_unरेजिस्टर_driver(&i5000_driver);
पूर्ण

module_init(i5000_init);
module_निकास(i5000_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR
    ("Linux Networx (http://lnxi.com) Doug Thompson <norsk5@xmission.com>");
MODULE_DESCRIPTION("MC Driver for Intel I5000 memory controllers - "
		I5000_REVISION);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
module_param(misc_messages, पूर्णांक, 0444);
MODULE_PARM_DESC(misc_messages, "Log miscellaneous non fatal messages");

