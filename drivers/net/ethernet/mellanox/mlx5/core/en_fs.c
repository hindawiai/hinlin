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

#समावेश <linux/list.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/mpfs.h>
#समावेश "en.h"
#समावेश "en_rep.h"
#समावेश "lib/mpfs.h"
#समावेश "en/ptp.h"

अटल पूर्णांक mlx5e_add_l2_flow_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_l2_rule *ai, पूर्णांक type);
अटल व्योम mlx5e_del_l2_flow_rule(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5e_l2_rule *ai);

क्रमागत अणु
	MLX5E_FULLMATCH = 0,
	MLX5E_ALLMULTI  = 1,
पूर्ण;

क्रमागत अणु
	MLX5E_UC        = 0,
	MLX5E_MC_IPV4   = 1,
	MLX5E_MC_IPV6   = 2,
	MLX5E_MC_OTHER  = 3,
पूर्ण;

क्रमागत अणु
	MLX5E_ACTION_NONE = 0,
	MLX5E_ACTION_ADD  = 1,
	MLX5E_ACTION_DEL  = 2,
पूर्ण;

काष्ठा mlx5e_l2_hash_node अणु
	काष्ठा hlist_node          hlist;
	u8                         action;
	काष्ठा mlx5e_l2_rule ai;
	bool   mpfs;
पूर्ण;

अटल अंतरभूत पूर्णांक mlx5e_hash_l2(u8 *addr)
अणु
	वापस addr[5];
पूर्ण

अटल व्योम mlx5e_add_l2_to_hash(काष्ठा hlist_head *hash, u8 *addr)
अणु
	काष्ठा mlx5e_l2_hash_node *hn;
	पूर्णांक ix = mlx5e_hash_l2(addr);
	पूर्णांक found = 0;

	hlist_क्रम_each_entry(hn, &hash[ix], hlist)
		अगर (ether_addr_equal_64bits(hn->ai.addr, addr)) अणु
			found = 1;
			अवरोध;
		पूर्ण

	अगर (found) अणु
		hn->action = MLX5E_ACTION_NONE;
		वापस;
	पूर्ण

	hn = kzalloc(माप(*hn), GFP_ATOMIC);
	अगर (!hn)
		वापस;

	ether_addr_copy(hn->ai.addr, addr);
	hn->action = MLX5E_ACTION_ADD;

	hlist_add_head(&hn->hlist, &hash[ix]);
पूर्ण

अटल व्योम mlx5e_del_l2_from_hash(काष्ठा mlx5e_l2_hash_node *hn)
अणु
	hlist_del(&hn->hlist);
	kमुक्त(hn);
पूर्ण

काष्ठा mlx5e_vlan_table अणु
	काष्ठा mlx5e_flow_table		ft;
	DECLARE_BITMAP(active_cvlans, VLAN_N_VID);
	DECLARE_BITMAP(active_svlans, VLAN_N_VID);
	काष्ठा mlx5_flow_handle	*active_cvlans_rule[VLAN_N_VID];
	काष्ठा mlx5_flow_handle	*active_svlans_rule[VLAN_N_VID];
	काष्ठा mlx5_flow_handle	*untagged_rule;
	काष्ठा mlx5_flow_handle	*any_cvlan_rule;
	काष्ठा mlx5_flow_handle	*any_svlan_rule;
	काष्ठा mlx5_flow_handle	*trap_rule;
	bool			cvlan_filter_disabled;
पूर्ण;

अचिन्हित दीर्घ *mlx5e_vlan_get_active_svlans(काष्ठा mlx5e_vlan_table *vlan)
अणु
	वापस vlan->active_svlans;
पूर्ण

काष्ठा mlx5_flow_table *mlx5e_vlan_get_flowtable(काष्ठा mlx5e_vlan_table *vlan)
अणु
	वापस vlan->ft.t;
पूर्ण

अटल पूर्णांक mlx5e_vport_context_update_vlans(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->netdev;
	पूर्णांक max_list_size;
	पूर्णांक list_size;
	u16 *vlans;
	पूर्णांक vlan;
	पूर्णांक err;
	पूर्णांक i;

	list_size = 0;
	क्रम_each_set_bit(vlan, priv->fs.vlan->active_cvlans, VLAN_N_VID)
		list_size++;

	max_list_size = 1 << MLX5_CAP_GEN(priv->mdev, log_max_vlan_list);

	अगर (list_size > max_list_size) अणु
		netdev_warn(ndev,
			    "netdev vlans list size (%d) > (%d) max vport list size, some vlans will be dropped\n",
			    list_size, max_list_size);
		list_size = max_list_size;
	पूर्ण

	vlans = kसुस्मृति(list_size, माप(*vlans), GFP_KERNEL);
	अगर (!vlans)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_set_bit(vlan, priv->fs.vlan->active_cvlans, VLAN_N_VID) अणु
		अगर (i >= list_size)
			अवरोध;
		vlans[i++] = vlan;
	पूर्ण

	err = mlx5_modअगरy_nic_vport_vlans(priv->mdev, vlans, list_size);
	अगर (err)
		netdev_err(ndev, "Failed to modify vport vlans list err(%d)\n",
			   err);

	kमुक्त(vlans);
	वापस err;
पूर्ण

क्रमागत mlx5e_vlan_rule_type अणु
	MLX5E_VLAN_RULE_TYPE_UNTAGGED,
	MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID,
	MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID,
	MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID,
	MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID,
पूर्ण;

अटल पूर्णांक __mlx5e_add_vlan_rule(काष्ठा mlx5e_priv *priv,
				 क्रमागत mlx5e_vlan_rule_type rule_type,
				 u16 vid, काष्ठा mlx5_flow_spec *spec)
अणु
	काष्ठा mlx5_flow_table *ft = priv->fs.vlan->ft.t;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_handle **rule_p;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	पूर्णांक err = 0;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = priv->fs.l2.ft.t;

	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;

	चयन (rule_type) अणु
	हाल MLX5E_VLAN_RULE_TYPE_UNTAGGED:
		/* cvlan_tag enabled in match criteria and
		 * disabled in match value means both S & C tags
		 * करोn't exist (untagged of both)
		 */
		rule_p = &priv->fs.vlan->untagged_rule;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.cvlan_tag);
		अवरोध;
	हाल MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID:
		rule_p = &priv->fs.vlan->any_cvlan_rule;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.cvlan_tag);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.cvlan_tag, 1);
		अवरोध;
	हाल MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID:
		rule_p = &priv->fs.vlan->any_svlan_rule;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.svlan_tag);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.svlan_tag, 1);
		अवरोध;
	हाल MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID:
		rule_p = &priv->fs.vlan->active_svlans_rule[vid];
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.svlan_tag);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.svlan_tag, 1);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.first_vid);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.first_vid,
			 vid);
		अवरोध;
	शेष: /* MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID */
		rule_p = &priv->fs.vlan->active_cvlans_rule[vid];
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.cvlan_tag);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.cvlan_tag, 1);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.first_vid);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.first_vid,
			 vid);
		अवरोध;
	पूर्ण

	अगर (WARN_ONCE(*rule_p, "VLAN rule already exists type %d", rule_type))
		वापस 0;

	*rule_p = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);

	अगर (IS_ERR(*rule_p)) अणु
		err = PTR_ERR(*rule_p);
		*rule_p = शून्य;
		netdev_err(priv->netdev, "%s: add rule failed\n", __func__);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_add_vlan_rule(काष्ठा mlx5e_priv *priv,
			       क्रमागत mlx5e_vlan_rule_type rule_type, u16 vid)
