<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* CAN driver क्रम Geschwister Schneider USB/CAN devices
 * and bytewerk.org candleLight USB CAN पूर्णांकerfaces.
 *
 * Copyright (C) 2013-2016 Geschwister Schneider Technologie-,
 * Entwicklungs- und Vertriebs UG (Haftungsbeschrथअnkt).
 * Copyright (C) 2016 Hubert Denkmair
 *
 * Many thanks to all socketcan devs!
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>

/* Device specअगरic स्थिरants */
#घोषणा USB_GSUSB_1_VENDOR_ID      0x1d50
#घोषणा USB_GSUSB_1_PRODUCT_ID     0x606f

#घोषणा USB_CANDLELIGHT_VENDOR_ID  0x1209
#घोषणा USB_CANDLELIGHT_PRODUCT_ID 0x2323

#घोषणा GSUSB_ENDPOINT_IN          1
#घोषणा GSUSB_ENDPOINT_OUT         2

/* Device specअगरic स्थिरants */
क्रमागत gs_usb_breq अणु
	GS_USB_BREQ_HOST_FORMAT = 0,
	GS_USB_BREQ_BITTIMING,
	GS_USB_BREQ_MODE,
	GS_USB_BREQ_BERR,
	GS_USB_BREQ_BT_CONST,
	GS_USB_BREQ_DEVICE_CONFIG,
	GS_USB_BREQ_TIMESTAMP,
	GS_USB_BREQ_IDENTIFY,
पूर्ण;

क्रमागत gs_can_mode अणु
	/* reset a channel. turns it off */
	GS_CAN_MODE_RESET = 0,
	/* starts a channel */
	GS_CAN_MODE_START
पूर्ण;

क्रमागत gs_can_state अणु
	GS_CAN_STATE_ERROR_ACTIVE = 0,
	GS_CAN_STATE_ERROR_WARNING,
	GS_CAN_STATE_ERROR_PASSIVE,
	GS_CAN_STATE_BUS_OFF,
	GS_CAN_STATE_STOPPED,
	GS_CAN_STATE_SLEEPING
पूर्ण;

क्रमागत gs_can_identअगरy_mode अणु
	GS_CAN_IDENTIFY_OFF = 0,
	GS_CAN_IDENTIFY_ON
पूर्ण;

/* data types passed between host and device */

/* The firmware on the original USB2CAN by Geschwister Schneider
 * Technologie Entwicklungs- und Vertriebs UG exchanges all data
 * between the host and the device in host byte order. This is करोne
 * with the काष्ठा gs_host_config::byte_order member, which is sent
 * first to indicate the desired byte order.
 *
 * The widely used खोलो source firmware candleLight करोesn't support
 * this feature and exchanges the data in little endian byte order.
 */
काष्ठा gs_host_config अणु
	__le32 byte_order;
पूर्ण __packed;

काष्ठा gs_device_config अणु
	u8 reserved1;
	u8 reserved2;
	u8 reserved3;
	u8 icount;
	__le32 sw_version;
	__le32 hw_version;
पूर्ण __packed;

#घोषणा GS_CAN_MODE_NORMAL               0
#घोषणा GS_CAN_MODE_LISTEN_ONLY          BIT(0)
#घोषणा GS_CAN_MODE_LOOP_BACK            BIT(1)
#घोषणा GS_CAN_MODE_TRIPLE_SAMPLE        BIT(2)
#घोषणा GS_CAN_MODE_ONE_SHOT             BIT(3)

काष्ठा gs_device_mode अणु
	__le32 mode;
	__le32 flags;
पूर्ण __packed;

काष्ठा gs_device_state अणु
	__le32 state;
	__le32 rxerr;
	__le32 txerr;
पूर्ण __packed;

काष्ठा gs_device_bittiming अणु
	__le32 prop_seg;
	__le32 phase_seg1;
	__le32 phase_seg2;
	__le32 sjw;
	__le32 brp;
पूर्ण __packed;

काष्ठा gs_identअगरy_mode अणु
	__le32 mode;
पूर्ण __packed;

#घोषणा GS_CAN_FEATURE_LISTEN_ONLY      BIT(0)
#घोषणा GS_CAN_FEATURE_LOOP_BACK        BIT(1)
#घोषणा GS_CAN_FEATURE_TRIPLE_SAMPLE    BIT(2)
#घोषणा GS_CAN_FEATURE_ONE_SHOT         BIT(3)
#घोषणा GS_CAN_FEATURE_HW_TIMESTAMP     BIT(4)
#घोषणा GS_CAN_FEATURE_IDENTIFY         BIT(5)

