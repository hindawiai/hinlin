<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* drivers/net/ethernet/मुक्तscale/gianfar.c
 *
 * Gianfar Ethernet Driver
 * This driver is deचिन्हित क्रम the non-CPM ethernet controllers
 * on the 85xx and 83xx family of पूर्णांकegrated processors
 * Based on 8260_io/fcc_enet.c
 *
 * Author: Andy Fleming
 * Maपूर्णांकainer: Kumar Gala
 * Modअगरier: Sandeep Gopalpet <sandeep.kumar@मुक्तscale.com>
 *
 * Copyright 2002-2009, 2011-2013 Freescale Semiconductor, Inc.
 * Copyright 2007 MontaVista Software, Inc.
 *
 *  Gianfar:  AKA Lambda Draconis, "Dragon"
 *  RA 11 31 24.2
 *  Dec +69 19 52
 *  V 3.84
 *  B-V +1.62
 *
 *  Theory of operation
 *
 *  The driver is initialized through of_device. Configuration inक्रमmation
 *  is thereक्रमe conveyed through an OF-style device tree.
 *
 *  The Gianfar Ethernet Controller uses a ring of buffer
 *  descriptors.  The beginning is indicated by a रेजिस्टर
 *  poपूर्णांकing to the physical address of the start of the ring.
 *  The end is determined by a "wrap" bit being set in the
 *  last descriptor of the ring.
 *
 *  When a packet is received, the RXF bit in the
 *  IEVENT रेजिस्टर is set, triggering an पूर्णांकerrupt when the
 *  corresponding bit in the IMASK रेजिस्टर is also set (अगर
 *  पूर्णांकerrupt coalescing is active, then the पूर्णांकerrupt may not
 *  happen immediately, but will रुको until either a set number
 *  of frames or amount of समय have passed).  In NAPI, the
 *  पूर्णांकerrupt handler will संकेत there is work to be करोne, and
 *  निकास. This method will start at the last known empty
 *  descriptor, and process every subsequent descriptor until there
 *  are none left with data (NAPI will stop after a set number of
 *  packets to give समय to other tasks, but will eventually
 *  process all the packets).  The data arrives inside a
 *  pre-allocated skb, and so after the skb is passed up to the
 *  stack, a new skb must be allocated, and the address field in
 *  the buffer descriptor must be updated to indicate this new
 *  skb.
 *
 *  When the kernel requests that a packet be transmitted, the
 *  driver starts where it left off last समय, and poपूर्णांकs the
 *  descriptor at the buffer which was passed in.  The driver
 *  then inक्रमms the DMA engine that there are packets पढ़ोy to
 *  be transmitted.  Once the controller is finished transmitting
 *  the packet, an पूर्णांकerrupt may be triggered (under the same
 *  conditions as क्रम reception, but depending on the TXF bit).
 *  The driver then cleans up the buffer.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/in.h>
#समावेश <linux/net_tstamp.h>

#समावेश <यंत्र/पन.स>
#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/mpc85xx.h>
#पूर्ण_अगर
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>

#समावेश "gianfar.h"

#घोषणा TX_TIMEOUT      (5*HZ)

MODULE_AUTHOR("Freescale Semiconductor, Inc");
MODULE_DESCRIPTION("Gianfar Ethernet Driver");
MODULE_LICENSE("GPL");

अटल व्योम gfar_init_rxbdp(काष्ठा gfar_priv_rx_q *rx_queue, काष्ठा rxbd8 *bdp,
			    dma_addr_t buf)
अणु
	u32 lstatus;

	bdp->bufPtr = cpu_to_be32(buf);

	lstatus = BD_LFLAG(RXBD_EMPTY | RXBD_INTERRUPT);
	अगर (bdp == rx_queue->rx_bd_base + rx_queue->rx_ring_size - 1)
		lstatus |= BD_LFLAG(RXBD_WRAP);

	gfar_wmb();

	bdp->lstatus = cpu_to_be32(lstatus);
पूर्ण

