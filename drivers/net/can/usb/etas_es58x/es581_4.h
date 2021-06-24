<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Driver क्रम ETAS GmbH ES58X USB CAN(-FD) Bus Interfaces.
 *
 * File es581_4.h: Definitions and declarations specअगरic to ETAS
 * ES581.4.
 *
 * Copyright (c) 2019 Robert Bosch Engineering and Business Solutions. All rights reserved.
 * Copyright (c) 2020 ETAS K.K.. All rights reserved.
 * Copyright (c) 2020, 2021 Vincent Mailhol <mailhol.vincent@wanaकरोo.fr>
 */

#अगर_अघोषित __ES581_4_H__
#घोषणा __ES581_4_H__

#समावेश <linux/types.h>

#घोषणा ES581_4_NUM_CAN_CH 2
#घोषणा ES581_4_CHANNEL_IDX_OFFSET 1

#घोषणा ES581_4_TX_BULK_MAX 25
#घोषणा ES581_4_RX_BULK_MAX 30
#घोषणा ES581_4_ECHO_BULK_MAX 30

क्रमागत es581_4_cmd_type अणु
	ES581_4_CAN_COMMAND_TYPE = 0x45
पूर्ण;

क्रमागत es581_4_cmd_id अणु
	ES581_4_CMD_ID_OPEN_CHANNEL = 0x01,
	ES581_4_CMD_ID_CLOSE_CHANNEL = 0x02,
	ES581_4_CMD_ID_SET_BITTIMING = 0x03,
	ES581_4_CMD_ID_ENABLE_CHANNEL = 0x04,
	ES581_4_CMD_ID_TX_MSG = 0x05,
	ES581_4_CMD_ID_RX_MSG = 0x06,
	ES581_4_CMD_ID_RESET_RX = 0x0A,
	ES581_4_CMD_ID_RESET_TX = 0x0B,
	ES581_4_CMD_ID_DISABLE_CHANNEL = 0x0C,
	ES581_4_CMD_ID_TIMESTAMP = 0x0E,
	ES581_4_CMD_ID_RESET_DEVICE = 0x28,
	ES581_4_CMD_ID_ECHO = 0x71,
	ES581_4_CMD_ID_DEVICE_ERR = 0x72
पूर्ण;

क्रमागत es581_4_rx_type अणु
	ES581_4_RX_TYPE_MESSAGE = 1,
	ES581_4_RX_TYPE_ERROR = 3,
	ES581_4_RX_TYPE_EVENT = 4
पूर्ण;

/**
 * काष्ठा es581_4_tx_conf_msg - Channel configuration.
 * @bitrate: Bitrate.
 * @sample_poपूर्णांक: Sample poपूर्णांक is in percent [0..100].
 * @samples_per_bit: type क्रमागत es58x_samples_per_bit.
 * @bit_समय: Number of समय quanta in one bit.
 * @sjw: Synchronization Jump Width.
 * @sync_edge: type क्रमागत es58x_sync_edge.
 * @physical_layer: type क्रमागत es58x_physical_layer.
 * @echo_mode: type क्रमागत es58x_echo_mode.
 * @channel_no: Channel number, starting from 1. Not to be confused
 *	with channed_idx of the ES58X FD which starts from 0.
 */
काष्ठा es581_4_tx_conf_msg अणु
	__le32 bitrate;
	__le32 sample_poपूर्णांक;
	__le32 samples_per_bit;
	__le32 bit_समय;
	__le32 sjw;
	__le32 sync_edge;
	__le32 physical_layer;
	__le32 echo_mode;
	u8 channel_no;
पूर्ण __packed;

काष्ठा es581_4_tx_can_msg अणु
	__le32 can_id;
	__le32 packet_idx;
	__le16 flags;
	u8 channel_no;
	u8 dlc;
	u8 data[CAN_MAX_DLEN];
पूर्ण __packed;

/* The ES581.4 allows bulk transfer.  */
काष्ठा es581_4_bulk_tx_can_msg अणु
	u8 num_can_msg;
	/* Using type "u8[]" instead of "struct es581_4_tx_can_msg[]"
	 * क्रम tx_msg_buf because each member has a flexible size.
	 */
	u8 tx_can_msg_buf[ES581_4_TX_BULK_MAX *
			  माप(काष्ठा es581_4_tx_can_msg)];
पूर्ण __packed;

काष्ठा es581_4_echo_msg अणु
	__le64 बारtamp;
	__le32 packet_idx;
पूर्ण __packed;

काष्ठा es581_4_bulk_echo_msg अणु
	u8 channel_no;
	काष्ठा es581_4_echo_msg echo_msg[ES581_4_ECHO_BULK_MAX];
पूर्ण __packed;

