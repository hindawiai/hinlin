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

#समावेश <linux/mutex.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/eचयन.h>

#समावेश "mlx5_core.h"
#समावेश "fs_core.h"
#समावेश "fs_cmd.h"
#समावेश "diag/fs_tracepoint.h"
#समावेश "accel/ipsec.h"
#समावेश "fpga/ipsec.h"

#घोषणा INIT_TREE_NODE_ARRAY_SIZE(...)	(माप((काष्ठा init_tree_node[])अणु__VA_ARGS__पूर्ण) /\
					 माप(काष्ठा init_tree_node))

#घोषणा ADD_PRIO(num_prios_val, min_level_val, num_levels_val, caps_val,\
		 ...) अणु.type = FS_TYPE_PRIO,\
	.min_ft_level = min_level_val,\
	.num_levels = num_levels_val,\
	.num_leaf_prios = num_prios_val,\
	.caps = caps_val,\
	.children = (काष्ठा init_tree_node[]) अणु__VA_ARGS__पूर्ण,\
	.ar_size = INIT_TREE_NODE_ARRAY_SIZE(__VA_ARGS__) \
पूर्ण

#घोषणा ADD_MULTIPLE_PRIO(num_prios_val, num_levels_val, ...)\
	ADD_PRIO(num_prios_val, 0, num_levels_val, अणुपूर्ण,\
		 __VA_ARGS__)\

#घोषणा ADD_NS(def_miss_act, ...) अणु.type = FS_TYPE_NAMESPACE,	\
	.def_miss_action = def_miss_act,\
	.children = (काष्ठा init_tree_node[]) अणु__VA_ARGS__पूर्ण,\
	.ar_size = INIT_TREE_NODE_ARRAY_SIZE(__VA_ARGS__) \
पूर्ण

#घोषणा INIT_CAPS_ARRAY_SIZE(...) (माप((दीर्घ[])अणु__VA_ARGS__पूर्ण) /\
				   माप(दीर्घ))

#घोषणा FS_CAP(cap) (__mlx5_bit_off(flow_table_nic_cap, cap))

#घोषणा FS_REQUIRED_CAPS(...) अणु.arr_sz = INIT_CAPS_ARRAY_SIZE(__VA_ARGS__), \
			       .caps = (दीर्घ[]) अणु__VA_ARGS__पूर्ण पूर्ण

#घोषणा FS_CHAINING_CAPS  FS_REQUIRED_CAPS(FS_CAP(flow_table_properties_nic_receive.flow_modअगरy_en), \
					   FS_CAP(flow_table_properties_nic_receive.modअगरy_root), \
					   FS_CAP(flow_table_properties_nic_receive.identअगरied_miss_table_mode), \
					   FS_CAP(flow_table_properties_nic_receive.flow_table_modअगरy))

#घोषणा FS_CHAINING_CAPS_EGRESS                                                \
	FS_REQUIRED_CAPS(                                                      \
		FS_CAP(flow_table_properties_nic_transmit.flow_modअगरy_en),     \
		FS_CAP(flow_table_properties_nic_transmit.modअगरy_root),        \
		FS_CAP(flow_table_properties_nic_transmit                      \
			       .identअगरied_miss_table_mode),                   \
		FS_CAP(flow_table_properties_nic_transmit.flow_table_modअगरy))

#घोषणा FS_CHAINING_CAPS_RDMA_TX                                                \
	FS_REQUIRED_CAPS(                                                       \
		FS_CAP(flow_table_properties_nic_transmit_rdma.flow_modअगरy_en), \
		FS_CAP(flow_table_properties_nic_transmit_rdma.modअगरy_root),    \
		FS_CAP(flow_table_properties_nic_transmit_rdma                  \
			       .identअगरied_miss_table_mode),                    \
		FS_CAP(flow_table_properties_nic_transmit_rdma                  \
			       .flow_table_modअगरy))

#घोषणा LEFTOVERS_NUM_LEVELS 1
#घोषणा LEFTOVERS_NUM_PRIOS 1

#घोषणा BY_PASS_PRIO_NUM_LEVELS 1
#घोषणा BY_PASS_MIN_LEVEL (ETHTOOL_MIN_LEVEL + MLX5_BY_PASS_NUM_PRIOS +\
			   LEFTOVERS_NUM_PRIOS)

#घोषणा ETHTOOL_PRIO_NUM_LEVELS 1
#घोषणा ETHTOOL_NUM_PRIOS 11
#घोषणा ETHTOOL_MIN_LEVEL (KERNEL_MIN_LEVEL + ETHTOOL_NUM_PRIOS)
/* Promiscuous, Vlan, mac, ttc, inner ttc, अणुUDP/ANY/aRFS/accel/अणुesp, esp_errपूर्णपूर्ण */
#घोषणा KERNEL_NIC_PRIO_NUM_LEVELS 7
#घोषणा KERNEL_NIC_NUM_PRIOS 1
/* One more level क्रम tc */
#घोषणा KERNEL_MIN_LEVEL (KERNEL_NIC_PRIO_NUM_LEVELS + 1)

#घोषणा KERNEL_NIC_TC_NUM_PRIOS  1
#घोषणा KERNEL_NIC_TC_NUM_LEVELS 2

#घोषणा ANCHOR_NUM_LEVELS 1
#घोषणा ANCHOR_NUM_PRIOS 1
#घोषणा ANCHOR_MIN_LEVEL (BY_PASS_MIN_LEVEL + 1)

#घोषणा OFFLOADS_MAX_FT 2
#घोषणा OFFLOADS_NUM_PRIOS 2
#घोषणा OFFLOADS_MIN_LEVEL (ANCHOR_MIN_LEVEL + OFFLOADS_NUM_PRIOS)

#घोषणा LAG_PRIO_NUM_LEVELS 1
#घोषणा LAG_NUM_PRIOS 1
#घोषणा LAG_MIN_LEVEL (OFFLOADS_MIN_LEVEL + 1)

#घोषणा KERNEL_TX_IPSEC_NUM_PRIOS  1
#घोषणा KERNEL_TX_IPSEC_NUM_LEVELS 1
#घोषणा KERNEL_TX_MIN_LEVEL        (KERNEL_TX_IPSEC_NUM_LEVELS)

काष्ठा node_caps अणु
	माप_प्रकार	arr_sz;
	दीर्घ	*caps;
पूर्ण;

अटल काष्ठा init_tree_node अणु
	क्रमागत fs_node_type	type;
	काष्ठा init_tree_node *children;
	पूर्णांक ar_size;
	काष्ठा node_caps caps;
	पूर्णांक min_ft_level;
	पूर्णांक num_leaf_prios;
	पूर्णांक prio;
	पूर्णांक num_levels;
	क्रमागत mlx5_flow_table_miss_action def_miss_action;
पूर्ण root_fs = अणु
	.type = FS_TYPE_NAMESPACE,
	.ar_size = 7,
	  .children = (काष्ठा init_tree_node[])अणु
		  ADD_PRIO(0, BY_PASS_MIN_LEVEL, 0, FS_CHAINING_CAPS,
			   ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				  ADD_MULTIPLE_PRIO(MLX5_BY_PASS_NUM_PRIOS,
						    BY_PASS_PRIO_NUM_LEVELS))),
		  ADD_PRIO(0, LAG_MIN_LEVEL, 0, FS_CHAINING_CAPS,
			   ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				  ADD_MULTIPLE_PRIO(LAG_NUM_PRIOS,
						    LAG_PRIO_NUM_LEVELS))),
		  ADD_PRIO(0, OFFLOADS_MIN_LEVEL, 0, FS_CHAINING_CAPS,
			   ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				  ADD_MULTIPLE_PRIO(OFFLOADS_NUM_PRIOS,
						    OFFLOADS_MAX_FT))),
		  ADD_PRIO(0, ETHTOOL_MIN_LEVEL, 0, FS_CHAINING_CAPS,
			   ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				  ADD_MULTIPLE_PRIO(ETHTOOL_NUM_PRIOS,
						    ETHTOOL_PRIO_NUM_LEVELS))),
		  ADD_PRIO(0, KERNEL_MIN_LEVEL, 0, अणुपूर्ण,
			   ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				  ADD_MULTIPLE_PRIO(KERNEL_NIC_TC_NUM_PRIOS,
						    KERNEL_NIC_TC_NUM_LEVELS),
				  ADD_MULTIPLE_PRIO(KERNEL_NIC_NUM_PRIOS,
						    KERNEL_NIC_PRIO_NUM_LEVELS))),
		  ADD_PRIO(0, BY_PASS_MIN_LEVEL, 0, FS_CHAINING_CAPS,
			   ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				  ADD_MULTIPLE_PRIO(LEFTOVERS_NUM_PRIOS,
						    LEFTOVERS_NUM_LEVELS))),
		  ADD_PRIO(0, ANCHOR_MIN_LEVEL, 0, अणुपूर्ण,
			   ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				  ADD_MULTIPLE_PRIO(ANCHOR_NUM_PRIOS,
						    ANCHOR_NUM_LEVELS))),
	पूर्ण
पूर्ण;

अटल काष्ठा init_tree_node egress_root_fs = अणु
	.type = FS_TYPE_NAMESPACE,
#अगर_घोषित CONFIG_MLX5_IPSEC
	.ar_size = 2,
#अन्यथा
	.ar_size = 1,
#पूर्ण_अगर
	.children = (काष्ठा init_tree_node[]) अणु
		ADD_PRIO(0, MLX5_BY_PASS_NUM_PRIOS, 0,
			 FS_CHAINING_CAPS_EGRESS,
			 ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				ADD_MULTIPLE_PRIO(MLX5_BY_PASS_NUM_PRIOS,
						  BY_PASS_PRIO_NUM_LEVELS))),
#अगर_घोषित CONFIG_MLX5_IPSEC
		ADD_PRIO(0, KERNEL_TX_MIN_LEVEL, 0,
			 FS_CHAINING_CAPS_EGRESS,
			 ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				ADD_MULTIPLE_PRIO(KERNEL_TX_IPSEC_NUM_PRIOS,
						  KERNEL_TX_IPSEC_NUM_LEVELS))),
#पूर्ण_अगर
	पूर्ण
पूर्ण;

#घोषणा RDMA_RX_BYPASS_PRIO 0
#घोषणा RDMA_RX_KERNEL_PRIO 1
अटल काष्ठा init_tree_node rdma_rx_root_fs = अणु
	.type = FS_TYPE_NAMESPACE,
	.ar_size = 2,
	.children = (काष्ठा init_tree_node[]) अणु
		[RDMA_RX_BYPASS_PRIO] =
		ADD_PRIO(0, MLX5_BY_PASS_NUM_REGULAR_PRIOS, 0,
			 FS_CHAINING_CAPS,
			 ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				ADD_MULTIPLE_PRIO(MLX5_BY_PASS_NUM_REGULAR_PRIOS,
						  BY_PASS_PRIO_NUM_LEVELS))),
		[RDMA_RX_KERNEL_PRIO] =
		ADD_PRIO(0, MLX5_BY_PASS_NUM_REGULAR_PRIOS + 1, 0,
			 FS_CHAINING_CAPS,
			 ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_SWITCH_DOMAIN,
				ADD_MULTIPLE_PRIO(1, 1))),
	पूर्ण
पूर्ण;

अटल काष्ठा init_tree_node rdma_tx_root_fs = अणु
	.type = FS_TYPE_NAMESPACE,
	.ar_size = 1,
	.children = (काष्ठा init_tree_node[]) अणु
		ADD_PRIO(0, MLX5_BY_PASS_NUM_PRIOS, 0,
			 FS_CHAINING_CAPS_RDMA_TX,
			 ADD_NS(MLX5_FLOW_TABLE_MISS_ACTION_DEF,
				ADD_MULTIPLE_PRIO(MLX5_BY_PASS_NUM_PRIOS,
						  BY_PASS_PRIO_NUM_LEVELS))),
	पूर्ण
पूर्ण;

क्रमागत fs_i_lock_class अणु
	FS_LOCK_GRANDPARENT,
	FS_LOCK_PARENT,
	FS_LOCK_CHILD
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params rhash_fte = अणु
	.key_len = माप_field(काष्ठा fs_fte, val),
	.key_offset = दुरत्व(काष्ठा fs_fte, val),
	.head_offset = दुरत्व(काष्ठा fs_fte, hash),
	.स्वतःmatic_shrinking = true,
	.min_size = 1,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params rhash_fg = अणु
	.key_len = माप_field(काष्ठा mlx5_flow_group, mask),
	.key_offset = दुरत्व(काष्ठा mlx5_flow_group, mask),
	.head_offset = दुरत्व(काष्ठा mlx5_flow_group, hash),
	.स्वतःmatic_shrinking = true,
	.min_size = 1,

पूर्ण;

अटल व्योम del_hw_flow_table(काष्ठा fs_node *node);
अटल व्योम del_hw_flow_group(काष्ठा fs_node *node);
अटल व्योम del_hw_fte(काष्ठा fs_node *node);
अटल व्योम del_sw_flow_table(काष्ठा fs_node *node);
अटल व्योम del_sw_flow_group(काष्ठा fs_node *node);
अटल व्योम del_sw_fte(काष्ठा fs_node *node);
अटल व्योम del_sw_prio(काष्ठा fs_node *node);
अटल व्योम del_sw_ns(काष्ठा fs_node *node);
/* Delete rule (destination) is special हाल that
 * requires to lock the FTE क्रम all the deletion process.
 */
अटल व्योम del_sw_hw_rule(काष्ठा fs_node *node);
अटल bool mlx5_flow_dests_cmp(काष्ठा mlx5_flow_destination *d1,
				काष्ठा mlx5_flow_destination *d2);
अटल व्योम cleanup_root_ns(काष्ठा mlx5_flow_root_namespace *root_ns);
अटल काष्ठा mlx5_flow_rule *
find_flow_rule(काष्ठा fs_fte *fte,
	       काष्ठा mlx5_flow_destination *dest);

अटल व्योम tree_init_node(काष्ठा fs_node *node,
			   व्योम (*del_hw_func)(काष्ठा fs_node *),
			   व्योम (*del_sw_func)(काष्ठा fs_node *))
अणु
	refcount_set(&node->refcount, 1);
	INIT_LIST_HEAD(&node->list);
	INIT_LIST_HEAD(&node->children);
	init_rwsem(&node->lock);
	node->del_hw_func = del_hw_func;
	node->del_sw_func = del_sw_func;
	node->active = false;
पूर्ण

अटल व्योम tree_add_node(काष्ठा fs_node *node, काष्ठा fs_node *parent)
अणु
	अगर (parent)
		refcount_inc(&parent->refcount);
	node->parent = parent;

	/* Parent is the root */
	अगर (!parent)
		node->root = node;
	अन्यथा
		node->root = parent->root;
पूर्ण

अटल पूर्णांक tree_get_node(काष्ठा fs_node *node)
अणु
	वापस refcount_inc_not_zero(&node->refcount);
पूर्ण

