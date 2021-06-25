<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_H
#घोषणा _MLXSW_SPECTRUM_H

#समावेश <linux/ethtool.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/list.h>
#समावेश <linux/dcbnl.h>
#समावेश <linux/in6.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/net_namespace.h>
#समावेश <linux/spinlock.h>
#समावेश <net/psample.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/red.h>
#समावेश <net/vxlan.h>
#समावेश <net/flow_offload.h>
#समावेश <net/inet_ecn.h>

#समावेश "port.h"
#समावेश "core.h"
#समावेश "core_acl_flex_keys.h"
#समावेश "core_acl_flex_actions.h"
#समावेश "reg.h"

#घोषणा MLXSW_SP_DEFAULT_VID (VLAN_N_VID - 1)

#घोषणा MLXSW_SP_FID_8021D_MAX 1024

#घोषणा MLXSW_SP_MID_MAX 7000

#घोषणा MLXSW_SP_KVD_LINEAR_SIZE 98304 /* entries */
#घोषणा MLXSW_SP_KVD_GRANULARITY 128

#घोषणा MLXSW_SP_RESOURCE_NAME_KVD "kvd"
#घोषणा MLXSW_SP_RESOURCE_NAME_KVD_LINEAR "linear"
#घोषणा MLXSW_SP_RESOURCE_NAME_KVD_HASH_SINGLE "hash_single"
#घोषणा MLXSW_SP_RESOURCE_NAME_KVD_HASH_DOUBLE "hash_double"
#घोषणा MLXSW_SP_RESOURCE_NAME_KVD_LINEAR_SINGLES "singles"
#घोषणा MLXSW_SP_RESOURCE_NAME_KVD_LINEAR_CHUNKS "chunks"
#घोषणा MLXSW_SP_RESOURCE_NAME_KVD_LINEAR_LARGE_CHUNKS "large_chunks"

#घोषणा MLXSW_SP_RESOURCE_NAME_SPAN "span_agents"

#घोषणा MLXSW_SP_RESOURCE_NAME_COUNTERS "counters"
#घोषणा MLXSW_SP_RESOURCE_NAME_COUNTERS_FLOW "flow"
#घोषणा MLXSW_SP_RESOURCE_NAME_COUNTERS_RIF "rif"

क्रमागत mlxsw_sp_resource_id अणु
	MLXSW_SP_RESOURCE_KVD = MLXSW_CORE_RESOURCE_MAX,
	MLXSW_SP_RESOURCE_KVD_LINEAR,
	MLXSW_SP_RESOURCE_KVD_HASH_SINGLE,
	MLXSW_SP_RESOURCE_KVD_HASH_DOUBLE,
	MLXSW_SP_RESOURCE_KVD_LINEAR_SINGLE,
	MLXSW_SP_RESOURCE_KVD_LINEAR_CHUNKS,
	MLXSW_SP_RESOURCE_KVD_LINEAR_LARGE_CHUNKS,
	MLXSW_SP_RESOURCE_SPAN,
	MLXSW_SP_RESOURCE_COUNTERS,
	MLXSW_SP_RESOURCE_COUNTERS_FLOW,
	MLXSW_SP_RESOURCE_COUNTERS_RIF,
	MLXSW_SP_RESOURCE_GLOBAL_POLICERS,
	MLXSW_SP_RESOURCE_SINGLE_RATE_POLICERS,
पूर्ण;

काष्ठा mlxsw_sp_port;
काष्ठा mlxsw_sp_rअगर;
काष्ठा mlxsw_sp_span_entry;
क्रमागत mlxsw_sp_l3proto;
जोड़ mlxsw_sp_l3addr;

काष्ठा mlxsw_sp_upper अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक ref_count;
पूर्ण;

क्रमागत mlxsw_sp_rअगर_type अणु
	MLXSW_SP_RIF_TYPE_SUBPORT,
	MLXSW_SP_RIF_TYPE_VLAN,
	MLXSW_SP_RIF_TYPE_FID,
	MLXSW_SP_RIF_TYPE_IPIP_LB, /* IP-in-IP loopback. */
	MLXSW_SP_RIF_TYPE_MAX,
पूर्ण;

काष्ठा mlxsw_sp_router_ops;

बाह्य स्थिर काष्ठा mlxsw_sp_router_ops mlxsw_sp1_router_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_router_ops mlxsw_sp2_router_ops;

काष्ठा mlxsw_sp_चयनdev_ops;

बाह्य स्थिर काष्ठा mlxsw_sp_चयनdev_ops mlxsw_sp1_चयनdev_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_चयनdev_ops mlxsw_sp2_चयनdev_ops;

क्रमागत mlxsw_sp_fid_type अणु
	MLXSW_SP_FID_TYPE_8021Q,
	MLXSW_SP_FID_TYPE_8021D,
	MLXSW_SP_FID_TYPE_RFID,
	MLXSW_SP_FID_TYPE_DUMMY,
	MLXSW_SP_FID_TYPE_MAX,
पूर्ण;

क्रमागत mlxsw_sp_nve_type अणु
	MLXSW_SP_NVE_TYPE_VXLAN,
पूर्ण;

काष्ठा mlxsw_sp_mid अणु
	काष्ठा list_head list;
	अचिन्हित अक्षर addr[ETH_ALEN];
	u16 fid;
	u16 mid;
	bool in_hw;
	अचिन्हित दीर्घ *ports_in_mid; /* bits array */
पूर्ण;

काष्ठा mlxsw_sp_sb;
काष्ठा mlxsw_sp_bridge;
काष्ठा mlxsw_sp_router;
काष्ठा mlxsw_sp_mr;
काष्ठा mlxsw_sp_acl;
काष्ठा mlxsw_sp_counter_pool;
काष्ठा mlxsw_sp_fid_core;
काष्ठा mlxsw_sp_kvdl;
काष्ठा mlxsw_sp_nve;
काष्ठा mlxsw_sp_kvdl_ops;
काष्ठा mlxsw_sp_mr_tcam_ops;
काष्ठा mlxsw_sp_acl_rulei_ops;
काष्ठा mlxsw_sp_acl_tcam_ops;
काष्ठा mlxsw_sp_nve_ops;
काष्ठा mlxsw_sp_sb_ops;
काष्ठा mlxsw_sp_sb_vals;
काष्ठा mlxsw_sp_port_type_speed_ops;
काष्ठा mlxsw_sp_ptp_state;
काष्ठा mlxsw_sp_ptp_ops;
काष्ठा mlxsw_sp_span_ops;
काष्ठा mlxsw_sp_qdisc_state;
काष्ठा mlxsw_sp_mall_entry;

काष्ठा mlxsw_sp_port_mapping अणु
	u8 module;
	u8 width;
	u8 lane;
पूर्ण;

काष्ठा mlxsw_sp अणु
	काष्ठा mlxsw_sp_port **ports;
	काष्ठा mlxsw_core *core;
	स्थिर काष्ठा mlxsw_bus_info *bus_info;
	अचिन्हित अक्षर base_mac[ETH_ALEN];
	स्थिर अचिन्हित अक्षर *mac_mask;
	काष्ठा mlxsw_sp_upper *lags;
	काष्ठा mlxsw_sp_port_mapping **port_mapping;
	काष्ठा rhashtable sample_trigger_ht;
	काष्ठा mlxsw_sp_sb *sb;
	काष्ठा mlxsw_sp_bridge *bridge;
	काष्ठा mlxsw_sp_router *router;
	काष्ठा mlxsw_sp_mr *mr;
	काष्ठा mlxsw_afa *afa;
	काष्ठा mlxsw_sp_acl *acl;
	काष्ठा mlxsw_sp_fid_core *fid_core;
	काष्ठा mlxsw_sp_policer_core *policer_core;
	काष्ठा mlxsw_sp_kvdl *kvdl;
	काष्ठा mlxsw_sp_nve *nve;
	काष्ठा notअगरier_block netdevice_nb;
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी;
	काष्ठा mlxsw_sp_ptp_state *ptp_state;
	काष्ठा mlxsw_sp_counter_pool *counter_pool;
	काष्ठा mlxsw_sp_span *span;
	काष्ठा mlxsw_sp_trap *trap;
	स्थिर काष्ठा mlxsw_sp_चयनdev_ops *चयनdev_ops;
	स्थिर काष्ठा mlxsw_sp_kvdl_ops *kvdl_ops;
	स्थिर काष्ठा mlxsw_afa_ops *afa_ops;
	स्थिर काष्ठा mlxsw_afk_ops *afk_ops;
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *mr_tcam_ops;
	स्थिर काष्ठा mlxsw_sp_acl_rulei_ops *acl_rulei_ops;
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *acl_tcam_ops;
	स्थिर काष्ठा mlxsw_sp_nve_ops **nve_ops_arr;
	स्थिर काष्ठा mlxsw_sp_sb_vals *sb_vals;
	स्थिर काष्ठा mlxsw_sp_sb_ops *sb_ops;
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *port_type_speed_ops;
	स्थिर काष्ठा mlxsw_sp_ptp_ops *ptp_ops;
	स्थिर काष्ठा mlxsw_sp_span_ops *span_ops;
	स्थिर काष्ठा mlxsw_sp_policer_core_ops *policer_core_ops;
	स्थिर काष्ठा mlxsw_sp_trap_ops *trap_ops;
	स्थिर काष्ठा mlxsw_sp_mall_ops *mall_ops;
	स्थिर काष्ठा mlxsw_sp_router_ops *router_ops;
	स्थिर काष्ठा mlxsw_listener *listeners;
	माप_प्रकार listeners_count;
	u32 lowest_shaper_bs;
