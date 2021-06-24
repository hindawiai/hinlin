<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Surface Serial Hub (SSH) protocol and communication पूर्णांकerface.
 *
 * Lower-level communication layers and SSH protocol definitions क्रम the
 * Surface System Aggregator Module (SSAM). Provides the पूर्णांकerface क्रम basic
 * packet- and request-based communication with the SSAM EC via SSH.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _LINUX_SURFACE_AGGREGATOR_SERIAL_HUB_H
#घोषणा _LINUX_SURFACE_AGGREGATOR_SERIAL_HUB_H

#समावेश <linux/crc-ccitt.h>
#समावेश <linux/kref.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/types.h>


/* -- Data काष्ठाures क्रम SAM-over-SSH communication. ----------------------- */

/**
 * क्रमागत ssh_frame_type - Frame types क्रम SSH frames.
 *
 * @SSH_FRAME_TYPE_DATA_SEQ:
 *	Indicates a data frame, followed by a payload with the length specअगरied
 *	in the ``काष्ठा ssh_frame.len`` field. This frame is sequenced, meaning
 *	that an ACK is required.
 *
 * @SSH_FRAME_TYPE_DATA_NSQ:
 *	Same as %SSH_FRAME_TYPE_DATA_SEQ, but unsequenced, meaning that the
 *	message करोes not have to be ACKed.
 *
 * @SSH_FRAME_TYPE_ACK:
 *	Indicates an ACK message.
 *
 * @SSH_FRAME_TYPE_NAK:
 *	Indicates an error response क्रम previously sent frame. In general, this
 *	means that the frame and/or payload is malक्रमmed, e.g. a CRC is wrong.
 *	For command-type payloads, this can also mean that the command is
 *	invalid.
 */
क्रमागत ssh_frame_type अणु
	SSH_FRAME_TYPE_DATA_SEQ = 0x80,
	SSH_FRAME_TYPE_DATA_NSQ = 0x00,
	SSH_FRAME_TYPE_ACK      = 0x40,
	SSH_FRAME_TYPE_NAK      = 0x04,
पूर्ण;

/**
 * काष्ठा ssh_frame - SSH communication frame.
 * @type: The type of the frame. See &क्रमागत ssh_frame_type.
 * @len:  The length of the frame payload directly following the CRC क्रम this
 *        frame. Does not include the final CRC क्रम that payload.
 * @seq:  The sequence number क्रम this message/exchange.
 */
काष्ठा ssh_frame अणु
	u8 type;
	__le16 len;
	u8 seq;
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा ssh_frame) == 4);

/*
 * SSH_FRAME_MAX_PAYLOAD_SIZE - Maximum SSH frame payload length in bytes.
 *
 * This is the physical maximum length of the protocol. Implementations may
 * set a more स्थिरrained limit.
 */
#घोषणा SSH_FRAME_MAX_PAYLOAD_SIZE	U16_MAX

/**
 * क्रमागत ssh_payload_type - Type indicator क्रम the SSH payload.
 * @SSH_PLD_TYPE_CMD: The payload is a command काष्ठाure with optional command
 *                    payload.
 */
क्रमागत ssh_payload_type अणु
	SSH_PLD_TYPE_CMD = 0x80,
पूर्ण;

/**
 * काष्ठा ssh_command - Payload of a command-type frame.
 * @type:    The type of the payload. See &क्रमागत ssh_payload_type. Should be
 *           SSH_PLD_TYPE_CMD क्रम this काष्ठा.
 * @tc:      Command target category.
 * @tid_out: Output target ID. Should be zero अगर this an incoming (EC to host)
 *           message.
 * @tid_in:  Input target ID. Should be zero अगर this is an outgoing (host to
 *           EC) message.
 * @iid:     Instance ID.
 * @rqid:    Request ID. Used to match requests with responses and dअगरferentiate
 *           between responses and events.
 * @cid:     Command ID.
 */
काष्ठा ssh_command अणु
	u8 type;
	u8 tc;
	u8 tid_out;
	u8 tid_in;
	u8 iid;
	__le16 rqid;
	u8 cid;
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा ssh_command) == 8);

