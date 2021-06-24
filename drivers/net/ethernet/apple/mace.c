<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Network device driver क्रम the MACE ethernet controller on
 * Apple Powermacs.  Assumes it's under a DBDMA controller.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/crc32.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/macपन.स>

#समावेश "mace.h"

अटल पूर्णांक port_aaui = -1;

#घोषणा N_RX_RING	8
#घोषणा N_TX_RING	6
#घोषणा MAX_TX_ACTIVE	1
#घोषणा NCMDS_TX	1	/* dma commands per element in tx ring */
#घोषणा RX_BUFLEN	(ETH_FRAME_LEN + 8)
#घोषणा TX_TIMEOUT	HZ	/* 1 second */

/* Chip rev needs workaround on HW & multicast addr change */
#घोषणा BROKEN_ADDRCHG_REV	0x0941

/* Bits in transmit DMA status */
#घोषणा TX_DMA_ERR	0x80

काष्ठा mace_data अणु
    अस्थिर काष्ठा mace __iomem *mace;
    अस्थिर काष्ठा dbdma_regs __iomem *tx_dma;
    पूर्णांक tx_dma_पूर्णांकr;
    अस्थिर काष्ठा dbdma_regs __iomem *rx_dma;
    पूर्णांक rx_dma_पूर्णांकr;
    अस्थिर काष्ठा dbdma_cmd *tx_cmds;	/* xmit dma command list */
    अस्थिर काष्ठा dbdma_cmd *rx_cmds;	/* recv dma command list */
    काष्ठा sk_buff *rx_bufs[N_RX_RING];
    पूर्णांक rx_fill;
    पूर्णांक rx_empty;
    काष्ठा sk_buff *tx_bufs[N_TX_RING];
    पूर्णांक tx_fill;
    पूर्णांक tx_empty;
    अचिन्हित अक्षर maccc;
    अचिन्हित अक्षर tx_fullup;
    अचिन्हित अक्षर tx_active;
    अचिन्हित अक्षर tx_bad_runt;
    काष्ठा समयr_list tx_समयout;
    पूर्णांक समयout_active;
    पूर्णांक port_aaui;
    पूर्णांक chipid;
    काष्ठा macio_dev *mdev;
    spinlock_t lock;
पूर्ण;

/*
 * Number of bytes of निजी data per MACE: allow enough क्रम
 * the rx and tx dma commands plus a branch dma command each,
 * and another 16 bytes to allow us to align the dma command
 * buffers on a 16 byte boundary.
 */
#घोषणा PRIV_BYTES	(माप(काष्ठा mace_data) \
	+ (N_RX_RING + NCMDS_TX * N_TX_RING + 3) * माप(काष्ठा dbdma_cmd))

