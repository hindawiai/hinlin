<शैली गुरु>
/*
 * Driver क्रम Marvell NETA network card क्रम Armada XP and Armada 370 SoCs.
 *
 * Copyright (C) 2012 Marvell
 *
 * Rami Rosen <rosenr@marvell.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mbus.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <net/hwbm.h>
#समावेश "mvneta_bm.h"
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/tso.h>
#समावेश <net/page_pool.h>
#समावेश <linux/bpf_trace.h>

/* Registers */
#घोषणा MVNETA_RXQ_CONFIG_REG(q)                (0x1400 + ((q) << 2))
#घोषणा      MVNETA_RXQ_HW_BUF_ALLOC            BIT(0)
#घोषणा      MVNETA_RXQ_SHORT_POOL_ID_SHIFT	4
#घोषणा      MVNETA_RXQ_SHORT_POOL_ID_MASK	0x30
#घोषणा      MVNETA_RXQ_LONG_POOL_ID_SHIFT	6
#घोषणा      MVNETA_RXQ_LONG_POOL_ID_MASK	0xc0
#घोषणा      MVNETA_RXQ_PKT_OFFSET_ALL_MASK     (0xf    << 8)
#घोषणा      MVNETA_RXQ_PKT_OFFSET_MASK(offs)   ((offs) << 8)
#घोषणा MVNETA_RXQ_THRESHOLD_REG(q)             (0x14c0 + ((q) << 2))
#घोषणा      MVNETA_RXQ_NON_OCCUPIED(v)         ((v) << 16)
#घोषणा MVNETA_RXQ_BASE_ADDR_REG(q)             (0x1480 + ((q) << 2))
#घोषणा MVNETA_RXQ_SIZE_REG(q)                  (0x14a0 + ((q) << 2))
#घोषणा      MVNETA_RXQ_BUF_SIZE_SHIFT          19
#घोषणा      MVNETA_RXQ_BUF_SIZE_MASK           (0x1fff << 19)
#घोषणा MVNETA_RXQ_STATUS_REG(q)                (0x14e0 + ((q) << 2))
#घोषणा      MVNETA_RXQ_OCCUPIED_ALL_MASK       0x3fff
#घोषणा MVNETA_RXQ_STATUS_UPDATE_REG(q)         (0x1500 + ((q) << 2))
#घोषणा      MVNETA_RXQ_ADD_NON_OCCUPIED_SHIFT  16
#घोषणा      MVNETA_RXQ_ADD_NON_OCCUPIED_MAX    255
#घोषणा MVNETA_PORT_POOL_BUFFER_SZ_REG(pool)	(0x1700 + ((pool) << 2))
#घोषणा      MVNETA_PORT_POOL_BUFFER_SZ_SHIFT	3
#घोषणा      MVNETA_PORT_POOL_BUFFER_SZ_MASK	0xfff8
#घोषणा MVNETA_PORT_RX_RESET                    0x1cc0
#घोषणा      MVNETA_PORT_RX_DMA_RESET           BIT(0)
#घोषणा MVNETA_PHY_ADDR                         0x2000
#घोषणा      MVNETA_PHY_ADDR_MASK               0x1f
#घोषणा MVNETA_MBUS_RETRY                       0x2010
#घोषणा MVNETA_UNIT_INTR_CAUSE                  0x2080
#घोषणा MVNETA_UNIT_CONTROL                     0x20B0
#घोषणा      MVNETA_PHY_POLLING_ENABLE          BIT(1)
#घोषणा MVNETA_WIN_BASE(w)                      (0x2200 + ((w) << 3))
#घोषणा MVNETA_WIN_SIZE(w)                      (0x2204 + ((w) << 3))
#घोषणा MVNETA_WIN_REMAP(w)                     (0x2280 + ((w) << 2))
#घोषणा MVNETA_BASE_ADDR_ENABLE                 0x2290
#घोषणा MVNETA_ACCESS_PROTECT_ENABLE            0x2294
#घोषणा MVNETA_PORT_CONFIG                      0x2400
#घोषणा      MVNETA_UNI_PROMISC_MODE            BIT(0)
#घोषणा      MVNETA_DEF_RXQ(q)                  ((q) << 1)
#घोषणा      MVNETA_DEF_RXQ_ARP(q)              ((q) << 4)
#घोषणा      MVNETA_TX_UNSET_ERR_SUM            BIT(12)
#घोषणा      MVNETA_DEF_RXQ_TCP(q)              ((q) << 16)
#घोषणा      MVNETA_DEF_RXQ_UDP(q)              ((q) << 19)
#घोषणा      MVNETA_DEF_RXQ_BPDU(q)             ((q) << 22)
#घोषणा      MVNETA_RX_CSUM_WITH_PSEUDO_HDR     BIT(25)
#घोषणा      MVNETA_PORT_CONFIG_DEFL_VALUE(q)   (MVNETA_DEF_RXQ(q)       | \
						 MVNETA_DEF_RXQ_ARP(q)	 | \
						 MVNETA_DEF_RXQ_TCP(q)	 | \
						 MVNETA_DEF_RXQ_UDP(q)	 | \
						 MVNETA_DEF_RXQ_BPDU(q)	 | \
						 MVNETA_TX_UNSET_ERR_SUM | \
						 MVNETA_RX_CSUM_WITH_PSEUDO_HDR)
#घोषणा MVNETA_PORT_CONFIG_EXTEND                0x2404
#घोषणा MVNETA_MAC_ADDR_LOW                      0x2414
#घोषणा MVNETA_MAC_ADDR_HIGH                     0x2418
#घोषणा MVNETA_SDMA_CONFIG                       0x241c
#घोषणा      MVNETA_SDMA_BRST_SIZE_16            4
#घोषणा      MVNETA_RX_BRST_SZ_MASK(burst)       ((burst) << 1)
#घोषणा      MVNETA_RX_NO_DATA_SWAP              BIT(4)
#घोषणा      MVNETA_TX_NO_DATA_SWAP              BIT(5)
#घोषणा      MVNETA_DESC_SWAP                    BIT(6)
#घोषणा      MVNETA_TX_BRST_SZ_MASK(burst)       ((burst) << 22)
#घोषणा	MVNETA_VLAN_PRIO_TO_RXQ			 0x2440
#घोषणा      MVNETA_VLAN_PRIO_RXQ_MAP(prio, rxq) ((rxq) << ((prio) * 3))
#घोषणा MVNETA_PORT_STATUS                       0x2444
#घोषणा      MVNETA_TX_IN_PRGRS                  BIT(1)
#घोषणा      MVNETA_TX_FIFO_EMPTY                BIT(8)
#घोषणा MVNETA_RX_MIN_FRAME_SIZE                 0x247c
/* Only exists on Armada XP and Armada 370 */
#घोषणा MVNETA_SERDES_CFG			 0x24A0
#घोषणा      MVNETA_SGMII_SERDES_PROTO		 0x0cc7
#घोषणा      MVNETA_QSGMII_SERDES_PROTO		 0x0667
#घोषणा      MVNETA_HSGMII_SERDES_PROTO		 0x1107
#घोषणा MVNETA_TYPE_PRIO                         0x24bc
#घोषणा      MVNETA_FORCE_UNI                    BIT(21)
#घोषणा MVNETA_TXQ_CMD_1                         0x24e4
#घोषणा MVNETA_TXQ_CMD                           0x2448
#घोषणा      MVNETA_TXQ_DISABLE_SHIFT            8
#घोषणा      MVNETA_TXQ_ENABLE_MASK              0x000000ff
#घोषणा MVNETA_RX_DISCARD_FRAME_COUNT		 0x2484
#घोषणा MVNETA_OVERRUN_FRAME_COUNT		 0x2488
#घोषणा MVNETA_GMAC_CLOCK_DIVIDER                0x24f4
#घोषणा      MVNETA_GMAC_1MS_CLOCK_ENABLE        BIT(31)
#घोषणा MVNETA_ACC_MODE                          0x2500
#घोषणा MVNETA_BM_ADDRESS                        0x2504
#घोषणा MVNETA_CPU_MAP(cpu)                      (0x2540 + ((cpu) << 2))
#घोषणा      MVNETA_CPU_RXQ_ACCESS_ALL_MASK      0x000000ff
#घोषणा      MVNETA_CPU_TXQ_ACCESS_ALL_MASK      0x0000ff00
#घोषणा      MVNETA_CPU_RXQ_ACCESS(rxq)		 BIT(rxq)
#घोषणा      MVNETA_CPU_TXQ_ACCESS(txq)		 BIT(txq + 8)
#घोषणा MVNETA_RXQ_TIME_COAL_REG(q)              (0x2580 + ((q) << 2))

/* Exception Interrupt Port/Queue Cause रेजिस्टर
 *
 * Their behavior depend of the mapping करोne using the PCPX2Q
 * रेजिस्टरs. For a given CPU अगर the bit associated to a queue is not
 * set, then क्रम the रेजिस्टर a पढ़ो from this CPU will always वापस
 * 0 and a ग_लिखो won't करो anything
 */

#घोषणा MVNETA_INTR_NEW_CAUSE                    0x25a0
#घोषणा MVNETA_INTR_NEW_MASK                     0x25a4

/* bits  0..7  = TXQ SENT, one bit per queue.
 * bits  8..15 = RXQ OCCUP, one bit per queue.
 * bits 16..23 = RXQ FREE, one bit per queue.
 * bit  29 = OLD_REG_SUM, see old reg ?
 * bit  30 = TX_ERR_SUM, one bit क्रम 4 ports
 * bit  31 = MISC_SUM,   one bit क्रम 4 ports
 */
#घोषणा      MVNETA_TX_INTR_MASK(nr_txqs)        (((1 << nr_txqs) - 1) << 0)
#घोषणा      MVNETA_TX_INTR_MASK_ALL             (0xff << 0)
#घोषणा      MVNETA_RX_INTR_MASK(nr_rxqs)        (((1 << nr_rxqs) - 1) << 8)
#घोषणा      MVNETA_RX_INTR_MASK_ALL             (0xff << 8)
#घोषणा      MVNETA_MISCINTR_INTR_MASK           BIT(31)

#घोषणा MVNETA_INTR_OLD_CAUSE                    0x25a8
#घोषणा MVNETA_INTR_OLD_MASK                     0x25ac

/* Data Path Port/Queue Cause Register */
#घोषणा MVNETA_INTR_MISC_CAUSE                   0x25b0
#घोषणा MVNETA_INTR_MISC_MASK                    0x25b4

#घोषणा      MVNETA_CAUSE_PHY_STATUS_CHANGE      BIT(0)
#घोषणा      MVNETA_CAUSE_LINK_CHANGE            BIT(1)
#घोषणा      MVNETA_CAUSE_PTP                    BIT(4)

#घोषणा      MVNETA_CAUSE_INTERNAL_ADDR_ERR      BIT(7)
#घोषणा      MVNETA_CAUSE_RX_OVERRUN             BIT(8)
#घोषणा      MVNETA_CAUSE_RX_CRC_ERROR           BIT(9)
#घोषणा      MVNETA_CAUSE_RX_LARGE_PKT           BIT(10)
#घोषणा      MVNETA_CAUSE_TX_UNDERUN             BIT(11)
#घोषणा      MVNETA_CAUSE_PRBS_ERR               BIT(12)
#घोषणा      MVNETA_CAUSE_PSC_SYNC_CHANGE        BIT(13)
#घोषणा      MVNETA_CAUSE_SERDES_SYNC_ERR        BIT(14)

#घोषणा      MVNETA_CAUSE_BMU_ALLOC_ERR_SHIFT    16
#घोषणा      MVNETA_CAUSE_BMU_ALLOC_ERR_ALL_MASK   (0xF << MVNETA_CAUSE_BMU_ALLOC_ERR_SHIFT)
#घोषणा      MVNETA_CAUSE_BMU_ALLOC_ERR_MASK(pool) (1 << (MVNETA_CAUSE_BMU_ALLOC_ERR_SHIFT + (pool)))

#घोषणा      MVNETA_CAUSE_TXQ_ERROR_SHIFT        24
#घोषणा      MVNETA_CAUSE_TXQ_ERROR_ALL_MASK     (0xFF << MVNETA_CAUSE_TXQ_ERROR_SHIFT)
#घोषणा      MVNETA_CAUSE_TXQ_ERROR_MASK(q)      (1 << (MVNETA_CAUSE_TXQ_ERROR_SHIFT + (q)))

#घोषणा MVNETA_INTR_ENABLE                       0x25b8
#घोषणा      MVNETA_TXQ_INTR_ENABLE_ALL_MASK     0x0000ff00
#घोषणा      MVNETA_RXQ_INTR_ENABLE_ALL_MASK     0x000000ff

#घोषणा MVNETA_RXQ_CMD                           0x2680
#घोषणा      MVNETA_RXQ_DISABLE_SHIFT            8
#घोषणा      MVNETA_RXQ_ENABLE_MASK              0x000000ff
#घोषणा MVETH_TXQ_TOKEN_COUNT_REG(q)             (0x2700 + ((q) << 4))
#घोषणा MVETH_TXQ_TOKEN_CFG_REG(q)               (0x2704 + ((q) << 4))
#घोषणा MVNETA_GMAC_CTRL_0                       0x2c00
#घोषणा      MVNETA_GMAC_MAX_RX_SIZE_SHIFT       2
#घोषणा      MVNETA_GMAC_MAX_RX_SIZE_MASK        0x7ffc
#घोषणा      MVNETA_GMAC0_PORT_1000BASE_X        BIT(1)
#घोषणा      MVNETA_GMAC0_PORT_ENABLE            BIT(0)
#घोषणा MVNETA_GMAC_CTRL_2                       0x2c08
#घोषणा      MVNETA_GMAC2_INBAND_AN_ENABLE       BIT(0)
#घोषणा      MVNETA_GMAC2_PCS_ENABLE             BIT(3)
#घोषणा      MVNETA_GMAC2_PORT_RGMII             BIT(4)
#घोषणा      MVNETA_GMAC2_PORT_RESET             BIT(6)
#घोषणा MVNETA_GMAC_STATUS                       0x2c10
#घोषणा      MVNETA_GMAC_LINK_UP                 BIT(0)
#घोषणा      MVNETA_GMAC_SPEED_1000              BIT(1)
#घोषणा      MVNETA_GMAC_SPEED_100               BIT(2)
#घोषणा      MVNETA_GMAC_FULL_DUPLEX             BIT(3)
#घोषणा      MVNETA_GMAC_RX_FLOW_CTRL_ENABLE     BIT(4)
#घोषणा      MVNETA_GMAC_TX_FLOW_CTRL_ENABLE     BIT(5)
#घोषणा      MVNETA_GMAC_RX_FLOW_CTRL_ACTIVE     BIT(6)
#घोषणा      MVNETA_GMAC_TX_FLOW_CTRL_ACTIVE     BIT(7)
#घोषणा      MVNETA_GMAC_AN_COMPLETE             BIT(11)
#घोषणा      MVNETA_GMAC_SYNC_OK                 BIT(14)
#घोषणा MVNETA_GMAC_AUTONEG_CONFIG               0x2c0c
#घोषणा      MVNETA_GMAC_FORCE_LINK_DOWN         BIT(0)
#घोषणा      MVNETA_GMAC_FORCE_LINK_PASS         BIT(1)
#घोषणा      MVNETA_GMAC_INBAND_AN_ENABLE        BIT(2)
#घोषणा      MVNETA_GMAC_AN_BYPASS_ENABLE        BIT(3)
#घोषणा      MVNETA_GMAC_INBAND_RESTART_AN       BIT(4)
#घोषणा      MVNETA_GMAC_CONFIG_MII_SPEED        BIT(5)
#घोषणा      MVNETA_GMAC_CONFIG_GMII_SPEED       BIT(6)
#घोषणा      MVNETA_GMAC_AN_SPEED_EN             BIT(7)
#घोषणा      MVNETA_GMAC_CONFIG_FLOW_CTRL        BIT(8)
#घोषणा      MVNETA_GMAC_ADVERT_SYM_FLOW_CTRL    BIT(9)
#घोषणा      MVNETA_GMAC_AN_FLOW_CTRL_EN         BIT(11)
#घोषणा      MVNETA_GMAC_CONFIG_FULL_DUPLEX      BIT(12)
#घोषणा      MVNETA_GMAC_AN_DUPLEX_EN            BIT(13)
#घोषणा MVNETA_GMAC_CTRL_4                       0x2c90
#घोषणा      MVNETA_GMAC4_SHORT_PREAMBLE_ENABLE  BIT(1)
#घोषणा MVNETA_MIB_COUNTERS_BASE                 0x3000
#घोषणा      MVNETA_MIB_LATE_COLLISION           0x7c
#घोषणा MVNETA_DA_FILT_SPEC_MCAST                0x3400
#घोषणा MVNETA_DA_FILT_OTH_MCAST                 0x3500
#घोषणा MVNETA_DA_FILT_UCAST_BASE                0x3600
#घोषणा MVNETA_TXQ_BASE_ADDR_REG(q)              (0x3c00 + ((q) << 2))
#घोषणा MVNETA_TXQ_SIZE_REG(q)                   (0x3c20 + ((q) << 2))
#घोषणा      MVNETA_TXQ_SENT_THRESH_ALL_MASK     0x3fff0000
#घोषणा      MVNETA_TXQ_SENT_THRESH_MASK(coal)   ((coal) << 16)
#घोषणा MVNETA_TXQ_UPDATE_REG(q)                 (0x3c60 + ((q) << 2))
#घोषणा      MVNETA_TXQ_DEC_SENT_SHIFT           16
#घोषणा      MVNETA_TXQ_DEC_SENT_MASK            0xff
#घोषणा MVNETA_TXQ_STATUS_REG(q)                 (0x3c40 + ((q) << 2))
#घोषणा      MVNETA_TXQ_SENT_DESC_SHIFT          16
#घोषणा      MVNETA_TXQ_SENT_DESC_MASK           0x3fff0000
#घोषणा MVNETA_PORT_TX_RESET                     0x3cf0
#घोषणा      MVNETA_PORT_TX_DMA_RESET            BIT(0)
#घोषणा MVNETA_TX_MTU                            0x3e0c
#घोषणा MVNETA_TX_TOKEN_SIZE                     0x3e14
#घोषणा      MVNETA_TX_TOKEN_SIZE_MAX            0xffffffff
#घोषणा MVNETA_TXQ_TOKEN_SIZE_REG(q)             (0x3e40 + ((q) << 2))
#घोषणा      MVNETA_TXQ_TOKEN_SIZE_MAX           0x7fffffff

#घोषणा MVNETA_LPI_CTRL_0                        0x2cc0
#घोषणा MVNETA_LPI_CTRL_1                        0x2cc4
#घोषणा      MVNETA_LPI_REQUEST_ENABLE           BIT(0)
#घोषणा MVNETA_LPI_CTRL_2                        0x2cc8
#घोषणा MVNETA_LPI_STATUS                        0x2ccc

#घोषणा MVNETA_CAUSE_TXQ_SENT_DESC_ALL_MASK	 0xff

/* Descriptor ring Macros */
#घोषणा MVNETA_QUEUE_NEXT_DESC(q, index)	\
	(((index) < (q)->last_desc) ? ((index) + 1) : 0)

/* Various स्थिरants */

/* Coalescing */
#घोषणा MVNETA_TXDONE_COAL_PKTS		0	/* पूर्णांकerrupt per packet */
#घोषणा MVNETA_RX_COAL_PKTS		32
#घोषणा MVNETA_RX_COAL_USEC		100

/* The two bytes Marvell header. Either contains a special value used
 * by Marvell चयनes when a specअगरic hardware mode is enabled (not
 * supported by this driver) or is filled स्वतःmatically by zeroes on
 * the RX side. Those two bytes being at the front of the Ethernet
 * header, they allow to have the IP header aligned on a 4 bytes
 * boundary स्वतःmatically: the hardware skips those two bytes on its
 * own.
 */
#घोषणा MVNETA_MH_SIZE			2

#घोषणा MVNETA_VLAN_TAG_LEN             4

#घोषणा MVNETA_TX_CSUM_DEF_SIZE		1600
#घोषणा MVNETA_TX_CSUM_MAX_SIZE		9800
#घोषणा MVNETA_ACC_MODE_EXT1		1
#घोषणा MVNETA_ACC_MODE_EXT2		2

#घोषणा MVNETA_MAX_DECODE_WIN		6

/* Timeout स्थिरants */
#घोषणा MVNETA_TX_DISABLE_TIMEOUT_MSEC	1000
#घोषणा MVNETA_RX_DISABLE_TIMEOUT_MSEC	1000
#घोषणा MVNETA_TX_FIFO_EMPTY_TIMEOUT	10000

#घोषणा MVNETA_TX_MTU_MAX		0x3ffff

/* The RSS lookup table actually has 256 entries but we करो not use
 * them yet
 */
#घोषणा MVNETA_RSS_LU_TABLE_SIZE	1

/* Max number of Rx descriptors */
#घोषणा MVNETA_MAX_RXD 512

/* Max number of Tx descriptors */
#घोषणा MVNETA_MAX_TXD 1024

/* Max number of allowed TCP segments क्रम software TSO */
#घोषणा MVNETA_MAX_TSO_SEGS 100

#घोषणा MVNETA_MAX_SKB_DESCS (MVNETA_MAX_TSO_SEGS * 2 + MAX_SKB_FRAGS)

/* descriptor aligned size */
#घोषणा MVNETA_DESC_ALIGNED_SIZE	32

/* Number of bytes to be taken पूर्णांकo account by HW when putting incoming data
 * to the buffers. It is needed in हाल NET_SKB_PAD exceeds maximum packet
 * offset supported in MVNETA_RXQ_CONFIG_REG(q) रेजिस्टरs.
 */
#घोषणा MVNETA_RX_PKT_OFFSET_CORRECTION		64

#घोषणा MVNETA_RX_PKT_SIZE(mtu) \
	ALIGN((mtu) + MVNETA_MH_SIZE + MVNETA_VLAN_TAG_LEN + \
	      ETH_HLEN + ETH_FCS_LEN,			     \
	      cache_line_size())

/* Driver assumes that the last 3 bits are 0 */
#घोषणा MVNETA_SKB_HEADROOM	ALIGN(max(NET_SKB_PAD, XDP_PACKET_HEADROOM), 8)
#घोषणा MVNETA_SKB_PAD	(SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info) + \
			 MVNETA_SKB_HEADROOM))
#घोषणा MVNETA_MAX_RX_BUF_SIZE	(PAGE_SIZE - MVNETA_SKB_PAD)

#घोषणा IS_TSO_HEADER(txq, addr) \
	((addr >= txq->tso_hdrs_phys) && \
	 (addr < txq->tso_hdrs_phys + txq->size * TSO_HEADER_SIZE))

#घोषणा MVNETA_RX_GET_BM_POOL_ID(rxd) \
	(((rxd)->status & MVNETA_RXD_BM_POOL_MASK) >> MVNETA_RXD_BM_POOL_SHIFT)

क्रमागत अणु
	ETHTOOL_STAT_EEE_WAKEUP,
	ETHTOOL_STAT_SKB_ALLOC_ERR,
	ETHTOOL_STAT_REFILL_ERR,
	ETHTOOL_XDP_REसूचीECT,
	ETHTOOL_XDP_PASS,
	ETHTOOL_XDP_DROP,
	ETHTOOL_XDP_TX,
	ETHTOOL_XDP_TX_ERR,
	ETHTOOL_XDP_XMIT,
	ETHTOOL_XDP_XMIT_ERR,
	ETHTOOL_MAX_STATS,
पूर्ण;

काष्ठा mvneta_statistic अणु
	अचिन्हित लघु offset;
	अचिन्हित लघु type;
	स्थिर अक्षर name[ETH_GSTRING_LEN];
पूर्ण;

#घोषणा T_REG_32	32
#घोषणा T_REG_64	64
#घोषणा T_SW		1

#घोषणा MVNETA_XDP_PASS		0
#घोषणा MVNETA_XDP_DROPPED	BIT(0)
#घोषणा MVNETA_XDP_TX		BIT(1)
#घोषणा MVNETA_XDP_REसूची	BIT(2)

अटल स्थिर काष्ठा mvneta_statistic mvneta_statistics[] = अणु
	अणु 0x3000, T_REG_64, "good_octets_received", पूर्ण,
	अणु 0x3010, T_REG_32, "good_frames_received", पूर्ण,
	अणु 0x3008, T_REG_32, "bad_octets_received", पूर्ण,
	अणु 0x3014, T_REG_32, "bad_frames_received", पूर्ण,
	अणु 0x3018, T_REG_32, "broadcast_frames_received", पूर्ण,
	अणु 0x301c, T_REG_32, "multicast_frames_received", पूर्ण,
	अणु 0x3050, T_REG_32, "unrec_mac_control_received", पूर्ण,
	अणु 0x3058, T_REG_32, "good_fc_received", पूर्ण,
	अणु 0x305c, T_REG_32, "bad_fc_received", पूर्ण,
	अणु 0x3060, T_REG_32, "undersize_received", पूर्ण,
	अणु 0x3064, T_REG_32, "fragments_received", पूर्ण,
	अणु 0x3068, T_REG_32, "oversize_received", पूर्ण,
	अणु 0x306c, T_REG_32, "jabber_received", पूर्ण,
	अणु 0x3070, T_REG_32, "mac_receive_error", पूर्ण,
	अणु 0x3074, T_REG_32, "bad_crc_event", पूर्ण,
	अणु 0x3078, T_REG_32, "collision", पूर्ण,
	अणु 0x307c, T_REG_32, "late_collision", पूर्ण,
	अणु 0x2484, T_REG_32, "rx_discard", पूर्ण,
	अणु 0x2488, T_REG_32, "rx_overrun", पूर्ण,
	अणु 0x3020, T_REG_32, "frames_64_octets", पूर्ण,
	अणु 0x3024, T_REG_32, "frames_65_to_127_octets", पूर्ण,
	अणु 0x3028, T_REG_32, "frames_128_to_255_octets", पूर्ण,
	अणु 0x302c, T_REG_32, "frames_256_to_511_octets", पूर्ण,
	अणु 0x3030, T_REG_32, "frames_512_to_1023_octets", पूर्ण,
	अणु 0x3034, T_REG_32, "frames_1024_to_max_octets", पूर्ण,
	अणु 0x3038, T_REG_64, "good_octets_sent", पूर्ण,
	अणु 0x3040, T_REG_32, "good_frames_sent", पूर्ण,
	अणु 0x3044, T_REG_32, "excessive_collision", पूर्ण,
	अणु 0x3048, T_REG_32, "multicast_frames_sent", पूर्ण,
	अणु 0x304c, T_REG_32, "broadcast_frames_sent", पूर्ण,
	अणु 0x3054, T_REG_32, "fc_sent", पूर्ण,
	अणु 0x300c, T_REG_32, "internal_mac_transmit_err", पूर्ण,
	अणु ETHTOOL_STAT_EEE_WAKEUP, T_SW, "eee_wakeup_errors", पूर्ण,
	अणु ETHTOOL_STAT_SKB_ALLOC_ERR, T_SW, "skb_alloc_errors", पूर्ण,
	अणु ETHTOOL_STAT_REFILL_ERR, T_SW, "refill_errors", पूर्ण,
	अणु ETHTOOL_XDP_REसूचीECT, T_SW, "rx_xdp_redirect", पूर्ण,
	अणु ETHTOOL_XDP_PASS, T_SW, "rx_xdp_pass", पूर्ण,
	अणु ETHTOOL_XDP_DROP, T_SW, "rx_xdp_drop", पूर्ण,
	अणु ETHTOOL_XDP_TX, T_SW, "rx_xdp_tx", पूर्ण,
	अणु ETHTOOL_XDP_TX_ERR, T_SW, "rx_xdp_tx_errors", पूर्ण,
	अणु ETHTOOL_XDP_XMIT, T_SW, "tx_xdp_xmit", पूर्ण,
	अणु ETHTOOL_XDP_XMIT_ERR, T_SW, "tx_xdp_xmit_errors", पूर्ण,
पूर्ण;

