<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies, Ltd.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __MLX5_ESWITCH_H__
#घोषणा __MLX5_ESWITCH_H__

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/atomic.h>
#समावेश <linux/xarray.h>
#समावेश <net/devlink.h>
#समावेश <linux/mlx5/device.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/fs.h>
#समावेश "lib/mpfs.h"
#समावेश "lib/fs_chains.h"
#समावेश "sf/sf.h"
#समावेश "en/tc_ct.h"
#समावेश "esw/sample.h"

क्रमागत mlx5_mapped_obj_type अणु
	MLX5_MAPPED_OBJ_CHAIN,
	MLX5_MAPPED_OBJ_SAMPLE,
पूर्ण;

काष्ठा mlx5_mapped_obj अणु
	क्रमागत mlx5_mapped_obj_type type;
	जोड़ अणु
		u32 chain;
		काष्ठा अणु
			u32 group_id;
			u32 rate;
			u32 trunc_size;
		पूर्ण sample;
	पूर्ण;
पूर्ण;

#अगर_घोषित CONFIG_MLX5_ESWITCH

#घोषणा ESW_OFFLOADS_DEFAULT_NUM_GROUPS 15

#घोषणा MLX5_MAX_UC_PER_VPORT(dev) \
	(1 << MLX5_CAP_GEN(dev, log_max_current_uc_list))

#घोषणा MLX5_MAX_MC_PER_VPORT(dev) \
	(1 << MLX5_CAP_GEN(dev, log_max_current_mc_list))

#घोषणा MLX5_MIN_BW_SHARE 1

#घोषणा MLX5_RATE_TO_BW_SHARE(rate, भागider, limit) \
	min_t(u32, max_t(u32, (rate) / (भागider), MLX5_MIN_BW_SHARE), limit)

#घोषणा mlx5_esw_has_fwd_fdb(dev) \
	MLX5_CAP_ESW_FLOWTABLE(dev, fdb_multi_path_to_table)

#घोषणा esw_chains(esw) \
	((esw)->fdb_table.offloads.esw_chains_priv)

काष्ठा vport_ingress अणु
	काष्ठा mlx5_flow_table *acl;
	काष्ठा mlx5_flow_handle *allow_rule;
	काष्ठा अणु
		काष्ठा mlx5_flow_group *allow_spoofchk_only_grp;
		काष्ठा mlx5_flow_group *allow_untagged_spoofchk_grp;
		काष्ठा mlx5_flow_group *allow_untagged_only_grp;
		काष्ठा mlx5_flow_group *drop_grp;
		काष्ठा mlx5_flow_handle *drop_rule;
		काष्ठा mlx5_fc *drop_counter;
	पूर्ण legacy;
	काष्ठा अणु
		/* Optional group to add an FTE to करो पूर्णांकernal priority
		 * tagging on ingress packets.
		 */
		काष्ठा mlx5_flow_group *metadata_prio_tag_grp;
		/* Group to add शेष match-all FTE entry to tag ingress
		 * packet with metadata.
		 */
		काष्ठा mlx5_flow_group *metadata_allmatch_grp;
		काष्ठा mlx5_modअगरy_hdr *modअगरy_metadata;
		काष्ठा mlx5_flow_handle *modअगरy_metadata_rule;
	पूर्ण offloads;
पूर्ण;

काष्ठा vport_egress अणु
	काष्ठा mlx5_flow_table *acl;
	काष्ठा mlx5_flow_handle  *allowed_vlan;
	काष्ठा mlx5_flow_group *vlan_grp;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा mlx5_flow_group *drop_grp;
			काष्ठा mlx5_flow_handle *drop_rule;
			काष्ठा mlx5_fc *drop_counter;
		पूर्ण legacy;
		काष्ठा अणु
			काष्ठा mlx5_flow_group *fwd_grp;
			काष्ठा mlx5_flow_handle *fwd_rule;
		पूर्ण offloads;
	पूर्ण;
पूर्ण;

काष्ठा mlx5_vport_drop_stats अणु
	u64 rx_dropped;
	u64 tx_dropped;
पूर्ण;

काष्ठा mlx5_vport_info अणु
	u8                      mac[ETH_ALEN];
	u16                     vlan;
	u64                     node_guid;
	पूर्णांक                     link_state;
	u8                      qos;
	u8                      spoofchk: 1;
	u8                      trusted: 1;