अटल पूर्णांक mace_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक mace_बंद(काष्ठा net_device *dev);
अटल netdev_tx_t mace_xmit_start(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम mace_set_multicast(काष्ठा net_device *dev);
अटल व्योम mace_reset(काष्ठा net_device *dev);
अटल पूर्णांक mace_set_address(काष्ठा net_device *dev, व्योम *addr);
अटल irqवापस_t mace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t mace_txdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t mace_rxdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल व्योम mace_set_समयout(काष्ठा net_device *dev);
अटल व्योम mace_tx_समयout(काष्ठा समयr_list *t);
अटल अंतरभूत व्योम dbdma_reset(अस्थिर काष्ठा dbdma_regs __iomem *dma);
अटल अंतरभूत व्योम mace_clean_rings(काष्ठा mace_data *mp);
अटल व्योम __mace_set_address(काष्ठा net_device *dev, व्योम *addr);

/*
 * If we can't get a skbuff when we need it, we use this area क्रम DMA.
 */
अटल अचिन्हित अक्षर *dummy_buf;

अटल स्थिर काष्ठा net_device_ops mace_netdev_ops = अणु
	.nकरो_खोलो		= mace_खोलो,
	.nकरो_stop		= mace_बंद,
	.nकरो_start_xmit		= mace_xmit_start,
	.nकरो_set_rx_mode	= mace_set_multicast,
	.nकरो_set_mac_address	= mace_set_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक mace_probe(काष्ठा macio_dev *mdev, स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा device_node *mace = macio_get_of_node(mdev);
	काष्ठा net_device *dev;
	काष्ठा mace_data *mp;
	स्थिर अचिन्हित अक्षर *addr;
	पूर्णांक j, rev, rc = -EBUSY;

	अगर (macio_resource_count(mdev) != 3 || macio_irq_count(mdev) != 3) अणु
		prपूर्णांकk(KERN_ERR "can't use MACE %pOF: need 3 addrs and 3 irqs\n",
		       mace);
		वापस -ENODEV;
	पूर्ण

	addr = of_get_property(mace, "mac-address", शून्य);
	अगर (addr == शून्य) अणु
		addr = of_get_property(mace, "local-mac-address", शून्य);
		अगर (addr == शून्य) अणु
			prपूर्णांकk(KERN_ERR "Can't get mac-address for MACE %pOF\n",
			       mace);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * lazy allocate the driver-wide dummy buffer. (Note that we
	 * never have more than one MACE in the प्रणाली anyway)
	 */
	अगर (dummy_buf == शून्य) अणु
		dummy_buf = kदो_स्मृति(RX_BUFLEN+2, GFP_KERNEL);
		अगर (dummy_buf == शून्य)
			वापस -ENOMEM;
	पूर्ण

	अगर (macio_request_resources(mdev, "mace")) अणु
		prपूर्णांकk(KERN_ERR "MACE: can't request IO resources !\n");
		वापस -EBUSY;
	पूर्ण

	dev = alloc_etherdev(PRIV_BYTES);
	अगर (!dev) अणु
		rc = -ENOMEM;
		जाओ err_release;
	पूर्ण
	SET_NETDEV_DEV(dev, &mdev->ofdev.dev);

	mp = netdev_priv(dev);
	mp->mdev = mdev;
	macio_set_drvdata(mdev, dev);

	dev->base_addr = macio_resource_start(mdev, 0);
	mp->mace = ioremap(dev->base_addr, 0x1000);
	अगर (mp->mace == शून्य) अणु
		prपूर्णांकk(KERN_ERR "MACE: can't map IO resources !\n");
		rc = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण
	dev->irq = macio_irq(mdev, 0);

	rev = addr[0] == 0 && addr[1] == 0xA0;
	क्रम (j = 0; j < 6; ++j) अणु
		dev->dev_addr[j] = rev ? bitrev8(addr[j]): addr[j];
	पूर्ण
	mp->chipid = (in_8(&mp->mace->chipid_hi) << 8) |
			in_8(&mp->mace->chipid_lo);


	mp = netdev_priv(dev);
	mp->maccc = ENXMT | ENRCV;

	mp->tx_dma = ioremap(macio_resource_start(mdev, 1), 0x1000);
	अगर (mp->tx_dma == शून्य) अणु
		prपूर्णांकk(KERN_ERR "MACE: can't map TX DMA resources !\n");
		rc = -ENOMEM;
		जाओ err_unmap_io;
	पूर्ण
	mp->tx_dma_पूर्णांकr = macio_irq(mdev, 1);

	mp->rx_dma = ioremap(macio_resource_start(mdev, 2), 0x1000);
	अगर (mp->rx_dma == शून्य) अणु
		prपूर्णांकk(KERN_ERR "MACE: can't map RX DMA resources !\n");
		rc = -ENOMEM;
		जाओ err_unmap_tx_dma;
	पूर्ण
	mp->rx_dma_पूर्णांकr = macio_irq(mdev, 2);

	mp->tx_cmds = (अस्थिर काष्ठा dbdma_cmd *) DBDMA_ALIGN(mp + 1);
	mp->rx_cmds = mp->tx_cmds + NCMDS_TX * N_TX_RING + 1;

	स_रखो((अक्षर *) mp->tx_cmds, 0,
	       (NCMDS_TX*N_TX_RING + N_RX_RING + 2) * माप(काष्ठा dbdma_cmd));
	समयr_setup(&mp->tx_समयout, mace_tx_समयout, 0);
	spin_lock_init(&mp->lock);
	mp->समयout_active = 0;

	अगर (port_aaui >= 0)
		mp->port_aaui = port_aaui;
	अन्यथा अणु
		/* Apple Network Server uses the AAUI port */
		अगर (of_machine_is_compatible("AAPL,ShinerESB"))
			mp->port_aaui = 1;
		अन्यथा अणु
#अगर_घोषित CONFIG_MACE_AAUI_PORT
			mp->port_aaui = 1;
#अन्यथा
			mp->port_aaui = 0;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	dev->netdev_ops = &mace_netdev_ops;

	/*
	 * Most of what is below could be moved to mace_खोलो()
	 */
	mace_reset(dev);

	rc = request_irq(dev->irq, mace_पूर्णांकerrupt, 0, "MACE", dev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "MACE: can't get irq %d\n", dev->irq);
		जाओ err_unmap_rx_dma;
	पूर्ण
	rc = request_irq(mp->tx_dma_पूर्णांकr, mace_txdma_पूर्णांकr, 0, "MACE-txdma", dev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "MACE: can't get irq %d\n", mp->tx_dma_पूर्णांकr);
		जाओ err_मुक्त_irq;
	पूर्ण
	rc = request_irq(mp->rx_dma_पूर्णांकr, mace_rxdma_पूर्णांकr, 0, "MACE-rxdma", dev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "MACE: can't get irq %d\n", mp->rx_dma_पूर्णांकr);
		जाओ err_मुक्त_tx_irq;
	पूर्ण

	rc = रेजिस्टर_netdev(dev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "MACE: Cannot register net device, aborting.\n");
		जाओ err_मुक्त_rx_irq;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: MACE at %pM, chip revision %d.%d\n",
	       dev->name, dev->dev_addr,
	       mp->chipid >> 8, mp->chipid & 0xff);

	वापस 0;

 err_मुक्त_rx_irq:
	मुक्त_irq(macio_irq(mdev, 2), dev);
 err_मुक्त_tx_irq:
	मुक्त_irq(macio_irq(mdev, 1), dev);
 err_मुक्त_irq:
	मुक्त_irq(macio_irq(mdev, 0), dev);
 err_unmap_rx_dma:
	iounmap(mp->rx_dma);
 err_unmap_tx_dma:
	iounmap(mp->tx_dma);
 err_unmap_io:
	iounmap(mp->mace);
 err_मुक्त:
	मुक्त_netdev(dev);
 err_release:
	macio_release_resources(mdev);

	वापस rc;
पूर्ण

अटल पूर्णांक mace_हटाओ(काष्ठा macio_dev *mdev)
अणु
	काष्ठा net_device *dev = macio_get_drvdata(mdev);
	काष्ठा mace_data *mp;

	BUG_ON(dev == शून्य);

	macio_set_drvdata(mdev, शून्य);

	mp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);

	मुक्त_irq(dev->irq, dev);
	मुक्त_irq(mp->tx_dma_पूर्णांकr, dev);
	मुक्त_irq(mp->rx_dma_पूर्णांकr, dev);

	iounmap(mp->rx_dma);
	iounmap(mp->tx_dma);
	iounmap(mp->mace);

	मुक्त_netdev(dev);

	macio_release_resources(mdev);

	वापस 0;
