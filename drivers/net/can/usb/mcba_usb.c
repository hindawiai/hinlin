<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* SocketCAN driver क्रम Microchip CAN BUS Analyzer Tool
 *
 * Copyright (C) 2017 Mobica Limited
 *
 * This driver is inspired by the 4.6.2 version of net/can/usb/usb_8dev.c
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

/* venकरोr and product id */
#घोषणा MCBA_MODULE_NAME "mcba_usb"
#घोषणा MCBA_VENDOR_ID 0x04d8
#घोषणा MCBA_PRODUCT_ID 0x0a30

/* driver स्थिरants */
#घोषणा MCBA_MAX_RX_URBS 20
#घोषणा MCBA_MAX_TX_URBS 20
#घोषणा MCBA_CTX_FREE MCBA_MAX_TX_URBS

/* RX buffer must be bigger than msg size since at the
 * beginning USB messages are stacked.
 */
#घोषणा MCBA_USB_RX_BUFF_SIZE 64
#घोषणा MCBA_USB_TX_BUFF_SIZE (माप(काष्ठा mcba_usb_msg))

/* MCBA endpoपूर्णांक numbers */
#घोषणा MCBA_USB_EP_IN 1
#घोषणा MCBA_USB_EP_OUT 1

/* Microchip command id */
#घोषणा MBCA_CMD_RECEIVE_MESSAGE 0xE3
#घोषणा MBCA_CMD_I_AM_ALIVE_FROM_CAN 0xF5
#घोषणा MBCA_CMD_I_AM_ALIVE_FROM_USB 0xF7
#घोषणा MBCA_CMD_CHANGE_BIT_RATE 0xA1
#घोषणा MBCA_CMD_TRANSMIT_MESSAGE_EV 0xA3
#घोषणा MBCA_CMD_SETUP_TERMINATION_RESISTANCE 0xA8
#घोषणा MBCA_CMD_READ_FW_VERSION 0xA9
#घोषणा MBCA_CMD_NOTHING_TO_SEND 0xFF
#घोषणा MBCA_CMD_TRANSMIT_MESSAGE_RSP 0xE2

#घोषणा MCBA_VER_REQ_USB 1
#घोषणा MCBA_VER_REQ_CAN 2

#घोषणा MCBA_SIDL_EXID_MASK 0x8
#घोषणा MCBA_DLC_MASK 0xf
#घोषणा MCBA_DLC_RTR_MASK 0x40

#घोषणा MCBA_CAN_STATE_WRN_TH 95
#घोषणा MCBA_CAN_STATE_ERR_PSV_TH 127

#घोषणा MCBA_TERMINATION_DISABLED CAN_TERMINATION_DISABLED
#घोषणा MCBA_TERMINATION_ENABLED 120

काष्ठा mcba_usb_ctx अणु
	काष्ठा mcba_priv *priv;
	u32 ndx;
	u8 dlc;
	bool can;
पूर्ण;

/* Structure to hold all of our device specअगरic stuff */
काष्ठा mcba_priv अणु
	काष्ठा can_priv can; /* must be the first member */
	काष्ठा sk_buff *echo_skb[MCBA_MAX_TX_URBS];
	काष्ठा mcba_usb_ctx tx_context[MCBA_MAX_TX_URBS];
	काष्ठा usb_device *udev;
	काष्ठा net_device *netdev;
	काष्ठा usb_anchor tx_submitted;
	काष्ठा usb_anchor rx_submitted;
	काष्ठा can_berr_counter bec;
	bool usb_ka_first_pass;
	bool can_ka_first_pass;
	bool can_speed_check;
	atomic_t मुक्त_ctx_cnt;
	व्योम *rxbuf[MCBA_MAX_RX_URBS];
	dma_addr_t rxbuf_dma[MCBA_MAX_RX_URBS];
पूर्ण;