पूर्ण;

/* Vport context events */
क्रमागत mlx5_eचयन_vport_event अणु
	MLX5_VPORT_UC_ADDR_CHANGE = BIT(0),
	MLX5_VPORT_MC_ADDR_CHANGE = BIT(1),
	MLX5_VPORT_PROMISC_CHANGE = BIT(3),
पूर्ण;

काष्ठा mlx5_vport अणु
	काष्ठा mlx5_core_dev    *dev;
	काष्ठा hlist_head       uc_list[MLX5_L2_ADDR_HASH_SIZE];
	काष्ठा hlist_head       mc_list[MLX5_L2_ADDR_HASH_SIZE];
	काष्ठा mlx5_flow_handle *promisc_rule;
	काष्ठा mlx5_flow_handle *allmulti_rule;
	काष्ठा work_काष्ठा      vport_change_handler;

	काष्ठा vport_ingress    ingress;
	काष्ठा vport_egress     egress;
	u32                     शेष_metadata;
	u32                     metadata;

	काष्ठा mlx5_vport_info  info;

	काष्ठा अणु
		bool            enabled;
		u32             esw_tsar_ix;
		u32             bw_share;
		u32 min_rate;
		u32 max_rate;
	पूर्ण qos;

	u16 vport;
	bool                    enabled;
	क्रमागत mlx5_eचयन_vport_event enabled_events;
	पूर्णांक index;
	काष्ठा devlink_port *dl_port;
पूर्ण;

काष्ठा mlx5_esw_indir_table;

काष्ठा mlx5_eचयन_fdb अणु
	जोड़ अणु
		काष्ठा legacy_fdb अणु
			काष्ठा mlx5_flow_table *fdb;
			काष्ठा mlx5_flow_group *addr_grp;
			काष्ठा mlx5_flow_group *allmulti_grp;
			काष्ठा mlx5_flow_group *promisc_grp;
			काष्ठा mlx5_flow_table *vepa_fdb;
			काष्ठा mlx5_flow_handle *vepa_uplink_rule;
			काष्ठा mlx5_flow_handle *vepa_star_rule;
		पूर्ण legacy;

		काष्ठा offloads_fdb अणु
			काष्ठा mlx5_flow_namespace *ns;
			काष्ठा mlx5_flow_table *slow_fdb;
			काष्ठा mlx5_flow_group *send_to_vport_grp;
			काष्ठा mlx5_flow_group *send_to_vport_meta_grp;
			काष्ठा mlx5_flow_group *peer_miss_grp;
			काष्ठा mlx5_flow_handle **peer_miss_rules;
			काष्ठा mlx5_flow_group *miss_grp;
			काष्ठा mlx5_flow_handle **send_to_vport_meta_rules;
			काष्ठा mlx5_flow_handle *miss_rule_uni;
			काष्ठा mlx5_flow_handle *miss_rule_multi;
			पूर्णांक vlan_push_pop_refcount;

			काष्ठा mlx5_fs_chains *esw_chains_priv;
			काष्ठा अणु
				DECLARE_HASHTABLE(table, 8);
				/* Protects vports.table */
				काष्ठा mutex lock;
			पूर्ण vports;

			काष्ठा mlx5_esw_indir_table *indir;

		पूर्ण offloads;
	पूर्ण;
	u32 flags;
पूर्ण;

काष्ठा mlx5_esw_offload अणु
	काष्ठा mlx5_flow_table *ft_offloads_restore;
	काष्ठा mlx5_flow_group *restore_group;
	काष्ठा mlx5_modअगरy_hdr *restore_copy_hdr_id;
	काष्ठा mapping_ctx *reg_c0_obj_pool;

	काष्ठा mlx5_flow_table *ft_offloads;
	काष्ठा mlx5_flow_group *vport_rx_group;
	काष्ठा xarray vport_reps;
	काष्ठा list_head peer_flows;
	काष्ठा mutex peer_mutex;
	काष्ठा mutex encap_tbl_lock; /* protects encap_tbl */
	DECLARE_HASHTABLE(encap_tbl, 8);
	काष्ठा mutex decap_tbl_lock; /* protects decap_tbl */
	DECLARE_HASHTABLE(decap_tbl, 8);
	काष्ठा mod_hdr_tbl mod_hdr;
	DECLARE_HASHTABLE(termtbl_tbl, 8);
	काष्ठा mutex termtbl_mutex; /* protects termtbl hash */
	काष्ठा xarray vhca_map;
	स्थिर काष्ठा mlx5_eचयन_rep_ops *rep_ops[NUM_REP_TYPES];
	u8 अंतरभूत_mode;
	atomic64_t num_flows;
	क्रमागत devlink_eचयन_encap_mode encap;
	काष्ठा ida vport_metadata_ida;
	अचिन्हित पूर्णांक host_number; /* ECPF supports one बाह्यal host */
