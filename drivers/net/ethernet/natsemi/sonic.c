<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sonic.c
 *
 * (C) 2005 Finn Thain
 *
 * Converted to DMA API, added zero-copy buffer handling, and
 * (from the mac68k project) पूर्णांकroduced dhd's support क्रम 16-bit cards.
 *
 * (C) 1996,1998 by Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 *
 * This driver is based on work from Andreas Busse, but most of
 * the code is rewritten.
 *
 * (C) 1995 by Andreas Busse (andy@walकरोrf-gmbh.de)
 *
 *    Core code included by प्रणाली sonic drivers
 *
 * And... partially rewritten again by David Huggins-Daines in order
 * to cope with screwed up Macपूर्णांकosh NICs that may or may not use
 * 16-bit DMA.
 *
 * (C) 1999 David Huggins-Daines <dhd@debian.org>
 *
 */

/*
 * Sources: Olivetti M700-10 Risc Personal Computer hardware handbook,
 * National Semiconductors data sheet क्रम the DP83932B Sonic Ethernet
 * controller, and the files "8390.c" and "skeleton.c" in this directory.
 *
 * Additional sources: Nat Semi data sheet क्रम the DP83932C and Nat Semi
 * Application Note AN-746, the files "lance.c" and "ibmlana.c". See also
 * the NetBSD file "sys/arch/mac68k/dev/if_sn.c".
 */

अटल अचिन्हित पूर्णांक version_prपूर्णांकed;

अटल पूर्णांक sonic_debug = -1;
module_param(sonic_debug, पूर्णांक, 0);
MODULE_PARM_DESC(sonic_debug, "debug message level");

अटल व्योम sonic_msg_init(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);

	lp->msg_enable = netअगर_msg_init(sonic_debug, 0);

	अगर (version_prपूर्णांकed++ == 0)
		netअगर_dbg(lp, drv, dev, "%s", version);
पूर्ण

अटल पूर्णांक sonic_alloc_descriptors(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);

	/* Allocate a chunk of memory क्रम the descriptors. Note that this
	 * must not cross a 64K boundary. It is smaller than one page which
	 * means that page alignment is a sufficient condition.
	 */
	lp->descriptors =
		dma_alloc_coherent(lp->device,
				   SIZखातापूर्ण_SONIC_DESC *
				   SONIC_BUS_SCALE(lp->dma_biपंचांगode),
				   &lp->descriptors_laddr, GFP_KERNEL);

	अगर (!lp->descriptors)
		वापस -ENOMEM;

	lp->cda = lp->descriptors;
	lp->tda = lp->cda + SIZखातापूर्ण_SONIC_CDA *
			    SONIC_BUS_SCALE(lp->dma_biपंचांगode);
	lp->rda = lp->tda + SIZखातापूर्ण_SONIC_TD * SONIC_NUM_TDS *
			    SONIC_BUS_SCALE(lp->dma_biपंचांगode);
	lp->rra = lp->rda + SIZखातापूर्ण_SONIC_RD * SONIC_NUM_RDS *
			    SONIC_BUS_SCALE(lp->dma_biपंचांगode);

	lp->cda_laddr = lp->descriptors_laddr;
	lp->tda_laddr = lp->cda_laddr + SIZखातापूर्ण_SONIC_CDA *
					SONIC_BUS_SCALE(lp->dma_biपंचांगode);
	lp->rda_laddr = lp->tda_laddr + SIZखातापूर्ण_SONIC_TD * SONIC_NUM_TDS *
					SONIC_BUS_SCALE(lp->dma_biपंचांगode);
	lp->rra_laddr = lp->rda_laddr + SIZखातापूर्ण_SONIC_RD * SONIC_NUM_RDS *
					SONIC_BUS_SCALE(lp->dma_biपंचांगode);

	वापस 0;
पूर्ण

/*
 * Open/initialize the SONIC controller.
 *
 * This routine should set everything up anew at each खोलो, even
 *  रेजिस्टरs that "should" only need to be set once at boot, so that
 *  there is non-reboot way to recover अगर something goes wrong.
 */
