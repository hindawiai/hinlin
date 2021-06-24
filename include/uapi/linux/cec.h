<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * cec - HDMI Consumer Electronics Control खुला header
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _CEC_UAPI_H
#घोषणा _CEC_UAPI_H

#समावेश <linux/types.h>
#समावेश <linux/माला.स>

#घोषणा CEC_MAX_MSG_SIZE	16

/**
 * काष्ठा cec_msg - CEC message काष्ठाure.
 * @tx_ts:	Timestamp in nanoseconds using CLOCK_MONOTONIC. Set by the
 *		driver when the message transmission has finished.
 * @rx_ts:	Timestamp in nanoseconds using CLOCK_MONOTONIC. Set by the
 *		driver when the message was received.
 * @len:	Length in bytes of the message.
 * @समयout:	The समयout (in ms) that is used to समयout CEC_RECEIVE.
 *		Set to 0 अगर you want to रुको क्रमever. This समयout can also be
 *		used with CEC_TRANSMIT as the समयout क्रम रुकोing क्रम a reply.
 *		If 0, then it will use a 1 second समयout instead of रुकोing
 *		क्रमever as is करोne with CEC_RECEIVE.
 * @sequence:	The framework assigns a sequence number to messages that are
 *		sent. This can be used to track replies to previously sent
 *		messages.
 * @flags:	Set to 0.
 * @msg:	The message payload.
 * @reply:	This field is ignored with CEC_RECEIVE and is only used by
 *		CEC_TRANSMIT. If non-zero, then रुको क्रम a reply with this
 *		opcode. Set to CEC_MSG_FEATURE_ABORT अगर you want to रुको क्रम
 *		a possible ABORT reply. If there was an error when sending the
 *		msg or FeatureAbort was वापसed, then reply is set to 0.
 *		If reply is non-zero upon वापस, then len/msg are set to
 *		the received message.
 *		If reply is zero upon वापस and status has the
 *		CEC_TX_STATUS_FEATURE_ABORT bit set, then len/msg are set to
 *		the received feature पात message.
 *		If reply is zero upon वापस and status has the
 *		CEC_TX_STATUS_MAX_RETRIES bit set, then no reply was seen at
 *		all. If reply is non-zero क्रम CEC_TRANSMIT and the message is a
 *		broadcast, then -EINVAL is वापसed.
 *		अगर reply is non-zero, then समयout is set to 1000 (the required
 *		maximum response समय).
 * @rx_status:	The message receive status bits. Set by the driver.
 * @tx_status:	The message transmit status bits. Set by the driver.
 * @tx_arb_lost_cnt: The number of 'Arbitration Lost' events. Set by the driver.
 * @tx_nack_cnt: The number of 'Not Acknowledged' events. Set by the driver.
 * @tx_low_drive_cnt: The number of 'Low Drive Detected' events. Set by the
 *		driver.
 * @tx_error_cnt: The number of 'Error' events. Set by the driver.
 */
काष्ठा cec_msg अणु
	__u64 tx_ts;
	__u64 rx_ts;
	__u32 len;
	__u32 समयout;
	__u32 sequence;
	__u32 flags;
	__u8 msg[CEC_MAX_MSG_SIZE];
	__u8 reply;
	__u8 rx_status;
	__u8 tx_status;
	__u8 tx_arb_lost_cnt;
	__u8 tx_nack_cnt;
	__u8 tx_low_drive_cnt;
	__u8 tx_error_cnt;
पूर्ण;

/**
 * cec_msg_initiator - वापस the initiator's logical address.
 * @msg:	the message काष्ठाure
 */
अटल अंतरभूत __u8 cec_msg_initiator(स्थिर काष्ठा cec_msg *msg)
अणु
	वापस msg->msg[0] >> 4;
पूर्ण

/**
 * cec_msg_destination - वापस the destination's logical address.
 * @msg:	the message काष्ठाure
 */
अटल अंतरभूत __u8 cec_msg_destination(स्थिर काष्ठा cec_msg *msg)
अणु
	वापस msg->msg[0] & 0xf;
पूर्ण

/**
 * cec_msg_opcode - वापस the opcode of the message, -1 क्रम poll
 * @msg:	the message काष्ठाure
 */
अटल अंतरभूत पूर्णांक cec_msg_opcode(स्थिर काष्ठा cec_msg *msg)
अणु
	वापस msg->len > 1 ? msg->msg[1] : -1;
पूर्ण

/**
 * cec_msg_is_broadcast - वापस true अगर this is a broadcast message.
 * @msg:	the message काष्ठाure
 */
अटल अंतरभूत पूर्णांक cec_msg_is_broadcast(स्थिर काष्ठा cec_msg *msg)
अणु
	वापस (msg->msg[0] & 0xf) == 0xf;
पूर्ण

/**
 * cec_msg_init - initialize the message काष्ठाure.
 * @msg:	the message काष्ठाure
 * @initiator:	the logical address of the initiator
 * @destination:the logical address of the destination (0xf क्रम broadcast)
 *
 * The whole काष्ठाure is zeroed, the len field is set to 1 (i.e. a poll
 * message) and the initiator and destination are filled in.
 */
अटल अंतरभूत व्योम cec_msg_init(काष्ठा cec_msg *msg,
				__u8 initiator, __u8 destination)
अणु
	स_रखो(msg, 0, माप(*msg));
	msg->msg[0] = (initiator << 4) | destination;
	msg->len = 1;
पूर्ण

/**
 * cec_msg_set_reply_to - fill in destination/initiator in a reply message.
 * @msg:	the message काष्ठाure क्रम the reply
 * @orig:	the original message काष्ठाure
 *
 * Set the msg destination to the orig initiator and the msg initiator to the
 * orig destination. Note that msg and orig may be the same poपूर्णांकer, in which
 * हाल the change is करोne in place.
 */
अटल अंतरभूत व्योम cec_msg_set_reply_to(काष्ठा cec_msg *msg,
					काष्ठा cec_msg *orig)
अणु
	/* The destination becomes the initiator and vice versa */
	msg->msg[0] = (cec_msg_destination(orig) << 4) |
		      cec_msg_initiator(orig);
	msg->reply = msg->समयout = 0;
पूर्ण

/* cec_msg flags field */
#घोषणा CEC_MSG_FL_REPLY_TO_FOLLOWERS	(1 << 0)
#घोषणा CEC_MSG_FL_RAW			(1 << 1)

/* cec_msg tx/rx_status field */
#घोषणा CEC_TX_STATUS_OK		(1 << 0)
#घोषणा CEC_TX_STATUS_ARB_LOST		(1 << 1)
#घोषणा CEC_TX_STATUS_NACK		(1 << 2)
#घोषणा CEC_TX_STATUS_LOW_DRIVE		(1 << 3)
#घोषणा CEC_TX_STATUS_ERROR		(1 << 4)
#घोषणा CEC_TX_STATUS_MAX_RETRIES	(1 << 5)
#घोषणा CEC_TX_STATUS_ABORTED		(1 << 6)
#घोषणा CEC_TX_STATUS_TIMEOUT		(1 << 7)

#घोषणा CEC_RX_STATUS_OK		(1 << 0)
#घोषणा CEC_RX_STATUS_TIMEOUT		(1 << 1)
#घोषणा CEC_RX_STATUS_FEATURE_ABORT	(1 << 2)
#घोषणा CEC_RX_STATUS_ABORTED		(1 << 3)

अटल अंतरभूत पूर्णांक cec_msg_status_is_ok(स्थिर काष्ठा cec_msg *msg)
अणु
	अगर (msg->tx_status && !(msg->tx_status & CEC_TX_STATUS_OK))
		वापस 0;
	अगर (msg->rx_status && !(msg->rx_status & CEC_RX_STATUS_OK))
		वापस 0;
	अगर (!msg->tx_status && !msg->rx_status)
		वापस 0;
	वापस !(msg->rx_status & CEC_RX_STATUS_FEATURE_ABORT);
पूर्ण

#घोषणा CEC_LOG_ADDR_INVALID		0xff
#घोषणा CEC_PHYS_ADDR_INVALID		0xffff

/*
 * The maximum number of logical addresses one device can be asचिन्हित to.
 * The CEC 2.0 spec allows क्रम only 2 logical addresses at the moment. The
 * Analog Devices CEC hardware supports 3. So let's go wild and go क्रम 4.
 */
#घोषणा CEC_MAX_LOG_ADDRS 4

