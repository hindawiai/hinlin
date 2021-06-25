<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_समय_event_h__
#घोषणा __iwl_fw_api_समय_event_h__

#समावेश "fw/api/phy-ctxt.h"

/* Time Event types, according to MAC type */
क्रमागत iwl_समय_event_type अणु
	/* BSS Station Events */
	TE_BSS_STA_AGGRESSIVE_ASSOC,
	TE_BSS_STA_ASSOC,
	TE_BSS_EAP_DHCP_PROT,
	TE_BSS_QUIET_PERIOD,

	/* P2P Device Events */
	TE_P2P_DEVICE_DISCOVERABLE,
	TE_P2P_DEVICE_LISTEN,
	TE_P2P_DEVICE_ACTION_SCAN,
	TE_P2P_DEVICE_FULL_SCAN,

	/* P2P Client Events */
	TE_P2P_CLIENT_AGGRESSIVE_ASSOC,
	TE_P2P_CLIENT_ASSOC,
	TE_P2P_CLIENT_QUIET_PERIOD,

	/* P2P GO Events */
	TE_P2P_GO_ASSOC_PROT,
	TE_P2P_GO_REPETITIVET_NOA,
	TE_P2P_GO_CT_WINDOW,

	/* WiDi Sync Events */
	TE_WIDI_TX_SYNC,

	/* Channel Switch NoA */
	TE_CHANNEL_SWITCH_PERIOD,

	TE_MAX
पूर्ण; /* MAC_EVENT_TYPE_API_E_VER_1 */

/* Time event - defines क्रम command API v1 */

/*
 * @TE_V1_FRAG_NONE: fragmentation of the समय event is NOT allowed.
 * @TE_V1_FRAG_SINGLE: fragmentation of the समय event is allowed, but only
 *	the first fragment is scheduled.
 * @TE_V1_FRAG_DUAL: fragmentation of the समय event is allowed, but only
 *	the first 2 fragments are scheduled.
 * @TE_V1_FRAG_ENDLESS: fragmentation of the समय event is allowed, and any
 *	number of fragments are valid.
 *
 * Other than the स्थिरant defined above, specअगरying a fragmentation value 'x'
 * means that the event can be fragmented but only the first 'x' will be
 * scheduled.
 */
क्रमागत अणु
	TE_V1_FRAG_NONE = 0,
	TE_V1_FRAG_SINGLE = 1,
	TE_V1_FRAG_DUAL = 2,
	TE_V1_FRAG_ENDLESS = 0xffffffff
पूर्ण;

/* If a Time Event can be fragmented, this is the max number of fragments */
#घोषणा TE_V1_FRAG_MAX_MSK	0x0fffffff
/* Repeat the समय event endlessly (until हटाओd) */
#घोषणा TE_V1_REPEAT_ENDLESS	0xffffffff
/* If a Time Event has bounded repetitions, this is the maximal value */
#घोषणा TE_V1_REPEAT_MAX_MSK_V1	0x0fffffff

/* Time Event dependencies: none, on another TE, or in a specअगरic समय */
क्रमागत अणु
	TE_V1_INDEPENDENT		= 0,
	TE_V1_DEP_OTHER			= BIT(0),
	TE_V1_DEP_TSF			= BIT(1),
	TE_V1_EVENT_SOCIOPATHIC		= BIT(2),
पूर्ण; /* MAC_EVENT_DEPENDENCY_POLICY_API_E_VER_2 */

/*
 * @TE_V1_NOTIF_NONE: no notअगरications
 * @TE_V1_NOTIF_HOST_EVENT_START: request/receive notअगरication on event start
 * @TE_V1_NOTIF_HOST_EVENT_END:request/receive notअगरication on event end
 * @TE_V1_NOTIF_INTERNAL_EVENT_START: पूर्णांकernal FW use
 * @TE_V1_NOTIF_INTERNAL_EVENT_END: पूर्णांकernal FW use.
 * @TE_V1_NOTIF_HOST_FRAG_START: request/receive notअगरication on frag start
 * @TE_V1_NOTIF_HOST_FRAG_END:request/receive notअगरication on frag end
 * @TE_V1_NOTIF_INTERNAL_FRAG_START: पूर्णांकernal FW use.
 * @TE_V1_NOTIF_INTERNAL_FRAG_END: पूर्णांकernal FW use.
 *
 * Supported Time event notअगरications configuration.
 * A notअगरication (both event and fragment) includes a status indicating weather
 * the FW was able to schedule the event or not. For fragment start/end
 * notअगरication the status is always success. There is no start/end fragment
 * notअगरication क्रम monolithic events.
 */