काष्ठा gs_device_bt_स्थिर अणु
	__le32 feature;
	__le32 fclk_can;
	__le32 tseg1_min;
	__le32 tseg1_max;
	__le32 tseg2_min;
	__le32 tseg2_max;
	__le32 sjw_max;
	__le32 brp_min;
	__le32 brp_max;
	__le32 brp_inc;
पूर्ण __packed;

#घोषणा GS_CAN_FLAG_OVERFLOW 1

काष्ठा gs_host_frame अणु
	u32 echo_id;
	__le32 can_id;

	u8 can_dlc;
	u8 channel;
	u8 flags;
	u8 reserved;

	u8 data[8];
पूर्ण __packed;
/* The GS USB devices make use of the same flags and masks as in
 * linux/can.h and linux/can/error.h, and no additional mapping is necessary.
 */

/* Only send a max of GS_MAX_TX_URBS frames per channel at a समय. */
#घोषणा GS_MAX_TX_URBS 10
/* Only launch a max of GS_MAX_RX_URBS usb requests at a समय. */
#घोषणा GS_MAX_RX_URBS 30
/* Maximum number of पूर्णांकerfaces the driver supports per device.
 * Current hardware only supports 2 पूर्णांकerfaces. The future may vary.
 */
#घोषणा GS_MAX_INTF 2

काष्ठा gs_tx_context अणु
	काष्ठा gs_can *dev;
	अचिन्हित पूर्णांक echo_id;
पूर्ण;

काष्ठा gs_can अणु
	काष्ठा can_priv can; /* must be the first member */

	काष्ठा gs_usb *parent;

	काष्ठा net_device *netdev;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *अगरace;

	काष्ठा can_bittiming_स्थिर bt_स्थिर;
	अचिन्हित पूर्णांक channel;	/* channel number */

	/* This lock prevents a race condition between xmit and receive. */
	spinlock_t tx_ctx_lock;
	काष्ठा gs_tx_context tx_context[GS_MAX_TX_URBS];

	काष्ठा usb_anchor tx_submitted;
	atomic_t active_tx_urbs;
पूर्ण;

/* usb पूर्णांकerface काष्ठा */
काष्ठा gs_usb अणु
	काष्ठा gs_can *canch[GS_MAX_INTF];
	काष्ठा usb_anchor rx_submitted;
	atomic_t active_channels;
	काष्ठा usb_device *udev;
पूर्ण;

/* 'allocate' a tx context.
 * वापसs a valid tx context or शून्य अगर there is no space.
 */
अटल काष्ठा gs_tx_context *gs_alloc_tx_context(काष्ठा gs_can *dev)
अणु
	पूर्णांक i = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->tx_ctx_lock, flags);

	क्रम (; i < GS_MAX_TX_URBS; i++) अणु
		अगर (dev->tx_context[i].echo_id == GS_MAX_TX_URBS) अणु
			dev->tx_context[i].echo_id = i;
			spin_unlock_irqrestore(&dev->tx_ctx_lock, flags);
			वापस &dev->tx_context[i];
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&dev->tx_ctx_lock, flags);
	वापस शून्य;
पूर्ण

/* releases a tx context
 */
अटल व्योम gs_मुक्त_tx_context(काष्ठा gs_tx_context *txc)
अणु
	txc->echo_id = GS_MAX_TX_URBS;
पूर्ण

/* Get a tx context by id.
 */
अटल काष्ठा gs_tx_context *gs_get_tx_context(काष्ठा gs_can *dev,
					       अचिन्हित पूर्णांक id)
अणु
	अचिन्हित दीर्घ flags;

	अगर (id < GS_MAX_TX_URBS) अणु
		spin_lock_irqsave(&dev->tx_ctx_lock, flags);
		अगर (dev->tx_context[id].echo_id == id) अणु
			spin_unlock_irqrestore(&dev->tx_ctx_lock, flags);
			वापस &dev->tx_context[id];
		पूर्ण
		spin_unlock_irqrestore(&dev->tx_ctx_lock, flags);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक gs_cmd_reset(काष्ठा gs_can *gsdev)
