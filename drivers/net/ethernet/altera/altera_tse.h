<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Altera Triple-Speed Ethernet MAC driver
 * Copyright (C) 2008-2014 Altera Corporation. All rights reserved
 *
 * Contributors:
 *   Dalon Westergreen
 *   Thomas Chou
 *   Ian Abbott
 *   Yuriy Kozlov
 *   Tobias Klauser
 *   Andriy Smolskyy
 *   Roman Bulgakov
 *   Dmytro Mytarchuk
 *   Matthew Gerlach
 *
 * Original driver contributed by SLS.
 * Major updates contributed by GlobalLogic
 */

#अगर_अघोषित __ALTERA_TSE_H__
#घोषणा __ALTERA_TSE_H__

#घोषणा ALTERA_TSE_RESOURCE_NAME	"altera_tse"

#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>

#घोषणा ALTERA_TSE_SW_RESET_WATCHDOG_CNTR	10000
#घोषणा ALTERA_TSE_MAC_FIFO_WIDTH		4	/* TX/RX FIFO width in
							 * bytes
							 */
/* Rx FIFO शेष settings */
#घोषणा ALTERA_TSE_RX_SECTION_EMPTY	16
#घोषणा ALTERA_TSE_RX_SECTION_FULL	0
#घोषणा ALTERA_TSE_RX_ALMOST_EMPTY	8
#घोषणा ALTERA_TSE_RX_ALMOST_FULL	8

/* Tx FIFO शेष settings */
#घोषणा ALTERA_TSE_TX_SECTION_EMPTY	16
#घोषणा ALTERA_TSE_TX_SECTION_FULL	0
#घोषणा ALTERA_TSE_TX_ALMOST_EMPTY	8
#घोषणा ALTERA_TSE_TX_ALMOST_FULL	3

/* MAC function configuration शेष settings */
#घोषणा ALTERA_TSE_TX_IPG_LENGTH	12

#घोषणा ALTERA_TSE_PAUSE_QUANTA		0xffff

#घोषणा GET_BIT_VALUE(v, bit)		(((v) >> (bit)) & 0x1)

/* MAC Command_Config Register Bit Definitions
 */
#घोषणा MAC_CMDCFG_TX_ENA			BIT(0)
#घोषणा MAC_CMDCFG_RX_ENA			BIT(1)
#घोषणा MAC_CMDCFG_XON_GEN			BIT(2)
#घोषणा MAC_CMDCFG_ETH_SPEED			BIT(3)
#घोषणा MAC_CMDCFG_PROMIS_EN			BIT(4)
#घोषणा MAC_CMDCFG_PAD_EN			BIT(5)
#घोषणा MAC_CMDCFG_CRC_FWD			BIT(6)
#घोषणा MAC_CMDCFG_PAUSE_FWD			BIT(7)
#घोषणा MAC_CMDCFG_PAUSE_IGNORE			BIT(8)
#घोषणा MAC_CMDCFG_TX_ADDR_INS			BIT(9)
#घोषणा MAC_CMDCFG_HD_ENA			BIT(10)
#घोषणा MAC_CMDCFG_EXCESS_COL			BIT(11)
#घोषणा MAC_CMDCFG_LATE_COL			BIT(12)
#घोषणा MAC_CMDCFG_SW_RESET			BIT(13)
#घोषणा MAC_CMDCFG_MHASH_SEL			BIT(14)
#घोषणा MAC_CMDCFG_LOOP_ENA			BIT(15)
#घोषणा MAC_CMDCFG_TX_ADDR_SEL(v)		(((v) & 0x7) << 16)
#घोषणा MAC_CMDCFG_MAGIC_ENA			BIT(19)
#घोषणा MAC_CMDCFG_SLEEP			BIT(20)
#घोषणा MAC_CMDCFG_WAKEUP			BIT(21)
#घोषणा MAC_CMDCFG_XOFF_GEN			BIT(22)
#घोषणा MAC_CMDCFG_CNTL_FRM_ENA			BIT(23)
#घोषणा MAC_CMDCFG_NO_LGTH_CHECK		BIT(24)
#घोषणा MAC_CMDCFG_ENA_10			BIT(25)
#घोषणा MAC_CMDCFG_RX_ERR_DISC			BIT(26)
#घोषणा MAC_CMDCFG_DISABLE_READ_TIMEOUT		BIT(27)
#घोषणा MAC_CMDCFG_CNT_RESET			BIT(31)

