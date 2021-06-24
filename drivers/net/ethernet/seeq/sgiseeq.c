<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sgiseeq.c: Seeq8003 ethernet driver क्रम SGI machines.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */

#अघोषित DEBUG

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>
#समावेश <यंत्र/sgi/seeq.h>

#समावेश "sgiseeq.h"

अटल अक्षर *sgiseeqstr = "SGI Seeq8003";

/*
 * If you want speed, you करो something silly, it always has worked क्रम me.  So,
 * with that in mind, I've decided to make this driver look completely like a
 * stupid Lance from a driver architecture perspective.  Only dअगरference is that
 * here our "ring buffer" looks and acts like a real Lance one करोes but is
 * laid out like how the HPC DMA and the Seeq want it to.  You'd be surprised
 * how a stupid idea like this can pay off in perक्रमmance, not to mention
 * making this driver 2,000 बार easier to ग_लिखो. ;-)
 */

/* Tune these अगर we tend to run out often etc. */
#घोषणा SEEQ_RX_BUFFERS  16
#घोषणा SEEQ_TX_BUFFERS  16

#घोषणा PKT_BUF_SZ       1584

#घोषणा NEXT_RX(i)  (((i) + 1) & (SEEQ_RX_BUFFERS - 1))
#घोषणा NEXT_TX(i)  (((i) + 1) & (SEEQ_TX_BUFFERS - 1))
#घोषणा PREV_RX(i)  (((i) - 1) & (SEEQ_RX_BUFFERS - 1))
#घोषणा PREV_TX(i)  (((i) - 1) & (SEEQ_TX_BUFFERS - 1))

#घोषणा TX_BUFFS_AVAIL(sp) ((sp->tx_old <= sp->tx_new) ? \
			    sp->tx_old + (SEEQ_TX_BUFFERS - 1) - sp->tx_new : \
			    sp->tx_old - sp->tx_new - 1)

#घोषणा VIRT_TO_DMA(sp, v) ((sp)->srings_dma +                                 \
				  (dma_addr_t)((अचिन्हित दीर्घ)(v) -            \
					       (अचिन्हित दीर्घ)((sp)->rx_desc)))

/* Copy frames लघुer than rx_copyअवरोध, otherwise pass on up in
 * a full sized sk_buff.  Value of 100 stolen from tulip.c (!alpha).
 */
अटल पूर्णांक rx_copyअवरोध = 100;

#घोषणा PAD_SIZE    (128 - माप(काष्ठा hpc_dma_desc) - माप(व्योम *))

काष्ठा sgiseeq_rx_desc अणु
	अस्थिर काष्ठा hpc_dma_desc rdma;
	u8 padding[PAD_SIZE];
	काष्ठा sk_buff *skb;
पूर्ण;

काष्ठा sgiseeq_tx_desc अणु
	अस्थिर काष्ठा hpc_dma_desc tdma;
	u8 padding[PAD_SIZE];
	काष्ठा sk_buff *skb;
पूर्ण;

/*
 * Warning: This काष्ठाure is laid out in a certain way because HPC dma
 *          descriptors must be 8-byte aligned.  So करोn't touch this without
 *          some care.
 */
काष्ठा sgiseeq_init_block अणु /* Note the name ;-) */
	काष्ठा sgiseeq_rx_desc rxvector[SEEQ_RX_BUFFERS];
	काष्ठा sgiseeq_tx_desc txvector[SEEQ_TX_BUFFERS];
पूर्ण;

काष्ठा sgiseeq_निजी अणु
	काष्ठा sgiseeq_init_block *srings;
	dma_addr_t srings_dma;

	/* Ptrs to the descriptors in uncached space. */
	काष्ठा sgiseeq_rx_desc *rx_desc;
	काष्ठा sgiseeq_tx_desc *tx_desc;

	अक्षर *name;
	काष्ठा hpc3_ethregs *hregs;
	काष्ठा sgiseeq_regs *sregs;

	/* Ring entry counters. */
	अचिन्हित पूर्णांक rx_new, tx_new;
	अचिन्हित पूर्णांक rx_old, tx_old;

	पूर्णांक is_edlc;
	अचिन्हित अक्षर control;
	अचिन्हित अक्षर mode;

	spinlock_t tx_lock;
पूर्ण;

