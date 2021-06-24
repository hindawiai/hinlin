<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित __TCP_COMMON__
#घोषणा __TCP_COMMON__

/********************/
/* TCP FW CONSTANTS */
/********************/

#घोषणा TCP_INVALID_TIMEOUT_VAL	-1

/* OOO opaque data received from LL2 */
काष्ठा ooo_opaque अणु
	__le32 cid;
	u8 drop_isle;
	u8 drop_size;
	u8 ooo_opcode;
	u8 ooo_isle;
पूर्ण;

/* tcp connect mode क्रमागत */
क्रमागत tcp_connect_mode अणु
	TCP_CONNECT_ACTIVE,
	TCP_CONNECT_PASSIVE,
	MAX_TCP_CONNECT_MODE
पूर्ण;

/* tcp function init parameters */
काष्ठा tcp_init_params अणु
	__le32 two_msl_समयr;
	__le16 tx_sws_समयr;
	u8 max_fin_rt;
	u8 reserved[9];
पूर्ण;

/* tcp IPv4/IPv6 क्रमागत */
क्रमागत tcp_ip_version अणु
	TCP_IPV4,
	TCP_IPV6,
	MAX_TCP_IP_VERSION
पूर्ण;

/* tcp offload parameters */
काष्ठा tcp_offload_params अणु
	__le16 local_mac_addr_lo;
	__le16 local_mac_addr_mid;
	__le16 local_mac_addr_hi;
	__le16 remote_mac_addr_lo;
	__le16 remote_mac_addr_mid;
	__le16 remote_mac_addr_hi;
	__le16 vlan_id;
	__le16 flags;
#घोषणा TCP_OFFLOAD_PARAMS_TS_EN_MASK			0x1
#घोषणा TCP_OFFLOAD_PARAMS_TS_EN_SHIFT			0
#घोषणा TCP_OFFLOAD_PARAMS_DA_EN_MASK			0x1
#घोषणा TCP_OFFLOAD_PARAMS_DA_EN_SHIFT			1
#घोषणा TCP_OFFLOAD_PARAMS_KA_EN_MASK			0x1
#घोषणा TCP_OFFLOAD_PARAMS_KA_EN_SHIFT			2
#घोषणा TCP_OFFLOAD_PARAMS_ECN_SENDER_EN_MASK		0x1
#घोषणा TCP_OFFLOAD_PARAMS_ECN_SENDER_EN_SHIFT		3
#घोषणा TCP_OFFLOAD_PARAMS_ECN_RECEIVER_EN_MASK		0x1
#घोषणा TCP_OFFLOAD_PARAMS_ECN_RECEIVER_EN_SHIFT	4
#घोषणा TCP_OFFLOAD_PARAMS_NAGLE_EN_MASK		0x1
#घोषणा TCP_OFFLOAD_PARAMS_NAGLE_EN_SHIFT		5
#घोषणा TCP_OFFLOAD_PARAMS_DA_CNT_EN_MASK		0x1
#घोषणा TCP_OFFLOAD_PARAMS_DA_CNT_EN_SHIFT		6
#घोषणा TCP_OFFLOAD_PARAMS_FIN_SENT_MASK		0x1
#घोषणा TCP_OFFLOAD_PARAMS_FIN_SENT_SHIFT		7
#घोषणा TCP_OFFLOAD_PARAMS_FIN_RECEIVED_MASK		0x1
#घोषणा TCP_OFFLOAD_PARAMS_FIN_RECEIVED_SHIFT		8
#घोषणा TCP_OFFLOAD_PARAMS_RESERVED_MASK		0x7F
#घोषणा TCP_OFFLOAD_PARAMS_RESERVED_SHIFT		9
	u8 ip_version;
	u8 reserved0[3];
	__le32 remote_ip[4];
	__le32 local_ip[4];
	__le32 flow_label;
	u8 ttl;
	u8 tos_or_tc;
	__le16 remote_port;
	__le16 local_port;
	__le16 mss;
	u8 rcv_wnd_scale;
	u8 connect_mode;
	__le16 srtt;
	__le32 ss_thresh;
	__le32 rcv_wnd;
	__le32 cwnd;
	u8 ka_max_probe_cnt;
	u8 dup_ack_theshold;
	__le16 reserved1;
	__le32 ka_समयout;
	__le32 ka_पूर्णांकerval;
	__le32 max_rt_समय;
	__le32 initial_rcv_wnd;
	__le32 rcv_next;
	__le32 snd_una;
	__le32 snd_next;
	__le32 snd_max;
	__le32 snd_wnd;
	__le32 snd_wl1;
	__le32 ts_recent;
	__le32 ts_recent_age;
	__le32 total_rt;
	__le32 ka_समयout_delta;
	__le32 rt_समयout_delta;
	u8 dup_ack_cnt;
	u8 snd_wnd_probe_cnt;
	u8 ka_probe_cnt;
	u8 rt_cnt;
	__le16 rtt_var;
	__le16 fw_पूर्णांकernal;
	u8 snd_wnd_scale;
	u8 ack_frequency;
	__le16 da_समयout_value;
	__le32 reserved3;
