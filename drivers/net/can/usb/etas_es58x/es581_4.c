<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Driver क्रम ETAS GmbH ES58X USB CAN(-FD) Bus Interfaces.
 *
 * File es581_4.c: Adds support to ETAS ES581.4.
 *
 * Copyright (c) 2019 Robert Bosch Engineering and Business Solutions. All rights reserved.
 * Copyright (c) 2020 ETAS K.K.. All rights reserved.
 * Copyright (c) 2020, 2021 Vincent Mailhol <mailhol.vincent@wanaकरोo.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "es58x_core.h"
#समावेश "es581_4.h"

/**
 * es581_4_माप_rx_tx_msg() - Calculate the actual length of the
 *	काष्ठाure of a rx or tx message.
 * @msg: message of variable length, must have a dlc field.
 *
 * Even अगर RTR frames have actually no payload, the ES58X devices
 * still expect it. Must be a macro in order to accept several types
 * (काष्ठा es581_4_tx_can_msg and काष्ठा es581_4_rx_can_msg) as an
 * input.
 *
 * Return: length of the message.
 */
#घोषणा es581_4_माप_rx_tx_msg(msg)				\
	दुरत्व(typeof(msg), data[can_cc_dlc2len((msg).dlc)])

अटल u16 es581_4_get_msg_len(स्थिर जोड़ es58x_urb_cmd *urb_cmd)
अणु
	वापस get_unaligned_le16(&urb_cmd->es581_4_urb_cmd.msg_len);
पूर्ण

अटल पूर्णांक es581_4_echo_msg(काष्ठा es58x_device *es58x_dev,
			    स्थिर काष्ठा es581_4_urb_cmd *es581_4_urb_cmd)
अणु
	काष्ठा net_device *netdev;
	स्थिर काष्ठा es581_4_bulk_echo_msg *bulk_echo_msg;
	स्थिर काष्ठा es581_4_echo_msg *echo_msg;
	u64 *tstamps = es58x_dev->बारtamps;
	u16 msg_len;
	u32 first_packet_idx, packet_idx;
	अचिन्हित पूर्णांक dropped = 0;
	पूर्णांक i, num_element, ret;

	bulk_echo_msg = &es581_4_urb_cmd->bulk_echo_msg;
	msg_len = get_unaligned_le16(&es581_4_urb_cmd->msg_len) -
	    माप(bulk_echo_msg->channel_no);
	num_element = es58x_msg_num_element(es58x_dev->dev,
					    bulk_echo_msg->echo_msg, msg_len);
	अगर (num_element <= 0)
		वापस num_element;

	ret = es58x_get_netdev(es58x_dev, bulk_echo_msg->channel_no,
			       ES581_4_CHANNEL_IDX_OFFSET, &netdev);
	अगर (ret)
		वापस ret;

	echo_msg = &bulk_echo_msg->echo_msg[0];
	first_packet_idx = get_unaligned_le32(&echo_msg->packet_idx);
	packet_idx = first_packet_idx;
	क्रम (i = 0; i < num_element; i++) अणु
		u32 पंचांगp_idx;

		echo_msg = &bulk_echo_msg->echo_msg[i];
		पंचांगp_idx = get_unaligned_le32(&echo_msg->packet_idx);
		अगर (पंचांगp_idx == packet_idx - 1) अणु
			अगर (net_ratelimit())
				netdev_warn(netdev,
					    "Received echo packet idx %u twice\n",
					    packet_idx - 1);
			dropped++;
			जारी;
		पूर्ण
		अगर (पंचांगp_idx != packet_idx) अणु
			netdev_err(netdev, "Echo packet idx jumped from %u to %u\n",
				   packet_idx - 1, echo_msg->packet_idx);
			वापस -EBADMSG;
		पूर्ण

		tstamps[i] = get_unaligned_le64(&echo_msg->बारtamp);
		packet_idx++;
	पूर्ण

	netdev->stats.tx_dropped += dropped;
	वापस es58x_can_get_echo_skb(netdev, first_packet_idx,
				      tstamps, num_element - dropped);
पूर्ण