#घोषणा MAC_CMDCFG_TX_ENA_GET(v)		GET_BIT_VALUE(v, 0)
#घोषणा MAC_CMDCFG_RX_ENA_GET(v)		GET_BIT_VALUE(v, 1)
#घोषणा MAC_CMDCFG_XON_GEN_GET(v)		GET_BIT_VALUE(v, 2)
#घोषणा MAC_CMDCFG_ETH_SPEED_GET(v)		GET_BIT_VALUE(v, 3)
#घोषणा MAC_CMDCFG_PROMIS_EN_GET(v)		GET_BIT_VALUE(v, 4)
#घोषणा MAC_CMDCFG_PAD_EN_GET(v)		GET_BIT_VALUE(v, 5)
#घोषणा MAC_CMDCFG_CRC_FWD_GET(v)		GET_BIT_VALUE(v, 6)
#घोषणा MAC_CMDCFG_PAUSE_FWD_GET(v)		GET_BIT_VALUE(v, 7)
#घोषणा MAC_CMDCFG_PAUSE_IGNORE_GET(v)		GET_BIT_VALUE(v, 8)
#घोषणा MAC_CMDCFG_TX_ADDR_INS_GET(v)		GET_BIT_VALUE(v, 9)
#घोषणा MAC_CMDCFG_HD_ENA_GET(v)		GET_BIT_VALUE(v, 10)
#घोषणा MAC_CMDCFG_EXCESS_COL_GET(v)		GET_BIT_VALUE(v, 11)
#घोषणा MAC_CMDCFG_LATE_COL_GET(v)		GET_BIT_VALUE(v, 12)
#घोषणा MAC_CMDCFG_SW_RESET_GET(v)		GET_BIT_VALUE(v, 13)
#घोषणा MAC_CMDCFG_MHASH_SEL_GET(v)		GET_BIT_VALUE(v, 14)
#घोषणा MAC_CMDCFG_LOOP_ENA_GET(v)		GET_BIT_VALUE(v, 15)
#घोषणा MAC_CMDCFG_TX_ADDR_SEL_GET(v)		(((v) >> 16) & 0x7)
#घोषणा MAC_CMDCFG_MAGIC_ENA_GET(v)		GET_BIT_VALUE(v, 19)
#घोषणा MAC_CMDCFG_SLEEP_GET(v)			GET_BIT_VALUE(v, 20)
#घोषणा MAC_CMDCFG_WAKEUP_GET(v)		GET_BIT_VALUE(v, 21)
#घोषणा MAC_CMDCFG_XOFF_GEN_GET(v)		GET_BIT_VALUE(v, 22)
#घोषणा MAC_CMDCFG_CNTL_FRM_ENA_GET(v)		GET_BIT_VALUE(v, 23)
#घोषणा MAC_CMDCFG_NO_LGTH_CHECK_GET(v)		GET_BIT_VALUE(v, 24)
#घोषणा MAC_CMDCFG_ENA_10_GET(v)		GET_BIT_VALUE(v, 25)
#घोषणा MAC_CMDCFG_RX_ERR_DISC_GET(v)		GET_BIT_VALUE(v, 26)
#घोषणा MAC_CMDCFG_DISABLE_READ_TIMEOUT_GET(v)	GET_BIT_VALUE(v, 27)
#घोषणा MAC_CMDCFG_CNT_RESET_GET(v)		GET_BIT_VALUE(v, 31)

/* SGMII PCS रेजिस्टर addresses
 */
