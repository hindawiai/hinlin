<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * iSCSI User/Kernel Shares (Defines, Constants, Protocol definitions, etc)
 *
 * Copyright (C) 2005 Dmitry Yusupov
 * Copyright (C) 2005 Alex Aizman
 * मुख्यtained by खोलो-iscsi@googlegroups.com
 */

#अगर_अघोषित ISCSI_IF_H
#घोषणा ISCSI_IF_H

#समावेश <scsi/iscsi_proto.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

#घोषणा ISCSI_NL_GRP_ISCSID	1
#घोषणा ISCSI_NL_GRP_UIP	2

#घोषणा UEVENT_BASE			10
#घोषणा KEVENT_BASE			100
#घोषणा ISCSI_ERR_BASE			1000

क्रमागत iscsi_uevent_e अणु
	ISCSI_UEVENT_UNKNOWN		= 0,

	/* करोwn events */
	ISCSI_UEVENT_CREATE_SESSION	= UEVENT_BASE + 1,
	ISCSI_UEVENT_DESTROY_SESSION	= UEVENT_BASE + 2,
	ISCSI_UEVENT_CREATE_CONN	= UEVENT_BASE + 3,
	ISCSI_UEVENT_DESTROY_CONN	= UEVENT_BASE + 4,
	ISCSI_UEVENT_BIND_CONN		= UEVENT_BASE + 5,
	ISCSI_UEVENT_SET_PARAM		= UEVENT_BASE + 6,
	ISCSI_UEVENT_START_CONN		= UEVENT_BASE + 7,
	ISCSI_UEVENT_STOP_CONN		= UEVENT_BASE + 8,
	ISCSI_UEVENT_SEND_PDU		= UEVENT_BASE + 9,
	ISCSI_UEVENT_GET_STATS		= UEVENT_BASE + 10,
	ISCSI_UEVENT_GET_PARAM		= UEVENT_BASE + 11,

	ISCSI_UEVENT_TRANSPORT_EP_CONNECT	= UEVENT_BASE + 12,
	ISCSI_UEVENT_TRANSPORT_EP_POLL		= UEVENT_BASE + 13,
	ISCSI_UEVENT_TRANSPORT_EP_DISCONNECT	= UEVENT_BASE + 14,

	ISCSI_UEVENT_TGT_DSCVR		= UEVENT_BASE + 15,
	ISCSI_UEVENT_SET_HOST_PARAM	= UEVENT_BASE + 16,
	ISCSI_UEVENT_UNBIND_SESSION	= UEVENT_BASE + 17,
	ISCSI_UEVENT_CREATE_BOUND_SESSION		= UEVENT_BASE + 18,
	ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST	= UEVENT_BASE + 19,

	ISCSI_UEVENT_PATH_UPDATE	= UEVENT_BASE + 20,
	ISCSI_UEVENT_SET_IFACE_PARAMS	= UEVENT_BASE + 21,
	ISCSI_UEVENT_PING		= UEVENT_BASE + 22,
	ISCSI_UEVENT_GET_CHAP		= UEVENT_BASE + 23,
	ISCSI_UEVENT_DELETE_CHAP	= UEVENT_BASE + 24,
	ISCSI_UEVENT_SET_FLASHNODE_PARAMS	= UEVENT_BASE + 25,
	ISCSI_UEVENT_NEW_FLASHNODE	= UEVENT_BASE + 26,
	ISCSI_UEVENT_DEL_FLASHNODE	= UEVENT_BASE + 27,
	ISCSI_UEVENT_LOGIN_FLASHNODE	= UEVENT_BASE + 28,
	ISCSI_UEVENT_LOGOUT_FLASHNODE	= UEVENT_BASE + 29,
	ISCSI_UEVENT_LOGOUT_FLASHNODE_SID	= UEVENT_BASE + 30,
	ISCSI_UEVENT_SET_CHAP		= UEVENT_BASE + 31,
	ISCSI_UEVENT_GET_HOST_STATS	= UEVENT_BASE + 32,
	ISCSI_UEVENT_DESTROY_SESSION_ASYNC	= UEVENT_BASE + 33,

	/* up events */
	ISCSI_KEVENT_RECV_PDU		= KEVENT_BASE + 1,
	ISCSI_KEVENT_CONN_ERROR		= KEVENT_BASE + 2,
	ISCSI_KEVENT_IF_ERROR		= KEVENT_BASE + 3,
	ISCSI_KEVENT_DESTROY_SESSION	= KEVENT_BASE + 4,
	ISCSI_KEVENT_UNBIND_SESSION	= KEVENT_BASE + 5,
	ISCSI_KEVENT_CREATE_SESSION	= KEVENT_BASE + 6,

	ISCSI_KEVENT_PATH_REQ		= KEVENT_BASE + 7,
	ISCSI_KEVENT_IF_DOWN		= KEVENT_BASE + 8,
	ISCSI_KEVENT_CONN_LOGIN_STATE   = KEVENT_BASE + 9,
	ISCSI_KEVENT_HOST_EVENT		= KEVENT_BASE + 10,
	ISCSI_KEVENT_PING_COMP		= KEVENT_BASE + 11,
पूर्ण;

क्रमागत iscsi_tgt_dscvr अणु
	ISCSI_TGT_DSCVR_SEND_TARGETS	= 1,
	ISCSI_TGT_DSCVR_ISNS		= 2,
	ISCSI_TGT_DSCVR_SLP		= 3,
पूर्ण;

क्रमागत iscsi_host_event_code अणु
	ISCSI_EVENT_LINKUP		= 1,
	ISCSI_EVENT_LINKDOWN,
	/* must always be last */
	ISCSI_EVENT_MAX,
पूर्ण;

