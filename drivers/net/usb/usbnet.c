<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB Network driver infraकाष्ठाure
 * Copyright (C) 2000-2005 by David Brownell
 * Copyright (C) 2003-2005 David Hollis <dhollis@davehollis.com>
 */

/*
 * This is a generic "USB networking" framework that works with several
 * kinds of full and high speed networking devices:  host-to-host cables,
 * smart usb peripherals, and actual Ethernet adapters.
 *
 * These devices usually dअगरfer in terms of control protocols (अगर they
 * even have one!) and someबार they define new framing to wrap or batch
 * Ethernet packets.  Otherwise, they talk to USB pretty much the same,
 * so पूर्णांकerface (un)binding, endpoपूर्णांक I/O queues, fault handling, and other
 * issues can usefully be addressed by this framework.
 */

// #घोषणा	DEBUG			// error path messages, extra info
// #घोषणा	VERBOSE			// more; success messages

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_runसमय.स>

/*-------------------------------------------------------------------------*/

/*
 * Nineteen USB 1.1 max size bulk transactions per frame (ms), max.
 * Several करोzen bytes of IPv4 data can fit in two such transactions.
 * One maximum size Ethernet packet takes twenty four of them.
 * For high speed, each frame comक्रमtably fits almost 36 max size
 * Ethernet packets (so queues should be bigger).
 *
 * The goal is to let the USB host controller be busy क्रम 5msec or
 * more beक्रमe an irq is required, under load.  Jumbograms change
 * the equation.
 */
#घोषणा	MAX_QUEUE_MEMORY	(60 * 1518)
#घोषणा	RX_QLEN(dev)		((dev)->rx_qlen)
#घोषणा	TX_QLEN(dev)		((dev)->tx_qlen)

// reawaken network queue this soon after stopping; अन्यथा watchकरोg barks
#घोषणा TX_TIMEOUT_JIFFIES	(5*HZ)

/* throttle rx/tx briefly after some faults, so hub_wq might disconnect()
 * us (it polls at HZ/4 usually) beक्रमe we report too many false errors.
 */
#घोषणा THROTTLE_JIFFIES	(HZ/8)

// between wakeups
#घोषणा UNLINK_TIMEOUT_MS	3

/*-------------------------------------------------------------------------*/

// अक्रमomly generated ethernet address
अटल u8	node_id [ETH_ALEN];

/* use ethtool to change the level क्रम any given device */
अटल पूर्णांक msg_level = -1;
module_param (msg_level, पूर्णांक, 0);
MODULE_PARM_DESC (msg_level, "Override default message level");

/*-------------------------------------------------------------------------*/

/* handles CDC Ethernet and many other network "bulk data" पूर्णांकerfaces */
पूर्णांक usbnet_get_endpoपूर्णांकs(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक				पंचांगp;
	काष्ठा usb_host_पूर्णांकerface	*alt = शून्य;
	काष्ठा usb_host_endpoपूर्णांक	*in = शून्य, *out = शून्य;
	काष्ठा usb_host_endpoपूर्णांक	*status = शून्य;

	क्रम (पंचांगp = 0; पंचांगp < पूर्णांकf->num_altsetting; पंचांगp++) अणु
		अचिन्हित	ep;

		in = out = status = शून्य;
		alt = पूर्णांकf->altsetting + पंचांगp;

		/* take the first altsetting with in-bulk + out-bulk;
		 * remember any status endpoपूर्णांक, just in हाल;
		 * ignore other endpoपूर्णांकs and altsettings.
		 */
		क्रम (ep = 0; ep < alt->desc.bNumEndpoपूर्णांकs; ep++) अणु
			काष्ठा usb_host_endpoपूर्णांक	*e;
			पूर्णांक				पूर्णांकr = 0;

			e = alt->endpoपूर्णांक + ep;

			/* ignore endpoपूर्णांकs which cannot transfer data */
			अगर (!usb_endpoपूर्णांक_maxp(&e->desc))
				जारी;

			चयन (e->desc.bmAttributes) अणु
			हाल USB_ENDPOINT_XFER_INT:
				अगर (!usb_endpoपूर्णांक_dir_in(&e->desc))
					जारी;
				पूर्णांकr = 1;
				fallthrough;
			हाल USB_ENDPOINT_XFER_BULK:
				अवरोध;
			शेष:
				जारी;
			पूर्ण
			अगर (usb_endpoपूर्णांक_dir_in(&e->desc)) अणु
				अगर (!पूर्णांकr && !in)
					in = e;
				अन्यथा अगर (पूर्णांकr && !status)
					status = e;
			पूर्ण अन्यथा अणु
				अगर (!out)
					out = e;
			पूर्ण
		पूर्ण
		अगर (in && out)
			अवरोध;
	पूर्ण
	अगर (!alt || !in || !out)
		वापस -EINVAL;

	अगर (alt->desc.bAlternateSetting != 0 ||
	    !(dev->driver_info->flags & FLAG_NO_SETINT)) अणु
		पंचांगp = usb_set_पूर्णांकerface (dev->udev, alt->desc.bInterfaceNumber,
				alt->desc.bAlternateSetting);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
	पूर्ण

	dev->in = usb_rcvbulkpipe (dev->udev,
			in->desc.bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK);
	dev->out = usb_sndbulkpipe (dev->udev,
			out->desc.bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK);
	dev->status = status;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_get_endpoपूर्णांकs);

पूर्णांक usbnet_get_ethernet_addr(काष्ठा usbnet *dev, पूर्णांक iMACAddress)
अणु
	पूर्णांक 		पंचांगp = -1, ret;
	अचिन्हित अक्षर	buf [13];

	ret = usb_string(dev->udev, iMACAddress, buf, माप buf);
	अगर (ret == 12)
		पंचांगp = hex2bin(dev->net->dev_addr, buf, 6);
	अगर (पंचांगp < 0) अणु
		dev_dbg(&dev->udev->dev,
			"bad MAC string %d fetch, %d\n", iMACAddress, पंचांगp);
		अगर (ret >= 0)
			ret = -EINVAL;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_get_ethernet_addr);

अटल व्योम पूर्णांकr_complete (काष्ठा urb *urb)
अणु
	काष्ठा usbnet	*dev = urb->context;
	पूर्णांक		status = urb->status;

	चयन (status) अणु
	/* success */
	हाल 0:
		dev->driver_info->status(dev, urb);
		अवरोध;

	/* software-driven पूर्णांकerface shutकरोwn */
	हाल -ENOENT:		/* urb समाप्तed */
	हाल -ESHUTDOWN:	/* hardware gone */
		netअगर_dbg(dev, अगरकरोwn, dev->net,
			  "intr shutdown, code %d\n", status);
		वापस;

	/* NOTE:  not throttling like RX/TX, since this endpoपूर्णांक
	 * alपढ़ोy polls infrequently
	 */
	शेष:
		netdev_dbg(dev->net, "intr status %d\n", status);
		अवरोध;
	पूर्ण

	status = usb_submit_urb (urb, GFP_ATOMIC);
	अगर (status != 0)
		netअगर_err(dev, समयr, dev->net,
			  "intr resubmit --> %d\n", status);
पूर्ण

अटल पूर्णांक init_status (काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अक्षर		*buf = शून्य;
	अचिन्हित	pipe = 0;
	अचिन्हित	maxp;
	अचिन्हित	period;

	अगर (!dev->driver_info->status)
		वापस 0;

	pipe = usb_rcvपूर्णांकpipe (dev->udev,
			dev->status->desc.bEndpoपूर्णांकAddress
				& USB_ENDPOINT_NUMBER_MASK);
	maxp = usb_maxpacket (dev->udev, pipe, 0);

	/* aव्योम 1 msec chatter:  min 8 msec poll rate */
	period = max ((पूर्णांक) dev->status->desc.bInterval,
		(dev->udev->speed == USB_SPEED_HIGH) ? 7 : 3);

	buf = kदो_स्मृति (maxp, GFP_KERNEL);
	अगर (buf) अणु
		dev->पूर्णांकerrupt = usb_alloc_urb (0, GFP_KERNEL);
		अगर (!dev->पूर्णांकerrupt) अणु
			kमुक्त (buf);
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt, dev->udev, pipe,
				buf, maxp, पूर्णांकr_complete, dev, period);
			dev->पूर्णांकerrupt->transfer_flags |= URB_FREE_BUFFER;
			dev_dbg(&पूर्णांकf->dev,
				"status ep%din, %d bytes period %d\n",
				usb_pipeendpoपूर्णांक(pipe), maxp, period);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Submit the पूर्णांकerrupt URB अगर not previously submitted, increasing refcount */
पूर्णांक usbnet_status_start(काष्ठा usbnet *dev, gfp_t mem_flags)
अणु
	पूर्णांक ret = 0;

	WARN_ON_ONCE(dev->पूर्णांकerrupt == शून्य);
	अगर (dev->पूर्णांकerrupt) अणु
		mutex_lock(&dev->पूर्णांकerrupt_mutex);

		अगर (++dev->पूर्णांकerrupt_count == 1)
			ret = usb_submit_urb(dev->पूर्णांकerrupt, mem_flags);

		dev_dbg(&dev->udev->dev, "incremented interrupt URB count to %d\n",
			dev->पूर्णांकerrupt_count);
		mutex_unlock(&dev->पूर्णांकerrupt_mutex);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_status_start);

/* For resume; submit पूर्णांकerrupt URB अगर previously submitted */
अटल पूर्णांक __usbnet_status_start_क्रमce(काष्ठा usbnet *dev, gfp_t mem_flags)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev->पूर्णांकerrupt_mutex);
	अगर (dev->पूर्णांकerrupt_count) अणु
		ret = usb_submit_urb(dev->पूर्णांकerrupt, mem_flags);
		dev_dbg(&dev->udev->dev,
			"submitted interrupt URB for resume\n");
	पूर्ण
	mutex_unlock(&dev->पूर्णांकerrupt_mutex);
	वापस ret;
