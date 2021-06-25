<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2020, Red Hat, Inc.
 */

#घोषणा pr_fmt(fmt) "MPTCP: " fmt

#समावेश <linux/inet.h>
#समावेश <linux/kernel.h>
#समावेश <net/tcp.h>
#समावेश <net/netns/generic.h>
#समावेश <net/mptcp.h>
#समावेश <net/genetlink.h>
#समावेश <uapi/linux/mptcp.h>

#समावेश "protocol.h"
#समावेश "mib.h"

/* क्रमward declaration */
अटल काष्ठा genl_family mptcp_genl_family;

अटल पूर्णांक pm_nl_pernet_id;

काष्ठा mptcp_pm_addr_entry अणु
	काष्ठा list_head	list;
	काष्ठा mptcp_addr_info	addr;
	u8			flags;
	पूर्णांक			अगरindex;
	काष्ठा rcu_head		rcu;
	काष्ठा socket		*lsk;
पूर्ण;

काष्ठा mptcp_pm_add_entry अणु
	काष्ठा list_head	list;
	काष्ठा mptcp_addr_info	addr;
	काष्ठा समयr_list	add_समयr;
	काष्ठा mptcp_sock	*sock;
	u8			retrans_बार;
पूर्ण;

#घोषणा MAX_ADDR_ID		255
#घोषणा BITMAP_SZ DIV_ROUND_UP(MAX_ADDR_ID + 1, BITS_PER_LONG)

काष्ठा pm_nl_pernet अणु
	/* protects pernet updates */
	spinlock_t		lock;
	काष्ठा list_head	local_addr_list;
	अचिन्हित पूर्णांक		addrs;
	अचिन्हित पूर्णांक		add_addr_संकेत_max;
	अचिन्हित पूर्णांक		add_addr_accept_max;
	अचिन्हित पूर्णांक		local_addr_max;
	अचिन्हित पूर्णांक		subflows_max;
	अचिन्हित पूर्णांक		next_id;
	अचिन्हित दीर्घ		id_biपंचांगap[BITMAP_SZ];
पूर्ण;

#घोषणा MPTCP_PM_ADDR_MAX	8
#घोषणा ADD_ADDR_RETRANS_MAX	3

अटल bool addresses_equal(स्थिर काष्ठा mptcp_addr_info *a,
			    काष्ठा mptcp_addr_info *b, bool use_port)
अणु
	bool addr_equals = false;

	अगर (a->family == b->family) अणु
		अगर (a->family == AF_INET)
			addr_equals = a->addr.s_addr == b->addr.s_addr;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
		अन्यथा
			addr_equals = !ipv6_addr_cmp(&a->addr6, &b->addr6);
	पूर्ण अन्यथा अगर (a->family == AF_INET) अणु
		अगर (ipv6_addr_v4mapped(&b->addr6))
			addr_equals = a->addr.s_addr == b->addr6.s6_addr32[3];
	पूर्ण अन्यथा अगर (b->family == AF_INET) अणु
		अगर (ipv6_addr_v4mapped(&a->addr6))
			addr_equals = a->addr6.s6_addr32[3] == b->addr.s_addr;
#पूर्ण_अगर
	पूर्ण

	अगर (!addr_equals)
		वापस false;
	अगर (!use_port)
		वापस true;

	वापस a->port == b->port;
पूर्ण

अटल bool address_zero(स्थिर काष्ठा mptcp_addr_info *addr)
अणु
	काष्ठा mptcp_addr_info zero;

	स_रखो(&zero, 0, माप(zero));
	zero.family = addr->family;

	वापस addresses_equal(addr, &zero, true);
पूर्ण

अटल व्योम local_address(स्थिर काष्ठा sock_common *skc,
			  काष्ठा mptcp_addr_info *addr)
अणु
	addr->family = skc->skc_family;
	addr->port = htons(skc->skc_num);
	अगर (addr->family == AF_INET)
		addr->addr.s_addr = skc->skc_rcv_saddr;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अन्यथा अगर (addr->family == AF_INET6)
		addr->addr6 = skc->skc_v6_rcv_saddr;
#पूर्ण_अगर
पूर्ण

अटल व्योम remote_address(स्थिर काष्ठा sock_common *skc,
			   काष्ठा mptcp_addr_info *addr)
अणु
	addr->family = skc->skc_family;
	addr->port = skc->skc_dport;
	अगर (addr->family == AF_INET)
		addr->addr.s_addr = skc->skc_daddr;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अन्यथा अगर (addr->family == AF_INET6)
		addr->addr6 = skc->skc_v6_daddr;
#पूर्ण_अगर
पूर्ण

अटल bool lookup_subflow_by_saddr(स्थिर काष्ठा list_head *list,
				    काष्ठा mptcp_addr_info *saddr)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_addr_info cur;
	काष्ठा sock_common *skc;

	list_क्रम_each_entry(subflow, list, node) अणु
		skc = (काष्ठा sock_common *)mptcp_subflow_tcp_sock(subflow);

		local_address(skc, &cur);
		अगर (addresses_equal(&cur, saddr, saddr->port))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool lookup_subflow_by_daddr(स्थिर काष्ठा list_head *list,
				    काष्ठा mptcp_addr_info *daddr)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_addr_info cur;
	काष्ठा sock_common *skc;

	list_क्रम_each_entry(subflow, list, node) अणु
		skc = (काष्ठा sock_common *)mptcp_subflow_tcp_sock(subflow);

		remote_address(skc, &cur);
		अगर (addresses_equal(&cur, daddr, daddr->port))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा mptcp_pm_addr_entry *
select_local_address(स्थिर काष्ठा pm_nl_pernet *pernet,
		     काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_pm_addr_entry *entry, *ret = शून्य;
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	msk_owned_by_me(msk);

	rcu_पढ़ो_lock();
	__mptcp_flush_join_list(msk);
	list_क्रम_each_entry_rcu(entry, &pernet->local_addr_list, list) अणु
		अगर (!(entry->flags & MPTCP_PM_ADDR_FLAG_SUBFLOW))
			जारी;

		अगर (entry->addr.family != sk->sk_family) अणु
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
			अगर ((entry->addr.family == AF_INET &&
			     !ipv6_addr_v4mapped(&sk->sk_v6_daddr)) ||
			    (sk->sk_family == AF_INET &&
			     !ipv6_addr_v4mapped(&entry->addr.addr6)))
#पूर्ण_अगर
				जारी;
		पूर्ण

		/* aव्योम any address alपढ़ोy in use by subflows and
		 * pending join
		 */
		अगर (!lookup_subflow_by_saddr(&msk->conn_list, &entry->addr)) अणु
			ret = entry;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल काष्ठा mptcp_pm_addr_entry *
select_संकेत_address(काष्ठा pm_nl_pernet *pernet, अचिन्हित पूर्णांक pos)
अणु
	काष्ठा mptcp_pm_addr_entry *entry, *ret = शून्य;
	पूर्णांक i = 0;

	rcu_पढ़ो_lock();
	/* करो not keep any additional per socket state, just संकेत
	 * the address list in order.
	 * Note: removal from the local address list during the msk lअगरe-cycle
	 * can lead to additional addresses not being announced.
	 */
	list_क्रम_each_entry_rcu(entry, &pernet->local_addr_list, list) अणु
		अगर (!(entry->flags & MPTCP_PM_ADDR_FLAG_SIGNAL))
			जारी;
		अगर (i++ == pos) अणु
			ret = entry;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक mptcp_pm_get_add_addr_संकेत_max(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((काष्ठा sock *)msk), pm_nl_pernet_id);
	वापस READ_ONCE(pernet->add_addr_संकेत_max);
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_pm_get_add_addr_संकेत_max);

अचिन्हित पूर्णांक mptcp_pm_get_add_addr_accept_max(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((काष्ठा sock *)msk), pm_nl_pernet_id);
	वापस READ_ONCE(pernet->add_addr_accept_max);
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_pm_get_add_addr_accept_max);

अचिन्हित पूर्णांक mptcp_pm_get_subflows_max(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((काष्ठा sock *)msk), pm_nl_pernet_id);
	वापस READ_ONCE(pernet->subflows_max);
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_pm_get_subflows_max);

अचिन्हित पूर्णांक mptcp_pm_get_local_addr_max(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा pm_nl_pernet *pernet;

	pernet = net_generic(sock_net((काष्ठा sock *)msk), pm_nl_pernet_id);
	वापस READ_ONCE(pernet->local_addr_max);
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_pm_get_local_addr_max);

अटल व्योम check_work_pending(काष्ठा mptcp_sock *msk)
अणु
	अगर (msk->pm.add_addr_संकेतed == mptcp_pm_get_add_addr_संकेत_max(msk) &&
	    (msk->pm.local_addr_used == mptcp_pm_get_local_addr_max(msk) ||
	     msk->pm.subflows == mptcp_pm_get_subflows_max(msk)))
		WRITE_ONCE(msk->pm.work_pending, false);
