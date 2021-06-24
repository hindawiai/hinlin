<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित _MLX5_FS_
#घोषणा _MLX5_FS_

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>

#घोषणा MLX5_FS_DEFAULT_FLOW_TAG 0x0

क्रमागत अणु
	MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO	= 1 << 16,
	MLX5_FLOW_CONTEXT_ACTION_ENCRYPT	= 1 << 17,
	MLX5_FLOW_CONTEXT_ACTION_DECRYPT	= 1 << 18,
	MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_NS	= 1 << 19,
पूर्ण;

क्रमागत अणु
	MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT = BIT(0),
	MLX5_FLOW_TABLE_TUNNEL_EN_DECAP = BIT(1),
	MLX5_FLOW_TABLE_TERMINATION = BIT(2),
	MLX5_FLOW_TABLE_UNMANAGED = BIT(3),
	MLX5_FLOW_TABLE_OTHER_VPORT = BIT(4),
पूर्ण;

#घोषणा LEFTOVERS_RULE_NUM	 2
अटल अंतरभूत व्योम build_leftovers_ft_param(पूर्णांक *priority,
					    पूर्णांक *n_ent,
					    पूर्णांक *n_grp)
अणु
	*priority = 0; /* Priority of leftovers_prio-0 */
	*n_ent = LEFTOVERS_RULE_NUM;
	*n_grp = LEFTOVERS_RULE_NUM;
पूर्ण

क्रमागत mlx5_flow_namespace_type अणु
	MLX5_FLOW_NAMESPACE_BYPASS,
	MLX5_FLOW_NAMESPACE_LAG,
	MLX5_FLOW_NAMESPACE_OFFLOADS,
	MLX5_FLOW_NAMESPACE_ETHTOOL,
	MLX5_FLOW_NAMESPACE_KERNEL,
	MLX5_FLOW_NAMESPACE_LEFTOVERS,
	MLX5_FLOW_NAMESPACE_ANCHOR,
	MLX5_FLOW_NAMESPACE_FDB,
	MLX5_FLOW_NAMESPACE_ESW_EGRESS,
	MLX5_FLOW_NAMESPACE_ESW_INGRESS,
	MLX5_FLOW_NAMESPACE_SNIFFER_RX,
	MLX5_FLOW_NAMESPACE_SNIFFER_TX,
	MLX5_FLOW_NAMESPACE_EGRESS,
	MLX5_FLOW_NAMESPACE_EGRESS_KERNEL,
	MLX5_FLOW_NAMESPACE_RDMA_RX,
	MLX5_FLOW_NAMESPACE_RDMA_RX_KERNEL,
	MLX5_FLOW_NAMESPACE_RDMA_TX,
पूर्ण;

क्रमागत अणु
	FDB_BYPASS_PATH,
	FDB_TC_OFFLOAD,
	FDB_FT_OFFLOAD,
	FDB_SLOW_PATH,
	FDB_PER_VPORT,
पूर्ण;

काष्ठा mlx5_pkt_reक्रमmat;
काष्ठा mlx5_modअगरy_hdr;
काष्ठा mlx5_flow_table;
काष्ठा mlx5_flow_group;
काष्ठा mlx5_flow_namespace;
काष्ठा mlx5_flow_handle;

क्रमागत अणु
	FLOW_CONTEXT_HAS_TAG = BIT(0),
पूर्ण;

काष्ठा mlx5_flow_context अणु
	u32 flags;
	u32 flow_tag;
	u32 flow_source;
पूर्ण;

काष्ठा mlx5_flow_spec अणु
	u8   match_criteria_enable;
	u32  match_criteria[MLX5_ST_SZ_DW(fte_match_param)];
	u32  match_value[MLX5_ST_SZ_DW(fte_match_param)];
	काष्ठा mlx5_flow_context flow_context;
पूर्ण;

क्रमागत अणु
	MLX5_FLOW_DEST_VPORT_VHCA_ID      = BIT(0),
	MLX5_FLOW_DEST_VPORT_REFORMAT_ID  = BIT(1),
पूर्ण;

काष्ठा mlx5_flow_destination अणु
	क्रमागत mlx5_flow_destination_type	type;
	जोड़ अणु
		u32			tir_num;
		u32			ft_num;
		काष्ठा mlx5_flow_table	*ft;
		u32			counter_id;
		काष्ठा अणु
			u16		num;
			u16		vhca_id;
			काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat;
			u8		flags;
		पूर्ण vport;
		u32			sampler_id;
	पूर्ण;
पूर्ण;

काष्ठा mod_hdr_tbl अणु
	काष्ठा mutex lock; /* protects hlist */
	DECLARE_HASHTABLE(hlist, 8);
पूर्ण;

काष्ठा mlx5_flow_namespace *
mlx5_get_fdb_sub_ns(काष्ठा mlx5_core_dev *dev, पूर्णांक n);
काष्ठा mlx5_flow_namespace *
mlx5_get_flow_namespace(काष्ठा mlx5_core_dev *dev,
			क्रमागत mlx5_flow_namespace_type type);
काष्ठा mlx5_flow_namespace *
mlx5_get_flow_vport_acl_namespace(काष्ठा mlx5_core_dev *dev,
				  क्रमागत mlx5_flow_namespace_type type,
				  पूर्णांक vport);