पूर्ण;

काष्ठा mlxsw_sp_ptp_ops अणु
	काष्ठा mlxsw_sp_ptp_घड़ी *
		(*घड़ी_init)(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा device *dev);
	व्योम (*घड़ी_fini)(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी);

	काष्ठा mlxsw_sp_ptp_state *(*init)(काष्ठा mlxsw_sp *mlxsw_sp);
	व्योम (*fini)(काष्ठा mlxsw_sp_ptp_state *ptp_state);

	/* Notअगरy a driver that a packet that might be PTP was received. Driver
	 * is responsible क्रम मुक्तing the passed-in SKB.
	 */
	व्योम (*receive)(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा sk_buff *skb,
			u8 local_port);

	/* Notअगरy a driver that a बारtamped packet was transmitted. Driver
	 * is responsible क्रम मुक्तing the passed-in SKB.
	 */
	व्योम (*transmitted)(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा sk_buff *skb,
			    u8 local_port);

	पूर्णांक (*hwtstamp_get)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा hwtstamp_config *config);
	पूर्णांक (*hwtstamp_set)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा hwtstamp_config *config);
	व्योम (*shaper_work)(काष्ठा work_काष्ठा *work);
	पूर्णांक (*get_ts_info)(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा ethtool_ts_info *info);
	पूर्णांक (*get_stats_count)(व्योम);
	व्योम (*get_stats_strings)(u8 **p);
	व्योम (*get_stats)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  u64 *data, पूर्णांक data_index);
पूर्ण;

अटल अंतरभूत काष्ठा mlxsw_sp_upper *
mlxsw_sp_lag_get(काष्ठा mlxsw_sp *mlxsw_sp, u16 lag_id)
अणु
	वापस &mlxsw_sp->lags[lag_id];
पूर्ण

काष्ठा mlxsw_sp_port_pcpu_stats अणु
	u64			rx_packets;
	u64			rx_bytes;
	u64			tx_packets;
	u64			tx_bytes;
	काष्ठा u64_stats_sync	syncp;
	u32			tx_dropped;
पूर्ण;

क्रमागत mlxsw_sp_sample_trigger_type अणु
	MLXSW_SP_SAMPLE_TRIGGER_TYPE_INGRESS,
	MLXSW_SP_SAMPLE_TRIGGER_TYPE_EGRESS,
	MLXSW_SP_SAMPLE_TRIGGER_TYPE_POLICY_ENGINE,
पूर्ण;

काष्ठा mlxsw_sp_sample_trigger अणु
	क्रमागत mlxsw_sp_sample_trigger_type type;
	u8 local_port; /* Reserved when trigger type is not ingress / egress. */
पूर्ण;

काष्ठा mlxsw_sp_sample_params अणु
	काष्ठा psample_group *psample_group;
	u32 trunc_size;
	u32 rate;
	bool truncate;
पूर्ण;

काष्ठा mlxsw_sp_bridge_port;
काष्ठा mlxsw_sp_fid;

काष्ठा mlxsw_sp_port_vlan अणु
	काष्ठा list_head list;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp_fid *fid;
	u16 vid;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	काष्ठा list_head bridge_vlan_node;
पूर्ण;

/* No need an पूर्णांकernal lock; At worse - miss a single periodic iteration */
काष्ठा mlxsw_sp_port_xstats अणु
	u64 ecn;
	u64 wred_drop[TC_MAX_QUEUE];
	u64 tail_drop[TC_MAX_QUEUE];
	u64 backlog[TC_MAX_QUEUE];
	u64 tx_bytes[IEEE_8021QAZ_MAX_TCS];
	u64 tx_packets[IEEE_8021QAZ_MAX_TCS];
पूर्ण;

काष्ठा mlxsw_sp_ptp_port_dir_stats अणु
	u64 packets;
	u64 बारtamps;
पूर्ण;

काष्ठा mlxsw_sp_ptp_port_stats अणु
	काष्ठा mlxsw_sp_ptp_port_dir_stats rx_gcd;
	काष्ठा mlxsw_sp_ptp_port_dir_stats tx_gcd;
पूर्ण;

काष्ठा mlxsw_sp_port अणु
	काष्ठा net_device *dev;
	काष्ठा mlxsw_sp_port_pcpu_stats __percpu *pcpu_stats;
	काष्ठा mlxsw_sp *mlxsw_sp;
	u8 local_port;
	u8 lagged:1,
	   split:1;
	u16 pvid;
	u16 lag_id;
	काष्ठा अणु
		u8 tx_छोड़ो:1,
		   rx_छोड़ो:1,
		   स्वतःneg:1;
	पूर्ण link;
	काष्ठा अणु
		काष्ठा ieee_ets *ets;
		काष्ठा ieee_maxrate *maxrate;
		काष्ठा ieee_pfc *pfc;
		क्रमागत mlxsw_reg_qpts_trust_state trust_state;
	पूर्ण dcb;
	काष्ठा mlxsw_sp_port_mapping mapping; /* mapping is स्थिरant during the
					       * mlxsw_sp_port lअगरeसमय, however
					       * the same localport can have
					       * dअगरferent mapping.
					       */
	काष्ठा अणु
		#घोषणा MLXSW_HW_STATS_UPDATE_TIME HZ
		काष्ठा rtnl_link_stats64 stats;
		काष्ठा mlxsw_sp_port_xstats xstats;
		काष्ठा delayed_work update_dw;
	पूर्ण periodic_hw_stats;
	काष्ठा list_head vlans_list;
	काष्ठा mlxsw_sp_port_vlan *शेष_vlan;
	काष्ठा mlxsw_sp_qdisc_state *qdisc;
	अचिन्हित acl_rule_count;
	काष्ठा mlxsw_sp_flow_block *ing_flow_block;
	काष्ठा mlxsw_sp_flow_block *eg_flow_block;
	काष्ठा अणु
		काष्ठा delayed_work shaper_dw;
		काष्ठा hwtstamp_config hwtstamp_config;
		u16 ing_types;
		u16 egr_types;
		काष्ठा mlxsw_sp_ptp_port_stats stats;
	पूर्ण ptp;
	u8 split_base_local_port;
	पूर्णांक max_mtu;
	u32 max_speed;
	काष्ठा mlxsw_sp_hdroom *hdroom;
	u64 module_overheat_initial_val;
पूर्ण;

काष्ठा mlxsw_sp_port_type_speed_ops अणु
	व्योम (*from_ptys_supported_port)(काष्ठा mlxsw_sp *mlxsw_sp,
					 u32 ptys_eth_proto,
					 काष्ठा ethtool_link_ksettings *cmd);
	व्योम (*from_ptys_link)(काष्ठा mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto,
			       अचिन्हित दीर्घ *mode);
	u32 (*from_ptys_speed)(काष्ठा mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto);
	व्योम (*from_ptys_link_mode)(काष्ठा mlxsw_sp *mlxsw_sp,
				    bool carrier_ok, u32 ptys_eth_proto,
				    काष्ठा ethtool_link_ksettings *cmd);
	पूर्णांक (*ptys_max_speed)(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 *p_max_speed);
	u32 (*to_ptys_advert_link)(काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd);
	u32 (*to_ptys_speed_lanes)(काष्ठा mlxsw_sp *mlxsw_sp, u8 width,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd);
	व्योम (*reg_ptys_eth_pack)(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *payload,
				  u8 local_port, u32 proto_admin, bool स्वतःneg);
	व्योम (*reg_ptys_eth_unpack)(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *payload,
				    u32 *p_eth_proto_cap,
				    u32 *p_eth_proto_admin,
				    u32 *p_eth_proto_oper);
	u32 (*ptys_proto_cap_masked_get)(u32 eth_proto_cap);
