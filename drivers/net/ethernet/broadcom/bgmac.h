<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BGMAC_H
#घोषणा _BGMAC_H

#समावेश <linux/netdevice.h>

#समावेश "unimac.h"

#घोषणा BGMAC_DEV_CTL				0x000
#घोषणा  BGMAC_DC_TSM				0x00000002
#घोषणा  BGMAC_DC_CFCO				0x00000004
#घोषणा  BGMAC_DC_RLSS				0x00000008
#घोषणा  BGMAC_DC_MROR				0x00000010
#घोषणा  BGMAC_DC_FCM_MASK			0x00000060
#घोषणा  BGMAC_DC_FCM_SHIFT			5
#घोषणा  BGMAC_DC_NAE				0x00000080
#घोषणा  BGMAC_DC_TF				0x00000100
#घोषणा  BGMAC_DC_RDS_MASK			0x00030000
#घोषणा  BGMAC_DC_RDS_SHIFT			16
#घोषणा  BGMAC_DC_TDS_MASK			0x000c0000
#घोषणा  BGMAC_DC_TDS_SHIFT			18
#घोषणा BGMAC_DEV_STATUS			0x004		/* Configuration of the पूर्णांकerface */
#घोषणा  BGMAC_DS_RBF				0x00000001
#घोषणा  BGMAC_DS_RDF				0x00000002
#घोषणा  BGMAC_DS_RIF				0x00000004
#घोषणा  BGMAC_DS_TBF				0x00000008
#घोषणा  BGMAC_DS_TDF				0x00000010
#घोषणा  BGMAC_DS_TIF				0x00000020
#घोषणा  BGMAC_DS_PO				0x00000040
#घोषणा  BGMAC_DS_MM_MASK			0x00000300	/* Mode of the पूर्णांकerface */
#घोषणा  BGMAC_DS_MM_SHIFT			8
#घोषणा BGMAC_BIST_STATUS			0x00c
#घोषणा BGMAC_INT_STATUS			0x020		/* Interrupt status */
#घोषणा  BGMAC_IS_MRO				0x00000001
#घोषणा  BGMAC_IS_MTO				0x00000002
#घोषणा  BGMAC_IS_TFD				0x00000004
#घोषणा  BGMAC_IS_LS				0x00000008
#घोषणा  BGMAC_IS_MDIO				0x00000010
#घोषणा  BGMAC_IS_MR				0x00000020
#घोषणा  BGMAC_IS_MT				0x00000040
#घोषणा  BGMAC_IS_TO				0x00000080
#घोषणा  BGMAC_IS_DESC_ERR			0x00000400	/* Descriptor error */
#घोषणा  BGMAC_IS_DATA_ERR			0x00000800	/* Data error */
#घोषणा  BGMAC_IS_DESC_PROT_ERR			0x00001000	/* Descriptor protocol error */
#घोषणा  BGMAC_IS_RX_DESC_UNDERF		0x00002000	/* Receive descriptor underflow */
#घोषणा  BGMAC_IS_RX_F_OVERF			0x00004000	/* Receive FIFO overflow */
#घोषणा  BGMAC_IS_TX_F_UNDERF			0x00008000	/* Transmit FIFO underflow */
#घोषणा  BGMAC_IS_RX				0x00010000	/* Interrupt क्रम RX queue 0 */
#घोषणा  BGMAC_IS_TX0				0x01000000	/* Interrupt क्रम TX queue 0 */
#घोषणा  BGMAC_IS_TX1				0x02000000	/* Interrupt क्रम TX queue 1 */
#घोषणा  BGMAC_IS_TX2				0x04000000	/* Interrupt क्रम TX queue 2 */
#घोषणा  BGMAC_IS_TX3				0x08000000	/* Interrupt क्रम TX queue 3 */
#घोषणा  BGMAC_IS_TX_MASK			0x0f000000
#घोषणा  BGMAC_IS_INTMASK			0x0f01fcff
#घोषणा  BGMAC_IS_ERRMASK			0x0000fc00
#घोषणा BGMAC_INT_MASK				0x024		/* Interrupt mask */
#घोषणा BGMAC_GP_TIMER				0x028
#घोषणा BGMAC_INT_RECV_LAZY			0x100
#घोषणा  BGMAC_IRL_TO_MASK			0x00ffffff
#घोषणा  BGMAC_IRL_FC_MASK			0xff000000
#घोषणा  BGMAC_IRL_FC_SHIFT			24		/* Shअगरt the number of पूर्णांकerrupts triggered per received frame */
#घोषणा BGMAC_FLOW_CTL_THRESH			0x104		/* Flow control thresholds */
#घोषणा BGMAC_WRRTHRESH				0x108
#घोषणा BGMAC_GMAC_IDLE_CNT_THRESH		0x10c
#घोषणा BGMAC_PHY_ACCESS			0x180		/* PHY access address */
#घोषणा  BGMAC_PA_DATA_MASK			0x0000ffff
#घोषणा  BGMAC_PA_ADDR_MASK			0x001f0000
#घोषणा  BGMAC_PA_ADDR_SHIFT			16
#घोषणा  BGMAC_PA_REG_MASK			0x1f000000
#घोषणा  BGMAC_PA_REG_SHIFT			24
#घोषणा  BGMAC_PA_WRITE				0x20000000
#घोषणा  BGMAC_PA_START				0x40000000
#घोषणा BGMAC_PHY_CNTL				0x188		/* PHY control address */
#घोषणा  BGMAC_PC_EPA_MASK			0x0000001f
#घोषणा  BGMAC_PC_MCT_MASK			0x007f0000
#घोषणा  BGMAC_PC_MCT_SHIFT			16
#घोषणा  BGMAC_PC_MTE				0x00800000
#घोषणा BGMAC_TXQ_CTL				0x18c
#घोषणा  BGMAC_TXQ_CTL_DBT_MASK			0x00000fff
#घोषणा  BGMAC_TXQ_CTL_DBT_SHIFT		0
#घोषणा BGMAC_RXQ_CTL				0x190
#घोषणा  BGMAC_RXQ_CTL_DBT_MASK			0x00000fff
#घोषणा  BGMAC_RXQ_CTL_DBT_SHIFT		0
#घोषणा  BGMAC_RXQ_CTL_PTE			0x00001000
#घोषणा  BGMAC_RXQ_CTL_MDP_MASK			0x3f000000
#घोषणा  BGMAC_RXQ_CTL_MDP_SHIFT		24
#घोषणा BGMAC_GPIO_SELECT			0x194
#घोषणा BGMAC_GPIO_OUTPUT_EN			0x198

