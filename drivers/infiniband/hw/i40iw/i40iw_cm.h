<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*******************************************************************************/

#अगर_अघोषित I40IW_CM_H
#घोषणा I40IW_CM_H

#घोषणा QUEUE_EVENTS

#घोषणा I40IW_MANAGE_APBVT_DEL 0
#घोषणा I40IW_MANAGE_APBVT_ADD 1

#घोषणा I40IW_MPA_REQUEST_ACCEPT  1
#घोषणा I40IW_MPA_REQUEST_REJECT  2

/* IETF MPA -- defines, क्रमागतs, काष्ठाs */
#घोषणा IEFT_MPA_KEY_REQ  "MPA ID Req Frame"
#घोषणा IEFT_MPA_KEY_REP  "MPA ID Rep Frame"
#घोषणा IETF_MPA_KEY_SIZE 16
#घोषणा IETF_MPA_VERSION  1
#घोषणा IETF_MAX_PRIV_DATA_LEN 512
#घोषणा IETF_MPA_FRAME_SIZE    20
#घोषणा IETF_RTR_MSG_SIZE      4
#घोषणा IETF_MPA_V2_FLAG       0x10
#घोषणा SNDMARKER_SEQNMASK     0x000001FF

#घोषणा I40IW_MAX_IETF_SIZE      32

/* IETF RTR MSG Fields               */
#घोषणा IETF_PEER_TO_PEER       0x8000
#घोषणा IETF_FLPDU_ZERO_LEN     0x4000
#घोषणा IETF_RDMA0_WRITE        0x8000
#घोषणा IETF_RDMA0_READ         0x4000
#घोषणा IETF_NO_IRD_ORD         0x3FFF

/* HW-supported IRD sizes*/
#घोषणा	I40IW_HW_IRD_SETTING_2	2
#घोषणा	I40IW_HW_IRD_SETTING_4	4
#घोषणा	I40IW_HW_IRD_SETTING_8	8
#घोषणा	I40IW_HW_IRD_SETTING_16	16
#घोषणा	I40IW_HW_IRD_SETTING_32	32
#घोषणा	I40IW_HW_IRD_SETTING_64	64

#घोषणा MAX_PORTS		65536
#घोषणा I40IW_VLAN_PRIO_SHIFT   13

क्रमागत ietf_mpa_flags अणु
	IETF_MPA_FLAGS_MARKERS = 0x80,	/* receive Markers */
	IETF_MPA_FLAGS_CRC = 0x40,	/* receive Markers */
	IETF_MPA_FLAGS_REJECT = 0x20,	/* Reject */
पूर्ण;

काष्ठा ietf_mpa_v1 अणु
	u8 key[IETF_MPA_KEY_SIZE];
	u8 flags;
	u8 rev;
	__be16 priv_data_len;
	u8 priv_data[];
पूर्ण;

#घोषणा ietf_mpa_req_resp_frame ietf_mpa_frame

काष्ठा ietf_rtr_msg अणु
	__be16 ctrl_ird;
	__be16 ctrl_ord;
पूर्ण;

काष्ठा ietf_mpa_v2 अणु
	u8 key[IETF_MPA_KEY_SIZE];
	u8 flags;
	u8 rev;
	__be16 priv_data_len;
	काष्ठा ietf_rtr_msg rtr_msg;
	u8 priv_data[];
पूर्ण;

काष्ठा i40iw_cm_node;
क्रमागत i40iw_समयr_type अणु
	I40IW_TIMER_TYPE_SEND,
	I40IW_TIMER_TYPE_RECV,
	I40IW_TIMER_NODE_CLEANUP,
	I40IW_TIMER_TYPE_CLOSE,
पूर्ण;

#घोषणा I40IW_PASSIVE_STATE_INDICATED    0
#घोषणा I40IW_DO_NOT_SEND_RESET_EVENT    1
#घोषणा I40IW_SEND_RESET_EVENT           2

#घोषणा MAX_I40IW_IFS 4

#घोषणा SET_ACK 0x1
#घोषणा SET_SYN 0x2
#घोषणा SET_FIN 0x4
#घोषणा SET_RST 0x8

#घोषणा TCP_OPTIONS_PADDING     3

काष्ठा option_base अणु
	u8 optionnum;
	u8 length;
पूर्ण;

क्रमागत option_numbers अणु
	OPTION_NUMBER_END,
	OPTION_NUMBER_NONE,
	OPTION_NUMBER_MSS,
	OPTION_NUMBER_WINDOW_SCALE,
	OPTION_NUMBER_SACK_PERM,
	OPTION_NUMBER_SACK,
	OPTION_NUMBER_WRITE0 = 0xbc
