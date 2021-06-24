<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel 7300 class Memory Controllers kernel module (Clarksboro)
 *
 * Copyright (c) 2010 by:
 *	 Mauro Carvalho Chehab
 *
 * Red Hat Inc. https://www.redhat.com
 *
 * Intel 7300 Chipset Memory Controller Hub (MCH) - Datasheet
 *	http://www.पूर्णांकel.com/Assets/PDF/datasheet/318082.pdf
 *
 * TODO: The chipset allow checking क्रम PCI Express errors also. Currently,
 *	 the driver covers only memory error errors
 *
 * This driver uses "csrows" EDAC attribute to represent DIMM slot#
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
 * Alter this version क्रम the I7300 module when modअगरications are made
 */
#घोषणा I7300_REVISION    " Ver: 1.0.0"

#घोषणा EDAC_MOD_STR      "i7300_edac"

#घोषणा i7300_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "i7300", fmt, ##arg)

#घोषणा i7300_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "i7300", fmt, ##arg)

/***********************************************
 * i7300 Limit स्थिरants Structs and अटल vars
 ***********************************************/

/*
 * Memory topology is organized as:
 *	Branch 0 - 2 channels: channels 0 and 1 (FDB0 PCI dev 21.0)
 *	Branch 1 - 2 channels: channels 2 and 3 (FDB1 PCI dev 22.0)
 * Each channel can have to 8 DIMM sets (called as SLOTS)
 * Slots should generally be filled in pairs
 *	Except on Single Channel mode of operation
 *		just slot 0/channel0 filled on this mode
 *	On normal operation mode, the two channels on a branch should be
 *		filled together क्रम the same SLOT#
 * When in mirrored mode, Branch 1 replicate memory at Branch 0, so, the four
 *		channels on both branches should be filled
 */

/* Limits क्रम i7300 */
#घोषणा MAX_SLOTS		8
#घोषणा MAX_BRANCHES		2
#घोषणा MAX_CH_PER_BRANCH	2
#घोषणा MAX_CHANNELS		(MAX_CH_PER_BRANCH * MAX_BRANCHES)
#घोषणा MAX_MIR			3

#घोषणा to_channel(ch, branch)	((((branch)) << 1) | (ch))

#घोषणा to_csrow(slot, ch, branch)					\
		(to_channel(ch, branch) | ((slot) << 2))

/* Device name and रेजिस्टर DID (Device ID) */
काष्ठा i7300_dev_info अणु
	स्थिर अक्षर *ctl_name;	/* name क्रम this device */
	u16 fsb_mapping_errors;	/* DID क्रम the branchmap,control */
पूर्ण;

/* Table of devices attributes supported by this driver */
अटल स्थिर काष्ठा i7300_dev_info i7300_devs[] = अणु
	अणु
		.ctl_name = "I7300",
		.fsb_mapping_errors = PCI_DEVICE_ID_INTEL_I7300_MCH_ERR,
	पूर्ण,
पूर्ण;

काष्ठा i7300_dimm_info अणु
	पूर्णांक megabytes;		/* size, 0 means not present  */
पूर्ण;

/* driver निजी data काष्ठाure */
काष्ठा i7300_pvt अणु
	काष्ठा pci_dev *pci_dev_16_0_fsb_ctlr;		/* 16.0 */
	काष्ठा pci_dev *pci_dev_16_1_fsb_addr_map;	/* 16.1 */
	काष्ठा pci_dev *pci_dev_16_2_fsb_err_regs;	/* 16.2 */
	काष्ठा pci_dev *pci_dev_2x_0_fbd_branch[MAX_BRANCHES];	/* 21.0  and 22.0 */

	u16 tolm;				/* top of low memory */
	u64 ambase;				/* AMB BAR */

	u32 mc_settings;			/* Report several settings */
	u32 mc_settings_a;

	u16 mir[MAX_MIR];			/* Memory Interleave Reg*/

	u16 mtr[MAX_SLOTS][MAX_BRANCHES];	/* Memory Technlogy Reg */
	u16 ambpresent[MAX_CHANNELS];		/* AMB present regs */

	/* DIMM inक्रमmation matrix, allocating architecture maximums */
	काष्ठा i7300_dimm_info dimm_info[MAX_SLOTS][MAX_CHANNELS];

	/* Temporary buffer क्रम use when preparing error messages */
	अक्षर *पंचांगp_prt_buffer;
पूर्ण;

/* FIXME: Why करो we need to have this अटल? */
अटल काष्ठा edac_pci_ctl_info *i7300_pci;

/***************************************************
 * i7300 Register definitions क्रम memory क्रमागतeration
 ***************************************************/

/*
 * Device 16,
 * Function 0: System Address (not करोcumented)
 * Function 1: Memory Branch Map, Control, Errors Register
 */

	/* OFFSETS क्रम Function 0 */
#घोषणा AMBASE			0x48 /* AMB Mem Mapped Reg Region Base */
#घोषणा MAXCH			0x56 /* Max Channel Number */
#घोषणा MAXDIMMPERCH		0x57 /* Max DIMM PER Channel Number */

	/* OFFSETS क्रम Function 1 */
#घोषणा MC_SETTINGS		0x40
  #घोषणा IS_MIRRORED(mc)		((mc) & (1 << 16))
  #घोषणा IS_ECC_ENABLED(mc)		((mc) & (1 << 5))
  #घोषणा IS_RETRY_ENABLED(mc)		((mc) & (1 << 31))
  #घोषणा IS_SCRBALGO_ENHANCED(mc)	((mc) & (1 << 8))

#घोषणा MC_SETTINGS_A		0x58
  #घोषणा IS_SINGLE_MODE(mca)		((mca) & (1 << 14))

#घोषणा TOLM			0x6C

#घोषणा MIR0			0x80
#घोषणा MIR1			0x84
#घोषणा MIR2			0x88