पूर्ण;

/* tcp offload parameters */
काष्ठा tcp_offload_params_opt2 अणु
	__le16 local_mac_addr_lo;
	__le16 local_mac_addr_mid;
	__le16 local_mac_addr_hi;
	__le16 remote_mac_addr_lo;
	__le16 remote_mac_addr_mid;
	__le16 remote_mac_addr_hi;
	__le16 vlan_id;
	__le16 flags;
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_TS_EN_MASK	0x1
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_TS_EN_SHIFT	0
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_DA_EN_MASK	0x1
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_DA_EN_SHIFT	1
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_KA_EN_MASK	0x1
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_KA_EN_SHIFT	2
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_ECN_EN_MASK	0x1
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_ECN_EN_SHIFT	3
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_RESERVED0_MASK	0xFFF
#घोषणा TCP_OFFLOAD_PARAMS_OPT2_RESERVED0_SHIFT	4
	u8 ip_version;
	u8 reserved1[3];
	__le32 remote_ip[4];
	__le32 local_ip[4];
	__le32 flow_label;
	u8 ttl;
	u8 tos_or_tc;
	__le16 remote_port;
	__le16 local_port;
	__le16 mss;
	u8 rcv_wnd_scale;
	u8 connect_mode;
	__le16 syn_ip_payload_length;
	__le32 syn_phy_addr_lo;
	__le32 syn_phy_addr_hi;
	__le32 cwnd;
	u8 ka_max_probe_cnt;
	u8 reserved2[3];
	__le32 ka_समयout;
	__le32 ka_पूर्णांकerval;
	__le32 max_rt_समय;
	__le32 reserved3[16];
पूर्ण;

/* tcp IPv4/IPv6 क्रमागत */
क्रमागत tcp_seg_placement_event अणु
	TCP_EVENT_ADD_PEN,
	TCP_EVENT_ADD_NEW_ISLE,
	TCP_EVENT_ADD_ISLE_RIGHT,
	TCP_EVENT_ADD_ISLE_LEFT,
	TCP_EVENT_JOIN,
	TCP_EVENT_DELETE_ISLES,
	TCP_EVENT_NOP,
	MAX_TCP_SEG_PLACEMENT_EVENT
पूर्ण;

/* tcp init parameters */
काष्ठा tcp_update_params अणु
	__le16 flags;