/* For 0x1e0 see BCMA_CLKCTLST. Below are BGMAC specअगरic bits */
#घोषणा  BGMAC_BCMA_CLKCTLST_MISC_PLL_REQ	0x00000100
#घोषणा  BGMAC_BCMA_CLKCTLST_MISC_PLL_ST	0x01000000

#घोषणा BGMAC_HW_WAR				0x1e4
#घोषणा BGMAC_PWR_CTL				0x1e8
#घोषणा BGMAC_DMA_BASE0				0x200		/* Tx and Rx controller */
#घोषणा BGMAC_DMA_BASE1				0x240		/* Tx controller only */
#घोषणा BGMAC_DMA_BASE2				0x280		/* Tx controller only */
#घोषणा BGMAC_DMA_BASE3				0x2C0		/* Tx controller only */
#घोषणा BGMAC_TX_GOOD_OCTETS			0x300
#घोषणा BGMAC_TX_GOOD_OCTETS_HIGH		0x304
#घोषणा BGMAC_TX_GOOD_PKTS			0x308
#घोषणा BGMAC_TX_OCTETS				0x30c
#घोषणा BGMAC_TX_OCTETS_HIGH			0x310
#घोषणा BGMAC_TX_PKTS				0x314
#घोषणा BGMAC_TX_BROADCAST_PKTS			0x318
#घोषणा BGMAC_TX_MULTICAST_PKTS			0x31c
#घोषणा BGMAC_TX_LEN_64				0x320
#घोषणा BGMAC_TX_LEN_65_TO_127			0x324
#घोषणा BGMAC_TX_LEN_128_TO_255			0x328
#घोषणा BGMAC_TX_LEN_256_TO_511			0x32c
#घोषणा BGMAC_TX_LEN_512_TO_1023		0x330
#घोषणा BGMAC_TX_LEN_1024_TO_1522		0x334
#घोषणा BGMAC_TX_LEN_1523_TO_2047		0x338
#घोषणा BGMAC_TX_LEN_2048_TO_4095		0x33c
#घोषणा BGMAC_TX_LEN_4096_TO_8191		0x340
#घोषणा BGMAC_TX_LEN_8192_TO_MAX		0x344
#घोषणा BGMAC_TX_JABBER_PKTS			0x348		/* Error */
#घोषणा BGMAC_TX_OVERSIZE_PKTS			0x34c		/* Error */
#घोषणा BGMAC_TX_FRAGMENT_PKTS			0x350
#घोषणा BGMAC_TX_UNDERRUNS			0x354		/* Error */
#घोषणा BGMAC_TX_TOTAL_COLS			0x358
#घोषणा BGMAC_TX_SINGLE_COLS			0x35c
#घोषणा BGMAC_TX_MULTIPLE_COLS			0x360
#घोषणा BGMAC_TX_EXCESSIVE_COLS			0x364		/* Error */
#घोषणा BGMAC_TX_LATE_COLS			0x368		/* Error */
#घोषणा BGMAC_TX_DEFERED			0x36c
#घोषणा BGMAC_TX_CARRIER_LOST			0x370
#घोषणा BGMAC_TX_PAUSE_PKTS			0x374
#घोषणा BGMAC_TX_UNI_PKTS			0x378
#घोषणा BGMAC_TX_Q0_PKTS			0x37c
#घोषणा BGMAC_TX_Q0_OCTETS			0x380
#घोषणा BGMAC_TX_Q0_OCTETS_HIGH			0x384
#घोषणा BGMAC_TX_Q1_PKTS			0x388
#घोषणा BGMAC_TX_Q1_OCTETS			0x38c
#घोषणा BGMAC_TX_Q1_OCTETS_HIGH			0x390
#घोषणा BGMAC_TX_Q2_PKTS			0x394
#घोषणा BGMAC_TX_Q2_OCTETS			0x398
#घोषणा BGMAC_TX_Q2_OCTETS_HIGH			0x39c
#घोषणा BGMAC_TX_Q3_PKTS			0x3a0
#घोषणा BGMAC_TX_Q3_OCTETS			0x3a4
#घोषणा BGMAC_TX_Q3_OCTETS_HIGH			0x3a8
#घोषणा BGMAC_RX_GOOD_OCTETS			0x3b0
#घोषणा BGMAC_RX_GOOD_OCTETS_HIGH		0x3b4
#घोषणा BGMAC_RX_GOOD_PKTS			0x3b8
#घोषणा BGMAC_RX_OCTETS				0x3bc
#घोषणा BGMAC_RX_OCTETS_HIGH			0x3c0
#घोषणा BGMAC_RX_PKTS				0x3c4
#घोषणा BGMAC_RX_BROADCAST_PKTS			0x3c8
#घोषणा BGMAC_RX_MULTICAST_PKTS			0x3cc
#घोषणा BGMAC_RX_LEN_64				0x3d0
#घोषणा BGMAC_RX_LEN_65_TO_127			0x3d4
#घोषणा BGMAC_RX_LEN_128_TO_255			0x3d8
#घोषणा BGMAC_RX_LEN_256_TO_511			0x3dc
#घोषणा BGMAC_RX_LEN_512_TO_1023		0x3e0
#घोषणा BGMAC_RX_LEN_1024_TO_1522		0x3e4
#घोषणा BGMAC_RX_LEN_1523_TO_2047		0x3e8
#घोषणा BGMAC_RX_LEN_2048_TO_4095		0x3ec
#घोषणा BGMAC_RX_LEN_4096_TO_8191		0x3f0
#घोषणा BGMAC_RX_LEN_8192_TO_MAX		0x3f4
#घोषणा BGMAC_RX_JABBER_PKTS			0x3f8		/* Error */
#घोषणा BGMAC_RX_OVERSIZE_PKTS			0x3fc		/* Error */
#घोषणा BGMAC_RX_FRAGMENT_PKTS			0x400
#घोषणा BGMAC_RX_MISSED_PKTS			0x404		/* Error */
#घोषणा BGMAC_RX_CRC_ALIGN_ERRS			0x408		/* Error */
#घोषणा BGMAC_RX_UNDERSIZE			0x40c		/* Error */
#घोषणा BGMAC_RX_CRC_ERRS			0x410		/* Error */
#घोषणा BGMAC_RX_ALIGN_ERRS			0x414		/* Error */
#घोषणा BGMAC_RX_SYMBOL_ERRS			0x418		/* Error */
#घोषणा BGMAC_RX_PAUSE_PKTS			0x41c
#घोषणा BGMAC_RX_NONPAUSE_PKTS			0x420
#घोषणा BGMAC_RX_SACHANGES			0x424
#घोषणा BGMAC_RX_UNI_PKTS			0x428
#घोषणा BGMAC_UNIMAC				0x800