/* CAN frame */
काष्ठा __packed mcba_usb_msg_can अणु
	u8 cmd_id;
	__be16 eid;
	__be16 sid;
	u8 dlc;
	u8 data[8];
	u8 बारtamp[4];
	u8 checksum;
पूर्ण;

/* command frame */
काष्ठा __packed mcba_usb_msg अणु
	u8 cmd_id;
	u8 unused[18];
पूर्ण;

काष्ठा __packed mcba_usb_msg_ka_usb अणु
	u8 cmd_id;
	u8 termination_state;
	u8 soft_ver_major;
	u8 soft_ver_minor;
	u8 unused[15];
पूर्ण;

काष्ठा __packed mcba_usb_msg_ka_can अणु
	u8 cmd_id;
	u8 tx_err_cnt;
	u8 rx_err_cnt;
	u8 rx_buff_ovfl;
	u8 tx_bus_off;
	__be16 can_bitrate;
	__le16 rx_lost;
	u8 can_stat;
	u8 soft_ver_major;
	u8 soft_ver_minor;
	u8 debug_mode;
	u8 test_complete;
	u8 test_result;
	u8 unused[4];
पूर्ण;

काष्ठा __packed mcba_usb_msg_change_bitrate अणु
	u8 cmd_id;
	__be16 bitrate;
	u8 unused[16];
पूर्ण;

काष्ठा __packed mcba_usb_msg_termination अणु
	u8 cmd_id;
	u8 termination;
	u8 unused[17];
पूर्ण;

काष्ठा __packed mcba_usb_msg_fw_ver अणु
	u8 cmd_id;
	u8 pic;
	u8 unused[17];
पूर्ण;

अटल स्थिर काष्ठा usb_device_id mcba_usb_table[] = अणु
	अणु USB_DEVICE(MCBA_VENDOR_ID, MCBA_PRODUCT_ID) पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, mcba_usb_table);

अटल स्थिर u16 mcba_termination[] = अणु MCBA_TERMINATION_DISABLED,
					MCBA_TERMINATION_ENABLED पूर्ण;

अटल स्थिर u32 mcba_bitrate[] = अणु 20000,  33333,  50000,  80000,  83333,
				    100000, 125000, 150000, 175000, 200000,
				    225000, 250000, 275000, 300000, 500000,
				    625000, 800000, 1000000 पूर्ण;

अटल अंतरभूत व्योम mcba_init_ctx(काष्ठा mcba_priv *priv)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < MCBA_MAX_TX_URBS; i++) अणु
		priv->tx_context[i].ndx = MCBA_CTX_FREE;
		priv->tx_context[i].priv = priv;
	पूर्ण

	atomic_set(&priv->मुक्त_ctx_cnt, ARRAY_SIZE(priv->tx_context));
पूर्ण

अटल अंतरभूत काष्ठा mcba_usb_ctx *mcba_usb_get_मुक्त_ctx(काष्ठा mcba_priv *priv,
							 काष्ठा can_frame *cf)
अणु
	पूर्णांक i = 0;
	काष्ठा mcba_usb_ctx *ctx = शून्य;

	क्रम (i = 0; i < MCBA_MAX_TX_URBS; i++) अणु
		अगर (priv->tx_context[i].ndx == MCBA_CTX_FREE) अणु
			ctx = &priv->tx_context[i];
			ctx->ndx = i;

			अगर (cf) अणु
				ctx->can = true;
				ctx->dlc = cf->len;
			पूर्ण अन्यथा अणु
				ctx->can = false;
				ctx->dlc = 0;
			पूर्ण

			atomic_dec(&priv->मुक्त_ctx_cnt);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!atomic_पढ़ो(&priv->मुक्त_ctx_cnt))
		/* That was the last मुक्त ctx. Slow करोwn tx path */
		netअगर_stop_queue(priv->netdev);

	वापस ctx;
पूर्ण

