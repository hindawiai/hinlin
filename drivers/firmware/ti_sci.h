<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Texas Instruments System Control Interface (TISCI) Protocol
 *
 * Communication protocol with TI SCI hardware
 * The प्रणाली works in a message response protocol
 * See: http://processors.wiki.ti.com/index.php/TISCI क्रम details
 *
 * Copyright (C)  2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित __TI_SCI_H
#घोषणा __TI_SCI_H

/* Generic Messages */
#घोषणा TI_SCI_MSG_ENABLE_WDT	0x0000
#घोषणा TI_SCI_MSG_WAKE_RESET	0x0001
#घोषणा TI_SCI_MSG_VERSION	0x0002
#घोषणा TI_SCI_MSG_WAKE_REASON	0x0003
#घोषणा TI_SCI_MSG_GOODBYE	0x0004
#घोषणा TI_SCI_MSG_SYS_RESET	0x0005

/* Device requests */
#घोषणा TI_SCI_MSG_SET_DEVICE_STATE	0x0200
#घोषणा TI_SCI_MSG_GET_DEVICE_STATE	0x0201
#घोषणा TI_SCI_MSG_SET_DEVICE_RESETS	0x0202

/* Clock requests */
#घोषणा TI_SCI_MSG_SET_CLOCK_STATE	0x0100
#घोषणा TI_SCI_MSG_GET_CLOCK_STATE	0x0101
#घोषणा TI_SCI_MSG_SET_CLOCK_PARENT	0x0102
#घोषणा TI_SCI_MSG_GET_CLOCK_PARENT	0x0103
#घोषणा TI_SCI_MSG_GET_NUM_CLOCK_PARENTS 0x0104
#घोषणा TI_SCI_MSG_SET_CLOCK_FREQ	0x010c
#घोषणा TI_SCI_MSG_QUERY_CLOCK_FREQ	0x010d
#घोषणा TI_SCI_MSG_GET_CLOCK_FREQ	0x010e

/* Resource Management Requests */
#घोषणा TI_SCI_MSG_GET_RESOURCE_RANGE	0x1500

/* IRQ requests */
#घोषणा TI_SCI_MSG_SET_IRQ		0x1000
#घोषणा TI_SCI_MSG_FREE_IRQ		0x1001

/* NAVSS resource management */
/* Ringacc requests */
#घोषणा TI_SCI_MSG_RM_RING_ALLOCATE		0x1100
#घोषणा TI_SCI_MSG_RM_RING_FREE			0x1101
#घोषणा TI_SCI_MSG_RM_RING_RECONFIG		0x1102
#घोषणा TI_SCI_MSG_RM_RING_RESET		0x1103
#घोषणा TI_SCI_MSG_RM_RING_CFG			0x1110

/* PSI-L requests */
#घोषणा TI_SCI_MSG_RM_PSIL_PAIR			0x1280
#घोषणा TI_SCI_MSG_RM_PSIL_UNPAIR		0x1281

#घोषणा TI_SCI_MSG_RM_UDMAP_TX_ALLOC		0x1200
#घोषणा TI_SCI_MSG_RM_UDMAP_TX_FREE		0x1201
#घोषणा TI_SCI_MSG_RM_UDMAP_RX_ALLOC		0x1210
#घोषणा TI_SCI_MSG_RM_UDMAP_RX_FREE		0x1211
#घोषणा TI_SCI_MSG_RM_UDMAP_FLOW_CFG		0x1220
#घोषणा TI_SCI_MSG_RM_UDMAP_OPT_FLOW_CFG	0x1221

#घोषणा TISCI_MSG_RM_UDMAP_TX_CH_CFG		0x1205
#घोषणा TISCI_MSG_RM_UDMAP_TX_CH_GET_CFG	0x1206
#घोषणा TISCI_MSG_RM_UDMAP_RX_CH_CFG		0x1215
#घोषणा TISCI_MSG_RM_UDMAP_RX_CH_GET_CFG	0x1216
#घोषणा TISCI_MSG_RM_UDMAP_FLOW_CFG		0x1230
#घोषणा TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG	0x1231
#घोषणा TISCI_MSG_RM_UDMAP_FLOW_GET_CFG		0x1232
#घोषणा TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_GET_CFG	0x1233

/* Processor Control requests */
#घोषणा TI_SCI_MSG_PROC_REQUEST		0xc000
#घोषणा TI_SCI_MSG_PROC_RELEASE		0xc001
#घोषणा TI_SCI_MSG_PROC_HANDOVER	0xc005
#घोषणा TI_SCI_MSG_SET_CONFIG		0xc100
#घोषणा TI_SCI_MSG_SET_CTRL		0xc101
#घोषणा TI_SCI_MSG_GET_STATUS		0xc400

/**
 * काष्ठा ti_sci_msg_hdr - Generic Message Header क्रम All messages and responses
 * @type:	Type of messages: One of TI_SCI_MSG* values
 * @host:	Host of the message
 * @seq:	Message identअगरier indicating a transfer sequence
 * @flags:	Flag क्रम the message
 */
काष्ठा ti_sci_msg_hdr अणु
	u16 type;
	u8 host;
	u8 seq;
#घोषणा TI_SCI_MSG_FLAG(val)			(1 << (val))
#घोषणा TI_SCI_FLAG_REQ_GENERIC_NORESPONSE	0x0
#घोषणा TI_SCI_FLAG_REQ_ACK_ON_RECEIVED		TI_SCI_MSG_FLAG(0)
#घोषणा TI_SCI_FLAG_REQ_ACK_ON_PROCESSED	TI_SCI_MSG_FLAG(1)
#घोषणा TI_SCI_FLAG_RESP_GENERIC_NACK		0x0
#घोषणा TI_SCI_FLAG_RESP_GENERIC_ACK		TI_SCI_MSG_FLAG(1)
	/* Additional Flags */
	u32 flags;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_version - Response क्रम a message
 * @hdr:		Generic header
 * @firmware_description: String describing the firmware
 * @firmware_revision:	Firmware revision
 * @abi_major:		Major version of the ABI that firmware supports
 * @abi_minor:		Minor version of the ABI that firmware supports
 *
 * In general, ABI version changes follow the rule that minor version increments
 * are backward compatible. Major revision changes in ABI may not be
 * backward compatible.
 *
 * Response to a generic message with message type TI_SCI_MSG_VERSION
 */
काष्ठा ti_sci_msg_resp_version अणु
	काष्ठा ti_sci_msg_hdr hdr;
	अक्षर firmware_description[32];
	u16 firmware_revision;
	u8 abi_major;
	u8 abi_minor;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_reboot - Reboot the SoC
 * @hdr:	Generic Header
 *
 * Request type is TI_SCI_MSG_SYS_RESET, responded with a generic
 * ACK/NACK message.
 */
काष्ठा ti_sci_msg_req_reboot अणु
	काष्ठा ti_sci_msg_hdr hdr;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_set_device_state - Set the desired state of the device
 * @hdr:		Generic header
 * @id:	Indicates which device to modअगरy
 * @reserved: Reserved space in message, must be 0 क्रम backward compatibility
 * @state: The desired state of the device.
 *
 * Certain flags can also be set to alter the device state:
 * + MSG_FLAG_DEVICE_WAKE_ENABLED - Configure the device to be a wake source.
 * The meaning of this flag will vary slightly from device to device and from
 * SoC to SoC but it generally allows the device to wake the SoC out of deep
 * suspend states.
 * + MSG_FLAG_DEVICE_RESET_ISO - Enable reset isolation क्रम this device.
 * + MSG_FLAG_DEVICE_EXCLUSIVE - Claim this device exclusively. When passed
 * with STATE_RETENTION or STATE_ON, it will claim the device exclusively.
 * If another host alपढ़ोy has this device set to STATE_RETENTION or STATE_ON,
 * the message will fail. Once successful, other hosts attempting to set
 * STATE_RETENTION or STATE_ON will fail.
 *
 * Request type is TI_SCI_MSG_SET_DEVICE_STATE, responded with a generic
 * ACK/NACK message.
 */
