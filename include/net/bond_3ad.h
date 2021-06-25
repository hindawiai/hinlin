<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _NET_BOND_3AD_H
#घोषणा _NET_BOND_3AD_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>

/* General definitions */
#घोषणा PKT_TYPE_LACPDU         cpu_to_be16(ETH_P_SLOW)
#घोषणा AD_TIMER_INTERVAL       100 /*msec*/

#घोषणा MULTICAST_LACPDU_ADDR    अणु0x01, 0x80, 0xC2, 0x00, 0x00, 0x02पूर्ण

#घोषणा AD_LACP_SLOW 0
#घोषणा AD_LACP_FAST 1

प्रकार काष्ठा mac_addr अणु
	u8 mac_addr_value[ETH_ALEN];
पूर्ण __packed mac_addr_t;

क्रमागत अणु
	BOND_AD_STABLE = 0,
	BOND_AD_BANDWIDTH = 1,
	BOND_AD_COUNT = 2,
पूर्ण;

/* rx machine states(43.4.11 in the 802.3ad standard) */
प्रकार क्रमागत अणु
	AD_RX_DUMMY,
	AD_RX_INITIALIZE,	/* rx Machine */
	AD_RX_PORT_DISABLED,	/* rx Machine */
	AD_RX_LACP_DISABLED,	/* rx Machine */
	AD_RX_EXPIRED,		/* rx Machine */
	AD_RX_DEFAULTED,	/* rx Machine */
	AD_RX_CURRENT		/* rx Machine */
पूर्ण rx_states_t;

/* periodic machine states(43.4.12 in the 802.3ad standard) */
प्रकार क्रमागत अणु
	AD_PERIODIC_DUMMY,
	AD_NO_PERIODIC,		/* periodic machine */
	AD_FAST_PERIODIC,	/* periodic machine */
	AD_SLOW_PERIODIC,	/* periodic machine */
	AD_PERIODIC_TX		/* periodic machine */
पूर्ण periodic_states_t;

/* mux machine states(43.4.13 in the 802.3ad standard) */
प्रकार क्रमागत अणु
	AD_MUX_DUMMY,
	AD_MUX_DETACHED,	/* mux machine */
	AD_MUX_WAITING,		/* mux machine */
	AD_MUX_ATTACHED,	/* mux machine */
	AD_MUX_COLLECTING_DISTRIBUTING	/* mux machine */
पूर्ण mux_states_t;

/* tx machine states(43.4.15 in the 802.3ad standard) */
प्रकार क्रमागत अणु
	AD_TX_DUMMY,
	AD_TRANSMIT		/* tx Machine */
पूर्ण tx_states_t;

/* churn machine states(43.4.17 in the 802.3ad standard) */
प्रकार क्रमागत अणु
	 AD_CHURN_MONITOR, /* monitoring क्रम churn */
	 AD_CHURN,         /* churn detected (error) */
	 AD_NO_CHURN       /* no churn (no error) */
पूर्ण churn_state_t;

/* rx indication types */
प्रकार क्रमागत अणु
	AD_TYPE_LACPDU = 1,	/* type lacpdu */
	AD_TYPE_MARKER		/* type marker */
पूर्ण pdu_type_t;

/* rx marker indication types */
प्रकार क्रमागत अणु
	AD_MARKER_INFORMATION_SUBTYPE = 1,	/* marker imक्रमmation subtype */
	AD_MARKER_RESPONSE_SUBTYPE		/* marker response subtype */
पूर्ण bond_marker_subtype_t;

/* समयrs types(43.4.9 in the 802.3ad standard) */
प्रकार क्रमागत अणु
	AD_CURRENT_WHILE_TIMER,
	AD_ACTOR_CHURN_TIMER,
	AD_PERIODIC_TIMER,
	AD_PARTNER_CHURN_TIMER,
	AD_WAIT_WHILE_TIMER
पूर्ण ad_समयrs_t;

#आशय pack(1)

/* Link Aggregation Control Protocol(LACP) data unit काष्ठाure(43.4.2.2 in the 802.3ad standard) */
प्रकार काष्ठा lacpdu अणु
	u8 subtype;		/* = LACP(= 0x01) */
	u8 version_number;
	u8 tlv_type_actor_info;	/* = actor inक्रमmation(type/length/value) */
	u8 actor_inक्रमmation_length;	/* = 20 */
	__be16 actor_प्रणाली_priority;
	काष्ठा mac_addr actor_प्रणाली;
	__be16 actor_key;
	__be16 actor_port_priority;
	__be16 actor_port;
	u8 actor_state;
	u8 reserved_3_1[3];		/* = 0 */
	u8 tlv_type_partner_info;	/* = partner inक्रमmation */
	u8 partner_inक्रमmation_length;	/* = 20 */
	__be16 partner_प्रणाली_priority;
	काष्ठा mac_addr partner_प्रणाली;
	__be16 partner_key;
	__be16 partner_port_priority;
	__be16 partner_port;
	u8 partner_state;
	u8 reserved_3_2[3];		/* = 0 */
	u8 tlv_type_collector_info;	/* = collector inक्रमmation */
	u8 collector_inक्रमmation_length;/* = 16 */
	__be16 collector_max_delay;
	u8 reserved_12[12];
	u8 tlv_type_terminator;		/* = terminator */
	u8 terminator_length;		/* = 0 */
	u8 reserved_50[50];		/* = 0 */