काष्ठा iscsi_uevent अणु
	uपूर्णांक32_t type; /* k/u events type */
	uपूर्णांक32_t अगरerror; /* carries पूर्णांकerface or resource errors */
	uपूर्णांक64_t transport_handle;

	जोड़ अणु
		/* messages u -> k */
		काष्ठा msg_create_session अणु
			uपूर्णांक32_t	initial_cmdsn;
			uपूर्णांक16_t	cmds_max;
			uपूर्णांक16_t	queue_depth;
		पूर्ण c_session;
		काष्ठा msg_create_bound_session अणु
			uपूर्णांक64_t	ep_handle;
			uपूर्णांक32_t	initial_cmdsn;
			uपूर्णांक16_t	cmds_max;
			uपूर्णांक16_t	queue_depth;
		पूर्ण c_bound_session;
		काष्ठा msg_destroy_session अणु
			uपूर्णांक32_t	sid;
		पूर्ण d_session;
		काष्ठा msg_create_conn अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
		पूर्ण c_conn;
		काष्ठा msg_bind_conn अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
			uपूर्णांक64_t	transport_eph;
			uपूर्णांक32_t	is_leading;
		पूर्ण b_conn;
		काष्ठा msg_destroy_conn अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
		पूर्ण d_conn;
		काष्ठा msg_send_pdu अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
			uपूर्णांक32_t	hdr_size;
			uपूर्णांक32_t	data_size;
		पूर्ण send_pdu;
		काष्ठा msg_set_param अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
			uपूर्णांक32_t	param; /* क्रमागत iscsi_param */
			uपूर्णांक32_t	len;
		पूर्ण set_param;
		काष्ठा msg_start_conn अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
		पूर्ण start_conn;
		काष्ठा msg_stop_conn अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
			uपूर्णांक64_t	conn_handle;
			uपूर्णांक32_t	flag;
		पूर्ण stop_conn;
		काष्ठा msg_get_stats अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
		पूर्ण get_stats;
		काष्ठा msg_transport_connect अणु
			uपूर्णांक32_t	non_blocking;
		पूर्ण ep_connect;
		काष्ठा msg_transport_connect_through_host अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	non_blocking;
		पूर्ण ep_connect_through_host;
		काष्ठा msg_transport_poll अणु
			uपूर्णांक64_t	ep_handle;
			uपूर्णांक32_t	समयout_ms;
		पूर्ण ep_poll;
		काष्ठा msg_transport_disconnect अणु
			uपूर्णांक64_t	ep_handle;
		पूर्ण ep_disconnect;
		काष्ठा msg_tgt_dscvr अणु
			क्रमागत iscsi_tgt_dscvr	type;
			uपूर्णांक32_t	host_no;
			/*
 			 * enable = 1 to establish a new connection
			 * with the server. enable = 0 to disconnect
			 * from the server. Used primarily to चयन
			 * from one iSNS server to another.
			 */
			uपूर्णांक32_t	enable;
		पूर्ण tgt_dscvr;
		काष्ठा msg_set_host_param अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	param; /* क्रमागत iscsi_host_param */
			uपूर्णांक32_t	len;
		पूर्ण set_host_param;
		काष्ठा msg_set_path अणु
			uपूर्णांक32_t	host_no;
		पूर्ण set_path;
		काष्ठा msg_set_अगरace_params अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	count;
		पूर्ण set_अगरace_params;
		काष्ठा msg_iscsi_ping अणु
			uपूर्णांक32_t        host_no;
			uपूर्णांक32_t        अगरace_num;
			uपूर्णांक32_t        अगरace_type;
			uपूर्णांक32_t        payload_size;
			uपूर्णांक32_t	pid;	/* unique ping id associated
						   with each ping request */
		पूर्ण iscsi_ping;
		काष्ठा msg_get_chap अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	num_entries; /* number of CHAP entries
						      * on request, number of
						      * valid CHAP entries on
						      * response */
			uपूर्णांक16_t	chap_tbl_idx;
		पूर्ण get_chap;
		काष्ठा msg_delete_chap अणु
		       uपूर्णांक32_t        host_no;
		       uपूर्णांक16_t        chap_tbl_idx;
		पूर्ण delete_chap;
		काष्ठा msg_set_flashnode_param अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	flashnode_idx;
			uपूर्णांक32_t	count;
		पूर्ण set_flashnode;
		काष्ठा msg_new_flashnode अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	len;
		पूर्ण new_flashnode;
		काष्ठा msg_del_flashnode अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	flashnode_idx;
		पूर्ण del_flashnode;
		काष्ठा msg_login_flashnode अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	flashnode_idx;
		पूर्ण login_flashnode;
		काष्ठा msg_logout_flashnode अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	flashnode_idx;
		पूर्ण logout_flashnode;
		काष्ठा msg_logout_flashnode_sid अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	sid;
		पूर्ण logout_flashnode_sid;
		काष्ठा msg_get_host_stats अणु
			uपूर्णांक32_t host_no;
		पूर्ण get_host_stats;
	पूर्ण u;
	जोड़ अणु
		/* messages k -> u */
		पूर्णांक			retcode;
		काष्ठा msg_create_session_ret अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	host_no;
		पूर्ण c_session_ret;
		काष्ठा msg_create_conn_ret अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
		पूर्ण c_conn_ret;
		काष्ठा msg_unbind_session अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	host_no;
		पूर्ण unbind_session;
		काष्ठा msg_recv_req अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
			uपूर्णांक64_t	recv_handle;
		पूर्ण recv_req;
		काष्ठा msg_conn_login अणु
			uपूर्णांक32_t        sid;
			uपूर्णांक32_t        cid;
			uपूर्णांक32_t        state; /* क्रमागत iscsi_conn_state */
		पूर्ण conn_login;
		काष्ठा msg_conn_error अणु
			uपूर्णांक32_t	sid;
			uपूर्णांक32_t	cid;
			uपूर्णांक32_t	error; /* क्रमागत iscsi_err */
		पूर्ण connerror;
		काष्ठा msg_session_destroyed अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	sid;
		पूर्ण d_session;
		काष्ठा msg_transport_connect_ret अणु
			uपूर्णांक64_t	handle;
		पूर्ण ep_connect_ret;
		काष्ठा msg_req_path अणु
			uपूर्णांक32_t	host_no;
		पूर्ण req_path;
		काष्ठा msg_notअगरy_अगर_करोwn अणु
			uपूर्णांक32_t	host_no;
		पूर्ण notअगरy_अगर_करोwn;
		काष्ठा msg_host_event अणु
			uपूर्णांक32_t	host_no;
			uपूर्णांक32_t	data_size;
			क्रमागत iscsi_host_event_code code;
		पूर्ण host_event;
		काष्ठा msg_ping_comp अणु
			uपूर्णांक32_t        host_no;
			uपूर्णांक32_t        status; /* क्रमागत
						 * iscsi_ping_status_code */
			uपूर्णांक32_t	pid;	/* unique ping id associated
						   with each ping request */
			uपूर्णांक32_t        data_size;
		पूर्ण ping_comp;
		काष्ठा msg_new_flashnode_ret अणु
			uपूर्णांक32_t	flashnode_idx;
		पूर्ण new_flashnode_ret;
	पूर्ण r;
