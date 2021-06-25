<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2006, 2007 Eugene Konev
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/atomic.h>

#समावेश <यंत्र/mach-ar7/ar7.h>

MODULE_AUTHOR("Eugene Konev <ejka@imfi.kspu.ru>");
MODULE_DESCRIPTION("TI AR7 ethernet driver (CPMAC)");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:cpmac");

अटल पूर्णांक debug_level = 8;
अटल पूर्णांक dumb_चयन;

/* Next 2 are only used in cpmac_probe, so it's poपूर्णांकless to change them */
module_param(debug_level, पूर्णांक, 0444);
module_param(dumb_चयन, पूर्णांक, 0444);

MODULE_PARM_DESC(debug_level, "Number of NETIF_MSG bits to enable");
MODULE_PARM_DESC(dumb_चयन, "Assume switch is not connected to MDIO bus");

#घोषणा CPMAC_VERSION "0.5.2"
/* frame size + 802.1q tag + FCS size */
#घोषणा CPMAC_SKB_SIZE		(ETH_FRAME_LEN + ETH_FCS_LEN + VLAN_HLEN)
#घोषणा CPMAC_QUEUES	8

/* Ethernet रेजिस्टरs */
#घोषणा CPMAC_TX_CONTROL		0x0004
#घोषणा CPMAC_TX_TEARDOWN		0x0008
#घोषणा CPMAC_RX_CONTROL		0x0014
#घोषणा CPMAC_RX_TEARDOWN		0x0018
#घोषणा CPMAC_MBP			0x0100
#घोषणा MBP_RXPASSCRC			0x40000000
#घोषणा MBP_RXQOS			0x20000000
#घोषणा MBP_RXNOCHAIN			0x10000000
#घोषणा MBP_RXCMF			0x01000000
#घोषणा MBP_RXSHORT			0x00800000
#घोषणा MBP_RXCEF			0x00400000
#घोषणा MBP_RXPROMISC			0x00200000
#घोषणा MBP_PROMISCCHAN(channel)	(((channel) & 0x7) << 16)
#घोषणा MBP_RXBCAST			0x00002000
#घोषणा MBP_BCASTCHAN(channel)		(((channel) & 0x7) << 8)
#घोषणा MBP_RXMCAST			0x00000020
#घोषणा MBP_MCASTCHAN(channel)		((channel) & 0x7)
#घोषणा CPMAC_UNICAST_ENABLE		0x0104
#घोषणा CPMAC_UNICAST_CLEAR		0x0108
#घोषणा CPMAC_MAX_LENGTH		0x010c
#घोषणा CPMAC_BUFFER_OFFSET		0x0110
#घोषणा CPMAC_MAC_CONTROL		0x0160
#घोषणा MAC_TXPTYPE			0x00000200
#घोषणा MAC_TXPACE			0x00000040
#घोषणा MAC_MII				0x00000020
#घोषणा MAC_TXFLOW			0x00000010
#घोषणा MAC_RXFLOW			0x00000008
#घोषणा MAC_MTEST			0x00000004
#घोषणा MAC_LOOPBACK			0x00000002
#घोषणा MAC_FDX				0x00000001
#घोषणा CPMAC_MAC_STATUS		0x0164
#घोषणा MAC_STATUS_QOS			0x00000004
#घोषणा MAC_STATUS_RXFLOW		0x00000002
#घोषणा MAC_STATUS_TXFLOW		0x00000001
#घोषणा CPMAC_TX_INT_ENABLE		0x0178
#घोषणा CPMAC_TX_INT_CLEAR		0x017c
#घोषणा CPMAC_MAC_INT_VECTOR		0x0180
#घोषणा MAC_INT_STATUS			0x00080000
#घोषणा MAC_INT_HOST			0x00040000
#घोषणा MAC_INT_RX			0x00020000
#घोषणा MAC_INT_TX			0x00010000
#घोषणा CPMAC_MAC_EOI_VECTOR		0x0184
#घोषणा CPMAC_RX_INT_ENABLE		0x0198
#घोषणा CPMAC_RX_INT_CLEAR		0x019c
#घोषणा CPMAC_MAC_INT_ENABLE		0x01a8
#घोषणा CPMAC_MAC_INT_CLEAR		0x01ac
#घोषणा CPMAC_MAC_ADDR_LO(channel)	(0x01b0 + (channel) * 4)
#घोषणा CPMAC_MAC_ADDR_MID		0x01d0
#घोषणा CPMAC_MAC_ADDR_HI		0x01d4
#घोषणा CPMAC_MAC_HASH_LO		0x01d8
#घोषणा CPMAC_MAC_HASH_HI		0x01dc
#घोषणा CPMAC_TX_PTR(channel)		(0x0600 + (channel) * 4)
#घोषणा CPMAC_RX_PTR(channel)		(0x0620 + (channel) * 4)
#घोषणा CPMAC_TX_ACK(channel)		(0x0640 + (channel) * 4)
#घोषणा CPMAC_RX_ACK(channel)		(0x0660 + (channel) * 4)
#घोषणा CPMAC_REG_END			0x0680

/* Rx/Tx statistics
 * TODO: use some of them to fill stats in cpmac_stats()
 */
#घोषणा CPMAC_STATS_RX_GOOD		0x0200
#घोषणा CPMAC_STATS_RX_BCAST		0x0204
#घोषणा CPMAC_STATS_RX_MCAST		0x0208
#घोषणा CPMAC_STATS_RX_PAUSE		0x020c
#घोषणा CPMAC_STATS_RX_CRC		0x0210
#घोषणा CPMAC_STATS_RX_ALIGN		0x0214
#घोषणा CPMAC_STATS_RX_OVER		0x0218
#घोषणा CPMAC_STATS_RX_JABBER		0x021c
#घोषणा CPMAC_STATS_RX_UNDER		0x0220
#घोषणा CPMAC_STATS_RX_FRAG		0x0224
#घोषणा CPMAC_STATS_RX_FILTER		0x0228
#घोषणा CPMAC_STATS_RX_QOSFILTER	0x022c
#घोषणा CPMAC_STATS_RX_OCTETS		0x0230

