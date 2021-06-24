<शैली गुरु>
/*
 * Driver क्रम the MPC5200 Fast Ethernet Controller
 *
 * Originally written by Dale Farnsworth <dfarnsworth@mvista.com> and
 * now मुख्यtained by Sylvain Munaut <tnt@246tNt.com>
 *
 * Copyright (C) 2007  Domen Puncer, Telargo, Inc.
 * Copyright (C) 2007  Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2003-2004  MontaVista, Software, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/crc32.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/mpc52xx.h>

#समावेश <linux/fsl/bestcomm/bestcomm.h>
#समावेश <linux/fsl/bestcomm/fec.h>

#समावेश "fec_mpc52xx.h"

#घोषणा DRIVER_NAME "mpc52xx-fec"

/* Private driver data काष्ठाure */
काष्ठा mpc52xx_fec_priv अणु
	काष्ठा net_device *ndev;
	पूर्णांक duplex;
	पूर्णांक speed;
	पूर्णांक r_irq;
	पूर्णांक t_irq;
	काष्ठा mpc52xx_fec __iomem *fec;
	काष्ठा bcom_task *rx_dmatsk;
	काष्ठा bcom_task *tx_dmatsk;
	spinlock_t lock;
	पूर्णांक msg_enable;

	/* MDIO link details */
	अचिन्हित पूर्णांक mdio_speed;
	काष्ठा device_node *phy_node;
	क्रमागत phy_state link;
	पूर्णांक seven_wire_mode;
पूर्ण;


अटल irqवापस_t mpc52xx_fec_पूर्णांकerrupt(पूर्णांक, व्योम *);
अटल irqवापस_t mpc52xx_fec_rx_पूर्णांकerrupt(पूर्णांक, व्योम *);
अटल irqवापस_t mpc52xx_fec_tx_पूर्णांकerrupt(पूर्णांक, व्योम *);
अटल व्योम mpc52xx_fec_stop(काष्ठा net_device *dev, bool may_sleep);
अटल व्योम mpc52xx_fec_start(काष्ठा net_device *dev);
अटल व्योम mpc52xx_fec_reset(काष्ठा net_device *dev);

#घोषणा MPC52xx_MESSAGES_DEFAULT ( NETIF_MSG_DRV | NETIF_MSG_PROBE | \
		NETIF_MSG_LINK | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP)
अटल पूर्णांक debug = -1;	/* the above शेष */
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "debugging messages level");

अटल व्योम mpc52xx_fec_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	dev_warn(&dev->dev, "transmit timed out\n");

	spin_lock_irqsave(&priv->lock, flags);
	mpc52xx_fec_reset(dev);
	dev->stats.tx_errors++;
	spin_unlock_irqrestore(&priv->lock, flags);

	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम mpc52xx_fec_set_paddr(काष्ठा net_device *dev, u8 *mac)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;

	out_be32(&fec->paddr1, *(u32 *)(&mac[0]));
	out_be32(&fec->paddr2, (*(u16 *)(&mac[4]) << 16) | FEC_PADDR2_TYPE);
पूर्ण

अटल पूर्णांक mpc52xx_fec_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sock = addr;

	स_नकल(dev->dev_addr, sock->sa_data, dev->addr_len);

	mpc52xx_fec_set_paddr(dev, sock->sa_data);
	वापस 0;
पूर्ण

अटल व्योम mpc52xx_fec_मुक्त_rx_buffers(काष्ठा net_device *dev, काष्ठा bcom_task *s)
अणु
	जबतक (!bcom_queue_empty(s)) अणु
		काष्ठा bcom_fec_bd *bd;
		काष्ठा sk_buff *skb;

		skb = bcom_retrieve_buffer(s, शून्य, (काष्ठा bcom_bd **)&bd);
		dma_unmap_single(dev->dev.parent, bd->skb_pa, skb->len,
				 DMA_FROM_DEVICE);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम
mpc52xx_fec_rx_submit(काष्ठा net_device *dev, काष्ठा sk_buff *rskb)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा bcom_fec_bd *bd;

	bd = (काष्ठा bcom_fec_bd *) bcom_prepare_next_buffer(priv->rx_dmatsk);
	bd->status = FEC_RX_BUFFER_SIZE;
	bd->skb_pa = dma_map_single(dev->dev.parent, rskb->data,
				    FEC_RX_BUFFER_SIZE, DMA_FROM_DEVICE);
	bcom_submit_next_buffer(priv->rx_dmatsk, rskb);
पूर्ण