काष्ठा ti_sci_msg_req_set_device_state अणु
	/* Additional hdr->flags options */
#घोषणा MSG_FLAG_DEVICE_WAKE_ENABLED	TI_SCI_MSG_FLAG(8)
#घोषणा MSG_FLAG_DEVICE_RESET_ISO	TI_SCI_MSG_FLAG(9)
#घोषणा MSG_FLAG_DEVICE_EXCLUSIVE	TI_SCI_MSG_FLAG(10)
	काष्ठा ti_sci_msg_hdr hdr;
	u32 id;
	u32 reserved;

#घोषणा MSG_DEVICE_SW_STATE_AUTO_OFF	0
#घोषणा MSG_DEVICE_SW_STATE_RETENTION	1
#घोषणा MSG_DEVICE_SW_STATE_ON		2
	u8 state;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_get_device_state - Request to get device.
 * @hdr:		Generic header
 * @id:		Device Identअगरier
 *
 * Request type is TI_SCI_MSG_GET_DEVICE_STATE, responded device state
 * inक्रमmation
 */
काष्ठा ti_sci_msg_req_get_device_state अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 id;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_get_device_state - Response to get device request.
 * @hdr:		Generic header
 * @context_loss_count: Indicates how many बार the device has lost context. A
 *	driver can use this monotonic counter to determine अगर the device has
 *	lost context since the last समय this message was exchanged.
 * @resets: Programmed state of the reset lines.
 * @programmed_state:	The state as programmed by set_device.
 *			- Uses the MSG_DEVICE_SW_* macros
 * @current_state:	The actual state of the hardware.
 *
 * Response to request TI_SCI_MSG_GET_DEVICE_STATE.
 */
काष्ठा ti_sci_msg_resp_get_device_state अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 context_loss_count;
	u32 resets;
	u8 programmed_state;
#घोषणा MSG_DEVICE_HW_STATE_OFF		0
#घोषणा MSG_DEVICE_HW_STATE_ON		1
#घोषणा MSG_DEVICE_HW_STATE_TRANS	2
	u8 current_state;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_set_device_resets - Set the desired resets
 *				configuration of the device
 * @hdr:		Generic header
 * @id:	Indicates which device to modअगरy
 * @resets: A bit field of resets क्रम the device. The meaning, behavior,
 *	and usage of the reset flags are device specअगरic. 0 क्रम a bit
 *	indicates releasing the reset represented by that bit जबतक 1
 *	indicates keeping it held.
 *
 * Request type is TI_SCI_MSG_SET_DEVICE_RESETS, responded with a generic
 * ACK/NACK message.
 */
काष्ठा ti_sci_msg_req_set_device_resets अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 id;
	u32 resets;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_set_घड़ी_state - Request to setup a Clock state
 * @hdr:	Generic Header, Certain flags can be set specअगरic to the घड़ीs:
 *		MSG_FLAG_CLOCK_ALLOW_SSC: Allow this घड़ी to be modअगरied
 *		via spपढ़ो spectrum घड़ीing.
 *		MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE: Allow this घड़ी's
 *		frequency to be changed जबतक it is running so दीर्घ as it
 *		is within the min/max limits.
 *		MSG_FLAG_CLOCK_INPUT_TERM: Enable input termination, this
 *		is only applicable to घड़ी inमाला_दो on the SoC pseuकरो-device.
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy. Set to 255 अगर घड़ी ID is
 *		greater than or equal to 255.
 * @request_state: Request the state क्रम the घड़ी to be set to.
 *		MSG_CLOCK_SW_STATE_UNREQ: The IP करोes not require this घड़ी,
 *		it can be disabled, regardless of the state of the device
 *		MSG_CLOCK_SW_STATE_AUTO: Allow the System Controller to
 *		स्वतःmatically manage the state of this घड़ी. If the device
 *		is enabled, then the घड़ी is enabled. If the device is set
 *		to off or retention, then the घड़ी is पूर्णांकernally set as not
 *		being required by the device.(शेष)
 *		MSG_CLOCK_SW_STATE_REQ:  Configure the घड़ी to be enabled,
 *		regardless of the state of the device.
 * @clk_id_32:	Clock identअगरier क्रम the device क्रम this request.
 *		Only to be used अगर the घड़ी ID is greater than or equal to
 *		255.
 *
 * Normally, all required घड़ीs are managed by TISCI entity, this is used
 * only क्रम specअगरic control *IF* required. Auto managed state is
 * MSG_CLOCK_SW_STATE_AUTO, in other states, TISCI entity assume remote
 * will explicitly control.
 *
 * Request type is TI_SCI_MSG_SET_CLOCK_STATE, response is a generic
 * ACK or NACK message.
 */
काष्ठा ti_sci_msg_req_set_घड़ी_state अणु
	/* Additional hdr->flags options */
#घोषणा MSG_FLAG_CLOCK_ALLOW_SSC		TI_SCI_MSG_FLAG(8)
#घोषणा MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE	TI_SCI_MSG_FLAG(9)
#घोषणा MSG_FLAG_CLOCK_INPUT_TERM		TI_SCI_MSG_FLAG(10)
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u8 clk_id;
#घोषणा MSG_CLOCK_SW_STATE_UNREQ	0
#घोषणा MSG_CLOCK_SW_STATE_AUTO		1
#घोषणा MSG_CLOCK_SW_STATE_REQ		2
	u8 request_state;
	u32 clk_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_get_घड़ी_state - Request क्रम घड़ी state
 * @hdr:	Generic Header
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to get state of. Set to 255 अगर the घड़ी
 *		ID is greater than or equal to 255.
 * @clk_id_32:	Clock identअगरier क्रम the device क्रम the request.
 *		Only to be used अगर the घड़ी ID is greater than or equal to
 *		255.
 *
 * Request type is TI_SCI_MSG_GET_CLOCK_STATE, response is state
 * of the घड़ी
 */
काष्ठा ti_sci_msg_req_get_घड़ी_state अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u8 clk_id;
	u32 clk_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_get_घड़ी_state - Response to get घड़ी state
 * @hdr:	Generic Header
 * @programmed_state: Any programmed state of the घड़ी. This is one of
 *		MSG_CLOCK_SW_STATE* values.
 * @current_state: Current state of the घड़ी. This is one of:
 *		MSG_CLOCK_HW_STATE_NOT_READY: Clock is not पढ़ोy
 *		MSG_CLOCK_HW_STATE_READY: Clock is पढ़ोy
 *
 * Response to TI_SCI_MSG_GET_CLOCK_STATE.
 */
काष्ठा ti_sci_msg_resp_get_घड़ी_state अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 programmed_state;
#घोषणा MSG_CLOCK_HW_STATE_NOT_READY	0
#घोषणा MSG_CLOCK_HW_STATE_READY	1
	u8 current_state;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_set_घड़ी_parent - Set the घड़ी parent
 * @hdr:	Generic Header
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy. Set to 255 अगर घड़ी ID is
 *		greater than or equal to 255.
 * @parent_id:	The new घड़ी parent is selectable by an index via this
 *		parameter. Set to 255 अगर घड़ी ID is greater than or
 *		equal to 255.
 * @clk_id_32:	Clock identअगरier अगर @clk_id field is 255.
 * @parent_id_32:	Parent identअगरier अगर @parent_id is 255.
 *
 * Request type is TI_SCI_MSG_SET_CLOCK_PARENT, response is generic
 * ACK / NACK message.
 */