अटल पूर्णांक sonic_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	पूर्णांक i;

	netअगर_dbg(lp, अगरup, dev, "%s: initializing sonic driver\n", __func__);

	spin_lock_init(&lp->lock);

	क्रम (i = 0; i < SONIC_NUM_RRS; i++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, SONIC_RBSIZE + 2);
		अगर (skb == शून्य) अणु
			जबतक(i > 0) अणु /* मुक्त any that were allocated successfully */
				i--;
				dev_kमुक्त_skb(lp->rx_skb[i]);
				lp->rx_skb[i] = शून्य;
			पूर्ण
			prपूर्णांकk(KERN_ERR "%s: couldn't allocate receive buffers\n",
			       dev->name);
			वापस -ENOMEM;
		पूर्ण
		/* align IP header unless DMA requires otherwise */
		अगर (SONIC_BUS_SCALE(lp->dma_biपंचांगode) == 2)
			skb_reserve(skb, 2);
		lp->rx_skb[i] = skb;
	पूर्ण

	क्रम (i = 0; i < SONIC_NUM_RRS; i++) अणु
		dma_addr_t laddr = dma_map_single(lp->device, skb_put(lp->rx_skb[i], SONIC_RBSIZE),
		                                  SONIC_RBSIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(lp->device, laddr)) अणु
			जबतक(i > 0) अणु /* मुक्त any that were mapped successfully */
				i--;
				dma_unmap_single(lp->device, lp->rx_laddr[i], SONIC_RBSIZE, DMA_FROM_DEVICE);
				lp->rx_laddr[i] = (dma_addr_t)0;
			पूर्ण
			क्रम (i = 0; i < SONIC_NUM_RRS; i++) अणु
				dev_kमुक्त_skb(lp->rx_skb[i]);
				lp->rx_skb[i] = शून्य;
			पूर्ण
			prपूर्णांकk(KERN_ERR "%s: couldn't map rx DMA buffers\n",
			       dev->name);
			वापस -ENOMEM;
		पूर्ण
		lp->rx_laddr[i] = laddr;
	पूर्ण

	/*
	 * Initialize the SONIC
	 */
	sonic_init(dev, true);

	netअगर_start_queue(dev);

	netअगर_dbg(lp, अगरup, dev, "%s: Initialization done\n", __func__);

	वापस 0;
पूर्ण

/* Wait क्रम the SONIC to become idle. */
अटल व्योम sonic_quiesce(काष्ठा net_device *dev, u16 mask, bool may_sleep)
अणु
	काष्ठा sonic_local * __maybe_unused lp = netdev_priv(dev);
	पूर्णांक i;
	u16 bits;

	क्रम (i = 0; i < 1000; ++i) अणु
		bits = SONIC_READ(SONIC_CMD) & mask;
		अगर (!bits)
			वापस;
		अगर (!may_sleep)
			udelay(20);
		अन्यथा
			usleep_range(100, 200);
	पूर्ण
	WARN_ONCE(1, "command deadline expired! 0x%04x\n", bits);
पूर्ण

/*
 * Close the SONIC device
 */
अटल पूर्णांक sonic_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	पूर्णांक i;

	netअगर_dbg(lp, अगरकरोwn, dev, "%s\n", __func__);

	netअगर_stop_queue(dev);

	/*
	 * stop the SONIC, disable पूर्णांकerrupts
	 */
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RXDIS);
	sonic_quiesce(dev, SONIC_CR_ALL, true);

	SONIC_WRITE(SONIC_IMR, 0);
	SONIC_WRITE(SONIC_ISR, 0x7fff);
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);

	/* unmap and मुक्त skbs that haven't been transmitted */
	क्रम (i = 0; i < SONIC_NUM_TDS; i++) अणु
		अगर(lp->tx_laddr[i]) अणु
			dma_unmap_single(lp->device, lp->tx_laddr[i], lp->tx_len[i], DMA_TO_DEVICE);
			lp->tx_laddr[i] = (dma_addr_t)0;
		पूर्ण
		अगर(lp->tx_skb[i]) अणु
			dev_kमुक्त_skb(lp->tx_skb[i]);
			lp->tx_skb[i] = शून्य;
		पूर्ण
	पूर्ण

	/* unmap and मुक्त the receive buffers */
	क्रम (i = 0; i < SONIC_NUM_RRS; i++) अणु
		अगर(lp->rx_laddr[i]) अणु
			dma_unmap_single(lp->device, lp->rx_laddr[i], SONIC_RBSIZE, DMA_FROM_DEVICE);
			lp->rx_laddr[i] = (dma_addr_t)0;
		पूर्ण
		अगर(lp->rx_skb[i]) अणु
			dev_kमुक्त_skb(lp->rx_skb[i]);
			lp->rx_skb[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sonic_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	पूर्णांक i;
	/*
	 * put the Sonic पूर्णांकo software-reset mode and
	 * disable all पूर्णांकerrupts beक्रमe releasing DMA buffers
	 */
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RXDIS);
	sonic_quiesce(dev, SONIC_CR_ALL, false);

	SONIC_WRITE(SONIC_IMR, 0);
	SONIC_WRITE(SONIC_ISR, 0x7fff);
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);
	/* We could resend the original skbs. Easier to re-initialise. */
	क्रम (i = 0; i < SONIC_NUM_TDS; i++) अणु
		अगर(lp->tx_laddr[i]) अणु
			dma_unmap_single(lp->device, lp->tx_laddr[i], lp->tx_len[i], DMA_TO_DEVICE);
			lp->tx_laddr[i] = (dma_addr_t)0;
		पूर्ण
		अगर(lp->tx_skb[i]) अणु
			dev_kमुक्त_skb(lp->tx_skb[i]);
			lp->tx_skb[i] = शून्य;
		पूर्ण
	पूर्ण
	/* Try to restart the adaptor. */
	sonic_init(dev, false);
	lp->stats.tx_errors++;
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

