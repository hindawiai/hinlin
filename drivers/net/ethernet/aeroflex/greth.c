<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Aeroflex Gaisler GRETH 10/100/1G Ethernet MAC.
 *
 * 2005-2010 (c) Aeroflex Gaisler AB
 *
 * This driver supports GRETH 10/100 and GRETH 10/100/1G Ethernet MACs
 * available in the GRLIB VHDL IP core library.
 *
 * Full करोcumentation of both cores can be found here:
 * https://www.gaisler.com/products/grlib/grip.pdf
 *
 * The Gigabit version supports scatter/gather DMA, any alignment of
 * buffers and checksum offloading.
 *
 * Contributors: Kristoffer Glembo
 *               Daniel Hellstrom
 *               Marko Isomaki
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/पन.स>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/byteorder.h>

#अगर_घोषित CONFIG_SPARC
#समावेश <यंत्र/idprom.h>
#पूर्ण_अगर

#समावेश "greth.h"

#घोषणा GRETH_DEF_MSG_ENABLE	  \
	(NETIF_MSG_DRV		| \
	 NETIF_MSG_PROBE	| \
	 NETIF_MSG_LINK		| \
	 NETIF_MSG_IFDOWN	| \
	 NETIF_MSG_IFUP		| \
	 NETIF_MSG_RX_ERR	| \
	 NETIF_MSG_TX_ERR)

अटल पूर्णांक greth_debug = -1;	/* -1 == use GRETH_DEF_MSG_ENABLE as value */
module_param(greth_debug, पूर्णांक, 0);
MODULE_PARM_DESC(greth_debug, "GRETH bitmapped debugging message enable value");