काष्ठा ti_sci_msg_req_set_घड़ी_parent अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u8 clk_id;
	u8 parent_id;
	u32 clk_id_32;
	u32 parent_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_get_घड़ी_parent - Get the घड़ी parent
 * @hdr:	Generic Header
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to get the parent क्रम. If this field
 *		contains 255, the actual घड़ी identअगरier is stored in
 *		@clk_id_32.
 * @clk_id_32:	Clock identअगरier अगर the @clk_id field contains 255.
 *
 * Request type is TI_SCI_MSG_GET_CLOCK_PARENT, response is parent inक्रमmation
 */
काष्ठा ti_sci_msg_req_get_घड़ी_parent अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u8 clk_id;
	u32 clk_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_get_घड़ी_parent - Response with घड़ी parent
 * @hdr:	Generic Header
 * @parent_id:	The current घड़ी parent. If set to 255, the current parent
 *		ID can be found from the @parent_id_32 field.
 * @parent_id_32:	Current घड़ी parent अगर @parent_id field is set to
 *			255.
 *
 * Response to TI_SCI_MSG_GET_CLOCK_PARENT.
 */
काष्ठा ti_sci_msg_resp_get_घड़ी_parent अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 parent_id;
	u32 parent_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_get_घड़ी_num_parents - Request to get घड़ी parents
 * @hdr:	Generic header
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request. Set to
 *		255 अगर घड़ी ID is greater than or equal to 255.
 * @clk_id_32:	Clock identअगरier अगर the @clk_id field contains 255.
 *
 * This request provides inक्रमmation about how many घड़ी parent options
 * are available क्रम a given घड़ी to a device. This is typically used
 * क्रम input घड़ीs.
 *
 * Request type is TI_SCI_MSG_GET_NUM_CLOCK_PARENTS, response is appropriate
 * message, or NACK in हाल of inability to satisfy request.
 */
काष्ठा ti_sci_msg_req_get_घड़ी_num_parents अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u8 clk_id;
	u32 clk_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_get_घड़ी_num_parents - Response क्रम get clk parents
 * @hdr:		Generic header
 * @num_parents:	Number of घड़ी parents. If set to 255, the actual
 *			number of parents is stored पूर्णांकo @num_parents_32
 *			field instead.
 * @num_parents_32:	Number of घड़ी parents अगर @num_parents field is
 *			set to 255.
 *
 * Response to TI_SCI_MSG_GET_NUM_CLOCK_PARENTS
 */
काष्ठा ti_sci_msg_resp_get_घड़ी_num_parents अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 num_parents;
	u32 num_parents_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_query_घड़ी_freq - Request to query a frequency
 * @hdr:	Generic Header
 * @dev_id:	Device identअगरier this request is क्रम
 * @min_freq_hz: The minimum allowable frequency in Hz. This is the minimum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * @target_freq_hz: The target घड़ी frequency. A frequency will be found
 *		as बंद to this target frequency as possible.
 * @max_freq_hz: The maximum allowable frequency in Hz. This is the maximum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request. Set to
 *		255 अगर घड़ी identअगरier is greater than or equal to 255.
 * @clk_id_32:	Clock identअगरier अगर @clk_id is set to 255.
 *
 * NOTE: Normally घड़ी frequency management is स्वतःmatically करोne by TISCI
 * entity. In हाल of specअगरic requests, TISCI evaluates capability to achieve
 * requested frequency within provided range and responds with
 * result message.
 *
 * Request type is TI_SCI_MSG_QUERY_CLOCK_FREQ, response is appropriate message,
 * or NACK in हाल of inability to satisfy request.
 */
काष्ठा ti_sci_msg_req_query_घड़ी_freq अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u64 min_freq_hz;
	u64 target_freq_hz;
	u64 max_freq_hz;
	u8 clk_id;
	u32 clk_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_query_घड़ी_freq - Response to a घड़ी frequency query
 * @hdr:	Generic Header
 * @freq_hz:	Frequency that is the best match in Hz.
 *
 * Response to request type TI_SCI_MSG_QUERY_CLOCK_FREQ. NOTE: अगर the request
 * cannot be satisfied, the message will be of type NACK.
 */
काष्ठा ti_sci_msg_resp_query_घड़ी_freq अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u64 freq_hz;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_set_घड़ी_freq - Request to setup a घड़ी frequency
 * @hdr:	Generic Header
 * @dev_id:	Device identअगरier this request is क्रम
 * @min_freq_hz: The minimum allowable frequency in Hz. This is the minimum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * @target_freq_hz: The target घड़ी frequency. The घड़ी will be programmed
 *		at a rate as बंद to this target frequency as possible.
 * @max_freq_hz: The maximum allowable frequency in Hz. This is the maximum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request. Set to
 *		255 अगर घड़ी ID is greater than or equal to 255.
 * @clk_id_32:	Clock identअगरier अगर @clk_id field is set to 255.
 *
 * NOTE: Normally घड़ी frequency management is स्वतःmatically करोne by TISCI
 * entity. In हाल of specअगरic requests, TISCI evaluates capability to achieve
 * requested range and responds with success/failure message.
 *
 * This sets the desired frequency क्रम a घड़ी within an allowable
 * range. This message will fail on an enabled घड़ी unless
 * MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE is set क्रम the घड़ी. Additionally,
 * अगर other घड़ीs have their frequency modअगरied due to this message,
 * they also must have the MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE or be disabled.
 *
 * Calling set frequency on a घड़ी input to the SoC pseuकरो-device will
 * inक्रमm the PMMC of that घड़ी's frequency. Setting a frequency of
 * zero will indicate the घड़ी is disabled.
 *
 * Calling set frequency on घड़ी outमाला_दो from the SoC pseuकरो-device will
 * function similarly to setting the घड़ी frequency on a device.
 *
 * Request type is TI_SCI_MSG_SET_CLOCK_FREQ, response is a generic ACK/NACK
 * message.
 */
काष्ठा ti_sci_msg_req_set_घड़ी_freq अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u64 min_freq_hz;
	u64 target_freq_hz;
	u64 max_freq_hz;
	u8 clk_id;
	u32 clk_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_get_घड़ी_freq - Request to get the घड़ी frequency
 * @hdr:	Generic Header
 * @dev_id:	Device identअगरier this request is क्रम
 * @clk_id:	Clock identअगरier क्रम the device क्रम this request. Set to
 *		255 अगर घड़ी ID is greater than or equal to 255.
 * @clk_id_32:	Clock identअगरier अगर @clk_id field is set to 255.
 *
 * NOTE: Normally घड़ी frequency management is स्वतःmatically करोne by TISCI
 * entity. In some हालs, घड़ी frequencies are configured by host.
 *
 * Request type is TI_SCI_MSG_GET_CLOCK_FREQ, responded with घड़ी frequency
 * that the घड़ी is currently at.
 */
काष्ठा ti_sci_msg_req_get_घड़ी_freq अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 dev_id;
	u8 clk_id;
	u32 clk_id_32;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_get_घड़ी_freq - Response of घड़ी frequency request
 * @hdr:	Generic Header
 * @freq_hz:	Frequency that the घड़ी is currently on, in Hz.
 *
 * Response to request type TI_SCI_MSG_GET_CLOCK_FREQ.
 */
काष्ठा ti_sci_msg_resp_get_घड़ी_freq अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u64 freq_hz;
पूर्ण __packed;

#घोषणा TI_SCI_IRQ_SECONDARY_HOST_INVALID	0xff

/**
 * काष्ठा ti_sci_msg_req_get_resource_range - Request to get a host's asचिन्हित
 *					      range of resources.
 * @hdr:		Generic Header
 * @type:		Unique resource assignment type
 * @subtype:		Resource assignment subtype within the resource type.
 * @secondary_host:	Host processing entity to which the resources are
 *			allocated. This is required only when the destination
 *			host id id dअगरferent from ti sci पूर्णांकerface host id,
 *			अन्यथा TI_SCI_IRQ_SECONDARY_HOST_INVALID can be passed.
 *
 * Request type is TI_SCI_MSG_GET_RESOURCE_RANGE. Responded with requested
 * resource range which is of type TI_SCI_MSG_GET_RESOURCE_RANGE.
 */
