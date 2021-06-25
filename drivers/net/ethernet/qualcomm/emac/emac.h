<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _EMAC_H_
#घोषणा _EMAC_H_

#समावेश <linux/irqवापस.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "emac-mac.h"
#समावेश "emac-phy.h"
#समावेश "emac-sgmii.h"

/* EMAC base रेजिस्टर offsets */
#घोषणा EMAC_DMA_MAS_CTRL		0x1400
#घोषणा EMAC_IRQ_MOD_TIM_INIT		0x1408
#घोषणा EMAC_BLK_IDLE_STS		0x140c
#घोषणा EMAC_PHY_LINK_DELAY		0x141c
#घोषणा EMAC_SYS_ALIV_CTRL		0x1434
#घोषणा EMAC_MAC_CTRL			0x1480
#घोषणा EMAC_MAC_IPGIFG_CTRL		0x1484
#घोषणा EMAC_MAC_STA_ADDR0		0x1488
#घोषणा EMAC_MAC_STA_ADDR1		0x148c
#घोषणा EMAC_HASH_TAB_REG0		0x1490
#घोषणा EMAC_HASH_TAB_REG1		0x1494
#घोषणा EMAC_MAC_HALF_DPLX_CTRL		0x1498
#घोषणा EMAC_MAX_FRAM_LEN_CTRL		0x149c
#घोषणा EMAC_WOL_CTRL0			0x14a0
#घोषणा EMAC_RSS_KEY0			0x14b0
#घोषणा EMAC_H1TPD_BASE_ADDR_LO		0x14e0
#घोषणा EMAC_H2TPD_BASE_ADDR_LO		0x14e4
#घोषणा EMAC_H3TPD_BASE_ADDR_LO		0x14e8
#घोषणा EMAC_INTER_SRAM_PART9		0x1534
#घोषणा EMAC_DESC_CTRL_0		0x1540
#घोषणा EMAC_DESC_CTRL_1		0x1544
#घोषणा EMAC_DESC_CTRL_2		0x1550
#घोषणा EMAC_DESC_CTRL_10		0x1554
#घोषणा EMAC_DESC_CTRL_12		0x1558
#घोषणा EMAC_DESC_CTRL_13		0x155c
#घोषणा EMAC_DESC_CTRL_3		0x1560
#घोषणा EMAC_DESC_CTRL_4		0x1564
#घोषणा EMAC_DESC_CTRL_5		0x1568
#घोषणा EMAC_DESC_CTRL_14		0x156c
#घोषणा EMAC_DESC_CTRL_15		0x1570
#घोषणा EMAC_DESC_CTRL_16		0x1574
#घोषणा EMAC_DESC_CTRL_6		0x1578
#घोषणा EMAC_DESC_CTRL_8		0x1580
#घोषणा EMAC_DESC_CTRL_9		0x1584
#घोषणा EMAC_DESC_CTRL_11		0x1588
#घोषणा EMAC_TXQ_CTRL_0			0x1590
#घोषणा EMAC_TXQ_CTRL_1			0x1594
#घोषणा EMAC_TXQ_CTRL_2			0x1598
#घोषणा EMAC_RXQ_CTRL_0			0x15a0
#घोषणा EMAC_RXQ_CTRL_1			0x15a4
#घोषणा EMAC_RXQ_CTRL_2			0x15a8
#घोषणा EMAC_RXQ_CTRL_3			0x15ac
#घोषणा EMAC_BASE_CPU_NUMBER		0x15b8
#घोषणा EMAC_DMA_CTRL			0x15c0
#घोषणा EMAC_MAILBOX_0			0x15e0
#घोषणा EMAC_MAILBOX_5			0x15e4
#घोषणा EMAC_MAILBOX_6			0x15e8
#घोषणा EMAC_MAILBOX_13			0x15ec
#घोषणा EMAC_MAILBOX_2			0x15f4
#घोषणा EMAC_MAILBOX_3			0x15f8
#घोषणा EMAC_INT_STATUS			0x1600
#घोषणा EMAC_INT_MASK			0x1604
#घोषणा EMAC_MAILBOX_11			0x160c
#घोषणा EMAC_AXI_MAST_CTRL		0x1610
#घोषणा EMAC_MAILBOX_12			0x1614
#घोषणा EMAC_MAILBOX_9			0x1618
#घोषणा EMAC_MAILBOX_10			0x161c
#घोषणा EMAC_ATHR_HEADER_CTRL		0x1620
#घोषणा EMAC_RXMAC_STATC_REG0		0x1700
#घोषणा EMAC_RXMAC_STATC_REG22		0x1758
#घोषणा EMAC_TXMAC_STATC_REG0		0x1760
#घोषणा EMAC_TXMAC_STATC_REG24		0x17c0
#घोषणा EMAC_CLK_GATE_CTRL		0x1814
#घोषणा EMAC_CORE_HW_VERSION		0x1974
#घोषणा EMAC_MISC_CTRL			0x1990
#घोषणा EMAC_MAILBOX_7			0x19e0
#घोषणा EMAC_MAILBOX_8			0x19e4
#घोषणा EMAC_IDT_TABLE0			0x1b00
#घोषणा EMAC_RXMAC_STATC_REG23		0x1bc8
#घोषणा EMAC_RXMAC_STATC_REG24		0x1bcc
#घोषणा EMAC_TXMAC_STATC_REG25		0x1bd0
#घोषणा EMAC_MAILBOX_15			0x1bd4
#घोषणा EMAC_MAILBOX_16			0x1bd8
#घोषणा EMAC_INT1_MASK			0x1bf0
#घोषणा EMAC_INT1_STATUS		0x1bf4
#घोषणा EMAC_INT2_MASK			0x1bf8
#घोषणा EMAC_INT2_STATUS		0x1bfc
#घोषणा EMAC_INT3_MASK			0x1c00
#घोषणा EMAC_INT3_STATUS		0x1c04