पूर्ण

काष्ठा mptcp_pm_add_entry *
mptcp_lookup_anno_list_by_saddr(काष्ठा mptcp_sock *msk,
				काष्ठा mptcp_addr_info *addr)
अणु
	काष्ठा mptcp_pm_add_entry *entry;

	lockdep_निश्चित_held(&msk->pm.lock);

	list_क्रम_each_entry(entry, &msk->pm.anno_list, list) अणु
		अगर (addresses_equal(&entry->addr, addr, true))
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

bool mptcp_pm_sport_in_anno_list(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *sk)
अणु
	काष्ठा mptcp_pm_add_entry *entry;
	काष्ठा mptcp_addr_info saddr;
	bool ret = false;

	local_address((काष्ठा sock_common *)sk, &saddr);

	spin_lock_bh(&msk->pm.lock);
	list_क्रम_each_entry(entry, &msk->pm.anno_list, list) अणु
		अगर (addresses_equal(&entry->addr, &saddr, true)) अणु
			ret = true;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock_bh(&msk->pm.lock);
	वापस ret;
पूर्ण

अटल व्योम mptcp_pm_add_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा mptcp_pm_add_entry *entry = from_समयr(entry, समयr, add_समयr);
	काष्ठा mptcp_sock *msk = entry->sock;
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	pr_debug("msk=%p", msk);

	अगर (!msk)
		वापस;

	अगर (inet_sk_state_load(sk) == TCP_CLOSE)
		वापस;

	अगर (!entry->addr.id)
		वापस;

	अगर (mptcp_pm_should_add_संकेत(msk)) अणु
		sk_reset_समयr(sk, समयr, jअगरfies + TCP_RTO_MAX / 8);
		जाओ out;
	पूर्ण

	spin_lock_bh(&msk->pm.lock);

	अगर (!mptcp_pm_should_add_संकेत(msk)) अणु
		pr_debug("retransmit ADD_ADDR id=%d", entry->addr.id);
		mptcp_pm_announce_addr(msk, &entry->addr, false);
		mptcp_pm_add_addr_send_ack(msk);
		entry->retrans_बार++;
	पूर्ण

	अगर (entry->retrans_बार < ADD_ADDR_RETRANS_MAX)
		sk_reset_समयr(sk, समयr,
			       jअगरfies + mptcp_get_add_addr_समयout(sock_net(sk)));

	spin_unlock_bh(&msk->pm.lock);

	अगर (entry->retrans_बार == ADD_ADDR_RETRANS_MAX)
		mptcp_pm_subflow_established(msk);

out:
	__sock_put(sk);
पूर्ण

काष्ठा mptcp_pm_add_entry *
mptcp_pm_del_add_समयr(काष्ठा mptcp_sock *msk,
		       काष्ठा mptcp_addr_info *addr, bool check_id)
अणु
	काष्ठा mptcp_pm_add_entry *entry;
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	spin_lock_bh(&msk->pm.lock);
	entry = mptcp_lookup_anno_list_by_saddr(msk, addr);
	अगर (entry && (!check_id || entry->addr.id == addr->id))
		entry->retrans_बार = ADD_ADDR_RETRANS_MAX;
	spin_unlock_bh(&msk->pm.lock);

	अगर (entry && (!check_id || entry->addr.id == addr->id))
		sk_stop_समयr_sync(sk, &entry->add_समयr);

	वापस entry;
पूर्ण

अटल bool mptcp_pm_alloc_anno_list(काष्ठा mptcp_sock *msk,
				     काष्ठा mptcp_pm_addr_entry *entry)
अणु
	काष्ठा mptcp_pm_add_entry *add_entry = शून्य;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा net *net = sock_net(sk);

	lockdep_निश्चित_held(&msk->pm.lock);

	अगर (mptcp_lookup_anno_list_by_saddr(msk, &entry->addr))
		वापस false;

	add_entry = kदो_स्मृति(माप(*add_entry), GFP_ATOMIC);
	अगर (!add_entry)
		वापस false;

	list_add(&add_entry->list, &msk->pm.anno_list);

	add_entry->addr = entry->addr;
	add_entry->sock = msk;
	add_entry->retrans_बार = 0;

	समयr_setup(&add_entry->add_समयr, mptcp_pm_add_समयr, 0);
	sk_reset_समयr(sk, &add_entry->add_समयr,
		       jअगरfies + mptcp_get_add_addr_समयout(net));

	वापस true;
पूर्ण

