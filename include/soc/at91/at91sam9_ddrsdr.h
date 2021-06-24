<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Header file क्रम the Aपंचांगel DDR/SDR SDRAM Controller
 *
 * Copyright (C) 2010 Aपंचांगel Corporation
 *	Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 */
#अगर_अघोषित AT91SAM9_DDRSDR_H
#घोषणा AT91SAM9_DDRSDR_H

#घोषणा AT91_DDRSDRC_MR		0x00	/* Mode Register */
#घोषणा		AT91_DDRSDRC_MODE	(0x7 << 0)		/* Command Mode */
#घोषणा			AT91_DDRSDRC_MODE_NORMAL	0
#घोषणा			AT91_DDRSDRC_MODE_NOP		1
#घोषणा			AT91_DDRSDRC_MODE_PRECHARGE	2
#घोषणा			AT91_DDRSDRC_MODE_LMR		3
#घोषणा			AT91_DDRSDRC_MODE_REFRESH	4
#घोषणा			AT91_DDRSDRC_MODE_EXT_LMR	5
#घोषणा			AT91_DDRSDRC_MODE_DEEP		6

#घोषणा AT91_DDRSDRC_RTR	0x04	/* Refresh Timer Register */
#घोषणा		AT91_DDRSDRC_COUNT	(0xfff << 0)		/* Refresh Timer Counter */

#घोषणा AT91_DDRSDRC_CR		0x08	/* Configuration Register */
#घोषणा		AT91_DDRSDRC_NC		(3 << 0)		/* Number of Column Bits */
#घोषणा			AT91_DDRSDRC_NC_SDR8	(0 << 0)
#घोषणा			AT91_DDRSDRC_NC_SDR9	(1 << 0)
#घोषणा			AT91_DDRSDRC_NC_SDR10	(2 << 0)
#घोषणा			AT91_DDRSDRC_NC_SDR11	(3 << 0)
#घोषणा			AT91_DDRSDRC_NC_DDR9	(0 << 0)
#घोषणा			AT91_DDRSDRC_NC_DDR10	(1 << 0)
#घोषणा			AT91_DDRSDRC_NC_DDR11	(2 << 0)
#घोषणा			AT91_DDRSDRC_NC_DDR12	(3 << 0)
#घोषणा		AT91_DDRSDRC_NR		(3 << 2)		/* Number of Row Bits */
#घोषणा			AT91_DDRSDRC_NR_11	(0 << 2)
#घोषणा			AT91_DDRSDRC_NR_12	(1 << 2)
#घोषणा			AT91_DDRSDRC_NR_13	(2 << 2)
#घोषणा			AT91_DDRSDRC_NR_14	(3 << 2)
#घोषणा		AT91_DDRSDRC_CAS	(7 << 4)		/* CAS Latency */
#घोषणा			AT91_DDRSDRC_CAS_2	(2 << 4)
#घोषणा			AT91_DDRSDRC_CAS_3	(3 << 4)
#घोषणा			AT91_DDRSDRC_CAS_25	(6 << 4)
#घोषणा		AT91_DDRSDRC_RST_DLL	(1 << 7)		/* Reset DLL */
#घोषणा		AT91_DDRSDRC_DICDS	(1 << 8)		/* Output impedance control */
#घोषणा		AT91_DDRSDRC_DIS_DLL	(1 << 9)		/* Disable DLL [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_OCD	(1 << 12)		/* Off-Chip Driver [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_DQMS	(1 << 16)		/* Mask Data is Shared [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_ACTBST	(1 << 18)		/* Active Bank X to Burst Stop Read Access Bank Y [SAM9 Only] */

#घोषणा AT91_DDRSDRC_T0PR	0x0C	/* Timing 0 Register */
#घोषणा		AT91_DDRSDRC_TRAS	(0xf <<  0)		/* Active to Preअक्षरge delay */
#घोषणा		AT91_DDRSDRC_TRCD	(0xf <<  4)		/* Row to Column delay */
#घोषणा		AT91_DDRSDRC_TWR	(0xf <<  8)		/* Write recovery delay */
#घोषणा		AT91_DDRSDRC_TRC	(0xf << 12)		/* Row cycle delay */
#घोषणा		AT91_DDRSDRC_TRP	(0xf << 16)		/* Row preअक्षरge delay */
#घोषणा		AT91_DDRSDRC_TRRD	(0xf << 20)		/* Active BankA to BankB */
#घोषणा		AT91_DDRSDRC_TWTR	(0x7 << 24)		/* Internal Write to Read delay */
#घोषणा		AT91_DDRSDRC_RED_WRRD	(0x1 << 27)		/* Reduce Write to Read Delay [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_TMRD	(0xf << 28)		/* Load mode to active/refresh delay */

#घोषणा AT91_DDRSDRC_T1PR	0x10	/* Timing 1 Register */
#घोषणा		AT91_DDRSDRC_TRFC	(0x1f << 0)		/* Row Cycle Delay */
#घोषणा		AT91_DDRSDRC_TXSNR	(0xff << 8)		/* Exit self-refresh to non-पढ़ो */
#घोषणा		AT91_DDRSDRC_TXSRD	(0xff << 16)		/* Exit self-refresh to पढ़ो */
#घोषणा		AT91_DDRSDRC_TXP	(0xf  << 24)		/* Exit घातer-करोwn delay */

