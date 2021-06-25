<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/hash.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/jhash.h>
#समावेश <linux/math64.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/pkt_cls.h>

#समावेश "cmsg.h"
#समावेश "main.h"
#समावेश "../nfp_app.h"

काष्ठा nfp_mask_id_table अणु
	काष्ठा hlist_node link;
	u32 hash_key;
	u32 ref_cnt;
	u8 mask_id;
पूर्ण;

काष्ठा nfp_fl_flow_table_cmp_arg अणु
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ cookie;
पूर्ण;

काष्ठा nfp_fl_stats_ctx_to_flow अणु
	काष्ठा rhash_head ht_node;
	u32 stats_cxt;
	काष्ठा nfp_fl_payload *flow;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params stats_ctx_table_params = अणु
	.key_offset	= दुरत्व(काष्ठा nfp_fl_stats_ctx_to_flow, stats_cxt),
	.head_offset	= दुरत्व(काष्ठा nfp_fl_stats_ctx_to_flow, ht_node),
	.key_len	= माप(u32),
पूर्ण;

अटल पूर्णांक nfp_release_stats_entry(काष्ठा nfp_app *app, u32 stats_context_id)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा circ_buf *ring;

	ring = &priv->stats_ids.मुक्त_list;
	/* Check अगर buffer is full. */
	अगर (!CIRC_SPACE(ring->head, ring->tail,
			priv->stats_ring_size * NFP_FL_STATS_ELEM_RS -
			NFP_FL_STATS_ELEM_RS + 1))
		वापस -ENOBUFS;

	स_नकल(&ring->buf[ring->head], &stats_context_id, NFP_FL_STATS_ELEM_RS);
	ring->head = (ring->head + NFP_FL_STATS_ELEM_RS) %
		     (priv->stats_ring_size * NFP_FL_STATS_ELEM_RS);

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_get_stats_entry(काष्ठा nfp_app *app, u32 *stats_context_id)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	u32 मुक्तd_stats_id, temp_stats_id;
	काष्ठा circ_buf *ring;

	ring = &priv->stats_ids.मुक्त_list;
	मुक्तd_stats_id = priv->stats_ring_size;
	/* Check क्रम unallocated entries first. */
	अगर (priv->stats_ids.init_unalloc > 0) अणु
		*stats_context_id =
			FIELD_PREP(NFP_FL_STAT_ID_STAT,
				   priv->stats_ids.init_unalloc - 1) |
			FIELD_PREP(NFP_FL_STAT_ID_MU_NUM,
				   priv->active_mem_unit);

		अगर (++priv->active_mem_unit == priv->total_mem_units) अणु
			priv->stats_ids.init_unalloc--;
			priv->active_mem_unit = 0;
		पूर्ण

		वापस 0;
	पूर्ण

	/* Check अगर buffer is empty. */
	अगर (ring->head == ring->tail) अणु
		*stats_context_id = मुक्तd_stats_id;
		वापस -ENOENT;
	पूर्ण

	स_नकल(&temp_stats_id, &ring->buf[ring->tail], NFP_FL_STATS_ELEM_RS);
	*stats_context_id = temp_stats_id;
	स_नकल(&ring->buf[ring->tail], &मुक्तd_stats_id, NFP_FL_STATS_ELEM_RS);
	ring->tail = (ring->tail + NFP_FL_STATS_ELEM_RS) %
		     (priv->stats_ring_size * NFP_FL_STATS_ELEM_RS);

	वापस 0;
पूर्ण

