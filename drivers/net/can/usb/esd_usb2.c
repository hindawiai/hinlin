<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN driver क्रम esd CAN-USB/2 and CAN-USB/Micro
 *
 * Copyright (C) 2010-2012 Matthias Fuchs <matthias.fuchs@esd.eu>, esd gmbh
 */
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>

MODULE_AUTHOR("Matthias Fuchs <matthias.fuchs@esd.eu>");
MODULE_DESCRIPTION("CAN driver for esd CAN-USB/2 and CAN-USB/Micro interfaces");
MODULE_LICENSE("GPL v2");

/* Define these values to match your devices */
#घोषणा USB_ESDGMBH_VENDOR_ID	0x0ab4
#घोषणा USB_CANUSB2_PRODUCT_ID	0x0010
#घोषणा USB_CANUSBM_PRODUCT_ID	0x0011

#घोषणा ESD_USB2_CAN_CLOCK	60000000
#घोषणा ESD_USBM_CAN_CLOCK	36000000
#घोषणा ESD_USB2_MAX_NETS	2

/* USB2 commands */
#घोषणा CMD_VERSION		1 /* also used क्रम VERSION_REPLY */
#घोषणा CMD_CAN_RX		2 /* device to host only */
#घोषणा CMD_CAN_TX		3 /* also used क्रम TX_DONE */
#घोषणा CMD_SETBAUD		4 /* also used क्रम SETBAUD_REPLY */
#घोषणा CMD_TS			5 /* also used क्रम TS_REPLY */
#घोषणा CMD_IDADD		6 /* also used क्रम IDADD_REPLY */

/* esd CAN message flags - dlc field */
#घोषणा ESD_RTR			0x10

/* esd CAN message flags - id field */
#घोषणा ESD_EXTID		0x20000000
#घोषणा ESD_EVENT		0x40000000
#घोषणा ESD_IDMASK		0x1fffffff

/* esd CAN event ids used by this driver */
#घोषणा ESD_EV_CAN_ERROR_EXT	2

/* baudrate message flags */
#घोषणा ESD_USB2_UBR		0x80000000
#घोषणा ESD_USB2_LOM		0x40000000
#घोषणा ESD_USB2_NO_BAUDRATE	0x7fffffff
#घोषणा ESD_USB2_TSEG1_MIN	1
#घोषणा ESD_USB2_TSEG1_MAX	16
#घोषणा ESD_USB2_TSEG1_SHIFT	16
#घोषणा ESD_USB2_TSEG2_MIN	1
#घोषणा ESD_USB2_TSEG2_MAX	8
#घोषणा ESD_USB2_TSEG2_SHIFT	20
#घोषणा ESD_USB2_SJW_MAX	4
#घोषणा ESD_USB2_SJW_SHIFT	14
#घोषणा ESD_USBM_SJW_SHIFT	24
#घोषणा ESD_USB2_BRP_MIN	1
#घोषणा ESD_USB2_BRP_MAX	1024
#घोषणा ESD_USB2_BRP_INC	1
#घोषणा ESD_USB2_3_SAMPLES	0x00800000

/* esd IDADD message */
#घोषणा ESD_ID_ENABLE		0x80
#घोषणा ESD_MAX_ID_SEGMENT	64

/* SJA1000 ECC रेजिस्टर (emulated by usb2 firmware) */
#घोषणा SJA1000_ECC_SEG		0x1F
#घोषणा SJA1000_ECC_सूची		0x20
#घोषणा SJA1000_ECC_ERR		0x06
#घोषणा SJA1000_ECC_BIT		0x00
#घोषणा SJA1000_ECC_FORM	0x40
#घोषणा SJA1000_ECC_STUFF	0x80
#घोषणा SJA1000_ECC_MASK	0xc0

/* esd bus state event codes */
#घोषणा ESD_BUSSTATE_MASK	0xc0
#घोषणा ESD_BUSSTATE_WARN	0x40
#घोषणा ESD_BUSSTATE_ERRPASSIVE	0x80
#घोषणा ESD_BUSSTATE_BUSOFF	0xc0

#घोषणा RX_BUFFER_SIZE		1024
#घोषणा MAX_RX_URBS		4
#घोषणा MAX_TX_URBS		16 /* must be घातer of 2 */

काष्ठा header_msg अणु
	u8 len; /* len is always the total message length in 32bit words */
	u8 cmd;
	u8 rsvd[2];
पूर्ण;

काष्ठा version_msg अणु
	u8 len;
	u8 cmd;
	u8 rsvd;
	u8 flags;
	__le32 drv_version;
पूर्ण;

काष्ठा version_reply_msg अणु
	u8 len;
	u8 cmd;
	u8 nets;
	u8 features;
	__le32 version;
	u8 name[16];
	__le32 rsvd;
	__le32 ts;