अटल पूर्णांक es581_4_rx_can_msg(काष्ठा es58x_device *es58x_dev,
			      स्थिर काष्ठा es581_4_urb_cmd *es581_4_urb_cmd,
			      u16 msg_len)
अणु
	स्थिर काष्ठा device *dev = es58x_dev->dev;
	काष्ठा net_device *netdev;
	पूर्णांक pkts, num_element, channel_no, ret;

	num_element = es58x_msg_num_element(dev, es581_4_urb_cmd->rx_can_msg,
					    msg_len);
	अगर (num_element <= 0)
		वापस num_element;

	channel_no = es581_4_urb_cmd->rx_can_msg[0].channel_no;
	ret = es58x_get_netdev(es58x_dev, channel_no,
			       ES581_4_CHANNEL_IDX_OFFSET, &netdev);
	अगर (ret)
		वापस ret;

	अगर (!netअगर_running(netdev)) अणु
		अगर (net_ratelimit())
			netdev_info(netdev,
				    "%s: %s is down, dropping %d rx packets\n",
				    __func__, netdev->name, num_element);
		netdev->stats.rx_dropped += num_element;
		वापस 0;
	पूर्ण

	क्रम (pkts = 0; pkts < num_element; pkts++) अणु
		स्थिर काष्ठा es581_4_rx_can_msg *rx_can_msg =
		    &es581_4_urb_cmd->rx_can_msg[pkts];
		u64 tstamp = get_unaligned_le64(&rx_can_msg->बारtamp);
		canid_t can_id = get_unaligned_le32(&rx_can_msg->can_id);

		अगर (channel_no != rx_can_msg->channel_no)
			वापस -EBADMSG;

		ret = es58x_rx_can_msg(netdev, tstamp, rx_can_msg->data,
				       can_id, rx_can_msg->flags,
				       rx_can_msg->dlc);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक es581_4_rx_err_msg(काष्ठा es58x_device *es58x_dev,
			      स्थिर काष्ठा es581_4_rx_err_msg *rx_err_msg)
अणु
	काष्ठा net_device *netdev;
	क्रमागत es58x_err error = get_unaligned_le32(&rx_err_msg->error);
	पूर्णांक ret;

	ret = es58x_get_netdev(es58x_dev, rx_err_msg->channel_no,
			       ES581_4_CHANNEL_IDX_OFFSET, &netdev);
	अगर (ret)
		वापस ret;

	वापस es58x_rx_err_msg(netdev, error, 0,
				get_unaligned_le64(&rx_err_msg->बारtamp));
पूर्ण

अटल पूर्णांक es581_4_rx_event_msg(काष्ठा es58x_device *es58x_dev,
				स्थिर काष्ठा es581_4_rx_event_msg *rx_event_msg)
अणु
	काष्ठा net_device *netdev;
	क्रमागत es58x_event event = get_unaligned_le32(&rx_event_msg->event);
	पूर्णांक ret;

	ret = es58x_get_netdev(es58x_dev, rx_event_msg->channel_no,
			       ES581_4_CHANNEL_IDX_OFFSET, &netdev);
	अगर (ret)
		वापस ret;

	वापस es58x_rx_err_msg(netdev, 0, event,
				get_unaligned_le64(&rx_event_msg->बारtamp));
पूर्ण

अटल पूर्णांक es581_4_rx_cmd_ret_u32(काष्ठा es58x_device *es58x_dev,
				  स्थिर काष्ठा es581_4_urb_cmd *es581_4_urb_cmd,
				  क्रमागत es58x_ret_type ret_type)
अणु
	काष्ठा net_device *netdev;
	स्थिर काष्ठा es581_4_rx_cmd_ret *rx_cmd_ret;
	u16 msg_len = get_unaligned_le16(&es581_4_urb_cmd->msg_len);
	पूर्णांक ret;

	ret = es58x_check_msg_len(es58x_dev->dev,
				  es581_4_urb_cmd->rx_cmd_ret, msg_len);
	अगर (ret)
		वापस ret;

	rx_cmd_ret = &es581_4_urb_cmd->rx_cmd_ret;

	ret = es58x_get_netdev(es58x_dev, rx_cmd_ret->channel_no,
			       ES581_4_CHANNEL_IDX_OFFSET, &netdev);
	अगर (ret)
		वापस ret;

	वापस es58x_rx_cmd_ret_u32(netdev, ret_type,
				    get_unaligned_le32(&rx_cmd_ret->rx_cmd_ret_le32));