काष्ठा mvneta_stats अणु
	u64	rx_packets;
	u64	rx_bytes;
	u64	tx_packets;
	u64	tx_bytes;
	/* xdp */
	u64	xdp_redirect;
	u64	xdp_pass;
	u64	xdp_drop;
	u64	xdp_xmit;
	u64	xdp_xmit_err;
	u64	xdp_tx;
	u64	xdp_tx_err;
पूर्ण;

काष्ठा mvneta_ethtool_stats अणु
	काष्ठा mvneta_stats ps;
	u64	skb_alloc_error;
	u64	refill_error;
पूर्ण;

काष्ठा mvneta_pcpu_stats अणु
	काष्ठा u64_stats_sync syncp;

	काष्ठा mvneta_ethtool_stats es;
	u64	rx_dropped;
	u64	rx_errors;
पूर्ण;

काष्ठा mvneta_pcpu_port अणु
	/* Poपूर्णांकer to the shared port */
	काष्ठा mvneta_port	*pp;

	/* Poपूर्णांकer to the CPU-local NAPI काष्ठा */
	काष्ठा napi_काष्ठा	napi;

	/* Cause of the previous पूर्णांकerrupt */
	u32			cause_rx_tx;
पूर्ण;

क्रमागत अणु
	__MVNETA_DOWN,
पूर्ण;

काष्ठा mvneta_port अणु
	u8 id;
	काष्ठा mvneta_pcpu_port __percpu	*ports;
	काष्ठा mvneta_pcpu_stats __percpu	*stats;

	अचिन्हित दीर्घ state;

	पूर्णांक pkt_size;
	व्योम __iomem *base;
	काष्ठा mvneta_rx_queue *rxqs;
	काष्ठा mvneta_tx_queue *txqs;
	काष्ठा net_device *dev;
	काष्ठा hlist_node node_online;
	काष्ठा hlist_node node_dead;
	पूर्णांक rxq_def;
	/* Protect the access to the percpu पूर्णांकerrupt रेजिस्टरs,
	 * ensuring that the configuration reमुख्यs coherent.
	 */
	spinlock_t lock;
	bool is_stopped;

	u32 cause_rx_tx;
	काष्ठा napi_काष्ठा napi;

	काष्ठा bpf_prog *xdp_prog;

	/* Core घड़ी */
	काष्ठा clk *clk;
	/* AXI घड़ी */
	काष्ठा clk *clk_bus;
	u8 mcast_count[256];
	u16 tx_ring_size;
	u16 rx_ring_size;
	u8 prio_tc_map[8];

	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	काष्ठा device_node *dn;
	अचिन्हित पूर्णांक tx_csum_limit;
	काष्ठा phylink *phylink;
	काष्ठा phylink_config phylink_config;
	काष्ठा phy *comphy;

	काष्ठा mvneta_bm *bm_priv;
	काष्ठा mvneta_bm_pool *pool_दीर्घ;
	काष्ठा mvneta_bm_pool *pool_लघु;
	पूर्णांक bm_win_id;

	bool eee_enabled;
	bool eee_active;
	bool tx_lpi_enabled;

	u64 ethtool_stats[ARRAY_SIZE(mvneta_statistics)];

	u32 indir[MVNETA_RSS_LU_TABLE_SIZE];

	/* Flags क्रम special SoC configurations */
	bool neta_armada3700;
	u16 rx_offset_correction;
	स्थिर काष्ठा mbus_dram_target_info *dram_target_info;
पूर्ण;

/* The mvneta_tx_desc and mvneta_rx_desc काष्ठाures describe the
 * layout of the transmit and reception DMA descriptors, and their
 * layout is thereक्रमe defined by the hardware design
 */

#घोषणा MVNETA_TX_L3_OFF_SHIFT	0
#घोषणा MVNETA_TX_IP_HLEN_SHIFT	8
#घोषणा MVNETA_TX_L4_UDP	BIT(16)
#घोषणा MVNETA_TX_L3_IP6	BIT(17)
#घोषणा MVNETA_TXD_IP_CSUM	BIT(18)
#घोषणा MVNETA_TXD_Z_PAD	BIT(19)
#घोषणा MVNETA_TXD_L_DESC	BIT(20)
#घोषणा MVNETA_TXD_F_DESC	BIT(21)
#घोषणा MVNETA_TXD_FLZ_DESC	(MVNETA_TXD_Z_PAD  | \
				 MVNETA_TXD_L_DESC | \
				 MVNETA_TXD_F_DESC)
#घोषणा MVNETA_TX_L4_CSUM_FULL	BIT(30)
#घोषणा MVNETA_TX_L4_CSUM_NOT	BIT(31)

#घोषणा MVNETA_RXD_ERR_CRC		0x0
#घोषणा MVNETA_RXD_BM_POOL_SHIFT	13
#घोषणा MVNETA_RXD_BM_POOL_MASK		(BIT(13) | BIT(14))
#घोषणा MVNETA_RXD_ERR_SUMMARY		BIT(16)
#घोषणा MVNETA_RXD_ERR_OVERRUN		BIT(17)
#घोषणा MVNETA_RXD_ERR_LEN		BIT(18)
#घोषणा MVNETA_RXD_ERR_RESOURCE		(BIT(17) | BIT(18))
#घोषणा MVNETA_RXD_ERR_CODE_MASK	(BIT(17) | BIT(18))
#घोषणा MVNETA_RXD_L3_IP4		BIT(25)
#घोषणा MVNETA_RXD_LAST_DESC		BIT(26)
#घोषणा MVNETA_RXD_FIRST_DESC		BIT(27)
#घोषणा MVNETA_RXD_FIRST_LAST_DESC	(MVNETA_RXD_FIRST_DESC | \
					 MVNETA_RXD_LAST_DESC)
#घोषणा MVNETA_RXD_L4_CSUM_OK		BIT(30)

#अगर defined(__LITTLE_ENDIAN)
काष्ठा mvneta_tx_desc अणु
	u32  command;		/* Options used by HW क्रम packet transmitting.*/
	u16  reserved1;		/* csum_l4 (क्रम future use)		*/
	u16  data_size;		/* Data size of transmitted packet in bytes */
	u32  buf_phys_addr;	/* Physical addr of transmitted buffer	*/
	u32  reserved2;		/* hw_cmd - (क्रम future use, PMT)	*/
	u32  reserved3[4];	/* Reserved - (क्रम future use)		*/
पूर्ण;

काष्ठा mvneta_rx_desc अणु
	u32  status;		/* Info about received packet		*/
	u16  reserved1;		/* pnc_info - (क्रम future use, PnC)	*/
	u16  data_size;		/* Size of received packet in bytes	*/

	u32  buf_phys_addr;	/* Physical address of the buffer	*/
	u32  reserved2;		/* pnc_flow_id  (क्रम future use, PnC)	*/

	u32  buf_cookie;	/* cookie क्रम access to RX buffer in rx path */
	u16  reserved3;		/* prefetch_cmd, क्रम future use		*/
	u16  reserved4;		/* csum_l4 - (क्रम future use, PnC)	*/

	u32  reserved5;		/* pnc_extra PnC (क्रम future use, PnC)	*/
	u32  reserved6;		/* hw_cmd (क्रम future use, PnC and HWF)	*/
पूर्ण;
#अन्यथा
काष्ठा mvneta_tx_desc अणु
	u16  data_size;		/* Data size of transmitted packet in bytes */
	u16  reserved1;		/* csum_l4 (क्रम future use)		*/
	u32  command;		/* Options used by HW क्रम packet transmitting.*/
	u32  reserved2;		/* hw_cmd - (क्रम future use, PMT)	*/
	u32  buf_phys_addr;	/* Physical addr of transmitted buffer	*/
	u32  reserved3[4];	/* Reserved - (क्रम future use)		*/
पूर्ण;

काष्ठा mvneta_rx_desc अणु
	u16  data_size;		/* Size of received packet in bytes	*/
	u16  reserved1;		/* pnc_info - (क्रम future use, PnC)	*/
	u32  status;		/* Info about received packet		*/

	u32  reserved2;		/* pnc_flow_id  (क्रम future use, PnC)	*/
	u32  buf_phys_addr;	/* Physical address of the buffer	*/

	u16  reserved4;		/* csum_l4 - (क्रम future use, PnC)	*/
	u16  reserved3;		/* prefetch_cmd, क्रम future use		*/
	u32  buf_cookie;	/* cookie क्रम access to RX buffer in rx path */

	u32  reserved5;		/* pnc_extra PnC (क्रम future use, PnC)	*/
	u32  reserved6;		/* hw_cmd (क्रम future use, PnC and HWF)	*/
पूर्ण;
#पूर्ण_अगर

क्रमागत mvneta_tx_buf_type अणु
	MVNETA_TYPE_SKB,
	MVNETA_TYPE_XDP_TX,
	MVNETA_TYPE_XDP_NDO,
पूर्ण;

काष्ठा mvneta_tx_buf अणु
	क्रमागत mvneta_tx_buf_type type;
	जोड़ अणु
		काष्ठा xdp_frame *xdpf;
		काष्ठा sk_buff *skb;
	पूर्ण;
पूर्ण;

काष्ठा mvneta_tx_queue अणु
	/* Number of this TX queue, in the range 0-7 */
	u8 id;

	/* Number of TX DMA descriptors in the descriptor ring */
	पूर्णांक size;

	/* Number of currently used TX DMA descriptor in the
	 * descriptor ring
	 */
	पूर्णांक count;
	पूर्णांक pending;
	पूर्णांक tx_stop_threshold;
	पूर्णांक tx_wake_threshold;

	/* Array of transmitted buffers */
	काष्ठा mvneta_tx_buf *buf;

	/* Index of last TX DMA descriptor that was inserted */
	पूर्णांक txq_put_index;

	/* Index of the TX DMA descriptor to be cleaned up */
	पूर्णांक txq_get_index;

	u32 करोne_pkts_coal;

	/* Virtual address of the TX DMA descriptors array */
	काष्ठा mvneta_tx_desc *descs;

	/* DMA address of the TX DMA descriptors array */
	dma_addr_t descs_phys;

	/* Index of the last TX DMA descriptor */
	पूर्णांक last_desc;

	/* Index of the next TX DMA descriptor to process */
	पूर्णांक next_desc_to_proc;

	/* DMA buffers क्रम TSO headers */
	अक्षर *tso_hdrs;

	/* DMA address of TSO headers */
	dma_addr_t tso_hdrs_phys;

	/* Affinity mask क्रम CPUs*/
	cpumask_t affinity_mask;
पूर्ण;

काष्ठा mvneta_rx_queue अणु
	/* rx queue number, in the range 0-7 */
	u8 id;

	/* num of rx descriptors in the rx descriptor ring */
	पूर्णांक size;

	u32 pkts_coal;
	u32 समय_coal;

	/* page_pool */
	काष्ठा page_pool *page_pool;
	काष्ठा xdp_rxq_info xdp_rxq;

	/* Virtual address of the RX buffer */
	व्योम  **buf_virt_addr;

	/* Virtual address of the RX DMA descriptors array */
	काष्ठा mvneta_rx_desc *descs;

	/* DMA address of the RX DMA descriptors array */
	dma_addr_t descs_phys;

	/* Index of the last RX DMA descriptor */
	पूर्णांक last_desc;

	/* Index of the next RX DMA descriptor to process */
	पूर्णांक next_desc_to_proc;

	/* Index of first RX DMA descriptor to refill */
	पूर्णांक first_to_refill;
	u32 refill_num;
पूर्ण;

अटल क्रमागत cpuhp_state online_hpstate;
/* The hardware supports eight (8) rx queues, but we are only allowing
 * the first one to be used. Thereक्रमe, let's just allocate one queue.
 */
अटल पूर्णांक rxq_number = 8;
अटल पूर्णांक txq_number = 8;

अटल पूर्णांक rxq_def;

अटल पूर्णांक rx_copyअवरोध __पढ़ो_mostly = 256;

/* HW BM need that each port be identअगरy by a unique ID */
अटल पूर्णांक global_port_id;

#घोषणा MVNETA_DRIVER_NAME "mvneta"
#घोषणा MVNETA_DRIVER_VERSION "1.0"

/* Utility/helper methods */

/* Write helper method */
अटल व्योम mvreg_ग_लिखो(काष्ठा mvneta_port *pp, u32 offset, u32 data)
अणु
	ग_लिखोl(data, pp->base + offset);
पूर्ण

/* Read helper method */
अटल u32 mvreg_पढ़ो(काष्ठा mvneta_port *pp, u32 offset)
अणु
	वापस पढ़ोl(pp->base + offset);
पूर्ण

/* Increment txq get counter */
अटल व्योम mvneta_txq_inc_get(काष्ठा mvneta_tx_queue *txq)
अणु
	txq->txq_get_index++;
	अगर (txq->txq_get_index == txq->size)
		txq->txq_get_index = 0;
पूर्ण

/* Increment txq put counter */
अटल व्योम mvneta_txq_inc_put(काष्ठा mvneta_tx_queue *txq)
अणु
	txq->txq_put_index++;
	अगर (txq->txq_put_index == txq->size)
		txq->txq_put_index = 0;
पूर्ण


/* Clear all MIB counters */
अटल व्योम mvneta_mib_counters_clear(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक i;

	/* Perक्रमm dummy पढ़ोs from MIB counters */
	क्रम (i = 0; i < MVNETA_MIB_LATE_COLLISION; i += 4)
		mvreg_पढ़ो(pp, (MVNETA_MIB_COUNTERS_BASE + i));
	mvreg_पढ़ो(pp, MVNETA_RX_DISCARD_FRAME_COUNT);
	mvreg_पढ़ो(pp, MVNETA_OVERRUN_FRAME_COUNT);
पूर्ण

/* Get System Network Statistics */
अटल व्योम
mvneta_get_stats64(काष्ठा net_device *dev,
		   काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	अचिन्हित पूर्णांक start;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा mvneta_pcpu_stats *cpu_stats;
		u64 rx_packets;
		u64 rx_bytes;
		u64 rx_dropped;
		u64 rx_errors;
		u64 tx_packets;
		u64 tx_bytes;

		cpu_stats = per_cpu_ptr(pp->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			rx_packets = cpu_stats->es.ps.rx_packets;
			rx_bytes   = cpu_stats->es.ps.rx_bytes;
			rx_dropped = cpu_stats->rx_dropped;
			rx_errors  = cpu_stats->rx_errors;
			tx_packets = cpu_stats->es.ps.tx_packets;
			tx_bytes   = cpu_stats->es.ps.tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		stats->rx_packets += rx_packets;
		stats->rx_bytes   += rx_bytes;
		stats->rx_dropped += rx_dropped;
		stats->rx_errors  += rx_errors;
		stats->tx_packets += tx_packets;
		stats->tx_bytes   += tx_bytes;
	पूर्ण

	stats->tx_dropped	= dev->stats.tx_dropped;
पूर्ण

/* Rx descriptors helper methods */

/* Checks whether the RX descriptor having this status is both the first
 * and the last descriptor क्रम the RX packet. Each RX packet is currently
 * received through a single RX descriptor, so not having each RX
 * descriptor with its first and last bits set is an error
 */
अटल पूर्णांक mvneta_rxq_desc_is_first_last(u32 status)
अणु
	वापस (status & MVNETA_RXD_FIRST_LAST_DESC) ==
		MVNETA_RXD_FIRST_LAST_DESC;
पूर्ण

/* Add number of descriptors पढ़ोy to receive new packets */
अटल व्योम mvneta_rxq_non_occup_desc_add(काष्ठा mvneta_port *pp,
					  काष्ठा mvneta_rx_queue *rxq,
					  पूर्णांक ndescs)
अणु
	/* Only MVNETA_RXQ_ADD_NON_OCCUPIED_MAX (255) descriptors can
	 * be added at once
	 */
	जबतक (ndescs > MVNETA_RXQ_ADD_NON_OCCUPIED_MAX) अणु
		mvreg_ग_लिखो(pp, MVNETA_RXQ_STATUS_UPDATE_REG(rxq->id),
			    (MVNETA_RXQ_ADD_NON_OCCUPIED_MAX <<
			     MVNETA_RXQ_ADD_NON_OCCUPIED_SHIFT));
		ndescs -= MVNETA_RXQ_ADD_NON_OCCUPIED_MAX;
	पूर्ण

	mvreg_ग_लिखो(pp, MVNETA_RXQ_STATUS_UPDATE_REG(rxq->id),
		    (ndescs << MVNETA_RXQ_ADD_NON_OCCUPIED_SHIFT));
पूर्ण

/* Get number of RX descriptors occupied by received packets */
अटल पूर्णांक mvneta_rxq_busy_desc_num_get(काष्ठा mvneta_port *pp,
					काष्ठा mvneta_rx_queue *rxq)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_RXQ_STATUS_REG(rxq->id));
	वापस val & MVNETA_RXQ_OCCUPIED_ALL_MASK;
पूर्ण

/* Update num of rx desc called upon वापस from rx path or
 * from mvneta_rxq_drop_pkts().
 */
अटल व्योम mvneta_rxq_desc_num_update(काष्ठा mvneta_port *pp,
				       काष्ठा mvneta_rx_queue *rxq,
				       पूर्णांक rx_करोne, पूर्णांक rx_filled)
अणु
	u32 val;

	अगर ((rx_करोne <= 0xff) && (rx_filled <= 0xff)) अणु
		val = rx_करोne |
		  (rx_filled << MVNETA_RXQ_ADD_NON_OCCUPIED_SHIFT);
		mvreg_ग_लिखो(pp, MVNETA_RXQ_STATUS_UPDATE_REG(rxq->id), val);
		वापस;
	पूर्ण

	/* Only 255 descriptors can be added at once */
	जबतक ((rx_करोne > 0) || (rx_filled > 0)) अणु
		अगर (rx_करोne <= 0xff) अणु
			val = rx_करोne;
			rx_करोne = 0;
		पूर्ण अन्यथा अणु
			val = 0xff;
			rx_करोne -= 0xff;
		पूर्ण
		अगर (rx_filled <= 0xff) अणु
			val |= rx_filled << MVNETA_RXQ_ADD_NON_OCCUPIED_SHIFT;
			rx_filled = 0;
		पूर्ण अन्यथा अणु
			val |= 0xff << MVNETA_RXQ_ADD_NON_OCCUPIED_SHIFT;
			rx_filled -= 0xff;
		पूर्ण
		mvreg_ग_लिखो(pp, MVNETA_RXQ_STATUS_UPDATE_REG(rxq->id), val);
	पूर्ण
पूर्ण

/* Get poपूर्णांकer to next RX descriptor to be processed by SW */
अटल काष्ठा mvneta_rx_desc *
mvneta_rxq_next_desc_get(काष्ठा mvneta_rx_queue *rxq)
अणु
	पूर्णांक rx_desc = rxq->next_desc_to_proc;

	rxq->next_desc_to_proc = MVNETA_QUEUE_NEXT_DESC(rxq, rx_desc);
	prefetch(rxq->descs + rxq->next_desc_to_proc);
	वापस rxq->descs + rx_desc;
पूर्ण

/* Change maximum receive size of the port. */
अटल व्योम mvneta_max_rx_size_set(काष्ठा mvneta_port *pp, पूर्णांक max_rx_size)
अणु
	u32 val;

	val =  mvreg_पढ़ो(pp, MVNETA_GMAC_CTRL_0);
	val &= ~MVNETA_GMAC_MAX_RX_SIZE_MASK;
	val |= ((max_rx_size - MVNETA_MH_SIZE) / 2) <<
		MVNETA_GMAC_MAX_RX_SIZE_SHIFT;
	mvreg_ग_लिखो(pp, MVNETA_GMAC_CTRL_0, val);
पूर्ण


/* Set rx queue offset */
अटल व्योम mvneta_rxq_offset_set(काष्ठा mvneta_port *pp,
				  काष्ठा mvneta_rx_queue *rxq,
				  पूर्णांक offset)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id));
	val &= ~MVNETA_RXQ_PKT_OFFSET_ALL_MASK;

	/* Offset is in */
	val |= MVNETA_RXQ_PKT_OFFSET_MASK(offset >> 3);
	mvreg_ग_लिखो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id), val);
पूर्ण


/* Tx descriptors helper methods */

/* Update HW with number of TX descriptors to be sent */
अटल व्योम mvneta_txq_pend_desc_add(काष्ठा mvneta_port *pp,
				     काष्ठा mvneta_tx_queue *txq,
				     पूर्णांक pend_desc)
अणु
	u32 val;

	pend_desc += txq->pending;

	/* Only 255 Tx descriptors can be added at once */
	करो अणु
		val = min(pend_desc, 255);
		mvreg_ग_लिखो(pp, MVNETA_TXQ_UPDATE_REG(txq->id), val);
		pend_desc -= val;
	पूर्ण जबतक (pend_desc > 0);
	txq->pending = 0;
पूर्ण

/* Get poपूर्णांकer to next TX descriptor to be processed (send) by HW */
अटल काष्ठा mvneta_tx_desc *
mvneta_txq_next_desc_get(काष्ठा mvneta_tx_queue *txq)
अणु
	पूर्णांक tx_desc = txq->next_desc_to_proc;

	txq->next_desc_to_proc = MVNETA_QUEUE_NEXT_DESC(txq, tx_desc);
	वापस txq->descs + tx_desc;
पूर्ण

/* Release the last allocated TX descriptor. Useful to handle DMA
 * mapping failures in the TX path.
 */
अटल व्योम mvneta_txq_desc_put(काष्ठा mvneta_tx_queue *txq)
अणु
	अगर (txq->next_desc_to_proc == 0)
		txq->next_desc_to_proc = txq->last_desc - 1;
	अन्यथा
		txq->next_desc_to_proc--;
पूर्ण

/* Set rxq buf size */
अटल व्योम mvneta_rxq_buf_size_set(काष्ठा mvneta_port *pp,
				    काष्ठा mvneta_rx_queue *rxq,
				    पूर्णांक buf_size)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_RXQ_SIZE_REG(rxq->id));

	val &= ~MVNETA_RXQ_BUF_SIZE_MASK;
	val |= ((buf_size >> 3) << MVNETA_RXQ_BUF_SIZE_SHIFT);

	mvreg_ग_लिखो(pp, MVNETA_RXQ_SIZE_REG(rxq->id), val);
पूर्ण

/* Disable buffer management (BM) */
अटल व्योम mvneta_rxq_bm_disable(काष्ठा mvneta_port *pp,
				  काष्ठा mvneta_rx_queue *rxq)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id));
	val &= ~MVNETA_RXQ_HW_BUF_ALLOC;
	mvreg_ग_लिखो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id), val);
पूर्ण

/* Enable buffer management (BM) */
अटल व्योम mvneta_rxq_bm_enable(काष्ठा mvneta_port *pp,
				 काष्ठा mvneta_rx_queue *rxq)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id));
	val |= MVNETA_RXQ_HW_BUF_ALLOC;
	mvreg_ग_लिखो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id), val);
पूर्ण

/* Notअगरy HW about port's assignment of pool क्रम bigger packets */
अटल व्योम mvneta_rxq_दीर्घ_pool_set(काष्ठा mvneta_port *pp,
				     काष्ठा mvneta_rx_queue *rxq)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id));
	val &= ~MVNETA_RXQ_LONG_POOL_ID_MASK;
	val |= (pp->pool_दीर्घ->id << MVNETA_RXQ_LONG_POOL_ID_SHIFT);

	mvreg_ग_लिखो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id), val);
पूर्ण

/* Notअगरy HW about port's assignment of pool क्रम smaller packets */
अटल व्योम mvneta_rxq_लघु_pool_set(काष्ठा mvneta_port *pp,
				      काष्ठा mvneta_rx_queue *rxq)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id));
	val &= ~MVNETA_RXQ_SHORT_POOL_ID_MASK;
	val |= (pp->pool_लघु->id << MVNETA_RXQ_SHORT_POOL_ID_SHIFT);

	mvreg_ग_लिखो(pp, MVNETA_RXQ_CONFIG_REG(rxq->id), val);
पूर्ण

/* Set port's receive buffer size क्रम asचिन्हित BM pool */
अटल अंतरभूत व्योम mvneta_bm_pool_bufsize_set(काष्ठा mvneta_port *pp,
					      पूर्णांक buf_size,
					      u8 pool_id)
अणु
	u32 val;

	अगर (!IS_ALIGNED(buf_size, 8)) अणु
		dev_warn(pp->dev->dev.parent,
			 "illegal buf_size value %d, round to %d\n",
			 buf_size, ALIGN(buf_size, 8));
		buf_size = ALIGN(buf_size, 8);
	पूर्ण

	val = mvreg_पढ़ो(pp, MVNETA_PORT_POOL_BUFFER_SZ_REG(pool_id));
	val |= buf_size & MVNETA_PORT_POOL_BUFFER_SZ_MASK;
	mvreg_ग_लिखो(pp, MVNETA_PORT_POOL_BUFFER_SZ_REG(pool_id), val);
पूर्ण

/* Configure MBUS winकरोw in order to enable access BM पूर्णांकernal SRAM */
अटल पूर्णांक mvneta_mbus_io_win_set(काष्ठा mvneta_port *pp, u32 base, u32 wsize,
				  u8 target, u8 attr)
अणु
	u32 win_enable, win_protect;
	पूर्णांक i;

	win_enable = mvreg_पढ़ो(pp, MVNETA_BASE_ADDR_ENABLE);

	अगर (pp->bm_win_id < 0) अणु
		/* Find first not occupied winकरोw */
		क्रम (i = 0; i < MVNETA_MAX_DECODE_WIN; i++) अणु
			अगर (win_enable & (1 << i)) अणु
				pp->bm_win_id = i;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == MVNETA_MAX_DECODE_WIN)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		i = pp->bm_win_id;
	पूर्ण

	mvreg_ग_लिखो(pp, MVNETA_WIN_BASE(i), 0);
	mvreg_ग_लिखो(pp, MVNETA_WIN_SIZE(i), 0);

	अगर (i < 4)
		mvreg_ग_लिखो(pp, MVNETA_WIN_REMAP(i), 0);

	mvreg_ग_लिखो(pp, MVNETA_WIN_BASE(i), (base & 0xffff0000) |
		    (attr << 8) | target);

	mvreg_ग_लिखो(pp, MVNETA_WIN_SIZE(i), (wsize - 1) & 0xffff0000);

	win_protect = mvreg_पढ़ो(pp, MVNETA_ACCESS_PROTECT_ENABLE);
	win_protect |= 3 << (2 * i);
	mvreg_ग_लिखो(pp, MVNETA_ACCESS_PROTECT_ENABLE, win_protect);

	win_enable &= ~(1 << i);
	mvreg_ग_लिखो(pp, MVNETA_BASE_ADDR_ENABLE, win_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_bm_port_mbus_init(काष्ठा mvneta_port *pp)
अणु
	u32 wsize;
	u8 target, attr;
	पूर्णांक err;

	/* Get BM winकरोw inक्रमmation */
	err = mvebu_mbus_get_io_win_info(pp->bm_priv->bppi_phys_addr, &wsize,
					 &target, &attr);
	अगर (err < 0)
		वापस err;

	pp->bm_win_id = -1;

	/* Open NETA -> BM winकरोw */
	err = mvneta_mbus_io_win_set(pp, pp->bm_priv->bppi_phys_addr, wsize,
				     target, attr);
	अगर (err < 0) अणु
		netdev_info(pp->dev, "fail to configure mbus window to BM\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* Assign and initialize pools क्रम port. In हाल of fail
 * buffer manager will reमुख्य disabled क्रम current port.
 */
अटल पूर्णांक mvneta_bm_port_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा mvneta_port *pp)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	u32 दीर्घ_pool_id, लघु_pool_id;

	अगर (!pp->neta_armada3700) अणु
		पूर्णांक ret;

		ret = mvneta_bm_port_mbus_init(pp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dn, "bm,pool-long", &दीर्घ_pool_id)) अणु
		netdev_info(pp->dev, "missing long pool id\n");
		वापस -EINVAL;
	पूर्ण

	/* Create port's दीर्घ pool depending on mtu */
	pp->pool_दीर्घ = mvneta_bm_pool_use(pp->bm_priv, दीर्घ_pool_id,
					   MVNETA_BM_LONG, pp->id,
					   MVNETA_RX_PKT_SIZE(pp->dev->mtu));
	अगर (!pp->pool_दीर्घ) अणु
		netdev_info(pp->dev, "fail to obtain long pool for port\n");
		वापस -ENOMEM;
	पूर्ण

	pp->pool_दीर्घ->port_map |= 1 << pp->id;

	mvneta_bm_pool_bufsize_set(pp, pp->pool_दीर्घ->buf_size,
				   pp->pool_दीर्घ->id);

	/* If लघु pool id is not defined, assume using single pool */
	अगर (of_property_पढ़ो_u32(dn, "bm,pool-short", &लघु_pool_id))
		लघु_pool_id = दीर्घ_pool_id;

	/* Create port's लघु pool */
	pp->pool_लघु = mvneta_bm_pool_use(pp->bm_priv, लघु_pool_id,
					    MVNETA_BM_SHORT, pp->id,
					    MVNETA_BM_SHORT_PKT_SIZE);
	अगर (!pp->pool_लघु) अणु
		netdev_info(pp->dev, "fail to obtain short pool for port\n");
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_दीर्घ, 1 << pp->id);
		वापस -ENOMEM;
	पूर्ण

	अगर (लघु_pool_id != दीर्घ_pool_id) अणु
		pp->pool_लघु->port_map |= 1 << pp->id;
		mvneta_bm_pool_bufsize_set(pp, pp->pool_लघु->buf_size,
					   pp->pool_लघु->id);
	पूर्ण

	वापस 0;
