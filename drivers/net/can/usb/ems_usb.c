<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN driver क्रम EMS Dr. Thomas Wuensche CPC-USB/ARM7
 *
 * Copyright (C) 2004-2009 EMS Dr. Thomas Wuensche
 */
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>

MODULE_AUTHOR("Sebastian Haas <haas@ems-wuensche.com>");
MODULE_DESCRIPTION("CAN driver for EMS Dr. Thomas Wuensche CAN/USB interfaces");
MODULE_LICENSE("GPL v2");

/* Control-Values क्रम CPC_Control() Command Subject Selection */
#घोषणा CONTR_CAN_MESSAGE 0x04
#घोषणा CONTR_CAN_STATE   0x0C
#घोषणा CONTR_BUS_ERROR   0x1C

/* Control Command Actions */
#घोषणा CONTR_CONT_OFF 0
#घोषणा CONTR_CONT_ON  1
#घोषणा CONTR_ONCE     2

/* Messages from CPC to PC */
#घोषणा CPC_MSG_TYPE_CAN_FRAME       1  /* CAN data frame */
#घोषणा CPC_MSG_TYPE_RTR_FRAME       8  /* CAN remote frame */
#घोषणा CPC_MSG_TYPE_CAN_PARAMS      12 /* Actual CAN parameters */
#घोषणा CPC_MSG_TYPE_CAN_STATE       14 /* CAN state message */
#घोषणा CPC_MSG_TYPE_EXT_CAN_FRAME   16 /* Extended CAN data frame */
#घोषणा CPC_MSG_TYPE_EXT_RTR_FRAME   17 /* Extended remote frame */
#घोषणा CPC_MSG_TYPE_CONTROL         19 /* change पूर्णांकerface behavior */
#घोषणा CPC_MSG_TYPE_CONFIRM         20 /* command processed confirmation */
#घोषणा CPC_MSG_TYPE_OVERRUN         21 /* overrun events */
#घोषणा CPC_MSG_TYPE_CAN_FRAME_ERROR 23 /* detected bus errors */
#घोषणा CPC_MSG_TYPE_ERR_COUNTER     25 /* RX/TX error counter */

/* Messages from the PC to the CPC पूर्णांकerface  */
#घोषणा CPC_CMD_TYPE_CAN_FRAME     1   /* CAN data frame */
#घोषणा CPC_CMD_TYPE_CONTROL       3   /* control of पूर्णांकerface behavior */
#घोषणा CPC_CMD_TYPE_CAN_PARAMS    6   /* set CAN parameters */
#घोषणा CPC_CMD_TYPE_RTR_FRAME     13  /* CAN remote frame */
#घोषणा CPC_CMD_TYPE_CAN_STATE     14  /* CAN state message */
#घोषणा CPC_CMD_TYPE_EXT_CAN_FRAME 15  /* Extended CAN data frame */
#घोषणा CPC_CMD_TYPE_EXT_RTR_FRAME 16  /* Extended CAN remote frame */
#घोषणा CPC_CMD_TYPE_CAN_EXIT      200 /* निकास the CAN */

#घोषणा CPC_CMD_TYPE_INQ_ERR_COUNTER 25 /* request the CAN error counters */
#घोषणा CPC_CMD_TYPE_CLEAR_MSG_QUEUE 8  /* clear CPC_MSG queue */
#घोषणा CPC_CMD_TYPE_CLEAR_CMD_QUEUE 28 /* clear CPC_CMD queue */

#घोषणा CPC_CC_TYPE_SJA1000 2 /* Philips basic CAN controller */

#घोषणा CPC_CAN_ECODE_ERRFRAME 0x01 /* Ecode type */

/* Overrun types */
#घोषणा CPC_OVR_EVENT_CAN       0x01
#घोषणा CPC_OVR_EVENT_CANSTATE  0x02
#घोषणा CPC_OVR_EVENT_BUSERROR  0x04

/*
 * If the CAN controller lost a message we indicate it with the highest bit
 * set in the count field.
 */
#घोषणा CPC_OVR_HW 0x80

/* Size of the "struct ems_cpc_msg" without the जोड़ */
#घोषणा CPC_MSG_HEADER_LEN   11
#घोषणा CPC_CAN_MSG_MIN_SIZE 5

/* Define these values to match your devices */
#घोषणा USB_CPCUSB_VENDOR_ID 0x12D6

