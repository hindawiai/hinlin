<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/emac.h
 *
 * Register definitions क्रम PowerPC 4xx on-chip ethernet contoller
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright (c) 2004, 2005 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Based on original work by
 *      Matt Porter <mporter@kernel.crashing.org>
 *      Armin Kuster <akuster@mvista.com>
 * 	Copyright 2002-2004 MontaVista Software Inc.
 */
#अगर_अघोषित __IBM_NEWEMAC_H
#घोषणा __IBM_NEWEMAC_H

#समावेश <linux/types.h>
#समावेश <linux/phy.h>

/* EMAC रेजिस्टरs 			Write Access rules */
काष्ठा emac_regs अणु
	/* Common रेजिस्टरs across all EMAC implementations. */
	u32 mr0;			/* Special 	*/
	u32 mr1;			/* Reset 	*/
	u32 पंचांगr0;			/* Special 	*/
	u32 पंचांगr1;			/* Special 	*/
	u32 rmr;			/* Reset 	*/
	u32 isr;			/* Always 	*/
	u32 iser;			/* Reset 	*/
	u32 iahr;			/* Reset, R, T 	*/
	u32 ialr;			/* Reset, R, T 	*/
	u32 vtpid;			/* Reset, R, T 	*/
	u32 vtci;			/* Reset, R, T 	*/
	u32 ptr;			/* Reset,    T 	*/
	जोड़ अणु
		/* Registers unique to EMAC4 implementations */
		काष्ठा अणु
			u32 iaht1;	/* Reset, R	*/
			u32 iaht2;	/* Reset, R	*/
			u32 iaht3;	/* Reset, R	*/
			u32 iaht4;	/* Reset, R	*/
			u32 gaht1;	/* Reset, R	*/
			u32 gaht2;	/* Reset, R	*/
			u32 gaht3;	/* Reset, R	*/
			u32 gaht4;	/* Reset, R	*/
		पूर्ण emac4;
		/* Registers unique to EMAC4SYNC implementations */
		काष्ठा अणु
			u32 mahr;	/* Reset, R, T  */
			u32 malr;	/* Reset, R, T  */
			u32 mmahr;	/* Reset, R, T  */
			u32 mmalr;	/* Reset, R, T  */
			u32 rsvd0[4];
		पूर्ण emac4sync;
	पूर्ण u0;
	/* Common रेजिस्टरs across all EMAC implementations. */
	u32 lsah;
	u32 lsal;
	u32 ipgvr;			/* Reset,    T 	*/
	u32 stacr;			/* Special 	*/
	u32 trtr;			/* Special 	*/
	u32 rwmr;			/* Reset 	*/
	u32 octx;
	u32 ocrx;
	जोड़ अणु
		/* Registers unique to EMAC4 implementations */
		काष्ठा अणु
			u32 ipcr;
		पूर्ण emac4;
		/* Registers unique to EMAC4SYNC implementations */
		काष्ठा अणु
			u32 rsvd1;
			u32 revid;
 			u32 rsvd2[2];
			u32 iaht1;	/* Reset, R     */
			u32 iaht2;	/* Reset, R     */
			u32 iaht3;	/* Reset, R     */
			u32 iaht4;	/* Reset, R     */
			u32 iaht5;	/* Reset, R     */
			u32 iaht6;	/* Reset, R     */
			u32 iaht7;	/* Reset, R     */
			u32 iaht8;	/* Reset, R     */
			u32 gaht1;	/* Reset, R     */
			u32 gaht2;	/* Reset, R     */
			u32 gaht3;	/* Reset, R     */
			u32 gaht4;	/* Reset, R     */
			u32 gaht5;	/* Reset, R     */
			u32 gaht6;	/* Reset, R     */
			u32 gaht7;	/* Reset, R     */
			u32 gaht8;	/* Reset, R     */
			u32 tpc;	/* Reset, T     */
		पूर्ण emac4sync;
	पूर्ण u1;
पूर्ण;

/* EMACx_MR0 */
#घोषणा EMAC_MR0_RXI			0x80000000
#घोषणा EMAC_MR0_TXI			0x40000000
#घोषणा EMAC_MR0_SRST			0x20000000
#घोषणा EMAC_MR0_TXE			0x10000000
#घोषणा EMAC_MR0_RXE			0x08000000
#घोषणा EMAC_MR0_WKE			0x04000000