/* BCMA GMAC core specअगरic IO Control (BCMA_IOCTL) flags */
#घोषणा BGMAC_BCMA_IOCTL_SW_CLKEN		0x00000004	/* PHY Clock Enable */
#घोषणा BGMAC_BCMA_IOCTL_SW_RESET		0x00000008	/* PHY Reset */
/* The IOCTL values appear to be dअगरferent in NS, NSP, and NS2, and करो not match
 * the values directly above
 */
#घोषणा BGMAC_CLK_EN				BIT(0)
#घोषणा BGMAC_RESERVED_0			BIT(1)
#घोषणा BGMAC_SOURCE_SYNC_MODE_EN		BIT(2)
#घोषणा BGMAC_DEST_SYNC_MODE_EN			BIT(3)
#घोषणा BGMAC_TX_CLK_OUT_INVERT_EN		BIT(4)
#घोषणा BGMAC_सूचीECT_GMII_MODE			BIT(5)
#घोषणा BGMAC_CLK_250_SEL			BIT(6)
#घोषणा BGMAC_AWCACHE				(0xf << 7)
#घोषणा BGMAC_RESERVED_1			(0x1f << 11)
#घोषणा BGMAC_ARCACHE				(0xf << 16)
#घोषणा BGMAC_AWUSER				(0x3f << 20)
#घोषणा BGMAC_ARUSER				(0x3f << 26)
#घोषणा BGMAC_RESERVED				BIT(31)

