<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2015-2017 Google, Inc
 *
 * USB Power Delivery protocol stack.
 */

#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/property.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/pd.h>
#समावेश <linux/usb/pd_aकरो.h>
#समावेश <linux/usb/pd_bकरो.h>
#समावेश <linux/usb/pd_ext_sdb.h>
#समावेश <linux/usb/pd_vकरो.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/usb/tcpm.h>
#समावेश <linux/usb/typec_alपंचांगode.h>

#समावेश <uapi/linux/sched/types.h>

#घोषणा FOREACH_STATE(S)			\
	S(INVALID_STATE),			\
	S(TOGGLING),			\
	S(SRC_UNATTACHED),			\
	S(SRC_ATTACH_WAIT),			\
	S(SRC_ATTACHED),			\
	S(SRC_STARTUP),				\
	S(SRC_SEND_CAPABILITIES),		\
	S(SRC_SEND_CAPABILITIES_TIMEOUT),	\
	S(SRC_NEGOTIATE_CAPABILITIES),		\
	S(SRC_TRANSITION_SUPPLY),		\
	S(SRC_READY),				\
	S(SRC_WAIT_NEW_CAPABILITIES),		\
						\
	S(SNK_UNATTACHED),			\
	S(SNK_ATTACH_WAIT),			\
	S(SNK_DEBOUNCED),			\
	S(SNK_ATTACHED),			\
	S(SNK_STARTUP),				\
	S(SNK_DISCOVERY),			\
	S(SNK_DISCOVERY_DEBOUNCE),		\
	S(SNK_DISCOVERY_DEBOUNCE_DONE),		\
	S(SNK_WAIT_CAPABILITIES),		\
	S(SNK_NEGOTIATE_CAPABILITIES),		\
	S(SNK_NEGOTIATE_PPS_CAPABILITIES),	\
	S(SNK_TRANSITION_SINK),			\
	S(SNK_TRANSITION_SINK_VBUS),		\
	S(SNK_READY),				\
						\
	S(ACC_UNATTACHED),			\
	S(DEBUG_ACC_ATTACHED),			\
	S(AUDIO_ACC_ATTACHED),			\
	S(AUDIO_ACC_DEBOUNCE),			\
						\
	S(HARD_RESET_SEND),			\
	S(HARD_RESET_START),			\
	S(SRC_HARD_RESET_VBUS_OFF),		\
	S(SRC_HARD_RESET_VBUS_ON),		\
	S(SNK_HARD_RESET_SINK_OFF),		\
	S(SNK_HARD_RESET_WAIT_VBUS),		\
	S(SNK_HARD_RESET_SINK_ON),		\
						\
	S(SOFT_RESET),				\
	S(SRC_SOFT_RESET_WAIT_SNK_TX),		\
	S(SNK_SOFT_RESET),			\
	S(SOFT_RESET_SEND),			\
						\
	S(DR_SWAP_ACCEPT),			\
	S(DR_SWAP_SEND),			\
	S(DR_SWAP_SEND_TIMEOUT),		\
	S(DR_SWAP_CANCEL),			\
	S(DR_SWAP_CHANGE_DR),			\
						\
	S(PR_SWAP_ACCEPT),			\
	S(PR_SWAP_SEND),			\
	S(PR_SWAP_SEND_TIMEOUT),		\
	S(PR_SWAP_CANCEL),			\
	S(PR_SWAP_START),			\
	S(PR_SWAP_SRC_SNK_TRANSITION_OFF),	\
	S(PR_SWAP_SRC_SNK_SOURCE_OFF),		\
	S(PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED), \
	S(PR_SWAP_SRC_SNK_SINK_ON),		\
	S(PR_SWAP_SNK_SRC_SINK_OFF),		\
	S(PR_SWAP_SNK_SRC_SOURCE_ON),		\
	S(PR_SWAP_SNK_SRC_SOURCE_ON_VBUS_RAMPED_UP),    \
						\
	S(VCONN_SWAP_ACCEPT),			\
	S(VCONN_SWAP_SEND),			\
	S(VCONN_SWAP_SEND_TIMEOUT),		\
	S(VCONN_SWAP_CANCEL),			\
	S(VCONN_SWAP_START),			\
	S(VCONN_SWAP_WAIT_FOR_VCONN),		\
	S(VCONN_SWAP_TURN_ON_VCONN),		\
	S(VCONN_SWAP_TURN_OFF_VCONN),		\
						\
	S(FR_SWAP_SEND),			\
	S(FR_SWAP_SEND_TIMEOUT),		\
	S(FR_SWAP_SNK_SRC_TRANSITION_TO_OFF),			\
	S(FR_SWAP_SNK_SRC_NEW_SINK_READY),		\
	S(FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED),	\
	S(FR_SWAP_CANCEL),			\
						\
	S(SNK_TRY),				\
	S(SNK_TRY_WAIT),			\
	S(SNK_TRY_WAIT_DEBOUNCE),               \
	S(SNK_TRY_WAIT_DEBOUNCE_CHECK_VBUS),    \
	S(SRC_TRYWAIT),				\
	S(SRC_TRYWAIT_DEBOUNCE),		\
	S(SRC_TRYWAIT_UNATTACHED),		\
						\
	S(SRC_TRY),				\
	S(SRC_TRY_WAIT),                        \
	S(SRC_TRY_DEBOUNCE),			\
	S(SNK_TRYWAIT),				\
	S(SNK_TRYWAIT_DEBOUNCE),		\
	S(SNK_TRYWAIT_VBUS),			\
	S(BIST_RX),				\
						\
	S(GET_STATUS_SEND),			\
	S(GET_STATUS_SEND_TIMEOUT),		\
	S(GET_PPS_STATUS_SEND),			\
	S(GET_PPS_STATUS_SEND_TIMEOUT),		\
						\
	S(GET_SINK_CAP),			\
	S(GET_SINK_CAP_TIMEOUT),		\
						\
	S(ERROR_RECOVERY),			\
	S(PORT_RESET),				\
	S(PORT_RESET_WAIT_OFF),			\
						\
	S(AMS_START),				\
	S(CHUNK_NOT_SUPP)

#घोषणा FOREACH_AMS(S)				\
	S(NONE_AMS),				\
	S(POWER_NEGOTIATION),			\
	S(GOTOMIN),				\
	S(SOFT_RESET_AMS),			\
	S(HARD_RESET),				\
	S(CABLE_RESET),				\
	S(GET_SOURCE_CAPABILITIES),		\
	S(GET_SINK_CAPABILITIES),		\
	S(POWER_ROLE_SWAP),			\
	S(FAST_ROLE_SWAP),			\
	S(DATA_ROLE_SWAP),			\
	S(VCONN_SWAP),				\
	S(SOURCE_ALERT),			\
	S(GETTING_SOURCE_EXTENDED_CAPABILITIES),\
	S(GETTING_SOURCE_SINK_STATUS),		\
	S(GETTING_BATTERY_CAPABILITIES),	\
	S(GETTING_BATTERY_STATUS),		\
	S(GETTING_MANUFACTURER_INFORMATION),	\
	S(SECURITY),				\
	S(FIRMWARE_UPDATE),			\
	S(DISCOVER_IDENTITY),			\
	S(SOURCE_STARTUP_CABLE_PLUG_DISCOVER_IDENTITY),	\
	S(DISCOVER_SVIDS),			\
	S(DISCOVER_MODES),			\
	S(DFP_TO_UFP_ENTER_MODE),		\
	S(DFP_TO_UFP_EXIT_MODE),		\
	S(DFP_TO_CABLE_PLUG_ENTER_MODE),	\
	S(DFP_TO_CABLE_PLUG_EXIT_MODE),		\
	S(ATTENTION),				\
	S(BIST),				\
	S(UNSTRUCTURED_VDMS),			\
	S(STRUCTURED_VDMS),			\
	S(COUNTRY_INFO),			\
	S(COUNTRY_CODES)

#घोषणा GENERATE_ENUM(e)	e
#घोषणा GENERATE_STRING(s)	#s

क्रमागत tcpm_state अणु
	FOREACH_STATE(GENERATE_ENUM)
पूर्ण;

अटल स्थिर अक्षर * स्थिर tcpm_states[] = अणु
	FOREACH_STATE(GENERATE_STRING)
पूर्ण;

क्रमागत tcpm_ams अणु
	FOREACH_AMS(GENERATE_ENUM)
पूर्ण;

अटल स्थिर अक्षर * स्थिर tcpm_ams_str[] = अणु
	FOREACH_AMS(GENERATE_STRING)
पूर्ण;

क्रमागत vdm_states अणु
	VDM_STATE_ERR_BUSY = -3,
	VDM_STATE_ERR_SEND = -2,
	VDM_STATE_ERR_TMOUT = -1,
	VDM_STATE_DONE = 0,
	/* Anything >0 represents an active state */
	VDM_STATE_READY = 1,
	VDM_STATE_BUSY = 2,
	VDM_STATE_WAIT_RSP_BUSY = 3,
	VDM_STATE_SEND_MESSAGE = 4,
पूर्ण;

क्रमागत pd_msg_request अणु
	PD_MSG_NONE = 0,
	PD_MSG_CTRL_REJECT,
	PD_MSG_CTRL_WAIT,
	PD_MSG_CTRL_NOT_SUPP,
	PD_MSG_DATA_SINK_CAP,
	PD_MSG_DATA_SOURCE_CAP,
पूर्ण;

क्रमागत adev_actions अणु
	ADEV_NONE = 0,
	ADEV_NOTIFY_USB_AND_QUEUE_VDM,
	ADEV_QUEUE_VDM,
	ADEV_QUEUE_VDM_SEND_EXIT_MODE_ON_FAIL,
	ADEV_ATTENTION,
पूर्ण;

/*
 * Initial current capability of the new source when vSafe5V is applied during PD3.0 Fast Role Swap.
 * Based on "Table 6-14 Fixed Supply PDO - Sink" of "USB Power Delivery Specअगरication Revision 3.0,
 * Version 1.2"
 */
क्रमागत frs_typec_current अणु
	FRS_NOT_SUPPORTED,
	FRS_DEFAULT_POWER,
	FRS_5V_1P5A,
	FRS_5V_3A,
पूर्ण;

/* Events from low level driver */

#घोषणा TCPM_CC_EVENT		BIT(0)
#घोषणा TCPM_VBUS_EVENT		BIT(1)
#घोषणा TCPM_RESET_EVENT	BIT(2)
#घोषणा TCPM_FRS_EVENT		BIT(3)
#घोषणा TCPM_SOURCING_VBUS	BIT(4)

#घोषणा LOG_BUFFER_ENTRIES	1024
#घोषणा LOG_BUFFER_ENTRY_SIZE	128

/* Alternate mode support */

#घोषणा SVID_DISCOVERY_MAX	16
#घोषणा ALTMODE_DISCOVERY_MAX	(SVID_DISCOVERY_MAX * MODE_DISCOVERY_MAX)

#घोषणा GET_SINK_CAP_RETRY_MS	100
#घोषणा SEND_DISCOVER_RETRY_MS	100

काष्ठा pd_mode_data अणु
	पूर्णांक svid_index;		/* current SVID index		*/
	पूर्णांक nsvids;
	u16 svids[SVID_DISCOVERY_MAX];
	पूर्णांक alपंचांगodes;		/* number of alternate modes	*/
	काष्ठा typec_alपंचांगode_desc alपंचांगode_desc[ALTMODE_DISCOVERY_MAX];
पूर्ण;

/*
 * @min_volt: Actual min voltage at the local port
 * @req_min_volt: Requested min voltage to the port partner
 * @max_volt: Actual max voltage at the local port
 * @req_max_volt: Requested max voltage to the port partner
 * @max_curr: Actual max current at the local port
 * @req_max_curr: Requested max current of the port partner
 * @req_out_volt: Requested output voltage to the port partner
 * @req_op_curr: Requested operating current to the port partner
 * @supported: Parter has atleast one APDO hence supports PPS
 * @active: PPS mode is active
 */
काष्ठा pd_pps_data अणु
	u32 min_volt;
	u32 req_min_volt;
	u32 max_volt;
	u32 req_max_volt;
	u32 max_curr;
	u32 req_max_curr;
	u32 req_out_volt;
	u32 req_op_curr;
	bool supported;
	bool active;
पूर्ण;

काष्ठा tcpm_port अणु
	काष्ठा device *dev;

	काष्ठा mutex lock;		/* tcpm state machine lock */
	काष्ठा kthपढ़ो_worker *wq;

	काष्ठा typec_capability typec_caps;
	काष्ठा typec_port *typec_port;

	काष्ठा tcpc_dev	*tcpc;
	काष्ठा usb_role_चयन *role_sw;

	क्रमागत typec_role vconn_role;
	क्रमागत typec_role pwr_role;
	क्रमागत typec_data_role data_role;
	क्रमागत typec_pwr_opmode pwr_opmode;

	काष्ठा usb_pd_identity partner_ident;
	काष्ठा typec_partner_desc partner_desc;
	काष्ठा typec_partner *partner;

	क्रमागत typec_cc_status cc_req;

	क्रमागत typec_cc_status cc1;
	क्रमागत typec_cc_status cc2;
	क्रमागत typec_cc_polarity polarity;

	bool attached;
	bool connected;
	क्रमागत typec_port_type port_type;

	/*
	 * Set to true when vbus is greater than VSAFE5V min.
	 * Set to false when vbus falls below vSinkDisconnect max threshold.
	 */
	bool vbus_present;

	/*
	 * Set to true when vbus is less than VSAFE0V max.
	 * Set to false when vbus is greater than VSAFE0V max.
	 */
	bool vbus_vsafe0v;

	bool vbus_never_low;
	bool vbus_source;
	bool vbus_अक्षरge;

	bool send_discover;
	bool op_vsafe5v;

	पूर्णांक try_role;
	पूर्णांक try_snk_count;
	पूर्णांक try_src_count;

	क्रमागत pd_msg_request queued_message;

	क्रमागत tcpm_state enter_state;
	क्रमागत tcpm_state prev_state;
	क्रमागत tcpm_state state;
	क्रमागत tcpm_state delayed_state;
	kसमय_प्रकार delayed_runसमय;
	अचिन्हित दीर्घ delay_ms;

	spinlock_t pd_event_lock;
	u32 pd_events;

	काष्ठा kthपढ़ो_work event_work;
	काष्ठा hrसमयr state_machine_समयr;
	काष्ठा kthपढ़ो_work state_machine;
	काष्ठा hrसमयr vdm_state_machine_समयr;
	काष्ठा kthपढ़ो_work vdm_state_machine;
	काष्ठा hrसमयr enable_frs_समयr;
	काष्ठा kthपढ़ो_work enable_frs;
	काष्ठा hrसमयr send_discover_समयr;
	काष्ठा kthपढ़ो_work send_discover_work;
	bool state_machine_running;
	bool vdm_sm_running;

	काष्ठा completion tx_complete;
	क्रमागत tcpm_transmit_status tx_status;

	काष्ठा mutex swap_lock;		/* swap command lock */
	bool swap_pending;
	bool non_pd_role_swap;
	काष्ठा completion swap_complete;
	पूर्णांक swap_status;

	अचिन्हित पूर्णांक negotiated_rev;
	अचिन्हित पूर्णांक message_id;
	अचिन्हित पूर्णांक caps_count;
	अचिन्हित पूर्णांक hard_reset_count;
	bool pd_capable;
	bool explicit_contract;
	अचिन्हित पूर्णांक rx_msgid;

	/* Partner capabilities/requests */
	u32 sink_request;
	u32 source_caps[PDO_MAX_OBJECTS];
	अचिन्हित पूर्णांक nr_source_caps;
	u32 sink_caps[PDO_MAX_OBJECTS];
	अचिन्हित पूर्णांक nr_sink_caps;

	/* Local capabilities */
	u32 src_pकरो[PDO_MAX_OBJECTS];
	अचिन्हित पूर्णांक nr_src_pकरो;
	u32 snk_pकरो[PDO_MAX_OBJECTS];
	अचिन्हित पूर्णांक nr_snk_pकरो;
	u32 snk_vकरो_v1[VDO_MAX_OBJECTS];
	अचिन्हित पूर्णांक nr_snk_vकरो_v1;
	u32 snk_vकरो[VDO_MAX_OBJECTS];
	अचिन्हित पूर्णांक nr_snk_vकरो;

	अचिन्हित पूर्णांक operating_snk_mw;
	bool update_sink_caps;

	/* Requested current / voltage to the port partner */
	u32 req_current_limit;
	u32 req_supply_voltage;
	/* Actual current / voltage limit of the local port */
	u32 current_limit;
	u32 supply_voltage;

	/* Used to export TA voltage and current */
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;
	क्रमागत घातer_supply_usb_type usb_type;

	u32 bist_request;

	/* PD state क्रम Venकरोr Defined Messages */
	क्रमागत vdm_states vdm_state;
	u32 vdm_retries;
	/* next Venकरोr Defined Message to send */
	u32 vकरो_data[VDO_MAX_SIZE];
	u8 vकरो_count;
	/* VDO to retry अगर UFP responder replied busy */
	u32 vकरो_retry;

	/* PPS */
	काष्ठा pd_pps_data pps_data;
	काष्ठा completion pps_complete;
	bool pps_pending;
	पूर्णांक pps_status;

	/* Alternate mode data */
	काष्ठा pd_mode_data mode_data;
	काष्ठा typec_alपंचांगode *partner_alपंचांगode[ALTMODE_DISCOVERY_MAX];
	काष्ठा typec_alपंचांगode *port_alपंचांगode[ALTMODE_DISCOVERY_MAX];

	/* Deadline in jअगरfies to निकास src_try_रुको state */
	अचिन्हित दीर्घ max_रुको;

	/* port beदीर्घs to a self घातered device */
	bool self_घातered;

	/* Sink FRS */
	क्रमागत frs_typec_current new_source_frs_current;

	/* Sink caps have been queried */
	bool sink_cap_करोne;

	/* Collision Aव्योमance and Atomic Message Sequence */
	क्रमागत tcpm_state upcoming_state;
	क्रमागत tcpm_ams ams;
	क्रमागत tcpm_ams next_ams;
	bool in_ams;

	/* Auto vbus disअक्षरge status */
	bool स्वतः_vbus_disअक्षरge_enabled;

	/*
	 * When set, port requests PD_P_SNK_STDBY_MW upon entering SNK_DISCOVERY and
	 * the actual currrent limit after RX of PD_CTRL_PSRDY क्रम PD link,
	 * SNK_READY क्रम non-pd link.
	 */
	bool slow_अक्षरger_loop;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dentry;
	काष्ठा mutex logbuffer_lock;	/* log buffer access lock */
	पूर्णांक logbuffer_head;
	पूर्णांक logbuffer_tail;
	u8 *logbuffer[LOG_BUFFER_ENTRIES];
#पूर्ण_अगर
पूर्ण;

काष्ठा pd_rx_event अणु
	काष्ठा kthपढ़ो_work work;
	काष्ठा tcpm_port *port;
	काष्ठा pd_message msg;
पूर्ण;

अटल स्थिर अक्षर * स्थिर pd_rev[] = अणु
	[PD_REV10]		= "rev1",
	[PD_REV20]		= "rev2",
	[PD_REV30]		= "rev3",
पूर्ण;

#घोषणा tcpm_cc_is_sink(cc) \
	((cc) == TYPEC_CC_RP_DEF || (cc) == TYPEC_CC_RP_1_5 || \
	 (cc) == TYPEC_CC_RP_3_0)

#घोषणा tcpm_port_is_sink(port) \
	((tcpm_cc_is_sink((port)->cc1) && !tcpm_cc_is_sink((port)->cc2)) || \
	 (tcpm_cc_is_sink((port)->cc2) && !tcpm_cc_is_sink((port)->cc1)))

#घोषणा tcpm_cc_is_source(cc) ((cc) == TYPEC_CC_RD)
#घोषणा tcpm_cc_is_audio(cc) ((cc) == TYPEC_CC_RA)
#घोषणा tcpm_cc_is_खोलो(cc) ((cc) == TYPEC_CC_OPEN)

#घोषणा tcpm_port_is_source(port) \
	((tcpm_cc_is_source((port)->cc1) && \
	 !tcpm_cc_is_source((port)->cc2)) || \
	 (tcpm_cc_is_source((port)->cc2) && \
	  !tcpm_cc_is_source((port)->cc1)))

#घोषणा tcpm_port_is_debug(port) \
	(tcpm_cc_is_source((port)->cc1) && tcpm_cc_is_source((port)->cc2))

#घोषणा tcpm_port_is_audio(port) \
	(tcpm_cc_is_audio((port)->cc1) && tcpm_cc_is_audio((port)->cc2))

#घोषणा tcpm_port_is_audio_detached(port) \
	((tcpm_cc_is_audio((port)->cc1) && tcpm_cc_is_खोलो((port)->cc2)) || \
	 (tcpm_cc_is_audio((port)->cc2) && tcpm_cc_is_खोलो((port)->cc1)))

#घोषणा tcpm_try_snk(port) \
	((port)->try_snk_count == 0 && (port)->try_role == TYPEC_SINK && \
	(port)->port_type == TYPEC_PORT_DRP)

#घोषणा tcpm_try_src(port) \
	((port)->try_src_count == 0 && (port)->try_role == TYPEC_SOURCE && \
	(port)->port_type == TYPEC_PORT_DRP)

#घोषणा tcpm_data_role_क्रम_source(port) \
	((port)->typec_caps.data == TYPEC_PORT_UFP ? \
	TYPEC_DEVICE : TYPEC_HOST)

#घोषणा tcpm_data_role_क्रम_sink(port) \
	((port)->typec_caps.data == TYPEC_PORT_DFP ? \
	TYPEC_HOST : TYPEC_DEVICE)

#घोषणा tcpm_sink_tx_ok(port) \
	(tcpm_port_is_sink(port) && \
	((port)->cc1 == TYPEC_CC_RP_3_0 || (port)->cc2 == TYPEC_CC_RP_3_0))

#घोषणा tcpm_रुको_क्रम_disअक्षरge(port) \
	(((port)->स्वतः_vbus_disअक्षरge_enabled && !(port)->vbus_vsafe0v) ? PD_T_SAFE_0V : 0)

अटल क्रमागत tcpm_state tcpm_शेष_state(काष्ठा tcpm_port *port)
अणु
	अगर (port->port_type == TYPEC_PORT_DRP) अणु
		अगर (port->try_role == TYPEC_SINK)
			वापस SNK_UNATTACHED;
		अन्यथा अगर (port->try_role == TYPEC_SOURCE)
			वापस SRC_UNATTACHED;
		/* Fall through to वापस SRC_UNATTACHED */
	पूर्ण अन्यथा अगर (port->port_type == TYPEC_PORT_SNK) अणु
		वापस SNK_UNATTACHED;
	पूर्ण
	वापस SRC_UNATTACHED;
पूर्ण

अटल bool tcpm_port_is_disconnected(काष्ठा tcpm_port *port)
अणु
	वापस (!port->attached && port->cc1 == TYPEC_CC_OPEN &&
		port->cc2 == TYPEC_CC_OPEN) ||
	       (port->attached && ((port->polarity == TYPEC_POLARITY_CC1 &&
				    port->cc1 == TYPEC_CC_OPEN) ||
				   (port->polarity == TYPEC_POLARITY_CC2 &&
				    port->cc2 == TYPEC_CC_OPEN)));
पूर्ण

/*
 * Logging
 */

#अगर_घोषित CONFIG_DEBUG_FS

अटल bool tcpm_log_full(काष्ठा tcpm_port *port)
अणु
	वापस port->logbuffer_tail ==
		(port->logbuffer_head + 1) % LOG_BUFFER_ENTRIES;
पूर्ण