पूर्ण

/* Update settings of a pool क्रम bigger packets */
अटल व्योम mvneta_bm_update_mtu(काष्ठा mvneta_port *pp, पूर्णांक mtu)
अणु
	काष्ठा mvneta_bm_pool *bm_pool = pp->pool_दीर्घ;
	काष्ठा hwbm_pool *hwbm_pool = &bm_pool->hwbm_pool;
	पूर्णांक num;

	/* Release all buffers from दीर्घ pool */
	mvneta_bm_bufs_मुक्त(pp->bm_priv, bm_pool, 1 << pp->id);
	अगर (hwbm_pool->buf_num) अणु
		WARN(1, "cannot free all buffers in pool %d\n",
		     bm_pool->id);
		जाओ bm_mtu_err;
	पूर्ण

	bm_pool->pkt_size = MVNETA_RX_PKT_SIZE(mtu);
	bm_pool->buf_size = MVNETA_RX_BUF_SIZE(bm_pool->pkt_size);
	hwbm_pool->frag_size = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
			SKB_DATA_ALIGN(MVNETA_RX_BUF_SIZE(bm_pool->pkt_size));

	/* Fill entire दीर्घ pool */
	num = hwbm_pool_add(hwbm_pool, hwbm_pool->size);
	अगर (num != hwbm_pool->size) अणु
		WARN(1, "pool %d: %d of %d allocated\n",
		     bm_pool->id, num, hwbm_pool->size);
		जाओ bm_mtu_err;
	पूर्ण
	mvneta_bm_pool_bufsize_set(pp, bm_pool->buf_size, bm_pool->id);

	वापस;

bm_mtu_err:
	mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_दीर्घ, 1 << pp->id);
	mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_लघु, 1 << pp->id);

	pp->bm_priv = शून्य;
	pp->rx_offset_correction = MVNETA_SKB_HEADROOM;
	mvreg_ग_लिखो(pp, MVNETA_ACC_MODE, MVNETA_ACC_MODE_EXT1);
	netdev_info(pp->dev, "fail to update MTU, fall back to software BM\n");
पूर्ण