पूर्ण

अटल व्योम dbdma_reset(अस्थिर काष्ठा dbdma_regs __iomem *dma)
अणु
    पूर्णांक i;

    out_le32(&dma->control, (WAKE|FLUSH|PAUSE|RUN) << 16);

    /*
     * Yes this looks peculiar, but apparently it needs to be this
     * way on some machines.
     */
    क्रम (i = 200; i > 0; --i)
	अगर (le32_to_cpu(dma->control) & RUN)
	    udelay(1);
पूर्ण

अटल व्योम mace_reset(काष्ठा net_device *dev)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    पूर्णांक i;

    /* soft-reset the chip */
    i = 200;
    जबतक (--i) अणु
	out_8(&mb->biucc, SWRST);
	अगर (in_8(&mb->biucc) & SWRST) अणु
	    udelay(10);
	    जारी;
	पूर्ण
	अवरोध;
    पूर्ण
    अगर (!i) अणु
	prपूर्णांकk(KERN_ERR "mace: cannot reset chip!\n");
	वापस;
    पूर्ण

    out_8(&mb->imr, 0xff);	/* disable all पूर्णांकrs क्रम now */
    i = in_8(&mb->ir);
    out_8(&mb->maccc, 0);	/* turn off tx, rx */

    out_8(&mb->biucc, XMTSP_64);
    out_8(&mb->utr, RTRD);
    out_8(&mb->fअगरocc, RCVFW_32 | XMTFW_16 | XMTFWU | RCVFWU | XMTBRST);
    out_8(&mb->xmtfc, AUTO_PAD_XMIT); /* स्वतः-pad लघु frames */
    out_8(&mb->rcvfc, 0);

    /* load up the hardware address */
    __mace_set_address(dev, dev->dev_addr);

    /* clear the multicast filter */
    अगर (mp->chipid == BROKEN_ADDRCHG_REV)
	out_8(&mb->iac, LOGADDR);
    अन्यथा अणु
	out_8(&mb->iac, ADDRCHG | LOGADDR);
	जबतक ((in_8(&mb->iac) & ADDRCHG) != 0)
		;
    पूर्ण
    क्रम (i = 0; i < 8; ++i)
	out_8(&mb->ladrf, 0);

    /* करोne changing address */
    अगर (mp->chipid != BROKEN_ADDRCHG_REV)
	out_8(&mb->iac, 0);

    अगर (mp->port_aaui)
    	out_8(&mb->plscc, PORTSEL_AUI + ENPLSIO);
    अन्यथा
    	out_8(&mb->plscc, PORTSEL_GPSI + ENPLSIO);
पूर्ण

अटल व्योम __mace_set_address(काष्ठा net_device *dev, व्योम *addr)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    अचिन्हित अक्षर *p = addr;
    पूर्णांक i;

    /* load up the hardware address */
    अगर (mp->chipid == BROKEN_ADDRCHG_REV)
    	out_8(&mb->iac, PHYADDR);
    अन्यथा अणु
    	out_8(&mb->iac, ADDRCHG | PHYADDR);
	जबतक ((in_8(&mb->iac) & ADDRCHG) != 0)
	    ;
    पूर्ण
    क्रम (i = 0; i < 6; ++i)
	out_8(&mb->padr, dev->dev_addr[i] = p[i]);
    अगर (mp->chipid != BROKEN_ADDRCHG_REV)
        out_8(&mb->iac, 0);
पूर्ण

अटल पूर्णांक mace_set_address(काष्ठा net_device *dev, व्योम *addr)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&mp->lock, flags);

    __mace_set_address(dev, addr);

    /* note: setting ADDRCHG clears ENRCV */
    out_8(&mb->maccc, mp->maccc);

    spin_unlock_irqrestore(&mp->lock, flags);
    वापस 0;
पूर्ण

