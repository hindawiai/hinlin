<शैली गुरु>
/* Linux multicast routing support
 * Common logic shared by IPv4 [ipmr] and IPv6 [ip6mr] implementation
 */

#समावेश <linux/rhashtable.h>
#समावेश <linux/mroute_base.h>

/* Sets everything common except 'dev', since that is करोne under locking */
व्योम vअगर_device_init(काष्ठा vअगर_device *v,
		     काष्ठा net_device *dev,
		     अचिन्हित दीर्घ rate_limit,
		     अचिन्हित अक्षर threshold,
		     अचिन्हित लघु flags,
		     अचिन्हित लघु get_अगरlink_mask)
अणु
	v->dev = शून्य;
	v->bytes_in = 0;
	v->bytes_out = 0;
	v->pkt_in = 0;
	v->pkt_out = 0;
	v->rate_limit = rate_limit;
	v->flags = flags;
	v->threshold = threshold;
	अगर (v->flags & get_अगरlink_mask)
		v->link = dev_get_अगरlink(dev);
	अन्यथा
		v->link = dev->अगरindex;
पूर्ण
EXPORT_SYMBOL(vअगर_device_init);

काष्ठा mr_table *
mr_table_alloc(काष्ठा net *net, u32 id,
	       काष्ठा mr_table_ops *ops,
	       व्योम (*expire_func)(काष्ठा समयr_list *t),
	       व्योम (*table_set)(काष्ठा mr_table *mrt,
				 काष्ठा net *net))
अणु
	काष्ठा mr_table *mrt;
	पूर्णांक err;

	mrt = kzalloc(माप(*mrt), GFP_KERNEL);
	अगर (!mrt)
		वापस ERR_PTR(-ENOMEM);
	mrt->id = id;
	ग_लिखो_pnet(&mrt->net, net);

	mrt->ops = *ops;
	err = rhltable_init(&mrt->mfc_hash, mrt->ops.rht_params);
	अगर (err) अणु
		kमुक्त(mrt);
		वापस ERR_PTR(err);
	पूर्ण
	INIT_LIST_HEAD(&mrt->mfc_cache_list);
	INIT_LIST_HEAD(&mrt->mfc_unres_queue);

	समयr_setup(&mrt->ipmr_expire_समयr, expire_func, 0);

	mrt->mroute_reg_vअगर_num = -1;
	table_set(mrt, net);
	वापस mrt;
पूर्ण
EXPORT_SYMBOL(mr_table_alloc);

व्योम *mr_mfc_find_parent(काष्ठा mr_table *mrt, व्योम *hasharg, पूर्णांक parent)
अणु
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा mr_mfc *c;

	list = rhltable_lookup(&mrt->mfc_hash, hasharg, *mrt->ops.rht_params);
	rhl_क्रम_each_entry_rcu(c, पंचांगp, list, mnode)
		अगर (parent == -1 || parent == c->mfc_parent)
			वापस c;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mr_mfc_find_parent);

व्योम *mr_mfc_find_any_parent(काष्ठा mr_table *mrt, पूर्णांक vअगरi)
अणु
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा mr_mfc *c;

	list = rhltable_lookup(&mrt->mfc_hash, mrt->ops.cmparg_any,
			       *mrt->ops.rht_params);
	rhl_क्रम_each_entry_rcu(c, पंचांगp, list, mnode)
		अगर (c->mfc_un.res.ttls[vअगरi] < 255)
			वापस c;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mr_mfc_find_any_parent);

व्योम *mr_mfc_find_any(काष्ठा mr_table *mrt, पूर्णांक vअगरi, व्योम *hasharg)
अणु
	काष्ठा rhlist_head *पंचांगp, *list;
	काष्ठा mr_mfc *c, *proxy;

	list = rhltable_lookup(&mrt->mfc_hash, hasharg, *mrt->ops.rht_params);
	rhl_क्रम_each_entry_rcu(c, पंचांगp, list, mnode) अणु
		अगर (c->mfc_un.res.ttls[vअगरi] < 255)
			वापस c;

		/* It's ok अगर the vअगरi is part of the अटल tree */
		proxy = mr_mfc_find_any_parent(mrt, c->mfc_parent);
		अगर (proxy && proxy->mfc_un.res.ttls[vअगरi] < 255)
			वापस c;
	पूर्ण

	वापस mr_mfc_find_any_parent(mrt, vअगरi);
