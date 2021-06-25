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

#समावेश <linux/hash.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश "en.h"

#घोषणा ARFS_HASH_SHIFT BITS_PER_BYTE
#घोषणा ARFS_HASH_SIZE BIT(BITS_PER_BYTE)

काष्ठा arfs_table अणु
	काष्ठा mlx5e_flow_table  ft;
	काष्ठा mlx5_flow_handle	 *शेष_rule;
	काष्ठा hlist_head	 rules_hash[ARFS_HASH_SIZE];
पूर्ण;

क्रमागत arfs_type अणु
	ARFS_IPV4_TCP,
	ARFS_IPV6_TCP,
	ARFS_IPV4_UDP,
	ARFS_IPV6_UDP,
	ARFS_NUM_TYPES,
पूर्ण;

काष्ठा mlx5e_arfs_tables अणु
	काष्ठा arfs_table arfs_tables[ARFS_NUM_TYPES];
	/* Protect aRFS rules list */
	spinlock_t                     arfs_lock;
	काष्ठा list_head               rules;
	पूर्णांक                            last_filter_id;
	काष्ठा workqueue_काष्ठा        *wq;
पूर्ण;

काष्ठा arfs_tuple अणु
	__be16 etype;
	u8     ip_proto;
	जोड़ अणु
		__be32 src_ipv4;
		काष्ठा in6_addr src_ipv6;
	पूर्ण;
	जोड़ अणु
		__be32 dst_ipv4;
		काष्ठा in6_addr dst_ipv6;
	पूर्ण;
	__be16 src_port;
	__be16 dst_port;
पूर्ण;

काष्ठा arfs_rule अणु
	काष्ठा mlx5e_priv	*priv;
	काष्ठा work_काष्ठा      arfs_work;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा hlist_node	hlist;
	पूर्णांक			rxq;
	/* Flow ID passed to nकरो_rx_flow_steer */
	पूर्णांक			flow_id;
	/* Filter ID वापसed by nकरो_rx_flow_steer */
	पूर्णांक			filter_id;
	काष्ठा arfs_tuple	tuple;
पूर्ण;

#घोषणा mlx5e_क्रम_each_arfs_rule(hn, पंचांगp, arfs_tables, i, j) \
	क्रम (i = 0; i < ARFS_NUM_TYPES; i++) \
		mlx5e_क्रम_each_hash_arfs_rule(hn, पंचांगp, arfs_tables[i].rules_hash, j)

#घोषणा mlx5e_क्रम_each_hash_arfs_rule(hn, पंचांगp, hash, j) \
	क्रम (j = 0; j < ARFS_HASH_SIZE; j++) \
		hlist_क्रम_each_entry_safe(hn, पंचांगp, &hash[j], hlist)

