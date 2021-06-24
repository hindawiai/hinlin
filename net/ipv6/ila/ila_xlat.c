<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/jhash.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/genetlink.h>
#समावेश <net/ila.h>
#समावेश <net/netns/generic.h>
#समावेश <uapi/linux/genetlink.h>
#समावेश "ila.h"

काष्ठा ila_xlat_params अणु
	काष्ठा ila_params ip;
	पूर्णांक अगरindex;
पूर्ण;

काष्ठा ila_map अणु
	काष्ठा ila_xlat_params xp;
	काष्ठा rhash_head node;
	काष्ठा ila_map __rcu *next;
	काष्ठा rcu_head rcu;
पूर्ण;

#घोषणा MAX_LOCKS 1024
#घोषणा	LOCKS_PER_CPU 10

अटल पूर्णांक alloc_ila_locks(काष्ठा ila_net *ilan)
अणु
	वापस alloc_bucket_spinlocks(&ilan->xlat.locks, &ilan->xlat.locks_mask,
				      MAX_LOCKS, LOCKS_PER_CPU,
				      GFP_KERNEL);
पूर्ण

अटल u32 hashrnd __पढ़ो_mostly;
अटल __always_अंतरभूत व्योम __ila_hash_secret_init(व्योम)
अणु
	net_get_अक्रमom_once(&hashrnd, माप(hashrnd));
पूर्ण

अटल अंतरभूत u32 ila_locator_hash(काष्ठा ila_locator loc)
अणु
	u32 *v = (u32 *)loc.v32;

	__ila_hash_secret_init();
	वापस jhash_2words(v[0], v[1], hashrnd);
पूर्ण

अटल अंतरभूत spinlock_t *ila_get_lock(काष्ठा ila_net *ilan,
				       काष्ठा ila_locator loc)
अणु
	वापस &ilan->xlat.locks[ila_locator_hash(loc) & ilan->xlat.locks_mask];
पूर्ण

अटल अंतरभूत पूर्णांक ila_cmp_wildcards(काष्ठा ila_map *ila,
				    काष्ठा ila_addr *iaddr, पूर्णांक अगरindex)
अणु
	वापस (ila->xp.अगरindex && ila->xp.अगरindex != अगरindex);
पूर्ण

अटल अंतरभूत पूर्णांक ila_cmp_params(काष्ठा ila_map *ila,
				 काष्ठा ila_xlat_params *xp)
अणु
	वापस (ila->xp.अगरindex != xp->अगरindex);
पूर्ण

