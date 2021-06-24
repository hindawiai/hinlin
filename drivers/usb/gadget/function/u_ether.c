<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * u_ether.c -- Ethernet-over-USB link layer utilities क्रम Gadget stack
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2003-2004 Robert Schwebel, Benedikt Spranger
 * Copyright (C) 2008 Nokia Corporation
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/device.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "u_ether.h"


/*
 * This component encapsulates the Ethernet link glue needed to provide
 * one (!) network link through the USB gadget stack, normally "usb0".
 *
 * The control and data models are handled by the function driver which
 * connects to this code; such as CDC Ethernet (ECM or EEM),
 * "CDC Subset", or RNDIS.  That includes all descriptor and endpoपूर्णांक
 * management.
 *
 * Link level addressing is handled by this component using module
 * parameters; अगर no such parameters are provided, अक्रमom link level
 * addresses are used.  Each end of the link uses one address.  The
 * host end address is exported in various ways, and is often recorded
 * in configuration databases.
 *
 * The driver which assembles each configuration using such a link is
 * responsible क्रम ensuring that each configuration includes at most one
 * instance of is network link.  (The network layer provides ways क्रम
 * this single "physical" link to be used by multiple भव links.)
 */

#घोषणा UETH__VERSION	"29-May-2008"

/* Experiments show that both Linux and Winकरोws hosts allow up to 16k
 * frame sizes. Set the max MTU size to 15k+52 to prevent allocating 32k
 * blocks and still have efficient handling. */
#घोषणा GETHER_MAX_MTU_SIZE 15412
#घोषणा GETHER_MAX_ETH_FRAME_LEN (GETHER_MAX_MTU_SIZE + ETH_HLEN)

काष्ठा eth_dev अणु
	/* lock is held जबतक accessing port_usb
	 */
	spinlock_t		lock;
	काष्ठा gether		*port_usb;

	काष्ठा net_device	*net;
	काष्ठा usb_gadget	*gadget;

	spinlock_t		req_lock;	/* guard अणुrx,txपूर्ण_reqs */
	काष्ठा list_head	tx_reqs, rx_reqs;
	atomic_t		tx_qlen;

	काष्ठा sk_buff_head	rx_frames;

	अचिन्हित		qmult;

	अचिन्हित		header_len;
	काष्ठा sk_buff		*(*wrap)(काष्ठा gether *, काष्ठा sk_buff *skb);
	पूर्णांक			(*unwrap)(काष्ठा gether *,
						काष्ठा sk_buff *skb,
						काष्ठा sk_buff_head *list);

	काष्ठा work_काष्ठा	work;

	अचिन्हित दीर्घ		toकरो;
#घोषणा	WORK_RX_MEMORY		0

	bool			zlp;
	bool			no_skb_reserve;
	bool			अगरname_set;
	u8			host_mac[ETH_ALEN];
	u8			dev_mac[ETH_ALEN];
पूर्ण;

/*-------------------------------------------------------------------------*/

#घोषणा RX_EXTRA	20	/* bytes guarding against rx overflows */

#घोषणा DEFAULT_QLEN	2	/* द्विगुन buffering by शेष */

/* क्रम dual-speed hardware, use deeper queues at high/super speed */
अटल अंतरभूत पूर्णांक qlen(काष्ठा usb_gadget *gadget, अचिन्हित qmult)
अणु
	अगर (gadget_is_dualspeed(gadget) && (gadget->speed == USB_SPEED_HIGH ||
					    gadget->speed >= USB_SPEED_SUPER))
		वापस qmult * DEFAULT_QLEN;
	अन्यथा
		वापस DEFAULT_QLEN;
पूर्ण

/*-------------------------------------------------------------------------*/

/* REVISIT there must be a better way than having two sets
 * of debug calls ...
 */

#अघोषित DBG
#अघोषित VDBG
#अघोषित ERROR
#अघोषित INFO