अटल क्रमागत mlx5e_traffic_types arfs_get_tt(क्रमागत arfs_type type)
अणु
	चयन (type) अणु
	हाल ARFS_IPV4_TCP:
		वापस MLX5E_TT_IPV4_TCP;
	हाल ARFS_IPV4_UDP:
		वापस MLX5E_TT_IPV4_UDP;
	हाल ARFS_IPV6_TCP:
		वापस MLX5E_TT_IPV6_TCP;
	हाल ARFS_IPV6_UDP:
		वापस MLX5E_TT_IPV6_UDP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक arfs_disable(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < ARFS_NUM_TYPES; i++) अणु
		/* Modअगरy ttc rules destination back to their शेष */
		err = mlx5e_ttc_fwd_शेष_dest(priv, arfs_get_tt(i));
		अगर (err) अणु
			netdev_err(priv->netdev,
				   "%s: modify ttc[%d] default destination failed, err(%d)\n",
				   __func__, arfs_get_tt(i), err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम arfs_del_rules(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5e_arfs_disable(काष्ठा mlx5e_priv *priv)
अणु
	arfs_del_rules(priv);

	वापस arfs_disable(priv);
पूर्ण

पूर्णांक mlx5e_arfs_enable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	पूर्णांक err, i;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	क्रम (i = 0; i < ARFS_NUM_TYPES; i++) अणु
		dest.ft = priv->fs.arfs->arfs_tables[i].ft.t;
		/* Modअगरy ttc rules destination to poपूर्णांक on the aRFS FTs */
		err = mlx5e_ttc_fwd_dest(priv, arfs_get_tt(i), &dest);
		अगर (err) अणु
			netdev_err(priv->netdev,
				   "%s: modify ttc[%d] dest to arfs, failed err(%d)\n",
				   __func__, arfs_get_tt(i), err);
			arfs_disable(priv);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम arfs_destroy_table(काष्ठा arfs_table *arfs_t)
अणु
	mlx5_del_flow_rules(arfs_t->शेष_rule);
	mlx5e_destroy_flow_table(&arfs_t->ft);
पूर्ण

अटल व्योम _mlx5e_cleanup_tables(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक i;

	arfs_del_rules(priv);
	destroy_workqueue(priv->fs.arfs->wq);
	क्रम (i = 0; i < ARFS_NUM_TYPES; i++) अणु
		अगर (!IS_ERR_OR_शून्य(priv->fs.arfs->arfs_tables[i].ft.t))
			arfs_destroy_table(&priv->fs.arfs->arfs_tables[i]);
	पूर्ण
पूर्ण

व्योम mlx5e_arfs_destroy_tables(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!(priv->netdev->hw_features & NETIF_F_NTUPLE))
		वापस;

	_mlx5e_cleanup_tables(priv);
	kvमुक्त(priv->fs.arfs);
पूर्ण

अटल पूर्णांक arfs_add_शेष_rule(काष्ठा mlx5e_priv *priv,
				 क्रमागत arfs_type type)
अणु
	काष्ठा arfs_table *arfs_t = &priv->fs.arfs->arfs_tables[type];
	काष्ठा mlx5e_tir *tir = priv->indir_tir;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	क्रमागत mlx5e_traffic_types tt;
	पूर्णांक err = 0;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	tt = arfs_get_tt(type);
	अगर (tt == -EINVAL) अणु
		netdev_err(priv->netdev, "%s: bad arfs_type: %d\n",
			   __func__, type);
		वापस -EINVAL;
	पूर्ण

	/* FIXME: Must use mlx5e_ttc_get_शेष_dest(),
	 * but can't since TTC शेष is not setup yet !
	 */
	dest.tir_num = tir[tt].tirn;
	arfs_t->शेष_rule = mlx5_add_flow_rules(arfs_t->ft.t, शून्य,
						   &flow_act,
						   &dest, 1);
	अगर (IS_ERR(arfs_t->शेष_rule)) अणु
		err = PTR_ERR(arfs_t->शेष_rule);
		arfs_t->शेष_rule = शून्य;
		netdev_err(priv->netdev, "%s: add rule failed, arfs type=%d\n",
			   __func__, type);
	पूर्ण

	वापस err;
पूर्ण

#घोषणा MLX5E_ARFS_NUM_GROUPS	2
#घोषणा MLX5E_ARFS_GROUP1_SIZE	(BIT(16) - 1)
#घोषणा MLX5E_ARFS_GROUP2_SIZE	BIT(0)
#घोषणा MLX5E_ARFS_TABLE_SIZE	(MLX5E_ARFS_GROUP1_SIZE +\
				 MLX5E_ARFS_GROUP2_SIZE)
अटल पूर्णांक arfs_create_groups(काष्ठा mlx5e_flow_table *ft,
			      क्रमागत  arfs_type type)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	व्योम *outer_headers_c;
	पूर्णांक ix = 0;
	u32 *in;
	पूर्णांक err;
	u8 *mc;

	ft->g = kसुस्मृति(MLX5E_ARFS_NUM_GROUPS,
			माप(*ft->g), GFP_KERNEL);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर  (!in || !ft->g) अणु
		kमुक्त(ft->g);
		kvमुक्त(in);
		वापस -ENOMEM;
	पूर्ण

	mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	outer_headers_c = MLX5_ADDR_OF(fte_match_param, mc,
				       outer_headers);
	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, ethertype);
	चयन (type) अणु
	हाल ARFS_IPV4_TCP:
	हाल ARFS_IPV6_TCP:
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, tcp_dport);
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, tcp_sport);
		अवरोध;
	हाल ARFS_IPV4_UDP:
	हाल ARFS_IPV6_UDP:
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, udp_dport);
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c, udp_sport);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (type) अणु
	हाल ARFS_IPV4_TCP:
	हाल ARFS_IPV4_UDP:
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c,
				 src_ipv4_src_ipv6.ipv4_layout.ipv4);
		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, outer_headers_c,
				 dst_ipv4_dst_ipv6.ipv4_layout.ipv4);
		अवरोध;
	हाल ARFS_IPV6_TCP:
	हाल ARFS_IPV6_UDP:
		स_रखो(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       0xff, 16);
		स_रखो(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       0xff, 16);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out;
	पूर्ण

	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_ARFS_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	अगर (IS_ERR(ft->g[ft->num_groups]))
		जाओ err;
	ft->num_groups++;

	स_रखो(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_ARFS_GROUP2_SIZE;
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
out:
	kvमुक्त(in);

	वापस err;
पूर्ण

अटल पूर्णांक arfs_create_table(काष्ठा mlx5e_priv *priv,
			     क्रमागत arfs_type type)
अणु
	काष्ठा mlx5e_arfs_tables *arfs = priv->fs.arfs;
	काष्ठा mlx5e_flow_table *ft = &arfs->arfs_tables[type].ft;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	पूर्णांक err;

	ft->num_groups = 0;

	ft_attr.max_fte = MLX5E_ARFS_TABLE_SIZE;
	ft_attr.level = MLX5E_ARFS_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &ft_attr);
	अगर (IS_ERR(ft->t)) अणु
		err = PTR_ERR(ft->t);
		ft->t = शून्य;
		वापस err;
	पूर्ण

	err = arfs_create_groups(ft, type);
	अगर (err)
		जाओ err;

	err = arfs_add_शेष_rule(priv, type);
	अगर (err)
		जाओ err;

	वापस 0;
