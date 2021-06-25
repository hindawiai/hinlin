<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN driver क्रम "8 devices" USB2CAN converter
 *
 * Copyright (C) 2012 Bernd Krumboeck (krumboeck@universalnet.at)
 *
 * This driver is inspired by the 3.2.0 version of drivers/net/can/usb/ems_usb.c
 * and drivers/net/can/usb/esd_usb2.c
 *
 * Many thanks to Gerhard Bertelsmann (info@gerhard-bertelsmann.de)
 * क्रम testing and fixing this driver. Also many thanks to "8 devices",
 * who were very cooperative and answered my questions.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>

/* driver स्थिरants */
#घोषणा MAX_RX_URBS			20
#घोषणा MAX_TX_URBS			20
#घोषणा RX_BUFFER_SIZE			64

/* venकरोr and product id */
#घोषणा USB_8DEV_VENDOR_ID		0x0483
#घोषणा USB_8DEV_PRODUCT_ID		0x1234

/* endpoपूर्णांकs */
क्रमागत usb_8dev_endpoपूर्णांक अणु
	USB_8DEV_ENDP_DATA_RX = 1,
	USB_8DEV_ENDP_DATA_TX,
	USB_8DEV_ENDP_CMD_RX,
	USB_8DEV_ENDP_CMD_TX
पूर्ण;

/* device CAN घड़ी */
#घोषणा USB_8DEV_ABP_CLOCK		32000000

/* setup flags */
#घोषणा USB_8DEV_SILENT			0x01
#घोषणा USB_8DEV_LOOPBACK		0x02
#घोषणा USB_8DEV_DISABLE_AUTO_RESTRANS	0x04
#घोषणा USB_8DEV_STATUS_FRAME		0x08

/* commands */
क्रमागत usb_8dev_cmd अणु
	USB_8DEV_RESET = 1,
	USB_8DEV_OPEN,
	USB_8DEV_CLOSE,
	USB_8DEV_SET_SPEED,
	USB_8DEV_SET_MASK_FILTER,
	USB_8DEV_GET_STATUS,
	USB_8DEV_GET_STATISTICS,
	USB_8DEV_GET_SERIAL,
	USB_8DEV_GET_SOFTW_VER,
	USB_8DEV_GET_HARDW_VER,
	USB_8DEV_RESET_TIMESTAMP,
	USB_8DEV_GET_SOFTW_HARDW_VER
पूर्ण;

/* command options */
#घोषणा USB_8DEV_BAUD_MANUAL		0x09
#घोषणा USB_8DEV_CMD_START		0x11
#घोषणा USB_8DEV_CMD_END		0x22

#घोषणा USB_8DEV_CMD_SUCCESS		0
#घोषणा USB_8DEV_CMD_ERROR		255

#घोषणा USB_8DEV_CMD_TIMEOUT		1000

/* frames */
#घोषणा USB_8DEV_DATA_START		0x55
#घोषणा USB_8DEV_DATA_END		0xAA

#घोषणा USB_8DEV_TYPE_CAN_FRAME		0
#घोषणा USB_8DEV_TYPE_ERROR_FRAME	3

#घोषणा USB_8DEV_EXTID			0x01
#घोषणा USB_8DEV_RTR			0x02
#घोषणा USB_8DEV_ERR_FLAG		0x04

/* status */
#घोषणा USB_8DEV_STATUSMSG_OK		0x00  /* Normal condition. */
#घोषणा USB_8DEV_STATUSMSG_OVERRUN	0x01  /* Overrun occurred when sending */
#घोषणा USB_8DEV_STATUSMSG_BUSLIGHT	0x02  /* Error counter has reached 96 */
#घोषणा USB_8DEV_STATUSMSG_BUSHEAVY	0x03  /* Error count. has reached 128 */
#घोषणा USB_8DEV_STATUSMSG_BUSOFF	0x04  /* Device is in BUSOFF */
#घोषणा USB_8DEV_STATUSMSG_STUFF	0x20  /* Stuff Error */
#घोषणा USB_8DEV_STATUSMSG_FORM		0x21  /* Form Error */
#घोषणा USB_8DEV_STATUSMSG_ACK		0x23  /* Ack Error */
#घोषणा USB_8DEV_STATUSMSG_BIT0		0x24  /* Bit1 Error */
#घोषणा USB_8DEV_STATUSMSG_BIT1		0x25  /* Bit0 Error */
#घोषणा USB_8DEV_STATUSMSG_CRC		0x27  /* CRC Error */