अटल अंतरभूत व्योम mace_clean_rings(काष्ठा mace_data *mp)
अणु
    पूर्णांक i;

    /* मुक्त some skb's */
    क्रम (i = 0; i < N_RX_RING; ++i) अणु
	अगर (mp->rx_bufs[i] != शून्य) अणु
	    dev_kमुक्त_skb(mp->rx_bufs[i]);
	    mp->rx_bufs[i] = शून्य;
	पूर्ण
    पूर्ण
    क्रम (i = mp->tx_empty; i != mp->tx_fill; ) अणु
	dev_kमुक्त_skb(mp->tx_bufs[i]);
	अगर (++i >= N_TX_RING)
	    i = 0;
    पूर्ण
पूर्ण

अटल पूर्णांक mace_खोलो(काष्ठा net_device *dev)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    अस्थिर काष्ठा dbdma_regs __iomem *rd = mp->rx_dma;
    अस्थिर काष्ठा dbdma_regs __iomem *td = mp->tx_dma;
    अस्थिर काष्ठा dbdma_cmd *cp;
    पूर्णांक i;
    काष्ठा sk_buff *skb;
    अचिन्हित अक्षर *data;

    /* reset the chip */
    mace_reset(dev);

    /* initialize list of sk_buffs क्रम receiving and set up recv dma */
    mace_clean_rings(mp);
    स_रखो((अक्षर *)mp->rx_cmds, 0, N_RX_RING * माप(काष्ठा dbdma_cmd));
    cp = mp->rx_cmds;
    क्रम (i = 0; i < N_RX_RING - 1; ++i) अणु
	skb = netdev_alloc_skb(dev, RX_BUFLEN + 2);
	अगर (!skb) अणु
	    data = dummy_buf;
	पूर्ण अन्यथा अणु
	    skb_reserve(skb, 2);	/* so IP header lands on 4-byte bdry */
	    data = skb->data;
	पूर्ण
	mp->rx_bufs[i] = skb;
	cp->req_count = cpu_to_le16(RX_BUFLEN);
	cp->command = cpu_to_le16(INPUT_LAST + INTR_ALWAYS);
	cp->phy_addr = cpu_to_le32(virt_to_bus(data));
	cp->xfer_status = 0;
	++cp;
    पूर्ण
    mp->rx_bufs[i] = शून्य;
    cp->command = cpu_to_le16(DBDMA_STOP);
    mp->rx_fill = i;
    mp->rx_empty = 0;

    /* Put a branch back to the beginning of the receive command list */
    ++cp;
    cp->command = cpu_to_le16(DBDMA_NOP + BR_ALWAYS);
    cp->cmd_dep = cpu_to_le32(virt_to_bus(mp->rx_cmds));

    /* start rx dma */
    out_le32(&rd->control, (RUN|PAUSE|FLUSH|WAKE) << 16); /* clear run bit */
    out_le32(&rd->cmdptr, virt_to_bus(mp->rx_cmds));
    out_le32(&rd->control, (RUN << 16) | RUN);

    /* put a branch at the end of the tx command list */
    cp = mp->tx_cmds + NCMDS_TX * N_TX_RING;
    cp->command = cpu_to_le16(DBDMA_NOP + BR_ALWAYS);
    cp->cmd_dep = cpu_to_le32(virt_to_bus(mp->tx_cmds));

    /* reset tx dma */
    out_le32(&td->control, (RUN|PAUSE|FLUSH|WAKE) << 16);
    out_le32(&td->cmdptr, virt_to_bus(mp->tx_cmds));
    mp->tx_fill = 0;
    mp->tx_empty = 0;
    mp->tx_fullup = 0;
    mp->tx_active = 0;
    mp->tx_bad_runt = 0;

    /* turn it on! */
    out_8(&mb->maccc, mp->maccc);
    /* enable all पूर्णांकerrupts except receive पूर्णांकerrupts */
    out_8(&mb->imr, RCVINT);

    वापस 0;
पूर्ण

अटल पूर्णांक mace_बंद(काष्ठा net_device *dev)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    अस्थिर काष्ठा dbdma_regs __iomem *rd = mp->rx_dma;
    अस्थिर काष्ठा dbdma_regs __iomem *td = mp->tx_dma;

    /* disable rx and tx */
    out_8(&mb->maccc, 0);
    out_8(&mb->imr, 0xff);		/* disable all पूर्णांकrs */

    /* disable rx and tx dma */
    rd->control = cpu_to_le32((RUN|PAUSE|FLUSH|WAKE) << 16); /* clear run bit */
    td->control = cpu_to_le32((RUN|PAUSE|FLUSH|WAKE) << 16); /* clear run bit */

    mace_clean_rings(mp);

    वापस 0;
पूर्ण

अटल अंतरभूत व्योम mace_set_समयout(काष्ठा net_device *dev)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);

    अगर (mp->समयout_active)
	del_समयr(&mp->tx_समयout);
    mp->tx_समयout.expires = jअगरfies + TX_TIMEOUT;
    add_समयr(&mp->tx_समयout);
    mp->समयout_active = 1;
पूर्ण