/* Normal Rx CAN Message */
काष्ठा es581_4_rx_can_msg अणु
	__le64 बारtamp;
	u8 rx_type;		/* type क्रमागत es581_4_rx_type */
	u8 flags;		/* type क्रमागत es58x_flag */
	u8 channel_no;
	u8 dlc;
	__le32 can_id;
	u8 data[CAN_MAX_DLEN];
पूर्ण __packed;

काष्ठा es581_4_rx_err_msg अणु
	__le64 बारtamp;
	__le16 rx_type;		/* type क्रमागत es581_4_rx_type */
	__le16 flags;		/* type क्रमागत es58x_flag */
	u8 channel_no;
	u8 __padding[2];
	u8 dlc;
	__le32 tag;		/* Related to the CAN filtering. Unused in this module */
	__le32 can_id;
	__le32 error;		/* type क्रमागत es58x_error */
	__le32 destination;	/* Unused in this module */
पूर्ण __packed;

काष्ठा es581_4_rx_event_msg अणु
	__le64 बारtamp;
	__le16 rx_type;		/* type क्रमागत es581_4_rx_type */
	u8 channel_no;
	u8 __padding;
	__le32 tag;		/* Related to the CAN filtering. Unused in this module */
	__le32 event;		/* type क्रमागत es58x_event */
	__le32 destination;	/* Unused in this module */
पूर्ण __packed;

काष्ठा es581_4_tx_ack_msg अणु
	__le16 tx_मुक्त_entries;	/* Number of reमुख्यing मुक्त entries in the device TX queue */
	u8 channel_no;
	u8 rx_cmd_ret_u8;	/* type क्रमागत es58x_cmd_ret_code_u8 */
पूर्ण __packed;

काष्ठा es581_4_rx_cmd_ret अणु
	__le32 rx_cmd_ret_le32;
	u8 channel_no;
	u8 __padding[3];
पूर्ण __packed;

/**
 * काष्ठा es581_4_urb_cmd - Commands received from or sent to the
 *	ES581.4 device.
 * @SOF: Start of Frame.
 * @cmd_type: Command Type (type: क्रमागत es581_4_cmd_type). The CRC
 *	calculation starts at this position.
 * @cmd_id: Command ID (type: क्रमागत es581_4_cmd_id).
 * @msg_len: Length of the message, excluding CRC (i.e. length of the
 *	जोड़).
 * @tx_conf_msg: Channel configuration.
 * @bulk_tx_can_msg: Tx messages.
 * @rx_can_msg: Array of Rx messages.
 * @bulk_echo_msg: Tx message being looped back.
 * @rx_err_msg: Error message.
 * @rx_event_msg: Event message.
 * @tx_ack_msg: Tx acknowledgment message.
 * @rx_cmd_ret: Command वापस code.
 * @बारtamp: Timestamp reply.
 * @rx_cmd_ret_u8: Rx 8 bits वापस code (type: क्रमागत
 *	es58x_cmd_ret_code_u8).
 * @raw_msg: Message raw payload.
 * @reserved_क्रम_crc16_करो_not_use: The काष्ठाure ends with a
 *	CRC16. Because the काष्ठाures in above जोड़ are of variable
 *	lengths, we can not predict the offset of the CRC in
 *	advance. Use functions es58x_get_crc() and es58x_set_crc() to
 *	manipulate it.
 */
काष्ठा es581_4_urb_cmd अणु
	__le16 SOF;
	u8 cmd_type;
	u8 cmd_id;
	__le16 msg_len;

	जोड़ अणु
		काष्ठा es581_4_tx_conf_msg tx_conf_msg;
		काष्ठा es581_4_bulk_tx_can_msg bulk_tx_can_msg;
		काष्ठा es581_4_rx_can_msg rx_can_msg[ES581_4_RX_BULK_MAX];
		काष्ठा es581_4_bulk_echo_msg bulk_echo_msg;
		काष्ठा es581_4_rx_err_msg rx_err_msg;
		काष्ठा es581_4_rx_event_msg rx_event_msg;
		काष्ठा es581_4_tx_ack_msg tx_ack_msg;
		काष्ठा es581_4_rx_cmd_ret rx_cmd_ret;
		__le64 बारtamp;
		u8 rx_cmd_ret_u8;
		u8 raw_msg[0];
	पूर्ण __packed;

	__le16 reserved_क्रम_crc16_करो_not_use;
पूर्ण __packed;

#घोषणा ES581_4_URB_CMD_HEADER_LEN (दुरत्व(काष्ठा es581_4_urb_cmd, raw_msg))
#घोषणा ES581_4_TX_URB_CMD_MAX_LEN					\
	ES58X_SIZखातापूर्ण_URB_CMD(काष्ठा es581_4_urb_cmd, bulk_tx_can_msg)
#घोषणा ES581_4_RX_URB_CMD_MAX_LEN					\
	ES58X_SIZखातापूर्ण_URB_CMD(काष्ठा es581_4_urb_cmd, rx_can_msg)

#पूर्ण_अगर /* __ES581_4_H__ */