पूर्ण

/* Kill the पूर्णांकerrupt URB अगर all submitters want it समाप्तed */
व्योम usbnet_status_stop(काष्ठा usbnet *dev)
अणु
	अगर (dev->पूर्णांकerrupt) अणु
		mutex_lock(&dev->पूर्णांकerrupt_mutex);
		WARN_ON(dev->पूर्णांकerrupt_count == 0);

		अगर (dev->पूर्णांकerrupt_count && --dev->पूर्णांकerrupt_count == 0)
			usb_समाप्त_urb(dev->पूर्णांकerrupt);

		dev_dbg(&dev->udev->dev,
			"decremented interrupt URB count to %d\n",
			dev->पूर्णांकerrupt_count);
		mutex_unlock(&dev->पूर्णांकerrupt_mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_status_stop);

/* For suspend; always समाप्त पूर्णांकerrupt URB */
अटल व्योम __usbnet_status_stop_क्रमce(काष्ठा usbnet *dev)
अणु
	अगर (dev->पूर्णांकerrupt) अणु
		mutex_lock(&dev->पूर्णांकerrupt_mutex);
		usb_समाप्त_urb(dev->पूर्णांकerrupt);
		dev_dbg(&dev->udev->dev, "killed interrupt URB for suspend\n");
		mutex_unlock(&dev->पूर्णांकerrupt_mutex);
	पूर्ण
पूर्ण

/* Passes this packet up the stack, updating its accounting.
 * Some link protocols batch packets, so their rx_fixup paths
 * can वापस clones as well as just modअगरy the original skb.
 */
व्योम usbnet_skb_वापस (काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा pcpu_sw_netstats *stats64 = this_cpu_ptr(dev->net->tstats);
	अचिन्हित दीर्घ flags;
	पूर्णांक	status;

	अगर (test_bit(EVENT_RX_PAUSED, &dev->flags)) अणु
		skb_queue_tail(&dev->rxq_छोड़ो, skb);
		वापस;
	पूर्ण

	/* only update अगर unset to allow minidriver rx_fixup override */
	अगर (skb->protocol == 0)
		skb->protocol = eth_type_trans (skb, dev->net);

	flags = u64_stats_update_begin_irqsave(&stats64->syncp);
	stats64->rx_packets++;
	stats64->rx_bytes += skb->len;
	u64_stats_update_end_irqrestore(&stats64->syncp, flags);

	netअगर_dbg(dev, rx_status, dev->net, "< rx, len %zu, type 0x%x\n",
		  skb->len + माप (काष्ठा ethhdr), skb->protocol);
	स_रखो (skb->cb, 0, माप (काष्ठा skb_data));

	अगर (skb_defer_rx_बारtamp(skb))
		वापस;

	status = netअगर_rx (skb);
	अगर (status != NET_RX_SUCCESS)
		netअगर_dbg(dev, rx_err, dev->net,
			  "netif_rx status %d\n", status);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_skb_वापस);

/* must be called अगर hard_mtu or rx_urb_size changed */
व्योम usbnet_update_max_qlen(काष्ठा usbnet *dev)
अणु
	क्रमागत usb_device_speed speed = dev->udev->speed;

	अगर (!dev->rx_urb_size || !dev->hard_mtu)
		जाओ insanity;
	चयन (speed) अणु
	हाल USB_SPEED_HIGH:
		dev->rx_qlen = MAX_QUEUE_MEMORY / dev->rx_urb_size;
		dev->tx_qlen = MAX_QUEUE_MEMORY / dev->hard_mtu;
		अवरोध;
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		/*
		 * Not take शेष 5ms qlen क्रम super speed HC to
		 * save memory, and iperf tests show 2.5ms qlen can
		 * work well
		 */
		dev->rx_qlen = 5 * MAX_QUEUE_MEMORY / dev->rx_urb_size;
		dev->tx_qlen = 5 * MAX_QUEUE_MEMORY / dev->hard_mtu;
		अवरोध;
	शेष:
insanity:
		dev->rx_qlen = dev->tx_qlen = 4;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_update_max_qlen);


/*-------------------------------------------------------------------------
 *
 * Network Device Driver (peer link to "Host Device", from USB host)
 *
 *-------------------------------------------------------------------------*/

पूर्णांक usbnet_change_mtu (काष्ठा net_device *net, पूर्णांक new_mtu)
अणु
	काष्ठा usbnet	*dev = netdev_priv(net);
	पूर्णांक		ll_mtu = new_mtu + net->hard_header_len;
	पूर्णांक		old_hard_mtu = dev->hard_mtu;
	पूर्णांक		old_rx_urb_size = dev->rx_urb_size;

	// no second zero-length packet पढ़ो wanted after mtu-sized packets
	अगर ((ll_mtu % dev->maxpacket) == 0)
		वापस -गलत_तर्क;
	net->mtu = new_mtu;

	dev->hard_mtu = net->mtu + net->hard_header_len;
	अगर (dev->rx_urb_size == old_hard_mtu) अणु
		dev->rx_urb_size = dev->hard_mtu;
		अगर (dev->rx_urb_size > old_rx_urb_size) अणु
			usbnet_छोड़ो_rx(dev);
			usbnet_unlink_rx_urbs(dev);
			usbnet_resume_rx(dev);
		पूर्ण
	पूर्ण

	/* max qlen depend on hard_mtu and rx_urb_size */
	usbnet_update_max_qlen(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_change_mtu);

/* The caller must hold list->lock */
अटल व्योम __usbnet_queue_skb(काष्ठा sk_buff_head *list,
			काष्ठा sk_buff *newsk, क्रमागत skb_state state)
अणु
	काष्ठा skb_data *entry = (काष्ठा skb_data *) newsk->cb;

	__skb_queue_tail(list, newsk);
	entry->state = state;
पूर्ण

/*-------------------------------------------------------------------------*/

/* some LK 2.4 HCDs oopsed अगर we मुक्तd or resubmitted urbs from
 * completion callbacks.  2.5 should have fixed those bugs...
 */

अटल क्रमागत skb_state defer_bh(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
		काष्ठा sk_buff_head *list, क्रमागत skb_state state)
अणु
	अचिन्हित दीर्घ		flags;
	क्रमागत skb_state 		old_state;
	काष्ठा skb_data *entry = (काष्ठा skb_data *) skb->cb;

	spin_lock_irqsave(&list->lock, flags);
	old_state = entry->state;
	entry->state = state;
	__skb_unlink(skb, list);

	/* defer_bh() is never called with list == &dev->करोne.
	 * spin_lock_nested() tells lockdep that it is OK to take
	 * dev->करोne.lock here with list->lock held.
	 */
	spin_lock_nested(&dev->करोne.lock, SINGLE_DEPTH_NESTING);

	__skb_queue_tail(&dev->करोne, skb);
	अगर (dev->करोne.qlen == 1)
		tasklet_schedule(&dev->bh);
	spin_unlock(&dev->करोne.lock);
	spin_unlock_irqrestore(&list->lock, flags);
	वापस old_state;
पूर्ण

/* some work can't be करोne in tasklets, so we use keventd
 *
 * NOTE:  annoying asymmetry:  अगर it's active, schedule_work() fails,
 * but tasklet_schedule() करोesn't.  hope the failure is rare.
 */
व्योम usbnet_defer_kevent (काष्ठा usbnet *dev, पूर्णांक work)
अणु
	set_bit (work, &dev->flags);
	अगर (!schedule_work (&dev->kevent))
		netdev_dbg(dev->net, "kevent %d may have been dropped\n", work);
	अन्यथा
		netdev_dbg(dev->net, "kevent %d scheduled\n", work);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_defer_kevent);

/*-------------------------------------------------------------------------*/

अटल व्योम rx_complete (काष्ठा urb *urb);