/* Must be called with either RTNL or rcu_पढ़ो_lock */
काष्ठा nfp_fl_payload *
nfp_flower_search_fl_table(काष्ठा nfp_app *app, अचिन्हित दीर्घ tc_flower_cookie,
			   काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_fl_flow_table_cmp_arg flower_cmp_arg;
	काष्ठा nfp_flower_priv *priv = app->priv;

	flower_cmp_arg.netdev = netdev;
	flower_cmp_arg.cookie = tc_flower_cookie;

	वापस rhashtable_lookup_fast(&priv->flow_table, &flower_cmp_arg,
				      nfp_flower_table_params);
पूर्ण

व्योम nfp_flower_rx_flow_stats(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक msg_len = nfp_flower_cmsg_get_data_len(skb);
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_stats_frame *stats;
	अचिन्हित अक्षर *msg;
	u32 ctx_id;
	पूर्णांक i;

	msg = nfp_flower_cmsg_get_data(skb);

	spin_lock(&priv->stats_lock);
	क्रम (i = 0; i < msg_len / माप(*stats); i++) अणु
		stats = (काष्ठा nfp_fl_stats_frame *)msg + i;
		ctx_id = be32_to_cpu(stats->stats_con_id);
		priv->stats[ctx_id].pkts += be32_to_cpu(stats->pkt_count);
		priv->stats[ctx_id].bytes += be64_to_cpu(stats->byte_count);
		priv->stats[ctx_id].used = jअगरfies;
	पूर्ण
	spin_unlock(&priv->stats_lock);
पूर्ण

अटल पूर्णांक nfp_release_mask_id(काष्ठा nfp_app *app, u8 mask_id)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा circ_buf *ring;

	ring = &priv->mask_ids.mask_id_मुक्त_list;
	/* Checking अगर buffer is full. */
	अगर (CIRC_SPACE(ring->head, ring->tail, NFP_FLOWER_MASK_ENTRY_RS) == 0)
		वापस -ENOBUFS;

	स_नकल(&ring->buf[ring->head], &mask_id, NFP_FLOWER_MASK_ELEMENT_RS);
	ring->head = (ring->head + NFP_FLOWER_MASK_ELEMENT_RS) %
		     (NFP_FLOWER_MASK_ENTRY_RS * NFP_FLOWER_MASK_ELEMENT_RS);

	priv->mask_ids.last_used[mask_id] = kसमय_get();

	वापस 0;
पूर्ण

अटल पूर्णांक nfp_mask_alloc(काष्ठा nfp_app *app, u8 *mask_id)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	kसमय_प्रकार reuse_समयout;
	काष्ठा circ_buf *ring;
	u8 temp_id, मुक्तd_id;

	ring = &priv->mask_ids.mask_id_मुक्त_list;
	मुक्तd_id = NFP_FLOWER_MASK_ENTRY_RS - 1;
	/* Checking क्रम unallocated entries first. */
	अगर (priv->mask_ids.init_unallocated > 0) अणु
		*mask_id = priv->mask_ids.init_unallocated;
		priv->mask_ids.init_unallocated--;
		वापस 0;
	पूर्ण

	/* Checking अगर buffer is empty. */
	अगर (ring->head == ring->tail)
		जाओ err_not_found;

	स_नकल(&temp_id, &ring->buf[ring->tail], NFP_FLOWER_MASK_ELEMENT_RS);
	*mask_id = temp_id;

	reuse_समयout = kसमय_add_ns(priv->mask_ids.last_used[*mask_id],
				     NFP_FL_MASK_REUSE_TIME_NS);

	अगर (kसमय_beक्रमe(kसमय_get(), reuse_समयout))
		जाओ err_not_found;

	स_नकल(&ring->buf[ring->tail], &मुक्तd_id, NFP_FLOWER_MASK_ELEMENT_RS);
	ring->tail = (ring->tail + NFP_FLOWER_MASK_ELEMENT_RS) %
		     (NFP_FLOWER_MASK_ENTRY_RS * NFP_FLOWER_MASK_ELEMENT_RS);

	वापस 0;

err_not_found:
	*mask_id = मुक्तd_id;
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
nfp_add_mask_table(काष्ठा nfp_app *app, अक्षर *mask_data, u32 mask_len)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_mask_id_table *mask_entry;
	अचिन्हित दीर्घ hash_key;
	u8 mask_id;

	अगर (nfp_mask_alloc(app, &mask_id))
		वापस -ENOENT;

	mask_entry = kदो_स्मृति(माप(*mask_entry), GFP_KERNEL);
	अगर (!mask_entry) अणु
		nfp_release_mask_id(app, mask_id);
		वापस -ENOMEM;
	पूर्ण

	INIT_HLIST_NODE(&mask_entry->link);
	mask_entry->mask_id = mask_id;
	hash_key = jhash(mask_data, mask_len, priv->mask_id_seed);
	mask_entry->hash_key = hash_key;
	mask_entry->ref_cnt = 1;
	hash_add(priv->mask_table, &mask_entry->link, hash_key);

	वापस mask_id;
पूर्ण

अटल काष्ठा nfp_mask_id_table *
nfp_search_mask_table(काष्ठा nfp_app *app, अक्षर *mask_data, u32 mask_len)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_mask_id_table *mask_entry;
	अचिन्हित दीर्घ hash_key;

	hash_key = jhash(mask_data, mask_len, priv->mask_id_seed);

	hash_क्रम_each_possible(priv->mask_table, mask_entry, link, hash_key)
		अगर (mask_entry->hash_key == hash_key)
			वापस mask_entry;

	वापस शून्य;
पूर्ण

अटल पूर्णांक
nfp_find_in_mask_table(काष्ठा nfp_app *app, अक्षर *mask_data, u32 mask_len)
अणु
	काष्ठा nfp_mask_id_table *mask_entry;

	mask_entry = nfp_search_mask_table(app, mask_data, mask_len);
	अगर (!mask_entry)
		वापस -ENOENT;

	mask_entry->ref_cnt++;

	/* Casting u8 to पूर्णांक क्रम later use. */
	वापस mask_entry->mask_id;
पूर्ण

अटल bool
nfp_check_mask_add(काष्ठा nfp_app *app, अक्षर *mask_data, u32 mask_len,
		   u8 *meta_flags, u8 *mask_id)
अणु
	पूर्णांक id;

	id = nfp_find_in_mask_table(app, mask_data, mask_len);
	अगर (id < 0) अणु
		id = nfp_add_mask_table(app, mask_data, mask_len);
		अगर (id < 0)
			वापस false;
		*meta_flags |= NFP_FL_META_FLAG_MANAGE_MASK;
	पूर्ण
	*mask_id = id;

	वापस true;
पूर्ण

अटल bool
nfp_check_mask_हटाओ(काष्ठा nfp_app *app, अक्षर *mask_data, u32 mask_len,
		      u8 *meta_flags, u8 *mask_id)
अणु
	काष्ठा nfp_mask_id_table *mask_entry;

	mask_entry = nfp_search_mask_table(app, mask_data, mask_len);
	अगर (!mask_entry)
		वापस false;

	*mask_id = mask_entry->mask_id;
	mask_entry->ref_cnt--;
	अगर (!mask_entry->ref_cnt) अणु
		hash_del(&mask_entry->link);
		nfp_release_mask_id(app, *mask_id);
		kमुक्त(mask_entry);
		अगर (meta_flags)
			*meta_flags |= NFP_FL_META_FLAG_MANAGE_MASK;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक nfp_compile_flow_metadata(काष्ठा nfp_app *app,
			      काष्ठा flow_cls_offload *flow,
			      काष्ठा nfp_fl_payload *nfp_flow,
			      काष्ठा net_device *netdev,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_fl_stats_ctx_to_flow *ctx_entry;
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_payload *check_entry;
	u8 new_mask_id;
	u32 stats_cxt;
	पूर्णांक err;

	err = nfp_get_stats_entry(app, &stats_cxt);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot allocate new stats context");
		वापस err;
	पूर्ण

	nfp_flow->meta.host_ctx_id = cpu_to_be32(stats_cxt);
	nfp_flow->meta.host_cookie = cpu_to_be64(flow->cookie);
	nfp_flow->ingress_dev = netdev;

	ctx_entry = kzalloc(माप(*ctx_entry), GFP_KERNEL);
	अगर (!ctx_entry) अणु
		err = -ENOMEM;
		जाओ err_release_stats;
	पूर्ण

	ctx_entry->stats_cxt = stats_cxt;
	ctx_entry->flow = nfp_flow;

	अगर (rhashtable_insert_fast(&priv->stats_ctx_table, &ctx_entry->ht_node,
				   stats_ctx_table_params)) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_ctx_entry;
	पूर्ण

	/* Do net allocate a mask-id क्रम pre_tun_rules. These flows are used to
	 * configure the pre_tun table and are never actually send to the
	 * firmware as an add-flow message. This causes the mask-id allocation
	 * on the firmware to get out of sync अगर allocated here.
	 */
	new_mask_id = 0;
	अगर (!nfp_flow->pre_tun_rule.dev &&
	    !nfp_check_mask_add(app, nfp_flow->mask_data,
				nfp_flow->meta.mask_len,
				&nfp_flow->meta.flags, &new_mask_id)) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot allocate a new mask id");
		अगर (nfp_release_stats_entry(app, stats_cxt)) अणु
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot release stats context");
			err = -EINVAL;
			जाओ err_हटाओ_rhash;
		पूर्ण
		err = -ENOENT;
		जाओ err_हटाओ_rhash;
	पूर्ण

	nfp_flow->meta.flow_version = cpu_to_be64(priv->flower_version);
	priv->flower_version++;

	/* Update flow payload with mask ids. */
	nfp_flow->unmasked_data[NFP_FL_MASK_ID_LOCATION] = new_mask_id;
	priv->stats[stats_cxt].pkts = 0;
	priv->stats[stats_cxt].bytes = 0;
	priv->stats[stats_cxt].used = jअगरfies;

	check_entry = nfp_flower_search_fl_table(app, flow->cookie, netdev);
	अगर (check_entry) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot offload duplicate flow entry");
		अगर (nfp_release_stats_entry(app, stats_cxt)) अणु
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot release stats context");
			err = -EINVAL;
			जाओ err_हटाओ_mask;
		पूर्ण

		अगर (!nfp_flow->pre_tun_rule.dev &&
		    !nfp_check_mask_हटाओ(app, nfp_flow->mask_data,
					   nfp_flow->meta.mask_len,
					   शून्य, &new_mask_id)) अणु
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot release mask id");
			err = -EINVAL;
			जाओ err_हटाओ_mask;
		पूर्ण

		err = -EEXIST;
		जाओ err_हटाओ_mask;
	पूर्ण

	वापस 0;

err_हटाओ_mask:
	अगर (!nfp_flow->pre_tun_rule.dev)
		nfp_check_mask_हटाओ(app, nfp_flow->mask_data,
				      nfp_flow->meta.mask_len,
				      शून्य, &new_mask_id);
err_हटाओ_rhash:
	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->stats_ctx_table,
					    &ctx_entry->ht_node,
					    stats_ctx_table_params));
err_मुक्त_ctx_entry:
	kमुक्त(ctx_entry);
err_release_stats:
	nfp_release_stats_entry(app, stats_cxt);

	वापस err;
पूर्ण

व्योम __nfp_modअगरy_flow_metadata(काष्ठा nfp_flower_priv *priv,
				काष्ठा nfp_fl_payload *nfp_flow)
अणु
	nfp_flow->meta.flags &= ~NFP_FL_META_FLAG_MANAGE_MASK;
	nfp_flow->meta.flow_version = cpu_to_be64(priv->flower_version);
	priv->flower_version++;
पूर्ण

पूर्णांक nfp_modअगरy_flow_metadata(काष्ठा nfp_app *app,
			     काष्ठा nfp_fl_payload *nfp_flow)
अणु
	काष्ठा nfp_fl_stats_ctx_to_flow *ctx_entry;
	काष्ठा nfp_flower_priv *priv = app->priv;
	u8 new_mask_id = 0;
	u32 temp_ctx_id;

	__nfp_modअगरy_flow_metadata(priv, nfp_flow);

	अगर (!nfp_flow->pre_tun_rule.dev)
		nfp_check_mask_हटाओ(app, nfp_flow->mask_data,
				      nfp_flow->meta.mask_len, &nfp_flow->meta.flags,
				      &new_mask_id);

	/* Update flow payload with mask ids. */
	nfp_flow->unmasked_data[NFP_FL_MASK_ID_LOCATION] = new_mask_id;

	/* Release the stats ctx id and ctx to flow table entry. */
	temp_ctx_id = be32_to_cpu(nfp_flow->meta.host_ctx_id);

	ctx_entry = rhashtable_lookup_fast(&priv->stats_ctx_table, &temp_ctx_id,
					   stats_ctx_table_params);
	अगर (!ctx_entry)
		वापस -ENOENT;

	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->stats_ctx_table,
					    &ctx_entry->ht_node,
					    stats_ctx_table_params));
	kमुक्त(ctx_entry);

	वापस nfp_release_stats_entry(app, temp_ctx_id);
