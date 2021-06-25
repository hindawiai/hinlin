<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Driver क्रम the Macपूर्णांकosh 68K onboard MACE controller with PSC
 *	driven DMA. The MACE driver code is derived from mace.c. The
 *	Mac68k theory of operation is courtesy of the MacBSD wizards.
 *
 *	Copyright (C) 1996 Paul Mackerras.
 *	Copyright (C) 1998 Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Modअगरied heavily by Joshua M. Thompson based on Dave Huang's NetBSD driver
 *
 *	Copyright (C) 2007 Finn Thain
 *
 *	Converted to DMA API, converted to unअगरied driver model,
 *	sync'd some routines with mace.c and fixed various bugs.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/crc32.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_psc.h>
#समावेश <यंत्र/page.h>
#समावेश "mace.h"

अटल अक्षर mac_mace_string[] = "macmace";

#घोषणा N_TX_BUFF_ORDER	0
#घोषणा N_TX_RING	(1 << N_TX_BUFF_ORDER)
#घोषणा N_RX_BUFF_ORDER	3
#घोषणा N_RX_RING	(1 << N_RX_BUFF_ORDER)

#घोषणा TX_TIMEOUT	HZ

#घोषणा MACE_BUFF_SIZE	0x800

/* Chip rev needs workaround on HW & multicast addr change */
#घोषणा BROKEN_ADDRCHG_REV	0x0941

/* The MACE is simply wired करोwn on a Mac68K box */

#घोषणा MACE_BASE	(व्योम *)(0x50F1C000)
#घोषणा MACE_PROM	(व्योम *)(0x50F08001)

काष्ठा mace_data अणु
	अस्थिर काष्ठा mace *mace;
	अचिन्हित अक्षर *tx_ring;
	dma_addr_t tx_ring_phys;
	अचिन्हित अक्षर *rx_ring;
	dma_addr_t rx_ring_phys;
	पूर्णांक dma_पूर्णांकr;
	पूर्णांक rx_slot, rx_tail;
	पूर्णांक tx_slot, tx_sloti, tx_count;
	पूर्णांक chipid;
	काष्ठा device *device;
पूर्ण;

काष्ठा mace_frame अणु
	u8	rcvcnt;
	u8	pad1;
	u8	rcvsts;
	u8	pad2;
	u8	rntpc;
	u8	pad3;
	u8	rcvcc;
	u8	pad4;
	u32	pad5;
	u32	pad6;
	u8	data[1];
	/* And frame जारीs.. */
पूर्ण;

#घोषणा PRIV_BYTES	माप(काष्ठा mace_data)

अटल पूर्णांक mace_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक mace_बंद(काष्ठा net_device *dev);
अटल netdev_tx_t mace_xmit_start(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम mace_set_multicast(काष्ठा net_device *dev);
अटल पूर्णांक mace_set_address(काष्ठा net_device *dev, व्योम *addr);
अटल व्योम mace_reset(काष्ठा net_device *dev);
अटल irqवापस_t mace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t mace_dma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल व्योम mace_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम __mace_set_address(काष्ठा net_device *dev, व्योम *addr);

/*
 * Load a receive DMA channel with a base address and ring length
 */

अटल व्योम mace_load_rxdma_base(काष्ठा net_device *dev, पूर्णांक set)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);

	psc_ग_लिखो_word(PSC_ENETRD_CMD + set, 0x0100);
	psc_ग_लिखो_दीर्घ(PSC_ENETRD_ADDR + set, (u32) mp->rx_ring_phys);
	psc_ग_लिखो_दीर्घ(PSC_ENETRD_LEN + set, N_RX_RING);
	psc_ग_लिखो_word(PSC_ENETRD_CMD + set, 0x9800);
	mp->rx_tail = 0;
पूर्ण

/*
 * Reset the receive DMA subप्रणाली
 */