अटल पूर्णांक rx_submit (काष्ठा usbnet *dev, काष्ठा urb *urb, gfp_t flags)
अणु
	काष्ठा sk_buff		*skb;
	काष्ठा skb_data		*entry;
	पूर्णांक			retval = 0;
	अचिन्हित दीर्घ		lockflags;
	माप_प्रकार			size = dev->rx_urb_size;

	/* prevent rx skb allocation when error ratio is high */
	अगर (test_bit(EVENT_RX_KILL, &dev->flags)) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOLINK;
	पूर्ण

	अगर (test_bit(EVENT_NO_IP_ALIGN, &dev->flags))
		skb = __netdev_alloc_skb(dev->net, size, flags);
	अन्यथा
		skb = __netdev_alloc_skb_ip_align(dev->net, size, flags);
	अगर (!skb) अणु
		netअगर_dbg(dev, rx_err, dev->net, "no rx skb\n");
		usbnet_defer_kevent (dev, EVENT_RX_MEMORY);
		usb_मुक्त_urb (urb);
		वापस -ENOMEM;
	पूर्ण

	entry = (काष्ठा skb_data *) skb->cb;
	entry->urb = urb;
	entry->dev = dev;
	entry->length = 0;

	usb_fill_bulk_urb (urb, dev->udev, dev->in,
		skb->data, size, rx_complete, skb);

	spin_lock_irqsave (&dev->rxq.lock, lockflags);

	अगर (netअगर_running (dev->net) &&
	    netअगर_device_present (dev->net) &&
	    test_bit(EVENT_DEV_OPEN, &dev->flags) &&
	    !test_bit (EVENT_RX_HALT, &dev->flags) &&
	    !test_bit (EVENT_DEV_ASLEEP, &dev->flags)) अणु
		चयन (retval = usb_submit_urb (urb, GFP_ATOMIC)) अणु
		हाल -EPIPE:
			usbnet_defer_kevent (dev, EVENT_RX_HALT);
			अवरोध;
		हाल -ENOMEM:
			usbnet_defer_kevent (dev, EVENT_RX_MEMORY);
			अवरोध;
		हाल -ENODEV:
			netअगर_dbg(dev, अगरकरोwn, dev->net, "device gone\n");
			netअगर_device_detach (dev->net);
			अवरोध;
		हाल -EHOSTUNREACH:
			retval = -ENOLINK;
			अवरोध;
		शेष:
			netअगर_dbg(dev, rx_err, dev->net,
				  "rx submit, %d\n", retval);
			tasklet_schedule (&dev->bh);
			अवरोध;
		हाल 0:
			__usbnet_queue_skb(&dev->rxq, skb, rx_start);
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_dbg(dev, अगरकरोwn, dev->net, "rx: stopped\n");
		retval = -ENOLINK;
	पूर्ण
	spin_unlock_irqrestore (&dev->rxq.lock, lockflags);
	अगर (retval) अणु
		dev_kमुक्त_skb_any (skb);
		usb_मुक्त_urb (urb);
	पूर्ण
	वापस retval;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम rx_process (काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	अगर (dev->driver_info->rx_fixup &&
	    !dev->driver_info->rx_fixup (dev, skb)) अणु
		/* With RX_ASSEMBLE, rx_fixup() must update counters */
		अगर (!(dev->driver_info->flags & FLAG_RX_ASSEMBLE))
			dev->net->stats.rx_errors++;
		जाओ करोne;
	पूर्ण
	// अन्यथा network stack हटाओs extra byte अगर we क्रमced a लघु packet

	/* all data was alपढ़ोy cloned from skb inside the driver */
	अगर (dev->driver_info->flags & FLAG_MULTI_PACKET)
		जाओ करोne;

	अगर (skb->len < ETH_HLEN) अणु
		dev->net->stats.rx_errors++;
		dev->net->stats.rx_length_errors++;
		netअगर_dbg(dev, rx_err, dev->net, "rx length %d\n", skb->len);
	पूर्ण अन्यथा अणु
		usbnet_skb_वापस(dev, skb);
		वापस;
	पूर्ण

करोne:
	skb_queue_tail(&dev->करोne, skb);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम rx_complete (काष्ठा urb *urb)
अणु
	काष्ठा sk_buff		*skb = (काष्ठा sk_buff *) urb->context;
	काष्ठा skb_data		*entry = (काष्ठा skb_data *) skb->cb;
	काष्ठा usbnet		*dev = entry->dev;
	पूर्णांक			urb_status = urb->status;
	क्रमागत skb_state		state;

	skb_put (skb, urb->actual_length);
	state = rx_करोne;
	entry->urb = शून्य;

	चयन (urb_status) अणु
	/* success */
	हाल 0:
		अवरोध;

	/* stalls need manual reset. this is rare ... except that
	 * when going through USB 2.0 TTs, unplug appears this way.
	 * we aव्योम the highspeed version of the ETIMEDOUT/EILSEQ
	 * storm, recovering as needed.
	 */
	हाल -EPIPE:
		dev->net->stats.rx_errors++;
		usbnet_defer_kevent (dev, EVENT_RX_HALT);
		fallthrough;

	/* software-driven पूर्णांकerface shutकरोwn */
	हाल -ECONNRESET:		/* async unlink */
	हाल -ESHUTDOWN:		/* hardware gone */
		netअगर_dbg(dev, अगरकरोwn, dev->net,
			  "rx shutdown, code %d\n", urb_status);
		जाओ block;

	/* we get controller i/o faults during hub_wq disconnect() delays.
	 * throttle करोwn resubmits, to aव्योम log floods; just temporarily,
	 * so we still recover when the fault isn't a hub_wq delay.
	 */
	हाल -EPROTO:
	हाल -ETIME:
	हाल -EILSEQ:
		dev->net->stats.rx_errors++;
		अगर (!समयr_pending (&dev->delay)) अणु
			mod_समयr (&dev->delay, jअगरfies + THROTTLE_JIFFIES);
			netअगर_dbg(dev, link, dev->net,
				  "rx throttle %d\n", urb_status);
		पूर्ण
block:
		state = rx_cleanup;
		entry->urb = urb;
		urb = शून्य;
		अवरोध;

	/* data overrun ... flush fअगरo? */
	हाल -EOVERFLOW:
		dev->net->stats.rx_over_errors++;
		fallthrough;

	शेष:
		state = rx_cleanup;
		dev->net->stats.rx_errors++;
		netअगर_dbg(dev, rx_err, dev->net, "rx status %d\n", urb_status);
		अवरोध;
	पूर्ण

	/* stop rx अगर packet error rate is high */
	अगर (++dev->pkt_cnt > 30) अणु
		dev->pkt_cnt = 0;
		dev->pkt_err = 0;
	पूर्ण अन्यथा अणु
		अगर (state == rx_cleanup)
			dev->pkt_err++;
		अगर (dev->pkt_err > 20)
			set_bit(EVENT_RX_KILL, &dev->flags);
	पूर्ण

	state = defer_bh(dev, skb, &dev->rxq, state);

	अगर (urb) अणु
		अगर (netअगर_running (dev->net) &&
		    !test_bit (EVENT_RX_HALT, &dev->flags) &&
		    state != unlink_start) अणु
			rx_submit (dev, urb, GFP_ATOMIC);
			usb_mark_last_busy(dev->udev);
			वापस;
		पूर्ण
		usb_मुक्त_urb (urb);
	पूर्ण
	netअगर_dbg(dev, rx_err, dev->net, "no read resubmitted\n");
पूर्ण

/*-------------------------------------------------------------------------*/
व्योम usbnet_छोड़ो_rx(काष्ठा usbnet *dev)
अणु
	set_bit(EVENT_RX_PAUSED, &dev->flags);

	netअगर_dbg(dev, rx_status, dev->net, "paused rx queue enabled\n");
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_छोड़ो_rx);

व्योम usbnet_resume_rx(काष्ठा usbnet *dev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक num = 0;

	clear_bit(EVENT_RX_PAUSED, &dev->flags);

	जबतक ((skb = skb_dequeue(&dev->rxq_छोड़ो)) != शून्य) अणु
		usbnet_skb_वापस(dev, skb);
		num++;
	पूर्ण

	tasklet_schedule(&dev->bh);

	netअगर_dbg(dev, rx_status, dev->net,
		  "paused rx queue disabled, %d skbs requeued\n", num);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_resume_rx);

व्योम usbnet_purge_छोड़ोd_rxq(काष्ठा usbnet *dev)
अणु
	skb_queue_purge(&dev->rxq_छोड़ो);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_purge_छोड़ोd_rxq);

/*-------------------------------------------------------------------------*/

// unlink pending rx/tx; completion handlers करो all other cleanup

अटल पूर्णांक unlink_urbs (काष्ठा usbnet *dev, काष्ठा sk_buff_head *q)
अणु
	अचिन्हित दीर्घ		flags;
	काष्ठा sk_buff		*skb;
	पूर्णांक			count = 0;

	spin_lock_irqsave (&q->lock, flags);
	जबतक (!skb_queue_empty(q)) अणु
		काष्ठा skb_data		*entry;
		काष्ठा urb		*urb;
		पूर्णांक			retval;

		skb_queue_walk(q, skb) अणु
			entry = (काष्ठा skb_data *) skb->cb;
			अगर (entry->state != unlink_start)
				जाओ found;
		पूर्ण
		अवरोध;
found:
		entry->state = unlink_start;
		urb = entry->urb;

		/*
		 * Get reference count of the URB to aव्योम it to be
		 * मुक्तd during usb_unlink_urb, which may trigger
		 * use-after-मुक्त problem inside usb_unlink_urb since
		 * usb_unlink_urb is always racing with .complete
		 * handler(include defer_bh).
		 */
		usb_get_urb(urb);
		spin_unlock_irqrestore(&q->lock, flags);
		// during some PM-driven resume scenarios,
		// these (async) unlinks complete immediately
		retval = usb_unlink_urb (urb);
		अगर (retval != -EINPROGRESS && retval != 0)
			netdev_dbg(dev->net, "unlink urb err, %d\n", retval);
		अन्यथा
			count++;
		usb_put_urb(urb);
		spin_lock_irqsave(&q->lock, flags);
	पूर्ण
	spin_unlock_irqrestore (&q->lock, flags);
	वापस count;
पूर्ण

// Flush all pending rx urbs
// minidrivers may need to करो this when the MTU changes

व्योम usbnet_unlink_rx_urbs(काष्ठा usbnet *dev)
अणु
	अगर (netअगर_running(dev->net)) अणु
		(व्योम) unlink_urbs (dev, &dev->rxq);
		tasklet_schedule(&dev->bh);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_unlink_rx_urbs);

/*-------------------------------------------------------------------------*/

अटल व्योम रुको_skb_queue_empty(काष्ठा sk_buff_head *q)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->lock, flags);
	जबतक (!skb_queue_empty(q)) अणु
		spin_unlock_irqrestore(&q->lock, flags);
		schedule_समयout(msecs_to_jअगरfies(UNLINK_TIMEOUT_MS));
		set_current_state(TASK_UNINTERRUPTIBLE);
		spin_lock_irqsave(&q->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);
पूर्ण