#घोषणा CPMAC_STATS_TX_GOOD		0x0234
#घोषणा CPMAC_STATS_TX_BCAST		0x0238
#घोषणा CPMAC_STATS_TX_MCAST		0x023c
#घोषणा CPMAC_STATS_TX_PAUSE		0x0240
#घोषणा CPMAC_STATS_TX_DEFER		0x0244
#घोषणा CPMAC_STATS_TX_COLLISION	0x0248
#घोषणा CPMAC_STATS_TX_SINGLECOLL	0x024c
#घोषणा CPMAC_STATS_TX_MULTICOLL	0x0250
#घोषणा CPMAC_STATS_TX_EXCESSCOLL	0x0254
#घोषणा CPMAC_STATS_TX_LATECOLL		0x0258
#घोषणा CPMAC_STATS_TX_UNDERRUN		0x025c
#घोषणा CPMAC_STATS_TX_CARRIERSENSE	0x0260
#घोषणा CPMAC_STATS_TX_OCTETS		0x0264

#घोषणा cpmac_पढ़ो(base, reg)		(पढ़ोl((व्योम __iomem *)(base) + (reg)))
#घोषणा cpmac_ग_लिखो(base, reg, val)	(ग_लिखोl(val, (व्योम __iomem *)(base) + \
						(reg)))

/* MDIO bus */
#घोषणा CPMAC_MDIO_VERSION		0x0000
#घोषणा CPMAC_MDIO_CONTROL		0x0004
#घोषणा MDIOC_IDLE			0x80000000
#घोषणा MDIOC_ENABLE			0x40000000
#घोषणा MDIOC_PREAMBLE			0x00100000
#घोषणा MDIOC_FAULT			0x00080000
#घोषणा MDIOC_FAULTDETECT		0x00040000
#घोषणा MDIOC_INTTEST			0x00020000
#घोषणा MDIOC_CLKDIV(भाग)		((भाग) & 0xff)
#घोषणा CPMAC_MDIO_ALIVE		0x0008
#घोषणा CPMAC_MDIO_LINK			0x000c
#घोषणा CPMAC_MDIO_ACCESS(channel)	(0x0080 + (channel) * 8)
#घोषणा MDIO_BUSY			0x80000000
#घोषणा MDIO_WRITE			0x40000000
#घोषणा MDIO_REG(reg)			(((reg) & 0x1f) << 21)
#घोषणा MDIO_PHY(phy)			(((phy) & 0x1f) << 16)
#घोषणा MDIO_DATA(data)			((data) & 0xffff)
#घोषणा CPMAC_MDIO_PHYSEL(channel)	(0x0084 + (channel) * 8)
#घोषणा PHYSEL_LINKSEL			0x00000040
#घोषणा PHYSEL_LINKINT			0x00000020

काष्ठा cpmac_desc अणु
	u32 hw_next;
	u32 hw_data;
	u16 buflen;
	u16 bufflags;
	u16 datalen;
	u16 dataflags;
#घोषणा CPMAC_SOP			0x8000
#घोषणा CPMAC_EOP			0x4000
#घोषणा CPMAC_OWN			0x2000
#घोषणा CPMAC_EOQ			0x1000
	काष्ठा sk_buff *skb;
	काष्ठा cpmac_desc *next;
	काष्ठा cpmac_desc *prev;
	dma_addr_t mapping;
	dma_addr_t data_mapping;
पूर्ण;

काष्ठा cpmac_priv अणु
	spinlock_t lock;
	spinlock_t rx_lock;
	काष्ठा cpmac_desc *rx_head;
	पूर्णांक ring_size;
	काष्ठा cpmac_desc *desc_ring;
	dma_addr_t dma_ring;
	व्योम __iomem *regs;
	काष्ठा mii_bus *mii_bus;
	अक्षर phy_name[MII_BUS_ID_SIZE + 3];
	पूर्णांक oldlink, oldspeed, oldduplex;
	u32 msg_enable;
	काष्ठा net_device *dev;
	काष्ठा work_काष्ठा reset_work;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा napi_काष्ठा napi;
	atomic_t reset_pending;
पूर्ण;

अटल irqवापस_t cpmac_irq(पूर्णांक, व्योम *);
अटल व्योम cpmac_hw_start(काष्ठा net_device *dev);
अटल व्योम cpmac_hw_stop(काष्ठा net_device *dev);
अटल पूर्णांक cpmac_stop(काष्ठा net_device *dev);
अटल पूर्णांक cpmac_खोलो(काष्ठा net_device *dev);

अटल व्योम cpmac_dump_regs(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	क्रम (i = 0; i < CPMAC_REG_END; i += 4) अणु
		अगर (i % 16 == 0) अणु
			अगर (i)
				prपूर्णांकk("\n");
			prपूर्णांकk("%s: reg[%p]:", dev->name, priv->regs + i);
		पूर्ण
		prपूर्णांकk(" %08x", cpmac_पढ़ो(priv->regs, i));
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम cpmac_dump_desc(काष्ठा net_device *dev, काष्ठा cpmac_desc *desc)
अणु
	पूर्णांक i;

	prपूर्णांकk("%s: desc[%p]:", dev->name, desc);
	क्रम (i = 0; i < माप(*desc) / 4; i++)
		prपूर्णांकk(" %08x", ((u32 *)desc)[i]);
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम cpmac_dump_all_desc(काष्ठा net_device *dev)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	काष्ठा cpmac_desc *dump = priv->rx_head;

	करो अणु
		cpmac_dump_desc(dev, dump);
		dump = dump->next;
	पूर्ण जबतक (dump != priv->rx_head);
पूर्ण

अटल व्योम cpmac_dump_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;

	prपूर्णांकk("%s: skb 0x%p, len=%d\n", dev->name, skb, skb->len);
	क्रम (i = 0; i < skb->len; i++) अणु
		अगर (i % 16 == 0) अणु
			अगर (i)
				prपूर्णांकk("\n");
			prपूर्णांकk("%s: data[%p]:", dev->name, skb->data + i);
		पूर्ण
		prपूर्णांकk(" %02x", ((u8 *)skb->data)[i]);
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल पूर्णांक cpmac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	u32 val;

	जबतक (cpmac_पढ़ो(bus->priv, CPMAC_MDIO_ACCESS(0)) & MDIO_BUSY)
		cpu_relax();
	cpmac_ग_लिखो(bus->priv, CPMAC_MDIO_ACCESS(0), MDIO_BUSY | MDIO_REG(reg) |
		    MDIO_PHY(phy_id));
	जबतक ((val = cpmac_पढ़ो(bus->priv, CPMAC_MDIO_ACCESS(0))) & MDIO_BUSY)
		cpu_relax();

	वापस MDIO_DATA(val);
पूर्ण

अटल पूर्णांक cpmac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id,
			    पूर्णांक reg, u16 val)