व्योम mptcp_pm_मुक्त_anno_list(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_pm_add_entry *entry, *पंचांगp;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	LIST_HEAD(मुक्त_list);

	pr_debug("msk=%p", msk);

	spin_lock_bh(&msk->pm.lock);
	list_splice_init(&msk->pm.anno_list, &मुक्त_list);
	spin_unlock_bh(&msk->pm.lock);

	list_क्रम_each_entry_safe(entry, पंचांगp, &मुक्त_list, list) अणु
		sk_stop_समयr_sync(sk, &entry->add_समयr);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल व्योम mptcp_pm_create_subflow_or_संकेत_addr(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा mptcp_pm_addr_entry *local;
	अचिन्हित पूर्णांक add_addr_संकेत_max;
	अचिन्हित पूर्णांक local_addr_max;
	काष्ठा pm_nl_pernet *pernet;
	अचिन्हित पूर्णांक subflows_max;

	pernet = net_generic(sock_net(sk), pm_nl_pernet_id);

	add_addr_संकेत_max = mptcp_pm_get_add_addr_संकेत_max(msk);
	local_addr_max = mptcp_pm_get_local_addr_max(msk);
	subflows_max = mptcp_pm_get_subflows_max(msk);

	pr_debug("local %d:%d signal %d:%d subflows %d:%d\n",
		 msk->pm.local_addr_used, local_addr_max,
		 msk->pm.add_addr_संकेतed, add_addr_संकेत_max,
		 msk->pm.subflows, subflows_max);

	/* check first क्रम announce */
	अगर (msk->pm.add_addr_संकेतed < add_addr_संकेत_max) अणु
		local = select_संकेत_address(pernet,
					      msk->pm.add_addr_संकेतed);

		अगर (local) अणु
			अगर (mptcp_pm_alloc_anno_list(msk, local)) अणु
				msk->pm.add_addr_संकेतed++;
				mptcp_pm_announce_addr(msk, &local->addr, false);
				mptcp_pm_nl_addr_send_ack(msk);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* pick failed, aव्योम fourther attempts later */
			msk->pm.local_addr_used = add_addr_संकेत_max;
		पूर्ण

		check_work_pending(msk);
	पूर्ण

	/* check अगर should create a new subflow */
	अगर (msk->pm.local_addr_used < local_addr_max &&
	    msk->pm.subflows < subflows_max) अणु
		local = select_local_address(pernet, msk);
		अगर (local) अणु
			काष्ठा mptcp_addr_info remote = अणु 0 पूर्ण;

			msk->pm.local_addr_used++;
			msk->pm.subflows++;
			check_work_pending(msk);
			remote_address((काष्ठा sock_common *)sk, &remote);
			spin_unlock_bh(&msk->pm.lock);
			__mptcp_subflow_connect(sk, &local->addr, &remote,
						local->flags, local->अगरindex);
			spin_lock_bh(&msk->pm.lock);
			वापस;
		पूर्ण

		/* lookup failed, aव्योम fourther attempts later */
		msk->pm.local_addr_used = local_addr_max;
		check_work_pending(msk);
	पूर्ण
पूर्ण

अटल व्योम mptcp_pm_nl_fully_established(काष्ठा mptcp_sock *msk)
अणु
	mptcp_pm_create_subflow_or_संकेत_addr(msk);
पूर्ण

अटल व्योम mptcp_pm_nl_subflow_established(काष्ठा mptcp_sock *msk)
अणु
	mptcp_pm_create_subflow_or_संकेत_addr(msk);
पूर्ण

अटल व्योम mptcp_pm_nl_add_addr_received(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	अचिन्हित पूर्णांक add_addr_accept_max;
	काष्ठा mptcp_addr_info remote;
	काष्ठा mptcp_addr_info local;
	अचिन्हित पूर्णांक subflows_max;

	add_addr_accept_max = mptcp_pm_get_add_addr_accept_max(msk);
	subflows_max = mptcp_pm_get_subflows_max(msk);

	pr_debug("accepted %d:%d remote family %d",
		 msk->pm.add_addr_accepted, add_addr_accept_max,
		 msk->pm.remote.family);

	अगर (lookup_subflow_by_daddr(&msk->conn_list, &msk->pm.remote))
		जाओ add_addr_echo;

	msk->pm.add_addr_accepted++;
	msk->pm.subflows++;
	अगर (msk->pm.add_addr_accepted >= add_addr_accept_max ||
	    msk->pm.subflows >= subflows_max)
		WRITE_ONCE(msk->pm.accept_addr, false);

	/* connect to the specअगरied remote address, using whatever
	 * local address the routing configuration will pick.
	 */
	remote = msk->pm.remote;
	अगर (!remote.port)
		remote.port = sk->sk_dport;
	स_रखो(&local, 0, माप(local));
	local.family = remote.family;

	spin_unlock_bh(&msk->pm.lock);
	__mptcp_subflow_connect(sk, &local, &remote, 0, 0);
	spin_lock_bh(&msk->pm.lock);

add_addr_echo:
	mptcp_pm_announce_addr(msk, &msk->pm.remote, true);
	mptcp_pm_nl_addr_send_ack(msk);
पूर्ण

व्योम mptcp_pm_nl_addr_send_ack(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;

	msk_owned_by_me(msk);
	lockdep_निश्चित_held(&msk->pm.lock);

	अगर (!mptcp_pm_should_add_संकेत(msk) &&
	    !mptcp_pm_should_rm_संकेत(msk))
		वापस;

	__mptcp_flush_join_list(msk);
	subflow = list_first_entry_or_null(&msk->conn_list, typeof(*subflow), node);
	अगर (subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

		spin_unlock_bh(&msk->pm.lock);
		pr_debug("send ack for %s%s%s",
			 mptcp_pm_should_add_संकेत(msk) ? "add_addr" : "rm_addr",
			 mptcp_pm_should_add_संकेत_ipv6(msk) ? " [ipv6]" : "",
			 mptcp_pm_should_add_संकेत_port(msk) ? " [port]" : "");

		lock_sock(ssk);
		tcp_send_ack(ssk);
		release_sock(ssk);
		spin_lock_bh(&msk->pm.lock);
	पूर्ण
पूर्ण

पूर्णांक mptcp_pm_nl_mp_prio_send_ack(काष्ठा mptcp_sock *msk,
				 काष्ठा mptcp_addr_info *addr,
				 u8 bkup)
अणु
	काष्ठा mptcp_subflow_context *subflow;

	pr_debug("bkup=%d", bkup);

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		काष्ठा sock *sk = (काष्ठा sock *)msk;
		काष्ठा mptcp_addr_info local;

		local_address((काष्ठा sock_common *)ssk, &local);
		अगर (!addresses_equal(&local, addr, addr->port))
			जारी;

		subflow->backup = bkup;
		subflow->send_mp_prio = 1;
		subflow->request_bkup = bkup;
		__MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPPRIOTX);

		spin_unlock_bh(&msk->pm.lock);
		pr_debug("send ack for mp_prio");
		lock_sock(ssk);
		tcp_send_ack(ssk);
		release_sock(ssk);
		spin_lock_bh(&msk->pm.lock);

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम mptcp_pm_nl_rm_addr_or_subflow(काष्ठा mptcp_sock *msk,
					   स्थिर काष्ठा mptcp_rm_list *rm_list,
					   क्रमागत linux_mptcp_mib_field rm_type)
अणु
	काष्ठा mptcp_subflow_context *subflow, *पंचांगp;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	u8 i;

	pr_debug("%s rm_list_nr %d",
		 rm_type == MPTCP_MIB_RMADDR ? "address" : "subflow", rm_list->nr);

	msk_owned_by_me(msk);

	अगर (!rm_list->nr)
		वापस;

	अगर (list_empty(&msk->conn_list))
		वापस;

	क्रम (i = 0; i < rm_list->nr; i++) अणु
		list_क्रम_each_entry_safe(subflow, पंचांगp, &msk->conn_list, node) अणु
			काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
			पूर्णांक how = RCV_SHUTDOWN | SEND_SHUTDOWN;
			u8 id = subflow->local_id;

			अगर (rm_type == MPTCP_MIB_RMADDR)
				id = subflow->remote_id;

			अगर (rm_list->ids[i] != id)
				जारी;

			pr_debug(" -> %s rm_list_ids[%d]=%u local_id=%u remote_id=%u",
				 rm_type == MPTCP_MIB_RMADDR ? "address" : "subflow",
				 i, rm_list->ids[i], subflow->local_id, subflow->remote_id);
			spin_unlock_bh(&msk->pm.lock);
			mptcp_subflow_shutकरोwn(sk, ssk, how);
			mptcp_बंद_ssk(sk, ssk, subflow);
			spin_lock_bh(&msk->pm.lock);

			अगर (rm_type == MPTCP_MIB_RMADDR) अणु
				msk->pm.add_addr_accepted--;
				WRITE_ONCE(msk->pm.accept_addr, true);
			पूर्ण अन्यथा अगर (rm_type == MPTCP_MIB_RMSUBFLOW) अणु
				msk->pm.local_addr_used--;
			पूर्ण
			msk->pm.subflows--;
			__MPTCP_INC_STATS(sock_net(sk), rm_type);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mptcp_pm_nl_rm_addr_received(काष्ठा mptcp_sock *msk)
अणु
	mptcp_pm_nl_rm_addr_or_subflow(msk, &msk->pm.rm_list_rx, MPTCP_MIB_RMADDR);
पूर्ण

व्योम mptcp_pm_nl_rm_subflow_received(काष्ठा mptcp_sock *msk,
				     स्थिर काष्ठा mptcp_rm_list *rm_list)
अणु
	mptcp_pm_nl_rm_addr_or_subflow(msk, rm_list, MPTCP_MIB_RMSUBFLOW);
पूर्ण

व्योम mptcp_pm_nl_work(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;

	msk_owned_by_me(msk);

	spin_lock_bh(&msk->pm.lock);

	pr_debug("msk=%p status=%x", msk, pm->status);
	अगर (pm->status & BIT(MPTCP_PM_ADD_ADDR_RECEIVED)) अणु
		pm->status &= ~BIT(MPTCP_PM_ADD_ADDR_RECEIVED);
		mptcp_pm_nl_add_addr_received(msk);
	पूर्ण
	अगर (pm->status & BIT(MPTCP_PM_ADD_ADDR_SEND_ACK)) अणु
		pm->status &= ~BIT(MPTCP_PM_ADD_ADDR_SEND_ACK);
		mptcp_pm_nl_addr_send_ack(msk);
	पूर्ण
	अगर (pm->status & BIT(MPTCP_PM_RM_ADDR_RECEIVED)) अणु
		pm->status &= ~BIT(MPTCP_PM_RM_ADDR_RECEIVED);
		mptcp_pm_nl_rm_addr_received(msk);
	पूर्ण
	अगर (pm->status & BIT(MPTCP_PM_ESTABLISHED)) अणु
		pm->status &= ~BIT(MPTCP_PM_ESTABLISHED);
		mptcp_pm_nl_fully_established(msk);
	पूर्ण
	अगर (pm->status & BIT(MPTCP_PM_SUBFLOW_ESTABLISHED)) अणु
		pm->status &= ~BIT(MPTCP_PM_SUBFLOW_ESTABLISHED);
		mptcp_pm_nl_subflow_established(msk);
	पूर्ण

	spin_unlock_bh(&msk->pm.lock);
पूर्ण

अटल bool address_use_port(काष्ठा mptcp_pm_addr_entry *entry)
अणु
	वापस (entry->flags &
		(MPTCP_PM_ADDR_FLAG_SIGNAL | MPTCP_PM_ADDR_FLAG_SUBFLOW)) ==
		MPTCP_PM_ADDR_FLAG_SIGNAL;
पूर्ण

अटल पूर्णांक mptcp_pm_nl_append_new_local_addr(काष्ठा pm_nl_pernet *pernet,
					     काष्ठा mptcp_pm_addr_entry *entry)
अणु
	काष्ठा mptcp_pm_addr_entry *cur;
	अचिन्हित पूर्णांक addr_max;
	पूर्णांक ret = -EINVAL;

	spin_lock_bh(&pernet->lock);
	/* to keep the code simple, करोn't करो IDR-like allocation क्रम address ID,
	 * just bail when we exceed limits
	 */
	अगर (pernet->next_id == MAX_ADDR_ID)
		pernet->next_id = 1;
	अगर (pernet->addrs >= MPTCP_PM_ADDR_MAX)
		जाओ out;
	अगर (test_bit(entry->addr.id, pernet->id_biपंचांगap))
		जाओ out;

	/* करो not insert duplicate address, dअगरferentiate on port only
	 * singled addresses
	 */
	list_क्रम_each_entry(cur, &pernet->local_addr_list, list) अणु
		अगर (addresses_equal(&cur->addr, &entry->addr,
				    address_use_port(entry) &&
				    address_use_port(cur)))
			जाओ out;
	पूर्ण

	अगर (!entry->addr.id) अणु
find_next:
		entry->addr.id = find_next_zero_bit(pernet->id_biपंचांगap,
						    MAX_ADDR_ID + 1,
						    pernet->next_id);
		अगर ((!entry->addr.id || entry->addr.id > MAX_ADDR_ID) &&
		    pernet->next_id != 1) अणु
			pernet->next_id = 1;
			जाओ find_next;
		पूर्ण
	पूर्ण

	अगर (!entry->addr.id || entry->addr.id > MAX_ADDR_ID)
		जाओ out;

	__set_bit(entry->addr.id, pernet->id_biपंचांगap);
	अगर (entry->addr.id > pernet->next_id)
		pernet->next_id = entry->addr.id;

	अगर (entry->flags & MPTCP_PM_ADDR_FLAG_SIGNAL) अणु
		addr_max = pernet->add_addr_संकेत_max;
		WRITE_ONCE(pernet->add_addr_संकेत_max, addr_max + 1);
	पूर्ण
	अगर (entry->flags & MPTCP_PM_ADDR_FLAG_SUBFLOW) अणु
		addr_max = pernet->local_addr_max;
		WRITE_ONCE(pernet->local_addr_max, addr_max + 1);
	पूर्ण

	pernet->addrs++;
	list_add_tail_rcu(&entry->list, &pernet->local_addr_list);
	ret = entry->addr.id;

out:
	spin_unlock_bh(&pernet->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mptcp_pm_nl_create_listen_socket(काष्ठा sock *sk,
					    काष्ठा mptcp_pm_addr_entry *entry)
अणु
	काष्ठा sockaddr_storage addr;
	काष्ठा mptcp_sock *msk;
	काष्ठा socket *ssock;
	पूर्णांक backlog = 1024;
	पूर्णांक err;

	err = sock_create_kern(sock_net(sk), entry->addr.family,
			       SOCK_STREAM, IPPROTO_MPTCP, &entry->lsk);
	अगर (err)
		वापस err;

	msk = mptcp_sk(entry->lsk->sk);
	अगर (!msk) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ssock = __mptcp_nmpc_socket(msk);
	अगर (!ssock) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	mptcp_info2sockaddr(&entry->addr, &addr, entry->addr.family);
	err = kernel_bind(ssock, (काष्ठा sockaddr *)&addr,
			  माप(काष्ठा sockaddr_in));
	अगर (err) अणु
		pr_warn("kernel_bind error, err=%d", err);
		जाओ out;
	पूर्ण

	err = kernel_listen(ssock, backlog);
	अगर (err) अणु
		pr_warn("kernel_listen error, err=%d", err);
		जाओ out;
	पूर्ण

	वापस 0;

out:
	sock_release(entry->lsk);
	वापस err;
पूर्ण

पूर्णांक mptcp_pm_nl_get_local_id(काष्ठा mptcp_sock *msk, काष्ठा sock_common *skc)
अणु
	काष्ठा mptcp_pm_addr_entry *entry;
	काष्ठा mptcp_addr_info skc_local;
	काष्ठा mptcp_addr_info msk_local;
	काष्ठा pm_nl_pernet *pernet;
	पूर्णांक ret = -1;

	अगर (WARN_ON_ONCE(!msk))
		वापस -1;

	/* The 0 ID mapping is defined by the first subflow, copied पूर्णांकo the msk
	 * addr
	 */
	local_address((काष्ठा sock_common *)msk, &msk_local);
	local_address((काष्ठा sock_common *)skc, &skc_local);
	अगर (addresses_equal(&msk_local, &skc_local, false))
		वापस 0;

	अगर (address_zero(&skc_local))
		वापस 0;

	pernet = net_generic(sock_net((काष्ठा sock *)msk), pm_nl_pernet_id);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(entry, &pernet->local_addr_list, list) अणु
		अगर (addresses_equal(&entry->addr, &skc_local, entry->addr.port)) अणु
			ret = entry->addr.id;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (ret >= 0)
		वापस ret;

	/* address not found, add to local list */
	entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;

	entry->addr = skc_local;
	entry->addr.id = 0;
	entry->addr.port = 0;
	entry->अगरindex = 0;
	entry->flags = 0;
	entry->lsk = शून्य;
	ret = mptcp_pm_nl_append_new_local_addr(pernet, entry);
	अगर (ret < 0)
		kमुक्त(entry);

	वापस ret;
पूर्ण

व्योम mptcp_pm_nl_data_init(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_pm_data *pm = &msk->pm;
	bool subflows;

	subflows = !!mptcp_pm_get_subflows_max(msk);
	WRITE_ONCE(pm->work_pending, (!!mptcp_pm_get_local_addr_max(msk) && subflows) ||
		   !!mptcp_pm_get_add_addr_संकेत_max(msk));
	WRITE_ONCE(pm->accept_addr, !!mptcp_pm_get_add_addr_accept_max(msk) && subflows);
	WRITE_ONCE(pm->accept_subflow, subflows);
पूर्ण

#घोषणा MPTCP_PM_CMD_GRP_OFFSET       0
#घोषणा MPTCP_PM_EV_GRP_OFFSET        1

अटल स्थिर काष्ठा genl_multicast_group mptcp_pm_mcgrps[] = अणु
	[MPTCP_PM_CMD_GRP_OFFSET]	= अणु .name = MPTCP_PM_CMD_GRP_NAME, पूर्ण,
	[MPTCP_PM_EV_GRP_OFFSET]        = अणु .name = MPTCP_PM_EV_GRP_NAME,
					    .flags = GENL_UNS_ADMIN_PERM,
					  पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
mptcp_pm_addr_policy[MPTCP_PM_ADDR_ATTR_MAX + 1] = अणु
	[MPTCP_PM_ADDR_ATTR_FAMILY]	= अणु .type	= NLA_U16,	पूर्ण,
	[MPTCP_PM_ADDR_ATTR_ID]		= अणु .type	= NLA_U8,	पूर्ण,
	[MPTCP_PM_ADDR_ATTR_ADDR4]	= अणु .type	= NLA_U32,	पूर्ण,
	[MPTCP_PM_ADDR_ATTR_ADDR6]	=
		NLA_POLICY_EXACT_LEN(माप(काष्ठा in6_addr)),
	[MPTCP_PM_ADDR_ATTR_PORT]	= अणु .type	= NLA_U16	पूर्ण,
	[MPTCP_PM_ADDR_ATTR_FLAGS]	= अणु .type	= NLA_U32	पूर्ण,
	[MPTCP_PM_ADDR_ATTR_IF_IDX]     = अणु .type	= NLA_S32	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy mptcp_pm_policy[MPTCP_PM_ATTR_MAX + 1] = अणु
	[MPTCP_PM_ATTR_ADDR]		=
					NLA_POLICY_NESTED(mptcp_pm_addr_policy),
	[MPTCP_PM_ATTR_RCV_ADD_ADDRS]	= अणु .type	= NLA_U32,	पूर्ण,
	[MPTCP_PM_ATTR_SUBFLOWS]	= अणु .type	= NLA_U32,	पूर्ण,
पूर्ण;

अटल पूर्णांक mptcp_pm_family_to_addr(पूर्णांक family)
अणु
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अगर (family == AF_INET6)
		वापस MPTCP_PM_ADDR_ATTR_ADDR6;
#पूर्ण_अगर
	वापस MPTCP_PM_ADDR_ATTR_ADDR4;
पूर्ण

अटल पूर्णांक mptcp_pm_parse_addr(काष्ठा nlattr *attr, काष्ठा genl_info *info,
			       bool require_family,
			       काष्ठा mptcp_pm_addr_entry *entry)
अणु
	काष्ठा nlattr *tb[MPTCP_PM_ADDR_ATTR_MAX + 1];
	पूर्णांक err, addr_addr;

	अगर (!attr) अणु
		GENL_SET_ERR_MSG(info, "missing address info");
		वापस -EINVAL;
	पूर्ण

	/* no validation needed - was alपढ़ोy करोne via nested policy */
	err = nla_parse_nested_deprecated(tb, MPTCP_PM_ADDR_ATTR_MAX, attr,
					  mptcp_pm_addr_policy, info->extack);
	अगर (err)
		वापस err;

	स_रखो(entry, 0, माप(*entry));
	अगर (!tb[MPTCP_PM_ADDR_ATTR_FAMILY]) अणु
		अगर (!require_family)
			जाओ skip_family;

		NL_SET_ERR_MSG_ATTR(info->extack, attr,
				    "missing family");
		वापस -EINVAL;
	पूर्ण

	entry->addr.family = nla_get_u16(tb[MPTCP_PM_ADDR_ATTR_FAMILY]);
	अगर (entry->addr.family != AF_INET
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	    && entry->addr.family != AF_INET6
#पूर्ण_अगर
	    ) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, attr,
				    "unknown address family");
		वापस -EINVAL;
	पूर्ण
	addr_addr = mptcp_pm_family_to_addr(entry->addr.family);
	अगर (!tb[addr_addr]) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, attr,
				    "missing address data");
		वापस -EINVAL;
	पूर्ण

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अगर (entry->addr.family == AF_INET6)
		entry->addr.addr6 = nla_get_in6_addr(tb[addr_addr]);
	अन्यथा
#पूर्ण_अगर
		entry->addr.addr.s_addr = nla_get_in_addr(tb[addr_addr]);

skip_family:
	अगर (tb[MPTCP_PM_ADDR_ATTR_IF_IDX]) अणु
		u32 val = nla_get_s32(tb[MPTCP_PM_ADDR_ATTR_IF_IDX]);

		entry->अगरindex = val;
	पूर्ण

	अगर (tb[MPTCP_PM_ADDR_ATTR_ID])
		entry->addr.id = nla_get_u8(tb[MPTCP_PM_ADDR_ATTR_ID]);

	अगर (tb[MPTCP_PM_ADDR_ATTR_FLAGS])
		entry->flags = nla_get_u32(tb[MPTCP_PM_ADDR_ATTR_FLAGS]);

	अगर (tb[MPTCP_PM_ADDR_ATTR_PORT])
		entry->addr.port = htons(nla_get_u16(tb[MPTCP_PM_ADDR_ATTR_PORT]));

	वापस 0;
पूर्ण

अटल काष्ठा pm_nl_pernet *genl_info_pm_nl(काष्ठा genl_info *info)
अणु
	वापस net_generic(genl_info_net(info), pm_nl_pernet_id);
पूर्ण

अटल पूर्णांक mptcp_nl_add_subflow_or_संकेत_addr(काष्ठा net *net)
अणु
	काष्ठा mptcp_sock *msk;
	दीर्घ s_slot = 0, s_num = 0;

	जबतक ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != शून्य) अणु
		काष्ठा sock *sk = (काष्ठा sock *)msk;

		अगर (!READ_ONCE(msk->fully_established))
			जाओ next;

		lock_sock(sk);
		spin_lock_bh(&msk->pm.lock);
		mptcp_pm_create_subflow_or_संकेत_addr(msk);
		spin_unlock_bh(&msk->pm.lock);
		release_sock(sk);

next:
		sock_put(sk);
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_nl_cmd_add_addr(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	काष्ठा pm_nl_pernet *pernet = genl_info_pm_nl(info);
	काष्ठा mptcp_pm_addr_entry addr, *entry;
	पूर्णांक ret;

	ret = mptcp_pm_parse_addr(attr, info, true, &addr);
	अगर (ret < 0)
		वापस ret;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		GENL_SET_ERR_MSG(info, "can't allocate addr");
		वापस -ENOMEM;
	पूर्ण

	*entry = addr;
	अगर (entry->addr.port) अणु
		ret = mptcp_pm_nl_create_listen_socket(skb->sk, entry);
		अगर (ret) अणु
			GENL_SET_ERR_MSG(info, "create listen socket error");
			kमुक्त(entry);
			वापस ret;
		पूर्ण
	पूर्ण
	ret = mptcp_pm_nl_append_new_local_addr(pernet, entry);
	अगर (ret < 0) अणु
		GENL_SET_ERR_MSG(info, "too many addresses or duplicate one");
		अगर (entry->lsk)
			sock_release(entry->lsk);
		kमुक्त(entry);
		वापस ret;
	पूर्ण

	mptcp_nl_add_subflow_or_संकेत_addr(sock_net(skb->sk));

	वापस 0;
पूर्ण

अटल काष्ठा mptcp_pm_addr_entry *
__lookup_addr_by_id(काष्ठा pm_nl_pernet *pernet, अचिन्हित पूर्णांक id)
अणु
	काष्ठा mptcp_pm_addr_entry *entry;

	list_क्रम_each_entry(entry, &pernet->local_addr_list, list) अणु
		अगर (entry->addr.id == id)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool हटाओ_anno_list_by_saddr(काष्ठा mptcp_sock *msk,
				      काष्ठा mptcp_addr_info *addr)
अणु
	काष्ठा mptcp_pm_add_entry *entry;

	entry = mptcp_pm_del_add_समयr(msk, addr, false);
	अगर (entry) अणु
		list_del(&entry->list);
		kमुक्त(entry);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool mptcp_pm_हटाओ_anno_addr(काष्ठा mptcp_sock *msk,
				      काष्ठा mptcp_addr_info *addr,
				      bool क्रमce)
अणु
	काष्ठा mptcp_rm_list list = अणु .nr = 0 पूर्ण;
	bool ret;

	list.ids[list.nr++] = addr->id;

	ret = हटाओ_anno_list_by_saddr(msk, addr);
	अगर (ret || क्रमce) अणु
		spin_lock_bh(&msk->pm.lock);
		mptcp_pm_हटाओ_addr(msk, &list);
		spin_unlock_bh(&msk->pm.lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mptcp_nl_हटाओ_subflow_and_संकेत_addr(काष्ठा net *net,
						   काष्ठा mptcp_addr_info *addr)
अणु
	काष्ठा mptcp_sock *msk;
	दीर्घ s_slot = 0, s_num = 0;
	काष्ठा mptcp_rm_list list = अणु .nr = 0 पूर्ण;

	pr_debug("remove_id=%d", addr->id);

	list.ids[list.nr++] = addr->id;

	जबतक ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != शून्य) अणु
		काष्ठा sock *sk = (काष्ठा sock *)msk;
		bool हटाओ_subflow;

		अगर (list_empty(&msk->conn_list)) अणु
			mptcp_pm_हटाओ_anno_addr(msk, addr, false);
			जाओ next;
		पूर्ण

		lock_sock(sk);
		हटाओ_subflow = lookup_subflow_by_saddr(&msk->conn_list, addr);
		mptcp_pm_हटाओ_anno_addr(msk, addr, हटाओ_subflow);
		अगर (हटाओ_subflow)
			mptcp_pm_हटाओ_subflow(msk, &list);
		release_sock(sk);

next:
		sock_put(sk);
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा addr_entry_release_work अणु
	काष्ठा rcu_work	rwork;
	काष्ठा mptcp_pm_addr_entry *entry;
पूर्ण;

अटल व्योम mptcp_pm_release_addr_entry(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा addr_entry_release_work *w;
	काष्ठा mptcp_pm_addr_entry *entry;

	w = container_of(to_rcu_work(work), काष्ठा addr_entry_release_work, rwork);
	entry = w->entry;
	अगर (entry) अणु
		अगर (entry->lsk)
			sock_release(entry->lsk);
		kमुक्त(entry);
	पूर्ण
	kमुक्त(w);
पूर्ण

अटल व्योम mptcp_pm_मुक्त_addr_entry(काष्ठा mptcp_pm_addr_entry *entry)
अणु
	काष्ठा addr_entry_release_work *w;

	w = kदो_स्मृति(माप(*w), GFP_ATOMIC);
	अगर (w) अणु
		INIT_RCU_WORK(&w->rwork, mptcp_pm_release_addr_entry);
		w->entry = entry;
		queue_rcu_work(प्रणाली_wq, &w->rwork);
	पूर्ण
पूर्ण

अटल पूर्णांक mptcp_nl_हटाओ_id_zero_address(काष्ठा net *net,
					   काष्ठा mptcp_addr_info *addr)
अणु
	काष्ठा mptcp_rm_list list = अणु .nr = 0 पूर्ण;
	दीर्घ s_slot = 0, s_num = 0;
	काष्ठा mptcp_sock *msk;

	list.ids[list.nr++] = 0;

	जबतक ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != शून्य) अणु
		काष्ठा sock *sk = (काष्ठा sock *)msk;
		काष्ठा mptcp_addr_info msk_local;

		अगर (list_empty(&msk->conn_list))
			जाओ next;

		local_address((काष्ठा sock_common *)msk, &msk_local);
		अगर (!addresses_equal(&msk_local, addr, addr->port))
			जाओ next;

		lock_sock(sk);
		spin_lock_bh(&msk->pm.lock);
		mptcp_pm_हटाओ_addr(msk, &list);
		mptcp_pm_nl_rm_subflow_received(msk, &list);
		spin_unlock_bh(&msk->pm.lock);
		release_sock(sk);

next:
		sock_put(sk);
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_nl_cmd_del_addr(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	काष्ठा pm_nl_pernet *pernet = genl_info_pm_nl(info);
	काष्ठा mptcp_pm_addr_entry addr, *entry;
	अचिन्हित पूर्णांक addr_max;
	पूर्णांक ret;

	ret = mptcp_pm_parse_addr(attr, info, false, &addr);
	अगर (ret < 0)
		वापस ret;

	/* the zero id address is special: the first address used by the msk
	 * always माला_लो such an id, so dअगरferent subflows can have dअगरferent zero
	 * id addresses. Additionally zero id is not accounted क्रम in id_biपंचांगap.
	 * Let's use an 'mptcp_rm_list' instead of the common हटाओ code.
	 */
	अगर (addr.addr.id == 0)
		वापस mptcp_nl_हटाओ_id_zero_address(sock_net(skb->sk), &addr.addr);

	spin_lock_bh(&pernet->lock);
	entry = __lookup_addr_by_id(pernet, addr.addr.id);
	अगर (!entry) अणु
		GENL_SET_ERR_MSG(info, "address not found");
		spin_unlock_bh(&pernet->lock);
		वापस -EINVAL;
	पूर्ण
	अगर (entry->flags & MPTCP_PM_ADDR_FLAG_SIGNAL) अणु
		addr_max = pernet->add_addr_संकेत_max;
		WRITE_ONCE(pernet->add_addr_संकेत_max, addr_max - 1);
	पूर्ण
	अगर (entry->flags & MPTCP_PM_ADDR_FLAG_SUBFLOW) अणु
		addr_max = pernet->local_addr_max;
		WRITE_ONCE(pernet->local_addr_max, addr_max - 1);
	पूर्ण

	pernet->addrs--;
	list_del_rcu(&entry->list);
	__clear_bit(entry->addr.id, pernet->id_biपंचांगap);
	spin_unlock_bh(&pernet->lock);

	mptcp_nl_हटाओ_subflow_and_संकेत_addr(sock_net(skb->sk), &entry->addr);
	mptcp_pm_मुक्त_addr_entry(entry);

	वापस ret;
पूर्ण

अटल व्योम mptcp_pm_हटाओ_addrs_and_subflows(काष्ठा mptcp_sock *msk,
					       काष्ठा list_head *rm_list)
अणु
	काष्ठा mptcp_rm_list alist = अणु .nr = 0 पूर्ण, slist = अणु .nr = 0 पूर्ण;
	काष्ठा mptcp_pm_addr_entry *entry;

	list_क्रम_each_entry(entry, rm_list, list) अणु
		अगर (lookup_subflow_by_saddr(&msk->conn_list, &entry->addr) &&
		    alist.nr < MPTCP_RM_IDS_MAX &&
		    slist.nr < MPTCP_RM_IDS_MAX) अणु
			alist.ids[alist.nr++] = entry->addr.id;
			slist.ids[slist.nr++] = entry->addr.id;
		पूर्ण अन्यथा अगर (हटाओ_anno_list_by_saddr(msk, &entry->addr) &&
			 alist.nr < MPTCP_RM_IDS_MAX) अणु
			alist.ids[alist.nr++] = entry->addr.id;
		पूर्ण
	पूर्ण

	अगर (alist.nr) अणु
		spin_lock_bh(&msk->pm.lock);
		mptcp_pm_हटाओ_addr(msk, &alist);
		spin_unlock_bh(&msk->pm.lock);
	पूर्ण
	अगर (slist.nr)
		mptcp_pm_हटाओ_subflow(msk, &slist);
पूर्ण

अटल व्योम mptcp_nl_हटाओ_addrs_list(काष्ठा net *net,
				       काष्ठा list_head *rm_list)
अणु
	दीर्घ s_slot = 0, s_num = 0;
	काष्ठा mptcp_sock *msk;

	अगर (list_empty(rm_list))
		वापस;

	जबतक ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != शून्य) अणु
		काष्ठा sock *sk = (काष्ठा sock *)msk;

		lock_sock(sk);
		mptcp_pm_हटाओ_addrs_and_subflows(msk, rm_list);
		release_sock(sk);

		sock_put(sk);
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम __flush_addrs(काष्ठा list_head *list)
अणु
	जबतक (!list_empty(list)) अणु
		काष्ठा mptcp_pm_addr_entry *cur;

		cur = list_entry(list->next,
				 काष्ठा mptcp_pm_addr_entry, list);
		list_del_rcu(&cur->list);
		mptcp_pm_मुक्त_addr_entry(cur);
	पूर्ण
पूर्ण

अटल व्योम __reset_counters(काष्ठा pm_nl_pernet *pernet)
अणु
	WRITE_ONCE(pernet->add_addr_संकेत_max, 0);
	WRITE_ONCE(pernet->add_addr_accept_max, 0);
	WRITE_ONCE(pernet->local_addr_max, 0);
	pernet->addrs = 0;
पूर्ण

अटल पूर्णांक mptcp_nl_cmd_flush_addrs(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा pm_nl_pernet *pernet = genl_info_pm_nl(info);
	LIST_HEAD(मुक्त_list);

	spin_lock_bh(&pernet->lock);
	list_splice_init(&pernet->local_addr_list, &मुक्त_list);
	__reset_counters(pernet);
	pernet->next_id = 1;
	biपंचांगap_zero(pernet->id_biपंचांगap, MAX_ADDR_ID + 1);
	spin_unlock_bh(&pernet->lock);
	mptcp_nl_हटाओ_addrs_list(sock_net(skb->sk), &मुक्त_list);
	__flush_addrs(&मुक्त_list);
	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_nl_fill_addr(काष्ठा sk_buff *skb,
			      काष्ठा mptcp_pm_addr_entry *entry)
अणु
	काष्ठा mptcp_addr_info *addr = &entry->addr;
	काष्ठा nlattr *attr;

	attr = nla_nest_start(skb, MPTCP_PM_ATTR_ADDR);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u16(skb, MPTCP_PM_ADDR_ATTR_FAMILY, addr->family))
		जाओ nla_put_failure;
	अगर (nla_put_u16(skb, MPTCP_PM_ADDR_ATTR_PORT, ntohs(addr->port)))
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, MPTCP_PM_ADDR_ATTR_ID, addr->id))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, MPTCP_PM_ADDR_ATTR_FLAGS, entry->flags))
		जाओ nla_put_failure;
	अगर (entry->अगरindex &&
	    nla_put_s32(skb, MPTCP_PM_ADDR_ATTR_IF_IDX, entry->अगरindex))
		जाओ nla_put_failure;

	अगर (addr->family == AF_INET &&
	    nla_put_in_addr(skb, MPTCP_PM_ADDR_ATTR_ADDR4,
			    addr->addr.s_addr))
		जाओ nla_put_failure;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अन्यथा अगर (addr->family == AF_INET6 &&
		 nla_put_in6_addr(skb, MPTCP_PM_ADDR_ATTR_ADDR6, &addr->addr6))
		जाओ nla_put_failure;
#पूर्ण_अगर
	nla_nest_end(skb, attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक mptcp_nl_cmd_get_addr(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	काष्ठा pm_nl_pernet *pernet = genl_info_pm_nl(info);
	काष्ठा mptcp_pm_addr_entry addr, *entry;
	काष्ठा sk_buff *msg;
	व्योम *reply;
	पूर्णांक ret;

	ret = mptcp_pm_parse_addr(attr, info, false, &addr);
	अगर (ret < 0)
		वापस ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	reply = genlmsg_put_reply(msg, info, &mptcp_genl_family, 0,
				  info->genlhdr->cmd);
	अगर (!reply) अणु
		GENL_SET_ERR_MSG(info, "not enough space in Netlink message");
		ret = -EMSGSIZE;
		जाओ fail;
	पूर्ण

	spin_lock_bh(&pernet->lock);
	entry = __lookup_addr_by_id(pernet, addr.addr.id);
	अगर (!entry) अणु
		GENL_SET_ERR_MSG(info, "address not found");
		ret = -EINVAL;
		जाओ unlock_fail;
	पूर्ण

	ret = mptcp_nl_fill_addr(msg, entry);
	अगर (ret)
		जाओ unlock_fail;

	genlmsg_end(msg, reply);
	ret = genlmsg_reply(msg, info);
	spin_unlock_bh(&pernet->lock);
	वापस ret;

unlock_fail:
	spin_unlock_bh(&pernet->lock);

fail:
	nlmsg_मुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक mptcp_nl_cmd_dump_addrs(काष्ठा sk_buff *msg,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(msg->sk);
	काष्ठा mptcp_pm_addr_entry *entry;
	काष्ठा pm_nl_pernet *pernet;
	पूर्णांक id = cb->args[0];
	व्योम *hdr;
	पूर्णांक i;

	pernet = net_generic(net, pm_nl_pernet_id);

	spin_lock_bh(&pernet->lock);
	क्रम (i = id; i < MAX_ADDR_ID + 1; i++) अणु
		अगर (test_bit(i, pernet->id_biपंचांगap)) अणु
			entry = __lookup_addr_by_id(pernet, i);
			अगर (!entry)
				अवरोध;

			अगर (entry->addr.id <= id)
				जारी;

			hdr = genlmsg_put(msg, NETLINK_CB(cb->skb).portid,
					  cb->nlh->nlmsg_seq, &mptcp_genl_family,
					  NLM_F_MULTI, MPTCP_PM_CMD_GET_ADDR);
			अगर (!hdr)
				अवरोध;

			अगर (mptcp_nl_fill_addr(msg, entry) < 0) अणु
				genlmsg_cancel(msg, hdr);
				अवरोध;
			पूर्ण

			id = entry->addr.id;
			genlmsg_end(msg, hdr);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pernet->lock);

	cb->args[0] = id;
	वापस msg->len;
पूर्ण

अटल पूर्णांक parse_limit(काष्ठा genl_info *info, पूर्णांक id, अचिन्हित पूर्णांक *limit)
अणु
	काष्ठा nlattr *attr = info->attrs[id];

	अगर (!attr)
		वापस 0;

	*limit = nla_get_u32(attr);
	अगर (*limit > MPTCP_PM_ADDR_MAX) अणु
		GENL_SET_ERR_MSG(info, "limit greater than maximum");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mptcp_nl_cmd_set_limits(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा pm_nl_pernet *pernet = genl_info_pm_nl(info);
	अचिन्हित पूर्णांक rcv_addrs, subflows;
	पूर्णांक ret;

	spin_lock_bh(&pernet->lock);
	rcv_addrs = pernet->add_addr_accept_max;
	ret = parse_limit(info, MPTCP_PM_ATTR_RCV_ADD_ADDRS, &rcv_addrs);
	अगर (ret)
		जाओ unlock;

	subflows = pernet->subflows_max;
	ret = parse_limit(info, MPTCP_PM_ATTR_SUBFLOWS, &subflows);
	अगर (ret)
		जाओ unlock;

	WRITE_ONCE(pernet->add_addr_accept_max, rcv_addrs);
	WRITE_ONCE(pernet->subflows_max, subflows);

unlock:
	spin_unlock_bh(&pernet->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
mptcp_nl_cmd_get_limits(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा pm_nl_pernet *pernet = genl_info_pm_nl(info);
	काष्ठा sk_buff *msg;
	व्योम *reply;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	reply = genlmsg_put_reply(msg, info, &mptcp_genl_family, 0,
				  MPTCP_PM_CMD_GET_LIMITS);
	अगर (!reply)
		जाओ fail;

	अगर (nla_put_u32(msg, MPTCP_PM_ATTR_RCV_ADD_ADDRS,
			READ_ONCE(pernet->add_addr_accept_max)))
		जाओ fail;

	अगर (nla_put_u32(msg, MPTCP_PM_ATTR_SUBFLOWS,
			READ_ONCE(pernet->subflows_max)))
		जाओ fail;

	genlmsg_end(msg, reply);
	वापस genlmsg_reply(msg, info);

fail:
	GENL_SET_ERR_MSG(info, "not enough space in Netlink message");
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक mptcp_nl_addr_backup(काष्ठा net *net,
				काष्ठा mptcp_addr_info *addr,
				u8 bkup)
अणु
	दीर्घ s_slot = 0, s_num = 0;
	काष्ठा mptcp_sock *msk;
	पूर्णांक ret = -EINVAL;

	जबतक ((msk = mptcp_token_iter_next(net, &s_slot, &s_num)) != शून्य) अणु
		काष्ठा sock *sk = (काष्ठा sock *)msk;

		अगर (list_empty(&msk->conn_list))
			जाओ next;

		lock_sock(sk);
		spin_lock_bh(&msk->pm.lock);
		ret = mptcp_pm_nl_mp_prio_send_ack(msk, addr, bkup);
		spin_unlock_bh(&msk->pm.lock);
		release_sock(sk);

next:
		sock_put(sk);
		cond_resched();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mptcp_nl_cmd_set_flags(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attr = info->attrs[MPTCP_PM_ATTR_ADDR];
	काष्ठा pm_nl_pernet *pernet = genl_info_pm_nl(info);
	काष्ठा mptcp_pm_addr_entry addr, *entry;
	काष्ठा net *net = sock_net(skb->sk);
	u8 bkup = 0;
	पूर्णांक ret;

	ret = mptcp_pm_parse_addr(attr, info, true, &addr);
	अगर (ret < 0)
		वापस ret;

	अगर (addr.flags & MPTCP_PM_ADDR_FLAG_BACKUP)
		bkup = 1;

	list_क्रम_each_entry(entry, &pernet->local_addr_list, list) अणु
		अगर (addresses_equal(&entry->addr, &addr.addr, true)) अणु
			ret = mptcp_nl_addr_backup(net, &entry->addr, bkup);
			अगर (ret)
				वापस ret;

			अगर (bkup)
				entry->flags |= MPTCP_PM_ADDR_FLAG_BACKUP;
			अन्यथा
				entry->flags &= ~MPTCP_PM_ADDR_FLAG_BACKUP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mptcp_nl_mcast_send(काष्ठा net *net, काष्ठा sk_buff *nlskb, gfp_t gfp)
अणु
	genlmsg_multicast_netns(&mptcp_genl_family, net,
				nlskb, 0, MPTCP_PM_EV_GRP_OFFSET, gfp);
पूर्ण

अटल पूर्णांक mptcp_event_add_subflow(काष्ठा sk_buff *skb, स्थिर काष्ठा sock *ssk)
अणु
	स्थिर काष्ठा inet_sock *issk = inet_sk(ssk);
	स्थिर काष्ठा mptcp_subflow_context *sf;

	अगर (nla_put_u16(skb, MPTCP_ATTR_FAMILY, ssk->sk_family))
		वापस -EMSGSIZE;

	चयन (ssk->sk_family) अणु
	हाल AF_INET:
		अगर (nla_put_in_addr(skb, MPTCP_ATTR_SADDR4, issk->inet_saddr))
			वापस -EMSGSIZE;
		अगर (nla_put_in_addr(skb, MPTCP_ATTR_DADDR4, issk->inet_daddr))
			वापस -EMSGSIZE;
		अवरोध;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	हाल AF_INET6: अणु
		स्थिर काष्ठा ipv6_pinfo *np = inet6_sk(ssk);

		अगर (nla_put_in6_addr(skb, MPTCP_ATTR_SADDR6, &np->saddr))
			वापस -EMSGSIZE;
		अगर (nla_put_in6_addr(skb, MPTCP_ATTR_DADDR6, &ssk->sk_v6_daddr))
			वापस -EMSGSIZE;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		WARN_ON_ONCE(1);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (nla_put_be16(skb, MPTCP_ATTR_SPORT, issk->inet_sport))
		वापस -EMSGSIZE;
	अगर (nla_put_be16(skb, MPTCP_ATTR_DPORT, issk->inet_dport))
		वापस -EMSGSIZE;

	sf = mptcp_subflow_ctx(ssk);
	अगर (WARN_ON_ONCE(!sf))
		वापस -EINVAL;

	अगर (nla_put_u8(skb, MPTCP_ATTR_LOC_ID, sf->local_id))
		वापस -EMSGSIZE;

	अगर (nla_put_u8(skb, MPTCP_ATTR_REM_ID, sf->remote_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_event_put_token_and_ssk(काष्ठा sk_buff *skb,
					 स्थिर काष्ठा mptcp_sock *msk,
					 स्थिर काष्ठा sock *ssk)
अणु
	स्थिर काष्ठा sock *sk = (स्थिर काष्ठा sock *)msk;
	स्थिर काष्ठा mptcp_subflow_context *sf;
	u8 sk_err;

	अगर (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token))
		वापस -EMSGSIZE;

	अगर (mptcp_event_add_subflow(skb, ssk))
		वापस -EMSGSIZE;

	sf = mptcp_subflow_ctx(ssk);
	अगर (WARN_ON_ONCE(!sf))
		वापस -EINVAL;

	अगर (nla_put_u8(skb, MPTCP_ATTR_BACKUP, sf->backup))
		वापस -EMSGSIZE;

	अगर (ssk->sk_bound_dev_अगर &&
	    nla_put_s32(skb, MPTCP_ATTR_IF_IDX, ssk->sk_bound_dev_अगर))
		वापस -EMSGSIZE;

	sk_err = ssk->sk_err;
	अगर (sk_err && sk->sk_state == TCP_ESTABLISHED &&
	    nla_put_u8(skb, MPTCP_ATTR_ERROR, sk_err))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_event_sub_established(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा mptcp_sock *msk,
				       स्थिर काष्ठा sock *ssk)
अणु
	वापस mptcp_event_put_token_and_ssk(skb, msk, ssk);
पूर्ण

अटल पूर्णांक mptcp_event_sub_बंदd(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा mptcp_sock *msk,
				  स्थिर काष्ठा sock *ssk)
अणु
	स्थिर काष्ठा mptcp_subflow_context *sf;

	अगर (mptcp_event_put_token_and_ssk(skb, msk, ssk))
		वापस -EMSGSIZE;

	sf = mptcp_subflow_ctx(ssk);
	अगर (!sf->reset_seen)
		वापस 0;

	अगर (nla_put_u32(skb, MPTCP_ATTR_RESET_REASON, sf->reset_reason))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, MPTCP_ATTR_RESET_FLAGS, sf->reset_transient))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_event_created(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा mptcp_sock *msk,
			       स्थिर काष्ठा sock *ssk)
अणु
	पूर्णांक err = nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token);

	अगर (err)
		वापस err;

	वापस mptcp_event_add_subflow(skb, ssk);
पूर्ण

व्योम mptcp_event_addr_हटाओd(स्थिर काष्ठा mptcp_sock *msk, uपूर्णांक8_t id)
अणु
	काष्ठा net *net = sock_net((स्थिर काष्ठा sock *)msk);
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;

	अगर (!genl_has_listeners(&mptcp_genl_family, net, MPTCP_PM_EV_GRP_OFFSET))
		वापस;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	nlh = genlmsg_put(skb, 0, 0, &mptcp_genl_family, 0, MPTCP_EVENT_REMOVED);
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, MPTCP_ATTR_REM_ID, id))
		जाओ nla_put_failure;

	genlmsg_end(skb, nlh);
	mptcp_nl_mcast_send(net, skb, GFP_ATOMIC);
	वापस;

nla_put_failure:
	kमुक्त_skb(skb);
पूर्ण

व्योम mptcp_event_addr_announced(स्थिर काष्ठा mptcp_sock *msk,
				स्थिर काष्ठा mptcp_addr_info *info)
अणु
	काष्ठा net *net = sock_net((स्थिर काष्ठा sock *)msk);
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;

	अगर (!genl_has_listeners(&mptcp_genl_family, net, MPTCP_PM_EV_GRP_OFFSET))
		वापस;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	nlh = genlmsg_put(skb, 0, 0, &mptcp_genl_family, 0,
			  MPTCP_EVENT_ANNOUNCED);
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, MPTCP_ATTR_REM_ID, info->id))
		जाओ nla_put_failure;

	अगर (nla_put_be16(skb, MPTCP_ATTR_DPORT, info->port))
		जाओ nla_put_failure;

	चयन (info->family) अणु
	हाल AF_INET:
		अगर (nla_put_in_addr(skb, MPTCP_ATTR_DADDR4, info->addr.s_addr))
			जाओ nla_put_failure;
		अवरोध;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	हाल AF_INET6:
		अगर (nla_put_in6_addr(skb, MPTCP_ATTR_DADDR6, &info->addr6))
			जाओ nla_put_failure;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON_ONCE(1);
		जाओ nla_put_failure;
	पूर्ण

	genlmsg_end(skb, nlh);
	mptcp_nl_mcast_send(net, skb, GFP_ATOMIC);
	वापस;

nla_put_failure:
	kमुक्त_skb(skb);
पूर्ण

व्योम mptcp_event(क्रमागत mptcp_event_type type, स्थिर काष्ठा mptcp_sock *msk,
		 स्थिर काष्ठा sock *ssk, gfp_t gfp)
अणु
	काष्ठा net *net = sock_net((स्थिर काष्ठा sock *)msk);
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;

	अगर (!genl_has_listeners(&mptcp_genl_family, net, MPTCP_PM_EV_GRP_OFFSET))
		वापस;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!skb)
		वापस;

	nlh = genlmsg_put(skb, 0, 0, &mptcp_genl_family, 0, type);
	अगर (!nlh)
		जाओ nla_put_failure;

	चयन (type) अणु
	हाल MPTCP_EVENT_UNSPEC:
		WARN_ON_ONCE(1);
		अवरोध;
	हाल MPTCP_EVENT_CREATED:
	हाल MPTCP_EVENT_ESTABLISHED:
		अगर (mptcp_event_created(skb, msk, ssk) < 0)
			जाओ nla_put_failure;
		अवरोध;
	हाल MPTCP_EVENT_CLOSED:
		अगर (nla_put_u32(skb, MPTCP_ATTR_TOKEN, msk->token) < 0)
			जाओ nla_put_failure;
		अवरोध;
	हाल MPTCP_EVENT_ANNOUNCED:
	हाल MPTCP_EVENT_REMOVED:
		/* call mptcp_event_addr_announced()/हटाओd instead */
		WARN_ON_ONCE(1);
		अवरोध;
	हाल MPTCP_EVENT_SUB_ESTABLISHED:
	हाल MPTCP_EVENT_SUB_PRIORITY:
		अगर (mptcp_event_sub_established(skb, msk, ssk) < 0)
			जाओ nla_put_failure;
		अवरोध;
	हाल MPTCP_EVENT_SUB_CLOSED:
		अगर (mptcp_event_sub_बंदd(skb, msk, ssk) < 0)
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण

	genlmsg_end(skb, nlh);
	mptcp_nl_mcast_send(net, skb, gfp);
	वापस;

