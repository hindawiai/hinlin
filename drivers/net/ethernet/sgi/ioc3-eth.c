<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Driver क्रम SGI's IOC3 based Ethernet cards as found in the PCI card.
 *
 * Copyright (C) 1999, 2000, 01, 03, 06 Ralf Baechle
 * Copyright (C) 1995, 1999, 2000, 2001 by Silicon Graphics, Inc.
 *
 * References:
 *  o IOC3 ASIC specअगरication 4.51, 1996-04-18
 *  o IEEE 802.3 specअगरication, 2000 edition
 *  o DP38840A Specअगरication, National Semiconductor, March 1997
 *
 * To करो:
 *
 *  o Use prefetching क्रम large packets.  What is a good lower limit क्रम
 *    prefetching?
 *  o Use hardware checksums.
 *  o Which PHYs might possibly be attached to the IOC3 in real live,
 *    which workarounds are required क्रम them?  Do we ever have Lucent's?
 *  o For the 2.5 branch समाप्त the mii-tool ioctls.
 */

#घोषणा IOC3_NAME	"ioc3-eth"
#घोषणा IOC3_VERSION	"2.6.3-4"

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/crc16.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/in.h>
#समावेश <linux/पन.स>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/gfp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/nvmem-consumer.h>

#समावेश <net/ip.h>

#समावेश <यंत्र/sn/ioc3.h>
#समावेश <यंत्र/pci/bridge.h>

#घोषणा CRC16_INIT	0
#घोषणा CRC16_VALID	0xb001

/* Number of RX buffers.  This is tunable in the range of 16 <= x < 512.
 * The value must be a घातer of two.
 */
#घोषणा RX_BUFFS		64
#घोषणा RX_RING_ENTRIES		512		/* fixed in hardware */
#घोषणा RX_RING_MASK		(RX_RING_ENTRIES - 1)
#घोषणा RX_RING_SIZE		(RX_RING_ENTRIES * माप(u64))

/* 128 TX buffers (not tunable) */
#घोषणा TX_RING_ENTRIES		128
#घोषणा TX_RING_MASK		(TX_RING_ENTRIES - 1)
#घोषणा TX_RING_SIZE		(TX_RING_ENTRIES * माप(काष्ठा ioc3_etxd))

/* IOC3 करोes dma transfers in 128 byte blocks */
#घोषणा IOC3_DMA_XFER_LEN	128UL

/* Every RX buffer starts with 8 byte descriptor data */
#घोषणा RX_OFFSET		(माप(काष्ठा ioc3_erxbuf) + NET_IP_ALIGN)
#घोषणा RX_BUF_SIZE		(13 * IOC3_DMA_XFER_LEN)

#घोषणा ETCSR_FD   ((21 << ETCSR_IPGR2_SHIFT) | (21 << ETCSR_IPGR1_SHIFT) | 21)
#घोषणा ETCSR_HD   ((17 << ETCSR_IPGR2_SHIFT) | (11 << ETCSR_IPGR1_SHIFT) | 21)

/* Private per NIC data of the driver.  */
काष्ठा ioc3_निजी अणु
	काष्ठा ioc3_ethregs *regs;
	काष्ठा device *dma_dev;
	u32 *ssram;
	अचिन्हित दीर्घ *rxr;		/* poपूर्णांकer to receiver ring */
	व्योम *tx_ring;
	काष्ठा ioc3_etxd *txr;
	dma_addr_t rxr_dma;
	dma_addr_t txr_dma;
	काष्ठा sk_buff *rx_skbs[RX_RING_ENTRIES];
	काष्ठा sk_buff *tx_skbs[TX_RING_ENTRIES];
	पूर्णांक rx_ci;			/* RX consumer index */
	पूर्णांक rx_pi;			/* RX producer index */
	पूर्णांक tx_ci;			/* TX consumer index */
	पूर्णांक tx_pi;			/* TX producer index */
	पूर्णांक txqlen;
	u32 emcr, ehar_h, ehar_l;
	spinlock_t ioc3_lock;
	काष्ठा mii_अगर_info mii;

	/* Members used by स्वतःnegotiation  */
	काष्ठा समयr_list ioc3_समयr;
पूर्ण;

अटल पूर्णांक ioc3_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल व्योम ioc3_set_multicast_list(काष्ठा net_device *dev);
अटल netdev_tx_t ioc3_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम ioc3_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल अंतरभूत अचिन्हित पूर्णांक ioc3_hash(स्थिर अचिन्हित अक्षर *addr);
अटल व्योम ioc3_start(काष्ठा ioc3_निजी *ip);
अटल अंतरभूत व्योम ioc3_stop(काष्ठा ioc3_निजी *ip);
अटल व्योम ioc3_init(काष्ठा net_device *dev);
अटल पूर्णांक ioc3_alloc_rx_bufs(काष्ठा net_device *dev);
अटल व्योम ioc3_मुक्त_rx_bufs(काष्ठा ioc3_निजी *ip);
अटल अंतरभूत व्योम ioc3_clean_tx_ring(काष्ठा ioc3_निजी *ip);

अटल स्थिर काष्ठा ethtool_ops ioc3_ethtool_ops;

अटल अंतरभूत अचिन्हित दीर्घ aligned_rx_skb_addr(अचिन्हित दीर्घ addr)
अणु
	वापस (~addr + 1) & (IOC3_DMA_XFER_LEN - 1UL);
पूर्ण

अटल अंतरभूत पूर्णांक ioc3_alloc_skb(काष्ठा ioc3_निजी *ip, काष्ठा sk_buff **skb,
				 काष्ठा ioc3_erxbuf **rxb, dma_addr_t *rxb_dma)