अणु
	जबतक (cpmac_पढ़ो(bus->priv, CPMAC_MDIO_ACCESS(0)) & MDIO_BUSY)
		cpu_relax();
	cpmac_ग_लिखो(bus->priv, CPMAC_MDIO_ACCESS(0), MDIO_BUSY | MDIO_WRITE |
		    MDIO_REG(reg) | MDIO_PHY(phy_id) | MDIO_DATA(val));

	वापस 0;
पूर्ण

अटल पूर्णांक cpmac_mdio_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा clk *cpmac_clk;

	cpmac_clk = clk_get(&bus->dev, "cpmac");
	अगर (IS_ERR(cpmac_clk)) अणु
		pr_err("unable to get cpmac clock\n");
		वापस -1;
	पूर्ण
	ar7_device_reset(AR7_RESET_BIT_MDIO);
	cpmac_ग_लिखो(bus->priv, CPMAC_MDIO_CONTROL, MDIOC_ENABLE |
		    MDIOC_CLKDIV(clk_get_rate(cpmac_clk) / 2200000 - 1));

	वापस 0;
पूर्ण

अटल काष्ठा mii_bus *cpmac_mii;

अटल व्योम cpmac_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	u8 पंचांगp;
	u32 mbp, bit, hash[2] = अणु 0, पूर्ण;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	mbp = cpmac_पढ़ो(priv->regs, CPMAC_MBP);
	अगर (dev->flags & IFF_PROMISC) अणु
		cpmac_ग_लिखो(priv->regs, CPMAC_MBP, (mbp & ~MBP_PROMISCCHAN(0)) |
			    MBP_RXPROMISC);
	पूर्ण अन्यथा अणु
		cpmac_ग_लिखो(priv->regs, CPMAC_MBP, mbp & ~MBP_RXPROMISC);
		अगर (dev->flags & IFF_ALLMULTI) अणु
			/* enable all multicast mode */
			cpmac_ग_लिखो(priv->regs, CPMAC_MAC_HASH_LO, 0xffffffff);
			cpmac_ग_लिखो(priv->regs, CPMAC_MAC_HASH_HI, 0xffffffff);
		पूर्ण अन्यथा अणु
			/* cpmac uses some strange mac address hashing
			 * (not crc32)
			 */
			netdev_क्रम_each_mc_addr(ha, dev) अणु
				bit = 0;
				पंचांगp = ha->addr[0];
				bit  ^= (पंचांगp >> 2) ^ (पंचांगp << 4);
				पंचांगp = ha->addr[1];
				bit  ^= (पंचांगp >> 4) ^ (पंचांगp << 2);
				पंचांगp = ha->addr[2];
				bit  ^= (पंचांगp >> 6) ^ पंचांगp;
				पंचांगp = ha->addr[3];
				bit  ^= (पंचांगp >> 2) ^ (पंचांगp << 4);
				पंचांगp = ha->addr[4];
				bit  ^= (पंचांगp >> 4) ^ (पंचांगp << 2);
				पंचांगp = ha->addr[5];
				bit  ^= (पंचांगp >> 6) ^ पंचांगp;
				bit &= 0x3f;
				hash[bit / 32] |= 1 << (bit % 32);
			पूर्ण

			cpmac_ग_लिखो(priv->regs, CPMAC_MAC_HASH_LO, hash[0]);
			cpmac_ग_लिखो(priv->regs, CPMAC_MAC_HASH_HI, hash[1]);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *cpmac_rx_one(काष्ठा cpmac_priv *priv,
				    काष्ठा cpmac_desc *desc)
अणु
	काष्ठा sk_buff *skb, *result = शून्य;

	अगर (unlikely(netअगर_msg_hw(priv)))
		cpmac_dump_desc(priv->dev, desc);
	cpmac_ग_लिखो(priv->regs, CPMAC_RX_ACK(0), (u32)desc->mapping);
	अगर (unlikely(!desc->datalen)) अणु
		अगर (netअगर_msg_rx_err(priv) && net_ratelimit())
			netdev_warn(priv->dev, "rx: spurious interrupt\n");

		वापस शून्य;
	पूर्ण

	skb = netdev_alloc_skb_ip_align(priv->dev, CPMAC_SKB_SIZE);
	अगर (likely(skb)) अणु
		skb_put(desc->skb, desc->datalen);
		desc->skb->protocol = eth_type_trans(desc->skb, priv->dev);
		skb_checksum_none_निश्चित(desc->skb);
		priv->dev->stats.rx_packets++;
		priv->dev->stats.rx_bytes += desc->datalen;
		result = desc->skb;
		dma_unmap_single(&priv->dev->dev, desc->data_mapping,
				 CPMAC_SKB_SIZE, DMA_FROM_DEVICE);
		desc->skb = skb;
		desc->data_mapping = dma_map_single(&priv->dev->dev, skb->data,
						    CPMAC_SKB_SIZE,
						    DMA_FROM_DEVICE);
		desc->hw_data = (u32)desc->data_mapping;
		अगर (unlikely(netअगर_msg_pktdata(priv))) अणु
			netdev_dbg(priv->dev, "received packet:\n");
			cpmac_dump_skb(priv->dev, result);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_rx_err(priv) && net_ratelimit())
			netdev_warn(priv->dev,
				    "low on skbs, dropping packet\n");

		priv->dev->stats.rx_dropped++;
	पूर्ण

	desc->buflen = CPMAC_SKB_SIZE;
	desc->dataflags = CPMAC_OWN;

	वापस result;
पूर्ण

