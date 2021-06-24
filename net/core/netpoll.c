<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common framework क्रम low-level network console, dump, and debugger code
 *
 * Sep 8 2003  Matt Mackall <mpm@selenic.com>
 *
 * based on the netconsole code from:
 *
 * Copyright (C) 2001  Ingo Molnar <mingo@redhat.com>
 * Copyright (C) 2002  Red Hat, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/addrconf.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip6_checksum.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <trace/events/napi.h>

/*
 * We मुख्यtain a small pool of fully-sized skbs, to make sure the
 * message माला_लो out even in extreme OOM situations.
 */

#घोषणा MAX_UDP_CHUNK 1460
#घोषणा MAX_SKBS 32

अटल काष्ठा sk_buff_head skb_pool;

DEFINE_STATIC_SRCU(netpoll_srcu);

#घोषणा USEC_PER_POLL	50

#घोषणा MAX_SKB_SIZE							\
	(माप(काष्ठा ethhdr) +					\
	 माप(काष्ठा iphdr) +						\
	 माप(काष्ठा udphdr) +					\
	 MAX_UDP_CHUNK)

अटल व्योम zap_completion_queue(व्योम);

अटल अचिन्हित पूर्णांक carrier_समयout = 4;
module_param(carrier_समयout, uपूर्णांक, 0644);

