<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
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

#समावेश <net/flow_dissector.h>
#समावेश <net/flow_offload.h>
#समावेश <net/sch_generic.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_skbedit.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/device.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/refcount.h>
#समावेश <linux/completion.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_vlan.h>
#समावेश <net/tc_act/tc_tunnel_key.h>
#समावेश <net/tc_act/tc_pedit.h>
#समावेश <net/tc_act/tc_csum.h>
#समावेश <net/tc_act/tc_mpls.h>
#समावेश <net/psample.h>
#समावेश <net/arp.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/bareudp.h>
#समावेश <net/bonding.h>
#समावेश "en.h"
#समावेश "en_rep.h"
#समावेश "en/rep/tc.h"
#समावेश "en/rep/neigh.h"
#समावेश "en_tc.h"
#समावेश "eswitch.h"
#समावेश "fs_core.h"
#समावेश "en/port.h"
#समावेश "en/tc_tun.h"
#समावेश "en/mapping.h"
#समावेश "en/tc_ct.h"
#समावेश "en/mod_hdr.h"
#समावेश "en/tc_priv.h"
#समावेश "en/tc_tun_encap.h"
#समावेश "esw/sample.h"
#समावेश "lib/devcom.h"
#समावेश "lib/geneve.h"
#समावेश "lib/fs_chains.h"
#समावेश "diag/en_tc_tracepoint.h"
#समावेश <यंत्र/भाग64.h>

#घोषणा nic_chains(priv) ((priv)->fs.tc.chains)
#घोषणा MLX5_MH_ACT_SZ MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः)

#घोषणा MLX5E_TC_TABLE_NUM_GROUPS 4
#घोषणा MLX5E_TC_TABLE_MAX_GROUP_SIZE BIT(18)

काष्ठा mlx5e_tc_attr_to_reg_mapping mlx5e_tc_attr_to_reg_mappings[] = अणु
	[CHAIN_TO_REG] = अणु
		.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_0,
		.moffset = 0,
		.mlen = 2,
	पूर्ण,
	[VPORT_TO_REG] = अणु
		.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_0,
		.moffset = 2,
		.mlen = 2,
	पूर्ण,
	[TUNNEL_TO_REG] = अणु
		.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_C_1,
		.moffset = 1,
		.mlen = ((ESW_TUN_OPTS_BITS + ESW_TUN_ID_BITS) / 8),
		.soffset = MLX5_BYTE_OFF(fte_match_param,
					 misc_parameters_2.metadata_reg_c_1),
	पूर्ण,
	[ZONE_TO_REG] = zone_to_reg_ct,
	[ZONE_RESTORE_TO_REG] = zone_restore_to_reg_ct,
	[CTSTATE_TO_REG] = ctstate_to_reg_ct,
	[MARK_TO_REG] = mark_to_reg_ct,
	[LABELS_TO_REG] = labels_to_reg_ct,
	[FTEID_TO_REG] = fteid_to_reg_ct,
	/* For NIC rules we store the retore metadata directly
	 * पूर्णांकo reg_b that is passed to SW since we करोn't
	 * jump between steering करोमुख्यs.
	 */
	[NIC_CHAIN_TO_REG] = अणु
		.mfield = MLX5_ACTION_IN_FIELD_METADATA_REG_B,
		.moffset = 0,
		.mlen = 2,
	पूर्ण,
	[NIC_ZONE_RESTORE_TO_REG] = nic_zone_restore_to_reg_ct,
पूर्ण;

/* To aव्योम false lock dependency warning set the tc_ht lock
 * class dअगरferent than the lock class of the ht being used when deleting
 * last flow from a group and then deleting a group, we get पूर्णांकo del_sw_flow_group()
 * which call rhashtable_destroy on fg->ftes_hash which will take ht->mutex but
 * it's dअगरferent than the ht->mutex here.
 */
अटल काष्ठा lock_class_key tc_ht_lock_key;

अटल व्योम mlx5e_put_flow_tunnel_id(काष्ठा mlx5e_tc_flow *flow);

व्योम
mlx5e_tc_match_to_reg_match(काष्ठा mlx5_flow_spec *spec,
			    क्रमागत mlx5e_tc_attr_to_reg type,
			    u32 data,
			    u32 mask)
अणु
	पूर्णांक soffset = mlx5e_tc_attr_to_reg_mappings[type].soffset;
	पूर्णांक match_len = mlx5e_tc_attr_to_reg_mappings[type].mlen;
	व्योम *headers_c = spec->match_criteria;
	व्योम *headers_v = spec->match_value;
	व्योम *fmask, *fval;

	fmask = headers_c + soffset;
	fval = headers_v + soffset;

	mask = (__क्रमce u32)(cpu_to_be32(mask)) >> (32 - (match_len * 8));
	data = (__क्रमce u32)(cpu_to_be32(data)) >> (32 - (match_len * 8));

	स_नकल(fmask, &mask, match_len);
	स_नकल(fval, &data, match_len);

	spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS_2;
पूर्ण

व्योम
mlx5e_tc_match_to_reg_get_match(काष्ठा mlx5_flow_spec *spec,
				क्रमागत mlx5e_tc_attr_to_reg type,
				u32 *data,
				u32 *mask)
अणु
	पूर्णांक soffset = mlx5e_tc_attr_to_reg_mappings[type].soffset;
	पूर्णांक match_len = mlx5e_tc_attr_to_reg_mappings[type].mlen;
	व्योम *headers_c = spec->match_criteria;
	व्योम *headers_v = spec->match_value;
	व्योम *fmask, *fval;

	fmask = headers_c + soffset;
	fval = headers_v + soffset;

	स_नकल(mask, fmask, match_len);
	स_नकल(data, fval, match_len);

	*mask = be32_to_cpu((__क्रमce __be32)(*mask << (32 - (match_len * 8))));
	*data = be32_to_cpu((__क्रमce __be32)(*data << (32 - (match_len * 8))));
पूर्ण

पूर्णांक
mlx5e_tc_match_to_reg_set_and_get_id(काष्ठा mlx5_core_dev *mdev,
				     काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
				     क्रमागत mlx5_flow_namespace_type ns,
				     क्रमागत mlx5e_tc_attr_to_reg type,
				     u32 data)
अणु
	पूर्णांक moffset = mlx5e_tc_attr_to_reg_mappings[type].moffset;
	पूर्णांक mfield = mlx5e_tc_attr_to_reg_mappings[type].mfield;
	पूर्णांक mlen = mlx5e_tc_attr_to_reg_mappings[type].mlen;
	अक्षर *modact;
	पूर्णांक err;

	err = alloc_mod_hdr_actions(mdev, ns, mod_hdr_acts);
	अगर (err)
		वापस err;

	modact = mod_hdr_acts->actions +
		 (mod_hdr_acts->num_actions * MLX5_MH_ACT_SZ);

	/* Firmware has 5bit length field and 0 means 32bits */
	अगर (mlen == 4)
		mlen = 0;

	MLX5_SET(set_action_in, modact, action_type, MLX5_ACTION_TYPE_SET);
	MLX5_SET(set_action_in, modact, field, mfield);
	MLX5_SET(set_action_in, modact, offset, moffset * 8);
	MLX5_SET(set_action_in, modact, length, mlen * 8);
	MLX5_SET(set_action_in, modact, data, data);
	err = mod_hdr_acts->num_actions;
	mod_hdr_acts->num_actions++;

	वापस err;
पूर्ण

अटल काष्ठा mlx5_tc_ct_priv *
get_ct_priv(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;

	अगर (is_mdev_चयनdev_mode(priv->mdev)) अणु
		uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
		uplink_priv = &uplink_rpriv->uplink_priv;

		वापस uplink_priv->ct_priv;
	पूर्ण

	वापस priv->fs.tc.ct;
पूर्ण

#अगर IS_ENABLED(CONFIG_MLX5_TC_SAMPLE)
अटल काष्ठा mlx5_esw_psample *
get_sample_priv(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;

	अगर (is_mdev_चयनdev_mode(priv->mdev)) अणु
		uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
		uplink_priv = &uplink_rpriv->uplink_priv;

		वापस uplink_priv->esw_psample;
	पूर्ण

	वापस शून्य;
पूर्ण
#पूर्ण_अगर

काष्ठा mlx5_flow_handle *
mlx5_tc_rule_insert(काष्ठा mlx5e_priv *priv,
		    काष्ठा mlx5_flow_spec *spec,
		    काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	अगर (is_mdev_चयनdev_mode(priv->mdev))
		वापस mlx5_eचयन_add_offloaded_rule(esw, spec, attr);

	वापस	mlx5e_add_offloaded_nic_rule(priv, spec, attr);
पूर्ण

व्योम
mlx5_tc_rule_delete(काष्ठा mlx5e_priv *priv,
		    काष्ठा mlx5_flow_handle *rule,
		    काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	अगर (is_mdev_चयनdev_mode(priv->mdev)) अणु
		mlx5_eचयन_del_offloaded_rule(esw, rule, attr);

		वापस;
	पूर्ण

	mlx5e_del_offloaded_nic_rule(priv, rule, attr);
पूर्ण

पूर्णांक
mlx5e_tc_match_to_reg_set(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
			  क्रमागत mlx5_flow_namespace_type ns,
			  क्रमागत mlx5e_tc_attr_to_reg type,
			  u32 data)
अणु
	पूर्णांक ret = mlx5e_tc_match_to_reg_set_and_get_id(mdev, mod_hdr_acts, ns, type, data);

	वापस ret < 0 ? ret : 0;
पूर्ण

व्योम mlx5e_tc_match_to_reg_mod_hdr_change(काष्ठा mlx5_core_dev *mdev,
					  काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
					  क्रमागत mlx5e_tc_attr_to_reg type,
					  पूर्णांक act_id, u32 data)
अणु
	पूर्णांक moffset = mlx5e_tc_attr_to_reg_mappings[type].moffset;
	पूर्णांक mfield = mlx5e_tc_attr_to_reg_mappings[type].mfield;
	पूर्णांक mlen = mlx5e_tc_attr_to_reg_mappings[type].mlen;
	अक्षर *modact;

	modact = mod_hdr_acts->actions + (act_id * MLX5_MH_ACT_SZ);

	/* Firmware has 5bit length field and 0 means 32bits */
	अगर (mlen == 4)
		mlen = 0;

	MLX5_SET(set_action_in, modact, action_type, MLX5_ACTION_TYPE_SET);
	MLX5_SET(set_action_in, modact, field, mfield);
	MLX5_SET(set_action_in, modact, offset, moffset * 8);
	MLX5_SET(set_action_in, modact, length, mlen * 8);
	MLX5_SET(set_action_in, modact, data, data);
पूर्ण

काष्ठा mlx5e_hairpin अणु
	काष्ठा mlx5_hairpin *pair;

	काष्ठा mlx5_core_dev *func_mdev;
	काष्ठा mlx5e_priv *func_priv;
	u32 tdn;
	u32 tirn;

	पूर्णांक num_channels;
	काष्ठा mlx5e_rqt indir_rqt;
	u32 indir_tirn[MLX5E_NUM_INसूची_TIRS];
	काष्ठा mlx5e_ttc_table ttc;
पूर्ण;

काष्ठा mlx5e_hairpin_entry अणु
	/* a node of a hash table which keeps all the  hairpin entries */
	काष्ठा hlist_node hairpin_hlist;

	/* protects flows list */
	spinlock_t flows_lock;
	/* flows sharing the same hairpin */
	काष्ठा list_head flows;
	/* hpe's that were not fully initialized when dead peer update event
	 * function traversed them.
	 */
	काष्ठा list_head dead_peer_रुको_list;

	u16 peer_vhca_id;
	u8 prio;
	काष्ठा mlx5e_hairpin *hp;
	refcount_t refcnt;
	काष्ठा completion res_पढ़ोy;
पूर्ण;

अटल व्योम mlx5e_tc_del_flow(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_tc_flow *flow);

काष्ठा mlx5e_tc_flow *mlx5e_flow_get(काष्ठा mlx5e_tc_flow *flow)
अणु
	अगर (!flow || !refcount_inc_not_zero(&flow->refcnt))
		वापस ERR_PTR(-EINVAL);
	वापस flow;
पूर्ण

व्योम mlx5e_flow_put(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tc_flow *flow)
अणु
	अगर (refcount_dec_and_test(&flow->refcnt)) अणु
		mlx5e_tc_del_flow(priv, flow);
		kमुक्त_rcu(flow, rcu_head);
	पूर्ण
पूर्ण

bool mlx5e_is_eचयन_flow(काष्ठा mlx5e_tc_flow *flow)
अणु
	वापस flow_flag_test(flow, ESWITCH);
पूर्ण

अटल bool mlx5e_is_ft_flow(काष्ठा mlx5e_tc_flow *flow)
अणु
	वापस flow_flag_test(flow, FT);
पूर्ण

bool mlx5e_is_offloaded_flow(काष्ठा mlx5e_tc_flow *flow)
अणु
	वापस flow_flag_test(flow, OFFLOADED);
पूर्ण

अटल पूर्णांक get_flow_name_space(काष्ठा mlx5e_tc_flow *flow)
अणु
	वापस mlx5e_is_eचयन_flow(flow) ?
		MLX5_FLOW_NAMESPACE_FDB : MLX5_FLOW_NAMESPACE_KERNEL;
पूर्ण

अटल काष्ठा mod_hdr_tbl *
get_mod_hdr_table(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	वापस get_flow_name_space(flow) == MLX5_FLOW_NAMESPACE_FDB ?
		&esw->offloads.mod_hdr :
		&priv->fs.tc.mod_hdr;
पूर्ण

अटल पूर्णांक mlx5e_attach_mod_hdr(काष्ठा mlx5e_priv *priv,
				काष्ठा mlx5e_tc_flow *flow,
				काष्ठा mlx5e_tc_flow_parse_attr *parse_attr)
अणु
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
	काष्ठा mlx5e_mod_hdr_handle *mh;

	mh = mlx5e_mod_hdr_attach(priv->mdev, get_mod_hdr_table(priv, flow),
				  get_flow_name_space(flow),
				  &parse_attr->mod_hdr_acts);
	अगर (IS_ERR(mh))
		वापस PTR_ERR(mh);

	modअगरy_hdr = mlx5e_mod_hdr_get(mh);
	flow->attr->modअगरy_hdr = modअगरy_hdr;
	flow->mh = mh;

	वापस 0;
पूर्ण

अटल व्योम mlx5e_detach_mod_hdr(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_tc_flow *flow)
अणु
	/* flow wasn't fully initialized */
	अगर (!flow->mh)
		वापस;

	mlx5e_mod_hdr_detach(priv->mdev, get_mod_hdr_table(priv, flow),
			     flow->mh);
	flow->mh = शून्य;
पूर्ण

अटल
काष्ठा mlx5_core_dev *mlx5e_hairpin_get_mdev(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *netdev;
	काष्ठा mlx5e_priv *priv;

	netdev = __dev_get_by_index(net, अगरindex);
	priv = netdev_priv(netdev);
	वापस priv->mdev;
पूर्ण

अटल पूर्णांक mlx5e_hairpin_create_transport(काष्ठा mlx5e_hairpin *hp)
अणु
	u32 in[MLX5_ST_SZ_DW(create_tir_in)] = अणुपूर्ण;
	व्योम *tirc;
	पूर्णांक err;

	err = mlx5_core_alloc_transport_करोमुख्य(hp->func_mdev, &hp->tdn);
	अगर (err)
		जाओ alloc_tdn_err;

	tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);

	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_सूचीECT);
	MLX5_SET(tirc, tirc, अंतरभूत_rqn, hp->pair->rqn[0]);
	MLX5_SET(tirc, tirc, transport_करोमुख्य, hp->tdn);

	err = mlx5_core_create_tir(hp->func_mdev, in, &hp->tirn);
	अगर (err)
		जाओ create_tir_err;

	वापस 0;

create_tir_err:
	mlx5_core_dealloc_transport_करोमुख्य(hp->func_mdev, hp->tdn);
alloc_tdn_err:
	वापस err;
पूर्ण

अटल व्योम mlx5e_hairpin_destroy_transport(काष्ठा mlx5e_hairpin *hp)
अणु
	mlx5_core_destroy_tir(hp->func_mdev, hp->tirn);
	mlx5_core_dealloc_transport_करोमुख्य(hp->func_mdev, hp->tdn);
पूर्ण

अटल पूर्णांक mlx5e_hairpin_fill_rqt_rqns(काष्ठा mlx5e_hairpin *hp, व्योम *rqtc)
अणु
	काष्ठा mlx5e_priv *priv = hp->func_priv;
	पूर्णांक i, ix, sz = MLX5E_INसूची_RQT_SIZE;
	u32 *indirection_rqt, rqn;

	indirection_rqt = kसुस्मृति(sz, माप(*indirection_rqt), GFP_KERNEL);
	अगर (!indirection_rqt)
		वापस -ENOMEM;

	mlx5e_build_शेष_indir_rqt(indirection_rqt, sz,
				      hp->num_channels);

	क्रम (i = 0; i < sz; i++) अणु
		ix = i;
		अगर (priv->rss_params.hfunc == ETH_RSS_HASH_XOR)
			ix = mlx5e_bits_invert(i, ilog2(sz));
		ix = indirection_rqt[ix];
		rqn = hp->pair->rqn[ix];
		MLX5_SET(rqtc, rqtc, rq_num[i], rqn);
	पूर्ण

	kमुक्त(indirection_rqt);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_hairpin_create_indirect_rqt(काष्ठा mlx5e_hairpin *hp)
अणु
	पूर्णांक inlen, err, sz = MLX5E_INसूची_RQT_SIZE;
	काष्ठा mlx5e_priv *priv = hp->func_priv;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	व्योम *rqtc;
	u32 *in;

	inlen = MLX5_ST_SZ_BYTES(create_rqt_in) + माप(u32) * sz;
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	rqtc = MLX5_ADDR_OF(create_rqt_in, in, rqt_context);

	MLX5_SET(rqtc, rqtc, rqt_actual_size, sz);
	MLX5_SET(rqtc, rqtc, rqt_max_size, sz);

	err = mlx5e_hairpin_fill_rqt_rqns(hp, rqtc);
	अगर (err)
		जाओ out;

	err = mlx5_core_create_rqt(mdev, in, inlen, &hp->indir_rqt.rqtn);
	अगर (!err)
		hp->indir_rqt.enabled = true;

out:
	kvमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_hairpin_create_indirect_tirs(काष्ठा mlx5e_hairpin *hp)
अणु
	काष्ठा mlx5e_priv *priv = hp->func_priv;
	u32 in[MLX5_ST_SZ_DW(create_tir_in)];
	पूर्णांक tt, i, err;
	व्योम *tirc;

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++) अणु
		काष्ठा mlx5e_tirc_config ttconfig = mlx5e_tirc_get_शेष_config(tt);

		स_रखो(in, 0, MLX5_ST_SZ_BYTES(create_tir_in));
		tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);

		MLX5_SET(tirc, tirc, transport_करोमुख्य, hp->tdn);
		MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_INसूचीECT);
		MLX5_SET(tirc, tirc, indirect_table, hp->indir_rqt.rqtn);
		mlx5e_build_indir_tir_ctx_hash(&priv->rss_params, &ttconfig, tirc, false);

		err = mlx5_core_create_tir(hp->func_mdev, in,
					   &hp->indir_tirn[tt]);
		अगर (err) अणु
			mlx5_core_warn(hp->func_mdev, "create indirect tirs failed, %d\n", err);
			जाओ err_destroy_tirs;
		पूर्ण
	पूर्ण
	वापस 0;

err_destroy_tirs:
	क्रम (i = 0; i < tt; i++)
		mlx5_core_destroy_tir(hp->func_mdev, hp->indir_tirn[i]);
	वापस err;
पूर्ण

अटल व्योम mlx5e_hairpin_destroy_indirect_tirs(काष्ठा mlx5e_hairpin *hp)
अणु
	पूर्णांक tt;

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		mlx5_core_destroy_tir(hp->func_mdev, hp->indir_tirn[tt]);
पूर्ण

अटल व्योम mlx5e_hairpin_set_ttc_params(काष्ठा mlx5e_hairpin *hp,
					 काष्ठा ttc_params *ttc_params)
अणु
	काष्ठा mlx5_flow_table_attr *ft_attr = &ttc_params->ft_attr;
	पूर्णांक tt;

	स_रखो(ttc_params, 0, माप(*ttc_params));

	ttc_params->any_tt_tirn = hp->tirn;

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		ttc_params->indir_tirn[tt] = hp->indir_tirn[tt];

	ft_attr->max_fte = MLX5E_TTC_TABLE_SIZE;
	ft_attr->level = MLX5E_TC_TTC_FT_LEVEL;
	ft_attr->prio = MLX5E_TC_PRIO;
पूर्ण

अटल पूर्णांक mlx5e_hairpin_rss_init(काष्ठा mlx5e_hairpin *hp)
अणु
	काष्ठा mlx5e_priv *priv = hp->func_priv;
	काष्ठा ttc_params ttc_params;
	पूर्णांक err;

	err = mlx5e_hairpin_create_indirect_rqt(hp);
	अगर (err)
		वापस err;

	err = mlx5e_hairpin_create_indirect_tirs(hp);
	अगर (err)
		जाओ err_create_indirect_tirs;

	mlx5e_hairpin_set_ttc_params(hp, &ttc_params);
	err = mlx5e_create_ttc_table(priv, &ttc_params, &hp->ttc);
	अगर (err)
		जाओ err_create_ttc_table;

	netdev_dbg(priv->netdev, "add hairpin: using %d channels rss ttc table id %x\n",
		   hp->num_channels, hp->ttc.ft.t->id);

	वापस 0;

err_create_ttc_table:
	mlx5e_hairpin_destroy_indirect_tirs(hp);
err_create_indirect_tirs:
	mlx5e_destroy_rqt(priv, &hp->indir_rqt);

	वापस err;
पूर्ण

अटल व्योम mlx5e_hairpin_rss_cleanup(काष्ठा mlx5e_hairpin *hp)
अणु
	काष्ठा mlx5e_priv *priv = hp->func_priv;

	mlx5e_destroy_ttc_table(priv, &hp->ttc);
	mlx5e_hairpin_destroy_indirect_tirs(hp);
	mlx5e_destroy_rqt(priv, &hp->indir_rqt);
पूर्ण

अटल काष्ठा mlx5e_hairpin *
mlx5e_hairpin_create(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_hairpin_params *params,
		     पूर्णांक peer_अगरindex)
अणु
	काष्ठा mlx5_core_dev *func_mdev, *peer_mdev;
	काष्ठा mlx5e_hairpin *hp;
	काष्ठा mlx5_hairpin *pair;
	पूर्णांक err;

	hp = kzalloc(माप(*hp), GFP_KERNEL);
	अगर (!hp)
		वापस ERR_PTR(-ENOMEM);

	func_mdev = priv->mdev;
	peer_mdev = mlx5e_hairpin_get_mdev(dev_net(priv->netdev), peer_अगरindex);

	pair = mlx5_core_hairpin_create(func_mdev, peer_mdev, params);
	अगर (IS_ERR(pair)) अणु
		err = PTR_ERR(pair);
		जाओ create_pair_err;
	पूर्ण
	hp->pair = pair;
	hp->func_mdev = func_mdev;
	hp->func_priv = priv;
	hp->num_channels = params->num_channels;

	err = mlx5e_hairpin_create_transport(hp);
	अगर (err)
		जाओ create_transport_err;

	अगर (hp->num_channels > 1) अणु
		err = mlx5e_hairpin_rss_init(hp);
		अगर (err)
			जाओ rss_init_err;
	पूर्ण

	वापस hp;

rss_init_err:
	mlx5e_hairpin_destroy_transport(hp);
create_transport_err:
	mlx5_core_hairpin_destroy(hp->pair);
create_pair_err:
	kमुक्त(hp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlx5e_hairpin_destroy(काष्ठा mlx5e_hairpin *hp)
अणु
	अगर (hp->num_channels > 1)
		mlx5e_hairpin_rss_cleanup(hp);
	mlx5e_hairpin_destroy_transport(hp);
	mlx5_core_hairpin_destroy(hp->pair);
	kvमुक्त(hp);
पूर्ण

अटल अंतरभूत u32 hash_hairpin_info(u16 peer_vhca_id, u8 prio)
अणु
	वापस (peer_vhca_id << 16 | prio);
पूर्ण

अटल काष्ठा mlx5e_hairpin_entry *mlx5e_hairpin_get(काष्ठा mlx5e_priv *priv,
						     u16 peer_vhca_id, u8 prio)
अणु
	काष्ठा mlx5e_hairpin_entry *hpe;
	u32 hash_key = hash_hairpin_info(peer_vhca_id, prio);

	hash_क्रम_each_possible(priv->fs.tc.hairpin_tbl, hpe,
			       hairpin_hlist, hash_key) अणु
		अगर (hpe->peer_vhca_id == peer_vhca_id && hpe->prio == prio) अणु
			refcount_inc(&hpe->refcnt);
			वापस hpe;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम mlx5e_hairpin_put(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_hairpin_entry *hpe)
अणु
	/* no more hairpin flows क्रम us, release the hairpin pair */
	अगर (!refcount_dec_and_mutex_lock(&hpe->refcnt, &priv->fs.tc.hairpin_tbl_lock))
		वापस;
	hash_del(&hpe->hairpin_hlist);
	mutex_unlock(&priv->fs.tc.hairpin_tbl_lock);

	अगर (!IS_ERR_OR_शून्य(hpe->hp)) अणु
		netdev_dbg(priv->netdev, "del hairpin: peer %s\n",
			   dev_name(hpe->hp->pair->peer_mdev->device));

		mlx5e_hairpin_destroy(hpe->hp);
	पूर्ण

	WARN_ON(!list_empty(&hpe->flows));
	kमुक्त(hpe);
पूर्ण

#घोषणा UNKNOWN_MATCH_PRIO 8

अटल पूर्णांक mlx5e_hairpin_get_prio(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5_flow_spec *spec, u8 *match_prio,
				  काष्ठा netlink_ext_ack *extack)
अणु
	व्योम *headers_c, *headers_v;
	u8 prio_val, prio_mask = 0;
	bool vlan_present;

#अगर_घोषित CONFIG_MLX5_CORE_EN_DCB
	अगर (priv->dcbx_dp.trust_state != MLX5_QPTS_TRUST_PCP) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "only PCP trust state supported for hairpin");
		वापस -EOPNOTSUPP;
	पूर्ण
#पूर्ण_अगर
	headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, outer_headers);
	headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, outer_headers);

	vlan_present = MLX5_GET(fte_match_set_lyr_2_4, headers_v, cvlan_tag);
	अगर (vlan_present) अणु
		prio_mask = MLX5_GET(fte_match_set_lyr_2_4, headers_c, first_prio);
		prio_val = MLX5_GET(fte_match_set_lyr_2_4, headers_v, first_prio);
	पूर्ण

	अगर (!vlan_present || !prio_mask) अणु
		prio_val = UNKNOWN_MATCH_PRIO;
	पूर्ण अन्यथा अगर (prio_mask != 0x7) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "masked priority match not supported for hairpin");
		वापस -EOPNOTSUPP;
	पूर्ण

	*match_prio = prio_val;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_hairpin_flow_add(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_tc_flow *flow,
				  काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक peer_अगरindex = parse_attr->mirred_अगरindex[0];
	काष्ठा mlx5_hairpin_params params;
	काष्ठा mlx5_core_dev *peer_mdev;
	काष्ठा mlx5e_hairpin_entry *hpe;
	काष्ठा mlx5e_hairpin *hp;
	u64 link_speed64;
	u32 link_speed;
	u8 match_prio;
	u16 peer_id;
	पूर्णांक err;

	peer_mdev = mlx5e_hairpin_get_mdev(dev_net(priv->netdev), peer_अगरindex);
	अगर (!MLX5_CAP_GEN(priv->mdev, hairpin) || !MLX5_CAP_GEN(peer_mdev, hairpin)) अणु
		NL_SET_ERR_MSG_MOD(extack, "hairpin is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	peer_id = MLX5_CAP_GEN(peer_mdev, vhca_id);
	err = mlx5e_hairpin_get_prio(priv, &parse_attr->spec, &match_prio,
				     extack);
	अगर (err)
		वापस err;

	mutex_lock(&priv->fs.tc.hairpin_tbl_lock);
	hpe = mlx5e_hairpin_get(priv, peer_id, match_prio);
	अगर (hpe) अणु
		mutex_unlock(&priv->fs.tc.hairpin_tbl_lock);
		रुको_क्रम_completion(&hpe->res_पढ़ोy);

		अगर (IS_ERR(hpe->hp)) अणु
			err = -EREMOTEIO;
			जाओ out_err;
		पूर्ण
		जाओ attach_flow;
	पूर्ण

	hpe = kzalloc(माप(*hpe), GFP_KERNEL);
	अगर (!hpe) अणु
		mutex_unlock(&priv->fs.tc.hairpin_tbl_lock);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&hpe->flows_lock);
	INIT_LIST_HEAD(&hpe->flows);
	INIT_LIST_HEAD(&hpe->dead_peer_रुको_list);
	hpe->peer_vhca_id = peer_id;
	hpe->prio = match_prio;
	refcount_set(&hpe->refcnt, 1);
	init_completion(&hpe->res_पढ़ोy);

	hash_add(priv->fs.tc.hairpin_tbl, &hpe->hairpin_hlist,
		 hash_hairpin_info(peer_id, match_prio));
	mutex_unlock(&priv->fs.tc.hairpin_tbl_lock);

	params.log_data_size = 15;
	params.log_data_size = min_t(u8, params.log_data_size,
				     MLX5_CAP_GEN(priv->mdev, log_max_hairpin_wq_data_sz));
	params.log_data_size = max_t(u8, params.log_data_size,
				     MLX5_CAP_GEN(priv->mdev, log_min_hairpin_wq_data_sz));

	params.log_num_packets = params.log_data_size -
				 MLX5_MPWRQ_MIN_LOG_STRIDE_SZ(priv->mdev);
	params.log_num_packets = min_t(u8, params.log_num_packets,
				       MLX5_CAP_GEN(priv->mdev, log_max_hairpin_num_packets));

	params.q_counter = priv->q_counter;
	/* set hairpin pair per each 50Gbs share of the link */
	mlx5e_port_max_linkspeed(priv->mdev, &link_speed);
	link_speed = max_t(u32, link_speed, 50000);
	link_speed64 = link_speed;
	करो_भाग(link_speed64, 50000);
	params.num_channels = link_speed64;

	hp = mlx5e_hairpin_create(priv, &params, peer_अगरindex);
	hpe->hp = hp;
	complete_all(&hpe->res_पढ़ोy);
	अगर (IS_ERR(hp)) अणु
		err = PTR_ERR(hp);
		जाओ out_err;
	पूर्ण

	netdev_dbg(priv->netdev, "add hairpin: tirn %x rqn %x peer %s sqn %x prio %d (log) data %d packets %d\n",
		   hp->tirn, hp->pair->rqn[0],
		   dev_name(hp->pair->peer_mdev->device),
		   hp->pair->sqn[0], match_prio, params.log_data_size, params.log_num_packets);

attach_flow:
	अगर (hpe->hp->num_channels > 1) अणु
		flow_flag_set(flow, HAIRPIN_RSS);
		flow->attr->nic_attr->hairpin_ft = hpe->hp->ttc.ft.t;
	पूर्ण अन्यथा अणु
		flow->attr->nic_attr->hairpin_tirn = hpe->hp->tirn;
	पूर्ण

	flow->hpe = hpe;
	spin_lock(&hpe->flows_lock);
	list_add(&flow->hairpin, &hpe->flows);
	spin_unlock(&hpe->flows_lock);

	वापस 0;

out_err:
	mlx5e_hairpin_put(priv, hpe);
	वापस err;
पूर्ण

अटल व्योम mlx5e_hairpin_flow_del(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5e_tc_flow *flow)
अणु
	/* flow wasn't fully initialized */
	अगर (!flow->hpe)
		वापस;

	spin_lock(&flow->hpe->flows_lock);
	list_del(&flow->hairpin);
	spin_unlock(&flow->hpe->flows_lock);

	mlx5e_hairpin_put(priv, flow->hpe);
	flow->hpe = शून्य;
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5e_add_offloaded_nic_rule(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5_flow_spec *spec,
			     काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_flow_context *flow_context = &spec->flow_context;
	काष्ठा mlx5_fs_chains *nic_chains = nic_chains(priv);
	काष्ठा mlx5_nic_flow_attr *nic_attr = attr->nic_attr;
	काष्ठा mlx5e_tc_table *tc = &priv->fs.tc;
	काष्ठा mlx5_flow_destination dest[2] = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणु
		.action = attr->action,
		.flags    = FLOW_ACT_NO_APPEND,
	पूर्ण;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक dest_ix = 0;

	flow_context->flags |= FLOW_CONTEXT_HAS_TAG;
	flow_context->flow_tag = nic_attr->flow_tag;

	अगर (attr->dest_ft) अणु
		dest[dest_ix].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
		dest[dest_ix].ft = attr->dest_ft;
		dest_ix++;
	पूर्ण अन्यथा अगर (nic_attr->hairpin_ft) अणु
		dest[dest_ix].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
		dest[dest_ix].ft = nic_attr->hairpin_ft;
		dest_ix++;
	पूर्ण अन्यथा अगर (nic_attr->hairpin_tirn) अणु
		dest[dest_ix].type = MLX5_FLOW_DESTINATION_TYPE_TIR;
		dest[dest_ix].tir_num = nic_attr->hairpin_tirn;
		dest_ix++;
	पूर्ण अन्यथा अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) अणु
		dest[dest_ix].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
		अगर (attr->dest_chain) अणु
			dest[dest_ix].ft = mlx5_chains_get_table(nic_chains,
								 attr->dest_chain, 1,
								 MLX5E_TC_FT_LEVEL);
			अगर (IS_ERR(dest[dest_ix].ft))
				वापस ERR_CAST(dest[dest_ix].ft);
		पूर्ण अन्यथा अणु
			dest[dest_ix].ft = mlx5e_vlan_get_flowtable(priv->fs.vlan);
		पूर्ण
		dest_ix++;
	पूर्ण

	अगर (dest[0].type == MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE &&
	    MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, ignore_flow_level))
		flow_act.flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;

	अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		dest[dest_ix].type = MLX5_FLOW_DESTINATION_TYPE_COUNTER;
		dest[dest_ix].counter_id = mlx5_fc_id(attr->counter);
		dest_ix++;
	पूर्ण

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		flow_act.modअगरy_hdr = attr->modअगरy_hdr;

	mutex_lock(&tc->t_lock);
	अगर (IS_ERR_OR_शून्य(tc->t)) अणु
		/* Create the root table here अगर करोesn't exist yet */
		tc->t =
			mlx5_chains_get_table(nic_chains, 0, 1, MLX5E_TC_FT_LEVEL);

		अगर (IS_ERR(tc->t)) अणु
			mutex_unlock(&tc->t_lock);
			netdev_err(priv->netdev,
				   "Failed to create tc offload table\n");
			rule = ERR_CAST(priv->fs.tc.t);
			जाओ err_ft_get;
		पूर्ण
	पूर्ण
	mutex_unlock(&tc->t_lock);

	अगर (attr->chain || attr->prio)
		ft = mlx5_chains_get_table(nic_chains,
					   attr->chain, attr->prio,
					   MLX5E_TC_FT_LEVEL);
	अन्यथा
		ft = attr->ft;

	अगर (IS_ERR(ft)) अणु
		rule = ERR_CAST(ft);
		जाओ err_ft_get;
	पूर्ण

	अगर (attr->outer_match_level != MLX5_MATCH_NONE)
		spec->match_criteria_enable |= MLX5_MATCH_OUTER_HEADERS;

	rule = mlx5_add_flow_rules(ft, spec,
				   &flow_act, dest, dest_ix);
	अगर (IS_ERR(rule))
		जाओ err_rule;

	वापस rule;