पूर्ण
EXPORT_SYMBOL(mr_mfc_find_any);

#अगर_घोषित CONFIG_PROC_FS
व्योम *mr_vअगर_seq_idx(काष्ठा net *net, काष्ठा mr_vअगर_iter *iter, loff_t pos)
अणु
	काष्ठा mr_table *mrt = iter->mrt;

	क्रम (iter->ct = 0; iter->ct < mrt->maxvअगर; ++iter->ct) अणु
		अगर (!VIF_EXISTS(mrt, iter->ct))
			जारी;
		अगर (pos-- == 0)
			वापस &mrt->vअगर_table[iter->ct];
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mr_vअगर_seq_idx);

व्योम *mr_vअगर_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा mr_vअगर_iter *iter = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा mr_table *mrt = iter->mrt;

	++*pos;
	अगर (v == SEQ_START_TOKEN)
		वापस mr_vअगर_seq_idx(net, iter, 0);

	जबतक (++iter->ct < mrt->maxvअगर) अणु
		अगर (!VIF_EXISTS(mrt, iter->ct))
			जारी;
		वापस &mrt->vअगर_table[iter->ct];
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mr_vअगर_seq_next);

व्योम *mr_mfc_seq_idx(काष्ठा net *net,
		     काष्ठा mr_mfc_iter *it, loff_t pos)
अणु
	काष्ठा mr_table *mrt = it->mrt;
	काष्ठा mr_mfc *mfc;

	rcu_पढ़ो_lock();
	it->cache = &mrt->mfc_cache_list;
	list_क्रम_each_entry_rcu(mfc, &mrt->mfc_cache_list, list)
		अगर (pos-- == 0)
			वापस mfc;
	rcu_पढ़ो_unlock();

	spin_lock_bh(it->lock);
	it->cache = &mrt->mfc_unres_queue;
	list_क्रम_each_entry(mfc, it->cache, list)
		अगर (pos-- == 0)
			वापस mfc;
	spin_unlock_bh(it->lock);

	it->cache = शून्य;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mr_mfc_seq_idx);

व्योम *mr_mfc_seq_next(काष्ठा seq_file *seq, व्योम *v,
		      loff_t *pos)
अणु
	काष्ठा mr_mfc_iter *it = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा mr_table *mrt = it->mrt;
	काष्ठा mr_mfc *c = v;

	++*pos;

	अगर (v == SEQ_START_TOKEN)
		वापस mr_mfc_seq_idx(net, seq->निजी, 0);

	अगर (c->list.next != it->cache)
		वापस list_entry(c->list.next, काष्ठा mr_mfc, list);

	अगर (it->cache == &mrt->mfc_unres_queue)
		जाओ end_of_list;

	/* exhausted cache_array, show unresolved */
	rcu_पढ़ो_unlock();
	it->cache = &mrt->mfc_unres_queue;

	spin_lock_bh(it->lock);
	अगर (!list_empty(it->cache))
		वापस list_first_entry(it->cache, काष्ठा mr_mfc, list);

end_of_list:
	spin_unlock_bh(it->lock);
	it->cache = शून्य;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mr_mfc_seq_next);
#पूर्ण_अगर

पूर्णांक mr_fill_mroute(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
		   काष्ठा mr_mfc *c, काष्ठा rपंचांगsg *rपंचांग)