/* EMACx_MR1 */
#घोषणा EMAC_MR1_FDE			0x80000000
#घोषणा EMAC_MR1_ILE			0x40000000
#घोषणा EMAC_MR1_VLE			0x20000000
#घोषणा EMAC_MR1_EIFC			0x10000000
#घोषणा EMAC_MR1_APP			0x08000000
#घोषणा EMAC_MR1_IST			0x01000000

#घोषणा EMAC_MR1_MF_MASK		0x00c00000
#घोषणा EMAC_MR1_MF_10			0x00000000
#घोषणा EMAC_MR1_MF_100			0x00400000
#घोषणा EMAC_MR1_MF_1000		0x00800000
#घोषणा EMAC_MR1_MF_1000GPCS		0x00c00000
#घोषणा EMAC_MR1_MF_IPPA(id)		(((id) & 0x1f) << 6)

#घोषणा EMAC_MR1_RFS_4K			0x00300000
#घोषणा EMAC_MR1_RFS_16K		0x00000000
#घोषणा EMAC_MR1_TFS_2K			0x00080000
#घोषणा EMAC_MR1_TR0_MULT		0x00008000
#घोषणा EMAC_MR1_JPSM			0x00000000
#घोषणा EMAC_MR1_MWSW_001		0x00000000
#घोषणा EMAC_MR1_BASE(opb)		(EMAC_MR1_TFS_2K | EMAC_MR1_TR0_MULT)


#घोषणा EMAC4_MR1_RFS_2K		0x00100000
#घोषणा EMAC4_MR1_RFS_4K		0x00180000
#घोषणा EMAC4_MR1_RFS_8K		0x00200000
#घोषणा EMAC4_MR1_RFS_16K		0x00280000
#घोषणा EMAC4_MR1_TFS_2K       		0x00020000
#घोषणा EMAC4_MR1_TFS_4K		0x00030000
#घोषणा EMAC4_MR1_TFS_8K		0x00040000
#घोषणा EMAC4_MR1_TFS_16K		0x00050000
#घोषणा EMAC4_MR1_TR			0x00008000
#घोषणा EMAC4_MR1_MWSW_001		0x00001000
#घोषणा EMAC4_MR1_JPSM			0x00000800
#घोषणा EMAC4_MR1_OBCI_MASK		0x00000038
#घोषणा EMAC4_MR1_OBCI_50		0x00000000
#घोषणा EMAC4_MR1_OBCI_66		0x00000008
#घोषणा EMAC4_MR1_OBCI_83		0x00000010
#घोषणा EMAC4_MR1_OBCI_100		0x00000018
#घोषणा EMAC4_MR1_OBCI_100P		0x00000020
#घोषणा EMAC4_MR1_OBCI(freq)		((freq) <= 50  ? EMAC4_MR1_OBCI_50 : \
					 (freq) <= 66  ? EMAC4_MR1_OBCI_66 : \
					 (freq) <= 83  ? EMAC4_MR1_OBCI_83 : \
					 (freq) <= 100 ? EMAC4_MR1_OBCI_100 : \
						EMAC4_MR1_OBCI_100P)

/* EMACx_TMR0 */
#घोषणा EMAC_TMR0_GNP			0x80000000
#घोषणा EMAC_TMR0_DEFAULT		0x00000000
#घोषणा EMAC4_TMR0_TFAE_2_32		0x00000001
#घोषणा EMAC4_TMR0_TFAE_4_64		0x00000002
#घोषणा EMAC4_TMR0_TFAE_8_128		0x00000003
#घोषणा EMAC4_TMR0_TFAE_16_256		0x00000004
#घोषणा EMAC4_TMR0_TFAE_32_512		0x00000005
#घोषणा EMAC4_TMR0_TFAE_64_1024		0x00000006
#घोषणा EMAC4_TMR0_TFAE_128_2048	0x00000007
#घोषणा EMAC4_TMR0_DEFAULT		EMAC4_TMR0_TFAE_2_32
#घोषणा EMAC_TMR0_XMIT			(EMAC_TMR0_GNP | EMAC_TMR0_DEFAULT)
#घोषणा EMAC4_TMR0_XMIT			(EMAC_TMR0_GNP | EMAC4_TMR0_DEFAULT)

