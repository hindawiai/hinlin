<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Marvell Discovery (MV643XX) and Marvell Orion ethernet ports
 * Copyright (C) 2002 Matthew Dharm <mdharm@momenco.com>
 *
 * Based on the 64360 driver from:
 * Copyright (C) 2002 Rabeeh Khoury <rabeeh@galileo.co.il>
 *		      Rabeeh Khoury <rabeeh@marvell.com>
 *
 * Copyright (C) 2003 PMC-Sierra, Inc.,
 *	written by Manish Lachwani
 *
 * Copyright (C) 2003 Ralf Baechle <ralf@linux-mips.org>
 *
 * Copyright (C) 2004-2006 MontaVista Software, Inc.
 *			   Dale Farnsworth <dale@farnsworth.org>
 *
 * Copyright (C) 2004 Steven J. Hill <sjhill1@rockwellcollins.com>
 *				     <sjhill@realitydiluted.com>
 *
 * Copyright (C) 2007-2008 Marvell Semiconductor
 *			   Lennert Buytenhek <buytenh@marvell.com>
 *
 * Copyright (C) 2013 Michael Stapelberg <michael@stapelberg.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <net/tso.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/phy.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>

अटल अक्षर mv643xx_eth_driver_name[] = "mv643xx_eth";
अटल अक्षर mv643xx_eth_driver_version[] = "1.4";


/*
 * Registers shared between all ports.
 */
#घोषणा PHY_ADDR			0x0000
#घोषणा WINDOW_BASE(w)			(0x0200 + ((w) << 3))
#घोषणा WINDOW_SIZE(w)			(0x0204 + ((w) << 3))
#घोषणा WINDOW_REMAP_HIGH(w)		(0x0280 + ((w) << 2))
#घोषणा WINDOW_BAR_ENABLE		0x0290
#घोषणा WINDOW_PROTECT(w)		(0x0294 + ((w) << 4))

/*
 * Main per-port रेजिस्टरs.  These live at offset 0x0400 क्रम
 * port #0, 0x0800 क्रम port #1, and 0x0c00 क्रम port #2.
 */
#घोषणा PORT_CONFIG			0x0000
#घोषणा  UNICAST_PROMISCUOUS_MODE	0x00000001
#घोषणा PORT_CONFIG_EXT			0x0004
#घोषणा MAC_ADDR_LOW			0x0014
#घोषणा MAC_ADDR_HIGH			0x0018
#घोषणा SDMA_CONFIG			0x001c
#घोषणा  TX_BURST_SIZE_16_64BIT		0x01000000
#घोषणा  TX_BURST_SIZE_4_64BIT		0x00800000
#घोषणा  BLM_TX_NO_SWAP			0x00000020
#घोषणा  BLM_RX_NO_SWAP			0x00000010
#घोषणा  RX_BURST_SIZE_16_64BIT		0x00000008
#घोषणा  RX_BURST_SIZE_4_64BIT		0x00000004
#घोषणा PORT_SERIAL_CONTROL		0x003c
#घोषणा  SET_MII_SPEED_TO_100		0x01000000
#घोषणा  SET_GMII_SPEED_TO_1000		0x00800000
#घोषणा  SET_FULL_DUPLEX_MODE		0x00200000
#घोषणा  MAX_RX_PACKET_9700BYTE		0x000a0000
#घोषणा  DISABLE_AUTO_NEG_SPEED_GMII	0x00002000
#घोषणा  DO_NOT_FORCE_LINK_FAIL		0x00000400
#घोषणा  SERIAL_PORT_CONTROL_RESERVED	0x00000200
#घोषणा  DISABLE_AUTO_NEG_FOR_FLOW_CTRL	0x00000008
#घोषणा  DISABLE_AUTO_NEG_FOR_DUPLEX	0x00000004
#घोषणा  FORCE_LINK_PASS		0x00000002
#घोषणा  SERIAL_PORT_ENABLE		0x00000001
#घोषणा PORT_STATUS			0x0044
#घोषणा  TX_FIFO_EMPTY			0x00000400
#घोषणा  TX_IN_PROGRESS			0x00000080
#घोषणा  PORT_SPEED_MASK		0x00000030
#घोषणा  PORT_SPEED_1000		0x00000010
#घोषणा  PORT_SPEED_100			0x00000020
#घोषणा  PORT_SPEED_10			0x00000000
#घोषणा  FLOW_CONTROL_ENABLED		0x00000008
#घोषणा  FULL_DUPLEX			0x00000004
#घोषणा  LINK_UP			0x00000002
#घोषणा TXQ_COMMAND			0x0048
#घोषणा TXQ_FIX_PRIO_CONF		0x004c
#घोषणा PORT_SERIAL_CONTROL1		0x004c
#घोषणा  CLK125_BYPASS_EN		0x00000010
#घोषणा TX_BW_RATE			0x0050
#घोषणा TX_BW_MTU			0x0058
#घोषणा TX_BW_BURST			0x005c
#घोषणा INT_CAUSE			0x0060
#घोषणा  INT_TX_END			0x07f80000
#घोषणा  INT_TX_END_0			0x00080000
#घोषणा  INT_RX				0x000003fc
#घोषणा  INT_RX_0			0x00000004
#घोषणा  INT_EXT			0x00000002
#घोषणा INT_CAUSE_EXT			0x0064
#घोषणा  INT_EXT_LINK_PHY		0x00110000
#घोषणा  INT_EXT_TX			0x000000ff
#घोषणा INT_MASK			0x0068
#घोषणा INT_MASK_EXT			0x006c
#घोषणा TX_FIFO_URGENT_THRESHOLD	0x0074
#घोषणा RX_DISCARD_FRAME_CNT		0x0084
#घोषणा RX_OVERRUN_FRAME_CNT		0x0088
#घोषणा TXQ_FIX_PRIO_CONF_MOVED		0x00dc
#घोषणा TX_BW_RATE_MOVED		0x00e0
#घोषणा TX_BW_MTU_MOVED			0x00e8
#घोषणा TX_BW_BURST_MOVED		0x00ec
#घोषणा RXQ_CURRENT_DESC_PTR(q)		(0x020c + ((q) << 4))
#घोषणा RXQ_COMMAND			0x0280
#घोषणा TXQ_CURRENT_DESC_PTR(q)		(0x02c0 + ((q) << 2))
#घोषणा TXQ_BW_TOKENS(q)		(0x0300 + ((q) << 4))
#घोषणा TXQ_BW_CONF(q)			(0x0304 + ((q) << 4))
#घोषणा TXQ_BW_WRR_CONF(q)		(0x0308 + ((q) << 4))

/*
 * Misc per-port रेजिस्टरs.
 */
#घोषणा MIB_COUNTERS(p)			(0x1000 + ((p) << 7))
#घोषणा SPECIAL_MCAST_TABLE(p)		(0x1400 + ((p) << 10))
#घोषणा OTHER_MCAST_TABLE(p)		(0x1500 + ((p) << 10))
#घोषणा UNICAST_TABLE(p)		(0x1600 + ((p) << 10))


/*
 * SDMA configuration रेजिस्टर शेष value.
 */
#अगर defined(__BIG_ENDIAN)
#घोषणा PORT_SDMA_CONFIG_DEFAULT_VALUE		\
		(RX_BURST_SIZE_4_64BIT	|	\
		 TX_BURST_SIZE_4_64BIT)
#या_अगर defined(__LITTLE_ENDIAN)
#घोषणा PORT_SDMA_CONFIG_DEFAULT_VALUE		\
		(RX_BURST_SIZE_4_64BIT	|	\
		 BLM_RX_NO_SWAP		|	\
		 BLM_TX_NO_SWAP		|	\
		 TX_BURST_SIZE_4_64BIT)
#अन्यथा
#त्रुटि One of __BIG_ENDIAN or __LITTLE_ENDIAN must be defined
#पूर्ण_अगर


/*
 * Misc definitions.
 */
#घोषणा DEFAULT_RX_QUEUE_SIZE	128
#घोषणा DEFAULT_TX_QUEUE_SIZE	512
#घोषणा SKB_DMA_REALIGN		((PAGE_SIZE - NET_SKB_PAD) % SMP_CACHE_BYTES)

/* Max number of allowed TCP segments क्रम software TSO */
#घोषणा MV643XX_MAX_TSO_SEGS 100
#घोषणा MV643XX_MAX_SKB_DESCS (MV643XX_MAX_TSO_SEGS * 2 + MAX_SKB_FRAGS)

#घोषणा IS_TSO_HEADER(txq, addr) \
	((addr >= txq->tso_hdrs_dma) && \
	 (addr < txq->tso_hdrs_dma + txq->tx_ring_size * TSO_HEADER_SIZE))

#घोषणा DESC_DMA_MAP_SINGLE 0
#घोषणा DESC_DMA_MAP_PAGE 1

/*
 * RX/TX descriptors.
 */
#अगर defined(__BIG_ENDIAN)
काष्ठा rx_desc अणु
	u16 byte_cnt;		/* Descriptor buffer byte count		*/
	u16 buf_size;		/* Buffer size				*/
	u32 cmd_sts;		/* Descriptor command status		*/
	u32 next_desc_ptr;	/* Next descriptor poपूर्णांकer		*/
	u32 buf_ptr;		/* Descriptor buffer poपूर्णांकer		*/
पूर्ण;

काष्ठा tx_desc अणु
	u16 byte_cnt;		/* buffer byte count			*/
	u16 l4i_chk;		/* CPU provided TCP checksum		*/
	u32 cmd_sts;		/* Command/status field			*/
	u32 next_desc_ptr;	/* Poपूर्णांकer to next descriptor		*/
	u32 buf_ptr;		/* poपूर्णांकer to buffer क्रम this descriptor*/
पूर्ण;
#या_अगर defined(__LITTLE_ENDIAN)
काष्ठा rx_desc अणु
	u32 cmd_sts;		/* Descriptor command status		*/
	u16 buf_size;		/* Buffer size				*/
	u16 byte_cnt;		/* Descriptor buffer byte count		*/
	u32 buf_ptr;		/* Descriptor buffer poपूर्णांकer		*/
	u32 next_desc_ptr;	/* Next descriptor poपूर्णांकer		*/
पूर्ण;

काष्ठा tx_desc अणु
	u32 cmd_sts;		/* Command/status field			*/
	u16 l4i_chk;		/* CPU provided TCP checksum		*/
	u16 byte_cnt;		/* buffer byte count			*/
	u32 buf_ptr;		/* poपूर्णांकer to buffer क्रम this descriptor*/
	u32 next_desc_ptr;	/* Poपूर्णांकer to next descriptor		*/
पूर्ण;
#अन्यथा
#त्रुटि One of __BIG_ENDIAN or __LITTLE_ENDIAN must be defined
#पूर्ण_अगर

/* RX & TX descriptor command */
#घोषणा BUFFER_OWNED_BY_DMA		0x80000000

/* RX & TX descriptor status */
#घोषणा ERROR_SUMMARY			0x00000001

/* RX descriptor status */
#घोषणा LAYER_4_CHECKSUM_OK		0x40000000
#घोषणा RX_ENABLE_INTERRUPT		0x20000000
#घोषणा RX_FIRST_DESC			0x08000000
#घोषणा RX_LAST_DESC			0x04000000
#घोषणा RX_IP_HDR_OK			0x02000000
#घोषणा RX_PKT_IS_IPV4			0x01000000
#घोषणा RX_PKT_IS_ETHERNETV2		0x00800000
#घोषणा RX_PKT_LAYER4_TYPE_MASK		0x00600000
#घोषणा RX_PKT_LAYER4_TYPE_TCP_IPV4	0x00000000
#घोषणा RX_PKT_IS_VLAN_TAGGED		0x00080000

/* TX descriptor command */
#घोषणा TX_ENABLE_INTERRUPT		0x00800000
#घोषणा GEN_CRC				0x00400000
#घोषणा TX_FIRST_DESC			0x00200000
#घोषणा TX_LAST_DESC			0x00100000
#घोषणा ZERO_PADDING			0x00080000
#घोषणा GEN_IP_V4_CHECKSUM		0x00040000
#घोषणा GEN_TCP_UDP_CHECKSUM		0x00020000
#घोषणा UDP_FRAME			0x00010000
#घोषणा MAC_HDR_EXTRA_4_BYTES		0x00008000
#घोषणा GEN_TCP_UDP_CHK_FULL		0x00000400
#घोषणा MAC_HDR_EXTRA_8_BYTES		0x00000200

#घोषणा TX_IHL_SHIFT			11


/* global *******************************************************************/
काष्ठा mv643xx_eth_shared_निजी अणु
	/*
	 * Ethernet controller base address.
	 */
	व्योम __iomem *base;

	/*
	 * Per-port MBUS winकरोw access रेजिस्टर value.
	 */
	u32 win_protect;

	/*
	 * Hardware-specअगरic parameters.
	 */
	पूर्णांक extended_rx_coal_limit;
	पूर्णांक tx_bw_control;
	पूर्णांक tx_csum_limit;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा TX_BW_CONTROL_ABSENT		0
#घोषणा TX_BW_CONTROL_OLD_LAYOUT	1
#घोषणा TX_BW_CONTROL_NEW_LAYOUT	2

अटल पूर्णांक mv643xx_eth_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक mv643xx_eth_stop(काष्ठा net_device *dev);


/* per-port *****************************************************************/
काष्ठा mib_counters अणु
	u64 good_octets_received;
	u32 bad_octets_received;
	u32 पूर्णांकernal_mac_transmit_err;
	u32 good_frames_received;
	u32 bad_frames_received;
	u32 broadcast_frames_received;
	u32 multicast_frames_received;
	u32 frames_64_octets;
	u32 frames_65_to_127_octets;
	u32 frames_128_to_255_octets;
	u32 frames_256_to_511_octets;
	u32 frames_512_to_1023_octets;
	u32 frames_1024_to_max_octets;
	u64 good_octets_sent;
	u32 good_frames_sent;
	u32 excessive_collision;
	u32 multicast_frames_sent;
	u32 broadcast_frames_sent;
	u32 unrec_mac_control_received;
	u32 fc_sent;
	u32 good_fc_received;
	u32 bad_fc_received;
	u32 undersize_received;
	u32 fragments_received;
	u32 oversize_received;
	u32 jabber_received;
	u32 mac_receive_error;
	u32 bad_crc_event;
	u32 collision;
	u32 late_collision;
	/* Non MIB hardware counters */
	u32 rx_discard;
	u32 rx_overrun;
