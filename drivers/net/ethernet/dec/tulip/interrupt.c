<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/पूर्णांकerrupt.c

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

        Please submit bugs to http://bugzilla.kernel.org/ .
*/

#समावेश <linux/pci.h>
#समावेश "tulip.h"
#समावेश <linux/etherdevice.h>

पूर्णांक tulip_rx_copyअवरोध;
अचिन्हित पूर्णांक tulip_max_पूर्णांकerrupt_work;

#अगर_घोषित CONFIG_TULIP_NAPI_HW_MITIGATION
#घोषणा MIT_SIZE 15
#घोषणा MIT_TABLE 15 /* We use 0 or max */

अटल अचिन्हित पूर्णांक mit_table[MIT_SIZE+1] =
अणु
        /*  CRS11 21143 hardware Mitigation Control Interrupt
            We use only RX mitigation we other techniques क्रम
            TX पूर्णांकr. mitigation.

           31    Cycle Size (समयr control)
           30:27 TX समयr in 16 * Cycle size
           26:24 TX No pkts beक्रमe Int.
           23:20 RX समयr in Cycle size
           19:17 RX No pkts beक्रमe Int.
           16       Continues Mode (CM)
        */

        0x0,             /* IM disabled */
        0x80150000,      /* RX समय = 1, RX pkts = 2, CM = 1 */
        0x80150000,
        0x80270000,
        0x80370000,
        0x80490000,
        0x80590000,
        0x80690000,
        0x807B0000,
        0x808B0000,
        0x809D0000,
        0x80AD0000,
        0x80BD0000,
        0x80CF0000,
        0x80DF0000,
//       0x80FF0000      /* RX समय = 16, RX pkts = 7, CM = 1 */
        0x80F10000      /* RX समय = 16, RX pkts = 0, CM = 1 */
पूर्ण;
#पूर्ण_अगर


पूर्णांक tulip_refill_rx(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक entry;
	पूर्णांक refilled = 0;

	/* Refill the Rx ring buffers. */
	क्रम (; tp->cur_rx - tp->dirty_rx > 0; tp->dirty_rx++) अणु
		entry = tp->dirty_rx % RX_RING_SIZE;
		अगर (tp->rx_buffers[entry].skb == शून्य) अणु
			काष्ठा sk_buff *skb;
			dma_addr_t mapping;

			skb = tp->rx_buffers[entry].skb =
				netdev_alloc_skb(dev, PKT_BUF_SZ);
			अगर (skb == शून्य)
				अवरोध;

			mapping = dma_map_single(&tp->pdev->dev, skb->data,
						 PKT_BUF_SZ, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&tp->pdev->dev, mapping)) अणु
				dev_kमुक्त_skb(skb);
				tp->rx_buffers[entry].skb = शून्य;
				अवरोध;
			पूर्ण

			tp->rx_buffers[entry].mapping = mapping;

			tp->rx_ring[entry].buffer1 = cpu_to_le32(mapping);
			refilled++;
		पूर्ण
		tp->rx_ring[entry].status = cpu_to_le32(DescOwned);
	पूर्ण
	अगर(tp->chip_id == LC82C168) अणु
		अगर(((ioपढ़ो32(tp->base_addr + CSR5)>>17)&0x07) == 4) अणु
			/* Rx stopped due to out of buffers,
			 * restart it
			 */
			ioग_लिखो32(0x01, tp->base_addr + CSR2);
		पूर्ण
	पूर्ण
	वापस refilled;
पूर्ण

#अगर_घोषित CONFIG_TULIP_NAPI

व्योम oom_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tulip_निजी *tp = from_समयr(tp, t, oom_समयr);

	napi_schedule(&tp->napi);
पूर्ण

पूर्णांक tulip_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा tulip_निजी *tp = container_of(napi, काष्ठा tulip_निजी, napi);
	काष्ठा net_device *dev = tp->dev;
	पूर्णांक entry = tp->cur_rx % RX_RING_SIZE;
	पूर्णांक work_करोne = 0;
#अगर_घोषित CONFIG_TULIP_NAPI_HW_MITIGATION
	पूर्णांक received = 0;
#पूर्ण_अगर