काष्ठा ti_sci_msg_req_get_resource_range अणु
	काष्ठा ti_sci_msg_hdr hdr;
#घोषणा MSG_RM_RESOURCE_TYPE_MASK	GENMASK(9, 0)
#घोषणा MSG_RM_RESOURCE_SUBTYPE_MASK	GENMASK(5, 0)
	u16 type;
	u8 subtype;
	u8 secondary_host;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_get_resource_range - Response to resource get range.
 * @hdr:		Generic Header
 * @range_start:	Start index of the first resource range.
 * @range_num:		Number of resources in the first range.
 * @range_start_sec:	Start index of the second resource range.
 * @range_num_sec:	Number of resources in the second range.
 *
 * Response to request TI_SCI_MSG_GET_RESOURCE_RANGE.
 */
काष्ठा ti_sci_msg_resp_get_resource_range अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u16 range_start;
	u16 range_num;
	u16 range_start_sec;
	u16 range_num_sec;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_manage_irq - Request to configure/release the route
 *					between the dev and the host.
 * @hdr:		Generic Header
 * @valid_params:	Bit fields defining the validity of पूर्णांकerrupt source
 *			parameters. If a bit is not set, then corresponding
 *			field is not valid and will not be used क्रम route set.
 *			Bit field definitions:
 *			0 - Valid bit क्रम @dst_id
 *			1 - Valid bit क्रम @dst_host_irq
 *			2 - Valid bit क्रम @ia_id
 *			3 - Valid bit क्रम @vपूर्णांक
 *			4 - Valid bit क्रम @global_event
 *			5 - Valid bit क्रम @vपूर्णांक_status_bit_index
 *			31 - Valid bit क्रम @secondary_host
 * @src_id:		IRQ source peripheral ID.
 * @src_index:		IRQ source index within the peripheral
 * @dst_id:		IRQ Destination ID. Based on the architecture it can be
 *			IRQ controller or host processor ID.
 * @dst_host_irq:	IRQ number of the destination host IRQ controller
 * @ia_id:		Device ID of the पूर्णांकerrupt aggregator in which the
 *			vपूर्णांक resides.
 * @vपूर्णांक:		Virtual पूर्णांकerrupt number अगर the पूर्णांकerrupt route
 *			is through an पूर्णांकerrupt aggregator.
 * @global_event:	Global event that is to be mapped to पूर्णांकerrupt
 *			aggregator भव पूर्णांकerrupt status bit.
 * @vपूर्णांक_status_bit:	Virtual पूर्णांकerrupt status bit अगर the पूर्णांकerrupt route
 *			utilizes an पूर्णांकerrupt aggregator status bit.
 * @secondary_host:	Host ID of the IRQ destination computing entity. This is
 *			required only when destination host id is dअगरferent
 *			from ti sci पूर्णांकerface host id.
 *
 * Request type is TI_SCI_MSG_SET/RELEASE_IRQ.
 * Response is generic ACK / NACK message.
 */
काष्ठा ti_sci_msg_req_manage_irq अणु
	काष्ठा ti_sci_msg_hdr hdr;
#घोषणा MSG_FLAG_DST_ID_VALID			TI_SCI_MSG_FLAG(0)
#घोषणा MSG_FLAG_DST_HOST_IRQ_VALID		TI_SCI_MSG_FLAG(1)
#घोषणा MSG_FLAG_IA_ID_VALID			TI_SCI_MSG_FLAG(2)
#घोषणा MSG_FLAG_VINT_VALID			TI_SCI_MSG_FLAG(3)
#घोषणा MSG_FLAG_GLB_EVNT_VALID			TI_SCI_MSG_FLAG(4)
#घोषणा MSG_FLAG_VINT_STS_BIT_VALID		TI_SCI_MSG_FLAG(5)
#घोषणा MSG_FLAG_SHOST_VALID			TI_SCI_MSG_FLAG(31)
	u32 valid_params;
	u16 src_id;
	u16 src_index;
	u16 dst_id;
	u16 dst_host_irq;
	u16 ia_id;
	u16 vपूर्णांक;
	u16 global_event;
	u8 vपूर्णांक_status_bit;
	u8 secondary_host;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_rm_ring_cfg_req - Configure a Navigator Subप्रणाली ring
 *
 * Configures the non-real-समय रेजिस्टरs of a Navigator Subप्रणाली ring.
 * @hdr:	Generic Header
 * @valid_params: Bitfield defining validity of ring configuration parameters.
 *	The ring configuration fields are not valid, and will not be used क्रम
 *	ring configuration, अगर their corresponding valid bit is zero.
 *	Valid bit usage:
 *	0 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req addr_lo
 *	1 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req addr_hi
 *	2 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req count
 *	3 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req mode
 *	4 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req size
 *	5 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req order_id
 *	6 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req virtid
 *	7 - Valid bit क्रम @tisci_msg_rm_ring_cfg_req ASEL
 * @nav_id: Device ID of Navigator Subप्रणाली from which the ring is allocated
 * @index: ring index to be configured.
 * @addr_lo: 32 LSBs of ring base address to be programmed पूर्णांकo the ring's
 *	RING_BA_LO रेजिस्टर
 * @addr_hi: 16 MSBs of ring base address to be programmed पूर्णांकo the ring's
 *	RING_BA_HI रेजिस्टर.
 * @count: Number of ring elements. Must be even अगर mode is CREDENTIALS or QM
 *	modes.
 * @mode: Specअगरies the mode the ring is to be configured.
 * @size: Specअगरies encoded ring element size. To calculate the encoded size use
 *	the क्रमmula (log2(size_bytes) - 2), where size_bytes cannot be
 *	greater than 256.
 * @order_id: Specअगरies the ring's bus order ID.
 * @virtid: Ring virt ID value
 * @asel: Ring ASEL (address select) value to be set पूर्णांकo the ASEL field of the
 *	ring's RING_BA_HI रेजिस्टर.
 */
काष्ठा ti_sci_msg_rm_ring_cfg_req अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 valid_params;
	u16 nav_id;
	u16 index;
	u32 addr_lo;
	u32 addr_hi;
	u32 count;
	u8 mode;
	u8 size;
	u8 order_id;
	u16 virtid;
	u8 asel;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_psil_pair - Pairs a PSI-L source thपढ़ो to a destination
 *				 thपढ़ो
 * @hdr:	Generic Header
 * @nav_id:	SoC Navigator Subप्रणाली device ID whose PSI-L config proxy is
 *		used to pair the source and destination thपढ़ोs.
 * @src_thपढ़ो:	PSI-L source thपढ़ो ID within the PSI-L System thपढ़ो map.
 *
 * UDMAP transmit channels mapped to source thपढ़ोs will have their
 * TCHAN_THRD_ID रेजिस्टर programmed with the destination thपढ़ो अगर the pairing
 * is successful.

 * @dst_thपढ़ो: PSI-L destination thपढ़ो ID within the PSI-L System thपढ़ो map.
 * PSI-L destination thपढ़ोs start at index 0x8000.  The request is NACK'd अगर
 * the destination thपढ़ो is not greater than or equal to 0x8000.
 *
 * UDMAP receive channels mapped to destination thपढ़ोs will have their
 * RCHAN_THRD_ID रेजिस्टर programmed with the source thपढ़ो अगर the pairing
 * is successful.
 *
 * Request type is TI_SCI_MSG_RM_PSIL_PAIR, response is a generic ACK or NACK
 * message.
 */