/* The logical addresses defined by CEC 2.0 */
#घोषणा CEC_LOG_ADDR_TV			0
#घोषणा CEC_LOG_ADDR_RECORD_1		1
#घोषणा CEC_LOG_ADDR_RECORD_2		2
#घोषणा CEC_LOG_ADDR_TUNER_1		3
#घोषणा CEC_LOG_ADDR_PLAYBACK_1		4
#घोषणा CEC_LOG_ADDR_AUDIOSYSTEM	5
#घोषणा CEC_LOG_ADDR_TUNER_2		6
#घोषणा CEC_LOG_ADDR_TUNER_3		7
#घोषणा CEC_LOG_ADDR_PLAYBACK_2		8
#घोषणा CEC_LOG_ADDR_RECORD_3		9
#घोषणा CEC_LOG_ADDR_TUNER_4		10
#घोषणा CEC_LOG_ADDR_PLAYBACK_3		11
#घोषणा CEC_LOG_ADDR_BACKUP_1		12
#घोषणा CEC_LOG_ADDR_BACKUP_2		13
#घोषणा CEC_LOG_ADDR_SPECIFIC		14
#घोषणा CEC_LOG_ADDR_UNREGISTERED	15 /* as initiator address */
#घोषणा CEC_LOG_ADDR_BROADCAST		15 /* as destination address */

/* The logical address types that the CEC device wants to claim */
#घोषणा CEC_LOG_ADDR_TYPE_TV		0
#घोषणा CEC_LOG_ADDR_TYPE_RECORD	1
#घोषणा CEC_LOG_ADDR_TYPE_TUNER		2
#घोषणा CEC_LOG_ADDR_TYPE_PLAYBACK	3
#घोषणा CEC_LOG_ADDR_TYPE_AUDIOSYSTEM	4
#घोषणा CEC_LOG_ADDR_TYPE_SPECIFIC	5
#घोषणा CEC_LOG_ADDR_TYPE_UNREGISTERED	6
/*
 * Switches should use UNREGISTERED.
 * Processors should use SPECIFIC.
 */

#घोषणा CEC_LOG_ADDR_MASK_TV		(1 << CEC_LOG_ADDR_TV)
#घोषणा CEC_LOG_ADDR_MASK_RECORD	((1 << CEC_LOG_ADDR_RECORD_1) | \
					 (1 << CEC_LOG_ADDR_RECORD_2) | \
					 (1 << CEC_LOG_ADDR_RECORD_3))
#घोषणा CEC_LOG_ADDR_MASK_TUNER		((1 << CEC_LOG_ADDR_TUNER_1) | \
					 (1 << CEC_LOG_ADDR_TUNER_2) | \
					 (1 << CEC_LOG_ADDR_TUNER_3) | \
					 (1 << CEC_LOG_ADDR_TUNER_4))
#घोषणा CEC_LOG_ADDR_MASK_PLAYBACK	((1 << CEC_LOG_ADDR_PLAYBACK_1) | \
					 (1 << CEC_LOG_ADDR_PLAYBACK_2) | \
					 (1 << CEC_LOG_ADDR_PLAYBACK_3))
#घोषणा CEC_LOG_ADDR_MASK_AUDIOSYSTEM	(1 << CEC_LOG_ADDR_AUDIOSYSTEM)
#घोषणा CEC_LOG_ADDR_MASK_BACKUP	((1 << CEC_LOG_ADDR_BACKUP_1) | \
					 (1 << CEC_LOG_ADDR_BACKUP_2))
#घोषणा CEC_LOG_ADDR_MASK_SPECIFIC	(1 << CEC_LOG_ADDR_SPECIFIC)
#घोषणा CEC_LOG_ADDR_MASK_UNREGISTERED	(1 << CEC_LOG_ADDR_UNREGISTERED)