err_rule:
	अगर (attr->chain || attr->prio)
		mlx5_chains_put_table(nic_chains,
				      attr->chain, attr->prio,
				      MLX5E_TC_FT_LEVEL);
err_ft_get:
	अगर (attr->dest_chain)
		mlx5_chains_put_table(nic_chains,
				      attr->dest_chain, 1,
				      MLX5E_TC_FT_LEVEL);

	वापस ERR_CAST(rule);
पूर्ण

अटल पूर्णांक
mlx5e_tc_add_nic_flow(काष्ठा mlx5e_priv *priv,
		      काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
		      काष्ठा mlx5e_tc_flow *flow,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	काष्ठा mlx5_core_dev *dev = priv->mdev;
	काष्ठा mlx5_fc *counter = शून्य;
	पूर्णांक err;

	अगर (flow_flag_test(flow, HAIRPIN)) अणु
		err = mlx5e_hairpin_flow_add(priv, flow, parse_attr, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		counter = mlx5_fc_create(dev, true);
		अगर (IS_ERR(counter))
			वापस PTR_ERR(counter);

		attr->counter = counter;
	पूर्ण

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR) अणु
		err = mlx5e_attach_mod_hdr(priv, flow, parse_attr);
		dealloc_mod_hdr_actions(&parse_attr->mod_hdr_acts);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (flow_flag_test(flow, CT))
		flow->rule[0] = mlx5_tc_ct_flow_offload(get_ct_priv(priv), flow, &parse_attr->spec,
							attr, &parse_attr->mod_hdr_acts);
	अन्यथा
		flow->rule[0] = mlx5e_add_offloaded_nic_rule(priv, &parse_attr->spec,
							     attr);

	वापस PTR_ERR_OR_ZERO(flow->rule[0]);
पूर्ण

व्योम mlx5e_del_offloaded_nic_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5_flow_handle *rule,
				  काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_fs_chains *nic_chains = nic_chains(priv);

	mlx5_del_flow_rules(rule);

	अगर (attr->chain || attr->prio)
		mlx5_chains_put_table(nic_chains, attr->chain, attr->prio,
				      MLX5E_TC_FT_LEVEL);

	अगर (attr->dest_chain)
		mlx5_chains_put_table(nic_chains, attr->dest_chain, 1,
				      MLX5E_TC_FT_LEVEL);
पूर्ण

अटल व्योम mlx5e_tc_del_nic_flow(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	काष्ठा mlx5e_tc_table *tc = &priv->fs.tc;

	flow_flag_clear(flow, OFFLOADED);

	अगर (flow_flag_test(flow, CT))
		mlx5_tc_ct_delete_flow(get_ct_priv(flow->priv), flow, attr);
	अन्यथा अगर (!IS_ERR_OR_शून्य(flow->rule[0]))
		mlx5e_del_offloaded_nic_rule(priv, flow->rule[0], attr);

	/* Remove root table अगर no rules are left to aव्योम
	 * extra steering hops.
	 */
	mutex_lock(&priv->fs.tc.t_lock);
	अगर (!mlx5e_tc_num_filters(priv, MLX5_TC_FLAG(NIC_OFFLOAD)) &&
	    !IS_ERR_OR_शून्य(tc->t)) अणु
		mlx5_chains_put_table(nic_chains(priv), 0, 1, MLX5E_TC_FT_LEVEL);
		priv->fs.tc.t = शून्य;
	पूर्ण
	mutex_unlock(&priv->fs.tc.t_lock);

	kvमुक्त(attr->parse_attr);

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		mlx5e_detach_mod_hdr(priv, flow);

	mlx5_fc_destroy(priv->mdev, attr->counter);

	अगर (flow_flag_test(flow, HAIRPIN))
		mlx5e_hairpin_flow_del(priv, flow);

	kमुक्त(flow->attr);
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5e_tc_offload_fdb_rules(काष्ठा mlx5_eचयन *esw,
			   काष्ठा mlx5e_tc_flow *flow,
			   काष्ठा mlx5_flow_spec *spec,
			   काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts;
	काष्ठा mlx5_flow_handle *rule;

	अगर (attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH)
		वापस mlx5_eचयन_add_offloaded_rule(esw, spec, attr);

	अगर (flow_flag_test(flow, CT)) अणु
		mod_hdr_acts = &attr->parse_attr->mod_hdr_acts;

		rule = mlx5_tc_ct_flow_offload(get_ct_priv(flow->priv),
					       flow, spec, attr,
					       mod_hdr_acts);
#अगर IS_ENABLED(CONFIG_MLX5_TC_SAMPLE)
	पूर्ण अन्यथा अगर (flow_flag_test(flow, SAMPLE)) अणु
		rule = mlx5_esw_sample_offload(get_sample_priv(flow->priv), spec, attr);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		rule = mlx5_eचयन_add_offloaded_rule(esw, spec, attr);
	पूर्ण

	अगर (IS_ERR(rule))
		वापस rule;

	अगर (attr->esw_attr->split_count) अणु
		flow->rule[1] = mlx5_eचयन_add_fwd_rule(esw, spec, attr);
		अगर (IS_ERR(flow->rule[1])) अणु
			अगर (flow_flag_test(flow, CT))
				mlx5_tc_ct_delete_flow(get_ct_priv(flow->priv), flow, attr);
			अन्यथा
				mlx5_eचयन_del_offloaded_rule(esw, rule, attr);
			वापस flow->rule[1];
		पूर्ण
	पूर्ण

	वापस rule;
पूर्ण

व्योम mlx5e_tc_unoffload_fdb_rules(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5e_tc_flow *flow,
				  काष्ठा mlx5_flow_attr *attr)
अणु
	flow_flag_clear(flow, OFFLOADED);

	अगर (attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH)
		जाओ offload_rule_0;

	अगर (flow_flag_test(flow, CT)) अणु
		mlx5_tc_ct_delete_flow(get_ct_priv(flow->priv), flow, attr);
		वापस;
	पूर्ण

#अगर IS_ENABLED(CONFIG_MLX5_TC_SAMPLE)
	अगर (flow_flag_test(flow, SAMPLE)) अणु
		mlx5_esw_sample_unoffload(get_sample_priv(flow->priv), flow->rule[0], attr);
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (attr->esw_attr->split_count)
		mlx5_eचयन_del_fwd_rule(esw, flow->rule[1], attr);

offload_rule_0:
	mlx5_eचयन_del_offloaded_rule(esw, flow->rule[0], attr);
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5e_tc_offload_to_slow_path(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5e_tc_flow *flow,
			      काष्ठा mlx5_flow_spec *spec)
अणु
	काष्ठा mlx5_flow_attr *slow_attr;
	काष्ठा mlx5_flow_handle *rule;

	slow_attr = mlx5_alloc_flow_attr(MLX5_FLOW_NAMESPACE_FDB);
	अगर (!slow_attr)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(slow_attr, flow->attr, ESW_FLOW_ATTR_SZ);
	slow_attr->action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	slow_attr->esw_attr->split_count = 0;
	slow_attr->flags |= MLX5_ESW_ATTR_FLAG_SLOW_PATH;

	rule = mlx5e_tc_offload_fdb_rules(esw, flow, spec, slow_attr);
	अगर (!IS_ERR(rule))
		flow_flag_set(flow, SLOW);

	kमुक्त(slow_attr);

	वापस rule;
पूर्ण

व्योम mlx5e_tc_unoffload_from_slow_path(काष्ठा mlx5_eचयन *esw,
				       काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_flow_attr *slow_attr;

	slow_attr = mlx5_alloc_flow_attr(MLX5_FLOW_NAMESPACE_FDB);
	अगर (!slow_attr) अणु
		mlx5_core_warn(flow->priv->mdev, "Unable to alloc attr to unoffload slow path rule\n");
		वापस;
	पूर्ण

	स_नकल(slow_attr, flow->attr, ESW_FLOW_ATTR_SZ);
	slow_attr->action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	slow_attr->esw_attr->split_count = 0;
	slow_attr->flags |= MLX5_ESW_ATTR_FLAG_SLOW_PATH;
	mlx5e_tc_unoffload_fdb_rules(esw, flow, slow_attr);
	flow_flag_clear(flow, SLOW);
	kमुक्त(slow_attr);
पूर्ण

/* Caller must obtain uplink_priv->unपढ़ोy_flows_lock mutex beक्रमe calling this
 * function.
 */
अटल व्योम unपढ़ोy_flow_add(काष्ठा mlx5e_tc_flow *flow,
			     काष्ठा list_head *unपढ़ोy_flows)
अणु
	flow_flag_set(flow, NOT_READY);
	list_add_tail(&flow->unपढ़ोy, unपढ़ोy_flows);
पूर्ण

/* Caller must obtain uplink_priv->unपढ़ोy_flows_lock mutex beक्रमe calling this
 * function.
 */
अटल व्योम unपढ़ोy_flow_del(काष्ठा mlx5e_tc_flow *flow)
अणु
	list_del(&flow->unपढ़ोy);
	flow_flag_clear(flow, NOT_READY);
पूर्ण

अटल व्योम add_unपढ़ोy_flow(काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mlx5_eचयन *esw;

	esw = flow->priv->mdev->priv.eचयन;
	rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &rpriv->uplink_priv;

	mutex_lock(&uplink_priv->unपढ़ोy_flows_lock);
	unपढ़ोy_flow_add(flow, &uplink_priv->unपढ़ोy_flows);
	mutex_unlock(&uplink_priv->unपढ़ोy_flows_lock);
पूर्ण

अटल व्योम हटाओ_unपढ़ोy_flow(काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mlx5_eचयन *esw;

	esw = flow->priv->mdev->priv.eचयन;
	rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &rpriv->uplink_priv;

	mutex_lock(&uplink_priv->unपढ़ोy_flows_lock);
	unपढ़ोy_flow_del(flow);
	mutex_unlock(&uplink_priv->unपढ़ोy_flows_lock);
पूर्ण

अटल bool same_hw_devs(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_priv *peer_priv);

bool mlx5e_tc_is_vf_tunnel(काष्ठा net_device *out_dev, काष्ठा net_device *route_dev)
अणु
	काष्ठा mlx5_core_dev *out_mdev, *route_mdev;
	काष्ठा mlx5e_priv *out_priv, *route_priv;

	out_priv = netdev_priv(out_dev);
	out_mdev = out_priv->mdev;
	route_priv = netdev_priv(route_dev);
	route_mdev = route_priv->mdev;

	अगर (out_mdev->coredev_type != MLX5_COREDEV_PF ||
	    route_mdev->coredev_type != MLX5_COREDEV_VF)
		वापस false;

	वापस same_hw_devs(out_priv, route_priv);
पूर्ण

पूर्णांक mlx5e_tc_query_route_vport(काष्ठा net_device *out_dev, काष्ठा net_device *route_dev, u16 *vport)
अणु
	काष्ठा mlx5e_priv *out_priv, *route_priv;
	काष्ठा mlx5_core_dev *route_mdev;
	काष्ठा mlx5_eचयन *esw;
	u16 vhca_id;
	पूर्णांक err;

	out_priv = netdev_priv(out_dev);
	esw = out_priv->mdev->priv.eचयन;
	route_priv = netdev_priv(route_dev);
	route_mdev = route_priv->mdev;

	vhca_id = MLX5_CAP_GEN(route_mdev, vhca_id);
	err = mlx5_eचयन_vhca_id_to_vport(esw, vhca_id, vport);
	वापस err;
पूर्ण

पूर्णांक mlx5e_tc_add_flow_mod_hdr(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
			      काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts = &parse_attr->mod_hdr_acts;
	काष्ठा mlx5_modअगरy_hdr *mod_hdr;

	mod_hdr = mlx5_modअगरy_header_alloc(priv->mdev,
					   get_flow_name_space(flow),
					   mod_hdr_acts->num_actions,
					   mod_hdr_acts->actions);
	अगर (IS_ERR(mod_hdr))
		वापस PTR_ERR(mod_hdr);

	WARN_ON(flow->attr->modअगरy_hdr);
	flow->attr->modअगरy_hdr = mod_hdr;

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5e_tc_add_fdb_flow(काष्ठा mlx5e_priv *priv,
		      काष्ठा mlx5e_tc_flow *flow,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	bool vf_tun = false, encap_valid = true;
	काष्ठा net_device *encap_dev = शून्य;
	काष्ठा mlx5_esw_flow_attr *esw_attr;
	काष्ठा mlx5_fc *counter = शून्य;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mlx5e_priv *out_priv;
	u32 max_prio, max_chain;
	पूर्णांक err = 0;
	पूर्णांक out_index;

	/* We check chain range only क्रम tc flows.
	 * For ft flows, we checked attr->chain was originally 0 and set it to
	 * FDB_FT_CHAIN which is outside tc range.
	 * See mlx5e_rep_setup_ft_cb().
	 */
	max_chain = mlx5_chains_get_chain_range(esw_chains(esw));
	अगर (!mlx5e_is_ft_flow(flow) && attr->chain > max_chain) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Requested chain is out of supported range");
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	max_prio = mlx5_chains_get_prio_range(esw_chains(esw));
	अगर (attr->prio > max_prio) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Requested priority is out of supported range");
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	अगर (flow_flag_test(flow, TUN_RX)) अणु
		err = mlx5e_attach_decap_route(priv, flow);
		अगर (err)
			जाओ err_out;
	पूर्ण

	अगर (flow_flag_test(flow, L3_TO_L2_DECAP)) अणु
		err = mlx5e_attach_decap(priv, flow, extack);
		अगर (err)
			जाओ err_out;
	पूर्ण

	parse_attr = attr->parse_attr;
	esw_attr = attr->esw_attr;

	क्रम (out_index = 0; out_index < MLX5_MAX_FLOW_FWD_VPORTS; out_index++) अणु
		काष्ठा net_device *out_dev;
		पूर्णांक mirred_अगरindex;

		अगर (!(esw_attr->dests[out_index].flags & MLX5_ESW_DEST_ENCAP))
			जारी;

		mirred_अगरindex = parse_attr->mirred_अगरindex[out_index];
		out_dev = dev_get_by_index(dev_net(priv->netdev), mirred_अगरindex);
		अगर (!out_dev) अणु
			NL_SET_ERR_MSG_MOD(extack, "Requested mirred device not found");
			err = -ENODEV;
			जाओ err_out;
		पूर्ण
		err = mlx5e_attach_encap(priv, flow, out_dev, out_index,
					 extack, &encap_dev, &encap_valid);
		dev_put(out_dev);
		अगर (err)
			जाओ err_out;

		अगर (esw_attr->dests[out_index].flags &
		    MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE)
			vf_tun = true;
		out_priv = netdev_priv(encap_dev);
		rpriv = out_priv->ppriv;
		esw_attr->dests[out_index].rep = rpriv->rep;
		esw_attr->dests[out_index].mdev = out_priv->mdev;
	पूर्ण

	अगर (vf_tun && esw_attr->out_count > 1) अणु
		NL_SET_ERR_MSG_MOD(extack, "VF tunnel encap with mirroring is not supported");
		err = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण

	err = mlx5_eचयन_add_vlan_action(esw, attr);
	अगर (err)
		जाओ err_out;

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR &&
	    !(attr->ct_attr.ct_action & TCA_CT_ACT_CLEAR)) अणु
		अगर (vf_tun) अणु
			err = mlx5e_tc_add_flow_mod_hdr(priv, parse_attr, flow);
			अगर (err)
				जाओ err_out;
		पूर्ण अन्यथा अणु
			err = mlx5e_attach_mod_hdr(priv, flow, parse_attr);
			अगर (err)
				जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		counter = mlx5_fc_create(esw_attr->counter_dev, true);
		अगर (IS_ERR(counter)) अणु
			err = PTR_ERR(counter);
			जाओ err_out;
		पूर्ण

		attr->counter = counter;
	पूर्ण

	/* we get here अगर one of the following takes place:
	 * (1) there's no error
	 * (2) there's an encap action and we don't have valid neigh
	 */
	अगर (!encap_valid)
		flow->rule[0] = mlx5e_tc_offload_to_slow_path(esw, flow, &parse_attr->spec);
	अन्यथा
		flow->rule[0] = mlx5e_tc_offload_fdb_rules(esw, flow, &parse_attr->spec, attr);

	अगर (IS_ERR(flow->rule[0])) अणु
		err = PTR_ERR(flow->rule[0]);
		जाओ err_out;
	पूर्ण
	flow_flag_set(flow, OFFLOADED);

	वापस 0;

err_out:
	flow_flag_set(flow, FAILED);
	वापस err;
पूर्ण

अटल bool mlx5_flow_has_geneve_opt(काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_flow_spec *spec = &flow->attr->parse_attr->spec;
	व्योम *headers_v = MLX5_ADDR_OF(fte_match_param,
				       spec->match_value,
				       misc_parameters_3);
	u32 geneve_tlv_opt_0_data = MLX5_GET(fte_match_set_misc3,
					     headers_v,
					     geneve_tlv_option_0_data);

	वापस !!geneve_tlv_opt_0_data;
पूर्ण

अटल व्योम mlx5e_tc_del_fdb_flow(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	काष्ठा mlx5_esw_flow_attr *esw_attr;
	bool vf_tun = false;
	पूर्णांक out_index;

	esw_attr = attr->esw_attr;
	mlx5e_put_flow_tunnel_id(flow);

	अगर (flow_flag_test(flow, NOT_READY))
		हटाओ_unपढ़ोy_flow(flow);

	अगर (mlx5e_is_offloaded_flow(flow)) अणु
		अगर (flow_flag_test(flow, SLOW))
			mlx5e_tc_unoffload_from_slow_path(esw, flow);
		अन्यथा
			mlx5e_tc_unoffload_fdb_rules(esw, flow, attr);
	पूर्ण

	अगर (mlx5_flow_has_geneve_opt(flow))
		mlx5_geneve_tlv_option_del(priv->mdev->geneve);

	mlx5_eचयन_del_vlan_action(esw, attr);

	अगर (flow->decap_route)
		mlx5e_detach_decap_route(priv, flow);

	क्रम (out_index = 0; out_index < MLX5_MAX_FLOW_FWD_VPORTS; out_index++) अणु
		अगर (esw_attr->dests[out_index].flags &
		    MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE)
			vf_tun = true;
		अगर (esw_attr->dests[out_index].flags & MLX5_ESW_DEST_ENCAP) अणु
			mlx5e_detach_encap(priv, flow, out_index);
			kमुक्त(attr->parse_attr->tun_info[out_index]);
		पूर्ण
	पूर्ण

	mlx5_tc_ct_match_del(get_ct_priv(priv), &flow->attr->ct_attr);

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR) अणु
		dealloc_mod_hdr_actions(&attr->parse_attr->mod_hdr_acts);
		अगर (vf_tun && attr->modअगरy_hdr)
			mlx5_modअगरy_header_dealloc(priv->mdev, attr->modअगरy_hdr);
		अन्यथा
			mlx5e_detach_mod_hdr(priv, flow);
	पूर्ण
	kvमुक्त(attr->parse_attr);
	kvमुक्त(attr->esw_attr->rx_tun_attr);

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_COUNT)
		mlx5_fc_destroy(esw_attr->counter_dev, attr->counter);

	अगर (flow_flag_test(flow, L3_TO_L2_DECAP))
		mlx5e_detach_decap(priv, flow);

	kमुक्त(flow->attr->esw_attr->sample);
	kमुक्त(flow->attr);
पूर्ण

काष्ठा mlx5_fc *mlx5e_tc_get_counter(काष्ठा mlx5e_tc_flow *flow)
अणु
	वापस flow->attr->counter;
पूर्ण

/* Iterate over पंचांगp_list of flows attached to flow_list head. */
व्योम mlx5e_put_flow_list(काष्ठा mlx5e_priv *priv, काष्ठा list_head *flow_list)
अणु
	काष्ठा mlx5e_tc_flow *flow, *पंचांगp;

	list_क्रम_each_entry_safe(flow, पंचांगp, flow_list, पंचांगp_list)
		mlx5e_flow_put(priv, flow);
पूर्ण

अटल व्योम __mlx5e_tc_del_fdb_peer_flow(काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_eचयन *esw = flow->priv->mdev->priv.eचयन;

	अगर (!flow_flag_test(flow, ESWITCH) ||
	    !flow_flag_test(flow, DUP))
		वापस;

	mutex_lock(&esw->offloads.peer_mutex);
	list_del(&flow->peer);
	mutex_unlock(&esw->offloads.peer_mutex);

	flow_flag_clear(flow, DUP);

	अगर (refcount_dec_and_test(&flow->peer_flow->refcnt)) अणु
		mlx5e_tc_del_fdb_flow(flow->peer_flow->priv, flow->peer_flow);
		kमुक्त(flow->peer_flow);
	पूर्ण

	flow->peer_flow = शून्य;
पूर्ण

अटल व्योम mlx5e_tc_del_fdb_peer_flow(काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_core_dev *dev = flow->priv->mdev;
	काष्ठा mlx5_devcom *devcom = dev->priv.devcom;
	काष्ठा mlx5_eचयन *peer_esw;

	peer_esw = mlx5_devcom_get_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
	अगर (!peer_esw)
		वापस;

	__mlx5e_tc_del_fdb_peer_flow(flow);
	mlx5_devcom_release_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
पूर्ण

अटल व्योम mlx5e_tc_del_flow(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_tc_flow *flow)
अणु
	अगर (mlx5e_is_eचयन_flow(flow)) अणु
		mlx5e_tc_del_fdb_peer_flow(flow);
		mlx5e_tc_del_fdb_flow(priv, flow);
	पूर्ण अन्यथा अणु
		mlx5e_tc_del_nic_flow(priv, flow);
	पूर्ण
पूर्ण

अटल पूर्णांक flow_has_tc_fwd_action(काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_action *flow_action = &rule->action;
	स्थिर काष्ठा flow_action_entry *act;
	पूर्णांक i;

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_GOTO:
			वापस true;
		शेष:
			जारी;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
enc_opts_is_करोnt_care_or_full_match(काष्ठा mlx5e_priv *priv,
				    काष्ठा flow_dissector_key_enc_opts *opts,
				    काष्ठा netlink_ext_ack *extack,
				    bool *करोnt_care)
अणु
	काष्ठा geneve_opt *opt;
	पूर्णांक off = 0;

	*करोnt_care = true;

	जबतक (opts->len > off) अणु
		opt = (काष्ठा geneve_opt *)&opts->data[off];

		अगर (!(*करोnt_care) || opt->opt_class || opt->type ||
		    स_प्रथम_inv(opt->opt_data, 0, opt->length * 4)) अणु
			*करोnt_care = false;

			अगर (opt->opt_class != htons(U16_MAX) ||
			    opt->type != U8_MAX) अणु
				NL_SET_ERR_MSG(extack,
					       "Partial match of tunnel options in chain > 0 isn't supported");
				netdev_warn(priv->netdev,
					    "Partial match of tunnel options in chain > 0 isn't supported");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण

		off += माप(काष्ठा geneve_opt) + opt->length * 4;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा COPY_DISSECTOR(rule, diss_key, dst)\
(अणु \
	काष्ठा flow_rule *__rule = (rule);\
	typeof(dst) __dst = dst;\
\
	स_नकल(__dst,\
	       skb_flow_dissector_target(__rule->match.dissector,\
					 diss_key,\
					 __rule->match.key),\
	       माप(*__dst));\
पूर्ण)

अटल पूर्णांक mlx5e_get_flow_tunnel_id(काष्ठा mlx5e_priv *priv,
				    काष्ठा mlx5e_tc_flow *flow,
				    काष्ठा flow_cls_offload *f,
				    काष्ठा net_device *filter_dev)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts;
	काष्ठा flow_match_enc_opts enc_opts_match;
	काष्ठा tunnel_match_enc_opts tun_enc_opts;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;
	काष्ठा tunnel_match_key tunnel_key;
	bool enc_opts_is_करोnt_care = true;
	u32 tun_id, enc_opts_id = 0;
	काष्ठा mlx5_eचयन *esw;
	u32 value, mask;
	पूर्णांक err;

	esw = priv->mdev->priv.eचयन;
	uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &uplink_rpriv->uplink_priv;

	स_रखो(&tunnel_key, 0, माप(tunnel_key));
	COPY_DISSECTOR(rule, FLOW_DISSECTOR_KEY_ENC_CONTROL,
		       &tunnel_key.enc_control);
	अगर (tunnel_key.enc_control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS)
		COPY_DISSECTOR(rule, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS,
			       &tunnel_key.enc_ipv4);
	अन्यथा
		COPY_DISSECTOR(rule, FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS,
			       &tunnel_key.enc_ipv6);
	COPY_DISSECTOR(rule, FLOW_DISSECTOR_KEY_ENC_IP, &tunnel_key.enc_ip);
	COPY_DISSECTOR(rule, FLOW_DISSECTOR_KEY_ENC_PORTS,
		       &tunnel_key.enc_tp);
	COPY_DISSECTOR(rule, FLOW_DISSECTOR_KEY_ENC_KEYID,
		       &tunnel_key.enc_key_id);
	tunnel_key.filter_अगरindex = filter_dev->अगरindex;

	err = mapping_add(uplink_priv->tunnel_mapping, &tunnel_key, &tun_id);
	अगर (err)
		वापस err;

	flow_rule_match_enc_opts(rule, &enc_opts_match);
	err = enc_opts_is_करोnt_care_or_full_match(priv,
						  enc_opts_match.mask,
						  extack,
						  &enc_opts_is_करोnt_care);
	अगर (err)
		जाओ err_enc_opts;

	अगर (!enc_opts_is_करोnt_care) अणु
		स_रखो(&tun_enc_opts, 0, माप(tun_enc_opts));
		स_नकल(&tun_enc_opts.key, enc_opts_match.key,
		       माप(*enc_opts_match.key));
		स_नकल(&tun_enc_opts.mask, enc_opts_match.mask,
		       माप(*enc_opts_match.mask));

		err = mapping_add(uplink_priv->tunnel_enc_opts_mapping,
				  &tun_enc_opts, &enc_opts_id);
		अगर (err)
			जाओ err_enc_opts;
	पूर्ण

	value = tun_id << ENC_OPTS_BITS | enc_opts_id;
	mask = enc_opts_id ? TUNNEL_ID_MASK :
			     (TUNNEL_ID_MASK & ~ENC_OPTS_BITS_MASK);

	अगर (attr->chain) अणु
		mlx5e_tc_match_to_reg_match(&attr->parse_attr->spec,
					    TUNNEL_TO_REG, value, mask);
	पूर्ण अन्यथा अणु
		mod_hdr_acts = &attr->parse_attr->mod_hdr_acts;
		err = mlx5e_tc_match_to_reg_set(priv->mdev,
						mod_hdr_acts, MLX5_FLOW_NAMESPACE_FDB,
						TUNNEL_TO_REG, value);
		अगर (err)
			जाओ err_set;

		attr->action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	पूर्ण

	flow->tunnel_id = value;
	वापस 0;

err_set:
	अगर (enc_opts_id)
		mapping_हटाओ(uplink_priv->tunnel_enc_opts_mapping,
			       enc_opts_id);
err_enc_opts:
	mapping_हटाओ(uplink_priv->tunnel_mapping, tun_id);
	वापस err;
पूर्ण

अटल व्योम mlx5e_put_flow_tunnel_id(काष्ठा mlx5e_tc_flow *flow)
अणु
	u32 enc_opts_id = flow->tunnel_id & ENC_OPTS_BITS_MASK;
	u32 tun_id = flow->tunnel_id >> ENC_OPTS_BITS;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;
	काष्ठा mlx5_eचयन *esw;

	esw = flow->priv->mdev->priv.eचयन;
	uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &uplink_rpriv->uplink_priv;

	अगर (tun_id)
		mapping_हटाओ(uplink_priv->tunnel_mapping, tun_id);
	अगर (enc_opts_id)
		mapping_हटाओ(uplink_priv->tunnel_enc_opts_mapping,
			       enc_opts_id);
पूर्ण

u32 mlx5e_tc_get_flow_tun_id(काष्ठा mlx5e_tc_flow *flow)
अणु
	वापस flow->tunnel_id;
पूर्ण

व्योम mlx5e_tc_set_ethertype(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा flow_match_basic *match, bool outer,
			    व्योम *headers_c, व्योम *headers_v)
अणु
	bool ip_version_cap;

	ip_version_cap = outer ?
		MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
					  ft_field_support.outer_ip_version) :
		MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
					  ft_field_support.inner_ip_version);

	अगर (ip_version_cap && match->mask->n_proto == htons(0xFFFF) &&
	    (match->key->n_proto == htons(ETH_P_IP) ||
	     match->key->n_proto == htons(ETH_P_IPV6))) अणु
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, ip_version);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_version,
			 match->key->n_proto == htons(ETH_P_IP) ? 4 : 6);
	पूर्ण अन्यथा अणु
		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ethertype,
			 ntohs(match->mask->n_proto));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ethertype,
			 ntohs(match->key->n_proto));
	पूर्ण
पूर्ण

u8 mlx5e_tc_get_ip_version(काष्ठा mlx5_flow_spec *spec, bool outer)
अणु
	व्योम *headers_v;
	u16 ethertype;
	u8 ip_version;

	अगर (outer)
		headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, outer_headers);
	अन्यथा
		headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, inner_headers);

	ip_version = MLX5_GET(fte_match_set_lyr_2_4, headers_v, ip_version);
	/* Return ip_version converted from ethertype anyway */
	अगर (!ip_version) अणु
		ethertype = MLX5_GET(fte_match_set_lyr_2_4, headers_v, ethertype);
		अगर (ethertype == ETH_P_IP || ethertype == ETH_P_ARP)
			ip_version = 4;
		अन्यथा अगर (ethertype == ETH_P_IPV6)
			ip_version = 6;
	पूर्ण
	वापस ip_version;
पूर्ण

अटल पूर्णांक parse_tunnel_attr(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_tc_flow *flow,
			     काष्ठा mlx5_flow_spec *spec,
			     काष्ठा flow_cls_offload *f,
			     काष्ठा net_device *filter_dev,
			     u8 *match_level,
			     bool *match_inner)
अणु
	काष्ठा mlx5e_tc_tunnel *tunnel = mlx5e_get_tc_tun(filter_dev);
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	bool needs_mapping, sets_mapping;
	पूर्णांक err;

	अगर (!mlx5e_is_eचयन_flow(flow))
		वापस -EOPNOTSUPP;

	needs_mapping = !!flow->attr->chain;
	sets_mapping = !flow->attr->chain && flow_has_tc_fwd_action(f);
	*match_inner = !needs_mapping;

	अगर ((needs_mapping || sets_mapping) &&
	    !mlx5_eचयन_reg_c1_loopback_enabled(esw)) अणु
		NL_SET_ERR_MSG(extack,
			       "Chains on tunnel devices isn't supported without register loopback support");
		netdev_warn(priv->netdev,
			    "Chains on tunnel devices isn't supported without register loopback support");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!flow->attr->chain) अणु
		err = mlx5e_tc_tun_parse(filter_dev, priv, spec, f,
					 match_level);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Failed to parse tunnel attributes");
			netdev_warn(priv->netdev,
				    "Failed to parse tunnel attributes");
			वापस err;
		पूर्ण

		/* With mpls over udp we decapsulate using packet reक्रमmat
		 * object
		 */
		अगर (!netअगर_is_bareudp(filter_dev))
			flow->attr->action |= MLX5_FLOW_CONTEXT_ACTION_DECAP;
		err = mlx5e_tc_set_attr_rx_tun(flow, spec);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (tunnel && tunnel->tunnel_type == MLX5E_TC_TUNNEL_TYPE_VXLAN) अणु
		काष्ठा mlx5_flow_spec *पंचांगp_spec;

		पंचांगp_spec = kvzalloc(माप(*पंचांगp_spec), GFP_KERNEL);
		अगर (!पंचांगp_spec) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to allocate memory for vxlan tmp spec");
			netdev_warn(priv->netdev, "Failed to allocate memory for vxlan tmp spec");
			वापस -ENOMEM;
		पूर्ण
		स_नकल(पंचांगp_spec, spec, माप(*पंचांगp_spec));

		err = mlx5e_tc_tun_parse(filter_dev, priv, पंचांगp_spec, f, match_level);
		अगर (err) अणु
			kvमुक्त(पंचांगp_spec);
			NL_SET_ERR_MSG_MOD(extack, "Failed to parse tunnel attributes");
			netdev_warn(priv->netdev, "Failed to parse tunnel attributes");
			वापस err;
		पूर्ण
		err = mlx5e_tc_set_attr_rx_tun(flow, पंचांगp_spec);
		kvमुक्त(पंचांगp_spec);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!needs_mapping && !sets_mapping)
		वापस 0;

	वापस mlx5e_get_flow_tunnel_id(priv, flow, f, filter_dev);