अटल पूर्णांक cpmac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpmac_desc *desc, *restart;
	काष्ठा cpmac_priv *priv = container_of(napi, काष्ठा cpmac_priv, napi);
	पूर्णांक received = 0, processed = 0;

	spin_lock(&priv->rx_lock);
	अगर (unlikely(!priv->rx_head)) अणु
		अगर (netअगर_msg_rx_err(priv) && net_ratelimit())
			netdev_warn(priv->dev, "rx: polling, but no queue\n");

		spin_unlock(&priv->rx_lock);
		napi_complete(napi);
		वापस 0;
	पूर्ण

	desc = priv->rx_head;
	restart = शून्य;
	जबतक (((desc->dataflags & CPMAC_OWN) == 0) && (received < budget)) अणु
		processed++;

		अगर ((desc->dataflags & CPMAC_EOQ) != 0) अणु
			/* The last update to eoq->hw_next didn't happen
			 * soon enough, and the receiver stopped here.
			 * Remember this descriptor so we can restart
			 * the receiver after मुक्तing some space.
			 */
			अगर (unlikely(restart)) अणु
				अगर (netअगर_msg_rx_err(priv))
					netdev_err(priv->dev, "poll found a"
						   " duplicate EOQ: %p and %p\n",
						   restart, desc);
				जाओ fatal_error;
			पूर्ण

			restart = desc->next;
		पूर्ण

		skb = cpmac_rx_one(priv, desc);
		अगर (likely(skb)) अणु
			netअगर_receive_skb(skb);
			received++;
		पूर्ण
		desc = desc->next;
	पूर्ण

	अगर (desc != priv->rx_head) अणु
		/* We मुक्तd some buffers, but not the whole ring,
		 * add what we did मुक्त to the rx list
		 */
		desc->prev->hw_next = (u32)0;
		priv->rx_head->prev->hw_next = priv->rx_head->mapping;
	पूर्ण

	/* Optimization: If we did not actually process an EOQ (perhaps because
	 * of quota limits), check to see अगर the tail of the queue has EOQ set.
	 * We should immediately restart in that हाल so that the receiver can
	 * restart and run in parallel with more packet processing.
	 * This lets us handle slightly larger bursts beक्रमe running
	 * out of ring space (assuming dev->weight < ring_size)
	 */

	अगर (!restart &&
	     (priv->rx_head->prev->dataflags & (CPMAC_OWN|CPMAC_EOQ))
		    == CPMAC_EOQ &&
	     (priv->rx_head->dataflags & CPMAC_OWN) != 0) अणु
		/* reset EOQ so the poll loop (above) करोesn't try to
		 * restart this when it eventually माला_लो to this descriptor.
		 */
		priv->rx_head->prev->dataflags &= ~CPMAC_EOQ;
		restart = priv->rx_head;
	पूर्ण

	अगर (restart) अणु
		priv->dev->stats.rx_errors++;
		priv->dev->stats.rx_fअगरo_errors++;
		अगर (netअगर_msg_rx_err(priv) && net_ratelimit())
			netdev_warn(priv->dev, "rx dma ring overrun\n");

		अगर (unlikely((restart->dataflags & CPMAC_OWN) == 0)) अणु
			अगर (netअगर_msg_drv(priv))
				netdev_err(priv->dev, "cpmac_poll is trying "
					"to restart rx from a descriptor "
					"that's not free: %p\n", restart);
			जाओ fatal_error;
		पूर्ण

		cpmac_ग_लिखो(priv->regs, CPMAC_RX_PTR(0), restart->mapping);
	पूर्ण

	priv->rx_head = desc;
	spin_unlock(&priv->rx_lock);
	अगर (unlikely(netअगर_msg_rx_status(priv)))
		netdev_dbg(priv->dev, "poll processed %d packets\n", received);

	अगर (processed == 0) अणु
		/* we ran out of packets to पढ़ो,
		 * revert to पूर्णांकerrupt-driven mode
		 */
		napi_complete(napi);
		cpmac_ग_लिखो(priv->regs, CPMAC_RX_INT_ENABLE, 1);
		वापस 0;
	पूर्ण

	वापस 1;

fatal_error:
	/* Something went horribly wrong.
	 * Reset hardware to try to recover rather than wedging.
	 */
	अगर (netअगर_msg_drv(priv)) अणु
		netdev_err(priv->dev, "cpmac_poll is confused. "
			   "Resetting hardware\n");
		cpmac_dump_all_desc(priv->dev);
		netdev_dbg(priv->dev, "RX_PTR(0)=0x%08x RX_ACK(0)=0x%08x\n",
			   cpmac_पढ़ो(priv->regs, CPMAC_RX_PTR(0)),
			   cpmac_पढ़ो(priv->regs, CPMAC_RX_ACK(0)));
	पूर्ण

	spin_unlock(&priv->rx_lock);
	napi_complete(napi);
	netअगर_tx_stop_all_queues(priv->dev);
	napi_disable(&priv->napi);

	atomic_inc(&priv->reset_pending);
	cpmac_hw_stop(priv->dev);
	अगर (!schedule_work(&priv->reset_work))
		atomic_dec(&priv->reset_pending);

	वापस 0;

पूर्ण

अटल netdev_tx_t cpmac_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक queue;
	अचिन्हित पूर्णांक len;
	काष्ठा cpmac_desc *desc;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	अगर (unlikely(atomic_पढ़ो(&priv->reset_pending)))
		वापस NETDEV_TX_BUSY;

	अगर (unlikely(skb_padto(skb, ETH_ZLEN)))
		वापस NETDEV_TX_OK;

	len = max_t(अचिन्हित पूर्णांक, skb->len, ETH_ZLEN);
	queue = skb_get_queue_mapping(skb);
	netअगर_stop_subqueue(dev, queue);

	desc = &priv->desc_ring[queue];
	अगर (unlikely(desc->dataflags & CPMAC_OWN)) अणु
		अगर (netअगर_msg_tx_err(priv) && net_ratelimit())
			netdev_warn(dev, "tx dma ring full\n");

		वापस NETDEV_TX_BUSY;
	पूर्ण

	spin_lock(&priv->lock);
	spin_unlock(&priv->lock);
	desc->dataflags = CPMAC_SOP | CPMAC_EOP | CPMAC_OWN;
	desc->skb = skb;
	desc->data_mapping = dma_map_single(&dev->dev, skb->data, len,
					    DMA_TO_DEVICE);
	desc->hw_data = (u32)desc->data_mapping;
	desc->datalen = len;
	desc->buflen = len;
	अगर (unlikely(netअगर_msg_tx_queued(priv)))
		netdev_dbg(dev, "sending 0x%p, len=%d\n", skb, skb->len);
	अगर (unlikely(netअगर_msg_hw(priv)))
		cpmac_dump_desc(dev, desc);
	अगर (unlikely(netअगर_msg_pktdata(priv)))
		cpmac_dump_skb(dev, skb);
	cpmac_ग_लिखो(priv->regs, CPMAC_TX_PTR(queue), (u32)desc->mapping);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम cpmac_end_xmit(काष्ठा net_device *dev, पूर्णांक queue)