पूर्ण;

काष्ठा rx_msg अणु
	u8 len;
	u8 cmd;
	u8 net;
	u8 dlc;
	__le32 ts;
	__le32 id; /* upper 3 bits contain flags */
	u8 data[8];
पूर्ण;

काष्ठा tx_msg अणु
	u8 len;
	u8 cmd;
	u8 net;
	u8 dlc;
	u32 hnd;	/* opaque handle, not used by device */
	__le32 id; /* upper 3 bits contain flags */
	u8 data[8];
पूर्ण;

काष्ठा tx_करोne_msg अणु
	u8 len;
	u8 cmd;
	u8 net;
	u8 status;
	u32 hnd;	/* opaque handle, not used by device */
	__le32 ts;
पूर्ण;

काष्ठा id_filter_msg अणु
	u8 len;
	u8 cmd;
	u8 net;
	u8 option;
	__le32 mask[ESD_MAX_ID_SEGMENT + 1];
पूर्ण;

काष्ठा set_baudrate_msg अणु
	u8 len;
	u8 cmd;
	u8 net;
	u8 rsvd;
	__le32 baud;
पूर्ण;

/* Main message type used between library and application */
काष्ठा __attribute__ ((packed)) esd_usb2_msg अणु
	जोड़ अणु
		काष्ठा header_msg hdr;
		काष्ठा version_msg version;
		काष्ठा version_reply_msg version_reply;
		काष्ठा rx_msg rx;
		काष्ठा tx_msg tx;
		काष्ठा tx_करोne_msg txकरोne;
		काष्ठा set_baudrate_msg setbaud;
		काष्ठा id_filter_msg filter;
	पूर्ण msg;
पूर्ण;

अटल काष्ठा usb_device_id esd_usb2_table[] = अणु
	अणुUSB_DEVICE(USB_ESDGMBH_VENDOR_ID, USB_CANUSB2_PRODUCT_ID)पूर्ण,
	अणुUSB_DEVICE(USB_ESDGMBH_VENDOR_ID, USB_CANUSBM_PRODUCT_ID)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, esd_usb2_table);

काष्ठा esd_usb2_net_priv;

काष्ठा esd_tx_urb_context अणु
	काष्ठा esd_usb2_net_priv *priv;
	u32 echo_index;
	पूर्णांक len;	/* CAN payload length */
पूर्ण;

काष्ठा esd_usb2 अणु
	काष्ठा usb_device *udev;
	काष्ठा esd_usb2_net_priv *nets[ESD_USB2_MAX_NETS];

	काष्ठा usb_anchor rx_submitted;

	पूर्णांक net_count;
	u32 version;
	पूर्णांक rxinitकरोne;
पूर्ण;

काष्ठा esd_usb2_net_priv अणु
	काष्ठा can_priv can; /* must be the first member */

	atomic_t active_tx_jobs;
	काष्ठा usb_anchor tx_submitted;
	काष्ठा esd_tx_urb_context tx_contexts[MAX_TX_URBS];

	काष्ठा esd_usb2 *usb2;
	काष्ठा net_device *netdev;
	पूर्णांक index;
	u8 old_state;
	काष्ठा can_berr_counter bec;
पूर्ण;

अटल व्योम esd_usb2_rx_event(काष्ठा esd_usb2_net_priv *priv,
			      काष्ठा esd_usb2_msg *msg)
