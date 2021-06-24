<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN driver क्रम PEAK System USB adapters
 * Derived from the PCAN project file driver/src/pcan_usb_core.c
 *
 * Copyright (C) 2003-2010 PEAK System-Technik GmbH
 * Copyright (C) 2010-2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 *
 * Many thanks to Klaus Hitschler <klaus.hitschler@gmx.de>
 */
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>
#समावेश <linux/ethtool.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>

#समावेश "pcan_usb_core.h"

MODULE_AUTHOR("Stephane Grosjean <s.grosjean@peak-system.com>");
MODULE_DESCRIPTION("CAN driver for PEAK-System USB adapters");
MODULE_LICENSE("GPL v2");

/* Table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id peak_usb_table[] = अणु
	अणु
		USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USB_PRODUCT_ID),
		.driver_info = (kernel_uदीर्घ_t)&pcan_usb,
	पूर्ण, अणु
		USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBPRO_PRODUCT_ID),
		.driver_info = (kernel_uदीर्घ_t)&pcan_usb_pro,
	पूर्ण, अणु
		USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBFD_PRODUCT_ID),
		.driver_info = (kernel_uदीर्घ_t)&pcan_usb_fd,
	पूर्ण, अणु
		USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBPROFD_PRODUCT_ID),
		.driver_info = (kernel_uदीर्घ_t)&pcan_usb_pro_fd,
	पूर्ण, अणु
		USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBCHIP_PRODUCT_ID),
		.driver_info = (kernel_uदीर्घ_t)&pcan_usb_chip,
	पूर्ण, अणु
		USB_DEVICE(PCAN_USB_VENDOR_ID, PCAN_USBX6_PRODUCT_ID),
		.driver_info = (kernel_uदीर्घ_t)&pcan_usb_x6,
	पूर्ण, अणु
		/* Terminating entry */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, peak_usb_table);

/*
 * dump memory
 */
#घोषणा DUMP_WIDTH	16
व्योम pcan_dump_mem(अक्षर *prompt, व्योम *p, पूर्णांक l)
अणु
	pr_info("%s dumping %s (%d bytes):\n",
		PCAN_USB_DRIVER_NAME, prompt ? prompt : "memory", l);
	prपूर्णांक_hex_dump(KERN_INFO, PCAN_USB_DRIVER_NAME " ", DUMP_PREFIX_NONE,
		       DUMP_WIDTH, 1, p, l, false);
पूर्ण

/*
 * initialize a समय_ref object with usb adapter own settings
 */
व्योम peak_usb_init_समय_ref(काष्ठा peak_समय_ref *समय_ref,
			    स्थिर काष्ठा peak_usb_adapter *adapter)
अणु
	अगर (समय_ref) अणु
		स_रखो(समय_ref, 0, माप(काष्ठा peak_समय_ref));
		समय_ref->adapter = adapter;
	पूर्ण
पूर्ण

/*
 * someबार, another now may be  more recent than current one...
 */
व्योम peak_usb_update_ts_now(काष्ठा peak_समय_ref *समय_ref, u32 ts_now)
अणु
	समय_ref->ts_dev_2 = ts_now;

	/* should रुको at least two passes beक्रमe computing */
	अगर (kसमय_प्रकारo_ns(समय_ref->tv_host) > 0) अणु
		u32 delta_ts = समय_ref->ts_dev_2 - समय_ref->ts_dev_1;

		अगर (समय_ref->ts_dev_2 < समय_ref->ts_dev_1)
			delta_ts &= (1 << समय_ref->adapter->ts_used_bits) - 1;

		समय_ref->ts_total += delta_ts;
	पूर्ण
पूर्ण

/*
 * रेजिस्टर device बारtamp as now
 */
