<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 */

/* Qualcomm Technologies, Inc. EMAC Ethernet Controller MAC layer support
 */

#समावेश <linux/tcp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <net/ip6_checksum.h>
#समावेश "emac.h"
#समावेश "emac-sgmii.h"

/* EMAC_MAC_CTRL */
#घोषणा SINGLE_PAUSE_MODE       	0x10000000
#घोषणा DEBUG_MODE                      0x08000000
#घोषणा BROAD_EN                        0x04000000
#घोषणा MULTI_ALL                       0x02000000
#घोषणा RX_CHKSUM_EN                    0x01000000
#घोषणा HUGE                            0x00800000
#घोषणा SPEED(x)			(((x) & 0x3) << 20)
#घोषणा SPEED_MASK			SPEED(0x3)
#घोषणा SIMR                            0x00080000
#घोषणा TPAUSE                          0x00010000
#घोषणा PROM_MODE                       0x00008000
#घोषणा VLAN_STRIP                      0x00004000
#घोषणा PRLEN_BMSK                      0x00003c00
#घोषणा PRLEN_SHFT                      10
#घोषणा HUGEN                           0x00000200
#घोषणा FLCHK                           0x00000100
#घोषणा PCRCE                           0x00000080
#घोषणा CRCE                            0x00000040
#घोषणा FULLD                           0x00000020
#घोषणा MAC_LP_EN                       0x00000010
#घोषणा RXFC                            0x00000008
#घोषणा TXFC                            0x00000004
#घोषणा RXEN                            0x00000002
#घोषणा TXEN                            0x00000001

/* EMAC_DESC_CTRL_3 */
#घोषणा RFD_RING_SIZE_BMSK                                       0xfff

/* EMAC_DESC_CTRL_4 */
#घोषणा RX_BUFFER_SIZE_BMSK                                     0xffff

/* EMAC_DESC_CTRL_6 */
#घोषणा RRD_RING_SIZE_BMSK                                       0xfff

/* EMAC_DESC_CTRL_9 */
#घोषणा TPD_RING_SIZE_BMSK                                      0xffff

/* EMAC_TXQ_CTRL_0 */
#घोषणा NUM_TXF_BURST_PREF_BMSK                             0xffff0000
#घोषणा NUM_TXF_BURST_PREF_SHFT                                     16
#घोषणा LS_8023_SP                                                0x80
#घोषणा TXQ_MODE                                                  0x40
#घोषणा TXQ_EN                                                    0x20
#घोषणा IP_OP_SP                                                  0x10
#घोषणा NUM_TPD_BURST_PREF_BMSK                                    0xf
#घोषणा NUM_TPD_BURST_PREF_SHFT                                      0

/* EMAC_TXQ_CTRL_1 */
#घोषणा JUMBO_TASK_OFFLOAD_THRESHOLD_BMSK                        0x7ff

/* EMAC_TXQ_CTRL_2 */
#घोषणा TXF_HWM_BMSK                                         0xfff0000
#घोषणा TXF_LWM_BMSK                                             0xfff

/* EMAC_RXQ_CTRL_0 */
#घोषणा RXQ_EN                                                 BIT(31)
#घोषणा CUT_THRU_EN                                            BIT(30)
#घोषणा RSS_HASH_EN                                            BIT(29)
#घोषणा NUM_RFD_BURST_PREF_BMSK                              0x3f00000
#घोषणा NUM_RFD_BURST_PREF_SHFT                                     20
#घोषणा IDT_TABLE_SIZE_BMSK                                    0x1ff00
#घोषणा IDT_TABLE_SIZE_SHFT                                          8
#घोषणा SP_IPV6                                                   0x80

/* EMAC_RXQ_CTRL_1 */
#घोषणा JUMBO_1KAH_BMSK                                         0xf000
#घोषणा JUMBO_1KAH_SHFT                                             12
#घोषणा RFD_PREF_LOW_TH                                           0x10
#घोषणा RFD_PREF_LOW_THRESHOLD_BMSK                              0xfc0
#घोषणा RFD_PREF_LOW_THRESHOLD_SHFT                                  6
#घोषणा RFD_PREF_UP_TH                                            0x10
#घोषणा RFD_PREF_UP_THRESHOLD_BMSK                                0x3f
#घोषणा RFD_PREF_UP_THRESHOLD_SHFT                                   0

/* EMAC_RXQ_CTRL_2 */
#घोषणा RXF_DOF_THRESFHOLD                                       0x1a0
#घोषणा RXF_DOF_THRESHOLD_BMSK                               0xfff0000
#घोषणा RXF_DOF_THRESHOLD_SHFT                                      16
#घोषणा RXF_UOF_THRESFHOLD                                        0xbe
#घोषणा RXF_UOF_THRESHOLD_BMSK                                   0xfff
#घोषणा RXF_UOF_THRESHOLD_SHFT                                       0

/* EMAC_RXQ_CTRL_3 */
#घोषणा RXD_TIMER_BMSK                                      0xffff0000
#घोषणा RXD_THRESHOLD_BMSK                                       0xfff
#घोषणा RXD_THRESHOLD_SHFT                                           0

/* EMAC_DMA_CTRL */
#घोषणा DMAW_DLY_CNT_BMSK                                      0xf0000
#घोषणा DMAW_DLY_CNT_SHFT                                           16
#घोषणा DMAR_DLY_CNT_BMSK                                       0xf800
#घोषणा DMAR_DLY_CNT_SHFT                                           11
#घोषणा DMAR_REQ_PRI                                             0x400
#घोषणा REGWRBLEN_BMSK                                           0x380
#घोषणा REGWRBLEN_SHFT                                               7
#घोषणा REGRDBLEN_BMSK                                            0x70
#घोषणा REGRDBLEN_SHFT                                               4
#घोषणा OUT_ORDER_MODE                                             0x4
#घोषणा ENH_ORDER_MODE                                             0x2
#घोषणा IN_ORDER_MODE                                              0x1

/* EMAC_MAILBOX_13 */
#घोषणा RFD3_PROC_IDX_BMSK                                   0xfff0000
#घोषणा RFD3_PROC_IDX_SHFT                                          16
#घोषणा RFD3_PROD_IDX_BMSK                                       0xfff
#घोषणा RFD3_PROD_IDX_SHFT                                           0

/* EMAC_MAILBOX_2 */
#घोषणा NTPD_CONS_IDX_BMSK                                  0xffff0000
#घोषणा NTPD_CONS_IDX_SHFT                                          16

/* EMAC_MAILBOX_3 */
#घोषणा RFD0_CONS_IDX_BMSK                                       0xfff
#घोषणा RFD0_CONS_IDX_SHFT                                           0

/* EMAC_MAILBOX_11 */
#घोषणा H3TPD_PROD_IDX_BMSK                                 0xffff0000
#घोषणा H3TPD_PROD_IDX_SHFT                                         16

/* EMAC_AXI_MAST_CTRL */
#घोषणा DATA_BYTE_SWAP                                             0x8
#घोषणा MAX_BOUND                                                  0x2
#घोषणा MAX_BTYPE                                                  0x1

/* EMAC_MAILBOX_12 */
#घोषणा H3TPD_CONS_IDX_BMSK                                 0xffff0000
#घोषणा H3TPD_CONS_IDX_SHFT                                         16

/* EMAC_MAILBOX_9 */
#घोषणा H2TPD_PROD_IDX_BMSK                                     0xffff
#घोषणा H2TPD_PROD_IDX_SHFT                                          0

/* EMAC_MAILBOX_10 */
#घोषणा H1TPD_CONS_IDX_BMSK                                 0xffff0000
#घोषणा H1TPD_CONS_IDX_SHFT                                         16
#घोषणा H2TPD_CONS_IDX_BMSK                                     0xffff
#घोषणा H2TPD_CONS_IDX_SHFT                                          0

/* EMAC_ATHR_HEADER_CTRL */
#घोषणा HEADER_CNT_EN                                              0x2
#घोषणा HEADER_ENABLE                                              0x1

/* EMAC_MAILBOX_0 */
#घोषणा RFD0_PROC_IDX_BMSK                                   0xfff0000
#घोषणा RFD0_PROC_IDX_SHFT                                          16
#घोषणा RFD0_PROD_IDX_BMSK                                       0xfff
#घोषणा RFD0_PROD_IDX_SHFT                                           0