/* Start the Ethernet port RX and TX activity */
अटल व्योम mvneta_port_up(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक queue;
	u32 q_map;

	/* Enable all initialized TXs. */
	q_map = 0;
	क्रम (queue = 0; queue < txq_number; queue++) अणु
		काष्ठा mvneta_tx_queue *txq = &pp->txqs[queue];
		अगर (txq->descs)
			q_map |= (1 << queue);
	पूर्ण
	mvreg_ग_लिखो(pp, MVNETA_TXQ_CMD, q_map);

	q_map = 0;
	/* Enable all initialized RXQs. */
	क्रम (queue = 0; queue < rxq_number; queue++) अणु
		काष्ठा mvneta_rx_queue *rxq = &pp->rxqs[queue];

		अगर (rxq->descs)
			q_map |= (1 << queue);
	पूर्ण
	mvreg_ग_लिखो(pp, MVNETA_RXQ_CMD, q_map);
पूर्ण

/* Stop the Ethernet port activity */
अटल व्योम mvneta_port_करोwn(काष्ठा mvneta_port *pp)
अणु
	u32 val;
	पूर्णांक count;

	/* Stop Rx port activity. Check port Rx activity. */
	val = mvreg_पढ़ो(pp, MVNETA_RXQ_CMD) & MVNETA_RXQ_ENABLE_MASK;

	/* Issue stop command क्रम active channels only */
	अगर (val != 0)
		mvreg_ग_लिखो(pp, MVNETA_RXQ_CMD,
			    val << MVNETA_RXQ_DISABLE_SHIFT);

	/* Wait क्रम all Rx activity to terminate. */
	count = 0;
	करो अणु
		अगर (count++ >= MVNETA_RX_DISABLE_TIMEOUT_MSEC) अणु
			netdev_warn(pp->dev,
				    "TIMEOUT for RX stopped ! rx_queue_cmd: 0x%08x\n",
				    val);
			अवरोध;
		पूर्ण
		mdelay(1);

		val = mvreg_पढ़ो(pp, MVNETA_RXQ_CMD);
	पूर्ण जबतक (val & MVNETA_RXQ_ENABLE_MASK);

	/* Stop Tx port activity. Check port Tx activity. Issue stop
	 * command क्रम active channels only
	 */
	val = (mvreg_पढ़ो(pp, MVNETA_TXQ_CMD)) & MVNETA_TXQ_ENABLE_MASK;

	अगर (val != 0)
		mvreg_ग_लिखो(pp, MVNETA_TXQ_CMD,
			    (val << MVNETA_TXQ_DISABLE_SHIFT));

	/* Wait क्रम all Tx activity to terminate. */
	count = 0;
	करो अणु
		अगर (count++ >= MVNETA_TX_DISABLE_TIMEOUT_MSEC) अणु
			netdev_warn(pp->dev,
				    "TIMEOUT for TX stopped status=0x%08x\n",
				    val);
			अवरोध;
		पूर्ण
		mdelay(1);

		/* Check TX Command reg that all Txqs are stopped */
		val = mvreg_पढ़ो(pp, MVNETA_TXQ_CMD);

	पूर्ण जबतक (val & MVNETA_TXQ_ENABLE_MASK);

	/* Double check to verअगरy that TX FIFO is empty */
	count = 0;
	करो अणु
		अगर (count++ >= MVNETA_TX_FIFO_EMPTY_TIMEOUT) अणु
			netdev_warn(pp->dev,
				    "TX FIFO empty timeout status=0x%08x\n",
				    val);
			अवरोध;
		पूर्ण
		mdelay(1);

		val = mvreg_पढ़ो(pp, MVNETA_PORT_STATUS);
	पूर्ण जबतक (!(val & MVNETA_TX_FIFO_EMPTY) &&
		 (val & MVNETA_TX_IN_PRGRS));

	udelay(200);
पूर्ण

/* Enable the port by setting the port enable bit of the MAC control रेजिस्टर */
अटल व्योम mvneta_port_enable(काष्ठा mvneta_port *pp)
अणु
	u32 val;

	/* Enable port */
	val = mvreg_पढ़ो(pp, MVNETA_GMAC_CTRL_0);
	val |= MVNETA_GMAC0_PORT_ENABLE;
	mvreg_ग_लिखो(pp, MVNETA_GMAC_CTRL_0, val);
पूर्ण

/* Disable the port and रुको क्रम about 200 usec beक्रमe retuning */
अटल व्योम mvneta_port_disable(काष्ठा mvneta_port *pp)
अणु
	u32 val;

	/* Reset the Enable bit in the Serial Control Register */
	val = mvreg_पढ़ो(pp, MVNETA_GMAC_CTRL_0);
	val &= ~MVNETA_GMAC0_PORT_ENABLE;
	mvreg_ग_लिखो(pp, MVNETA_GMAC_CTRL_0, val);

	udelay(200);
पूर्ण

/* Multicast tables methods */

/* Set all entries in Unicast MAC Table; queue==-1 means reject all */
अटल व्योम mvneta_set_ucast_table(काष्ठा mvneta_port *pp, पूर्णांक queue)
अणु
	पूर्णांक offset;
	u32 val;

	अगर (queue == -1) अणु
		val = 0;
	पूर्ण अन्यथा अणु
		val = 0x1 | (queue << 1);
		val |= (val << 24) | (val << 16) | (val << 8);
	पूर्ण

	क्रम (offset = 0; offset <= 0xc; offset += 4)
		mvreg_ग_लिखो(pp, MVNETA_DA_FILT_UCAST_BASE + offset, val);
पूर्ण

/* Set all entries in Special Multicast MAC Table; queue==-1 means reject all */
अटल व्योम mvneta_set_special_mcast_table(काष्ठा mvneta_port *pp, पूर्णांक queue)
अणु
	पूर्णांक offset;
	u32 val;

	अगर (queue == -1) अणु
		val = 0;
	पूर्ण अन्यथा अणु
		val = 0x1 | (queue << 1);
		val |= (val << 24) | (val << 16) | (val << 8);
	पूर्ण

	क्रम (offset = 0; offset <= 0xfc; offset += 4)
		mvreg_ग_लिखो(pp, MVNETA_DA_FILT_SPEC_MCAST + offset, val);

पूर्ण

/* Set all entries in Other Multicast MAC Table. queue==-1 means reject all */
अटल व्योम mvneta_set_other_mcast_table(काष्ठा mvneta_port *pp, पूर्णांक queue)
अणु
	पूर्णांक offset;
	u32 val;

	अगर (queue == -1) अणु
		स_रखो(pp->mcast_count, 0, माप(pp->mcast_count));
		val = 0;
	पूर्ण अन्यथा अणु
		स_रखो(pp->mcast_count, 1, माप(pp->mcast_count));
		val = 0x1 | (queue << 1);
		val |= (val << 24) | (val << 16) | (val << 8);
	पूर्ण

	क्रम (offset = 0; offset <= 0xfc; offset += 4)
		mvreg_ग_लिखो(pp, MVNETA_DA_FILT_OTH_MCAST + offset, val);
पूर्ण

अटल व्योम mvneta_percpu_unmask_पूर्णांकerrupt(व्योम *arg)
अणु
	काष्ठा mvneta_port *pp = arg;

	/* All the queue are unmasked, but actually only the ones
	 * mapped to this CPU will be unmasked
	 */
	mvreg_ग_लिखो(pp, MVNETA_INTR_NEW_MASK,
		    MVNETA_RX_INTR_MASK_ALL |
		    MVNETA_TX_INTR_MASK_ALL |
		    MVNETA_MISCINTR_INTR_MASK);
पूर्ण

अटल व्योम mvneta_percpu_mask_पूर्णांकerrupt(व्योम *arg)
अणु
	काष्ठा mvneta_port *pp = arg;

	/* All the queue are masked, but actually only the ones
	 * mapped to this CPU will be masked
	 */
	mvreg_ग_लिखो(pp, MVNETA_INTR_NEW_MASK, 0);
	mvreg_ग_लिखो(pp, MVNETA_INTR_OLD_MASK, 0);
	mvreg_ग_लिखो(pp, MVNETA_INTR_MISC_MASK, 0);
पूर्ण

अटल व्योम mvneta_percpu_clear_पूर्णांकr_cause(व्योम *arg)
अणु
	काष्ठा mvneta_port *pp = arg;

	/* All the queue are cleared, but actually only the ones
	 * mapped to this CPU will be cleared
	 */
	mvreg_ग_लिखो(pp, MVNETA_INTR_NEW_CAUSE, 0);
	mvreg_ग_लिखो(pp, MVNETA_INTR_MISC_CAUSE, 0);
	mvreg_ग_लिखो(pp, MVNETA_INTR_OLD_CAUSE, 0);
पूर्ण

/* This method sets शेषs to the NETA port:
 *	Clears पूर्णांकerrupt Cause and Mask रेजिस्टरs.
 *	Clears all MAC tables.
 *	Sets शेषs to all रेजिस्टरs.
 *	Resets RX and TX descriptor rings.
 *	Resets PHY.
 * This method can be called after mvneta_port_करोwn() to वापस the port
 *	settings to शेषs.
 */
अटल व्योम mvneta_शेषs_set(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक cpu;
	पूर्णांक queue;
	u32 val;
	पूर्णांक max_cpu = num_present_cpus();

	/* Clear all Cause रेजिस्टरs */
	on_each_cpu(mvneta_percpu_clear_पूर्णांकr_cause, pp, true);

	/* Mask all पूर्णांकerrupts */
	on_each_cpu(mvneta_percpu_mask_पूर्णांकerrupt, pp, true);
	mvreg_ग_लिखो(pp, MVNETA_INTR_ENABLE, 0);

	/* Enable MBUS Retry bit16 */
	mvreg_ग_लिखो(pp, MVNETA_MBUS_RETRY, 0x20);

	/* Set CPU queue access map. CPUs are asचिन्हित to the RX and
	 * TX queues modulo their number. If there is only one TX
	 * queue then it is asचिन्हित to the CPU associated to the
	 * शेष RX queue.
	 */
	क्रम_each_present_cpu(cpu) अणु
		पूर्णांक rxq_map = 0, txq_map = 0;
		पूर्णांक rxq, txq;
		अगर (!pp->neta_armada3700) अणु
			क्रम (rxq = 0; rxq < rxq_number; rxq++)
				अगर ((rxq % max_cpu) == cpu)
					rxq_map |= MVNETA_CPU_RXQ_ACCESS(rxq);

			क्रम (txq = 0; txq < txq_number; txq++)
				अगर ((txq % max_cpu) == cpu)
					txq_map |= MVNETA_CPU_TXQ_ACCESS(txq);

			/* With only one TX queue we configure a special हाल
			 * which will allow to get all the irq on a single
			 * CPU
			 */
			अगर (txq_number == 1)
				txq_map = (cpu == pp->rxq_def) ?
					MVNETA_CPU_TXQ_ACCESS(1) : 0;

		पूर्ण अन्यथा अणु
			txq_map = MVNETA_CPU_TXQ_ACCESS_ALL_MASK;
			rxq_map = MVNETA_CPU_RXQ_ACCESS_ALL_MASK;
		पूर्ण

		mvreg_ग_लिखो(pp, MVNETA_CPU_MAP(cpu), rxq_map | txq_map);
	पूर्ण

	/* Reset RX and TX DMAs */
	mvreg_ग_लिखो(pp, MVNETA_PORT_RX_RESET, MVNETA_PORT_RX_DMA_RESET);
	mvreg_ग_लिखो(pp, MVNETA_PORT_TX_RESET, MVNETA_PORT_TX_DMA_RESET);

	/* Disable Legacy WRR, Disable EJP, Release from reset */
	mvreg_ग_लिखो(pp, MVNETA_TXQ_CMD_1, 0);
	क्रम (queue = 0; queue < txq_number; queue++) अणु
		mvreg_ग_लिखो(pp, MVETH_TXQ_TOKEN_COUNT_REG(queue), 0);
		mvreg_ग_लिखो(pp, MVETH_TXQ_TOKEN_CFG_REG(queue), 0);
	पूर्ण

	mvreg_ग_लिखो(pp, MVNETA_PORT_TX_RESET, 0);
	mvreg_ग_लिखो(pp, MVNETA_PORT_RX_RESET, 0);

	/* Set Port Acceleration Mode */
	अगर (pp->bm_priv)
		/* HW buffer management + legacy parser */
		val = MVNETA_ACC_MODE_EXT2;
	अन्यथा
		/* SW buffer management + legacy parser */
		val = MVNETA_ACC_MODE_EXT1;
	mvreg_ग_लिखो(pp, MVNETA_ACC_MODE, val);

	अगर (pp->bm_priv)
		mvreg_ग_लिखो(pp, MVNETA_BM_ADDRESS, pp->bm_priv->bppi_phys_addr);

	/* Update val of portCfg रेजिस्टर accordingly with all RxQueue types */
	val = MVNETA_PORT_CONFIG_DEFL_VALUE(pp->rxq_def);
	mvreg_ग_लिखो(pp, MVNETA_PORT_CONFIG, val);

	val = 0;
	mvreg_ग_लिखो(pp, MVNETA_PORT_CONFIG_EXTEND, val);
	mvreg_ग_लिखो(pp, MVNETA_RX_MIN_FRAME_SIZE, 64);

	/* Build PORT_SDMA_CONFIG_REG */
	val = 0;

	/* Default burst size */
	val |= MVNETA_TX_BRST_SZ_MASK(MVNETA_SDMA_BRST_SIZE_16);
	val |= MVNETA_RX_BRST_SZ_MASK(MVNETA_SDMA_BRST_SIZE_16);
	val |= MVNETA_RX_NO_DATA_SWAP | MVNETA_TX_NO_DATA_SWAP;

#अगर defined(__BIG_ENDIAN)
	val |= MVNETA_DESC_SWAP;
#पूर्ण_अगर

	/* Assign port SDMA configuration */
	mvreg_ग_लिखो(pp, MVNETA_SDMA_CONFIG, val);

	/* Disable PHY polling in hardware, since we're using the
	 * kernel phylib to करो this.
	 */
	val = mvreg_पढ़ो(pp, MVNETA_UNIT_CONTROL);
	val &= ~MVNETA_PHY_POLLING_ENABLE;
	mvreg_ग_लिखो(pp, MVNETA_UNIT_CONTROL, val);

	mvneta_set_ucast_table(pp, -1);
	mvneta_set_special_mcast_table(pp, -1);
	mvneta_set_other_mcast_table(pp, -1);

	/* Set port पूर्णांकerrupt enable रेजिस्टर - शेष enable all */
	mvreg_ग_लिखो(pp, MVNETA_INTR_ENABLE,
		    (MVNETA_RXQ_INTR_ENABLE_ALL_MASK
		     | MVNETA_TXQ_INTR_ENABLE_ALL_MASK));

	mvneta_mib_counters_clear(pp);
पूर्ण

/* Set max sizes क्रम tx queues */
अटल व्योम mvneta_txq_max_tx_size_set(काष्ठा mvneta_port *pp, पूर्णांक max_tx_size)

अणु
	u32 val, size, mtu;
	पूर्णांक queue;

	mtu = max_tx_size * 8;
	अगर (mtu > MVNETA_TX_MTU_MAX)
		mtu = MVNETA_TX_MTU_MAX;

	/* Set MTU */
	val = mvreg_पढ़ो(pp, MVNETA_TX_MTU);
	val &= ~MVNETA_TX_MTU_MAX;
	val |= mtu;
	mvreg_ग_लिखो(pp, MVNETA_TX_MTU, val);

	/* TX token size and all TXQs token size must be larger that MTU */
	val = mvreg_पढ़ो(pp, MVNETA_TX_TOKEN_SIZE);

	size = val & MVNETA_TX_TOKEN_SIZE_MAX;
	अगर (size < mtu) अणु
		size = mtu;
		val &= ~MVNETA_TX_TOKEN_SIZE_MAX;
		val |= size;
		mvreg_ग_लिखो(pp, MVNETA_TX_TOKEN_SIZE, val);
	पूर्ण
	क्रम (queue = 0; queue < txq_number; queue++) अणु
		val = mvreg_पढ़ो(pp, MVNETA_TXQ_TOKEN_SIZE_REG(queue));

		size = val & MVNETA_TXQ_TOKEN_SIZE_MAX;
		अगर (size < mtu) अणु
			size = mtu;
			val &= ~MVNETA_TXQ_TOKEN_SIZE_MAX;
			val |= size;
			mvreg_ग_लिखो(pp, MVNETA_TXQ_TOKEN_SIZE_REG(queue), val);
		पूर्ण
	पूर्ण
पूर्ण

/* Set unicast address */
अटल व्योम mvneta_set_ucast_addr(काष्ठा mvneta_port *pp, u8 last_nibble,
				  पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक unicast_reg;
	अचिन्हित पूर्णांक tbl_offset;
	अचिन्हित पूर्णांक reg_offset;

	/* Locate the Unicast table entry */
	last_nibble = (0xf & last_nibble);

	/* offset from unicast tbl base */
	tbl_offset = (last_nibble / 4) * 4;

	/* offset within the above reg  */
	reg_offset = last_nibble % 4;

	unicast_reg = mvreg_पढ़ो(pp, (MVNETA_DA_FILT_UCAST_BASE + tbl_offset));

	अगर (queue == -1) अणु
		/* Clear accepts frame bit at specअगरied unicast DA tbl entry */
		unicast_reg &= ~(0xff << (8 * reg_offset));
	पूर्ण अन्यथा अणु
		unicast_reg &= ~(0xff << (8 * reg_offset));
		unicast_reg |= ((0x01 | (queue << 1)) << (8 * reg_offset));
	पूर्ण

	mvreg_ग_लिखो(pp, (MVNETA_DA_FILT_UCAST_BASE + tbl_offset), unicast_reg);
पूर्ण

/* Set mac address */
अटल व्योम mvneta_mac_addr_set(काष्ठा mvneta_port *pp, अचिन्हित अक्षर *addr,
				पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक mac_h;
	अचिन्हित पूर्णांक mac_l;

	अगर (queue != -1) अणु
		mac_l = (addr[4] << 8) | (addr[5]);
		mac_h = (addr[0] << 24) | (addr[1] << 16) |
			(addr[2] << 8) | (addr[3] << 0);

		mvreg_ग_लिखो(pp, MVNETA_MAC_ADDR_LOW, mac_l);
		mvreg_ग_लिखो(pp, MVNETA_MAC_ADDR_HIGH, mac_h);
	पूर्ण

	/* Accept frames of this address */
	mvneta_set_ucast_addr(pp, addr[5], queue);
पूर्ण

/* Set the number of packets that will be received beक्रमe RX पूर्णांकerrupt
 * will be generated by HW.
 */
अटल व्योम mvneta_rx_pkts_coal_set(काष्ठा mvneta_port *pp,
				    काष्ठा mvneta_rx_queue *rxq, u32 value)
अणु
	mvreg_ग_लिखो(pp, MVNETA_RXQ_THRESHOLD_REG(rxq->id),
		    value | MVNETA_RXQ_NON_OCCUPIED(0));
पूर्ण

/* Set the समय delay in usec beक्रमe RX पूर्णांकerrupt will be generated by
 * HW.
 */
अटल व्योम mvneta_rx_समय_coal_set(काष्ठा mvneta_port *pp,
				    काष्ठा mvneta_rx_queue *rxq, u32 value)
अणु
	u32 val;
	अचिन्हित दीर्घ clk_rate;

	clk_rate = clk_get_rate(pp->clk);
	val = (clk_rate / 1000000) * value;

	mvreg_ग_लिखो(pp, MVNETA_RXQ_TIME_COAL_REG(rxq->id), val);
पूर्ण

/* Set threshold क्रम TX_DONE pkts coalescing */
अटल व्योम mvneta_tx_करोne_pkts_coal_set(काष्ठा mvneta_port *pp,
					 काष्ठा mvneta_tx_queue *txq, u32 value)
अणु
	u32 val;

	val = mvreg_पढ़ो(pp, MVNETA_TXQ_SIZE_REG(txq->id));

	val &= ~MVNETA_TXQ_SENT_THRESH_ALL_MASK;
	val |= MVNETA_TXQ_SENT_THRESH_MASK(value);

	mvreg_ग_लिखो(pp, MVNETA_TXQ_SIZE_REG(txq->id), val);
पूर्ण

/* Handle rx descriptor fill by setting buf_cookie and buf_phys_addr */
अटल व्योम mvneta_rx_desc_fill(काष्ठा mvneta_rx_desc *rx_desc,
				u32 phys_addr, व्योम *virt_addr,
				काष्ठा mvneta_rx_queue *rxq)
अणु
	पूर्णांक i;

	rx_desc->buf_phys_addr = phys_addr;
	i = rx_desc - rxq->descs;
	rxq->buf_virt_addr[i] = virt_addr;
पूर्ण

/* Decrement sent descriptors counter */
अटल व्योम mvneta_txq_sent_desc_dec(काष्ठा mvneta_port *pp,
				     काष्ठा mvneta_tx_queue *txq,
				     पूर्णांक sent_desc)
अणु
	u32 val;

	/* Only 255 TX descriptors can be updated at once */
	जबतक (sent_desc > 0xff) अणु
		val = 0xff << MVNETA_TXQ_DEC_SENT_SHIFT;
		mvreg_ग_लिखो(pp, MVNETA_TXQ_UPDATE_REG(txq->id), val);
		sent_desc = sent_desc - 0xff;
	पूर्ण

	val = sent_desc << MVNETA_TXQ_DEC_SENT_SHIFT;
	mvreg_ग_लिखो(pp, MVNETA_TXQ_UPDATE_REG(txq->id), val);
पूर्ण

/* Get number of TX descriptors alपढ़ोy sent by HW */
अटल पूर्णांक mvneta_txq_sent_desc_num_get(काष्ठा mvneta_port *pp,
					काष्ठा mvneta_tx_queue *txq)
अणु
	u32 val;
	पूर्णांक sent_desc;

	val = mvreg_पढ़ो(pp, MVNETA_TXQ_STATUS_REG(txq->id));
	sent_desc = (val & MVNETA_TXQ_SENT_DESC_MASK) >>
		MVNETA_TXQ_SENT_DESC_SHIFT;

	वापस sent_desc;
पूर्ण

/* Get number of sent descriptors and decrement counter.
 *  The number of sent descriptors is वापसed.
 */
अटल पूर्णांक mvneta_txq_sent_desc_proc(काष्ठा mvneta_port *pp,
				     काष्ठा mvneta_tx_queue *txq)
अणु
	पूर्णांक sent_desc;

	/* Get number of sent descriptors */
	sent_desc = mvneta_txq_sent_desc_num_get(pp, txq);

	/* Decrement sent descriptors counter */
	अगर (sent_desc)
		mvneta_txq_sent_desc_dec(pp, txq, sent_desc);

	वापस sent_desc;
पूर्ण

/* Set TXQ descriptors fields relevant क्रम CSUM calculation */
अटल u32 mvneta_txq_desc_csum(पूर्णांक l3_offs, पूर्णांक l3_proto,
				पूर्णांक ip_hdr_len, पूर्णांक l4_proto)
अणु
	u32 command;

	/* Fields: L3_offset, IP_hdrlen, L3_type, G_IPv4_chk,
	 * G_L4_chk, L4_type; required only क्रम checksum
	 * calculation
	 */
	command =  l3_offs    << MVNETA_TX_L3_OFF_SHIFT;
	command |= ip_hdr_len << MVNETA_TX_IP_HLEN_SHIFT;

	अगर (l3_proto == htons(ETH_P_IP))
		command |= MVNETA_TXD_IP_CSUM;
	अन्यथा
		command |= MVNETA_TX_L3_IP6;

	अगर (l4_proto == IPPROTO_TCP)
		command |=  MVNETA_TX_L4_CSUM_FULL;
	अन्यथा अगर (l4_proto == IPPROTO_UDP)
		command |= MVNETA_TX_L4_UDP | MVNETA_TX_L4_CSUM_FULL;
	अन्यथा
		command |= MVNETA_TX_L4_CSUM_NOT;

	वापस command;
पूर्ण


/* Display more error info */
अटल व्योम mvneta_rx_error(काष्ठा mvneta_port *pp,
			    काष्ठा mvneta_rx_desc *rx_desc)
अणु
	काष्ठा mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);
	u32 status = rx_desc->status;

	/* update per-cpu counter */
	u64_stats_update_begin(&stats->syncp);
	stats->rx_errors++;
	u64_stats_update_end(&stats->syncp);

	चयन (status & MVNETA_RXD_ERR_CODE_MASK) अणु
	हाल MVNETA_RXD_ERR_CRC:
		netdev_err(pp->dev, "bad rx status %08x (crc error), size=%d\n",
			   status, rx_desc->data_size);
		अवरोध;
	हाल MVNETA_RXD_ERR_OVERRUN:
		netdev_err(pp->dev, "bad rx status %08x (overrun error), size=%d\n",
			   status, rx_desc->data_size);
		अवरोध;
	हाल MVNETA_RXD_ERR_LEN:
		netdev_err(pp->dev, "bad rx status %08x (max frame length error), size=%d\n",
			   status, rx_desc->data_size);
		अवरोध;
	हाल MVNETA_RXD_ERR_RESOURCE:
		netdev_err(pp->dev, "bad rx status %08x (resource error), size=%d\n",
			   status, rx_desc->data_size);
		अवरोध;
	पूर्ण
पूर्ण

/* Handle RX checksum offload based on the descriptor's status */
अटल व्योम mvneta_rx_csum(काष्ठा mvneta_port *pp, u32 status,
			   काष्ठा sk_buff *skb)
अणु
	अगर ((pp->dev->features & NETIF_F_RXCSUM) &&
	    (status & MVNETA_RXD_L3_IP4) &&
	    (status & MVNETA_RXD_L4_CSUM_OK)) अणु
		skb->csum = 0;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		वापस;
	पूर्ण

	skb->ip_summed = CHECKSUM_NONE;
पूर्ण

/* Return tx queue poपूर्णांकer (find last set bit) according to <cause> वापसed
 * क्रमm tx_करोne reg. <cause> must not be null. The वापस value is always a
 * valid queue क्रम matching the first one found in <cause>.
 */
अटल काष्ठा mvneta_tx_queue *mvneta_tx_करोne_policy(काष्ठा mvneta_port *pp,
						     u32 cause)
अणु
	पूर्णांक queue = fls(cause) - 1;

	वापस &pp->txqs[queue];
पूर्ण

/* Free tx queue skbuffs */
अटल व्योम mvneta_txq_bufs_मुक्त(काष्ठा mvneta_port *pp,
				 काष्ठा mvneta_tx_queue *txq, पूर्णांक num,
				 काष्ठा netdev_queue *nq, bool napi)
अणु
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;
	काष्ठा xdp_frame_bulk bq;
	पूर्णांक i;

	xdp_frame_bulk_init(&bq);

	rcu_पढ़ो_lock(); /* need क्रम xdp_वापस_frame_bulk */

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा mvneta_tx_buf *buf = &txq->buf[txq->txq_get_index];
		काष्ठा mvneta_tx_desc *tx_desc = txq->descs +
			txq->txq_get_index;

		mvneta_txq_inc_get(txq);

		अगर (!IS_TSO_HEADER(txq, tx_desc->buf_phys_addr) &&
		    buf->type != MVNETA_TYPE_XDP_TX)
			dma_unmap_single(pp->dev->dev.parent,
					 tx_desc->buf_phys_addr,
					 tx_desc->data_size, DMA_TO_DEVICE);
		अगर (buf->type == MVNETA_TYPE_SKB && buf->skb) अणु
			bytes_compl += buf->skb->len;
			pkts_compl++;
			dev_kमुक्त_skb_any(buf->skb);
		पूर्ण अन्यथा अगर (buf->type == MVNETA_TYPE_XDP_TX ||
			   buf->type == MVNETA_TYPE_XDP_NDO) अणु
			अगर (napi && buf->type == MVNETA_TYPE_XDP_TX)
				xdp_वापस_frame_rx_napi(buf->xdpf);
			अन्यथा
				xdp_वापस_frame_bulk(buf->xdpf, &bq);
		पूर्ण
	पूर्ण
	xdp_flush_frame_bulk(&bq);

	rcu_पढ़ो_unlock();

	netdev_tx_completed_queue(nq, pkts_compl, bytes_compl);
पूर्ण

/* Handle end of transmission */
अटल व्योम mvneta_txq_करोne(काष्ठा mvneta_port *pp,
			   काष्ठा mvneta_tx_queue *txq)
अणु
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(pp->dev, txq->id);
	पूर्णांक tx_करोne;

	tx_करोne = mvneta_txq_sent_desc_proc(pp, txq);
	अगर (!tx_करोne)
		वापस;

	mvneta_txq_bufs_मुक्त(pp, txq, tx_करोne, nq, true);

	txq->count -= tx_करोne;

	अगर (netअगर_tx_queue_stopped(nq)) अणु
		अगर (txq->count <= txq->tx_wake_threshold)
			netअगर_tx_wake_queue(nq);
	पूर्ण
पूर्ण

/* Refill processing क्रम SW buffer management */
/* Allocate page per descriptor */
अटल पूर्णांक mvneta_rx_refill(काष्ठा mvneta_port *pp,
			    काष्ठा mvneta_rx_desc *rx_desc,
			    काष्ठा mvneta_rx_queue *rxq,
			    gfp_t gfp_mask)
अणु
	dma_addr_t phys_addr;
	काष्ठा page *page;

	page = page_pool_alloc_pages(rxq->page_pool,
				     gfp_mask | __GFP_NOWARN);
	अगर (!page)
		वापस -ENOMEM;

	phys_addr = page_pool_get_dma_addr(page) + pp->rx_offset_correction;
	mvneta_rx_desc_fill(rx_desc, phys_addr, page, rxq);

	वापस 0;
पूर्ण

/* Handle tx checksum */
अटल u32 mvneta_skb_tx_csum(काष्ठा mvneta_port *pp, काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		पूर्णांक ip_hdr_len = 0;
		__be16 l3_proto = vlan_get_protocol(skb);
		u8 l4_proto;

		अगर (l3_proto == htons(ETH_P_IP)) अणु
			काष्ठा iphdr *ip4h = ip_hdr(skb);

			/* Calculate IPv4 checksum and L4 checksum */
			ip_hdr_len = ip4h->ihl;
			l4_proto = ip4h->protocol;
		पूर्ण अन्यथा अगर (l3_proto == htons(ETH_P_IPV6)) अणु
			काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);

			/* Read l4_protocol from one of IPv6 extra headers */
			अगर (skb_network_header_len(skb) > 0)
				ip_hdr_len = (skb_network_header_len(skb) >> 2);
			l4_proto = ip6h->nexthdr;
		पूर्ण अन्यथा
			वापस MVNETA_TX_L4_CSUM_NOT;

		वापस mvneta_txq_desc_csum(skb_network_offset(skb),
					    l3_proto, ip_hdr_len, l4_proto);
	पूर्ण

	वापस MVNETA_TX_L4_CSUM_NOT;
पूर्ण

/* Drop packets received by the RXQ and मुक्त buffers */
अटल व्योम mvneta_rxq_drop_pkts(काष्ठा mvneta_port *pp,
				 काष्ठा mvneta_rx_queue *rxq)
अणु
	पूर्णांक rx_करोne, i;

	rx_करोne = mvneta_rxq_busy_desc_num_get(pp, rxq);
	अगर (rx_करोne)
		mvneta_rxq_desc_num_update(pp, rxq, rx_करोne, rx_करोne);

	अगर (pp->bm_priv) अणु
		क्रम (i = 0; i < rx_करोne; i++) अणु
			काष्ठा mvneta_rx_desc *rx_desc =
						  mvneta_rxq_next_desc_get(rxq);
			u8 pool_id = MVNETA_RX_GET_BM_POOL_ID(rx_desc);
			काष्ठा mvneta_bm_pool *bm_pool;

			bm_pool = &pp->bm_priv->bm_pools[pool_id];
			/* Return dropped buffer to the pool */
			mvneta_bm_pool_put_bp(pp->bm_priv, bm_pool,
					      rx_desc->buf_phys_addr);
		पूर्ण
		वापस;
	पूर्ण

	क्रम (i = 0; i < rxq->size; i++) अणु
		काष्ठा mvneta_rx_desc *rx_desc = rxq->descs + i;
		व्योम *data = rxq->buf_virt_addr[i];
		अगर (!data || !(rx_desc->buf_phys_addr))
			जारी;

		page_pool_put_full_page(rxq->page_pool, data, false);
	पूर्ण
	अगर (xdp_rxq_info_is_reg(&rxq->xdp_rxq))
		xdp_rxq_info_unreg(&rxq->xdp_rxq);
	page_pool_destroy(rxq->page_pool);
	rxq->page_pool = शून्य;
पूर्ण

अटल व्योम
mvneta_update_stats(काष्ठा mvneta_port *pp,
		    काष्ठा mvneta_stats *ps)
अणु
	काष्ठा mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);

	u64_stats_update_begin(&stats->syncp);
	stats->es.ps.rx_packets += ps->rx_packets;
	stats->es.ps.rx_bytes += ps->rx_bytes;
	/* xdp */
	stats->es.ps.xdp_redirect += ps->xdp_redirect;
	stats->es.ps.xdp_pass += ps->xdp_pass;
	stats->es.ps.xdp_drop += ps->xdp_drop;
	u64_stats_update_end(&stats->syncp);
पूर्ण

अटल अंतरभूत
पूर्णांक mvneta_rx_refill_queue(काष्ठा mvneta_port *pp, काष्ठा mvneta_rx_queue *rxq)
अणु
	काष्ठा mvneta_rx_desc *rx_desc;
	पूर्णांक curr_desc = rxq->first_to_refill;
	पूर्णांक i;

	क्रम (i = 0; (i < rxq->refill_num) && (i < 64); i++) अणु
		rx_desc = rxq->descs + curr_desc;
		अगर (!(rx_desc->buf_phys_addr)) अणु
			अगर (mvneta_rx_refill(pp, rx_desc, rxq, GFP_ATOMIC)) अणु
				काष्ठा mvneta_pcpu_stats *stats;

				pr_err("Can't refill queue %d. Done %d from %d\n",
				       rxq->id, i, rxq->refill_num);

				stats = this_cpu_ptr(pp->stats);
				u64_stats_update_begin(&stats->syncp);
				stats->es.refill_error++;
				u64_stats_update_end(&stats->syncp);
				अवरोध;
			पूर्ण
		पूर्ण
		curr_desc = MVNETA_QUEUE_NEXT_DESC(rxq, curr_desc);
	पूर्ण
	rxq->refill_num -= i;
	rxq->first_to_refill = curr_desc;

	वापस i;
पूर्ण

अटल व्योम
mvneta_xdp_put_buff(काष्ठा mvneta_port *pp, काष्ठा mvneta_rx_queue *rxq,
		    काष्ठा xdp_buff *xdp, काष्ठा skb_shared_info *sinfo,
		    पूर्णांक sync_len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sinfo->nr_frags; i++)
		page_pool_put_full_page(rxq->page_pool,
					skb_frag_page(&sinfo->frags[i]), true);
	page_pool_put_page(rxq->page_pool, virt_to_head_page(xdp->data),
			   sync_len, true);
पूर्ण

अटल पूर्णांक
mvneta_xdp_submit_frame(काष्ठा mvneta_port *pp, काष्ठा mvneta_tx_queue *txq,
			काष्ठा xdp_frame *xdpf, bool dma_map)
अणु
	काष्ठा mvneta_tx_desc *tx_desc;
	काष्ठा mvneta_tx_buf *buf;
	dma_addr_t dma_addr;

	अगर (txq->count >= txq->tx_stop_threshold)
		वापस MVNETA_XDP_DROPPED;

	tx_desc = mvneta_txq_next_desc_get(txq);

	buf = &txq->buf[txq->txq_put_index];
	अगर (dma_map) अणु
		/* nकरो_xdp_xmit */
		dma_addr = dma_map_single(pp->dev->dev.parent, xdpf->data,
					  xdpf->len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(pp->dev->dev.parent, dma_addr)) अणु
			mvneta_txq_desc_put(txq);
			वापस MVNETA_XDP_DROPPED;
		पूर्ण
		buf->type = MVNETA_TYPE_XDP_NDO;
	पूर्ण अन्यथा अणु
		काष्ठा page *page = virt_to_page(xdpf->data);

		dma_addr = page_pool_get_dma_addr(page) +
			   माप(*xdpf) + xdpf->headroom;
		dma_sync_single_क्रम_device(pp->dev->dev.parent, dma_addr,
					   xdpf->len, DMA_BIसूचीECTIONAL);
		buf->type = MVNETA_TYPE_XDP_TX;
	पूर्ण
	buf->xdpf = xdpf;

	tx_desc->command = MVNETA_TXD_FLZ_DESC;
	tx_desc->buf_phys_addr = dma_addr;
	tx_desc->data_size = xdpf->len;

	mvneta_txq_inc_put(txq);
	txq->pending++;
	txq->count++;

	वापस MVNETA_XDP_TX;
पूर्ण

अटल पूर्णांक
mvneta_xdp_xmit_back(काष्ठा mvneta_port *pp, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);
	काष्ठा mvneta_tx_queue *txq;
	काष्ठा netdev_queue *nq;
	काष्ठा xdp_frame *xdpf;
	पूर्णांक cpu;
	u32 ret;

	xdpf = xdp_convert_buff_to_frame(xdp);
	अगर (unlikely(!xdpf))
		वापस MVNETA_XDP_DROPPED;

	cpu = smp_processor_id();
	txq = &pp->txqs[cpu % txq_number];
	nq = netdev_get_tx_queue(pp->dev, txq->id);

	__netअगर_tx_lock(nq, cpu);
	ret = mvneta_xdp_submit_frame(pp, txq, xdpf, false);
	अगर (ret == MVNETA_XDP_TX) अणु
		u64_stats_update_begin(&stats->syncp);
		stats->es.ps.tx_bytes += xdpf->len;
		stats->es.ps.tx_packets++;
		stats->es.ps.xdp_tx++;
		u64_stats_update_end(&stats->syncp);

		mvneta_txq_pend_desc_add(pp, txq, 0);
	पूर्ण अन्यथा अणु
		u64_stats_update_begin(&stats->syncp);
		stats->es.ps.xdp_tx_err++;
		u64_stats_update_end(&stats->syncp);
	पूर्ण
	__netअगर_tx_unlock(nq);

	वापस ret;
पूर्ण

अटल पूर्णांक
mvneta_xdp_xmit(काष्ठा net_device *dev, पूर्णांक num_frame,
		काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	काष्ठा mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);
	पूर्णांक i, nxmit_byte = 0, nxmit = 0;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा mvneta_tx_queue *txq;
	काष्ठा netdev_queue *nq;
	u32 ret;

	अगर (unlikely(test_bit(__MVNETA_DOWN, &pp->state)))
		वापस -ENETDOWN;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	txq = &pp->txqs[cpu % txq_number];
	nq = netdev_get_tx_queue(pp->dev, txq->id);

	__netअगर_tx_lock(nq, cpu);
	क्रम (i = 0; i < num_frame; i++) अणु
		ret = mvneta_xdp_submit_frame(pp, txq, frames[i], true);
		अगर (ret != MVNETA_XDP_TX)
			अवरोध;

		nxmit_byte += frames[i]->len;
		nxmit++;
	पूर्ण

	अगर (unlikely(flags & XDP_XMIT_FLUSH))
		mvneta_txq_pend_desc_add(pp, txq, 0);
	__netअगर_tx_unlock(nq);

	u64_stats_update_begin(&stats->syncp);
	stats->es.ps.tx_bytes += nxmit_byte;
	stats->es.ps.tx_packets += nxmit;
	stats->es.ps.xdp_xmit += nxmit;
	stats->es.ps.xdp_xmit_err += num_frame - nxmit;
	u64_stats_update_end(&stats->syncp);

	वापस nxmit;
पूर्ण

अटल पूर्णांक
mvneta_run_xdp(काष्ठा mvneta_port *pp, काष्ठा mvneta_rx_queue *rxq,
	       काष्ठा bpf_prog *prog, काष्ठा xdp_buff *xdp,
	       u32 frame_sz, काष्ठा mvneta_stats *stats)
अणु
	काष्ठा skb_shared_info *sinfo = xdp_get_shared_info_from_buff(xdp);
	अचिन्हित पूर्णांक len, data_len, sync;
	u32 ret, act;

	len = xdp->data_end - xdp->data_hard_start - pp->rx_offset_correction;
	data_len = xdp->data_end - xdp->data;
	act = bpf_prog_run_xdp(prog, xdp);

	/* Due xdp_adjust_tail: DMA sync क्रम_device cover max len CPU touch */
	sync = xdp->data_end - xdp->data_hard_start - pp->rx_offset_correction;
	sync = max(sync, len);

	चयन (act) अणु
	हाल XDP_PASS:
		stats->xdp_pass++;
		वापस MVNETA_XDP_PASS;
	हाल XDP_REसूचीECT: अणु
		पूर्णांक err;

		err = xdp_करो_redirect(pp->dev, xdp, prog);
		अगर (unlikely(err)) अणु
			mvneta_xdp_put_buff(pp, rxq, xdp, sinfo, sync);
			ret = MVNETA_XDP_DROPPED;
		पूर्ण अन्यथा अणु
			ret = MVNETA_XDP_REसूची;
			stats->xdp_redirect++;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल XDP_TX:
		ret = mvneta_xdp_xmit_back(pp, xdp);
		अगर (ret != MVNETA_XDP_TX)
			mvneta_xdp_put_buff(pp, rxq, xdp, sinfo, sync);
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(pp->dev, prog, act);
		fallthrough;
	हाल XDP_DROP:
		mvneta_xdp_put_buff(pp, rxq, xdp, sinfo, sync);
		ret = MVNETA_XDP_DROPPED;
		stats->xdp_drop++;
		अवरोध;
	पूर्ण

	stats->rx_bytes += frame_sz + xdp->data_end - xdp->data - data_len;
	stats->rx_packets++;

	वापस ret;
पूर्ण

अटल व्योम
mvneta_swbm_rx_frame(काष्ठा mvneta_port *pp,
		     काष्ठा mvneta_rx_desc *rx_desc,
		     काष्ठा mvneta_rx_queue *rxq,
		     काष्ठा xdp_buff *xdp, पूर्णांक *size,
		     काष्ठा page *page)
अणु
	अचिन्हित अक्षर *data = page_address(page);
	पूर्णांक data_len = -MVNETA_MH_SIZE, len;
	काष्ठा net_device *dev = pp->dev;
	क्रमागत dma_data_direction dma_dir;
	काष्ठा skb_shared_info *sinfo;

	अगर (*size > MVNETA_MAX_RX_BUF_SIZE) अणु
		len = MVNETA_MAX_RX_BUF_SIZE;
		data_len += len;
	पूर्ण अन्यथा अणु
		len = *size;
		data_len += len - ETH_FCS_LEN;
	पूर्ण
	*size = *size - len;

	dma_dir = page_pool_get_dma_dir(rxq->page_pool);
	dma_sync_single_क्रम_cpu(dev->dev.parent,
				rx_desc->buf_phys_addr,
				len, dma_dir);

	rx_desc->buf_phys_addr = 0;

	/* Prefetch header */
	prefetch(data);
	xdp_prepare_buff(xdp, data, pp->rx_offset_correction + MVNETA_MH_SIZE,
			 data_len, false);

	sinfo = xdp_get_shared_info_from_buff(xdp);
	sinfo->nr_frags = 0;
पूर्ण

अटल व्योम
mvneta_swbm_add_rx_fragment(काष्ठा mvneta_port *pp,
			    काष्ठा mvneta_rx_desc *rx_desc,
			    काष्ठा mvneta_rx_queue *rxq,
			    काष्ठा xdp_buff *xdp, पूर्णांक *size,
			    काष्ठा skb_shared_info *xdp_sinfo,
			    काष्ठा page *page)
अणु
	काष्ठा net_device *dev = pp->dev;
	क्रमागत dma_data_direction dma_dir;
	पूर्णांक data_len, len;

	अगर (*size > MVNETA_MAX_RX_BUF_SIZE) अणु
		len = MVNETA_MAX_RX_BUF_SIZE;
		data_len = len;
	पूर्ण अन्यथा अणु
		len = *size;
		data_len = len - ETH_FCS_LEN;
	पूर्ण
	dma_dir = page_pool_get_dma_dir(rxq->page_pool);
	dma_sync_single_क्रम_cpu(dev->dev.parent,
				rx_desc->buf_phys_addr,
				len, dma_dir);
	rx_desc->buf_phys_addr = 0;

	अगर (data_len > 0 && xdp_sinfo->nr_frags < MAX_SKB_FRAGS) अणु
		skb_frag_t *frag = &xdp_sinfo->frags[xdp_sinfo->nr_frags++];

		skb_frag_off_set(frag, pp->rx_offset_correction);
		skb_frag_size_set(frag, data_len);
		__skb_frag_set_page(frag, page);

		/* last fragment */
		अगर (len == *size) अणु
			काष्ठा skb_shared_info *sinfo;

			sinfo = xdp_get_shared_info_from_buff(xdp);
			sinfo->nr_frags = xdp_sinfo->nr_frags;
			स_नकल(sinfo->frags, xdp_sinfo->frags,
			       sinfo->nr_frags * माप(skb_frag_t));
		पूर्ण
	पूर्ण अन्यथा अणु
		page_pool_put_full_page(rxq->page_pool, page, true);
	पूर्ण
	*size -= len;
पूर्ण

अटल काष्ठा sk_buff *
mvneta_swbm_build_skb(काष्ठा mvneta_port *pp, काष्ठा mvneta_rx_queue *rxq,
		      काष्ठा xdp_buff *xdp, u32 desc_status)
अणु
	काष्ठा skb_shared_info *sinfo = xdp_get_shared_info_from_buff(xdp);
	पूर्णांक i, num_frags = sinfo->nr_frags;
	काष्ठा sk_buff *skb;

	skb = build_skb(xdp->data_hard_start, PAGE_SIZE);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	page_pool_release_page(rxq->page_pool, virt_to_page(xdp->data));

	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	skb_put(skb, xdp->data_end - xdp->data);
	mvneta_rx_csum(pp, desc_status, skb);

	क्रम (i = 0; i < num_frags; i++) अणु
		skb_frag_t *frag = &sinfo->frags[i];

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				skb_frag_page(frag), skb_frag_off(frag),
				skb_frag_size(frag), PAGE_SIZE);
		page_pool_release_page(rxq->page_pool, skb_frag_page(frag));
	पूर्ण

	वापस skb;
पूर्ण

/* Main rx processing when using software buffer management */
अटल पूर्णांक mvneta_rx_swbm(काष्ठा napi_काष्ठा *napi,
			  काष्ठा mvneta_port *pp, पूर्णांक budget,
			  काष्ठा mvneta_rx_queue *rxq)
अणु
	पूर्णांक rx_proc = 0, rx_toकरो, refill, size = 0;
	काष्ठा net_device *dev = pp->dev;
	काष्ठा skb_shared_info sinfo;
	काष्ठा mvneta_stats ps = अणुपूर्ण;
	काष्ठा bpf_prog *xdp_prog;
	u32 desc_status, frame_sz;
	काष्ठा xdp_buff xdp_buf;

	xdp_init_buff(&xdp_buf, PAGE_SIZE, &rxq->xdp_rxq);
	xdp_buf.data_hard_start = शून्य;

	sinfo.nr_frags = 0;

	/* Get number of received packets */
	rx_toकरो = mvneta_rxq_busy_desc_num_get(pp, rxq);

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(pp->xdp_prog);

	/* Fairness NAPI loop */
	जबतक (rx_proc < budget && rx_proc < rx_toकरो) अणु
		काष्ठा mvneta_rx_desc *rx_desc = mvneta_rxq_next_desc_get(rxq);
		u32 rx_status, index;
		काष्ठा sk_buff *skb;
		काष्ठा page *page;

		index = rx_desc - rxq->descs;
		page = (काष्ठा page *)rxq->buf_virt_addr[index];

		rx_status = rx_desc->status;
		rx_proc++;
		rxq->refill_num++;

		अगर (rx_status & MVNETA_RXD_FIRST_DESC) अणु
			/* Check errors only क्रम FIRST descriptor */
			अगर (rx_status & MVNETA_RXD_ERR_SUMMARY) अणु
				mvneta_rx_error(pp, rx_desc);
				जाओ next;
			पूर्ण

			size = rx_desc->data_size;
			frame_sz = size - ETH_FCS_LEN;
			desc_status = rx_status;

			mvneta_swbm_rx_frame(pp, rx_desc, rxq, &xdp_buf,
					     &size, page);
		पूर्ण अन्यथा अणु
			अगर (unlikely(!xdp_buf.data_hard_start)) अणु
				rx_desc->buf_phys_addr = 0;
				page_pool_put_full_page(rxq->page_pool, page,
							true);
				जाओ next;
			पूर्ण

			mvneta_swbm_add_rx_fragment(pp, rx_desc, rxq, &xdp_buf,
						    &size, &sinfo, page);
		पूर्ण /* Middle or Last descriptor */

		अगर (!(rx_status & MVNETA_RXD_LAST_DESC))
			/* no last descriptor this समय */
			जारी;

		अगर (size) अणु
			mvneta_xdp_put_buff(pp, rxq, &xdp_buf, &sinfo, -1);
			जाओ next;
		पूर्ण

		अगर (xdp_prog &&
		    mvneta_run_xdp(pp, rxq, xdp_prog, &xdp_buf, frame_sz, &ps))
			जाओ next;

		skb = mvneta_swbm_build_skb(pp, rxq, &xdp_buf, desc_status);
		अगर (IS_ERR(skb)) अणु
			काष्ठा mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);

			mvneta_xdp_put_buff(pp, rxq, &xdp_buf, &sinfo, -1);

			u64_stats_update_begin(&stats->syncp);
			stats->es.skb_alloc_error++;
			stats->rx_dropped++;
			u64_stats_update_end(&stats->syncp);

			जाओ next;
		पूर्ण

		ps.rx_bytes += skb->len;
		ps.rx_packets++;

		skb->protocol = eth_type_trans(skb, dev);
		napi_gro_receive(napi, skb);
next:
		xdp_buf.data_hard_start = शून्य;
		sinfo.nr_frags = 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (xdp_buf.data_hard_start)
		mvneta_xdp_put_buff(pp, rxq, &xdp_buf, &sinfo, -1);

	अगर (ps.xdp_redirect)
		xdp_करो_flush_map();

	अगर (ps.rx_packets)
		mvneta_update_stats(pp, &ps);

	/* वापस some buffers to hardware queue, one at a समय is too slow */
	refill = mvneta_rx_refill_queue(pp, rxq);

	/* Update rxq management counters */
	mvneta_rxq_desc_num_update(pp, rxq, rx_proc, refill);

	वापस ps.rx_packets;
पूर्ण

/* Main rx processing when using hardware buffer management */
अटल पूर्णांक mvneta_rx_hwbm(काष्ठा napi_काष्ठा *napi,
			  काष्ठा mvneta_port *pp, पूर्णांक rx_toकरो,
			  काष्ठा mvneta_rx_queue *rxq)
अणु
	काष्ठा net_device *dev = pp->dev;
	पूर्णांक rx_करोne;
	u32 rcvd_pkts = 0;
	u32 rcvd_bytes = 0;

	/* Get number of received packets */
	rx_करोne = mvneta_rxq_busy_desc_num_get(pp, rxq);

	अगर (rx_toकरो > rx_करोne)
		rx_toकरो = rx_करोne;

	rx_करोne = 0;

	/* Fairness NAPI loop */
	जबतक (rx_करोne < rx_toकरो) अणु
		काष्ठा mvneta_rx_desc *rx_desc = mvneta_rxq_next_desc_get(rxq);
		काष्ठा mvneta_bm_pool *bm_pool = शून्य;
		काष्ठा sk_buff *skb;
		अचिन्हित अक्षर *data;
		dma_addr_t phys_addr;
		u32 rx_status, frag_size;
		पूर्णांक rx_bytes, err;
		u8 pool_id;

		rx_करोne++;
		rx_status = rx_desc->status;
		rx_bytes = rx_desc->data_size - (ETH_FCS_LEN + MVNETA_MH_SIZE);
		data = (u8 *)(uपूर्णांकptr_t)rx_desc->buf_cookie;
		phys_addr = rx_desc->buf_phys_addr;
		pool_id = MVNETA_RX_GET_BM_POOL_ID(rx_desc);
		bm_pool = &pp->bm_priv->bm_pools[pool_id];

		अगर (!mvneta_rxq_desc_is_first_last(rx_status) ||
		    (rx_status & MVNETA_RXD_ERR_SUMMARY)) अणु