अणु
	काष्ठा rta_mfc_stats mfcs;
	काष्ठा nlattr *mp_attr;
	काष्ठा rtnexthop *nhp;
	अचिन्हित दीर्घ lastuse;
	पूर्णांक ct;

	/* If cache is unresolved, करोn't try to parse IIF and OIF */
	अगर (c->mfc_parent >= MAXVIFS) अणु
		rपंचांग->rपंचांग_flags |= RTNH_F_UNRESOLVED;
		वापस -ENOENT;
	पूर्ण

	अगर (VIF_EXISTS(mrt, c->mfc_parent) &&
	    nla_put_u32(skb, RTA_IIF,
			mrt->vअगर_table[c->mfc_parent].dev->अगरindex) < 0)
		वापस -EMSGSIZE;

	अगर (c->mfc_flags & MFC_OFFLOAD)
		rपंचांग->rपंचांग_flags |= RTNH_F_OFFLOAD;

	mp_attr = nla_nest_start_noflag(skb, RTA_MULTIPATH);
	अगर (!mp_attr)
		वापस -EMSGSIZE;

	क्रम (ct = c->mfc_un.res.minvअगर; ct < c->mfc_un.res.maxvअगर; ct++) अणु
		अगर (VIF_EXISTS(mrt, ct) && c->mfc_un.res.ttls[ct] < 255) अणु
			काष्ठा vअगर_device *vअगर;

			nhp = nla_reserve_nohdr(skb, माप(*nhp));
			अगर (!nhp) अणु
				nla_nest_cancel(skb, mp_attr);
				वापस -EMSGSIZE;
			पूर्ण

			nhp->rtnh_flags = 0;
			nhp->rtnh_hops = c->mfc_un.res.ttls[ct];
			vअगर = &mrt->vअगर_table[ct];
			nhp->rtnh_अगरindex = vअगर->dev->अगरindex;
			nhp->rtnh_len = माप(*nhp);
		पूर्ण
	पूर्ण

	nla_nest_end(skb, mp_attr);

	lastuse = READ_ONCE(c->mfc_un.res.lastuse);
	lastuse = समय_after_eq(jअगरfies, lastuse) ? jअगरfies - lastuse : 0;

	mfcs.mfcs_packets = c->mfc_un.res.pkt;
	mfcs.mfcs_bytes = c->mfc_un.res.bytes;
	mfcs.mfcs_wrong_अगर = c->mfc_un.res.wrong_अगर;
	अगर (nla_put_64bit(skb, RTA_MFC_STATS, माप(mfcs), &mfcs, RTA_PAD) ||
	    nla_put_u64_64bit(skb, RTA_EXPIRES, jअगरfies_to_घड़ी_प्रकार(lastuse),
			      RTA_PAD))
		वापस -EMSGSIZE;

	rपंचांग->rपंचांग_type = RTN_MULTICAST;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(mr_fill_mroute);

अटल bool mr_mfc_uses_dev(स्थिर काष्ठा mr_table *mrt,
			    स्थिर काष्ठा mr_mfc *c,
			    स्थिर काष्ठा net_device *dev)
अणु
	पूर्णांक ct;

	क्रम (ct = c->mfc_un.res.minvअगर; ct < c->mfc_un.res.maxvअगर; ct++) अणु
		अगर (VIF_EXISTS(mrt, ct) && c->mfc_un.res.ttls[ct] < 255) अणु
			स्थिर काष्ठा vअगर_device *vअगर;

			vअगर = &mrt->vअगर_table[ct];
			अगर (vअगर->dev == dev)
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक mr_table_dump(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
		  काष्ठा netlink_callback *cb,
		  पूर्णांक (*fill)(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
			      u32 portid, u32 seq, काष्ठा mr_mfc *c,
			      पूर्णांक cmd, पूर्णांक flags),
		  spinlock_t *lock, काष्ठा fib_dump_filter *filter)
अणु
	अचिन्हित पूर्णांक e = 0, s_e = cb->args[1];
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;
	काष्ठा mr_mfc *mfc;
	पूर्णांक err;

	अगर (filter->filter_set)
		flags |= NLM_F_DUMP_FILTERED;

	list_क्रम_each_entry_rcu(mfc, &mrt->mfc_cache_list, list) अणु
		अगर (e < s_e)
			जाओ next_entry;
		अगर (filter->dev &&
		    !mr_mfc_uses_dev(mrt, mfc, filter->dev))
			जाओ next_entry;

		err = fill(mrt, skb, NETLINK_CB(cb->skb).portid,
			   cb->nlh->nlmsg_seq, mfc, RTM_NEWROUTE, flags);
		अगर (err < 0)
			जाओ out;