अटल netdev_tx_t mace_xmit_start(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा dbdma_regs __iomem *td = mp->tx_dma;
    अस्थिर काष्ठा dbdma_cmd *cp, *np;
    अचिन्हित दीर्घ flags;
    पूर्णांक fill, next, len;

    /* see अगर there's a मुक्त slot in the tx ring */
    spin_lock_irqsave(&mp->lock, flags);
    fill = mp->tx_fill;
    next = fill + 1;
    अगर (next >= N_TX_RING)
	next = 0;
    अगर (next == mp->tx_empty) अणु
	netअगर_stop_queue(dev);
	mp->tx_fullup = 1;
	spin_unlock_irqrestore(&mp->lock, flags);
	वापस NETDEV_TX_BUSY;		/* can't take it at the moment */
    पूर्ण
    spin_unlock_irqrestore(&mp->lock, flags);

    /* partially fill in the dma command block */
    len = skb->len;
    अगर (len > ETH_FRAME_LEN) अणु
	prपूर्णांकk(KERN_DEBUG "mace: xmit frame too long (%d)\n", len);
	len = ETH_FRAME_LEN;
    पूर्ण
    mp->tx_bufs[fill] = skb;
    cp = mp->tx_cmds + NCMDS_TX * fill;
    cp->req_count = cpu_to_le16(len);
    cp->phy_addr = cpu_to_le32(virt_to_bus(skb->data));

    np = mp->tx_cmds + NCMDS_TX * next;
    out_le16(&np->command, DBDMA_STOP);

    /* poke the tx dma channel */
    spin_lock_irqsave(&mp->lock, flags);
    mp->tx_fill = next;
    अगर (!mp->tx_bad_runt && mp->tx_active < MAX_TX_ACTIVE) अणु
	out_le16(&cp->xfer_status, 0);
	out_le16(&cp->command, OUTPUT_LAST);
	out_le32(&td->control, ((RUN|WAKE) << 16) + (RUN|WAKE));
	++mp->tx_active;
	mace_set_समयout(dev);
    पूर्ण
    अगर (++next >= N_TX_RING)
	next = 0;
    अगर (next == mp->tx_empty)
	netअगर_stop_queue(dev);
    spin_unlock_irqrestore(&mp->lock, flags);

    वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम mace_set_multicast(काष्ठा net_device *dev)
अणु
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    पूर्णांक i;
    u32 crc;
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&mp->lock, flags);
    mp->maccc &= ~PROM;
    अगर (dev->flags & IFF_PROMISC) अणु
	mp->maccc |= PROM;
    पूर्ण अन्यथा अणु
	अचिन्हित अक्षर multicast_filter[8];
	काष्ठा netdev_hw_addr *ha;

	अगर (dev->flags & IFF_ALLMULTI) अणु
	    क्रम (i = 0; i < 8; i++)
		multicast_filter[i] = 0xff;
	पूर्ण अन्यथा अणु
	    क्रम (i = 0; i < 8; i++)
		multicast_filter[i] = 0;
	    netdev_क्रम_each_mc_addr(ha, dev) अणु
	        crc = ether_crc_le(6, ha->addr);
		i = crc >> 26;	/* bit number in multicast_filter */
		multicast_filter[i >> 3] |= 1 << (i & 7);
	    पूर्ण
	पूर्ण
#अगर 0
	prपूर्णांकk("Multicast filter :");
	क्रम (i = 0; i < 8; i++)
	    prपूर्णांकk("%02x ", multicast_filter[i]);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	अगर (mp->chipid == BROKEN_ADDRCHG_REV)
	    out_8(&mb->iac, LOGADDR);
	अन्यथा अणु
	    out_8(&mb->iac, ADDRCHG | LOGADDR);
	    जबतक ((in_8(&mb->iac) & ADDRCHG) != 0)
		;
	पूर्ण
	क्रम (i = 0; i < 8; ++i)
	    out_8(&mb->ladrf, multicast_filter[i]);
	अगर (mp->chipid != BROKEN_ADDRCHG_REV)
	    out_8(&mb->iac, 0);
    पूर्ण
    /* reset maccc */
    out_8(&mb->maccc, mp->maccc);
    spin_unlock_irqrestore(&mp->lock, flags);
पूर्ण

अटल व्योम mace_handle_misc_पूर्णांकrs(काष्ठा mace_data *mp, पूर्णांक पूर्णांकr, काष्ठा net_device *dev)
अणु
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    अटल पूर्णांक mace_babbles, mace_jabbers;

    अगर (पूर्णांकr & MPCO)
	dev->stats.rx_missed_errors += 256;
    dev->stats.rx_missed_errors += in_8(&mb->mpc);   /* पढ़ोing clears it */
    अगर (पूर्णांकr & RNTPCO)
	dev->stats.rx_length_errors += 256;
    dev->stats.rx_length_errors += in_8(&mb->rntpc); /* पढ़ोing clears it */
    अगर (पूर्णांकr & CERR)
	++dev->stats.tx_heartbeat_errors;
    अगर (पूर्णांकr & BABBLE)
	अगर (mace_babbles++ < 4)
	    prपूर्णांकk(KERN_DEBUG "mace: babbling transmitter\n");
    अगर (पूर्णांकr & JABBER)
	अगर (mace_jabbers++ < 4)
	    prपूर्णांकk(KERN_DEBUG "mace: jabbering transceiver\n");
पूर्ण