/* BCMA GMAC core specअगरic IO status (BCMA_IOST) flags */
#घोषणा BGMAC_BCMA_IOST_ATTACHED		0x00000800

#घोषणा BGMAC_NUM_MIB_TX_REGS	\
		(((BGMAC_TX_Q3_OCTETS_HIGH - BGMAC_TX_GOOD_OCTETS) / 4) + 1)
#घोषणा BGMAC_NUM_MIB_RX_REGS	\
		(((BGMAC_RX_UNI_PKTS - BGMAC_RX_GOOD_OCTETS) / 4) + 1)

#घोषणा BGMAC_DMA_TX_CTL			0x00
#घोषणा  BGMAC_DMA_TX_ENABLE			0x00000001
#घोषणा  BGMAC_DMA_TX_SUSPEND			0x00000002
#घोषणा  BGMAC_DMA_TX_LOOPBACK			0x00000004
#घोषणा  BGMAC_DMA_TX_FLUSH			0x00000010
#घोषणा  BGMAC_DMA_TX_MR_MASK			0x000000C0	/* Multiple outstanding पढ़ोs */
#घोषणा  BGMAC_DMA_TX_MR_SHIFT			6
#घोषणा   BGMAC_DMA_TX_MR_1			0
#घोषणा   BGMAC_DMA_TX_MR_2			1
#घोषणा  BGMAC_DMA_TX_PARITY_DISABLE		0x00000800
#घोषणा  BGMAC_DMA_TX_ADDREXT_MASK		0x00030000
#घोषणा  BGMAC_DMA_TX_ADDREXT_SHIFT		16
#घोषणा  BGMAC_DMA_TX_BL_MASK			0x001C0000	/* BurstLen bits */
#घोषणा  BGMAC_DMA_TX_BL_SHIFT			18
#घोषणा   BGMAC_DMA_TX_BL_16			0
#घोषणा   BGMAC_DMA_TX_BL_32			1
#घोषणा   BGMAC_DMA_TX_BL_64			2
#घोषणा   BGMAC_DMA_TX_BL_128			3
#घोषणा   BGMAC_DMA_TX_BL_256			4
#घोषणा   BGMAC_DMA_TX_BL_512			5
#घोषणा   BGMAC_DMA_TX_BL_1024			6
#घोषणा  BGMAC_DMA_TX_PC_MASK			0x00E00000	/* Prefetch control */
#घोषणा  BGMAC_DMA_TX_PC_SHIFT			21
#घोषणा   BGMAC_DMA_TX_PC_0			0
#घोषणा   BGMAC_DMA_TX_PC_4			1
#घोषणा   BGMAC_DMA_TX_PC_8			2
#घोषणा   BGMAC_DMA_TX_PC_16			3
#घोषणा  BGMAC_DMA_TX_PT_MASK			0x03000000	/* Prefetch threshold */
#घोषणा  BGMAC_DMA_TX_PT_SHIFT			24
#घोषणा   BGMAC_DMA_TX_PT_1			0
#घोषणा   BGMAC_DMA_TX_PT_2			1
#घोषणा   BGMAC_DMA_TX_PT_4			2
#घोषणा   BGMAC_DMA_TX_PT_8			3
#घोषणा BGMAC_DMA_TX_INDEX			0x04
#घोषणा BGMAC_DMA_TX_RINGLO			0x08
#घोषणा BGMAC_DMA_TX_RINGHI			0x0C
#घोषणा BGMAC_DMA_TX_STATUS			0x10
#घोषणा  BGMAC_DMA_TX_STATDPTR			0x00001FFF
#घोषणा  BGMAC_DMA_TX_STAT			0xF0000000
#घोषणा   BGMAC_DMA_TX_STAT_DISABLED		0x00000000
#घोषणा   BGMAC_DMA_TX_STAT_ACTIVE		0x10000000
#घोषणा   BGMAC_DMA_TX_STAT_IDLEWAIT		0x20000000
#घोषणा   BGMAC_DMA_TX_STAT_STOPPED		0x30000000
#घोषणा   BGMAC_DMA_TX_STAT_SUSP		0x40000000
#घोषणा BGMAC_DMA_TX_ERROR			0x14
#घोषणा  BGMAC_DMA_TX_ERRDPTR			0x0001FFFF
#घोषणा  BGMAC_DMA_TX_ERR			0xF0000000
#घोषणा   BGMAC_DMA_TX_ERR_NOERR		0x00000000
#घोषणा   BGMAC_DMA_TX_ERR_PROT			0x10000000
#घोषणा   BGMAC_DMA_TX_ERR_UNDERRUN		0x20000000
#घोषणा   BGMAC_DMA_TX_ERR_TRANSFER		0x30000000
#घोषणा   BGMAC_DMA_TX_ERR_DESCREAD		0x40000000
#घोषणा   BGMAC_DMA_TX_ERR_CORE			0x50000000
#घोषणा BGMAC_DMA_RX_CTL			0x20
#घोषणा  BGMAC_DMA_RX_ENABLE			0x00000001
#घोषणा  BGMAC_DMA_RX_FRAME_OFFSET_MASK		0x000000FE
#घोषणा  BGMAC_DMA_RX_FRAME_OFFSET_SHIFT	1
#घोषणा  BGMAC_DMA_RX_सूचीECT_FIFO		0x00000100
#घोषणा  BGMAC_DMA_RX_OVERFLOW_CONT		0x00000400
#घोषणा  BGMAC_DMA_RX_PARITY_DISABLE		0x00000800
#घोषणा  BGMAC_DMA_RX_MR_MASK			0x000000C0	/* Multiple outstanding पढ़ोs */
#घोषणा  BGMAC_DMA_RX_MR_SHIFT			6
#घोषणा   BGMAC_DMA_TX_MR_1			0
#घोषणा   BGMAC_DMA_TX_MR_2			1
#घोषणा  BGMAC_DMA_RX_ADDREXT_MASK		0x00030000
#घोषणा  BGMAC_DMA_RX_ADDREXT_SHIFT		16
#घोषणा  BGMAC_DMA_RX_BL_MASK			0x001C0000	/* BurstLen bits */
#घोषणा  BGMAC_DMA_RX_BL_SHIFT			18
#घोषणा   BGMAC_DMA_RX_BL_16			0
#घोषणा   BGMAC_DMA_RX_BL_32			1
#घोषणा   BGMAC_DMA_RX_BL_64			2
#घोषणा   BGMAC_DMA_RX_BL_128			3
#घोषणा   BGMAC_DMA_RX_BL_256			4
#घोषणा   BGMAC_DMA_RX_BL_512			5
#घोषणा   BGMAC_DMA_RX_BL_1024			6
#घोषणा  BGMAC_DMA_RX_PC_MASK			0x00E00000	/* Prefetch control */
#घोषणा  BGMAC_DMA_RX_PC_SHIFT			21
#घोषणा   BGMAC_DMA_RX_PC_0			0
#घोषणा   BGMAC_DMA_RX_PC_4			1
#घोषणा   BGMAC_DMA_RX_PC_8			2
#घोषणा   BGMAC_DMA_RX_PC_16			3
#घोषणा  BGMAC_DMA_RX_PT_MASK			0x03000000	/* Prefetch threshold */
#घोषणा  BGMAC_DMA_RX_PT_SHIFT			24
#घोषणा   BGMAC_DMA_RX_PT_1			0
#घोषणा   BGMAC_DMA_RX_PT_2			1
#घोषणा   BGMAC_DMA_RX_PT_4			2
#घोषणा   BGMAC_DMA_RX_PT_8			3
#घोषणा BGMAC_DMA_RX_INDEX			0x24
#घोषणा BGMAC_DMA_RX_RINGLO			0x28
#घोषणा BGMAC_DMA_RX_RINGHI			0x2C
#घोषणा BGMAC_DMA_RX_STATUS			0x30
#घोषणा  BGMAC_DMA_RX_STATDPTR			0x00001FFF
#घोषणा  BGMAC_DMA_RX_STAT			0xF0000000
#घोषणा   BGMAC_DMA_RX_STAT_DISABLED		0x00000000
#घोषणा   BGMAC_DMA_RX_STAT_ACTIVE		0x10000000
#घोषणा   BGMAC_DMA_RX_STAT_IDLEWAIT		0x20000000
#घोषणा   BGMAC_DMA_RX_STAT_STOPPED		0x30000000
#घोषणा   BGMAC_DMA_RX_STAT_SUSP		0x40000000
#घोषणा BGMAC_DMA_RX_ERROR			0x34
#घोषणा  BGMAC_DMA_RX_ERRDPTR			0x0001FFFF
#घोषणा  BGMAC_DMA_RX_ERR			0xF0000000
#घोषणा   BGMAC_DMA_RX_ERR_NOERR		0x00000000
#घोषणा   BGMAC_DMA_RX_ERR_PROT			0x10000000
#घोषणा   BGMAC_DMA_RX_ERR_UNDERRUN		0x20000000
#घोषणा   BGMAC_DMA_RX_ERR_TRANSFER		0x30000000
#घोषणा   BGMAC_DMA_RX_ERR_DESCREAD		0x40000000
#घोषणा   BGMAC_DMA_RX_ERR_CORE			0x50000000

