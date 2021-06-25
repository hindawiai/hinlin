<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम DDR memories based on JEDEC specs
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Aneesh V <aneesh@ti.com>
 */
#अगर_अघोषित __JEDEC_DDR_H
#घोषणा __JEDEC_DDR_H

#समावेश <linux/types.h>

/* DDR Densities */
#घोषणा DDR_DENSITY_64Mb	1
#घोषणा DDR_DENSITY_128Mb	2
#घोषणा DDR_DENSITY_256Mb	3
#घोषणा DDR_DENSITY_512Mb	4
#घोषणा DDR_DENSITY_1Gb		5
#घोषणा DDR_DENSITY_2Gb		6
#घोषणा DDR_DENSITY_4Gb		7
#घोषणा DDR_DENSITY_8Gb		8
#घोषणा DDR_DENSITY_16Gb	9
#घोषणा DDR_DENSITY_32Gb	10

/* DDR type */
#घोषणा DDR_TYPE_DDR2		1
#घोषणा DDR_TYPE_DDR3		2
#घोषणा DDR_TYPE_LPDDR2_S4	3
#घोषणा DDR_TYPE_LPDDR2_S2	4
#घोषणा DDR_TYPE_LPDDR2_NVM	5
#घोषणा DDR_TYPE_LPDDR3		6

/* DDR IO width */
#घोषणा DDR_IO_WIDTH_4		1
#घोषणा DDR_IO_WIDTH_8		2
#घोषणा DDR_IO_WIDTH_16		3
#घोषणा DDR_IO_WIDTH_32		4

/* Number of Row bits */
#घोषणा R9			9
#घोषणा R10			10
#घोषणा R11			11
#घोषणा R12			12
#घोषणा R13			13
#घोषणा R14			14
#घोषणा R15			15
#घोषणा R16			16

/* Number of Column bits */
#घोषणा C7			7
#घोषणा C8			8
#घोषणा C9			9
#घोषणा C10			10
#घोषणा C11			11
#घोषणा C12			12

/* Number of Banks */
#घोषणा B1			0
#घोषणा B2			1
#घोषणा B4			2
#घोषणा B8			3

/* Refresh rate in nano-seconds */
#घोषणा T_REFI_15_6		15600
#घोषणा T_REFI_7_8		7800
#घोषणा T_REFI_3_9		3900

/* tRFC values */
#घोषणा T_RFC_90		90000
#घोषणा T_RFC_110		110000
#घोषणा T_RFC_130		130000
#घोषणा T_RFC_160		160000
#घोषणा T_RFC_210		210000
#घोषणा T_RFC_300		300000
#घोषणा T_RFC_350		350000

/* Mode रेजिस्टर numbers */
#घोषणा DDR_MR0			0
#घोषणा DDR_MR1			1
#घोषणा DDR_MR2			2
#घोषणा DDR_MR3			3
#घोषणा DDR_MR4			4
#घोषणा DDR_MR5			5
#घोषणा DDR_MR6			6
#घोषणा DDR_MR7			7
#घोषणा DDR_MR8			8
#घोषणा DDR_MR9			9
#घोषणा DDR_MR10		10
#घोषणा DDR_MR11		11
#घोषणा DDR_MR16		16
#घोषणा DDR_MR17		17
#घोषणा DDR_MR18		18

/*
 * LPDDR2 related defines
 */

/* MR4 रेजिस्टर fields */
#घोषणा MR4_SDRAM_REF_RATE_SHIFT			0
#घोषणा MR4_SDRAM_REF_RATE_MASK				7
#घोषणा MR4_TUF_SHIFT					7
#घोषणा MR4_TUF_MASK					(1 << 7)

/* MR4 SDRAM Refresh Rate field values */
#घोषणा SDRAM_TEMP_NOMINAL				0x3
#घोषणा SDRAM_TEMP_RESERVED_4				0x4
#घोषणा SDRAM_TEMP_HIGH_DERATE_REFRESH			0x5
#घोषणा SDRAM_TEMP_HIGH_DERATE_REFRESH_AND_TIMINGS	0x6
#घोषणा SDRAM_TEMP_VERY_HIGH_SHUTDOWN			0x7