पूर्ण __attribute__ ((aligned (माप(uपूर्णांक64_t))));

क्रमागत iscsi_param_type अणु
	ISCSI_PARAM,		/* iscsi_param (session, conn, target, LU) */
	ISCSI_HOST_PARAM,	/* iscsi_host_param */
	ISCSI_NET_PARAM,	/* iscsi_net_param */
	ISCSI_FLASHNODE_PARAM,	/* iscsi_flashnode_param */
	ISCSI_CHAP_PARAM,	/* iscsi_chap_param */
	ISCSI_IFACE_PARAM,	/* iscsi_अगरace_param */
पूर्ण;

/* काष्ठाure क्रम minimalist useहाल */
काष्ठा iscsi_param_info अणु
	uपूर्णांक32_t len;		/* Actual length of the param value */
	uपूर्णांक16_t param;		/* iscsi param */
	uपूर्णांक8_t value[];	/* length sized value follows */
पूर्ण __packed;

काष्ठा iscsi_अगरace_param_info अणु
	uपूर्णांक32_t अगरace_num;	/* अगरace number, 0 - n */
	uपूर्णांक32_t len;		/* Actual length of the param */
	uपूर्णांक16_t param;		/* iscsi param value */
	uपूर्णांक8_t अगरace_type;	/* IPv4 or IPv6 */
	uपूर्णांक8_t param_type;	/* iscsi_param_type */
	uपूर्णांक8_t value[];	/* length sized value follows */
पूर्ण __packed;

/*
 * To keep the काष्ठा iscsi_uevent size the same क्रम userspace code
 * compatibility, the मुख्य काष्ठाure क्रम ISCSI_UEVENT_PATH_UPDATE and
 * ISCSI_KEVENT_PATH_REQ is defined separately and comes after the
 * काष्ठा iscsi_uevent in the NETLINK_ISCSI message.
 */
काष्ठा iscsi_path अणु
	uपूर्णांक64_t	handle;
	uपूर्णांक8_t		mac_addr[6];
	uपूर्णांक8_t		mac_addr_old[6];
	uपूर्णांक32_t	ip_addr_len;	/* 4 or 16 */
	जोड़ अणु
		काष्ठा in_addr	v4_addr;
		काष्ठा in6_addr	v6_addr;
	पूर्ण src;
	जोड़ अणु
		काष्ठा in_addr	v4_addr;
		काष्ठा in6_addr	v6_addr;
	पूर्ण dst;
	uपूर्णांक16_t	vlan_id;
	uपूर्णांक16_t	pmtu;
पूर्ण __attribute__ ((aligned (माप(uपूर्णांक64_t))));

/* iscsi अगरace enabled/disabled setting */
#घोषणा ISCSI_IFACE_DISABLE	0x01
#घोषणा ISCSI_IFACE_ENABLE	0x02

/* ipv4 bootproto */
#घोषणा ISCSI_BOOTPROTO_STATIC		0x01
#घोषणा ISCSI_BOOTPROTO_DHCP		0x02

/* ipv6 addr स्वतःconfig type */
#घोषणा ISCSI_IPV6_AUTOCFG_DISABLE		0x01
#घोषणा ISCSI_IPV6_AUTOCFG_ND_ENABLE		0x02
#घोषणा ISCSI_IPV6_AUTOCFG_DHCPV6_ENABLE	0x03

/* ipv6 link local addr type */
#घोषणा ISCSI_IPV6_LINKLOCAL_AUTOCFG_ENABLE	0x01
#घोषणा ISCSI_IPV6_LINKLOCAL_AUTOCFG_DISABLE	0x02

/* ipv6 router addr type */
#घोषणा ISCSI_IPV6_ROUTER_AUTOCFG_ENABLE	0x01
#घोषणा ISCSI_IPV6_ROUTER_AUTOCFG_DISABLE	0x02

#घोषणा ISCSI_IFACE_TYPE_IPV4		0x01
#घोषणा ISCSI_IFACE_TYPE_IPV6		0x02

#घोषणा ISCSI_MAX_VLAN_ID		4095
#घोषणा ISCSI_MAX_VLAN_PRIORITY		7

/* iscsi vlan enable/disabled setting */
#घोषणा ISCSI_VLAN_DISABLE	0x01
#घोषणा ISCSI_VLAN_ENABLE	0x02

/* iscsi generic enable/disabled setting क्रम various features */
#घोषणा ISCSI_NET_PARAM_DISABLE		0x01
#घोषणा ISCSI_NET_PARAM_ENABLE		0x02