/* EMAC_DMA_MAS_CTRL */
#घोषणा DEV_ID_NUM_BMSK                                     0x7f000000
#घोषणा DEV_ID_NUM_SHFT                                             24
#घोषणा DEV_REV_NUM_BMSK                                      0xff0000
#घोषणा DEV_REV_NUM_SHFT                                            16
#घोषणा INT_RD_CLR_EN                                           0x4000
#घोषणा IRQ_MODERATOR2_EN                                        0x800
#घोषणा IRQ_MODERATOR_EN                                         0x400
#घोषणा LPW_CLK_SEL                                               0x80
#घोषणा LPW_STATE                                                 0x20
#घोषणा LPW_MODE                                                  0x10
#घोषणा SOFT_RST                                                   0x1

/* EMAC_IRQ_MOD_TIM_INIT */
#घोषणा IRQ_MODERATOR2_INIT_BMSK                            0xffff0000
#घोषणा IRQ_MODERATOR2_INIT_SHFT                                    16
#घोषणा IRQ_MODERATOR_INIT_BMSK                                 0xffff
#घोषणा IRQ_MODERATOR_INIT_SHFT                                      0

/* EMAC_INT_STATUS */
#घोषणा DIS_INT                                                BIT(31)
#घोषणा PTP_INT                                                BIT(30)
#घोषणा RFD4_UR_INT                                            BIT(29)
#घोषणा TX_PKT_INT3                                            BIT(26)
#घोषणा TX_PKT_INT2                                            BIT(25)
#घोषणा TX_PKT_INT1                                            BIT(24)
#घोषणा RX_PKT_INT3                                            BIT(19)
#घोषणा RX_PKT_INT2                                            BIT(18)
#घोषणा RX_PKT_INT1                                            BIT(17)
#घोषणा RX_PKT_INT0                                            BIT(16)
#घोषणा TX_PKT_INT                                             BIT(15)
#घोषणा TXQ_TO_INT                                             BIT(14)
#घोषणा GPHY_WAKEUP_INT                                        BIT(13)
#घोषणा GPHY_LINK_DOWN_INT                                     BIT(12)
#घोषणा GPHY_LINK_UP_INT                                       BIT(11)
#घोषणा DMAW_TO_INT                                            BIT(10)
#घोषणा DMAR_TO_INT                                             BIT(9)
#घोषणा TXF_UR_INT                                              BIT(8)
#घोषणा RFD3_UR_INT                                             BIT(7)
#घोषणा RFD2_UR_INT                                             BIT(6)
#घोषणा RFD1_UR_INT                                             BIT(5)
#घोषणा RFD0_UR_INT                                             BIT(4)
#घोषणा RXF_OF_INT                                              BIT(3)
#घोषणा SW_MAN_INT                                              BIT(2)

