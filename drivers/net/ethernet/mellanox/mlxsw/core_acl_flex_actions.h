<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_CORE_ACL_FLEX_ACTIONS_H
#घोषणा _MLXSW_CORE_ACL_FLEX_ACTIONS_H

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <net/flow_offload.h>

काष्ठा mlxsw_afa;
काष्ठा mlxsw_afa_block;

काष्ठा mlxsw_afa_ops अणु
	पूर्णांक (*kvdl_set_add)(व्योम *priv, u32 *p_kvdl_index,
			    अक्षर *enc_actions, bool is_first);
	व्योम (*kvdl_set_del)(व्योम *priv, u32 kvdl_index, bool is_first);
	पूर्णांक (*kvdl_set_activity_get)(व्योम *priv, u32 kvdl_index,
				     bool *activity);
	पूर्णांक (*kvdl_fwd_entry_add)(व्योम *priv, u32 *p_kvdl_index, u8 local_port);
	व्योम (*kvdl_fwd_entry_del)(व्योम *priv, u32 kvdl_index);
	पूर्णांक (*counter_index_get)(व्योम *priv, अचिन्हित पूर्णांक *p_counter_index);
	व्योम (*counter_index_put)(व्योम *priv, अचिन्हित पूर्णांक counter_index);
	पूर्णांक (*mirror_add)(व्योम *priv, u8 local_in_port,
			  स्थिर काष्ठा net_device *out_dev,
			  bool ingress, पूर्णांक *p_span_id);
	व्योम (*mirror_del)(व्योम *priv, u8 local_in_port, पूर्णांक span_id,
			   bool ingress);
	पूर्णांक (*policer_add)(व्योम *priv, u64 rate_bytes_ps, u32 burst,
			   u16 *p_policer_index,
			   काष्ठा netlink_ext_ack *extack);
	व्योम (*policer_del)(व्योम *priv, u16 policer_index);
	पूर्णांक (*sampler_add)(व्योम *priv, u8 local_port,
			   काष्ठा psample_group *psample_group, u32 rate,
			   u32 trunc_size, bool truncate, bool ingress,
			   पूर्णांक *p_span_id, काष्ठा netlink_ext_ack *extack);
	व्योम (*sampler_del)(व्योम *priv, u8 local_port, पूर्णांक span_id,
			    bool ingress);
	bool dummy_first_set;
पूर्ण;

काष्ठा mlxsw_afa *mlxsw_afa_create(अचिन्हित पूर्णांक max_acts_per_set,
				   स्थिर काष्ठा mlxsw_afa_ops *ops,
				   व्योम *ops_priv);
व्योम mlxsw_afa_destroy(काष्ठा mlxsw_afa *mlxsw_afa);
काष्ठा mlxsw_afa_block *mlxsw_afa_block_create(काष्ठा mlxsw_afa *mlxsw_afa);
व्योम mlxsw_afa_block_destroy(काष्ठा mlxsw_afa_block *block);
पूर्णांक mlxsw_afa_block_commit(काष्ठा mlxsw_afa_block *block);
अक्षर *mlxsw_afa_block_first_set(काष्ठा mlxsw_afa_block *block);
अक्षर *mlxsw_afa_block_cur_set(काष्ठा mlxsw_afa_block *block);
u32 mlxsw_afa_block_first_kvdl_index(काष्ठा mlxsw_afa_block *block);
पूर्णांक mlxsw_afa_block_activity_get(काष्ठा mlxsw_afa_block *block, bool *activity);
पूर्णांक mlxsw_afa_block_जारी(काष्ठा mlxsw_afa_block *block);
पूर्णांक mlxsw_afa_block_jump(काष्ठा mlxsw_afa_block *block, u16 group_id);
पूर्णांक mlxsw_afa_block_terminate(काष्ठा mlxsw_afa_block *block);
स्थिर काष्ठा flow_action_cookie *
mlxsw_afa_cookie_lookup(काष्ठा mlxsw_afa *mlxsw_afa, u32 cookie_index);
पूर्णांक mlxsw_afa_block_append_drop(काष्ठा mlxsw_afa_block *block, bool ingress,
				स्थिर काष्ठा flow_action_cookie *fa_cookie,
				काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_trap(काष्ठा mlxsw_afa_block *block, u16 trap_id);
पूर्णांक mlxsw_afa_block_append_trap_and_क्रमward(काष्ठा mlxsw_afa_block *block,
					    u16 trap_id);
पूर्णांक mlxsw_afa_block_append_mirror(काष्ठा mlxsw_afa_block *block,
				  u8 local_in_port,
				  स्थिर काष्ठा net_device *out_dev,
				  bool ingress,
				  काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_fwd(काष्ठा mlxsw_afa_block *block,
			       u8 local_port, bool in_port,
			       काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_vlan_modअगरy(काष्ठा mlxsw_afa_block *block,
				       u16 vid, u8 pcp, u8 et,
				       काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_qos_चयन_prio(काष्ठा mlxsw_afa_block *block,
					   u8 prio,
					   काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_qos_dsfield(काष्ठा mlxsw_afa_block *block,
				       u8 dsfield,
				       काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_qos_dscp(काष्ठा mlxsw_afa_block *block,
				    u8 dscp, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_qos_ecn(काष्ठा mlxsw_afa_block *block,
				   u8 ecn, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_allocated_counter(काष्ठा mlxsw_afa_block *block,
					     u32 counter_index);
पूर्णांक mlxsw_afa_block_append_counter(काष्ठा mlxsw_afa_block *block,
				   u32 *p_counter_index,
				   काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_fid_set(काष्ठा mlxsw_afa_block *block, u16 fid,
				   काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_mcrouter(काष्ठा mlxsw_afa_block *block,
				    u16 expected_irअगर, u16 min_mtu,
				    bool rmid_valid, u32 kvdl_index);
पूर्णांक mlxsw_afa_block_append_l4port(काष्ठा mlxsw_afa_block *block, bool is_dport, u16 l4_port,
				  काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_police(काष्ठा mlxsw_afa_block *block,
				  u32 fa_index, u64 rate_bytes_ps, u32 burst,
				  u16 *p_policer_index,
				  काष्ठा netlink_ext_ack *extack);
पूर्णांक mlxsw_afa_block_append_sampler(काष्ठा mlxsw_afa_block *block, u8 local_port,
				   काष्ठा psample_group *psample_group,
				   u32 rate, u32 trunc_size, bool truncate,
				   bool ingress,
				   काष्ठा netlink_ext_ack *extack);

#पूर्ण_अगर
