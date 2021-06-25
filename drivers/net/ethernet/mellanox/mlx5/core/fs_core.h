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

#अगर_अघोषित _MLX5_FS_CORE_
#घोषणा _MLX5_FS_CORE_

#समावेश <linux/refcount.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/llist.h>
#समावेश <steering/fs_dr.h>

#घोषणा FDB_TC_MAX_CHAIN 3
#घोषणा FDB_FT_CHAIN (FDB_TC_MAX_CHAIN + 1)
#घोषणा FDB_TC_SLOW_PATH_CHAIN (FDB_FT_CHAIN + 1)

/* The index of the last real chain (FT) + 1 as chain zero is valid as well */
#घोषणा FDB_NUM_CHAINS (FDB_FT_CHAIN + 1)

#घोषणा FDB_TC_MAX_PRIO 16
#घोषणा FDB_TC_LEVELS_PER_PRIO 2

काष्ठा mlx5_modअगरy_hdr अणु
	क्रमागत mlx5_flow_namespace_type ns_type;
	जोड़ अणु
		काष्ठा mlx5_fs_dr_action action;
		u32 id;
	पूर्ण;
पूर्ण;

काष्ठा mlx5_pkt_reक्रमmat अणु
	क्रमागत mlx5_flow_namespace_type ns_type;
	पूर्णांक reक्रमmat_type; /* from mlx5_अगरc */
	जोड़ अणु
		काष्ठा mlx5_fs_dr_action action;
		u32 id;
	पूर्ण;
पूर्ण;

/* FS_TYPE_PRIO_CHAINS is a PRIO that will have namespaces only,
 * and those are in parallel to one another when going over them to connect
 * a new flow table. Meaning the last flow table in a TYPE_PRIO prio in one
 * parallel namespace will not स्वतःmatically connect to the first flow table
 * found in any prio in any next namespace, but skip the entire containing
 * TYPE_PRIO_CHAINS prio.
 *
 * This is used to implement tc chains, each chain of prios is a dअगरferent
 * namespace inside a containing TYPE_PRIO_CHAINS prio.
 */

क्रमागत fs_node_type अणु
	FS_TYPE_NAMESPACE,
	FS_TYPE_PRIO,
	FS_TYPE_PRIO_CHAINS,
	FS_TYPE_FLOW_TABLE,
	FS_TYPE_FLOW_GROUP,
	FS_TYPE_FLOW_ENTRY,
	FS_TYPE_FLOW_DEST
पूर्ण;

क्रमागत fs_flow_table_type अणु
	FS_FT_NIC_RX          = 0x0,
	FS_FT_NIC_TX          = 0x1,
	FS_FT_ESW_EGRESS_ACL  = 0x2,
	FS_FT_ESW_INGRESS_ACL = 0x3,
	FS_FT_FDB             = 0X4,
	FS_FT_SNIFFER_RX	= 0X5,
	FS_FT_SNIFFER_TX	= 0X6,
	FS_FT_RDMA_RX		= 0X7,
	FS_FT_RDMA_TX		= 0X8,
	FS_FT_MAX_TYPE = FS_FT_RDMA_TX,
पूर्ण;

क्रमागत fs_flow_table_op_mod अणु
	FS_FT_OP_MOD_NORMAL,
	FS_FT_OP_MOD_LAG_DEMUX,
पूर्ण;

क्रमागत fs_fte_status अणु
	FS_FTE_STATUS_EXISTING = 1UL << 0,
पूर्ण;

क्रमागत mlx5_flow_steering_mode अणु
	MLX5_FLOW_STEERING_MODE_DMFS,
	MLX5_FLOW_STEERING_MODE_SMFS
पूर्ण;

काष्ठा mlx5_flow_steering अणु
	काष्ठा mlx5_core_dev *dev;
	क्रमागत   mlx5_flow_steering_mode	mode;
	काष्ठा kmem_cache		*fgs_cache;
	काष्ठा kmem_cache               *ftes_cache;
	काष्ठा mlx5_flow_root_namespace *root_ns;
	काष्ठा mlx5_flow_root_namespace *fdb_root_ns;
	काष्ठा mlx5_flow_namespace	**fdb_sub_ns;
	काष्ठा mlx5_flow_root_namespace **esw_egress_root_ns;
	काष्ठा mlx5_flow_root_namespace **esw_ingress_root_ns;
	काष्ठा mlx5_flow_root_namespace	*snअगरfer_tx_root_ns;
	काष्ठा mlx5_flow_root_namespace	*snअगरfer_rx_root_ns;
	काष्ठा mlx5_flow_root_namespace	*rdma_rx_root_ns;
	काष्ठा mlx5_flow_root_namespace	*rdma_tx_root_ns;
	काष्ठा mlx5_flow_root_namespace	*egress_root_ns;
	पूर्णांक esw_egress_acl_vports;
	पूर्णांक esw_ingress_acl_vports;
पूर्ण;

