<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Driver क्रम ETAS GmbH ES58X USB CAN(-FD) Bus Interfaces.
 *
 * File es58x_core.h: All common definitions and declarations.
 *
 * Copyright (c) 2019 Robert Bosch Engineering and Business Solutions. All rights reserved.
 * Copyright (c) 2020 ETAS K.K.. All rights reserved.
 * Copyright (c) 2020, 2021 Vincent Mailhol <mailhol.vincent@wanaकरोo.fr>
 */

#अगर_अघोषित __ES58X_COMMON_H__
#घोषणा __ES58X_COMMON_H__

#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>

#समावेश "es581_4.h"
#समावेश "es58x_fd.h"

/* Driver स्थिरants */
#घोषणा ES58X_RX_URBS_MAX 5	/* Empirical value */
#घोषणा ES58X_TX_URBS_MAX 6	/* Empirical value */

#घोषणा ES58X_MAX(param)				\
	(ES581_4_##param > ES58X_FD_##param ?		\
		ES581_4_##param : ES58X_FD_##param)
#घोषणा ES58X_TX_BULK_MAX ES58X_MAX(TX_BULK_MAX)
#घोषणा ES58X_RX_BULK_MAX ES58X_MAX(RX_BULK_MAX)
#घोषणा ES58X_ECHO_BULK_MAX ES58X_MAX(ECHO_BULK_MAX)
#घोषणा ES58X_NUM_CAN_CH_MAX ES58X_MAX(NUM_CAN_CH)

/* Use this when channel index is irrelevant (e.g. device
 * बारtamp).
 */
#घोषणा ES58X_CHANNEL_IDX_NA 0xFF
#घोषणा ES58X_EMPTY_MSG शून्य

/* Threshold on consecutive CAN_STATE_ERROR_PASSIVE. If we receive
 * ES58X_CONSECUTIVE_ERR_PASSIVE_MAX बार the event
 * ES58X_ERR_CRTL_PASSIVE in a row without any successful RX or TX,
 * we क्रमce the device to चयन to CAN_STATE_BUS_OFF state.
 */
#घोषणा ES58X_CONSECUTIVE_ERR_PASSIVE_MAX 254

/* A magic number sent by the ES581.4 to inक्रमm it is alive. */
#घोषणा ES58X_HEARTBEAT 0x11

/**
 * क्रमागत es58x_driver_info - Quirks of the device.
 * @ES58X_DUAL_CHANNEL: Device has two CAN channels. If this flag is
 *	not set, it is implied that the device has only one CAN
 *	channel.
 * @ES58X_FD_FAMILY: Device is CAN-FD capable. If this flag is not
 *	set, the device only supports classical CAN.
 */
क्रमागत es58x_driver_info अणु
	ES58X_DUAL_CHANNEL = BIT(0),
	ES58X_FD_FAMILY = BIT(1)
पूर्ण;

क्रमागत es58x_echo अणु
	ES58X_ECHO_OFF = 0,
	ES58X_ECHO_ON = 1
पूर्ण;

/**
 * क्रमागत es58x_physical_layer - Type of the physical layer.
 * @ES58X_PHYSICAL_LAYER_HIGH_SPEED: High-speed CAN (c.f. ISO
 *	11898-2).
 *
 * Some products of the ETAS portfolio also support low-speed CAN
 * (c.f. ISO 11898-3). However, all the devices in scope of this
 * driver करो not support the option, thus, the क्रमागत has only one
 * member.
 */
क्रमागत es58x_physical_layer अणु
	ES58X_PHYSICAL_LAYER_HIGH_SPEED = 1
पूर्ण;

क्रमागत es58x_samples_per_bit अणु
	ES58X_SAMPLES_PER_BIT_ONE = 1,
	ES58X_SAMPLES_PER_BIT_THREE = 2
पूर्ण;

/**
 * क्रमागत es58x_sync_edge - Synchronization method.
 * @ES58X_SYNC_EDGE_SINGLE: ISO CAN specअगरication defines the use of a
 *	single edge synchronization.  The synchronization should be
 *	करोne on recessive to करोminant level change.
 *
 * For inक्रमmation, ES582.1 and ES584.1 also support a द्विगुन
 * synchronization, requiring both recessive to करोminant then करोminant
 * to recessive level change. However, this is not supported in
 * SocketCAN framework, thus, the क्रमागत has only one member.
 */
क्रमागत es58x_sync_edge अणु
	ES58X_SYNC_EDGE_SINGLE = 1
पूर्ण;

/**
 * क्रमागत es58x_flag - CAN flags क्रम RX/TX messages.
 * @ES58X_FLAG_EFF: Extended Frame Format (EFF).
 * @ES58X_FLAG_RTR: Remote Transmission Request (RTR).
 * @ES58X_FLAG_FD_BRS: Bit rate चयन (BRS): second bitrate क्रम
 *	payload data.
 * @ES58X_FLAG_FD_ESI: Error State Indicator (ESI): tell अगर the
 *	transmitting node is in error passive mode.
 * @ES58X_FLAG_FD_DATA: CAN FD frame.
 */
क्रमागत es58x_flag अणु
	ES58X_FLAG_EFF = BIT(0),
	ES58X_FLAG_RTR = BIT(1),
	ES58X_FLAG_FD_BRS = BIT(3),
	ES58X_FLAG_FD_ESI = BIT(5),
	ES58X_FLAG_FD_DATA = BIT(6)
पूर्ण;

/**
 * क्रमागत es58x_err - CAN error detection.
 * @ES58X_ERR_OK: No errors.
 * @ES58X_ERR_PROT_STUFF: Bit stuffing error: more than 5 consecutive
 *	equal bits.
 * @ES58X_ERR_PROT_FORM: Frame क्रमmat error.
 * @ES58X_ERR_ACK: Received no ACK on transmission.
 * @ES58X_ERR_PROT_BIT: Single bit error.
 * @ES58X_ERR_PROT_CRC: Incorrect 15, 17 or 21 bits CRC.
 * @ES58X_ERR_PROT_BIT1: Unable to send recessive bit: tried to send
 *	recessive bit 1 but monitored करोminant bit 0.
 * @ES58X_ERR_PROT_BIT0: Unable to send करोminant bit: tried to send
 *	करोminant bit 0 but monitored recessive bit 1.
 * @ES58X_ERR_PROT_OVERLOAD: Bus overload.
 * @ES58X_ERR_PROT_UNSPEC: Unspecअगरied.
 *
 * Please refer to ISO 11898-1:2015, section 10.11 "Error detection"
 * and section 10.13 "Overload signaling" क्रम additional details.
 */
क्रमागत es58x_err अणु
	ES58X_ERR_OK = 0,
	ES58X_ERR_PROT_STUFF = BIT(0),
	ES58X_ERR_PROT_FORM = BIT(1),
	ES58X_ERR_ACK = BIT(2),
	ES58X_ERR_PROT_BIT = BIT(3),
	ES58X_ERR_PROT_CRC = BIT(4),
	ES58X_ERR_PROT_BIT1 = BIT(5),
	ES58X_ERR_PROT_BIT0 = BIT(6),
	ES58X_ERR_PROT_OVERLOAD = BIT(7),
	ES58X_ERR_PROT_UNSPEC = BIT(31)
पूर्ण;

/**
 * क्रमागत es58x_event - CAN error codes वापसed by the device.
 * @ES58X_EVENT_OK: No errors.
 * @ES58X_EVENT_CRTL_ACTIVE: Active state: both TR and RX error count
 *	is less than 128.
 * @ES58X_EVENT_CRTL_PASSIVE: Passive state: either TX or RX error
 *	count is greater than 127.
 * @ES58X_EVENT_CRTL_WARNING: Warning state: either TX or RX error
 *	count is greater than 96.
 * @ES58X_EVENT_BUSOFF: Bus off.
 * @ES58X_EVENT_SINGLE_WIRE: Lost connection on either CAN high or CAN
 *	low.
 *
 * Please refer to ISO 11898-1:2015, section 12.1.4 "Rules of fault
 * confinement" क्रम additional details.
 */
क्रमागत es58x_event अणु
	ES58X_EVENT_OK = 0,
	ES58X_EVENT_CRTL_ACTIVE = BIT(0),
	ES58X_EVENT_CRTL_PASSIVE = BIT(1),
	ES58X_EVENT_CRTL_WARNING = BIT(2),
	ES58X_EVENT_BUSOFF = BIT(3),
	ES58X_EVENT_SINGLE_WIRE = BIT(4)
पूर्ण;

/* क्रमागत es58x_ret_u8 - Device वापस error codes, 8 bit क्रमmat.
 *
 * Specअगरic to ES581.4.
 */
क्रमागत es58x_ret_u8 अणु
	ES58X_RET_U8_OK = 0x00,
	ES58X_RET_U8_ERR_UNSPECIFIED_FAILURE = 0x80,
	ES58X_RET_U8_ERR_NO_MEM = 0x81,
	ES58X_RET_U8_ERR_BAD_CRC = 0x99
पूर्ण;

/* क्रमागत es58x_ret_u32 - Device वापस error codes, 32 bit क्रमmat.
 */
क्रमागत es58x_ret_u32 अणु
	ES58X_RET_U32_OK = 0x00000000UL,
	ES58X_RET_U32_ERR_UNSPECIFIED_FAILURE = 0x80000000UL,
	ES58X_RET_U32_ERR_NO_MEM = 0x80004001UL,
	ES58X_RET_U32_WARN_PARAM_ADJUSTED = 0x40004000UL,
	ES58X_RET_U32_WARN_TX_MAYBE_REORDER = 0x40004001UL,
	ES58X_RET_U32_ERR_TIMEDOUT = 0x80000008UL,
	ES58X_RET_U32_ERR_FIFO_FULL = 0x80003002UL,
	ES58X_RET_U32_ERR_BAD_CONFIG = 0x80004000UL,
	ES58X_RET_U32_ERR_NO_RESOURCE = 0x80004002UL
पूर्ण;

/* क्रमागत es58x_ret_type - Type of the command वापसed by the ES58X
 *	device.
 */
क्रमागत es58x_ret_type अणु
	ES58X_RET_TYPE_SET_BITTIMING,
	ES58X_RET_TYPE_ENABLE_CHANNEL,
	ES58X_RET_TYPE_DISABLE_CHANNEL,
	ES58X_RET_TYPE_TX_MSG,
	ES58X_RET_TYPE_RESET_RX,
	ES58X_RET_TYPE_RESET_TX,
	ES58X_RET_TYPE_DEVICE_ERR
पूर्ण;

जोड़ es58x_urb_cmd अणु
	काष्ठा es581_4_urb_cmd es581_4_urb_cmd;
	काष्ठा es58x_fd_urb_cmd es58x_fd_urb_cmd;
	काष्ठा अणु		/* Common header parts of all variants */
		__le16 sof;
		u8 cmd_type;
		u8 cmd_id;
	पूर्ण __packed;
	u8 raw_cmd[0];
पूर्ण;

/**
 * काष्ठा es58x_priv - All inक्रमmation specअगरic to a CAN channel.
 * @can: काष्ठा can_priv must be the first member (Socket CAN relies
 *	on the fact that function netdev_priv() वापसs a poपूर्णांकer to
 *	a काष्ठा can_priv).
 * @es58x_dev: poपूर्णांकer to the corresponding ES58X device.
 * @tx_urb: Used as a buffer to concatenate the TX messages and to करो
 *	a bulk send. Please refer to es58x_start_xmit() क्रम more
 *	details.
 * @tx_tail: Index of the oldest packet still pending क्रम
 *	completion. @tx_tail & echo_skb_mask represents the beginning
 *	of the echo skb FIFO, i.e. index of the first element.
 * @tx_head: Index of the next packet to be sent to the
 *	device. @tx_head & echo_skb_mask represents the end of the
 *	echo skb FIFO plus one, i.e. the first मुक्त index.
 * @tx_can_msg_cnt: Number of messages in @tx_urb.
 * @tx_can_msg_is_fd: false: all messages in @tx_urb are Classical
 *	CAN, true: all messages in @tx_urb are CAN FD. Rationale:
 *	ES58X FD devices करो not allow to mix Classical CAN and FD CAN
 *	frames in one single bulk transmission.
 * @err_passive_beक्रमe_rtx_success: The ES58X device might enter in a
 *	state in which it keeps alternating between error passive
 *	and active states. This counter keeps track of the number of
 *	error passive and अगर it माला_लो bigger than
 *	ES58X_CONSECUTIVE_ERR_PASSIVE_MAX, es58x_rx_err_msg() will
 *	क्रमce the status to bus-off.
 * @channel_idx: Channel index, starts at zero.
 */
काष्ठा es58x_priv अणु
	काष्ठा can_priv can;
	काष्ठा es58x_device *es58x_dev;
	काष्ठा urb *tx_urb;

	u32 tx_tail;
	u32 tx_head;

	u8 tx_can_msg_cnt;
	bool tx_can_msg_is_fd;

	u8 err_passive_beक्रमe_rtx_success;

	u8 channel_idx;
पूर्ण;

/**
 * काष्ठा es58x_parameters - Constant parameters of a given hardware
 *	variant.
 * @bittiming_स्थिर: Nominal bittimming स्थिरant parameters.
 * @data_bittiming_स्थिर: Data bittiming स्थिरant parameters.
 * @tdc_स्थिर: Transmission Delay Compensation स्थिरant parameters.
 * @bitrate_max: Maximum bitrate supported by the device.
 * @घड़ी: CAN घड़ी parameters.
 * @ctrlmode_supported: List of supported modes. Please refer to
 *	can/netlink.h file क्रम additional details.
 * @tx_start_of_frame: Magic number at the beginning of each TX URB
 *	command.
 * @rx_start_of_frame: Magic number at the beginning of each RX URB
 *	command.
 * @tx_urb_cmd_max_len: Maximum length of a TX URB command.
 * @rx_urb_cmd_max_len: Maximum length of a RX URB command.
 * @fअगरo_mask: Bit mask to quickly convert the tx_tail and tx_head
 *	field of the काष्ठा es58x_priv पूर्णांकo echo_skb
 *	indexes. Properties: @fअगरo_mask = echos_skb_max - 1 where
 *	echo_skb_max must be a घातer of two. Also, echo_skb_max must
 *	not exceed the maximum size of the device पूर्णांकernal TX FIFO
 *	length. This parameter is used to control the network queue
 *	wake/stop logic.
 * @dql_min_limit: Dynamic Queue Limits (DQL) असलolute minimum limit
 *	of bytes allowed to be queued on this network device transmit
 *	queue. Used by the Byte Queue Limits (BQL) to determine how
 *	frequently the xmit_more flag will be set to true in
 *	es58x_start_xmit(). Set this value higher to optimize क्रम
 *	throughput but be aware that it might have a negative impact
 *	on the latency! This value can also be set dynamically. Please
 *	refer to Documentation/ABI/testing/sysfs-class-net-queues क्रम
 *	more details.
 * @tx_bulk_max: Maximum number of TX messages that can be sent in one
 *	single URB packet.
 * @urb_cmd_header_len: Length of the URB command header.
 * @rx_urb_max: Number of RX URB to be allocated during device probe.
 * @tx_urb_max: Number of TX URB to be allocated during device probe.
 */
काष्ठा es58x_parameters अणु
	स्थिर काष्ठा can_bittiming_स्थिर *bittiming_स्थिर;
	स्थिर काष्ठा can_bittiming_स्थिर *data_bittiming_स्थिर;
	स्थिर काष्ठा can_tdc_स्थिर *tdc_स्थिर;
	u32 bitrate_max;
	काष्ठा can_घड़ी घड़ी;
	u32 ctrlmode_supported;
	u16 tx_start_of_frame;
	u16 rx_start_of_frame;
	u16 tx_urb_cmd_max_len;
	u16 rx_urb_cmd_max_len;
	u16 fअगरo_mask;
	u16 dql_min_limit;
	u8 tx_bulk_max;
	u8 urb_cmd_header_len;
	u8 rx_urb_max;
	u8 tx_urb_max;
पूर्ण;

/**
 * काष्ठा es58x_चालकs - Function poपूर्णांकers used to encode/decode
 *	the TX/RX messages.
 * @get_msg_len: Get field msg_len of the urb_cmd. The offset of
 *	msg_len inside urb_cmd depends of the device model.
 * @handle_urb_cmd: Decode the URB command received from the device
 *	and dispatch it to the relevant sub function.
 * @fill_urb_header: Fill the header of urb_cmd.
 * @tx_can_msg: Encode a TX CAN message and add it to the bulk buffer
 *	cmd_buf of es58x_dev.
 * @enable_channel: Start the CAN channel.
 * @disable_channel: Stop the CAN channel.
 * @reset_device: Full reset of the device. N.B: this feature is only
 *	present on the ES581.4. For ES58X FD devices, this field is
 *	set to शून्य.
 * @get_बारtamp: Request a बारtamp from the ES58X device.
 */
काष्ठा es58x_चालकs अणु
	u16 (*get_msg_len)(स्थिर जोड़ es58x_urb_cmd *urb_cmd);
	पूर्णांक (*handle_urb_cmd)(काष्ठा es58x_device *es58x_dev,
			      स्थिर जोड़ es58x_urb_cmd *urb_cmd);
	व्योम (*fill_urb_header)(जोड़ es58x_urb_cmd *urb_cmd, u8 cmd_type,
				u8 cmd_id, u8 channel_idx, u16 cmd_len);
	पूर्णांक (*tx_can_msg)(काष्ठा es58x_priv *priv, स्थिर काष्ठा sk_buff *skb);
	पूर्णांक (*enable_channel)(काष्ठा es58x_priv *priv);
	पूर्णांक (*disable_channel)(काष्ठा es58x_priv *priv);
	पूर्णांक (*reset_device)(काष्ठा es58x_device *es58x_dev);
	पूर्णांक (*get_बारtamp)(काष्ठा es58x_device *es58x_dev);
पूर्ण;

/**
 * काष्ठा es58x_device - All inक्रमmation specअगरic to an ES58X device.
 * @dev: Device inक्रमmation.
 * @udev: USB device inक्रमmation.
 * @netdev: Array of our CAN channels.
 * @param: The स्थिरant parameters.
 * @ops: Operators.
 * @rx_pipe: USB reception pipe.
 * @tx_pipe: USB transmission pipe.
 * @rx_urbs: Anchor क्रम received URBs.
 * @tx_urbs_busy: Anchor क्रम TX URBs which were send to the device.
 * @tx_urbs_idle: Anchor क्रम TX USB which are idle. This driver
 *	allocates the memory क्रम the URBs during the probe. When a TX
 *	URB is needed, it can be taken from this anchor. The network
 *	queue wake/stop logic should prevent this URB from getting
 *	empty. Please refer to es58x_get_tx_urb() क्रम more details.
 * @tx_urbs_idle_cnt: number of urbs in @tx_urbs_idle.
 * @खोलोed_channel_cnt: number of channels खोलोed (c.f. es58x_खोलो()
 *	and es58x_stop()).
 * @kसमय_req_ns: kernel बारtamp when es58x_set_realसमय_dअगरf_ns()
 *	was called.
 * @realसमय_dअगरf_ns: dअगरference in nanoseconds between the घड़ीs of
 *	the ES58X device and the kernel.
 * @बारtamps: a temporary buffer to store the समय stamps beक्रमe
 *	feeding them to es58x_can_get_echo_skb(). Can only be used
 *	in RX branches.
 * @rx_max_packet_size: Maximum length of bulk-in URB.
 * @num_can_ch: Number of CAN channel (i.e. number of elements of @netdev).
 * @rx_cmd_buf_len: Length of @rx_cmd_buf.
 * @rx_cmd_buf: The device might split the URB commands in an
 *	arbitrary amount of pieces. This buffer is used to concatenate
 *	all those pieces. Can only be used in RX branches. This field
 *	has to be the last one of the काष्ठाure because it is has a
 *	flexible size (c.f. es58x_माप_es58x_device() function).
 */
काष्ठा es58x_device अणु
	काष्ठा device *dev;
	काष्ठा usb_device *udev;
	काष्ठा net_device *netdev[ES58X_NUM_CAN_CH_MAX];

	स्थिर काष्ठा es58x_parameters *param;
	स्थिर काष्ठा es58x_चालकs *ops;

	पूर्णांक rx_pipe;
	पूर्णांक tx_pipe;

	काष्ठा usb_anchor rx_urbs;
	काष्ठा usb_anchor tx_urbs_busy;
	काष्ठा usb_anchor tx_urbs_idle;
	atomic_t tx_urbs_idle_cnt;
	atomic_t खोलोed_channel_cnt;

	u64 kसमय_req_ns;
	s64 realसमय_dअगरf_ns;

	u64 बारtamps[ES58X_ECHO_BULK_MAX];

	u16 rx_max_packet_size;
	u8 num_can_ch;

	u16 rx_cmd_buf_len;
	जोड़ es58x_urb_cmd rx_cmd_buf;
पूर्ण;

/**
 * es58x_माप_es58x_device() - Calculate the maximum length of
 *	काष्ठा es58x_device.
 * @es58x_dev_param: The स्थिरant parameters of the device.
 *
 * The length of काष्ठा es58x_device depends on the length of its last
 * field: rx_cmd_buf. This macro allows to optimize the memory
 * allocation.
 *
 * Return: length of काष्ठा es58x_device.
 */
अटल अंतरभूत माप_प्रकार es58x_माप_es58x_device(स्थिर काष्ठा es58x_parameters
					       *es58x_dev_param)
अणु
	वापस दुरत्व(काष्ठा es58x_device, rx_cmd_buf) +
		es58x_dev_param->rx_urb_cmd_max_len;
पूर्ण

अटल अंतरभूत पूर्णांक __es58x_check_msg_len(स्थिर काष्ठा device *dev,
					स्थिर अक्षर *stringअगरied_msg,
					माप_प्रकार actual_len, माप_प्रकार expected_len)
अणु
	अगर (expected_len != actual_len) अणु
		dev_err(dev,
			"Length of %s is %zu but received command is %zu.\n",
			stringअगरied_msg, expected_len, actual_len);
		वापस -EMSGSIZE;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * es58x_check_msg_len() - Check the size of a received message.
 * @dev: Device, used to prपूर्णांक error messages.
 * @msg: Received message, must not be a poपूर्णांकer.
 * @actual_len: Length of the message as advertised in the command header.
 *
 * Must be a macro in order to accept the dअगरferent types of messages
 * as an input. Can be use with any of the messages which have a fixed
 * length. Check क्रम an exact match of the size.
 *
 * Return: zero on success, -EMSGSIZE अगर @actual_len dअगरfers from the
 * expected length.
 */
#घोषणा es58x_check_msg_len(dev, msg, actual_len)			\
	__es58x_check_msg_len(dev, __stringअगरy(msg),			\
			      actual_len, माप(msg))

अटल अंतरभूत पूर्णांक __es58x_check_msg_max_len(स्थिर काष्ठा device *dev,
					    स्थिर अक्षर *stringअगरied_msg,
					    माप_प्रकार actual_len,
					    माप_प्रकार expected_len)
अणु
	अगर (actual_len > expected_len) अणु
		dev_err(dev,
			"Maximum length for %s is %zu but received command is %zu.\n",
			stringअगरied_msg, expected_len, actual_len);
		वापस -EOVERFLOW;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * es58x_check_msg_max_len() - Check the maximum size of a received message.
 * @dev: Device, used to prपूर्णांक error messages.
 * @msg: Received message, must not be a poपूर्णांकer.
 * @actual_len: Length of the message as advertised in the command header.
 *
 * Must be a macro in order to accept the dअगरferent types of messages
 * as an input. To be used with the messages of variable sizes. Only
 * check that the message is not bigger than the maximum expected
 * size.
 *
 * Return: zero on success, -EOVERFLOW अगर @actual_len is greater than
 * the expected length.
 */
#घोषणा es58x_check_msg_max_len(dev, msg, actual_len)			\
	__es58x_check_msg_max_len(dev, __stringअगरy(msg),		\
				  actual_len, माप(msg))

अटल अंतरभूत पूर्णांक __es58x_msg_num_element(स्थिर काष्ठा device *dev,
					  स्थिर अक्षर *stringअगरied_msg,
					  माप_प्रकार actual_len, माप_प्रकार msg_len,
					  माप_प्रकार elem_len)
अणु
	माप_प्रकार actual_num_elem = actual_len / elem_len;
	माप_प्रकार expected_num_elem = msg_len / elem_len;

	अगर (actual_num_elem == 0) अणु
		dev_err(dev,
			"Minimum length for %s is %zu but received command is %zu.\n",
			stringअगरied_msg, elem_len, actual_len);
		वापस -EMSGSIZE;
	पूर्ण अन्यथा अगर ((actual_len % elem_len) != 0) अणु
		dev_err(dev,
			"Received command length: %zu is not a multiple of %s[0]: %zu\n",
			actual_len, stringअगरied_msg, elem_len);
		वापस -EMSGSIZE;
	पूर्ण अन्यथा अगर (actual_num_elem > expected_num_elem) अणु
		dev_err(dev,
			"Array %s is supposed to have %zu elements each of size %zu...\n",
			stringअगरied_msg, expected_num_elem, elem_len);
		dev_err(dev,
			"... But received command has %zu elements (total length %zu).\n",
			actual_num_elem, actual_len);
		वापस -EOVERFLOW;
	पूर्ण
	वापस actual_num_elem;
पूर्ण

/**
 * es58x_msg_num_element() - Check size and give the number of
 *	elements in a message of array type.
 * @dev: Device, used to prपूर्णांक error messages.
 * @msg: Received message, must be an array.
 * @actual_len: Length of the message as advertised in the command
 *	header.
 *
 * Must be a macro in order to accept the dअगरferent types of messages
 * as an input. To be used on message of array type. Array's element
 * has to be of fixed size (अन्यथा use es58x_check_msg_max_len()). Check
 * that the total length is an exact multiple of the length of a
 * single element.
 *
 * Return: number of elements in the array on success, -EOVERFLOW अगर
 * @actual_len is greater than the expected length, -EMSGSIZE अगर
 * @actual_len is not a multiple of a single element.
 */
#घोषणा es58x_msg_num_element(dev, msg, actual_len)			\
(अणु									\
	माप_प्रकार __elem_len = माप((msg)[0]) + __must_be_array(msg);	\
	__es58x_msg_num_element(dev, __stringअगरy(msg), actual_len,	\
				माप(msg), __elem_len);		\
पूर्ण)

/**
 * es58x_priv() - Get the priv member and cast it to काष्ठा es58x_priv.
 * @netdev: CAN network device.
 *
 * Return: ES58X device.
 */
अटल अंतरभूत काष्ठा es58x_priv *es58x_priv(काष्ठा net_device *netdev)
अणु
	वापस (काष्ठा es58x_priv *)netdev_priv(netdev);
पूर्ण

/**
 * ES58X_SIZखातापूर्ण_URB_CMD() - Calculate the maximum length of an urb
 *	command क्रम a given message field name.
 * @es58x_urb_cmd_type: type (either "struct es581_4_urb_cmd" or
 *	"struct es58x_fd_urb_cmd").
 * @msg_field: name of the message field.
 *
 * Must be a macro in order to accept the dअगरferent command types as
 * an input.
 *
 * Return: length of the urb command.
 */
#घोषणा ES58X_SIZखातापूर्ण_URB_CMD(es58x_urb_cmd_type, msg_field)		\
	(दुरत्व(es58x_urb_cmd_type, raw_msg)				\
		+ माप_field(es58x_urb_cmd_type, msg_field)		\
		+ माप_field(es58x_urb_cmd_type,			\
			       reserved_क्रम_crc16_करो_not_use))

/**
 * es58x_get_urb_cmd_len() - Calculate the actual length of an urb
 *	command क्रम a given message length.
 * @es58x_dev: ES58X device.
 * @msg_len: Length of the message.
 *
 * Add the header and CRC lengths to the message length.
 *
 * Return: length of the urb command.
 */
अटल अंतरभूत माप_प्रकार es58x_get_urb_cmd_len(काष्ठा es58x_device *es58x_dev,
					   u16 msg_len)
अणु
	वापस es58x_dev->param->urb_cmd_header_len + msg_len + माप(u16);
पूर्ण

/**
 * es58x_get_netdev() - Get the network device.
 * @es58x_dev: ES58X device.
 * @channel_no: The channel number as advertised in the urb command.
 * @channel_idx_offset: Some of the ES58x starts channel numbering
 *	from 0 (ES58X FD), others from 1 (ES581.4).
 * @netdev: CAN network device.
 *
 * Do a sanity check on the index provided by the device.
 *
 * Return: zero on success, -ECHRNG अगर the received channel number is
 *	out of range and -ENODEV अगर the network device is not yet
 *	configured.
 */
अटल अंतरभूत पूर्णांक es58x_get_netdev(काष्ठा es58x_device *es58x_dev,
				   पूर्णांक channel_no, पूर्णांक channel_idx_offset,
				   काष्ठा net_device **netdev)
अणु
	पूर्णांक channel_idx = channel_no - channel_idx_offset;

	*netdev = शून्य;
	अगर (channel_idx < 0 || channel_idx >= es58x_dev->num_can_ch)
		वापस -ECHRNG;

	*netdev = es58x_dev->netdev[channel_idx];
	अगर (!*netdev || !netअगर_device_present(*netdev))
		वापस -ENODEV;

	वापस 0;
पूर्ण

/**
 * es58x_get_raw_can_id() - Get the CAN ID.
 * @cf: CAN frame.
 *
 * Mask the CAN ID in order to only keep the signअगरicant bits.
 *
 * Return: the raw value of the CAN ID.
 */
अटल अंतरभूत पूर्णांक es58x_get_raw_can_id(स्थिर काष्ठा can_frame *cf)
अणु
	अगर (cf->can_id & CAN_EFF_FLAG)
		वापस cf->can_id & CAN_EFF_MASK;
	अन्यथा
		वापस cf->can_id & CAN_SFF_MASK;
पूर्ण

/**
 * es58x_get_flags() - Get the CAN flags.
 * @skb: socket buffer of a CAN message.
 *
 * Return: the CAN flag as an क्रमागत es58x_flag.
 */
अटल अंतरभूत क्रमागत es58x_flag es58x_get_flags(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;
	क्रमागत es58x_flag es58x_flags = 0;

	अगर (cf->can_id & CAN_EFF_FLAG)
		es58x_flags |= ES58X_FLAG_EFF;

	अगर (can_is_canfd_skb(skb)) अणु
		es58x_flags |= ES58X_FLAG_FD_DATA;
		अगर (cf->flags & CANFD_BRS)
			es58x_flags |= ES58X_FLAG_FD_BRS;
		अगर (cf->flags & CANFD_ESI)
			es58x_flags |= ES58X_FLAG_FD_ESI;
	पूर्ण अन्यथा अगर (cf->can_id & CAN_RTR_FLAG)
		/* Remote frames are only defined in Classical CAN frames */
		es58x_flags |= ES58X_FLAG_RTR;

	वापस es58x_flags;
पूर्ण

पूर्णांक es58x_can_get_echo_skb(काष्ठा net_device *netdev, u32 packet_idx,
			   u64 *tstamps, अचिन्हित पूर्णांक pkts);
पूर्णांक es58x_tx_ack_msg(काष्ठा net_device *netdev, u16 tx_मुक्त_entries,
		     क्रमागत es58x_ret_u32 rx_cmd_ret_u32);
पूर्णांक es58x_rx_can_msg(काष्ठा net_device *netdev, u64 बारtamp, स्थिर u8 *data,
		     canid_t can_id, क्रमागत es58x_flag es58x_flags, u8 dlc);
पूर्णांक es58x_rx_err_msg(काष्ठा net_device *netdev, क्रमागत es58x_err error,
		     क्रमागत es58x_event event, u64 बारtamp);
व्योम es58x_rx_बारtamp(काष्ठा es58x_device *es58x_dev, u64 बारtamp);
पूर्णांक es58x_rx_cmd_ret_u8(काष्ठा device *dev, क्रमागत es58x_ret_type cmd_ret_type,
			क्रमागत es58x_ret_u8 rx_cmd_ret_u8);
पूर्णांक es58x_rx_cmd_ret_u32(काष्ठा net_device *netdev,
			 क्रमागत es58x_ret_type cmd_ret_type,
			 क्रमागत es58x_ret_u32 rx_cmd_ret_u32);
पूर्णांक es58x_send_msg(काष्ठा es58x_device *es58x_dev, u8 cmd_type, u8 cmd_id,
		   स्थिर व्योम *msg, u16 cmd_len, पूर्णांक channel_idx);

बाह्य स्थिर काष्ठा es58x_parameters es581_4_param;
बाह्य स्थिर काष्ठा es58x_चालकs es581_4_ops;

बाह्य स्थिर काष्ठा es58x_parameters es58x_fd_param;
बाह्य स्थिर काष्ठा es58x_चालकs es58x_fd_ops;

#पूर्ण_अगर /* __ES58X_COMMON_H__ */