पूर्ण

अटल व्योम *get_match_inner_headers_criteria(काष्ठा mlx5_flow_spec *spec)
अणु
	वापस MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			    inner_headers);
पूर्ण

अटल व्योम *get_match_inner_headers_value(काष्ठा mlx5_flow_spec *spec)
अणु
	वापस MLX5_ADDR_OF(fte_match_param, spec->match_value,
			    inner_headers);
पूर्ण

अटल व्योम *get_match_outer_headers_criteria(काष्ठा mlx5_flow_spec *spec)
अणु
	वापस MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			    outer_headers);
पूर्ण

अटल व्योम *get_match_outer_headers_value(काष्ठा mlx5_flow_spec *spec)
अणु
	वापस MLX5_ADDR_OF(fte_match_param, spec->match_value,
			    outer_headers);
पूर्ण

अटल व्योम *get_match_headers_value(u32 flags,
				     काष्ठा mlx5_flow_spec *spec)
अणु
	वापस (flags & MLX5_FLOW_CONTEXT_ACTION_DECAP) ?
		get_match_inner_headers_value(spec) :
		get_match_outer_headers_value(spec);
पूर्ण

अटल व्योम *get_match_headers_criteria(u32 flags,
					काष्ठा mlx5_flow_spec *spec)
अणु
	वापस (flags & MLX5_FLOW_CONTEXT_ACTION_DECAP) ?
		get_match_inner_headers_criteria(spec) :
		get_match_outer_headers_criteria(spec);