अणु
	काष्ठा gs_device_mode *dm;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = gsdev->अगरace;
	पूर्णांक rc;

	dm = kzalloc(माप(*dm), GFP_KERNEL);
	अगर (!dm)
		वापस -ENOMEM;

	dm->mode = GS_CAN_MODE_RESET;

	rc = usb_control_msg(पूर्णांकerface_to_usbdev(पूर्णांकf),
			     usb_sndctrlpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), 0),
			     GS_USB_BREQ_MODE,
			     USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     gsdev->channel,
			     0,
			     dm,
			     माप(*dm),
			     1000);

	kमुक्त(dm);

	वापस rc;
पूर्ण

अटल व्योम gs_update_state(काष्ठा gs_can *dev, काष्ठा can_frame *cf)
अणु
	काष्ठा can_device_stats *can_stats = &dev->can.can_stats;

	अगर (cf->can_id & CAN_ERR_RESTARTED) अणु
		dev->can.state = CAN_STATE_ERROR_ACTIVE;
		can_stats->restarts++;
	पूर्ण अन्यथा अगर (cf->can_id & CAN_ERR_BUSOFF) अणु
		dev->can.state = CAN_STATE_BUS_OFF;
		can_stats->bus_off++;
	पूर्ण अन्यथा अगर (cf->can_id & CAN_ERR_CRTL) अणु
		अगर ((cf->data[1] & CAN_ERR_CRTL_TX_WARNING) ||
		    (cf->data[1] & CAN_ERR_CRTL_RX_WARNING)) अणु
			dev->can.state = CAN_STATE_ERROR_WARNING;
			can_stats->error_warning++;
		पूर्ण अन्यथा अगर ((cf->data[1] & CAN_ERR_CRTL_TX_PASSIVE) ||
			   (cf->data[1] & CAN_ERR_CRTL_RX_PASSIVE)) अणु
			dev->can.state = CAN_STATE_ERROR_PASSIVE;
			can_stats->error_passive++;
		पूर्ण अन्यथा अणु
			dev->can.state = CAN_STATE_ERROR_ACTIVE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gs_usb_receive_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा gs_usb *usbcan = urb->context;
	काष्ठा gs_can *dev;
	काष्ठा net_device *netdev;
	पूर्णांक rc;
	काष्ठा net_device_stats *stats;
	काष्ठा gs_host_frame *hf = urb->transfer_buffer;
	काष्ठा gs_tx_context *txc;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	BUG_ON(!usbcan);

	चयन (urb->status) अणु
	हाल 0: /* success */
		अवरोध;
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		/* करो not resubmit पातed urbs. eg: when device goes करोwn */
		वापस;
	पूर्ण

	/* device reports out of range channel id */
	अगर (hf->channel >= GS_MAX_INTF)
		जाओ resubmit_urb;

	dev = usbcan->canch[hf->channel];

	netdev = dev->netdev;
	stats = &netdev->stats;

	अगर (!netअगर_device_present(netdev))
		वापस;

	अगर (hf->echo_id == -1) अणु /* normal rx */
		skb = alloc_can_skb(dev->netdev, &cf);
		अगर (!skb)
			वापस;

		cf->can_id = le32_to_cpu(hf->can_id);

		can_frame_set_cc_len(cf, hf->can_dlc, dev->can.ctrlmode);
		स_नकल(cf->data, hf->data, 8);

		/* ERROR frames tell us inक्रमmation about the controller */
		अगर (le32_to_cpu(hf->can_id) & CAN_ERR_FLAG)
			gs_update_state(dev, cf);

		netdev->stats.rx_packets++;
		netdev->stats.rx_bytes += hf->can_dlc;

		netअगर_rx(skb);
	पूर्ण अन्यथा अणु /* echo_id == hf->echo_id */
		अगर (hf->echo_id >= GS_MAX_TX_URBS) अणु
			netdev_err(netdev,
				   "Unexpected out of range echo id %d\n",
				   hf->echo_id);
			जाओ resubmit_urb;
		पूर्ण

		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += hf->can_dlc;

		txc = gs_get_tx_context(dev, hf->echo_id);

		/* bad devices send bad echo_ids. */
		अगर (!txc) अणु
			netdev_err(netdev,
				   "Unexpected unused echo id %d\n",
				   hf->echo_id);
			जाओ resubmit_urb;
		पूर्ण

		can_get_echo_skb(netdev, hf->echo_id, शून्य);

		gs_मुक्त_tx_context(txc);

		atomic_dec(&dev->active_tx_urbs);

		netअगर_wake_queue(netdev);
	पूर्ण

	अगर (hf->flags & GS_CAN_FLAG_OVERFLOW) अणु
		skb = alloc_can_err_skb(netdev, &cf);
		अगर (!skb)
			जाओ resubmit_urb;

		cf->can_id |= CAN_ERR_CRTL;
		cf->len = CAN_ERR_DLC;
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		stats->rx_errors++;
		netअगर_rx(skb);
	पूर्ण

 resubmit_urb:
	usb_fill_bulk_urb(urb,
			  usbcan->udev,
			  usb_rcvbulkpipe(usbcan->udev, GSUSB_ENDPOINT_IN),
			  hf,
			  माप(काष्ठा gs_host_frame),
			  gs_usb_receive_bulk_callback,
			  usbcan
			  );

	rc = usb_submit_urb(urb, GFP_ATOMIC);

	/* USB failure take करोwn all पूर्णांकerfaces */
	अगर (rc == -ENODEV) अणु
		क्रम (rc = 0; rc < GS_MAX_INTF; rc++) अणु
			अगर (usbcan->canch[rc])
				netअगर_device_detach(usbcan->canch[rc]->netdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक gs_usb_set_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा gs_can *dev = netdev_priv(netdev);
	काष्ठा can_bittiming *bt = &dev->can.bittiming;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->अगरace;
	पूर्णांक rc;
	काष्ठा gs_device_bittiming *dbt;

	dbt = kदो_स्मृति(माप(*dbt), GFP_KERNEL);
	अगर (!dbt)
		वापस -ENOMEM;

	dbt->prop_seg = cpu_to_le32(bt->prop_seg);
	dbt->phase_seg1 = cpu_to_le32(bt->phase_seg1);
	dbt->phase_seg2 = cpu_to_le32(bt->phase_seg2);
	dbt->sjw = cpu_to_le32(bt->sjw);
	dbt->brp = cpu_to_le32(bt->brp);

	/* request bit timings */
	rc = usb_control_msg(पूर्णांकerface_to_usbdev(पूर्णांकf),
			     usb_sndctrlpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), 0),
			     GS_USB_BREQ_BITTIMING,
			     USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     dev->channel,
			     0,
			     dbt,
			     माप(*dbt),
			     1000);

	kमुक्त(dbt);

	अगर (rc < 0)
		dev_err(netdev->dev.parent, "Couldn't set bittimings (err=%d)",
			rc);

	वापस (rc > 0) ? 0 : rc;