#घोषणा SGMII_PCS_SCRATCH	0x10
#घोषणा SGMII_PCS_REV		0x11
#घोषणा SGMII_PCS_LINK_TIMER_0	0x12
#घोषणा SGMII_PCS_LINK_TIMER_1	0x13
#घोषणा SGMII_PCS_IF_MODE	0x14
#घोषणा SGMII_PCS_DIS_READ_TO	0x15
#घोषणा SGMII_PCS_READ_TO	0x16
#घोषणा SGMII_PCS_SW_RESET_TIMEOUT 100 /* usecs */

/* MDIO रेजिस्टरs within MAC रेजिस्टर Space
 */
काष्ठा altera_tse_mdio अणु
	u32 control;	/* PHY device operation control रेजिस्टर */
	u32 status;	/* PHY device operation status रेजिस्टर */
	u32 phy_id1;	/* Bits 31:16 of PHY identअगरier */
	u32 phy_id2;	/* Bits 15:0 of PHY identअगरier */
	u32 स्वतः_negotiation_advertisement;	/* Auto-negotiation
							 * advertisement
							 * रेजिस्टर
							 */
	u32 remote_partner_base_page_ability;

	u32 reg6;
	u32 reg7;
	u32 reg8;
	u32 reg9;
	u32 rega;
	u32 regb;
	u32 regc;
	u32 regd;
	u32 rege;
	u32 regf;
	u32 reg10;
	u32 reg11;
	u32 reg12;
	u32 reg13;
	u32 reg14;
	u32 reg15;
	u32 reg16;
	u32 reg17;
	u32 reg18;
	u32 reg19;
	u32 reg1a;
	u32 reg1b;
	u32 reg1c;
	u32 reg1d;
	u32 reg1e;
	u32 reg1f;
पूर्ण;

/* MAC रेजिस्टर Space. Note that some of these रेजिस्टरs may or may not be
 * present depending upon options chosen by the user when the core was
 * configured and built. Please consult the Altera Triple Speed Ethernet User
 * Guide क्रम details.
 */
