<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Driver क्रम ETAS GmbH ES58X USB CAN(-FD) Bus Interfaces.
 *
 * File es58x_fd.c: Adds support to ETAS ES582.1 and ES584.1 (naming
 * convention: we use the term "ES58X FD" when referring to those two
 * variants together).
 *
 * Copyright (c) 2019 Robert Bosch Engineering and Business Solutions. All rights reserved.
 * Copyright (c) 2020 ETAS K.K.. All rights reserved.
 * Copyright (c) 2020, 2021 Vincent Mailhol <mailhol.vincent@wanaकरोo.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "es58x_core.h"
#समावेश "es58x_fd.h"

/**
 * es58x_fd_माप_rx_tx_msg() - Calculate the actual length of the
 *	काष्ठाure of a rx or tx message.
 * @msg: message of variable length, must have a dlc and a len fields.
 *
 * Even अगर RTR frames have actually no payload, the ES58X devices
 * still expect it. Must be a macro in order to accept several types
 * (काष्ठा es58x_fd_tx_can_msg and काष्ठा es58x_fd_rx_can_msg) as an
 * input.
 *
 * Return: length of the message.
 */
#घोषणा es58x_fd_माप_rx_tx_msg(msg)					\
(अणु									\
	typeof(msg) __msg = (msg);					\
	माप_प्रकार __msg_len;						\
									\
	अगर (__msg.flags & ES58X_FLAG_FD_DATA)				\
		__msg_len = canfd_sanitize_len(__msg.len);		\
	अन्यथा								\
		__msg_len = can_cc_dlc2len(__msg.dlc);			\
									\
	दुरत्व(typeof(__msg), data[__msg_len]);			\
पूर्ण)

अटल क्रमागत es58x_fd_cmd_type es58x_fd_cmd_type(काष्ठा net_device *netdev)
अणु
	u32 ctrlmode = es58x_priv(netdev)->can.ctrlmode;

	अगर (ctrlmode & (CAN_CTRLMODE_FD | CAN_CTRLMODE_FD_NON_ISO))
		वापस ES58X_FD_CMD_TYPE_CANFD;
	अन्यथा
		वापस ES58X_FD_CMD_TYPE_CAN;
पूर्ण

अटल u16 es58x_fd_get_msg_len(स्थिर जोड़ es58x_urb_cmd *urb_cmd)
अणु
	वापस get_unaligned_le16(&urb_cmd->es58x_fd_urb_cmd.msg_len);
पूर्ण

अटल पूर्णांक es58x_fd_echo_msg(काष्ठा net_device *netdev,
			     स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd)
अणु
	काष्ठा es58x_priv *priv = es58x_priv(netdev);
	स्थिर काष्ठा es58x_fd_echo_msg *echo_msg;
	काष्ठा es58x_device *es58x_dev = priv->es58x_dev;
	u64 *tstamps = es58x_dev->बारtamps;
	u16 msg_len = get_unaligned_le16(&es58x_fd_urb_cmd->msg_len);
	पूर्णांक i, num_element;
	u32 rcv_packet_idx;

	स्थिर u32 mask = GENMASK(31, माप(echo_msg->packet_idx) * 8);

	num_element = es58x_msg_num_element(es58x_dev->dev,
					    es58x_fd_urb_cmd->echo_msg,
					    msg_len);
	अगर (num_element < 0)
		वापस num_element;
	echo_msg = es58x_fd_urb_cmd->echo_msg;

	rcv_packet_idx = (priv->tx_tail & mask) | echo_msg[0].packet_idx;
	क्रम (i = 0; i < num_element; i++) अणु
		अगर ((u8)rcv_packet_idx != echo_msg[i].packet_idx) अणु
			netdev_err(netdev, "Packet idx jumped from %u to %u\n",
				   (u8)rcv_packet_idx - 1,
				   echo_msg[i].packet_idx);
			वापस -EBADMSG;
		पूर्ण

		tstamps[i] = get_unaligned_le64(&echo_msg[i].बारtamp);
		rcv_packet_idx++;
	पूर्ण

	वापस es58x_can_get_echo_skb(netdev, priv->tx_tail, tstamps, num_element);