// precondition: never called in_पूर्णांकerrupt
अटल व्योम usbnet_terminate_urbs(काष्ठा usbnet *dev)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक temp;

	/* ensure there are no more active urbs */
	add_रुको_queue(&dev->रुको, &रुको);
	set_current_state(TASK_UNINTERRUPTIBLE);
	temp = unlink_urbs(dev, &dev->txq) +
		unlink_urbs(dev, &dev->rxq);

	/* maybe रुको क्रम deletions to finish. */
	रुको_skb_queue_empty(&dev->rxq);
	रुको_skb_queue_empty(&dev->txq);
	रुको_skb_queue_empty(&dev->करोne);
	netअगर_dbg(dev, अगरकरोwn, dev->net,
		  "waited for %d urb completions\n", temp);
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&dev->रुको, &रुको);
पूर्ण

पूर्णांक usbnet_stop (काष्ठा net_device *net)
अणु
	काष्ठा usbnet		*dev = netdev_priv(net);
	स्थिर काष्ठा driver_info *info = dev->driver_info;
	पूर्णांक			retval, pm, mpn;

	clear_bit(EVENT_DEV_OPEN, &dev->flags);
	netअगर_stop_queue (net);

	netअगर_info(dev, अगरकरोwn, dev->net,
		   "stop stats: rx/tx %lu/%lu, errs %lu/%lu\n",
		   net->stats.rx_packets, net->stats.tx_packets,
		   net->stats.rx_errors, net->stats.tx_errors);

	/* to not race resume */
	pm = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	/* allow minidriver to stop correctly (wireless devices to turn off
	 * radio etc) */
	अगर (info->stop) अणु
		retval = info->stop(dev);
		अगर (retval < 0)
			netअगर_info(dev, अगरकरोwn, dev->net,
				   "stop fail (%d) usbnet usb-%s-%s, %s\n",
				   retval,
				   dev->udev->bus->bus_name, dev->udev->devpath,
				   info->description);
	पूर्ण

	अगर (!(info->flags & FLAG_AVOID_UNLINK_URBS))
		usbnet_terminate_urbs(dev);

	usbnet_status_stop(dev);

	usbnet_purge_छोड़ोd_rxq(dev);

	mpn = !test_and_clear_bit(EVENT_NO_RUNTIME_PM, &dev->flags);

	/* deferred work (task, समयr, softirq) must also stop.
	 * can't flush_scheduled_work() until we drop rtnl (later),
	 * अन्यथा workers could deadlock; so make workers a NOP.
	 */
	dev->flags = 0;
	del_समयr_sync (&dev->delay);
	tasklet_समाप्त (&dev->bh);
	अगर (!pm)
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	अगर (info->manage_घातer && mpn)
		info->manage_घातer(dev, 0);
	अन्यथा
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_stop);

/*-------------------------------------------------------------------------*/

// posts पढ़ोs, and enables ग_लिखो queuing

// precondition: never called in_पूर्णांकerrupt

पूर्णांक usbnet_खोलो (काष्ठा net_device *net)
अणु
	काष्ठा usbnet		*dev = netdev_priv(net);
	पूर्णांक			retval;
	स्थिर काष्ठा driver_info *info = dev->driver_info;

	अगर ((retval = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf)) < 0) अणु
		netअगर_info(dev, अगरup, dev->net,
			   "resumption fail (%d) usbnet usb-%s-%s, %s\n",
			   retval,
			   dev->udev->bus->bus_name,
			   dev->udev->devpath,
			   info->description);
		जाओ करोne_nopm;
	पूर्ण

	// put पूर्णांकo "known safe" state
	अगर (info->reset && (retval = info->reset (dev)) < 0) अणु
		netअगर_info(dev, अगरup, dev->net,
			   "open reset fail (%d) usbnet usb-%s-%s, %s\n",
			   retval,
			   dev->udev->bus->bus_name,
			   dev->udev->devpath,
			   info->description);
		जाओ करोne;
	पूर्ण

	/* hard_mtu or rx_urb_size may change in reset() */
	usbnet_update_max_qlen(dev);

	// insist peer be connected
	अगर (info->check_connect && (retval = info->check_connect (dev)) < 0) अणु
		netअगर_err(dev, अगरup, dev->net, "can't open; %d\n", retval);
		जाओ करोne;
	पूर्ण

	/* start any status पूर्णांकerrupt transfer */
	अगर (dev->पूर्णांकerrupt) अणु
		retval = usbnet_status_start(dev, GFP_KERNEL);
		अगर (retval < 0) अणु
			netअगर_err(dev, अगरup, dev->net,
				  "intr submit %d\n", retval);
			जाओ करोne;
		पूर्ण
	पूर्ण

	set_bit(EVENT_DEV_OPEN, &dev->flags);
	netअगर_start_queue (net);
	netअगर_info(dev, अगरup, dev->net,
		   "open: enable queueing (rx %d, tx %d) mtu %d %s framing\n",
		   (पूर्णांक)RX_QLEN(dev), (पूर्णांक)TX_QLEN(dev),
		   dev->net->mtu,
		   (dev->driver_info->flags & FLAG_FRAMING_NC) ? "NetChip" :
		   (dev->driver_info->flags & FLAG_FRAMING_GL) ? "GeneSys" :
		   (dev->driver_info->flags & FLAG_FRAMING_Z) ? "Zaurus" :
		   (dev->driver_info->flags & FLAG_FRAMING_RN) ? "RNDIS" :
		   (dev->driver_info->flags & FLAG_FRAMING_AX) ? "ASIX" :
		   "simple");

	/* reset rx error state */
	dev->pkt_cnt = 0;
	dev->pkt_err = 0;
	clear_bit(EVENT_RX_KILL, &dev->flags);

	// delay posting पढ़ोs until we're fully खोलो
	tasklet_schedule (&dev->bh);
	अगर (info->manage_घातer) अणु
		retval = info->manage_घातer(dev, 1);
		अगर (retval < 0) अणु
			retval = 0;
			set_bit(EVENT_NO_RUNTIME_PM, &dev->flags);
		पूर्ण अन्यथा अणु
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
		पूर्ण
	पूर्ण
	वापस retval;
करोne:
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
करोne_nopm:
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_खोलो);

/*-------------------------------------------------------------------------*/

/* ethtool methods; minidrivers may need to add some more, but
 * they'll probably want to use this base set.
 */

/* These methods are written on the assumption that the device
 * uses MII
 */
पूर्णांक usbnet_get_link_ksettings_mii(काष्ठा net_device *net,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	अगर (!dev->mii.mdio_पढ़ो)
		वापस -EOPNOTSUPP;

	mii_ethtool_get_link_ksettings(&dev->mii, cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_get_link_ksettings_mii);

पूर्णांक usbnet_get_link_ksettings_पूर्णांकernal(काष्ठा net_device *net,
					काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	/* the assumption that speed is equal on tx and rx
	 * is deeply engrained पूर्णांकo the networking layer.
	 * For wireless stuff it is not true.
	 * We assume that rx_speed matters more.
	 */
	अगर (dev->rx_speed != SPEED_UNSET)
		cmd->base.speed = dev->rx_speed / 1000000;
	अन्यथा अगर (dev->tx_speed != SPEED_UNSET)
		cmd->base.speed = dev->tx_speed / 1000000;
	अन्यथा
		cmd->base.speed = SPEED_UNKNOWN;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_get_link_ksettings_पूर्णांकernal);

पूर्णांक usbnet_set_link_ksettings_mii(काष्ठा net_device *net,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	पूर्णांक retval;

	अगर (!dev->mii.mdio_ग_लिखो)
		वापस -EOPNOTSUPP;

	retval = mii_ethtool_set_link_ksettings(&dev->mii, cmd);

	/* link speed/duplex might have changed */
	अगर (dev->driver_info->link_reset)
		dev->driver_info->link_reset(dev);

	/* hard_mtu or rx_urb_size may change in link_reset() */
	usbnet_update_max_qlen(dev);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_set_link_ksettings_mii);

u32 usbnet_get_link (काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	/* If a check_connect is defined, वापस its result */
	अगर (dev->driver_info->check_connect)
		वापस dev->driver_info->check_connect (dev) == 0;

	/* अगर the device has mii operations, use those */
	अगर (dev->mii.mdio_पढ़ो)
		वापस mii_link_ok(&dev->mii);

	/* Otherwise, dtrt क्रम drivers calling netअगर_carrier_अणुon,offपूर्ण */
	वापस ethtool_op_get_link(net);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_get_link);

पूर्णांक usbnet_nway_reset(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	अगर (!dev->mii.mdio_ग_लिखो)
		वापस -EOPNOTSUPP;

	वापस mii_nway_restart(&dev->mii);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_nway_reset);

व्योम usbnet_get_drvinfo (काष्ठा net_device *net, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	strlcpy (info->driver, dev->driver_name, माप info->driver);
	strlcpy (info->fw_version, dev->driver_info->description,
		माप info->fw_version);
	usb_make_path (dev->udev, info->bus_info, माप info->bus_info);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_get_drvinfo);

u32 usbnet_get_msglevel (काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	वापस dev->msg_enable;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_get_msglevel);

व्योम usbnet_set_msglevel (काष्ठा net_device *net, u32 level)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	dev->msg_enable = level;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_set_msglevel);

/* drivers may override शेष ethtool_ops in their bind() routine */
अटल स्थिर काष्ठा ethtool_ops usbnet_ethtool_ops = अणु
	.get_link		= usbnet_get_link,
	.nway_reset		= usbnet_nway_reset,
	.get_drvinfo		= usbnet_get_drvinfo,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल व्योम __handle_link_change(काष्ठा usbnet *dev)