err:
	mlx5e_destroy_flow_table(ft);
	वापस err;
पूर्ण

पूर्णांक mlx5e_arfs_create_tables(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	अगर (!(priv->netdev->hw_features & NETIF_F_NTUPLE))
		वापस 0;

	priv->fs.arfs = kvzalloc(माप(*priv->fs.arfs), GFP_KERNEL);
	अगर (!priv->fs.arfs)
		वापस -ENOMEM;

	spin_lock_init(&priv->fs.arfs->arfs_lock);
	INIT_LIST_HEAD(&priv->fs.arfs->rules);
	priv->fs.arfs->wq = create_singlethपढ़ो_workqueue("mlx5e_arfs");
	अगर (!priv->fs.arfs->wq)
		जाओ err;

	क्रम (i = 0; i < ARFS_NUM_TYPES; i++) अणु
		err = arfs_create_table(priv, i);
		अगर (err)
			जाओ err_des;
	पूर्ण
	वापस 0;

err_des:
	_mlx5e_cleanup_tables(priv);
err:
	kvमुक्त(priv->fs.arfs);
	वापस err;
पूर्ण

#घोषणा MLX5E_ARFS_EXPIRY_QUOTA 60

अटल व्योम arfs_may_expire_flow(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा arfs_rule *arfs_rule;
	काष्ठा hlist_node *hपंचांगp;
	HLIST_HEAD(del_list);
	पूर्णांक quota = 0;
	पूर्णांक i;
	पूर्णांक j;

	spin_lock_bh(&priv->fs.arfs->arfs_lock);
	mlx5e_क्रम_each_arfs_rule(arfs_rule, hपंचांगp, priv->fs.arfs->arfs_tables, i, j) अणु
		अगर (!work_pending(&arfs_rule->arfs_work) &&
		    rps_may_expire_flow(priv->netdev,
					arfs_rule->rxq, arfs_rule->flow_id,
					arfs_rule->filter_id)) अणु
			hlist_del_init(&arfs_rule->hlist);
			hlist_add_head(&arfs_rule->hlist, &del_list);
			अगर (quota++ > MLX5E_ARFS_EXPIRY_QUOTA)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->fs.arfs->arfs_lock);
	hlist_क्रम_each_entry_safe(arfs_rule, hपंचांगp, &del_list, hlist) अणु
		अगर (arfs_rule->rule)
			mlx5_del_flow_rules(arfs_rule->rule);
		hlist_del(&arfs_rule->hlist);
		kमुक्त(arfs_rule);
	पूर्ण
पूर्ण

अटल व्योम arfs_del_rules(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा hlist_node *hपंचांगp;
	काष्ठा arfs_rule *rule;
	HLIST_HEAD(del_list);
	पूर्णांक i;
	पूर्णांक j;

	spin_lock_bh(&priv->fs.arfs->arfs_lock);
	mlx5e_क्रम_each_arfs_rule(rule, hपंचांगp, priv->fs.arfs->arfs_tables, i, j) अणु
		hlist_del_init(&rule->hlist);
		hlist_add_head(&rule->hlist, &del_list);
	पूर्ण
	spin_unlock_bh(&priv->fs.arfs->arfs_lock);

	hlist_क्रम_each_entry_safe(rule, hपंचांगp, &del_list, hlist) अणु
		cancel_work_sync(&rule->arfs_work);
		अगर (rule->rule)
			mlx5_del_flow_rules(rule->rule);
		hlist_del(&rule->hlist);
		kमुक्त(rule);
	पूर्ण
पूर्ण

अटल काष्ठा hlist_head *
arfs_hash_bucket(काष्ठा arfs_table *arfs_t, __be16 src_port,
		 __be16 dst_port)
अणु
	अचिन्हित दीर्घ l;
	पूर्णांक bucket_idx;

	l = (__क्रमce अचिन्हित दीर्घ)src_port |
	    ((__क्रमce अचिन्हित दीर्घ)dst_port << 2);

	bucket_idx = hash_दीर्घ(l, ARFS_HASH_SHIFT);

	वापस &arfs_t->rules_hash[bucket_idx];
पूर्ण

अटल काष्ठा arfs_table *arfs_get_table(काष्ठा mlx5e_arfs_tables *arfs,
					 u8 ip_proto, __be16 etype)
अणु
	अगर (etype == htons(ETH_P_IP) && ip_proto == IPPROTO_TCP)
		वापस &arfs->arfs_tables[ARFS_IPV4_TCP];
	अगर (etype == htons(ETH_P_IP) && ip_proto == IPPROTO_UDP)
		वापस &arfs->arfs_tables[ARFS_IPV4_UDP];
	अगर (etype == htons(ETH_P_IPV6) && ip_proto == IPPROTO_TCP)
		वापस &arfs->arfs_tables[ARFS_IPV6_TCP];
	अगर (etype == htons(ETH_P_IPV6) && ip_proto == IPPROTO_UDP)
		वापस &arfs->arfs_tables[ARFS_IPV6_UDP];

	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5_flow_handle *arfs_add_rule(काष्ठा mlx5e_priv *priv,
					      काष्ठा arfs_rule *arfs_rule)
अणु
	काष्ठा mlx5e_arfs_tables *arfs = priv->fs.arfs;
	काष्ठा arfs_tuple *tuple = &arfs_rule->tuple;
	काष्ठा mlx5_flow_handle *rule = शून्य;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	MLX5_DECLARE_FLOW_ACT(flow_act);
	काष्ठा arfs_table *arfs_table;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक err = 0;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
			 outer_headers.ethertype);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.ethertype,
		 ntohs(tuple->etype));
	arfs_table = arfs_get_table(arfs, tuple->ip_proto, tuple->etype);
	अगर (!arfs_table) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ft = arfs_table->ft.t;
	अगर (tuple->ip_proto == IPPROTO_TCP) अणु
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.tcp_dport);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.tcp_sport);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.tcp_dport,
			 ntohs(tuple->dst_port));
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.tcp_sport,
			 ntohs(tuple->src_port));
	पूर्ण अन्यथा अणु
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.udp_dport);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.udp_sport);
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.udp_dport,
			 ntohs(tuple->dst_port));
		MLX5_SET(fte_match_param, spec->match_value, outer_headers.udp_sport,
			 ntohs(tuple->src_port));
	पूर्ण
	अगर (tuple->etype == htons(ETH_P_IP)) अणु
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &tuple->src_ipv4,
		       4);
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &tuple->dst_ipv4,
		       4);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.src_ipv4_src_ipv6.ipv4_layout.ipv4);
		MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria,
				 outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4);
	पूर्ण अन्यथा अणु
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &tuple->src_ipv6,
		       16);
		स_नकल(MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &tuple->dst_ipv6,
		       16);
		स_रखो(MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    outer_headers.src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       0xff,
		       16);
		स_रखो(MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       0xff,
		       16);
	पूर्ण
	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dest.tir_num = priv->direct_tir[arfs_rule->rxq].tirn;
	rule = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		priv->channel_stats[arfs_rule->rxq].rq.arfs_err++;
		mlx5e_dbg(HW, priv,
			  "%s: add rule(filter id=%d, rq idx=%d, ip proto=0x%x) failed,err=%d\n",
			  __func__, arfs_rule->filter_id, arfs_rule->rxq,
			  tuple->ip_proto, err);
	पूर्ण