व्योम peak_usb_set_ts_now(काष्ठा peak_समय_ref *समय_ref, u32 ts_now)
अणु
	अगर (kसमय_प्रकारo_ns(समय_ref->tv_host_0) == 0) अणु
		/* use monotonic घड़ी to correctly compute further deltas */
		समय_ref->tv_host_0 = kसमय_get();
		समय_ref->tv_host = kसमय_set(0, 0);
	पूर्ण अन्यथा अणु
		/*
		 * delta_us should not be >= 2^32 => delta should be < 4294s
		 * handle 32-bits wrapping here: अगर count of s. reaches 4200,
		 * reset counters and change समय base
		 */
		अगर (kसमय_प्रकारo_ns(समय_ref->tv_host)) अणु
			kसमय_प्रकार delta = kसमय_sub(समय_ref->tv_host,
						  समय_ref->tv_host_0);
			अगर (kसमय_प्रकारo_ns(delta) > (4200ull * NSEC_PER_SEC)) अणु
				समय_ref->tv_host_0 = समय_ref->tv_host;
				समय_ref->ts_total = 0;
			पूर्ण
		पूर्ण

		समय_ref->tv_host = kसमय_get();
		समय_ref->tick_count++;
	पूर्ण

	समय_ref->ts_dev_1 = समय_ref->ts_dev_2;
	peak_usb_update_ts_now(समय_ref, ts_now);
पूर्ण

/*
 * compute समय according to current ts and समय_ref data
 */
व्योम peak_usb_get_ts_समय(काष्ठा peak_समय_ref *समय_ref, u32 ts, kसमय_प्रकार *समय)
अणु
	/* protect from getting समय beक्रमe setting now */
	अगर (kसमय_प्रकारo_ns(समय_ref->tv_host)) अणु
		u64 delta_us;
		s64 delta_ts = 0;

		/* General हाल: dev_ts_1 < dev_ts_2 < ts, with:
		 *
		 * - dev_ts_1 = previous sync बारtamp
		 * - dev_ts_2 = last sync बारtamp
		 * - ts = event बारtamp
		 * - ts_period = known sync period (theoretical)
		 *             ~ dev_ts2 - dev_ts1
		 * *but*:
		 *
		 * - समय counters wrap (see adapter->ts_used_bits)
		 * - someबार, dev_ts_1 < ts < dev_ts2
		 *
		 * "normal" हाल (sync समय counters increase):
		 * must take पूर्णांकo account हाल when ts wraps (tsw)
		 *
		 *      < ts_period > <          >
		 *     |             |            |
		 *  ---+--------+----+-------0-+--+-->
		 *     ts_dev_1 |    ts_dev_2  |
		 *              ts             tsw
		 */
		अगर (समय_ref->ts_dev_1 < समय_ref->ts_dev_2) अणु
			/* हाल when event समय (tsw) wraps */
			अगर (ts < समय_ref->ts_dev_1)
				delta_ts = BIT_ULL(समय_ref->adapter->ts_used_bits);

		/* Otherwise, sync समय counter (ts_dev_2) has wrapped:
		 * handle हाल when event समय (tsn) hasn't.
		 *
		 *      < ts_period > <          >
		 *     |             |            |
		 *  ---+--------+--0-+---------+--+-->
		 *     ts_dev_1 |    ts_dev_2  |
		 *              tsn            ts
		 */
		पूर्ण अन्यथा अगर (समय_ref->ts_dev_1 < ts) अणु
			delta_ts = -BIT_ULL(समय_ref->adapter->ts_used_bits);
		पूर्ण

		/* add delay between last sync and event बारtamps */
		delta_ts += (चिन्हित पूर्णांक)(ts - समय_ref->ts_dev_2);

		/* add समय from beginning to last sync */
		delta_ts += समय_ref->ts_total;

		/* convert ticks number पूर्णांकo microseconds */
		delta_us = delta_ts * समय_ref->adapter->us_per_ts_scale;
		delta_us >>= समय_ref->adapter->us_per_ts_shअगरt;

		*समय = kसमय_add_us(समय_ref->tv_host_0, delta_us);
	पूर्ण अन्यथा अणु
		*समय = kसमय_get();
	पूर्ण
पूर्ण

/*
 * post received skb after having set any hw बारtamp
 */