/*
 * SSH_COMMAND_MAX_PAYLOAD_SIZE - Maximum SSH command payload length in bytes.
 *
 * This is the physical maximum length of the protocol. Implementations may
 * set a more स्थिरrained limit.
 */
#घोषणा SSH_COMMAND_MAX_PAYLOAD_SIZE \
	(SSH_FRAME_MAX_PAYLOAD_SIZE - माप(काष्ठा ssh_command))

/*
 * SSH_MSG_LEN_BASE - Base-length of a SSH message.
 *
 * This is the minimum number of bytes required to क्रमm a message. The actual
 * message length is SSH_MSG_LEN_BASE plus the length of the frame payload.
 */
#घोषणा SSH_MSG_LEN_BASE	(माप(काष्ठा ssh_frame) + 3ull * माप(u16))

/*
 * SSH_MSG_LEN_CTRL - Length of a SSH control message.
 *
 * This is the length of a SSH control message, which is equal to a SSH
 * message without any payload.
 */
#घोषणा SSH_MSG_LEN_CTRL	SSH_MSG_LEN_BASE

/**
 * SSH_MESSAGE_LENGTH() - Compute length of SSH message.
 * @payload_size: Length of the payload inside the SSH frame.
 *
 * Return: Returns the length of a SSH message with payload of specअगरied size.
 */
#घोषणा SSH_MESSAGE_LENGTH(payload_size) (SSH_MSG_LEN_BASE + (payload_size))

/**
 * SSH_COMMAND_MESSAGE_LENGTH() - Compute length of SSH command message.
 * @payload_size: Length of the command payload.
 *
 * Return: Returns the length of a SSH command message with command payload of
 * specअगरied size.
 */
#घोषणा SSH_COMMAND_MESSAGE_LENGTH(payload_size) \
	SSH_MESSAGE_LENGTH(माप(काष्ठा ssh_command) + (payload_size))

/**
 * SSH_MSGOFFSET_FRAME() - Compute offset in SSH message to specअगरied field in
 * frame.
 * @field: The field क्रम which the offset should be computed.
 *
 * Return: Returns the offset of the specअगरied &काष्ठा ssh_frame field in the
 * raw SSH message data as. Takes SYN bytes (u16) preceding the frame पूर्णांकo
 * account.
 */
#घोषणा SSH_MSGOFFSET_FRAME(field) \
	(माप(u16) + दुरत्व(काष्ठा ssh_frame, field))

/**
 * SSH_MSGOFFSET_COMMAND() - Compute offset in SSH message to specअगरied field
 * in command.
 * @field: The field क्रम which the offset should be computed.
 *
 * Return: Returns the offset of the specअगरied &काष्ठा ssh_command field in
 * the raw SSH message data. Takes SYN bytes (u16) preceding the frame and the
 * frame CRC (u16) between frame and command पूर्णांकo account.
 */
#घोषणा SSH_MSGOFFSET_COMMAND(field) \
	(2ull * माप(u16) + माप(काष्ठा ssh_frame) \
		+ दुरत्व(काष्ठा ssh_command, field))

/*
 * SSH_MSG_SYN - SSH message synchronization (SYN) bytes as u16.
 */
#घोषणा SSH_MSG_SYN		((u16)0x55aa)

/**
 * ssh_crc() - Compute CRC क्रम SSH messages.
 * @buf: The poपूर्णांकer poपूर्णांकing to the data क्रम which the CRC should be computed.
 * @len: The length of the data क्रम which the CRC should be computed.
 *
 * Return: Returns the CRC computed on the provided data, as used क्रम SSH
 * messages.
 */
अटल अंतरभूत u16 ssh_crc(स्थिर u8 *buf, माप_प्रकार len)
अणु
	वापस crc_ccitt_false(0xffff, buf, len);
पूर्ण

/*
 * SSH_NUM_EVENTS - The number of reserved event IDs.
 *
 * The number of reserved event IDs, used क्रम रेजिस्टरing an SSH event
 * handler. Valid event IDs are numbers below or equal to this value, with
 * exception of zero, which is not an event ID. Thus, this is also the
 * असलolute maximum number of event handlers that can be रेजिस्टरed.
 */