out:
	kvमुक्त(spec);
	वापस err ? ERR_PTR(err) : rule;
पूर्ण

अटल व्योम arfs_modअगरy_rule_rq(काष्ठा mlx5e_priv *priv,
				काष्ठा mlx5_flow_handle *rule, u16 rxq)
अणु
	काष्ठा mlx5_flow_destination dst = अणुपूर्ण;
	पूर्णांक err = 0;

	dst.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dst.tir_num = priv->direct_tir[rxq].tirn;
	err =  mlx5_modअगरy_rule_destination(rule, &dst, शून्य);
	अगर (err)
		netdev_warn(priv->netdev,
			    "Failed to modify aRFS rule destination to rq=%d\n", rxq);
पूर्ण

अटल व्योम arfs_handle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arfs_rule *arfs_rule = container_of(work,
						   काष्ठा arfs_rule,
						   arfs_work);
	काष्ठा mlx5e_priv *priv = arfs_rule->priv;
	काष्ठा mlx5_flow_handle *rule;

	mutex_lock(&priv->state_lock);
	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		spin_lock_bh(&priv->fs.arfs->arfs_lock);
		hlist_del(&arfs_rule->hlist);
		spin_unlock_bh(&priv->fs.arfs->arfs_lock);

		mutex_unlock(&priv->state_lock);
		kमुक्त(arfs_rule);
		जाओ out;
	पूर्ण
	mutex_unlock(&priv->state_lock);

	अगर (!arfs_rule->rule) अणु
		rule = arfs_add_rule(priv, arfs_rule);
		अगर (IS_ERR(rule))
			जाओ out;
		arfs_rule->rule = rule;
	पूर्ण अन्यथा अणु
		arfs_modअगरy_rule_rq(priv, arfs_rule->rule,
				    arfs_rule->rxq);
	पूर्ण