पूर्ण

अटल पूर्णांक es58x_fd_rx_can_msg(काष्ठा net_device *netdev,
			       स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd)
अणु
	काष्ठा es58x_device *es58x_dev = es58x_priv(netdev)->es58x_dev;
	स्थिर u8 *rx_can_msg_buf = es58x_fd_urb_cmd->rx_can_msg_buf;
	u16 rx_can_msg_buf_len = get_unaligned_le16(&es58x_fd_urb_cmd->msg_len);
	पूर्णांक pkts, ret;

	ret = es58x_check_msg_max_len(es58x_dev->dev,
				      es58x_fd_urb_cmd->rx_can_msg_buf,
				      rx_can_msg_buf_len);
	अगर (ret)
		वापस ret;

	क्रम (pkts = 0; rx_can_msg_buf_len > 0; pkts++) अणु
		स्थिर काष्ठा es58x_fd_rx_can_msg *rx_can_msg =
		    (स्थिर काष्ठा es58x_fd_rx_can_msg *)rx_can_msg_buf;
		bool is_can_fd = !!(rx_can_msg->flags & ES58X_FLAG_FD_DATA);
		/* rx_can_msg_len is the length of the rx_can_msg
		 * buffer. Not to be confused with rx_can_msg->len
		 * which is the length of the CAN payload
		 * rx_can_msg->data.
		 */
		u16 rx_can_msg_len = es58x_fd_माप_rx_tx_msg(*rx_can_msg);

		अगर (rx_can_msg_len > rx_can_msg_buf_len) अणु
			netdev_err(netdev,
				   "%s: Expected a rx_can_msg of size %d but only %d bytes are left in rx_can_msg_buf\n",
				   __func__,
				   rx_can_msg_len, rx_can_msg_buf_len);
			वापस -EMSGSIZE;
		पूर्ण
		अगर (rx_can_msg->len > CANFD_MAX_DLEN) अणु
			netdev_err(netdev,
				   "%s: Data length is %d but maximum should be %d\n",
				   __func__, rx_can_msg->len, CANFD_MAX_DLEN);
			वापस -EMSGSIZE;
		पूर्ण

		अगर (netअगर_running(netdev)) अणु
			u64 tstamp = get_unaligned_le64(&rx_can_msg->बारtamp);
			canid_t can_id = get_unaligned_le32(&rx_can_msg->can_id);
			u8 dlc;

			अगर (is_can_fd)
				dlc = can_fd_len2dlc(rx_can_msg->len);
			अन्यथा
				dlc = rx_can_msg->dlc;

			ret = es58x_rx_can_msg(netdev, tstamp, rx_can_msg->data,
					       can_id, rx_can_msg->flags, dlc);
			अगर (ret)
				अवरोध;
		पूर्ण

		rx_can_msg_buf_len -= rx_can_msg_len;
		rx_can_msg_buf += rx_can_msg_len;
	पूर्ण

	अगर (!netअगर_running(netdev)) अणु
		अगर (net_ratelimit())
			netdev_info(netdev,
				    "%s: %s is down, dropping %d rx packets\n",
				    __func__, netdev->name, pkts);
		netdev->stats.rx_dropped += pkts;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक es58x_fd_rx_event_msg(काष्ठा net_device *netdev,
				 स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd)
अणु
	काष्ठा es58x_device *es58x_dev = es58x_priv(netdev)->es58x_dev;
	u16 msg_len = get_unaligned_le16(&es58x_fd_urb_cmd->msg_len);
	स्थिर काष्ठा es58x_fd_rx_event_msg *rx_event_msg;
	पूर्णांक ret;

	ret = es58x_check_msg_len(es58x_dev->dev, *rx_event_msg, msg_len);
	अगर (ret)
		वापस ret;

	rx_event_msg = &es58x_fd_urb_cmd->rx_event_msg;

	वापस es58x_rx_err_msg(netdev, rx_event_msg->error_code,
				rx_event_msg->event_code,
				get_unaligned_le64(&rx_event_msg->बारtamp));
