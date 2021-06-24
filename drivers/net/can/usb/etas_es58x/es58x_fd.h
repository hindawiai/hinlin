<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Driver क्रम ETAS GmbH ES58X USB CAN(-FD) Bus Interfaces.
 *
 * File es58x_fd.h: Definitions and declarations specअगरic to ETAS
 * ES582.1 and ES584.1 (naming convention: we use the term "ES58X FD"
 * when referring to those two variants together).
 *
 * Copyright (c) 2019 Robert Bosch Engineering and Business Solutions. All rights reserved.
 * Copyright (c) 2020 ETAS K.K.. All rights reserved.
 * Copyright (c) 2020, 2021 Vincent Mailhol <mailhol.vincent@wanaकरोo.fr>
 */

#अगर_अघोषित __ES58X_FD_H__
#घोषणा __ES58X_FD_H__

#समावेश <linux/types.h>

#घोषणा ES582_1_NUM_CAN_CH 2
#घोषणा ES584_1_NUM_CAN_CH 1
#घोषणा ES58X_FD_NUM_CAN_CH 2
#घोषणा ES58X_FD_CHANNEL_IDX_OFFSET 0

#घोषणा ES58X_FD_TX_BULK_MAX 100
#घोषणा ES58X_FD_RX_BULK_MAX 100
#घोषणा ES58X_FD_ECHO_BULK_MAX 100

क्रमागत es58x_fd_cmd_type अणु
	ES58X_FD_CMD_TYPE_CAN = 0x03,
	ES58X_FD_CMD_TYPE_CANFD = 0x04,
	ES58X_FD_CMD_TYPE_DEVICE = 0xFF
पूर्ण;

/* Command IDs क्रम ES58X_FD_CMD_TYPE_अणुCAN,CANFDपूर्ण. */
क्रमागत es58x_fd_can_cmd_id अणु
	ES58X_FD_CAN_CMD_ID_ENABLE_CHANNEL = 0x01,
	ES58X_FD_CAN_CMD_ID_DISABLE_CHANNEL = 0x02,
	ES58X_FD_CAN_CMD_ID_TX_MSG = 0x05,
	ES58X_FD_CAN_CMD_ID_ECHO_MSG = 0x07,
	ES58X_FD_CAN_CMD_ID_RX_MSG = 0x10,
	ES58X_FD_CAN_CMD_ID_ERROR_OR_EVENT_MSG = 0x11,
	ES58X_FD_CAN_CMD_ID_RESET_RX = 0x20,
	ES58X_FD_CAN_CMD_ID_RESET_TX = 0x21,
	ES58X_FD_CAN_CMD_ID_TX_MSG_NO_ACK = 0x55
पूर्ण;

/* Command IDs क्रम ES58X_FD_CMD_TYPE_DEVICE. */
क्रमागत es58x_fd_dev_cmd_id अणु
	ES58X_FD_DEV_CMD_ID_GETTIMETICKS = 0x01,
	ES58X_FD_DEV_CMD_ID_TIMESTAMP = 0x02
पूर्ण;

/**
 * क्रमागत es58x_fd_ctrlmode - Controller mode.
 * @ES58X_FD_CTRLMODE_ACTIVE: send and receive messages.
 * @ES58X_FD_CTRLMODE_PASSIVE: only receive messages (monitor). Do not
 *	send anything, not even the acknowledgment bit.
 * @ES58X_FD_CTRLMODE_FD: CAN FD according to ISO11898-1.
 * @ES58X_FD_CTRLMODE_FD_NON_ISO: follow Bosch CAN FD Specअगरication
 *	V1.0
 * @ES58X_FD_CTRLMODE_DISABLE_PROTOCOL_EXCEPTION_HANDLING: How to
 *	behave when CAN FD reserved bit is monitored as
 *	करोminant. (c.f. ISO 11898-1:2015, section 10.4.2.4 "Control
 *	field", paragraph "r0 bit"). 0 (not disable = enable): send
 *	error frame. 1 (disable): goes पूर्णांकo bus पूर्णांकegration mode
 *	(c.f. below).
 * @ES58X_FD_CTRLMODE_EDGE_FILTER_DURING_BUS_INTEGRATION: 0: Edge
 *	filtering is disabled. 1: Edge filtering is enabled. Two
 *	consecutive करोminant bits required to detect an edge क्रम hard
 *	synchronization.
 */