काष्ठा fs_node अणु
	काष्ठा list_head	list;
	काष्ठा list_head	children;
	क्रमागत fs_node_type	type;
	काष्ठा fs_node		*parent;
	काष्ठा fs_node		*root;
	/* lock the node क्रम writing and traversing */
	काष्ठा rw_semaphore	lock;
	refcount_t		refcount;
	bool			active;
	व्योम			(*del_hw_func)(काष्ठा fs_node *);
	व्योम			(*del_sw_func)(काष्ठा fs_node *);
	atomic_t		version;
पूर्ण;

काष्ठा mlx5_flow_rule अणु
	काष्ठा fs_node				node;
	काष्ठा mlx5_flow_table			*ft;
	काष्ठा mlx5_flow_destination		dest_attr;
	/* next_ft should be accessed under chain_lock and only of
	 * destination type is FWD_NEXT_fT.
	 */
	काष्ठा list_head			next_ft;
	u32					sw_action;
पूर्ण;

काष्ठा mlx5_flow_handle अणु
	पूर्णांक num_rules;
	काष्ठा mlx5_flow_rule *rule[];
पूर्ण;

/* Type of children is mlx5_flow_group */
काष्ठा mlx5_flow_table अणु
	काष्ठा fs_node			node;
	काष्ठा mlx5_fs_dr_table		fs_dr_table;
	u32				id;
	u16				vport;
	अचिन्हित पूर्णांक			max_fte;
	अचिन्हित पूर्णांक			level;
	क्रमागत fs_flow_table_type		type;
	क्रमागत fs_flow_table_op_mod	op_mod;
	काष्ठा अणु
		bool			active;
		अचिन्हित पूर्णांक		required_groups;
		अचिन्हित पूर्णांक		group_size;
		अचिन्हित पूर्णांक		num_groups;
		अचिन्हित पूर्णांक		max_fte;
	पूर्ण स्वतःgroup;
	/* Protect fwd_rules */
	काष्ठा mutex			lock;
	/* FWD rules that poपूर्णांक on this flow table */
	काष्ठा list_head		fwd_rules;
	u32				flags;
	काष्ठा rhltable			fgs_hash;
	क्रमागत mlx5_flow_table_miss_action def_miss_action;
	काष्ठा mlx5_flow_namespace	*ns;
पूर्ण;

काष्ठा mlx5_ft_underlay_qp अणु
	काष्ठा list_head list;
	u32 qpn;
पूर्ण;

#घोषणा MLX5_FTE_MATCH_PARAM_RESERVED	reserved_at_c00
/* Calculate the fte_match_param length and without the reserved length.
 * Make sure the reserved field is the last.
 */
#घोषणा MLX5_ST_SZ_DW_MATCH_PARAM					    \
	((MLX5_BYTE_OFF(fte_match_param, MLX5_FTE_MATCH_PARAM_RESERVED) / माप(u32)) + \
	 BUILD_BUG_ON_ZERO(MLX5_ST_SZ_BYTES(fte_match_param) !=		     \
			   MLX5_FLD_SZ_BYTES(fte_match_param,		     \
					     MLX5_FTE_MATCH_PARAM_RESERVED) +\
			   MLX5_BYTE_OFF(fte_match_param,		     \
					 MLX5_FTE_MATCH_PARAM_RESERVED)))

/* Type of children is mlx5_flow_rule */
काष्ठा fs_fte अणु
	काष्ठा fs_node			node;
	काष्ठा mlx5_fs_dr_rule		fs_dr_rule;
	u32				val[MLX5_ST_SZ_DW_MATCH_PARAM];
	u32				dests_size;
	u32				index;
	काष्ठा mlx5_flow_context	flow_context;
	काष्ठा mlx5_flow_act		action;
	क्रमागत fs_fte_status		status;
	काष्ठा mlx5_fc			*counter;
	काष्ठा rhash_head		hash;
	पूर्णांक				modअगरy_mask;
पूर्ण;

/* Type of children is mlx5_flow_table/namespace */
काष्ठा fs_prio अणु
	काष्ठा fs_node			node;
	अचिन्हित पूर्णांक			num_levels;
	अचिन्हित पूर्णांक			start_level;
	अचिन्हित पूर्णांक			prio;
	अचिन्हित पूर्णांक			num_ft;
पूर्ण;

/* Type of children is fs_prio */
काष्ठा mlx5_flow_namespace अणु
	/* parent == शून्य => root ns */
	काष्ठा	fs_node			node;
	क्रमागत mlx5_flow_table_miss_action def_miss_action;
पूर्ण;

काष्ठा mlx5_flow_group_mask अणु
	u8	match_criteria_enable;
	u32	match_criteria[MLX5_ST_SZ_DW_MATCH_PARAM];
पूर्ण;

/* Type of children is fs_fte */
काष्ठा mlx5_flow_group अणु
	काष्ठा fs_node			node;
	काष्ठा mlx5_fs_dr_matcher	fs_dr_matcher;
	काष्ठा mlx5_flow_group_mask	mask;
	u32				start_index;
	u32				max_ftes;
	काष्ठा ida			fte_allocator;
	u32				id;
	काष्ठा rhashtable		ftes_hash;
	काष्ठा rhlist_head		hash;
पूर्ण;