अणु
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	अगर (rule_type == MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID)
		mlx5e_vport_context_update_vlans(priv);

	err = __mlx5e_add_vlan_rule(priv, rule_type, vid, spec);

	kvमुक्त(spec);

	वापस err;
पूर्ण

अटल व्योम mlx5e_del_vlan_rule(काष्ठा mlx5e_priv *priv,
				क्रमागत mlx5e_vlan_rule_type rule_type, u16 vid)
अणु
	चयन (rule_type) अणु
	हाल MLX5E_VLAN_RULE_TYPE_UNTAGGED:
		अगर (priv->fs.vlan->untagged_rule) अणु
			mlx5_del_flow_rules(priv->fs.vlan->untagged_rule);
			priv->fs.vlan->untagged_rule = शून्य;
		पूर्ण
		अवरोध;
	हाल MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID:
		अगर (priv->fs.vlan->any_cvlan_rule) अणु
			mlx5_del_flow_rules(priv->fs.vlan->any_cvlan_rule);
			priv->fs.vlan->any_cvlan_rule = शून्य;
		पूर्ण
		अवरोध;
	हाल MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID:
		अगर (priv->fs.vlan->any_svlan_rule) अणु
			mlx5_del_flow_rules(priv->fs.vlan->any_svlan_rule);
			priv->fs.vlan->any_svlan_rule = शून्य;
		पूर्ण
		अवरोध;
	हाल MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID:
		अगर (priv->fs.vlan->active_svlans_rule[vid]) अणु
			mlx5_del_flow_rules(priv->fs.vlan->active_svlans_rule[vid]);
			priv->fs.vlan->active_svlans_rule[vid] = शून्य;
		पूर्ण
		अवरोध;
	हाल MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID:
		अगर (priv->fs.vlan->active_cvlans_rule[vid]) अणु
			mlx5_del_flow_rules(priv->fs.vlan->active_cvlans_rule[vid]);
			priv->fs.vlan->active_cvlans_rule[vid] = शून्य;
		पूर्ण
		mlx5e_vport_context_update_vlans(priv);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_del_any_vid_rules(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID, 0);
	mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID, 0);
पूर्ण

अटल पूर्णांक mlx5e_add_any_vid_rules(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err;

	err = mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID, 0);
	अगर (err)
		वापस err;

	वापस mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID, 0);
पूर्ण

अटल काष्ठा mlx5_flow_handle *
mlx5e_add_trap_rule(काष्ठा mlx5_flow_table *ft, पूर्णांक trap_id, पूर्णांक tir_num)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस ERR_PTR(-ENOMEM);
	spec->flow_context.flags |= FLOW_CONTEXT_HAS_TAG;
	spec->flow_context.flow_tag = trap_id;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dest.tir_num = tir_num;

	rule = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	kvमुक्त(spec);
	वापस rule;
पूर्ण

पूर्णांक mlx5e_add_vlan_trap(काष्ठा mlx5e_priv *priv, पूर्णांक trap_id, पूर्णांक tir_num)
अणु
	काष्ठा mlx5_flow_table *ft = priv->fs.vlan->ft.t;
	काष्ठा mlx5_flow_handle *rule;
	पूर्णांक err;

	rule = mlx5e_add_trap_rule(ft, trap_id, tir_num);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		priv->fs.vlan->trap_rule = शून्य;
		netdev_err(priv->netdev, "%s: add VLAN trap rule failed, err %d\n",
			   __func__, err);
		वापस err;
	पूर्ण
	priv->fs.vlan->trap_rule = rule;
	वापस 0;
पूर्ण

व्योम mlx5e_हटाओ_vlan_trap(काष्ठा mlx5e_priv *priv)
अणु
	अगर (priv->fs.vlan->trap_rule) अणु
		mlx5_del_flow_rules(priv->fs.vlan->trap_rule);
		priv->fs.vlan->trap_rule = शून्य;
	पूर्ण
पूर्ण

पूर्णांक mlx5e_add_mac_trap(काष्ठा mlx5e_priv *priv, पूर्णांक trap_id, पूर्णांक tir_num)
अणु
	काष्ठा mlx5_flow_table *ft = priv->fs.l2.ft.t;
	काष्ठा mlx5_flow_handle *rule;
	पूर्णांक err;

	rule = mlx5e_add_trap_rule(ft, trap_id, tir_num);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		priv->fs.l2.trap_rule = शून्य;
		netdev_err(priv->netdev, "%s: add MAC trap rule failed, err %d\n",
			   __func__, err);
		वापस err;
	पूर्ण
	priv->fs.l2.trap_rule = rule;
	वापस 0;
पूर्ण

व्योम mlx5e_हटाओ_mac_trap(काष्ठा mlx5e_priv *priv)
अणु
	अगर (priv->fs.l2.trap_rule) अणु
		mlx5_del_flow_rules(priv->fs.l2.trap_rule);
		priv->fs.l2.trap_rule = शून्य;
	पूर्ण
पूर्ण

व्योम mlx5e_enable_cvlan_filter(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!priv->fs.vlan->cvlan_filter_disabled)
		वापस;

	priv->fs.vlan->cvlan_filter_disabled = false;
	अगर (priv->netdev->flags & IFF_PROMISC)
		वापस;
	mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID, 0);
पूर्ण

व्योम mlx5e_disable_cvlan_filter(काष्ठा mlx5e_priv *priv)
अणु
	अगर (priv->fs.vlan->cvlan_filter_disabled)
		वापस;

	priv->fs.vlan->cvlan_filter_disabled = true;
	अगर (priv->netdev->flags & IFF_PROMISC)
		वापस;
	mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID, 0);
पूर्ण

अटल पूर्णांक mlx5e_vlan_rx_add_cvid(काष्ठा mlx5e_priv *priv, u16 vid)
अणु
	पूर्णांक err;

	set_bit(vid, priv->fs.vlan->active_cvlans);

	err = mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID, vid);
	अगर (err)
		clear_bit(vid, priv->fs.vlan->active_cvlans);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_vlan_rx_add_svid(काष्ठा mlx5e_priv *priv, u16 vid)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	पूर्णांक err;

	set_bit(vid, priv->fs.vlan->active_svlans);

	err = mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID, vid);
	अगर (err) अणु
		clear_bit(vid, priv->fs.vlan->active_svlans);
		वापस err;
	पूर्ण

	/* Need to fix some features.. */
	netdev_update_features(netdev);
	वापस err;
पूर्ण