पूर्ण;

/* E-Switch MC FDB table hash node */
काष्ठा esw_mc_addr अणु /* SRIOV only */
	काष्ठा l2addr_node     node;
	काष्ठा mlx5_flow_handle *uplink_rule; /* Forward to uplink rule */
	u32                    refcnt;
पूर्ण;

काष्ठा mlx5_host_work अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा mlx5_eचयन	*esw;
पूर्ण;

काष्ठा mlx5_esw_functions अणु
	काष्ठा mlx5_nb		nb;
	u16			num_vfs;
पूर्ण;

क्रमागत अणु
	MLX5_ESWITCH_VPORT_MATCH_METADATA = BIT(0),
	MLX5_ESWITCH_REG_C1_LOOPBACK_ENABLED = BIT(1),
पूर्ण;

काष्ठा mlx5_eचयन अणु
	काष्ठा mlx5_core_dev    *dev;
	काष्ठा mlx5_nb          nb;
	काष्ठा mlx5_eचयन_fdb fdb_table;
	/* legacy data काष्ठाures */
	काष्ठा hlist_head       mc_table[MLX5_L2_ADDR_HASH_SIZE];
	काष्ठा esw_mc_addr mc_promisc;
	/* end of legacy */
	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा xarray vports;
	u32 flags;
	पूर्णांक                     total_vports;
	पूर्णांक                     enabled_vports;
	/* Synchronize between vport change events
	 * and async SRIOV admin state changes
	 */
	काष्ठा mutex            state_lock;

	/* Protects eचयन mode change that occurs via one or more
	 * user commands, i.e. sriov state change, devlink commands.
	 */
	काष्ठा rw_semaphore mode_lock;
	atomic64_t user_count;

	काष्ठा अणु
		bool            enabled;
		u32             root_tsar_id;
	पूर्ण qos;

	काष्ठा mlx5_esw_offload offloads;
	पूर्णांक                     mode;
	u16                     manager_vport;
	u16                     first_host_vport;
	काष्ठा mlx5_esw_functions esw_funcs;
	काष्ठा अणु
		u32             large_group_num;
	पूर्ण  params;
	काष्ठा blocking_notअगरier_head n_head;
पूर्ण;

व्योम esw_offloads_disable(काष्ठा mlx5_eचयन *esw);
पूर्णांक esw_offloads_enable(काष्ठा mlx5_eचयन *esw);
व्योम esw_offloads_cleanup_reps(काष्ठा mlx5_eचयन *esw);
पूर्णांक esw_offloads_init_reps(काष्ठा mlx5_eचयन *esw);

bool mlx5_esw_vport_match_metadata_supported(स्थिर काष्ठा mlx5_eचयन *esw);
पूर्णांक mlx5_esw_offloads_vport_metadata_set(काष्ठा mlx5_eचयन *esw, bool enable);
u32 mlx5_esw_match_metadata_alloc(काष्ठा mlx5_eचयन *esw);
व्योम mlx5_esw_match_metadata_मुक्त(काष्ठा mlx5_eचयन *esw, u32 metadata);

पूर्णांक mlx5_esw_modअगरy_vport_rate(काष्ठा mlx5_eचयन *esw, u16 vport_num,
			       u32 rate_mbps);

/* E-Switch API */
पूर्णांक mlx5_eचयन_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_eचयन_cleanup(काष्ठा mlx5_eचयन *esw);

#घोषणा MLX5_ESWITCH_IGNORE_NUM_VFS (-1)
पूर्णांक mlx5_eचयन_enable_locked(काष्ठा mlx5_eचयन *esw, पूर्णांक mode, पूर्णांक num_vfs);
पूर्णांक mlx5_eचयन_enable(काष्ठा mlx5_eचयन *esw, पूर्णांक num_vfs);
व्योम mlx5_eचयन_disable_locked(काष्ठा mlx5_eचयन *esw, bool clear_vf);
व्योम mlx5_eचयन_disable(काष्ठा mlx5_eचयन *esw, bool clear_vf);
पूर्णांक mlx5_eचयन_set_vport_mac(काष्ठा mlx5_eचयन *esw,
			       u16 vport, स्थिर u8 *mac);