पूर्ण

अटल पूर्णांक mlx5e_flower_parse_meta(काष्ठा net_device *filter_dev,
				   काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा net_device *ingress_dev;
	काष्ठा flow_match_meta match;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_META))
		वापस 0;

	flow_rule_match_meta(rule, &match);
	अगर (!match.mask->ingress_अगरindex)
		वापस 0;

	अगर (match.mask->ingress_अगरindex != 0xFFFFFFFF) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported ingress ifindex mask");
		वापस -EOPNOTSUPP;
	पूर्ण

	ingress_dev = __dev_get_by_index(dev_net(filter_dev),
					 match.key->ingress_अगरindex);
	अगर (!ingress_dev) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can't find the ingress port to match on");
		वापस -ENOENT;
	पूर्ण

	अगर (ingress_dev != filter_dev) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can't match on the ingress filter port");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool skip_key_basic(काष्ठा net_device *filter_dev,
			   काष्ठा flow_cls_offload *f)
अणु
	/* When करोing mpls over udp decap, the user needs to provide
	 * MPLS_UC as the protocol in order to be able to match on mpls
	 * label fields.  However, the actual ethertype is IP so we want to
	 * aव्योम matching on this, otherwise we'll fail the match.
	 */
	अगर (netअगर_is_bareudp(filter_dev) && f->common.chain_index == 0)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __parse_cls_flower(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_tc_flow *flow,
			      काष्ठा mlx5_flow_spec *spec,
			      काष्ठा flow_cls_offload *f,
			      काष्ठा net_device *filter_dev,
			      u8 *inner_match_level, u8 *outer_match_level)
अणु
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	व्योम *headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				       outer_headers);
	व्योम *headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				       outer_headers);
	व्योम *misc_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    misc_parameters);
	व्योम *misc_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters);
	व्योम *misc_c_3 = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    misc_parameters_3);
	व्योम *misc_v_3 = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters_3);
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	क्रमागत fs_flow_table_type fs_type;
	u16 addr_type = 0;
	u8 ip_proto = 0;
	u8 *match_level;
	पूर्णांक err;

	fs_type = mlx5e_is_eचयन_flow(flow) ? FS_FT_FDB : FS_FT_NIC_RX;
	match_level = outer_match_level;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_META) |
	      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_CVLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_PORTS)	|
	      BIT(FLOW_DISSECTOR_KEY_ENC_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_TCP) |
	      BIT(FLOW_DISSECTOR_KEY_IP)  |
	      BIT(FLOW_DISSECTOR_KEY_CT) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_IP) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_OPTS) |
	      BIT(FLOW_DISSECTOR_KEY_ICMP) |
	      BIT(FLOW_DISSECTOR_KEY_MPLS))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported key");
		netdev_dbg(priv->netdev, "Unsupported key used: 0x%x\n",
			   dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mlx5e_get_tc_tun(filter_dev)) अणु
		bool match_inner = false;

		err = parse_tunnel_attr(priv, flow, spec, f, filter_dev,
					outer_match_level, &match_inner);
		अगर (err)
			वापस err;

		अगर (match_inner) अणु
			/* header poपूर्णांकers should poपूर्णांक to the inner headers
			 * अगर the packet was decapsulated alपढ़ोy.
			 * outer headers are set by parse_tunnel_attr.
			 */
			match_level = inner_match_level;
			headers_c = get_match_inner_headers_criteria(spec);
			headers_v = get_match_inner_headers_value(spec);
		पूर्ण
	पूर्ण

	err = mlx5e_flower_parse_meta(filter_dev, f);
	अगर (err)
		वापस err;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC) &&
	    !skip_key_basic(filter_dev, f)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		mlx5e_tc_set_ethertype(priv->mdev, &match,
				       match_level == outer_match_level,
				       headers_c, headers_v);

		अगर (match.mask->n_proto)
			*match_level = MLX5_MATCH_L2;
	पूर्ण
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN) ||
	    is_vlan_dev(filter_dev)) अणु
		काष्ठा flow_dissector_key_vlan filter_dev_mask;
		काष्ठा flow_dissector_key_vlan filter_dev_key;
		काष्ठा flow_match_vlan match;

		अगर (is_vlan_dev(filter_dev)) अणु
			match.key = &filter_dev_key;
			match.key->vlan_id = vlan_dev_vlan_id(filter_dev);
			match.key->vlan_tpid = vlan_dev_vlan_proto(filter_dev);
			match.key->vlan_priority = 0;
			match.mask = &filter_dev_mask;
			स_रखो(match.mask, 0xff, माप(*match.mask));
			match.mask->vlan_priority = 0;
		पूर्ण अन्यथा अणु
			flow_rule_match_vlan(rule, &match);
		पूर्ण
		अगर (match.mask->vlan_id ||
		    match.mask->vlan_priority ||
		    match.mask->vlan_tpid) अणु
			अगर (match.key->vlan_tpid == htons(ETH_P_8021AD)) अणु
				MLX5_SET(fte_match_set_lyr_2_4, headers_c,
					 svlan_tag, 1);
				MLX5_SET(fte_match_set_lyr_2_4, headers_v,
					 svlan_tag, 1);
			पूर्ण अन्यथा अणु
				MLX5_SET(fte_match_set_lyr_2_4, headers_c,
					 cvlan_tag, 1);
				MLX5_SET(fte_match_set_lyr_2_4, headers_v,
					 cvlan_tag, 1);
			पूर्ण

			MLX5_SET(fte_match_set_lyr_2_4, headers_c, first_vid,
				 match.mask->vlan_id);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v, first_vid,
				 match.key->vlan_id);

			MLX5_SET(fte_match_set_lyr_2_4, headers_c, first_prio,
				 match.mask->vlan_priority);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v, first_prio,
				 match.key->vlan_priority);

			*match_level = MLX5_MATCH_L2;
		पूर्ण
	पूर्ण अन्यथा अगर (*match_level != MLX5_MATCH_NONE) अणु
		/* cvlan_tag enabled in match criteria and
		 * disabled in match value means both S & C tags
		 * करोn't exist (untagged of both)
		 */
		MLX5_SET(fte_match_set_lyr_2_4, headers_c, cvlan_tag, 1);
		*match_level = MLX5_MATCH_L2;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CVLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_cvlan(rule, &match);
		अगर (match.mask->vlan_id ||
		    match.mask->vlan_priority ||
		    match.mask->vlan_tpid) अणु
			अगर (!MLX5_CAP_FLOWTABLE_TYPE(priv->mdev, ft_field_support.outer_second_vid,
						     fs_type)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Matching on CVLAN is not supported");
				वापस -EOPNOTSUPP;
			पूर्ण

			अगर (match.key->vlan_tpid == htons(ETH_P_8021AD)) अणु
				MLX5_SET(fte_match_set_misc, misc_c,
					 outer_second_svlan_tag, 1);
				MLX5_SET(fte_match_set_misc, misc_v,
					 outer_second_svlan_tag, 1);
			पूर्ण अन्यथा अणु
				MLX5_SET(fte_match_set_misc, misc_c,
					 outer_second_cvlan_tag, 1);
				MLX5_SET(fte_match_set_misc, misc_v,
					 outer_second_cvlan_tag, 1);
			पूर्ण

			MLX5_SET(fte_match_set_misc, misc_c, outer_second_vid,
				 match.mask->vlan_id);
			MLX5_SET(fte_match_set_misc, misc_v, outer_second_vid,
				 match.key->vlan_id);
			MLX5_SET(fte_match_set_misc, misc_c, outer_second_prio,
				 match.mask->vlan_priority);
			MLX5_SET(fte_match_set_misc, misc_v, outer_second_prio,
				 match.key->vlan_priority);

			*match_level = MLX5_MATCH_L2;
			spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
					     dmac_47_16),
				match.mask->dst);
		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
					     dmac_47_16),
				match.key->dst);

		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
					     smac_47_16),
				match.mask->src);
		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
					     smac_47_16),
				match.key->src);

		अगर (!is_zero_ether_addr(match.mask->src) ||
		    !is_zero_ether_addr(match.mask->dst))
			*match_level = MLX5_MATCH_L2;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;

		/* the HW करोesn't support frag first/later */
		अगर (match.mask->flags & FLOW_DIS_FIRST_FRAG)
			वापस -EOPNOTSUPP;

		अगर (match.mask->flags & FLOW_DIS_IS_FRAGMENT) अणु
			MLX5_SET(fte_match_set_lyr_2_4, headers_c, frag, 1);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v, frag,
				 match.key->flags & FLOW_DIS_IS_FRAGMENT);

			/* the HW करोesn't need L3 अंतरभूत to match on frag=no */
			अगर (!(match.key->flags & FLOW_DIS_IS_FRAGMENT))
				*match_level = MLX5_MATCH_L2;
	/* ***  L2 attributes parsing up to here *** */
			अन्यथा
				*match_level = MLX5_MATCH_L3;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		ip_proto = match.key->ip_proto;

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_protocol,
			 match.mask->ip_proto);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_protocol,
			 match.key->ip_proto);

		अगर (match.mask->ip_proto)
			*match_level = MLX5_MATCH_L3;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &match.mask->src, माप(match.mask->src));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &match.key->src, माप(match.key->src));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &match.mask->dst, माप(match.mask->dst));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &match.key->dst, माप(match.key->dst));

		अगर (match.mask->src || match.mask->dst)
			*match_level = MLX5_MATCH_L3;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &match.mask->src, माप(match.mask->src));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &match.key->src, माप(match.key->src));

		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &match.mask->dst, माप(match.mask->dst));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &match.key->dst, माप(match.key->dst));

		अगर (ipv6_addr_type(&match.mask->src) != IPV6_ADDR_ANY ||
		    ipv6_addr_type(&match.mask->dst) != IPV6_ADDR_ANY)
			*match_level = MLX5_MATCH_L3;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP)) अणु
		काष्ठा flow_match_ip match;

		flow_rule_match_ip(rule, &match);
		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_ecn,
			 match.mask->tos & 0x3);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_ecn,
			 match.key->tos & 0x3);

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_dscp,
			 match.mask->tos >> 2);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_dscp,
			 match.key->tos  >> 2);

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ttl_hoplimit,
			 match.mask->ttl);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ttl_hoplimit,
			 match.key->ttl);

		अगर (match.mask->ttl &&
		    !MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev,
						ft_field_support.outer_ipv4_ttl)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Matching on TTL is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (match.mask->tos || match.mask->ttl)
			*match_level = MLX5_MATCH_L3;
	पूर्ण

	/* ***  L3 attributes parsing up to here *** */

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		चयन (ip_proto) अणु
		हाल IPPROTO_TCP:
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 tcp_sport, ntohs(match.mask->src));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 tcp_sport, ntohs(match.key->src));

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 tcp_dport, ntohs(match.mask->dst));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 tcp_dport, ntohs(match.key->dst));
			अवरोध;

		हाल IPPROTO_UDP:
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 udp_sport, ntohs(match.mask->src));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 udp_sport, ntohs(match.key->src));

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 udp_dport, ntohs(match.mask->dst));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 udp_dport, ntohs(match.key->dst));
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack,
					   "Only UDP and TCP transports are supported for L4 matching");
			netdev_err(priv->netdev,
				   "Only UDP and TCP transport are supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (match.mask->src || match.mask->dst)
			*match_level = MLX5_MATCH_L4;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_TCP)) अणु
		काष्ठा flow_match_tcp match;

		flow_rule_match_tcp(rule, &match);
		MLX5_SET(fte_match_set_lyr_2_4, headers_c, tcp_flags,
			 ntohs(match.mask->flags));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, tcp_flags,
			 ntohs(match.key->flags));

		अगर (match.mask->flags)
			*match_level = MLX5_MATCH_L4;
	पूर्ण
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ICMP)) अणु
		काष्ठा flow_match_icmp match;

		flow_rule_match_icmp(rule, &match);
		चयन (ip_proto) अणु
		हाल IPPROTO_ICMP:
			अगर (!(MLX5_CAP_GEN(priv->mdev, flex_parser_protocols) &
			      MLX5_FLEX_PROTO_ICMP))
				वापस -EOPNOTSUPP;
			MLX5_SET(fte_match_set_misc3, misc_c_3, icmp_type,
				 match.mask->type);
			MLX5_SET(fte_match_set_misc3, misc_v_3, icmp_type,
				 match.key->type);
			MLX5_SET(fte_match_set_misc3, misc_c_3, icmp_code,
				 match.mask->code);
			MLX5_SET(fte_match_set_misc3, misc_v_3, icmp_code,
				 match.key->code);
			अवरोध;
		हाल IPPROTO_ICMPV6:
			अगर (!(MLX5_CAP_GEN(priv->mdev, flex_parser_protocols) &
			      MLX5_FLEX_PROTO_ICMPV6))
				वापस -EOPNOTSUPP;
			MLX5_SET(fte_match_set_misc3, misc_c_3, icmpv6_type,
				 match.mask->type);
			MLX5_SET(fte_match_set_misc3, misc_v_3, icmpv6_type,
				 match.key->type);
			MLX5_SET(fte_match_set_misc3, misc_c_3, icmpv6_code,
				 match.mask->code);
			MLX5_SET(fte_match_set_misc3, misc_v_3, icmpv6_code,
				 match.key->code);
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack,
					   "Code and type matching only with ICMP and ICMPv6");
			netdev_err(priv->netdev,
				   "Code and type matching only with ICMP and ICMPv6\n");
			वापस -EINVAL;
		पूर्ण
		अगर (match.mask->code || match.mask->type) अणु
			*match_level = MLX5_MATCH_L4;
			spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS_3;
		पूर्ण
	पूर्ण
	/* Currenlty supported only क्रम MPLS over UDP */
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_MPLS) &&
	    !netअगर_is_bareudp(filter_dev)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on MPLS is supported only for MPLS over UDP");
		netdev_err(priv->netdev,
			   "Matching on MPLS is supported only for MPLS over UDP\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_cls_flower(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5e_tc_flow *flow,
			    काष्ठा mlx5_flow_spec *spec,
			    काष्ठा flow_cls_offload *f,
			    काष्ठा net_device *filter_dev)
अणु
	u8 inner_match_level, outer_match_level, non_tunnel_match_level;
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा mlx5_core_dev *dev = priv->mdev;
	काष्ठा mlx5_eचयन *esw = dev->priv.eचयन;
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep;
	bool is_eचयन_flow;
	पूर्णांक err;

	inner_match_level = MLX5_MATCH_NONE;
	outer_match_level = MLX5_MATCH_NONE;

	err = __parse_cls_flower(priv, flow, spec, f, filter_dev,
				 &inner_match_level, &outer_match_level);
	non_tunnel_match_level = (inner_match_level == MLX5_MATCH_NONE) ?
				 outer_match_level : inner_match_level;

	is_eचयन_flow = mlx5e_is_eचयन_flow(flow);
	अगर (!err && is_eचयन_flow) अणु
		rep = rpriv->rep;
		अगर (rep->vport != MLX5_VPORT_UPLINK &&
		    (esw->offloads.अंतरभूत_mode != MLX5_INLINE_MODE_NONE &&
		    esw->offloads.अंतरभूत_mode < non_tunnel_match_level)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Flow is not offloaded due to min inline setting");
			netdev_warn(priv->netdev,
				    "Flow is not offloaded due to min inline setting, required %d actual %d\n",
				    non_tunnel_match_level, esw->offloads.अंतरभूत_mode);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	flow->attr->inner_match_level = inner_match_level;
	flow->attr->outer_match_level = outer_match_level;


	वापस err;
पूर्ण

काष्ठा pedit_headers अणु
	काष्ठा ethhdr  eth;
	काष्ठा vlan_hdr vlan;
	काष्ठा iphdr   ip4;
	काष्ठा ipv6hdr ip6;
	काष्ठा tcphdr  tcp;
	काष्ठा udphdr  udp;
पूर्ण;

काष्ठा pedit_headers_action अणु
	काष्ठा pedit_headers	vals;
	काष्ठा pedit_headers	masks;
	u32			pedits;
पूर्ण;

अटल पूर्णांक pedit_header_offsets[] = अणु
	[FLOW_ACT_MANGLE_HDR_TYPE_ETH] = दुरत्व(काष्ठा pedit_headers, eth),
	[FLOW_ACT_MANGLE_HDR_TYPE_IP4] = दुरत्व(काष्ठा pedit_headers, ip4),
	[FLOW_ACT_MANGLE_HDR_TYPE_IP6] = दुरत्व(काष्ठा pedit_headers, ip6),
	[FLOW_ACT_MANGLE_HDR_TYPE_TCP] = दुरत्व(काष्ठा pedit_headers, tcp),
	[FLOW_ACT_MANGLE_HDR_TYPE_UDP] = दुरत्व(काष्ठा pedit_headers, udp),
पूर्ण;

#घोषणा pedit_header(_ph, _htype) ((व्योम *)(_ph) + pedit_header_offsets[_htype])

अटल पूर्णांक set_pedit_val(u8 hdr_type, u32 mask, u32 val, u32 offset,
			 काष्ठा pedit_headers_action *hdrs)
अणु
	u32 *curr_pmask, *curr_pval;

	curr_pmask = (u32 *)(pedit_header(&hdrs->masks, hdr_type) + offset);
	curr_pval  = (u32 *)(pedit_header(&hdrs->vals, hdr_type) + offset);

	अगर (*curr_pmask & mask)  /* disallow acting twice on the same location */
		जाओ out_err;

	*curr_pmask |= mask;
	*curr_pval  |= (val & mask);

	वापस 0;

out_err:
	वापस -EOPNOTSUPP;
पूर्ण

काष्ठा mlx5_fields अणु
	u8  field;
	u8  field_bsize;
	u32 field_mask;
	u32 offset;
	u32 match_offset;
पूर्ण;

#घोषणा OFFLOAD(fw_field, field_bsize, field_mask, field, off, match_field) \
		अणुMLX5_ACTION_IN_FIELD_OUT_ ## fw_field, field_bsize, field_mask, \
		 दुरत्व(काष्ठा pedit_headers, field) + (off), \
		 MLX5_BYTE_OFF(fte_match_set_lyr_2_4, match_field)पूर्ण

/* masked values are the same and there are no reग_लिखोs that करो not have a
 * match.
 */
#घोषणा SAME_VAL_MASK(type, valp, maskp, matchvalp, matchmaskp) (अणु \
	type matchmaskx = *(type *)(matchmaskp); \
	type matchvalx = *(type *)(matchvalp); \
	type maskx = *(type *)(maskp); \
	type valx = *(type *)(valp); \
	\
	(valx & maskx) == (matchvalx & matchmaskx) && !(maskx & (maskx ^ \
								 matchmaskx)); \
पूर्ण)

अटल bool cmp_val_mask(व्योम *valp, व्योम *maskp, व्योम *matchvalp,
			 व्योम *matchmaskp, u8 bsize)
अणु
	bool same = false;

	चयन (bsize) अणु
	हाल 8:
		same = SAME_VAL_MASK(u8, valp, maskp, matchvalp, matchmaskp);
		अवरोध;
	हाल 16:
		same = SAME_VAL_MASK(u16, valp, maskp, matchvalp, matchmaskp);
		अवरोध;
	हाल 32:
		same = SAME_VAL_MASK(u32, valp, maskp, matchvalp, matchmaskp);
		अवरोध;
	पूर्ण

	वापस same;
पूर्ण

अटल काष्ठा mlx5_fields fields[] = अणु
	OFFLOAD(DMAC_47_16, 32, U32_MAX, eth.h_dest[0], 0, dmac_47_16),
	OFFLOAD(DMAC_15_0,  16, U16_MAX, eth.h_dest[4], 0, dmac_15_0),
	OFFLOAD(SMAC_47_16, 32, U32_MAX, eth.h_source[0], 0, smac_47_16),
	OFFLOAD(SMAC_15_0,  16, U16_MAX, eth.h_source[4], 0, smac_15_0),
	OFFLOAD(ETHERTYPE,  16, U16_MAX, eth.h_proto, 0, ethertype),
	OFFLOAD(FIRST_VID,  16, U16_MAX, vlan.h_vlan_TCI, 0, first_vid),

	OFFLOAD(IP_DSCP, 8,    0xfc, ip4.tos,   0, ip_dscp),
	OFFLOAD(IP_TTL,  8,  U8_MAX, ip4.ttl,   0, ttl_hoplimit),
	OFFLOAD(SIPV4,  32, U32_MAX, ip4.saddr, 0, src_ipv4_src_ipv6.ipv4_layout.ipv4),
	OFFLOAD(DIPV4,  32, U32_MAX, ip4.daddr, 0, dst_ipv4_dst_ipv6.ipv4_layout.ipv4),

	OFFLOAD(SIPV6_127_96, 32, U32_MAX, ip6.saddr.s6_addr32[0], 0,
		src_ipv4_src_ipv6.ipv6_layout.ipv6[0]),
	OFFLOAD(SIPV6_95_64,  32, U32_MAX, ip6.saddr.s6_addr32[1], 0,
		src_ipv4_src_ipv6.ipv6_layout.ipv6[4]),
	OFFLOAD(SIPV6_63_32,  32, U32_MAX, ip6.saddr.s6_addr32[2], 0,
		src_ipv4_src_ipv6.ipv6_layout.ipv6[8]),
	OFFLOAD(SIPV6_31_0,   32, U32_MAX, ip6.saddr.s6_addr32[3], 0,
		src_ipv4_src_ipv6.ipv6_layout.ipv6[12]),
	OFFLOAD(DIPV6_127_96, 32, U32_MAX, ip6.daddr.s6_addr32[0], 0,
		dst_ipv4_dst_ipv6.ipv6_layout.ipv6[0]),
	OFFLOAD(DIPV6_95_64,  32, U32_MAX, ip6.daddr.s6_addr32[1], 0,
		dst_ipv4_dst_ipv6.ipv6_layout.ipv6[4]),
	OFFLOAD(DIPV6_63_32,  32, U32_MAX, ip6.daddr.s6_addr32[2], 0,
		dst_ipv4_dst_ipv6.ipv6_layout.ipv6[8]),
	OFFLOAD(DIPV6_31_0,   32, U32_MAX, ip6.daddr.s6_addr32[3], 0,
		dst_ipv4_dst_ipv6.ipv6_layout.ipv6[12]),
	OFFLOAD(IPV6_HOPLIMIT, 8,  U8_MAX, ip6.hop_limit, 0, ttl_hoplimit),
	OFFLOAD(IP_DSCP, 16,  0xc00f, ip6, 0, ip_dscp),

	OFFLOAD(TCP_SPORT, 16, U16_MAX, tcp.source,  0, tcp_sport),
	OFFLOAD(TCP_DPORT, 16, U16_MAX, tcp.dest,    0, tcp_dport),
	/* in linux iphdr tcp_flags is 8 bits दीर्घ */
	OFFLOAD(TCP_FLAGS,  8,  U8_MAX, tcp.ack_seq, 5, tcp_flags),

	OFFLOAD(UDP_SPORT, 16, U16_MAX, udp.source, 0, udp_sport),
	OFFLOAD(UDP_DPORT, 16, U16_MAX, udp.dest,   0, udp_dport),