अणु
	काष्ठा net_device_stats *stats = &priv->netdev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 id = le32_to_cpu(msg->msg.rx.id) & ESD_IDMASK;

	अगर (id == ESD_EV_CAN_ERROR_EXT) अणु
		u8 state = msg->msg.rx.data[0];
		u8 ecc = msg->msg.rx.data[1];
		u8 txerr = msg->msg.rx.data[2];
		u8 rxerr = msg->msg.rx.data[3];

		skb = alloc_can_err_skb(priv->netdev, &cf);
		अगर (skb == शून्य) अणु
			stats->rx_dropped++;
			वापस;
		पूर्ण

		अगर (state != priv->old_state) अणु
			priv->old_state = state;

			चयन (state & ESD_BUSSTATE_MASK) अणु
			हाल ESD_BUSSTATE_BUSOFF:
				priv->can.state = CAN_STATE_BUS_OFF;
				cf->can_id |= CAN_ERR_BUSOFF;
				priv->can.can_stats.bus_off++;
				can_bus_off(priv->netdev);
				अवरोध;
			हाल ESD_BUSSTATE_WARN:
				priv->can.state = CAN_STATE_ERROR_WARNING;
				priv->can.can_stats.error_warning++;
				अवरोध;
			हाल ESD_BUSSTATE_ERRPASSIVE:
				priv->can.state = CAN_STATE_ERROR_PASSIVE;
				priv->can.can_stats.error_passive++;
				अवरोध;
			शेष:
				priv->can.state = CAN_STATE_ERROR_ACTIVE;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			priv->can.can_stats.bus_error++;
			stats->rx_errors++;

			cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

			चयन (ecc & SJA1000_ECC_MASK) अणु
			हाल SJA1000_ECC_BIT:
				cf->data[2] |= CAN_ERR_PROT_BIT;
				अवरोध;
			हाल SJA1000_ECC_FORM:
				cf->data[2] |= CAN_ERR_PROT_FORM;
				अवरोध;
			हाल SJA1000_ECC_STUFF:
				cf->data[2] |= CAN_ERR_PROT_STUFF;
				अवरोध;
			शेष:
				cf->data[3] = ecc & SJA1000_ECC_SEG;
				अवरोध;
			पूर्ण

			/* Error occurred during transmission? */
			अगर (!(ecc & SJA1000_ECC_सूची))
				cf->data[2] |= CAN_ERR_PROT_TX;

			अगर (priv->can.state == CAN_STATE_ERROR_WARNING ||
			    priv->can.state == CAN_STATE_ERROR_PASSIVE) अणु
				cf->data[1] = (txerr > rxerr) ?
					CAN_ERR_CRTL_TX_PASSIVE :
					CAN_ERR_CRTL_RX_PASSIVE;
			पूर्ण
			cf->data[6] = txerr;
			cf->data[7] = rxerr;
		पूर्ण

		priv->bec.txerr = txerr;
		priv->bec.rxerr = rxerr;

		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल व्योम esd_usb2_rx_can_msg(काष्ठा esd_usb2_net_priv *priv,
				काष्ठा esd_usb2_msg *msg)
अणु
	काष्ठा net_device_stats *stats = &priv->netdev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	u32 id;

	अगर (!netअगर_device_present(priv->netdev))
		वापस;

	id = le32_to_cpu(msg->msg.rx.id);

	अगर (id & ESD_EVENT) अणु
		esd_usb2_rx_event(priv, msg);
	पूर्ण अन्यथा अणु
		skb = alloc_can_skb(priv->netdev, &cf);
		अगर (skb == शून्य) अणु
			stats->rx_dropped++;
			वापस;
		पूर्ण

		cf->can_id = id & ESD_IDMASK;
		can_frame_set_cc_len(cf, msg->msg.rx.dlc & ~ESD_RTR,
				     priv->can.ctrlmode);

		अगर (id & ESD_EXTID)
			cf->can_id |= CAN_EFF_FLAG;

		अगर (msg->msg.rx.dlc & ESD_RTR) अणु
			cf->can_id |= CAN_RTR_FLAG;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < cf->len; i++)
				cf->data[i] = msg->msg.rx.data[i];
		पूर्ण

		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_rx(skb);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम esd_usb2_tx_करोne_msg(काष्ठा esd_usb2_net_priv *priv,
				 काष्ठा esd_usb2_msg *msg)
अणु
	काष्ठा net_device_stats *stats = &priv->netdev->stats;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा esd_tx_urb_context *context;

	अगर (!netअगर_device_present(netdev))
		वापस;

	context = &priv->tx_contexts[msg->msg.txकरोne.hnd & (MAX_TX_URBS - 1)];

	अगर (!msg->msg.txकरोne.status) अणु
		stats->tx_packets++;
		stats->tx_bytes += context->len;
		can_get_echo_skb(netdev, context->echo_index, शून्य);
	पूर्ण अन्यथा अणु
		stats->tx_errors++;
		can_मुक्त_echo_skb(netdev, context->echo_index, शून्य);
	पूर्ण

	/* Release context */
	context->echo_index = MAX_TX_URBS;
	atomic_dec(&priv->active_tx_jobs);

	netअगर_wake_queue(netdev);
पूर्ण

