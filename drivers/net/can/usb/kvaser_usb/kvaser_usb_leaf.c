<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Parts of this driver are based on the following:
 *  - Kvaser linux leaf driver (version 4.78)
 *  - CAN driver क्रम esd CAN-USB/2
 *  - Kvaser linux usbcanII driver (version 5.3)
 *
 * Copyright (C) 2002-2018 KVASER AB, Sweden. All rights reserved.
 * Copyright (C) 2010 Matthias Fuchs <matthias.fuchs@esd.eu>, esd gmbh
 * Copyright (C) 2012 Olivier Sobrie <olivier@sobrie.be>
 * Copyright (C) 2015 Valeo S.A.
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/netlink.h>

#समावेश "kvaser_usb.h"

/* Forward declaration */
अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_leaf_dev_cfg;

#घोषणा CAN_USB_CLOCK			8000000
#घोषणा MAX_USBCAN_NET_DEVICES		2

/* Command header size */
#घोषणा CMD_HEADER_LEN			2

/* Kvaser CAN message flags */
#घोषणा MSG_FLAG_ERROR_FRAME		BIT(0)
#घोषणा MSG_FLAG_OVERRUN		BIT(1)
#घोषणा MSG_FLAG_NERR			BIT(2)
#घोषणा MSG_FLAG_WAKEUP			BIT(3)
#घोषणा MSG_FLAG_REMOTE_FRAME		BIT(4)
#घोषणा MSG_FLAG_RESERVED		BIT(5)
#घोषणा MSG_FLAG_TX_ACK			BIT(6)
#घोषणा MSG_FLAG_TX_REQUEST		BIT(7)

/* CAN states (M16C CxSTRH रेजिस्टर) */
#घोषणा M16C_STATE_BUS_RESET		BIT(0)
#घोषणा M16C_STATE_BUS_ERROR		BIT(4)
#घोषणा M16C_STATE_BUS_PASSIVE		BIT(5)
#घोषणा M16C_STATE_BUS_OFF		BIT(6)

/* Leaf/usbcan command ids */
#घोषणा CMD_RX_STD_MESSAGE		12
#घोषणा CMD_TX_STD_MESSAGE		13
#घोषणा CMD_RX_EXT_MESSAGE		14
#घोषणा CMD_TX_EXT_MESSAGE		15
#घोषणा CMD_SET_BUS_PARAMS		16
#घोषणा CMD_CHIP_STATE_EVENT		20
#घोषणा CMD_SET_CTRL_MODE		21
#घोषणा CMD_RESET_CHIP			24
#घोषणा CMD_START_CHIP			26
#घोषणा CMD_START_CHIP_REPLY		27
#घोषणा CMD_STOP_CHIP			28
#घोषणा CMD_STOP_CHIP_REPLY		29

#घोषणा CMD_USBCAN_CLOCK_OVERFLOW_EVENT	33

#घोषणा CMD_GET_CARD_INFO		34
#घोषणा CMD_GET_CARD_INFO_REPLY		35
#घोषणा CMD_GET_SOFTWARE_INFO		38
#घोषणा CMD_GET_SOFTWARE_INFO_REPLY	39
#घोषणा CMD_FLUSH_QUEUE			48
#घोषणा CMD_TX_ACKNOWLEDGE		50
#घोषणा CMD_CAN_ERROR_EVENT		51
#घोषणा CMD_FLUSH_QUEUE_REPLY		68

#घोषणा CMD_LEAF_LOG_MESSAGE		106

/* error factors */
#घोषणा M16C_EF_ACKE			BIT(0)
#घोषणा M16C_EF_CRCE			BIT(1)
#घोषणा M16C_EF_FORME			BIT(2)
#घोषणा M16C_EF_STFE			BIT(3)
#घोषणा M16C_EF_BITE0			BIT(4)
#घोषणा M16C_EF_BITE1			BIT(5)
#घोषणा M16C_EF_RCVE			BIT(6)
#घोषणा M16C_EF_TRE			BIT(7)

/* Only Leaf-based devices can report M16C error factors,
 * thus define our own error status flags क्रम USBCANII
 */
#घोषणा USBCAN_ERROR_STATE_NONE		0
#घोषणा USBCAN_ERROR_STATE_TX_ERROR	BIT(0)
#घोषणा USBCAN_ERROR_STATE_RX_ERROR	BIT(1)
#घोषणा USBCAN_ERROR_STATE_BUSERROR	BIT(2)

/* bittiming parameters */
#घोषणा KVASER_USB_TSEG1_MIN		1
#घोषणा KVASER_USB_TSEG1_MAX		16
#घोषणा KVASER_USB_TSEG2_MIN		1
#घोषणा KVASER_USB_TSEG2_MAX		8
#घोषणा KVASER_USB_SJW_MAX		4
#घोषणा KVASER_USB_BRP_MIN		1
#घोषणा KVASER_USB_BRP_MAX		64
#घोषणा KVASER_USB_BRP_INC		1

/* ctrl modes */
#घोषणा KVASER_CTRL_MODE_NORMAL		1
#घोषणा KVASER_CTRL_MODE_SILENT		2
#घोषणा KVASER_CTRL_MODE_SELFRECEPTION	3
#घोषणा KVASER_CTRL_MODE_OFF		4

/* Extended CAN identअगरier flag */
#घोषणा KVASER_EXTENDED_FRAME		BIT(31)

काष्ठा kvaser_cmd_simple अणु
	u8 tid;
	u8 channel;
पूर्ण __packed;

काष्ठा kvaser_cmd_cardinfo अणु
	u8 tid;
	u8 nchannels;
	__le32 serial_number;
	__le32 padding0;
	__le32 घड़ी_resolution;
	__le32 mfgdate;
	u8 ean[8];
	u8 hw_revision;
	जोड़ अणु
		काष्ठा अणु
			u8 usb_hs_mode;
		पूर्ण __packed leaf1;
		काष्ठा अणु
			u8 padding;
		पूर्ण __packed usbcan1;
	पूर्ण __packed;
	__le16 padding1;
पूर्ण __packed;

काष्ठा leaf_cmd_softinfo अणु
	u8 tid;
	u8 padding0;
	__le32 sw_options;
	__le32 fw_version;
	__le16 max_outstanding_tx;
	__le16 padding1[9];