अटल पूर्णांक mpc52xx_fec_alloc_rx_buffers(काष्ठा net_device *dev, काष्ठा bcom_task *rxtsk)
अणु
	काष्ठा sk_buff *skb;

	जबतक (!bcom_queue_full(rxtsk)) अणु
		skb = netdev_alloc_skb(dev, FEC_RX_BUFFER_SIZE);
		अगर (!skb)
			वापस -EAGAIN;

		/* zero out the initial receive buffers to aid debugging */
		स_रखो(skb->data, 0, FEC_RX_BUFFER_SIZE);
		mpc52xx_fec_rx_submit(dev, skb);
	पूर्ण
	वापस 0;
पूर्ण

/* based on generic_adjust_link from fs_enet-मुख्य.c */
अटल व्योम mpc52xx_fec_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	पूर्णांक new_state = 0;

	अगर (phydev->link != PHY_DOWN) अणु
		अगर (phydev->duplex != priv->duplex) अणु
			काष्ठा mpc52xx_fec __iomem *fec = priv->fec;
			u32 rcntrl;
			u32 tcntrl;

			new_state = 1;
			priv->duplex = phydev->duplex;

			rcntrl = in_be32(&fec->r_cntrl);
			tcntrl = in_be32(&fec->x_cntrl);

			rcntrl &= ~FEC_RCNTRL_DRT;
			tcntrl &= ~FEC_TCNTRL_FDEN;
			अगर (phydev->duplex == DUPLEX_FULL)
				tcntrl |= FEC_TCNTRL_FDEN;	/* FD enable */
			अन्यथा
				rcntrl |= FEC_RCNTRL_DRT;	/* disable Rx on Tx (HD) */

			out_be32(&fec->r_cntrl, rcntrl);
			out_be32(&fec->x_cntrl, tcntrl);
		पूर्ण

		अगर (phydev->speed != priv->speed) अणु
			new_state = 1;
			priv->speed = phydev->speed;
		पूर्ण

		अगर (priv->link == PHY_DOWN) अणु
			new_state = 1;
			priv->link = phydev->link;
		पूर्ण

	पूर्ण अन्यथा अगर (priv->link) अणु
		new_state = 1;
		priv->link = PHY_DOWN;
		priv->speed = 0;
		priv->duplex = -1;
	पूर्ण

	अगर (new_state && netअगर_msg_link(priv))
		phy_prपूर्णांक_status(phydev);
पूर्ण