काष्ठा altera_tse_mac अणु
	/* Bits 15:0: MegaCore function revision (0x0800). Bit 31:16: Customer
	 * specअगरic revision
	 */
	u32 megacore_revision;
	/* Provides a memory location क्रम user applications to test the device
	 * memory operation.
	 */
	u32 scratch_pad;
	/* The host processor uses this रेजिस्टर to control and configure the
	 * MAC block
	 */
	u32 command_config;
	/* 32-bit primary MAC address word 0 bits 0 to 31 of the primary
	 * MAC address
	 */
	u32 mac_addr_0;
	/* 32-bit primary MAC address word 1 bits 32 to 47 of the primary
	 * MAC address
	 */
	u32 mac_addr_1;
	/* 14-bit maximum frame length. The MAC receive logic */
	u32 frm_length;
	/* The छोड़ो quanta is used in each छोड़ो frame sent to a remote
	 * Ethernet device, in increments of 512 Ethernet bit बार
	 */
	u32 छोड़ो_quanta;
	/* 12-bit receive FIFO section-empty threshold */
	u32 rx_section_empty;
	/* 12-bit receive FIFO section-full threshold */
	u32 rx_section_full;
	/* 12-bit transmit FIFO section-empty threshold */
	u32 tx_section_empty;
	/* 12-bit transmit FIFO section-full threshold */
	u32 tx_section_full;
	/* 12-bit receive FIFO almost-empty threshold */
	u32 rx_almost_empty;
	/* 12-bit receive FIFO almost-full threshold */
	u32 rx_almost_full;
	/* 12-bit transmit FIFO almost-empty threshold */
	u32 tx_almost_empty;
	/* 12-bit transmit FIFO almost-full threshold */
	u32 tx_almost_full;
	/* MDIO address of PHY Device 0. Bits 0 to 4 hold a 5-bit PHY address */
	u32 mdio_phy0_addr;
	/* MDIO address of PHY Device 1. Bits 0 to 4 hold a 5-bit PHY address */
	u32 mdio_phy1_addr;

	/* Bit[15:0]ै 16-bit holकरोff quanta */
	u32 holकरोff_quant;

	/* only अगर 100/1000 BaseX PCS, reserved otherwise */
	u32 reserved1[5];

	/* Minimum IPG between consecutive transmit frame in terms of bytes */
	u32 tx_ipg_length;

	/* IEEE 802.3 oEntity Managed Object Support */

	/* The MAC addresses */
	u32 mac_id_1;
	u32 mac_id_2;

	/* Number of frames transmitted without error including छोड़ो frames */
	u32 frames_transmitted_ok;
	/* Number of frames received without error including छोड़ो frames */
	u32 frames_received_ok;
	/* Number of frames received with a CRC error */
	u32 frames_check_sequence_errors;
	/* Frame received with an alignment error */
	u32 alignment_errors;
	/* Sum of payload and padding octets of frames transmitted without
	 * error
	 */
	u32 octets_transmitted_ok;
	/* Sum of payload and padding octets of frames received without error */
	u32 octets_received_ok;

	/* IEEE 802.3 oPausedEntity Managed Object Support */

	/* Number of transmitted छोड़ो frames */
	u32 tx_छोड़ो_mac_ctrl_frames;
	/* Number of Received छोड़ो frames */
	u32 rx_छोड़ो_mac_ctrl_frames;

	/* IETF MIB (MIB-II) Object Support */

	/* Number of frames received with error */
	u32 अगर_in_errors;
	/* Number of frames transmitted with error */
	u32 अगर_out_errors;
	/* Number of valid received unicast frames */
	u32 अगर_in_ucast_pkts;
	/* Number of valid received multicasts frames (without छोड़ो) */
	u32 अगर_in_multicast_pkts;
	/* Number of valid received broadcast frames */
	u32 अगर_in_broadcast_pkts;
	u32 अगर_out_discards;
	/* The number of valid unicast frames transmitted */
	u32 अगर_out_ucast_pkts;
	/* The number of valid multicast frames transmitted,
	 * excluding छोड़ो frames
	 */
	u32 अगर_out_multicast_pkts;
	u32 अगर_out_broadcast_pkts;

	/* IETF RMON MIB Object Support */

	/* Counts the number of dropped packets due to पूर्णांकernal errors
	 * of the MAC client.
	 */
	u32 ether_stats_drop_events;
	/* Total number of bytes received. Good and bad frames. */
	u32 ether_stats_octets;
	/* Total number of packets received. Counts good and bad packets. */
	u32 ether_stats_pkts;
	/* Number of packets received with less than 64 bytes. */
	u32 ether_stats_undersize_pkts;
	/* The number of frames received that are दीर्घer than the
	 * value configured in the frm_length रेजिस्टर
	 */
	u32 ether_stats_oversize_pkts;
	/* Number of received packet with 64 bytes */
	u32 ether_stats_pkts_64_octets;
	/* Frames (good and bad) with 65 to 127 bytes */
	u32 ether_stats_pkts_65to127_octets;
	/* Frames (good and bad) with 128 to 255 bytes */
	u32 ether_stats_pkts_128to255_octets;
	/* Frames (good and bad) with 256 to 511 bytes */
	u32 ether_stats_pkts_256to511_octets;
	/* Frames (good and bad) with 512 to 1023 bytes */
	u32 ether_stats_pkts_512to1023_octets;
	/* Frames (good and bad) with 1024 to 1518 bytes */
	u32 ether_stats_pkts_1024to1518_octets;

	/* Any frame length from 1519 to the maximum length configured in the
	 * frm_length रेजिस्टर, अगर it is greater than 1518
	 */
	u32 ether_stats_pkts_1519tox_octets;
	/* Too दीर्घ frames with CRC error */
	u32 ether_stats_jabbers;
	/* Too लघु frames with CRC error */
	u32 ether_stats_fragments;

	u32 reserved2;

	/* FIFO control रेजिस्टर */
	u32 tx_cmd_stat;
	u32 rx_cmd_stat;

	/* Extended Statistics Counters */
	u32 msb_octets_transmitted_ok;
	u32 msb_octets_received_ok;
	u32 msb_ether_stats_octets;

	u32 reserved3;

	/* Multicast address resolution table, mapped in the controller address
	 * space
	 */
	u32 hash_table[64];

	/* Registers 0 to 31 within PHY device 0/1 connected to the MDIO PHY
	 * management पूर्णांकerface
	 */
	काष्ठा altera_tse_mdio mdio_phy0;
	काष्ठा altera_tse_mdio mdio_phy1;

	/* 4 Supplemental MAC Addresses */
	u32 supp_mac_addr_0_0;
	u32 supp_mac_addr_0_1;
	u32 supp_mac_addr_1_0;
	u32 supp_mac_addr_1_1;
	u32 supp_mac_addr_2_0;
	u32 supp_mac_addr_2_1;
	u32 supp_mac_addr_3_0;
	u32 supp_mac_addr_3_1;

	u32 reserved4[8];

	/* IEEE 1588v2 Feature */
	u32 tx_period;
	u32 tx_adjust_fns;
	u32 tx_adjust_ns;
	u32 rx_period;
	u32 rx_adjust_fns;
	u32 rx_adjust_ns;

	u32 reserved5[42];
