<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Freescale Integrated Flash Controller
 *
 * Copyright 2011 Freescale Semiconductor, Inc
 *
 * Author: Dipen Dudhat <dipen.dudhat@मुक्तscale.com>
 */

#अगर_अघोषित __ASM_FSL_IFC_H
#घोषणा __ASM_FSL_IFC_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>

/*
 * The actual number of banks implemented depends on the IFC version
 *    - IFC version 1.0 implements 4 banks.
 *    - IFC version 1.1 onward implements 8 banks.
 */
#घोषणा FSL_IFC_BANK_COUNT 8

#घोषणा FSL_IFC_VERSION_MASK	0x0F0F0000
#घोषणा FSL_IFC_VERSION_1_0_0	0x01000000
#घोषणा FSL_IFC_VERSION_1_1_0	0x01010000
#घोषणा FSL_IFC_VERSION_2_0_0	0x02000000

#घोषणा PGOFFSET_64K	(64*1024)
#घोषणा PGOFFSET_4K	(4*1024)

/*
 * CSPR - Chip Select Property Register
 */
#घोषणा CSPR_BA				0xFFFF0000
#घोषणा CSPR_BA_SHIFT			16
#घोषणा CSPR_PORT_SIZE			0x00000180
#घोषणा CSPR_PORT_SIZE_SHIFT		7
/* Port Size 8 bit */
#घोषणा CSPR_PORT_SIZE_8		0x00000080
/* Port Size 16 bit */
#घोषणा CSPR_PORT_SIZE_16		0x00000100
/* Port Size 32 bit */
#घोषणा CSPR_PORT_SIZE_32		0x00000180
/* Write Protect */
#घोषणा CSPR_WP				0x00000040
#घोषणा CSPR_WP_SHIFT			6
/* Machine Select */
#घोषणा CSPR_MSEL			0x00000006
#घोषणा CSPR_MSEL_SHIFT			1
/* NOR */
#घोषणा CSPR_MSEL_NOR			0x00000000
/* न_अंकD */
#घोषणा CSPR_MSEL_न_अंकD			0x00000002
/* GPCM */
#घोषणा CSPR_MSEL_GPCM			0x00000004
/* Bank Valid */
#घोषणा CSPR_V				0x00000001
#घोषणा CSPR_V_SHIFT			0

/*
 * Address Mask Register
 */
#घोषणा IFC_AMASK_MASK			0xFFFF0000
#घोषणा IFC_AMASK_SHIFT			16
#घोषणा IFC_AMASK(n)			(IFC_AMASK_MASK << \
					(__ilog2(n) - IFC_AMASK_SHIFT))

/*
 * Chip Select Option Register IFC_न_अंकD Machine
 */
/* Enable ECC Encoder */
#घोषणा CSOR_न_अंकD_ECC_ENC_EN		0x80000000
#घोषणा CSOR_न_अंकD_ECC_MODE_MASK		0x30000000
/* 4 bit correction per 520 Byte sector */
#घोषणा CSOR_न_अंकD_ECC_MODE_4		0x00000000
/* 8 bit correction per 528 Byte sector */
#घोषणा CSOR_न_अंकD_ECC_MODE_8		0x10000000
/* Enable ECC Decoder */
#घोषणा CSOR_न_अंकD_ECC_DEC_EN		0x04000000
/* Row Address Length */
#घोषणा CSOR_न_अंकD_RAL_MASK		0x01800000
#घोषणा CSOR_न_अंकD_RAL_SHIFT		20
#घोषणा CSOR_न_अंकD_RAL_1			0x00000000
#घोषणा CSOR_न_अंकD_RAL_2			0x00800000
#घोषणा CSOR_न_अंकD_RAL_3			0x01000000
#घोषणा CSOR_न_अंकD_RAL_4			0x01800000
/* Page Size 512b, 2k, 4k */
#घोषणा CSOR_न_अंकD_PGS_MASK		0x00180000
#घोषणा CSOR_न_अंकD_PGS_SHIFT		16
#घोषणा CSOR_न_अंकD_PGS_512		0x00000000
#घोषणा CSOR_न_अंकD_PGS_2K		0x00080000
#घोषणा CSOR_न_अंकD_PGS_4K		0x00100000
#घोषणा CSOR_न_अंकD_PGS_8K		0x00180000
/* Spare region Size */
#घोषणा CSOR_न_अंकD_SPRZ_MASK		0x0000E000
#घोषणा CSOR_न_अंकD_SPRZ_SHIFT		13
#घोषणा CSOR_न_अंकD_SPRZ_16		0x00000000
#घोषणा CSOR_न_अंकD_SPRZ_64		0x00002000
#घोषणा CSOR_न_अंकD_SPRZ_128		0x00004000
#घोषणा CSOR_न_अंकD_SPRZ_210		0x00006000
#घोषणा CSOR_न_अंकD_SPRZ_218		0x00008000
#घोषणा CSOR_न_अंकD_SPRZ_224		0x0000A000
#घोषणा CSOR_न_अंकD_SPRZ_CSOR_EXT		0x0000C000
/* Pages Per Block */
#घोषणा CSOR_न_अंकD_PB_MASK		0x00000700
#घोषणा CSOR_न_अंकD_PB_SHIFT		8
#घोषणा CSOR_न_अंकD_PB(n)		((__ilog2(n) - 5) << CSOR_न_अंकD_PB_SHIFT)
/* Time क्रम Read Enable High to Output High Impedance */
#घोषणा CSOR_न_अंकD_TRHZ_MASK		0x0000001C
#घोषणा CSOR_न_अंकD_TRHZ_SHIFT		2
#घोषणा CSOR_न_अंकD_TRHZ_20		0x00000000
#घोषणा CSOR_न_अंकD_TRHZ_40		0x00000004
#घोषणा CSOR_न_अंकD_TRHZ_60		0x00000008
#घोषणा CSOR_न_अंकD_TRHZ_80		0x0000000C
#घोषणा CSOR_न_अंकD_TRHZ_100		0x00000010
/* Buffer control disable */
#घोषणा CSOR_न_अंकD_BCTLD			0x00000001