/* EMAC_MAILBOX_6 */
#घोषणा RFD2_PROC_IDX_BMSK                                   0xfff0000
#घोषणा RFD2_PROC_IDX_SHFT                                          16
#घोषणा RFD2_PROD_IDX_BMSK                                       0xfff
#घोषणा RFD2_PROD_IDX_SHFT                                           0

/* EMAC_CORE_HW_VERSION */
#घोषणा MAJOR_BMSK                                          0xf0000000
#घोषणा MAJOR_SHFT                                                  28
#घोषणा MINOR_BMSK                                           0xfff0000
#घोषणा MINOR_SHFT                                                  16
#घोषणा STEP_BMSK                                               0xffff
#घोषणा STEP_SHFT                                                    0

/* EMAC_EMAC_WRAPPER_CSR1 */
#घोषणा TX_INDX_FIFO_SYNC_RST                                  BIT(23)
#घोषणा TX_TS_FIFO_SYNC_RST                                    BIT(22)
#घोषणा RX_TS_FIFO2_SYNC_RST                                   BIT(21)
#घोषणा RX_TS_FIFO1_SYNC_RST                                   BIT(20)
#घोषणा TX_TS_ENABLE                                           BIT(16)
#घोषणा DIS_1588_CLKS                                          BIT(11)
#घोषणा FREQ_MODE                                               BIT(9)
#घोषणा ENABLE_RRD_TIMESTAMP                                    BIT(3)

/* EMAC_EMAC_WRAPPER_CSR2 */
#घोषणा HDRIVE_BMSK                                             0x3000
#घोषणा HDRIVE_SHFT                                                 12
#घोषणा SLB_EN                                                  BIT(9)
#घोषणा PLB_EN                                                  BIT(8)
#घोषणा WOL_EN                                                  BIT(3)
#घोषणा PHY_RESET                                               BIT(0)

#घोषणा EMAC_DEV_ID                                             0x0040

/* SGMII v2 per lane रेजिस्टरs */
#घोषणा SGMII_LN_RSM_START             0x029C

/* SGMII v2 PHY common रेजिस्टरs */
#घोषणा SGMII_PHY_CMN_CTRL            0x0408
#घोषणा SGMII_PHY_CMN_RESET_CTRL      0x0410

/* SGMII v2 PHY रेजिस्टरs per lane */
#घोषणा SGMII_PHY_LN_OFFSET          0x0400
#घोषणा SGMII_PHY_LN_LANE_STATUS     0x00DC
#घोषणा SGMII_PHY_LN_BIST_GEN0       0x008C
#घोषणा SGMII_PHY_LN_BIST_GEN1       0x0090
#घोषणा SGMII_PHY_LN_BIST_GEN2       0x0094
#घोषणा SGMII_PHY_LN_BIST_GEN3       0x0098
#घोषणा SGMII_PHY_LN_CDR_CTRL1       0x005C

क्रमागत emac_clk_id अणु
	EMAC_CLK_AXI,
	EMAC_CLK_CFG_AHB,
	EMAC_CLK_HIGH_SPEED,
	EMAC_CLK_MDIO,
	EMAC_CLK_TX,
	EMAC_CLK_RX,
	EMAC_CLK_SYS,
	EMAC_CLK_CNT
पूर्ण;

#घोषणा EMAC_LINK_SPEED_UNKNOWN                                    0x0
#घोषणा EMAC_LINK_SPEED_10_HALF                                 BIT(0)
#घोषणा EMAC_LINK_SPEED_10_FULL                                 BIT(1)
#घोषणा EMAC_LINK_SPEED_100_HALF                                BIT(2)
#घोषणा EMAC_LINK_SPEED_100_FULL                                BIT(3)
#घोषणा EMAC_LINK_SPEED_1GB_FULL                                BIT(5)

#घोषणा EMAC_MAX_SETUP_LNK_CYCLE                                   100