#घोषणा xprपूर्णांकk(d, level, fmt, args...) \
	prपूर्णांकk(level "%s: " fmt , (d)->net->name , ## args)

#अगर_घोषित DEBUG
#अघोषित DEBUG
#घोषणा DBG(dev, fmt, args...) \
	xprपूर्णांकk(dev , KERN_DEBUG , fmt , ## args)
#अन्यथा
#घोषणा DBG(dev, fmt, args...) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

#अगर_घोषित VERBOSE_DEBUG
#घोषणा VDBG	DBG
#अन्यथा
#घोषणा VDBG(dev, fmt, args...) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

#घोषणा ERROR(dev, fmt, args...) \
	xprपूर्णांकk(dev , KERN_ERR , fmt , ## args)
#घोषणा INFO(dev, fmt, args...) \
	xprपूर्णांकk(dev , KERN_INFO , fmt , ## args)

/*-------------------------------------------------------------------------*/

/* NETWORK DRIVER HOOKUP (to the layer above this driver) */

अटल व्योम eth_get_drvinfo(काष्ठा net_device *net, काष्ठा ethtool_drvinfo *p)
अणु
	काष्ठा eth_dev *dev = netdev_priv(net);

	strlcpy(p->driver, "g_ether", माप(p->driver));
	strlcpy(p->version, UETH__VERSION, माप(p->version));
	strlcpy(p->fw_version, dev->gadget->name, माप(p->fw_version));
	strlcpy(p->bus_info, dev_name(&dev->gadget->dev), माप(p->bus_info));
पूर्ण

/* REVISIT can also support:
 *   - WOL (by tracking suspends and issuing remote wakeup)
 *   - msglevel (implies updated messaging)
 *   - ... probably more ethtool ops
 */

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_drvinfo = eth_get_drvinfo,
	.get_link = ethtool_op_get_link,
पूर्ण;

अटल व्योम defer_kevent(काष्ठा eth_dev *dev, पूर्णांक flag)
अणु
	अगर (test_and_set_bit(flag, &dev->toकरो))
		वापस;
	अगर (!schedule_work(&dev->work))
		ERROR(dev, "kevent %d may have been dropped\n", flag);
	अन्यथा
		DBG(dev, "kevent %d scheduled\n", flag);
पूर्ण

अटल व्योम rx_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req);

अटल पूर्णांक
rx_submit(काष्ठा eth_dev *dev, काष्ठा usb_request *req, gfp_t gfp_flags)
अणु
	काष्ठा usb_gadget *g = dev->gadget;
	काष्ठा sk_buff	*skb;
	पूर्णांक		retval = -ENOMEM;
	माप_प्रकार		size = 0;
	काष्ठा usb_ep	*out;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->port_usb)
		out = dev->port_usb->out_ep;
	अन्यथा
		out = शून्य;

	अगर (!out)
	अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -ENOTCONN;
	पूर्ण

	/* Padding up to RX_EXTRA handles minor disagreements with host.
	 * Normally we use the USB "terminate on short read" convention;
	 * so allow up to (N*maxpacket), since that memory is normally
	 * alपढ़ोy allocated.  Some hardware करोesn't deal well with लघु
	 * पढ़ोs (e.g. DMA must be N*maxpacket), so क्रम now करोn't trim a
	 * byte off the end (to क्रमce hardware errors on overflow).
	 *
	 * RNDIS uses पूर्णांकernal framing, and explicitly allows senders to
	 * pad to end-of-packet.  That's potentially nice क्रम speed, but
	 * means receivers can't recover lost synch on their own (because
	 * new packets करोn't only start after a लघु RX).
	 */
	size += माप(काष्ठा ethhdr) + dev->net->mtu + RX_EXTRA;
	size += dev->port_usb->header_len;

	अगर (g->quirk_ep_out_aligned_size) अणु
		size += out->maxpacket - 1;
		size -= size % out->maxpacket;
	पूर्ण

	अगर (dev->port_usb->is_fixed)
		size = max_t(माप_प्रकार, size, dev->port_usb->fixed_out_len);
	spin_unlock_irqrestore(&dev->lock, flags);

	skb = __netdev_alloc_skb(dev->net, size + NET_IP_ALIGN, gfp_flags);
	अगर (skb == शून्य) अणु
		DBG(dev, "no rx skb\n");
		जाओ enomem;
	पूर्ण

	/* Some platक्रमms perक्रमm better when IP packets are aligned,
	 * but on at least one, checksumming fails otherwise.  Note:
	 * RNDIS headers involve variable numbers of LE32 values.
	 */
	अगर (likely(!dev->no_skb_reserve))
		skb_reserve(skb, NET_IP_ALIGN);

	req->buf = skb->data;
	req->length = size;
	req->complete = rx_complete;
	req->context = skb;

	retval = usb_ep_queue(out, req, gfp_flags);
	अगर (retval == -ENOMEM)
enomem:
		defer_kevent(dev, WORK_RX_MEMORY);
	अगर (retval) अणु
		DBG(dev, "rx submit --> %d\n", retval);
		अगर (skb)
			dev_kमुक्त_skb_any(skb);
		spin_lock_irqsave(&dev->req_lock, flags);
		list_add(&req->list, &dev->rx_reqs);
		spin_unlock_irqrestore(&dev->req_lock, flags);
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम rx_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा sk_buff	*skb = req->context, *skb2;
	काष्ठा eth_dev	*dev = ep->driver_data;
	पूर्णांक		status = req->status;

	चयन (status) अणु

	/* normal completion */
	हाल 0:
		skb_put(skb, req->actual);

		अगर (dev->unwrap) अणु
			अचिन्हित दीर्घ	flags;

			spin_lock_irqsave(&dev->lock, flags);
			अगर (dev->port_usb) अणु
				status = dev->unwrap(dev->port_usb,
							skb,
							&dev->rx_frames);
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb_any(skb);
				status = -ENOTCONN;
			पूर्ण
			spin_unlock_irqrestore(&dev->lock, flags);
		पूर्ण अन्यथा अणु
			skb_queue_tail(&dev->rx_frames, skb);
		पूर्ण
		skb = शून्य;

		skb2 = skb_dequeue(&dev->rx_frames);
		जबतक (skb2) अणु
			अगर (status < 0
					|| ETH_HLEN > skb2->len
					|| skb2->len > GETHER_MAX_ETH_FRAME_LEN) अणु
				dev->net->stats.rx_errors++;
				dev->net->stats.rx_length_errors++;
				DBG(dev, "rx length %d\n", skb2->len);
				dev_kमुक्त_skb_any(skb2);
				जाओ next_frame;
			पूर्ण
			skb2->protocol = eth_type_trans(skb2, dev->net);
			dev->net->stats.rx_packets++;
			dev->net->stats.rx_bytes += skb2->len;

			/* no buffer copies needed, unless hardware can't
			 * use skb buffers.
			 */
			status = netअगर_rx(skb2);
next_frame:
			skb2 = skb_dequeue(&dev->rx_frames);
		पूर्ण
		अवरोध;

	/* software-driven पूर्णांकerface shutकरोwn */
	हाल -ECONNRESET:		/* unlink */
	हाल -ESHUTDOWN:		/* disconnect etc */
		VDBG(dev, "rx shutdown, code %d\n", status);
		जाओ quiesce;

	/* क्रम hardware स्वतःmagic (such as pxa) */
	हाल -ECONNABORTED:		/* endpoपूर्णांक reset */
		DBG(dev, "rx %s reset\n", ep->name);
		defer_kevent(dev, WORK_RX_MEMORY);
quiesce:
		dev_kमुक्त_skb_any(skb);
		जाओ clean;

	/* data overrun */
	हाल -EOVERFLOW:
		dev->net->stats.rx_over_errors++;
		fallthrough;

	शेष:
		dev->net->stats.rx_errors++;
		DBG(dev, "rx status %d\n", status);
		अवरोध;
	पूर्ण

	अगर (skb)
		dev_kमुक्त_skb_any(skb);
	अगर (!netअगर_running(dev->net)) अणु
clean:
		spin_lock(&dev->req_lock);
		list_add(&req->list, &dev->rx_reqs);
		spin_unlock(&dev->req_lock);
		req = शून्य;
	पूर्ण
	अगर (req)
		rx_submit(dev, req, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक pपुनः_स्मृति(काष्ठा list_head *list, काष्ठा usb_ep *ep, अचिन्हित n)
अणु
	अचिन्हित		i;
	काष्ठा usb_request	*req;

	अगर (!n)
		वापस -ENOMEM;

	/* queue/recycle up to N requests */
	i = n;
	list_क्रम_each_entry(req, list, list) अणु
		अगर (i-- == 0)
			जाओ extra;
	पूर्ण
	जबतक (i--) अणु
		req = usb_ep_alloc_request(ep, GFP_ATOMIC);
		अगर (!req)
			वापस list_empty(list) ? -ENOMEM : 0;
		list_add(&req->list, list);
	पूर्ण
	वापस 0;

extra:
	/* मुक्त extras */
	क्रम (;;) अणु
		काष्ठा list_head	*next;

		next = req->list.next;
		list_del(&req->list);
		usb_ep_मुक्त_request(ep, req);

		अगर (next == list)
			अवरोध;

		req = container_of(next, काष्ठा usb_request, list);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_requests(काष्ठा eth_dev *dev, काष्ठा gether *link, अचिन्हित n)
अणु
	पूर्णांक	status;

	spin_lock(&dev->req_lock);
	status = pपुनः_स्मृति(&dev->tx_reqs, link->in_ep, n);
	अगर (status < 0)
		जाओ fail;
	status = pपुनः_स्मृति(&dev->rx_reqs, link->out_ep, n);
	अगर (status < 0)
		जाओ fail;
	जाओ करोne;
fail:
	DBG(dev, "can't alloc requests\n");
करोne:
	spin_unlock(&dev->req_lock);
	वापस status;
पूर्ण

अटल व्योम rx_fill(काष्ठा eth_dev *dev, gfp_t gfp_flags)
अणु
	काष्ठा usb_request	*req;
	अचिन्हित दीर्घ		flags;

	/* fill unused rxq slots with some skb */
	spin_lock_irqsave(&dev->req_lock, flags);
	जबतक (!list_empty(&dev->rx_reqs)) अणु
		req = list_first_entry(&dev->rx_reqs, काष्ठा usb_request, list);
		list_del_init(&req->list);
		spin_unlock_irqrestore(&dev->req_lock, flags);

		अगर (rx_submit(dev, req, gfp_flags) < 0) अणु
			defer_kevent(dev, WORK_RX_MEMORY);
			वापस;
		पूर्ण

		spin_lock_irqsave(&dev->req_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&dev->req_lock, flags);
पूर्ण

अटल व्योम eth_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा eth_dev	*dev = container_of(work, काष्ठा eth_dev, work);

	अगर (test_and_clear_bit(WORK_RX_MEMORY, &dev->toकरो)) अणु
		अगर (netअगर_running(dev->net))
			rx_fill(dev, GFP_KERNEL);
	पूर्ण

	अगर (dev->toकरो)
		DBG(dev, "work done, flags = 0x%lx\n", dev->toकरो);
पूर्ण

अटल व्योम tx_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा sk_buff	*skb = req->context;
	काष्ठा eth_dev	*dev = ep->driver_data;

	चयन (req->status) अणु
	शेष:
		dev->net->stats.tx_errors++;
		VDBG(dev, "tx err %d\n", req->status);
		fallthrough;
	हाल -ECONNRESET:		/* unlink */
	हाल -ESHUTDOWN:		/* disconnect etc */
		dev_kमुक्त_skb_any(skb);
		अवरोध;
	हाल 0:
		dev->net->stats.tx_bytes += skb->len;
		dev_consume_skb_any(skb);
	पूर्ण
	dev->net->stats.tx_packets++;

	spin_lock(&dev->req_lock);
	list_add(&req->list, &dev->tx_reqs);
	spin_unlock(&dev->req_lock);

	atomic_dec(&dev->tx_qlen);
	अगर (netअगर_carrier_ok(dev->net))
		netअगर_wake_queue(dev->net);
पूर्ण

अटल अंतरभूत पूर्णांक is_promisc(u16 cdc_filter)
अणु
	वापस cdc_filter & USB_CDC_PACKET_TYPE_PROMISCUOUS;
पूर्ण

अटल netdev_tx_t eth_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *net)
अणु
	काष्ठा eth_dev		*dev = netdev_priv(net);
	पूर्णांक			length = 0;
	पूर्णांक			retval;
	काष्ठा usb_request	*req = शून्य;
	अचिन्हित दीर्घ		flags;
	काष्ठा usb_ep		*in;
	u16			cdc_filter;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->port_usb) अणु
		in = dev->port_usb->in_ep;
		cdc_filter = dev->port_usb->cdc_filter;
	पूर्ण अन्यथा अणु
		in = शून्य;
		cdc_filter = 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (skb && !in) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* apply outgoing CDC or RNDIS filters */
	अगर (skb && !is_promisc(cdc_filter)) अणु
		u8		*dest = skb->data;

		अगर (is_multicast_ether_addr(dest)) अणु
			u16	type;

			/* ignores USB_CDC_PACKET_TYPE_MULTICAST and host
			 * SET_ETHERNET_MULTICAST_FILTERS requests
			 */
			अगर (is_broadcast_ether_addr(dest))
				type = USB_CDC_PACKET_TYPE_BROADCAST;
			अन्यथा
				type = USB_CDC_PACKET_TYPE_ALL_MULTICAST;
			अगर (!(cdc_filter & type)) अणु
				dev_kमुक्त_skb_any(skb);
				वापस NETDEV_TX_OK;
			पूर्ण
		पूर्ण
		/* ignores USB_CDC_PACKET_TYPE_सूचीECTED */
	पूर्ण

	spin_lock_irqsave(&dev->req_lock, flags);
	/*
	 * this मुक्तlist can be empty अगर an पूर्णांकerrupt triggered disconnect()
	 * and reconfigured the gadget (shutting करोwn this queue) after the
	 * network stack decided to xmit but beक्रमe we got the spinlock.
	 */
	अगर (list_empty(&dev->tx_reqs)) अणु
		spin_unlock_irqrestore(&dev->req_lock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	req = list_first_entry(&dev->tx_reqs, काष्ठा usb_request, list);
	list_del(&req->list);

	/* temporarily stop TX queue when the मुक्तlist empties */
	अगर (list_empty(&dev->tx_reqs))
		netअगर_stop_queue(net);
	spin_unlock_irqrestore(&dev->req_lock, flags);

	/* no buffer copies needed, unless the network stack did it
	 * or the hardware can't use skb buffers.
	 * or there's not enough space क्रम extra headers we need
	 */
	अगर (dev->wrap) अणु
		अचिन्हित दीर्घ	flags;

		spin_lock_irqsave(&dev->lock, flags);
		अगर (dev->port_usb)
			skb = dev->wrap(dev->port_usb, skb);
		spin_unlock_irqrestore(&dev->lock, flags);
		अगर (!skb) अणु
			/* Multi frame CDC protocols may store the frame क्रम
			 * later which is not a dropped frame.
			 */
			अगर (dev->port_usb &&
					dev->port_usb->supports_multi_frame)
				जाओ multअगरrame;
			जाओ drop;
		पूर्ण
	पूर्ण

	length = skb->len;
	req->buf = skb->data;
	req->context = skb;
	req->complete = tx_complete;

	/* NCM requires no zlp अगर transfer is dwNtbInMaxSize */
	अगर (dev->port_usb &&
	    dev->port_usb->is_fixed &&
	    length == dev->port_usb->fixed_in_len &&
	    (length % in->maxpacket) == 0)
		req->zero = 0;
	अन्यथा
		req->zero = 1;

	/* use zlp framing on tx क्रम strict CDC-Ether conक्रमmance,
	 * though any robust network rx path ignores extra padding.
	 * and some hardware करोesn't like to ग_लिखो zlps.
	 */
	अगर (req->zero && !dev->zlp && (length % in->maxpacket) == 0)
		length++;

	req->length = length;

	retval = usb_ep_queue(in, req, GFP_ATOMIC);
	चयन (retval) अणु
	शेष:
		DBG(dev, "tx queue err %d\n", retval);
		अवरोध;
	हाल 0:
		netअगर_trans_update(net);
		atomic_inc(&dev->tx_qlen);
	पूर्ण

	अगर (retval) अणु
		dev_kमुक्त_skb_any(skb);
drop:
		dev->net->stats.tx_dropped++;
multअगरrame:
		spin_lock_irqsave(&dev->req_lock, flags);
		अगर (list_empty(&dev->tx_reqs))
			netअगर_start_queue(net);
		list_add(&req->list, &dev->tx_reqs);
		spin_unlock_irqrestore(&dev->req_lock, flags);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम eth_start(काष्ठा eth_dev *dev, gfp_t gfp_flags)
अणु
	DBG(dev, "%s\n", __func__);

	/* fill the rx queue */
	rx_fill(dev, gfp_flags);

	/* and खोलो the tx floodgates */
	atomic_set(&dev->tx_qlen, 0);
	netअगर_wake_queue(dev->net);
पूर्ण

अटल पूर्णांक eth_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा eth_dev	*dev = netdev_priv(net);
	काष्ठा gether	*link;

	DBG(dev, "%s\n", __func__);
	अगर (netअगर_carrier_ok(dev->net))
		eth_start(dev, GFP_KERNEL);

	spin_lock_irq(&dev->lock);
	link = dev->port_usb;
	अगर (link && link->खोलो)
		link->खोलो(link);
	spin_unlock_irq(&dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक eth_stop(काष्ठा net_device *net)
अणु
	काष्ठा eth_dev	*dev = netdev_priv(net);
	अचिन्हित दीर्घ	flags;

	VDBG(dev, "%s\n", __func__);
	netअगर_stop_queue(net);

	DBG(dev, "stop stats: rx/tx %ld/%ld, errs %ld/%ld\n",
		dev->net->stats.rx_packets, dev->net->stats.tx_packets,
		dev->net->stats.rx_errors, dev->net->stats.tx_errors
		);

	/* ensure there are no more active requests */
	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->port_usb) अणु
		काष्ठा gether	*link = dev->port_usb;
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *in;
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *out;

		अगर (link->बंद)
			link->बंद(link);

		/* NOTE:  we have no पात-queue primitive we could use
		 * to cancel all pending I/O.  Instead, we disable then
		 * reenable the endpoपूर्णांकs ... this idiom may leave toggle
		 * wrong, but that's a self-correcting error.
		 *
		 * REVISIT:  we *COULD* just let the transfers complete at
		 * their own pace; the network stack can handle old packets.
		 * For the moment we leave this here, since it works.
		 */
		in = link->in_ep->desc;
		out = link->out_ep->desc;
		usb_ep_disable(link->in_ep);
		usb_ep_disable(link->out_ep);
		अगर (netअगर_carrier_ok(net)) अणु
			DBG(dev, "host still using in/out endpoints\n");
			link->in_ep->desc = in;
			link->out_ep->desc = out;
			usb_ep_enable(link->in_ep);
			usb_ep_enable(link->out_ep);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक get_ether_addr(स्थिर अक्षर *str, u8 *dev_addr)
अणु
	अगर (str) अणु
		अचिन्हित	i;

		क्रम (i = 0; i < 6; i++) अणु
			अचिन्हित अक्षर num;

			अगर ((*str == '.') || (*str == ':'))
				str++;
			num = hex_to_bin(*str++) << 4;
			num |= hex_to_bin(*str++);
			dev_addr [i] = num;
		पूर्ण
		अगर (is_valid_ether_addr(dev_addr))
			वापस 0;
	पूर्ण
	eth_अक्रमom_addr(dev_addr);
	वापस 1;
पूर्ण

अटल पूर्णांक get_ether_addr_str(u8 dev_addr[ETH_ALEN], अक्षर *str, पूर्णांक len)
अणु
	अगर (len < 18)
		वापस -EINVAL;

	snम_लिखो(str, len, "%pM", dev_addr);
	वापस 18;
पूर्ण

अटल स्थिर काष्ठा net_device_ops eth_netdev_ops = अणु
	.nकरो_खोलो		= eth_खोलो,
	.nकरो_stop		= eth_stop,
	.nकरो_start_xmit		= eth_start_xmit,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल काष्ठा device_type gadget_type = अणु
	.name	= "gadget",
पूर्ण;

/*
 * gether_setup_name - initialize one ethernet-over-usb link
 * @g: gadget to associated with these links
 * @ethaddr: शून्य, or a buffer in which the ethernet address of the
 *	host side of the link is recorded
 * @netname: name क्रम network device (क्रम example, "usb")
 * Context: may sleep
 *
 * This sets up the single network link that may be exported by a
 * gadget driver using this framework.  The link layer addresses are
 * set up using module parameters.
 *
 * Returns an eth_dev poपूर्णांकer on success, or an ERR_PTR on failure.
 */
काष्ठा eth_dev *gether_setup_name(काष्ठा usb_gadget *g,
		स्थिर अक्षर *dev_addr, स्थिर अक्षर *host_addr,
		u8 ethaddr[ETH_ALEN], अचिन्हित qmult, स्थिर अक्षर *netname)
अणु
	काष्ठा eth_dev		*dev;
	काष्ठा net_device	*net;
	पूर्णांक			status;

	net = alloc_etherdev(माप *dev);
	अगर (!net)
		वापस ERR_PTR(-ENOMEM);

	dev = netdev_priv(net);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->req_lock);
	INIT_WORK(&dev->work, eth_work);
	INIT_LIST_HEAD(&dev->tx_reqs);
	INIT_LIST_HEAD(&dev->rx_reqs);

	skb_queue_head_init(&dev->rx_frames);

	/* network device setup */
	dev->net = net;
	dev->qmult = qmult;
	snम_लिखो(net->name, माप(net->name), "%s%%d", netname);

	अगर (get_ether_addr(dev_addr, net->dev_addr))
		dev_warn(&g->dev,
			"using random %s ethernet address\n", "self");
	अगर (get_ether_addr(host_addr, dev->host_mac))
		dev_warn(&g->dev,
			"using random %s ethernet address\n", "host");

	अगर (ethaddr)
		स_नकल(ethaddr, dev->host_mac, ETH_ALEN);

	net->netdev_ops = &eth_netdev_ops;

	net->ethtool_ops = &ops;

	/* MTU range: 14 - 15412 */
	net->min_mtu = ETH_HLEN;
	net->max_mtu = GETHER_MAX_MTU_SIZE;

	dev->gadget = g;
	SET_NETDEV_DEV(net, &g->dev);
	SET_NETDEV_DEVTYPE(net, &gadget_type);

	status = रेजिस्टर_netdev(net);
	अगर (status < 0) अणु
		dev_dbg(&g->dev, "register_netdev failed, %d\n", status);
		मुक्त_netdev(net);
		dev = ERR_PTR(status);
	पूर्ण अन्यथा अणु
		INFO(dev, "MAC %pM\n", net->dev_addr);
		INFO(dev, "HOST MAC %pM\n", dev->host_mac);

		/*
		 * two kinds of host-initiated state changes:
		 *  - अगरf DATA transfer is active, carrier is "on"
		 *  - tx queueing enabled अगर खोलो *and* carrier is "on"
		 */
		netअगर_carrier_off(net);
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(gether_setup_name);

काष्ठा net_device *gether_setup_name_शेष(स्थिर अक्षर *netname)
अणु
	काष्ठा net_device	*net;
	काष्ठा eth_dev		*dev;

	net = alloc_etherdev(माप(*dev));
	अगर (!net)
		वापस ERR_PTR(-ENOMEM);

	dev = netdev_priv(net);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->req_lock);
	INIT_WORK(&dev->work, eth_work);
	INIT_LIST_HEAD(&dev->tx_reqs);
	INIT_LIST_HEAD(&dev->rx_reqs);

	skb_queue_head_init(&dev->rx_frames);

	/* network device setup */
	dev->net = net;
	dev->qmult = QMULT_DEFAULT;
	snम_लिखो(net->name, माप(net->name), "%s%%d", netname);

	eth_अक्रमom_addr(dev->dev_mac);
	pr_warn("using random %s ethernet address\n", "self");
	eth_अक्रमom_addr(dev->host_mac);
	pr_warn("using random %s ethernet address\n", "host");

	net->netdev_ops = &eth_netdev_ops;

	net->ethtool_ops = &ops;
	SET_NETDEV_DEVTYPE(net, &gadget_type);

	/* MTU range: 14 - 15412 */
	net->min_mtu = ETH_HLEN;
	net->max_mtu = GETHER_MAX_MTU_SIZE;

	वापस net;