/* EMACx_TMR1 */

#घोषणा EMAC_TMR1(l,h)			(((l) << 27) | (((h) & 0xff) << 16))
#घोषणा EMAC4_TMR1(l,h)			(((l) << 27) | (((h) & 0x3ff) << 14))

/* EMACx_RMR */
#घोषणा EMAC_RMR_SP			0x80000000
#घोषणा EMAC_RMR_SFCS			0x40000000
#घोषणा EMAC_RMR_RRP			0x20000000
#घोषणा EMAC_RMR_RFP			0x10000000
#घोषणा EMAC_RMR_ROP			0x08000000
#घोषणा EMAC_RMR_RPIR			0x04000000
#घोषणा EMAC_RMR_PPP			0x02000000
#घोषणा EMAC_RMR_PME			0x01000000
#घोषणा EMAC_RMR_PMME			0x00800000
#घोषणा EMAC_RMR_IAE			0x00400000
#घोषणा EMAC_RMR_MIAE			0x00200000
#घोषणा EMAC_RMR_BAE			0x00100000
#घोषणा EMAC_RMR_MAE			0x00080000
#घोषणा EMAC_RMR_BASE			0x00000000
#घोषणा EMAC4_RMR_RFAF_2_32		0x00000001
#घोषणा EMAC4_RMR_RFAF_4_64		0x00000002
#घोषणा EMAC4_RMR_RFAF_8_128		0x00000003
#घोषणा EMAC4_RMR_RFAF_16_256		0x00000004
#घोषणा EMAC4_RMR_RFAF_32_512		0x00000005
#घोषणा EMAC4_RMR_RFAF_64_1024		0x00000006
#घोषणा EMAC4_RMR_RFAF_128_2048		0x00000007
#घोषणा EMAC4_RMR_BASE			EMAC4_RMR_RFAF_128_2048
#घोषणा EMAC4_RMR_MJS_MASK              0x0001fff8
#घोषणा EMAC4_RMR_MJS(s)                (((s) << 3) & EMAC4_RMR_MJS_MASK)

/* EMACx_ISR & EMACx_ISER */
#घोषणा EMAC4_ISR_TXPE			0x20000000
#घोषणा EMAC4_ISR_RXPE			0x10000000
#घोषणा EMAC4_ISR_TXUE			0x08000000
#घोषणा EMAC4_ISR_RXOE			0x04000000
#घोषणा EMAC_ISR_OVR			0x02000000
#घोषणा EMAC_ISR_PP			0x01000000
#घोषणा EMAC_ISR_BP			0x00800000
#घोषणा EMAC_ISR_RP			0x00400000
#घोषणा EMAC_ISR_SE			0x00200000
#घोषणा EMAC_ISR_ALE			0x00100000
#घोषणा EMAC_ISR_BFCS			0x00080000
#घोषणा EMAC_ISR_PTLE			0x00040000
#घोषणा EMAC_ISR_ORE			0x00020000
#घोषणा EMAC_ISR_IRE			0x00010000
#घोषणा EMAC_ISR_SQE			0x00000080
#घोषणा EMAC_ISR_TE			0x00000040
#घोषणा EMAC_ISR_MOS			0x00000002
#घोषणा EMAC_ISR_MOF			0x00000001

/* EMACx_STACR */
#घोषणा EMAC_STACR_PHYD_MASK		0xffff
#घोषणा EMAC_STACR_PHYD_SHIFT		16
#घोषणा EMAC_STACR_OC			0x00008000
#घोषणा EMAC_STACR_PHYE			0x00004000
#घोषणा EMAC_STACR_STAC_MASK		0x00003000
#घोषणा EMAC_STACR_STAC_READ		0x00001000
#घोषणा EMAC_STACR_STAC_WRITE		0x00002000
#घोषणा EMAC_STACR_OPBC_MASK		0x00000C00
#घोषणा EMAC_STACR_OPBC_50		0x00000000
#घोषणा EMAC_STACR_OPBC_66		0x00000400
#घोषणा EMAC_STACR_OPBC_83		0x00000800
#घोषणा EMAC_STACR_OPBC_100		0x00000C00
#घोषणा EMAC_STACR_OPBC(freq)		((freq) <= 50 ? EMAC_STACR_OPBC_50 : \
					 (freq) <= 66 ? EMAC_STACR_OPBC_66 : \
					 (freq) <= 83 ? EMAC_STACR_OPBC_83 : EMAC_STACR_OPBC_100)