/*
 * Chip Select Option Register - NOR Flash Mode
 */
/* Enable Address shअगरt Mode */
#घोषणा CSOR_NOR_ADM_SHFT_MODE_EN	0x80000000
/* Page Read Enable from NOR device */
#घोषणा CSOR_NOR_PGRD_EN		0x10000000
/* AVD Toggle Enable during Burst Program */
#घोषणा CSOR_NOR_AVD_TGL_PGM_EN		0x01000000
/* Address Data Multiplexing Shअगरt */
#घोषणा CSOR_NOR_ADM_MASK		0x0003E000
#घोषणा CSOR_NOR_ADM_SHIFT_SHIFT	13
#घोषणा CSOR_NOR_ADM_SHIFT(n)	((n) << CSOR_NOR_ADM_SHIFT_SHIFT)
/* Type of the NOR device hooked */
#घोषणा CSOR_NOR_NOR_MODE_AYSNC_NOR	0x00000000
#घोषणा CSOR_NOR_NOR_MODE_AVD_NOR	0x00000020
/* Time क्रम Read Enable High to Output High Impedance */
#घोषणा CSOR_NOR_TRHZ_MASK		0x0000001C
#घोषणा CSOR_NOR_TRHZ_SHIFT		2
#घोषणा CSOR_NOR_TRHZ_20		0x00000000
#घोषणा CSOR_NOR_TRHZ_40		0x00000004
#घोषणा CSOR_NOR_TRHZ_60		0x00000008
#घोषणा CSOR_NOR_TRHZ_80		0x0000000C
#घोषणा CSOR_NOR_TRHZ_100		0x00000010
/* Buffer control disable */
#घोषणा CSOR_NOR_BCTLD			0x00000001

/*
 * Chip Select Option Register - GPCM Mode
 */
/* GPCM Mode - Normal */
#घोषणा CSOR_GPCM_GPMODE_NORMAL		0x00000000
/* GPCM Mode - GenericASIC */
#घोषणा CSOR_GPCM_GPMODE_ASIC		0x80000000
/* Parity Mode odd/even */
#घोषणा CSOR_GPCM_PARITY_EVEN		0x40000000
/* Parity Checking enable/disable */
#घोषणा CSOR_GPCM_PAR_EN		0x20000000
/* GPCM Timeout Count */
#घोषणा CSOR_GPCM_GPTO_MASK		0x0F000000
#घोषणा CSOR_GPCM_GPTO_SHIFT		24
#घोषणा CSOR_GPCM_GPTO(n)	((__ilog2(n) - 8) << CSOR_GPCM_GPTO_SHIFT)
/* GPCM External Access Termination mode क्रम पढ़ो access */
#घोषणा CSOR_GPCM_RGETA_EXT		0x00080000
/* GPCM External Access Termination mode क्रम ग_लिखो access */
#घोषणा CSOR_GPCM_WGETA_EXT		0x00040000
/* Address Data Multiplexing Shअगरt */
#घोषणा CSOR_GPCM_ADM_MASK		0x0003E000
#घोषणा CSOR_GPCM_ADM_SHIFT_SHIFT	13
#घोषणा CSOR_GPCM_ADM_SHIFT(n)	((n) << CSOR_GPCM_ADM_SHIFT_SHIFT)
/* Generic ASIC Parity error indication delay */
#घोषणा CSOR_GPCM_GAPERRD_MASK		0x00000180
#घोषणा CSOR_GPCM_GAPERRD_SHIFT		7
#घोषणा CSOR_GPCM_GAPERRD(n)	(((n) - 1) << CSOR_GPCM_GAPERRD_SHIFT)
/* Time क्रम Read Enable High to Output High Impedance */
#घोषणा CSOR_GPCM_TRHZ_MASK		0x0000001C
#घोषणा CSOR_GPCM_TRHZ_20		0x00000000
#घोषणा CSOR_GPCM_TRHZ_40		0x00000004
#घोषणा CSOR_GPCM_TRHZ_60		0x00000008
#घोषणा CSOR_GPCM_TRHZ_80		0x0000000C
#घोषणा CSOR_GPCM_TRHZ_100		0x00000010
/* Buffer control disable */
#घोषणा CSOR_GPCM_BCTLD			0x00000001

/*
 * Ready Busy Status Register (RB_STAT)
 */
/* CSn is READY */
#घोषणा IFC_RB_STAT_READY_CS0		0x80000000
#घोषणा IFC_RB_STAT_READY_CS1		0x40000000
#घोषणा IFC_RB_STAT_READY_CS2		0x20000000
#घोषणा IFC_RB_STAT_READY_CS3		0x10000000

/*
 * General Control Register (GCR)
 */
#घोषणा IFC_GCR_MASK			0x8000F800
/* reset all IFC hardware */
#घोषणा IFC_GCR_SOFT_RST_ALL		0x80000000
/* Turnaroud Time of बाह्यal buffer */
#घोषणा IFC_GCR_TBCTL_TRN_TIME		0x0000F800
#घोषणा IFC_GCR_TBCTL_TRN_TIME_SHIFT	11