#घोषणा SSH_NUM_EVENTS		34

/*
 * SSH_NUM_TARGETS - The number of communication tarमाला_लो used in the protocol.
 */
#घोषणा SSH_NUM_TARGETS		2

/**
 * ssh_rqid_next_valid() - Return the next valid request ID.
 * @rqid: The current request ID.
 *
 * Return: Returns the next valid request ID, following the current request ID
 * provided to this function. This function skips any request IDs reserved क्रम
 * events.
 */
अटल अंतरभूत u16 ssh_rqid_next_valid(u16 rqid)
अणु
	वापस rqid > 0 ? rqid + 1u : rqid + SSH_NUM_EVENTS + 1u;
पूर्ण

/**
 * ssh_rqid_to_event() - Convert request ID to its corresponding event ID.
 * @rqid: The request ID to convert.
 */
अटल अंतरभूत u16 ssh_rqid_to_event(u16 rqid)
अणु
	वापस rqid - 1u;
पूर्ण

/**
 * ssh_rqid_is_event() - Check अगर given request ID is a valid event ID.
 * @rqid: The request ID to check.
 */
अटल अंतरभूत bool ssh_rqid_is_event(u16 rqid)
अणु
	वापस ssh_rqid_to_event(rqid) < SSH_NUM_EVENTS;
पूर्ण

/**
 * ssh_tc_to_rqid() - Convert target category to its corresponding request ID.
 * @tc: The target category to convert.
 */
अटल अंतरभूत u16 ssh_tc_to_rqid(u8 tc)
अणु
	वापस tc;
पूर्ण

/**
 * ssh_tid_to_index() - Convert target ID to its corresponding target index.
 * @tid: The target ID to convert.
 */
अटल अंतरभूत u8 ssh_tid_to_index(u8 tid)
अणु
	वापस tid - 1u;
पूर्ण

/**
 * ssh_tid_is_valid() - Check अगर target ID is valid/supported.
 * @tid: The target ID to check.
 */
अटल अंतरभूत bool ssh_tid_is_valid(u8 tid)
अणु
	वापस ssh_tid_to_index(tid) < SSH_NUM_TARGETS;
पूर्ण

/**
 * काष्ठा ssam_span - Reference to a buffer region.
 * @ptr: Poपूर्णांकer to the buffer region.
 * @len: Length of the buffer region.
 *
 * A reference to a (non-owned) buffer segment, consisting of poपूर्णांकer and
 * length. Use of this काष्ठा indicates non-owned data, i.e. data of which the
 * lअगरe-समय is managed (i.e. it is allocated/मुक्तd) via another poपूर्णांकer.
 */
काष्ठा ssam_span अणु
	u8    *ptr;
	माप_प्रकार len;
पूर्ण;

/*
 * Known SSH/EC target categories.
 *
 * List of currently known target category values; "Known" as in we know they
 * exist and are valid on at least some device/model. Detailed functionality
 * or the full category name is only known क्रम some of these categories and
 * is detailed in the respective comment below.
 *
 * These values and abbreviations have been extracted from strings inside the
 * Winकरोws driver.
 */