क्रमागत अणु
	TE_V1_NOTIF_NONE = 0,
	TE_V1_NOTIF_HOST_EVENT_START = BIT(0),
	TE_V1_NOTIF_HOST_EVENT_END = BIT(1),
	TE_V1_NOTIF_INTERNAL_EVENT_START = BIT(2),
	TE_V1_NOTIF_INTERNAL_EVENT_END = BIT(3),
	TE_V1_NOTIF_HOST_FRAG_START = BIT(4),
	TE_V1_NOTIF_HOST_FRAG_END = BIT(5),
	TE_V1_NOTIF_INTERNAL_FRAG_START = BIT(6),
	TE_V1_NOTIF_INTERNAL_FRAG_END = BIT(7),
पूर्ण; /* MAC_EVENT_ACTION_API_E_VER_2 */

/* Time event - defines क्रम command API */

/*
 * @TE_V2_FRAG_NONE: fragmentation of the समय event is NOT allowed.
 * @TE_V2_FRAG_SINGLE: fragmentation of the समय event is allowed, but only
 *  the first fragment is scheduled.
 * @TE_V2_FRAG_DUAL: fragmentation of the समय event is allowed, but only
 *  the first 2 fragments are scheduled.
 * @TE_V2_FRAG_ENDLESS: fragmentation of the समय event is allowed, and any
 *  number of fragments are valid.
 *
 * Other than the स्थिरant defined above, specअगरying a fragmentation value 'x'
 * means that the event can be fragmented but only the first 'x' will be
 * scheduled.
 */
क्रमागत अणु
	TE_V2_FRAG_NONE = 0,
	TE_V2_FRAG_SINGLE = 1,
	TE_V2_FRAG_DUAL = 2,
	TE_V2_FRAG_MAX = 0xfe,
	TE_V2_FRAG_ENDLESS = 0xff
पूर्ण;

/* Repeat the समय event endlessly (until हटाओd) */
#घोषणा TE_V2_REPEAT_ENDLESS	0xff
/* If a Time Event has bounded repetitions, this is the maximal value */
#घोषणा TE_V2_REPEAT_MAX	0xfe

#घोषणा TE_V2_PLACEMENT_POS	12
#घोषणा TE_V2_ABSENCE_POS	15

/**
 * क्रमागत iwl_समय_event_policy - Time event policy values
 * A notअगरication (both event and fragment) includes a status indicating weather
 * the FW was able to schedule the event or not. For fragment start/end
 * notअगरication the status is always success. There is no start/end fragment
 * notअगरication क्रम monolithic events.
 *
 * @TE_V2_DEFAULT_POLICY: independent, social, present, unoticable
 * @TE_V2_NOTIF_HOST_EVENT_START: request/receive notअगरication on event start
 * @TE_V2_NOTIF_HOST_EVENT_END:request/receive notअगरication on event end
 * @TE_V2_NOTIF_INTERNAL_EVENT_START: पूर्णांकernal FW use
 * @TE_V2_NOTIF_INTERNAL_EVENT_END: पूर्णांकernal FW use.
 * @TE_V2_NOTIF_HOST_FRAG_START: request/receive notअगरication on frag start
 * @TE_V2_NOTIF_HOST_FRAG_END:request/receive notअगरication on frag end
 * @TE_V2_NOTIF_INTERNAL_FRAG_START: पूर्णांकernal FW use.
 * @TE_V2_NOTIF_INTERNAL_FRAG_END: पूर्णांकernal FW use.
 * @TE_V2_START_IMMEDIATELY: start समय event immediately
 * @TE_V2_DEP_OTHER: depends on another समय event
 * @TE_V2_DEP_TSF: depends on a specअगरic समय
 * @TE_V2_EVENT_SOCIOPATHIC: can't co-exist with other events of tha same MAC
 * @TE_V2_ABSENCE: are we present or असलent during the Time Event.
 */