/*
 * Common Event and Error Status Register (CM_EVTER_STAT)
 */
/* Chip select error */
#घोषणा IFC_CM_EVTER_STAT_CSER		0x80000000

/*
 * Common Event and Error Enable Register (CM_EVTER_EN)
 */
/* Chip select error checking enable */
#घोषणा IFC_CM_EVTER_EN_CSEREN		0x80000000

/*
 * Common Event and Error Interrupt Enable Register (CM_EVTER_INTR_EN)
 */
/* Chip select error पूर्णांकerrupt enable */
#घोषणा IFC_CM_EVTER_INTR_EN_CSERIREN	0x80000000

/*
 * Common Transfer Error Attribute Register-0 (CM_ERATTR0)
 */
/* transaction type of error Read/Write */
#घोषणा IFC_CM_ERATTR0_ERTYP_READ	0x80000000
#घोषणा IFC_CM_ERATTR0_ERAID		0x0FF00000
#घोषणा IFC_CM_ERATTR0_ERAID_SHIFT	20
#घोषणा IFC_CM_ERATTR0_ESRCID		0x0000FF00
#घोषणा IFC_CM_ERATTR0_ESRCID_SHIFT	8

/*
 * Clock Control Register (CCR)
 */
#घोषणा IFC_CCR_MASK			0x0F0F8800
/* Clock भागision ratio */
#घोषणा IFC_CCR_CLK_DIV_MASK		0x0F000000
#घोषणा IFC_CCR_CLK_DIV_SHIFT		24
#घोषणा IFC_CCR_CLK_DIV(n)		((n-1) << IFC_CCR_CLK_DIV_SHIFT)
/* IFC Clock Delay */
#घोषणा IFC_CCR_CLK_DLY_MASK		0x000F0000
#घोषणा IFC_CCR_CLK_DLY_SHIFT		16
#घोषणा IFC_CCR_CLK_DLY(n)		((n) << IFC_CCR_CLK_DLY_SHIFT)
/* Invert IFC घड़ी beक्रमe sending out */
#घोषणा IFC_CCR_INV_CLK_EN		0x00008000
/* Fedback IFC Clock */
#घोषणा IFC_CCR_FB_IFC_CLK_SEL		0x00000800

/*
 * Clock Status Register (CSR)
 */
/* Clk is stable */
#घोषणा IFC_CSR_CLK_STAT_STABLE		0x80000000

/*
 * IFC_न_अंकD Machine Specअगरic Registers
 */
/*
 * न_अंकD Configuration Register (NCFGR)
 */
/* Auto Boot Mode */
#घोषणा IFC_न_अंकD_NCFGR_BOOT		0x80000000
/* SRAM Initialization */
#घोषणा IFC_न_अंकD_NCFGR_SRAM_INIT_EN	0x20000000
/* Addressing Mode-ROW0+n/COL0 */
#घोषणा IFC_न_अंकD_NCFGR_ADDR_MODE_RC0	0x00000000
/* Addressing Mode-ROW0+n/COL0+n */
#घोषणा IFC_न_अंकD_NCFGR_ADDR_MODE_RC1	0x00400000
/* Number of loop iterations of FIR sequences क्रम multi page operations */
#घोषणा IFC_न_अंकD_NCFGR_NUM_LOOP_MASK	0x0000F000
#घोषणा IFC_न_अंकD_NCFGR_NUM_LOOP_SHIFT	12
#घोषणा IFC_न_अंकD_NCFGR_NUM_LOOP(n)	((n) << IFC_न_अंकD_NCFGR_NUM_LOOP_SHIFT)
/* Number of रुको cycles */
#घोषणा IFC_न_अंकD_NCFGR_NUM_WAIT_MASK	0x000000FF
#घोषणा IFC_न_अंकD_NCFGR_NUM_WAIT_SHIFT	0

/*
 * न_अंकD Flash Command Registers (न_अंकD_FCR0/न_अंकD_FCR1)
 */
/* General purpose FCM flash command bytes CMD0-CMD7 */
#घोषणा IFC_न_अंकD_FCR0_CMD0		0xFF000000
#घोषणा IFC_न_अंकD_FCR0_CMD0_SHIFT	24
#घोषणा IFC_न_अंकD_FCR0_CMD1		0x00FF0000
#घोषणा IFC_न_अंकD_FCR0_CMD1_SHIFT	16
#घोषणा IFC_न_अंकD_FCR0_CMD2		0x0000FF00
#घोषणा IFC_न_अंकD_FCR0_CMD2_SHIFT	8
#घोषणा IFC_न_अंकD_FCR0_CMD3		0x000000FF
#घोषणा IFC_न_अंकD_FCR0_CMD3_SHIFT	0
#घोषणा IFC_न_अंकD_FCR1_CMD4		0xFF000000
#घोषणा IFC_न_अंकD_FCR1_CMD4_SHIFT	24
#घोषणा IFC_न_अंकD_FCR1_CMD5		0x00FF0000
#घोषणा IFC_न_अंकD_FCR1_CMD5_SHIFT	16
#घोषणा IFC_न_अंकD_FCR1_CMD6		0x0000FF00
#घोषणा IFC_न_अंकD_FCR1_CMD6_SHIFT	8
#घोषणा IFC_न_अंकD_FCR1_CMD7		0x000000FF
#घोषणा IFC_न_अंकD_FCR1_CMD7_SHIFT	0