/*
 * Note: Other Intel EDAC drivers use AMBPRESENT to identअगरy अगर the available
 * memory. From datasheet item 7.3.1 (FB-DIMM technology & organization), it
 * seems that we cannot use this inक्रमmation directly क्रम the same usage.
 * Each memory slot may have up to 2 AMB पूर्णांकerfaces, one क्रम income and another
 * क्रम outcome पूर्णांकerface to the next slot.
 * For now, the driver just stores the AMB present रेजिस्टरs, but rely only at
 * the MTR info to detect memory.
 * Datasheet is also not clear about how to map each AMBPRESENT रेजिस्टरs to
 * one of the 4 available channels.
 */
#घोषणा AMBPRESENT_0	0x64
#घोषणा AMBPRESENT_1	0x66

अटल स्थिर u16 mtr_regs[MAX_SLOTS] = अणु
	0x80, 0x84, 0x88, 0x8c,
	0x82, 0x86, 0x8a, 0x8e
पूर्ण;

/*
 * Defines to extract the vaious fields from the
 *	MTRx - Memory Technology Registers
 */
#घोषणा MTR_DIMMS_PRESENT(mtr)		((mtr) & (1 << 8))
#घोषणा MTR_DIMMS_ETHROTTLE(mtr)	((mtr) & (1 << 7))
#घोषणा MTR_DRAM_WIDTH(mtr)		(((mtr) & (1 << 6)) ? 8 : 4)
#घोषणा MTR_DRAM_BANKS(mtr)		(((mtr) & (1 << 5)) ? 8 : 4)
#घोषणा MTR_DIMM_RANKS(mtr)		(((mtr) & (1 << 4)) ? 1 : 0)
#घोषणा MTR_DIMM_ROWS(mtr)		(((mtr) >> 2) & 0x3)
#घोषणा MTR_DRAM_BANKS_ADDR_BITS	2
#घोषणा MTR_DIMM_ROWS_ADDR_BITS(mtr)	(MTR_DIMM_ROWS(mtr) + 13)
#घोषणा MTR_DIMM_COLS(mtr)		((mtr) & 0x3)
#घोषणा MTR_DIMM_COLS_ADDR_BITS(mtr)	(MTR_DIMM_COLS(mtr) + 10)

/************************************************
 * i7300 Register definitions क्रम error detection
 ************************************************/

/*
 * Device 16.1: FBD Error Registers
 */
#घोषणा FERR_FAT_FBD	0x98
अटल स्थिर अक्षर *ferr_fat_fbd_name[] = अणु
	[22] = "Non-Redundant Fast Reset Timeout",
	[2]  = ">Tmid Thermal event with intelligent throttling disabled",
	[1]  = "Memory or FBD configuration CRC read error",
	[0]  = "Memory Write error on non-redundant retry or "
	       "FBD configuration Write error on retry",
पूर्ण;
#घोषणा GET_FBD_FAT_IDX(fbderr)	(((fbderr) >> 28) & 3)
#घोषणा FERR_FAT_FBD_ERR_MASK ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 22))

#घोषणा FERR_NF_FBD	0xa0
अटल स्थिर अक्षर *ferr_nf_fbd_name[] = अणु
	[24] = "DIMM-Spare Copy Completed",
	[23] = "DIMM-Spare Copy Initiated",
	[22] = "Redundant Fast Reset Timeout",
	[21] = "Memory Write error on redundant retry",
	[18] = "SPD protocol Error",
	[17] = "FBD Northbound parity error on FBD Sync Status",
	[16] = "Correctable Patrol Data ECC",
	[15] = "Correctable Resilver- or Spare-Copy Data ECC",
	[14] = "Correctable Mirrored Demand Data ECC",
	[13] = "Correctable Non-Mirrored Demand Data ECC",
	[11] = "Memory or FBD configuration CRC read error",
	[10] = "FBD Configuration Write error on first attempt",
	[9]  = "Memory Write error on first attempt",
	[8]  = "Non-Aliased Uncorrectable Patrol Data ECC",
	[7]  = "Non-Aliased Uncorrectable Resilver- or Spare-Copy Data ECC",
	[6]  = "Non-Aliased Uncorrectable Mirrored Demand Data ECC",
	[5]  = "Non-Aliased Uncorrectable Non-Mirrored Demand Data ECC",
	[4]  = "Aliased Uncorrectable Patrol Data ECC",
	[3]  = "Aliased Uncorrectable Resilver- or Spare-Copy Data ECC",
	[2]  = "Aliased Uncorrectable Mirrored Demand Data ECC",
	[1]  = "Aliased Uncorrectable Non-Mirrored Demand Data ECC",
	[0]  = "Uncorrectable Data ECC on Replay",
पूर्ण;
#घोषणा GET_FBD_NF_IDX(fbderr)	(((fbderr) >> 28) & 3)
#घोषणा FERR_NF_FBD_ERR_MASK ((1 << 24) | (1 << 23) | (1 << 22) | (1 << 21) |\
			      (1 << 18) | (1 << 17) | (1 << 16) | (1 << 15) |\
			      (1 << 14) | (1 << 13) | (1 << 11) | (1 << 10) |\
			      (1 << 9)  | (1 << 8)  | (1 << 7)  | (1 << 6)  |\
			      (1 << 5)  | (1 << 4)  | (1 << 3)  | (1 << 2)  |\
			      (1 << 1)  | (1 << 0))

#घोषणा EMASK_FBD	0xa8
#घोषणा EMASK_FBD_ERR_MASK ((1 << 27) | (1 << 26) | (1 << 25) | (1 << 24) |\
			    (1 << 22) | (1 << 21) | (1 << 20) | (1 << 19) |\
			    (1 << 18) | (1 << 17) | (1 << 16) | (1 << 14) |\
			    (1 << 13) | (1 << 12) | (1 << 11) | (1 << 10) |\
			    (1 << 9)  | (1 << 8)  | (1 << 7)  | (1 << 6)  |\
			    (1 << 5)  | (1 << 4)  | (1 << 3)  | (1 << 2)  |\
			    (1 << 1)  | (1 << 0))

