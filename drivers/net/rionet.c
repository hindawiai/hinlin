<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rionet - Ethernet driver over RapidIO messaging services
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/slab.h>
#समावेश <linux/rio_ids.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/reboot.h>

#घोषणा DRV_NAME        "rionet"
#घोषणा DRV_VERSION     "0.3"
#घोषणा DRV_AUTHOR      "Matt Porter <mporter@kernel.crashing.org>"
#घोषणा DRV_DESC        "Ethernet over RapidIO"

MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESC);
MODULE_LICENSE("GPL");

#घोषणा RIONET_DEFAULT_MSGLEVEL \
			(NETIF_MSG_DRV          | \
			 NETIF_MSG_LINK         | \
			 NETIF_MSG_RX_ERR       | \
			 NETIF_MSG_TX_ERR)

#घोषणा RIONET_DOORBELL_JOIN	0x1000
#घोषणा RIONET_DOORBELL_LEAVE	0x1001

#घोषणा RIONET_MAILBOX		0

#घोषणा RIONET_TX_RING_SIZE	CONFIG_RIONET_TX_SIZE
#घोषणा RIONET_RX_RING_SIZE	CONFIG_RIONET_RX_SIZE
#घोषणा RIONET_MAX_NETS		8
#घोषणा RIONET_MSG_SIZE         RIO_MAX_MSG_SIZE
#घोषणा RIONET_MAX_MTU          (RIONET_MSG_SIZE - ETH_HLEN)

काष्ठा rionet_निजी अणु
	काष्ठा rio_mport *mport;
	काष्ठा sk_buff *rx_skb[RIONET_RX_RING_SIZE];
	काष्ठा sk_buff *tx_skb[RIONET_TX_RING_SIZE];
	पूर्णांक rx_slot;
	पूर्णांक tx_slot;
	पूर्णांक tx_cnt;
	पूर्णांक ack_slot;
	spinlock_t lock;
	spinlock_t tx_lock;
	u32 msg_enable;
	bool खोलो;
पूर्ण;

काष्ठा rionet_peer अणु
	काष्ठा list_head node;
	काष्ठा rio_dev *rdev;
	काष्ठा resource *res;
पूर्ण;

काष्ठा rionet_net अणु
	काष्ठा net_device *ndev;
	काष्ठा list_head peers;
	spinlock_t lock;	/* net info access lock */
	काष्ठा rio_dev **active;
	पूर्णांक nact;	/* number of active peers */
पूर्ण;

अटल काष्ठा rionet_net nets[RIONET_MAX_NETS];

#घोषणा is_rionet_capable(src_ops, dst_ops)			\
			((src_ops & RIO_SRC_OPS_DATA_MSG) &&	\
			 (dst_ops & RIO_DST_OPS_DATA_MSG) &&	\
			 (src_ops & RIO_SRC_OPS_DOORBELL) &&	\
			 (dst_ops & RIO_DST_OPS_DOORBELL))
#घोषणा dev_rionet_capable(dev) \
	is_rionet_capable(dev->src_ops, dev->dst_ops)

#घोषणा RIONET_MAC_MATCH(x)	(!स_भेद((x), "\00\01\00\01", 4))
#घोषणा RIONET_GET_DESTID(x)	((*((u8 *)x + 4) << 8) | *((u8 *)x + 5))

अटल पूर्णांक rionet_rx_clean(काष्ठा net_device *ndev)
अणु
	पूर्णांक i;
	पूर्णांक error = 0;
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);
	व्योम *data;

	i = rnet->rx_slot;

	करो अणु
		अगर (!rnet->rx_skb[i])
			जारी;

		अगर (!(data = rio_get_inb_message(rnet->mport, RIONET_MAILBOX)))
			अवरोध;

		rnet->rx_skb[i]->data = data;
		skb_put(rnet->rx_skb[i], RIO_MAX_MSG_SIZE);
		rnet->rx_skb[i]->protocol =
		    eth_type_trans(rnet->rx_skb[i], ndev);
		error = netअगर_rx(rnet->rx_skb[i]);

		अगर (error == NET_RX_DROP) अणु
			ndev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += RIO_MAX_MSG_SIZE;
		पूर्ण

	पूर्ण जबतक ((i = (i + 1) % RIONET_RX_RING_SIZE) != rnet->rx_slot);

	वापस i;
पूर्ण