/*
 * Flash ROW and COL Address Register (ROWn, COLn)
 */
/* Main/spare region locator */
#घोषणा IFC_न_अंकD_COL_MS			0x80000000
/* Column Address */
#घोषणा IFC_न_अंकD_COL_CA_MASK		0x00000FFF

/*
 * न_अंकD Flash Byte Count Register (न_अंकD_BC)
 */
/* Byte Count क्रम पढ़ो/Write */
#घोषणा IFC_न_अंकD_BC			0x000001FF

/*
 * न_अंकD Flash Inकाष्ठाion Registers (न_अंकD_FIR0/न_अंकD_FIR1/न_अंकD_FIR2)
 */
/* न_अंकD Machine specअगरic opcodes OP0-OP14*/
#घोषणा IFC_न_अंकD_FIR0_OP0		0xFC000000
#घोषणा IFC_न_अंकD_FIR0_OP0_SHIFT		26
#घोषणा IFC_न_अंकD_FIR0_OP1		0x03F00000
#घोषणा IFC_न_अंकD_FIR0_OP1_SHIFT		20
#घोषणा IFC_न_अंकD_FIR0_OP2		0x000FC000
#घोषणा IFC_न_अंकD_FIR0_OP2_SHIFT		14
#घोषणा IFC_न_अंकD_FIR0_OP3		0x00003F00
#घोषणा IFC_न_अंकD_FIR0_OP3_SHIFT		8
#घोषणा IFC_न_अंकD_FIR0_OP4		0x000000FC
#घोषणा IFC_न_अंकD_FIR0_OP4_SHIFT		2
#घोषणा IFC_न_अंकD_FIR1_OP5		0xFC000000
#घोषणा IFC_न_अंकD_FIR1_OP5_SHIFT		26
#घोषणा IFC_न_अंकD_FIR1_OP6		0x03F00000
#घोषणा IFC_न_अंकD_FIR1_OP6_SHIFT		20
#घोषणा IFC_न_अंकD_FIR1_OP7		0x000FC000
#घोषणा IFC_न_अंकD_FIR1_OP7_SHIFT		14
#घोषणा IFC_न_अंकD_FIR1_OP8		0x00003F00
#घोषणा IFC_न_अंकD_FIR1_OP8_SHIFT		8
#घोषणा IFC_न_अंकD_FIR1_OP9		0x000000FC
#घोषणा IFC_न_अंकD_FIR1_OP9_SHIFT		2
#घोषणा IFC_न_अंकD_FIR2_OP10		0xFC000000
#घोषणा IFC_न_अंकD_FIR2_OP10_SHIFT	26
#घोषणा IFC_न_अंकD_FIR2_OP11		0x03F00000
#घोषणा IFC_न_अंकD_FIR2_OP11_SHIFT	20
#घोषणा IFC_न_अंकD_FIR2_OP12		0x000FC000
#घोषणा IFC_न_अंकD_FIR2_OP12_SHIFT	14
#घोषणा IFC_न_अंकD_FIR2_OP13		0x00003F00
#घोषणा IFC_न_अंकD_FIR2_OP13_SHIFT	8
#घोषणा IFC_न_अंकD_FIR2_OP14		0x000000FC
#घोषणा IFC_न_अंकD_FIR2_OP14_SHIFT	2

/*
 * Inकाष्ठाion opcodes to be programmed
 * in FIR रेजिस्टरs- 6bits
 */
क्रमागत अगरc_nand_fir_opcodes अणु
	IFC_FIR_OP_NOP,
	IFC_FIR_OP_CA0,
	IFC_FIR_OP_CA1,
	IFC_FIR_OP_CA2,
	IFC_FIR_OP_CA3,
	IFC_FIR_OP_RA0,
	IFC_FIR_OP_RA1,
	IFC_FIR_OP_RA2,
	IFC_FIR_OP_RA3,
	IFC_FIR_OP_CMD0,
	IFC_FIR_OP_CMD1,
	IFC_FIR_OP_CMD2,
	IFC_FIR_OP_CMD3,
	IFC_FIR_OP_CMD4,
	IFC_FIR_OP_CMD5,
	IFC_FIR_OP_CMD6,
	IFC_FIR_OP_CMD7,
	IFC_FIR_OP_CW0,
	IFC_FIR_OP_CW1,
	IFC_FIR_OP_CW2,
	IFC_FIR_OP_CW3,
	IFC_FIR_OP_CW4,
	IFC_FIR_OP_CW5,
	IFC_FIR_OP_CW6,
	IFC_FIR_OP_CW7,
	IFC_FIR_OP_WBCD,
	IFC_FIR_OP_RBCD,
	IFC_FIR_OP_BTRD,
	IFC_FIR_OP_RDSTAT,
	IFC_FIR_OP_NWAIT,
	IFC_FIR_OP_WFR,
	IFC_FIR_OP_SBRD,
	IFC_FIR_OP_UA,
	IFC_FIR_OP_RB,
पूर्ण;

/*
 * न_अंकD Chip Select Register (न_अंकD_CSEL)
 */
#घोषणा IFC_न_अंकD_CSEL			0x0C000000
#घोषणा IFC_न_अंकD_CSEL_SHIFT		26
#घोषणा IFC_न_अंकD_CSEL_CS0		0x00000000
#घोषणा IFC_न_अंकD_CSEL_CS1		0x04000000
#घोषणा IFC_न_अंकD_CSEL_CS2		0x08000000
#घोषणा IFC_न_अंकD_CSEL_CS3		0x0C000000