#घोषणा USB_CPCUSB_ARM7_PRODUCT_ID 0x0444

/* Mode रेजिस्टर NXP LPC2119/SJA1000 CAN Controller */
#घोषणा SJA1000_MOD_NORMAL 0x00
#घोषणा SJA1000_MOD_RM     0x01

/* ECC रेजिस्टर NXP LPC2119/SJA1000 CAN Controller */
#घोषणा SJA1000_ECC_SEG   0x1F
#घोषणा SJA1000_ECC_सूची   0x20
#घोषणा SJA1000_ECC_ERR   0x06
#घोषणा SJA1000_ECC_BIT   0x00
#घोषणा SJA1000_ECC_FORM  0x40
#घोषणा SJA1000_ECC_STUFF 0x80
#घोषणा SJA1000_ECC_MASK  0xc0

/* Status रेजिस्टर content */
#घोषणा SJA1000_SR_BS 0x80
#घोषणा SJA1000_SR_ES 0x40

#घोषणा SJA1000_DEFAULT_OUTPUT_CONTROL 0xDA

/*
 * The device actually uses a 16MHz घड़ी to generate the CAN घड़ी
 * but it expects SJA1000 bit settings based on 8MHz (is पूर्णांकernally
 * converted).
 */
#घोषणा EMS_USB_ARM7_CLOCK 8000000

#घोषणा CPC_TX_QUEUE_TRIGGER_LOW	25
#घोषणा CPC_TX_QUEUE_TRIGGER_HIGH	35

/*
 * CAN-Message representation in a CPC_MSG. Message object type is
 * CPC_MSG_TYPE_CAN_FRAME or CPC_MSG_TYPE_RTR_FRAME or
 * CPC_MSG_TYPE_EXT_CAN_FRAME or CPC_MSG_TYPE_EXT_RTR_FRAME.
 */
काष्ठा cpc_can_msg अणु
	__le32 id;
	u8 length;
	u8 msg[8];
पूर्ण;

/* Representation of the CAN parameters क्रम the SJA1000 controller */
काष्ठा cpc_sja1000_params अणु
	u8 mode;
	u8 acc_code0;
	u8 acc_code1;
	u8 acc_code2;
	u8 acc_code3;
	u8 acc_mask0;
	u8 acc_mask1;
	u8 acc_mask2;
	u8 acc_mask3;
	u8 btr0;
	u8 btr1;
	u8 outp_contr;
पूर्ण;

/* CAN params message representation */
काष्ठा cpc_can_params अणु
	u8 cc_type;

	/* Will support M16C CAN controller in the future */
	जोड़ अणु
		काष्ठा cpc_sja1000_params sja1000;
	पूर्ण cc_params;
पूर्ण;

/* Structure क्रम confirmed message handling */
काष्ठा cpc_confirm अणु
	u8 error; /* error code */
पूर्ण;

/* Structure क्रम overrun conditions */
काष्ठा cpc_overrun अणु
	u8 event;
	u8 count;
पूर्ण;

/* SJA1000 CAN errors (compatible to NXP LPC2119) */
काष्ठा cpc_sja1000_can_error अणु
	u8 ecc;
	u8 rxerr;
	u8 txerr;
पूर्ण;

/* काष्ठाure क्रम CAN error conditions */
काष्ठा cpc_can_error अणु
	u8 ecode;

	काष्ठा अणु
		u8 cc_type;

		/* Other controllers may also provide error code capture regs */
		जोड़ अणु
			काष्ठा cpc_sja1000_can_error sja1000;
		पूर्ण regs;
	पूर्ण cc;
पूर्ण;

/*
 * Structure containing RX/TX error counter. This काष्ठाure is used to request
 * the values of the CAN controllers TX and RX error counter.
 */
काष्ठा cpc_can_err_counter अणु
	u8 rx;
	u8 tx;
पूर्ण;

/* Main message type used between library and application */
काष्ठा __packed ems_cpc_msg अणु
	u8 type;	/* type of message */
	u8 length;	/* length of data within जोड़ 'msg' */
	u8 msgid;	/* confirmation handle */
	__le32 ts_sec;	/* बारtamp in seconds */
	__le32 ts_nsec;	/* बारtamp in nano seconds */

	जोड़ अणु
		u8 generic[64];
		काष्ठा cpc_can_msg can_msg;
		काष्ठा cpc_can_params can_params;
		काष्ठा cpc_confirm confirmation;
		काष्ठा cpc_overrun overrun;
		काष्ठा cpc_can_error error;
		काष्ठा cpc_can_err_counter err_counter;
		u8 can_state;
	पूर्ण msg;