/* EMAC_MAILBOX_5 */
#घोषणा RFD1_PROC_IDX_BMSK                                   0xfff0000
#घोषणा RFD1_PROC_IDX_SHFT                                          16
#घोषणा RFD1_PROD_IDX_BMSK                                       0xfff
#घोषणा RFD1_PROD_IDX_SHFT                                           0

/* EMAC_MISC_CTRL */
#घोषणा RX_UNCPL_INT_EN                                            0x1

/* EMAC_MAILBOX_7 */
#घोषणा RFD2_CONS_IDX_BMSK                                   0xfff0000
#घोषणा RFD2_CONS_IDX_SHFT                                          16
#घोषणा RFD1_CONS_IDX_BMSK                                       0xfff
#घोषणा RFD1_CONS_IDX_SHFT                                           0

/* EMAC_MAILBOX_8 */
#घोषणा RFD3_CONS_IDX_BMSK                                       0xfff
#घोषणा RFD3_CONS_IDX_SHFT                                           0

/* EMAC_MAILBOX_15 */
#घोषणा NTPD_PROD_IDX_BMSK                                      0xffff
#घोषणा NTPD_PROD_IDX_SHFT                                           0

/* EMAC_MAILBOX_16 */
#घोषणा H1TPD_PROD_IDX_BMSK                                     0xffff
#घोषणा H1TPD_PROD_IDX_SHFT                                          0

#घोषणा RXQ0_RSS_HSTYP_IPV6_TCP_EN                                0x20
#घोषणा RXQ0_RSS_HSTYP_IPV6_EN                                    0x10
#घोषणा RXQ0_RSS_HSTYP_IPV4_TCP_EN                                 0x8
#घोषणा RXQ0_RSS_HSTYP_IPV4_EN                                     0x4

/* EMAC_EMAC_WRAPPER_TX_TS_INX */
#घोषणा EMAC_WRAPPER_TX_TS_EMPTY                               BIT(31)
#घोषणा EMAC_WRAPPER_TX_TS_INX_BMSK                             0xffff

काष्ठा emac_skb_cb अणु
	u32           tpd_idx;
	अचिन्हित दीर्घ jअगरfies;
पूर्ण;

#घोषणा EMAC_SKB_CB(skb)	((काष्ठा emac_skb_cb *)(skb)->cb)
#घोषणा EMAC_RSS_IDT_SIZE	256
#घोषणा JUMBO_1KAH		0x4
#घोषणा RXD_TH			0x100
#घोषणा EMAC_TPD_LAST_FRAGMENT	0x80000000
#घोषणा EMAC_TPD_TSTAMP_SAVE	0x80000000

/* EMAC Errors in emac_rrd.word[3] */
#घोषणा EMAC_RRD_L4F		BIT(14)
#घोषणा EMAC_RRD_IPF		BIT(15)
#घोषणा EMAC_RRD_CRC		BIT(21)
#घोषणा EMAC_RRD_FAE		BIT(22)
#घोषणा EMAC_RRD_TRN		BIT(23)
#घोषणा EMAC_RRD_RNT		BIT(24)
#घोषणा EMAC_RRD_INC		BIT(25)
#घोषणा EMAC_RRD_FOV		BIT(29)
#घोषणा EMAC_RRD_LEN		BIT(30)

/* Error bits that will result in a received frame being discarded */
#घोषणा EMAC_RRD_ERROR (EMAC_RRD_IPF | EMAC_RRD_CRC | EMAC_RRD_FAE | \
			EMAC_RRD_TRN | EMAC_RRD_RNT | EMAC_RRD_INC | \
			EMAC_RRD_FOV | EMAC_RRD_LEN)
#घोषणा EMAC_RRD_STATS_DW_IDX 3

#घोषणा EMAC_RRD(RXQ, SIZE, IDX)	((RXQ)->rrd.v_addr + (SIZE * (IDX)))
#घोषणा EMAC_RFD(RXQ, SIZE, IDX)	((RXQ)->rfd.v_addr + (SIZE * (IDX)))
#घोषणा EMAC_TPD(TXQ, SIZE, IDX)	((TXQ)->tpd.v_addr + (SIZE * (IDX)))

#घोषणा GET_RFD_BUFFER(RXQ, IDX)	(&((RXQ)->rfd.rfbuff[(IDX)]))
#घोषणा GET_TPD_BUFFER(RTQ, IDX)	(&((RTQ)->tpd.tpbuff[(IDX)]))

#घोषणा EMAC_TX_POLL_HWTXTSTAMP_THRESHOLD	8

#घोषणा ISR_RX_PKT      (\
	RX_PKT_INT0     |\
	RX_PKT_INT1     |\
	RX_PKT_INT2     |\
	RX_PKT_INT3)

व्योम emac_mac_multicast_addr_set(काष्ठा emac_adapter *adpt, u8 *addr)
अणु
	u32 crc32, bit, reg, mta;

	/* Calculate the CRC of the MAC address */
	crc32 = ether_crc(ETH_ALEN, addr);

	/* The HASH Table is an array of 2 32-bit रेजिस्टरs. It is
	 * treated like an array of 64 bits (BitArray[hash_value]).
	 * Use the upper 6 bits of the above CRC as the hash value.
	 */
	reg = (crc32 >> 31) & 0x1;
	bit = (crc32 >> 26) & 0x1F;

	mta = पढ़ोl(adpt->base + EMAC_HASH_TAB_REG0 + (reg << 2));
	mta |= BIT(bit);
	ग_लिखोl(mta, adpt->base + EMAC_HASH_TAB_REG0 + (reg << 2));
पूर्ण

व्योम emac_mac_multicast_addr_clear(काष्ठा emac_adapter *adpt)
अणु
	ग_लिखोl(0, adpt->base + EMAC_HASH_TAB_REG0);
	ग_लिखोl(0, adpt->base + EMAC_HASH_TAB_REG1);
पूर्ण

/* definitions क्रम RSS */
#घोषणा EMAC_RSS_KEY(_i, _type) \
		(EMAC_RSS_KEY0 + ((_i) * माप(_type)))
#घोषणा EMAC_RSS_TBL(_i, _type) \
		(EMAC_IDT_TABLE0 + ((_i) * माप(_type)))

