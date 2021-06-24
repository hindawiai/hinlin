<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2008 Nuovation System Designs, LLC
 *   Grant Erickson <gerickson@nuovations.com>
 *
 * This file defines processor mnemonics क्रम accessing and managing
 * the IBM DDR1/DDR2 ECC controller found in the 405EX[r], 440SP,
 * 440SPe, 460EX, 460GT and 460SX.
 */

#अगर_अघोषित __PPC4XX_EDAC_H
#घोषणा __PPC4XX_EDAC_H

#समावेश <linux/types.h>

/*
 * Macro क्रम generating रेजिस्टर field mnemonics
 */
#घोषणा PPC_REG_BITS			32
#घोषणा PPC_REG_VAL(bit, val)		((val) << ((PPC_REG_BITS - 1) - (bit)))
#घोषणा PPC_REG_DECODE(bit, val)	((val) >> ((PPC_REG_BITS - 1) - (bit)))

/*
 * IBM 4xx DDR1/DDR2 SDRAM memory controller रेजिस्टरs (at least those
 * relevant to ECC)
 */
#घोषणा SDRAM_BESR			0x00	/* Error status (पढ़ो/clear) */
#घोषणा SDRAM_BESRT			0x01	/* Error statuss (test/set)  */
#घोषणा SDRAM_BEARL			0x02	/* Error address low	     */
#घोषणा SDRAM_BEARH			0x03	/* Error address high	     */
#घोषणा SDRAM_WMIRQ			0x06	/* Write master (पढ़ो/clear) */
#घोषणा SDRAM_WMIRQT			0x07	/* Write master (test/set)   */
#घोषणा SDRAM_MCOPT1			0x20	/* Controller options 1	     */
#घोषणा SDRAM_MBXCF_BASE		0x40	/* Bank n configuration base */
#घोषणा	SDRAM_MBXCF(n)			(SDRAM_MBXCF_BASE + (4 * (n)))
#घोषणा SDRAM_MB0CF			SDRAM_MBXCF(0)
#घोषणा SDRAM_MB1CF			SDRAM_MBXCF(1)
#घोषणा SDRAM_MB2CF			SDRAM_MBXCF(2)
#घोषणा SDRAM_MB3CF			SDRAM_MBXCF(3)
#घोषणा SDRAM_ECCCR			0x98	/* ECC error status	     */
#घोषणा SDRAM_ECCES			SDRAM_ECCCR

/*
 * PLB Master IDs
 */
#घोषणा	SDRAM_PLB_M0ID_FIRST		0
#घोषणा	SDRAM_PLB_M0ID_ICU		SDRAM_PLB_M0ID_FIRST
#घोषणा	SDRAM_PLB_M0ID_PCIE0		1
#घोषणा	SDRAM_PLB_M0ID_PCIE1		2
#घोषणा	SDRAM_PLB_M0ID_DMA		3
#घोषणा	SDRAM_PLB_M0ID_DCU		4
#घोषणा	SDRAM_PLB_M0ID_OPB		5
#घोषणा	SDRAM_PLB_M0ID_MAL		6
#घोषणा	SDRAM_PLB_M0ID_SEC		7
#घोषणा	SDRAM_PLB_M0ID_AHB		8
#घोषणा SDRAM_PLB_M0ID_LAST		SDRAM_PLB_M0ID_AHB
#घोषणा SDRAM_PLB_M0ID_COUNT		(SDRAM_PLB_M0ID_LAST - \
					 SDRAM_PLB_M0ID_FIRST + 1)

/*
 * Memory Controller Bus Error Status Register
 */
#घोषणा SDRAM_BESR_MASK			PPC_REG_VAL(7, 0xFF)
#घोषणा SDRAM_BESR_M0ID_MASK		PPC_REG_VAL(3, 0xF)
#घोषणा	SDRAM_BESR_M0ID_DECODE(n)	PPC_REG_DECODE(3, n)
#घोषणा SDRAM_BESR_M0ID_ICU		PPC_REG_VAL(3, SDRAM_PLB_M0ID_ICU)
#घोषणा SDRAM_BESR_M0ID_PCIE0		PPC_REG_VAL(3, SDRAM_PLB_M0ID_PCIE0)
#घोषणा SDRAM_BESR_M0ID_PCIE1		PPC_REG_VAL(3, SDRAM_PLB_M0ID_PCIE1)
#घोषणा SDRAM_BESR_M0ID_DMA		PPC_REG_VAL(3, SDRAM_PLB_M0ID_DMA)
#घोषणा SDRAM_BESR_M0ID_DCU		PPC_REG_VAL(3, SDRAM_PLB_M0ID_DCU)
#घोषणा SDRAM_BESR_M0ID_OPB		PPC_REG_VAL(3, SDRAM_PLB_M0ID_OPB)
#घोषणा SDRAM_BESR_M0ID_MAL		PPC_REG_VAL(3, SDRAM_PLB_M0ID_MAL)
#घोषणा SDRAM_BESR_M0ID_SEC		PPC_REG_VAL(3, SDRAM_PLB_M0ID_SEC)
#घोषणा SDRAM_BESR_M0ID_AHB		PPC_REG_VAL(3, SDRAM_PLB_M0ID_AHB)
#घोषणा SDRAM_BESR_M0ET_MASK		PPC_REG_VAL(6, 0x7)
#घोषणा SDRAM_BESR_M0ET_NONE		PPC_REG_VAL(6, 0)
#घोषणा SDRAM_BESR_M0ET_ECC		PPC_REG_VAL(6, 1)
#घोषणा SDRAM_BESR_M0RW_MASK		PPC_REG_VAL(7, 1)
#घोषणा SDRAM_BESR_M0RW_WRITE		PPC_REG_VAL(7, 0)
#घोषणा SDRAM_BESR_M0RW_READ		PPC_REG_VAL(7, 1)