पूर्ण;

/*
 * Table of devices that work with this driver
 * NOTE: This driver supports only CPC-USB/ARM7 (LPC2119) yet.
 */
अटल काष्ठा usb_device_id ems_usb_table[] = अणु
	अणुUSB_DEVICE(USB_CPCUSB_VENDOR_ID, USB_CPCUSB_ARM7_PRODUCT_ID)पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, ems_usb_table);

#घोषणा RX_BUFFER_SIZE      64
#घोषणा CPC_HEADER_SIZE     4
#घोषणा INTR_IN_BUFFER_SIZE 4

#घोषणा MAX_RX_URBS 10
#घोषणा MAX_TX_URBS 10

काष्ठा ems_usb;

काष्ठा ems_tx_urb_context अणु
	काष्ठा ems_usb *dev;

	u32 echo_index;
	u8 dlc;
पूर्ण;

काष्ठा ems_usb अणु
	काष्ठा can_priv can; /* must be the first member */

	काष्ठा sk_buff *echo_skb[MAX_TX_URBS];

	काष्ठा usb_device *udev;
	काष्ठा net_device *netdev;

	atomic_t active_tx_urbs;
	काष्ठा usb_anchor tx_submitted;
	काष्ठा ems_tx_urb_context tx_contexts[MAX_TX_URBS];

	काष्ठा usb_anchor rx_submitted;

	काष्ठा urb *पूर्णांकr_urb;

	u8 *tx_msg_buffer;

	u8 *पूर्णांकr_in_buffer;
	अचिन्हित पूर्णांक मुक्त_slots; /* remember number of available slots */

	काष्ठा ems_cpc_msg active_params; /* active controller parameters */
पूर्ण;

अटल व्योम ems_usb_पढ़ो_पूर्णांकerrupt_callback(काष्ठा urb *urb)
अणु
	काष्ठा ems_usb *dev = urb->context;
	काष्ठा net_device *netdev = dev->netdev;
	पूर्णांक err;

	अगर (!netअगर_device_present(netdev))
		वापस;

	चयन (urb->status) अणु
	हाल 0:
		dev->मुक्त_slots = dev->पूर्णांकr_in_buffer[1];
		अगर (dev->मुक्त_slots > CPC_TX_QUEUE_TRIGGER_HIGH &&
		    netअगर_queue_stopped(netdev))
			netअगर_wake_queue(netdev);
		अवरोध;

	हाल -ECONNRESET: /* unlink */
	हाल -ENOENT:
	हाल -EPIPE:
	हाल -EPROTO:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		netdev_info(netdev, "Rx interrupt aborted %d\n", urb->status);
		अवरोध;
	पूर्ण

	err = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (err == -ENODEV)
		netअगर_device_detach(netdev);
	अन्यथा अगर (err)
		netdev_err(netdev, "failed resubmitting intr urb: %d\n", err);
पूर्ण