पूर्ण;

अटल अचिन्हित दीर्घ mask_to_le(अचिन्हित दीर्घ mask, पूर्णांक size)
अणु
	__be32 mask_be32;
	__be16 mask_be16;

	अगर (size == 32) अणु
		mask_be32 = (__क्रमce __be32)(mask);
		mask = (__क्रमce अचिन्हित दीर्घ)cpu_to_le32(be32_to_cpu(mask_be32));
	पूर्ण अन्यथा अगर (size == 16) अणु
		mask_be32 = (__क्रमce __be32)(mask);
		mask_be16 = *(__be16 *)&mask_be32;
		mask = (__क्रमce अचिन्हित दीर्घ)cpu_to_le16(be16_to_cpu(mask_be16));
	पूर्ण

	वापस mask;
पूर्ण
अटल पूर्णांक offload_pedit_fields(काष्ठा mlx5e_priv *priv,
				पूर्णांक namespace,
				काष्ठा pedit_headers_action *hdrs,
				काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				u32 *action_flags,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा pedit_headers *set_masks, *add_masks, *set_vals, *add_vals;
	पूर्णांक i, action_size, first, last, next_z;
	व्योम *headers_c, *headers_v, *action, *vals_p;
	u32 *s_masks_p, *a_masks_p, s_mask, a_mask;
	काष्ठा mlx5e_tc_mod_hdr_acts *mod_acts;
	काष्ठा mlx5_fields *f;
	अचिन्हित दीर्घ mask, field_mask;
	पूर्णांक err;
	u8 cmd;

	mod_acts = &parse_attr->mod_hdr_acts;
	headers_c = get_match_headers_criteria(*action_flags, &parse_attr->spec);
	headers_v = get_match_headers_value(*action_flags, &parse_attr->spec);

	set_masks = &hdrs[0].masks;
	add_masks = &hdrs[1].masks;
	set_vals = &hdrs[0].vals;
	add_vals = &hdrs[1].vals;

	action_size = MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः);

	क्रम (i = 0; i < ARRAY_SIZE(fields); i++) अणु
		bool skip;

		f = &fields[i];
		/* aव्योम seeing bits set from previous iterations */
		s_mask = 0;
		a_mask = 0;

		s_masks_p = (व्योम *)set_masks + f->offset;
		a_masks_p = (व्योम *)add_masks + f->offset;

		s_mask = *s_masks_p & f->field_mask;
		a_mask = *a_masks_p & f->field_mask;

		अगर (!s_mask && !a_mask) /* nothing to offload here */
			जारी;

		अगर (s_mask && a_mask) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "can't set and add to the same HW field");
			prपूर्णांकk(KERN_WARNING "mlx5: can't set and add to the same HW field (%x)\n", f->field);
			वापस -EOPNOTSUPP;
		पूर्ण

		skip = false;
		अगर (s_mask) अणु
			व्योम *match_mask = headers_c + f->match_offset;
			व्योम *match_val = headers_v + f->match_offset;

			cmd  = MLX5_ACTION_TYPE_SET;
			mask = s_mask;
			vals_p = (व्योम *)set_vals + f->offset;
			/* करोn't reग_लिखो अगर we have a match on the same value */
			अगर (cmp_val_mask(vals_p, s_masks_p, match_val,
					 match_mask, f->field_bsize))
				skip = true;
			/* clear to denote we consumed this field */
			*s_masks_p &= ~f->field_mask;
		पूर्ण अन्यथा अणु
			cmd  = MLX5_ACTION_TYPE_ADD;
			mask = a_mask;
			vals_p = (व्योम *)add_vals + f->offset;
			/* add 0 is no change */
			अगर ((*(u32 *)vals_p & f->field_mask) == 0)
				skip = true;
			/* clear to denote we consumed this field */
			*a_masks_p &= ~f->field_mask;
		पूर्ण
		अगर (skip)
			जारी;

		mask = mask_to_le(mask, f->field_bsize);

		first = find_first_bit(&mask, f->field_bsize);
		next_z = find_next_zero_bit(&mask, f->field_bsize, first);
		last  = find_last_bit(&mask, f->field_bsize);
		अगर (first < next_z && next_z < last) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "rewrite of few sub-fields isn't supported");
			prपूर्णांकk(KERN_WARNING "mlx5: rewrite of few sub-fields (mask %lx) isn't offloaded\n",
			       mask);
			वापस -EOPNOTSUPP;
		पूर्ण

		err = alloc_mod_hdr_actions(priv->mdev, namespace, mod_acts);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "too many pedit actions, can't offload");
			mlx5_core_warn(priv->mdev,
				       "mlx5: parsed %d pedit actions, can't do more\n",
				       mod_acts->num_actions);
			वापस err;
		पूर्ण

		action = mod_acts->actions +
			 (mod_acts->num_actions * action_size);
		MLX5_SET(set_action_in, action, action_type, cmd);
		MLX5_SET(set_action_in, action, field, f->field);

		अगर (cmd == MLX5_ACTION_TYPE_SET) अणु
			पूर्णांक start;

			field_mask = mask_to_le(f->field_mask, f->field_bsize);

			/* अगर field is bit sized it can start not from first bit */
			start = find_first_bit(&field_mask, f->field_bsize);

			MLX5_SET(set_action_in, action, offset, first - start);
			/* length is num of bits to be written, zero means length of 32 */
			MLX5_SET(set_action_in, action, length, (last - first + 1));
		पूर्ण

		अगर (f->field_bsize == 32)
			MLX5_SET(set_action_in, action, data, ntohl(*(__be32 *)vals_p) >> first);
		अन्यथा अगर (f->field_bsize == 16)
			MLX5_SET(set_action_in, action, data, ntohs(*(__be16 *)vals_p) >> first);
		अन्यथा अगर (f->field_bsize == 8)
			MLX5_SET(set_action_in, action, data, *(u8 *)vals_p >> first);

		++mod_acts->num_actions;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_flow_namespace_max_modअगरy_action(काष्ठा mlx5_core_dev *mdev,
						  पूर्णांक namespace)
अणु
	अगर (namespace == MLX5_FLOW_NAMESPACE_FDB) /* FDB offloading */
		वापस MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, max_modअगरy_header_actions);
	अन्यथा /* namespace is MLX5_FLOW_NAMESPACE_KERNEL - NIC offloading */
		वापस MLX5_CAP_FLOWTABLE_NIC_RX(mdev, max_modअगरy_header_actions);
पूर्ण

पूर्णांक alloc_mod_hdr_actions(काष्ठा mlx5_core_dev *mdev,
			  पूर्णांक namespace,
			  काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts)
अणु
	पूर्णांक action_size, new_num_actions, max_hw_actions;
	माप_प्रकार new_sz, old_sz;
	व्योम *ret;

	अगर (mod_hdr_acts->num_actions < mod_hdr_acts->max_actions)
		वापस 0;

	action_size = MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः);

	max_hw_actions = mlx5e_flow_namespace_max_modअगरy_action(mdev,
								namespace);
	new_num_actions = min(max_hw_actions,
			      mod_hdr_acts->actions ?
			      mod_hdr_acts->max_actions * 2 : 1);
	अगर (mod_hdr_acts->max_actions == new_num_actions)
		वापस -ENOSPC;

	new_sz = action_size * new_num_actions;
	old_sz = mod_hdr_acts->max_actions * action_size;
	ret = kपुनः_स्मृति(mod_hdr_acts->actions, new_sz, GFP_KERNEL);
	अगर (!ret)
		वापस -ENOMEM;

	स_रखो(ret + old_sz, 0, new_sz - old_sz);
	mod_hdr_acts->actions = ret;
	mod_hdr_acts->max_actions = new_num_actions;

	वापस 0;
पूर्ण

व्योम dealloc_mod_hdr_actions(काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts)
अणु
	kमुक्त(mod_hdr_acts->actions);
	mod_hdr_acts->actions = शून्य;
	mod_hdr_acts->num_actions = 0;
	mod_hdr_acts->max_actions = 0;
पूर्ण

अटल स्थिर काष्ठा pedit_headers zero_masks = अणुपूर्ण;

अटल पूर्णांक
parse_pedit_to_modअगरy_hdr(काष्ठा mlx5e_priv *priv,
			  स्थिर काष्ठा flow_action_entry *act, पूर्णांक namespace,
			  काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
			  काष्ठा pedit_headers_action *hdrs,
			  काष्ठा netlink_ext_ack *extack)
अणु
	u8 cmd = (act->id == FLOW_ACTION_MANGLE) ? 0 : 1;
	पूर्णांक err = -EOPNOTSUPP;
	u32 mask, val, offset;
	u8 htype;

	htype = act->mangle.htype;
	err = -EOPNOTSUPP; /* can't be all optimistic */

	अगर (htype == FLOW_ACT_MANGLE_UNSPEC) अणु
		NL_SET_ERR_MSG_MOD(extack, "legacy pedit isn't offloaded");
		जाओ out_err;
	पूर्ण

	अगर (!mlx5e_flow_namespace_max_modअगरy_action(priv->mdev, namespace)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "The pedit offload action is not supported");
		जाओ out_err;
	पूर्ण

	mask = act->mangle.mask;
	val = act->mangle.val;
	offset = act->mangle.offset;

	err = set_pedit_val(htype, ~mask, val, offset, &hdrs[cmd]);
	अगर (err)
		जाओ out_err;

	hdrs[cmd].pedits++;

	वापस 0;
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक
parse_pedit_to_reक्रमmat(काष्ठा mlx5e_priv *priv,
			स्थिर काष्ठा flow_action_entry *act,
			काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
			काष्ठा netlink_ext_ack *extack)
अणु
	u32 mask, val, offset;
	u32 *p;

	अगर (act->id != FLOW_ACTION_MANGLE)
		वापस -EOPNOTSUPP;

	अगर (act->mangle.htype != FLOW_ACT_MANGLE_HDR_TYPE_ETH) अणु
		NL_SET_ERR_MSG_MOD(extack, "Only Ethernet modification is supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	mask = ~act->mangle.mask;
	val = act->mangle.val;
	offset = act->mangle.offset;
	p = (u32 *)&parse_attr->eth;
	*(p + (offset >> 2)) |= (val & mask);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_tc_pedit_action(काष्ठा mlx5e_priv *priv,
				 स्थिर काष्ठा flow_action_entry *act, पूर्णांक namespace,
				 काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				 काष्ठा pedit_headers_action *hdrs,
				 काष्ठा mlx5e_tc_flow *flow,
				 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (flow && flow_flag_test(flow, L3_TO_L2_DECAP))
		वापस parse_pedit_to_reक्रमmat(priv, act, parse_attr, extack);

	वापस parse_pedit_to_modअगरy_hdr(priv, act, namespace,
					 parse_attr, hdrs, extack);
पूर्ण

अटल पूर्णांक alloc_tc_pedit_action(काष्ठा mlx5e_priv *priv, पूर्णांक namespace,
				 काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				 काष्ठा pedit_headers_action *hdrs,
				 u32 *action_flags,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा pedit_headers *cmd_masks;
	पूर्णांक err;
	u8 cmd;

	err = offload_pedit_fields(priv, namespace, hdrs, parse_attr,
				   action_flags, extack);
	अगर (err < 0)
		जाओ out_dealloc_parsed_actions;

	क्रम (cmd = 0; cmd < __PEDIT_CMD_MAX; cmd++) अणु
		cmd_masks = &hdrs[cmd].masks;
		अगर (स_भेद(cmd_masks, &zero_masks, माप(zero_masks))) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "attempt to offload an unsupported field");
			netdev_warn(priv->netdev, "attempt to offload an unsupported field (cmd %d)\n", cmd);
			prपूर्णांक_hex_dump(KERN_WARNING, "mask: ", DUMP_PREFIX_ADDRESS,
				       16, 1, cmd_masks, माप(zero_masks), true);
			err = -EOPNOTSUPP;
			जाओ out_dealloc_parsed_actions;
		पूर्ण
	पूर्ण

	वापस 0;

out_dealloc_parsed_actions:
	dealloc_mod_hdr_actions(&parse_attr->mod_hdr_acts);
	वापस err;
पूर्ण

अटल bool csum_offload_supported(काष्ठा mlx5e_priv *priv,
				   u32 action,
				   u32 update_flags,
				   काष्ठा netlink_ext_ack *extack)
अणु
	u32 prot_flags = TCA_CSUM_UPDATE_FLAG_IPV4HDR | TCA_CSUM_UPDATE_FLAG_TCP |
			 TCA_CSUM_UPDATE_FLAG_UDP;

	/*  The HW recalcs checksums only अगर re-writing headers */
	अगर (!(action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "TC csum action is only offloaded with pedit");
		netdev_warn(priv->netdev,
			    "TC csum action is only offloaded with pedit\n");
		वापस false;
	पूर्ण

	अगर (update_flags & ~prot_flags) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "can't offload TC csum action for some header/s");
		netdev_warn(priv->netdev,
			    "can't offload TC csum action for some header/s - flags %#x\n",
			    update_flags);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा ip_ttl_word अणु
	__u8	ttl;
	__u8	protocol;
	__sum16	check;
पूर्ण;

काष्ठा ipv6_hoplimit_word अणु
	__be16	payload_len;
	__u8	nexthdr;
	__u8	hop_limit;
पूर्ण;

अटल पूर्णांक is_action_keys_supported(स्थिर काष्ठा flow_action_entry *act,
				    bool ct_flow, bool *modअगरy_ip_header,
				    bool *modअगरy_tuple,
				    काष्ठा netlink_ext_ack *extack)
अणु
	u32 mask, offset;
	u8 htype;

	htype = act->mangle.htype;
	offset = act->mangle.offset;
	mask = ~act->mangle.mask;
	/* For IPv4 & IPv6 header check 4 byte word,
	 * to determine that modअगरied fields
	 * are NOT ttl & hop_limit only.
	 */
	अगर (htype == FLOW_ACT_MANGLE_HDR_TYPE_IP4) अणु
		काष्ठा ip_ttl_word *ttl_word =
			(काष्ठा ip_ttl_word *)&mask;

		अगर (offset != दुरत्व(काष्ठा iphdr, ttl) ||
		    ttl_word->protocol ||
		    ttl_word->check) अणु
			*modअगरy_ip_header = true;
		पूर्ण

		अगर (offset >= दुरत्व(काष्ठा iphdr, saddr))
			*modअगरy_tuple = true;

		अगर (ct_flow && *modअगरy_tuple) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "can't offload re-write of ipv4 address with action ct");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अगर (htype == FLOW_ACT_MANGLE_HDR_TYPE_IP6) अणु
		काष्ठा ipv6_hoplimit_word *hoplimit_word =
			(काष्ठा ipv6_hoplimit_word *)&mask;

		अगर (offset != दुरत्व(काष्ठा ipv6hdr, payload_len) ||
		    hoplimit_word->payload_len ||
		    hoplimit_word->nexthdr) अणु
			*modअगरy_ip_header = true;
		पूर्ण

		अगर (ct_flow && offset >= दुरत्व(काष्ठा ipv6hdr, saddr))
			*modअगरy_tuple = true;

		अगर (ct_flow && *modअगरy_tuple) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "can't offload re-write of ipv6 address with action ct");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अगर (htype == FLOW_ACT_MANGLE_HDR_TYPE_TCP ||
		   htype == FLOW_ACT_MANGLE_HDR_TYPE_UDP) अणु
		*modअगरy_tuple = true;
		अगर (ct_flow) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "can't offload re-write of transport header ports with action ct");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool modअगरy_tuple_supported(bool modअगरy_tuple, bool ct_clear,
				   bool ct_flow, काष्ठा netlink_ext_ack *extack,
				   काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5_flow_spec *spec)
अणु
	अगर (!modअगरy_tuple || ct_clear)
		वापस true;

	अगर (ct_flow) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "can't offload tuple modification with non-clear ct()");
		netdev_info(priv->netdev,
			    "can't offload tuple modification with non-clear ct()");
		वापस false;
	पूर्ण

	/* Add ct_state=-trk match so it will be offloaded क्रम non ct flows
	 * (or after clear action), as otherwise, since the tuple is changed,
	 * we can't restore ct state
	 */
	अगर (mlx5_tc_ct_add_no_trk_match(spec)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "can't offload tuple modification with ct matches and no ct(clear) action");
		netdev_info(priv->netdev,
			    "can't offload tuple modification with ct matches and no ct(clear) action");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool modअगरy_header_match_supported(काष्ठा mlx5e_priv *priv,
					  काष्ठा mlx5_flow_spec *spec,
					  काष्ठा flow_action *flow_action,
					  u32 actions, bool ct_flow,
					  bool ct_clear,
					  काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा flow_action_entry *act;
	bool modअगरy_ip_header, modअगरy_tuple;
	व्योम *headers_c;
	व्योम *headers_v;
	u16 ethertype;
	u8 ip_proto;
	पूर्णांक i, err;

	headers_c = get_match_headers_criteria(actions, spec);
	headers_v = get_match_headers_value(actions, spec);
	ethertype = MLX5_GET(fte_match_set_lyr_2_4, headers_v, ethertype);

	/* क्रम non-IP we only re-ग_लिखो MACs, so we're okay */
	अगर (MLX5_GET(fte_match_set_lyr_2_4, headers_c, ip_version) == 0 &&
	    ethertype != ETH_P_IP && ethertype != ETH_P_IPV6)
		जाओ out_ok;

	modअगरy_ip_header = false;
	modअगरy_tuple = false;
	flow_action_क्रम_each(i, act, flow_action) अणु
		अगर (act->id != FLOW_ACTION_MANGLE &&
		    act->id != FLOW_ACTION_ADD)
			जारी;

		err = is_action_keys_supported(act, ct_flow,
					       &modअगरy_ip_header,
					       &modअगरy_tuple, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!modअगरy_tuple_supported(modअगरy_tuple, ct_clear, ct_flow, extack,
				    priv, spec))
		वापस false;

	ip_proto = MLX5_GET(fte_match_set_lyr_2_4, headers_v, ip_protocol);
	अगर (modअगरy_ip_header && ip_proto != IPPROTO_TCP &&
	    ip_proto != IPPROTO_UDP && ip_proto != IPPROTO_ICMP) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "can't offload re-write of non TCP/UDP");
		netdev_info(priv->netdev, "can't offload re-write of ip proto %d\n",
			    ip_proto);
		वापस false;
	पूर्ण

out_ok:
	वापस true;
पूर्ण

अटल bool actions_match_supported(काष्ठा mlx5e_priv *priv,
				    काष्ठा flow_action *flow_action,
				    काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				    काष्ठा mlx5e_tc_flow *flow,
				    काष्ठा netlink_ext_ack *extack)