/*
 * Memory Controller PLB Write Master Interrupt Register
 */
#घोषणा SDRAM_WMIRQ_MASK		PPC_REG_VAL(8, 0x1FF)
#घोषणा	SDRAM_WMIRQ_ENCODE(id)		PPC_REG_VAL((id % \
						     SDRAM_PLB_M0ID_COUNT), 1)
#घोषणा SDRAM_WMIRQ_ICU			PPC_REG_VAL(SDRAM_PLB_M0ID_ICU, 1)
#घोषणा SDRAM_WMIRQ_PCIE0		PPC_REG_VAL(SDRAM_PLB_M0ID_PCIE0, 1)
#घोषणा SDRAM_WMIRQ_PCIE1		PPC_REG_VAL(SDRAM_PLB_M0ID_PCIE1, 1)
#घोषणा SDRAM_WMIRQ_DMA			PPC_REG_VAL(SDRAM_PLB_M0ID_DMA, 1)
#घोषणा SDRAM_WMIRQ_DCU			PPC_REG_VAL(SDRAM_PLB_M0ID_DCU, 1)
#घोषणा SDRAM_WMIRQ_OPB			PPC_REG_VAL(SDRAM_PLB_M0ID_OPB, 1)
#घोषणा SDRAM_WMIRQ_MAL			PPC_REG_VAL(SDRAM_PLB_M0ID_MAL, 1)
#घोषणा SDRAM_WMIRQ_SEC			PPC_REG_VAL(SDRAM_PLB_M0ID_SEC, 1)
#घोषणा SDRAM_WMIRQ_AHB			PPC_REG_VAL(SDRAM_PLB_M0ID_AHB, 1)

/*
 * Memory Controller Options 1 Register
 */
#घोषणा SDRAM_MCOPT1_MCHK_MASK	    PPC_REG_VAL(3, 0x3)	 /* ECC mask	     */
#घोषणा SDRAM_MCOPT1_MCHK_NON	    PPC_REG_VAL(3, 0x0)	 /* No ECC gen	     */
#घोषणा SDRAM_MCOPT1_MCHK_GEN	    PPC_REG_VAL(3, 0x2)	 /* ECC gen	     */
#घोषणा SDRAM_MCOPT1_MCHK_CHK	    PPC_REG_VAL(3, 0x1)	 /* ECC gen and chk  */
#घोषणा SDRAM_MCOPT1_MCHK_CHK_REP   PPC_REG_VAL(3, 0x3)	 /* ECC gen/chk/rpt  */
#घोषणा SDRAM_MCOPT1_MCHK_DECODE(n) ((((u32)(n)) >> 28) & 0x3)
#घोषणा SDRAM_MCOPT1_RDEN_MASK	    PPC_REG_VAL(4, 0x1)	 /* Rgstrd DIMM mask */
#घोषणा SDRAM_MCOPT1_RDEN	    PPC_REG_VAL(4, 0x1)	 /* Rgstrd DIMM enbl */
#घोषणा SDRAM_MCOPT1_WDTH_MASK	    PPC_REG_VAL(7, 0x1)	 /* Width mask	     */
#घोषणा SDRAM_MCOPT1_WDTH_32	    PPC_REG_VAL(7, 0x0)	 /* 32 bits	     */
#घोषणा SDRAM_MCOPT1_WDTH_16	    PPC_REG_VAL(7, 0x1)	 /* 16 bits	     */
#घोषणा SDRAM_MCOPT1_DDR_TYPE_MASK  PPC_REG_VAL(11, 0x1) /* DDR type mask    */
#घोषणा SDRAM_MCOPT1_DDR1_TYPE	    PPC_REG_VAL(11, 0x0) /* DDR1 type	     */
#घोषणा SDRAM_MCOPT1_DDR2_TYPE	    PPC_REG_VAL(11, 0x1) /* DDR2 type	     */

/*
 * Memory Bank 0 - n Configuration Register
 */