पूर्ण __packed;

काष्ठा usbcan_cmd_softinfo अणु
	u8 tid;
	u8 fw_name[5];
	__le16 max_outstanding_tx;
	u8 padding[6];
	__le32 fw_version;
	__le16 checksum;
	__le16 sw_options;
पूर्ण __packed;

काष्ठा kvaser_cmd_busparams अणु
	u8 tid;
	u8 channel;
	__le32 bitrate;
	u8 tseg1;
	u8 tseg2;
	u8 sjw;
	u8 no_samp;
पूर्ण __packed;

काष्ठा kvaser_cmd_tx_can अणु
	u8 channel;
	u8 tid;
	u8 data[14];
	जोड़ अणु
		काष्ठा अणु
			u8 padding;
			u8 flags;
		पूर्ण __packed leaf;
		काष्ठा अणु
			u8 flags;
			u8 padding;
		पूर्ण __packed usbcan;
	पूर्ण __packed;
पूर्ण __packed;

काष्ठा kvaser_cmd_rx_can_header अणु
	u8 channel;
	u8 flag;
पूर्ण __packed;

काष्ठा leaf_cmd_rx_can अणु
	u8 channel;
	u8 flag;

	__le16 समय[3];
	u8 data[14];
पूर्ण __packed;

काष्ठा usbcan_cmd_rx_can अणु
	u8 channel;
	u8 flag;

	u8 data[14];
	__le16 समय;
पूर्ण __packed;

काष्ठा leaf_cmd_chip_state_event अणु
	u8 tid;
	u8 channel;

	__le16 समय[3];
	u8 tx_errors_count;
	u8 rx_errors_count;

	u8 status;
	u8 padding[3];
पूर्ण __packed;

काष्ठा usbcan_cmd_chip_state_event अणु
	u8 tid;
	u8 channel;

	u8 tx_errors_count;
	u8 rx_errors_count;
	__le16 समय;

	u8 status;
	u8 padding[3];
पूर्ण __packed;

काष्ठा kvaser_cmd_tx_acknowledge_header अणु
	u8 channel;
	u8 tid;
पूर्ण __packed;

काष्ठा leaf_cmd_error_event अणु
	u8 tid;
	u8 flags;
	__le16 समय[3];
	u8 channel;
	u8 padding;
	u8 tx_errors_count;
	u8 rx_errors_count;
	u8 status;
	u8 error_factor;
पूर्ण __packed;

काष्ठा usbcan_cmd_error_event अणु
	u8 tid;
	u8 padding;
	u8 tx_errors_count_ch0;
	u8 rx_errors_count_ch0;
	u8 tx_errors_count_ch1;
	u8 rx_errors_count_ch1;
	u8 status_ch0;
	u8 status_ch1;
	__le16 समय;
पूर्ण __packed;

काष्ठा kvaser_cmd_ctrl_mode अणु
	u8 tid;
	u8 channel;
	u8 ctrl_mode;
	u8 padding[3];
पूर्ण __packed;

काष्ठा kvaser_cmd_flush_queue अणु
	u8 tid;
	u8 channel;
	u8 flags;
	u8 padding[3];
पूर्ण __packed;

काष्ठा leaf_cmd_log_message अणु
	u8 channel;
	u8 flags;
	__le16 समय[3];
	u8 dlc;
	u8 समय_offset;
	__le32 id;
	u8 data[8];
पूर्ण __packed;

काष्ठा kvaser_cmd अणु
	u8 len;
	u8 id;
	जोड़	अणु
		काष्ठा kvaser_cmd_simple simple;
		काष्ठा kvaser_cmd_cardinfo cardinfo;
		काष्ठा kvaser_cmd_busparams busparams;

		काष्ठा kvaser_cmd_rx_can_header rx_can_header;
		काष्ठा kvaser_cmd_tx_acknowledge_header tx_acknowledge_header;

		जोड़ अणु
			काष्ठा leaf_cmd_softinfo softinfo;
			काष्ठा leaf_cmd_rx_can rx_can;
			काष्ठा leaf_cmd_chip_state_event chip_state_event;
			काष्ठा leaf_cmd_error_event error_event;
			काष्ठा leaf_cmd_log_message log_message;
		पूर्ण __packed leaf;

		जोड़ अणु
			काष्ठा usbcan_cmd_softinfo softinfo;
			काष्ठा usbcan_cmd_rx_can rx_can;
			काष्ठा usbcan_cmd_chip_state_event chip_state_event;
			काष्ठा usbcan_cmd_error_event error_event;
		पूर्ण __packed usbcan;

		काष्ठा kvaser_cmd_tx_can tx_can;
		काष्ठा kvaser_cmd_ctrl_mode ctrl_mode;
		काष्ठा kvaser_cmd_flush_queue flush_queue;
	पूर्ण u;
पूर्ण __packed;

/* Summary of a kvaser error event, क्रम a unअगरied Leaf/Usbcan error
 * handling. Some discrepancies between the two families exist:
 *
 * - USBCAN firmware करोes not report M16C "error factors"
 * - USBCAN controllers has dअगरficulties reporting अगर the उठाओd error
 *   event is क्रम ch0 or ch1. They leave such arbitration to the OS
 *   driver by letting it compare error counters with previous values
 *   and decide the error event's channel. Thus क्रम USBCAN, the channel
 *   field is only advisory.
 */
काष्ठा kvaser_usb_err_summary अणु
	u8 channel, status, txerr, rxerr;
	जोड़ अणु
		काष्ठा अणु
			u8 error_factor;
		पूर्ण leaf;
		काष्ठा अणु
			u8 other_ch_status;
			u8 error_state;
		पूर्ण usbcan;
	पूर्ण;
पूर्ण;

अटल व्योम *
kvaser_usb_leaf_frame_to_cmd(स्थिर काष्ठा kvaser_usb_net_priv *priv,
			     स्थिर काष्ठा sk_buff *skb, पूर्णांक *frame_len,
			     पूर्णांक *cmd_len, u16 transid)