क्रमागत iwl_समय_event_policy अणु
	TE_V2_DEFAULT_POLICY = 0x0,

	/* notअगरications (event start/stop, fragment start/stop) */
	TE_V2_NOTIF_HOST_EVENT_START = BIT(0),
	TE_V2_NOTIF_HOST_EVENT_END = BIT(1),
	TE_V2_NOTIF_INTERNAL_EVENT_START = BIT(2),
	TE_V2_NOTIF_INTERNAL_EVENT_END = BIT(3),

	TE_V2_NOTIF_HOST_FRAG_START = BIT(4),
	TE_V2_NOTIF_HOST_FRAG_END = BIT(5),
	TE_V2_NOTIF_INTERNAL_FRAG_START = BIT(6),
	TE_V2_NOTIF_INTERNAL_FRAG_END = BIT(7),
	TE_V2_START_IMMEDIATELY = BIT(11),

	/* placement अक्षरacteristics */
	TE_V2_DEP_OTHER = BIT(TE_V2_PLACEMENT_POS),
	TE_V2_DEP_TSF = BIT(TE_V2_PLACEMENT_POS + 1),
	TE_V2_EVENT_SOCIOPATHIC = BIT(TE_V2_PLACEMENT_POS + 2),

	/* are we present or असलent during the Time Event. */
	TE_V2_ABSENCE = BIT(TE_V2_ABSENCE_POS),
पूर्ण;

/**
 * काष्ठा iwl_समय_event_cmd - configuring Time Events
 * with काष्ठा MAC_TIME_EVENT_DATA_API_S_VER_2 (see also
 * with version 1. determined by IWL_UCODE_TLV_FLAGS)
 * ( TIME_EVENT_CMD = 0x29 )
 * @id_and_color: ID and color of the relevant MAC,
 *	&क्रमागत iwl_ctxt_id_and_color
 * @action: action to perक्रमm, one of &क्रमागत iwl_ctxt_action
 * @id: this field has two meanings, depending on the action:
 *	If the action is ADD, then it means the type of event to add.
 *	For all other actions it is the unique event ID asचिन्हित when the
 *	event was added by the FW.
 * @apply_समय: When to start the Time Event (in GP2)
 * @max_delay: maximum delay to event's start (apply समय), in TU
 * @depends_on: the unique ID of the event we depend on (अगर any)
 * @पूर्णांकerval: पूर्णांकerval between repetitions, in TU
 * @duration: duration of event in TU
 * @repeat: how many repetitions to करो, can be TE_REPEAT_ENDLESS
 * @max_frags: maximal number of fragments the Time Event can be भागided to
 * @policy: defines whether uCode shall notअगरy the host or other uCode modules
 *	on event and/or fragment start and/or end
 *	using one of TE_INDEPENDENT, TE_DEP_OTHER, TE_DEP_TSF
 *	TE_EVENT_SOCIOPATHIC
 *	using TE_ABSENCE and using TE_NOTIF_*,
 *	&क्रमागत iwl_समय_event_policy
 */
काष्ठा iwl_समय_event_cmd अणु
	/* COMMON_INDEX_HDR_API_S_VER_1 */
	__le32 id_and_color;
	__le32 action;
	__le32 id;
	/* MAC_TIME_EVENT_DATA_API_S_VER_2 */
	__le32 apply_समय;
	__le32 max_delay;
	__le32 depends_on;
	__le32 पूर्णांकerval;
	__le32 duration;
	u8 repeat;
	u8 max_frags;
	__le16 policy;
पूर्ण __packed; /* MAC_TIME_EVENT_CMD_API_S_VER_2 */

/**
 * काष्ठा iwl_समय_event_resp - response काष्ठाure to iwl_समय_event_cmd
 * @status: bit 0 indicates success, all others specअगरy errors
 * @id: the Time Event type
 * @unique_id: the unique ID asचिन्हित (in ADD) or given (others) to the TE
 * @id_and_color: ID and color of the relevant MAC,
 *	&क्रमागत iwl_ctxt_id_and_color
 */