क्रमागत es58x_fd_ctrlmode अणु
	ES58X_FD_CTRLMODE_ACTIVE = 0,
	ES58X_FD_CTRLMODE_PASSIVE = BIT(0),
	ES58X_FD_CTRLMODE_FD = BIT(4),
	ES58X_FD_CTRLMODE_FD_NON_ISO = BIT(5),
	ES58X_FD_CTRLMODE_DISABLE_PROTOCOL_EXCEPTION_HANDLING = BIT(6),
	ES58X_FD_CTRLMODE_EDGE_FILTER_DURING_BUS_INTEGRATION = BIT(7)
पूर्ण;

काष्ठा es58x_fd_bittiming अणु
	__le32 bitrate;
	__le16 tseg1;		/* range: [tseg1_min-1..tseg1_max-1] */
	__le16 tseg2;		/* range: [tseg2_min-1..tseg2_max-1] */
	__le16 brp;		/* range: [brp_min-1..brp_max-1] */
	__le16 sjw;		/* range: [0..sjw_max-1] */
पूर्ण __packed;

/**
 * काष्ठा es58x_fd_tx_conf_msg - Channel configuration.
 * @nominal_bittiming: Nominal bittiming.
 * @samples_per_bit: type क्रमागत es58x_samples_per_bit.
 * @sync_edge: type क्रमागत es58x_sync_edge.
 * @physical_layer: type क्रमागत es58x_physical_layer.
 * @echo_mode: type क्रमागत es58x_echo_mode.
 * @ctrlmode: type क्रमागत es58x_fd_ctrlmode.
 * @canfd_enabled: boolean (0: Classical CAN, 1: CAN and/or CANFD).
 * @data_bittiming: Bittiming क्रम flexible data-rate transmission.
 * @tdc_enabled: Transmitter Delay Compensation चयन (0: disabled,
 *	1: enabled). On very high bitrates, the delay between when the
 *	bit is sent and received on the CANTX and CANRX pins of the
 *	transceiver start to be signअगरicant enough क्रम errors to occur
 *	and thus need to be compensated.
 * @tdco: Transmitter Delay Compensation Offset. Offset value, in समय
 *	quanta, defining the delay between the start of the bit
 *	reception on the CANRX pin of the transceiver and the SSP
 *	(Secondary Sample Poपूर्णांक). Valid values: 0 to 127.
 * @tdcf: Transmitter Delay Compensation Filter winकरोw. Defines the
 *	minimum value क्रम the SSP position, in समय quanta. The
 *	feature is enabled when TDCF is configured to a value greater
 *	than TDCO. Valid values: 0 to 127.
 *
 * Please refer to the microcontroller datasheet: "SAM
 * E701/S70/V70/V71 Family" section 49 "Controller Area Network
 * (MCAN)" क्रम additional inक्रमmation.
 */
काष्ठा es58x_fd_tx_conf_msg अणु
	काष्ठा es58x_fd_bittiming nominal_bittiming;
	u8 samples_per_bit;
	u8 sync_edge;
	u8 physical_layer;
	u8 echo_mode;
	u8 ctrlmode;
	u8 canfd_enabled;
	काष्ठा es58x_fd_bittiming data_bittiming;
	u8 tdc_enabled;
	__le16 tdco;
	__le16 tdcf;
पूर्ण __packed;

#घोषणा ES58X_FD_CAN_CONF_LEN					\
	(दुरत्व(काष्ठा es58x_fd_tx_conf_msg, canfd_enabled))
#घोषणा ES58X_FD_CANFD_CONF_LEN (माप(काष्ठा es58x_fd_tx_conf_msg))

काष्ठा es58x_fd_tx_can_msg अणु
	u8 packet_idx;
	__le32 can_id;
	u8 flags;
	जोड़ अणु
		u8 dlc;		/* Only अगर cmd_id is ES58X_FD_CMD_TYPE_CAN */
		u8 len;		/* Only अगर cmd_id is ES58X_FD_CMD_TYPE_CANFD */
	पूर्ण __packed;
	u8 data[CANFD_MAX_DLEN];
पूर्ण __packed;

#घोषणा ES58X_FD_CAN_TX_LEN						\
	(दुरत्व(काष्ठा es58x_fd_tx_can_msg, data[CAN_MAX_DLEN]))
#घोषणा ES58X_FD_CANFD_TX_LEN (माप(काष्ठा es58x_fd_tx_can_msg))

काष्ठा es58x_fd_rx_can_msg अणु
	__le64 बारtamp;
	__le32 can_id;
	u8 flags;
	जोड़ अणु
		u8 dlc;		/* Only अगर cmd_id is ES58X_FD_CMD_TYPE_CAN */
		u8 len;		/* Only अगर cmd_id is ES58X_FD_CMD_TYPE_CANFD */
	पूर्ण __packed;
	u8 data[CANFD_MAX_DLEN];