#घोषणा USB_8DEV_RP_MASK		0x7F  /* Mask क्रम Receive Error Bit */


/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id usb_8dev_table[] = अणु
	अणु USB_DEVICE(USB_8DEV_VENDOR_ID, USB_8DEV_PRODUCT_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_8dev_table);

काष्ठा usb_8dev_tx_urb_context अणु
	काष्ठा usb_8dev_priv *priv;

	u32 echo_index;
	u8 dlc;
पूर्ण;

/* Structure to hold all of our device specअगरic stuff */
काष्ठा usb_8dev_priv अणु
	काष्ठा can_priv can; /* must be the first member */

	काष्ठा sk_buff *echo_skb[MAX_TX_URBS];

	काष्ठा usb_device *udev;
	काष्ठा net_device *netdev;

	atomic_t active_tx_urbs;
	काष्ठा usb_anchor tx_submitted;
	काष्ठा usb_8dev_tx_urb_context tx_contexts[MAX_TX_URBS];

	काष्ठा usb_anchor rx_submitted;

	काष्ठा can_berr_counter bec;

	u8 *cmd_msg_buffer;

	काष्ठा mutex usb_8dev_cmd_lock;

पूर्ण;

/* tx frame */
काष्ठा __packed usb_8dev_tx_msg अणु
	u8 begin;
	u8 flags;	/* RTR and EXT_ID flag */
	__be32 id;	/* upper 3 bits not used */
	u8 dlc;		/* data length code 0-8 bytes */
	u8 data[8];	/* 64-bit data */
	u8 end;
पूर्ण;

/* rx frame */
काष्ठा __packed usb_8dev_rx_msg अणु
	u8 begin;
	u8 type;		/* frame type */
	u8 flags;		/* RTR and EXT_ID flag */
	__be32 id;		/* upper 3 bits not used */
	u8 dlc;			/* data length code 0-8 bytes */
	u8 data[8];		/* 64-bit data */
	__be32 बारtamp;	/* 32-bit बारtamp */
	u8 end;
पूर्ण;

/* command frame */
काष्ठा __packed usb_8dev_cmd_msg अणु
	u8 begin;
	u8 channel;	/* unknown - always 0 */
	u8 command;	/* command to execute */
	u8 opt1;	/* optional parameter / वापस value */
	u8 opt2;	/* optional parameter 2 */
	u8 data[10];	/* optional parameter and data */
	u8 end;
पूर्ण;