अटल अंतरभूत पूर्णांक cec_has_tv(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_TV;
पूर्ण

अटल अंतरभूत पूर्णांक cec_has_record(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_RECORD;
पूर्ण

अटल अंतरभूत पूर्णांक cec_has_tuner(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_TUNER;
पूर्ण

अटल अंतरभूत पूर्णांक cec_has_playback(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_PLAYBACK;
पूर्ण

अटल अंतरभूत पूर्णांक cec_has_audioप्रणाली(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_AUDIOSYSTEM;
पूर्ण

अटल अंतरभूत पूर्णांक cec_has_backup(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_BACKUP;
पूर्ण

अटल अंतरभूत पूर्णांक cec_has_specअगरic(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_SPECIFIC;
पूर्ण

अटल अंतरभूत पूर्णांक cec_is_unरेजिस्टरed(__u16 log_addr_mask)
अणु
	वापस log_addr_mask & CEC_LOG_ADDR_MASK_UNREGISTERED;
पूर्ण

अटल अंतरभूत पूर्णांक cec_is_unconfigured(__u16 log_addr_mask)
अणु
	वापस log_addr_mask == 0;
पूर्ण

/*
 * Use this अगर there is no venकरोr ID (CEC_G_VENDOR_ID) or अगर the venकरोr ID
 * should be disabled (CEC_S_VENDOR_ID)
 */
#घोषणा CEC_VENDOR_ID_NONE		0xffffffff

/* The message handling modes */
/* Modes क्रम initiator */
#घोषणा CEC_MODE_NO_INITIATOR		(0x0 << 0)
#घोषणा CEC_MODE_INITIATOR		(0x1 << 0)
#घोषणा CEC_MODE_EXCL_INITIATOR		(0x2 << 0)
#घोषणा CEC_MODE_INITIATOR_MSK		0x0f

/* Modes क्रम follower */
#घोषणा CEC_MODE_NO_FOLLOWER		(0x0 << 4)
#घोषणा CEC_MODE_FOLLOWER		(0x1 << 4)
#घोषणा CEC_MODE_EXCL_FOLLOWER		(0x2 << 4)
#घोषणा CEC_MODE_EXCL_FOLLOWER_PASSTHRU	(0x3 << 4)
#घोषणा CEC_MODE_MONITOR_PIN		(0xd << 4)
#घोषणा CEC_MODE_MONITOR		(0xe << 4)
#घोषणा CEC_MODE_MONITOR_ALL		(0xf << 4)
#घोषणा CEC_MODE_FOLLOWER_MSK		0xf0

/* Userspace has to configure the physical address */
#घोषणा CEC_CAP_PHYS_ADDR	(1 << 0)
/* Userspace has to configure the logical addresses */
#घोषणा CEC_CAP_LOG_ADDRS	(1 << 1)
/* Userspace can transmit messages (and thus become follower as well) */
#घोषणा CEC_CAP_TRANSMIT	(1 << 2)
/*
 * Passthrough all messages instead of processing them.
 */
#घोषणा CEC_CAP_PASSTHROUGH	(1 << 3)
/* Supports remote control */
#घोषणा CEC_CAP_RC		(1 << 4)
/* Hardware can monitor all messages, not just directed and broadcast. */
#घोषणा CEC_CAP_MONITOR_ALL	(1 << 5)
/* Hardware can use CEC only अगर the HDMI HPD pin is high. */
#घोषणा CEC_CAP_NEEDS_HPD	(1 << 6)
/* Hardware can monitor CEC pin transitions */
#घोषणा CEC_CAP_MONITOR_PIN	(1 << 7)
/* CEC_ADAP_G_CONNECTOR_INFO is available */
#घोषणा CEC_CAP_CONNECTOR_INFO	(1 << 8)

/**
 * काष्ठा cec_caps - CEC capabilities काष्ठाure.
 * @driver: name of the CEC device driver.
 * @name: name of the CEC device. @driver + @name must be unique.
 * @available_log_addrs: number of available logical addresses.
 * @capabilities: capabilities of the CEC adapter.
 * @version: version of the CEC adapter framework.
 */
काष्ठा cec_caps अणु
	अक्षर driver[32];
	अक्षर name[32];
	__u32 available_log_addrs;
	__u32 capabilities;
	__u32 version;
पूर्ण;

/**
 * काष्ठा cec_log_addrs - CEC logical addresses काष्ठाure.
 * @log_addr: the claimed logical addresses. Set by the driver.
 * @log_addr_mask: current logical address mask. Set by the driver.
 * @cec_version: the CEC version that the adapter should implement. Set by the
 *	caller.
 * @num_log_addrs: how many logical addresses should be claimed. Set by the
 *	caller.
 * @venकरोr_id: the venकरोr ID of the device. Set by the caller.
 * @flags: flags.
 * @osd_name: the OSD name of the device. Set by the caller.
 * @primary_device_type: the primary device type क्रम each logical address.
 *	Set by the caller.
 * @log_addr_type: the logical address types. Set by the caller.
 * @all_device_types: CEC 2.0: all device types represented by the logical
 *	address. Set by the caller.
 * @features:	CEC 2.0: The logical address features. Set by the caller.
 */
काष्ठा cec_log_addrs अणु
	__u8 log_addr[CEC_MAX_LOG_ADDRS];
	__u16 log_addr_mask;
	__u8 cec_version;
	__u8 num_log_addrs;
	__u32 venकरोr_id;
	__u32 flags;
	अक्षर osd_name[15];
	__u8 primary_device_type[CEC_MAX_LOG_ADDRS];
	__u8 log_addr_type[CEC_MAX_LOG_ADDRS];

	/* CEC 2.0 */
	__u8 all_device_types[CEC_MAX_LOG_ADDRS];
	__u8 features[CEC_MAX_LOG_ADDRS][12];
पूर्ण;

/* Allow a fallback to unरेजिस्टरed */
#घोषणा CEC_LOG_ADDRS_FL_ALLOW_UNREG_FALLBACK	(1 << 0)
/* Passthrough RC messages to the input subप्रणाली */
#घोषणा CEC_LOG_ADDRS_FL_ALLOW_RC_PASSTHRU	(1 << 1)
/* CDC-Only device: supports only CDC messages */
#घोषणा CEC_LOG_ADDRS_FL_CDC_ONLY		(1 << 2)

/**
 * काष्ठा cec_drm_connector_info - tells which drm connector is
 * associated with the CEC adapter.
 * @card_no: drm card number
 * @connector_id: drm connector ID
 */
काष्ठा cec_drm_connector_info अणु
	__u32 card_no;
	__u32 connector_id;
पूर्ण;

#घोषणा CEC_CONNECTOR_TYPE_NO_CONNECTOR	0
#घोषणा CEC_CONNECTOR_TYPE_DRM		1

/**
 * काष्ठा cec_connector_info - tells अगर and which connector is
 * associated with the CEC adapter.
 * @type: connector type (अगर any)
 * @drm: drm connector info
 * @raw: array to pad the जोड़
 */
काष्ठा cec_connector_info अणु
	__u32 type;
	जोड़ अणु
		काष्ठा cec_drm_connector_info drm;
		__u32 raw[16];
	पूर्ण;
पूर्ण;

/* Events */

/* Event that occurs when the adapter state changes */
#घोषणा CEC_EVENT_STATE_CHANGE		1
/*
 * This event is sent when messages are lost because the application
 * didn't empty the message queue in समय
 */
#घोषणा CEC_EVENT_LOST_MSGS		2
#घोषणा CEC_EVENT_PIN_CEC_LOW		3
#घोषणा CEC_EVENT_PIN_CEC_HIGH		4
#घोषणा CEC_EVENT_PIN_HPD_LOW		5
#घोषणा CEC_EVENT_PIN_HPD_HIGH		6
#घोषणा CEC_EVENT_PIN_5V_LOW		7
#घोषणा CEC_EVENT_PIN_5V_HIGH		8

#घोषणा CEC_EVENT_FL_INITIAL_STATE	(1 << 0)
#घोषणा CEC_EVENT_FL_DROPPED_EVENTS	(1 << 1)

/**
 * काष्ठा cec_event_state_change - used when the CEC adapter changes state.
 * @phys_addr: the current physical address
 * @log_addr_mask: the current logical address mask
 * @have_conn_info: अगर non-zero, then HDMI connector inक्रमmation is available.
 *	This field is only valid अगर CEC_CAP_CONNECTOR_INFO is set. If that
 *	capability is set and @have_conn_info is zero, then that indicates
 *	that the HDMI connector device is not instantiated, either because
 *	the HDMI driver is still configuring the device or because the HDMI
 *	device was unbound.
 */
काष्ठा cec_event_state_change अणु
	__u16 phys_addr;
	__u16 log_addr_mask;
	__u16 have_conn_info;
पूर्ण;

/**
 * काष्ठा cec_event_lost_msgs - tells you how many messages were lost.
 * @lost_msgs: how many messages were lost.
 */
काष्ठा cec_event_lost_msgs अणु
	__u32 lost_msgs;
पूर्ण;

/**
 * काष्ठा cec_event - CEC event काष्ठाure
 * @ts: the बारtamp of when the event was sent.
 * @event: the event.
 * @flags: event flags.
 * @state_change: the event payload क्रम CEC_EVENT_STATE_CHANGE.
 * @lost_msgs: the event payload क्रम CEC_EVENT_LOST_MSGS.
 * @raw: array to pad the जोड़.
 */
काष्ठा cec_event अणु
	__u64 ts;
	__u32 event;
	__u32 flags;
	जोड़ अणु
		काष्ठा cec_event_state_change state_change;
		काष्ठा cec_event_lost_msgs lost_msgs;
		__u32 raw[16];
	पूर्ण;
पूर्ण;

/* ioctls */

/* Adapter capabilities */
#घोषणा CEC_ADAP_G_CAPS		_IOWR('a',  0, काष्ठा cec_caps)

/*
 * phys_addr is either 0 (अगर this is the CEC root device)
 * or a valid physical address obtained from the sink's EDID
 * as पढ़ो by this CEC device (अगर this is a source device)
 * or a physical address obtained and modअगरied from a sink
 * EDID and used क्रम a sink CEC device.
 * If nothing is connected, then phys_addr is 0xffff.
 * See HDMI 1.4b, section 8.7 (Physical Address).
 *
 * The CEC_ADAP_S_PHYS_ADDR ioctl may not be available अगर that is handled
 * पूर्णांकernally.
 */
#घोषणा CEC_ADAP_G_PHYS_ADDR	_IOR('a',  1, __u16)
#घोषणा CEC_ADAP_S_PHYS_ADDR	_IOW('a',  2, __u16)

/*
 * Configure the CEC adapter. It sets the device type and which
 * logical types it will try to claim. It will वापस which
 * logical addresses it could actually claim.
 * An error is वापसed अगर the adapter is disabled or अगर there
 * is no physical address asचिन्हित.
 */

#घोषणा CEC_ADAP_G_LOG_ADDRS	_IOR('a',  3, काष्ठा cec_log_addrs)
#घोषणा CEC_ADAP_S_LOG_ADDRS	_IOWR('a',  4, काष्ठा cec_log_addrs)

/* Transmit/receive a CEC command */
#घोषणा CEC_TRANSMIT		_IOWR('a',  5, काष्ठा cec_msg)
#घोषणा CEC_RECEIVE		_IOWR('a',  6, काष्ठा cec_msg)

/* Dequeue CEC events */
#घोषणा CEC_DQEVENT		_IOWR('a',  7, काष्ठा cec_event)

/*
 * Get and set the message handling mode क्रम this filehandle.
 */
#घोषणा CEC_G_MODE		_IOR('a',  8, __u32)
#घोषणा CEC_S_MODE		_IOW('a',  9, __u32)

/* Get the connector info */
#घोषणा CEC_ADAP_G_CONNECTOR_INFO _IOR('a',  10, काष्ठा cec_connector_info)

/*
 * The reमुख्यder of this header defines all CEC messages and opeअक्रमs.
 * The क्रमmat matters since it the cec-ctl utility parses it to generate
 * code क्रम implementing all these messages.
 *
 * Comments ending with 'Feature' group messages क्रम each feature.
 * If messages are part of multiple features, then the "Has also"
 * comment is used to list the previously defined messages that are
 * supported by the feature.
 *
 * Beक्रमe opeअक्रमs are defined a comment is added that gives the
 * name of the opeअक्रम and in brackets the variable name of the
 * corresponding argument in the cec-funcs.h function.
 */

/* Messages */

/* One Touch Play Feature */
#घोषणा CEC_MSG_ACTIVE_SOURCE				0x82
#घोषणा CEC_MSG_IMAGE_VIEW_ON				0x04
#घोषणा CEC_MSG_TEXT_VIEW_ON				0x0d


/* Routing Control Feature */

/*
 * Has also:
 *	CEC_MSG_ACTIVE_SOURCE
 */

#घोषणा CEC_MSG_INACTIVE_SOURCE				0x9d
#घोषणा CEC_MSG_REQUEST_ACTIVE_SOURCE			0x85
#घोषणा CEC_MSG_ROUTING_CHANGE				0x80
#घोषणा CEC_MSG_ROUTING_INFORMATION			0x81
#घोषणा CEC_MSG_SET_STREAM_PATH				0x86


/* Standby Feature */
#घोषणा CEC_MSG_STANDBY					0x36


/* One Touch Record Feature */
#घोषणा CEC_MSG_RECORD_OFF				0x0b
#घोषणा CEC_MSG_RECORD_ON				0x09
/* Record Source Type Opeअक्रम (rec_src_type) */
#घोषणा CEC_OP_RECORD_SRC_OWN				1
#घोषणा CEC_OP_RECORD_SRC_DIGITAL			2
#घोषणा CEC_OP_RECORD_SRC_ANALOG			3
#घोषणा CEC_OP_RECORD_SRC_EXT_PLUG			4
#घोषणा CEC_OP_RECORD_SRC_EXT_PHYS_ADDR			5
/* Service Identअगरication Method Opeअक्रम (service_id_method) */
#घोषणा CEC_OP_SERVICE_ID_METHOD_BY_DIG_ID		0
#घोषणा CEC_OP_SERVICE_ID_METHOD_BY_CHANNEL		1
/* Digital Service Broadcast System Opeअक्रम (dig_bcast_प्रणाली) */
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ARIB_GEN	0x00
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_GEN	0x01
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_DVB_GEN		0x02
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ARIB_BS		0x08
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ARIB_CS		0x09
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ARIB_T		0x0a
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_CABLE	0x10
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_SAT	0x11
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_T		0x12
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_DVB_C		0x18
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_DVB_S		0x19
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_DVB_S2		0x1a
#घोषणा CEC_OP_DIG_SERVICE_BCAST_SYSTEM_DVB_T		0x1b
/* Analogue Broadcast Type Opeअक्रम (ana_bcast_type) */
#घोषणा CEC_OP_ANA_BCAST_TYPE_CABLE			0
#घोषणा CEC_OP_ANA_BCAST_TYPE_SATELLITE			1
#घोषणा CEC_OP_ANA_BCAST_TYPE_TERRESTRIAL		2
/* Broadcast System Opeअक्रम (bcast_प्रणाली) */
#घोषणा CEC_OP_BCAST_SYSTEM_PAL_BG			0x00
#घोषणा CEC_OP_BCAST_SYSTEM_SECAM_LQ			0x01 /* SECAM L' */
#घोषणा CEC_OP_BCAST_SYSTEM_PAL_M			0x02
#घोषणा CEC_OP_BCAST_SYSTEM_NTSC_M			0x03
#घोषणा CEC_OP_BCAST_SYSTEM_PAL_I			0x04
#घोषणा CEC_OP_BCAST_SYSTEM_SECAM_DK			0x05
#घोषणा CEC_OP_BCAST_SYSTEM_SECAM_BG			0x06
#घोषणा CEC_OP_BCAST_SYSTEM_SECAM_L			0x07
#घोषणा CEC_OP_BCAST_SYSTEM_PAL_DK			0x08
#घोषणा CEC_OP_BCAST_SYSTEM_OTHER			0x1f
/* Channel Number Format Opeअक्रम (channel_number_fmt) */
#घोषणा CEC_OP_CHANNEL_NUMBER_FMT_1_PART		0x01
#घोषणा CEC_OP_CHANNEL_NUMBER_FMT_2_PART		0x02

#घोषणा CEC_MSG_RECORD_STATUS				0x0a
/* Record Status Opeअक्रम (rec_status) */
#घोषणा CEC_OP_RECORD_STATUS_CUR_SRC			0x01
#घोषणा CEC_OP_RECORD_STATUS_DIG_SERVICE		0x02
#घोषणा CEC_OP_RECORD_STATUS_ANA_SERVICE		0x03
#घोषणा CEC_OP_RECORD_STATUS_EXT_INPUT			0x04
#घोषणा CEC_OP_RECORD_STATUS_NO_DIG_SERVICE		0x05
#घोषणा CEC_OP_RECORD_STATUS_NO_ANA_SERVICE		0x06
#घोषणा CEC_OP_RECORD_STATUS_NO_SERVICE			0x07
#घोषणा CEC_OP_RECORD_STATUS_INVALID_EXT_PLUG		0x09
#घोषणा CEC_OP_RECORD_STATUS_INVALID_EXT_PHYS_ADDR	0x0a
#घोषणा CEC_OP_RECORD_STATUS_UNSUP_CA			0x0b
#घोषणा CEC_OP_RECORD_STATUS_NO_CA_ENTITLEMENTS		0x0c
#घोषणा CEC_OP_RECORD_STATUS_CANT_COPY_SRC		0x0d
#घोषणा CEC_OP_RECORD_STATUS_NO_MORE_COPIES		0x0e
#घोषणा CEC_OP_RECORD_STATUS_NO_MEDIA			0x10
#घोषणा CEC_OP_RECORD_STATUS_PLAYING			0x11
#घोषणा CEC_OP_RECORD_STATUS_ALREADY_RECORDING		0x12
#घोषणा CEC_OP_RECORD_STATUS_MEDIA_PROT			0x13
#घोषणा CEC_OP_RECORD_STATUS_NO_SIGNAL			0x14
#घोषणा CEC_OP_RECORD_STATUS_MEDIA_PROBLEM		0x15
#घोषणा CEC_OP_RECORD_STATUS_NO_SPACE			0x16
#घोषणा CEC_OP_RECORD_STATUS_PARENTAL_LOCK		0x17
#घोषणा CEC_OP_RECORD_STATUS_TERMINATED_OK		0x1a
#घोषणा CEC_OP_RECORD_STATUS_ALREADY_TERM		0x1b
#घोषणा CEC_OP_RECORD_STATUS_OTHER			0x1f

#घोषणा CEC_MSG_RECORD_TV_SCREEN			0x0f


/* Timer Programming Feature */
#घोषणा CEC_MSG_CLEAR_ANALOGUE_TIMER			0x33
/* Recording Sequence Opeअक्रम (recording_seq) */
#घोषणा CEC_OP_REC_SEQ_SUNDAY				0x01
#घोषणा CEC_OP_REC_SEQ_MONDAY				0x02
#घोषणा CEC_OP_REC_SEQ_TUESDAY				0x04
#घोषणा CEC_OP_REC_SEQ_WEDNESDAY			0x08
#घोषणा CEC_OP_REC_SEQ_THURSDAY				0x10
#घोषणा CEC_OP_REC_SEQ_FRIDAY				0x20
#घोषणा CEC_OP_REC_SEQ_SATERDAY				0x40
#घोषणा CEC_OP_REC_SEQ_ONCE_ONLY			0x00

#घोषणा CEC_MSG_CLEAR_DIGITAL_TIMER			0x99

#घोषणा CEC_MSG_CLEAR_EXT_TIMER				0xa1
/* External Source Specअगरier Opeअक्रम (ext_src_spec) */
#घोषणा CEC_OP_EXT_SRC_PLUG				0x04
#घोषणा CEC_OP_EXT_SRC_PHYS_ADDR			0x05

#घोषणा CEC_MSG_SET_ANALOGUE_TIMER			0x34
#घोषणा CEC_MSG_SET_DIGITAL_TIMER			0x97
#घोषणा CEC_MSG_SET_EXT_TIMER				0xa2

#घोषणा CEC_MSG_SET_TIMER_PROGRAM_TITLE			0x67
#घोषणा CEC_MSG_TIMER_CLEARED_STATUS			0x43
/* Timer Cleared Status Data Opeअक्रम (समयr_cleared_status) */
#घोषणा CEC_OP_TIMER_CLR_STAT_RECORDING			0x00
#घोषणा CEC_OP_TIMER_CLR_STAT_NO_MATCHING		0x01
#घोषणा CEC_OP_TIMER_CLR_STAT_NO_INFO			0x02
#घोषणा CEC_OP_TIMER_CLR_STAT_CLEARED			0x80

#घोषणा CEC_MSG_TIMER_STATUS				0x35
/* Timer Overlap Warning Opeअक्रम (समयr_overlap_warning) */
#घोषणा CEC_OP_TIMER_OVERLAP_WARNING_NO_OVERLAP		0
#घोषणा CEC_OP_TIMER_OVERLAP_WARNING_OVERLAP		1
/* Media Info Opeअक्रम (media_info) */
#घोषणा CEC_OP_MEDIA_INFO_UNPROT_MEDIA			0
#घोषणा CEC_OP_MEDIA_INFO_PROT_MEDIA			1
#घोषणा CEC_OP_MEDIA_INFO_NO_MEDIA			2
/* Programmed Indicator Opeअक्रम (prog_indicator) */
#घोषणा CEC_OP_PROG_IND_NOT_PROGRAMMED			0
#घोषणा CEC_OP_PROG_IND_PROGRAMMED			1
/* Programmed Info Opeअक्रम (prog_info) */
#घोषणा CEC_OP_PROG_INFO_ENOUGH_SPACE			0x08
#घोषणा CEC_OP_PROG_INFO_NOT_ENOUGH_SPACE		0x09
#घोषणा CEC_OP_PROG_INFO_MIGHT_NOT_BE_ENOUGH_SPACE	0x0b
#घोषणा CEC_OP_PROG_INFO_NONE_AVAILABLE			0x0a
/* Not Programmed Error Info Opeअक्रम (prog_error) */
#घोषणा CEC_OP_PROG_ERROR_NO_FREE_TIMER			0x01
#घोषणा CEC_OP_PROG_ERROR_DATE_OUT_OF_RANGE		0x02
#घोषणा CEC_OP_PROG_ERROR_REC_SEQ_ERROR			0x03
#घोषणा CEC_OP_PROG_ERROR_INV_EXT_PLUG			0x04
#घोषणा CEC_OP_PROG_ERROR_INV_EXT_PHYS_ADDR		0x05
#घोषणा CEC_OP_PROG_ERROR_CA_UNSUPP			0x06
#घोषणा CEC_OP_PROG_ERROR_INSUF_CA_ENTITLEMENTS		0x07
#घोषणा CEC_OP_PROG_ERROR_RESOLUTION_UNSUPP		0x08
#घोषणा CEC_OP_PROG_ERROR_PARENTAL_LOCK			0x09
#घोषणा CEC_OP_PROG_ERROR_CLOCK_FAILURE			0x0a
#घोषणा CEC_OP_PROG_ERROR_DUPLICATE			0x0e


/* System Inक्रमmation Feature */
#घोषणा CEC_MSG_CEC_VERSION				0x9e
/* CEC Version Opeअक्रम (cec_version) */
#घोषणा CEC_OP_CEC_VERSION_1_3A				4
#घोषणा CEC_OP_CEC_VERSION_1_4				5
#घोषणा CEC_OP_CEC_VERSION_2_0				6

#घोषणा CEC_MSG_GET_CEC_VERSION				0x9f
#घोषणा CEC_MSG_GIVE_PHYSICAL_ADDR			0x83
#घोषणा CEC_MSG_GET_MENU_LANGUAGE			0x91
#घोषणा CEC_MSG_REPORT_PHYSICAL_ADDR			0x84
/* Primary Device Type Opeअक्रम (prim_devtype) */
#घोषणा CEC_OP_PRIM_DEVTYPE_TV				0
#घोषणा CEC_OP_PRIM_DEVTYPE_RECORD			1
#घोषणा CEC_OP_PRIM_DEVTYPE_TUNER			3
#घोषणा CEC_OP_PRIM_DEVTYPE_PLAYBACK			4
#घोषणा CEC_OP_PRIM_DEVTYPE_AUDIOSYSTEM			5
#घोषणा CEC_OP_PRIM_DEVTYPE_SWITCH			6
#घोषणा CEC_OP_PRIM_DEVTYPE_PROCESSOR			7

#घोषणा CEC_MSG_SET_MENU_LANGUAGE			0x32
#घोषणा CEC_MSG_REPORT_FEATURES				0xa6	/* HDMI 2.0 */
/* All Device Types Opeअक्रम (all_device_types) */
#घोषणा CEC_OP_ALL_DEVTYPE_TV				0x80
#घोषणा CEC_OP_ALL_DEVTYPE_RECORD			0x40
#घोषणा CEC_OP_ALL_DEVTYPE_TUNER			0x20
#घोषणा CEC_OP_ALL_DEVTYPE_PLAYBACK			0x10
#घोषणा CEC_OP_ALL_DEVTYPE_AUDIOSYSTEM			0x08
#घोषणा CEC_OP_ALL_DEVTYPE_SWITCH			0x04
/*
 * And अगर you wondering what happened to PROCESSOR devices: those should
 * be mapped to a SWITCH.
 */

/* Valid क्रम RC Profile and Device Feature opeअक्रमs */
#घोषणा CEC_OP_FEAT_EXT					0x80	/* Extension bit */
/* RC Profile Opeअक्रम (rc_profile) */
#घोषणा CEC_OP_FEAT_RC_TV_PROखाता_NONE			0x00
#घोषणा CEC_OP_FEAT_RC_TV_PROखाता_1			0x02
#घोषणा CEC_OP_FEAT_RC_TV_PROखाता_2			0x06
#घोषणा CEC_OP_FEAT_RC_TV_PROखाता_3			0x0a
#घोषणा CEC_OP_FEAT_RC_TV_PROखाता_4			0x0e
#घोषणा CEC_OP_FEAT_RC_SRC_HAS_DEV_ROOT_MENU		0x50
#घोषणा CEC_OP_FEAT_RC_SRC_HAS_DEV_SETUP_MENU		0x48
#घोषणा CEC_OP_FEAT_RC_SRC_HAS_CONTENTS_MENU		0x44
#घोषणा CEC_OP_FEAT_RC_SRC_HAS_MEDIA_TOP_MENU		0x42
#घोषणा CEC_OP_FEAT_RC_SRC_HAS_MEDIA_CONTEXT_MENU	0x41
/* Device Feature Opeअक्रम (dev_features) */
#घोषणा CEC_OP_FEAT_DEV_HAS_RECORD_TV_SCREEN		0x40
#घोषणा CEC_OP_FEAT_DEV_HAS_SET_OSD_STRING		0x20
#घोषणा CEC_OP_FEAT_DEV_HAS_DECK_CONTROL		0x10
#घोषणा CEC_OP_FEAT_DEV_HAS_SET_AUDIO_RATE		0x08
#घोषणा CEC_OP_FEAT_DEV_SINK_HAS_ARC_TX			0x04
#घोषणा CEC_OP_FEAT_DEV_SOURCE_HAS_ARC_RX		0x02

#घोषणा CEC_MSG_GIVE_FEATURES				0xa5	/* HDMI 2.0 */


/* Deck Control Feature */
#घोषणा CEC_MSG_DECK_CONTROL				0x42
/* Deck Control Mode Opeअक्रम (deck_control_mode) */
#घोषणा CEC_OP_DECK_CTL_MODE_SKIP_FWD			1
#घोषणा CEC_OP_DECK_CTL_MODE_SKIP_REV			2
#घोषणा CEC_OP_DECK_CTL_MODE_STOP			3
#घोषणा CEC_OP_DECK_CTL_MODE_EJECT			4

#घोषणा CEC_MSG_DECK_STATUS				0x1b
/* Deck Info Opeअक्रम (deck_info) */
#घोषणा CEC_OP_DECK_INFO_PLAY				0x11
#घोषणा CEC_OP_DECK_INFO_RECORD				0x12
#घोषणा CEC_OP_DECK_INFO_PLAY_REV			0x13
#घोषणा CEC_OP_DECK_INFO_STILL				0x14
#घोषणा CEC_OP_DECK_INFO_SLOW				0x15
#घोषणा CEC_OP_DECK_INFO_SLOW_REV			0x16
#घोषणा CEC_OP_DECK_INFO_FAST_FWD			0x17
#घोषणा CEC_OP_DECK_INFO_FAST_REV			0x18
#घोषणा CEC_OP_DECK_INFO_NO_MEDIA			0x19
#घोषणा CEC_OP_DECK_INFO_STOP				0x1a
#घोषणा CEC_OP_DECK_INFO_SKIP_FWD			0x1b
#घोषणा CEC_OP_DECK_INFO_SKIP_REV			0x1c
#घोषणा CEC_OP_DECK_INFO_INDEX_SEARCH_FWD		0x1d
#घोषणा CEC_OP_DECK_INFO_INDEX_SEARCH_REV		0x1e
#घोषणा CEC_OP_DECK_INFO_OTHER				0x1f

#घोषणा CEC_MSG_GIVE_DECK_STATUS			0x1a
/* Status Request Opeअक्रम (status_req) */
#घोषणा CEC_OP_STATUS_REQ_ON				1
#घोषणा CEC_OP_STATUS_REQ_OFF				2
#घोषणा CEC_OP_STATUS_REQ_ONCE				3

#घोषणा CEC_MSG_PLAY					0x41
/* Play Mode Opeअक्रम (play_mode) */
#घोषणा CEC_OP_PLAY_MODE_PLAY_FWD			0x24
#घोषणा CEC_OP_PLAY_MODE_PLAY_REV			0x20
#घोषणा CEC_OP_PLAY_MODE_PLAY_STILL			0x25
#घोषणा CEC_OP_PLAY_MODE_PLAY_FAST_FWD_MIN		0x05
#घोषणा CEC_OP_PLAY_MODE_PLAY_FAST_FWD_MED		0x06
#घोषणा CEC_OP_PLAY_MODE_PLAY_FAST_FWD_MAX		0x07
#घोषणा CEC_OP_PLAY_MODE_PLAY_FAST_REV_MIN		0x09
#घोषणा CEC_OP_PLAY_MODE_PLAY_FAST_REV_MED		0x0a
#घोषणा CEC_OP_PLAY_MODE_PLAY_FAST_REV_MAX		0x0b
#घोषणा CEC_OP_PLAY_MODE_PLAY_SLOW_FWD_MIN		0x15
#घोषणा CEC_OP_PLAY_MODE_PLAY_SLOW_FWD_MED		0x16
#घोषणा CEC_OP_PLAY_MODE_PLAY_SLOW_FWD_MAX		0x17
#घोषणा CEC_OP_PLAY_MODE_PLAY_SLOW_REV_MIN		0x19
#घोषणा CEC_OP_PLAY_MODE_PLAY_SLOW_REV_MED		0x1a
#घोषणा CEC_OP_PLAY_MODE_PLAY_SLOW_REV_MAX		0x1b


/* Tuner Control Feature */
#घोषणा CEC_MSG_GIVE_TUNER_DEVICE_STATUS		0x08
#घोषणा CEC_MSG_SELECT_ANALOGUE_SERVICE			0x92
#घोषणा CEC_MSG_SELECT_DIGITAL_SERVICE			0x93
#घोषणा CEC_MSG_TUNER_DEVICE_STATUS			0x07
/* Recording Flag Opeअक्रम (rec_flag) */
#घोषणा CEC_OP_REC_FLAG_NOT_USED			0
#घोषणा CEC_OP_REC_FLAG_USED				1
/* Tuner Display Info Opeअक्रम (tuner_display_info) */
#घोषणा CEC_OP_TUNER_DISPLAY_INFO_DIGITAL		0
#घोषणा CEC_OP_TUNER_DISPLAY_INFO_NONE			1
#घोषणा CEC_OP_TUNER_DISPLAY_INFO_ANALOGUE		2

#घोषणा CEC_MSG_TUNER_STEP_DECREMENT			0x06
#घोषणा CEC_MSG_TUNER_STEP_INCREMENT			0x05


/* Venकरोr Specअगरic Commands Feature */

/*
 * Has also:
 *	CEC_MSG_CEC_VERSION
 *	CEC_MSG_GET_CEC_VERSION
 */
#घोषणा CEC_MSG_DEVICE_VENDOR_ID			0x87
#घोषणा CEC_MSG_GIVE_DEVICE_VENDOR_ID			0x8c
#घोषणा CEC_MSG_VENDOR_COMMAND				0x89
#घोषणा CEC_MSG_VENDOR_COMMAND_WITH_ID			0xa0
#घोषणा CEC_MSG_VENDOR_REMOTE_BUTTON_DOWN		0x8a
#घोषणा CEC_MSG_VENDOR_REMOTE_BUTTON_UP			0x8b


/* OSD Display Feature */
#घोषणा CEC_MSG_SET_OSD_STRING				0x64
/* Display Control Opeअक्रम (disp_ctl) */
#घोषणा CEC_OP_DISP_CTL_DEFAULT				0x00
#घोषणा CEC_OP_DISP_CTL_UNTIL_CLEARED			0x40
#घोषणा CEC_OP_DISP_CTL_CLEAR				0x80


/* Device OSD Transfer Feature */
#घोषणा CEC_MSG_GIVE_OSD_NAME				0x46
#घोषणा CEC_MSG_SET_OSD_NAME				0x47


/* Device Menu Control Feature */
#घोषणा CEC_MSG_MENU_REQUEST				0x8d
/* Menu Request Type Opeअक्रम (menu_req) */
#घोषणा CEC_OP_MENU_REQUEST_ACTIVATE			0x00
#घोषणा CEC_OP_MENU_REQUEST_DEACTIVATE			0x01
#घोषणा CEC_OP_MENU_REQUEST_QUERY			0x02

#घोषणा CEC_MSG_MENU_STATUS				0x8e
/* Menu State Opeअक्रम (menu_state) */
#घोषणा CEC_OP_MENU_STATE_ACTIVATED			0x00
#घोषणा CEC_OP_MENU_STATE_DEACTIVATED			0x01

#घोषणा CEC_MSG_USER_CONTROL_PRESSED			0x44
/* UI Command Opeअक्रम (ui_cmd) */
#घोषणा CEC_OP_UI_CMD_SELECT				0x00
#घोषणा CEC_OP_UI_CMD_UP				0x01
#घोषणा CEC_OP_UI_CMD_DOWN				0x02
#घोषणा CEC_OP_UI_CMD_LEFT				0x03
#घोषणा CEC_OP_UI_CMD_RIGHT				0x04
#घोषणा CEC_OP_UI_CMD_RIGHT_UP				0x05
#घोषणा CEC_OP_UI_CMD_RIGHT_DOWN			0x06
#घोषणा CEC_OP_UI_CMD_LEFT_UP				0x07
#घोषणा CEC_OP_UI_CMD_LEFT_DOWN				0x08
#घोषणा CEC_OP_UI_CMD_DEVICE_ROOT_MENU			0x09
#घोषणा CEC_OP_UI_CMD_DEVICE_SETUP_MENU			0x0a
#घोषणा CEC_OP_UI_CMD_CONTENTS_MENU			0x0b
#घोषणा CEC_OP_UI_CMD_FAVORITE_MENU			0x0c
#घोषणा CEC_OP_UI_CMD_BACK				0x0d
#घोषणा CEC_OP_UI_CMD_MEDIA_TOP_MENU			0x10
#घोषणा CEC_OP_UI_CMD_MEDIA_CONTEXT_SENSITIVE_MENU	0x11
#घोषणा CEC_OP_UI_CMD_NUMBER_ENTRY_MODE			0x1d
#घोषणा CEC_OP_UI_CMD_NUMBER_11				0x1e
#घोषणा CEC_OP_UI_CMD_NUMBER_12				0x1f
#घोषणा CEC_OP_UI_CMD_NUMBER_0_OR_NUMBER_10		0x20
#घोषणा CEC_OP_UI_CMD_NUMBER_1				0x21
#घोषणा CEC_OP_UI_CMD_NUMBER_2				0x22
#घोषणा CEC_OP_UI_CMD_NUMBER_3				0x23
#घोषणा CEC_OP_UI_CMD_NUMBER_4				0x24
#घोषणा CEC_OP_UI_CMD_NUMBER_5				0x25
#घोषणा CEC_OP_UI_CMD_NUMBER_6				0x26
#घोषणा CEC_OP_UI_CMD_NUMBER_7				0x27
#घोषणा CEC_OP_UI_CMD_NUMBER_8				0x28
#घोषणा CEC_OP_UI_CMD_NUMBER_9				0x29
#घोषणा CEC_OP_UI_CMD_DOT				0x2a
#घोषणा CEC_OP_UI_CMD_ENTER				0x2b
#घोषणा CEC_OP_UI_CMD_CLEAR				0x2c
#घोषणा CEC_OP_UI_CMD_NEXT_FAVORITE			0x2f
#घोषणा CEC_OP_UI_CMD_CHANNEL_UP			0x30
#घोषणा CEC_OP_UI_CMD_CHANNEL_DOWN			0x31
#घोषणा CEC_OP_UI_CMD_PREVIOUS_CHANNEL			0x32
#घोषणा CEC_OP_UI_CMD_SOUND_SELECT			0x33
#घोषणा CEC_OP_UI_CMD_INPUT_SELECT			0x34
#घोषणा CEC_OP_UI_CMD_DISPLAY_INFORMATION		0x35
#घोषणा CEC_OP_UI_CMD_HELP				0x36
#घोषणा CEC_OP_UI_CMD_PAGE_UP				0x37
#घोषणा CEC_OP_UI_CMD_PAGE_DOWN				0x38
#घोषणा CEC_OP_UI_CMD_POWER				0x40
#घोषणा CEC_OP_UI_CMD_VOLUME_UP				0x41
#घोषणा CEC_OP_UI_CMD_VOLUME_DOWN			0x42
#घोषणा CEC_OP_UI_CMD_MUTE				0x43
#घोषणा CEC_OP_UI_CMD_PLAY				0x44
#घोषणा CEC_OP_UI_CMD_STOP				0x45
#घोषणा CEC_OP_UI_CMD_PAUSE				0x46
#घोषणा CEC_OP_UI_CMD_RECORD				0x47
#घोषणा CEC_OP_UI_CMD_REWIND				0x48
#घोषणा CEC_OP_UI_CMD_FAST_FORWARD			0x49
#घोषणा CEC_OP_UI_CMD_EJECT				0x4a
#घोषणा CEC_OP_UI_CMD_SKIP_FORWARD			0x4b
#घोषणा CEC_OP_UI_CMD_SKIP_BACKWARD			0x4c
#घोषणा CEC_OP_UI_CMD_STOP_RECORD			0x4d
#घोषणा CEC_OP_UI_CMD_PAUSE_RECORD			0x4e
#घोषणा CEC_OP_UI_CMD_ANGLE				0x50
#घोषणा CEC_OP_UI_CMD_SUB_PICTURE			0x51
#घोषणा CEC_OP_UI_CMD_VIDEO_ON_DEMAND			0x52
#घोषणा CEC_OP_UI_CMD_ELECTRONIC_PROGRAM_GUIDE		0x53
#घोषणा CEC_OP_UI_CMD_TIMER_PROGRAMMING			0x54
#घोषणा CEC_OP_UI_CMD_INITIAL_CONFIGURATION		0x55
#घोषणा CEC_OP_UI_CMD_SELECT_BROADCAST_TYPE		0x56
#घोषणा CEC_OP_UI_CMD_SELECT_SOUND_PRESENTATION		0x57
#घोषणा CEC_OP_UI_CMD_AUDIO_DESCRIPTION			0x58
#घोषणा CEC_OP_UI_CMD_INTERNET				0x59
#घोषणा CEC_OP_UI_CMD_3D_MODE				0x5a
#घोषणा CEC_OP_UI_CMD_PLAY_FUNCTION			0x60
#घोषणा CEC_OP_UI_CMD_PAUSE_PLAY_FUNCTION		0x61
#घोषणा CEC_OP_UI_CMD_RECORD_FUNCTION			0x62
#घोषणा CEC_OP_UI_CMD_PAUSE_RECORD_FUNCTION		0x63
#घोषणा CEC_OP_UI_CMD_STOP_FUNCTION			0x64
#घोषणा CEC_OP_UI_CMD_MUTE_FUNCTION			0x65
#घोषणा CEC_OP_UI_CMD_RESTORE_VOLUME_FUNCTION		0x66
#घोषणा CEC_OP_UI_CMD_TUNE_FUNCTION			0x67
#घोषणा CEC_OP_UI_CMD_SELECT_MEDIA_FUNCTION		0x68
#घोषणा CEC_OP_UI_CMD_SELECT_AV_INPUT_FUNCTION		0x69
#घोषणा CEC_OP_UI_CMD_SELECT_AUDIO_INPUT_FUNCTION	0x6a
#घोषणा CEC_OP_UI_CMD_POWER_TOGGLE_FUNCTION		0x6b
#घोषणा CEC_OP_UI_CMD_POWER_OFF_FUNCTION		0x6c
#घोषणा CEC_OP_UI_CMD_POWER_ON_FUNCTION			0x6d
#घोषणा CEC_OP_UI_CMD_F1_BLUE				0x71
#घोषणा CEC_OP_UI_CMD_F2_RED				0x72
#घोषणा CEC_OP_UI_CMD_F3_GREEN				0x73
#घोषणा CEC_OP_UI_CMD_F4_YELLOW				0x74
#घोषणा CEC_OP_UI_CMD_F5				0x75
#घोषणा CEC_OP_UI_CMD_DATA				0x76
/* UI Broadcast Type Opeअक्रम (ui_bcast_type) */
#घोषणा CEC_OP_UI_BCAST_TYPE_TOGGLE_ALL			0x00
#घोषणा CEC_OP_UI_BCAST_TYPE_TOGGLE_DIG_ANA		0x01
#घोषणा CEC_OP_UI_BCAST_TYPE_ANALOGUE			0x10
#घोषणा CEC_OP_UI_BCAST_TYPE_ANALOGUE_T			0x20
#घोषणा CEC_OP_UI_BCAST_TYPE_ANALOGUE_CABLE		0x30
#घोषणा CEC_OP_UI_BCAST_TYPE_ANALOGUE_SAT		0x40
#घोषणा CEC_OP_UI_BCAST_TYPE_DIGITAL			0x50
#घोषणा CEC_OP_UI_BCAST_TYPE_DIGITAL_T			0x60
#घोषणा CEC_OP_UI_BCAST_TYPE_DIGITAL_CABLE		0x70
#घोषणा CEC_OP_UI_BCAST_TYPE_DIGITAL_SAT		0x80
#घोषणा CEC_OP_UI_BCAST_TYPE_DIGITAL_COM_SAT		0x90
#घोषणा CEC_OP_UI_BCAST_TYPE_DIGITAL_COM_SAT2		0x91
#घोषणा CEC_OP_UI_BCAST_TYPE_IP				0xa0
/* UI Sound Presentation Control Opeअक्रम (ui_snd_pres_ctl) */
#घोषणा CEC_OP_UI_SND_PRES_CTL_DUAL_MONO		0x10
#घोषणा CEC_OP_UI_SND_PRES_CTL_KARAOKE			0x20
#घोषणा CEC_OP_UI_SND_PRES_CTL_DOWNMIX			0x80
#घोषणा CEC_OP_UI_SND_PRES_CTL_REVERB			0x90
#घोषणा CEC_OP_UI_SND_PRES_CTL_EQUALIZER		0xa0
#घोषणा CEC_OP_UI_SND_PRES_CTL_BASS_UP			0xb1
#घोषणा CEC_OP_UI_SND_PRES_CTL_BASS_NEUTRAL		0xb2
#घोषणा CEC_OP_UI_SND_PRES_CTL_BASS_DOWN		0xb3
#घोषणा CEC_OP_UI_SND_PRES_CTL_TREBLE_UP		0xc1
#घोषणा CEC_OP_UI_SND_PRES_CTL_TREBLE_NEUTRAL		0xc2
#घोषणा CEC_OP_UI_SND_PRES_CTL_TREBLE_DOWN		0xc3

#घोषणा CEC_MSG_USER_CONTROL_RELEASED			0x45


/* Remote Control Passthrough Feature */

/*
 * Has also:
 *	CEC_MSG_USER_CONTROL_PRESSED
 *	CEC_MSG_USER_CONTROL_RELEASED
 */


/* Power Status Feature */
#घोषणा CEC_MSG_GIVE_DEVICE_POWER_STATUS		0x8f
#घोषणा CEC_MSG_REPORT_POWER_STATUS			0x90
/* Power Status Opeअक्रम (pwr_state) */
#घोषणा CEC_OP_POWER_STATUS_ON				0
#घोषणा CEC_OP_POWER_STATUS_STANDBY			1
#घोषणा CEC_OP_POWER_STATUS_TO_ON			2
#घोषणा CEC_OP_POWER_STATUS_TO_STANDBY			3


/* General Protocol Messages */
#घोषणा CEC_MSG_FEATURE_ABORT				0x00
/* Abort Reason Opeअक्रम (reason) */
#घोषणा CEC_OP_ABORT_UNRECOGNIZED_OP			0
#घोषणा CEC_OP_ABORT_INCORRECT_MODE			1
#घोषणा CEC_OP_ABORT_NO_SOURCE				2
#घोषणा CEC_OP_ABORT_INVALID_OP				3
#घोषणा CEC_OP_ABORT_REFUSED				4
#घोषणा CEC_OP_ABORT_UNDETERMINED			5

#घोषणा CEC_MSG_ABORT					0xff


/* System Audio Control Feature */

/*
 * Has also:
 *	CEC_MSG_USER_CONTROL_PRESSED
 *	CEC_MSG_USER_CONTROL_RELEASED
 */
#घोषणा CEC_MSG_GIVE_AUDIO_STATUS			0x71
#घोषणा CEC_MSG_GIVE_SYSTEM_AUDIO_MODE_STATUS		0x7d
#घोषणा CEC_MSG_REPORT_AUDIO_STATUS			0x7a
/* Audio Mute Status Opeअक्रम (aud_mute_status) */
#घोषणा CEC_OP_AUD_MUTE_STATUS_OFF			0
#घोषणा CEC_OP_AUD_MUTE_STATUS_ON			1

#घोषणा CEC_MSG_REPORT_SHORT_AUDIO_DESCRIPTOR		0xa3
#घोषणा CEC_MSG_REQUEST_SHORT_AUDIO_DESCRIPTOR		0xa4
#घोषणा CEC_MSG_SET_SYSTEM_AUDIO_MODE			0x72
/* System Audio Status Opeअक्रम (sys_aud_status) */
#घोषणा CEC_OP_SYS_AUD_STATUS_OFF			0
#घोषणा CEC_OP_SYS_AUD_STATUS_ON			1

#घोषणा CEC_MSG_SYSTEM_AUDIO_MODE_REQUEST		0x70
#घोषणा CEC_MSG_SYSTEM_AUDIO_MODE_STATUS		0x7e
/* Audio Format ID Opeअक्रम (audio_क्रमmat_id) */
#घोषणा CEC_OP_AUD_FMT_ID_CEA861			0
#घोषणा CEC_OP_AUD_FMT_ID_CEA861_CXT			1


/* Audio Rate Control Feature */
#घोषणा CEC_MSG_SET_AUDIO_RATE				0x9a
/* Audio Rate Opeअक्रम (audio_rate) */
#घोषणा CEC_OP_AUD_RATE_OFF				0
#घोषणा CEC_OP_AUD_RATE_WIDE_STD			1
#घोषणा CEC_OP_AUD_RATE_WIDE_FAST			2
#घोषणा CEC_OP_AUD_RATE_WIDE_SLOW			3
#घोषणा CEC_OP_AUD_RATE_NARROW_STD			4
#घोषणा CEC_OP_AUD_RATE_NARROW_FAST			5
#घोषणा CEC_OP_AUD_RATE_NARROW_SLOW			6


/* Audio Return Channel Control Feature */
#घोषणा CEC_MSG_INITIATE_ARC				0xc0
#घोषणा CEC_MSG_REPORT_ARC_INITIATED			0xc1
#घोषणा CEC_MSG_REPORT_ARC_TERMINATED			0xc2
#घोषणा CEC_MSG_REQUEST_ARC_INITIATION			0xc3
#घोषणा CEC_MSG_REQUEST_ARC_TERMINATION			0xc4
#घोषणा CEC_MSG_TERMINATE_ARC				0xc5


/* Dynamic Audio Lipsync Feature */
/* Only क्रम CEC 2.0 and up */
#घोषणा CEC_MSG_REQUEST_CURRENT_LATENCY			0xa7
#घोषणा CEC_MSG_REPORT_CURRENT_LATENCY			0xa8
/* Low Latency Mode Opeअक्रम (low_latency_mode) */
#घोषणा CEC_OP_LOW_LATENCY_MODE_OFF			0
#घोषणा CEC_OP_LOW_LATENCY_MODE_ON			1
/* Audio Output Compensated Opeअक्रम (audio_out_compensated) */
#घोषणा CEC_OP_AUD_OUT_COMPENSATED_NA			0
#घोषणा CEC_OP_AUD_OUT_COMPENSATED_DELAY		1
#घोषणा CEC_OP_AUD_OUT_COMPENSATED_NO_DELAY		2
#घोषणा CEC_OP_AUD_OUT_COMPENSATED_PARTIAL_DELAY	3


/* Capability Discovery and Control Feature */
#घोषणा CEC_MSG_CDC_MESSAGE				0xf8
/* Ethernet-over-HDMI: nobody ever करोes this... */
#घोषणा CEC_MSG_CDC_HEC_INQUIRE_STATE			0x00
#घोषणा CEC_MSG_CDC_HEC_REPORT_STATE			0x01
/* HEC Functionality State Opeअक्रम (hec_func_state) */
#घोषणा CEC_OP_HEC_FUNC_STATE_NOT_SUPPORTED		0
#घोषणा CEC_OP_HEC_FUNC_STATE_INACTIVE			1
#घोषणा CEC_OP_HEC_FUNC_STATE_ACTIVE			2
#घोषणा CEC_OP_HEC_FUNC_STATE_ACTIVATION_FIELD		3
/* Host Functionality State Opeअक्रम (host_func_state) */
#घोषणा CEC_OP_HOST_FUNC_STATE_NOT_SUPPORTED		0
#घोषणा CEC_OP_HOST_FUNC_STATE_INACTIVE			1
#घोषणा CEC_OP_HOST_FUNC_STATE_ACTIVE			2
/* ENC Functionality State Opeअक्रम (enc_func_state) */
#घोषणा CEC_OP_ENC_FUNC_STATE_EXT_CON_NOT_SUPPORTED	0
#घोषणा CEC_OP_ENC_FUNC_STATE_EXT_CON_INACTIVE		1
#घोषणा CEC_OP_ENC_FUNC_STATE_EXT_CON_ACTIVE		2
/* CDC Error Code Opeअक्रम (cdc_errcode) */
#घोषणा CEC_OP_CDC_ERROR_CODE_NONE			0
#घोषणा CEC_OP_CDC_ERROR_CODE_CAP_UNSUPPORTED		1
#घोषणा CEC_OP_CDC_ERROR_CODE_WRONG_STATE		2
#घोषणा CEC_OP_CDC_ERROR_CODE_OTHER			3
/* HEC Support Opeअक्रम (hec_support) */
#घोषणा CEC_OP_HEC_SUPPORT_NO				0
#घोषणा CEC_OP_HEC_SUPPORT_YES				1
/* HEC Activation Opeअक्रम (hec_activation) */
#घोषणा CEC_OP_HEC_ACTIVATION_ON			0
#घोषणा CEC_OP_HEC_ACTIVATION_OFF			1

#घोषणा CEC_MSG_CDC_HEC_SET_STATE_ADJACENT		0x02
#घोषणा CEC_MSG_CDC_HEC_SET_STATE			0x03
/* HEC Set State Opeअक्रम (hec_set_state) */
#घोषणा CEC_OP_HEC_SET_STATE_DEACTIVATE			0
#घोषणा CEC_OP_HEC_SET_STATE_ACTIVATE			1

#घोषणा CEC_MSG_CDC_HEC_REQUEST_DEACTIVATION		0x04
#घोषणा CEC_MSG_CDC_HEC_NOTIFY_ALIVE			0x05
#घोषणा CEC_MSG_CDC_HEC_DISCOVER			0x06
/* Hotplug Detect messages */
#घोषणा CEC_MSG_CDC_HPD_SET_STATE			0x10
/* HPD State Opeअक्रम (hpd_state) */
#घोषणा CEC_OP_HPD_STATE_CP_EDID_DISABLE		0
#घोषणा CEC_OP_HPD_STATE_CP_EDID_ENABLE			1
#घोषणा CEC_OP_HPD_STATE_CP_EDID_DISABLE_ENABLE		2
#घोषणा CEC_OP_HPD_STATE_EDID_DISABLE			3
#घोषणा CEC_OP_HPD_STATE_EDID_ENABLE			4
#घोषणा CEC_OP_HPD_STATE_EDID_DISABLE_ENABLE		5
#घोषणा CEC_MSG_CDC_HPD_REPORT_STATE			0x11
/* HPD Error Code Opeअक्रम (hpd_error) */
#घोषणा CEC_OP_HPD_ERROR_NONE				0
#घोषणा CEC_OP_HPD_ERROR_INITIATOR_NOT_CAPABLE		1
#घोषणा CEC_OP_HPD_ERROR_INITIATOR_WRONG_STATE		2
#घोषणा CEC_OP_HPD_ERROR_OTHER				3
#घोषणा CEC_OP_HPD_ERROR_NONE_NO_VIDEO			4

/* End of Messages */

/* Helper functions to identअगरy the 'special' CEC devices */

अटल अंतरभूत पूर्णांक cec_is_2nd_tv(स्थिर काष्ठा cec_log_addrs *las)
अणु
	/*
	 * It is a second TV अगर the logical address is 14 or 15 and the
	 * primary device type is a TV.
	 */
	वापस las->num_log_addrs &&
	       las->log_addr[0] >= CEC_LOG_ADDR_SPECIFIC &&
	       las->primary_device_type[0] == CEC_OP_PRIM_DEVTYPE_TV;
पूर्ण

अटल अंतरभूत पूर्णांक cec_is_processor(स्थिर काष्ठा cec_log_addrs *las)
अणु
	/*
	 * It is a processor अगर the logical address is 12-15 and the
	 * primary device type is a Processor.
	 */
	वापस las->num_log_addrs &&
	       las->log_addr[0] >= CEC_LOG_ADDR_BACKUP_1 &&
	       las->primary_device_type[0] == CEC_OP_PRIM_DEVTYPE_PROCESSOR;
पूर्ण

अटल अंतरभूत पूर्णांक cec_is_चयन(स्थिर काष्ठा cec_log_addrs *las)
अणु
	/*
	 * It is a चयन अगर the logical address is 15 and the
	 * primary device type is a Switch and the CDC-Only flag is not set.
	 */
	वापस las->num_log_addrs == 1 &&
	       las->log_addr[0] == CEC_LOG_ADDR_UNREGISTERED &&
	       las->primary_device_type[0] == CEC_OP_PRIM_DEVTYPE_SWITCH &&
	       !(las->flags & CEC_LOG_ADDRS_FL_CDC_ONLY);
पूर्ण

अटल अंतरभूत पूर्णांक cec_is_cdc_only(स्थिर काष्ठा cec_log_addrs *las)
अणु
	/*
	 * It is a CDC-only device अगर the logical address is 15 and the
	 * primary device type is a Switch and the CDC-Only flag is set.
	 */
	वापस las->num_log_addrs == 1 &&
	       las->log_addr[0] == CEC_LOG_ADDR_UNREGISTERED &&
	       las->primary_device_type[0] == CEC_OP_PRIM_DEVTYPE_SWITCH &&
	       (las->flags & CEC_LOG_ADDRS_FL_CDC_ONLY);
पूर्ण

#पूर्ण_अगर