/* iSCSI network params */
क्रमागत iscsi_net_param अणु
	ISCSI_NET_PARAM_IPV4_ADDR		= 1,
	ISCSI_NET_PARAM_IPV4_SUBNET,
	ISCSI_NET_PARAM_IPV4_GW,
	ISCSI_NET_PARAM_IPV4_BOOTPROTO,
	ISCSI_NET_PARAM_MAC,
	ISCSI_NET_PARAM_IPV6_LINKLOCAL,
	ISCSI_NET_PARAM_IPV6_ADDR,
	ISCSI_NET_PARAM_IPV6_ROUTER,
	ISCSI_NET_PARAM_IPV6_ADDR_AUTOCFG,
	ISCSI_NET_PARAM_IPV6_LINKLOCAL_AUTOCFG,
	ISCSI_NET_PARAM_IPV6_ROUTER_AUTOCFG,
	ISCSI_NET_PARAM_IFACE_ENABLE,
	ISCSI_NET_PARAM_VLAN_ID,
	ISCSI_NET_PARAM_VLAN_PRIORITY,
	ISCSI_NET_PARAM_VLAN_ENABLED,
	ISCSI_NET_PARAM_VLAN_TAG,
	ISCSI_NET_PARAM_IFACE_TYPE,
	ISCSI_NET_PARAM_IFACE_NAME,
	ISCSI_NET_PARAM_MTU,
	ISCSI_NET_PARAM_PORT,
	ISCSI_NET_PARAM_IPADDR_STATE,
	ISCSI_NET_PARAM_IPV6_LINKLOCAL_STATE,
	ISCSI_NET_PARAM_IPV6_ROUTER_STATE,
	ISCSI_NET_PARAM_DELAYED_ACK_EN,
	ISCSI_NET_PARAM_TCP_NAGLE_DISABLE,
	ISCSI_NET_PARAM_TCP_WSF_DISABLE,
	ISCSI_NET_PARAM_TCP_WSF,
	ISCSI_NET_PARAM_TCP_TIMER_SCALE,
	ISCSI_NET_PARAM_TCP_TIMESTAMP_EN,
	ISCSI_NET_PARAM_CACHE_ID,
	ISCSI_NET_PARAM_IPV4_DHCP_DNS_ADDR_EN,
	ISCSI_NET_PARAM_IPV4_DHCP_SLP_DA_EN,
	ISCSI_NET_PARAM_IPV4_TOS_EN,
	ISCSI_NET_PARAM_IPV4_TOS,
	ISCSI_NET_PARAM_IPV4_GRAT_ARP_EN,
	ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID_EN,
	ISCSI_NET_PARAM_IPV4_DHCP_ALT_CLIENT_ID,
	ISCSI_NET_PARAM_IPV4_DHCP_REQ_VENDOR_ID_EN,
	ISCSI_NET_PARAM_IPV4_DHCP_USE_VENDOR_ID_EN,
	ISCSI_NET_PARAM_IPV4_DHCP_VENDOR_ID,
	ISCSI_NET_PARAM_IPV4_DHCP_LEARN_IQN_EN,
	ISCSI_NET_PARAM_IPV4_FRAGMENT_DISABLE,
	ISCSI_NET_PARAM_IPV4_IN_FORWARD_EN,
	ISCSI_NET_PARAM_IPV4_TTL,
	ISCSI_NET_PARAM_IPV6_GRAT_NEIGHBOR_ADV_EN,
	ISCSI_NET_PARAM_IPV6_MLD_EN,
	ISCSI_NET_PARAM_IPV6_FLOW_LABEL,
	ISCSI_NET_PARAM_IPV6_TRAFFIC_CLASS,
	ISCSI_NET_PARAM_IPV6_HOP_LIMIT,
	ISCSI_NET_PARAM_IPV6_ND_REACHABLE_TMO,
	ISCSI_NET_PARAM_IPV6_ND_REXMIT_TIME,
	ISCSI_NET_PARAM_IPV6_ND_STALE_TMO,
	ISCSI_NET_PARAM_IPV6_DUP_ADDR_DETECT_CNT,
	ISCSI_NET_PARAM_IPV6_RTR_ADV_LINK_MTU,
	ISCSI_NET_PARAM_REसूचीECT_EN,
पूर्ण;

क्रमागत iscsi_ipaddress_state अणु
	ISCSI_IPDDRESS_STATE_UNCONFIGURED,
	ISCSI_IPDDRESS_STATE_ACQUIRING,
	ISCSI_IPDDRESS_STATE_TENTATIVE,
	ISCSI_IPDDRESS_STATE_VALID,
	ISCSI_IPDDRESS_STATE_DISABLING,
	ISCSI_IPDDRESS_STATE_INVALID,
	ISCSI_IPDDRESS_STATE_DEPRECATED,
पूर्ण;

क्रमागत iscsi_router_state अणु
	ISCSI_ROUTER_STATE_UNKNOWN,
	ISCSI_ROUTER_STATE_ADVERTISED,
	ISCSI_ROUTER_STATE_MANUAL,
	ISCSI_ROUTER_STATE_STALE,
पूर्ण;

/* iSCSI specअगरic settings params क्रम अगरace */
क्रमागत iscsi_अगरace_param अणु
	ISCSI_IFACE_PARAM_DEF_TASKMGMT_TMO,
	ISCSI_IFACE_PARAM_HDRDGST_EN,
	ISCSI_IFACE_PARAM_DATADGST_EN,
	ISCSI_IFACE_PARAM_IMM_DATA_EN,
	ISCSI_IFACE_PARAM_INITIAL_R2T_EN,
	ISCSI_IFACE_PARAM_DATASEQ_INORDER_EN,
	ISCSI_IFACE_PARAM_PDU_INORDER_EN,
	ISCSI_IFACE_PARAM_ERL,
	ISCSI_IFACE_PARAM_MAX_RECV_DLENGTH,
	ISCSI_IFACE_PARAM_FIRST_BURST,
	ISCSI_IFACE_PARAM_MAX_R2T,
	ISCSI_IFACE_PARAM_MAX_BURST,
	ISCSI_IFACE_PARAM_CHAP_AUTH_EN,
	ISCSI_IFACE_PARAM_BIDI_CHAP_EN,
	ISCSI_IFACE_PARAM_DISCOVERY_AUTH_OPTIONAL,
	ISCSI_IFACE_PARAM_DISCOVERY_LOGOUT_EN,
	ISCSI_IFACE_PARAM_STRICT_LOGIN_COMP_EN,
	ISCSI_IFACE_PARAM_INITIATOR_NAME,
पूर्ण;

क्रमागत iscsi_conn_state अणु
	ISCSI_CONN_STATE_FREE,
	ISCSI_CONN_STATE_XPT_WAIT,
	ISCSI_CONN_STATE_IN_LOGIN,
	ISCSI_CONN_STATE_LOGGED_IN,
	ISCSI_CONN_STATE_IN_LOGOUT,
	ISCSI_CONN_STATE_LOGOUT_REQUESTED,
	ISCSI_CONN_STATE_CLEANUP_WAIT,
पूर्ण;

/*
 * Common error codes
 */