अटल पूर्णांक usb_8dev_send_cmd_msg(काष्ठा usb_8dev_priv *priv, u8 *msg, पूर्णांक size)
अणु
	पूर्णांक actual_length;

	वापस usb_bulk_msg(priv->udev,
			    usb_sndbulkpipe(priv->udev, USB_8DEV_ENDP_CMD_TX),
			    msg, size, &actual_length, USB_8DEV_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक usb_8dev_रुको_cmd_msg(काष्ठा usb_8dev_priv *priv, u8 *msg, पूर्णांक size,
				पूर्णांक *actual_length)
अणु
	वापस usb_bulk_msg(priv->udev,
			    usb_rcvbulkpipe(priv->udev, USB_8DEV_ENDP_CMD_RX),
			    msg, size, actual_length, USB_8DEV_CMD_TIMEOUT);
पूर्ण

/* Send command to device and receive result.
 * Command was successful when opt1 = 0.
 */
अटल पूर्णांक usb_8dev_send_cmd(काष्ठा usb_8dev_priv *priv,
			     काष्ठा usb_8dev_cmd_msg *out,
			     काष्ठा usb_8dev_cmd_msg *in)
अणु
	पूर्णांक err;
	पूर्णांक num_bytes_पढ़ो;
	काष्ठा net_device *netdev;

	netdev = priv->netdev;

	out->begin = USB_8DEV_CMD_START;
	out->end = USB_8DEV_CMD_END;

	mutex_lock(&priv->usb_8dev_cmd_lock);

	स_नकल(priv->cmd_msg_buffer, out,
		माप(काष्ठा usb_8dev_cmd_msg));

	err = usb_8dev_send_cmd_msg(priv, priv->cmd_msg_buffer,
				    माप(काष्ठा usb_8dev_cmd_msg));
	अगर (err < 0) अणु
		netdev_err(netdev, "sending command message failed\n");
		जाओ failed;
	पूर्ण

	err = usb_8dev_रुको_cmd_msg(priv, priv->cmd_msg_buffer,
				    माप(काष्ठा usb_8dev_cmd_msg),
				    &num_bytes_पढ़ो);
	अगर (err < 0) अणु
		netdev_err(netdev, "no command message answer\n");
		जाओ failed;
	पूर्ण

	स_नकल(in, priv->cmd_msg_buffer, माप(काष्ठा usb_8dev_cmd_msg));

	अगर (in->begin != USB_8DEV_CMD_START || in->end != USB_8DEV_CMD_END ||
			num_bytes_पढ़ो != 16 || in->opt1 != 0)
		err = -EPROTO;

failed:
	mutex_unlock(&priv->usb_8dev_cmd_lock);
	वापस err;
पूर्ण

/* Send खोलो command to device */
अटल पूर्णांक usb_8dev_cmd_खोलो(काष्ठा usb_8dev_priv *priv)
अणु
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा usb_8dev_cmd_msg ouपंचांगsg;
	काष्ठा usb_8dev_cmd_msg inmsg;
	u32 ctrlmode = priv->can.ctrlmode;
	u32 flags = USB_8DEV_STATUS_FRAME;
	__be32 beflags;
	__be16 bebrp;

	स_रखो(&ouपंचांगsg, 0, माप(ouपंचांगsg));
	ouपंचांगsg.command = USB_8DEV_OPEN;
	ouपंचांगsg.opt1 = USB_8DEV_BAUD_MANUAL;
	ouपंचांगsg.data[0] = bt->prop_seg + bt->phase_seg1;
	ouपंचांगsg.data[1] = bt->phase_seg2;
	ouपंचांगsg.data[2] = bt->sjw;

	/* BRP */
	bebrp = cpu_to_be16((u16)bt->brp);
	स_नकल(&ouपंचांगsg.data[3], &bebrp, माप(bebrp));

	/* flags */
	अगर (ctrlmode & CAN_CTRLMODE_LOOPBACK)
		flags |= USB_8DEV_LOOPBACK;
	अगर (ctrlmode & CAN_CTRLMODE_LISTENONLY)
		flags |= USB_8DEV_SILENT;
	अगर (ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		flags |= USB_8DEV_DISABLE_AUTO_RESTRANS;

	beflags = cpu_to_be32(flags);
	स_नकल(&ouपंचांगsg.data[5], &beflags, माप(beflags));

	वापस usb_8dev_send_cmd(priv, &ouपंचांगsg, &inmsg);
पूर्ण

/* Send बंद command to device */
अटल पूर्णांक usb_8dev_cmd_बंद(काष्ठा usb_8dev_priv *priv)
अणु
	काष्ठा usb_8dev_cmd_msg inmsg;
	काष्ठा usb_8dev_cmd_msg ouपंचांगsg = अणु
		.channel = 0,
		.command = USB_8DEV_CLOSE,
		.opt1 = 0,
		.opt2 = 0
	पूर्ण;

	वापस usb_8dev_send_cmd(priv, &ouपंचांगsg, &inmsg);
पूर्ण

/* Get firmware and hardware version */
अटल पूर्णांक usb_8dev_cmd_version(काष्ठा usb_8dev_priv *priv, u32 *res)
अणु
	काष्ठा usb_8dev_cmd_msg	inmsg;
	काष्ठा usb_8dev_cmd_msg	ouपंचांगsg = अणु
		.channel = 0,
		.command = USB_8DEV_GET_SOFTW_HARDW_VER,
		.opt1 = 0,
		.opt2 = 0
	पूर्ण;

	पूर्णांक err = usb_8dev_send_cmd(priv, &ouपंचांगsg, &inmsg);
	अगर (err)
		वापस err;

	*res = be32_to_cpup((__be32 *)inmsg.data);

	वापस err;
पूर्ण

/* Set network device mode
 *
 * Maybe we should leave this function empty, because the device
 * set mode variable with खोलो command.
 */
अटल पूर्णांक usb_8dev_set_mode(काष्ठा net_device *netdev, क्रमागत can_mode mode)
अणु
	काष्ठा usb_8dev_priv *priv = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = usb_8dev_cmd_खोलो(priv);
		अगर (err)
			netdev_warn(netdev, "couldn't start device");
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

/* Read error/status frames */
अटल व्योम usb_8dev_rx_err_msg(काष्ठा usb_8dev_priv *priv,
				काष्ठा usb_8dev_rx_msg *msg)
अणु
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats = &priv->netdev->stats;

	/* Error message:
	 * byte 0: Status
	 * byte 1: bit   7: Receive Passive
	 * byte 1: bit 0-6: Receive Error Counter
	 * byte 2: Transmit Error Counter
	 * byte 3: Always 0 (maybe reserved क्रम future use)
	 */

	u8 state = msg->data[0];
	u8 rxerr = msg->data[1] & USB_8DEV_RP_MASK;
	u8 txerr = msg->data[2];
	पूर्णांक rx_errors = 0;
	पूर्णांक tx_errors = 0;

	skb = alloc_can_err_skb(priv->netdev, &cf);
	अगर (!skb)
		वापस;

	चयन (state) अणु
	हाल USB_8DEV_STATUSMSG_OK:
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		cf->can_id |= CAN_ERR_PROT;
		cf->data[2] = CAN_ERR_PROT_ACTIVE;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_BUSOFF:
		priv->can.state = CAN_STATE_BUS_OFF;
		cf->can_id |= CAN_ERR_BUSOFF;
		priv->can.can_stats.bus_off++;
		can_bus_off(priv->netdev);
		अवरोध;
	हाल USB_8DEV_STATUSMSG_OVERRUN:
	हाल USB_8DEV_STATUSMSG_BUSLIGHT:
	हाल USB_8DEV_STATUSMSG_BUSHEAVY:
		cf->can_id |= CAN_ERR_CRTL;
		अवरोध;
	शेष:
		priv->can.state = CAN_STATE_ERROR_WARNING;
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
		priv->can.can_stats.bus_error++;
		अवरोध;
	पूर्ण

	चयन (state) अणु
	हाल USB_8DEV_STATUSMSG_OK:
	हाल USB_8DEV_STATUSMSG_BUSOFF:
		अवरोध;
	हाल USB_8DEV_STATUSMSG_ACK:
		cf->can_id |= CAN_ERR_ACK;
		tx_errors = 1;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_CRC:
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		rx_errors = 1;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_BIT0:
		cf->data[2] |= CAN_ERR_PROT_BIT0;
		tx_errors = 1;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_BIT1:
		cf->data[2] |= CAN_ERR_PROT_BIT1;
		tx_errors = 1;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_FORM:
		cf->data[2] |= CAN_ERR_PROT_FORM;
		rx_errors = 1;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_STUFF:
		cf->data[2] |= CAN_ERR_PROT_STUFF;
		rx_errors = 1;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_OVERRUN:
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		rx_errors = 1;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_BUSLIGHT:
		priv->can.state = CAN_STATE_ERROR_WARNING;
		cf->data[1] = (txerr > rxerr) ?
			CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		priv->can.can_stats.error_warning++;
		अवरोध;
	हाल USB_8DEV_STATUSMSG_BUSHEAVY:
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		cf->data[1] = (txerr > rxerr) ?
			CAN_ERR_CRTL_TX_PASSIVE :
			CAN_ERR_CRTL_RX_PASSIVE;
		priv->can.can_stats.error_passive++;
		अवरोध;
	शेष:
		netdev_warn(priv->netdev,
			    "Unknown status/error message (%d)\n", state);
		अवरोध;
	पूर्ण

	अगर (tx_errors) अणु
		cf->data[2] |= CAN_ERR_PROT_TX;
		stats->tx_errors++;
	पूर्ण

	अगर (rx_errors)
		stats->rx_errors++;

	cf->data[6] = txerr;
	cf->data[7] = rxerr;

	priv->bec.txerr = txerr;
	priv->bec.rxerr = rxerr;

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

/* Read data and status frames */
अटल व्योम usb_8dev_rx_can_msg(काष्ठा usb_8dev_priv *priv,
				काष्ठा usb_8dev_rx_msg *msg)
अणु
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats = &priv->netdev->stats;

	अगर (msg->type == USB_8DEV_TYPE_ERROR_FRAME &&
		   msg->flags == USB_8DEV_ERR_FLAG) अणु
		usb_8dev_rx_err_msg(priv, msg);
	पूर्ण अन्यथा अगर (msg->type == USB_8DEV_TYPE_CAN_FRAME) अणु
		skb = alloc_can_skb(priv->netdev, &cf);
		अगर (!skb)
			वापस;

		cf->can_id = be32_to_cpu(msg->id);
		can_frame_set_cc_len(cf, msg->dlc & 0xF, priv->can.ctrlmode);

		अगर (msg->flags & USB_8DEV_EXTID)
			cf->can_id |= CAN_EFF_FLAG;

		अगर (msg->flags & USB_8DEV_RTR)
			cf->can_id |= CAN_RTR_FLAG;
		अन्यथा
			स_नकल(cf->data, msg->data, cf->len);

		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_rx(skb);

		can_led_event(priv->netdev, CAN_LED_EVENT_RX);
	पूर्ण अन्यथा अणु
		netdev_warn(priv->netdev, "frame type %d unknown",
			 msg->type);
	पूर्ण

पूर्ण

/* Callback क्रम पढ़ोing data from device
 *
 * Check urb status, call पढ़ो function and resubmit urb पढ़ो operation.
 */
अटल व्योम usb_8dev_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_8dev_priv *priv = urb->context;
	काष्ठा net_device *netdev;
	पूर्णांक retval;
	पूर्णांक pos = 0;

	netdev = priv->netdev;

	अगर (!netअगर_device_present(netdev))
		वापस;

	चयन (urb->status) अणु
	हाल 0: /* success */
		अवरोध;

	हाल -ENOENT:
	हाल -EPIPE:
	हाल -EPROTO:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		netdev_info(netdev, "Rx URB aborted (%d)\n",
			 urb->status);
		जाओ resubmit_urb;
	पूर्ण

	जबतक (pos < urb->actual_length) अणु
		काष्ठा usb_8dev_rx_msg *msg;

		अगर (pos + माप(काष्ठा usb_8dev_rx_msg) > urb->actual_length) अणु
			netdev_err(priv->netdev, "format error\n");
			अवरोध;
		पूर्ण

		msg = (काष्ठा usb_8dev_rx_msg *)(urb->transfer_buffer + pos);
		usb_8dev_rx_can_msg(priv, msg);

		pos += माप(काष्ठा usb_8dev_rx_msg);
	पूर्ण

resubmit_urb:
	usb_fill_bulk_urb(urb, priv->udev,
			  usb_rcvbulkpipe(priv->udev, USB_8DEV_ENDP_DATA_RX),
			  urb->transfer_buffer, RX_BUFFER_SIZE,
			  usb_8dev_पढ़ो_bulk_callback, priv);

	retval = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (retval == -ENODEV)
		netअगर_device_detach(netdev);
	अन्यथा अगर (retval)
		netdev_err(netdev,
			"failed resubmitting read bulk urb: %d\n", retval);
पूर्ण

/* Callback handler क्रम ग_लिखो operations
 *
 * Free allocated buffers, check transmit status and
 * calculate statistic.
 */
अटल व्योम usb_8dev_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_8dev_tx_urb_context *context = urb->context;
	काष्ठा usb_8dev_priv *priv;
	काष्ठा net_device *netdev;

	BUG_ON(!context);

	priv = context->priv;
	netdev = priv->netdev;

	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);

	atomic_dec(&priv->active_tx_urbs);

	अगर (!netअगर_device_present(netdev))
		वापस;

	अगर (urb->status)
		netdev_info(netdev, "Tx URB aborted (%d)\n",
			 urb->status);

	netdev->stats.tx_packets++;
	netdev->stats.tx_bytes += context->dlc;

	can_get_echo_skb(netdev, context->echo_index, शून्य);

	can_led_event(netdev, CAN_LED_EVENT_TX);

	/* Release context */
	context->echo_index = MAX_TX_URBS;

	netअगर_wake_queue(netdev);
पूर्ण

/* Send data to device */
अटल netdev_tx_t usb_8dev_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *netdev)
अणु
	काष्ठा usb_8dev_priv *priv = netdev_priv(netdev);
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा can_frame *cf = (काष्ठा can_frame *) skb->data;
	काष्ठा usb_8dev_tx_msg *msg;
	काष्ठा urb *urb;
	काष्ठा usb_8dev_tx_urb_context *context = शून्य;
	u8 *buf;
	पूर्णांक i, err;
	माप_प्रकार size = माप(काष्ठा usb_8dev_tx_msg);

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	/* create a URB, and a buffer क्रम it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ nomem;

	buf = usb_alloc_coherent(priv->udev, size, GFP_ATOMIC,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		netdev_err(netdev, "No memory left for USB buffer\n");
		जाओ nomembuf;
	पूर्ण

	स_रखो(buf, 0, size);

	msg = (काष्ठा usb_8dev_tx_msg *)buf;
	msg->begin = USB_8DEV_DATA_START;
	msg->flags = 0x00;

	अगर (cf->can_id & CAN_RTR_FLAG)
		msg->flags |= USB_8DEV_RTR;

	अगर (cf->can_id & CAN_EFF_FLAG)
		msg->flags |= USB_8DEV_EXTID;

	msg->id = cpu_to_be32(cf->can_id & CAN_ERR_MASK);
	msg->dlc = can_get_cc_dlc(cf, priv->can.ctrlmode);
	स_नकल(msg->data, cf->data, cf->len);
	msg->end = USB_8DEV_DATA_END;

	क्रम (i = 0; i < MAX_TX_URBS; i++) अणु
		अगर (priv->tx_contexts[i].echo_index == MAX_TX_URBS) अणु
			context = &priv->tx_contexts[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* May never happen! When this happens we'd more URBs in flight as
	 * allowed (MAX_TX_URBS).
	 */
	अगर (!context)
		जाओ noमुक्तcontext;

	context->priv = priv;
	context->echo_index = i;
	context->dlc = cf->len;

	usb_fill_bulk_urb(urb, priv->udev,
			  usb_sndbulkpipe(priv->udev, USB_8DEV_ENDP_DATA_TX),
			  buf, size, usb_8dev_ग_लिखो_bulk_callback, context);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &priv->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&priv->active_tx_urbs);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(err))
		जाओ failed;
	अन्यथा अगर (atomic_पढ़ो(&priv->active_tx_urbs) >= MAX_TX_URBS)
		/* Slow करोwn tx path */
		netअगर_stop_queue(netdev);

	/* Release our reference to this URB, the USB core will eventually मुक्त
	 * it entirely.
	 */
	usb_मुक्त_urb(urb);

	वापस NETDEV_TX_OK;