#घोषणा AT91_DDRSDRC_T2PR	0x14	/* Timing 2 Register [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_TXARD	(0xf  << 0)		/* Exit active घातer करोwn delay to पढ़ो command in mode "Fast Exit" */
#घोषणा		AT91_DDRSDRC_TXARDS	(0xf  << 4)		/* Exit active घातer करोwn delay to पढ़ो command in mode "Slow Exit" */
#घोषणा		AT91_DDRSDRC_TRPA	(0xf  << 8)		/* Row Preअक्षरge All delay */
#घोषणा		AT91_DDRSDRC_TRTP	(0x7  << 12)		/* Read to Preअक्षरge delay */

#घोषणा AT91_DDRSDRC_LPR	0x1C	/* Low Power Register */
#घोषणा		AT91_DDRSDRC_LPCB	(3 << 0)		/* Low-घातer Configurations */
#घोषणा			AT91_DDRSDRC_LPCB_DISABLE		0
#घोषणा			AT91_DDRSDRC_LPCB_SELF_REFRESH		1
#घोषणा			AT91_DDRSDRC_LPCB_POWER_DOWN		2
#घोषणा			AT91_DDRSDRC_LPCB_DEEP_POWER_DOWN	3
#घोषणा		AT91_DDRSDRC_CLKFR	(1 << 2)	/* Clock Frozen */
#घोषणा		AT91_DDRSDRC_LPDDR2_PWOFF	(1 << 3)	/* LPDDR Power Off */
#घोषणा		AT91_DDRSDRC_PASR	(7 << 4)	/* Partial Array Self Refresh */
#घोषणा		AT91_DDRSDRC_TCSR	(3 << 8)	/* Temperature Compensated Self Refresh */
#घोषणा		AT91_DDRSDRC_DS		(3 << 10)	/* Drive Strength */
#घोषणा		AT91_DDRSDRC_TIMEOUT	(3 << 12)	/* Time to define when Low Power Mode is enabled */
#घोषणा			AT91_DDRSDRC_TIMEOUT_0_CLK_CYCLES	(0 << 12)
#घोषणा			AT91_DDRSDRC_TIMEOUT_64_CLK_CYCLES	(1 << 12)
#घोषणा			AT91_DDRSDRC_TIMEOUT_128_CLK_CYCLES	(2 << 12)
#घोषणा		AT91_DDRSDRC_APDE	(1 << 16)	 /* Active घातer करोwn निकास समय */
#घोषणा		AT91_DDRSDRC_UPD_MR	(3 << 20)	 /* Update load mode रेजिस्टर and extended mode रेजिस्टर */

#घोषणा AT91_DDRSDRC_MDR	0x20	/* Memory Device Register */
#घोषणा		AT91_DDRSDRC_MD		(7 << 0)	/* Memory Device Type */
#घोषणा			AT91_DDRSDRC_MD_SDR		0
#घोषणा			AT91_DDRSDRC_MD_LOW_POWER_SDR	1
#घोषणा			AT91_DDRSDRC_MD_LOW_POWER_DDR	3
#घोषणा			AT91_DDRSDRC_MD_LPDDR3		5
#घोषणा			AT91_DDRSDRC_MD_DDR2		6	/* [SAM9 Only] */
#घोषणा			AT91_DDRSDRC_MD_LPDDR2		7
#घोषणा		AT91_DDRSDRC_DBW	(1 << 4)		/* Data Bus Width */
#घोषणा			AT91_DDRSDRC_DBW_32BITS		(0 <<  4)
#घोषणा			AT91_DDRSDRC_DBW_16BITS		(1 <<  4)

#घोषणा AT91_DDRSDRC_DLL	0x24	/* DLL Inक्रमmation Register */
#घोषणा		AT91_DDRSDRC_MDINC	(1 << 0)		/* Master Delay increment */
#घोषणा		AT91_DDRSDRC_MDDEC	(1 << 1)		/* Master Delay decrement */
#घोषणा		AT91_DDRSDRC_MDOVF	(1 << 2)		/* Master Delay Overflow */
#घोषणा		AT91_DDRSDRC_MDVAL	(0xff <<  8)		/* Master Delay value */

#घोषणा AT91_DDRSDRC_HS		0x2C	/* High Speed Register [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_DIS_ATCP_RD	(1 << 2)	/* Anticip पढ़ो access is disabled */

#घोषणा AT91_DDRSDRC_DELAY(n)	(0x30 + (0x4 * (n)))	/* Delay I/O Register n */

#घोषणा AT91_DDRSDRC_WPMR	0xE4	/* Write Protect Mode Register [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_WP		(1 << 0)		/* Write protect enable */
#घोषणा		AT91_DDRSDRC_WPKEY	(0xffffff << 8)		/* Write protect key */
#घोषणा		AT91_DDRSDRC_KEY	(0x444452 << 8)		/* Write protect key = "DDR" */

#घोषणा AT91_DDRSDRC_WPSR	0xE8	/* Write Protect Status Register [SAM9 Only] */
#घोषणा		AT91_DDRSDRC_WPVS	(1 << 0)		/* Write protect violation status */
#घोषणा		AT91_DDRSDRC_WPVSRC	(0xffff << 8)		/* Write protect violation source */

#पूर्ण_अगर