पूर्ण;

अटल अंतरभूत u8 mlxsw_sp_tunnel_ecn_decap(u8 outer_ecn, u8 inner_ecn,
					   bool *trap_en)
अणु
	bool set_ce = false;

	*trap_en = !!__INET_ECN_decapsulate(outer_ecn, inner_ecn, &set_ce);
	अगर (set_ce)
		वापस INET_ECN_CE;
	अन्यथा अगर (outer_ecn == INET_ECN_ECT_1 && inner_ecn == INET_ECN_ECT_0)
		वापस INET_ECN_ECT_1;
	अन्यथा
		वापस inner_ecn;
पूर्ण

अटल अंतरभूत काष्ठा net_device *
mlxsw_sp_bridge_vxlan_dev_find(काष्ठा net_device *br_dev)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(br_dev, dev, iter) अणु
		अगर (netअगर_is_vxlan(dev))
			वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool mlxsw_sp_bridge_has_vxlan(काष्ठा net_device *br_dev)
अणु
	वापस !!mlxsw_sp_bridge_vxlan_dev_find(br_dev);
पूर्ण

अटल अंतरभूत पूर्णांक
mlxsw_sp_vxlan_mapped_vid(स्थिर काष्ठा net_device *vxlan_dev, u16 *p_vid)
अणु
	काष्ठा bridge_vlan_info vinfo;
	u16 vid = 0;
	पूर्णांक err;

	err = br_vlan_get_pvid(vxlan_dev, &vid);
	अगर (err || !vid)
		जाओ out;

	err = br_vlan_get_info(vxlan_dev, vid, &vinfo);
	अगर (err || !(vinfo.flags & BRIDGE_VLAN_INFO_UNTAGGED))
		vid = 0;

out:
	*p_vid = vid;
	वापस err;
पूर्ण

अटल अंतरभूत bool
mlxsw_sp_port_is_छोड़ो_en(स्थिर काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	वापस mlxsw_sp_port->link.tx_छोड़ो || mlxsw_sp_port->link.rx_छोड़ो;
पूर्ण

अटल अंतरभूत काष्ठा mlxsw_sp_port *
mlxsw_sp_port_lagged_get(काष्ठा mlxsw_sp *mlxsw_sp, u16 lag_id, u8 port_index)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	u8 local_port;

	local_port = mlxsw_core_lag_mapping_get(mlxsw_sp->core,
						lag_id, port_index);
	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	वापस mlxsw_sp_port && mlxsw_sp_port->lagged ? mlxsw_sp_port : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mlxsw_sp_port_vlan *
mlxsw_sp_port_vlan_find_by_vid(स्थिर काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       u16 vid)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &mlxsw_sp_port->vlans_list,
			    list) अणु
		अगर (mlxsw_sp_port_vlan->vid == vid)
			वापस mlxsw_sp_port_vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

क्रमागत mlxsw_sp_flood_type अणु
	MLXSW_SP_FLOOD_TYPE_UC,
	MLXSW_SP_FLOOD_TYPE_BC,
	MLXSW_SP_FLOOD_TYPE_MC,
पूर्ण;

पूर्णांक mlxsw_sp_port_get_stats_raw(काष्ठा net_device *dev, पूर्णांक grp,
				पूर्णांक prio, अक्षर *ppcnt_pl);
पूर्णांक mlxsw_sp_port_admin_status_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   bool is_up);
पूर्णांक
mlxsw_sp_port_vlan_classअगरication_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      bool is_8021ad_tagged,
				      bool is_8021q_tagged);

/* spectrum_buffers.c */
काष्ठा mlxsw_sp_hdroom_prio अणु
	/* Number of port buffer associated with this priority. This is the
	 * actually configured value.
	 */
	u8 buf_idx;
	/* Value of buf_idx deduced from the DCB ETS configuration. */
	u8 ets_buf_idx;
	/* Value of buf_idx taken from the dcbnl_रखो_बफfer configuration. */
	u8 set_buf_idx;
	bool lossy;
पूर्ण;

काष्ठा mlxsw_sp_hdroom_buf अणु
	u32 thres_cells;
	u32 size_cells;
	/* Size requirement क्रमm dcbnl_रखो_बफfer. */
	u32 set_size_cells;
	bool lossy;
पूर्ण;

क्रमागत mlxsw_sp_hdroom_mode अणु
	MLXSW_SP_HDROOM_MODE_DCB,
	MLXSW_SP_HDROOM_MODE_TC,
पूर्ण;

#घोषणा MLXSW_SP_PB_COUNT 10

काष्ठा mlxsw_sp_hdroom अणु
	क्रमागत mlxsw_sp_hdroom_mode mode;

	काष्ठा अणु
		काष्ठा mlxsw_sp_hdroom_prio prio[IEEE_8021Q_MAX_PRIORITIES];
	पूर्ण prios;
	काष्ठा अणु
		काष्ठा mlxsw_sp_hdroom_buf buf[MLXSW_SP_PB_COUNT];
	पूर्ण bufs;
	काष्ठा अणु
		/* Size actually configured क्रम the पूर्णांकernal buffer. Equal to
		 * reserve when पूर्णांकernal buffer is enabled.
		 */
		u32 size_cells;
		/* Space reserved in the headroom क्रम the पूर्णांकernal buffer. Port
		 * buffers are not allowed to grow पूर्णांकo this space.
		 */
		u32 reserve_cells;
		bool enable;
	पूर्ण पूर्णांक_buf;
	पूर्णांक delay_bytes;
	पूर्णांक mtu;
पूर्ण;

पूर्णांक mlxsw_sp_buffers_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_buffers_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_port_buffers_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
व्योम mlxsw_sp_port_buffers_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
पूर्णांक mlxsw_sp_sb_pool_get(काष्ठा mlxsw_core *mlxsw_core,
			 अचिन्हित पूर्णांक sb_index, u16 pool_index,
			 काष्ठा devlink_sb_pool_info *pool_info);
पूर्णांक mlxsw_sp_sb_pool_set(काष्ठा mlxsw_core *mlxsw_core,
			 अचिन्हित पूर्णांक sb_index, u16 pool_index, u32 size,
			 क्रमागत devlink_sb_threshold_type threshold_type,
			 काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_sb_port_pool_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
			      अचिन्हित पूर्णांक sb_index, u16 pool_index,
			      u32 *p_threshold);
पूर्णांक mlxsw_sp_sb_port_pool_set(काष्ठा mlxsw_core_port *mlxsw_core_port,
			      अचिन्हित पूर्णांक sb_index, u16 pool_index,
			      u32 threshold, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_sb_tc_pool_bind_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
				 अचिन्हित पूर्णांक sb_index, u16 tc_index,
				 क्रमागत devlink_sb_pool_type pool_type,
				 u16 *p_pool_index, u32 *p_threshold);
पूर्णांक mlxsw_sp_sb_tc_pool_bind_set(काष्ठा mlxsw_core_port *mlxsw_core_port,
				 अचिन्हित पूर्णांक sb_index, u16 tc_index,
				 क्रमागत devlink_sb_pool_type pool_type,
				 u16 pool_index, u32 threshold,
				 काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_sb_occ_snapshot(काष्ठा mlxsw_core *mlxsw_core,
			     अचिन्हित पूर्णांक sb_index);
पूर्णांक mlxsw_sp_sb_occ_max_clear(काष्ठा mlxsw_core *mlxsw_core,
			      अचिन्हित पूर्णांक sb_index);
पूर्णांक mlxsw_sp_sb_occ_port_pool_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
				  अचिन्हित पूर्णांक sb_index, u16 pool_index,
				  u32 *p_cur, u32 *p_max);
पूर्णांक mlxsw_sp_sb_occ_tc_port_bind_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
				     अचिन्हित पूर्णांक sb_index, u16 tc_index,
				     क्रमागत devlink_sb_pool_type pool_type,
				     u32 *p_cur, u32 *p_max);
u32 mlxsw_sp_cells_bytes(स्थिर काष्ठा mlxsw_sp *mlxsw_sp, u32 cells);
u32 mlxsw_sp_bytes_cells(स्थिर काष्ठा mlxsw_sp *mlxsw_sp, u32 bytes);
व्योम mlxsw_sp_hdroom_prios_reset_buf_idx(काष्ठा mlxsw_sp_hdroom *hdroom);
व्योम mlxsw_sp_hdroom_bufs_reset_lossiness(काष्ठा mlxsw_sp_hdroom *hdroom);
व्योम mlxsw_sp_hdroom_bufs_reset_sizes(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      काष्ठा mlxsw_sp_hdroom *hdroom);
पूर्णांक mlxsw_sp_hdroom_configure(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      स्थिर काष्ठा mlxsw_sp_hdroom *hdroom);
काष्ठा mlxsw_sp_sample_params *
mlxsw_sp_sample_trigger_params_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
				      स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger);
