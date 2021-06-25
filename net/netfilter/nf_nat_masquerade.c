<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/netfilter/nf_nat_masquerade.h>

अटल DEFINE_MUTEX(masq_mutex);
अटल अचिन्हित पूर्णांक masq_refcnt __पढ़ो_mostly;

अचिन्हित पूर्णांक
nf_nat_masquerade_ipv4(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hooknum,
		       स्थिर काष्ठा nf_nat_range2 *range,
		       स्थिर काष्ठा net_device *out)
अणु
	काष्ठा nf_conn *ct;
	काष्ठा nf_conn_nat *nat;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_nat_range2 newrange;
	स्थिर काष्ठा rtable *rt;
	__be32 newsrc, nh;

	WARN_ON(hooknum != NF_INET_POST_ROUTING);

	ct = nf_ct_get(skb, &ctinfo);

	WARN_ON(!(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
			 ctinfo == IP_CT_RELATED_REPLY)));

	/* Source address is 0.0.0.0 - locally generated packet that is
	 * probably not supposed to be masqueraded.
	 */
	अगर (ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3.ip == 0)
		वापस NF_ACCEPT;

	rt = skb_rtable(skb);
	nh = rt_nexthop(rt, ip_hdr(skb)->daddr);
	newsrc = inet_select_addr(out, nh, RT_SCOPE_UNIVERSE);
	अगर (!newsrc) अणु
		pr_info("%s ate my IP address\n", out->name);
		वापस NF_DROP;
	पूर्ण

	nat = nf_ct_nat_ext_add(ct);
	अगर (nat)
		nat->masq_index = out->अगरindex;

	/* Transfer from original range. */
	स_रखो(&newrange.min_addr, 0, माप(newrange.min_addr));
	स_रखो(&newrange.max_addr, 0, माप(newrange.max_addr));
	newrange.flags       = range->flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr.ip = newsrc;
	newrange.max_addr.ip = newsrc;
	newrange.min_proto   = range->min_proto;
	newrange.max_proto   = range->max_proto;

	/* Hand modअगरied range to generic setup. */
	वापस nf_nat_setup_info(ct, &newrange, NF_NAT_MANIP_SRC);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_masquerade_ipv4);

अटल पूर्णांक device_cmp(काष्ठा nf_conn *i, व्योम *अगरindex)
अणु
	स्थिर काष्ठा nf_conn_nat *nat = nfct_nat(i);

	अगर (!nat)
		वापस 0;
	वापस nat->masq_index == (पूर्णांक)(दीर्घ)अगरindex;
पूर्ण

अटल पूर्णांक masq_device_event(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	स्थिर काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);

	अगर (event == NETDEV_DOWN) अणु
		/* Device was करोwned.  Search entire table क्रम
		 * conntracks which were associated with that device,
		 * and क्रमget them.
		 */

		nf_ct_iterate_cleanup_net(net, device_cmp,
					  (व्योम *)(दीर्घ)dev->अगरindex, 0, 0);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक inet_cmp(काष्ठा nf_conn *ct, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;
	काष्ठा net_device *dev = अगरa->अगरa_dev->dev;
	काष्ठा nf_conntrack_tuple *tuple;

	अगर (!device_cmp(ct, (व्योम *)(दीर्घ)dev->अगरindex))
		वापस 0;

	tuple = &ct->tuplehash[IP_CT_सूची_REPLY].tuple;

	वापस अगरa->अगरa_address == tuple->dst.u3.ip;
पूर्ण

अटल पूर्णांक masq_inet_event(काष्ठा notअगरier_block *this,
			   अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा in_device *idev = ((काष्ठा in_अगरaddr *)ptr)->अगरa_dev;
	काष्ठा net *net = dev_net(idev->dev);

	/* The masq_dev_notअगरier will catch the हाल of the device going
	 * करोwn.  So अगर the inetdev is dead and being destroyed we have
	 * no work to करो.  Otherwise this is an inभागidual address removal
	 * and we have to perक्रमm the flush.
	 */
	अगर (idev->dead)
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_DOWN)
		nf_ct_iterate_cleanup_net(net, inet_cmp, ptr, 0, 0);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block masq_dev_notअगरier = अणु
	.notअगरier_call	= masq_device_event,
पूर्ण;

अटल काष्ठा notअगरier_block masq_inet_notअगरier = अणु
	.notअगरier_call	= masq_inet_event,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल atomic_t v6_worker_count __पढ़ो_mostly;

अटल पूर्णांक
nat_ipv6_dev_get_saddr(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
		       स्थिर काष्ठा in6_addr *daddr, अचिन्हित पूर्णांक srcprefs,
		       काष्ठा in6_addr *saddr)
अणु
#अगर_घोषित CONFIG_IPV6_MODULE
	स्थिर काष्ठा nf_ipv6_ops *v6_ops = nf_get_ipv6_ops();

	अगर (!v6_ops)
		वापस -EHOSTUNREACH;

	वापस v6_ops->dev_get_saddr(net, dev, daddr, srcprefs, saddr);
#अन्यथा
	वापस ipv6_dev_get_saddr(net, dev, daddr, srcprefs, saddr);
#पूर्ण_अगर
पूर्ण

अचिन्हित पूर्णांक
nf_nat_masquerade_ipv6(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_nat_range2 *range,
		       स्थिर काष्ठा net_device *out)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn_nat *nat;
	काष्ठा in6_addr src;
	काष्ठा nf_conn *ct;
	काष्ठा nf_nat_range2 newrange;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
			 ctinfo == IP_CT_RELATED_REPLY)));

	अगर (nat_ipv6_dev_get_saddr(nf_ct_net(ct), out,
				   &ipv6_hdr(skb)->daddr, 0, &src) < 0)
		वापस NF_DROP;

	nat = nf_ct_nat_ext_add(ct);
	अगर (nat)
		nat->masq_index = out->अगरindex;

	newrange.flags		= range->flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr.in6	= src;
	newrange.max_addr.in6	= src;
	newrange.min_proto	= range->min_proto;
	newrange.max_proto	= range->max_proto;

	वापस nf_nat_setup_info(ct, &newrange, NF_NAT_MANIP_SRC);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_masquerade_ipv6);