पूर्ण;

काष्ठा option_mss अणु
	u8 optionnum;
	u8 length;
	__be16 mss;
पूर्ण;

काष्ठा option_winकरोwscale अणु
	u8 optionnum;
	u8 length;
	u8 shअगरtcount;
पूर्ण;

जोड़ all_known_options अणु
	अक्षर as_end;
	काष्ठा option_base as_base;
	काष्ठा option_mss as_mss;
	काष्ठा option_winकरोwscale as_winकरोwscale;
पूर्ण;

काष्ठा i40iw_समयr_entry अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ समयtosend;	/* jअगरfies */
	काष्ठा i40iw_puda_buf *sqbuf;
	u32 type;
	u32 retrycount;
	u32 retranscount;
	u32 context;
	u32 send_retrans;
	पूर्णांक बंद_when_complete;
पूर्ण;

#घोषणा I40IW_DEFAULT_RETRYS	64
#घोषणा I40IW_DEFAULT_RETRANS	8
#घोषणा I40IW_DEFAULT_TTL	0x40
#घोषणा I40IW_DEFAULT_RTT_VAR	0x6
#घोषणा I40IW_DEFAULT_SS_THRESH 0x3FFFFFFF
#घोषणा I40IW_DEFAULT_REXMIT_THRESH 8

#घोषणा I40IW_RETRY_TIMEOUT   HZ
#घोषणा I40IW_SHORT_TIME      10
#घोषणा I40IW_LONG_TIME       (2 * HZ)
#घोषणा I40IW_MAX_TIMEOUT     ((अचिन्हित दीर्घ)(12 * HZ))

#घोषणा I40IW_CM_HASHTABLE_SIZE         1024
#घोषणा I40IW_CM_TCP_TIMER_INTERVAL     3000
#घोषणा I40IW_CM_DEFAULT_MTU            1540
#घोषणा I40IW_CM_DEFAULT_FRAME_CNT      10
#घोषणा I40IW_CM_THREAD_STACK_SIZE      256
#घोषणा I40IW_CM_DEFAULT_RCV_WND        64240
#घोषणा I40IW_CM_DEFAULT_RCV_WND_SCALED 0x3fffc
#घोषणा I40IW_CM_DEFAULT_RCV_WND_SCALE  2
#घोषणा I40IW_CM_DEFAULT_FREE_PKTS      0x000A
#घोषणा I40IW_CM_FREE_PKT_LO_WATERMARK  2

#घोषणा I40IW_CM_DEFAULT_MSS   536

#घोषणा I40IW_CM_DEF_SEQ       0x159bf75f
#घोषणा I40IW_CM_DEF_LOCAL_ID  0x3b47

#घोषणा I40IW_CM_DEF_SEQ2      0x18ed5740
#घोषणा I40IW_CM_DEF_LOCAL_ID2 0xb807
#घोषणा MAX_CM_BUFFER   (I40IW_MAX_IETF_SIZE + IETF_MAX_PRIV_DATA_LEN)

प्रकार u32 i40iw_addr_t;

#घोषणा i40iw_cm_tsa_context i40iw_qp_context

काष्ठा i40iw_qp;

/* cm node transition states */
क्रमागत i40iw_cm_node_state अणु
	I40IW_CM_STATE_UNKNOWN,
	I40IW_CM_STATE_INITED,
	I40IW_CM_STATE_LISTENING,
	I40IW_CM_STATE_SYN_RCVD,
	I40IW_CM_STATE_SYN_SENT,
	I40IW_CM_STATE_ONE_SIDE_ESTABLISHED,
	I40IW_CM_STATE_ESTABLISHED,
	I40IW_CM_STATE_ACCEPTING,
	I40IW_CM_STATE_MPAREQ_SENT,
	I40IW_CM_STATE_MPAREQ_RCVD,
	I40IW_CM_STATE_MPAREJ_RCVD,
	I40IW_CM_STATE_OFFLOADED,
	I40IW_CM_STATE_FIN_WAIT1,
	I40IW_CM_STATE_FIN_WAIT2,
	I40IW_CM_STATE_CLOSE_WAIT,
	I40IW_CM_STATE_TIME_WAIT,
	I40IW_CM_STATE_LAST_ACK,
	I40IW_CM_STATE_CLOSING,
	I40IW_CM_STATE_LISTENER_DESTROYED,
	I40IW_CM_STATE_CLOSED
पूर्ण;