अटल व्योम esd_usb2_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा esd_usb2 *dev = urb->context;
	पूर्णांक retval;
	पूर्णांक pos = 0;
	पूर्णांक i;

	चयन (urb->status) अणु
	हाल 0: /* success */
		अवरोध;

	हाल -ENOENT:
	हाल -EPIPE:
	हाल -EPROTO:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		dev_info(dev->udev->dev.parent,
			 "Rx URB aborted (%d)\n", urb->status);
		जाओ resubmit_urb;
	पूर्ण

	जबतक (pos < urb->actual_length) अणु
		काष्ठा esd_usb2_msg *msg;

		msg = (काष्ठा esd_usb2_msg *)(urb->transfer_buffer + pos);

		चयन (msg->msg.hdr.cmd) अणु
		हाल CMD_CAN_RX:
			अगर (msg->msg.rx.net >= dev->net_count) अणु
				dev_err(dev->udev->dev.parent, "format error\n");
				अवरोध;
			पूर्ण

			esd_usb2_rx_can_msg(dev->nets[msg->msg.rx.net], msg);
			अवरोध;

		हाल CMD_CAN_TX:
			अगर (msg->msg.txकरोne.net >= dev->net_count) अणु
				dev_err(dev->udev->dev.parent, "format error\n");
				अवरोध;
			पूर्ण

			esd_usb2_tx_करोne_msg(dev->nets[msg->msg.txकरोne.net],
					     msg);
			अवरोध;
		पूर्ण

		pos += msg->msg.hdr.len << 2;

		अगर (pos > urb->actual_length) अणु
			dev_err(dev->udev->dev.parent, "format error\n");
			अवरोध;
		पूर्ण
	पूर्ण

resubmit_urb:
	usb_fill_bulk_urb(urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
			  urb->transfer_buffer, RX_BUFFER_SIZE,
			  esd_usb2_पढ़ो_bulk_callback, dev);

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval == -ENODEV) अणु
		क्रम (i = 0; i < dev->net_count; i++) अणु
			अगर (dev->nets[i])
				netअगर_device_detach(dev->nets[i]->netdev);
		पूर्ण
	पूर्ण अन्यथा अगर (retval) अणु
		dev_err(dev->udev->dev.parent,
			"failed resubmitting read bulk urb: %d\n", retval);
	पूर्ण

	वापस;
पूर्ण

/*
 * callback क्रम bulk IN urb
 */
अटल व्योम esd_usb2_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा esd_tx_urb_context *context = urb->context;
	काष्ठा esd_usb2_net_priv *priv;
	काष्ठा net_device *netdev;
	माप_प्रकार size = माप(काष्ठा esd_usb2_msg);

	WARN_ON(!context);

	priv = context->priv;
	netdev = priv->netdev;

	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev, size,
			  urb->transfer_buffer, urb->transfer_dma);

	अगर (!netअगर_device_present(netdev))
		वापस;

	अगर (urb->status)
		netdev_info(netdev, "Tx URB aborted (%d)\n", urb->status);

	netअगर_trans_update(netdev);
पूर्ण

अटल sमाप_प्रकार show_firmware(काष्ठा device *d,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(d);
	काष्ठा esd_usb2 *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "%d.%d.%d\n",
		       (dev->version >> 12) & 0xf,
		       (dev->version >> 8) & 0xf,
		       dev->version & 0xff);
पूर्ण
अटल DEVICE_ATTR(firmware, 0444, show_firmware, शून्य);

अटल sमाप_प्रकार show_hardware(काष्ठा device *d,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(d);
	काष्ठा esd_usb2 *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "%d.%d.%d\n",
		       (dev->version >> 28) & 0xf,
		       (dev->version >> 24) & 0xf,
		       (dev->version >> 16) & 0xff);
पूर्ण
अटल DEVICE_ATTR(hardware, 0444, show_hardware, शून्य);

अटल sमाप_प्रकार show_nets(काष्ठा device *d,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(d);
	काष्ठा esd_usb2 *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "%d", dev->net_count);
पूर्ण
अटल DEVICE_ATTR(nets, 0444, show_nets, शून्य);

अटल पूर्णांक esd_usb2_send_msg(काष्ठा esd_usb2 *dev, काष्ठा esd_usb2_msg *msg)
अणु
	पूर्णांक actual_length;

	वापस usb_bulk_msg(dev->udev,
			    usb_sndbulkpipe(dev->udev, 2),
			    msg,
			    msg->msg.hdr.len << 2,
			    &actual_length,
			    1000);
पूर्ण

अटल पूर्णांक esd_usb2_रुको_msg(काष्ठा esd_usb2 *dev,
			     काष्ठा esd_usb2_msg *msg)
अणु
	पूर्णांक actual_length;

	वापस usb_bulk_msg(dev->udev,
			    usb_rcvbulkpipe(dev->udev, 1),
			    msg,
			    माप(*msg),
			    &actual_length,
			    1000);
पूर्ण