अणु
	काष्ठा sk_buff *new_skb;
	dma_addr_t d;
	पूर्णांक offset;

	new_skb = alloc_skb(RX_BUF_SIZE + IOC3_DMA_XFER_LEN - 1, GFP_ATOMIC);
	अगर (!new_skb)
		वापस -ENOMEM;

	/* ensure buffer is aligned to IOC3_DMA_XFER_LEN */
	offset = aligned_rx_skb_addr((अचिन्हित दीर्घ)new_skb->data);
	अगर (offset)
		skb_reserve(new_skb, offset);

	d = dma_map_single(ip->dma_dev, new_skb->data,
			   RX_BUF_SIZE, DMA_FROM_DEVICE);

	अगर (dma_mapping_error(ip->dma_dev, d)) अणु
		dev_kमुक्त_skb_any(new_skb);
		वापस -ENOMEM;
	पूर्ण
	*rxb_dma = d;
	*rxb = (काष्ठा ioc3_erxbuf *)new_skb->data;
	skb_reserve(new_skb, RX_OFFSET);
	*skb = new_skb;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI_XTALK_BRIDGE
अटल अंतरभूत अचिन्हित दीर्घ ioc3_map(dma_addr_t addr, अचिन्हित दीर्घ attr)
अणु
	वापस (addr & ~PCI64_ATTR_BAR) | attr;
पूर्ण

#घोषणा ERBAR_VAL	(ERBAR_BARRIER_BIT << ERBAR_RXBARR_SHIFT)
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ ioc3_map(dma_addr_t addr, अचिन्हित दीर्घ attr)
अणु
	वापस addr;
पूर्ण

#घोषणा ERBAR_VAL	0
#पूर्ण_अगर

अटल पूर्णांक ioc3eth_nvmem_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर अक्षर *name = dev_name(dev);
	स्थिर अक्षर *prefix = data;
	पूर्णांक prefix_len;

	prefix_len = म_माप(prefix);
	अगर (म_माप(name) < (prefix_len + 3))
		वापस 0;

	अगर (स_भेद(prefix, name, prefix_len) != 0)
		वापस 0;

	/* found nvmem device which is attached to our ioc3
	 * now check क्रम one wire family code 09, 89 and 91
	 */
	अगर (स_भेद(name + prefix_len, "09-", 3) == 0)
		वापस 1;
	अगर (स_भेद(name + prefix_len, "89-", 3) == 0)
		वापस 1;
	अगर (स_भेद(name + prefix_len, "91-", 3) == 0)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ioc3eth_get_mac_addr(काष्ठा resource *res, u8 mac_addr[6])
अणु
	काष्ठा nvmem_device *nvmem;
	अक्षर prefix[24];
	u8 prom[16];
	पूर्णांक ret;
	पूर्णांक i;

	snम_लिखो(prefix, माप(prefix), "ioc3-%012llx-",
		 res->start & ~0xffff);

	nvmem = nvmem_device_find(prefix, ioc3eth_nvmem_match);
	अगर (IS_ERR(nvmem))
		वापस PTR_ERR(nvmem);

	ret = nvmem_device_पढ़ो(nvmem, 0, 16, prom);
	nvmem_device_put(nvmem);
	अगर (ret < 0)
		वापस ret;

	/* check, अगर content is valid */
	अगर (prom[0] != 0x0a ||
	    crc16(CRC16_INIT, prom, 13) != CRC16_VALID)
		वापस -EINVAL;

	क्रम (i = 0; i < 6; i++)
		mac_addr[i] = prom[10 - i];

	वापस 0;
पूर्ण

अटल व्योम __ioc3_set_mac_address(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);

	ग_लिखोl((dev->dev_addr[5] <<  8) |
	       dev->dev_addr[4],
	       &ip->regs->emar_h);
	ग_लिखोl((dev->dev_addr[3] << 24) |
	       (dev->dev_addr[2] << 16) |
	       (dev->dev_addr[1] <<  8) |
	       dev->dev_addr[0],
	       &ip->regs->emar_l);
पूर्ण

अटल पूर्णांक ioc3_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा sockaddr *sa = addr;

	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);

	spin_lock_irq(&ip->ioc3_lock);
	__ioc3_set_mac_address(dev);
	spin_unlock_irq(&ip->ioc3_lock);

	वापस 0;
पूर्ण

/* Caller must hold the ioc3_lock ever क्रम MII पढ़ोers.  This is also
 * used to protect the transmitter side but it's low contention.
 */
अटल पूर्णांक ioc3_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_ethregs *regs = ip->regs;

	जबतक (पढ़ोl(&regs->micr) & MICR_BUSY)
		;
	ग_लिखोl((phy << MICR_PHYADDR_SHIFT) | reg | MICR_READTRIG,
	       &regs->micr);
	जबतक (पढ़ोl(&regs->micr) & MICR_BUSY)
		;

	वापस पढ़ोl(&regs->midr_r) & MIDR_DATA_MASK;
पूर्ण

अटल व्योम ioc3_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy, पूर्णांक reg, पूर्णांक data)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_ethregs *regs = ip->regs;

	जबतक (पढ़ोl(&regs->micr) & MICR_BUSY)
		;
	ग_लिखोl(data, &regs->midr_w);
	ग_लिखोl((phy << MICR_PHYADDR_SHIFT) | reg, &regs->micr);
	जबतक (पढ़ोl(&regs->micr) & MICR_BUSY)
		;
पूर्ण

अटल पूर्णांक ioc3_mii_init(काष्ठा ioc3_निजी *ip);

अटल काष्ठा net_device_stats *ioc3_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_ethregs *regs = ip->regs;

	dev->stats.collisions += पढ़ोl(&regs->etcdc) & ETCDC_COLLCNT_MASK;
	वापस &dev->stats;
पूर्ण