पूर्ण

अटल व्योम gs_usb_xmit_callback(काष्ठा urb *urb)
अणु
	काष्ठा gs_tx_context *txc = urb->context;
	काष्ठा gs_can *dev = txc->dev;
	काष्ठा net_device *netdev = dev->netdev;

	अगर (urb->status)
		netdev_info(netdev, "usb xmit fail %d\n", txc->echo_id);

	usb_मुक्त_coherent(urb->dev,
			  urb->transfer_buffer_length,
			  urb->transfer_buffer,
			  urb->transfer_dma);
पूर्ण

अटल netdev_tx_t gs_can_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *netdev)
अणु
	काष्ठा gs_can *dev = netdev_priv(netdev);
	काष्ठा net_device_stats *stats = &dev->netdev->stats;
	काष्ठा urb *urb;
	काष्ठा gs_host_frame *hf;
	काष्ठा can_frame *cf;
	पूर्णांक rc;
	अचिन्हित पूर्णांक idx;
	काष्ठा gs_tx_context *txc;

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	/* find an empty context to keep track of transmission */
	txc = gs_alloc_tx_context(dev);
	अगर (!txc)
		वापस NETDEV_TX_BUSY;

	/* create a URB, and a buffer क्रम it */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ nomem_urb;

	hf = usb_alloc_coherent(dev->udev, माप(*hf), GFP_ATOMIC,
				&urb->transfer_dma);
	अगर (!hf) अणु
		netdev_err(netdev, "No memory left for USB buffer\n");
		जाओ nomem_hf;
	पूर्ण

	idx = txc->echo_id;

	अगर (idx >= GS_MAX_TX_URBS) अणु
		netdev_err(netdev, "Invalid tx context %d\n", idx);
		जाओ badidx;
	पूर्ण

	hf->echo_id = idx;
	hf->channel = dev->channel;

	cf = (काष्ठा can_frame *)skb->data;

	hf->can_id = cpu_to_le32(cf->can_id);
	hf->can_dlc = can_get_cc_dlc(cf, dev->can.ctrlmode);

	स_नकल(hf->data, cf->data, cf->len);

	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, GSUSB_ENDPOINT_OUT),
			  hf,
			  माप(*hf),
			  gs_usb_xmit_callback,
			  txc);

	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &dev->tx_submitted);

	can_put_echo_skb(skb, netdev, idx, 0);

	atomic_inc(&dev->active_tx_urbs);

	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(rc)) अणु			/* usb send failed */
		atomic_dec(&dev->active_tx_urbs);

		can_मुक्त_echo_skb(netdev, idx, शून्य);
		gs_मुक्त_tx_context(txc);

		usb_unanchor_urb(urb);
		usb_मुक्त_coherent(dev->udev,
				  माप(*hf),
				  hf,
				  urb->transfer_dma);

		अगर (rc == -ENODEV) अणु
			netअगर_device_detach(netdev);
		पूर्ण अन्यथा अणु
			netdev_err(netdev, "usb_submit failed (err=%d)\n", rc);
			stats->tx_dropped++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Slow करोwn tx path */
		अगर (atomic_पढ़ो(&dev->active_tx_urbs) >= GS_MAX_TX_URBS)
			netअगर_stop_queue(netdev);
	पूर्ण

	/* let usb core take care of this urb */
	usb_मुक्त_urb(urb);

	वापस NETDEV_TX_OK;

 badidx:
	usb_मुक्त_coherent(dev->udev,
			  माप(*hf),
			  hf,
			  urb->transfer_dma);
 nomem_hf:
	usb_मुक्त_urb(urb);

 nomem_urb:
	gs_मुक्त_tx_context(txc);
	dev_kमुक्त_skb(skb);
	stats->tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक gs_can_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा gs_can *dev = netdev_priv(netdev);
	काष्ठा gs_usb *parent = dev->parent;
	पूर्णांक rc, i;
	काष्ठा gs_device_mode *dm;
	u32 ctrlmode;
	u32 flags = 0;

	rc = खोलो_candev(netdev);
	अगर (rc)
		वापस rc;

	अगर (atomic_add_वापस(1, &parent->active_channels) == 1) अणु
		क्रम (i = 0; i < GS_MAX_RX_URBS; i++) अणु
			काष्ठा urb *urb;
			u8 *buf;

			/* alloc rx urb */
			urb = usb_alloc_urb(0, GFP_KERNEL);
			अगर (!urb)
				वापस -ENOMEM;

			/* alloc rx buffer */
			buf = usb_alloc_coherent(dev->udev,
						 माप(काष्ठा gs_host_frame),
						 GFP_KERNEL,
						 &urb->transfer_dma);
			अगर (!buf) अणु
				netdev_err(netdev,
					   "No memory left for USB buffer\n");
				usb_मुक्त_urb(urb);
				वापस -ENOMEM;
			पूर्ण

			/* fill, anchor, and submit rx urb */
			usb_fill_bulk_urb(urb,
					  dev->udev,
					  usb_rcvbulkpipe(dev->udev,
							  GSUSB_ENDPOINT_IN),
					  buf,
					  माप(काष्ठा gs_host_frame),
					  gs_usb_receive_bulk_callback,
					  parent);
			urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

			usb_anchor_urb(urb, &parent->rx_submitted);

			rc = usb_submit_urb(urb, GFP_KERNEL);
			अगर (rc) अणु
				अगर (rc == -ENODEV)
					netअगर_device_detach(dev->netdev);

				netdev_err(netdev,
					   "usb_submit failed (err=%d)\n",
					   rc);

				usb_unanchor_urb(urb);
				usb_मुक्त_urb(urb);
				अवरोध;
			पूर्ण

			/* Drop reference,
			 * USB core will take care of मुक्तing it
			 */
			usb_मुक्त_urb(urb);
		पूर्ण
	पूर्ण

	dm = kदो_स्मृति(माप(*dm), GFP_KERNEL);
	अगर (!dm)
		वापस -ENOMEM;

	/* flags */
	ctrlmode = dev->can.ctrlmode;

	अगर (ctrlmode & CAN_CTRLMODE_LOOPBACK)
		flags |= GS_CAN_MODE_LOOP_BACK;
	अन्यथा अगर (ctrlmode & CAN_CTRLMODE_LISTENONLY)
		flags |= GS_CAN_MODE_LISTEN_ONLY;

	/* Controller is not allowed to retry TX
	 * this mode is unavailable on aपंचांगels uc3c hardware
	 */
	अगर (ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		flags |= GS_CAN_MODE_ONE_SHOT;

	अगर (ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		flags |= GS_CAN_MODE_TRIPLE_SAMPLE;

	/* finally start device */
	dm->mode = cpu_to_le32(GS_CAN_MODE_START);
	dm->flags = cpu_to_le32(flags);
	rc = usb_control_msg(पूर्णांकerface_to_usbdev(dev->अगरace),
			     usb_sndctrlpipe(पूर्णांकerface_to_usbdev(dev->अगरace), 0),
			     GS_USB_BREQ_MODE,
			     USB_सूची_OUT | USB_TYPE_VENDOR |
			     USB_RECIP_INTERFACE,
			     dev->channel,
			     0,
			     dm,
			     माप(*dm),
			     1000);

	अगर (rc < 0) अणु
		netdev_err(netdev, "Couldn't start device (err=%d)\n", rc);
		kमुक्त(dm);
		वापस rc;
	पूर्ण

	kमुक्त(dm);

	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	अगर (!(dev->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
		netअगर_start_queue(netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक gs_can_बंद(काष्ठा net_device *netdev)
अणु
	पूर्णांक rc;
	काष्ठा gs_can *dev = netdev_priv(netdev);
	काष्ठा gs_usb *parent = dev->parent;

	netअगर_stop_queue(netdev);

	/* Stop polling */
	अगर (atomic_dec_and_test(&parent->active_channels))
		usb_समाप्त_anchored_urbs(&parent->rx_submitted);

	/* Stop sending URBs */
	usb_समाप्त_anchored_urbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);

	/* reset the device */
	rc = gs_cmd_reset(dev);
	अगर (rc < 0)
		netdev_warn(netdev, "Couldn't shutdown device (err=%d)", rc);

	/* reset tx contexts */
	क्रम (rc = 0; rc < GS_MAX_TX_URBS; rc++) अणु
		dev->tx_context[rc].dev = dev;
		dev->tx_context[rc].echo_id = GS_MAX_TX_URBS;
	पूर्ण

	/* बंद the netdev */
	बंद_candev(netdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops gs_usb_netdev_ops = अणु
	.nकरो_खोलो = gs_can_खोलो,
	.nकरो_stop = gs_can_बंद,
	.nकरो_start_xmit = gs_can_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल पूर्णांक gs_usb_set_identअगरy(काष्ठा net_device *netdev, bool करो_identअगरy)
अणु
	काष्ठा gs_can *dev = netdev_priv(netdev);
	काष्ठा gs_identअगरy_mode *imode;
	पूर्णांक rc;

	imode = kदो_स्मृति(माप(*imode), GFP_KERNEL);

	अगर (!imode)
		वापस -ENOMEM;

	अगर (करो_identअगरy)
		imode->mode = cpu_to_le32(GS_CAN_IDENTIFY_ON);
	अन्यथा
		imode->mode = cpu_to_le32(GS_CAN_IDENTIFY_OFF);

	rc = usb_control_msg(पूर्णांकerface_to_usbdev(dev->अगरace),
			     usb_sndctrlpipe(पूर्णांकerface_to_usbdev(dev->अगरace),
					     0),
			     GS_USB_BREQ_IDENTIFY,
			     USB_सूची_OUT | USB_TYPE_VENDOR |
			     USB_RECIP_INTERFACE,
			     dev->channel,
			     0,
			     imode,
			     माप(*imode),
			     100);

	kमुक्त(imode);

	वापस (rc > 0) ? 0 : rc;
पूर्ण

/* blink LED's क्रम finding the this पूर्णांकerface */
अटल पूर्णांक gs_usb_set_phys_id(काष्ठा net_device *dev,
			      क्रमागत ethtool_phys_id_state state)
अणु
	पूर्णांक rc = 0;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		rc = gs_usb_set_identअगरy(dev, GS_CAN_IDENTIFY_ON);
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		rc = gs_usb_set_identअगरy(dev, GS_CAN_IDENTIFY_OFF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops gs_usb_ethtool_ops = अणु
	.set_phys_id = gs_usb_set_phys_id,
पूर्ण;

अटल काष्ठा gs_can *gs_make_candev(अचिन्हित पूर्णांक channel,
				     काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				     काष्ठा gs_device_config *dconf)
अणु
	काष्ठा gs_can *dev;
	काष्ठा net_device *netdev;
	पूर्णांक rc;
	काष्ठा gs_device_bt_स्थिर *bt_स्थिर;
	u32 feature;

	bt_स्थिर = kदो_स्मृति(माप(*bt_स्थिर), GFP_KERNEL);
	अगर (!bt_स्थिर)
		वापस ERR_PTR(-ENOMEM);

	/* fetch bit timing स्थिरants */
	rc = usb_control_msg(पूर्णांकerface_to_usbdev(पूर्णांकf),
			     usb_rcvctrlpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), 0),
			     GS_USB_BREQ_BT_CONST,
			     USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     channel,
			     0,
			     bt_स्थिर,
			     माप(*bt_स्थिर),
			     1000);

	अगर (rc < 0) अणु
		dev_err(&पूर्णांकf->dev,
			"Couldn't get bit timing const for channel (err=%d)\n",
			rc);
		kमुक्त(bt_स्थिर);
		वापस ERR_PTR(rc);
	पूर्ण

	/* create netdev */
	netdev = alloc_candev(माप(काष्ठा gs_can), GS_MAX_TX_URBS);
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "Couldn't allocate candev\n");
		kमुक्त(bt_स्थिर);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dev = netdev_priv(netdev);

	netdev->netdev_ops = &gs_usb_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support full roundtrip echo */

	/* dev setup */
	म_नकल(dev->bt_स्थिर.name, "gs_usb");
	dev->bt_स्थिर.tseg1_min = le32_to_cpu(bt_स्थिर->tseg1_min);
	dev->bt_स्थिर.tseg1_max = le32_to_cpu(bt_स्थिर->tseg1_max);
	dev->bt_स्थिर.tseg2_min = le32_to_cpu(bt_स्थिर->tseg2_min);
	dev->bt_स्थिर.tseg2_max = le32_to_cpu(bt_स्थिर->tseg2_max);
	dev->bt_स्थिर.sjw_max = le32_to_cpu(bt_स्थिर->sjw_max);
	dev->bt_स्थिर.brp_min = le32_to_cpu(bt_स्थिर->brp_min);
	dev->bt_स्थिर.brp_max = le32_to_cpu(bt_स्थिर->brp_max);
	dev->bt_स्थिर.brp_inc = le32_to_cpu(bt_स्थिर->brp_inc);

	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	dev->अगरace = पूर्णांकf;
	dev->netdev = netdev;
	dev->channel = channel;

	init_usb_anchor(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);
	spin_lock_init(&dev->tx_ctx_lock);
	क्रम (rc = 0; rc < GS_MAX_TX_URBS; rc++) अणु
		dev->tx_context[rc].dev = dev;
		dev->tx_context[rc].echo_id = GS_MAX_TX_URBS;
	पूर्ण

	/* can setup */
	dev->can.state = CAN_STATE_STOPPED;
	dev->can.घड़ी.freq = le32_to_cpu(bt_स्थिर->fclk_can);
	dev->can.bittiming_स्थिर = &dev->bt_स्थिर;
	dev->can.करो_set_bittiming = gs_usb_set_bittiming;

	dev->can.ctrlmode_supported = CAN_CTRLMODE_CC_LEN8_DLC;

	feature = le32_to_cpu(bt_स्थिर->feature);
	अगर (feature & GS_CAN_FEATURE_LISTEN_ONLY)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_LISTENONLY;

	अगर (feature & GS_CAN_FEATURE_LOOP_BACK)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_LOOPBACK;

	अगर (feature & GS_CAN_FEATURE_TRIPLE_SAMPLE)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;

	अगर (feature & GS_CAN_FEATURE_ONE_SHOT)
		dev->can.ctrlmode_supported |= CAN_CTRLMODE_ONE_SHOT;

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);

	अगर (le32_to_cpu(dconf->sw_version) > 1)
		अगर (feature & GS_CAN_FEATURE_IDENTIFY)
			netdev->ethtool_ops = &gs_usb_ethtool_ops;

	kमुक्त(bt_स्थिर);

	rc = रेजिस्टर_candev(dev->netdev);
	अगर (rc) अणु
		मुक्त_candev(dev->netdev);
		dev_err(&पूर्णांकf->dev, "Couldn't register candev (err=%d)\n", rc);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस dev;
पूर्ण

अटल व्योम gs_destroy_candev(काष्ठा gs_can *dev)
अणु
	unरेजिस्टर_candev(dev->netdev);
	usb_समाप्त_anchored_urbs(&dev->tx_submitted);
	मुक्त_candev(dev->netdev);
पूर्ण

अटल पूर्णांक gs_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा gs_usb *dev;
	पूर्णांक rc = -ENOMEM;
	अचिन्हित पूर्णांक icount, i;
	काष्ठा gs_host_config *hconf;
	काष्ठा gs_device_config *dconf;

	hconf = kदो_स्मृति(माप(*hconf), GFP_KERNEL);
	अगर (!hconf)
		वापस -ENOMEM;

	hconf->byte_order = cpu_to_le32(0x0000beef);

	/* send host config */
	rc = usb_control_msg(पूर्णांकerface_to_usbdev(पूर्णांकf),
			     usb_sndctrlpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), 0),
			     GS_USB_BREQ_HOST_FORMAT,
			     USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     1,
			     पूर्णांकf->cur_altsetting->desc.bInterfaceNumber,
			     hconf,
			     माप(*hconf),
			     1000);

	kमुक्त(hconf);

	अगर (rc < 0) अणु
		dev_err(&पूर्णांकf->dev, "Couldn't send data format (err=%d)\n",
			rc);
		वापस rc;
	पूर्ण

	dconf = kदो_स्मृति(माप(*dconf), GFP_KERNEL);
	अगर (!dconf)
		वापस -ENOMEM;

	/* पढ़ो device config */
	rc = usb_control_msg(पूर्णांकerface_to_usbdev(पूर्णांकf),
			     usb_rcvctrlpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), 0),
			     GS_USB_BREQ_DEVICE_CONFIG,
			     USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     1,
			     पूर्णांकf->cur_altsetting->desc.bInterfaceNumber,
			     dconf,
			     माप(*dconf),
			     1000);
	अगर (rc < 0) अणु
		dev_err(&पूर्णांकf->dev, "Couldn't get device config: (err=%d)\n",
			rc);
		kमुक्त(dconf);
		वापस rc;
	पूर्ण

	icount = dconf->icount + 1;
	dev_info(&पूर्णांकf->dev, "Configuring for %d interfaces\n", icount);

	अगर (icount > GS_MAX_INTF) अणु
		dev_err(&पूर्णांकf->dev,
			"Driver cannot handle more that %d CAN interfaces\n",
			GS_MAX_INTF);
		kमुक्त(dconf);
		वापस -EINVAL;
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		kमुक्त(dconf);
		वापस -ENOMEM;
	पूर्ण

	init_usb_anchor(&dev->rx_submitted);

	atomic_set(&dev->active_channels, 0);

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);
	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	क्रम (i = 0; i < icount; i++) अणु
		dev->canch[i] = gs_make_candev(i, पूर्णांकf, dconf);
		अगर (IS_ERR_OR_शून्य(dev->canch[i])) अणु
			/* save error code to वापस later */
			rc = PTR_ERR(dev->canch[i]);

			/* on failure destroy previously created candevs */
			icount = i;
			क्रम (i = 0; i < icount; i++)
				gs_destroy_candev(dev->canch[i]);

			usb_समाप्त_anchored_urbs(&dev->rx_submitted);
			kमुक्त(dconf);
			kमुक्त(dev);
			वापस rc;
		पूर्ण
		dev->canch[i]->parent = dev;
	पूर्ण

	kमुक्त(dconf);

	वापस 0;