अणु
	अगर (!test_bit(EVENT_DEV_OPEN, &dev->flags))
		वापस;

	अगर (!netअगर_carrier_ok(dev->net)) अणु
		/* समाप्त URBs क्रम पढ़ोing packets to save bus bandwidth */
		unlink_urbs(dev, &dev->rxq);

		/*
		 * tx_समयout will unlink URBs क्रम sending packets and
		 * tx queue is stopped by netcore after link becomes off
		 */
	पूर्ण अन्यथा अणु
		/* submitting URBs क्रम पढ़ोing packets */
		tasklet_schedule(&dev->bh);
	पूर्ण

	/* hard_mtu or rx_urb_size may change during link change */
	usbnet_update_max_qlen(dev);

	clear_bit(EVENT_LINK_CHANGE, &dev->flags);
पूर्ण

व्योम usbnet_set_rx_mode(काष्ठा net_device *net)
अणु
	काष्ठा usbnet		*dev = netdev_priv(net);

	usbnet_defer_kevent(dev, EVENT_SET_RX_MODE);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_set_rx_mode);

अटल व्योम __handle_set_rx_mode(काष्ठा usbnet *dev)
अणु
	अगर (dev->driver_info->set_rx_mode)
		(dev->driver_info->set_rx_mode)(dev);

	clear_bit(EVENT_SET_RX_MODE, &dev->flags);
पूर्ण

/* work that cannot be करोne in पूर्णांकerrupt context uses keventd.
 *
 * NOTE:  with 2.5 we could करो more of this using completion callbacks,
 * especially now that control transfers can be queued.
 */
अटल व्योम
usbnet_deferred_kevent (काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbnet		*dev =
		container_of(work, काष्ठा usbnet, kevent);
	पूर्णांक			status;

	/* usb_clear_halt() needs a thपढ़ो context */
	अगर (test_bit (EVENT_TX_HALT, &dev->flags)) अणु
		unlink_urbs (dev, &dev->txq);
		status = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0)
			जाओ fail_pipe;
		status = usb_clear_halt (dev->udev, dev->out);
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0 &&
		    status != -EPIPE &&
		    status != -ESHUTDOWN) अणु
			अगर (netअगर_msg_tx_err (dev))
fail_pipe:
				netdev_err(dev->net, "can't clear tx halt, status %d\n",
					   status);
		पूर्ण अन्यथा अणु
			clear_bit (EVENT_TX_HALT, &dev->flags);
			अगर (status != -ESHUTDOWN)
				netअगर_wake_queue (dev->net);
		पूर्ण
	पूर्ण
	अगर (test_bit (EVENT_RX_HALT, &dev->flags)) अणु
		unlink_urbs (dev, &dev->rxq);
		status = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0)
			जाओ fail_halt;
		status = usb_clear_halt (dev->udev, dev->in);
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0 &&
		    status != -EPIPE &&
		    status != -ESHUTDOWN) अणु
			अगर (netअगर_msg_rx_err (dev))
fail_halt:
				netdev_err(dev->net, "can't clear rx halt, status %d\n",
					   status);
		पूर्ण अन्यथा अणु
			clear_bit (EVENT_RX_HALT, &dev->flags);
			tasklet_schedule (&dev->bh);
		पूर्ण
	पूर्ण

	/* tasklet could resubmit itself क्रमever अगर memory is tight */
	अगर (test_bit (EVENT_RX_MEMORY, &dev->flags)) अणु
		काष्ठा urb	*urb = शून्य;
		पूर्णांक resched = 1;

		अगर (netअगर_running (dev->net))
			urb = usb_alloc_urb (0, GFP_KERNEL);
		अन्यथा
			clear_bit (EVENT_RX_MEMORY, &dev->flags);
		अगर (urb != शून्य) अणु
			clear_bit (EVENT_RX_MEMORY, &dev->flags);
			status = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
			अगर (status < 0) अणु
				usb_मुक्त_urb(urb);
				जाओ fail_lowmem;
			पूर्ण
			अगर (rx_submit (dev, urb, GFP_KERNEL) == -ENOLINK)
				resched = 0;
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
fail_lowmem:
			अगर (resched)
				tasklet_schedule (&dev->bh);
		पूर्ण
	पूर्ण

	अगर (test_bit (EVENT_LINK_RESET, &dev->flags)) अणु
		स्थिर काष्ठा driver_info *info = dev->driver_info;
		पूर्णांक			retval = 0;

		clear_bit (EVENT_LINK_RESET, &dev->flags);
		status = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0)
			जाओ skip_reset;
		अगर(info->link_reset && (retval = info->link_reset(dev)) < 0) अणु
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
skip_reset:
			netdev_info(dev->net, "link reset failed (%d) usbnet usb-%s-%s, %s\n",
				    retval,
				    dev->udev->bus->bus_name,
				    dev->udev->devpath,
				    info->description);
		पूर्ण अन्यथा अणु
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
		पूर्ण

		/* handle link change from link resetting */
		__handle_link_change(dev);
	पूर्ण

	अगर (test_bit (EVENT_LINK_CHANGE, &dev->flags))
		__handle_link_change(dev);

	अगर (test_bit (EVENT_SET_RX_MODE, &dev->flags))
		__handle_set_rx_mode(dev);


	अगर (dev->flags)
		netdev_dbg(dev->net, "kevent done, flags = 0x%lx\n", dev->flags);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम tx_complete (काष्ठा urb *urb)
अणु
	काष्ठा sk_buff		*skb = (काष्ठा sk_buff *) urb->context;
	काष्ठा skb_data		*entry = (काष्ठा skb_data *) skb->cb;
	काष्ठा usbnet		*dev = entry->dev;

	अगर (urb->status == 0) अणु
		काष्ठा pcpu_sw_netstats *stats64 = this_cpu_ptr(dev->net->tstats);
		अचिन्हित दीर्घ flags;

		flags = u64_stats_update_begin_irqsave(&stats64->syncp);
		stats64->tx_packets += entry->packets;
		stats64->tx_bytes += entry->length;
		u64_stats_update_end_irqrestore(&stats64->syncp, flags);
	पूर्ण अन्यथा अणु
		dev->net->stats.tx_errors++;

		चयन (urb->status) अणु
		हाल -EPIPE:
			usbnet_defer_kevent (dev, EVENT_TX_HALT);
			अवरोध;

		/* software-driven पूर्णांकerface shutकरोwn */
		हाल -ECONNRESET:		// async unlink
		हाल -ESHUTDOWN:		// hardware gone
			अवरोध;

		/* like rx, tx माला_लो controller i/o faults during hub_wq
		 * delays and so it uses the same throttling mechanism.
		 */
		हाल -EPROTO:
		हाल -ETIME:
		हाल -EILSEQ:
			usb_mark_last_busy(dev->udev);
			अगर (!समयr_pending (&dev->delay)) अणु
				mod_समयr (&dev->delay,
					jअगरfies + THROTTLE_JIFFIES);
				netअगर_dbg(dev, link, dev->net,
					  "tx throttle %d\n", urb->status);
			पूर्ण
			netअगर_stop_queue (dev->net);
			अवरोध;
		शेष:
			netअगर_dbg(dev, tx_err, dev->net,
				  "tx err %d\n", entry->urb->status);
			अवरोध;
		पूर्ण
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
	(व्योम) defer_bh(dev, skb, &dev->txq, tx_करोne);
पूर्ण

/*-------------------------------------------------------------------------*/

व्योम usbnet_tx_समयout (काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा usbnet		*dev = netdev_priv(net);

	unlink_urbs (dev, &dev->txq);
	tasklet_schedule (&dev->bh);
	/* this needs to be handled inभागidually because the generic layer
	 * करोesn't know what is sufficient and could not restore निजी
	 * inक्रमmation अगर a remedy of an unconditional reset were used.
	 */
	अगर (dev->driver_info->recover)
		(dev->driver_info->recover)(dev);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_tx_समयout);

/*-------------------------------------------------------------------------*/

अटल पूर्णांक build_dma_sg(स्थिर काष्ठा sk_buff *skb, काष्ठा urb *urb)
अणु
	अचिन्हित num_sgs, total_len = 0;
	पूर्णांक i, s = 0;

	num_sgs = skb_shinfo(skb)->nr_frags + 1;
	अगर (num_sgs == 1)
		वापस 0;

	/* reserve one क्रम zero packet */
	urb->sg = kदो_स्मृति_array(num_sgs + 1, माप(काष्ठा scatterlist),
				GFP_ATOMIC);
	अगर (!urb->sg)
		वापस -ENOMEM;

	urb->num_sgs = num_sgs;
	sg_init_table(urb->sg, urb->num_sgs + 1);

	sg_set_buf(&urb->sg[s++], skb->data, skb_headlen(skb));
	total_len += skb_headlen(skb);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];

		total_len += skb_frag_size(f);
		sg_set_page(&urb->sg[i + s], skb_frag_page(f), skb_frag_size(f),
			    skb_frag_off(f));
	पूर्ण
	urb->transfer_buffer_length = total_len;

	वापस 1;
पूर्ण

netdev_tx_t usbnet_start_xmit (काष्ठा sk_buff *skb,
				     काष्ठा net_device *net)