अटल व्योम ems_usb_rx_can_msg(काष्ठा ems_usb *dev, काष्ठा ems_cpc_msg *msg)
अणु
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	काष्ठा net_device_stats *stats = &dev->netdev->stats;

	skb = alloc_can_skb(dev->netdev, &cf);
	अगर (skb == शून्य)
		वापस;

	cf->can_id = le32_to_cpu(msg->msg.can_msg.id);
	cf->len = can_cc_dlc2len(msg->msg.can_msg.length & 0xF);

	अगर (msg->type == CPC_MSG_TYPE_EXT_CAN_FRAME ||
	    msg->type == CPC_MSG_TYPE_EXT_RTR_FRAME)
		cf->can_id |= CAN_EFF_FLAG;

	अगर (msg->type == CPC_MSG_TYPE_RTR_FRAME ||
	    msg->type == CPC_MSG_TYPE_EXT_RTR_FRAME) अणु
		cf->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < cf->len; i++)
			cf->data[i] = msg->msg.can_msg.msg[i];
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल व्योम ems_usb_rx_err(काष्ठा ems_usb *dev, काष्ठा ems_cpc_msg *msg)
अणु
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats = &dev->netdev->stats;

	skb = alloc_can_err_skb(dev->netdev, &cf);
	अगर (skb == शून्य)
		वापस;

	अगर (msg->type == CPC_MSG_TYPE_CAN_STATE) अणु
		u8 state = msg->msg.can_state;

		अगर (state & SJA1000_SR_BS) अणु
			dev->can.state = CAN_STATE_BUS_OFF;
			cf->can_id |= CAN_ERR_BUSOFF;

			dev->can.can_stats.bus_off++;
			can_bus_off(dev->netdev);
		पूर्ण अन्यथा अगर (state & SJA1000_SR_ES) अणु
			dev->can.state = CAN_STATE_ERROR_WARNING;
			dev->can.can_stats.error_warning++;
		पूर्ण अन्यथा अणु
			dev->can.state = CAN_STATE_ERROR_ACTIVE;
			dev->can.can_stats.error_passive++;
		पूर्ण
	पूर्ण अन्यथा अगर (msg->type == CPC_MSG_TYPE_CAN_FRAME_ERROR) अणु
		u8 ecc = msg->msg.error.cc.regs.sja1000.ecc;
		u8 txerr = msg->msg.error.cc.regs.sja1000.txerr;
		u8 rxerr = msg->msg.error.cc.regs.sja1000.rxerr;

		/* bus error पूर्णांकerrupt */
		dev->can.can_stats.bus_error++;
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
		अगर ((ecc & SJA1000_ECC_सूची) == 0)
			cf->data[2] |= CAN_ERR_PROT_TX;

		अगर (dev->can.state == CAN_STATE_ERROR_WARNING ||
		    dev->can.state == CAN_STATE_ERROR_PASSIVE) अणु
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (txerr > rxerr) ?
			    CAN_ERR_CRTL_TX_PASSIVE : CAN_ERR_CRTL_RX_PASSIVE;
		पूर्ण
	पूर्ण अन्यथा अगर (msg->type == CPC_MSG_TYPE_OVERRUN) अणु
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

		stats->rx_over_errors++;
		stats->rx_errors++;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

/*
 * callback क्रम bulk IN urb
 */
अटल व्योम ems_usb_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा ems_usb *dev = urb->context;
	काष्ठा net_device *netdev;
	पूर्णांक retval;

	netdev = dev->netdev;

	अगर (!netअगर_device_present(netdev))
		वापस;

	चयन (urb->status) अणु
	हाल 0: /* success */
		अवरोध;

	हाल -ENOENT:
		वापस;

	शेष:
		netdev_info(netdev, "Rx URB aborted (%d)\n", urb->status);
		जाओ resubmit_urb;
	पूर्ण

	अगर (urb->actual_length > CPC_HEADER_SIZE) अणु
		काष्ठा ems_cpc_msg *msg;
		u8 *ibuf = urb->transfer_buffer;
		u8 msg_count, start;

		msg_count = ibuf[0] & ~0x80;

		start = CPC_HEADER_SIZE;

		जबतक (msg_count) अणु
			msg = (काष्ठा ems_cpc_msg *)&ibuf[start];

			चयन (msg->type) अणु
			हाल CPC_MSG_TYPE_CAN_STATE:
				/* Process CAN state changes */
				ems_usb_rx_err(dev, msg);
				अवरोध;

			हाल CPC_MSG_TYPE_CAN_FRAME:
			हाल CPC_MSG_TYPE_EXT_CAN_FRAME:
			हाल CPC_MSG_TYPE_RTR_FRAME:
			हाल CPC_MSG_TYPE_EXT_RTR_FRAME:
				ems_usb_rx_can_msg(dev, msg);
				अवरोध;

			हाल CPC_MSG_TYPE_CAN_FRAME_ERROR:
				/* Process errorframe */
				ems_usb_rx_err(dev, msg);
				अवरोध;

			हाल CPC_MSG_TYPE_OVERRUN:
				/* Message lost जबतक receiving */
				ems_usb_rx_err(dev, msg);
				अवरोध;
			पूर्ण

			start += CPC_MSG_HEADER_LEN + msg->length;
			msg_count--;

			अगर (start > urb->transfer_buffer_length) अणु
				netdev_err(netdev, "format error\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

resubmit_urb:
	usb_fill_bulk_urb(urb, dev->udev, usb_rcvbulkpipe(dev->udev, 2),
			  urb->transfer_buffer, RX_BUFFER_SIZE,
			  ems_usb_पढ़ो_bulk_callback, dev);

	retval = usb_submit_urb(urb, GFP_ATOMIC);

	अगर (retval == -ENODEV)
		netअगर_device_detach(netdev);
	अन्यथा अगर (retval)
		netdev_err(netdev,
			   "failed resubmitting read bulk urb: %d\n", retval);
पूर्ण

/*
 * callback क्रम bulk IN urb
 */
अटल व्योम ems_usb_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा ems_tx_urb_context *context = urb->context;
	काष्ठा ems_usb *dev;
	काष्ठा net_device *netdev;

	BUG_ON(!context);

	dev = context->dev;
	netdev = dev->netdev;

	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);

	atomic_dec(&dev->active_tx_urbs);

	अगर (!netअगर_device_present(netdev))
		वापस;

	अगर (urb->status)
		netdev_info(netdev, "Tx URB aborted (%d)\n", urb->status);

	netअगर_trans_update(netdev);

	/* transmission complete पूर्णांकerrupt */
	netdev->stats.tx_packets++;
	netdev->stats.tx_bytes += context->dlc;

	can_get_echo_skb(netdev, context->echo_index, शून्य);

	/* Release context */
	context->echo_index = MAX_TX_URBS;