पूर्णांक
mlxsw_sp_sample_trigger_params_set(काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger,
				   स्थिर काष्ठा mlxsw_sp_sample_params *params,
				   काष्ठा netlink_ext_ack *extack);
व्योम
mlxsw_sp_sample_trigger_params_unset(काष्ठा mlxsw_sp *mlxsw_sp,
				     स्थिर काष्ठा mlxsw_sp_sample_trigger *trigger);

बाह्य स्थिर काष्ठा mlxsw_sp_sb_vals mlxsw_sp1_sb_vals;
बाह्य स्थिर काष्ठा mlxsw_sp_sb_vals mlxsw_sp2_sb_vals;

बाह्य स्थिर काष्ठा mlxsw_sp_sb_ops mlxsw_sp1_sb_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_sb_ops mlxsw_sp2_sb_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_sb_ops mlxsw_sp3_sb_ops;

/* spectrum_चयनdev.c */
पूर्णांक mlxsw_sp_चयनdev_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_चयनdev_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_rअगर_fdb_op(काष्ठा mlxsw_sp *mlxsw_sp, स्थिर अक्षर *mac, u16 fid,
			bool adding);
व्योम
mlxsw_sp_port_vlan_bridge_leave(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan);
पूर्णांक mlxsw_sp_port_bridge_join(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा net_device *brport_dev,
			      काष्ठा net_device *br_dev,
			      काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_sp_port_bridge_leave(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				काष्ठा net_device *brport_dev,
				काष्ठा net_device *br_dev);
bool mlxsw_sp_bridge_device_is_offloaded(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					 स्थिर काष्ठा net_device *br_dev);
पूर्णांक mlxsw_sp_bridge_vxlan_join(काष्ठा mlxsw_sp *mlxsw_sp,
			       स्थिर काष्ठा net_device *br_dev,
			       स्थिर काष्ठा net_device *vxlan_dev, u16 vid,
			       काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_sp_bridge_vxlan_leave(काष्ठा mlxsw_sp *mlxsw_sp,
				 स्थिर काष्ठा net_device *vxlan_dev);
बाह्य काष्ठा notअगरier_block mlxsw_sp_चयनdev_notअगरier;

/* spectrum.c */
व्योम mlxsw_sp_rx_listener_no_mark_func(काष्ठा sk_buff *skb,
				       u8 local_port, व्योम *priv);
व्योम mlxsw_sp_ptp_receive(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा sk_buff *skb,
			  u8 local_port);
पूर्णांक mlxsw_sp_port_speed_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 *speed);
पूर्णांक mlxsw_sp_port_ets_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  क्रमागत mlxsw_reg_qeec_hr hr, u8 index, u8 next_index,
			  bool dwrr, u8 dwrr_weight);
पूर्णांक mlxsw_sp_port_prio_tc_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      u8 चयन_prio, u8 tclass);
पूर्णांक mlxsw_sp_port_ets_maxrate_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  क्रमागत mlxsw_reg_qeec_hr hr, u8 index,
				  u8 next_index, u32 maxrate, u8 burst_size);
क्रमागत mlxsw_reg_spms_state mlxsw_sp_stp_spms_state(u8 stp_state);
पूर्णांक mlxsw_sp_port_vid_stp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid,
			      u8 state);
पूर्णांक mlxsw_sp_port_vp_mode_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, bool enable);
पूर्णांक mlxsw_sp_port_vid_learning_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid,
				   bool learn_enable);
पूर्णांक mlxsw_sp_ethtype_to_sver_type(u16 ethtype, u8 *p_sver_type);
पूर्णांक mlxsw_sp_port_egress_ethtype_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     u16 ethtype);
पूर्णांक mlxsw_sp_port_pvid_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid,
			   u16 ethtype);
काष्ठा mlxsw_sp_port_vlan *
mlxsw_sp_port_vlan_create(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid);
व्योम mlxsw_sp_port_vlan_destroy(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan);
पूर्णांक mlxsw_sp_port_vlan_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid_begin,
			   u16 vid_end, bool is_member, bool untagged);
पूर्णांक mlxsw_sp_flow_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
			      अचिन्हित पूर्णांक counter_index, u64 *packets,
			      u64 *bytes);
पूर्णांक mlxsw_sp_flow_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
				अचिन्हित पूर्णांक *p_counter_index);
व्योम mlxsw_sp_flow_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
				अचिन्हित पूर्णांक counter_index);
bool mlxsw_sp_port_dev_check(स्थिर काष्ठा net_device *dev);
काष्ठा mlxsw_sp *mlxsw_sp_lower_get(काष्ठा net_device *dev);
काष्ठा mlxsw_sp_port *mlxsw_sp_port_dev_lower_find(काष्ठा net_device *dev);
काष्ठा mlxsw_sp_port *mlxsw_sp_port_lower_dev_hold(काष्ठा net_device *dev);
व्योम mlxsw_sp_port_dev_put(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
काष्ठा mlxsw_sp_port *mlxsw_sp_port_dev_lower_find_rcu(काष्ठा net_device *dev);

/* spectrum_dcb.c */
#अगर_घोषित CONFIG_MLXSW_SPECTRUM_DCB
पूर्णांक mlxsw_sp_port_dcb_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
व्योम mlxsw_sp_port_dcb_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
#अन्यथा
अटल अंतरभूत पूर्णांक mlxsw_sp_port_dcb_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम mlxsw_sp_port_dcb_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणुपूर्ण
#पूर्ण_अगर

/* spectrum_router.c */
क्रमागत mlxsw_sp_l3proto अणु
	MLXSW_SP_L3_PROTO_IPV4,
	MLXSW_SP_L3_PROTO_IPV6,
#घोषणा MLXSW_SP_L3_PROTO_MAX	(MLXSW_SP_L3_PROTO_IPV6 + 1)
पूर्ण;

जोड़ mlxsw_sp_l3addr अणु
	__be32 addr4;
	काष्ठा in6_addr addr6;
पूर्ण;

पूर्णांक mlxsw_sp_router_init(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_sp_router_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_netdevice_router_port_event(काष्ठा net_device *dev,
					 अचिन्हित दीर्घ event, व्योम *ptr);
व्योम mlxsw_sp_rअगर_macvlan_del(काष्ठा mlxsw_sp *mlxsw_sp,
			      स्थिर काष्ठा net_device *macvlan_dev);
पूर्णांक mlxsw_sp_inetaddr_valid_event(काष्ठा notअगरier_block *unused,
				  अचिन्हित दीर्घ event, व्योम *ptr);
पूर्णांक mlxsw_sp_inet6addr_valid_event(काष्ठा notअगरier_block *unused,
				   अचिन्हित दीर्घ event, व्योम *ptr);
पूर्णांक mlxsw_sp_netdevice_vrf_event(काष्ठा net_device *l3_dev, अचिन्हित दीर्घ event,
				 काष्ठा netdev_notअगरier_changeupper_info *info);
bool mlxsw_sp_netdev_is_ipip_ol(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
				स्थिर काष्ठा net_device *dev);
bool mlxsw_sp_netdev_is_ipip_ul(काष्ठा mlxsw_sp *mlxsw_sp,
				स्थिर काष्ठा net_device *dev);
पूर्णांक mlxsw_sp_netdevice_ipip_ol_event(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा net_device *l3_dev,
				     अचिन्हित दीर्घ event,
				     काष्ठा netdev_notअगरier_info *info);
पूर्णांक
mlxsw_sp_netdevice_ipip_ul_event(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा net_device *l3_dev,
				 अचिन्हित दीर्घ event,
				 काष्ठा netdev_notअगरier_info *info);
पूर्णांक
mlxsw_sp_port_vlan_router_join(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan,
			       काष्ठा net_device *l3_dev,
			       काष्ठा netlink_ext_ack *extack);
व्योम
mlxsw_sp_port_vlan_router_leave(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan);
व्योम mlxsw_sp_rअगर_destroy_by_dev(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा net_device *dev);
bool mlxsw_sp_rअगर_exists(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा net_device *dev);
u16 mlxsw_sp_rअगर_vid(काष्ठा mlxsw_sp *mlxsw_sp, स्थिर काष्ठा net_device *dev);
u8 mlxsw_sp_router_port(स्थिर काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_router_nve_promote_decap(काष्ठा mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
				      क्रमागत mlxsw_sp_l3proto ul_proto,
				      स्थिर जोड़ mlxsw_sp_l3addr *ul_sip,
				      u32 tunnel_index);
व्योम mlxsw_sp_router_nve_demote_decap(काष्ठा mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
				      क्रमागत mlxsw_sp_l3proto ul_proto,
				      स्थिर जोड़ mlxsw_sp_l3addr *ul_sip);
पूर्णांक mlxsw_sp_router_tb_id_vr_id(काष्ठा mlxsw_sp *mlxsw_sp, u32 tb_id,
				u16 *vr_id);
पूर्णांक mlxsw_sp_router_ul_rअगर_get(काष्ठा mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
			       u16 *ul_rअगर_index);
व्योम mlxsw_sp_router_ul_rअगर_put(काष्ठा mlxsw_sp *mlxsw_sp, u16 ul_rअगर_index);

/* spectrum_kvdl.c */
क्रमागत mlxsw_sp_kvdl_entry_type अणु
	MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
	MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
	MLXSW_SP_KVDL_ENTRY_TYPE_PBS,
	MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR,
	MLXSW_SP_KVDL_ENTRY_TYPE_TNUMT,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक
mlxsw_sp_kvdl_entry_size(क्रमागत mlxsw_sp_kvdl_entry_type type)
अणु
	चयन (type) अणु
	हाल MLXSW_SP_KVDL_ENTRY_TYPE_ADJ:
	हाल MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET:
	हाल MLXSW_SP_KVDL_ENTRY_TYPE_PBS:
	हाल MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR:
	हाल MLXSW_SP_KVDL_ENTRY_TYPE_TNUMT:
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

काष्ठा mlxsw_sp_kvdl_ops अणु
	माप_प्रकार priv_size;
	पूर्णांक (*init)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv);
	व्योम (*fini)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv);
	पूर्णांक (*alloc)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
		     क्रमागत mlxsw_sp_kvdl_entry_type type,
		     अचिन्हित पूर्णांक entry_count, u32 *p_entry_index);
	व्योम (*मुक्त)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
		     क्रमागत mlxsw_sp_kvdl_entry_type type,
		     अचिन्हित पूर्णांक entry_count, पूर्णांक entry_index);
	पूर्णांक (*alloc_size_query)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				क्रमागत mlxsw_sp_kvdl_entry_type type,
				अचिन्हित पूर्णांक entry_count,
				अचिन्हित पूर्णांक *p_alloc_count);
	पूर्णांक (*resources_रेजिस्टर)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv);