अटल पूर्णांक ila_cmpfn(काष्ठा rhashtable_compare_arg *arg,
		     स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा ila_map *ila = obj;

	वापस (ila->xp.ip.locator_match.v64 != *(__be64 *)arg->key);
पूर्ण

अटल अंतरभूत पूर्णांक ila_order(काष्ठा ila_map *ila)
अणु
	पूर्णांक score = 0;

	अगर (ila->xp.अगरindex)
		score += 1 << 1;

	वापस score;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params rht_params = अणु
	.nelem_hपूर्णांक = 1024,
	.head_offset = दुरत्व(काष्ठा ila_map, node),
	.key_offset = दुरत्व(काष्ठा ila_map, xp.ip.locator_match),
	.key_len = माप(u64), /* identअगरier */
	.max_size = 1048576,
	.min_size = 256,
	.स्वतःmatic_shrinking = true,
	.obj_cmpfn = ila_cmpfn,
पूर्ण;

अटल पूर्णांक parse_nl_config(काष्ठा genl_info *info,
			   काष्ठा ila_xlat_params *xp)
अणु
	स_रखो(xp, 0, माप(*xp));

	अगर (info->attrs[ILA_ATTR_LOCATOR])
		xp->ip.locator.v64 = (__क्रमce __be64)nla_get_u64(
			info->attrs[ILA_ATTR_LOCATOR]);

	अगर (info->attrs[ILA_ATTR_LOCATOR_MATCH])
		xp->ip.locator_match.v64 = (__क्रमce __be64)nla_get_u64(
			info->attrs[ILA_ATTR_LOCATOR_MATCH]);

	अगर (info->attrs[ILA_ATTR_CSUM_MODE])
		xp->ip.csum_mode = nla_get_u8(info->attrs[ILA_ATTR_CSUM_MODE]);
	अन्यथा
		xp->ip.csum_mode = ILA_CSUM_NO_ACTION;

	अगर (info->attrs[ILA_ATTR_IDENT_TYPE])
		xp->ip.ident_type = nla_get_u8(
				info->attrs[ILA_ATTR_IDENT_TYPE]);
	अन्यथा
		xp->ip.ident_type = ILA_ATYPE_USE_FORMAT;

	अगर (info->attrs[ILA_ATTR_IFINDEX])
		xp->अगरindex = nla_get_s32(info->attrs[ILA_ATTR_IFINDEX]);

	वापस 0;
पूर्ण

/* Must be called with rcu पढ़ोlock */
अटल अंतरभूत काष्ठा ila_map *ila_lookup_wildcards(काष्ठा ila_addr *iaddr,
						   पूर्णांक अगरindex,
						   काष्ठा ila_net *ilan)
अणु
	काष्ठा ila_map *ila;

	ila = rhashtable_lookup_fast(&ilan->xlat.rhash_table, &iaddr->loc,
				     rht_params);
	जबतक (ila) अणु
		अगर (!ila_cmp_wildcards(ila, iaddr, अगरindex))
			वापस ila;
		ila = rcu_access_poपूर्णांकer(ila->next);
	पूर्ण

	वापस शून्य;
पूर्ण

/* Must be called with rcu पढ़ोlock */
अटल अंतरभूत काष्ठा ila_map *ila_lookup_by_params(काष्ठा ila_xlat_params *xp,
						   काष्ठा ila_net *ilan)
अणु
	काष्ठा ila_map *ila;

	ila = rhashtable_lookup_fast(&ilan->xlat.rhash_table,
				     &xp->ip.locator_match,
				     rht_params);
	जबतक (ila) अणु
		अगर (!ila_cmp_params(ila, xp))
			वापस ila;
		ila = rcu_access_poपूर्णांकer(ila->next);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम ila_release(काष्ठा ila_map *ila)
अणु
	kमुक्त_rcu(ila, rcu);
पूर्ण

अटल व्योम ila_मुक्त_node(काष्ठा ila_map *ila)
अणु
	काष्ठा ila_map *next;

	/* Assume rcu_पढ़ोlock held */
	जबतक (ila) अणु
		next = rcu_access_poपूर्णांकer(ila->next);
		ila_release(ila);
		ila = next;
	पूर्ण
पूर्ण

अटल व्योम ila_मुक्त_cb(व्योम *ptr, व्योम *arg)
अणु
	ila_मुक्त_node((काष्ठा ila_map *)ptr);
पूर्ण

अटल पूर्णांक ila_xlat_addr(काष्ठा sk_buff *skb, bool sir2ila);

अटल अचिन्हित पूर्णांक
ila_nf_input(व्योम *priv,
	     काष्ठा sk_buff *skb,
	     स्थिर काष्ठा nf_hook_state *state)
अणु
	ila_xlat_addr(skb, false);
	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ila_nf_hook_ops[] = अणु
	अणु
		.hook = ila_nf_input,
		.pf = NFPROTO_IPV6,
		.hooknum = NF_INET_PRE_ROUTING,
		.priority = -1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ila_add_mapping(काष्ठा net *net, काष्ठा ila_xlat_params *xp)
अणु
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);
	काष्ठा ila_map *ila, *head;
	spinlock_t *lock = ila_get_lock(ilan, xp->ip.locator_match);
	पूर्णांक err = 0, order;

	अगर (!ilan->xlat.hooks_रेजिस्टरed) अणु
		/* We defer रेजिस्टरing net hooks in the namespace until the
		 * first mapping is added.
		 */
		err = nf_रेजिस्टर_net_hooks(net, ila_nf_hook_ops,
					    ARRAY_SIZE(ila_nf_hook_ops));
		अगर (err)
			वापस err;

		ilan->xlat.hooks_रेजिस्टरed = true;
	पूर्ण

	ila = kzalloc(माप(*ila), GFP_KERNEL);
	अगर (!ila)
		वापस -ENOMEM;

	ila_init_saved_csum(&xp->ip);

	ila->xp = *xp;

	order = ila_order(ila);

	spin_lock(lock);

	head = rhashtable_lookup_fast(&ilan->xlat.rhash_table,
				      &xp->ip.locator_match,
				      rht_params);
	अगर (!head) अणु
		/* New entry क्रम the rhash_table */
		err = rhashtable_lookup_insert_fast(&ilan->xlat.rhash_table,
						    &ila->node, rht_params);
	पूर्ण अन्यथा अणु
		काष्ठा ila_map *tila = head, *prev = शून्य;

		करो अणु
			अगर (!ila_cmp_params(tila, xp)) अणु
				err = -EEXIST;
				जाओ out;
			पूर्ण

			अगर (order > ila_order(tila))
				अवरोध;

			prev = tila;
			tila = rcu_dereference_रक्षित(tila->next,
				lockdep_is_held(lock));
		पूर्ण जबतक (tila);

		अगर (prev) अणु
			/* Insert in sub list of head */
			RCU_INIT_POINTER(ila->next, tila);
			rcu_assign_poपूर्णांकer(prev->next, ila);
		पूर्ण अन्यथा अणु
			/* Make this ila new head */
			RCU_INIT_POINTER(ila->next, head);
			err = rhashtable_replace_fast(&ilan->xlat.rhash_table,
						      &head->node,
						      &ila->node, rht_params);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock(lock);

	अगर (err)
		kमुक्त(ila);

	वापस err;