पूर्ण

अटल पूर्णांक es581_4_tx_ack_msg(काष्ठा es58x_device *es58x_dev,
			      स्थिर काष्ठा es581_4_urb_cmd *es581_4_urb_cmd)
अणु
	काष्ठा net_device *netdev;
	स्थिर काष्ठा es581_4_tx_ack_msg *tx_ack_msg;
	u16 msg_len = get_unaligned_le16(&es581_4_urb_cmd->msg_len);
	पूर्णांक ret;

	tx_ack_msg = &es581_4_urb_cmd->tx_ack_msg;
	ret = es58x_check_msg_len(es58x_dev->dev, *tx_ack_msg, msg_len);
	अगर (ret)
		वापस ret;

	अगर (tx_ack_msg->rx_cmd_ret_u8 != ES58X_RET_U8_OK)
		वापस es58x_rx_cmd_ret_u8(es58x_dev->dev,
					   ES58X_RET_TYPE_TX_MSG,
					   tx_ack_msg->rx_cmd_ret_u8);

	ret = es58x_get_netdev(es58x_dev, tx_ack_msg->channel_no,
			       ES581_4_CHANNEL_IDX_OFFSET, &netdev);
	अगर (ret)
		वापस ret;

	वापस es58x_tx_ack_msg(netdev,
				get_unaligned_le16(&tx_ack_msg->tx_मुक्त_entries),
				ES58X_RET_U32_OK);
पूर्ण

अटल पूर्णांक es581_4_dispatch_rx_cmd(काष्ठा es58x_device *es58x_dev,
				   स्थिर काष्ठा es581_4_urb_cmd *es581_4_urb_cmd)
अणु
	स्थिर काष्ठा device *dev = es58x_dev->dev;
	u16 msg_len = get_unaligned_le16(&es581_4_urb_cmd->msg_len);
	क्रमागत es581_4_rx_type rx_type = es581_4_urb_cmd->rx_can_msg[0].rx_type;
	पूर्णांक ret = 0;

	चयन (rx_type) अणु
	हाल ES581_4_RX_TYPE_MESSAGE:
		वापस es581_4_rx_can_msg(es58x_dev, es581_4_urb_cmd, msg_len);

	हाल ES581_4_RX_TYPE_ERROR:
		ret = es58x_check_msg_len(dev, es581_4_urb_cmd->rx_err_msg,
					  msg_len);
		अगर (ret < 0)
			वापस ret;
		वापस es581_4_rx_err_msg(es58x_dev,
					  &es581_4_urb_cmd->rx_err_msg);

	हाल ES581_4_RX_TYPE_EVENT:
		ret = es58x_check_msg_len(dev, es581_4_urb_cmd->rx_event_msg,
					  msg_len);
		अगर (ret < 0)
			वापस ret;
		वापस es581_4_rx_event_msg(es58x_dev,
					    &es581_4_urb_cmd->rx_event_msg);

	शेष:
		dev_err(dev, "%s: Unknown rx_type 0x%02X\n", __func__, rx_type);
		वापस -EBADRQC;
	पूर्ण
पूर्ण

अटल पूर्णांक es581_4_handle_urb_cmd(काष्ठा es58x_device *es58x_dev,
				  स्थिर जोड़ es58x_urb_cmd *urb_cmd)