__म_लिखो(2, 0)
अटल व्योम _tcpm_log(काष्ठा tcpm_port *port, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	अक्षर पंचांगpbuffer[LOG_BUFFER_ENTRY_SIZE];
	u64 ts_nsec = local_घड़ी();
	अचिन्हित दीर्घ rem_nsec;

	mutex_lock(&port->logbuffer_lock);
	अगर (!port->logbuffer[port->logbuffer_head]) अणु
		port->logbuffer[port->logbuffer_head] =
				kzalloc(LOG_BUFFER_ENTRY_SIZE, GFP_KERNEL);
		अगर (!port->logbuffer[port->logbuffer_head]) अणु
			mutex_unlock(&port->logbuffer_lock);
			वापस;
		पूर्ण
	पूर्ण

	vsnम_लिखो(पंचांगpbuffer, माप(पंचांगpbuffer), fmt, args);

	अगर (tcpm_log_full(port)) अणु
		port->logbuffer_head = max(port->logbuffer_head - 1, 0);
		म_नकल(पंचांगpbuffer, "overflow");
	पूर्ण

	अगर (port->logbuffer_head < 0 ||
	    port->logbuffer_head >= LOG_BUFFER_ENTRIES) अणु
		dev_warn(port->dev,
			 "Bad log buffer index %d\n", port->logbuffer_head);
		जाओ पात;
	पूर्ण

	अगर (!port->logbuffer[port->logbuffer_head]) अणु
		dev_warn(port->dev,
			 "Log buffer index %d is NULL\n", port->logbuffer_head);
		जाओ पात;
	पूर्ण

	rem_nsec = करो_भाग(ts_nsec, 1000000000);
	scnम_लिखो(port->logbuffer[port->logbuffer_head],
		  LOG_BUFFER_ENTRY_SIZE, "[%5lu.%06lu] %s",
		  (अचिन्हित दीर्घ)ts_nsec, rem_nsec / 1000,
		  पंचांगpbuffer);
	port->logbuffer_head = (port->logbuffer_head + 1) % LOG_BUFFER_ENTRIES;

पात:
	mutex_unlock(&port->logbuffer_lock);
पूर्ण

__म_लिखो(2, 3)
अटल व्योम tcpm_log(काष्ठा tcpm_port *port, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	/* Do not log जबतक disconnected and unattached */
	अगर (tcpm_port_is_disconnected(port) &&
	    (port->state == SRC_UNATTACHED || port->state == SNK_UNATTACHED ||
	     port->state == TOGGLING))
		वापस;

	बहु_शुरू(args, fmt);
	_tcpm_log(port, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

__म_लिखो(2, 3)
अटल व्योम tcpm_log_क्रमce(काष्ठा tcpm_port *port, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	_tcpm_log(port, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम tcpm_log_source_caps(काष्ठा tcpm_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->nr_source_caps; i++) अणु
		u32 pकरो = port->source_caps[i];
		क्रमागत pd_pकरो_type type = pकरो_type(pकरो);
		अक्षर msg[64];

		चयन (type) अणु
		हाल PDO_TYPE_FIXED:
			scnम_लिखो(msg, माप(msg),
				  "%u mV, %u mA [%s%s%s%s%s%s]",
				  pकरो_fixed_voltage(pकरो),
				  pकरो_max_current(pकरो),
				  (pकरो & PDO_FIXED_DUAL_ROLE) ?
							"R" : "",
				  (pकरो & PDO_FIXED_SUSPEND) ?
							"S" : "",
				  (pकरो & PDO_FIXED_HIGHER_CAP) ?
							"H" : "",
				  (pकरो & PDO_FIXED_USB_COMM) ?
							"U" : "",
				  (pकरो & PDO_FIXED_DATA_SWAP) ?
							"D" : "",
				  (pकरो & PDO_FIXED_EXTPOWER) ?
							"E" : "");
			अवरोध;
		हाल PDO_TYPE_VAR:
			scnम_लिखो(msg, माप(msg),
				  "%u-%u mV, %u mA",
				  pकरो_min_voltage(pकरो),
				  pकरो_max_voltage(pकरो),
				  pकरो_max_current(pकरो));
			अवरोध;
		हाल PDO_TYPE_BATT:
			scnम_लिखो(msg, माप(msg),
				  "%u-%u mV, %u mW",
				  pकरो_min_voltage(pकरो),
				  pकरो_max_voltage(pकरो),
				  pकरो_max_घातer(pकरो));
			अवरोध;
		हाल PDO_TYPE_APDO:
			अगर (pकरो_apकरो_type(pकरो) == APDO_TYPE_PPS)
				scnम_लिखो(msg, माप(msg),
					  "%u-%u mV, %u mA",
					  pकरो_pps_apकरो_min_voltage(pकरो),
					  pकरो_pps_apकरो_max_voltage(pकरो),
					  pकरो_pps_apकरो_max_current(pकरो));
			अन्यथा
				म_नकल(msg, "undefined APDO");
			अवरोध;
		शेष:
			म_नकल(msg, "undefined");
			अवरोध;
		पूर्ण
		tcpm_log(port, " PDO %d: type %d, %s",
			 i, type, msg);
	पूर्ण
पूर्ण

अटल पूर्णांक tcpm_debug_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा tcpm_port *port = (काष्ठा tcpm_port *)s->निजी;
	पूर्णांक tail;

	mutex_lock(&port->logbuffer_lock);
	tail = port->logbuffer_tail;
	जबतक (tail != port->logbuffer_head) अणु
		seq_म_लिखो(s, "%s\n", port->logbuffer[tail]);
		tail = (tail + 1) % LOG_BUFFER_ENTRIES;
	पूर्ण
	अगर (!seq_has_overflowed(s))
		port->logbuffer_tail = tail;
	mutex_unlock(&port->logbuffer_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(tcpm_debug);

अटल व्योम tcpm_debugfs_init(काष्ठा tcpm_port *port)
अणु
	अक्षर name[NAME_MAX];

	mutex_init(&port->logbuffer_lock);
	snम_लिखो(name, NAME_MAX, "tcpm-%s", dev_name(port->dev));
	port->dentry = debugfs_create_dir(name, usb_debug_root);
	debugfs_create_file("log", S_IFREG | 0444, port->dentry, port,
			    &tcpm_debug_fops);
पूर्ण

अटल व्योम tcpm_debugfs_निकास(काष्ठा tcpm_port *port)
अणु
	पूर्णांक i;

	mutex_lock(&port->logbuffer_lock);
	क्रम (i = 0; i < LOG_BUFFER_ENTRIES; i++) अणु
		kमुक्त(port->logbuffer[i]);
		port->logbuffer[i] = शून्य;
	पूर्ण
	mutex_unlock(&port->logbuffer_lock);

	debugfs_हटाओ(port->dentry);
पूर्ण

#अन्यथा

__म_लिखो(2, 3)
अटल व्योम tcpm_log(स्थिर काष्ठा tcpm_port *port, स्थिर अक्षर *fmt, ...) अणु पूर्ण
__म_लिखो(2, 3)
अटल व्योम tcpm_log_क्रमce(काष्ठा tcpm_port *port, स्थिर अक्षर *fmt, ...) अणु पूर्ण
अटल व्योम tcpm_log_source_caps(काष्ठा tcpm_port *port) अणु पूर्ण
अटल व्योम tcpm_debugfs_init(स्थिर काष्ठा tcpm_port *port) अणु पूर्ण
अटल व्योम tcpm_debugfs_निकास(स्थिर काष्ठा tcpm_port *port) अणु पूर्ण

#पूर्ण_अगर

अटल व्योम tcpm_set_cc(काष्ठा tcpm_port *port, क्रमागत typec_cc_status cc)
अणु
	tcpm_log(port, "cc:=%d", cc);
	port->cc_req = cc;
	port->tcpc->set_cc(port->tcpc, cc);
पूर्ण

/*
 * Determine RP value to set based on maximum current supported
 * by a port अगर configured as source.
 * Returns CC value to report to link partner.
 */
अटल क्रमागत typec_cc_status tcpm_rp_cc(काष्ठा tcpm_port *port)
अणु
	स्थिर u32 *src_pकरो = port->src_pकरो;
	पूर्णांक nr_pकरो = port->nr_src_pकरो;
	पूर्णांक i;

	/*
	 * Search क्रम first entry with matching voltage.
	 * It should report the maximum supported current.
	 */
	क्रम (i = 0; i < nr_pकरो; i++) अणु
		स्थिर u32 pकरो = src_pकरो[i];

		अगर (pकरो_type(pकरो) == PDO_TYPE_FIXED &&
		    pकरो_fixed_voltage(pकरो) == 5000) अणु
			अचिन्हित पूर्णांक curr = pकरो_max_current(pकरो);

			अगर (curr >= 3000)
				वापस TYPEC_CC_RP_3_0;
			अन्यथा अगर (curr >= 1500)
				वापस TYPEC_CC_RP_1_5;
			वापस TYPEC_CC_RP_DEF;
		पूर्ण
	पूर्ण

	वापस TYPEC_CC_RP_DEF;
पूर्ण

अटल व्योम tcpm_ams_finish(काष्ठा tcpm_port *port)
अणु
	tcpm_log(port, "AMS %s finished", tcpm_ams_str[port->ams]);

	अगर (port->pd_capable && port->pwr_role == TYPEC_SOURCE) अणु
		अगर (port->negotiated_rev >= PD_REV30)
			tcpm_set_cc(port, SINK_TX_OK);
		अन्यथा
			tcpm_set_cc(port, SINK_TX_NG);
	पूर्ण अन्यथा अगर (port->pwr_role == TYPEC_SOURCE) अणु
		tcpm_set_cc(port, tcpm_rp_cc(port));
	पूर्ण

	port->in_ams = false;
	port->ams = NONE_AMS;
पूर्ण

अटल पूर्णांक tcpm_pd_transmit(काष्ठा tcpm_port *port,
			    क्रमागत tcpm_transmit_type type,
			    स्थिर काष्ठा pd_message *msg)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	अगर (msg)
		tcpm_log(port, "PD TX, header: %#x", le16_to_cpu(msg->header));
	अन्यथा
		tcpm_log(port, "PD TX, type: %#x", type);

	reinit_completion(&port->tx_complete);
	ret = port->tcpc->pd_transmit(port->tcpc, type, msg, port->negotiated_rev);
	अगर (ret < 0)
		वापस ret;

	mutex_unlock(&port->lock);
	समयout = रुको_क्रम_completion_समयout(&port->tx_complete,
				msecs_to_jअगरfies(PD_T_TCPC_TX_TIMEOUT));
	mutex_lock(&port->lock);
	अगर (!समयout)
		वापस -ETIMEDOUT;

	चयन (port->tx_status) अणु
	हाल TCPC_TX_SUCCESS:
		port->message_id = (port->message_id + 1) & PD_HEADER_ID_MASK;
		/*
		 * USB PD rev 2.0, 8.3.2.2.1:
		 * USB PD rev 3.0, 8.3.2.1.3:
		 * "... Note that every AMS is Interruptible until the first
		 * Message in the sequence has been successfully sent (GoodCRC
		 * Message received)."
		 */
		अगर (port->ams != NONE_AMS)
			port->in_ams = true;
		अवरोध;
	हाल TCPC_TX_DISCARDED:
		ret = -EAGAIN;
		अवरोध;
	हाल TCPC_TX_FAILED:
	शेष:
		ret = -EIO;
		अवरोध;
	पूर्ण

	/* Some AMS करोn't expect responses. Finish them here. */
	अगर (port->ams == ATTENTION || port->ams == SOURCE_ALERT)
		tcpm_ams_finish(port);

	वापस ret;
पूर्ण

व्योम tcpm_pd_transmit_complete(काष्ठा tcpm_port *port,
			       क्रमागत tcpm_transmit_status status)
अणु
	tcpm_log(port, "PD TX complete, status: %u", status);
	port->tx_status = status;
	complete(&port->tx_complete);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_pd_transmit_complete);

अटल पूर्णांक tcpm_mux_set(काष्ठा tcpm_port *port, पूर्णांक state,
			क्रमागत usb_role usb_role,
			क्रमागत typec_orientation orientation)
अणु
	पूर्णांक ret;

	tcpm_log(port, "Requesting mux state %d, usb-role %d, orientation %d",
		 state, usb_role, orientation);

	ret = typec_set_orientation(port->typec_port, orientation);
	अगर (ret)
		वापस ret;

	अगर (port->role_sw) अणु
		ret = usb_role_चयन_set_role(port->role_sw, usb_role);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस typec_set_mode(port->typec_port, state);
पूर्ण

अटल पूर्णांक tcpm_set_polarity(काष्ठा tcpm_port *port,
			     क्रमागत typec_cc_polarity polarity)
अणु
	पूर्णांक ret;

	tcpm_log(port, "polarity %d", polarity);

	ret = port->tcpc->set_polarity(port->tcpc, polarity);
	अगर (ret < 0)
		वापस ret;

	port->polarity = polarity;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_set_vconn(काष्ठा tcpm_port *port, bool enable)
अणु
	पूर्णांक ret;

	tcpm_log(port, "vconn:=%d", enable);

	ret = port->tcpc->set_vconn(port->tcpc, enable);
	अगर (!ret) अणु
		port->vconn_role = enable ? TYPEC_SOURCE : TYPEC_SINK;
		typec_set_vconn_role(port->typec_port, port->vconn_role);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 tcpm_get_current_limit(काष्ठा tcpm_port *port)
अणु
	क्रमागत typec_cc_status cc;
	u32 limit;

	cc = port->polarity ? port->cc2 : port->cc1;
	चयन (cc) अणु
	हाल TYPEC_CC_RP_1_5:
		limit = 1500;
		अवरोध;
	हाल TYPEC_CC_RP_3_0:
		limit = 3000;
		अवरोध;
	हाल TYPEC_CC_RP_DEF:
	शेष:
		अगर (port->tcpc->get_current_limit)
			limit = port->tcpc->get_current_limit(port->tcpc);
		अन्यथा
			limit = 0;
		अवरोध;
	पूर्ण

	वापस limit;
पूर्ण

अटल पूर्णांक tcpm_set_current_limit(काष्ठा tcpm_port *port, u32 max_ma, u32 mv)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	tcpm_log(port, "Setting voltage/current limit %u mV %u mA", mv, max_ma);

	port->supply_voltage = mv;
	port->current_limit = max_ma;
	घातer_supply_changed(port->psy);

	अगर (port->tcpc->set_current_limit)
		ret = port->tcpc->set_current_limit(port->tcpc, max_ma, mv);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_set_attached_state(काष्ठा tcpm_port *port, bool attached)
अणु
	वापस port->tcpc->set_roles(port->tcpc, attached, port->pwr_role,
				     port->data_role);
पूर्ण

अटल पूर्णांक tcpm_set_roles(काष्ठा tcpm_port *port, bool attached,
			  क्रमागत typec_role role, क्रमागत typec_data_role data)
अणु
	क्रमागत typec_orientation orientation;
	क्रमागत usb_role usb_role;
	पूर्णांक ret;

	अगर (port->polarity == TYPEC_POLARITY_CC1)
		orientation = TYPEC_ORIENTATION_NORMAL;
	अन्यथा
		orientation = TYPEC_ORIENTATION_REVERSE;

	अगर (port->typec_caps.data == TYPEC_PORT_DRD) अणु
		अगर (data == TYPEC_HOST)
			usb_role = USB_ROLE_HOST;
		अन्यथा
			usb_role = USB_ROLE_DEVICE;
	पूर्ण अन्यथा अगर (port->typec_caps.data == TYPEC_PORT_DFP) अणु
		अगर (data == TYPEC_HOST) अणु
			अगर (role == TYPEC_SOURCE)
				usb_role = USB_ROLE_HOST;
			अन्यथा
				usb_role = USB_ROLE_NONE;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (data == TYPEC_DEVICE) अणु
			अगर (role == TYPEC_SINK)
				usb_role = USB_ROLE_DEVICE;
			अन्यथा
				usb_role = USB_ROLE_NONE;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	ret = tcpm_mux_set(port, TYPEC_STATE_USB, usb_role, orientation);
	अगर (ret < 0)
		वापस ret;

	ret = port->tcpc->set_roles(port->tcpc, attached, role, data);
	अगर (ret < 0)
		वापस ret;

	port->pwr_role = role;
	port->data_role = data;
	typec_set_data_role(port->typec_port, data);
	typec_set_pwr_role(port->typec_port, role);

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_set_pwr_role(काष्ठा tcpm_port *port, क्रमागत typec_role role)
अणु
	पूर्णांक ret;

	ret = port->tcpc->set_roles(port->tcpc, true, role,
				    port->data_role);
	अगर (ret < 0)
		वापस ret;

	port->pwr_role = role;
	typec_set_pwr_role(port->typec_port, role);

	वापस 0;
पूर्ण

/*
 * Transक्रमm the PDO to be compliant to PD rev2.0.
 * Return 0 अगर the PDO type is not defined in PD rev2.0.
 * Otherwise, वापस the converted PDO.
 */
अटल u32 tcpm_क्रमge_legacy_pकरो(काष्ठा tcpm_port *port, u32 pकरो, क्रमागत typec_role role)
अणु
	चयन (pकरो_type(pकरो)) अणु
	हाल PDO_TYPE_FIXED:
		अगर (role == TYPEC_SINK)
			वापस pकरो & ~PDO_FIXED_FRS_CURR_MASK;
		अन्यथा
			वापस pकरो & ~PDO_FIXED_UNCHUNK_EXT;
	हाल PDO_TYPE_VAR:
	हाल PDO_TYPE_BATT:
		वापस pकरो;
	हाल PDO_TYPE_APDO:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tcpm_pd_send_source_caps(काष्ठा tcpm_port *port)
अणु
	काष्ठा pd_message msg;
	u32 pकरो;
	अचिन्हित पूर्णांक i, nr_pकरो = 0;

	स_रखो(&msg, 0, माप(msg));

	क्रम (i = 0; i < port->nr_src_pकरो; i++) अणु
		अगर (port->negotiated_rev >= PD_REV30) अणु
			msg.payload[nr_pकरो++] =	cpu_to_le32(port->src_pकरो[i]);
		पूर्ण अन्यथा अणु
			pकरो = tcpm_क्रमge_legacy_pकरो(port, port->src_pकरो[i], TYPEC_SOURCE);
			अगर (pकरो)
				msg.payload[nr_pकरो++] = cpu_to_le32(pकरो);
		पूर्ण
	पूर्ण

	अगर (!nr_pकरो) अणु
		/* No source capabilities defined, sink only */
		msg.header = PD_HEADER_LE(PD_CTRL_REJECT,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id, 0);
	पूर्ण अन्यथा अणु
		msg.header = PD_HEADER_LE(PD_DATA_SOURCE_CAP,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id,
					  nr_pकरो);
	पूर्ण

	वापस tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
पूर्ण

अटल पूर्णांक tcpm_pd_send_sink_caps(काष्ठा tcpm_port *port)
अणु
	काष्ठा pd_message msg;
	u32 pकरो;
	अचिन्हित पूर्णांक i, nr_pकरो = 0;

	स_रखो(&msg, 0, माप(msg));

	क्रम (i = 0; i < port->nr_snk_pकरो; i++) अणु
		अगर (port->negotiated_rev >= PD_REV30) अणु
			msg.payload[nr_pकरो++] =	cpu_to_le32(port->snk_pकरो[i]);
		पूर्ण अन्यथा अणु
			pकरो = tcpm_क्रमge_legacy_pकरो(port, port->snk_pकरो[i], TYPEC_SINK);
			अगर (pकरो)
				msg.payload[nr_pकरो++] = cpu_to_le32(pकरो);
		पूर्ण
	पूर्ण

	अगर (!nr_pकरो) अणु
		/* No sink capabilities defined, source only */
		msg.header = PD_HEADER_LE(PD_CTRL_REJECT,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id, 0);
	पूर्ण अन्यथा अणु
		msg.header = PD_HEADER_LE(PD_DATA_SINK_CAP,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id,
					  nr_pकरो);
	पूर्ण

	वापस tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
पूर्ण

अटल व्योम mod_tcpm_delayed_work(काष्ठा tcpm_port *port, अचिन्हित पूर्णांक delay_ms)
अणु
	अगर (delay_ms) अणु
		hrसमयr_start(&port->state_machine_समयr, ms_to_kसमय(delay_ms), HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		hrसमयr_cancel(&port->state_machine_समयr);
		kthपढ़ो_queue_work(port->wq, &port->state_machine);
	पूर्ण
पूर्ण

अटल व्योम mod_vdm_delayed_work(काष्ठा tcpm_port *port, अचिन्हित पूर्णांक delay_ms)
अणु
	अगर (delay_ms) अणु
		hrसमयr_start(&port->vdm_state_machine_समयr, ms_to_kसमय(delay_ms),
			      HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		hrसमयr_cancel(&port->vdm_state_machine_समयr);
		kthपढ़ो_queue_work(port->wq, &port->vdm_state_machine);
	पूर्ण
पूर्ण

अटल व्योम mod_enable_frs_delayed_work(काष्ठा tcpm_port *port, अचिन्हित पूर्णांक delay_ms)
अणु
	अगर (delay_ms) अणु
		hrसमयr_start(&port->enable_frs_समयr, ms_to_kसमय(delay_ms), HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		hrसमयr_cancel(&port->enable_frs_समयr);
		kthपढ़ो_queue_work(port->wq, &port->enable_frs);
	पूर्ण
पूर्ण

अटल व्योम mod_send_discover_delayed_work(काष्ठा tcpm_port *port, अचिन्हित पूर्णांक delay_ms)
अणु
	अगर (delay_ms) अणु
		hrसमयr_start(&port->send_discover_समयr, ms_to_kसमय(delay_ms), HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		hrसमयr_cancel(&port->send_discover_समयr);
		kthपढ़ो_queue_work(port->wq, &port->send_discover_work);
	पूर्ण
पूर्ण

अटल व्योम tcpm_set_state(काष्ठा tcpm_port *port, क्रमागत tcpm_state state,
			   अचिन्हित पूर्णांक delay_ms)
अणु
	अगर (delay_ms) अणु
		tcpm_log(port, "pending state change %s -> %s @ %u ms [%s %s]",
			 tcpm_states[port->state], tcpm_states[state], delay_ms,
			 pd_rev[port->negotiated_rev], tcpm_ams_str[port->ams]);
		port->delayed_state = state;
		mod_tcpm_delayed_work(port, delay_ms);
		port->delayed_runसमय = kसमय_add(kसमय_get(), ms_to_kसमय(delay_ms));
		port->delay_ms = delay_ms;
	पूर्ण अन्यथा अणु
		tcpm_log(port, "state change %s -> %s [%s %s]",
			 tcpm_states[port->state], tcpm_states[state],
			 pd_rev[port->negotiated_rev], tcpm_ams_str[port->ams]);
		port->delayed_state = INVALID_STATE;
		port->prev_state = port->state;
		port->state = state;
		/*
		 * Don't re-queue the state machine work item if we're currently
		 * in the state machine and we're immediately changing states.
		 * tcpm_state_machine_work() will जारी running the state
		 * machine.
		 */
		अगर (!port->state_machine_running)
			mod_tcpm_delayed_work(port, 0);
	पूर्ण
पूर्ण

अटल व्योम tcpm_set_state_cond(काष्ठा tcpm_port *port, क्रमागत tcpm_state state,
				अचिन्हित पूर्णांक delay_ms)
अणु
	अगर (port->enter_state == port->state)
		tcpm_set_state(port, state, delay_ms);
	अन्यथा
		tcpm_log(port,
			 "skipped %sstate change %s -> %s [%u ms], context state %s [%s %s]",
			 delay_ms ? "delayed " : "",
			 tcpm_states[port->state], tcpm_states[state],
			 delay_ms, tcpm_states[port->enter_state],
			 pd_rev[port->negotiated_rev], tcpm_ams_str[port->ams]);
पूर्ण

अटल व्योम tcpm_queue_message(काष्ठा tcpm_port *port,
			       क्रमागत pd_msg_request message)
अणु
	port->queued_message = message;
	mod_tcpm_delayed_work(port, 0);
पूर्ण

अटल bool tcpm_vdm_ams(काष्ठा tcpm_port *port)
अणु
	चयन (port->ams) अणु
	हाल DISCOVER_IDENTITY:
	हाल SOURCE_STARTUP_CABLE_PLUG_DISCOVER_IDENTITY:
	हाल DISCOVER_SVIDS:
	हाल DISCOVER_MODES:
	हाल DFP_TO_UFP_ENTER_MODE:
	हाल DFP_TO_UFP_EXIT_MODE:
	हाल DFP_TO_CABLE_PLUG_ENTER_MODE:
	हाल DFP_TO_CABLE_PLUG_EXIT_MODE:
	हाल ATTENTION:
	हाल UNSTRUCTURED_VDMS:
	हाल STRUCTURED_VDMS:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool tcpm_ams_पूर्णांकerruptible(काष्ठा tcpm_port *port)
अणु
	चयन (port->ams) अणु
	/* Interruptible AMS */
	हाल NONE_AMS:
	हाल SECURITY:
	हाल FIRMWARE_UPDATE:
	हाल DISCOVER_IDENTITY:
	हाल SOURCE_STARTUP_CABLE_PLUG_DISCOVER_IDENTITY:
	हाल DISCOVER_SVIDS:
	हाल DISCOVER_MODES:
	हाल DFP_TO_UFP_ENTER_MODE:
	हाल DFP_TO_UFP_EXIT_MODE:
	हाल DFP_TO_CABLE_PLUG_ENTER_MODE:
	हाल DFP_TO_CABLE_PLUG_EXIT_MODE:
	हाल UNSTRUCTURED_VDMS:
	हाल STRUCTURED_VDMS:
	हाल COUNTRY_INFO:
	हाल COUNTRY_CODES:
		अवरोध;
	/* Non-Interruptible AMS */
	शेष:
		अगर (port->in_ams)
			वापस false;
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक tcpm_ams_start(काष्ठा tcpm_port *port, क्रमागत tcpm_ams ams)
अणु
	पूर्णांक ret = 0;

	tcpm_log(port, "AMS %s start", tcpm_ams_str[ams]);

	अगर (!tcpm_ams_पूर्णांकerruptible(port) &&
	    !(ams == HARD_RESET || ams == SOFT_RESET_AMS)) अणु
		port->upcoming_state = INVALID_STATE;
		tcpm_log(port, "AMS %s not interruptible, aborting",
			 tcpm_ams_str[port->ams]);
		वापस -EAGAIN;
	पूर्ण

	अगर (port->pwr_role == TYPEC_SOURCE) अणु
		क्रमागत typec_cc_status cc_req = port->cc_req;

		port->ams = ams;

		अगर (ams == HARD_RESET) अणु
			tcpm_set_cc(port, tcpm_rp_cc(port));
			tcpm_pd_transmit(port, TCPC_TX_HARD_RESET, शून्य);
			tcpm_set_state(port, HARD_RESET_START, 0);
			वापस ret;
		पूर्ण अन्यथा अगर (ams == SOFT_RESET_AMS) अणु
			अगर (!port->explicit_contract)
				tcpm_set_cc(port, tcpm_rp_cc(port));
			tcpm_set_state(port, SOFT_RESET_SEND, 0);
			वापस ret;
		पूर्ण अन्यथा अगर (tcpm_vdm_ams(port)) अणु
			/* tSinkTx is enक्रमced in vdm_run_state_machine */
			अगर (port->negotiated_rev >= PD_REV30)
				tcpm_set_cc(port, SINK_TX_NG);
			वापस ret;
		पूर्ण

		अगर (port->negotiated_rev >= PD_REV30)
			tcpm_set_cc(port, SINK_TX_NG);

		चयन (port->state) अणु
		हाल SRC_READY:
		हाल SRC_STARTUP:
		हाल SRC_SOFT_RESET_WAIT_SNK_TX:
		हाल SOFT_RESET:
		हाल SOFT_RESET_SEND:
			अगर (port->negotiated_rev >= PD_REV30)
				tcpm_set_state(port, AMS_START,
					       cc_req == SINK_TX_OK ?
					       PD_T_SINK_TX : 0);
			अन्यथा
				tcpm_set_state(port, AMS_START, 0);
			अवरोध;
		शेष:
			अगर (port->negotiated_rev >= PD_REV30)
				tcpm_set_state(port, SRC_READY,
					       cc_req == SINK_TX_OK ?
					       PD_T_SINK_TX : 0);
			अन्यथा
				tcpm_set_state(port, SRC_READY, 0);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (port->negotiated_rev >= PD_REV30 &&
		    !tcpm_sink_tx_ok(port) &&
		    ams != SOFT_RESET_AMS &&
		    ams != HARD_RESET) अणु
			port->upcoming_state = INVALID_STATE;
			tcpm_log(port, "Sink TX No Go");
			वापस -EAGAIN;
		पूर्ण

		port->ams = ams;

		अगर (ams == HARD_RESET) अणु
			tcpm_pd_transmit(port, TCPC_TX_HARD_RESET, शून्य);
			tcpm_set_state(port, HARD_RESET_START, 0);
			वापस ret;
		पूर्ण अन्यथा अगर (tcpm_vdm_ams(port)) अणु
			वापस ret;
		पूर्ण

		अगर (port->state == SNK_READY ||
		    port->state == SNK_SOFT_RESET)
			tcpm_set_state(port, AMS_START, 0);
		अन्यथा
			tcpm_set_state(port, SNK_READY, 0);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * VDM/VDO handling functions
 */
अटल व्योम tcpm_queue_vdm(काष्ठा tcpm_port *port, स्थिर u32 header,
			   स्थिर u32 *data, पूर्णांक cnt)
अणु
	WARN_ON(!mutex_is_locked(&port->lock));

	/* Make sure we are not still processing a previous VDM packet */
	WARN_ON(port->vdm_state > VDM_STATE_DONE);

	port->vकरो_count = cnt + 1;
	port->vकरो_data[0] = header;
	स_नकल(&port->vकरो_data[1], data, माप(u32) * cnt);
	/* Set पढ़ोy, vdm state machine will actually send */
	port->vdm_retries = 0;
	port->vdm_state = VDM_STATE_READY;

	mod_vdm_delayed_work(port, 0);
पूर्ण

अटल व्योम tcpm_queue_vdm_unlocked(काष्ठा tcpm_port *port, स्थिर u32 header,
				    स्थिर u32 *data, पूर्णांक cnt)
अणु
	mutex_lock(&port->lock);
	tcpm_queue_vdm(port, header, data, cnt);
	mutex_unlock(&port->lock);
पूर्ण

अटल व्योम svdm_consume_identity(काष्ठा tcpm_port *port, स्थिर u32 *p, पूर्णांक cnt)
अणु
	u32 vकरो = p[VDO_INDEX_IDH];
	u32 product = p[VDO_INDEX_PRODUCT];

	स_रखो(&port->mode_data, 0, माप(port->mode_data));

	port->partner_ident.id_header = vकरो;
	port->partner_ident.cert_stat = p[VDO_INDEX_CSTAT];
	port->partner_ident.product = product;

	typec_partner_set_identity(port->partner);

	tcpm_log(port, "Identity: %04x:%04x.%04x",
		 PD_IDH_VID(vकरो),
		 PD_PRODUCT_PID(product), product & 0xffff);
पूर्ण

अटल bool svdm_consume_svids(काष्ठा tcpm_port *port, स्थिर u32 *p, पूर्णांक cnt)
अणु
	काष्ठा pd_mode_data *pmdata = &port->mode_data;
	पूर्णांक i;

	क्रम (i = 1; i < cnt; i++) अणु
		u16 svid;

		svid = (p[i] >> 16) & 0xffff;
		अगर (!svid)
			वापस false;

		अगर (pmdata->nsvids >= SVID_DISCOVERY_MAX)
			जाओ पात;

		pmdata->svids[pmdata->nsvids++] = svid;
		tcpm_log(port, "SVID %d: 0x%x", pmdata->nsvids, svid);

		svid = p[i] & 0xffff;
		अगर (!svid)
			वापस false;

		अगर (pmdata->nsvids >= SVID_DISCOVERY_MAX)
			जाओ पात;

		pmdata->svids[pmdata->nsvids++] = svid;
		tcpm_log(port, "SVID %d: 0x%x", pmdata->nsvids, svid);
	पूर्ण
	वापस true;
पात:
	tcpm_log(port, "SVID_DISCOVERY_MAX(%d) too low!", SVID_DISCOVERY_MAX);
	वापस false;
पूर्ण

अटल व्योम svdm_consume_modes(काष्ठा tcpm_port *port, स्थिर u32 *p, पूर्णांक cnt)
अणु
	काष्ठा pd_mode_data *pmdata = &port->mode_data;
	काष्ठा typec_alपंचांगode_desc *palपंचांगode;
	पूर्णांक i;

	अगर (pmdata->alपंचांगodes >= ARRAY_SIZE(port->partner_alपंचांगode)) अणु
		/* Alपढ़ोy logged in svdm_consume_svids() */
		वापस;
	पूर्ण

	क्रम (i = 1; i < cnt; i++) अणु
		palपंचांगode = &pmdata->alपंचांगode_desc[pmdata->alपंचांगodes];
		स_रखो(palपंचांगode, 0, माप(*palपंचांगode));

		palपंचांगode->svid = pmdata->svids[pmdata->svid_index];
		palपंचांगode->mode = i;
		palपंचांगode->vकरो = p[i];

		tcpm_log(port, " Alternate mode %d: SVID 0x%04x, VDO %d: 0x%08x",
			 pmdata->alपंचांगodes, palपंचांगode->svid,
			 palपंचांगode->mode, palपंचांगode->vकरो);

		pmdata->alपंचांगodes++;
	पूर्ण
पूर्ण

अटल व्योम tcpm_रेजिस्टर_partner_alपंचांगodes(काष्ठा tcpm_port *port)
अणु
	काष्ठा pd_mode_data *modep = &port->mode_data;
	काष्ठा typec_alपंचांगode *alपंचांगode;
	पूर्णांक i;

	क्रम (i = 0; i < modep->alपंचांगodes; i++) अणु
		alपंचांगode = typec_partner_रेजिस्टर_alपंचांगode(port->partner,
						&modep->alपंचांगode_desc[i]);
		अगर (IS_ERR(alपंचांगode)) अणु
			tcpm_log(port, "Failed to register partner SVID 0x%04x",
				 modep->alपंचांगode_desc[i].svid);
			alपंचांगode = शून्य;
		पूर्ण
		port->partner_alपंचांगode[i] = alपंचांगode;
	पूर्ण
पूर्ण

#घोषणा supports_modal(port)	PD_IDH_MODAL_SUPP((port)->partner_ident.id_header)

अटल पूर्णांक tcpm_pd_svdm(काष्ठा tcpm_port *port, काष्ठा typec_alपंचांगode *adev,
			स्थिर u32 *p, पूर्णांक cnt, u32 *response,
			क्रमागत adev_actions *adev_action)
अणु
	काष्ठा typec_port *typec = port->typec_port;
	काष्ठा typec_alपंचांगode *pdev;
	काष्ठा pd_mode_data *modep;
	पूर्णांक svdm_version;
	पूर्णांक rlen = 0;
	पूर्णांक cmd_type;
	पूर्णांक cmd;
	पूर्णांक i;

	cmd_type = PD_VDO_CMDT(p[0]);
	cmd = PD_VDO_CMD(p[0]);

	tcpm_log(port, "Rx VDM cmd 0x%x type %d cmd %d len %d",
		 p[0], cmd_type, cmd, cnt);

	modep = &port->mode_data;

	pdev = typec_match_alपंचांगode(port->partner_alपंचांगode, ALTMODE_DISCOVERY_MAX,
				   PD_VDO_VID(p[0]), PD_VDO_OPOS(p[0]));

	svdm_version = typec_get_negotiated_svdm_version(typec);
	अगर (svdm_version < 0)
		वापस 0;

	चयन (cmd_type) अणु
	हाल CMDT_INIT:
		चयन (cmd) अणु
		हाल CMD_DISCOVER_IDENT:
			अगर (PD_VDO_VID(p[0]) != USB_SID_PD)
				अवरोध;

			अगर (PD_VDO_SVDM_VER(p[0]) < svdm_version) अणु
				typec_partner_set_svdm_version(port->partner,
							       PD_VDO_SVDM_VER(p[0]));
				svdm_version = PD_VDO_SVDM_VER(p[0]);
			पूर्ण

			port->ams = DISCOVER_IDENTITY;
			/*
			 * PD2.0 Spec 6.10.3: respond with NAK as DFP (data host)
			 * PD3.1 Spec 6.4.4.2.5.1: respond with NAK अगर "invalid field" or
			 * "wrong configuation" or "Unrecognized"
			 */
			अगर ((port->data_role == TYPEC_DEVICE || svdm_version >= SVDM_VER_2_0) &&
			    port->nr_snk_vकरो) अणु
				अगर (svdm_version < SVDM_VER_2_0) अणु
					क्रम (i = 0; i < port->nr_snk_vकरो_v1; i++)
						response[i + 1] = port->snk_vकरो_v1[i];
					rlen = port->nr_snk_vकरो_v1 + 1;

				पूर्ण अन्यथा अणु
					क्रम (i = 0; i < port->nr_snk_vकरो; i++)
						response[i + 1] = port->snk_vकरो[i];
					rlen = port->nr_snk_vकरो + 1;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल CMD_DISCOVER_SVID:
			port->ams = DISCOVER_SVIDS;
			अवरोध;
		हाल CMD_DISCOVER_MODES:
			port->ams = DISCOVER_MODES;
			अवरोध;
		हाल CMD_ENTER_MODE:
			port->ams = DFP_TO_UFP_ENTER_MODE;
			अवरोध;
		हाल CMD_EXIT_MODE:
			port->ams = DFP_TO_UFP_EXIT_MODE;
			अवरोध;
		हाल CMD_ATTENTION:
			/* Attention command करोes not have response */
			*adev_action = ADEV_ATTENTION;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अगर (rlen >= 1) अणु
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_ACK);
		पूर्ण अन्यथा अगर (rlen == 0) अणु
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_NAK);
			rlen = 1;
		पूर्ण अन्यथा अणु
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_BUSY);
			rlen = 1;
		पूर्ण
		response[0] = (response[0] & ~VDO_SVDM_VERS_MASK) |
			      (VDO_SVDM_VERS(typec_get_negotiated_svdm_version(typec)));
		अवरोध;
	हाल CMDT_RSP_ACK:
		/* silently drop message अगर we are not connected */
		अगर (IS_ERR_OR_शून्य(port->partner))
			अवरोध;

		tcpm_ams_finish(port);

		चयन (cmd) अणु
		हाल CMD_DISCOVER_IDENT:
			अगर (PD_VDO_SVDM_VER(p[0]) < svdm_version)
				typec_partner_set_svdm_version(port->partner,
							       PD_VDO_SVDM_VER(p[0]));
			/* 6.4.4.3.1 */
			svdm_consume_identity(port, p, cnt);
			response[0] = VDO(USB_SID_PD, 1, typec_get_negotiated_svdm_version(typec),
					  CMD_DISCOVER_SVID);
			rlen = 1;
			अवरोध;
		हाल CMD_DISCOVER_SVID:
			/* 6.4.4.3.2 */
			अगर (svdm_consume_svids(port, p, cnt)) अणु
				response[0] = VDO(USB_SID_PD, 1, svdm_version, CMD_DISCOVER_SVID);
				rlen = 1;
			पूर्ण अन्यथा अगर (modep->nsvids && supports_modal(port)) अणु
				response[0] = VDO(modep->svids[0], 1, svdm_version,
						  CMD_DISCOVER_MODES);
				rlen = 1;
			पूर्ण
			अवरोध;
		हाल CMD_DISCOVER_MODES:
			/* 6.4.4.3.3 */
			svdm_consume_modes(port, p, cnt);
			modep->svid_index++;
			अगर (modep->svid_index < modep->nsvids) अणु
				u16 svid = modep->svids[modep->svid_index];
				response[0] = VDO(svid, 1, svdm_version, CMD_DISCOVER_MODES);
				rlen = 1;
			पूर्ण अन्यथा अणु
				tcpm_रेजिस्टर_partner_alपंचांगodes(port);
				port->vdm_sm_running = false;
			पूर्ण
			अवरोध;
		हाल CMD_ENTER_MODE:
			अगर (adev && pdev) अणु
				typec_alपंचांगode_update_active(pdev, true);
				*adev_action = ADEV_QUEUE_VDM_SEND_EXIT_MODE_ON_FAIL;
			पूर्ण
			वापस 0;
		हाल CMD_EXIT_MODE:
			अगर (adev && pdev) अणु
				typec_alपंचांगode_update_active(pdev, false);
				/* Back to USB Operation */
				*adev_action = ADEV_NOTIFY_USB_AND_QUEUE_VDM;
				वापस 0;
			पूर्ण
			अवरोध;
		हाल VDO_CMD_VENDOR(0) ... VDO_CMD_VENDOR(15):
			अवरोध;
		शेष:
			/* Unrecognized SVDM */
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_NAK);
			rlen = 1;
			response[0] = (response[0] & ~VDO_SVDM_VERS_MASK) |
				      (VDO_SVDM_VERS(svdm_version));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CMDT_RSP_NAK:
		tcpm_ams_finish(port);
		चयन (cmd) अणु
		हाल CMD_DISCOVER_IDENT:
		हाल CMD_DISCOVER_SVID:
		हाल CMD_DISCOVER_MODES:
		हाल VDO_CMD_VENDOR(0) ... VDO_CMD_VENDOR(15):
			अवरोध;
		हाल CMD_ENTER_MODE:
			/* Back to USB Operation */
			*adev_action = ADEV_NOTIFY_USB_AND_QUEUE_VDM;
			वापस 0;
		शेष:
			/* Unrecognized SVDM */
			response[0] = p[0] | VDO_CMDT(CMDT_RSP_NAK);
			rlen = 1;
			response[0] = (response[0] & ~VDO_SVDM_VERS_MASK) |
				      (VDO_SVDM_VERS(svdm_version));
			अवरोध;
		पूर्ण
		port->vdm_sm_running = false;
		अवरोध;
	शेष:
		response[0] = p[0] | VDO_CMDT(CMDT_RSP_NAK);
		rlen = 1;
		response[0] = (response[0] & ~VDO_SVDM_VERS_MASK) |
			      (VDO_SVDM_VERS(svdm_version));
		port->vdm_sm_running = false;
		अवरोध;
	पूर्ण

	/* Inक्रमming the alternate mode drivers about everything */
	*adev_action = ADEV_QUEUE_VDM;
	वापस rlen;
पूर्ण

अटल व्योम tcpm_handle_vdm_request(काष्ठा tcpm_port *port,
				    स्थिर __le32 *payload, पूर्णांक cnt)
अणु
	क्रमागत adev_actions adev_action = ADEV_NONE;
	काष्ठा typec_alपंचांगode *adev;
	u32 p[PD_MAX_PAYLOAD];
	u32 response[8] = अणु पूर्ण;
	पूर्णांक i, rlen = 0;

	क्रम (i = 0; i < cnt; i++)
		p[i] = le32_to_cpu(payload[i]);

	adev = typec_match_alपंचांगode(port->port_alपंचांगode, ALTMODE_DISCOVERY_MAX,
				   PD_VDO_VID(p[0]), PD_VDO_OPOS(p[0]));

	अगर (port->vdm_state == VDM_STATE_BUSY) अणु
		/* If UFP responded busy retry after समयout */
		अगर (PD_VDO_CMDT(p[0]) == CMDT_RSP_BUSY) अणु
			port->vdm_state = VDM_STATE_WAIT_RSP_BUSY;
			port->vकरो_retry = (p[0] & ~VDO_CMDT_MASK) |
				CMDT_INIT;
			mod_vdm_delayed_work(port, PD_T_VDM_BUSY);
			वापस;
		पूर्ण
		port->vdm_state = VDM_STATE_DONE;
	पूर्ण

	अगर (PD_VDO_SVDM(p[0])) अणु
		rlen = tcpm_pd_svdm(port, adev, p, cnt, response, &adev_action);
	पूर्ण अन्यथा अणु
		अगर (port->negotiated_rev >= PD_REV30)
			tcpm_queue_message(port, PD_MSG_CTRL_NOT_SUPP);
	पूर्ण

	/*
	 * We are करोne with any state stored in the port काष्ठा now, except
	 * क्रम any port काष्ठा changes करोne by the tcpm_queue_vdm() call
	 * below, which is a separate operation.
	 *
	 * So we can safely release the lock here; and we MUST release the
	 * lock here to aव्योम an AB BA lock inversion:
	 *
	 * If we keep the lock here then the lock ordering in this path is:
	 * 1. tcpm_pd_rx_handler take the tcpm port lock
	 * 2. One of the typec_alपंचांगode_* calls below takes the alt-mode's lock
	 *
	 * And we also have this ordering:
	 * 1. alt-mode driver takes the alt-mode's lock
	 * 2. alt-mode driver calls tcpm_alपंचांगode_enter which takes the
	 *    tcpm port lock
	 *
	 * Dropping our lock here aव्योमs this.
	 */
	mutex_unlock(&port->lock);

	अगर (adev) अणु
		चयन (adev_action) अणु
		हाल ADEV_NONE:
			अवरोध;
		हाल ADEV_NOTIFY_USB_AND_QUEUE_VDM:
			WARN_ON(typec_alपंचांगode_notअगरy(adev, TYPEC_STATE_USB, शून्य));
			typec_alपंचांगode_vdm(adev, p[0], &p[1], cnt);
			अवरोध;
		हाल ADEV_QUEUE_VDM:
			typec_alपंचांगode_vdm(adev, p[0], &p[1], cnt);
			अवरोध;
		हाल ADEV_QUEUE_VDM_SEND_EXIT_MODE_ON_FAIL:
			अगर (typec_alपंचांगode_vdm(adev, p[0], &p[1], cnt)) अणु
				पूर्णांक svdm_version = typec_get_negotiated_svdm_version(
									port->typec_port);
				अगर (svdm_version < 0)
					अवरोध;

				response[0] = VDO(adev->svid, 1, svdm_version,
						  CMD_EXIT_MODE);
				response[0] |= VDO_OPOS(adev->mode);
				rlen = 1;
			पूर्ण
			अवरोध;
		हाल ADEV_ATTENTION:
			typec_alपंचांगode_attention(adev, p[1]);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * We must re-take the lock here to balance the unlock in
	 * tcpm_pd_rx_handler, note that no changes, other then the
	 * tcpm_queue_vdm call, are made जबतक the lock is held again.
	 * All that is करोne after the call is unwinding the call stack until
	 * we वापस to tcpm_pd_rx_handler and करो the unlock there.
	 */
	mutex_lock(&port->lock);

	अगर (rlen > 0)
		tcpm_queue_vdm(port, response[0], &response[1], rlen - 1);
पूर्ण

अटल व्योम tcpm_send_vdm(काष्ठा tcpm_port *port, u32 vid, पूर्णांक cmd,
			  स्थिर u32 *data, पूर्णांक count)
अणु
	पूर्णांक svdm_version = typec_get_negotiated_svdm_version(port->typec_port);
	u32 header;

	अगर (svdm_version < 0)
		वापस;

	अगर (WARN_ON(count > VDO_MAX_SIZE - 1))
		count = VDO_MAX_SIZE - 1;

	/* set VDM header with VID & CMD */
	header = VDO(vid, ((vid & USB_SID_PD) == USB_SID_PD) ?
			1 : (PD_VDO_CMD(cmd) <= CMD_ATTENTION),
			svdm_version, cmd);
	tcpm_queue_vdm(port, header, data, count);
पूर्ण

अटल अचिन्हित पूर्णांक vdm_पढ़ोy_समयout(u32 vdm_hdr)
अणु
	अचिन्हित पूर्णांक समयout;
	पूर्णांक cmd = PD_VDO_CMD(vdm_hdr);

	/* its not a काष्ठाured VDM command */
	अगर (!PD_VDO_SVDM(vdm_hdr))
		वापस PD_T_VDM_UNSTRUCTURED;

	चयन (PD_VDO_CMDT(vdm_hdr)) अणु
	हाल CMDT_INIT:
		अगर (cmd == CMD_ENTER_MODE || cmd == CMD_EXIT_MODE)
			समयout = PD_T_VDM_WAIT_MODE_E;
		अन्यथा
			समयout = PD_T_VDM_SNDR_RSP;
		अवरोध;
	शेष:
		अगर (cmd == CMD_ENTER_MODE || cmd == CMD_EXIT_MODE)
			समयout = PD_T_VDM_E_MODE;
		अन्यथा
			समयout = PD_T_VDM_RCVR_RSP;
		अवरोध;
	पूर्ण
	वापस समयout;
पूर्ण

अटल व्योम vdm_run_state_machine(काष्ठा tcpm_port *port)
अणु
	काष्ठा pd_message msg;
	पूर्णांक i, res = 0;
	u32 vकरो_hdr = port->vकरो_data[0];

	चयन (port->vdm_state) अणु
	हाल VDM_STATE_READY:
		/* Only transmit VDM अगर attached */
		अगर (!port->attached) अणु
			port->vdm_state = VDM_STATE_ERR_BUSY;
			अवरोध;
		पूर्ण

		/*
		 * अगर there's traffic or we're not in PDO ready state don't send
		 * a VDM.
		 */
		अगर (port->state != SRC_READY && port->state != SNK_READY)
			अवरोध;

		/* TODO: AMS operation क्रम Unकाष्ठाured VDM */
		अगर (PD_VDO_SVDM(vकरो_hdr) && PD_VDO_CMDT(vकरो_hdr) == CMDT_INIT) अणु
			चयन (PD_VDO_CMD(vकरो_hdr)) अणु
			हाल CMD_DISCOVER_IDENT:
				res = tcpm_ams_start(port, DISCOVER_IDENTITY);
				अगर (res == 0)
					port->send_discover = false;
				अन्यथा अगर (res == -EAGAIN)
					mod_send_discover_delayed_work(port,
								       SEND_DISCOVER_RETRY_MS);
				अवरोध;
			हाल CMD_DISCOVER_SVID:
				res = tcpm_ams_start(port, DISCOVER_SVIDS);
				अवरोध;
			हाल CMD_DISCOVER_MODES:
				res = tcpm_ams_start(port, DISCOVER_MODES);
				अवरोध;
			हाल CMD_ENTER_MODE:
				res = tcpm_ams_start(port, DFP_TO_UFP_ENTER_MODE);
				अवरोध;
			हाल CMD_EXIT_MODE:
				res = tcpm_ams_start(port, DFP_TO_UFP_EXIT_MODE);
				अवरोध;
			हाल CMD_ATTENTION:
				res = tcpm_ams_start(port, ATTENTION);
				अवरोध;
			हाल VDO_CMD_VENDOR(0) ... VDO_CMD_VENDOR(15):
				res = tcpm_ams_start(port, STRUCTURED_VDMS);
				अवरोध;
			शेष:
				res = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			अगर (res < 0) अणु
				port->vdm_state = VDM_STATE_ERR_BUSY;
				वापस;
			पूर्ण
		पूर्ण

		port->vdm_state = VDM_STATE_SEND_MESSAGE;
		mod_vdm_delayed_work(port, (port->negotiated_rev >= PD_REV30 &&
					    port->pwr_role == TYPEC_SOURCE &&
					    PD_VDO_SVDM(vकरो_hdr) &&
					    PD_VDO_CMDT(vकरो_hdr) == CMDT_INIT) ?
					   PD_T_SINK_TX : 0);
		अवरोध;
	हाल VDM_STATE_WAIT_RSP_BUSY:
		port->vकरो_data[0] = port->vकरो_retry;
		port->vकरो_count = 1;
		port->vdm_state = VDM_STATE_READY;
		tcpm_ams_finish(port);
		अवरोध;
	हाल VDM_STATE_BUSY:
		port->vdm_state = VDM_STATE_ERR_TMOUT;
		अगर (port->ams != NONE_AMS)
			tcpm_ams_finish(port);
		अवरोध;
	हाल VDM_STATE_ERR_SEND:
		/*
		 * A partner which करोes not support USB PD will not reply,
		 * so this is not a fatal error. At the same समय, some
		 * devices may not वापस GoodCRC under some circumstances,
		 * so we need to retry.
		 */
		अगर (port->vdm_retries < 3) अणु
			tcpm_log(port, "VDM Tx error, retry");
			port->vdm_retries++;
			port->vdm_state = VDM_STATE_READY;
			अगर (PD_VDO_SVDM(vकरो_hdr) && PD_VDO_CMDT(vकरो_hdr) == CMDT_INIT)
				tcpm_ams_finish(port);
		पूर्ण अन्यथा अणु
			tcpm_ams_finish(port);
		पूर्ण
		अवरोध;
	हाल VDM_STATE_SEND_MESSAGE:
		/* Prepare and send VDM */
		स_रखो(&msg, 0, माप(msg));
		msg.header = PD_HEADER_LE(PD_DATA_VENDOR_DEF,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id, port->vकरो_count);
		क्रम (i = 0; i < port->vकरो_count; i++)
			msg.payload[i] = cpu_to_le32(port->vकरो_data[i]);
		res = tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
		अगर (res < 0) अणु
			port->vdm_state = VDM_STATE_ERR_SEND;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ समयout;

			port->vdm_retries = 0;
			port->vdm_state = VDM_STATE_BUSY;
			समयout = vdm_पढ़ोy_समयout(vकरो_hdr);
			mod_vdm_delayed_work(port, समयout);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम vdm_state_machine_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा tcpm_port *port = container_of(work, काष्ठा tcpm_port, vdm_state_machine);
	क्रमागत vdm_states prev_state;

	mutex_lock(&port->lock);

	/*
	 * Continue running as दीर्घ as the port is not busy and there was
	 * a state change.
	 */
	करो अणु
		prev_state = port->vdm_state;
		vdm_run_state_machine(port);
	पूर्ण जबतक (port->vdm_state != prev_state &&
		 port->vdm_state != VDM_STATE_BUSY &&
		 port->vdm_state != VDM_STATE_SEND_MESSAGE);

	अगर (port->vdm_state < VDM_STATE_READY)
		port->vdm_sm_running = false;

	mutex_unlock(&port->lock);
पूर्ण

क्रमागत pकरो_err अणु
	PDO_NO_ERR,
	PDO_ERR_NO_VSAFE5V,
	PDO_ERR_VSAFE5V_NOT_FIRST,
	PDO_ERR_PDO_TYPE_NOT_IN_ORDER,
	PDO_ERR_FIXED_NOT_SORTED,
	PDO_ERR_VARIABLE_BATT_NOT_SORTED,
	PDO_ERR_DUPE_PDO,
	PDO_ERR_PPS_APDO_NOT_SORTED,
	PDO_ERR_DUPE_PPS_APDO,
पूर्ण;

अटल स्थिर अक्षर * स्थिर pकरो_err_msg[] = अणु
	[PDO_ERR_NO_VSAFE5V] =
	" err: source/sink caps should atleast have vSafe5V",
	[PDO_ERR_VSAFE5V_NOT_FIRST] =
	" err: vSafe5V Fixed Supply Object Shall always be the first object",
	[PDO_ERR_PDO_TYPE_NOT_IN_ORDER] =
	" err: PDOs should be in the following order: Fixed; Battery; Variable",
	[PDO_ERR_FIXED_NOT_SORTED] =
	" err: Fixed supply pdos should be in increasing order of their fixed voltage",
	[PDO_ERR_VARIABLE_BATT_NOT_SORTED] =
	" err: Variable/Battery supply pdos should be in increasing order of their minimum voltage",
	[PDO_ERR_DUPE_PDO] =
	" err: Variable/Batt supply pdos cannot have same min/max voltage",
	[PDO_ERR_PPS_APDO_NOT_SORTED] =
	" err: Programmable power supply apdos should be in increasing order of their maximum voltage",
	[PDO_ERR_DUPE_PPS_APDO] =
	" err: Programmable power supply apdos cannot have same min/max voltage and max current",
पूर्ण;

अटल क्रमागत pकरो_err tcpm_caps_err(काष्ठा tcpm_port *port, स्थिर u32 *pकरो,
				  अचिन्हित पूर्णांक nr_pकरो)
अणु
	अचिन्हित पूर्णांक i;

	/* Should at least contain vSafe5v */
	अगर (nr_pकरो < 1)
		वापस PDO_ERR_NO_VSAFE5V;

	/* The vSafe5V Fixed Supply Object Shall always be the first object */
	अगर (pकरो_type(pकरो[0]) != PDO_TYPE_FIXED ||
	    pकरो_fixed_voltage(pकरो[0]) != VSAFE5V)
		वापस PDO_ERR_VSAFE5V_NOT_FIRST;

	क्रम (i = 1; i < nr_pकरो; i++) अणु
		अगर (pकरो_type(pकरो[i]) < pकरो_type(pकरो[i - 1])) अणु
			वापस PDO_ERR_PDO_TYPE_NOT_IN_ORDER;
		पूर्ण अन्यथा अगर (pकरो_type(pकरो[i]) == pकरो_type(pकरो[i - 1])) अणु
			क्रमागत pd_pकरो_type type = pकरो_type(pकरो[i]);

			चयन (type) अणु
			/*
			 * The reमुख्यing Fixed Supply Objects, अगर
			 * present, shall be sent in voltage order;
			 * lowest to highest.
			 */
			हाल PDO_TYPE_FIXED:
				अगर (pकरो_fixed_voltage(pकरो[i]) <=
				    pकरो_fixed_voltage(pकरो[i - 1]))
					वापस PDO_ERR_FIXED_NOT_SORTED;
				अवरोध;
			/*
			 * The Battery Supply Objects and Variable
			 * supply, अगर present shall be sent in Minimum
			 * Voltage order; lowest to highest.
			 */
			हाल PDO_TYPE_VAR:
			हाल PDO_TYPE_BATT:
				अगर (pकरो_min_voltage(pकरो[i]) <
				    pकरो_min_voltage(pकरो[i - 1]))
					वापस PDO_ERR_VARIABLE_BATT_NOT_SORTED;
				अन्यथा अगर ((pकरो_min_voltage(pकरो[i]) ==
					  pकरो_min_voltage(pकरो[i - 1])) &&
					 (pकरो_max_voltage(pकरो[i]) ==
					  pकरो_max_voltage(pकरो[i - 1])))
					वापस PDO_ERR_DUPE_PDO;
				अवरोध;
			/*
			 * The Programmable Power Supply APDOs, अगर present,
			 * shall be sent in Maximum Voltage order;
			 * lowest to highest.
			 */
			हाल PDO_TYPE_APDO:
				अगर (pकरो_apकरो_type(pकरो[i]) != APDO_TYPE_PPS)
					अवरोध;

				अगर (pकरो_pps_apकरो_max_voltage(pकरो[i]) <
				    pकरो_pps_apकरो_max_voltage(pकरो[i - 1]))
					वापस PDO_ERR_PPS_APDO_NOT_SORTED;
				अन्यथा अगर (pकरो_pps_apकरो_min_voltage(pकरो[i]) ==
					  pकरो_pps_apकरो_min_voltage(pकरो[i - 1]) &&
					 pकरो_pps_apकरो_max_voltage(pकरो[i]) ==
					  pकरो_pps_apकरो_max_voltage(pकरो[i - 1]) &&
					 pकरो_pps_apकरो_max_current(pकरो[i]) ==
					  pकरो_pps_apकरो_max_current(pकरो[i - 1]))
					वापस PDO_ERR_DUPE_PPS_APDO;
				अवरोध;
			शेष:
				tcpm_log_क्रमce(port, " Unknown pdo type");
			पूर्ण
		पूर्ण
	पूर्ण

	वापस PDO_NO_ERR;
पूर्ण

अटल पूर्णांक tcpm_validate_caps(काष्ठा tcpm_port *port, स्थिर u32 *pकरो,
			      अचिन्हित पूर्णांक nr_pकरो)
अणु
	क्रमागत pकरो_err err_index = tcpm_caps_err(port, pकरो, nr_pकरो);

	अगर (err_index != PDO_NO_ERR) अणु
		tcpm_log_क्रमce(port, " %s", pकरो_err_msg[err_index]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_alपंचांगode_enter(काष्ठा typec_alपंचांगode *alपंचांगode, u32 *vकरो)
अणु
	काष्ठा tcpm_port *port = typec_alपंचांगode_get_drvdata(alपंचांगode);
	पूर्णांक svdm_version;
	u32 header;

	svdm_version = typec_get_negotiated_svdm_version(port->typec_port);
	अगर (svdm_version < 0)
		वापस svdm_version;

	header = VDO(alपंचांगode->svid, vकरो ? 2 : 1, svdm_version, CMD_ENTER_MODE);
	header |= VDO_OPOS(alपंचांगode->mode);

	tcpm_queue_vdm_unlocked(port, header, vकरो, vकरो ? 1 : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_alपंचांगode_निकास(काष्ठा typec_alपंचांगode *alपंचांगode)
अणु
	काष्ठा tcpm_port *port = typec_alपंचांगode_get_drvdata(alपंचांगode);
	पूर्णांक svdm_version;
	u32 header;

	svdm_version = typec_get_negotiated_svdm_version(port->typec_port);
	अगर (svdm_version < 0)
		वापस svdm_version;

	header = VDO(alपंचांगode->svid, 1, svdm_version, CMD_EXIT_MODE);
	header |= VDO_OPOS(alपंचांगode->mode);

	tcpm_queue_vdm_unlocked(port, header, शून्य, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_alपंचांगode_vdm(काष्ठा typec_alपंचांगode *alपंचांगode,
			    u32 header, स्थिर u32 *data, पूर्णांक count)
अणु
	काष्ठा tcpm_port *port = typec_alपंचांगode_get_drvdata(alपंचांगode);

	tcpm_queue_vdm_unlocked(port, header, data, count - 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा typec_alपंचांगode_ops tcpm_alपंचांगode_ops = अणु
	.enter = tcpm_alपंचांगode_enter,
	.निकास = tcpm_alपंचांगode_निकास,
	.vdm = tcpm_alपंचांगode_vdm,
पूर्ण;

/*
 * PD (data, control) command handling functions
 */
अटल अंतरभूत क्रमागत tcpm_state पढ़ोy_state(काष्ठा tcpm_port *port)
अणु
	अगर (port->pwr_role == TYPEC_SOURCE)
		वापस SRC_READY;
	अन्यथा
		वापस SNK_READY;
पूर्ण

अटल पूर्णांक tcpm_pd_send_control(काष्ठा tcpm_port *port,
				क्रमागत pd_ctrl_msg_type type);

अटल व्योम tcpm_handle_alert(काष्ठा tcpm_port *port, स्थिर __le32 *payload,
			      पूर्णांक cnt)
अणु
	u32 p0 = le32_to_cpu(payload[0]);
	अचिन्हित पूर्णांक type = usb_pd_aकरो_type(p0);

	अगर (!type) अणु
		tcpm_log(port, "Alert message received with no type");
		tcpm_queue_message(port, PD_MSG_CTRL_NOT_SUPP);
		वापस;
	पूर्ण

	/* Just handling non-battery alerts क्रम now */
	अगर (!(type & USB_PD_ADO_TYPE_BATT_STATUS_CHANGE)) अणु
		अगर (port->pwr_role == TYPEC_SOURCE) अणु
			port->upcoming_state = GET_STATUS_SEND;
			tcpm_ams_start(port, GETTING_SOURCE_SINK_STATUS);
		पूर्ण अन्यथा अणु
			/*
			 * Do not check SinkTxOk here in हाल the Source करोesn't set its Rp to
			 * SinkTxOk in समय.
			 */
			port->ams = GETTING_SOURCE_SINK_STATUS;
			tcpm_set_state(port, GET_STATUS_SEND, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		tcpm_queue_message(port, PD_MSG_CTRL_NOT_SUPP);
	पूर्ण
पूर्ण

अटल पूर्णांक tcpm_set_स्वतः_vbus_disअक्षरge_threshold(काष्ठा tcpm_port *port,
						  क्रमागत typec_pwr_opmode mode, bool pps_active,
						  u32 requested_vbus_voltage)
अणु
	पूर्णांक ret;

	अगर (!port->tcpc->set_स्वतः_vbus_disअक्षरge_threshold)
		वापस 0;

	ret = port->tcpc->set_स्वतः_vbus_disअक्षरge_threshold(port->tcpc, mode, pps_active,
							    requested_vbus_voltage);
	tcpm_log_क्रमce(port,
		       "set_auto_vbus_discharge_threshold mode:%d pps_active:%c vbus:%u ret:%d",
		       mode, pps_active ? 'y' : 'n', requested_vbus_voltage, ret);

	वापस ret;
पूर्ण

अटल व्योम tcpm_pd_handle_state(काष्ठा tcpm_port *port,
				 क्रमागत tcpm_state state,
				 क्रमागत tcpm_ams ams,
				 अचिन्हित पूर्णांक delay_ms)
अणु
	चयन (port->state) अणु
	हाल SRC_READY:
	हाल SNK_READY:
		port->ams = ams;
		tcpm_set_state(port, state, delay_ms);
		अवरोध;
	/* 8.3.3.4.1.1 and 6.8.1 घातer transitioning */
	हाल SNK_TRANSITION_SINK:
	हाल SNK_TRANSITION_SINK_VBUS:
	हाल SRC_TRANSITION_SUPPLY:
		tcpm_set_state(port, HARD_RESET_SEND, 0);
		अवरोध;
	शेष:
		अगर (!tcpm_ams_पूर्णांकerruptible(port)) अणु
			tcpm_set_state(port, port->pwr_role == TYPEC_SOURCE ?
				       SRC_SOFT_RESET_WAIT_SNK_TX :
				       SNK_SOFT_RESET,
				       0);
		पूर्ण अन्यथा अणु
			/* process the Message 6.8.1 */
			port->upcoming_state = state;
			port->next_ams = ams;
			tcpm_set_state(port, पढ़ोy_state(port), delay_ms);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcpm_pd_handle_msg(काष्ठा tcpm_port *port,
			       क्रमागत pd_msg_request message,
			       क्रमागत tcpm_ams ams)
अणु
	चयन (port->state) अणु
	हाल SRC_READY:
	हाल SNK_READY:
		port->ams = ams;
		tcpm_queue_message(port, message);
		अवरोध;
	/* PD 3.0 Spec 8.3.3.4.1.1 and 6.8.1 */
	हाल SNK_TRANSITION_SINK:
	हाल SNK_TRANSITION_SINK_VBUS:
	हाल SRC_TRANSITION_SUPPLY:
		tcpm_set_state(port, HARD_RESET_SEND, 0);
		अवरोध;
	शेष:
		अगर (!tcpm_ams_पूर्णांकerruptible(port)) अणु
			tcpm_set_state(port, port->pwr_role == TYPEC_SOURCE ?
				       SRC_SOFT_RESET_WAIT_SNK_TX :
				       SNK_SOFT_RESET,
				       0);
		पूर्ण अन्यथा अणु
			port->next_ams = ams;
			tcpm_set_state(port, पढ़ोy_state(port), 0);
			/* 6.8.1 process the Message */
			tcpm_queue_message(port, message);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcpm_pd_data_request(काष्ठा tcpm_port *port,
				 स्थिर काष्ठा pd_message *msg)
अणु
	क्रमागत pd_data_msg_type type = pd_header_type_le(msg->header);
	अचिन्हित पूर्णांक cnt = pd_header_cnt_le(msg->header);
	अचिन्हित पूर्णांक rev = pd_header_rev_le(msg->header);
	अचिन्हित पूर्णांक i;
	क्रमागत frs_typec_current partner_frs_current;
	bool frs_enable;
	पूर्णांक ret;

	अगर (tcpm_vdm_ams(port) && type != PD_DATA_VENDOR_DEF) अणु
		port->vdm_state = VDM_STATE_ERR_BUSY;
		tcpm_ams_finish(port);
		mod_vdm_delayed_work(port, 0);
	पूर्ण

	चयन (type) अणु
	हाल PD_DATA_SOURCE_CAP:
		क्रम (i = 0; i < cnt; i++)
			port->source_caps[i] = le32_to_cpu(msg->payload[i]);

		port->nr_source_caps = cnt;

		tcpm_log_source_caps(port);

		tcpm_validate_caps(port, port->source_caps,
				   port->nr_source_caps);

		/*
		 * Adjust revision in subsequent message headers, as required,
		 * to comply with 6.2.1.1.5 of the USB PD 3.0 spec. We करोn't
		 * support Rev 1.0 so just करो nothing in that scenario.
		 */
		अगर (rev == PD_REV10) अणु
			अगर (port->ams == GET_SOURCE_CAPABILITIES)
				tcpm_ams_finish(port);
			अवरोध;
		पूर्ण

		अगर (rev < PD_MAX_REV)
			port->negotiated_rev = rev;

		अगर (port->pwr_role == TYPEC_SOURCE) अणु
			अगर (port->ams == GET_SOURCE_CAPABILITIES)
				tcpm_pd_handle_state(port, SRC_READY, NONE_AMS, 0);
			/* Unexpected Source Capabilities */
			अन्यथा
				tcpm_pd_handle_msg(port,
						   port->negotiated_rev < PD_REV30 ?
						   PD_MSG_CTRL_REJECT :
						   PD_MSG_CTRL_NOT_SUPP,
						   NONE_AMS);
		पूर्ण अन्यथा अगर (port->state == SNK_WAIT_CAPABILITIES) अणु
		/*
		 * This message may be received even अगर VBUS is not
		 * present. This is quite unexpected; see USB PD
		 * specअगरication, sections 8.3.3.6.3.1 and 8.3.3.6.3.2.
		 * However, at the same समय, we must be पढ़ोy to
		 * receive this message and respond to it 15ms after
		 * receiving PS_RDY during घातer swap operations, no matter
		 * अगर VBUS is available or not (USB PD specअगरication,
		 * section 6.5.9.2).
		 * So we need to accept the message either way,
		 * but be prepared to keep रुकोing क्रम VBUS after it was
		 * handled.
		 */
			port->ams = POWER_NEGOTIATION;
			port->in_ams = true;
			tcpm_set_state(port, SNK_NEGOTIATE_CAPABILITIES, 0);
		पूर्ण अन्यथा अणु
			अगर (port->ams == GET_SOURCE_CAPABILITIES)
				tcpm_ams_finish(port);
			tcpm_pd_handle_state(port, SNK_NEGOTIATE_CAPABILITIES,
					     POWER_NEGOTIATION, 0);
		पूर्ण
		अवरोध;
	हाल PD_DATA_REQUEST:
		/*
		 * Adjust revision in subsequent message headers, as required,
		 * to comply with 6.2.1.1.5 of the USB PD 3.0 spec. We करोn't
		 * support Rev 1.0 so just reject in that scenario.
		 */
		अगर (rev == PD_REV10) अणु
			tcpm_pd_handle_msg(port,
					   port->negotiated_rev < PD_REV30 ?
					   PD_MSG_CTRL_REJECT :
					   PD_MSG_CTRL_NOT_SUPP,
					   NONE_AMS);
			अवरोध;
		पूर्ण

		अगर (rev < PD_MAX_REV)
			port->negotiated_rev = rev;

		अगर (port->pwr_role != TYPEC_SOURCE || cnt != 1) अणु
			tcpm_pd_handle_msg(port,
					   port->negotiated_rev < PD_REV30 ?
					   PD_MSG_CTRL_REJECT :
					   PD_MSG_CTRL_NOT_SUPP,
					   NONE_AMS);
			अवरोध;
		पूर्ण

		port->sink_request = le32_to_cpu(msg->payload[0]);

		अगर (port->vdm_sm_running && port->explicit_contract) अणु
			tcpm_pd_handle_msg(port, PD_MSG_CTRL_WAIT, port->ams);
			अवरोध;
		पूर्ण

		अगर (port->state == SRC_SEND_CAPABILITIES)
			tcpm_set_state(port, SRC_NEGOTIATE_CAPABILITIES, 0);
		अन्यथा
			tcpm_pd_handle_state(port, SRC_NEGOTIATE_CAPABILITIES,
					     POWER_NEGOTIATION, 0);
		अवरोध;
	हाल PD_DATA_SINK_CAP:
		/* We करोn't करो anything with this at the moment... */
		क्रम (i = 0; i < cnt; i++)
			port->sink_caps[i] = le32_to_cpu(msg->payload[i]);

		partner_frs_current = (port->sink_caps[0] & PDO_FIXED_FRS_CURR_MASK) >>
			PDO_FIXED_FRS_CURR_SHIFT;
		frs_enable = partner_frs_current && (partner_frs_current <=
						     port->new_source_frs_current);
		tcpm_log(port,
			 "Port partner FRS capable partner_frs_current:%u port_frs_current:%u enable:%c",
			 partner_frs_current, port->new_source_frs_current, frs_enable ? 'y' : 'n');
		अगर (frs_enable) अणु
			ret  = port->tcpc->enable_frs(port->tcpc, true);
			tcpm_log(port, "Enable FRS %s, ret:%d\n", ret ? "fail" : "success", ret);
		पूर्ण

		port->nr_sink_caps = cnt;
		port->sink_cap_करोne = true;
		अगर (port->ams == GET_SINK_CAPABILITIES)
			tcpm_set_state(port, पढ़ोy_state(port), 0);
		/* Unexpected Sink Capabilities */
		अन्यथा
			tcpm_pd_handle_msg(port,
					   port->negotiated_rev < PD_REV30 ?
					   PD_MSG_CTRL_REJECT :
					   PD_MSG_CTRL_NOT_SUPP,
					   NONE_AMS);
		अवरोध;
	हाल PD_DATA_VENDOR_DEF:
		अगर (tcpm_vdm_ams(port) || port->nr_snk_vकरो)
			tcpm_handle_vdm_request(port, msg->payload, cnt);
		अन्यथा अगर (port->negotiated_rev > PD_REV20)
			tcpm_pd_handle_msg(port, PD_MSG_CTRL_NOT_SUPP, NONE_AMS);
		अवरोध;
	हाल PD_DATA_BIST:
		port->bist_request = le32_to_cpu(msg->payload[0]);
		tcpm_pd_handle_state(port, BIST_RX, BIST, 0);
		अवरोध;
	हाल PD_DATA_ALERT:
		अगर (port->state != SRC_READY && port->state != SNK_READY)
			tcpm_pd_handle_state(port, port->pwr_role == TYPEC_SOURCE ?
					     SRC_SOFT_RESET_WAIT_SNK_TX : SNK_SOFT_RESET,
					     NONE_AMS, 0);
		अन्यथा
			tcpm_handle_alert(port, msg->payload, cnt);
		अवरोध;
	हाल PD_DATA_BATT_STATUS:
	हाल PD_DATA_GET_COUNTRY_INFO:
		/* Currently unsupported */
		tcpm_pd_handle_msg(port, port->negotiated_rev < PD_REV30 ?
				   PD_MSG_CTRL_REJECT :
				   PD_MSG_CTRL_NOT_SUPP,
				   NONE_AMS);
		अवरोध;
	शेष:
		tcpm_pd_handle_msg(port, port->negotiated_rev < PD_REV30 ?
				   PD_MSG_CTRL_REJECT :
				   PD_MSG_CTRL_NOT_SUPP,
				   NONE_AMS);
		tcpm_log(port, "Unrecognized data message type %#x", type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcpm_pps_complete(काष्ठा tcpm_port *port, पूर्णांक result)
अणु
	अगर (port->pps_pending) अणु
		port->pps_status = result;
		port->pps_pending = false;
		complete(&port->pps_complete);
	पूर्ण
पूर्ण

अटल व्योम tcpm_pd_ctrl_request(काष्ठा tcpm_port *port,
				 स्थिर काष्ठा pd_message *msg)
अणु
	क्रमागत pd_ctrl_msg_type type = pd_header_type_le(msg->header);
	क्रमागत tcpm_state next_state;

	/*
	 * Stop VDM state machine अगर पूर्णांकerrupted by other Messages जबतक NOT_SUPP is allowed in
	 * VDM AMS अगर रुकोing क्रम VDM responses and will be handled later.
	 */
	अगर (tcpm_vdm_ams(port) && type != PD_CTRL_NOT_SUPP && type != PD_CTRL_GOOD_CRC) अणु
		port->vdm_state = VDM_STATE_ERR_BUSY;
		tcpm_ams_finish(port);
		mod_vdm_delayed_work(port, 0);
	पूर्ण

	चयन (type) अणु
	हाल PD_CTRL_GOOD_CRC:
	हाल PD_CTRL_PING:
		अवरोध;
	हाल PD_CTRL_GET_SOURCE_CAP:
		tcpm_pd_handle_msg(port, PD_MSG_DATA_SOURCE_CAP, GET_SOURCE_CAPABILITIES);
		अवरोध;
	हाल PD_CTRL_GET_SINK_CAP:
		tcpm_pd_handle_msg(port, PD_MSG_DATA_SINK_CAP, GET_SINK_CAPABILITIES);
		अवरोध;
	हाल PD_CTRL_GOTO_MIN:
		अवरोध;
	हाल PD_CTRL_PS_RDY:
		चयन (port->state) अणु
		हाल SNK_TRANSITION_SINK:
			अगर (port->vbus_present) अणु
				tcpm_set_current_limit(port,
						       port->req_current_limit,
						       port->req_supply_voltage);
				port->explicit_contract = true;
				tcpm_set_स्वतः_vbus_disअक्षरge_threshold(port,
								       TYPEC_PWR_MODE_PD,
								       port->pps_data.active,
								       port->supply_voltage);
				/* Set VDM running flag ASAP */
				अगर (port->data_role == TYPEC_HOST &&
				    port->send_discover)
					port->vdm_sm_running = true;
				tcpm_set_state(port, SNK_READY, 0);
			पूर्ण अन्यथा अणु
				/*
				 * Seen after घातer swap. Keep रुकोing क्रम VBUS
				 * in a transitional state.
				 */
				tcpm_set_state(port,
					       SNK_TRANSITION_SINK_VBUS, 0);
			पूर्ण
			अवरोध;
		हाल PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED:
			tcpm_set_state(port, PR_SWAP_SRC_SNK_SINK_ON, 0);
			अवरोध;
		हाल PR_SWAP_SNK_SRC_SINK_OFF:
			tcpm_set_state(port, PR_SWAP_SNK_SRC_SOURCE_ON, 0);
			अवरोध;
		हाल VCONN_SWAP_WAIT_FOR_VCONN:
			tcpm_set_state(port, VCONN_SWAP_TURN_OFF_VCONN, 0);
			अवरोध;
		हाल FR_SWAP_SNK_SRC_TRANSITION_TO_OFF:
			tcpm_set_state(port, FR_SWAP_SNK_SRC_NEW_SINK_READY, 0);
			अवरोध;
		शेष:
			tcpm_pd_handle_state(port,
					     port->pwr_role == TYPEC_SOURCE ?
					     SRC_SOFT_RESET_WAIT_SNK_TX :
					     SNK_SOFT_RESET,
					     NONE_AMS, 0);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PD_CTRL_REJECT:
	हाल PD_CTRL_WAIT:
	हाल PD_CTRL_NOT_SUPP:
		चयन (port->state) अणु
		हाल SNK_NEGOTIATE_CAPABILITIES:
			/* USB PD specअगरication, Figure 8-43 */
			अगर (port->explicit_contract) अणु
				next_state = SNK_READY;
				अगर (port->data_role == TYPEC_HOST &&
				    port->send_discover)
					port->vdm_sm_running = true;
			पूर्ण अन्यथा अणु
				next_state = SNK_WAIT_CAPABILITIES;
			पूर्ण
			tcpm_set_state(port, next_state, 0);
			अवरोध;
		हाल SNK_NEGOTIATE_PPS_CAPABILITIES:
			/* Revert data back from any requested PPS updates */
			port->pps_data.req_out_volt = port->supply_voltage;
			port->pps_data.req_op_curr = port->current_limit;
			port->pps_status = (type == PD_CTRL_WAIT ?
					    -EAGAIN : -EOPNOTSUPP);

			अगर (port->data_role == TYPEC_HOST &&
			    port->send_discover)
				port->vdm_sm_running = true;

			tcpm_set_state(port, SNK_READY, 0);
			अवरोध;
		हाल DR_SWAP_SEND:
			port->swap_status = (type == PD_CTRL_WAIT ?
					     -EAGAIN : -EOPNOTSUPP);
			tcpm_set_state(port, DR_SWAP_CANCEL, 0);
			अवरोध;
		हाल PR_SWAP_SEND:
			port->swap_status = (type == PD_CTRL_WAIT ?
					     -EAGAIN : -EOPNOTSUPP);
			tcpm_set_state(port, PR_SWAP_CANCEL, 0);
			अवरोध;
		हाल VCONN_SWAP_SEND:
			port->swap_status = (type == PD_CTRL_WAIT ?
					     -EAGAIN : -EOPNOTSUPP);
			tcpm_set_state(port, VCONN_SWAP_CANCEL, 0);
			अवरोध;
		हाल FR_SWAP_SEND:
			tcpm_set_state(port, FR_SWAP_CANCEL, 0);
			अवरोध;
		हाल GET_SINK_CAP:
			port->sink_cap_करोne = true;
			tcpm_set_state(port, पढ़ोy_state(port), 0);
			अवरोध;
		हाल SRC_READY:
		हाल SNK_READY:
			अगर (port->vdm_state > VDM_STATE_READY) अणु
				port->vdm_state = VDM_STATE_DONE;
				अगर (tcpm_vdm_ams(port))
					tcpm_ams_finish(port);
				mod_vdm_delayed_work(port, 0);
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			tcpm_pd_handle_state(port,
					     port->pwr_role == TYPEC_SOURCE ?
					     SRC_SOFT_RESET_WAIT_SNK_TX :
					     SNK_SOFT_RESET,
					     NONE_AMS, 0);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PD_CTRL_ACCEPT:
		चयन (port->state) अणु
		हाल SNK_NEGOTIATE_CAPABILITIES:
			port->pps_data.active = false;
			tcpm_set_state(port, SNK_TRANSITION_SINK, 0);
			अवरोध;
		हाल SNK_NEGOTIATE_PPS_CAPABILITIES:
			port->pps_data.active = true;
			port->pps_data.min_volt = port->pps_data.req_min_volt;
			port->pps_data.max_volt = port->pps_data.req_max_volt;
			port->pps_data.max_curr = port->pps_data.req_max_curr;
			port->req_supply_voltage = port->pps_data.req_out_volt;
			port->req_current_limit = port->pps_data.req_op_curr;
			घातer_supply_changed(port->psy);
			tcpm_set_state(port, SNK_TRANSITION_SINK, 0);
			अवरोध;
		हाल SOFT_RESET_SEND:
			अगर (port->ams == SOFT_RESET_AMS)
				tcpm_ams_finish(port);
			अगर (port->pwr_role == TYPEC_SOURCE) अणु
				port->upcoming_state = SRC_SEND_CAPABILITIES;
				tcpm_ams_start(port, POWER_NEGOTIATION);
			पूर्ण अन्यथा अणु
				tcpm_set_state(port, SNK_WAIT_CAPABILITIES, 0);
			पूर्ण
			अवरोध;
		हाल DR_SWAP_SEND:
			अगर (port->data_role == TYPEC_DEVICE &&
			    port->send_discover)
				port->vdm_sm_running = true;

			tcpm_set_state(port, DR_SWAP_CHANGE_DR, 0);
			अवरोध;
		हाल PR_SWAP_SEND:
			tcpm_set_state(port, PR_SWAP_START, 0);
			अवरोध;
		हाल VCONN_SWAP_SEND:
			tcpm_set_state(port, VCONN_SWAP_START, 0);
			अवरोध;
		हाल FR_SWAP_SEND:
			tcpm_set_state(port, FR_SWAP_SNK_SRC_TRANSITION_TO_OFF, 0);
			अवरोध;
		शेष:
			tcpm_pd_handle_state(port,
					     port->pwr_role == TYPEC_SOURCE ?
					     SRC_SOFT_RESET_WAIT_SNK_TX :
					     SNK_SOFT_RESET,
					     NONE_AMS, 0);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PD_CTRL_SOFT_RESET:
		port->ams = SOFT_RESET_AMS;
		tcpm_set_state(port, SOFT_RESET, 0);
		अवरोध;
	हाल PD_CTRL_DR_SWAP:
		/*
		 * XXX
		 * 6.3.9: If an alternate mode is active, a request to swap
		 * alternate modes shall trigger a port reset.
		 */
		अगर (port->typec_caps.data != TYPEC_PORT_DRD) अणु
			tcpm_pd_handle_msg(port,
					   port->negotiated_rev < PD_REV30 ?
					   PD_MSG_CTRL_REJECT :
					   PD_MSG_CTRL_NOT_SUPP,
					   NONE_AMS);
		पूर्ण अन्यथा अणु
			अगर (port->vdm_sm_running) अणु
				tcpm_queue_message(port, PD_MSG_CTRL_WAIT);
				अवरोध;
			पूर्ण

			tcpm_pd_handle_state(port, DR_SWAP_ACCEPT, DATA_ROLE_SWAP, 0);
		पूर्ण
		अवरोध;
	हाल PD_CTRL_PR_SWAP:
		अगर (port->port_type != TYPEC_PORT_DRP) अणु
			tcpm_pd_handle_msg(port,
					   port->negotiated_rev < PD_REV30 ?
					   PD_MSG_CTRL_REJECT :
					   PD_MSG_CTRL_NOT_SUPP,
					   NONE_AMS);
		पूर्ण अन्यथा अणु
			अगर (port->vdm_sm_running) अणु
				tcpm_queue_message(port, PD_MSG_CTRL_WAIT);
				अवरोध;
			पूर्ण

			tcpm_pd_handle_state(port, PR_SWAP_ACCEPT, POWER_ROLE_SWAP, 0);
		पूर्ण
		अवरोध;
	हाल PD_CTRL_VCONN_SWAP:
		अगर (port->vdm_sm_running) अणु
			tcpm_queue_message(port, PD_MSG_CTRL_WAIT);
			अवरोध;
		पूर्ण

		tcpm_pd_handle_state(port, VCONN_SWAP_ACCEPT, VCONN_SWAP, 0);
		अवरोध;
	हाल PD_CTRL_GET_SOURCE_CAP_EXT:
	हाल PD_CTRL_GET_STATUS:
	हाल PD_CTRL_FR_SWAP:
	हाल PD_CTRL_GET_PPS_STATUS:
	हाल PD_CTRL_GET_COUNTRY_CODES:
		/* Currently not supported */
		tcpm_pd_handle_msg(port,
				   port->negotiated_rev < PD_REV30 ?
				   PD_MSG_CTRL_REJECT :
				   PD_MSG_CTRL_NOT_SUPP,
				   NONE_AMS);
		अवरोध;
	शेष:
		tcpm_pd_handle_msg(port,
				   port->negotiated_rev < PD_REV30 ?
				   PD_MSG_CTRL_REJECT :
				   PD_MSG_CTRL_NOT_SUPP,
				   NONE_AMS);
		tcpm_log(port, "Unrecognized ctrl message type %#x", type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcpm_pd_ext_msg_request(काष्ठा tcpm_port *port,
				    स्थिर काष्ठा pd_message *msg)
अणु
	क्रमागत pd_ext_msg_type type = pd_header_type_le(msg->header);
	अचिन्हित पूर्णांक data_size = pd_ext_header_data_size_le(msg->ext_msg.header);

	/* stopping VDM state machine अगर पूर्णांकerrupted by other Messages */
	अगर (tcpm_vdm_ams(port)) अणु
		port->vdm_state = VDM_STATE_ERR_BUSY;
		tcpm_ams_finish(port);
		mod_vdm_delayed_work(port, 0);
	पूर्ण

	अगर (!(le16_to_cpu(msg->ext_msg.header) & PD_EXT_HDR_CHUNKED)) अणु
		tcpm_pd_handle_msg(port, PD_MSG_CTRL_NOT_SUPP, NONE_AMS);
		tcpm_log(port, "Unchunked extended messages unsupported");
		वापस;
	पूर्ण

	अगर (data_size > PD_EXT_MAX_CHUNK_DATA) अणु
		tcpm_pd_handle_state(port, CHUNK_NOT_SUPP, NONE_AMS, PD_T_CHUNK_NOT_SUPP);
		tcpm_log(port, "Chunk handling not yet supported");
		वापस;
	पूर्ण

	चयन (type) अणु
	हाल PD_EXT_STATUS:
	हाल PD_EXT_PPS_STATUS:
		अगर (port->ams == GETTING_SOURCE_SINK_STATUS) अणु
			tcpm_ams_finish(port);
			tcpm_set_state(port, पढ़ोy_state(port), 0);
		पूर्ण अन्यथा अणु
			/* unexpected Status or PPS_Status Message */
			tcpm_pd_handle_state(port, port->pwr_role == TYPEC_SOURCE ?
					     SRC_SOFT_RESET_WAIT_SNK_TX : SNK_SOFT_RESET,
					     NONE_AMS, 0);
		पूर्ण
		अवरोध;
	हाल PD_EXT_SOURCE_CAP_EXT:
	हाल PD_EXT_GET_BATT_CAP:
	हाल PD_EXT_GET_BATT_STATUS:
	हाल PD_EXT_BATT_CAP:
	हाल PD_EXT_GET_MANUFACTURER_INFO:
	हाल PD_EXT_MANUFACTURER_INFO:
	हाल PD_EXT_SECURITY_REQUEST:
	हाल PD_EXT_SECURITY_RESPONSE:
	हाल PD_EXT_FW_UPDATE_REQUEST:
	हाल PD_EXT_FW_UPDATE_RESPONSE:
	हाल PD_EXT_COUNTRY_INFO:
	हाल PD_EXT_COUNTRY_CODES:
		tcpm_pd_handle_msg(port, PD_MSG_CTRL_NOT_SUPP, NONE_AMS);
		अवरोध;
	शेष:
		tcpm_pd_handle_msg(port, PD_MSG_CTRL_NOT_SUPP, NONE_AMS);
		tcpm_log(port, "Unrecognized extended message type %#x", type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcpm_pd_rx_handler(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा pd_rx_event *event = container_of(work,
						 काष्ठा pd_rx_event, work);
	स्थिर काष्ठा pd_message *msg = &event->msg;
	अचिन्हित पूर्णांक cnt = pd_header_cnt_le(msg->header);
	काष्ठा tcpm_port *port = event->port;

	mutex_lock(&port->lock);

	tcpm_log(port, "PD RX, header: %#x [%d]", le16_to_cpu(msg->header),
		 port->attached);

	अगर (port->attached) अणु
		क्रमागत pd_ctrl_msg_type type = pd_header_type_le(msg->header);
		अचिन्हित पूर्णांक msgid = pd_header_msgid_le(msg->header);

		/*
		 * USB PD standard, 6.6.1.2:
		 * "... अगर MessageID value in a received Message is the
		 * same as the stored value, the receiver shall वापस a
		 * GoodCRC Message with that MessageID value and drop
		 * the Message (this is a retry of an alपढ़ोy received
		 * Message). Note: this shall not apply to the Soft_Reset
		 * Message which always has a MessageID value of zero."
		 */
		अगर (msgid == port->rx_msgid && type != PD_CTRL_SOFT_RESET)
			जाओ करोne;
		port->rx_msgid = msgid;

		/*
		 * If both ends believe to be DFP/host, we have a data role
		 * mismatch.
		 */
		अगर (!!(le16_to_cpu(msg->header) & PD_HEADER_DATA_ROLE) ==
		    (port->data_role == TYPEC_HOST)) अणु
			tcpm_log(port,
				 "Data role mismatch, initiating error recovery");
			tcpm_set_state(port, ERROR_RECOVERY, 0);
		पूर्ण अन्यथा अणु
			अगर (le16_to_cpu(msg->header) & PD_HEADER_EXT_HDR)
				tcpm_pd_ext_msg_request(port, msg);
			अन्यथा अगर (cnt)
				tcpm_pd_data_request(port, msg);
			अन्यथा
				tcpm_pd_ctrl_request(port, msg);
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&port->lock);
	kमुक्त(event);
पूर्ण

व्योम tcpm_pd_receive(काष्ठा tcpm_port *port, स्थिर काष्ठा pd_message *msg)
अणु
	काष्ठा pd_rx_event *event;

	event = kzalloc(माप(*event), GFP_ATOMIC);
	अगर (!event)
		वापस;

	kthपढ़ो_init_work(&event->work, tcpm_pd_rx_handler);
	event->port = port;
	स_नकल(&event->msg, msg, माप(*msg));
	kthपढ़ो_queue_work(port->wq, &event->work);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_pd_receive);

अटल पूर्णांक tcpm_pd_send_control(काष्ठा tcpm_port *port,
				क्रमागत pd_ctrl_msg_type type)
अणु
	काष्ठा pd_message msg;

	स_रखो(&msg, 0, माप(msg));
	msg.header = PD_HEADER_LE(type, port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 0);

	वापस tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
पूर्ण

/*
 * Send queued message without affecting state.
 * Return true अगर state machine should go back to sleep,
 * false otherwise.
 */
अटल bool tcpm_send_queued_message(काष्ठा tcpm_port *port)
अणु
	क्रमागत pd_msg_request queued_message;
	पूर्णांक ret;

	करो अणु
		queued_message = port->queued_message;
		port->queued_message = PD_MSG_NONE;

		चयन (queued_message) अणु
		हाल PD_MSG_CTRL_WAIT:
			tcpm_pd_send_control(port, PD_CTRL_WAIT);
			अवरोध;
		हाल PD_MSG_CTRL_REJECT:
			tcpm_pd_send_control(port, PD_CTRL_REJECT);
			अवरोध;
		हाल PD_MSG_CTRL_NOT_SUPP:
			tcpm_pd_send_control(port, PD_CTRL_NOT_SUPP);
			अवरोध;
		हाल PD_MSG_DATA_SINK_CAP:
			ret = tcpm_pd_send_sink_caps(port);
			अगर (ret < 0) अणु
				tcpm_log(port, "Unable to send snk caps, ret=%d", ret);
				tcpm_set_state(port, SNK_SOFT_RESET, 0);
			पूर्ण
			tcpm_ams_finish(port);
			अवरोध;
		हाल PD_MSG_DATA_SOURCE_CAP:
			ret = tcpm_pd_send_source_caps(port);
			अगर (ret < 0) अणु
				tcpm_log(port,
					 "Unable to send src caps, ret=%d",
					 ret);
				tcpm_set_state(port, SOFT_RESET_SEND, 0);
			पूर्ण अन्यथा अगर (port->pwr_role == TYPEC_SOURCE) अणु
				tcpm_ams_finish(port);
				tcpm_set_state(port, HARD_RESET_SEND,
					       PD_T_SENDER_RESPONSE);
			पूर्ण अन्यथा अणु
				tcpm_ams_finish(port);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण जबतक (port->queued_message != PD_MSG_NONE);

	अगर (port->delayed_state != INVALID_STATE) अणु
		अगर (kसमय_after(port->delayed_runसमय, kसमय_get())) अणु
			mod_tcpm_delayed_work(port, kसमय_प्रकारo_ms(kसमय_sub(port->delayed_runसमय,
									  kसमय_get())));
			वापस true;
		पूर्ण
		port->delayed_state = INVALID_STATE;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक tcpm_pd_check_request(काष्ठा tcpm_port *port)
अणु
	u32 pकरो, rकरो = port->sink_request;
	अचिन्हित पूर्णांक max, op, pकरो_max, index;
	क्रमागत pd_pकरो_type type;

	index = rकरो_index(rकरो);
	अगर (!index || index > port->nr_src_pकरो)
		वापस -EINVAL;

	pकरो = port->src_pकरो[index - 1];
	type = pकरो_type(pकरो);
	चयन (type) अणु
	हाल PDO_TYPE_FIXED:
	हाल PDO_TYPE_VAR:
		max = rकरो_max_current(rकरो);
		op = rकरो_op_current(rकरो);
		pकरो_max = pकरो_max_current(pकरो);

		अगर (op > pकरो_max)
			वापस -EINVAL;
		अगर (max > pकरो_max && !(rकरो & RDO_CAP_MISMATCH))
			वापस -EINVAL;

		अगर (type == PDO_TYPE_FIXED)
			tcpm_log(port,
				 "Requested %u mV, %u mA for %u / %u mA",
				 pकरो_fixed_voltage(pकरो), pकरो_max, op, max);
		अन्यथा
			tcpm_log(port,
				 "Requested %u -> %u mV, %u mA for %u / %u mA",
				 pकरो_min_voltage(pकरो), pकरो_max_voltage(pकरो),
				 pकरो_max, op, max);
		अवरोध;
	हाल PDO_TYPE_BATT:
		max = rकरो_max_घातer(rकरो);
		op = rकरो_op_घातer(rकरो);
		pकरो_max = pकरो_max_घातer(pकरो);

		अगर (op > pकरो_max)
			वापस -EINVAL;
		अगर (max > pकरो_max && !(rकरो & RDO_CAP_MISMATCH))
			वापस -EINVAL;
		tcpm_log(port,
			 "Requested %u -> %u mV, %u mW for %u / %u mW",
			 pकरो_min_voltage(pकरो), pकरो_max_voltage(pकरो),
			 pकरो_max, op, max);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	port->op_vsafe5v = index == 1;

	वापस 0;
पूर्ण

#घोषणा min_घातer(x, y) min(pकरो_max_घातer(x), pकरो_max_घातer(y))
#घोषणा min_current(x, y) min(pकरो_max_current(x), pकरो_max_current(y))

अटल पूर्णांक tcpm_pd_select_pकरो(काष्ठा tcpm_port *port, पूर्णांक *sink_pकरो,
			      पूर्णांक *src_pकरो)
अणु
	अचिन्हित पूर्णांक i, j, max_src_mv = 0, min_src_mv = 0, max_mw = 0,
		     max_mv = 0, src_mw = 0, src_ma = 0, max_snk_mv = 0,
		     min_snk_mv = 0;
	पूर्णांक ret = -EINVAL;

	port->pps_data.supported = false;
	port->usb_type = POWER_SUPPLY_USB_TYPE_PD;
	घातer_supply_changed(port->psy);

	/*
	 * Select the source PDO providing the most घातer which has a
	 * matchig sink cap.
	 */
	क्रम (i = 0; i < port->nr_source_caps; i++) अणु
		u32 pकरो = port->source_caps[i];
		क्रमागत pd_pकरो_type type = pकरो_type(pकरो);

		चयन (type) अणु
		हाल PDO_TYPE_FIXED:
			max_src_mv = pकरो_fixed_voltage(pकरो);
			min_src_mv = max_src_mv;
			अवरोध;
		हाल PDO_TYPE_BATT:
		हाल PDO_TYPE_VAR:
			max_src_mv = pकरो_max_voltage(pकरो);
			min_src_mv = pकरो_min_voltage(pकरो);
			अवरोध;
		हाल PDO_TYPE_APDO:
			अगर (pकरो_apकरो_type(pकरो) == APDO_TYPE_PPS) अणु
				port->pps_data.supported = true;
				port->usb_type =
					POWER_SUPPLY_USB_TYPE_PD_PPS;
				घातer_supply_changed(port->psy);
			पूर्ण
			जारी;
		शेष:
			tcpm_log(port, "Invalid source PDO type, ignoring");
			जारी;
		पूर्ण

		चयन (type) अणु
		हाल PDO_TYPE_FIXED:
		हाल PDO_TYPE_VAR:
			src_ma = pकरो_max_current(pकरो);
			src_mw = src_ma * min_src_mv / 1000;
			अवरोध;
		हाल PDO_TYPE_BATT:
			src_mw = pकरो_max_घातer(pकरो);
			अवरोध;
		हाल PDO_TYPE_APDO:
			जारी;
		शेष:
			tcpm_log(port, "Invalid source PDO type, ignoring");
			जारी;
		पूर्ण

		क्रम (j = 0; j < port->nr_snk_pकरो; j++) अणु
			pकरो = port->snk_pकरो[j];

			चयन (pकरो_type(pकरो)) अणु
			हाल PDO_TYPE_FIXED:
				max_snk_mv = pकरो_fixed_voltage(pकरो);
				min_snk_mv = max_snk_mv;
				अवरोध;
			हाल PDO_TYPE_BATT:
			हाल PDO_TYPE_VAR:
				max_snk_mv = pकरो_max_voltage(pकरो);
				min_snk_mv = pकरो_min_voltage(pकरो);
				अवरोध;
			हाल PDO_TYPE_APDO:
				जारी;
			शेष:
				tcpm_log(port, "Invalid sink PDO type, ignoring");
				जारी;
			पूर्ण

			अगर (max_src_mv <= max_snk_mv &&
				min_src_mv >= min_snk_mv) अणु
				/* Prefer higher voltages अगर available */
				अगर ((src_mw == max_mw && min_src_mv > max_mv) ||
							src_mw > max_mw) अणु
					*src_pकरो = i;
					*sink_pकरो = j;
					max_mw = src_mw;
					max_mv = min_src_mv;
					ret = 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा min_pps_apकरो_current(x, y)	\
	min(pकरो_pps_apकरो_max_current(x), pकरो_pps_apकरो_max_current(y))

अटल अचिन्हित पूर्णांक tcpm_pd_select_pps_apकरो(काष्ठा tcpm_port *port)
अणु
	अचिन्हित पूर्णांक i, j, max_mw = 0, max_mv = 0;
	अचिन्हित पूर्णांक min_src_mv, max_src_mv, src_ma, src_mw;
	अचिन्हित पूर्णांक min_snk_mv, max_snk_mv;
	अचिन्हित पूर्णांक max_op_mv;
	u32 pकरो, src, snk;
	अचिन्हित पूर्णांक src_pकरो = 0, snk_pकरो = 0;

	/*
	 * Select the source PPS APDO providing the most घातer जबतक staying
	 * within the board's limits. We skip the first PDO as this is always
	 * 5V 3A.
	 */
	क्रम (i = 1; i < port->nr_source_caps; ++i) अणु
		pकरो = port->source_caps[i];

		चयन (pकरो_type(pकरो)) अणु
		हाल PDO_TYPE_APDO:
			अगर (pकरो_apकरो_type(pकरो) != APDO_TYPE_PPS) अणु
				tcpm_log(port, "Not PPS APDO (source), ignoring");
				जारी;
			पूर्ण

			min_src_mv = pकरो_pps_apकरो_min_voltage(pकरो);
			max_src_mv = pकरो_pps_apकरो_max_voltage(pकरो);
			src_ma = pकरो_pps_apकरो_max_current(pकरो);
			src_mw = (src_ma * max_src_mv) / 1000;

			/*
			 * Now search through the sink PDOs to find a matching
			 * PPS APDO. Again skip the first sink PDO as this will
			 * always be 5V 3A.
			 */
			क्रम (j = 1; j < port->nr_snk_pकरो; j++) अणु
				pकरो = port->snk_pकरो[j];

				चयन (pकरो_type(pकरो)) अणु
				हाल PDO_TYPE_APDO:
					अगर (pकरो_apकरो_type(pकरो) != APDO_TYPE_PPS) अणु
						tcpm_log(port,
							 "Not PPS APDO (sink), ignoring");
						जारी;
					पूर्ण

					min_snk_mv =
						pकरो_pps_apकरो_min_voltage(pकरो);
					max_snk_mv =
						pकरो_pps_apकरो_max_voltage(pकरो);
					अवरोध;
				शेष:
					tcpm_log(port,
						 "Not APDO type (sink), ignoring");
					जारी;
				पूर्ण

				अगर (min_src_mv <= max_snk_mv &&
				    max_src_mv >= min_snk_mv) अणु
					max_op_mv = min(max_src_mv, max_snk_mv);
					src_mw = (max_op_mv * src_ma) / 1000;
					/* Prefer higher voltages अगर available */
					अगर ((src_mw == max_mw &&
					     max_op_mv > max_mv) ||
					    src_mw > max_mw) अणु
						src_pकरो = i;
						snk_pकरो = j;
						max_mw = src_mw;
						max_mv = max_op_mv;
					पूर्ण
				पूर्ण
			पूर्ण

			अवरोध;
		शेष:
			tcpm_log(port, "Not APDO type (source), ignoring");
			जारी;
		पूर्ण
	पूर्ण

	अगर (src_pकरो) अणु
		src = port->source_caps[src_pकरो];
		snk = port->snk_pकरो[snk_pकरो];

		port->pps_data.req_min_volt = max(pकरो_pps_apकरो_min_voltage(src),
						  pकरो_pps_apकरो_min_voltage(snk));
		port->pps_data.req_max_volt = min(pकरो_pps_apकरो_max_voltage(src),
						  pकरो_pps_apकरो_max_voltage(snk));
		port->pps_data.req_max_curr = min_pps_apकरो_current(src, snk);
		port->pps_data.req_out_volt = min(port->pps_data.req_max_volt,
						  max(port->pps_data.req_min_volt,
						      port->pps_data.req_out_volt));
		port->pps_data.req_op_curr = min(port->pps_data.req_max_curr,
						 port->pps_data.req_op_curr);
	पूर्ण

	वापस src_pकरो;
पूर्ण

अटल पूर्णांक tcpm_pd_build_request(काष्ठा tcpm_port *port, u32 *rकरो)
अणु
	अचिन्हित पूर्णांक mv, ma, mw, flags;
	अचिन्हित पूर्णांक max_ma, max_mw;
	क्रमागत pd_pकरो_type type;
	u32 pकरो, matching_snk_pकरो;
	पूर्णांक src_pकरो_index = 0;
	पूर्णांक snk_pकरो_index = 0;
	पूर्णांक ret;

	ret = tcpm_pd_select_pकरो(port, &snk_pकरो_index, &src_pकरो_index);
	अगर (ret < 0)
		वापस ret;

	pकरो = port->source_caps[src_pकरो_index];
	matching_snk_pकरो = port->snk_pकरो[snk_pकरो_index];
	type = pकरो_type(pकरो);

	चयन (type) अणु
	हाल PDO_TYPE_FIXED:
		mv = pकरो_fixed_voltage(pकरो);
		अवरोध;
	हाल PDO_TYPE_BATT:
	हाल PDO_TYPE_VAR:
		mv = pकरो_min_voltage(pकरो);
		अवरोध;
	शेष:
		tcpm_log(port, "Invalid PDO selected!");
		वापस -EINVAL;
	पूर्ण

	/* Select maximum available current within the sink pकरो's limit */
	अगर (type == PDO_TYPE_BATT) अणु
		mw = min_घातer(pकरो, matching_snk_pकरो);
		ma = 1000 * mw / mv;
	पूर्ण अन्यथा अणु
		ma = min_current(pकरो, matching_snk_pकरो);
		mw = ma * mv / 1000;
	पूर्ण

	flags = RDO_USB_COMM | RDO_NO_SUSPEND;

	/* Set mismatch bit अगर offered घातer is less than operating घातer */
	max_ma = ma;
	max_mw = mw;
	अगर (mw < port->operating_snk_mw) अणु
		flags |= RDO_CAP_MISMATCH;
		अगर (type == PDO_TYPE_BATT &&
		    (pकरो_max_घातer(matching_snk_pकरो) > pकरो_max_घातer(pकरो)))
			max_mw = pकरो_max_घातer(matching_snk_pकरो);
		अन्यथा अगर (pकरो_max_current(matching_snk_pकरो) >
			 pकरो_max_current(pकरो))
			max_ma = pकरो_max_current(matching_snk_pकरो);
	पूर्ण

	tcpm_log(port, "cc=%d cc1=%d cc2=%d vbus=%d vconn=%s polarity=%d",
		 port->cc_req, port->cc1, port->cc2, port->vbus_source,
		 port->vconn_role == TYPEC_SOURCE ? "source" : "sink",
		 port->polarity);

	अगर (type == PDO_TYPE_BATT) अणु
		*rकरो = RDO_BATT(src_pकरो_index + 1, mw, max_mw, flags);

		tcpm_log(port, "Requesting PDO %d: %u mV, %u mW%s",
			 src_pकरो_index, mv, mw,
			 flags & RDO_CAP_MISMATCH ? " [mismatch]" : "");
	पूर्ण अन्यथा अणु
		*rकरो = RDO_FIXED(src_pकरो_index + 1, ma, max_ma, flags);

		tcpm_log(port, "Requesting PDO %d: %u mV, %u mA%s",
			 src_pकरो_index, mv, ma,
			 flags & RDO_CAP_MISMATCH ? " [mismatch]" : "");
	पूर्ण

	port->req_current_limit = ma;
	port->req_supply_voltage = mv;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_pd_send_request(काष्ठा tcpm_port *port)
अणु
	काष्ठा pd_message msg;
	पूर्णांक ret;
	u32 rकरो;

	ret = tcpm_pd_build_request(port, &rकरो);
	अगर (ret < 0)
		वापस ret;

	स_रखो(&msg, 0, माप(msg));
	msg.header = PD_HEADER_LE(PD_DATA_REQUEST,
				  port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 1);
	msg.payload[0] = cpu_to_le32(rकरो);

	वापस tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
पूर्ण

अटल पूर्णांक tcpm_pd_build_pps_request(काष्ठा tcpm_port *port, u32 *rकरो)
अणु
	अचिन्हित पूर्णांक out_mv, op_ma, op_mw, max_mv, max_ma, flags;
	क्रमागत pd_pकरो_type type;
	अचिन्हित पूर्णांक src_pकरो_index;
	u32 pकरो;

	src_pकरो_index = tcpm_pd_select_pps_apकरो(port);
	अगर (!src_pकरो_index)
		वापस -EOPNOTSUPP;

	pकरो = port->source_caps[src_pकरो_index];
	type = pकरो_type(pकरो);

	चयन (type) अणु
	हाल PDO_TYPE_APDO:
		अगर (pकरो_apकरो_type(pकरो) != APDO_TYPE_PPS) अणु
			tcpm_log(port, "Invalid APDO selected!");
			वापस -EINVAL;
		पूर्ण
		max_mv = port->pps_data.req_max_volt;
		max_ma = port->pps_data.req_max_curr;
		out_mv = port->pps_data.req_out_volt;
		op_ma = port->pps_data.req_op_curr;
		अवरोध;
	शेष:
		tcpm_log(port, "Invalid PDO selected!");
		वापस -EINVAL;
	पूर्ण

	flags = RDO_USB_COMM | RDO_NO_SUSPEND;

	op_mw = (op_ma * out_mv) / 1000;
	अगर (op_mw < port->operating_snk_mw) अणु
		/*
		 * Try raising current to meet घातer needs. If that's not enough
		 * then try upping the voltage. If that's still not enough
		 * then we've obviously chosen a PPS APDO which really isn't
		 * suitable so abanकरोn ship.
		 */
		op_ma = (port->operating_snk_mw * 1000) / out_mv;
		अगर ((port->operating_snk_mw * 1000) % out_mv)
			++op_ma;
		op_ma += RDO_PROG_CURR_MA_STEP - (op_ma % RDO_PROG_CURR_MA_STEP);

		अगर (op_ma > max_ma) अणु
			op_ma = max_ma;
			out_mv = (port->operating_snk_mw * 1000) / op_ma;
			अगर ((port->operating_snk_mw * 1000) % op_ma)
				++out_mv;
			out_mv += RDO_PROG_VOLT_MV_STEP -
				  (out_mv % RDO_PROG_VOLT_MV_STEP);

			अगर (out_mv > max_mv) अणु
				tcpm_log(port, "Invalid PPS APDO selected!");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	tcpm_log(port, "cc=%d cc1=%d cc2=%d vbus=%d vconn=%s polarity=%d",
		 port->cc_req, port->cc1, port->cc2, port->vbus_source,
		 port->vconn_role == TYPEC_SOURCE ? "source" : "sink",
		 port->polarity);

	*rकरो = RDO_PROG(src_pकरो_index + 1, out_mv, op_ma, flags);

	tcpm_log(port, "Requesting APDO %d: %u mV, %u mA",
		 src_pकरो_index, out_mv, op_ma);

	port->pps_data.req_op_curr = op_ma;
	port->pps_data.req_out_volt = out_mv;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_pd_send_pps_request(काष्ठा tcpm_port *port)
अणु
	काष्ठा pd_message msg;
	पूर्णांक ret;
	u32 rकरो;

	ret = tcpm_pd_build_pps_request(port, &rकरो);
	अगर (ret < 0)
		वापस ret;

	स_रखो(&msg, 0, माप(msg));
	msg.header = PD_HEADER_LE(PD_DATA_REQUEST,
				  port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 1);
	msg.payload[0] = cpu_to_le32(rकरो);

	वापस tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
पूर्ण

अटल पूर्णांक tcpm_set_vbus(काष्ठा tcpm_port *port, bool enable)
अणु
	पूर्णांक ret;

	अगर (enable && port->vbus_अक्षरge)
		वापस -EINVAL;

	tcpm_log(port, "vbus:=%d charge=%d", enable, port->vbus_अक्षरge);

	ret = port->tcpc->set_vbus(port->tcpc, enable, port->vbus_अक्षरge);
	अगर (ret < 0)
		वापस ret;

	port->vbus_source = enable;
	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_set_अक्षरge(काष्ठा tcpm_port *port, bool अक्षरge)
अणु
	पूर्णांक ret;

	अगर (अक्षरge && port->vbus_source)
		वापस -EINVAL;

	अगर (अक्षरge != port->vbus_अक्षरge) अणु
		tcpm_log(port, "vbus=%d charge:=%d", port->vbus_source, अक्षरge);
		ret = port->tcpc->set_vbus(port->tcpc, port->vbus_source,
					   अक्षरge);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	port->vbus_अक्षरge = अक्षरge;
	घातer_supply_changed(port->psy);
	वापस 0;
पूर्ण

अटल bool tcpm_start_toggling(काष्ठा tcpm_port *port, क्रमागत typec_cc_status cc)
अणु
	पूर्णांक ret;

	अगर (!port->tcpc->start_toggling)
		वापस false;

	tcpm_log_क्रमce(port, "Start toggling");
	ret = port->tcpc->start_toggling(port->tcpc, port->port_type, cc);
	वापस ret == 0;
पूर्ण

अटल पूर्णांक tcpm_init_vbus(काष्ठा tcpm_port *port)
अणु
	पूर्णांक ret;

	ret = port->tcpc->set_vbus(port->tcpc, false, false);
	port->vbus_source = false;
	port->vbus_अक्षरge = false;
	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_init_vconn(काष्ठा tcpm_port *port)
अणु
	पूर्णांक ret;

	ret = port->tcpc->set_vconn(port->tcpc, false);
	port->vconn_role = TYPEC_SINK;
	वापस ret;
पूर्ण

अटल व्योम tcpm_typec_connect(काष्ठा tcpm_port *port)
अणु
	अगर (!port->connected) अणु
		/* Make sure we करोn't report stale identity inक्रमmation */
		स_रखो(&port->partner_ident, 0, माप(port->partner_ident));
		port->partner_desc.usb_pd = port->pd_capable;
		अगर (tcpm_port_is_debug(port))
			port->partner_desc.accessory = TYPEC_ACCESSORY_DEBUG;
		अन्यथा अगर (tcpm_port_is_audio(port))
			port->partner_desc.accessory = TYPEC_ACCESSORY_AUDIO;
		अन्यथा
			port->partner_desc.accessory = TYPEC_ACCESSORY_NONE;
		port->partner = typec_रेजिस्टर_partner(port->typec_port,
						       &port->partner_desc);
		port->connected = true;
	पूर्ण
पूर्ण

अटल पूर्णांक tcpm_src_attach(काष्ठा tcpm_port *port)
अणु
	क्रमागत typec_cc_polarity polarity =
				port->cc2 == TYPEC_CC_RD ? TYPEC_POLARITY_CC2
							 : TYPEC_POLARITY_CC1;
	पूर्णांक ret;

	अगर (port->attached)
		वापस 0;

	ret = tcpm_set_polarity(port, polarity);
	अगर (ret < 0)
		वापस ret;

	अगर (port->tcpc->enable_स्वतः_vbus_disअक्षरge) अणु
		ret = port->tcpc->enable_स्वतः_vbus_disअक्षरge(port->tcpc, true);
		tcpm_log_क्रमce(port, "enable vbus discharge ret:%d", ret);
		अगर (!ret)
			port->स्वतः_vbus_disअक्षरge_enabled = true;
	पूर्ण

	ret = tcpm_set_roles(port, true, TYPEC_SOURCE, tcpm_data_role_क्रम_source(port));
	अगर (ret < 0)
		वापस ret;

	ret = port->tcpc->set_pd_rx(port->tcpc, true);
	अगर (ret < 0)
		जाओ out_disable_mux;

	/*
	 * USB Type-C specअगरication, version 1.2,
	 * chapter 4.5.2.2.8.1 (Attached.SRC Requirements)
	 * Enable VCONN only अगर the non-RD port is set to RA.
	 */
	अगर ((polarity == TYPEC_POLARITY_CC1 && port->cc2 == TYPEC_CC_RA) ||
	    (polarity == TYPEC_POLARITY_CC2 && port->cc1 == TYPEC_CC_RA)) अणु
		ret = tcpm_set_vconn(port, true);
		अगर (ret < 0)
			जाओ out_disable_pd;
	पूर्ण

	ret = tcpm_set_vbus(port, true);
	अगर (ret < 0)
		जाओ out_disable_vconn;

	port->pd_capable = false;

	port->partner = शून्य;

	port->attached = true;
	port->send_discover = true;

	वापस 0;

out_disable_vconn:
	tcpm_set_vconn(port, false);
out_disable_pd:
	port->tcpc->set_pd_rx(port->tcpc, false);
out_disable_mux:
	tcpm_mux_set(port, TYPEC_STATE_SAFE, USB_ROLE_NONE,
		     TYPEC_ORIENTATION_NONE);
	वापस ret;
पूर्ण

अटल व्योम tcpm_typec_disconnect(काष्ठा tcpm_port *port)
अणु
	अगर (port->connected) अणु
		typec_unरेजिस्टर_partner(port->partner);
		port->partner = शून्य;
		port->connected = false;
	पूर्ण
पूर्ण

अटल व्योम tcpm_unरेजिस्टर_alपंचांगodes(काष्ठा tcpm_port *port)
अणु
	काष्ठा pd_mode_data *modep = &port->mode_data;
	पूर्णांक i;

	क्रम (i = 0; i < modep->alपंचांगodes; i++) अणु
		typec_unरेजिस्टर_alपंचांगode(port->partner_alपंचांगode[i]);
		port->partner_alपंचांगode[i] = शून्य;
	पूर्ण

	स_रखो(modep, 0, माप(*modep));
पूर्ण

अटल व्योम tcpm_set_partner_usb_comm_capable(काष्ठा tcpm_port *port, bool capable)
अणु
	tcpm_log(port, "Setting usb_comm capable %s", capable ? "true" : "false");

	अगर (port->tcpc->set_partner_usb_comm_capable)
		port->tcpc->set_partner_usb_comm_capable(port->tcpc, capable);
पूर्ण

अटल व्योम tcpm_reset_port(काष्ठा tcpm_port *port)
अणु
	पूर्णांक ret;

	अगर (port->tcpc->enable_स्वतः_vbus_disअक्षरge) अणु
		ret = port->tcpc->enable_स्वतः_vbus_disअक्षरge(port->tcpc, false);
		tcpm_log_क्रमce(port, "Disable vbus discharge ret:%d", ret);
		अगर (!ret)
			port->स्वतः_vbus_disअक्षरge_enabled = false;
	पूर्ण
	port->in_ams = false;
	port->ams = NONE_AMS;
	port->vdm_sm_running = false;
	tcpm_unरेजिस्टर_alपंचांगodes(port);
	tcpm_typec_disconnect(port);
	port->attached = false;
	port->pd_capable = false;
	port->pps_data.supported = false;
	tcpm_set_partner_usb_comm_capable(port, false);

	/*
	 * First Rx ID should be 0; set this to a sentinel of -1 so that
	 * we can check tcpm_pd_rx_handler() अगर we had seen it beक्रमe.
	 */
	port->rx_msgid = -1;

	port->tcpc->set_pd_rx(port->tcpc, false);
	tcpm_init_vbus(port);	/* also disables अक्षरging */
	tcpm_init_vconn(port);
	tcpm_set_current_limit(port, 0, 0);
	tcpm_set_polarity(port, TYPEC_POLARITY_CC1);
	tcpm_mux_set(port, TYPEC_STATE_SAFE, USB_ROLE_NONE,
		     TYPEC_ORIENTATION_NONE);
	tcpm_set_attached_state(port, false);
	port->try_src_count = 0;
	port->try_snk_count = 0;
	port->usb_type = POWER_SUPPLY_USB_TYPE_C;
	घातer_supply_changed(port->psy);
	port->nr_sink_caps = 0;
	port->sink_cap_करोne = false;
	अगर (port->tcpc->enable_frs)
		port->tcpc->enable_frs(port->tcpc, false);
पूर्ण

अटल व्योम tcpm_detach(काष्ठा tcpm_port *port)
अणु
	अगर (tcpm_port_is_disconnected(port))
		port->hard_reset_count = 0;

	अगर (!port->attached)
		वापस;

	अगर (port->tcpc->set_bist_data) अणु
		tcpm_log(port, "disable BIST MODE TESTDATA");
		port->tcpc->set_bist_data(port->tcpc, false);
	पूर्ण

	tcpm_reset_port(port);
पूर्ण

अटल व्योम tcpm_src_detach(काष्ठा tcpm_port *port)
अणु
	tcpm_detach(port);
पूर्ण

अटल पूर्णांक tcpm_snk_attach(काष्ठा tcpm_port *port)
अणु
	पूर्णांक ret;

	अगर (port->attached)
		वापस 0;

	ret = tcpm_set_polarity(port, port->cc2 != TYPEC_CC_OPEN ?
				TYPEC_POLARITY_CC2 : TYPEC_POLARITY_CC1);
	अगर (ret < 0)
		वापस ret;

	अगर (port->tcpc->enable_स्वतः_vbus_disअक्षरge) अणु
		tcpm_set_स्वतः_vbus_disअक्षरge_threshold(port, TYPEC_PWR_MODE_USB, false, VSAFE5V);
		ret = port->tcpc->enable_स्वतः_vbus_disअक्षरge(port->tcpc, true);
		tcpm_log_क्रमce(port, "enable vbus discharge ret:%d", ret);
		अगर (!ret)
			port->स्वतः_vbus_disअक्षरge_enabled = true;
	पूर्ण

	ret = tcpm_set_roles(port, true, TYPEC_SINK, tcpm_data_role_क्रम_sink(port));
	अगर (ret < 0)
		वापस ret;

	port->pd_capable = false;

	port->partner = शून्य;

	port->attached = true;
	port->send_discover = true;

	वापस 0;
पूर्ण

अटल व्योम tcpm_snk_detach(काष्ठा tcpm_port *port)
अणु
	tcpm_detach(port);
पूर्ण

अटल पूर्णांक tcpm_acc_attach(काष्ठा tcpm_port *port)
अणु
	पूर्णांक ret;

	अगर (port->attached)
		वापस 0;

	ret = tcpm_set_roles(port, true, TYPEC_SOURCE,
			     tcpm_data_role_क्रम_source(port));
	अगर (ret < 0)
		वापस ret;

	port->partner = शून्य;

	tcpm_typec_connect(port);

	port->attached = true;

	वापस 0;
पूर्ण

अटल व्योम tcpm_acc_detach(काष्ठा tcpm_port *port)
अणु
	tcpm_detach(port);
पूर्ण

अटल अंतरभूत क्रमागत tcpm_state hard_reset_state(काष्ठा tcpm_port *port)
अणु
	अगर (port->hard_reset_count < PD_N_HARD_RESET_COUNT)
		वापस HARD_RESET_SEND;
	अगर (port->pd_capable)
		वापस ERROR_RECOVERY;
	अगर (port->pwr_role == TYPEC_SOURCE)
		वापस SRC_UNATTACHED;
	अगर (port->state == SNK_WAIT_CAPABILITIES)
		वापस SNK_READY;
	वापस SNK_UNATTACHED;
पूर्ण

अटल अंतरभूत क्रमागत tcpm_state unattached_state(काष्ठा tcpm_port *port)
अणु
	अगर (port->port_type == TYPEC_PORT_DRP) अणु
		अगर (port->pwr_role == TYPEC_SOURCE)
			वापस SRC_UNATTACHED;
		अन्यथा
			वापस SNK_UNATTACHED;
	पूर्ण अन्यथा अगर (port->port_type == TYPEC_PORT_SRC) अणु
		वापस SRC_UNATTACHED;
	पूर्ण

	वापस SNK_UNATTACHED;
पूर्ण

अटल व्योम tcpm_swap_complete(काष्ठा tcpm_port *port, पूर्णांक result)
अणु
	अगर (port->swap_pending) अणु
		port->swap_status = result;
		port->swap_pending = false;
		port->non_pd_role_swap = false;
		complete(&port->swap_complete);
	पूर्ण
पूर्ण

अटल क्रमागत typec_pwr_opmode tcpm_get_pwr_opmode(क्रमागत typec_cc_status cc)
अणु
	चयन (cc) अणु
	हाल TYPEC_CC_RP_1_5:
		वापस TYPEC_PWR_MODE_1_5A;
	हाल TYPEC_CC_RP_3_0:
		वापस TYPEC_PWR_MODE_3_0A;
	हाल TYPEC_CC_RP_DEF:
	शेष:
		वापस TYPEC_PWR_MODE_USB;
	पूर्ण
पूर्ण

अटल व्योम run_state_machine(काष्ठा tcpm_port *port)
अणु
	पूर्णांक ret;
	क्रमागत typec_pwr_opmode opmode;
	अचिन्हित पूर्णांक msecs;
	क्रमागत tcpm_state upcoming_state;

	port->enter_state = port->state;
	चयन (port->state) अणु
	हाल TOGGLING:
		अवरोध;
	/* SRC states */
	हाल SRC_UNATTACHED:
		अगर (!port->non_pd_role_swap)
			tcpm_swap_complete(port, -ENOTCONN);
		tcpm_src_detach(port);
		अगर (tcpm_start_toggling(port, tcpm_rp_cc(port))) अणु
			tcpm_set_state(port, TOGGLING, 0);
			अवरोध;
		पूर्ण
		tcpm_set_cc(port, tcpm_rp_cc(port));
		अगर (port->port_type == TYPEC_PORT_DRP)
			tcpm_set_state(port, SNK_UNATTACHED, PD_T_DRP_SNK);
		अवरोध;
	हाल SRC_ATTACH_WAIT:
		अगर (tcpm_port_is_debug(port))
			tcpm_set_state(port, DEBUG_ACC_ATTACHED,
				       PD_T_CC_DEBOUNCE);
		अन्यथा अगर (tcpm_port_is_audio(port))
			tcpm_set_state(port, AUDIO_ACC_ATTACHED,
				       PD_T_CC_DEBOUNCE);
		अन्यथा अगर (tcpm_port_is_source(port) && port->vbus_vsafe0v)
			tcpm_set_state(port,
				       tcpm_try_snk(port) ? SNK_TRY
							  : SRC_ATTACHED,
				       PD_T_CC_DEBOUNCE);
		अवरोध;

	हाल SNK_TRY:
		port->try_snk_count++;
		/*
		 * Requirements:
		 * - Do not drive vconn or vbus
		 * - Terminate CC pins (both) to Rd
		 * Action:
		 * - Wait क्रम tDRPTry (PD_T_DRP_TRY).
		 *   Until then, ignore any state changes.
		 */
		tcpm_set_cc(port, TYPEC_CC_RD);
		tcpm_set_state(port, SNK_TRY_WAIT, PD_T_DRP_TRY);
		अवरोध;
	हाल SNK_TRY_WAIT:
		अगर (tcpm_port_is_sink(port)) अणु
			tcpm_set_state(port, SNK_TRY_WAIT_DEBOUNCE, 0);
		पूर्ण अन्यथा अणु
			tcpm_set_state(port, SRC_TRYWAIT, 0);
			port->max_रुको = 0;
		पूर्ण
		अवरोध;
	हाल SNK_TRY_WAIT_DEBOUNCE:
		tcpm_set_state(port, SNK_TRY_WAIT_DEBOUNCE_CHECK_VBUS,
			       PD_T_TRY_CC_DEBOUNCE);
		अवरोध;
	हाल SNK_TRY_WAIT_DEBOUNCE_CHECK_VBUS:
		अगर (port->vbus_present && tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACHED, 0);
		अन्यथा
			port->max_रुको = 0;
		अवरोध;
	हाल SRC_TRYWAIT:
		tcpm_set_cc(port, tcpm_rp_cc(port));
		अगर (port->max_रुको == 0) अणु
			port->max_रुको = jअगरfies +
					 msecs_to_jअगरfies(PD_T_DRP_TRY);
			tcpm_set_state(port, SRC_TRYWAIT_UNATTACHED,
				       PD_T_DRP_TRY);
		पूर्ण अन्यथा अणु
			अगर (समय_is_after_jअगरfies(port->max_रुको))
				tcpm_set_state(port, SRC_TRYWAIT_UNATTACHED,
					       jअगरfies_to_msecs(port->max_रुको -
								jअगरfies));
			अन्यथा
				tcpm_set_state(port, SNK_UNATTACHED, 0);
		पूर्ण
		अवरोध;
	हाल SRC_TRYWAIT_DEBOUNCE:
		tcpm_set_state(port, SRC_ATTACHED, PD_T_CC_DEBOUNCE);
		अवरोध;
	हाल SRC_TRYWAIT_UNATTACHED:
		tcpm_set_state(port, SNK_UNATTACHED, 0);
		अवरोध;

	हाल SRC_ATTACHED:
		ret = tcpm_src_attach(port);
		tcpm_set_state(port, SRC_UNATTACHED,
			       ret < 0 ? 0 : PD_T_PS_SOURCE_ON);
		अवरोध;
	हाल SRC_STARTUP:
		opmode =  tcpm_get_pwr_opmode(tcpm_rp_cc(port));
		typec_set_pwr_opmode(port->typec_port, opmode);
		port->pwr_opmode = TYPEC_PWR_MODE_USB;
		port->caps_count = 0;
		port->negotiated_rev = PD_MAX_REV;
		port->message_id = 0;
		port->rx_msgid = -1;
		port->explicit_contract = false;
		/* SNK -> SRC POWER/FAST_ROLE_SWAP finished */
		अगर (port->ams == POWER_ROLE_SWAP ||
		    port->ams == FAST_ROLE_SWAP)
			tcpm_ams_finish(port);
		port->upcoming_state = SRC_SEND_CAPABILITIES;
		tcpm_ams_start(port, POWER_NEGOTIATION);
		अवरोध;
	हाल SRC_SEND_CAPABILITIES:
		port->caps_count++;
		अगर (port->caps_count > PD_N_CAPS_COUNT) अणु
			tcpm_set_state(port, SRC_READY, 0);
			अवरोध;
		पूर्ण
		ret = tcpm_pd_send_source_caps(port);
		अगर (ret < 0) अणु
			tcpm_set_state(port, SRC_SEND_CAPABILITIES,
				       PD_T_SEND_SOURCE_CAP);
		पूर्ण अन्यथा अणु
			/*
			 * Per standard, we should clear the reset counter here.
			 * However, that can result in state machine hang-ups.
			 * Reset it only in READY state to improve stability.
			 */
			/* port->hard_reset_count = 0; */
			port->caps_count = 0;
			port->pd_capable = true;
			tcpm_set_state_cond(port, SRC_SEND_CAPABILITIES_TIMEOUT,
					    PD_T_SEND_SOURCE_CAP);
		पूर्ण
		अवरोध;
	हाल SRC_SEND_CAPABILITIES_TIMEOUT:
		/*
		 * Error recovery क्रम a PD_DATA_SOURCE_CAP reply समयout.
		 *
		 * PD 2.0 sinks are supposed to accept src-capabilities with a
		 * 3.0 header and simply ignore any src PDOs which the sink करोes
		 * not understand such as PPS but some 2.0 sinks instead ignore
		 * the entire PD_DATA_SOURCE_CAP message, causing contract
		 * negotiation to fail.
		 *
		 * After PD_N_HARD_RESET_COUNT hard-reset attempts, we try
		 * sending src-capabilities with a lower PD revision to
		 * make these broken sinks work.
		 */
		अगर (port->hard_reset_count < PD_N_HARD_RESET_COUNT) अणु
			tcpm_set_state(port, HARD_RESET_SEND, 0);
		पूर्ण अन्यथा अगर (port->negotiated_rev > PD_REV20) अणु
			port->negotiated_rev--;
			port->hard_reset_count = 0;
			tcpm_set_state(port, SRC_SEND_CAPABILITIES, 0);
		पूर्ण अन्यथा अणु
			tcpm_set_state(port, hard_reset_state(port), 0);
		पूर्ण
		अवरोध;
	हाल SRC_NEGOTIATE_CAPABILITIES:
		ret = tcpm_pd_check_request(port);
		अगर (ret < 0) अणु
			tcpm_pd_send_control(port, PD_CTRL_REJECT);
			अगर (!port->explicit_contract) अणु
				tcpm_set_state(port,
					       SRC_WAIT_NEW_CAPABILITIES, 0);
			पूर्ण अन्यथा अणु
				tcpm_set_state(port, SRC_READY, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
			tcpm_set_partner_usb_comm_capable(port,
							  !!(port->sink_request & RDO_USB_COMM));
			tcpm_set_state(port, SRC_TRANSITION_SUPPLY,
				       PD_T_SRC_TRANSITION);
		पूर्ण
		अवरोध;
	हाल SRC_TRANSITION_SUPPLY:
		/* XXX: regulator_set_voltage(vbus, ...) */
		tcpm_pd_send_control(port, PD_CTRL_PS_RDY);
		port->explicit_contract = true;
		typec_set_pwr_opmode(port->typec_port, TYPEC_PWR_MODE_PD);
		port->pwr_opmode = TYPEC_PWR_MODE_PD;
		tcpm_set_state_cond(port, SRC_READY, 0);
		अवरोध;
	हाल SRC_READY:
#अगर 1
		port->hard_reset_count = 0;
#पूर्ण_अगर
		port->try_src_count = 0;

		tcpm_swap_complete(port, 0);
		tcpm_typec_connect(port);

		अगर (port->ams != NONE_AMS)
			tcpm_ams_finish(port);
		अगर (port->next_ams != NONE_AMS) अणु
			port->ams = port->next_ams;
			port->next_ams = NONE_AMS;
		पूर्ण

		/*
		 * If previous AMS is पूर्णांकerrupted, चयन to the upcoming
		 * state.
		 */
		अगर (port->upcoming_state != INVALID_STATE) अणु
			upcoming_state = port->upcoming_state;
			port->upcoming_state = INVALID_STATE;
			tcpm_set_state(port, upcoming_state, 0);
			अवरोध;
		पूर्ण

		/*
		 * 6.4.4.3.1 Discover Identity
		 * "The Discover Identity Command Shall only be sent to SOP when there is an
		 * Explicit Contract."
		 * For now, this driver only supports SOP क्रम DISCOVER_IDENTITY, thus using
		 * port->explicit_contract to decide whether to send the command.
		 */
		अगर (port->explicit_contract)
			mod_send_discover_delayed_work(port, 0);
		अन्यथा
			port->send_discover = false;

		/*
		 * 6.3.5
		 * Sending ping messages is not necessary अगर
		 * - the source operates at vSafe5V
		 * or
		 * - The प्रणाली is not operating in PD mode
		 * or
		 * - Both partners are connected using a Type-C connector
		 *
		 * There is no actual need to send PD messages since the local
		 * port type-c and the spec करोes not clearly say whether PD is
		 * possible when type-c is connected to Type-A/B
		 */
		अवरोध;
	हाल SRC_WAIT_NEW_CAPABILITIES:
		/* Nothing to करो... */
		अवरोध;

	/* SNK states */
	हाल SNK_UNATTACHED:
		अगर (!port->non_pd_role_swap)
			tcpm_swap_complete(port, -ENOTCONN);
		tcpm_pps_complete(port, -ENOTCONN);
		tcpm_snk_detach(port);
		अगर (tcpm_start_toggling(port, TYPEC_CC_RD)) अणु
			tcpm_set_state(port, TOGGLING, 0);
			अवरोध;
		पूर्ण
		tcpm_set_cc(port, TYPEC_CC_RD);
		अगर (port->port_type == TYPEC_PORT_DRP)
			tcpm_set_state(port, SRC_UNATTACHED, PD_T_DRP_SRC);
		अवरोध;
	हाल SNK_ATTACH_WAIT:
		अगर ((port->cc1 == TYPEC_CC_OPEN &&
		     port->cc2 != TYPEC_CC_OPEN) ||
		    (port->cc1 != TYPEC_CC_OPEN &&
		     port->cc2 == TYPEC_CC_OPEN))
			tcpm_set_state(port, SNK_DEBOUNCED,
				       PD_T_CC_DEBOUNCE);
		अन्यथा अगर (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, SNK_UNATTACHED,
				       PD_T_PD_DEBOUNCE);
		अवरोध;
	हाल SNK_DEBOUNCED:
		अगर (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, SNK_UNATTACHED,
				       PD_T_PD_DEBOUNCE);
		अन्यथा अगर (port->vbus_present)
			tcpm_set_state(port,
				       tcpm_try_src(port) ? SRC_TRY
							  : SNK_ATTACHED,
				       0);
		अन्यथा
			/* Wait क्रम VBUS, but not क्रमever */
			tcpm_set_state(port, PORT_RESET, PD_T_PS_SOURCE_ON);
		अवरोध;

	हाल SRC_TRY:
		port->try_src_count++;
		tcpm_set_cc(port, tcpm_rp_cc(port));
		port->max_रुको = 0;
		tcpm_set_state(port, SRC_TRY_WAIT, 0);
		अवरोध;
	हाल SRC_TRY_WAIT:
		अगर (port->max_रुको == 0) अणु
			port->max_रुको = jअगरfies +
					 msecs_to_jअगरfies(PD_T_DRP_TRY);
			msecs = PD_T_DRP_TRY;
		पूर्ण अन्यथा अणु
			अगर (समय_is_after_jअगरfies(port->max_रुको))
				msecs = jअगरfies_to_msecs(port->max_रुको -
							 jअगरfies);
			अन्यथा
				msecs = 0;
		पूर्ण
		tcpm_set_state(port, SNK_TRYWAIT, msecs);
		अवरोध;
	हाल SRC_TRY_DEBOUNCE:
		tcpm_set_state(port, SRC_ATTACHED, PD_T_PD_DEBOUNCE);
		अवरोध;
	हाल SNK_TRYWAIT:
		tcpm_set_cc(port, TYPEC_CC_RD);
		tcpm_set_state(port, SNK_TRYWAIT_VBUS, PD_T_CC_DEBOUNCE);
		अवरोध;
	हाल SNK_TRYWAIT_VBUS:
		/*
		 * TCPM stays in this state indefinitely until VBUS
		 * is detected as दीर्घ as Rp is not detected क्रम
		 * more than a समय period of tPDDebounce.
		 */
		अगर (port->vbus_present && tcpm_port_is_sink(port)) अणु
			tcpm_set_state(port, SNK_ATTACHED, 0);
			अवरोध;
		पूर्ण
		अगर (!tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_TRYWAIT_DEBOUNCE, 0);
		अवरोध;
	हाल SNK_TRYWAIT_DEBOUNCE:
		tcpm_set_state(port, SNK_UNATTACHED, PD_T_PD_DEBOUNCE);
		अवरोध;
	हाल SNK_ATTACHED:
		ret = tcpm_snk_attach(port);
		अगर (ret < 0)
			tcpm_set_state(port, SNK_UNATTACHED, 0);
		अन्यथा
			tcpm_set_state(port, SNK_STARTUP, 0);
		अवरोध;
	हाल SNK_STARTUP:
		opmode =  tcpm_get_pwr_opmode(port->polarity ?
					      port->cc2 : port->cc1);
		typec_set_pwr_opmode(port->typec_port, opmode);
		port->pwr_opmode = TYPEC_PWR_MODE_USB;
		port->negotiated_rev = PD_MAX_REV;
		port->message_id = 0;
		port->rx_msgid = -1;
		port->explicit_contract = false;

		अगर (port->ams == POWER_ROLE_SWAP ||
		    port->ams == FAST_ROLE_SWAP)
			/* SRC -> SNK POWER/FAST_ROLE_SWAP finished */
			tcpm_ams_finish(port);

		tcpm_set_state(port, SNK_DISCOVERY, 0);
		अवरोध;
	हाल SNK_DISCOVERY:
		अगर (port->vbus_present) अणु
			u32 current_lim = tcpm_get_current_limit(port);

			अगर (port->slow_अक्षरger_loop && (current_lim > PD_P_SNK_STDBY_MW / 5))
				current_lim = PD_P_SNK_STDBY_MW / 5;
			tcpm_set_current_limit(port, current_lim, 5000);
			tcpm_set_अक्षरge(port, true);
			tcpm_set_state(port, SNK_WAIT_CAPABILITIES, 0);
			अवरोध;
		पूर्ण
		/*
		 * For DRP, समयouts dअगरfer. Also, handling is supposed to be
		 * dअगरferent and much more complex (dead battery detection;
		 * see USB घातer delivery specअगरication, section 8.3.3.6.1.5.1).
		 */
		tcpm_set_state(port, hard_reset_state(port),
			       port->port_type == TYPEC_PORT_DRP ?
					PD_T_DB_DETECT : PD_T_NO_RESPONSE);
		अवरोध;
	हाल SNK_DISCOVERY_DEBOUNCE:
		tcpm_set_state(port, SNK_DISCOVERY_DEBOUNCE_DONE,
			       PD_T_CC_DEBOUNCE);
		अवरोध;
	हाल SNK_DISCOVERY_DEBOUNCE_DONE:
		अगर (!tcpm_port_is_disconnected(port) &&
		    tcpm_port_is_sink(port) &&
		    kसमय_after(port->delayed_runसमय, kसमय_get())) अणु
			tcpm_set_state(port, SNK_DISCOVERY,
				       kसमय_प्रकारo_ms(kसमय_sub(port->delayed_runसमय, kसमय_get())));
			अवरोध;
		पूर्ण
		tcpm_set_state(port, unattached_state(port), 0);
		अवरोध;
	हाल SNK_WAIT_CAPABILITIES:
		ret = port->tcpc->set_pd_rx(port->tcpc, true);
		अगर (ret < 0) अणु
			tcpm_set_state(port, SNK_READY, 0);
			अवरोध;
		पूर्ण
		/*
		 * If VBUS has never been low, and we समय out रुकोing
		 * क्रम source cap, try a soft reset first, in हाल we
		 * were alपढ़ोy in a stable contract beक्रमe this boot.
		 * Do this only once.
		 */
		अगर (port->vbus_never_low) अणु
			port->vbus_never_low = false;
			tcpm_set_state(port, SNK_SOFT_RESET,
				       PD_T_SINK_WAIT_CAP);
		पूर्ण अन्यथा अणु
			tcpm_set_state(port, hard_reset_state(port),
				       PD_T_SINK_WAIT_CAP);
		पूर्ण
		अवरोध;
	हाल SNK_NEGOTIATE_CAPABILITIES:
		port->pd_capable = true;
		tcpm_set_partner_usb_comm_capable(port,
						  !!(port->source_caps[0] & PDO_FIXED_USB_COMM));
		port->hard_reset_count = 0;
		ret = tcpm_pd_send_request(port);
		अगर (ret < 0) अणु
			/* Let the Source send capabilities again. */
			tcpm_set_state(port, SNK_WAIT_CAPABILITIES, 0);
		पूर्ण अन्यथा अणु
			tcpm_set_state_cond(port, hard_reset_state(port),
					    PD_T_SENDER_RESPONSE);
		पूर्ण
		अवरोध;
	हाल SNK_NEGOTIATE_PPS_CAPABILITIES:
		ret = tcpm_pd_send_pps_request(port);
		अगर (ret < 0) अणु
			port->pps_status = ret;
			/*
			 * If this was called due to updates to sink
			 * capabilities, and pps is no दीर्घer valid, we should
			 * safely fall back to a standard PDO.
			 */
			अगर (port->update_sink_caps)
				tcpm_set_state(port, SNK_NEGOTIATE_CAPABILITIES, 0);
			अन्यथा
				tcpm_set_state(port, SNK_READY, 0);
		पूर्ण अन्यथा अणु
			tcpm_set_state_cond(port, hard_reset_state(port),
					    PD_T_SENDER_RESPONSE);
		पूर्ण
		अवरोध;
	हाल SNK_TRANSITION_SINK:
		/* From the USB PD spec:
		 * "The Sink Shall transition to Sink Standby beक्रमe a positive or
		 * negative voltage transition of VBUS. During Sink Standby
		 * the Sink Shall reduce its घातer draw to pSnkStdby."
		 *
		 * This is not applicable to PPS though as the port can जारी
		 * to draw negotiated घातer without चयनing to standby.
		 */
		अगर (port->supply_voltage != port->req_supply_voltage && !port->pps_data.active &&
		    port->current_limit * port->supply_voltage / 1000 > PD_P_SNK_STDBY_MW) अणु
			u32 stdby_ma = PD_P_SNK_STDBY_MW * 1000 / port->supply_voltage;

			tcpm_log(port, "Setting standby current %u mV @ %u mA",
				 port->supply_voltage, stdby_ma);
			tcpm_set_current_limit(port, stdby_ma, port->supply_voltage);
		पूर्ण
		fallthrough;
	हाल SNK_TRANSITION_SINK_VBUS:
		tcpm_set_state(port, hard_reset_state(port),
			       PD_T_PS_TRANSITION);
		अवरोध;
	हाल SNK_READY:
		port->try_snk_count = 0;
		port->update_sink_caps = false;
		अगर (port->explicit_contract) अणु
			typec_set_pwr_opmode(port->typec_port,
					     TYPEC_PWR_MODE_PD);
			port->pwr_opmode = TYPEC_PWR_MODE_PD;
		पूर्ण

		अगर (!port->pd_capable && port->slow_अक्षरger_loop)
			tcpm_set_current_limit(port, tcpm_get_current_limit(port), 5000);
		tcpm_swap_complete(port, 0);
		tcpm_typec_connect(port);
		mod_enable_frs_delayed_work(port, 0);
		tcpm_pps_complete(port, port->pps_status);

		अगर (port->ams != NONE_AMS)
			tcpm_ams_finish(port);
		अगर (port->next_ams != NONE_AMS) अणु
			port->ams = port->next_ams;
			port->next_ams = NONE_AMS;
		पूर्ण

		/*
		 * If previous AMS is पूर्णांकerrupted, चयन to the upcoming
		 * state.
		 */
		अगर (port->upcoming_state != INVALID_STATE) अणु
			upcoming_state = port->upcoming_state;
			port->upcoming_state = INVALID_STATE;
			tcpm_set_state(port, upcoming_state, 0);
			अवरोध;
		पूर्ण

		/*
		 * 6.4.4.3.1 Discover Identity
		 * "The Discover Identity Command Shall only be sent to SOP when there is an
		 * Explicit Contract."
		 * For now, this driver only supports SOP क्रम DISCOVER_IDENTITY, thus using
		 * port->explicit_contract.
		 */
		अगर (port->explicit_contract)
			mod_send_discover_delayed_work(port, 0);
		अन्यथा
			port->send_discover = false;

		घातer_supply_changed(port->psy);
		अवरोध;

	/* Accessory states */
	हाल ACC_UNATTACHED:
		tcpm_acc_detach(port);
		tcpm_set_state(port, SRC_UNATTACHED, 0);
		अवरोध;
	हाल DEBUG_ACC_ATTACHED:
	हाल AUDIO_ACC_ATTACHED:
		ret = tcpm_acc_attach(port);
		अगर (ret < 0)
			tcpm_set_state(port, ACC_UNATTACHED, 0);
		अवरोध;
	हाल AUDIO_ACC_DEBOUNCE:
		tcpm_set_state(port, ACC_UNATTACHED, PD_T_CC_DEBOUNCE);
		अवरोध;

	/* Hard_Reset states */
	हाल HARD_RESET_SEND:
		अगर (port->ams != NONE_AMS)
			tcpm_ams_finish(port);
		/*
		 * State machine will be directed to HARD_RESET_START,
		 * thus set upcoming_state to INVALID_STATE.
		 */
		port->upcoming_state = INVALID_STATE;
		tcpm_ams_start(port, HARD_RESET);
		अवरोध;
	हाल HARD_RESET_START:
		port->sink_cap_करोne = false;
		अगर (port->tcpc->enable_frs)
			port->tcpc->enable_frs(port->tcpc, false);
		port->hard_reset_count++;
		port->tcpc->set_pd_rx(port->tcpc, false);
		tcpm_unरेजिस्टर_alपंचांगodes(port);
		port->nr_sink_caps = 0;
		port->send_discover = true;
		अगर (port->pwr_role == TYPEC_SOURCE)
			tcpm_set_state(port, SRC_HARD_RESET_VBUS_OFF,
				       PD_T_PS_HARD_RESET);
		अन्यथा
			tcpm_set_state(port, SNK_HARD_RESET_SINK_OFF, 0);
		अवरोध;
	हाल SRC_HARD_RESET_VBUS_OFF:
		/*
		 * 7.1.5 Response to Hard Resets
		 * Hard Reset Signaling indicates a communication failure has occurred and the
		 * Source Shall stop driving VCONN, Shall हटाओ Rp from the VCONN pin and Shall
		 * drive VBUS to vSafe0V as shown in Figure 7-9.
		 */
		tcpm_set_vconn(port, false);
		tcpm_set_vbus(port, false);
		tcpm_set_roles(port, port->self_घातered, TYPEC_SOURCE,
			       tcpm_data_role_क्रम_source(port));
		/*
		 * If tcpc fails to notअगरy vbus off, TCPM will रुको क्रम PD_T_SAFE_0V +
		 * PD_T_SRC_RECOVER beक्रमe turning vbus back on.
		 * From Table 7-12 Sequence Description क्रम a Source Initiated Hard Reset:
		 * 4. Policy Engine रुकोs tPSHardReset after sending Hard Reset Signaling and then
		 * tells the Device Policy Manager to inकाष्ठा the घातer supply to perक्रमm a
		 * Hard Reset. The transition to vSafe0V Shall occur within tSafe0V (t2).
		 * 5. After tSrcRecover the Source applies घातer to VBUS in an attempt to
		 * re-establish communication with the Sink and resume USB Default Operation.
		 * The transition to vSafe5V Shall occur within tSrcTurnOn(t4).
		 */
		tcpm_set_state(port, SRC_HARD_RESET_VBUS_ON, PD_T_SAFE_0V + PD_T_SRC_RECOVER);
		अवरोध;
	हाल SRC_HARD_RESET_VBUS_ON:
		tcpm_set_vconn(port, true);
		tcpm_set_vbus(port, true);
		अगर (port->ams == HARD_RESET)
			tcpm_ams_finish(port);
		port->tcpc->set_pd_rx(port->tcpc, true);
		tcpm_set_attached_state(port, true);
		tcpm_set_state(port, SRC_UNATTACHED, PD_T_PS_SOURCE_ON);
		अवरोध;
	हाल SNK_HARD_RESET_SINK_OFF:
		/* Do not disअक्षरge/disconnect during hard reseet */
		tcpm_set_स्वतः_vbus_disअक्षरge_threshold(port, TYPEC_PWR_MODE_USB, false, 0);
		स_रखो(&port->pps_data, 0, माप(port->pps_data));
		tcpm_set_vconn(port, false);
		अगर (port->pd_capable)
			tcpm_set_अक्षरge(port, false);
		tcpm_set_roles(port, port->self_घातered, TYPEC_SINK,
			       tcpm_data_role_क्रम_sink(port));
		/*
		 * VBUS may or may not toggle, depending on the adapter.
		 * If it करोesn't toggle, transition to SNK_HARD_RESET_SINK_ON
		 * directly after समयout.
		 */
		tcpm_set_state(port, SNK_HARD_RESET_SINK_ON, PD_T_SAFE_0V);
		अवरोध;
	हाल SNK_HARD_RESET_WAIT_VBUS:
		अगर (port->ams == HARD_RESET)
			tcpm_ams_finish(port);
		/* Assume we're disconnected if VBUS doesn't come back. */
		tcpm_set_state(port, SNK_UNATTACHED,
			       PD_T_SRC_RECOVER_MAX + PD_T_SRC_TURN_ON);
		अवरोध;
	हाल SNK_HARD_RESET_SINK_ON:
		/* Note: There is no guarantee that VBUS is on in this state */
		/*
		 * XXX:
		 * The specअगरication suggests that dual mode ports in sink
		 * mode should transition to state PE_SRC_Transition_to_शेष.
		 * See USB घातer delivery specअगरication chapter 8.3.3.6.1.3.
		 * This would mean to to
		 * - turn off VCONN, reset घातer supply
		 * - request hardware reset
		 * - turn on VCONN
		 * - Transition to state PE_Src_Startup
		 * SNK only ports shall transition to state Snk_Startup
		 * (see chapter 8.3.3.3.8).
		 * Similar, dual-mode ports in source mode should transition
		 * to PE_SNK_Transition_to_शेष.
		 */
		अगर (port->pd_capable) अणु
			tcpm_set_current_limit(port,
					       tcpm_get_current_limit(port),
					       5000);
			tcpm_set_अक्षरge(port, true);
		पूर्ण
		अगर (port->ams == HARD_RESET)
			tcpm_ams_finish(port);
		tcpm_set_attached_state(port, true);
		tcpm_set_स्वतः_vbus_disअक्षरge_threshold(port, TYPEC_PWR_MODE_USB, false, VSAFE5V);
		tcpm_set_state(port, SNK_STARTUP, 0);
		अवरोध;

	/* Soft_Reset states */
	हाल SOFT_RESET:
		port->message_id = 0;
		port->rx_msgid = -1;
		tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
		tcpm_ams_finish(port);
		अगर (port->pwr_role == TYPEC_SOURCE) अणु
			port->upcoming_state = SRC_SEND_CAPABILITIES;
			tcpm_ams_start(port, POWER_NEGOTIATION);
		पूर्ण अन्यथा अणु
			tcpm_set_state(port, SNK_WAIT_CAPABILITIES, 0);
		पूर्ण
		अवरोध;
	हाल SRC_SOFT_RESET_WAIT_SNK_TX:
	हाल SNK_SOFT_RESET:
		अगर (port->ams != NONE_AMS)
			tcpm_ams_finish(port);
		port->upcoming_state = SOFT_RESET_SEND;
		tcpm_ams_start(port, SOFT_RESET_AMS);
		अवरोध;
	हाल SOFT_RESET_SEND:
		port->message_id = 0;
		port->rx_msgid = -1;
		अगर (tcpm_pd_send_control(port, PD_CTRL_SOFT_RESET))
			tcpm_set_state_cond(port, hard_reset_state(port), 0);
		अन्यथा
			tcpm_set_state_cond(port, hard_reset_state(port),
					    PD_T_SENDER_RESPONSE);
		अवरोध;

	/* DR_Swap states */
	हाल DR_SWAP_SEND:
		tcpm_pd_send_control(port, PD_CTRL_DR_SWAP);
		tcpm_set_state_cond(port, DR_SWAP_SEND_TIMEOUT,
				    PD_T_SENDER_RESPONSE);
		अवरोध;
	हाल DR_SWAP_ACCEPT:
		tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
		/* Set VDM state machine running flag ASAP */
		अगर (port->data_role == TYPEC_DEVICE && port->send_discover)
			port->vdm_sm_running = true;
		tcpm_set_state_cond(port, DR_SWAP_CHANGE_DR, 0);
		अवरोध;
	हाल DR_SWAP_SEND_TIMEOUT:
		tcpm_swap_complete(port, -ETIMEDOUT);
		tcpm_ams_finish(port);
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;
	हाल DR_SWAP_CHANGE_DR:
		अगर (port->data_role == TYPEC_HOST) अणु
			tcpm_unरेजिस्टर_alपंचांगodes(port);
			tcpm_set_roles(port, true, port->pwr_role,
				       TYPEC_DEVICE);
		पूर्ण अन्यथा अणु
			tcpm_set_roles(port, true, port->pwr_role,
				       TYPEC_HOST);
			port->send_discover = true;
		पूर्ण
		tcpm_ams_finish(port);
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;

	हाल FR_SWAP_SEND:
		अगर (tcpm_pd_send_control(port, PD_CTRL_FR_SWAP)) अणु
			tcpm_set_state(port, ERROR_RECOVERY, 0);
			अवरोध;
		पूर्ण
		tcpm_set_state_cond(port, FR_SWAP_SEND_TIMEOUT, PD_T_SENDER_RESPONSE);
		अवरोध;
	हाल FR_SWAP_SEND_TIMEOUT:
		tcpm_set_state(port, ERROR_RECOVERY, 0);
		अवरोध;
	हाल FR_SWAP_SNK_SRC_TRANSITION_TO_OFF:
		tcpm_set_state(port, ERROR_RECOVERY, PD_T_PS_SOURCE_OFF);
		अवरोध;
	हाल FR_SWAP_SNK_SRC_NEW_SINK_READY:
		अगर (port->vbus_source)
			tcpm_set_state(port, FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED, 0);
		अन्यथा
			tcpm_set_state(port, ERROR_RECOVERY, PD_T_RECEIVER_RESPONSE);
		अवरोध;
	हाल FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED:
		tcpm_set_pwr_role(port, TYPEC_SOURCE);
		अगर (tcpm_pd_send_control(port, PD_CTRL_PS_RDY)) अणु
			tcpm_set_state(port, ERROR_RECOVERY, 0);
			अवरोध;
		पूर्ण
		tcpm_set_cc(port, tcpm_rp_cc(port));
		tcpm_set_state(port, SRC_STARTUP, PD_T_SWAP_SRC_START);
		अवरोध;

	/* PR_Swap states */
	हाल PR_SWAP_ACCEPT:
		tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
		tcpm_set_state(port, PR_SWAP_START, 0);
		अवरोध;
	हाल PR_SWAP_SEND:
		tcpm_pd_send_control(port, PD_CTRL_PR_SWAP);
		tcpm_set_state_cond(port, PR_SWAP_SEND_TIMEOUT,
				    PD_T_SENDER_RESPONSE);
		अवरोध;
	हाल PR_SWAP_SEND_TIMEOUT:
		tcpm_swap_complete(port, -ETIMEDOUT);
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;
	हाल PR_SWAP_START:
		अगर (port->pwr_role == TYPEC_SOURCE)
			tcpm_set_state(port, PR_SWAP_SRC_SNK_TRANSITION_OFF,
				       PD_T_SRC_TRANSITION);
		अन्यथा
			tcpm_set_state(port, PR_SWAP_SNK_SRC_SINK_OFF, 0);
		अवरोध;
	हाल PR_SWAP_SRC_SNK_TRANSITION_OFF:
		/*
		 * Prevent vbus disअक्षरge circuit from turning on during PR_SWAP
		 * as this is not a disconnect.
		 */
		tcpm_set_vbus(port, false);
		port->explicit_contract = false;
		/* allow समय क्रम Vbus disअक्षरge, must be < tSrcSwapStdby */
		tcpm_set_state(port, PR_SWAP_SRC_SNK_SOURCE_OFF,
			       PD_T_SRCSWAPSTDBY);
		अवरोध;
	हाल PR_SWAP_SRC_SNK_SOURCE_OFF:
		tcpm_set_cc(port, TYPEC_CC_RD);
		/* allow CC debounce */
		tcpm_set_state(port, PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED,
			       PD_T_CC_DEBOUNCE);
		अवरोध;
	हाल PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED:
		/*
		 * USB-PD standard, 6.2.1.4, Port Power Role:
		 * "During the Power Role Swap Sequence, क्रम the initial Source
		 * Port, the Port Power Role field shall be set to Sink in the
		 * PS_RDY Message indicating that the initial Sourceै s घातer
		 * supply is turned off"
		 */
		tcpm_set_pwr_role(port, TYPEC_SINK);
		अगर (tcpm_pd_send_control(port, PD_CTRL_PS_RDY)) अणु
			tcpm_set_state(port, ERROR_RECOVERY, 0);
			अवरोध;
		पूर्ण
		tcpm_set_state(port, ERROR_RECOVERY, PD_T_PS_SOURCE_ON_PRS);
		अवरोध;
	हाल PR_SWAP_SRC_SNK_SINK_ON:
		/* Set the vbus disconnect threshold क्रम implicit contract */
		tcpm_set_स्वतः_vbus_disअक्षरge_threshold(port, TYPEC_PWR_MODE_USB, false, VSAFE5V);
		tcpm_set_state(port, SNK_STARTUP, 0);
		अवरोध;
	हाल PR_SWAP_SNK_SRC_SINK_OFF:
		/*
		 * Prevent vbus disअक्षरge circuit from turning on during PR_SWAP
		 * as this is not a disconnect.
		 */
		tcpm_set_स्वतः_vbus_disअक्षरge_threshold(port, TYPEC_PWR_MODE_USB,
						       port->pps_data.active, 0);
		tcpm_set_अक्षरge(port, false);
		tcpm_set_state(port, hard_reset_state(port),
			       PD_T_PS_SOURCE_OFF);
		अवरोध;
	हाल PR_SWAP_SNK_SRC_SOURCE_ON:
		tcpm_set_cc(port, tcpm_rp_cc(port));
		tcpm_set_vbus(port, true);
		/*
		 * allow समय VBUS ramp-up, must be < tNewSrc
		 * Also, this winकरोw overlaps with CC debounce as well.
		 * So, Wait क्रम the max of two which is PD_T_NEWSRC
		 */
		tcpm_set_state(port, PR_SWAP_SNK_SRC_SOURCE_ON_VBUS_RAMPED_UP,
			       PD_T_NEWSRC);
		अवरोध;
	हाल PR_SWAP_SNK_SRC_SOURCE_ON_VBUS_RAMPED_UP:
		/*
		 * USB PD standard, 6.2.1.4:
		 * "Subsequent Messages initiated by the Policy Engine,
		 * such as the PS_RDY Message sent to indicate that Vbus
		 * is पढ़ोy, will have the Port Power Role field set to
		 * Source."
		 */
		tcpm_set_pwr_role(port, TYPEC_SOURCE);
		tcpm_pd_send_control(port, PD_CTRL_PS_RDY);
		tcpm_set_state(port, SRC_STARTUP, PD_T_SWAP_SRC_START);
		अवरोध;

	हाल VCONN_SWAP_ACCEPT:
		tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
		tcpm_ams_finish(port);
		tcpm_set_state(port, VCONN_SWAP_START, 0);
		अवरोध;
	हाल VCONN_SWAP_SEND:
		tcpm_pd_send_control(port, PD_CTRL_VCONN_SWAP);
		tcpm_set_state(port, VCONN_SWAP_SEND_TIMEOUT,
			       PD_T_SENDER_RESPONSE);
		अवरोध;
	हाल VCONN_SWAP_SEND_TIMEOUT:
		tcpm_swap_complete(port, -ETIMEDOUT);
		अगर (port->data_role == TYPEC_HOST && port->send_discover)
			port->vdm_sm_running = true;
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;
	हाल VCONN_SWAP_START:
		अगर (port->vconn_role == TYPEC_SOURCE)
			tcpm_set_state(port, VCONN_SWAP_WAIT_FOR_VCONN, 0);
		अन्यथा
			tcpm_set_state(port, VCONN_SWAP_TURN_ON_VCONN, 0);
		अवरोध;
	हाल VCONN_SWAP_WAIT_FOR_VCONN:
		tcpm_set_state(port, hard_reset_state(port),
			       PD_T_VCONN_SOURCE_ON);
		अवरोध;
	हाल VCONN_SWAP_TURN_ON_VCONN:
		tcpm_set_vconn(port, true);
		tcpm_pd_send_control(port, PD_CTRL_PS_RDY);
		अगर (port->data_role == TYPEC_HOST && port->send_discover)
			port->vdm_sm_running = true;
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;
	हाल VCONN_SWAP_TURN_OFF_VCONN:
		tcpm_set_vconn(port, false);
		अगर (port->data_role == TYPEC_HOST && port->send_discover)
			port->vdm_sm_running = true;
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;

	हाल DR_SWAP_CANCEL:
	हाल PR_SWAP_CANCEL:
	हाल VCONN_SWAP_CANCEL:
		tcpm_swap_complete(port, port->swap_status);
		अगर (port->data_role == TYPEC_HOST && port->send_discover)
			port->vdm_sm_running = true;
		अगर (port->pwr_role == TYPEC_SOURCE)
			tcpm_set_state(port, SRC_READY, 0);
		अन्यथा
			tcpm_set_state(port, SNK_READY, 0);
		अवरोध;
	हाल FR_SWAP_CANCEL:
		अगर (port->pwr_role == TYPEC_SOURCE)
			tcpm_set_state(port, SRC_READY, 0);
		अन्यथा
			tcpm_set_state(port, SNK_READY, 0);
		अवरोध;

	हाल BIST_RX:
		चयन (BDO_MODE_MASK(port->bist_request)) अणु
		हाल BDO_MODE_CARRIER2:
			tcpm_pd_transmit(port, TCPC_TX_BIST_MODE_2, शून्य);
			tcpm_set_state(port, unattached_state(port),
				       PD_T_BIST_CONT_MODE);
			अवरोध;
		हाल BDO_MODE_TESTDATA:
			अगर (port->tcpc->set_bist_data) अणु
				tcpm_log(port, "Enable BIST MODE TESTDATA");
				port->tcpc->set_bist_data(port->tcpc, true);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल GET_STATUS_SEND:
		tcpm_pd_send_control(port, PD_CTRL_GET_STATUS);
		tcpm_set_state(port, GET_STATUS_SEND_TIMEOUT,
			       PD_T_SENDER_RESPONSE);
		अवरोध;
	हाल GET_STATUS_SEND_TIMEOUT:
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;
	हाल GET_PPS_STATUS_SEND:
		tcpm_pd_send_control(port, PD_CTRL_GET_PPS_STATUS);
		tcpm_set_state(port, GET_PPS_STATUS_SEND_TIMEOUT,
			       PD_T_SENDER_RESPONSE);
		अवरोध;
	हाल GET_PPS_STATUS_SEND_TIMEOUT:
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;
	हाल GET_SINK_CAP:
		tcpm_pd_send_control(port, PD_CTRL_GET_SINK_CAP);
		tcpm_set_state(port, GET_SINK_CAP_TIMEOUT, PD_T_SENDER_RESPONSE);
		अवरोध;
	हाल GET_SINK_CAP_TIMEOUT:
		port->sink_cap_करोne = true;
		tcpm_set_state(port, पढ़ोy_state(port), 0);
		अवरोध;
	हाल ERROR_RECOVERY:
		tcpm_swap_complete(port, -EPROTO);
		tcpm_pps_complete(port, -EPROTO);
		tcpm_set_state(port, PORT_RESET, 0);
		अवरोध;
	हाल PORT_RESET:
		tcpm_reset_port(port);
		tcpm_set_cc(port, TYPEC_CC_OPEN);
		tcpm_set_state(port, PORT_RESET_WAIT_OFF,
			       PD_T_ERROR_RECOVERY);
		अवरोध;
	हाल PORT_RESET_WAIT_OFF:
		tcpm_set_state(port,
			       tcpm_शेष_state(port),
			       port->vbus_present ? PD_T_PS_SOURCE_OFF : 0);
		अवरोध;

	/* AMS पूर्णांकermediate state */
	हाल AMS_START:
		अगर (port->upcoming_state == INVALID_STATE) अणु
			tcpm_set_state(port, port->pwr_role == TYPEC_SOURCE ?
				       SRC_READY : SNK_READY, 0);
			अवरोध;
		पूर्ण

		upcoming_state = port->upcoming_state;
		port->upcoming_state = INVALID_STATE;
		tcpm_set_state(port, upcoming_state, 0);
		अवरोध;

	/* Chunk state */
	हाल CHUNK_NOT_SUPP:
		tcpm_pd_send_control(port, PD_CTRL_NOT_SUPP);
		tcpm_set_state(port, port->pwr_role == TYPEC_SOURCE ? SRC_READY : SNK_READY, 0);
		अवरोध;
	शेष:
		WARN(1, "Unexpected port state %d\n", port->state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tcpm_state_machine_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा tcpm_port *port = container_of(work, काष्ठा tcpm_port, state_machine);
	क्रमागत tcpm_state prev_state;

	mutex_lock(&port->lock);
	port->state_machine_running = true;

	अगर (port->queued_message && tcpm_send_queued_message(port))
		जाओ करोne;

	/* If we were queued due to a delayed state change, update it now */
	अगर (port->delayed_state) अणु
		tcpm_log(port, "state change %s -> %s [delayed %ld ms]",
			 tcpm_states[port->state],
			 tcpm_states[port->delayed_state], port->delay_ms);
		port->prev_state = port->state;
		port->state = port->delayed_state;
		port->delayed_state = INVALID_STATE;
	पूर्ण

	/*
	 * Continue running as दीर्घ as we have (non-delayed) state changes
	 * to make.
	 */
	करो अणु
		prev_state = port->state;
		run_state_machine(port);
		अगर (port->queued_message)
			tcpm_send_queued_message(port);
	पूर्ण जबतक (port->state != prev_state && !port->delayed_state);

करोne:
	port->state_machine_running = false;
	mutex_unlock(&port->lock);
पूर्ण

अटल व्योम _tcpm_cc_change(काष्ठा tcpm_port *port, क्रमागत typec_cc_status cc1,
			    क्रमागत typec_cc_status cc2)
अणु
	क्रमागत typec_cc_status old_cc1, old_cc2;
	क्रमागत tcpm_state new_state;

	old_cc1 = port->cc1;
	old_cc2 = port->cc2;
	port->cc1 = cc1;
	port->cc2 = cc2;

	tcpm_log_क्रमce(port,
		       "CC1: %u -> %u, CC2: %u -> %u [state %s, polarity %d, %s]",
		       old_cc1, cc1, old_cc2, cc2, tcpm_states[port->state],
		       port->polarity,
		       tcpm_port_is_disconnected(port) ? "disconnected"
						       : "connected");

	चयन (port->state) अणु
	हाल TOGGLING:
		अगर (tcpm_port_is_debug(port) || tcpm_port_is_audio(port) ||
		    tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		अन्यथा अगर (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		अवरोध;
	हाल SRC_UNATTACHED:
	हाल ACC_UNATTACHED:
		अगर (tcpm_port_is_debug(port) || tcpm_port_is_audio(port) ||
		    tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		अवरोध;
	हाल SRC_ATTACH_WAIT:
		अगर (tcpm_port_is_disconnected(port) ||
		    tcpm_port_is_audio_detached(port))
			tcpm_set_state(port, SRC_UNATTACHED, 0);
		अन्यथा अगर (cc1 != old_cc1 || cc2 != old_cc2)
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		अवरोध;
	हाल SRC_ATTACHED:
	हाल SRC_SEND_CAPABILITIES:
	हाल SRC_READY:
		अगर (tcpm_port_is_disconnected(port) ||
		    !tcpm_port_is_source(port)) अणु
			अगर (port->port_type == TYPEC_PORT_SRC)
				tcpm_set_state(port, SRC_UNATTACHED, tcpm_रुको_क्रम_disअक्षरge(port));
			अन्यथा
				tcpm_set_state(port, SNK_UNATTACHED, tcpm_रुको_क्रम_disअक्षरge(port));
		पूर्ण
		अवरोध;
	हाल SNK_UNATTACHED:
		अगर (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		अवरोध;
	हाल SNK_ATTACH_WAIT:
		अगर ((port->cc1 == TYPEC_CC_OPEN &&
		     port->cc2 != TYPEC_CC_OPEN) ||
		    (port->cc1 != TYPEC_CC_OPEN &&
		     port->cc2 == TYPEC_CC_OPEN))
			new_state = SNK_DEBOUNCED;
		अन्यथा अगर (tcpm_port_is_disconnected(port))
			new_state = SNK_UNATTACHED;
		अन्यथा
			अवरोध;
		अगर (new_state != port->delayed_state)
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		अवरोध;
	हाल SNK_DEBOUNCED:
		अगर (tcpm_port_is_disconnected(port))
			new_state = SNK_UNATTACHED;
		अन्यथा अगर (port->vbus_present)
			new_state = tcpm_try_src(port) ? SRC_TRY : SNK_ATTACHED;
		अन्यथा
			new_state = SNK_UNATTACHED;
		अगर (new_state != port->delayed_state)
			tcpm_set_state(port, SNK_DEBOUNCED, 0);
		अवरोध;
	हाल SNK_READY:
		/*
		 * EXIT condition is based primarily on vbus disconnect and CC is secondary.
		 * "A port that has entered पूर्णांकo USB PD communications with the Source and
		 * has seen the CC voltage exceed vRd-USB may monitor the CC pin to detect
		 * cable disconnect in addition to monitoring VBUS.
		 *
		 * A port that is monitoring the CC voltage क्रम disconnect (but is not in
		 * the process of a USB PD PR_Swap or USB PD FR_Swap) shall transition to
		 * Unattached.SNK within tSinkDisconnect after the CC voltage reमुख्यs below
		 * vRd-USB क्रम tPDDebounce."
		 *
		 * When set_स्वतः_vbus_disअक्षरge_threshold is enabled, CC pins go
		 * away beक्रमe vbus decays to disconnect threshold. Allow
		 * disconnect to be driven by vbus disconnect when स्वतः vbus
		 * disअक्षरge is enabled.
		 */
		अगर (!port->स्वतः_vbus_disअक्षरge_enabled && tcpm_port_is_disconnected(port))
			tcpm_set_state(port, unattached_state(port), 0);
		अन्यथा अगर (!port->pd_capable &&
			 (cc1 != old_cc1 || cc2 != old_cc2))
			tcpm_set_current_limit(port,
					       tcpm_get_current_limit(port),
					       5000);
		अवरोध;

	हाल AUDIO_ACC_ATTACHED:
		अगर (cc1 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_OPEN)
			tcpm_set_state(port, AUDIO_ACC_DEBOUNCE, 0);
		अवरोध;
	हाल AUDIO_ACC_DEBOUNCE:
		अगर (tcpm_port_is_audio(port))
			tcpm_set_state(port, AUDIO_ACC_ATTACHED, 0);
		अवरोध;

	हाल DEBUG_ACC_ATTACHED:
		अगर (cc1 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_OPEN)
			tcpm_set_state(port, ACC_UNATTACHED, 0);
		अवरोध;

	हाल SNK_TRY:
		/* Do nothing, रुकोing क्रम समयout */
		अवरोध;

	हाल SNK_DISCOVERY:
		/* CC line is unstable, रुको क्रम debounce */
		अगर (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, SNK_DISCOVERY_DEBOUNCE, 0);
		अवरोध;
	हाल SNK_DISCOVERY_DEBOUNCE:
		अवरोध;

	हाल SRC_TRYWAIT:
		/* Hand over to state machine अगर needed */
		अगर (!port->vbus_present && tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT_DEBOUNCE, 0);
		अवरोध;
	हाल SRC_TRYWAIT_DEBOUNCE:
		अगर (port->vbus_present || !tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT, 0);
		अवरोध;
	हाल SNK_TRY_WAIT_DEBOUNCE:
		अगर (!tcpm_port_is_sink(port)) अणु
			port->max_रुको = 0;
			tcpm_set_state(port, SRC_TRYWAIT, 0);
		पूर्ण
		अवरोध;
	हाल SRC_TRY_WAIT:
		अगर (tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRY_DEBOUNCE, 0);
		अवरोध;
	हाल SRC_TRY_DEBOUNCE:
		tcpm_set_state(port, SRC_TRY_WAIT, 0);
		अवरोध;
	हाल SNK_TRYWAIT_DEBOUNCE:
		अगर (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_TRYWAIT_VBUS, 0);
		अवरोध;
	हाल SNK_TRYWAIT_VBUS:
		अगर (!tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_TRYWAIT_DEBOUNCE, 0);
		अवरोध;
	हाल SNK_TRY_WAIT_DEBOUNCE_CHECK_VBUS:
		अगर (!tcpm_port_is_sink(port))
			tcpm_set_state(port, SRC_TRYWAIT, PD_T_TRY_CC_DEBOUNCE);
		अन्यथा
			tcpm_set_state(port, SNK_TRY_WAIT_DEBOUNCE_CHECK_VBUS, 0);
		अवरोध;
	हाल SNK_TRYWAIT:
		/* Do nothing, रुकोing क्रम tCCDebounce */
		अवरोध;
	हाल PR_SWAP_SNK_SRC_SINK_OFF:
	हाल PR_SWAP_SRC_SNK_TRANSITION_OFF:
	हाल PR_SWAP_SRC_SNK_SOURCE_OFF:
	हाल PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED:
	हाल PR_SWAP_SNK_SRC_SOURCE_ON:
		/*
		 * CC state change is expected in PR_SWAP
		 * Ignore it.
		 */
		अवरोध;
	हाल FR_SWAP_SEND:
	हाल FR_SWAP_SEND_TIMEOUT:
	हाल FR_SWAP_SNK_SRC_TRANSITION_TO_OFF:
	हाल FR_SWAP_SNK_SRC_NEW_SINK_READY:
	हाल FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED:
		/* Do nothing, CC change expected */
		अवरोध;

	हाल PORT_RESET:
	हाल PORT_RESET_WAIT_OFF:
		/*
		 * State set back to शेष mode once the समयr completes.
		 * Ignore CC changes here.
		 */
		अवरोध;
	शेष:
		/*
		 * While acting as sink and स्वतः vbus disअक्षरge is enabled, Allow disconnect
		 * to be driven by vbus disconnect.
		 */
		अगर (tcpm_port_is_disconnected(port) && !(port->pwr_role == TYPEC_SINK &&
							 port->स्वतः_vbus_disअक्षरge_enabled))
			tcpm_set_state(port, unattached_state(port), 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _tcpm_pd_vbus_on(काष्ठा tcpm_port *port)
अणु
	tcpm_log_क्रमce(port, "VBUS on");
	port->vbus_present = true;
	/*
	 * When vbus_present is true i.e. Voltage at VBUS is greater than VSAFE5V implicitly
	 * states that vbus is not at VSAFE0V, hence clear the vbus_vsafe0v flag here.
	 */
	port->vbus_vsafe0v = false;

	चयन (port->state) अणु
	हाल SNK_TRANSITION_SINK_VBUS:
		port->explicit_contract = true;
		/* Set the VDM flag ASAP */
		अगर (port->data_role == TYPEC_HOST && port->send_discover)
			port->vdm_sm_running = true;
		tcpm_set_state(port, SNK_READY, 0);
		अवरोध;
	हाल SNK_DISCOVERY:
		tcpm_set_state(port, SNK_DISCOVERY, 0);
		अवरोध;

	हाल SNK_DEBOUNCED:
		tcpm_set_state(port, tcpm_try_src(port) ? SRC_TRY
							: SNK_ATTACHED,
				       0);
		अवरोध;
	हाल SNK_HARD_RESET_WAIT_VBUS:
		tcpm_set_state(port, SNK_HARD_RESET_SINK_ON, 0);
		अवरोध;
	हाल SRC_ATTACHED:
		tcpm_set_state(port, SRC_STARTUP, 0);
		अवरोध;
	हाल SRC_HARD_RESET_VBUS_ON:
		tcpm_set_state(port, SRC_STARTUP, 0);
		अवरोध;

	हाल SNK_TRY:
		/* Do nothing, रुकोing क्रम समयout */
		अवरोध;
	हाल SRC_TRYWAIT:
		/* Do nothing, Waiting क्रम Rd to be detected */
		अवरोध;
	हाल SRC_TRYWAIT_DEBOUNCE:
		tcpm_set_state(port, SRC_TRYWAIT, 0);
		अवरोध;
	हाल SNK_TRY_WAIT_DEBOUNCE:
		/* Do nothing, रुकोing क्रम PD_DEBOUNCE to करो be करोne */
		अवरोध;
	हाल SNK_TRYWAIT:
		/* Do nothing, रुकोing क्रम tCCDebounce */
		अवरोध;
	हाल SNK_TRYWAIT_VBUS:
		अगर (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACHED, 0);
		अवरोध;
	हाल SNK_TRYWAIT_DEBOUNCE:
		/* Do nothing, रुकोing क्रम Rp */
		अवरोध;
	हाल SNK_TRY_WAIT_DEBOUNCE_CHECK_VBUS:
		अगर (port->vbus_present && tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACHED, 0);
		अवरोध;
	हाल SRC_TRY_WAIT:
	हाल SRC_TRY_DEBOUNCE:
		/* Do nothing, रुकोing क्रम sink detection */
		अवरोध;
	हाल FR_SWAP_SEND:
	हाल FR_SWAP_SEND_TIMEOUT:
	हाल FR_SWAP_SNK_SRC_TRANSITION_TO_OFF:
	हाल FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED:
		अगर (port->tcpc->frs_sourcing_vbus)
			port->tcpc->frs_sourcing_vbus(port->tcpc);
		अवरोध;
	हाल FR_SWAP_SNK_SRC_NEW_SINK_READY:
		अगर (port->tcpc->frs_sourcing_vbus)
			port->tcpc->frs_sourcing_vbus(port->tcpc);
		tcpm_set_state(port, FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED, 0);
		अवरोध;

	हाल PORT_RESET:
	हाल PORT_RESET_WAIT_OFF:
		/*
		 * State set back to शेष mode once the समयr completes.
		 * Ignore vbus changes here.
		 */
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _tcpm_pd_vbus_off(काष्ठा tcpm_port *port)
अणु
	tcpm_log_क्रमce(port, "VBUS off");
	port->vbus_present = false;
	port->vbus_never_low = false;
	चयन (port->state) अणु
	हाल SNK_HARD_RESET_SINK_OFF:
		tcpm_set_state(port, SNK_HARD_RESET_WAIT_VBUS, 0);
		अवरोध;
	हाल HARD_RESET_SEND:
		अवरोध;
	हाल SNK_TRY:
		/* Do nothing, रुकोing क्रम समयout */
		अवरोध;
	हाल SRC_TRYWAIT:
		/* Hand over to state machine अगर needed */
		अगर (tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT_DEBOUNCE, 0);
		अवरोध;
	हाल SNK_TRY_WAIT_DEBOUNCE:
		/* Do nothing, रुकोing क्रम PD_DEBOUNCE to करो be करोne */
		अवरोध;
	हाल SNK_TRYWAIT:
	हाल SNK_TRYWAIT_VBUS:
	हाल SNK_TRYWAIT_DEBOUNCE:
		अवरोध;
	हाल SNK_ATTACH_WAIT:
		tcpm_set_state(port, SNK_UNATTACHED, 0);
		अवरोध;

	हाल SNK_NEGOTIATE_CAPABILITIES:
		अवरोध;

	हाल PR_SWAP_SRC_SNK_TRANSITION_OFF:
		tcpm_set_state(port, PR_SWAP_SRC_SNK_SOURCE_OFF, 0);
		अवरोध;

	हाल PR_SWAP_SNK_SRC_SINK_OFF:
		/* Do nothing, expected */
		अवरोध;

	हाल PR_SWAP_SNK_SRC_SOURCE_ON:
		/*
		 * Do nothing when vbus off notअगरication is received.
		 * TCPM can रुको क्रम PD_T_NEWSRC in PR_SWAP_SNK_SRC_SOURCE_ON
		 * क्रम the vbus source to ramp up.
		 */
		अवरोध;

	हाल PORT_RESET_WAIT_OFF:
		tcpm_set_state(port, tcpm_शेष_state(port), 0);
		अवरोध;

	हाल SRC_TRY_WAIT:
	हाल SRC_TRY_DEBOUNCE:
		/* Do nothing, रुकोing क्रम sink detection */
		अवरोध;

	हाल SRC_STARTUP:
	हाल SRC_SEND_CAPABILITIES:
	हाल SRC_SEND_CAPABILITIES_TIMEOUT:
	हाल SRC_NEGOTIATE_CAPABILITIES:
	हाल SRC_TRANSITION_SUPPLY:
	हाल SRC_READY:
	हाल SRC_WAIT_NEW_CAPABILITIES:
		/*
		 * Force to unattached state to re-initiate connection.
		 * DRP port should move to Unattached.SNK instead of Unattached.SRC अगर
		 * sink हटाओd. Although sink removal here is due to source's vbus collapse,
		 * treat it the same way क्रम consistency.
		 */
		अगर (port->port_type == TYPEC_PORT_SRC)
			tcpm_set_state(port, SRC_UNATTACHED, tcpm_रुको_क्रम_disअक्षरge(port));
		अन्यथा
			tcpm_set_state(port, SNK_UNATTACHED, tcpm_रुको_क्रम_disअक्षरge(port));
		अवरोध;

	हाल PORT_RESET:
		/*
		 * State set back to शेष mode once the समयr completes.
		 * Ignore vbus changes here.
		 */
		अवरोध;

	हाल FR_SWAP_SEND:
	हाल FR_SWAP_SEND_TIMEOUT:
	हाल FR_SWAP_SNK_SRC_TRANSITION_TO_OFF:
	हाल FR_SWAP_SNK_SRC_NEW_SINK_READY:
	हाल FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED:
		/* Do nothing, vbus drop expected */
		अवरोध;

	शेष:
		अगर (port->pwr_role == TYPEC_SINK && port->attached)
			tcpm_set_state(port, SNK_UNATTACHED, tcpm_रुको_क्रम_disअक्षरge(port));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _tcpm_pd_vbus_vsafe0v(काष्ठा tcpm_port *port)
अणु
	tcpm_log_क्रमce(port, "VBUS VSAFE0V");
	port->vbus_vsafe0v = true;
	चयन (port->state) अणु
	हाल SRC_HARD_RESET_VBUS_OFF:
		/*
		 * After establishing the vSafe0V voltage condition on VBUS, the Source Shall रुको
		 * tSrcRecover beक्रमe re-applying VCONN and restoring VBUS to vSafe5V.
		 */
		tcpm_set_state(port, SRC_HARD_RESET_VBUS_ON, PD_T_SRC_RECOVER);
		अवरोध;
	हाल SRC_ATTACH_WAIT:
		अगर (tcpm_port_is_source(port))
			tcpm_set_state(port, tcpm_try_snk(port) ? SNK_TRY : SRC_ATTACHED,
				       PD_T_CC_DEBOUNCE);
		अवरोध;
	हाल SRC_STARTUP:
	हाल SRC_SEND_CAPABILITIES:
	हाल SRC_SEND_CAPABILITIES_TIMEOUT:
	हाल SRC_NEGOTIATE_CAPABILITIES:
	हाल SRC_TRANSITION_SUPPLY:
	हाल SRC_READY:
	हाल SRC_WAIT_NEW_CAPABILITIES:
		अगर (port->स्वतः_vbus_disअक्षरge_enabled) अणु
			अगर (port->port_type == TYPEC_PORT_SRC)
				tcpm_set_state(port, SRC_UNATTACHED, 0);
			अन्यथा
				tcpm_set_state(port, SNK_UNATTACHED, 0);
		पूर्ण
		अवरोध;
	शेष:
		अगर (port->pwr_role == TYPEC_SINK && port->स्वतः_vbus_disअक्षरge_enabled)
			tcpm_set_state(port, SNK_UNATTACHED, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _tcpm_pd_hard_reset(काष्ठा tcpm_port *port)
अणु
	tcpm_log_क्रमce(port, "Received hard reset");
	अगर (port->bist_request == BDO_MODE_TESTDATA && port->tcpc->set_bist_data)
		port->tcpc->set_bist_data(port->tcpc, false);

	अगर (port->ams != NONE_AMS)
		port->ams = NONE_AMS;
	अगर (port->hard_reset_count < PD_N_HARD_RESET_COUNT)
		port->ams = HARD_RESET;
	/*
	 * If we keep receiving hard reset requests, executing the hard reset
	 * must have failed. Revert to error recovery अगर that happens.
	 */
	tcpm_set_state(port,
		       port->hard_reset_count < PD_N_HARD_RESET_COUNT ?
				HARD_RESET_START : ERROR_RECOVERY,
		       0);
पूर्ण

अटल व्योम tcpm_pd_event_handler(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा tcpm_port *port = container_of(work, काष्ठा tcpm_port,
					      event_work);
	u32 events;

	mutex_lock(&port->lock);

	spin_lock(&port->pd_event_lock);
	जबतक (port->pd_events) अणु
		events = port->pd_events;
		port->pd_events = 0;
		spin_unlock(&port->pd_event_lock);
		अगर (events & TCPM_RESET_EVENT)
			_tcpm_pd_hard_reset(port);
		अगर (events & TCPM_VBUS_EVENT) अणु
			bool vbus;

			vbus = port->tcpc->get_vbus(port->tcpc);
			अगर (vbus) अणु
				_tcpm_pd_vbus_on(port);
			पूर्ण अन्यथा अणु
				_tcpm_pd_vbus_off(port);
				/*
				 * When TCPC करोes not support detecting vsafe0v voltage level,
				 * treat vbus असलent as vsafe0v. Else invoke is_vbus_vsafe0v
				 * to see अगर vbus has disअक्षरge to VSAFE0V.
				 */
				अगर (!port->tcpc->is_vbus_vsafe0v ||
				    port->tcpc->is_vbus_vsafe0v(port->tcpc))
					_tcpm_pd_vbus_vsafe0v(port);
			पूर्ण
		पूर्ण
		अगर (events & TCPM_CC_EVENT) अणु
			क्रमागत typec_cc_status cc1, cc2;

			अगर (port->tcpc->get_cc(port->tcpc, &cc1, &cc2) == 0)
				_tcpm_cc_change(port, cc1, cc2);
		पूर्ण
		अगर (events & TCPM_FRS_EVENT) अणु
			अगर (port->state == SNK_READY) अणु
				पूर्णांक ret;

				port->upcoming_state = FR_SWAP_SEND;
				ret = tcpm_ams_start(port, FAST_ROLE_SWAP);
				अगर (ret == -EAGAIN)
					port->upcoming_state = INVALID_STATE;
			पूर्ण अन्यथा अणु
				tcpm_log(port, "Discarding FRS_SIGNAL! Not in sink ready");
			पूर्ण
		पूर्ण
		अगर (events & TCPM_SOURCING_VBUS) अणु
			tcpm_log(port, "sourcing vbus");
			/*
			 * In fast role swap हाल TCPC स्वतःnomously sources vbus. Set vbus_source
			 * true as TCPM wouldn't have called tcpm_set_vbus.
			 *
			 * When vbus is sourced on the command on TCPM i.e. TCPM called
			 * tcpm_set_vbus to source vbus, vbus_source would alपढ़ोy be true.
			 */
			port->vbus_source = true;
			_tcpm_pd_vbus_on(port);
		पूर्ण

		spin_lock(&port->pd_event_lock);
	पूर्ण
	spin_unlock(&port->pd_event_lock);
	mutex_unlock(&port->lock);
पूर्ण

व्योम tcpm_cc_change(काष्ठा tcpm_port *port)
अणु
	spin_lock(&port->pd_event_lock);
	port->pd_events |= TCPM_CC_EVENT;
	spin_unlock(&port->pd_event_lock);
	kthपढ़ो_queue_work(port->wq, &port->event_work);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_cc_change);

व्योम tcpm_vbus_change(काष्ठा tcpm_port *port)
अणु
	spin_lock(&port->pd_event_lock);
	port->pd_events |= TCPM_VBUS_EVENT;
	spin_unlock(&port->pd_event_lock);
	kthपढ़ो_queue_work(port->wq, &port->event_work);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_vbus_change);

व्योम tcpm_pd_hard_reset(काष्ठा tcpm_port *port)
अणु
	spin_lock(&port->pd_event_lock);
	port->pd_events = TCPM_RESET_EVENT;
	spin_unlock(&port->pd_event_lock);
	kthपढ़ो_queue_work(port->wq, &port->event_work);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_pd_hard_reset);

व्योम tcpm_sink_frs(काष्ठा tcpm_port *port)
अणु
	spin_lock(&port->pd_event_lock);
	port->pd_events = TCPM_FRS_EVENT;
	spin_unlock(&port->pd_event_lock);
	kthपढ़ो_queue_work(port->wq, &port->event_work);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_sink_frs);

व्योम tcpm_sourcing_vbus(काष्ठा tcpm_port *port)
अणु
	spin_lock(&port->pd_event_lock);
	port->pd_events = TCPM_SOURCING_VBUS;
	spin_unlock(&port->pd_event_lock);
	kthपढ़ो_queue_work(port->wq, &port->event_work);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_sourcing_vbus);

अटल व्योम tcpm_enable_frs_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा tcpm_port *port = container_of(work, काष्ठा tcpm_port, enable_frs);
	पूर्णांक ret;

	mutex_lock(&port->lock);
	/* Not FRS capable */
	अगर (!port->connected || port->port_type != TYPEC_PORT_DRP ||
	    port->pwr_opmode != TYPEC_PWR_MODE_PD ||
	    !port->tcpc->enable_frs ||
	    /* Sink caps queried */
	    port->sink_cap_करोne || port->negotiated_rev < PD_REV30)
		जाओ unlock;

	/* Send when the state machine is idle */
	अगर (port->state != SNK_READY || port->vdm_sm_running || port->send_discover)
		जाओ resched;

	port->upcoming_state = GET_SINK_CAP;
	ret = tcpm_ams_start(port, GET_SINK_CAPABILITIES);
	अगर (ret == -EAGAIN) अणु
		port->upcoming_state = INVALID_STATE;
	पूर्ण अन्यथा अणु
		port->sink_cap_करोne = true;
		जाओ unlock;
	पूर्ण
resched:
	mod_enable_frs_delayed_work(port, GET_SINK_CAP_RETRY_MS);
unlock:
	mutex_unlock(&port->lock);
पूर्ण

अटल व्योम tcpm_send_discover_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा tcpm_port *port = container_of(work, काष्ठा tcpm_port, send_discover_work);

	mutex_lock(&port->lock);
	/* No need to send DISCOVER_IDENTITY anymore */
	अगर (!port->send_discover)
		जाओ unlock;

	/* Retry अगर the port is not idle */
	अगर ((port->state != SRC_READY && port->state != SNK_READY) || port->vdm_sm_running) अणु
		mod_send_discover_delayed_work(port, SEND_DISCOVER_RETRY_MS);
		जाओ unlock;
	पूर्ण

	/* Only send the Message अगर the port is host क्रम PD rev2.0 */
	अगर (port->data_role == TYPEC_HOST || port->negotiated_rev > PD_REV20)
		tcpm_send_vdm(port, USB_SID_PD, CMD_DISCOVER_IDENT, शून्य, 0);

unlock:
	mutex_unlock(&port->lock);
पूर्ण

अटल पूर्णांक tcpm_dr_set(काष्ठा typec_port *p, क्रमागत typec_data_role data)
अणु
	काष्ठा tcpm_port *port = typec_get_drvdata(p);
	पूर्णांक ret;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	अगर (port->typec_caps.data != TYPEC_PORT_DRD) अणु
		ret = -EINVAL;
		जाओ port_unlock;
	पूर्ण
	अगर (port->state != SRC_READY && port->state != SNK_READY) अणु
		ret = -EAGAIN;
		जाओ port_unlock;
	पूर्ण

	अगर (port->data_role == data) अणु
		ret = 0;
		जाओ port_unlock;
	पूर्ण

	/*
	 * XXX
	 * 6.3.9: If an alternate mode is active, a request to swap
	 * alternate modes shall trigger a port reset.
	 * Reject data role swap request in this हाल.
	 */

	अगर (!port->pd_capable) अणु
		/*
		 * If the partner is not PD capable, reset the port to
		 * trigger a role change. This can only work अगर a preferred
		 * role is configured, and अगर it matches the requested role.
		 */
		अगर (port->try_role == TYPEC_NO_PREFERRED_ROLE ||
		    port->try_role == port->pwr_role) अणु
			ret = -EINVAL;
			जाओ port_unlock;
		पूर्ण
		port->non_pd_role_swap = true;
		tcpm_set_state(port, PORT_RESET, 0);
	पूर्ण अन्यथा अणु
		port->upcoming_state = DR_SWAP_SEND;
		ret = tcpm_ams_start(port, DATA_ROLE_SWAP);
		अगर (ret == -EAGAIN) अणु
			port->upcoming_state = INVALID_STATE;
			जाओ port_unlock;
		पूर्ण
	पूर्ण

	port->swap_status = 0;
	port->swap_pending = true;
	reinit_completion(&port->swap_complete);
	mutex_unlock(&port->lock);

	अगर (!रुको_क्रम_completion_समयout(&port->swap_complete,
				msecs_to_jअगरfies(PD_ROLE_SWAP_TIMEOUT)))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = port->swap_status;

	port->non_pd_role_swap = false;
	जाओ swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_pr_set(काष्ठा typec_port *p, क्रमागत typec_role role)
अणु
	काष्ठा tcpm_port *port = typec_get_drvdata(p);
	पूर्णांक ret;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	अगर (port->port_type != TYPEC_PORT_DRP) अणु
		ret = -EINVAL;
		जाओ port_unlock;
	पूर्ण
	अगर (port->state != SRC_READY && port->state != SNK_READY) अणु
		ret = -EAGAIN;
		जाओ port_unlock;
	पूर्ण

	अगर (role == port->pwr_role) अणु
		ret = 0;
		जाओ port_unlock;
	पूर्ण

	port->upcoming_state = PR_SWAP_SEND;
	ret = tcpm_ams_start(port, POWER_ROLE_SWAP);
	अगर (ret == -EAGAIN) अणु
		port->upcoming_state = INVALID_STATE;
		जाओ port_unlock;
	पूर्ण

	port->swap_status = 0;
	port->swap_pending = true;
	reinit_completion(&port->swap_complete);
	mutex_unlock(&port->lock);

	अगर (!रुको_क्रम_completion_समयout(&port->swap_complete,
				msecs_to_jअगरfies(PD_ROLE_SWAP_TIMEOUT)))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = port->swap_status;

	जाओ swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_vconn_set(काष्ठा typec_port *p, क्रमागत typec_role role)
अणु
	काष्ठा tcpm_port *port = typec_get_drvdata(p);
	पूर्णांक ret;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	अगर (port->state != SRC_READY && port->state != SNK_READY) अणु
		ret = -EAGAIN;
		जाओ port_unlock;
	पूर्ण

	अगर (role == port->vconn_role) अणु
		ret = 0;
		जाओ port_unlock;
	पूर्ण

	port->upcoming_state = VCONN_SWAP_SEND;
	ret = tcpm_ams_start(port, VCONN_SWAP);
	अगर (ret == -EAGAIN) अणु
		port->upcoming_state = INVALID_STATE;
		जाओ port_unlock;
	पूर्ण

	port->swap_status = 0;
	port->swap_pending = true;
	reinit_completion(&port->swap_complete);
	mutex_unlock(&port->lock);

	अगर (!रुको_क्रम_completion_समयout(&port->swap_complete,
				msecs_to_jअगरfies(PD_ROLE_SWAP_TIMEOUT)))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = port->swap_status;

	जाओ swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_try_role(काष्ठा typec_port *p, पूर्णांक role)
अणु
	काष्ठा tcpm_port *port = typec_get_drvdata(p);
	काष्ठा tcpc_dev	*tcpc = port->tcpc;
	पूर्णांक ret = 0;

	mutex_lock(&port->lock);
	अगर (tcpc->try_role)
		ret = tcpc->try_role(tcpc, role);
	अगर (!ret)
		port->try_role = role;
	port->try_src_count = 0;
	port->try_snk_count = 0;
	mutex_unlock(&port->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_pps_set_op_curr(काष्ठा tcpm_port *port, u16 req_op_curr)
अणु
	अचिन्हित पूर्णांक target_mw;
	पूर्णांक ret;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	अगर (!port->pps_data.active) अणु
		ret = -EOPNOTSUPP;
		जाओ port_unlock;
	पूर्ण

	अगर (port->state != SNK_READY) अणु
		ret = -EAGAIN;
		जाओ port_unlock;
	पूर्ण

	अगर (req_op_curr > port->pps_data.max_curr) अणु
		ret = -EINVAL;
		जाओ port_unlock;
	पूर्ण

	target_mw = (req_op_curr * port->supply_voltage) / 1000;
	अगर (target_mw < port->operating_snk_mw) अणु
		ret = -EINVAL;
		जाओ port_unlock;
	पूर्ण

	port->upcoming_state = SNK_NEGOTIATE_PPS_CAPABILITIES;
	ret = tcpm_ams_start(port, POWER_NEGOTIATION);
	अगर (ret == -EAGAIN) अणु
		port->upcoming_state = INVALID_STATE;
		जाओ port_unlock;
	पूर्ण

	/* Round करोwn operating current to align with PPS valid steps */
	req_op_curr = req_op_curr - (req_op_curr % RDO_PROG_CURR_MA_STEP);

	reinit_completion(&port->pps_complete);
	port->pps_data.req_op_curr = req_op_curr;
	port->pps_status = 0;
	port->pps_pending = true;
	mutex_unlock(&port->lock);

	अगर (!रुको_क्रम_completion_समयout(&port->pps_complete,
				msecs_to_jअगरfies(PD_PPS_CTRL_TIMEOUT)))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = port->pps_status;

	जाओ swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_pps_set_out_volt(काष्ठा tcpm_port *port, u16 req_out_volt)
अणु
	अचिन्हित पूर्णांक target_mw;
	पूर्णांक ret;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	अगर (!port->pps_data.active) अणु
		ret = -EOPNOTSUPP;
		जाओ port_unlock;
	पूर्ण

	अगर (port->state != SNK_READY) अणु
		ret = -EAGAIN;
		जाओ port_unlock;
	पूर्ण

	अगर (req_out_volt < port->pps_data.min_volt ||
	    req_out_volt > port->pps_data.max_volt) अणु
		ret = -EINVAL;
		जाओ port_unlock;
	पूर्ण

	target_mw = (port->current_limit * req_out_volt) / 1000;
	अगर (target_mw < port->operating_snk_mw) अणु
		ret = -EINVAL;
		जाओ port_unlock;
	पूर्ण

	port->upcoming_state = SNK_NEGOTIATE_PPS_CAPABILITIES;
	ret = tcpm_ams_start(port, POWER_NEGOTIATION);
	अगर (ret == -EAGAIN) अणु
		port->upcoming_state = INVALID_STATE;
		जाओ port_unlock;
	पूर्ण

	/* Round करोwn output voltage to align with PPS valid steps */
	req_out_volt = req_out_volt - (req_out_volt % RDO_PROG_VOLT_MV_STEP);

	reinit_completion(&port->pps_complete);
	port->pps_data.req_out_volt = req_out_volt;
	port->pps_status = 0;
	port->pps_pending = true;
	mutex_unlock(&port->lock);

	अगर (!रुको_क्रम_completion_समयout(&port->pps_complete,
				msecs_to_jअगरfies(PD_PPS_CTRL_TIMEOUT)))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = port->pps_status;

	जाओ swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_pps_activate(काष्ठा tcpm_port *port, bool activate)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	अगर (!port->pps_data.supported) अणु
		ret = -EOPNOTSUPP;
		जाओ port_unlock;
	पूर्ण

	/* Trying to deactivate PPS when alपढ़ोy deactivated so just bail */
	अगर (!port->pps_data.active && !activate)
		जाओ port_unlock;

	अगर (port->state != SNK_READY) अणु
		ret = -EAGAIN;
		जाओ port_unlock;
	पूर्ण

	अगर (activate)
		port->upcoming_state = SNK_NEGOTIATE_PPS_CAPABILITIES;
	अन्यथा
		port->upcoming_state = SNK_NEGOTIATE_CAPABILITIES;
	ret = tcpm_ams_start(port, POWER_NEGOTIATION);
	अगर (ret == -EAGAIN) अणु
		port->upcoming_state = INVALID_STATE;
		जाओ port_unlock;
	पूर्ण

	reinit_completion(&port->pps_complete);
	port->pps_status = 0;
	port->pps_pending = true;

	/* Trigger PPS request or move back to standard PDO contract */
	अगर (activate) अणु
		port->pps_data.req_out_volt = port->supply_voltage;
		port->pps_data.req_op_curr = port->current_limit;
	पूर्ण
	mutex_unlock(&port->lock);

	अगर (!रुको_क्रम_completion_समयout(&port->pps_complete,
				msecs_to_jअगरfies(PD_PPS_CTRL_TIMEOUT)))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = port->pps_status;

	जाओ swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);

	वापस ret;
पूर्ण

अटल व्योम tcpm_init(काष्ठा tcpm_port *port)
अणु
	क्रमागत typec_cc_status cc1, cc2;

	port->tcpc->init(port->tcpc);

	tcpm_reset_port(port);

	/*
	 * XXX
	 * Should possibly रुको क्रम VBUS to settle अगर it was enabled locally
	 * since tcpm_reset_port() will disable VBUS.
	 */
	port->vbus_present = port->tcpc->get_vbus(port->tcpc);
	अगर (port->vbus_present)
		port->vbus_never_low = true;

	/*
	 * 1. When vbus_present is true, voltage on VBUS is alपढ़ोy at VSAFE5V.
	 * So implicitly vbus_vsafe0v = false.
	 *
	 * 2. When vbus_present is false and TCPC करोes NOT support querying
	 * vsafe0v status, then, it's best to assume vbus is at VSAFE0V i.e.
	 * vbus_vsafe0v is true.
	 *
	 * 3. When vbus_present is false and TCPC करोes support querying vsafe0v,
	 * then, query tcpc क्रम vsafe0v status.
	 */
	अगर (port->vbus_present)
		port->vbus_vsafe0v = false;
	अन्यथा अगर (!port->tcpc->is_vbus_vsafe0v)
		port->vbus_vsafe0v = true;
	अन्यथा
		port->vbus_vsafe0v = port->tcpc->is_vbus_vsafe0v(port->tcpc);

	tcpm_set_state(port, tcpm_शेष_state(port), 0);

	अगर (port->tcpc->get_cc(port->tcpc, &cc1, &cc2) == 0)
		_tcpm_cc_change(port, cc1, cc2);

	/*
	 * Some adapters need a clean slate at startup, and won't recover
	 * otherwise. So करो not try to be fancy and क्रमce a clean disconnect.
	 */
	tcpm_set_state(port, PORT_RESET, 0);
पूर्ण

अटल पूर्णांक tcpm_port_type_set(काष्ठा typec_port *p, क्रमागत typec_port_type type)
अणु
	काष्ठा tcpm_port *port = typec_get_drvdata(p);

	mutex_lock(&port->lock);
	अगर (type == port->port_type)
		जाओ port_unlock;

	port->port_type = type;

	अगर (!port->connected) अणु
		tcpm_set_state(port, PORT_RESET, 0);
	पूर्ण अन्यथा अगर (type == TYPEC_PORT_SNK) अणु
		अगर (!(port->pwr_role == TYPEC_SINK &&
		      port->data_role == TYPEC_DEVICE))
			tcpm_set_state(port, PORT_RESET, 0);
	पूर्ण अन्यथा अगर (type == TYPEC_PORT_SRC) अणु
		अगर (!(port->pwr_role == TYPEC_SOURCE &&
		      port->data_role == TYPEC_HOST))
			tcpm_set_state(port, PORT_RESET, 0);
	पूर्ण

port_unlock:
	mutex_unlock(&port->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा typec_operations tcpm_ops = अणु
	.try_role = tcpm_try_role,
	.dr_set = tcpm_dr_set,
	.pr_set = tcpm_pr_set,
	.vconn_set = tcpm_vconn_set,
	.port_type_set = tcpm_port_type_set
पूर्ण;

व्योम tcpm_tcpc_reset(काष्ठा tcpm_port *port)
अणु
	mutex_lock(&port->lock);
	/* XXX: Maपूर्णांकain PD connection अगर possible? */
	tcpm_init(port);
	mutex_unlock(&port->lock);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_tcpc_reset);

अटल पूर्णांक tcpm_fw_get_caps(काष्ठा tcpm_port *port,
			    काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर अक्षर *cap_str;
	पूर्णांक ret;
	u32 mw, frs_current;

	अगर (!fwnode)
		वापस -EINVAL;

	/*
	 * This fwnode has a "compatible" property, but is never populated as a
	 * काष्ठा device. Instead we simply parse it to पढ़ो the properties.
	 * This it अवरोधs fw_devlink=on. To मुख्यtain backward compatibility
	 * with existing DT files, we work around this by deleting any
	 * fwnode_links to/from this fwnode.
	 */
	fw_devlink_purge_असलent_suppliers(fwnode);

	/* USB data support is optional */
	ret = fwnode_property_पढ़ो_string(fwnode, "data-role", &cap_str);
	अगर (ret == 0) अणु
		ret = typec_find_port_data_role(cap_str);
		अगर (ret < 0)
			वापस ret;
		port->typec_caps.data = ret;
	पूर्ण

	ret = fwnode_property_पढ़ो_string(fwnode, "power-role", &cap_str);
	अगर (ret < 0)
		वापस ret;

	ret = typec_find_port_घातer_role(cap_str);
	अगर (ret < 0)
		वापस ret;
	port->typec_caps.type = ret;
	port->port_type = port->typec_caps.type;

	port->slow_अक्षरger_loop = fwnode_property_पढ़ो_bool(fwnode, "slow-charger-loop");
	अगर (port->port_type == TYPEC_PORT_SNK)
		जाओ sink;

	/* Get source pकरोs */
	ret = fwnode_property_count_u32(fwnode, "source-pdos");
	अगर (ret <= 0)
		वापस -EINVAL;

	port->nr_src_pकरो = min(ret, PDO_MAX_OBJECTS);
	ret = fwnode_property_पढ़ो_u32_array(fwnode, "source-pdos",
					     port->src_pकरो, port->nr_src_pकरो);
	अगर ((ret < 0) || tcpm_validate_caps(port, port->src_pकरो,
					    port->nr_src_pकरो))
		वापस -EINVAL;

	अगर (port->port_type == TYPEC_PORT_SRC)
		वापस 0;

	/* Get the preferred घातer role क्रम DRP */
	ret = fwnode_property_पढ़ो_string(fwnode, "try-power-role", &cap_str);
	अगर (ret < 0)
		वापस ret;

	port->typec_caps.prefer_role = typec_find_घातer_role(cap_str);
	अगर (port->typec_caps.prefer_role < 0)
		वापस -EINVAL;
sink:
	/* Get sink pकरोs */
	ret = fwnode_property_count_u32(fwnode, "sink-pdos");
	अगर (ret <= 0)
		वापस -EINVAL;

	port->nr_snk_pकरो = min(ret, PDO_MAX_OBJECTS);
	ret = fwnode_property_पढ़ो_u32_array(fwnode, "sink-pdos",
					     port->snk_pकरो, port->nr_snk_pकरो);
	अगर ((ret < 0) || tcpm_validate_caps(port, port->snk_pकरो,
					    port->nr_snk_pकरो))
		वापस -EINVAL;

	अगर (fwnode_property_पढ़ो_u32(fwnode, "op-sink-microwatt", &mw) < 0)
		वापस -EINVAL;
	port->operating_snk_mw = mw / 1000;

	port->self_घातered = fwnode_property_पढ़ो_bool(fwnode, "self-powered");

	/* FRS can only be supported byb DRP ports */
	अगर (port->port_type == TYPEC_PORT_DRP) अणु
		ret = fwnode_property_पढ़ो_u32(fwnode, "new-source-frs-typec-current",
					       &frs_current);
		अगर (ret >= 0 && frs_current <= FRS_5V_3A)
			port->new_source_frs_current = frs_current;
	पूर्ण

	/* sink-vकरोs is optional */
	ret = fwnode_property_count_u32(fwnode, "sink-vdos");
	अगर (ret < 0)
		ret = 0;

	port->nr_snk_vकरो = min(ret, VDO_MAX_OBJECTS);
	अगर (port->nr_snk_vकरो) अणु
		ret = fwnode_property_पढ़ो_u32_array(fwnode, "sink-vdos",
						     port->snk_vकरो,
						     port->nr_snk_vकरो);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* If sink-vकरोs is found, sink-vकरोs-v1 is expected क्रम backward compatibility. */
	अगर (port->nr_snk_vकरो) अणु
		ret = fwnode_property_count_u32(fwnode, "sink-vdos-v1");
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret == 0)
			वापस -ENODATA;

		port->nr_snk_vकरो_v1 = min(ret, VDO_MAX_OBJECTS);
		ret = fwnode_property_पढ़ो_u32_array(fwnode, "sink-vdos-v1",
						     port->snk_vकरो_v1,
						     port->nr_snk_vकरो_v1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Power Supply access to expose source घातer inक्रमmation */
क्रमागत tcpm_psy_online_states अणु
	TCPM_PSY_OFFLINE = 0,
	TCPM_PSY_FIXED_ONLINE,
	TCPM_PSY_PROG_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property tcpm_psy_props[] = अणु
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल पूर्णांक tcpm_psy_get_online(काष्ठा tcpm_port *port,
			       जोड़ घातer_supply_propval *val)
अणु
	अगर (port->vbus_अक्षरge) अणु
		अगर (port->pps_data.active)
			val->पूर्णांकval = TCPM_PSY_PROG_ONLINE;
		अन्यथा
			val->पूर्णांकval = TCPM_PSY_FIXED_ONLINE;
	पूर्ण अन्यथा अणु
		val->पूर्णांकval = TCPM_PSY_OFFLINE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_psy_get_voltage_min(काष्ठा tcpm_port *port,
				    जोड़ घातer_supply_propval *val)
अणु
	अगर (port->pps_data.active)
		val->पूर्णांकval = port->pps_data.min_volt * 1000;
	अन्यथा
		val->पूर्णांकval = port->supply_voltage * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_psy_get_voltage_max(काष्ठा tcpm_port *port,
				    जोड़ घातer_supply_propval *val)
अणु
	अगर (port->pps_data.active)
		val->पूर्णांकval = port->pps_data.max_volt * 1000;
	अन्यथा
		val->पूर्णांकval = port->supply_voltage * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_psy_get_voltage_now(काष्ठा tcpm_port *port,
				    जोड़ घातer_supply_propval *val)
अणु
	val->पूर्णांकval = port->supply_voltage * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_psy_get_current_max(काष्ठा tcpm_port *port,
				    जोड़ घातer_supply_propval *val)
अणु
	अगर (port->pps_data.active)
		val->पूर्णांकval = port->pps_data.max_curr * 1000;
	अन्यथा
		val->पूर्णांकval = port->current_limit * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_psy_get_current_now(काष्ठा tcpm_port *port,
				    जोड़ घातer_supply_propval *val)
अणु
	val->पूर्णांकval = port->current_limit * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_psy_get_prop(काष्ठा घातer_supply *psy,
			     क्रमागत घातer_supply_property psp,
			     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा tcpm_port *port = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		val->पूर्णांकval = port->usb_type;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = tcpm_psy_get_online(port, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		ret = tcpm_psy_get_voltage_min(port, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		ret = tcpm_psy_get_voltage_max(port, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = tcpm_psy_get_voltage_now(port, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		ret = tcpm_psy_get_current_max(port, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = tcpm_psy_get_current_now(port, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_psy_set_online(काष्ठा tcpm_port *port,
			       स्थिर जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;

	चयन (val->पूर्णांकval) अणु
	हाल TCPM_PSY_FIXED_ONLINE:
		ret = tcpm_pps_activate(port, false);
		अवरोध;
	हाल TCPM_PSY_PROG_ONLINE:
		ret = tcpm_pps_activate(port, true);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_psy_set_prop(काष्ठा घातer_supply *psy,
			     क्रमागत घातer_supply_property psp,
			     स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा tcpm_port *port = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = tcpm_psy_set_online(port, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (val->पूर्णांकval < port->pps_data.min_volt * 1000 ||
		    val->पूर्णांकval > port->pps_data.max_volt * 1000)
			ret = -EINVAL;
		अन्यथा
			ret = tcpm_pps_set_out_volt(port, val->पूर्णांकval / 1000);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		अगर (val->पूर्णांकval > port->pps_data.max_curr * 1000)
			ret = -EINVAL;
		अन्यथा
			ret = tcpm_pps_set_op_curr(port, val->पूर्णांकval / 1000);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	घातer_supply_changed(port->psy);
	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_psy_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल क्रमागत घातer_supply_usb_type tcpm_psy_usb_types[] = अणु
	POWER_SUPPLY_USB_TYPE_C,
	POWER_SUPPLY_USB_TYPE_PD,
	POWER_SUPPLY_USB_TYPE_PD_PPS,
पूर्ण;

अटल स्थिर अक्षर *tcpm_psy_name_prefix = "tcpm-source-psy-";

अटल पूर्णांक devm_tcpm_psy_रेजिस्टर(काष्ठा tcpm_port *port)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	स्थिर अक्षर *port_dev_name = dev_name(port->dev);
	माप_प्रकार psy_name_len = म_माप(tcpm_psy_name_prefix) +
				     म_माप(port_dev_name) + 1;
	अक्षर *psy_name;

	psy_cfg.drv_data = port;
	psy_cfg.fwnode = dev_fwnode(port->dev);
	psy_name = devm_kzalloc(port->dev, psy_name_len, GFP_KERNEL);
	अगर (!psy_name)
		वापस -ENOMEM;

	snम_लिखो(psy_name, psy_name_len, "%s%s", tcpm_psy_name_prefix,
		 port_dev_name);
	port->psy_desc.name = psy_name;
	port->psy_desc.type = POWER_SUPPLY_TYPE_USB;
	port->psy_desc.usb_types = tcpm_psy_usb_types;
	port->psy_desc.num_usb_types = ARRAY_SIZE(tcpm_psy_usb_types);
	port->psy_desc.properties = tcpm_psy_props;
	port->psy_desc.num_properties = ARRAY_SIZE(tcpm_psy_props);
	port->psy_desc.get_property = tcpm_psy_get_prop;
	port->psy_desc.set_property = tcpm_psy_set_prop;
	port->psy_desc.property_is_ग_लिखोable = tcpm_psy_prop_ग_लिखोable;

	port->usb_type = POWER_SUPPLY_USB_TYPE_C;

	port->psy = devm_घातer_supply_रेजिस्टर(port->dev, &port->psy_desc,
					       &psy_cfg);

	वापस PTR_ERR_OR_ZERO(port->psy);
पूर्ण

अटल क्रमागत hrसमयr_restart state_machine_समयr_handler(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tcpm_port *port = container_of(समयr, काष्ठा tcpm_port, state_machine_समयr);

	kthपढ़ो_queue_work(port->wq, &port->state_machine);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल क्रमागत hrसमयr_restart vdm_state_machine_समयr_handler(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tcpm_port *port = container_of(समयr, काष्ठा tcpm_port, vdm_state_machine_समयr);

	kthपढ़ो_queue_work(port->wq, &port->vdm_state_machine);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल क्रमागत hrसमयr_restart enable_frs_समयr_handler(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tcpm_port *port = container_of(समयr, काष्ठा tcpm_port, enable_frs_समयr);

	kthपढ़ो_queue_work(port->wq, &port->enable_frs);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल क्रमागत hrसमयr_restart send_discover_समयr_handler(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tcpm_port *port = container_of(समयr, काष्ठा tcpm_port, send_discover_समयr);

	kthपढ़ो_queue_work(port->wq, &port->send_discover_work);
	वापस HRTIMER_NORESTART;
पूर्ण

काष्ठा tcpm_port *tcpm_रेजिस्टर_port(काष्ठा device *dev, काष्ठा tcpc_dev *tcpc)
अणु
	काष्ठा tcpm_port *port;
	पूर्णांक err;

	अगर (!dev || !tcpc ||
	    !tcpc->get_vbus || !tcpc->set_cc || !tcpc->get_cc ||
	    !tcpc->set_polarity || !tcpc->set_vconn || !tcpc->set_vbus ||
	    !tcpc->set_pd_rx || !tcpc->set_roles || !tcpc->pd_transmit)
		वापस ERR_PTR(-EINVAL);

	port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस ERR_PTR(-ENOMEM);

	port->dev = dev;
	port->tcpc = tcpc;

	mutex_init(&port->lock);
	mutex_init(&port->swap_lock);

	port->wq = kthपढ़ो_create_worker(0, dev_name(dev));
	अगर (IS_ERR(port->wq))
		वापस ERR_CAST(port->wq);
	sched_set_fअगरo(port->wq->task);

	kthपढ़ो_init_work(&port->state_machine, tcpm_state_machine_work);
	kthपढ़ो_init_work(&port->vdm_state_machine, vdm_state_machine_work);
	kthपढ़ो_init_work(&port->event_work, tcpm_pd_event_handler);
	kthपढ़ो_init_work(&port->enable_frs, tcpm_enable_frs_work);
	kthपढ़ो_init_work(&port->send_discover_work, tcpm_send_discover_work);
	hrसमयr_init(&port->state_machine_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	port->state_machine_समयr.function = state_machine_समयr_handler;
	hrसमयr_init(&port->vdm_state_machine_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	port->vdm_state_machine_समयr.function = vdm_state_machine_समयr_handler;
	hrसमयr_init(&port->enable_frs_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	port->enable_frs_समयr.function = enable_frs_समयr_handler;
	hrसमयr_init(&port->send_discover_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	port->send_discover_समयr.function = send_discover_समयr_handler;

	spin_lock_init(&port->pd_event_lock);

	init_completion(&port->tx_complete);
	init_completion(&port->swap_complete);
	init_completion(&port->pps_complete);
	tcpm_debugfs_init(port);

	err = tcpm_fw_get_caps(port, tcpc->fwnode);
	अगर (err < 0)
		जाओ out_destroy_wq;

	port->try_role = port->typec_caps.prefer_role;

	port->typec_caps.fwnode = tcpc->fwnode;
	port->typec_caps.revision = 0x0120;	/* Type-C spec release 1.2 */
	port->typec_caps.pd_revision = 0x0300;	/* USB-PD spec release 3.0 */
	port->typec_caps.svdm_version = SVDM_VER_2_0;
	port->typec_caps.driver_data = port;
	port->typec_caps.ops = &tcpm_ops;
	port->typec_caps.orientation_aware = 1;

	port->partner_desc.identity = &port->partner_ident;
	port->port_type = port->typec_caps.type;

	port->role_sw = usb_role_चयन_get(port->dev);
	अगर (IS_ERR(port->role_sw)) अणु
		err = PTR_ERR(port->role_sw);
		जाओ out_destroy_wq;
	पूर्ण

	err = devm_tcpm_psy_रेजिस्टर(port);
	अगर (err)
		जाओ out_role_sw_put;
	घातer_supply_changed(port->psy);

	port->typec_port = typec_रेजिस्टर_port(port->dev, &port->typec_caps);
	अगर (IS_ERR(port->typec_port)) अणु
		err = PTR_ERR(port->typec_port);
		जाओ out_role_sw_put;
	पूर्ण

	typec_port_रेजिस्टर_alपंचांगodes(port->typec_port,
				     &tcpm_alपंचांगode_ops, port,
				     port->port_alपंचांगode, ALTMODE_DISCOVERY_MAX);

	mutex_lock(&port->lock);
	tcpm_init(port);
	mutex_unlock(&port->lock);

	tcpm_log(port, "%s: registered", dev_name(dev));
	वापस port;

out_role_sw_put:
	usb_role_चयन_put(port->role_sw);
out_destroy_wq:
	tcpm_debugfs_निकास(port);
	kthपढ़ो_destroy_worker(port->wq);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_रेजिस्टर_port);

व्योम tcpm_unरेजिस्टर_port(काष्ठा tcpm_port *port)
अणु
	पूर्णांक i;

	hrसमयr_cancel(&port->send_discover_समयr);
	hrसमयr_cancel(&port->enable_frs_समयr);
	hrसमयr_cancel(&port->vdm_state_machine_समयr);
	hrसमयr_cancel(&port->state_machine_समयr);

	tcpm_reset_port(port);
	क्रम (i = 0; i < ARRAY_SIZE(port->port_alपंचांगode); i++)
		typec_unरेजिस्टर_alपंचांगode(port->port_alपंचांगode[i]);
	typec_unरेजिस्टर_port(port->typec_port);
	usb_role_चयन_put(port->role_sw);
	tcpm_debugfs_निकास(port);
	kthपढ़ो_destroy_worker(port->wq);
पूर्ण
EXPORT_SYMBOL_GPL(tcpm_unरेजिस्टर_port);

MODULE_AUTHOR("Guenter Roeck <groeck@chromium.org>");
MODULE_DESCRIPTION("USB Type-C Port Manager");
MODULE_LICENSE("GPL");