अणु
	bool ct_flow = false, ct_clear = false;
	u32 actions;

	ct_clear = flow->attr->ct_attr.ct_action &
		TCA_CT_ACT_CLEAR;
	ct_flow = flow_flag_test(flow, CT) && !ct_clear;
	actions = flow->attr->action;

	अगर (mlx5e_is_eचयन_flow(flow)) अणु
		अगर (flow->attr->esw_attr->split_count && ct_flow &&
		    !MLX5_CAP_GEN(flow->attr->esw_attr->in_mdev, reg_c_preserve)) अणु
			/* All रेजिस्टरs used by ct are cleared when using
			 * split rules.
			 */
			NL_SET_ERR_MSG_MOD(extack,
					   "Can't offload mirroring with action ct");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (actions & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		वापस modअगरy_header_match_supported(priv, &parse_attr->spec,
						     flow_action, actions,
						     ct_flow, ct_clear,
						     extack);

	वापस true;
पूर्ण

अटल bool same_port_devs(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_priv *peer_priv)
अणु
	वापस priv->mdev == peer_priv->mdev;
पूर्ण

अटल bool same_hw_devs(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_priv *peer_priv)
अणु
	काष्ठा mlx5_core_dev *fmdev, *pmdev;
	u64 fप्रणाली_guid, pप्रणाली_guid;

	fmdev = priv->mdev;
	pmdev = peer_priv->mdev;

	fप्रणाली_guid = mlx5_query_nic_प्रणाली_image_guid(fmdev);
	pप्रणाली_guid = mlx5_query_nic_प्रणाली_image_guid(pmdev);

	वापस (fप्रणाली_guid == pप्रणाली_guid);
पूर्ण

अटल bool same_vf_reps(काष्ठा mlx5e_priv *priv,
			 काष्ठा net_device *out_dev)
अणु
	वापस mlx5e_eचयन_vf_rep(priv->netdev) &&
	       priv->netdev == out_dev;
पूर्ण

अटल पूर्णांक add_vlan_reग_लिखो_action(काष्ठा mlx5e_priv *priv, पूर्णांक namespace,
				   स्थिर काष्ठा flow_action_entry *act,
				   काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				   काष्ठा pedit_headers_action *hdrs,
				   u32 *action, काष्ठा netlink_ext_ack *extack)
अणु
	u16 mask16 = VLAN_VID_MASK;
	u16 val16 = act->vlan.vid & VLAN_VID_MASK;
	स्थिर काष्ठा flow_action_entry pedit_act = अणु
		.id = FLOW_ACTION_MANGLE,
		.mangle.htype = FLOW_ACT_MANGLE_HDR_TYPE_ETH,
		.mangle.offset = दुरत्व(काष्ठा vlan_ethhdr, h_vlan_TCI),
		.mangle.mask = ~(u32)be16_to_cpu(*(__be16 *)&mask16),
		.mangle.val = (u32)be16_to_cpu(*(__be16 *)&val16),
	पूर्ण;
	u8 match_prio_mask, match_prio_val;
	व्योम *headers_c, *headers_v;
	पूर्णांक err;

	headers_c = get_match_headers_criteria(*action, &parse_attr->spec);
	headers_v = get_match_headers_value(*action, &parse_attr->spec);

	अगर (!(MLX5_GET(fte_match_set_lyr_2_4, headers_c, cvlan_tag) &&
	      MLX5_GET(fte_match_set_lyr_2_4, headers_v, cvlan_tag))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "VLAN rewrite action must have VLAN protocol match");
		वापस -EOPNOTSUPP;
	पूर्ण

	match_prio_mask = MLX5_GET(fte_match_set_lyr_2_4, headers_c, first_prio);
	match_prio_val = MLX5_GET(fte_match_set_lyr_2_4, headers_v, first_prio);
	अगर (act->vlan.prio != (match_prio_val & match_prio_mask)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Changing VLAN prio is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	err = parse_tc_pedit_action(priv, &pedit_act, namespace, parse_attr, hdrs, शून्य, extack);
	*action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;

	वापस err;
पूर्ण

अटल पूर्णांक
add_vlan_prio_tag_reग_लिखो_action(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				 काष्ठा pedit_headers_action *hdrs,
				 u32 *action, काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा flow_action_entry prio_tag_act = अणु
		.vlan.vid = 0,
		.vlan.prio =
			MLX5_GET(fte_match_set_lyr_2_4,
				 get_match_headers_value(*action,
							 &parse_attr->spec),
				 first_prio) &
			MLX5_GET(fte_match_set_lyr_2_4,
				 get_match_headers_criteria(*action,
							    &parse_attr->spec),
				 first_prio),
	पूर्ण;

	वापस add_vlan_reग_लिखो_action(priv, MLX5_FLOW_NAMESPACE_FDB,
				       &prio_tag_act, parse_attr, hdrs, action,
				       extack);
पूर्ण

अटल पूर्णांक validate_जाओ_chain(काष्ठा mlx5e_priv *priv,
			       काष्ठा mlx5e_tc_flow *flow,
			       स्थिर काष्ठा flow_action_entry *act,
			       u32 actions,
			       काष्ठा netlink_ext_ack *extack)
अणु
	bool is_esw = mlx5e_is_eचयन_flow(flow);
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	bool ft_flow = mlx5e_is_ft_flow(flow);
	u32 dest_chain = act->chain_index;
	काष्ठा mlx5_fs_chains *chains;
	काष्ठा mlx5_eचयन *esw;
	u32 reक्रमmat_and_fwd;
	u32 max_chain;

	esw = priv->mdev->priv.eचयन;
	chains = is_esw ? esw_chains(esw) : nic_chains(priv);
	max_chain = mlx5_chains_get_chain_range(chains);
	reक्रमmat_and_fwd = is_esw ?
			   MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev, reक्रमmat_and_fwd_to_table) :
			   MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, reक्रमmat_and_fwd_to_table);

	अगर (ft_flow) अणु
		NL_SET_ERR_MSG_MOD(extack, "Goto action is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!mlx5_chains_backwards_supported(chains) &&
	    dest_chain <= attr->chain) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Goto lower numbered chain isn't supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (dest_chain > max_chain) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Requested destination chain is out of supported range");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (actions & (MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT |
		       MLX5_FLOW_CONTEXT_ACTION_DECAP) &&
	    !reक्रमmat_and_fwd) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Goto chain is not allowed if action has reformat or decap");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_tc_nic_actions(काष्ठा mlx5e_priv *priv,
				काष्ठा flow_action *flow_action,
				काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
				काष्ठा mlx5e_tc_flow *flow,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	काष्ठा pedit_headers_action hdrs[2] = अणुपूर्ण;
	स्थिर काष्ठा flow_action_entry *act;
	काष्ठा mlx5_nic_flow_attr *nic_attr;
	u32 action = 0;
	पूर्णांक err, i;

	अगर (!flow_action_has_entries(flow_action))
		वापस -EINVAL;

	अगर (!flow_action_hw_stats_check(flow_action, extack,
					FLOW_ACTION_HW_STATS_DELAYED_BIT))
		वापस -EOPNOTSUPP;

	nic_attr = attr->nic_attr;

	nic_attr->flow_tag = MLX5_FS_DEFAULT_FLOW_TAG;

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_ACCEPT:
			action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
				  MLX5_FLOW_CONTEXT_ACTION_COUNT;
			अवरोध;
		हाल FLOW_ACTION_DROP:
			action |= MLX5_FLOW_CONTEXT_ACTION_DROP;
			अगर (MLX5_CAP_FLOWTABLE(priv->mdev,
					       flow_table_properties_nic_receive.flow_counter))
				action |= MLX5_FLOW_CONTEXT_ACTION_COUNT;
			अवरोध;
		हाल FLOW_ACTION_MANGLE:
		हाल FLOW_ACTION_ADD:
			err = parse_tc_pedit_action(priv, act, MLX5_FLOW_NAMESPACE_KERNEL,
						    parse_attr, hdrs, शून्य, extack);
			अगर (err)
				वापस err;

			action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
			अवरोध;
		हाल FLOW_ACTION_VLAN_MANGLE:
			err = add_vlan_reग_लिखो_action(priv,
						      MLX5_FLOW_NAMESPACE_KERNEL,
						      act, parse_attr, hdrs,
						      &action, extack);
			अगर (err)
				वापस err;

			अवरोध;
		हाल FLOW_ACTION_CSUM:
			अगर (csum_offload_supported(priv, action,
						   act->csum_flags,
						   extack))
				अवरोध;

			वापस -EOPNOTSUPP;
		हाल FLOW_ACTION_REसूचीECT: अणु
			काष्ठा net_device *peer_dev = act->dev;

			अगर (priv->netdev->netdev_ops == peer_dev->netdev_ops &&
			    same_hw_devs(priv, netdev_priv(peer_dev))) अणु
				parse_attr->mirred_अगरindex[0] = peer_dev->अगरindex;
				flow_flag_set(flow, HAIRPIN);
				action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
					  MLX5_FLOW_CONTEXT_ACTION_COUNT;
			पूर्ण अन्यथा अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "device is not on same HW, can't offload");
				netdev_warn(priv->netdev, "device %s not on same HW, can't offload\n",
					    peer_dev->name);
				वापस -EINVAL;
			पूर्ण
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_MARK: अणु
			u32 mark = act->mark;

			अगर (mark & ~MLX5E_TC_FLOW_ID_MASK) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Bad flow mark - only 16 bit is supported");
				वापस -EINVAL;
			पूर्ण

			nic_attr->flow_tag = mark;
			action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_GOTO:
			err = validate_जाओ_chain(priv, flow, act, action,
						  extack);
			अगर (err)
				वापस err;

			action |= MLX5_FLOW_CONTEXT_ACTION_COUNT;
			attr->dest_chain = act->chain_index;
			अवरोध;
		हाल FLOW_ACTION_CT:
			err = mlx5_tc_ct_parse_action(get_ct_priv(priv), attr, act, extack);
			अगर (err)
				वापस err;

			flow_flag_set(flow, CT);
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "The offload action is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (hdrs[TCA_PEDIT_KEY_EX_CMD_SET].pedits ||
	    hdrs[TCA_PEDIT_KEY_EX_CMD_ADD].pedits) अणु
		err = alloc_tc_pedit_action(priv, MLX5_FLOW_NAMESPACE_KERNEL,
					    parse_attr, hdrs, &action, extack);
		अगर (err)
			वापस err;
		/* in हाल all pedit actions are skipped, हटाओ the MOD_HDR
		 * flag.
		 */
		अगर (parse_attr->mod_hdr_acts.num_actions == 0) अणु
			action &= ~MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
			dealloc_mod_hdr_actions(&parse_attr->mod_hdr_acts);
		पूर्ण
	पूर्ण

	attr->action = action;

	अगर (attr->dest_chain) अणु
		अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) अणु
			NL_SET_ERR_MSG(extack, "Mirroring goto chain rules isn't supported");
			वापस -EOPNOTSUPP;
		पूर्ण
		attr->action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	पूर्ण

	अगर (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		attr->action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;

	अगर (!actions_match_supported(priv, flow_action, parse_attr, flow, extack))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल bool is_merged_eचयन_vfs(काष्ठा mlx5e_priv *priv,
				  काष्ठा net_device *peer_netdev)
अणु
	काष्ठा mlx5e_priv *peer_priv;

	peer_priv = netdev_priv(peer_netdev);

	वापस (MLX5_CAP_ESW(priv->mdev, merged_eचयन) &&
		mlx5e_eचयन_vf_rep(priv->netdev) &&
		mlx5e_eचयन_vf_rep(peer_netdev) &&
		same_hw_devs(priv, peer_priv));
पूर्ण

अटल पूर्णांक parse_tc_vlan_action(काष्ठा mlx5e_priv *priv,
				स्थिर काष्ठा flow_action_entry *act,
				काष्ठा mlx5_esw_flow_attr *attr,
				u32 *action)
अणु
	u8 vlan_idx = attr->total_vlan;

	अगर (vlan_idx >= MLX5_FS_VLAN_DEPTH)
		वापस -EOPNOTSUPP;

	चयन (act->id) अणु
	हाल FLOW_ACTION_VLAN_POP:
		अगर (vlan_idx) अणु
			अगर (!mlx5_eचयन_vlan_actions_supported(priv->mdev,
								 MLX5_FS_VLAN_DEPTH))
				वापस -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2;
		पूर्ण अन्यथा अणु
			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_POP;
		पूर्ण
		अवरोध;
	हाल FLOW_ACTION_VLAN_PUSH:
		attr->vlan_vid[vlan_idx] = act->vlan.vid;
		attr->vlan_prio[vlan_idx] = act->vlan.prio;
		attr->vlan_proto[vlan_idx] = act->vlan.proto;
		अगर (!attr->vlan_proto[vlan_idx])
			attr->vlan_proto[vlan_idx] = htons(ETH_P_8021Q);

		अगर (vlan_idx) अणु
			अगर (!mlx5_eचयन_vlan_actions_supported(priv->mdev,
								 MLX5_FS_VLAN_DEPTH))
				वापस -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2;
		पूर्ण अन्यथा अणु
			अगर (!mlx5_eचयन_vlan_actions_supported(priv->mdev, 1) &&
			    (act->vlan.proto != htons(ETH_P_8021Q) ||
			     act->vlan.prio))
				वापस -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	attr->total_vlan = vlan_idx + 1;

	वापस 0;
पूर्ण

अटल काष्ठा net_device *get_fdb_out_dev(काष्ठा net_device *uplink_dev,
					  काष्ठा net_device *out_dev)
अणु
	काष्ठा net_device *fdb_out_dev = out_dev;
	काष्ठा net_device *uplink_upper;

	rcu_पढ़ो_lock();
	uplink_upper = netdev_master_upper_dev_get_rcu(uplink_dev);
	अगर (uplink_upper && netअगर_is_lag_master(uplink_upper) &&
	    uplink_upper == out_dev) अणु
		fdb_out_dev = uplink_dev;
	पूर्ण अन्यथा अगर (netअगर_is_lag_master(out_dev)) अणु
		fdb_out_dev = bond_option_active_slave_get_rcu(netdev_priv(out_dev));
		अगर (fdb_out_dev &&
		    (!mlx5e_eचयन_rep(fdb_out_dev) ||
		     !netdev_port_same_parent_id(fdb_out_dev, uplink_dev)))
			fdb_out_dev = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस fdb_out_dev;
पूर्ण

अटल पूर्णांक add_vlan_push_action(काष्ठा mlx5e_priv *priv,
				काष्ठा mlx5_flow_attr *attr,
				काष्ठा net_device **out_dev,
				u32 *action)
अणु
	काष्ठा net_device *vlan_dev = *out_dev;
	काष्ठा flow_action_entry vlan_act = अणु
		.id = FLOW_ACTION_VLAN_PUSH,
		.vlan.vid = vlan_dev_vlan_id(vlan_dev),
		.vlan.proto = vlan_dev_vlan_proto(vlan_dev),
		.vlan.prio = 0,
	पूर्ण;
	पूर्णांक err;

	err = parse_tc_vlan_action(priv, &vlan_act, attr->esw_attr, action);
	अगर (err)
		वापस err;

	rcu_पढ़ो_lock();
	*out_dev = dev_get_by_index_rcu(dev_net(vlan_dev), dev_get_अगरlink(vlan_dev));
	rcu_पढ़ो_unlock();
	अगर (!*out_dev)
		वापस -ENODEV;

	अगर (is_vlan_dev(*out_dev))
		err = add_vlan_push_action(priv, attr, out_dev, action);

	वापस err;
पूर्ण

अटल पूर्णांक add_vlan_pop_action(काष्ठा mlx5e_priv *priv,
			       काष्ठा mlx5_flow_attr *attr,
			       u32 *action)
अणु
	काष्ठा flow_action_entry vlan_act = अणु
		.id = FLOW_ACTION_VLAN_POP,
	पूर्ण;
	पूर्णांक nest_level, err = 0;

	nest_level = attr->parse_attr->filter_dev->lower_level -
						priv->netdev->lower_level;
	जबतक (nest_level--) अणु
		err = parse_tc_vlan_action(priv, &vlan_act, attr->esw_attr, action);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल bool same_hw_reps(काष्ठा mlx5e_priv *priv,
			 काष्ठा net_device *peer_netdev)
अणु
	काष्ठा mlx5e_priv *peer_priv;

	peer_priv = netdev_priv(peer_netdev);

	वापस mlx5e_eचयन_rep(priv->netdev) &&
	       mlx5e_eचयन_rep(peer_netdev) &&
	       same_hw_devs(priv, peer_priv);
पूर्ण

अटल bool is_lag_dev(काष्ठा mlx5e_priv *priv,
		       काष्ठा net_device *peer_netdev)
अणु
	वापस ((mlx5_lag_is_sriov(priv->mdev) ||
		 mlx5_lag_is_multipath(priv->mdev)) &&
		 same_hw_reps(priv, peer_netdev));
पूर्ण

bool mlx5e_is_valid_eचयन_fwd_dev(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *out_dev)
अणु
	अगर (is_merged_eचयन_vfs(priv, out_dev))
		वापस true;

	अगर (is_lag_dev(priv, out_dev))
		वापस true;

	वापस mlx5e_eचयन_rep(out_dev) &&
	       same_port_devs(priv, netdev_priv(out_dev));
पूर्ण

अटल bool is_duplicated_output_device(काष्ठा net_device *dev,
					काष्ठा net_device *out_dev,
					पूर्णांक *अगरindexes, पूर्णांक अगर_count,
					काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < अगर_count; i++) अणु
		अगर (अगरindexes[i] == out_dev->अगरindex) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "can't duplicate output to same device");
			netdev_err(dev, "can't duplicate output to same device: %s\n",
				   out_dev->name);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक verअगरy_uplink_क्रमwarding(काष्ठा mlx5e_priv *priv,
				    काष्ठा mlx5e_tc_flow *flow,
				    काष्ठा net_device *out_dev,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_esw_flow_attr *attr = flow->attr->esw_attr;
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_rep_priv *rep_priv;

	/* Forwarding non encapsulated traffic between
	 * uplink ports is allowed only अगर
	 * termination_table_raw_traffic cap is set.
	 *
	 * Input vport was stored attr->in_rep.
	 * In LAG हाल, *priv* is the निजी data of
	 * uplink which may be not the input vport.
	 */
	rep_priv = mlx5e_rep_to_rep_priv(attr->in_rep);

	अगर (!(mlx5e_eचयन_uplink_rep(rep_priv->netdev) &&
	      mlx5e_eचयन_uplink_rep(out_dev)))
		वापस 0;

	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev,
					termination_table_raw_traffic)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "devices are both uplink, can't offload forwarding");
			pr_err("devices %s %s are both uplink, can't offload forwarding\n",
			       priv->netdev->name, out_dev->name);
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (out_dev != rep_priv->netdev) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "devices are not the same uplink, can't offload forwarding");
		pr_err("devices %s %s are both uplink but not the same, can't offload forwarding\n",
		       priv->netdev->name, out_dev->name);
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_tc_fdb_actions(काष्ठा mlx5e_priv *priv,
				काष्ठा flow_action *flow_action,
				काष्ठा mlx5e_tc_flow *flow,
				काष्ठा netlink_ext_ack *extack,
				काष्ठा net_device *filter_dev)