पूर्ण;

काष्ठा rx_queue अणु
	पूर्णांक index;

	पूर्णांक rx_ring_size;

	पूर्णांक rx_desc_count;
	पूर्णांक rx_curr_desc;
	पूर्णांक rx_used_desc;

	काष्ठा rx_desc *rx_desc_area;
	dma_addr_t rx_desc_dma;
	पूर्णांक rx_desc_area_size;
	काष्ठा sk_buff **rx_skb;
पूर्ण;

काष्ठा tx_queue अणु
	पूर्णांक index;

	पूर्णांक tx_ring_size;

	पूर्णांक tx_desc_count;
	पूर्णांक tx_curr_desc;
	पूर्णांक tx_used_desc;

	पूर्णांक tx_stop_threshold;
	पूर्णांक tx_wake_threshold;

	अक्षर *tso_hdrs;
	dma_addr_t tso_hdrs_dma;

	काष्ठा tx_desc *tx_desc_area;
	अक्षर *tx_desc_mapping; /* array to track the type of the dma mapping */
	dma_addr_t tx_desc_dma;
	पूर्णांक tx_desc_area_size;

	काष्ठा sk_buff_head tx_skb;

	अचिन्हित दीर्घ tx_packets;
	अचिन्हित दीर्घ tx_bytes;
	अचिन्हित दीर्घ tx_dropped;
पूर्ण;

काष्ठा mv643xx_eth_निजी अणु
	काष्ठा mv643xx_eth_shared_निजी *shared;
	व्योम __iomem *base;
	पूर्णांक port_num;

	काष्ठा net_device *dev;

	काष्ठा समयr_list mib_counters_समयr;
	spinlock_t mib_counters_lock;
	काष्ठा mib_counters mib_counters;

	काष्ठा work_काष्ठा tx_समयout_task;

	काष्ठा napi_काष्ठा napi;
	u32 पूर्णांक_mask;
	u8 oom;
	u8 work_link;
	u8 work_tx;
	u8 work_tx_end;
	u8 work_rx;
	u8 work_rx_refill;

	पूर्णांक skb_size;

	/*
	 * RX state.
	 */
	पूर्णांक rx_ring_size;
	अचिन्हित दीर्घ rx_desc_sram_addr;
	पूर्णांक rx_desc_sram_size;
	पूर्णांक rxq_count;
	काष्ठा समयr_list rx_oom;
	काष्ठा rx_queue rxq[8];

	/*
	 * TX state.
	 */
	पूर्णांक tx_ring_size;
	अचिन्हित दीर्घ tx_desc_sram_addr;
	पूर्णांक tx_desc_sram_size;
	पूर्णांक txq_count;
	काष्ठा tx_queue txq[8];

	/*
	 * Hardware-specअगरic parameters.
	 */
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक t_clk;
पूर्ण;


/* port रेजिस्टर accessors **************************************************/
अटल अंतरभूत u32 rdl(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक offset)
अणु
	वापस पढ़ोl(mp->shared->base + offset);
पूर्ण

अटल अंतरभूत u32 rdlp(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक offset)
अणु
	वापस पढ़ोl(mp->base + offset);
पूर्ण

अटल अंतरभूत व्योम wrl(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक offset, u32 data)
अणु
	ग_लिखोl(data, mp->shared->base + offset);
पूर्ण

अटल अंतरभूत व्योम wrlp(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक offset, u32 data)
अणु
	ग_लिखोl(data, mp->base + offset);
पूर्ण


/* rxq/txq helper functions *************************************************/
अटल काष्ठा mv643xx_eth_निजी *rxq_to_mp(काष्ठा rx_queue *rxq)
अणु
	वापस container_of(rxq, काष्ठा mv643xx_eth_निजी, rxq[rxq->index]);
पूर्ण

अटल काष्ठा mv643xx_eth_निजी *txq_to_mp(काष्ठा tx_queue *txq)
अणु
	वापस container_of(txq, काष्ठा mv643xx_eth_निजी, txq[txq->index]);
पूर्ण