क्रमागत iscsi_err अणु
	ISCSI_OK			= 0,

	ISCSI_ERR_DATASN		= ISCSI_ERR_BASE + 1,
	ISCSI_ERR_DATA_OFFSET		= ISCSI_ERR_BASE + 2,
	ISCSI_ERR_MAX_CMDSN		= ISCSI_ERR_BASE + 3,
	ISCSI_ERR_EXP_CMDSN		= ISCSI_ERR_BASE + 4,
	ISCSI_ERR_BAD_OPCODE		= ISCSI_ERR_BASE + 5,
	ISCSI_ERR_DATALEN		= ISCSI_ERR_BASE + 6,
	ISCSI_ERR_AHSLEN		= ISCSI_ERR_BASE + 7,
	ISCSI_ERR_PROTO			= ISCSI_ERR_BASE + 8,
	ISCSI_ERR_LUN			= ISCSI_ERR_BASE + 9,
	ISCSI_ERR_BAD_ITT		= ISCSI_ERR_BASE + 10,
	ISCSI_ERR_CONN_FAILED		= ISCSI_ERR_BASE + 11,
	ISCSI_ERR_R2TSN			= ISCSI_ERR_BASE + 12,
	ISCSI_ERR_SESSION_FAILED	= ISCSI_ERR_BASE + 13,
	ISCSI_ERR_HDR_DGST		= ISCSI_ERR_BASE + 14,
	ISCSI_ERR_DATA_DGST		= ISCSI_ERR_BASE + 15,
	ISCSI_ERR_PARAM_NOT_FOUND	= ISCSI_ERR_BASE + 16,
	ISCSI_ERR_NO_SCSI_CMD		= ISCSI_ERR_BASE + 17,
	ISCSI_ERR_INVALID_HOST		= ISCSI_ERR_BASE + 18,
	ISCSI_ERR_XMIT_FAILED		= ISCSI_ERR_BASE + 19,
	ISCSI_ERR_TCP_CONN_CLOSE	= ISCSI_ERR_BASE + 20,
	ISCSI_ERR_SCSI_EH_SESSION_RST	= ISCSI_ERR_BASE + 21,
	ISCSI_ERR_NOP_TIMEDOUT		= ISCSI_ERR_BASE + 22,
पूर्ण;

/*
 * iSCSI Parameters (RFC3720)
 */
क्रमागत iscsi_param अणु
	/* passed in using netlink set param */
	ISCSI_PARAM_MAX_RECV_DLENGTH,
	ISCSI_PARAM_MAX_XMIT_DLENGTH,
	ISCSI_PARAM_HDRDGST_EN,
	ISCSI_PARAM_DATADGST_EN,
	ISCSI_PARAM_INITIAL_R2T_EN,
	ISCSI_PARAM_MAX_R2T,
	ISCSI_PARAM_IMM_DATA_EN,
	ISCSI_PARAM_FIRST_BURST,
	ISCSI_PARAM_MAX_BURST,
	ISCSI_PARAM_PDU_INORDER_EN,
	ISCSI_PARAM_DATASEQ_INORDER_EN,
	ISCSI_PARAM_ERL,
	ISCSI_PARAM_IFMARKER_EN,
	ISCSI_PARAM_OFMARKER_EN,
	ISCSI_PARAM_EXP_STATSN,
	ISCSI_PARAM_TARGET_NAME,
	ISCSI_PARAM_TPGT,
	ISCSI_PARAM_PERSISTENT_ADDRESS,
	ISCSI_PARAM_PERSISTENT_PORT,
	ISCSI_PARAM_SESS_RECOVERY_TMO,

	/* passed in through bind conn using transport_fd */
	ISCSI_PARAM_CONN_PORT,
	ISCSI_PARAM_CONN_ADDRESS,

	ISCSI_PARAM_USERNAME,
	ISCSI_PARAM_USERNAME_IN,
	ISCSI_PARAM_PASSWORD,
	ISCSI_PARAM_PASSWORD_IN,

	ISCSI_PARAM_FAST_ABORT,
	ISCSI_PARAM_ABORT_TMO,
	ISCSI_PARAM_LU_RESET_TMO,
	ISCSI_PARAM_HOST_RESET_TMO,

	ISCSI_PARAM_PING_TMO,
	ISCSI_PARAM_RECV_TMO,

	ISCSI_PARAM_IFACE_NAME,
	ISCSI_PARAM_ISID,
	ISCSI_PARAM_INITIATOR_NAME,

	ISCSI_PARAM_TGT_RESET_TMO,
	ISCSI_PARAM_TARGET_ALIAS,

	ISCSI_PARAM_CHAP_IN_IDX,
	ISCSI_PARAM_CHAP_OUT_IDX,

	ISCSI_PARAM_BOOT_ROOT,
	ISCSI_PARAM_BOOT_NIC,
	ISCSI_PARAM_BOOT_TARGET,

	ISCSI_PARAM_AUTO_SND_TGT_DISABLE,
	ISCSI_PARAM_DISCOVERY_SESS,
	ISCSI_PARAM_PORTAL_TYPE,
	ISCSI_PARAM_CHAP_AUTH_EN,
	ISCSI_PARAM_DISCOVERY_LOGOUT_EN,
	ISCSI_PARAM_BIDI_CHAP_EN,
	ISCSI_PARAM_DISCOVERY_AUTH_OPTIONAL,

	ISCSI_PARAM_DEF_TIME2WAIT,
	ISCSI_PARAM_DEF_TIME2RETAIN,
	ISCSI_PARAM_MAX_SEGMENT_SIZE,
	ISCSI_PARAM_STATSN,
	ISCSI_PARAM_KEEPALIVE_TMO,
	ISCSI_PARAM_LOCAL_PORT,
	ISCSI_PARAM_TSID,
	ISCSI_PARAM_DEF_TASKMGMT_TMO,

	ISCSI_PARAM_TCP_TIMESTAMP_STAT,
	ISCSI_PARAM_TCP_WSF_DISABLE,
	ISCSI_PARAM_TCP_NAGLE_DISABLE,
	ISCSI_PARAM_TCP_TIMER_SCALE,
	ISCSI_PARAM_TCP_TIMESTAMP_EN,
	ISCSI_PARAM_TCP_XMIT_WSF,
	ISCSI_PARAM_TCP_RECV_WSF,
	ISCSI_PARAM_IP_FRAGMENT_DISABLE,
	ISCSI_PARAM_IPV4_TOS,
	ISCSI_PARAM_IPV6_TC,
	ISCSI_PARAM_IPV6_FLOW_LABEL,
	ISCSI_PARAM_IS_FW_ASSIGNED_IPV6,

	ISCSI_PARAM_DISCOVERY_PARENT_IDX,
	ISCSI_PARAM_DISCOVERY_PARENT_TYPE,
	ISCSI_PARAM_LOCAL_IPADDR,
	/* must always be last */
	ISCSI_PARAM_MAX,