काष्ठा ti_sci_msg_psil_pair अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 nav_id;
	u32 src_thपढ़ो;
	u32 dst_thपढ़ो;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_psil_unpair - Unpairs a PSI-L source thपढ़ो from a
 *				   destination thपढ़ो
 * @hdr:	Generic Header
 * @nav_id:	SoC Navigator Subप्रणाली device ID whose PSI-L config proxy is
 *		used to unpair the source and destination thपढ़ोs.
 * @src_thपढ़ो:	PSI-L source thपढ़ो ID within the PSI-L System thपढ़ो map.
 *
 * UDMAP transmit channels mapped to source thपढ़ोs will have their
 * TCHAN_THRD_ID रेजिस्टर cleared अगर the unpairing is successful.
 *
 * @dst_thपढ़ो: PSI-L destination thपढ़ो ID within the PSI-L System thपढ़ो map.
 * PSI-L destination thपढ़ोs start at index 0x8000.  The request is NACK'd अगर
 * the destination thपढ़ो is not greater than or equal to 0x8000.
 *
 * UDMAP receive channels mapped to destination thपढ़ोs will have their
 * RCHAN_THRD_ID रेजिस्टर cleared अगर the unpairing is successful.
 *
 * Request type is TI_SCI_MSG_RM_PSIL_UNPAIR, response is a generic ACK or NACK
 * message.
 */
काष्ठा ti_sci_msg_psil_unpair अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 nav_id;
	u32 src_thपढ़ो;
	u32 dst_thपढ़ो;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_udmap_rx_flow_cfg -  UDMAP receive flow configuration
 *					  message
 * @hdr: Generic Header
 * @nav_id: SoC Navigator Subप्रणाली device ID from which the receive flow is
 *	allocated
 * @flow_index: UDMAP receive flow index क्रम non-optional configuration.
 * @rx_ch_index: Specअगरies the index of the receive channel using the flow_index
 * @rx_einfo_present: UDMAP receive flow extended packet info present.
 * @rx_psinfo_present: UDMAP receive flow PS words present.
 * @rx_error_handling: UDMAP receive flow error handling configuration. Valid
 *	values are TI_SCI_RM_UDMAP_RX_FLOW_ERR_DROP/RETRY.
 * @rx_desc_type: UDMAP receive flow descriptor type. It can be one of
 *	TI_SCI_RM_UDMAP_RX_FLOW_DESC_HOST/MONO.
 * @rx_sop_offset: UDMAP receive flow start of packet offset.
 * @rx_dest_qnum: UDMAP receive flow destination queue number.
 * @rx_ps_location: UDMAP receive flow PS words location.
 *	0 - end of packet descriptor
 *	1 - Beginning of the data buffer
 * @rx_src_tag_hi: UDMAP receive flow source tag high byte स्थिरant
 * @rx_src_tag_lo: UDMAP receive flow source tag low byte स्थिरant
 * @rx_dest_tag_hi: UDMAP receive flow destination tag high byte स्थिरant
 * @rx_dest_tag_lo: UDMAP receive flow destination tag low byte स्थिरant
 * @rx_src_tag_hi_sel: UDMAP receive flow source tag high byte selector
 * @rx_src_tag_lo_sel: UDMAP receive flow source tag low byte selector
 * @rx_dest_tag_hi_sel: UDMAP receive flow destination tag high byte selector
 * @rx_dest_tag_lo_sel: UDMAP receive flow destination tag low byte selector
 * @rx_माप_प्रकारhresh_en: UDMAP receive flow packet size based मुक्त buffer queue
 *	enable. If enabled, the ti_sci_rm_udmap_rx_flow_opt_cfg also need to be
 *	configured and sent.
 * @rx_fdq0_sz0_qnum: UDMAP receive flow मुक्त descriptor queue 0.
 * @rx_fdq1_qnum: UDMAP receive flow मुक्त descriptor queue 1.
 * @rx_fdq2_qnum: UDMAP receive flow मुक्त descriptor queue 2.
 * @rx_fdq3_qnum: UDMAP receive flow मुक्त descriptor queue 3.
 *
 * For detailed inक्रमmation on the settings, see the UDMAP section of the TRM.
 */
काष्ठा ti_sci_msg_udmap_rx_flow_cfg अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 nav_id;
	u32 flow_index;
	u32 rx_ch_index;
	u8 rx_einfo_present;
	u8 rx_psinfo_present;
	u8 rx_error_handling;
	u8 rx_desc_type;
	u16 rx_sop_offset;
	u16 rx_dest_qnum;
	u8 rx_ps_location;
	u8 rx_src_tag_hi;
	u8 rx_src_tag_lo;
	u8 rx_dest_tag_hi;
	u8 rx_dest_tag_lo;
	u8 rx_src_tag_hi_sel;
	u8 rx_src_tag_lo_sel;
	u8 rx_dest_tag_hi_sel;
	u8 rx_dest_tag_lo_sel;
	u8 rx_माप_प्रकारhresh_en;
	u16 rx_fdq0_sz0_qnum;
	u16 rx_fdq1_qnum;
	u16 rx_fdq2_qnum;
	u16 rx_fdq3_qnum;
पूर्ण __packed;

/**
 * काष्ठा rm_ti_sci_msg_udmap_rx_flow_opt_cfg - parameters क्रम UDMAP receive
 *						flow optional configuration
 * @hdr: Generic Header
 * @nav_id: SoC Navigator Subप्रणाली device ID from which the receive flow is
 *	allocated
 * @flow_index: UDMAP receive flow index क्रम optional configuration.
 * @rx_ch_index: Specअगरies the index of the receive channel using the flow_index
 * @rx_माप_प्रकारhresh0: UDMAP receive flow packet size threshold 0.
 * @rx_माप_प्रकारhresh1: UDMAP receive flow packet size threshold 1.
 * @rx_माप_प्रकारhresh2: UDMAP receive flow packet size threshold 2.
 * @rx_fdq0_sz1_qnum: UDMAP receive flow मुक्त descriptor queue क्रम size
 *	threshold 1.
 * @rx_fdq0_sz2_qnum: UDMAP receive flow मुक्त descriptor queue क्रम size
 *	threshold 2.
 * @rx_fdq0_sz3_qnum: UDMAP receive flow मुक्त descriptor queue क्रम size
 *	threshold 3.
 *
 * For detailed inक्रमmation on the settings, see the UDMAP section of the TRM.
 */
काष्ठा rm_ti_sci_msg_udmap_rx_flow_opt_cfg अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 nav_id;
	u32 flow_index;
	u32 rx_ch_index;
	u16 rx_माप_प्रकारhresh0;
	u16 rx_माप_प्रकारhresh1;
	u16 rx_माप_प्रकारhresh2;
	u16 rx_fdq0_sz1_qnum;
	u16 rx_fdq0_sz2_qnum;
	u16 rx_fdq0_sz3_qnum;
पूर्ण __packed;