काष्ठा mlx5_flow_root_namespace अणु
	काष्ठा mlx5_flow_namespace	ns;
	क्रमागत   mlx5_flow_steering_mode	mode;
	काष्ठा mlx5_fs_dr_करोमुख्य	fs_dr_करोमुख्य;
	क्रमागत   fs_flow_table_type	table_type;
	काष्ठा mlx5_core_dev		*dev;
	काष्ठा mlx5_flow_table		*root_ft;
	/* Should be held when chaining flow tables */
	काष्ठा mutex			chain_lock;
	काष्ठा list_head		underlay_qpns;
	स्थिर काष्ठा mlx5_flow_cmds	*cmds;
पूर्ण;

पूर्णांक mlx5_init_fc_stats(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cleanup_fc_stats(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_fc_queue_stats_work(काष्ठा mlx5_core_dev *dev,
			      काष्ठा delayed_work *dwork,
			      अचिन्हित दीर्घ delay);
व्योम mlx5_fc_update_sampling_पूर्णांकerval(काष्ठा mlx5_core_dev *dev,
				      अचिन्हित दीर्घ पूर्णांकerval);

स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_fw_cmds(व्योम);

पूर्णांक mlx5_flow_namespace_set_peer(काष्ठा mlx5_flow_root_namespace *ns,
				 काष्ठा mlx5_flow_root_namespace *peer_ns);

पूर्णांक mlx5_flow_namespace_set_mode(काष्ठा mlx5_flow_namespace *ns,
				 क्रमागत mlx5_flow_steering_mode mode);

पूर्णांक mlx5_init_fs(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cleanup_fs(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_fs_egress_acls_init(काष्ठा mlx5_core_dev *dev, पूर्णांक total_vports);
व्योम mlx5_fs_egress_acls_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_fs_ingress_acls_init(काष्ठा mlx5_core_dev *dev, पूर्णांक total_vports);
व्योम mlx5_fs_ingress_acls_cleanup(काष्ठा mlx5_core_dev *dev);

#घोषणा fs_get_obj(v, _node)  अणुv = container_of((_node), typeof(*v), node); पूर्ण

#घोषणा fs_list_क्रम_each_entry(pos, root)		\
	list_क्रम_each_entry(pos, root, node.list)

#घोषणा fs_list_क्रम_each_entry_safe(pos, पंचांगp, root)		\
	list_क्रम_each_entry_safe(pos, पंचांगp, root, node.list)

#घोषणा fs_क्रम_each_ns_or_ft_reverse(pos, prio)				\
	list_क्रम_each_entry_reverse(pos, &(prio)->node.children, list)

#घोषणा fs_क्रम_each_ns_or_ft(pos, prio)					\
	list_क्रम_each_entry(pos, (&(prio)->node.children), list)

#घोषणा fs_क्रम_each_prio(pos, ns)			\
	fs_list_क्रम_each_entry(pos, &(ns)->node.children)

#घोषणा fs_क्रम_each_ns(pos, prio)			\
	fs_list_क्रम_each_entry(pos, &(prio)->node.children)

#घोषणा fs_क्रम_each_ft(pos, prio)			\
	fs_list_क्रम_each_entry(pos, &(prio)->node.children)

#घोषणा fs_क्रम_each_ft_safe(pos, पंचांगp, prio)			\
	fs_list_क्रम_each_entry_safe(pos, पंचांगp, &(prio)->node.children)

#घोषणा fs_क्रम_each_fg(pos, ft)			\
	fs_list_क्रम_each_entry(pos, &(ft)->node.children)

#घोषणा fs_क्रम_each_fte(pos, fg)			\
	fs_list_क्रम_each_entry(pos, &(fg)->node.children)

#घोषणा fs_क्रम_each_dst(pos, fte)			\
	fs_list_क्रम_each_entry(pos, &(fte)->node.children)

#घोषणा MLX5_CAP_FLOWTABLE_TYPE(mdev, cap, type) (		\
	(type == FS_FT_NIC_RX) ? MLX5_CAP_FLOWTABLE_NIC_RX(mdev, cap) :		\
	(type == FS_FT_ESW_EGRESS_ACL) ? MLX5_CAP_ESW_EGRESS_ACL(mdev, cap) :		\
	(type == FS_FT_ESW_INGRESS_ACL) ? MLX5_CAP_ESW_INGRESS_ACL(mdev, cap) :		\
	(type == FS_FT_FDB) ? MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, cap) :		\
	(type == FS_FT_SNIFFER_RX) ? MLX5_CAP_FLOWTABLE_SNIFFER_RX(mdev, cap) :		\
	(type == FS_FT_SNIFFER_TX) ? MLX5_CAP_FLOWTABLE_SNIFFER_TX(mdev, cap) :		\
	(type == FS_FT_RDMA_RX) ? MLX5_CAP_FLOWTABLE_RDMA_RX(mdev, cap) :		\
	(type == FS_FT_RDMA_TX) ? MLX5_CAP_FLOWTABLE_RDMA_TX(mdev, cap) :      \
	(BUILD_BUG_ON_ZERO(FS_FT_RDMA_TX != FS_FT_MAX_TYPE))\
	)

#पूर्ण_अगर