अटल व्योम nested_करोwn_पढ़ो_ref_node(काष्ठा fs_node *node,
				      क्रमागत fs_i_lock_class class)
अणु
	अगर (node) अणु
		करोwn_पढ़ो_nested(&node->lock, class);
		refcount_inc(&node->refcount);
	पूर्ण
पूर्ण

अटल व्योम nested_करोwn_ग_लिखो_ref_node(काष्ठा fs_node *node,
				       क्रमागत fs_i_lock_class class)
अणु
	अगर (node) अणु
		करोwn_ग_लिखो_nested(&node->lock, class);
		refcount_inc(&node->refcount);
	पूर्ण
पूर्ण

अटल व्योम करोwn_ग_लिखो_ref_node(काष्ठा fs_node *node, bool locked)
अणु
	अगर (node) अणु
		अगर (!locked)
			करोwn_ग_लिखो(&node->lock);
		refcount_inc(&node->refcount);
	पूर्ण
पूर्ण

अटल व्योम up_पढ़ो_ref_node(काष्ठा fs_node *node)
अणु
	refcount_dec(&node->refcount);
	up_पढ़ो(&node->lock);
पूर्ण

अटल व्योम up_ग_लिखो_ref_node(काष्ठा fs_node *node, bool locked)
अणु
	refcount_dec(&node->refcount);
	अगर (!locked)
		up_ग_लिखो(&node->lock);
पूर्ण

अटल व्योम tree_put_node(काष्ठा fs_node *node, bool locked)
अणु
	काष्ठा fs_node *parent_node = node->parent;

	अगर (refcount_dec_and_test(&node->refcount)) अणु
		अगर (node->del_hw_func)
			node->del_hw_func(node);
		अगर (parent_node) अणु
			करोwn_ग_लिखो_ref_node(parent_node, locked);
			list_del_init(&node->list);
		पूर्ण
		node->del_sw_func(node);
		अगर (parent_node)
			up_ग_लिखो_ref_node(parent_node, locked);
		node = शून्य;
	पूर्ण
	अगर (!node && parent_node)
		tree_put_node(parent_node, locked);
पूर्ण

अटल पूर्णांक tree_हटाओ_node(काष्ठा fs_node *node, bool locked)
अणु
	अगर (refcount_पढ़ो(&node->refcount) > 1) अणु
		refcount_dec(&node->refcount);
		वापस -EEXIST;
	पूर्ण
	tree_put_node(node, locked);
	वापस 0;
पूर्ण

अटल काष्ठा fs_prio *find_prio(काष्ठा mlx5_flow_namespace *ns,
				 अचिन्हित पूर्णांक prio)
अणु
	काष्ठा fs_prio *iter_prio;

	fs_क्रम_each_prio(iter_prio, ns) अणु
		अगर (iter_prio->prio == prio)
			वापस iter_prio;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool is_fwd_next_action(u32 action)
अणु
	वापस action & (MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO |
			 MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_NS);
पूर्ण

अटल bool check_valid_spec(स्थिर काष्ठा mlx5_flow_spec *spec)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_ST_SZ_DW_MATCH_PARAM; i++)
		अगर (spec->match_value[i] & ~spec->match_criteria[i]) अणु
			pr_warn("mlx5_core: match_value differs from match_criteria\n");
			वापस false;
		पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा mlx5_flow_root_namespace *find_root(काष्ठा fs_node *node)