/**
 * Configures a Navigator Subप्रणाली UDMAP transmit channel
 *
 * Configures the non-real-समय रेजिस्टरs of a Navigator Subप्रणाली UDMAP
 * transmit channel.  The channel index must be asचिन्हित to the host defined
 * in the TISCI header via the RM board configuration resource assignment
 * range list.
 *
 * @hdr: Generic Header
 *
 * @valid_params: Bitfield defining validity of tx channel configuration
 * parameters. The tx channel configuration fields are not valid, and will not
 * be used क्रम ch configuration, अगर their corresponding valid bit is zero.
 * Valid bit usage:
 *    0 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_छोड़ो_on_err
 *    1 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_atype
 *    2 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_chan_type
 *    3 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_fetch_size
 *    4 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::txcq_qnum
 *    5 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_priority
 *    6 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_qos
 *    7 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_orderid
 *    8 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_sched_priority
 *    9 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_filt_einfo
 *   10 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_filt_pswords
 *   11 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_supr_tdpkt
 *   12 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_credit_count
 *   13 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::fdepth
 *   14 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_burst_size
 *   15 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::tx_tdtype
 *   16 - Valid bit क्रम @ref ti_sci_msg_rm_udmap_tx_ch_cfg::extended_ch_type
 *
 * @nav_id: SoC device ID of Navigator Subप्रणाली where tx channel is located
 *
 * @index: UDMAP transmit channel index.
 *
 * @tx_छोड़ो_on_err: UDMAP transmit channel छोड़ो on error configuration to
 * be programmed पूर्णांकo the tx_छोड़ो_on_err field of the channel's TCHAN_TCFG
 * रेजिस्टर.
 *
 * @tx_filt_einfo: UDMAP transmit channel extended packet inक्रमmation passing
 * configuration to be programmed पूर्णांकo the tx_filt_einfo field of the
 * channel's TCHAN_TCFG रेजिस्टर.
 *
 * @tx_filt_pswords: UDMAP transmit channel protocol specअगरic word passing
 * configuration to be programmed पूर्णांकo the tx_filt_pswords field of the
 * channel's TCHAN_TCFG रेजिस्टर.
 *
 * @tx_atype: UDMAP transmit channel non Ring Accelerator access poपूर्णांकer
 * पूर्णांकerpretation configuration to be programmed पूर्णांकo the tx_atype field of
 * the channel's TCHAN_TCFG रेजिस्टर.
 *
 * @tx_chan_type: UDMAP transmit channel functional channel type and work
 * passing mechanism configuration to be programmed पूर्णांकo the tx_chan_type
 * field of the channel's TCHAN_TCFG रेजिस्टर.
 *
 * @tx_supr_tdpkt: UDMAP transmit channel tearकरोwn packet generation suppression
 * configuration to be programmed पूर्णांकo the tx_supr_tdpkt field of the channel's
 * TCHAN_TCFG रेजिस्टर.
 *
 * @tx_fetch_size: UDMAP transmit channel number of 32-bit descriptor words to
 * fetch configuration to be programmed पूर्णांकo the tx_fetch_size field of the
 * channel's TCHAN_TCFG रेजिस्टर.  The user must make sure to set the maximum
 * word count that can pass through the channel क्रम any allowed descriptor type.
 *
 * @tx_credit_count: UDMAP transmit channel transfer request credit count
 * configuration to be programmed पूर्णांकo the count field of the TCHAN_TCREDIT
 * रेजिस्टर.  Specअगरies how many credits क्रम complete TRs are available.
 *
 * @txcq_qnum: UDMAP transmit channel completion queue configuration to be
 * programmed पूर्णांकo the txcq_qnum field of the TCHAN_TCQ रेजिस्टर. The specअगरied
 * completion queue must be asचिन्हित to the host, or a subordinate of the host,
 * requesting configuration of the transmit channel.
 *
 * @tx_priority: UDMAP transmit channel transmit priority value to be programmed
 * पूर्णांकo the priority field of the channel's TCHAN_TPRI_CTRL रेजिस्टर.
 *
 * @tx_qos: UDMAP transmit channel transmit qos value to be programmed पूर्णांकo the
 * qos field of the channel's TCHAN_TPRI_CTRL रेजिस्टर.
 *
 * @tx_orderid: UDMAP transmit channel bus order id value to be programmed पूर्णांकo
 * the orderid field of the channel's TCHAN_TPRI_CTRL रेजिस्टर.
 *
 * @fdepth: UDMAP transmit channel FIFO depth configuration to be programmed
 * पूर्णांकo the fdepth field of the TCHAN_TFIFO_DEPTH रेजिस्टर. Sets the number of
 * Tx FIFO bytes which are allowed to be stored क्रम the channel. Check the UDMAP
 * section of the TRM क्रम restrictions regarding this parameter.
 *
 * @tx_sched_priority: UDMAP transmit channel tx scheduling priority
 * configuration to be programmed पूर्णांकo the priority field of the channel's
 * TCHAN_TST_SCHED रेजिस्टर.
 *
 * @tx_burst_size: UDMAP transmit channel burst size configuration to be
 * programmed पूर्णांकo the tx_burst_size field of the TCHAN_TCFG रेजिस्टर.
 *
 * @tx_tdtype: UDMAP transmit channel tearकरोwn type configuration to be
 * programmed पूर्णांकo the tdtype field of the TCHAN_TCFG रेजिस्टर:
 * 0 - Return immediately
 * 1 - Wait क्रम completion message from remote peer
 *
 * @extended_ch_type: Valid क्रम BCDMA.
 * 0 - the channel is split tx channel (tchan)
 * 1 - the channel is block copy channel (bchan)
 */
काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg_req अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 valid_params;
	u16 nav_id;
	u16 index;
	u8 tx_छोड़ो_on_err;
	u8 tx_filt_einfo;
	u8 tx_filt_pswords;
	u8 tx_atype;
	u8 tx_chan_type;
	u8 tx_supr_tdpkt;
	u16 tx_fetch_size;
	u8 tx_credit_count;
	u16 txcq_qnum;
	u8 tx_priority;
	u8 tx_qos;
	u8 tx_orderid;
	u16 fdepth;
	u8 tx_sched_priority;
	u8 tx_burst_size;
	u8 tx_tdtype;
	u8 extended_ch_type;
पूर्ण __packed;