अटल पूर्णांक mpc52xx_fec_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = शून्य;
	पूर्णांक err = -EBUSY;

	अगर (priv->phy_node) अणु
		phydev = of_phy_connect(priv->ndev, priv->phy_node,
					mpc52xx_fec_adjust_link, 0, 0);
		अगर (!phydev) अणु
			dev_err(&dev->dev, "of_phy_connect failed\n");
			वापस -ENODEV;
		पूर्ण
		phy_start(phydev);
	पूर्ण

	अगर (request_irq(dev->irq, mpc52xx_fec_पूर्णांकerrupt, IRQF_SHARED,
	                DRIVER_NAME "_ctrl", dev)) अणु
		dev_err(&dev->dev, "ctrl interrupt request failed\n");
		जाओ मुक्त_phy;
	पूर्ण
	अगर (request_irq(priv->r_irq, mpc52xx_fec_rx_पूर्णांकerrupt, 0,
	                DRIVER_NAME "_rx", dev)) अणु
		dev_err(&dev->dev, "rx interrupt request failed\n");
		जाओ मुक्त_ctrl_irq;
	पूर्ण
	अगर (request_irq(priv->t_irq, mpc52xx_fec_tx_पूर्णांकerrupt, 0,
	                DRIVER_NAME "_tx", dev)) अणु
		dev_err(&dev->dev, "tx interrupt request failed\n");
		जाओ मुक्त_2irqs;
	पूर्ण

	bcom_fec_rx_reset(priv->rx_dmatsk);
	bcom_fec_tx_reset(priv->tx_dmatsk);

	err = mpc52xx_fec_alloc_rx_buffers(dev, priv->rx_dmatsk);
	अगर (err) अणु
		dev_err(&dev->dev, "mpc52xx_fec_alloc_rx_buffers failed\n");
		जाओ मुक्त_irqs;
	पूर्ण

	bcom_enable(priv->rx_dmatsk);
	bcom_enable(priv->tx_dmatsk);

	mpc52xx_fec_start(dev);

	netअगर_start_queue(dev);

	वापस 0;

 मुक्त_irqs:
	मुक्त_irq(priv->t_irq, dev);
 मुक्त_2irqs:
	मुक्त_irq(priv->r_irq, dev);
 मुक्त_ctrl_irq:
	मुक्त_irq(dev->irq, dev);
 मुक्त_phy:
	अगर (phydev) अणु
		phy_stop(phydev);
		phy_disconnect(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mpc52xx_fec_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;

	netअगर_stop_queue(dev);

	mpc52xx_fec_stop(dev, true);

	mpc52xx_fec_मुक्त_rx_buffers(dev, priv->rx_dmatsk);

	मुक्त_irq(dev->irq, dev);
	मुक्त_irq(priv->r_irq, dev);
	मुक्त_irq(priv->t_irq, dev);

	अगर (phydev) अणु
		/* घातer करोwn phy */
		phy_stop(phydev);
		phy_disconnect(phydev);
	पूर्ण

	वापस 0;
पूर्ण

/* This will only be invoked अगर your driver is _not_ in XOFF state.
 * What this means is that you need not check it, and that this
 * invariant will hold अगर you make sure that the netअगर_*_queue()
 * calls are करोne at the proper बार.
 */
अटल netdev_tx_t
mpc52xx_fec_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा bcom_fec_bd *bd;
	अचिन्हित दीर्घ flags;

	अगर (bcom_queue_full(priv->tx_dmatsk)) अणु
		अगर (net_ratelimit())
			dev_err(&dev->dev, "transmit queue overrun\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	bd = (काष्ठा bcom_fec_bd *)
		bcom_prepare_next_buffer(priv->tx_dmatsk);

	bd->status = skb->len | BCOM_FEC_TX_BD_TFD | BCOM_FEC_TX_BD_TC;
	bd->skb_pa = dma_map_single(dev->dev.parent, skb->data, skb->len,
				    DMA_TO_DEVICE);

	skb_tx_बारtamp(skb);
	bcom_submit_next_buffer(priv->tx_dmatsk, skb);
	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (bcom_queue_full(priv->tx_dmatsk)) अणु
		netअगर_stop_queue(dev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम mpc52xx_fec_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);

	disable_irq(priv->t_irq);
	mpc52xx_fec_tx_पूर्णांकerrupt(priv->t_irq, dev);
	enable_irq(priv->t_irq);
	disable_irq(priv->r_irq);
	mpc52xx_fec_rx_पूर्णांकerrupt(priv->r_irq, dev);
	enable_irq(priv->r_irq);
पूर्ण
#पूर्ण_अगर


/* This handles BestComm transmit task पूर्णांकerrupts
 */
अटल irqवापस_t mpc52xx_fec_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);

	spin_lock(&priv->lock);
	जबतक (bcom_buffer_करोne(priv->tx_dmatsk)) अणु
		काष्ठा sk_buff *skb;
		काष्ठा bcom_fec_bd *bd;
		skb = bcom_retrieve_buffer(priv->tx_dmatsk, शून्य,
				(काष्ठा bcom_bd **)&bd);
		dma_unmap_single(dev->dev.parent, bd->skb_pa, skb->len,
				 DMA_TO_DEVICE);

		dev_consume_skb_irq(skb);
	पूर्ण
	spin_unlock(&priv->lock);

	netअगर_wake_queue(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mpc52xx_fec_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा sk_buff *rskb; /* received sk_buff */
	काष्ठा sk_buff *skb;  /* new sk_buff to enqueue in its place */
	काष्ठा bcom_fec_bd *bd;
	u32 status, physaddr;
	पूर्णांक length;

	spin_lock(&priv->lock);

	जबतक (bcom_buffer_करोne(priv->rx_dmatsk)) अणु

		rskb = bcom_retrieve_buffer(priv->rx_dmatsk, &status,
					    (काष्ठा bcom_bd **)&bd);
		physaddr = bd->skb_pa;

		/* Test क्रम errors in received frame */
		अगर (status & BCOM_FEC_RX_BD_ERRORS) अणु
			/* Drop packet and reuse the buffer */
			mpc52xx_fec_rx_submit(dev, rskb);
			dev->stats.rx_dropped++;
			जारी;
		पूर्ण

		/* skbs are allocated on खोलो, so now we allocate a new one,
		 * and हटाओ the old (with the packet) */
		skb = netdev_alloc_skb(dev, FEC_RX_BUFFER_SIZE);
		अगर (!skb) अणु
			/* Can't get a new one : reuse the same & drop pkt */
			dev_notice(&dev->dev, "Low memory - dropped packet.\n");
			mpc52xx_fec_rx_submit(dev, rskb);
			dev->stats.rx_dropped++;
			जारी;
		पूर्ण

		/* Enqueue the new sk_buff back on the hardware */
		mpc52xx_fec_rx_submit(dev, skb);

		/* Process the received skb - Drop the spin lock जबतक
		 * calling पूर्णांकo the network stack */
		spin_unlock(&priv->lock);

		dma_unmap_single(dev->dev.parent, physaddr, rskb->len,
				 DMA_FROM_DEVICE);
		length = status & BCOM_FEC_RX_BD_LEN_MASK;
		skb_put(rskb, length - 4);	/* length without CRC32 */
		rskb->protocol = eth_type_trans(rskb, dev);
		अगर (!skb_defer_rx_बारtamp(rskb))
			netअगर_rx(rskb);

		spin_lock(&priv->lock);
	पूर्ण

	spin_unlock(&priv->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mpc52xx_fec_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;
	u32 ievent;

	ievent = in_be32(&fec->ievent);

	ievent &= ~FEC_IEVENT_MII;	/* mii is handled separately */
	अगर (!ievent)
		वापस IRQ_NONE;

	out_be32(&fec->ievent, ievent);		/* clear pending events */

	/* on fअगरo error, soft-reset fec */
	अगर (ievent & (FEC_IEVENT_RFIFO_ERROR | FEC_IEVENT_XFIFO_ERROR)) अणु

		अगर (net_ratelimit() && (ievent & FEC_IEVENT_RFIFO_ERROR))
			dev_warn(&dev->dev, "FEC_IEVENT_RFIFO_ERROR\n");
		अगर (net_ratelimit() && (ievent & FEC_IEVENT_XFIFO_ERROR))
			dev_warn(&dev->dev, "FEC_IEVENT_XFIFO_ERROR\n");

		spin_lock(&priv->lock);
		mpc52xx_fec_reset(dev);
		spin_unlock(&priv->lock);

		वापस IRQ_HANDLED;
	पूर्ण

	अगर (ievent & ~FEC_IEVENT_TFINT)
		dev_dbg(&dev->dev, "ievent: %08x\n", ievent);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Get the current statistics.
 * This may be called with the card खोलो or बंदd.
 */
अटल काष्ठा net_device_stats *mpc52xx_fec_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;

	stats->rx_bytes = in_be32(&fec->rmon_r_octets);
	stats->rx_packets = in_be32(&fec->rmon_r_packets);
	stats->rx_errors = in_be32(&fec->rmon_r_crc_align) +
		in_be32(&fec->rmon_r_undersize) +
		in_be32(&fec->rmon_r_oversize) +
		in_be32(&fec->rmon_r_frag) +
		in_be32(&fec->rmon_r_jab);

	stats->tx_bytes = in_be32(&fec->rmon_t_octets);
	stats->tx_packets = in_be32(&fec->rmon_t_packets);
	stats->tx_errors = in_be32(&fec->rmon_t_crc_align) +
		in_be32(&fec->rmon_t_undersize) +
		in_be32(&fec->rmon_t_oversize) +
		in_be32(&fec->rmon_t_frag) +
		in_be32(&fec->rmon_t_jab);

	stats->multicast = in_be32(&fec->rmon_r_mc_pkt);
	stats->collisions = in_be32(&fec->rmon_t_col);

	/* detailed rx_errors: */
	stats->rx_length_errors = in_be32(&fec->rmon_r_undersize)
					+ in_be32(&fec->rmon_r_oversize)
					+ in_be32(&fec->rmon_r_frag)
					+ in_be32(&fec->rmon_r_jab);
	stats->rx_over_errors = in_be32(&fec->r_macerr);
	stats->rx_crc_errors = in_be32(&fec->ieee_r_crc);
	stats->rx_frame_errors = in_be32(&fec->ieee_r_align);
	stats->rx_fअगरo_errors = in_be32(&fec->rmon_r_drop);
	stats->rx_missed_errors = in_be32(&fec->rmon_r_drop);

	/* detailed tx_errors: */
	stats->tx_पातed_errors = 0;
	stats->tx_carrier_errors = in_be32(&fec->ieee_t_cserr);
	stats->tx_fअगरo_errors = in_be32(&fec->rmon_t_drop);
	stats->tx_heartbeat_errors = in_be32(&fec->ieee_t_sqe);
	stats->tx_winकरोw_errors = in_be32(&fec->ieee_t_lcol);

	वापस stats;
पूर्ण

/*
 * Read MIB counters in order to reset them,
 * then zero all the stats fields in memory
 */
अटल व्योम mpc52xx_fec_reset_stats(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;

	out_be32(&fec->mib_control, FEC_MIB_DISABLE);
	स_रखो_io(&fec->rmon_t_drop, 0,
		   दुरत्व(काष्ठा mpc52xx_fec, reserved10) -
		   दुरत्व(काष्ठा mpc52xx_fec, rmon_t_drop));
	out_be32(&fec->mib_control, 0);

	स_रखो(&dev->stats, 0, माप(dev->stats));
पूर्ण

/*
 * Set or clear the multicast filter क्रम this adaptor.
 */
अटल व्योम mpc52xx_fec_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;
	u32 rx_control;

	rx_control = in_be32(&fec->r_cntrl);

	अगर (dev->flags & IFF_PROMISC) अणु
		rx_control |= FEC_RCNTRL_PROM;
		out_be32(&fec->r_cntrl, rx_control);
	पूर्ण अन्यथा अणु
		rx_control &= ~FEC_RCNTRL_PROM;
		out_be32(&fec->r_cntrl, rx_control);

		अगर (dev->flags & IFF_ALLMULTI) अणु
			out_be32(&fec->gaddr1, 0xffffffff);
			out_be32(&fec->gaddr2, 0xffffffff);
		पूर्ण अन्यथा अणु
			u32 crc;
			काष्ठा netdev_hw_addr *ha;
			u32 gaddr1 = 0x00000000;
			u32 gaddr2 = 0x00000000;

			netdev_क्रम_each_mc_addr(ha, dev) अणु
				crc = ether_crc_le(6, ha->addr) >> 26;
				अगर (crc >= 32)
					gaddr1 |= 1 << (crc-32);
				अन्यथा
					gaddr2 |= 1 << crc;
			पूर्ण
			out_be32(&fec->gaddr1, gaddr1);
			out_be32(&fec->gaddr2, gaddr2);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mpc52xx_fec_hw_init
 * @dev: network device
 *
 * Setup various hardware setting, only needed once on start
 */
अटल व्योम mpc52xx_fec_hw_init(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;
	पूर्णांक i;

	/* Whack a reset.  We should रुको क्रम this. */
	out_be32(&fec->ecntrl, FEC_ECNTRL_RESET);
	क्रम (i = 0; i < FEC_RESET_DELAY; ++i) अणु
		अगर ((in_be32(&fec->ecntrl) & FEC_ECNTRL_RESET) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i == FEC_RESET_DELAY)
		dev_err(&dev->dev, "FEC Reset timeout!\n");

	/* set छोड़ो to 0x20 frames */
	out_be32(&fec->op_छोड़ो, FEC_OP_PAUSE_OPCODE | 0x20);

	/* high service request will be deनिश्चितed when there's < 7 bytes in fअगरo
	 * low service request will be deनिश्चितed when there's < 4*7 bytes in fअगरo
	 */
	out_be32(&fec->rfअगरo_cntrl, FEC_FIFO_CNTRL_FRAME | FEC_FIFO_CNTRL_LTG_7);
	out_be32(&fec->tfअगरo_cntrl, FEC_FIFO_CNTRL_FRAME | FEC_FIFO_CNTRL_LTG_7);

	/* alarm when <= x bytes in FIFO */
	out_be32(&fec->rfअगरo_alarm, 0x0000030c);
	out_be32(&fec->tfअगरo_alarm, 0x00000100);

	/* begin transmittion when 256 bytes are in FIFO (or खातापूर्ण or FIFO full) */
	out_be32(&fec->x_wmrk, FEC_FIFO_WMRK_256B);

	/* enable crc generation */
	out_be32(&fec->xmit_fsm, FEC_XMIT_FSM_APPEND_CRC | FEC_XMIT_FSM_ENABLE_CRC);
	out_be32(&fec->iaddr1, 0x00000000);	/* No inभागidual filter */
	out_be32(&fec->iaddr2, 0x00000000);	/* No inभागidual filter */

	/* set phy speed.
	 * this can't be करोne in phy driver, since it needs to be called
	 * beक्रमe fec stuff (even on resume) */
	out_be32(&fec->mii_speed, priv->mdio_speed);
पूर्ण

/**
 * mpc52xx_fec_start
 * @dev: network device
 *
 * This function is called to start or restart the FEC during a link
 * change.  This happens on fअगरo errors or when चयनing between half
 * and full duplex.
 */
अटल व्योम mpc52xx_fec_start(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;
	u32 rcntrl;
	u32 tcntrl;
	u32 पंचांगp;

	/* clear sticky error bits */
	पंचांगp = FEC_FIFO_STATUS_ERR | FEC_FIFO_STATUS_UF | FEC_FIFO_STATUS_OF;
	out_be32(&fec->rfअगरo_status, in_be32(&fec->rfअगरo_status) & पंचांगp);
	out_be32(&fec->tfअगरo_status, in_be32(&fec->tfअगरo_status) & पंचांगp);

	/* FIFOs will reset on mpc52xx_fec_enable */
	out_be32(&fec->reset_cntrl, FEC_RESET_CNTRL_ENABLE_IS_RESET);

	/* Set station address. */
	mpc52xx_fec_set_paddr(dev, dev->dev_addr);

	mpc52xx_fec_set_multicast_list(dev);

	/* set max frame len, enable flow control, select mii mode */
	rcntrl = FEC_RX_BUFFER_SIZE << 16;	/* max frame length */
	rcntrl |= FEC_RCNTRL_FCE;

	अगर (!priv->seven_wire_mode)
		rcntrl |= FEC_RCNTRL_MII_MODE;

	अगर (priv->duplex == DUPLEX_FULL)
		tcntrl = FEC_TCNTRL_FDEN;	/* FD enable */
	अन्यथा अणु
		rcntrl |= FEC_RCNTRL_DRT;	/* disable Rx on Tx (HD) */
		tcntrl = 0;
	पूर्ण
	out_be32(&fec->r_cntrl, rcntrl);
	out_be32(&fec->x_cntrl, tcntrl);

	/* Clear any outstanding पूर्णांकerrupt. */
	out_be32(&fec->ievent, 0xffffffff);

	/* Enable पूर्णांकerrupts we wish to service. */
	out_be32(&fec->imask, FEC_IMASK_ENABLE);

	/* And last, enable the transmit and receive processing. */
	out_be32(&fec->ecntrl, FEC_ECNTRL_ETHER_EN);
	out_be32(&fec->r_des_active, 0x01000000);
पूर्ण

/**
 * mpc52xx_fec_stop
 * @dev: network device
 *
 * stop all activity on fec and empty dma buffers
 */
अटल व्योम mpc52xx_fec_stop(काष्ठा net_device *dev, bool may_sleep)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;
	अचिन्हित दीर्घ समयout;

	/* disable all पूर्णांकerrupts */
	out_be32(&fec->imask, 0);

	/* Disable the rx task. */
	bcom_disable(priv->rx_dmatsk);

	/* Wait क्रम tx queue to drain, but only अगर we're in process context */
	अगर (may_sleep) अणु
		समयout = jअगरfies + msecs_to_jअगरfies(2000);
		जबतक (समय_beक्रमe(jअगरfies, समयout) &&
				!bcom_queue_empty(priv->tx_dmatsk))
			msleep(100);

		अगर (समय_after_eq(jअगरfies, समयout))
			dev_err(&dev->dev, "queues didn't drain\n");
#अगर 1
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_err(&dev->dev, "  tx: index: %i, outdex: %i\n",
					priv->tx_dmatsk->index,
					priv->tx_dmatsk->outdex);
			dev_err(&dev->dev, "  rx: index: %i, outdex: %i\n",
					priv->rx_dmatsk->index,
					priv->rx_dmatsk->outdex);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	bcom_disable(priv->tx_dmatsk);

	/* Stop FEC */
	out_be32(&fec->ecntrl, in_be32(&fec->ecntrl) & ~FEC_ECNTRL_ETHER_EN);
पूर्ण

/* reset fec and bestcomm tasks */
अटल व्योम mpc52xx_fec_reset(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	काष्ठा mpc52xx_fec __iomem *fec = priv->fec;

	mpc52xx_fec_stop(dev, false);

	out_be32(&fec->rfअगरo_status, in_be32(&fec->rfअगरo_status));
	out_be32(&fec->reset_cntrl, FEC_RESET_CNTRL_RESET_FIFO);

	mpc52xx_fec_मुक्त_rx_buffers(dev, priv->rx_dmatsk);

	mpc52xx_fec_hw_init(dev);

	bcom_fec_rx_reset(priv->rx_dmatsk);
	bcom_fec_tx_reset(priv->tx_dmatsk);

	mpc52xx_fec_alloc_rx_buffers(dev, priv->rx_dmatsk);

	bcom_enable(priv->rx_dmatsk);
	bcom_enable(priv->tx_dmatsk);

	mpc52xx_fec_start(dev);

	netअगर_wake_queue(dev);
पूर्ण


/* ethtool पूर्णांकerface */

अटल u32 mpc52xx_fec_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	वापस priv->msg_enable;
पूर्ण

अटल व्योम mpc52xx_fec_set_msglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा mpc52xx_fec_priv *priv = netdev_priv(dev);
	priv->msg_enable = level;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops mpc52xx_fec_ethtool_ops = अणु
	.get_link = ethtool_op_get_link,
	.get_msglevel = mpc52xx_fec_get_msglevel,
	.set_msglevel = mpc52xx_fec_set_msglevel,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;


अटल स्थिर काष्ठा net_device_ops mpc52xx_fec_netdev_ops = अणु
	.nकरो_खोलो = mpc52xx_fec_खोलो,
	.nकरो_stop = mpc52xx_fec_बंद,
	.nकरो_start_xmit = mpc52xx_fec_start_xmit,
	.nकरो_set_rx_mode = mpc52xx_fec_set_multicast_list,
	.nकरो_set_mac_address = mpc52xx_fec_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_करो_ioctl = phy_करो_ioctl,
	.nकरो_tx_समयout = mpc52xx_fec_tx_समयout,
	.nकरो_get_stats = mpc52xx_fec_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = mpc52xx_fec_poll_controller,
#पूर्ण_अगर
पूर्ण;

/* ======================================================================== */
/* OF Driver                                                                */
/* ======================================================================== */

अटल पूर्णांक mpc52xx_fec_probe(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक rv;
	काष्ठा net_device *ndev;
	काष्ठा mpc52xx_fec_priv *priv = शून्य;
	काष्ठा resource mem;
	स्थिर u32 *prop;
	पूर्णांक prop_size;
	काष्ठा device_node *np = op->dev.of_node;

	phys_addr_t rx_fअगरo;
	phys_addr_t tx_fअगरo;

	/* Get the ether ndev & it's निजी zone */
	ndev = alloc_etherdev(माप(काष्ठा mpc52xx_fec_priv));
	अगर (!ndev)
		वापस -ENOMEM;

	priv = netdev_priv(ndev);
	priv->ndev = ndev;

	/* Reserve FEC control zone */
	rv = of_address_to_resource(np, 0, &mem);
	अगर (rv) अणु
		pr_err("Error while parsing device node resource\n");
		जाओ err_netdev;
	पूर्ण
	अगर (resource_size(&mem) < माप(काष्ठा mpc52xx_fec)) अणु
		pr_err("invalid resource size (%lx < %x), check mpc52xx_devices.c\n",
		       (अचिन्हित दीर्घ)resource_size(&mem),
		       माप(काष्ठा mpc52xx_fec));
		rv = -EINVAL;
		जाओ err_netdev;
	पूर्ण

	अगर (!request_mem_region(mem.start, माप(काष्ठा mpc52xx_fec),
				DRIVER_NAME)) अणु
		rv = -EBUSY;
		जाओ err_netdev;
	पूर्ण

	/* Init ether ndev with what we have */
	ndev->netdev_ops	= &mpc52xx_fec_netdev_ops;
	ndev->ethtool_ops	= &mpc52xx_fec_ethtool_ops;
	ndev->watchकरोg_समयo	= FEC_WATCHDOG_TIMEOUT;
	ndev->base_addr		= mem.start;
	SET_NETDEV_DEV(ndev, &op->dev);

	spin_lock_init(&priv->lock);

	/* ioremap the zones */
	priv->fec = ioremap(mem.start, माप(काष्ठा mpc52xx_fec));

	अगर (!priv->fec) अणु
		rv = -ENOMEM;
		जाओ err_mem_region;
	पूर्ण

	/* Bestcomm init */
	rx_fअगरo = ndev->base_addr + दुरत्व(काष्ठा mpc52xx_fec, rfअगरo_data);
	tx_fअगरo = ndev->base_addr + दुरत्व(काष्ठा mpc52xx_fec, tfअगरo_data);

	priv->rx_dmatsk = bcom_fec_rx_init(FEC_RX_NUM_BD, rx_fअगरo, FEC_RX_BUFFER_SIZE);
	priv->tx_dmatsk = bcom_fec_tx_init(FEC_TX_NUM_BD, tx_fअगरo);

	अगर (!priv->rx_dmatsk || !priv->tx_dmatsk) अणु
		pr_err("Can not init SDMA tasks\n");
		rv = -ENOMEM;
		जाओ err_rx_tx_dmatsk;
	पूर्ण

	/* Get the IRQ we need one by one */
		/* Control */
	ndev->irq = irq_of_parse_and_map(np, 0);

		/* RX */
	priv->r_irq = bcom_get_task_irq(priv->rx_dmatsk);

		/* TX */
	priv->t_irq = bcom_get_task_irq(priv->tx_dmatsk);

	/*
	 * MAC address init:
	 *
	 * First try to पढ़ो MAC address from DT
	 */
	rv = of_get_mac_address(np, ndev->dev_addr);
	अगर (rv) अणु
		काष्ठा mpc52xx_fec __iomem *fec = priv->fec;

		/*
		 * If the MAC addresse is not provided via DT then पढ़ो
		 * it back from the controller regs
		 */
		*(u32 *)(&ndev->dev_addr[0]) = in_be32(&fec->paddr1);
		*(u16 *)(&ndev->dev_addr[4]) = in_be32(&fec->paddr2) >> 16;
	पूर्ण

	/*
	 * Check अगर the MAC address is valid, अगर not get a अक्रमom one
	 */
	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		eth_hw_addr_अक्रमom(ndev);
		dev_warn(&ndev->dev, "using random MAC address %pM\n",
			 ndev->dev_addr);
	पूर्ण

	priv->msg_enable = netअगर_msg_init(debug, MPC52xx_MESSAGES_DEFAULT);

	/*
	 * Link mode configuration
	 */

	/* Start with safe शेषs क्रम link connection */
	priv->speed = 100;
	priv->duplex = DUPLEX_HALF;
	priv->mdio_speed = ((mpc5xxx_get_bus_frequency(np) >> 20) / 5) << 1;

	/* The current speed preconfigures the speed of the MII link */
	prop = of_get_property(np, "current-speed", &prop_size);
	अगर (prop && (prop_size >= माप(u32) * 2)) अणु
		priv->speed = prop[0];
		priv->duplex = prop[1] ? DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण

	/* If there is a phy handle, then get the PHY node */
	priv->phy_node = of_parse_phandle(np, "phy-handle", 0);

	/* the 7-wire property means करोn't use MII mode */
	अगर (of_find_property(np, "fsl,7-wire-mode", शून्य)) अणु
		priv->seven_wire_mode = 1;
		dev_info(&ndev->dev, "using 7-wire PHY mode\n");
	पूर्ण

	/* Hardware init */
	mpc52xx_fec_hw_init(ndev);
	mpc52xx_fec_reset_stats(ndev);

	rv = रेजिस्टर_netdev(ndev);
	अगर (rv < 0)
		जाओ err_node;

	/* We're करोne ! */
	platक्रमm_set_drvdata(op, ndev);
	netdev_info(ndev, "%pOF MAC %pM\n",
		    op->dev.of_node, ndev->dev_addr);

	वापस 0;

err_node:
	of_node_put(priv->phy_node);
	irq_dispose_mapping(ndev->irq);
err_rx_tx_dmatsk:
	अगर (priv->rx_dmatsk)
		bcom_fec_rx_release(priv->rx_dmatsk);
	अगर (priv->tx_dmatsk)
		bcom_fec_tx_release(priv->tx_dmatsk);
	iounmap(priv->fec);
err_mem_region:
	release_mem_region(mem.start, माप(काष्ठा mpc52xx_fec));
err_netdev:
	मुक्त_netdev(ndev);

	वापस rv;
पूर्ण

अटल पूर्णांक
mpc52xx_fec_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा net_device *ndev;
	काष्ठा mpc52xx_fec_priv *priv;

	ndev = platक्रमm_get_drvdata(op);
	priv = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);

	of_node_put(priv->phy_node);
	priv->phy_node = शून्य;

	irq_dispose_mapping(ndev->irq);

	bcom_fec_rx_release(priv->rx_dmatsk);
	bcom_fec_tx_release(priv->tx_dmatsk);

	iounmap(priv->fec);

	release_mem_region(ndev->base_addr, माप(काष्ठा mpc52xx_fec));

	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mpc52xx_fec_of_suspend(काष्ठा platक्रमm_device *op, pm_message_t state)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(op);

	अगर (netअगर_running(dev))
		mpc52xx_fec_बंद(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc52xx_fec_of_resume(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(op);

	mpc52xx_fec_hw_init(dev);
	mpc52xx_fec_reset_stats(dev);

	अगर (netअगर_running(dev))
		mpc52xx_fec_खोलो(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id mpc52xx_fec_match[] = अणु
	अणु .compatible = "fsl,mpc5200b-fec", पूर्ण,
	अणु .compatible = "fsl,mpc5200-fec", पूर्ण,
	अणु .compatible = "mpc5200-fec", पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, mpc52xx_fec_match);

अटल काष्ठा platक्रमm_driver mpc52xx_fec_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = mpc52xx_fec_match,
	पूर्ण,
	.probe		= mpc52xx_fec_probe,
	.हटाओ		= mpc52xx_fec_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= mpc52xx_fec_of_suspend,
	.resume		= mpc52xx_fec_of_resume,
#पूर्ण_अगर
पूर्ण;


/* ======================================================================== */
/* Module                                                                   */
/* ======================================================================== */

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
#अगर_घोषित CONFIG_FEC_MPC52xx_MDIO
	&mpc52xx_fec_mdio_driver,
#पूर्ण_अगर
	&mpc52xx_fec_driver,
पूर्ण;

अटल पूर्णांक __init
mpc52xx_fec_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

अटल व्योम __निकास
mpc52xx_fec_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण


module_init(mpc52xx_fec_init);
module_निकास(mpc52xx_fec_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dale Farnsworth");
MODULE_DESCRIPTION("Ethernet driver for the Freescale MPC52xx FEC");