पूर्ण

अटल पूर्णांक ila_del_mapping(काष्ठा net *net, काष्ठा ila_xlat_params *xp)
अणु
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);
	काष्ठा ila_map *ila, *head, *prev;
	spinlock_t *lock = ila_get_lock(ilan, xp->ip.locator_match);
	पूर्णांक err = -ENOENT;

	spin_lock(lock);

	head = rhashtable_lookup_fast(&ilan->xlat.rhash_table,
				      &xp->ip.locator_match, rht_params);
	ila = head;

	prev = शून्य;

	जबतक (ila) अणु
		अगर (ila_cmp_params(ila, xp)) अणु
			prev = ila;
			ila = rcu_dereference_रक्षित(ila->next,
							lockdep_is_held(lock));
			जारी;
		पूर्ण

		err = 0;

		अगर (prev) अणु
			/* Not head, just delete from list */
			rcu_assign_poपूर्णांकer(prev->next, ila->next);
		पूर्ण अन्यथा अणु
			/* It is the head. If there is something in the
			 * sublist we need to make a new head.
			 */
			head = rcu_dereference_रक्षित(ila->next,
							 lockdep_is_held(lock));
			अगर (head) अणु
				/* Put first entry in the sublist पूर्णांकo the
				 * table
				 */
				err = rhashtable_replace_fast(
					&ilan->xlat.rhash_table, &ila->node,
					&head->node, rht_params);
				अगर (err)
					जाओ out;
			पूर्ण अन्यथा अणु
				/* Entry no दीर्घer used */
				err = rhashtable_हटाओ_fast(
						&ilan->xlat.rhash_table,
						&ila->node, rht_params);
			पूर्ण
		पूर्ण

		ila_release(ila);

		अवरोध;
	पूर्ण

out:
	spin_unlock(lock);

	वापस err;
पूर्ण