पूर्ण;

#घोषणा tse_csroffs(a) (दुरत्व(काष्ठा altera_tse_mac, a))

/* Transmit and Receive Command Registers Bit Definitions
 */
#घोषणा ALTERA_TSE_TX_CMD_STAT_OMIT_CRC		BIT(17)
#घोषणा ALTERA_TSE_TX_CMD_STAT_TX_SHIFT16	BIT(18)
#घोषणा ALTERA_TSE_RX_CMD_STAT_RX_SHIFT16	BIT(25)

/* Wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा tse_buffer अणु
	काष्ठा list_head lh;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	u32 len;
	पूर्णांक mapped_as_page;
पूर्ण;

काष्ठा altera_tse_निजी;

#घोषणा ALTERA_DTYPE_SGDMA 1
#घोषणा ALTERA_DTYPE_MSGDMA 2

/* standard DMA पूर्णांकerface क्रम SGDMA and MSGDMA */
काष्ठा altera_dmaops अणु
	पूर्णांक altera_dtype;
	पूर्णांक dmamask;
	व्योम (*reset_dma)(काष्ठा altera_tse_निजी *);
	व्योम (*enable_txirq)(काष्ठा altera_tse_निजी *);
	व्योम (*enable_rxirq)(काष्ठा altera_tse_निजी *);
	व्योम (*disable_txirq)(काष्ठा altera_tse_निजी *);
	व्योम (*disable_rxirq)(काष्ठा altera_tse_निजी *);
	व्योम (*clear_txirq)(काष्ठा altera_tse_निजी *);
	व्योम (*clear_rxirq)(काष्ठा altera_tse_निजी *);
	पूर्णांक (*tx_buffer)(काष्ठा altera_tse_निजी *, काष्ठा tse_buffer *);
	u32 (*tx_completions)(काष्ठा altera_tse_निजी *);
	व्योम (*add_rx_desc)(काष्ठा altera_tse_निजी *, काष्ठा tse_buffer *);
	u32 (*get_rx_status)(काष्ठा altera_tse_निजी *);
	पूर्णांक (*init_dma)(काष्ठा altera_tse_निजी *);
	व्योम (*uninit_dma)(काष्ठा altera_tse_निजी *);
	व्योम (*start_rxdma)(काष्ठा altera_tse_निजी *);
पूर्ण;

/* This काष्ठाure is निजी to each device.
 */