अणु
	काष्ठा pedit_headers_action hdrs[2] = अणुपूर्ण;
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	स्थिर काष्ठा ip_tunnel_info *info = शून्य;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	पूर्णांक अगरindexes[MLX5_MAX_FLOW_FWD_VPORTS];
	bool ft_flow = mlx5e_is_ft_flow(flow);
	स्थिर काष्ठा flow_action_entry *act;
	काष्ठा mlx5_esw_flow_attr *esw_attr;
	काष्ठा mlx5_sample_attr sample = अणुपूर्ण;
	bool encap = false, decap = false;
	u32 action = attr->action;
	पूर्णांक err, i, अगर_count = 0;
	bool mpls_push = false;

	अगर (!flow_action_has_entries(flow_action))
		वापस -EINVAL;

	अगर (!flow_action_hw_stats_check(flow_action, extack,
					FLOW_ACTION_HW_STATS_DELAYED_BIT))
		वापस -EOPNOTSUPP;

	esw_attr = attr->esw_attr;
	parse_attr = attr->parse_attr;

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_DROP:
			action |= MLX5_FLOW_CONTEXT_ACTION_DROP |
				  MLX5_FLOW_CONTEXT_ACTION_COUNT;
			अवरोध;
		हाल FLOW_ACTION_TRAP:
			अगर (!flow_offload_has_one_action(flow_action)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "action trap is supported as a sole action only");
				वापस -EOPNOTSUPP;
			पूर्ण
			action |= (MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
				   MLX5_FLOW_CONTEXT_ACTION_COUNT);
			attr->flags |= MLX5_ESW_ATTR_FLAG_SLOW_PATH;
			अवरोध;
		हाल FLOW_ACTION_MPLS_PUSH:
			अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev,
							reक्रमmat_l2_to_l3_tunnel) ||
			    act->mpls_push.proto != htons(ETH_P_MPLS_UC)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "mpls push is supported only for mpls_uc protocol");
				वापस -EOPNOTSUPP;
			पूर्ण
			mpls_push = true;
			अवरोध;
		हाल FLOW_ACTION_MPLS_POP:
			/* we only support mpls pop अगर it is the first action
			 * and the filter net device is bareudp. Subsequent
			 * actions can be pedit and the last can be mirred
			 * egress redirect.
			 */
			अगर (i) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "mpls pop supported only as first action");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (!netअगर_is_bareudp(filter_dev)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "mpls pop supported only on bareudp devices");
				वापस -EOPNOTSUPP;
			पूर्ण

			parse_attr->eth.h_proto = act->mpls_pop.proto;
			action |= MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
			flow_flag_set(flow, L3_TO_L2_DECAP);
			अवरोध;
		हाल FLOW_ACTION_MANGLE:
		हाल FLOW_ACTION_ADD:
			err = parse_tc_pedit_action(priv, act, MLX5_FLOW_NAMESPACE_FDB,
						    parse_attr, hdrs, flow, extack);
			अगर (err)
				वापस err;

			अगर (!flow_flag_test(flow, L3_TO_L2_DECAP)) अणु
				action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
				esw_attr->split_count = esw_attr->out_count;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_CSUM:
			अगर (csum_offload_supported(priv, action,
						   act->csum_flags, extack))
				अवरोध;

			वापस -EOPNOTSUPP;
		हाल FLOW_ACTION_REसूचीECT:
		हाल FLOW_ACTION_MIRRED: अणु
			काष्ठा mlx5e_priv *out_priv;
			काष्ठा net_device *out_dev;

			out_dev = act->dev;
			अगर (!out_dev) अणु
				/* out_dev is शून्य when filters with
				 * non-existing mirred device are replayed to
				 * the driver.
				 */
				वापस -EINVAL;
			पूर्ण

			अगर (mpls_push && !netअगर_is_bareudp(out_dev)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "mpls is supported only through a bareudp device");
				वापस -EOPNOTSUPP;
			पूर्ण

			अगर (ft_flow && out_dev == priv->netdev) अणु
				/* Ignore क्रमward to self rules generated
				 * by adding both mlx5 devs to the flow table
				 * block on a normal nft offload setup.
				 */
				वापस -EOPNOTSUPP;
			पूर्ण

			अगर (esw_attr->out_count >= MLX5_MAX_FLOW_FWD_VPORTS) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "can't support more output ports, can't offload forwarding");
				netdev_warn(priv->netdev,
					    "can't support more than %d output ports, can't offload forwarding\n",
					    esw_attr->out_count);
				वापस -EOPNOTSUPP;
			पूर्ण

			action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
				  MLX5_FLOW_CONTEXT_ACTION_COUNT;
			अगर (encap) अणु
				parse_attr->mirred_अगरindex[esw_attr->out_count] =
					out_dev->अगरindex;
				parse_attr->tun_info[esw_attr->out_count] =
					mlx5e_dup_tun_info(info);
				अगर (!parse_attr->tun_info[esw_attr->out_count])
					वापस -ENOMEM;
				encap = false;
				esw_attr->dests[esw_attr->out_count].flags |=
					MLX5_ESW_DEST_ENCAP;
				esw_attr->out_count++;
				/* attr->dests[].rep is resolved when we
				 * handle encap
				 */
			पूर्ण अन्यथा अगर (netdev_port_same_parent_id(priv->netdev, out_dev)) अणु
				काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
				काष्ठा net_device *uplink_dev = mlx5_eचयन_uplink_get_proto_dev(esw, REP_ETH);

				अगर (is_duplicated_output_device(priv->netdev,
								out_dev,
								अगरindexes,
								अगर_count,
								extack))
					वापस -EOPNOTSUPP;

				अगरindexes[अगर_count] = out_dev->अगरindex;
				अगर_count++;

				out_dev = get_fdb_out_dev(uplink_dev, out_dev);
				अगर (!out_dev)
					वापस -ENODEV;

				अगर (is_vlan_dev(out_dev)) अणु
					err = add_vlan_push_action(priv, attr,
								   &out_dev,
								   &action);
					अगर (err)
						वापस err;
				पूर्ण

				अगर (is_vlan_dev(parse_attr->filter_dev)) अणु
					err = add_vlan_pop_action(priv, attr,
								  &action);
					अगर (err)
						वापस err;
				पूर्ण

				err = verअगरy_uplink_क्रमwarding(priv, flow, out_dev, extack);
				अगर (err)
					वापस err;

				अगर (!mlx5e_is_valid_eचयन_fwd_dev(priv, out_dev)) अणु
					NL_SET_ERR_MSG_MOD(extack,
							   "devices are not on same switch HW, can't offload forwarding");
					वापस -EOPNOTSUPP;
				पूर्ण

				अगर (same_vf_reps(priv, out_dev)) अणु
					NL_SET_ERR_MSG_MOD(extack,
							   "can't forward from a VF to itself");
					वापस -EOPNOTSUPP;
				पूर्ण

				out_priv = netdev_priv(out_dev);
				rpriv = out_priv->ppriv;
				esw_attr->dests[esw_attr->out_count].rep = rpriv->rep;
				esw_attr->dests[esw_attr->out_count].mdev = out_priv->mdev;
				esw_attr->out_count++;
			पूर्ण अन्यथा अगर (parse_attr->filter_dev != priv->netdev) अणु
				/* All mlx5 devices are called to configure
				 * high level device filters. Thereक्रमe, the
				 * *attempt* to  install a filter on invalid
				 * eचयन should not trigger an explicit error
				 */
				वापस -EINVAL;
			पूर्ण अन्यथा अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "devices are not on same switch HW, can't offload forwarding");
				netdev_warn(priv->netdev,
					    "devices %s %s not on same switch HW, can't offload forwarding\n",
					    priv->netdev->name,
					    out_dev->name);
				वापस -EINVAL;
			पूर्ण
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_TUNNEL_ENCAP:
			info = act->tunnel;
			अगर (info)
				encap = true;
			अन्यथा
				वापस -EOPNOTSUPP;

			अवरोध;
		हाल FLOW_ACTION_VLAN_PUSH:
		हाल FLOW_ACTION_VLAN_POP:
			अगर (act->id == FLOW_ACTION_VLAN_PUSH &&
			    (action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP)) अणु
				/* Replace vlan pop+push with vlan modअगरy */
				action &= ~MLX5_FLOW_CONTEXT_ACTION_VLAN_POP;
				err = add_vlan_reग_लिखो_action(priv,
							      MLX5_FLOW_NAMESPACE_FDB,
							      act, parse_attr, hdrs,
							      &action, extack);
			पूर्ण अन्यथा अणु
				err = parse_tc_vlan_action(priv, act, esw_attr, &action);
			पूर्ण
			अगर (err)
				वापस err;

			esw_attr->split_count = esw_attr->out_count;
			अवरोध;
		हाल FLOW_ACTION_VLAN_MANGLE:
			err = add_vlan_reग_लिखो_action(priv,
						      MLX5_FLOW_NAMESPACE_FDB,
						      act, parse_attr, hdrs,
						      &action, extack);
			अगर (err)
				वापस err;

			esw_attr->split_count = esw_attr->out_count;
			अवरोध;
		हाल FLOW_ACTION_TUNNEL_DECAP:
			decap = true;
			अवरोध;
		हाल FLOW_ACTION_GOTO:
			err = validate_जाओ_chain(priv, flow, act, action,
						  extack);
			अगर (err)
				वापस err;

			action |= MLX5_FLOW_CONTEXT_ACTION_COUNT;
			attr->dest_chain = act->chain_index;
			अवरोध;
		हाल FLOW_ACTION_CT:
			अगर (flow_flag_test(flow, SAMPLE)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Sample action with connection tracking is not supported");
				वापस -EOPNOTSUPP;
			पूर्ण
			err = mlx5_tc_ct_parse_action(get_ct_priv(priv), attr, act, extack);
			अगर (err)
				वापस err;

			flow_flag_set(flow, CT);
			esw_attr->split_count = esw_attr->out_count;
			अवरोध;
		हाल FLOW_ACTION_SAMPLE:
			अगर (flow_flag_test(flow, CT)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Sample action with connection tracking is not supported");
				वापस -EOPNOTSUPP;
			पूर्ण
			sample.rate = act->sample.rate;
			sample.group_num = act->sample.psample_group->group_num;
			अगर (act->sample.truncate)
				sample.trunc_size = act->sample.trunc_size;
			flow_flag_set(flow, SAMPLE);
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "The offload action is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	/* always set IP version क्रम indirect table handling */
	attr->ip_version = mlx5e_tc_get_ip_version(&parse_attr->spec, true);

	अगर (MLX5_CAP_GEN(esw->dev, prio_tag_required) &&
	    action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP) अणु
		/* For prio tag mode, replace vlan pop with reग_लिखो vlan prio
		 * tag reग_लिखो.
		 */
		action &= ~MLX5_FLOW_CONTEXT_ACTION_VLAN_POP;
		err = add_vlan_prio_tag_reग_लिखो_action(priv, parse_attr, hdrs,
						       &action, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (hdrs[TCA_PEDIT_KEY_EX_CMD_SET].pedits ||
	    hdrs[TCA_PEDIT_KEY_EX_CMD_ADD].pedits) अणु
		err = alloc_tc_pedit_action(priv, MLX5_FLOW_NAMESPACE_FDB,
					    parse_attr, hdrs, &action, extack);
		अगर (err)
			वापस err;
		/* in हाल all pedit actions are skipped, हटाओ the MOD_HDR
		 * flag. we might have set split_count either by pedit or
		 * pop/push. अगर there is no pop/push either, reset it too.
		 */
		अगर (parse_attr->mod_hdr_acts.num_actions == 0) अणु
			action &= ~MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
			dealloc_mod_hdr_actions(&parse_attr->mod_hdr_acts);
			अगर (!((action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP) ||
			      (action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH)))
				esw_attr->split_count = 0;
		पूर्ण
	पूर्ण

	attr->action = action;
	अगर (!actions_match_supported(priv, flow_action, parse_attr, flow, extack))
		वापस -EOPNOTSUPP;

	अगर (attr->dest_chain) अणु
		अगर (decap) अणु
			/* It can be supported अगर we'll create a mapping क्रम
			 * the tunnel device only (without tunnel), and set
			 * this tunnel id with this decap flow.
			 *
			 * On restore (miss), we'll just set this saved tunnel
			 * device.
			 */

			NL_SET_ERR_MSG(extack,
				       "Decap with goto isn't supported");
			netdev_warn(priv->netdev,
				    "Decap with goto isn't supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		attr->action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	पूर्ण

	अगर (!(attr->action &
	      (MLX5_FLOW_CONTEXT_ACTION_FWD_DEST | MLX5_FLOW_CONTEXT_ACTION_DROP))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Rule must have at least one forward/drop action");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (esw_attr->split_count > 0 && !mlx5_esw_has_fwd_fdb(priv->mdev)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "current firmware doesn't support split rule for port mirroring");
		netdev_warn_once(priv->netdev, "current firmware doesn't support split rule for port mirroring\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Allocate sample attribute only when there is a sample action and
	 * no errors after parsing.
	 */
	अगर (flow_flag_test(flow, SAMPLE)) अणु
		esw_attr->sample = kzalloc(माप(*esw_attr->sample), GFP_KERNEL);
		अगर (!esw_attr->sample)
			वापस -ENOMEM;
		*esw_attr->sample = sample;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम get_flags(पूर्णांक flags, अचिन्हित दीर्घ *flow_flags)
अणु
	अचिन्हित दीर्घ __flow_flags = 0;

	अगर (flags & MLX5_TC_FLAG(INGRESS))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_INGRESS);
	अगर (flags & MLX5_TC_FLAG(EGRESS))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_EGRESS);

	अगर (flags & MLX5_TC_FLAG(ESW_OFFLOAD))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_ESWITCH);
	अगर (flags & MLX5_TC_FLAG(NIC_OFFLOAD))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_NIC);
	अगर (flags & MLX5_TC_FLAG(FT_OFFLOAD))
		__flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_FT);

	*flow_flags = __flow_flags;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params tc_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mlx5e_tc_flow, node),
	.key_offset = दुरत्व(काष्ठा mlx5e_tc_flow, cookie),
	.key_len = माप(((काष्ठा mlx5e_tc_flow *)0)->cookie),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल काष्ठा rhashtable *get_tc_ht(काष्ठा mlx5e_priv *priv,
				    अचिन्हित दीर्घ flags)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;

	अगर (flags & MLX5_TC_FLAG(ESW_OFFLOAD)) अणु
		uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
		वापस &uplink_rpriv->uplink_priv.tc_ht;
	पूर्ण अन्यथा /* NIC offload */
		वापस &priv->fs.tc.ht;
पूर्ण

अटल bool is_peer_flow_needed(काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = flow->attr->esw_attr;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	bool is_rep_ingress = esw_attr->in_rep->vport != MLX5_VPORT_UPLINK &&
		flow_flag_test(flow, INGRESS);
	bool act_is_encap = !!(attr->action &
			       MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT);
	bool esw_paired = mlx5_devcom_is_paired(esw_attr->in_mdev->priv.devcom,
						MLX5_DEVCOM_ESW_OFFLOADS);

	अगर (!esw_paired)
		वापस false;

	अगर ((mlx5_lag_is_sriov(esw_attr->in_mdev) ||
	     mlx5_lag_is_multipath(esw_attr->in_mdev)) &&
	    (is_rep_ingress || act_is_encap))
		वापस true;

	वापस false;
पूर्ण

काष्ठा mlx5_flow_attr *
mlx5_alloc_flow_attr(क्रमागत mlx5_flow_namespace_type type)
अणु
	u32 ex_attr_size = (type == MLX5_FLOW_NAMESPACE_FDB)  ?
				माप(काष्ठा mlx5_esw_flow_attr) :
				माप(काष्ठा mlx5_nic_flow_attr);
	काष्ठा mlx5_flow_attr *attr;

	वापस kzalloc(माप(*attr) + ex_attr_size, GFP_KERNEL);
पूर्ण

अटल पूर्णांक
mlx5e_alloc_flow(काष्ठा mlx5e_priv *priv, पूर्णांक attr_size,
		 काष्ठा flow_cls_offload *f, अचिन्हित दीर्घ flow_flags,
		 काष्ठा mlx5e_tc_flow_parse_attr **__parse_attr,
		 काष्ठा mlx5e_tc_flow **__flow)
अणु
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5_flow_attr *attr;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक err = -ENOMEM;
	पूर्णांक out_index;

	flow = kzalloc(माप(*flow), GFP_KERNEL);
	parse_attr = kvzalloc(माप(*parse_attr), GFP_KERNEL);
	अगर (!parse_attr || !flow)
		जाओ err_मुक्त;

	flow->flags = flow_flags;
	flow->cookie = f->cookie;
	flow->priv = priv;

	attr = mlx5_alloc_flow_attr(get_flow_name_space(flow));
	अगर (!attr)
		जाओ err_मुक्त;

	flow->attr = attr;

	क्रम (out_index = 0; out_index < MLX5_MAX_FLOW_FWD_VPORTS; out_index++)
		INIT_LIST_HEAD(&flow->encaps[out_index].list);
	INIT_LIST_HEAD(&flow->hairpin);
	INIT_LIST_HEAD(&flow->l3_to_l2_reक्रमmat);
	refcount_set(&flow->refcnt, 1);
	init_completion(&flow->init_करोne);

	*__flow = flow;
	*__parse_attr = parse_attr;

	वापस 0;

err_मुक्त:
	kमुक्त(flow);
	kvमुक्त(parse_attr);
	वापस err;
पूर्ण

अटल व्योम
mlx5e_flow_attr_init(काष्ठा mlx5_flow_attr *attr,
		     काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
		     काष्ठा flow_cls_offload *f)
अणु
	attr->parse_attr = parse_attr;
	attr->chain = f->common.chain_index;
	attr->prio = f->common.prio;
पूर्ण

अटल व्योम
mlx5e_flow_esw_attr_init(काष्ठा mlx5_flow_attr *attr,
			 काष्ठा mlx5e_priv *priv,
			 काष्ठा mlx5e_tc_flow_parse_attr *parse_attr,
			 काष्ठा flow_cls_offload *f,
			 काष्ठा mlx5_eचयन_rep *in_rep,
			 काष्ठा mlx5_core_dev *in_mdev)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;

	mlx5e_flow_attr_init(attr, parse_attr, f);

	esw_attr->in_rep = in_rep;
	esw_attr->in_mdev = in_mdev;

	अगर (MLX5_CAP_ESW(esw->dev, counter_eचयन_affinity) ==
	    MLX5_COUNTER_SOURCE_ESWITCH)
		esw_attr->counter_dev = in_mdev;
	अन्यथा
		esw_attr->counter_dev = priv->mdev;
पूर्ण

अटल काष्ठा mlx5e_tc_flow *
__mlx5e_add_fdb_flow(काष्ठा mlx5e_priv *priv,
		     काष्ठा flow_cls_offload *f,
		     अचिन्हित दीर्घ flow_flags,
		     काष्ठा net_device *filter_dev,
		     काष्ठा mlx5_eचयन_rep *in_rep,
		     काष्ठा mlx5_core_dev *in_mdev)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक attr_size, err;

	flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_ESWITCH);
	attr_size  = माप(काष्ठा mlx5_esw_flow_attr);
	err = mlx5e_alloc_flow(priv, attr_size, f, flow_flags,
			       &parse_attr, &flow);
	अगर (err)
		जाओ out;

	parse_attr->filter_dev = filter_dev;
	mlx5e_flow_esw_attr_init(flow->attr,
				 priv, parse_attr,
				 f, in_rep, in_mdev);

	err = parse_cls_flower(flow->priv, flow, &parse_attr->spec,
			       f, filter_dev);
	अगर (err)
		जाओ err_मुक्त;

	/* actions validation depends on parsing the ct matches first */
	err = mlx5_tc_ct_match_add(get_ct_priv(priv), &parse_attr->spec, f,
				   &flow->attr->ct_attr, extack);
	अगर (err)
		जाओ err_मुक्त;

	err = parse_tc_fdb_actions(priv, &rule->action, flow, extack, filter_dev);
	अगर (err)
		जाओ err_मुक्त;

	err = mlx5e_tc_add_fdb_flow(priv, flow, extack);
	complete_all(&flow->init_करोne);
	अगर (err) अणु
		अगर (!(err == -ENETUNREACH && mlx5_lag_is_multipath(in_mdev)))
			जाओ err_मुक्त;

		add_unपढ़ोy_flow(flow);
	पूर्ण

	वापस flow;

err_मुक्त:
	mlx5e_flow_put(priv, flow);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक mlx5e_tc_add_fdb_peer_flow(काष्ठा flow_cls_offload *f,
				      काष्ठा mlx5e_tc_flow *flow,
				      अचिन्हित दीर्घ flow_flags)
अणु
	काष्ठा mlx5e_priv *priv = flow->priv, *peer_priv;
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन, *peer_esw;
	काष्ठा mlx5_esw_flow_attr *attr = flow->attr->esw_attr;
	काष्ठा mlx5_devcom *devcom = priv->mdev->priv.devcom;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5e_rep_priv *peer_urpriv;
	काष्ठा mlx5e_tc_flow *peer_flow;
	काष्ठा mlx5_core_dev *in_mdev;
	पूर्णांक err = 0;

	peer_esw = mlx5_devcom_get_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
	अगर (!peer_esw)
		वापस -ENODEV;

	peer_urpriv = mlx5_eचयन_get_uplink_priv(peer_esw, REP_ETH);
	peer_priv = netdev_priv(peer_urpriv->netdev);

	/* in_mdev is asचिन्हित of which the packet originated from.
	 * So packets redirected to uplink use the same mdev of the
	 * original flow and packets redirected from uplink use the
	 * peer mdev.
	 */
	अगर (attr->in_rep->vport == MLX5_VPORT_UPLINK)
		in_mdev = peer_priv->mdev;
	अन्यथा
		in_mdev = priv->mdev;

	parse_attr = flow->attr->parse_attr;
	peer_flow = __mlx5e_add_fdb_flow(peer_priv, f, flow_flags,
					 parse_attr->filter_dev,
					 attr->in_rep, in_mdev);
	अगर (IS_ERR(peer_flow)) अणु
		err = PTR_ERR(peer_flow);
		जाओ out;
	पूर्ण

	flow->peer_flow = peer_flow;
	flow_flag_set(flow, DUP);
	mutex_lock(&esw->offloads.peer_mutex);
	list_add_tail(&flow->peer, &esw->offloads.peer_flows);
	mutex_unlock(&esw->offloads.peer_mutex);

out:
	mlx5_devcom_release_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5e_add_fdb_flow(काष्ठा mlx5e_priv *priv,
		   काष्ठा flow_cls_offload *f,
		   अचिन्हित दीर्घ flow_flags,
		   काष्ठा net_device *filter_dev,
		   काष्ठा mlx5e_tc_flow **__flow)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *in_rep = rpriv->rep;
	काष्ठा mlx5_core_dev *in_mdev = priv->mdev;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक err;

	flow = __mlx5e_add_fdb_flow(priv, f, flow_flags, filter_dev, in_rep,
				    in_mdev);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	अगर (is_peer_flow_needed(flow)) अणु
		err = mlx5e_tc_add_fdb_peer_flow(f, flow, flow_flags);
		अगर (err) अणु
			mlx5e_tc_del_fdb_flow(priv, flow);
			जाओ out;
		पूर्ण
	पूर्ण

	*__flow = flow;

	वापस 0;

