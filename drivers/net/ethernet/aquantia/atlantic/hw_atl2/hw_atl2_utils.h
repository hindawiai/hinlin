<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित HW_ATL2_UTILS_H
#घोषणा HW_ATL2_UTILS_H

#समावेश "aq_hw.h"

/* F W    A P I */

काष्ठा link_options_s अणु
	u8 link_up:1;
	u8 link_renegotiate:1;
	u8 minimal_link_speed:1;
	u8 पूर्णांकernal_loopback:1;
	u8 बाह्यal_loopback:1;
	u8 rate_10M_hd:1;
	u8 rate_100M_hd:1;
	u8 rate_1G_hd:1;

	u8 rate_10M:1;
	u8 rate_100M:1;
	u8 rate_1G:1;
	u8 rate_2P5G:1;
	u8 rate_N2P5G:1;
	u8 rate_5G:1;
	u8 rate_N5G:1;
	u8 rate_10G:1;

	u8 eee_100M:1;
	u8 eee_1G:1;
	u8 eee_2P5G:1;
	u8 eee_5G:1;
	u8 eee_10G:1;
	u8 rsvd3:3;

	u8 छोड़ो_rx:1;
	u8 छोड़ो_tx:1;
	u8 rsvd4:1;
	u8 करोwnshअगरt:1;
	u8 करोwnshअगरt_retry:4;
पूर्ण;

काष्ठा link_control_s अणु
	u8 mode:4;
	u8 disable_crc_corruption:1;
	u8 discard_लघु_frames:1;
	u8 flow_control_mode:1;
	u8 disable_length_check:1;

	u8 discard_errored_frames:1;
	u8 control_frame_enable:1;
	u8 enable_tx_padding:1;
	u8 enable_crc_क्रमwarding:1;
	u8 enable_frame_padding_removal_rx: 1;
	u8 promiscuous_mode: 1;
	u8 rsvd:2;

	u16 rsvd2;
पूर्ण;

काष्ठा thermal_shutकरोwn_s अणु
	u8 enable:1;
	u8 warning_enable:1;
	u8 rsvd:6;

	u8 shutकरोwn_temperature;
	u8 cold_temperature;
	u8 warning_temperature;
पूर्ण;

काष्ठा mac_address_s अणु
	u8 mac_address[6];
पूर्ण;

काष्ठा mac_address_aligned_s अणु
	काष्ठा mac_address_s aligned;
	u16 rsvd;
पूर्ण;

काष्ठा sleep_proxy_s अणु
	काष्ठा wake_on_lan_s अणु
		u8 wake_on_magic_packet:1;
		u8 wake_on_pattern:1;
		u8 wake_on_link_up:1;
		u8 wake_on_link_करोwn:1;
		u8 wake_on_ping:1;
		u8 wake_on_समयr:1;
		u8 rsvd:2;

		u8 rsvd2;
		u16 rsvd3;

		u32 link_up_समयout;
		u32 link_करोwn_समयout;
		u32 समयr;
	पूर्ण wake_on_lan;

	काष्ठा अणु
		u32 mask[4];
		u32 crc32;
	पूर्ण wake_up_pattern[8];

	काष्ठा __packed अणु
		u8 arp_responder:1;
		u8 echo_responder:1;
		u8 igmp_client:1;
		u8 echo_truncate:1;
		u8 address_guard:1;
		u8 ignore_fragmented:1;
		u8 rsvd:2;

		u16 echo_max_len;
		u8 rsvd2;
	पूर्ण ipv4_offload;

	u32 ipv4_offload_addr[8];
	u32 reserved[8];

	काष्ठा __packed अणु
		u8 ns_responder:1;
		u8 echo_responder:1;
		u8 mld_client:1;
		u8 echo_truncate:1;
		u8 address_guard:1;
		u8 rsvd:3;

		u16 echo_max_len;
		u8 rsvd2;
	पूर्ण ipv6_offload;

	u32 ipv6_offload_addr[16][4];

	काष्ठा अणु
		u16 port[16];
	पूर्ण tcp_port_offload;

	काष्ठा अणु
		u16 port[16];
	पूर्ण udp_port_offload;

	काष्ठा अणु
		u32 retry_count;
		u32 retry_पूर्णांकerval;
	पूर्ण ka4_offload;

	काष्ठा अणु
		u32 समयout;
		u16 local_port;
		u16 remote_port;
		u8 remote_mac_addr[6];
		u16 rsvd;
		u32 rsvd2;
		u32 rsvd3;
		u16 rsvd4;
		u16 win_size;
		u32 seq_num;
		u32 ack_num;
		u32 local_ip;
		u32 remote_ip;
	पूर्ण ka4_connection[16];

	काष्ठा अणु
		u32 retry_count;
		u32 retry_पूर्णांकerval;
	पूर्ण ka6_offload;

	काष्ठा अणु
		u32 समयout;
		u16 local_port;
		u16 remote_port;
		u8 remote_mac_addr[6];
		u16 rsvd;
		u32 rsvd2;
		u32 rsvd3;
		u16 rsvd4;
		u16 win_size;
		u32 seq_num;
		u32 ack_num;
		u32 local_ip[4];
		u32 remote_ip[4];
	पूर्ण ka6_connection[16];

	काष्ठा अणु
		u32 rr_count;
		u32 rr_buf_len;
		u32 idx_offset;
		u32 rr__offset;
	पूर्ण mdns_offload;