पूर्णांक mlx5e_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	अगर (mlx5e_is_uplink_rep(priv))
		वापस 0; /* no vlan table क्रम uplink rep */

	अगर (be16_to_cpu(proto) == ETH_P_8021Q)
		वापस mlx5e_vlan_rx_add_cvid(priv, vid);
	अन्यथा अगर (be16_to_cpu(proto) == ETH_P_8021AD)
		वापस mlx5e_vlan_rx_add_svid(priv, vid);

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक mlx5e_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	अगर (mlx5e_is_uplink_rep(priv))
		वापस 0; /* no vlan table क्रम uplink rep */

	अगर (be16_to_cpu(proto) == ETH_P_8021Q) अणु
		clear_bit(vid, priv->fs.vlan->active_cvlans);
		mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID, vid);
	पूर्ण अन्यथा अगर (be16_to_cpu(proto) == ETH_P_8021AD) अणु
		clear_bit(vid, priv->fs.vlan->active_svlans);
		mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID, vid);
		netdev_update_features(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5e_add_vlan_rules(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक i;

	mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_UNTAGGED, 0);

	क्रम_each_set_bit(i, priv->fs.vlan->active_cvlans, VLAN_N_VID) अणु
		mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID, i);
	पूर्ण

	क्रम_each_set_bit(i, priv->fs.vlan->active_svlans, VLAN_N_VID)
		mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID, i);

	अगर (priv->fs.vlan->cvlan_filter_disabled)
		mlx5e_add_any_vid_rules(priv);
पूर्ण

अटल व्योम mlx5e_del_vlan_rules(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक i;

	mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_UNTAGGED, 0);

	क्रम_each_set_bit(i, priv->fs.vlan->active_cvlans, VLAN_N_VID) अणु
		mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID, i);
	पूर्ण

	क्रम_each_set_bit(i, priv->fs.vlan->active_svlans, VLAN_N_VID)
		mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID, i);

	WARN_ON_ONCE(!(test_bit(MLX5E_STATE_DESTROYING, &priv->state)));

	mlx5e_हटाओ_vlan_trap(priv);

	/* must be called after DESTROY bit is set and
	 * set_rx_mode is called and flushed
	 */
	अगर (priv->fs.vlan->cvlan_filter_disabled)
		mlx5e_del_any_vid_rules(priv);
पूर्ण

#घोषणा mlx5e_क्रम_each_hash_node(hn, पंचांगp, hash, i) \
	क्रम (i = 0; i < MLX5E_L2_ADDR_HASH_SIZE; i++) \
		hlist_क्रम_each_entry_safe(hn, पंचांगp, &hash[i], hlist)

अटल व्योम mlx5e_execute_l2_action(काष्ठा mlx5e_priv *priv,
				    काष्ठा mlx5e_l2_hash_node *hn)
अणु
	u8 action = hn->action;
	u8 mac_addr[ETH_ALEN];
	पूर्णांक l2_err = 0;

	ether_addr_copy(mac_addr, hn->ai.addr);

	चयन (action) अणु
	हाल MLX5E_ACTION_ADD:
		mlx5e_add_l2_flow_rule(priv, &hn->ai, MLX5E_FULLMATCH);
		अगर (!is_multicast_ether_addr(mac_addr)) अणु
			l2_err = mlx5_mpfs_add_mac(priv->mdev, mac_addr);
			hn->mpfs = !l2_err;
		पूर्ण
		hn->action = MLX5E_ACTION_NONE;
		अवरोध;

	हाल MLX5E_ACTION_DEL:
		अगर (!is_multicast_ether_addr(mac_addr) && hn->mpfs)
			l2_err = mlx5_mpfs_del_mac(priv->mdev, mac_addr);
		mlx5e_del_l2_flow_rule(priv, &hn->ai);
		mlx5e_del_l2_from_hash(hn);
		अवरोध;
	पूर्ण

	अगर (l2_err)
		netdev_warn(priv->netdev, "MPFS, failed to %s mac %pM, err(%d)\n",
			    action == MLX5E_ACTION_ADD ? "add" : "del", mac_addr, l2_err);
पूर्ण