/* mcba_usb_मुक्त_ctx and mcba_usb_get_मुक्त_ctx are executed by dअगरferent
 * thपढ़ोs. The order of execution in below function is important.
 */
अटल अंतरभूत व्योम mcba_usb_मुक्त_ctx(काष्ठा mcba_usb_ctx *ctx)
अणु
	/* Increase number of मुक्त ctxs beक्रमe मुक्तing ctx */
	atomic_inc(&ctx->priv->मुक्त_ctx_cnt);

	ctx->ndx = MCBA_CTX_FREE;

	/* Wake up the queue once ctx is marked मुक्त */
	netअगर_wake_queue(ctx->priv->netdev);
पूर्ण

अटल व्योम mcba_usb_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा mcba_usb_ctx *ctx = urb->context;
	काष्ठा net_device *netdev;

	WARN_ON(!ctx);

	netdev = ctx->priv->netdev;

	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);

	अगर (ctx->can) अणु
		अगर (!netअगर_device_present(netdev))
			वापस;

		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += ctx->dlc;

		can_led_event(netdev, CAN_LED_EVENT_TX);
		can_get_echo_skb(netdev, ctx->ndx, शून्य);
	पूर्ण

	अगर (urb->status)
		netdev_info(netdev, "Tx URB aborted (%d)\n", urb->status);

	/* Release the context */
	mcba_usb_मुक्त_ctx(ctx);
पूर्ण

/* Send data to device */
अटल netdev_tx_t mcba_usb_xmit(काष्ठा mcba_priv *priv,
				 काष्ठा mcba_usb_msg *usb_msg,
				 काष्ठा mcba_usb_ctx *ctx)
अणु
	काष्ठा urb *urb;
	u8 *buf;
	पूर्णांक err;

	/* create a URB, and a buffer क्रम it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		वापस -ENOMEM;

	buf = usb_alloc_coherent(priv->udev, MCBA_USB_TX_BUFF_SIZE, GFP_ATOMIC,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ nomembuf;
	पूर्ण

	स_नकल(buf, usb_msg, MCBA_USB_TX_BUFF_SIZE);

	usb_fill_bulk_urb(urb, priv->udev,
			  usb_sndbulkpipe(priv->udev, MCBA_USB_EP_OUT), buf,
			  MCBA_USB_TX_BUFF_SIZE, mcba_usb_ग_लिखो_bulk_callback,
			  ctx);

	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &priv->tx_submitted);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(err))
		जाओ failed;

	/* Release our reference to this URB, the USB core will eventually मुक्त
	 * it entirely.
	 */
	usb_मुक्त_urb(urb);

	वापस 0;

failed:
	usb_unanchor_urb(urb);
	usb_मुक्त_coherent(priv->udev, MCBA_USB_TX_BUFF_SIZE, buf,
			  urb->transfer_dma);

	अगर (err == -ENODEV)
		netअगर_device_detach(priv->netdev);
	अन्यथा
		netdev_warn(priv->netdev, "failed tx_urb %d\n", err);

nomembuf:
	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