/*
 * Device 16.2: Global Error Registers
 */

#घोषणा FERR_GLOBAL_HI	0x48
अटल स्थिर अक्षर *ferr_global_hi_name[] = अणु
	[3] = "FSB 3 Fatal Error",
	[2] = "FSB 2 Fatal Error",
	[1] = "FSB 1 Fatal Error",
	[0] = "FSB 0 Fatal Error",
पूर्ण;
#घोषणा ferr_global_hi_is_fatal(त्रुटि_सं)	1

#घोषणा FERR_GLOBAL_LO	0x40
अटल स्थिर अक्षर *ferr_global_lo_name[] = अणु
	[31] = "Internal MCH Fatal Error",
	[30] = "Intel QuickData Technology Device Fatal Error",
	[29] = "FSB1 Fatal Error",
	[28] = "FSB0 Fatal Error",
	[27] = "FBD Channel 3 Fatal Error",
	[26] = "FBD Channel 2 Fatal Error",
	[25] = "FBD Channel 1 Fatal Error",
	[24] = "FBD Channel 0 Fatal Error",
	[23] = "PCI Express Device 7Fatal Error",
	[22] = "PCI Express Device 6 Fatal Error",
	[21] = "PCI Express Device 5 Fatal Error",
	[20] = "PCI Express Device 4 Fatal Error",
	[19] = "PCI Express Device 3 Fatal Error",
	[18] = "PCI Express Device 2 Fatal Error",
	[17] = "PCI Express Device 1 Fatal Error",
	[16] = "ESI Fatal Error",
	[15] = "Internal MCH Non-Fatal Error",
	[14] = "Intel QuickData Technology Device Non Fatal Error",
	[13] = "FSB1 Non-Fatal Error",
	[12] = "FSB 0 Non-Fatal Error",
	[11] = "FBD Channel 3 Non-Fatal Error",
	[10] = "FBD Channel 2 Non-Fatal Error",
	[9]  = "FBD Channel 1 Non-Fatal Error",
	[8]  = "FBD Channel 0 Non-Fatal Error",
	[7]  = "PCI Express Device 7 Non-Fatal Error",
	[6]  = "PCI Express Device 6 Non-Fatal Error",
	[5]  = "PCI Express Device 5 Non-Fatal Error",
	[4]  = "PCI Express Device 4 Non-Fatal Error",
	[3]  = "PCI Express Device 3 Non-Fatal Error",
	[2]  = "PCI Express Device 2 Non-Fatal Error",
	[1]  = "PCI Express Device 1 Non-Fatal Error",
	[0]  = "ESI Non-Fatal Error",
पूर्ण;
#घोषणा ferr_global_lo_is_fatal(त्रुटि_सं)	((त्रुटि_सं < 16) ? 0 : 1)

#घोषणा NRECMEMA	0xbe
  #घोषणा NRECMEMA_BANK(v)	(((v) >> 12) & 7)
  #घोषणा NRECMEMA_RANK(v)	(((v) >> 8) & 15)

#घोषणा NRECMEMB	0xc0
  #घोषणा NRECMEMB_IS_WR(v)	((v) & (1 << 31))
  #घोषणा NRECMEMB_CAS(v)	(((v) >> 16) & 0x1fff)
  #घोषणा NRECMEMB_RAS(v)	((v) & 0xffff)

#घोषणा REDMEMA		0xdc

#घोषणा REDMEMB		0x7c

#घोषणा RECMEMA		0xe0
  #घोषणा RECMEMA_BANK(v)	(((v) >> 12) & 7)
  #घोषणा RECMEMA_RANK(v)	(((v) >> 8) & 15)

#घोषणा RECMEMB		0xe4
  #घोषणा RECMEMB_IS_WR(v)	((v) & (1 << 31))
  #घोषणा RECMEMB_CAS(v)	(((v) >> 16) & 0x1fff)
  #घोषणा RECMEMB_RAS(v)	((v) & 0xffff)

/********************************************
 * i7300 Functions related to error detection
 ********************************************/

/**
 * get_err_from_table() - Gets the error message from a table
 * @table:	table name (array of अक्षर *)
 * @size:	number of elements at the table
 * @pos:	position of the element to be वापसed
 *
 * This is a small routine that माला_लो the pos-th element of a table. If the
 * element करोesn't exist (or it is empty), it वापसs "reserved".
 * Instead of calling it directly, the better is to call via the macro
 * GET_ERR_FROM_TABLE(), that स्वतःmatically checks the table size via
 * ARRAY_SIZE() macro
 */
अटल स्थिर अक्षर *get_err_from_table(स्थिर अक्षर *table[], पूर्णांक size, पूर्णांक pos)
अणु
	अगर (unlikely(pos >= size))
		वापस "Reserved";

	अगर (unlikely(!table[pos]))
		वापस "Reserved";

	वापस table[pos];
पूर्ण

#घोषणा GET_ERR_FROM_TABLE(table, pos)				\
	get_err_from_table(table, ARRAY_SIZE(table), pos)

/**
 * i7300_process_error_global() - Retrieve the hardware error inक्रमmation from
 *				  the hardware global error रेजिस्टरs and
 *				  sends it to dmesg
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 */
अटल व्योम i7300_process_error_global(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt;
	u32 errnum, error_reg;
	अचिन्हित दीर्घ errors;
	स्थिर अक्षर *specअगरic;
	bool is_fatal;

	pvt = mci->pvt_info;

	/* पढ़ो in the 1st FATAL error रेजिस्टर */
	pci_पढ़ो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_HI, &error_reg);
	अगर (unlikely(error_reg)) अणु
		errors = error_reg;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_global_hi_name));
		specअगरic = GET_ERR_FROM_TABLE(ferr_global_hi_name, errnum);
		is_fatal = ferr_global_hi_is_fatal(errnum);

		/* Clear the error bit */
		pci_ग_लिखो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
				       FERR_GLOBAL_HI, error_reg);

		जाओ error_global;
	पूर्ण

	pci_पढ़ो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_LO, &error_reg);
	अगर (unlikely(error_reg)) अणु
		errors = error_reg;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_global_lo_name));
		specअगरic = GET_ERR_FROM_TABLE(ferr_global_lo_name, errnum);
		is_fatal = ferr_global_lo_is_fatal(errnum);

		/* Clear the error bit */
		pci_ग_लिखो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
				       FERR_GLOBAL_LO, error_reg);

		जाओ error_global;
	पूर्ण
	वापस;