अटल पूर्णांक esd_usb2_setup_rx_urbs(काष्ठा esd_usb2 *dev)
अणु
	पूर्णांक i, err = 0;

	अगर (dev->rxinitकरोne)
		वापस 0;

	क्रम (i = 0; i < MAX_RX_URBS; i++) अणु
		काष्ठा urb *urb = शून्य;
		u8 *buf = शून्य;

		/* create a URB, and a buffer क्रम it */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		buf = usb_alloc_coherent(dev->udev, RX_BUFFER_SIZE, GFP_KERNEL,
					 &urb->transfer_dma);
		अगर (!buf) अणु
			dev_warn(dev->udev->dev.parent,
				 "No memory left for USB buffer\n");
			err = -ENOMEM;
			जाओ मुक्तurb;
		पूर्ण

		usb_fill_bulk_urb(urb, dev->udev,
				  usb_rcvbulkpipe(dev->udev, 1),
				  buf, RX_BUFFER_SIZE,
				  esd_usb2_पढ़ो_bulk_callback, dev);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &dev->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			usb_unanchor_urb(urb);
			usb_मुक्त_coherent(dev->udev, RX_BUFFER_SIZE, buf,
					  urb->transfer_dma);
		पूर्ण

मुक्तurb:
		/* Drop reference, USB core will take care of मुक्तing it */
		usb_मुक्त_urb(urb);
		अगर (err)
			अवरोध;
	पूर्ण

	/* Did we submit any URBs */
	अगर (i == 0) अणु
		dev_err(dev->udev->dev.parent, "couldn't setup read URBs\n");
		वापस err;
	पूर्ण

	/* Warn अगर we've couldn't transmit all the URBs */
	अगर (i < MAX_RX_URBS) अणु
		dev_warn(dev->udev->dev.parent,
			 "rx performance may be slow\n");
	पूर्ण

	dev->rxinitकरोne = 1;
	वापस 0;
पूर्ण

/*
 * Start पूर्णांकerface
 */