पूर्णांक mlx5_eचयन_set_vport_state(काष्ठा mlx5_eचयन *esw,
				 u16 vport, पूर्णांक link_state);
पूर्णांक mlx5_eचयन_set_vport_vlan(काष्ठा mlx5_eचयन *esw,
				u16 vport, u16 vlan, u8 qos);
पूर्णांक mlx5_eचयन_set_vport_spoofchk(काष्ठा mlx5_eचयन *esw,
				    u16 vport, bool spoofchk);
पूर्णांक mlx5_eचयन_set_vport_trust(काष्ठा mlx5_eचयन *esw,
				 u16 vport_num, bool setting);
पूर्णांक mlx5_eचयन_set_vport_rate(काष्ठा mlx5_eचयन *esw, u16 vport,
				u32 max_rate, u32 min_rate);
पूर्णांक mlx5_eचयन_set_vepa(काष्ठा mlx5_eचयन *esw, u8 setting);
पूर्णांक mlx5_eचयन_get_vepa(काष्ठा mlx5_eचयन *esw, u8 *setting);
पूर्णांक mlx5_eचयन_get_vport_config(काष्ठा mlx5_eचयन *esw,
				  u16 vport, काष्ठा अगरla_vf_info *ivi);
पूर्णांक mlx5_eचयन_get_vport_stats(काष्ठा mlx5_eचयन *esw,
				 u16 vport,
				 काष्ठा अगरla_vf_stats *vf_stats);
व्योम mlx5_eचयन_del_send_to_vport_rule(काष्ठा mlx5_flow_handle *rule);

पूर्णांक mlx5_eचयन_modअगरy_esw_vport_context(काष्ठा mlx5_core_dev *dev, u16 vport,
					  bool other_vport, व्योम *in);

काष्ठा mlx5_flow_spec;
काष्ठा mlx5_esw_flow_attr;
काष्ठा mlx5_termtbl_handle;

bool
mlx5_eचयन_termtbl_required(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_flow_attr *attr,
			      काष्ठा mlx5_flow_act *flow_act,
			      काष्ठा mlx5_flow_spec *spec);

काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_termtbl_rule(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_flow_table *ft,
			      काष्ठा mlx5_flow_spec *spec,
			      काष्ठा mlx5_esw_flow_attr *attr,
			      काष्ठा mlx5_flow_act *flow_act,
			      काष्ठा mlx5_flow_destination *dest,
			      पूर्णांक num_dest);

व्योम
mlx5_eचयन_termtbl_put(काष्ठा mlx5_eचयन *esw,
			 काष्ठा mlx5_termtbl_handle *tt);

व्योम
mlx5_eचयन_clear_rule_source_port(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_spec *spec);

काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_offloaded_rule(काष्ठा mlx5_eचयन *esw,
				काष्ठा mlx5_flow_spec *spec,
				काष्ठा mlx5_flow_attr *attr);
काष्ठा mlx5_flow_handle *
mlx5_eचयन_add_fwd_rule(काष्ठा mlx5_eचयन *esw,
			  काष्ठा mlx5_flow_spec *spec,
			  काष्ठा mlx5_flow_attr *attr);
व्योम
mlx5_eचयन_del_offloaded_rule(काष्ठा mlx5_eचयन *esw,
				काष्ठा mlx5_flow_handle *rule,
				काष्ठा mlx5_flow_attr *attr);
व्योम
mlx5_eचयन_del_fwd_rule(काष्ठा mlx5_eचयन *esw,
			  काष्ठा mlx5_flow_handle *rule,
			  काष्ठा mlx5_flow_attr *attr);

काष्ठा mlx5_flow_handle *
mlx5_eचयन_create_vport_rx_rule(काष्ठा mlx5_eचयन *esw, u16 vport,
				  काष्ठा mlx5_flow_destination *dest);

क्रमागत अणु
	SET_VLAN_STRIP	= BIT(0),
	SET_VLAN_INSERT	= BIT(1)
पूर्ण;