अटल व्योम mlx5e_sync_netdev_addr(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा netdev_hw_addr *ha;

	netअगर_addr_lock_bh(netdev);

	mlx5e_add_l2_to_hash(priv->fs.l2.netdev_uc,
			     priv->netdev->dev_addr);

	netdev_क्रम_each_uc_addr(ha, netdev)
		mlx5e_add_l2_to_hash(priv->fs.l2.netdev_uc, ha->addr);

	netdev_क्रम_each_mc_addr(ha, netdev)
		mlx5e_add_l2_to_hash(priv->fs.l2.netdev_mc, ha->addr);

	netअगर_addr_unlock_bh(netdev);
पूर्ण

अटल व्योम mlx5e_fill_addr_array(काष्ठा mlx5e_priv *priv, पूर्णांक list_type,
				  u8 addr_array[][ETH_ALEN], पूर्णांक size)
अणु
	bool is_uc = (list_type == MLX5_NVPRT_LIST_TYPE_UC);
	काष्ठा net_device *ndev = priv->netdev;
	काष्ठा mlx5e_l2_hash_node *hn;
	काष्ठा hlist_head *addr_list;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i = 0;
	पूर्णांक hi;

	addr_list = is_uc ? priv->fs.l2.netdev_uc : priv->fs.l2.netdev_mc;

	अगर (is_uc) /* Make sure our own address is pushed first */
		ether_addr_copy(addr_array[i++], ndev->dev_addr);
	अन्यथा अगर (priv->fs.l2.broadcast_enabled)
		ether_addr_copy(addr_array[i++], ndev->broadcast);

	mlx5e_क्रम_each_hash_node(hn, पंचांगp, addr_list, hi) अणु
		अगर (ether_addr_equal(ndev->dev_addr, hn->ai.addr))
			जारी;
		अगर (i >= size)
			अवरोध;
		ether_addr_copy(addr_array[i++], hn->ai.addr);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_vport_context_update_addr_list(काष्ठा mlx5e_priv *priv,
						 पूर्णांक list_type)
अणु
	bool is_uc = (list_type == MLX5_NVPRT_LIST_TYPE_UC);
	काष्ठा mlx5e_l2_hash_node *hn;
	u8 (*addr_array)[ETH_ALEN] = शून्य;
	काष्ठा hlist_head *addr_list;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक max_size;
	पूर्णांक size;
	पूर्णांक err;
	पूर्णांक hi;

	size = is_uc ? 0 : (priv->fs.l2.broadcast_enabled ? 1 : 0);
	max_size = is_uc ?
		1 << MLX5_CAP_GEN(priv->mdev, log_max_current_uc_list) :
		1 << MLX5_CAP_GEN(priv->mdev, log_max_current_mc_list);

	addr_list = is_uc ? priv->fs.l2.netdev_uc : priv->fs.l2.netdev_mc;
	mlx5e_क्रम_each_hash_node(hn, पंचांगp, addr_list, hi)
		size++;

	अगर (size > max_size) अणु
		netdev_warn(priv->netdev,
			    "netdev %s list size (%d) > (%d) max vport list size, some addresses will be dropped\n",
			    is_uc ? "UC" : "MC", size, max_size);
		size = max_size;
	पूर्ण

	अगर (size) अणु
		addr_array = kसुस्मृति(size, ETH_ALEN, GFP_KERNEL);
		अगर (!addr_array) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		mlx5e_fill_addr_array(priv, list_type, addr_array, size);
	पूर्ण

	err = mlx5_modअगरy_nic_vport_mac_list(priv->mdev, list_type, addr_array, size);
out:
	अगर (err)
		netdev_err(priv->netdev,
			   "Failed to modify vport %s list err(%d)\n",
			   is_uc ? "UC" : "MC", err);
	kमुक्त(addr_array);
पूर्ण

अटल व्योम mlx5e_vport_context_update(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_l2_table *ea = &priv->fs.l2;

	mlx5e_vport_context_update_addr_list(priv, MLX5_NVPRT_LIST_TYPE_UC);
	mlx5e_vport_context_update_addr_list(priv, MLX5_NVPRT_LIST_TYPE_MC);
	mlx5_modअगरy_nic_vport_promisc(priv->mdev, 0,
				      ea->allmulti_enabled,
				      ea->promisc_enabled);
पूर्ण

अटल व्योम mlx5e_apply_netdev_addr(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_l2_hash_node *hn;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	mlx5e_क्रम_each_hash_node(hn, पंचांगp, priv->fs.l2.netdev_uc, i)
		mlx5e_execute_l2_action(priv, hn);

	mlx5e_क्रम_each_hash_node(hn, पंचांगp, priv->fs.l2.netdev_mc, i)
		mlx5e_execute_l2_action(priv, hn);
पूर्ण

अटल व्योम mlx5e_handle_netdev_addr(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_l2_hash_node *hn;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	mlx5e_क्रम_each_hash_node(hn, पंचांगp, priv->fs.l2.netdev_uc, i)
		hn->action = MLX5E_ACTION_DEL;
	mlx5e_क्रम_each_hash_node(hn, पंचांगp, priv->fs.l2.netdev_mc, i)
		hn->action = MLX5E_ACTION_DEL;

	अगर (!test_bit(MLX5E_STATE_DESTROYING, &priv->state))
		mlx5e_sync_netdev_addr(priv);

	mlx5e_apply_netdev_addr(priv);
पूर्ण

#घोषणा MLX5E_PROMISC_GROUP0_SIZE BIT(0)
#घोषणा MLX5E_PROMISC_TABLE_SIZE MLX5E_PROMISC_GROUP0_SIZE

अटल पूर्णांक mlx5e_add_promisc_rule(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_flow_table *ft = priv->fs.promisc.ft.t;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_handle **rule_p;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = priv->fs.ttc.ft.t;

	rule_p = &priv->fs.promisc.rule;
	*rule_p = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	अगर (IS_ERR(*rule_p)) अणु
		err = PTR_ERR(*rule_p);
		*rule_p = शून्य;
		netdev_err(priv->netdev, "%s: add promiscuous rule failed\n", __func__);
	पूर्ण
	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_create_promisc_table(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_flow_table *ft = &priv->fs.promisc.ft;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	पूर्णांक err;

	ft_attr.max_fte = MLX5E_PROMISC_TABLE_SIZE;
	ft_attr.स्वतःgroup.max_num_groups = 1;
	ft_attr.level = MLX5E_PROMISC_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;

	ft->t = mlx5_create_स्वतः_grouped_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		netdev_err(priv->netdev, "fail to create promisc table err=%d\n", err);
		वापस err;
	पूर्ण

	err = mlx5e_add_promisc_rule(priv);
	अगर (err)
		जाओ err_destroy_promisc_table;

	वापस 0;

err_destroy_promisc_table:
	mlx5_destroy_flow_table(ft->t);
	ft->t = शून्य;

	वापस err;
पूर्ण

अटल व्योम mlx5e_del_promisc_rule(काष्ठा mlx5e_priv *priv)
अणु
	अगर (WARN(!priv->fs.promisc.rule, "Trying to remove non-existing promiscuous rule"))
		वापस;
	mlx5_del_flow_rules(priv->fs.promisc.rule);
	priv->fs.promisc.rule = शून्य;
पूर्ण

अटल व्योम mlx5e_destroy_promisc_table(काष्ठा mlx5e_priv *priv)
अणु
	अगर (WARN(!priv->fs.promisc.ft.t, "Trying to remove non-existing promiscuous table"))
		वापस;
	mlx5e_del_promisc_rule(priv);
	mlx5_destroy_flow_table(priv->fs.promisc.ft.t);
	priv->fs.promisc.ft.t = शून्य;
पूर्ण

व्योम mlx5e_set_rx_mode_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_priv *priv = container_of(work, काष्ठा mlx5e_priv,
					       set_rx_mode_work);

	काष्ठा mlx5e_l2_table *ea = &priv->fs.l2;
	काष्ठा net_device *ndev = priv->netdev;

	bool rx_mode_enable   = !test_bit(MLX5E_STATE_DESTROYING, &priv->state);
	bool promisc_enabled   = rx_mode_enable && (ndev->flags & IFF_PROMISC);
	bool allmulti_enabled  = rx_mode_enable && (ndev->flags & IFF_ALLMULTI);
	bool broadcast_enabled = rx_mode_enable;

	bool enable_promisc    = !ea->promisc_enabled   &&  promisc_enabled;
	bool disable_promisc   =  ea->promisc_enabled   && !promisc_enabled;
	bool enable_allmulti   = !ea->allmulti_enabled  &&  allmulti_enabled;
	bool disable_allmulti  =  ea->allmulti_enabled  && !allmulti_enabled;
	bool enable_broadcast  = !ea->broadcast_enabled &&  broadcast_enabled;
	bool disable_broadcast =  ea->broadcast_enabled && !broadcast_enabled;
	पूर्णांक err;

	अगर (enable_promisc) अणु
		err = mlx5e_create_promisc_table(priv);
		अगर (err)
			enable_promisc = false;
		अगर (!priv->channels.params.vlan_strip_disable && !err)
			netdev_warn_once(ndev,
					 "S-tagged traffic will be dropped while C-tag vlan stripping is enabled\n");
	पूर्ण
	अगर (enable_allmulti)
		mlx5e_add_l2_flow_rule(priv, &ea->allmulti, MLX5E_ALLMULTI);
	अगर (enable_broadcast)
		mlx5e_add_l2_flow_rule(priv, &ea->broadcast, MLX5E_FULLMATCH);

	mlx5e_handle_netdev_addr(priv);

	अगर (disable_broadcast)
		mlx5e_del_l2_flow_rule(priv, &ea->broadcast);
	अगर (disable_allmulti)
		mlx5e_del_l2_flow_rule(priv, &ea->allmulti);
	अगर (disable_promisc)
		mlx5e_destroy_promisc_table(priv);

	ea->promisc_enabled   = promisc_enabled;
	ea->allmulti_enabled  = allmulti_enabled;
	ea->broadcast_enabled = broadcast_enabled;

	mlx5e_vport_context_update(priv);
पूर्ण

अटल व्योम mlx5e_destroy_groups(काष्ठा mlx5e_flow_table *ft)
अणु
	पूर्णांक i;

	क्रम (i = ft->num_groups - 1; i >= 0; i--) अणु
		अगर (!IS_ERR_OR_शून्य(ft->g[i]))
			mlx5_destroy_flow_group(ft->g[i]);
		ft->g[i] = शून्य;
	पूर्ण
	ft->num_groups = 0;
पूर्ण

व्योम mlx5e_init_l2_addr(काष्ठा mlx5e_priv *priv)
अणु
	ether_addr_copy(priv->fs.l2.broadcast.addr, priv->netdev->broadcast);
पूर्ण

व्योम mlx5e_destroy_flow_table(काष्ठा mlx5e_flow_table *ft)
अणु
	mlx5e_destroy_groups(ft);
	kमुक्त(ft->g);
	mlx5_destroy_flow_table(ft->t);
	ft->t = शून्य;
पूर्ण

अटल व्योम mlx5e_cleanup_ttc_rules(काष्ठा mlx5e_ttc_table *ttc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5E_NUM_TT; i++) अणु
		अगर (!IS_ERR_OR_शून्य(ttc->rules[i].rule)) अणु
			mlx5_del_flow_rules(ttc->rules[i].rule);
			ttc->rules[i].rule = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MLX5E_NUM_TUNNEL_TT; i++) अणु
		अगर (!IS_ERR_OR_शून्य(ttc->tunnel_rules[i])) अणु
			mlx5_del_flow_rules(ttc->tunnel_rules[i]);
			ttc->tunnel_rules[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा mlx5e_etype_proto अणु
	u16 etype;
	u8 proto;
पूर्ण;

अटल काष्ठा mlx5e_etype_proto ttc_rules[] = अणु
	[MLX5E_TT_IPV4_TCP] = अणु
		.etype = ETH_P_IP,
		.proto = IPPROTO_TCP,
	पूर्ण,
	[MLX5E_TT_IPV6_TCP] = अणु
		.etype = ETH_P_IPV6,
		.proto = IPPROTO_TCP,
	पूर्ण,
	[MLX5E_TT_IPV4_UDP] = अणु
		.etype = ETH_P_IP,
		.proto = IPPROTO_UDP,
	पूर्ण,
	[MLX5E_TT_IPV6_UDP] = अणु
		.etype = ETH_P_IPV6,
		.proto = IPPROTO_UDP,
	पूर्ण,
	[MLX5E_TT_IPV4_IPSEC_AH] = अणु
		.etype = ETH_P_IP,
		.proto = IPPROTO_AH,
	पूर्ण,
	[MLX5E_TT_IPV6_IPSEC_AH] = अणु
		.etype = ETH_P_IPV6,
		.proto = IPPROTO_AH,
	पूर्ण,
	[MLX5E_TT_IPV4_IPSEC_ESP] = अणु
		.etype = ETH_P_IP,
		.proto = IPPROTO_ESP,
	पूर्ण,
	[MLX5E_TT_IPV6_IPSEC_ESP] = अणु
		.etype = ETH_P_IPV6,
		.proto = IPPROTO_ESP,
	पूर्ण,
	[MLX5E_TT_IPV4] = अणु
		.etype = ETH_P_IP,
		.proto = 0,
	पूर्ण,
	[MLX5E_TT_IPV6] = अणु
		.etype = ETH_P_IPV6,
		.proto = 0,
	पूर्ण,
	[MLX5E_TT_ANY] = अणु
		.etype = 0,
		.proto = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा mlx5e_etype_proto ttc_tunnel_rules[] = अणु
	[MLX5E_TT_IPV4_GRE] = अणु
		.etype = ETH_P_IP,
		.proto = IPPROTO_GRE,
	पूर्ण,
	[MLX5E_TT_IPV6_GRE] = अणु
		.etype = ETH_P_IPV6,
		.proto = IPPROTO_GRE,
	पूर्ण,
	[MLX5E_TT_IPV4_IPIP] = अणु
		.etype = ETH_P_IP,
		.proto = IPPROTO_IPIP,
	पूर्ण,
	[MLX5E_TT_IPV6_IPIP] = अणु
		.etype = ETH_P_IPV6,
		.proto = IPPROTO_IPIP,
	पूर्ण,
	[MLX5E_TT_IPV4_IPV6] = अणु
		.etype = ETH_P_IP,
		.proto = IPPROTO_IPV6,
	पूर्ण,
	[MLX5E_TT_IPV6_IPV6] = अणु
		.etype = ETH_P_IPV6,
		.proto = IPPROTO_IPV6,
	पूर्ण,

पूर्ण;

u8 mlx5e_get_proto_by_tunnel_type(क्रमागत mlx5e_tunnel_types tt)
अणु
	वापस ttc_tunnel_rules[tt].proto;
पूर्ण

अटल bool mlx5e_tunnel_proto_supported_rx(काष्ठा mlx5_core_dev *mdev, u8 proto_type)
अणु
	चयन (proto_type) अणु
	हाल IPPROTO_GRE:
		वापस MLX5_CAP_ETH(mdev, tunnel_stateless_gre);
	हाल IPPROTO_IPIP:
	हाल IPPROTO_IPV6:
		वापस (MLX5_CAP_ETH(mdev, tunnel_stateless_ip_over_ip) ||
			MLX5_CAP_ETH(mdev, tunnel_stateless_ip_over_ip_rx));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mlx5e_tunnel_any_rx_proto_supported(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक tt;

	क्रम (tt = 0; tt < MLX5E_NUM_TUNNEL_TT; tt++) अणु
		अगर (mlx5e_tunnel_proto_supported_rx(mdev, ttc_tunnel_rules[tt].proto))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool mlx5e_tunnel_inner_ft_supported(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस (mlx5e_tunnel_any_rx_proto_supported(mdev) &&
		MLX5_CAP_FLOWTABLE_NIC_RX(mdev, ft_field_support.inner_ip_version));
पूर्ण

अटल u8 mlx5e_etype_to_ipv(u16 ethertype)
अणु
	अगर (ethertype == ETH_P_IP)
		वापस 4;

	अगर (ethertype == ETH_P_IPV6)
		वापस 6;

	वापस 0;
पूर्ण

अटल काष्ठा mlx5_flow_handle *
mlx5e_generate_ttc_rule(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5_flow_table *ft,
			काष्ठा mlx5_flow_destination *dest,
			u16 etype,
			u8 proto)
अणु
	पूर्णांक match_ipv_outer = MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, ft_field_support.outer_ip_version);
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;
	u8 ipv;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस ERR_PTR(-ENOMEM);

	अगर (proto) अणु
		spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ip_protocol);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.ip_protocol, proto);
	पूर्ण

	ipv = mlx5e_etype_to_ipv(etype);
	अगर (match_ipv_outer && ipv) अणु
		spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ip_version);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.ip_version, ipv);
	पूर्ण अन्यथा अगर (etype) अणु
		spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.ethertype);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.ethertype, etype);
	पूर्ण

	rule = mlx5_add_flow_rules(ft, spec, &flow_act, dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev, "%s: add rule failed\n", __func__);
	पूर्ण

	kvमुक्त(spec);
	वापस err ? ERR_PTR(err) : rule;
पूर्ण

अटल पूर्णांक mlx5e_generate_ttc_table_rules(काष्ठा mlx5e_priv *priv,
					  काष्ठा ttc_params *params,
					  काष्ठा mlx5e_ttc_table *ttc)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_handle **trules;
	काष्ठा mlx5e_ttc_rule *rules;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक tt;
	पूर्णांक err;

	ft = ttc->ft.t;
	rules = ttc->rules;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	क्रम (tt = 0; tt < MLX5E_NUM_TT; tt++) अणु
		काष्ठा mlx5e_ttc_rule *rule = &rules[tt];

		अगर (tt == MLX5E_TT_ANY)
			dest.tir_num = params->any_tt_tirn;
		अन्यथा
			dest.tir_num = params->indir_tirn[tt];

		rule->rule = mlx5e_generate_ttc_rule(priv, ft, &dest,
						     ttc_rules[tt].etype,
						     ttc_rules[tt].proto);
		अगर (IS_ERR(rule->rule)) अणु
			err = PTR_ERR(rule->rule);
			rule->rule = शून्य;
			जाओ del_rules;
		पूर्ण
		rule->शेष_dest = dest;
	पूर्ण

	अगर (!params->inner_ttc || !mlx5e_tunnel_inner_ft_supported(priv->mdev))
		वापस 0;

	trules    = ttc->tunnel_rules;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft   = params->inner_ttc->ft.t;
	क्रम (tt = 0; tt < MLX5E_NUM_TUNNEL_TT; tt++) अणु
		अगर (!mlx5e_tunnel_proto_supported_rx(priv->mdev,
						     ttc_tunnel_rules[tt].proto))
			जारी;
		trules[tt] = mlx5e_generate_ttc_rule(priv, ft, &dest,
						     ttc_tunnel_rules[tt].etype,
						     ttc_tunnel_rules[tt].proto);
		अगर (IS_ERR(trules[tt])) अणु
			err = PTR_ERR(trules[tt]);
			trules[tt] = शून्य;
			जाओ del_rules;
		पूर्ण
	पूर्ण

	वापस 0;

del_rules:
	mlx5e_cleanup_ttc_rules(ttc);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_create_ttc_table_groups(काष्ठा mlx5e_ttc_table *ttc,
					 bool use_ipv)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5e_flow_table *ft = &ttc->ft;
	पूर्णांक ix = 0;
	u32 *in;
	पूर्णांक err;
	u8 *mc;

	ft->g = kसुस्मृति(MLX5E_TTC_NUM_GROUPS,
			माप(*ft->g), GFP_KERNEL);
	अगर (!ft->g)
		वापस -ENOMEM;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		kमुक्त(ft->g);
		ft->g = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/* L4 Group */
	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.ip_protocol);
	अगर (use_ipv)
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.ip_version);
	अन्यथा
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.ethertype);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_TTC_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	/* L3 Group */
	MLX5_SET(fte_match_param, mc, outer_headers.ip_protocol, 0);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_TTC_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	/* Any Group */
	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_TTC_GROUP3_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	kvमुक्त(in);
	वापस 0;

err:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = शून्य;
	kvमुक्त(in);

	वापस err;
पूर्ण

अटल काष्ठा mlx5_flow_handle *
mlx5e_generate_inner_ttc_rule(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5_flow_table *ft,
			      काष्ठा mlx5_flow_destination *dest,
			      u16 etype, u8 proto)
अणु
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;
	u8 ipv;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस ERR_PTR(-ENOMEM);

	ipv = mlx5e_etype_to_ipv(etype);
	अगर (etype && ipv) अणु
		spec->match_criteria_enable = MLX5_MATCH_INNER_HEADERS;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, inner_headers.ip_version);
		MLX5_SET(fte_match_param, spec->match_value, inner_headers.ip_version, ipv);
	पूर्ण

	अगर (proto) अणु
		spec->match_criteria_enable = MLX5_MATCH_INNER_HEADERS;
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, inner_headers.ip_protocol);
		MLX5_SET(fte_match_param, spec->match_value, inner_headers.ip_protocol, proto);
	पूर्ण

	rule = mlx5_add_flow_rules(ft, spec, &flow_act, dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev, "%s: add rule failed\n", __func__);
	पूर्ण

	kvमुक्त(spec);
	वापस err ? ERR_PTR(err) : rule;
पूर्ण

अटल पूर्णांक mlx5e_generate_inner_ttc_table_rules(काष्ठा mlx5e_priv *priv,
						काष्ठा ttc_params *params,
						काष्ठा mlx5e_ttc_table *ttc)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5e_ttc_rule *rules;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक err;
	पूर्णांक tt;

	ft = ttc->ft.t;
	rules = ttc->rules;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;

	क्रम (tt = 0; tt < MLX5E_NUM_TT; tt++) अणु
		काष्ठा mlx5e_ttc_rule *rule = &rules[tt];

		अगर (tt == MLX5E_TT_ANY)
			dest.tir_num = params->any_tt_tirn;
		अन्यथा
			dest.tir_num = params->indir_tirn[tt];

		rule->rule = mlx5e_generate_inner_ttc_rule(priv, ft, &dest,
							   ttc_rules[tt].etype,
							   ttc_rules[tt].proto);
		अगर (IS_ERR(rule->rule)) अणु
			err = PTR_ERR(rule->rule);
			rule->rule = शून्य;
			जाओ del_rules;
		पूर्ण
		rule->शेष_dest = dest;
	पूर्ण

	वापस 0;