error_global:
	i7300_mc_prपूर्णांकk(mci, KERN_EMERG, "%s misc error: %s\n",
			is_fatal ? "Fatal" : "NOT fatal", specअगरic);
पूर्ण

/**
 * i7300_process_fbd_error() - Retrieve the hardware error inक्रमmation from
 *			       the FBD error रेजिस्टरs and sends it via
 *			       EDAC error API calls
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 */
अटल व्योम i7300_process_fbd_error(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt;
	u32 errnum, value, error_reg;
	u16 val16;
	अचिन्हित branch, channel, bank, rank, cas, ras;
	u32 syndrome;

	अचिन्हित दीर्घ errors;
	स्थिर अक्षर *specअगरic;
	bool is_wr;

	pvt = mci->pvt_info;

	/* पढ़ो in the 1st FATAL error रेजिस्टर */
	pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_FAT_FBD, &error_reg);
	अगर (unlikely(error_reg & FERR_FAT_FBD_ERR_MASK)) अणु
		errors = error_reg & FERR_FAT_FBD_ERR_MASK ;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_fat_fbd_name));
		specअगरic = GET_ERR_FROM_TABLE(ferr_fat_fbd_name, errnum);
		branch = (GET_FBD_FAT_IDX(error_reg) == 2) ? 1 : 0;

		pci_पढ़ो_config_word(pvt->pci_dev_16_1_fsb_addr_map,
				     NRECMEMA, &val16);
		bank = NRECMEMA_BANK(val16);
		rank = NRECMEMA_RANK(val16);

		pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				NRECMEMB, &value);
		is_wr = NRECMEMB_IS_WR(value);
		cas = NRECMEMB_CAS(value);
		ras = NRECMEMB_RAS(value);

		/* Clean the error रेजिस्टर */
		pci_ग_लिखो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				FERR_FAT_FBD, error_reg);

		snम_लिखो(pvt->पंचांगp_prt_buffer, PAGE_SIZE,
			 "Bank=%d RAS=%d CAS=%d Err=0x%lx (%s))",
			 bank, ras, cas, errors, specअगरic);

		edac_mc_handle_error(HW_EVENT_ERR_FATAL, mci, 1, 0, 0, 0,
				     branch, -1, rank,
				     is_wr ? "Write error" : "Read error",
				     pvt->पंचांगp_prt_buffer);

	पूर्ण

	/* पढ़ो in the 1st NON-FATAL error रेजिस्टर */
	pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_NF_FBD, &error_reg);
	अगर (unlikely(error_reg & FERR_NF_FBD_ERR_MASK)) अणु
		errors = error_reg & FERR_NF_FBD_ERR_MASK;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_nf_fbd_name));
		specअगरic = GET_ERR_FROM_TABLE(ferr_nf_fbd_name, errnum);
		branch = (GET_FBD_NF_IDX(error_reg) == 2) ? 1 : 0;

		pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			REDMEMA, &syndrome);

		pci_पढ़ो_config_word(pvt->pci_dev_16_1_fsb_addr_map,
				     RECMEMA, &val16);
		bank = RECMEMA_BANK(val16);
		rank = RECMEMA_RANK(val16);

		pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				RECMEMB, &value);
		is_wr = RECMEMB_IS_WR(value);
		cas = RECMEMB_CAS(value);
		ras = RECMEMB_RAS(value);

		pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				     REDMEMB, &value);
		channel = (branch << 1);

		/* Second channel ? */
		channel += !!(value & BIT(17));

		/* Clear the error bit */
		pci_ग_लिखो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				FERR_NF_FBD, error_reg);

		/* Form out message */
		snम_लिखो(pvt->पंचांगp_prt_buffer, PAGE_SIZE,
			 "DRAM-Bank=%d RAS=%d CAS=%d, Err=0x%lx (%s))",
			 bank, ras, cas, errors, specअगरic);

		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0,
				     syndrome,
				     branch >> 1, channel % 2, rank,
				     is_wr ? "Write error" : "Read error",
				     pvt->पंचांगp_prt_buffer);
	पूर्ण
	वापस;
पूर्ण

/**
 * i7300_check_error() - Calls the error checking subroutines
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 */
अटल व्योम i7300_check_error(काष्ठा mem_ctl_info *mci)
अणु
	i7300_process_error_global(mci);
	i7300_process_fbd_error(mci);
पूर्ण;

/**
 * i7300_clear_error() - Clears the error रेजिस्टरs
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 */
अटल व्योम i7300_clear_error(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt = mci->pvt_info;
	u32 value;
	/*
	 * All error values are RWC - we need to पढ़ो and ग_लिखो 1 to the
	 * bit that we want to cleanup
	 */

	/* Clear global error रेजिस्टरs */
	pci_पढ़ो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_HI, &value);
	pci_ग_लिखो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_HI, value);

	pci_पढ़ो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_LO, &value);
	pci_ग_लिखो_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_LO, value);

	/* Clear FBD error रेजिस्टरs */
	pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_FAT_FBD, &value);
	pci_ग_लिखो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_FAT_FBD, value);

	pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_NF_FBD, &value);
	pci_ग_लिखो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_NF_FBD, value);
पूर्ण