पूर्ण;

पूर्णांक mlxsw_sp_kvdl_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_kvdl_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_kvdl_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			क्रमागत mlxsw_sp_kvdl_entry_type type,
			अचिन्हित पूर्णांक entry_count, u32 *p_entry_index);
व्योम mlxsw_sp_kvdl_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			क्रमागत mlxsw_sp_kvdl_entry_type type,
			अचिन्हित पूर्णांक entry_count, पूर्णांक entry_index);
पूर्णांक mlxsw_sp_kvdl_alloc_count_query(काष्ठा mlxsw_sp *mlxsw_sp,
				    क्रमागत mlxsw_sp_kvdl_entry_type type,
				    अचिन्हित पूर्णांक entry_count,
				    अचिन्हित पूर्णांक *p_alloc_count);

/* spectrum1_kvdl.c */
बाह्य स्थिर काष्ठा mlxsw_sp_kvdl_ops mlxsw_sp1_kvdl_ops;
पूर्णांक mlxsw_sp1_kvdl_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core);

/* spectrum2_kvdl.c */
बाह्य स्थिर काष्ठा mlxsw_sp_kvdl_ops mlxsw_sp2_kvdl_ops;

काष्ठा mlxsw_sp_acl_rule_info अणु
	अचिन्हित पूर्णांक priority;
	काष्ठा mlxsw_afk_element_values values;
	काष्ठा mlxsw_afa_block *act_block;
	u8 action_created:1,
	   ingress_bind_blocker:1,
	   egress_bind_blocker:1,
	   counter_valid:1,
	   policer_index_valid:1;
	अचिन्हित पूर्णांक counter_index;
	u16 policer_index;
पूर्ण;

/* spectrum_flow.c */
काष्ठा mlxsw_sp_flow_block अणु
	काष्ठा list_head binding_list;
	काष्ठा अणु
		काष्ठा list_head list;
		अचिन्हित पूर्णांक min_prio;
		अचिन्हित पूर्णांक max_prio;
	पूर्ण mall;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset_zero;
	काष्ठा mlxsw_sp *mlxsw_sp;
	अचिन्हित पूर्णांक rule_count;
	अचिन्हित पूर्णांक disable_count;
	अचिन्हित पूर्णांक ingress_blocker_rule_count;
	अचिन्हित पूर्णांक egress_blocker_rule_count;
	अचिन्हित पूर्णांक ingress_binding_count;
	अचिन्हित पूर्णांक egress_binding_count;
	काष्ठा net *net;
पूर्ण;

काष्ठा mlxsw_sp_flow_block_binding अणु
	काष्ठा list_head list;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	bool ingress;
पूर्ण;

अटल अंतरभूत काष्ठा mlxsw_sp *
mlxsw_sp_flow_block_mlxsw_sp(काष्ठा mlxsw_sp_flow_block *block)
अणु
	वापस block->mlxsw_sp;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mlxsw_sp_flow_block_rule_count(स्थिर काष्ठा mlxsw_sp_flow_block *block)
अणु
	वापस block ? block->rule_count : 0;
पूर्ण

अटल अंतरभूत व्योम
mlxsw_sp_flow_block_disable_inc(काष्ठा mlxsw_sp_flow_block *block)
अणु
	अगर (block)
		block->disable_count++;
पूर्ण

अटल अंतरभूत व्योम
mlxsw_sp_flow_block_disable_dec(काष्ठा mlxsw_sp_flow_block *block)
अणु
	अगर (block)
		block->disable_count--;
पूर्ण

अटल अंतरभूत bool
mlxsw_sp_flow_block_disabled(स्थिर काष्ठा mlxsw_sp_flow_block *block)
अणु
	वापस block->disable_count;
पूर्ण

अटल अंतरभूत bool
mlxsw_sp_flow_block_is_egress_bound(स्थिर काष्ठा mlxsw_sp_flow_block *block)
अणु
	वापस block->egress_binding_count;
पूर्ण

अटल अंतरभूत bool
mlxsw_sp_flow_block_is_ingress_bound(स्थिर काष्ठा mlxsw_sp_flow_block *block)
अणु
	वापस block->ingress_binding_count;
पूर्ण

अटल अंतरभूत bool
mlxsw_sp_flow_block_is_mixed_bound(स्थिर काष्ठा mlxsw_sp_flow_block *block)
अणु
	वापस block->ingress_binding_count && block->egress_binding_count;
पूर्ण

काष्ठा mlxsw_sp_flow_block *mlxsw_sp_flow_block_create(काष्ठा mlxsw_sp *mlxsw_sp,
						       काष्ठा net *net);
व्योम mlxsw_sp_flow_block_destroy(काष्ठा mlxsw_sp_flow_block *block);
पूर्णांक mlxsw_sp_setup_tc_block_clsact(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा flow_block_offload *f,
				   bool ingress);

/* spectrum_acl.c */
काष्ठा mlxsw_sp_acl_ruleset;

क्रमागत mlxsw_sp_acl_profile अणु
	MLXSW_SP_ACL_PROखाता_FLOWER,
	MLXSW_SP_ACL_PROखाता_MR,
पूर्ण;

काष्ठा mlxsw_afk *mlxsw_sp_acl_afk(काष्ठा mlxsw_sp_acl *acl);

पूर्णांक mlxsw_sp_acl_ruleset_bind(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_flow_block *block,
			      काष्ठा mlxsw_sp_flow_block_binding *binding);
व्योम mlxsw_sp_acl_ruleset_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_flow_block *block,
				 काष्ठा mlxsw_sp_flow_block_binding *binding);
काष्ठा mlxsw_sp_acl_ruleset *
mlxsw_sp_acl_ruleset_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			    क्रमागत mlxsw_sp_acl_profile profile);
काष्ठा mlxsw_sp_acl_ruleset *
mlxsw_sp_acl_ruleset_get(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			 क्रमागत mlxsw_sp_acl_profile profile,
			 काष्ठा mlxsw_afk_element_usage *पंचांगplt_elusage);