nla_put_failure:
	kमुक्त_skb(skb);
पूर्ण

अटल स्थिर काष्ठा genl_small_ops mptcp_pm_ops[] = अणु
	अणु
		.cmd    = MPTCP_PM_CMD_ADD_ADDR,
		.करोit   = mptcp_nl_cmd_add_addr,
		.flags  = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd    = MPTCP_PM_CMD_DEL_ADDR,
		.करोit   = mptcp_nl_cmd_del_addr,
		.flags  = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd    = MPTCP_PM_CMD_FLUSH_ADDRS,
		.करोit   = mptcp_nl_cmd_flush_addrs,
		.flags  = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd    = MPTCP_PM_CMD_GET_ADDR,
		.करोit   = mptcp_nl_cmd_get_addr,
		.dumpit   = mptcp_nl_cmd_dump_addrs,
	पूर्ण,
	अणु
		.cmd    = MPTCP_PM_CMD_SET_LIMITS,
		.करोit   = mptcp_nl_cmd_set_limits,
		.flags  = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd    = MPTCP_PM_CMD_GET_LIMITS,
		.करोit   = mptcp_nl_cmd_get_limits,
	पूर्ण,
	अणु
		.cmd    = MPTCP_PM_CMD_SET_FLAGS,
		.करोit   = mptcp_nl_cmd_set_flags,
		.flags  = GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family mptcp_genl_family __ro_after_init = अणु
	.name		= MPTCP_PM_NAME,
	.version	= MPTCP_PM_VER,
	.maxattr	= MPTCP_PM_ATTR_MAX,
	.policy		= mptcp_pm_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= mptcp_pm_ops,
	.n_small_ops	= ARRAY_SIZE(mptcp_pm_ops),
	.mcgrps		= mptcp_pm_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(mptcp_pm_mcgrps),
