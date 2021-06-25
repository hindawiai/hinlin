<शैली गुरु>
/*
 * Combined Ethernet driver क्रम Motorola MPC8xx and MPC82xx.
 *
 * Copyright (c) 2003 Intracom S.A.
 *  by Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2005 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * Heavily based on original FEC driver by Dan Malek <dan@embeddededge.com>
 * and modअगरications by Joakim Tjernlund <joakim.tjernlund@lumentis.se>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "fs_enet.h"

/*************************************************/

MODULE_AUTHOR("Pantelis Antoniou <panto@intracom.gr>");
MODULE_DESCRIPTION("Freescale Ethernet Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक fs_enet_debug = -1; /* -1 == use FS_ENET_DEF_MSG_ENABLE as value */
module_param(fs_enet_debug, पूर्णांक, 0);
MODULE_PARM_DESC(fs_enet_debug,
		 "Freescale bitmapped debugging message enable value");

#घोषणा RX_RING_SIZE	32
#घोषणा TX_RING_SIZE	64

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम fs_enet_netpoll(काष्ठा net_device *dev);
#पूर्ण_अगर

अटल व्योम fs_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	(*fep->ops->set_multicast_list)(dev);
पूर्ण

अटल व्योम skb_align(काष्ठा sk_buff *skb, पूर्णांक align)
अणु
	पूर्णांक off = ((अचिन्हित दीर्घ)skb->data) & (align - 1);

	अगर (off)
		skb_reserve(skb, align - off);
पूर्ण

/* NAPI function */
अटल पूर्णांक fs_enet_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा fs_enet_निजी *fep = container_of(napi, काष्ठा fs_enet_निजी, napi);
	काष्ठा net_device *dev = fep->ndev;
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	cbd_t __iomem *bdp;
	काष्ठा sk_buff *skb, *skbn;
	पूर्णांक received = 0;
	u16 pkt_len, sc;
	पूर्णांक curidx;
	पूर्णांक dirtyidx, करो_wake, करो_restart;
	पूर्णांक tx_left = TX_RING_SIZE;

	spin_lock(&fep->tx_lock);
	bdp = fep->dirty_tx;

	/* clear status bits क्रम napi*/
	(*fep->ops->napi_clear_event)(dev);

	करो_wake = करो_restart = 0;
	जबतक (((sc = CBDR_SC(bdp)) & BD_ENET_TX_READY) == 0 && tx_left) अणु
		dirtyidx = bdp - fep->tx_bd_base;

		अगर (fep->tx_मुक्त == fep->tx_ring)
			अवरोध;

		skb = fep->tx_skbuff[dirtyidx];

		/*
		 * Check क्रम errors.
		 */
		अगर (sc & (BD_ENET_TX_HB | BD_ENET_TX_LC |
			  BD_ENET_TX_RL | BD_ENET_TX_UN | BD_ENET_TX_CSL)) अणु

			अगर (sc & BD_ENET_TX_HB)	/* No heartbeat */
				dev->stats.tx_heartbeat_errors++;
			अगर (sc & BD_ENET_TX_LC)	/* Late collision */
				dev->stats.tx_winकरोw_errors++;
			अगर (sc & BD_ENET_TX_RL)	/* Retrans limit */
				dev->stats.tx_पातed_errors++;
			अगर (sc & BD_ENET_TX_UN)	/* Underrun */
				dev->stats.tx_fअगरo_errors++;
			अगर (sc & BD_ENET_TX_CSL)	/* Carrier lost */
				dev->stats.tx_carrier_errors++;

			अगर (sc & (BD_ENET_TX_LC | BD_ENET_TX_RL | BD_ENET_TX_UN)) अणु
				dev->stats.tx_errors++;
				करो_restart = 1;
			पूर्ण
		पूर्ण अन्यथा
			dev->stats.tx_packets++;

		अगर (sc & BD_ENET_TX_READY) अणु
			dev_warn(fep->dev,
				 "HEY! Enet xmit interrupt and TX_READY.\n");
		पूर्ण

		/*
		 * Deferred means some collisions occurred during transmit,
		 * but we eventually sent the packet OK.
		 */
		अगर (sc & BD_ENET_TX_DEF)
			dev->stats.collisions++;

		/* unmap */
		अगर (fep->mapped_as_page[dirtyidx])
			dma_unmap_page(fep->dev, CBDR_BUFADDR(bdp),
				       CBDR_DATLEN(bdp), DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(fep->dev, CBDR_BUFADDR(bdp),
					 CBDR_DATLEN(bdp), DMA_TO_DEVICE);

		/*
		 * Free the sk buffer associated with this last transmit.
		 */
		अगर (skb) अणु
			dev_kमुक्त_skb(skb);
			fep->tx_skbuff[dirtyidx] = शून्य;
		पूर्ण

		/*
		 * Update poपूर्णांकer to next buffer descriptor to be transmitted.
		 */
		अगर ((sc & BD_ENET_TX_WRAP) == 0)
			bdp++;
		अन्यथा
			bdp = fep->tx_bd_base;

		/*
		 * Since we have मुक्तd up a buffer, the ring is no दीर्घer
		 * full.
		 */
		अगर (++fep->tx_मुक्त == MAX_SKB_FRAGS)
			करो_wake = 1;
		tx_left--;
	पूर्ण

	fep->dirty_tx = bdp;

	अगर (करो_restart)
		(*fep->ops->tx_restart)(dev);

	spin_unlock(&fep->tx_lock);

	अगर (करो_wake)
		netअगर_wake_queue(dev);

	/*
	 * First, grab all of the stats क्रम the incoming packet.
	 * These get messed up अगर we get called due to a busy condition.
	 */
	bdp = fep->cur_rx;

	जबतक (((sc = CBDR_SC(bdp)) & BD_ENET_RX_EMPTY) == 0 &&
	       received < budget) अणु
		curidx = bdp - fep->rx_bd_base;

		/*
		 * Since we have allocated space to hold a complete frame,
		 * the last indicator should be set.
		 */
		अगर ((sc & BD_ENET_RX_LAST) == 0)
			dev_warn(fep->dev, "rcv is not +last\n");

		/*
		 * Check क्रम errors.
		 */
		अगर (sc & (BD_ENET_RX_LG | BD_ENET_RX_SH | BD_ENET_RX_CL |
			  BD_ENET_RX_NO | BD_ENET_RX_CR | BD_ENET_RX_OV)) अणु
			dev->stats.rx_errors++;
			/* Frame too दीर्घ or too लघु. */
			अगर (sc & (BD_ENET_RX_LG | BD_ENET_RX_SH))
				dev->stats.rx_length_errors++;
			/* Frame alignment */
			अगर (sc & (BD_ENET_RX_NO | BD_ENET_RX_CL))
				dev->stats.rx_frame_errors++;
			/* CRC Error */
			अगर (sc & BD_ENET_RX_CR)
				dev->stats.rx_crc_errors++;
			/* FIFO overrun */
			अगर (sc & BD_ENET_RX_OV)
				dev->stats.rx_crc_errors++;

			skbn = fep->rx_skbuff[curidx];
		पूर्ण अन्यथा अणु
			skb = fep->rx_skbuff[curidx];

			/*
			 * Process the incoming frame.
			 */
			dev->stats.rx_packets++;
			pkt_len = CBDR_DATLEN(bdp) - 4;	/* हटाओ CRC */
			dev->stats.rx_bytes += pkt_len + 4;

			अगर (pkt_len <= fpi->rx_copyअवरोध) अणु
				/* +2 to make IP header L1 cache aligned */
				skbn = netdev_alloc_skb(dev, pkt_len + 2);
				अगर (skbn != शून्य) अणु
					skb_reserve(skbn, 2);	/* align IP header */
					skb_copy_from_linear_data(skb,
						      skbn->data, pkt_len);
					swap(skb, skbn);
					dma_sync_single_क्रम_cpu(fep->dev,
						CBDR_BUFADDR(bdp),
						L1_CACHE_ALIGN(pkt_len),
						DMA_FROM_DEVICE);
				पूर्ण
			पूर्ण अन्यथा अणु
				skbn = netdev_alloc_skb(dev, ENET_RX_FRSIZE);

				अगर (skbn) अणु
					dma_addr_t dma;

					skb_align(skbn, ENET_RX_ALIGN);

					dma_unmap_single(fep->dev,
						CBDR_BUFADDR(bdp),
						L1_CACHE_ALIGN(PKT_MAXBUF_SIZE),
						DMA_FROM_DEVICE);

					dma = dma_map_single(fep->dev,
						skbn->data,
						L1_CACHE_ALIGN(PKT_MAXBUF_SIZE),
						DMA_FROM_DEVICE);
					CBDW_BUFADDR(bdp, dma);
				पूर्ण
			पूर्ण

			अगर (skbn != शून्य) अणु
				skb_put(skb, pkt_len);	/* Make room */
				skb->protocol = eth_type_trans(skb, dev);
				received++;
				netअगर_receive_skb(skb);
			पूर्ण अन्यथा अणु
				dev->stats.rx_dropped++;
				skbn = skb;
			पूर्ण
		पूर्ण

		fep->rx_skbuff[curidx] = skbn;
		CBDW_DATLEN(bdp, 0);
		CBDW_SC(bdp, (sc & ~BD_ENET_RX_STATS) | BD_ENET_RX_EMPTY);

		/*
		 * Update BD poपूर्णांकer to next entry.
		 */
		अगर ((sc & BD_ENET_RX_WRAP) == 0)
			bdp++;
		अन्यथा
			bdp = fep->rx_bd_base;

		(*fep->ops->rx_bd_करोne)(dev);
	पूर्ण

	fep->cur_rx = bdp;

	अगर (received < budget && tx_left) अणु
		/* करोne */
		napi_complete_करोne(napi, received);
		(*fep->ops->napi_enable)(dev);

		वापस received;
	पूर्ण

	वापस budget;
पूर्ण

/*
 * The पूर्णांकerrupt handler.
 * This is called from the MPC core पूर्णांकerrupt.
 */
अटल irqवापस_t
fs_enet_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा fs_enet_निजी *fep;
	स्थिर काष्ठा fs_platक्रमm_info *fpi;
	u32 पूर्णांक_events;
	u32 पूर्णांक_clr_events;
	पूर्णांक nr, napi_ok;
	पूर्णांक handled;

	fep = netdev_priv(dev);
	fpi = fep->fpi;

	nr = 0;
	जबतक ((पूर्णांक_events = (*fep->ops->get_पूर्णांक_events)(dev)) != 0) अणु
		nr++;

		पूर्णांक_clr_events = पूर्णांक_events;
		पूर्णांक_clr_events &= ~fep->ev_napi;

		(*fep->ops->clear_पूर्णांक_events)(dev, पूर्णांक_clr_events);

		अगर (पूर्णांक_events & fep->ev_err)
			(*fep->ops->ev_error)(dev, पूर्णांक_events);

		अगर (पूर्णांक_events & fep->ev) अणु
			napi_ok = napi_schedule_prep(&fep->napi);

			(*fep->ops->napi_disable)(dev);
			(*fep->ops->clear_पूर्णांक_events)(dev, fep->ev_napi);

			/* NOTE: it is possible क्रम FCCs in NAPI mode    */
			/* to submit a spurious पूर्णांकerrupt जबतक in poll  */
			अगर (napi_ok)
				__napi_schedule(&fep->napi);
		पूर्ण

	पूर्ण

	handled = nr > 0;
	वापस IRQ_RETVAL(handled);
पूर्ण

व्योम fs_init_bds(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	cbd_t __iomem *bdp;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	fs_cleanup_bds(dev);

	fep->dirty_tx = fep->cur_tx = fep->tx_bd_base;
	fep->tx_मुक्त = fep->tx_ring;
	fep->cur_rx = fep->rx_bd_base;

	/*
	 * Initialize the receive buffer descriptors.
	 */
	क्रम (i = 0, bdp = fep->rx_bd_base; i < fep->rx_ring; i++, bdp++) अणु
		skb = netdev_alloc_skb(dev, ENET_RX_FRSIZE);
		अगर (skb == शून्य)
			अवरोध;

		skb_align(skb, ENET_RX_ALIGN);
		fep->rx_skbuff[i] = skb;
		CBDW_BUFADDR(bdp,
			dma_map_single(fep->dev, skb->data,
				L1_CACHE_ALIGN(PKT_MAXBUF_SIZE),
				DMA_FROM_DEVICE));
		CBDW_DATLEN(bdp, 0);	/* zero */
		CBDW_SC(bdp, BD_ENET_RX_EMPTY |
			((i < fep->rx_ring - 1) ? 0 : BD_SC_WRAP));
	पूर्ण
	/*
	 * अगर we failed, fillup reमुख्यder
	 */
	क्रम (; i < fep->rx_ring; i++, bdp++) अणु
		fep->rx_skbuff[i] = शून्य;
		CBDW_SC(bdp, (i < fep->rx_ring - 1) ? 0 : BD_SC_WRAP);
	पूर्ण

	/*
	 * ...and the same क्रम transmit.
	 */
	क्रम (i = 0, bdp = fep->tx_bd_base; i < fep->tx_ring; i++, bdp++) अणु
		fep->tx_skbuff[i] = शून्य;
		CBDW_BUFADDR(bdp, 0);
		CBDW_DATLEN(bdp, 0);
		CBDW_SC(bdp, (i < fep->tx_ring - 1) ? 0 : BD_SC_WRAP);
	पूर्ण
पूर्ण

व्योम fs_cleanup_bds(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	cbd_t __iomem *bdp;
	पूर्णांक i;

	/*
	 * Reset SKB transmit buffers.
	 */
	क्रम (i = 0, bdp = fep->tx_bd_base; i < fep->tx_ring; i++, bdp++) अणु
		अगर ((skb = fep->tx_skbuff[i]) == शून्य)
			जारी;

		/* unmap */
		dma_unmap_single(fep->dev, CBDR_BUFADDR(bdp),
				skb->len, DMA_TO_DEVICE);

		fep->tx_skbuff[i] = शून्य;
		dev_kमुक्त_skb(skb);
	पूर्ण

	/*
	 * Reset SKB receive buffers
	 */
	क्रम (i = 0, bdp = fep->rx_bd_base; i < fep->rx_ring; i++, bdp++) अणु
		अगर ((skb = fep->rx_skbuff[i]) == शून्य)
			जारी;

		/* unmap */
		dma_unmap_single(fep->dev, CBDR_BUFADDR(bdp),
			L1_CACHE_ALIGN(PKT_MAXBUF_SIZE),
			DMA_FROM_DEVICE);

		fep->rx_skbuff[i] = शून्य;

		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/**********************************************************************************/

#अगर_घोषित CONFIG_FS_ENET_MPC5121_FEC
/*
 * MPC5121 FEC requeries 4-byte alignment क्रम TX data buffer!
 */
अटल काष्ठा sk_buff *tx_skb_align_workaround(काष्ठा net_device *dev,
					       काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *new_skb;

	अगर (skb_linearize(skb))
		वापस शून्य;

	/* Alloc new skb */
	new_skb = netdev_alloc_skb(dev, skb->len + 4);
	अगर (!new_skb)
		वापस शून्य;

	/* Make sure new skb is properly aligned */
	skb_align(new_skb, 4);

	/* Copy data to new skb ... */
	skb_copy_from_linear_data(skb, new_skb->data, skb->len);
	skb_put(new_skb, skb->len);

	/* ... and मुक्त an old one */
	dev_kमुक्त_skb_any(skb);

	वापस new_skb;
पूर्ण
#पूर्ण_अगर

अटल netdev_tx_t
fs_enet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	cbd_t __iomem *bdp;
	पूर्णांक curidx;
	u16 sc;
	पूर्णांक nr_frags;
	skb_frag_t *frag;
	पूर्णांक len;
#अगर_घोषित CONFIG_FS_ENET_MPC5121_FEC
	पूर्णांक is_aligned = 1;
	पूर्णांक i;

	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4)) अणु
		is_aligned = 0;
	पूर्ण अन्यथा अणु
		nr_frags = skb_shinfo(skb)->nr_frags;
		frag = skb_shinfo(skb)->frags;
		क्रम (i = 0; i < nr_frags; i++, frag++) अणु
			अगर (!IS_ALIGNED(skb_frag_off(frag), 4)) अणु
				is_aligned = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!is_aligned) अणु
		skb = tx_skb_align_workaround(dev, skb);
		अगर (!skb) अणु
			/*
			 * We have lost packet due to memory allocation error
			 * in tx_skb_align_workaround(). Hopefully original
			 * skb is still valid, so try transmit it later.
			 */
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	spin_lock(&fep->tx_lock);

	/*
	 * Fill in a Tx ring entry
	 */
	bdp = fep->cur_tx;

	nr_frags = skb_shinfo(skb)->nr_frags;
	अगर (fep->tx_मुक्त <= nr_frags || (CBDR_SC(bdp) & BD_ENET_TX_READY)) अणु
		netअगर_stop_queue(dev);
		spin_unlock(&fep->tx_lock);

		/*
		 * Ooops.  All transmit buffers are full.  Bail out.
		 * This should not happen, since the tx queue should be stopped.
		 */
		dev_warn(fep->dev, "tx queue full!.\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	curidx = bdp - fep->tx_bd_base;

	len = skb->len;
	dev->stats.tx_bytes += len;
	अगर (nr_frags)
		len -= skb->data_len;
	fep->tx_मुक्त -= nr_frags + 1;
	/*
	 * Push the data cache so the CPM करोes not get stale memory data.
	 */
	CBDW_BUFADDR(bdp, dma_map_single(fep->dev,
				skb->data, len, DMA_TO_DEVICE));
	CBDW_DATLEN(bdp, len);

	fep->mapped_as_page[curidx] = 0;
	frag = skb_shinfo(skb)->frags;
	जबतक (nr_frags) अणु
		CBDC_SC(bdp,
			BD_ENET_TX_STATS | BD_ENET_TX_INTR | BD_ENET_TX_LAST |
			BD_ENET_TX_TC);
		CBDS_SC(bdp, BD_ENET_TX_READY);

		अगर ((CBDR_SC(bdp) & BD_ENET_TX_WRAP) == 0) अणु
			bdp++;
			curidx++;
		पूर्ण अन्यथा अणु
			bdp = fep->tx_bd_base;
			curidx = 0;
		पूर्ण

		len = skb_frag_size(frag);
		CBDW_BUFADDR(bdp, skb_frag_dma_map(fep->dev, frag, 0, len,
						   DMA_TO_DEVICE));
		CBDW_DATLEN(bdp, len);

		fep->tx_skbuff[curidx] = शून्य;
		fep->mapped_as_page[curidx] = 1;

		frag++;
		nr_frags--;
	पूर्ण

	/* Trigger transmission start */
	sc = BD_ENET_TX_READY | BD_ENET_TX_INTR |
	     BD_ENET_TX_LAST | BD_ENET_TX_TC;

	/* note that जबतक FEC करोes not have this bit
	 * it marks it as available क्रम software use
	 * yay क्रम hw reuse :) */
	अगर (skb->len <= 60)
		sc |= BD_ENET_TX_PAD;
	CBDC_SC(bdp, BD_ENET_TX_STATS);
	CBDS_SC(bdp, sc);

	/* Save skb poपूर्णांकer. */
	fep->tx_skbuff[curidx] = skb;

	/* If this was the last BD in the ring, start at the beginning again. */
	अगर ((CBDR_SC(bdp) & BD_ENET_TX_WRAP) == 0)
		bdp++;
	अन्यथा
		bdp = fep->tx_bd_base;
	fep->cur_tx = bdp;

	अगर (fep->tx_मुक्त < MAX_SKB_FRAGS)
		netअगर_stop_queue(dev);

	skb_tx_बारtamp(skb);

	(*fep->ops->tx_kickstart)(dev);

	spin_unlock(&fep->tx_lock);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम fs_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fs_enet_निजी *fep = container_of(work, काष्ठा fs_enet_निजी,
						   समयout_work);
	काष्ठा net_device *dev = fep->ndev;
	अचिन्हित दीर्घ flags;
	पूर्णांक wake = 0;

	dev->stats.tx_errors++;

	spin_lock_irqsave(&fep->lock, flags);

	अगर (dev->flags & IFF_UP) अणु
		phy_stop(dev->phydev);
		(*fep->ops->stop)(dev);
		(*fep->ops->restart)(dev);
	पूर्ण

	phy_start(dev->phydev);
	wake = fep->tx_मुक्त >= MAX_SKB_FRAGS &&
	       !(CBDR_SC(fep->cur_tx) & BD_ENET_TX_READY);
	spin_unlock_irqrestore(&fep->lock, flags);

	अगर (wake)
		netअगर_wake_queue(dev);
पूर्ण

अटल व्योम fs_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	schedule_work(&fep->समयout_work);
पूर्ण

/*-----------------------------------------------------------------------------
 *  generic link-change handler - should be sufficient क्रम most हालs
 *-----------------------------------------------------------------------------*/
अटल व्योम generic_adjust_link(काष्ठा  net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	पूर्णांक new_state = 0;

	अगर (phydev->link) अणु
		/* adjust to duplex mode */
		अगर (phydev->duplex != fep->oldduplex) अणु
			new_state = 1;
			fep->oldduplex = phydev->duplex;
		पूर्ण

		अगर (phydev->speed != fep->oldspeed) अणु
			new_state = 1;
			fep->oldspeed = phydev->speed;
		पूर्ण

		अगर (!fep->oldlink) अणु
			new_state = 1;
			fep->oldlink = 1;
		पूर्ण

		अगर (new_state)
			fep->ops->restart(dev);
	पूर्ण अन्यथा अगर (fep->oldlink) अणु
		new_state = 1;
		fep->oldlink = 0;
		fep->oldspeed = 0;
		fep->oldduplex = -1;
	पूर्ण

	अगर (new_state && netअगर_msg_link(fep))
		phy_prपूर्णांक_status(phydev);
पूर्ण


अटल व्योम fs_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fep->lock, flags);

	अगर(fep->ops->adjust_link)
		fep->ops->adjust_link(dev);
	अन्यथा
		generic_adjust_link(dev);

	spin_unlock_irqrestore(&fep->lock, flags);
पूर्ण

अटल पूर्णांक fs_init_phy(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा phy_device *phydev;
	phy_पूर्णांकerface_t अगरace;

	fep->oldlink = 0;
	fep->oldspeed = 0;
	fep->oldduplex = -1;

	अगरace = fep->fpi->use_rmii ?
		PHY_INTERFACE_MODE_RMII : PHY_INTERFACE_MODE_MII;

	phydev = of_phy_connect(dev, fep->fpi->phy_node, &fs_adjust_link, 0,
				अगरace);
	अगर (!phydev) अणु
		dev_err(&dev->dev, "Could not attach to PHY\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fs_enet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	पूर्णांक r;
	पूर्णांक err;

	/* to initialize the fep->cur_rx,... */
	/* not करोing this, will cause a crash in fs_enet_napi */
	fs_init_bds(fep->ndev);

	napi_enable(&fep->napi);

	/* Install our पूर्णांकerrupt handler. */
	r = request_irq(fep->पूर्णांकerrupt, fs_enet_पूर्णांकerrupt, IRQF_SHARED,
			"fs_enet-mac", dev);
	अगर (r != 0) अणु
		dev_err(fep->dev, "Could not allocate FS_ENET IRQ!");
		napi_disable(&fep->napi);
		वापस -EINVAL;
	पूर्ण

	err = fs_init_phy(dev);
	अगर (err) अणु
		मुक्त_irq(fep->पूर्णांकerrupt, dev);
		napi_disable(&fep->napi);
		वापस err;
	पूर्ण
	phy_start(dev->phydev);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक fs_enet_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);
	napi_disable(&fep->napi);
	cancel_work_sync(&fep->समयout_work);
	phy_stop(dev->phydev);

	spin_lock_irqsave(&fep->lock, flags);
	spin_lock(&fep->tx_lock);
	(*fep->ops->stop)(dev);
	spin_unlock(&fep->tx_lock);
	spin_unlock_irqrestore(&fep->lock, flags);

	/* release any irqs */
	phy_disconnect(dev->phydev);
	मुक्त_irq(fep->पूर्णांकerrupt, dev);

	वापस 0;
पूर्ण

/*************************************************************************/

अटल व्योम fs_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
पूर्ण

अटल पूर्णांक fs_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	वापस (*fep->ops->get_regs_len)(dev);
पूर्ण

अटल व्योम fs_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			 व्योम *p)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक r, len;

	len = regs->len;

	spin_lock_irqsave(&fep->lock, flags);
	r = (*fep->ops->get_regs)(dev, p, &len);
	spin_unlock_irqrestore(&fep->lock, flags);

	अगर (r == 0)
		regs->version = 0;
पूर्ण

अटल u32 fs_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	वापस fep->msg_enable;
पूर्ण

अटल व्योम fs_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fep->msg_enable = value;
पूर्ण

अटल पूर्णांक fs_get_tunable(काष्ठा net_device *dev,
			  स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = fpi->rx_copyअवरोध;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fs_set_tunable(काष्ठा net_device *dev,
			  स्थिर काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		fpi->rx_copyअवरोध = *(u32 *)data;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops fs_ethtool_ops = अणु
	.get_drvinfo = fs_get_drvinfo,
	.get_regs_len = fs_get_regs_len,
	.nway_reset = phy_ethtool_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_msglevel = fs_get_msglevel,
	.set_msglevel = fs_set_msglevel,
	.get_regs = fs_get_regs,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
	.get_tunable = fs_get_tunable,
	.set_tunable = fs_set_tunable,
पूर्ण;

बाह्य पूर्णांक fs_mii_connect(काष्ठा net_device *dev);
बाह्य व्योम fs_mii_disconnect(काष्ठा net_device *dev);

/**************************************************************************************/

#अगर_घोषित CONFIG_FS_ENET_HAS_FEC
#घोषणा IS_FEC(match) ((match)->data == &fs_fec_ops)
#अन्यथा
#घोषणा IS_FEC(match) 0
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops fs_enet_netdev_ops = अणु
	.nकरो_खोलो		= fs_enet_खोलो,
	.nकरो_stop		= fs_enet_बंद,
	.nकरो_start_xmit		= fs_enet_start_xmit,
	.nकरो_tx_समयout		= fs_समयout,
	.nकरो_set_rx_mode	= fs_set_multicast_list,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= fs_enet_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा of_device_id fs_enet_match[];
अटल पूर्णांक fs_enet_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा net_device *ndev;
	काष्ठा fs_enet_निजी *fep;
	काष्ठा fs_platक्रमm_info *fpi;
	स्थिर u32 *data;
	काष्ठा clk *clk;
	पूर्णांक err;
	स्थिर अक्षर *phy_connection_type;
	पूर्णांक privsize, len, ret = -ENODEV;

	match = of_match_device(fs_enet_match, &ofdev->dev);
	अगर (!match)
		वापस -EINVAL;

	fpi = kzalloc(माप(*fpi), GFP_KERNEL);
	अगर (!fpi)
		वापस -ENOMEM;

	अगर (!IS_FEC(match)) अणु
		data = of_get_property(ofdev->dev.of_node, "fsl,cpm-command", &len);
		अगर (!data || len != 4)
			जाओ out_मुक्त_fpi;

		fpi->cp_command = *data;
	पूर्ण

	fpi->rx_ring = RX_RING_SIZE;
	fpi->tx_ring = TX_RING_SIZE;
	fpi->rx_copyअवरोध = 240;
	fpi->napi_weight = 17;
	fpi->phy_node = of_parse_phandle(ofdev->dev.of_node, "phy-handle", 0);
	अगर (!fpi->phy_node && of_phy_is_fixed_link(ofdev->dev.of_node)) अणु
		err = of_phy_रेजिस्टर_fixed_link(ofdev->dev.of_node);
		अगर (err)
			जाओ out_मुक्त_fpi;

		/* In the हाल of a fixed PHY, the DT node associated
		 * to the PHY is the Ethernet MAC DT node.
		 */
		fpi->phy_node = of_node_get(ofdev->dev.of_node);
	पूर्ण

	अगर (of_device_is_compatible(ofdev->dev.of_node, "fsl,mpc5125-fec")) अणु
		phy_connection_type = of_get_property(ofdev->dev.of_node,
						"phy-connection-type", शून्य);
		अगर (phy_connection_type && !म_भेद("rmii", phy_connection_type))
			fpi->use_rmii = 1;
	पूर्ण

	/* make घड़ी lookup non-fatal (the driver is shared among platक्रमms),
	 * but require enable to succeed when a घड़ी was specअगरied/found,
	 * keep a reference to the घड़ी upon successful acquisition
	 */
	clk = devm_clk_get(&ofdev->dev, "per");
	अगर (!IS_ERR(clk)) अणु
		ret = clk_prepare_enable(clk);
		अगर (ret)
			जाओ out_deरेजिस्टर_fixed_link;

		fpi->clk_per = clk;
	पूर्ण

	privsize = माप(*fep) +
	           माप(काष्ठा sk_buff **) *
		     (fpi->rx_ring + fpi->tx_ring) +
		   माप(अक्षर) * fpi->tx_ring;

	ndev = alloc_etherdev(privsize);
	अगर (!ndev) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण

	SET_NETDEV_DEV(ndev, &ofdev->dev);
	platक्रमm_set_drvdata(ofdev, ndev);

	fep = netdev_priv(ndev);
	fep->dev = &ofdev->dev;
	fep->ndev = ndev;
	fep->fpi = fpi;
	fep->ops = match->data;

	ret = fep->ops->setup_data(ndev);
	अगर (ret)
		जाओ out_मुक्त_dev;

	fep->rx_skbuff = (काष्ठा sk_buff **)&fep[1];
	fep->tx_skbuff = fep->rx_skbuff + fpi->rx_ring;
	fep->mapped_as_page = (अक्षर *)(fep->rx_skbuff + fpi->rx_ring +
				       fpi->tx_ring);

	spin_lock_init(&fep->lock);
	spin_lock_init(&fep->tx_lock);

	of_get_mac_address(ofdev->dev.of_node, ndev->dev_addr);

	ret = fep->ops->allocate_bd(ndev);
	अगर (ret)
		जाओ out_cleanup_data;

	fep->rx_bd_base = fep->ring_base;
	fep->tx_bd_base = fep->rx_bd_base + fpi->rx_ring;

	fep->tx_ring = fpi->tx_ring;
	fep->rx_ring = fpi->rx_ring;

	ndev->netdev_ops = &fs_enet_netdev_ops;
	ndev->watchकरोg_समयo = 2 * HZ;
	INIT_WORK(&fep->समयout_work, fs_समयout_work);
	netअगर_napi_add(ndev, &fep->napi, fs_enet_napi, fpi->napi_weight);

	ndev->ethtool_ops = &fs_ethtool_ops;

	netअगर_carrier_off(ndev);

	ndev->features |= NETIF_F_SG;

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret)
		जाओ out_मुक्त_bd;

	pr_info("%s: fs_enet: %pM\n", ndev->name, ndev->dev_addr);

	वापस 0;

out_मुक्त_bd:
	fep->ops->मुक्त_bd(ndev);
out_cleanup_data:
	fep->ops->cleanup_data(ndev);
out_मुक्त_dev:
	मुक्त_netdev(ndev);
out_put:
	clk_disable_unprepare(fpi->clk_per);
out_deरेजिस्टर_fixed_link:
	of_node_put(fpi->phy_node);
	अगर (of_phy_is_fixed_link(ofdev->dev.of_node))
		of_phy_deरेजिस्टर_fixed_link(ofdev->dev.of_node);
out_मुक्त_fpi:
	kमुक्त(fpi);
	वापस ret;
पूर्ण

अटल पूर्णांक fs_enet_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(ofdev);
	काष्ठा fs_enet_निजी *fep = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);

	fep->ops->मुक्त_bd(ndev);
	fep->ops->cleanup_data(ndev);
	dev_set_drvdata(fep->dev, शून्य);
	of_node_put(fep->fpi->phy_node);
	clk_disable_unprepare(fep->fpi->clk_per);
	अगर (of_phy_is_fixed_link(ofdev->dev.of_node))
		of_phy_deरेजिस्टर_fixed_link(ofdev->dev.of_node);
	मुक्त_netdev(ndev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fs_enet_match[] = अणु
#अगर_घोषित CONFIG_FS_ENET_HAS_SCC
	अणु
		.compatible = "fsl,cpm1-scc-enet",
		.data = (व्योम *)&fs_scc_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,cpm2-scc-enet",
		.data = (व्योम *)&fs_scc_ops,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_ENET_HAS_FCC
	अणु
		.compatible = "fsl,cpm2-fcc-enet",
		.data = (व्योम *)&fs_fcc_ops,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_ENET_HAS_FEC
#अगर_घोषित CONFIG_FS_ENET_MPC5121_FEC
	अणु
		.compatible = "fsl,mpc5121-fec",
		.data = (व्योम *)&fs_fec_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,mpc5125-fec",
		.data = (व्योम *)&fs_fec_ops,
	पूर्ण,
#अन्यथा
	अणु
		.compatible = "fsl,pq1-fec-enet",
		.data = (व्योम *)&fs_fec_ops,
	पूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fs_enet_match);

अटल काष्ठा platक्रमm_driver fs_enet_driver = अणु
	.driver = अणु
		.name = "fs_enet",
		.of_match_table = fs_enet_match,
	पूर्ण,
	.probe = fs_enet_probe,
	.हटाओ = fs_enet_हटाओ,
पूर्ण;

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम fs_enet_netpoll(काष्ठा net_device *dev)
अणु
       disable_irq(dev->irq);
       fs_enet_पूर्णांकerrupt(dev->irq, dev);
       enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

module_platक्रमm_driver(fs_enet_driver);