अटल व्योम gfar_init_tx_rx_base(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 __iomem *baddr;
	पूर्णांक i;

	baddr = &regs->tbase0;
	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		gfar_ग_लिखो(baddr, priv->tx_queue[i]->tx_bd_dma_base);
		baddr += 2;
	पूर्ण

	baddr = &regs->rbase0;
	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		gfar_ग_लिखो(baddr, priv->rx_queue[i]->rx_bd_dma_base);
		baddr += 2;
	पूर्ण
पूर्ण

अटल व्योम gfar_init_rqprm(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 __iomem *baddr;
	पूर्णांक i;

	baddr = &regs->rqprm0;
	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		gfar_ग_लिखो(baddr, priv->rx_queue[i]->rx_ring_size |
			   (DEFAULT_RX_LFC_THR << FBTHR_SHIFT));
		baddr++;
	पूर्ण
पूर्ण

अटल व्योम gfar_rx_offload_en(काष्ठा gfar_निजी *priv)
अणु
	/* set this when rx hw offload (TOE) functions are being used */
	priv->uses_rxfcb = 0;

	अगर (priv->ndev->features & (NETIF_F_RXCSUM | NETIF_F_HW_VLAN_CTAG_RX))
		priv->uses_rxfcb = 1;

	अगर (priv->hwts_rx_en || priv->rx_filer_enable)
		priv->uses_rxfcb = 1;
पूर्ण

अटल व्योम gfar_mac_rx_config(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 rctrl = 0;

	अगर (priv->rx_filer_enable) अणु
		rctrl |= RCTRL_FILREN | RCTRL_PRSDEP_INIT;
		/* Program the RIR0 reg with the required distribution */
		gfar_ग_लिखो(&regs->rir0, DEFAULT_2RXQ_RIR0);
	पूर्ण

	/* Restore PROMISC mode */
	अगर (priv->ndev->flags & IFF_PROMISC)
		rctrl |= RCTRL_PROM;

	अगर (priv->ndev->features & NETIF_F_RXCSUM)
		rctrl |= RCTRL_CHECKSUMMING;

	अगर (priv->extended_hash)
		rctrl |= RCTRL_EXTHASH | RCTRL_EMEN;

	अगर (priv->padding) अणु
		rctrl &= ~RCTRL_PAL_MASK;
		rctrl |= RCTRL_PADDING(priv->padding);
	पूर्ण

	/* Enable HW समय stamping अगर requested from user space */
	अगर (priv->hwts_rx_en)
		rctrl |= RCTRL_PRSDEP_INIT | RCTRL_TS_ENABLE;

	अगर (priv->ndev->features & NETIF_F_HW_VLAN_CTAG_RX)
		rctrl |= RCTRL_VLEX | RCTRL_PRSDEP_INIT;

	/* Clear the LFC bit */
	gfar_ग_लिखो(&regs->rctrl, rctrl);
	/* Init flow control threshold values */
	gfar_init_rqprm(priv);
	gfar_ग_लिखो(&regs->ptv, DEFAULT_LFC_PTVVAL);
	rctrl |= RCTRL_LFC;

	/* Init rctrl based on our settings */
	gfar_ग_लिखो(&regs->rctrl, rctrl);
पूर्ण

अटल व्योम gfar_mac_tx_config(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tctrl = 0;

	अगर (priv->ndev->features & NETIF_F_IP_CSUM)
		tctrl |= TCTRL_INIT_CSUM;

	अगर (priv->prio_sched_en)
		tctrl |= TCTRL_TXSCHED_PRIO;
	अन्यथा अणु
		tctrl |= TCTRL_TXSCHED_WRRS;
		gfar_ग_लिखो(&regs->tr03wt, DEFAULT_WRRS_WEIGHT);
		gfar_ग_लिखो(&regs->tr47wt, DEFAULT_WRRS_WEIGHT);
	पूर्ण

	अगर (priv->ndev->features & NETIF_F_HW_VLAN_CTAG_TX)
		tctrl |= TCTRL_VLINS;

	gfar_ग_लिखो(&regs->tctrl, tctrl);
पूर्ण

अटल व्योम gfar_configure_coalescing(काष्ठा gfar_निजी *priv,
			       अचिन्हित दीर्घ tx_mask, अचिन्हित दीर्घ rx_mask)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 __iomem *baddr;

	अगर (priv->mode == MQ_MG_MODE) अणु
		पूर्णांक i = 0;

		baddr = &regs->txic0;
		क्रम_each_set_bit(i, &tx_mask, priv->num_tx_queues) अणु
			gfar_ग_लिखो(baddr + i, 0);
			अगर (likely(priv->tx_queue[i]->txcoalescing))
				gfar_ग_लिखो(baddr + i, priv->tx_queue[i]->txic);
		पूर्ण

		baddr = &regs->rxic0;
		क्रम_each_set_bit(i, &rx_mask, priv->num_rx_queues) अणु
			gfar_ग_लिखो(baddr + i, 0);
			अगर (likely(priv->rx_queue[i]->rxcoalescing))
				gfar_ग_लिखो(baddr + i, priv->rx_queue[i]->rxic);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Backward compatible हाल -- even अगर we enable
		 * multiple queues, there's only single reg to program
		 */
		gfar_ग_लिखो(&regs->txic, 0);
		अगर (likely(priv->tx_queue[0]->txcoalescing))
			gfar_ग_लिखो(&regs->txic, priv->tx_queue[0]->txic);

		gfar_ग_लिखो(&regs->rxic, 0);
		अगर (unlikely(priv->rx_queue[0]->rxcoalescing))
			gfar_ग_लिखो(&regs->rxic, priv->rx_queue[0]->rxic);
	पूर्ण
पूर्ण

अटल व्योम gfar_configure_coalescing_all(काष्ठा gfar_निजी *priv)
अणु
	gfar_configure_coalescing(priv, 0xFF, 0xFF);
पूर्ण

अटल काष्ठा net_device_stats *gfar_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ rx_packets = 0, rx_bytes = 0, rx_dropped = 0;
	अचिन्हित दीर्घ tx_packets = 0, tx_bytes = 0;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		rx_packets += priv->rx_queue[i]->stats.rx_packets;
		rx_bytes   += priv->rx_queue[i]->stats.rx_bytes;
		rx_dropped += priv->rx_queue[i]->stats.rx_dropped;
	पूर्ण

	dev->stats.rx_packets = rx_packets;
	dev->stats.rx_bytes   = rx_bytes;
	dev->stats.rx_dropped = rx_dropped;

	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		tx_bytes += priv->tx_queue[i]->stats.tx_bytes;
		tx_packets += priv->tx_queue[i]->stats.tx_packets;
	पूर्ण

	dev->stats.tx_bytes   = tx_bytes;
	dev->stats.tx_packets = tx_packets;

	वापस &dev->stats;
पूर्ण

/* Set the appropriate hash bit क्रम the given addr */
/* The algorithm works like so:
 * 1) Take the Destination Address (ie the multicast address), and
 * करो a CRC on it (little endian), and reverse the bits of the
 * result.
 * 2) Use the 8 most signअगरicant bits as a hash पूर्णांकo a 256-entry
 * table.  The table is controlled through 8 32-bit रेजिस्टरs:
 * gaddr0-7.  gaddr0's MSB is entry 0, and gaddr7's LSB is
 * gaddr7.  This means that the 3 most signअगरicant bits in the
 * hash index which gaddr रेजिस्टर to use, and the 5 other bits
 * indicate which bit (assuming an IBM numbering scheme, which
 * क्रम PowerPC (पंचांग) is usually the हाल) in the रेजिस्टर holds
 * the entry.
 */
अटल व्योम gfar_set_hash_क्रम_addr(काष्ठा net_device *dev, u8 *addr)
अणु
	u32 tempval;
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	u32 result = ether_crc(ETH_ALEN, addr);
	पूर्णांक width = priv->hash_width;
	u8 whichbit = (result >> (32 - width)) & 0x1f;
	u8 whichreg = result >> (32 - width + 5);
	u32 value = (1 << (31-whichbit));

	tempval = gfar_पढ़ो(priv->hash_regs[whichreg]);
	tempval |= value;
	gfar_ग_लिखो(priv->hash_regs[whichreg], tempval);
पूर्ण

/* There are multiple MAC Address रेजिस्टर pairs on some controllers
 * This function sets the numth pair to a given address
 */
अटल व्योम gfar_set_mac_क्रम_addr(काष्ठा net_device *dev, पूर्णांक num,
				  स्थिर u8 *addr)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;
	u32 __iomem *macptr = &regs->macstnaddr1;

	macptr += num*2;

	/* For a station address of 0x12345678ABCD in transmission
	 * order (BE), MACnADDR1 is set to 0xCDAB7856 and
	 * MACnADDR2 is set to 0x34120000.
	 */
	tempval = (addr[5] << 24) | (addr[4] << 16) |
		  (addr[3] << 8)  |  addr[2];

	gfar_ग_लिखो(macptr, tempval);

	tempval = (addr[1] << 24) | (addr[0] << 16);

	gfar_ग_लिखो(macptr+1, tempval);
पूर्ण

अटल पूर्णांक gfar_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret;

	ret = eth_mac_addr(dev, p);
	अगर (ret)
		वापस ret;

	gfar_set_mac_क्रम_addr(dev, 0, dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम gfar_पूर्णांकs_disable(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < priv->num_grps; i++) अणु
		काष्ठा gfar __iomem *regs = priv->gfargrp[i].regs;
		/* Clear IEVENT */
		gfar_ग_लिखो(&regs->ievent, IEVENT_INIT_CLEAR);

		/* Initialize IMASK */
		gfar_ग_लिखो(&regs->imask, IMASK_INIT_CLEAR);
	पूर्ण
पूर्ण

अटल व्योम gfar_पूर्णांकs_enable(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < priv->num_grps; i++) अणु
		काष्ठा gfar __iomem *regs = priv->gfargrp[i].regs;
		/* Unmask the पूर्णांकerrupts we look क्रम */
		gfar_ग_लिखो(&regs->imask, IMASK_DEFAULT);
	पूर्ण
पूर्ण

अटल पूर्णांक gfar_alloc_tx_queues(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		priv->tx_queue[i] = kzalloc(माप(काष्ठा gfar_priv_tx_q),
					    GFP_KERNEL);
		अगर (!priv->tx_queue[i])
			वापस -ENOMEM;

		priv->tx_queue[i]->tx_skbuff = शून्य;
		priv->tx_queue[i]->qindex = i;
		priv->tx_queue[i]->dev = priv->ndev;
		spin_lock_init(&(priv->tx_queue[i]->txlock));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gfar_alloc_rx_queues(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		priv->rx_queue[i] = kzalloc(माप(काष्ठा gfar_priv_rx_q),
					    GFP_KERNEL);
		अगर (!priv->rx_queue[i])
			वापस -ENOMEM;

		priv->rx_queue[i]->qindex = i;
		priv->rx_queue[i]->ndev = priv->ndev;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gfar_मुक्त_tx_queues(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_tx_queues; i++)
		kमुक्त(priv->tx_queue[i]);
पूर्ण

अटल व्योम gfar_मुक्त_rx_queues(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_queues; i++)
		kमुक्त(priv->rx_queue[i]);
पूर्ण

अटल व्योम unmap_group_regs(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAXGROUPS; i++)
		अगर (priv->gfargrp[i].regs)
			iounmap(priv->gfargrp[i].regs);
पूर्ण

अटल व्योम मुक्त_gfar_dev(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < priv->num_grps; i++)
		क्रम (j = 0; j < GFAR_NUM_IRQS; j++) अणु
			kमुक्त(priv->gfargrp[i].irqinfo[j]);
			priv->gfargrp[i].irqinfo[j] = शून्य;
		पूर्ण

	मुक्त_netdev(priv->ndev);
पूर्ण

अटल व्योम disable_napi(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_grps; i++) अणु
		napi_disable(&priv->gfargrp[i].napi_rx);
		napi_disable(&priv->gfargrp[i].napi_tx);
	पूर्ण
पूर्ण

अटल व्योम enable_napi(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_grps; i++) अणु
		napi_enable(&priv->gfargrp[i].napi_rx);
		napi_enable(&priv->gfargrp[i].napi_tx);
	पूर्ण
पूर्ण

अटल पूर्णांक gfar_parse_group(काष्ठा device_node *np,
			    काष्ठा gfar_निजी *priv, स्थिर अक्षर *model)
अणु
	काष्ठा gfar_priv_grp *grp = &priv->gfargrp[priv->num_grps];
	पूर्णांक i;

	क्रम (i = 0; i < GFAR_NUM_IRQS; i++) अणु
		grp->irqinfo[i] = kzalloc(माप(काष्ठा gfar_irqinfo),
					  GFP_KERNEL);
		अगर (!grp->irqinfo[i])
			वापस -ENOMEM;
	पूर्ण

	grp->regs = of_iomap(np, 0);
	अगर (!grp->regs)
		वापस -ENOMEM;

	gfar_irq(grp, TX)->irq = irq_of_parse_and_map(np, 0);

	/* If we aren't the FEC we have multiple पूर्णांकerrupts */
	अगर (model && strहालcmp(model, "FEC")) अणु
		gfar_irq(grp, RX)->irq = irq_of_parse_and_map(np, 1);
		gfar_irq(grp, ER)->irq = irq_of_parse_and_map(np, 2);
		अगर (!gfar_irq(grp, TX)->irq ||
		    !gfar_irq(grp, RX)->irq ||
		    !gfar_irq(grp, ER)->irq)
			वापस -EINVAL;
	पूर्ण

	grp->priv = priv;
	spin_lock_init(&grp->grplock);
	अगर (priv->mode == MQ_MG_MODE) अणु
		/* One Q per पूर्णांकerrupt group: Q0 to G0, Q1 to G1 */
		grp->rx_bit_map = (DEFAULT_MAPPING >> priv->num_grps);
		grp->tx_bit_map = (DEFAULT_MAPPING >> priv->num_grps);
	पूर्ण अन्यथा अणु
		grp->rx_bit_map = 0xFF;
		grp->tx_bit_map = 0xFF;
	पूर्ण

	/* bit_map's MSB is q0 (from q0 to q7) but, क्रम_each_set_bit parses
	 * right to left, so we need to revert the 8 bits to get the q index
	 */
	grp->rx_bit_map = bitrev8(grp->rx_bit_map);
	grp->tx_bit_map = bitrev8(grp->tx_bit_map);

	/* Calculate RSTAT, TSTAT, RQUEUE and TQUEUE values,
	 * also assign queues to groups
	 */
	क्रम_each_set_bit(i, &grp->rx_bit_map, priv->num_rx_queues) अणु
		अगर (!grp->rx_queue)
			grp->rx_queue = priv->rx_queue[i];
		grp->num_rx_queues++;
		grp->rstat |= (RSTAT_CLEAR_RHALT >> i);
		priv->rqueue |= ((RQUEUE_EN0 | RQUEUE_EX0) >> i);
		priv->rx_queue[i]->grp = grp;
	पूर्ण

	क्रम_each_set_bit(i, &grp->tx_bit_map, priv->num_tx_queues) अणु
		अगर (!grp->tx_queue)
			grp->tx_queue = priv->tx_queue[i];
		grp->num_tx_queues++;
		grp->tstat |= (TSTAT_CLEAR_THALT >> i);
		priv->tqueue |= (TQUEUE_EN0 >> i);
		priv->tx_queue[i]->grp = grp;
	पूर्ण

	priv->num_grps++;

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_of_group_count(काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	पूर्णांक num = 0;

	क्रम_each_available_child_of_node(np, child)
		अगर (of_node_name_eq(child, "queue-group"))
			num++;

	वापस num;
पूर्ण

/* Reads the controller's रेजिस्टरs to determine what पूर्णांकerface
 * connects it to the PHY.
 */
अटल phy_पूर्णांकerface_t gfar_get_पूर्णांकerface(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 ecntrl;

	ecntrl = gfar_पढ़ो(&regs->ecntrl);

	अगर (ecntrl & ECNTRL_SGMII_MODE)
		वापस PHY_INTERFACE_MODE_SGMII;

	अगर (ecntrl & ECNTRL_TBI_MODE) अणु
		अगर (ecntrl & ECNTRL_REDUCED_MODE)
			वापस PHY_INTERFACE_MODE_RTBI;
		अन्यथा
			वापस PHY_INTERFACE_MODE_TBI;
	पूर्ण

	अगर (ecntrl & ECNTRL_REDUCED_MODE) अणु
		अगर (ecntrl & ECNTRL_REDUCED_MII_MODE) अणु
			वापस PHY_INTERFACE_MODE_RMII;
		पूर्ण
		अन्यथा अणु
			phy_पूर्णांकerface_t पूर्णांकerface = priv->पूर्णांकerface;

			/* This isn't स्वतःdetected right now, so it must
			 * be set by the device tree or platक्रमm code.
			 */
			अगर (पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
				वापस PHY_INTERFACE_MODE_RGMII_ID;

			वापस PHY_INTERFACE_MODE_RGMII;
		पूर्ण
	पूर्ण

	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_GIGABIT)
		वापस PHY_INTERFACE_MODE_GMII;

	वापस PHY_INTERFACE_MODE_MII;
पूर्ण

अटल पूर्णांक gfar_of_init(काष्ठा platक्रमm_device *ofdev, काष्ठा net_device **pdev)
अणु
	स्थिर अक्षर *model;
	पूर्णांक err = 0, i;
	phy_पूर्णांकerface_t पूर्णांकerface;
	काष्ठा net_device *dev = शून्य;
	काष्ठा gfar_निजी *priv = शून्य;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा device_node *child = शून्य;
	u32 stash_len = 0;
	u32 stash_idx = 0;
	अचिन्हित पूर्णांक num_tx_qs, num_rx_qs;
	अचिन्हित लघु mode;

	अगर (!np)
		वापस -ENODEV;

	अगर (of_device_is_compatible(np, "fsl,etsec2"))
		mode = MQ_MG_MODE;
	अन्यथा
		mode = SQ_SG_MODE;

	अगर (mode == SQ_SG_MODE) अणु
		num_tx_qs = 1;
		num_rx_qs = 1;
	पूर्ण अन्यथा अणु /* MQ_MG_MODE */
		/* get the actual number of supported groups */
		अचिन्हित पूर्णांक num_grps = gfar_of_group_count(np);

		अगर (num_grps == 0 || num_grps > MAXGROUPS) अणु
			dev_err(&ofdev->dev, "Invalid # of int groups(%d)\n",
				num_grps);
			pr_err("Cannot do alloc_etherdev, aborting\n");
			वापस -EINVAL;
		पूर्ण

		num_tx_qs = num_grps; /* one txq per पूर्णांक group */
		num_rx_qs = num_grps; /* one rxq per पूर्णांक group */
	पूर्ण

	अगर (num_tx_qs > MAX_TX_QS) अणु
		pr_err("num_tx_qs(=%d) greater than MAX_TX_QS(=%d)\n",
		       num_tx_qs, MAX_TX_QS);
		pr_err("Cannot do alloc_etherdev, aborting\n");
		वापस -EINVAL;
	पूर्ण

	अगर (num_rx_qs > MAX_RX_QS) अणु
		pr_err("num_rx_qs(=%d) greater than MAX_RX_QS(=%d)\n",
		       num_rx_qs, MAX_RX_QS);
		pr_err("Cannot do alloc_etherdev, aborting\n");
		वापस -EINVAL;
	पूर्ण

	*pdev = alloc_etherdev_mq(माप(*priv), num_tx_qs);
	dev = *pdev;
	अगर (शून्य == dev)
		वापस -ENOMEM;

	priv = netdev_priv(dev);
	priv->ndev = dev;

	priv->mode = mode;

	priv->num_tx_queues = num_tx_qs;
	netअगर_set_real_num_rx_queues(dev, num_rx_qs);
	priv->num_rx_queues = num_rx_qs;

	err = gfar_alloc_tx_queues(priv);
	अगर (err)
		जाओ tx_alloc_failed;

	err = gfar_alloc_rx_queues(priv);
	अगर (err)
		जाओ rx_alloc_failed;

	err = of_property_पढ़ो_string(np, "model", &model);
	अगर (err) अणु
		pr_err("Device model property missing, aborting\n");
		जाओ rx_alloc_failed;
	पूर्ण

	/* Init Rx queue filer rule set linked list */
	INIT_LIST_HEAD(&priv->rx_list.list);
	priv->rx_list.count = 0;
	mutex_init(&priv->rx_queue_access);

	क्रम (i = 0; i < MAXGROUPS; i++)
		priv->gfargrp[i].regs = शून्य;

	/* Parse and initialize group specअगरic inक्रमmation */
	अगर (priv->mode == MQ_MG_MODE) अणु
		क्रम_each_available_child_of_node(np, child) अणु
			अगर (!of_node_name_eq(child, "queue-group"))
				जारी;

			err = gfar_parse_group(child, priv, model);
			अगर (err) अणु
				of_node_put(child);
				जाओ err_grp_init;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* SQ_SG_MODE */
		err = gfar_parse_group(np, priv, model);
		अगर (err)
			जाओ err_grp_init;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "bd-stash")) अणु
		priv->device_flags |= FSL_GIANFAR_DEV_HAS_BD_STASHING;
		priv->bd_stash_en = 1;
	पूर्ण

	err = of_property_पढ़ो_u32(np, "rx-stash-len", &stash_len);

	अगर (err == 0)
		priv->rx_stash_size = stash_len;

	err = of_property_पढ़ो_u32(np, "rx-stash-idx", &stash_idx);

	अगर (err == 0)
		priv->rx_stash_index = stash_idx;

	अगर (stash_len || stash_idx)
		priv->device_flags |= FSL_GIANFAR_DEV_HAS_BUF_STASHING;

	err = of_get_mac_address(np, dev->dev_addr);
	अगर (err) अणु
		eth_hw_addr_अक्रमom(dev);
		dev_info(&ofdev->dev, "Using random MAC address: %pM\n", dev->dev_addr);
	पूर्ण

	अगर (model && !strहालcmp(model, "TSEC"))
		priv->device_flags |= FSL_GIANFAR_DEV_HAS_GIGABIT |
				     FSL_GIANFAR_DEV_HAS_COALESCE |
				     FSL_GIANFAR_DEV_HAS_RMON |
				     FSL_GIANFAR_DEV_HAS_MULTI_INTR;

	अगर (model && !strहालcmp(model, "eTSEC"))
		priv->device_flags |= FSL_GIANFAR_DEV_HAS_GIGABIT |
				     FSL_GIANFAR_DEV_HAS_COALESCE |
				     FSL_GIANFAR_DEV_HAS_RMON |
				     FSL_GIANFAR_DEV_HAS_MULTI_INTR |
				     FSL_GIANFAR_DEV_HAS_CSUM |
				     FSL_GIANFAR_DEV_HAS_VLAN |
				     FSL_GIANFAR_DEV_HAS_MAGIC_PACKET |
				     FSL_GIANFAR_DEV_HAS_EXTENDED_HASH |
				     FSL_GIANFAR_DEV_HAS_TIMER |
				     FSL_GIANFAR_DEV_HAS_RX_खाताR;

	/* Use PHY connection type from the DT node अगर one is specअगरied there.
	 * rgmii-id really needs to be specअगरied. Other types can be
	 * detected by hardware
	 */
	err = of_get_phy_mode(np, &पूर्णांकerface);
	अगर (!err)
		priv->पूर्णांकerface = पूर्णांकerface;
	अन्यथा
		priv->पूर्णांकerface = gfar_get_पूर्णांकerface(dev);

	अगर (of_find_property(np, "fsl,magic-packet", शून्य))
		priv->device_flags |= FSL_GIANFAR_DEV_HAS_MAGIC_PACKET;

	अगर (of_get_property(np, "fsl,wake-on-filer", शून्य))
		priv->device_flags |= FSL_GIANFAR_DEV_HAS_WAKE_ON_खाताR;

	priv->phy_node = of_parse_phandle(np, "phy-handle", 0);

	/* In the हाल of a fixed PHY, the DT node associated
	 * to the PHY is the Ethernet MAC DT node.
	 */
	अगर (!priv->phy_node && of_phy_is_fixed_link(np)) अणु
		err = of_phy_रेजिस्टर_fixed_link(np);
		अगर (err)
			जाओ err_grp_init;

		priv->phy_node = of_node_get(np);
	पूर्ण

	/* Find the TBI PHY.  If it's not there, we don't support SGMII */
	priv->tbi_node = of_parse_phandle(np, "tbi-handle", 0);

	वापस 0;

err_grp_init:
	unmap_group_regs(priv);
rx_alloc_failed:
	gfar_मुक्त_rx_queues(priv);
tx_alloc_failed:
	gfar_मुक्त_tx_queues(priv);
	मुक्त_gfar_dev(priv);
	वापस err;
पूर्ण

अटल u32 cluster_entry_per_class(काष्ठा gfar_निजी *priv, u32 rqfar,
				   u32 class)
अणु
	u32 rqfpr = FPR_खाताR_MASK;
	u32 rqfcr = 0x0;

	rqfar--;
	rqfcr = RQFCR_CLE | RQFCR_PID_MASK | RQFCR_CMP_EXACT;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	gfar_ग_लिखो_filer(priv, rqfar, rqfcr, rqfpr);

	rqfar--;
	rqfcr = RQFCR_CMP_NOMATCH;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	gfar_ग_लिखो_filer(priv, rqfar, rqfcr, rqfpr);

	rqfar--;
	rqfcr = RQFCR_CMP_EXACT | RQFCR_PID_PARSE | RQFCR_CLE | RQFCR_AND;
	rqfpr = class;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	gfar_ग_लिखो_filer(priv, rqfar, rqfcr, rqfpr);

	rqfar--;
	rqfcr = RQFCR_CMP_EXACT | RQFCR_PID_MASK | RQFCR_AND;
	rqfpr = class;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	gfar_ग_लिखो_filer(priv, rqfar, rqfcr, rqfpr);

	वापस rqfar;
पूर्ण

अटल व्योम gfar_init_filer_table(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i = 0x0;
	u32 rqfar = MAX_खाताR_IDX;
	u32 rqfcr = 0x0;
	u32 rqfpr = FPR_खाताR_MASK;

	/* Default rule */
	rqfcr = RQFCR_CMP_MATCH;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	gfar_ग_लिखो_filer(priv, rqfar, rqfcr, rqfpr);

	rqfar = cluster_entry_per_class(priv, rqfar, RQFPR_IPV6);
	rqfar = cluster_entry_per_class(priv, rqfar, RQFPR_IPV6 | RQFPR_UDP);
	rqfar = cluster_entry_per_class(priv, rqfar, RQFPR_IPV6 | RQFPR_TCP);
	rqfar = cluster_entry_per_class(priv, rqfar, RQFPR_IPV4);
	rqfar = cluster_entry_per_class(priv, rqfar, RQFPR_IPV4 | RQFPR_UDP);
	rqfar = cluster_entry_per_class(priv, rqfar, RQFPR_IPV4 | RQFPR_TCP);

	/* cur_filer_idx indicated the first non-masked rule */
	priv->cur_filer_idx = rqfar;

	/* Rest are masked rules */
	rqfcr = RQFCR_CMP_NOMATCH;
	क्रम (i = 0; i < rqfar; i++) अणु
		priv->ftp_rqfcr[i] = rqfcr;
		priv->ftp_rqfpr[i] = rqfpr;
		gfar_ग_लिखो_filer(priv, i, rqfcr, rqfpr);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC
अटल व्योम __gfar_detect_errata_83xx(काष्ठा gfar_निजी *priv)
अणु
	अचिन्हित पूर्णांक pvr = mfspr(SPRN_PVR);
	अचिन्हित पूर्णांक svr = mfspr(SPRN_SVR);
	अचिन्हित पूर्णांक mod = (svr >> 16) & 0xfff6; /* w/o E suffix */
	अचिन्हित पूर्णांक rev = svr & 0xffff;

	/* MPC8313 Rev 2.0 and higher; All MPC837x */
	अगर ((pvr == 0x80850010 && mod == 0x80b0 && rev >= 0x0020) ||
	    (pvr == 0x80861010 && (mod & 0xfff9) == 0x80c0))
		priv->errata |= GFAR_ERRATA_74;

	/* MPC8313 and MPC837x all rev */
	अगर ((pvr == 0x80850010 && mod == 0x80b0) ||
	    (pvr == 0x80861010 && (mod & 0xfff9) == 0x80c0))
		priv->errata |= GFAR_ERRATA_76;

	/* MPC8313 Rev < 2.0 */
	अगर (pvr == 0x80850010 && mod == 0x80b0 && rev < 0x0020)
		priv->errata |= GFAR_ERRATA_12;
पूर्ण

अटल व्योम __gfar_detect_errata_85xx(काष्ठा gfar_निजी *priv)
अणु
	अचिन्हित पूर्णांक svr = mfspr(SPRN_SVR);

	अगर ((SVR_SOC_VER(svr) == SVR_8548) && (SVR_REV(svr) == 0x20))
		priv->errata |= GFAR_ERRATA_12;
	/* P2020/P1010 Rev 1; MPC8548 Rev 2 */
	अगर (((SVR_SOC_VER(svr) == SVR_P2020) && (SVR_REV(svr) < 0x20)) ||
	    ((SVR_SOC_VER(svr) == SVR_P2010) && (SVR_REV(svr) < 0x20)) ||
	    ((SVR_SOC_VER(svr) == SVR_8548) && (SVR_REV(svr) < 0x31)))
		priv->errata |= GFAR_ERRATA_76; /* aka eTSEC 20 */
पूर्ण
#पूर्ण_अगर

अटल व्योम gfar_detect_errata(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा device *dev = &priv->ofdev->dev;

	/* no plans to fix */
	priv->errata |= GFAR_ERRATA_A002;

#अगर_घोषित CONFIG_PPC
	अगर (pvr_version_is(PVR_VER_E500V1) || pvr_version_is(PVR_VER_E500V2))
		__gfar_detect_errata_85xx(priv);
	अन्यथा /* non-mpc85xx parts, i.e. e300 core based */
		__gfar_detect_errata_83xx(priv);
#पूर्ण_अगर

	अगर (priv->errata)
		dev_info(dev, "enabled errata workarounds, flags: 0x%x\n",
			 priv->errata);
पूर्ण

अटल व्योम gfar_init_addr_hash_table(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;

	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_EXTENDED_HASH) अणु
		priv->extended_hash = 1;
		priv->hash_width = 9;

		priv->hash_regs[0] = &regs->igaddr0;
		priv->hash_regs[1] = &regs->igaddr1;
		priv->hash_regs[2] = &regs->igaddr2;
		priv->hash_regs[3] = &regs->igaddr3;
		priv->hash_regs[4] = &regs->igaddr4;
		priv->hash_regs[5] = &regs->igaddr5;
		priv->hash_regs[6] = &regs->igaddr6;
		priv->hash_regs[7] = &regs->igaddr7;
		priv->hash_regs[8] = &regs->gaddr0;
		priv->hash_regs[9] = &regs->gaddr1;
		priv->hash_regs[10] = &regs->gaddr2;
		priv->hash_regs[11] = &regs->gaddr3;
		priv->hash_regs[12] = &regs->gaddr4;
		priv->hash_regs[13] = &regs->gaddr5;
		priv->hash_regs[14] = &regs->gaddr6;
		priv->hash_regs[15] = &regs->gaddr7;

	पूर्ण अन्यथा अणु
		priv->extended_hash = 0;
		priv->hash_width = 8;

		priv->hash_regs[0] = &regs->gaddr0;
		priv->hash_regs[1] = &regs->gaddr1;
		priv->hash_regs[2] = &regs->gaddr2;
		priv->hash_regs[3] = &regs->gaddr3;
		priv->hash_regs[4] = &regs->gaddr4;
		priv->hash_regs[5] = &regs->gaddr5;
		priv->hash_regs[6] = &regs->gaddr6;
		priv->hash_regs[7] = &regs->gaddr7;
	पूर्ण
पूर्ण

अटल पूर्णांक __gfar_is_rx_idle(काष्ठा gfar_निजी *priv)
अणु
	u32 res;

	/* Normaly TSEC should not hang on GRS commands, so we should
	 * actually रुको क्रम IEVENT_GRSC flag.
	 */
	अगर (!gfar_has_errata(priv, GFAR_ERRATA_A002))
		वापस 0;

	/* Read the eTSEC रेजिस्टर at offset 0xD1C. If bits 7-14 are
	 * the same as bits 23-30, the eTSEC Rx is assumed to be idle
	 * and the Rx can be safely reset.
	 */
	res = gfar_पढ़ो((व्योम __iomem *)priv->gfargrp[0].regs + 0xd1c);
	res &= 0x7f807f80;
	अगर ((res & 0xffff) == (res >> 16))
		वापस 1;

	वापस 0;
पूर्ण

/* Halt the receive and transmit queues */
अटल व्योम gfar_halt_nodisable(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक stopped;

	gfar_पूर्णांकs_disable(priv);

	अगर (gfar_is_dma_stopped(priv))
		वापस;

	/* Stop the DMA, and रुको क्रम it to stop */
	tempval = gfar_पढ़ो(&regs->dmactrl);
	tempval |= (DMACTRL_GRS | DMACTRL_GTS);
	gfar_ग_लिखो(&regs->dmactrl, tempval);

retry:
	समयout = 1000;
	जबतक (!(stopped = gfar_is_dma_stopped(priv)) && समयout) अणु
		cpu_relax();
		समयout--;
	पूर्ण

	अगर (!समयout)
		stopped = gfar_is_dma_stopped(priv);

	अगर (!stopped && !gfar_is_rx_dma_stopped(priv) &&
	    !__gfar_is_rx_idle(priv))
		जाओ retry;
पूर्ण

/* Halt the receive and transmit queues */
अटल व्योम gfar_halt(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;

	/* Dissable the Rx/Tx hw queues */
	gfar_ग_लिखो(&regs->rqueue, 0);
	gfar_ग_लिखो(&regs->tqueue, 0);

	mdelay(10);

	gfar_halt_nodisable(priv);

	/* Disable Rx/Tx DMA */
	tempval = gfar_पढ़ो(&regs->maccfg1);
	tempval &= ~(MACCFG1_RX_EN | MACCFG1_TX_EN);
	gfar_ग_लिखो(&regs->maccfg1, tempval);
पूर्ण

अटल व्योम मुक्त_skb_tx_queue(काष्ठा gfar_priv_tx_q *tx_queue)
अणु
	काष्ठा txbd8 *txbdp;
	काष्ठा gfar_निजी *priv = netdev_priv(tx_queue->dev);
	पूर्णांक i, j;

	txbdp = tx_queue->tx_bd_base;

	क्रम (i = 0; i < tx_queue->tx_ring_size; i++) अणु
		अगर (!tx_queue->tx_skbuff[i])
			जारी;

		dma_unmap_single(priv->dev, be32_to_cpu(txbdp->bufPtr),
				 be16_to_cpu(txbdp->length), DMA_TO_DEVICE);
		txbdp->lstatus = 0;
		क्रम (j = 0; j < skb_shinfo(tx_queue->tx_skbuff[i])->nr_frags;
		     j++) अणु
			txbdp++;
			dma_unmap_page(priv->dev, be32_to_cpu(txbdp->bufPtr),
				       be16_to_cpu(txbdp->length),
				       DMA_TO_DEVICE);
		पूर्ण
		txbdp++;
		dev_kमुक्त_skb_any(tx_queue->tx_skbuff[i]);
		tx_queue->tx_skbuff[i] = शून्य;
	पूर्ण
	kमुक्त(tx_queue->tx_skbuff);
	tx_queue->tx_skbuff = शून्य;
पूर्ण

अटल व्योम मुक्त_skb_rx_queue(काष्ठा gfar_priv_rx_q *rx_queue)
अणु
	पूर्णांक i;

	काष्ठा rxbd8 *rxbdp = rx_queue->rx_bd_base;

	dev_kमुक्त_skb(rx_queue->skb);

	क्रम (i = 0; i < rx_queue->rx_ring_size; i++) अणु
		काष्ठा	gfar_rx_buff *rxb = &rx_queue->rx_buff[i];

		rxbdp->lstatus = 0;
		rxbdp->bufPtr = 0;
		rxbdp++;

		अगर (!rxb->page)
			जारी;

		dma_unmap_page(rx_queue->dev, rxb->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
		__मुक्त_page(rxb->page);

		rxb->page = शून्य;
	पूर्ण

	kमुक्त(rx_queue->rx_buff);
	rx_queue->rx_buff = शून्य;
पूर्ण

/* If there are any tx skbs or rx skbs still around, मुक्त them.
 * Then मुक्त tx_skbuff and rx_skbuff
 */
अटल व्योम मुक्त_skb_resources(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar_priv_tx_q *tx_queue = शून्य;
	काष्ठा gfar_priv_rx_q *rx_queue = शून्य;
	पूर्णांक i;

	/* Go through all the buffer descriptors and मुक्त their data buffers */
	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq;

		tx_queue = priv->tx_queue[i];
		txq = netdev_get_tx_queue(tx_queue->dev, tx_queue->qindex);
		अगर (tx_queue->tx_skbuff)
			मुक्त_skb_tx_queue(tx_queue);
		netdev_tx_reset_queue(txq);
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		rx_queue = priv->rx_queue[i];
		अगर (rx_queue->rx_buff)
			मुक्त_skb_rx_queue(rx_queue);
	पूर्ण

	dma_मुक्त_coherent(priv->dev,
			  माप(काष्ठा txbd8) * priv->total_tx_ring_size +
			  माप(काष्ठा rxbd8) * priv->total_rx_ring_size,
			  priv->tx_queue[0]->tx_bd_base,
			  priv->tx_queue[0]->tx_bd_dma_base);
पूर्ण

व्योम stop_gfar(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	netअगर_tx_stop_all_queues(dev);

	smp_mb__beक्रमe_atomic();
	set_bit(GFAR_DOWN, &priv->state);
	smp_mb__after_atomic();

	disable_napi(priv);

	/* disable पूर्णांकs and gracefully shut करोwn Rx/Tx DMA */
	gfar_halt(priv);

	phy_stop(dev->phydev);

	मुक्त_skb_resources(priv);
पूर्ण

अटल व्योम gfar_start(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;
	पूर्णांक i = 0;

	/* Enable Rx/Tx hw queues */
	gfar_ग_लिखो(&regs->rqueue, priv->rqueue);
	gfar_ग_लिखो(&regs->tqueue, priv->tqueue);

	/* Initialize DMACTRL to have WWR and WOP */
	tempval = gfar_पढ़ो(&regs->dmactrl);
	tempval |= DMACTRL_INIT_SETTINGS;
	gfar_ग_लिखो(&regs->dmactrl, tempval);

	/* Make sure we aren't stopped */
	tempval = gfar_पढ़ो(&regs->dmactrl);
	tempval &= ~(DMACTRL_GRS | DMACTRL_GTS);
	gfar_ग_लिखो(&regs->dmactrl, tempval);

	क्रम (i = 0; i < priv->num_grps; i++) अणु
		regs = priv->gfargrp[i].regs;
		/* Clear THLT/RHLT, so that the DMA starts polling now */
		gfar_ग_लिखो(&regs->tstat, priv->gfargrp[i].tstat);
		gfar_ग_लिखो(&regs->rstat, priv->gfargrp[i].rstat);
	पूर्ण

	/* Enable Rx/Tx DMA */
	tempval = gfar_पढ़ो(&regs->maccfg1);
	tempval |= (MACCFG1_RX_EN | MACCFG1_TX_EN);
	gfar_ग_लिखो(&regs->maccfg1, tempval);

	gfar_पूर्णांकs_enable(priv);

	netअगर_trans_update(priv->ndev); /* prevent tx समयout */
पूर्ण

अटल bool gfar_new_page(काष्ठा gfar_priv_rx_q *rxq, काष्ठा gfar_rx_buff *rxb)
अणु
	काष्ठा page *page;
	dma_addr_t addr;

	page = dev_alloc_page();
	अगर (unlikely(!page))
		वापस false;

	addr = dma_map_page(rxq->dev, page, 0, PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(rxq->dev, addr))) अणु
		__मुक्त_page(page);

		वापस false;
	पूर्ण

	rxb->dma = addr;
	rxb->page = page;
	rxb->page_offset = 0;

	वापस true;
पूर्ण

अटल व्योम gfar_rx_alloc_err(काष्ठा gfar_priv_rx_q *rx_queue)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(rx_queue->ndev);
	काष्ठा gfar_extra_stats *estats = &priv->extra_stats;

	netdev_err(rx_queue->ndev, "Can't alloc RX buffers\n");
	atomic64_inc(&estats->rx_alloc_err);
पूर्ण

अटल व्योम gfar_alloc_rx_buffs(काष्ठा gfar_priv_rx_q *rx_queue,
				पूर्णांक alloc_cnt)
अणु
	काष्ठा rxbd8 *bdp;
	काष्ठा gfar_rx_buff *rxb;
	पूर्णांक i;

	i = rx_queue->next_to_use;
	bdp = &rx_queue->rx_bd_base[i];
	rxb = &rx_queue->rx_buff[i];

	जबतक (alloc_cnt--) अणु
		/* try reuse page */
		अगर (unlikely(!rxb->page)) अणु
			अगर (unlikely(!gfar_new_page(rx_queue, rxb))) अणु
				gfar_rx_alloc_err(rx_queue);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Setup the new RxBD */
		gfar_init_rxbdp(rx_queue, bdp,
				rxb->dma + rxb->page_offset + RXBUF_ALIGNMENT);

		/* Update to the next poपूर्णांकer */
		bdp++;
		rxb++;

		अगर (unlikely(++i == rx_queue->rx_ring_size)) अणु
			i = 0;
			bdp = rx_queue->rx_bd_base;
			rxb = rx_queue->rx_buff;
		पूर्ण
	पूर्ण

	rx_queue->next_to_use = i;
	rx_queue->next_to_alloc = i;
पूर्ण

अटल व्योम gfar_init_bds(काष्ठा net_device *ndev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(ndev);
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	काष्ठा gfar_priv_tx_q *tx_queue = शून्य;
	काष्ठा gfar_priv_rx_q *rx_queue = शून्य;
	काष्ठा txbd8 *txbdp;
	u32 __iomem *rfbptr;
	पूर्णांक i, j;

	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		tx_queue = priv->tx_queue[i];
		/* Initialize some variables in our dev काष्ठाure */
		tx_queue->num_txbdमुक्त = tx_queue->tx_ring_size;
		tx_queue->dirty_tx = tx_queue->tx_bd_base;
		tx_queue->cur_tx = tx_queue->tx_bd_base;
		tx_queue->skb_curtx = 0;
		tx_queue->skb_dirtytx = 0;

		/* Initialize Transmit Descriptor Ring */
		txbdp = tx_queue->tx_bd_base;
		क्रम (j = 0; j < tx_queue->tx_ring_size; j++) अणु
			txbdp->lstatus = 0;
			txbdp->bufPtr = 0;
			txbdp++;
		पूर्ण

		/* Set the last descriptor in the ring to indicate wrap */
		txbdp--;
		txbdp->status = cpu_to_be16(be16_to_cpu(txbdp->status) |
					    TXBD_WRAP);
	पूर्ण

	rfbptr = &regs->rfbptr0;
	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		rx_queue = priv->rx_queue[i];

		rx_queue->next_to_clean = 0;
		rx_queue->next_to_use = 0;
		rx_queue->next_to_alloc = 0;

		/* make sure next_to_clean != next_to_use after this
		 * by leaving at least 1 unused descriptor
		 */
		gfar_alloc_rx_buffs(rx_queue, gfar_rxbd_unused(rx_queue));

		rx_queue->rfbptr = rfbptr;
		rfbptr += 2;
	पूर्ण
पूर्ण

अटल पूर्णांक gfar_alloc_skb_resources(काष्ठा net_device *ndev)
अणु
	व्योम *vaddr;
	dma_addr_t addr;
	पूर्णांक i, j;
	काष्ठा gfar_निजी *priv = netdev_priv(ndev);
	काष्ठा device *dev = priv->dev;
	काष्ठा gfar_priv_tx_q *tx_queue = शून्य;
	काष्ठा gfar_priv_rx_q *rx_queue = शून्य;

	priv->total_tx_ring_size = 0;
	क्रम (i = 0; i < priv->num_tx_queues; i++)
		priv->total_tx_ring_size += priv->tx_queue[i]->tx_ring_size;

	priv->total_rx_ring_size = 0;
	क्रम (i = 0; i < priv->num_rx_queues; i++)
		priv->total_rx_ring_size += priv->rx_queue[i]->rx_ring_size;

	/* Allocate memory क्रम the buffer descriptors */
	vaddr = dma_alloc_coherent(dev,
				   (priv->total_tx_ring_size *
				    माप(काष्ठा txbd8)) +
				   (priv->total_rx_ring_size *
				    माप(काष्ठा rxbd8)),
				   &addr, GFP_KERNEL);
	अगर (!vaddr)
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		tx_queue = priv->tx_queue[i];
		tx_queue->tx_bd_base = vaddr;
		tx_queue->tx_bd_dma_base = addr;
		tx_queue->dev = ndev;
		/* enet DMA only understands physical addresses */
		addr  += माप(काष्ठा txbd8) * tx_queue->tx_ring_size;
		vaddr += माप(काष्ठा txbd8) * tx_queue->tx_ring_size;
	पूर्ण

	/* Start the rx descriptor ring where the tx ring leaves off */
	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		rx_queue = priv->rx_queue[i];
		rx_queue->rx_bd_base = vaddr;
		rx_queue->rx_bd_dma_base = addr;
		rx_queue->ndev = ndev;
		rx_queue->dev = dev;
		addr  += माप(काष्ठा rxbd8) * rx_queue->rx_ring_size;
		vaddr += माप(काष्ठा rxbd8) * rx_queue->rx_ring_size;
	पूर्ण

	/* Setup the skbuff rings */
	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		tx_queue = priv->tx_queue[i];
		tx_queue->tx_skbuff =
			kदो_स्मृति_array(tx_queue->tx_ring_size,
				      माप(*tx_queue->tx_skbuff),
				      GFP_KERNEL);
		अगर (!tx_queue->tx_skbuff)
			जाओ cleanup;

		क्रम (j = 0; j < tx_queue->tx_ring_size; j++)
			tx_queue->tx_skbuff[j] = शून्य;
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		rx_queue = priv->rx_queue[i];
		rx_queue->rx_buff = kसुस्मृति(rx_queue->rx_ring_size,
					    माप(*rx_queue->rx_buff),
					    GFP_KERNEL);
		अगर (!rx_queue->rx_buff)
			जाओ cleanup;
	पूर्ण

	gfar_init_bds(ndev);

	वापस 0;

cleanup:
	मुक्त_skb_resources(priv);
	वापस -ENOMEM;
पूर्ण

/* Bring the controller up and running */
पूर्णांक startup_gfar(काष्ठा net_device *ndev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(ndev);
	पूर्णांक err;

	gfar_mac_reset(priv);

	err = gfar_alloc_skb_resources(ndev);
	अगर (err)
		वापस err;

	gfar_init_tx_rx_base(priv);

	smp_mb__beक्रमe_atomic();
	clear_bit(GFAR_DOWN, &priv->state);
	smp_mb__after_atomic();

	/* Start Rx/Tx DMA and enable the पूर्णांकerrupts */
	gfar_start(priv);

	/* क्रमce link state update after mac reset */
	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	phy_start(ndev->phydev);

	enable_napi(priv);

	netअगर_tx_wake_all_queues(ndev);

	वापस 0;
पूर्ण

अटल u32 gfar_get_flowctrl_cfg(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा phy_device *phydev = ndev->phydev;
	u32 val = 0;

	अगर (!phydev->duplex)
		वापस val;

	अगर (!priv->छोड़ो_aneg_en) अणु
		अगर (priv->tx_छोड़ो_en)
			val |= MACCFG1_TX_FLOW;
		अगर (priv->rx_छोड़ो_en)
			val |= MACCFG1_RX_FLOW;
	पूर्ण अन्यथा अणु
		u16 lcl_adv, rmt_adv;
		u8 flowctrl;
		/* get link partner capabilities */
		rmt_adv = 0;
		अगर (phydev->छोड़ो)
			rmt_adv = LPA_PAUSE_CAP;
		अगर (phydev->asym_छोड़ो)
			rmt_adv |= LPA_PAUSE_ASYM;

		lcl_adv = linkmode_adv_to_lcl_adv_t(phydev->advertising);
		flowctrl = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);
		अगर (flowctrl & FLOW_CTRL_TX)
			val |= MACCFG1_TX_FLOW;
		अगर (flowctrl & FLOW_CTRL_RX)
			val |= MACCFG1_RX_FLOW;
	पूर्ण

	वापस val;
पूर्ण

अटल noअंतरभूत व्योम gfar_update_link_state(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा phy_device *phydev = ndev->phydev;
	काष्ठा gfar_priv_rx_q *rx_queue = शून्य;
	पूर्णांक i;

	अगर (unlikely(test_bit(GFAR_RESETTING, &priv->state)))
		वापस;

	अगर (phydev->link) अणु
		u32 tempval1 = gfar_पढ़ो(&regs->maccfg1);
		u32 tempval = gfar_पढ़ो(&regs->maccfg2);
		u32 ecntrl = gfar_पढ़ो(&regs->ecntrl);
		u32 tx_flow_oldval = (tempval1 & MACCFG1_TX_FLOW);

		अगर (phydev->duplex != priv->oldduplex) अणु
			अगर (!(phydev->duplex))
				tempval &= ~(MACCFG2_FULL_DUPLEX);
			अन्यथा
				tempval |= MACCFG2_FULL_DUPLEX;

			priv->oldduplex = phydev->duplex;
		पूर्ण

		अगर (phydev->speed != priv->oldspeed) अणु
			चयन (phydev->speed) अणु
			हाल 1000:
				tempval =
				    ((tempval & ~(MACCFG2_IF)) | MACCFG2_GMII);

				ecntrl &= ~(ECNTRL_R100);
				अवरोध;
			हाल 100:
			हाल 10:
				tempval =
				    ((tempval & ~(MACCFG2_IF)) | MACCFG2_MII);

				/* Reduced mode distinguishes
				 * between 10 and 100
				 */
				अगर (phydev->speed == SPEED_100)
					ecntrl |= ECNTRL_R100;
				अन्यथा
					ecntrl &= ~(ECNTRL_R100);
				अवरोध;
			शेष:
				netअगर_warn(priv, link, priv->ndev,
					   "Ack!  Speed (%d) is not 10/100/1000!\n",
					   phydev->speed);
				अवरोध;
			पूर्ण

			priv->oldspeed = phydev->speed;
		पूर्ण

		tempval1 &= ~(MACCFG1_TX_FLOW | MACCFG1_RX_FLOW);
		tempval1 |= gfar_get_flowctrl_cfg(priv);

		/* Turn last मुक्त buffer recording on */
		अगर ((tempval1 & MACCFG1_TX_FLOW) && !tx_flow_oldval) अणु
			क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
				u32 bdp_dma;

				rx_queue = priv->rx_queue[i];
				bdp_dma = gfar_rxbd_dma_lastमुक्त(rx_queue);
				gfar_ग_लिखो(rx_queue->rfbptr, bdp_dma);
			पूर्ण

			priv->tx_actual_en = 1;
		पूर्ण

		अगर (unlikely(!(tempval1 & MACCFG1_TX_FLOW) && tx_flow_oldval))
			priv->tx_actual_en = 0;

		gfar_ग_लिखो(&regs->maccfg1, tempval1);
		gfar_ग_लिखो(&regs->maccfg2, tempval);
		gfar_ग_लिखो(&regs->ecntrl, ecntrl);

		अगर (!priv->oldlink)
			priv->oldlink = 1;

	पूर्ण अन्यथा अगर (priv->oldlink) अणु
		priv->oldlink = 0;
		priv->oldspeed = 0;
		priv->oldduplex = -1;
	पूर्ण

	अगर (netअगर_msg_link(priv))
		phy_prपूर्णांक_status(phydev);
पूर्ण

/* Called every समय the controller might need to be made
 * aware of new link state.  The PHY code conveys this
 * inक्रमmation through variables in the phydev काष्ठाure, and this
 * function converts those variables पूर्णांकo the appropriate
 * रेजिस्टर values, and can bring करोwn the device अगर needed.
 */
अटल व्योम adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;

	अगर (unlikely(phydev->link != priv->oldlink ||
		     (phydev->link && (phydev->duplex != priv->oldduplex ||
				       phydev->speed != priv->oldspeed))))
		gfar_update_link_state(priv);
पूर्ण

/* Initialize TBI PHY पूर्णांकerface क्रम communicating with the
 * SERDES lynx PHY on the chip.  We communicate with this PHY
 * through the MDIO bus on each controller, treating it as a
 * "normal" PHY at the address found in the TBIPA रेजिस्टर.  We assume
 * that the TBIPA रेजिस्टर is valid.  Either the MDIO bus code will set
 * it to a value that करोesn't conflict with other PHYs on the bus, or the
 * value करोesn't matter, as there are no other PHYs on the bus.
 */
अटल व्योम gfar_configure_serdes(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा phy_device *tbiphy;

	अगर (!priv->tbi_node) अणु
		dev_warn(&dev->dev, "error: SGMII mode requires that the "
				    "device tree specify a tbi-handle\n");
		वापस;
	पूर्ण

	tbiphy = of_phy_find_device(priv->tbi_node);
	अगर (!tbiphy) अणु
		dev_err(&dev->dev, "error: Could not get TBI device\n");
		वापस;
	पूर्ण

	/* If the link is alपढ़ोy up, we must alपढ़ोy be ok, and करोn't need to
	 * configure and reset the TBI<->SerDes link.  Maybe U-Boot configured
	 * everything क्रम us?  Resetting it takes the link करोwn and requires
	 * several seconds क्रम it to come back.
	 */
	अगर (phy_पढ़ो(tbiphy, MII_BMSR) & BMSR_LSTATUS) अणु
		put_device(&tbiphy->mdio.dev);
		वापस;
	पूर्ण

	/* Single clk mode, mii mode off(क्रम serdes communication) */
	phy_ग_लिखो(tbiphy, MII_TBICON, TBICON_CLK_SELECT);

	phy_ग_लिखो(tbiphy, MII_ADVERTISE,
		  ADVERTISE_1000XFULL | ADVERTISE_1000XPAUSE |
		  ADVERTISE_1000XPSE_ASYM);

	phy_ग_लिखो(tbiphy, MII_BMCR,
		  BMCR_ANENABLE | BMCR_ANRESTART | BMCR_FULLDPLX |
		  BMCR_SPEED1000);

	put_device(&tbiphy->mdio.dev);
पूर्ण

/* Initializes driver's PHY state, and attaches to the PHY.
 * Returns 0 on success.
 */
अटल पूर्णांक init_phy(काष्ठा net_device *dev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	phy_पूर्णांकerface_t पूर्णांकerface = priv->पूर्णांकerface;
	काष्ठा phy_device *phydev;
	काष्ठा ethtool_eee edata;

	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, mask);
	linkmode_set_bit(ETHTOOL_LINK_MODE_MII_BIT, mask);
	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_GIGABIT)
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT, mask);

	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	phydev = of_phy_connect(dev, priv->phy_node, &adjust_link, 0,
				पूर्णांकerface);
	अगर (!phydev) अणु
		dev_err(&dev->dev, "could not attach to PHY\n");
		वापस -ENODEV;
	पूर्ण

	अगर (पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		gfar_configure_serdes(dev);

	/* Remove any features not supported by the controller */
	linkmode_and(phydev->supported, phydev->supported, mask);
	linkmode_copy(phydev->advertising, phydev->supported);

	/* Add support क्रम flow control */
	phy_support_asym_छोड़ो(phydev);

	/* disable EEE स्वतःneg, EEE not supported by eTSEC */
	स_रखो(&edata, 0, माप(काष्ठा ethtool_eee));
	phy_ethtool_set_eee(phydev, &edata);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा txfcb *gfar_add_fcb(काष्ठा sk_buff *skb)
अणु
	काष्ठा txfcb *fcb = skb_push(skb, GMAC_FCB_LEN);

	स_रखो(fcb, 0, GMAC_FCB_LEN);

	वापस fcb;
पूर्ण

अटल अंतरभूत व्योम gfar_tx_checksum(काष्ठा sk_buff *skb, काष्ठा txfcb *fcb,
				    पूर्णांक fcb_length)
अणु
	/* If we're here, it's a IP packet with a TCP or UDP
	 * payload.  We set it to checksum, using a pseuकरो-header
	 * we provide
	 */
	u8 flags = TXFCB_DEFAULT;

	/* Tell the controller what the protocol is
	 * And provide the alपढ़ोy calculated phcs
	 */
	अगर (ip_hdr(skb)->protocol == IPPROTO_UDP) अणु
		flags |= TXFCB_UDP;
		fcb->phcs = (__क्रमce __be16)(udp_hdr(skb)->check);
	पूर्ण अन्यथा
		fcb->phcs = (__क्रमce __be16)(tcp_hdr(skb)->check);

	/* l3os is the distance between the start of the
	 * frame (skb->data) and the start of the IP hdr.
	 * l4os is the distance between the start of the
	 * l3 hdr and the l4 hdr
	 */
	fcb->l3os = (u8)(skb_network_offset(skb) - fcb_length);
	fcb->l4os = skb_network_header_len(skb);

	fcb->flags = flags;
पूर्ण

अटल अंतरभूत व्योम gfar_tx_vlan(काष्ठा sk_buff *skb, काष्ठा txfcb *fcb)
अणु
	fcb->flags |= TXFCB_VLN;
	fcb->vlctl = cpu_to_be16(skb_vlan_tag_get(skb));
पूर्ण

अटल अंतरभूत काष्ठा txbd8 *skip_txbd(काष्ठा txbd8 *bdp, पूर्णांक stride,
				      काष्ठा txbd8 *base, पूर्णांक ring_size)
अणु
	काष्ठा txbd8 *new_bd = bdp + stride;

	वापस (new_bd >= (base + ring_size)) ? (new_bd - ring_size) : new_bd;
पूर्ण

अटल अंतरभूत काष्ठा txbd8 *next_txbd(काष्ठा txbd8 *bdp, काष्ठा txbd8 *base,
				      पूर्णांक ring_size)
अणु
	वापस skip_txbd(bdp, 1, base, ring_size);
पूर्ण

/* eTSEC12: csum generation not supported क्रम some fcb offsets */
अटल अंतरभूत bool gfar_csum_errata_12(काष्ठा gfar_निजी *priv,
				       अचिन्हित दीर्घ fcb_addr)
अणु
	वापस (gfar_has_errata(priv, GFAR_ERRATA_12) &&
	       (fcb_addr % 0x20) > 0x18);
पूर्ण

/* eTSEC76: csum generation क्रम frames larger than 2500 may
 * cause excess delays beक्रमe start of transmission
 */
अटल अंतरभूत bool gfar_csum_errata_76(काष्ठा gfar_निजी *priv,
				       अचिन्हित पूर्णांक len)
अणु
	वापस (gfar_has_errata(priv, GFAR_ERRATA_76) &&
	       (len > 2500));
पूर्ण

/* This is called by the kernel when a frame is पढ़ोy क्रम transmission.
 * It is poपूर्णांकed to by the dev->hard_start_xmit function poपूर्णांकer
 */
अटल netdev_tx_t gfar_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा gfar_priv_tx_q *tx_queue = शून्य;
	काष्ठा netdev_queue *txq;
	काष्ठा gfar __iomem *regs = शून्य;
	काष्ठा txfcb *fcb = शून्य;
	काष्ठा txbd8 *txbdp, *txbdp_start, *base, *txbdp_tstamp = शून्य;
	u32 lstatus;
	skb_frag_t *frag;
	पूर्णांक i, rq = 0;
	पूर्णांक करो_tstamp, करो_csum, करो_vlan;
	u32 bufaddr;
	अचिन्हित पूर्णांक nr_frags, nr_txbds, bytes_sent, fcb_len = 0;

	rq = skb->queue_mapping;
	tx_queue = priv->tx_queue[rq];
	txq = netdev_get_tx_queue(dev, rq);
	base = tx_queue->tx_bd_base;
	regs = tx_queue->grp->regs;

	करो_csum = (CHECKSUM_PARTIAL == skb->ip_summed);
	करो_vlan = skb_vlan_tag_present(skb);
	करो_tstamp = (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
		    priv->hwts_tx_en;

	अगर (करो_csum || करो_vlan)
		fcb_len = GMAC_FCB_LEN;

	/* check अगर समय stamp should be generated */
	अगर (unlikely(करो_tstamp))
		fcb_len = GMAC_FCB_LEN + GMAC_TXPAL_LEN;

	/* make space क्रम additional header when fcb is needed */
	अगर (fcb_len) अणु
		अगर (unlikely(skb_cow_head(skb, fcb_len))) अणु
			dev->stats.tx_errors++;
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	/* total number of fragments in the SKB */
	nr_frags = skb_shinfo(skb)->nr_frags;

	/* calculate the required number of TxBDs क्रम this skb */
	अगर (unlikely(करो_tstamp))
		nr_txbds = nr_frags + 2;
	अन्यथा
		nr_txbds = nr_frags + 1;

	/* check अगर there is space to queue this packet */
	अगर (nr_txbds > tx_queue->num_txbdमुक्त) अणु
		/* no space, stop the queue */
		netअगर_tx_stop_queue(txq);
		dev->stats.tx_fअगरo_errors++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Update transmit stats */
	bytes_sent = skb->len;
	tx_queue->stats.tx_bytes += bytes_sent;
	/* keep Tx bytes on wire क्रम BQL accounting */
	GFAR_CB(skb)->bytes_sent = bytes_sent;
	tx_queue->stats.tx_packets++;

	txbdp = txbdp_start = tx_queue->cur_tx;
	lstatus = be32_to_cpu(txbdp->lstatus);

	/* Add TxPAL between FCB and frame अगर required */
	अगर (unlikely(करो_tstamp)) अणु
		skb_push(skb, GMAC_TXPAL_LEN);
		स_रखो(skb->data, 0, GMAC_TXPAL_LEN);
	पूर्ण

	/* Add TxFCB अगर required */
	अगर (fcb_len) अणु
		fcb = gfar_add_fcb(skb);
		lstatus |= BD_LFLAG(TXBD_TOE);
	पूर्ण

	/* Set up checksumming */
	अगर (करो_csum) अणु
		gfar_tx_checksum(skb, fcb, fcb_len);

		अगर (unlikely(gfar_csum_errata_12(priv, (अचिन्हित दीर्घ)fcb)) ||
		    unlikely(gfar_csum_errata_76(priv, skb->len))) अणु
			__skb_pull(skb, GMAC_FCB_LEN);
			skb_checksum_help(skb);
			अगर (करो_vlan || करो_tstamp) अणु
				/* put back a new fcb क्रम vlan/tstamp TOE */
				fcb = gfar_add_fcb(skb);
			पूर्ण अन्यथा अणु
				/* Tx TOE not used */
				lstatus &= ~(BD_LFLAG(TXBD_TOE));
				fcb = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (करो_vlan)
		gfar_tx_vlan(skb, fcb);

	bufaddr = dma_map_single(priv->dev, skb->data, skb_headlen(skb),
				 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(priv->dev, bufaddr)))
		जाओ dma_map_err;

	txbdp_start->bufPtr = cpu_to_be32(bufaddr);

	/* Time stamp insertion requires one additional TxBD */
	अगर (unlikely(करो_tstamp))
		txbdp_tstamp = txbdp = next_txbd(txbdp, base,
						 tx_queue->tx_ring_size);

	अगर (likely(!nr_frags)) अणु
		अगर (likely(!करो_tstamp))
			lstatus |= BD_LFLAG(TXBD_LAST | TXBD_INTERRUPT);
	पूर्ण अन्यथा अणु
		u32 lstatus_start = lstatus;

		/* Place the fragment addresses and lengths पूर्णांकo the TxBDs */
		frag = &skb_shinfo(skb)->frags[0];
		क्रम (i = 0; i < nr_frags; i++, frag++) अणु
			अचिन्हित पूर्णांक size;

			/* Poपूर्णांक at the next BD, wrapping as needed */
			txbdp = next_txbd(txbdp, base, tx_queue->tx_ring_size);

			size = skb_frag_size(frag);

			lstatus = be32_to_cpu(txbdp->lstatus) | size |
				  BD_LFLAG(TXBD_READY);

			/* Handle the last BD specially */
			अगर (i == nr_frags - 1)
				lstatus |= BD_LFLAG(TXBD_LAST | TXBD_INTERRUPT);

			bufaddr = skb_frag_dma_map(priv->dev, frag, 0,
						   size, DMA_TO_DEVICE);
			अगर (unlikely(dma_mapping_error(priv->dev, bufaddr)))
				जाओ dma_map_err;

			/* set the TxBD length and buffer poपूर्णांकer */
			txbdp->bufPtr = cpu_to_be32(bufaddr);
			txbdp->lstatus = cpu_to_be32(lstatus);
		पूर्ण

		lstatus = lstatus_start;
	पूर्ण

	/* If समय stamping is requested one additional TxBD must be set up. The
	 * first TxBD poपूर्णांकs to the FCB and must have a data length of
	 * GMAC_FCB_LEN. The second TxBD poपूर्णांकs to the actual frame data with
	 * the full frame length.
	 */
	अगर (unlikely(करो_tstamp)) अणु
		u32 lstatus_ts = be32_to_cpu(txbdp_tstamp->lstatus);

		bufaddr = be32_to_cpu(txbdp_start->bufPtr);
		bufaddr += fcb_len;

		lstatus_ts |= BD_LFLAG(TXBD_READY) |
			      (skb_headlen(skb) - fcb_len);
		अगर (!nr_frags)
			lstatus_ts |= BD_LFLAG(TXBD_LAST | TXBD_INTERRUPT);

		txbdp_tstamp->bufPtr = cpu_to_be32(bufaddr);
		txbdp_tstamp->lstatus = cpu_to_be32(lstatus_ts);
		lstatus |= BD_LFLAG(TXBD_CRC | TXBD_READY) | GMAC_FCB_LEN;

		/* Setup tx hardware समय stamping */
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		fcb->ptp = 1;
	पूर्ण अन्यथा अणु
		lstatus |= BD_LFLAG(TXBD_CRC | TXBD_READY) | skb_headlen(skb);
	पूर्ण

	netdev_tx_sent_queue(txq, bytes_sent);

	gfar_wmb();

	txbdp_start->lstatus = cpu_to_be32(lstatus);

	gfar_wmb(); /* क्रमce lstatus ग_लिखो beक्रमe tx_skbuff */

	tx_queue->tx_skbuff[tx_queue->skb_curtx] = skb;

	/* Update the current skb poपूर्णांकer to the next entry we will use
	 * (wrapping अगर necessary)
	 */
	tx_queue->skb_curtx = (tx_queue->skb_curtx + 1) &
			      TX_RING_MOD_MASK(tx_queue->tx_ring_size);

	tx_queue->cur_tx = next_txbd(txbdp, base, tx_queue->tx_ring_size);

	/* We can work in parallel with gfar_clean_tx_ring(), except
	 * when modअगरying num_txbdमुक्त. Note that we didn't grab the lock
	 * when we were पढ़ोing the num_txbdमुक्त and checking क्रम available
	 * space, that's because outside of this function it can only grow.
	 */
	spin_lock_bh(&tx_queue->txlock);
	/* reduce TxBD मुक्त count */
	tx_queue->num_txbdमुक्त -= (nr_txbds);
	spin_unlock_bh(&tx_queue->txlock);

	/* If the next BD still needs to be cleaned up, then the bds
	 * are full.  We need to tell the kernel to stop sending us stuff.
	 */
	अगर (!tx_queue->num_txbdमुक्त) अणु
		netअगर_tx_stop_queue(txq);

		dev->stats.tx_fअगरo_errors++;
	पूर्ण

	/* Tell the DMA to go go go */
	gfar_ग_लिखो(&regs->tstat, TSTAT_CLEAR_THALT >> tx_queue->qindex);

	वापस NETDEV_TX_OK;

dma_map_err:
	txbdp = next_txbd(txbdp_start, base, tx_queue->tx_ring_size);
	अगर (करो_tstamp)
		txbdp = next_txbd(txbdp, base, tx_queue->tx_ring_size);
	क्रम (i = 0; i < nr_frags; i++) अणु
		lstatus = be32_to_cpu(txbdp->lstatus);
		अगर (!(lstatus & BD_LFLAG(TXBD_READY)))
			अवरोध;

		lstatus &= ~BD_LFLAG(TXBD_READY);
		txbdp->lstatus = cpu_to_be32(lstatus);
		bufaddr = be32_to_cpu(txbdp->bufPtr);
		dma_unmap_page(priv->dev, bufaddr, be16_to_cpu(txbdp->length),
			       DMA_TO_DEVICE);
		txbdp = next_txbd(txbdp, base, tx_queue->tx_ring_size);
	पूर्ण
	gfar_wmb();
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* Changes the mac address अगर the controller is not running. */
अटल पूर्णांक gfar_set_mac_address(काष्ठा net_device *dev)
अणु
	gfar_set_mac_क्रम_addr(dev, 0, dev->dev_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	जबतक (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	अगर (dev->flags & IFF_UP)
		stop_gfar(dev);

	dev->mtu = new_mtu;

	अगर (dev->flags & IFF_UP)
		startup_gfar(dev);

	clear_bit_unlock(GFAR_RESETTING, &priv->state);

	वापस 0;
पूर्ण

अटल व्योम reset_gfar(काष्ठा net_device *ndev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(ndev);

	जबतक (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	stop_gfar(ndev);
	startup_gfar(ndev);

	clear_bit_unlock(GFAR_RESETTING, &priv->state);
पूर्ण

/* gfar_reset_task माला_लो scheduled when a packet has not been
 * transmitted after a set amount of समय.
 * For now, assume that clearing out all the काष्ठाures, and
 * starting over will fix the problem.
 */
अटल व्योम gfar_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gfar_निजी *priv = container_of(work, काष्ठा gfar_निजी,
						 reset_task);
	reset_gfar(priv->ndev);
पूर्ण

अटल व्योम gfar_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	dev->stats.tx_errors++;
	schedule_work(&priv->reset_task);
पूर्ण

अटल पूर्णांक gfar_hwtstamp_set(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	काष्ठा gfar_निजी *priv = netdev_priv(netdev);

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		priv->hwts_tx_en = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		अगर (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_TIMER))
			वापस -दुस्फल;
		priv->hwts_tx_en = 1;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अगर (priv->hwts_rx_en) अणु
			priv->hwts_rx_en = 0;
			reset_gfar(netdev);
		पूर्ण
		अवरोध;
	शेष:
		अगर (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_TIMER))
			वापस -दुस्फल;
		अगर (!priv->hwts_rx_en) अणु
			priv->hwts_rx_en = 1;
			reset_gfar(netdev);
		पूर्ण
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

अटल पूर्णांक gfar_hwtstamp_get(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	काष्ठा gfar_निजी *priv = netdev_priv(netdev);

	config.flags = 0;
	config.tx_type = priv->hwts_tx_en ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	config.rx_filter = (priv->hwts_rx_en ?
			    HWTSTAMP_FILTER_ALL : HWTSTAMP_FILTER_NONE);

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

अटल पूर्णांक gfar_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा phy_device *phydev = dev->phydev;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (cmd == SIOCSHWTSTAMP)
		वापस gfar_hwtstamp_set(dev, rq);
	अगर (cmd == SIOCGHWTSTAMP)
		वापस gfar_hwtstamp_get(dev, rq);

	अगर (!phydev)
		वापस -ENODEV;

	वापस phy_mii_ioctl(phydev, rq, cmd);
पूर्ण

/* Interrupt Handler क्रम Transmit complete */
अटल व्योम gfar_clean_tx_ring(काष्ठा gfar_priv_tx_q *tx_queue)
अणु
	काष्ठा net_device *dev = tx_queue->dev;
	काष्ठा netdev_queue *txq;
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा txbd8 *bdp, *next = शून्य;
	काष्ठा txbd8 *lbdp = शून्य;
	काष्ठा txbd8 *base = tx_queue->tx_bd_base;
	काष्ठा sk_buff *skb;
	पूर्णांक skb_dirtytx;
	पूर्णांक tx_ring_size = tx_queue->tx_ring_size;
	पूर्णांक frags = 0, nr_txbds = 0;
	पूर्णांक i;
	पूर्णांक howmany = 0;
	पूर्णांक tqi = tx_queue->qindex;
	अचिन्हित पूर्णांक bytes_sent = 0;
	u32 lstatus;
	माप_प्रकार buflen;

	txq = netdev_get_tx_queue(dev, tqi);
	bdp = tx_queue->dirty_tx;
	skb_dirtytx = tx_queue->skb_dirtytx;

	जबतक ((skb = tx_queue->tx_skbuff[skb_dirtytx])) अणु
		bool करो_tstamp;

		करो_tstamp = (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
			    priv->hwts_tx_en;

		frags = skb_shinfo(skb)->nr_frags;

		/* When समय stamping, one additional TxBD must be मुक्तd.
		 * Also, we need to dma_unmap_single() the TxPAL.
		 */
		अगर (unlikely(करो_tstamp))
			nr_txbds = frags + 2;
		अन्यथा
			nr_txbds = frags + 1;

		lbdp = skip_txbd(bdp, nr_txbds - 1, base, tx_ring_size);

		lstatus = be32_to_cpu(lbdp->lstatus);

		/* Only clean completed frames */
		अगर ((lstatus & BD_LFLAG(TXBD_READY)) &&
		    (lstatus & BD_LENGTH_MASK))
			अवरोध;

		अगर (unlikely(करो_tstamp)) अणु
			next = next_txbd(bdp, base, tx_ring_size);
			buflen = be16_to_cpu(next->length) +
				 GMAC_FCB_LEN + GMAC_TXPAL_LEN;
		पूर्ण अन्यथा
			buflen = be16_to_cpu(bdp->length);

		dma_unmap_single(priv->dev, be32_to_cpu(bdp->bufPtr),
				 buflen, DMA_TO_DEVICE);

		अगर (unlikely(करो_tstamp)) अणु
			काष्ठा skb_shared_hwtstamps shhwtstamps;
			u64 *ns = (u64 *)(((uपूर्णांकptr_t)skb->data + 0x10) &
					  ~0x7UL);

			स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
			shhwtstamps.hwtstamp = ns_to_kसमय(be64_to_cpu(*ns));
			skb_pull(skb, GMAC_FCB_LEN + GMAC_TXPAL_LEN);
			skb_tstamp_tx(skb, &shhwtstamps);
			gfar_clear_txbd_status(bdp);
			bdp = next;
		पूर्ण

		gfar_clear_txbd_status(bdp);
		bdp = next_txbd(bdp, base, tx_ring_size);

		क्रम (i = 0; i < frags; i++) अणु
			dma_unmap_page(priv->dev, be32_to_cpu(bdp->bufPtr),
				       be16_to_cpu(bdp->length),
				       DMA_TO_DEVICE);
			gfar_clear_txbd_status(bdp);
			bdp = next_txbd(bdp, base, tx_ring_size);
		पूर्ण

		bytes_sent += GFAR_CB(skb)->bytes_sent;

		dev_kमुक्त_skb_any(skb);

		tx_queue->tx_skbuff[skb_dirtytx] = शून्य;

		skb_dirtytx = (skb_dirtytx + 1) &
			      TX_RING_MOD_MASK(tx_ring_size);

		howmany++;
		spin_lock(&tx_queue->txlock);
		tx_queue->num_txbdमुक्त += nr_txbds;
		spin_unlock(&tx_queue->txlock);
	पूर्ण

	/* If we मुक्तd a buffer, we can restart transmission, अगर necessary */
	अगर (tx_queue->num_txbdमुक्त &&
	    netअगर_tx_queue_stopped(txq) &&
	    !(test_bit(GFAR_DOWN, &priv->state)))
		netअगर_wake_subqueue(priv->ndev, tqi);

	/* Update dirty indicators */
	tx_queue->skb_dirtytx = skb_dirtytx;
	tx_queue->dirty_tx = bdp;

	netdev_tx_completed_queue(txq, howmany, bytes_sent);
पूर्ण

अटल व्योम count_errors(u32 lstatus, काष्ठा net_device *ndev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा gfar_extra_stats *estats = &priv->extra_stats;

	/* If the packet was truncated, none of the other errors matter */
	अगर (lstatus & BD_LFLAG(RXBD_TRUNCATED)) अणु
		stats->rx_length_errors++;

		atomic64_inc(&estats->rx_trunc);

		वापस;
	पूर्ण
	/* Count the errors, अगर there were any */
	अगर (lstatus & BD_LFLAG(RXBD_LARGE | RXBD_SHORT)) अणु
		stats->rx_length_errors++;

		अगर (lstatus & BD_LFLAG(RXBD_LARGE))
			atomic64_inc(&estats->rx_large);
		अन्यथा
			atomic64_inc(&estats->rx_लघु);
	पूर्ण
	अगर (lstatus & BD_LFLAG(RXBD_NONOCTET)) अणु
		stats->rx_frame_errors++;
		atomic64_inc(&estats->rx_nonoctet);
	पूर्ण
	अगर (lstatus & BD_LFLAG(RXBD_CRCERR)) अणु
		atomic64_inc(&estats->rx_crcerr);
		stats->rx_crc_errors++;
	पूर्ण
	अगर (lstatus & BD_LFLAG(RXBD_OVERRUN)) अणु
		atomic64_inc(&estats->rx_overrun);
		stats->rx_over_errors++;
	पूर्ण
पूर्ण

अटल irqवापस_t gfar_receive(पूर्णांक irq, व्योम *grp_id)
अणु
	काष्ठा gfar_priv_grp *grp = (काष्ठा gfar_priv_grp *)grp_id;
	अचिन्हित दीर्घ flags;
	u32 imask, ievent;

	ievent = gfar_पढ़ो(&grp->regs->ievent);

	अगर (unlikely(ievent & IEVENT_FGPI)) अणु
		gfar_ग_लिखो(&grp->regs->ievent, IEVENT_FGPI);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (likely(napi_schedule_prep(&grp->napi_rx))) अणु
		spin_lock_irqsave(&grp->grplock, flags);
		imask = gfar_पढ़ो(&grp->regs->imask);
		imask &= IMASK_RX_DISABLED;
		gfar_ग_लिखो(&grp->regs->imask, imask);
		spin_unlock_irqrestore(&grp->grplock, flags);
		__napi_schedule(&grp->napi_rx);
	पूर्ण अन्यथा अणु
		/* Clear IEVENT, so पूर्णांकerrupts aren't called again
		 * because of the packets that have alपढ़ोy arrived.
		 */
		gfar_ग_लिखो(&grp->regs->ievent, IEVENT_RX_MASK);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Interrupt Handler क्रम Transmit complete */
अटल irqवापस_t gfar_transmit(पूर्णांक irq, व्योम *grp_id)
अणु
	काष्ठा gfar_priv_grp *grp = (काष्ठा gfar_priv_grp *)grp_id;
	अचिन्हित दीर्घ flags;
	u32 imask;

	अगर (likely(napi_schedule_prep(&grp->napi_tx))) अणु
		spin_lock_irqsave(&grp->grplock, flags);
		imask = gfar_पढ़ो(&grp->regs->imask);
		imask &= IMASK_TX_DISABLED;
		gfar_ग_लिखो(&grp->regs->imask, imask);
		spin_unlock_irqrestore(&grp->grplock, flags);
		__napi_schedule(&grp->napi_tx);
	पूर्ण अन्यथा अणु
		/* Clear IEVENT, so पूर्णांकerrupts aren't called again
		 * because of the packets that have alपढ़ोy arrived.
		 */
		gfar_ग_लिखो(&grp->regs->ievent, IEVENT_TX_MASK);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल bool gfar_add_rx_frag(काष्ठा gfar_rx_buff *rxb, u32 lstatus,
			     काष्ठा sk_buff *skb, bool first)
अणु
	पूर्णांक size = lstatus & BD_LENGTH_MASK;
	काष्ठा page *page = rxb->page;

	अगर (likely(first)) अणु
		skb_put(skb, size);
	पूर्ण अन्यथा अणु
		/* the last fragments' length contains the full frame length */
		अगर (lstatus & BD_LFLAG(RXBD_LAST))
			size -= skb->len;

		WARN(size < 0, "gianfar: rx fragment size underflow");
		अगर (size < 0)
			वापस false;

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
				rxb->page_offset + RXBUF_ALIGNMENT,
				size, GFAR_RXB_TRUESIZE);
	पूर्ण

	/* try reuse page */
	अगर (unlikely(page_count(page) != 1 || page_is_pfmeदो_स्मृति(page)))
		वापस false;

	/* change offset to the other half */
	rxb->page_offset ^= GFAR_RXB_TRUESIZE;

	page_ref_inc(page);

	वापस true;
पूर्ण

अटल व्योम gfar_reuse_rx_page(काष्ठा gfar_priv_rx_q *rxq,
			       काष्ठा gfar_rx_buff *old_rxb)
अणु
	काष्ठा gfar_rx_buff *new_rxb;
	u16 nta = rxq->next_to_alloc;

	new_rxb = &rxq->rx_buff[nta];

	/* find next buf that can reuse a page */
	nta++;
	rxq->next_to_alloc = (nta < rxq->rx_ring_size) ? nta : 0;

	/* copy page reference */
	*new_rxb = *old_rxb;

	/* sync क्रम use by the device */
	dma_sync_single_range_क्रम_device(rxq->dev, old_rxb->dma,
					 old_rxb->page_offset,
					 GFAR_RXB_TRUESIZE, DMA_FROM_DEVICE);
पूर्ण

अटल काष्ठा sk_buff *gfar_get_next_rxbuff(काष्ठा gfar_priv_rx_q *rx_queue,
					    u32 lstatus, काष्ठा sk_buff *skb)
अणु
	काष्ठा gfar_rx_buff *rxb = &rx_queue->rx_buff[rx_queue->next_to_clean];
	काष्ठा page *page = rxb->page;
	bool first = false;

	अगर (likely(!skb)) अणु
		व्योम *buff_addr = page_address(page) + rxb->page_offset;

		skb = build_skb(buff_addr, GFAR_SKBFRAG_SIZE);
		अगर (unlikely(!skb)) अणु
			gfar_rx_alloc_err(rx_queue);
			वापस शून्य;
		पूर्ण
		skb_reserve(skb, RXBUF_ALIGNMENT);
		first = true;
	पूर्ण

	dma_sync_single_range_क्रम_cpu(rx_queue->dev, rxb->dma, rxb->page_offset,
				      GFAR_RXB_TRUESIZE, DMA_FROM_DEVICE);

	अगर (gfar_add_rx_frag(rxb, lstatus, skb, first)) अणु
		/* reuse the मुक्त half of the page */
		gfar_reuse_rx_page(rx_queue, rxb);
	पूर्ण अन्यथा अणु
		/* page cannot be reused, unmap it */
		dma_unmap_page(rx_queue->dev, rxb->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
	पूर्ण

	/* clear rxb content */
	rxb->page = शून्य;

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम gfar_rx_checksum(काष्ठा sk_buff *skb, काष्ठा rxfcb *fcb)
अणु
	/* If valid headers were found, and valid sums
	 * were verअगरied, then we tell the kernel that no
	 * checksumming is necessary.  Otherwise, it is [FIXME]
	 */
	अगर ((be16_to_cpu(fcb->flags) & RXFCB_CSUM_MASK) ==
	    (RXFCB_CIP | RXFCB_CTU))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	अन्यथा
		skb_checksum_none_निश्चित(skb);
पूर्ण

/* gfar_process_frame() -- handle one incoming packet अगर skb isn't शून्य. */
अटल व्योम gfar_process_frame(काष्ठा net_device *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(ndev);
	काष्ठा rxfcb *fcb = शून्य;

	/* fcb is at the beginning अगर exists */
	fcb = (काष्ठा rxfcb *)skb->data;

	/* Remove the FCB from the skb
	 * Remove the padded bytes, अगर there are any
	 */
	अगर (priv->uses_rxfcb)
		skb_pull(skb, GMAC_FCB_LEN);

	/* Get receive बारtamp from the skb */
	अगर (priv->hwts_rx_en) अणु
		काष्ठा skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
		u64 *ns = (u64 *) skb->data;

		स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
		shhwtstamps->hwtstamp = ns_to_kसमय(be64_to_cpu(*ns));
	पूर्ण

	अगर (priv->padding)
		skb_pull(skb, priv->padding);

	/* Trim off the FCS */
	pskb_trim(skb, skb->len - ETH_FCS_LEN);

	अगर (ndev->features & NETIF_F_RXCSUM)
		gfar_rx_checksum(skb, fcb);

	/* There's need to check क्रम NETIF_F_HW_VLAN_CTAG_RX here.
	 * Even अगर vlan rx accel is disabled, on some chips
	 * RXFCB_VLN is pseuकरो अक्रमomly set.
	 */
	अगर (ndev->features & NETIF_F_HW_VLAN_CTAG_RX &&
	    be16_to_cpu(fcb->flags) & RXFCB_VLN)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       be16_to_cpu(fcb->vlctl));
पूर्ण

/* gfar_clean_rx_ring() -- Processes each frame in the rx ring
 * until the budget/quota has been reached. Returns the number
 * of frames handled
 */
अटल पूर्णांक gfar_clean_rx_ring(काष्ठा gfar_priv_rx_q *rx_queue,
			      पूर्णांक rx_work_limit)
अणु
	काष्ठा net_device *ndev = rx_queue->ndev;
	काष्ठा gfar_निजी *priv = netdev_priv(ndev);
	काष्ठा rxbd8 *bdp;
	पूर्णांक i, howmany = 0;
	काष्ठा sk_buff *skb = rx_queue->skb;
	पूर्णांक cleaned_cnt = gfar_rxbd_unused(rx_queue);
	अचिन्हित पूर्णांक total_bytes = 0, total_pkts = 0;

	/* Get the first full descriptor */
	i = rx_queue->next_to_clean;

	जबतक (rx_work_limit--) अणु
		u32 lstatus;

		अगर (cleaned_cnt >= GFAR_RX_BUFF_ALLOC) अणु
			gfar_alloc_rx_buffs(rx_queue, cleaned_cnt);
			cleaned_cnt = 0;
		पूर्ण

		bdp = &rx_queue->rx_bd_base[i];
		lstatus = be32_to_cpu(bdp->lstatus);
		अगर (lstatus & BD_LFLAG(RXBD_EMPTY))
			अवरोध;

		/* lost RXBD_LAST descriptor due to overrun */
		अगर (skb &&
		    (lstatus & BD_LFLAG(RXBD_FIRST))) अणु
			/* discard faulty buffer */
			dev_kमुक्त_skb(skb);
			skb = शून्य;
			rx_queue->stats.rx_dropped++;

			/* can जारी normally */
		पूर्ण

		/* order rx buffer descriptor पढ़ोs */
		rmb();

		/* fetch next to clean buffer from the ring */
		skb = gfar_get_next_rxbuff(rx_queue, lstatus, skb);
		अगर (unlikely(!skb))
			अवरोध;

		cleaned_cnt++;
		howmany++;

		अगर (unlikely(++i == rx_queue->rx_ring_size))
			i = 0;

		rx_queue->next_to_clean = i;

		/* fetch next buffer अगर not the last in frame */
		अगर (!(lstatus & BD_LFLAG(RXBD_LAST)))
			जारी;

		अगर (unlikely(lstatus & BD_LFLAG(RXBD_ERR))) अणु
			count_errors(lstatus, ndev);

			/* discard faulty buffer */
			dev_kमुक्त_skb(skb);
			skb = शून्य;
			rx_queue->stats.rx_dropped++;
			जारी;
		पूर्ण

		gfar_process_frame(ndev, skb);

		/* Increment the number of packets */
		total_pkts++;
		total_bytes += skb->len;

		skb_record_rx_queue(skb, rx_queue->qindex);

		skb->protocol = eth_type_trans(skb, ndev);

		/* Send the packet up the stack */
		napi_gro_receive(&rx_queue->grp->napi_rx, skb);

		skb = शून्य;
	पूर्ण

	/* Store incomplete frames क्रम completion */
	rx_queue->skb = skb;

	rx_queue->stats.rx_packets += total_pkts;
	rx_queue->stats.rx_bytes += total_bytes;

	अगर (cleaned_cnt)
		gfar_alloc_rx_buffs(rx_queue, cleaned_cnt);

	/* Update Last Free RxBD poपूर्णांकer क्रम LFC */
	अगर (unlikely(priv->tx_actual_en)) अणु
		u32 bdp_dma = gfar_rxbd_dma_lastमुक्त(rx_queue);

		gfar_ग_लिखो(rx_queue->rfbptr, bdp_dma);
	पूर्ण

	वापस howmany;
पूर्ण

अटल पूर्णांक gfar_poll_rx_sq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gfar_priv_grp *gfargrp =
		container_of(napi, काष्ठा gfar_priv_grp, napi_rx);
	काष्ठा gfar __iomem *regs = gfargrp->regs;
	काष्ठा gfar_priv_rx_q *rx_queue = gfargrp->rx_queue;
	पूर्णांक work_करोne = 0;

	/* Clear IEVENT, so पूर्णांकerrupts aren't called again
	 * because of the packets that have alपढ़ोy arrived
	 */
	gfar_ग_लिखो(&regs->ievent, IEVENT_RX_MASK);

	work_करोne = gfar_clean_rx_ring(rx_queue, budget);

	अगर (work_करोne < budget) अणु
		u32 imask;
		napi_complete_करोne(napi, work_करोne);
		/* Clear the halt bit in RSTAT */
		gfar_ग_लिखो(&regs->rstat, gfargrp->rstat);

		spin_lock_irq(&gfargrp->grplock);
		imask = gfar_पढ़ो(&regs->imask);
		imask |= IMASK_RX_DEFAULT;
		gfar_ग_लिखो(&regs->imask, imask);
		spin_unlock_irq(&gfargrp->grplock);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक gfar_poll_tx_sq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gfar_priv_grp *gfargrp =
		container_of(napi, काष्ठा gfar_priv_grp, napi_tx);
	काष्ठा gfar __iomem *regs = gfargrp->regs;
	काष्ठा gfar_priv_tx_q *tx_queue = gfargrp->tx_queue;
	u32 imask;

	/* Clear IEVENT, so पूर्णांकerrupts aren't called again
	 * because of the packets that have alपढ़ोy arrived
	 */
	gfar_ग_लिखो(&regs->ievent, IEVENT_TX_MASK);

	/* run Tx cleanup to completion */
	अगर (tx_queue->tx_skbuff[tx_queue->skb_dirtytx])
		gfar_clean_tx_ring(tx_queue);

	napi_complete(napi);

	spin_lock_irq(&gfargrp->grplock);
	imask = gfar_पढ़ो(&regs->imask);
	imask |= IMASK_TX_DEFAULT;
	gfar_ग_लिखो(&regs->imask, imask);
	spin_unlock_irq(&gfargrp->grplock);

	वापस 0;
पूर्ण

/* GFAR error पूर्णांकerrupt handler */
अटल irqवापस_t gfar_error(पूर्णांक irq, व्योम *grp_id)
अणु
	काष्ठा gfar_priv_grp *gfargrp = grp_id;
	काष्ठा gfar __iomem *regs = gfargrp->regs;
	काष्ठा gfar_निजी *priv= gfargrp->priv;
	काष्ठा net_device *dev = priv->ndev;

	/* Save ievent क्रम future reference */
	u32 events = gfar_पढ़ो(&regs->ievent);

	/* Clear IEVENT */
	gfar_ग_लिखो(&regs->ievent, events & IEVENT_ERR_MASK);

	/* Magic Packet is not an error. */
	अगर ((priv->device_flags & FSL_GIANFAR_DEV_HAS_MAGIC_PACKET) &&
	    (events & IEVENT_MAG))
		events &= ~IEVENT_MAG;

	/* Hmm... */
	अगर (netअगर_msg_rx_err(priv) || netअगर_msg_tx_err(priv))
		netdev_dbg(dev,
			   "error interrupt (ievent=0x%08x imask=0x%08x)\n",
			   events, gfar_पढ़ो(&regs->imask));

	/* Update the error counters */
	अगर (events & IEVENT_TXE) अणु
		dev->stats.tx_errors++;

		अगर (events & IEVENT_LC)
			dev->stats.tx_winकरोw_errors++;
		अगर (events & IEVENT_CRL)
			dev->stats.tx_पातed_errors++;
		अगर (events & IEVENT_XFUN) अणु
			netअगर_dbg(priv, tx_err, dev,
				  "TX FIFO underrun, packet dropped\n");
			dev->stats.tx_dropped++;
			atomic64_inc(&priv->extra_stats.tx_underrun);

			schedule_work(&priv->reset_task);
		पूर्ण
		netअगर_dbg(priv, tx_err, dev, "Transmit Error\n");
	पूर्ण
	अगर (events & IEVENT_BSY) अणु
		dev->stats.rx_over_errors++;
		atomic64_inc(&priv->extra_stats.rx_bsy);

		netअगर_dbg(priv, rx_err, dev, "busy error (rstat: %x)\n",
			  gfar_पढ़ो(&regs->rstat));
	पूर्ण
	अगर (events & IEVENT_BABR) अणु
		dev->stats.rx_errors++;
		atomic64_inc(&priv->extra_stats.rx_babr);

		netअगर_dbg(priv, rx_err, dev, "babbling RX error\n");
	पूर्ण
	अगर (events & IEVENT_EBERR) अणु
		atomic64_inc(&priv->extra_stats.eberr);
		netअगर_dbg(priv, rx_err, dev, "bus error\n");
	पूर्ण
	अगर (events & IEVENT_RXC)
		netअगर_dbg(priv, rx_status, dev, "control frame\n");

	अगर (events & IEVENT_BABT) अणु
		atomic64_inc(&priv->extra_stats.tx_babt);
		netअगर_dbg(priv, tx_err, dev, "babbling TX error\n");
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/* The पूर्णांकerrupt handler क्रम devices with one पूर्णांकerrupt */
अटल irqवापस_t gfar_पूर्णांकerrupt(पूर्णांक irq, व्योम *grp_id)
अणु
	काष्ठा gfar_priv_grp *gfargrp = grp_id;

	/* Save ievent क्रम future reference */
	u32 events = gfar_पढ़ो(&gfargrp->regs->ievent);

	/* Check क्रम reception */
	अगर (events & IEVENT_RX_MASK)
		gfar_receive(irq, grp_id);

	/* Check क्रम transmit completion */
	अगर (events & IEVENT_TX_MASK)
		gfar_transmit(irq, grp_id);

	/* Check क्रम errors */
	अगर (events & IEVENT_ERR_MASK)
		gfar_error(irq, grp_id);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/* Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम gfar_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	पूर्णांक i;

	/* If the device has multiple पूर्णांकerrupts, run tx/rx */
	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_MULTI_INTR) अणु
		क्रम (i = 0; i < priv->num_grps; i++) अणु
			काष्ठा gfar_priv_grp *grp = &priv->gfargrp[i];

			disable_irq(gfar_irq(grp, TX)->irq);
			disable_irq(gfar_irq(grp, RX)->irq);
			disable_irq(gfar_irq(grp, ER)->irq);
			gfar_पूर्णांकerrupt(gfar_irq(grp, TX)->irq, grp);
			enable_irq(gfar_irq(grp, ER)->irq);
			enable_irq(gfar_irq(grp, RX)->irq);
			enable_irq(gfar_irq(grp, TX)->irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < priv->num_grps; i++) अणु
			काष्ठा gfar_priv_grp *grp = &priv->gfargrp[i];

			disable_irq(gfar_irq(grp, TX)->irq);
			gfar_पूर्णांकerrupt(gfar_irq(grp, TX)->irq, grp);
			enable_irq(gfar_irq(grp, TX)->irq);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम मुक्त_grp_irqs(काष्ठा gfar_priv_grp *grp)
अणु
	मुक्त_irq(gfar_irq(grp, TX)->irq, grp);
	मुक्त_irq(gfar_irq(grp, RX)->irq, grp);
	मुक्त_irq(gfar_irq(grp, ER)->irq, grp);
पूर्ण

अटल पूर्णांक रेजिस्टर_grp_irqs(काष्ठा gfar_priv_grp *grp)
अणु
	काष्ठा gfar_निजी *priv = grp->priv;
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक err;

	/* If the device has multiple पूर्णांकerrupts, रेजिस्टर क्रम
	 * them.  Otherwise, only रेजिस्टर क्रम the one
	 */
	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_MULTI_INTR) अणु
		/* Install our पूर्णांकerrupt handlers क्रम Error,
		 * Transmit, and Receive
		 */
		err = request_irq(gfar_irq(grp, ER)->irq, gfar_error, 0,
				  gfar_irq(grp, ER)->name, grp);
		अगर (err < 0) अणु
			netअगर_err(priv, पूर्णांकr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, ER)->irq);

			जाओ err_irq_fail;
		पूर्ण
		enable_irq_wake(gfar_irq(grp, ER)->irq);

		err = request_irq(gfar_irq(grp, TX)->irq, gfar_transmit, 0,
				  gfar_irq(grp, TX)->name, grp);
		अगर (err < 0) अणु
			netअगर_err(priv, पूर्णांकr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, TX)->irq);
			जाओ tx_irq_fail;
		पूर्ण
		err = request_irq(gfar_irq(grp, RX)->irq, gfar_receive, 0,
				  gfar_irq(grp, RX)->name, grp);
		अगर (err < 0) अणु
			netअगर_err(priv, पूर्णांकr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, RX)->irq);
			जाओ rx_irq_fail;
		पूर्ण
		enable_irq_wake(gfar_irq(grp, RX)->irq);

	पूर्ण अन्यथा अणु
		err = request_irq(gfar_irq(grp, TX)->irq, gfar_पूर्णांकerrupt, 0,
				  gfar_irq(grp, TX)->name, grp);
		अगर (err < 0) अणु
			netअगर_err(priv, पूर्णांकr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, TX)->irq);
			जाओ err_irq_fail;
		पूर्ण
		enable_irq_wake(gfar_irq(grp, TX)->irq);
	पूर्ण

	वापस 0;

rx_irq_fail:
	मुक्त_irq(gfar_irq(grp, TX)->irq, grp);
tx_irq_fail:
	मुक्त_irq(gfar_irq(grp, ER)->irq, grp);
err_irq_fail:
	वापस err;

पूर्ण

अटल व्योम gfar_मुक्त_irq(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक i;

	/* Free the IRQs */
	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_MULTI_INTR) अणु
		क्रम (i = 0; i < priv->num_grps; i++)
			मुक्त_grp_irqs(&priv->gfargrp[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < priv->num_grps; i++)
			मुक्त_irq(gfar_irq(&priv->gfargrp[i], TX)->irq,
				 &priv->gfargrp[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक gfar_request_irq(काष्ठा gfar_निजी *priv)
अणु
	पूर्णांक err, i, j;

	क्रम (i = 0; i < priv->num_grps; i++) अणु
		err = रेजिस्टर_grp_irqs(&priv->gfargrp[i]);
		अगर (err) अणु
			क्रम (j = 0; j < i; j++)
				मुक्त_grp_irqs(&priv->gfargrp[j]);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Called when something needs to use the ethernet device
 * Returns 0 क्रम success.
 */
अटल पूर्णांक gfar_enet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	पूर्णांक err;

	err = init_phy(dev);
	अगर (err)
		वापस err;

	err = gfar_request_irq(priv);
	अगर (err)
		वापस err;

	err = startup_gfar(dev);
	अगर (err)
		वापस err;

	वापस err;
पूर्ण

/* Stops the kernel queue, and halts the controller */
अटल पूर्णांक gfar_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा gfar_निजी *priv = netdev_priv(dev);

	cancel_work_sync(&priv->reset_task);
	stop_gfar(dev);

	/* Disconnect from the PHY */
	phy_disconnect(dev->phydev);

	gfar_मुक्त_irq(priv);

	वापस 0;
पूर्ण

/* Clears each of the exact match रेजिस्टरs to zero, so they
 * करोn't पूर्णांकerfere with normal reception
 */
अटल व्योम gfar_clear_exact_match(काष्ठा net_device *dev)
अणु
	पूर्णांक idx;
	अटल स्थिर u8 zero_arr[ETH_ALEN] = अणु0, 0, 0, 0, 0, 0पूर्ण;

	क्रम (idx = 1; idx < GFAR_EM_NUM + 1; idx++)
		gfar_set_mac_क्रम_addr(dev, idx, zero_arr);
पूर्ण

/* Update the hash table based on the current list of multicast
 * addresses we subscribe to.  Also, change the promiscuity of
 * the device based on the flags (this function is called
 * whenever dev->flags is changed
 */
अटल व्योम gfar_set_multi(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा gfar_निजी *priv = netdev_priv(dev);
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;

	अगर (dev->flags & IFF_PROMISC) अणु
		/* Set RCTRL to PROM */
		tempval = gfar_पढ़ो(&regs->rctrl);
		tempval |= RCTRL_PROM;
		gfar_ग_लिखो(&regs->rctrl, tempval);
	पूर्ण अन्यथा अणु
		/* Set RCTRL to not PROM */
		tempval = gfar_पढ़ो(&regs->rctrl);
		tempval &= ~(RCTRL_PROM);
		gfar_ग_लिखो(&regs->rctrl, tempval);
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI) अणु
		/* Set the hash to rx all multicast frames */
		gfar_ग_लिखो(&regs->igaddr0, 0xffffffff);
		gfar_ग_लिखो(&regs->igaddr1, 0xffffffff);
		gfar_ग_लिखो(&regs->igaddr2, 0xffffffff);
		gfar_ग_लिखो(&regs->igaddr3, 0xffffffff);
		gfar_ग_लिखो(&regs->igaddr4, 0xffffffff);
		gfar_ग_लिखो(&regs->igaddr5, 0xffffffff);
		gfar_ग_लिखो(&regs->igaddr6, 0xffffffff);
		gfar_ग_लिखो(&regs->igaddr7, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr0, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr1, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr2, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr3, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr4, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr5, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr6, 0xffffffff);
		gfar_ग_लिखो(&regs->gaddr7, 0xffffffff);
	पूर्ण अन्यथा अणु
		पूर्णांक em_num;
		पूर्णांक idx;

		/* zero out the hash */
		gfar_ग_लिखो(&regs->igaddr0, 0x0);
		gfar_ग_लिखो(&regs->igaddr1, 0x0);
		gfar_ग_लिखो(&regs->igaddr2, 0x0);
		gfar_ग_लिखो(&regs->igaddr3, 0x0);
		gfar_ग_लिखो(&regs->igaddr4, 0x0);
		gfar_ग_लिखो(&regs->igaddr5, 0x0);
		gfar_ग_लिखो(&regs->igaddr6, 0x0);
		gfar_ग_लिखो(&regs->igaddr7, 0x0);
		gfar_ग_लिखो(&regs->gaddr0, 0x0);
		gfar_ग_लिखो(&regs->gaddr1, 0x0);
		gfar_ग_लिखो(&regs->gaddr2, 0x0);
		gfar_ग_लिखो(&regs->gaddr3, 0x0);
		gfar_ग_लिखो(&regs->gaddr4, 0x0);
		gfar_ग_लिखो(&regs->gaddr5, 0x0);
		gfar_ग_लिखो(&regs->gaddr6, 0x0);
		gfar_ग_लिखो(&regs->gaddr7, 0x0);

		/* If we have extended hash tables, we need to
		 * clear the exact match रेजिस्टरs to prepare क्रम
		 * setting them
		 */
		अगर (priv->extended_hash) अणु
			em_num = GFAR_EM_NUM + 1;
			gfar_clear_exact_match(dev);
			idx = 1;
		पूर्ण अन्यथा अणु
			idx = 0;
			em_num = 0;
		पूर्ण

		अगर (netdev_mc_empty(dev))
			वापस;

		/* Parse the list, and set the appropriate bits */
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (idx < em_num) अणु
				gfar_set_mac_क्रम_addr(dev, idx, ha->addr);
				idx++;
			पूर्ण अन्यथा
				gfar_set_hash_क्रम_addr(dev, ha->addr);
		पूर्ण
	पूर्ण
पूर्ण

व्योम gfar_mac_reset(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;

	/* Reset MAC layer */
	gfar_ग_लिखो(&regs->maccfg1, MACCFG1_SOFT_RESET);

	/* We need to delay at least 3 TX घड़ीs */
	udelay(3);

	/* the soft reset bit is not self-resetting, so we need to
	 * clear it beक्रमe resuming normal operation
	 */
	gfar_ग_लिखो(&regs->maccfg1, 0);

	udelay(3);

	gfar_rx_offload_en(priv);

	/* Initialize the max receive frame/buffer lengths */
	gfar_ग_लिखो(&regs->maxfrm, GFAR_JUMBO_FRAME_SIZE);
	gfar_ग_लिखो(&regs->mrblr, GFAR_RXB_SIZE);

	/* Initialize the Minimum Frame Length Register */
	gfar_ग_लिखो(&regs->minflr, MINFLR_INIT_SETTINGS);

	/* Initialize MACCFG2. */
	tempval = MACCFG2_INIT_SETTINGS;

	/* eTSEC74 erratum: Rx frames of length MAXFRM or MAXFRM-1
	 * are marked as truncated.  Aव्योम this by MACCFG2[Huge Frame]=1,
	 * and by checking RxBD[LG] and discarding larger than MAXFRM.
	 */
	अगर (gfar_has_errata(priv, GFAR_ERRATA_74))
		tempval |= MACCFG2_HUGEFRAME | MACCFG2_LENGTHCHECK;

	gfar_ग_लिखो(&regs->maccfg2, tempval);

	/* Clear mac addr hash रेजिस्टरs */
	gfar_ग_लिखो(&regs->igaddr0, 0);
	gfar_ग_लिखो(&regs->igaddr1, 0);
	gfar_ग_लिखो(&regs->igaddr2, 0);
	gfar_ग_लिखो(&regs->igaddr3, 0);
	gfar_ग_लिखो(&regs->igaddr4, 0);
	gfar_ग_लिखो(&regs->igaddr5, 0);
	gfar_ग_लिखो(&regs->igaddr6, 0);
	gfar_ग_लिखो(&regs->igaddr7, 0);

	gfar_ग_लिखो(&regs->gaddr0, 0);
	gfar_ग_लिखो(&regs->gaddr1, 0);
	gfar_ग_लिखो(&regs->gaddr2, 0);
	gfar_ग_लिखो(&regs->gaddr3, 0);
	gfar_ग_लिखो(&regs->gaddr4, 0);
	gfar_ग_लिखो(&regs->gaddr5, 0);
	gfar_ग_लिखो(&regs->gaddr6, 0);
	gfar_ग_लिखो(&regs->gaddr7, 0);

	अगर (priv->extended_hash)
		gfar_clear_exact_match(priv->ndev);

	gfar_mac_rx_config(priv);

	gfar_mac_tx_config(priv);

	gfar_set_mac_address(priv->ndev);

	gfar_set_multi(priv->ndev);

	/* clear ievent and imask beक्रमe configuring coalescing */
	gfar_पूर्णांकs_disable(priv);

	/* Configure the coalescing support */
	gfar_configure_coalescing_all(priv);
पूर्ण

अटल व्योम gfar_hw_init(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 attrs;

	/* Stop the DMA engine now, in हाल it was running beक्रमe
	 * (The firmware could have used it, and left it running).
	 */
	gfar_halt(priv);

	gfar_mac_reset(priv);

	/* Zero out the rmon mib रेजिस्टरs अगर it has them */
	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_RMON) अणु
		स_रखो_io(&(regs->rmon), 0, माप(काष्ठा rmon_mib));

		/* Mask off the CAM पूर्णांकerrupts */
		gfar_ग_लिखो(&regs->rmon.cam1, 0xffffffff);
		gfar_ग_लिखो(&regs->rmon.cam2, 0xffffffff);
	पूर्ण

	/* Initialize ECNTRL */
	gfar_ग_लिखो(&regs->ecntrl, ECNTRL_INIT_SETTINGS);

	/* Set the extraction length and index */
	attrs = ATTRELI_EL(priv->rx_stash_size) |
		ATTRELI_EI(priv->rx_stash_index);

	gfar_ग_लिखो(&regs->attreli, attrs);

	/* Start with शेषs, and add stashing
	 * depending on driver parameters
	 */
	attrs = ATTR_INIT_SETTINGS;

	अगर (priv->bd_stash_en)
		attrs |= ATTR_BDSTASH;

	अगर (priv->rx_stash_size != 0)
		attrs |= ATTR_BUFSTASH;

	gfar_ग_लिखो(&regs->attr, attrs);

	/* FIFO configs */
	gfar_ग_लिखो(&regs->fअगरo_tx_thr, DEFAULT_FIFO_TX_THR);
	gfar_ग_लिखो(&regs->fअगरo_tx_starve, DEFAULT_FIFO_TX_STARVE);
	gfar_ग_लिखो(&regs->fअगरo_tx_starve_shutoff, DEFAULT_FIFO_TX_STARVE_OFF);

	/* Program the पूर्णांकerrupt steering regs, only क्रम MG devices */
	अगर (priv->num_grps > 1)
		gfar_ग_लिखो_isrg(priv);
पूर्ण

अटल स्थिर काष्ठा net_device_ops gfar_netdev_ops = अणु
	.nकरो_खोलो = gfar_enet_खोलो,
	.nकरो_start_xmit = gfar_start_xmit,
	.nकरो_stop = gfar_बंद,
	.nकरो_change_mtu = gfar_change_mtu,
	.nकरो_set_features = gfar_set_features,
	.nकरो_set_rx_mode = gfar_set_multi,
	.nकरो_tx_समयout = gfar_समयout,
	.nकरो_करो_ioctl = gfar_ioctl,
	.nकरो_get_stats = gfar_get_stats,
	.nकरो_change_carrier = fixed_phy_change_carrier,
	.nकरो_set_mac_address = gfar_set_mac_addr,
	.nकरो_validate_addr = eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = gfar_netpoll,
#पूर्ण_अगर
पूर्ण;

/* Set up the ethernet device काष्ठाure, निजी data,
 * and anything अन्यथा we need beक्रमe we start
 */
अटल पूर्णांक gfar_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा net_device *dev = शून्य;
	काष्ठा gfar_निजी *priv = शून्य;
	पूर्णांक err = 0, i;

	err = gfar_of_init(ofdev, &dev);

	अगर (err)
		वापस err;

	priv = netdev_priv(dev);
	priv->ndev = dev;
	priv->ofdev = ofdev;
	priv->dev = &ofdev->dev;
	SET_NETDEV_DEV(dev, &ofdev->dev);

	INIT_WORK(&priv->reset_task, gfar_reset_task);

	platक्रमm_set_drvdata(ofdev, priv);

	gfar_detect_errata(priv);

	/* Set the dev->base_addr to the gfar reg region */
	dev->base_addr = (अचिन्हित दीर्घ) priv->gfargrp[0].regs;

	/* Fill in the dev काष्ठाure */
	dev->watchकरोg_समयo = TX_TIMEOUT;
	/* MTU range: 50 - 9586 */
	dev->mtu = 1500;
	dev->min_mtu = 50;
	dev->max_mtu = GFAR_JUMBO_FRAME_SIZE - ETH_HLEN;
	dev->netdev_ops = &gfar_netdev_ops;
	dev->ethtool_ops = &gfar_ethtool_ops;

	/* Register क्रम napi ...We are रेजिस्टरing NAPI क्रम each grp */
	क्रम (i = 0; i < priv->num_grps; i++) अणु
		netअगर_napi_add(dev, &priv->gfargrp[i].napi_rx,
			       gfar_poll_rx_sq, GFAR_DEV_WEIGHT);
		netअगर_tx_napi_add(dev, &priv->gfargrp[i].napi_tx,
				  gfar_poll_tx_sq, 2);
	पूर्ण

	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_CSUM) अणु
		dev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG |
				   NETIF_F_RXCSUM;
		dev->features |= NETIF_F_IP_CSUM | NETIF_F_SG |
				 NETIF_F_RXCSUM | NETIF_F_HIGHDMA;
	पूर्ण

	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_VLAN) अणु
		dev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_HW_VLAN_CTAG_RX;
		dev->features |= NETIF_F_HW_VLAN_CTAG_RX;
	पूर्ण

	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	gfar_init_addr_hash_table(priv);

	/* Insert receive समय stamps पूर्णांकo padding alignment bytes, and
	 * plus 2 bytes padding to ensure the cpu alignment.
	 */
	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_TIMER)
		priv->padding = 8 + DEFAULT_PADDING;

	अगर (dev->features & NETIF_F_IP_CSUM ||
	    priv->device_flags & FSL_GIANFAR_DEV_HAS_TIMER)
		dev->needed_headroom = GMAC_FCB_LEN + GMAC_TXPAL_LEN;

	/* Initializing some of the rx/tx queue level parameters */
	क्रम (i = 0; i < priv->num_tx_queues; i++) अणु
		priv->tx_queue[i]->tx_ring_size = DEFAULT_TX_RING_SIZE;
		priv->tx_queue[i]->num_txbdमुक्त = DEFAULT_TX_RING_SIZE;
		priv->tx_queue[i]->txcoalescing = DEFAULT_TX_COALESCE;
		priv->tx_queue[i]->txic = DEFAULT_TXIC;
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_queues; i++) अणु
		priv->rx_queue[i]->rx_ring_size = DEFAULT_RX_RING_SIZE;
		priv->rx_queue[i]->rxcoalescing = DEFAULT_RX_COALESCE;
		priv->rx_queue[i]->rxic = DEFAULT_RXIC;
	पूर्ण

	/* Always enable rx filer अगर available */
	priv->rx_filer_enable =
	    (priv->device_flags & FSL_GIANFAR_DEV_HAS_RX_खाताR) ? 1 : 0;
	/* Enable most messages by शेष */
	priv->msg_enable = (NETIF_MSG_IFUP << 1 ) - 1;
	/* use pritority h/w tx queue scheduling क्रम single queue devices */
	अगर (priv->num_tx_queues == 1)
		priv->prio_sched_en = 1;

	set_bit(GFAR_DOWN, &priv->state);

	gfar_hw_init(priv);

	/* Carrier starts करोwn, phylib will bring it up */
	netअगर_carrier_off(dev);

	err = रेजिस्टर_netdev(dev);

	अगर (err) अणु
		pr_err("%s: Cannot register net device, aborting\n", dev->name);
		जाओ रेजिस्टर_fail;
	पूर्ण

	अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_MAGIC_PACKET)
		priv->wol_supported |= GFAR_WOL_MAGIC;

	अगर ((priv->device_flags & FSL_GIANFAR_DEV_HAS_WAKE_ON_खाताR) &&
	    priv->rx_filer_enable)
		priv->wol_supported |= GFAR_WOL_खाताR_UCAST;

	device_set_wakeup_capable(&ofdev->dev, priv->wol_supported);

	/* fill out IRQ number and name fields */
	क्रम (i = 0; i < priv->num_grps; i++) अणु
		काष्ठा gfar_priv_grp *grp = &priv->gfargrp[i];
		अगर (priv->device_flags & FSL_GIANFAR_DEV_HAS_MULTI_INTR) अणु
			प्र_लिखो(gfar_irq(grp, TX)->name, "%s%s%c%s",
				dev->name, "_g", '0' + i, "_tx");
			प्र_लिखो(gfar_irq(grp, RX)->name, "%s%s%c%s",
				dev->name, "_g", '0' + i, "_rx");
			प्र_लिखो(gfar_irq(grp, ER)->name, "%s%s%c%s",
				dev->name, "_g", '0' + i, "_er");
		पूर्ण अन्यथा
			म_नकल(gfar_irq(grp, TX)->name, dev->name);
	पूर्ण

	/* Initialize the filer table */
	gfar_init_filer_table(priv);

	/* Prपूर्णांक out the device info */
	netdev_info(dev, "mac: %pM\n", dev->dev_addr);

	/* Even more device info helps when determining which kernel
	 * provided which set of benchmarks.
	 */
	netdev_info(dev, "Running with NAPI enabled\n");
	क्रम (i = 0; i < priv->num_rx_queues; i++)
		netdev_info(dev, "RX BD ring size for Q[%d]: %d\n",
			    i, priv->rx_queue[i]->rx_ring_size);
	क्रम (i = 0; i < priv->num_tx_queues; i++)
		netdev_info(dev, "TX BD ring size for Q[%d]: %d\n",
			    i, priv->tx_queue[i]->tx_ring_size);

	वापस 0;

रेजिस्टर_fail:
	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);
	unmap_group_regs(priv);
	gfar_मुक्त_rx_queues(priv);
	gfar_मुक्त_tx_queues(priv);
	of_node_put(priv->phy_node);
	of_node_put(priv->tbi_node);
	मुक्त_gfar_dev(priv);
	वापस err;
पूर्ण

अटल पूर्णांक gfar_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा gfar_निजी *priv = platक्रमm_get_drvdata(ofdev);
	काष्ठा device_node *np = ofdev->dev.of_node;

	of_node_put(priv->phy_node);
	of_node_put(priv->tbi_node);

	unरेजिस्टर_netdev(priv->ndev);

	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);

	unmap_group_regs(priv);
	gfar_मुक्त_rx_queues(priv);
	gfar_मुक्त_tx_queues(priv);
	मुक्त_gfar_dev(priv);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल व्योम __gfar_filer_disable(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 temp;

	temp = gfar_पढ़ो(&regs->rctrl);
	temp &= ~(RCTRL_FILREN | RCTRL_PRSDEP_INIT);
	gfar_ग_लिखो(&regs->rctrl, temp);
पूर्ण

अटल व्योम __gfar_filer_enable(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 temp;

	temp = gfar_पढ़ो(&regs->rctrl);
	temp |= RCTRL_FILREN | RCTRL_PRSDEP_INIT;
	gfar_ग_लिखो(&regs->rctrl, temp);
पूर्ण

/* Filer rules implementing wol capabilities */
अटल व्योम gfar_filer_config_wol(काष्ठा gfar_निजी *priv)
अणु
	अचिन्हित पूर्णांक i;
	u32 rqfcr;

	__gfar_filer_disable(priv);

	/* clear the filer table, reject any packet by शेष */
	rqfcr = RQFCR_RJE | RQFCR_CMP_MATCH;
	क्रम (i = 0; i <= MAX_खाताR_IDX; i++)
		gfar_ग_लिखो_filer(priv, i, rqfcr, 0);

	i = 0;
	अगर (priv->wol_opts & GFAR_WOL_खाताR_UCAST) अणु
		/* unicast packet, accept it */
		काष्ठा net_device *ndev = priv->ndev;
		/* get the शेष rx queue index */
		u8 qindex = (u8)priv->gfargrp[0].rx_queue->qindex;
		u32 dest_mac_addr = (ndev->dev_addr[0] << 16) |
				    (ndev->dev_addr[1] << 8) |
				     ndev->dev_addr[2];

		rqfcr = (qindex << 10) | RQFCR_AND |
			RQFCR_CMP_EXACT | RQFCR_PID_DAH;

		gfar_ग_लिखो_filer(priv, i++, rqfcr, dest_mac_addr);

		dest_mac_addr = (ndev->dev_addr[3] << 16) |
				(ndev->dev_addr[4] << 8) |
				 ndev->dev_addr[5];
		rqfcr = (qindex << 10) | RQFCR_GPI |
			RQFCR_CMP_EXACT | RQFCR_PID_DAL;
		gfar_ग_लिखो_filer(priv, i++, rqfcr, dest_mac_addr);
	पूर्ण

	__gfar_filer_enable(priv);
पूर्ण

अटल व्योम gfar_filer_restore_table(काष्ठा gfar_निजी *priv)
अणु
	u32 rqfcr, rqfpr;
	अचिन्हित पूर्णांक i;

	__gfar_filer_disable(priv);

	क्रम (i = 0; i <= MAX_खाताR_IDX; i++) अणु
		rqfcr = priv->ftp_rqfcr[i];
		rqfpr = priv->ftp_rqfpr[i];
		gfar_ग_लिखो_filer(priv, i, rqfcr, rqfpr);
	पूर्ण

	__gfar_filer_enable(priv);
पूर्ण

/* gfar_start() क्रम Rx only and with the FGPI filer पूर्णांकerrupt enabled */
अटल व्योम gfar_start_wol_filer(काष्ठा gfar_निजी *priv)
अणु
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;
	पूर्णांक i = 0;

	/* Enable Rx hw queues */
	gfar_ग_लिखो(&regs->rqueue, priv->rqueue);

	/* Initialize DMACTRL to have WWR and WOP */
	tempval = gfar_पढ़ो(&regs->dmactrl);
	tempval |= DMACTRL_INIT_SETTINGS;
	gfar_ग_लिखो(&regs->dmactrl, tempval);

	/* Make sure we aren't stopped */
	tempval = gfar_पढ़ो(&regs->dmactrl);
	tempval &= ~DMACTRL_GRS;
	gfar_ग_लिखो(&regs->dmactrl, tempval);

	क्रम (i = 0; i < priv->num_grps; i++) अणु
		regs = priv->gfargrp[i].regs;
		/* Clear RHLT, so that the DMA starts polling now */
		gfar_ग_लिखो(&regs->rstat, priv->gfargrp[i].rstat);
		/* enable the Filer General Purpose Interrupt */
		gfar_ग_लिखो(&regs->imask, IMASK_FGPI);
	पूर्ण

	/* Enable Rx DMA */
	tempval = gfar_पढ़ो(&regs->maccfg1);
	tempval |= MACCFG1_RX_EN;
	gfar_ग_लिखो(&regs->maccfg1, tempval);
पूर्ण

अटल पूर्णांक gfar_suspend(काष्ठा device *dev)
अणु
	काष्ठा gfar_निजी *priv = dev_get_drvdata(dev);
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;
	u16 wol = priv->wol_opts;

	अगर (!netअगर_running(ndev))
		वापस 0;

	disable_napi(priv);
	netअगर_tx_lock(ndev);
	netअगर_device_detach(ndev);
	netअगर_tx_unlock(ndev);

	gfar_halt(priv);

	अगर (wol & GFAR_WOL_MAGIC) अणु
		/* Enable पूर्णांकerrupt on Magic Packet */
		gfar_ग_लिखो(&regs->imask, IMASK_MAG);

		/* Enable Magic Packet mode */
		tempval = gfar_पढ़ो(&regs->maccfg2);
		tempval |= MACCFG2_MPEN;
		gfar_ग_लिखो(&regs->maccfg2, tempval);

		/* re-enable the Rx block */
		tempval = gfar_पढ़ो(&regs->maccfg1);
		tempval |= MACCFG1_RX_EN;
		gfar_ग_लिखो(&regs->maccfg1, tempval);

	पूर्ण अन्यथा अगर (wol & GFAR_WOL_खाताR_UCAST) अणु
		gfar_filer_config_wol(priv);
		gfar_start_wol_filer(priv);

	पूर्ण अन्यथा अणु
		phy_stop(ndev->phydev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_resume(काष्ठा device *dev)
अणु
	काष्ठा gfar_निजी *priv = dev_get_drvdata(dev);
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा gfar __iomem *regs = priv->gfargrp[0].regs;
	u32 tempval;
	u16 wol = priv->wol_opts;

	अगर (!netअगर_running(ndev))
		वापस 0;

	अगर (wol & GFAR_WOL_MAGIC) अणु
		/* Disable Magic Packet mode */
		tempval = gfar_पढ़ो(&regs->maccfg2);
		tempval &= ~MACCFG2_MPEN;
		gfar_ग_लिखो(&regs->maccfg2, tempval);

	पूर्ण अन्यथा अगर (wol & GFAR_WOL_खाताR_UCAST) अणु
		/* need to stop rx only, tx is alपढ़ोy करोwn */
		gfar_halt(priv);
		gfar_filer_restore_table(priv);

	पूर्ण अन्यथा अणु
		phy_start(ndev->phydev);
	पूर्ण

	gfar_start(priv);

	netअगर_device_attach(ndev);
	enable_napi(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक gfar_restore(काष्ठा device *dev)
अणु
	काष्ठा gfar_निजी *priv = dev_get_drvdata(dev);
	काष्ठा net_device *ndev = priv->ndev;

	अगर (!netअगर_running(ndev)) अणु
		netअगर_device_attach(ndev);

		वापस 0;
	पूर्ण

	gfar_init_bds(ndev);

	gfar_mac_reset(priv);

	gfar_init_tx_rx_base(priv);

	gfar_start(priv);

	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	अगर (ndev->phydev)
		phy_start(ndev->phydev);

	netअगर_device_attach(ndev);
	enable_napi(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gfar_pm_ops = अणु
	.suspend = gfar_suspend,
	.resume = gfar_resume,
	.मुक्तze = gfar_suspend,
	.thaw = gfar_resume,
	.restore = gfar_restore,
पूर्ण;

#घोषणा GFAR_PM_OPS (&gfar_pm_ops)

#अन्यथा

#घोषणा GFAR_PM_OPS शून्य

#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id gfar_match[] =
अणु
	अणु
		.type = "network",
		.compatible = "gianfar",
	पूर्ण,
	अणु
		.compatible = "fsl,etsec2",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gfar_match);

/* Structure क्रम a device driver */
अटल काष्ठा platक्रमm_driver gfar_driver = अणु
	.driver = अणु
		.name = "fsl-gianfar",
		.pm = GFAR_PM_OPS,
		.of_match_table = gfar_match,
	पूर्ण,
	.probe = gfar_probe,
	.हटाओ = gfar_हटाओ,
पूर्ण;

module_platक्रमm_driver(gfar_driver);