/**
 * i7300_enable_error_reporting() - Enable the memory reporting logic at the
 *				    hardware
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 */
अटल व्योम i7300_enable_error_reporting(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt = mci->pvt_info;
	u32 fbd_error_mask;

	/* Read the FBD Error Mask Register */
	pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      EMASK_FBD, &fbd_error_mask);

	/* Enable with a '0' */
	fbd_error_mask &= ~(EMASK_FBD_ERR_MASK);

	pci_ग_लिखो_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			       EMASK_FBD, fbd_error_mask);
पूर्ण

/************************************************
 * i7300 Functions related to memory क्रमागतberation
 ************************************************/

/**
 * decode_mtr() - Decodes the MTR descriptor, filling the edac काष्ठाs
 * @pvt: poपूर्णांकer to the निजी data काष्ठा used by i7300 driver
 * @slot: DIMM slot (0 to 7)
 * @ch: Channel number within the branch (0 or 1)
 * @branch: Branch number (0 or 1)
 * @dinfo: Poपूर्णांकer to DIMM info where dimm size is stored
 * @dimm: Poपूर्णांकer to the काष्ठा dimm_info that corresponds to that element
 */
अटल पूर्णांक decode_mtr(काष्ठा i7300_pvt *pvt,
		      पूर्णांक slot, पूर्णांक ch, पूर्णांक branch,
		      काष्ठा i7300_dimm_info *dinfo,
		      काष्ठा dimm_info *dimm)
अणु
	पूर्णांक mtr, ans, addrBits, channel;

	channel = to_channel(ch, branch);

	mtr = pvt->mtr[slot][branch];
	ans = MTR_DIMMS_PRESENT(mtr) ? 1 : 0;

	edac_dbg(2, "\tMTR%d CH%d: DIMMs are %sPresent (mtr)\n",
		 slot, channel, ans ? "" : "NOT ");

	/* Determine अगर there is a DIMM present in this DIMM slot */
	अगर (!ans)
		वापस 0;

	/* Start with the number of bits क्रम a Bank
	* on the DRAM */
	addrBits = MTR_DRAM_BANKS_ADDR_BITS;
	/* Add thक्रमागतber of ROW bits */
	addrBits += MTR_DIMM_ROWS_ADDR_BITS(mtr);
	/* add the number of COLUMN bits */
	addrBits += MTR_DIMM_COLS_ADDR_BITS(mtr);
	/* add the number of RANK bits */
	addrBits += MTR_DIMM_RANKS(mtr);

	addrBits += 6;	/* add 64 bits per DIMM */
	addrBits -= 20;	/* भागide by 2^^20 */
	addrBits -= 3;	/* 8 bits per bytes */

	dinfo->megabytes = 1 << addrBits;

	edac_dbg(2, "\t\tWIDTH: x%d\n", MTR_DRAM_WIDTH(mtr));

	edac_dbg(2, "\t\tELECTRICAL THROTTLING is %s\n",
		 MTR_DIMMS_ETHROTTLE(mtr) ? "enabled" : "disabled");

	edac_dbg(2, "\t\tNUMBANK: %d bank(s)\n", MTR_DRAM_BANKS(mtr));
	edac_dbg(2, "\t\tNUMRANK: %s\n",
		 MTR_DIMM_RANKS(mtr) ? "double" : "single");
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
	edac_dbg(2, "\t\tSIZE: %d MB\n", dinfo->megabytes);

	/*
	 * The type of error detection actually depends of the
	 * mode of operation. When it is just one single memory chip, at
	 * socket 0, channel 0, it uses 8-byte-over-32-byte SECDED+ code.
	 * In normal or mirrored mode, it uses Lockstep mode,
	 * with the possibility of using an extended algorithm क्रम x8 memories
	 * See datasheet Sections 7.3.6 to 7.3.8
	 */

	dimm->nr_pages = MiB_TO_PAGES(dinfo->megabytes);
	dimm->grain = 8;
	dimm->mtype = MEM_FB_DDR2;
	अगर (IS_SINGLE_MODE(pvt->mc_settings_a)) अणु
		dimm->edac_mode = EDAC_SECDED;
		edac_dbg(2, "\t\tECC code is 8-byte-over-32-byte SECDED+ code\n");
	पूर्ण अन्यथा अणु
		edac_dbg(2, "\t\tECC code is on Lockstep mode\n");
		अगर (MTR_DRAM_WIDTH(mtr) == 8)
			dimm->edac_mode = EDAC_S8ECD8ED;
		अन्यथा
			dimm->edac_mode = EDAC_S4ECD4ED;
	पूर्ण

	/* ask what device type on this row */
	अगर (MTR_DRAM_WIDTH(mtr) == 8) अणु
		edac_dbg(2, "\t\tScrub algorithm for x8 is on %s mode\n",
			 IS_SCRBALGO_ENHANCED(pvt->mc_settings) ?
			 "enhanced" : "normal");

		dimm->dtype = DEV_X8;
	पूर्ण अन्यथा
		dimm->dtype = DEV_X4;

	वापस mtr;
पूर्ण

/**
 * prपूर्णांक_dimm_size() - Prपूर्णांकs dump of the memory organization
 * @pvt: poपूर्णांकer to the निजी data काष्ठा used by i7300 driver
 *
 * Useful क्रम debug. If debug is disabled, this routine करो nothing
 */