अणु
	काष्ठा usbnet		*dev = netdev_priv(net);
	अचिन्हित पूर्णांक			length;
	काष्ठा urb		*urb = शून्य;
	काष्ठा skb_data		*entry;
	स्थिर काष्ठा driver_info *info = dev->driver_info;
	अचिन्हित दीर्घ		flags;
	पूर्णांक retval;

	अगर (skb)
		skb_tx_बारtamp(skb);

	// some devices want funky USB-level framing, क्रम
	// win32 driver (usually) and/or hardware quirks
	अगर (info->tx_fixup) अणु
		skb = info->tx_fixup (dev, skb, GFP_ATOMIC);
		अगर (!skb) अणु
			/* packet collected; minidriver रुकोing क्रम more */
			अगर (info->flags & FLAG_MULTI_PACKET)
				जाओ not_drop;
			netअगर_dbg(dev, tx_err, dev->net, "can't tx_fixup skb\n");
			जाओ drop;
		पूर्ण
	पूर्ण

	अगर (!(urb = usb_alloc_urb (0, GFP_ATOMIC))) अणु
		netअगर_dbg(dev, tx_err, dev->net, "no urb\n");
		जाओ drop;
	पूर्ण

	entry = (काष्ठा skb_data *) skb->cb;
	entry->urb = urb;
	entry->dev = dev;

	usb_fill_bulk_urb (urb, dev->udev, dev->out,
			skb->data, skb->len, tx_complete, skb);
	अगर (dev->can_dma_sg) अणु
		अगर (build_dma_sg(skb, urb) < 0)
			जाओ drop;
	पूर्ण
	length = urb->transfer_buffer_length;

	/* करोn't assume the hardware handles USB_ZERO_PACKET
	 * NOTE:  strictly conक्रमming cdc-ether devices should expect
	 * the ZLP here, but ignore the one-byte packet.
	 * NOTE2: CDC NCM specअगरication is dअगरferent from CDC ECM when
	 * handling ZLP/लघु packets, so cdc_ncm driver will make लघु
	 * packet itself अगर needed.
	 */
	अगर (length % dev->maxpacket == 0) अणु
		अगर (!(info->flags & FLAG_SEND_ZLP)) अणु
			अगर (!(info->flags & FLAG_MULTI_PACKET)) अणु
				length++;
				अगर (skb_tailroom(skb) && !urb->num_sgs) अणु
					skb->data[skb->len] = 0;
					__skb_put(skb, 1);
				पूर्ण अन्यथा अगर (urb->num_sgs)
					sg_set_buf(&urb->sg[urb->num_sgs++],
							dev->padding_pkt, 1);
			पूर्ण
		पूर्ण अन्यथा
			urb->transfer_flags |= URB_ZERO_PACKET;
	पूर्ण
	urb->transfer_buffer_length = length;

	अगर (info->flags & FLAG_MULTI_PACKET) अणु
		/* Driver has set number of packets and a length delta.
		 * Calculate the complete length and ensure that it's
		 * positive.
		 */
		entry->length += length;
		अगर (WARN_ON_ONCE(entry->length <= 0))
			entry->length = length;
	पूर्ण अन्यथा अणु
		usbnet_set_skb_tx_stats(skb, 1, length);
	पूर्ण

	spin_lock_irqsave(&dev->txq.lock, flags);
	retval = usb_स्वतःpm_get_पूर्णांकerface_async(dev->पूर्णांकf);
	अगर (retval < 0) अणु
		spin_unlock_irqrestore(&dev->txq.lock, flags);
		जाओ drop;
	पूर्ण
	अगर (netअगर_queue_stopped(net)) अणु
		usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
		spin_unlock_irqrestore(&dev->txq.lock, flags);
		जाओ drop;
	पूर्ण

#अगर_घोषित CONFIG_PM
	/* अगर this triggers the device is still a sleep */
	अगर (test_bit(EVENT_DEV_ASLEEP, &dev->flags)) अणु
		/* transmission will be करोne in resume */
		usb_anchor_urb(urb, &dev->deferred);
		/* no use to process more packets */
		netअगर_stop_queue(net);
		usb_put_urb(urb);
		spin_unlock_irqrestore(&dev->txq.lock, flags);
		netdev_dbg(dev->net, "Delaying transmission for resumption\n");
		जाओ deferred;
	पूर्ण
#पूर्ण_अगर

	चयन ((retval = usb_submit_urb (urb, GFP_ATOMIC))) अणु
	हाल -EPIPE:
		netअगर_stop_queue (net);
		usbnet_defer_kevent (dev, EVENT_TX_HALT);
		usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
		अवरोध;
	शेष:
		usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
		netअगर_dbg(dev, tx_err, dev->net,
			  "tx: submit urb err %d\n", retval);
		अवरोध;
	हाल 0:
		netअगर_trans_update(net);
		__usbnet_queue_skb(&dev->txq, skb, tx_start);
		अगर (dev->txq.qlen >= TX_QLEN (dev))
			netअगर_stop_queue (net);
	पूर्ण
	spin_unlock_irqrestore (&dev->txq.lock, flags);

	अगर (retval) अणु
		netअगर_dbg(dev, tx_err, dev->net, "drop, code %d\n", retval);
drop:
		dev->net->stats.tx_dropped++;
not_drop:
		अगर (skb)
			dev_kमुक्त_skb_any (skb);
		अगर (urb) अणु
			kमुक्त(urb->sg);
			usb_मुक्त_urb(urb);
		पूर्ण
	पूर्ण अन्यथा
		netअगर_dbg(dev, tx_queued, dev->net,
			  "> tx, len %u, type 0x%x\n", length, skb->protocol);
#अगर_घोषित CONFIG_PM
deferred:
#पूर्ण_अगर
	वापस NETDEV_TX_OK;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_start_xmit);

अटल पूर्णांक rx_alloc_submit(काष्ठा usbnet *dev, gfp_t flags)
अणु
	काष्ठा urb	*urb;
	पूर्णांक		i;
	पूर्णांक		ret = 0;

	/* करोn't refill the queue all at once */
	क्रम (i = 0; i < 10 && dev->rxq.qlen < RX_QLEN(dev); i++) अणु
		urb = usb_alloc_urb(0, flags);
		अगर (urb != शून्य) अणु
			ret = rx_submit(dev, urb, flags);
			अगर (ret)
				जाओ err;
		पूर्ण अन्यथा अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण
err:
	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/

// tasklet (work deferred from completions, in_irq) or समयr

अटल व्योम usbnet_bh (काष्ठा समयr_list *t)
अणु
	काष्ठा usbnet		*dev = from_समयr(dev, t, delay);
	काष्ठा sk_buff		*skb;
	काष्ठा skb_data		*entry;

	जबतक ((skb = skb_dequeue (&dev->करोne))) अणु
		entry = (काष्ठा skb_data *) skb->cb;
		चयन (entry->state) अणु
		हाल rx_करोne:
			entry->state = rx_cleanup;
			rx_process (dev, skb);
			जारी;
		हाल tx_करोne:
			kमुक्त(entry->urb->sg);
			fallthrough;
		हाल rx_cleanup:
			usb_मुक्त_urb (entry->urb);
			dev_kमुक्त_skb (skb);
			जारी;
		शेष:
			netdev_dbg(dev->net, "bogus skb state %d\n", entry->state);
		पूर्ण
	पूर्ण

	/* restart RX again after disabling due to high error rate */
	clear_bit(EVENT_RX_KILL, &dev->flags);

	/* रुकोing क्रम all pending urbs to complete?
	 * only then can we क्रमgo submitting anew
	 */
	अगर (रुकोqueue_active(&dev->रुको)) अणु
		अगर (dev->txq.qlen + dev->rxq.qlen + dev->करोne.qlen == 0)
			wake_up_all(&dev->रुको);

	// or are we maybe लघु a few urbs?
	पूर्ण अन्यथा अगर (netअगर_running (dev->net) &&
		   netअगर_device_present (dev->net) &&
		   netअगर_carrier_ok(dev->net) &&
		   !समयr_pending(&dev->delay) &&
		   !test_bit(EVENT_RX_PAUSED, &dev->flags) &&
		   !test_bit(EVENT_RX_HALT, &dev->flags)) अणु
		पूर्णांक	temp = dev->rxq.qlen;

		अगर (temp < RX_QLEN(dev)) अणु
			अगर (rx_alloc_submit(dev, GFP_ATOMIC) == -ENOLINK)
				वापस;
			अगर (temp != dev->rxq.qlen)
				netअगर_dbg(dev, link, dev->net,
					  "rxqlen %d --> %d\n",
					  temp, dev->rxq.qlen);
			अगर (dev->rxq.qlen < RX_QLEN(dev))
				tasklet_schedule (&dev->bh);
		पूर्ण
		अगर (dev->txq.qlen < TX_QLEN (dev))
			netअगर_wake_queue (dev->net);
	पूर्ण
पूर्ण

अटल व्योम usbnet_bh_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा usbnet *dev = from_tasklet(dev, t, bh);

	usbnet_bh(&dev->delay);
पूर्ण


/*-------------------------------------------------------------------------
 *
 * USB Device Driver support
 *
 *-------------------------------------------------------------------------*/

// precondition: never called in_पूर्णांकerrupt

व्योम usbnet_disconnect (काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet		*dev;
	काष्ठा usb_device	*xdev;
	काष्ठा net_device	*net;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (!dev)
		वापस;

	xdev = पूर्णांकerface_to_usbdev (पूर्णांकf);

	netअगर_info(dev, probe, dev->net, "unregister '%s' usb-%s-%s, %s\n",
		   पूर्णांकf->dev.driver->name,
		   xdev->bus->bus_name, xdev->devpath,
		   dev->driver_info->description);

	net = dev->net;
	unरेजिस्टर_netdev (net);

	cancel_work_sync(&dev->kevent);

	usb_scuttle_anchored_urbs(&dev->deferred);

	अगर (dev->driver_info->unbind)
		dev->driver_info->unbind (dev, पूर्णांकf);

	usb_समाप्त_urb(dev->पूर्णांकerrupt);
	usb_मुक्त_urb(dev->पूर्णांकerrupt);
	kमुक्त(dev->padding_pkt);

	मुक्त_percpu(net->tstats);
	मुक्त_netdev(net);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_disconnect);

अटल स्थिर काष्ठा net_device_ops usbnet_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_set_rx_mode	= usbnet_set_rx_mode,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/*-------------------------------------------------------------------------*/