अटल व्योम mace_rxdma_reset(काष्ठा net_device *dev)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mace = mp->mace;
	u8 maccc = mace->maccc;

	mace->maccc = maccc & ~ENRCV;

	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x8800);
	mace_load_rxdma_base(dev, 0x00);
	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x0400);

	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x8800);
	mace_load_rxdma_base(dev, 0x10);
	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x0400);

	mace->maccc = maccc;
	mp->rx_slot = 0;

	psc_ग_लिखो_word(PSC_ENETRD_CMD + PSC_SET0, 0x9800);
	psc_ग_लिखो_word(PSC_ENETRD_CMD + PSC_SET1, 0x9800);
पूर्ण

/*
 * Reset the transmit DMA subप्रणाली
 */

अटल व्योम mace_txdma_reset(काष्ठा net_device *dev)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mace = mp->mace;
	u8 maccc;

	psc_ग_लिखो_word(PSC_ENETWR_CTL, 0x8800);

	maccc = mace->maccc;
	mace->maccc = maccc & ~ENXMT;

	mp->tx_slot = mp->tx_sloti = 0;
	mp->tx_count = N_TX_RING;

	psc_ग_लिखो_word(PSC_ENETWR_CTL, 0x0400);
	mace->maccc = maccc;
पूर्ण

/*
 * Disable DMA
 */

अटल व्योम mace_dma_off(काष्ठा net_device *dev)
अणु
	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x8800);
	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x1000);
	psc_ग_लिखो_word(PSC_ENETRD_CMD + PSC_SET0, 0x1100);
	psc_ग_लिखो_word(PSC_ENETRD_CMD + PSC_SET1, 0x1100);

	psc_ग_लिखो_word(PSC_ENETWR_CTL, 0x8800);
	psc_ग_लिखो_word(PSC_ENETWR_CTL, 0x1000);
	psc_ग_लिखो_word(PSC_ENETWR_CMD + PSC_SET0, 0x1100);
	psc_ग_लिखो_word(PSC_ENETWR_CMD + PSC_SET1, 0x1100);
पूर्ण

अटल स्थिर काष्ठा net_device_ops mace_netdev_ops = अणु
	.nकरो_खोलो		= mace_खोलो,
	.nकरो_stop		= mace_बंद,
	.nकरो_start_xmit		= mace_xmit_start,
	.nकरो_tx_समयout		= mace_tx_समयout,
	.nकरो_set_rx_mode	= mace_set_multicast,
	.nकरो_set_mac_address	= mace_set_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/*
 * Not really much of a probe. The hardware table tells us अगर this
 * model of Macपूर्णांकrash has a MACE (AV macपूर्णांकoshes)
 */

अटल पूर्णांक mace_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक j;
	काष्ठा mace_data *mp;
	अचिन्हित अक्षर *addr;
	काष्ठा net_device *dev;
	अचिन्हित अक्षर checksum = 0;
	पूर्णांक err;

	dev = alloc_etherdev(PRIV_BYTES);
	अगर (!dev)
		वापस -ENOMEM;

	mp = netdev_priv(dev);

	mp->device = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	dev->base_addr = (u32)MACE_BASE;
	mp->mace = MACE_BASE;

	dev->irq = IRQ_MAC_MACE;
	mp->dma_पूर्णांकr = IRQ_MAC_MACE_DMA;

	mp->chipid = mp->mace->chipid_hi << 8 | mp->mace->chipid_lo;

	/*
	 * The PROM contains 8 bytes which total 0xFF when XOR'd
	 * together. Due to the usual peculiar apple brain damage
	 * the bytes are spaced out in a strange boundary and the
	 * bits are reversed.
	 */

	addr = MACE_PROM;

	क्रम (j = 0; j < 6; ++j) अणु
		u8 v = bitrev8(addr[j<<4]);
		checksum ^= v;
		dev->dev_addr[j] = v;
	पूर्ण
	क्रम (; j < 8; ++j) अणु
		checksum ^= bitrev8(addr[j<<4]);
	पूर्ण

	अगर (checksum != 0xFF) अणु
		मुक्त_netdev(dev);
		वापस -ENODEV;
	पूर्ण

	dev->netdev_ops		= &mace_netdev_ops;
	dev->watchकरोg_समयo	= TX_TIMEOUT;

	pr_info("Onboard MACE, hardware address %pM, chip revision 0x%04X\n",
		dev->dev_addr, mp->chipid);

	err = रेजिस्टर_netdev(dev);
	अगर (!err)
		वापस 0;

	मुक्त_netdev(dev);
	वापस err;