क्रमागत ssam_ssh_tc अणु
				/* Category 0x00 is invalid क्रम EC use. */
	SSAM_SSH_TC_SAM = 0x01,	/* Generic प्रणाली functionality, real-समय घड़ी. */
	SSAM_SSH_TC_BAT = 0x02,	/* Battery/घातer subप्रणाली. */
	SSAM_SSH_TC_TMP = 0x03,	/* Thermal subप्रणाली. */
	SSAM_SSH_TC_PMC = 0x04,
	SSAM_SSH_TC_FAN = 0x05,
	SSAM_SSH_TC_PoM = 0x06,
	SSAM_SSH_TC_DBG = 0x07,
	SSAM_SSH_TC_KBD = 0x08,	/* Legacy keyboard (Laptop 1/2). */
	SSAM_SSH_TC_FWU = 0x09,
	SSAM_SSH_TC_UNI = 0x0a,
	SSAM_SSH_TC_LPC = 0x0b,
	SSAM_SSH_TC_TCL = 0x0c,
	SSAM_SSH_TC_SFL = 0x0d,
	SSAM_SSH_TC_KIP = 0x0e,
	SSAM_SSH_TC_EXT = 0x0f,
	SSAM_SSH_TC_BLD = 0x10,
	SSAM_SSH_TC_BAS = 0x11,	/* Detachment प्रणाली (Surface Book 2/3). */
	SSAM_SSH_TC_SEN = 0x12,
	SSAM_SSH_TC_SRQ = 0x13,
	SSAM_SSH_TC_MCU = 0x14,
	SSAM_SSH_TC_HID = 0x15,	/* Generic HID input subप्रणाली. */
	SSAM_SSH_TC_TCH = 0x16,
	SSAM_SSH_TC_BKL = 0x17,
	SSAM_SSH_TC_TAM = 0x18,
	SSAM_SSH_TC_ACC = 0x19,
	SSAM_SSH_TC_UFI = 0x1a,
	SSAM_SSH_TC_USC = 0x1b,
	SSAM_SSH_TC_PEN = 0x1c,
	SSAM_SSH_TC_VID = 0x1d,
	SSAM_SSH_TC_AUD = 0x1e,
	SSAM_SSH_TC_SMC = 0x1f,
	SSAM_SSH_TC_KPD = 0x20,
	SSAM_SSH_TC_REG = 0x21,	/* Extended event registry. */
पूर्ण;


/* -- Packet transport layer (ptl). ----------------------------------------- */

/**
 * क्रमागत ssh_packet_base_priority - Base priorities क्रम &काष्ठा ssh_packet.
 * @SSH_PACKET_PRIORITY_FLUSH: Base priority क्रम flush packets.
 * @SSH_PACKET_PRIORITY_DATA:  Base priority क्रम normal data packets.
 * @SSH_PACKET_PRIORITY_NAK:   Base priority क्रम NAK packets.
 * @SSH_PACKET_PRIORITY_ACK:   Base priority क्रम ACK packets.
 */
क्रमागत ssh_packet_base_priority अणु
	SSH_PACKET_PRIORITY_FLUSH = 0,	/* same as DATA to sequence flush */
	SSH_PACKET_PRIORITY_DATA  = 0,
	SSH_PACKET_PRIORITY_NAK   = 1,
	SSH_PACKET_PRIORITY_ACK   = 2,
पूर्ण;

/*
 * Same as SSH_PACKET_PRIORITY() below, only with actual values.
 */
#घोषणा __SSH_PACKET_PRIORITY(base, try) \
	(((base) << 4) | ((try) & 0x0f))

/**
 * SSH_PACKET_PRIORITY() - Compute packet priority from base priority and
 * number of tries.
 * @base: The base priority as suffix of &क्रमागत ssh_packet_base_priority, e.g.
 *        ``FLUSH``, ``DATA``, ``ACK``, or ``NAK``.
 * @try:  The number of tries (must be less than 16).
 *
 * Compute the combined packet priority. The combined priority is करोminated by
 * the base priority, whereas the number of (re-)tries decides the precedence
 * of packets with the same base priority, giving higher priority to packets
 * that alपढ़ोy have more tries.
 *
 * Return: Returns the computed priority as value fitting inside a &u8. A
 * higher number means a higher priority.
 */