#घोषणा np_info(np, fmt, ...)				\
	pr_info("%s: " fmt, np->name, ##__VA_ARGS__)
#घोषणा np_err(np, fmt, ...)				\
	pr_err("%s: " fmt, np->name, ##__VA_ARGS__)
#घोषणा np_notice(np, fmt, ...)				\
	pr_notice("%s: " fmt, np->name, ##__VA_ARGS__)

अटल netdev_tx_t netpoll_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      काष्ठा netdev_queue *txq)
अणु
	netdev_tx_t status = NETDEV_TX_OK;
	netdev_features_t features;

	features = netअगर_skb_features(skb);

	अगर (skb_vlan_tag_present(skb) &&
	    !vlan_hw_offload_capable(features, skb->vlan_proto)) अणु
		skb = __vlan_hwaccel_push_inside(skb);
		अगर (unlikely(!skb)) अणु
			/* This is actually a packet drop, but we
			 * करोn't want the code that calls this
			 * function to try and operate on a शून्य skb.
			 */
			जाओ out;
		पूर्ण
	पूर्ण

	status = netdev_start_xmit(skb, dev, txq, false);

out:
	वापस status;
पूर्ण

अटल व्योम queue_process(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netpoll_info *npinfo =
		container_of(work, काष्ठा netpoll_info, tx_work.work);
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	जबतक ((skb = skb_dequeue(&npinfo->txq))) अणु
		काष्ठा net_device *dev = skb->dev;
		काष्ठा netdev_queue *txq;
		अचिन्हित पूर्णांक q_index;

		अगर (!netअगर_device_present(dev) || !netअगर_running(dev)) अणु
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		local_irq_save(flags);
		/* check अगर skb->queue_mapping is still valid */
		q_index = skb_get_queue_mapping(skb);
		अगर (unlikely(q_index >= dev->real_num_tx_queues)) अणु
			q_index = q_index % dev->real_num_tx_queues;
			skb_set_queue_mapping(skb, q_index);
		पूर्ण
		txq = netdev_get_tx_queue(dev, q_index);
		HARD_TX_LOCK(dev, txq, smp_processor_id());
		अगर (netअगर_xmit_frozen_or_stopped(txq) ||
		    !dev_xmit_complete(netpoll_start_xmit(skb, dev, txq))) अणु
			skb_queue_head(&npinfo->txq, skb);
			HARD_TX_UNLOCK(dev, txq);
			local_irq_restore(flags);

			schedule_delayed_work(&npinfo->tx_work, HZ/10);
			वापस;
		पूर्ण
		HARD_TX_UNLOCK(dev, txq);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

अटल व्योम poll_one_napi(काष्ठा napi_काष्ठा *napi)
अणु
	पूर्णांक work;

	/* If we set this bit but see that it has alपढ़ोy been set,
	 * that indicates that napi has been disabled and we need
	 * to पात this operation
	 */
	अगर (test_and_set_bit(NAPI_STATE_NPSVC, &napi->state))
		वापस;

	/* We explicilty pass the polling call a budget of 0 to
	 * indicate that we are clearing the Tx path only.
	 */
	work = napi->poll(napi, 0);
	WARN_ONCE(work, "%pS exceeded budget in poll\n", napi->poll);
	trace_napi_poll(napi, work, 0);

	clear_bit(NAPI_STATE_NPSVC, &napi->state);
पूर्ण

अटल व्योम poll_napi(काष्ठा net_device *dev)
अणु
	काष्ठा napi_काष्ठा *napi;
	पूर्णांक cpu = smp_processor_id();

	list_क्रम_each_entry_rcu(napi, &dev->napi_list, dev_list) अणु
		अगर (cmpxchg(&napi->poll_owner, -1, cpu) == -1) अणु
			poll_one_napi(napi);
			smp_store_release(&napi->poll_owner, -1);
		पूर्ण
	पूर्ण
पूर्ण

व्योम netpoll_poll_dev(काष्ठा net_device *dev)
अणु
	काष्ठा netpoll_info *ni = rcu_dereference_bh(dev->npinfo);
	स्थिर काष्ठा net_device_ops *ops;

	/* Don't करो any rx activity अगर the dev_lock mutex is held
	 * the dev_खोलो/बंद paths use this to block netpoll activity
	 * जबतक changing device state
	 */
	अगर (!ni || करोwn_trylock(&ni->dev_lock))
		वापस;

	अगर (!netअगर_running(dev)) अणु
		up(&ni->dev_lock);
		वापस;
	पूर्ण

	ops = dev->netdev_ops;
	अगर (ops->nकरो_poll_controller)
		ops->nकरो_poll_controller(dev);

	poll_napi(dev);

	up(&ni->dev_lock);

	zap_completion_queue();
पूर्ण
EXPORT_SYMBOL(netpoll_poll_dev);

व्योम netpoll_poll_disable(काष्ठा net_device *dev)
अणु
	काष्ठा netpoll_info *ni;
	पूर्णांक idx;
	might_sleep();
	idx = srcu_पढ़ो_lock(&netpoll_srcu);
	ni = srcu_dereference(dev->npinfo, &netpoll_srcu);
	अगर (ni)
		करोwn(&ni->dev_lock);
	srcu_पढ़ो_unlock(&netpoll_srcu, idx);
पूर्ण
EXPORT_SYMBOL(netpoll_poll_disable);

व्योम netpoll_poll_enable(काष्ठा net_device *dev)
अणु
	काष्ठा netpoll_info *ni;
	rcu_पढ़ो_lock();
	ni = rcu_dereference(dev->npinfo);
	अगर (ni)
		up(&ni->dev_lock);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(netpoll_poll_enable);

अटल व्योम refill_skbs(व्योम)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&skb_pool.lock, flags);
	जबतक (skb_pool.qlen < MAX_SKBS) अणु
		skb = alloc_skb(MAX_SKB_SIZE, GFP_ATOMIC);
		अगर (!skb)
			अवरोध;

		__skb_queue_tail(&skb_pool, skb);
	पूर्ण
	spin_unlock_irqrestore(&skb_pool.lock, flags);
पूर्ण

अटल व्योम zap_completion_queue(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा softnet_data *sd = &get_cpu_var(softnet_data);

	अगर (sd->completion_queue) अणु
		काष्ठा sk_buff *clist;

		local_irq_save(flags);
		clist = sd->completion_queue;
		sd->completion_queue = शून्य;
		local_irq_restore(flags);

		जबतक (clist != शून्य) अणु
			काष्ठा sk_buff *skb = clist;
			clist = clist->next;
			अगर (!skb_irq_मुक्तable(skb)) अणु
				refcount_set(&skb->users, 1);
				dev_kमुक्त_skb_any(skb); /* put this one back */
			पूर्ण अन्यथा अणु
				__kमुक्त_skb(skb);
			पूर्ण
		पूर्ण
	पूर्ण

	put_cpu_var(softnet_data);
पूर्ण

अटल काष्ठा sk_buff *find_skb(काष्ठा netpoll *np, पूर्णांक len, पूर्णांक reserve)
अणु
	पूर्णांक count = 0;
	काष्ठा sk_buff *skb;

	zap_completion_queue();
	refill_skbs();
repeat:

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb)
		skb = skb_dequeue(&skb_pool);

	अगर (!skb) अणु
		अगर (++count < 10) अणु
			netpoll_poll_dev(np->dev);
			जाओ repeat;
		पूर्ण
		वापस शून्य;
	पूर्ण

	refcount_set(&skb->users, 1);
	skb_reserve(skb, reserve);
	वापस skb;
पूर्ण

अटल पूर्णांक netpoll_owner_active(काष्ठा net_device *dev)
अणु
	काष्ठा napi_काष्ठा *napi;

	list_क्रम_each_entry_rcu(napi, &dev->napi_list, dev_list) अणु
		अगर (napi->poll_owner == smp_processor_id())
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* call with IRQ disabled */
अटल netdev_tx_t __netpoll_send_skb(काष्ठा netpoll *np, काष्ठा sk_buff *skb)
अणु
	netdev_tx_t status = NETDEV_TX_BUSY;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ tries;
	/* It is up to the caller to keep npinfo alive. */
	काष्ठा netpoll_info *npinfo;

	lockdep_निश्चित_irqs_disabled();

	dev = np->dev;
	npinfo = rcu_dereference_bh(dev->npinfo);

	अगर (!npinfo || !netअगर_running(dev) || !netअगर_device_present(dev)) अणु
		dev_kमुक्त_skb_irq(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	/* करोn't get messages out of order, and no recursion */
	अगर (skb_queue_len(&npinfo->txq) == 0 && !netpoll_owner_active(dev)) अणु
		काष्ठा netdev_queue *txq;

		txq = netdev_core_pick_tx(dev, skb, शून्य);

		/* try until next घड़ी tick */
		क्रम (tries = jअगरfies_to_usecs(1)/USEC_PER_POLL;
		     tries > 0; --tries) अणु
			अगर (HARD_TX_TRYLOCK(dev, txq)) अणु
				अगर (!netअगर_xmit_stopped(txq))
					status = netpoll_start_xmit(skb, dev, txq);

				HARD_TX_UNLOCK(dev, txq);

				अगर (dev_xmit_complete(status))
					अवरोध;

			पूर्ण

			/* tickle device maybe there is some cleanup */
			netpoll_poll_dev(np->dev);

			udelay(USEC_PER_POLL);
		पूर्ण

		WARN_ONCE(!irqs_disabled(),
			"netpoll_send_skb_on_dev(): %s enabled interrupts in poll (%pS)\n",
			dev->name, dev->netdev_ops->nकरो_start_xmit);

	पूर्ण

	अगर (!dev_xmit_complete(status)) अणु
		skb_queue_tail(&npinfo->txq, skb);
		schedule_delayed_work(&npinfo->tx_work,0);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

netdev_tx_t netpoll_send_skb(काष्ठा netpoll *np, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	netdev_tx_t ret;

	अगर (unlikely(!np)) अणु
		dev_kमुक्त_skb_irq(skb);
		ret = NET_XMIT_DROP;
	पूर्ण अन्यथा अणु
		local_irq_save(flags);
		ret = __netpoll_send_skb(np, skb);
		local_irq_restore(flags);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(netpoll_send_skb);

व्योम netpoll_send_udp(काष्ठा netpoll *np, स्थिर अक्षर *msg, पूर्णांक len)
अणु
	पूर्णांक total_len, ip_len, udp_len;
	काष्ठा sk_buff *skb;
	काष्ठा udphdr *udph;
	काष्ठा iphdr *iph;
	काष्ठा ethhdr *eth;
	अटल atomic_t ip_ident;
	काष्ठा ipv6hdr *ip6h;

	WARN_ON_ONCE(!irqs_disabled());

	udp_len = len + माप(*udph);
	अगर (np->ipv6)
		ip_len = udp_len + माप(*ip6h);
	अन्यथा
		ip_len = udp_len + माप(*iph);

	total_len = ip_len + LL_RESERVED_SPACE(np->dev);

	skb = find_skb(np, total_len + np->dev->needed_tailroom,
		       total_len - len);
	अगर (!skb)
		वापस;

	skb_copy_to_linear_data(skb, msg, len);
	skb_put(skb, len);

	skb_push(skb, माप(*udph));
	skb_reset_transport_header(skb);
	udph = udp_hdr(skb);
	udph->source = htons(np->local_port);
	udph->dest = htons(np->remote_port);
	udph->len = htons(udp_len);

	अगर (np->ipv6) अणु
		udph->check = 0;
		udph->check = csum_ipv6_magic(&np->local_ip.in6,
					      &np->remote_ip.in6,
					      udp_len, IPPROTO_UDP,
					      csum_partial(udph, udp_len, 0));
		अगर (udph->check == 0)
			udph->check = CSUM_MANGLED_0;

		skb_push(skb, माप(*ip6h));
		skb_reset_network_header(skb);
		ip6h = ipv6_hdr(skb);

		/* ip6h->version = 6; ip6h->priority = 0; */
		put_unaligned(0x60, (अचिन्हित अक्षर *)ip6h);
		ip6h->flow_lbl[0] = 0;
		ip6h->flow_lbl[1] = 0;
		ip6h->flow_lbl[2] = 0;

		ip6h->payload_len = htons(माप(काष्ठा udphdr) + len);
		ip6h->nexthdr = IPPROTO_UDP;
		ip6h->hop_limit = 32;
		ip6h->saddr = np->local_ip.in6;
		ip6h->daddr = np->remote_ip.in6;

		eth = skb_push(skb, ETH_HLEN);
		skb_reset_mac_header(skb);
		skb->protocol = eth->h_proto = htons(ETH_P_IPV6);
	पूर्ण अन्यथा अणु
		udph->check = 0;
		udph->check = csum_tcpudp_magic(np->local_ip.ip,
						np->remote_ip.ip,
						udp_len, IPPROTO_UDP,
						csum_partial(udph, udp_len, 0));
		अगर (udph->check == 0)
			udph->check = CSUM_MANGLED_0;

		skb_push(skb, माप(*iph));
		skb_reset_network_header(skb);
		iph = ip_hdr(skb);

		/* iph->version = 4; iph->ihl = 5; */
		put_unaligned(0x45, (अचिन्हित अक्षर *)iph);
		iph->tos      = 0;
		put_unaligned(htons(ip_len), &(iph->tot_len));
		iph->id       = htons(atomic_inc_वापस(&ip_ident));
		iph->frag_off = 0;
		iph->ttl      = 64;
		iph->protocol = IPPROTO_UDP;
		iph->check    = 0;
		put_unaligned(np->local_ip.ip, &(iph->saddr));
		put_unaligned(np->remote_ip.ip, &(iph->daddr));
		iph->check    = ip_fast_csum((अचिन्हित अक्षर *)iph, iph->ihl);

		eth = skb_push(skb, ETH_HLEN);
		skb_reset_mac_header(skb);
		skb->protocol = eth->h_proto = htons(ETH_P_IP);
	पूर्ण

	ether_addr_copy(eth->h_source, np->dev->dev_addr);
	ether_addr_copy(eth->h_dest, np->remote_mac);

	skb->dev = np->dev;

	netpoll_send_skb(np, skb);
पूर्ण
EXPORT_SYMBOL(netpoll_send_udp);

व्योम netpoll_prपूर्णांक_options(काष्ठा netpoll *np)
अणु
	np_info(np, "local port %d\n", np->local_port);
	अगर (np->ipv6)
		np_info(np, "local IPv6 address %pI6c\n", &np->local_ip.in6);
	अन्यथा
		np_info(np, "local IPv4 address %pI4\n", &np->local_ip.ip);
	np_info(np, "interface '%s'\n", np->dev_name);
	np_info(np, "remote port %d\n", np->remote_port);
	अगर (np->ipv6)
		np_info(np, "remote IPv6 address %pI6c\n", &np->remote_ip.in6);
	अन्यथा
		np_info(np, "remote IPv4 address %pI4\n", &np->remote_ip.ip);
	np_info(np, "remote ethernet address %pM\n", np->remote_mac);
पूर्ण
EXPORT_SYMBOL(netpoll_prपूर्णांक_options);

अटल पूर्णांक netpoll_parse_ip_addr(स्थिर अक्षर *str, जोड़ inet_addr *addr)
अणु
	स्थिर अक्षर *end;

	अगर (!म_अक्षर(str, ':') &&
	    in4_pton(str, -1, (व्योम *)addr, -1, &end) > 0) अणु
		अगर (!*end)
			वापस 0;
	पूर्ण
	अगर (in6_pton(str, -1, addr->in6.s6_addr, -1, &end) > 0) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (!*end)
			वापस 1;
#अन्यथा
		वापस -1;
#पूर्ण_अगर
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक netpoll_parse_options(काष्ठा netpoll *np, अक्षर *opt)
अणु
	अक्षर *cur=opt, *delim;
	पूर्णांक ipv6;
	bool ipversion_set = false;

	अगर (*cur != '@') अणु
		अगर ((delim = म_अक्षर(cur, '@')) == शून्य)
			जाओ parse_failed;
		*delim = 0;
		अगर (kstrtou16(cur, 10, &np->local_port))
			जाओ parse_failed;
		cur = delim;
	पूर्ण
	cur++;

	अगर (*cur != '/') अणु
		ipversion_set = true;
		अगर ((delim = म_अक्षर(cur, '/')) == शून्य)
			जाओ parse_failed;
		*delim = 0;
		ipv6 = netpoll_parse_ip_addr(cur, &np->local_ip);
		अगर (ipv6 < 0)
			जाओ parse_failed;
		अन्यथा
			np->ipv6 = (bool)ipv6;
		cur = delim;
	पूर्ण
	cur++;

	अगर (*cur != ',') अणु
		/* parse out dev name */
		अगर ((delim = म_अक्षर(cur, ',')) == शून्य)
			जाओ parse_failed;
		*delim = 0;
		strlcpy(np->dev_name, cur, माप(np->dev_name));
		cur = delim;
	पूर्ण
	cur++;

	अगर (*cur != '@') अणु
		/* dst port */
		अगर ((delim = म_अक्षर(cur, '@')) == शून्य)
			जाओ parse_failed;
		*delim = 0;
		अगर (*cur == ' ' || *cur == '\t')
			np_info(np, "warning: whitespace is not allowed\n");
		अगर (kstrtou16(cur, 10, &np->remote_port))
			जाओ parse_failed;
		cur = delim;
	पूर्ण
	cur++;

	/* dst ip */
	अगर ((delim = म_अक्षर(cur, '/')) == शून्य)
		जाओ parse_failed;
	*delim = 0;
	ipv6 = netpoll_parse_ip_addr(cur, &np->remote_ip);
	अगर (ipv6 < 0)
		जाओ parse_failed;
	अन्यथा अगर (ipversion_set && np->ipv6 != (bool)ipv6)
		जाओ parse_failed;
	अन्यथा
		np->ipv6 = (bool)ipv6;
	cur = delim + 1;

	अगर (*cur != 0) अणु
		/* MAC address */
		अगर (!mac_pton(cur, np->remote_mac))
			जाओ parse_failed;
	पूर्ण

	netpoll_prपूर्णांक_options(np);

	वापस 0;

 parse_failed:
	np_info(np, "couldn't parse config at '%s'!\n", cur);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(netpoll_parse_options);

पूर्णांक __netpoll_setup(काष्ठा netpoll *np, काष्ठा net_device *ndev)
अणु
	काष्ठा netpoll_info *npinfo;
	स्थिर काष्ठा net_device_ops *ops;
	पूर्णांक err;

	np->dev = ndev;
	strlcpy(np->dev_name, ndev->name, IFNAMSIZ);

	अगर (ndev->priv_flags & IFF_DISABLE_NETPOLL) अणु
		np_err(np, "%s doesn't support polling, aborting\n",
		       np->dev_name);
		err = -ENOTSUPP;
		जाओ out;
	पूर्ण

	अगर (!ndev->npinfo) अणु
		npinfo = kदो_स्मृति(माप(*npinfo), GFP_KERNEL);
		अगर (!npinfo) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		sema_init(&npinfo->dev_lock, 1);
		skb_queue_head_init(&npinfo->txq);
		INIT_DELAYED_WORK(&npinfo->tx_work, queue_process);

		refcount_set(&npinfo->refcnt, 1);

		ops = np->dev->netdev_ops;
		अगर (ops->nकरो_netpoll_setup) अणु
			err = ops->nकरो_netpoll_setup(ndev, npinfo);
			अगर (err)
				जाओ मुक्त_npinfo;
		पूर्ण
	पूर्ण अन्यथा अणु
		npinfo = rtnl_dereference(ndev->npinfo);
		refcount_inc(&npinfo->refcnt);
	पूर्ण

	npinfo->netpoll = np;

	/* last thing to करो is link it to the net device काष्ठाure */
	rcu_assign_poपूर्णांकer(ndev->npinfo, npinfo);

	वापस 0;

मुक्त_npinfo:
	kमुक्त(npinfo);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__netpoll_setup);

पूर्णांक netpoll_setup(काष्ठा netpoll *np)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा in_device *in_dev;
	पूर्णांक err;

	rtnl_lock();
	अगर (np->dev_name[0]) अणु
		काष्ठा net *net = current->nsproxy->net_ns;
		ndev = __dev_get_by_name(net, np->dev_name);
	पूर्ण
	अगर (!ndev) अणु
		np_err(np, "%s doesn't exist, aborting\n", np->dev_name);
		err = -ENODEV;
		जाओ unlock;
	पूर्ण
	dev_hold(ndev);

	अगर (netdev_master_upper_dev_get(ndev)) अणु
		np_err(np, "%s is a slave device, aborting\n", np->dev_name);
		err = -EBUSY;
		जाओ put;
	पूर्ण

	अगर (!netअगर_running(ndev)) अणु
		अचिन्हित दीर्घ aपंचांगost, atleast;

		np_info(np, "device %s not up yet, forcing it\n", np->dev_name);

		err = dev_खोलो(ndev, शून्य);

		अगर (err) अणु
			np_err(np, "failed to open %s\n", ndev->name);
			जाओ put;
		पूर्ण

		rtnl_unlock();
		atleast = jअगरfies + HZ/10;
		aपंचांगost = jअगरfies + carrier_समयout * HZ;
		जबतक (!netअगर_carrier_ok(ndev)) अणु
			अगर (समय_after(jअगरfies, aपंचांगost)) अणु
				np_notice(np, "timeout waiting for carrier\n");
				अवरोध;
			पूर्ण
			msleep(1);
		पूर्ण

		/* If carrier appears to come up instantly, we करोn't
		 * trust it and छोड़ो so that we करोn't pump all our
		 * queued console messages पूर्णांकo the bitbucket.
		 */

		अगर (समय_beक्रमe(jअगरfies, atleast)) अणु
			np_notice(np, "carrier detect appears untrustworthy, waiting 4 seconds\n");
			msleep(4000);
		पूर्ण
		rtnl_lock();
	पूर्ण

	अगर (!np->local_ip.ip) अणु
		अगर (!np->ipv6) अणु
			स्थिर काष्ठा in_अगरaddr *अगरa;

			in_dev = __in_dev_get_rtnl(ndev);
			अगर (!in_dev)
				जाओ put_noaddr;

			अगरa = rtnl_dereference(in_dev->अगरa_list);
			अगर (!अगरa) अणु
put_noaddr:
				np_err(np, "no IP address for %s, aborting\n",
				       np->dev_name);
				err = -EDESTADDRREQ;
				जाओ put;
			पूर्ण

			np->local_ip.ip = अगरa->अगरa_local;
			np_info(np, "local IP %pI4\n", &np->local_ip.ip);
		पूर्ण अन्यथा अणु
#अगर IS_ENABLED(CONFIG_IPV6)
			काष्ठा inet6_dev *idev;

			err = -EDESTADDRREQ;
			idev = __in6_dev_get(ndev);
			अगर (idev) अणु
				काष्ठा inet6_अगरaddr *अगरp;

				पढ़ो_lock_bh(&idev->lock);
				list_क्रम_each_entry(अगरp, &idev->addr_list, अगर_list) अणु
					अगर (!!(ipv6_addr_type(&अगरp->addr) & IPV6_ADDR_LINKLOCAL) !=
					    !!(ipv6_addr_type(&np->remote_ip.in6) & IPV6_ADDR_LINKLOCAL))
						जारी;
					np->local_ip.in6 = अगरp->addr;
					err = 0;
					अवरोध;
				पूर्ण
				पढ़ो_unlock_bh(&idev->lock);
			पूर्ण
			अगर (err) अणु
				np_err(np, "no IPv6 address for %s, aborting\n",
				       np->dev_name);
				जाओ put;
			पूर्ण अन्यथा
				np_info(np, "local IPv6 %pI6c\n", &np->local_ip.in6);
#अन्यथा
			np_err(np, "IPv6 is not supported %s, aborting\n",
			       np->dev_name);
			err = -EINVAL;
			जाओ put;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	/* fill up the skb queue */
	refill_skbs();

	err = __netpoll_setup(np, ndev);
	अगर (err)
		जाओ put;

	rtnl_unlock();
	वापस 0;

put:
	dev_put(ndev);
unlock:
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(netpoll_setup);

अटल पूर्णांक __init netpoll_init(व्योम)
अणु
	skb_queue_head_init(&skb_pool);
	वापस 0;
पूर्ण
core_initcall(netpoll_init);

अटल व्योम rcu_cleanup_netpoll_info(काष्ठा rcu_head *rcu_head)
अणु
	काष्ठा netpoll_info *npinfo =
			container_of(rcu_head, काष्ठा netpoll_info, rcu);

	skb_queue_purge(&npinfo->txq);

	/* we can't call cancel_delayed_work_sync here, as we are in softirq */
	cancel_delayed_work(&npinfo->tx_work);

	/* clean after last, unfinished work */
	__skb_queue_purge(&npinfo->txq);
	/* now cancel it again */
	cancel_delayed_work(&npinfo->tx_work);
	kमुक्त(npinfo);
पूर्ण

व्योम __netpoll_cleanup(काष्ठा netpoll *np)
अणु
	काष्ठा netpoll_info *npinfo;

	npinfo = rtnl_dereference(np->dev->npinfo);
	अगर (!npinfo)
		वापस;

	synchronize_srcu(&netpoll_srcu);

	अगर (refcount_dec_and_test(&npinfo->refcnt)) अणु
		स्थिर काष्ठा net_device_ops *ops;

		ops = np->dev->netdev_ops;
		अगर (ops->nकरो_netpoll_cleanup)
			ops->nकरो_netpoll_cleanup(np->dev);

		RCU_INIT_POINTER(np->dev->npinfo, शून्य);
		call_rcu(&npinfo->rcu, rcu_cleanup_netpoll_info);
	पूर्ण अन्यथा
		RCU_INIT_POINTER(np->dev->npinfo, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(__netpoll_cleanup);

व्योम __netpoll_मुक्त(काष्ठा netpoll *np)
अणु
	ASSERT_RTNL();

	/* Wait क्रम transmitting packets to finish beक्रमe मुक्तing. */
	synchronize_rcu();
	__netpoll_cleanup(np);
	kमुक्त(np);
पूर्ण
EXPORT_SYMBOL_GPL(__netpoll_मुक्त);

व्योम netpoll_cleanup(काष्ठा netpoll *np)
अणु
	rtnl_lock();
	अगर (!np->dev)
		जाओ out;
	__netpoll_cleanup(np);
	dev_put(np->dev);
	np->dev = शून्य;
out:
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL(netpoll_cleanup);