पूर्ण

/*
 * Reset the chip.
 */

अटल व्योम mace_reset(काष्ठा net_device *dev)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;
	पूर्णांक i;

	/* soft-reset the chip */
	i = 200;
	जबतक (--i) अणु
		mb->biucc = SWRST;
		अगर (mb->biucc & SWRST) अणु
			udelay(10);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (!i) अणु
		prपूर्णांकk(KERN_ERR "macmace: cannot reset chip!\n");
		वापस;
	पूर्ण

	mb->maccc = 0;	/* turn off tx, rx */
	mb->imr = 0xFF;	/* disable all पूर्णांकrs क्रम now */
	i = mb->ir;

	mb->biucc = XMTSP_64;
	mb->utr = RTRD;
	mb->fअगरocc = XMTFW_8 | RCVFW_64 | XMTFWU | RCVFWU;

	mb->xmtfc = AUTO_PAD_XMIT; /* स्वतः-pad लघु frames */
	mb->rcvfc = 0;

	/* load up the hardware address */
	__mace_set_address(dev, dev->dev_addr);

	/* clear the multicast filter */
	अगर (mp->chipid == BROKEN_ADDRCHG_REV)
		mb->iac = LOGADDR;
	अन्यथा अणु
		mb->iac = ADDRCHG | LOGADDR;
		जबतक ((mb->iac & ADDRCHG) != 0)
			;
	पूर्ण
	क्रम (i = 0; i < 8; ++i)
		mb->ladrf = 0;

	/* करोne changing address */
	अगर (mp->chipid != BROKEN_ADDRCHG_REV)
		mb->iac = 0;

	mb->plscc = PORTSEL_AUI;
पूर्ण

/*
 * Load the address on a mace controller.
 */

अटल व्योम __mace_set_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;
	अचिन्हित अक्षर *p = addr;
	पूर्णांक i;

	/* load up the hardware address */
	अगर (mp->chipid == BROKEN_ADDRCHG_REV)
		mb->iac = PHYADDR;
	अन्यथा अणु
		mb->iac = ADDRCHG | PHYADDR;
		जबतक ((mb->iac & ADDRCHG) != 0)
			;
	पूर्ण
	क्रम (i = 0; i < 6; ++i)
		mb->padr = dev->dev_addr[i] = p[i];
	अगर (mp->chipid != BROKEN_ADDRCHG_REV)
		mb->iac = 0;
पूर्ण

अटल पूर्णांक mace_set_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;
	अचिन्हित दीर्घ flags;
	u8 maccc;

	local_irq_save(flags);

	maccc = mb->maccc;

	__mace_set_address(dev, addr);

	mb->maccc = maccc;

	local_irq_restore(flags);

	वापस 0;
पूर्ण

/*
 * Open the Macपूर्णांकosh MACE. Most of this is playing with the DMA
 * engine. The ethernet chip is quite मित्रly.
 */