del_rules:

	mlx5e_cleanup_ttc_rules(ttc);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_create_inner_ttc_table_groups(काष्ठा mlx5e_ttc_table *ttc)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5e_flow_table *ft = &ttc->ft;
	पूर्णांक ix = 0;
	u32 *in;
	पूर्णांक err;
	u8 *mc;

	ft->g = kसुस्मृति(MLX5E_INNER_TTC_NUM_GROUPS, माप(*ft->g), GFP_KERNEL);
	अगर (!ft->g)
		वापस -ENOMEM;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		kमुक्त(ft->g);
		ft->g = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/* L4 Group */
	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	MLX5_SET_TO_ONES(fte_match_param, mc, inner_headers.ip_protocol);
	MLX5_SET_TO_ONES(fte_match_param, mc, inner_headers.ip_version);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_INNER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_INNER_TTC_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	/* L3 Group */
	MLX5_SET(fte_match_param, mc, inner_headers.ip_protocol, 0);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_INNER_TTC_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	/* Any Group */
	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_INNER_TTC_GROUP3_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	kvमुक्त(in);
	वापस 0;

err:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = शून्य;
	kvमुक्त(in);

	वापस err;
पूर्ण

व्योम mlx5e_set_ttc_basic_params(काष्ठा mlx5e_priv *priv,
				काष्ठा ttc_params *ttc_params)
अणु
	ttc_params->any_tt_tirn = priv->direct_tir[0].tirn;
	ttc_params->inner_ttc = &priv->fs.inner_ttc;
पूर्ण

व्योम mlx5e_set_inner_ttc_ft_params(काष्ठा ttc_params *ttc_params)
अणु
	काष्ठा mlx5_flow_table_attr *ft_attr = &ttc_params->ft_attr;

	ft_attr->max_fte = MLX5E_INNER_TTC_TABLE_SIZE;
	ft_attr->level = MLX5E_INNER_TTC_FT_LEVEL;
	ft_attr->prio = MLX5E_NIC_PRIO;