पूर्ण

/*
 * Send the given CPC command synchronously
 */
अटल पूर्णांक ems_usb_command_msg(काष्ठा ems_usb *dev, काष्ठा ems_cpc_msg *msg)
अणु
	पूर्णांक actual_length;

	/* Copy payload */
	स_नकल(&dev->tx_msg_buffer[CPC_HEADER_SIZE], msg,
	       msg->length + CPC_MSG_HEADER_LEN);

	/* Clear header */
	स_रखो(&dev->tx_msg_buffer[0], 0, CPC_HEADER_SIZE);

	वापस usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 2),
			    &dev->tx_msg_buffer[0],
			    msg->length + CPC_MSG_HEADER_LEN + CPC_HEADER_SIZE,
			    &actual_length, 1000);
पूर्ण

/*
 * Change CAN controllers' mode रेजिस्टर
 */
अटल पूर्णांक ems_usb_ग_लिखो_mode(काष्ठा ems_usb *dev, u8 mode)
अणु
	dev->active_params.msg.can_params.cc_params.sja1000.mode = mode;

	वापस ems_usb_command_msg(dev, &dev->active_params);
पूर्ण

/*
 * Send a CPC_Control command to change behaviour when पूर्णांकerface receives a CAN
 * message, bus error or CAN state changed notअगरications.
 */
अटल पूर्णांक ems_usb_control_cmd(काष्ठा ems_usb *dev, u8 val)
अणु
	काष्ठा ems_cpc_msg cmd;

	cmd.type = CPC_CMD_TYPE_CONTROL;
	cmd.length = CPC_MSG_HEADER_LEN + 1;

	cmd.msgid = 0;

	cmd.msg.generic[0] = val;

	वापस ems_usb_command_msg(dev, &cmd);
पूर्ण

/*
 * Start पूर्णांकerface
 */