क्रमागत mlx5_flow_match_level अणु
	MLX5_MATCH_NONE	= MLX5_INLINE_MODE_NONE,
	MLX5_MATCH_L2	= MLX5_INLINE_MODE_L2,
	MLX5_MATCH_L3	= MLX5_INLINE_MODE_IP,
	MLX5_MATCH_L4	= MLX5_INLINE_MODE_TCP_UDP,
पूर्ण;

/* current maximum क्रम flow based vport multicasting */
#घोषणा MLX5_MAX_FLOW_FWD_VPORTS 2

क्रमागत अणु
	MLX5_ESW_DEST_ENCAP         = BIT(0),
	MLX5_ESW_DEST_ENCAP_VALID   = BIT(1),
	MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE  = BIT(2),
पूर्ण;

क्रमागत अणु
	MLX5_ESW_ATTR_FLAG_VLAN_HANDLED  = BIT(0),
	MLX5_ESW_ATTR_FLAG_SLOW_PATH     = BIT(1),
	MLX5_ESW_ATTR_FLAG_NO_IN_PORT    = BIT(2),
	MLX5_ESW_ATTR_FLAG_SRC_REWRITE   = BIT(3),
	MLX5_ESW_ATTR_FLAG_SAMPLE        = BIT(4),
पूर्ण;

काष्ठा mlx5_esw_flow_attr अणु
	काष्ठा mlx5_eचयन_rep *in_rep;
	काष्ठा mlx5_core_dev	*in_mdev;
	काष्ठा mlx5_core_dev    *counter_dev;

	पूर्णांक split_count;
	पूर्णांक out_count;

	__be16	vlan_proto[MLX5_FS_VLAN_DEPTH];
	u16	vlan_vid[MLX5_FS_VLAN_DEPTH];
	u8	vlan_prio[MLX5_FS_VLAN_DEPTH];
	u8	total_vlan;
	काष्ठा अणु
		u32 flags;
		काष्ठा mlx5_eचयन_rep *rep;
		काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat;
		काष्ठा mlx5_core_dev *mdev;
		काष्ठा mlx5_termtbl_handle *termtbl;
		पूर्णांक src_port_reग_लिखो_act_id;
	पूर्ण dests[MLX5_MAX_FLOW_FWD_VPORTS];
	काष्ठा mlx5_rx_tun_attr *rx_tun_attr;
	काष्ठा mlx5_pkt_reक्रमmat *decap_pkt_reक्रमmat;
	काष्ठा mlx5_sample_attr *sample;
पूर्ण;