/*
 * न_अंकD Operation Sequence Start (न_अंकDSEQ_STRT)
 */
/* न_अंकD Flash Operation Start */
#घोषणा IFC_न_अंकD_SEQ_STRT_FIR_STRT	0x80000000
/* Automatic Erase */
#घोषणा IFC_न_अंकD_SEQ_STRT_AUTO_ERS	0x00800000
/* Automatic Program */
#घोषणा IFC_न_अंकD_SEQ_STRT_AUTO_PGM	0x00100000
/* Automatic Copyback */
#घोषणा IFC_न_अंकD_SEQ_STRT_AUTO_CPB	0x00020000
/* Automatic Read Operation */
#घोषणा IFC_न_अंकD_SEQ_STRT_AUTO_RD	0x00004000
/* Automatic Status Read */
#घोषणा IFC_न_अंकD_SEQ_STRT_AUTO_STAT_RD	0x00000800

/*
 * न_अंकD Event and Error Status Register (न_अंकD_EVTER_STAT)
 */
/* Operation Complete */
#घोषणा IFC_न_अंकD_EVTER_STAT_OPC		0x80000000
/* Flash Timeout Error */
#घोषणा IFC_न_अंकD_EVTER_STAT_FTOER	0x08000000
/* Write Protect Error */
#घोषणा IFC_न_अंकD_EVTER_STAT_WPER	0x04000000
/* ECC Error */
#घोषणा IFC_न_अंकD_EVTER_STAT_ECCER	0x02000000
/* RCW Load Done */
#घोषणा IFC_न_अंकD_EVTER_STAT_RCW_DN	0x00008000
/* Boot Loadr Done */
#घोषणा IFC_न_अंकD_EVTER_STAT_BOOT_DN	0x00004000
/* Bad Block Indicator search select */
#घोषणा IFC_न_अंकD_EVTER_STAT_BBI_SRCH_SE	0x00000800

/*
 * न_अंकD Flash Page Read Completion Event Status Register
 * (PGRDCMPL_EVT_STAT)
 */
#घोषणा PGRDCMPL_EVT_STAT_MASK		0xFFFF0000
/* Small Page 0-15 Done */
#घोषणा PGRDCMPL_EVT_STAT_SECTION_SP(n)	(1 << (31 - (n)))
/* Large Page(2K) 0-3 Done */
#घोषणा PGRDCMPL_EVT_STAT_LP_2K(n)	(0xF << (28 - (n)*4))
/* Large Page(4K) 0-1 Done */
#घोषणा PGRDCMPL_EVT_STAT_LP_4K(n)	(0xFF << (24 - (n)*8))

/*
 * न_अंकD Event and Error Enable Register (न_अंकD_EVTER_EN)
 */
/* Operation complete event enable */
#घोषणा IFC_न_अंकD_EVTER_EN_OPC_EN	0x80000000
/* Page पढ़ो complete event enable */
#घोषणा IFC_न_अंकD_EVTER_EN_PGRDCMPL_EN	0x20000000
/* Flash Timeout error enable */
#घोषणा IFC_न_अंकD_EVTER_EN_FTOER_EN	0x08000000
/* Write Protect error enable */
#घोषणा IFC_न_अंकD_EVTER_EN_WPER_EN	0x04000000
/* ECC error logging enable */
#घोषणा IFC_न_अंकD_EVTER_EN_ECCER_EN	0x02000000

/*
 * न_अंकD Event and Error Interrupt Enable Register (न_अंकD_EVTER_INTR_EN)
 */
/* Enable पूर्णांकerrupt क्रम operation complete */
#घोषणा IFC_न_अंकD_EVTER_INTR_OPCIR_EN		0x80000000
/* Enable पूर्णांकerrupt क्रम Page पढ़ो complete */
#घोषणा IFC_न_अंकD_EVTER_INTR_PGRDCMPLIR_EN	0x20000000
/* Enable पूर्णांकerrupt क्रम Flash समयout error */
#घोषणा IFC_न_अंकD_EVTER_INTR_FTOERIR_EN		0x08000000
/* Enable पूर्णांकerrupt क्रम Write protect error */
#घोषणा IFC_न_अंकD_EVTER_INTR_WPERIR_EN		0x04000000
/* Enable पूर्णांकerrupt क्रम ECC error*/
#घोषणा IFC_न_अंकD_EVTER_INTR_ECCERIR_EN		0x02000000

/*
 * न_अंकD Transfer Error Attribute Register-0 (न_अंकD_ERATTR0)
 */
#घोषणा IFC_न_अंकD_ERATTR0_MASK		0x0C080000
/* Error on CS0-3 क्रम न_अंकD */
#घोषणा IFC_न_अंकD_ERATTR0_ERCS_CS0	0x00000000
#घोषणा IFC_न_अंकD_ERATTR0_ERCS_CS1	0x04000000
#घोषणा IFC_न_अंकD_ERATTR0_ERCS_CS2	0x08000000
#घोषणा IFC_न_अंकD_ERATTR0_ERCS_CS3	0x0C000000
/* Transaction type of error Read/Write */
#घोषणा IFC_न_अंकD_ERATTR0_ERTTYPE_READ	0x00080000

/*
 * न_अंकD Flash Status Register (न_अंकD_FSR)
 */
/* First byte of data पढ़ो from पढ़ो status op */
#घोषणा IFC_न_अंकD_NFSR_RS0		0xFF000000
/* Second byte of data पढ़ो from पढ़ो status op */
#घोषणा IFC_न_अंकD_NFSR_RS1		0x00FF0000