#घोषणा BGMAC_DESC_CTL0_EOT			0x10000000	/* End of ring */
#घोषणा BGMAC_DESC_CTL0_IOC			0x20000000	/* IRQ on complete */
#घोषणा BGMAC_DESC_CTL0_खातापूर्ण			0x40000000	/* End of frame */
#घोषणा BGMAC_DESC_CTL0_SOF			0x80000000	/* Start of frame */
#घोषणा BGMAC_DESC_CTL1_LEN			0x00003FFF

#घोषणा BGMAC_PHY_NOREGS			BRCM_PSEUDO_PHY_ADDR
#घोषणा BGMAC_PHY_MASK				0x1F

#घोषणा BGMAC_MAX_TX_RINGS			4
#घोषणा BGMAC_MAX_RX_RINGS			1

#घोषणा BGMAC_TX_RING_SLOTS			128
#घोषणा BGMAC_RX_RING_SLOTS			512

#घोषणा BGMAC_RX_HEADER_LEN			28		/* Last 24 bytes are unused. Well... */
#घोषणा BGMAC_RX_FRAME_OFFSET			30		/* There are 2 unused bytes between header and real data */
#घोषणा BGMAC_RX_BUF_OFFSET			(NET_SKB_PAD + NET_IP_ALIGN - \
						 BGMAC_RX_FRAME_OFFSET)