#घोषणा EMAC_STACR_BASE(opb)		EMAC_STACR_OPBC(opb)
#घोषणा EMAC4_STACR_BASE(opb)		0x00000000
#घोषणा EMAC_STACR_PCDA_MASK		0x1f
#घोषणा EMAC_STACR_PCDA_SHIFT		5
#घोषणा EMAC_STACR_PRA_MASK		0x1f
#घोषणा EMACX_STACR_STAC_MASK		0x00003800
#घोषणा EMACX_STACR_STAC_READ		0x00001000
#घोषणा EMACX_STACR_STAC_WRITE		0x00000800
#घोषणा EMACX_STACR_STAC_IND_ADDR	0x00002000
#घोषणा EMACX_STACR_STAC_IND_READ	0x00003800
#घोषणा EMACX_STACR_STAC_IND_READINC	0x00003000
#घोषणा EMACX_STACR_STAC_IND_WRITE	0x00002800


/* EMACx_TRTR */
#घोषणा EMAC_TRTR_SHIFT_EMAC4		24
#घोषणा EMAC_TRTR_SHIFT		27

/* EMAC specअगरic TX descriptor control fields (ग_लिखो access) */
#घोषणा EMAC_TX_CTRL_GFCS		0x0200
#घोषणा EMAC_TX_CTRL_GP			0x0100
#घोषणा EMAC_TX_CTRL_ISA		0x0080
#घोषणा EMAC_TX_CTRL_RSA		0x0040
#घोषणा EMAC_TX_CTRL_IVT		0x0020
#घोषणा EMAC_TX_CTRL_RVT		0x0010
#घोषणा EMAC_TX_CTRL_TAH_CSUM		0x000e

/* EMAC specअगरic TX descriptor status fields (पढ़ो access) */
#घोषणा EMAC_TX_ST_BFCS			0x0200
#घोषणा EMAC_TX_ST_LCS			0x0080
#घोषणा EMAC_TX_ST_ED			0x0040
#घोषणा EMAC_TX_ST_EC			0x0020
#घोषणा EMAC_TX_ST_LC			0x0010
#घोषणा EMAC_TX_ST_MC			0x0008
#घोषणा EMAC_TX_ST_SC			0x0004
#घोषणा EMAC_TX_ST_UR			0x0002
#घोषणा EMAC_TX_ST_SQE			0x0001
#घोषणा EMAC_IS_BAD_TX			(EMAC_TX_ST_LCS | EMAC_TX_ST_ED | \
					 EMAC_TX_ST_EC | EMAC_TX_ST_LC | \
					 EMAC_TX_ST_MC | EMAC_TX_ST_UR)
#घोषणा EMAC_IS_BAD_TX_TAH		(EMAC_TX_ST_LCS | EMAC_TX_ST_ED | \
					 EMAC_TX_ST_EC | EMAC_TX_ST_LC)

/* EMAC specअगरic RX descriptor status fields (पढ़ो access) */
#घोषणा EMAC_RX_ST_OE			0x0200
#घोषणा EMAC_RX_ST_PP			0x0100
#घोषणा EMAC_RX_ST_BP			0x0080
#घोषणा EMAC_RX_ST_RP			0x0040
#घोषणा EMAC_RX_ST_SE			0x0020
#घोषणा EMAC_RX_ST_AE			0x0010
#घोषणा EMAC_RX_ST_BFCS			0x0008
#घोषणा EMAC_RX_ST_PTL			0x0004
#घोषणा EMAC_RX_ST_ORE			0x0002
#घोषणा EMAC_RX_ST_IRE			0x0001
#घोषणा EMAC_RX_TAH_BAD_CSUM		0x0003
#घोषणा EMAC_BAD_RX_MASK		(EMAC_RX_ST_OE | EMAC_RX_ST_BP | \
					 EMAC_RX_ST_RP | EMAC_RX_ST_SE | \
					 EMAC_RX_ST_AE | EMAC_RX_ST_BFCS | \
					 EMAC_RX_ST_PTL | EMAC_RX_ST_ORE | \
					 EMAC_RX_ST_IRE )
#पूर्ण_अगर /* __IBM_NEWEMAC_H */