#घोषणा NUM_DDR_ADDR_TABLE_ENTRIES			11
#घोषणा NUM_DDR_TIMING_TABLE_ENTRIES			4

/* Structure क्रम DDR addressing info from the JEDEC spec */
काष्ठा lpddr2_addressing अणु
	u32 num_banks;
	u32 tREFI_ns;
	u32 tRFCab_ps;
पूर्ण;

/*
 * Structure क्रम timings from the LPDDR2 datasheet
 * All parameters are in pico seconds(ps) unless explicitly indicated
 * with a suffix like tRAS_max_ns below
 */
काष्ठा lpddr2_timings अणु
	u32 max_freq;
	u32 min_freq;
	u32 tRPab;
	u32 tRCD;
	u32 tWR;
	u32 tRAS_min;
	u32 tRRD;
	u32 tWTR;
	u32 tXP;
	u32 tRTP;
	u32 tCKESR;
	u32 tDQSCK_max;
	u32 tDQSCK_max_derated;
	u32 tFAW;
	u32 tZQCS;
	u32 tZQCL;
	u32 tZQinit;
	u32 tRAS_max_ns;
पूर्ण;

/*
 * Min value क्रम some parameters in terms of number of tCK cycles(nCK)
 * Please set to zero parameters that are not valid क्रम a given memory
 * type
 */
काष्ठा lpddr2_min_tck अणु
	u32 tRPab;
	u32 tRCD;
	u32 tWR;
	u32 tRASmin;
	u32 tRRD;
	u32 tWTR;
	u32 tXP;
	u32 tRTP;
	u32 tCKE;
	u32 tCKESR;
	u32 tFAW;
पूर्ण;

बाह्य स्थिर काष्ठा lpddr2_addressing
	lpddr2_jedec_addressing_table[NUM_DDR_ADDR_TABLE_ENTRIES];
बाह्य स्थिर काष्ठा lpddr2_timings
	lpddr2_jedec_timings[NUM_DDR_TIMING_TABLE_ENTRIES];
बाह्य स्थिर काष्ठा lpddr2_min_tck lpddr2_jedec_min_tck;

/*
 * Structure क्रम timings क्रम LPDDR3 based on LPDDR2 plus additional fields.
 * All parameters are in pico seconds(ps) excluding max_freq, min_freq which
 * are in Hz.
 */
काष्ठा lpddr3_timings अणु
	u32 max_freq;
	u32 min_freq;
	u32 tRFC;
	u32 tRRD;
	u32 tRPab;
	u32 tRPpb;
	u32 tRCD;
	u32 tRC;
	u32 tRAS;
	u32 tWTR;
	u32 tWR;
	u32 tRTP;
	u32 tW2W_C2C;
	u32 tR2R_C2C;
	u32 tWL;
	u32 tDQSCK;
	u32 tRL;
	u32 tFAW;
	u32 tXSR;
	u32 tXP;
	u32 tCKE;
	u32 tCKESR;
	u32 tMRD;
पूर्ण;

/*
 * Min value क्रम some parameters in terms of number of tCK cycles(nCK)
 * Please set to zero parameters that are not valid क्रम a given memory
 * type
 */
काष्ठा lpddr3_min_tck अणु
	u32 tRFC;
	u32 tRRD;
	u32 tRPab;
	u32 tRPpb;
	u32 tRCD;
	u32 tRC;
	u32 tRAS;
	u32 tWTR;
	u32 tWR;
	u32 tRTP;
	u32 tW2W_C2C;
	u32 tR2R_C2C;
	u32 tWL;
	u32 tDQSCK;
	u32 tRL;
	u32 tFAW;
	u32 tXSR;
	u32 tXP;
	u32 tCKE;
	u32 tCKESR;
	u32 tMRD;
पूर्ण;

#पूर्ण_अगर /* __JEDEC_DDR_H */