#घोषणा SDRAM_MBCF_BA_MASK		PPC_REG_VAL(12, 0x1FFF)
#घोषणा SDRAM_MBCF_SZ_MASK		PPC_REG_VAL(19, 0xF)
#घोषणा SDRAM_MBCF_SZ_DECODE(mbxcf)	PPC_REG_DECODE(19, mbxcf)
#घोषणा SDRAM_MBCF_SZ_4MB		PPC_REG_VAL(19, 0x0)
#घोषणा SDRAM_MBCF_SZ_8MB		PPC_REG_VAL(19, 0x1)
#घोषणा SDRAM_MBCF_SZ_16MB		PPC_REG_VAL(19, 0x2)
#घोषणा SDRAM_MBCF_SZ_32MB		PPC_REG_VAL(19, 0x3)
#घोषणा SDRAM_MBCF_SZ_64MB		PPC_REG_VAL(19, 0x4)
#घोषणा SDRAM_MBCF_SZ_128MB		PPC_REG_VAL(19, 0x5)
#घोषणा SDRAM_MBCF_SZ_256MB		PPC_REG_VAL(19, 0x6)
#घोषणा SDRAM_MBCF_SZ_512MB		PPC_REG_VAL(19, 0x7)
#घोषणा SDRAM_MBCF_SZ_1GB		PPC_REG_VAL(19, 0x8)
#घोषणा SDRAM_MBCF_SZ_2GB		PPC_REG_VAL(19, 0x9)
#घोषणा SDRAM_MBCF_SZ_4GB		PPC_REG_VAL(19, 0xA)
#घोषणा SDRAM_MBCF_SZ_8GB		PPC_REG_VAL(19, 0xB)
#घोषणा SDRAM_MBCF_AM_MASK		PPC_REG_VAL(23, 0xF)
#घोषणा SDRAM_MBCF_AM_MODE0		PPC_REG_VAL(23, 0x0)
#घोषणा SDRAM_MBCF_AM_MODE1		PPC_REG_VAL(23, 0x1)
#घोषणा SDRAM_MBCF_AM_MODE2		PPC_REG_VAL(23, 0x2)
#घोषणा SDRAM_MBCF_AM_MODE3		PPC_REG_VAL(23, 0x3)
#घोषणा SDRAM_MBCF_AM_MODE4		PPC_REG_VAL(23, 0x4)
#घोषणा SDRAM_MBCF_AM_MODE5		PPC_REG_VAL(23, 0x5)
#घोषणा SDRAM_MBCF_AM_MODE6		PPC_REG_VAL(23, 0x6)
#घोषणा SDRAM_MBCF_AM_MODE7		PPC_REG_VAL(23, 0x7)
#घोषणा SDRAM_MBCF_AM_MODE8		PPC_REG_VAL(23, 0x8)
#घोषणा SDRAM_MBCF_AM_MODE9		PPC_REG_VAL(23, 0x9)
#घोषणा SDRAM_MBCF_BE_MASK		PPC_REG_VAL(31, 0x1)
#घोषणा SDRAM_MBCF_BE_DISABLE		PPC_REG_VAL(31, 0x0)
#घोषणा SDRAM_MBCF_BE_ENABLE		PPC_REG_VAL(31, 0x1)

/*
 * ECC Error Status
 */
#घोषणा SDRAM_ECCES_MASK		PPC_REG_VAL(21, 0x3FFFFF)
#घोषणा SDRAM_ECCES_BNCE_MASK		PPC_REG_VAL(15, 0xFFFF)
#घोषणा SDRAM_ECCES_BNCE_ENCODE(lane)	PPC_REG_VAL(((lane) & 0xF), 1)
#घोषणा SDRAM_ECCES_CKBER_MASK		PPC_REG_VAL(17, 0x3)
#घोषणा SDRAM_ECCES_CKBER_NONE		PPC_REG_VAL(17, 0)
#घोषणा SDRAM_ECCES_CKBER_16_ECC_0_3	PPC_REG_VAL(17, 2)
#घोषणा SDRAM_ECCES_CKBER_32_ECC_0_3	PPC_REG_VAL(17, 1)
#घोषणा SDRAM_ECCES_CKBER_32_ECC_4_8	PPC_REG_VAL(17, 2)
#घोषणा SDRAM_ECCES_CKBER_32_ECC_0_8	PPC_REG_VAL(17, 3)
#घोषणा SDRAM_ECCES_CE			PPC_REG_VAL(18, 1)
#घोषणा SDRAM_ECCES_UE			PPC_REG_VAL(19, 1)
#घोषणा SDRAM_ECCES_BKNER_MASK		PPC_REG_VAL(21, 0x3)
#घोषणा SDRAM_ECCES_BK0ER		PPC_REG_VAL(20, 1)
#घोषणा SDRAM_ECCES_BK1ER		PPC_REG_VAL(21, 1)

#पूर्ण_अगर /* __PPC4XX_EDAC_H */