/* Jumbo frame size with FCS */
#घोषणा BGMAC_RX_MAX_FRAME_SIZE			9724
#घोषणा BGMAC_RX_BUF_SIZE			(BGMAC_RX_FRAME_OFFSET + BGMAC_RX_MAX_FRAME_SIZE)
#घोषणा BGMAC_RX_ALLOC_SIZE			(SKB_DATA_ALIGN(BGMAC_RX_BUF_SIZE + BGMAC_RX_BUF_OFFSET) + \
						 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

#घोषणा BGMAC_BFL_ENETROBO			0x0010		/* has ephy roboचयन spi */
#घोषणा BGMAC_BFL_ENETADM			0x0080		/* has ADMtek चयन */
#घोषणा BGMAC_BFL_ENETVLAN			0x0100		/* can करो vlan */

#घोषणा BGMAC_CHIPCTL_1_IF_TYPE_MASK		0x00000030
#घोषणा BGMAC_CHIPCTL_1_IF_TYPE_RMII		0x00000000
#घोषणा BGMAC_CHIPCTL_1_IF_TYPE_MII		0x00000010
#घोषणा BGMAC_CHIPCTL_1_IF_TYPE_RGMII		0x00000020
#घोषणा BGMAC_CHIPCTL_1_SW_TYPE_MASK		0x000000C0
#घोषणा BGMAC_CHIPCTL_1_SW_TYPE_EPHY		0x00000000
#घोषणा BGMAC_CHIPCTL_1_SW_TYPE_EPHYMII		0x00000040
#घोषणा BGMAC_CHIPCTL_1_SW_TYPE_EPHYRMII	0x00000080
#घोषणा BGMAC_CHIPCTL_1_SW_TYPE_RGMII		0x000000C0
#घोषणा BGMAC_CHIPCTL_1_RXC_DLL_BYPASS		0x00010000

#घोषणा BGMAC_CHIPCTL_4_IF_TYPE_MASK		0x00003000
#घोषणा BGMAC_CHIPCTL_4_IF_TYPE_RMII		0x00000000
#घोषणा BGMAC_CHIPCTL_4_IF_TYPE_MII		0x00001000
#घोषणा BGMAC_CHIPCTL_4_IF_TYPE_RGMII		0x00002000
#घोषणा BGMAC_CHIPCTL_4_SW_TYPE_MASK		0x0000C000
#घोषणा BGMAC_CHIPCTL_4_SW_TYPE_EPHY		0x00000000
#घोषणा BGMAC_CHIPCTL_4_SW_TYPE_EPHYMII		0x00004000
#घोषणा BGMAC_CHIPCTL_4_SW_TYPE_EPHYRMII	0x00008000
#घोषणा BGMAC_CHIPCTL_4_SW_TYPE_RGMII		0x0000C000

#घोषणा BGMAC_CHIPCTL_7_IF_TYPE_MASK		0x000000C0
#घोषणा BGMAC_CHIPCTL_7_IF_TYPE_RMII		0x00000000
#घोषणा BGMAC_CHIPCTL_7_IF_TYPE_MII		0x00000040
#घोषणा BGMAC_CHIPCTL_7_IF_TYPE_RGMII		0x00000080

#घोषणा BGMAC_WEIGHT	64

#घोषणा ETHER_MAX_LEN	(ETH_FRAME_LEN + ETH_FCS_LEN)