/* Send data to device */
अटल netdev_tx_t mcba_usb_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *netdev)
अणु
	काष्ठा mcba_priv *priv = netdev_priv(netdev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	काष्ठा mcba_usb_ctx *ctx = शून्य;
	काष्ठा net_device_stats *stats = &priv->netdev->stats;
	u16 sid;
	पूर्णांक err;
	काष्ठा mcba_usb_msg_can usb_msg = अणु
		.cmd_id = MBCA_CMD_TRANSMIT_MESSAGE_EV
	पूर्ण;

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	ctx = mcba_usb_get_मुक्त_ctx(priv, cf);
	अगर (!ctx)
		वापस NETDEV_TX_BUSY;

	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		/* SIDH    | SIDL                 | EIDH   | EIDL
		 * 28 - 21 | 20 19 18 x x x 17 16 | 15 - 8 | 7 - 0
		 */
		sid = MCBA_SIDL_EXID_MASK;
		/* store 28-18 bits */
		sid |= (cf->can_id & 0x1ffc0000) >> 13;
		/* store 17-16 bits */
		sid |= (cf->can_id & 0x30000) >> 16;
		put_unaligned_be16(sid, &usb_msg.sid);

		/* store 15-0 bits */
		put_unaligned_be16(cf->can_id & 0xffff, &usb_msg.eid);
	पूर्ण अन्यथा अणु
		/* SIDH   | SIDL
		 * 10 - 3 | 2 1 0 x x x x x
		 */
		put_unaligned_be16((cf->can_id & CAN_SFF_MASK) << 5,
				   &usb_msg.sid);
		usb_msg.eid = 0;
	पूर्ण

	usb_msg.dlc = cf->len;

	स_नकल(usb_msg.data, cf->data, usb_msg.dlc);

	अगर (cf->can_id & CAN_RTR_FLAG)
		usb_msg.dlc |= MCBA_DLC_RTR_MASK;

	can_put_echo_skb(skb, priv->netdev, ctx->ndx, 0);

	err = mcba_usb_xmit(priv, (काष्ठा mcba_usb_msg *)&usb_msg, ctx);
	अगर (err)
		जाओ xmit_failed;

	वापस NETDEV_TX_OK;

xmit_failed:
	can_मुक्त_echo_skb(priv->netdev, ctx->ndx, शून्य);
	mcba_usb_मुक्त_ctx(ctx);
	dev_kमुक्त_skb(skb);
	stats->tx_dropped++;

	वापस NETDEV_TX_OK;
पूर्ण

/* Send cmd to device */
अटल व्योम mcba_usb_xmit_cmd(काष्ठा mcba_priv *priv,
			      काष्ठा mcba_usb_msg *usb_msg)
अणु
	काष्ठा mcba_usb_ctx *ctx = शून्य;
	पूर्णांक err;

	ctx = mcba_usb_get_मुक्त_ctx(priv, शून्य);
	अगर (!ctx) अणु
		netdev_err(priv->netdev,
			   "Lack of free ctx. Sending (%d) cmd aborted",
			   usb_msg->cmd_id);

		वापस;
	पूर्ण

	err = mcba_usb_xmit(priv, usb_msg, ctx);
	अगर (err)
		netdev_err(priv->netdev, "Failed to send cmd (%d)",
			   usb_msg->cmd_id);
पूर्ण

अटल व्योम mcba_usb_xmit_change_bitrate(काष्ठा mcba_priv *priv, u16 bitrate)
अणु
	काष्ठा mcba_usb_msg_change_bitrate usb_msg = अणु
		.cmd_id = MBCA_CMD_CHANGE_BIT_RATE
	पूर्ण;

	put_unaligned_be16(bitrate, &usb_msg.bitrate);

	mcba_usb_xmit_cmd(priv, (काष्ठा mcba_usb_msg *)&usb_msg);
पूर्ण

अटल व्योम mcba_usb_xmit_पढ़ो_fw_ver(काष्ठा mcba_priv *priv, u8 pic)
अणु
	काष्ठा mcba_usb_msg_fw_ver usb_msg = अणु
		.cmd_id = MBCA_CMD_READ_FW_VERSION,
		.pic = pic
	पूर्ण;

	mcba_usb_xmit_cmd(priv, (काष्ठा mcba_usb_msg *)&usb_msg);
पूर्ण

अटल व्योम mcba_usb_process_can(काष्ठा mcba_priv *priv,
				 काष्ठा mcba_usb_msg_can *msg)
अणु
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats = &priv->netdev->stats;
	u16 sid;

	skb = alloc_can_skb(priv->netdev, &cf);
	अगर (!skb)
		वापस;

	sid = get_unaligned_be16(&msg->sid);

	अगर (sid & MCBA_SIDL_EXID_MASK) अणु
		/* SIDH    | SIDL                 | EIDH   | EIDL
		 * 28 - 21 | 20 19 18 x x x 17 16 | 15 - 8 | 7 - 0
		 */
		cf->can_id = CAN_EFF_FLAG;

		/* store 28-18 bits */
		cf->can_id |= (sid & 0xffe0) << 13;
		/* store 17-16 bits */
		cf->can_id |= (sid & 3) << 16;
		/* store 15-0 bits */
		cf->can_id |= get_unaligned_be16(&msg->eid);
	पूर्ण अन्यथा अणु
		/* SIDH   | SIDL
		 * 10 - 3 | 2 1 0 x x x x x
		 */
		cf->can_id = (sid & 0xffe0) >> 5;
	पूर्ण

	अगर (msg->dlc & MCBA_DLC_RTR_MASK)
		cf->can_id |= CAN_RTR_FLAG;

	cf->len = can_cc_dlc2len(msg->dlc & MCBA_DLC_MASK);

	स_नकल(cf->data, msg->data, cf->len);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	can_led_event(priv->netdev, CAN_LED_EVENT_RX);
	netअगर_rx(skb);
पूर्ण

अटल व्योम mcba_usb_process_ka_usb(काष्ठा mcba_priv *priv,
				    काष्ठा mcba_usb_msg_ka_usb *msg)
अणु
	अगर (unlikely(priv->usb_ka_first_pass)) अणु
		netdev_info(priv->netdev, "PIC USB version %u.%u\n",
			    msg->soft_ver_major, msg->soft_ver_minor);

		priv->usb_ka_first_pass = false;
	पूर्ण

	अगर (msg->termination_state)
		priv->can.termination = MCBA_TERMINATION_ENABLED;
	अन्यथा
		priv->can.termination = MCBA_TERMINATION_DISABLED;
पूर्ण

अटल u32 convert_can2host_bitrate(काष्ठा mcba_usb_msg_ka_can *msg)
अणु
	स्थिर u32 bitrate = get_unaligned_be16(&msg->can_bitrate);

	अगर ((bitrate == 33) || (bitrate == 83))
		वापस bitrate * 1000 + 333;
	अन्यथा
		वापस bitrate * 1000;
पूर्ण

अटल व्योम mcba_usb_process_ka_can(काष्ठा mcba_priv *priv,
				    काष्ठा mcba_usb_msg_ka_can *msg)
अणु
	अगर (unlikely(priv->can_ka_first_pass)) अणु
		netdev_info(priv->netdev, "PIC CAN version %u.%u\n",
			    msg->soft_ver_major, msg->soft_ver_minor);

		priv->can_ka_first_pass = false;
	पूर्ण

	अगर (unlikely(priv->can_speed_check)) अणु
		स्थिर u32 bitrate = convert_can2host_bitrate(msg);

		priv->can_speed_check = false;

		अगर (bitrate != priv->can.bittiming.bitrate)
			netdev_err(
			    priv->netdev,
			    "Wrong bitrate reported by the device (%u). Expected %u",
			    bitrate, priv->can.bittiming.bitrate);
	पूर्ण

	priv->bec.txerr = msg->tx_err_cnt;
	priv->bec.rxerr = msg->rx_err_cnt;

	अगर (msg->tx_bus_off)
		priv->can.state = CAN_STATE_BUS_OFF;

	अन्यथा अगर ((priv->bec.txerr > MCBA_CAN_STATE_ERR_PSV_TH) ||
		 (priv->bec.rxerr > MCBA_CAN_STATE_ERR_PSV_TH))
		priv->can.state = CAN_STATE_ERROR_PASSIVE;

	अन्यथा अगर ((priv->bec.txerr > MCBA_CAN_STATE_WRN_TH) ||
		 (priv->bec.rxerr > MCBA_CAN_STATE_WRN_TH))
		priv->can.state = CAN_STATE_ERROR_WARNING;
पूर्ण

अटल व्योम mcba_usb_process_rx(काष्ठा mcba_priv *priv,
				काष्ठा mcba_usb_msg *msg)
अणु
	चयन (msg->cmd_id) अणु
	हाल MBCA_CMD_I_AM_ALIVE_FROM_CAN:
		mcba_usb_process_ka_can(priv,
					(काष्ठा mcba_usb_msg_ka_can *)msg);
		अवरोध;

	हाल MBCA_CMD_I_AM_ALIVE_FROM_USB:
		mcba_usb_process_ka_usb(priv,
					(काष्ठा mcba_usb_msg_ka_usb *)msg);
		अवरोध;

	हाल MBCA_CMD_RECEIVE_MESSAGE:
		mcba_usb_process_can(priv, (काष्ठा mcba_usb_msg_can *)msg);
		अवरोध;

	हाल MBCA_CMD_NOTHING_TO_SEND:
		/* Side effect of communication between PIC_USB and PIC_CAN.
		 * PIC_CAN is telling us that it has nothing to send
		 */
		अवरोध;

	हाल MBCA_CMD_TRANSMIT_MESSAGE_RSP:
		/* Transmission response from the device containing बारtamp */
		अवरोध;

	शेष:
		netdev_warn(priv->netdev, "Unsupported msg (0x%X)",
			    msg->cmd_id);
		अवरोध;
	पूर्ण
पूर्ण

/* Callback क्रम पढ़ोing data from device
 *
 * Check urb status, call पढ़ो function and resubmit urb पढ़ो operation.
 */
अटल व्योम mcba_usb_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा mcba_priv *priv = urb->context;
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
		netdev_info(netdev, "Rx URB aborted (%d)\n", urb->status);

		जाओ resubmit_urb;
	पूर्ण

	जबतक (pos < urb->actual_length) अणु
		काष्ठा mcba_usb_msg *msg;

		अगर (pos + माप(काष्ठा mcba_usb_msg) > urb->actual_length) अणु
			netdev_err(priv->netdev, "format error\n");
			अवरोध;
		पूर्ण

		msg = (काष्ठा mcba_usb_msg *)(urb->transfer_buffer + pos);
		mcba_usb_process_rx(priv, msg);

		pos += माप(काष्ठा mcba_usb_msg);
	पूर्ण

resubmit_urb:

	usb_fill_bulk_urb(urb, priv->udev,
			  usb_rcvbulkpipe(priv->udev, MCBA_USB_EP_OUT),
			  urb->transfer_buffer, MCBA_USB_RX_BUFF_SIZE,
			  mcba_usb_पढ़ो_bulk_callback, priv);

	retval = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (retval == -ENODEV)
		netअगर_device_detach(netdev);
	अन्यथा अगर (retval)
		netdev_err(netdev, "failed resubmitting read bulk urb: %d\n",
			   retval);
पूर्ण

/* Start USB device */
अटल पूर्णांक mcba_usb_start(काष्ठा mcba_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक err, i;

	mcba_init_ctx(priv);

	क्रम (i = 0; i < MCBA_MAX_RX_URBS; i++) अणु
		काष्ठा urb *urb = शून्य;
		u8 *buf;
		dma_addr_t buf_dma;

		/* create a URB, and a buffer क्रम it */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		buf = usb_alloc_coherent(priv->udev, MCBA_USB_RX_BUFF_SIZE,
					 GFP_KERNEL, &buf_dma);
		अगर (!buf) अणु
			netdev_err(netdev, "No memory left for USB buffer\n");
			usb_मुक्त_urb(urb);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		usb_fill_bulk_urb(urb, priv->udev,
				  usb_rcvbulkpipe(priv->udev, MCBA_USB_EP_IN),
				  buf, MCBA_USB_RX_BUFF_SIZE,
				  mcba_usb_पढ़ो_bulk_callback, priv);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &priv->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			usb_unanchor_urb(urb);
			usb_मुक्त_coherent(priv->udev, MCBA_USB_RX_BUFF_SIZE,
					  buf, buf_dma);
			usb_मुक्त_urb(urb);
			अवरोध;
		पूर्ण

		priv->rxbuf[i] = buf;
		priv->rxbuf_dma[i] = buf_dma;

		/* Drop reference, USB core will take care of मुक्तing it */
		usb_मुक्त_urb(urb);
	पूर्ण

	/* Did we submit any URBs */
	अगर (i == 0) अणु
		netdev_warn(netdev, "couldn't setup read URBs\n");
		वापस err;
	पूर्ण

	/* Warn अगर we've couldn't transmit all the URBs */
	अगर (i < MCBA_MAX_RX_URBS)
		netdev_warn(netdev, "rx performance may be slow\n");

	mcba_usb_xmit_पढ़ो_fw_ver(priv, MCBA_VER_REQ_USB);
	mcba_usb_xmit_पढ़ो_fw_ver(priv, MCBA_VER_REQ_CAN);

	वापस err;
पूर्ण

/* Open USB device */
अटल पूर्णांक mcba_usb_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा mcba_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	/* common खोलो */
	err = खोलो_candev(netdev);
	अगर (err)
		वापस err;

	priv->can_speed_check = true;
	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	can_led_event(netdev, CAN_LED_EVENT_OPEN);
	netअगर_start_queue(netdev);

	वापस 0;
पूर्ण

अटल व्योम mcba_urb_unlink(काष्ठा mcba_priv *priv)
अणु
	पूर्णांक i;

	usb_समाप्त_anchored_urbs(&priv->rx_submitted);

	क्रम (i = 0; i < MCBA_MAX_RX_URBS; ++i)
		usb_मुक्त_coherent(priv->udev, MCBA_USB_RX_BUFF_SIZE,
				  priv->rxbuf[i], priv->rxbuf_dma[i]);

	usb_समाप्त_anchored_urbs(&priv->tx_submitted);
पूर्ण

/* Close USB device */
अटल पूर्णांक mcba_usb_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा mcba_priv *priv = netdev_priv(netdev);

	priv->can.state = CAN_STATE_STOPPED;

	netअगर_stop_queue(netdev);

	/* Stop polling */
	mcba_urb_unlink(priv);

	बंद_candev(netdev);
	can_led_event(netdev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

/* Set network device mode
 *
 * Maybe we should leave this function empty, because the device
 * set mode variable with खोलो command.
 */
अटल पूर्णांक mcba_net_set_mode(काष्ठा net_device *netdev, क्रमागत can_mode mode)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mcba_net_get_berr_counter(स्थिर काष्ठा net_device *netdev,
				     काष्ठा can_berr_counter *bec)
अणु
	काष्ठा mcba_priv *priv = netdev_priv(netdev);

	bec->txerr = priv->bec.txerr;
	bec->rxerr = priv->bec.rxerr;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mcba_netdev_ops = अणु
	.nकरो_खोलो = mcba_usb_खोलो,
	.nकरो_stop = mcba_usb_बंद,
	.nकरो_start_xmit = mcba_usb_start_xmit,
पूर्ण;

/* Microchip CANBUS has hardcoded bittiming values by शेष.
 * This function sends request via USB to change the speed and align bittiming
 * values क्रम presentation purposes only
 */
अटल पूर्णांक mcba_net_set_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा mcba_priv *priv = netdev_priv(netdev);
	स्थिर u16 bitrate_kbps = priv->can.bittiming.bitrate / 1000;

	mcba_usb_xmit_change_bitrate(priv, bitrate_kbps);

	वापस 0;
पूर्ण

अटल पूर्णांक mcba_set_termination(काष्ठा net_device *netdev, u16 term)
अणु
	काष्ठा mcba_priv *priv = netdev_priv(netdev);
	काष्ठा mcba_usb_msg_termination usb_msg = अणु
		.cmd_id = MBCA_CMD_SETUP_TERMINATION_RESISTANCE
	पूर्ण;

	अगर (term == MCBA_TERMINATION_ENABLED)
		usb_msg.termination = 1;
	अन्यथा
		usb_msg.termination = 0;

	mcba_usb_xmit_cmd(priv, (काष्ठा mcba_usb_msg *)&usb_msg);

	वापस 0;
पूर्ण

अटल पूर्णांक mcba_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा net_device *netdev;
	काष्ठा mcba_priv *priv;
	पूर्णांक err;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	netdev = alloc_candev(माप(काष्ठा mcba_priv), MCBA_MAX_TX_URBS);
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "Couldn't alloc candev\n");
		वापस -ENOMEM;
	पूर्ण

	priv = netdev_priv(netdev);

	priv->udev = usbdev;
	priv->netdev = netdev;
	priv->usb_ka_first_pass = true;
	priv->can_ka_first_pass = true;
	priv->can_speed_check = false;

	init_usb_anchor(&priv->rx_submitted);
	init_usb_anchor(&priv->tx_submitted);

	usb_set_पूर्णांकfdata(पूर्णांकf, priv);

	/* Init CAN device */
	priv->can.state = CAN_STATE_STOPPED;
	priv->can.termination_स्थिर = mcba_termination;
	priv->can.termination_स्थिर_cnt = ARRAY_SIZE(mcba_termination);
	priv->can.bitrate_स्थिर = mcba_bitrate;
	priv->can.bitrate_स्थिर_cnt = ARRAY_SIZE(mcba_bitrate);

	priv->can.करो_set_termination = mcba_set_termination;
	priv->can.करो_set_mode = mcba_net_set_mode;
	priv->can.करो_get_berr_counter = mcba_net_get_berr_counter;
	priv->can.करो_set_bittiming = mcba_net_set_bittiming;

	netdev->netdev_ops = &mcba_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);

	err = रेजिस्टर_candev(netdev);
	अगर (err) अणु
		netdev_err(netdev, "couldn't register CAN device: %d\n", err);

		जाओ cleanup_मुक्त_candev;
	पूर्ण

	devm_can_led_init(netdev);

	/* Start USB dev only अगर we have successfully रेजिस्टरed CAN device */
	err = mcba_usb_start(priv);
	अगर (err) अणु
		अगर (err == -ENODEV)
			netअगर_device_detach(priv->netdev);

		netdev_warn(netdev, "couldn't start device: %d\n", err);

		जाओ cleanup_unरेजिस्टर_candev;
	पूर्ण

	dev_info(&पूर्णांकf->dev, "Microchip CAN BUS Analyzer connected\n");

	वापस 0;

cleanup_unरेजिस्टर_candev:
	unरेजिस्टर_candev(priv->netdev);

cleanup_मुक्त_candev:
	मुक्त_candev(netdev);

	वापस err;
पूर्ण

/* Called by the usb core when driver is unloaded or device is हटाओd */
अटल व्योम mcba_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mcba_priv *priv = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	netdev_info(priv->netdev, "device disconnected\n");

	unरेजिस्टर_candev(priv->netdev);
	mcba_urb_unlink(priv);
	मुक्त_candev(priv->netdev);
पूर्ण

अटल काष्ठा usb_driver mcba_usb_driver = अणु
	.name = MCBA_MODULE_NAME,
	.probe = mcba_usb_probe,
	.disconnect = mcba_usb_disconnect,
	.id_table = mcba_usb_table,
पूर्ण;

module_usb_driver(mcba_usb_driver);

MODULE_AUTHOR("Remigiusz Koधधदtaj <remigiusz.kollataj@mobica.com>");
MODULE_DESCRIPTION("SocketCAN driver for Microchip CAN BUS Analyzer Tool");
MODULE_LICENSE("GPL v2");