अटल irqवापस_t mace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    अस्थिर काष्ठा dbdma_regs __iomem *td = mp->tx_dma;
    अस्थिर काष्ठा dbdma_cmd *cp;
    पूर्णांक पूर्णांकr, fs, i, stat, x;
    पूर्णांक xcount, dstat;
    अचिन्हित दीर्घ flags;
    /* अटल पूर्णांक mace_last_fs, mace_last_xcount; */

    spin_lock_irqsave(&mp->lock, flags);
    पूर्णांकr = in_8(&mb->ir);		/* पढ़ो पूर्णांकerrupt रेजिस्टर */
    in_8(&mb->xmtrc);			/* get retries */
    mace_handle_misc_पूर्णांकrs(mp, पूर्णांकr, dev);

    i = mp->tx_empty;
    जबतक (in_8(&mb->pr) & XMTSV) अणु
	del_समयr(&mp->tx_समयout);
	mp->समयout_active = 0;
	/*
	 * Clear any पूर्णांकerrupt indication associated with this status
	 * word.  This appears to unlatch any error indication from
	 * the DMA controller.
	 */
	पूर्णांकr = in_8(&mb->ir);
	अगर (पूर्णांकr != 0)
	    mace_handle_misc_पूर्णांकrs(mp, पूर्णांकr, dev);
	अगर (mp->tx_bad_runt) अणु
	    fs = in_8(&mb->xmtfs);
	    mp->tx_bad_runt = 0;
	    out_8(&mb->xmtfc, AUTO_PAD_XMIT);
	    जारी;
	पूर्ण
	dstat = le32_to_cpu(td->status);
	/* stop DMA controller */
	out_le32(&td->control, RUN << 16);
	/*
	 * xcount is the number of complete frames which have been
	 * written to the fअगरo but क्रम which status has not been पढ़ो.
	 */
	xcount = (in_8(&mb->fअगरofc) >> XMTFC_SH) & XMTFC_MASK;
	अगर (xcount == 0 || (dstat & DEAD)) अणु
	    /*
	     * If a packet was पातed beक्रमe the DMA controller has
	     * finished transferring it, it seems that there are 2 bytes
	     * which are stuck in some buffer somewhere.  These will get
	     * transmitted as soon as we पढ़ो the frame status (which
	     * reenables the transmit data transfer request).  Turning
	     * off the DMA controller and/or resetting the MACE करोesn't
	     * help.  So we disable स्वतः-padding and FCS transmission
	     * so the two bytes will only be a runt packet which should
	     * be ignored by other stations.
	     */
	    out_8(&mb->xmtfc, DXMTFCS);
	पूर्ण
	fs = in_8(&mb->xmtfs);
	अगर ((fs & XMTSV) == 0) अणु
	    prपूर्णांकk(KERN_ERR "mace: xmtfs not valid! (fs=%x xc=%d ds=%x)\n",
		   fs, xcount, dstat);
	    mace_reset(dev);
		/*
		 * XXX mace likes to hang the machine after a xmtfs error.
		 * This is hard to reproduce, resetting *may* help
		 */
	पूर्ण
	cp = mp->tx_cmds + NCMDS_TX * i;
	stat = le16_to_cpu(cp->xfer_status);
	अगर ((fs & (UFLO|LCOL|LCAR|RTRY)) || (dstat & DEAD) || xcount == 0) अणु
	    /*
	     * Check whether there were in fact 2 bytes written to
	     * the transmit FIFO.
	     */
	    udelay(1);
	    x = (in_8(&mb->fअगरofc) >> XMTFC_SH) & XMTFC_MASK;
	    अगर (x != 0) अणु
		/* there were two bytes with an end-of-packet indication */
		mp->tx_bad_runt = 1;
		mace_set_समयout(dev);
	    पूर्ण अन्यथा अणु
		/*
		 * Either there weren't the two bytes buffered up, or they
		 * didn't have an end-of-packet indication.
		 * We flush the transmit FIFO just in हाल (by setting the
		 * XMTFWU bit with the transmitter disabled).
		 */
		out_8(&mb->maccc, in_8(&mb->maccc) & ~ENXMT);
		out_8(&mb->fअगरocc, in_8(&mb->fअगरocc) | XMTFWU);
		udelay(1);
		out_8(&mb->maccc, in_8(&mb->maccc) | ENXMT);
		out_8(&mb->xmtfc, AUTO_PAD_XMIT);
	    पूर्ण
	पूर्ण
	/* dma should have finished */
	अगर (i == mp->tx_fill) अणु
	    prपूर्णांकk(KERN_DEBUG "mace: tx ring ran out? (fs=%x xc=%d ds=%x)\n",
		   fs, xcount, dstat);
	    जारी;
	पूर्ण
	/* Update stats */
	अगर (fs & (UFLO|LCOL|LCAR|RTRY)) अणु
	    ++dev->stats.tx_errors;
	    अगर (fs & LCAR)
		++dev->stats.tx_carrier_errors;
	    अगर (fs & (UFLO|LCOL|RTRY))
		++dev->stats.tx_पातed_errors;
	पूर्ण अन्यथा अणु
	    dev->stats.tx_bytes += mp->tx_bufs[i]->len;
	    ++dev->stats.tx_packets;
	पूर्ण
	dev_consume_skb_irq(mp->tx_bufs[i]);
	--mp->tx_active;
	अगर (++i >= N_TX_RING)
	    i = 0;