अटल व्योम prपूर्णांक_dimm_size(काष्ठा i7300_pvt *pvt)
अणु
#अगर_घोषित CONFIG_EDAC_DEBUG
	काष्ठा i7300_dimm_info *dinfo;
	अक्षर *p;
	पूर्णांक space, n;
	पूर्णांक channel, slot;

	space = PAGE_SIZE;
	p = pvt->पंचांगp_prt_buffer;

	n = snम_लिखो(p, space, "              ");
	p += n;
	space -= n;
	क्रम (channel = 0; channel < MAX_CHANNELS; channel++) अणु
		n = snम_लिखो(p, space, "channel %d | ", channel);
		p += n;
		space -= n;
	पूर्ण
	edac_dbg(2, "%s\n", pvt->पंचांगp_prt_buffer);
	p = pvt->पंचांगp_prt_buffer;
	space = PAGE_SIZE;
	n = snम_लिखो(p, space, "-------------------------------"
			       "------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", pvt->पंचांगp_prt_buffer);
	p = pvt->पंचांगp_prt_buffer;
	space = PAGE_SIZE;

	क्रम (slot = 0; slot < MAX_SLOTS; slot++) अणु
		n = snम_लिखो(p, space, "csrow/SLOT %d  ", slot);
		p += n;
		space -= n;

		क्रम (channel = 0; channel < MAX_CHANNELS; channel++) अणु
			dinfo = &pvt->dimm_info[slot][channel];
			n = snम_लिखो(p, space, "%4d MB   | ", dinfo->megabytes);
			p += n;
			space -= n;
		पूर्ण

		edac_dbg(2, "%s\n", pvt->पंचांगp_prt_buffer);
		p = pvt->पंचांगp_prt_buffer;
		space = PAGE_SIZE;
	पूर्ण

	n = snम_लिखो(p, space, "-------------------------------"
			       "------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", pvt->पंचांगp_prt_buffer);
	p = pvt->पंचांगp_prt_buffer;
	space = PAGE_SIZE;
#पूर्ण_अगर
पूर्ण

/**
 * i7300_init_csrows() - Initialize the 'csrows' table within
 *			 the mci control काष्ठाure with the
 *			 addressing of memory.
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 */
अटल पूर्णांक i7300_init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt;
	काष्ठा i7300_dimm_info *dinfo;
	पूर्णांक rc = -ENODEV;
	पूर्णांक mtr;
	पूर्णांक ch, branch, slot, channel, max_channel, max_branch;
	काष्ठा dimm_info *dimm;

	pvt = mci->pvt_info;

	edac_dbg(2, "Memory Technology Registers:\n");

	अगर (IS_SINGLE_MODE(pvt->mc_settings_a)) अणु
		max_branch = 1;
		max_channel = 1;
	पूर्ण अन्यथा अणु
		max_branch = MAX_BRANCHES;
		max_channel = MAX_CH_PER_BRANCH;
	पूर्ण

	/* Get the AMB present रेजिस्टरs क्रम the four channels */
	क्रम (branch = 0; branch < max_branch; branch++) अणु
		/* Read and dump branch 0's MTRs */
		channel = to_channel(0, branch);
		pci_पढ़ो_config_word(pvt->pci_dev_2x_0_fbd_branch[branch],
				     AMBPRESENT_0,
				&pvt->ambpresent[channel]);
		edac_dbg(2, "\t\tAMB-present CH%d = 0x%x:\n",
			 channel, pvt->ambpresent[channel]);

		अगर (max_channel == 1)
			जारी;

		channel = to_channel(1, branch);
		pci_पढ़ो_config_word(pvt->pci_dev_2x_0_fbd_branch[branch],
				     AMBPRESENT_1,
				&pvt->ambpresent[channel]);
		edac_dbg(2, "\t\tAMB-present CH%d = 0x%x:\n",
			 channel, pvt->ambpresent[channel]);
	पूर्ण

	/* Get the set of MTR[0-7] regs by each branch */
	क्रम (slot = 0; slot < MAX_SLOTS; slot++) अणु
		पूर्णांक where = mtr_regs[slot];
		क्रम (branch = 0; branch < max_branch; branch++) अणु
			pci_पढ़ो_config_word(pvt->pci_dev_2x_0_fbd_branch[branch],
					where,
					&pvt->mtr[slot][branch]);
			क्रम (ch = 0; ch < max_channel; ch++) अणु
				पूर्णांक channel = to_channel(ch, branch);

				dimm = edac_get_dimm(mci, branch, ch, slot);

				dinfo = &pvt->dimm_info[slot][channel];

				mtr = decode_mtr(pvt, slot, ch, branch,
						 dinfo, dimm);

				/* अगर no DIMMS on this row, जारी */
				अगर (!MTR_DIMMS_PRESENT(mtr))
					जारी;

				rc = 0;

			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/**
 * decode_mir() - Decodes Memory Interleave Register (MIR) info
 * @mir_no: number of the MIR रेजिस्टर to decode
 * @mir: array with the MIR data cached on the driver
 */
अटल व्योम decode_mir(पूर्णांक mir_no, u16 mir[MAX_MIR])
अणु
	अगर (mir[mir_no] & 3)
		edac_dbg(2, "MIR%d: limit= 0x%x Branch(es) that participate: %s %s\n",
			 mir_no,
			 (mir[mir_no] >> 4) & 0xfff,
			 (mir[mir_no] & 1) ? "B0" : "",
			 (mir[mir_no] & 2) ? "B1" : "");
पूर्ण

/**
 * i7300_get_mc_regs() - Get the contents of the MC क्रमागतeration रेजिस्टरs
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 *
 * Data पढ़ो is cached पूर्णांकernally क्रम its usage when needed
 */