पूर्ण __packed lacpdu_t;

प्रकार काष्ठा lacpdu_header अणु
	काष्ठा ethhdr hdr;
	काष्ठा lacpdu lacpdu;
पूर्ण __packed lacpdu_header_t;

/* Marker Protocol Data Unit(PDU) काष्ठाure(43.5.3.2 in the 802.3ad standard) */
प्रकार काष्ठा bond_marker अणु
	u8 subtype;		/* = 0x02  (marker PDU) */
	u8 version_number;	/* = 0x01 */
	u8 tlv_type;		/* = 0x01  (marker inक्रमmation) */
	/* = 0x02  (marker response inक्रमmation) */
	u8 marker_length;	/* = 0x16 */
	u16 requester_port;	/* The number asचिन्हित to the port by the requester */
	काष्ठा mac_addr requester_प्रणाली;	/* The requester's प्रणाली id */
	u32 requester_transaction_id;		/* The transaction id allocated by the requester, */
	u16 pad;		/* = 0 */
	u8 tlv_type_terminator;	/* = 0x00 */
	u8 terminator_length;	/* = 0x00 */
	u8 reserved_90[90];	/* = 0 */
पूर्ण __packed bond_marker_t;

प्रकार काष्ठा bond_marker_header अणु
	काष्ठा ethhdr hdr;
	काष्ठा bond_marker marker;
पूर्ण __packed bond_marker_header_t;

#आशय pack()

काष्ठा slave;
काष्ठा bonding;
काष्ठा ad_info;
काष्ठा port;

#अगर_घोषित __ia64__
#आशय pack(8)
#पूर्ण_अगर

काष्ठा bond_3ad_stats अणु
	atomic64_t lacpdu_rx;
	atomic64_t lacpdu_tx;
	atomic64_t lacpdu_unknown_rx;
	atomic64_t lacpdu_illegal_rx;

	atomic64_t marker_rx;
	atomic64_t marker_tx;
	atomic64_t marker_resp_rx;
	atomic64_t marker_resp_tx;
	atomic64_t marker_unknown_rx;
पूर्ण;

/* aggregator काष्ठाure(43.4.5 in the 802.3ad standard) */
प्रकार काष्ठा aggregator अणु
	काष्ठा mac_addr aggregator_mac_address;
	u16 aggregator_identअगरier;
	bool is_inभागidual;
	u16 actor_admin_aggregator_key;
	u16 actor_oper_aggregator_key;
	काष्ठा mac_addr partner_प्रणाली;
	u16 partner_प्रणाली_priority;
	u16 partner_oper_aggregator_key;
	u16 receive_state;	/* BOOLEAN */
	u16 transmit_state;	/* BOOLEAN */
	काष्ठा port *lag_ports;
	/* ****** PRIVATE PARAMETERS ****** */
	काष्ठा slave *slave;	/* poपूर्णांकer to the bond slave that this aggregator beदीर्घs to */
	u16 is_active;		/* BOOLEAN. Indicates अगर this aggregator is active */
	u16 num_of_ports;
पूर्ण aggregator_t;

काष्ठा port_params अणु
	काष्ठा mac_addr प्रणाली;
	u16 प्रणाली_priority;
	u16 key;
	u16 port_number;
	u16 port_priority;
	u16 port_state;
पूर्ण;