अणु
	काष्ठा fs_node *root;
	काष्ठा mlx5_flow_namespace *ns;

	root = node->root;

	अगर (WARN_ON(root->type != FS_TYPE_NAMESPACE)) अणु
		pr_warn("mlx5: flow steering node is not in tree or garbaged\n");
		वापस शून्य;
	पूर्ण

	ns = container_of(root, काष्ठा mlx5_flow_namespace, node);
	वापस container_of(ns, काष्ठा mlx5_flow_root_namespace, ns);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_flow_steering *get_steering(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(node);

	अगर (root)
		वापस root->dev->priv.steering;
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mlx5_core_dev *get_dev(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(node);

	अगर (root)
		वापस root->dev;
	वापस शून्य;
पूर्ण

अटल व्योम del_sw_ns(काष्ठा fs_node *node)
अणु
	kमुक्त(node);
पूर्ण

अटल व्योम del_sw_prio(काष्ठा fs_node *node)
अणु
	kमुक्त(node);
पूर्ण

अटल व्योम del_hw_flow_table(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_core_dev *dev;
	पूर्णांक err;

	fs_get_obj(ft, node);
	dev = get_dev(&ft->node);
	root = find_root(&ft->node);
	trace_mlx5_fs_del_ft(ft);

	अगर (node->active) अणु
		err = root->cmds->destroy_flow_table(root, ft);
		अगर (err)
			mlx5_core_warn(dev, "flow steering can't destroy ft\n");
	पूर्ण
पूर्ण

अटल व्योम del_sw_flow_table(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_table *ft;
	काष्ठा fs_prio *prio;

	fs_get_obj(ft, node);

	rhltable_destroy(&ft->fgs_hash);
	अगर (ft->node.parent) अणु
		fs_get_obj(prio, ft->node.parent);
		prio->num_ft--;
	पूर्ण
	kमुक्त(ft);
पूर्ण

अटल व्योम modअगरy_fte(काष्ठा fs_fte *fte)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *fg;
	काष्ठा mlx5_core_dev *dev;
	पूर्णांक err;

	fs_get_obj(fg, fte->node.parent);
	fs_get_obj(ft, fg->node.parent);
	dev = get_dev(&fte->node);

	root = find_root(&ft->node);
	err = root->cmds->update_fte(root, ft, fg, fte->modअगरy_mask, fte);
	अगर (err)
		mlx5_core_warn(dev,
			       "%s can't del rule fg id=%d fte_index=%d\n",
			       __func__, fg->id, fte->index);
	fte->modअगरy_mask = 0;
पूर्ण

अटल व्योम del_sw_hw_rule(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_rule *rule;
	काष्ठा fs_fte *fte;

	fs_get_obj(rule, node);
	fs_get_obj(fte, rule->node.parent);
	trace_mlx5_fs_del_rule(rule);
	अगर (is_fwd_next_action(rule->sw_action)) अणु
		mutex_lock(&rule->dest_attr.ft->lock);
		list_del(&rule->next_ft);
		mutex_unlock(&rule->dest_attr.ft->lock);
	पूर्ण

	अगर (rule->dest_attr.type == MLX5_FLOW_DESTINATION_TYPE_COUNTER  &&
	    --fte->dests_size) अणु
		fte->modअगरy_mask |=
			BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_ACTION) |
			BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_FLOW_COUNTERS);
		fte->action.action &= ~MLX5_FLOW_CONTEXT_ACTION_COUNT;
		जाओ out;
	पूर्ण

	अगर (rule->dest_attr.type == MLX5_FLOW_DESTINATION_TYPE_PORT &&
	    --fte->dests_size) अणु
		fte->modअगरy_mask |= BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_ACTION);
		fte->action.action &= ~MLX5_FLOW_CONTEXT_ACTION_ALLOW;
		जाओ out;
	पूर्ण

	अगर ((fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) &&
	    --fte->dests_size) अणु
		fte->modअगरy_mask |=
			BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_DESTINATION_LIST);
	पूर्ण
out:
	kमुक्त(rule);
पूर्ण

अटल व्योम del_hw_fte(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *fg;
	काष्ठा mlx5_core_dev *dev;
	काष्ठा fs_fte *fte;
	पूर्णांक err;

	fs_get_obj(fte, node);
	fs_get_obj(fg, fte->node.parent);
	fs_get_obj(ft, fg->node.parent);

	trace_mlx5_fs_del_fte(fte);
	dev = get_dev(&ft->node);
	root = find_root(&ft->node);
	अगर (node->active) अणु
		err = root->cmds->delete_fte(root, ft, fte);
		अगर (err)
			mlx5_core_warn(dev,
				       "flow steering can't delete fte in index %d of flow group id %d\n",
				       fte->index, fg->id);
		node->active = false;
	पूर्ण
पूर्ण

अटल व्योम del_sw_fte(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_steering *steering = get_steering(node);
	काष्ठा mlx5_flow_group *fg;
	काष्ठा fs_fte *fte;
	पूर्णांक err;

	fs_get_obj(fte, node);
	fs_get_obj(fg, fte->node.parent);

	err = rhashtable_हटाओ_fast(&fg->ftes_hash,
				     &fte->hash,
				     rhash_fte);
	WARN_ON(err);
	ida_मुक्त(&fg->fte_allocator, fte->index - fg->start_index);
	kmem_cache_मुक्त(steering->ftes_cache, fte);
पूर्ण

अटल व्योम del_hw_flow_group(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	काष्ठा mlx5_flow_group *fg;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_core_dev *dev;

	fs_get_obj(fg, node);
	fs_get_obj(ft, fg->node.parent);
	dev = get_dev(&ft->node);
	trace_mlx5_fs_del_fg(fg);

	root = find_root(&ft->node);
	अगर (fg->node.active && root->cmds->destroy_flow_group(root, ft, fg))
		mlx5_core_warn(dev, "flow steering can't destroy fg %d of ft %d\n",
			       fg->id, ft->id);
पूर्ण

अटल व्योम del_sw_flow_group(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_steering *steering = get_steering(node);
	काष्ठा mlx5_flow_group *fg;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक err;

	fs_get_obj(fg, node);
	fs_get_obj(ft, fg->node.parent);

	rhashtable_destroy(&fg->ftes_hash);
	ida_destroy(&fg->fte_allocator);
	अगर (ft->स्वतःgroup.active &&
	    fg->max_ftes == ft->स्वतःgroup.group_size &&
	    fg->start_index < ft->स्वतःgroup.max_fte)
		ft->स्वतःgroup.num_groups--;
	err = rhltable_हटाओ(&ft->fgs_hash,
			      &fg->hash,
			      rhash_fg);
	WARN_ON(err);
	kmem_cache_मुक्त(steering->fgs_cache, fg);
पूर्ण

अटल पूर्णांक insert_fte(काष्ठा mlx5_flow_group *fg, काष्ठा fs_fte *fte)
अणु
	पूर्णांक index;
	पूर्णांक ret;

	index = ida_alloc_max(&fg->fte_allocator, fg->max_ftes - 1, GFP_KERNEL);
	अगर (index < 0)
		वापस index;

	fte->index = index + fg->start_index;
	ret = rhashtable_insert_fast(&fg->ftes_hash,
				     &fte->hash,
				     rhash_fte);
	अगर (ret)
		जाओ err_ida_हटाओ;

	tree_add_node(&fte->node, &fg->node);
	list_add_tail(&fte->node.list, &fg->node.children);
	वापस 0;

err_ida_हटाओ:
	ida_मुक्त(&fg->fte_allocator, index);
	वापस ret;
पूर्ण

अटल काष्ठा fs_fte *alloc_fte(काष्ठा mlx5_flow_table *ft,
				स्थिर काष्ठा mlx5_flow_spec *spec,
				काष्ठा mlx5_flow_act *flow_act)
अणु
	काष्ठा mlx5_flow_steering *steering = get_steering(&ft->node);
	काष्ठा fs_fte *fte;

	fte = kmem_cache_zalloc(steering->ftes_cache, GFP_KERNEL);
	अगर (!fte)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(fte->val, &spec->match_value, माप(fte->val));
	fte->node.type =  FS_TYPE_FLOW_ENTRY;
	fte->action = *flow_act;
	fte->flow_context = spec->flow_context;

	tree_init_node(&fte->node, del_hw_fte, del_sw_fte);

	वापस fte;
पूर्ण

अटल व्योम dealloc_flow_group(काष्ठा mlx5_flow_steering *steering,
			       काष्ठा mlx5_flow_group *fg)
अणु
	rhashtable_destroy(&fg->ftes_hash);
	kmem_cache_मुक्त(steering->fgs_cache, fg);
पूर्ण

अटल काष्ठा mlx5_flow_group *alloc_flow_group(काष्ठा mlx5_flow_steering *steering,
						u8 match_criteria_enable,
						स्थिर व्योम *match_criteria,
						पूर्णांक start_index,
						पूर्णांक end_index)
अणु
	काष्ठा mlx5_flow_group *fg;
	पूर्णांक ret;

	fg = kmem_cache_zalloc(steering->fgs_cache, GFP_KERNEL);
	अगर (!fg)
		वापस ERR_PTR(-ENOMEM);

	ret = rhashtable_init(&fg->ftes_hash, &rhash_fte);
	अगर (ret) अणु
		kmem_cache_मुक्त(steering->fgs_cache, fg);
		वापस ERR_PTR(ret);
	पूर्ण

	ida_init(&fg->fte_allocator);
	fg->mask.match_criteria_enable = match_criteria_enable;
	स_नकल(&fg->mask.match_criteria, match_criteria,
	       माप(fg->mask.match_criteria));
	fg->node.type =  FS_TYPE_FLOW_GROUP;
	fg->start_index = start_index;
	fg->max_ftes = end_index - start_index + 1;

	वापस fg;
पूर्ण

अटल काष्ठा mlx5_flow_group *alloc_insert_flow_group(काष्ठा mlx5_flow_table *ft,
						       u8 match_criteria_enable,
						       स्थिर व्योम *match_criteria,
						       पूर्णांक start_index,
						       पूर्णांक end_index,
						       काष्ठा list_head *prev)
अणु
	काष्ठा mlx5_flow_steering *steering = get_steering(&ft->node);
	काष्ठा mlx5_flow_group *fg;
	पूर्णांक ret;

	fg = alloc_flow_group(steering, match_criteria_enable, match_criteria,
			      start_index, end_index);
	अगर (IS_ERR(fg))
		वापस fg;

	/* initialize refcnt, add to parent list */
	ret = rhltable_insert(&ft->fgs_hash,
			      &fg->hash,
			      rhash_fg);
	अगर (ret) अणु
		dealloc_flow_group(steering, fg);
		वापस ERR_PTR(ret);
	पूर्ण

	tree_init_node(&fg->node, del_hw_flow_group, del_sw_flow_group);
	tree_add_node(&fg->node, &ft->node);
	/* Add node to group list */
	list_add(&fg->node.list, prev);
	atomic_inc(&ft->node.version);

	वापस fg;
पूर्ण

अटल काष्ठा mlx5_flow_table *alloc_flow_table(पूर्णांक level, u16 vport, पूर्णांक max_fte,
						क्रमागत fs_flow_table_type table_type,
						क्रमागत fs_flow_table_op_mod op_mod,
						u32 flags)
अणु
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक ret;

	ft  = kzalloc(माप(*ft), GFP_KERNEL);
	अगर (!ft)
		वापस ERR_PTR(-ENOMEM);

	ret = rhltable_init(&ft->fgs_hash, &rhash_fg);
	अगर (ret) अणु
		kमुक्त(ft);
		वापस ERR_PTR(ret);
	पूर्ण

	ft->level = level;
	ft->node.type = FS_TYPE_FLOW_TABLE;
	ft->op_mod = op_mod;
	ft->type = table_type;
	ft->vport = vport;
	ft->max_fte = max_fte;
	ft->flags = flags;
	INIT_LIST_HEAD(&ft->fwd_rules);
	mutex_init(&ft->lock);

	वापस ft;
पूर्ण

/* If reverse is false, then we search क्रम the first flow table in the
 * root sub-tree from start(बंदst from right), अन्यथा we search क्रम the
 * last flow table in the root sub-tree till start(बंदst from left).
 */
अटल काष्ठा mlx5_flow_table *find_बंदst_ft_recursive(काष्ठा fs_node  *root,
							 काष्ठा list_head *start,
							 bool reverse)
अणु
#घोषणा list_advance_entry(pos, reverse)		\
	((reverse) ? list_prev_entry(pos, list) : list_next_entry(pos, list))

#घोषणा list_क्रम_each_advance_जारी(pos, head, reverse)	\
	क्रम (pos = list_advance_entry(pos, reverse);		\
	     &pos->list != (head);				\
	     pos = list_advance_entry(pos, reverse))

	काष्ठा fs_node *iter = list_entry(start, काष्ठा fs_node, list);
	काष्ठा mlx5_flow_table *ft = शून्य;

	अगर (!root || root->type == FS_TYPE_PRIO_CHAINS)
		वापस शून्य;

	list_क्रम_each_advance_जारी(iter, &root->children, reverse) अणु
		अगर (iter->type == FS_TYPE_FLOW_TABLE) अणु
			fs_get_obj(ft, iter);
			वापस ft;
		पूर्ण
		ft = find_बंदst_ft_recursive(iter, &iter->children, reverse);
		अगर (ft)
			वापस ft;
	पूर्ण

	वापस ft;
पूर्ण

/* If reverse is false then वापस the first flow table in next priority of
 * prio in the tree, अन्यथा वापस the last flow table in the previous priority
 * of prio in the tree.
 */
अटल काष्ठा mlx5_flow_table *find_बंदst_ft(काष्ठा fs_prio *prio, bool reverse)
अणु
	काष्ठा mlx5_flow_table *ft = शून्य;
	काष्ठा fs_node *curr_node;
	काष्ठा fs_node *parent;

	parent = prio->node.parent;
	curr_node = &prio->node;
	जबतक (!ft && parent) अणु
		ft = find_बंदst_ft_recursive(parent, &curr_node->list, reverse);
		curr_node = parent;
		parent = curr_node->parent;
	पूर्ण
	वापस ft;
पूर्ण

/* Assuming all the tree is locked by mutex chain lock */
अटल काष्ठा mlx5_flow_table *find_next_chained_ft(काष्ठा fs_prio *prio)
अणु
	वापस find_बंदst_ft(prio, false);
पूर्ण

/* Assuming all the tree is locked by mutex chain lock */
अटल काष्ठा mlx5_flow_table *find_prev_chained_ft(काष्ठा fs_prio *prio)
अणु
	वापस find_बंदst_ft(prio, true);
पूर्ण

अटल काष्ठा mlx5_flow_table *find_next_fwd_ft(काष्ठा mlx5_flow_table *ft,
						काष्ठा mlx5_flow_act *flow_act)
अणु
	काष्ठा fs_prio *prio;
	bool next_ns;

	next_ns = flow_act->action & MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_NS;
	fs_get_obj(prio, next_ns ? ft->ns->node.parent : ft->node.parent);

	वापस find_next_chained_ft(prio);
पूर्ण

अटल पूर्णांक connect_fts_in_prio(काष्ठा mlx5_core_dev *dev,
			       काष्ठा fs_prio *prio,
			       काष्ठा mlx5_flow_table *ft)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&prio->node);
	काष्ठा mlx5_flow_table *iter;
	पूर्णांक err;

	fs_क्रम_each_ft(iter, prio) अणु
		err = root->cmds->modअगरy_flow_table(root, iter, ft);
		अगर (err) अणु
			mlx5_core_err(dev,
				      "Failed to modify flow table id %d, type %d, err %d\n",
				      iter->id, iter->type, err);
			/* The driver is out of sync with the FW */
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Connect flow tables from previous priority of prio to ft */
अटल पूर्णांक connect_prev_fts(काष्ठा mlx5_core_dev *dev,
			    काष्ठा mlx5_flow_table *ft,
			    काष्ठा fs_prio *prio)
अणु
	काष्ठा mlx5_flow_table *prev_ft;

	prev_ft = find_prev_chained_ft(prio);
	अगर (prev_ft) अणु
		काष्ठा fs_prio *prev_prio;

		fs_get_obj(prev_prio, prev_ft->node.parent);
		वापस connect_fts_in_prio(dev, prev_prio, ft);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक update_root_ft_create(काष्ठा mlx5_flow_table *ft, काष्ठा fs_prio
				 *prio)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&prio->node);
	काष्ठा mlx5_ft_underlay_qp *uqp;
	पूर्णांक min_level = पूर्णांक_उच्च;
	पूर्णांक err = 0;
	u32 qpn;

	अगर (root->root_ft)
		min_level = root->root_ft->level;

	अगर (ft->level >= min_level)
		वापस 0;

	अगर (list_empty(&root->underlay_qpns)) अणु
		/* Don't set any QPN (zero) in हाल QPN list is empty */
		qpn = 0;
		err = root->cmds->update_root_ft(root, ft, qpn, false);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(uqp, &root->underlay_qpns, list) अणु
			qpn = uqp->qpn;
			err = root->cmds->update_root_ft(root, ft,
							 qpn, false);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (err)
		mlx5_core_warn(root->dev,
			       "Update root flow table of id(%u) qpn(%d) failed\n",
			       ft->id, qpn);
	अन्यथा
		root->root_ft = ft;

	वापस err;
पूर्ण

अटल पूर्णांक _mlx5_modअगरy_rule_destination(काष्ठा mlx5_flow_rule *rule,
					 काष्ठा mlx5_flow_destination *dest)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *fg;
	काष्ठा fs_fte *fte;
	पूर्णांक modअगरy_mask = BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_DESTINATION_LIST);
	पूर्णांक err = 0;

	fs_get_obj(fte, rule->node.parent);
	अगर (!(fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST))
		वापस -EINVAL;
	करोwn_ग_लिखो_ref_node(&fte->node, false);
	fs_get_obj(fg, fte->node.parent);
	fs_get_obj(ft, fg->node.parent);

	स_नकल(&rule->dest_attr, dest, माप(*dest));
	root = find_root(&ft->node);
	err = root->cmds->update_fte(root, ft, fg,
				     modअगरy_mask, fte);
	up_ग_लिखो_ref_node(&fte->node, false);

	वापस err;
पूर्ण

पूर्णांक mlx5_modअगरy_rule_destination(काष्ठा mlx5_flow_handle *handle,
				 काष्ठा mlx5_flow_destination *new_dest,
				 काष्ठा mlx5_flow_destination *old_dest)
अणु
	पूर्णांक i;

	अगर (!old_dest) अणु
		अगर (handle->num_rules != 1)
			वापस -EINVAL;
		वापस _mlx5_modअगरy_rule_destination(handle->rule[0],
						     new_dest);
	पूर्ण

	क्रम (i = 0; i < handle->num_rules; i++) अणु
		अगर (mlx5_flow_dests_cmp(new_dest, &handle->rule[i]->dest_attr))
			वापस _mlx5_modअगरy_rule_destination(handle->rule[i],
							     new_dest);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Modअगरy/set FWD rules that poपूर्णांक on old_next_ft to poपूर्णांक on new_next_ft  */
अटल पूर्णांक connect_fwd_rules(काष्ठा mlx5_core_dev *dev,
			     काष्ठा mlx5_flow_table *new_next_ft,
			     काष्ठा mlx5_flow_table *old_next_ft)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_rule *iter;
	पूर्णांक err = 0;

	/* new_next_ft and old_next_ft could be शून्य only
	 * when we create/destroy the anchor flow table.
	 */
	अगर (!new_next_ft || !old_next_ft)
		वापस 0;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = new_next_ft;

	mutex_lock(&old_next_ft->lock);
	list_splice_init(&old_next_ft->fwd_rules, &new_next_ft->fwd_rules);
	mutex_unlock(&old_next_ft->lock);
	list_क्रम_each_entry(iter, &new_next_ft->fwd_rules, next_ft) अणु
		अगर ((iter->sw_action & MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_NS) &&
		    iter->ft->ns == new_next_ft->ns)
			जारी;

		err = _mlx5_modअगरy_rule_destination(iter, &dest);
		अगर (err)
			pr_err("mlx5_core: failed to modify rule to point on flow table %d\n",
			       new_next_ft->id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक connect_flow_table(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_flow_table *ft,
			      काष्ठा fs_prio *prio)
अणु
	काष्ठा mlx5_flow_table *next_ft;
	पूर्णांक err = 0;

	/* Connect_prev_fts and update_root_ft_create are mutually exclusive */

	अगर (list_empty(&prio->node.children)) अणु
		err = connect_prev_fts(dev, ft, prio);
		अगर (err)
			वापस err;

		next_ft = find_next_chained_ft(prio);
		err = connect_fwd_rules(dev, ft, next_ft);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MLX5_CAP_FLOWTABLE(dev,
			       flow_table_properties_nic_receive.modअगरy_root))
		err = update_root_ft_create(ft, prio);
	वापस err;
पूर्ण

अटल व्योम list_add_flow_table(काष्ठा mlx5_flow_table *ft,
				काष्ठा fs_prio *prio)
अणु
	काष्ठा list_head *prev = &prio->node.children;
	काष्ठा mlx5_flow_table *iter;

	fs_क्रम_each_ft(iter, prio) अणु
		अगर (iter->level > ft->level)
			अवरोध;
		prev = &iter->node.list;
	पूर्ण
	list_add(&ft->node.list, prev);
पूर्ण

अटल काष्ठा mlx5_flow_table *__mlx5_create_flow_table(काष्ठा mlx5_flow_namespace *ns,
							काष्ठा mlx5_flow_table_attr *ft_attr,
							क्रमागत fs_flow_table_op_mod op_mod,
							u16 vport)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&ns->node);
	bool unmanaged = ft_attr->flags & MLX5_FLOW_TABLE_UNMANAGED;
	काष्ठा mlx5_flow_table *next_ft;
	काष्ठा fs_prio *fs_prio = शून्य;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक log_table_sz;
	पूर्णांक err;

	अगर (!root) अणु
		pr_err("mlx5: flow steering failed to find root of namespace\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	mutex_lock(&root->chain_lock);
	fs_prio = find_prio(ns, ft_attr->prio);
	अगर (!fs_prio) अणु
		err = -EINVAL;
		जाओ unlock_root;
	पूर्ण
	अगर (!unmanaged) अणु
		/* The level is related to the
		 * priority level range.
		 */
		अगर (ft_attr->level >= fs_prio->num_levels) अणु
			err = -ENOSPC;
			जाओ unlock_root;
		पूर्ण

		ft_attr->level += fs_prio->start_level;
	पूर्ण

	/* The level is related to the
	 * priority level range.
	 */
	ft = alloc_flow_table(ft_attr->level,
			      vport,
			      ft_attr->max_fte ? roundup_घात_of_two(ft_attr->max_fte) : 0,
			      root->table_type,
			      op_mod, ft_attr->flags);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		जाओ unlock_root;
	पूर्ण

	tree_init_node(&ft->node, del_hw_flow_table, del_sw_flow_table);
	log_table_sz = ft->max_fte ? ilog2(ft->max_fte) : 0;
	next_ft = unmanaged ? ft_attr->next_ft :
			      find_next_chained_ft(fs_prio);
	ft->def_miss_action = ns->def_miss_action;
	ft->ns = ns;
	err = root->cmds->create_flow_table(root, ft, log_table_sz, next_ft);
	अगर (err)
		जाओ मुक्त_ft;

	अगर (!unmanaged) अणु
		err = connect_flow_table(root->dev, ft, fs_prio);
		अगर (err)
			जाओ destroy_ft;
	पूर्ण

	ft->node.active = true;
	करोwn_ग_लिखो_ref_node(&fs_prio->node, false);
	अगर (!unmanaged) अणु
		tree_add_node(&ft->node, &fs_prio->node);
		list_add_flow_table(ft, fs_prio);
	पूर्ण अन्यथा अणु
		ft->node.root = fs_prio->node.root;
	पूर्ण
	fs_prio->num_ft++;
	up_ग_लिखो_ref_node(&fs_prio->node, false);
	mutex_unlock(&root->chain_lock);
	trace_mlx5_fs_add_ft(ft);
	वापस ft;
destroy_ft:
	root->cmds->destroy_flow_table(root, ft);
मुक्त_ft:
	rhltable_destroy(&ft->fgs_hash);
	kमुक्त(ft);
unlock_root:
	mutex_unlock(&root->chain_lock);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा mlx5_flow_table *mlx5_create_flow_table(काष्ठा mlx5_flow_namespace *ns,
					       काष्ठा mlx5_flow_table_attr *ft_attr)
अणु
	वापस __mlx5_create_flow_table(ns, ft_attr, FS_FT_OP_MOD_NORMAL, 0);
पूर्ण
EXPORT_SYMBOL(mlx5_create_flow_table);

काष्ठा mlx5_flow_table *
mlx5_create_vport_flow_table(काष्ठा mlx5_flow_namespace *ns,
			     काष्ठा mlx5_flow_table_attr *ft_attr, u16 vport)
अणु
	वापस __mlx5_create_flow_table(ns, ft_attr, FS_FT_OP_MOD_NORMAL, vport);
पूर्ण

काष्ठा mlx5_flow_table*
mlx5_create_lag_demux_flow_table(काष्ठा mlx5_flow_namespace *ns,
				 पूर्णांक prio, u32 level)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;

	ft_attr.level = level;
	ft_attr.prio  = prio;
	वापस __mlx5_create_flow_table(ns, &ft_attr, FS_FT_OP_MOD_LAG_DEMUX, 0);
पूर्ण
EXPORT_SYMBOL(mlx5_create_lag_demux_flow_table);

काष्ठा mlx5_flow_table*
mlx5_create_स्वतः_grouped_flow_table(काष्ठा mlx5_flow_namespace *ns,
				    काष्ठा mlx5_flow_table_attr *ft_attr)
अणु
	पूर्णांक num_reserved_entries = ft_attr->स्वतःgroup.num_reserved_entries;
	पूर्णांक स्वतःgroups_max_fte = ft_attr->max_fte - num_reserved_entries;
	पूर्णांक max_num_groups = ft_attr->स्वतःgroup.max_num_groups;
	काष्ठा mlx5_flow_table *ft;

	अगर (max_num_groups > स्वतःgroups_max_fte)
		वापस ERR_PTR(-EINVAL);
	अगर (num_reserved_entries > ft_attr->max_fte)
		वापस ERR_PTR(-EINVAL);

	ft = mlx5_create_flow_table(ns, ft_attr);
	अगर (IS_ERR(ft))
		वापस ft;

	ft->स्वतःgroup.active = true;
	ft->स्वतःgroup.required_groups = max_num_groups;
	ft->स्वतःgroup.max_fte = स्वतःgroups_max_fte;
	/* We save place क्रम flow groups in addition to max types */
	ft->स्वतःgroup.group_size = स्वतःgroups_max_fte / (max_num_groups + 1);

	वापस ft;
पूर्ण
EXPORT_SYMBOL(mlx5_create_स्वतः_grouped_flow_table);

काष्ठा mlx5_flow_group *mlx5_create_flow_group(काष्ठा mlx5_flow_table *ft,
					       u32 *fg_in)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&ft->node);
	व्योम *match_criteria = MLX5_ADDR_OF(create_flow_group_in,
					    fg_in, match_criteria);
	u8 match_criteria_enable = MLX5_GET(create_flow_group_in,
					    fg_in,
					    match_criteria_enable);
	पूर्णांक start_index = MLX5_GET(create_flow_group_in, fg_in,
				   start_flow_index);
	पूर्णांक end_index = MLX5_GET(create_flow_group_in, fg_in,
				 end_flow_index);
	काष्ठा mlx5_flow_group *fg;
	पूर्णांक err;

	अगर (ft->स्वतःgroup.active && start_index < ft->स्वतःgroup.max_fte)
		वापस ERR_PTR(-EPERM);

	करोwn_ग_लिखो_ref_node(&ft->node, false);
	fg = alloc_insert_flow_group(ft, match_criteria_enable, match_criteria,
				     start_index, end_index,
				     ft->node.children.prev);
	up_ग_लिखो_ref_node(&ft->node, false);
	अगर (IS_ERR(fg))
		वापस fg;

	err = root->cmds->create_flow_group(root, ft, fg_in, fg);
	अगर (err) अणु
		tree_put_node(&fg->node, false);
		वापस ERR_PTR(err);
	पूर्ण
	trace_mlx5_fs_add_fg(fg);
	fg->node.active = true;

	वापस fg;
पूर्ण
EXPORT_SYMBOL(mlx5_create_flow_group);

अटल काष्ठा mlx5_flow_rule *alloc_rule(काष्ठा mlx5_flow_destination *dest)
अणु
	काष्ठा mlx5_flow_rule *rule;

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule)
		वापस शून्य;

	INIT_LIST_HEAD(&rule->next_ft);
	rule->node.type = FS_TYPE_FLOW_DEST;
	अगर (dest)
		स_नकल(&rule->dest_attr, dest, माप(*dest));

	वापस rule;