पूर्णांक peak_usb_netअगर_rx(काष्ठा sk_buff *skb,
		      काष्ठा peak_समय_ref *समय_ref, u32 ts_low)
अणु
	काष्ठा skb_shared_hwtstamps *hwts = skb_hwtstamps(skb);

	peak_usb_get_ts_समय(समय_ref, ts_low, &hwts->hwtstamp);

	वापस netअगर_rx(skb);
पूर्ण

/*
 * callback क्रम bulk Rx urb
 */
अटल व्योम peak_usb_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा peak_usb_device *dev = urb->context;
	काष्ठा net_device *netdev;
	पूर्णांक err;

	netdev = dev->netdev;

	अगर (!netअगर_device_present(netdev))
		वापस;

	/* check reception status */
	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;

	हाल -EILSEQ:
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		अगर (net_ratelimit())
			netdev_err(netdev,
				   "Rx urb aborted (%d)\n", urb->status);
		जाओ resubmit_urb;
	पूर्ण

	/* protect from any incoming empty msgs */
	अगर ((urb->actual_length > 0) && (dev->adapter->dev_decode_buf)) अणु
		/* handle these kinds of msgs only अगर _start callback called */
		अगर (dev->state & PCAN_USB_STATE_STARTED) अणु
			err = dev->adapter->dev_decode_buf(dev, urb);
			अगर (err)
				pcan_dump_mem("received usb message",
					      urb->transfer_buffer,
					      urb->transfer_buffer_length);
		पूर्ण
	पूर्ण

resubmit_urb:
	usb_fill_bulk_urb(urb, dev->udev,
		usb_rcvbulkpipe(dev->udev, dev->ep_msg_in),
		urb->transfer_buffer, dev->adapter->rx_buffer_size,
		peak_usb_पढ़ो_bulk_callback, dev);

	usb_anchor_urb(urb, &dev->rx_submitted);
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (!err)
		वापस;

	usb_unanchor_urb(urb);

	अगर (err == -ENODEV)
		netअगर_device_detach(netdev);
	अन्यथा
		netdev_err(netdev, "failed resubmitting read bulk urb: %d\n",
			   err);
पूर्ण

/*
 * callback क्रम bulk Tx urb
 */
अटल व्योम peak_usb_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा peak_tx_urb_context *context = urb->context;
	काष्ठा peak_usb_device *dev;
	काष्ठा net_device *netdev;

	BUG_ON(!context);

	dev = context->dev;
	netdev = dev->netdev;

	atomic_dec(&dev->active_tx_urbs);

	अगर (!netअगर_device_present(netdev))
		वापस;

	/* check tx status */
	चयन (urb->status) अणु
	हाल 0:
		/* transmission complete */
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += context->data_len;

		/* prevent tx समयout */
		netअगर_trans_update(netdev);
		अवरोध;

	हाल -EPROTO:
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		अवरोध;

	शेष:
		अगर (net_ratelimit())
			netdev_err(netdev, "Tx urb aborted (%d)\n",
				   urb->status);
		अवरोध;
	पूर्ण

	/* should always release echo skb and corresponding context */
	can_get_echo_skb(netdev, context->echo_index, शून्य);
	context->echo_index = PCAN_USB_MAX_TX_URBS;

	/* करो wakeup tx queue in हाल of success only */
	अगर (!urb->status)
		netअगर_wake_queue(netdev);
पूर्ण

/*
 * called by netdev to send one skb on the CAN पूर्णांकerface.
 */