अटल पूर्णांक ems_usb_start(काष्ठा ems_usb *dev)
अणु
	काष्ठा net_device *netdev = dev->netdev;
	पूर्णांक err, i;

	dev->पूर्णांकr_in_buffer[0] = 0;
	dev->मुक्त_slots = 50; /* initial size */

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
			netdev_err(netdev, "No memory left for USB buffer\n");
			usb_मुक्त_urb(urb);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		usb_fill_bulk_urb(urb, dev->udev, usb_rcvbulkpipe(dev->udev, 2),
				  buf, RX_BUFFER_SIZE,
				  ems_usb_पढ़ो_bulk_callback, dev);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &dev->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err) अणु
			usb_unanchor_urb(urb);
			usb_मुक्त_coherent(dev->udev, RX_BUFFER_SIZE, buf,
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

	/* Setup and start पूर्णांकerrupt URB */
	usb_fill_पूर्णांक_urb(dev->पूर्णांकr_urb, dev->udev,
			 usb_rcvपूर्णांकpipe(dev->udev, 1),
			 dev->पूर्णांकr_in_buffer,
			 INTR_IN_BUFFER_SIZE,
			 ems_usb_पढ़ो_पूर्णांकerrupt_callback, dev, 1);

	err = usb_submit_urb(dev->पूर्णांकr_urb, GFP_KERNEL);
	अगर (err) अणु
		netdev_warn(netdev, "intr URB submit failed: %d\n", err);

		वापस err;
	पूर्ण

	/* CPC-USB will transfer received message to host */
	err = ems_usb_control_cmd(dev, CONTR_CAN_MESSAGE | CONTR_CONT_ON);
	अगर (err)
		जाओ failed;

	/* CPC-USB will transfer CAN state changes to host */
	err = ems_usb_control_cmd(dev, CONTR_CAN_STATE | CONTR_CONT_ON);
	अगर (err)
		जाओ failed;

	/* CPC-USB will transfer bus errors to host */
	err = ems_usb_control_cmd(dev, CONTR_BUS_ERROR | CONTR_CONT_ON);
	अगर (err)
		जाओ failed;

	err = ems_usb_ग_लिखो_mode(dev, SJA1000_MOD_NORMAL);
	अगर (err)
		जाओ failed;

	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस 0;

failed:
	netdev_warn(netdev, "couldn't submit control: %d\n", err);

	वापस err;
पूर्ण

अटल व्योम unlink_all_urbs(काष्ठा ems_usb *dev)
अणु
	पूर्णांक i;

	usb_unlink_urb(dev->पूर्णांकr_urb);

	usb_समाप्त_anchored_urbs(&dev->rx_submitted);

	usb_समाप्त_anchored_urbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);

	क्रम (i = 0; i < MAX_TX_URBS; i++)
		dev->tx_contexts[i].echo_index = MAX_TX_URBS;
पूर्ण

अटल पूर्णांक ems_usb_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ems_usb *dev = netdev_priv(netdev);
	पूर्णांक err;

	err = ems_usb_ग_लिखो_mode(dev, SJA1000_MOD_RM);
	अगर (err)
		वापस err;

	/* common खोलो */
	err = खोलो_candev(netdev);
	अगर (err)
		वापस err;

	/* finally start device */
	err = ems_usb_start(dev);
	अगर (err) अणु
		अगर (err == -ENODEV)
			netअगर_device_detach(dev->netdev);

		netdev_warn(netdev, "couldn't start device: %d\n", err);

		बंद_candev(netdev);

		वापस err;
	पूर्ण


	netअगर_start_queue(netdev);

	वापस 0;
पूर्ण