काष्ठा mlx5_flow_table_attr अणु
	पूर्णांक prio;
	पूर्णांक max_fte;
	u32 level;
	u32 flags;
	काष्ठा mlx5_flow_table *next_ft;

	काष्ठा अणु
		पूर्णांक max_num_groups;
		पूर्णांक num_reserved_entries;
	पूर्ण स्वतःgroup;
पूर्ण;

काष्ठा mlx5_flow_table *
mlx5_create_flow_table(काष्ठा mlx5_flow_namespace *ns,
		       काष्ठा mlx5_flow_table_attr *ft_attr);

काष्ठा mlx5_flow_table *
mlx5_create_स्वतः_grouped_flow_table(काष्ठा mlx5_flow_namespace *ns,
				    काष्ठा mlx5_flow_table_attr *ft_attr);

काष्ठा mlx5_flow_table *
mlx5_create_vport_flow_table(काष्ठा mlx5_flow_namespace *ns,
			     काष्ठा mlx5_flow_table_attr *ft_attr, u16 vport);
काष्ठा mlx5_flow_table *mlx5_create_lag_demux_flow_table(
					       काष्ठा mlx5_flow_namespace *ns,
					       पूर्णांक prio, u32 level);
पूर्णांक mlx5_destroy_flow_table(काष्ठा mlx5_flow_table *ft);

/* inbox should be set with the following values:
 * start_flow_index
 * end_flow_index
 * match_criteria_enable
 * match_criteria
 */
काष्ठा mlx5_flow_group *
mlx5_create_flow_group(काष्ठा mlx5_flow_table *ft, u32 *in);
व्योम mlx5_destroy_flow_group(काष्ठा mlx5_flow_group *fg);

काष्ठा mlx5_fs_vlan अणु
        u16 ethtype;
        u16 vid;
        u8  prio;
पूर्ण;

#घोषणा MLX5_FS_VLAN_DEPTH	2

क्रमागत अणु
	FLOW_ACT_NO_APPEND = BIT(0),
	FLOW_ACT_IGNORE_FLOW_LEVEL = BIT(1),
पूर्ण;

काष्ठा mlx5_flow_act अणु
	u32 action;
	काष्ठा mlx5_modअगरy_hdr  *modअगरy_hdr;
	काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat;
	जोड़ अणु
		u32 ipsec_obj_id;
		uपूर्णांकptr_t esp_id;
	पूर्ण;
	u32 flags;
	काष्ठा mlx5_fs_vlan vlan[MLX5_FS_VLAN_DEPTH];
	काष्ठा ib_counters *counters;
पूर्ण;

#घोषणा MLX5_DECLARE_FLOW_ACT(name) \
	काष्ठा mlx5_flow_act name = अणु .action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST,\
				      .flags =  0, पूर्ण

/* Single destination per rule.
 * Group ID is implied by the match criteria.
 */
काष्ठा mlx5_flow_handle *
mlx5_add_flow_rules(काष्ठा mlx5_flow_table *ft,
		    स्थिर काष्ठा mlx5_flow_spec *spec,
		    काष्ठा mlx5_flow_act *flow_act,
		    काष्ठा mlx5_flow_destination *dest,
		    पूर्णांक num_dest);
व्योम mlx5_del_flow_rules(काष्ठा mlx5_flow_handle *fr);

पूर्णांक mlx5_modअगरy_rule_destination(काष्ठा mlx5_flow_handle *handler,
				 काष्ठा mlx5_flow_destination *new_dest,
				 काष्ठा mlx5_flow_destination *old_dest);

काष्ठा mlx5_fc *mlx5_fc_create(काष्ठा mlx5_core_dev *dev, bool aging);
व्योम mlx5_fc_destroy(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fc *counter);
u64 mlx5_fc_query_lastuse(काष्ठा mlx5_fc *counter);
व्योम mlx5_fc_query_cached(काष्ठा mlx5_fc *counter,
			  u64 *bytes, u64 *packets, u64 *lastuse);
पूर्णांक mlx5_fc_query(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_fc *counter,
		  u64 *packets, u64 *bytes);
u32 mlx5_fc_id(काष्ठा mlx5_fc *counter);

पूर्णांक mlx5_fs_add_rx_underlay_qpn(काष्ठा mlx5_core_dev *dev, u32 underlay_qpn);
पूर्णांक mlx5_fs_हटाओ_rx_underlay_qpn(काष्ठा mlx5_core_dev *dev, u32 underlay_qpn);

काष्ठा mlx5_modअगरy_hdr *mlx5_modअगरy_header_alloc(काष्ठा mlx5_core_dev *dev,
						 u8 ns_type, u8 num_actions,
						 व्योम *modअगरy_actions);
व्योम mlx5_modअगरy_header_dealloc(काष्ठा mlx5_core_dev *dev,
				काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr);

काष्ठा mlx5_pkt_reक्रमmat *mlx5_packet_reक्रमmat_alloc(काष्ठा mlx5_core_dev *dev,
						     पूर्णांक reक्रमmat_type,
						     माप_प्रकार size,
						     व्योम *reक्रमmat_data,
						     क्रमागत mlx5_flow_namespace_type ns_type);
व्योम mlx5_packet_reक्रमmat_dealloc(काष्ठा mlx5_core_dev *dev,
				  काष्ठा mlx5_pkt_reक्रमmat *reक्रमmat);

#पूर्ण_अगर