#अगर 0
	mace_last_fs = fs;
	mace_last_xcount = xcount;
#पूर्ण_अगर
    पूर्ण

    अगर (i != mp->tx_empty) अणु
	mp->tx_fullup = 0;
	netअगर_wake_queue(dev);
    पूर्ण
    mp->tx_empty = i;
    i += mp->tx_active;
    अगर (i >= N_TX_RING)
	i -= N_TX_RING;
    अगर (!mp->tx_bad_runt && i != mp->tx_fill && mp->tx_active < MAX_TX_ACTIVE) अणु
	करो अणु
	    /* set up the next one */
	    cp = mp->tx_cmds + NCMDS_TX * i;
	    out_le16(&cp->xfer_status, 0);
	    out_le16(&cp->command, OUTPUT_LAST);
	    ++mp->tx_active;
	    अगर (++i >= N_TX_RING)
		i = 0;
	पूर्ण जबतक (i != mp->tx_fill && mp->tx_active < MAX_TX_ACTIVE);
	out_le32(&td->control, ((RUN|WAKE) << 16) + (RUN|WAKE));
	mace_set_समयout(dev);
    पूर्ण
    spin_unlock_irqrestore(&mp->lock, flags);
    वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mace_tx_समयout(काष्ठा समयr_list *t)
अणु
    काष्ठा mace_data *mp = from_समयr(mp, t, tx_समयout);
    काष्ठा net_device *dev = macio_get_drvdata(mp->mdev);
    अस्थिर काष्ठा mace __iomem *mb = mp->mace;
    अस्थिर काष्ठा dbdma_regs __iomem *td = mp->tx_dma;
    अस्थिर काष्ठा dbdma_regs __iomem *rd = mp->rx_dma;
    अस्थिर काष्ठा dbdma_cmd *cp;
    अचिन्हित दीर्घ flags;
    पूर्णांक i;

    spin_lock_irqsave(&mp->lock, flags);
    mp->समयout_active = 0;
    अगर (mp->tx_active == 0 && !mp->tx_bad_runt)
	जाओ out;

    /* update various counters */
    mace_handle_misc_पूर्णांकrs(mp, in_8(&mb->ir), dev);

    cp = mp->tx_cmds + NCMDS_TX * mp->tx_empty;

    /* turn off both tx and rx and reset the chip */
    out_8(&mb->maccc, 0);
    prपूर्णांकk(KERN_ERR "mace: transmit timeout - resetting\n");
    dbdma_reset(td);
    mace_reset(dev);

    /* restart rx dma */
    cp = bus_to_virt(le32_to_cpu(rd->cmdptr));
    dbdma_reset(rd);
    out_le16(&cp->xfer_status, 0);
    out_le32(&rd->cmdptr, virt_to_bus(cp));
    out_le32(&rd->control, (RUN << 16) | RUN);

    /* fix up the transmit side */
    i = mp->tx_empty;
    mp->tx_active = 0;
    ++dev->stats.tx_errors;
    अगर (mp->tx_bad_runt) अणु
	mp->tx_bad_runt = 0;
    पूर्ण अन्यथा अगर (i != mp->tx_fill) अणु
	dev_kमुक्त_skb(mp->tx_bufs[i]);
	अगर (++i >= N_TX_RING)
	    i = 0;
	mp->tx_empty = i;
    पूर्ण
    mp->tx_fullup = 0;
    netअगर_wake_queue(dev);
    अगर (i != mp->tx_fill) अणु
	cp = mp->tx_cmds + NCMDS_TX * i;
	out_le16(&cp->xfer_status, 0);
	out_le16(&cp->command, OUTPUT_LAST);
	out_le32(&td->cmdptr, virt_to_bus(cp));
	out_le32(&td->control, (RUN << 16) | RUN);
	++mp->tx_active;
	mace_set_समयout(dev);
    पूर्ण

    /* turn it back on */
    out_8(&mb->imr, RCVINT);
    out_8(&mb->maccc, mp->maccc);

out:
    spin_unlock_irqrestore(&mp->lock, flags);
पूर्ण