पूर्ण __packed;

#घोषणा ES58X_FD_CAN_RX_LEN						\
	(दुरत्व(काष्ठा es58x_fd_rx_can_msg, data[CAN_MAX_DLEN]))
#घोषणा ES58X_FD_CANFD_RX_LEN (माप(काष्ठा es58x_fd_rx_can_msg))

काष्ठा es58x_fd_echo_msg अणु
	__le64 बारtamp;
	u8 packet_idx;
पूर्ण __packed;

काष्ठा es58x_fd_rx_event_msg अणु
	__le64 बारtamp;
	__le32 can_id;
	u8 flags;		/* type क्रमागत es58x_flag */
	u8 error_type;		/* 0: event, 1: error */
	u8 error_code;
	u8 event_code;
पूर्ण __packed;

काष्ठा es58x_fd_tx_ack_msg अणु
	__le32 rx_cmd_ret_le32;	/* type क्रमागत es58x_cmd_ret_code_u32 */
	__le16 tx_मुक्त_entries;	/* Number of reमुख्यing मुक्त entries in the device TX queue */
पूर्ण __packed;

/**
 * काष्ठा es58x_fd_urb_cmd - Commands received from or sent to the
 *	ES58X FD device.
 * @SOF: Start of Frame.
 * @cmd_type: Command Type (type: क्रमागत es58x_fd_cmd_type). The CRC
 *	calculation starts at this position.
 * @cmd_id: Command ID (type: क्रमागत es58x_fd_cmd_id).
 * @channel_idx: Channel index starting at 0.
 * @msg_len: Length of the message, excluding CRC (i.e. length of the
 *	जोड़).
 * @tx_conf_msg: Channel configuration.
 * @tx_can_msg_buf: Concatenation of Tx messages. Type is "u8[]"
 *	instead of "struct es58x_fd_tx_msg[]" because the काष्ठाure
 *	has a flexible size.
 * @rx_can_msg_buf: Concatenation Rx messages. Type is "u8[]" instead
 *	of "struct es58x_fd_rx_msg[]" because the काष्ठाure has a
 *	flexible size.
 * @echo_msg: Array of echo messages (e.g. Tx messages being looped
 *	back).
 * @rx_event_msg: Error or event message.
 * @tx_ack_msg: Tx acknowledgment message.
 * @बारtamp: Timestamp reply.
 * @rx_cmd_ret_le32: Rx 32 bits वापस code (type: क्रमागत
 *	es58x_cmd_ret_code_u32).
 * @raw_msg: Message raw payload.
 * @reserved_क्रम_crc16_करो_not_use: The काष्ठाure ends with a
 *	CRC16. Because the काष्ठाures in above जोड़ are of variable
 *	lengths, we can not predict the offset of the CRC in
 *	advance. Use functions es58x_get_crc() and es58x_set_crc() to
 *	manipulate it.
 */
काष्ठा es58x_fd_urb_cmd अणु
	__le16 SOF;
	u8 cmd_type;
	u8 cmd_id;
	u8 channel_idx;
	__le16 msg_len;

	जोड़ अणु
		काष्ठा es58x_fd_tx_conf_msg tx_conf_msg;
		u8 tx_can_msg_buf[ES58X_FD_TX_BULK_MAX * ES58X_FD_CANFD_TX_LEN];
		u8 rx_can_msg_buf[ES58X_FD_RX_BULK_MAX * ES58X_FD_CANFD_RX_LEN];
		काष्ठा es58x_fd_echo_msg echo_msg[ES58X_FD_ECHO_BULK_MAX];
		काष्ठा es58x_fd_rx_event_msg rx_event_msg;
		काष्ठा es58x_fd_tx_ack_msg tx_ack_msg;
		__le64 बारtamp;
		__le32 rx_cmd_ret_le32;
		u8 raw_msg[0];
	पूर्ण __packed;

	__le16 reserved_क्रम_crc16_करो_not_use;
पूर्ण __packed;

#घोषणा ES58X_FD_URB_CMD_HEADER_LEN (दुरत्व(काष्ठा es58x_fd_urb_cmd, raw_msg))
#घोषणा ES58X_FD_TX_URB_CMD_MAX_LEN					\
	ES58X_SIZखातापूर्ण_URB_CMD(काष्ठा es58x_fd_urb_cmd, tx_can_msg_buf)
#घोषणा ES58X_FD_RX_URB_CMD_MAX_LEN					\
	ES58X_SIZखातापूर्ण_URB_CMD(काष्ठा es58x_fd_urb_cmd, rx_can_msg_buf)

#पूर्ण_अगर /* __ES58X_FD_H__ */