/*
 * ECC Error Status Registers (ECCSTAT0-ECCSTAT3)
 */
/* Number of ECC errors on sector n (n = 0-15) */
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR0_MASK	0x0F000000
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR0_SHIFT	24
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR1_MASK	0x000F0000
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR1_SHIFT	16
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR2_MASK	0x00000F00
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR2_SHIFT	8
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR3_MASK	0x0000000F
#घोषणा IFC_न_अंकD_ECCSTAT0_ERRCNT_SECTOR3_SHIFT	0
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR4_MASK	0x0F000000
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR4_SHIFT	24
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR5_MASK	0x000F0000
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR5_SHIFT	16
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR6_MASK	0x00000F00
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR6_SHIFT	8
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR7_MASK	0x0000000F
#घोषणा IFC_न_अंकD_ECCSTAT1_ERRCNT_SECTOR7_SHIFT	0
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR8_MASK	0x0F000000
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR8_SHIFT	24
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR9_MASK	0x000F0000
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR9_SHIFT	16
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR10_MASK	0x00000F00
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR10_SHIFT	8
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR11_MASK	0x0000000F
#घोषणा IFC_न_अंकD_ECCSTAT2_ERRCNT_SECTOR11_SHIFT	0
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR12_MASK	0x0F000000
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR12_SHIFT	24
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR13_MASK	0x000F0000
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR13_SHIFT	16
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR14_MASK	0x00000F00
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR14_SHIFT	8
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR15_MASK	0x0000000F
#घोषणा IFC_न_अंकD_ECCSTAT3_ERRCNT_SECTOR15_SHIFT	0

/*
 * न_अंकD Control Register (न_अंकDCR)
 */
#घोषणा IFC_न_अंकD_NCR_FTOCNT_MASK	0x1E000000
#घोषणा IFC_न_अंकD_NCR_FTOCNT_SHIFT	25
#घोषणा IFC_न_अंकD_NCR_FTOCNT(n)	((_ilog2(n) - 8)  << IFC_न_अंकD_NCR_FTOCNT_SHIFT)

/*
 * न_अंकD_AUTOBOOT_TRGR
 */
/* Trigger RCW load */
#घोषणा IFC_न_अंकD_AUTOBOOT_TRGR_RCW_LD	0x80000000
/* Trigget Auto Boot */
#घोषणा IFC_न_अंकD_AUTOBOOT_TRGR_BOOT_LD	0x20000000

/*
 * न_अंकD_MDR
 */
/* 1st पढ़ो data byte when opcode SBRD */
#घोषणा IFC_न_अंकD_MDR_RDATA0		0xFF000000
/* 2nd पढ़ो data byte when opcode SBRD */
#घोषणा IFC_न_अंकD_MDR_RDATA1		0x00FF0000

/*
 * NOR Machine Specअगरic Registers
 */
/*
 * NOR Event and Error Status Register (NOR_EVTER_STAT)
 */
/* NOR Command Sequence Operation Complete */
#घोषणा IFC_NOR_EVTER_STAT_OPC_NOR	0x80000000
/* Write Protect Error */
#घोषणा IFC_NOR_EVTER_STAT_WPER		0x04000000
/* Command Sequence Timeout Error */
#घोषणा IFC_NOR_EVTER_STAT_STOER	0x01000000

/*
 * NOR Event and Error Enable Register (NOR_EVTER_EN)
 */
/* NOR Command Seq complete event enable */
#घोषणा IFC_NOR_EVTER_EN_OPCEN_NOR	0x80000000
/* Write Protect Error Checking Enable */
#घोषणा IFC_NOR_EVTER_EN_WPEREN		0x04000000
/* Timeout Error Enable */
#घोषणा IFC_NOR_EVTER_EN_STOEREN	0x01000000

/*
 * NOR Event and Error Interrupt Enable Register (NOR_EVTER_INTR_EN)
 */
/* Enable पूर्णांकerrupt क्रम OPC complete */
#घोषणा IFC_NOR_EVTER_INTR_OPCEN_NOR	0x80000000
/* Enable पूर्णांकerrupt क्रम ग_लिखो protect error */
#घोषणा IFC_NOR_EVTER_INTR_WPEREN	0x04000000
/* Enable पूर्णांकerrupt क्रम समयout error */
#घोषणा IFC_NOR_EVTER_INTR_STOEREN	0x01000000

/*
 * NOR Transfer Error Attribute Register-0 (NOR_ERATTR0)
 */
/* Source ID क्रम error transaction */
#घोषणा IFC_NOR_ERATTR0_ERSRCID		0xFF000000
/* AXI ID क्रम error transation */
#घोषणा IFC_NOR_ERATTR0_ERAID		0x000FF000
/* Chip select corresponds to NOR error */
#घोषणा IFC_NOR_ERATTR0_ERCS_CS0	0x00000000
#घोषणा IFC_NOR_ERATTR0_ERCS_CS1	0x00000010
#घोषणा IFC_NOR_ERATTR0_ERCS_CS2	0x00000020
#घोषणा IFC_NOR_ERATTR0_ERCS_CS3	0x00000030
/* Type of transaction पढ़ो/ग_लिखो */
#घोषणा IFC_NOR_ERATTR0_ERTYPE_READ	0x00000001

/*
 * NOR Transfer Error Attribute Register-2 (NOR_ERATTR2)
 */