अटल पूर्णांक i7300_get_mc_regs(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt;
	u32 actual_tolm;
	पूर्णांक i, rc;

	pvt = mci->pvt_info;

	pci_पढ़ो_config_dword(pvt->pci_dev_16_0_fsb_ctlr, AMBASE,
			(u32 *) &pvt->ambase);

	edac_dbg(2, "AMBASE= 0x%lx\n", (दीर्घ अचिन्हित पूर्णांक)pvt->ambase);

	/* Get the Branch Map regs */
	pci_पढ़ो_config_word(pvt->pci_dev_16_1_fsb_addr_map, TOLM, &pvt->tolm);
	pvt->tolm >>= 12;
	edac_dbg(2, "TOLM (number of 256M regions) =%u (0x%x)\n",
		 pvt->tolm, pvt->tolm);

	actual_tolm = (u32) ((1000l * pvt->tolm) >> (30 - 28));
	edac_dbg(2, "Actual TOLM byte addr=%u.%03u GB (0x%x)\n",
		 actual_tolm/1000, actual_tolm % 1000, pvt->tolm << 28);

	/* Get memory controller settings */
	pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map, MC_SETTINGS,
			     &pvt->mc_settings);
	pci_पढ़ो_config_dword(pvt->pci_dev_16_1_fsb_addr_map, MC_SETTINGS_A,
			     &pvt->mc_settings_a);

	अगर (IS_SINGLE_MODE(pvt->mc_settings_a))
		edac_dbg(0, "Memory controller operating on single mode\n");
	अन्यथा
		edac_dbg(0, "Memory controller operating on %smirrored mode\n",
			 IS_MIRRORED(pvt->mc_settings) ? "" : "non-");

	edac_dbg(0, "Error detection is %s\n",
		 IS_ECC_ENABLED(pvt->mc_settings) ? "enabled" : "disabled");
	edac_dbg(0, "Retry is %s\n",
		 IS_RETRY_ENABLED(pvt->mc_settings) ? "enabled" : "disabled");

	/* Get Memory Interleave Range रेजिस्टरs */
	pci_पढ़ो_config_word(pvt->pci_dev_16_1_fsb_addr_map, MIR0,
			     &pvt->mir[0]);
	pci_पढ़ो_config_word(pvt->pci_dev_16_1_fsb_addr_map, MIR1,
			     &pvt->mir[1]);
	pci_पढ़ो_config_word(pvt->pci_dev_16_1_fsb_addr_map, MIR2,
			     &pvt->mir[2]);

	/* Decode the MIR regs */
	क्रम (i = 0; i < MAX_MIR; i++)
		decode_mir(i, pvt->mir);

	rc = i7300_init_csrows(mci);
	अगर (rc < 0)
		वापस rc;

	/* Go and determine the size of each DIMM and place in an
	 * orderly matrix */
	prपूर्णांक_dimm_size(pvt);

	वापस 0;
पूर्ण

/*************************************************
 * i7300 Functions related to device probe/release
 *************************************************/

/**
 * i7300_put_devices() - Release the PCI devices
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 */
अटल व्योम i7300_put_devices(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt;
	पूर्णांक branch;

	pvt = mci->pvt_info;

	/* Decrement usage count क्रम devices */
	क्रम (branch = 0; branch < MAX_CH_PER_BRANCH; branch++)
		pci_dev_put(pvt->pci_dev_2x_0_fbd_branch[branch]);
	pci_dev_put(pvt->pci_dev_16_2_fsb_err_regs);
	pci_dev_put(pvt->pci_dev_16_1_fsb_addr_map);
पूर्ण

/**
 * i7300_get_devices() - Find and perक्रमm 'get' operation on the MCH's
 *			 device/functions we want to reference क्रम this driver
 * @mci: काष्ठा mem_ctl_info poपूर्णांकer
 *
 * Access and prepare the several devices क्रम usage:
 * I7300 devices used by this driver:
 *    Device 16, functions 0,1 and 2:	PCI_DEVICE_ID_INTEL_I7300_MCH_ERR
 *    Device 21 function 0:		PCI_DEVICE_ID_INTEL_I7300_MCH_FB0
 *    Device 22 function 0:		PCI_DEVICE_ID_INTEL_I7300_MCH_FB1
 */
अटल पूर्णांक i7300_get_devices(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i7300_pvt *pvt;
	काष्ठा pci_dev *pdev;

	pvt = mci->pvt_info;

	/* Attempt to 'get' the MCH रेजिस्टर we want */
	pdev = शून्य;
	जबतक ((pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				      PCI_DEVICE_ID_INTEL_I7300_MCH_ERR,
				      pdev))) अणु
		/* Store device 16 funcs 1 and 2 */
		चयन (PCI_FUNC(pdev->devfn)) अणु
		हाल 1:
			अगर (!pvt->pci_dev_16_1_fsb_addr_map)
				pvt->pci_dev_16_1_fsb_addr_map =
							pci_dev_get(pdev);
			अवरोध;
		हाल 2:
			अगर (!pvt->pci_dev_16_2_fsb_err_regs)
				pvt->pci_dev_16_2_fsb_err_regs =
							pci_dev_get(pdev);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pvt->pci_dev_16_1_fsb_addr_map ||
	    !pvt->pci_dev_16_2_fsb_err_regs) अणु
		/* At least one device was not found */
		i7300_prपूर्णांकk(KERN_ERR,
			"'system address,Process Bus' device not found:"
			"vendor 0x%x device 0x%x ERR funcs (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_I7300_MCH_ERR);
		जाओ error;
	पूर्ण

	edac_dbg(1, "System Address, processor bus- PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->pci_dev_16_0_fsb_ctlr),
		 pvt->pci_dev_16_0_fsb_ctlr->venकरोr,
		 pvt->pci_dev_16_0_fsb_ctlr->device);
	edac_dbg(1, "Branchmap, control and errors - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->pci_dev_16_1_fsb_addr_map),
		 pvt->pci_dev_16_1_fsb_addr_map->venकरोr,
		 pvt->pci_dev_16_1_fsb_addr_map->device);
	edac_dbg(1, "FSB Error Regs - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->pci_dev_16_2_fsb_err_regs),
		 pvt->pci_dev_16_2_fsb_err_regs->venकरोr,
		 pvt->pci_dev_16_2_fsb_err_regs->device);

	pvt->pci_dev_2x_0_fbd_branch[0] = pci_get_device(PCI_VENDOR_ID_INTEL,
					    PCI_DEVICE_ID_INTEL_I7300_MCH_FB0,
					    शून्य);
	अगर (!pvt->pci_dev_2x_0_fbd_branch[0]) अणु
		i7300_prपूर्णांकk(KERN_ERR,
			"MC: 'BRANCH 0' device not found:"
			"vendor 0x%x device 0x%x Func 0 (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_I7300_MCH_FB0);
		जाओ error;
	पूर्ण

	pvt->pci_dev_2x_0_fbd_branch[1] = pci_get_device(PCI_VENDOR_ID_INTEL,
					    PCI_DEVICE_ID_INTEL_I7300_MCH_FB1,
					    शून्य);
	अगर (!pvt->pci_dev_2x_0_fbd_branch[1]) अणु
		i7300_prपूर्णांकk(KERN_ERR,
			"MC: 'BRANCH 1' device not found:"
			"vendor 0x%x device 0x%x Func 0 "
			"(broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_I7300_MCH_FB1);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	i7300_put_devices(mci);
	वापस -ENODEV;
पूर्ण

/**
 * i7300_init_one() - Probe क्रम one instance of the device
 * @pdev: काष्ठा pci_dev poपूर्णांकer
 * @id: काष्ठा pci_device_id poपूर्णांकer - currently unused
 */
अटल पूर्णांक i7300_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[3];
	काष्ठा i7300_pvt *pvt;
	पूर्णांक rc;

	/* wake up device */
	rc = pci_enable_device(pdev);
	अगर (rc == -EIO)
		वापस rc;

	edac_dbg(0, "MC: pdev bus %u dev=0x%x fn=0x%x\n",
		 pdev->bus->number,
		 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));

	/* We only are looking क्रम func 0 of the set */
	अगर (PCI_FUNC(pdev->devfn) != 0)
		वापस -ENODEV;

	/* allocate a new MC control काष्ठाure */
	layers[0].type = EDAC_MC_LAYER_BRANCH;
	layers[0].size = MAX_BRANCHES;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = MAX_CH_PER_BRANCH;
	layers[1].is_virt_csrow = true;
	layers[2].type = EDAC_MC_LAYER_SLOT;
	layers[2].size = MAX_SLOTS;
	layers[2].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(0, "MC: mci = %p\n", mci);

	mci->pdev = &pdev->dev;	/* record ptr  to the generic device */

	pvt = mci->pvt_info;
	pvt->pci_dev_16_0_fsb_ctlr = pdev;	/* Record this device in our निजी */

	pvt->पंचांगp_prt_buffer = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!pvt->पंचांगp_prt_buffer) अणु
		edac_mc_मुक्त(mci);
		वापस -ENOMEM;
	पूर्ण

	/* 'get' the pci devices we want to reserve क्रम our use */
	अगर (i7300_get_devices(mci))
		जाओ fail0;

	mci->mc_idx = 0;
	mci->mtype_cap = MEM_FLAG_FB_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "i7300_edac.c";
	mci->ctl_name = i7300_devs[0].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = शून्य;

	/* Set the function poपूर्णांकer to an actual operation function */
	mci->edac_check = i7300_check_error;

	/* initialize the MC control काष्ठाure 'csrows' table
	 * with the mapping and control inक्रमmation */
	अगर (i7300_get_mc_regs(mci)) अणु
		edac_dbg(0, "MC: Setting mci->edac_cap to EDAC_FLAG_NONE because i7300_init_csrows() returned nonzero value\n");
		mci->edac_cap = EDAC_FLAG_NONE;	/* no csrows found */
	पूर्ण अन्यथा अणु
		edac_dbg(1, "MC: Enable error reporting now\n");
		i7300_enable_error_reporting(mci);
	पूर्ण

	/* add this new MC control काष्ठाure to EDAC's list of MCs */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		/* FIXME: perhaps some code should go here that disables error
		 * reporting अगर we just enabled it
		 */
		जाओ fail1;
	पूर्ण

	i7300_clear_error(mci);

	/* allocating generic PCI control info */
	i7300_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!i7300_pci) अणु
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

	i7300_put_devices(mci);