#घोषणा TCP_UPDATE_PARAMS_REMOTE_MAC_ADDR_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_REMOTE_MAC_ADDR_CHANGED_SHIFT		0
#घोषणा TCP_UPDATE_PARAMS_MSS_CHANGED_MASK			0x1
#घोषणा TCP_UPDATE_PARAMS_MSS_CHANGED_SHIFT			1
#घोषणा TCP_UPDATE_PARAMS_TTL_CHANGED_MASK			0x1
#घोषणा TCP_UPDATE_PARAMS_TTL_CHANGED_SHIFT			2
#घोषणा TCP_UPDATE_PARAMS_TOS_OR_TC_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_TOS_OR_TC_CHANGED_SHIFT		3
#घोषणा TCP_UPDATE_PARAMS_KA_TIMEOUT_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_KA_TIMEOUT_CHANGED_SHIFT		4
#घोषणा TCP_UPDATE_PARAMS_KA_INTERVAL_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_KA_INTERVAL_CHANGED_SHIFT		5
#घोषणा TCP_UPDATE_PARAMS_MAX_RT_TIME_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_MAX_RT_TIME_CHANGED_SHIFT		6
#घोषणा TCP_UPDATE_PARAMS_FLOW_LABEL_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_FLOW_LABEL_CHANGED_SHIFT		7
#घोषणा TCP_UPDATE_PARAMS_INITIAL_RCV_WND_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_INITIAL_RCV_WND_CHANGED_SHIFT		8
#घोषणा TCP_UPDATE_PARAMS_KA_MAX_PROBE_CNT_CHANGED_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_KA_MAX_PROBE_CNT_CHANGED_SHIFT	9
#घोषणा TCP_UPDATE_PARAMS_KA_EN_CHANGED_MASK			0x1
#घोषणा TCP_UPDATE_PARAMS_KA_EN_CHANGED_SHIFT			10
#घोषणा TCP_UPDATE_PARAMS_NAGLE_EN_CHANGED_MASK			0x1
#घोषणा TCP_UPDATE_PARAMS_NAGLE_EN_CHANGED_SHIFT		11
#घोषणा TCP_UPDATE_PARAMS_KA_EN_MASK				0x1
#घोषणा TCP_UPDATE_PARAMS_KA_EN_SHIFT				12
#घोषणा TCP_UPDATE_PARAMS_NAGLE_EN_MASK				0x1
#घोषणा TCP_UPDATE_PARAMS_NAGLE_EN_SHIFT			13
#घोषणा TCP_UPDATE_PARAMS_KA_RESTART_MASK			0x1
#घोषणा TCP_UPDATE_PARAMS_KA_RESTART_SHIFT			14
#घोषणा TCP_UPDATE_PARAMS_RETRANSMIT_RESTART_MASK		0x1
#घोषणा TCP_UPDATE_PARAMS_RETRANSMIT_RESTART_SHIFT		15
	__le16 remote_mac_addr_lo;
	__le16 remote_mac_addr_mid;
	__le16 remote_mac_addr_hi;
	__le16 mss;
	u8 ttl;
	u8 tos_or_tc;
	__le32 ka_समयout;
	__le32 ka_पूर्णांकerval;
	__le32 max_rt_समय;
	__le32 flow_label;
	__le32 initial_rcv_wnd;
	u8 ka_max_probe_cnt;
	u8 reserved1[7];
पूर्ण;

/* toe upload parameters */
काष्ठा tcp_upload_params अणु
	__le32 rcv_next;
	__le32 snd_una;
	__le32 snd_next;
	__le32 snd_max;
	__le32 snd_wnd;
	__le32 rcv_wnd;
	__le32 snd_wl1;
	__le32 cwnd;
	__le32 ss_thresh;
	__le16 srtt;
	__le16 rtt_var;
	__le32 ts_समय;
	__le32 ts_recent;
	__le32 ts_recent_age;
	__le32 total_rt;
	__le32 ka_समयout_delta;
	__le32 rt_समयout_delta;
	u8 dup_ack_cnt;
	u8 snd_wnd_probe_cnt;
	u8 ka_probe_cnt;
	u8 rt_cnt;
	__le32 reserved;
पूर्ण;

#पूर्ण_अगर /* __TCP_COMMON__ */