अटल व्योम rionet_rx_fill(काष्ठा net_device *ndev, पूर्णांक end)
अणु
	पूर्णांक i;
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);

	i = rnet->rx_slot;
	करो अणु
		rnet->rx_skb[i] = dev_alloc_skb(RIO_MAX_MSG_SIZE);

		अगर (!rnet->rx_skb[i])
			अवरोध;

		rio_add_inb_buffer(rnet->mport, RIONET_MAILBOX,
				   rnet->rx_skb[i]->data);
	पूर्ण जबतक ((i = (i + 1) % RIONET_RX_RING_SIZE) != end);

	rnet->rx_slot = i;
पूर्ण

अटल पूर्णांक rionet_queue_tx_msg(काष्ठा sk_buff *skb, काष्ठा net_device *ndev,
			       काष्ठा rio_dev *rdev)
अणु
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);

	rio_add_outb_message(rnet->mport, rdev, 0, skb->data, skb->len);
	rnet->tx_skb[rnet->tx_slot] = skb;

	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += skb->len;

	अगर (++rnet->tx_cnt == RIONET_TX_RING_SIZE)
		netअगर_stop_queue(ndev);

	++rnet->tx_slot;
	rnet->tx_slot &= (RIONET_TX_RING_SIZE - 1);

	अगर (netअगर_msg_tx_queued(rnet))
		prपूर्णांकk(KERN_INFO "%s: queued skb len %8.8x\n", DRV_NAME,
		       skb->len);

	वापस 0;
पूर्ण

अटल netdev_tx_t rionet_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *ndev)
अणु
	पूर्णांक i;
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb->data;
	u16 destid;
	अचिन्हित दीर्घ flags;
	पूर्णांक add_num = 1;

	spin_lock_irqsave(&rnet->tx_lock, flags);

	अगर (is_multicast_ether_addr(eth->h_dest))
		add_num = nets[rnet->mport->id].nact;

	अगर ((rnet->tx_cnt + add_num) > RIONET_TX_RING_SIZE) अणु
		netअगर_stop_queue(ndev);
		spin_unlock_irqrestore(&rnet->tx_lock, flags);
		prपूर्णांकk(KERN_ERR "%s: BUG! Tx Ring full when queue awake!\n",
		       ndev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (is_multicast_ether_addr(eth->h_dest)) अणु
		पूर्णांक count = 0;

		क्रम (i = 0; i < RIO_MAX_ROUTE_ENTRIES(rnet->mport->sys_size);
				i++)
			अगर (nets[rnet->mport->id].active[i]) अणु
				rionet_queue_tx_msg(skb, ndev,
					nets[rnet->mport->id].active[i]);
				अगर (count)
					refcount_inc(&skb->users);
				count++;
			पूर्ण
	पूर्ण अन्यथा अगर (RIONET_MAC_MATCH(eth->h_dest)) अणु
		destid = RIONET_GET_DESTID(eth->h_dest);
		अगर (nets[rnet->mport->id].active[destid])
			rionet_queue_tx_msg(skb, ndev,
					nets[rnet->mport->id].active[destid]);
		अन्यथा अणु
			/*
			 * If the target device was हटाओd from the list of
			 * active peers but we still have TX packets targeting
			 * it just report sending a packet to the target
			 * (without actual packet transfer).
			 */
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += skb->len;
			dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&rnet->tx_lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम rionet_dbell_event(काष्ठा rio_mport *mport, व्योम *dev_id, u16 sid, u16 tid,
			       u16 info)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);
	काष्ठा rionet_peer *peer;
	अचिन्हित अक्षर netid = rnet->mport->id;

	अगर (netअगर_msg_पूर्णांकr(rnet))
		prपूर्णांकk(KERN_INFO "%s: doorbell sid %4.4x tid %4.4x info %4.4x",
		       DRV_NAME, sid, tid, info);
	अगर (info == RIONET_DOORBELL_JOIN) अणु
		अगर (!nets[netid].active[sid]) अणु
			spin_lock(&nets[netid].lock);
			list_क्रम_each_entry(peer, &nets[netid].peers, node) अणु
				अगर (peer->rdev->destid == sid) अणु
					nets[netid].active[sid] = peer->rdev;
					nets[netid].nact++;
				पूर्ण
			पूर्ण
			spin_unlock(&nets[netid].lock);

			rio_mport_send_करोorbell(mport, sid,
						RIONET_DOORBELL_JOIN);
		पूर्ण
	पूर्ण अन्यथा अगर (info == RIONET_DOORBELL_LEAVE) अणु
		spin_lock(&nets[netid].lock);
		अगर (nets[netid].active[sid]) अणु
			nets[netid].active[sid] = शून्य;
			nets[netid].nact--;
		पूर्ण
		spin_unlock(&nets[netid].lock);
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_पूर्णांकr(rnet))
			prपूर्णांकk(KERN_WARNING "%s: unhandled doorbell\n",
			       DRV_NAME);
	पूर्ण