अणु
	स्थिर काष्ठा es581_4_urb_cmd *es581_4_urb_cmd;
	काष्ठा device *dev = es58x_dev->dev;
	u16 msg_len = es581_4_get_msg_len(urb_cmd);
	पूर्णांक ret;

	es581_4_urb_cmd = &urb_cmd->es581_4_urb_cmd;

	अगर (es581_4_urb_cmd->cmd_type != ES581_4_CAN_COMMAND_TYPE) अणु
		dev_err(dev, "%s: Unknown command type (0x%02X)\n",
			__func__, es581_4_urb_cmd->cmd_type);
		वापस -EBADRQC;
	पूर्ण

	चयन ((क्रमागत es581_4_cmd_id)es581_4_urb_cmd->cmd_id) अणु
	हाल ES581_4_CMD_ID_SET_BITTIMING:
		वापस es581_4_rx_cmd_ret_u32(es58x_dev, es581_4_urb_cmd,
					      ES58X_RET_TYPE_SET_BITTIMING);

	हाल ES581_4_CMD_ID_ENABLE_CHANNEL:
		वापस es581_4_rx_cmd_ret_u32(es58x_dev, es581_4_urb_cmd,
					      ES58X_RET_TYPE_ENABLE_CHANNEL);

	हाल ES581_4_CMD_ID_TX_MSG:
		वापस es581_4_tx_ack_msg(es58x_dev, es581_4_urb_cmd);

	हाल ES581_4_CMD_ID_RX_MSG:
		वापस es581_4_dispatch_rx_cmd(es58x_dev, es581_4_urb_cmd);

	हाल ES581_4_CMD_ID_RESET_RX:
		ret = es581_4_rx_cmd_ret_u32(es58x_dev, es581_4_urb_cmd,
					     ES58X_RET_TYPE_RESET_RX);
		वापस ret;

	हाल ES581_4_CMD_ID_RESET_TX:
		ret = es581_4_rx_cmd_ret_u32(es58x_dev, es581_4_urb_cmd,
					     ES58X_RET_TYPE_RESET_TX);
		वापस ret;

	हाल ES581_4_CMD_ID_DISABLE_CHANNEL:
		वापस es581_4_rx_cmd_ret_u32(es58x_dev, es581_4_urb_cmd,
					      ES58X_RET_TYPE_DISABLE_CHANNEL);

	हाल ES581_4_CMD_ID_TIMESTAMP:
		ret = es58x_check_msg_len(dev, es581_4_urb_cmd->बारtamp,
					  msg_len);
		अगर (ret < 0)
			वापस ret;
		es58x_rx_बारtamp(es58x_dev,
				   get_unaligned_le64(&es581_4_urb_cmd->बारtamp));
		वापस 0;

	हाल ES581_4_CMD_ID_ECHO:
		वापस es581_4_echo_msg(es58x_dev, es581_4_urb_cmd);

	हाल ES581_4_CMD_ID_DEVICE_ERR:
		ret = es58x_check_msg_len(dev, es581_4_urb_cmd->rx_cmd_ret_u8,
					  msg_len);
		अगर (ret)
			वापस ret;
		वापस es58x_rx_cmd_ret_u8(dev, ES58X_RET_TYPE_DEVICE_ERR,
					   es581_4_urb_cmd->rx_cmd_ret_u8);

	शेष:
		dev_warn(dev, "%s: Unexpected command ID: 0x%02X\n",
			 __func__, es581_4_urb_cmd->cmd_id);
		वापस -EBADRQC;
	पूर्ण
पूर्ण

अटल व्योम es581_4_fill_urb_header(जोड़ es58x_urb_cmd *urb_cmd, u8 cmd_type,
				    u8 cmd_id, u8 channel_idx, u16 msg_len)
अणु
	काष्ठा es581_4_urb_cmd *es581_4_urb_cmd = &urb_cmd->es581_4_urb_cmd;

	es581_4_urb_cmd->SOF = cpu_to_le16(es581_4_param.tx_start_of_frame);
	es581_4_urb_cmd->cmd_type = cmd_type;
	es581_4_urb_cmd->cmd_id = cmd_id;
	es581_4_urb_cmd->msg_len = cpu_to_le16(msg_len);
पूर्ण