#घोषणा IFC_NOR_ERATTR2_ER_NUM_PHASE_EXP	0x000F0000
#घोषणा IFC_NOR_ERATTR2_ER_NUM_PHASE_PER	0x00000F00

/*
 * NOR Control Register (NORCR)
 */
#घोषणा IFC_NORCR_MASK			0x0F0F0000
/* No. of Address/Data Phase */
#घोषणा IFC_NORCR_NUM_PHASE_MASK	0x0F000000
#घोषणा IFC_NORCR_NUM_PHASE_SHIFT	24
#घोषणा IFC_NORCR_NUM_PHASE(n)	((n-1) << IFC_NORCR_NUM_PHASE_SHIFT)
/* Sequence Timeout Count */
#घोषणा IFC_NORCR_STOCNT_MASK		0x000F0000
#घोषणा IFC_NORCR_STOCNT_SHIFT		16
#घोषणा IFC_NORCR_STOCNT(n)	((__ilog2(n) - 8) << IFC_NORCR_STOCNT_SHIFT)

/*
 * GPCM Machine specअगरic रेजिस्टरs
 */
/*
 * GPCM Event and Error Status Register (GPCM_EVTER_STAT)
 */
/* Timeout error */
#घोषणा IFC_GPCM_EVTER_STAT_TOER	0x04000000
/* Parity error */
#घोषणा IFC_GPCM_EVTER_STAT_PER		0x01000000

/*
 * GPCM Event and Error Enable Register (GPCM_EVTER_EN)
 */
/* Timeout error enable */
#घोषणा IFC_GPCM_EVTER_EN_TOER_EN	0x04000000
/* Parity error enable */
#घोषणा IFC_GPCM_EVTER_EN_PER_EN	0x01000000

/*
 * GPCM Event and Error Interrupt Enable Register (GPCM_EVTER_INTR_EN)
 */
/* Enable Interrupt क्रम समयout error */
#घोषणा IFC_GPCM_EEIER_TOERIR_EN	0x04000000
/* Enable Interrupt क्रम Parity error */
#घोषणा IFC_GPCM_EEIER_PERIR_EN		0x01000000

/*
 * GPCM Transfer Error Attribute Register-0 (GPCM_ERATTR0)
 */
/* Source ID क्रम error transaction */
#घोषणा IFC_GPCM_ERATTR0_ERSRCID	0xFF000000
/* AXI ID क्रम error transaction */
#घोषणा IFC_GPCM_ERATTR0_ERAID		0x000FF000
/* Chip select corresponds to GPCM error */
#घोषणा IFC_GPCM_ERATTR0_ERCS_CS0	0x00000000
#घोषणा IFC_GPCM_ERATTR0_ERCS_CS1	0x00000040
#घोषणा IFC_GPCM_ERATTR0_ERCS_CS2	0x00000080
#घोषणा IFC_GPCM_ERATTR0_ERCS_CS3	0x000000C0
/* Type of transaction पढ़ो/Write */
#घोषणा IFC_GPCM_ERATTR0_ERTYPE_READ	0x00000001

/*
 * GPCM Transfer Error Attribute Register-2 (GPCM_ERATTR2)
 */
/* On which beat of address/data parity error is observed */
#घोषणा IFC_GPCM_ERATTR2_PERR_BEAT		0x00000C00
/* Parity Error on byte */
#घोषणा IFC_GPCM_ERATTR2_PERR_BYTE		0x000000F0
/* Parity Error reported in addr or data phase */
#घोषणा IFC_GPCM_ERATTR2_PERR_DATA_PHASE	0x00000001

/*
 * GPCM Status Register (GPCM_STAT)
 */
#घोषणा IFC_GPCM_STAT_BSY		0x80000000  /* GPCM is busy */

/*
 * IFC Controller न_अंकD Machine रेजिस्टरs
 */
काष्ठा fsl_अगरc_nand अणु
	__be32 ncfgr;
	u32 res1[0x4];
	__be32 nand_fcr0;
	__be32 nand_fcr1;
	u32 res2[0x8];
	__be32 row0;
	u32 res3;
	__be32 col0;
	u32 res4;
	__be32 row1;
	u32 res5;
	__be32 col1;
	u32 res6;
	__be32 row2;
	u32 res7;
	__be32 col2;
	u32 res8;
	__be32 row3;
	u32 res9;
	__be32 col3;
	u32 res10[0x24];
	__be32 nand_fbcr;
	u32 res11;
	__be32 nand_fir0;
	__be32 nand_fir1;
	__be32 nand_fir2;
	u32 res12[0x10];
	__be32 nand_csel;
	u32 res13;
	__be32 nandseq_strt;
	u32 res14;
	__be32 nand_evter_stat;
	u32 res15;
	__be32 pgrdcmpl_evt_stat;
	u32 res16[0x2];
	__be32 nand_evter_en;
	u32 res17[0x2];
	__be32 nand_evter_पूर्णांकr_en;
	__be32 nand_vol_addr_stat;
	u32 res18;
	__be32 nand_erattr0;
	__be32 nand_erattr1;
	u32 res19[0x10];
	__be32 nand_fsr;
	u32 res20;
	__be32 nand_eccstat[8];
	u32 res21[0x1c];
	__be32 nanndcr;
	u32 res22[0x2];
	__be32 nand_स्वतःboot_trgr;
	u32 res23;
	__be32 nand_mdr;
	u32 res24[0x1C];
	__be32 nand_dll_lowcfg0;
	__be32 nand_dll_lowcfg1;
	u32 res25;
	__be32 nand_dll_lowstat;
	u32 res26[0x3c];