#अगर_घोषित CONFIG_TULIP_NAPI_HW_MITIGATION

/* that one buffer is needed क्रम mit activation; or might be a
   bug in the ring buffer code; check later -- JHS*/

        अगर (budget >=RX_RING_SIZE) budget--;
#पूर्ण_अगर

	अगर (tulip_debug > 4)
		netdev_dbg(dev, " In tulip_rx(), entry %d %08x\n",
			   entry, tp->rx_ring[entry].status);

       करो अणु
		अगर (ioपढ़ो32(tp->base_addr + CSR5) == 0xffffffff) अणु
			netdev_dbg(dev, " In tulip_poll(), hardware disappeared\n");
			अवरोध;
		पूर्ण
               /* Acknowledge current RX पूर्णांकerrupt sources. */
               ioग_लिखो32((RxIntr | RxNoBuf), tp->base_addr + CSR5);


               /* If we own the next entry, it is a new packet. Send it up. */
               जबतक ( ! (tp->rx_ring[entry].status & cpu_to_le32(DescOwned))) अणु
                       s32 status = le32_to_cpu(tp->rx_ring[entry].status);
		       लघु pkt_len;

                       अगर (tp->dirty_rx + RX_RING_SIZE == tp->cur_rx)
                               अवरोध;

		       अगर (tulip_debug > 5)
				netdev_dbg(dev, "In tulip_rx(), entry %d %08x\n",
					   entry, status);

		       अगर (++work_करोne >= budget)
                               जाओ not_करोne;

		       /*
			* Omit the four octet CRC from the length.
			* (May not be considered valid until we have
			* checked status क्रम RxLengthOver2047 bits)
			*/
		       pkt_len = ((status >> 16) & 0x7ff) - 4;

		       /*
			* Maximum pkt_len is 1518 (1514 + vlan header)
			* Anything higher than this is always invalid
			* regardless of RxLengthOver2047 bits
			*/

		       अगर ((status & (RxLengthOver2047 |
				      RxDescCRCError |
				      RxDescCollisionSeen |
				      RxDescRunt |
				      RxDescDescErr |
				      RxWholePkt)) != RxWholePkt ||
			   pkt_len > 1518) अणु
			       अगर ((status & (RxLengthOver2047 |
					      RxWholePkt)) != RxWholePkt) अणु
                                /* Ingore earlier buffers. */
                                       अगर ((status & 0xffff) != 0x7fff) अणु
                                               अगर (tulip_debug > 1)
                                                       dev_warn(&dev->dev,
								"Oversized Ethernet frame spanned multiple buffers, status %08x!\n",
								status);
						dev->stats.rx_length_errors++;
					पूर्ण
			       पूर्ण अन्यथा अणु
                                /* There was a fatal error. */
				       अगर (tulip_debug > 2)
						netdev_dbg(dev, "Receive error, Rx status %08x\n",
							   status);
					dev->stats.rx_errors++; /* end of a packet.*/
					अगर (pkt_len > 1518 ||
					    (status & RxDescRunt))
						dev->stats.rx_length_errors++;

					अगर (status & 0x0004)
						dev->stats.rx_frame_errors++;
					अगर (status & 0x0002)
						dev->stats.rx_crc_errors++;
					अगर (status & 0x0001)
						dev->stats.rx_fअगरo_errors++;
                               पूर्ण
                       पूर्ण अन्यथा अणु
                               काष्ठा sk_buff *skb;

                               /* Check अगर the packet is दीर्घ enough to accept without copying
                                  to a minimally-sized skbuff. */
                               अगर (pkt_len < tulip_rx_copyअवरोध &&
                                   (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
                                       skb_reserve(skb, 2);    /* 16 byte align the IP header */
					dma_sync_single_क्रम_cpu(&tp->pdev->dev,
								tp->rx_buffers[entry].mapping,
								pkt_len,
								DMA_FROM_DEVICE);
#अगर ! defined(__alpha__)
                                       skb_copy_to_linear_data(skb, tp->rx_buffers[entry].skb->data,
                                                        pkt_len);
                                       skb_put(skb, pkt_len);
#अन्यथा
                                       skb_put_data(skb,
                                                    tp->rx_buffers[entry].skb->data,
                                                    pkt_len);
#पूर्ण_अगर
					dma_sync_single_क्रम_device(&tp->pdev->dev,
								   tp->rx_buffers[entry].mapping,
								   pkt_len,
								   DMA_FROM_DEVICE);
                               पूर्ण अन्यथा अणु        /* Pass up the skb alपढ़ोy on the Rx ring. */
                                       अक्षर *temp = skb_put(skb = tp->rx_buffers[entry].skb,
                                                            pkt_len);

#अगर_अघोषित final_version
                                       अगर (tp->rx_buffers[entry].mapping !=
                                           le32_to_cpu(tp->rx_ring[entry].buffer1)) अणु
                                               dev_err(&dev->dev,
						       "Internal fault: The skbuff addresses do not match in tulip_rx: %08x vs. %08llx %p / %p\n",
						       le32_to_cpu(tp->rx_ring[entry].buffer1),
						       (अचिन्हित दीर्घ दीर्घ)tp->rx_buffers[entry].mapping,
						       skb->head, temp);
                                       पूर्ण
#पूर्ण_अगर

					dma_unmap_single(&tp->pdev->dev,
							 tp->rx_buffers[entry].mapping,
							 PKT_BUF_SZ,
							 DMA_FROM_DEVICE);

                                       tp->rx_buffers[entry].skb = शून्य;
                                       tp->rx_buffers[entry].mapping = 0;
                               पूर्ण
                               skb->protocol = eth_type_trans(skb, dev);

                               netअगर_receive_skb(skb);

				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
                       पूर्ण
#अगर_घोषित CONFIG_TULIP_NAPI_HW_MITIGATION
		       received++;
#पूर्ण_अगर

                       entry = (++tp->cur_rx) % RX_RING_SIZE;
                       अगर (tp->cur_rx - tp->dirty_rx > RX_RING_SIZE/4)
                               tulip_refill_rx(dev);

                पूर्ण

               /* New ack strategy... irq करोes not ack Rx any दीर्घer
                  hopefully this helps */

               /* Really bad things can happen here... If new packet arrives
                * and an irq arrives (tx or just due to occasionally unset
                * mask), it will be acked by irq handler, but new thपढ़ो
                * is not scheduled. It is major hole in design.
                * No idea how to fix this अगर "playing with fire" will fail
                * tomorrow (night 011029). If it will not fail, we won
                * finally: amount of IO did not increase at all. */
       पूर्ण जबतक ((ioपढ़ो32(tp->base_addr + CSR5) & RxIntr));

 #अगर_घोषित CONFIG_TULIP_NAPI_HW_MITIGATION

          /* We use this simplistic scheme क्रम IM. It's proven by
             real lअगरe installations. We can have IM enabled
            जारीsly but this would cause unnecessary latency.
            Unक्रमtunely we can't use all the NET_RX_* feedback here.
            This would turn on IM क्रम devices that is not contributing
            to backlog congestion with unnecessary latency.

             We monitor the device RX-ring and have:

             HW Interrupt Mitigation either ON or OFF.

            ON:  More then 1 pkt received (per पूर्णांकr.) OR we are dropping
             OFF: Only 1 pkt received

             Note. We only use min and max (0, 15) settings from mit_table */


          अगर( tp->flags &  HAS_INTR_MITIGATION) अणु
                 अगर( received > 1 ) अणु
                         अगर( ! tp->mit_on ) अणु
                                 tp->mit_on = 1;
                                 ioग_लिखो32(mit_table[MIT_TABLE], tp->base_addr + CSR11);
                         पूर्ण
                  पूर्ण
                 अन्यथा अणु
                         अगर( tp->mit_on ) अणु
                                 tp->mit_on = 0;
                                 ioग_लिखो32(0, tp->base_addr + CSR11);
                         पूर्ण
                  पूर्ण
          पूर्ण

#पूर्ण_अगर /* CONFIG_TULIP_NAPI_HW_MITIGATION */

         tulip_refill_rx(dev);

         /* If RX ring is not full we are out of memory. */
         अगर (tp->rx_buffers[tp->dirty_rx % RX_RING_SIZE].skb == शून्य)
		 जाओ oom;

         /* Remove us from polling list and enable RX पूर्णांकr. */

	napi_complete_करोne(napi, work_करोne);
	ioग_लिखो32(tulip_tbl[tp->chip_id].valid_पूर्णांकrs, tp->base_addr+CSR7);

         /* The last op happens after poll completion. Which means the following:
          * 1. it can race with disabling irqs in irq handler
          * 2. it can race with dise/enabling irqs in other poll thपढ़ोs
          * 3. अगर an irq उठाओd after beginning loop, it will be immediately
          *    triggered here.
          *
          * Summarizing: the logic results in some redundant irqs both
          * due to races in masking and due to too late acking of alपढ़ोy
          * processed irqs. But it must not result in losing events.
          */

         वापस work_करोne;

 not_करोne:
         अगर (tp->cur_rx - tp->dirty_rx > RX_RING_SIZE/2 ||
             tp->rx_buffers[tp->dirty_rx % RX_RING_SIZE].skb == शून्य)
                 tulip_refill_rx(dev);

         अगर (tp->rx_buffers[tp->dirty_rx % RX_RING_SIZE].skb == शून्य)
		 जाओ oom;

         वापस work_करोne;

 oom:    /* Executed with RX पूर्णांकs disabled */

         /* Start समयr, stop polling, but करो not enable rx पूर्णांकerrupts. */
         mod_समयr(&tp->oom_समयr, jअगरfies+1);

         /* Think: समयr_pending() was an explicit signature of bug.
          * Timer can be pending now but fired and completed
          * beक्रमe we did napi_complete(). See? We would lose it. */

         /* हटाओ ourselves from the polling list */
         napi_complete_करोne(napi, work_करोne);

         वापस work_करोne;
पूर्ण

#अन्यथा /* CONFIG_TULIP_NAPI */

अटल पूर्णांक tulip_rx(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक entry = tp->cur_rx % RX_RING_SIZE;
	पूर्णांक rx_work_limit = tp->dirty_rx + RX_RING_SIZE - tp->cur_rx;
	पूर्णांक received = 0;

	अगर (tulip_debug > 4)
		netdev_dbg(dev, "In tulip_rx(), entry %d %08x\n",
			   entry, tp->rx_ring[entry].status);
	/* If we own the next entry, it is a new packet. Send it up. */
	जबतक ( ! (tp->rx_ring[entry].status & cpu_to_le32(DescOwned))) अणु
		s32 status = le32_to_cpu(tp->rx_ring[entry].status);
		लघु pkt_len;

		अगर (tulip_debug > 5)
			netdev_dbg(dev, "In tulip_rx(), entry %d %08x\n",
				   entry, status);
		अगर (--rx_work_limit < 0)
			अवरोध;

		/*
		  Omit the four octet CRC from the length.
		  (May not be considered valid until we have
		  checked status क्रम RxLengthOver2047 bits)
		*/
		pkt_len = ((status >> 16) & 0x7ff) - 4;
		/*
		  Maximum pkt_len is 1518 (1514 + vlan header)
		  Anything higher than this is always invalid
		  regardless of RxLengthOver2047 bits
		*/

		अगर ((status & (RxLengthOver2047 |
			       RxDescCRCError |
			       RxDescCollisionSeen |
			       RxDescRunt |
			       RxDescDescErr |
			       RxWholePkt))        != RxWholePkt ||
		    pkt_len > 1518) अणु
			अगर ((status & (RxLengthOver2047 |
			     RxWholePkt))         != RxWholePkt) अणु
				/* Ingore earlier buffers. */
				अगर ((status & 0xffff) != 0x7fff) अणु
					अगर (tulip_debug > 1)
						netdev_warn(dev,
							    "Oversized Ethernet frame spanned multiple buffers, status %08x!\n",
							    status);
					dev->stats.rx_length_errors++;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* There was a fatal error. */
				अगर (tulip_debug > 2)
					netdev_dbg(dev, "Receive error, Rx status %08x\n",
						   status);
				dev->stats.rx_errors++; /* end of a packet.*/
				अगर (pkt_len > 1518 ||
				    (status & RxDescRunt))
					dev->stats.rx_length_errors++;
				अगर (status & 0x0004)
					dev->stats.rx_frame_errors++;
				अगर (status & 0x0002)
					dev->stats.rx_crc_errors++;
				अगर (status & 0x0001)
					dev->stats.rx_fअगरo_errors++;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb;

			/* Check अगर the packet is दीर्घ enough to accept without copying
			   to a minimally-sized skbuff. */
			अगर (pkt_len < tulip_rx_copyअवरोध &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != शून्य) अणु
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				dma_sync_single_क्रम_cpu(&tp->pdev->dev,
							tp->rx_buffers[entry].mapping,
							pkt_len,
							DMA_FROM_DEVICE);
#अगर ! defined(__alpha__)
				skb_copy_to_linear_data(skb, tp->rx_buffers[entry].skb->data,
						 pkt_len);
				skb_put(skb, pkt_len);
#अन्यथा
				skb_put_data(skb,
					     tp->rx_buffers[entry].skb->data,
					     pkt_len);
#पूर्ण_अगर
				dma_sync_single_क्रम_device(&tp->pdev->dev,
							   tp->rx_buffers[entry].mapping,
							   pkt_len,
							   DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु 	/* Pass up the skb alपढ़ोy on the Rx ring. */
				अक्षर *temp = skb_put(skb = tp->rx_buffers[entry].skb,
						     pkt_len);

#अगर_अघोषित final_version
				अगर (tp->rx_buffers[entry].mapping !=
				    le32_to_cpu(tp->rx_ring[entry].buffer1)) अणु
					dev_err(&dev->dev,
						"Internal fault: The skbuff addresses do not match in tulip_rx: %08x vs. %Lx %p / %p\n",
						le32_to_cpu(tp->rx_ring[entry].buffer1),
						(दीर्घ दीर्घ)tp->rx_buffers[entry].mapping,
						skb->head, temp);
				पूर्ण
#पूर्ण_अगर

				dma_unmap_single(&tp->pdev->dev,
						 tp->rx_buffers[entry].mapping,
						 PKT_BUF_SZ, DMA_FROM_DEVICE);

				tp->rx_buffers[entry].skb = शून्य;
				tp->rx_buffers[entry].mapping = 0;
			पूर्ण
			skb->protocol = eth_type_trans(skb, dev);

			netअगर_rx(skb);

			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण
		received++;
		entry = (++tp->cur_rx) % RX_RING_SIZE;
	पूर्ण
	वापस received;
पूर्ण
#पूर्ण_अगर  /* CONFIG_TULIP_NAPI */

अटल अंतरभूत अचिन्हित पूर्णांक phy_पूर्णांकerrupt (काष्ठा net_device *dev)
अणु
#अगर_घोषित __hppa__
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	पूर्णांक csr12 = ioपढ़ो32(tp->base_addr + CSR12) & 0xff;

	अगर (csr12 != tp->csr12_shaकरोw) अणु
		/* ack पूर्णांकerrupt */
		ioग_लिखो32(csr12 | 0x02, tp->base_addr + CSR12);
		tp->csr12_shaकरोw = csr12;
		/* करो link change stuff */
		spin_lock(&tp->lock);
		tulip_check_duplex(dev);
		spin_unlock(&tp->lock);
		/* clear irq ack bit */
		ioग_लिखो32(csr12 & ~0x02, tp->base_addr + CSR12);

		वापस 1;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up
   after the Tx thपढ़ो. */
irqवापस_t tulip_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_instance;
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक csr5;
	पूर्णांक missed;
	पूर्णांक rx = 0;
	पूर्णांक tx = 0;
	पूर्णांक oi = 0;
	पूर्णांक maxrx = RX_RING_SIZE;
	पूर्णांक maxtx = TX_RING_SIZE;
	पूर्णांक maxoi = TX_RING_SIZE;
#अगर_घोषित CONFIG_TULIP_NAPI
	पूर्णांक rxd = 0;
#अन्यथा
	पूर्णांक entry;
#पूर्ण_अगर
	अचिन्हित पूर्णांक work_count = tulip_max_पूर्णांकerrupt_work;
	अचिन्हित पूर्णांक handled = 0;

	/* Let's see whether the पूर्णांकerrupt really is क्रम us */
	csr5 = ioपढ़ो32(ioaddr + CSR5);

        अगर (tp->flags & HAS_PHY_IRQ)
	        handled = phy_पूर्णांकerrupt (dev);

	अगर ((csr5 & (NormalIntr|AbnormalIntr)) == 0)
		वापस IRQ_RETVAL(handled);

	tp->nir++;

	करो अणु

#अगर_घोषित CONFIG_TULIP_NAPI

		अगर (!rxd && (csr5 & (RxIntr | RxNoBuf))) अणु
			rxd++;
			/* Mask RX पूर्णांकrs and add the device to poll list. */
			ioग_लिखो32(tulip_tbl[tp->chip_id].valid_पूर्णांकrs&~RxPollInt, ioaddr + CSR7);
			napi_schedule(&tp->napi);

			अगर (!(csr5&~(AbnormalIntr|NormalIntr|RxPollInt|TPLnkPass)))
                               अवरोध;
		पूर्ण

               /* Acknowledge the पूर्णांकerrupt sources we handle here ASAP
                  the poll function करोes Rx and RxNoBuf acking */

		ioग_लिखो32(csr5 & 0x0001ff3f, ioaddr + CSR5);

#अन्यथा
		/* Acknowledge all of the current पूर्णांकerrupt sources ASAP. */
		ioग_लिखो32(csr5 & 0x0001ffff, ioaddr + CSR5);


		अगर (csr5 & (RxIntr | RxNoBuf)) अणु
				rx += tulip_rx(dev);
			tulip_refill_rx(dev);
		पूर्ण

#पूर्ण_अगर /*  CONFIG_TULIP_NAPI */

		अगर (tulip_debug > 4)
			netdev_dbg(dev, "interrupt  csr5=%#8.8x new csr5=%#8.8x\n",
				   csr5, ioपढ़ो32(ioaddr + CSR5));


		अगर (csr5 & (TxNoBuf | TxDied | TxIntr | TimerInt)) अणु
			अचिन्हित पूर्णांक dirty_tx;

			spin_lock(&tp->lock);

			क्रम (dirty_tx = tp->dirty_tx; tp->cur_tx - dirty_tx > 0;
				 dirty_tx++) अणु
				पूर्णांक entry = dirty_tx % TX_RING_SIZE;
				पूर्णांक status = le32_to_cpu(tp->tx_ring[entry].status);

				अगर (status < 0)
					अवरोध;			/* It still has not been Txed */

				/* Check क्रम Rx filter setup frames. */
				अगर (tp->tx_buffers[entry].skb == शून्य) अणु
					/* test because dummy frames not mapped */
					अगर (tp->tx_buffers[entry].mapping)
						dma_unmap_single(&tp->pdev->dev,
								 tp->tx_buffers[entry].mapping,
								 माप(tp->setup_frame),
								 DMA_TO_DEVICE);
					जारी;
				पूर्ण

				अगर (status & 0x8000) अणु
					/* There was an major error, log it. */
#अगर_अघोषित final_version
					अगर (tulip_debug > 1)
						netdev_dbg(dev, "Transmit error, Tx status %08x\n",
							   status);
#पूर्ण_अगर
					dev->stats.tx_errors++;
					अगर (status & 0x4104)
						dev->stats.tx_पातed_errors++;
					अगर (status & 0x0C00)
						dev->stats.tx_carrier_errors++;
					अगर (status & 0x0200)
						dev->stats.tx_winकरोw_errors++;
					अगर (status & 0x0002)
						dev->stats.tx_fअगरo_errors++;
					अगर ((status & 0x0080) && tp->full_duplex == 0)
						dev->stats.tx_heartbeat_errors++;
				पूर्ण अन्यथा अणु
					dev->stats.tx_bytes +=
						tp->tx_buffers[entry].skb->len;
					dev->stats.collisions += (status >> 3) & 15;
					dev->stats.tx_packets++;
				पूर्ण

				dma_unmap_single(&tp->pdev->dev,
						 tp->tx_buffers[entry].mapping,
						 tp->tx_buffers[entry].skb->len,
						 DMA_TO_DEVICE);

				/* Free the original skb. */
				dev_kमुक्त_skb_irq(tp->tx_buffers[entry].skb);
				tp->tx_buffers[entry].skb = शून्य;
				tp->tx_buffers[entry].mapping = 0;
				tx++;
			पूर्ण

#अगर_अघोषित final_version
			अगर (tp->cur_tx - dirty_tx > TX_RING_SIZE) अणु
				dev_err(&dev->dev,
					"Out-of-sync dirty pointer, %d vs. %d\n",
					dirty_tx, tp->cur_tx);
				dirty_tx += TX_RING_SIZE;
			पूर्ण
#पूर्ण_अगर

			अगर (tp->cur_tx - dirty_tx < TX_RING_SIZE - 2)
				netअगर_wake_queue(dev);

			tp->dirty_tx = dirty_tx;
			अगर (csr5 & TxDied) अणु
				अगर (tulip_debug > 2)
					dev_warn(&dev->dev,
						 "The transmitter stopped.  CSR5 is %x, CSR6 %x, new CSR6 %x\n",
						 csr5, ioपढ़ो32(ioaddr + CSR6),
						 tp->csr6);
				tulip_restart_rxtx(tp);
			पूर्ण
			spin_unlock(&tp->lock);
		पूर्ण

		/* Log errors. */
		अगर (csr5 & AbnormalIntr) अणु	/* Abnormal error summary bit. */
			अगर (csr5 == 0xffffffff)
				अवरोध;
			अगर (csr5 & TxJabber)
				dev->stats.tx_errors++;
			अगर (csr5 & TxFIFOUnderflow) अणु
				अगर ((tp->csr6 & 0xC000) != 0xC000)
					tp->csr6 += 0x4000;	/* Bump up the Tx threshold */
				अन्यथा
					tp->csr6 |= 0x00200000;  /* Store-n-क्रमward. */
				/* Restart the transmit process. */
				tulip_restart_rxtx(tp);
				ioग_लिखो32(0, ioaddr + CSR1);
			पूर्ण
			अगर (csr5 & (RxDied | RxNoBuf)) अणु
				अगर (tp->flags & COMET_MAC_ADDR) अणु
					ioग_लिखो32(tp->mc_filter[0], ioaddr + 0xAC);
					ioग_लिखो32(tp->mc_filter[1], ioaddr + 0xB0);
				पूर्ण
			पूर्ण
			अगर (csr5 & RxDied) अणु		/* Missed a Rx frame. */
				dev->stats.rx_missed_errors += ioपढ़ो32(ioaddr + CSR8) & 0xffff;
				dev->stats.rx_errors++;
				tulip_start_rxtx(tp);
			पूर्ण
			/*
			 * NB: t21142_lnk_change() करोes a del_समयr_sync(), so be careful अगर this
			 * call is ever करोne under the spinlock
			 */
			अगर (csr5 & (TPLnkPass | TPLnkFail | 0x08000000)) अणु
				अगर (tp->link_change)
					(tp->link_change)(dev, csr5);
			पूर्ण
			अगर (csr5 & SystemError) अणु
				पूर्णांक error = (csr5 >> 23) & 7;
				/* oops, we hit a PCI error.  The code produced corresponds
				 * to the reason:
				 *  0 - parity error
				 *  1 - master पात
				 *  2 - target पात
				 * Note that on parity error, we should करो a software reset
				 * of the chip to get it back पूर्णांकo a sane state (according
				 * to the 21142/3 करोcs that is).
				 *   -- rmk
				 */
				dev_err(&dev->dev,
					"(%lu) System Error occurred (%d)\n",
					tp->nir, error);
			पूर्ण
			/* Clear all error sources, included unकरोcumented ones! */
			ioग_लिखो32(0x0800f7ba, ioaddr + CSR5);
			oi++;
		पूर्ण
		अगर (csr5 & TimerInt) अणु

			अगर (tulip_debug > 2)
				dev_err(&dev->dev,
					"Re-enabling interrupts, %08x\n",
					csr5);
			ioग_लिखो32(tulip_tbl[tp->chip_id].valid_पूर्णांकrs, ioaddr + CSR7);
			tp->tसमयr = 0;
			oi++;
		पूर्ण
		अगर (tx > maxtx || rx > maxrx || oi > maxoi) अणु
			अगर (tulip_debug > 1)
				dev_warn(&dev->dev, "Too much work during an interrupt, csr5=0x%08x. (%lu) (%d,%d,%d)\n",
					 csr5, tp->nir, tx, rx, oi);

                       /* Acknowledge all पूर्णांकerrupt sources. */
                        ioग_लिखो32(0x8001ffff, ioaddr + CSR5);
                        अगर (tp->flags & HAS_INTR_MITIGATION) अणु
                     /* Josip Loncaric at ICASE did extensive experimentation
			to develop a good पूर्णांकerrupt mitigation setting.*/
                                ioग_लिखो32(0x8b240000, ioaddr + CSR11);
                        पूर्ण अन्यथा अगर (tp->chip_id == LC82C168) अणु
				/* the LC82C168 करोesn't have a hw समयr.*/
				ioग_लिखो32(0x00, ioaddr + CSR7);
				mod_समयr(&tp->समयr, RUN_AT(HZ/50));
			पूर्ण अन्यथा अणु
                          /* Mask all पूर्णांकerrupting sources, set समयr to
				re-enable. */
                                ioग_लिखो32(((~csr5) & 0x0001ebef) | AbnormalIntr | TimerInt, ioaddr + CSR7);
                                ioग_लिखो32(0x0012, ioaddr + CSR11);
                        पूर्ण
			अवरोध;
		पूर्ण

		work_count--;
		अगर (work_count == 0)
			अवरोध;

		csr5 = ioपढ़ो32(ioaddr + CSR5);

#अगर_घोषित CONFIG_TULIP_NAPI
		अगर (rxd)
			csr5 &= ~RxPollInt;
	पूर्ण जबतक ((csr5 & (TxNoBuf |
			  TxDied |
			  TxIntr |
			  TimerInt |
			  /* Abnormal पूर्णांकr. */
			  RxDied |
			  TxFIFOUnderflow |
			  TxJabber |
			  TPLnkFail |
			  SystemError )) != 0);
#अन्यथा
	पूर्ण जबतक ((csr5 & (NormalIntr|AbnormalIntr)) != 0);

	tulip_refill_rx(dev);

	/* check अगर the card is in suspend mode */
	entry = tp->dirty_rx % RX_RING_SIZE;
	अगर (tp->rx_buffers[entry].skb == शून्य) अणु
		अगर (tulip_debug > 1)
			dev_warn(&dev->dev,
				 "in rx suspend mode: (%lu) (tp->cur_rx = %u, ttimer = %d, rx = %d) go/stay in suspend mode\n",
				 tp->nir, tp->cur_rx, tp->tसमयr, rx);
		अगर (tp->chip_id == LC82C168) अणु
			ioग_लिखो32(0x00, ioaddr + CSR7);
			mod_समयr(&tp->समयr, RUN_AT(HZ/50));
		पूर्ण अन्यथा अणु
			अगर (tp->tसमयr == 0 || (ioपढ़ो32(ioaddr + CSR11) & 0xffff) == 0) अणु
				अगर (tulip_debug > 1)
					dev_warn(&dev->dev,
						 "in rx suspend mode: (%lu) set timer\n",
						 tp->nir);
				ioग_लिखो32(tulip_tbl[tp->chip_id].valid_पूर्णांकrs | TimerInt,
					ioaddr + CSR7);
				ioग_लिखो32(TimerInt, ioaddr + CSR5);
				ioग_लिखो32(12, ioaddr + CSR11);
				tp->tसमयr = 1;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_TULIP_NAPI */

	अगर ((missed = ioपढ़ो32(ioaddr + CSR8) & 0x1ffff)) अणु
		dev->stats.rx_dropped += missed & 0x10000 ? 0x10000 : missed;
	पूर्ण

	अगर (tulip_debug > 4)
		netdev_dbg(dev, "exiting interrupt, csr5=%#04x\n",
			   ioपढ़ो32(ioaddr + CSR5));

	वापस IRQ_HANDLED;
पूर्ण