fail0:
	kमुक्त(pvt->पंचांगp_prt_buffer);
	edac_mc_मुक्त(mci);
	वापस -ENODEV;
पूर्ण

/**
 * i7300_हटाओ_one() - Remove the driver
 * @pdev: काष्ठा pci_dev poपूर्णांकer
 */
अटल व्योम i7300_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	अक्षर *पंचांगp;

	edac_dbg(0, "\n");

	अगर (i7300_pci)
		edac_pci_release_generic_ctl(i7300_pci);

	mci = edac_mc_del_mc(&pdev->dev);
	अगर (!mci)
		वापस;

	पंचांगp = ((काष्ठा i7300_pvt *)mci->pvt_info)->पंचांगp_prt_buffer;

	/* retrieve references to resources, and मुक्त those resources */
	i7300_put_devices(mci);

	kमुक्त(पंचांगp);
	edac_mc_मुक्त(mci);
पूर्ण

/*
 * pci_device_id: table क्रम which devices we are looking क्रम
 *
 * Has only 8086:360c PCI ID
 */
अटल स्थिर काष्ठा pci_device_id i7300_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_I7300_MCH_ERR)पूर्ण,
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i7300_pci_tbl);

/*
 * i7300_driver: pci_driver काष्ठाure क्रम this module
 */
अटल काष्ठा pci_driver i7300_driver = अणु
	.name = "i7300_edac",
	.probe = i7300_init_one,
	.हटाओ = i7300_हटाओ_one,
	.id_table = i7300_pci_tbl,
पूर्ण;

/**
 * i7300_init() - Registers the driver
 */
अटल पूर्णांक __init i7300_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(2, "\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&i7300_driver);

	वापस (pci_rc < 0) ? pci_rc : 0;
पूर्ण

/**
 * i7300_init() - Unरेजिस्टरs the driver
 */
अटल व्योम __निकास i7300_निकास(व्योम)
अणु
	edac_dbg(2, "\n");
	pci_unरेजिस्टर_driver(&i7300_driver);
पूर्ण

module_init(i7300_init);
module_निकास(i7300_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_AUTHOR("Red Hat Inc. (https://www.redhat.com)");
MODULE_DESCRIPTION("MC Driver for Intel I7300 memory controllers - "
		   I7300_REVISION);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