अणु
	काष्ठा cpmac_desc *desc;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	desc = &priv->desc_ring[queue];
	cpmac_ग_लिखो(priv->regs, CPMAC_TX_ACK(queue), (u32)desc->mapping);
	अगर (likely(desc->skb)) अणु
		spin_lock(&priv->lock);
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += desc->skb->len;
		spin_unlock(&priv->lock);
		dma_unmap_single(&dev->dev, desc->data_mapping, desc->skb->len,
				 DMA_TO_DEVICE);

		अगर (unlikely(netअगर_msg_tx_करोne(priv)))
			netdev_dbg(dev, "sent 0x%p, len=%d\n",
				   desc->skb, desc->skb->len);

		dev_consume_skb_irq(desc->skb);
		desc->skb = शून्य;
		अगर (__netअगर_subqueue_stopped(dev, queue))
			netअगर_wake_subqueue(dev, queue);
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_tx_err(priv) && net_ratelimit())
			netdev_warn(dev, "end_xmit: spurious interrupt\n");
		अगर (__netअगर_subqueue_stopped(dev, queue))
			netअगर_wake_subqueue(dev, queue);
	पूर्ण
पूर्ण

अटल व्योम cpmac_hw_stop(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	काष्ठा plat_cpmac_data *pdata = dev_get_platdata(&priv->pdev->dev);

	ar7_device_reset(pdata->reset_bit);
	cpmac_ग_लिखो(priv->regs, CPMAC_RX_CONTROL,
		    cpmac_पढ़ो(priv->regs, CPMAC_RX_CONTROL) & ~1);
	cpmac_ग_लिखो(priv->regs, CPMAC_TX_CONTROL,
		    cpmac_पढ़ो(priv->regs, CPMAC_TX_CONTROL) & ~1);
	क्रम (i = 0; i < 8; i++) अणु
		cpmac_ग_लिखो(priv->regs, CPMAC_TX_PTR(i), 0);
		cpmac_ग_लिखो(priv->regs, CPMAC_RX_PTR(i), 0);
	पूर्ण
	cpmac_ग_लिखो(priv->regs, CPMAC_UNICAST_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_RX_INT_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_TX_INT_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_INT_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_CONTROL,
		    cpmac_पढ़ो(priv->regs, CPMAC_MAC_CONTROL) & ~MAC_MII);
पूर्ण

अटल व्योम cpmac_hw_start(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	काष्ठा plat_cpmac_data *pdata = dev_get_platdata(&priv->pdev->dev);

	ar7_device_reset(pdata->reset_bit);
	क्रम (i = 0; i < 8; i++) अणु
		cpmac_ग_लिखो(priv->regs, CPMAC_TX_PTR(i), 0);
		cpmac_ग_लिखो(priv->regs, CPMAC_RX_PTR(i), 0);
	पूर्ण
	cpmac_ग_लिखो(priv->regs, CPMAC_RX_PTR(0), priv->rx_head->mapping);

	cpmac_ग_लिखो(priv->regs, CPMAC_MBP, MBP_RXSHORT | MBP_RXBCAST |
		    MBP_RXMCAST);
	cpmac_ग_लिखो(priv->regs, CPMAC_BUFFER_OFFSET, 0);
	क्रम (i = 0; i < 8; i++)
		cpmac_ग_लिखो(priv->regs, CPMAC_MAC_ADDR_LO(i), dev->dev_addr[5]);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_ADDR_MID, dev->dev_addr[4]);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_ADDR_HI, dev->dev_addr[0] |
		    (dev->dev_addr[1] << 8) | (dev->dev_addr[2] << 16) |
		    (dev->dev_addr[3] << 24));
	cpmac_ग_लिखो(priv->regs, CPMAC_MAX_LENGTH, CPMAC_SKB_SIZE);
	cpmac_ग_लिखो(priv->regs, CPMAC_UNICAST_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_RX_INT_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_TX_INT_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_INT_CLEAR, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_UNICAST_ENABLE, 1);
	cpmac_ग_लिखो(priv->regs, CPMAC_RX_INT_ENABLE, 1);
	cpmac_ग_लिखो(priv->regs, CPMAC_TX_INT_ENABLE, 0xff);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_INT_ENABLE, 3);

	cpmac_ग_लिखो(priv->regs, CPMAC_RX_CONTROL,
		    cpmac_पढ़ो(priv->regs, CPMAC_RX_CONTROL) | 1);
	cpmac_ग_लिखो(priv->regs, CPMAC_TX_CONTROL,
		    cpmac_पढ़ो(priv->regs, CPMAC_TX_CONTROL) | 1);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_CONTROL,
		    cpmac_पढ़ो(priv->regs, CPMAC_MAC_CONTROL) | MAC_MII |
		    MAC_FDX);
पूर्ण

अटल व्योम cpmac_clear_rx(काष्ठा net_device *dev)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	काष्ठा cpmac_desc *desc;
	पूर्णांक i;

	अगर (unlikely(!priv->rx_head))
		वापस;
	desc = priv->rx_head;
	क्रम (i = 0; i < priv->ring_size; i++) अणु
		अगर ((desc->dataflags & CPMAC_OWN) == 0) अणु
			अगर (netअगर_msg_rx_err(priv) && net_ratelimit())
				netdev_warn(dev, "packet dropped\n");
			अगर (unlikely(netअगर_msg_hw(priv)))
				cpmac_dump_desc(dev, desc);
			desc->dataflags = CPMAC_OWN;
			dev->stats.rx_dropped++;
		पूर्ण
		desc->hw_next = desc->next->mapping;
		desc = desc->next;
	पूर्ण
	priv->rx_head->prev->hw_next = 0;