/**
 * Configures a Navigator Subप्रणाली UDMAP receive channel
 *
 * Configures the non-real-समय रेजिस्टरs of a Navigator Subप्रणाली UDMAP
 * receive channel.  The channel index must be asचिन्हित to the host defined
 * in the TISCI header via the RM board configuration resource assignment
 * range list.
 *
 * @hdr: Generic Header
 *
 * @valid_params: Bitfield defining validity of rx channel configuration
 * parameters.
 * The rx channel configuration fields are not valid, and will not be used क्रम
 * ch configuration, अगर their corresponding valid bit is zero.
 * Valid bit usage:
 *    0 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_छोड़ो_on_err
 *    1 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_atype
 *    2 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type
 *    3 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_fetch_size
 *    4 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rxcq_qnum
 *    5 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_priority
 *    6 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_qos
 *    7 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_orderid
 *    8 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_sched_priority
 *    9 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::flowid_start
 *   10 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::flowid_cnt
 *   11 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_लघु
 *   12 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_दीर्घ
 *   14 - Valid bit क्रम @ti_sci_msg_rm_udmap_rx_ch_cfg_req::rx_burst_size
 *
 * @nav_id: SoC device ID of Navigator Subप्रणाली where rx channel is located
 *
 * @index: UDMAP receive channel index.
 *
 * @rx_fetch_size: UDMAP receive channel number of 32-bit descriptor words to
 * fetch configuration to be programmed पूर्णांकo the rx_fetch_size field of the
 * channel's RCHAN_RCFG रेजिस्टर.
 *
 * @rxcq_qnum: UDMAP receive channel completion queue configuration to be
 * programmed पूर्णांकo the rxcq_qnum field of the RCHAN_RCQ रेजिस्टर.
 * The specअगरied completion queue must be asचिन्हित to the host, or a subordinate
 * of the host, requesting configuration of the receive channel.
 *
 * @rx_priority: UDMAP receive channel receive priority value to be programmed
 * पूर्णांकo the priority field of the channel's RCHAN_RPRI_CTRL रेजिस्टर.
 *
 * @rx_qos: UDMAP receive channel receive qos value to be programmed पूर्णांकo the
 * qos field of the channel's RCHAN_RPRI_CTRL रेजिस्टर.
 *
 * @rx_orderid: UDMAP receive channel bus order id value to be programmed पूर्णांकo
 * the orderid field of the channel's RCHAN_RPRI_CTRL रेजिस्टर.
 *
 * @rx_sched_priority: UDMAP receive channel rx scheduling priority
 * configuration to be programmed पूर्णांकo the priority field of the channel's
 * RCHAN_RST_SCHED रेजिस्टर.
 *
 * @flowid_start: UDMAP receive channel additional flows starting index
 * configuration to program पूर्णांकo the flow_start field of the RCHAN_RFLOW_RNG
 * रेजिस्टर. Specअगरies the starting index क्रम flow IDs the receive channel is to
 * make use of beyond the शेष flow. flowid_start and @ref flowid_cnt must be
 * set as valid and configured together. The starting flow ID set by
 * @ref flowid_cnt must be a flow index within the Navigator Subप्रणाली's subset
 * of flows beyond the शेष flows अटलally mapped to receive channels.
 * The additional flows must be asचिन्हित to the host, or a subordinate of the
 * host, requesting configuration of the receive channel.
 *
 * @flowid_cnt: UDMAP receive channel additional flows count configuration to
 * program पूर्णांकo the flowid_cnt field of the RCHAN_RFLOW_RNG रेजिस्टर.
 * This field specअगरies how many flow IDs are in the additional contiguous range
 * of legal flow IDs क्रम the channel.  @ref flowid_start and flowid_cnt must be
 * set as valid and configured together. Disabling the valid_params field bit
 * क्रम flowid_cnt indicates no flow IDs other than the शेष are to be
 * allocated and used by the receive channel. @ref flowid_start plus flowid_cnt
 * cannot be greater than the number of receive flows in the receive channel's
 * Navigator Subप्रणाली.  The additional flows must be asचिन्हित to the host, or a
 * subordinate of the host, requesting configuration of the receive channel.
 *
 * @rx_छोड़ो_on_err: UDMAP receive channel छोड़ो on error configuration to be
 * programmed पूर्णांकo the rx_छोड़ो_on_err field of the channel's RCHAN_RCFG
 * रेजिस्टर.
 *
 * @rx_atype: UDMAP receive channel non Ring Accelerator access poपूर्णांकer
 * पूर्णांकerpretation configuration to be programmed पूर्णांकo the rx_atype field of the
 * channel's RCHAN_RCFG रेजिस्टर.
 *
 * @rx_chan_type: UDMAP receive channel functional channel type and work passing
 * mechanism configuration to be programmed पूर्णांकo the rx_chan_type field of the
 * channel's RCHAN_RCFG रेजिस्टर.
 *
 * @rx_ignore_लघु: UDMAP receive channel लघु packet treaपंचांगent configuration
 * to be programmed पूर्णांकo the rx_ignore_लघु field of the RCHAN_RCFG रेजिस्टर.
 *
 * @rx_ignore_दीर्घ: UDMAP receive channel दीर्घ packet treaपंचांगent configuration to
 * be programmed पूर्णांकo the rx_ignore_दीर्घ field of the RCHAN_RCFG रेजिस्टर.
 *
 * @rx_burst_size: UDMAP receive channel burst size configuration to be
 * programmed पूर्णांकo the rx_burst_size field of the RCHAN_RCFG रेजिस्टर.
 */
काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg_req अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 valid_params;
	u16 nav_id;
	u16 index;
	u16 rx_fetch_size;
	u16 rxcq_qnum;
	u8 rx_priority;
	u8 rx_qos;
	u8 rx_orderid;
	u8 rx_sched_priority;
	u16 flowid_start;
	u16 flowid_cnt;
	u8 rx_छोड़ो_on_err;
	u8 rx_atype;
	u8 rx_chan_type;
	u8 rx_ignore_लघु;
	u8 rx_ignore_दीर्घ;
	u8 rx_burst_size;
पूर्ण __packed;

/**
 * Configures a Navigator Subप्रणाली UDMAP receive flow
 *
 * Configures a Navigator Subप्रणाली UDMAP receive flow's रेजिस्टरs.
 * Configuration करोes not include the flow रेजिस्टरs which handle size-based
 * मुक्त descriptor queue routing.
 *
 * The flow index must be asचिन्हित to the host defined in the TISCI header via
 * the RM board configuration resource assignment range list.
 *
 * @hdr: Standard TISCI header
 *
 * @valid_params
 * Bitfield defining validity of rx flow configuration parameters.  The
 * rx flow configuration fields are not valid, and will not be used क्रम flow
 * configuration, अगर their corresponding valid bit is zero.  Valid bit usage:
 *     0 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_einfo_present
 *     1 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_psinfo_present
 *     2 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_error_handling
 *     3 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_desc_type
 *     4 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_sop_offset
 *     5 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_dest_qnum
 *     6 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi
 *     7 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo
 *     8 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi
 *     9 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo
 *    10 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi_sel
 *    11 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo_sel
 *    12 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi_sel
 *    13 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo_sel
 *    14 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_fdq0_sz0_qnum
 *    15 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_fdq1_sz0_qnum
 *    16 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_fdq2_sz0_qnum
 *    17 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_fdq3_sz0_qnum
 *    18 - Valid bit क्रम @tisci_msg_rm_udmap_flow_cfg_req::rx_ps_location
 *
 * @nav_id: SoC device ID of Navigator Subप्रणाली from which the receive flow is
 * allocated
 *
 * @flow_index: UDMAP receive flow index क्रम non-optional configuration.
 *
 * @rx_einfo_present:
 * UDMAP receive flow extended packet info present configuration to be
 * programmed पूर्णांकo the rx_einfo_present field of the flow's RFLOW_RFA रेजिस्टर.
 *
 * @rx_psinfo_present:
 * UDMAP receive flow PS words present configuration to be programmed पूर्णांकo the
 * rx_psinfo_present field of the flow's RFLOW_RFA रेजिस्टर.
 *
 * @rx_error_handling:
 * UDMAP receive flow error handling configuration to be programmed पूर्णांकo the
 * rx_error_handling field of the flow's RFLOW_RFA रेजिस्टर.
 *
 * @rx_desc_type:
 * UDMAP receive flow descriptor type configuration to be programmed पूर्णांकo the
 * rx_desc_type field field of the flow's RFLOW_RFA रेजिस्टर.
 *
 * @rx_sop_offset:
 * UDMAP receive flow start of packet offset configuration to be programmed
 * पूर्णांकo the rx_sop_offset field of the RFLOW_RFA रेजिस्टर.  See the UDMAP
 * section of the TRM क्रम more inक्रमmation on this setting.  Valid values क्रम
 * this field are 0-255 bytes.
 *
 * @rx_dest_qnum:
 * UDMAP receive flow destination queue configuration to be programmed पूर्णांकo the
 * rx_dest_qnum field of the flow's RFLOW_RFA रेजिस्टर.  The specअगरied
 * destination queue must be valid within the Navigator Subप्रणाली and must be
 * owned by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * @rx_src_tag_hi:
 * UDMAP receive flow source tag high byte स्थिरant configuration to be
 * programmed पूर्णांकo the rx_src_tag_hi field of the flow's RFLOW_RFB रेजिस्टर.
 * See the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_src_tag_lo:
 * UDMAP receive flow source tag low byte स्थिरant configuration to be
 * programmed पूर्णांकo the rx_src_tag_lo field of the flow's RFLOW_RFB रेजिस्टर.
 * See the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_dest_tag_hi:
 * UDMAP receive flow destination tag high byte स्थिरant configuration to be
 * programmed पूर्णांकo the rx_dest_tag_hi field of the flow's RFLOW_RFB रेजिस्टर.
 * See the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_dest_tag_lo:
 * UDMAP receive flow destination tag low byte स्थिरant configuration to be
 * programmed पूर्णांकo the rx_dest_tag_lo field of the flow's RFLOW_RFB रेजिस्टर.
 * See the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_src_tag_hi_sel:
 * UDMAP receive flow source tag high byte selector configuration to be
 * programmed पूर्णांकo the rx_src_tag_hi_sel field of the RFLOW_RFC रेजिस्टर.  See
 * the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_src_tag_lo_sel:
 * UDMAP receive flow source tag low byte selector configuration to be
 * programmed पूर्णांकo the rx_src_tag_lo_sel field of the RFLOW_RFC रेजिस्टर.  See
 * the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_dest_tag_hi_sel:
 * UDMAP receive flow destination tag high byte selector configuration to be
 * programmed पूर्णांकo the rx_dest_tag_hi_sel field of the RFLOW_RFC रेजिस्टर.  See
 * the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_dest_tag_lo_sel:
 * UDMAP receive flow destination tag low byte selector configuration to be
 * programmed पूर्णांकo the rx_dest_tag_lo_sel field of the RFLOW_RFC रेजिस्टर.  See
 * the UDMAP section of the TRM क्रम more inक्रमmation on this setting.
 *
 * @rx_fdq0_sz0_qnum:
 * UDMAP receive flow मुक्त descriptor queue 0 configuration to be programmed
 * पूर्णांकo the rx_fdq0_sz0_qnum field of the flow's RFLOW_RFD रेजिस्टर.  See the
 * UDMAP section of the TRM क्रम more inक्रमmation on this setting. The specअगरied
 * मुक्त queue must be valid within the Navigator Subप्रणाली and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * @rx_fdq1_qnum:
 * UDMAP receive flow मुक्त descriptor queue 1 configuration to be programmed
 * पूर्णांकo the rx_fdq1_qnum field of the flow's RFLOW_RFD रेजिस्टर.  See the
 * UDMAP section of the TRM क्रम more inक्रमmation on this setting.  The specअगरied
 * मुक्त queue must be valid within the Navigator Subप्रणाली and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * @rx_fdq2_qnum:
 * UDMAP receive flow मुक्त descriptor queue 2 configuration to be programmed
 * पूर्णांकo the rx_fdq2_qnum field of the flow's RFLOW_RFE रेजिस्टर.  See the
 * UDMAP section of the TRM क्रम more inक्रमmation on this setting.  The specअगरied
 * मुक्त queue must be valid within the Navigator Subप्रणाली and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * @rx_fdq3_qnum:
 * UDMAP receive flow मुक्त descriptor queue 3 configuration to be programmed
 * पूर्णांकo the rx_fdq3_qnum field of the flow's RFLOW_RFE रेजिस्टर.  See the
 * UDMAP section of the TRM क्रम more inक्रमmation on this setting.  The specअगरied
 * मुक्त queue must be valid within the Navigator Subप्रणाली and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * @rx_ps_location:
 * UDMAP receive flow PS words location configuration to be programmed पूर्णांकo the
 * rx_ps_location field of the flow's RFLOW_RFA रेजिस्टर.
 */