पूर्ण

अटल पूर्णांक es58x_fd_rx_cmd_ret_u32(काष्ठा net_device *netdev,
				   स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd,
				   क्रमागत es58x_ret_type cmd_ret_type)
अणु
	काष्ठा es58x_device *es58x_dev = es58x_priv(netdev)->es58x_dev;
	u16 msg_len = get_unaligned_le16(&es58x_fd_urb_cmd->msg_len);
	पूर्णांक ret;

	ret = es58x_check_msg_len(es58x_dev->dev,
				  es58x_fd_urb_cmd->rx_cmd_ret_le32, msg_len);
	अगर (ret)
		वापस ret;

	वापस es58x_rx_cmd_ret_u32(netdev, cmd_ret_type,
				    get_unaligned_le32(&es58x_fd_urb_cmd->rx_cmd_ret_le32));
पूर्ण

अटल पूर्णांक es58x_fd_tx_ack_msg(काष्ठा net_device *netdev,
			       स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd)
अणु
	काष्ठा es58x_device *es58x_dev = es58x_priv(netdev)->es58x_dev;
	स्थिर काष्ठा es58x_fd_tx_ack_msg *tx_ack_msg;
	u16 msg_len = get_unaligned_le16(&es58x_fd_urb_cmd->msg_len);
	पूर्णांक ret;

	tx_ack_msg = &es58x_fd_urb_cmd->tx_ack_msg;
	ret = es58x_check_msg_len(es58x_dev->dev, *tx_ack_msg, msg_len);
	अगर (ret)
		वापस ret;

	वापस es58x_tx_ack_msg(netdev,
				get_unaligned_le16(&tx_ack_msg->tx_मुक्त_entries),
				get_unaligned_le32(&tx_ack_msg->rx_cmd_ret_le32));
पूर्ण

अटल पूर्णांक es58x_fd_can_cmd_id(काष्ठा es58x_device *es58x_dev,
			       स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd)
अणु
	काष्ठा net_device *netdev;
	पूर्णांक ret;

	ret = es58x_get_netdev(es58x_dev, es58x_fd_urb_cmd->channel_idx,
			       ES58X_FD_CHANNEL_IDX_OFFSET, &netdev);
	अगर (ret)
		वापस ret;

	चयन ((क्रमागत es58x_fd_can_cmd_id)es58x_fd_urb_cmd->cmd_id) अणु
	हाल ES58X_FD_CAN_CMD_ID_ENABLE_CHANNEL:
		वापस es58x_fd_rx_cmd_ret_u32(netdev, es58x_fd_urb_cmd,
					       ES58X_RET_TYPE_ENABLE_CHANNEL);

	हाल ES58X_FD_CAN_CMD_ID_DISABLE_CHANNEL:
		वापस es58x_fd_rx_cmd_ret_u32(netdev, es58x_fd_urb_cmd,
					       ES58X_RET_TYPE_DISABLE_CHANNEL);

	हाल ES58X_FD_CAN_CMD_ID_TX_MSG:
		वापस es58x_fd_tx_ack_msg(netdev, es58x_fd_urb_cmd);

	हाल ES58X_FD_CAN_CMD_ID_ECHO_MSG:
		वापस es58x_fd_echo_msg(netdev, es58x_fd_urb_cmd);

	हाल ES58X_FD_CAN_CMD_ID_RX_MSG:
		वापस es58x_fd_rx_can_msg(netdev, es58x_fd_urb_cmd);

	हाल ES58X_FD_CAN_CMD_ID_RESET_RX:
		वापस es58x_fd_rx_cmd_ret_u32(netdev, es58x_fd_urb_cmd,
					       ES58X_RET_TYPE_RESET_RX);

	हाल ES58X_FD_CAN_CMD_ID_RESET_TX:
		वापस es58x_fd_rx_cmd_ret_u32(netdev, es58x_fd_urb_cmd,
					       ES58X_RET_TYPE_RESET_TX);

	हाल ES58X_FD_CAN_CMD_ID_ERROR_OR_EVENT_MSG:
		वापस es58x_fd_rx_event_msg(netdev, es58x_fd_urb_cmd);

	शेष:
		वापस -EBADRQC;
	पूर्ण