पूर्ण;

काष्ठा छोड़ो_quanta_s अणु
	u16 quanta_10M;
	u16 threshold_10M;
	u16 quanta_100M;
	u16 threshold_100M;
	u16 quanta_1G;
	u16 threshold_1G;
	u16 quanta_2P5G;
	u16 threshold_2P5G;
	u16 quanta_5G;
	u16 threshold_5G;
	u16 quanta_10G;
	u16 threshold_10G;
पूर्ण;

काष्ठा data_buffer_status_s अणु
	u32 data_offset;
	u32 data_length;
पूर्ण;

काष्ठा device_caps_s अणु
	u8 finite_flashless:1;
	u8 cable_diag:1;
	u8 ncsi:1;
	u8 avb:1;
	u8 rsvd:4;

	u8 rsvd2;
	u16 rsvd3;
	u32 rsvd4;
पूर्ण;

काष्ठा version_s अणु
	काष्ठा bundle_version_t अणु
		u8 major;
		u8 minor;
		u16 build;
	पूर्ण bundle;
	काष्ठा mac_version_t अणु
		u8 major;
		u8 minor;
		u16 build;
	पूर्ण mac;
	काष्ठा phy_version_t अणु
		u8 major;
		u8 minor;
		u16 build;
	पूर्ण phy;
	u32 rsvd;
पूर्ण;

काष्ठा link_status_s अणु
	u8 link_state:4;
	u8 link_rate:4;

	u8 छोड़ो_tx:1;
	u8 छोड़ो_rx:1;
	u8 eee:1;
	u8 duplex:1;
	u8 rsvd:4;

	u16 rsvd2;
पूर्ण;

काष्ठा wol_status_s अणु
	u8 wake_count;
	u8 wake_reason;

	u16 wake_up_packet_length :12;
	u16 wake_up_pattern_number :3;
	u16 rsvd:1;

	u32 wake_up_packet[379];
पूर्ण;

काष्ठा mac_health_monitor_s अणु
	u8 mac_पढ़ोy:1;
	u8 mac_fault:1;
	u8 mac_flashless_finished:1;
	u8 rsvd:5;

	u8 mac_temperature;
	u16 mac_heart_beat;
	u16 mac_fault_code;
	u16 rsvd2;
पूर्ण;

काष्ठा phy_health_monitor_s अणु
	u8 phy_पढ़ोy:1;
	u8 phy_fault:1;
	u8 phy_hot_warning:1;
	u8 rsvd:5;

	u8 phy_temperature;
	u16 phy_heart_beat;
	u16 phy_fault_code;
	u16 rsvd2;
पूर्ण;

काष्ठा device_link_caps_s अणु
	u8 rsvd:3;
	u8 पूर्णांकernal_loopback:1;
	u8 बाह्यal_loopback:1;
	u8 rate_10M_hd:1;
	u8 rate_100M_hd:1;
	u8 rate_1G_hd:1;

	u8 rate_10M:1;
	u8 rate_100M:1;
	u8 rate_1G:1;
	u8 rate_2P5G:1;
	u8 rate_N2P5G:1;
	u8 rate_5G:1;
	u8 rate_N5G:1;
	u8 rate_10G:1;

	u8 rsvd3:1;
	u8 eee_100M:1;
	u8 eee_1G:1;
	u8 eee_2P5G:1;
	u8 rsvd4:1;
	u8 eee_5G:1;
	u8 rsvd5:1;
	u8 eee_10G:1;

	u8 छोड़ो_rx:1;
	u8 छोड़ो_tx:1;
	u8 pfc:1;
	u8 करोwnshअगरt:1;
	u8 करोwnshअगरt_retry:4;
पूर्ण;