पूर्ण;

/*
 * IFC controller NOR Machine रेजिस्टरs
 */
काष्ठा fsl_अगरc_nor अणु
	__be32 nor_evter_stat;
	u32 res1[0x2];
	__be32 nor_evter_en;
	u32 res2[0x2];
	__be32 nor_evter_पूर्णांकr_en;
	u32 res3[0x2];
	__be32 nor_erattr0;
	__be32 nor_erattr1;
	__be32 nor_erattr2;
	u32 res4[0x4];
	__be32 norcr;
	u32 res5[0xEF];
पूर्ण;

/*
 * IFC controller GPCM Machine रेजिस्टरs
 */
काष्ठा fsl_अगरc_gpcm अणु
	__be32 gpcm_evter_stat;
	u32 res1[0x2];
	__be32 gpcm_evter_en;
	u32 res2[0x2];
	__be32 gpcm_evter_पूर्णांकr_en;
	u32 res3[0x2];
	__be32 gpcm_erattr0;
	__be32 gpcm_erattr1;
	__be32 gpcm_erattr2;
	__be32 gpcm_stat;
पूर्ण;

/*
 * IFC Controller Registers
 */
काष्ठा fsl_अगरc_global अणु
	__be32 अगरc_rev;
	u32 res1[0x2];
	काष्ठा अणु
		__be32 cspr_ext;
		__be32 cspr;
		u32 res2;
	पूर्ण cspr_cs[FSL_IFC_BANK_COUNT];
	u32 res3[0xd];
	काष्ठा अणु
		__be32 amask;
		u32 res4[0x2];
	पूर्ण amask_cs[FSL_IFC_BANK_COUNT];
	u32 res5[0xc];
	काष्ठा अणु
		__be32 csor;
		__be32 csor_ext;
		u32 res6;
	पूर्ण csor_cs[FSL_IFC_BANK_COUNT];
	u32 res7[0xc];
	काष्ठा अणु
		__be32 ftim[4];
		u32 res8[0x8];
	पूर्ण ftim_cs[FSL_IFC_BANK_COUNT];
	u32 res9[0x30];
	__be32 rb_stat;
	__be32 rb_map;
	__be32 wb_map;
	__be32 अगरc_gcr;
	u32 res10[0x2];
	__be32 cm_evter_stat;
	u32 res11[0x2];
	__be32 cm_evter_en;
	u32 res12[0x2];
	__be32 cm_evter_पूर्णांकr_en;
	u32 res13[0x2];
	__be32 cm_erattr0;
	__be32 cm_erattr1;
	u32 res14[0x2];
	__be32 अगरc_ccr;
	__be32 अगरc_csr;
	__be32 ddr_ccr_low;
पूर्ण;


काष्ठा fsl_अगरc_runसमय अणु
	काष्ठा fsl_अगरc_nand अगरc_nand;
	काष्ठा fsl_अगरc_nor अगरc_nor;
	काष्ठा fsl_अगरc_gpcm अगरc_gpcm;
पूर्ण;

बाह्य अचिन्हित पूर्णांक convert_अगरc_address(phys_addr_t addr_base);
बाह्य पूर्णांक fsl_अगरc_find(phys_addr_t addr_base);

/* overview of the fsl अगरc controller */

काष्ठा fsl_अगरc_ctrl अणु
	/* device info */
	काष्ठा device			*dev;
	काष्ठा fsl_अगरc_global __iomem	*gregs;
	काष्ठा fsl_अगरc_runसमय __iomem	*rregs;
	पूर्णांक				irq;
	पूर्णांक				nand_irq;
	spinlock_t			lock;
	व्योम				*nand;
	पूर्णांक				version;
	पूर्णांक				banks;

	u32 nand_stat;
	रुको_queue_head_t nand_रुको;
	bool little_endian;
पूर्ण;

बाह्य काष्ठा fsl_अगरc_ctrl *fsl_अगरc_ctrl_dev;

अटल अंतरभूत u32 अगरc_in32(व्योम __iomem *addr)
अणु
	u32 val;

	अगर (fsl_अगरc_ctrl_dev->little_endian)
		val = ioपढ़ो32(addr);
	अन्यथा
		val = ioपढ़ो32be(addr);

	वापस val;
पूर्ण

अटल अंतरभूत u16 अगरc_in16(व्योम __iomem *addr)
अणु
	u16 val;

	अगर (fsl_अगरc_ctrl_dev->little_endian)
		val = ioपढ़ो16(addr);
	अन्यथा
		val = ioपढ़ो16be(addr);

	वापस val;
पूर्ण

अटल अंतरभूत u8 अगरc_in8(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो8(addr);
पूर्ण

अटल अंतरभूत व्योम अगरc_out32(u32 val, व्योम __iomem *addr)
अणु
	अगर (fsl_अगरc_ctrl_dev->little_endian)
		ioग_लिखो32(val, addr);
	अन्यथा
		ioग_लिखो32be(val, addr);
पूर्ण

अटल अंतरभूत व्योम अगरc_out16(u16 val, व्योम __iomem *addr)
अणु
	अगर (fsl_अगरc_ctrl_dev->little_endian)
		ioग_लिखो16(val, addr);
	अन्यथा
		ioग_लिखो16be(val, addr);
पूर्ण

अटल अंतरभूत व्योम अगरc_out8(u8 val, व्योम __iomem *addr)
अणु
	ioग_लिखो8(val, addr);
पूर्ण

#पूर्ण_अगर /* __ASM_FSL_IFC_H */