// precondition: never called in_पूर्णांकerrupt

अटल काष्ठा device_type wlan_type = अणु
	.name	= "wlan",
पूर्ण;

अटल काष्ठा device_type wwan_type = अणु
	.name	= "wwan",
पूर्ण;

पूर्णांक
usbnet_probe (काष्ठा usb_पूर्णांकerface *udev, स्थिर काष्ठा usb_device_id *prod)
अणु
	काष्ठा usbnet			*dev;
	काष्ठा net_device		*net;
	काष्ठा usb_host_पूर्णांकerface	*पूर्णांकerface;
	स्थिर काष्ठा driver_info	*info;
	काष्ठा usb_device		*xdev;
	पूर्णांक				status;
	स्थिर अक्षर			*name;
	काष्ठा usb_driver 	*driver = to_usb_driver(udev->dev.driver);

	/* usbnet alपढ़ोy took usb runसमय pm, so have to enable the feature
	 * क्रम usb पूर्णांकerface, otherwise usb_स्वतःpm_get_पूर्णांकerface may वापस
	 * failure अगर RUNTIME_PM is enabled.
	 */
	अगर (!driver->supports_स्वतःsuspend) अणु
		driver->supports_स्वतःsuspend = 1;
		pm_runसमय_enable(&udev->dev);
	पूर्ण

	name = udev->dev.driver->name;
	info = (स्थिर काष्ठा driver_info *) prod->driver_info;
	अगर (!info) अणु
		dev_dbg (&udev->dev, "blacklisted by %s\n", name);
		वापस -ENODEV;
	पूर्ण
	xdev = पूर्णांकerface_to_usbdev (udev);
	पूर्णांकerface = udev->cur_altsetting;

	status = -ENOMEM;

	// set up our own records
	net = alloc_etherdev(माप(*dev));
	अगर (!net)
		जाओ out;

	/* netdev_prपूर्णांकk() needs this so करो it as early as possible */
	SET_NETDEV_DEV(net, &udev->dev);

	dev = netdev_priv(net);
	dev->udev = xdev;
	dev->पूर्णांकf = udev;
	dev->driver_info = info;
	dev->driver_name = name;
	dev->rx_speed = SPEED_UNSET;
	dev->tx_speed = SPEED_UNSET;

	net->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!net->tstats)
		जाओ out0;

	dev->msg_enable = netअगर_msg_init (msg_level, NETIF_MSG_DRV
				| NETIF_MSG_PROBE | NETIF_MSG_LINK);
	init_रुकोqueue_head(&dev->रुको);
	skb_queue_head_init (&dev->rxq);
	skb_queue_head_init (&dev->txq);
	skb_queue_head_init (&dev->करोne);
	skb_queue_head_init(&dev->rxq_छोड़ो);
	tasklet_setup(&dev->bh, usbnet_bh_tasklet);
	INIT_WORK (&dev->kevent, usbnet_deferred_kevent);
	init_usb_anchor(&dev->deferred);
	समयr_setup(&dev->delay, usbnet_bh, 0);
	mutex_init (&dev->phy_mutex);
	mutex_init(&dev->पूर्णांकerrupt_mutex);
	dev->पूर्णांकerrupt_count = 0;

	dev->net = net;
	म_नकल (net->name, "usb%d");
	स_नकल (net->dev_addr, node_id, माप node_id);

	/* rx and tx sides can use dअगरferent message sizes;
	 * bind() should set rx_urb_size in that हाल.
	 */
	dev->hard_mtu = net->mtu + net->hard_header_len;
	net->min_mtu = 0;
	net->max_mtu = ETH_MAX_MTU;

	net->netdev_ops = &usbnet_netdev_ops;
	net->watchकरोg_समयo = TX_TIMEOUT_JIFFIES;
	net->ethtool_ops = &usbnet_ethtool_ops;

	// allow device-specअगरic bind/init procedures
	// NOTE net->name still not usable ...
	अगर (info->bind) अणु
		status = info->bind (dev, udev);
		अगर (status < 0)
			जाओ out1;

		// heuristic:  "usb%d" क्रम links we know are two-host,
		// अन्यथा "eth%d" when there's reasonable करोubt.  userspace
		// can नाम the link अगर it knows better.
		अगर ((dev->driver_info->flags & FLAG_ETHER) != 0 &&
		    ((dev->driver_info->flags & FLAG_POINTTOPOINT) == 0 ||
		     (net->dev_addr [0] & 0x02) == 0))
			म_नकल (net->name, "eth%d");
		/* WLAN devices should always be named "wlan%d" */
		अगर ((dev->driver_info->flags & FLAG_WLAN) != 0)
			म_नकल(net->name, "wlan%d");
		/* WWAN devices should always be named "wwan%d" */
		अगर ((dev->driver_info->flags & FLAG_WWAN) != 0)
			म_नकल(net->name, "wwan%d");

		/* devices that cannot करो ARP */
		अगर ((dev->driver_info->flags & FLAG_NOARP) != 0)
			net->flags |= IFF_NOARP;

		/* maybe the remote can't receive an Ethernet MTU */
		अगर (net->mtu > (dev->hard_mtu - net->hard_header_len))
			net->mtu = dev->hard_mtu - net->hard_header_len;
	पूर्ण अन्यथा अगर (!info->in || !info->out)
		status = usbnet_get_endpoपूर्णांकs (dev, udev);
	अन्यथा अणु
		dev->in = usb_rcvbulkpipe (xdev, info->in);
		dev->out = usb_sndbulkpipe (xdev, info->out);
		अगर (!(info->flags & FLAG_NO_SETINT))
			status = usb_set_पूर्णांकerface (xdev,
				पूर्णांकerface->desc.bInterfaceNumber,
				पूर्णांकerface->desc.bAlternateSetting);
		अन्यथा
			status = 0;

	पूर्ण
	अगर (status >= 0 && dev->status)
		status = init_status (dev, udev);
	अगर (status < 0)
		जाओ out3;

	अगर (!dev->rx_urb_size)
		dev->rx_urb_size = dev->hard_mtu;
	dev->maxpacket = usb_maxpacket (dev->udev, dev->out, 1);

	/* let userspace know we have a अक्रमom address */
	अगर (ether_addr_equal(net->dev_addr, node_id))
		net->addr_assign_type = NET_ADDR_RANDOM;

	अगर ((dev->driver_info->flags & FLAG_WLAN) != 0)
		SET_NETDEV_DEVTYPE(net, &wlan_type);
	अगर ((dev->driver_info->flags & FLAG_WWAN) != 0)
		SET_NETDEV_DEVTYPE(net, &wwan_type);

	/* initialize max rx_qlen and tx_qlen */
	usbnet_update_max_qlen(dev);

	अगर (dev->can_dma_sg && !(info->flags & FLAG_SEND_ZLP) &&
		!(info->flags & FLAG_MULTI_PACKET)) अणु
		dev->padding_pkt = kzalloc(1, GFP_KERNEL);
		अगर (!dev->padding_pkt) अणु
			status = -ENOMEM;
			जाओ out4;
		पूर्ण
	पूर्ण

	status = रेजिस्टर_netdev (net);
	अगर (status)
		जाओ out5;
	netअगर_info(dev, probe, dev->net,
		   "register '%s' at usb-%s-%s, %s, %pM\n",
		   udev->dev.driver->name,
		   xdev->bus->bus_name, xdev->devpath,
		   dev->driver_info->description,
		   net->dev_addr);

	// ok, it's पढ़ोy to go.
	usb_set_पूर्णांकfdata (udev, dev);

	netअगर_device_attach (net);

	अगर (dev->driver_info->flags & FLAG_LINK_INTR)
		usbnet_link_change(dev, 0, 0);

	वापस 0;

out5:
	kमुक्त(dev->padding_pkt);
out4:
	usb_मुक्त_urb(dev->पूर्णांकerrupt);
out3:
	अगर (info->unbind)
		info->unbind (dev, udev);
out1:
	/* subdrivers must unकरो all they did in bind() अगर they
	 * fail it, but we may fail later and a deferred kevent
	 * may trigger an error resubmitting itself and, worse,
	 * schedule a समयr. So we समाप्त it all just in हाल.
	 */
	cancel_work_sync(&dev->kevent);
	del_समयr_sync(&dev->delay);
	मुक्त_percpu(net->tstats);
out0:
	मुक्त_netdev(net);
out:
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_probe);

/*-------------------------------------------------------------------------*/

/*
 * suspend the whole driver as soon as the first पूर्णांकerface is suspended
 * resume only when the last पूर्णांकerface is resumed
 */

पूर्णांक usbnet_suspend (काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbnet		*dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!dev->suspend_count++) अणु
		spin_lock_irq(&dev->txq.lock);
		/* करोn't स्वतःsuspend जबतक transmitting */
		अगर (dev->txq.qlen && PMSG_IS_AUTO(message)) अणु
			dev->suspend_count--;
			spin_unlock_irq(&dev->txq.lock);
			वापस -EBUSY;
		पूर्ण अन्यथा अणु
			set_bit(EVENT_DEV_ASLEEP, &dev->flags);
			spin_unlock_irq(&dev->txq.lock);
		पूर्ण
		/*
		 * accelerate emptying of the rx and queues, to aव्योम
		 * having everything error out.
		 */
		netअगर_device_detach (dev->net);
		usbnet_terminate_urbs(dev);
		__usbnet_status_stop_क्रमce(dev);

		/*
		 * reattach so runसमय management can use and
		 * wake the device
		 */
		netअगर_device_attach (dev->net);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_suspend);