पूर्ण
EXPORT_SYMBOL_GPL(gether_setup_name_शेष);

पूर्णांक gether_रेजिस्टर_netdev(काष्ठा net_device *net)
अणु
	काष्ठा eth_dev *dev;
	काष्ठा usb_gadget *g;
	काष्ठा sockaddr sa;
	पूर्णांक status;

	अगर (!net->dev.parent)
		वापस -EINVAL;
	dev = netdev_priv(net);
	g = dev->gadget;
	status = रेजिस्टर_netdev(net);
	अगर (status < 0) अणु
		dev_dbg(&g->dev, "register_netdev failed, %d\n", status);
		वापस status;
	पूर्ण अन्यथा अणु
		INFO(dev, "HOST MAC %pM\n", dev->host_mac);

		/* two kinds of host-initiated state changes:
		 *  - अगरf DATA transfer is active, carrier is "on"
		 *  - tx queueing enabled अगर खोलो *and* carrier is "on"
		 */
		netअगर_carrier_off(net);
	पूर्ण
	sa.sa_family = net->type;
	स_नकल(sa.sa_data, dev->dev_mac, ETH_ALEN);
	rtnl_lock();
	status = dev_set_mac_address(net, &sa, शून्य);
	rtnl_unlock();
	अगर (status)
		pr_warn("cannot set self ethernet address: %d\n", status);
	अन्यथा
		INFO(dev, "MAC %pM\n", dev->dev_mac);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(gether_रेजिस्टर_netdev);