अटल netdev_tx_t ems_usb_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा ems_usb *dev = netdev_priv(netdev);
	काष्ठा ems_tx_urb_context *context = शून्य;
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	काष्ठा ems_cpc_msg *msg;
	काष्ठा urb *urb;
	u8 *buf;
	पूर्णांक i, err;
	माप_प्रकार size = CPC_HEADER_SIZE + CPC_MSG_HEADER_LEN
			+ माप(काष्ठा cpc_can_msg);

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	/* create a URB, and a buffer क्रम it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ nomem;

	buf = usb_alloc_coherent(dev->udev, size, GFP_ATOMIC, &urb->transfer_dma);
	अगर (!buf) अणु
		netdev_err(netdev, "No memory left for USB buffer\n");
		usb_मुक्त_urb(urb);
		जाओ nomem;
	पूर्ण

	msg = (काष्ठा ems_cpc_msg *)&buf[CPC_HEADER_SIZE];

	msg->msg.can_msg.id = cpu_to_le32(cf->can_id & CAN_ERR_MASK);
	msg->msg.can_msg.length = cf->len;

	अगर (cf->can_id & CAN_RTR_FLAG) अणु
		msg->type = cf->can_id & CAN_EFF_FLAG ?
			CPC_CMD_TYPE_EXT_RTR_FRAME : CPC_CMD_TYPE_RTR_FRAME;

		msg->length = CPC_CAN_MSG_MIN_SIZE;
	पूर्ण अन्यथा अणु
		msg->type = cf->can_id & CAN_EFF_FLAG ?
			CPC_CMD_TYPE_EXT_CAN_FRAME : CPC_CMD_TYPE_CAN_FRAME;

		क्रम (i = 0; i < cf->len; i++)
			msg->msg.can_msg.msg[i] = cf->data[i];

		msg->length = CPC_CAN_MSG_MIN_SIZE + cf->len;
	पूर्ण

	क्रम (i = 0; i < MAX_TX_URBS; i++) अणु
		अगर (dev->tx_contexts[i].echo_index == MAX_TX_URBS) अणु
			context = &dev->tx_contexts[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * May never happen! When this happens we'd more URBs in flight as
	 * allowed (MAX_TX_URBS).
	 */
	अगर (!context) अणु
		usb_मुक्त_coherent(dev->udev, size, buf, urb->transfer_dma);
		usb_मुक्त_urb(urb);

		netdev_warn(netdev, "couldn't find free context\n");

		वापस NETDEV_TX_BUSY;
	पूर्ण

	context->dev = dev;
	context->echo_index = i;
	context->dlc = cf->len;

	usb_fill_bulk_urb(urb, dev->udev, usb_sndbulkpipe(dev->udev, 2), buf,
			  size, ems_usb_ग_लिखो_bulk_callback, context);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &dev->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&dev->active_tx_urbs);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		can_मुक्त_echo_skb(netdev, context->echo_index, शून्य);

		usb_unanchor_urb(urb);
		usb_मुक्त_coherent(dev->udev, size, buf, urb->transfer_dma);
		dev_kमुक्त_skb(skb);

		atomic_dec(&dev->active_tx_urbs);

		अगर (err == -ENODEV) अणु
			netअगर_device_detach(netdev);
		पूर्ण अन्यथा अणु
			netdev_warn(netdev, "failed tx_urb %d\n", err);

			stats->tx_dropped++;
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_trans_update(netdev);

		/* Slow करोwn tx path */
		अगर (atomic_पढ़ो(&dev->active_tx_urbs) >= MAX_TX_URBS ||
		    dev->मुक्त_slots < CPC_TX_QUEUE_TRIGGER_LOW) अणु
			netअगर_stop_queue(netdev);
		पूर्ण
	पूर्ण

	/*
	 * Release our reference to this URB, the USB core will eventually मुक्त
	 * it entirely.
	 */
	usb_मुक्त_urb(urb);

	वापस NETDEV_TX_OK;