पूर्णांक usbnet_resume (काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet		*dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा sk_buff          *skb;
	काष्ठा urb              *res;
	पूर्णांक                     retval;

	अगर (!--dev->suspend_count) अणु
		/* resume पूर्णांकerrupt URB अगर it was previously submitted */
		__usbnet_status_start_क्रमce(dev, GFP_NOIO);

		spin_lock_irq(&dev->txq.lock);
		जबतक ((res = usb_get_from_anchor(&dev->deferred))) अणु

			skb = (काष्ठा sk_buff *)res->context;
			retval = usb_submit_urb(res, GFP_ATOMIC);
			अगर (retval < 0) अणु
				dev_kमुक्त_skb_any(skb);
				kमुक्त(res->sg);
				usb_मुक्त_urb(res);
				usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
			पूर्ण अन्यथा अणु
				netअगर_trans_update(dev->net);
				__skb_queue_tail(&dev->txq, skb);
			पूर्ण
		पूर्ण

		smp_mb();
		clear_bit(EVENT_DEV_ASLEEP, &dev->flags);
		spin_unlock_irq(&dev->txq.lock);

		अगर (test_bit(EVENT_DEV_OPEN, &dev->flags)) अणु
			/* handle remote wakeup ASAP
			 * we cannot race against stop
			 */
			अगर (netअगर_device_present(dev->net) &&
				!समयr_pending(&dev->delay) &&
				!test_bit(EVENT_RX_HALT, &dev->flags))
					rx_alloc_submit(dev, GFP_NOIO);

			अगर (!(dev->txq.qlen >= TX_QLEN(dev)))
				netअगर_tx_wake_all_queues(dev->net);
			tasklet_schedule (&dev->bh);
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(EVENT_DEVICE_REPORT_IDLE, &dev->flags))
		usb_स्वतःpm_get_पूर्णांकerface_no_resume(पूर्णांकf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_resume);

/*
 * Either a subdriver implements manage_घातer, then it is assumed to always
 * be पढ़ोy to be suspended or it reports the पढ़ोiness to be suspended
 * explicitly
 */
व्योम usbnet_device_suggests_idle(काष्ठा usbnet *dev)
अणु
	अगर (!test_and_set_bit(EVENT_DEVICE_REPORT_IDLE, &dev->flags)) अणु
		dev->पूर्णांकf->needs_remote_wakeup = 1;
		usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(usbnet_device_suggests_idle);

/*
 * For devices that can करो without special commands
 */
पूर्णांक usbnet_manage_घातer(काष्ठा usbnet *dev, पूर्णांक on)
अणु
	dev->पूर्णांकf->needs_remote_wakeup = on;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(usbnet_manage_घातer);

व्योम usbnet_link_change(काष्ठा usbnet *dev, bool link, bool need_reset)
अणु
	/* update link after link is reseted */
	अगर (link && !need_reset)
		netअगर_carrier_on(dev->net);
	अन्यथा
		netअगर_carrier_off(dev->net);

	अगर (need_reset && link)
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
	अन्यथा
		usbnet_defer_kevent(dev, EVENT_LINK_CHANGE);
पूर्ण
EXPORT_SYMBOL(usbnet_link_change);

/*-------------------------------------------------------------------------*/
अटल पूर्णांक __usbnet_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
			     u16 value, u16 index, व्योम *data, u16 size)
अणु
	व्योम *buf = शून्य;
	पूर्णांक err = -ENOMEM;

	netdev_dbg(dev->net, "usbnet_read_cmd cmd=0x%02x reqtype=%02x"
		   " value=0x%04x index=0x%04x size=%d\n",
		   cmd, reqtype, value, index, size);

	अगर (size) अणु
		buf = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!buf)
			जाओ out;
	पूर्ण

	err = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
			      cmd, reqtype, value, index, buf, size,
			      USB_CTRL_GET_TIMEOUT);
	अगर (err > 0 && err <= size) अणु
		अगर (data)
			स_नकल(data, buf, err);
		अन्यथा
			netdev_dbg(dev->net,
				   "Huh? Data requested but thrown away.\n");
	पूर्ण
	kमुक्त(buf);
out:
	वापस err;
पूर्ण

अटल पूर्णांक __usbnet_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
			      u16 value, u16 index, स्थिर व्योम *data,
			      u16 size)
अणु
	व्योम *buf = शून्य;
	पूर्णांक err = -ENOMEM;

	netdev_dbg(dev->net, "usbnet_write_cmd cmd=0x%02x reqtype=%02x"
		   " value=0x%04x index=0x%04x size=%d\n",
		   cmd, reqtype, value, index, size);

	अगर (data) अणु
		buf = kmemdup(data, size, GFP_KERNEL);
		अगर (!buf)
			जाओ out;
	पूर्ण अन्यथा अणु
        अगर (size) अणु
            WARN_ON_ONCE(1);
            err = -EINVAL;
            जाओ out;
        पूर्ण
    पूर्ण

	err = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			      cmd, reqtype, value, index, buf, size,
			      USB_CTRL_SET_TIMEOUT);
	kमुक्त(buf);

out:
	वापस err;
पूर्ण

/*
 * The function can't be called inside suspend/resume callback,
 * otherwise deadlock will be caused.
 */
पूर्णांक usbnet_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
		    u16 value, u16 index, व्योम *data, u16 size)
अणु
	पूर्णांक ret;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf) < 0)
		वापस -ENODEV;
	ret = __usbnet_पढ़ो_cmd(dev, cmd, reqtype, value, index,
				data, size);
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_पढ़ो_cmd);

/*
 * The function can't be called inside suspend/resume callback,
 * otherwise deadlock will be caused.
 */
पूर्णांक usbnet_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
		     u16 value, u16 index, स्थिर व्योम *data, u16 size)
अणु
	पूर्णांक ret;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf) < 0)
		वापस -ENODEV;
	ret = __usbnet_ग_लिखो_cmd(dev, cmd, reqtype, value, index,
				 data, size);
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_ग_लिखो_cmd);

/*
 * The function can be called inside suspend/resume callback safely
 * and should only be called by suspend/resume callback generally.
 */
पूर्णांक usbnet_पढ़ो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
			  u16 value, u16 index, व्योम *data, u16 size)
अणु
	वापस __usbnet_पढ़ो_cmd(dev, cmd, reqtype, value, index,
				 data, size);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_पढ़ो_cmd_nopm);

/*
 * The function can be called inside suspend/resume callback safely
 * and should only be called by suspend/resume callback generally.
 */
पूर्णांक usbnet_ग_लिखो_cmd_nopm(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
			  u16 value, u16 index, स्थिर व्योम *data,
			  u16 size)
अणु
	वापस __usbnet_ग_लिखो_cmd(dev, cmd, reqtype, value, index,
				  data, size);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_ग_लिखो_cmd_nopm);

अटल व्योम usbnet_async_cmd_cb(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req = (काष्ठा usb_ctrlrequest *)urb->context;
	पूर्णांक status = urb->status;

	अगर (status < 0)
		dev_dbg(&urb->dev->dev, "%s failed with %d",
			__func__, status);

	kमुक्त(req);
	usb_मुक्त_urb(urb);
पूर्ण

/*
 * The caller must make sure that device can't be put पूर्णांकo suspend
 * state until the control URB completes.
 */
पूर्णांक usbnet_ग_लिखो_cmd_async(काष्ठा usbnet *dev, u8 cmd, u8 reqtype,
			   u16 value, u16 index, स्थिर व्योम *data, u16 size)
अणु
	काष्ठा usb_ctrlrequest *req = शून्य;
	काष्ठा urb *urb;
	पूर्णांक err = -ENOMEM;
	व्योम *buf = शून्य;

	netdev_dbg(dev->net, "usbnet_write_cmd cmd=0x%02x reqtype=%02x"
		   " value=0x%04x index=0x%04x size=%d\n",
		   cmd, reqtype, value, index, size);

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ fail;

	अगर (data) अणु
		buf = kmemdup(data, size, GFP_ATOMIC);
		अगर (!buf) अणु
			netdev_err(dev->net, "Error allocating buffer"
				   " in %s!\n", __func__);
			जाओ fail_मुक्त;
		पूर्ण
	पूर्ण

	req = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_ATOMIC);
	अगर (!req)
		जाओ fail_मुक्त_buf;

	req->bRequestType = reqtype;
	req->bRequest = cmd;
	req->wValue = cpu_to_le16(value);
	req->wIndex = cpu_to_le16(index);
	req->wLength = cpu_to_le16(size);

	usb_fill_control_urb(urb, dev->udev,
			     usb_sndctrlpipe(dev->udev, 0),
			     (व्योम *)req, buf, size,
			     usbnet_async_cmd_cb, req);
	urb->transfer_flags |= URB_FREE_BUFFER;

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		netdev_err(dev->net, "Error submitting the control"
			   " message: status=%d\n", err);
		जाओ fail_मुक्त;
	पूर्ण
	वापस 0;

fail_मुक्त_buf:
	kमुक्त(buf);
fail_मुक्त:
	kमुक्त(req);
	usb_मुक्त_urb(urb);
fail:
	वापस err;

पूर्ण
EXPORT_SYMBOL_GPL(usbnet_ग_लिखो_cmd_async);
/*-------------------------------------------------------------------------*/

अटल पूर्णांक __init usbnet_init(व्योम)
अणु
	/* Compiler should optimize this out. */
	BUILD_BUG_ON(
		माप_field(काष्ठा sk_buff, cb) < माप(काष्ठा skb_data));

	eth_अक्रमom_addr(node_id);
	वापस 0;
पूर्ण
module_init(usbnet_init);

अटल व्योम __निकास usbnet_निकास(व्योम)
अणु
पूर्ण
module_निकास(usbnet_निकास);

MODULE_AUTHOR("David Brownell");
MODULE_DESCRIPTION("USB network driver framework");
MODULE_LICENSE("GPL");