अटल अंतरभूत व्योम dma_sync_desc_cpu(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);

	dma_sync_single_क्रम_cpu(dev->dev.parent, VIRT_TO_DMA(sp, addr),
			माप(काष्ठा sgiseeq_rx_desc), DMA_BIसूचीECTIONAL);
पूर्ण

अटल अंतरभूत व्योम dma_sync_desc_dev(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);

	dma_sync_single_क्रम_device(dev->dev.parent, VIRT_TO_DMA(sp, addr),
			माप(काष्ठा sgiseeq_rx_desc), DMA_BIसूचीECTIONAL);
पूर्ण

अटल अंतरभूत व्योम hpc3_eth_reset(काष्ठा hpc3_ethregs *hregs)
अणु
	hregs->reset = HPC3_ERST_CRESET | HPC3_ERST_CLRIRQ;
	udelay(20);
	hregs->reset = 0;
पूर्ण

अटल अंतरभूत व्योम reset_hpc3_and_seeq(काष्ठा hpc3_ethregs *hregs,
				       काष्ठा sgiseeq_regs *sregs)
अणु
	hregs->rx_ctrl = hregs->tx_ctrl = 0;
	hpc3_eth_reset(hregs);
पूर्ण

#घोषणा RSTAT_GO_BITS (SEEQ_RCMD_IGOOD | SEEQ_RCMD_Iखातापूर्ण | SEEQ_RCMD_ISHORT | \
		       SEEQ_RCMD_IDRIB | SEEQ_RCMD_ICRC)

अटल अंतरभूत व्योम seeq_go(काष्ठा sgiseeq_निजी *sp,
			   काष्ठा hpc3_ethregs *hregs,
			   काष्ठा sgiseeq_regs *sregs)
अणु
	sregs->rstat = sp->mode | RSTAT_GO_BITS;
	hregs->rx_ctrl = HPC3_ERXCTRL_ACTIVE;
पूर्ण

अटल अंतरभूत व्योम __sgiseeq_set_mac_address(काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	काष्ठा sgiseeq_regs *sregs = sp->sregs;
	पूर्णांक i;

	sregs->tstat = SEEQ_TCMD_RB0;
	क्रम (i = 0; i < 6; i++)
		sregs->rw.eth_addr[i] = dev->dev_addr[i];
पूर्ण

अटल पूर्णांक sgiseeq_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	काष्ठा sockaddr *sa = addr;

	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);

	spin_lock_irq(&sp->tx_lock);
	__sgiseeq_set_mac_address(dev);
	spin_unlock_irq(&sp->tx_lock);

	वापस 0;
पूर्ण

#घोषणा TCNTINFO_INIT (HPCDMA_EOX | HPCDMA_ETXD)
#घोषणा RCNTCFG_INIT  (HPCDMA_OWN | HPCDMA_EORP | HPCDMA_XIE)
#घोषणा RCNTINFO_INIT (RCNTCFG_INIT | (PKT_BUF_SZ & HPCDMA_BCNT))

अटल पूर्णांक seeq_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	पूर्णांक i;

	netअगर_stop_queue(dev);
	sp->rx_new = sp->tx_new = 0;
	sp->rx_old = sp->tx_old = 0;

	__sgiseeq_set_mac_address(dev);

	/* Setup tx ring. */
	क्रम(i = 0; i < SEEQ_TX_BUFFERS; i++) अणु
		sp->tx_desc[i].tdma.cntinfo = TCNTINFO_INIT;
		dma_sync_desc_dev(dev, &sp->tx_desc[i]);
	पूर्ण

	/* And now the rx ring. */
	क्रम (i = 0; i < SEEQ_RX_BUFFERS; i++) अणु
		अगर (!sp->rx_desc[i].skb) अणु
			dma_addr_t dma_addr;
			काष्ठा sk_buff *skb = netdev_alloc_skb(dev, PKT_BUF_SZ);

			अगर (skb == शून्य)
				वापस -ENOMEM;
			skb_reserve(skb, 2);
			dma_addr = dma_map_single(dev->dev.parent,
						  skb->data - 2,
						  PKT_BUF_SZ, DMA_FROM_DEVICE);
			sp->rx_desc[i].skb = skb;
			sp->rx_desc[i].rdma.pbuf = dma_addr;
		पूर्ण
		sp->rx_desc[i].rdma.cntinfo = RCNTINFO_INIT;
		dma_sync_desc_dev(dev, &sp->rx_desc[i]);
	पूर्ण
	sp->rx_desc[i - 1].rdma.cntinfo |= HPCDMA_EOR;
	dma_sync_desc_dev(dev, &sp->rx_desc[i - 1]);
	वापस 0;