काष्ठा iwl_समय_event_resp अणु
	__le32 status;
	__le32 id;
	__le32 unique_id;
	__le32 id_and_color;
पूर्ण __packed; /* MAC_TIME_EVENT_RSP_API_S_VER_1 */

/**
 * काष्ठा iwl_समय_event_notअगर - notअगरications of समय event start/stop
 * ( TIME_EVENT_NOTIFICATION = 0x2a )
 * @बारtamp: action बारtamp in GP2
 * @session_id: session's unique id
 * @unique_id: unique id of the Time Event itself
 * @id_and_color: ID and color of the relevant MAC
 * @action: &क्रमागत iwl_समय_event_policy
 * @status: true अगर scheduled, false otherwise (not executed)
 */
काष्ठा iwl_समय_event_notअगर अणु
	__le32 बारtamp;
	__le32 session_id;
	__le32 unique_id;
	__le32 id_and_color;
	__le32 action;
	__le32 status;
पूर्ण __packed; /* MAC_TIME_EVENT_NTFY_API_S_VER_1 */

/*
 * काष्ठा iwl_hs20_roc_req_tail - tail of iwl_hs20_roc_req
 *
 * @node_addr: Our MAC Address
 * @reserved: reserved क्रम alignment
 * @apply_समय: GP2 value to start (should always be the current GP2 value)
 * @apply_समय_max_delay: Maximum apply समय delay value in TU. Defines max
 *	समय by which start of the event is allowed to be postponed.
 * @duration: event duration in TU To calculate event duration:
 *	समयEventDuration = min(duration, reमुख्यingQuota)
 */
काष्ठा iwl_hs20_roc_req_tail अणु
	u8 node_addr[ETH_ALEN];
	__le16 reserved;
	__le32 apply_समय;
	__le32 apply_समय_max_delay;
	__le32 duration;
पूर्ण __packed;

/*
 * Aux ROC command
 *
 * Command requests the firmware to create a समय event क्रम a certain duration
 * and reमुख्य on the given channel. This is करोne by using the Aux framework in
 * the FW.
 * The command was first used क्रम Hot Spot issues - but can be used regardless
 * to Hot Spot.
 *
 * ( HOT_SPOT_CMD 0x53 )
 *
 * @id_and_color: ID and color of the MAC
 * @action: action to perक्रमm, one of FW_CTXT_ACTION_*
 * @event_unique_id: If the action FW_CTXT_ACTION_REMOVE then the
 *	event_unique_id should be the id of the समय event asचिन्हित by ucode.
 *	Otherwise ignore the event_unique_id.
 * @sta_id_and_color: station id and color, resumed during "Remain On Channel"
 *	activity.
 * @channel_info: channel info
 */
काष्ठा iwl_hs20_roc_req अणु
	/* COMMON_INDEX_HDR_API_S_VER_1 hdr */
	__le32 id_and_color;
	__le32 action;
	__le32 event_unique_id;
	__le32 sta_id_and_color;
	काष्ठा iwl_fw_channel_info channel_info;
	काष्ठा iwl_hs20_roc_req_tail tail;
पूर्ण __packed; /* HOT_SPOT_CMD_API_S_VER_1 */

/*
 * values क्रम AUX ROC result values
 */
क्रमागत iwl_mvm_hot_spot अणु
	HOT_SPOT_RSP_STATUS_OK,
	HOT_SPOT_RSP_STATUS_TOO_MANY_EVENTS,
	HOT_SPOT_MAX_NUM_OF_SESSIONS,
पूर्ण;

/*
 * Aux ROC command response
 *
 * In response to iwl_hs20_roc_req the FW sends this command to notअगरy the
 * driver the uid of the समयvent.
 *
 * ( HOT_SPOT_CMD 0x53 )
 *
 * @event_unique_id: Unique ID of समय event asचिन्हित by ucode
 * @status: Return status 0 is success, all the rest used क्रम specअगरic errors
 */
काष्ठा iwl_hs20_roc_res अणु
	__le32 event_unique_id;
	__le32 status;
पूर्ण __packed; /* HOT_SPOT_RSP_API_S_VER_1 */