पूर्ण

अटल काष्ठा mlx5_flow_handle *alloc_handle(पूर्णांक num_rules)
अणु
	काष्ठा mlx5_flow_handle *handle;

	handle = kzalloc(काष्ठा_size(handle, rule, num_rules), GFP_KERNEL);
	अगर (!handle)
		वापस शून्य;

	handle->num_rules = num_rules;

	वापस handle;
पूर्ण

अटल व्योम destroy_flow_handle(काष्ठा fs_fte *fte,
				काष्ठा mlx5_flow_handle *handle,
				काष्ठा mlx5_flow_destination *dest,
				पूर्णांक i)
अणु
	क्रम (; --i >= 0;) अणु
		अगर (refcount_dec_and_test(&handle->rule[i]->node.refcount)) अणु
			fte->dests_size--;
			list_del(&handle->rule[i]->node.list);
			kमुक्त(handle->rule[i]);
		पूर्ण
	पूर्ण
	kमुक्त(handle);
पूर्ण

अटल काष्ठा mlx5_flow_handle *
create_flow_handle(काष्ठा fs_fte *fte,
		   काष्ठा mlx5_flow_destination *dest,
		   पूर्णांक dest_num,
		   पूर्णांक *modअगरy_mask,
		   bool *new_rule)
अणु
	काष्ठा mlx5_flow_handle *handle;
	काष्ठा mlx5_flow_rule *rule = शून्य;
	अटल पूर्णांक count = BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_FLOW_COUNTERS);
	अटल पूर्णांक dst = BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_DESTINATION_LIST);
	पूर्णांक type;
	पूर्णांक i = 0;

	handle = alloc_handle((dest_num) ? dest_num : 1);
	अगर (!handle)
		वापस ERR_PTR(-ENOMEM);

	करो अणु
		अगर (dest) अणु
			rule = find_flow_rule(fte, dest + i);
			अगर (rule) अणु
				refcount_inc(&rule->node.refcount);
				जाओ rule_found;
			पूर्ण
		पूर्ण

		*new_rule = true;
		rule = alloc_rule(dest + i);
		अगर (!rule)
			जाओ मुक्त_rules;

		/* Add dest to dests list- we need flow tables to be in the
		 * end of the list क्रम क्रमward to next prio rules.
		 */
		tree_init_node(&rule->node, शून्य, del_sw_hw_rule);
		अगर (dest &&
		    dest[i].type != MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE)
			list_add(&rule->node.list, &fte->node.children);
		अन्यथा
			list_add_tail(&rule->node.list, &fte->node.children);
		अगर (dest) अणु
			fte->dests_size++;

			type = dest[i].type ==
				MLX5_FLOW_DESTINATION_TYPE_COUNTER;
			*modअगरy_mask |= type ? count : dst;
		पूर्ण
rule_found:
		handle->rule[i] = rule;
	पूर्ण जबतक (++i < dest_num);

	वापस handle;

मुक्त_rules:
	destroy_flow_handle(fte, handle, dest, i);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/* fte should not be deleted जबतक calling this function */
अटल काष्ठा mlx5_flow_handle *
add_rule_fte(काष्ठा fs_fte *fte,
	     काष्ठा mlx5_flow_group *fg,
	     काष्ठा mlx5_flow_destination *dest,
	     पूर्णांक dest_num,
	     bool update_action)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	काष्ठा mlx5_flow_handle *handle;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक modअगरy_mask = 0;
	पूर्णांक err;
	bool new_rule = false;

	handle = create_flow_handle(fte, dest, dest_num, &modअगरy_mask,
				    &new_rule);
	अगर (IS_ERR(handle) || !new_rule)
		जाओ out;

	अगर (update_action)
		modअगरy_mask |= BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_ACTION);

	fs_get_obj(ft, fg->node.parent);
	root = find_root(&fg->node);
	अगर (!(fte->status & FS_FTE_STATUS_EXISTING))
		err = root->cmds->create_fte(root, ft, fg, fte);
	अन्यथा
		err = root->cmds->update_fte(root, ft, fg, modअगरy_mask, fte);
	अगर (err)
		जाओ मुक्त_handle;

	fte->node.active = true;
	fte->status |= FS_FTE_STATUS_EXISTING;
	atomic_inc(&fg->node.version);

out:
	वापस handle;

मुक्त_handle:
	destroy_flow_handle(fte, handle, dest, handle->num_rules);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा mlx5_flow_group *alloc_स्वतः_flow_group(काष्ठा mlx5_flow_table  *ft,
						     स्थिर काष्ठा mlx5_flow_spec *spec)
अणु
	काष्ठा list_head *prev = &ft->node.children;
	u32 max_fte = ft->स्वतःgroup.max_fte;
	अचिन्हित पूर्णांक candidate_index = 0;
	अचिन्हित पूर्णांक group_size = 0;
	काष्ठा mlx5_flow_group *fg;

	अगर (!ft->स्वतःgroup.active)
		वापस ERR_PTR(-ENOENT);

	अगर (ft->स्वतःgroup.num_groups < ft->स्वतःgroup.required_groups)
		group_size = ft->स्वतःgroup.group_size;

	/*  max_fte == ft->स्वतःgroup.max_types */
	अगर (group_size == 0)
		group_size = 1;

	/* sorted by start_index */
	fs_क्रम_each_fg(fg, ft) अणु
		अगर (candidate_index + group_size > fg->start_index)
			candidate_index = fg->start_index + fg->max_ftes;
		अन्यथा
			अवरोध;
		prev = &fg->node.list;
	पूर्ण

	अगर (candidate_index + group_size > max_fte)
		वापस ERR_PTR(-ENOSPC);

	fg = alloc_insert_flow_group(ft,
				     spec->match_criteria_enable,
				     spec->match_criteria,
				     candidate_index,
				     candidate_index + group_size - 1,
				     prev);
	अगर (IS_ERR(fg))
		जाओ out;

	अगर (group_size == ft->स्वतःgroup.group_size)
		ft->स्वतःgroup.num_groups++;

out:
	वापस fg;
पूर्ण

अटल पूर्णांक create_स्वतः_flow_group(काष्ठा mlx5_flow_table *ft,
				  काष्ठा mlx5_flow_group *fg)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&ft->node);
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	व्योम *match_criteria_addr;
	u8 src_esw_owner_mask_on;
	व्योम *misc;
	पूर्णांक err;
	u32 *in;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_flow_group_in, in, match_criteria_enable,
		 fg->mask.match_criteria_enable);
	MLX5_SET(create_flow_group_in, in, start_flow_index, fg->start_index);
	MLX5_SET(create_flow_group_in, in, end_flow_index,   fg->start_index +
		 fg->max_ftes - 1);

	misc = MLX5_ADDR_OF(fte_match_param, fg->mask.match_criteria,
			    misc_parameters);
	src_esw_owner_mask_on = !!MLX5_GET(fte_match_set_misc, misc,
					 source_eचयन_owner_vhca_id);
	MLX5_SET(create_flow_group_in, in,
		 source_eचयन_owner_vhca_id_valid, src_esw_owner_mask_on);

	match_criteria_addr = MLX5_ADDR_OF(create_flow_group_in,
					   in, match_criteria);
	स_नकल(match_criteria_addr, fg->mask.match_criteria,
	       माप(fg->mask.match_criteria));

	err = root->cmds->create_flow_group(root, ft, in, fg);
	अगर (!err) अणु
		fg->node.active = true;
		trace_mlx5_fs_add_fg(fg);
	पूर्ण

	kvमुक्त(in);
	वापस err;
पूर्ण

अटल bool mlx5_flow_dests_cmp(काष्ठा mlx5_flow_destination *d1,
				काष्ठा mlx5_flow_destination *d2)
अणु
	अगर (d1->type == d2->type) अणु
		अगर ((d1->type == MLX5_FLOW_DESTINATION_TYPE_VPORT &&
		     d1->vport.num == d2->vport.num &&
		     d1->vport.flags == d2->vport.flags &&
		     ((d1->vport.flags & MLX5_FLOW_DEST_VPORT_VHCA_ID) ?
		      (d1->vport.vhca_id == d2->vport.vhca_id) : true) &&
		     ((d1->vport.flags & MLX5_FLOW_DEST_VPORT_REFORMAT_ID) ?
		      (d1->vport.pkt_reक्रमmat->id ==
		       d2->vport.pkt_reक्रमmat->id) : true)) ||
		    (d1->type == MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE &&
		     d1->ft == d2->ft) ||
		    (d1->type == MLX5_FLOW_DESTINATION_TYPE_TIR &&
		     d1->tir_num == d2->tir_num) ||
		    (d1->type == MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM &&
		     d1->ft_num == d2->ft_num))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा mlx5_flow_rule *find_flow_rule(काष्ठा fs_fte *fte,
					     काष्ठा mlx5_flow_destination *dest)
अणु
	काष्ठा mlx5_flow_rule *rule;

	list_क्रम_each_entry(rule, &fte->node.children, node.list) अणु
		अगर (mlx5_flow_dests_cmp(&rule->dest_attr, dest))
			वापस rule;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool check_conflicting_actions(u32 action1, u32 action2)
