<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DDR addressing details and AC timing parameters from JEDEC specs
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Aneesh V <aneesh@ti.com>
 */

#समावेश <linux/export.h>

#समावेश "jedec_ddr.h"

/* LPDDR2 addressing details from JESD209-2 section 2.4 */
स्थिर काष्ठा lpddr2_addressing
	lpddr2_jedec_addressing_table[NUM_DDR_ADDR_TABLE_ENTRIES] = अणु
	अणुB4, T_REFI_15_6, T_RFC_90पूर्ण, /* 64M */
	अणुB4, T_REFI_15_6, T_RFC_90पूर्ण, /* 128M */
	अणुB4, T_REFI_7_8,  T_RFC_90पूर्ण, /* 256M */
	अणुB4, T_REFI_7_8,  T_RFC_90पूर्ण, /* 512M */
	अणुB8, T_REFI_7_8, T_RFC_130पूर्ण, /* 1GS4 */
	अणुB8, T_REFI_3_9, T_RFC_130पूर्ण, /* 2GS4 */
	अणुB8, T_REFI_3_9, T_RFC_130पूर्ण, /* 4G */
	अणुB8, T_REFI_3_9, T_RFC_210पूर्ण, /* 8G */
	अणुB4, T_REFI_7_8, T_RFC_130पूर्ण, /* 1GS2 */
	अणुB4, T_REFI_3_9, T_RFC_130पूर्ण, /* 2GS2 */
पूर्ण;
EXPORT_SYMBOL_GPL(lpddr2_jedec_addressing_table);

/* LPDDR2 AC timing parameters from JESD209-2 section 12 */
स्थिर काष्ठा lpddr2_timings
	lpddr2_jedec_timings[NUM_DDR_TIMING_TABLE_ENTRIES] = अणु
	/* Speed bin 400(200 MHz) */
	[0] = अणु
		.max_freq	= 200000000,
		.min_freq	= 10000000,
		.tRPab		= 21000,
		.tRCD		= 18000,
		.tWR		= 15000,
		.tRAS_min	= 42000,
		.tRRD		= 10000,
		.tWTR		= 10000,
		.tXP		= 7500,
		.tRTP		= 7500,
		.tCKESR		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCL		= 360000,
		.tZQinit	= 1000000,
		.tRAS_max_ns	= 70000,
		.tDQSCK_max_derated = 6000,
	पूर्ण,
	/* Speed bin 533(266 MHz) */
	[1] = अणु
		.max_freq	= 266666666,
		.min_freq	= 10000000,
		.tRPab		= 21000,
		.tRCD		= 18000,
		.tWR		= 15000,
		.tRAS_min	= 42000,
		.tRRD		= 10000,
		.tWTR		= 7500,
		.tXP		= 7500,
		.tRTP		= 7500,
		.tCKESR		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCL		= 360000,
		.tZQinit	= 1000000,
		.tRAS_max_ns	= 70000,
		.tDQSCK_max_derated = 6000,
	पूर्ण,
	/* Speed bin 800(400 MHz) */
	[2] = अणु
		.max_freq	= 400000000,
		.min_freq	= 10000000,
		.tRPab		= 21000,
		.tRCD		= 18000,
		.tWR		= 15000,
		.tRAS_min	= 42000,
		.tRRD		= 10000,
		.tWTR		= 7500,
		.tXP		= 7500,
		.tRTP		= 7500,
		.tCKESR		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCL		= 360000,
		.tZQinit	= 1000000,
		.tRAS_max_ns	= 70000,
		.tDQSCK_max_derated = 6000,
	पूर्ण,
	/* Speed bin 1066(533 MHz) */
	[3] = अणु
		.max_freq	= 533333333,
		.min_freq	= 10000000,
		.tRPab		= 21000,
		.tRCD		= 18000,
		.tWR		= 15000,
		.tRAS_min	= 42000,
		.tRRD		= 10000,
		.tWTR		= 7500,
		.tXP		= 7500,
		.tRTP		= 7500,
		.tCKESR		= 15000,
		.tDQSCK_max	= 5500,
		.tFAW		= 50000,
		.tZQCS		= 90000,
		.tZQCL		= 360000,
		.tZQinit	= 1000000,
		.tRAS_max_ns	= 70000,
		.tDQSCK_max_derated = 5620,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(lpddr2_jedec_timings);

स्थिर काष्ठा lpddr2_min_tck lpddr2_jedec_min_tck = अणु
	.tRPab		= 3,
	.tRCD		= 3,
	.tWR		= 3,
	.tRASmin	= 3,
	.tRRD		= 2,
	.tWTR		= 2,
	.tXP		= 2,
	.tRTP		= 2,
	.tCKE		= 3,
	.tCKESR		= 3,
	.tFAW		= 8
पूर्ण;
EXPORT_SYMBOL_GPL(lpddr2_jedec_min_tck);