अणु
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा kvaser_cmd *cmd;
	u8 *cmd_tx_can_flags = शून्य;		/* GCC */
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;

	*frame_len = cf->len;

	cmd = kदो_स्मृति(माप(*cmd), GFP_ATOMIC);
	अगर (cmd) अणु
		cmd->u.tx_can.tid = transid & 0xff;
		cmd->len = *cmd_len = CMD_HEADER_LEN +
				      माप(काष्ठा kvaser_cmd_tx_can);
		cmd->u.tx_can.channel = priv->channel;

		चयन (dev->card_data.leaf.family) अणु
		हाल KVASER_LEAF:
			cmd_tx_can_flags = &cmd->u.tx_can.leaf.flags;
			अवरोध;
		हाल KVASER_USBCAN:
			cmd_tx_can_flags = &cmd->u.tx_can.usbcan.flags;
			अवरोध;
		पूर्ण

		*cmd_tx_can_flags = 0;

		अगर (cf->can_id & CAN_EFF_FLAG) अणु
			cmd->id = CMD_TX_EXT_MESSAGE;
			cmd->u.tx_can.data[0] = (cf->can_id >> 24) & 0x1f;
			cmd->u.tx_can.data[1] = (cf->can_id >> 18) & 0x3f;
			cmd->u.tx_can.data[2] = (cf->can_id >> 14) & 0x0f;
			cmd->u.tx_can.data[3] = (cf->can_id >> 6) & 0xff;
			cmd->u.tx_can.data[4] = cf->can_id & 0x3f;
		पूर्ण अन्यथा अणु
			cmd->id = CMD_TX_STD_MESSAGE;
			cmd->u.tx_can.data[0] = (cf->can_id >> 6) & 0x1f;
			cmd->u.tx_can.data[1] = cf->can_id & 0x3f;
		पूर्ण

		cmd->u.tx_can.data[5] = cf->len;
		स_नकल(&cmd->u.tx_can.data[6], cf->data, cf->len);

		अगर (cf->can_id & CAN_RTR_FLAG)
			*cmd_tx_can_flags |= MSG_FLAG_REMOTE_FRAME;
	पूर्ण
	वापस cmd;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_रुको_cmd(स्थिर काष्ठा kvaser_usb *dev, u8 id,
				    काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_cmd *पंचांगp;
	व्योम *buf;
	पूर्णांक actual_len;
	पूर्णांक err;
	पूर्णांक pos;
	अचिन्हित दीर्घ to = jअगरfies + msecs_to_jअगरfies(KVASER_USB_TIMEOUT);

	buf = kzalloc(KVASER_USB_RX_BUFFER_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	करो अणु
		err = kvaser_usb_recv_cmd(dev, buf, KVASER_USB_RX_BUFFER_SIZE,
					  &actual_len);
		अगर (err < 0)
			जाओ end;

		pos = 0;
		जबतक (pos <= actual_len - CMD_HEADER_LEN) अणु
			पंचांगp = buf + pos;

			/* Handle commands crossing the USB endpoपूर्णांक max packet
			 * size boundary. Check kvaser_usb_पढ़ो_bulk_callback()
			 * क्रम further details.
			 */
			अगर (पंचांगp->len == 0) अणु
				pos = round_up(pos,
					       le16_to_cpu
						(dev->bulk_in->wMaxPacketSize));
				जारी;
			पूर्ण

			अगर (pos + पंचांगp->len > actual_len) अणु
				dev_err_ratelimited(&dev->पूर्णांकf->dev,
						    "Format error\n");
				अवरोध;
			पूर्ण

			अगर (पंचांगp->id == id) अणु
				स_नकल(cmd, पंचांगp, पंचांगp->len);
				जाओ end;
			पूर्ण

			pos += पंचांगp->len;
		पूर्ण
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, to));

	err = -EINVAL;