अटल व्योम ioc3_tcpudp_checksum(काष्ठा sk_buff *skb, u32 hwsum, पूर्णांक len)
अणु
	काष्ठा ethhdr *eh = eth_hdr(skb);
	अचिन्हित पूर्णांक proto;
	अचिन्हित अक्षर *cp;
	काष्ठा iphdr *ih;
	u32 csum, ehsum;
	u16 *ew;

	/* Did hardware handle the checksum at all?  The हालs we can handle
	 * are:
	 *
	 * - TCP and UDP checksums of IPv4 only.
	 * - IPv6 would be करोable but we keep that क्रम later ...
	 * - Only unfragmented packets.  Did somebody alपढ़ोy tell you
	 *   fragmentation is evil?
	 * - करोn't care about packet size.  Worst हाल when processing a
	 *   malक्रमmed packet we'll try to access the packet at ip header +
	 *   64 bytes which is still inside the skb.  Even in the unlikely
	 *   हाल where the checksum is right the higher layers will still
	 *   drop the packet as appropriate.
	 */
	अगर (eh->h_proto != htons(ETH_P_IP))
		वापस;

	ih = (काष्ठा iphdr *)((अक्षर *)eh + ETH_HLEN);
	अगर (ip_is_fragment(ih))
		वापस;

	proto = ih->protocol;
	अगर (proto != IPPROTO_TCP && proto != IPPROTO_UDP)
		वापस;

	/* Same as tx - compute csum of pseuकरो header  */
	csum = hwsum +
	       (ih->tot_len - (ih->ihl << 2)) +
	       htons((u16)ih->protocol) +
	       (ih->saddr >> 16) + (ih->saddr & 0xffff) +
	       (ih->daddr >> 16) + (ih->daddr & 0xffff);

	/* Sum up ethernet dest addr, src addr and protocol  */
	ew = (u16 *)eh;
	ehsum = ew[0] + ew[1] + ew[2] + ew[3] + ew[4] + ew[5] + ew[6];

	ehsum = (ehsum & 0xffff) + (ehsum >> 16);
	ehsum = (ehsum & 0xffff) + (ehsum >> 16);

	csum += 0xffff ^ ehsum;

	/* In the next step we also subtract the 1's complement
	 * checksum of the trailing ethernet CRC.
	 */
	cp = (अक्षर *)eh + len;	/* poपूर्णांकs at trailing CRC */
	अगर (len & 1) अणु
		csum += 0xffff ^ (u16)((cp[1] << 8) | cp[0]);
		csum += 0xffff ^ (u16)((cp[3] << 8) | cp[2]);
	पूर्ण अन्यथा अणु
		csum += 0xffff ^ (u16)((cp[0] << 8) | cp[1]);
		csum += 0xffff ^ (u16)((cp[2] << 8) | cp[3]);
	पूर्ण

	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);

	अगर (csum == 0xffff)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल अंतरभूत व्योम ioc3_rx(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा sk_buff *skb, *new_skb;
	पूर्णांक rx_entry, n_entry, len;
	काष्ठा ioc3_erxbuf *rxb;
	अचिन्हित दीर्घ *rxr;
	dma_addr_t d;
	u32 w0, err;

	rxr = ip->rxr;		/* Ring base */
	rx_entry = ip->rx_ci;				/* RX consume index */
	n_entry = ip->rx_pi;

	skb = ip->rx_skbs[rx_entry];
	rxb = (काष्ठा ioc3_erxbuf *)(skb->data - RX_OFFSET);
	w0 = be32_to_cpu(rxb->w0);

	जबतक (w0 & ERXBUF_V) अणु
		err = be32_to_cpu(rxb->err);		/* It's valid ...  */
		अगर (err & ERXBUF_GOODPKT) अणु
			len = ((w0 >> ERXBUF_BYTECNT_SHIFT) & 0x7ff) - 4;
			skb_put(skb, len);
			skb->protocol = eth_type_trans(skb, dev);

			अगर (ioc3_alloc_skb(ip, &new_skb, &rxb, &d)) अणु
				/* Ouch, drop packet and just recycle packet
				 * to keep the ring filled.
				 */
				dev->stats.rx_dropped++;
				new_skb = skb;
				d = rxr[rx_entry];
				जाओ next;
			पूर्ण

			अगर (likely(dev->features & NETIF_F_RXCSUM))
				ioc3_tcpudp_checksum(skb,
						     w0 & ERXBUF_IPCKSUM_MASK,
						     len);

			dma_unmap_single(ip->dma_dev, rxr[rx_entry],
					 RX_BUF_SIZE, DMA_FROM_DEVICE);

			netअगर_rx(skb);

			ip->rx_skbs[rx_entry] = शून्य;	/* Poison  */

			dev->stats.rx_packets++;		/* Statistics */
			dev->stats.rx_bytes += len;
		पूर्ण अन्यथा अणु
			/* The frame is invalid and the skb never
			 * reached the network layer so we can just
			 * recycle it.
			 */
			new_skb = skb;
			d = rxr[rx_entry];
			dev->stats.rx_errors++;
		पूर्ण
		अगर (err & ERXBUF_CRCERR)	/* Statistics */
			dev->stats.rx_crc_errors++;
		अगर (err & ERXBUF_FRAMERR)
			dev->stats.rx_frame_errors++;

next:
		ip->rx_skbs[n_entry] = new_skb;
		rxr[n_entry] = cpu_to_be64(ioc3_map(d, PCI64_ATTR_BAR));
		rxb->w0 = 0;				/* Clear valid flag */
		n_entry = (n_entry + 1) & RX_RING_MASK;	/* Update erpir */

		/* Now go on to the next ring entry.  */
		rx_entry = (rx_entry + 1) & RX_RING_MASK;
		skb = ip->rx_skbs[rx_entry];
		rxb = (काष्ठा ioc3_erxbuf *)(skb->data - RX_OFFSET);
		w0 = be32_to_cpu(rxb->w0);
	पूर्ण
	ग_लिखोl((n_entry << 3) | ERPIR_ARM, &ip->regs->erpir);
	ip->rx_pi = n_entry;
	ip->rx_ci = rx_entry;
पूर्ण

अटल अंतरभूत व्योम ioc3_tx(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_ethregs *regs = ip->regs;
	अचिन्हित दीर्घ packets, bytes;
	पूर्णांक tx_entry, o_entry;
	काष्ठा sk_buff *skb;
	u32 etcir;

	spin_lock(&ip->ioc3_lock);
	etcir = पढ़ोl(&regs->etcir);

	tx_entry = (etcir >> 7) & TX_RING_MASK;
	o_entry = ip->tx_ci;
	packets = 0;
	bytes = 0;

	जबतक (o_entry != tx_entry) अणु
		packets++;
		skb = ip->tx_skbs[o_entry];
		bytes += skb->len;
		dev_consume_skb_irq(skb);
		ip->tx_skbs[o_entry] = शून्य;

		o_entry = (o_entry + 1) & TX_RING_MASK;	/* Next */

		etcir = पढ़ोl(&regs->etcir);		/* More pkts sent?  */
		tx_entry = (etcir >> 7) & TX_RING_MASK;
	पूर्ण

	dev->stats.tx_packets += packets;
	dev->stats.tx_bytes += bytes;
	ip->txqlen -= packets;

	अगर (netअगर_queue_stopped(dev) && ip->txqlen < TX_RING_ENTRIES)
		netअगर_wake_queue(dev);

	ip->tx_ci = o_entry;
	spin_unlock(&ip->ioc3_lock);
पूर्ण

/* Deal with fatal IOC3 errors.  This condition might be caused by a hard or
 * software problems, so we should try to recover
 * more gracefully अगर this ever happens.  In theory we might be flooded
 * with such error पूर्णांकerrupts अगर something really goes wrong, so we might
 * also consider to take the पूर्णांकerface करोwn.
 */
अटल व्योम ioc3_error(काष्ठा net_device *dev, u32 eisr)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);

	spin_lock(&ip->ioc3_lock);

	अगर (eisr & EISR_RXOFLO)
		net_err_ratelimited("%s: RX overflow.\n", dev->name);
	अगर (eisr & EISR_RXBUFOFLO)
		net_err_ratelimited("%s: RX buffer overflow.\n", dev->name);
	अगर (eisr & EISR_RXMEMERR)
		net_err_ratelimited("%s: RX PCI error.\n", dev->name);
	अगर (eisr & EISR_RXPARERR)
		net_err_ratelimited("%s: RX SSRAM parity error.\n", dev->name);
	अगर (eisr & EISR_TXBUFUFLO)
		net_err_ratelimited("%s: TX buffer underflow.\n", dev->name);
	अगर (eisr & EISR_TXMEMERR)
		net_err_ratelimited("%s: TX PCI error.\n", dev->name);

	ioc3_stop(ip);
	ioc3_मुक्त_rx_bufs(ip);
	ioc3_clean_tx_ring(ip);

	ioc3_init(dev);
	अगर (ioc3_alloc_rx_bufs(dev)) अणु
		netdev_err(dev, "%s: rx buffer allocation failed\n", __func__);
		spin_unlock(&ip->ioc3_lock);
		वापस;
	पूर्ण
	ioc3_start(ip);
	ioc3_mii_init(ip);

	netअगर_wake_queue(dev);

	spin_unlock(&ip->ioc3_lock);
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
 * after the Tx thपढ़ो.
 */
अटल irqवापस_t ioc3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev_id);
	काष्ठा ioc3_ethregs *regs = ip->regs;
	u32 eisr;

	eisr = पढ़ोl(&regs->eisr);
	ग_लिखोl(eisr, &regs->eisr);
	पढ़ोl(&regs->eisr);				/* Flush */

	अगर (eisr & (EISR_RXOFLO | EISR_RXBUFOFLO | EISR_RXMEMERR |
		    EISR_RXPARERR | EISR_TXBUFUFLO | EISR_TXMEMERR))
		ioc3_error(dev_id, eisr);
	अगर (eisr & EISR_RXTIMERINT)
		ioc3_rx(dev_id);
	अगर (eisr & EISR_TXEXPLICIT)
		ioc3_tx(dev_id);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम ioc3_setup_duplex(काष्ठा ioc3_निजी *ip)