व्योम gether_set_gadget(काष्ठा net_device *net, काष्ठा usb_gadget *g)
अणु
	काष्ठा eth_dev *dev;

	dev = netdev_priv(net);
	dev->gadget = g;
	SET_NETDEV_DEV(net, &g->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gether_set_gadget);

पूर्णांक gether_set_dev_addr(काष्ठा net_device *net, स्थिर अक्षर *dev_addr)
अणु
	काष्ठा eth_dev *dev;
	u8 new_addr[ETH_ALEN];

	dev = netdev_priv(net);
	अगर (get_ether_addr(dev_addr, new_addr))
		वापस -EINVAL;
	स_नकल(dev->dev_mac, new_addr, ETH_ALEN);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gether_set_dev_addr);

पूर्णांक gether_get_dev_addr(काष्ठा net_device *net, अक्षर *dev_addr, पूर्णांक len)
अणु
	काष्ठा eth_dev *dev;
	पूर्णांक ret;

	dev = netdev_priv(net);
	ret = get_ether_addr_str(dev->dev_mac, dev_addr, len);
	अगर (ret + 1 < len) अणु
		dev_addr[ret++] = '\n';
		dev_addr[ret] = '\0';
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gether_get_dev_addr);

पूर्णांक gether_set_host_addr(काष्ठा net_device *net, स्थिर अक्षर *host_addr)
अणु
	काष्ठा eth_dev *dev;
	u8 new_addr[ETH_ALEN];

	dev = netdev_priv(net);
	अगर (get_ether_addr(host_addr, new_addr))
		वापस -EINVAL;
	स_नकल(dev->host_mac, new_addr, ETH_ALEN);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gether_set_host_addr);