noमुक्तcontext:
	usb_मुक्त_coherent(priv->udev, size, buf, urb->transfer_dma);
	usb_मुक्त_urb(urb);

	netdev_warn(netdev, "couldn't find free context");

	वापस NETDEV_TX_BUSY;

failed:
	can_मुक्त_echo_skb(netdev, context->echo_index, शून्य);

	usb_unanchor_urb(urb);
	usb_मुक्त_coherent(priv->udev, size, buf, urb->transfer_dma);

	atomic_dec(&priv->active_tx_urbs);

	अगर (err == -ENODEV)
		netअगर_device_detach(netdev);
	अन्यथा
		netdev_warn(netdev, "failed tx_urb %d\n", err);

nomembuf:
	usb_मुक्त_urb(urb);

nomem:
	dev_kमुक्त_skb(skb);
	stats->tx_dropped++;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक usb_8dev_get_berr_counter(स्थिर काष्ठा net_device *netdev,
				     काष्ठा can_berr_counter *bec)
अणु
	काष्ठा usb_8dev_priv *priv = netdev_priv(netdev);

	bec->txerr = priv->bec.txerr;
	bec->rxerr = priv->bec.rxerr;

	वापस 0;
पूर्ण

/* Start USB device */
अटल पूर्णांक usb_8dev_start(काष्ठा usb_8dev_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक err, i;

	क्रम (i = 0; i < MAX_RX_URBS; i++) अणु
		काष्ठा urb *urb = शून्य;
		u8 *buf;

		/* create a URB, and a buffer क्रम it */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		buf = usb_alloc_coherent(priv->udev, RX_BUFFER_SIZE, GFP_KERNEL,
					 &urb->transfer_dma);
		अगर (!buf) अणु
			netdev_err(netdev, "No memory left for USB buffer\n");
			usb_मुक्त_urb(urb);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		usb_fill_bulk_urb(urb, priv->udev,
				  usb_rcvbulkpipe(priv->udev,
						  USB_8DEV_ENDP_DATA_RX),
				  buf, RX_BUFFER_SIZE,
				  usb_8dev_पढ़ो_bulk_callback, priv);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &priv->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			usb_unanchor_urb(urb);
			usb_मुक्त_coherent(priv->udev, RX_BUFFER_SIZE, buf,
					  urb->transfer_dma);
			usb_मुक्त_urb(urb);
			अवरोध;
		पूर्ण

		/* Drop reference, USB core will take care of मुक्तing it */
		usb_मुक्त_urb(urb);
	पूर्ण

	/* Did we submit any URBs */
	अगर (i == 0) अणु
		netdev_warn(netdev, "couldn't setup read URBs\n");
		वापस err;
	पूर्ण

	/* Warn अगर we've couldn't transmit all the URBs */
	अगर (i < MAX_RX_URBS)
		netdev_warn(netdev, "rx performance may be slow\n");

	err = usb_8dev_cmd_खोलो(priv);
	अगर (err)
		जाओ failed;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस 0;

failed:
	अगर (err == -ENODEV)
		netअगर_device_detach(priv->netdev);

	netdev_warn(netdev, "couldn't submit control: %d\n", err);

	वापस err;
पूर्ण

/* Open USB device */
अटल पूर्णांक usb_8dev_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा usb_8dev_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	/* common खोलो */
	err = खोलो_candev(netdev);
	अगर (err)
		वापस err;

	can_led_event(netdev, CAN_LED_EVENT_OPEN);

	/* finally start device */
	err = usb_8dev_start(priv);
	अगर (err) अणु
		अगर (err == -ENODEV)
			netअगर_device_detach(priv->netdev);

		netdev_warn(netdev, "couldn't start device: %d\n",
			 err);

		बंद_candev(netdev);

		वापस err;
	पूर्ण

	netअगर_start_queue(netdev);

	वापस 0;
पूर्ण

अटल व्योम unlink_all_urbs(काष्ठा usb_8dev_priv *priv)
अणु
	पूर्णांक i;

	usb_समाप्त_anchored_urbs(&priv->rx_submitted);

	usb_समाप्त_anchored_urbs(&priv->tx_submitted);
	atomic_set(&priv->active_tx_urbs, 0);

	क्रम (i = 0; i < MAX_TX_URBS; i++)
		priv->tx_contexts[i].echo_index = MAX_TX_URBS;
पूर्ण

/* Close USB device */
अटल पूर्णांक usb_8dev_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा usb_8dev_priv *priv = netdev_priv(netdev);
	पूर्णांक err = 0;

	/* Send CLOSE command to CAN controller */
	err = usb_8dev_cmd_बंद(priv);
	अगर (err)
		netdev_warn(netdev, "couldn't stop device");

	priv->can.state = CAN_STATE_STOPPED;

	netअगर_stop_queue(netdev);

	/* Stop polling */
	unlink_all_urbs(priv);

	बंद_candev(netdev);

	can_led_event(netdev, CAN_LED_EVENT_STOP);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops usb_8dev_netdev_ops = अणु
	.nकरो_खोलो = usb_8dev_खोलो,
	.nकरो_stop = usb_8dev_बंद,
	.nकरो_start_xmit = usb_8dev_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर usb_8dev_bittiming_स्थिर = अणु
	.name = "usb_8dev",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

/* Probe USB device
 *
 * Check device and firmware.
 * Set supported modes and bittiming स्थिरants.
 * Allocate some memory.
 */
अटल पूर्णांक usb_8dev_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा net_device *netdev;
	काष्ठा usb_8dev_priv *priv;
	पूर्णांक i, err = -ENOMEM;
	u32 version;
	अक्षर buf[18];
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	/* product id looks strange, better we also check iProduct string */
	अगर (usb_string(usbdev, usbdev->descriptor.iProduct, buf,
		       माप(buf)) > 0 && म_भेद(buf, "USB2CAN converter")) अणु
		dev_info(&usbdev->dev, "ignoring: not an USB2CAN converter\n");
		वापस -ENODEV;
	पूर्ण

	netdev = alloc_candev(माप(काष्ठा usb_8dev_priv), MAX_TX_URBS);
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "Couldn't alloc candev\n");
		वापस -ENOMEM;
	पूर्ण

	priv = netdev_priv(netdev);

	priv->udev = usbdev;
	priv->netdev = netdev;

	priv->can.state = CAN_STATE_STOPPED;
	priv->can.घड़ी.freq = USB_8DEV_ABP_CLOCK;
	priv->can.bittiming_स्थिर = &usb_8dev_bittiming_स्थिर;
	priv->can.करो_set_mode = usb_8dev_set_mode;
	priv->can.करो_get_berr_counter = usb_8dev_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
				      CAN_CTRLMODE_LISTENONLY |
				      CAN_CTRLMODE_ONE_SHOT |
				      CAN_CTRLMODE_CC_LEN8_DLC;

	netdev->netdev_ops = &usb_8dev_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	init_usb_anchor(&priv->rx_submitted);

	init_usb_anchor(&priv->tx_submitted);
	atomic_set(&priv->active_tx_urbs, 0);

	क्रम (i = 0; i < MAX_TX_URBS; i++)
		priv->tx_contexts[i].echo_index = MAX_TX_URBS;

	priv->cmd_msg_buffer = devm_kzalloc(&पूर्णांकf->dev, माप(काष्ठा usb_8dev_cmd_msg),
					    GFP_KERNEL);
	अगर (!priv->cmd_msg_buffer)
		जाओ cleanup_candev;

	usb_set_पूर्णांकfdata(पूर्णांकf, priv);

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);

	mutex_init(&priv->usb_8dev_cmd_lock);

	err = रेजिस्टर_candev(netdev);
	अगर (err) अणु
		netdev_err(netdev,
			"couldn't register CAN device: %d\n", err);
		जाओ cleanup_candev;
	पूर्ण

	err = usb_8dev_cmd_version(priv, &version);
	अगर (err) अणु
		netdev_err(netdev, "can't get firmware version\n");
		जाओ cleanup_unरेजिस्टर_candev;
	पूर्ण अन्यथा अणु
		netdev_info(netdev,
			 "firmware: %d.%d, hardware: %d.%d\n",
			 (version>>24) & 0xff, (version>>16) & 0xff,
			 (version>>8) & 0xff, version & 0xff);
	पूर्ण

	devm_can_led_init(netdev);

	वापस 0;

cleanup_unरेजिस्टर_candev:
	unरेजिस्टर_netdev(priv->netdev);

cleanup_candev:
	मुक्त_candev(netdev);

	वापस err;

पूर्ण

/* Called by the usb core when driver is unloaded or device is हटाओd */
अटल व्योम usb_8dev_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_8dev_priv *priv = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (priv) अणु
		netdev_info(priv->netdev, "device disconnected\n");

		unरेजिस्टर_netdev(priv->netdev);
		unlink_all_urbs(priv);
		मुक्त_candev(priv->netdev);
	पूर्ण

पूर्ण

अटल काष्ठा usb_driver usb_8dev_driver = अणु
	.name =		"usb_8dev",
	.probe =	usb_8dev_probe,
	.disconnect =	usb_8dev_disconnect,
	.id_table =	usb_8dev_table,
पूर्ण;

module_usb_driver(usb_8dev_driver);

MODULE_AUTHOR("Bernd Krumboeck <krumboeck@universalnet.at>");
MODULE_DESCRIPTION("CAN driver for 8 devices USB2CAN interfaces");
MODULE_LICENSE("GPL v2");