अटल पूर्णांक es581_4_tx_can_msg(काष्ठा es58x_priv *priv,
			      स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा es58x_device *es58x_dev = priv->es58x_dev;
	जोड़ es58x_urb_cmd *urb_cmd = priv->tx_urb->transfer_buffer;
	काष्ठा es581_4_urb_cmd *es581_4_urb_cmd = &urb_cmd->es581_4_urb_cmd;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	काष्ठा es581_4_tx_can_msg *tx_can_msg;
	u16 msg_len;
	पूर्णांक ret;

	अगर (can_is_canfd_skb(skb))
		वापस -EMSGSIZE;

	अगर (priv->tx_can_msg_cnt == 0) अणु
		msg_len = 1; /* काष्ठा es581_4_bulk_tx_can_msg:num_can_msg */
		es581_4_fill_urb_header(urb_cmd, ES581_4_CAN_COMMAND_TYPE,
					ES581_4_CMD_ID_TX_MSG,
					priv->channel_idx, msg_len);
		es581_4_urb_cmd->bulk_tx_can_msg.num_can_msg = 0;
	पूर्ण अन्यथा अणु
		msg_len = es581_4_get_msg_len(urb_cmd);
	पूर्ण

	ret = es58x_check_msg_max_len(es58x_dev->dev,
				      es581_4_urb_cmd->bulk_tx_can_msg,
				      msg_len + माप(*tx_can_msg));
	अगर (ret)
		वापस ret;

	/* Fill message contents. */
	tx_can_msg = (काष्ठा es581_4_tx_can_msg *)
	    &es581_4_urb_cmd->bulk_tx_can_msg.tx_can_msg_buf[msg_len - 1];
	put_unaligned_le32(es58x_get_raw_can_id(cf), &tx_can_msg->can_id);
	put_unaligned_le32(priv->tx_head, &tx_can_msg->packet_idx);
	put_unaligned_le16((u16)es58x_get_flags(skb), &tx_can_msg->flags);
	tx_can_msg->channel_no = priv->channel_idx + ES581_4_CHANNEL_IDX_OFFSET;
	tx_can_msg->dlc = can_get_cc_dlc(cf, priv->can.ctrlmode);

	स_नकल(tx_can_msg->data, cf->data, cf->len);

	/* Calculate new sizes. */
	es581_4_urb_cmd->bulk_tx_can_msg.num_can_msg++;
	msg_len += es581_4_माप_rx_tx_msg(*tx_can_msg);
	priv->tx_urb->transfer_buffer_length = es58x_get_urb_cmd_len(es58x_dev,
								     msg_len);
	es581_4_urb_cmd->msg_len = cpu_to_le16(msg_len);

	वापस 0;
पूर्ण

अटल पूर्णांक es581_4_set_bittiming(काष्ठा es58x_priv *priv)
अणु
	काष्ठा es581_4_tx_conf_msg tx_conf_msg = अणु 0 पूर्ण;
	काष्ठा can_bittiming *bt = &priv->can.bittiming;

	tx_conf_msg.bitrate = cpu_to_le32(bt->bitrate);
	/* bt->sample_poपूर्णांक is in tenth of percent. Convert it to percent. */
	tx_conf_msg.sample_poपूर्णांक = cpu_to_le32(bt->sample_poपूर्णांक / 10U);
	tx_conf_msg.samples_per_bit = cpu_to_le32(ES58X_SAMPLES_PER_BIT_ONE);
	tx_conf_msg.bit_समय = cpu_to_le32(can_bit_समय(bt));
	tx_conf_msg.sjw = cpu_to_le32(bt->sjw);
	tx_conf_msg.sync_edge = cpu_to_le32(ES58X_SYNC_EDGE_SINGLE);
	tx_conf_msg.physical_layer =
	    cpu_to_le32(ES58X_PHYSICAL_LAYER_HIGH_SPEED);
	tx_conf_msg.echo_mode = cpu_to_le32(ES58X_ECHO_ON);
	tx_conf_msg.channel_no = priv->channel_idx + ES581_4_CHANNEL_IDX_OFFSET;

	वापस es58x_send_msg(priv->es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_SET_BITTIMING, &tx_conf_msg,
			      माप(tx_conf_msg), priv->channel_idx);
पूर्ण

अटल पूर्णांक es581_4_enable_channel(काष्ठा es58x_priv *priv)
अणु
	पूर्णांक ret;
	u8 msg = priv->channel_idx + ES581_4_CHANNEL_IDX_OFFSET;

	ret = es581_4_set_bittiming(priv);
	अगर (ret)
		वापस ret;

	वापस es58x_send_msg(priv->es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_ENABLE_CHANNEL, &msg, माप(msg),
			      priv->channel_idx);
पूर्ण

अटल पूर्णांक es581_4_disable_channel(काष्ठा es58x_priv *priv)
अणु
	u8 msg = priv->channel_idx + ES581_4_CHANNEL_IDX_OFFSET;

	वापस es58x_send_msg(priv->es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_DISABLE_CHANNEL, &msg, माप(msg),
			      priv->channel_idx);
पूर्ण

अटल पूर्णांक es581_4_reset_device(काष्ठा es58x_device *es58x_dev)
अणु
	वापस es58x_send_msg(es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_RESET_DEVICE,
			      ES58X_EMPTY_MSG, 0, ES58X_CHANNEL_IDX_NA);
पूर्ण

अटल पूर्णांक es581_4_get_बारtamp(काष्ठा es58x_device *es58x_dev)
अणु
	वापस es58x_send_msg(es58x_dev, ES581_4_CAN_COMMAND_TYPE,
			      ES581_4_CMD_ID_TIMESTAMP,
			      ES58X_EMPTY_MSG, 0, ES58X_CHANNEL_IDX_NA);
पूर्ण

/* Nominal bittiming स्थिरants क्रम ES581.4 as specअगरied in the
 * microcontroller datasheet: "Stellaris(R) LM3S5B91 Microcontroller"
 * table 17-4 "CAN Protocol Ranges" from Texas Instruments.
 */
अटल स्थिर काष्ठा can_bittiming_स्थिर es581_4_bittiming_स्थिर = अणु
	.name = "ES581.4",
	.tseg1_min = 1,
	.tseg1_max = 8,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 128,
	.brp_inc = 1
पूर्ण;

स्थिर काष्ठा es58x_parameters es581_4_param = अणु
	.bittiming_स्थिर = &es581_4_bittiming_स्थिर,
	.data_bittiming_स्थिर = शून्य,
	.tdc_स्थिर = शून्य,
	.bitrate_max = 1 * CAN_MBPS,
	.घड़ी = अणु.freq = 50 * CAN_MHZपूर्ण,
	.ctrlmode_supported = CAN_CTRLMODE_CC_LEN8_DLC,
	.tx_start_of_frame = 0xAFAF,
	.rx_start_of_frame = 0xFAFA,
	.tx_urb_cmd_max_len = ES581_4_TX_URB_CMD_MAX_LEN,
	.rx_urb_cmd_max_len = ES581_4_RX_URB_CMD_MAX_LEN,
	/* Size of पूर्णांकernal device TX queue is 330.
	 *
	 * However, we witnessed some ES58X_ERR_PROT_CRC errors from
	 * the device and thus, echo_skb_max was lowered to the
	 * empirical value of 75 which seems stable and then rounded
	 * करोwn to become a घातer of two.
	 *
	 * Root cause of those ES58X_ERR_PROT_CRC errors is still
	 * unclear.
	 */
	.fअगरo_mask = 63, /* echo_skb_max = 64 */
	.dql_min_limit = CAN_FRAME_LEN_MAX * 50, /* Empirical value. */
	.tx_bulk_max = ES581_4_TX_BULK_MAX,
	.urb_cmd_header_len = ES581_4_URB_CMD_HEADER_LEN,
	.rx_urb_max = ES58X_RX_URBS_MAX,
	.tx_urb_max = ES58X_TX_URBS_MAX
पूर्ण;

स्थिर काष्ठा es58x_चालकs es581_4_ops = अणु
	.get_msg_len = es581_4_get_msg_len,
	.handle_urb_cmd = es581_4_handle_urb_cmd,
	.fill_urb_header = es581_4_fill_urb_header,
	.tx_can_msg = es581_4_tx_can_msg,
	.enable_channel = es581_4_enable_channel,
	.disable_channel = es581_4_disable_channel,
	.reset_device = es581_4_reset_device,
	.get_बारtamp = es581_4_get_बारtamp
पूर्ण;