व्योम mlxsw_sp_acl_ruleset_put(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_acl_ruleset *ruleset);
u16 mlxsw_sp_acl_ruleset_group_id(काष्ठा mlxsw_sp_acl_ruleset *ruleset);
व्योम mlxsw_sp_acl_ruleset_prio_get(काष्ठा mlxsw_sp_acl_ruleset *ruleset,
				   अचिन्हित पूर्णांक *p_min_prio,
				   अचिन्हित पूर्णांक *p_max_prio);

काष्ठा mlxsw_sp_acl_rule_info *
mlxsw_sp_acl_rulei_create(काष्ठा mlxsw_sp_acl *acl,
			  काष्ठा mlxsw_afa_block *afa_block);
व्योम mlxsw_sp_acl_rulei_destroy(काष्ठा mlxsw_sp_acl_rule_info *rulei);
पूर्णांक mlxsw_sp_acl_rulei_commit(काष्ठा mlxsw_sp_acl_rule_info *rulei);
व्योम mlxsw_sp_acl_rulei_priority(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				 अचिन्हित पूर्णांक priority);
व्योम mlxsw_sp_acl_rulei_keymask_u32(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    क्रमागत mlxsw_afk_element element,
				    u32 key_value, u32 mask_value);
व्योम mlxsw_sp_acl_rulei_keymask_buf(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    क्रमागत mlxsw_afk_element element,
				    स्थिर अक्षर *key_value,
				    स्थिर अक्षर *mask_value, अचिन्हित पूर्णांक len);