पूर्ण

अटल व्योम gs_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अचिन्हित i;
	काष्ठा gs_usb *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (!dev) अणु
		dev_err(&पूर्णांकf->dev, "Disconnect (nodata)\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < GS_MAX_INTF; i++)
		अगर (dev->canch[i])
			gs_destroy_candev(dev->canch[i]);

	usb_समाप्त_anchored_urbs(&dev->rx_submitted);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा usb_device_id gs_usb_table[] = अणु
	अणु USB_DEVICE_INTERFACE_NUMBER(USB_GSUSB_1_VENDOR_ID,
				      USB_GSUSB_1_PRODUCT_ID, 0) पूर्ण,
	अणु USB_DEVICE_INTERFACE_NUMBER(USB_CANDLELIGHT_VENDOR_ID,
				      USB_CANDLELIGHT_PRODUCT_ID, 0) पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, gs_usb_table);

अटल काष्ठा usb_driver gs_usb_driver = अणु
	.name       = "gs_usb",
	.probe      = gs_usb_probe,
	.disconnect = gs_usb_disconnect,
	.id_table   = gs_usb_table,
पूर्ण;

module_usb_driver(gs_usb_driver);

MODULE_AUTHOR("Maximilian Schneider <mws@schneidersoft.net>");
MODULE_DESCRIPTION(
"Socket CAN device driver for Geschwister Schneider Technologie-, "
"Entwicklungs- und Vertriebs UG. USB2.0 to CAN interfaces\n"
"and bytewerk.org candleLight USB CAN interfaces.");
MODULE_LICENSE("GPL v2");