पूर्णांक gether_get_host_addr(काष्ठा net_device *net, अक्षर *host_addr, पूर्णांक len)
अणु
	काष्ठा eth_dev *dev;
	पूर्णांक ret;

	dev = netdev_priv(net);
	ret = get_ether_addr_str(dev->host_mac, host_addr, len);
	अगर (ret + 1 < len) अणु
		host_addr[ret++] = '\n';
		host_addr[ret] = '\0';
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gether_get_host_addr);

पूर्णांक gether_get_host_addr_cdc(काष्ठा net_device *net, अक्षर *host_addr, पूर्णांक len)
अणु
	काष्ठा eth_dev *dev;

	अगर (len < 13)
		वापस -EINVAL;

	dev = netdev_priv(net);
	snम_लिखो(host_addr, len, "%pm", dev->host_mac);

	वापस म_माप(host_addr);
पूर्ण
EXPORT_SYMBOL_GPL(gether_get_host_addr_cdc);

व्योम gether_get_host_addr_u8(काष्ठा net_device *net, u8 host_mac[ETH_ALEN])
अणु
	काष्ठा eth_dev *dev;

	dev = netdev_priv(net);
	स_नकल(host_mac, dev->host_mac, ETH_ALEN);
पूर्ण
EXPORT_SYMBOL_GPL(gether_get_host_addr_u8);