/**
 * क्रमागत iwl_mvm_session_prot_conf_id - session protection's configurations
 * @SESSION_PROTECT_CONF_ASSOC: Start a session protection क्रम association.
 *	The firmware will allocate two events.
 *	Valid क्रम BSS_STA and P2P_STA.
 *	* A rather लघु event that can't be fragmented and with a very
 *	high priority. If every goes well (99% of the हालs) the
 *	association should complete within this first event. During
 *	that event, no other activity will happen in the firmware,
 *	which is why it can't be too दीर्घ.
 *	The length of this event is hard-coded in the firmware: 300TUs.
 *	* Another event which can be much दीर्घer (it's duration is
 *	configurable by the driver) which has a slightly lower
 *	priority and that can be fragmented allowing other activities
 *	to run जबतक this event is running.
 *	The firmware will स्वतःmatically हटाओ both events once the driver sets
 *	the BSS MAC as associated. Neither of the events will be हटाओd
 *	क्रम the P2P_STA MAC.
 *	Only the duration is configurable क्रम this protection.
 * @SESSION_PROTECT_CONF_GO_CLIENT_ASSOC: not used
 * @SESSION_PROTECT_CONF_P2P_DEVICE_DISCOV: Schedule the P2P Device to be in
 *	listen mode. Will be fragmented. Valid only on the P2P Device MAC.
 *	Valid only on the P2P Device MAC. The firmware will take पूर्णांकo account
 *	the duration, the पूर्णांकerval and the repetition count.
 * @SESSION_PROTECT_CONF_P2P_GO_NEGOTIATION: Schedule the P2P Device to be be
 *	able to run the GO Negotiation. Will not be fragmented and not
 *	repetitive. Valid only on the P2P Device MAC. Only the duration will
 *	be taken पूर्णांकo account.
 * @SESSION_PROTECT_CONF_MAX_ID: not used
 */
क्रमागत iwl_mvm_session_prot_conf_id अणु
	SESSION_PROTECT_CONF_ASSOC,
	SESSION_PROTECT_CONF_GO_CLIENT_ASSOC,
	SESSION_PROTECT_CONF_P2P_DEVICE_DISCOV,
	SESSION_PROTECT_CONF_P2P_GO_NEGOTIATION,
	SESSION_PROTECT_CONF_MAX_ID,
पूर्ण; /* SESSION_PROTECTION_CONF_ID_E_VER_1 */

/**
 * काष्ठा iwl_mvm_session_prot_cmd - configure a session protection
 * @id_and_color: the id and color of the mac क्रम which this session protection
 *	is sent
 * @action: can be either FW_CTXT_ACTION_ADD or FW_CTXT_ACTION_REMOVE
 * @conf_id: see &क्रमागत iwl_mvm_session_prot_conf_id
 * @duration_tu: the duration of the whole protection in TUs.
 * @repetition_count: not used
 * @पूर्णांकerval: not used
 *
 * Note: the session protection will always be scheduled to start as
 * early as possible, but the maximum delay is configuration dependent.
 * The firmware supports only one concurrent session protection per vअगर.
 * Adding a new session protection will हटाओ any currently running session.
 */
काष्ठा iwl_mvm_session_prot_cmd अणु
	/* COMMON_INDEX_HDR_API_S_VER_1 hdr */
	__le32 id_and_color;
	__le32 action;
	__le32 conf_id;
	__le32 duration_tu;
	__le32 repetition_count;
	__le32 पूर्णांकerval;
पूर्ण __packed; /* SESSION_PROTECTION_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_mvm_session_prot_notअगर - session protection started / ended
 * @mac_id: the mac id क्रम which the session protection started / ended
 * @status: 1 means success, 0 means failure
 * @start: 1 means the session protection started, 0 means it ended
 * @conf_id: see &क्रमागत iwl_mvm_session_prot_conf_id
 *
 * Note that any session protection will always get two notअगरications: start
 * and end even the firmware could not schedule it.
 */
काष्ठा iwl_mvm_session_prot_notअगर अणु
	__le32 mac_id;
	__le32 status;
	__le32 start;
	__le32 conf_id;
पूर्ण __packed; /* SESSION_PROTECTION_NOTIFICATION_API_S_VER_2 */

#पूर्ण_अगर /* __iwl_fw_api_समय_event_h__ */