काष्ठा sleep_proxy_caps_s अणु
	u8 ipv4_offload:1;
	u8 ipv6_offload:1;
	u8 tcp_port_offload:1;
	u8 udp_port_offload:1;
	u8 ka4_offload:1;
	u8 ka6_offload:1;
	u8 mdns_offload:1;
	u8 wake_on_ping:1;

	u8 wake_on_magic_packet:1;
	u8 wake_on_pattern:1;
	u8 wake_on_समयr:1;
	u8 wake_on_link:1;
	u8 wake_patterns_count:4;

	u8 ipv4_count;
	u8 ipv6_count;

	u8 tcp_port_offload_count;
	u8 udp_port_offload_count;

	u8 tcp4_ka_count;
	u8 tcp6_ka_count;

	u8 igmp_offload:1;
	u8 mld_offload:1;
	u8 rsvd:6;

	u8 rsvd2;
	u16 rsvd3;
पूर्ण;

काष्ठा lkp_link_caps_s अणु
	u8 rsvd:5;
	u8 rate_10M_hd:1;
	u8 rate_100M_hd:1;
	u8 rate_1G_hd:1;

	u8 rate_10M:1;
	u8 rate_100M:1;
	u8 rate_1G:1;
	u8 rate_2P5G:1;
	u8 rate_N2P5G:1;
	u8 rate_5G:1;
	u8 rate_N5G:1;
	u8 rate_10G:1;

	u8 rsvd2:1;
	u8 eee_100M:1;
	u8 eee_1G:1;
	u8 eee_2P5G:1;
	u8 rsvd3:1;
	u8 eee_5G:1;
	u8 rsvd4:1;
	u8 eee_10G:1;

	u8 छोड़ो_rx:1;
	u8 छोड़ो_tx:1;
	u8 rsvd5:6;
पूर्ण;

काष्ठा core_dump_s अणु
	u32 reg0;
	u32 reg1;
	u32 reg2;

	u32 hi;
	u32 lo;

	u32 regs[32];
पूर्ण;

काष्ठा trace_s अणु
	u32 sync_counter;
	u32 mem_buffer[0x1ff];
पूर्ण;

काष्ठा cable_diag_control_s अणु
	u8 toggle :1;
	u8 rsvd:7;

	u8 रुको_समयout_sec;
	u16 rsvd2;
पूर्ण;

काष्ठा cable_diag_lane_data_s अणु
	u8 result_code;
	u8 dist;
	u8 far_dist;
	u8 rsvd;
पूर्ण;

काष्ठा cable_diag_status_s अणु
	काष्ठा cable_diag_lane_data_s lane_data[4];
	u8 transact_id;
	u8 status:4;
	u8 rsvd:4;
	u16 rsvd2;
पूर्ण;

काष्ठा statistics_s अणु
	काष्ठा अणु
		u32 link_up;
		u32 link_करोwn;
	पूर्ण link;

	काष्ठा अणु
		u64 tx_unicast_octets;
		u64 tx_multicast_octets;
		u64 tx_broadcast_octets;
		u64 rx_unicast_octets;
		u64 rx_multicast_octets;
		u64 rx_broadcast_octets;

		u32 tx_unicast_frames;
		u32 tx_multicast_frames;
		u32 tx_broadcast_frames;
		u32 tx_errors;

		u32 rx_unicast_frames;
		u32 rx_multicast_frames;
		u32 rx_broadcast_frames;
		u32 rx_dropped_frames;
		u32 rx_error_frames;

		u32 tx_good_frames;
		u32 rx_good_frames;
		u32 reserve_fw_gap;
	पूर्ण msm;
	u32 मुख्य_loop_cycles;
	u32 reserve_fw_gap;
पूर्ण;

काष्ठा filter_caps_s अणु
	u8 l2_filters_base_index:6;
	u8 flexible_filter_mask:2;
	u8 l2_filter_count;
	u8 ethertype_filter_base_index;
	u8 ethertype_filter_count;

	u8 vlan_filter_base_index;
	u8 vlan_filter_count;
	u8 l3_ip4_filter_base_index:4;
	u8 l3_ip4_filter_count:4;
	u8 l3_ip6_filter_base_index:4;
	u8 l3_ip6_filter_count:4;

	u8 l4_filter_base_index:4;
	u8 l4_filter_count:4;
	u8 l4_flex_filter_base_index:4;
	u8 l4_flex_filter_count:4;
	u8 rslv_tbl_base_index;
	u8 rslv_tbl_count;
पूर्ण;