पूर्ण

अटल व्योम rionet_inb_msg_event(काष्ठा rio_mport *mport, व्योम *dev_id, पूर्णांक mbox, पूर्णांक slot)
अणु
	पूर्णांक n;
	काष्ठा net_device *ndev = dev_id;
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);

	अगर (netअगर_msg_पूर्णांकr(rnet))
		prपूर्णांकk(KERN_INFO "%s: inbound message event, mbox %d slot %d\n",
		       DRV_NAME, mbox, slot);

	spin_lock(&rnet->lock);
	अगर ((n = rionet_rx_clean(ndev)) != rnet->rx_slot)
		rionet_rx_fill(ndev, n);
	spin_unlock(&rnet->lock);
पूर्ण

अटल व्योम rionet_outb_msg_event(काष्ठा rio_mport *mport, व्योम *dev_id, पूर्णांक mbox, पूर्णांक slot)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);

	spin_lock(&rnet->tx_lock);

	अगर (netअगर_msg_पूर्णांकr(rnet))
		prपूर्णांकk(KERN_INFO
		       "%s: outbound message event, mbox %d slot %d\n",
		       DRV_NAME, mbox, slot);

	जबतक (rnet->tx_cnt && (rnet->ack_slot != slot)) अणु
		/* dma unmap single */
		dev_kमुक्त_skb_irq(rnet->tx_skb[rnet->ack_slot]);
		rnet->tx_skb[rnet->ack_slot] = शून्य;
		++rnet->ack_slot;
		rnet->ack_slot &= (RIONET_TX_RING_SIZE - 1);
		rnet->tx_cnt--;
	पूर्ण

	अगर (rnet->tx_cnt < RIONET_TX_RING_SIZE)
		netअगर_wake_queue(ndev);

	spin_unlock(&rnet->tx_lock);
पूर्ण

अटल पूर्णांक rionet_खोलो(काष्ठा net_device *ndev)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा rionet_peer *peer;
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);
	अचिन्हित अक्षर netid = rnet->mport->id;
	अचिन्हित दीर्घ flags;

	अगर (netअगर_msg_अगरup(rnet))
		prपूर्णांकk(KERN_INFO "%s: open\n", DRV_NAME);

	अगर ((rc = rio_request_inb_dbell(rnet->mport,
					(व्योम *)ndev,
					RIONET_DOORBELL_JOIN,
					RIONET_DOORBELL_LEAVE,
					rionet_dbell_event)) < 0)
		जाओ out;

	अगर ((rc = rio_request_inb_mbox(rnet->mport,
				       (व्योम *)ndev,
				       RIONET_MAILBOX,
				       RIONET_RX_RING_SIZE,
				       rionet_inb_msg_event)) < 0)
		जाओ out;

	अगर ((rc = rio_request_outb_mbox(rnet->mport,
					(व्योम *)ndev,
					RIONET_MAILBOX,
					RIONET_TX_RING_SIZE,
					rionet_outb_msg_event)) < 0)
		जाओ out;

	/* Initialize inbound message ring */
	क्रम (i = 0; i < RIONET_RX_RING_SIZE; i++)
		rnet->rx_skb[i] = शून्य;
	rnet->rx_slot = 0;
	rionet_rx_fill(ndev, 0);

	rnet->tx_slot = 0;
	rnet->tx_cnt = 0;
	rnet->ack_slot = 0;

	netअगर_carrier_on(ndev);
	netअगर_start_queue(ndev);

	spin_lock_irqsave(&nets[netid].lock, flags);
	list_क्रम_each_entry(peer, &nets[netid].peers, node) अणु
		/* Send a join message */
		rio_send_करोorbell(peer->rdev, RIONET_DOORBELL_JOIN);
	पूर्ण
	spin_unlock_irqrestore(&nets[netid].lock, flags);
	rnet->खोलो = true;

      out:
	वापस rc;