पूर्णांक ila_xlat_nl_cmd_add_mapping(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा ila_xlat_params p;
	पूर्णांक err;

	err = parse_nl_config(info, &p);
	अगर (err)
		वापस err;

	वापस ila_add_mapping(net, &p);
पूर्ण

पूर्णांक ila_xlat_nl_cmd_del_mapping(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा ila_xlat_params xp;
	पूर्णांक err;

	err = parse_nl_config(info, &xp);
	अगर (err)
		वापस err;

	ila_del_mapping(net, &xp);

	वापस 0;
पूर्ण

अटल अंतरभूत spinlock_t *lock_from_ila_map(काष्ठा ila_net *ilan,
					    काष्ठा ila_map *ila)
अणु
	वापस ila_get_lock(ilan, ila->xp.ip.locator_match);
पूर्ण

पूर्णांक ila_xlat_nl_cmd_flush(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);
	काष्ठा rhashtable_iter iter;
	काष्ठा ila_map *ila;
	spinlock_t *lock;
	पूर्णांक ret = 0;

	rhashtable_walk_enter(&ilan->xlat.rhash_table, &iter);
	rhashtable_walk_start(&iter);

	क्रम (;;) अणु
		ila = rhashtable_walk_next(&iter);

		अगर (IS_ERR(ila)) अणु
			अगर (PTR_ERR(ila) == -EAGAIN)
				जारी;
			ret = PTR_ERR(ila);
			जाओ करोne;
		पूर्ण अन्यथा अगर (!ila) अणु
			अवरोध;
		पूर्ण

		lock = lock_from_ila_map(ilan, ila);

		spin_lock(lock);

		ret = rhashtable_हटाओ_fast(&ilan->xlat.rhash_table,
					     &ila->node, rht_params);
		अगर (!ret)
			ila_मुक्त_node(ila);

		spin_unlock(lock);

		अगर (ret)
			अवरोध;
	पूर्ण

करोne:
	rhashtable_walk_stop(&iter);
	rhashtable_walk_निकास(&iter);
	वापस ret;
पूर्ण

अटल पूर्णांक ila_fill_info(काष्ठा ila_map *ila, काष्ठा sk_buff *msg)
अणु
	अगर (nla_put_u64_64bit(msg, ILA_ATTR_LOCATOR,
			      (__क्रमce u64)ila->xp.ip.locator.v64,
			      ILA_ATTR_PAD) ||
	    nla_put_u64_64bit(msg, ILA_ATTR_LOCATOR_MATCH,
			      (__क्रमce u64)ila->xp.ip.locator_match.v64,
			      ILA_ATTR_PAD) ||
	    nla_put_s32(msg, ILA_ATTR_IFINDEX, ila->xp.अगरindex) ||
	    nla_put_u8(msg, ILA_ATTR_CSUM_MODE, ila->xp.ip.csum_mode) ||
	    nla_put_u8(msg, ILA_ATTR_IDENT_TYPE, ila->xp.ip.ident_type))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक ila_dump_info(काष्ठा ila_map *ila,
			 u32 portid, u32 seq, u32 flags,
			 काष्ठा sk_buff *skb, u8 cmd)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, portid, seq, &ila_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -ENOMEM;

	अगर (ila_fill_info(ila, skb) < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक ila_xlat_nl_cmd_get_mapping(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);
	काष्ठा sk_buff *msg;
	काष्ठा ila_xlat_params xp;
	काष्ठा ila_map *ila;
	पूर्णांक ret;

	ret = parse_nl_config(info, &xp);
	अगर (ret)
		वापस ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	rcu_पढ़ो_lock();

	ila = ila_lookup_by_params(&xp, ilan);
	अगर (ila) अणु
		ret = ila_dump_info(ila,
				    info->snd_portid,
				    info->snd_seq, 0, msg,
				    info->genlhdr->cmd);
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (ret < 0)
		जाओ out_मुक्त;

	वापस genlmsg_reply(msg, info);

out_मुक्त:
	nlmsg_मुक्त(msg);
	वापस ret;
पूर्ण

काष्ठा ila_dump_iter अणु
	काष्ठा rhashtable_iter rhiter;
	पूर्णांक skip;
पूर्ण;

पूर्णांक ila_xlat_nl_dump_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);
	काष्ठा ila_dump_iter *iter;

	iter = kदो_स्मृति(माप(*iter), GFP_KERNEL);
	अगर (!iter)
		वापस -ENOMEM;

	rhashtable_walk_enter(&ilan->xlat.rhash_table, &iter->rhiter);

	iter->skip = 0;
	cb->args[0] = (दीर्घ)iter;

	वापस 0;
पूर्ण

पूर्णांक ila_xlat_nl_dump_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा ila_dump_iter *iter = (काष्ठा ila_dump_iter *)cb->args[0];

	rhashtable_walk_निकास(&iter->rhiter);

	kमुक्त(iter);

	वापस 0;
पूर्ण

पूर्णांक ila_xlat_nl_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा ila_dump_iter *iter = (काष्ठा ila_dump_iter *)cb->args[0];
	काष्ठा rhashtable_iter *rhiter = &iter->rhiter;
	पूर्णांक skip = iter->skip;
	काष्ठा ila_map *ila;
	पूर्णांक ret;

	rhashtable_walk_start(rhiter);

	/* Get first entry */
	ila = rhashtable_walk_peek(rhiter);

	अगर (ila && !IS_ERR(ila) && skip) अणु
		/* Skip over visited entries */

		जबतक (ila && skip) अणु
			/* Skip over any ila entries in this list that we
			 * have alपढ़ोy dumped.
			 */
			ila = rcu_access_poपूर्णांकer(ila->next);
			skip--;
		पूर्ण
	पूर्ण

	skip = 0;

	क्रम (;;) अणु
		अगर (IS_ERR(ila)) अणु
			ret = PTR_ERR(ila);
			अगर (ret == -EAGAIN) अणु
				/* Table has changed and iter has reset. Return
				 * -EAGAIN to the application even अगर we have
				 * written data to the skb. The application
				 * needs to deal with this.
				 */

				जाओ out_ret;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (!ila) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		जबतक (ila) अणु
			ret =  ila_dump_info(ila, NETLINK_CB(cb->skb).portid,
					     cb->nlh->nlmsg_seq, NLM_F_MULTI,
					     skb, ILA_CMD_GET);
			अगर (ret)
				जाओ out;

			skip++;
			ila = rcu_access_poपूर्णांकer(ila->next);
		पूर्ण

		skip = 0;
		ila = rhashtable_walk_next(rhiter);
	पूर्ण

out:
	iter->skip = skip;
	ret = (skb->len ? : ret);

out_ret:
	rhashtable_walk_stop(rhiter);
	वापस ret;
पूर्ण

पूर्णांक ila_xlat_init_net(काष्ठा net *net)
अणु
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);
	पूर्णांक err;

	err = alloc_ila_locks(ilan);
	अगर (err)
		वापस err;

	rhashtable_init(&ilan->xlat.rhash_table, &rht_params);

	वापस 0;
पूर्ण

व्योम ila_xlat_निकास_net(काष्ठा net *net)
अणु
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);

	rhashtable_मुक्त_and_destroy(&ilan->xlat.rhash_table, ila_मुक्त_cb, शून्य);

	मुक्त_bucket_spinlocks(ilan->xlat.locks);

	अगर (ilan->xlat.hooks_रेजिस्टरed)
		nf_unरेजिस्टर_net_hooks(net, ila_nf_hook_ops,
					ARRAY_SIZE(ila_nf_hook_ops));
पूर्ण

अटल पूर्णांक ila_xlat_addr(काष्ठा sk_buff *skb, bool sir2ila)
अणु
	काष्ठा ila_map *ila;
	काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ila_net *ilan = net_generic(net, ila_net_id);
	काष्ठा ila_addr *iaddr = ila_a2i(&ip6h->daddr);

	/* Assumes skb contains a valid IPv6 header that is pulled */

	/* No check here that ILA type in the mapping matches what is in the
	 * address. We assume that whatever sender gaves us can be translated.
	 * The checksum mode however is relevant.
	 */

	rcu_पढ़ो_lock();

	ila = ila_lookup_wildcards(iaddr, skb->dev->अगरindex, ilan);
	अगर (ila)
		ila_update_ipv6_locator(skb, &ila->xp.ip, sir2ila);

	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