पूर्ण

व्योम mlx5e_set_ttc_ft_params(काष्ठा ttc_params *ttc_params)

अणु
	काष्ठा mlx5_flow_table_attr *ft_attr = &ttc_params->ft_attr;

	ft_attr->max_fte = MLX5E_TTC_TABLE_SIZE;
	ft_attr->level = MLX5E_TTC_FT_LEVEL;
	ft_attr->prio = MLX5E_NIC_PRIO;
पूर्ण

पूर्णांक mlx5e_create_inner_ttc_table(काष्ठा mlx5e_priv *priv, काष्ठा ttc_params *params,
				 काष्ठा mlx5e_ttc_table *ttc)
अणु
	काष्ठा mlx5e_flow_table *ft = &ttc->ft;
	पूर्णांक err;

	अगर (!mlx5e_tunnel_inner_ft_supported(priv->mdev))
		वापस 0;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &params->ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		ft->t = शून्य;
		वापस err;
	पूर्ण

	err = mlx5e_create_inner_ttc_table_groups(ttc);
	अगर (err)
		जाओ err;

	err = mlx5e_generate_inner_ttc_table_rules(priv, params, ttc);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	mlx5e_destroy_flow_table(ft);
	वापस err;
पूर्ण

व्योम mlx5e_destroy_inner_ttc_table(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5e_ttc_table *ttc)
अणु
	अगर (!mlx5e_tunnel_inner_ft_supported(priv->mdev))
		वापस;

	mlx5e_cleanup_ttc_rules(ttc);
	mlx5e_destroy_flow_table(&ttc->ft);
पूर्ण

व्योम mlx5e_destroy_ttc_table(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_ttc_table *ttc)
अणु
	mlx5e_cleanup_ttc_rules(ttc);
	mlx5e_destroy_flow_table(&ttc->ft);
पूर्ण

पूर्णांक mlx5e_create_ttc_table(काष्ठा mlx5e_priv *priv, काष्ठा ttc_params *params,
			   काष्ठा mlx5e_ttc_table *ttc)
अणु
	bool match_ipv_outer = MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, ft_field_support.outer_ip_version);
	काष्ठा mlx5e_flow_table *ft = &ttc->ft;
	पूर्णांक err;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &params->ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		ft->t = शून्य;
		वापस err;
	पूर्ण

	err = mlx5e_create_ttc_table_groups(ttc, match_ipv_outer);
	अगर (err)
		जाओ err;

	err = mlx5e_generate_ttc_table_rules(priv, params, ttc);
	अगर (err)
		जाओ err;

	वापस 0;
err:
	mlx5e_destroy_flow_table(ft);
	वापस err;
पूर्ण

पूर्णांक mlx5e_ttc_fwd_dest(काष्ठा mlx5e_priv *priv, क्रमागत mlx5e_traffic_types type,
		       काष्ठा mlx5_flow_destination *new_dest)
अणु
	वापस mlx5_modअगरy_rule_destination(priv->fs.ttc.rules[type].rule, new_dest, शून्य);
पूर्ण

काष्ठा mlx5_flow_destination
mlx5e_ttc_get_शेष_dest(काष्ठा mlx5e_priv *priv, क्रमागत mlx5e_traffic_types type)
अणु
	काष्ठा mlx5_flow_destination *dest = &priv->fs.ttc.rules[type].शेष_dest;

	WARN_ONCE(dest->type != MLX5_FLOW_DESTINATION_TYPE_TIR,
		  "TTC[%d] default dest is not setup yet", type);

	वापस *dest;
पूर्ण

पूर्णांक mlx5e_ttc_fwd_शेष_dest(काष्ठा mlx5e_priv *priv, क्रमागत mlx5e_traffic_types type)
अणु
	काष्ठा mlx5_flow_destination dest = mlx5e_ttc_get_शेष_dest(priv, type);

	वापस mlx5e_ttc_fwd_dest(priv, type, &dest);
पूर्ण

अटल व्योम mlx5e_del_l2_flow_rule(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5e_l2_rule *ai)
अणु
	अगर (!IS_ERR_OR_शून्य(ai->rule)) अणु
		mlx5_del_flow_rules(ai->rule);
		ai->rule = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_add_l2_flow_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_l2_rule *ai, पूर्णांक type)
अणु
	काष्ठा mlx5_flow_table *ft = priv->fs.l2.ft.t;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;
	u8 *mc_dmac;
	u8 *mv_dmac;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	mc_dmac = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			       outer_headers.dmac_47_16);
	mv_dmac = MLX5_ADDR_OF(fte_match_param, spec->match_value,
			       outer_headers.dmac_47_16);

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = priv->fs.ttc.ft.t;

	चयन (type) अणु
	हाल MLX5E_FULLMATCH:
		spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
		eth_broadcast_addr(mc_dmac);
		ether_addr_copy(mv_dmac, ai->addr);
		अवरोध;

	हाल MLX5E_ALLMULTI:
		spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
		mc_dmac[0] = 0x01;
		mv_dmac[0] = 0x01;
		अवरोध;
	पूर्ण

	ai->rule = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	अगर (IS_ERR(ai->rule)) अणु
		netdev_err(priv->netdev, "%s: add l2 rule(mac:%pM) failed\n",
			   __func__, mv_dmac);
		err = PTR_ERR(ai->rule);
		ai->rule = शून्य;
	पूर्ण

	kvमुक्त(spec);

	वापस err;
पूर्ण

#घोषणा MLX5E_NUM_L2_GROUPS	   3
#घोषणा MLX5E_L2_GROUP1_SIZE	   BIT(15)
#घोषणा MLX5E_L2_GROUP2_SIZE	   BIT(0)
#घोषणा MLX5E_L2_GROUP_TRAP_SIZE   BIT(0) /* must be last */
#घोषणा MLX5E_L2_TABLE_SIZE	   (MLX5E_L2_GROUP1_SIZE +\
				    MLX5E_L2_GROUP2_SIZE +\
				    MLX5E_L2_GROUP_TRAP_SIZE)
अटल पूर्णांक mlx5e_create_l2_table_groups(काष्ठा mlx5e_l2_table *l2_table)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5e_flow_table *ft = &l2_table->ft;
	पूर्णांक ix = 0;
	u8 *mc_dmac;
	u32 *in;
	पूर्णांक err;
	u8 *mc;

	ft->g = kसुस्मृति(MLX5E_NUM_L2_GROUPS, माप(*ft->g), GFP_KERNEL);
	अगर (!ft->g)
		वापस -ENOMEM;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		kमुक्त(ft->g);
		वापस -ENOMEM;
	पूर्ण

	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	mc_dmac = MLX5_ADDR_OF(fte_match_param, mc,
			       outer_headers.dmac_47_16);
	/* Flow Group क्रम full match */
	eth_broadcast_addr(mc_dmac);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_L2_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	/* Flow Group क्रम allmulti */
	eth_zero_addr(mc_dmac);
	mc_dmac[0] = 0x01;
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_L2_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	/* Flow Group क्रम l2 traps */
	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_L2_GROUP_TRAP_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	kvमुक्त(in);
	वापस 0;