अणु
	काष्ठा ioc3_ethregs *regs = ip->regs;

	spin_lock_irq(&ip->ioc3_lock);

	अगर (ip->mii.full_duplex) अणु
		ग_लिखोl(ETCSR_FD, &regs->etcsr);
		ip->emcr |= EMCR_DUPLEX;
	पूर्ण अन्यथा अणु
		ग_लिखोl(ETCSR_HD, &regs->etcsr);
		ip->emcr &= ~EMCR_DUPLEX;
	पूर्ण
	ग_लिखोl(ip->emcr, &regs->emcr);

	spin_unlock_irq(&ip->ioc3_lock);
पूर्ण

अटल व्योम ioc3_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ioc3_निजी *ip = from_समयr(ip, t, ioc3_समयr);

	/* Prपूर्णांक the link status अगर it has changed */
	mii_check_media(&ip->mii, 1, 0);
	ioc3_setup_duplex(ip);

	ip->ioc3_समयr.expires = jअगरfies + ((12 * HZ) / 10); /* 1.2s */
	add_समयr(&ip->ioc3_समयr);
पूर्ण

/* Try to find a PHY.  There is no apparent relation between the MII addresses
 * in the SGI करोcumentation and what we find in reality, so we simply probe
 * क्रम the PHY.
 */
अटल पूर्णांक ioc3_mii_init(काष्ठा ioc3_निजी *ip)
अणु
	u16 word;
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		word = ioc3_mdio_पढ़ो(ip->mii.dev, i, MII_PHYSID1);

		अगर (word != 0xffff && word != 0x0000) अणु
			ip->mii.phy_id = i;
			वापस 0;
		पूर्ण
	पूर्ण
	ip->mii.phy_id = -1;
	वापस -ENODEV;
पूर्ण

अटल व्योम ioc3_mii_start(काष्ठा ioc3_निजी *ip)
अणु
	ip->ioc3_समयr.expires = jअगरfies + (12 * HZ) / 10;  /* 1.2 sec. */
	add_समयr(&ip->ioc3_समयr);
पूर्ण

अटल अंतरभूत व्योम ioc3_tx_unmap(काष्ठा ioc3_निजी *ip, पूर्णांक entry)
अणु
	काष्ठा ioc3_etxd *desc;
	u32 cmd, bufcnt, len;

	desc = &ip->txr[entry];
	cmd = be32_to_cpu(desc->cmd);
	bufcnt = be32_to_cpu(desc->bufcnt);
	अगर (cmd & ETXD_B1V) अणु
		len = (bufcnt & ETXD_B1CNT_MASK) >> ETXD_B1CNT_SHIFT;
		dma_unmap_single(ip->dma_dev, be64_to_cpu(desc->p1),
				 len, DMA_TO_DEVICE);
	पूर्ण
	अगर (cmd & ETXD_B2V) अणु
		len = (bufcnt & ETXD_B2CNT_MASK) >> ETXD_B2CNT_SHIFT;
		dma_unmap_single(ip->dma_dev, be64_to_cpu(desc->p2),
				 len, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ioc3_clean_tx_ring(काष्ठा ioc3_निजी *ip)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < TX_RING_ENTRIES; i++) अणु
		skb = ip->tx_skbs[i];
		अगर (skb) अणु
			ioc3_tx_unmap(ip, i);
			ip->tx_skbs[i] = शून्य;
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		ip->txr[i].cmd = 0;
	पूर्ण
	ip->tx_pi = 0;
	ip->tx_ci = 0;