/* Config MAC modes */
व्योम emac_mac_mode_config(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा net_device *netdev = adpt->netdev;
	u32 mac;

	mac = पढ़ोl(adpt->base + EMAC_MAC_CTRL);
	mac &= ~(VLAN_STRIP | PROM_MODE | MULTI_ALL | MAC_LP_EN);

	अगर (netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		mac |= VLAN_STRIP;

	अगर (netdev->flags & IFF_PROMISC)
		mac |= PROM_MODE;

	अगर (netdev->flags & IFF_ALLMULTI)
		mac |= MULTI_ALL;

	ग_लिखोl(mac, adpt->base + EMAC_MAC_CTRL);
पूर्ण

/* Config descriptor rings */
अटल व्योम emac_mac_dma_rings_config(काष्ठा emac_adapter *adpt)
अणु
	/* TPD (Transmit Packet Descriptor) */
	ग_लिखोl(upper_32_bits(adpt->tx_q.tpd.dma_addr),
	       adpt->base + EMAC_DESC_CTRL_1);

	ग_लिखोl(lower_32_bits(adpt->tx_q.tpd.dma_addr),
	       adpt->base + EMAC_DESC_CTRL_8);

	ग_लिखोl(adpt->tx_q.tpd.count & TPD_RING_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTRL_9);

	/* RFD (Receive Free Descriptor) & RRD (Receive Return Descriptor) */
	ग_लिखोl(upper_32_bits(adpt->rx_q.rfd.dma_addr),
	       adpt->base + EMAC_DESC_CTRL_0);

	ग_लिखोl(lower_32_bits(adpt->rx_q.rfd.dma_addr),
	       adpt->base + EMAC_DESC_CTRL_2);
	ग_लिखोl(lower_32_bits(adpt->rx_q.rrd.dma_addr),
	       adpt->base + EMAC_DESC_CTRL_5);

	ग_लिखोl(adpt->rx_q.rfd.count & RFD_RING_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTRL_3);
	ग_लिखोl(adpt->rx_q.rrd.count & RRD_RING_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTRL_6);

	ग_लिखोl(adpt->rxbuf_size & RX_BUFFER_SIZE_BMSK,
	       adpt->base + EMAC_DESC_CTRL_4);

	ग_लिखोl(0, adpt->base + EMAC_DESC_CTRL_11);

	/* Load all of the base addresses above and ensure that triggering HW to
	 * पढ़ो ring poपूर्णांकers is flushed
	 */
	ग_लिखोl(1, adpt->base + EMAC_INTER_SRAM_PART9);
पूर्ण

/* Config transmit parameters */
अटल व्योम emac_mac_tx_config(काष्ठा emac_adapter *adpt)
अणु
	u32 val;

	ग_लिखोl((EMAC_MAX_TX_OFFLOAD_THRESH >> 3) &
	       JUMBO_TASK_OFFLOAD_THRESHOLD_BMSK, adpt->base + EMAC_TXQ_CTRL_1);

	val = (adpt->tpd_burst << NUM_TPD_BURST_PREF_SHFT) &
	       NUM_TPD_BURST_PREF_BMSK;

	val |= TXQ_MODE | LS_8023_SP;
	val |= (0x0100 << NUM_TXF_BURST_PREF_SHFT) &
		NUM_TXF_BURST_PREF_BMSK;

	ग_लिखोl(val, adpt->base + EMAC_TXQ_CTRL_0);
	emac_reg_update32(adpt->base + EMAC_TXQ_CTRL_2,
			  (TXF_HWM_BMSK | TXF_LWM_BMSK), 0);
पूर्ण

/* Config receive parameters */
अटल व्योम emac_mac_rx_config(काष्ठा emac_adapter *adpt)
अणु
	u32 val;

	val = (adpt->rfd_burst << NUM_RFD_BURST_PREF_SHFT) &
	       NUM_RFD_BURST_PREF_BMSK;
	val |= (SP_IPV6 | CUT_THRU_EN);

	ग_लिखोl(val, adpt->base + EMAC_RXQ_CTRL_0);

	val = पढ़ोl(adpt->base + EMAC_RXQ_CTRL_1);
	val &= ~(JUMBO_1KAH_BMSK | RFD_PREF_LOW_THRESHOLD_BMSK |
		 RFD_PREF_UP_THRESHOLD_BMSK);
	val |= (JUMBO_1KAH << JUMBO_1KAH_SHFT) |
		(RFD_PREF_LOW_TH << RFD_PREF_LOW_THRESHOLD_SHFT) |
		(RFD_PREF_UP_TH  << RFD_PREF_UP_THRESHOLD_SHFT);
	ग_लिखोl(val, adpt->base + EMAC_RXQ_CTRL_1);

	val = पढ़ोl(adpt->base + EMAC_RXQ_CTRL_2);
	val &= ~(RXF_DOF_THRESHOLD_BMSK | RXF_UOF_THRESHOLD_BMSK);
	val |= (RXF_DOF_THRESFHOLD  << RXF_DOF_THRESHOLD_SHFT) |
		(RXF_UOF_THRESFHOLD << RXF_UOF_THRESHOLD_SHFT);
	ग_लिखोl(val, adpt->base + EMAC_RXQ_CTRL_2);

	val = पढ़ोl(adpt->base + EMAC_RXQ_CTRL_3);
	val &= ~(RXD_TIMER_BMSK | RXD_THRESHOLD_BMSK);
	val |= RXD_TH << RXD_THRESHOLD_SHFT;
	ग_लिखोl(val, adpt->base + EMAC_RXQ_CTRL_3);
पूर्ण

/* Config dma */
अटल व्योम emac_mac_dma_config(काष्ठा emac_adapter *adpt)
अणु
	u32 dma_ctrl = DMAR_REQ_PRI;

	चयन (adpt->dma_order) अणु
	हाल emac_dma_ord_in:
		dma_ctrl |= IN_ORDER_MODE;
		अवरोध;
	हाल emac_dma_ord_enh:
		dma_ctrl |= ENH_ORDER_MODE;
		अवरोध;
	हाल emac_dma_ord_out:
		dma_ctrl |= OUT_ORDER_MODE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dma_ctrl |= (((u32)adpt->dmar_block) << REGRDBLEN_SHFT) &
						REGRDBLEN_BMSK;
	dma_ctrl |= (((u32)adpt->dmaw_block) << REGWRBLEN_SHFT) &
						REGWRBLEN_BMSK;
	dma_ctrl |= (((u32)adpt->dmar_dly_cnt) << DMAR_DLY_CNT_SHFT) &
						DMAR_DLY_CNT_BMSK;
	dma_ctrl |= (((u32)adpt->dmaw_dly_cnt) << DMAW_DLY_CNT_SHFT) &
						DMAW_DLY_CNT_BMSK;

	/* config DMA and ensure that configuration is flushed to HW */
	ग_लिखोl(dma_ctrl, adpt->base + EMAC_DMA_CTRL);
पूर्ण

/* set MAC address */
अटल व्योम emac_set_mac_address(काष्ठा emac_adapter *adpt, u8 *addr)
अणु
	u32 sta;

	/* क्रम example: 00-A0-C6-11-22-33
	 * 0<-->C6112233, 1<-->00A0.
	 */

	/* low 32bit word */
	sta = (((u32)addr[2]) << 24) | (((u32)addr[3]) << 16) |
	      (((u32)addr[4]) << 8)  | (((u32)addr[5]));
	ग_लिखोl(sta, adpt->base + EMAC_MAC_STA_ADDR0);

	/* hight 32bit word */
	sta = (((u32)addr[0]) << 8) | (u32)addr[1];
	ग_लिखोl(sta, adpt->base + EMAC_MAC_STA_ADDR1);
पूर्ण

अटल व्योम emac_mac_config(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा net_device *netdev = adpt->netdev;
	अचिन्हित पूर्णांक max_frame;
	u32 val;

	emac_set_mac_address(adpt, netdev->dev_addr);

	max_frame = netdev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	adpt->rxbuf_size = netdev->mtu > EMAC_DEF_RX_BUF_SIZE ?
		ALIGN(max_frame, 8) : EMAC_DEF_RX_BUF_SIZE;

	emac_mac_dma_rings_config(adpt);

	ग_लिखोl(netdev->mtu + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN,
	       adpt->base + EMAC_MAX_FRAM_LEN_CTRL);

	emac_mac_tx_config(adpt);
	emac_mac_rx_config(adpt);
	emac_mac_dma_config(adpt);

	val = पढ़ोl(adpt->base + EMAC_AXI_MAST_CTRL);
	val &= ~(DATA_BYTE_SWAP | MAX_BOUND);
	val |= MAX_BTYPE;
	ग_लिखोl(val, adpt->base + EMAC_AXI_MAST_CTRL);
	ग_लिखोl(0, adpt->base + EMAC_CLK_GATE_CTRL);
	ग_लिखोl(RX_UNCPL_INT_EN, adpt->base + EMAC_MISC_CTRL);
पूर्ण

व्योम emac_mac_reset(काष्ठा emac_adapter *adpt)
अणु
	emac_mac_stop(adpt);

	emac_reg_update32(adpt->base + EMAC_DMA_MAS_CTRL, 0, SOFT_RST);
	usleep_range(100, 150); /* reset may take up to 100usec */

	/* पूर्णांकerrupt clear-on-पढ़ो */
	emac_reg_update32(adpt->base + EMAC_DMA_MAS_CTRL, 0, INT_RD_CLR_EN);
पूर्ण

अटल व्योम emac_mac_start(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा phy_device *phydev = adpt->phydev;
	u32 mac, csr1;

	/* enable tx queue */
	emac_reg_update32(adpt->base + EMAC_TXQ_CTRL_0, 0, TXQ_EN);

	/* enable rx queue */
	emac_reg_update32(adpt->base + EMAC_RXQ_CTRL_0, 0, RXQ_EN);

	/* enable mac control */
	mac = पढ़ोl(adpt->base + EMAC_MAC_CTRL);
	csr1 = पढ़ोl(adpt->csr + EMAC_EMAC_WRAPPER_CSR1);

	mac |= TXEN | RXEN;     /* enable RX/TX */

	/* Configure MAC flow control. If set to स्वतःmatic, then match
	 * whatever the PHY करोes. Otherwise, enable or disable it, depending
	 * on what the user configured via ethtool.
	 */
	mac &= ~(RXFC | TXFC);

	अगर (adpt->स्वतःmatic) अणु
		/* If it's set to स्वतःmatic, then update our local values */
		adpt->rx_flow_control = phydev->छोड़ो;
		adpt->tx_flow_control = phydev->छोड़ो != phydev->asym_छोड़ो;
	पूर्ण
	mac |= adpt->rx_flow_control ? RXFC : 0;
	mac |= adpt->tx_flow_control ? TXFC : 0;

	/* setup link speed */
	mac &= ~SPEED_MASK;
	अगर (phydev->speed == SPEED_1000) अणु
		mac |= SPEED(2);
		csr1 |= FREQ_MODE;
	पूर्ण अन्यथा अणु
		mac |= SPEED(1);
		csr1 &= ~FREQ_MODE;
	पूर्ण

	अगर (phydev->duplex == DUPLEX_FULL)
		mac |= FULLD;
	अन्यथा
		mac &= ~FULLD;

	/* other parameters */
	mac |= (CRCE | PCRCE);
	mac |= ((adpt->preamble << PRLEN_SHFT) & PRLEN_BMSK);
	mac |= BROAD_EN;
	mac |= FLCHK;
	mac &= ~RX_CHKSUM_EN;
	mac &= ~(HUGEN | VLAN_STRIP | TPAUSE | SIMR | HUGE | MULTI_ALL |
		 DEBUG_MODE | SINGLE_PAUSE_MODE);

	/* Enable single-छोड़ो-frame mode अगर requested.
	 *
	 * If enabled, the EMAC will send a single छोड़ो frame when the RX
	 * queue is full.  This normally leads to packet loss because
	 * the छोड़ो frame disables the remote MAC only क्रम 33ms (the quanta),
	 * and then the remote MAC जारीs sending packets even though
	 * the RX queue is still full.
	 *
	 * If disabled, the EMAC sends a छोड़ो frame every 31ms until the RX
	 * queue is no दीर्घer full.  Normally, this is the preferred
	 * method of operation.  However, when the प्रणाली is hung (e.g.
	 * cores are halted), the EMAC पूर्णांकerrupt handler is never called
	 * and so the RX queue fills up quickly and stays full.  The resuling
	 * non-stop "flood" of छोड़ो frames someबार has the effect of
	 * disabling nearby चयनes.  In some हालs, other nearby चयनes
	 * are also affected, shutting करोwn the entire network.
	 *
	 * The user can enable or disable single-छोड़ो-frame mode
	 * via ethtool.
	 */
	mac |= adpt->single_छोड़ो_mode ? SINGLE_PAUSE_MODE : 0;

	ग_लिखोl_relaxed(csr1, adpt->csr + EMAC_EMAC_WRAPPER_CSR1);

	ग_लिखोl_relaxed(mac, adpt->base + EMAC_MAC_CTRL);

	/* enable पूर्णांकerrupt पढ़ो clear, low घातer sleep mode and
	 * the irq moderators
	 */

	ग_लिखोl_relaxed(adpt->irq_mod, adpt->base + EMAC_IRQ_MOD_TIM_INIT);
	ग_लिखोl_relaxed(INT_RD_CLR_EN | LPW_MODE | IRQ_MODERATOR_EN |
			IRQ_MODERATOR2_EN, adpt->base + EMAC_DMA_MAS_CTRL);

	emac_mac_mode_config(adpt);

	emac_reg_update32(adpt->base + EMAC_ATHR_HEADER_CTRL,
			  (HEADER_ENABLE | HEADER_CNT_EN), 0);
पूर्ण

व्योम emac_mac_stop(काष्ठा emac_adapter *adpt)
अणु
	emac_reg_update32(adpt->base + EMAC_RXQ_CTRL_0, RXQ_EN, 0);
	emac_reg_update32(adpt->base + EMAC_TXQ_CTRL_0, TXQ_EN, 0);
	emac_reg_update32(adpt->base + EMAC_MAC_CTRL, TXEN | RXEN, 0);
	usleep_range(1000, 1050); /* stopping mac may take upto 1msec */
पूर्ण

/* Free all descriptors of given transmit queue */
अटल व्योम emac_tx_q_descs_मुक्त(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_tx_queue *tx_q = &adpt->tx_q;
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!tx_q->tpd.tpbuff)
		वापस;

	क्रम (i = 0; i < tx_q->tpd.count; i++) अणु
		काष्ठा emac_buffer *tpbuf = GET_TPD_BUFFER(tx_q, i);

		अगर (tpbuf->dma_addr) अणु
			dma_unmap_single(adpt->netdev->dev.parent,
					 tpbuf->dma_addr, tpbuf->length,
					 DMA_TO_DEVICE);
			tpbuf->dma_addr = 0;
		पूर्ण
		अगर (tpbuf->skb) अणु
			dev_kमुक्त_skb_any(tpbuf->skb);
			tpbuf->skb = शून्य;
		पूर्ण
	पूर्ण

	size = माप(काष्ठा emac_buffer) * tx_q->tpd.count;
	स_रखो(tx_q->tpd.tpbuff, 0, size);

	/* clear the descriptor ring */
	स_रखो(tx_q->tpd.v_addr, 0, tx_q->tpd.size);

	tx_q->tpd.consume_idx = 0;
	tx_q->tpd.produce_idx = 0;
पूर्ण

/* Free all descriptors of given receive queue */
अटल व्योम emac_rx_q_मुक्त_descs(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा device *dev = adpt->netdev->dev.parent;
	काष्ठा emac_rx_queue *rx_q = &adpt->rx_q;
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!rx_q->rfd.rfbuff)
		वापस;

	क्रम (i = 0; i < rx_q->rfd.count; i++) अणु
		काष्ठा emac_buffer *rfbuf = GET_RFD_BUFFER(rx_q, i);

		अगर (rfbuf->dma_addr) अणु
			dma_unmap_single(dev, rfbuf->dma_addr, rfbuf->length,
					 DMA_FROM_DEVICE);
			rfbuf->dma_addr = 0;
		पूर्ण
		अगर (rfbuf->skb) अणु
			dev_kमुक्त_skb(rfbuf->skb);
			rfbuf->skb = शून्य;
		पूर्ण
	पूर्ण

	size =  माप(काष्ठा emac_buffer) * rx_q->rfd.count;
	स_रखो(rx_q->rfd.rfbuff, 0, size);

	/* clear the descriptor rings */
	स_रखो(rx_q->rrd.v_addr, 0, rx_q->rrd.size);
	rx_q->rrd.produce_idx = 0;
	rx_q->rrd.consume_idx = 0;

	स_रखो(rx_q->rfd.v_addr, 0, rx_q->rfd.size);
	rx_q->rfd.produce_idx = 0;
	rx_q->rfd.consume_idx = 0;
पूर्ण

/* Free all buffers associated with given transmit queue */
अटल व्योम emac_tx_q_bufs_मुक्त(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_tx_queue *tx_q = &adpt->tx_q;

	emac_tx_q_descs_मुक्त(adpt);

	kमुक्त(tx_q->tpd.tpbuff);
	tx_q->tpd.tpbuff = शून्य;
	tx_q->tpd.v_addr = शून्य;
	tx_q->tpd.dma_addr = 0;
	tx_q->tpd.size = 0;
पूर्ण

/* Allocate TX descriptor ring क्रम the given transmit queue */
अटल पूर्णांक emac_tx_q_desc_alloc(काष्ठा emac_adapter *adpt,
				काष्ठा emac_tx_queue *tx_q)
अणु
	काष्ठा emac_ring_header *ring_header = &adpt->ring_header;
	पूर्णांक node = dev_to_node(adpt->netdev->dev.parent);
	माप_प्रकार size;

	size = माप(काष्ठा emac_buffer) * tx_q->tpd.count;
	tx_q->tpd.tpbuff = kzalloc_node(size, GFP_KERNEL, node);
	अगर (!tx_q->tpd.tpbuff)
		वापस -ENOMEM;

	tx_q->tpd.size = tx_q->tpd.count * (adpt->tpd_size * 4);
	tx_q->tpd.dma_addr = ring_header->dma_addr + ring_header->used;
	tx_q->tpd.v_addr = ring_header->v_addr + ring_header->used;
	ring_header->used += ALIGN(tx_q->tpd.size, 8);
	tx_q->tpd.produce_idx = 0;
	tx_q->tpd.consume_idx = 0;

	वापस 0;
पूर्ण

/* Free all buffers associated with given transmit queue */
अटल व्योम emac_rx_q_bufs_मुक्त(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_rx_queue *rx_q = &adpt->rx_q;

	emac_rx_q_मुक्त_descs(adpt);

	kमुक्त(rx_q->rfd.rfbuff);
	rx_q->rfd.rfbuff   = शून्य;

	rx_q->rfd.v_addr   = शून्य;
	rx_q->rfd.dma_addr = 0;
	rx_q->rfd.size     = 0;

	rx_q->rrd.v_addr   = शून्य;
	rx_q->rrd.dma_addr = 0;
	rx_q->rrd.size     = 0;
पूर्ण

/* Allocate RX descriptor rings क्रम the given receive queue */
अटल पूर्णांक emac_rx_descs_alloc(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_ring_header *ring_header = &adpt->ring_header;
	पूर्णांक node = dev_to_node(adpt->netdev->dev.parent);
	काष्ठा emac_rx_queue *rx_q = &adpt->rx_q;
	माप_प्रकार size;

	size = माप(काष्ठा emac_buffer) * rx_q->rfd.count;
	rx_q->rfd.rfbuff = kzalloc_node(size, GFP_KERNEL, node);
	अगर (!rx_q->rfd.rfbuff)
		वापस -ENOMEM;

	rx_q->rrd.size = rx_q->rrd.count * (adpt->rrd_size * 4);
	rx_q->rfd.size = rx_q->rfd.count * (adpt->rfd_size * 4);

	rx_q->rrd.dma_addr = ring_header->dma_addr + ring_header->used;
	rx_q->rrd.v_addr   = ring_header->v_addr + ring_header->used;
	ring_header->used += ALIGN(rx_q->rrd.size, 8);

	rx_q->rfd.dma_addr = ring_header->dma_addr + ring_header->used;
	rx_q->rfd.v_addr   = ring_header->v_addr + ring_header->used;
	ring_header->used += ALIGN(rx_q->rfd.size, 8);

	rx_q->rrd.produce_idx = 0;
	rx_q->rrd.consume_idx = 0;

	rx_q->rfd.produce_idx = 0;
	rx_q->rfd.consume_idx = 0;

	वापस 0;
पूर्ण

/* Allocate all TX and RX descriptor rings */
पूर्णांक emac_mac_rx_tx_rings_alloc_all(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_ring_header *ring_header = &adpt->ring_header;
	काष्ठा device *dev = adpt->netdev->dev.parent;
	अचिन्हित पूर्णांक num_tx_descs = adpt->tx_desc_cnt;
	अचिन्हित पूर्णांक num_rx_descs = adpt->rx_desc_cnt;
	पूर्णांक ret;

	adpt->tx_q.tpd.count = adpt->tx_desc_cnt;

	adpt->rx_q.rrd.count = adpt->rx_desc_cnt;
	adpt->rx_q.rfd.count = adpt->rx_desc_cnt;

	/* Ring DMA buffer. Each ring may need up to 8 bytes क्रम alignment,
	 * hence the additional padding bytes are allocated.
	 */
	ring_header->size = num_tx_descs * (adpt->tpd_size * 4) +
			    num_rx_descs * (adpt->rfd_size * 4) +
			    num_rx_descs * (adpt->rrd_size * 4) +
			    8 + 2 * 8; /* 8 byte per one Tx and two Rx rings */

	ring_header->used = 0;
	ring_header->v_addr = dma_alloc_coherent(dev, ring_header->size,
						 &ring_header->dma_addr,
						 GFP_KERNEL);
	अगर (!ring_header->v_addr)
		वापस -ENOMEM;

	ring_header->used = ALIGN(ring_header->dma_addr, 8) -
							ring_header->dma_addr;

	ret = emac_tx_q_desc_alloc(adpt, &adpt->tx_q);
	अगर (ret) अणु
		netdev_err(adpt->netdev, "error: Tx Queue alloc failed\n");
		जाओ err_alloc_tx;
	पूर्ण

	ret = emac_rx_descs_alloc(adpt);
	अगर (ret) अणु
		netdev_err(adpt->netdev, "error: Rx Queue alloc failed\n");
		जाओ err_alloc_rx;
	पूर्ण

	वापस 0;

err_alloc_rx:
	emac_tx_q_bufs_मुक्त(adpt);
err_alloc_tx:
	dma_मुक्त_coherent(dev, ring_header->size,
			  ring_header->v_addr, ring_header->dma_addr);

	ring_header->v_addr   = शून्य;
	ring_header->dma_addr = 0;
	ring_header->size     = 0;
	ring_header->used     = 0;

	वापस ret;
पूर्ण

/* Free all TX and RX descriptor rings */
व्योम emac_mac_rx_tx_rings_मुक्त_all(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_ring_header *ring_header = &adpt->ring_header;
	काष्ठा device *dev = adpt->netdev->dev.parent;

	emac_tx_q_bufs_मुक्त(adpt);
	emac_rx_q_bufs_मुक्त(adpt);

	dma_मुक्त_coherent(dev, ring_header->size,
			  ring_header->v_addr, ring_header->dma_addr);

	ring_header->v_addr   = शून्य;
	ring_header->dma_addr = 0;
	ring_header->size     = 0;
	ring_header->used     = 0;
पूर्ण

/* Initialize descriptor rings */
अटल व्योम emac_mac_rx_tx_ring_reset_all(काष्ठा emac_adapter *adpt)
अणु
	अचिन्हित पूर्णांक i;

	adpt->tx_q.tpd.produce_idx = 0;
	adpt->tx_q.tpd.consume_idx = 0;
	क्रम (i = 0; i < adpt->tx_q.tpd.count; i++)
		adpt->tx_q.tpd.tpbuff[i].dma_addr = 0;

	adpt->rx_q.rrd.produce_idx = 0;
	adpt->rx_q.rrd.consume_idx = 0;
	adpt->rx_q.rfd.produce_idx = 0;
	adpt->rx_q.rfd.consume_idx = 0;
	क्रम (i = 0; i < adpt->rx_q.rfd.count; i++)
		adpt->rx_q.rfd.rfbuff[i].dma_addr = 0;
पूर्ण

/* Produce new receive मुक्त descriptor */
अटल व्योम emac_mac_rx_rfd_create(काष्ठा emac_adapter *adpt,
				   काष्ठा emac_rx_queue *rx_q,
				   dma_addr_t addr)
अणु
	u32 *hw_rfd = EMAC_RFD(rx_q, adpt->rfd_size, rx_q->rfd.produce_idx);

	*(hw_rfd++) = lower_32_bits(addr);
	*hw_rfd = upper_32_bits(addr);

	अगर (++rx_q->rfd.produce_idx == rx_q->rfd.count)
		rx_q->rfd.produce_idx = 0;
पूर्ण

/* Fill up receive queue's RFD with pपुनः_स्मृतिated receive buffers */
अटल व्योम emac_mac_rx_descs_refill(काष्ठा emac_adapter *adpt,
				    काष्ठा emac_rx_queue *rx_q)
अणु
	काष्ठा emac_buffer *curr_rxbuf;
	काष्ठा emac_buffer *next_rxbuf;
	अचिन्हित पूर्णांक count = 0;
	u32 next_produce_idx;

	next_produce_idx = rx_q->rfd.produce_idx + 1;
	अगर (next_produce_idx == rx_q->rfd.count)
		next_produce_idx = 0;

	curr_rxbuf = GET_RFD_BUFFER(rx_q, rx_q->rfd.produce_idx);
	next_rxbuf = GET_RFD_BUFFER(rx_q, next_produce_idx);

	/* this always has a blank rx_buffer*/
	जबतक (!next_rxbuf->dma_addr) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक ret;

		skb = netdev_alloc_skb_ip_align(adpt->netdev, adpt->rxbuf_size);
		अगर (!skb)
			अवरोध;

		curr_rxbuf->dma_addr =
			dma_map_single(adpt->netdev->dev.parent, skb->data,
				       adpt->rxbuf_size, DMA_FROM_DEVICE);

		ret = dma_mapping_error(adpt->netdev->dev.parent,
					curr_rxbuf->dma_addr);
		अगर (ret) अणु
			dev_kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
		curr_rxbuf->skb = skb;
		curr_rxbuf->length = adpt->rxbuf_size;

		emac_mac_rx_rfd_create(adpt, rx_q, curr_rxbuf->dma_addr);
		next_produce_idx = rx_q->rfd.produce_idx + 1;
		अगर (next_produce_idx == rx_q->rfd.count)
			next_produce_idx = 0;

		curr_rxbuf = GET_RFD_BUFFER(rx_q, rx_q->rfd.produce_idx);
		next_rxbuf = GET_RFD_BUFFER(rx_q, next_produce_idx);
		count++;
	पूर्ण

	अगर (count) अणु
		u32 prod_idx = (rx_q->rfd.produce_idx << rx_q->produce_shअगरt) &
				rx_q->produce_mask;
		emac_reg_update32(adpt->base + rx_q->produce_reg,
				  rx_q->produce_mask, prod_idx);
	पूर्ण
पूर्ण

अटल व्योम emac_adjust_link(काष्ठा net_device *netdev)
अणु
	काष्ठा emac_adapter *adpt = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;

	अगर (phydev->link) अणु
		emac_mac_start(adpt);
		emac_sgmii_link_change(adpt, true);
	पूर्ण अन्यथा अणु
		emac_sgmii_link_change(adpt, false);
		emac_mac_stop(adpt);
	पूर्ण

	phy_prपूर्णांक_status(phydev);
पूर्ण

/* Bringup the पूर्णांकerface/HW */
पूर्णांक emac_mac_up(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा net_device *netdev = adpt->netdev;
	पूर्णांक ret;

	emac_mac_rx_tx_ring_reset_all(adpt);
	emac_mac_config(adpt);
	emac_mac_rx_descs_refill(adpt, &adpt->rx_q);

	adpt->phydev->irq = PHY_POLL;
	ret = phy_connect_direct(netdev, adpt->phydev, emac_adjust_link,
				 PHY_INTERFACE_MODE_SGMII);
	अगर (ret) अणु
		netdev_err(adpt->netdev, "could not connect phy\n");
		वापस ret;
	पूर्ण

	phy_attached_prपूर्णांक(adpt->phydev, शून्य);

	/* enable mac irq */
	ग_लिखोl((u32)~DIS_INT, adpt->base + EMAC_INT_STATUS);
	ग_लिखोl(adpt->irq.mask, adpt->base + EMAC_INT_MASK);

	phy_start(adpt->phydev);

	napi_enable(&adpt->rx_q.napi);
	netअगर_start_queue(netdev);

	वापस 0;
पूर्ण

/* Bring करोwn the पूर्णांकerface/HW */
व्योम emac_mac_करोwn(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा net_device *netdev = adpt->netdev;

	netअगर_stop_queue(netdev);
	napi_disable(&adpt->rx_q.napi);

	phy_stop(adpt->phydev);

	/* Interrupts must be disabled beक्रमe the PHY is disconnected, to
	 * aव्योम a race condition where adjust_link is null when we get
	 * an पूर्णांकerrupt.
	 */
	ग_लिखोl(DIS_INT, adpt->base + EMAC_INT_STATUS);
	ग_लिखोl(0, adpt->base + EMAC_INT_MASK);
	synchronize_irq(adpt->irq.irq);

	phy_disconnect(adpt->phydev);

	emac_mac_reset(adpt);

	emac_tx_q_descs_मुक्त(adpt);
	netdev_reset_queue(adpt->netdev);
	emac_rx_q_मुक्त_descs(adpt);
पूर्ण

/* Consume next received packet descriptor */
अटल bool emac_rx_process_rrd(काष्ठा emac_adapter *adpt,
				काष्ठा emac_rx_queue *rx_q,
				काष्ठा emac_rrd *rrd)
अणु
	u32 *hw_rrd = EMAC_RRD(rx_q, adpt->rrd_size, rx_q->rrd.consume_idx);

	rrd->word[3] = *(hw_rrd + 3);

	अगर (!RRD_UPDT(rrd))
		वापस false;

	rrd->word[4] = 0;
	rrd->word[5] = 0;

	rrd->word[0] = *(hw_rrd++);
	rrd->word[1] = *(hw_rrd++);
	rrd->word[2] = *(hw_rrd++);

	अगर (unlikely(RRD_NOR(rrd) != 1)) अणु
		netdev_err(adpt->netdev,
			   "error: multi-RFD not support yet! nor:%lu\n",
			   RRD_NOR(rrd));
	पूर्ण

	/* mark rrd as processed */
	RRD_UPDT_SET(rrd, 0);
	*hw_rrd = rrd->word[3];

	अगर (++rx_q->rrd.consume_idx == rx_q->rrd.count)
		rx_q->rrd.consume_idx = 0;

	वापस true;
पूर्ण

/* Produce new transmit descriptor */
अटल व्योम emac_tx_tpd_create(काष्ठा emac_adapter *adpt,
			       काष्ठा emac_tx_queue *tx_q, काष्ठा emac_tpd *tpd)
अणु
	u32 *hw_tpd;

	tx_q->tpd.last_produce_idx = tx_q->tpd.produce_idx;
	hw_tpd = EMAC_TPD(tx_q, adpt->tpd_size, tx_q->tpd.produce_idx);

	अगर (++tx_q->tpd.produce_idx == tx_q->tpd.count)
		tx_q->tpd.produce_idx = 0;

	*(hw_tpd++) = tpd->word[0];
	*(hw_tpd++) = tpd->word[1];
	*(hw_tpd++) = tpd->word[2];
	*hw_tpd = tpd->word[3];
पूर्ण

/* Mark the last transmit descriptor as such (क्रम the transmit packet) */
अटल व्योम emac_tx_tpd_mark_last(काष्ठा emac_adapter *adpt,
				  काष्ठा emac_tx_queue *tx_q)
अणु
	u32 *hw_tpd =
		EMAC_TPD(tx_q, adpt->tpd_size, tx_q->tpd.last_produce_idx);
	u32 पंचांगp_tpd;

	पंचांगp_tpd = *(hw_tpd + 1);
	पंचांगp_tpd |= EMAC_TPD_LAST_FRAGMENT;
	*(hw_tpd + 1) = पंचांगp_tpd;
पूर्ण

अटल व्योम emac_rx_rfd_clean(काष्ठा emac_rx_queue *rx_q, काष्ठा emac_rrd *rrd)
अणु
	काष्ठा emac_buffer *rfbuf = rx_q->rfd.rfbuff;
	u32 consume_idx = RRD_SI(rrd);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < RRD_NOR(rrd); i++) अणु
		rfbuf[consume_idx].skb = शून्य;
		अगर (++consume_idx == rx_q->rfd.count)
			consume_idx = 0;
	पूर्ण

	rx_q->rfd.consume_idx = consume_idx;
	rx_q->rfd.process_idx = consume_idx;
पूर्ण

/* Push the received skb to upper layers */
अटल व्योम emac_receive_skb(काष्ठा emac_rx_queue *rx_q,
			     काष्ठा sk_buff *skb,
			     u16 vlan_tag, bool vlan_flag)
अणु
	अगर (vlan_flag) अणु
		u16 vlan;

		EMAC_TAG_TO_VLAN(vlan_tag, vlan);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan);
	पूर्ण

	napi_gro_receive(&rx_q->napi, skb);
पूर्ण

/* Process receive event */
व्योम emac_mac_rx_process(काष्ठा emac_adapter *adpt, काष्ठा emac_rx_queue *rx_q,
			 पूर्णांक *num_pkts, पूर्णांक max_pkts)
अणु
	u32 proc_idx, hw_consume_idx, num_consume_pkts;
	काष्ठा net_device *netdev  = adpt->netdev;
	काष्ठा emac_buffer *rfbuf;
	अचिन्हित पूर्णांक count = 0;
	काष्ठा emac_rrd rrd;
	काष्ठा sk_buff *skb;
	u32 reg;

	reg = पढ़ोl_relaxed(adpt->base + rx_q->consume_reg);

	hw_consume_idx = (reg & rx_q->consume_mask) >> rx_q->consume_shअगरt;
	num_consume_pkts = (hw_consume_idx >= rx_q->rrd.consume_idx) ?
		(hw_consume_idx -  rx_q->rrd.consume_idx) :
		(hw_consume_idx + rx_q->rrd.count - rx_q->rrd.consume_idx);

	करो अणु
		अगर (!num_consume_pkts)
			अवरोध;

		अगर (!emac_rx_process_rrd(adpt, rx_q, &rrd))
			अवरोध;

		अगर (likely(RRD_NOR(&rrd) == 1)) अणु
			/* good receive */
			rfbuf = GET_RFD_BUFFER(rx_q, RRD_SI(&rrd));
			dma_unmap_single(adpt->netdev->dev.parent,
					 rfbuf->dma_addr, rfbuf->length,
					 DMA_FROM_DEVICE);
			rfbuf->dma_addr = 0;
			skb = rfbuf->skb;
		पूर्ण अन्यथा अणु
			netdev_err(adpt->netdev,
				   "error: multi-RFD not support yet!\n");
			अवरोध;
		पूर्ण
		emac_rx_rfd_clean(rx_q, &rrd);
		num_consume_pkts--;
		count++;

		/* Due to a HW issue in L4 check sum detection (UDP/TCP frags
		 * with DF set are marked as error), drop packets based on the
		 * error mask rather than the summary bit (ignoring L4F errors)
		 */
		अगर (rrd.word[EMAC_RRD_STATS_DW_IDX] & EMAC_RRD_ERROR) अणु
			netअगर_dbg(adpt, rx_status, adpt->netdev,
				  "Drop error packet[RRD: 0x%x:0x%x:0x%x:0x%x]\n",
				  rrd.word[0], rrd.word[1],
				  rrd.word[2], rrd.word[3]);

			dev_kमुक्त_skb(skb);
			जारी;
		पूर्ण

		skb_put(skb, RRD_PKT_SIZE(&rrd) - ETH_FCS_LEN);
		skb->dev = netdev;
		skb->protocol = eth_type_trans(skb, skb->dev);
		अगर (netdev->features & NETIF_F_RXCSUM)
			skb->ip_summed = RRD_L4F(&rrd) ?
					  CHECKSUM_NONE : CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);

		emac_receive_skb(rx_q, skb, (u16)RRD_CVALN_TAG(&rrd),
				 (bool)RRD_CVTAG(&rrd));

		(*num_pkts)++;
	पूर्ण जबतक (*num_pkts < max_pkts);

	अगर (count) अणु
		proc_idx = (rx_q->rfd.process_idx << rx_q->process_shft) &
				rx_q->process_mask;
		emac_reg_update32(adpt->base + rx_q->process_reg,
				  rx_q->process_mask, proc_idx);
		emac_mac_rx_descs_refill(adpt, rx_q);
	पूर्ण
पूर्ण

/* get the number of मुक्त transmit descriptors */
अटल अचिन्हित पूर्णांक emac_tpd_num_मुक्त_descs(काष्ठा emac_tx_queue *tx_q)
अणु
	u32 produce_idx = tx_q->tpd.produce_idx;
	u32 consume_idx = tx_q->tpd.consume_idx;

	वापस (consume_idx > produce_idx) ?
		(consume_idx - produce_idx - 1) :
		(tx_q->tpd.count + consume_idx - produce_idx - 1);
पूर्ण

/* Process transmit event */
व्योम emac_mac_tx_process(काष्ठा emac_adapter *adpt, काष्ठा emac_tx_queue *tx_q)
अणु
	u32 reg = पढ़ोl_relaxed(adpt->base + tx_q->consume_reg);
	u32 hw_consume_idx, pkts_compl = 0, bytes_compl = 0;
	काष्ठा emac_buffer *tpbuf;

	hw_consume_idx = (reg & tx_q->consume_mask) >> tx_q->consume_shअगरt;

	जबतक (tx_q->tpd.consume_idx != hw_consume_idx) अणु
		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.consume_idx);
		अगर (tpbuf->dma_addr) अणु
			dma_unmap_page(adpt->netdev->dev.parent,
				       tpbuf->dma_addr, tpbuf->length,
				       DMA_TO_DEVICE);
			tpbuf->dma_addr = 0;
		पूर्ण

		अगर (tpbuf->skb) अणु
			pkts_compl++;
			bytes_compl += tpbuf->skb->len;
			dev_consume_skb_irq(tpbuf->skb);
			tpbuf->skb = शून्य;
		पूर्ण

		अगर (++tx_q->tpd.consume_idx == tx_q->tpd.count)
			tx_q->tpd.consume_idx = 0;
	पूर्ण

	netdev_completed_queue(adpt->netdev, pkts_compl, bytes_compl);

	अगर (netअगर_queue_stopped(adpt->netdev))
		अगर (emac_tpd_num_मुक्त_descs(tx_q) > (MAX_SKB_FRAGS + 1))
			netअगर_wake_queue(adpt->netdev);
पूर्ण

/* Initialize all queue data काष्ठाures */
व्योम emac_mac_rx_tx_ring_init_all(काष्ठा platक्रमm_device *pdev,
				  काष्ठा emac_adapter *adpt)
अणु
	adpt->rx_q.netdev = adpt->netdev;

	adpt->rx_q.produce_reg  = EMAC_MAILBOX_0;
	adpt->rx_q.produce_mask = RFD0_PROD_IDX_BMSK;
	adpt->rx_q.produce_shअगरt = RFD0_PROD_IDX_SHFT;

	adpt->rx_q.process_reg  = EMAC_MAILBOX_0;
	adpt->rx_q.process_mask = RFD0_PROC_IDX_BMSK;
	adpt->rx_q.process_shft = RFD0_PROC_IDX_SHFT;

	adpt->rx_q.consume_reg  = EMAC_MAILBOX_3;
	adpt->rx_q.consume_mask = RFD0_CONS_IDX_BMSK;
	adpt->rx_q.consume_shअगरt = RFD0_CONS_IDX_SHFT;

	adpt->rx_q.irq          = &adpt->irq;
	adpt->rx_q.पूर्णांकr         = adpt->irq.mask & ISR_RX_PKT;

	adpt->tx_q.produce_reg  = EMAC_MAILBOX_15;
	adpt->tx_q.produce_mask = NTPD_PROD_IDX_BMSK;
	adpt->tx_q.produce_shअगरt = NTPD_PROD_IDX_SHFT;

	adpt->tx_q.consume_reg  = EMAC_MAILBOX_2;
	adpt->tx_q.consume_mask = NTPD_CONS_IDX_BMSK;
	adpt->tx_q.consume_shअगरt = NTPD_CONS_IDX_SHFT;
पूर्ण

/* Fill up transmit descriptors with TSO and Checksum offload inक्रमmation */
अटल पूर्णांक emac_tso_csum(काष्ठा emac_adapter *adpt,
			 काष्ठा emac_tx_queue *tx_q,
			 काष्ठा sk_buff *skb,
			 काष्ठा emac_tpd *tpd)
अणु
	अचिन्हित पूर्णांक hdr_len;
	पूर्णांक ret;

	अगर (skb_is_gso(skb)) अणु
		अगर (skb_header_cloned(skb)) अणु
			ret = pskb_expand_head(skb, 0, 0, GFP_ATOMIC);
			अगर (unlikely(ret))
				वापस ret;
		पूर्ण

		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			u32 pkt_len = ((अचिन्हित अक्षर *)ip_hdr(skb) - skb->data)
				       + ntohs(ip_hdr(skb)->tot_len);
			अगर (skb->len > pkt_len)
				pskb_trim(skb, pkt_len);
		पूर्ण

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		अगर (unlikely(skb->len == hdr_len)) अणु
			/* we only need to करो csum */
			netअगर_warn(adpt, tx_err, adpt->netdev,
				   "tso not needed for packet with 0 data\n");
			जाओ करो_csum;
		पूर्ण

		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4) अणु
			ip_hdr(skb)->check = 0;
			tcp_hdr(skb)->check =
				~csum_tcpudp_magic(ip_hdr(skb)->saddr,
						   ip_hdr(skb)->daddr,
						   0, IPPROTO_TCP, 0);
			TPD_IPV4_SET(tpd, 1);
		पूर्ण

		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6) अणु
			/* ipv6 tso need an extra tpd */
			काष्ठा emac_tpd extra_tpd;

			स_रखो(tpd, 0, माप(*tpd));
			स_रखो(&extra_tpd, 0, माप(extra_tpd));

			tcp_v6_gso_csum_prep(skb);

			TPD_PKT_LEN_SET(&extra_tpd, skb->len);
			TPD_LSO_SET(&extra_tpd, 1);
			TPD_LSOV_SET(&extra_tpd, 1);
			emac_tx_tpd_create(adpt, tx_q, &extra_tpd);
			TPD_LSOV_SET(tpd, 1);
		पूर्ण

		TPD_LSO_SET(tpd, 1);
		TPD_TCPHDR_OFFSET_SET(tpd, skb_transport_offset(skb));
		TPD_MSS_SET(tpd, skb_shinfo(skb)->gso_size);
		वापस 0;
	पूर्ण

करो_csum:
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		अचिन्हित पूर्णांक css, cso;

		cso = skb_transport_offset(skb);
		अगर (unlikely(cso & 0x1)) अणु
			netdev_err(adpt->netdev,
				   "error: payload offset should be even\n");
			वापस -EINVAL;
		पूर्ण
		css = cso + skb->csum_offset;

		TPD_PAYLOAD_OFFSET_SET(tpd, cso >> 1);
		TPD_CXSUM_OFFSET_SET(tpd, css >> 1);
		TPD_CSX_SET(tpd, 1);
	पूर्ण

	वापस 0;
पूर्ण

/* Fill up transmit descriptors */
अटल व्योम emac_tx_fill_tpd(काष्ठा emac_adapter *adpt,
			     काष्ठा emac_tx_queue *tx_q, काष्ठा sk_buff *skb,
			     काष्ठा emac_tpd *tpd)
अणु
	अचिन्हित पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	अचिन्हित पूर्णांक first = tx_q->tpd.produce_idx;
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	काष्ठा emac_buffer *tpbuf = शून्य;
	अचिन्हित पूर्णांक mapped_len = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक count = 0;
	पूर्णांक ret;

	/* अगर Large Segment Offload is (in TCP Segmentation Offload काष्ठा) */
	अगर (TPD_LSO(tpd)) अणु
		mapped_len = skb_transport_offset(skb) + tcp_hdrlen(skb);

		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.produce_idx);
		tpbuf->length = mapped_len;
		tpbuf->dma_addr = dma_map_page(adpt->netdev->dev.parent,
					       virt_to_page(skb->data),
					       offset_in_page(skb->data),
					       tpbuf->length,
					       DMA_TO_DEVICE);
		ret = dma_mapping_error(adpt->netdev->dev.parent,
					tpbuf->dma_addr);
		अगर (ret)
			जाओ error;

		TPD_BUFFER_ADDR_L_SET(tpd, lower_32_bits(tpbuf->dma_addr));
		TPD_BUFFER_ADDR_H_SET(tpd, upper_32_bits(tpbuf->dma_addr));
		TPD_BUF_LEN_SET(tpd, tpbuf->length);
		emac_tx_tpd_create(adpt, tx_q, tpd);
		count++;
	पूर्ण

	अगर (mapped_len < len) अणु
		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.produce_idx);
		tpbuf->length = len - mapped_len;
		tpbuf->dma_addr = dma_map_page(adpt->netdev->dev.parent,
					       virt_to_page(skb->data +
							    mapped_len),
					       offset_in_page(skb->data +
							      mapped_len),
					       tpbuf->length, DMA_TO_DEVICE);
		ret = dma_mapping_error(adpt->netdev->dev.parent,
					tpbuf->dma_addr);
		अगर (ret)
			जाओ error;

		TPD_BUFFER_ADDR_L_SET(tpd, lower_32_bits(tpbuf->dma_addr));
		TPD_BUFFER_ADDR_H_SET(tpd, upper_32_bits(tpbuf->dma_addr));
		TPD_BUF_LEN_SET(tpd, tpbuf->length);
		emac_tx_tpd_create(adpt, tx_q, tpd);
		count++;
	पूर्ण

	क्रम (i = 0; i < nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.produce_idx);
		tpbuf->length = skb_frag_size(frag);
		tpbuf->dma_addr = skb_frag_dma_map(adpt->netdev->dev.parent,
						   frag, 0, tpbuf->length,
						   DMA_TO_DEVICE);
		ret = dma_mapping_error(adpt->netdev->dev.parent,
					tpbuf->dma_addr);
		अगर (ret)
			जाओ error;

		TPD_BUFFER_ADDR_L_SET(tpd, lower_32_bits(tpbuf->dma_addr));
		TPD_BUFFER_ADDR_H_SET(tpd, upper_32_bits(tpbuf->dma_addr));
		TPD_BUF_LEN_SET(tpd, tpbuf->length);
		emac_tx_tpd_create(adpt, tx_q, tpd);
		count++;
	पूर्ण

	/* The last tpd */
	wmb();
	emac_tx_tpd_mark_last(adpt, tx_q);

	/* The last buffer info contain the skb address,
	 * so it will be मुक्तd after unmap
	 */
	tpbuf->skb = skb;

	वापस;

error:
	/* One of the memory mappings failed, so unकरो everything */
	tx_q->tpd.produce_idx = first;

	जबतक (count--) अणु
		tpbuf = GET_TPD_BUFFER(tx_q, first);
		dma_unmap_page(adpt->netdev->dev.parent, tpbuf->dma_addr,
			       tpbuf->length, DMA_TO_DEVICE);
		tpbuf->dma_addr = 0;
		tpbuf->length = 0;

		अगर (++first == tx_q->tpd.count)
			first = 0;
	पूर्ण

	dev_kमुक्त_skb(skb);
पूर्ण

/* Transmit the packet using specअगरied transmit queue */
netdev_tx_t emac_mac_tx_buf_send(काष्ठा emac_adapter *adpt,
				 काष्ठा emac_tx_queue *tx_q,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा emac_tpd tpd;
	u32 prod_idx;
	पूर्णांक len;

	स_रखो(&tpd, 0, माप(tpd));

	अगर (emac_tso_csum(adpt, tx_q, skb, &tpd) != 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		u16 tag;

		EMAC_VLAN_TO_TAG(skb_vlan_tag_get(skb), tag);
		TPD_CVLAN_TAG_SET(&tpd, tag);
		TPD_INSTC_SET(&tpd, 1);
	पूर्ण

	अगर (skb_network_offset(skb) != ETH_HLEN)
		TPD_TYP_SET(&tpd, 1);

	len = skb->len;
	emac_tx_fill_tpd(adpt, tx_q, skb, &tpd);

	netdev_sent_queue(adpt->netdev, len);

	/* Make sure the are enough मुक्त descriptors to hold one
	 * maximum-sized SKB.  We need one desc क्रम each fragment,
	 * one क्रम the checksum (emac_tso_csum), one क्रम TSO, and
	 * and one क्रम the SKB header.
	 */
	अगर (emac_tpd_num_मुक्त_descs(tx_q) < (MAX_SKB_FRAGS + 3))
		netअगर_stop_queue(adpt->netdev);

	/* update produce idx */
	prod_idx = (tx_q->tpd.produce_idx << tx_q->produce_shअगरt) &
		    tx_q->produce_mask;
	emac_reg_update32(adpt->base + tx_q->produce_reg,
			  tx_q->produce_mask, prod_idx);

	वापस NETDEV_TX_OK;
पूर्ण