पूर्ण

अटल पूर्णांक es58x_fd_device_cmd_id(काष्ठा es58x_device *es58x_dev,
				  स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd)
अणु
	u16 msg_len = get_unaligned_le16(&es58x_fd_urb_cmd->msg_len);
	पूर्णांक ret;

	चयन ((क्रमागत es58x_fd_dev_cmd_id)es58x_fd_urb_cmd->cmd_id) अणु
	हाल ES58X_FD_DEV_CMD_ID_TIMESTAMP:
		ret = es58x_check_msg_len(es58x_dev->dev,
					  es58x_fd_urb_cmd->बारtamp, msg_len);
		अगर (ret)
			वापस ret;
		es58x_rx_बारtamp(es58x_dev,
				   get_unaligned_le64(&es58x_fd_urb_cmd->बारtamp));
		वापस 0;

	शेष:
		वापस -EBADRQC;
	पूर्ण
पूर्ण

अटल पूर्णांक es58x_fd_handle_urb_cmd(काष्ठा es58x_device *es58x_dev,
				   स्थिर जोड़ es58x_urb_cmd *urb_cmd)
अणु
	स्थिर काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd;
	पूर्णांक ret;

	es58x_fd_urb_cmd = &urb_cmd->es58x_fd_urb_cmd;

	चयन ((क्रमागत es58x_fd_cmd_type)es58x_fd_urb_cmd->cmd_type) अणु
	हाल ES58X_FD_CMD_TYPE_CAN:
	हाल ES58X_FD_CMD_TYPE_CANFD:
		ret = es58x_fd_can_cmd_id(es58x_dev, es58x_fd_urb_cmd);
		अवरोध;

	हाल ES58X_FD_CMD_TYPE_DEVICE:
		ret = es58x_fd_device_cmd_id(es58x_dev, es58x_fd_urb_cmd);
		अवरोध;

	शेष:
		ret = -EBADRQC;
		अवरोध;
	पूर्ण

	अगर (ret == -EBADRQC)
		dev_err(es58x_dev->dev,
			"%s: Unknown command type (0x%02X) and command ID (0x%02X) combination\n",
			__func__, es58x_fd_urb_cmd->cmd_type,
			es58x_fd_urb_cmd->cmd_id);

	वापस ret;
पूर्ण

अटल व्योम es58x_fd_fill_urb_header(जोड़ es58x_urb_cmd *urb_cmd, u8 cmd_type,
				     u8 cmd_id, u8 channel_idx, u16 msg_len)
अणु
	काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd = &urb_cmd->es58x_fd_urb_cmd;

	es58x_fd_urb_cmd->SOF = cpu_to_le16(es58x_fd_param.tx_start_of_frame);
	es58x_fd_urb_cmd->cmd_type = cmd_type;
	es58x_fd_urb_cmd->cmd_id = cmd_id;
	es58x_fd_urb_cmd->channel_idx = channel_idx;
	es58x_fd_urb_cmd->msg_len = cpu_to_le16(msg_len);
पूर्ण