पूर्ण;

/* iSCSI HBA params */
क्रमागत iscsi_host_param अणु
	ISCSI_HOST_PARAM_HWADDRESS,
	ISCSI_HOST_PARAM_INITIATOR_NAME,
	ISCSI_HOST_PARAM_NETDEV_NAME,
	ISCSI_HOST_PARAM_IPADDRESS,
	ISCSI_HOST_PARAM_PORT_STATE,
	ISCSI_HOST_PARAM_PORT_SPEED,
	ISCSI_HOST_PARAM_MAX,
पूर्ण;

/* portal type */
#घोषणा PORTAL_TYPE_IPV4	"ipv4"
#घोषणा PORTAL_TYPE_IPV6	"ipv6"

/* iSCSI Flash Target params */
क्रमागत iscsi_flashnode_param अणु
	ISCSI_FLASHNODE_IS_FW_ASSIGNED_IPV6,
	ISCSI_FLASHNODE_PORTAL_TYPE,
	ISCSI_FLASHNODE_AUTO_SND_TGT_DISABLE,
	ISCSI_FLASHNODE_DISCOVERY_SESS,
	ISCSI_FLASHNODE_ENTRY_EN,
	ISCSI_FLASHNODE_HDR_DGST_EN,
	ISCSI_FLASHNODE_DATA_DGST_EN,
	ISCSI_FLASHNODE_IMM_DATA_EN,
	ISCSI_FLASHNODE_INITIAL_R2T_EN,
	ISCSI_FLASHNODE_DATASEQ_INORDER,
	ISCSI_FLASHNODE_PDU_INORDER,
	ISCSI_FLASHNODE_CHAP_AUTH_EN,
	ISCSI_FLASHNODE_SNACK_REQ_EN,
	ISCSI_FLASHNODE_DISCOVERY_LOGOUT_EN,
	ISCSI_FLASHNODE_BIDI_CHAP_EN,
	/* make authentication क्रम discovery sessions optional */
	ISCSI_FLASHNODE_DISCOVERY_AUTH_OPTIONAL,
	ISCSI_FLASHNODE_ERL,
	ISCSI_FLASHNODE_TCP_TIMESTAMP_STAT,
	ISCSI_FLASHNODE_TCP_NAGLE_DISABLE,
	ISCSI_FLASHNODE_TCP_WSF_DISABLE,
	ISCSI_FLASHNODE_TCP_TIMER_SCALE,
	ISCSI_FLASHNODE_TCP_TIMESTAMP_EN,
	ISCSI_FLASHNODE_IP_FRAG_DISABLE,
	ISCSI_FLASHNODE_MAX_RECV_DLENGTH,
	ISCSI_FLASHNODE_MAX_XMIT_DLENGTH,
	ISCSI_FLASHNODE_FIRST_BURST,
	ISCSI_FLASHNODE_DEF_TIME2WAIT,
	ISCSI_FLASHNODE_DEF_TIME2RETAIN,
	ISCSI_FLASHNODE_MAX_R2T,
	ISCSI_FLASHNODE_KEEPALIVE_TMO,
	ISCSI_FLASHNODE_ISID,
	ISCSI_FLASHNODE_TSID,
	ISCSI_FLASHNODE_PORT,
	ISCSI_FLASHNODE_MAX_BURST,
	ISCSI_FLASHNODE_DEF_TASKMGMT_TMO,
	ISCSI_FLASHNODE_IPADDR,
	ISCSI_FLASHNODE_ALIAS,
	ISCSI_FLASHNODE_REसूचीECT_IPADDR,
	ISCSI_FLASHNODE_MAX_SEGMENT_SIZE,
	ISCSI_FLASHNODE_LOCAL_PORT,
	ISCSI_FLASHNODE_IPV4_TOS,
	ISCSI_FLASHNODE_IPV6_TC,
	ISCSI_FLASHNODE_IPV6_FLOW_LABEL,
	ISCSI_FLASHNODE_NAME,
	ISCSI_FLASHNODE_TPGT,
	ISCSI_FLASHNODE_LINK_LOCAL_IPV6,
	ISCSI_FLASHNODE_DISCOVERY_PARENT_IDX,
	ISCSI_FLASHNODE_DISCOVERY_PARENT_TYPE,
	ISCSI_FLASHNODE_TCP_XMIT_WSF,
	ISCSI_FLASHNODE_TCP_RECV_WSF,
	ISCSI_FLASHNODE_CHAP_IN_IDX,
	ISCSI_FLASHNODE_CHAP_OUT_IDX,
	ISCSI_FLASHNODE_USERNAME,
	ISCSI_FLASHNODE_USERNAME_IN,
	ISCSI_FLASHNODE_PASSWORD,
	ISCSI_FLASHNODE_PASSWORD_IN,
	ISCSI_FLASHNODE_STATSN,
	ISCSI_FLASHNODE_EXP_STATSN,
	ISCSI_FLASHNODE_IS_BOOT_TGT,

	ISCSI_FLASHNODE_MAX,
पूर्ण;

काष्ठा iscsi_flashnode_param_info अणु
	uपूर्णांक32_t len;		/* Actual length of the param */
	uपूर्णांक16_t param;		/* iscsi param value */
	uपूर्णांक8_t value[];	/* length sized value follows */
पूर्ण __packed;

क्रमागत iscsi_discovery_parent_type अणु
	ISCSI_DISC_PARENT_UNKNOWN	= 0x1,
	ISCSI_DISC_PARENT_SENDTGT	= 0x2,
	ISCSI_DISC_PARENT_ISNS		= 0x3,
पूर्ण;