व्योम gether_set_qmult(काष्ठा net_device *net, अचिन्हित qmult)
अणु
	काष्ठा eth_dev *dev;

	dev = netdev_priv(net);
	dev->qmult = qmult;
पूर्ण
EXPORT_SYMBOL_GPL(gether_set_qmult);

अचिन्हित gether_get_qmult(काष्ठा net_device *net)
अणु
	काष्ठा eth_dev *dev;

	dev = netdev_priv(net);
	वापस dev->qmult;
पूर्ण
EXPORT_SYMBOL_GPL(gether_get_qmult);

पूर्णांक gether_get_अगरname(काष्ठा net_device *net, अक्षर *name, पूर्णांक len)
अणु
	काष्ठा eth_dev *dev = netdev_priv(net);
	पूर्णांक ret;

	rtnl_lock();
	ret = scnम_लिखो(name, len, "%s\n",
			dev->अगरname_set ? net->name : netdev_name(net));
	rtnl_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gether_get_अगरname);

पूर्णांक gether_set_अगरname(काष्ठा net_device *net, स्थिर अक्षर *name, पूर्णांक len)
अणु
	काष्ठा eth_dev *dev = netdev_priv(net);
	अक्षर पंचांगp[IFNAMSIZ];
	स्थिर अक्षर *p;

	अगर (name[len - 1] == '\n')
		len--;

	अगर (len >= माप(पंचांगp))
		वापस -E2BIG;

	strscpy(पंचांगp, name, len + 1);
	अगर (!dev_valid_name(पंचांगp))
		वापस -EINVAL;

	/* Require exactly one %d, so binding will not fail with EEXIST. */
	p = म_अक्षर(name, '%');
	अगर (!p || p[1] != 'd' || strchr(p + 2, '%'))
		वापस -EINVAL;

	म_नकलन(net->name, पंचांगp, माप(net->name));
	dev->अगरname_set = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gether_set_अगरname);