पूर्ण;

अटल पूर्णांक __net_init pm_nl_init_net(काष्ठा net *net)
अणु
	काष्ठा pm_nl_pernet *pernet = net_generic(net, pm_nl_pernet_id);

	INIT_LIST_HEAD_RCU(&pernet->local_addr_list);
	__reset_counters(pernet);
	pernet->next_id = 1;
	biपंचांगap_zero(pernet->id_biपंचांगap, MAX_ADDR_ID + 1);
	spin_lock_init(&pernet->lock);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास pm_nl_निकास_net(काष्ठा list_head *net_list)
अणु
	काष्ठा net *net;

	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		काष्ठा pm_nl_pernet *pernet = net_generic(net, pm_nl_pernet_id);

		/* net is हटाओd from namespace list, can't race with
		 * other modअगरiers
		 */
		__flush_addrs(&pernet->local_addr_list);
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations mptcp_pm_pernet_ops = अणु
	.init = pm_nl_init_net,
	.निकास_batch = pm_nl_निकास_net,
	.id = &pm_nl_pernet_id,
	.size = माप(काष्ठा pm_nl_pernet),
पूर्ण;

व्योम __init mptcp_pm_nl_init(व्योम)
अणु
	अगर (रेजिस्टर_pernet_subsys(&mptcp_pm_pernet_ops) < 0)
		panic("Failed to register MPTCP PM pernet subsystem.\n");

	अगर (genl_रेजिस्टर_family(&mptcp_genl_family))
		panic("Failed to register MPTCP PM netlink family\n");
पूर्ण