पूर्णांक mlx5_devlink_eचयन_mode_set(काष्ठा devlink *devlink, u16 mode,
				  काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_devlink_eचयन_mode_get(काष्ठा devlink *devlink, u16 *mode);
पूर्णांक mlx5_devlink_eचयन_अंतरभूत_mode_set(काष्ठा devlink *devlink, u8 mode,
					 काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_devlink_eचयन_अंतरभूत_mode_get(काष्ठा devlink *devlink, u8 *mode);
पूर्णांक mlx5_devlink_eचयन_encap_mode_set(काष्ठा devlink *devlink,
					क्रमागत devlink_eचयन_encap_mode encap,
					काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_devlink_eचयन_encap_mode_get(काष्ठा devlink *devlink,
					क्रमागत devlink_eचयन_encap_mode *encap);
पूर्णांक mlx5_devlink_port_function_hw_addr_get(काष्ठा devlink *devlink,
					   काष्ठा devlink_port *port,
					   u8 *hw_addr, पूर्णांक *hw_addr_len,
					   काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_devlink_port_function_hw_addr_set(काष्ठा devlink *devlink,
					   काष्ठा devlink_port *port,
					   स्थिर u8 *hw_addr, पूर्णांक hw_addr_len,
					   काष्ठा netlink_ext_ack *extack);

व्योम *mlx5_eचयन_get_uplink_priv(काष्ठा mlx5_eचयन *esw, u8 rep_type);

पूर्णांक mlx5_eचयन_add_vlan_action(काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_flow_attr *attr);
पूर्णांक mlx5_eचयन_del_vlan_action(काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_flow_attr *attr);
पूर्णांक __mlx5_eचयन_set_vport_vlan(काष्ठा mlx5_eचयन *esw,
				  u16 vport, u16 vlan, u8 qos, u8 set_flags);

अटल अंतरभूत bool mlx5_esw_qos_enabled(काष्ठा mlx5_eचयन *esw)
अणु
	वापस esw->qos.enabled;
पूर्ण

अटल अंतरभूत bool mlx5_eचयन_vlan_actions_supported(काष्ठा mlx5_core_dev *dev,
						       u8 vlan_depth)
अणु
	bool ret = MLX5_CAP_ESW_FLOWTABLE_FDB(dev, pop_vlan) &&
		   MLX5_CAP_ESW_FLOWTABLE_FDB(dev, push_vlan);

	अगर (vlan_depth == 1)
		वापस ret;

	वापस  ret && MLX5_CAP_ESW_FLOWTABLE_FDB(dev, pop_vlan_2) &&
		MLX5_CAP_ESW_FLOWTABLE_FDB(dev, push_vlan_2);
पूर्ण

bool mlx5_esw_lag_prereq(काष्ठा mlx5_core_dev *dev0,
			 काष्ठा mlx5_core_dev *dev1);
bool mlx5_esw_multipath_prereq(काष्ठा mlx5_core_dev *dev0,
			       काष्ठा mlx5_core_dev *dev1);

स्थिर u32 *mlx5_esw_query_functions(काष्ठा mlx5_core_dev *dev);

#घोषणा MLX5_DEBUG_ESWITCH_MASK BIT(3)

#घोषणा esw_info(__dev, क्रमmat, ...)			\
	dev_info((__dev)->device, "E-Switch: " क्रमmat, ##__VA_ARGS__)

#घोषणा esw_warn(__dev, क्रमmat, ...)			\
	dev_warn((__dev)->device, "E-Switch: " क्रमmat, ##__VA_ARGS__)

#घोषणा esw_debug(dev, क्रमmat, ...)				\
	mlx5_core_dbg_mask(dev, MLX5_DEBUG_ESWITCH_MASK, क्रमmat, ##__VA_ARGS__)

अटल अंतरभूत bool mlx5_esw_allowed(स्थिर काष्ठा mlx5_eचयन *esw)
अणु
	वापस esw && MLX5_ESWITCH_MANAGER(esw->dev);
पूर्ण

/* The वापसed number is valid only when the dev is eचयन manager. */
अटल अंतरभूत u16 mlx5_eचयन_manager_vport(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_core_is_ecpf_esw_manager(dev) ?
		MLX5_VPORT_ECPF : MLX5_VPORT_PF;
पूर्ण

अटल अंतरभूत bool
mlx5_esw_is_manager_vport(स्थिर काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	वापस esw->manager_vport == vport_num;
पूर्ण

अटल अंतरभूत u16 mlx5_eचयन_first_host_vport_num(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_core_is_ecpf_esw_manager(dev) ?
		MLX5_VPORT_PF : MLX5_VPORT_FIRST_VF;
पूर्ण

अटल अंतरभूत bool mlx5_eचयन_is_funcs_handler(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_core_is_ecpf_esw_manager(dev);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mlx5_esw_vport_to_devlink_port_index(स्थिर काष्ठा mlx5_core_dev *dev,
				     u16 vport_num)
अणु
	वापस (MLX5_CAP_GEN(dev, vhca_id) << 16) | vport_num;
पूर्ण

अटल अंतरभूत u16
mlx5_esw_devlink_port_index_to_vport_num(अचिन्हित पूर्णांक dl_port_index)
अणु
	वापस dl_port_index & 0xffff;
पूर्ण

/* TODO: This mlx5e_tc function shouldn't be called by eचयन */
व्योम mlx5e_tc_clean_fdb_peer_flows(काष्ठा mlx5_eचयन *esw);

/* Each mark identअगरies eचयन vport type.
 * MLX5_ESW_VPT_HOST_FN is used to identअगरy both PF and VF ports using
 * a single mark.
 * MLX5_ESW_VPT_VF identअगरies a SRIOV VF vport.
 * MLX5_ESW_VPT_SF identअगरies SF vport.
 */
#घोषणा MLX5_ESW_VPT_HOST_FN XA_MARK_0
#घोषणा MLX5_ESW_VPT_VF XA_MARK_1
#घोषणा MLX5_ESW_VPT_SF XA_MARK_2

/* The vport iterator is valid only after vport are initialized in mlx5_eचयन_init.
 * Borrowed the idea from xa_क्रम_each_marked() but with support क्रम desired last element.
 */

#घोषणा mlx5_esw_क्रम_each_vport(esw, index, vport) \
	xa_क्रम_each(&((esw)->vports), index, vport)

#घोषणा mlx5_esw_क्रम_each_entry_marked(xa, index, entry, last, filter)	\
	क्रम (index = 0, entry = xa_find(xa, &index, last, filter); \
	     entry; entry = xa_find_after(xa, &index, last, filter))

#घोषणा mlx5_esw_क्रम_each_vport_marked(esw, index, vport, last, filter)	\
	mlx5_esw_क्रम_each_entry_marked(&((esw)->vports), index, vport, last, filter)

#घोषणा mlx5_esw_क्रम_each_vf_vport(esw, index, vport, last)	\
	mlx5_esw_क्रम_each_vport_marked(esw, index, vport, last, MLX5_ESW_VPT_VF)

#घोषणा mlx5_esw_क्रम_each_host_func_vport(esw, index, vport, last)	\
	mlx5_esw_क्रम_each_vport_marked(esw, index, vport, last, MLX5_ESW_VPT_HOST_FN)

काष्ठा mlx5_eचयन *mlx5_devlink_eचयन_get(काष्ठा devlink *devlink);
काष्ठा mlx5_vport *__must_check
mlx5_eचयन_get_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num);

bool mlx5_eचयन_is_vf_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num);
bool mlx5_esw_is_sf_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num);

पूर्णांक mlx5_esw_funcs_changed_handler(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type, व्योम *data);

पूर्णांक
mlx5_eचयन_enable_pf_vf_vports(काष्ठा mlx5_eचयन *esw,
				 क्रमागत mlx5_eचयन_vport_event enabled_events);
व्योम mlx5_eचयन_disable_pf_vf_vports(काष्ठा mlx5_eचयन *esw);

पूर्णांक mlx5_esw_vport_enable(काष्ठा mlx5_eचयन *esw, u16 vport_num,
			  क्रमागत mlx5_eचयन_vport_event enabled_events);
व्योम mlx5_esw_vport_disable(काष्ठा mlx5_eचयन *esw, u16 vport_num);

पूर्णांक
esw_vport_create_offloads_acl_tables(काष्ठा mlx5_eचयन *esw,
				     काष्ठा mlx5_vport *vport);
व्योम
esw_vport_destroy_offloads_acl_tables(काष्ठा mlx5_eचयन *esw,
				      काष्ठा mlx5_vport *vport);

काष्ठा esw_vport_tbl_namespace अणु
	पूर्णांक max_fte;
	पूर्णांक max_num_groups;
	u32 flags;
पूर्ण;

काष्ठा mlx5_vport_tbl_attr अणु
	u16 chain;
	u16 prio;
	u16 vport;
	स्थिर काष्ठा esw_vport_tbl_namespace *vport_ns;
पूर्ण;

काष्ठा mlx5_flow_table *
mlx5_esw_vporttbl_get(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport_tbl_attr *attr);
व्योम
mlx5_esw_vporttbl_put(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport_tbl_attr *attr);

काष्ठा mlx5_flow_handle *
esw_add_restore_rule(काष्ठा mlx5_eचयन *esw, u32 tag);

पूर्णांक esw_offloads_load_rep(काष्ठा mlx5_eचयन *esw, u16 vport_num);
व्योम esw_offloads_unload_rep(काष्ठा mlx5_eचयन *esw, u16 vport_num);

पूर्णांक mlx5_esw_offloads_rep_load(काष्ठा mlx5_eचयन *esw, u16 vport_num);
व्योम mlx5_esw_offloads_rep_unload(काष्ठा mlx5_eचयन *esw, u16 vport_num);

पूर्णांक mlx5_eचयन_load_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num,
			    क्रमागत mlx5_eचयन_vport_event enabled_events);
व्योम mlx5_eचयन_unload_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num);

पूर्णांक mlx5_eचयन_load_vf_vports(काष्ठा mlx5_eचयन *esw, u16 num_vfs,
				क्रमागत mlx5_eचयन_vport_event enabled_events);
व्योम mlx5_eचयन_unload_vf_vports(काष्ठा mlx5_eचयन *esw, u16 num_vfs);

पूर्णांक mlx5_esw_offloads_devlink_port_रेजिस्टर(काष्ठा mlx5_eचयन *esw, u16 vport_num);
व्योम mlx5_esw_offloads_devlink_port_unरेजिस्टर(काष्ठा mlx5_eचयन *esw, u16 vport_num);
काष्ठा devlink_port *mlx5_esw_offloads_devlink_port(काष्ठा mlx5_eचयन *esw, u16 vport_num);

पूर्णांक mlx5_esw_devlink_sf_port_रेजिस्टर(काष्ठा mlx5_eचयन *esw, काष्ठा devlink_port *dl_port,
				      u16 vport_num, u32 controller, u32 sfnum);
व्योम mlx5_esw_devlink_sf_port_unरेजिस्टर(काष्ठा mlx5_eचयन *esw, u16 vport_num);

पूर्णांक mlx5_esw_offloads_sf_vport_enable(काष्ठा mlx5_eचयन *esw, काष्ठा devlink_port *dl_port,
				      u16 vport_num, u32 controller, u32 sfnum);
व्योम mlx5_esw_offloads_sf_vport_disable(काष्ठा mlx5_eचयन *esw, u16 vport_num);
पूर्णांक mlx5_esw_sf_max_hpf_functions(काष्ठा mlx5_core_dev *dev, u16 *max_sfs, u16 *sf_base_id);

पूर्णांक mlx5_esw_vport_vhca_id_set(काष्ठा mlx5_eचयन *esw, u16 vport_num);
व्योम mlx5_esw_vport_vhca_id_clear(काष्ठा mlx5_eचयन *esw, u16 vport_num);
पूर्णांक mlx5_eचयन_vhca_id_to_vport(काष्ठा mlx5_eचयन *esw, u16 vhca_id, u16 *vport_num);

/**
 * mlx5_esw_event_info - Indicates eचयन mode changed/changing.
 *
 * @new_mode: New mode of eचयन.
 */
काष्ठा mlx5_esw_event_info अणु
	u16 new_mode;
पूर्ण;

पूर्णांक mlx5_esw_event_notअगरier_रेजिस्टर(काष्ठा mlx5_eचयन *esw, काष्ठा notअगरier_block *n);
व्योम mlx5_esw_event_notअगरier_unरेजिस्टर(काष्ठा mlx5_eचयन *esw, काष्ठा notअगरier_block *n);

bool mlx5_esw_hold(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_esw_release(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_esw_get(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_esw_put(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_esw_try_lock(काष्ठा mlx5_eचयन *esw);
व्योम mlx5_esw_unlock(काष्ठा mlx5_eचयन *esw);

व्योम esw_vport_change_handle_locked(काष्ठा mlx5_vport *vport);

bool mlx5_esw_offloads_controller_valid(स्थिर काष्ठा mlx5_eचयन *esw, u32 controller);

#अन्यथा  /* CONFIG_MLX5_ESWITCH */
/* eचयन API stubs */
अटल अंतरभूत पूर्णांक  mlx5_eचयन_init(काष्ठा mlx5_core_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5_eचयन_cleanup(काष्ठा mlx5_eचयन *esw) अणुपूर्ण
अटल अंतरभूत पूर्णांक mlx5_eचयन_enable(काष्ठा mlx5_eचयन *esw, पूर्णांक num_vfs) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5_eचयन_disable(काष्ठा mlx5_eचयन *esw, bool clear_vf) अणुपूर्ण
अटल अंतरभूत bool mlx5_esw_lag_prereq(काष्ठा mlx5_core_dev *dev0, काष्ठा mlx5_core_dev *dev1) अणु वापस true; पूर्ण
अटल अंतरभूत bool mlx5_eचयन_is_funcs_handler(काष्ठा mlx5_core_dev *dev) अणु वापस false; पूर्ण
अटल अंतरभूत
पूर्णांक mlx5_eचयन_set_vport_state(काष्ठा mlx5_eचयन *esw, u16 vport, पूर्णांक link_state) अणु वापस 0; पूर्ण
अटल अंतरभूत स्थिर u32 *mlx5_esw_query_functions(काष्ठा mlx5_core_dev *dev)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_flow_handle *
esw_add_restore_rule(काष्ठा mlx5_eचयन *esw, u32 tag)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mlx5_esw_vport_to_devlink_port_index(स्थिर काष्ठा mlx5_core_dev *dev,
				     u16 vport_num)
अणु
	वापस vport_num;
पूर्ण
#पूर्ण_अगर /* CONFIG_MLX5_ESWITCH */

#पूर्ण_अगर /* __MLX5_ESWITCH_H__ */