पूर्णांक mlxsw_sp_acl_rulei_act_जारी(काष्ठा mlxsw_sp_acl_rule_info *rulei);
पूर्णांक mlxsw_sp_acl_rulei_act_jump(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				u16 group_id);
पूर्णांक mlxsw_sp_acl_rulei_act_terminate(काष्ठा mlxsw_sp_acl_rule_info *rulei);
पूर्णांक mlxsw_sp_acl_rulei_act_drop(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				bool ingress,
				स्थिर काष्ठा flow_action_cookie *fa_cookie,
				काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_trap(काष्ठा mlxsw_sp_acl_rule_info *rulei);
पूर्णांक mlxsw_sp_acl_rulei_act_mirror(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  काष्ठा mlxsw_sp_flow_block *block,
				  काष्ठा net_device *out_dev,
				  काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_fwd(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_rule_info *rulei,
			       काष्ठा net_device *out_dev,
			       काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_vlan(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_rule_info *rulei,
				u32 action, u16 vid, u16 proto, u8 prio,
				काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_priority(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    u32 prio, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_mangle(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  क्रमागत flow_action_mangle_base htype,
				  u32 offset, u32 mask, u32 val,
				  काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_police(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  u32 index, u64 rate_bytes_ps,
				  u32 burst, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_count(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_rule_info *rulei,
				 काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_fid_set(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_acl_rule_info *rulei,
				   u16 fid, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_acl_rulei_act_sample(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  काष्ठा mlxsw_sp_flow_block *block,
				  काष्ठा psample_group *psample_group, u32 rate,
				  u32 trunc_size, bool truncate,
				  काष्ठा netlink_ext_ack *extack);

काष्ठा mlxsw_sp_acl_rule;

काष्ठा mlxsw_sp_acl_rule *
mlxsw_sp_acl_rule_create(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा mlxsw_sp_acl_ruleset *ruleset,
			 अचिन्हित दीर्घ cookie,
			 काष्ठा mlxsw_afa_block *afa_block,
			 काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_sp_acl_rule_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_rule *rule);
पूर्णांक mlxsw_sp_acl_rule_add(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_acl_rule *rule);
व्योम mlxsw_sp_acl_rule_del(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_acl_rule *rule);
पूर्णांक mlxsw_sp_acl_rule_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_rule *rule,
				     काष्ठा mlxsw_afa_block *afa_block);
काष्ठा mlxsw_sp_acl_rule *
mlxsw_sp_acl_rule_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा mlxsw_sp_acl_ruleset *ruleset,
			 अचिन्हित दीर्घ cookie);
काष्ठा mlxsw_sp_acl_rule_info *
mlxsw_sp_acl_rule_rulei(काष्ठा mlxsw_sp_acl_rule *rule);
पूर्णांक mlxsw_sp_acl_rule_get_stats(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_rule *rule,
				u64 *packets, u64 *bytes, u64 *drops,
				u64 *last_use,
				क्रमागत flow_action_hw_stats *used_hw_stats);

काष्ठा mlxsw_sp_fid *mlxsw_sp_acl_dummy_fid(काष्ठा mlxsw_sp *mlxsw_sp);

अटल अंतरभूत स्थिर काष्ठा flow_action_cookie *
mlxsw_sp_acl_act_cookie_lookup(काष्ठा mlxsw_sp *mlxsw_sp, u32 cookie_index)
अणु
	वापस mlxsw_afa_cookie_lookup(mlxsw_sp->afa, cookie_index);
पूर्ण

पूर्णांक mlxsw_sp_acl_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_acl_fini(काष्ठा mlxsw_sp *mlxsw_sp);
u32 mlxsw_sp_acl_region_rehash_पूर्णांकrvl_get(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_acl_region_rehash_पूर्णांकrvl_set(काष्ठा mlxsw_sp *mlxsw_sp, u32 val);

काष्ठा mlxsw_sp_acl_mangle_action;

काष्ठा mlxsw_sp_acl_rulei_ops अणु
	पूर्णांक (*act_mangle_field)(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा mlxsw_sp_acl_rule_info *rulei,
				काष्ठा mlxsw_sp_acl_mangle_action *mact, u32 val,
				काष्ठा netlink_ext_ack *extack);
पूर्ण;

बाह्य काष्ठा mlxsw_sp_acl_rulei_ops mlxsw_sp1_acl_rulei_ops;
बाह्य काष्ठा mlxsw_sp_acl_rulei_ops mlxsw_sp2_acl_rulei_ops;

/* spectrum_acl_tcam.c */
काष्ठा mlxsw_sp_acl_tcam;
काष्ठा mlxsw_sp_acl_tcam_region;

काष्ठा mlxsw_sp_acl_tcam_ops अणु
	क्रमागत mlxsw_reg_ptar_key_type key_type;
	माप_प्रकार priv_size;
	पूर्णांक (*init)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
		    काष्ठा mlxsw_sp_acl_tcam *tcam);
	व्योम (*fini)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv);
	माप_प्रकार region_priv_size;
	पूर्णांक (*region_init)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *region_priv,
			   व्योम *tcam_priv,
			   काष्ठा mlxsw_sp_acl_tcam_region *region,
			   व्योम *hपूर्णांकs_priv);
	व्योम (*region_fini)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *region_priv);
	पूर्णांक (*region_associate)(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_tcam_region *region);
	व्योम * (*region_rehash_hपूर्णांकs_get)(व्योम *region_priv);
	व्योम (*region_rehash_hपूर्णांकs_put)(व्योम *hपूर्णांकs_priv);
	माप_प्रकार chunk_priv_size;
	व्योम (*chunk_init)(व्योम *region_priv, व्योम *chunk_priv,
			   अचिन्हित पूर्णांक priority);
	व्योम (*chunk_fini)(व्योम *chunk_priv);
	माप_प्रकार entry_priv_size;
	पूर्णांक (*entry_add)(काष्ठा mlxsw_sp *mlxsw_sp,
			 व्योम *region_priv, व्योम *chunk_priv,
			 व्योम *entry_priv,
			 काष्ठा mlxsw_sp_acl_rule_info *rulei);
	व्योम (*entry_del)(काष्ठा mlxsw_sp *mlxsw_sp,
			  व्योम *region_priv, व्योम *chunk_priv,
			  व्योम *entry_priv);
	पूर्णांक (*entry_action_replace)(काष्ठा mlxsw_sp *mlxsw_sp,
				    व्योम *region_priv, व्योम *entry_priv,
				    काष्ठा mlxsw_sp_acl_rule_info *rulei);
	पूर्णांक (*entry_activity_get)(काष्ठा mlxsw_sp *mlxsw_sp,
				  व्योम *region_priv, व्योम *entry_priv,
				  bool *activity);
पूर्ण;

/* spectrum1_acl_tcam.c */
बाह्य स्थिर काष्ठा mlxsw_sp_acl_tcam_ops mlxsw_sp1_acl_tcam_ops;

/* spectrum2_acl_tcam.c */
बाह्य स्थिर काष्ठा mlxsw_sp_acl_tcam_ops mlxsw_sp2_acl_tcam_ops;

/* spectrum_acl_flex_actions.c */
बाह्य स्थिर काष्ठा mlxsw_afa_ops mlxsw_sp1_act_afa_ops;
बाह्य स्थिर काष्ठा mlxsw_afa_ops mlxsw_sp2_act_afa_ops;

/* spectrum_acl_flex_keys.c */
बाह्य स्थिर काष्ठा mlxsw_afk_ops mlxsw_sp1_afk_ops;
बाह्य स्थिर काष्ठा mlxsw_afk_ops mlxsw_sp2_afk_ops;

/* spectrum_matchall.c */
काष्ठा mlxsw_sp_mall_ops अणु
	पूर्णांक (*sample_add)(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा mlxsw_sp_mall_entry *mall_entry,
			  काष्ठा netlink_ext_ack *extack);
	व्योम (*sample_del)(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा mlxsw_sp_mall_entry *mall_entry);
पूर्ण;

बाह्य स्थिर काष्ठा mlxsw_sp_mall_ops mlxsw_sp1_mall_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_mall_ops mlxsw_sp2_mall_ops;

क्रमागत mlxsw_sp_mall_action_type अणु
	MLXSW_SP_MALL_ACTION_TYPE_MIRROR,
	MLXSW_SP_MALL_ACTION_TYPE_SAMPLE,
	MLXSW_SP_MALL_ACTION_TYPE_TRAP,
पूर्ण;

काष्ठा mlxsw_sp_mall_mirror_entry अणु
	स्थिर काष्ठा net_device *to_dev;
	पूर्णांक span_id;
पूर्ण;

काष्ठा mlxsw_sp_mall_trap_entry अणु
	पूर्णांक span_id;
पूर्ण;

काष्ठा mlxsw_sp_mall_sample_entry अणु
	काष्ठा mlxsw_sp_sample_params params;
	पूर्णांक span_id;	/* Relevant क्रम Spectrum-2 onwards. */
पूर्ण;

काष्ठा mlxsw_sp_mall_entry अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ cookie;
	अचिन्हित पूर्णांक priority;
	क्रमागत mlxsw_sp_mall_action_type type;
	bool ingress;
	जोड़ अणु
		काष्ठा mlxsw_sp_mall_mirror_entry mirror;
		काष्ठा mlxsw_sp_mall_trap_entry trap;
		काष्ठा mlxsw_sp_mall_sample_entry sample;
	पूर्ण;
	काष्ठा rcu_head rcu;
पूर्ण;

पूर्णांक mlxsw_sp_mall_replace(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_flow_block *block,
			  काष्ठा tc_cls_matchall_offload *f);
व्योम mlxsw_sp_mall_destroy(काष्ठा mlxsw_sp_flow_block *block,
			   काष्ठा tc_cls_matchall_offload *f);
पूर्णांक mlxsw_sp_mall_port_bind(काष्ठा mlxsw_sp_flow_block *block,
			    काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_sp_mall_port_unbind(काष्ठा mlxsw_sp_flow_block *block,
			       काष्ठा mlxsw_sp_port *mlxsw_sp_port);
पूर्णांक mlxsw_sp_mall_prio_get(काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			   अचिन्हित पूर्णांक *p_min_prio, अचिन्हित पूर्णांक *p_max_prio);

/* spectrum_flower.c */
पूर्णांक mlxsw_sp_flower_replace(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_flow_block *block,
			    काष्ठा flow_cls_offload *f);
व्योम mlxsw_sp_flower_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_flow_block *block,
			     काष्ठा flow_cls_offload *f);
पूर्णांक mlxsw_sp_flower_stats(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_flow_block *block,
			  काष्ठा flow_cls_offload *f);
पूर्णांक mlxsw_sp_flower_पंचांगplt_create(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_flow_block *block,
				 काष्ठा flow_cls_offload *f);
व्योम mlxsw_sp_flower_पंचांगplt_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_flow_block *block,
				   काष्ठा flow_cls_offload *f);
पूर्णांक mlxsw_sp_flower_prio_get(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_flow_block *block,
			     u32 chain_index, अचिन्हित पूर्णांक *p_min_prio,
			     अचिन्हित पूर्णांक *p_max_prio);

/* spectrum_qdisc.c */
पूर्णांक mlxsw_sp_tc_qdisc_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
व्योम mlxsw_sp_tc_qdisc_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
पूर्णांक mlxsw_sp_setup_tc_red(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा tc_red_qopt_offload *p);
पूर्णांक mlxsw_sp_setup_tc_prio(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा tc_prio_qopt_offload *p);
पूर्णांक mlxsw_sp_setup_tc_ets(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा tc_ets_qopt_offload *p);
पूर्णांक mlxsw_sp_setup_tc_tbf(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा tc_tbf_qopt_offload *p);
पूर्णांक mlxsw_sp_setup_tc_fअगरo(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा tc_fअगरo_qopt_offload *p);
पूर्णांक mlxsw_sp_setup_tc_block_qevent_early_drop(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					      काष्ठा flow_block_offload *f);

/* spectrum_fid.c */
bool mlxsw_sp_fid_is_dummy(काष्ठा mlxsw_sp *mlxsw_sp, u16 fid_index);
bool mlxsw_sp_fid_lag_vid_valid(स्थिर काष्ठा mlxsw_sp_fid *fid);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_lookup_by_index(काष्ठा mlxsw_sp *mlxsw_sp,
						  u16 fid_index);
पूर्णांक mlxsw_sp_fid_nve_अगरindex(स्थिर काष्ठा mlxsw_sp_fid *fid, पूर्णांक *nve_अगरindex);
पूर्णांक mlxsw_sp_fid_nve_type(स्थिर काष्ठा mlxsw_sp_fid *fid,
			  क्रमागत mlxsw_sp_nve_type *p_type);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_lookup_by_vni(काष्ठा mlxsw_sp *mlxsw_sp,
						__be32 vni);
पूर्णांक mlxsw_sp_fid_vni(स्थिर काष्ठा mlxsw_sp_fid *fid, __be32 *vni);
पूर्णांक mlxsw_sp_fid_nve_flood_index_set(काष्ठा mlxsw_sp_fid *fid,
				     u32 nve_flood_index);
व्योम mlxsw_sp_fid_nve_flood_index_clear(काष्ठा mlxsw_sp_fid *fid);
bool mlxsw_sp_fid_nve_flood_index_is_set(स्थिर काष्ठा mlxsw_sp_fid *fid);
पूर्णांक mlxsw_sp_fid_vni_set(काष्ठा mlxsw_sp_fid *fid, क्रमागत mlxsw_sp_nve_type type,
			 __be32 vni, पूर्णांक nve_अगरindex);
व्योम mlxsw_sp_fid_vni_clear(काष्ठा mlxsw_sp_fid *fid);
bool mlxsw_sp_fid_vni_is_set(स्थिर काष्ठा mlxsw_sp_fid *fid);
व्योम mlxsw_sp_fid_fdb_clear_offload(स्थिर काष्ठा mlxsw_sp_fid *fid,
				    स्थिर काष्ठा net_device *nve_dev);
पूर्णांक mlxsw_sp_fid_flood_set(काष्ठा mlxsw_sp_fid *fid,
			   क्रमागत mlxsw_sp_flood_type packet_type, u8 local_port,
			   bool member);
पूर्णांक mlxsw_sp_fid_port_vid_map(काष्ठा mlxsw_sp_fid *fid,
			      काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid);
व्योम mlxsw_sp_fid_port_vid_unmap(काष्ठा mlxsw_sp_fid *fid,
				 काष्ठा mlxsw_sp_port *mlxsw_sp_port, u16 vid);
u16 mlxsw_sp_fid_index(स्थिर काष्ठा mlxsw_sp_fid *fid);
क्रमागत mlxsw_sp_fid_type mlxsw_sp_fid_type(स्थिर काष्ठा mlxsw_sp_fid *fid);
व्योम mlxsw_sp_fid_rअगर_set(काष्ठा mlxsw_sp_fid *fid, काष्ठा mlxsw_sp_rअगर *rअगर);
काष्ठा mlxsw_sp_rअगर *mlxsw_sp_fid_rअगर(स्थिर काष्ठा mlxsw_sp_fid *fid);
क्रमागत mlxsw_sp_rअगर_type
mlxsw_sp_fid_type_rअगर_type(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_fid_type type);
u16 mlxsw_sp_fid_8021q_vid(स्थिर काष्ठा mlxsw_sp_fid *fid);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021q_get(काष्ठा mlxsw_sp *mlxsw_sp, u16 vid);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021d_get(काष्ठा mlxsw_sp *mlxsw_sp,
					    पूर्णांक br_अगरindex);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021q_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
					       u16 vid);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_8021d_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
					       पूर्णांक br_अगरindex);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_rfid_get(काष्ठा mlxsw_sp *mlxsw_sp,
					   u16 rअगर_index);
काष्ठा mlxsw_sp_fid *mlxsw_sp_fid_dummy_get(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_fid_put(काष्ठा mlxsw_sp_fid *fid);
पूर्णांक mlxsw_sp_port_fids_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
व्योम mlxsw_sp_port_fids_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
पूर्णांक mlxsw_sp_fids_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_fids_fini(काष्ठा mlxsw_sp *mlxsw_sp);

/* spectrum_mr.c */
क्रमागत mlxsw_sp_mr_route_prio अणु
	MLXSW_SP_MR_ROUTE_PRIO_SG,
	MLXSW_SP_MR_ROUTE_PRIO_STARG,
	MLXSW_SP_MR_ROUTE_PRIO_CATCHALL,
	__MLXSW_SP_MR_ROUTE_PRIO_MAX
पूर्ण;

#घोषणा MLXSW_SP_MR_ROUTE_PRIO_MAX (__MLXSW_SP_MR_ROUTE_PRIO_MAX - 1)

काष्ठा mlxsw_sp_mr_route_key;

काष्ठा mlxsw_sp_mr_tcam_ops अणु
	माप_प्रकार priv_size;
	पूर्णांक (*init)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv);
	व्योम (*fini)(व्योम *priv);
	माप_प्रकार route_priv_size;
	पूर्णांक (*route_create)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
			    व्योम *route_priv,
			    काष्ठा mlxsw_sp_mr_route_key *key,
			    काष्ठा mlxsw_afa_block *afa_block,
			    क्रमागत mlxsw_sp_mr_route_prio prio);
	व्योम (*route_destroy)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
			      व्योम *route_priv,
			      काष्ठा mlxsw_sp_mr_route_key *key);
	पूर्णांक (*route_update)(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
			    काष्ठा mlxsw_sp_mr_route_key *key,
			    काष्ठा mlxsw_afa_block *afa_block);