/* Feature Flags */
#घोषणा BGMAC_FEAT_TX_MASK_SETUP	BIT(0)
#घोषणा BGMAC_FEAT_RX_MASK_SETUP	BIT(1)
#घोषणा BGMAC_FEAT_IOST_ATTACHED	BIT(2)
#घोषणा BGMAC_FEAT_NO_RESET		BIT(3)
#घोषणा BGMAC_FEAT_MISC_PLL_REQ		BIT(4)
#घोषणा BGMAC_FEAT_SW_TYPE_PHY		BIT(5)
#घोषणा BGMAC_FEAT_SW_TYPE_EPHYRMII	BIT(6)
#घोषणा BGMAC_FEAT_SW_TYPE_RGMII	BIT(7)
#घोषणा BGMAC_FEAT_CMN_PHY_CTL		BIT(8)
#घोषणा BGMAC_FEAT_FLW_CTRL1		BIT(9)
#घोषणा BGMAC_FEAT_FLW_CTRL2		BIT(10)
#घोषणा BGMAC_FEAT_SET_RXQ_CLK		BIT(11)
#घोषणा BGMAC_FEAT_CLKCTLST		BIT(12)
#घोषणा BGMAC_FEAT_NO_CLR_MIB		BIT(13)
#घोषणा BGMAC_FEAT_FORCE_SPEED_2500	BIT(14)
#घोषणा BGMAC_FEAT_CMDCFG_SR_REV4	BIT(15)
#घोषणा BGMAC_FEAT_IRQ_ID_OOB_6		BIT(16)
#घोषणा BGMAC_FEAT_CC4_IF_SW_TYPE	BIT(17)
#घोषणा BGMAC_FEAT_CC4_IF_SW_TYPE_RGMII	BIT(18)
#घोषणा BGMAC_FEAT_CC7_IF_TYPE_RGMII	BIT(19)
#घोषणा BGMAC_FEAT_IDM_MASK		BIT(20)

काष्ठा bgmac_slot_info अणु
	जोड़ अणु
		काष्ठा sk_buff *skb;
		व्योम *buf;
	पूर्ण;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा bgmac_dma_desc अणु
	__le32 ctl0;
	__le32 ctl1;
	__le32 addr_low;
	__le32 addr_high;
पूर्ण __packed;

क्रमागत bgmac_dma_ring_type अणु
	BGMAC_DMA_RING_TX,
	BGMAC_DMA_RING_RX,
पूर्ण;

/**
 * bgmac_dma_ring - contains info about DMA ring (either TX or RX one)
 * @start: index of the first slot containing data
 * @end: index of a slot that can *not* be पढ़ो (yet)
 *
 * Be really aware of the specअगरic @end meaning. It's an index of a slot *after*
 * the one containing data that can be पढ़ो. If @start equals @end the ring is
 * empty.
 */
काष्ठा bgmac_dma_ring अणु
	u32 start;
	u32 end;

	काष्ठा bgmac_dma_desc *cpu_base;
	dma_addr_t dma_base;
	u32 index_base; /* Used क्रम unaligned rings only, otherwise 0 */
	u16 mmio_base;
	bool unaligned;

	काष्ठा bgmac_slot_info slots[BGMAC_RX_RING_SLOTS];
पूर्ण;

काष्ठा bgmac_rx_header अणु
	__le16 len;
	__le16 flags;
	__le16 pad[12];
पूर्ण;

काष्ठा bgmac अणु
	जोड़ अणु
		काष्ठा अणु
			व्योम __iomem *base;
			व्योम __iomem *idm_base;
			व्योम __iomem *nicpm_base;
		पूर्ण plat;
		काष्ठा अणु
			काष्ठा bcma_device *core;
			/* Reference to CMN core क्रम BCM4706 */
			काष्ठा bcma_device *cmn;
		पूर्ण bcma;
	पूर्ण;

	काष्ठा device *dev;
	काष्ठा device *dma_dev;
	u32 feature_flags;

	काष्ठा net_device *net_dev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा mii_bus *mii_bus;

	/* DMA */
	काष्ठा bgmac_dma_ring tx_ring[BGMAC_MAX_TX_RINGS];
	काष्ठा bgmac_dma_ring rx_ring[BGMAC_MAX_RX_RINGS];

	/* Stats */
	bool stats_grabbed;
	u32 mib_tx_regs[BGMAC_NUM_MIB_TX_REGS];
	u32 mib_rx_regs[BGMAC_NUM_MIB_RX_REGS];

	/* Int */
	पूर्णांक irq;
	u32 पूर्णांक_mask;

	/* Current MAC state */
	पूर्णांक mac_speed;
	पूर्णांक mac_duplex;

	u8 phyaddr;
	bool has_robosw;

	bool loopback;

	u32 (*पढ़ो)(काष्ठा bgmac *bgmac, u16 offset);
	व्योम (*ग_लिखो)(काष्ठा bgmac *bgmac, u16 offset, u32 value);
	u32 (*idm_पढ़ो)(काष्ठा bgmac *bgmac, u16 offset);
	व्योम (*idm_ग_लिखो)(काष्ठा bgmac *bgmac, u16 offset, u32 value);
	bool (*clk_enabled)(काष्ठा bgmac *bgmac);
	व्योम (*clk_enable)(काष्ठा bgmac *bgmac, u32 flags);
	व्योम (*cco_ctl_maskset)(काष्ठा bgmac *bgmac, u32 offset, u32 mask,
				u32 set);
	u32 (*get_bus_घड़ी)(काष्ठा bgmac *bgmac);
	व्योम (*cmn_maskset32)(काष्ठा bgmac *bgmac, u16 offset, u32 mask,
			      u32 set);
	पूर्णांक (*phy_connect)(काष्ठा bgmac *bgmac);