अटल पूर्णांक mace_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;

	/* reset the chip */
	mace_reset(dev);

	अगर (request_irq(dev->irq, mace_पूर्णांकerrupt, 0, dev->name, dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: can't get irq %d\n", dev->name, dev->irq);
		वापस -EAGAIN;
	पूर्ण
	अगर (request_irq(mp->dma_पूर्णांकr, mace_dma_पूर्णांकr, 0, dev->name, dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: can't get irq %d\n", dev->name, mp->dma_पूर्णांकr);
		मुक्त_irq(dev->irq, dev);
		वापस -EAGAIN;
	पूर्ण

	/* Allocate the DMA ring buffers */

	mp->tx_ring = dma_alloc_coherent(mp->device,
					 N_TX_RING * MACE_BUFF_SIZE,
					 &mp->tx_ring_phys, GFP_KERNEL);
	अगर (mp->tx_ring == शून्य)
		जाओ out1;

	mp->rx_ring = dma_alloc_coherent(mp->device,
					 N_RX_RING * MACE_BUFF_SIZE,
					 &mp->rx_ring_phys, GFP_KERNEL);
	अगर (mp->rx_ring == शून्य)
		जाओ out2;

	mace_dma_off(dev);

	/* Not sure what these करो */

	psc_ग_लिखो_word(PSC_ENETWR_CTL, 0x9000);
	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x9000);
	psc_ग_लिखो_word(PSC_ENETWR_CTL, 0x0400);
	psc_ग_लिखो_word(PSC_ENETRD_CTL, 0x0400);

	mace_rxdma_reset(dev);
	mace_txdma_reset(dev);

	/* turn it on! */
	mb->maccc = ENXMT | ENRCV;
	/* enable all पूर्णांकerrupts except receive पूर्णांकerrupts */
	mb->imr = RCVINT;
	वापस 0;

out2:
	dma_मुक्त_coherent(mp->device, N_TX_RING * MACE_BUFF_SIZE,
	                  mp->tx_ring, mp->tx_ring_phys);
out1:
	मुक्त_irq(dev->irq, dev);
	मुक्त_irq(mp->dma_पूर्णांकr, dev);
	वापस -ENOMEM;
पूर्ण

/*
 * Shut करोwn the mace and its पूर्णांकerrupt channel
 */

अटल पूर्णांक mace_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;

	mb->maccc = 0;		/* disable rx and tx	 */
	mb->imr = 0xFF;		/* disable all irqs	 */
	mace_dma_off(dev);	/* disable rx and tx dma */

	वापस 0;
पूर्ण

/*
 * Transmit a frame
 */

अटल netdev_tx_t mace_xmit_start(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/* Stop the queue since there's only the one buffer */

	local_irq_save(flags);
	netअगर_stop_queue(dev);
	अगर (!mp->tx_count) अणु
		prपूर्णांकk(KERN_ERR "macmace: tx queue running but no free buffers.\n");
		local_irq_restore(flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	mp->tx_count--;
	local_irq_restore(flags);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	/* We need to copy पूर्णांकo our xmit buffer to take care of alignment and caching issues */
	skb_copy_from_linear_data(skb, mp->tx_ring, skb->len);

	/* load the Tx DMA and fire it off */

	psc_ग_लिखो_दीर्घ(PSC_ENETWR_ADDR + mp->tx_slot, (u32)  mp->tx_ring_phys);
	psc_ग_लिखो_दीर्घ(PSC_ENETWR_LEN + mp->tx_slot, skb->len);
	psc_ग_लिखो_word(PSC_ENETWR_CMD + mp->tx_slot, 0x9800);

	mp->tx_slot ^= 0x10;

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम mace_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;
	पूर्णांक i;
	u32 crc;
	u8 maccc;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	maccc = mb->maccc;
	mb->maccc &= ~PROM;

	अगर (dev->flags & IFF_PROMISC) अणु
		mb->maccc |= PROM;
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर multicast_filter[8];
		काष्ठा netdev_hw_addr *ha;

		अगर (dev->flags & IFF_ALLMULTI) अणु
			क्रम (i = 0; i < 8; i++) अणु
				multicast_filter[i] = 0xFF;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 8; i++)
				multicast_filter[i] = 0;
			netdev_क्रम_each_mc_addr(ha, dev) अणु
				crc = ether_crc_le(6, ha->addr);
				/* bit number in multicast_filter */
				i = crc >> 26;
				multicast_filter[i >> 3] |= 1 << (i & 7);
			पूर्ण
		पूर्ण

		अगर (mp->chipid == BROKEN_ADDRCHG_REV)
			mb->iac = LOGADDR;
		अन्यथा अणु
			mb->iac = ADDRCHG | LOGADDR;
			जबतक ((mb->iac & ADDRCHG) != 0)
				;
		पूर्ण
		क्रम (i = 0; i < 8; ++i)
			mb->ladrf = multicast_filter[i];
		अगर (mp->chipid != BROKEN_ADDRCHG_REV)
			mb->iac = 0;
	पूर्ण

	mb->maccc = maccc;
	local_irq_restore(flags);
पूर्ण

अटल व्योम mace_handle_misc_पूर्णांकrs(काष्ठा net_device *dev, पूर्णांक पूर्णांकr)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;
	अटल पूर्णांक mace_babbles, mace_jabbers;

	अगर (पूर्णांकr & MPCO)
		dev->stats.rx_missed_errors += 256;
	dev->stats.rx_missed_errors += mb->mpc;   /* पढ़ोing clears it */
	अगर (पूर्णांकr & RNTPCO)
		dev->stats.rx_length_errors += 256;
	dev->stats.rx_length_errors += mb->rntpc; /* पढ़ोing clears it */
	अगर (पूर्णांकr & CERR)
		++dev->stats.tx_heartbeat_errors;
	अगर (पूर्णांकr & BABBLE)
		अगर (mace_babbles++ < 4)
			prपूर्णांकk(KERN_DEBUG "macmace: babbling transmitter\n");
	अगर (पूर्णांकr & JABBER)
		अगर (mace_jabbers++ < 4)
			prपूर्णांकk(KERN_DEBUG "macmace: jabbering transceiver\n");
पूर्ण

अटल irqवापस_t mace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;
	पूर्णांक पूर्णांकr, fs;
	अचिन्हित दीर्घ flags;

	/* करोn't want the dma पूर्णांकerrupt handler to fire */
	local_irq_save(flags);

	पूर्णांकr = mb->ir; /* पढ़ो पूर्णांकerrupt रेजिस्टर */
	mace_handle_misc_पूर्णांकrs(dev, पूर्णांकr);

	अगर (पूर्णांकr & XMTINT) अणु
		fs = mb->xmtfs;
		अगर ((fs & XMTSV) == 0) अणु
			prपूर्णांकk(KERN_ERR "macmace: xmtfs not valid! (fs=%x)\n", fs);
			mace_reset(dev);
			/*
			 * XXX mace likes to hang the machine after a xmtfs error.
			 * This is hard to reproduce, resetting *may* help
			 */
		पूर्ण
		/* dma should have finished */
		अगर (!mp->tx_count) अणु
			prपूर्णांकk(KERN_DEBUG "macmace: tx ring ran out? (fs=%x)\n", fs);
		पूर्ण
		/* Update stats */
		अगर (fs & (UFLO|LCOL|LCAR|RTRY)) अणु
			++dev->stats.tx_errors;
			अगर (fs & LCAR)
				++dev->stats.tx_carrier_errors;
			अन्यथा अगर (fs & (UFLO|LCOL|RTRY)) अणु
				++dev->stats.tx_पातed_errors;
				अगर (mb->xmtfs & UFLO) अणु
					dev->stats.tx_fअगरo_errors++;
					mace_txdma_reset(dev);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mp->tx_count)
		netअगर_wake_queue(dev);

	local_irq_restore(flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mace_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mace_data *mp = netdev_priv(dev);
	अस्थिर काष्ठा mace *mb = mp->mace;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* turn off both tx and rx and reset the chip */
	mb->maccc = 0;
	prपूर्णांकk(KERN_ERR "macmace: transmit timeout - resetting\n");
	mace_txdma_reset(dev);
	mace_reset(dev);

	/* restart rx dma */
	mace_rxdma_reset(dev);

	mp->tx_count = N_TX_RING;
	netअगर_wake_queue(dev);

	/* turn it on! */
	mb->maccc = ENXMT | ENRCV;
	/* enable all पूर्णांकerrupts except receive पूर्णांकerrupts */
	mb->imr = RCVINT;

	local_irq_restore(flags);
पूर्ण

/*
 * Handle a newly arrived frame
 */

अटल व्योम mace_dma_rx_frame(काष्ठा net_device *dev, काष्ठा mace_frame *mf)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक frame_status = mf->rcvsts;

	अगर (frame_status & (RS_OFLO | RS_CLSN | RS_FRAMERR | RS_FCSERR)) अणु
		dev->stats.rx_errors++;
		अगर (frame_status & RS_OFLO)
			dev->stats.rx_fअगरo_errors++;
		अगर (frame_status & RS_CLSN)
			dev->stats.collisions++;
		अगर (frame_status & RS_FRAMERR)
			dev->stats.rx_frame_errors++;
		अगर (frame_status & RS_FCSERR)
			dev->stats.rx_crc_errors++;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक frame_length = mf->rcvcnt + ((frame_status & 0x0F) << 8 );

		skb = netdev_alloc_skb(dev, frame_length + 2);
		अगर (!skb) अणु
			dev->stats.rx_dropped++;
			वापस;
		पूर्ण
		skb_reserve(skb, 2);
		skb_put_data(skb, mf->data, frame_length);

		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += frame_length;
	पूर्ण
पूर्ण

/*
 * The PSC has passed us a DMA पूर्णांकerrupt event.
 */

अटल irqवापस_t mace_dma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा mace_data *mp = netdev_priv(dev);
	पूर्णांक left, head;
	u16 status;
	u32 baka;

	/* Not sure what this करोes */

	जबतक ((baka = psc_पढ़ो_दीर्घ(PSC_MYSTERY)) != psc_पढ़ो_दीर्घ(PSC_MYSTERY));
	अगर (!(baka & 0x60000000)) वापस IRQ_NONE;

	/*
	 * Process the पढ़ो queue
	 */

	status = psc_पढ़ो_word(PSC_ENETRD_CTL);

	अगर (status & 0x2000) अणु
		mace_rxdma_reset(dev);
	पूर्ण अन्यथा अगर (status & 0x0100) अणु
		psc_ग_लिखो_word(PSC_ENETRD_CMD + mp->rx_slot, 0x1100);

		left = psc_पढ़ो_दीर्घ(PSC_ENETRD_LEN + mp->rx_slot);
		head = N_RX_RING - left;

		/* Loop through the ring buffer and process new packages */

		जबतक (mp->rx_tail < head) अणु
			mace_dma_rx_frame(dev, (काष्ठा mace_frame*) (mp->rx_ring
				+ (mp->rx_tail * MACE_BUFF_SIZE)));
			mp->rx_tail++;
		पूर्ण

		/* If we're out of buffers in this ring then चयन to */
		/* the other set, otherwise just reactivate this one.  */

		अगर (!left) अणु
			mace_load_rxdma_base(dev, mp->rx_slot);
			mp->rx_slot ^= 0x10;
		पूर्ण अन्यथा अणु
			psc_ग_लिखो_word(PSC_ENETRD_CMD + mp->rx_slot, 0x9800);
		पूर्ण
	पूर्ण

	/*
	 * Process the ग_लिखो queue
	 */

	status = psc_पढ़ो_word(PSC_ENETWR_CTL);

	अगर (status & 0x2000) अणु
		mace_txdma_reset(dev);
	पूर्ण अन्यथा अगर (status & 0x0100) अणु
		psc_ग_लिखो_word(PSC_ENETWR_CMD + mp->tx_sloti, 0x0100);
		mp->tx_sloti ^= 0x10;
		mp->tx_count++;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Macintosh MACE ethernet driver");
MODULE_ALIAS("platform:macmace");

अटल पूर्णांक mac_mace_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा mace_data *mp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);

	मुक्त_irq(dev->irq, dev);
	मुक्त_irq(IRQ_MAC_MACE_DMA, dev);

	dma_मुक्त_coherent(mp->device, N_RX_RING * MACE_BUFF_SIZE,
	                  mp->rx_ring, mp->rx_ring_phys);
	dma_मुक्त_coherent(mp->device, N_TX_RING * MACE_BUFF_SIZE,
	                  mp->tx_ring, mp->tx_ring_phys);

	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mac_mace_driver = अणु
	.probe  = mace_probe,
	.हटाओ = mac_mace_device_हटाओ,
	.driver	= अणु
		.name	= mac_mace_string,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mac_mace_driver);