अटल irqवापस_t mace_txdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mace_rxdma_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
    काष्ठा mace_data *mp = netdev_priv(dev);
    अस्थिर काष्ठा dbdma_regs __iomem *rd = mp->rx_dma;
    अस्थिर काष्ठा dbdma_cmd *cp, *np;
    पूर्णांक i, nb, stat, next;
    काष्ठा sk_buff *skb;
    अचिन्हित frame_status;
    अटल पूर्णांक mace_lost_status;
    अचिन्हित अक्षर *data;
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&mp->lock, flags);
    क्रम (i = mp->rx_empty; i != mp->rx_fill; ) अणु
	cp = mp->rx_cmds + i;
	stat = le16_to_cpu(cp->xfer_status);
	अगर ((stat & ACTIVE) == 0) अणु
	    next = i + 1;
	    अगर (next >= N_RX_RING)
		next = 0;
	    np = mp->rx_cmds + next;
	    अगर (next != mp->rx_fill &&
		(le16_to_cpu(np->xfer_status) & ACTIVE) != 0) अणु
		prपूर्णांकk(KERN_DEBUG "mace: lost a status word\n");
		++mace_lost_status;
	    पूर्ण अन्यथा
		अवरोध;
	पूर्ण
	nb = le16_to_cpu(cp->req_count) - le16_to_cpu(cp->res_count);
	out_le16(&cp->command, DBDMA_STOP);
	/* got a packet, have a look at it */
	skb = mp->rx_bufs[i];
	अगर (!skb) अणु
	    ++dev->stats.rx_dropped;
	पूर्ण अन्यथा अगर (nb > 8) अणु
	    data = skb->data;
	    frame_status = (data[nb-3] << 8) + data[nb-4];
	    अगर (frame_status & (RS_OFLO|RS_CLSN|RS_FRAMERR|RS_FCSERR)) अणु
		++dev->stats.rx_errors;
		अगर (frame_status & RS_OFLO)
		    ++dev->stats.rx_over_errors;
		अगर (frame_status & RS_FRAMERR)
		    ++dev->stats.rx_frame_errors;
		अगर (frame_status & RS_FCSERR)
		    ++dev->stats.rx_crc_errors;
	    पूर्ण अन्यथा अणु
		/* Mace feature AUTO_STRIP_RCV is on by शेष, dropping the
		 * FCS on frames with 802.3 headers. This means that Ethernet
		 * frames have 8 extra octets at the end, जबतक 802.3 frames
		 * have only 4. We need to correctly account क्रम this. */
		अगर (*(अचिन्हित लघु *)(data+12) < 1536) /* 802.3 header */
		    nb -= 4;
		अन्यथा	/* Ethernet header; mace includes FCS */
		    nb -= 8;
		skb_put(skb, nb);
		skb->protocol = eth_type_trans(skb, dev);
		dev->stats.rx_bytes += skb->len;
		netअगर_rx(skb);
		mp->rx_bufs[i] = शून्य;
		++dev->stats.rx_packets;
	    पूर्ण
	पूर्ण अन्यथा अणु
	    ++dev->stats.rx_errors;
	    ++dev->stats.rx_length_errors;
	पूर्ण

	/* advance to next */
	अगर (++i >= N_RX_RING)
	    i = 0;
    पूर्ण
    mp->rx_empty = i;

    i = mp->rx_fill;
    क्रम (;;) अणु
	next = i + 1;
	अगर (next >= N_RX_RING)
	    next = 0;
	अगर (next == mp->rx_empty)
	    अवरोध;
	cp = mp->rx_cmds + i;
	skb = mp->rx_bufs[i];
	अगर (!skb) अणु
	    skb = netdev_alloc_skb(dev, RX_BUFLEN + 2);
	    अगर (skb) अणु
		skb_reserve(skb, 2);
		mp->rx_bufs[i] = skb;
	    पूर्ण
	पूर्ण
	cp->req_count = cpu_to_le16(RX_BUFLEN);
	data = skb? skb->data: dummy_buf;
	cp->phy_addr = cpu_to_le32(virt_to_bus(data));
	out_le16(&cp->xfer_status, 0);
	out_le16(&cp->command, INPUT_LAST + INTR_ALWAYS);
#अगर 0
	अगर ((le32_to_cpu(rd->status) & ACTIVE) != 0) अणु
	    out_le32(&rd->control, (PAUSE << 16) | PAUSE);
	    जबतक ((in_le32(&rd->status) & ACTIVE) != 0)
		;
	पूर्ण
#पूर्ण_अगर
	i = next;
    पूर्ण
    अगर (i != mp->rx_fill) अणु
	out_le32(&rd->control, ((RUN|WAKE) << 16) | (RUN|WAKE));
	mp->rx_fill = i;
    पूर्ण
    spin_unlock_irqrestore(&mp->lock, flags);
    वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id mace_match[] =
अणु
	अणु
	.name 		= "mace",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE (of, mace_match);

अटल काष्ठा macio_driver mace_driver =
अणु
	.driver = अणु
		.name 		= "mace",
		.owner		= THIS_MODULE,
		.of_match_table	= mace_match,
	पूर्ण,
	.probe		= mace_probe,
	.हटाओ		= mace_हटाओ,
पूर्ण;


अटल पूर्णांक __init mace_init(व्योम)
अणु
	वापस macio_रेजिस्टर_driver(&mace_driver);
पूर्ण

अटल व्योम __निकास mace_cleanup(व्योम)
अणु
	macio_unरेजिस्टर_driver(&mace_driver);

	kमुक्त(dummy_buf);
	dummy_buf = शून्य;
पूर्ण

MODULE_AUTHOR("Paul Mackerras");
MODULE_DESCRIPTION("PowerMac MACE driver.");
module_param(port_aaui, पूर्णांक, 0);
MODULE_PARM_DESC(port_aaui, "MACE uses AAUI port (0-1)");
MODULE_LICENSE("GPL");

module_init(mace_init);
module_निकास(mace_cleanup);