अणु
	u32 xored_actions = action1 ^ action2;

	/* अगर one rule only wants to count, it's ok */
	अगर (action1 == MLX5_FLOW_CONTEXT_ACTION_COUNT ||
	    action2 == MLX5_FLOW_CONTEXT_ACTION_COUNT)
		वापस false;

	अगर (xored_actions & (MLX5_FLOW_CONTEXT_ACTION_DROP  |
			     MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT |
			     MLX5_FLOW_CONTEXT_ACTION_DECAP |
			     MLX5_FLOW_CONTEXT_ACTION_MOD_HDR  |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_POP |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2 |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक check_conflicting_ftes(काष्ठा fs_fte *fte,
				  स्थिर काष्ठा mlx5_flow_context *flow_context,
				  स्थिर काष्ठा mlx5_flow_act *flow_act)
अणु
	अगर (check_conflicting_actions(flow_act->action, fte->action.action)) अणु
		mlx5_core_warn(get_dev(&fte->node),
			       "Found two FTEs with conflicting actions\n");
		वापस -EEXIST;
	पूर्ण

	अगर ((flow_context->flags & FLOW_CONTEXT_HAS_TAG) &&
	    fte->flow_context.flow_tag != flow_context->flow_tag) अणु
		mlx5_core_warn(get_dev(&fte->node),
			       "FTE flow tag %u already exists with different flow tag %u\n",
			       fte->flow_context.flow_tag,
			       flow_context->flow_tag);
		वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mlx5_flow_handle *add_rule_fg(काष्ठा mlx5_flow_group *fg,
					    स्थिर काष्ठा mlx5_flow_spec *spec,
					    काष्ठा mlx5_flow_act *flow_act,
					    काष्ठा mlx5_flow_destination *dest,
					    पूर्णांक dest_num,
					    काष्ठा fs_fte *fte)
अणु
	काष्ठा mlx5_flow_handle *handle;
	पूर्णांक old_action;
	पूर्णांक i;
	पूर्णांक ret;

	ret = check_conflicting_ftes(fte, &spec->flow_context, flow_act);
	अगर (ret)
		वापस ERR_PTR(ret);

	old_action = fte->action.action;
	fte->action.action |= flow_act->action;
	handle = add_rule_fte(fte, fg, dest, dest_num,
			      old_action != flow_act->action);
	अगर (IS_ERR(handle)) अणु
		fte->action.action = old_action;
		वापस handle;
	पूर्ण
	trace_mlx5_fs_set_fte(fte, false);

	क्रम (i = 0; i < handle->num_rules; i++) अणु
		अगर (refcount_पढ़ो(&handle->rule[i]->node.refcount) == 1) अणु
			tree_add_node(&handle->rule[i]->node, &fte->node);
			trace_mlx5_fs_add_rule(handle->rule[i]);
		पूर्ण
	पूर्ण
	वापस handle;
पूर्ण

अटल bool counter_is_valid(u32 action)
अणु
	वापस (action & (MLX5_FLOW_CONTEXT_ACTION_DROP |
			  MLX5_FLOW_CONTEXT_ACTION_ALLOW |
			  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST));
पूर्ण

अटल bool dest_is_valid(काष्ठा mlx5_flow_destination *dest,
			  काष्ठा mlx5_flow_act *flow_act,
			  काष्ठा mlx5_flow_table *ft)
अणु
	bool ignore_level = flow_act->flags & FLOW_ACT_IGNORE_FLOW_LEVEL;
	u32 action = flow_act->action;

	अगर (dest && (dest->type == MLX5_FLOW_DESTINATION_TYPE_COUNTER))
		वापस counter_is_valid(action);

	अगर (!(action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST))
		वापस true;

	अगर (ignore_level) अणु
		अगर (ft->type != FS_FT_FDB &&
		    ft->type != FS_FT_NIC_RX)
			वापस false;

		अगर (dest->type == MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE &&
		    ft->type != dest->ft->type)
			वापस false;
	पूर्ण

	अगर (!dest || ((dest->type ==
	    MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE) &&
	    (dest->ft->level <= ft->level && !ignore_level)))
		वापस false;
	वापस true;
पूर्ण

काष्ठा match_list अणु
	काष्ठा list_head	list;
	काष्ठा mlx5_flow_group *g;
पूर्ण;

अटल व्योम मुक्त_match_list(काष्ठा match_list *head, bool ft_locked)
अणु
	काष्ठा match_list *iter, *match_पंचांगp;

	list_क्रम_each_entry_safe(iter, match_पंचांगp, &head->list,
				 list) अणु
		tree_put_node(&iter->g->node, ft_locked);
		list_del(&iter->list);
		kमुक्त(iter);
	पूर्ण
पूर्ण

अटल पूर्णांक build_match_list(काष्ठा match_list *match_head,
			    काष्ठा mlx5_flow_table *ft,
			    स्थिर काष्ठा mlx5_flow_spec *spec,
			    bool ft_locked)
अणु
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा mlx5_flow_group *g;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	INIT_LIST_HEAD(&match_head->list);
	/* Collect all fgs which has a matching match_criteria */
	list = rhltable_lookup(&ft->fgs_hash, spec, rhash_fg);
	/* RCU is atomic, we can't execute FW commands here */
	rhl_क्रम_each_entry_rcu(g, पंचांगp, list, hash) अणु
		काष्ठा match_list *curr_match;

		अगर (unlikely(!tree_get_node(&g->node)))
			जारी;

		curr_match = kदो_स्मृति(माप(*curr_match), GFP_ATOMIC);
		अगर (!curr_match) अणु
			मुक्त_match_list(match_head, ft_locked);
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		curr_match->g = g;
		list_add_tail(&curr_match->list, &match_head->list);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल u64 matched_fgs_get_version(काष्ठा list_head *match_head)
अणु
	काष्ठा match_list *iter;
	u64 version = 0;

	list_क्रम_each_entry(iter, match_head, list)
		version += (u64)atomic_पढ़ो(&iter->g->node.version);
	वापस version;
पूर्ण

अटल काष्ठा fs_fte *
lookup_fte_locked(काष्ठा mlx5_flow_group *g,
		  स्थिर u32 *match_value,
		  bool take_ग_लिखो)
अणु
	काष्ठा fs_fte *fte_पंचांगp;

	अगर (take_ग_लिखो)
		nested_करोwn_ग_लिखो_ref_node(&g->node, FS_LOCK_PARENT);
	अन्यथा
		nested_करोwn_पढ़ो_ref_node(&g->node, FS_LOCK_PARENT);
	fte_पंचांगp = rhashtable_lookup_fast(&g->ftes_hash, match_value,
					 rhash_fte);
	अगर (!fte_पंचांगp || !tree_get_node(&fte_पंचांगp->node)) अणु
		fte_पंचांगp = शून्य;
		जाओ out;
	पूर्ण
	अगर (!fte_पंचांगp->node.active) अणु
		tree_put_node(&fte_पंचांगp->node, false);
		fte_पंचांगp = शून्य;
		जाओ out;
	पूर्ण

	nested_करोwn_ग_लिखो_ref_node(&fte_पंचांगp->node, FS_LOCK_CHILD);
out:
	अगर (take_ग_लिखो)
		up_ग_लिखो_ref_node(&g->node, false);
	अन्यथा
		up_पढ़ो_ref_node(&g->node);
	वापस fte_पंचांगp;
पूर्ण

अटल काष्ठा mlx5_flow_handle *
try_add_to_existing_fg(काष्ठा mlx5_flow_table *ft,
		       काष्ठा list_head *match_head,
		       स्थिर काष्ठा mlx5_flow_spec *spec,
		       काष्ठा mlx5_flow_act *flow_act,
		       काष्ठा mlx5_flow_destination *dest,
		       पूर्णांक dest_num,
		       पूर्णांक ft_version)
अणु
	काष्ठा mlx5_flow_steering *steering = get_steering(&ft->node);
	काष्ठा mlx5_flow_group *g;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा match_list *iter;
	bool take_ग_लिखो = false;
	काष्ठा fs_fte *fte;
	u64  version = 0;
	पूर्णांक err;

	fte = alloc_fte(ft, spec, flow_act);
	अगर (IS_ERR(fte))
		वापस  ERR_PTR(-ENOMEM);

search_again_locked:
	अगर (flow_act->flags & FLOW_ACT_NO_APPEND)
		जाओ skip_search;
	version = matched_fgs_get_version(match_head);
	/* Try to find an fte with identical match value and attempt update its
	 * action.
	 */
	list_क्रम_each_entry(iter, match_head, list) अणु
		काष्ठा fs_fte *fte_पंचांगp;

		g = iter->g;
		fte_पंचांगp = lookup_fte_locked(g, spec->match_value, take_ग_लिखो);
		अगर (!fte_पंचांगp)
			जारी;
		rule = add_rule_fg(g, spec, flow_act, dest, dest_num, fte_पंचांगp);
		/* No error check needed here, because insert_fte() is not called */
		up_ग_लिखो_ref_node(&fte_पंचांगp->node, false);
		tree_put_node(&fte_पंचांगp->node, false);
		kmem_cache_मुक्त(steering->ftes_cache, fte);
		वापस rule;
	पूर्ण

skip_search:
	/* No group with matching fte found, or we skipped the search.
	 * Try to add a new fte to any matching fg.
	 */

	/* Check the ft version, क्रम हाल that new flow group
	 * was added जबतक the fgs weren't locked
	 */
	अगर (atomic_पढ़ो(&ft->node.version) != ft_version) अणु
		rule = ERR_PTR(-EAGAIN);
		जाओ out;
	पूर्ण

	/* Check the fgs version. If version have changed it could be that an
	 * FTE with the same match value was added जबतक the fgs weren't
	 * locked.
	 */
	अगर (!(flow_act->flags & FLOW_ACT_NO_APPEND) &&
	    version != matched_fgs_get_version(match_head)) अणु
		take_ग_लिखो = true;
		जाओ search_again_locked;
	पूर्ण

	list_क्रम_each_entry(iter, match_head, list) अणु
		g = iter->g;

		nested_करोwn_ग_लिखो_ref_node(&g->node, FS_LOCK_PARENT);

		अगर (!g->node.active) अणु
			up_ग_लिखो_ref_node(&g->node, false);
			जारी;
		पूर्ण

		err = insert_fte(g, fte);
		अगर (err) अणु
			up_ग_लिखो_ref_node(&g->node, false);
			अगर (err == -ENOSPC)
				जारी;
			kmem_cache_मुक्त(steering->ftes_cache, fte);
			वापस ERR_PTR(err);
		पूर्ण

		nested_करोwn_ग_लिखो_ref_node(&fte->node, FS_LOCK_CHILD);
		up_ग_लिखो_ref_node(&g->node, false);
		rule = add_rule_fg(g, spec, flow_act, dest, dest_num, fte);
		up_ग_लिखो_ref_node(&fte->node, false);
		अगर (IS_ERR(rule))
			tree_put_node(&fte->node, false);
		वापस rule;
	पूर्ण
	rule = ERR_PTR(-ENOENT);
out:
	kmem_cache_मुक्त(steering->ftes_cache, fte);
	वापस rule;
पूर्ण

अटल काष्ठा mlx5_flow_handle *
_mlx5_add_flow_rules(काष्ठा mlx5_flow_table *ft,
		     स्थिर काष्ठा mlx5_flow_spec *spec,
		     काष्ठा mlx5_flow_act *flow_act,
		     काष्ठा mlx5_flow_destination *dest,
		     पूर्णांक dest_num)

अणु
	काष्ठा mlx5_flow_steering *steering = get_steering(&ft->node);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा match_list match_head;
	काष्ठा mlx5_flow_group *g;
	bool take_ग_लिखो = false;
	काष्ठा fs_fte *fte;
	पूर्णांक version;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!check_valid_spec(spec))
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < dest_num; i++) अणु
		अगर (!dest_is_valid(&dest[i], flow_act, ft))
			वापस ERR_PTR(-EINVAL);
	पूर्ण
	nested_करोwn_पढ़ो_ref_node(&ft->node, FS_LOCK_GRANDPARENT);
search_again_locked:
	version = atomic_पढ़ो(&ft->node.version);

	/* Collect all fgs which has a matching match_criteria */
	err = build_match_list(&match_head, ft, spec, take_ग_लिखो);
	अगर (err) अणु
		अगर (take_ग_लिखो)
			up_ग_लिखो_ref_node(&ft->node, false);
		अन्यथा
			up_पढ़ो_ref_node(&ft->node);
		वापस ERR_PTR(err);
	पूर्ण

	अगर (!take_ग_लिखो)
		up_पढ़ो_ref_node(&ft->node);

	rule = try_add_to_existing_fg(ft, &match_head.list, spec, flow_act, dest,
				      dest_num, version);
	मुक्त_match_list(&match_head, take_ग_लिखो);
	अगर (!IS_ERR(rule) ||
	    (PTR_ERR(rule) != -ENOENT && PTR_ERR(rule) != -EAGAIN)) अणु
		अगर (take_ग_लिखो)
			up_ग_लिखो_ref_node(&ft->node, false);
		वापस rule;
	पूर्ण

	अगर (!take_ग_लिखो) अणु
		nested_करोwn_ग_लिखो_ref_node(&ft->node, FS_LOCK_GRANDPARENT);
		take_ग_लिखो = true;
	पूर्ण

	अगर (PTR_ERR(rule) == -EAGAIN ||
	    version != atomic_पढ़ो(&ft->node.version))
		जाओ search_again_locked;

	g = alloc_स्वतः_flow_group(ft, spec);
	अगर (IS_ERR(g)) अणु
		rule = ERR_CAST(g);
		up_ग_लिखो_ref_node(&ft->node, false);
		वापस rule;
	पूर्ण

	fte = alloc_fte(ft, spec, flow_act);
	अगर (IS_ERR(fte)) अणु
		up_ग_लिखो_ref_node(&ft->node, false);
		err = PTR_ERR(fte);
		जाओ err_alloc_fte;
	पूर्ण

	nested_करोwn_ग_लिखो_ref_node(&g->node, FS_LOCK_PARENT);
	up_ग_लिखो_ref_node(&ft->node, false);

	err = create_स्वतः_flow_group(ft, g);
	अगर (err)
		जाओ err_release_fg;

	err = insert_fte(g, fte);
	अगर (err)
		जाओ err_release_fg;

	nested_करोwn_ग_लिखो_ref_node(&fte->node, FS_LOCK_CHILD);
	up_ग_लिखो_ref_node(&g->node, false);
	rule = add_rule_fg(g, spec, flow_act, dest, dest_num, fte);
	up_ग_लिखो_ref_node(&fte->node, false);
	अगर (IS_ERR(rule))
		tree_put_node(&fte->node, false);
	tree_put_node(&g->node, false);
	वापस rule;

err_release_fg:
	up_ग_लिखो_ref_node(&g->node, false);
	kmem_cache_मुक्त(steering->ftes_cache, fte);
err_alloc_fte:
	tree_put_node(&g->node, false);
	वापस ERR_PTR(err);
पूर्ण

अटल bool fwd_next_prio_supported(काष्ठा mlx5_flow_table *ft)
अणु
	वापस ((ft->type == FS_FT_NIC_RX) &&
		(MLX5_CAP_FLOWTABLE(get_dev(&ft->node), nic_rx_multi_path_tirs)));
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5_add_flow_rules(काष्ठा mlx5_flow_table *ft,
		    स्थिर काष्ठा mlx5_flow_spec *spec,
		    काष्ठा mlx5_flow_act *flow_act,
		    काष्ठा mlx5_flow_destination *dest,
		    पूर्णांक num_dest)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&ft->node);
	अटल स्थिर काष्ठा mlx5_flow_spec zero_spec = अणुपूर्ण;
	काष्ठा mlx5_flow_destination *gen_dest = शून्य;
	काष्ठा mlx5_flow_table *next_ft = शून्य;
	काष्ठा mlx5_flow_handle *handle = शून्य;
	u32 sw_action = flow_act->action;
	पूर्णांक i;

	अगर (!spec)
		spec = &zero_spec;

	अगर (!is_fwd_next_action(sw_action))
		वापस _mlx5_add_flow_rules(ft, spec, flow_act, dest, num_dest);

	अगर (!fwd_next_prio_supported(ft))
		वापस ERR_PTR(-EOPNOTSUPP);

	mutex_lock(&root->chain_lock);
	next_ft = find_next_fwd_ft(ft, flow_act);
	अगर (!next_ft) अणु
		handle = ERR_PTR(-EOPNOTSUPP);
		जाओ unlock;
	पूर्ण

	gen_dest = kसुस्मृति(num_dest + 1, माप(*dest),
			   GFP_KERNEL);
	अगर (!gen_dest) अणु
		handle = ERR_PTR(-ENOMEM);
		जाओ unlock;
	पूर्ण
	क्रम (i = 0; i < num_dest; i++)
		gen_dest[i] = dest[i];
	gen_dest[i].type =
		MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	gen_dest[i].ft = next_ft;
	dest = gen_dest;
	num_dest++;
	flow_act->action &= ~(MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO |
			      MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_NS);
	flow_act->action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	handle = _mlx5_add_flow_rules(ft, spec, flow_act, dest, num_dest);
	अगर (IS_ERR(handle))
		जाओ unlock;

	अगर (list_empty(&handle->rule[num_dest - 1]->next_ft)) अणु
		mutex_lock(&next_ft->lock);
		list_add(&handle->rule[num_dest - 1]->next_ft,
			 &next_ft->fwd_rules);
		mutex_unlock(&next_ft->lock);
		handle->rule[num_dest - 1]->sw_action = sw_action;
		handle->rule[num_dest - 1]->ft = ft;
	पूर्ण
unlock:
	mutex_unlock(&root->chain_lock);
	kमुक्त(gen_dest);
	वापस handle;
पूर्ण
EXPORT_SYMBOL(mlx5_add_flow_rules);