काष्ठा ti_sci_msg_rm_udmap_flow_cfg_req अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u32 valid_params;
	u16 nav_id;
	u16 flow_index;
	u8 rx_einfo_present;
	u8 rx_psinfo_present;
	u8 rx_error_handling;
	u8 rx_desc_type;
	u16 rx_sop_offset;
	u16 rx_dest_qnum;
	u8 rx_src_tag_hi;
	u8 rx_src_tag_lo;
	u8 rx_dest_tag_hi;
	u8 rx_dest_tag_lo;
	u8 rx_src_tag_hi_sel;
	u8 rx_src_tag_lo_sel;
	u8 rx_dest_tag_hi_sel;
	u8 rx_dest_tag_lo_sel;
	u16 rx_fdq0_sz0_qnum;
	u16 rx_fdq1_qnum;
	u16 rx_fdq2_qnum;
	u16 rx_fdq3_qnum;
	u8 rx_ps_location;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_proc_request - Request a processor
 * @hdr:		Generic Header
 * @processor_id:	ID of processor being requested
 *
 * Request type is TI_SCI_MSG_PROC_REQUEST, response is a generic ACK/NACK
 * message.
 */
काष्ठा ti_sci_msg_req_proc_request अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 processor_id;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_proc_release - Release a processor
 * @hdr:		Generic Header
 * @processor_id:	ID of processor being released
 *
 * Request type is TI_SCI_MSG_PROC_RELEASE, response is a generic ACK/NACK
 * message.
 */
काष्ठा ti_sci_msg_req_proc_release अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 processor_id;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_proc_hanकरोver - Hanकरोver a processor to a host
 * @hdr:		Generic Header
 * @processor_id:	ID of processor being handed over
 * @host_id:		Host ID the control needs to be transferred to
 *
 * Request type is TI_SCI_MSG_PROC_HANDOVER, response is a generic ACK/NACK
 * message.
 */
काष्ठा ti_sci_msg_req_proc_hanकरोver अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 processor_id;
	u8 host_id;
पूर्ण __packed;

/* Boot Vector masks */
#घोषणा TI_SCI_ADDR_LOW_MASK			GENMASK_ULL(31, 0)
#घोषणा TI_SCI_ADDR_HIGH_MASK			GENMASK_ULL(63, 32)
#घोषणा TI_SCI_ADDR_HIGH_SHIFT			32

/**
 * काष्ठा ti_sci_msg_req_set_config - Set Processor boot configuration
 * @hdr:		Generic Header
 * @processor_id:	ID of processor being configured
 * @bootvector_low:	Lower 32 bit address (Little Endian) of boot vector
 * @bootvector_high:	Higher 32 bit address (Little Endian) of boot vector
 * @config_flags_set:	Optional Processor specअगरic Config Flags to set.
 *			Setting a bit here implies the corresponding mode
 *			will be set
 * @config_flags_clear:	Optional Processor specअगरic Config Flags to clear.
 *			Setting a bit here implies the corresponding mode
 *			will be cleared
 *
 * Request type is TI_SCI_MSG_PROC_HANDOVER, response is a generic ACK/NACK
 * message.
 */
काष्ठा ti_sci_msg_req_set_config अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 processor_id;
	u32 bootvector_low;
	u32 bootvector_high;
	u32 config_flags_set;
	u32 config_flags_clear;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_set_ctrl - Set Processor boot control flags
 * @hdr:		Generic Header
 * @processor_id:	ID of processor being configured
 * @control_flags_set:	Optional Processor specअगरic Control Flags to set.
 *			Setting a bit here implies the corresponding mode
 *			will be set
 * @control_flags_clear:Optional Processor specअगरic Control Flags to clear.
 *			Setting a bit here implies the corresponding mode
 *			will be cleared
 *
 * Request type is TI_SCI_MSG_SET_CTRL, response is a generic ACK/NACK
 * message.
 */
काष्ठा ti_sci_msg_req_set_ctrl अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 processor_id;
	u32 control_flags_set;
	u32 control_flags_clear;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_req_get_status - Processor boot status request
 * @hdr:		Generic Header
 * @processor_id:	ID of processor whose status is being requested
 *
 * Request type is TI_SCI_MSG_GET_STATUS, response is an appropriate
 * message, or NACK in हाल of inability to satisfy request.
 */
काष्ठा ti_sci_msg_req_get_status अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 processor_id;
पूर्ण __packed;

/**
 * काष्ठा ti_sci_msg_resp_get_status - Processor boot status response
 * @hdr:		Generic Header
 * @processor_id:	ID of processor whose status is वापसed
 * @bootvector_low:	Lower 32 bit address (Little Endian) of boot vector
 * @bootvector_high:	Higher 32 bit address (Little Endian) of boot vector
 * @config_flags:	Optional Processor specअगरic Config Flags set currently
 * @control_flags:	Optional Processor specअगरic Control Flags set currently
 * @status_flags:	Optional Processor specअगरic Status Flags set currently
 *
 * Response काष्ठाure to a TI_SCI_MSG_GET_STATUS request.
 */
काष्ठा ti_sci_msg_resp_get_status अणु
	काष्ठा ti_sci_msg_hdr hdr;
	u8 processor_id;
	u32 bootvector_low;
	u32 bootvector_high;
	u32 config_flags;
	u32 control_flags;
	u32 status_flags;
पूर्ण __packed;

#पूर्ण_अगर /* __TI_SCI_H */