err_drop_frame_ret_pool:
			/* Return the buffer to the pool */
			mvneta_bm_pool_put_bp(pp->bm_priv, bm_pool,
					      rx_desc->buf_phys_addr);
err_drop_frame:
			mvneta_rx_error(pp, rx_desc);
			/* leave the descriptor untouched */
			जारी;
		पूर्ण

		अगर (rx_bytes <= rx_copyअवरोध) अणु
			/* better copy a small frame and not unmap the DMA region */
			skb = netdev_alloc_skb_ip_align(dev, rx_bytes);
			अगर (unlikely(!skb))
				जाओ err_drop_frame_ret_pool;

			dma_sync_single_range_क्रम_cpu(&pp->bm_priv->pdev->dev,
			                              rx_desc->buf_phys_addr,
			                              MVNETA_MH_SIZE + NET_SKB_PAD,
			                              rx_bytes,
			                              DMA_FROM_DEVICE);
			skb_put_data(skb, data + MVNETA_MH_SIZE + NET_SKB_PAD,
				     rx_bytes);

			skb->protocol = eth_type_trans(skb, dev);
			mvneta_rx_csum(pp, rx_status, skb);
			napi_gro_receive(napi, skb);

			rcvd_pkts++;
			rcvd_bytes += rx_bytes;

			/* Return the buffer to the pool */
			mvneta_bm_pool_put_bp(pp->bm_priv, bm_pool,
					      rx_desc->buf_phys_addr);

			/* leave the descriptor and buffer untouched */
			जारी;
		पूर्ण

		/* Refill processing */
		err = hwbm_pool_refill(&bm_pool->hwbm_pool, GFP_ATOMIC);
		अगर (err) अणु
			काष्ठा mvneta_pcpu_stats *stats;

			netdev_err(dev, "Linux processing - Can't refill\n");

			stats = this_cpu_ptr(pp->stats);
			u64_stats_update_begin(&stats->syncp);
			stats->es.refill_error++;
			u64_stats_update_end(&stats->syncp);

			जाओ err_drop_frame_ret_pool;
		पूर्ण

		frag_size = bm_pool->hwbm_pool.frag_size;

		skb = build_skb(data, frag_size > PAGE_SIZE ? 0 : frag_size);

		/* After refill old buffer has to be unmapped regardless
		 * the skb is successfully built or not.
		 */
		dma_unmap_single(&pp->bm_priv->pdev->dev, phys_addr,
				 bm_pool->buf_size, DMA_FROM_DEVICE);
		अगर (!skb)
			जाओ err_drop_frame;

		rcvd_pkts++;
		rcvd_bytes += rx_bytes;

		/* Linux processing */
		skb_reserve(skb, MVNETA_MH_SIZE + NET_SKB_PAD);
		skb_put(skb, rx_bytes);

		skb->protocol = eth_type_trans(skb, dev);

		mvneta_rx_csum(pp, rx_status, skb);

		napi_gro_receive(napi, skb);
	पूर्ण

	अगर (rcvd_pkts) अणु
		काष्ठा mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);

		u64_stats_update_begin(&stats->syncp);
		stats->es.ps.rx_packets += rcvd_pkts;
		stats->es.ps.rx_bytes += rcvd_bytes;
		u64_stats_update_end(&stats->syncp);
	पूर्ण

	/* Update rxq management counters */
	mvneta_rxq_desc_num_update(pp, rxq, rx_करोne, rx_करोne);

	वापस rx_करोne;
पूर्ण

अटल अंतरभूत व्योम
mvneta_tso_put_hdr(काष्ठा sk_buff *skb,
		   काष्ठा mvneta_port *pp, काष्ठा mvneta_tx_queue *txq)
अणु
	पूर्णांक hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	काष्ठा mvneta_tx_buf *buf = &txq->buf[txq->txq_put_index];
	काष्ठा mvneta_tx_desc *tx_desc;

	tx_desc = mvneta_txq_next_desc_get(txq);
	tx_desc->data_size = hdr_len;
	tx_desc->command = mvneta_skb_tx_csum(pp, skb);
	tx_desc->command |= MVNETA_TXD_F_DESC;
	tx_desc->buf_phys_addr = txq->tso_hdrs_phys +
				 txq->txq_put_index * TSO_HEADER_SIZE;
	buf->type = MVNETA_TYPE_SKB;
	buf->skb = शून्य;

	mvneta_txq_inc_put(txq);
पूर्ण

अटल अंतरभूत पूर्णांक
mvneta_tso_put_data(काष्ठा net_device *dev, काष्ठा mvneta_tx_queue *txq,
		    काष्ठा sk_buff *skb, अक्षर *data, पूर्णांक size,
		    bool last_tcp, bool is_last)
अणु
	काष्ठा mvneta_tx_buf *buf = &txq->buf[txq->txq_put_index];
	काष्ठा mvneta_tx_desc *tx_desc;

	tx_desc = mvneta_txq_next_desc_get(txq);
	tx_desc->data_size = size;
	tx_desc->buf_phys_addr = dma_map_single(dev->dev.parent, data,
						size, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev->dev.parent,
		     tx_desc->buf_phys_addr))) अणु
		mvneta_txq_desc_put(txq);
		वापस -ENOMEM;
	पूर्ण

	tx_desc->command = 0;
	buf->type = MVNETA_TYPE_SKB;
	buf->skb = शून्य;

	अगर (last_tcp) अणु
		/* last descriptor in the TCP packet */
		tx_desc->command = MVNETA_TXD_L_DESC;

		/* last descriptor in SKB */
		अगर (is_last)
			buf->skb = skb;
	पूर्ण
	mvneta_txq_inc_put(txq);
	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_tx_tso(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			 काष्ठा mvneta_tx_queue *txq)
अणु
	पूर्णांक hdr_len, total_len, data_left;
	पूर्णांक desc_count = 0;
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	काष्ठा tso_t tso;
	पूर्णांक i;

	/* Count needed descriptors */
	अगर ((txq->count + tso_count_descs(skb)) >= txq->size)
		वापस 0;

	अगर (skb_headlen(skb) < (skb_transport_offset(skb) + tcp_hdrlen(skb))) अणु
		pr_info("*** Is this even  possible???!?!?\n");
		वापस 0;
	पूर्ण

	/* Initialize the TSO handler, and prepare the first payload */
	hdr_len = tso_start(skb, &tso);

	total_len = skb->len - hdr_len;
	जबतक (total_len > 0) अणु
		अक्षर *hdr;

		data_left = min_t(पूर्णांक, skb_shinfo(skb)->gso_size, total_len);
		total_len -= data_left;
		desc_count++;

		/* prepare packet headers: MAC + IP + TCP */
		hdr = txq->tso_hdrs + txq->txq_put_index * TSO_HEADER_SIZE;
		tso_build_hdr(skb, hdr, &tso, data_left, total_len == 0);

		mvneta_tso_put_hdr(skb, pp, txq);

		जबतक (data_left > 0) अणु
			पूर्णांक size;
			desc_count++;

			size = min_t(पूर्णांक, tso.size, data_left);

			अगर (mvneta_tso_put_data(dev, txq, skb,
						 tso.data, size,
						 size == data_left,
						 total_len == 0))
				जाओ err_release;
			data_left -= size;

			tso_build_data(skb, &tso, size);
		पूर्ण
	पूर्ण

	वापस desc_count;

err_release:
	/* Release all used data descriptors; header descriptors must not
	 * be DMA-unmapped.
	 */
	क्रम (i = desc_count - 1; i >= 0; i--) अणु
		काष्ठा mvneta_tx_desc *tx_desc = txq->descs + i;
		अगर (!IS_TSO_HEADER(txq, tx_desc->buf_phys_addr))
			dma_unmap_single(pp->dev->dev.parent,
					 tx_desc->buf_phys_addr,
					 tx_desc->data_size,
					 DMA_TO_DEVICE);
		mvneta_txq_desc_put(txq);
	पूर्ण
	वापस 0;
पूर्ण

/* Handle tx fragmentation processing */
अटल पूर्णांक mvneta_tx_frag_process(काष्ठा mvneta_port *pp, काष्ठा sk_buff *skb,
				  काष्ठा mvneta_tx_queue *txq)
अणु
	काष्ठा mvneta_tx_desc *tx_desc;
	पूर्णांक i, nr_frags = skb_shinfo(skb)->nr_frags;

	क्रम (i = 0; i < nr_frags; i++) अणु
		काष्ठा mvneta_tx_buf *buf = &txq->buf[txq->txq_put_index];
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		व्योम *addr = skb_frag_address(frag);

		tx_desc = mvneta_txq_next_desc_get(txq);
		tx_desc->data_size = skb_frag_size(frag);

		tx_desc->buf_phys_addr =
			dma_map_single(pp->dev->dev.parent, addr,
				       tx_desc->data_size, DMA_TO_DEVICE);

		अगर (dma_mapping_error(pp->dev->dev.parent,
				      tx_desc->buf_phys_addr)) अणु
			mvneta_txq_desc_put(txq);
			जाओ error;
		पूर्ण

		अगर (i == nr_frags - 1) अणु
			/* Last descriptor */
			tx_desc->command = MVNETA_TXD_L_DESC | MVNETA_TXD_Z_PAD;
			buf->skb = skb;
		पूर्ण अन्यथा अणु
			/* Descriptor in the middle: Not First, Not Last */
			tx_desc->command = 0;
			buf->skb = शून्य;
		पूर्ण
		buf->type = MVNETA_TYPE_SKB;
		mvneta_txq_inc_put(txq);
	पूर्ण

	वापस 0;

error:
	/* Release all descriptors that were used to map fragments of
	 * this packet, as well as the corresponding DMA mappings
	 */
	क्रम (i = i - 1; i >= 0; i--) अणु
		tx_desc = txq->descs + i;
		dma_unmap_single(pp->dev->dev.parent,
				 tx_desc->buf_phys_addr,
				 tx_desc->data_size,
				 DMA_TO_DEVICE);
		mvneta_txq_desc_put(txq);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

/* Main tx processing */
अटल netdev_tx_t mvneta_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	u16 txq_id = skb_get_queue_mapping(skb);
	काष्ठा mvneta_tx_queue *txq = &pp->txqs[txq_id];
	काष्ठा mvneta_tx_buf *buf = &txq->buf[txq->txq_put_index];
	काष्ठा mvneta_tx_desc *tx_desc;
	पूर्णांक len = skb->len;
	पूर्णांक frags = 0;
	u32 tx_cmd;

	अगर (!netअगर_running(dev))
		जाओ out;

	अगर (skb_is_gso(skb)) अणु
		frags = mvneta_tx_tso(skb, dev, txq);
		जाओ out;
	पूर्ण

	frags = skb_shinfo(skb)->nr_frags + 1;

	/* Get a descriptor क्रम the first part of the packet */
	tx_desc = mvneta_txq_next_desc_get(txq);

	tx_cmd = mvneta_skb_tx_csum(pp, skb);

	tx_desc->data_size = skb_headlen(skb);

	tx_desc->buf_phys_addr = dma_map_single(dev->dev.parent, skb->data,
						tx_desc->data_size,
						DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev->dev.parent,
				       tx_desc->buf_phys_addr))) अणु
		mvneta_txq_desc_put(txq);
		frags = 0;
		जाओ out;
	पूर्ण

	buf->type = MVNETA_TYPE_SKB;
	अगर (frags == 1) अणु
		/* First and Last descriptor */
		tx_cmd |= MVNETA_TXD_FLZ_DESC;
		tx_desc->command = tx_cmd;
		buf->skb = skb;
		mvneta_txq_inc_put(txq);
	पूर्ण अन्यथा अणु
		/* First but not Last */
		tx_cmd |= MVNETA_TXD_F_DESC;
		buf->skb = शून्य;
		mvneta_txq_inc_put(txq);
		tx_desc->command = tx_cmd;
		/* Continue with other skb fragments */
		अगर (mvneta_tx_frag_process(pp, skb, txq)) अणु
			dma_unmap_single(dev->dev.parent,
					 tx_desc->buf_phys_addr,
					 tx_desc->data_size,
					 DMA_TO_DEVICE);
			mvneta_txq_desc_put(txq);
			frags = 0;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (frags > 0) अणु
		काष्ठा netdev_queue *nq = netdev_get_tx_queue(dev, txq_id);
		काष्ठा mvneta_pcpu_stats *stats = this_cpu_ptr(pp->stats);

		netdev_tx_sent_queue(nq, len);

		txq->count += frags;
		अगर (txq->count >= txq->tx_stop_threshold)
			netअगर_tx_stop_queue(nq);

		अगर (!netdev_xmit_more() || netअगर_xmit_stopped(nq) ||
		    txq->pending + frags > MVNETA_TXQ_DEC_SENT_MASK)
			mvneta_txq_pend_desc_add(pp, txq, frags);
		अन्यथा
			txq->pending += frags;

		u64_stats_update_begin(&stats->syncp);
		stats->es.ps.tx_bytes += len;
		stats->es.ps.tx_packets++;
		u64_stats_update_end(&stats->syncp);
	पूर्ण अन्यथा अणु
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण


/* Free tx resources, when resetting a port */
अटल व्योम mvneta_txq_करोne_क्रमce(काष्ठा mvneta_port *pp,
				  काष्ठा mvneta_tx_queue *txq)

अणु
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(pp->dev, txq->id);
	पूर्णांक tx_करोne = txq->count;

	mvneta_txq_bufs_मुक्त(pp, txq, tx_करोne, nq, false);

	/* reset txq */
	txq->count = 0;
	txq->txq_put_index = 0;
	txq->txq_get_index = 0;
पूर्ण

/* Handle tx करोne - called in softirq context. The <cause_tx_करोne> argument
 * must be a valid cause according to MVNETA_TXQ_INTR_MASK_ALL.
 */
अटल व्योम mvneta_tx_करोne_gbe(काष्ठा mvneta_port *pp, u32 cause_tx_करोne)
अणु
	काष्ठा mvneta_tx_queue *txq;
	काष्ठा netdev_queue *nq;
	पूर्णांक cpu = smp_processor_id();

	जबतक (cause_tx_करोne) अणु
		txq = mvneta_tx_करोne_policy(pp, cause_tx_करोne);

		nq = netdev_get_tx_queue(pp->dev, txq->id);
		__netअगर_tx_lock(nq, cpu);

		अगर (txq->count)
			mvneta_txq_करोne(pp, txq);

		__netअगर_tx_unlock(nq);
		cause_tx_करोne &= ~((1 << txq->id));
	पूर्ण
पूर्ण

/* Compute crc8 of the specअगरied address, using a unique algorithm ,
 * according to hw spec, dअगरferent than generic crc8 algorithm
 */
अटल पूर्णांक mvneta_addr_crc(अचिन्हित अक्षर *addr)
अणु
	पूर्णांक crc = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		पूर्णांक j;

		crc = (crc ^ addr[i]) << 8;
		क्रम (j = 7; j >= 0; j--) अणु
			अगर (crc & (0x100 << j))
				crc ^= 0x107 << j;
		पूर्ण
	पूर्ण

	वापस crc;
पूर्ण

/* This method controls the net device special MAC multicast support.
 * The Special Multicast Table क्रम MAC addresses supports MAC of the क्रमm
 * 0x01-00-5E-00-00-XX (where XX is between 0x00 and 0xFF).
 * The MAC DA[7:0] bits are used as a poपूर्णांकer to the Special Multicast
 * Table entries in the DA-Filter table. This method set the Special
 * Multicast Table appropriate entry.
 */