काष्ठा emac_stats अणु
	/* rx */
	u64 rx_ok;              /* good packets */
	u64 rx_bcast;           /* good broadcast packets */
	u64 rx_mcast;           /* good multicast packets */
	u64 rx_छोड़ो;           /* छोड़ो packet */
	u64 rx_ctrl;            /* control packets other than छोड़ो frame. */
	u64 rx_fcs_err;         /* packets with bad FCS. */
	u64 rx_len_err;         /* packets with length mismatch */
	u64 rx_byte_cnt;        /* good bytes count (without FCS) */
	u64 rx_runt;            /* runt packets */
	u64 rx_frag;            /* fragment count */
	u64 rx_sz_64;	        /* packets that are 64 bytes */
	u64 rx_sz_65_127;       /* packets that are 65-127 bytes */
	u64 rx_sz_128_255;      /* packets that are 128-255 bytes */
	u64 rx_sz_256_511;      /* packets that are 256-511 bytes */
	u64 rx_sz_512_1023;     /* packets that are 512-1023 bytes */
	u64 rx_sz_1024_1518;    /* packets that are 1024-1518 bytes */
	u64 rx_sz_1519_max;     /* packets that are 1519-MTU bytes*/
	u64 rx_sz_ov;           /* packets that are >MTU bytes (truncated) */
	u64 rx_rxf_ov;          /* packets dropped due to RX FIFO overflow */
	u64 rx_align_err;       /* alignment errors */
	u64 rx_bcast_byte_cnt;  /* broadcast packets byte count (without FCS) */
	u64 rx_mcast_byte_cnt;  /* multicast packets byte count (without FCS) */
	u64 rx_err_addr;        /* packets dropped due to address filtering */
	u64 rx_crc_align;       /* CRC align errors */
	u64 rx_jabbers;         /* jabbers */

	/* tx */
	u64 tx_ok;              /* good packets */
	u64 tx_bcast;           /* good broadcast packets */
	u64 tx_mcast;           /* good multicast packets */
	u64 tx_छोड़ो;           /* छोड़ो packets */
	u64 tx_exc_defer;       /* packets with excessive deferral */
	u64 tx_ctrl;            /* control packets other than छोड़ो frame */
	u64 tx_defer;           /* packets that are deferred. */
	u64 tx_byte_cnt;        /* good bytes count (without FCS) */
	u64 tx_sz_64;           /* packets that are 64 bytes */
	u64 tx_sz_65_127;       /* packets that are 65-127 bytes */
	u64 tx_sz_128_255;      /* packets that are 128-255 bytes */
	u64 tx_sz_256_511;      /* packets that are 256-511 bytes */
	u64 tx_sz_512_1023;     /* packets that are 512-1023 bytes */
	u64 tx_sz_1024_1518;    /* packets that are 1024-1518 bytes */
	u64 tx_sz_1519_max;     /* packets that are 1519-MTU bytes */
	u64 tx_1_col;           /* packets single prior collision */
	u64 tx_2_col;           /* packets with multiple prior collisions */
	u64 tx_late_col;        /* packets with late collisions */
	u64 tx_पात_col;       /* packets पातed due to excess collisions */
	u64 tx_underrun;        /* packets पातed due to FIFO underrun */
	u64 tx_rd_eop;          /* count of पढ़ोs beyond EOP */
	u64 tx_len_err;         /* packets with length mismatch */
	u64 tx_trunc;           /* packets truncated due to size >MTU */
	u64 tx_bcast_byte;      /* broadcast packets byte count (without FCS) */
	u64 tx_mcast_byte;      /* multicast packets byte count (without FCS) */
	u64 tx_col;             /* collisions */

	spinlock_t lock;	/* prevent multiple simultaneous पढ़ोers */
पूर्ण;

/* RSS hstype Definitions */
#घोषणा EMAC_RSS_HSTYP_IPV4_EN				    0x00000001
#घोषणा EMAC_RSS_HSTYP_TCP4_EN				    0x00000002
#घोषणा EMAC_RSS_HSTYP_IPV6_EN				    0x00000004
#घोषणा EMAC_RSS_HSTYP_TCP6_EN				    0x00000008
#घोषणा EMAC_RSS_HSTYP_ALL_EN (\
		EMAC_RSS_HSTYP_IPV4_EN   |\
		EMAC_RSS_HSTYP_TCP4_EN   |\
		EMAC_RSS_HSTYP_IPV6_EN   |\
		EMAC_RSS_HSTYP_TCP6_EN)

#घोषणा EMAC_VLAN_TO_TAG(_vlan, _tag) \
		(_tag =  ((((_vlan) >> 8) & 0xFF) | (((_vlan) & 0xFF) << 8)))