out:
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5e_add_nic_flow(काष्ठा mlx5e_priv *priv,
		   काष्ठा flow_cls_offload *f,
		   अचिन्हित दीर्घ flow_flags,
		   काष्ठा net_device *filter_dev,
		   काष्ठा mlx5e_tc_flow **__flow)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक attr_size, err;

	अगर (!MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, ignore_flow_level)) अणु
		अगर (!tc_cls_can_offload_and_chain0(priv->netdev, &f->common))
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (!tc_can_offload_extack(priv->netdev, f->common.extack)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	flow_flags |= BIT(MLX5E_TC_FLOW_FLAG_NIC);
	attr_size  = माप(काष्ठा mlx5_nic_flow_attr);
	err = mlx5e_alloc_flow(priv, attr_size, f, flow_flags,
			       &parse_attr, &flow);
	अगर (err)
		जाओ out;

	parse_attr->filter_dev = filter_dev;
	mlx5e_flow_attr_init(flow->attr, parse_attr, f);

	err = parse_cls_flower(flow->priv, flow, &parse_attr->spec,
			       f, filter_dev);
	अगर (err)
		जाओ err_मुक्त;

	err = mlx5_tc_ct_match_add(get_ct_priv(priv), &parse_attr->spec, f,
				   &flow->attr->ct_attr, extack);
	अगर (err)
		जाओ err_मुक्त;

	err = parse_tc_nic_actions(priv, &rule->action, parse_attr, flow, extack);
	अगर (err)
		जाओ err_मुक्त;

	err = mlx5e_tc_add_nic_flow(priv, parse_attr, flow, extack);
	अगर (err)
		जाओ err_मुक्त;

	flow_flag_set(flow, OFFLOADED);
	*__flow = flow;

	वापस 0;

err_मुक्त:
	flow_flag_set(flow, FAILED);
	dealloc_mod_hdr_actions(&parse_attr->mod_hdr_acts);
	mlx5e_flow_put(priv, flow);
out:
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5e_tc_add_flow(काष्ठा mlx5e_priv *priv,
		  काष्ठा flow_cls_offload *f,
		  अचिन्हित दीर्घ flags,
		  काष्ठा net_device *filter_dev,
		  काष्ठा mlx5e_tc_flow **flow)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	अचिन्हित दीर्घ flow_flags;
	पूर्णांक err;

	get_flags(flags, &flow_flags);

	अगर (!tc_can_offload_extack(priv->netdev, f->common.extack))
		वापस -EOPNOTSUPP;

	अगर (esw && esw->mode == MLX5_ESWITCH_OFFLOADS)
		err = mlx5e_add_fdb_flow(priv, f, flow_flags,
					 filter_dev, flow);
	अन्यथा
		err = mlx5e_add_nic_flow(priv, f, flow_flags,
					 filter_dev, flow);

	वापस err;
पूर्ण

अटल bool is_flow_rule_duplicate_allowed(काष्ठा net_device *dev,
					   काष्ठा mlx5e_rep_priv *rpriv)
अणु
	/* Offloaded flow rule is allowed to duplicate on non-uplink representor
	 * sharing tc block with other slaves of a lag device. Rpriv can be शून्य अगर this
	 * function is called from NIC mode.
	 */
	वापस netअगर_is_lag_port(dev) && rpriv && rpriv->rep->vport != MLX5_VPORT_UPLINK;
पूर्ण

पूर्णांक mlx5e_configure_flower(काष्ठा net_device *dev, काष्ठा mlx5e_priv *priv,
			   काष्ठा flow_cls_offload *f, अचिन्हित दीर्घ flags)
अणु
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा rhashtable *tc_ht = get_tc_ht(priv, flags);
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक err = 0;

	अगर (!mlx5_esw_hold(priv->mdev))
		वापस -EAGAIN;

	mlx5_esw_get(priv->mdev);

	rcu_पढ़ो_lock();
	flow = rhashtable_lookup(tc_ht, &f->cookie, tc_ht_params);
	अगर (flow) अणु
		/* Same flow rule offloaded to non-uplink representor sharing tc block,
		 * just वापस 0.
		 */
		अगर (is_flow_rule_duplicate_allowed(dev, rpriv) && flow->orig_dev != dev)
			जाओ rcu_unlock;

		NL_SET_ERR_MSG_MOD(extack,
				   "flow cookie already exists, ignoring");
		netdev_warn_once(priv->netdev,
				 "flow cookie %lx already exists, ignoring\n",
				 f->cookie);
		err = -EEXIST;
		जाओ rcu_unlock;
	पूर्ण
rcu_unlock:
	rcu_पढ़ो_unlock();
	अगर (flow)
		जाओ out;

	trace_mlx5e_configure_flower(f);
	err = mlx5e_tc_add_flow(priv, f, flags, dev, &flow);
	अगर (err)
		जाओ out;

	/* Flow rule offloaded to non-uplink representor sharing tc block,
	 * set the flow's owner dev.
	 */
	अगर (is_flow_rule_duplicate_allowed(dev, rpriv))
		flow->orig_dev = dev;

	err = rhashtable_lookup_insert_fast(tc_ht, &flow->node, tc_ht_params);
	अगर (err)
		जाओ err_मुक्त;

	mlx5_esw_release(priv->mdev);
	वापस 0;

err_मुक्त:
	mlx5e_flow_put(priv, flow);
out:
	mlx5_esw_put(priv->mdev);
	mlx5_esw_release(priv->mdev);
	वापस err;
पूर्ण

अटल bool same_flow_direction(काष्ठा mlx5e_tc_flow *flow, पूर्णांक flags)
अणु
	bool dir_ingress = !!(flags & MLX5_TC_FLAG(INGRESS));
	bool dir_egress = !!(flags & MLX5_TC_FLAG(EGRESS));

	वापस flow_flag_test(flow, INGRESS) == dir_ingress &&
		flow_flag_test(flow, EGRESS) == dir_egress;
पूर्ण

पूर्णांक mlx5e_delete_flower(काष्ठा net_device *dev, काष्ठा mlx5e_priv *priv,
			काष्ठा flow_cls_offload *f, अचिन्हित दीर्घ flags)
अणु
	काष्ठा rhashtable *tc_ht = get_tc_ht(priv, flags);
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	flow = rhashtable_lookup(tc_ht, &f->cookie, tc_ht_params);
	अगर (!flow || !same_flow_direction(flow, flags)) अणु
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	/* Only delete the flow अगर it करोesn't have MLX5E_TC_FLOW_DELETED flag
	 * set.
	 */
	अगर (flow_flag_test_and_set(flow, DELETED)) अणु
		err = -EINVAL;
		जाओ errout;
	पूर्ण
	rhashtable_हटाओ_fast(tc_ht, &flow->node, tc_ht_params);
	rcu_पढ़ो_unlock();

	trace_mlx5e_delete_flower(f);
	mlx5e_flow_put(priv, flow);

	mlx5_esw_put(priv->mdev);
	वापस 0;

errout:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

पूर्णांक mlx5e_stats_flower(काष्ठा net_device *dev, काष्ठा mlx5e_priv *priv,
		       काष्ठा flow_cls_offload *f, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mlx5_devcom *devcom = priv->mdev->priv.devcom;
	काष्ठा rhashtable *tc_ht = get_tc_ht(priv, flags);
	काष्ठा mlx5_eचयन *peer_esw;
	काष्ठा mlx5e_tc_flow *flow;
	काष्ठा mlx5_fc *counter;
	u64 lastuse = 0;
	u64 packets = 0;
	u64 bytes = 0;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	flow = mlx5e_flow_get(rhashtable_lookup(tc_ht, &f->cookie,
						tc_ht_params));
	rcu_पढ़ो_unlock();
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	अगर (!same_flow_direction(flow, flags)) अणु
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	अगर (mlx5e_is_offloaded_flow(flow) || flow_flag_test(flow, CT)) अणु
		counter = mlx5e_tc_get_counter(flow);
		अगर (!counter)
			जाओ errout;

		mlx5_fc_query_cached(counter, &bytes, &packets, &lastuse);
	पूर्ण

	/* Under multipath it's possible क्रम one rule to be currently
	 * un-offloaded जबतक the other rule is offloaded.
	 */
	peer_esw = mlx5_devcom_get_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
	अगर (!peer_esw)
		जाओ out;

	अगर (flow_flag_test(flow, DUP) &&
	    flow_flag_test(flow->peer_flow, OFFLOADED)) अणु
		u64 bytes2;
		u64 packets2;
		u64 lastuse2;

		counter = mlx5e_tc_get_counter(flow->peer_flow);
		अगर (!counter)
			जाओ no_peer_counter;
		mlx5_fc_query_cached(counter, &bytes2, &packets2, &lastuse2);

		bytes += bytes2;
		packets += packets2;
		lastuse = max_t(u64, lastuse, lastuse2);
	पूर्ण

no_peer_counter:
	mlx5_devcom_release_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
out:
	flow_stats_update(&f->stats, bytes, packets, 0, lastuse,
			  FLOW_ACTION_HW_STATS_DELAYED);
	trace_mlx5e_stats_flower(f);
errout:
	mlx5e_flow_put(priv, flow);
	वापस err;
पूर्ण

अटल पूर्णांक apply_police_params(काष्ठा mlx5e_priv *priv, u64 rate,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन *esw;
	u32 rate_mbps = 0;
	u16 vport_num;
	पूर्णांक err;

	vport_num = rpriv->rep->vport;
	अगर (vport_num >= MLX5_VPORT_ECPF) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Ingress rate limit is supported only for Eswitch ports connected to VFs");
		वापस -EOPNOTSUPP;
	पूर्ण

	esw = priv->mdev->priv.eचयन;
	/* rate is given in bytes/sec.
	 * First convert to bits/sec and then round to the nearest mbit/secs.
	 * mbit means million bits.
	 * Moreover, अगर rate is non zero we choose to configure to a minimum of
	 * 1 mbit/sec.
	 */
	अगर (rate) अणु
		rate = (rate * BITS_PER_BYTE) + 500000;
		करो_भाग(rate, 1000000);
		rate_mbps = max_t(u32, rate, 1);
	पूर्ण

	err = mlx5_esw_modअगरy_vport_rate(esw, vport_num, rate_mbps);
	अगर (err)
		NL_SET_ERR_MSG_MOD(extack, "failed applying action to hardware");

	वापस err;
पूर्ण

अटल पूर्णांक scan_tc_matchall_fdb_actions(काष्ठा mlx5e_priv *priv,
					काष्ठा flow_action *flow_action,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	स्थिर काष्ठा flow_action_entry *act;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!flow_action_has_entries(flow_action)) अणु
		NL_SET_ERR_MSG_MOD(extack, "matchall called with no action");
		वापस -EINVAL;
	पूर्ण

	अगर (!flow_offload_has_one_action(flow_action)) अणु
		NL_SET_ERR_MSG_MOD(extack, "matchall policing support only a single action");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!flow_action_basic_hw_stats_check(flow_action, extack))
		वापस -EOPNOTSUPP;

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_POLICE:
			अगर (act->police.rate_pkt_ps) अणु
				NL_SET_ERR_MSG_MOD(extack, "QoS offload not support packets per second");
				वापस -EOPNOTSUPP;
			पूर्ण
			err = apply_police_params(priv, act->police.rate_bytes_ps, extack);
			अगर (err)
				वापस err;

			rpriv->prev_vf_vport_stats = priv->stats.vf_vport;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "mlx5 supports only police action for matchall");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5e_tc_configure_matchall(काष्ठा mlx5e_priv *priv,
				काष्ठा tc_cls_matchall_offload *ma)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा netlink_ext_ack *extack = ma->common.extack;

	अगर (!mlx5_esw_qos_enabled(esw)) अणु
		NL_SET_ERR_MSG_MOD(extack, "QoS is not supported on this device");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ma->common.prio != 1) अणु
		NL_SET_ERR_MSG_MOD(extack, "only priority 1 is supported");
		वापस -EINVAL;
	पूर्ण

	वापस scan_tc_matchall_fdb_actions(priv, &ma->rule->action, extack);
पूर्ण

पूर्णांक mlx5e_tc_delete_matchall(काष्ठा mlx5e_priv *priv,
			     काष्ठा tc_cls_matchall_offload *ma)
अणु
	काष्ठा netlink_ext_ack *extack = ma->common.extack;

	वापस apply_police_params(priv, 0, extack);
पूर्ण

व्योम mlx5e_tc_stats_matchall(काष्ठा mlx5e_priv *priv,
			     काष्ठा tc_cls_matchall_offload *ma)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा rtnl_link_stats64 cur_stats;
	u64 dbytes;
	u64 dpkts;

	cur_stats = priv->stats.vf_vport;
	dpkts = cur_stats.rx_packets - rpriv->prev_vf_vport_stats.rx_packets;
	dbytes = cur_stats.rx_bytes - rpriv->prev_vf_vport_stats.rx_bytes;
	rpriv->prev_vf_vport_stats = cur_stats;
	flow_stats_update(&ma->stats, dbytes, dpkts, 0, jअगरfies,
			  FLOW_ACTION_HW_STATS_DELAYED);
पूर्ण

अटल व्योम mlx5e_tc_hairpin_update_dead_peer(काष्ठा mlx5e_priv *priv,
					      काष्ठा mlx5e_priv *peer_priv)
अणु
	काष्ठा mlx5_core_dev *peer_mdev = peer_priv->mdev;
	काष्ठा mlx5e_hairpin_entry *hpe, *पंचांगp;
	LIST_HEAD(init_रुको_list);
	u16 peer_vhca_id;
	पूर्णांक bkt;

	अगर (!same_hw_devs(priv, peer_priv))
		वापस;

	peer_vhca_id = MLX5_CAP_GEN(peer_mdev, vhca_id);

	mutex_lock(&priv->fs.tc.hairpin_tbl_lock);
	hash_क्रम_each(priv->fs.tc.hairpin_tbl, bkt, hpe, hairpin_hlist)
		अगर (refcount_inc_not_zero(&hpe->refcnt))
			list_add(&hpe->dead_peer_रुको_list, &init_रुको_list);
	mutex_unlock(&priv->fs.tc.hairpin_tbl_lock);

	list_क्रम_each_entry_safe(hpe, पंचांगp, &init_रुको_list, dead_peer_रुको_list) अणु
		रुको_क्रम_completion(&hpe->res_पढ़ोy);
		अगर (!IS_ERR_OR_शून्य(hpe->hp) && hpe->peer_vhca_id == peer_vhca_id)
			mlx5_core_hairpin_clear_dead_peer(hpe->hp->pair);

		mlx5e_hairpin_put(priv, hpe);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_tc_netdev_event(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा mlx5e_flow_steering *fs;
	काष्ठा mlx5e_priv *peer_priv;
	काष्ठा mlx5e_tc_table *tc;
	काष्ठा mlx5e_priv *priv;

	अगर (ndev->netdev_ops != &mlx5e_netdev_ops ||
	    event != NETDEV_UNREGISTER ||
	    ndev->reg_state == NETREG_REGISTERED)
		वापस NOTIFY_DONE;

	tc = container_of(this, काष्ठा mlx5e_tc_table, netdevice_nb);
	fs = container_of(tc, काष्ठा mlx5e_flow_steering, tc);
	priv = container_of(fs, काष्ठा mlx5e_priv, fs);
	peer_priv = netdev_priv(ndev);
	अगर (priv == peer_priv ||
	    !(priv->netdev->features & NETIF_F_HW_TC))
		वापस NOTIFY_DONE;

	mlx5e_tc_hairpin_update_dead_peer(priv, peer_priv);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक mlx5e_tc_nic_get_ft_size(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक tc_grp_size, tc_tbl_size;
	u32 max_flow_counter;

	max_flow_counter = (MLX5_CAP_GEN(dev, max_flow_counter_31_16) << 16) |
			    MLX5_CAP_GEN(dev, max_flow_counter_15_0);

	tc_grp_size = min_t(पूर्णांक, max_flow_counter, MLX5E_TC_TABLE_MAX_GROUP_SIZE);

	tc_tbl_size = min_t(पूर्णांक, tc_grp_size * MLX5E_TC_TABLE_NUM_GROUPS,
			    BIT(MLX5_CAP_FLOWTABLE_NIC_RX(dev, log_max_ft_size)));

	वापस tc_tbl_size;
पूर्ण

पूर्णांक mlx5e_tc_nic_init(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_tc_table *tc = &priv->fs.tc;
	काष्ठा mlx5_core_dev *dev = priv->mdev;
	काष्ठा mapping_ctx *chains_mapping;
	काष्ठा mlx5_chains_attr attr = अणुपूर्ण;
	पूर्णांक err;

	mlx5e_mod_hdr_tbl_init(&tc->mod_hdr);
	mutex_init(&tc->t_lock);
	mutex_init(&tc->hairpin_tbl_lock);
	hash_init(tc->hairpin_tbl);

	err = rhashtable_init(&tc->ht, &tc_ht_params);
	अगर (err)
		वापस err;

	lockdep_set_class(&tc->ht.mutex, &tc_ht_lock_key);

	chains_mapping = mapping_create(माप(काष्ठा mlx5_mapped_obj),
					MLX5E_TC_TABLE_CHAIN_TAG_MASK, true);
	अगर (IS_ERR(chains_mapping)) अणु
		err = PTR_ERR(chains_mapping);
		जाओ err_mapping;
	पूर्ण
	tc->mapping = chains_mapping;

	अगर (MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, ignore_flow_level))
		attr.flags = MLX5_CHAINS_AND_PRIOS_SUPPORTED |
			MLX5_CHAINS_IGNORE_FLOW_LEVEL_SUPPORTED;
	attr.ns = MLX5_FLOW_NAMESPACE_KERNEL;
	attr.max_ft_sz = mlx5e_tc_nic_get_ft_size(dev);
	attr.max_grp_num = MLX5E_TC_TABLE_NUM_GROUPS;
	attr.शेष_ft = mlx5e_vlan_get_flowtable(priv->fs.vlan);
	attr.mapping = chains_mapping;

	tc->chains = mlx5_chains_create(dev, &attr);
	अगर (IS_ERR(tc->chains)) अणु
		err = PTR_ERR(tc->chains);
		जाओ err_chains;
	पूर्ण

	tc->ct = mlx5_tc_ct_init(priv, tc->chains, &priv->fs.tc.mod_hdr,
				 MLX5_FLOW_NAMESPACE_KERNEL);

	tc->netdevice_nb.notअगरier_call = mlx5e_tc_netdev_event;
	err = रेजिस्टर_netdevice_notअगरier_dev_net(priv->netdev,
						  &tc->netdevice_nb,
						  &tc->netdevice_nn);
	अगर (err) अणु
		tc->netdevice_nb.notअगरier_call = शून्य;
		mlx5_core_warn(priv->mdev, "Failed to register netdev notifier\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
	mlx5_tc_ct_clean(tc->ct);
	mlx5_chains_destroy(tc->chains);
err_chains:
	mapping_destroy(chains_mapping);
err_mapping:
	rhashtable_destroy(&tc->ht);
	वापस err;
पूर्ण

अटल व्योम _mlx5e_tc_del_flow(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा mlx5e_tc_flow *flow = ptr;
	काष्ठा mlx5e_priv *priv = flow->priv;

	mlx5e_tc_del_flow(priv, flow);
	kमुक्त(flow);
पूर्ण

व्योम mlx5e_tc_nic_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_tc_table *tc = &priv->fs.tc;

	अगर (tc->netdevice_nb.notअगरier_call)
		unरेजिस्टर_netdevice_notअगरier_dev_net(priv->netdev,
						      &tc->netdevice_nb,
						      &tc->netdevice_nn);

	mlx5e_mod_hdr_tbl_destroy(&tc->mod_hdr);
	mutex_destroy(&tc->hairpin_tbl_lock);

	rhashtable_मुक्त_and_destroy(&tc->ht, _mlx5e_tc_del_flow, शून्य);

	अगर (!IS_ERR_OR_शून्य(tc->t)) अणु
		mlx5_chains_put_table(tc->chains, 0, 1, MLX5E_TC_FT_LEVEL);
		tc->t = शून्य;
	पूर्ण
	mutex_destroy(&tc->t_lock);

	mlx5_tc_ct_clean(tc->ct);
	mapping_destroy(tc->mapping);
	mlx5_chains_destroy(tc->chains);
पूर्ण

पूर्णांक mlx5e_tc_esw_init(काष्ठा rhashtable *tc_ht)
अणु
	स्थिर माप_प्रकार sz_enc_opts = माप(काष्ठा tunnel_match_enc_opts);
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mapping_ctx *mapping;
	काष्ठा mlx5_eचयन *esw;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक err = 0;

	uplink_priv = container_of(tc_ht, काष्ठा mlx5_rep_uplink_priv, tc_ht);
	rpriv = container_of(uplink_priv, काष्ठा mlx5e_rep_priv, uplink_priv);
	priv = netdev_priv(rpriv->netdev);
	esw = priv->mdev->priv.eचयन;

	uplink_priv->ct_priv = mlx5_tc_ct_init(netdev_priv(priv->netdev),
					       esw_chains(esw),
					       &esw->offloads.mod_hdr,
					       MLX5_FLOW_NAMESPACE_FDB);

#अगर IS_ENABLED(CONFIG_MLX5_TC_SAMPLE)
	uplink_priv->esw_psample = mlx5_esw_sample_init(netdev_priv(priv->netdev));
#पूर्ण_अगर

	mapping = mapping_create(माप(काष्ठा tunnel_match_key),
				 TUNNEL_INFO_BITS_MASK, true);
	अगर (IS_ERR(mapping)) अणु
		err = PTR_ERR(mapping);
		जाओ err_tun_mapping;
	पूर्ण
	uplink_priv->tunnel_mapping = mapping;

	/* 0xFFF is reserved क्रम stack devices slow path table mark */
	mapping = mapping_create(sz_enc_opts, ENC_OPTS_BITS_MASK - 1, true);
	अगर (IS_ERR(mapping)) अणु
		err = PTR_ERR(mapping);
		जाओ err_enc_opts_mapping;
	पूर्ण
	uplink_priv->tunnel_enc_opts_mapping = mapping;

	err = rhashtable_init(tc_ht, &tc_ht_params);
	अगर (err)
		जाओ err_ht_init;

	lockdep_set_class(&tc_ht->mutex, &tc_ht_lock_key);

	uplink_priv->encap = mlx5e_tc_tun_init(priv);
	अगर (IS_ERR(uplink_priv->encap)) अणु
		err = PTR_ERR(uplink_priv->encap);
		जाओ err_रेजिस्टर_fib_notअगरier;
	पूर्ण

	वापस 0;

err_रेजिस्टर_fib_notअगरier:
	rhashtable_destroy(tc_ht);
err_ht_init:
	mapping_destroy(uplink_priv->tunnel_enc_opts_mapping);
err_enc_opts_mapping:
	mapping_destroy(uplink_priv->tunnel_mapping);
err_tun_mapping:
#अगर IS_ENABLED(CONFIG_MLX5_TC_SAMPLE)
	mlx5_esw_sample_cleanup(uplink_priv->esw_psample);
#पूर्ण_अगर
	mlx5_tc_ct_clean(uplink_priv->ct_priv);
	netdev_warn(priv->netdev,
		    "Failed to initialize tc (eswitch), err: %d", err);
	वापस err;
पूर्ण

व्योम mlx5e_tc_esw_cleanup(काष्ठा rhashtable *tc_ht)
अणु
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;

	uplink_priv = container_of(tc_ht, काष्ठा mlx5_rep_uplink_priv, tc_ht);

	rhashtable_मुक्त_and_destroy(tc_ht, _mlx5e_tc_del_flow, शून्य);
	mlx5e_tc_tun_cleanup(uplink_priv->encap);

	mapping_destroy(uplink_priv->tunnel_enc_opts_mapping);
	mapping_destroy(uplink_priv->tunnel_mapping);

#अगर IS_ENABLED(CONFIG_MLX5_TC_SAMPLE)
	mlx5_esw_sample_cleanup(uplink_priv->esw_psample);
#पूर्ण_अगर
	mlx5_tc_ct_clean(uplink_priv->ct_priv);
पूर्ण

पूर्णांक mlx5e_tc_num_filters(काष्ठा mlx5e_priv *priv, अचिन्हित दीर्घ flags)
अणु
	काष्ठा rhashtable *tc_ht = get_tc_ht(priv, flags);

	वापस atomic_पढ़ो(&tc_ht->nelems);
पूर्ण

व्योम mlx5e_tc_clean_fdb_peer_flows(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5e_tc_flow *flow, *पंचांगp;

	list_क्रम_each_entry_safe(flow, पंचांगp, &esw->offloads.peer_flows, peer)
		__mlx5e_tc_del_fdb_peer_flow(flow);
पूर्ण

व्योम mlx5e_tc_reoffload_flows_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_rep_uplink_priv *rpriv =
		container_of(work, काष्ठा mlx5_rep_uplink_priv,
			     reoffload_flows_work);
	काष्ठा mlx5e_tc_flow *flow, *पंचांगp;

	mutex_lock(&rpriv->unपढ़ोy_flows_lock);
	list_क्रम_each_entry_safe(flow, पंचांगp, &rpriv->unपढ़ोy_flows, unपढ़ोy) अणु
		अगर (!mlx5e_tc_add_fdb_flow(flow->priv, flow, शून्य))
			unपढ़ोy_flow_del(flow);
	पूर्ण
	mutex_unlock(&rpriv->unपढ़ोy_flows_lock);
पूर्ण

अटल पूर्णांक mlx5e_setup_tc_cls_flower(काष्ठा mlx5e_priv *priv,
				     काष्ठा flow_cls_offload *cls_flower,
				     अचिन्हित दीर्घ flags)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस mlx5e_configure_flower(priv->netdev, priv, cls_flower,
					      flags);
	हाल FLOW_CLS_DESTROY:
		वापस mlx5e_delete_flower(priv->netdev, priv, cls_flower,
					   flags);
	हाल FLOW_CLS_STATS:
		वापस mlx5e_stats_flower(priv->netdev, priv, cls_flower,
					  flags);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlx5e_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
			    व्योम *cb_priv)
अणु
	अचिन्हित दीर्घ flags = MLX5_TC_FLAG(INGRESS);
	काष्ठा mlx5e_priv *priv = cb_priv;

	अगर (!priv->netdev || !netअगर_device_present(priv->netdev))
		वापस -EOPNOTSUPP;

	अगर (mlx5e_is_uplink_rep(priv))
		flags |= MLX5_TC_FLAG(ESW_OFFLOAD);
	अन्यथा
		flags |= MLX5_TC_FLAG(NIC_OFFLOAD);

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस mlx5e_setup_tc_cls_flower(priv, type_data, flags);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

bool mlx5e_tc_update_skb(काष्ठा mlx5_cqe64 *cqe,
			 काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	u32 chain = 0, chain_tag, reg_b, zone_restore_id;
	काष्ठा mlx5e_priv *priv = netdev_priv(skb->dev);
	काष्ठा mlx5e_tc_table *tc = &priv->fs.tc;
	काष्ठा mlx5_mapped_obj mapped_obj;
	काष्ठा tc_skb_ext *tc_skb_ext;
	पूर्णांक err;

	reg_b = be32_to_cpu(cqe->ft_metadata);

	chain_tag = reg_b & MLX5E_TC_TABLE_CHAIN_TAG_MASK;

	err = mapping_find(tc->mapping, chain_tag, &mapped_obj);
	अगर (err) अणु
		netdev_dbg(priv->netdev,
			   "Couldn't find chain for chain tag: %d, err: %d\n",
			   chain_tag, err);
		वापस false;
	पूर्ण

	अगर (mapped_obj.type == MLX5_MAPPED_OBJ_CHAIN) अणु
		chain = mapped_obj.chain;
		tc_skb_ext = tc_skb_ext_alloc(skb);
		अगर (WARN_ON(!tc_skb_ext))
			वापस false;

		tc_skb_ext->chain = chain;

		zone_restore_id = (reg_b >> REG_MAPPING_SHIFT(NIC_ZONE_RESTORE_TO_REG)) &
			ESW_ZONE_ID_MASK;

		अगर (!mlx5e_tc_ct_restore_flow(tc->ct, skb,
					      zone_restore_id))
			वापस false;
	पूर्ण अन्यथा अणु
		netdev_dbg(priv->netdev, "Invalid mapped object type: %d\n", mapped_obj.type);
		वापस false;
	पूर्ण
#पूर्ण_अगर /* CONFIG_NET_TC_SKB_EXT */

	वापस true;
पूर्ण