nomem:
	dev_kमुक्त_skb(skb);
	stats->tx_dropped++;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ems_usb_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ems_usb *dev = netdev_priv(netdev);

	/* Stop polling */
	unlink_all_urbs(dev);

	netअगर_stop_queue(netdev);

	/* Set CAN controller to reset mode */
	अगर (ems_usb_ग_लिखो_mode(dev, SJA1000_MOD_RM))
		netdev_warn(netdev, "couldn't stop device");

	बंद_candev(netdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ems_usb_netdev_ops = अणु
	.nकरो_खोलो = ems_usb_खोलो,
	.nकरो_stop = ems_usb_बंद,
	.nकरो_start_xmit = ems_usb_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर ems_usb_bittiming_स्थिर = अणु
	.name = "ems_usb",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

अटल पूर्णांक ems_usb_set_mode(काष्ठा net_device *netdev, क्रमागत can_mode mode)
अणु
	काष्ठा ems_usb *dev = netdev_priv(netdev);

	चयन (mode) अणु
	हाल CAN_MODE_START:
		अगर (ems_usb_ग_लिखो_mode(dev, SJA1000_MOD_NORMAL))
			netdev_warn(netdev, "couldn't start device");

		अगर (netअगर_queue_stopped(netdev))
			netअगर_wake_queue(netdev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ems_usb_set_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा ems_usb *dev = netdev_priv(netdev);
	काष्ठा can_bittiming *bt = &dev->can.bittiming;
	u8 btr0, btr1;

	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	अगर (dev->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	netdev_info(netdev, "setting BTR0=0x%02x BTR1=0x%02x\n", btr0, btr1);

	dev->active_params.msg.can_params.cc_params.sja1000.btr0 = btr0;
	dev->active_params.msg.can_params.cc_params.sja1000.btr1 = btr1;

	वापस ems_usb_command_msg(dev, &dev->active_params);
पूर्ण

अटल व्योम init_params_sja1000(काष्ठा ems_cpc_msg *msg)
अणु
	काष्ठा cpc_sja1000_params *sja1000 =
		&msg->msg.can_params.cc_params.sja1000;

	msg->type = CPC_CMD_TYPE_CAN_PARAMS;
	msg->length = माप(काष्ठा cpc_can_params);
	msg->msgid = 0;

	msg->msg.can_params.cc_type = CPC_CC_TYPE_SJA1000;

	/* Acceptance filter खोलो */
	sja1000->acc_code0 = 0x00;
	sja1000->acc_code1 = 0x00;
	sja1000->acc_code2 = 0x00;
	sja1000->acc_code3 = 0x00;

	/* Acceptance filter खोलो */
	sja1000->acc_mask0 = 0xFF;
	sja1000->acc_mask1 = 0xFF;
	sja1000->acc_mask2 = 0xFF;
	sja1000->acc_mask3 = 0xFF;

	sja1000->btr0 = 0;
	sja1000->btr1 = 0;

	sja1000->outp_contr = SJA1000_DEFAULT_OUTPUT_CONTROL;
	sja1000->mode = SJA1000_MOD_RM;
पूर्ण

/*
 * probe function क्रम new CPC-USB devices
 */
अटल पूर्णांक ems_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा net_device *netdev;
	काष्ठा ems_usb *dev;
	पूर्णांक i, err = -ENOMEM;

	netdev = alloc_candev(माप(काष्ठा ems_usb), MAX_TX_URBS);
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "ems_usb: Couldn't alloc candev\n");
		वापस -ENOMEM;
	पूर्ण

	dev = netdev_priv(netdev);

	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	dev->netdev = netdev;

	dev->can.state = CAN_STATE_STOPPED;
	dev->can.घड़ी.freq = EMS_USB_ARM7_CLOCK;
	dev->can.bittiming_स्थिर = &ems_usb_bittiming_स्थिर;
	dev->can.करो_set_bittiming = ems_usb_set_bittiming;
	dev->can.करो_set_mode = ems_usb_set_mode;
	dev->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES;

	netdev->netdev_ops = &ems_usb_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	init_usb_anchor(&dev->rx_submitted);

	init_usb_anchor(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);

	क्रम (i = 0; i < MAX_TX_URBS; i++)
		dev->tx_contexts[i].echo_index = MAX_TX_URBS;

	dev->पूर्णांकr_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकr_urb)
		जाओ cleanup_candev;

	dev->पूर्णांकr_in_buffer = kzalloc(INTR_IN_BUFFER_SIZE, GFP_KERNEL);
	अगर (!dev->पूर्णांकr_in_buffer)
		जाओ cleanup_पूर्णांकr_urb;

	dev->tx_msg_buffer = kzalloc(CPC_HEADER_SIZE +
				     माप(काष्ठा ems_cpc_msg), GFP_KERNEL);
	अगर (!dev->tx_msg_buffer)
		जाओ cleanup_पूर्णांकr_in_buffer;

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);

	init_params_sja1000(&dev->active_params);

	err = ems_usb_command_msg(dev, &dev->active_params);
	अगर (err) अणु
		netdev_err(netdev, "couldn't initialize controller: %d\n", err);
		जाओ cleanup_tx_msg_buffer;
	पूर्ण

	err = रेजिस्टर_candev(netdev);
	अगर (err) अणु
		netdev_err(netdev, "couldn't register CAN device: %d\n", err);
		जाओ cleanup_tx_msg_buffer;
	पूर्ण

	वापस 0;

cleanup_tx_msg_buffer:
	kमुक्त(dev->tx_msg_buffer);

cleanup_पूर्णांकr_in_buffer:
	kमुक्त(dev->पूर्णांकr_in_buffer);

cleanup_पूर्णांकr_urb:
	usb_मुक्त_urb(dev->पूर्णांकr_urb);

cleanup_candev:
	मुक्त_candev(netdev);

	वापस err;
पूर्ण

/*
 * called by the usb core when the device is हटाओd from the प्रणाली
 */
अटल व्योम ems_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ems_usb *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (dev) अणु
		unरेजिस्टर_netdev(dev->netdev);
		मुक्त_candev(dev->netdev);

		unlink_all_urbs(dev);

		usb_मुक्त_urb(dev->पूर्णांकr_urb);

		kमुक्त(dev->पूर्णांकr_in_buffer);
		kमुक्त(dev->tx_msg_buffer);
	पूर्ण
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver ems_usb_driver = अणु
	.name = "ems_usb",
	.probe = ems_usb_probe,
	.disconnect = ems_usb_disconnect,
	.id_table = ems_usb_table,
पूर्ण;

module_usb_driver(ems_usb_driver);