पूर्ण;

/* spectrum1_mr_tcam.c */
बाह्य स्थिर काष्ठा mlxsw_sp_mr_tcam_ops mlxsw_sp1_mr_tcam_ops;

/* spectrum2_mr_tcam.c */
बाह्य स्थिर काष्ठा mlxsw_sp_mr_tcam_ops mlxsw_sp2_mr_tcam_ops;

/* spectrum_nve.c */
काष्ठा mlxsw_sp_nve_params अणु
	क्रमागत mlxsw_sp_nve_type type;
	__be32 vni;
	स्थिर काष्ठा net_device *dev;
	u16 ethertype;
पूर्ण;

बाह्य स्थिर काष्ठा mlxsw_sp_nve_ops *mlxsw_sp1_nve_ops_arr[];
बाह्य स्थिर काष्ठा mlxsw_sp_nve_ops *mlxsw_sp2_nve_ops_arr[];

पूर्णांक mlxsw_sp_nve_learned_ip_resolve(काष्ठा mlxsw_sp *mlxsw_sp, u32 uip,
				    क्रमागत mlxsw_sp_l3proto proto,
				    जोड़ mlxsw_sp_l3addr *addr);
पूर्णांक mlxsw_sp_nve_flood_ip_add(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_fid *fid,
			      क्रमागत mlxsw_sp_l3proto proto,
			      जोड़ mlxsw_sp_l3addr *addr);
व्योम mlxsw_sp_nve_flood_ip_del(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_fid *fid,
			       क्रमागत mlxsw_sp_l3proto proto,
			       जोड़ mlxsw_sp_l3addr *addr);
पूर्णांक mlxsw_sp_nve_fid_enable(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा mlxsw_sp_fid *fid,
			    काष्ठा mlxsw_sp_nve_params *params,
			    काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_sp_nve_fid_disable(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_fid *fid);
पूर्णांक mlxsw_sp_port_nve_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
व्योम mlxsw_sp_port_nve_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
पूर्णांक mlxsw_sp_nve_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_nve_fini(काष्ठा mlxsw_sp *mlxsw_sp);

/* spectrum_nve_vxlan.c */
पूर्णांक mlxsw_sp_nve_inc_parsing_depth_get(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_nve_inc_parsing_depth_put(काष्ठा mlxsw_sp *mlxsw_sp);

/* spectrum_trap.c */
पूर्णांक mlxsw_sp_devlink_traps_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_devlink_traps_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_trap_init(काष्ठा mlxsw_core *mlxsw_core,
		       स्थिर काष्ठा devlink_trap *trap, व्योम *trap_ctx);
व्योम mlxsw_sp_trap_fini(काष्ठा mlxsw_core *mlxsw_core,
			स्थिर काष्ठा devlink_trap *trap, व्योम *trap_ctx);
पूर्णांक mlxsw_sp_trap_action_set(काष्ठा mlxsw_core *mlxsw_core,
			     स्थिर काष्ठा devlink_trap *trap,
			     क्रमागत devlink_trap_action action,
			     काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_sp_trap_group_init(काष्ठा mlxsw_core *mlxsw_core,
			     स्थिर काष्ठा devlink_trap_group *group);
पूर्णांक mlxsw_sp_trap_group_set(काष्ठा mlxsw_core *mlxsw_core,
			    स्थिर काष्ठा devlink_trap_group *group,
			    स्थिर काष्ठा devlink_trap_policer *policer,
			    काष्ठा netlink_ext_ack *extack);
पूर्णांक
mlxsw_sp_trap_policer_init(काष्ठा mlxsw_core *mlxsw_core,
			   स्थिर काष्ठा devlink_trap_policer *policer);
व्योम mlxsw_sp_trap_policer_fini(काष्ठा mlxsw_core *mlxsw_core,
				स्थिर काष्ठा devlink_trap_policer *policer);
पूर्णांक
mlxsw_sp_trap_policer_set(काष्ठा mlxsw_core *mlxsw_core,
			  स्थिर काष्ठा devlink_trap_policer *policer,
			  u64 rate, u64 burst, काष्ठा netlink_ext_ack *extack);
पूर्णांक
mlxsw_sp_trap_policer_counter_get(काष्ठा mlxsw_core *mlxsw_core,
				  स्थिर काष्ठा devlink_trap_policer *policer,
				  u64 *p_drops);
पूर्णांक mlxsw_sp_trap_group_policer_hw_id_get(काष्ठा mlxsw_sp *mlxsw_sp, u16 id,
					  bool *p_enabled, u16 *p_hw_id);

अटल अंतरभूत काष्ठा net *mlxsw_sp_net(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस mlxsw_core_net(mlxsw_sp->core);
पूर्ण

/* spectrum_ethtool.c */
बाह्य स्थिर काष्ठा ethtool_ops mlxsw_sp_port_ethtool_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_port_type_speed_ops mlxsw_sp1_port_type_speed_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_port_type_speed_ops mlxsw_sp2_port_type_speed_ops;

/* spectrum_policer.c */
बाह्य स्थिर काष्ठा mlxsw_sp_policer_core_ops mlxsw_sp1_policer_core_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_policer_core_ops mlxsw_sp2_policer_core_ops;

क्रमागत mlxsw_sp_policer_type अणु
	MLXSW_SP_POLICER_TYPE_SINGLE_RATE,

	__MLXSW_SP_POLICER_TYPE_MAX,
	MLXSW_SP_POLICER_TYPE_MAX = __MLXSW_SP_POLICER_TYPE_MAX - 1,
पूर्ण;

काष्ठा mlxsw_sp_policer_params अणु
	u64 rate;
	u64 burst;
	bool bytes;
पूर्ण;

पूर्णांक mlxsw_sp_policer_add(काष्ठा mlxsw_sp *mlxsw_sp,
			 क्रमागत mlxsw_sp_policer_type type,
			 स्थिर काष्ठा mlxsw_sp_policer_params *params,
			 काष्ठा netlink_ext_ack *extack, u16 *p_policer_index);
व्योम mlxsw_sp_policer_del(काष्ठा mlxsw_sp *mlxsw_sp,
			  क्रमागत mlxsw_sp_policer_type type,
			  u16 policer_index);
पूर्णांक mlxsw_sp_policer_drops_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
				       क्रमागत mlxsw_sp_policer_type type,
				       u16 policer_index, u64 *p_drops);
पूर्णांक mlxsw_sp_policers_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_policers_fini(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_policer_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core);

#पूर्ण_अगर