next_entry:
		e++;
	पूर्ण

	spin_lock_bh(lock);
	list_क्रम_each_entry(mfc, &mrt->mfc_unres_queue, list) अणु
		अगर (e < s_e)
			जाओ next_entry2;
		अगर (filter->dev &&
		    !mr_mfc_uses_dev(mrt, mfc, filter->dev))
			जाओ next_entry2;

		err = fill(mrt, skb, NETLINK_CB(cb->skb).portid,
			   cb->nlh->nlmsg_seq, mfc, RTM_NEWROUTE, flags);
		अगर (err < 0) अणु
			spin_unlock_bh(lock);
			जाओ out;
		पूर्ण
next_entry2:
		e++;
	पूर्ण
	spin_unlock_bh(lock);
	err = 0;
out:
	cb->args[1] = e;
	वापस err;
पूर्ण
EXPORT_SYMBOL(mr_table_dump);

पूर्णांक mr_rपंचांग_dumproute(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		     काष्ठा mr_table *(*iter)(काष्ठा net *net,
					      काष्ठा mr_table *mrt),
		     पूर्णांक (*fill)(काष्ठा mr_table *mrt,
				 काष्ठा sk_buff *skb,
				 u32 portid, u32 seq, काष्ठा mr_mfc *c,
				 पूर्णांक cmd, पूर्णांक flags),
		     spinlock_t *lock, काष्ठा fib_dump_filter *filter)
अणु
	अचिन्हित पूर्णांक t = 0, s_t = cb->args[0];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा mr_table *mrt;
	पूर्णांक err;

	/* multicast करोes not track protocol or have route type other
	 * than RTN_MULTICAST
	 */
	अगर (filter->filter_set) अणु
		अगर (filter->protocol || filter->flags ||
		    (filter->rt_type && filter->rt_type != RTN_MULTICAST))
			वापस skb->len;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (mrt = iter(net, शून्य); mrt; mrt = iter(net, mrt)) अणु
		अगर (t < s_t)
			जाओ next_table;

		err = mr_table_dump(mrt, skb, cb, fill, lock, filter);
		अगर (err < 0)
			अवरोध;
		cb->args[1] = 0;
next_table:
		t++;
	पूर्ण
	rcu_पढ़ो_unlock();

	cb->args[0] = t;

	वापस skb->len;
पूर्ण
EXPORT_SYMBOL(mr_rपंचांग_dumproute);

पूर्णांक mr_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb, अचिन्हित लघु family,
	    पूर्णांक (*rules_dump)(काष्ठा net *net,
			      काष्ठा notअगरier_block *nb,
			      काष्ठा netlink_ext_ack *extack),
	    काष्ठा mr_table *(*mr_iter)(काष्ठा net *net,
					काष्ठा mr_table *mrt),
	    rwlock_t *mrt_lock,
	    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mr_table *mrt;
	पूर्णांक err;

	err = rules_dump(net, nb, extack);
	अगर (err)
		वापस err;

	क्रम (mrt = mr_iter(net, शून्य); mrt; mrt = mr_iter(net, mrt)) अणु
		काष्ठा vअगर_device *v = &mrt->vअगर_table[0];
		काष्ठा mr_mfc *mfc;
		पूर्णांक vअगरi;

		/* Notअगरiy on table VIF entries */
		पढ़ो_lock(mrt_lock);
		क्रम (vअगरi = 0; vअगरi < mrt->maxvअगर; vअगरi++, v++) अणु
			अगर (!v->dev)
				जारी;

			err = mr_call_vअगर_notअगरier(nb, family,
						   FIB_EVENT_VIF_ADD,
						   v, vअगरi, mrt->id, extack);
			अगर (err)
				अवरोध;
		पूर्ण
		पढ़ो_unlock(mrt_lock);

		अगर (err)
			वापस err;

		/* Notअगरy on table MFC entries */
		list_क्रम_each_entry_rcu(mfc, &mrt->mfc_cache_list, list) अणु
			err = mr_call_mfc_notअगरier(nb, family,
						   FIB_EVENT_ENTRY_ADD,
						   mfc, mrt->id, extack);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mr_dump);