क्रमागत mpa_frame_version अणु
	IETF_MPA_V1 = 1,
	IETF_MPA_V2 = 2
पूर्ण;

क्रमागत mpa_frame_key अणु
	MPA_KEY_REQUEST,
	MPA_KEY_REPLY
पूर्ण;

क्रमागत send_rdma0 अणु
	SEND_RDMA_READ_ZERO = 1,
	SEND_RDMA_WRITE_ZERO = 2
पूर्ण;

क्रमागत i40iw_tcpip_pkt_type अणु
	I40IW_PKT_TYPE_UNKNOWN,
	I40IW_PKT_TYPE_SYN,
	I40IW_PKT_TYPE_SYNACK,
	I40IW_PKT_TYPE_ACK,
	I40IW_PKT_TYPE_FIN,
	I40IW_PKT_TYPE_RST
पूर्ण;

/* CM context params */
काष्ठा i40iw_cm_tcp_context अणु
	u8 client;

	u32 loc_seq_num;
	u32 loc_ack_num;
	u32 rem_ack_num;
	u32 rcv_nxt;

	u32 loc_id;
	u32 rem_id;

	u32 snd_wnd;
	u32 max_snd_wnd;

	u32 rcv_wnd;
	u32 mss;
	u8 snd_wscale;
	u8 rcv_wscale;
पूर्ण;

क्रमागत i40iw_cm_listener_state अणु
	I40IW_CM_LISTENER_PASSIVE_STATE = 1,
	I40IW_CM_LISTENER_ACTIVE_STATE = 2,
	I40IW_CM_LISTENER_EITHER_STATE = 3
पूर्ण;

काष्ठा i40iw_cm_listener अणु
	काष्ठा list_head list;
	काष्ठा i40iw_cm_core *cm_core;
	u8 loc_mac[ETH_ALEN];
	u32 loc_addr[4];
	u16 loc_port;
	काष्ठा iw_cm_id *cm_id;
	atomic_t ref_count;
	काष्ठा i40iw_device *iwdev;
	atomic_t pend_accepts_cnt;
	पूर्णांक backlog;
	क्रमागत i40iw_cm_listener_state listener_state;
	u32 reused_node;
	u8 user_pri;
	u8 tos;
	u16 vlan_id;
	bool qhash_set;
	bool ipv4;
	काष्ठा list_head child_listen_list;

पूर्ण;

काष्ठा i40iw_kmem_info अणु
	व्योम *addr;
	u32 size;
पूर्ण;

/* per connection node and node state inक्रमmation */
काष्ठा i40iw_cm_node अणु
	u32 loc_addr[4], rem_addr[4];
	u16 loc_port, rem_port;
	u16 vlan_id;
	क्रमागत i40iw_cm_node_state state;
	u8 loc_mac[ETH_ALEN];
	u8 rem_mac[ETH_ALEN];
	atomic_t ref_count;
	काष्ठा i40iw_qp *iwqp;
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_sc_dev *dev;
	काष्ठा i40iw_cm_tcp_context tcp_cntxt;
	काष्ठा i40iw_cm_core *cm_core;
	काष्ठा i40iw_cm_node *loopbackpartner;
	काष्ठा i40iw_समयr_entry *send_entry;
	काष्ठा i40iw_समयr_entry *बंद_entry;
	spinlock_t retrans_list_lock; /* cm transmit packet */
	क्रमागत send_rdma0 send_rdma0_op;
	u16 ird_size;
	u16 ord_size;
	u16     mpav2_ird_ord;
	काष्ठा iw_cm_id *cm_id;
	काष्ठा list_head list;
	bool accelerated;
	काष्ठा i40iw_cm_listener *listener;
	पूर्णांक apbvt_set;
	पूर्णांक accept_pend;
	काष्ठा list_head समयr_entry;
	काष्ठा list_head reset_entry;
	काष्ठा list_head tearकरोwn_entry;
	atomic_t passive_state;
	bool qhash_set;
	u8 user_pri;
	u8 tos;
	bool ipv4;
	bool snd_mark_en;
	u16 lsmm_size;
	क्रमागत mpa_frame_version mpa_frame_rev;
	काष्ठा i40iw_kmem_info pdata;
	जोड़ अणु
		काष्ठा ietf_mpa_v1 mpa_frame;
		काष्ठा ietf_mpa_v2 mpa_v2_frame;
	पूर्ण;

	u8 pdata_buf[IETF_MAX_PRIV_DATA_LEN];
	काष्ठा i40iw_kmem_info mpa_hdr;
	bool ack_rcvd;
पूर्ण;