पूर्ण

अटल पूर्णांक rionet_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);
	काष्ठा rionet_peer *peer;
	अचिन्हित अक्षर netid = rnet->mport->id;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (netअगर_msg_अगरup(rnet))
		prपूर्णांकk(KERN_INFO "%s: close %s\n", DRV_NAME, ndev->name);

	netअगर_stop_queue(ndev);
	netअगर_carrier_off(ndev);
	rnet->खोलो = false;

	क्रम (i = 0; i < RIONET_RX_RING_SIZE; i++)
		kमुक्त_skb(rnet->rx_skb[i]);

	spin_lock_irqsave(&nets[netid].lock, flags);
	list_क्रम_each_entry(peer, &nets[netid].peers, node) अणु
		अगर (nets[netid].active[peer->rdev->destid]) अणु
			rio_send_करोorbell(peer->rdev, RIONET_DOORBELL_LEAVE);
			nets[netid].active[peer->rdev->destid] = शून्य;
		पूर्ण
		अगर (peer->res)
			rio_release_outb_dbell(peer->rdev, peer->res);
	पूर्ण
	spin_unlock_irqrestore(&nets[netid].lock, flags);

	rio_release_inb_dbell(rnet->mport, RIONET_DOORBELL_JOIN,
			      RIONET_DOORBELL_LEAVE);
	rio_release_inb_mbox(rnet->mport, RIONET_MAILBOX);
	rio_release_outb_mbox(rnet->mport, RIONET_MAILBOX);

	वापस 0;
पूर्ण

अटल व्योम rionet_हटाओ_dev(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	अचिन्हित अक्षर netid = rdev->net->hport->id;
	काष्ठा rionet_peer *peer;
	पूर्णांक state, found = 0;
	अचिन्हित दीर्घ flags;

	अगर (!dev_rionet_capable(rdev))
		वापस;

	spin_lock_irqsave(&nets[netid].lock, flags);
	list_क्रम_each_entry(peer, &nets[netid].peers, node) अणु
		अगर (peer->rdev == rdev) अणु
			list_del(&peer->node);
			अगर (nets[netid].active[rdev->destid]) अणु
				state = atomic_पढ़ो(&rdev->state);
				अगर (state != RIO_DEVICE_GONE &&
				    state != RIO_DEVICE_INITIALIZING) अणु
					rio_send_करोorbell(rdev,
							RIONET_DOORBELL_LEAVE);
				पूर्ण
				nets[netid].active[rdev->destid] = शून्य;
				nets[netid].nact--;
			पूर्ण
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&nets[netid].lock, flags);

	अगर (found) अणु
		अगर (peer->res)
			rio_release_outb_dbell(rdev, peer->res);
		kमुक्त(peer);
	पूर्ण
पूर्ण

अटल व्योम rionet_get_drvinfo(काष्ठा net_device *ndev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->fw_version, "n/a", माप(info->fw_version));
	strlcpy(info->bus_info, rnet->mport->name, माप(info->bus_info));
पूर्ण

अटल u32 rionet_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);

	वापस rnet->msg_enable;
पूर्ण

अटल व्योम rionet_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा rionet_निजी *rnet = netdev_priv(ndev);

	rnet->msg_enable = value;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops rionet_ethtool_ops = अणु
	.get_drvinfo = rionet_get_drvinfo,
	.get_msglevel = rionet_get_msglevel,
	.set_msglevel = rionet_set_msglevel,
	.get_link = ethtool_op_get_link,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops rionet_netdev_ops = अणु
	.nकरो_खोलो		= rionet_खोलो,
	.nकरो_stop		= rionet_बंद,
	.nकरो_start_xmit		= rionet_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक rionet_setup_netdev(काष्ठा rio_mport *mport, काष्ठा net_device *ndev)