/* iSCSI port Speed */
क्रमागत iscsi_port_speed अणु
	ISCSI_PORT_SPEED_UNKNOWN	= 0x1,
	ISCSI_PORT_SPEED_10MBPS		= 0x2,
	ISCSI_PORT_SPEED_100MBPS	= 0x4,
	ISCSI_PORT_SPEED_1GBPS		= 0x8,
	ISCSI_PORT_SPEED_10GBPS		= 0x10,
	ISCSI_PORT_SPEED_25GBPS         = 0x20,
	ISCSI_PORT_SPEED_40GBPS         = 0x40,
पूर्ण;

/* iSCSI port state */
क्रमागत iscsi_port_state अणु
	ISCSI_PORT_STATE_DOWN		= 0x1,
	ISCSI_PORT_STATE_UP		= 0x2,
पूर्ण;

/* iSCSI PING status/error code */
क्रमागत iscsi_ping_status_code अणु
	ISCSI_PING_SUCCESS			= 0,
	ISCSI_PING_FW_DISABLED			= 0x1,
	ISCSI_PING_IPADDR_INVALID		= 0x2,
	ISCSI_PING_LINKLOCAL_IPV6_ADDR_INVALID	= 0x3,
	ISCSI_PING_TIMEOUT			= 0x4,
	ISCSI_PING_INVALID_DEST_ADDR		= 0x5,
	ISCSI_PING_OVERSIZE_PACKET		= 0x6,
	ISCSI_PING_ICMP_ERROR			= 0x7,
	ISCSI_PING_MAX_REQ_EXCEEDED		= 0x8,
	ISCSI_PING_NO_ARP_RECEIVED		= 0x9,
पूर्ण;

#घोषणा iscsi_ptr(_handle) ((व्योम*)(अचिन्हित दीर्घ)_handle)
#घोषणा iscsi_handle(_ptr) ((uपूर्णांक64_t)(अचिन्हित दीर्घ)_ptr)

/*
 * These flags presents iSCSI Data-Path capabilities.
 */
#घोषणा CAP_RECOVERY_L0		0x1
#घोषणा CAP_RECOVERY_L1		0x2
#घोषणा CAP_RECOVERY_L2		0x4
#घोषणा CAP_MULTI_R2T		0x8
#घोषणा CAP_HDRDGST		0x10
#घोषणा CAP_DATADGST		0x20
#घोषणा CAP_MULTI_CONN		0x40
#घोषणा CAP_TEXT_NEGO		0x80
#घोषणा CAP_MARKERS		0x100
#घोषणा CAP_FW_DB		0x200
#घोषणा CAP_SENDTARGETS_OFFLOAD	0x400	/* offload discovery process */
#घोषणा CAP_DATA_PATH_OFFLOAD	0x800	/* offload entire IO path */
#घोषणा CAP_DIGEST_OFFLOAD	0x1000	/* offload hdr and data digests */
#घोषणा CAP_PADDING_OFFLOAD	0x2000	/* offload padding insertion, removal,
					 and verअगरication */
#घोषणा CAP_LOGIN_OFFLOAD	0x4000  /* offload session login */

/*
 * These flags describes reason of stop_conn() call
 */
#घोषणा STOP_CONN_TERM		0x1
#घोषणा STOP_CONN_SUSPEND	0x2
#घोषणा STOP_CONN_RECOVER	0x3

#घोषणा ISCSI_STATS_CUSTOM_MAX		32
#घोषणा ISCSI_STATS_CUSTOM_DESC_MAX	64
काष्ठा iscsi_stats_custom अणु
	अक्षर desc[ISCSI_STATS_CUSTOM_DESC_MAX];
	uपूर्णांक64_t value;
पूर्ण;

/*
 * काष्ठा iscsi_stats - iSCSI Statistics (iSCSI MIB)
 *
 * Note: this काष्ठाure contains counters collected on per-connection basis.
 */
काष्ठा iscsi_stats अणु
	/* octets */
	uपूर्णांक64_t txdata_octets;
	uपूर्णांक64_t rxdata_octets;

	/* xmit pdus */
	uपूर्णांक32_t noptx_pdus;
	uपूर्णांक32_t scsicmd_pdus;
	uपूर्णांक32_t पंचांगfcmd_pdus;
	uपूर्णांक32_t login_pdus;
	uपूर्णांक32_t text_pdus;
	uपूर्णांक32_t dataout_pdus;
	uपूर्णांक32_t logout_pdus;
	uपूर्णांक32_t snack_pdus;

	/* recv pdus */
	uपूर्णांक32_t noprx_pdus;
	uपूर्णांक32_t scsirsp_pdus;
	uपूर्णांक32_t पंचांगfrsp_pdus;
	uपूर्णांक32_t textrsp_pdus;
	uपूर्णांक32_t datain_pdus;
	uपूर्णांक32_t logoutrsp_pdus;
	uपूर्णांक32_t r2t_pdus;
	uपूर्णांक32_t async_pdus;
	uपूर्णांक32_t rjt_pdus;

	/* errors */
	uपूर्णांक32_t digest_err;
	uपूर्णांक32_t समयout_err;

	/*
	 * iSCSI Custom Statistics support, i.e. Transport could
	 * extend existing MIB statistics with its own specअगरic statistics
	 * up to ISCSI_STATS_CUSTOM_MAX
	 */
	uपूर्णांक32_t custom_length;
	काष्ठा iscsi_stats_custom custom[]
		__attribute__ ((aligned (माप(uपूर्णांक64_t))));
पूर्ण;

क्रमागत chap_type_e अणु
	CHAP_TYPE_OUT,
	CHAP_TYPE_IN,
पूर्ण;

क्रमागत iscsi_chap_param अणु
	ISCSI_CHAP_PARAM_INDEX,
	ISCSI_CHAP_PARAM_CHAP_TYPE,
	ISCSI_CHAP_PARAM_USERNAME,
	ISCSI_CHAP_PARAM_PASSWORD,
	ISCSI_CHAP_PARAM_PASSWORD_LEN
पूर्ण;

#घोषणा ISCSI_CHAP_AUTH_NAME_MAX_LEN	256
#घोषणा ISCSI_CHAP_AUTH_SECRET_MAX_LEN	256
काष्ठा iscsi_chap_rec अणु
	uपूर्णांक16_t chap_tbl_idx;
	क्रमागत chap_type_e chap_type;
	अक्षर username[ISCSI_CHAP_AUTH_NAME_MAX_LEN];
	uपूर्णांक8_t password[ISCSI_CHAP_AUTH_SECRET_MAX_LEN];
	uपूर्णांक8_t password_length;