/* Accept MAC address of the क्रमm macaddr=0x08,0x00,0x20,0x30,0x40,0x50 */
अटल पूर्णांक macaddr[6];
module_param_array(macaddr, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(macaddr, "GRETH Ethernet MAC address");

अटल पूर्णांक greth_edcl = 1;
module_param(greth_edcl, पूर्णांक, 0);
MODULE_PARM_DESC(greth_edcl, "GRETH EDCL usage indicator. Set to 1 if EDCL is used.");

अटल पूर्णांक greth_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t greth_start_xmit(काष्ठा sk_buff *skb,
	   काष्ठा net_device *dev);
अटल netdev_tx_t greth_start_xmit_gbit(काष्ठा sk_buff *skb,
	   काष्ठा net_device *dev);
अटल पूर्णांक greth_rx(काष्ठा net_device *dev, पूर्णांक limit);
अटल पूर्णांक greth_rx_gbit(काष्ठा net_device *dev, पूर्णांक limit);
अटल व्योम greth_clean_tx(काष्ठा net_device *dev);
अटल व्योम greth_clean_tx_gbit(काष्ठा net_device *dev);
अटल irqवापस_t greth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक greth_बंद(काष्ठा net_device *dev);
अटल पूर्णांक greth_set_mac_add(काष्ठा net_device *dev, व्योम *p);
अटल व्योम greth_set_multicast_list(काष्ठा net_device *dev);

#घोषणा GRETH_REGLOAD(a)	    (be32_to_cpu(__raw_पढ़ोl(&(a))))
#घोषणा GRETH_REGSAVE(a, v)         (__raw_ग_लिखोl(cpu_to_be32(v), &(a)))
#घोषणा GRETH_REGORIN(a, v)         (GRETH_REGSAVE(a, (GRETH_REGLOAD(a) | (v))))
#घोषणा GRETH_REGANDIN(a, v)        (GRETH_REGSAVE(a, (GRETH_REGLOAD(a) & (v))))

#घोषणा NEXT_TX(N)      (((N) + 1) & GRETH_TXBD_NUM_MASK)
#घोषणा SKIP_TX(N, C)   (((N) + C) & GRETH_TXBD_NUM_MASK)
#घोषणा NEXT_RX(N)      (((N) + 1) & GRETH_RXBD_NUM_MASK)

अटल व्योम greth_prपूर्णांक_rx_packet(व्योम *addr, पूर्णांक len)
अणु
	prपूर्णांक_hex_dump(KERN_DEBUG, "RX: ", DUMP_PREFIX_OFFSET, 16, 1,
			addr, len, true);
पूर्ण

अटल व्योम greth_prपूर्णांक_tx_packet(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;
	पूर्णांक length;

	अगर (skb_shinfo(skb)->nr_frags == 0)
		length = skb->len;
	अन्यथा
		length = skb_headlen(skb);

	prपूर्णांक_hex_dump(KERN_DEBUG, "TX: ", DUMP_PREFIX_OFFSET, 16, 1,
			skb->data, length, true);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु

		prपूर्णांक_hex_dump(KERN_DEBUG, "TX: ", DUMP_PREFIX_OFFSET, 16, 1,
			       skb_frag_address(&skb_shinfo(skb)->frags[i]),
			       skb_frag_size(&skb_shinfo(skb)->frags[i]), true);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम greth_enable_tx(काष्ठा greth_निजी *greth)
अणु
	wmb();
	GRETH_REGORIN(greth->regs->control, GRETH_TXEN);
पूर्ण

अटल अंतरभूत व्योम greth_enable_tx_and_irq(काष्ठा greth_निजी *greth)
अणु
	wmb(); /* BDs must been written to memory beक्रमe enabling TX */
	GRETH_REGORIN(greth->regs->control, GRETH_TXEN | GRETH_TXI);
पूर्ण

अटल अंतरभूत व्योम greth_disable_tx(काष्ठा greth_निजी *greth)
अणु
	GRETH_REGANDIN(greth->regs->control, ~GRETH_TXEN);
पूर्ण

अटल अंतरभूत व्योम greth_enable_rx(काष्ठा greth_निजी *greth)
अणु
	wmb();
	GRETH_REGORIN(greth->regs->control, GRETH_RXEN);
पूर्ण

अटल अंतरभूत व्योम greth_disable_rx(काष्ठा greth_निजी *greth)
अणु
	GRETH_REGANDIN(greth->regs->control, ~GRETH_RXEN);
पूर्ण

अटल अंतरभूत व्योम greth_enable_irqs(काष्ठा greth_निजी *greth)
अणु
	GRETH_REGORIN(greth->regs->control, GRETH_RXI | GRETH_TXI);
पूर्ण

अटल अंतरभूत व्योम greth_disable_irqs(काष्ठा greth_निजी *greth)
अणु
	GRETH_REGANDIN(greth->regs->control, ~(GRETH_RXI|GRETH_TXI));
पूर्ण

अटल अंतरभूत व्योम greth_ग_लिखो_bd(u32 *bd, u32 val)
अणु
	__raw_ग_लिखोl(cpu_to_be32(val), bd);
पूर्ण

अटल अंतरभूत u32 greth_पढ़ो_bd(u32 *bd)
अणु
	वापस be32_to_cpu(__raw_पढ़ोl(bd));
पूर्ण

अटल व्योम greth_clean_rings(काष्ठा greth_निजी *greth)
अणु
	पूर्णांक i;
	काष्ठा greth_bd *rx_bdp = greth->rx_bd_base;
	काष्ठा greth_bd *tx_bdp = greth->tx_bd_base;

	अगर (greth->gbit_mac) अणु

		/* Free and unmap RX buffers */
		क्रम (i = 0; i < GRETH_RXBD_NUM; i++, rx_bdp++) अणु
			अगर (greth->rx_skbuff[i] != शून्य) अणु
				dev_kमुक्त_skb(greth->rx_skbuff[i]);
				dma_unmap_single(greth->dev,
						 greth_पढ़ो_bd(&rx_bdp->addr),
						 MAX_FRAME_SIZE+NET_IP_ALIGN,
						 DMA_FROM_DEVICE);
			पूर्ण
		पूर्ण

		/* TX buffers */
		जबतक (greth->tx_मुक्त < GRETH_TXBD_NUM) अणु

			काष्ठा sk_buff *skb = greth->tx_skbuff[greth->tx_last];
			पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
			tx_bdp = greth->tx_bd_base + greth->tx_last;
			greth->tx_last = NEXT_TX(greth->tx_last);

			dma_unmap_single(greth->dev,
					 greth_पढ़ो_bd(&tx_bdp->addr),
					 skb_headlen(skb),
					 DMA_TO_DEVICE);

			क्रम (i = 0; i < nr_frags; i++) अणु
				skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
				tx_bdp = greth->tx_bd_base + greth->tx_last;

				dma_unmap_page(greth->dev,
					       greth_पढ़ो_bd(&tx_bdp->addr),
					       skb_frag_size(frag),
					       DMA_TO_DEVICE);

				greth->tx_last = NEXT_TX(greth->tx_last);
			पूर्ण
			greth->tx_मुक्त += nr_frags+1;
			dev_kमुक्त_skb(skb);
		पूर्ण


	पूर्ण अन्यथा अणु /* 10/100 Mbps MAC */

		क्रम (i = 0; i < GRETH_RXBD_NUM; i++, rx_bdp++) अणु
			kमुक्त(greth->rx_bufs[i]);
			dma_unmap_single(greth->dev,
					 greth_पढ़ो_bd(&rx_bdp->addr),
					 MAX_FRAME_SIZE,
					 DMA_FROM_DEVICE);
		पूर्ण
		क्रम (i = 0; i < GRETH_TXBD_NUM; i++, tx_bdp++) अणु
			kमुक्त(greth->tx_bufs[i]);
			dma_unmap_single(greth->dev,
					 greth_पढ़ो_bd(&tx_bdp->addr),
					 MAX_FRAME_SIZE,
					 DMA_TO_DEVICE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक greth_init_rings(काष्ठा greth_निजी *greth)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा greth_bd *rx_bd, *tx_bd;
	u32 dma_addr;
	पूर्णांक i;

	rx_bd = greth->rx_bd_base;
	tx_bd = greth->tx_bd_base;

	/* Initialize descriptor rings and buffers */
	अगर (greth->gbit_mac) अणु

		क्रम (i = 0; i < GRETH_RXBD_NUM; i++) अणु
			skb = netdev_alloc_skb(greth->netdev, MAX_FRAME_SIZE+NET_IP_ALIGN);
			अगर (skb == शून्य) अणु
				अगर (netअगर_msg_अगरup(greth))
					dev_err(greth->dev, "Error allocating DMA ring.\n");
				जाओ cleanup;
			पूर्ण
			skb_reserve(skb, NET_IP_ALIGN);
			dma_addr = dma_map_single(greth->dev,
						  skb->data,
						  MAX_FRAME_SIZE+NET_IP_ALIGN,
						  DMA_FROM_DEVICE);

			अगर (dma_mapping_error(greth->dev, dma_addr)) अणु
				अगर (netअगर_msg_अगरup(greth))
					dev_err(greth->dev, "Could not create initial DMA mapping\n");
				जाओ cleanup;
			पूर्ण
			greth->rx_skbuff[i] = skb;
			greth_ग_लिखो_bd(&rx_bd[i].addr, dma_addr);
			greth_ग_लिखो_bd(&rx_bd[i].stat, GRETH_BD_EN | GRETH_BD_IE);
		पूर्ण

	पूर्ण अन्यथा अणु

		/* 10/100 MAC uses a fixed set of buffers and copy to/from SKBs */
		क्रम (i = 0; i < GRETH_RXBD_NUM; i++) अणु

			greth->rx_bufs[i] = kदो_स्मृति(MAX_FRAME_SIZE, GFP_KERNEL);

			अगर (greth->rx_bufs[i] == शून्य) अणु
				अगर (netअगर_msg_अगरup(greth))
					dev_err(greth->dev, "Error allocating DMA ring.\n");
				जाओ cleanup;
			पूर्ण

			dma_addr = dma_map_single(greth->dev,
						  greth->rx_bufs[i],
						  MAX_FRAME_SIZE,
						  DMA_FROM_DEVICE);

			अगर (dma_mapping_error(greth->dev, dma_addr)) अणु
				अगर (netअगर_msg_अगरup(greth))
					dev_err(greth->dev, "Could not create initial DMA mapping\n");
				जाओ cleanup;
			पूर्ण
			greth_ग_लिखो_bd(&rx_bd[i].addr, dma_addr);
			greth_ग_लिखो_bd(&rx_bd[i].stat, GRETH_BD_EN | GRETH_BD_IE);
		पूर्ण
		क्रम (i = 0; i < GRETH_TXBD_NUM; i++) अणु

			greth->tx_bufs[i] = kदो_स्मृति(MAX_FRAME_SIZE, GFP_KERNEL);

			अगर (greth->tx_bufs[i] == शून्य) अणु
				अगर (netअगर_msg_अगरup(greth))
					dev_err(greth->dev, "Error allocating DMA ring.\n");
				जाओ cleanup;
			पूर्ण

			dma_addr = dma_map_single(greth->dev,
						  greth->tx_bufs[i],
						  MAX_FRAME_SIZE,
						  DMA_TO_DEVICE);

			अगर (dma_mapping_error(greth->dev, dma_addr)) अणु
				अगर (netअगर_msg_अगरup(greth))
					dev_err(greth->dev, "Could not create initial DMA mapping\n");
				जाओ cleanup;
			पूर्ण
			greth_ग_लिखो_bd(&tx_bd[i].addr, dma_addr);
			greth_ग_लिखो_bd(&tx_bd[i].stat, 0);
		पूर्ण
	पूर्ण
	greth_ग_लिखो_bd(&rx_bd[GRETH_RXBD_NUM - 1].stat,
		       greth_पढ़ो_bd(&rx_bd[GRETH_RXBD_NUM - 1].stat) | GRETH_BD_WR);

	/* Initialize poपूर्णांकers. */
	greth->rx_cur = 0;
	greth->tx_next = 0;
	greth->tx_last = 0;
	greth->tx_मुक्त = GRETH_TXBD_NUM;

	/* Initialize descriptor base address */
	GRETH_REGSAVE(greth->regs->tx_desc_p, greth->tx_bd_base_phys);
	GRETH_REGSAVE(greth->regs->rx_desc_p, greth->rx_bd_base_phys);

	वापस 0;

cleanup:
	greth_clean_rings(greth);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक greth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	पूर्णांक err;

	err = greth_init_rings(greth);
	अगर (err) अणु
		अगर (netअगर_msg_अगरup(greth))
			dev_err(&dev->dev, "Could not allocate memory for DMA rings\n");
		वापस err;
	पूर्ण

	err = request_irq(greth->irq, greth_पूर्णांकerrupt, 0, "eth", (व्योम *) dev);
	अगर (err) अणु
		अगर (netअगर_msg_अगरup(greth))
			dev_err(&dev->dev, "Could not allocate interrupt %d\n", dev->irq);
		greth_clean_rings(greth);
		वापस err;
	पूर्ण

	अगर (netअगर_msg_अगरup(greth))
		dev_dbg(&dev->dev, " starting queue\n");
	netअगर_start_queue(dev);

	GRETH_REGSAVE(greth->regs->status, 0xFF);

	napi_enable(&greth->napi);

	greth_enable_irqs(greth);
	greth_enable_tx(greth);
	greth_enable_rx(greth);
	वापस 0;

पूर्ण

अटल पूर्णांक greth_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);

	napi_disable(&greth->napi);

	greth_disable_irqs(greth);
	greth_disable_tx(greth);
	greth_disable_rx(greth);

	netअगर_stop_queue(dev);

	मुक्त_irq(greth->irq, (व्योम *) dev);

	greth_clean_rings(greth);

	वापस 0;
पूर्ण

अटल netdev_tx_t
greth_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	काष्ठा greth_bd *bdp;
	पूर्णांक err = NETDEV_TX_OK;
	u32 status, dma_addr, ctrl;
	अचिन्हित दीर्घ flags;

	/* Clean TX Ring */
	greth_clean_tx(greth->netdev);

	अगर (unlikely(greth->tx_मुक्त <= 0)) अणु
		spin_lock_irqsave(&greth->devlock, flags);/*save from poll/irq*/
		ctrl = GRETH_REGLOAD(greth->regs->control);
		/* Enable TX IRQ only अगर not alपढ़ोy in poll() routine */
		अगर (ctrl & GRETH_RXI)
			GRETH_REGSAVE(greth->regs->control, ctrl | GRETH_TXI);
		netअगर_stop_queue(dev);
		spin_unlock_irqrestore(&greth->devlock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (netअगर_msg_pktdata(greth))
		greth_prपूर्णांक_tx_packet(skb);


	अगर (unlikely(skb->len > MAX_FRAME_SIZE)) अणु
		dev->stats.tx_errors++;
		जाओ out;
	पूर्ण

	bdp = greth->tx_bd_base + greth->tx_next;
	dma_addr = greth_पढ़ो_bd(&bdp->addr);

	स_नकल((अचिन्हित अक्षर *) phys_to_virt(dma_addr), skb->data, skb->len);

	dma_sync_single_क्रम_device(greth->dev, dma_addr, skb->len, DMA_TO_DEVICE);

	status = GRETH_BD_EN | GRETH_BD_IE | (skb->len & GRETH_BD_LEN);
	greth->tx_bufs_length[greth->tx_next] = skb->len & GRETH_BD_LEN;

	/* Wrap around descriptor ring */
	अगर (greth->tx_next == GRETH_TXBD_NUM_MASK) अणु
		status |= GRETH_BD_WR;
	पूर्ण

	greth->tx_next = NEXT_TX(greth->tx_next);
	greth->tx_मुक्त--;

	/* Write descriptor control word and enable transmission */
	greth_ग_लिखो_bd(&bdp->stat, status);
	spin_lock_irqsave(&greth->devlock, flags); /*save from poll/irq*/
	greth_enable_tx(greth);
	spin_unlock_irqrestore(&greth->devlock, flags);

out:
	dev_kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल अंतरभूत u16 greth_num_मुक्त_bds(u16 tx_last, u16 tx_next)
अणु
	अगर (tx_next < tx_last)
		वापस (tx_last - tx_next) - 1;
	अन्यथा
		वापस GRETH_TXBD_NUM - (tx_next - tx_last) - 1;
पूर्ण

अटल netdev_tx_t
greth_start_xmit_gbit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	काष्ठा greth_bd *bdp;
	u32 status, dma_addr;
	पूर्णांक curr_tx, nr_frags, i, err = NETDEV_TX_OK;
	अचिन्हित दीर्घ flags;
	u16 tx_last;

	nr_frags = skb_shinfo(skb)->nr_frags;
	tx_last = greth->tx_last;
	rmb(); /* tx_last is updated by the poll task */

	अगर (greth_num_मुक्त_bds(tx_last, greth->tx_next) < nr_frags + 1) अणु
		netअगर_stop_queue(dev);
		err = NETDEV_TX_BUSY;
		जाओ out;
	पूर्ण

	अगर (netअगर_msg_pktdata(greth))
		greth_prपूर्णांक_tx_packet(skb);

	अगर (unlikely(skb->len > MAX_FRAME_SIZE)) अणु
		dev->stats.tx_errors++;
		जाओ out;
	पूर्ण

	/* Save skb poपूर्णांकer. */
	greth->tx_skbuff[greth->tx_next] = skb;

	/* Linear buf */
	अगर (nr_frags != 0)
		status = GRETH_TXBD_MORE;
	अन्यथा
		status = GRETH_BD_IE;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		status |= GRETH_TXBD_CSALL;
	status |= skb_headlen(skb) & GRETH_BD_LEN;
	अगर (greth->tx_next == GRETH_TXBD_NUM_MASK)
		status |= GRETH_BD_WR;


	bdp = greth->tx_bd_base + greth->tx_next;
	greth_ग_लिखो_bd(&bdp->stat, status);
	dma_addr = dma_map_single(greth->dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(greth->dev, dma_addr)))
		जाओ map_error;

	greth_ग_लिखो_bd(&bdp->addr, dma_addr);

	curr_tx = NEXT_TX(greth->tx_next);

	/* Frags */
	क्रम (i = 0; i < nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		greth->tx_skbuff[curr_tx] = शून्य;
		bdp = greth->tx_bd_base + curr_tx;

		status = GRETH_BD_EN;
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			status |= GRETH_TXBD_CSALL;
		status |= skb_frag_size(frag) & GRETH_BD_LEN;

		/* Wrap around descriptor ring */
		अगर (curr_tx == GRETH_TXBD_NUM_MASK)
			status |= GRETH_BD_WR;

		/* More fragments left */
		अगर (i < nr_frags - 1)
			status |= GRETH_TXBD_MORE;
		अन्यथा
			status |= GRETH_BD_IE; /* enable IRQ on last fragment */

		greth_ग_लिखो_bd(&bdp->stat, status);

		dma_addr = skb_frag_dma_map(greth->dev, frag, 0, skb_frag_size(frag),
					    DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(greth->dev, dma_addr)))
			जाओ frag_map_error;

		greth_ग_लिखो_bd(&bdp->addr, dma_addr);

		curr_tx = NEXT_TX(curr_tx);
	पूर्ण

	wmb();

	/* Enable the descriptor chain by enabling the first descriptor */
	bdp = greth->tx_bd_base + greth->tx_next;
	greth_ग_लिखो_bd(&bdp->stat,
		       greth_पढ़ो_bd(&bdp->stat) | GRETH_BD_EN);

	spin_lock_irqsave(&greth->devlock, flags); /*save from poll/irq*/
	greth->tx_next = curr_tx;
	greth_enable_tx_and_irq(greth);
	spin_unlock_irqrestore(&greth->devlock, flags);

	वापस NETDEV_TX_OK;

frag_map_error:
	/* Unmap SKB mappings that succeeded and disable descriptor */
	क्रम (i = 0; greth->tx_next + i != curr_tx; i++) अणु
		bdp = greth->tx_bd_base + greth->tx_next + i;
		dma_unmap_single(greth->dev,
				 greth_पढ़ो_bd(&bdp->addr),
				 greth_पढ़ो_bd(&bdp->stat) & GRETH_BD_LEN,
				 DMA_TO_DEVICE);
		greth_ग_लिखो_bd(&bdp->stat, 0);
	पूर्ण
map_error:
	अगर (net_ratelimit())
		dev_warn(greth->dev, "Could not create TX DMA mapping\n");
	dev_kमुक्त_skb(skb);
out:
	वापस err;
पूर्ण

अटल irqवापस_t greth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा greth_निजी *greth;
	u32 status, ctrl;
	irqवापस_t retval = IRQ_NONE;

	greth = netdev_priv(dev);

	spin_lock(&greth->devlock);

	/* Get the पूर्णांकerrupt events that caused us to be here. */
	status = GRETH_REGLOAD(greth->regs->status);

	/* Must see अगर पूर्णांकerrupts are enabled also, INT_TX|INT_RX flags may be
	 * set regardless of whether IRQ is enabled or not. Especially
	 * important when shared IRQ.
	 */
	ctrl = GRETH_REGLOAD(greth->regs->control);

	/* Handle rx and tx पूर्णांकerrupts through poll */
	अगर (((status & (GRETH_INT_RE | GRETH_INT_RX)) && (ctrl & GRETH_RXI)) ||
	    ((status & (GRETH_INT_TE | GRETH_INT_TX)) && (ctrl & GRETH_TXI))) अणु
		retval = IRQ_HANDLED;

		/* Disable पूर्णांकerrupts and schedule poll() */
		greth_disable_irqs(greth);
		napi_schedule(&greth->napi);
	पूर्ण

	spin_unlock(&greth->devlock);

	वापस retval;
पूर्ण

अटल व्योम greth_clean_tx(काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth;
	काष्ठा greth_bd *bdp;
	u32 stat;

	greth = netdev_priv(dev);

	जबतक (1) अणु
		bdp = greth->tx_bd_base + greth->tx_last;
		GRETH_REGSAVE(greth->regs->status, GRETH_INT_TE | GRETH_INT_TX);
		mb();
		stat = greth_पढ़ो_bd(&bdp->stat);

		अगर (unlikely(stat & GRETH_BD_EN))
			अवरोध;

		अगर (greth->tx_मुक्त == GRETH_TXBD_NUM)
			अवरोध;

		/* Check status क्रम errors */
		अगर (unlikely(stat & GRETH_TXBD_STATUS)) अणु
			dev->stats.tx_errors++;
			अगर (stat & GRETH_TXBD_ERR_AL)
				dev->stats.tx_पातed_errors++;
			अगर (stat & GRETH_TXBD_ERR_UE)
				dev->stats.tx_fअगरo_errors++;
		पूर्ण
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += greth->tx_bufs_length[greth->tx_last];
		greth->tx_last = NEXT_TX(greth->tx_last);
		greth->tx_मुक्त++;
	पूर्ण

	अगर (greth->tx_मुक्त > 0) अणु
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम greth_update_tx_stats(काष्ठा net_device *dev, u32 stat)
अणु
	/* Check status क्रम errors */
	अगर (unlikely(stat & GRETH_TXBD_STATUS)) अणु
		dev->stats.tx_errors++;
		अगर (stat & GRETH_TXBD_ERR_AL)
			dev->stats.tx_पातed_errors++;
		अगर (stat & GRETH_TXBD_ERR_UE)
			dev->stats.tx_fअगरo_errors++;
		अगर (stat & GRETH_TXBD_ERR_LC)
			dev->stats.tx_पातed_errors++;
	पूर्ण
	dev->stats.tx_packets++;
पूर्ण

अटल व्योम greth_clean_tx_gbit(काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth;
	काष्ठा greth_bd *bdp, *bdp_last_frag;
	काष्ठा sk_buff *skb = शून्य;
	u32 stat;
	पूर्णांक nr_frags, i;
	u16 tx_last;

	greth = netdev_priv(dev);
	tx_last = greth->tx_last;

	जबतक (tx_last != greth->tx_next) अणु

		skb = greth->tx_skbuff[tx_last];

		nr_frags = skb_shinfo(skb)->nr_frags;

		/* We only clean fully completed SKBs */
		bdp_last_frag = greth->tx_bd_base + SKIP_TX(tx_last, nr_frags);

		GRETH_REGSAVE(greth->regs->status, GRETH_INT_TE | GRETH_INT_TX);
		mb();
		stat = greth_पढ़ो_bd(&bdp_last_frag->stat);

		अगर (stat & GRETH_BD_EN)
			अवरोध;

		greth->tx_skbuff[tx_last] = शून्य;

		greth_update_tx_stats(dev, stat);
		dev->stats.tx_bytes += skb->len;

		bdp = greth->tx_bd_base + tx_last;

		tx_last = NEXT_TX(tx_last);

		dma_unmap_single(greth->dev,
				 greth_पढ़ो_bd(&bdp->addr),
				 skb_headlen(skb),
				 DMA_TO_DEVICE);

		क्रम (i = 0; i < nr_frags; i++) अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			bdp = greth->tx_bd_base + tx_last;

			dma_unmap_page(greth->dev,
				       greth_पढ़ो_bd(&bdp->addr),
				       skb_frag_size(frag),
				       DMA_TO_DEVICE);

			tx_last = NEXT_TX(tx_last);
		पूर्ण
		dev_kमुक्त_skb(skb);
	पूर्ण
	अगर (skb) अणु /* skb is set only अगर the above जबतक loop was entered */
		wmb();
		greth->tx_last = tx_last;

		अगर (netअगर_queue_stopped(dev) &&
		    (greth_num_मुक्त_bds(tx_last, greth->tx_next) >
		    (MAX_SKB_FRAGS+1)))
			netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक greth_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा greth_निजी *greth;
	काष्ठा greth_bd *bdp;
	काष्ठा sk_buff *skb;
	पूर्णांक pkt_len;
	पूर्णांक bad, count;
	u32 status, dma_addr;
	अचिन्हित दीर्घ flags;

	greth = netdev_priv(dev);

	क्रम (count = 0; count < limit; ++count) अणु

		bdp = greth->rx_bd_base + greth->rx_cur;
		GRETH_REGSAVE(greth->regs->status, GRETH_INT_RE | GRETH_INT_RX);
		mb();
		status = greth_पढ़ो_bd(&bdp->stat);

		अगर (unlikely(status & GRETH_BD_EN)) अणु
			अवरोध;
		पूर्ण

		dma_addr = greth_पढ़ो_bd(&bdp->addr);
		bad = 0;

		/* Check status क्रम errors. */
		अगर (unlikely(status & GRETH_RXBD_STATUS)) अणु
			अगर (status & GRETH_RXBD_ERR_FT) अणु
				dev->stats.rx_length_errors++;
				bad = 1;
			पूर्ण
			अगर (status & (GRETH_RXBD_ERR_AE | GRETH_RXBD_ERR_OE)) अणु
				dev->stats.rx_frame_errors++;
				bad = 1;
			पूर्ण
			अगर (status & GRETH_RXBD_ERR_CRC) अणु
				dev->stats.rx_crc_errors++;
				bad = 1;
			पूर्ण
		पूर्ण
		अगर (unlikely(bad)) अणु
			dev->stats.rx_errors++;

		पूर्ण अन्यथा अणु

			pkt_len = status & GRETH_BD_LEN;

			skb = netdev_alloc_skb(dev, pkt_len + NET_IP_ALIGN);

			अगर (unlikely(skb == शून्य)) अणु

				अगर (net_ratelimit())
					dev_warn(&dev->dev, "low on memory - " "packet dropped\n");

				dev->stats.rx_dropped++;

			पूर्ण अन्यथा अणु
				skb_reserve(skb, NET_IP_ALIGN);

				dma_sync_single_क्रम_cpu(greth->dev,
							dma_addr,
							pkt_len,
							DMA_FROM_DEVICE);

				अगर (netअगर_msg_pktdata(greth))
					greth_prपूर्णांक_rx_packet(phys_to_virt(dma_addr), pkt_len);

				skb_put_data(skb, phys_to_virt(dma_addr),
					     pkt_len);

				skb->protocol = eth_type_trans(skb, dev);
				dev->stats.rx_bytes += pkt_len;
				dev->stats.rx_packets++;
				netअगर_receive_skb(skb);
			पूर्ण
		पूर्ण

		status = GRETH_BD_EN | GRETH_BD_IE;
		अगर (greth->rx_cur == GRETH_RXBD_NUM_MASK) अणु
			status |= GRETH_BD_WR;
		पूर्ण

		wmb();
		greth_ग_लिखो_bd(&bdp->stat, status);

		dma_sync_single_क्रम_device(greth->dev, dma_addr, MAX_FRAME_SIZE, DMA_FROM_DEVICE);

		spin_lock_irqsave(&greth->devlock, flags); /* save from XMIT */
		greth_enable_rx(greth);
		spin_unlock_irqrestore(&greth->devlock, flags);

		greth->rx_cur = NEXT_RX(greth->rx_cur);
	पूर्ण

	वापस count;
पूर्ण

अटल अंतरभूत पूर्णांक hw_checksummed(u32 status)
अणु

	अगर (status & GRETH_RXBD_IP_FRAG)
		वापस 0;

	अगर (status & GRETH_RXBD_IP && status & GRETH_RXBD_IP_CSERR)
		वापस 0;

	अगर (status & GRETH_RXBD_UDP && status & GRETH_RXBD_UDP_CSERR)
		वापस 0;

	अगर (status & GRETH_RXBD_TCP && status & GRETH_RXBD_TCP_CSERR)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक greth_rx_gbit(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा greth_निजी *greth;
	काष्ठा greth_bd *bdp;
	काष्ठा sk_buff *skb, *newskb;
	पूर्णांक pkt_len;
	पूर्णांक bad, count = 0;
	u32 status, dma_addr;
	अचिन्हित दीर्घ flags;

	greth = netdev_priv(dev);

	क्रम (count = 0; count < limit; ++count) अणु

		bdp = greth->rx_bd_base + greth->rx_cur;
		skb = greth->rx_skbuff[greth->rx_cur];
		GRETH_REGSAVE(greth->regs->status, GRETH_INT_RE | GRETH_INT_RX);
		mb();
		status = greth_पढ़ो_bd(&bdp->stat);
		bad = 0;

		अगर (status & GRETH_BD_EN)
			अवरोध;

		/* Check status क्रम errors. */
		अगर (unlikely(status & GRETH_RXBD_STATUS)) अणु

			अगर (status & GRETH_RXBD_ERR_FT) अणु
				dev->stats.rx_length_errors++;
				bad = 1;
			पूर्ण अन्यथा अगर (status &
				   (GRETH_RXBD_ERR_AE | GRETH_RXBD_ERR_OE | GRETH_RXBD_ERR_LE)) अणु
				dev->stats.rx_frame_errors++;
				bad = 1;
			पूर्ण अन्यथा अगर (status & GRETH_RXBD_ERR_CRC) अणु
				dev->stats.rx_crc_errors++;
				bad = 1;
			पूर्ण
		पूर्ण

		/* Allocate new skb to replace current, not needed अगर the
		 * current skb can be reused */
		अगर (!bad && (newskb=netdev_alloc_skb(dev, MAX_FRAME_SIZE + NET_IP_ALIGN))) अणु
			skb_reserve(newskb, NET_IP_ALIGN);

			dma_addr = dma_map_single(greth->dev,
						      newskb->data,
						      MAX_FRAME_SIZE + NET_IP_ALIGN,
						      DMA_FROM_DEVICE);

			अगर (!dma_mapping_error(greth->dev, dma_addr)) अणु
				/* Process the incoming frame. */
				pkt_len = status & GRETH_BD_LEN;

				dma_unmap_single(greth->dev,
						 greth_पढ़ो_bd(&bdp->addr),
						 MAX_FRAME_SIZE + NET_IP_ALIGN,
						 DMA_FROM_DEVICE);

				अगर (netअगर_msg_pktdata(greth))
					greth_prपूर्णांक_rx_packet(phys_to_virt(greth_पढ़ो_bd(&bdp->addr)), pkt_len);

				skb_put(skb, pkt_len);

				अगर (dev->features & NETIF_F_RXCSUM && hw_checksummed(status))
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				अन्यथा
					skb_checksum_none_निश्चित(skb);

				skb->protocol = eth_type_trans(skb, dev);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
				netअगर_receive_skb(skb);

				greth->rx_skbuff[greth->rx_cur] = newskb;
				greth_ग_लिखो_bd(&bdp->addr, dma_addr);
			पूर्ण अन्यथा अणु
				अगर (net_ratelimit())
					dev_warn(greth->dev, "Could not create DMA mapping, dropping packet\n");
				dev_kमुक्त_skb(newskb);
				/* reusing current skb, so it is a drop */
				dev->stats.rx_dropped++;
			पूर्ण
		पूर्ण अन्यथा अगर (bad) अणु
			/* Bad Frame transfer, the skb is reused */
			dev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			/* Failed Allocating a new skb. This is rather stupid
			 * but the current "filled" skb is reused, as अगर
			 * transfer failure. One could argue that RX descriptor
			 * table handling should be भागided पूर्णांकo cleaning and
			 * filling as the TX part of the driver
			 */
			अगर (net_ratelimit())
				dev_warn(greth->dev, "Could not allocate SKB, dropping packet\n");
			/* reusing current skb, so it is a drop */
			dev->stats.rx_dropped++;
		पूर्ण

		status = GRETH_BD_EN | GRETH_BD_IE;
		अगर (greth->rx_cur == GRETH_RXBD_NUM_MASK) अणु
			status |= GRETH_BD_WR;
		पूर्ण

		wmb();
		greth_ग_लिखो_bd(&bdp->stat, status);
		spin_lock_irqsave(&greth->devlock, flags);
		greth_enable_rx(greth);
		spin_unlock_irqrestore(&greth->devlock, flags);
		greth->rx_cur = NEXT_RX(greth->rx_cur);
	पूर्ण

	वापस count;

पूर्ण

अटल पूर्णांक greth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा greth_निजी *greth;
	पूर्णांक work_करोne = 0;
	अचिन्हित दीर्घ flags;
	u32 mask, ctrl;
	greth = container_of(napi, काष्ठा greth_निजी, napi);

restart_txrx_poll:
	अगर (greth->gbit_mac) अणु
		greth_clean_tx_gbit(greth->netdev);
		work_करोne += greth_rx_gbit(greth->netdev, budget - work_करोne);
	पूर्ण अन्यथा अणु
		अगर (netअगर_queue_stopped(greth->netdev))
			greth_clean_tx(greth->netdev);
		work_करोne += greth_rx(greth->netdev, budget - work_करोne);
	पूर्ण

	अगर (work_करोne < budget) अणु

		spin_lock_irqsave(&greth->devlock, flags);

		ctrl = GRETH_REGLOAD(greth->regs->control);
		अगर ((greth->gbit_mac && (greth->tx_last != greth->tx_next)) ||
		    (!greth->gbit_mac && netअगर_queue_stopped(greth->netdev))) अणु
			GRETH_REGSAVE(greth->regs->control,
					ctrl | GRETH_TXI | GRETH_RXI);
			mask = GRETH_INT_RX | GRETH_INT_RE |
			       GRETH_INT_TX | GRETH_INT_TE;
		पूर्ण अन्यथा अणु
			GRETH_REGSAVE(greth->regs->control, ctrl | GRETH_RXI);
			mask = GRETH_INT_RX | GRETH_INT_RE;
		पूर्ण

		अगर (GRETH_REGLOAD(greth->regs->status) & mask) अणु
			GRETH_REGSAVE(greth->regs->control, ctrl);
			spin_unlock_irqrestore(&greth->devlock, flags);
			जाओ restart_txrx_poll;
		पूर्ण अन्यथा अणु
			napi_complete_करोne(napi, work_करोne);
			spin_unlock_irqrestore(&greth->devlock, flags);
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक greth_set_mac_add(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा greth_निजी *greth;
	काष्ठा greth_regs *regs;

	greth = netdev_priv(dev);
	regs = greth->regs;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	GRETH_REGSAVE(regs->esa_msb, dev->dev_addr[0] << 8 | dev->dev_addr[1]);
	GRETH_REGSAVE(regs->esa_lsb, dev->dev_addr[2] << 24 | dev->dev_addr[3] << 16 |
		      dev->dev_addr[4] << 8 | dev->dev_addr[5]);

	वापस 0;
पूर्ण

अटल u32 greth_hash_get_index(__u8 *addr)
अणु
	वापस (ether_crc(6, addr)) & 0x3F;
पूर्ण

अटल व्योम greth_set_hash_filter(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	काष्ठा greth_regs *regs = greth->regs;
	u32 mc_filter[2];
	अचिन्हित पूर्णांक bitnr;

	mc_filter[0] = mc_filter[1] = 0;

	netdev_क्रम_each_mc_addr(ha, dev) अणु
		bitnr = greth_hash_get_index(ha->addr);
		mc_filter[bitnr >> 5] |= 1 << (bitnr & 31);
	पूर्ण

	GRETH_REGSAVE(regs->hash_msb, mc_filter[1]);
	GRETH_REGSAVE(regs->hash_lsb, mc_filter[0]);
पूर्ण

अटल व्योम greth_set_multicast_list(काष्ठा net_device *dev)
अणु
	पूर्णांक cfg;
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	काष्ठा greth_regs *regs = greth->regs;

	cfg = GRETH_REGLOAD(regs->control);
	अगर (dev->flags & IFF_PROMISC)
		cfg |= GRETH_CTRL_PR;
	अन्यथा
		cfg &= ~GRETH_CTRL_PR;

	अगर (greth->multicast) अणु
		अगर (dev->flags & IFF_ALLMULTI) अणु
			GRETH_REGSAVE(regs->hash_msb, -1);
			GRETH_REGSAVE(regs->hash_lsb, -1);
			cfg |= GRETH_CTRL_MCEN;
			GRETH_REGSAVE(regs->control, cfg);
			वापस;
		पूर्ण

		अगर (netdev_mc_empty(dev)) अणु
			cfg &= ~GRETH_CTRL_MCEN;
			GRETH_REGSAVE(regs->control, cfg);
			वापस;
		पूर्ण

		/* Setup multicast filter */
		greth_set_hash_filter(dev);
		cfg |= GRETH_CTRL_MCEN;
	पूर्ण
	GRETH_REGSAVE(regs->control, cfg);
पूर्ण

अटल u32 greth_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	वापस greth->msg_enable;
पूर्ण

अटल व्योम greth_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	greth->msg_enable = value;
पूर्ण

अटल पूर्णांक greth_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस माप(काष्ठा greth_regs);
पूर्ण

अटल व्योम greth_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);

	strlcpy(info->driver, dev_driver_string(greth->dev),
		माप(info->driver));
	strlcpy(info->bus_info, greth->dev->bus->name, माप(info->bus_info));
पूर्ण

अटल व्योम greth_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	u32 __iomem *greth_regs = (u32 __iomem *) greth->regs;
	u32 *buff = p;

	क्रम (i = 0; i < माप(काष्ठा greth_regs) / माप(u32); i++)
		buff[i] = greth_पढ़ो_bd(&greth_regs[i]);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops greth_ethtool_ops = अणु
	.get_msglevel		= greth_get_msglevel,
	.set_msglevel		= greth_set_msglevel,
	.get_drvinfo		= greth_get_drvinfo,
	.get_regs_len           = greth_get_regs_len,
	.get_regs               = greth_get_regs,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
पूर्ण;

अटल काष्ठा net_device_ops greth_netdev_ops = अणु
	.nकरो_खोलो		= greth_खोलो,
	.nकरो_stop		= greth_बंद,
	.nकरो_start_xmit		= greth_start_xmit,
	.nकरो_set_mac_address	= greth_set_mac_add,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल अंतरभूत पूर्णांक रुको_क्रम_mdio(काष्ठा greth_निजी *greth)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + 4*HZ/100;
	जबतक (GRETH_REGLOAD(greth->regs->mdio) & GRETH_MII_BUSY) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक greth_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा greth_निजी *greth = bus->priv;
	पूर्णांक data;

	अगर (!रुको_क्रम_mdio(greth))
		वापस -EBUSY;

	GRETH_REGSAVE(greth->regs->mdio, ((phy & 0x1F) << 11) | ((reg & 0x1F) << 6) | 2);

	अगर (!रुको_क्रम_mdio(greth))
		वापस -EBUSY;

	अगर (!(GRETH_REGLOAD(greth->regs->mdio) & GRETH_MII_NVALID)) अणु
		data = (GRETH_REGLOAD(greth->regs->mdio) >> 16) & 0xFFFF;
		वापस data;

	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक greth_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg, u16 val)
अणु
	काष्ठा greth_निजी *greth = bus->priv;

	अगर (!रुको_क्रम_mdio(greth))
		वापस -EBUSY;

	GRETH_REGSAVE(greth->regs->mdio,
		      ((val & 0xFFFF) << 16) | ((phy & 0x1F) << 11) | ((reg & 0x1F) << 6) | 1);

	अगर (!रुको_क्रम_mdio(greth))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम greth_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	अचिन्हित दीर्घ flags;
	पूर्णांक status_change = 0;
	u32 ctrl;

	spin_lock_irqsave(&greth->devlock, flags);

	अगर (phydev->link) अणु

		अगर ((greth->speed != phydev->speed) || (greth->duplex != phydev->duplex)) अणु
			ctrl = GRETH_REGLOAD(greth->regs->control) &
			       ~(GRETH_CTRL_FD | GRETH_CTRL_SP | GRETH_CTRL_GB);

			अगर (phydev->duplex)
				ctrl |= GRETH_CTRL_FD;

			अगर (phydev->speed == SPEED_100)
				ctrl |= GRETH_CTRL_SP;
			अन्यथा अगर (phydev->speed == SPEED_1000)
				ctrl |= GRETH_CTRL_GB;

			GRETH_REGSAVE(greth->regs->control, ctrl);
			greth->speed = phydev->speed;
			greth->duplex = phydev->duplex;
			status_change = 1;
		पूर्ण
	पूर्ण

	अगर (phydev->link != greth->link) अणु
		अगर (!phydev->link) अणु
			greth->speed = 0;
			greth->duplex = -1;
		पूर्ण
		greth->link = phydev->link;

		status_change = 1;
	पूर्ण

	spin_unlock_irqrestore(&greth->devlock, flags);

	अगर (status_change) अणु
		अगर (phydev->link)
			pr_debug("%s: link up (%d/%s)\n",
				dev->name, phydev->speed,
				DUPLEX_FULL == phydev->duplex ? "Full" : "Half");
		अन्यथा
			pr_debug("%s: link down\n", dev->name);
	पूर्ण
पूर्ण

अटल पूर्णांक greth_mdio_probe(काष्ठा net_device *dev)
अणु
	काष्ठा greth_निजी *greth = netdev_priv(dev);
	काष्ठा phy_device *phy = शून्य;
	पूर्णांक ret;

	/* Find the first PHY */
	phy = phy_find_first(greth->mdio);

	अगर (!phy) अणु
		अगर (netअगर_msg_probe(greth))
			dev_err(&dev->dev, "no PHY found\n");
		वापस -ENXIO;
	पूर्ण

	ret = phy_connect_direct(dev, phy, &greth_link_change,
				 greth->gbit_mac ? PHY_INTERFACE_MODE_GMII : PHY_INTERFACE_MODE_MII);
	अगर (ret) अणु
		अगर (netअगर_msg_अगरup(greth))
			dev_err(&dev->dev, "could not attach to PHY\n");
		वापस ret;
	पूर्ण

	अगर (greth->gbit_mac)
		phy_set_max_speed(phy, SPEED_1000);
	अन्यथा
		phy_set_max_speed(phy, SPEED_100);

	linkmode_copy(phy->advertising, phy->supported);

	greth->link = 0;
	greth->speed = 0;
	greth->duplex = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक greth_mdio_init(काष्ठा greth_निजी *greth)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	काष्ठा net_device *ndev = greth->netdev;

	greth->mdio = mdiobus_alloc();
	अगर (!greth->mdio) अणु
		वापस -ENOMEM;
	पूर्ण

	greth->mdio->name = "greth-mdio";
	snम_लिखो(greth->mdio->id, MII_BUS_ID_SIZE, "%s-%d", greth->mdio->name, greth->irq);
	greth->mdio->पढ़ो = greth_mdio_पढ़ो;
	greth->mdio->ग_लिखो = greth_mdio_ग_लिखो;
	greth->mdio->priv = greth;

	ret = mdiobus_रेजिस्टर(greth->mdio);
	अगर (ret) अणु
		जाओ error;
	पूर्ण

	ret = greth_mdio_probe(greth->netdev);
	अगर (ret) अणु
		अगर (netअगर_msg_probe(greth))
			dev_err(&greth->netdev->dev, "failed to probe MDIO bus\n");
		जाओ unreg_mdio;
	पूर्ण

	phy_start(ndev->phydev);

	/* If Ethernet debug link is used make स्वतःneg happen right away */
	अगर (greth->edcl && greth_edcl == 1) अणु
		phy_start_aneg(ndev->phydev);
		समयout = jअगरfies + 6*HZ;
		जबतक (!phy_aneg_करोne(ndev->phydev) &&
		       समय_beक्रमe(jअगरfies, समयout)) अणु
		पूर्ण
		phy_पढ़ो_status(ndev->phydev);
		greth_link_change(greth->netdev);
	पूर्ण

	वापस 0;

unreg_mdio:
	mdiobus_unरेजिस्टर(greth->mdio);
error:
	mdiobus_मुक्त(greth->mdio);
	वापस ret;
पूर्ण

/* Initialize the GRETH MAC */
अटल पूर्णांक greth_of_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा greth_निजी *greth;
	काष्ठा greth_regs *regs;

	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक पंचांगp;
	अचिन्हित दीर्घ समयout;

	dev = alloc_etherdev(माप(काष्ठा greth_निजी));

	अगर (dev == शून्य)
		वापस -ENOMEM;

	greth = netdev_priv(dev);
	greth->netdev = dev;
	greth->dev = &ofdev->dev;

	अगर (greth_debug > 0)
		greth->msg_enable = greth_debug;
	अन्यथा
		greth->msg_enable = GRETH_DEF_MSG_ENABLE;

	spin_lock_init(&greth->devlock);

	greth->regs = of_ioremap(&ofdev->resource[0], 0,
				 resource_size(&ofdev->resource[0]),
				 "grlib-greth regs");

	अगर (greth->regs == शून्य) अणु
		अगर (netअगर_msg_probe(greth))
			dev_err(greth->dev, "ioremap failure.\n");
		err = -EIO;
		जाओ error1;
	पूर्ण

	regs = greth->regs;
	greth->irq = ofdev->archdata.irqs[0];

	dev_set_drvdata(greth->dev, dev);
	SET_NETDEV_DEV(dev, greth->dev);

	अगर (netअगर_msg_probe(greth))
		dev_dbg(greth->dev, "resetting controller.\n");

	/* Reset the controller. */
	GRETH_REGSAVE(regs->control, GRETH_RESET);

	/* Wait क्रम MAC to reset itself */
	समयout = jअगरfies + HZ/100;
	जबतक (GRETH_REGLOAD(regs->control) & GRETH_RESET) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			err = -EIO;
			अगर (netअगर_msg_probe(greth))
				dev_err(greth->dev, "timeout when waiting for reset.\n");
			जाओ error2;
		पूर्ण
	पूर्ण

	/* Get शेष PHY address  */
	greth->phyaddr = (GRETH_REGLOAD(regs->mdio) >> 11) & 0x1F;

	/* Check अगर we have GBIT capable MAC */
	पंचांगp = GRETH_REGLOAD(regs->control);
	greth->gbit_mac = (पंचांगp >> 27) & 1;

	/* Check क्रम multicast capability */
	greth->multicast = (पंचांगp >> 25) & 1;

	greth->edcl = (पंचांगp >> 31) & 1;

	/* If we have EDCL we disable the EDCL speed-duplex FSM so
	 * it करोesn't पूर्णांकerfere with the software */
	अगर (greth->edcl != 0)
		GRETH_REGORIN(regs->control, GRETH_CTRL_DISDUPLEX);

	/* Check अगर MAC can handle MDIO पूर्णांकerrupts */
	greth->mdio_पूर्णांक_en = (पंचांगp >> 26) & 1;

	err = greth_mdio_init(greth);
	अगर (err) अणु
		अगर (netअगर_msg_probe(greth))
			dev_err(greth->dev, "failed to register MDIO bus\n");
		जाओ error2;
	पूर्ण

	/* Allocate TX descriptor ring in coherent memory */
	greth->tx_bd_base = dma_alloc_coherent(greth->dev, 1024,
					       &greth->tx_bd_base_phys,
					       GFP_KERNEL);
	अगर (!greth->tx_bd_base) अणु
		err = -ENOMEM;
		जाओ error3;
	पूर्ण

	/* Allocate RX descriptor ring in coherent memory */
	greth->rx_bd_base = dma_alloc_coherent(greth->dev, 1024,
					       &greth->rx_bd_base_phys,
					       GFP_KERNEL);
	अगर (!greth->rx_bd_base) अणु
		err = -ENOMEM;
		जाओ error4;
	पूर्ण

	/* Get MAC address from: module param, OF property or ID prom */
	क्रम (i = 0; i < 6; i++) अणु
		अगर (macaddr[i] != 0)
			अवरोध;
	पूर्ण
	अगर (i == 6) अणु
		u8 addr[ETH_ALEN];

		err = of_get_mac_address(ofdev->dev.of_node, addr);
		अगर (!err) अणु
			क्रम (i = 0; i < 6; i++)
				macaddr[i] = (अचिन्हित पूर्णांक) addr[i];
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SPARC
			क्रम (i = 0; i < 6; i++)
				macaddr[i] = (अचिन्हित पूर्णांक) idprom->id_ethaddr[i];
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = macaddr[i];

	macaddr[5]++;

	अगर (!is_valid_ether_addr(&dev->dev_addr[0])) अणु
		अगर (netअगर_msg_probe(greth))
			dev_err(greth->dev, "no valid ethernet address, aborting.\n");
		err = -EINVAL;
		जाओ error5;
	पूर्ण

	GRETH_REGSAVE(regs->esa_msb, dev->dev_addr[0] << 8 | dev->dev_addr[1]);
	GRETH_REGSAVE(regs->esa_lsb, dev->dev_addr[2] << 24 | dev->dev_addr[3] << 16 |
		      dev->dev_addr[4] << 8 | dev->dev_addr[5]);

	/* Clear all pending पूर्णांकerrupts except PHY irq */
	GRETH_REGSAVE(regs->status, 0xFF);

	अगर (greth->gbit_mac) अणु
		dev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM |
			NETIF_F_RXCSUM;
		dev->features = dev->hw_features | NETIF_F_HIGHDMA;
		greth_netdev_ops.nकरो_start_xmit = greth_start_xmit_gbit;
	पूर्ण

	अगर (greth->multicast) अणु
		greth_netdev_ops.nकरो_set_rx_mode = greth_set_multicast_list;
		dev->flags |= IFF_MULTICAST;
	पूर्ण अन्यथा अणु
		dev->flags &= ~IFF_MULTICAST;
	पूर्ण

	dev->netdev_ops = &greth_netdev_ops;
	dev->ethtool_ops = &greth_ethtool_ops;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		अगर (netअगर_msg_probe(greth))
			dev_err(greth->dev, "netdevice registration failed.\n");
		जाओ error5;
	पूर्ण

	/* setup NAPI */
	netअगर_napi_add(dev, &greth->napi, greth_poll, 64);

	वापस 0;

error5:
	dma_मुक्त_coherent(greth->dev, 1024, greth->rx_bd_base, greth->rx_bd_base_phys);
error4:
	dma_मुक्त_coherent(greth->dev, 1024, greth->tx_bd_base, greth->tx_bd_base_phys);
error3:
	mdiobus_unरेजिस्टर(greth->mdio);
error2:
	of_iounmap(&ofdev->resource[0], greth->regs, resource_size(&ofdev->resource[0]));
error1:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक greth_of_हटाओ(काष्ठा platक्रमm_device *of_dev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(of_dev);
	काष्ठा greth_निजी *greth = netdev_priv(ndev);

	/* Free descriptor areas */
	dma_मुक्त_coherent(&of_dev->dev, 1024, greth->rx_bd_base, greth->rx_bd_base_phys);

	dma_मुक्त_coherent(&of_dev->dev, 1024, greth->tx_bd_base, greth->tx_bd_base_phys);

	अगर (ndev->phydev)
		phy_stop(ndev->phydev);
	mdiobus_unरेजिस्टर(greth->mdio);

	unरेजिस्टर_netdev(ndev);
	मुक्त_netdev(ndev);

	of_iounmap(&of_dev->resource[0], greth->regs, resource_size(&of_dev->resource[0]));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id greth_of_match[] = अणु
	अणु
	 .name = "GAISLER_ETHMAC",
	 पूर्ण,
	अणु
	 .name = "01_01d",
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, greth_of_match);

अटल काष्ठा platक्रमm_driver greth_of_driver = अणु
	.driver = अणु
		.name = "grlib-greth",
		.of_match_table = greth_of_match,
	पूर्ण,
	.probe = greth_of_probe,
	.हटाओ = greth_of_हटाओ,
पूर्ण;

module_platक्रमm_driver(greth_of_driver);

MODULE_AUTHOR("Aeroflex Gaisler AB.");
MODULE_DESCRIPTION("Aeroflex Gaisler Ethernet MAC driver");
MODULE_LICENSE("GPL");