पूर्ण;

काष्ठा bgmac *bgmac_alloc(काष्ठा device *dev);
पूर्णांक bgmac_enet_probe(काष्ठा bgmac *bgmac);
व्योम bgmac_enet_हटाओ(काष्ठा bgmac *bgmac);
व्योम bgmac_adjust_link(काष्ठा net_device *net_dev);
पूर्णांक bgmac_phy_connect_direct(काष्ठा bgmac *bgmac);
पूर्णांक bgmac_enet_suspend(काष्ठा bgmac *bgmac);
पूर्णांक bgmac_enet_resume(काष्ठा bgmac *bgmac);

काष्ठा mii_bus *bcma_mdio_mii_रेजिस्टर(काष्ठा bgmac *bgmac);
व्योम bcma_mdio_mii_unरेजिस्टर(काष्ठा mii_bus *mii_bus);

अटल अंतरभूत u32 bgmac_पढ़ो(काष्ठा bgmac *bgmac, u16 offset)
अणु
	वापस bgmac->पढ़ो(bgmac, offset);
पूर्ण

अटल अंतरभूत व्योम bgmac_ग_लिखो(काष्ठा bgmac *bgmac, u16 offset, u32 value)
अणु
	bgmac->ग_लिखो(bgmac, offset, value);
पूर्ण

अटल अंतरभूत u32 bgmac_umac_पढ़ो(काष्ठा bgmac *bgmac, u16 offset)
अणु
	वापस bgmac_पढ़ो(bgmac, BGMAC_UNIMAC + offset);
पूर्ण

अटल अंतरभूत व्योम bgmac_umac_ग_लिखो(काष्ठा bgmac *bgmac, u16 offset, u32 value)
अणु
	bgmac_ग_लिखो(bgmac, BGMAC_UNIMAC + offset, value);
पूर्ण

अटल अंतरभूत u32 bgmac_idm_पढ़ो(काष्ठा bgmac *bgmac, u16 offset)
अणु
	वापस bgmac->idm_पढ़ो(bgmac, offset);
पूर्ण

अटल अंतरभूत व्योम bgmac_idm_ग_लिखो(काष्ठा bgmac *bgmac, u16 offset, u32 value)
अणु
	bgmac->idm_ग_लिखो(bgmac, offset, value);
पूर्ण

अटल अंतरभूत bool bgmac_clk_enabled(काष्ठा bgmac *bgmac)
अणु
	वापस bgmac->clk_enabled(bgmac);
पूर्ण

अटल अंतरभूत व्योम bgmac_clk_enable(काष्ठा bgmac *bgmac, u32 flags)
अणु
	bgmac->clk_enable(bgmac, flags);
पूर्ण

अटल अंतरभूत व्योम bgmac_cco_ctl_maskset(काष्ठा bgmac *bgmac, u32 offset,
					 u32 mask, u32 set)
अणु
	bgmac->cco_ctl_maskset(bgmac, offset, mask, set);
पूर्ण

अटल अंतरभूत u32 bgmac_get_bus_घड़ी(काष्ठा bgmac *bgmac)
अणु
	वापस bgmac->get_bus_घड़ी(bgmac);
पूर्ण

अटल अंतरभूत व्योम bgmac_cmn_maskset32(काष्ठा bgmac *bgmac, u16 offset,
				       u32 mask, u32 set)
अणु
	bgmac->cmn_maskset32(bgmac, offset, mask, set);
पूर्ण

अटल अंतरभूत व्योम bgmac_maskset(काष्ठा bgmac *bgmac, u16 offset, u32 mask,
				   u32 set)
अणु
	bgmac_ग_लिखो(bgmac, offset, (bgmac_पढ़ो(bgmac, offset) & mask) | set);
पूर्ण

अटल अंतरभूत व्योम bgmac_mask(काष्ठा bgmac *bgmac, u16 offset, u32 mask)
अणु
	bgmac_maskset(bgmac, offset, mask, 0);
पूर्ण

अटल अंतरभूत व्योम bgmac_set(काष्ठा bgmac *bgmac, u16 offset, u32 set)
अणु
	bgmac_maskset(bgmac, offset, ~0, set);
पूर्ण

अटल अंतरभूत व्योम bgmac_umac_maskset(काष्ठा bgmac *bgmac, u16 offset, u32 mask, u32 set)
अणु
	bgmac_maskset(bgmac, BGMAC_UNIMAC + offset, mask, set);
पूर्ण

अटल अंतरभूत पूर्णांक bgmac_phy_connect(काष्ठा bgmac *bgmac)
अणु
	वापस bgmac->phy_connect(bgmac);
पूर्ण
#पूर्ण_अगर /* _BGMAC_H */