काष्ठा masq_dev_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा net *net;
	काष्ठा in6_addr addr;
	पूर्णांक अगरindex;
पूर्ण;

अटल पूर्णांक inet6_cmp(काष्ठा nf_conn *ct, व्योम *work)
अणु
	काष्ठा masq_dev_work *w = (काष्ठा masq_dev_work *)work;
	काष्ठा nf_conntrack_tuple *tuple;

	अगर (!device_cmp(ct, (व्योम *)(दीर्घ)w->अगरindex))
		वापस 0;

	tuple = &ct->tuplehash[IP_CT_सूची_REPLY].tuple;

	वापस ipv6_addr_equal(&w->addr, &tuple->dst.u3.in6);
पूर्ण

अटल व्योम iterate_cleanup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा masq_dev_work *w;

	w = container_of(work, काष्ठा masq_dev_work, work);

	nf_ct_iterate_cleanup_net(w->net, inet6_cmp, (व्योम *)w, 0, 0);

	put_net(w->net);
	kमुक्त(w);
	atomic_dec(&v6_worker_count);
	module_put(THIS_MODULE);
पूर्ण

/* atomic notअगरier; can't call nf_ct_iterate_cleanup_net (it can sleep).
 *
 * Defer it to the प्रणाली workqueue.
 *
 * As we can have 'a lot' of inet_events (depending on amount of ipv6
 * addresses being deleted), we also need to limit work item queue.
 */
अटल पूर्णांक masq_inet6_event(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगरa = ptr;
	स्थिर काष्ठा net_device *dev;
	काष्ठा masq_dev_work *w;
	काष्ठा net *net;

	अगर (event != NETDEV_DOWN || atomic_पढ़ो(&v6_worker_count) >= 16)
		वापस NOTIFY_DONE;

	dev = अगरa->idev->dev;
	net = maybe_get_net(dev_net(dev));
	अगर (!net)
		वापस NOTIFY_DONE;

	अगर (!try_module_get(THIS_MODULE))
		जाओ err_module;

	w = kदो_स्मृति(माप(*w), GFP_ATOMIC);
	अगर (w) अणु
		atomic_inc(&v6_worker_count);

		INIT_WORK(&w->work, iterate_cleanup_work);
		w->अगरindex = dev->अगरindex;
		w->net = net;
		w->addr = अगरa->addr;
		schedule_work(&w->work);

		वापस NOTIFY_DONE;
	पूर्ण

	module_put(THIS_MODULE);
 err_module:
	put_net(net);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block masq_inet6_notअगरier = अणु
	.notअगरier_call	= masq_inet6_event,
पूर्ण;

अटल पूर्णांक nf_nat_masquerade_ipv6_रेजिस्टर_notअगरier(व्योम)
अणु
	वापस रेजिस्टर_inet6addr_notअगरier(&masq_inet6_notअगरier);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक nf_nat_masquerade_ipv6_रेजिस्टर_notअगरier(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

पूर्णांक nf_nat_masquerade_inet_रेजिस्टर_notअगरiers(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&masq_mutex);
	अगर (WARN_ON_ONCE(masq_refcnt == अच_पूर्णांक_उच्च)) अणु
		ret = -EOVERFLOW;
		जाओ out_unlock;
	पूर्ण

	/* check अगर the notअगरier was alपढ़ोy set */
	अगर (++masq_refcnt > 1)
		जाओ out_unlock;

	/* Register क्रम device करोwn reports */
	ret = रेजिस्टर_netdevice_notअगरier(&masq_dev_notअगरier);
	अगर (ret)
		जाओ err_dec;
	/* Register IP address change reports */
	ret = रेजिस्टर_inetaddr_notअगरier(&masq_inet_notअगरier);
	अगर (ret)
		जाओ err_unरेजिस्टर;

	ret = nf_nat_masquerade_ipv6_रेजिस्टर_notअगरier();
	अगर (ret)
		जाओ err_unreg_inet;

	mutex_unlock(&masq_mutex);
	वापस ret;
err_unreg_inet:
	unरेजिस्टर_inetaddr_notअगरier(&masq_inet_notअगरier);
err_unरेजिस्टर:
	unरेजिस्टर_netdevice_notअगरier(&masq_dev_notअगरier);
err_dec:
	masq_refcnt--;
out_unlock:
	mutex_unlock(&masq_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_masquerade_inet_रेजिस्टर_notअगरiers);

व्योम nf_nat_masquerade_inet_unरेजिस्टर_notअगरiers(व्योम)
अणु
	mutex_lock(&masq_mutex);
	/* check अगर the notअगरiers still have clients */
	अगर (--masq_refcnt > 0)
		जाओ out_unlock;

	unरेजिस्टर_netdevice_notअगरier(&masq_dev_notअगरier);
	unरेजिस्टर_inetaddr_notअगरier(&masq_inet_notअगरier);
#अगर IS_ENABLED(CONFIG_IPV6)
	unरेजिस्टर_inet6addr_notअगरier(&masq_inet6_notअगरier);
#पूर्ण_अगर
out_unlock:
	mutex_unlock(&masq_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nf_nat_masquerade_inet_unरेजिस्टर_notअगरiers);