अटल व्योम mvneta_set_special_mcast_addr(काष्ठा mvneta_port *pp,
					  अचिन्हित अक्षर last_byte,
					  पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक smc_table_reg;
	अचिन्हित पूर्णांक tbl_offset;
	अचिन्हित पूर्णांक reg_offset;

	/* Register offset from SMC table base    */
	tbl_offset = (last_byte / 4);
	/* Entry offset within the above reg */
	reg_offset = last_byte % 4;

	smc_table_reg = mvreg_पढ़ो(pp, (MVNETA_DA_FILT_SPEC_MCAST
					+ tbl_offset * 4));

	अगर (queue == -1)
		smc_table_reg &= ~(0xff << (8 * reg_offset));
	अन्यथा अणु
		smc_table_reg &= ~(0xff << (8 * reg_offset));
		smc_table_reg |= ((0x01 | (queue << 1)) << (8 * reg_offset));
	पूर्ण

	mvreg_ग_लिखो(pp, MVNETA_DA_FILT_SPEC_MCAST + tbl_offset * 4,
		    smc_table_reg);
पूर्ण

/* This method controls the network device Other MAC multicast support.
 * The Other Multicast Table is used क्रम multicast of another type.
 * A CRC-8 is used as an index to the Other Multicast Table entries
 * in the DA-Filter table.
 * The method माला_लो the CRC-8 value from the calling routine and
 * sets the Other Multicast Table appropriate entry according to the
 * specअगरied CRC-8 .
 */
अटल व्योम mvneta_set_other_mcast_addr(काष्ठा mvneta_port *pp,
					अचिन्हित अक्षर crc8,
					पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक omc_table_reg;
	अचिन्हित पूर्णांक tbl_offset;
	अचिन्हित पूर्णांक reg_offset;

	tbl_offset = (crc8 / 4) * 4; /* Register offset from OMC table base */
	reg_offset = crc8 % 4;	     /* Entry offset within the above reg   */

	omc_table_reg = mvreg_पढ़ो(pp, MVNETA_DA_FILT_OTH_MCAST + tbl_offset);

	अगर (queue == -1) अणु
		/* Clear accepts frame bit at specअगरied Other DA table entry */
		omc_table_reg &= ~(0xff << (8 * reg_offset));
	पूर्ण अन्यथा अणु
		omc_table_reg &= ~(0xff << (8 * reg_offset));
		omc_table_reg |= ((0x01 | (queue << 1)) << (8 * reg_offset));
	पूर्ण

	mvreg_ग_लिखो(pp, MVNETA_DA_FILT_OTH_MCAST + tbl_offset, omc_table_reg);
पूर्ण

/* The network device supports multicast using two tables:
 *    1) Special Multicast Table क्रम MAC addresses of the क्रमm
 *       0x01-00-5E-00-00-XX (where XX is between 0x00 and 0xFF).
 *       The MAC DA[7:0] bits are used as a poपूर्णांकer to the Special Multicast
 *       Table entries in the DA-Filter table.
 *    2) Other Multicast Table क्रम multicast of another type. A CRC-8 value
 *       is used as an index to the Other Multicast Table entries in the
 *       DA-Filter table.
 */
अटल पूर्णांक mvneta_mcast_addr_set(काष्ठा mvneta_port *pp, अचिन्हित अक्षर *p_addr,
				 पूर्णांक queue)
अणु
	अचिन्हित अक्षर crc_result = 0;

	अगर (स_भेद(p_addr, "\x01\x00\x5e\x00\x00", 5) == 0) अणु
		mvneta_set_special_mcast_addr(pp, p_addr[5], queue);
		वापस 0;
	पूर्ण

	crc_result = mvneta_addr_crc(p_addr);
	अगर (queue == -1) अणु
		अगर (pp->mcast_count[crc_result] == 0) अणु
			netdev_info(pp->dev, "No valid Mcast for crc8=0x%02x\n",
				    crc_result);
			वापस -EINVAL;
		पूर्ण

		pp->mcast_count[crc_result]--;
		अगर (pp->mcast_count[crc_result] != 0) अणु
			netdev_info(pp->dev,
				    "After delete there are %d valid Mcast for crc8=0x%02x\n",
				    pp->mcast_count[crc_result], crc_result);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		pp->mcast_count[crc_result]++;

	mvneta_set_other_mcast_addr(pp, crc_result, queue);

	वापस 0;
पूर्ण

/* Configure Fitering mode of Ethernet port */
अटल व्योम mvneta_rx_unicast_promisc_set(काष्ठा mvneta_port *pp,
					  पूर्णांक is_promisc)
अणु
	u32 port_cfg_reg, val;

	port_cfg_reg = mvreg_पढ़ो(pp, MVNETA_PORT_CONFIG);

	val = mvreg_पढ़ो(pp, MVNETA_TYPE_PRIO);

	/* Set / Clear UPM bit in port configuration रेजिस्टर */
	अगर (is_promisc) अणु
		/* Accept all Unicast addresses */
		port_cfg_reg |= MVNETA_UNI_PROMISC_MODE;
		val |= MVNETA_FORCE_UNI;
		mvreg_ग_लिखो(pp, MVNETA_MAC_ADDR_LOW, 0xffff);
		mvreg_ग_लिखो(pp, MVNETA_MAC_ADDR_HIGH, 0xffffffff);
	पूर्ण अन्यथा अणु
		/* Reject all Unicast addresses */
		port_cfg_reg &= ~MVNETA_UNI_PROMISC_MODE;
		val &= ~MVNETA_FORCE_UNI;
	पूर्ण

	mvreg_ग_लिखो(pp, MVNETA_PORT_CONFIG, port_cfg_reg);
	mvreg_ग_लिखो(pp, MVNETA_TYPE_PRIO, val);
पूर्ण

/* रेजिस्टर unicast and multicast addresses */
अटल व्योम mvneta_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;

	अगर (dev->flags & IFF_PROMISC) अणु
		/* Accept all: Multicast + Unicast */
		mvneta_rx_unicast_promisc_set(pp, 1);
		mvneta_set_ucast_table(pp, pp->rxq_def);
		mvneta_set_special_mcast_table(pp, pp->rxq_def);
		mvneta_set_other_mcast_table(pp, pp->rxq_def);
	पूर्ण अन्यथा अणु
		/* Accept single Unicast */
		mvneta_rx_unicast_promisc_set(pp, 0);
		mvneta_set_ucast_table(pp, -1);
		mvneta_mac_addr_set(pp, dev->dev_addr, pp->rxq_def);

		अगर (dev->flags & IFF_ALLMULTI) अणु
			/* Accept all multicast */
			mvneta_set_special_mcast_table(pp, pp->rxq_def);
			mvneta_set_other_mcast_table(pp, pp->rxq_def);
		पूर्ण अन्यथा अणु
			/* Accept only initialized multicast */
			mvneta_set_special_mcast_table(pp, -1);
			mvneta_set_other_mcast_table(pp, -1);

			अगर (!netdev_mc_empty(dev)) अणु
				netdev_क्रम_each_mc_addr(ha, dev) अणु
					mvneta_mcast_addr_set(pp, ha->addr,
							      pp->rxq_def);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Interrupt handling - the callback क्रम request_irq() */
अटल irqवापस_t mvneta_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mvneta_port *pp = (काष्ठा mvneta_port *)dev_id;

	mvreg_ग_लिखो(pp, MVNETA_INTR_NEW_MASK, 0);
	napi_schedule(&pp->napi);

	वापस IRQ_HANDLED;
पूर्ण

/* Interrupt handling - the callback क्रम request_percpu_irq() */
अटल irqवापस_t mvneta_percpu_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mvneta_pcpu_port *port = (काष्ठा mvneta_pcpu_port *)dev_id;

	disable_percpu_irq(port->pp->dev->irq);
	napi_schedule(&port->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mvneta_link_change(काष्ठा mvneta_port *pp)
अणु
	u32 gmac_stat = mvreg_पढ़ो(pp, MVNETA_GMAC_STATUS);

	phylink_mac_change(pp->phylink, !!(gmac_stat & MVNETA_GMAC_LINK_UP));
पूर्ण

/* NAPI handler
 * Bits 0 - 7 of the causeRxTx रेजिस्टर indicate that are transmitted
 * packets on the corresponding TXQ (Bit 0 is क्रम TX queue 1).
 * Bits 8 -15 of the cause Rx Tx रेजिस्टर indicate that are received
 * packets on the corresponding RXQ (Bit 8 is क्रम RX queue 0).
 * Each CPU has its own causeRxTx रेजिस्टर
 */
अटल पूर्णांक mvneta_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक rx_करोne = 0;
	u32 cause_rx_tx;
	पूर्णांक rx_queue;
	काष्ठा mvneta_port *pp = netdev_priv(napi->dev);
	काष्ठा mvneta_pcpu_port *port = this_cpu_ptr(pp->ports);

	अगर (!netअगर_running(pp->dev)) अणु
		napi_complete(napi);
		वापस rx_करोne;
	पूर्ण

	/* Read cause रेजिस्टर */
	cause_rx_tx = mvreg_पढ़ो(pp, MVNETA_INTR_NEW_CAUSE);
	अगर (cause_rx_tx & MVNETA_MISCINTR_INTR_MASK) अणु
		u32 cause_misc = mvreg_पढ़ो(pp, MVNETA_INTR_MISC_CAUSE);

		mvreg_ग_लिखो(pp, MVNETA_INTR_MISC_CAUSE, 0);

		अगर (cause_misc & (MVNETA_CAUSE_PHY_STATUS_CHANGE |
				  MVNETA_CAUSE_LINK_CHANGE))
			mvneta_link_change(pp);
	पूर्ण

	/* Release Tx descriptors */
	अगर (cause_rx_tx & MVNETA_TX_INTR_MASK_ALL) अणु
		mvneta_tx_करोne_gbe(pp, (cause_rx_tx & MVNETA_TX_INTR_MASK_ALL));
		cause_rx_tx &= ~MVNETA_TX_INTR_MASK_ALL;
	पूर्ण

	/* For the हाल where the last mvneta_poll did not process all
	 * RX packets
	 */
	cause_rx_tx |= pp->neta_armada3700 ? pp->cause_rx_tx :
		port->cause_rx_tx;

	rx_queue = fls(((cause_rx_tx >> 8) & 0xff));
	अगर (rx_queue) अणु
		rx_queue = rx_queue - 1;
		अगर (pp->bm_priv)
			rx_करोne = mvneta_rx_hwbm(napi, pp, budget,
						 &pp->rxqs[rx_queue]);
		अन्यथा
			rx_करोne = mvneta_rx_swbm(napi, pp, budget,
						 &pp->rxqs[rx_queue]);
	पूर्ण

	अगर (rx_करोne < budget) अणु
		cause_rx_tx = 0;
		napi_complete_करोne(napi, rx_करोne);

		अगर (pp->neta_armada3700) अणु
			अचिन्हित दीर्घ flags;

			local_irq_save(flags);
			mvreg_ग_लिखो(pp, MVNETA_INTR_NEW_MASK,
				    MVNETA_RX_INTR_MASK(rxq_number) |
				    MVNETA_TX_INTR_MASK(txq_number) |
				    MVNETA_MISCINTR_INTR_MASK);
			local_irq_restore(flags);
		पूर्ण अन्यथा अणु
			enable_percpu_irq(pp->dev->irq, 0);
		पूर्ण
	पूर्ण

	अगर (pp->neta_armada3700)
		pp->cause_rx_tx = cause_rx_tx;
	अन्यथा
		port->cause_rx_tx = cause_rx_tx;

	वापस rx_करोne;
पूर्ण

अटल पूर्णांक mvneta_create_page_pool(काष्ठा mvneta_port *pp,
				   काष्ठा mvneta_rx_queue *rxq, पूर्णांक size)
अणु
	काष्ठा bpf_prog *xdp_prog = READ_ONCE(pp->xdp_prog);
	काष्ठा page_pool_params pp_params = अणु
		.order = 0,
		.flags = PP_FLAG_DMA_MAP | PP_FLAG_DMA_SYNC_DEV,
		.pool_size = size,
		.nid = NUMA_NO_NODE,
		.dev = pp->dev->dev.parent,
		.dma_dir = xdp_prog ? DMA_BIसूचीECTIONAL : DMA_FROM_DEVICE,
		.offset = pp->rx_offset_correction,
		.max_len = MVNETA_MAX_RX_BUF_SIZE,
	पूर्ण;
	पूर्णांक err;

	rxq->page_pool = page_pool_create(&pp_params);
	अगर (IS_ERR(rxq->page_pool)) अणु
		err = PTR_ERR(rxq->page_pool);
		rxq->page_pool = शून्य;
		वापस err;
	पूर्ण

	err = xdp_rxq_info_reg(&rxq->xdp_rxq, pp->dev, rxq->id, 0);
	अगर (err < 0)
		जाओ err_मुक्त_pp;

	err = xdp_rxq_info_reg_mem_model(&rxq->xdp_rxq, MEM_TYPE_PAGE_POOL,
					 rxq->page_pool);
	अगर (err)
		जाओ err_unरेजिस्टर_rxq;

	वापस 0;

err_unरेजिस्टर_rxq:
	xdp_rxq_info_unreg(&rxq->xdp_rxq);
err_मुक्त_pp:
	page_pool_destroy(rxq->page_pool);
	rxq->page_pool = शून्य;
	वापस err;
पूर्ण

/* Handle rxq fill: allocates rxq skbs; called when initializing a port */
अटल पूर्णांक mvneta_rxq_fill(काष्ठा mvneta_port *pp, काष्ठा mvneta_rx_queue *rxq,
			   पूर्णांक num)
अणु
	पूर्णांक i, err;

	err = mvneta_create_page_pool(pp, rxq, num);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < num; i++) अणु
		स_रखो(rxq->descs + i, 0, माप(काष्ठा mvneta_rx_desc));
		अगर (mvneta_rx_refill(pp, rxq->descs + i, rxq,
				     GFP_KERNEL) != 0) अणु
			netdev_err(pp->dev,
				   "%s:rxq %d, %d of %d buffs  filled\n",
				   __func__, rxq->id, i, num);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Add this number of RX descriptors as non occupied (पढ़ोy to
	 * get packets)
	 */
	mvneta_rxq_non_occup_desc_add(pp, rxq, i);

	वापस i;
पूर्ण

/* Free all packets pending transmit from all TXQs and reset TX port */
अटल व्योम mvneta_tx_reset(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक queue;

	/* मुक्त the skb's in the tx ring */
	क्रम (queue = 0; queue < txq_number; queue++)
		mvneta_txq_करोne_क्रमce(pp, &pp->txqs[queue]);

	mvreg_ग_लिखो(pp, MVNETA_PORT_TX_RESET, MVNETA_PORT_TX_DMA_RESET);
	mvreg_ग_लिखो(pp, MVNETA_PORT_TX_RESET, 0);
पूर्ण

अटल व्योम mvneta_rx_reset(काष्ठा mvneta_port *pp)
अणु
	mvreg_ग_लिखो(pp, MVNETA_PORT_RX_RESET, MVNETA_PORT_RX_DMA_RESET);
	mvreg_ग_लिखो(pp, MVNETA_PORT_RX_RESET, 0);
पूर्ण

/* Rx/Tx queue initialization/cleanup methods */

अटल पूर्णांक mvneta_rxq_sw_init(काष्ठा mvneta_port *pp,
			      काष्ठा mvneta_rx_queue *rxq)
अणु
	rxq->size = pp->rx_ring_size;

	/* Allocate memory क्रम RX descriptors */
	rxq->descs = dma_alloc_coherent(pp->dev->dev.parent,
					rxq->size * MVNETA_DESC_ALIGNED_SIZE,
					&rxq->descs_phys, GFP_KERNEL);
	अगर (!rxq->descs)
		वापस -ENOMEM;

	rxq->last_desc = rxq->size - 1;

	वापस 0;
पूर्ण

अटल व्योम mvneta_rxq_hw_init(काष्ठा mvneta_port *pp,
			       काष्ठा mvneta_rx_queue *rxq)
अणु
	/* Set Rx descriptors queue starting address */
	mvreg_ग_लिखो(pp, MVNETA_RXQ_BASE_ADDR_REG(rxq->id), rxq->descs_phys);
	mvreg_ग_लिखो(pp, MVNETA_RXQ_SIZE_REG(rxq->id), rxq->size);

	/* Set coalescing pkts and समय */
	mvneta_rx_pkts_coal_set(pp, rxq, rxq->pkts_coal);
	mvneta_rx_समय_coal_set(pp, rxq, rxq->समय_coal);

	अगर (!pp->bm_priv) अणु
		/* Set Offset */
		mvneta_rxq_offset_set(pp, rxq, 0);
		mvneta_rxq_buf_size_set(pp, rxq, PAGE_SIZE < SZ_64K ?
					MVNETA_MAX_RX_BUF_SIZE :
					MVNETA_RX_BUF_SIZE(pp->pkt_size));
		mvneta_rxq_bm_disable(pp, rxq);
		mvneta_rxq_fill(pp, rxq, rxq->size);
	पूर्ण अन्यथा अणु
		/* Set Offset */
		mvneta_rxq_offset_set(pp, rxq,
				      NET_SKB_PAD - pp->rx_offset_correction);

		mvneta_rxq_bm_enable(pp, rxq);
		/* Fill RXQ with buffers from RX pool */
		mvneta_rxq_दीर्घ_pool_set(pp, rxq);
		mvneta_rxq_लघु_pool_set(pp, rxq);
		mvneta_rxq_non_occup_desc_add(pp, rxq, rxq->size);
	पूर्ण
पूर्ण

/* Create a specअगरied RX queue */
अटल पूर्णांक mvneta_rxq_init(काष्ठा mvneta_port *pp,
			   काष्ठा mvneta_rx_queue *rxq)

अणु
	पूर्णांक ret;

	ret = mvneta_rxq_sw_init(pp, rxq);
	अगर (ret < 0)
		वापस ret;

	mvneta_rxq_hw_init(pp, rxq);

	वापस 0;
पूर्ण

/* Cleanup Rx queue */
अटल व्योम mvneta_rxq_deinit(काष्ठा mvneta_port *pp,
			      काष्ठा mvneta_rx_queue *rxq)
अणु
	mvneta_rxq_drop_pkts(pp, rxq);

	अगर (rxq->descs)
		dma_मुक्त_coherent(pp->dev->dev.parent,
				  rxq->size * MVNETA_DESC_ALIGNED_SIZE,
				  rxq->descs,
				  rxq->descs_phys);

	rxq->descs             = शून्य;
	rxq->last_desc         = 0;
	rxq->next_desc_to_proc = 0;
	rxq->descs_phys        = 0;
	rxq->first_to_refill   = 0;
	rxq->refill_num        = 0;
पूर्ण

अटल पूर्णांक mvneta_txq_sw_init(काष्ठा mvneta_port *pp,
			      काष्ठा mvneta_tx_queue *txq)
अणु
	पूर्णांक cpu;

	txq->size = pp->tx_ring_size;

	/* A queue must always have room क्रम at least one skb.
	 * Thereक्रमe, stop the queue when the मुक्त entries reaches
	 * the maximum number of descriptors per skb.
	 */
	txq->tx_stop_threshold = txq->size - MVNETA_MAX_SKB_DESCS;
	txq->tx_wake_threshold = txq->tx_stop_threshold / 2;

	/* Allocate memory क्रम TX descriptors */
	txq->descs = dma_alloc_coherent(pp->dev->dev.parent,
					txq->size * MVNETA_DESC_ALIGNED_SIZE,
					&txq->descs_phys, GFP_KERNEL);
	अगर (!txq->descs)
		वापस -ENOMEM;

	txq->last_desc = txq->size - 1;

	txq->buf = kदो_स्मृति_array(txq->size, माप(*txq->buf), GFP_KERNEL);
	अगर (!txq->buf)
		वापस -ENOMEM;

	/* Allocate DMA buffers क्रम TSO MAC/IP/TCP headers */
	txq->tso_hdrs = dma_alloc_coherent(pp->dev->dev.parent,
					   txq->size * TSO_HEADER_SIZE,
					   &txq->tso_hdrs_phys, GFP_KERNEL);
	अगर (!txq->tso_hdrs)
		वापस -ENOMEM;

	/* Setup XPS mapping */
	अगर (pp->neta_armada3700)
		cpu = 0;
	अन्यथा अगर (txq_number > 1)
		cpu = txq->id % num_present_cpus();
	अन्यथा
		cpu = pp->rxq_def % num_present_cpus();
	cpumask_set_cpu(cpu, &txq->affinity_mask);
	netअगर_set_xps_queue(pp->dev, &txq->affinity_mask, txq->id);

	वापस 0;
पूर्ण

अटल व्योम mvneta_txq_hw_init(काष्ठा mvneta_port *pp,
			       काष्ठा mvneta_tx_queue *txq)
अणु
	/* Set maximum bandwidth क्रम enabled TXQs */
	mvreg_ग_लिखो(pp, MVETH_TXQ_TOKEN_CFG_REG(txq->id), 0x03ffffff);
	mvreg_ग_लिखो(pp, MVETH_TXQ_TOKEN_COUNT_REG(txq->id), 0x3fffffff);

	/* Set Tx descriptors queue starting address */
	mvreg_ग_लिखो(pp, MVNETA_TXQ_BASE_ADDR_REG(txq->id), txq->descs_phys);
	mvreg_ग_लिखो(pp, MVNETA_TXQ_SIZE_REG(txq->id), txq->size);

	mvneta_tx_करोne_pkts_coal_set(pp, txq, txq->करोne_pkts_coal);
पूर्ण

/* Create and initialize a tx queue */
अटल पूर्णांक mvneta_txq_init(काष्ठा mvneta_port *pp,
			   काष्ठा mvneta_tx_queue *txq)
अणु
	पूर्णांक ret;

	ret = mvneta_txq_sw_init(pp, txq);
	अगर (ret < 0)
		वापस ret;

	mvneta_txq_hw_init(pp, txq);

	वापस 0;
पूर्ण

/* Free allocated resources when mvneta_txq_init() fails to allocate memory*/
अटल व्योम mvneta_txq_sw_deinit(काष्ठा mvneta_port *pp,
				 काष्ठा mvneta_tx_queue *txq)
अणु
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(pp->dev, txq->id);

	kमुक्त(txq->buf);

	अगर (txq->tso_hdrs)
		dma_मुक्त_coherent(pp->dev->dev.parent,
				  txq->size * TSO_HEADER_SIZE,
				  txq->tso_hdrs, txq->tso_hdrs_phys);
	अगर (txq->descs)
		dma_मुक्त_coherent(pp->dev->dev.parent,
				  txq->size * MVNETA_DESC_ALIGNED_SIZE,
				  txq->descs, txq->descs_phys);

	netdev_tx_reset_queue(nq);

	txq->descs             = शून्य;
	txq->last_desc         = 0;
	txq->next_desc_to_proc = 0;
	txq->descs_phys        = 0;
पूर्ण

अटल व्योम mvneta_txq_hw_deinit(काष्ठा mvneta_port *pp,
				 काष्ठा mvneta_tx_queue *txq)
अणु
	/* Set minimum bandwidth क्रम disabled TXQs */
	mvreg_ग_लिखो(pp, MVETH_TXQ_TOKEN_CFG_REG(txq->id), 0);
	mvreg_ग_लिखो(pp, MVETH_TXQ_TOKEN_COUNT_REG(txq->id), 0);

	/* Set Tx descriptors queue starting address and size */
	mvreg_ग_लिखो(pp, MVNETA_TXQ_BASE_ADDR_REG(txq->id), 0);
	mvreg_ग_लिखो(pp, MVNETA_TXQ_SIZE_REG(txq->id), 0);
पूर्ण

अटल व्योम mvneta_txq_deinit(काष्ठा mvneta_port *pp,
			      काष्ठा mvneta_tx_queue *txq)
अणु
	mvneta_txq_sw_deinit(pp, txq);
	mvneta_txq_hw_deinit(pp, txq);
पूर्ण

/* Cleanup all Tx queues */
अटल व्योम mvneta_cleanup_txqs(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक queue;

	क्रम (queue = 0; queue < txq_number; queue++)
		mvneta_txq_deinit(pp, &pp->txqs[queue]);
पूर्ण

/* Cleanup all Rx queues */
अटल व्योम mvneta_cleanup_rxqs(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक queue;

	क्रम (queue = 0; queue < rxq_number; queue++)
		mvneta_rxq_deinit(pp, &pp->rxqs[queue]);
पूर्ण


/* Init all Rx queues */
अटल पूर्णांक mvneta_setup_rxqs(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक queue;

	क्रम (queue = 0; queue < rxq_number; queue++) अणु
		पूर्णांक err = mvneta_rxq_init(pp, &pp->rxqs[queue]);

		अगर (err) अणु
			netdev_err(pp->dev, "%s: can't create rxq=%d\n",
				   __func__, queue);
			mvneta_cleanup_rxqs(pp);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Init all tx queues */
अटल पूर्णांक mvneta_setup_txqs(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक queue;

	क्रम (queue = 0; queue < txq_number; queue++) अणु
		पूर्णांक err = mvneta_txq_init(pp, &pp->txqs[queue]);
		अगर (err) अणु
			netdev_err(pp->dev, "%s: can't create txq=%d\n",
				   __func__, queue);
			mvneta_cleanup_txqs(pp);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_comphy_init(काष्ठा mvneta_port *pp, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	पूर्णांक ret;

	ret = phy_set_mode_ext(pp->comphy, PHY_MODE_ETHERNET, पूर्णांकerface);
	अगर (ret)
		वापस ret;

	वापस phy_घातer_on(pp->comphy);
पूर्ण

अटल पूर्णांक mvneta_config_पूर्णांकerface(काष्ठा mvneta_port *pp,
				   phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	पूर्णांक ret = 0;

	अगर (pp->comphy) अणु
		अगर (पूर्णांकerface == PHY_INTERFACE_MODE_SGMII ||
		    पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX ||
		    पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX) अणु
			ret = mvneta_comphy_init(pp, पूर्णांकerface);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_QSGMII:
			mvreg_ग_लिखो(pp, MVNETA_SERDES_CFG,
				    MVNETA_QSGMII_SERDES_PROTO);
			अवरोध;

		हाल PHY_INTERFACE_MODE_SGMII:
		हाल PHY_INTERFACE_MODE_1000BASEX:
			mvreg_ग_लिखो(pp, MVNETA_SERDES_CFG,
				    MVNETA_SGMII_SERDES_PROTO);
			अवरोध;

		हाल PHY_INTERFACE_MODE_2500BASEX:
			mvreg_ग_लिखो(pp, MVNETA_SERDES_CFG,
				    MVNETA_HSGMII_SERDES_PROTO);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pp->phy_पूर्णांकerface = पूर्णांकerface;

	वापस ret;
पूर्ण

अटल व्योम mvneta_start_dev(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक cpu;

	WARN_ON(mvneta_config_पूर्णांकerface(pp, pp->phy_पूर्णांकerface));

	mvneta_max_rx_size_set(pp, pp->pkt_size);
	mvneta_txq_max_tx_size_set(pp, pp->pkt_size);

	/* start the Rx/Tx activity */
	mvneta_port_enable(pp);

	अगर (!pp->neta_armada3700) अणु
		/* Enable polling on the port */
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा mvneta_pcpu_port *port =
				per_cpu_ptr(pp->ports, cpu);

			napi_enable(&port->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		napi_enable(&pp->napi);
	पूर्ण

	/* Unmask पूर्णांकerrupts. It has to be करोne from each CPU */
	on_each_cpu(mvneta_percpu_unmask_पूर्णांकerrupt, pp, true);

	mvreg_ग_लिखो(pp, MVNETA_INTR_MISC_MASK,
		    MVNETA_CAUSE_PHY_STATUS_CHANGE |
		    MVNETA_CAUSE_LINK_CHANGE);

	phylink_start(pp->phylink);

	/* We may have called phylink_speed_करोwn beक्रमe */
	phylink_speed_up(pp->phylink);

	netअगर_tx_start_all_queues(pp->dev);

	clear_bit(__MVNETA_DOWN, &pp->state);
पूर्ण

अटल व्योम mvneta_stop_dev(काष्ठा mvneta_port *pp)
अणु
	अचिन्हित पूर्णांक cpu;

	set_bit(__MVNETA_DOWN, &pp->state);

	अगर (device_may_wakeup(&pp->dev->dev))
		phylink_speed_करोwn(pp->phylink, false);

	phylink_stop(pp->phylink);

	अगर (!pp->neta_armada3700) अणु
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा mvneta_pcpu_port *port =
				per_cpu_ptr(pp->ports, cpu);

			napi_disable(&port->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		napi_disable(&pp->napi);
	पूर्ण

	netअगर_carrier_off(pp->dev);

	mvneta_port_करोwn(pp);
	netअगर_tx_stop_all_queues(pp->dev);

	/* Stop the port activity */
	mvneta_port_disable(pp);

	/* Clear all ethernet port पूर्णांकerrupts */
	on_each_cpu(mvneta_percpu_clear_पूर्णांकr_cause, pp, true);

	/* Mask all ethernet port पूर्णांकerrupts */
	on_each_cpu(mvneta_percpu_mask_पूर्णांकerrupt, pp, true);

	mvneta_tx_reset(pp);
	mvneta_rx_reset(pp);

	WARN_ON(phy_घातer_off(pp->comphy));
पूर्ण

अटल व्योम mvneta_percpu_enable(व्योम *arg)
अणु
	काष्ठा mvneta_port *pp = arg;

	enable_percpu_irq(pp->dev->irq, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम mvneta_percpu_disable(व्योम *arg)
अणु
	काष्ठा mvneta_port *pp = arg;

	disable_percpu_irq(pp->dev->irq);
पूर्ण

/* Change the device mtu */
अटल पूर्णांक mvneta_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	पूर्णांक ret;

	अगर (!IS_ALIGNED(MVNETA_RX_PKT_SIZE(mtu), 8)) अणु
		netdev_info(dev, "Illegal MTU value %d, rounding to %d\n",
			    mtu, ALIGN(MVNETA_RX_PKT_SIZE(mtu), 8));
		mtu = ALIGN(MVNETA_RX_PKT_SIZE(mtu), 8);
	पूर्ण

	अगर (pp->xdp_prog && mtu > MVNETA_MAX_RX_BUF_SIZE) अणु
		netdev_info(dev, "Illegal MTU value %d for XDP mode\n", mtu);
		वापस -EINVAL;
	पूर्ण

	dev->mtu = mtu;

	अगर (!netअगर_running(dev)) अणु
		अगर (pp->bm_priv)
			mvneta_bm_update_mtu(pp, mtu);

		netdev_update_features(dev);
		वापस 0;
	पूर्ण

	/* The पूर्णांकerface is running, so we have to क्रमce a
	 * पुनः_स्मृतिation of the queues
	 */
	mvneta_stop_dev(pp);
	on_each_cpu(mvneta_percpu_disable, pp, true);

	mvneta_cleanup_txqs(pp);
	mvneta_cleanup_rxqs(pp);

	अगर (pp->bm_priv)
		mvneta_bm_update_mtu(pp, mtu);

	pp->pkt_size = MVNETA_RX_PKT_SIZE(dev->mtu);

	ret = mvneta_setup_rxqs(pp);
	अगर (ret) अणु
		netdev_err(dev, "unable to setup rxqs after MTU change\n");
		वापस ret;
	पूर्ण

	ret = mvneta_setup_txqs(pp);
	अगर (ret) अणु
		netdev_err(dev, "unable to setup txqs after MTU change\n");
		वापस ret;
	पूर्ण

	on_each_cpu(mvneta_percpu_enable, pp, true);
	mvneta_start_dev(pp);

	netdev_update_features(dev);

	वापस 0;
पूर्ण

अटल netdev_features_t mvneta_fix_features(काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	अगर (pp->tx_csum_limit && dev->mtu > pp->tx_csum_limit) अणु
		features &= ~(NETIF_F_IP_CSUM | NETIF_F_TSO);
		netdev_info(dev,
			    "Disable IP checksum for MTU greater than %dB\n",
			    pp->tx_csum_limit);
	पूर्ण

	वापस features;
पूर्ण

/* Get mac address */
अटल व्योम mvneta_get_mac_addr(काष्ठा mvneta_port *pp, अचिन्हित अक्षर *addr)
अणु
	u32 mac_addr_l, mac_addr_h;

	mac_addr_l = mvreg_पढ़ो(pp, MVNETA_MAC_ADDR_LOW);
	mac_addr_h = mvreg_पढ़ो(pp, MVNETA_MAC_ADDR_HIGH);
	addr[0] = (mac_addr_h >> 24) & 0xFF;
	addr[1] = (mac_addr_h >> 16) & 0xFF;
	addr[2] = (mac_addr_h >> 8) & 0xFF;
	addr[3] = mac_addr_h & 0xFF;
	addr[4] = (mac_addr_l >> 8) & 0xFF;
	addr[5] = mac_addr_l & 0xFF;
पूर्ण

/* Handle setting mac address */
अटल पूर्णांक mvneta_set_mac_addr(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	काष्ठा sockaddr *sockaddr = addr;
	पूर्णांक ret;

	ret = eth_prepare_mac_addr_change(dev, addr);
	अगर (ret < 0)
		वापस ret;
	/* Remove previous address table entry */
	mvneta_mac_addr_set(pp, dev->dev_addr, -1);

	/* Set new addr in hw */
	mvneta_mac_addr_set(pp, sockaddr->sa_data, pp->rxq_def);

	eth_commit_mac_addr_change(dev, addr);
	वापस 0;
पूर्ण

अटल व्योम mvneta_validate(काष्ठा phylink_config *config,
			    अचिन्हित दीर्घ *supported,
			    काष्ठा phylink_link_state *state)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा mvneta_port *pp = netdev_priv(ndev);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	/* We only support QSGMII, SGMII, 802.3z and RGMII modes */
	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_QSGMII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
	    !phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface) &&
	    !phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface)) अणु
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		वापस;
	पूर्ण

	/* Allow all the expected bits */
	phylink_set(mask, Autoneg);
	phylink_set_port_modes(mask);

	/* Asymmetric छोड़ो is unsupported */
	phylink_set(mask, Pause);

	/* Half-duplex at speeds higher than 100Mbit is unsupported */
	अगर (pp->comphy || state->पूर्णांकerface != PHY_INTERFACE_MODE_2500BASEX) अणु
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseX_Full);
	पूर्ण
	अगर (pp->comphy || state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX) अणु
		phylink_set(mask, 2500baseT_Full);
		phylink_set(mask, 2500baseX_Full);
	पूर्ण

	अगर (!phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		/* 10M and 100M are only supported in non-802.3z mode */
		phylink_set(mask, 10baseT_Half);
		phylink_set(mask, 10baseT_Full);
		phylink_set(mask, 100baseT_Half);
		phylink_set(mask, 100baseT_Full);
	पूर्ण

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);

	/* We can only operate at 2500BaseX or 1000BaseX.  If requested
	 * to advertise both, only report advertising at 2500BaseX.
	 */
	phylink_helper_basex_speed(state);
पूर्ण

अटल व्योम mvneta_mac_pcs_get_state(काष्ठा phylink_config *config,
				     काष्ठा phylink_link_state *state)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा mvneta_port *pp = netdev_priv(ndev);
	u32 gmac_stat;

	gmac_stat = mvreg_पढ़ो(pp, MVNETA_GMAC_STATUS);

	अगर (gmac_stat & MVNETA_GMAC_SPEED_1000)
		state->speed =
			state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX ?
			SPEED_2500 : SPEED_1000;
	अन्यथा अगर (gmac_stat & MVNETA_GMAC_SPEED_100)
		state->speed = SPEED_100;
	अन्यथा
		state->speed = SPEED_10;

	state->an_complete = !!(gmac_stat & MVNETA_GMAC_AN_COMPLETE);
	state->link = !!(gmac_stat & MVNETA_GMAC_LINK_UP);
	state->duplex = !!(gmac_stat & MVNETA_GMAC_FULL_DUPLEX);

	state->छोड़ो = 0;
	अगर (gmac_stat & MVNETA_GMAC_RX_FLOW_CTRL_ENABLE)
		state->छोड़ो |= MLO_PAUSE_RX;
	अगर (gmac_stat & MVNETA_GMAC_TX_FLOW_CTRL_ENABLE)
		state->छोड़ो |= MLO_PAUSE_TX;
पूर्ण

अटल व्योम mvneta_mac_an_restart(काष्ठा phylink_config *config)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा mvneta_port *pp = netdev_priv(ndev);
	u32 gmac_an = mvreg_पढ़ो(pp, MVNETA_GMAC_AUTONEG_CONFIG);

	mvreg_ग_लिखो(pp, MVNETA_GMAC_AUTONEG_CONFIG,
		    gmac_an | MVNETA_GMAC_INBAND_RESTART_AN);
	mvreg_ग_लिखो(pp, MVNETA_GMAC_AUTONEG_CONFIG,
		    gmac_an & ~MVNETA_GMAC_INBAND_RESTART_AN);
पूर्ण

अटल व्योम mvneta_mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			      स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा mvneta_port *pp = netdev_priv(ndev);
	u32 new_ctrl0, gmac_ctrl0 = mvreg_पढ़ो(pp, MVNETA_GMAC_CTRL_0);
	u32 new_ctrl2, gmac_ctrl2 = mvreg_पढ़ो(pp, MVNETA_GMAC_CTRL_2);
	u32 new_ctrl4, gmac_ctrl4 = mvreg_पढ़ो(pp, MVNETA_GMAC_CTRL_4);
	u32 new_clk, gmac_clk = mvreg_पढ़ो(pp, MVNETA_GMAC_CLOCK_DIVIDER);
	u32 new_an, gmac_an = mvreg_पढ़ो(pp, MVNETA_GMAC_AUTONEG_CONFIG);

	new_ctrl0 = gmac_ctrl0 & ~MVNETA_GMAC0_PORT_1000BASE_X;
	new_ctrl2 = gmac_ctrl2 & ~(MVNETA_GMAC2_INBAND_AN_ENABLE |
				   MVNETA_GMAC2_PORT_RESET);
	new_ctrl4 = gmac_ctrl4 & ~(MVNETA_GMAC4_SHORT_PREAMBLE_ENABLE);
	new_clk = gmac_clk & ~MVNETA_GMAC_1MS_CLOCK_ENABLE;
	new_an = gmac_an & ~(MVNETA_GMAC_INBAND_AN_ENABLE |
			     MVNETA_GMAC_INBAND_RESTART_AN |
			     MVNETA_GMAC_AN_SPEED_EN |
			     MVNETA_GMAC_ADVERT_SYM_FLOW_CTRL |
			     MVNETA_GMAC_AN_FLOW_CTRL_EN |
			     MVNETA_GMAC_AN_DUPLEX_EN);

	/* Even though it might look weird, when we're configured in
	 * SGMII or QSGMII mode, the RGMII bit needs to be set.
	 */
	new_ctrl2 |= MVNETA_GMAC2_PORT_RGMII;

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_QSGMII ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII ||
	    phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface))
		new_ctrl2 |= MVNETA_GMAC2_PCS_ENABLE;

	अगर (phylink_test(state->advertising, Pause))
		new_an |= MVNETA_GMAC_ADVERT_SYM_FLOW_CTRL;

	अगर (!phylink_स्वतःneg_inband(mode)) अणु
		/* Phy or fixed speed - nothing to करो, leave the
		 * configured speed, duplex and flow control as-is.
		 */
	पूर्ण अन्यथा अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		/* SGMII mode receives the state from the PHY */
		new_ctrl2 |= MVNETA_GMAC2_INBAND_AN_ENABLE;
		new_clk |= MVNETA_GMAC_1MS_CLOCK_ENABLE;
		new_an = (new_an & ~(MVNETA_GMAC_FORCE_LINK_DOWN |
				     MVNETA_GMAC_FORCE_LINK_PASS |
				     MVNETA_GMAC_CONFIG_MII_SPEED |
				     MVNETA_GMAC_CONFIG_GMII_SPEED |
				     MVNETA_GMAC_CONFIG_FULL_DUPLEX)) |
			 MVNETA_GMAC_INBAND_AN_ENABLE |
			 MVNETA_GMAC_AN_SPEED_EN |
			 MVNETA_GMAC_AN_DUPLEX_EN;
	पूर्ण अन्यथा अणु
		/* 802.3z negotiation - only 1000base-X */
		new_ctrl0 |= MVNETA_GMAC0_PORT_1000BASE_X;
		new_clk |= MVNETA_GMAC_1MS_CLOCK_ENABLE;
		new_an = (new_an & ~(MVNETA_GMAC_FORCE_LINK_DOWN |
				     MVNETA_GMAC_FORCE_LINK_PASS |
				     MVNETA_GMAC_CONFIG_MII_SPEED)) |
			 MVNETA_GMAC_INBAND_AN_ENABLE |
			 MVNETA_GMAC_CONFIG_GMII_SPEED |
			 /* The MAC only supports FD mode */
			 MVNETA_GMAC_CONFIG_FULL_DUPLEX;

		अगर (state->छोड़ो & MLO_PAUSE_AN && state->an_enabled)
			new_an |= MVNETA_GMAC_AN_FLOW_CTRL_EN;
	पूर्ण

	/* Armada 370 करोcumentation says we can only change the port mode
	 * and in-band enable when the link is करोwn, so क्रमce it करोwn
	 * जबतक making these changes. We also करो this क्रम GMAC_CTRL2
	 */
	अगर ((new_ctrl0 ^ gmac_ctrl0) & MVNETA_GMAC0_PORT_1000BASE_X ||
	    (new_ctrl2 ^ gmac_ctrl2) & MVNETA_GMAC2_INBAND_AN_ENABLE ||
	    (new_an  ^ gmac_an) & MVNETA_GMAC_INBAND_AN_ENABLE) अणु
		mvreg_ग_लिखो(pp, MVNETA_GMAC_AUTONEG_CONFIG,
			    (gmac_an & ~MVNETA_GMAC_FORCE_LINK_PASS) |
			    MVNETA_GMAC_FORCE_LINK_DOWN);
	पूर्ण


	/* When at 2.5G, the link partner can send frames with लघुened
	 * preambles.
	 */
	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX)
		new_ctrl4 |= MVNETA_GMAC4_SHORT_PREAMBLE_ENABLE;

	अगर (pp->phy_पूर्णांकerface != state->पूर्णांकerface) अणु
		अगर (pp->comphy)
			WARN_ON(phy_घातer_off(pp->comphy));
		WARN_ON(mvneta_config_पूर्णांकerface(pp, state->पूर्णांकerface));
	पूर्ण

	अगर (new_ctrl0 != gmac_ctrl0)
		mvreg_ग_लिखो(pp, MVNETA_GMAC_CTRL_0, new_ctrl0);
	अगर (new_ctrl2 != gmac_ctrl2)
		mvreg_ग_लिखो(pp, MVNETA_GMAC_CTRL_2, new_ctrl2);
	अगर (new_ctrl4 != gmac_ctrl4)
		mvreg_ग_लिखो(pp, MVNETA_GMAC_CTRL_4, new_ctrl4);
	अगर (new_clk != gmac_clk)
		mvreg_ग_लिखो(pp, MVNETA_GMAC_CLOCK_DIVIDER, new_clk);
	अगर (new_an != gmac_an)
		mvreg_ग_लिखो(pp, MVNETA_GMAC_AUTONEG_CONFIG, new_an);

	अगर (gmac_ctrl2 & MVNETA_GMAC2_PORT_RESET) अणु
		जबतक ((mvreg_पढ़ो(pp, MVNETA_GMAC_CTRL_2) &
			MVNETA_GMAC2_PORT_RESET) != 0)
			जारी;
	पूर्ण
पूर्ण

अटल व्योम mvneta_set_eee(काष्ठा mvneta_port *pp, bool enable)
अणु
	u32 lpi_ctl1;

	lpi_ctl1 = mvreg_पढ़ो(pp, MVNETA_LPI_CTRL_1);
	अगर (enable)
		lpi_ctl1 |= MVNETA_LPI_REQUEST_ENABLE;
	अन्यथा
		lpi_ctl1 &= ~MVNETA_LPI_REQUEST_ENABLE;
	mvreg_ग_लिखो(pp, MVNETA_LPI_CTRL_1, lpi_ctl1);
पूर्ण

अटल व्योम mvneta_mac_link_करोwn(काष्ठा phylink_config *config,
				 अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा mvneta_port *pp = netdev_priv(ndev);
	u32 val;

	mvneta_port_करोwn(pp);

	अगर (!phylink_स्वतःneg_inband(mode)) अणु
		val = mvreg_पढ़ो(pp, MVNETA_GMAC_AUTONEG_CONFIG);
		val &= ~MVNETA_GMAC_FORCE_LINK_PASS;
		val |= MVNETA_GMAC_FORCE_LINK_DOWN;
		mvreg_ग_लिखो(pp, MVNETA_GMAC_AUTONEG_CONFIG, val);
	पूर्ण

	pp->eee_active = false;
	mvneta_set_eee(pp, false);
पूर्ण

अटल व्योम mvneta_mac_link_up(काष्ठा phylink_config *config,
			       काष्ठा phy_device *phy,
			       अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
			       पूर्णांक speed, पूर्णांक duplex,
			       bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा net_device *ndev = to_net_dev(config->dev);
	काष्ठा mvneta_port *pp = netdev_priv(ndev);
	u32 val;

	अगर (!phylink_स्वतःneg_inband(mode)) अणु
		val = mvreg_पढ़ो(pp, MVNETA_GMAC_AUTONEG_CONFIG);
		val &= ~(MVNETA_GMAC_FORCE_LINK_DOWN |
			 MVNETA_GMAC_CONFIG_MII_SPEED |
			 MVNETA_GMAC_CONFIG_GMII_SPEED |
			 MVNETA_GMAC_CONFIG_FLOW_CTRL |
			 MVNETA_GMAC_CONFIG_FULL_DUPLEX);
		val |= MVNETA_GMAC_FORCE_LINK_PASS;

		अगर (speed == SPEED_1000 || speed == SPEED_2500)
			val |= MVNETA_GMAC_CONFIG_GMII_SPEED;
		अन्यथा अगर (speed == SPEED_100)
			val |= MVNETA_GMAC_CONFIG_MII_SPEED;

		अगर (duplex == DUPLEX_FULL)
			val |= MVNETA_GMAC_CONFIG_FULL_DUPLEX;

		अगर (tx_छोड़ो || rx_छोड़ो)
			val |= MVNETA_GMAC_CONFIG_FLOW_CTRL;

		mvreg_ग_लिखो(pp, MVNETA_GMAC_AUTONEG_CONFIG, val);
	पूर्ण अन्यथा अणु
		/* When inband करोesn't cover flow control or flow control is
		 * disabled, we need to manually configure it. This bit will
		 * only have effect अगर MVNETA_GMAC_AN_FLOW_CTRL_EN is unset.
		 */
		val = mvreg_पढ़ो(pp, MVNETA_GMAC_AUTONEG_CONFIG);
		val &= ~MVNETA_GMAC_CONFIG_FLOW_CTRL;

		अगर (tx_छोड़ो || rx_छोड़ो)
			val |= MVNETA_GMAC_CONFIG_FLOW_CTRL;

		mvreg_ग_लिखो(pp, MVNETA_GMAC_AUTONEG_CONFIG, val);
	पूर्ण

	mvneta_port_up(pp);

	अगर (phy && pp->eee_enabled) अणु
		pp->eee_active = phy_init_eee(phy, 0) >= 0;
		mvneta_set_eee(pp, pp->eee_active && pp->tx_lpi_enabled);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops mvneta_phylink_ops = अणु
	.validate = mvneta_validate,
	.mac_pcs_get_state = mvneta_mac_pcs_get_state,
	.mac_an_restart = mvneta_mac_an_restart,
	.mac_config = mvneta_mac_config,
	.mac_link_करोwn = mvneta_mac_link_करोwn,
	.mac_link_up = mvneta_mac_link_up,
पूर्ण;

अटल पूर्णांक mvneta_mdio_probe(काष्ठा mvneta_port *pp)
अणु
	काष्ठा ethtool_wolinfo wol = अणु .cmd = ETHTOOL_GWOL पूर्ण;
	पूर्णांक err = phylink_of_phy_connect(pp->phylink, pp->dn, 0);

	अगर (err)
		netdev_err(pp->dev, "could not attach PHY: %d\n", err);

	phylink_ethtool_get_wol(pp->phylink, &wol);
	device_set_wakeup_capable(&pp->dev->dev, !!wol.supported);

	/* PHY WoL may be enabled but device wakeup disabled */
	अगर (wol.supported)
		device_set_wakeup_enable(&pp->dev->dev, !!wol.wolopts);

	वापस err;
पूर्ण

अटल व्योम mvneta_mdio_हटाओ(काष्ठा mvneta_port *pp)
अणु
	phylink_disconnect_phy(pp->phylink);
पूर्ण

/* Electing a CPU must be करोne in an atomic way: it should be करोne
 * after or beक्रमe the removal/insertion of a CPU and this function is
 * not reentrant.
 */
अटल व्योम mvneta_percpu_elect(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक elected_cpu = 0, max_cpu, cpu, i = 0;

	/* Use the cpu associated to the rxq when it is online, in all
	 * the other हालs, use the cpu 0 which can't be offline.
	 */
	अगर (cpu_online(pp->rxq_def))
		elected_cpu = pp->rxq_def;

	max_cpu = num_present_cpus();

	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक rxq_map = 0, txq_map = 0;
		पूर्णांक rxq;

		क्रम (rxq = 0; rxq < rxq_number; rxq++)
			अगर ((rxq % max_cpu) == cpu)
				rxq_map |= MVNETA_CPU_RXQ_ACCESS(rxq);

		अगर (cpu == elected_cpu)
			/* Map the शेष receive queue to the elected CPU */
			rxq_map |= MVNETA_CPU_RXQ_ACCESS(pp->rxq_def);

		/* We update the TX queue map only अगर we have one
		 * queue. In this हाल we associate the TX queue to
		 * the CPU bound to the शेष RX queue
		 */
		अगर (txq_number == 1)
			txq_map = (cpu == elected_cpu) ?
				MVNETA_CPU_TXQ_ACCESS(1) : 0;
		अन्यथा
			txq_map = mvreg_पढ़ो(pp, MVNETA_CPU_MAP(cpu)) &
				MVNETA_CPU_TXQ_ACCESS_ALL_MASK;

		mvreg_ग_लिखो(pp, MVNETA_CPU_MAP(cpu), rxq_map | txq_map);

		/* Update the पूर्णांकerrupt mask on each CPU according the
		 * new mapping
		 */
		smp_call_function_single(cpu, mvneta_percpu_unmask_पूर्णांकerrupt,
					 pp, true);
		i++;

	पूर्ण
पूर्ण;

अटल पूर्णांक mvneta_cpu_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	पूर्णांक other_cpu;
	काष्ठा mvneta_port *pp = hlist_entry_safe(node, काष्ठा mvneta_port,
						  node_online);
	काष्ठा mvneta_pcpu_port *port = per_cpu_ptr(pp->ports, cpu);

	/* Armada 3700's per-cpu पूर्णांकerrupt क्रम mvneta is broken, all पूर्णांकerrupts
	 * are routed to CPU 0, so we करोn't need all the cpu-hotplug support
	 */
	अगर (pp->neta_armada3700)
		वापस 0;

	spin_lock(&pp->lock);
	/*
	 * Configuring the driver क्रम a new CPU जबतक the driver is
	 * stopping is racy, so just aव्योम it.
	 */
	अगर (pp->is_stopped) अणु
		spin_unlock(&pp->lock);
		वापस 0;
	पूर्ण
	netअगर_tx_stop_all_queues(pp->dev);

	/*
	 * We have to synchronise on tha napi of each CPU except the one
	 * just being woken up
	 */
	क्रम_each_online_cpu(other_cpu) अणु
		अगर (other_cpu != cpu) अणु
			काष्ठा mvneta_pcpu_port *other_port =
				per_cpu_ptr(pp->ports, other_cpu);

			napi_synchronize(&other_port->napi);
		पूर्ण
	पूर्ण

	/* Mask all ethernet port पूर्णांकerrupts */
	on_each_cpu(mvneta_percpu_mask_पूर्णांकerrupt, pp, true);
	napi_enable(&port->napi);

	/*
	 * Enable per-CPU पूर्णांकerrupts on the CPU that is
	 * brought up.
	 */
	mvneta_percpu_enable(pp);

	/*
	 * Enable per-CPU पूर्णांकerrupt on the one CPU we care
	 * about.
	 */
	mvneta_percpu_elect(pp);

	/* Unmask all ethernet port पूर्णांकerrupts */
	on_each_cpu(mvneta_percpu_unmask_पूर्णांकerrupt, pp, true);
	mvreg_ग_लिखो(pp, MVNETA_INTR_MISC_MASK,
		    MVNETA_CAUSE_PHY_STATUS_CHANGE |
		    MVNETA_CAUSE_LINK_CHANGE);
	netअगर_tx_start_all_queues(pp->dev);
	spin_unlock(&pp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_cpu_करोwn_prepare(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा mvneta_port *pp = hlist_entry_safe(node, काष्ठा mvneta_port,
						  node_online);
	काष्ठा mvneta_pcpu_port *port = per_cpu_ptr(pp->ports, cpu);

	/*
	 * Thanks to this lock we are sure that any pending cpu election is
	 * करोne.
	 */
	spin_lock(&pp->lock);
	/* Mask all ethernet port पूर्णांकerrupts */
	on_each_cpu(mvneta_percpu_mask_पूर्णांकerrupt, pp, true);
	spin_unlock(&pp->lock);

	napi_synchronize(&port->napi);
	napi_disable(&port->napi);
	/* Disable per-CPU पूर्णांकerrupts on the CPU that is brought करोwn. */
	mvneta_percpu_disable(pp);
	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_cpu_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा mvneta_port *pp = hlist_entry_safe(node, काष्ठा mvneta_port,
						  node_dead);

	/* Check अगर a new CPU must be elected now this on is करोwn */
	spin_lock(&pp->lock);
	mvneta_percpu_elect(pp);
	spin_unlock(&pp->lock);
	/* Unmask all ethernet port पूर्णांकerrupts */
	on_each_cpu(mvneta_percpu_unmask_पूर्णांकerrupt, pp, true);
	mvreg_ग_लिखो(pp, MVNETA_INTR_MISC_MASK,
		    MVNETA_CAUSE_PHY_STATUS_CHANGE |
		    MVNETA_CAUSE_LINK_CHANGE);
	netअगर_tx_start_all_queues(pp->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	पूर्णांक ret;

	pp->pkt_size = MVNETA_RX_PKT_SIZE(pp->dev->mtu);

	ret = mvneta_setup_rxqs(pp);
	अगर (ret)
		वापस ret;

	ret = mvneta_setup_txqs(pp);
	अगर (ret)
		जाओ err_cleanup_rxqs;

	/* Connect to port पूर्णांकerrupt line */
	अगर (pp->neta_armada3700)
		ret = request_irq(pp->dev->irq, mvneta_isr, 0,
				  dev->name, pp);
	अन्यथा
		ret = request_percpu_irq(pp->dev->irq, mvneta_percpu_isr,
					 dev->name, pp->ports);
	अगर (ret) अणु
		netdev_err(pp->dev, "cannot request irq %d\n", pp->dev->irq);
		जाओ err_cleanup_txqs;
	पूर्ण

	अगर (!pp->neta_armada3700) अणु
		/* Enable per-CPU पूर्णांकerrupt on all the CPU to handle our RX
		 * queue पूर्णांकerrupts
		 */
		on_each_cpu(mvneta_percpu_enable, pp, true);

		pp->is_stopped = false;
		/* Register a CPU notअगरier to handle the हाल where our CPU
		 * might be taken offline.
		 */
		ret = cpuhp_state_add_instance_nocalls(online_hpstate,
						       &pp->node_online);
		अगर (ret)
			जाओ err_मुक्त_irq;

		ret = cpuhp_state_add_instance_nocalls(CPUHP_NET_MVNETA_DEAD,
						       &pp->node_dead);
		अगर (ret)
			जाओ err_मुक्त_online_hp;
	पूर्ण

	ret = mvneta_mdio_probe(pp);
	अगर (ret < 0) अणु
		netdev_err(dev, "cannot probe MDIO bus\n");
		जाओ err_मुक्त_dead_hp;
	पूर्ण

	mvneta_start_dev(pp);

	वापस 0;

err_मुक्त_dead_hp:
	अगर (!pp->neta_armada3700)
		cpuhp_state_हटाओ_instance_nocalls(CPUHP_NET_MVNETA_DEAD,
						    &pp->node_dead);
err_मुक्त_online_hp:
	अगर (!pp->neta_armada3700)
		cpuhp_state_हटाओ_instance_nocalls(online_hpstate,
						    &pp->node_online);
err_मुक्त_irq:
	अगर (pp->neta_armada3700) अणु
		मुक्त_irq(pp->dev->irq, pp);
	पूर्ण अन्यथा अणु
		on_each_cpu(mvneta_percpu_disable, pp, true);
		मुक्त_percpu_irq(pp->dev->irq, pp->ports);
	पूर्ण
err_cleanup_txqs:
	mvneta_cleanup_txqs(pp);
err_cleanup_rxqs:
	mvneta_cleanup_rxqs(pp);
	वापस ret;
पूर्ण

/* Stop the port, मुक्त port पूर्णांकerrupt line */
अटल पूर्णांक mvneta_stop(काष्ठा net_device *dev)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	अगर (!pp->neta_armada3700) अणु
		/* Inक्रमm that we are stopping so we करोn't want to setup the
		 * driver क्रम new CPUs in the notअगरiers. The code of the
		 * notअगरier क्रम CPU online is रक्षित by the same spinlock,
		 * so when we get the lock, the notअगरer work is करोne.
		 */
		spin_lock(&pp->lock);
		pp->is_stopped = true;
		spin_unlock(&pp->lock);

		mvneta_stop_dev(pp);
		mvneta_mdio_हटाओ(pp);

		cpuhp_state_हटाओ_instance_nocalls(online_hpstate,
						    &pp->node_online);
		cpuhp_state_हटाओ_instance_nocalls(CPUHP_NET_MVNETA_DEAD,
						    &pp->node_dead);
		on_each_cpu(mvneta_percpu_disable, pp, true);
		मुक्त_percpu_irq(dev->irq, pp->ports);
	पूर्ण अन्यथा अणु
		mvneta_stop_dev(pp);
		mvneta_mdio_हटाओ(pp);
		मुक्त_irq(dev->irq, pp);
	पूर्ण

	mvneta_cleanup_rxqs(pp);
	mvneta_cleanup_txqs(pp);

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	वापस phylink_mii_ioctl(pp->phylink, अगरr, cmd);
पूर्ण

अटल पूर्णांक mvneta_xdp_setup(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
			    काष्ठा netlink_ext_ack *extack)
अणु
	bool need_update, running = netअगर_running(dev);
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	काष्ठा bpf_prog *old_prog;

	अगर (prog && dev->mtu > MVNETA_MAX_RX_BUF_SIZE) अणु
		NL_SET_ERR_MSG_MOD(extack, "MTU too large for XDP");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (pp->bm_priv) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Hardware Buffer Management not supported on XDP");
		वापस -EOPNOTSUPP;
	पूर्ण

	need_update = !!pp->xdp_prog != !!prog;
	अगर (running && need_update)
		mvneta_stop(dev);

	old_prog = xchg(&pp->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	अगर (running && need_update)
		वापस mvneta_खोलो(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस mvneta_xdp_setup(dev, xdp->prog, xdp->extack);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Ethtool methods */

/* Set link ksettings (phy address, speed) क्रम ethtools */
अटल पूर्णांक
mvneta_ethtool_set_link_ksettings(काष्ठा net_device *ndev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(ndev);

	वापस phylink_ethtool_ksettings_set(pp->phylink, cmd);
पूर्ण

/* Get link ksettings क्रम ethtools */
अटल पूर्णांक
mvneta_ethtool_get_link_ksettings(काष्ठा net_device *ndev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(ndev);

	वापस phylink_ethtool_ksettings_get(pp->phylink, cmd);
पूर्ण

अटल पूर्णांक mvneta_ethtool_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	वापस phylink_ethtool_nway_reset(pp->phylink);
पूर्ण

/* Set पूर्णांकerrupt coalescing क्रम ethtools */
अटल पूर्णांक mvneta_ethtool_set_coalesce(काष्ठा net_device *dev,
				       काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	पूर्णांक queue;

	क्रम (queue = 0; queue < rxq_number; queue++) अणु
		काष्ठा mvneta_rx_queue *rxq = &pp->rxqs[queue];
		rxq->समय_coal = c->rx_coalesce_usecs;
		rxq->pkts_coal = c->rx_max_coalesced_frames;
		mvneta_rx_pkts_coal_set(pp, rxq, rxq->pkts_coal);
		mvneta_rx_समय_coal_set(pp, rxq, rxq->समय_coal);
	पूर्ण

	क्रम (queue = 0; queue < txq_number; queue++) अणु
		काष्ठा mvneta_tx_queue *txq = &pp->txqs[queue];
		txq->करोne_pkts_coal = c->tx_max_coalesced_frames;
		mvneta_tx_करोne_pkts_coal_set(pp, txq, txq->करोne_pkts_coal);
	पूर्ण

	वापस 0;
पूर्ण

/* get coalescing क्रम ethtools */
अटल पूर्णांक mvneta_ethtool_get_coalesce(काष्ठा net_device *dev,
				       काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	c->rx_coalesce_usecs        = pp->rxqs[0].समय_coal;
	c->rx_max_coalesced_frames  = pp->rxqs[0].pkts_coal;

	c->tx_max_coalesced_frames =  pp->txqs[0].करोne_pkts_coal;
	वापस 0;
पूर्ण


अटल व्योम mvneta_ethtool_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, MVNETA_DRIVER_NAME,
		माप(drvinfo->driver));
	strlcpy(drvinfo->version, MVNETA_DRIVER_VERSION,
		माप(drvinfo->version));
	strlcpy(drvinfo->bus_info, dev_name(&dev->dev),
		माप(drvinfo->bus_info));
पूर्ण


अटल व्योम mvneta_ethtool_get_ringparam(काष्ठा net_device *netdev,
					 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(netdev);

	ring->rx_max_pending = MVNETA_MAX_RXD;
	ring->tx_max_pending = MVNETA_MAX_TXD;
	ring->rx_pending = pp->rx_ring_size;
	ring->tx_pending = pp->tx_ring_size;
पूर्ण

अटल पूर्णांक mvneta_ethtool_set_ringparam(काष्ठा net_device *dev,
					काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	अगर ((ring->rx_pending == 0) || (ring->tx_pending == 0))
		वापस -EINVAL;
	pp->rx_ring_size = ring->rx_pending < MVNETA_MAX_RXD ?
		ring->rx_pending : MVNETA_MAX_RXD;

	pp->tx_ring_size = clamp_t(u16, ring->tx_pending,
				   MVNETA_MAX_SKB_DESCS * 2, MVNETA_MAX_TXD);
	अगर (pp->tx_ring_size != ring->tx_pending)
		netdev_warn(dev, "TX queue size set to %u (requested %u)\n",
			    pp->tx_ring_size, ring->tx_pending);

	अगर (netअगर_running(dev)) अणु
		mvneta_stop(dev);
		अगर (mvneta_खोलो(dev)) अणु
			netdev_err(dev,
				   "error on opening device after ring param change\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mvneta_ethtool_get_छोड़ोparam(काष्ठा net_device *dev,
					  काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	phylink_ethtool_get_छोड़ोparam(pp->phylink, छोड़ो);
पूर्ण

अटल पूर्णांक mvneta_ethtool_set_छोड़ोparam(काष्ठा net_device *dev,
					 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	वापस phylink_ethtool_set_छोड़ोparam(pp->phylink, छोड़ो);
पूर्ण

अटल व्योम mvneta_ethtool_get_strings(काष्ठा net_device *netdev, u32 sset,
				       u8 *data)
अणु
	अगर (sset == ETH_SS_STATS) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(mvneta_statistics); i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
			       mvneta_statistics[i].name, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल व्योम
mvneta_ethtool_update_pcpu_stats(काष्ठा mvneta_port *pp,
				 काष्ठा mvneta_ethtool_stats *es)
अणु
	अचिन्हित पूर्णांक start;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा mvneta_pcpu_stats *stats;
		u64 skb_alloc_error;
		u64 refill_error;
		u64 xdp_redirect;
		u64 xdp_xmit_err;
		u64 xdp_tx_err;
		u64 xdp_pass;
		u64 xdp_drop;
		u64 xdp_xmit;
		u64 xdp_tx;

		stats = per_cpu_ptr(pp->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			skb_alloc_error = stats->es.skb_alloc_error;
			refill_error = stats->es.refill_error;
			xdp_redirect = stats->es.ps.xdp_redirect;
			xdp_pass = stats->es.ps.xdp_pass;
			xdp_drop = stats->es.ps.xdp_drop;
			xdp_xmit = stats->es.ps.xdp_xmit;
			xdp_xmit_err = stats->es.ps.xdp_xmit_err;
			xdp_tx = stats->es.ps.xdp_tx;
			xdp_tx_err = stats->es.ps.xdp_tx_err;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		es->skb_alloc_error += skb_alloc_error;
		es->refill_error += refill_error;
		es->ps.xdp_redirect += xdp_redirect;
		es->ps.xdp_pass += xdp_pass;
		es->ps.xdp_drop += xdp_drop;
		es->ps.xdp_xmit += xdp_xmit;
		es->ps.xdp_xmit_err += xdp_xmit_err;
		es->ps.xdp_tx += xdp_tx;
		es->ps.xdp_tx_err += xdp_tx_err;
	पूर्ण
पूर्ण

अटल व्योम mvneta_ethtool_update_stats(काष्ठा mvneta_port *pp)
अणु
	काष्ठा mvneta_ethtool_stats stats = अणुपूर्ण;
	स्थिर काष्ठा mvneta_statistic *s;
	व्योम __iomem *base = pp->base;
	u32 high, low;
	u64 val;
	पूर्णांक i;

	mvneta_ethtool_update_pcpu_stats(pp, &stats);
	क्रम (i = 0, s = mvneta_statistics;
	     s < mvneta_statistics + ARRAY_SIZE(mvneta_statistics);
	     s++, i++) अणु
		चयन (s->type) अणु
		हाल T_REG_32:
			val = पढ़ोl_relaxed(base + s->offset);
			pp->ethtool_stats[i] += val;
			अवरोध;
		हाल T_REG_64:
			/* Docs say to पढ़ो low 32-bit then high */
			low = पढ़ोl_relaxed(base + s->offset);
			high = पढ़ोl_relaxed(base + s->offset + 4);
			val = (u64)high << 32 | low;
			pp->ethtool_stats[i] += val;
			अवरोध;
		हाल T_SW:
			चयन (s->offset) अणु
			हाल ETHTOOL_STAT_EEE_WAKEUP:
				val = phylink_get_eee_err(pp->phylink);
				pp->ethtool_stats[i] += val;
				अवरोध;
			हाल ETHTOOL_STAT_SKB_ALLOC_ERR:
				pp->ethtool_stats[i] = stats.skb_alloc_error;
				अवरोध;
			हाल ETHTOOL_STAT_REFILL_ERR:
				pp->ethtool_stats[i] = stats.refill_error;
				अवरोध;
			हाल ETHTOOL_XDP_REसूचीECT:
				pp->ethtool_stats[i] = stats.ps.xdp_redirect;
				अवरोध;
			हाल ETHTOOL_XDP_PASS:
				pp->ethtool_stats[i] = stats.ps.xdp_pass;
				अवरोध;
			हाल ETHTOOL_XDP_DROP:
				pp->ethtool_stats[i] = stats.ps.xdp_drop;
				अवरोध;
			हाल ETHTOOL_XDP_TX:
				pp->ethtool_stats[i] = stats.ps.xdp_tx;
				अवरोध;
			हाल ETHTOOL_XDP_TX_ERR:
				pp->ethtool_stats[i] = stats.ps.xdp_tx_err;
				अवरोध;
			हाल ETHTOOL_XDP_XMIT:
				pp->ethtool_stats[i] = stats.ps.xdp_xmit;
				अवरोध;
			हाल ETHTOOL_XDP_XMIT_ERR:
				pp->ethtool_stats[i] = stats.ps.xdp_xmit_err;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mvneta_ethtool_get_stats(काष्ठा net_device *dev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	पूर्णांक i;

	mvneta_ethtool_update_stats(pp);

	क्रम (i = 0; i < ARRAY_SIZE(mvneta_statistics); i++)
		*data++ = pp->ethtool_stats[i];
पूर्ण

अटल पूर्णांक mvneta_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस ARRAY_SIZE(mvneta_statistics);
	वापस -EOPNOTSUPP;
पूर्ण

अटल u32 mvneta_ethtool_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	वापस MVNETA_RSS_LU_TABLE_SIZE;
पूर्ण

अटल पूर्णांक mvneta_ethtool_get_rxnfc(काष्ठा net_device *dev,
				    काष्ठा ethtool_rxnfc *info,
				    u32 *rules __always_unused)
अणु
	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data =  rxq_number;
		वापस 0;
	हाल ETHTOOL_GRXFH:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक  mvneta_config_rss(काष्ठा mvneta_port *pp)
अणु
	पूर्णांक cpu;
	u32 val;

	netअगर_tx_stop_all_queues(pp->dev);

	on_each_cpu(mvneta_percpu_mask_पूर्णांकerrupt, pp, true);

	अगर (!pp->neta_armada3700) अणु
		/* We have to synchronise on the napi of each CPU */
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा mvneta_pcpu_port *pcpu_port =
				per_cpu_ptr(pp->ports, cpu);

			napi_synchronize(&pcpu_port->napi);
			napi_disable(&pcpu_port->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		napi_synchronize(&pp->napi);
		napi_disable(&pp->napi);
	पूर्ण

	pp->rxq_def = pp->indir[0];

	/* Update unicast mapping */
	mvneta_set_rx_mode(pp->dev);

	/* Update val of portCfg रेजिस्टर accordingly with all RxQueue types */
	val = MVNETA_PORT_CONFIG_DEFL_VALUE(pp->rxq_def);
	mvreg_ग_लिखो(pp, MVNETA_PORT_CONFIG, val);

	/* Update the elected CPU matching the new rxq_def */
	spin_lock(&pp->lock);
	mvneta_percpu_elect(pp);
	spin_unlock(&pp->lock);

	अगर (!pp->neta_armada3700) अणु
		/* We have to synchronise on the napi of each CPU */
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा mvneta_pcpu_port *pcpu_port =
				per_cpu_ptr(pp->ports, cpu);

			napi_enable(&pcpu_port->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		napi_enable(&pp->napi);
	पूर्ण

	netअगर_tx_start_all_queues(pp->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_ethtool_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
				   स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	/* Current code क्रम Armada 3700 करोesn't support RSS features yet */
	अगर (pp->neta_armada3700)
		वापस -EOPNOTSUPP;

	/* We require at least one supported parameter to be changed
	 * and no change in any of the unsupported parameters
	 */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;

	अगर (!indir)
		वापस 0;

	स_नकल(pp->indir, indir, MVNETA_RSS_LU_TABLE_SIZE);

	वापस mvneta_config_rss(pp);
पूर्ण

अटल पूर्णांक mvneta_ethtool_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key,
				   u8 *hfunc)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	/* Current code क्रम Armada 3700 करोesn't support RSS features yet */
	अगर (pp->neta_armada3700)
		वापस -EOPNOTSUPP;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (!indir)
		वापस 0;

	स_नकल(indir, pp->indir, MVNETA_RSS_LU_TABLE_SIZE);

	वापस 0;
पूर्ण

अटल व्योम mvneta_ethtool_get_wol(काष्ठा net_device *dev,
				   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	phylink_ethtool_get_wol(pp->phylink, wol);
पूर्ण

अटल पूर्णांक mvneta_ethtool_set_wol(काष्ठा net_device *dev,
				  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	पूर्णांक ret;

	ret = phylink_ethtool_set_wol(pp->phylink, wol);
	अगर (!ret)
		device_set_wakeup_enable(&dev->dev, !!wol->wolopts);

	वापस ret;
पूर्ण

अटल पूर्णांक mvneta_ethtool_get_eee(काष्ठा net_device *dev,
				  काष्ठा ethtool_eee *eee)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	u32 lpi_ctl0;

	lpi_ctl0 = mvreg_पढ़ो(pp, MVNETA_LPI_CTRL_0);

	eee->eee_enabled = pp->eee_enabled;
	eee->eee_active = pp->eee_active;
	eee->tx_lpi_enabled = pp->tx_lpi_enabled;
	eee->tx_lpi_समयr = (lpi_ctl0) >> 8; // * scale;

	वापस phylink_ethtool_get_eee(pp->phylink, eee);
पूर्ण

अटल पूर्णांक mvneta_ethtool_set_eee(काष्ठा net_device *dev,
				  काष्ठा ethtool_eee *eee)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	u32 lpi_ctl0;

	/* The Armada 37x करोcuments करो not give limits क्रम this other than
	 * it being an 8-bit रेजिस्टर.
	 */
	अगर (eee->tx_lpi_enabled && eee->tx_lpi_समयr > 255)
		वापस -EINVAL;

	lpi_ctl0 = mvreg_पढ़ो(pp, MVNETA_LPI_CTRL_0);
	lpi_ctl0 &= ~(0xff << 8);
	lpi_ctl0 |= eee->tx_lpi_समयr << 8;
	mvreg_ग_लिखो(pp, MVNETA_LPI_CTRL_0, lpi_ctl0);

	pp->eee_enabled = eee->eee_enabled;
	pp->tx_lpi_enabled = eee->tx_lpi_enabled;

	mvneta_set_eee(pp, eee->tx_lpi_enabled && eee->eee_enabled);

	वापस phylink_ethtool_set_eee(pp->phylink, eee);
पूर्ण

अटल व्योम mvneta_clear_rx_prio_map(काष्ठा mvneta_port *pp)
अणु
	mvreg_ग_लिखो(pp, MVNETA_VLAN_PRIO_TO_RXQ, 0);
पूर्ण

अटल व्योम mvneta_setup_rx_prio_map(काष्ठा mvneta_port *pp)
अणु
	u32 val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < rxq_number; i++)
		val |= MVNETA_VLAN_PRIO_RXQ_MAP(i, pp->prio_tc_map[i]);

	mvreg_ग_लिखो(pp, MVNETA_VLAN_PRIO_TO_RXQ, val);
पूर्ण

अटल पूर्णांक mvneta_setup_mqprio(काष्ठा net_device *dev,
			       काष्ठा tc_mqprio_qopt *qopt)
अणु
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	u8 num_tc;
	पूर्णांक i;

	qopt->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	num_tc = qopt->num_tc;

	अगर (num_tc > rxq_number)
		वापस -EINVAL;

	अगर (!num_tc) अणु
		mvneta_clear_rx_prio_map(pp);
		netdev_reset_tc(dev);
		वापस 0;
	पूर्ण

	स_नकल(pp->prio_tc_map, qopt->prio_tc_map, माप(pp->prio_tc_map));

	mvneta_setup_rx_prio_map(pp);

	netdev_set_num_tc(dev, qopt->num_tc);
	क्रम (i = 0; i < qopt->num_tc; i++)
		netdev_set_tc_queue(dev, i, qopt->count[i], qopt->offset[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			   व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस mvneta_setup_mqprio(dev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops mvneta_netdev_ops = अणु
	.nकरो_खोलो            = mvneta_खोलो,
	.nकरो_stop            = mvneta_stop,
	.nकरो_start_xmit      = mvneta_tx,
	.nकरो_set_rx_mode     = mvneta_set_rx_mode,
	.nकरो_set_mac_address = mvneta_set_mac_addr,
	.nकरो_change_mtu      = mvneta_change_mtu,
	.nकरो_fix_features    = mvneta_fix_features,
	.nकरो_get_stats64     = mvneta_get_stats64,
	.nकरो_करो_ioctl        = mvneta_ioctl,
	.nकरो_bpf	     = mvneta_xdp,
	.nकरो_xdp_xmit        = mvneta_xdp_xmit,
	.nकरो_setup_tc	     = mvneta_setup_tc,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops mvneta_eth_tool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.nway_reset	= mvneta_ethtool_nway_reset,
	.get_link       = ethtool_op_get_link,
	.set_coalesce   = mvneta_ethtool_set_coalesce,
	.get_coalesce   = mvneta_ethtool_get_coalesce,
	.get_drvinfo    = mvneta_ethtool_get_drvinfo,
	.get_ringparam  = mvneta_ethtool_get_ringparam,
	.set_ringparam	= mvneta_ethtool_set_ringparam,
	.get_छोड़ोparam	= mvneta_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam	= mvneta_ethtool_set_छोड़ोparam,
	.get_strings	= mvneta_ethtool_get_strings,
	.get_ethtool_stats = mvneta_ethtool_get_stats,
	.get_sset_count	= mvneta_ethtool_get_sset_count,
	.get_rxfh_indir_size = mvneta_ethtool_get_rxfh_indir_size,
	.get_rxnfc	= mvneta_ethtool_get_rxnfc,
	.get_rxfh	= mvneta_ethtool_get_rxfh,
	.set_rxfh	= mvneta_ethtool_set_rxfh,
	.get_link_ksettings = mvneta_ethtool_get_link_ksettings,
	.set_link_ksettings = mvneta_ethtool_set_link_ksettings,
	.get_wol        = mvneta_ethtool_get_wol,
	.set_wol        = mvneta_ethtool_set_wol,
	.get_eee	= mvneta_ethtool_get_eee,
	.set_eee	= mvneta_ethtool_set_eee,
पूर्ण;

/* Initialize hw */
अटल पूर्णांक mvneta_init(काष्ठा device *dev, काष्ठा mvneta_port *pp)
अणु
	पूर्णांक queue;

	/* Disable port */
	mvneta_port_disable(pp);

	/* Set port शेष values */
	mvneta_शेषs_set(pp);

	pp->txqs = devm_kसुस्मृति(dev, txq_number, माप(*pp->txqs), GFP_KERNEL);
	अगर (!pp->txqs)
		वापस -ENOMEM;

	/* Initialize TX descriptor rings */
	क्रम (queue = 0; queue < txq_number; queue++) अणु
		काष्ठा mvneta_tx_queue *txq = &pp->txqs[queue];
		txq->id = queue;
		txq->size = pp->tx_ring_size;
		txq->करोne_pkts_coal = MVNETA_TXDONE_COAL_PKTS;
	पूर्ण

	pp->rxqs = devm_kसुस्मृति(dev, rxq_number, माप(*pp->rxqs), GFP_KERNEL);
	अगर (!pp->rxqs)
		वापस -ENOMEM;

	/* Create Rx descriptor rings */
	क्रम (queue = 0; queue < rxq_number; queue++) अणु
		काष्ठा mvneta_rx_queue *rxq = &pp->rxqs[queue];
		rxq->id = queue;
		rxq->size = pp->rx_ring_size;
		rxq->pkts_coal = MVNETA_RX_COAL_PKTS;
		rxq->समय_coal = MVNETA_RX_COAL_USEC;
		rxq->buf_virt_addr
			= devm_kदो_स्मृति_array(pp->dev->dev.parent,
					     rxq->size,
					     माप(*rxq->buf_virt_addr),
					     GFP_KERNEL);
		अगर (!rxq->buf_virt_addr)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* platक्रमm glue : initialize decoding winकरोws */
अटल व्योम mvneta_conf_mbus_winकरोws(काष्ठा mvneta_port *pp,
				     स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	u32 win_enable;
	u32 win_protect;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		mvreg_ग_लिखो(pp, MVNETA_WIN_BASE(i), 0);
		mvreg_ग_लिखो(pp, MVNETA_WIN_SIZE(i), 0);

		अगर (i < 4)
			mvreg_ग_लिखो(pp, MVNETA_WIN_REMAP(i), 0);
	पूर्ण

	win_enable = 0x3f;
	win_protect = 0;

	अगर (dram) अणु
		क्रम (i = 0; i < dram->num_cs; i++) अणु
			स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

			mvreg_ग_लिखो(pp, MVNETA_WIN_BASE(i),
				    (cs->base & 0xffff0000) |
				    (cs->mbus_attr << 8) |
				    dram->mbus_dram_target_id);

			mvreg_ग_लिखो(pp, MVNETA_WIN_SIZE(i),
				    (cs->size - 1) & 0xffff0000);

			win_enable &= ~(1 << i);
			win_protect |= 3 << (2 * i);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* For Armada3700 खोलो शेष 4GB Mbus winकरोw, leaving
		 * arbitration of target/attribute to a dअगरferent layer
		 * of configuration.
		 */
		mvreg_ग_लिखो(pp, MVNETA_WIN_SIZE(0), 0xffff0000);
		win_enable &= ~BIT(0);
		win_protect = 3;
	पूर्ण

	mvreg_ग_लिखो(pp, MVNETA_BASE_ADDR_ENABLE, win_enable);
	mvreg_ग_लिखो(pp, MVNETA_ACCESS_PROTECT_ENABLE, win_protect);
पूर्ण

/* Power up the port */
अटल पूर्णांक mvneta_port_घातer_up(काष्ठा mvneta_port *pp, पूर्णांक phy_mode)
अणु
	/* MAC Cause रेजिस्टर should be cleared */
	mvreg_ग_लिखो(pp, MVNETA_UNIT_INTR_CAUSE, 0);

	अगर (phy_mode != PHY_INTERFACE_MODE_QSGMII &&
	    phy_mode != PHY_INTERFACE_MODE_SGMII &&
	    !phy_पूर्णांकerface_mode_is_8023z(phy_mode) &&
	    !phy_पूर्णांकerface_mode_is_rgmii(phy_mode))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Device initialization routine */
अटल पूर्णांक mvneta_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा device_node *bm_node;
	काष्ठा mvneta_port *pp;
	काष्ठा net_device *dev;
	काष्ठा phylink *phylink;
	काष्ठा phy *comphy;
	अक्षर hw_mac_addr[ETH_ALEN];
	phy_पूर्णांकerface_t phy_mode;
	स्थिर अक्षर *mac_from;
	पूर्णांक tx_csum_limit;
	पूर्णांक err;
	पूर्णांक cpu;

	dev = devm_alloc_etherdev_mqs(&pdev->dev, माप(काष्ठा mvneta_port),
				      txq_number, rxq_number);
	अगर (!dev)
		वापस -ENOMEM;

	dev->irq = irq_of_parse_and_map(dn, 0);
	अगर (dev->irq == 0)
		वापस -EINVAL;

	err = of_get_phy_mode(dn, &phy_mode);
	अगर (err) अणु
		dev_err(&pdev->dev, "incorrect phy-mode\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	comphy = devm_of_phy_get(&pdev->dev, dn, शून्य);
	अगर (comphy == ERR_PTR(-EPROBE_DEFER)) अणु
		err = -EPROBE_DEFER;
		जाओ err_मुक्त_irq;
	पूर्ण अन्यथा अगर (IS_ERR(comphy)) अणु
		comphy = शून्य;
	पूर्ण

	pp = netdev_priv(dev);
	spin_lock_init(&pp->lock);

	pp->phylink_config.dev = &dev->dev;
	pp->phylink_config.type = PHYLINK_NETDEV;

	phylink = phylink_create(&pp->phylink_config, pdev->dev.fwnode,
				 phy_mode, &mvneta_phylink_ops);
	अगर (IS_ERR(phylink)) अणु
		err = PTR_ERR(phylink);
		जाओ err_मुक्त_irq;
	पूर्ण

	dev->tx_queue_len = MVNETA_MAX_TXD;
	dev->watchकरोg_समयo = 5 * HZ;
	dev->netdev_ops = &mvneta_netdev_ops;

	dev->ethtool_ops = &mvneta_eth_tool_ops;

	pp->phylink = phylink;
	pp->comphy = comphy;
	pp->phy_पूर्णांकerface = phy_mode;
	pp->dn = dn;

	pp->rxq_def = rxq_def;
	pp->indir[0] = rxq_def;

	/* Get special SoC configurations */
	अगर (of_device_is_compatible(dn, "marvell,armada-3700-neta"))
		pp->neta_armada3700 = true;

	pp->clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(pp->clk))
		pp->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pp->clk)) अणु
		err = PTR_ERR(pp->clk);
		जाओ err_मुक्त_phylink;
	पूर्ण

	clk_prepare_enable(pp->clk);

	pp->clk_bus = devm_clk_get(&pdev->dev, "bus");
	अगर (!IS_ERR(pp->clk_bus))
		clk_prepare_enable(pp->clk_bus);

	pp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pp->base)) अणु
		err = PTR_ERR(pp->base);
		जाओ err_clk;
	पूर्ण

	/* Alloc per-cpu port काष्ठाure */
	pp->ports = alloc_percpu(काष्ठा mvneta_pcpu_port);
	अगर (!pp->ports) अणु
		err = -ENOMEM;
		जाओ err_clk;
	पूर्ण

	/* Alloc per-cpu stats */
	pp->stats = netdev_alloc_pcpu_stats(काष्ठा mvneta_pcpu_stats);
	अगर (!pp->stats) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_ports;
	पूर्ण

	err = of_get_mac_address(dn, dev->dev_addr);
	अगर (!err) अणु
		mac_from = "device tree";
	पूर्ण अन्यथा अणु
		mvneta_get_mac_addr(pp, hw_mac_addr);
		अगर (is_valid_ether_addr(hw_mac_addr)) अणु
			mac_from = "hardware";
			स_नकल(dev->dev_addr, hw_mac_addr, ETH_ALEN);
		पूर्ण अन्यथा अणु
			mac_from = "random";
			eth_hw_addr_अक्रमom(dev);
		पूर्ण
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dn, "tx-csum-limit", &tx_csum_limit)) अणु
		अगर (tx_csum_limit < 0 ||
		    tx_csum_limit > MVNETA_TX_CSUM_MAX_SIZE) अणु
			tx_csum_limit = MVNETA_TX_CSUM_DEF_SIZE;
			dev_info(&pdev->dev,
				 "Wrong TX csum limit in DT, set to %dB\n",
				 MVNETA_TX_CSUM_DEF_SIZE);
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(dn, "marvell,armada-370-neta")) अणु
		tx_csum_limit = MVNETA_TX_CSUM_DEF_SIZE;
	पूर्ण अन्यथा अणु
		tx_csum_limit = MVNETA_TX_CSUM_MAX_SIZE;
	पूर्ण

	pp->tx_csum_limit = tx_csum_limit;

	pp->dram_target_info = mv_mbus_dram_info();
	/* Armada3700 requires setting शेष configuration of Mbus
	 * winकरोws, however without using filled mbus_dram_target_info
	 * काष्ठाure.
	 */
	अगर (pp->dram_target_info || pp->neta_armada3700)
		mvneta_conf_mbus_winकरोws(pp, pp->dram_target_info);

	pp->tx_ring_size = MVNETA_MAX_TXD;
	pp->rx_ring_size = MVNETA_MAX_RXD;

	pp->dev = dev;
	SET_NETDEV_DEV(dev, &pdev->dev);

	pp->id = global_port_id++;

	/* Obtain access to BM resources अगर enabled and alपढ़ोy initialized */
	bm_node = of_parse_phandle(dn, "buffer-manager", 0);
	अगर (bm_node) अणु
		pp->bm_priv = mvneta_bm_get(bm_node);
		अगर (pp->bm_priv) अणु
			err = mvneta_bm_port_init(pdev, pp);
			अगर (err < 0) अणु
				dev_info(&pdev->dev,
					 "use SW buffer management\n");
				mvneta_bm_put(pp->bm_priv);
				pp->bm_priv = शून्य;
			पूर्ण
		पूर्ण
		/* Set RX packet offset correction क्रम platक्रमms, whose
		 * NET_SKB_PAD, exceeds 64B. It should be 64B क्रम 64-bit
		 * platक्रमms and 0B क्रम 32-bit ones.
		 */
		pp->rx_offset_correction = max(0,
					       NET_SKB_PAD -
					       MVNETA_RX_PKT_OFFSET_CORRECTION);
	पूर्ण
	of_node_put(bm_node);

	/* sw buffer management */
	अगर (!pp->bm_priv)
		pp->rx_offset_correction = MVNETA_SKB_HEADROOM;

	err = mvneta_init(&pdev->dev, pp);
	अगर (err < 0)
		जाओ err_netdev;

	err = mvneta_port_घातer_up(pp, pp->phy_पूर्णांकerface);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "can't power up port\n");
		जाओ err_netdev;
	पूर्ण

	/* Armada3700 network controller करोes not support per-cpu
	 * operation, so only single NAPI should be initialized.
	 */
	अगर (pp->neta_armada3700) अणु
		netअगर_napi_add(dev, &pp->napi, mvneta_poll, NAPI_POLL_WEIGHT);
	पूर्ण अन्यथा अणु
		क्रम_each_present_cpu(cpu) अणु
			काष्ठा mvneta_pcpu_port *port =
				per_cpu_ptr(pp->ports, cpu);

			netअगर_napi_add(dev, &port->napi, mvneta_poll,
				       NAPI_POLL_WEIGHT);
			port->pp = pp;
		पूर्ण
	पूर्ण

	dev->features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			NETIF_F_TSO | NETIF_F_RXCSUM;
	dev->hw_features |= dev->features;
	dev->vlan_features |= dev->features;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	dev->gso_max_segs = MVNETA_MAX_TSO_SEGS;

	/* MTU range: 68 - 9676 */
	dev->min_mtu = ETH_MIN_MTU;
	/* 9676 == 9700 - 20 and rounding to 8 */
	dev->max_mtu = 9676;

	err = रेजिस्टर_netdev(dev);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register\n");
		जाओ err_netdev;
	पूर्ण

	netdev_info(dev, "Using %s mac address %pM\n", mac_from,
		    dev->dev_addr);

	platक्रमm_set_drvdata(pdev, pp->dev);

	वापस 0;

err_netdev:
	अगर (pp->bm_priv) अणु
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_दीर्घ, 1 << pp->id);
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_लघु,
				       1 << pp->id);
		mvneta_bm_put(pp->bm_priv);
	पूर्ण
	मुक्त_percpu(pp->stats);
err_मुक्त_ports:
	मुक्त_percpu(pp->ports);
err_clk:
	clk_disable_unprepare(pp->clk_bus);
	clk_disable_unprepare(pp->clk);
err_मुक्त_phylink:
	अगर (pp->phylink)
		phylink_destroy(pp->phylink);
err_मुक्त_irq:
	irq_dispose_mapping(dev->irq);
	वापस err;
पूर्ण

/* Device removal routine */
अटल पूर्णांक mvneta_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device  *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	clk_disable_unprepare(pp->clk_bus);
	clk_disable_unprepare(pp->clk);
	मुक्त_percpu(pp->ports);
	मुक्त_percpu(pp->stats);
	irq_dispose_mapping(dev->irq);
	phylink_destroy(pp->phylink);

	अगर (pp->bm_priv) अणु
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_दीर्घ, 1 << pp->id);
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_लघु,
				       1 << pp->id);
		mvneta_bm_put(pp->bm_priv);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mvneta_suspend(काष्ठा device *device)
अणु
	पूर्णांक queue;
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा mvneta_port *pp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		जाओ clean_निकास;

	अगर (!pp->neta_armada3700) अणु
		spin_lock(&pp->lock);
		pp->is_stopped = true;
		spin_unlock(&pp->lock);

		cpuhp_state_हटाओ_instance_nocalls(online_hpstate,
						    &pp->node_online);
		cpuhp_state_हटाओ_instance_nocalls(CPUHP_NET_MVNETA_DEAD,
						    &pp->node_dead);
	पूर्ण

	rtnl_lock();
	mvneta_stop_dev(pp);
	rtnl_unlock();

	क्रम (queue = 0; queue < rxq_number; queue++) अणु
		काष्ठा mvneta_rx_queue *rxq = &pp->rxqs[queue];

		mvneta_rxq_drop_pkts(pp, rxq);
	पूर्ण

	क्रम (queue = 0; queue < txq_number; queue++) अणु
		काष्ठा mvneta_tx_queue *txq = &pp->txqs[queue];

		mvneta_txq_hw_deinit(pp, txq);
	पूर्ण

clean_निकास:
	netअगर_device_detach(dev);
	clk_disable_unprepare(pp->clk_bus);
	clk_disable_unprepare(pp->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_resume(काष्ठा device *device)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(device);
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा mvneta_port *pp = netdev_priv(dev);
	पूर्णांक err, queue;

	clk_prepare_enable(pp->clk);
	अगर (!IS_ERR(pp->clk_bus))
		clk_prepare_enable(pp->clk_bus);
	अगर (pp->dram_target_info || pp->neta_armada3700)
		mvneta_conf_mbus_winकरोws(pp, pp->dram_target_info);
	अगर (pp->bm_priv) अणु
		err = mvneta_bm_port_init(pdev, pp);
		अगर (err < 0) अणु
			dev_info(&pdev->dev, "use SW buffer management\n");
			pp->rx_offset_correction = MVNETA_SKB_HEADROOM;
			pp->bm_priv = शून्य;
		पूर्ण
	पूर्ण
	mvneta_शेषs_set(pp);
	err = mvneta_port_घातer_up(pp, pp->phy_पूर्णांकerface);
	अगर (err < 0) अणु
		dev_err(device, "can't power up port\n");
		वापस err;
	पूर्ण

	netअगर_device_attach(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	क्रम (queue = 0; queue < rxq_number; queue++) अणु
		काष्ठा mvneta_rx_queue *rxq = &pp->rxqs[queue];

		rxq->next_desc_to_proc = 0;
		mvneta_rxq_hw_init(pp, rxq);
	पूर्ण

	क्रम (queue = 0; queue < txq_number; queue++) अणु
		काष्ठा mvneta_tx_queue *txq = &pp->txqs[queue];

		txq->next_desc_to_proc = 0;
		mvneta_txq_hw_init(pp, txq);
	पूर्ण

	अगर (!pp->neta_armada3700) अणु
		spin_lock(&pp->lock);
		pp->is_stopped = false;
		spin_unlock(&pp->lock);
		cpuhp_state_add_instance_nocalls(online_hpstate,
						 &pp->node_online);
		cpuhp_state_add_instance_nocalls(CPUHP_NET_MVNETA_DEAD,
						 &pp->node_dead);
	पूर्ण

	rtnl_lock();
	mvneta_start_dev(pp);
	rtnl_unlock();
	mvneta_set_rx_mode(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mvneta_pm_ops, mvneta_suspend, mvneta_resume);

अटल स्थिर काष्ठा of_device_id mvneta_match[] = अणु
	अणु .compatible = "marvell,armada-370-neta" पूर्ण,
	अणु .compatible = "marvell,armada-xp-neta" पूर्ण,
	अणु .compatible = "marvell,armada-3700-neta" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mvneta_match);

अटल काष्ठा platक्रमm_driver mvneta_driver = अणु
	.probe = mvneta_probe,
	.हटाओ = mvneta_हटाओ,
	.driver = अणु
		.name = MVNETA_DRIVER_NAME,
		.of_match_table = mvneta_match,
		.pm = &mvneta_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mvneta_driver_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN, "net/mvneta:online",
				      mvneta_cpu_online,
				      mvneta_cpu_करोwn_prepare);
	अगर (ret < 0)
		जाओ out;
	online_hpstate = ret;
	ret = cpuhp_setup_state_multi(CPUHP_NET_MVNETA_DEAD, "net/mvneta:dead",
				      शून्य, mvneta_cpu_dead);
	अगर (ret)
		जाओ err_dead;

	ret = platक्रमm_driver_रेजिस्टर(&mvneta_driver);
	अगर (ret)
		जाओ err;
	वापस 0;

err:
	cpuhp_हटाओ_multi_state(CPUHP_NET_MVNETA_DEAD);
err_dead:
	cpuhp_हटाओ_multi_state(online_hpstate);
out:
	वापस ret;
पूर्ण
module_init(mvneta_driver_init);

अटल व्योम __निकास mvneta_driver_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mvneta_driver);
	cpuhp_हटाओ_multi_state(CPUHP_NET_MVNETA_DEAD);
	cpuhp_हटाओ_multi_state(online_hpstate);
पूर्ण
module_निकास(mvneta_driver_निकास);

MODULE_DESCRIPTION("Marvell NETA Ethernet Driver - www.marvell.com");
MODULE_AUTHOR("Rami Rosen <rosenr@marvell.com>, Thomas Petazzoni <thomas.petazzoni@free-electrons.com>");
MODULE_LICENSE("GPL");

module_param(rxq_number, पूर्णांक, 0444);
module_param(txq_number, पूर्णांक, 0444);

module_param(rxq_def, पूर्णांक, 0444);
module_param(rx_copyअवरोध, पूर्णांक, 0644);