व्योम mlx5_del_flow_rules(काष्ठा mlx5_flow_handle *handle)
अणु
	काष्ठा fs_fte *fte;
	पूर्णांक i;

	/* In order to consolidate the HW changes we lock the FTE क्रम other
	 * changes, and increase its refcount, in order not to perक्रमm the
	 * "del" functions of the FTE. Will handle them here.
	 * The removal of the rules is करोne under locked FTE.
	 * After removing all the handle's rules, अगर there are reमुख्यing
	 * rules, it means we just need to modअगरy the FTE in FW, and
	 * unlock/decrease the refcount we increased beक्रमe.
	 * Otherwise, it means the FTE should be deleted. First delete the
	 * FTE in FW. Then, unlock the FTE, and proceed the tree_put_node of
	 * the FTE, which will handle the last decrease of the refcount, as
	 * well as required handling of its parent.
	 */
	fs_get_obj(fte, handle->rule[0]->node.parent);
	करोwn_ग_लिखो_ref_node(&fte->node, false);
	क्रम (i = handle->num_rules - 1; i >= 0; i--)
		tree_हटाओ_node(&handle->rule[i]->node, true);
	अगर (fte->dests_size) अणु
		अगर (fte->modअगरy_mask)
			modअगरy_fte(fte);
		up_ग_लिखो_ref_node(&fte->node, false);
	पूर्ण अन्यथा अगर (list_empty(&fte->node.children)) अणु
		del_hw_fte(&fte->node);
		/* Aव्योम द्विगुन call to del_hw_fte */
		fte->node.del_hw_func = शून्य;
		up_ग_लिखो_ref_node(&fte->node, false);
		tree_put_node(&fte->node, false);
	पूर्ण
	kमुक्त(handle);
पूर्ण
EXPORT_SYMBOL(mlx5_del_flow_rules);

/* Assuming prio->node.children(flow tables) is sorted by level */
अटल काष्ठा mlx5_flow_table *find_next_ft(काष्ठा mlx5_flow_table *ft)
अणु
	काष्ठा fs_prio *prio;

	fs_get_obj(prio, ft->node.parent);

	अगर (!list_is_last(&ft->node.list, &prio->node.children))
		वापस list_next_entry(ft, node.list);
	वापस find_next_chained_ft(prio);
पूर्ण

अटल पूर्णांक update_root_ft_destroy(काष्ठा mlx5_flow_table *ft)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&ft->node);
	काष्ठा mlx5_ft_underlay_qp *uqp;
	काष्ठा mlx5_flow_table *new_root_ft = शून्य;
	पूर्णांक err = 0;
	u32 qpn;

	अगर (root->root_ft != ft)
		वापस 0;

	new_root_ft = find_next_ft(ft);
	अगर (!new_root_ft) अणु
		root->root_ft = शून्य;
		वापस 0;
	पूर्ण

	अगर (list_empty(&root->underlay_qpns)) अणु
		/* Don't set any QPN (zero) in हाल QPN list is empty */
		qpn = 0;
		err = root->cmds->update_root_ft(root, new_root_ft,
						 qpn, false);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(uqp, &root->underlay_qpns, list) अणु
			qpn = uqp->qpn;
			err = root->cmds->update_root_ft(root,
							 new_root_ft, qpn,
							 false);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (err)
		mlx5_core_warn(root->dev,
			       "Update root flow table of id(%u) qpn(%d) failed\n",
			       ft->id, qpn);
	अन्यथा
		root->root_ft = new_root_ft;

	वापस 0;
पूर्ण

/* Connect flow table from previous priority to
 * the next flow table.
 */
अटल पूर्णांक disconnect_flow_table(काष्ठा mlx5_flow_table *ft)
अणु
	काष्ठा mlx5_core_dev *dev = get_dev(&ft->node);
	काष्ठा mlx5_flow_table *next_ft;
	काष्ठा fs_prio *prio;
	पूर्णांक err = 0;

	err = update_root_ft_destroy(ft);
	अगर (err)
		वापस err;

	fs_get_obj(prio, ft->node.parent);
	अगर  (!(list_first_entry(&prio->node.children,
				काष्ठा mlx5_flow_table,
				node.list) == ft))
		वापस 0;

	next_ft = find_next_chained_ft(prio);
	err = connect_fwd_rules(dev, next_ft, ft);
	अगर (err)
		वापस err;

	err = connect_prev_fts(dev, next_ft, prio);
	अगर (err)
		mlx5_core_warn(dev, "Failed to disconnect flow table %d\n",
			       ft->id);
	वापस err;
पूर्ण

पूर्णांक mlx5_destroy_flow_table(काष्ठा mlx5_flow_table *ft)
अणु
	काष्ठा mlx5_flow_root_namespace *root = find_root(&ft->node);
	पूर्णांक err = 0;

	mutex_lock(&root->chain_lock);
	अगर (!(ft->flags & MLX5_FLOW_TABLE_UNMANAGED))
		err = disconnect_flow_table(ft);
	अगर (err) अणु
		mutex_unlock(&root->chain_lock);
		वापस err;
	पूर्ण
	अगर (tree_हटाओ_node(&ft->node, false))
		mlx5_core_warn(get_dev(&ft->node), "Flow table %d wasn't destroyed, refcount > 1\n",
			       ft->id);
	mutex_unlock(&root->chain_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_destroy_flow_table);

व्योम mlx5_destroy_flow_group(काष्ठा mlx5_flow_group *fg)
अणु
	अगर (tree_हटाओ_node(&fg->node, false))
		mlx5_core_warn(get_dev(&fg->node), "Flow group %d wasn't destroyed, refcount > 1\n",
			       fg->id);
पूर्ण
EXPORT_SYMBOL(mlx5_destroy_flow_group);

काष्ठा mlx5_flow_namespace *mlx5_get_fdb_sub_ns(काष्ठा mlx5_core_dev *dev,
						पूर्णांक n)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;

	अगर (!steering || !steering->fdb_sub_ns)
		वापस शून्य;

	वापस steering->fdb_sub_ns[n];
पूर्ण
EXPORT_SYMBOL(mlx5_get_fdb_sub_ns);

काष्ठा mlx5_flow_namespace *mlx5_get_flow_namespace(काष्ठा mlx5_core_dev *dev,
						    क्रमागत mlx5_flow_namespace_type type)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;
	काष्ठा mlx5_flow_root_namespace *root_ns;
	पूर्णांक prio = 0;
	काष्ठा fs_prio *fs_prio;
	काष्ठा mlx5_flow_namespace *ns;

	अगर (!steering)
		वापस शून्य;

	चयन (type) अणु
	हाल MLX5_FLOW_NAMESPACE_FDB:
		अगर (steering->fdb_root_ns)
			वापस &steering->fdb_root_ns->ns;
		वापस शून्य;
	हाल MLX5_FLOW_NAMESPACE_SNIFFER_RX:
		अगर (steering->snअगरfer_rx_root_ns)
			वापस &steering->snअगरfer_rx_root_ns->ns;
		वापस शून्य;
	हाल MLX5_FLOW_NAMESPACE_SNIFFER_TX:
		अगर (steering->snअगरfer_tx_root_ns)
			वापस &steering->snअगरfer_tx_root_ns->ns;
		वापस शून्य;
	शेष:
		अवरोध;
	पूर्ण

	अगर (type == MLX5_FLOW_NAMESPACE_EGRESS ||
	    type == MLX5_FLOW_NAMESPACE_EGRESS_KERNEL) अणु
		root_ns = steering->egress_root_ns;
		prio = type - MLX5_FLOW_NAMESPACE_EGRESS;
	पूर्ण अन्यथा अगर (type == MLX5_FLOW_NAMESPACE_RDMA_RX) अणु
		root_ns = steering->rdma_rx_root_ns;
		prio = RDMA_RX_BYPASS_PRIO;
	पूर्ण अन्यथा अगर (type == MLX5_FLOW_NAMESPACE_RDMA_RX_KERNEL) अणु
		root_ns = steering->rdma_rx_root_ns;
		prio = RDMA_RX_KERNEL_PRIO;
	पूर्ण अन्यथा अगर (type == MLX5_FLOW_NAMESPACE_RDMA_TX) अणु
		root_ns = steering->rdma_tx_root_ns;
	पूर्ण अन्यथा अणु /* Must be NIC RX */
		root_ns = steering->root_ns;
		prio = type;
	पूर्ण

	अगर (!root_ns)
		वापस शून्य;

	fs_prio = find_prio(&root_ns->ns, prio);
	अगर (!fs_prio)
		वापस शून्य;

	ns = list_first_entry(&fs_prio->node.children,
			      typeof(*ns),
			      node.list);

	वापस ns;
पूर्ण
EXPORT_SYMBOL(mlx5_get_flow_namespace);

काष्ठा mlx5_flow_namespace *mlx5_get_flow_vport_acl_namespace(काष्ठा mlx5_core_dev *dev,
							      क्रमागत mlx5_flow_namespace_type type,
							      पूर्णांक vport)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;

	अगर (!steering)
		वापस शून्य;

	चयन (type) अणु
	हाल MLX5_FLOW_NAMESPACE_ESW_EGRESS:
		अगर (vport >= steering->esw_egress_acl_vports)
			वापस शून्य;
		अगर (steering->esw_egress_root_ns &&
		    steering->esw_egress_root_ns[vport])
			वापस &steering->esw_egress_root_ns[vport]->ns;
		अन्यथा
			वापस शून्य;
	हाल MLX5_FLOW_NAMESPACE_ESW_INGRESS:
		अगर (vport >= steering->esw_ingress_acl_vports)
			वापस शून्य;
		अगर (steering->esw_ingress_root_ns &&
		    steering->esw_ingress_root_ns[vport])
			वापस &steering->esw_ingress_root_ns[vport]->ns;
		अन्यथा
			वापस शून्य;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा fs_prio *_fs_create_prio(काष्ठा mlx5_flow_namespace *ns,
				       अचिन्हित पूर्णांक prio,
				       पूर्णांक num_levels,
				       क्रमागत fs_node_type type)
अणु
	काष्ठा fs_prio *fs_prio;

	fs_prio = kzalloc(माप(*fs_prio), GFP_KERNEL);
	अगर (!fs_prio)
		वापस ERR_PTR(-ENOMEM);

	fs_prio->node.type = type;
	tree_init_node(&fs_prio->node, शून्य, del_sw_prio);
	tree_add_node(&fs_prio->node, &ns->node);
	fs_prio->num_levels = num_levels;
	fs_prio->prio = prio;
	list_add_tail(&fs_prio->node.list, &ns->node.children);

	वापस fs_prio;
पूर्ण

अटल काष्ठा fs_prio *fs_create_prio_chained(काष्ठा mlx5_flow_namespace *ns,
					      अचिन्हित पूर्णांक prio,
					      पूर्णांक num_levels)
अणु
	वापस _fs_create_prio(ns, prio, num_levels, FS_TYPE_PRIO_CHAINS);
पूर्ण

अटल काष्ठा fs_prio *fs_create_prio(काष्ठा mlx5_flow_namespace *ns,
				      अचिन्हित पूर्णांक prio, पूर्णांक num_levels)
अणु
	वापस _fs_create_prio(ns, prio, num_levels, FS_TYPE_PRIO);
पूर्ण

अटल काष्ठा mlx5_flow_namespace *fs_init_namespace(काष्ठा mlx5_flow_namespace
						     *ns)
अणु
	ns->node.type = FS_TYPE_NAMESPACE;

	वापस ns;
पूर्ण

अटल काष्ठा mlx5_flow_namespace *fs_create_namespace(काष्ठा fs_prio *prio,
						       पूर्णांक def_miss_act)
अणु
	काष्ठा mlx5_flow_namespace	*ns;

	ns = kzalloc(माप(*ns), GFP_KERNEL);
	अगर (!ns)
		वापस ERR_PTR(-ENOMEM);

	fs_init_namespace(ns);
	ns->def_miss_action = def_miss_act;
	tree_init_node(&ns->node, शून्य, del_sw_ns);
	tree_add_node(&ns->node, &prio->node);
	list_add_tail(&ns->node.list, &prio->node.children);

	वापस ns;
पूर्ण

अटल पूर्णांक create_leaf_prios(काष्ठा mlx5_flow_namespace *ns, पूर्णांक prio,
			     काष्ठा init_tree_node *prio_metadata)
अणु
	काष्ठा fs_prio *fs_prio;
	पूर्णांक i;

	क्रम (i = 0; i < prio_metadata->num_leaf_prios; i++) अणु
		fs_prio = fs_create_prio(ns, prio++, prio_metadata->num_levels);
		अगर (IS_ERR(fs_prio))
			वापस PTR_ERR(fs_prio);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा FLOW_TABLE_BIT_SZ 1
#घोषणा GET_FLOW_TABLE_CAP(dev, offset) \
	((be32_to_cpu(*((__be32 *)(dev->caps.hca_cur[MLX5_CAP_FLOW_TABLE]) +	\
			offset / 32)) >>					\
	  (32 - FLOW_TABLE_BIT_SZ - (offset & 0x1f))) & FLOW_TABLE_BIT_SZ)