पूर्ण

अटल व्योम ioc3_मुक्त_rx_bufs(काष्ठा ioc3_निजी *ip)
अणु
	पूर्णांक rx_entry, n_entry;
	काष्ठा sk_buff *skb;

	n_entry = ip->rx_ci;
	rx_entry = ip->rx_pi;

	जबतक (n_entry != rx_entry) अणु
		skb = ip->rx_skbs[n_entry];
		अगर (skb) अणु
			dma_unmap_single(ip->dma_dev,
					 be64_to_cpu(ip->rxr[n_entry]),
					 RX_BUF_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		n_entry = (n_entry + 1) & RX_RING_MASK;
	पूर्ण
पूर्ण

अटल पूर्णांक ioc3_alloc_rx_bufs(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_erxbuf *rxb;
	dma_addr_t d;
	पूर्णांक i;

	/* Now the rx buffers.  The RX ring may be larger but
	 * we only allocate 16 buffers क्रम now.  Need to tune
	 * this क्रम perक्रमmance and memory later.
	 */
	क्रम (i = 0; i < RX_BUFFS; i++) अणु
		अगर (ioc3_alloc_skb(ip, &ip->rx_skbs[i], &rxb, &d))
			वापस -ENOMEM;

		rxb->w0 = 0;	/* Clear valid flag */
		ip->rxr[i] = cpu_to_be64(ioc3_map(d, PCI64_ATTR_BAR));
	पूर्ण
	ip->rx_ci = 0;
	ip->rx_pi = RX_BUFFS;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ioc3_ssram_disc(काष्ठा ioc3_निजी *ip)
अणु
	काष्ठा ioc3_ethregs *regs = ip->regs;
	u32 *ssram0 = &ip->ssram[0x0000];
	u32 *ssram1 = &ip->ssram[0x4000];
	u32 pattern = 0x5555;

	/* Assume the larger size SSRAM and enable parity checking */
	ग_लिखोl(पढ़ोl(&regs->emcr) | (EMCR_बफ_मान | EMCR_RAMPAR), &regs->emcr);
	पढ़ोl(&regs->emcr); /* Flush */

	ग_लिखोl(pattern, ssram0);
	ग_लिखोl(~pattern & IOC3_SSRAM_DM, ssram1);

	अगर ((पढ़ोl(ssram0) & IOC3_SSRAM_DM) != pattern ||
	    (पढ़ोl(ssram1) & IOC3_SSRAM_DM) != (~pattern & IOC3_SSRAM_DM)) अणु
		/* set ssram size to 64 KB */
		ip->emcr |= EMCR_RAMPAR;
		ग_लिखोl(पढ़ोl(&regs->emcr) & ~EMCR_बफ_मान, &regs->emcr);
	पूर्ण अन्यथा अणु
		ip->emcr |= EMCR_बफ_मान | EMCR_RAMPAR;
	पूर्ण
पूर्ण

अटल व्योम ioc3_init(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_ethregs *regs = ip->regs;

	del_समयr_sync(&ip->ioc3_समयr);	/* Kill अगर running	*/

	ग_लिखोl(EMCR_RST, &regs->emcr);		/* Reset		*/
	पढ़ोl(&regs->emcr);			/* Flush WB		*/
	udelay(4);				/* Give it समय ...	*/
	ग_लिखोl(0, &regs->emcr);
	पढ़ोl(&regs->emcr);

	/* Misc रेजिस्टरs  */
	ग_लिखोl(ERBAR_VAL, &regs->erbar);
	पढ़ोl(&regs->etcdc);			/* Clear on पढ़ो */
	ग_लिखोl(15, &regs->ercsr);		/* RX low watermark  */
	ग_लिखोl(0, &regs->ertr);			/* Interrupt immediately */
	__ioc3_set_mac_address(dev);
	ग_लिखोl(ip->ehar_h, &regs->ehar_h);
	ग_लिखोl(ip->ehar_l, &regs->ehar_l);
	ग_लिखोl(42, &regs->ersr);		/* XXX should be अक्रमom */
पूर्ण

अटल व्योम ioc3_start(काष्ठा ioc3_निजी *ip)
अणु
	काष्ठा ioc3_ethregs *regs = ip->regs;
	अचिन्हित दीर्घ ring;

	/* Now the rx ring base, consume & produce रेजिस्टरs.  */
	ring = ioc3_map(ip->rxr_dma, PCI64_ATTR_PREC);
	ग_लिखोl(ring >> 32, &regs->erbr_h);
	ग_लिखोl(ring & 0xffffffff, &regs->erbr_l);
	ग_लिखोl(ip->rx_ci << 3, &regs->ercir);
	ग_लिखोl((ip->rx_pi << 3) | ERPIR_ARM, &regs->erpir);

	ring = ioc3_map(ip->txr_dma, PCI64_ATTR_PREC);

	ip->txqlen = 0;					/* nothing queued  */

	/* Now the tx ring base, consume & produce रेजिस्टरs.  */
	ग_लिखोl(ring >> 32, &regs->etbr_h);
	ग_लिखोl(ring & 0xffffffff, &regs->etbr_l);
	ग_लिखोl(ip->tx_pi << 7, &regs->etpir);
	ग_लिखोl(ip->tx_ci << 7, &regs->etcir);
	पढ़ोl(&regs->etcir);				/* Flush */

	ip->emcr |= ((RX_OFFSET / 2) << EMCR_RXOFF_SHIFT) | EMCR_TXDMAEN |
		    EMCR_TXEN | EMCR_RXDMAEN | EMCR_RXEN | EMCR_PADEN;
	ग_लिखोl(ip->emcr, &regs->emcr);
	ग_लिखोl(EISR_RXTIMERINT | EISR_RXOFLO | EISR_RXBUFOFLO |
	       EISR_RXMEMERR | EISR_RXPARERR | EISR_TXBUFUFLO |
	       EISR_TXEXPLICIT | EISR_TXMEMERR, &regs->eier);
	पढ़ोl(&regs->eier);
पूर्ण

अटल अंतरभूत व्योम ioc3_stop(काष्ठा ioc3_निजी *ip)
अणु
	काष्ठा ioc3_ethregs *regs = ip->regs;

	ग_लिखोl(0, &regs->emcr);			/* Shutup */
	ग_लिखोl(0, &regs->eier);			/* Disable पूर्णांकerrupts */
	पढ़ोl(&regs->eier);			/* Flush */
पूर्ण

अटल पूर्णांक ioc3_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);

	ip->ehar_h = 0;
	ip->ehar_l = 0;

	ioc3_init(dev);
	अगर (ioc3_alloc_rx_bufs(dev)) अणु
		netdev_err(dev, "%s: rx buffer allocation failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	ioc3_start(ip);
	ioc3_mii_start(ip);

	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक ioc3_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);

	del_समयr_sync(&ip->ioc3_समयr);

	netअगर_stop_queue(dev);

	ioc3_stop(ip);

	ioc3_मुक्त_rx_bufs(ip);
	ioc3_clean_tx_ring(ip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ioc3_netdev_ops = अणु
	.nकरो_खोलो		= ioc3_खोलो,
	.nकरो_stop		= ioc3_बंद,
	.nकरो_start_xmit		= ioc3_start_xmit,
	.nकरो_tx_समयout		= ioc3_समयout,
	.nकरो_get_stats		= ioc3_get_stats,
	.nकरो_set_rx_mode	= ioc3_set_multicast_list,
	.nकरो_करो_ioctl		= ioc3_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= ioc3_set_mac_address,
पूर्ण;

अटल पूर्णांक ioc3eth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 sw_physid1, sw_physid2, venकरोr, model, rev;
	काष्ठा ioc3_निजी *ip;
	काष्ठा net_device *dev;
	काष्ठा resource *regs;
	u8 mac_addr[6];
	पूर्णांक err;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	/* get mac addr from one wire prom */
	अगर (ioc3eth_get_mac_addr(regs, mac_addr))
		वापस -EPROBE_DEFER; /* not available yet */

	dev = alloc_etherdev(माप(काष्ठा ioc3_निजी));
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);

	ip = netdev_priv(dev);
	ip->dma_dev = pdev->dev.parent;
	ip->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ip->regs)) अणु
		err = PTR_ERR(ip->regs);
		जाओ out_मुक्त;
	पूर्ण

	ip->ssram = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(ip->ssram)) अणु
		err = PTR_ERR(ip->ssram);
		जाओ out_मुक्त;
	पूर्ण

	dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dev->irq < 0) अणु
		err = dev->irq;
		जाओ out_मुक्त;
	पूर्ण

	अगर (devm_request_irq(&pdev->dev, dev->irq, ioc3_पूर्णांकerrupt,
			     IRQF_SHARED, "ioc3-eth", dev)) अणु
		dev_err(&pdev->dev, "Can't get irq %d\n", dev->irq);
		err = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	spin_lock_init(&ip->ioc3_lock);
	समयr_setup(&ip->ioc3_समयr, ioc3_समयr, 0);

	ioc3_stop(ip);

	/* Allocate rx ring.  4kb = 512 entries, must be 4kb aligned */
	ip->rxr = dma_alloc_coherent(ip->dma_dev, RX_RING_SIZE, &ip->rxr_dma,
				     GFP_KERNEL);
	अगर (!ip->rxr) अणु
		pr_err("ioc3-eth: rx ring allocation failed\n");
		err = -ENOMEM;
		जाओ out_stop;
	पूर्ण

	/* Allocate tx rings.  16kb = 128 bufs, must be 16kb aligned  */
	ip->tx_ring = dma_alloc_coherent(ip->dma_dev, TX_RING_SIZE + SZ_16K - 1,
					 &ip->txr_dma, GFP_KERNEL);
	अगर (!ip->tx_ring) अणु
		pr_err("ioc3-eth: tx ring allocation failed\n");
		err = -ENOMEM;
		जाओ out_stop;
	पूर्ण
	/* Align TX ring */
	ip->txr = PTR_ALIGN(ip->tx_ring, SZ_16K);
	ip->txr_dma = ALIGN(ip->txr_dma, SZ_16K);

	ioc3_init(dev);

	ip->mii.phy_id_mask = 0x1f;
	ip->mii.reg_num_mask = 0x1f;
	ip->mii.dev = dev;
	ip->mii.mdio_पढ़ो = ioc3_mdio_पढ़ो;
	ip->mii.mdio_ग_लिखो = ioc3_mdio_ग_लिखो;

	ioc3_mii_init(ip);

	अगर (ip->mii.phy_id == -1) अणु
		netdev_err(dev, "Didn't find a PHY, goodbye.\n");
		err = -ENODEV;
		जाओ out_stop;
	पूर्ण

	ioc3_mii_start(ip);
	ioc3_ssram_disc(ip);
	स_नकल(dev->dev_addr, mac_addr, ETH_ALEN);

	/* The IOC3-specअगरic entries in the device काष्ठाure. */
	dev->watchकरोg_समयo	= 5 * HZ;
	dev->netdev_ops		= &ioc3_netdev_ops;
	dev->ethtool_ops	= &ioc3_ethtool_ops;
	dev->hw_features	= NETIF_F_IP_CSUM | NETIF_F_RXCSUM;
	dev->features		= NETIF_F_IP_CSUM | NETIF_F_HIGHDMA;

	sw_physid1 = ioc3_mdio_पढ़ो(dev, ip->mii.phy_id, MII_PHYSID1);
	sw_physid2 = ioc3_mdio_पढ़ो(dev, ip->mii.phy_id, MII_PHYSID2);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out_stop;

	mii_check_media(&ip->mii, 1, 1);
	ioc3_setup_duplex(ip);

	venकरोr = (sw_physid1 << 12) | (sw_physid2 >> 4);
	model  = (sw_physid2 >> 4) & 0x3f;
	rev    = sw_physid2 & 0xf;
	netdev_info(dev, "Using PHY %d, vendor 0x%x, model %d, rev %d.\n",
		    ip->mii.phy_id, venकरोr, model, rev);
	netdev_info(dev, "IOC3 SSRAM has %d kbyte.\n",
		    ip->emcr & EMCR_बफ_मान ? 128 : 64);

	वापस 0;