पूर्ण

काष्ठा nfp_fl_payload *
nfp_flower_get_fl_payload_from_ctx(काष्ठा nfp_app *app, u32 ctx_id)
अणु
	काष्ठा nfp_fl_stats_ctx_to_flow *ctx_entry;
	काष्ठा nfp_flower_priv *priv = app->priv;

	ctx_entry = rhashtable_lookup_fast(&priv->stats_ctx_table, &ctx_id,
					   stats_ctx_table_params);
	अगर (!ctx_entry)
		वापस शून्य;

	वापस ctx_entry->flow;
पूर्ण

अटल पूर्णांक nfp_fl_obj_cmpfn(काष्ठा rhashtable_compare_arg *arg,
			    स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा nfp_fl_flow_table_cmp_arg *cmp_arg = arg->key;
	स्थिर काष्ठा nfp_fl_payload *flow_entry = obj;

	अगर (flow_entry->ingress_dev == cmp_arg->netdev)
		वापस flow_entry->tc_flower_cookie != cmp_arg->cookie;

	वापस 1;
पूर्ण

अटल u32 nfp_fl_obj_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा nfp_fl_payload *flower_entry = data;

	वापस jhash2((u32 *)&flower_entry->tc_flower_cookie,
		      माप(flower_entry->tc_flower_cookie) / माप(u32),
		      seed);
पूर्ण

अटल u32 nfp_fl_key_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा nfp_fl_flow_table_cmp_arg *cmp_arg = data;

	वापस jhash2((u32 *)&cmp_arg->cookie,
		      माप(cmp_arg->cookie) / माप(u32), seed);
पूर्ण

स्थिर काष्ठा rhashtable_params nfp_flower_table_params = अणु
	.head_offset		= दुरत्व(काष्ठा nfp_fl_payload, fl_node),
	.hashfn			= nfp_fl_key_hashfn,
	.obj_cmpfn		= nfp_fl_obj_cmpfn,
	.obj_hashfn		= nfp_fl_obj_hashfn,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

स्थिर काष्ठा rhashtable_params merge_table_params = अणु
	.key_offset	= दुरत्व(काष्ठा nfp_merge_info, parent_ctx),
	.head_offset	= दुरत्व(काष्ठा nfp_merge_info, ht_node),
	.key_len	= माप(u64),
पूर्ण;

पूर्णांक nfp_flower_metadata_init(काष्ठा nfp_app *app, u64 host_ctx_count,
			     अचिन्हित पूर्णांक host_num_mems)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	पूर्णांक err, stats_size;

	hash_init(priv->mask_table);

	err = rhashtable_init(&priv->flow_table, &nfp_flower_table_params);
	अगर (err)
		वापस err;

	err = rhashtable_init(&priv->stats_ctx_table, &stats_ctx_table_params);
	अगर (err)
		जाओ err_मुक्त_flow_table;

	err = rhashtable_init(&priv->merge_table, &merge_table_params);
	अगर (err)
		जाओ err_मुक्त_stats_ctx_table;

	get_अक्रमom_bytes(&priv->mask_id_seed, माप(priv->mask_id_seed));

	/* Init ring buffer and unallocated mask_ids. */
	priv->mask_ids.mask_id_मुक्त_list.buf =
		kदो_स्मृति_array(NFP_FLOWER_MASK_ENTRY_RS,
			      NFP_FLOWER_MASK_ELEMENT_RS, GFP_KERNEL);
	अगर (!priv->mask_ids.mask_id_मुक्त_list.buf)
		जाओ err_मुक्त_merge_table;

	priv->mask_ids.init_unallocated = NFP_FLOWER_MASK_ENTRY_RS - 1;

	/* Init बारtamps क्रम mask id*/
	priv->mask_ids.last_used =
		kदो_स्मृति_array(NFP_FLOWER_MASK_ENTRY_RS,
			      माप(*priv->mask_ids.last_used), GFP_KERNEL);
	अगर (!priv->mask_ids.last_used)
		जाओ err_मुक्त_mask_id;

	/* Init ring buffer and unallocated stats_ids. */
	priv->stats_ids.मुक्त_list.buf =
		vदो_स्मृति(array_size(NFP_FL_STATS_ELEM_RS,
				   priv->stats_ring_size));
	अगर (!priv->stats_ids.मुक्त_list.buf)
		जाओ err_मुक्त_last_used;

	priv->stats_ids.init_unalloc = भाग_u64(host_ctx_count, host_num_mems);

	stats_size = FIELD_PREP(NFP_FL_STAT_ID_STAT, host_ctx_count) |
		     FIELD_PREP(NFP_FL_STAT_ID_MU_NUM, host_num_mems - 1);
	priv->stats = kvदो_स्मृति_array(stats_size, माप(काष्ठा nfp_fl_stats),
				     GFP_KERNEL);
	अगर (!priv->stats)
		जाओ err_मुक्त_ring_buf;

	spin_lock_init(&priv->stats_lock);

	वापस 0;

err_मुक्त_ring_buf:
	vमुक्त(priv->stats_ids.मुक्त_list.buf);
err_मुक्त_last_used:
	kमुक्त(priv->mask_ids.last_used);
err_मुक्त_mask_id:
	kमुक्त(priv->mask_ids.mask_id_मुक्त_list.buf);
err_मुक्त_merge_table:
	rhashtable_destroy(&priv->merge_table);
err_मुक्त_stats_ctx_table:
	rhashtable_destroy(&priv->stats_ctx_table);
err_मुक्त_flow_table:
	rhashtable_destroy(&priv->flow_table);
	वापस -ENOMEM;
पूर्ण

व्योम nfp_flower_metadata_cleanup(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;

	अगर (!priv)
		वापस;

	rhashtable_मुक्त_and_destroy(&priv->flow_table,
				    nfp_check_rhashtable_empty, शून्य);
	rhashtable_मुक्त_and_destroy(&priv->stats_ctx_table,
				    nfp_check_rhashtable_empty, शून्य);
	rhashtable_मुक्त_and_destroy(&priv->merge_table,
				    nfp_check_rhashtable_empty, शून्य);
	kvमुक्त(priv->stats);
	kमुक्त(priv->mask_ids.mask_id_मुक्त_list.buf);
	kमुक्त(priv->mask_ids.last_used);
	vमुक्त(priv->stats_ids.मुक्त_list.buf);
पूर्ण