पूर्ण

अटल व्योम seeq_purge_ring(काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	पूर्णांक i;

	/* clear tx ring. */
	क्रम (i = 0; i < SEEQ_TX_BUFFERS; i++) अणु
		अगर (sp->tx_desc[i].skb) अणु
			dev_kमुक्त_skb(sp->tx_desc[i].skb);
			sp->tx_desc[i].skb = शून्य;
		पूर्ण
	पूर्ण

	/* And now the rx ring. */
	क्रम (i = 0; i < SEEQ_RX_BUFFERS; i++) अणु
		अगर (sp->rx_desc[i].skb) अणु
			dev_kमुक्त_skb(sp->rx_desc[i].skb);
			sp->rx_desc[i].skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित DEBUG
अटल काष्ठा sgiseeq_निजी *gpriv;
अटल काष्ठा net_device *gdev;

अटल व्योम sgiseeq_dump_rings(व्योम)
अणु
	अटल पूर्णांक once;
	काष्ठा sgiseeq_rx_desc *r = gpriv->rx_desc;
	काष्ठा sgiseeq_tx_desc *t = gpriv->tx_desc;
	काष्ठा hpc3_ethregs *hregs = gpriv->hregs;
	पूर्णांक i;

	अगर (once)
		वापस;
	once++;
	prपूर्णांकk("RING DUMP:\n");
	क्रम (i = 0; i < SEEQ_RX_BUFFERS; i++) अणु
		prपूर्णांकk("RX [%d]: @(%p) [%08x,%08x,%08x] ",
		       i, (&r[i]), r[i].rdma.pbuf, r[i].rdma.cntinfo,
		       r[i].rdma.pnext);
		i += 1;
		prपूर्णांकk("-- [%d]: @(%p) [%08x,%08x,%08x]\n",
		       i, (&r[i]), r[i].rdma.pbuf, r[i].rdma.cntinfo,
		       r[i].rdma.pnext);
	पूर्ण
	क्रम (i = 0; i < SEEQ_TX_BUFFERS; i++) अणु
		prपूर्णांकk("TX [%d]: @(%p) [%08x,%08x,%08x] ",
		       i, (&t[i]), t[i].tdma.pbuf, t[i].tdma.cntinfo,
		       t[i].tdma.pnext);
		i += 1;
		prपूर्णांकk("-- [%d]: @(%p) [%08x,%08x,%08x]\n",
		       i, (&t[i]), t[i].tdma.pbuf, t[i].tdma.cntinfo,
		       t[i].tdma.pnext);
	पूर्ण
	prपूर्णांकk("INFO: [rx_new = %d rx_old=%d] [tx_new = %d tx_old = %d]\n",
	       gpriv->rx_new, gpriv->rx_old, gpriv->tx_new, gpriv->tx_old);
	prपूर्णांकk("RREGS: rx_cbptr[%08x] rx_ndptr[%08x] rx_ctrl[%08x]\n",
	       hregs->rx_cbptr, hregs->rx_ndptr, hregs->rx_ctrl);
	prपूर्णांकk("TREGS: tx_cbptr[%08x] tx_ndptr[%08x] tx_ctrl[%08x]\n",
	       hregs->tx_cbptr, hregs->tx_ndptr, hregs->tx_ctrl);
पूर्ण
#पूर्ण_अगर

#घोषणा TSTAT_INIT_SEEQ (SEEQ_TCMD_IPT|SEEQ_TCMD_I16|SEEQ_TCMD_IC|SEEQ_TCMD_IUF)
#घोषणा TSTAT_INIT_EDLC ((TSTAT_INIT_SEEQ) | SEEQ_TCMD_RB2)

अटल पूर्णांक init_seeq(काष्ठा net_device *dev, काष्ठा sgiseeq_निजी *sp,
		     काष्ठा sgiseeq_regs *sregs)
अणु
	काष्ठा hpc3_ethregs *hregs = sp->hregs;
	पूर्णांक err;

	reset_hpc3_and_seeq(hregs, sregs);
	err = seeq_init_ring(dev);
	अगर (err)
		वापस err;

	/* Setup to field the proper पूर्णांकerrupt types. */
	अगर (sp->is_edlc) अणु
		sregs->tstat = TSTAT_INIT_EDLC;
		sregs->rw.wregs.control = sp->control;
		sregs->rw.wregs.frame_gap = 0;
	पूर्ण अन्यथा अणु
		sregs->tstat = TSTAT_INIT_SEEQ;
	पूर्ण

	hregs->rx_ndptr = VIRT_TO_DMA(sp, sp->rx_desc);
	hregs->tx_ndptr = VIRT_TO_DMA(sp, sp->tx_desc);

	seeq_go(sp, hregs, sregs);
	वापस 0;
पूर्ण

अटल व्योम record_rx_errors(काष्ठा net_device *dev, अचिन्हित अक्षर status)
अणु
	अगर (status & SEEQ_RSTAT_OVERF ||
	    status & SEEQ_RSTAT_SFRAME)
		dev->stats.rx_over_errors++;
	अगर (status & SEEQ_RSTAT_CERROR)
		dev->stats.rx_crc_errors++;
	अगर (status & SEEQ_RSTAT_DERROR)
		dev->stats.rx_frame_errors++;
	अगर (status & SEEQ_RSTAT_Rखातापूर्ण)
		dev->stats.rx_errors++;
पूर्ण

अटल अंतरभूत व्योम rx_maybe_restart(काष्ठा sgiseeq_निजी *sp,
				    काष्ठा hpc3_ethregs *hregs,
				    काष्ठा sgiseeq_regs *sregs)
अणु
	अगर (!(hregs->rx_ctrl & HPC3_ERXCTRL_ACTIVE)) अणु
		hregs->rx_ndptr = VIRT_TO_DMA(sp, sp->rx_desc + sp->rx_new);
		seeq_go(sp, hregs, sregs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sgiseeq_rx(काष्ठा net_device *dev, काष्ठा sgiseeq_निजी *sp,
			      काष्ठा hpc3_ethregs *hregs,
			      काष्ठा sgiseeq_regs *sregs)
अणु
	काष्ठा sgiseeq_rx_desc *rd;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा sk_buff *newskb;
	अचिन्हित अक्षर pkt_status;
	पूर्णांक len = 0;
	अचिन्हित पूर्णांक orig_end = PREV_RX(sp->rx_new);

	/* Service every received packet. */
	rd = &sp->rx_desc[sp->rx_new];
	dma_sync_desc_cpu(dev, rd);
	जबतक (!(rd->rdma.cntinfo & HPCDMA_OWN)) अणु
		len = PKT_BUF_SZ - (rd->rdma.cntinfo & HPCDMA_BCNT) - 3;
		dma_unmap_single(dev->dev.parent, rd->rdma.pbuf,
				 PKT_BUF_SZ, DMA_FROM_DEVICE);
		pkt_status = rd->skb->data[len];
		अगर (pkt_status & SEEQ_RSTAT_FIG) अणु
			/* Packet is OK. */
			/* We करोn't want to receive our own packets */
			अगर (!ether_addr_equal(rd->skb->data + 6, dev->dev_addr)) अणु
				अगर (len > rx_copyअवरोध) अणु
					skb = rd->skb;
					newskb = netdev_alloc_skb(dev, PKT_BUF_SZ);
					अगर (!newskb) अणु
						newskb = skb;
						skb = शून्य;
						जाओ memory_squeeze;
					पूर्ण
					skb_reserve(newskb, 2);
				पूर्ण अन्यथा अणु
					skb = netdev_alloc_skb_ip_align(dev, len);
					अगर (skb)
						skb_copy_to_linear_data(skb, rd->skb->data, len);

					newskb = rd->skb;
				पूर्ण
memory_squeeze:
				अगर (skb) अणु
					skb_put(skb, len);
					skb->protocol = eth_type_trans(skb, dev);
					netअगर_rx(skb);
					dev->stats.rx_packets++;
					dev->stats.rx_bytes += len;
				पूर्ण अन्यथा अणु
					dev->stats.rx_dropped++;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Silently drop my own packets */
				newskb = rd->skb;
			पूर्ण
		पूर्ण अन्यथा अणु
			record_rx_errors(dev, pkt_status);
			newskb = rd->skb;
		पूर्ण
		rd->skb = newskb;
		rd->rdma.pbuf = dma_map_single(dev->dev.parent,
					       newskb->data - 2,
					       PKT_BUF_SZ, DMA_FROM_DEVICE);

		/* Return the entry to the ring pool. */
		rd->rdma.cntinfo = RCNTINFO_INIT;
		sp->rx_new = NEXT_RX(sp->rx_new);
		dma_sync_desc_dev(dev, rd);
		rd = &sp->rx_desc[sp->rx_new];
		dma_sync_desc_cpu(dev, rd);
	पूर्ण
	dma_sync_desc_dev(dev, rd);

	dma_sync_desc_cpu(dev, &sp->rx_desc[orig_end]);
	sp->rx_desc[orig_end].rdma.cntinfo &= ~(HPCDMA_EOR);
	dma_sync_desc_dev(dev, &sp->rx_desc[orig_end]);
	dma_sync_desc_cpu(dev, &sp->rx_desc[PREV_RX(sp->rx_new)]);
	sp->rx_desc[PREV_RX(sp->rx_new)].rdma.cntinfo |= HPCDMA_EOR;
	dma_sync_desc_dev(dev, &sp->rx_desc[PREV_RX(sp->rx_new)]);
	rx_maybe_restart(sp, hregs, sregs);
पूर्ण

अटल अंतरभूत व्योम tx_maybe_reset_collisions(काष्ठा sgiseeq_निजी *sp,
					     काष्ठा sgiseeq_regs *sregs)
अणु
	अगर (sp->is_edlc) अणु
		sregs->rw.wregs.control = sp->control & ~(SEEQ_CTRL_XCNT);
		sregs->rw.wregs.control = sp->control;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम kick_tx(काष्ठा net_device *dev,
			   काष्ठा sgiseeq_निजी *sp,
			   काष्ठा hpc3_ethregs *hregs)
अणु
	काष्ठा sgiseeq_tx_desc *td;
	पूर्णांक i = sp->tx_old;

	/* If the HPC aपूर्णांक करोin nothin, and there are more packets
	 * with ETXD cleared and XIU set we must make very certain
	 * that we restart the HPC अन्यथा we risk locking up the
	 * adapter.  The following code is only safe अगरf the HPCDMA
	 * is not active!
	 */
	td = &sp->tx_desc[i];
	dma_sync_desc_cpu(dev, td);
	जबतक ((td->tdma.cntinfo & (HPCDMA_XIU | HPCDMA_ETXD)) ==
	      (HPCDMA_XIU | HPCDMA_ETXD)) अणु
		i = NEXT_TX(i);
		td = &sp->tx_desc[i];
		dma_sync_desc_cpu(dev, td);
	पूर्ण
	अगर (td->tdma.cntinfo & HPCDMA_XIU) अणु
		dma_sync_desc_dev(dev, td);
		hregs->tx_ndptr = VIRT_TO_DMA(sp, td);
		hregs->tx_ctrl = HPC3_ETXCTRL_ACTIVE;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sgiseeq_tx(काष्ठा net_device *dev, काष्ठा sgiseeq_निजी *sp,
			      काष्ठा hpc3_ethregs *hregs,
			      काष्ठा sgiseeq_regs *sregs)
अणु
	काष्ठा sgiseeq_tx_desc *td;
	अचिन्हित दीर्घ status = hregs->tx_ctrl;
	पूर्णांक j;

	tx_maybe_reset_collisions(sp, sregs);

	अगर (!(status & (HPC3_ETXCTRL_ACTIVE | SEEQ_TSTAT_PTRANS))) अणु
		/* Oops, HPC detected some sort of error. */
		अगर (status & SEEQ_TSTAT_R16)
			dev->stats.tx_पातed_errors++;
		अगर (status & SEEQ_TSTAT_UFLOW)
			dev->stats.tx_fअगरo_errors++;
		अगर (status & SEEQ_TSTAT_LCLS)
			dev->stats.collisions++;
	पूर्ण

	/* Ack 'em... */
	क्रम (j = sp->tx_old; j != sp->tx_new; j = NEXT_TX(j)) अणु
		td = &sp->tx_desc[j];

		dma_sync_desc_cpu(dev, td);
		अगर (!(td->tdma.cntinfo & (HPCDMA_XIU)))
			अवरोध;
		अगर (!(td->tdma.cntinfo & (HPCDMA_ETXD))) अणु
			dma_sync_desc_dev(dev, td);
			अगर (!(status & HPC3_ETXCTRL_ACTIVE)) अणु
				hregs->tx_ndptr = VIRT_TO_DMA(sp, td);
				hregs->tx_ctrl = HPC3_ETXCTRL_ACTIVE;
			पूर्ण
			अवरोध;
		पूर्ण
		dev->stats.tx_packets++;
		sp->tx_old = NEXT_TX(sp->tx_old);
		td->tdma.cntinfo &= ~(HPCDMA_XIU | HPCDMA_XIE);
		td->tdma.cntinfo |= HPCDMA_EOX;
		अगर (td->skb) अणु
			dev_kमुक्त_skb_any(td->skb);
			td->skb = शून्य;
		पूर्ण
		dma_sync_desc_dev(dev, td);
	पूर्ण
पूर्ण

अटल irqवापस_t sgiseeq_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	काष्ठा hpc3_ethregs *hregs = sp->hregs;
	काष्ठा sgiseeq_regs *sregs = sp->sregs;

	spin_lock(&sp->tx_lock);

	/* Ack the IRQ and set software state. */
	hregs->reset = HPC3_ERST_CLRIRQ;

	/* Always check क्रम received packets. */
	sgiseeq_rx(dev, sp, hregs, sregs);

	/* Only check क्रम tx acks अगर we have something queued. */
	अगर (sp->tx_old != sp->tx_new)
		sgiseeq_tx(dev, sp, hregs, sregs);

	अगर ((TX_BUFFS_AVAIL(sp) > 0) && netअगर_queue_stopped(dev)) अणु
		netअगर_wake_queue(dev);
	पूर्ण
	spin_unlock(&sp->tx_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sgiseeq_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	काष्ठा sgiseeq_regs *sregs = sp->sregs;
	अचिन्हित पूर्णांक irq = dev->irq;
	पूर्णांक err;

	अगर (request_irq(irq, sgiseeq_पूर्णांकerrupt, 0, sgiseeqstr, dev)) अणु
		prपूर्णांकk(KERN_ERR "Seeq8003: Can't get irq %d\n", dev->irq);
		वापस -EAGAIN;
	पूर्ण

	err = init_seeq(dev, sp, sregs);
	अगर (err)
		जाओ out_मुक्त_irq;

	netअगर_start_queue(dev);

	वापस 0;

out_मुक्त_irq:
	मुक्त_irq(irq, dev);

	वापस err;
पूर्ण

अटल पूर्णांक sgiseeq_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	काष्ठा sgiseeq_regs *sregs = sp->sregs;
	अचिन्हित पूर्णांक irq = dev->irq;

	netअगर_stop_queue(dev);

	/* Shutकरोwn the Seeq. */
	reset_hpc3_and_seeq(sp->hregs, sregs);
	मुक्त_irq(irq, dev);
	seeq_purge_ring(dev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sgiseeq_reset(काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	काष्ठा sgiseeq_regs *sregs = sp->sregs;
	पूर्णांक err;

	err = init_seeq(dev, sp, sregs);
	अगर (err)
		वापस err;

	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);

	वापस 0;
पूर्ण

अटल netdev_tx_t
sgiseeq_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	काष्ठा hpc3_ethregs *hregs = sp->hregs;
	अचिन्हित दीर्घ flags;
	काष्ठा sgiseeq_tx_desc *td;
	पूर्णांक len, entry;

	spin_lock_irqsave(&sp->tx_lock, flags);

	/* Setup... */
	len = skb->len;
	अगर (len < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN)) अणु
			spin_unlock_irqrestore(&sp->tx_lock, flags);
			वापस NETDEV_TX_OK;
		पूर्ण
		len = ETH_ZLEN;
	पूर्ण

	dev->stats.tx_bytes += len;
	entry = sp->tx_new;
	td = &sp->tx_desc[entry];
	dma_sync_desc_cpu(dev, td);

	/* Create entry.  There are so many races with adding a new
	 * descriptor to the chain:
	 * 1) Assume that the HPC is off processing a DMA chain जबतक
	 *    we are changing all of the following.
	 * 2) Do no allow the HPC to look at a new descriptor until
	 *    we have completely set up it's state.  This means, करो
	 *    not clear HPCDMA_EOX in the current last descritptor
	 *    until the one we are adding looks consistent and could
	 *    be processes right now.
	 * 3) The tx पूर्णांकerrupt code must notice when we've added a new
	 *    entry and the HPC got to the end of the chain beक्रमe we
	 *    added this new entry and restarted it.
	 */
	td->skb = skb;
	td->tdma.pbuf = dma_map_single(dev->dev.parent, skb->data,
				       len, DMA_TO_DEVICE);
	td->tdma.cntinfo = (len & HPCDMA_BCNT) |
	                   HPCDMA_XIU | HPCDMA_EOXP | HPCDMA_XIE | HPCDMA_EOX;
	dma_sync_desc_dev(dev, td);
	अगर (sp->tx_old != sp->tx_new) अणु
		काष्ठा sgiseeq_tx_desc *backend;

		backend = &sp->tx_desc[PREV_TX(sp->tx_new)];
		dma_sync_desc_cpu(dev, backend);
		backend->tdma.cntinfo &= ~HPCDMA_EOX;
		dma_sync_desc_dev(dev, backend);
	पूर्ण
	sp->tx_new = NEXT_TX(sp->tx_new); /* Advance. */

	/* Maybe kick the HPC back पूर्णांकo motion. */
	अगर (!(hregs->tx_ctrl & HPC3_ETXCTRL_ACTIVE))
		kick_tx(dev, sp, hregs);

	अगर (!TX_BUFFS_AVAIL(sp))
		netअगर_stop_queue(dev);
	spin_unlock_irqrestore(&sp->tx_lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	prपूर्णांकk(KERN_NOTICE "%s: transmit timed out, resetting\n", dev->name);
	sgiseeq_reset(dev);

	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम sgiseeq_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	अचिन्हित अक्षर oldmode = sp->mode;

	अगर(dev->flags & IFF_PROMISC)
		sp->mode = SEEQ_RCMD_RANY;
	अन्यथा अगर ((dev->flags & IFF_ALLMULTI) || !netdev_mc_empty(dev))
		sp->mode = SEEQ_RCMD_RBMCAST;
	अन्यथा
		sp->mode = SEEQ_RCMD_RBCAST;

	/* XXX I know this sucks, but is there a better way to reprogram
	 * XXX the receiver? At least, this shouldn't happen too often.
	 */

	अगर (oldmode != sp->mode)
		sgiseeq_reset(dev);
पूर्ण

अटल अंतरभूत व्योम setup_tx_ring(काष्ठा net_device *dev,
				 काष्ठा sgiseeq_tx_desc *buf,
				 पूर्णांक nbufs)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	पूर्णांक i = 0;

	जबतक (i < (nbufs - 1)) अणु
		buf[i].tdma.pnext = VIRT_TO_DMA(sp, buf + i + 1);
		buf[i].tdma.pbuf = 0;
		dma_sync_desc_dev(dev, &buf[i]);
		i++;
	पूर्ण
	buf[i].tdma.pnext = VIRT_TO_DMA(sp, buf);
	dma_sync_desc_dev(dev, &buf[i]);
पूर्ण

अटल अंतरभूत व्योम setup_rx_ring(काष्ठा net_device *dev,
				 काष्ठा sgiseeq_rx_desc *buf,
				 पूर्णांक nbufs)
अणु
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);
	पूर्णांक i = 0;

	जबतक (i < (nbufs - 1)) अणु
		buf[i].rdma.pnext = VIRT_TO_DMA(sp, buf + i + 1);
		buf[i].rdma.pbuf = 0;
		dma_sync_desc_dev(dev, &buf[i]);
		i++;
	पूर्ण
	buf[i].rdma.pbuf = 0;
	buf[i].rdma.pnext = VIRT_TO_DMA(sp, buf);
	dma_sync_desc_dev(dev, &buf[i]);
पूर्ण

अटल स्थिर काष्ठा net_device_ops sgiseeq_netdev_ops = अणु
	.nकरो_खोलो		= sgiseeq_खोलो,
	.nकरो_stop		= sgiseeq_बंद,
	.nकरो_start_xmit		= sgiseeq_start_xmit,
	.nकरो_tx_समयout		= समयout,
	.nकरो_set_rx_mode	= sgiseeq_set_multicast,
	.nकरो_set_mac_address	= sgiseeq_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक sgiseeq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sgiseeq_platक्रमm_data *pd = dev_get_platdata(&pdev->dev);
	काष्ठा hpc3_regs *hpcregs = pd->hpc;
	काष्ठा sgiseeq_init_block *sr;
	अचिन्हित पूर्णांक irq = pd->irq;
	काष्ठा sgiseeq_निजी *sp;
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_etherdev(माप (काष्ठा sgiseeq_निजी));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);
	sp = netdev_priv(dev);

	/* Make निजी data page aligned */
	sr = dma_alloc_noncoherent(&pdev->dev, माप(*sp->srings),
			&sp->srings_dma, DMA_BIसूचीECTIONAL, GFP_KERNEL);
	अगर (!sr) अणु
		prपूर्णांकk(KERN_ERR "Sgiseeq: Page alloc failed, aborting.\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_dev;
	पूर्ण
	sp->srings = sr;
	sp->rx_desc = sp->srings->rxvector;
	sp->tx_desc = sp->srings->txvector;
	spin_lock_init(&sp->tx_lock);

	/* A couple calculations now, saves many cycles later. */
	setup_rx_ring(dev, sp->rx_desc, SEEQ_RX_BUFFERS);
	setup_tx_ring(dev, sp->tx_desc, SEEQ_TX_BUFFERS);

	स_नकल(dev->dev_addr, pd->mac, ETH_ALEN);

#अगर_घोषित DEBUG
	gpriv = sp;
	gdev = dev;
#पूर्ण_अगर
	sp->sregs = (काष्ठा sgiseeq_regs *) &hpcregs->eth_ext[0];
	sp->hregs = &hpcregs->ethregs;
	sp->name = sgiseeqstr;
	sp->mode = SEEQ_RCMD_RBCAST;

	/* Setup PIO and DMA transfer timing */
	sp->hregs->pconfig = 0x161;
	sp->hregs->dconfig = HPC3_EDCFG_FIRQ | HPC3_EDCFG_FEOP |
			     HPC3_EDCFG_FRXDC | HPC3_EDCFG_PTO | 0x026;

	/* Setup PIO and DMA transfer timing */
	sp->hregs->pconfig = 0x161;
	sp->hregs->dconfig = HPC3_EDCFG_FIRQ | HPC3_EDCFG_FEOP |
			     HPC3_EDCFG_FRXDC | HPC3_EDCFG_PTO | 0x026;

	/* Reset the chip. */
	hpc3_eth_reset(sp->hregs);

	sp->is_edlc = !(sp->sregs->rw.rregs.collision_tx[0] & 0xff);
	अगर (sp->is_edlc)
		sp->control = SEEQ_CTRL_XCNT | SEEQ_CTRL_ACCNT |
			      SEEQ_CTRL_SFLAG | SEEQ_CTRL_ESHORT |
			      SEEQ_CTRL_ENCARR;

	dev->netdev_ops		= &sgiseeq_netdev_ops;
	dev->watchकरोg_समयo	= (200 * HZ) / 1000;
	dev->irq		= irq;

	अगर (रेजिस्टर_netdev(dev)) अणु
		prपूर्णांकk(KERN_ERR "Sgiseeq: Cannot register net device, "
		       "aborting.\n");
		err = -ENODEV;
		जाओ err_out_मुक्त_attrs;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: %s %pM\n", dev->name, sgiseeqstr, dev->dev_addr);

	वापस 0;

err_out_मुक्त_attrs:
	dma_मुक्त_noncoherent(&pdev->dev, माप(*sp->srings), sp->srings,
		       sp->srings_dma, DMA_BIसूचीECTIONAL);
err_out_मुक्त_dev:
	मुक्त_netdev(dev);

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक sgiseeq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sgiseeq_निजी *sp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	dma_मुक्त_noncoherent(&pdev->dev, माप(*sp->srings), sp->srings,
		       sp->srings_dma, DMA_BIसूचीECTIONAL);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sgiseeq_driver = अणु
	.probe	= sgiseeq_probe,
	.हटाओ	= sgiseeq_हटाओ,
	.driver = अणु
		.name	= "sgiseeq",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(sgiseeq_driver);

MODULE_DESCRIPTION("SGI Seeq 8003 driver");
MODULE_AUTHOR("Linux/MIPS Mailing List <linux-mips@linux-mips.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sgiseeq");