#घोषणा EMAC_TAG_TO_VLAN(_tag, _vlan) \
		(_vlan = ((((_tag) >> 8) & 0xFF) | (((_tag) & 0xFF) << 8)))

#घोषणा EMAC_DEF_RX_BUF_SIZE					  1536
#घोषणा EMAC_MAX_JUMBO_PKT_SIZE				    (9 * 1024)
#घोषणा EMAC_MAX_TX_OFFLOAD_THRESH			    (9 * 1024)

#घोषणा EMAC_MAX_ETH_FRAME_SIZE		       EMAC_MAX_JUMBO_PKT_SIZE
#घोषणा EMAC_MIN_ETH_FRAME_SIZE					    68

#घोषणा EMAC_DEF_TX_QUEUES					     1
#घोषणा EMAC_DEF_RX_QUEUES					     1

#घोषणा EMAC_MIN_TX_DESCS					   128
#घोषणा EMAC_MIN_RX_DESCS					   128

#घोषणा EMAC_MAX_TX_DESCS					 16383
#घोषणा EMAC_MAX_RX_DESCS					  2047

#घोषणा EMAC_DEF_TX_DESCS					   512
#घोषणा EMAC_DEF_RX_DESCS					   256

#घोषणा EMAC_DEF_RX_IRQ_MOD					   250
#घोषणा EMAC_DEF_TX_IRQ_MOD					   250

#घोषणा EMAC_WATCHDOG_TIME				      (5 * HZ)

/* by शेष check link every 4 seconds */
#घोषणा EMAC_TRY_LINK_TIMEOUT				      (4 * HZ)

/* emac_irq per-device (per-adapter) irq properties.
 * @irq:	irq number.
 * @mask	mask to use over status रेजिस्टर.
 */
काष्ठा emac_irq अणु
	अचिन्हित पूर्णांक	irq;
	u32		mask;
पूर्ण;

/* The device's मुख्य data काष्ठाure */
काष्ठा emac_adapter अणु
	काष्ठा net_device		*netdev;
	काष्ठा mii_bus			*mii_bus;
	काष्ठा phy_device		*phydev;

	व्योम __iomem			*base;
	व्योम __iomem			*csr;

	काष्ठा emac_sgmii		phy;
	काष्ठा emac_stats		stats;

	काष्ठा emac_irq			irq;
	काष्ठा clk			*clk[EMAC_CLK_CNT];

	/* All Descriptor memory */
	काष्ठा emac_ring_header		ring_header;
	काष्ठा emac_tx_queue		tx_q;
	काष्ठा emac_rx_queue		rx_q;
	अचिन्हित पूर्णांक			tx_desc_cnt;
	अचिन्हित पूर्णांक			rx_desc_cnt;
	अचिन्हित पूर्णांक			rrd_size; /* in quad words */
	अचिन्हित पूर्णांक			rfd_size; /* in quad words */
	अचिन्हित पूर्णांक			tpd_size; /* in quad words */

	अचिन्हित पूर्णांक			rxbuf_size;

	/* Flow control / छोड़ो frames support. If स्वतःmatic=True, करो whatever
	 * the PHY करोes. Otherwise, use tx_flow_control and rx_flow_control.
	 */
	bool				स्वतःmatic;
	bool				tx_flow_control;
	bool				rx_flow_control;

	/* True == use single-छोड़ो-frame mode. */
	bool				single_छोड़ो_mode;

	/* Ring parameter */
	u8				tpd_burst;
	u8				rfd_burst;
	अचिन्हित पूर्णांक			dmaw_dly_cnt;
	अचिन्हित पूर्णांक			dmar_dly_cnt;
	क्रमागत emac_dma_req_block		dmar_block;
	क्रमागत emac_dma_req_block		dmaw_block;
	क्रमागत emac_dma_order		dma_order;

	u32				irq_mod;
	u32				preamble;

	काष्ठा work_काष्ठा		work_thपढ़ो;

	u16				msg_enable;

	काष्ठा mutex			reset_lock;
पूर्ण;

पूर्णांक emac_reinit_locked(काष्ठा emac_adapter *adpt);
व्योम emac_reg_update32(व्योम __iomem *addr, u32 mask, u32 val);

व्योम emac_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम emac_update_hw_stats(काष्ठा emac_adapter *adpt);

#पूर्ण_अगर /* _EMAC_H_ */