पूर्ण;

#घोषणा ISCSI_HOST_STATS_CUSTOM_MAX             32
#घोषणा ISCSI_HOST_STATS_CUSTOM_DESC_MAX        64
काष्ठा iscsi_host_stats_custom अणु
	अक्षर desc[ISCSI_HOST_STATS_CUSTOM_DESC_MAX];
	uपूर्णांक64_t value;
पूर्ण;

/* काष्ठा iscsi_offload_host_stats: Host statistics,
 * Include statistics क्रम MAC, IP, TCP & iSCSI.
 */
काष्ठा iscsi_offload_host_stats अणु
	/* MAC */
	uपूर्णांक64_t mactx_frames;
	uपूर्णांक64_t mactx_bytes;
	uपूर्णांक64_t mactx_multicast_frames;
	uपूर्णांक64_t mactx_broadcast_frames;
	uपूर्णांक64_t mactx_छोड़ो_frames;
	uपूर्णांक64_t mactx_control_frames;
	uपूर्णांक64_t mactx_deferral;
	uपूर्णांक64_t mactx_excess_deferral;
	uपूर्णांक64_t mactx_late_collision;
	uपूर्णांक64_t mactx_पात;
	uपूर्णांक64_t mactx_single_collision;
	uपूर्णांक64_t mactx_multiple_collision;
	uपूर्णांक64_t mactx_collision;
	uपूर्णांक64_t mactx_frames_dropped;
	uपूर्णांक64_t mactx_jumbo_frames;
	uपूर्णांक64_t macrx_frames;
	uपूर्णांक64_t macrx_bytes;
	uपूर्णांक64_t macrx_unknown_control_frames;
	uपूर्णांक64_t macrx_छोड़ो_frames;
	uपूर्णांक64_t macrx_control_frames;
	uपूर्णांक64_t macrx_dribble;
	uपूर्णांक64_t macrx_frame_length_error;
	uपूर्णांक64_t macrx_jabber;
	uपूर्णांक64_t macrx_carrier_sense_error;
	uपूर्णांक64_t macrx_frame_discarded;
	uपूर्णांक64_t macrx_frames_dropped;
	uपूर्णांक64_t mac_crc_error;
	uपूर्णांक64_t mac_encoding_error;
	uपूर्णांक64_t macrx_length_error_large;
	uपूर्णांक64_t macrx_length_error_small;
	uपूर्णांक64_t macrx_multicast_frames;
	uपूर्णांक64_t macrx_broadcast_frames;
	/* IP */
	uपूर्णांक64_t iptx_packets;
	uपूर्णांक64_t iptx_bytes;
	uपूर्णांक64_t iptx_fragments;
	uपूर्णांक64_t iprx_packets;
	uपूर्णांक64_t iprx_bytes;
	uपूर्णांक64_t iprx_fragments;
	uपूर्णांक64_t ip_datagram_reassembly;
	uपूर्णांक64_t ip_invalid_address_error;
	uपूर्णांक64_t ip_error_packets;
	uपूर्णांक64_t ip_fragrx_overlap;
	uपूर्णांक64_t ip_fragrx_outoक्रमder;
	uपूर्णांक64_t ip_datagram_reassembly_समयout;
	uपूर्णांक64_t ipv6tx_packets;
	uपूर्णांक64_t ipv6tx_bytes;
	uपूर्णांक64_t ipv6tx_fragments;
	uपूर्णांक64_t ipv6rx_packets;
	uपूर्णांक64_t ipv6rx_bytes;
	uपूर्णांक64_t ipv6rx_fragments;
	uपूर्णांक64_t ipv6_datagram_reassembly;
	uपूर्णांक64_t ipv6_invalid_address_error;
	uपूर्णांक64_t ipv6_error_packets;
	uपूर्णांक64_t ipv6_fragrx_overlap;
	uपूर्णांक64_t ipv6_fragrx_outoक्रमder;
	uपूर्णांक64_t ipv6_datagram_reassembly_समयout;
	/* TCP */
	uपूर्णांक64_t tcptx_segments;
	uपूर्णांक64_t tcptx_bytes;
	uपूर्णांक64_t tcprx_segments;
	uपूर्णांक64_t tcprx_byte;
	uपूर्णांक64_t tcp_duplicate_ack_retx;
	uपूर्णांक64_t tcp_retx_समयr_expired;
	uपूर्णांक64_t tcprx_duplicate_ack;
	uपूर्णांक64_t tcprx_pure_ackr;
	uपूर्णांक64_t tcptx_delayed_ack;
	uपूर्णांक64_t tcptx_pure_ack;
	uपूर्णांक64_t tcprx_segment_error;
	uपूर्णांक64_t tcprx_segment_outoक्रमder;
	uपूर्णांक64_t tcprx_winकरोw_probe;
	uपूर्णांक64_t tcprx_winकरोw_update;
	uपूर्णांक64_t tcptx_winकरोw_probe_persist;
	/* ECC */
	uपूर्णांक64_t ecc_error_correction;
	/* iSCSI */
	uपूर्णांक64_t iscsi_pdu_tx;
	uपूर्णांक64_t iscsi_data_bytes_tx;
	uपूर्णांक64_t iscsi_pdu_rx;
	uपूर्णांक64_t iscsi_data_bytes_rx;
	uपूर्णांक64_t iscsi_io_completed;
	uपूर्णांक64_t iscsi_unexpected_io_rx;
	uपूर्णांक64_t iscsi_क्रमmat_error;
	uपूर्णांक64_t iscsi_hdr_digest_error;
	uपूर्णांक64_t iscsi_data_digest_error;
	uपूर्णांक64_t iscsi_sequence_error;
	/*
	 * iSCSI Custom Host Statistics support, i.e. Transport could
	 * extend existing host statistics with its own specअगरic statistics
	 * up to ISCSI_HOST_STATS_CUSTOM_MAX
	 */
	uपूर्णांक32_t custom_length;
	काष्ठा iscsi_host_stats_custom custom[]
		__aligned(माप(uपूर्णांक64_t));
पूर्ण;

#पूर्ण_अगर