out_stop:
	del_समयr_sync(&ip->ioc3_समयr);
	अगर (ip->rxr)
		dma_मुक्त_coherent(ip->dma_dev, RX_RING_SIZE, ip->rxr,
				  ip->rxr_dma);
	अगर (ip->tx_ring)
		dma_मुक्त_coherent(ip->dma_dev, TX_RING_SIZE + SZ_16K - 1, ip->tx_ring,
				  ip->txr_dma);
out_मुक्त:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक ioc3eth_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);

	dma_मुक्त_coherent(ip->dma_dev, RX_RING_SIZE, ip->rxr, ip->rxr_dma);
	dma_मुक्त_coherent(ip->dma_dev, TX_RING_SIZE + SZ_16K - 1, ip->tx_ring, ip->txr_dma);

	unरेजिस्टर_netdev(dev);
	del_समयr_sync(&ip->ioc3_समयr);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण


अटल netdev_tx_t ioc3_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_etxd *desc;
	अचिन्हित दीर्घ data;
	अचिन्हित पूर्णांक len;
	पूर्णांक produce;
	u32 w0 = 0;

	/* IOC3 has a fairly simple minded checksumming hardware which simply
	 * adds up the 1's complement checksum क्रम the entire packet and
	 * inserts it at an offset which can be specअगरied in the descriptor
	 * पूर्णांकo the transmit packet.  This means we have to compensate क्रम the
	 * MAC header which should not be summed and the TCP/UDP pseuकरो headers
	 * manually.
	 */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर काष्ठा iphdr *ih = ip_hdr(skb);
		स्थिर पूर्णांक proto = ntohs(ih->protocol);
		अचिन्हित पूर्णांक csoff;
		u32 csum, ehsum;
		u16 *eh;

		/* The MAC header.  skb->mac seem the logic approach
		 * to find the MAC header - except it's a शून्य poपूर्णांकer ...
		 */
		eh = (u16 *)skb->data;

		/* Sum up dest addr, src addr and protocol  */
		ehsum = eh[0] + eh[1] + eh[2] + eh[3] + eh[4] + eh[5] + eh[6];

		/* Skip IP header; it's sum is always zero and was
		 * alपढ़ोy filled in by ip_output.c
		 */
		csum = csum_tcpudp_nofold(ih->saddr, ih->daddr,
					  ih->tot_len - (ih->ihl << 2),
					  proto, csum_fold(ehsum));

		csum = (csum & 0xffff) + (csum >> 16);	/* Fold again */
		csum = (csum & 0xffff) + (csum >> 16);

		csoff = ETH_HLEN + (ih->ihl << 2);
		अगर (proto == IPPROTO_UDP) अणु
			csoff += दुरत्व(काष्ठा udphdr, check);
			udp_hdr(skb)->check = csum;
		पूर्ण
		अगर (proto == IPPROTO_TCP) अणु
			csoff += दुरत्व(काष्ठा tcphdr, check);
			tcp_hdr(skb)->check = csum;
		पूर्ण

		w0 = ETXD_DOCHECKSUM | (csoff << ETXD_CHKOFF_SHIFT);
	पूर्ण

	spin_lock_irq(&ip->ioc3_lock);

	data = (अचिन्हित दीर्घ)skb->data;
	len = skb->len;

	produce = ip->tx_pi;
	desc = &ip->txr[produce];

	अगर (len <= 104) अणु
		/* Short packet, let's copy it directly पूर्णांकo the ring.  */
		skb_copy_from_linear_data(skb, desc->data, skb->len);
		अगर (len < ETH_ZLEN) अणु
			/* Very लघु packet, pad with zeros at the end. */
			स_रखो(desc->data + len, 0, ETH_ZLEN - len);
			len = ETH_ZLEN;
		पूर्ण
		desc->cmd = cpu_to_be32(len | ETXD_INTWHENDONE | ETXD_D0V | w0);
		desc->bufcnt = cpu_to_be32(len);
	पूर्ण अन्यथा अगर ((data ^ (data + len - 1)) & 0x4000) अणु
		अचिन्हित दीर्घ b2 = (data | 0x3fffUL) + 1UL;
		अचिन्हित दीर्घ s1 = b2 - data;
		अचिन्हित दीर्घ s2 = data + len - b2;
		dma_addr_t d1, d2;

		desc->cmd    = cpu_to_be32(len | ETXD_INTWHENDONE |
					   ETXD_B1V | ETXD_B2V | w0);
		desc->bufcnt = cpu_to_be32((s1 << ETXD_B1CNT_SHIFT) |
					   (s2 << ETXD_B2CNT_SHIFT));
		d1 = dma_map_single(ip->dma_dev, skb->data, s1, DMA_TO_DEVICE);
		अगर (dma_mapping_error(ip->dma_dev, d1))
			जाओ drop_packet;
		d2 = dma_map_single(ip->dma_dev, (व्योम *)b2, s1, DMA_TO_DEVICE);
		अगर (dma_mapping_error(ip->dma_dev, d2)) अणु
			dma_unmap_single(ip->dma_dev, d1, len, DMA_TO_DEVICE);
			जाओ drop_packet;
		पूर्ण
		desc->p1     = cpu_to_be64(ioc3_map(d1, PCI64_ATTR_PREF));
		desc->p2     = cpu_to_be64(ioc3_map(d2, PCI64_ATTR_PREF));
	पूर्ण अन्यथा अणु
		dma_addr_t d;

		/* Normal sized packet that करोesn't cross a page boundary. */
		desc->cmd = cpu_to_be32(len | ETXD_INTWHENDONE | ETXD_B1V | w0);
		desc->bufcnt = cpu_to_be32(len << ETXD_B1CNT_SHIFT);
		d = dma_map_single(ip->dma_dev, skb->data, len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(ip->dma_dev, d))
			जाओ drop_packet;
		desc->p1     = cpu_to_be64(ioc3_map(d, PCI64_ATTR_PREF));
	पूर्ण

	mb(); /* make sure all descriptor changes are visible */

	ip->tx_skbs[produce] = skb;			/* Remember skb */
	produce = (produce + 1) & TX_RING_MASK;
	ip->tx_pi = produce;
	ग_लिखोl(produce << 7, &ip->regs->etpir);		/* Fire ... */

	ip->txqlen++;

	अगर (ip->txqlen >= (TX_RING_ENTRIES - 1))
		netअगर_stop_queue(dev);

	spin_unlock_irq(&ip->ioc3_lock);

	वापस NETDEV_TX_OK;