अटल व्योम rxq_enable(काष्ठा rx_queue *rxq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = rxq_to_mp(rxq);
	wrlp(mp, RXQ_COMMAND, 1 << rxq->index);
पूर्ण

अटल व्योम rxq_disable(काष्ठा rx_queue *rxq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = rxq_to_mp(rxq);
	u8 mask = 1 << rxq->index;

	wrlp(mp, RXQ_COMMAND, mask << 8);
	जबतक (rdlp(mp, RXQ_COMMAND) & mask)
		udelay(10);
पूर्ण

अटल व्योम txq_reset_hw_ptr(काष्ठा tx_queue *txq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	u32 addr;

	addr = (u32)txq->tx_desc_dma;
	addr += txq->tx_curr_desc * माप(काष्ठा tx_desc);
	wrlp(mp, TXQ_CURRENT_DESC_PTR(txq->index), addr);
पूर्ण

अटल व्योम txq_enable(काष्ठा tx_queue *txq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	wrlp(mp, TXQ_COMMAND, 1 << txq->index);
पूर्ण

अटल व्योम txq_disable(काष्ठा tx_queue *txq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	u8 mask = 1 << txq->index;

	wrlp(mp, TXQ_COMMAND, mask << 8);
	जबतक (rdlp(mp, TXQ_COMMAND) & mask)
		udelay(10);
पूर्ण

अटल व्योम txq_maybe_wake(काष्ठा tx_queue *txq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(mp->dev, txq->index);

	अगर (netअगर_tx_queue_stopped(nq)) अणु
		__netअगर_tx_lock(nq, smp_processor_id());
		अगर (txq->tx_desc_count <= txq->tx_wake_threshold)
			netअगर_tx_wake_queue(nq);
		__netअगर_tx_unlock(nq);
	पूर्ण
पूर्ण

अटल पूर्णांक rxq_process(काष्ठा rx_queue *rxq, पूर्णांक budget)
अणु
	काष्ठा mv643xx_eth_निजी *mp = rxq_to_mp(rxq);
	काष्ठा net_device_stats *stats = &mp->dev->stats;
	पूर्णांक rx;

	rx = 0;
	जबतक (rx < budget && rxq->rx_desc_count) अणु
		काष्ठा rx_desc *rx_desc;
		अचिन्हित पूर्णांक cmd_sts;
		काष्ठा sk_buff *skb;
		u16 byte_cnt;

		rx_desc = &rxq->rx_desc_area[rxq->rx_curr_desc];

		cmd_sts = rx_desc->cmd_sts;
		अगर (cmd_sts & BUFFER_OWNED_BY_DMA)
			अवरोध;
		rmb();

		skb = rxq->rx_skb[rxq->rx_curr_desc];
		rxq->rx_skb[rxq->rx_curr_desc] = शून्य;

		rxq->rx_curr_desc++;
		अगर (rxq->rx_curr_desc == rxq->rx_ring_size)
			rxq->rx_curr_desc = 0;

		dma_unmap_single(mp->dev->dev.parent, rx_desc->buf_ptr,
				 rx_desc->buf_size, DMA_FROM_DEVICE);
		rxq->rx_desc_count--;
		rx++;

		mp->work_rx_refill |= 1 << rxq->index;

		byte_cnt = rx_desc->byte_cnt;

		/*
		 * Update statistics.
		 *
		 * Note that the descriptor byte count includes 2 dummy
		 * bytes स्वतःmatically inserted by the hardware at the
		 * start of the packet (which we करोn't count), and a 4
		 * byte CRC at the end of the packet (which we करो count).
		 */
		stats->rx_packets++;
		stats->rx_bytes += byte_cnt - 2;

		/*
		 * In हाल we received a packet without first / last bits
		 * on, or the error summary bit is set, the packet needs
		 * to be dropped.
		 */
		अगर ((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC | ERROR_SUMMARY))
			!= (RX_FIRST_DESC | RX_LAST_DESC))
			जाओ err;

		/*
		 * The -4 is क्रम the CRC in the trailer of the
		 * received packet
		 */
		skb_put(skb, byte_cnt - 2 - 4);

		अगर (cmd_sts & LAYER_4_CHECKSUM_OK)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->protocol = eth_type_trans(skb, mp->dev);

		napi_gro_receive(&mp->napi, skb);

		जारी;

err:
		stats->rx_dropped++;

		अगर ((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
			(RX_FIRST_DESC | RX_LAST_DESC)) अणु
			अगर (net_ratelimit())
				netdev_err(mp->dev,
					   "received packet spanning multiple descriptors\n");
		पूर्ण

		अगर (cmd_sts & ERROR_SUMMARY)
			stats->rx_errors++;

		dev_kमुक्त_skb(skb);
	पूर्ण

	अगर (rx < budget)
		mp->work_rx &= ~(1 << rxq->index);

	वापस rx;
पूर्ण

अटल पूर्णांक rxq_refill(काष्ठा rx_queue *rxq, पूर्णांक budget)
अणु
	काष्ठा mv643xx_eth_निजी *mp = rxq_to_mp(rxq);
	पूर्णांक refilled;

	refilled = 0;
	जबतक (refilled < budget && rxq->rx_desc_count < rxq->rx_ring_size) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक rx;
		काष्ठा rx_desc *rx_desc;
		पूर्णांक size;

		skb = netdev_alloc_skb(mp->dev, mp->skb_size);

		अगर (skb == शून्य) अणु
			mp->oom = 1;
			जाओ oom;
		पूर्ण

		अगर (SKB_DMA_REALIGN)
			skb_reserve(skb, SKB_DMA_REALIGN);

		refilled++;
		rxq->rx_desc_count++;

		rx = rxq->rx_used_desc++;
		अगर (rxq->rx_used_desc == rxq->rx_ring_size)
			rxq->rx_used_desc = 0;

		rx_desc = rxq->rx_desc_area + rx;

		size = skb_end_poपूर्णांकer(skb) - skb->data;
		rx_desc->buf_ptr = dma_map_single(mp->dev->dev.parent,
						  skb->data, size,
						  DMA_FROM_DEVICE);
		rx_desc->buf_size = size;
		rxq->rx_skb[rx] = skb;
		wmb();
		rx_desc->cmd_sts = BUFFER_OWNED_BY_DMA | RX_ENABLE_INTERRUPT;
		wmb();

		/*
		 * The hardware स्वतःmatically prepends 2 bytes of
		 * dummy data to each received packet, so that the
		 * IP header ends up 16-byte aligned.
		 */
		skb_reserve(skb, 2);
	पूर्ण

	अगर (refilled < budget)
		mp->work_rx_refill &= ~(1 << rxq->index);

oom:
	वापस refilled;
पूर्ण


/* tx ***********************************************************************/
अटल अंतरभूत अचिन्हित पूर्णांक has_tiny_unaligned_frags(काष्ठा sk_buff *skb)
अणु
	पूर्णांक frag;

	क्रम (frag = 0; frag < skb_shinfo(skb)->nr_frags; frag++) अणु
		स्थिर skb_frag_t *fragp = &skb_shinfo(skb)->frags[frag];

		अगर (skb_frag_size(fragp) <= 8 && skb_frag_off(fragp) & 7)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skb_tx_csum(काष्ठा mv643xx_eth_निजी *mp, काष्ठा sk_buff *skb,
		       u16 *l4i_chk, u32 *command, पूर्णांक length)
अणु
	पूर्णांक ret;
	u32 cmd = 0;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		पूर्णांक hdr_len;
		पूर्णांक tag_bytes;

		BUG_ON(skb->protocol != htons(ETH_P_IP) &&
		       skb->protocol != htons(ETH_P_8021Q));

		hdr_len = (व्योम *)ip_hdr(skb) - (व्योम *)skb->data;
		tag_bytes = hdr_len - ETH_HLEN;

		अगर (length - hdr_len > mp->shared->tx_csum_limit ||
		    unlikely(tag_bytes & ~12)) अणु
			ret = skb_checksum_help(skb);
			अगर (!ret)
				जाओ no_csum;
			वापस ret;
		पूर्ण

		अगर (tag_bytes & 4)
			cmd |= MAC_HDR_EXTRA_4_BYTES;
		अगर (tag_bytes & 8)
			cmd |= MAC_HDR_EXTRA_8_BYTES;

		cmd |= GEN_TCP_UDP_CHECKSUM | GEN_TCP_UDP_CHK_FULL |
			   GEN_IP_V4_CHECKSUM   |
			   ip_hdr(skb)->ihl << TX_IHL_SHIFT;

		/* TODO: Revisit this. With the usage of GEN_TCP_UDP_CHK_FULL
		 * it seems we करोn't need to pass the initial checksum.
		 */
		चयन (ip_hdr(skb)->protocol) अणु
		हाल IPPROTO_UDP:
			cmd |= UDP_FRAME;
			*l4i_chk = 0;
			अवरोध;
		हाल IPPROTO_TCP:
			*l4i_chk = 0;
			अवरोध;
		शेष:
			WARN(1, "protocol not supported");
		पूर्ण
	पूर्ण अन्यथा अणु
no_csum:
		/* Errata BTS #50, IHL must be 5 अगर no HW checksum */
		cmd |= 5 << TX_IHL_SHIFT;
	पूर्ण
	*command = cmd;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
txq_put_data_tso(काष्ठा net_device *dev, काष्ठा tx_queue *txq,
		 काष्ठा sk_buff *skb, अक्षर *data, पूर्णांक length,
		 bool last_tcp, bool is_last)
अणु
	पूर्णांक tx_index;
	u32 cmd_sts;
	काष्ठा tx_desc *desc;

	tx_index = txq->tx_curr_desc++;
	अगर (txq->tx_curr_desc == txq->tx_ring_size)
		txq->tx_curr_desc = 0;
	desc = &txq->tx_desc_area[tx_index];
	txq->tx_desc_mapping[tx_index] = DESC_DMA_MAP_SINGLE;

	desc->l4i_chk = 0;
	desc->byte_cnt = length;

	अगर (length <= 8 && (uपूर्णांकptr_t)data & 0x7) अणु
		/* Copy unaligned small data fragment to TSO header data area */
		स_नकल(txq->tso_hdrs + tx_index * TSO_HEADER_SIZE,
		       data, length);
		desc->buf_ptr = txq->tso_hdrs_dma
			+ tx_index * TSO_HEADER_SIZE;
	पूर्ण अन्यथा अणु
		/* Alignment is okay, map buffer and hand off to hardware */
		txq->tx_desc_mapping[tx_index] = DESC_DMA_MAP_SINGLE;
		desc->buf_ptr = dma_map_single(dev->dev.parent, data,
			length, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dev->dev.parent,
					       desc->buf_ptr))) अणु
			WARN(1, "dma_map_single failed!\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	cmd_sts = BUFFER_OWNED_BY_DMA;
	अगर (last_tcp) अणु
		/* last descriptor in the TCP packet */
		cmd_sts |= ZERO_PADDING | TX_LAST_DESC;
		/* last descriptor in SKB */
		अगर (is_last)
			cmd_sts |= TX_ENABLE_INTERRUPT;
	पूर्ण
	desc->cmd_sts = cmd_sts;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
txq_put_hdr_tso(काष्ठा sk_buff *skb, काष्ठा tx_queue *txq, पूर्णांक length,
		u32 *first_cmd_sts, bool first_desc)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	पूर्णांक hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	पूर्णांक tx_index;
	काष्ठा tx_desc *desc;
	पूर्णांक ret;
	u32 cmd_csum = 0;
	u16 l4i_chk = 0;
	u32 cmd_sts;

	tx_index = txq->tx_curr_desc;
	desc = &txq->tx_desc_area[tx_index];

	ret = skb_tx_csum(mp, skb, &l4i_chk, &cmd_csum, length);
	अगर (ret)
		WARN(1, "failed to prepare checksum!");

	/* Should we set this? Can't use the value from skb_tx_csum()
	 * as it's not the correct initial L4 checksum to use.
	 */
	desc->l4i_chk = 0;

	desc->byte_cnt = hdr_len;
	desc->buf_ptr = txq->tso_hdrs_dma +
			txq->tx_curr_desc * TSO_HEADER_SIZE;
	cmd_sts = cmd_csum | BUFFER_OWNED_BY_DMA  | TX_FIRST_DESC |
				   GEN_CRC;

	/* Defer updating the first command descriptor until all
	 * following descriptors have been written.
	 */
	अगर (first_desc)
		*first_cmd_sts = cmd_sts;
	अन्यथा
		desc->cmd_sts = cmd_sts;

	txq->tx_curr_desc++;
	अगर (txq->tx_curr_desc == txq->tx_ring_size)
		txq->tx_curr_desc = 0;
पूर्ण

अटल पूर्णांक txq_submit_tso(काष्ठा tx_queue *txq, काष्ठा sk_buff *skb,
			  काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	पूर्णांक hdr_len, total_len, data_left, ret;
	पूर्णांक desc_count = 0;
	काष्ठा tso_t tso;
	काष्ठा tx_desc *first_tx_desc;
	u32 first_cmd_sts = 0;

	/* Count needed descriptors */
	अगर ((txq->tx_desc_count + tso_count_descs(skb)) >= txq->tx_ring_size) अणु
		netdev_dbg(dev, "not enough descriptors for TSO!\n");
		वापस -EBUSY;
	पूर्ण

	first_tx_desc = &txq->tx_desc_area[txq->tx_curr_desc];

	/* Initialize the TSO handler, and prepare the first payload */
	hdr_len = tso_start(skb, &tso);

	total_len = skb->len - hdr_len;
	जबतक (total_len > 0) अणु
		bool first_desc = (desc_count == 0);
		अक्षर *hdr;

		data_left = min_t(पूर्णांक, skb_shinfo(skb)->gso_size, total_len);
		total_len -= data_left;
		desc_count++;

		/* prepare packet headers: MAC + IP + TCP */
		hdr = txq->tso_hdrs + txq->tx_curr_desc * TSO_HEADER_SIZE;
		tso_build_hdr(skb, hdr, &tso, data_left, total_len == 0);
		txq_put_hdr_tso(skb, txq, data_left, &first_cmd_sts,
				first_desc);

		जबतक (data_left > 0) अणु
			पूर्णांक size;
			desc_count++;

			size = min_t(पूर्णांक, tso.size, data_left);
			ret = txq_put_data_tso(dev, txq, skb, tso.data, size,
					       size == data_left,
					       total_len == 0);
			अगर (ret)
				जाओ err_release;
			data_left -= size;
			tso_build_data(skb, &tso, size);
		पूर्ण
	पूर्ण

	__skb_queue_tail(&txq->tx_skb, skb);
	skb_tx_बारtamp(skb);

	/* ensure all other descriptors are written beक्रमe first cmd_sts */
	wmb();
	first_tx_desc->cmd_sts = first_cmd_sts;

	/* clear TX_END status */
	mp->work_tx_end &= ~(1 << txq->index);

	/* ensure all descriptors are written beक्रमe poking hardware */
	wmb();
	txq_enable(txq);
	txq->tx_desc_count += desc_count;
	वापस 0;
err_release:
	/* TODO: Release all used data descriptors; header descriptors must not
	 * be DMA-unmapped.
	 */
	वापस ret;
पूर्ण

अटल व्योम txq_submit_frag_skb(काष्ठा tx_queue *txq, काष्ठा sk_buff *skb)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक frag;

	क्रम (frag = 0; frag < nr_frags; frag++) अणु
		skb_frag_t *this_frag;
		पूर्णांक tx_index;
		काष्ठा tx_desc *desc;

		this_frag = &skb_shinfo(skb)->frags[frag];
		tx_index = txq->tx_curr_desc++;
		अगर (txq->tx_curr_desc == txq->tx_ring_size)
			txq->tx_curr_desc = 0;
		desc = &txq->tx_desc_area[tx_index];
		txq->tx_desc_mapping[tx_index] = DESC_DMA_MAP_PAGE;

		/*
		 * The last fragment will generate an पूर्णांकerrupt
		 * which will मुक्त the skb on TX completion.
		 */
		अगर (frag == nr_frags - 1) अणु
			desc->cmd_sts = BUFFER_OWNED_BY_DMA |
					ZERO_PADDING | TX_LAST_DESC |
					TX_ENABLE_INTERRUPT;
		पूर्ण अन्यथा अणु
			desc->cmd_sts = BUFFER_OWNED_BY_DMA;
		पूर्ण

		desc->l4i_chk = 0;
		desc->byte_cnt = skb_frag_size(this_frag);
		desc->buf_ptr = skb_frag_dma_map(mp->dev->dev.parent,
						 this_frag, 0, desc->byte_cnt,
						 DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक txq_submit_skb(काष्ठा tx_queue *txq, काष्ठा sk_buff *skb,
			  काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक tx_index;
	काष्ठा tx_desc *desc;
	u32 cmd_sts;
	u16 l4i_chk;
	पूर्णांक length, ret;

	cmd_sts = 0;
	l4i_chk = 0;

	अगर (txq->tx_ring_size - txq->tx_desc_count < MAX_SKB_FRAGS + 1) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "tx queue full?!\n");
		वापस -EBUSY;
	पूर्ण

	ret = skb_tx_csum(mp, skb, &l4i_chk, &cmd_sts, skb->len);
	अगर (ret)
		वापस ret;
	cmd_sts |= TX_FIRST_DESC | GEN_CRC | BUFFER_OWNED_BY_DMA;

	tx_index = txq->tx_curr_desc++;
	अगर (txq->tx_curr_desc == txq->tx_ring_size)
		txq->tx_curr_desc = 0;
	desc = &txq->tx_desc_area[tx_index];
	txq->tx_desc_mapping[tx_index] = DESC_DMA_MAP_SINGLE;

	अगर (nr_frags) अणु
		txq_submit_frag_skb(txq, skb);
		length = skb_headlen(skb);
	पूर्ण अन्यथा अणु
		cmd_sts |= ZERO_PADDING | TX_LAST_DESC | TX_ENABLE_INTERRUPT;
		length = skb->len;
	पूर्ण

	desc->l4i_chk = l4i_chk;
	desc->byte_cnt = length;
	desc->buf_ptr = dma_map_single(mp->dev->dev.parent, skb->data,
				       length, DMA_TO_DEVICE);

	__skb_queue_tail(&txq->tx_skb, skb);

	skb_tx_बारtamp(skb);

	/* ensure all other descriptors are written beक्रमe first cmd_sts */
	wmb();
	desc->cmd_sts = cmd_sts;

	/* clear TX_END status */
	mp->work_tx_end &= ~(1 << txq->index);

	/* ensure all descriptors are written beक्रमe poking hardware */
	wmb();
	txq_enable(txq);

	txq->tx_desc_count += nr_frags + 1;

	वापस 0;
पूर्ण

अटल netdev_tx_t mv643xx_eth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	पूर्णांक length, queue, ret;
	काष्ठा tx_queue *txq;
	काष्ठा netdev_queue *nq;

	queue = skb_get_queue_mapping(skb);
	txq = mp->txq + queue;
	nq = netdev_get_tx_queue(dev, queue);

	अगर (has_tiny_unaligned_frags(skb) && __skb_linearize(skb)) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev,
			      "failed to linearize skb with tiny unaligned fragment\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	length = skb->len;

	अगर (skb_is_gso(skb))
		ret = txq_submit_tso(txq, skb, dev);
	अन्यथा
		ret = txq_submit_skb(txq, skb, dev);
	अगर (!ret) अणु
		txq->tx_bytes += length;
		txq->tx_packets++;

		अगर (txq->tx_desc_count >= txq->tx_stop_threshold)
			netअगर_tx_stop_queue(nq);
	पूर्ण अन्यथा अणु
		txq->tx_dropped++;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण


/* tx napi ******************************************************************/
अटल व्योम txq_kick(काष्ठा tx_queue *txq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(mp->dev, txq->index);
	u32 hw_desc_ptr;
	u32 expected_ptr;

	__netअगर_tx_lock(nq, smp_processor_id());

	अगर (rdlp(mp, TXQ_COMMAND) & (1 << txq->index))
		जाओ out;

	hw_desc_ptr = rdlp(mp, TXQ_CURRENT_DESC_PTR(txq->index));
	expected_ptr = (u32)txq->tx_desc_dma +
				txq->tx_curr_desc * माप(काष्ठा tx_desc);

	अगर (hw_desc_ptr != expected_ptr)
		txq_enable(txq);

out:
	__netअगर_tx_unlock(nq);

	mp->work_tx_end &= ~(1 << txq->index);
पूर्ण

अटल पूर्णांक txq_reclaim(काष्ठा tx_queue *txq, पूर्णांक budget, पूर्णांक क्रमce)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(mp->dev, txq->index);
	पूर्णांक reclaimed;

	__netअगर_tx_lock_bh(nq);

	reclaimed = 0;
	जबतक (reclaimed < budget && txq->tx_desc_count > 0) अणु
		पूर्णांक tx_index;
		काष्ठा tx_desc *desc;
		u32 cmd_sts;
		अक्षर desc_dma_map;

		tx_index = txq->tx_used_desc;
		desc = &txq->tx_desc_area[tx_index];
		desc_dma_map = txq->tx_desc_mapping[tx_index];

		cmd_sts = desc->cmd_sts;

		अगर (cmd_sts & BUFFER_OWNED_BY_DMA) अणु
			अगर (!क्रमce)
				अवरोध;
			desc->cmd_sts = cmd_sts & ~BUFFER_OWNED_BY_DMA;
		पूर्ण

		txq->tx_used_desc = tx_index + 1;
		अगर (txq->tx_used_desc == txq->tx_ring_size)
			txq->tx_used_desc = 0;

		reclaimed++;
		txq->tx_desc_count--;

		अगर (!IS_TSO_HEADER(txq, desc->buf_ptr)) अणु

			अगर (desc_dma_map == DESC_DMA_MAP_PAGE)
				dma_unmap_page(mp->dev->dev.parent,
					       desc->buf_ptr,
					       desc->byte_cnt,
					       DMA_TO_DEVICE);
			अन्यथा
				dma_unmap_single(mp->dev->dev.parent,
						 desc->buf_ptr,
						 desc->byte_cnt,
						 DMA_TO_DEVICE);
		पूर्ण

		अगर (cmd_sts & TX_ENABLE_INTERRUPT) अणु
			काष्ठा sk_buff *skb = __skb_dequeue(&txq->tx_skb);

			अगर (!WARN_ON(!skb))
				dev_consume_skb_any(skb);
		पूर्ण

		अगर (cmd_sts & ERROR_SUMMARY) अणु
			netdev_info(mp->dev, "tx error\n");
			mp->dev->stats.tx_errors++;
		पूर्ण

	पूर्ण

	__netअगर_tx_unlock_bh(nq);

	अगर (reclaimed < budget)
		mp->work_tx &= ~(1 << txq->index);

	वापस reclaimed;
पूर्ण


/* tx rate control **********************************************************/
/*
 * Set total maximum TX rate (shared by all TX queues क्रम this port)
 * to 'rate' bits per second, with a maximum burst of 'burst' bytes.
 */
अटल व्योम tx_set_rate(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक rate, पूर्णांक burst)
अणु
	पूर्णांक token_rate;
	पूर्णांक mtu;
	पूर्णांक bucket_size;

	token_rate = ((rate / 1000) * 64) / (mp->t_clk / 1000);
	अगर (token_rate > 1023)
		token_rate = 1023;

	mtu = (mp->dev->mtu + 255) >> 8;
	अगर (mtu > 63)
		mtu = 63;

	bucket_size = (burst + 255) >> 8;
	अगर (bucket_size > 65535)
		bucket_size = 65535;

	चयन (mp->shared->tx_bw_control) अणु
	हाल TX_BW_CONTROL_OLD_LAYOUT:
		wrlp(mp, TX_BW_RATE, token_rate);
		wrlp(mp, TX_BW_MTU, mtu);
		wrlp(mp, TX_BW_BURST, bucket_size);
		अवरोध;
	हाल TX_BW_CONTROL_NEW_LAYOUT:
		wrlp(mp, TX_BW_RATE_MOVED, token_rate);
		wrlp(mp, TX_BW_MTU_MOVED, mtu);
		wrlp(mp, TX_BW_BURST_MOVED, bucket_size);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम txq_set_rate(काष्ठा tx_queue *txq, पूर्णांक rate, पूर्णांक burst)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	पूर्णांक token_rate;
	पूर्णांक bucket_size;

	token_rate = ((rate / 1000) * 64) / (mp->t_clk / 1000);
	अगर (token_rate > 1023)
		token_rate = 1023;

	bucket_size = (burst + 255) >> 8;
	अगर (bucket_size > 65535)
		bucket_size = 65535;

	wrlp(mp, TXQ_BW_TOKENS(txq->index), token_rate << 14);
	wrlp(mp, TXQ_BW_CONF(txq->index), (bucket_size << 10) | token_rate);
पूर्ण

अटल व्योम txq_set_fixed_prio_mode(काष्ठा tx_queue *txq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);
	पूर्णांक off;
	u32 val;

	/*
	 * Turn on fixed priority mode.
	 */
	off = 0;
	चयन (mp->shared->tx_bw_control) अणु
	हाल TX_BW_CONTROL_OLD_LAYOUT:
		off = TXQ_FIX_PRIO_CONF;
		अवरोध;
	हाल TX_BW_CONTROL_NEW_LAYOUT:
		off = TXQ_FIX_PRIO_CONF_MOVED;
		अवरोध;
	पूर्ण

	अगर (off) अणु
		val = rdlp(mp, off);
		val |= 1 << txq->index;
		wrlp(mp, off, val);
	पूर्ण
पूर्ण


/* mii management पूर्णांकerface *************************************************/
अटल व्योम mv643xx_eth_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	u32 pscr = rdlp(mp, PORT_SERIAL_CONTROL);
	u32 स्वतःneg_disable = FORCE_LINK_PASS |
	             DISABLE_AUTO_NEG_SPEED_GMII |
		     DISABLE_AUTO_NEG_FOR_FLOW_CTRL |
		     DISABLE_AUTO_NEG_FOR_DUPLEX;

	अगर (dev->phydev->स्वतःneg == AUTONEG_ENABLE) अणु
		/* enable स्वतः negotiation */
		pscr &= ~स्वतःneg_disable;
		जाओ out_ग_लिखो;
	पूर्ण

	pscr |= स्वतःneg_disable;

	अगर (dev->phydev->speed == SPEED_1000) अणु
		/* क्रमce gigabit, half duplex not supported */
		pscr |= SET_GMII_SPEED_TO_1000;
		pscr |= SET_FULL_DUPLEX_MODE;
		जाओ out_ग_लिखो;
	पूर्ण

	pscr &= ~SET_GMII_SPEED_TO_1000;

	अगर (dev->phydev->speed == SPEED_100)
		pscr |= SET_MII_SPEED_TO_100;
	अन्यथा
		pscr &= ~SET_MII_SPEED_TO_100;

	अगर (dev->phydev->duplex == DUPLEX_FULL)
		pscr |= SET_FULL_DUPLEX_MODE;
	अन्यथा
		pscr &= ~SET_FULL_DUPLEX_MODE;

out_ग_लिखो:
	wrlp(mp, PORT_SERIAL_CONTROL, pscr);
पूर्ण

/* statistics ***************************************************************/
अटल काष्ठा net_device_stats *mv643xx_eth_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	अचिन्हित दीर्घ tx_packets = 0;
	अचिन्हित दीर्घ tx_bytes = 0;
	अचिन्हित दीर्घ tx_dropped = 0;
	पूर्णांक i;

	क्रम (i = 0; i < mp->txq_count; i++) अणु
		काष्ठा tx_queue *txq = mp->txq + i;

		tx_packets += txq->tx_packets;
		tx_bytes += txq->tx_bytes;
		tx_dropped += txq->tx_dropped;
	पूर्ण

	stats->tx_packets = tx_packets;
	stats->tx_bytes = tx_bytes;
	stats->tx_dropped = tx_dropped;

	वापस stats;
पूर्ण

अटल अंतरभूत u32 mib_पढ़ो(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक offset)
अणु
	वापस rdl(mp, MIB_COUNTERS(mp->port_num) + offset);
पूर्ण

अटल व्योम mib_counters_clear(काष्ठा mv643xx_eth_निजी *mp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x80; i += 4)
		mib_पढ़ो(mp, i);

	/* Clear non MIB hw counters also */
	rdlp(mp, RX_DISCARD_FRAME_CNT);
	rdlp(mp, RX_OVERRUN_FRAME_CNT);
पूर्ण

अटल व्योम mib_counters_update(काष्ठा mv643xx_eth_निजी *mp)
अणु
	काष्ठा mib_counters *p = &mp->mib_counters;

	spin_lock_bh(&mp->mib_counters_lock);
	p->good_octets_received += mib_पढ़ो(mp, 0x00);
	p->bad_octets_received += mib_पढ़ो(mp, 0x08);
	p->पूर्णांकernal_mac_transmit_err += mib_पढ़ो(mp, 0x0c);
	p->good_frames_received += mib_पढ़ो(mp, 0x10);
	p->bad_frames_received += mib_पढ़ो(mp, 0x14);
	p->broadcast_frames_received += mib_पढ़ो(mp, 0x18);
	p->multicast_frames_received += mib_पढ़ो(mp, 0x1c);
	p->frames_64_octets += mib_पढ़ो(mp, 0x20);
	p->frames_65_to_127_octets += mib_पढ़ो(mp, 0x24);
	p->frames_128_to_255_octets += mib_पढ़ो(mp, 0x28);
	p->frames_256_to_511_octets += mib_पढ़ो(mp, 0x2c);
	p->frames_512_to_1023_octets += mib_पढ़ो(mp, 0x30);
	p->frames_1024_to_max_octets += mib_पढ़ो(mp, 0x34);
	p->good_octets_sent += mib_पढ़ो(mp, 0x38);
	p->good_frames_sent += mib_पढ़ो(mp, 0x40);
	p->excessive_collision += mib_पढ़ो(mp, 0x44);
	p->multicast_frames_sent += mib_पढ़ो(mp, 0x48);
	p->broadcast_frames_sent += mib_पढ़ो(mp, 0x4c);
	p->unrec_mac_control_received += mib_पढ़ो(mp, 0x50);
	p->fc_sent += mib_पढ़ो(mp, 0x54);
	p->good_fc_received += mib_पढ़ो(mp, 0x58);
	p->bad_fc_received += mib_पढ़ो(mp, 0x5c);
	p->undersize_received += mib_पढ़ो(mp, 0x60);
	p->fragments_received += mib_पढ़ो(mp, 0x64);
	p->oversize_received += mib_पढ़ो(mp, 0x68);
	p->jabber_received += mib_पढ़ो(mp, 0x6c);
	p->mac_receive_error += mib_पढ़ो(mp, 0x70);
	p->bad_crc_event += mib_पढ़ो(mp, 0x74);
	p->collision += mib_पढ़ो(mp, 0x78);
	p->late_collision += mib_पढ़ो(mp, 0x7c);
	/* Non MIB hardware counters */
	p->rx_discard += rdlp(mp, RX_DISCARD_FRAME_CNT);
	p->rx_overrun += rdlp(mp, RX_OVERRUN_FRAME_CNT);
	spin_unlock_bh(&mp->mib_counters_lock);
पूर्ण

अटल व्योम mib_counters_समयr_wrapper(काष्ठा समयr_list *t)
अणु
	काष्ठा mv643xx_eth_निजी *mp = from_समयr(mp, t, mib_counters_समयr);
	mib_counters_update(mp);
	mod_समयr(&mp->mib_counters_समयr, jअगरfies + 30 * HZ);
पूर्ण


/* पूर्णांकerrupt coalescing *****************************************************/
/*
 * Hardware coalescing parameters are set in units of 64 t_clk
 * cycles.  I.e.:
 *
 *	coal_delay_in_usec = 64000000 * रेजिस्टर_value / t_clk_rate
 *
 *	रेजिस्टर_value = coal_delay_in_usec * t_clk_rate / 64000000
 *
 * In the ->set*() methods, we round the computed रेजिस्टर value
 * to the nearest पूर्णांकeger.
 */
अटल अचिन्हित पूर्णांक get_rx_coal(काष्ठा mv643xx_eth_निजी *mp)
अणु
	u32 val = rdlp(mp, SDMA_CONFIG);
	u64 temp;

	अगर (mp->shared->extended_rx_coal_limit)
		temp = ((val & 0x02000000) >> 10) | ((val & 0x003fff80) >> 7);
	अन्यथा
		temp = (val & 0x003fff00) >> 8;

	temp *= 64000000;
	temp += mp->t_clk / 2;
	करो_भाग(temp, mp->t_clk);

	वापस (अचिन्हित पूर्णांक)temp;
पूर्ण

अटल व्योम set_rx_coal(काष्ठा mv643xx_eth_निजी *mp, अचिन्हित पूर्णांक usec)
अणु
	u64 temp;
	u32 val;

	temp = (u64)usec * mp->t_clk;
	temp += 31999999;
	करो_भाग(temp, 64000000);

	val = rdlp(mp, SDMA_CONFIG);
	अगर (mp->shared->extended_rx_coal_limit) अणु
		अगर (temp > 0xffff)
			temp = 0xffff;
		val &= ~0x023fff80;
		val |= (temp & 0x8000) << 10;
		val |= (temp & 0x7fff) << 7;
	पूर्ण अन्यथा अणु
		अगर (temp > 0x3fff)
			temp = 0x3fff;
		val &= ~0x003fff00;
		val |= (temp & 0x3fff) << 8;
	पूर्ण
	wrlp(mp, SDMA_CONFIG, val);
पूर्ण

अटल अचिन्हित पूर्णांक get_tx_coal(काष्ठा mv643xx_eth_निजी *mp)
अणु
	u64 temp;

	temp = (rdlp(mp, TX_FIFO_URGENT_THRESHOLD) & 0x3fff0) >> 4;
	temp *= 64000000;
	temp += mp->t_clk / 2;
	करो_भाग(temp, mp->t_clk);

	वापस (अचिन्हित पूर्णांक)temp;
पूर्ण

अटल व्योम set_tx_coal(काष्ठा mv643xx_eth_निजी *mp, अचिन्हित पूर्णांक usec)
अणु
	u64 temp;

	temp = (u64)usec * mp->t_clk;
	temp += 31999999;
	करो_भाग(temp, 64000000);

	अगर (temp > 0x3fff)
		temp = 0x3fff;

	wrlp(mp, TX_FIFO_URGENT_THRESHOLD, temp << 4);
पूर्ण


/* ethtool ******************************************************************/
काष्ठा mv643xx_eth_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक netdev_off;
	पूर्णांक mp_off;
पूर्ण;

#घोषणा SSTAT(m)						\
	अणु #m, माप_field(काष्ठा net_device_stats, m),		\
	  दुरत्व(काष्ठा net_device, stats.m), -1 पूर्ण

#घोषणा MIBSTAT(m)						\
	अणु #m, माप_field(काष्ठा mib_counters, m),		\
	  -1, दुरत्व(काष्ठा mv643xx_eth_निजी, mib_counters.m) पूर्ण

अटल स्थिर काष्ठा mv643xx_eth_stats mv643xx_eth_stats[] = अणु
	SSTAT(rx_packets),
	SSTAT(tx_packets),
	SSTAT(rx_bytes),
	SSTAT(tx_bytes),
	SSTAT(rx_errors),
	SSTAT(tx_errors),
	SSTAT(rx_dropped),
	SSTAT(tx_dropped),
	MIBSTAT(good_octets_received),
	MIBSTAT(bad_octets_received),
	MIBSTAT(पूर्णांकernal_mac_transmit_err),
	MIBSTAT(good_frames_received),
	MIBSTAT(bad_frames_received),
	MIBSTAT(broadcast_frames_received),
	MIBSTAT(multicast_frames_received),
	MIBSTAT(frames_64_octets),
	MIBSTAT(frames_65_to_127_octets),
	MIBSTAT(frames_128_to_255_octets),
	MIBSTAT(frames_256_to_511_octets),
	MIBSTAT(frames_512_to_1023_octets),
	MIBSTAT(frames_1024_to_max_octets),
	MIBSTAT(good_octets_sent),
	MIBSTAT(good_frames_sent),
	MIBSTAT(excessive_collision),
	MIBSTAT(multicast_frames_sent),
	MIBSTAT(broadcast_frames_sent),
	MIBSTAT(unrec_mac_control_received),
	MIBSTAT(fc_sent),
	MIBSTAT(good_fc_received),
	MIBSTAT(bad_fc_received),
	MIBSTAT(undersize_received),
	MIBSTAT(fragments_received),
	MIBSTAT(oversize_received),
	MIBSTAT(jabber_received),
	MIBSTAT(mac_receive_error),
	MIBSTAT(bad_crc_event),
	MIBSTAT(collision),
	MIBSTAT(late_collision),
	MIBSTAT(rx_discard),
	MIBSTAT(rx_overrun),
पूर्ण;

अटल पूर्णांक
mv643xx_eth_get_link_ksettings_phy(काष्ठा mv643xx_eth_निजी *mp,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा net_device *dev = mp->dev;

	phy_ethtool_ksettings_get(dev->phydev, cmd);

	/*
	 * The MAC करोes not support 1000baseT_Half.
	 */
	linkmode_clear_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
			   cmd->link_modes.supported);
	linkmode_clear_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
			   cmd->link_modes.advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
mv643xx_eth_get_link_ksettings_phyless(काष्ठा mv643xx_eth_निजी *mp,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 port_status;
	u32 supported, advertising;

	port_status = rdlp(mp, PORT_STATUS);

	supported = SUPPORTED_MII;
	advertising = ADVERTISED_MII;
	चयन (port_status & PORT_SPEED_MASK) अणु
	हाल PORT_SPEED_10:
		cmd->base.speed = SPEED_10;
		अवरोध;
	हाल PORT_SPEED_100:
		cmd->base.speed = SPEED_100;
		अवरोध;
	हाल PORT_SPEED_1000:
		cmd->base.speed = SPEED_1000;
		अवरोध;
	शेष:
		cmd->base.speed = -1;
		अवरोध;
	पूर्ण
	cmd->base.duplex = (port_status & FULL_DUPLEX) ?
		DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port = PORT_MII;
	cmd->base.phy_address = 0;
	cmd->base.स्वतःneg = AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल व्योम
mv643xx_eth_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts = 0;
	अगर (dev->phydev)
		phy_ethtool_get_wol(dev->phydev, wol);
पूर्ण

अटल पूर्णांक
mv643xx_eth_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक err;

	अगर (!dev->phydev)
		वापस -EOPNOTSUPP;

	err = phy_ethtool_set_wol(dev->phydev, wol);
	/* Given that mv643xx_eth works without the marvell-specअगरic PHY driver,
	 * this debugging hपूर्णांक is useful to have.
	 */
	अगर (err == -EOPNOTSUPP)
		netdev_info(dev, "The PHY does not support set_wol, was CONFIG_MARVELL_PHY enabled?\n");
	वापस err;
पूर्ण

अटल पूर्णांक
mv643xx_eth_get_link_ksettings(काष्ठा net_device *dev,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	अगर (dev->phydev)
		वापस mv643xx_eth_get_link_ksettings_phy(mp, cmd);
	अन्यथा
		वापस mv643xx_eth_get_link_ksettings_phyless(mp, cmd);
पूर्ण

अटल पूर्णांक
mv643xx_eth_set_link_ksettings(काष्ठा net_device *dev,
			       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ethtool_link_ksettings c = *cmd;
	u32 advertising;
	पूर्णांक ret;

	अगर (!dev->phydev)
		वापस -EINVAL;

	/*
	 * The MAC करोes not support 1000baseT_Half.
	 */
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						c.link_modes.advertising);
	advertising &= ~ADVERTISED_1000baseT_Half;
	ethtool_convert_legacy_u32_to_link_mode(c.link_modes.advertising,
						advertising);

	ret = phy_ethtool_ksettings_set(dev->phydev, &c);
	अगर (!ret)
		mv643xx_eth_adjust_link(dev);
	वापस ret;
पूर्ण

अटल व्योम mv643xx_eth_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, mv643xx_eth_driver_name,
		माप(drvinfo->driver));
	strlcpy(drvinfo->version, mv643xx_eth_driver_version,
		माप(drvinfo->version));
	strlcpy(drvinfo->fw_version, "N/A", माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, "platform", माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक
mv643xx_eth_get_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	ec->rx_coalesce_usecs = get_rx_coal(mp);
	ec->tx_coalesce_usecs = get_tx_coal(mp);

	वापस 0;
पूर्ण

अटल पूर्णांक
mv643xx_eth_set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	set_rx_coal(mp, ec->rx_coalesce_usecs);
	set_tx_coal(mp, ec->tx_coalesce_usecs);

	वापस 0;
पूर्ण

अटल व्योम
mv643xx_eth_get_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *er)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	er->rx_max_pending = 4096;
	er->tx_max_pending = 4096;

	er->rx_pending = mp->rx_ring_size;
	er->tx_pending = mp->tx_ring_size;
पूर्ण

अटल पूर्णांक
mv643xx_eth_set_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *er)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	अगर (er->rx_mini_pending || er->rx_jumbo_pending)
		वापस -EINVAL;

	mp->rx_ring_size = er->rx_pending < 4096 ? er->rx_pending : 4096;
	mp->tx_ring_size = clamp_t(अचिन्हित पूर्णांक, er->tx_pending,
				   MV643XX_MAX_SKB_DESCS * 2, 4096);
	अगर (mp->tx_ring_size != er->tx_pending)
		netdev_warn(dev, "TX queue size set to %u (requested %u)\n",
			    mp->tx_ring_size, er->tx_pending);

	अगर (netअगर_running(dev)) अणु
		mv643xx_eth_stop(dev);
		अगर (mv643xx_eth_खोलो(dev)) अणु
			netdev_err(dev,
				   "fatal error on re-opening device after ring param change\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक
mv643xx_eth_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	bool rx_csum = features & NETIF_F_RXCSUM;

	wrlp(mp, PORT_CONFIG, rx_csum ? 0x02000000 : 0x00000000);

	वापस 0;
पूर्ण

अटल व्योम mv643xx_eth_get_strings(काष्ठा net_device *dev,
				    uपूर्णांक32_t stringset, uपूर्णांक8_t *data)
अणु
	पूर्णांक i;

	अगर (stringset == ETH_SS_STATS) अणु
		क्रम (i = 0; i < ARRAY_SIZE(mv643xx_eth_stats); i++) अणु
			स_नकल(data + i * ETH_GSTRING_LEN,
				mv643xx_eth_stats[i].stat_string,
				ETH_GSTRING_LEN);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mv643xx_eth_get_ethtool_stats(काष्ठा net_device *dev,
					  काष्ठा ethtool_stats *stats,
					  uपूर्णांक64_t *data)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	पूर्णांक i;

	mv643xx_eth_get_stats(dev);
	mib_counters_update(mp);

	क्रम (i = 0; i < ARRAY_SIZE(mv643xx_eth_stats); i++) अणु
		स्थिर काष्ठा mv643xx_eth_stats *stat;
		व्योम *p;

		stat = mv643xx_eth_stats + i;

		अगर (stat->netdev_off >= 0)
			p = ((व्योम *)mp->dev) + stat->netdev_off;
		अन्यथा
			p = ((व्योम *)mp) + stat->mp_off;

		data[i] = (stat->माप_stat == 8) ?
				*(uपूर्णांक64_t *)p : *(uपूर्णांक32_t *)p;
	पूर्ण
पूर्ण

अटल पूर्णांक mv643xx_eth_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस ARRAY_SIZE(mv643xx_eth_stats);

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops mv643xx_eth_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo		= mv643xx_eth_get_drvinfo,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= mv643xx_eth_get_coalesce,
	.set_coalesce		= mv643xx_eth_set_coalesce,
	.get_ringparam		= mv643xx_eth_get_ringparam,
	.set_ringparam		= mv643xx_eth_set_ringparam,
	.get_strings		= mv643xx_eth_get_strings,
	.get_ethtool_stats	= mv643xx_eth_get_ethtool_stats,
	.get_sset_count		= mv643xx_eth_get_sset_count,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_wol                = mv643xx_eth_get_wol,
	.set_wol                = mv643xx_eth_set_wol,
	.get_link_ksettings	= mv643xx_eth_get_link_ksettings,
	.set_link_ksettings	= mv643xx_eth_set_link_ksettings,
पूर्ण;


/* address handling *********************************************************/
अटल व्योम uc_addr_get(काष्ठा mv643xx_eth_निजी *mp, अचिन्हित अक्षर *addr)
अणु
	अचिन्हित पूर्णांक mac_h = rdlp(mp, MAC_ADDR_HIGH);
	अचिन्हित पूर्णांक mac_l = rdlp(mp, MAC_ADDR_LOW);

	addr[0] = (mac_h >> 24) & 0xff;
	addr[1] = (mac_h >> 16) & 0xff;
	addr[2] = (mac_h >> 8) & 0xff;
	addr[3] = mac_h & 0xff;
	addr[4] = (mac_l >> 8) & 0xff;
	addr[5] = mac_l & 0xff;
पूर्ण

अटल व्योम uc_addr_set(काष्ठा mv643xx_eth_निजी *mp, अचिन्हित अक्षर *addr)
अणु
	wrlp(mp, MAC_ADDR_HIGH,
		(addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3]);
	wrlp(mp, MAC_ADDR_LOW, (addr[4] << 8) | addr[5]);
पूर्ण

अटल u32 uc_addr_filter_mask(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	u32 nibbles;

	अगर (dev->flags & IFF_PROMISC)
		वापस 0;

	nibbles = 1 << (dev->dev_addr[5] & 0x0f);
	netdev_क्रम_each_uc_addr(ha, dev) अणु
		अगर (स_भेद(dev->dev_addr, ha->addr, 5))
			वापस 0;
		अगर ((dev->dev_addr[5] ^ ha->addr[5]) & 0xf0)
			वापस 0;

		nibbles |= 1 << (ha->addr[5] & 0x0f);
	पूर्ण

	वापस nibbles;
पूर्ण

अटल व्योम mv643xx_eth_program_unicast_filter(काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	u32 port_config;
	u32 nibbles;
	पूर्णांक i;

	uc_addr_set(mp, dev->dev_addr);

	port_config = rdlp(mp, PORT_CONFIG) & ~UNICAST_PROMISCUOUS_MODE;

	nibbles = uc_addr_filter_mask(dev);
	अगर (!nibbles) अणु
		port_config |= UNICAST_PROMISCUOUS_MODE;
		nibbles = 0xffff;
	पूर्ण

	क्रम (i = 0; i < 16; i += 4) अणु
		पूर्णांक off = UNICAST_TABLE(mp->port_num) + i;
		u32 v;

		v = 0;
		अगर (nibbles & 1)
			v |= 0x00000001;
		अगर (nibbles & 2)
			v |= 0x00000100;
		अगर (nibbles & 4)
			v |= 0x00010000;
		अगर (nibbles & 8)
			v |= 0x01000000;
		nibbles >>= 4;

		wrl(mp, off, v);
	पूर्ण

	wrlp(mp, PORT_CONFIG, port_config);
पूर्ण

अटल पूर्णांक addr_crc(अचिन्हित अक्षर *addr)
अणु
	पूर्णांक crc = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		पूर्णांक j;

		crc = (crc ^ addr[i]) << 8;
		क्रम (j = 7; j >= 0; j--) अणु
			अगर (crc & (0x100 << j))
				crc ^= 0x107 << j;
		पूर्ण
	पूर्ण

	वापस crc;
पूर्ण

अटल व्योम mv643xx_eth_program_multicast_filter(काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	u32 *mc_spec;
	u32 *mc_other;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

	अगर (dev->flags & (IFF_PROMISC | IFF_ALLMULTI))
		जाओ promiscuous;

	/* Allocate both mc_spec and mc_other tables */
	mc_spec = kसुस्मृति(128, माप(u32), GFP_ATOMIC);
	अगर (!mc_spec)
		जाओ promiscuous;
	mc_other = &mc_spec[64];

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		u8 *a = ha->addr;
		u32 *table;
		u8 entry;

		अगर (स_भेद(a, "\x01\x00\x5e\x00\x00", 5) == 0) अणु
			table = mc_spec;
			entry = a[5];
		पूर्ण अन्यथा अणु
			table = mc_other;
			entry = addr_crc(a);
		पूर्ण

		table[entry >> 2] |= 1 << (8 * (entry & 3));
	पूर्ण

	क्रम (i = 0; i < 64; i++) अणु
		wrl(mp, SPECIAL_MCAST_TABLE(mp->port_num) + i * माप(u32),
		    mc_spec[i]);
		wrl(mp, OTHER_MCAST_TABLE(mp->port_num) + i * माप(u32),
		    mc_other[i]);
	पूर्ण

	kमुक्त(mc_spec);
	वापस;

promiscuous:
	क्रम (i = 0; i < 64; i++) अणु
		wrl(mp, SPECIAL_MCAST_TABLE(mp->port_num) + i * माप(u32),
		    0x01010101u);
		wrl(mp, OTHER_MCAST_TABLE(mp->port_num) + i * माप(u32),
		    0x01010101u);
	पूर्ण
पूर्ण

अटल व्योम mv643xx_eth_set_rx_mode(काष्ठा net_device *dev)
अणु
	mv643xx_eth_program_unicast_filter(dev);
	mv643xx_eth_program_multicast_filter(dev);
पूर्ण

अटल पूर्णांक mv643xx_eth_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;

	अगर (!is_valid_ether_addr(sa->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, sa->sa_data, ETH_ALEN);

	netअगर_addr_lock_bh(dev);
	mv643xx_eth_program_unicast_filter(dev);
	netअगर_addr_unlock_bh(dev);

	वापस 0;
पूर्ण


/* rx/tx queue initialisation ***********************************************/
अटल पूर्णांक rxq_init(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक index)
अणु
	काष्ठा rx_queue *rxq = mp->rxq + index;
	काष्ठा rx_desc *rx_desc;
	पूर्णांक size;
	पूर्णांक i;

	rxq->index = index;

	rxq->rx_ring_size = mp->rx_ring_size;

	rxq->rx_desc_count = 0;
	rxq->rx_curr_desc = 0;
	rxq->rx_used_desc = 0;

	size = rxq->rx_ring_size * माप(काष्ठा rx_desc);

	अगर (index == 0 && size <= mp->rx_desc_sram_size) अणु
		rxq->rx_desc_area = ioremap(mp->rx_desc_sram_addr,
						mp->rx_desc_sram_size);
		rxq->rx_desc_dma = mp->rx_desc_sram_addr;
	पूर्ण अन्यथा अणु
		rxq->rx_desc_area = dma_alloc_coherent(mp->dev->dev.parent,
						       size, &rxq->rx_desc_dma,
						       GFP_KERNEL);
	पूर्ण

	अगर (rxq->rx_desc_area == शून्य) अणु
		netdev_err(mp->dev,
			   "can't allocate rx ring (%d bytes)\n", size);
		जाओ out;
	पूर्ण
	स_रखो(rxq->rx_desc_area, 0, size);

	rxq->rx_desc_area_size = size;
	rxq->rx_skb = kसुस्मृति(rxq->rx_ring_size, माप(*rxq->rx_skb),
				    GFP_KERNEL);
	अगर (rxq->rx_skb == शून्य)
		जाओ out_मुक्त;

	rx_desc = rxq->rx_desc_area;
	क्रम (i = 0; i < rxq->rx_ring_size; i++) अणु
		पूर्णांक nexti;

		nexti = i + 1;
		अगर (nexti == rxq->rx_ring_size)
			nexti = 0;

		rx_desc[i].next_desc_ptr = rxq->rx_desc_dma +
					nexti * माप(काष्ठा rx_desc);
	पूर्ण

	वापस 0;


out_मुक्त:
	अगर (index == 0 && size <= mp->rx_desc_sram_size)
		iounmap(rxq->rx_desc_area);
	अन्यथा
		dma_मुक्त_coherent(mp->dev->dev.parent, size,
				  rxq->rx_desc_area,
				  rxq->rx_desc_dma);

out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम rxq_deinit(काष्ठा rx_queue *rxq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = rxq_to_mp(rxq);
	पूर्णांक i;

	rxq_disable(rxq);

	क्रम (i = 0; i < rxq->rx_ring_size; i++) अणु
		अगर (rxq->rx_skb[i]) अणु
			dev_consume_skb_any(rxq->rx_skb[i]);
			rxq->rx_desc_count--;
		पूर्ण
	पूर्ण

	अगर (rxq->rx_desc_count) अणु
		netdev_err(mp->dev, "error freeing rx ring -- %d skbs stuck\n",
			   rxq->rx_desc_count);
	पूर्ण

	अगर (rxq->index == 0 &&
	    rxq->rx_desc_area_size <= mp->rx_desc_sram_size)
		iounmap(rxq->rx_desc_area);
	अन्यथा
		dma_मुक्त_coherent(mp->dev->dev.parent, rxq->rx_desc_area_size,
				  rxq->rx_desc_area, rxq->rx_desc_dma);

	kमुक्त(rxq->rx_skb);
पूर्ण

अटल पूर्णांक txq_init(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक index)
अणु
	काष्ठा tx_queue *txq = mp->txq + index;
	काष्ठा tx_desc *tx_desc;
	पूर्णांक size;
	पूर्णांक ret;
	पूर्णांक i;

	txq->index = index;

	txq->tx_ring_size = mp->tx_ring_size;

	/* A queue must always have room क्रम at least one skb.
	 * Thereक्रमe, stop the queue when the मुक्त entries reaches
	 * the maximum number of descriptors per skb.
	 */
	txq->tx_stop_threshold = txq->tx_ring_size - MV643XX_MAX_SKB_DESCS;
	txq->tx_wake_threshold = txq->tx_stop_threshold / 2;

	txq->tx_desc_count = 0;
	txq->tx_curr_desc = 0;
	txq->tx_used_desc = 0;

	size = txq->tx_ring_size * माप(काष्ठा tx_desc);

	अगर (index == 0 && size <= mp->tx_desc_sram_size) अणु
		txq->tx_desc_area = ioremap(mp->tx_desc_sram_addr,
						mp->tx_desc_sram_size);
		txq->tx_desc_dma = mp->tx_desc_sram_addr;
	पूर्ण अन्यथा अणु
		txq->tx_desc_area = dma_alloc_coherent(mp->dev->dev.parent,
						       size, &txq->tx_desc_dma,
						       GFP_KERNEL);
	पूर्ण

	अगर (txq->tx_desc_area == शून्य) अणु
		netdev_err(mp->dev,
			   "can't allocate tx ring (%d bytes)\n", size);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(txq->tx_desc_area, 0, size);

	txq->tx_desc_area_size = size;

	tx_desc = txq->tx_desc_area;
	क्रम (i = 0; i < txq->tx_ring_size; i++) अणु
		काष्ठा tx_desc *txd = tx_desc + i;
		पूर्णांक nexti;

		nexti = i + 1;
		अगर (nexti == txq->tx_ring_size)
			nexti = 0;

		txd->cmd_sts = 0;
		txd->next_desc_ptr = txq->tx_desc_dma +
					nexti * माप(काष्ठा tx_desc);
	पूर्ण

	txq->tx_desc_mapping = kसुस्मृति(txq->tx_ring_size, माप(अक्षर),
				       GFP_KERNEL);
	अगर (!txq->tx_desc_mapping) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_desc_area;
	पूर्ण

	/* Allocate DMA buffers क्रम TSO MAC/IP/TCP headers */
	txq->tso_hdrs = dma_alloc_coherent(mp->dev->dev.parent,
					   txq->tx_ring_size * TSO_HEADER_SIZE,
					   &txq->tso_hdrs_dma, GFP_KERNEL);
	अगर (txq->tso_hdrs == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_desc_mapping;
	पूर्ण
	skb_queue_head_init(&txq->tx_skb);

	वापस 0;

err_मुक्त_desc_mapping:
	kमुक्त(txq->tx_desc_mapping);
err_मुक्त_desc_area:
	अगर (index == 0 && size <= mp->tx_desc_sram_size)
		iounmap(txq->tx_desc_area);
	अन्यथा
		dma_मुक्त_coherent(mp->dev->dev.parent, txq->tx_desc_area_size,
				  txq->tx_desc_area, txq->tx_desc_dma);
	वापस ret;
पूर्ण

अटल व्योम txq_deinit(काष्ठा tx_queue *txq)
अणु
	काष्ठा mv643xx_eth_निजी *mp = txq_to_mp(txq);

	txq_disable(txq);
	txq_reclaim(txq, txq->tx_ring_size, 1);

	BUG_ON(txq->tx_used_desc != txq->tx_curr_desc);

	अगर (txq->index == 0 &&
	    txq->tx_desc_area_size <= mp->tx_desc_sram_size)
		iounmap(txq->tx_desc_area);
	अन्यथा
		dma_मुक्त_coherent(mp->dev->dev.parent, txq->tx_desc_area_size,
				  txq->tx_desc_area, txq->tx_desc_dma);
	kमुक्त(txq->tx_desc_mapping);

	अगर (txq->tso_hdrs)
		dma_मुक्त_coherent(mp->dev->dev.parent,
				  txq->tx_ring_size * TSO_HEADER_SIZE,
				  txq->tso_hdrs, txq->tso_hdrs_dma);
पूर्ण


/* netdev ops and related ***************************************************/
अटल पूर्णांक mv643xx_eth_collect_events(काष्ठा mv643xx_eth_निजी *mp)
अणु
	u32 पूर्णांक_cause;
	u32 पूर्णांक_cause_ext;

	पूर्णांक_cause = rdlp(mp, INT_CAUSE) & mp->पूर्णांक_mask;
	अगर (पूर्णांक_cause == 0)
		वापस 0;

	पूर्णांक_cause_ext = 0;
	अगर (पूर्णांक_cause & INT_EXT) अणु
		पूर्णांक_cause &= ~INT_EXT;
		पूर्णांक_cause_ext = rdlp(mp, INT_CAUSE_EXT);
	पूर्ण

	अगर (पूर्णांक_cause) अणु
		wrlp(mp, INT_CAUSE, ~पूर्णांक_cause);
		mp->work_tx_end |= ((पूर्णांक_cause & INT_TX_END) >> 19) &
				~(rdlp(mp, TXQ_COMMAND) & 0xff);
		mp->work_rx |= (पूर्णांक_cause & INT_RX) >> 2;
	पूर्ण

	पूर्णांक_cause_ext &= INT_EXT_LINK_PHY | INT_EXT_TX;
	अगर (पूर्णांक_cause_ext) अणु
		wrlp(mp, INT_CAUSE_EXT, ~पूर्णांक_cause_ext);
		अगर (पूर्णांक_cause_ext & INT_EXT_LINK_PHY)
			mp->work_link = 1;
		mp->work_tx |= पूर्णांक_cause_ext & INT_EXT_TX;
	पूर्ण

	वापस 1;
पूर्ण

अटल irqवापस_t mv643xx_eth_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	अगर (unlikely(!mv643xx_eth_collect_events(mp)))
		वापस IRQ_NONE;

	wrlp(mp, INT_MASK, 0);
	napi_schedule(&mp->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम handle_link_event(काष्ठा mv643xx_eth_निजी *mp)
अणु
	काष्ठा net_device *dev = mp->dev;
	u32 port_status;
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक fc;

	port_status = rdlp(mp, PORT_STATUS);
	अगर (!(port_status & LINK_UP)) अणु
		अगर (netअगर_carrier_ok(dev)) अणु
			पूर्णांक i;

			netdev_info(dev, "link down\n");

			netअगर_carrier_off(dev);

			क्रम (i = 0; i < mp->txq_count; i++) अणु
				काष्ठा tx_queue *txq = mp->txq + i;

				txq_reclaim(txq, txq->tx_ring_size, 1);
				txq_reset_hw_ptr(txq);
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	चयन (port_status & PORT_SPEED_MASK) अणु
	हाल PORT_SPEED_10:
		speed = 10;
		अवरोध;
	हाल PORT_SPEED_100:
		speed = 100;
		अवरोध;
	हाल PORT_SPEED_1000:
		speed = 1000;
		अवरोध;
	शेष:
		speed = -1;
		अवरोध;
	पूर्ण
	duplex = (port_status & FULL_DUPLEX) ? 1 : 0;
	fc = (port_status & FLOW_CONTROL_ENABLED) ? 1 : 0;

	netdev_info(dev, "link up, %d Mb/s, %s duplex, flow control %sabled\n",
		    speed, duplex ? "full" : "half", fc ? "en" : "dis");

	अगर (!netअगर_carrier_ok(dev))
		netअगर_carrier_on(dev);
पूर्ण

अटल पूर्णांक mv643xx_eth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mv643xx_eth_निजी *mp;
	पूर्णांक work_करोne;

	mp = container_of(napi, काष्ठा mv643xx_eth_निजी, napi);

	अगर (unlikely(mp->oom)) अणु
		mp->oom = 0;
		del_समयr(&mp->rx_oom);
	पूर्ण

	work_करोne = 0;
	जबतक (work_करोne < budget) अणु
		u8 queue_mask;
		पूर्णांक queue;
		पूर्णांक work_tbd;

		अगर (mp->work_link) अणु
			mp->work_link = 0;
			handle_link_event(mp);
			work_करोne++;
			जारी;
		पूर्ण

		queue_mask = mp->work_tx | mp->work_tx_end | mp->work_rx;
		अगर (likely(!mp->oom))
			queue_mask |= mp->work_rx_refill;

		अगर (!queue_mask) अणु
			अगर (mv643xx_eth_collect_events(mp))
				जारी;
			अवरोध;
		पूर्ण

		queue = fls(queue_mask) - 1;
		queue_mask = 1 << queue;

		work_tbd = budget - work_करोne;
		अगर (work_tbd > 16)
			work_tbd = 16;

		अगर (mp->work_tx_end & queue_mask) अणु
			txq_kick(mp->txq + queue);
		पूर्ण अन्यथा अगर (mp->work_tx & queue_mask) अणु
			work_करोne += txq_reclaim(mp->txq + queue, work_tbd, 0);
			txq_maybe_wake(mp->txq + queue);
		पूर्ण अन्यथा अगर (mp->work_rx & queue_mask) अणु
			work_करोne += rxq_process(mp->rxq + queue, work_tbd);
		पूर्ण अन्यथा अगर (!mp->oom && (mp->work_rx_refill & queue_mask)) अणु
			work_करोne += rxq_refill(mp->rxq + queue, work_tbd);
		पूर्ण अन्यथा अणु
			BUG();
		पूर्ण
	पूर्ण

	अगर (work_करोne < budget) अणु
		अगर (mp->oom)
			mod_समयr(&mp->rx_oom, jअगरfies + (HZ / 10));
		napi_complete_करोne(napi, work_करोne);
		wrlp(mp, INT_MASK, mp->पूर्णांक_mask);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल अंतरभूत व्योम oom_समयr_wrapper(काष्ठा समयr_list *t)
अणु
	काष्ठा mv643xx_eth_निजी *mp = from_समयr(mp, t, rx_oom);

	napi_schedule(&mp->napi);
पूर्ण

अटल व्योम port_start(काष्ठा mv643xx_eth_निजी *mp)
अणु
	काष्ठा net_device *dev = mp->dev;
	u32 pscr;
	पूर्णांक i;

	/*
	 * Perक्रमm PHY reset, अगर there is a PHY.
	 */
	अगर (dev->phydev) अणु
		काष्ठा ethtool_link_ksettings cmd;

		mv643xx_eth_get_link_ksettings(dev, &cmd);
		phy_init_hw(dev->phydev);
		mv643xx_eth_set_link_ksettings(
			dev, (स्थिर काष्ठा ethtool_link_ksettings *)&cmd);
		phy_start(dev->phydev);
	पूर्ण

	/*
	 * Configure basic link parameters.
	 */
	pscr = rdlp(mp, PORT_SERIAL_CONTROL);

	pscr |= SERIAL_PORT_ENABLE;
	wrlp(mp, PORT_SERIAL_CONTROL, pscr);

	pscr |= DO_NOT_FORCE_LINK_FAIL;
	अगर (!dev->phydev)
		pscr |= FORCE_LINK_PASS;
	wrlp(mp, PORT_SERIAL_CONTROL, pscr);

	/*
	 * Configure TX path and queues.
	 */
	tx_set_rate(mp, 1000000000, 16777216);
	क्रम (i = 0; i < mp->txq_count; i++) अणु
		काष्ठा tx_queue *txq = mp->txq + i;

		txq_reset_hw_ptr(txq);
		txq_set_rate(txq, 1000000000, 16777216);
		txq_set_fixed_prio_mode(txq);
	पूर्ण

	/*
	 * Receive all unmatched unicast, TCP, UDP, BPDU and broadcast
	 * frames to RX queue #0, and include the pseuकरो-header when
	 * calculating receive checksums.
	 */
	mv643xx_eth_set_features(mp->dev, mp->dev->features);

	/*
	 * Treat BPDUs as normal multicasts, and disable partition mode.
	 */
	wrlp(mp, PORT_CONFIG_EXT, 0x00000000);

	/*
	 * Add configured unicast addresses to address filter table.
	 */
	mv643xx_eth_program_unicast_filter(mp->dev);

	/*
	 * Enable the receive queues.
	 */
	क्रम (i = 0; i < mp->rxq_count; i++) अणु
		काष्ठा rx_queue *rxq = mp->rxq + i;
		u32 addr;

		addr = (u32)rxq->rx_desc_dma;
		addr += rxq->rx_curr_desc * माप(काष्ठा rx_desc);
		wrlp(mp, RXQ_CURRENT_DESC_PTR(i), addr);

		rxq_enable(rxq);
	पूर्ण
पूर्ण

अटल व्योम mv643xx_eth_recalc_skb_size(काष्ठा mv643xx_eth_निजी *mp)
अणु
	पूर्णांक skb_size;

	/*
	 * Reserve 2+14 bytes क्रम an ethernet header (the hardware
	 * स्वतःmatically prepends 2 bytes of dummy data to each
	 * received packet), 16 bytes क्रम up to four VLAN tags, and
	 * 4 bytes क्रम the trailing FCS -- 36 bytes total.
	 */
	skb_size = mp->dev->mtu + 36;

	/*
	 * Make sure that the skb size is a multiple of 8 bytes, as
	 * the lower three bits of the receive descriptor's buffer
	 * size field are ignored by the hardware.
	 */
	mp->skb_size = (skb_size + 7) & ~7;

	/*
	 * If NET_SKB_PAD is smaller than a cache line,
	 * netdev_alloc_skb() will cause skb->data to be misaligned
	 * to a cache line boundary.  If this is the हाल, include
	 * some extra space to allow re-aligning the data area.
	 */
	mp->skb_size += SKB_DMA_REALIGN;
पूर्ण

अटल पूर्णांक mv643xx_eth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	पूर्णांक err;
	पूर्णांक i;

	wrlp(mp, INT_CAUSE, 0);
	wrlp(mp, INT_CAUSE_EXT, 0);
	rdlp(mp, INT_CAUSE_EXT);

	err = request_irq(dev->irq, mv643xx_eth_irq,
			  IRQF_SHARED, dev->name, dev);
	अगर (err) अणु
		netdev_err(dev, "can't assign irq\n");
		वापस -EAGAIN;
	पूर्ण

	mv643xx_eth_recalc_skb_size(mp);

	napi_enable(&mp->napi);

	mp->पूर्णांक_mask = INT_EXT;

	क्रम (i = 0; i < mp->rxq_count; i++) अणु
		err = rxq_init(mp, i);
		अगर (err) अणु
			जबतक (--i >= 0)
				rxq_deinit(mp->rxq + i);
			जाओ out;
		पूर्ण

		rxq_refill(mp->rxq + i, पूर्णांक_उच्च);
		mp->पूर्णांक_mask |= INT_RX_0 << i;
	पूर्ण

	अगर (mp->oom) अणु
		mp->rx_oom.expires = jअगरfies + (HZ / 10);
		add_समयr(&mp->rx_oom);
	पूर्ण

	क्रम (i = 0; i < mp->txq_count; i++) अणु
		err = txq_init(mp, i);
		अगर (err) अणु
			जबतक (--i >= 0)
				txq_deinit(mp->txq + i);
			जाओ out_मुक्त;
		पूर्ण
		mp->पूर्णांक_mask |= INT_TX_END_0 << i;
	पूर्ण

	add_समयr(&mp->mib_counters_समयr);
	port_start(mp);

	wrlp(mp, INT_MASK_EXT, INT_EXT_LINK_PHY | INT_EXT_TX);
	wrlp(mp, INT_MASK, mp->पूर्णांक_mask);

	वापस 0;


out_मुक्त:
	क्रम (i = 0; i < mp->rxq_count; i++)
		rxq_deinit(mp->rxq + i);
out:
	मुक्त_irq(dev->irq, dev);

	वापस err;
पूर्ण

अटल व्योम port_reset(काष्ठा mv643xx_eth_निजी *mp)
अणु
	अचिन्हित पूर्णांक data;
	पूर्णांक i;

	क्रम (i = 0; i < mp->rxq_count; i++)
		rxq_disable(mp->rxq + i);
	क्रम (i = 0; i < mp->txq_count; i++)
		txq_disable(mp->txq + i);

	जबतक (1) अणु
		u32 ps = rdlp(mp, PORT_STATUS);

		अगर ((ps & (TX_IN_PROGRESS | TX_FIFO_EMPTY)) == TX_FIFO_EMPTY)
			अवरोध;
		udelay(10);
	पूर्ण

	/* Reset the Enable bit in the Configuration Register */
	data = rdlp(mp, PORT_SERIAL_CONTROL);
	data &= ~(SERIAL_PORT_ENABLE		|
		  DO_NOT_FORCE_LINK_FAIL	|
		  FORCE_LINK_PASS);
	wrlp(mp, PORT_SERIAL_CONTROL, data);
पूर्ण

अटल पूर्णांक mv643xx_eth_stop(काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);
	पूर्णांक i;

	wrlp(mp, INT_MASK_EXT, 0x00000000);
	wrlp(mp, INT_MASK, 0x00000000);
	rdlp(mp, INT_MASK);

	napi_disable(&mp->napi);

	del_समयr_sync(&mp->rx_oom);

	netअगर_carrier_off(dev);
	अगर (dev->phydev)
		phy_stop(dev->phydev);
	मुक्त_irq(dev->irq, dev);

	port_reset(mp);
	mv643xx_eth_get_stats(dev);
	mib_counters_update(mp);
	del_समयr_sync(&mp->mib_counters_समयr);

	क्रम (i = 0; i < mp->rxq_count; i++)
		rxq_deinit(mp->rxq + i);
	क्रम (i = 0; i < mp->txq_count; i++)
		txq_deinit(mp->txq + i);

	वापस 0;
पूर्ण

अटल पूर्णांक mv643xx_eth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक ret;

	अगर (!dev->phydev)
		वापस -ENOTSUPP;

	ret = phy_mii_ioctl(dev->phydev, अगरr, cmd);
	अगर (!ret)
		mv643xx_eth_adjust_link(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक mv643xx_eth_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	dev->mtu = new_mtu;
	mv643xx_eth_recalc_skb_size(mp);
	tx_set_rate(mp, 1000000000, 16777216);

	अगर (!netअगर_running(dev))
		वापस 0;

	/*
	 * Stop and then re-खोलो the पूर्णांकerface. This will allocate RX
	 * skbs of the new MTU.
	 * There is a possible danger that the खोलो will not succeed,
	 * due to memory being full.
	 */
	mv643xx_eth_stop(dev);
	अगर (mv643xx_eth_खोलो(dev)) अणु
		netdev_err(dev,
			   "fatal error on re-opening device after MTU change\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tx_समयout_task(काष्ठा work_काष्ठा *ugly)
अणु
	काष्ठा mv643xx_eth_निजी *mp;

	mp = container_of(ugly, काष्ठा mv643xx_eth_निजी, tx_समयout_task);
	अगर (netअगर_running(mp->dev)) अणु
		netअगर_tx_stop_all_queues(mp->dev);
		port_reset(mp);
		port_start(mp);
		netअगर_tx_wake_all_queues(mp->dev);
	पूर्ण
पूर्ण

अटल व्योम mv643xx_eth_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	netdev_info(dev, "tx timeout\n");

	schedule_work(&mp->tx_समयout_task);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम mv643xx_eth_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = netdev_priv(dev);

	wrlp(mp, INT_MASK, 0x00000000);
	rdlp(mp, INT_MASK);

	mv643xx_eth_irq(dev->irq, dev);

	wrlp(mp, INT_MASK, mp->पूर्णांक_mask);
पूर्ण
#पूर्ण_अगर


/* platक्रमm glue ************************************************************/
अटल व्योम
mv643xx_eth_conf_mbus_winकरोws(काष्ठा mv643xx_eth_shared_निजी *msp,
			      स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	व्योम __iomem *base = msp->base;
	u32 win_enable;
	u32 win_protect;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		ग_लिखोl(0, base + WINDOW_BASE(i));
		ग_लिखोl(0, base + WINDOW_SIZE(i));
		अगर (i < 4)
			ग_लिखोl(0, base + WINDOW_REMAP_HIGH(i));
	पूर्ण

	win_enable = 0x3f;
	win_protect = 0;

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		ग_लिखोl((cs->base & 0xffff0000) |
			(cs->mbus_attr << 8) |
			dram->mbus_dram_target_id, base + WINDOW_BASE(i));
		ग_लिखोl((cs->size - 1) & 0xffff0000, base + WINDOW_SIZE(i));

		win_enable &= ~(1 << i);
		win_protect |= 3 << (2 * i);
	पूर्ण

	ग_लिखोl(win_enable, base + WINDOW_BAR_ENABLE);
	msp->win_protect = win_protect;
पूर्ण

अटल व्योम infer_hw_params(काष्ठा mv643xx_eth_shared_निजी *msp)
अणु
	/*
	 * Check whether we have a 14-bit coal limit field in bits
	 * [21:8], or a 16-bit coal limit in bits [25,21:7] of the
	 * SDMA config रेजिस्टर.
	 */
	ग_लिखोl(0x02000000, msp->base + 0x0400 + SDMA_CONFIG);
	अगर (पढ़ोl(msp->base + 0x0400 + SDMA_CONFIG) & 0x02000000)
		msp->extended_rx_coal_limit = 1;
	अन्यथा
		msp->extended_rx_coal_limit = 0;

	/*
	 * Check whether the MAC supports TX rate control, and अगर
	 * yes, whether its associated रेजिस्टरs are in the old or
	 * the new place.
	 */
	ग_लिखोl(1, msp->base + 0x0400 + TX_BW_MTU_MOVED);
	अगर (पढ़ोl(msp->base + 0x0400 + TX_BW_MTU_MOVED) & 1) अणु
		msp->tx_bw_control = TX_BW_CONTROL_NEW_LAYOUT;
	पूर्ण अन्यथा अणु
		ग_लिखोl(7, msp->base + 0x0400 + TX_BW_RATE);
		अगर (पढ़ोl(msp->base + 0x0400 + TX_BW_RATE) & 7)
			msp->tx_bw_control = TX_BW_CONTROL_OLD_LAYOUT;
		अन्यथा
			msp->tx_bw_control = TX_BW_CONTROL_ABSENT;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id mv643xx_eth_shared_ids[] = अणु
	अणु .compatible = "marvell,orion-eth", पूर्ण,
	अणु .compatible = "marvell,kirkwood-eth", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mv643xx_eth_shared_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF_IRQ
#घोषणा mv643xx_eth_property(_np, _name, _v)				\
	करो अणु								\
		u32 पंचांगp;						\
		अगर (!of_property_पढ़ो_u32(_np, "marvell," _name, &पंचांगp))	\
			_v = पंचांगp;					\
	पूर्ण जबतक (0)

अटल काष्ठा platक्रमm_device *port_platdev[3];

अटल पूर्णांक mv643xx_eth_shared_of_add_port(काष्ठा platक्रमm_device *pdev,
					  काष्ठा device_node *pnp)
अणु
	काष्ठा platक्रमm_device *ppdev;
	काष्ठा mv643xx_eth_platक्रमm_data ppd;
	काष्ठा resource res;
	पूर्णांक ret;
	पूर्णांक dev_num = 0;

	स_रखो(&ppd, 0, माप(ppd));
	ppd.shared = pdev;

	स_रखो(&res, 0, माप(res));
	अगर (of_irq_to_resource(pnp, 0, &res) <= 0) अणु
		dev_err(&pdev->dev, "missing interrupt on %pOFn\n", pnp);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(pnp, "reg", &ppd.port_number)) अणु
		dev_err(&pdev->dev, "missing reg property on %pOFn\n", pnp);
		वापस -EINVAL;
	पूर्ण

	अगर (ppd.port_number >= 3) अणु
		dev_err(&pdev->dev, "invalid reg property on %pOFn\n", pnp);
		वापस -EINVAL;
	पूर्ण

	जबतक (dev_num < 3 && port_platdev[dev_num])
		dev_num++;

	अगर (dev_num == 3) अणु
		dev_err(&pdev->dev, "too many ports registered\n");
		वापस -EINVAL;
	पूर्ण

	of_get_mac_address(pnp, ppd.mac_addr);

	mv643xx_eth_property(pnp, "tx-queue-size", ppd.tx_queue_size);
	mv643xx_eth_property(pnp, "tx-sram-addr", ppd.tx_sram_addr);
	mv643xx_eth_property(pnp, "tx-sram-size", ppd.tx_sram_size);
	mv643xx_eth_property(pnp, "rx-queue-size", ppd.rx_queue_size);
	mv643xx_eth_property(pnp, "rx-sram-addr", ppd.rx_sram_addr);
	mv643xx_eth_property(pnp, "rx-sram-size", ppd.rx_sram_size);

	ppd.phy_node = of_parse_phandle(pnp, "phy-handle", 0);
	अगर (!ppd.phy_node) अणु
		ppd.phy_addr = MV643XX_ETH_PHY_NONE;
		of_property_पढ़ो_u32(pnp, "speed", &ppd.speed);
		of_property_पढ़ो_u32(pnp, "duplex", &ppd.duplex);
	पूर्ण

	ppdev = platक्रमm_device_alloc(MV643XX_ETH_NAME, dev_num);
	अगर (!ppdev)
		वापस -ENOMEM;
	ppdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	ppdev->dev.of_node = pnp;

	ret = platक्रमm_device_add_resources(ppdev, &res, 1);
	अगर (ret)
		जाओ port_err;

	ret = platक्रमm_device_add_data(ppdev, &ppd, माप(ppd));
	अगर (ret)
		जाओ port_err;

	ret = platक्रमm_device_add(ppdev);
	अगर (ret)
		जाओ port_err;

	port_platdev[dev_num] = ppdev;

	वापस 0;

port_err:
	platक्रमm_device_put(ppdev);
	वापस ret;
पूर्ण

अटल पूर्णांक mv643xx_eth_shared_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv643xx_eth_shared_platक्रमm_data *pd;
	काष्ठा device_node *pnp, *np = pdev->dev.of_node;
	पूर्णांक ret;

	/* bail out अगर not रेजिस्टरed from DT */
	अगर (!np)
		वापस 0;

	pd = devm_kzalloc(&pdev->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;
	pdev->dev.platक्रमm_data = pd;

	mv643xx_eth_property(np, "tx-checksum-limit", pd->tx_csum_limit);

	क्रम_each_available_child_of_node(np, pnp) अणु
		ret = mv643xx_eth_shared_of_add_port(pdev, pnp);
		अगर (ret) अणु
			of_node_put(pnp);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mv643xx_eth_shared_of_हटाओ(व्योम)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < 3; n++) अणु
		platक्रमm_device_del(port_platdev[n]);
		port_platdev[n] = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mv643xx_eth_shared_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mv643xx_eth_shared_of_हटाओ(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mv643xx_eth_shared_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल पूर्णांक mv643xx_eth_version_prपूर्णांकed;
	काष्ठा mv643xx_eth_shared_platक्रमm_data *pd;
	काष्ठा mv643xx_eth_shared_निजी *msp;
	स्थिर काष्ठा mbus_dram_target_info *dram;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (!mv643xx_eth_version_prपूर्णांकed++)
		pr_notice("MV-643xx 10/100/1000 ethernet driver version %s\n",
			  mv643xx_eth_driver_version);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य)
		वापस -EINVAL;

	msp = devm_kzalloc(&pdev->dev, माप(*msp), GFP_KERNEL);
	अगर (msp == शून्य)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, msp);

	msp->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (msp->base == शून्य)
		वापस -ENOMEM;

	msp->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (!IS_ERR(msp->clk))
		clk_prepare_enable(msp->clk);

	/*
	 * (Re-)program MBUS remapping winकरोws अगर we are asked to.
	 */
	dram = mv_mbus_dram_info();
	अगर (dram)
		mv643xx_eth_conf_mbus_winकरोws(msp, dram);

	ret = mv643xx_eth_shared_of_probe(pdev);
	अगर (ret)
		जाओ err_put_clk;
	pd = dev_get_platdata(&pdev->dev);

	msp->tx_csum_limit = (pd != शून्य && pd->tx_csum_limit) ?
					pd->tx_csum_limit : 9 * 1024;
	infer_hw_params(msp);

	वापस 0;

err_put_clk:
	अगर (!IS_ERR(msp->clk))
		clk_disable_unprepare(msp->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक mv643xx_eth_shared_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv643xx_eth_shared_निजी *msp = platक्रमm_get_drvdata(pdev);

	mv643xx_eth_shared_of_हटाओ();
	अगर (!IS_ERR(msp->clk))
		clk_disable_unprepare(msp->clk);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mv643xx_eth_shared_driver = अणु
	.probe		= mv643xx_eth_shared_probe,
	.हटाओ		= mv643xx_eth_shared_हटाओ,
	.driver = अणु
		.name	= MV643XX_ETH_SHARED_NAME,
		.of_match_table = of_match_ptr(mv643xx_eth_shared_ids),
	पूर्ण,
पूर्ण;

अटल व्योम phy_addr_set(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक phy_addr)
अणु
	पूर्णांक addr_shअगरt = 5 * mp->port_num;
	u32 data;

	data = rdl(mp, PHY_ADDR);
	data &= ~(0x1f << addr_shअगरt);
	data |= (phy_addr & 0x1f) << addr_shअगरt;
	wrl(mp, PHY_ADDR, data);
पूर्ण

अटल पूर्णांक phy_addr_get(काष्ठा mv643xx_eth_निजी *mp)
अणु
	अचिन्हित पूर्णांक data;

	data = rdl(mp, PHY_ADDR);

	वापस (data >> (5 * mp->port_num)) & 0x1f;
पूर्ण

अटल व्योम set_params(काष्ठा mv643xx_eth_निजी *mp,
		       काष्ठा mv643xx_eth_platक्रमm_data *pd)
अणु
	काष्ठा net_device *dev = mp->dev;
	अचिन्हित पूर्णांक tx_ring_size;

	अगर (is_valid_ether_addr(pd->mac_addr))
		स_नकल(dev->dev_addr, pd->mac_addr, ETH_ALEN);
	अन्यथा
		uc_addr_get(mp, dev->dev_addr);

	mp->rx_ring_size = DEFAULT_RX_QUEUE_SIZE;
	अगर (pd->rx_queue_size)
		mp->rx_ring_size = pd->rx_queue_size;
	mp->rx_desc_sram_addr = pd->rx_sram_addr;
	mp->rx_desc_sram_size = pd->rx_sram_size;

	mp->rxq_count = pd->rx_queue_count ? : 1;

	tx_ring_size = DEFAULT_TX_QUEUE_SIZE;
	अगर (pd->tx_queue_size)
		tx_ring_size = pd->tx_queue_size;

	mp->tx_ring_size = clamp_t(अचिन्हित पूर्णांक, tx_ring_size,
				   MV643XX_MAX_SKB_DESCS * 2, 4096);
	अगर (mp->tx_ring_size != tx_ring_size)
		netdev_warn(dev, "TX queue size set to %u (requested %u)\n",
			    mp->tx_ring_size, tx_ring_size);

	mp->tx_desc_sram_addr = pd->tx_sram_addr;
	mp->tx_desc_sram_size = pd->tx_sram_size;

	mp->txq_count = pd->tx_queue_count ? : 1;
पूर्ण

अटल पूर्णांक get_phy_mode(काष्ठा mv643xx_eth_निजी *mp)
अणु
	काष्ठा device *dev = mp->dev->dev.parent;
	phy_पूर्णांकerface_t अगरace;
	पूर्णांक err;

	अगर (dev->of_node)
		err = of_get_phy_mode(dev->of_node, &अगरace);

	/* Historical शेष अगर unspecअगरied. We could also पढ़ो/ग_लिखो
	 * the पूर्णांकerface state in the PSC1
	 */
	अगर (!dev->of_node || err)
		अगरace = PHY_INTERFACE_MODE_GMII;
	वापस अगरace;
पूर्ण

अटल काष्ठा phy_device *phy_scan(काष्ठा mv643xx_eth_निजी *mp,
				   पूर्णांक phy_addr)
अणु
	काष्ठा phy_device *phydev;
	पूर्णांक start;
	पूर्णांक num;
	पूर्णांक i;
	अक्षर phy_id[MII_BUS_ID_SIZE + 3];

	अगर (phy_addr == MV643XX_ETH_PHY_ADDR_DEFAULT) अणु
		start = phy_addr_get(mp) & 0x1f;
		num = 32;
	पूर्ण अन्यथा अणु
		start = phy_addr & 0x1f;
		num = 1;
	पूर्ण

	/* Attempt to connect to the PHY using orion-mdio */
	phydev = ERR_PTR(-ENODEV);
	क्रम (i = 0; i < num; i++) अणु
		पूर्णांक addr = (start + i) & 0x1f;

		snम_लिखो(phy_id, माप(phy_id), PHY_ID_FMT,
				"orion-mdio-mii", addr);

		phydev = phy_connect(mp->dev, phy_id, mv643xx_eth_adjust_link,
				     get_phy_mode(mp));
		अगर (!IS_ERR(phydev)) अणु
			phy_addr_set(mp, addr);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस phydev;
पूर्ण

अटल व्योम phy_init(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा net_device *dev = mp->dev;
	काष्ठा phy_device *phy = dev->phydev;

	अगर (speed == 0) अणु
		phy->स्वतःneg = AUTONEG_ENABLE;
		phy->speed = 0;
		phy->duplex = 0;
		linkmode_copy(phy->advertising, phy->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				 phy->advertising);
	पूर्ण अन्यथा अणु
		phy->स्वतःneg = AUTONEG_DISABLE;
		linkmode_zero(phy->advertising);
		phy->speed = speed;
		phy->duplex = duplex;
	पूर्ण
	phy_start_aneg(phy);
पूर्ण

अटल व्योम init_pscr(काष्ठा mv643xx_eth_निजी *mp, पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा net_device *dev = mp->dev;
	u32 pscr;

	pscr = rdlp(mp, PORT_SERIAL_CONTROL);
	अगर (pscr & SERIAL_PORT_ENABLE) अणु
		pscr &= ~SERIAL_PORT_ENABLE;
		wrlp(mp, PORT_SERIAL_CONTROL, pscr);
	पूर्ण

	pscr = MAX_RX_PACKET_9700BYTE | SERIAL_PORT_CONTROL_RESERVED;
	अगर (!dev->phydev) अणु
		pscr |= DISABLE_AUTO_NEG_SPEED_GMII;
		अगर (speed == SPEED_1000)
			pscr |= SET_GMII_SPEED_TO_1000;
		अन्यथा अगर (speed == SPEED_100)
			pscr |= SET_MII_SPEED_TO_100;

		pscr |= DISABLE_AUTO_NEG_FOR_FLOW_CTRL;

		pscr |= DISABLE_AUTO_NEG_FOR_DUPLEX;
		अगर (duplex == DUPLEX_FULL)
			pscr |= SET_FULL_DUPLEX_MODE;
	पूर्ण

	wrlp(mp, PORT_SERIAL_CONTROL, pscr);
पूर्ण

अटल स्थिर काष्ठा net_device_ops mv643xx_eth_netdev_ops = अणु
	.nकरो_खोलो		= mv643xx_eth_खोलो,
	.nकरो_stop		= mv643xx_eth_stop,
	.nकरो_start_xmit		= mv643xx_eth_xmit,
	.nकरो_set_rx_mode	= mv643xx_eth_set_rx_mode,
	.nकरो_set_mac_address	= mv643xx_eth_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= mv643xx_eth_ioctl,
	.nकरो_change_mtu		= mv643xx_eth_change_mtu,
	.nकरो_set_features	= mv643xx_eth_set_features,
	.nकरो_tx_समयout		= mv643xx_eth_tx_समयout,
	.nकरो_get_stats		= mv643xx_eth_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= mv643xx_eth_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mv643xx_eth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv643xx_eth_platक्रमm_data *pd;
	काष्ठा mv643xx_eth_निजी *mp;
	काष्ठा net_device *dev;
	काष्ठा phy_device *phydev = शून्य;
	काष्ठा resource *res;
	पूर्णांक err;

	pd = dev_get_platdata(&pdev->dev);
	अगर (pd == शून्य) अणु
		dev_err(&pdev->dev, "no mv643xx_eth_platform_data\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pd->shared == शून्य) अणु
		dev_err(&pdev->dev, "no mv643xx_eth_platform_data->shared\n");
		वापस -ENODEV;
	पूर्ण

	dev = alloc_etherdev_mq(माप(काष्ठा mv643xx_eth_निजी), 8);
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	mp = netdev_priv(dev);
	platक्रमm_set_drvdata(pdev, mp);

	mp->shared = platक्रमm_get_drvdata(pd->shared);
	mp->base = mp->shared->base + 0x0400 + (pd->port_number << 10);
	mp->port_num = pd->port_number;

	mp->dev = dev;

	/* Kirkwood resets some रेजिस्टरs on gated घड़ीs. Especially
	 * CLK125_BYPASS_EN must be cleared but is not available on
	 * all other SoCs/System Controllers using this driver.
	 */
	अगर (of_device_is_compatible(pdev->dev.of_node,
				    "marvell,kirkwood-eth-port"))
		wrlp(mp, PORT_SERIAL_CONTROL1,
		     rdlp(mp, PORT_SERIAL_CONTROL1) & ~CLK125_BYPASS_EN);

	/*
	 * Start with a शेष rate, and अगर there is a घड़ी, allow
	 * it to override the शेष.
	 */
	mp->t_clk = 133000000;
	mp->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (!IS_ERR(mp->clk)) अणु
		clk_prepare_enable(mp->clk);
		mp->t_clk = clk_get_rate(mp->clk);
	पूर्ण अन्यथा अगर (!IS_ERR(mp->shared->clk)) अणु
		mp->t_clk = clk_get_rate(mp->shared->clk);
	पूर्ण

	set_params(mp, pd);
	netअगर_set_real_num_tx_queues(dev, mp->txq_count);
	netअगर_set_real_num_rx_queues(dev, mp->rxq_count);

	err = 0;
	अगर (pd->phy_node) अणु
		phydev = of_phy_connect(mp->dev, pd->phy_node,
					mv643xx_eth_adjust_link, 0,
					get_phy_mode(mp));
		अगर (!phydev)
			err = -ENODEV;
		अन्यथा
			phy_addr_set(mp, phydev->mdio.addr);
	पूर्ण अन्यथा अगर (pd->phy_addr != MV643XX_ETH_PHY_NONE) अणु
		phydev = phy_scan(mp, pd->phy_addr);

		अगर (IS_ERR(phydev))
			err = PTR_ERR(phydev);
		अन्यथा
			phy_init(mp, pd->speed, pd->duplex);
	पूर्ण
	अगर (err == -ENODEV) अणु
		err = -EPROBE_DEFER;
		जाओ out;
	पूर्ण
	अगर (err)
		जाओ out;

	dev->ethtool_ops = &mv643xx_eth_ethtool_ops;

	init_pscr(mp, pd->speed, pd->duplex);


	mib_counters_clear(mp);

	समयr_setup(&mp->mib_counters_समयr, mib_counters_समयr_wrapper, 0);
	mp->mib_counters_समयr.expires = jअगरfies + 30 * HZ;

	spin_lock_init(&mp->mib_counters_lock);

	INIT_WORK(&mp->tx_समयout_task, tx_समयout_task);

	netअगर_napi_add(dev, &mp->napi, mv643xx_eth_poll, NAPI_POLL_WEIGHT);

	समयr_setup(&mp->rx_oom, oom_समयr_wrapper, 0);


	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	BUG_ON(!res);
	dev->irq = res->start;

	dev->netdev_ops = &mv643xx_eth_netdev_ops;

	dev->watchकरोg_समयo = 2 * HZ;
	dev->base_addr = 0;

	dev->features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO;
	dev->vlan_features = dev->features;

	dev->features |= NETIF_F_RXCSUM;
	dev->hw_features = dev->features;

	dev->priv_flags |= IFF_UNICAST_FLT;
	dev->gso_max_segs = MV643XX_MAX_TSO_SEGS;

	/* MTU range: 64 - 9500 */
	dev->min_mtu = 64;
	dev->max_mtu = 9500;

	अगर (mp->shared->win_protect)
		wrl(mp, WINDOW_PROTECT(mp->port_num), mp->shared->win_protect);

	netअगर_carrier_off(dev);

	wrlp(mp, SDMA_CONFIG, PORT_SDMA_CONFIG_DEFAULT_VALUE);

	set_rx_coal(mp, 250);
	set_tx_coal(mp, 0);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out;

	netdev_notice(dev, "port %d with MAC address %pM\n",
		      mp->port_num, dev->dev_addr);

	अगर (mp->tx_desc_sram_size > 0)
		netdev_notice(dev, "configured with sram\n");

	वापस 0;

out:
	अगर (!IS_ERR(mp->clk))
		clk_disable_unprepare(mp->clk);
	मुक्त_netdev(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mv643xx_eth_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = platक्रमm_get_drvdata(pdev);
	काष्ठा net_device *dev = mp->dev;

	unरेजिस्टर_netdev(mp->dev);
	अगर (dev->phydev)
		phy_disconnect(dev->phydev);
	cancel_work_sync(&mp->tx_समयout_task);

	अगर (!IS_ERR(mp->clk))
		clk_disable_unprepare(mp->clk);

	मुक्त_netdev(mp->dev);

	वापस 0;
पूर्ण

अटल व्योम mv643xx_eth_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv643xx_eth_निजी *mp = platक्रमm_get_drvdata(pdev);

	/* Mask all पूर्णांकerrupts on ethernet port */
	wrlp(mp, INT_MASK, 0);
	rdlp(mp, INT_MASK);

	अगर (netअगर_running(mp->dev))
		port_reset(mp);
पूर्ण

अटल काष्ठा platक्रमm_driver mv643xx_eth_driver = अणु
	.probe		= mv643xx_eth_probe,
	.हटाओ		= mv643xx_eth_हटाओ,
	.shutकरोwn	= mv643xx_eth_shutकरोwn,
	.driver = अणु
		.name	= MV643XX_ETH_NAME,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&mv643xx_eth_shared_driver,
	&mv643xx_eth_driver,
पूर्ण;

अटल पूर्णांक __init mv643xx_eth_init_module(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_init(mv643xx_eth_init_module);

अटल व्योम __निकास mv643xx_eth_cleanup_module(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(mv643xx_eth_cleanup_module);

MODULE_AUTHOR("Rabeeh Khoury, Assaf Hoffman, Matthew Dharm, "
	      "Manish Lachwani, Dale Farnsworth and Lennert Buytenhek");
MODULE_DESCRIPTION("Ethernet driver for Marvell MV643XX");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" MV643XX_ETH_SHARED_NAME);
MODULE_ALIAS("platform:" MV643XX_ETH_NAME);