अटल bool has_required_caps(काष्ठा mlx5_core_dev *dev, काष्ठा node_caps *caps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < caps->arr_sz; i++) अणु
		अगर (!GET_FLOW_TABLE_CAP(dev, caps->caps[i]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक init_root_tree_recursive(काष्ठा mlx5_flow_steering *steering,
				    काष्ठा init_tree_node *init_node,
				    काष्ठा fs_node *fs_parent_node,
				    काष्ठा init_tree_node *init_parent_node,
				    पूर्णांक prio)
अणु
	पूर्णांक max_ft_level = MLX5_CAP_FLOWTABLE(steering->dev,
					      flow_table_properties_nic_receive.
					      max_ft_level);
	काष्ठा mlx5_flow_namespace *fs_ns;
	काष्ठा fs_prio *fs_prio;
	काष्ठा fs_node *base;
	पूर्णांक i;
	पूर्णांक err;

	अगर (init_node->type == FS_TYPE_PRIO) अणु
		अगर ((init_node->min_ft_level > max_ft_level) ||
		    !has_required_caps(steering->dev, &init_node->caps))
			वापस 0;

		fs_get_obj(fs_ns, fs_parent_node);
		अगर (init_node->num_leaf_prios)
			वापस create_leaf_prios(fs_ns, prio, init_node);
		fs_prio = fs_create_prio(fs_ns, prio, init_node->num_levels);
		अगर (IS_ERR(fs_prio))
			वापस PTR_ERR(fs_prio);
		base = &fs_prio->node;
	पूर्ण अन्यथा अगर (init_node->type == FS_TYPE_NAMESPACE) अणु
		fs_get_obj(fs_prio, fs_parent_node);
		fs_ns = fs_create_namespace(fs_prio, init_node->def_miss_action);
		अगर (IS_ERR(fs_ns))
			वापस PTR_ERR(fs_ns);
		base = &fs_ns->node;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	prio = 0;
	क्रम (i = 0; i < init_node->ar_size; i++) अणु
		err = init_root_tree_recursive(steering, &init_node->children[i],
					       base, init_node, prio);
		अगर (err)
			वापस err;
		अगर (init_node->children[i].type == FS_TYPE_PRIO &&
		    init_node->children[i].num_leaf_prios) अणु
			prio += init_node->children[i].num_leaf_prios;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_root_tree(काष्ठा mlx5_flow_steering *steering,
			  काष्ठा init_tree_node *init_node,
			  काष्ठा fs_node *fs_parent_node)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < init_node->ar_size; i++) अणु
		err = init_root_tree_recursive(steering, &init_node->children[i],
					       fs_parent_node,
					       init_node, i);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम del_sw_root_ns(काष्ठा fs_node *node)
अणु
	काष्ठा mlx5_flow_root_namespace *root_ns;
	काष्ठा mlx5_flow_namespace *ns;

	fs_get_obj(ns, node);
	root_ns = container_of(ns, काष्ठा mlx5_flow_root_namespace, ns);
	mutex_destroy(&root_ns->chain_lock);
	kमुक्त(node);
पूर्ण

अटल काष्ठा mlx5_flow_root_namespace
*create_root_ns(काष्ठा mlx5_flow_steering *steering,
		क्रमागत fs_flow_table_type table_type)
अणु
	स्थिर काष्ठा mlx5_flow_cmds *cmds = mlx5_fs_cmd_get_शेष(table_type);
	काष्ठा mlx5_flow_root_namespace *root_ns;
	काष्ठा mlx5_flow_namespace *ns;

	अगर (mlx5_fpga_ipsec_device_caps(steering->dev) & MLX5_ACCEL_IPSEC_CAP_DEVICE &&
	    (table_type == FS_FT_NIC_RX || table_type == FS_FT_NIC_TX))
		cmds = mlx5_fs_cmd_get_शेष_ipsec_fpga_cmds(table_type);

	/* Create the root namespace */
	root_ns = kzalloc(माप(*root_ns), GFP_KERNEL);
	अगर (!root_ns)
		वापस शून्य;

	root_ns->dev = steering->dev;
	root_ns->table_type = table_type;
	root_ns->cmds = cmds;

	INIT_LIST_HEAD(&root_ns->underlay_qpns);

	ns = &root_ns->ns;
	fs_init_namespace(ns);
	mutex_init(&root_ns->chain_lock);
	tree_init_node(&ns->node, शून्य, del_sw_root_ns);
	tree_add_node(&ns->node, शून्य);

	वापस root_ns;
पूर्ण

अटल व्योम set_prio_attrs_in_prio(काष्ठा fs_prio *prio, पूर्णांक acc_level);

अटल पूर्णांक set_prio_attrs_in_ns(काष्ठा mlx5_flow_namespace *ns, पूर्णांक acc_level)
अणु
	काष्ठा fs_prio *prio;

	fs_क्रम_each_prio(prio, ns) अणु
		 /* This updates prio start_level and num_levels */
		set_prio_attrs_in_prio(prio, acc_level);
		acc_level += prio->num_levels;
	पूर्ण
	वापस acc_level;
पूर्ण

अटल व्योम set_prio_attrs_in_prio(काष्ठा fs_prio *prio, पूर्णांक acc_level)
अणु
	काष्ठा mlx5_flow_namespace *ns;
	पूर्णांक acc_level_ns = acc_level;

	prio->start_level = acc_level;
	fs_क्रम_each_ns(ns, prio) अणु
		/* This updates start_level and num_levels of ns's priority descendants */
		acc_level_ns = set_prio_attrs_in_ns(ns, acc_level);

		/* If this a prio with chains, and we can jump from one chain
		 * (namepsace) to another, so we accumulate the levels
		 */
		अगर (prio->node.type == FS_TYPE_PRIO_CHAINS)
			acc_level = acc_level_ns;
	पूर्ण

	अगर (!prio->num_levels)
		prio->num_levels = acc_level_ns - prio->start_level;
	WARN_ON(prio->num_levels < acc_level_ns - prio->start_level);
पूर्ण

अटल व्योम set_prio_attrs(काष्ठा mlx5_flow_root_namespace *root_ns)
अणु
	काष्ठा mlx5_flow_namespace *ns = &root_ns->ns;
	काष्ठा fs_prio *prio;
	पूर्णांक start_level = 0;

	fs_क्रम_each_prio(prio, ns) अणु
		set_prio_attrs_in_prio(prio, start_level);
		start_level += prio->num_levels;
	पूर्ण
पूर्ण

#घोषणा ANCHOR_PRIO 0
#घोषणा ANCHOR_SIZE 1
#घोषणा ANCHOR_LEVEL 0
अटल पूर्णांक create_anchor_flow_table(काष्ठा mlx5_flow_steering *steering)
अणु
	काष्ठा mlx5_flow_namespace *ns = शून्य;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_table *ft;

	ns = mlx5_get_flow_namespace(steering->dev, MLX5_FLOW_NAMESPACE_ANCHOR);
	अगर (WARN_ON(!ns))
		वापस -EINVAL;

	ft_attr.max_fte = ANCHOR_SIZE;
	ft_attr.level   = ANCHOR_LEVEL;
	ft_attr.prio    = ANCHOR_PRIO;

	ft = mlx5_create_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		mlx5_core_err(steering->dev, "Failed to create last anchor flow table");
		वापस PTR_ERR(ft);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक init_root_ns(काष्ठा mlx5_flow_steering *steering)
अणु
	पूर्णांक err;

	steering->root_ns = create_root_ns(steering, FS_FT_NIC_RX);
	अगर (!steering->root_ns)
		वापस -ENOMEM;

	err = init_root_tree(steering, &root_fs, &steering->root_ns->ns.node);
	अगर (err)
		जाओ out_err;

	set_prio_attrs(steering->root_ns);
	err = create_anchor_flow_table(steering);
	अगर (err)
		जाओ out_err;

	वापस 0;

out_err:
	cleanup_root_ns(steering->root_ns);
	steering->root_ns = शून्य;
	वापस err;
पूर्ण

अटल व्योम clean_tree(काष्ठा fs_node *node)
अणु
	अगर (node) अणु
		काष्ठा fs_node *iter;
		काष्ठा fs_node *temp;

		tree_get_node(node);
		list_क्रम_each_entry_safe(iter, temp, &node->children, list)
			clean_tree(iter);
		tree_put_node(node, false);
		tree_हटाओ_node(node, false);
	पूर्ण
पूर्ण

अटल व्योम cleanup_root_ns(काष्ठा mlx5_flow_root_namespace *root_ns)
अणु
	अगर (!root_ns)
		वापस;

	clean_tree(&root_ns->ns.node);
पूर्ण

व्योम mlx5_cleanup_fs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;

	cleanup_root_ns(steering->root_ns);
	cleanup_root_ns(steering->fdb_root_ns);
	steering->fdb_root_ns = शून्य;
	kमुक्त(steering->fdb_sub_ns);
	steering->fdb_sub_ns = शून्य;
	cleanup_root_ns(steering->snअगरfer_rx_root_ns);
	cleanup_root_ns(steering->snअगरfer_tx_root_ns);
	cleanup_root_ns(steering->rdma_rx_root_ns);
	cleanup_root_ns(steering->rdma_tx_root_ns);
	cleanup_root_ns(steering->egress_root_ns);
	mlx5_cleanup_fc_stats(dev);
	kmem_cache_destroy(steering->ftes_cache);
	kmem_cache_destroy(steering->fgs_cache);
	kमुक्त(steering);
पूर्ण

अटल पूर्णांक init_snअगरfer_tx_root_ns(काष्ठा mlx5_flow_steering *steering)
अणु
	काष्ठा fs_prio *prio;

	steering->snअगरfer_tx_root_ns = create_root_ns(steering, FS_FT_SNIFFER_TX);
	अगर (!steering->snअगरfer_tx_root_ns)
		वापस -ENOMEM;

	/* Create single prio */
	prio = fs_create_prio(&steering->snअगरfer_tx_root_ns->ns, 0, 1);
	वापस PTR_ERR_OR_ZERO(prio);
पूर्ण

अटल पूर्णांक init_snअगरfer_rx_root_ns(काष्ठा mlx5_flow_steering *steering)
अणु
	काष्ठा fs_prio *prio;

	steering->snअगरfer_rx_root_ns = create_root_ns(steering, FS_FT_SNIFFER_RX);
	अगर (!steering->snअगरfer_rx_root_ns)
		वापस -ENOMEM;

	/* Create single prio */
	prio = fs_create_prio(&steering->snअगरfer_rx_root_ns->ns, 0, 1);
	वापस PTR_ERR_OR_ZERO(prio);
पूर्ण

अटल पूर्णांक init_rdma_rx_root_ns(काष्ठा mlx5_flow_steering *steering)
अणु
	पूर्णांक err;

	steering->rdma_rx_root_ns = create_root_ns(steering, FS_FT_RDMA_RX);
	अगर (!steering->rdma_rx_root_ns)
		वापस -ENOMEM;

	err = init_root_tree(steering, &rdma_rx_root_fs,
			     &steering->rdma_rx_root_ns->ns.node);
	अगर (err)
		जाओ out_err;

	set_prio_attrs(steering->rdma_rx_root_ns);

	वापस 0;

out_err:
	cleanup_root_ns(steering->rdma_rx_root_ns);
	steering->rdma_rx_root_ns = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक init_rdma_tx_root_ns(काष्ठा mlx5_flow_steering *steering)
अणु
	पूर्णांक err;

	steering->rdma_tx_root_ns = create_root_ns(steering, FS_FT_RDMA_TX);
	अगर (!steering->rdma_tx_root_ns)
		वापस -ENOMEM;

	err = init_root_tree(steering, &rdma_tx_root_fs,
			     &steering->rdma_tx_root_ns->ns.node);
	अगर (err)
		जाओ out_err;

	set_prio_attrs(steering->rdma_tx_root_ns);

	वापस 0;

out_err:
	cleanup_root_ns(steering->rdma_tx_root_ns);
	steering->rdma_tx_root_ns = शून्य;
	वापस err;
पूर्ण

/* FT and tc chains are stored in the same array so we can re-use the
 * mlx5_get_fdb_sub_ns() and tc api क्रम FT chains.
 * When creating a new ns क्रम each chain store it in the first available slot.
 * Assume tc chains are created and stored first and only then the FT chain.
 */
अटल व्योम store_fdb_sub_ns_prio_chain(काष्ठा mlx5_flow_steering *steering,
					काष्ठा mlx5_flow_namespace *ns)
अणु
	पूर्णांक chain = 0;

	जबतक (steering->fdb_sub_ns[chain])
		++chain;

	steering->fdb_sub_ns[chain] = ns;
पूर्ण

अटल पूर्णांक create_fdb_sub_ns_prio_chain(काष्ठा mlx5_flow_steering *steering,
					काष्ठा fs_prio *maj_prio)
अणु
	काष्ठा mlx5_flow_namespace *ns;
	काष्ठा fs_prio *min_prio;
	पूर्णांक prio;

	ns = fs_create_namespace(maj_prio, MLX5_FLOW_TABLE_MISS_ACTION_DEF);
	अगर (IS_ERR(ns))
		वापस PTR_ERR(ns);

	क्रम (prio = 0; prio < FDB_TC_MAX_PRIO; prio++) अणु
		min_prio = fs_create_prio(ns, prio, FDB_TC_LEVELS_PER_PRIO);
		अगर (IS_ERR(min_prio))
			वापस PTR_ERR(min_prio);
	पूर्ण

	store_fdb_sub_ns_prio_chain(steering, ns);

	वापस 0;
पूर्ण

अटल पूर्णांक create_fdb_chains(काष्ठा mlx5_flow_steering *steering,
			     पूर्णांक fs_prio,
			     पूर्णांक chains)
अणु
	काष्ठा fs_prio *maj_prio;
	पूर्णांक levels;
	पूर्णांक chain;
	पूर्णांक err;

	levels = FDB_TC_LEVELS_PER_PRIO * FDB_TC_MAX_PRIO * chains;
	maj_prio = fs_create_prio_chained(&steering->fdb_root_ns->ns,
					  fs_prio,
					  levels);
	अगर (IS_ERR(maj_prio))
		वापस PTR_ERR(maj_prio);

	क्रम (chain = 0; chain < chains; chain++) अणु
		err = create_fdb_sub_ns_prio_chain(steering, maj_prio);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_fdb_fast_path(काष्ठा mlx5_flow_steering *steering)
अणु
	पूर्णांक err;

	steering->fdb_sub_ns = kसुस्मृति(FDB_NUM_CHAINS,
				       माप(*steering->fdb_sub_ns),
				       GFP_KERNEL);
	अगर (!steering->fdb_sub_ns)
		वापस -ENOMEM;

	err = create_fdb_chains(steering, FDB_TC_OFFLOAD, FDB_TC_MAX_CHAIN + 1);
	अगर (err)
		वापस err;

	err = create_fdb_chains(steering, FDB_FT_OFFLOAD, 1);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक init_fdb_root_ns(काष्ठा mlx5_flow_steering *steering)
अणु
	काष्ठा fs_prio *maj_prio;
	पूर्णांक err;

	steering->fdb_root_ns = create_root_ns(steering, FS_FT_FDB);
	अगर (!steering->fdb_root_ns)
		वापस -ENOMEM;

	maj_prio = fs_create_prio(&steering->fdb_root_ns->ns, FDB_BYPASS_PATH,
				  1);
	अगर (IS_ERR(maj_prio)) अणु
		err = PTR_ERR(maj_prio);
		जाओ out_err;
	पूर्ण
	err = create_fdb_fast_path(steering);
	अगर (err)
		जाओ out_err;

	maj_prio = fs_create_prio(&steering->fdb_root_ns->ns, FDB_SLOW_PATH, 1);
	अगर (IS_ERR(maj_prio)) अणु
		err = PTR_ERR(maj_prio);
		जाओ out_err;
	पूर्ण

	/* We put this priority last, knowing that nothing will get here
	 * unless explicitly क्रमwarded to. This is possible because the
	 * slow path tables have catch all rules and nothing माला_लो passed
	 * those tables.
	 */
	maj_prio = fs_create_prio(&steering->fdb_root_ns->ns, FDB_PER_VPORT, 1);
	अगर (IS_ERR(maj_prio)) अणु
		err = PTR_ERR(maj_prio);
		जाओ out_err;
	पूर्ण

	set_prio_attrs(steering->fdb_root_ns);
	वापस 0;

out_err:
	cleanup_root_ns(steering->fdb_root_ns);
	kमुक्त(steering->fdb_sub_ns);
	steering->fdb_sub_ns = शून्य;
	steering->fdb_root_ns = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक init_egress_acl_root_ns(काष्ठा mlx5_flow_steering *steering, पूर्णांक vport)
अणु
	काष्ठा fs_prio *prio;

	steering->esw_egress_root_ns[vport] = create_root_ns(steering, FS_FT_ESW_EGRESS_ACL);
	अगर (!steering->esw_egress_root_ns[vport])
		वापस -ENOMEM;

	/* create 1 prio*/
	prio = fs_create_prio(&steering->esw_egress_root_ns[vport]->ns, 0, 1);
	वापस PTR_ERR_OR_ZERO(prio);
पूर्ण

अटल पूर्णांक init_ingress_acl_root_ns(काष्ठा mlx5_flow_steering *steering, पूर्णांक vport)
अणु
	काष्ठा fs_prio *prio;

	steering->esw_ingress_root_ns[vport] = create_root_ns(steering, FS_FT_ESW_INGRESS_ACL);
	अगर (!steering->esw_ingress_root_ns[vport])
		वापस -ENOMEM;

	/* create 1 prio*/
	prio = fs_create_prio(&steering->esw_ingress_root_ns[vport]->ns, 0, 1);
	वापस PTR_ERR_OR_ZERO(prio);
पूर्ण

पूर्णांक mlx5_fs_egress_acls_init(काष्ठा mlx5_core_dev *dev, पूर्णांक total_vports)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;
	पूर्णांक err;
	पूर्णांक i;

	steering->esw_egress_root_ns =
			kसुस्मृति(total_vports,
				माप(*steering->esw_egress_root_ns),
				GFP_KERNEL);
	अगर (!steering->esw_egress_root_ns)
		वापस -ENOMEM;

	क्रम (i = 0; i < total_vports; i++) अणु
		err = init_egress_acl_root_ns(steering, i);
		अगर (err)
			जाओ cleanup_root_ns;
	पूर्ण
	steering->esw_egress_acl_vports = total_vports;
	वापस 0;

cleanup_root_ns:
	क्रम (i--; i >= 0; i--)
		cleanup_root_ns(steering->esw_egress_root_ns[i]);
	kमुक्त(steering->esw_egress_root_ns);
	steering->esw_egress_root_ns = शून्य;
	वापस err;
पूर्ण

व्योम mlx5_fs_egress_acls_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;
	पूर्णांक i;

	अगर (!steering->esw_egress_root_ns)
		वापस;

	क्रम (i = 0; i < steering->esw_egress_acl_vports; i++)
		cleanup_root_ns(steering->esw_egress_root_ns[i]);

	kमुक्त(steering->esw_egress_root_ns);
	steering->esw_egress_root_ns = शून्य;
पूर्ण

पूर्णांक mlx5_fs_ingress_acls_init(काष्ठा mlx5_core_dev *dev, पूर्णांक total_vports)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;
	पूर्णांक err;
	पूर्णांक i;

	steering->esw_ingress_root_ns =
			kसुस्मृति(total_vports,
				माप(*steering->esw_ingress_root_ns),
				GFP_KERNEL);
	अगर (!steering->esw_ingress_root_ns)
		वापस -ENOMEM;

	क्रम (i = 0; i < total_vports; i++) अणु
		err = init_ingress_acl_root_ns(steering, i);
		अगर (err)
			जाओ cleanup_root_ns;
	पूर्ण
	steering->esw_ingress_acl_vports = total_vports;
	वापस 0;

cleanup_root_ns:
	क्रम (i--; i >= 0; i--)
		cleanup_root_ns(steering->esw_ingress_root_ns[i]);
	kमुक्त(steering->esw_ingress_root_ns);
	steering->esw_ingress_root_ns = शून्य;
	वापस err;
पूर्ण

व्योम mlx5_fs_ingress_acls_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_flow_steering *steering = dev->priv.steering;
	पूर्णांक i;

	अगर (!steering->esw_ingress_root_ns)
		वापस;

	क्रम (i = 0; i < steering->esw_ingress_acl_vports; i++)
		cleanup_root_ns(steering->esw_ingress_root_ns[i]);

	kमुक्त(steering->esw_ingress_root_ns);
	steering->esw_ingress_root_ns = शून्य;
पूर्ण

अटल पूर्णांक init_egress_root_ns(काष्ठा mlx5_flow_steering *steering)
अणु
	पूर्णांक err;

	steering->egress_root_ns = create_root_ns(steering,
						  FS_FT_NIC_TX);
	अगर (!steering->egress_root_ns)
		वापस -ENOMEM;

	err = init_root_tree(steering, &egress_root_fs,
			     &steering->egress_root_ns->ns.node);
	अगर (err)
		जाओ cleanup;
	set_prio_attrs(steering->egress_root_ns);
	वापस 0;
cleanup:
	cleanup_root_ns(steering->egress_root_ns);
	steering->egress_root_ns = शून्य;
	वापस err;
पूर्ण

पूर्णांक mlx5_init_fs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_flow_steering *steering;
	पूर्णांक err = 0;

	err = mlx5_init_fc_stats(dev);
	अगर (err)
		वापस err;

	steering = kzalloc(माप(*steering), GFP_KERNEL);
	अगर (!steering)
		वापस -ENOMEM;
	steering->dev = dev;
	dev->priv.steering = steering;

	steering->fgs_cache = kmem_cache_create("mlx5_fs_fgs",
						माप(काष्ठा mlx5_flow_group), 0,
						0, शून्य);
	steering->ftes_cache = kmem_cache_create("mlx5_fs_ftes", माप(काष्ठा fs_fte), 0,
						 0, शून्य);
	अगर (!steering->ftes_cache || !steering->fgs_cache) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर ((((MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_ETH) &&
	      (MLX5_CAP_GEN(dev, nic_flow_table))) ||
	     ((MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_IB) &&
	      MLX5_CAP_GEN(dev, ipoib_enhanced_offloads))) &&
	    MLX5_CAP_FLOWTABLE_NIC_RX(dev, ft_support)) अणु
		err = init_root_ns(steering);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (MLX5_ESWITCH_MANAGER(dev)) अणु
		अगर (MLX5_CAP_ESW_FLOWTABLE_FDB(dev, ft_support)) अणु
			err = init_fdb_root_ns(steering);
			अगर (err)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_FLOWTABLE_SNIFFER_RX(dev, ft_support)) अणु
		err = init_snअगरfer_rx_root_ns(steering);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (MLX5_CAP_FLOWTABLE_SNIFFER_TX(dev, ft_support)) अणु
		err = init_snअगरfer_tx_root_ns(steering);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (MLX5_CAP_FLOWTABLE_RDMA_RX(dev, ft_support) &&
	    MLX5_CAP_FLOWTABLE_RDMA_RX(dev, table_miss_action_करोमुख्य)) अणु
		err = init_rdma_rx_root_ns(steering);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (MLX5_CAP_FLOWTABLE_RDMA_TX(dev, ft_support)) अणु
		err = init_rdma_tx_root_ns(steering);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (mlx5_fpga_ipsec_device_caps(steering->dev) & MLX5_ACCEL_IPSEC_CAP_DEVICE ||
	    MLX5_CAP_FLOWTABLE_NIC_TX(dev, ft_support)) अणु
		err = init_egress_root_ns(steering);
		अगर (err)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	mlx5_cleanup_fs(dev);
	वापस err;