out:
	arfs_may_expire_flow(priv);
पूर्ण

अटल काष्ठा arfs_rule *arfs_alloc_rule(काष्ठा mlx5e_priv *priv,
					 काष्ठा arfs_table *arfs_t,
					 स्थिर काष्ठा flow_keys *fk,
					 u16 rxq, u32 flow_id)
अणु
	काष्ठा arfs_rule *rule;
	काष्ठा arfs_tuple *tuple;

	rule = kzalloc(माप(*rule), GFP_ATOMIC);
	अगर (!rule)
		वापस शून्य;

	rule->priv = priv;
	rule->rxq = rxq;
	INIT_WORK(&rule->arfs_work, arfs_handle_work);

	tuple = &rule->tuple;
	tuple->etype = fk->basic.n_proto;
	tuple->ip_proto = fk->basic.ip_proto;
	अगर (tuple->etype == htons(ETH_P_IP)) अणु
		tuple->src_ipv4 = fk->addrs.v4addrs.src;
		tuple->dst_ipv4 = fk->addrs.v4addrs.dst;
	पूर्ण अन्यथा अणु
		स_नकल(&tuple->src_ipv6, &fk->addrs.v6addrs.src,
		       माप(काष्ठा in6_addr));
		स_नकल(&tuple->dst_ipv6, &fk->addrs.v6addrs.dst,
		       माप(काष्ठा in6_addr));
	पूर्ण
	tuple->src_port = fk->ports.src;
	tuple->dst_port = fk->ports.dst;

	rule->flow_id = flow_id;
	rule->filter_id = priv->fs.arfs->last_filter_id++ % RPS_NO_FILTER;

	hlist_add_head(&rule->hlist,
		       arfs_hash_bucket(arfs_t, tuple->src_port,
					tuple->dst_port));
	वापस rule;