/*
 * gether_cleanup - हटाओ Ethernet-over-USB device
 * Context: may sleep
 *
 * This is called to मुक्त all resources allocated by @gether_setup().
 */
व्योम gether_cleanup(काष्ठा eth_dev *dev)
अणु
	अगर (!dev)
		वापस;

	unरेजिस्टर_netdev(dev->net);
	flush_work(&dev->work);
	मुक्त_netdev(dev->net);
पूर्ण
EXPORT_SYMBOL_GPL(gether_cleanup);

/**
 * gether_connect - notअगरy network layer that USB link is active
 * @link: the USB link, set up with endpoपूर्णांकs, descriptors matching
 *	current device speed, and any framing wrapper(s) set up.
 * Context: irqs blocked
 *
 * This is called to activate endpoपूर्णांकs and let the network layer know
 * the connection is active ("carrier detect").  It may cause the I/O
 * queues to खोलो and start letting network packets flow, but will in
 * any हाल activate the endpoपूर्णांकs so that they respond properly to the
 * USB host.
 *
 * Verअगरy net_device poपूर्णांकer वापसed using IS_ERR().  If it करोesn't
 * indicate some error code (negative त्रुटि_सं), ep->driver_data values
 * have been overwritten.
 */
काष्ठा net_device *gether_connect(काष्ठा gether *link)
अणु
	काष्ठा eth_dev		*dev = link->ioport;
	पूर्णांक			result = 0;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	link->in_ep->driver_data = dev;
	result = usb_ep_enable(link->in_ep);
	अगर (result != 0) अणु
		DBG(dev, "enable %s --> %d\n",
			link->in_ep->name, result);
		जाओ fail0;
	पूर्ण

	link->out_ep->driver_data = dev;
	result = usb_ep_enable(link->out_ep);
	अगर (result != 0) अणु
		DBG(dev, "enable %s --> %d\n",
			link->out_ep->name, result);
		जाओ fail1;
	पूर्ण

	अगर (result == 0)
		result = alloc_requests(dev, link, qlen(dev->gadget,
					dev->qmult));

	अगर (result == 0) अणु
		dev->zlp = link->is_zlp_ok;
		dev->no_skb_reserve = gadget_aव्योमs_skb_reserve(dev->gadget);
		DBG(dev, "qlen %d\n", qlen(dev->gadget, dev->qmult));

		dev->header_len = link->header_len;
		dev->unwrap = link->unwrap;
		dev->wrap = link->wrap;

		spin_lock(&dev->lock);
		dev->port_usb = link;
		अगर (netअगर_running(dev->net)) अणु
			अगर (link->खोलो)
				link->खोलो(link);
		पूर्ण अन्यथा अणु
			अगर (link->बंद)
				link->बंद(link);
		पूर्ण
		spin_unlock(&dev->lock);

		netअगर_carrier_on(dev->net);
		अगर (netअगर_running(dev->net))
			eth_start(dev, GFP_ATOMIC);

	/* on error, disable any endpoपूर्णांकs  */
	पूर्ण अन्यथा अणु
		(व्योम) usb_ep_disable(link->out_ep);