पूर्ण

पूर्णांक mlx5_fs_add_rx_underlay_qpn(काष्ठा mlx5_core_dev *dev, u32 underlay_qpn)
अणु
	काष्ठा mlx5_flow_root_namespace *root = dev->priv.steering->root_ns;
	काष्ठा mlx5_ft_underlay_qp *new_uqp;
	पूर्णांक err = 0;

	new_uqp = kzalloc(माप(*new_uqp), GFP_KERNEL);
	अगर (!new_uqp)
		वापस -ENOMEM;

	mutex_lock(&root->chain_lock);

	अगर (!root->root_ft) अणु
		err = -EINVAL;
		जाओ update_ft_fail;
	पूर्ण

	err = root->cmds->update_root_ft(root, root->root_ft, underlay_qpn,
					 false);
	अगर (err) अणु
		mlx5_core_warn(dev, "Failed adding underlay QPN (%u) to root FT err(%d)\n",
			       underlay_qpn, err);
		जाओ update_ft_fail;
	पूर्ण

	new_uqp->qpn = underlay_qpn;
	list_add_tail(&new_uqp->list, &root->underlay_qpns);

	mutex_unlock(&root->chain_lock);

	वापस 0;

update_ft_fail:
	mutex_unlock(&root->chain_lock);
	kमुक्त(new_uqp);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_fs_add_rx_underlay_qpn);

पूर्णांक mlx5_fs_हटाओ_rx_underlay_qpn(काष्ठा mlx5_core_dev *dev, u32 underlay_qpn)
अणु
	काष्ठा mlx5_flow_root_namespace *root = dev->priv.steering->root_ns;
	काष्ठा mlx5_ft_underlay_qp *uqp;
	bool found = false;
	पूर्णांक err = 0;

	mutex_lock(&root->chain_lock);
	list_क्रम_each_entry(uqp, &root->underlay_qpns, list) अणु
		अगर (uqp->qpn == underlay_qpn) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		mlx5_core_warn(dev, "Failed finding underlay qp (%u) in qpn list\n",
			       underlay_qpn);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = root->cmds->update_root_ft(root, root->root_ft, underlay_qpn,
					 true);
	अगर (err)
		mlx5_core_warn(dev, "Failed removing underlay QPN (%u) from root FT err(%d)\n",
			       underlay_qpn, err);

	list_del(&uqp->list);
	mutex_unlock(&root->chain_lock);
	kमुक्त(uqp);

	वापस 0;

out:
	mutex_unlock(&root->chain_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_fs_हटाओ_rx_underlay_qpn);

अटल काष्ठा mlx5_flow_root_namespace
*get_root_namespace(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_flow_namespace_type ns_type)
अणु
	काष्ठा mlx5_flow_namespace *ns;

	अगर (ns_type == MLX5_FLOW_NAMESPACE_ESW_EGRESS ||
	    ns_type == MLX5_FLOW_NAMESPACE_ESW_INGRESS)
		ns = mlx5_get_flow_vport_acl_namespace(dev, ns_type, 0);
	अन्यथा
		ns = mlx5_get_flow_namespace(dev, ns_type);
	अगर (!ns)
		वापस शून्य;

	वापस find_root(&ns->node);
पूर्ण

काष्ठा mlx5_modअगरy_hdr *mlx5_modअगरy_header_alloc(काष्ठा mlx5_core_dev *dev,
						 u8 ns_type, u8 num_actions,
						 व्योम *modअगरy_actions)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
	पूर्णांक err;

	root = get_root_namespace(dev, ns_type);
	अगर (!root)
		वापस ERR_PTR(-EOPNOTSUPP);

	modअगरy_hdr = kzalloc(माप(*modअगरy_hdr), GFP_KERNEL);
	अगर (!modअगरy_hdr)
		वापस ERR_PTR(-ENOMEM);

	modअगरy_hdr->ns_type = ns_type;
	err = root->cmds->modअगरy_header_alloc(root, ns_type, num_actions,
					      modअगरy_actions, modअगरy_hdr);
	अगर (err) अणु
		kमुक्त(modअगरy_hdr);
		वापस ERR_PTR(err);
	पूर्ण

	वापस modअगरy_hdr;
पूर्ण
EXPORT_SYMBOL(mlx5_modअगरy_header_alloc);

व्योम mlx5_modअगरy_header_dealloc(काष्ठा mlx5_core_dev *dev,
				काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr)
अणु
	काष्ठा mlx5_flow_root_namespace *root;

	root = get_root_namespace(dev, modअगरy_hdr->ns_type);
	अगर (WARN_ON(!root))
		वापस;
	root->cmds->modअगरy_header_dealloc(root, modअगरy_hdr);
	kमुक्त(modअगरy_hdr);
पूर्ण
EXPORT_SYMBOL(mlx5_modअगरy_header_dealloc);

काष्ठा mlx5_pkt_reक्रमmat *mlx5_packet_reक्रमmat_alloc(काष्ठा mlx5_core_dev *dev,
						     पूर्णांक reक्रमmat_type,
						     माप_प्रकार size,
						     व्योम *reक्रमmat_data,
						     क्रमागत mlx5_flow_namespace_type ns_type)
अणु
	काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat;
	काष्ठा mlx5_flow_root_namespace *root;
	पूर्णांक err;

	root = get_root_namespace(dev, ns_type);
	अगर (!root)
		वापस ERR_PTR(-EOPNOTSUPP);

	pkt_reक्रमmat = kzalloc(माप(*pkt_reक्रमmat), GFP_KERNEL);
	अगर (!pkt_reक्रमmat)
		वापस ERR_PTR(-ENOMEM);

	pkt_reक्रमmat->ns_type = ns_type;
	pkt_reक्रमmat->reक्रमmat_type = reक्रमmat_type;
	err = root->cmds->packet_reक्रमmat_alloc(root, reक्रमmat_type, size,
						reक्रमmat_data, ns_type,
						pkt_reक्रमmat);
	अगर (err) अणु
		kमुक्त(pkt_reक्रमmat);
		वापस ERR_PTR(err);
	पूर्ण

	वापस pkt_reक्रमmat;
पूर्ण
EXPORT_SYMBOL(mlx5_packet_reक्रमmat_alloc);

व्योम mlx5_packet_reक्रमmat_dealloc(काष्ठा mlx5_core_dev *dev,
				  काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat)
अणु
	काष्ठा mlx5_flow_root_namespace *root;

	root = get_root_namespace(dev, pkt_reक्रमmat->ns_type);
	अगर (WARN_ON(!root))
		वापस;
	root->cmds->packet_reक्रमmat_dealloc(root, pkt_reक्रमmat);
	kमुक्त(pkt_reक्रमmat);
पूर्ण
EXPORT_SYMBOL(mlx5_packet_reक्रमmat_dealloc);

पूर्णांक mlx5_flow_namespace_set_peer(काष्ठा mlx5_flow_root_namespace *ns,
				 काष्ठा mlx5_flow_root_namespace *peer_ns)
अणु
	अगर (peer_ns && ns->mode != peer_ns->mode) अणु
		mlx5_core_err(ns->dev,
			      "Can't peer namespace of different steering mode\n");
		वापस -EINVAL;
	पूर्ण

	वापस ns->cmds->set_peer(ns, peer_ns);
पूर्ण

/* This function should be called only at init stage of the namespace.
 * It is not safe to call this function जबतक steering operations
 * are executed in the namespace.
 */
पूर्णांक mlx5_flow_namespace_set_mode(काष्ठा mlx5_flow_namespace *ns,
				 क्रमागत mlx5_flow_steering_mode mode)
अणु
	काष्ठा mlx5_flow_root_namespace *root;
	स्थिर काष्ठा mlx5_flow_cmds *cmds;
	पूर्णांक err;

	root = find_root(&ns->node);
	अगर (&root->ns != ns)
	/* Can't set cmds to non root namespace */
		वापस -EINVAL;

	अगर (root->table_type != FS_FT_FDB)
		वापस -EOPNOTSUPP;

	अगर (root->mode == mode)
		वापस 0;

	अगर (mode == MLX5_FLOW_STEERING_MODE_SMFS)
		cmds = mlx5_fs_cmd_get_dr_cmds();
	अन्यथा
		cmds = mlx5_fs_cmd_get_fw_cmds();
	अगर (!cmds)
		वापस -EOPNOTSUPP;

	err = cmds->create_ns(root);
	अगर (err) अणु
		mlx5_core_err(root->dev, "Failed to create flow namespace (%d)\n",
			      err);
		वापस err;
	पूर्ण

	root->cmds->destroy_ns(root);
	root->cmds = cmds;
	root->mode = mode;

	वापस 0;
पूर्ण