काष्ठा altera_tse_निजी अणु
	काष्ठा net_device *dev;
	काष्ठा device *device;
	काष्ठा napi_काष्ठा napi;

	/* MAC address space */
	काष्ठा altera_tse_mac __iomem *mac_dev;

	/* TSE Revision */
	u32	revision;

	/* mSGDMA Rx Dispatcher address space */
	व्योम __iomem *rx_dma_csr;
	व्योम __iomem *rx_dma_desc;
	व्योम __iomem *rx_dma_resp;

	/* mSGDMA Tx Dispatcher address space */
	व्योम __iomem *tx_dma_csr;
	व्योम __iomem *tx_dma_desc;

	/* Rx buffers queue */
	काष्ठा tse_buffer *rx_ring;
	u32 rx_cons;
	u32 rx_prod;
	u32 rx_ring_size;
	u32 rx_dma_buf_sz;

	/* Tx ring buffer */
	काष्ठा tse_buffer *tx_ring;
	u32 tx_prod;
	u32 tx_cons;
	u32 tx_ring_size;

	/* Interrupts */
	u32 tx_irq;
	u32 rx_irq;

	/* RX/TX MAC FIFO configs */
	u32 tx_fअगरo_depth;
	u32 rx_fअगरo_depth;

	/* Hash filter settings */
	u32 hash_filter;
	u32 added_unicast;

	/* Descriptor memory info क्रम managing SGDMA */
	u32 txdescmem;
	u32 rxdescmem;
	dma_addr_t rxdescmem_busaddr;
	dma_addr_t txdescmem_busaddr;
	u32 txctrlreg;
	u32 rxctrlreg;
	dma_addr_t rxdescphys;
	dma_addr_t txdescphys;

	काष्ठा list_head txlisthd;
	काष्ठा list_head rxlisthd;

	/* MAC command_config रेजिस्टर protection */
	spinlock_t mac_cfg_lock;
	/* Tx path protection */
	spinlock_t tx_lock;
	/* Rx DMA & पूर्णांकerrupt control protection */
	spinlock_t rxdma_irq_lock;

	/* PHY */
	पूर्णांक phy_addr;		/* PHY's MDIO address, -1 क्रम स्वतःdetection */
	phy_पूर्णांकerface_t phy_अगरace;
	काष्ठा mii_bus *mdio;
	पूर्णांक oldspeed;
	पूर्णांक oldduplex;
	पूर्णांक oldlink;

	/* ethtool msglvl option */
	u32 msg_enable;

	काष्ठा altera_dmaops *dmaops;
पूर्ण;

/* Function prototypes
 */
व्योम altera_tse_set_ethtool_ops(काष्ठा net_device *);

अटल अंतरभूत
u32 csrrd32(व्योम __iomem *mac, माप_प्रकार offs)
अणु
	व्योम __iomem *paddr = (व्योम __iomem *)((uपूर्णांकptr_t)mac + offs);
	वापस पढ़ोl(paddr);
पूर्ण

अटल अंतरभूत
u16 csrrd16(व्योम __iomem *mac, माप_प्रकार offs)
अणु
	व्योम __iomem *paddr = (व्योम __iomem *)((uपूर्णांकptr_t)mac + offs);
	वापस पढ़ोw(paddr);
पूर्ण

अटल अंतरभूत
u8 csrrd8(व्योम __iomem *mac, माप_प्रकार offs)
अणु
	व्योम __iomem *paddr = (व्योम __iomem *)((uपूर्णांकptr_t)mac + offs);
	वापस पढ़ोb(paddr);
पूर्ण

अटल अंतरभूत
व्योम csrwr32(u32 val, व्योम __iomem *mac, माप_प्रकार offs)
अणु
	व्योम __iomem *paddr = (व्योम __iomem *)((uपूर्णांकptr_t)mac + offs);

	ग_लिखोl(val, paddr);
पूर्ण

अटल अंतरभूत
व्योम csrwr16(u16 val, व्योम __iomem *mac, माप_प्रकार offs)
अणु
	व्योम __iomem *paddr = (व्योम __iomem *)((uपूर्णांकptr_t)mac + offs);

	ग_लिखोw(val, paddr);
पूर्ण

अटल अंतरभूत
व्योम csrwr8(u8 val, व्योम __iomem *mac, माप_प्रकार offs)
अणु
	व्योम __iomem *paddr = (व्योम __iomem *)((uपूर्णांकptr_t)mac + offs);

	ग_लिखोb(val, paddr);
पूर्ण

#पूर्ण_अगर /* __ALTERA_TSE_H__ */