काष्ठा request_policy_s अणु
	काष्ठा अणु
		u8 all:1;
		u8 mcast:1;
		u8 rx_queue_tc_index:5;
		u8 queue_or_tc:1;
	पूर्ण promisc;

	काष्ठा अणु
		u8 accept:1;
		u8 rsvd:1;
		u8 rx_queue_tc_index:5;
		u8 queue_or_tc:1;
	पूर्ण bcast;

	काष्ठा अणु
		u8 accept:1;
		u8 rsvd:1;
		u8 rx_queue_tc_index:5;
		u8 queue_or_tc:1;
	पूर्ण mcast;

	u8 rsvd:8;
पूर्ण;

काष्ठा fw_पूर्णांकerface_in अणु
	u32 mtu;
	u32 rsvd1;
	काष्ठा mac_address_aligned_s mac_address;
	काष्ठा link_control_s link_control;
	u32 rsvd2;
	काष्ठा link_options_s link_options;
	u32 rsvd3;
	काष्ठा thermal_shutकरोwn_s thermal_shutकरोwn;
	u32 rsvd4;
	काष्ठा sleep_proxy_s sleep_proxy;
	u32 rsvd5;
	काष्ठा छोड़ो_quanta_s छोड़ो_quanta[8];
	काष्ठा cable_diag_control_s cable_diag_control;
	u32 rsvd6;
	काष्ठा data_buffer_status_s data_buffer_status;
	u32 rsvd7;
	काष्ठा request_policy_s request_policy;
पूर्ण;

काष्ठा transaction_counter_s अणु
	u16 transaction_cnt_a;
	u16 transaction_cnt_b;
पूर्ण;

काष्ठा management_status_s अणु
	काष्ठा mac_address_s mac_address;
	u16 vlan;

	काष्ठाअणु
		u32 enable : 1;
		u32 rsvd:31;
	पूर्ण flags;

	u32 rsvd1;
	u32 rsvd2;
	u32 rsvd3;
	u32 rsvd4;
	u32 rsvd5;
पूर्ण;

काष्ठा fw_पूर्णांकerface_out अणु
	काष्ठा transaction_counter_s transaction_id;
	काष्ठा version_s version;
	काष्ठा link_status_s link_status;
	काष्ठा wol_status_s wol_status;
	u32 rsvd;
	u32 rsvd2;
	काष्ठा mac_health_monitor_s mac_health_monitor;
	u32 rsvd3;
	u32 rsvd4;
	काष्ठा phy_health_monitor_s phy_health_monitor;
	u32 rsvd5;
	u32 rsvd6;
	काष्ठा cable_diag_status_s cable_diag_status;
	u32 rsvd7;
	काष्ठा device_link_caps_s device_link_caps;
	u32 rsvd8;
	काष्ठा sleep_proxy_caps_s sleep_proxy_caps;
	u32 rsvd9;
	काष्ठा lkp_link_caps_s lkp_link_caps;
	u32 rsvd10;
	काष्ठा core_dump_s core_dump;
	u32 rsvd11;
	काष्ठा statistics_s stats;
	u32 rsvd12;
	काष्ठा filter_caps_s filter_caps;
	काष्ठा device_caps_s device_caps;
	u32 rsvd13;
	काष्ठा management_status_s management_status;
	u32 reserve[21];
	काष्ठा trace_s trace;
पूर्ण;

#घोषणा  AQ_A2_FW_LINK_RATE_INVALID 0
#घोषणा  AQ_A2_FW_LINK_RATE_10M     1
#घोषणा  AQ_A2_FW_LINK_RATE_100M    2
#घोषणा  AQ_A2_FW_LINK_RATE_1G      3
#घोषणा  AQ_A2_FW_LINK_RATE_2G5     4
#घोषणा  AQ_A2_FW_LINK_RATE_5G      5
#घोषणा  AQ_A2_FW_LINK_RATE_10G     6

#घोषणा  AQ_HOST_MODE_INVALID      0U
#घोषणा  AQ_HOST_MODE_ACTIVE       1U
#घोषणा  AQ_HOST_MODE_SLEEP_PROXY  2U
#घोषणा  AQ_HOST_MODE_LOW_POWER    3U
#घोषणा  AQ_HOST_MODE_SHUTDOWN     4U

पूर्णांक hw_atl2_utils_initfw(काष्ठा aq_hw_s *self, स्थिर काष्ठा aq_fw_ops **fw_ops);

पूर्णांक hw_atl2_utils_soft_reset(काष्ठा aq_hw_s *self);

u32 hw_atl2_utils_get_fw_version(काष्ठा aq_hw_s *self);

पूर्णांक hw_atl2_utils_get_action_resolve_table_caps(काष्ठा aq_hw_s *self,
						u8 *base_index, u8 *count);

बाह्य स्थिर काष्ठा aq_fw_ops aq_a2_fw_ops;

#पूर्ण_अगर /* HW_ATL2_UTILS_H */