पूर्ण

अटल व्योम cpmac_clear_tx(काष्ठा net_device *dev)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	अगर (unlikely(!priv->desc_ring))
		वापस;
	क्रम (i = 0; i < CPMAC_QUEUES; i++) अणु
		priv->desc_ring[i].dataflags = 0;
		अगर (priv->desc_ring[i].skb) अणु
			dev_kमुक्त_skb_any(priv->desc_ring[i].skb);
			priv->desc_ring[i].skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cpmac_hw_error(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpmac_priv *priv =
		container_of(work, काष्ठा cpmac_priv, reset_work);

	spin_lock(&priv->rx_lock);
	cpmac_clear_rx(priv->dev);
	spin_unlock(&priv->rx_lock);
	cpmac_clear_tx(priv->dev);
	cpmac_hw_start(priv->dev);
	barrier();
	atomic_dec(&priv->reset_pending);

	netअगर_tx_wake_all_queues(priv->dev);
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_INT_ENABLE, 3);
पूर्ण

अटल व्योम cpmac_check_status(काष्ठा net_device *dev)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	u32 macstatus = cpmac_पढ़ो(priv->regs, CPMAC_MAC_STATUS);
	पूर्णांक rx_channel = (macstatus >> 8) & 7;
	पूर्णांक rx_code = (macstatus >> 12) & 15;
	पूर्णांक tx_channel = (macstatus >> 16) & 7;
	पूर्णांक tx_code = (macstatus >> 20) & 15;

	अगर (rx_code || tx_code) अणु
		अगर (netअगर_msg_drv(priv) && net_ratelimit()) अणु
			/* Can't find any करोcumentation on what these
			 * error codes actually are. So just log them and hope..
			 */
			अगर (rx_code)
				netdev_warn(dev, "host error %d on rx "
					"channel %d (macstatus %08x), resetting\n",
					rx_code, rx_channel, macstatus);
			अगर (tx_code)
				netdev_warn(dev, "host error %d on tx "
					"channel %d (macstatus %08x), resetting\n",
					tx_code, tx_channel, macstatus);
		पूर्ण

		netअगर_tx_stop_all_queues(dev);
		cpmac_hw_stop(dev);
		अगर (schedule_work(&priv->reset_work))
			atomic_inc(&priv->reset_pending);
		अगर (unlikely(netअगर_msg_hw(priv)))
			cpmac_dump_regs(dev);
	पूर्ण
	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_INT_CLEAR, 0xff);
पूर्ण