अटल पूर्णांक esd_usb2_start(काष्ठा esd_usb2_net_priv *priv)
अणु
	काष्ठा esd_usb2 *dev = priv->usb2;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा esd_usb2_msg *msg;
	पूर्णांक err, i;

	msg = kदो_स्मृति(माप(*msg), GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Enable all IDs
	 * The IDADD message takes up to 64 32 bit biपंचांगasks (2048 bits).
	 * Each bit represents one 11 bit CAN identअगरier. A set bit
	 * enables reception of the corresponding CAN identअगरier. A cleared
	 * bit disabled this identअगरier. An additional biपंचांगask value
	 * following the CAN 2.0A bits is used to enable reception of
	 * extended CAN frames. Only the LSB of this final mask is checked
	 * क्रम the complete 29 bit ID range. The IDADD message also allows
	 * filter configuration क्रम an ID subset. In this हाल you can add
	 * the number of the starting biपंचांगask (0..64) to the filter.option
	 * field followed by only some biपंचांगasks.
	 */
	msg->msg.hdr.cmd = CMD_IDADD;
	msg->msg.hdr.len = 2 + ESD_MAX_ID_SEGMENT;
	msg->msg.filter.net = priv->index;
	msg->msg.filter.option = ESD_ID_ENABLE; /* start with segment 0 */
	क्रम (i = 0; i < ESD_MAX_ID_SEGMENT; i++)
		msg->msg.filter.mask[i] = cpu_to_le32(0xffffffff);
	/* enable 29bit extended IDs */
	msg->msg.filter.mask[ESD_MAX_ID_SEGMENT] = cpu_to_le32(0x00000001);

	err = esd_usb2_send_msg(dev, msg);
	अगर (err)
		जाओ out;

	err = esd_usb2_setup_rx_urbs(dev);
	अगर (err)
		जाओ out;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

out:
	अगर (err == -ENODEV)
		netअगर_device_detach(netdev);
	अगर (err)
		netdev_err(netdev, "couldn't start device: %d\n", err);

	kमुक्त(msg);
	वापस err;
पूर्ण

अटल व्योम unlink_all_urbs(काष्ठा esd_usb2 *dev)
अणु
	काष्ठा esd_usb2_net_priv *priv;
	पूर्णांक i, j;

	usb_समाप्त_anchored_urbs(&dev->rx_submitted);
	क्रम (i = 0; i < dev->net_count; i++) अणु
		priv = dev->nets[i];
		अगर (priv) अणु
			usb_समाप्त_anchored_urbs(&priv->tx_submitted);
			atomic_set(&priv->active_tx_jobs, 0);

			क्रम (j = 0; j < MAX_TX_URBS; j++)
				priv->tx_contexts[j].echo_index = MAX_TX_URBS;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक esd_usb2_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा esd_usb2_net_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	/* common खोलो */
	err = खोलो_candev(netdev);
	अगर (err)
		वापस err;

	/* finally start device */
	err = esd_usb2_start(priv);
	अगर (err) अणु
		netdev_warn(netdev, "couldn't start device: %d\n", err);
		बंद_candev(netdev);
		वापस err;
	पूर्ण

	netअगर_start_queue(netdev);

	वापस 0;
पूर्ण

अटल netdev_tx_t esd_usb2_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *netdev)
अणु
	काष्ठा esd_usb2_net_priv *priv = netdev_priv(netdev);
	काष्ठा esd_usb2 *dev = priv->usb2;
	काष्ठा esd_tx_urb_context *context = शून्य;
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	काष्ठा esd_usb2_msg *msg;
	काष्ठा urb *urb;
	u8 *buf;
	पूर्णांक i, err;
	पूर्णांक ret = NETDEV_TX_OK;
	माप_प्रकार size = माप(काष्ठा esd_usb2_msg);

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	/* create a URB, and a buffer क्रम it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		stats->tx_dropped++;
		dev_kमुक्त_skb(skb);
		जाओ nourbmem;
	पूर्ण

	buf = usb_alloc_coherent(dev->udev, size, GFP_ATOMIC,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		netdev_err(netdev, "No memory left for USB buffer\n");
		stats->tx_dropped++;
		dev_kमुक्त_skb(skb);
		जाओ nobufmem;
	पूर्ण

	msg = (काष्ठा esd_usb2_msg *)buf;

	msg->msg.hdr.len = 3; /* minimal length */
	msg->msg.hdr.cmd = CMD_CAN_TX;
	msg->msg.tx.net = priv->index;
	msg->msg.tx.dlc = can_get_cc_dlc(cf, priv->can.ctrlmode);
	msg->msg.tx.id = cpu_to_le32(cf->can_id & CAN_ERR_MASK);

	अगर (cf->can_id & CAN_RTR_FLAG)
		msg->msg.tx.dlc |= ESD_RTR;

	अगर (cf->can_id & CAN_EFF_FLAG)
		msg->msg.tx.id |= cpu_to_le32(ESD_EXTID);

	क्रम (i = 0; i < cf->len; i++)
		msg->msg.tx.data[i] = cf->data[i];

	msg->msg.hdr.len += (cf->len + 3) >> 2;

	क्रम (i = 0; i < MAX_TX_URBS; i++) अणु
		अगर (priv->tx_contexts[i].echo_index == MAX_TX_URBS) अणु
			context = &priv->tx_contexts[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * This may never happen.
	 */
	अगर (!context) अणु
		netdev_warn(netdev, "couldn't find free context\n");
		ret = NETDEV_TX_BUSY;
		जाओ releasebuf;
	पूर्ण

	context->priv = priv;
	context->echo_index = i;
	context->len = cf->len;

	/* hnd must not be 0 - MSB is stripped in txकरोne handling */
	msg->msg.tx.hnd = 0x80000000 | i; /* वापसed in TX करोne message */

	usb_fill_bulk_urb(urb, dev->udev, usb_sndbulkpipe(dev->udev, 2), buf,
			  msg->msg.hdr.len << 2,
			  esd_usb2_ग_लिखो_bulk_callback, context);

	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_anchor_urb(urb, &priv->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&priv->active_tx_jobs);

	/* Slow करोwn tx path */
	अगर (atomic_पढ़ो(&priv->active_tx_jobs) >= MAX_TX_URBS)
		netअगर_stop_queue(netdev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		can_मुक्त_echo_skb(netdev, context->echo_index, शून्य);

		atomic_dec(&priv->active_tx_jobs);
		usb_unanchor_urb(urb);

		stats->tx_dropped++;

		अगर (err == -ENODEV)
			netअगर_device_detach(netdev);
		अन्यथा
			netdev_warn(netdev, "failed tx_urb %d\n", err);

		जाओ releasebuf;
	पूर्ण

	netअगर_trans_update(netdev);

	/*
	 * Release our reference to this URB, the USB core will eventually मुक्त
	 * it entirely.
	 */
	usb_मुक्त_urb(urb);

	वापस NETDEV_TX_OK;

releasebuf:
	usb_मुक्त_coherent(dev->udev, size, buf, urb->transfer_dma);

nobufmem:
	usb_मुक्त_urb(urb);

nourbmem:
	वापस ret;
पूर्ण

अटल पूर्णांक esd_usb2_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा esd_usb2_net_priv *priv = netdev_priv(netdev);
	काष्ठा esd_usb2_msg *msg;
	पूर्णांक i;

	msg = kदो_स्मृति(माप(*msg), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	/* Disable all IDs (see esd_usb2_start()) */
	msg->msg.hdr.cmd = CMD_IDADD;
	msg->msg.hdr.len = 2 + ESD_MAX_ID_SEGMENT;
	msg->msg.filter.net = priv->index;
	msg->msg.filter.option = ESD_ID_ENABLE; /* start with segment 0 */
	क्रम (i = 0; i <= ESD_MAX_ID_SEGMENT; i++)
		msg->msg.filter.mask[i] = 0;
	अगर (esd_usb2_send_msg(priv->usb2, msg) < 0)
		netdev_err(netdev, "sending idadd message failed\n");

	/* set CAN controller to reset mode */
	msg->msg.hdr.len = 2;
	msg->msg.hdr.cmd = CMD_SETBAUD;
	msg->msg.setbaud.net = priv->index;
	msg->msg.setbaud.rsvd = 0;
	msg->msg.setbaud.baud = cpu_to_le32(ESD_USB2_NO_BAUDRATE);
	अगर (esd_usb2_send_msg(priv->usb2, msg) < 0)
		netdev_err(netdev, "sending setbaud message failed\n");

	priv->can.state = CAN_STATE_STOPPED;

	netअगर_stop_queue(netdev);

	बंद_candev(netdev);

	kमुक्त(msg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops esd_usb2_netdev_ops = अणु
	.nकरो_खोलो = esd_usb2_खोलो,
	.nकरो_stop = esd_usb2_बंद,
	.nकरो_start_xmit = esd_usb2_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर esd_usb2_bittiming_स्थिर = अणु
	.name = "esd_usb2",
	.tseg1_min = ESD_USB2_TSEG1_MIN,
	.tseg1_max = ESD_USB2_TSEG1_MAX,
	.tseg2_min = ESD_USB2_TSEG2_MIN,
	.tseg2_max = ESD_USB2_TSEG2_MAX,
	.sjw_max = ESD_USB2_SJW_MAX,
	.brp_min = ESD_USB2_BRP_MIN,
	.brp_max = ESD_USB2_BRP_MAX,
	.brp_inc = ESD_USB2_BRP_INC,
पूर्ण;

अटल पूर्णांक esd_usb2_set_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा esd_usb2_net_priv *priv = netdev_priv(netdev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा esd_usb2_msg *msg;
	पूर्णांक err;
	u32 canbtr;
	पूर्णांक sjw_shअगरt;

	canbtr = ESD_USB2_UBR;
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		canbtr |= ESD_USB2_LOM;

	canbtr |= (bt->brp - 1) & (ESD_USB2_BRP_MAX - 1);

	अगर (le16_to_cpu(priv->usb2->udev->descriptor.idProduct) ==
	    USB_CANUSBM_PRODUCT_ID)
		sjw_shअगरt = ESD_USBM_SJW_SHIFT;
	अन्यथा
		sjw_shअगरt = ESD_USB2_SJW_SHIFT;

	canbtr |= ((bt->sjw - 1) & (ESD_USB2_SJW_MAX - 1))
		<< sjw_shअगरt;
	canbtr |= ((bt->prop_seg + bt->phase_seg1 - 1)
		   & (ESD_USB2_TSEG1_MAX - 1))
		<< ESD_USB2_TSEG1_SHIFT;
	canbtr |= ((bt->phase_seg2 - 1) & (ESD_USB2_TSEG2_MAX - 1))
		<< ESD_USB2_TSEG2_SHIFT;
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		canbtr |= ESD_USB2_3_SAMPLES;

	msg = kदो_स्मृति(माप(*msg), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->msg.hdr.len = 2;
	msg->msg.hdr.cmd = CMD_SETBAUD;
	msg->msg.setbaud.net = priv->index;
	msg->msg.setbaud.rsvd = 0;
	msg->msg.setbaud.baud = cpu_to_le32(canbtr);

	netdev_info(netdev, "setting BTR=%#x\n", canbtr);

	err = esd_usb2_send_msg(priv->usb2, msg);

	kमुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक esd_usb2_get_berr_counter(स्थिर काष्ठा net_device *netdev,
				     काष्ठा can_berr_counter *bec)
अणु
	काष्ठा esd_usb2_net_priv *priv = netdev_priv(netdev);

	bec->txerr = priv->bec.txerr;
	bec->rxerr = priv->bec.rxerr;

	वापस 0;
पूर्ण

अटल पूर्णांक esd_usb2_set_mode(काष्ठा net_device *netdev, क्रमागत can_mode mode)
अणु
	चयन (mode) अणु
	हाल CAN_MODE_START:
		netअगर_wake_queue(netdev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक esd_usb2_probe_one_net(काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक index)
अणु
	काष्ठा esd_usb2 *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा net_device *netdev;
	काष्ठा esd_usb2_net_priv *priv;
	पूर्णांक err = 0;
	पूर्णांक i;

	netdev = alloc_candev(माप(*priv), MAX_TX_URBS);
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "couldn't alloc candev\n");
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	priv = netdev_priv(netdev);

	init_usb_anchor(&priv->tx_submitted);
	atomic_set(&priv->active_tx_jobs, 0);

	क्रम (i = 0; i < MAX_TX_URBS; i++)
		priv->tx_contexts[i].echo_index = MAX_TX_URBS;

	priv->usb2 = dev;
	priv->netdev = netdev;
	priv->index = index;

	priv->can.state = CAN_STATE_STOPPED;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LISTENONLY |
		CAN_CTRLMODE_CC_LEN8_DLC;

	अगर (le16_to_cpu(dev->udev->descriptor.idProduct) ==
	    USB_CANUSBM_PRODUCT_ID)
		priv->can.घड़ी.freq = ESD_USBM_CAN_CLOCK;
	अन्यथा अणु
		priv->can.घड़ी.freq = ESD_USB2_CAN_CLOCK;
		priv->can.ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;
	पूर्ण

	priv->can.bittiming_स्थिर = &esd_usb2_bittiming_स्थिर;
	priv->can.करो_set_bittiming = esd_usb2_set_bittiming;
	priv->can.करो_set_mode = esd_usb2_set_mode;
	priv->can.करो_get_berr_counter = esd_usb2_get_berr_counter;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	netdev->netdev_ops = &esd_usb2_netdev_ops;

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);
	netdev->dev_id = index;

	err = रेजिस्टर_candev(netdev);
	अगर (err) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register CAN device: %d\n", err);
		मुक्त_candev(netdev);
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	dev->nets[index] = priv;
	netdev_info(netdev, "device %s registered\n", netdev->name);

करोne:
	वापस err;
पूर्ण

/*
 * probe function क्रम new USB2 devices
 *
 * check version inक्रमmation and number of available
 * CAN पूर्णांकerfaces
 */
अटल पूर्णांक esd_usb2_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा esd_usb2 *dev;
	काष्ठा esd_usb2_msg *msg;
	पूर्णांक i, err;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	init_usb_anchor(&dev->rx_submitted);

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	msg = kदो_स्मृति(माप(*msg), GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ मुक्त_msg;
	पूर्ण

	/* query number of CAN पूर्णांकerfaces (nets) */
	msg->msg.hdr.cmd = CMD_VERSION;
	msg->msg.hdr.len = 2;
	msg->msg.version.rsvd = 0;
	msg->msg.version.flags = 0;
	msg->msg.version.drv_version = 0;

	err = esd_usb2_send_msg(dev, msg);
	अगर (err < 0) अणु
		dev_err(&पूर्णांकf->dev, "sending version message failed\n");
		जाओ मुक्त_msg;
	पूर्ण

	err = esd_usb2_रुको_msg(dev, msg);
	अगर (err < 0) अणु
		dev_err(&पूर्णांकf->dev, "no version message answer\n");
		जाओ मुक्त_msg;
	पूर्ण

	dev->net_count = (पूर्णांक)msg->msg.version_reply.nets;
	dev->version = le32_to_cpu(msg->msg.version_reply.version);

	अगर (device_create_file(&पूर्णांकf->dev, &dev_attr_firmware))
		dev_err(&पूर्णांकf->dev,
			"Couldn't create device file for firmware\n");

	अगर (device_create_file(&पूर्णांकf->dev, &dev_attr_hardware))
		dev_err(&पूर्णांकf->dev,
			"Couldn't create device file for hardware\n");

	अगर (device_create_file(&पूर्णांकf->dev, &dev_attr_nets))
		dev_err(&पूर्णांकf->dev,
			"Couldn't create device file for nets\n");

	/* करो per device probing */
	क्रम (i = 0; i < dev->net_count; i++)
		esd_usb2_probe_one_net(पूर्णांकf, i);

मुक्त_msg:
	kमुक्त(msg);
	अगर (err)
		kमुक्त(dev);
करोne:
	वापस err;
पूर्ण

/*
 * called by the usb core when the device is हटाओd from the प्रणाली
 */
अटल व्योम esd_usb2_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा esd_usb2 *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा net_device *netdev;
	पूर्णांक i;

	device_हटाओ_file(&पूर्णांकf->dev, &dev_attr_firmware);
	device_हटाओ_file(&पूर्णांकf->dev, &dev_attr_hardware);
	device_हटाओ_file(&पूर्णांकf->dev, &dev_attr_nets);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (dev) अणु
		क्रम (i = 0; i < dev->net_count; i++) अणु
			अगर (dev->nets[i]) अणु
				netdev = dev->nets[i]->netdev;
				unरेजिस्टर_netdev(netdev);
				मुक्त_candev(netdev);
			पूर्ण
		पूर्ण
		unlink_all_urbs(dev);
		kमुक्त(dev);
	पूर्ण
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver esd_usb2_driver = अणु
	.name = "esd_usb2",
	.probe = esd_usb2_probe,
	.disconnect = esd_usb2_disconnect,
	.id_table = esd_usb2_table,
पूर्ण;

module_usb_driver(esd_usb2_driver);