अणु
	पूर्णांक rc = 0;
	काष्ठा rionet_निजी *rnet;
	u16 device_id;
	स्थिर माप_प्रकार rionet_active_bytes = माप(व्योम *) *
				RIO_MAX_ROUTE_ENTRIES(mport->sys_size);

	nets[mport->id].active = (काष्ठा rio_dev **)__get_मुक्त_pages(GFP_KERNEL,
						get_order(rionet_active_bytes));
	अगर (!nets[mport->id].active) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	स_रखो((व्योम *)nets[mport->id].active, 0, rionet_active_bytes);

	/* Set up निजी area */
	rnet = netdev_priv(ndev);
	rnet->mport = mport;
	rnet->खोलो = false;

	/* Set the शेष MAC address */
	device_id = rio_local_get_device_id(mport);
	ndev->dev_addr[0] = 0x00;
	ndev->dev_addr[1] = 0x01;
	ndev->dev_addr[2] = 0x00;
	ndev->dev_addr[3] = 0x01;
	ndev->dev_addr[4] = device_id >> 8;
	ndev->dev_addr[5] = device_id & 0xff;

	ndev->netdev_ops = &rionet_netdev_ops;
	ndev->mtu = RIONET_MAX_MTU;
	/* MTU range: 68 - 4082 */
	ndev->min_mtu = ETH_MIN_MTU;
	ndev->max_mtu = RIONET_MAX_MTU;
	ndev->features = NETIF_F_LLTX;
	SET_NETDEV_DEV(ndev, &mport->dev);
	ndev->ethtool_ops = &rionet_ethtool_ops;

	spin_lock_init(&rnet->lock);
	spin_lock_init(&rnet->tx_lock);

	rnet->msg_enable = RIONET_DEFAULT_MSGLEVEL;

	rc = रेजिस्टर_netdev(ndev);
	अगर (rc != 0) अणु
		मुक्त_pages((अचिन्हित दीर्घ)nets[mport->id].active,
			   get_order(rionet_active_bytes));
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: %s %s Version %s, MAC %pM, %s\n",
	       ndev->name,
	       DRV_NAME,
	       DRV_DESC,
	       DRV_VERSION,
	       ndev->dev_addr,
	       mport->name);

      out:
	वापस rc;
पूर्ण

अटल पूर्णांक rionet_add_dev(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	पूर्णांक rc = -ENODEV;
	u32 lsrc_ops, ldst_ops;
	काष्ठा rionet_peer *peer;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	अचिन्हित अक्षर netid = rdev->net->hport->id;

	अगर (netid >= RIONET_MAX_NETS)
		वापस rc;

	/*
	 * If first समय through this net, make sure local device is rionet
	 * capable and setup netdev (this step will be skipped in later probes
	 * on the same net).
	 */
	अगर (!nets[netid].ndev) अणु
		rio_local_पढ़ो_config_32(rdev->net->hport, RIO_SRC_OPS_CAR,
					 &lsrc_ops);
		rio_local_पढ़ो_config_32(rdev->net->hport, RIO_DST_OPS_CAR,
					 &ldst_ops);
		अगर (!is_rionet_capable(lsrc_ops, ldst_ops)) अणु
			prपूर्णांकk(KERN_ERR
			       "%s: local device %s is not network capable\n",
			       DRV_NAME, rdev->net->hport->name);
			जाओ out;
		पूर्ण

		/* Allocate our net_device काष्ठाure */
		ndev = alloc_etherdev(माप(काष्ठा rionet_निजी));
		अगर (ndev == शून्य) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		rc = rionet_setup_netdev(rdev->net->hport, ndev);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: failed to setup netdev (rc=%d)\n",
			       DRV_NAME, rc);
			मुक्त_netdev(ndev);
			जाओ out;
		पूर्ण

		INIT_LIST_HEAD(&nets[netid].peers);
		spin_lock_init(&nets[netid].lock);
		nets[netid].nact = 0;
		nets[netid].ndev = ndev;
	पूर्ण

	/*
	 * If the remote device has mailbox/करोorbell capabilities,
	 * add it to the peer list.
	 */
	अगर (dev_rionet_capable(rdev)) अणु
		काष्ठा rionet_निजी *rnet;
		अचिन्हित दीर्घ flags;

		rnet = netdev_priv(nets[netid].ndev);

		peer = kzalloc(माप(*peer), GFP_KERNEL);
		अगर (!peer) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		peer->rdev = rdev;
		peer->res = rio_request_outb_dbell(peer->rdev,
						RIONET_DOORBELL_JOIN,
						RIONET_DOORBELL_LEAVE);
		अगर (!peer->res) अणु
			pr_err("%s: error requesting doorbells\n", DRV_NAME);
			kमुक्त(peer);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		spin_lock_irqsave(&nets[netid].lock, flags);
		list_add_tail(&peer->node, &nets[netid].peers);
		spin_unlock_irqrestore(&nets[netid].lock, flags);
		pr_debug("%s: %s add peer %s\n",
			 DRV_NAME, __func__, rio_name(rdev));

		/* If netdev is alपढ़ोy खोलोed, send join request to new peer */
		अगर (rnet->खोलो)
			rio_send_करोorbell(peer->rdev, RIONET_DOORBELL_JOIN);
	पूर्ण

	वापस 0;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक rionet_shutकरोwn(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ code,
			   व्योम *unused)