drop_packet:
	dev_kमुक्त_skb_any(skb);
	dev->stats.tx_dropped++;

	spin_unlock_irq(&ip->ioc3_lock);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ioc3_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);

	netdev_err(dev, "transmit timed out, resetting\n");

	spin_lock_irq(&ip->ioc3_lock);

	ioc3_stop(ip);
	ioc3_मुक्त_rx_bufs(ip);
	ioc3_clean_tx_ring(ip);

	ioc3_init(dev);
	अगर (ioc3_alloc_rx_bufs(dev)) अणु
		netdev_err(dev, "%s: rx buffer allocation failed\n", __func__);
		spin_unlock_irq(&ip->ioc3_lock);
		वापस;
	पूर्ण
	ioc3_start(ip);
	ioc3_mii_init(ip);
	ioc3_mii_start(ip);

	spin_unlock_irq(&ip->ioc3_lock);

	netअगर_wake_queue(dev);
पूर्ण

/* Given a multicast ethernet address, this routine calculates the
 * address's bit index in the logical address filter mask
 */
अटल अंतरभूत अचिन्हित पूर्णांक ioc3_hash(स्थिर अचिन्हित अक्षर *addr)
अणु
	अचिन्हित पूर्णांक temp = 0;
	पूर्णांक bits;
	u32 crc;

	crc = ether_crc_le(ETH_ALEN, addr);

	crc &= 0x3f;    /* bit reverse lowest 6 bits क्रम hash index */
	क्रम (bits = 6; --bits >= 0; ) अणु
		temp <<= 1;
		temp |= (crc & 0x1);
		crc >>= 1;
	पूर्ण

	वापस temp;