पूर्ण

अटल bool arfs_cmp(स्थिर काष्ठा arfs_tuple *tuple, स्थिर काष्ठा flow_keys *fk)
अणु
	अगर (tuple->src_port != fk->ports.src || tuple->dst_port != fk->ports.dst)
		वापस false;
	अगर (tuple->etype != fk->basic.n_proto)
		वापस false;
	अगर (tuple->etype == htons(ETH_P_IP))
		वापस tuple->src_ipv4 == fk->addrs.v4addrs.src &&
		       tuple->dst_ipv4 == fk->addrs.v4addrs.dst;
	अगर (tuple->etype == htons(ETH_P_IPV6))
		वापस !स_भेद(&tuple->src_ipv6, &fk->addrs.v6addrs.src,
			       माप(काष्ठा in6_addr)) &&
		       !स_भेद(&tuple->dst_ipv6, &fk->addrs.v6addrs.dst,
			       माप(काष्ठा in6_addr));
	वापस false;
पूर्ण

अटल काष्ठा arfs_rule *arfs_find_rule(काष्ठा arfs_table *arfs_t,
					स्थिर काष्ठा flow_keys *fk)
अणु
	काष्ठा arfs_rule *arfs_rule;
	काष्ठा hlist_head *head;

	head = arfs_hash_bucket(arfs_t, fk->ports.src, fk->ports.dst);
	hlist_क्रम_each_entry(arfs_rule, head, hlist) अणु
		अगर (arfs_cmp(&arfs_rule->tuple, fk))
			वापस arfs_rule;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक mlx5e_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
			u16 rxq_index, u32 flow_id)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_arfs_tables *arfs = priv->fs.arfs;
	काष्ठा arfs_table *arfs_t;
	काष्ठा arfs_rule *arfs_rule;
	काष्ठा flow_keys fk;

	अगर (!skb_flow_dissect_flow_keys(skb, &fk, 0))
		वापस -EPROTONOSUPPORT;

	अगर (fk.basic.n_proto != htons(ETH_P_IP) &&
	    fk.basic.n_proto != htons(ETH_P_IPV6))
		वापस -EPROTONOSUPPORT;

	अगर (skb->encapsulation)
		वापस -EPROTONOSUPPORT;

	arfs_t = arfs_get_table(arfs, fk.basic.ip_proto, fk.basic.n_proto);
	अगर (!arfs_t)
		वापस -EPROTONOSUPPORT;

	spin_lock_bh(&arfs->arfs_lock);
	arfs_rule = arfs_find_rule(arfs_t, &fk);
	अगर (arfs_rule) अणु
		अगर (arfs_rule->rxq == rxq_index) अणु
			spin_unlock_bh(&arfs->arfs_lock);
			वापस arfs_rule->filter_id;
		पूर्ण
		arfs_rule->rxq = rxq_index;
	पूर्ण अन्यथा अणु
		arfs_rule = arfs_alloc_rule(priv, arfs_t, &fk, rxq_index, flow_id);
		अगर (!arfs_rule) अणु
			spin_unlock_bh(&arfs->arfs_lock);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	queue_work(priv->fs.arfs->wq, &arfs_rule->arfs_work);
	spin_unlock_bh(&arfs->arfs_lock);
	वापस arfs_rule->filter_id;
पूर्ण