अणु
	काष्ठा rionet_peer *peer;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	pr_debug("%s: %s\n", DRV_NAME, __func__);

	क्रम (i = 0; i < RIONET_MAX_NETS; i++) अणु
		अगर (!nets[i].ndev)
			जारी;

		spin_lock_irqsave(&nets[i].lock, flags);
		list_क्रम_each_entry(peer, &nets[i].peers, node) अणु
			अगर (nets[i].active[peer->rdev->destid]) अणु
				rio_send_करोorbell(peer->rdev,
						  RIONET_DOORBELL_LEAVE);
				nets[i].active[peer->rdev->destid] = शून्य;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&nets[i].lock, flags);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम rionet_हटाओ_mport(काष्ठा device *dev,
				काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा rio_mport *mport = to_rio_mport(dev);
	काष्ठा net_device *ndev;
	पूर्णांक id = mport->id;

	pr_debug("%s %s\n", __func__, mport->name);

	WARN(nets[id].nact, "%s called when connected to %d peers\n",
	     __func__, nets[id].nact);
	WARN(!nets[id].ndev, "%s called for mport without NDEV\n",
	     __func__);

	अगर (nets[id].ndev) अणु
		ndev = nets[id].ndev;
		netअगर_stop_queue(ndev);
		unरेजिस्टर_netdev(ndev);

		मुक्त_pages((अचिन्हित दीर्घ)nets[id].active,
			   get_order(माप(व्योम *) *
			   RIO_MAX_ROUTE_ENTRIES(mport->sys_size)));
		nets[id].active = शून्य;
		मुक्त_netdev(ndev);
		nets[id].ndev = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित MODULE
अटल काष्ठा rio_device_id rionet_id_table[] = अणु
	अणुRIO_DEVICE(RIO_ANY_ID, RIO_ANY_ID)पूर्ण,
	अणु 0, पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(rapidio, rionet_id_table);
#पूर्ण_अगर

अटल काष्ठा subsys_पूर्णांकerface rionet_पूर्णांकerface = अणु
	.name		= "rionet",
	.subsys		= &rio_bus_type,
	.add_dev	= rionet_add_dev,
	.हटाओ_dev	= rionet_हटाओ_dev,
पूर्ण;

अटल काष्ठा notअगरier_block rionet_notअगरier = अणु
	.notअगरier_call = rionet_shutकरोwn,
पूर्ण;

/* the rio_mport_पूर्णांकerface is used to handle local mport devices */
अटल काष्ठा class_पूर्णांकerface rio_mport_पूर्णांकerface __refdata = अणु
	.class = &rio_mport_class,
	.add_dev = शून्य,
	.हटाओ_dev = rionet_हटाओ_mport,
पूर्ण;

अटल पूर्णांक __init rionet_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_reboot_notअगरier(&rionet_notअगरier);
	अगर (ret) अणु
		pr_err("%s: failed to register reboot notifier (err=%d)\n",
		       DRV_NAME, ret);
		वापस ret;
	पूर्ण

	ret = class_पूर्णांकerface_रेजिस्टर(&rio_mport_पूर्णांकerface);
	अगर (ret) अणु
		pr_err("%s: class_interface_register error: %d\n",
		       DRV_NAME, ret);
		वापस ret;
	पूर्ण

	वापस subsys_पूर्णांकerface_रेजिस्टर(&rionet_पूर्णांकerface);
पूर्ण

अटल व्योम __निकास rionet_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&rionet_notअगरier);
	subsys_पूर्णांकerface_unरेजिस्टर(&rionet_पूर्णांकerface);
	class_पूर्णांकerface_unरेजिस्टर(&rio_mport_पूर्णांकerface);
पूर्ण

late_initcall(rionet_init);
module_निकास(rionet_निकास);