अटल irqवापस_t cpmac_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा cpmac_priv *priv;
	पूर्णांक queue;
	u32 status;

	priv = netdev_priv(dev);

	status = cpmac_पढ़ो(priv->regs, CPMAC_MAC_INT_VECTOR);

	अगर (unlikely(netअगर_msg_पूर्णांकr(priv)))
		netdev_dbg(dev, "interrupt status: 0x%08x\n", status);

	अगर (status & MAC_INT_TX)
		cpmac_end_xmit(dev, (status & 7));

	अगर (status & MAC_INT_RX) अणु
		queue = (status >> 8) & 7;
		अगर (napi_schedule_prep(&priv->napi)) अणु
			cpmac_ग_लिखो(priv->regs, CPMAC_RX_INT_CLEAR, 1 << queue);
			__napi_schedule(&priv->napi);
		पूर्ण
	पूर्ण

	cpmac_ग_लिखो(priv->regs, CPMAC_MAC_EOI_VECTOR, 0);

	अगर (unlikely(status & (MAC_INT_HOST | MAC_INT_STATUS)))
		cpmac_check_status(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cpmac_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	spin_lock(&priv->lock);
	dev->stats.tx_errors++;
	spin_unlock(&priv->lock);
	अगर (netअगर_msg_tx_err(priv) && net_ratelimit())
		netdev_warn(dev, "transmit timeout\n");

	atomic_inc(&priv->reset_pending);
	barrier();
	cpmac_clear_tx(dev);
	barrier();
	atomic_dec(&priv->reset_pending);

	netअगर_tx_wake_all_queues(priv->dev);
पूर्ण

अटल व्योम cpmac_get_ringparam(काष्ठा net_device *dev,
						काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	ring->rx_max_pending = 1024;
	ring->rx_mini_max_pending = 1;
	ring->rx_jumbo_max_pending = 1;
	ring->tx_max_pending = 1;

	ring->rx_pending = priv->ring_size;
	ring->rx_mini_pending = 1;
	ring->rx_jumbo_pending = 1;
	ring->tx_pending = 1;
पूर्ण

अटल पूर्णांक cpmac_set_ringparam(काष्ठा net_device *dev,
						काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);

	अगर (netअगर_running(dev))
		वापस -EBUSY;
	priv->ring_size = ring->rx_pending;

	वापस 0;
पूर्ण

अटल व्योम cpmac_get_drvinfo(काष्ठा net_device *dev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "cpmac", माप(info->driver));
	strlcpy(info->version, CPMAC_VERSION, माप(info->version));
	snम_लिखो(info->bus_info, माप(info->bus_info), "%s", "cpmac");
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cpmac_ethtool_ops = अणु
	.get_drvinfo = cpmac_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_ringparam = cpmac_get_ringparam,
	.set_ringparam = cpmac_set_ringparam,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल व्योम cpmac_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	पूर्णांक new_state = 0;

	spin_lock(&priv->lock);
	अगर (dev->phydev->link) अणु
		netअगर_tx_start_all_queues(dev);
		अगर (dev->phydev->duplex != priv->oldduplex) अणु
			new_state = 1;
			priv->oldduplex = dev->phydev->duplex;
		पूर्ण

		अगर (dev->phydev->speed != priv->oldspeed) अणु
			new_state = 1;
			priv->oldspeed = dev->phydev->speed;
		पूर्ण

		अगर (!priv->oldlink) अणु
			new_state = 1;
			priv->oldlink = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (priv->oldlink) अणु
		new_state = 1;
		priv->oldlink = 0;
		priv->oldspeed = 0;
		priv->oldduplex = -1;
	पूर्ण

	अगर (new_state && netअगर_msg_link(priv) && net_ratelimit())
		phy_prपूर्णांक_status(dev->phydev);

	spin_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक cpmac_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक i, size, res;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	काष्ठा resource *mem;
	काष्ठा cpmac_desc *desc;
	काष्ठा sk_buff *skb;

	mem = platक्रमm_get_resource_byname(priv->pdev, IORESOURCE_MEM, "regs");
	अगर (!request_mem_region(mem->start, resource_size(mem), dev->name)) अणु
		अगर (netअगर_msg_drv(priv))
			netdev_err(dev, "failed to request registers\n");

		res = -ENXIO;
		जाओ fail_reserve;
	पूर्ण

	priv->regs = ioremap(mem->start, resource_size(mem));
	अगर (!priv->regs) अणु
		अगर (netअगर_msg_drv(priv))
			netdev_err(dev, "failed to remap registers\n");

		res = -ENXIO;
		जाओ fail_remap;
	पूर्ण

	size = priv->ring_size + CPMAC_QUEUES;
	priv->desc_ring = dma_alloc_coherent(&dev->dev,
					     माप(काष्ठा cpmac_desc) * size,
					     &priv->dma_ring,
					     GFP_KERNEL);
	अगर (!priv->desc_ring) अणु
		res = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	क्रम (i = 0; i < size; i++)
		priv->desc_ring[i].mapping = priv->dma_ring + माप(*desc) * i;

	priv->rx_head = &priv->desc_ring[CPMAC_QUEUES];
	क्रम (i = 0, desc = priv->rx_head; i < priv->ring_size; i++, desc++) अणु
		skb = netdev_alloc_skb_ip_align(dev, CPMAC_SKB_SIZE);
		अगर (unlikely(!skb)) अणु
			res = -ENOMEM;
			जाओ fail_desc;
		पूर्ण
		desc->skb = skb;
		desc->data_mapping = dma_map_single(&dev->dev, skb->data,
						    CPMAC_SKB_SIZE,
						    DMA_FROM_DEVICE);
		desc->hw_data = (u32)desc->data_mapping;
		desc->buflen = CPMAC_SKB_SIZE;
		desc->dataflags = CPMAC_OWN;
		desc->next = &priv->rx_head[(i + 1) % priv->ring_size];
		desc->next->prev = desc;
		desc->hw_next = (u32)desc->next->mapping;
	पूर्ण

	priv->rx_head->prev->hw_next = (u32)0;

	res = request_irq(dev->irq, cpmac_irq, IRQF_SHARED, dev->name, dev);
	अगर (res) अणु
		अगर (netअगर_msg_drv(priv))
			netdev_err(dev, "failed to obtain irq\n");

		जाओ fail_irq;
	पूर्ण

	atomic_set(&priv->reset_pending, 0);
	INIT_WORK(&priv->reset_work, cpmac_hw_error);
	cpmac_hw_start(dev);

	napi_enable(&priv->napi);
	phy_start(dev->phydev);

	वापस 0;

fail_irq:
fail_desc:
	क्रम (i = 0; i < priv->ring_size; i++) अणु
		अगर (priv->rx_head[i].skb) अणु
			dma_unmap_single(&dev->dev,
					 priv->rx_head[i].data_mapping,
					 CPMAC_SKB_SIZE,
					 DMA_FROM_DEVICE);
			kमुक्त_skb(priv->rx_head[i].skb);
		पूर्ण
	पूर्ण
	dma_मुक्त_coherent(&dev->dev, माप(काष्ठा cpmac_desc) * size,
			  priv->desc_ring, priv->dma_ring);

fail_alloc:
	iounmap(priv->regs);

fail_remap:
	release_mem_region(mem->start, resource_size(mem));

fail_reserve:
	वापस res;
पूर्ण

अटल पूर्णांक cpmac_stop(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा cpmac_priv *priv = netdev_priv(dev);
	काष्ठा resource *mem;

	netअगर_tx_stop_all_queues(dev);

	cancel_work_sync(&priv->reset_work);
	napi_disable(&priv->napi);
	phy_stop(dev->phydev);

	cpmac_hw_stop(dev);

	क्रम (i = 0; i < 8; i++)
		cpmac_ग_लिखो(priv->regs, CPMAC_TX_PTR(i), 0);
	cpmac_ग_लिखो(priv->regs, CPMAC_RX_PTR(0), 0);
	cpmac_ग_लिखो(priv->regs, CPMAC_MBP, 0);

	मुक्त_irq(dev->irq, dev);
	iounmap(priv->regs);
	mem = platक्रमm_get_resource_byname(priv->pdev, IORESOURCE_MEM, "regs");
	release_mem_region(mem->start, resource_size(mem));
	priv->rx_head = &priv->desc_ring[CPMAC_QUEUES];
	क्रम (i = 0; i < priv->ring_size; i++) अणु
		अगर (priv->rx_head[i].skb) अणु
			dma_unmap_single(&dev->dev,
					 priv->rx_head[i].data_mapping,
					 CPMAC_SKB_SIZE,
					 DMA_FROM_DEVICE);
			kमुक्त_skb(priv->rx_head[i].skb);
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(&dev->dev, माप(काष्ठा cpmac_desc) *
			  (CPMAC_QUEUES + priv->ring_size),
			  priv->desc_ring, priv->dma_ring);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops cpmac_netdev_ops = अणु
	.nकरो_खोलो		= cpmac_खोलो,
	.nकरो_stop		= cpmac_stop,
	.nकरो_start_xmit		= cpmac_start_xmit,
	.nकरो_tx_समयout		= cpmac_tx_समयout,
	.nकरो_set_rx_mode	= cpmac_set_multicast_list,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक बाह्यal_चयन;

अटल पूर्णांक cpmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc, phy_id;
	अक्षर mdio_bus_id[MII_BUS_ID_SIZE];
	काष्ठा resource *mem;
	काष्ठा cpmac_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा plat_cpmac_data *pdata;
	काष्ठा phy_device *phydev = शून्य;

	pdata = dev_get_platdata(&pdev->dev);

	अगर (बाह्यal_चयन || dumb_चयन) अणु
		म_नकलन(mdio_bus_id, "fixed-0", MII_BUS_ID_SIZE); /* fixed phys bus */
		phy_id = pdev->id;
	पूर्ण अन्यथा अणु
		क्रम (phy_id = 0; phy_id < PHY_MAX_ADDR; phy_id++) अणु
			अगर (!(pdata->phy_mask & (1 << phy_id)))
				जारी;
			अगर (!mdiobus_get_phy(cpmac_mii, phy_id))
				जारी;
			म_नकलन(mdio_bus_id, cpmac_mii->id, MII_BUS_ID_SIZE);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (phy_id == PHY_MAX_ADDR) अणु
		dev_err(&pdev->dev, "no PHY present, falling back "
			"to switch on MDIO bus 0\n");
		म_नकलन(mdio_bus_id, "fixed-0", MII_BUS_ID_SIZE); /* fixed phys bus */
		phy_id = pdev->id;
	पूर्ण
	mdio_bus_id[माप(mdio_bus_id) - 1] = '\0';

	dev = alloc_etherdev_mq(माप(*priv), CPMAC_QUEUES);
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	platक्रमm_set_drvdata(pdev, dev);
	priv = netdev_priv(dev);

	priv->pdev = pdev;
	mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	अगर (!mem) अणु
		rc = -ENODEV;
		जाओ fail;
	पूर्ण

	dev->irq = platक्रमm_get_irq_byname(pdev, "irq");

	dev->netdev_ops = &cpmac_netdev_ops;
	dev->ethtool_ops = &cpmac_ethtool_ops;

	netअगर_napi_add(dev, &priv->napi, cpmac_poll, 64);

	spin_lock_init(&priv->lock);
	spin_lock_init(&priv->rx_lock);
	priv->dev = dev;
	priv->ring_size = 64;
	priv->msg_enable = netअगर_msg_init(debug_level, 0xff);
	स_नकल(dev->dev_addr, pdata->dev_addr, माप(pdata->dev_addr));

	snम_लिखो(priv->phy_name, MII_BUS_ID_SIZE, PHY_ID_FMT,
						mdio_bus_id, phy_id);

	phydev = phy_connect(dev, priv->phy_name, cpmac_adjust_link,
			     PHY_INTERFACE_MODE_MII);

	अगर (IS_ERR(phydev)) अणु
		अगर (netअगर_msg_drv(priv))
			dev_err(&pdev->dev, "Could not attach to PHY\n");

		rc = PTR_ERR(phydev);
		जाओ fail;
	पूर्ण

	rc = रेजिस्टर_netdev(dev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Could not register net device\n");
		जाओ fail;
	पूर्ण

	अगर (netअगर_msg_probe(priv)) अणु
		dev_info(&pdev->dev, "regs: %p, irq: %d, phy: %s, "
			 "mac: %pM\n", (व्योम *)mem->start, dev->irq,
			 priv->phy_name, dev->dev_addr);
	पूर्ण

	वापस 0;

fail:
	मुक्त_netdev(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक cpmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpmac_driver = अणु
	.driver = अणु
		.name 	= "cpmac",
	पूर्ण,
	.probe 	= cpmac_probe,
	.हटाओ = cpmac_हटाओ,
पूर्ण;

पूर्णांक cpmac_init(व्योम)
अणु
	u32 mask;
	पूर्णांक i, res;

	cpmac_mii = mdiobus_alloc();
	अगर (cpmac_mii == शून्य)
		वापस -ENOMEM;

	cpmac_mii->name = "cpmac-mii";
	cpmac_mii->पढ़ो = cpmac_mdio_पढ़ो;
	cpmac_mii->ग_लिखो = cpmac_mdio_ग_लिखो;
	cpmac_mii->reset = cpmac_mdio_reset;

	cpmac_mii->priv = ioremap(AR7_REGS_MDIO, 256);

	अगर (!cpmac_mii->priv) अणु
		pr_err("Can't ioremap mdio registers\n");
		res = -ENXIO;
		जाओ fail_alloc;
	पूर्ण

	/* FIXME: unhardcode gpio&reset bits */
	ar7_gpio_disable(26);
	ar7_gpio_disable(27);
	ar7_device_reset(AR7_RESET_BIT_CPMAC_LO);
	ar7_device_reset(AR7_RESET_BIT_CPMAC_HI);
	ar7_device_reset(AR7_RESET_BIT_EPHY);

	cpmac_mii->reset(cpmac_mii);

	क्रम (i = 0; i < 300; i++) अणु
		mask = cpmac_पढ़ो(cpmac_mii->priv, CPMAC_MDIO_ALIVE);
		अगर (mask)
			अवरोध;
		अन्यथा
			msleep(10);
	पूर्ण

	mask &= 0x7fffffff;
	अगर (mask & (mask - 1)) अणु
		बाह्यal_चयन = 1;
		mask = 0;
	पूर्ण

	cpmac_mii->phy_mask = ~(mask | 0x80000000);
	snम_लिखो(cpmac_mii->id, MII_BUS_ID_SIZE, "cpmac-1");

	res = mdiobus_रेजिस्टर(cpmac_mii);
	अगर (res)
		जाओ fail_mii;

	res = platक्रमm_driver_रेजिस्टर(&cpmac_driver);
	अगर (res)
		जाओ fail_cpmac;

	वापस 0;

fail_cpmac:
	mdiobus_unरेजिस्टर(cpmac_mii);

fail_mii:
	iounmap(cpmac_mii->priv);

fail_alloc:
	mdiobus_मुक्त(cpmac_mii);

	वापस res;
पूर्ण

व्योम cpmac_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cpmac_driver);
	mdiobus_unरेजिस्टर(cpmac_mii);
	iounmap(cpmac_mii->priv);
	mdiobus_मुक्त(cpmac_mii);
पूर्ण

module_init(cpmac_init);
module_निकास(cpmac_निकास);