/*
 * transmit packet
 *
 * Appends new TD during transmission thus aव्योमing any TX पूर्णांकerrupts
 * until we run out of TDs.
 * This routine पूर्णांकeracts बंदly with the ISR in that it may,
 *   set tx_skb[i]
 *   reset the status flags of the new TD
 *   set and reset EOL flags
 *   stop the tx queue
 * The ISR पूर्णांकeracts with this routine in various ways. It may,
 *   reset tx_skb[i]
 *   test the EOL and status flags of the TDs
 *   wake the tx queue
 * Concurrently with all of this, the SONIC is potentially writing to
 * the status flags of the TDs.
 */

अटल पूर्णांक sonic_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	dma_addr_t laddr;
	पूर्णांक length;
	पूर्णांक entry;
	अचिन्हित दीर्घ flags;

	netअगर_dbg(lp, tx_queued, dev, "%s: skb=%p\n", __func__, skb);

	length = skb->len;
	अगर (length < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			वापस NETDEV_TX_OK;
		length = ETH_ZLEN;
	पूर्ण

	/*
	 * Map the packet data पूर्णांकo the logical DMA address space
	 */

	laddr = dma_map_single(lp->device, skb->data, length, DMA_TO_DEVICE);
	अगर (!laddr) अणु
		pr_err_ratelimited("%s: failed to map tx DMA buffer.\n", dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_irqsave(&lp->lock, flags);

	entry = (lp->eol_tx + 1) & SONIC_TDS_MASK;

	sonic_tda_put(dev, entry, SONIC_TD_STATUS, 0);       /* clear status */
	sonic_tda_put(dev, entry, SONIC_TD_FRAG_COUNT, 1);   /* single fragment */
	sonic_tda_put(dev, entry, SONIC_TD_PKTSIZE, length); /* length of packet */
	sonic_tda_put(dev, entry, SONIC_TD_FRAG_PTR_L, laddr & 0xffff);
	sonic_tda_put(dev, entry, SONIC_TD_FRAG_PTR_H, laddr >> 16);
	sonic_tda_put(dev, entry, SONIC_TD_FRAG_SIZE, length);
	sonic_tda_put(dev, entry, SONIC_TD_LINK,
		sonic_tda_get(dev, entry, SONIC_TD_LINK) | SONIC_EOL);

	sonic_tda_put(dev, lp->eol_tx, SONIC_TD_LINK, ~SONIC_EOL &
		      sonic_tda_get(dev, lp->eol_tx, SONIC_TD_LINK));

	netअगर_dbg(lp, tx_queued, dev, "%s: issuing Tx command\n", __func__);

	SONIC_WRITE(SONIC_CMD, SONIC_CR_TXP);

	lp->tx_len[entry] = length;
	lp->tx_laddr[entry] = laddr;
	lp->tx_skb[entry] = skb;

	lp->eol_tx = entry;

	entry = (entry + 1) & SONIC_TDS_MASK;
	अगर (lp->tx_skb[entry]) अणु
		/* The ring is full, the ISR has yet to process the next TD. */
		netअगर_dbg(lp, tx_queued, dev, "%s: stopping queue\n", __func__);
		netअगर_stop_queue(dev);
		/* after this packet, रुको क्रम ISR to मुक्त up some TDAs */
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * The typical workload of the driver:
 * Handle the network पूर्णांकerface पूर्णांकerrupts.
 */
अटल irqवापस_t sonic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा sonic_local *lp = netdev_priv(dev);
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	/* The lock has two purposes. Firstly, it synchronizes sonic_पूर्णांकerrupt()
	 * with sonic_send_packet() so that the two functions can share state.
	 * Secondly, it makes sonic_पूर्णांकerrupt() re-entrant, as that is required
	 * by macsonic which must use two IRQs with dअगरferent priority levels.
	 */
	spin_lock_irqsave(&lp->lock, flags);

	status = SONIC_READ(SONIC_ISR) & SONIC_IMR_DEFAULT;
	अगर (!status) अणु
		spin_unlock_irqrestore(&lp->lock, flags);

		वापस IRQ_NONE;
	पूर्ण

	करो अणु
		SONIC_WRITE(SONIC_ISR, status); /* clear the पूर्णांकerrupt(s) */

		अगर (status & SONIC_INT_PKTRX) अणु
			netअगर_dbg(lp, पूर्णांकr, dev, "%s: packet rx\n", __func__);
			sonic_rx(dev);	/* got packet(s) */
		पूर्ण

		अगर (status & SONIC_INT_TXDN) अणु
			पूर्णांक entry = lp->cur_tx;
			पूर्णांक td_status;
			पूर्णांक मुक्तd_some = 0;

			/* The state of a Transmit Descriptor may be inferred
			 * from अणु tx_skb[entry], td_status पूर्ण as follows.
			 * अणु clear, clear पूर्ण => the TD has never been used
			 * अणु set,   clear पूर्ण => the TD was handed to SONIC
			 * अणु set,   set   पूर्ण => the TD was handed back
			 * अणु clear, set   पूर्ण => the TD is available क्रम re-use
			 */

			netअगर_dbg(lp, पूर्णांकr, dev, "%s: tx done\n", __func__);

			जबतक (lp->tx_skb[entry] != शून्य) अणु
				अगर ((td_status = sonic_tda_get(dev, entry, SONIC_TD_STATUS)) == 0)
					अवरोध;

				अगर (td_status & SONIC_TCR_PTX) अणु
					lp->stats.tx_packets++;
					lp->stats.tx_bytes += sonic_tda_get(dev, entry, SONIC_TD_PKTSIZE);
				पूर्ण अन्यथा अणु
					अगर (td_status & (SONIC_TCR_EXD |
					    SONIC_TCR_EXC | SONIC_TCR_BCM))
						lp->stats.tx_पातed_errors++;
					अगर (td_status &
					    (SONIC_TCR_NCRS | SONIC_TCR_CRLS))
						lp->stats.tx_carrier_errors++;
					अगर (td_status & SONIC_TCR_OWC)
						lp->stats.tx_winकरोw_errors++;
					अगर (td_status & SONIC_TCR_FU)
						lp->stats.tx_fअगरo_errors++;
				पूर्ण

				/* We must मुक्त the original skb */
				dev_consume_skb_irq(lp->tx_skb[entry]);
				lp->tx_skb[entry] = शून्य;
				/* and unmap DMA buffer */
				dma_unmap_single(lp->device, lp->tx_laddr[entry], lp->tx_len[entry], DMA_TO_DEVICE);
				lp->tx_laddr[entry] = (dma_addr_t)0;
				मुक्तd_some = 1;

				अगर (sonic_tda_get(dev, entry, SONIC_TD_LINK) & SONIC_EOL) अणु
					entry = (entry + 1) & SONIC_TDS_MASK;
					अवरोध;
				पूर्ण
				entry = (entry + 1) & SONIC_TDS_MASK;
			पूर्ण

			अगर (मुक्तd_some || lp->tx_skb[entry] == शून्य)
				netअगर_wake_queue(dev);  /* The ring is no दीर्घer full */
			lp->cur_tx = entry;
		पूर्ण

		/*
		 * check error conditions
		 */
		अगर (status & SONIC_INT_RFO) अणु
			netअगर_dbg(lp, rx_err, dev, "%s: rx fifo overrun\n",
				  __func__);
		पूर्ण
		अगर (status & SONIC_INT_RDE) अणु
			netअगर_dbg(lp, rx_err, dev, "%s: rx descriptors exhausted\n",
				  __func__);
		पूर्ण
		अगर (status & SONIC_INT_RBAE) अणु
			netअगर_dbg(lp, rx_err, dev, "%s: rx buffer area exceeded\n",
				  __func__);
		पूर्ण

		/* counter overruns; all counters are 16bit wide */
		अगर (status & SONIC_INT_FAE)
			lp->stats.rx_frame_errors += 65536;
		अगर (status & SONIC_INT_CRC)
			lp->stats.rx_crc_errors += 65536;
		अगर (status & SONIC_INT_MP)
			lp->stats.rx_missed_errors += 65536;

		/* transmit error */
		अगर (status & SONIC_INT_TXER) अणु
			u16 tcr = SONIC_READ(SONIC_TCR);

			netअगर_dbg(lp, tx_err, dev, "%s: TXER intr, TCR %04x\n",
				  __func__, tcr);

			अगर (tcr & (SONIC_TCR_EXD | SONIC_TCR_EXC |
				   SONIC_TCR_FU | SONIC_TCR_BCM)) अणु
				/* Aborted transmission. Try again. */
				netअगर_stop_queue(dev);
				SONIC_WRITE(SONIC_CMD, SONIC_CR_TXP);
			पूर्ण
		पूर्ण

		/* bus retry */
		अगर (status & SONIC_INT_BR) अणु
			prपूर्णांकk(KERN_ERR "%s: Bus retry occurred! Device interrupt disabled.\n",
				dev->name);
			/* ... to help debug DMA problems causing endless पूर्णांकerrupts. */
			/* Bounce the eth पूर्णांकerface to turn on the पूर्णांकerrupt again. */
			SONIC_WRITE(SONIC_IMR, 0);
		पूर्ण

		status = SONIC_READ(SONIC_ISR) & SONIC_IMR_DEFAULT;
	पूर्ण जबतक (status);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/* Return the array index corresponding to a given Receive Buffer poपूर्णांकer. */
अटल पूर्णांक index_from_addr(काष्ठा sonic_local *lp, dma_addr_t addr,
			   अचिन्हित पूर्णांक last)
अणु
	अचिन्हित पूर्णांक i = last;

	करो अणु
		i = (i + 1) & SONIC_RRS_MASK;
		अगर (addr == lp->rx_laddr[i])
			वापस i;
	पूर्ण जबतक (i != last);

	वापस -ENOENT;
पूर्ण

/* Allocate and map a new skb to be used as a receive buffer. */
अटल bool sonic_alloc_rb(काष्ठा net_device *dev, काष्ठा sonic_local *lp,
			   काष्ठा sk_buff **new_skb, dma_addr_t *new_addr)
अणु
	*new_skb = netdev_alloc_skb(dev, SONIC_RBSIZE + 2);
	अगर (!*new_skb)
		वापस false;

	अगर (SONIC_BUS_SCALE(lp->dma_biपंचांगode) == 2)
		skb_reserve(*new_skb, 2);

	*new_addr = dma_map_single(lp->device, skb_put(*new_skb, SONIC_RBSIZE),
				   SONIC_RBSIZE, DMA_FROM_DEVICE);
	अगर (!*new_addr) अणु
		dev_kमुक्त_skb(*new_skb);
		*new_skb = शून्य;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Place a new receive resource in the Receive Resource Area and update RWP. */
अटल व्योम sonic_update_rra(काष्ठा net_device *dev, काष्ठा sonic_local *lp,
			     dma_addr_t old_addr, dma_addr_t new_addr)
अणु
	अचिन्हित पूर्णांक entry = sonic_rr_entry(dev, SONIC_READ(SONIC_RWP));
	अचिन्हित पूर्णांक end = sonic_rr_entry(dev, SONIC_READ(SONIC_RRP));
	u32 buf;

	/* The resources in the range [RRP, RWP) beदीर्घ to the SONIC. This loop
	 * scans the other resources in the RRA, those in the range [RWP, RRP).
	 */
	करो अणु
		buf = (sonic_rra_get(dev, entry, SONIC_RR_BUFADR_H) << 16) |
		      sonic_rra_get(dev, entry, SONIC_RR_BUFADR_L);

		अगर (buf == old_addr)
			अवरोध;

		entry = (entry + 1) & SONIC_RRS_MASK;
	पूर्ण जबतक (entry != end);

	WARN_ONCE(buf != old_addr, "failed to find resource!\n");

	sonic_rra_put(dev, entry, SONIC_RR_BUFADR_H, new_addr >> 16);
	sonic_rra_put(dev, entry, SONIC_RR_BUFADR_L, new_addr & 0xffff);

	entry = (entry + 1) & SONIC_RRS_MASK;

	SONIC_WRITE(SONIC_RWP, sonic_rr_addr(dev, entry));
पूर्ण

/*
 * We have a good packet(s), pass it/them up the network stack.
 */
अटल व्योम sonic_rx(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	पूर्णांक entry = lp->cur_rx;
	पूर्णांक prev_entry = lp->eol_rx;
	bool rbe = false;

	जबतक (sonic_rda_get(dev, entry, SONIC_RD_IN_USE) == 0) अणु
		u16 status = sonic_rda_get(dev, entry, SONIC_RD_STATUS);

		/* If the RD has LPKT set, the chip has finished with the RB */
		अगर ((status & SONIC_RCR_PRX) && (status & SONIC_RCR_LPKT)) अणु
			काष्ठा sk_buff *new_skb;
			dma_addr_t new_laddr;
			u32 addr = (sonic_rda_get(dev, entry,
						  SONIC_RD_PKTPTR_H) << 16) |
				   sonic_rda_get(dev, entry, SONIC_RD_PKTPTR_L);
			पूर्णांक i = index_from_addr(lp, addr, entry);

			अगर (i < 0) अणु
				WARN_ONCE(1, "failed to find buffer!\n");
				अवरोध;
			पूर्ण

			अगर (sonic_alloc_rb(dev, lp, &new_skb, &new_laddr)) अणु
				काष्ठा sk_buff *used_skb = lp->rx_skb[i];
				पूर्णांक pkt_len;

				/* Pass the used buffer up the stack */
				dma_unmap_single(lp->device, addr, SONIC_RBSIZE,
						 DMA_FROM_DEVICE);

				pkt_len = sonic_rda_get(dev, entry,
							SONIC_RD_PKTLEN);
				skb_trim(used_skb, pkt_len);
				used_skb->protocol = eth_type_trans(used_skb,
								    dev);
				netअगर_rx(used_skb);
				lp->stats.rx_packets++;
				lp->stats.rx_bytes += pkt_len;

				lp->rx_skb[i] = new_skb;
				lp->rx_laddr[i] = new_laddr;
			पूर्ण अन्यथा अणु
				/* Failed to obtain a new buffer so re-use it */
				new_laddr = addr;
				lp->stats.rx_dropped++;
			पूर्ण
			/* If RBE is alपढ़ोy निश्चितed when RWP advances then
			 * it's safe to clear RBE after processing this packet.
			 */
			rbe = rbe || SONIC_READ(SONIC_ISR) & SONIC_INT_RBE;
			sonic_update_rra(dev, lp, addr, new_laddr);
		पूर्ण
		/*
		 * give back the descriptor
		 */
		sonic_rda_put(dev, entry, SONIC_RD_STATUS, 0);
		sonic_rda_put(dev, entry, SONIC_RD_IN_USE, 1);

		prev_entry = entry;
		entry = (entry + 1) & SONIC_RDS_MASK;
	पूर्ण

	lp->cur_rx = entry;

	अगर (prev_entry != lp->eol_rx) अणु
		/* Advance the EOL flag to put descriptors back पूर्णांकo service */
		sonic_rda_put(dev, prev_entry, SONIC_RD_LINK, SONIC_EOL |
			      sonic_rda_get(dev, prev_entry, SONIC_RD_LINK));
		sonic_rda_put(dev, lp->eol_rx, SONIC_RD_LINK, ~SONIC_EOL &
			      sonic_rda_get(dev, lp->eol_rx, SONIC_RD_LINK));
		lp->eol_rx = prev_entry;
	पूर्ण

	अगर (rbe)
		SONIC_WRITE(SONIC_ISR, SONIC_INT_RBE);
पूर्ण


/*
 * Get the current statistics.
 * This may be called with the device खोलो or बंदd.
 */
अटल काष्ठा net_device_stats *sonic_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);

	/* पढ़ो the tally counter from the SONIC and reset them */
	lp->stats.rx_crc_errors += SONIC_READ(SONIC_CRCT);
	SONIC_WRITE(SONIC_CRCT, 0xffff);
	lp->stats.rx_frame_errors += SONIC_READ(SONIC_FAET);
	SONIC_WRITE(SONIC_FAET, 0xffff);
	lp->stats.rx_missed_errors += SONIC_READ(SONIC_MPT);
	SONIC_WRITE(SONIC_MPT, 0xffff);

	वापस &lp->stats;
पूर्ण


/*
 * Set or clear the multicast filter क्रम this adaptor.
 */
अटल व्योम sonic_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक rcr;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित अक्षर *addr;
	पूर्णांक i;

	rcr = SONIC_READ(SONIC_RCR) & ~(SONIC_RCR_PRO | SONIC_RCR_AMC);
	rcr |= SONIC_RCR_BRD;	/* accept broadcast packets */

	अगर (dev->flags & IFF_PROMISC) अणु	/* set promiscuous mode */
		rcr |= SONIC_RCR_PRO;
	पूर्ण अन्यथा अणु
		अगर ((dev->flags & IFF_ALLMULTI) ||
		    (netdev_mc_count(dev) > 15)) अणु
			rcr |= SONIC_RCR_AMC;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ flags;

			netअगर_dbg(lp, अगरup, dev, "%s: mc_count %d\n", __func__,
				  netdev_mc_count(dev));
			sonic_set_cam_enable(dev, 1);  /* always enable our own address */
			i = 1;
			netdev_क्रम_each_mc_addr(ha, dev) अणु
				addr = ha->addr;
				sonic_cda_put(dev, i, SONIC_CD_CAP0, addr[1] << 8 | addr[0]);
				sonic_cda_put(dev, i, SONIC_CD_CAP1, addr[3] << 8 | addr[2]);
				sonic_cda_put(dev, i, SONIC_CD_CAP2, addr[5] << 8 | addr[4]);
				sonic_set_cam_enable(dev, sonic_get_cam_enable(dev) | (1 << i));
				i++;
			पूर्ण
			SONIC_WRITE(SONIC_CDC, 16);
			SONIC_WRITE(SONIC_CDP, lp->cda_laddr & 0xffff);

			/* LCAM and TXP commands can't be used simultaneously */
			spin_lock_irqsave(&lp->lock, flags);
			sonic_quiesce(dev, SONIC_CR_TXP, false);
			SONIC_WRITE(SONIC_CMD, SONIC_CR_LCAM);
			sonic_quiesce(dev, SONIC_CR_LCAM, false);
			spin_unlock_irqrestore(&lp->lock, flags);
		पूर्ण
	पूर्ण

	netअगर_dbg(lp, अगरup, dev, "%s: setting RCR=%x\n", __func__, rcr);

	SONIC_WRITE(SONIC_RCR, rcr);
पूर्ण


/*
 * Initialize the SONIC ethernet controller.
 */
अटल पूर्णांक sonic_init(काष्ठा net_device *dev, bool may_sleep)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	पूर्णांक i;

	/*
	 * put the Sonic पूर्णांकo software-reset mode and
	 * disable all पूर्णांकerrupts
	 */
	SONIC_WRITE(SONIC_IMR, 0);
	SONIC_WRITE(SONIC_ISR, 0x7fff);
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);

	/* While in reset mode, clear CAM Enable रेजिस्टर */
	SONIC_WRITE(SONIC_CE, 0);

	/*
	 * clear software reset flag, disable receiver, clear and
	 * enable पूर्णांकerrupts, then completely initialize the SONIC
	 */
	SONIC_WRITE(SONIC_CMD, 0);
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RXDIS | SONIC_CR_STP);
	sonic_quiesce(dev, SONIC_CR_ALL, may_sleep);

	/*
	 * initialize the receive resource area
	 */
	netअगर_dbg(lp, अगरup, dev, "%s: initialize receive resource area\n",
		  __func__);

	क्रम (i = 0; i < SONIC_NUM_RRS; i++) अणु
		u16 bufadr_l = (अचिन्हित दीर्घ)lp->rx_laddr[i] & 0xffff;
		u16 bufadr_h = (अचिन्हित दीर्घ)lp->rx_laddr[i] >> 16;
		sonic_rra_put(dev, i, SONIC_RR_BUFADR_L, bufadr_l);
		sonic_rra_put(dev, i, SONIC_RR_BUFADR_H, bufadr_h);
		sonic_rra_put(dev, i, SONIC_RR_बफ_मानE_L, SONIC_RBSIZE >> 1);
		sonic_rra_put(dev, i, SONIC_RR_बफ_मानE_H, 0);
	पूर्ण

	/* initialize all RRA रेजिस्टरs */
	SONIC_WRITE(SONIC_RSA, sonic_rr_addr(dev, 0));
	SONIC_WRITE(SONIC_REA, sonic_rr_addr(dev, SONIC_NUM_RRS));
	SONIC_WRITE(SONIC_RRP, sonic_rr_addr(dev, 0));
	SONIC_WRITE(SONIC_RWP, sonic_rr_addr(dev, SONIC_NUM_RRS - 1));
	SONIC_WRITE(SONIC_URRA, lp->rra_laddr >> 16);
	SONIC_WRITE(SONIC_EOBC, (SONIC_RBSIZE >> 1) - (lp->dma_biपंचांगode ? 2 : 1));

	/* load the resource poपूर्णांकers */
	netअगर_dbg(lp, अगरup, dev, "%s: issuing RRRA command\n", __func__);

	SONIC_WRITE(SONIC_CMD, SONIC_CR_RRRA);
	sonic_quiesce(dev, SONIC_CR_RRRA, may_sleep);

	/*
	 * Initialize the receive descriptors so that they
	 * become a circular linked list, ie. let the last
	 * descriptor poपूर्णांक to the first again.
	 */
	netअगर_dbg(lp, अगरup, dev, "%s: initialize receive descriptors\n",
		  __func__);

	क्रम (i=0; i<SONIC_NUM_RDS; i++) अणु
		sonic_rda_put(dev, i, SONIC_RD_STATUS, 0);
		sonic_rda_put(dev, i, SONIC_RD_PKTLEN, 0);
		sonic_rda_put(dev, i, SONIC_RD_PKTPTR_L, 0);
		sonic_rda_put(dev, i, SONIC_RD_PKTPTR_H, 0);
		sonic_rda_put(dev, i, SONIC_RD_SEQNO, 0);
		sonic_rda_put(dev, i, SONIC_RD_IN_USE, 1);
		sonic_rda_put(dev, i, SONIC_RD_LINK,
			lp->rda_laddr +
			((i+1) * SIZखातापूर्ण_SONIC_RD * SONIC_BUS_SCALE(lp->dma_biपंचांगode)));
	पूर्ण
	/* fix last descriptor */
	sonic_rda_put(dev, SONIC_NUM_RDS - 1, SONIC_RD_LINK,
		(lp->rda_laddr & 0xffff) | SONIC_EOL);
	lp->eol_rx = SONIC_NUM_RDS - 1;
	lp->cur_rx = 0;
	SONIC_WRITE(SONIC_URDA, lp->rda_laddr >> 16);
	SONIC_WRITE(SONIC_CRDA, lp->rda_laddr & 0xffff);

	/*
	 * initialize transmit descriptors
	 */
	netअगर_dbg(lp, अगरup, dev, "%s: initialize transmit descriptors\n",
		  __func__);

	क्रम (i = 0; i < SONIC_NUM_TDS; i++) अणु
		sonic_tda_put(dev, i, SONIC_TD_STATUS, 0);
		sonic_tda_put(dev, i, SONIC_TD_CONFIG, 0);
		sonic_tda_put(dev, i, SONIC_TD_PKTSIZE, 0);
		sonic_tda_put(dev, i, SONIC_TD_FRAG_COUNT, 0);
		sonic_tda_put(dev, i, SONIC_TD_LINK,
			(lp->tda_laddr & 0xffff) +
			(i + 1) * SIZखातापूर्ण_SONIC_TD * SONIC_BUS_SCALE(lp->dma_biपंचांगode));
		lp->tx_skb[i] = शून्य;
	पूर्ण
	/* fix last descriptor */
	sonic_tda_put(dev, SONIC_NUM_TDS - 1, SONIC_TD_LINK,
		(lp->tda_laddr & 0xffff));

	SONIC_WRITE(SONIC_UTDA, lp->tda_laddr >> 16);
	SONIC_WRITE(SONIC_CTDA, lp->tda_laddr & 0xffff);
	lp->cur_tx = 0;
	lp->eol_tx = SONIC_NUM_TDS - 1;

	/*
	 * put our own address to CAM desc[0]
	 */
	sonic_cda_put(dev, 0, SONIC_CD_CAP0, dev->dev_addr[1] << 8 | dev->dev_addr[0]);
	sonic_cda_put(dev, 0, SONIC_CD_CAP1, dev->dev_addr[3] << 8 | dev->dev_addr[2]);
	sonic_cda_put(dev, 0, SONIC_CD_CAP2, dev->dev_addr[5] << 8 | dev->dev_addr[4]);
	sonic_set_cam_enable(dev, 1);

	क्रम (i = 0; i < 16; i++)
		sonic_cda_put(dev, i, SONIC_CD_ENTRY_POINTER, i);

	/*
	 * initialize CAM रेजिस्टरs
	 */
	SONIC_WRITE(SONIC_CDP, lp->cda_laddr & 0xffff);
	SONIC_WRITE(SONIC_CDC, 16);

	/*
	 * load the CAM
	 */
	SONIC_WRITE(SONIC_CMD, SONIC_CR_LCAM);
	sonic_quiesce(dev, SONIC_CR_LCAM, may_sleep);

	/*
	 * enable receiver, disable loopback
	 * and enable all पूर्णांकerrupts
	 */
	SONIC_WRITE(SONIC_RCR, SONIC_RCR_DEFAULT);
	SONIC_WRITE(SONIC_TCR, SONIC_TCR_DEFAULT);
	SONIC_WRITE(SONIC_ISR, 0x7fff);
	SONIC_WRITE(SONIC_IMR, SONIC_IMR_DEFAULT);
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RXEN);

	netअगर_dbg(lp, अगरup, dev, "%s: new status=%x\n", __func__,
		  SONIC_READ(SONIC_CMD));

	वापस 0;
पूर्ण

MODULE_LICENSE("GPL");