/* काष्ठाure क्रम client or CM to fill when making CM api calls. */
/*	- only need to set relevant data, based on op. */
काष्ठा i40iw_cm_info अणु
	काष्ठा iw_cm_id *cm_id;
	u16 loc_port;
	u16 rem_port;
	u32 loc_addr[4];
	u32 rem_addr[4];
	u16 vlan_id;
	पूर्णांक backlog;
	u8 user_pri;
	u8 tos;
	bool ipv4;
पूर्ण;

/* CM event codes */
क्रमागत i40iw_cm_event_type अणु
	I40IW_CM_EVENT_UNKNOWN,
	I40IW_CM_EVENT_ESTABLISHED,
	I40IW_CM_EVENT_MPA_REQ,
	I40IW_CM_EVENT_MPA_CONNECT,
	I40IW_CM_EVENT_MPA_ACCEPT,
	I40IW_CM_EVENT_MPA_REJECT,
	I40IW_CM_EVENT_MPA_ESTABLISHED,
	I40IW_CM_EVENT_CONNECTED,
	I40IW_CM_EVENT_RESET,
	I40IW_CM_EVENT_ABORTED
पूर्ण;

/* event to post to CM event handler */
काष्ठा i40iw_cm_event अणु
	क्रमागत i40iw_cm_event_type type;
	काष्ठा i40iw_cm_info cm_info;
	काष्ठा work_काष्ठा event_work;
	काष्ठा i40iw_cm_node *cm_node;
पूर्ण;

काष्ठा i40iw_cm_core अणु
	काष्ठा i40iw_device *iwdev;
	काष्ठा i40iw_sc_dev *dev;

	काष्ठा list_head listen_nodes;
	काष्ठा list_head accelerated_list;
	काष्ठा list_head non_accelerated_list;

	काष्ठा समयr_list tcp_समयr;

	काष्ठा workqueue_काष्ठा *event_wq;
	काष्ठा workqueue_काष्ठा *disconn_wq;

	spinlock_t ht_lock; /* manage hash table */
	spinlock_t listen_list_lock; /* listen list */
	spinlock_t apbvt_lock; /*manage apbvt entries*/

	अचिन्हित दीर्घ ports_in_use[BITS_TO_LONGS(MAX_PORTS)];

	u64	stats_nodes_created;
	u64	stats_nodes_destroyed;
	u64	stats_listen_created;
	u64	stats_listen_destroyed;
	u64	stats_listen_nodes_created;
	u64	stats_listen_nodes_destroyed;
	u64	stats_loopbacks;
	u64	stats_accepts;
	u64	stats_rejects;
	u64	stats_connect_errs;
	u64	stats_passive_errs;
	u64	stats_pkt_retrans;
	u64	stats_backlog_drops;
पूर्ण;

पूर्णांक i40iw_schedule_cm_समयr(काष्ठा i40iw_cm_node *cm_node,
			    काष्ठा i40iw_puda_buf *sqbuf,
			    क्रमागत i40iw_समयr_type type,
			    पूर्णांक send_retrans,
			    पूर्णांक बंद_when_complete);

पूर्णांक i40iw_accept(काष्ठा iw_cm_id *, काष्ठा iw_cm_conn_param *);
पूर्णांक i40iw_reject(काष्ठा iw_cm_id *, स्थिर व्योम *, u8);
पूर्णांक i40iw_connect(काष्ठा iw_cm_id *, काष्ठा iw_cm_conn_param *);
पूर्णांक i40iw_create_listen(काष्ठा iw_cm_id *, पूर्णांक);
पूर्णांक i40iw_destroy_listen(काष्ठा iw_cm_id *);

पूर्णांक i40iw_cm_start(काष्ठा i40iw_device *);
पूर्णांक i40iw_cm_stop(काष्ठा i40iw_device *);

पूर्णांक i40iw_arp_table(काष्ठा i40iw_device *iwdev,
		    u32 *ip_addr,
		    bool ipv4,
		    u8 *mac_addr,
		    u32 action);

व्योम i40iw_अगर_notअगरy(काष्ठा i40iw_device *iwdev, काष्ठा net_device *netdev,
		     u32 *ipaddr, bool ipv4, bool अगरup);
व्योम i40iw_cm_tearकरोwn_connections(काष्ठा i40iw_device *iwdev, u32 *ipaddr,
				   काष्ठा i40iw_cm_info *nfo,
				   bool disconnect_all);
bool i40iw_port_in_use(काष्ठा i40iw_cm_core *cm_core, u16 port);
#पूर्ण_अगर /* I40IW_CM_H */