पूर्ण

अटल व्योम ioc3_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, IOC3_NAME, माप(info->driver));
	strlcpy(info->version, IOC3_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(to_pci_dev(dev->dev.parent)),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक ioc3_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);

	spin_lock_irq(&ip->ioc3_lock);
	mii_ethtool_get_link_ksettings(&ip->mii, cmd);
	spin_unlock_irq(&ip->ioc3_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ioc3_set_link_ksettings(काष्ठा net_device *dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&ip->ioc3_lock);
	rc = mii_ethtool_set_link_ksettings(&ip->mii, cmd);
	spin_unlock_irq(&ip->ioc3_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक ioc3_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&ip->ioc3_lock);
	rc = mii_nway_restart(&ip->mii);
	spin_unlock_irq(&ip->ioc3_lock);

	वापस rc;
पूर्ण

अटल u32 ioc3_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&ip->ioc3_lock);
	rc = mii_link_ok(&ip->mii);
	spin_unlock_irq(&ip->ioc3_lock);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ioc3_ethtool_ops = अणु
	.get_drvinfo		= ioc3_get_drvinfo,
	.nway_reset		= ioc3_nway_reset,
	.get_link		= ioc3_get_link,
	.get_link_ksettings	= ioc3_get_link_ksettings,
	.set_link_ksettings	= ioc3_set_link_ksettings,
पूर्ण;

अटल पूर्णांक ioc3_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&ip->ioc3_lock);
	rc = generic_mii_ioctl(&ip->mii, अगर_mii(rq), cmd, शून्य);
	spin_unlock_irq(&ip->ioc3_lock);

	वापस rc;
पूर्ण

अटल व्योम ioc3_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ioc3_निजी *ip = netdev_priv(dev);
	काष्ठा ioc3_ethregs *regs = ip->regs;
	काष्ठा netdev_hw_addr *ha;
	u64 ehar = 0;

	spin_lock_irq(&ip->ioc3_lock);

	अगर (dev->flags & IFF_PROMISC) अणु			/* Set promiscuous.  */
		ip->emcr |= EMCR_PROMISC;
		ग_लिखोl(ip->emcr, &regs->emcr);
		पढ़ोl(&regs->emcr);
	पूर्ण अन्यथा अणु
		ip->emcr &= ~EMCR_PROMISC;
		ग_लिखोl(ip->emcr, &regs->emcr);		/* Clear promiscuous. */
		पढ़ोl(&regs->emcr);

		अगर ((dev->flags & IFF_ALLMULTI) ||
		    (netdev_mc_count(dev) > 64)) अणु
			/* Too many क्रम hashing to make sense or we want all
			 * multicast packets anyway,  so skip computing all the
			 * hashes and just accept all packets.
			 */
			ip->ehar_h = 0xffffffff;
			ip->ehar_l = 0xffffffff;
		पूर्ण अन्यथा अणु
			netdev_क्रम_each_mc_addr(ha, dev) अणु
				ehar |= (1UL << ioc3_hash(ha->addr));
			पूर्ण
			ip->ehar_h = ehar >> 32;
			ip->ehar_l = ehar & 0xffffffff;
		पूर्ण
		ग_लिखोl(ip->ehar_h, &regs->ehar_h);
		ग_लिखोl(ip->ehar_l, &regs->ehar_l);
	पूर्ण

	spin_unlock_irq(&ip->ioc3_lock);
पूर्ण

अटल काष्ठा platक्रमm_driver ioc3eth_driver = अणु
	.probe  = ioc3eth_probe,
	.हटाओ = ioc3eth_हटाओ,
	.driver = अणु
		.name = "ioc3-eth",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(ioc3eth_driver);

MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
MODULE_DESCRIPTION("SGI IOC3 Ethernet driver");
MODULE_LICENSE("GPL");