अटल netdev_tx_t peak_usb_nकरो_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *netdev)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	काष्ठा peak_tx_urb_context *context = शून्य;
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	काष्ठा urb *urb;
	u8 *obuf;
	पूर्णांक i, err;
	माप_प्रकार size = dev->adapter->tx_buffer_size;

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	क्रम (i = 0; i < PCAN_USB_MAX_TX_URBS; i++)
		अगर (dev->tx_contexts[i].echo_index == PCAN_USB_MAX_TX_URBS) अणु
			context = dev->tx_contexts + i;
			अवरोध;
		पूर्ण

	अगर (!context) अणु
		/* should not occur except during restart */
		वापस NETDEV_TX_BUSY;
	पूर्ण

	urb = context->urb;
	obuf = urb->transfer_buffer;

	err = dev->adapter->dev_encode_msg(dev, skb, obuf, &size);
	अगर (err) अणु
		अगर (net_ratelimit())
			netdev_err(netdev, "packet dropped\n");
		dev_kमुक्त_skb(skb);
		stats->tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	context->echo_index = i;

	/* Note: this works with CANFD frames too */
	context->data_len = cfd->len;

	usb_anchor_urb(urb, &dev->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&dev->active_tx_urbs);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		can_मुक्त_echo_skb(netdev, context->echo_index, शून्य);

		usb_unanchor_urb(urb);

		/* this context is not used in fact */
		context->echo_index = PCAN_USB_MAX_TX_URBS;

		atomic_dec(&dev->active_tx_urbs);

		चयन (err) अणु
		हाल -ENODEV:
			netअगर_device_detach(netdev);
			अवरोध;
		शेष:
			netdev_warn(netdev, "tx urb submitting failed err=%d\n",
				    err);
			fallthrough;
		हाल -ENOENT:
			/* cable unplugged */
			stats->tx_dropped++;
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_trans_update(netdev);

		/* slow करोwn tx path */
		अगर (atomic_पढ़ो(&dev->active_tx_urbs) >= PCAN_USB_MAX_TX_URBS)
			netअगर_stop_queue(netdev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * start the CAN पूर्णांकerface.
 * Rx and Tx urbs are allocated here. Rx urbs are submitted here.
 */
अटल पूर्णांक peak_usb_start(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा net_device *netdev = dev->netdev;
	पूर्णांक err, i;

	क्रम (i = 0; i < PCAN_USB_MAX_RX_URBS; i++) अणु
		काष्ठा urb *urb;
		u8 *buf;

		/* create a URB, and a buffer क्रम it, to receive usb messages */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		buf = kदो_स्मृति(dev->adapter->rx_buffer_size, GFP_KERNEL);
		अगर (!buf) अणु
			usb_मुक्त_urb(urb);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		usb_fill_bulk_urb(urb, dev->udev,
			usb_rcvbulkpipe(dev->udev, dev->ep_msg_in),
			buf, dev->adapter->rx_buffer_size,
			peak_usb_पढ़ो_bulk_callback, dev);

		/* ask last usb_मुक्त_urb() to also kमुक्त() transfer_buffer */
		urb->transfer_flags |= URB_FREE_BUFFER;
		usb_anchor_urb(urb, &dev->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			अगर (err == -ENODEV)
				netअगर_device_detach(dev->netdev);

			usb_unanchor_urb(urb);
			kमुक्त(buf);
			usb_मुक्त_urb(urb);
			अवरोध;
		पूर्ण

		/* drop reference, USB core will take care of मुक्तing it */
		usb_मुक्त_urb(urb);
	पूर्ण

	/* did we submit any URBs? Warn अगर we was not able to submit all urbs */
	अगर (i < PCAN_USB_MAX_RX_URBS) अणु
		अगर (i == 0) अणु
			netdev_err(netdev, "couldn't setup any rx URB\n");
			वापस err;
		पूर्ण

		netdev_warn(netdev, "rx performance may be slow\n");
	पूर्ण

	/* pre-alloc tx buffers and corresponding urbs */
	क्रम (i = 0; i < PCAN_USB_MAX_TX_URBS; i++) अणु
		काष्ठा peak_tx_urb_context *context;
		काष्ठा urb *urb;
		u8 *buf;

		/* create a URB and a buffer क्रम it, to transmit usb messages */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		buf = kदो_स्मृति(dev->adapter->tx_buffer_size, GFP_KERNEL);
		अगर (!buf) अणु
			usb_मुक्त_urb(urb);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		context = dev->tx_contexts + i;
		context->dev = dev;
		context->urb = urb;

		usb_fill_bulk_urb(urb, dev->udev,
			usb_sndbulkpipe(dev->udev, dev->ep_msg_out),
			buf, dev->adapter->tx_buffer_size,
			peak_usb_ग_लिखो_bulk_callback, context);

		/* ask last usb_मुक्त_urb() to also kमुक्त() transfer_buffer */
		urb->transfer_flags |= URB_FREE_BUFFER;
	पूर्ण

	/* warn अगर we were not able to allocate enough tx contexts */
	अगर (i < PCAN_USB_MAX_TX_URBS) अणु
		अगर (i == 0) अणु
			netdev_err(netdev, "couldn't setup any tx URB\n");
			जाओ err_tx;
		पूर्ण

		netdev_warn(netdev, "tx performance may be slow\n");
	पूर्ण

	अगर (dev->adapter->dev_start) अणु
		err = dev->adapter->dev_start(dev);
		अगर (err)
			जाओ err_adapter;
	पूर्ण

	dev->state |= PCAN_USB_STATE_STARTED;

	/* can set bus on now */
	अगर (dev->adapter->dev_set_bus) अणु
		err = dev->adapter->dev_set_bus(dev, 1);
		अगर (err)
			जाओ err_adapter;
	पूर्ण

	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस 0;

err_adapter:
	अगर (err == -ENODEV)
		netअगर_device_detach(dev->netdev);

	netdev_warn(netdev, "couldn't submit control: %d\n", err);

	क्रम (i = 0; i < PCAN_USB_MAX_TX_URBS; i++) अणु
		usb_मुक्त_urb(dev->tx_contexts[i].urb);
		dev->tx_contexts[i].urb = शून्य;
	पूर्ण
err_tx:
	usb_समाप्त_anchored_urbs(&dev->rx_submitted);

	वापस err;
पूर्ण

/*
 * called by netdev to खोलो the corresponding CAN पूर्णांकerface.
 */
अटल पूर्णांक peak_usb_nकरो_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	पूर्णांक err;

	/* common खोलो */
	err = खोलो_candev(netdev);
	अगर (err)
		वापस err;

	/* finally start device */
	err = peak_usb_start(dev);
	अगर (err) अणु
		netdev_err(netdev, "couldn't start device: %d\n", err);
		बंद_candev(netdev);
		वापस err;
	पूर्ण

	netअगर_start_queue(netdev);

	वापस 0;
पूर्ण

/*
 * unlink in-flight Rx and Tx urbs and मुक्त their memory.
 */
अटल व्योम peak_usb_unlink_all_urbs(काष्ठा peak_usb_device *dev)
अणु
	पूर्णांक i;

	/* मुक्त all Rx (submitted) urbs */
	usb_समाप्त_anchored_urbs(&dev->rx_submitted);

	/* मुक्त unsubmitted Tx urbs first */
	क्रम (i = 0; i < PCAN_USB_MAX_TX_URBS; i++) अणु
		काष्ठा urb *urb = dev->tx_contexts[i].urb;

		अगर (!urb ||
		    dev->tx_contexts[i].echo_index != PCAN_USB_MAX_TX_URBS) अणु
			/*
			 * this urb is alपढ़ोy released or always submitted,
			 * let usb core मुक्त by itself
			 */
			जारी;
		पूर्ण

		usb_मुक्त_urb(urb);
		dev->tx_contexts[i].urb = शून्य;
	पूर्ण

	/* then मुक्त all submitted Tx urbs */
	usb_समाप्त_anchored_urbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);
पूर्ण

/*
 * called by netdev to बंद the corresponding CAN पूर्णांकerface.
 */
अटल पूर्णांक peak_usb_nकरो_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);

	dev->state &= ~PCAN_USB_STATE_STARTED;
	netअगर_stop_queue(netdev);

	बंद_candev(netdev);

	dev->can.state = CAN_STATE_STOPPED;

	/* unlink all pending urbs and मुक्त used memory */
	peak_usb_unlink_all_urbs(dev);

	अगर (dev->adapter->dev_stop)
		dev->adapter->dev_stop(dev);

	/* can set bus off now */
	अगर (dev->adapter->dev_set_bus) अणु
		पूर्णांक err = dev->adapter->dev_set_bus(dev, 0);

		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * handle end of रुकोing क्रम the device to reset
 */
व्योम peak_usb_restart_complete(काष्ठा peak_usb_device *dev)
अणु
	/* finally MUST update can state */
	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	/* netdev queue can be awaken now */
	netअगर_wake_queue(dev->netdev);
पूर्ण

व्योम peak_usb_async_complete(काष्ठा urb *urb)
अणु
	kमुक्त(urb->transfer_buffer);
	usb_मुक्त_urb(urb);
पूर्ण

/*
 * device (स्वतः-)restart mechanism runs in a समयr context =>
 * MUST handle restart with asynchronous usb transfers
 */
अटल पूर्णांक peak_usb_restart(काष्ठा peak_usb_device *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक err;
	u8 *buf;

	/*
	 * अगर device करोesn't define any asynchronous restart handler, simply
	 * wake the netdev queue up
	 */
	अगर (!dev->adapter->dev_restart_async) अणु
		peak_usb_restart_complete(dev);
		वापस 0;
	पूर्ण

	/* first allocate a urb to handle the asynchronous steps */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		वापस -ENOMEM;

	/* also allocate enough space क्रम the commands to send */
	buf = kदो_स्मृति(PCAN_USB_MAX_CMD_LEN, GFP_ATOMIC);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	/* call the device specअगरic handler क्रम the restart */
	err = dev->adapter->dev_restart_async(dev, urb, buf);
	अगर (!err)
		वापस 0;

	kमुक्त(buf);
	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

/*
 * candev callback used to change CAN mode.
 * Warning: this is called from a समयr context!
 */
अटल पूर्णांक peak_usb_set_mode(काष्ठा net_device *netdev, क्रमागत can_mode mode)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = peak_usb_restart(dev);
		अगर (err)
			netdev_err(netdev, "couldn't start device (err %d)\n",
				   err);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

/*
 * candev callback used to set device nominal/arbitration bitrate.
 */
अटल पूर्णांक peak_usb_set_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	स्थिर काष्ठा peak_usb_adapter *pa = dev->adapter;

	अगर (pa->dev_set_bittiming) अणु
		काष्ठा can_bittiming *bt = &dev->can.bittiming;
		पूर्णांक err = pa->dev_set_bittiming(dev, bt);

		अगर (err)
			netdev_info(netdev, "couldn't set bitrate (err %d)\n",
				    err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * candev callback used to set device data bitrate.
 */
अटल पूर्णांक peak_usb_set_data_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा peak_usb_device *dev = netdev_priv(netdev);
	स्थिर काष्ठा peak_usb_adapter *pa = dev->adapter;

	अगर (pa->dev_set_data_bittiming) अणु
		काष्ठा can_bittiming *bt = &dev->can.data_bittiming;
		पूर्णांक err = pa->dev_set_data_bittiming(dev, bt);

		अगर (err)
			netdev_info(netdev,
				    "couldn't set data bitrate (err %d)\n",
				    err);

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops peak_usb_netdev_ops = अणु
	.nकरो_खोलो = peak_usb_nकरो_खोलो,
	.nकरो_stop = peak_usb_nकरो_stop,
	.nकरो_start_xmit = peak_usb_nकरो_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

/*
 * create one device which is attached to CAN controller #ctrl_idx of the
 * usb adapter.
 */
अटल पूर्णांक peak_usb_create_dev(स्थिर काष्ठा peak_usb_adapter *peak_usb_adapter,
			       काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक ctrl_idx)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक माप_candev = peak_usb_adapter->माप_dev_निजी;
	काष्ठा peak_usb_device *dev;
	काष्ठा net_device *netdev;
	पूर्णांक i, err;
	u16 पंचांगp16;

	अगर (माप_candev < माप(काष्ठा peak_usb_device))
		माप_candev = माप(काष्ठा peak_usb_device);

	netdev = alloc_candev(माप_candev, PCAN_USB_MAX_TX_URBS);
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "%s: couldn't alloc candev\n",
			PCAN_USB_DRIVER_NAME);
		वापस -ENOMEM;
	पूर्ण

	dev = netdev_priv(netdev);

	/* allocate a buffer large enough to send commands */
	dev->cmd_buf = kzalloc(PCAN_USB_MAX_CMD_LEN, GFP_KERNEL);
	अगर (!dev->cmd_buf) अणु
		err = -ENOMEM;
		जाओ lbl_मुक्त_candev;
	पूर्ण

	dev->udev = usb_dev;
	dev->netdev = netdev;
	dev->adapter = peak_usb_adapter;
	dev->ctrl_idx = ctrl_idx;
	dev->state = PCAN_USB_STATE_CONNECTED;

	dev->ep_msg_in = peak_usb_adapter->ep_msg_in;
	dev->ep_msg_out = peak_usb_adapter->ep_msg_out[ctrl_idx];

	dev->can.घड़ी = peak_usb_adapter->घड़ी;
	dev->can.bittiming_स्थिर = peak_usb_adapter->bittiming_स्थिर;
	dev->can.करो_set_bittiming = peak_usb_set_bittiming;
	dev->can.data_bittiming_स्थिर = peak_usb_adapter->data_bittiming_स्थिर;
	dev->can.करो_set_data_bittiming = peak_usb_set_data_bittiming;
	dev->can.करो_set_mode = peak_usb_set_mode;
	dev->can.करो_get_berr_counter = peak_usb_adapter->करो_get_berr_counter;
	dev->can.ctrlmode_supported = peak_usb_adapter->ctrlmode_supported;

	netdev->netdev_ops = &peak_usb_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	/* add ethtool support */
	netdev->ethtool_ops = peak_usb_adapter->ethtool_ops;

	init_usb_anchor(&dev->rx_submitted);

	init_usb_anchor(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);

	क्रम (i = 0; i < PCAN_USB_MAX_TX_URBS; i++)
		dev->tx_contexts[i].echo_index = PCAN_USB_MAX_TX_URBS;

	dev->prev_siblings = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);
	netdev->dev_id = ctrl_idx;

	err = रेजिस्टर_candev(netdev);
	अगर (err) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register CAN device: %d\n", err);
		जाओ lbl_restore_पूर्णांकf_data;
	पूर्ण

	अगर (dev->prev_siblings)
		(dev->prev_siblings)->next_siblings = dev;

	/* keep hw revision पूर्णांकo the netdevice */
	पंचांगp16 = le16_to_cpu(usb_dev->descriptor.bcdDevice);
	dev->device_rev = पंचांगp16 >> 8;

	अगर (dev->adapter->dev_init) अणु
		err = dev->adapter->dev_init(dev);
		अगर (err)
			जाओ lbl_unरेजिस्टर_candev;
	पूर्ण

	/* set bus off */
	अगर (dev->adapter->dev_set_bus) अणु
		err = dev->adapter->dev_set_bus(dev, 0);
		अगर (err)
			जाओ adap_dev_मुक्त;
	पूर्ण

	/* get device number early */
	अगर (dev->adapter->dev_get_device_id)
		dev->adapter->dev_get_device_id(dev, &dev->device_number);

	netdev_info(netdev, "attached to %s channel %u (device %u)\n",
			peak_usb_adapter->name, ctrl_idx, dev->device_number);

	वापस 0;

adap_dev_मुक्त:
	अगर (dev->adapter->dev_मुक्त)
		dev->adapter->dev_मुक्त(dev);

lbl_unरेजिस्टर_candev:
	unरेजिस्टर_candev(netdev);

lbl_restore_पूर्णांकf_data:
	usb_set_पूर्णांकfdata(पूर्णांकf, dev->prev_siblings);
	kमुक्त(dev->cmd_buf);

lbl_मुक्त_candev:
	मुक्त_candev(netdev);

	वापस err;
पूर्ण

/*
 * called by the usb core when the device is unplugged from the प्रणाली
 */
अटल व्योम peak_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा peak_usb_device *dev;
	काष्ठा peak_usb_device *dev_prev_siblings;

	/* unरेजिस्टर as many netdev devices as siblings */
	क्रम (dev = usb_get_पूर्णांकfdata(पूर्णांकf); dev; dev = dev_prev_siblings) अणु
		काष्ठा net_device *netdev = dev->netdev;
		अक्षर name[IFNAMSIZ];

		dev_prev_siblings = dev->prev_siblings;
		dev->state &= ~PCAN_USB_STATE_CONNECTED;
		strlcpy(name, netdev->name, IFNAMSIZ);

		unरेजिस्टर_netdev(netdev);

		kमुक्त(dev->cmd_buf);
		dev->next_siblings = शून्य;
		अगर (dev->adapter->dev_मुक्त)
			dev->adapter->dev_मुक्त(dev);

		मुक्त_candev(netdev);
		dev_info(&पूर्णांकf->dev, "%s removed\n", name);
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

/*
 * probe function क्रम new PEAK-System devices
 */
अटल पूर्णांक peak_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	स्थिर काष्ठा peak_usb_adapter *peak_usb_adapter;
	पूर्णांक i, err = -ENOMEM;

	/* get corresponding PCAN-USB adapter */
	peak_usb_adapter = (स्थिर काष्ठा peak_usb_adapter *)id->driver_info;

	/* got corresponding adapter: check अगर it handles current पूर्णांकerface */
	अगर (peak_usb_adapter->पूर्णांकf_probe) अणु
		err = peak_usb_adapter->पूर्णांकf_probe(पूर्णांकf);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < peak_usb_adapter->ctrl_count; i++) अणु
		err = peak_usb_create_dev(peak_usb_adapter, पूर्णांकf, i);
		अगर (err) अणु
			/* deरेजिस्टर alपढ़ोy created devices */
			peak_usb_disconnect(पूर्णांकf);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver peak_usb_driver = अणु
	.name = PCAN_USB_DRIVER_NAME,
	.disconnect = peak_usb_disconnect,
	.probe = peak_usb_probe,
	.id_table = peak_usb_table,