err_destroy_groups:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = शून्य;
	mlx5e_destroy_groups(ft);
	kvमुक्त(in);
	kमुक्त(ft->g);

	वापस err;
पूर्ण

अटल व्योम mlx5e_destroy_l2_table(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_destroy_flow_table(&priv->fs.l2.ft);
पूर्ण

अटल पूर्णांक mlx5e_create_l2_table(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_l2_table *l2_table = &priv->fs.l2;
	काष्ठा mlx5e_flow_table *ft = &l2_table->ft;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	पूर्णांक err;

	ft->num_groups = 0;

	ft_attr.max_fte = MLX5E_L2_TABLE_SIZE;
	ft_attr.level = MLX5E_L2_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		ft->t = शून्य;
		वापस err;
	पूर्ण

	err = mlx5e_create_l2_table_groups(l2_table);
	अगर (err)
		जाओ err_destroy_flow_table;

	वापस 0;

err_destroy_flow_table:
	mlx5_destroy_flow_table(ft->t);
	ft->t = शून्य;

	वापस err;
पूर्ण

#घोषणा MLX5E_NUM_VLAN_GROUPS	5
#घोषणा MLX5E_VLAN_GROUP0_SIZE	BIT(12)
#घोषणा MLX5E_VLAN_GROUP1_SIZE	BIT(12)
#घोषणा MLX5E_VLAN_GROUP2_SIZE	BIT(1)
#घोषणा MLX5E_VLAN_GROUP3_SIZE	BIT(0)
#घोषणा MLX5E_VLAN_GROUP_TRAP_SIZE BIT(0) /* must be last */
#घोषणा MLX5E_VLAN_TABLE_SIZE	(MLX5E_VLAN_GROUP0_SIZE +\
				 MLX5E_VLAN_GROUP1_SIZE +\
				 MLX5E_VLAN_GROUP2_SIZE +\
				 MLX5E_VLAN_GROUP3_SIZE +\
				 MLX5E_VLAN_GROUP_TRAP_SIZE)

अटल पूर्णांक __mlx5e_create_vlan_table_groups(काष्ठा mlx5e_flow_table *ft, u32 *in,
					    पूर्णांक inlen)
अणु
	पूर्णांक err;
	पूर्णांक ix = 0;
	u8 *mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);

	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.first_vid);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_VLAN_GROUP0_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.svlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.first_vid);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_VLAN_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.cvlan_tag);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_VLAN_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.svlan_tag);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_VLAN_GROUP3_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_VLAN_GROUP_TRAP_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err_destroy_groups;
	ft->num_groups++;

	वापस 0;

err_destroy_groups:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = शून्य;
	mlx5e_destroy_groups(ft);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_create_vlan_table_groups(काष्ठा mlx5e_flow_table *ft)
अणु
	u32 *in;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	err = __mlx5e_create_vlan_table_groups(ft, in, inlen);

	kvमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_create_vlan_table(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5e_flow_table *ft;
	पूर्णांक err;

	priv->fs.vlan = kvzalloc(माप(*priv->fs.vlan), GFP_KERNEL);
	अगर (!priv->fs.vlan)
		वापस -ENOMEM;

	ft = &priv->fs.vlan->ft;
	ft->num_groups = 0;

	ft_attr.max_fte = MLX5E_VLAN_TABLE_SIZE;
	ft_attr.level = MLX5E_VLAN_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		जाओ err_मुक्त_t;
	पूर्ण

	ft->g = kसुस्मृति(MLX5E_NUM_VLAN_GROUPS, माप(*ft->g), GFP_KERNEL);
	अगर (!ft->g) अणु
		err = -ENOMEM;
		जाओ err_destroy_vlan_table;
	पूर्ण

	err = mlx5e_create_vlan_table_groups(ft);
	अगर (err)
		जाओ err_मुक्त_g;

	mlx5e_add_vlan_rules(priv);

	वापस 0;

err_मुक्त_g:
	kमुक्त(ft->g);
err_destroy_vlan_table:
	mlx5_destroy_flow_table(ft->t);
err_मुक्त_t:
	kvमुक्त(priv->fs.vlan);
	priv->fs.vlan = शून्य;

	वापस err;
पूर्ण

अटल व्योम mlx5e_destroy_vlan_table(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_del_vlan_rules(priv);
	mlx5e_destroy_flow_table(&priv->fs.vlan->ft);
	kvमुक्त(priv->fs.vlan);
पूर्ण

पूर्णांक mlx5e_create_flow_steering(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा ttc_params ttc_params = अणुपूर्ण;
	पूर्णांक tt, err;

	priv->fs.ns = mlx5_get_flow_namespace(priv->mdev,
					       MLX5_FLOW_NAMESPACE_KERNEL);

	अगर (!priv->fs.ns)
		वापस -EOPNOTSUPP;

	err = mlx5e_arfs_create_tables(priv);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create arfs tables, err=%d\n",
			   err);
		priv->netdev->hw_features &= ~NETIF_F_NTUPLE;
	पूर्ण

	mlx5e_set_ttc_basic_params(priv, &ttc_params);
	mlx5e_set_inner_ttc_ft_params(&ttc_params);
	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		ttc_params.indir_tirn[tt] = priv->inner_indir_tir[tt].tirn;

	err = mlx5e_create_inner_ttc_table(priv, &ttc_params, &priv->fs.inner_ttc);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create inner ttc table, err=%d\n",
			   err);
		जाओ err_destroy_arfs_tables;
	पूर्ण

	mlx5e_set_ttc_ft_params(&ttc_params);
	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		ttc_params.indir_tirn[tt] = priv->indir_tir[tt].tirn;

	err = mlx5e_create_ttc_table(priv, &ttc_params, &priv->fs.ttc);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create ttc table, err=%d\n",
			   err);
		जाओ err_destroy_inner_ttc_table;
	पूर्ण

	err = mlx5e_create_l2_table(priv);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create l2 table, err=%d\n",
			   err);
		जाओ err_destroy_ttc_table;
	पूर्ण

	err = mlx5e_create_vlan_table(priv);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create vlan table, err=%d\n",
			   err);
		जाओ err_destroy_l2_table;
	पूर्ण

	err = mlx5e_ptp_alloc_rx_fs(priv);
	अगर (err)
		जाओ err_destory_vlan_table;

	mlx5e_ethtool_init_steering(priv);

	वापस 0;

err_destory_vlan_table:
	mlx5e_destroy_vlan_table(priv);
err_destroy_l2_table:
	mlx5e_destroy_l2_table(priv);
err_destroy_ttc_table:
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
err_destroy_inner_ttc_table:
	mlx5e_destroy_inner_ttc_table(priv, &priv->fs.inner_ttc);
err_destroy_arfs_tables:
	mlx5e_arfs_destroy_tables(priv);

	वापस err;
पूर्ण

व्योम mlx5e_destroy_flow_steering(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_ptp_मुक्त_rx_fs(priv);
	mlx5e_destroy_vlan_table(priv);
	mlx5e_destroy_l2_table(priv);
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
	mlx5e_destroy_inner_ttc_table(priv, &priv->fs.inner_ttc);
	mlx5e_arfs_destroy_tables(priv);
	mlx5e_ethtool_cleanup_steering(priv);
पूर्ण