fail1:
		(व्योम) usb_ep_disable(link->in_ep);
	पूर्ण
fail0:
	/* caller is responsible क्रम cleanup on error */
	अगर (result < 0)
		वापस ERR_PTR(result);
	वापस dev->net;
पूर्ण
EXPORT_SYMBOL_GPL(gether_connect);

/**
 * gether_disconnect - notअगरy network layer that USB link is inactive
 * @link: the USB link, on which gether_connect() was called
 * Context: irqs blocked
 *
 * This is called to deactivate endpoपूर्णांकs and let the network layer know
 * the connection went inactive ("no carrier").
 *
 * On वापस, the state is as अगर gether_connect() had never been called.
 * The endpoपूर्णांकs are inactive, and accordingly without active USB I/O.
 * Poपूर्णांकers to endpoपूर्णांक descriptors and endpoपूर्णांक निजी data are nulled.
 */
व्योम gether_disconnect(काष्ठा gether *link)
अणु
	काष्ठा eth_dev		*dev = link->ioport;
	काष्ठा usb_request	*req;

	WARN_ON(!dev);
	अगर (!dev)
		वापस;

	DBG(dev, "%s\n", __func__);

	netअगर_stop_queue(dev->net);
	netअगर_carrier_off(dev->net);

	/* disable endpoपूर्णांकs, क्रमcing (synchronous) completion
	 * of all pending i/o.  then मुक्त the request objects
	 * and क्रमget about the endpoपूर्णांकs.
	 */
	usb_ep_disable(link->in_ep);
	spin_lock(&dev->req_lock);
	जबतक (!list_empty(&dev->tx_reqs)) अणु
		req = list_first_entry(&dev->tx_reqs, काष्ठा usb_request, list);
		list_del(&req->list);

		spin_unlock(&dev->req_lock);
		usb_ep_मुक्त_request(link->in_ep, req);
		spin_lock(&dev->req_lock);
	पूर्ण
	spin_unlock(&dev->req_lock);
	link->in_ep->desc = शून्य;

	usb_ep_disable(link->out_ep);
	spin_lock(&dev->req_lock);
	जबतक (!list_empty(&dev->rx_reqs)) अणु
		req = list_first_entry(&dev->rx_reqs, काष्ठा usb_request, list);
		list_del(&req->list);

		spin_unlock(&dev->req_lock);
		usb_ep_मुक्त_request(link->out_ep, req);
		spin_lock(&dev->req_lock);
	पूर्ण
	spin_unlock(&dev->req_lock);
	link->out_ep->desc = शून्य;

	/* finish क्रमgetting about this USB link episode */
	dev->header_len = 0;
	dev->unwrap = शून्य;
	dev->wrap = शून्य;

	spin_lock(&dev->lock);
	dev->port_usb = शून्य;
	spin_unlock(&dev->lock);
पूर्ण
EXPORT_SYMBOL_GPL(gether_disconnect);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Brownell");