/* port काष्ठाure(43.4.6 in the 802.3ad standard) */
प्रकार काष्ठा port अणु
	u16 actor_port_number;
	u16 actor_port_priority;
	काष्ठा mac_addr actor_प्रणाली;	/* This parameter is added here although it is not specअगरied in the standard, just क्रम simplअगरication */
	u16 actor_प्रणाली_priority;	/* This parameter is added here although it is not specअगरied in the standard, just क्रम simplअगरication */
	u16 actor_port_aggregator_identअगरier;
	bool ntt;
	u16 actor_admin_port_key;
	u16 actor_oper_port_key;
	u8 actor_admin_port_state;
	u8 actor_oper_port_state;

	काष्ठा port_params partner_admin;
	काष्ठा port_params partner_oper;

	bool is_enabled;

	/* ****** PRIVATE PARAMETERS ****** */
	u16 sm_vars;		/* all state machines variables क्रम this port */
	rx_states_t sm_rx_state;	/* state machine rx state */
	u16 sm_rx_समयr_counter;	/* state machine rx समयr counter */
	periodic_states_t sm_periodic_state;	/* state machine periodic state */
	u16 sm_periodic_समयr_counter;	/* state machine periodic समयr counter */
	mux_states_t sm_mux_state;	/* state machine mux state */
	u16 sm_mux_समयr_counter;	/* state machine mux समयr counter */
	tx_states_t sm_tx_state;	/* state machine tx state */
	u16 sm_tx_समयr_counter;	/* state machine tx समयr counter(allways on - enter to transmit state 3 समय per second) */
	u16 sm_churn_actor_समयr_counter;
	u16 sm_churn_partner_समयr_counter;
	u32 churn_actor_count;
	u32 churn_partner_count;
	churn_state_t sm_churn_actor_state;
	churn_state_t sm_churn_partner_state;
	काष्ठा slave *slave;		/* poपूर्णांकer to the bond slave that this port beदीर्घs to */
	काष्ठा aggregator *aggregator;	/* poपूर्णांकer to an aggregator that this port related to */
	काष्ठा port *next_port_in_aggregator;	/* Next port on the linked list of the parent aggregator */
	u32 transaction_id;		/* continuous number क्रम identअगरication of Marker PDU's; */
	काष्ठा lacpdu lacpdu;		/* the lacpdu that will be sent क्रम this port */
पूर्ण port_t;

/* प्रणाली काष्ठाure */
काष्ठा ad_प्रणाली अणु
	u16 sys_priority;
	काष्ठा mac_addr sys_mac_addr;
पूर्ण;

#अगर_घोषित __ia64__
#आशय pack()
#पूर्ण_अगर

/* ========== AD Exported काष्ठाures to the मुख्य bonding code ========== */
#घोषणा BOND_AD_INFO(bond)   ((bond)->ad_info)
#घोषणा SLAVE_AD_INFO(slave) ((slave)->ad_info)

काष्ठा ad_bond_info अणु
	काष्ठा ad_प्रणाली प्रणाली;	/* 802.3ad प्रणाली काष्ठाure */
	काष्ठा bond_3ad_stats stats;
	u32 agg_select_समयr;		/* Timer to select aggregator after all adapter's hand shakes */
	u16 aggregator_identअगरier;
पूर्ण;

काष्ठा ad_slave_info अणु
	काष्ठा aggregator aggregator;	/* 802.3ad aggregator काष्ठाure */
	काष्ठा port port;		/* 802.3ad port काष्ठाure */
	काष्ठा bond_3ad_stats stats;
	u16 id;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *bond_3ad_churn_desc(churn_state_t state)
अणु
	अटल स्थिर अक्षर *स्थिर churn_description[] = अणु
		"monitoring",
		"churned",
		"none",
		"unknown"
	पूर्ण;
	पूर्णांक max_size = ARRAY_SIZE(churn_description);

	अगर (state >= max_size)
		state = max_size - 1;

	वापस churn_description[state];
पूर्ण

/* ========== AD Exported functions to the मुख्य bonding code ========== */
व्योम bond_3ad_initialize(काष्ठा bonding *bond, u16 tick_resolution);
व्योम bond_3ad_bind_slave(काष्ठा slave *slave);
व्योम bond_3ad_unbind_slave(काष्ठा slave *slave);
व्योम bond_3ad_state_machine_handler(काष्ठा work_काष्ठा *);
व्योम bond_3ad_initiate_agg_selection(काष्ठा bonding *bond, पूर्णांक समयout);
व्योम bond_3ad_adapter_speed_duplex_changed(काष्ठा slave *slave);
व्योम bond_3ad_handle_link_change(काष्ठा slave *slave, अक्षर link);
पूर्णांक  bond_3ad_get_active_agg_info(काष्ठा bonding *bond, काष्ठा ad_info *ad_info);
पूर्णांक  __bond_3ad_get_active_agg_info(काष्ठा bonding *bond,
				    काष्ठा ad_info *ad_info);
पूर्णांक bond_3ad_lacpdu_recv(स्थिर काष्ठा sk_buff *skb, काष्ठा bonding *bond,
			 काष्ठा slave *slave);
पूर्णांक bond_3ad_set_carrier(काष्ठा bonding *bond);
व्योम bond_3ad_update_lacp_rate(काष्ठा bonding *bond);
व्योम bond_3ad_update_ad_actor_settings(काष्ठा bonding *bond);
पूर्णांक bond_3ad_stats_fill(काष्ठा sk_buff *skb, काष्ठा bond_3ad_stats *stats);
माप_प्रकार bond_3ad_stats_size(व्योम);
#पूर्ण_अगर /* _NET_BOND_3AD_H */