अटल पूर्णांक es58x_fd_tx_can_msg(काष्ठा es58x_priv *priv,
			       स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा es58x_device *es58x_dev = priv->es58x_dev;
	जोड़ es58x_urb_cmd *urb_cmd = priv->tx_urb->transfer_buffer;
	काष्ठा es58x_fd_urb_cmd *es58x_fd_urb_cmd = &urb_cmd->es58x_fd_urb_cmd;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	काष्ठा es58x_fd_tx_can_msg *tx_can_msg;
	bool is_fd = can_is_canfd_skb(skb);
	u16 msg_len;
	पूर्णांक ret;

	अगर (priv->tx_can_msg_cnt == 0) अणु
		msg_len = 0;
		es58x_fd_fill_urb_header(urb_cmd,
					 is_fd ? ES58X_FD_CMD_TYPE_CANFD
					       : ES58X_FD_CMD_TYPE_CAN,
					 ES58X_FD_CAN_CMD_ID_TX_MSG_NO_ACK,
					 priv->channel_idx, msg_len);
	पूर्ण अन्यथा अणु
		msg_len = es58x_fd_get_msg_len(urb_cmd);
	पूर्ण

	ret = es58x_check_msg_max_len(es58x_dev->dev,
				      es58x_fd_urb_cmd->tx_can_msg_buf,
				      msg_len + माप(*tx_can_msg));
	अगर (ret)
		वापस ret;

	/* Fill message contents. */
	tx_can_msg = (काष्ठा es58x_fd_tx_can_msg *)
	    &es58x_fd_urb_cmd->tx_can_msg_buf[msg_len];
	tx_can_msg->packet_idx = (u8)priv->tx_head;
	put_unaligned_le32(es58x_get_raw_can_id(cf), &tx_can_msg->can_id);
	tx_can_msg->flags = (u8)es58x_get_flags(skb);
	अगर (is_fd)
		tx_can_msg->len = cf->len;
	अन्यथा
		tx_can_msg->dlc = can_get_cc_dlc(cf, priv->can.ctrlmode);
	स_नकल(tx_can_msg->data, cf->data, cf->len);

	/* Calculate new sizes */
	msg_len += es58x_fd_माप_rx_tx_msg(*tx_can_msg);
	priv->tx_urb->transfer_buffer_length = es58x_get_urb_cmd_len(es58x_dev,
								     msg_len);
	put_unaligned_le16(msg_len, &es58x_fd_urb_cmd->msg_len);

	वापस 0;
पूर्ण

अटल व्योम es58x_fd_convert_bittiming(काष्ठा es58x_fd_bittiming *es58x_fd_bt,
				       काष्ठा can_bittiming *bt)
अणु
	/* The actual value set in the hardware रेजिस्टरs is one less
	 * than the functional value.
	 */
	स्थिर पूर्णांक offset = 1;

	es58x_fd_bt->bitrate = cpu_to_le32(bt->bitrate);
	es58x_fd_bt->tseg1 =
	    cpu_to_le16(bt->prop_seg + bt->phase_seg1 - offset);
	es58x_fd_bt->tseg2 = cpu_to_le16(bt->phase_seg2 - offset);
	es58x_fd_bt->brp = cpu_to_le16(bt->brp - offset);
	es58x_fd_bt->sjw = cpu_to_le16(bt->sjw - offset);
पूर्ण

अटल पूर्णांक es58x_fd_enable_channel(काष्ठा es58x_priv *priv)
अणु
	काष्ठा es58x_device *es58x_dev = priv->es58x_dev;
	काष्ठा net_device *netdev = es58x_dev->netdev[priv->channel_idx];
	काष्ठा es58x_fd_tx_conf_msg tx_conf_msg = अणु 0 पूर्ण;
	u32 ctrlmode;
	माप_प्रकार conf_len = 0;

	es58x_fd_convert_bittiming(&tx_conf_msg.nominal_bittiming,
				   &priv->can.bittiming);
	ctrlmode = priv->can.ctrlmode;

	अगर (ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		tx_conf_msg.samples_per_bit = ES58X_SAMPLES_PER_BIT_THREE;
	अन्यथा
		tx_conf_msg.samples_per_bit = ES58X_SAMPLES_PER_BIT_ONE;
	tx_conf_msg.sync_edge = ES58X_SYNC_EDGE_SINGLE;
	tx_conf_msg.physical_layer = ES58X_PHYSICAL_LAYER_HIGH_SPEED;
	tx_conf_msg.echo_mode = ES58X_ECHO_ON;
	अगर (ctrlmode & CAN_CTRLMODE_LISTENONLY)
		tx_conf_msg.ctrlmode |= ES58X_FD_CTRLMODE_PASSIVE;
	अन्यथा
		tx_conf_msg.ctrlmode |=  ES58X_FD_CTRLMODE_ACTIVE;

	अगर (ctrlmode & CAN_CTRLMODE_FD_NON_ISO) अणु
		tx_conf_msg.ctrlmode |= ES58X_FD_CTRLMODE_FD_NON_ISO;
		tx_conf_msg.canfd_enabled = 1;
	पूर्ण अन्यथा अगर (ctrlmode & CAN_CTRLMODE_FD) अणु
		tx_conf_msg.ctrlmode |= ES58X_FD_CTRLMODE_FD;
		tx_conf_msg.canfd_enabled = 1;
	पूर्ण

	अगर (tx_conf_msg.canfd_enabled) अणु
		es58x_fd_convert_bittiming(&tx_conf_msg.data_bittiming,
					   &priv->can.data_bittiming);

		अगर (priv->can.tdc.tdco) अणु
			tx_conf_msg.tdc_enabled = 1;
			tx_conf_msg.tdco = cpu_to_le16(priv->can.tdc.tdco);
			tx_conf_msg.tdcf = cpu_to_le16(priv->can.tdc.tdcf);
		पूर्ण

		conf_len = ES58X_FD_CANFD_CONF_LEN;
	पूर्ण अन्यथा अणु
		conf_len = ES58X_FD_CAN_CONF_LEN;
	पूर्ण

	वापस es58x_send_msg(es58x_dev, es58x_fd_cmd_type(netdev),
			      ES58X_FD_CAN_CMD_ID_ENABLE_CHANNEL,
			      &tx_conf_msg, conf_len, priv->channel_idx);
पूर्ण

अटल पूर्णांक es58x_fd_disable_channel(काष्ठा es58x_priv *priv)
अणु
	/* The type (ES58X_FD_CMD_TYPE_CAN or ES58X_FD_CMD_TYPE_CANFD) करोes
	 * not matter here.
	 */
	वापस es58x_send_msg(priv->es58x_dev, ES58X_FD_CMD_TYPE_CAN,
			      ES58X_FD_CAN_CMD_ID_DISABLE_CHANNEL,
			      ES58X_EMPTY_MSG, 0, priv->channel_idx);
पूर्ण

अटल पूर्णांक es58x_fd_get_बारtamp(काष्ठा es58x_device *es58x_dev)
अणु
	वापस es58x_send_msg(es58x_dev, ES58X_FD_CMD_TYPE_DEVICE,
			      ES58X_FD_DEV_CMD_ID_TIMESTAMP, ES58X_EMPTY_MSG,
			      0, ES58X_CHANNEL_IDX_NA);
पूर्ण

/* Nominal bittiming स्थिरants क्रम ES582.1 and ES584.1 as specअगरied in
 * the microcontroller datasheet: "SAM E701/S70/V70/V71 Family"
 * section 49.6.8 "MCAN Nominal Bit Timing and Prescaler Register"
 * from Microchip.
 *
 * The values from the specअगरication are the hardware रेजिस्टर
 * values. To convert them to the functional values, all ranges were
 * incremented by 1 (e.g. range [0..n-1] changed to [1..n]).
 */
अटल स्थिर काष्ठा can_bittiming_स्थिर es58x_fd_nom_bittiming_स्थिर = अणु
	.name = "ES582.1/ES584.1",
	.tseg1_min = 2,
	.tseg1_max = 256,
	.tseg2_min = 2,
	.tseg2_max = 128,
	.sjw_max = 128,
	.brp_min = 1,
	.brp_max = 512,
	.brp_inc = 1
पूर्ण;

/* Data bittiming स्थिरants क्रम ES582.1 and ES584.1 as specअगरied in
 * the microcontroller datasheet: "SAM E701/S70/V70/V71 Family"
 * section 49.6.4 "MCAN Data Bit Timing and Prescaler Register" from
 * Microchip.
 */
अटल स्थिर काष्ठा can_bittiming_स्थिर es58x_fd_data_bittiming_स्थिर = अणु
	.name = "ES582.1/ES584.1",
	.tseg1_min = 2,
	.tseg1_max = 32,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 8,
	.brp_min = 1,
	.brp_max = 32,
	.brp_inc = 1
पूर्ण;

/* Transmission Delay Compensation स्थिरants क्रम ES582.1 and ES584.1
 * as specअगरied in the microcontroller datasheet: "SAM
 * E701/S70/V70/V71 Family" section 49.6.15 "MCAN Transmitter Delay
 * Compensation Register" from Microchip.
 */
अटल स्थिर काष्ठा can_tdc_स्थिर es58x_tdc_स्थिर = अणु
	.tdcv_max = 0, /* Manual mode not supported. */
	.tdco_max = 127,
	.tdcf_max = 127
पूर्ण;

स्थिर काष्ठा es58x_parameters es58x_fd_param = अणु
	.bittiming_स्थिर = &es58x_fd_nom_bittiming_स्थिर,
	.data_bittiming_स्थिर = &es58x_fd_data_bittiming_स्थिर,
	.tdc_स्थिर = &es58x_tdc_स्थिर,
	/* The devices use NXP TJA1044G transievers which guarantee
	 * the timing क्रम data rates up to 5 Mbps. Bitrates up to 8
	 * Mbps work in an optimal environment but are not recommended
	 * क्रम production environment.
	 */
	.bitrate_max = 8 * CAN_MBPS,
	.घड़ी = अणु.freq = 80 * CAN_MHZपूर्ण,
	.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK | CAN_CTRLMODE_LISTENONLY |
	    CAN_CTRLMODE_3_SAMPLES | CAN_CTRLMODE_FD | CAN_CTRLMODE_FD_NON_ISO |
	    CAN_CTRLMODE_CC_LEN8_DLC,
	.tx_start_of_frame = 0xCEFA,	/* FACE in little endian */
	.rx_start_of_frame = 0xFECA,	/* CAFE in little endian */
	.tx_urb_cmd_max_len = ES58X_FD_TX_URB_CMD_MAX_LEN,
	.rx_urb_cmd_max_len = ES58X_FD_RX_URB_CMD_MAX_LEN,
	/* Size of पूर्णांकernal device TX queue is 500.
	 *
	 * However, when reaching value around 278, the device's busy
	 * LED turns on and thus maximum value of 500 is never reached
	 * in practice. Also, when this value is too high, some error
	 * on the echo_msg were witnessed when the device is
	 * recovering from bus off.
	 *
	 * For above reasons, a value that would prevent the device
	 * from becoming busy was chosen. In practice, BQL would
	 * prevent the value from even getting बंदr to below
	 * maximum, so no impact on perक्रमmance was measured.
	 */
	.fअगरo_mask = 255, /* echo_skb_max = 256 */
	.dql_min_limit = CAN_FRAME_LEN_MAX * 15, /* Empirical value. */
	.tx_bulk_max = ES58X_FD_TX_BULK_MAX,
	.urb_cmd_header_len = ES58X_FD_URB_CMD_HEADER_LEN,
	.rx_urb_max = ES58X_RX_URBS_MAX,
	.tx_urb_max = ES58X_TX_URBS_MAX
पूर्ण;

स्थिर काष्ठा es58x_चालकs es58x_fd_ops = अणु
	.get_msg_len = es58x_fd_get_msg_len,
	.handle_urb_cmd = es58x_fd_handle_urb_cmd,
	.fill_urb_header = es58x_fd_fill_urb_header,
	.tx_can_msg = es58x_fd_tx_can_msg,
	.enable_channel = es58x_fd_enable_channel,
	.disable_channel = es58x_fd_disable_channel,
	.reset_device = शून्य, /* Not implemented in the device firmware. */
	.get_बारtamp = es58x_fd_get_बारtamp
पूर्ण;