#घोषणा SSH_PACKET_PRIORITY(base, try) \
	__SSH_PACKET_PRIORITY(SSH_PACKET_PRIORITY_##base, (try))

/**
 * ssh_packet_priority_get_try() - Get number of tries from packet priority.
 * @priority: The packet priority.
 *
 * Return: Returns the number of tries encoded in the specअगरied packet
 * priority.
 */
अटल अंतरभूत u8 ssh_packet_priority_get_try(u8 priority)
अणु
	वापस priority & 0x0f;
पूर्ण

/**
 * ssh_packet_priority_get_base - Get base priority from packet priority.
 * @priority: The packet priority.
 *
 * Return: Returns the base priority encoded in the given packet priority.
 */
अटल अंतरभूत u8 ssh_packet_priority_get_base(u8 priority)
अणु
	वापस (priority & 0xf0) >> 4;
पूर्ण

क्रमागत ssh_packet_flags अणु
	/* state flags */
	SSH_PACKET_SF_LOCKED_BIT,
	SSH_PACKET_SF_QUEUED_BIT,
	SSH_PACKET_SF_PENDING_BIT,
	SSH_PACKET_SF_TRANSMITTING_BIT,
	SSH_PACKET_SF_TRANSMITTED_BIT,
	SSH_PACKET_SF_ACKED_BIT,
	SSH_PACKET_SF_CANCELED_BIT,
	SSH_PACKET_SF_COMPLETED_BIT,

	/* type flags */
	SSH_PACKET_TY_FLUSH_BIT,
	SSH_PACKET_TY_SEQUENCED_BIT,
	SSH_PACKET_TY_BLOCKING_BIT,

	/* mask क्रम state flags */
	SSH_PACKET_FLAGS_SF_MASK =
		  BIT(SSH_PACKET_SF_LOCKED_BIT)
		| BIT(SSH_PACKET_SF_QUEUED_BIT)
		| BIT(SSH_PACKET_SF_PENDING_BIT)
		| BIT(SSH_PACKET_SF_TRANSMITTING_BIT)
		| BIT(SSH_PACKET_SF_TRANSMITTED_BIT)
		| BIT(SSH_PACKET_SF_ACKED_BIT)
		| BIT(SSH_PACKET_SF_CANCELED_BIT)
		| BIT(SSH_PACKET_SF_COMPLETED_BIT),

	/* mask क्रम type flags */
	SSH_PACKET_FLAGS_TY_MASK =
		  BIT(SSH_PACKET_TY_FLUSH_BIT)
		| BIT(SSH_PACKET_TY_SEQUENCED_BIT)
		| BIT(SSH_PACKET_TY_BLOCKING_BIT),
पूर्ण;

काष्ठा ssh_ptl;
काष्ठा ssh_packet;

/**
 * काष्ठा ssh_packet_ops - Callback operations क्रम a SSH packet.
 * @release:  Function called when the packet reference count reaches zero.
 *            This callback must be relied upon to ensure that the packet has
 *            left the transport प्रणाली(s).
 * @complete: Function called when the packet is completed, either with
 *            success or failure. In हाल of failure, the reason क्रम the
 *            failure is indicated by the value of the provided status code
 *            argument. This value will be zero in हाल of success. Note that
 *            a call to this callback करोes not guarantee that the packet is
 *            not in use by the transport प्रणाली any more.
 */
काष्ठा ssh_packet_ops अणु
	व्योम (*release)(काष्ठा ssh_packet *p);
	व्योम (*complete)(काष्ठा ssh_packet *p, पूर्णांक status);
पूर्ण;

/**
 * काष्ठा ssh_packet - SSH transport packet.
 * @ptl:      Poपूर्णांकer to the packet transport layer. May be %शून्य अगर the packet
 *            (or enclosing request) has not been submitted yet.
 * @refcnt:   Reference count of the packet.
 * @priority: Priority of the packet. Must be computed via
 *            SSH_PACKET_PRIORITY(). Must only be accessed जबतक holding the
 *            queue lock after first submission.
 * @data:     Raw message data.
 * @data.len: Length of the raw message data.
 * @data.ptr: Poपूर्णांकer to the raw message data buffer.
 * @state:    State and type flags describing current packet state (dynamic)
 *            and type (अटल). See &क्रमागत ssh_packet_flags क्रम possible
 *            options.
 * @बारtamp: Timestamp specअगरying when the latest transmission of a
 *            currently pending packet has been started. May be %KTIME_MAX
 *            beक्रमe or in-between transmission attempts. Used क्रम the packet
 *            समयout implementation. Must only be accessed जबतक holding the
 *            pending lock after first submission.
 * @queue_node:	The list node क्रम the packet queue.
 * @pending_node: The list node क्रम the set of pending packets.
 * @ops:      Packet operations.
 */
काष्ठा ssh_packet अणु
	काष्ठा ssh_ptl *ptl;
	काष्ठा kref refcnt;

	u8 priority;

	काष्ठा अणु
		माप_प्रकार len;
		u8 *ptr;
	पूर्ण data;

	अचिन्हित दीर्घ state;
	kसमय_प्रकार बारtamp;

	काष्ठा list_head queue_node;
	काष्ठा list_head pending_node;

	स्थिर काष्ठा ssh_packet_ops *ops;
पूर्ण;

काष्ठा ssh_packet *ssh_packet_get(काष्ठा ssh_packet *p);
व्योम ssh_packet_put(काष्ठा ssh_packet *p);

/**
 * ssh_packet_set_data() - Set raw message data of packet.
 * @p:   The packet क्रम which the message data should be set.
 * @ptr: Poपूर्णांकer to the memory holding the message data.
 * @len: Length of the message data.
 *
 * Sets the raw message data buffer of the packet to the provided memory. The
 * memory is not copied. Instead, the caller is responsible क्रम management
 * (i.e. allocation and deallocation) of the memory. The caller must ensure
 * that the provided memory is valid and contains a valid SSH message,
 * starting from the समय of submission of the packet until the ``release``
 * callback has been called. During this समय, the memory may not be altered
 * in any way.
 */
अटल अंतरभूत व्योम ssh_packet_set_data(काष्ठा ssh_packet *p, u8 *ptr, माप_प्रकार len)
अणु
	p->data.ptr = ptr;
	p->data.len = len;
पूर्ण


/* -- Request transport layer (rtl). ---------------------------------------- */

क्रमागत ssh_request_flags अणु
	/* state flags */
	SSH_REQUEST_SF_LOCKED_BIT,
	SSH_REQUEST_SF_QUEUED_BIT,
	SSH_REQUEST_SF_PENDING_BIT,
	SSH_REQUEST_SF_TRANSMITTING_BIT,
	SSH_REQUEST_SF_TRANSMITTED_BIT,
	SSH_REQUEST_SF_RSPRCVD_BIT,
	SSH_REQUEST_SF_CANCELED_BIT,
	SSH_REQUEST_SF_COMPLETED_BIT,

	/* type flags */
	SSH_REQUEST_TY_FLUSH_BIT,
	SSH_REQUEST_TY_HAS_RESPONSE_BIT,

	/* mask क्रम state flags */
	SSH_REQUEST_FLAGS_SF_MASK =
		  BIT(SSH_REQUEST_SF_LOCKED_BIT)
		| BIT(SSH_REQUEST_SF_QUEUED_BIT)
		| BIT(SSH_REQUEST_SF_PENDING_BIT)
		| BIT(SSH_REQUEST_SF_TRANSMITTING_BIT)
		| BIT(SSH_REQUEST_SF_TRANSMITTED_BIT)
		| BIT(SSH_REQUEST_SF_RSPRCVD_BIT)
		| BIT(SSH_REQUEST_SF_CANCELED_BIT)
		| BIT(SSH_REQUEST_SF_COMPLETED_BIT),

	/* mask क्रम type flags */
	SSH_REQUEST_FLAGS_TY_MASK =
		  BIT(SSH_REQUEST_TY_FLUSH_BIT)
		| BIT(SSH_REQUEST_TY_HAS_RESPONSE_BIT),
पूर्ण;

काष्ठा ssh_rtl;
काष्ठा ssh_request;

/**
 * काष्ठा ssh_request_ops - Callback operations क्रम a SSH request.
 * @release:  Function called when the request's reference count reaches zero.
 *            This callback must be relied upon to ensure that the request has
 *            left the transport प्रणालीs (both, packet an request प्रणालीs).
 * @complete: Function called when the request is completed, either with
 *            success or failure. The command data क्रम the request response
 *            is provided via the &काष्ठा ssh_command parameter (``cmd``),
 *            the command payload of the request response via the &काष्ठा
 *            ssh_span parameter (``data``).
 *
 *            If the request करोes not have any response or has not been
 *            completed with success, both ``cmd`` and ``data`` parameters will
 *            be शून्य. If the request response करोes not have any command
 *            payload, the ``data`` span will be an empty (zero-length) span.
 *
 *            In हाल of failure, the reason क्रम the failure is indicated by
 *            the value of the provided status code argument (``status``). This
 *            value will be zero in हाल of success and a regular त्रुटि_सं
 *            otherwise.
 *
 *            Note that a call to this callback करोes not guarantee that the
 *            request is not in use by the transport प्रणालीs any more.
 */
काष्ठा ssh_request_ops अणु
	व्योम (*release)(काष्ठा ssh_request *rqst);
	व्योम (*complete)(काष्ठा ssh_request *rqst,
			 स्थिर काष्ठा ssh_command *cmd,
			 स्थिर काष्ठा ssam_span *data, पूर्णांक status);
पूर्ण;

/**
 * काष्ठा ssh_request - SSH transport request.
 * @packet: The underlying SSH transport packet.
 * @node:   List node क्रम the request queue and pending set.
 * @state:  State and type flags describing current request state (dynamic)
 *          and type (अटल). See &क्रमागत ssh_request_flags क्रम possible
 *          options.
 * @बारtamp: Timestamp specअगरying when we start रुकोing on the response of
 *          the request. This is set once the underlying packet has been
 *          completed and may be %KTIME_MAX beक्रमe that, or when the request
 *          करोes not expect a response. Used क्रम the request समयout
 *          implementation.
 * @ops:    Request Operations.
 */
काष्ठा ssh_request अणु
	काष्ठा ssh_packet packet;
	काष्ठा list_head node;

	अचिन्हित दीर्घ state;
	kसमय_प्रकार बारtamp;

	स्थिर काष्ठा ssh_request_ops *ops;
पूर्ण;

/**
 * to_ssh_request() - Cast a SSH packet to its enclosing SSH request.
 * @p: The packet to cast.
 *
 * Casts the given &काष्ठा ssh_packet to its enclosing &काष्ठा ssh_request.
 * The caller is responsible क्रम making sure that the packet is actually
 * wrapped in a &काष्ठा ssh_request.
 *
 * Return: Returns the &काष्ठा ssh_request wrapping the provided packet.
 */
अटल अंतरभूत काष्ठा ssh_request *to_ssh_request(काष्ठा ssh_packet *p)
अणु
	वापस container_of(p, काष्ठा ssh_request, packet);
पूर्ण

/**
 * ssh_request_get() - Increment reference count of request.
 * @r: The request to increment the reference count of.
 *
 * Increments the reference count of the given request by incrementing the
 * reference count of the underlying &काष्ठा ssh_packet, enबंदd in it.
 *
 * See also ssh_request_put(), ssh_packet_get().
 *
 * Return: Returns the request provided as input.
 */
अटल अंतरभूत काष्ठा ssh_request *ssh_request_get(काष्ठा ssh_request *r)
अणु
	वापस r ? to_ssh_request(ssh_packet_get(&r->packet)) : शून्य;
पूर्ण

/**
 * ssh_request_put() - Decrement reference count of request.
 * @r: The request to decrement the reference count of.
 *
 * Decrements the reference count of the given request by decrementing the
 * reference count of the underlying &काष्ठा ssh_packet, enबंदd in it. If
 * the reference count reaches zero, the ``release`` callback specअगरied in the
 * request's &काष्ठा ssh_request_ops, i.e. ``r->ops->release``, will be
 * called.
 *
 * See also ssh_request_get(), ssh_packet_put().
 */
अटल अंतरभूत व्योम ssh_request_put(काष्ठा ssh_request *r)
अणु
	अगर (r)
		ssh_packet_put(&r->packet);
पूर्ण

/**
 * ssh_request_set_data() - Set raw message data of request.
 * @r:   The request क्रम which the message data should be set.
 * @ptr: Poपूर्णांकer to the memory holding the message data.
 * @len: Length of the message data.
 *
 * Sets the raw message data buffer of the underlying packet to the specअगरied
 * buffer. Does not copy the actual message data, just sets the buffer poपूर्णांकer
 * and length. Refer to ssh_packet_set_data() क्रम more details.
 */
अटल अंतरभूत व्योम ssh_request_set_data(काष्ठा ssh_request *r, u8 *ptr, माप_प्रकार len)
अणु
	ssh_packet_set_data(&r->packet, ptr, len);
पूर्ण

#पूर्ण_अगर /* _LINUX_SURFACE_AGGREGATOR_SERIAL_HUB_H */