पूर्ण;

अटल पूर्णांक __init peak_usb_init(व्योम)
अणु
	पूर्णांक err;

	/* रेजिस्टर this driver with the USB subप्रणाली */
	err = usb_रेजिस्टर(&peak_usb_driver);
	अगर (err)
		pr_err("%s: usb_register failed (err %d)\n",
			PCAN_USB_DRIVER_NAME, err);

	वापस err;
पूर्ण

अटल पूर्णांक peak_usb_करो_device_निकास(काष्ठा device *d, व्योम *arg)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(d);
	काष्ठा peak_usb_device *dev;

	/* stop as many netdev devices as siblings */
	क्रम (dev = usb_get_पूर्णांकfdata(पूर्णांकf); dev; dev = dev->prev_siblings) अणु
		काष्ठा net_device *netdev = dev->netdev;

		अगर (netअगर_device_present(netdev))
			अगर (dev->adapter->dev_निकास)
				dev->adapter->dev_निकास(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास peak_usb_निकास(व्योम)
अणु
	पूर्णांक err;

	/* last chance करो send any synchronous commands here */
	err = driver_क्रम_each_device(&peak_usb_driver.drvwrap.driver, शून्य,
				     शून्य, peak_usb_करो_device_निकास);
	अगर (err)
		pr_err("%s: failed to stop all can devices (err %d)\n",
			PCAN_USB_DRIVER_NAME, err);

	/* deरेजिस्टर this driver with the USB subप्रणाली */
	usb_deरेजिस्टर(&peak_usb_driver);

	pr_info("%s: PCAN-USB interfaces driver unloaded\n",
		PCAN_USB_DRIVER_NAME);
पूर्ण

module_init(peak_usb_init);
module_निकास(peak_usb_निकास);