end:
	kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_send_simple_cmd(स्थिर काष्ठा kvaser_usb *dev,
					   u8 cmd_id, पूर्णांक channel)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक rc;

	cmd = kदो_स्मृति(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->id = cmd_id;
	cmd->len = CMD_HEADER_LEN + माप(काष्ठा kvaser_cmd_simple);
	cmd->u.simple.channel = channel;
	cmd->u.simple.tid = 0xff;

	rc = kvaser_usb_send_cmd(dev, cmd, cmd->len);

	kमुक्त(cmd);
	वापस rc;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_get_software_info_inner(काष्ठा kvaser_usb *dev)
अणु
	काष्ठा kvaser_cmd cmd;
	पूर्णांक err;

	err = kvaser_usb_leaf_send_simple_cmd(dev, CMD_GET_SOFTWARE_INFO, 0);
	अगर (err)
		वापस err;

	err = kvaser_usb_leaf_रुको_cmd(dev, CMD_GET_SOFTWARE_INFO_REPLY, &cmd);
	अगर (err)
		वापस err;

	चयन (dev->card_data.leaf.family) अणु
	हाल KVASER_LEAF:
		dev->fw_version = le32_to_cpu(cmd.u.leaf.softinfo.fw_version);
		dev->max_tx_urbs =
			le16_to_cpu(cmd.u.leaf.softinfo.max_outstanding_tx);
		अवरोध;
	हाल KVASER_USBCAN:
		dev->fw_version = le32_to_cpu(cmd.u.usbcan.softinfo.fw_version);
		dev->max_tx_urbs =
			le16_to_cpu(cmd.u.usbcan.softinfo.max_outstanding_tx);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_get_software_info(काष्ठा kvaser_usb *dev)
अणु
	पूर्णांक err;
	पूर्णांक retry = 3;

	/* On some x86 laptops, plugging a Kvaser device again after
	 * an unplug makes the firmware always ignore the very first
	 * command. For such a हाल, provide some room क्रम retries
	 * instead of completely निकासing the driver.
	 */
	करो अणु
		err = kvaser_usb_leaf_get_software_info_inner(dev);
	पूर्ण जबतक (--retry && err == -ETIMEDOUT);

	वापस err;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_get_card_info(काष्ठा kvaser_usb *dev)
अणु
	काष्ठा kvaser_cmd cmd;
	पूर्णांक err;

	err = kvaser_usb_leaf_send_simple_cmd(dev, CMD_GET_CARD_INFO, 0);
	अगर (err)
		वापस err;

	err = kvaser_usb_leaf_रुको_cmd(dev, CMD_GET_CARD_INFO_REPLY, &cmd);
	अगर (err)
		वापस err;

	dev->nchannels = cmd.u.cardinfo.nchannels;
	अगर (dev->nchannels > KVASER_USB_MAX_NET_DEVICES ||
	    (dev->card_data.leaf.family == KVASER_USBCAN &&
	     dev->nchannels > MAX_USBCAN_NET_DEVICES))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम kvaser_usb_leaf_tx_acknowledge(स्थिर काष्ठा kvaser_usb *dev,
					   स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा net_device_stats *stats;
	काष्ठा kvaser_usb_tx_urb_context *context;
	काष्ठा kvaser_usb_net_priv *priv;
	अचिन्हित दीर्घ flags;
	u8 channel, tid;

	channel = cmd->u.tx_acknowledge_header.channel;
	tid = cmd->u.tx_acknowledge_header.tid;

	अगर (channel >= dev->nchannels) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Invalid channel number (%d)\n", channel);
		वापस;
	पूर्ण

	priv = dev->nets[channel];

	अगर (!netअगर_device_present(priv->netdev))
		वापस;

	stats = &priv->netdev->stats;

	context = &priv->tx_contexts[tid % dev->max_tx_urbs];

	/* Someबार the state change करोesn't come after a bus-off event */
	अगर (priv->can.restart_ms && priv->can.state >= CAN_STATE_BUS_OFF) अणु
		काष्ठा sk_buff *skb;
		काष्ठा can_frame *cf;

		skb = alloc_can_err_skb(priv->netdev, &cf);
		अगर (skb) अणु
			cf->can_id |= CAN_ERR_RESTARTED;

			stats->rx_packets++;
			stats->rx_bytes += cf->len;
			netअगर_rx(skb);
		पूर्ण अन्यथा अणु
			netdev_err(priv->netdev,
				   "No memory left for err_skb\n");
		पूर्ण

		priv->can.can_stats.restarts++;
		netअगर_carrier_on(priv->netdev);

		priv->can.state = CAN_STATE_ERROR_ACTIVE;
	पूर्ण

	stats->tx_packets++;
	stats->tx_bytes += context->dlc;

	spin_lock_irqsave(&priv->tx_contexts_lock, flags);

	can_get_echo_skb(priv->netdev, context->echo_index, शून्य);
	context->echo_index = dev->max_tx_urbs;
	--priv->active_tx_contexts;
	netअगर_wake_queue(priv->netdev);

	spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_simple_cmd_async(काष्ठा kvaser_usb_net_priv *priv,
					    u8 cmd_id)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक err;

	cmd = kzalloc(माप(*cmd), GFP_ATOMIC);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->len = CMD_HEADER_LEN + माप(काष्ठा kvaser_cmd_simple);
	cmd->id = cmd_id;
	cmd->u.simple.channel = priv->channel;

	err = kvaser_usb_send_cmd_async(priv, cmd, cmd->len);
	अगर (err)
		kमुक्त(cmd);

	वापस err;
पूर्ण

अटल व्योम
kvaser_usb_leaf_rx_error_update_can_state(काष्ठा kvaser_usb_net_priv *priv,
					स्थिर काष्ठा kvaser_usb_err_summary *es,
					काष्ठा can_frame *cf)
अणु
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा net_device_stats *stats = &priv->netdev->stats;
	क्रमागत can_state cur_state, new_state, tx_state, rx_state;

	netdev_dbg(priv->netdev, "Error status: 0x%02x\n", es->status);

	new_state = priv->can.state;
	cur_state = priv->can.state;

	अगर (es->status & (M16C_STATE_BUS_OFF | M16C_STATE_BUS_RESET)) अणु
		new_state = CAN_STATE_BUS_OFF;
	पूर्ण अन्यथा अगर (es->status & M16C_STATE_BUS_PASSIVE) अणु
		new_state = CAN_STATE_ERROR_PASSIVE;
	पूर्ण अन्यथा अगर (es->status & M16C_STATE_BUS_ERROR) अणु
		/* Guard against spurious error events after a busoff */
		अगर (cur_state < CAN_STATE_BUS_OFF) अणु
			अगर (es->txerr >= 128 || es->rxerr >= 128)
				new_state = CAN_STATE_ERROR_PASSIVE;
			अन्यथा अगर (es->txerr >= 96 || es->rxerr >= 96)
				new_state = CAN_STATE_ERROR_WARNING;
			अन्यथा अगर (cur_state > CAN_STATE_ERROR_ACTIVE)
				new_state = CAN_STATE_ERROR_ACTIVE;
		पूर्ण
	पूर्ण

	अगर (!es->status)
		new_state = CAN_STATE_ERROR_ACTIVE;

	अगर (new_state != cur_state) अणु
		tx_state = (es->txerr >= es->rxerr) ? new_state : 0;
		rx_state = (es->txerr <= es->rxerr) ? new_state : 0;

		can_change_state(priv->netdev, cf, tx_state, rx_state);
	पूर्ण

	अगर (priv->can.restart_ms &&
	    cur_state >= CAN_STATE_BUS_OFF &&
	    new_state < CAN_STATE_BUS_OFF)
		priv->can.can_stats.restarts++;

	चयन (dev->card_data.leaf.family) अणु
	हाल KVASER_LEAF:
		अगर (es->leaf.error_factor) अणु
			priv->can.can_stats.bus_error++;
			stats->rx_errors++;
		पूर्ण
		अवरोध;
	हाल KVASER_USBCAN:
		अगर (es->usbcan.error_state & USBCAN_ERROR_STATE_TX_ERROR)
			stats->tx_errors++;
		अगर (es->usbcan.error_state & USBCAN_ERROR_STATE_RX_ERROR)
			stats->rx_errors++;
		अगर (es->usbcan.error_state & USBCAN_ERROR_STATE_BUSERROR)
			priv->can.can_stats.bus_error++;
		अवरोध;
	पूर्ण

	priv->bec.txerr = es->txerr;
	priv->bec.rxerr = es->rxerr;
पूर्ण

अटल व्योम kvaser_usb_leaf_rx_error(स्थिर काष्ठा kvaser_usb *dev,
				     स्थिर काष्ठा kvaser_usb_err_summary *es)
अणु
	काष्ठा can_frame *cf;
	काष्ठा can_frame पंचांगp_cf = अणु .can_id = CAN_ERR_FLAG,
				    .len = CAN_ERR_DLC पूर्ण;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats;
	काष्ठा kvaser_usb_net_priv *priv;
	क्रमागत can_state old_state, new_state;

	अगर (es->channel >= dev->nchannels) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Invalid channel number (%d)\n", es->channel);
		वापस;
	पूर्ण

	priv = dev->nets[es->channel];
	stats = &priv->netdev->stats;

	/* Update all of the CAN पूर्णांकerface's state and error counters beक्रमe
	 * trying any memory allocation that can actually fail with -ENOMEM.
	 *
	 * We send a temporary stack-allocated error CAN frame to
	 * can_change_state() क्रम the very same reason.
	 *
	 * TODO: Split can_change_state() responsibility between updating the
	 * CAN पूर्णांकerface's state and counters, and the setting up of CAN error
	 * frame ID and data to userspace. Remove stack allocation afterwards.
	 */
	old_state = priv->can.state;
	kvaser_usb_leaf_rx_error_update_can_state(priv, es, &पंचांगp_cf);
	new_state = priv->can.state;

	skb = alloc_can_err_skb(priv->netdev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण
	स_नकल(cf, &पंचांगp_cf, माप(*cf));

	अगर (new_state != old_state) अणु
		अगर (es->status &
		    (M16C_STATE_BUS_OFF | M16C_STATE_BUS_RESET)) अणु
			अगर (!priv->can.restart_ms)
				kvaser_usb_leaf_simple_cmd_async(priv,
								 CMD_STOP_CHIP);
			netअगर_carrier_off(priv->netdev);
		पूर्ण

		अगर (priv->can.restart_ms &&
		    old_state >= CAN_STATE_BUS_OFF &&
		    new_state < CAN_STATE_BUS_OFF) अणु
			cf->can_id |= CAN_ERR_RESTARTED;
			netअगर_carrier_on(priv->netdev);
		पूर्ण
	पूर्ण

	चयन (dev->card_data.leaf.family) अणु
	हाल KVASER_LEAF:
		अगर (es->leaf.error_factor) अणु
			cf->can_id |= CAN_ERR_BUSERROR | CAN_ERR_PROT;

			अगर (es->leaf.error_factor & M16C_EF_ACKE)
				cf->data[3] = CAN_ERR_PROT_LOC_ACK;
			अगर (es->leaf.error_factor & M16C_EF_CRCE)
				cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
			अगर (es->leaf.error_factor & M16C_EF_FORME)
				cf->data[2] |= CAN_ERR_PROT_FORM;
			अगर (es->leaf.error_factor & M16C_EF_STFE)
				cf->data[2] |= CAN_ERR_PROT_STUFF;
			अगर (es->leaf.error_factor & M16C_EF_BITE0)
				cf->data[2] |= CAN_ERR_PROT_BIT0;
			अगर (es->leaf.error_factor & M16C_EF_BITE1)
				cf->data[2] |= CAN_ERR_PROT_BIT1;
			अगर (es->leaf.error_factor & M16C_EF_TRE)
				cf->data[2] |= CAN_ERR_PROT_TX;
		पूर्ण
		अवरोध;
	हाल KVASER_USBCAN:
		अगर (es->usbcan.error_state & USBCAN_ERROR_STATE_BUSERROR)
			cf->can_id |= CAN_ERR_BUSERROR;
		अवरोध;
	पूर्ण

	cf->data[6] = es->txerr;
	cf->data[7] = es->rxerr;

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

/* For USBCAN, report error to userspace अगर the channels's errors counter
 * has changed, or we're the only channel seeing a bus error state.
 */
अटल व्योम
kvaser_usb_leaf_usbcan_conditionally_rx_error(स्थिर काष्ठा kvaser_usb *dev,
					      काष्ठा kvaser_usb_err_summary *es)
अणु
	काष्ठा kvaser_usb_net_priv *priv;
	अचिन्हित पूर्णांक channel;
	bool report_error;

	channel = es->channel;
	अगर (channel >= dev->nchannels) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Invalid channel number (%d)\n", channel);
		वापस;
	पूर्ण

	priv = dev->nets[channel];
	report_error = false;

	अगर (es->txerr != priv->bec.txerr) अणु
		es->usbcan.error_state |= USBCAN_ERROR_STATE_TX_ERROR;
		report_error = true;
	पूर्ण
	अगर (es->rxerr != priv->bec.rxerr) अणु
		es->usbcan.error_state |= USBCAN_ERROR_STATE_RX_ERROR;
		report_error = true;
	पूर्ण
	अगर ((es->status & M16C_STATE_BUS_ERROR) &&
	    !(es->usbcan.other_ch_status & M16C_STATE_BUS_ERROR)) अणु
		es->usbcan.error_state |= USBCAN_ERROR_STATE_BUSERROR;
		report_error = true;
	पूर्ण

	अगर (report_error)
		kvaser_usb_leaf_rx_error(dev, es);
पूर्ण

अटल व्योम kvaser_usb_leaf_usbcan_rx_error(स्थिर काष्ठा kvaser_usb *dev,
					    स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_err_summary es = अणु पूर्ण;

	चयन (cmd->id) अणु
	/* Someबार errors are sent as unsolicited chip state events */
	हाल CMD_CHIP_STATE_EVENT:
		es.channel = cmd->u.usbcan.chip_state_event.channel;
		es.status = cmd->u.usbcan.chip_state_event.status;
		es.txerr = cmd->u.usbcan.chip_state_event.tx_errors_count;
		es.rxerr = cmd->u.usbcan.chip_state_event.rx_errors_count;
		kvaser_usb_leaf_usbcan_conditionally_rx_error(dev, &es);
		अवरोध;

	हाल CMD_CAN_ERROR_EVENT:
		es.channel = 0;
		es.status = cmd->u.usbcan.error_event.status_ch0;
		es.txerr = cmd->u.usbcan.error_event.tx_errors_count_ch0;
		es.rxerr = cmd->u.usbcan.error_event.rx_errors_count_ch0;
		es.usbcan.other_ch_status =
			cmd->u.usbcan.error_event.status_ch1;
		kvaser_usb_leaf_usbcan_conditionally_rx_error(dev, &es);

		/* The USBCAN firmware supports up to 2 channels.
		 * Now that ch0 was checked, check अगर ch1 has any errors.
		 */
		अगर (dev->nchannels == MAX_USBCAN_NET_DEVICES) अणु
			es.channel = 1;
			es.status = cmd->u.usbcan.error_event.status_ch1;
			es.txerr =
				cmd->u.usbcan.error_event.tx_errors_count_ch1;
			es.rxerr =
				cmd->u.usbcan.error_event.rx_errors_count_ch1;
			es.usbcan.other_ch_status =
				cmd->u.usbcan.error_event.status_ch0;
			kvaser_usb_leaf_usbcan_conditionally_rx_error(dev, &es);
		पूर्ण
		अवरोध;

	शेष:
		dev_err(&dev->पूर्णांकf->dev, "Invalid cmd id (%d)\n", cmd->id);
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_leaf_leaf_rx_error(स्थिर काष्ठा kvaser_usb *dev,
					  स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_err_summary es = अणु पूर्ण;

	चयन (cmd->id) अणु
	हाल CMD_CAN_ERROR_EVENT:
		es.channel = cmd->u.leaf.error_event.channel;
		es.status = cmd->u.leaf.error_event.status;
		es.txerr = cmd->u.leaf.error_event.tx_errors_count;
		es.rxerr = cmd->u.leaf.error_event.rx_errors_count;
		es.leaf.error_factor = cmd->u.leaf.error_event.error_factor;
		अवरोध;
	हाल CMD_LEAF_LOG_MESSAGE:
		es.channel = cmd->u.leaf.log_message.channel;
		es.status = cmd->u.leaf.log_message.data[0];
		es.txerr = cmd->u.leaf.log_message.data[2];
		es.rxerr = cmd->u.leaf.log_message.data[3];
		es.leaf.error_factor = cmd->u.leaf.log_message.data[1];
		अवरोध;
	हाल CMD_CHIP_STATE_EVENT:
		es.channel = cmd->u.leaf.chip_state_event.channel;
		es.status = cmd->u.leaf.chip_state_event.status;
		es.txerr = cmd->u.leaf.chip_state_event.tx_errors_count;
		es.rxerr = cmd->u.leaf.chip_state_event.rx_errors_count;
		es.leaf.error_factor = 0;
		अवरोध;
	शेष:
		dev_err(&dev->पूर्णांकf->dev, "Invalid cmd id (%d)\n", cmd->id);
		वापस;
	पूर्ण

	kvaser_usb_leaf_rx_error(dev, &es);
पूर्ण

अटल व्योम kvaser_usb_leaf_rx_can_err(स्थिर काष्ठा kvaser_usb_net_priv *priv,
				       स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	अगर (cmd->u.rx_can_header.flag & (MSG_FLAG_ERROR_FRAME |
					 MSG_FLAG_NERR)) अणु
		काष्ठा net_device_stats *stats = &priv->netdev->stats;

		netdev_err(priv->netdev, "Unknown error (flags: 0x%02x)\n",
			   cmd->u.rx_can_header.flag);

		stats->rx_errors++;
		वापस;
	पूर्ण

	अगर (cmd->u.rx_can_header.flag & MSG_FLAG_OVERRUN)
		kvaser_usb_can_rx_over_error(priv->netdev);
पूर्ण

अटल व्योम kvaser_usb_leaf_rx_can_msg(स्थिर काष्ठा kvaser_usb *dev,
				       स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats;
	u8 channel = cmd->u.rx_can_header.channel;
	स्थिर u8 *rx_data = शून्य;	/* GCC */

	अगर (channel >= dev->nchannels) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Invalid channel number (%d)\n", channel);
		वापस;
	पूर्ण

	priv = dev->nets[channel];
	stats = &priv->netdev->stats;

	अगर ((cmd->u.rx_can_header.flag & MSG_FLAG_ERROR_FRAME) &&
	    (dev->card_data.leaf.family == KVASER_LEAF &&
	     cmd->id == CMD_LEAF_LOG_MESSAGE)) अणु
		kvaser_usb_leaf_leaf_rx_error(dev, cmd);
		वापस;
	पूर्ण अन्यथा अगर (cmd->u.rx_can_header.flag & (MSG_FLAG_ERROR_FRAME |
						MSG_FLAG_NERR |
						MSG_FLAG_OVERRUN)) अणु
		kvaser_usb_leaf_rx_can_err(priv, cmd);
		वापस;
	पूर्ण अन्यथा अगर (cmd->u.rx_can_header.flag & ~MSG_FLAG_REMOTE_FRAME) अणु
		netdev_warn(priv->netdev,
			    "Unhandled frame (flags: 0x%02x)\n",
			    cmd->u.rx_can_header.flag);
		वापस;
	पूर्ण

	चयन (dev->card_data.leaf.family) अणु
	हाल KVASER_LEAF:
		rx_data = cmd->u.leaf.rx_can.data;
		अवरोध;
	हाल KVASER_USBCAN:
		rx_data = cmd->u.usbcan.rx_can.data;
		अवरोध;
	पूर्ण

	skb = alloc_can_skb(priv->netdev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	अगर (dev->card_data.leaf.family == KVASER_LEAF && cmd->id ==
	    CMD_LEAF_LOG_MESSAGE) अणु
		cf->can_id = le32_to_cpu(cmd->u.leaf.log_message.id);
		अगर (cf->can_id & KVASER_EXTENDED_FRAME)
			cf->can_id &= CAN_EFF_MASK | CAN_EFF_FLAG;
		अन्यथा
			cf->can_id &= CAN_SFF_MASK;

		cf->len = can_cc_dlc2len(cmd->u.leaf.log_message.dlc);

		अगर (cmd->u.leaf.log_message.flags & MSG_FLAG_REMOTE_FRAME)
			cf->can_id |= CAN_RTR_FLAG;
		अन्यथा
			स_नकल(cf->data, &cmd->u.leaf.log_message.data,
			       cf->len);
	पूर्ण अन्यथा अणु
		cf->can_id = ((rx_data[0] & 0x1f) << 6) | (rx_data[1] & 0x3f);

		अगर (cmd->id == CMD_RX_EXT_MESSAGE) अणु
			cf->can_id <<= 18;
			cf->can_id |= ((rx_data[2] & 0x0f) << 14) |
				      ((rx_data[3] & 0xff) << 6) |
				      (rx_data[4] & 0x3f);
			cf->can_id |= CAN_EFF_FLAG;
		पूर्ण

		cf->len = can_cc_dlc2len(rx_data[5]);

		अगर (cmd->u.rx_can_header.flag & MSG_FLAG_REMOTE_FRAME)
			cf->can_id |= CAN_RTR_FLAG;
		अन्यथा
			स_नकल(cf->data, &rx_data[6], cf->len);
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);
पूर्ण

अटल व्योम kvaser_usb_leaf_start_chip_reply(स्थिर काष्ठा kvaser_usb *dev,
					     स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv;
	u8 channel = cmd->u.simple.channel;

	अगर (channel >= dev->nchannels) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Invalid channel number (%d)\n", channel);
		वापस;
	पूर्ण

	priv = dev->nets[channel];

	अगर (completion_करोne(&priv->start_comp) &&
	    netअगर_queue_stopped(priv->netdev)) अणु
		netअगर_wake_queue(priv->netdev);
	पूर्ण अन्यथा अणु
		netअगर_start_queue(priv->netdev);
		complete(&priv->start_comp);
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_leaf_stop_chip_reply(स्थिर काष्ठा kvaser_usb *dev,
					    स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	काष्ठा kvaser_usb_net_priv *priv;
	u8 channel = cmd->u.simple.channel;

	अगर (channel >= dev->nchannels) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Invalid channel number (%d)\n", channel);
		वापस;
	पूर्ण

	priv = dev->nets[channel];

	complete(&priv->stop_comp);
पूर्ण

अटल व्योम kvaser_usb_leaf_handle_command(स्थिर काष्ठा kvaser_usb *dev,
					   स्थिर काष्ठा kvaser_cmd *cmd)
अणु
	चयन (cmd->id) अणु
	हाल CMD_START_CHIP_REPLY:
		kvaser_usb_leaf_start_chip_reply(dev, cmd);
		अवरोध;

	हाल CMD_STOP_CHIP_REPLY:
		kvaser_usb_leaf_stop_chip_reply(dev, cmd);
		अवरोध;

	हाल CMD_RX_STD_MESSAGE:
	हाल CMD_RX_EXT_MESSAGE:
		kvaser_usb_leaf_rx_can_msg(dev, cmd);
		अवरोध;

	हाल CMD_LEAF_LOG_MESSAGE:
		अगर (dev->card_data.leaf.family != KVASER_LEAF)
			जाओ warn;
		kvaser_usb_leaf_rx_can_msg(dev, cmd);
		अवरोध;

	हाल CMD_CHIP_STATE_EVENT:
	हाल CMD_CAN_ERROR_EVENT:
		अगर (dev->card_data.leaf.family == KVASER_LEAF)
			kvaser_usb_leaf_leaf_rx_error(dev, cmd);
		अन्यथा
			kvaser_usb_leaf_usbcan_rx_error(dev, cmd);
		अवरोध;

	हाल CMD_TX_ACKNOWLEDGE:
		kvaser_usb_leaf_tx_acknowledge(dev, cmd);
		अवरोध;

	/* Ignored commands */
	हाल CMD_USBCAN_CLOCK_OVERFLOW_EVENT:
		अगर (dev->card_data.leaf.family != KVASER_USBCAN)
			जाओ warn;
		अवरोध;

	हाल CMD_FLUSH_QUEUE_REPLY:
		अगर (dev->card_data.leaf.family != KVASER_LEAF)
			जाओ warn;
		अवरोध;

	शेष:
warn:		dev_warn(&dev->पूर्णांकf->dev, "Unhandled command (%d)\n", cmd->id);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम kvaser_usb_leaf_पढ़ो_bulk_callback(काष्ठा kvaser_usb *dev,
					       व्योम *buf, पूर्णांक len)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक pos = 0;

	जबतक (pos <= len - CMD_HEADER_LEN) अणु
		cmd = buf + pos;

		/* The Kvaser firmware can only पढ़ो and ग_लिखो commands that
		 * करोes not cross the USB's endpoपूर्णांक wMaxPacketSize boundary.
		 * If a follow-up command crosses such boundary, firmware माला_दो
		 * a placeholder zero-length command in its place then aligns
		 * the real command to the next max packet size.
		 *
		 * Handle such हालs or we're going to miss a signअगरicant
		 * number of events in हाल of a heavy rx load on the bus.
		 */
		अगर (cmd->len == 0) अणु
			pos = round_up(pos, le16_to_cpu
						(dev->bulk_in->wMaxPacketSize));
			जारी;
		पूर्ण

		अगर (pos + cmd->len > len) अणु
			dev_err_ratelimited(&dev->पूर्णांकf->dev, "Format error\n");
			अवरोध;
		पूर्ण

		kvaser_usb_leaf_handle_command(dev, cmd);
		pos += cmd->len;
	पूर्ण
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_set_opt_mode(स्थिर काष्ठा kvaser_usb_net_priv *priv)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->id = CMD_SET_CTRL_MODE;
	cmd->len = CMD_HEADER_LEN + माप(काष्ठा kvaser_cmd_ctrl_mode);
	cmd->u.ctrl_mode.tid = 0xff;
	cmd->u.ctrl_mode.channel = priv->channel;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		cmd->u.ctrl_mode.ctrl_mode = KVASER_CTRL_MODE_SILENT;
	अन्यथा
		cmd->u.ctrl_mode.ctrl_mode = KVASER_CTRL_MODE_NORMAL;

	rc = kvaser_usb_send_cmd(priv->dev, cmd, cmd->len);

	kमुक्त(cmd);
	वापस rc;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_start_chip(काष्ठा kvaser_usb_net_priv *priv)
अणु
	पूर्णांक err;

	init_completion(&priv->start_comp);

	err = kvaser_usb_leaf_send_simple_cmd(priv->dev, CMD_START_CHIP,
					      priv->channel);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&priv->start_comp,
					 msecs_to_jअगरfies(KVASER_USB_TIMEOUT)))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_stop_chip(काष्ठा kvaser_usb_net_priv *priv)
अणु
	पूर्णांक err;

	init_completion(&priv->stop_comp);

	err = kvaser_usb_leaf_send_simple_cmd(priv->dev, CMD_STOP_CHIP,
					      priv->channel);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&priv->stop_comp,
					 msecs_to_jअगरfies(KVASER_USB_TIMEOUT)))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_reset_chip(काष्ठा kvaser_usb *dev, पूर्णांक channel)
अणु
	वापस kvaser_usb_leaf_send_simple_cmd(dev, CMD_RESET_CHIP, channel);
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_flush_queue(काष्ठा kvaser_usb_net_priv *priv)
अणु
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक rc;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->id = CMD_FLUSH_QUEUE;
	cmd->len = CMD_HEADER_LEN + माप(काष्ठा kvaser_cmd_flush_queue);
	cmd->u.flush_queue.channel = priv->channel;
	cmd->u.flush_queue.flags = 0x00;

	rc = kvaser_usb_send_cmd(priv->dev, cmd, cmd->len);

	kमुक्त(cmd);
	वापस rc;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_init_card(काष्ठा kvaser_usb *dev)
अणु
	काष्ठा kvaser_usb_dev_card_data *card_data = &dev->card_data;

	dev->cfg = &kvaser_usb_leaf_dev_cfg;
	card_data->ctrlmode_supported |= CAN_CTRLMODE_3_SAMPLES;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा can_bittiming_स्थिर kvaser_usb_leaf_bittiming_स्थिर = अणु
	.name = "kvaser_usb",
	.tseg1_min = KVASER_USB_TSEG1_MIN,
	.tseg1_max = KVASER_USB_TSEG1_MAX,
	.tseg2_min = KVASER_USB_TSEG2_MIN,
	.tseg2_max = KVASER_USB_TSEG2_MAX,
	.sjw_max = KVASER_USB_SJW_MAX,
	.brp_min = KVASER_USB_BRP_MIN,
	.brp_max = KVASER_USB_BRP_MAX,
	.brp_inc = KVASER_USB_BRP_INC,
पूर्ण;

अटल पूर्णांक kvaser_usb_leaf_set_bittiming(काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा kvaser_usb *dev = priv->dev;
	काष्ठा kvaser_cmd *cmd;
	पूर्णांक rc;

	cmd = kदो_स्मृति(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->id = CMD_SET_BUS_PARAMS;
	cmd->len = CMD_HEADER_LEN + माप(काष्ठा kvaser_cmd_busparams);
	cmd->u.busparams.channel = priv->channel;
	cmd->u.busparams.tid = 0xff;
	cmd->u.busparams.bitrate = cpu_to_le32(bt->bitrate);
	cmd->u.busparams.sjw = bt->sjw;
	cmd->u.busparams.tseg1 = bt->prop_seg + bt->phase_seg1;
	cmd->u.busparams.tseg2 = bt->phase_seg2;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		cmd->u.busparams.no_samp = 3;
	अन्यथा
		cmd->u.busparams.no_samp = 1;

	rc = kvaser_usb_send_cmd(dev, cmd, cmd->len);

	kमुक्त(cmd);
	वापस rc;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_set_mode(काष्ठा net_device *netdev,
				    क्रमागत can_mode mode)
अणु
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);
	पूर्णांक err;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = kvaser_usb_leaf_simple_cmd_async(priv, CMD_START_CHIP);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_get_berr_counter(स्थिर काष्ठा net_device *netdev,
					    काष्ठा can_berr_counter *bec)
अणु
	काष्ठा kvaser_usb_net_priv *priv = netdev_priv(netdev);

	*bec = priv->bec;

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_usb_leaf_setup_endpoपूर्णांकs(काष्ठा kvaser_usb *dev)
अणु
	स्थिर काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक i;

	अगरace_desc = dev->पूर्णांकf->cur_altsetting;

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (!dev->bulk_in && usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक))
			dev->bulk_in = endpoपूर्णांक;

		अगर (!dev->bulk_out && usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक))
			dev->bulk_out = endpoपूर्णांक;

		/* use first bulk endpoपूर्णांक क्रम in and out */
		अगर (dev->bulk_in && dev->bulk_out)
			वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

स्थिर काष्ठा kvaser_usb_dev_ops kvaser_usb_leaf_dev_ops = अणु
	.dev_set_mode = kvaser_usb_leaf_set_mode,
	.dev_set_bittiming = kvaser_usb_leaf_set_bittiming,
	.dev_set_data_bittiming = शून्य,
	.dev_get_berr_counter = kvaser_usb_leaf_get_berr_counter,
	.dev_setup_endpoपूर्णांकs = kvaser_usb_leaf_setup_endpoपूर्णांकs,
	.dev_init_card = kvaser_usb_leaf_init_card,
	.dev_get_software_info = kvaser_usb_leaf_get_software_info,
	.dev_get_software_details = शून्य,
	.dev_get_card_info = kvaser_usb_leaf_get_card_info,
	.dev_get_capabilities = शून्य,
	.dev_set_opt_mode = kvaser_usb_leaf_set_opt_mode,
	.dev_start_chip = kvaser_usb_leaf_start_chip,
	.dev_stop_chip = kvaser_usb_leaf_stop_chip,
	.dev_reset_chip = kvaser_usb_leaf_reset_chip,
	.dev_flush_queue = kvaser_usb_leaf_flush_queue,
	.dev_पढ़ो_bulk_callback = kvaser_usb_leaf_पढ़ो_bulk_callback,
	.dev_frame_to_cmd = kvaser_usb_leaf_frame_to_cmd,
पूर्ण;

अटल स्थिर काष्ठा kvaser_usb_dev_cfg kvaser_usb_leaf_dev_cfg = अणु
	.घड़ी = अणु
		.freq = CAN_USB_CLOCK,
	पूर्ण,
	.बारtamp_freq = 1,
	.bittiming_स्थिर = &kvaser_usb_leaf_bittiming_स्थिर,
पूर्ण;
