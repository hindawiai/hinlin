<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pluggable TCP congestion control support and newReno
 * congestion control.
 * Based on ideas from I/O scheduler support and Web100.
 *
 * Copyright (C) 2005 Stephen Hemminger <shemminger@osdl.org>
 */

#घोषणा pr_fmt(fmt) "TCP: " fmt

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/gfp.h>
#समावेश <linux/jhash.h>
#समावेश <net/tcp.h>

अटल DEFINE_SPINLOCK(tcp_cong_list_lock);
अटल LIST_HEAD(tcp_cong_list);

/* Simple linear search, करोn't expect many entries! */
काष्ठा tcp_congestion_ops *tcp_ca_find(स्थिर अक्षर *name)
अणु
	काष्ठा tcp_congestion_ops *e;

	list_क्रम_each_entry_rcu(e, &tcp_cong_list, list) अणु
		अगर (म_भेद(e->name, name) == 0)
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Must be called with rcu lock held */
अटल काष्ठा tcp_congestion_ops *tcp_ca_find_स्वतःload(काष्ठा net *net,
						       स्थिर अक्षर *name)
अणु
	काष्ठा tcp_congestion_ops *ca = tcp_ca_find(name);

#अगर_घोषित CONFIG_MODULES
	अगर (!ca && capable(CAP_NET_ADMIN)) अणु
		rcu_पढ़ो_unlock();
		request_module("tcp_%s", name);
		rcu_पढ़ो_lock();
		ca = tcp_ca_find(name);
	पूर्ण
#पूर्ण_अगर
	वापस ca;
पूर्ण

/* Simple linear search, not much in here. */
काष्ठा tcp_congestion_ops *tcp_ca_find_key(u32 key)
अणु
	काष्ठा tcp_congestion_ops *e;

	list_क्रम_each_entry_rcu(e, &tcp_cong_list, list) अणु
		अगर (e->key == key)
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Attach new congestion control algorithm to the list
 * of available options.
 */
पूर्णांक tcp_रेजिस्टर_congestion_control(काष्ठा tcp_congestion_ops *ca)
अणु
	पूर्णांक ret = 0;

	/* all algorithms must implement these */
	अगर (!ca->ssthresh || !ca->unकरो_cwnd ||
	    !(ca->cong_aव्योम || ca->cong_control)) अणु
		pr_err("%s does not implement required ops\n", ca->name);
		वापस -EINVAL;
	पूर्ण

	ca->key = jhash(ca->name, माप(ca->name), म_माप(ca->name));

	spin_lock(&tcp_cong_list_lock);
	अगर (ca->key == TCP_CA_UNSPEC || tcp_ca_find_key(ca->key)) अणु
		pr_notice("%s already registered or non-unique key\n",
			  ca->name);
		ret = -EEXIST;
	पूर्ण अन्यथा अणु
		list_add_tail_rcu(&ca->list, &tcp_cong_list);
		pr_debug("%s registered\n", ca->name);
	पूर्ण
	spin_unlock(&tcp_cong_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_रेजिस्टर_congestion_control);

/*
 * Remove congestion control algorithm, called from
 * the module's हटाओ function.  Module ref counts are used
 * to ensure that this can't be करोne till all sockets using
 * that method are बंदd.
 */
व्योम tcp_unरेजिस्टर_congestion_control(काष्ठा tcp_congestion_ops *ca)
अणु
	spin_lock(&tcp_cong_list_lock);
	list_del_rcu(&ca->list);
	spin_unlock(&tcp_cong_list_lock);

	/* Wait क्रम outstanding पढ़ोers to complete beक्रमe the
	 * module माला_लो हटाओd entirely.
	 *
	 * A try_module_get() should fail by now as our module is
	 * in "going" state since no refs are held anymore and
	 * module_निकास() handler being called.
	 */
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(tcp_unरेजिस्टर_congestion_control);

u32 tcp_ca_get_key_by_name(काष्ठा net *net, स्थिर अक्षर *name, bool *ecn_ca)
अणु
	स्थिर काष्ठा tcp_congestion_ops *ca;
	u32 key = TCP_CA_UNSPEC;

	might_sleep();

	rcu_पढ़ो_lock();
	ca = tcp_ca_find_स्वतःload(net, name);
	अगर (ca) अणु
		key = ca->key;
		*ecn_ca = ca->flags & TCP_CONG_NEEDS_ECN;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस key;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_ca_get_key_by_name);

अक्षर *tcp_ca_get_name_by_key(u32 key, अक्षर *buffer)
अणु
	स्थिर काष्ठा tcp_congestion_ops *ca;
	अक्षर *ret = शून्य;

	rcu_पढ़ो_lock();
	ca = tcp_ca_find_key(key);
	अगर (ca)
		ret = म_नकलन(buffer, ca->name,
			      TCP_CA_NAME_MAX);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_ca_get_name_by_key);

/* Assign choice of congestion control. */
व्योम tcp_assign_congestion_control(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा tcp_congestion_ops *ca;

	rcu_पढ़ो_lock();
	ca = rcu_dereference(net->ipv4.tcp_congestion_control);
	अगर (unlikely(!bpf_try_module_get(ca, ca->owner)))
		ca = &tcp_reno;
	icsk->icsk_ca_ops = ca;
	rcu_पढ़ो_unlock();

	स_रखो(icsk->icsk_ca_priv, 0, माप(icsk->icsk_ca_priv));
	अगर (ca->flags & TCP_CONG_NEEDS_ECN)
		INET_ECN_xmit(sk);
	अन्यथा
		INET_ECN_करोntxmit(sk);
पूर्ण

व्योम tcp_init_congestion_control(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	tcp_sk(sk)->prior_ssthresh = 0;
	अगर (icsk->icsk_ca_ops->init)
		icsk->icsk_ca_ops->init(sk);
	अगर (tcp_ca_needs_ecn(sk))
		INET_ECN_xmit(sk);
	अन्यथा
		INET_ECN_करोntxmit(sk);
	icsk->icsk_ca_initialized = 1;
पूर्ण

अटल व्योम tcp_reinit_congestion_control(काष्ठा sock *sk,
					  स्थिर काष्ठा tcp_congestion_ops *ca)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	tcp_cleanup_congestion_control(sk);
	icsk->icsk_ca_ops = ca;
	icsk->icsk_ca_setsockopt = 1;
	स_रखो(icsk->icsk_ca_priv, 0, माप(icsk->icsk_ca_priv));

	अगर (ca->flags & TCP_CONG_NEEDS_ECN)
		INET_ECN_xmit(sk);
	अन्यथा
		INET_ECN_करोntxmit(sk);

	अगर (!((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN)))
		tcp_init_congestion_control(sk);
पूर्ण

/* Manage refcounts on socket बंद. */
व्योम tcp_cleanup_congestion_control(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ca_ops->release)
		icsk->icsk_ca_ops->release(sk);
	bpf_module_put(icsk->icsk_ca_ops, icsk->icsk_ca_ops->owner);
पूर्ण

/* Used by sysctl to change शेष congestion control */
पूर्णांक tcp_set_शेष_congestion_control(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा tcp_congestion_ops *ca;
	स्थिर काष्ठा tcp_congestion_ops *prev;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ca = tcp_ca_find_स्वतःload(net, name);
	अगर (!ca) अणु
		ret = -ENOENT;
	पूर्ण अन्यथा अगर (!bpf_try_module_get(ca, ca->owner)) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अगर (!net_eq(net, &init_net) &&
			!(ca->flags & TCP_CONG_NON_RESTRICTED)) अणु
		/* Only init netns can set शेष to a restricted algorithm */
		ret = -EPERM;
	पूर्ण अन्यथा अणु
		prev = xchg(&net->ipv4.tcp_congestion_control, ca);
		अगर (prev)
			bpf_module_put(prev, prev->owner);

		ca->flags |= TCP_CONG_NON_RESTRICTED;
		ret = 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* Set शेष value from kernel configuration at bootup */
अटल पूर्णांक __init tcp_congestion_शेष(व्योम)
अणु
	वापस tcp_set_शेष_congestion_control(&init_net,
						  CONFIG_DEFAULT_TCP_CONG);
पूर्ण
late_initcall(tcp_congestion_शेष);

/* Build string with list of available congestion control values */
व्योम tcp_get_available_congestion_control(अक्षर *buf, माप_प्रकार maxlen)
अणु
	काष्ठा tcp_congestion_ops *ca;
	माप_प्रकार offs = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ca, &tcp_cong_list, list) अणु
		offs += snम_लिखो(buf + offs, maxlen - offs,
				 "%s%s",
				 offs == 0 ? "" : " ", ca->name);

		अगर (WARN_ON_ONCE(offs >= maxlen))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Get current शेष congestion control */
व्योम tcp_get_शेष_congestion_control(काष्ठा net *net, अक्षर *name)
अणु
	स्थिर काष्ठा tcp_congestion_ops *ca;

	rcu_पढ़ो_lock();
	ca = rcu_dereference(net->ipv4.tcp_congestion_control);
	म_नकलन(name, ca->name, TCP_CA_NAME_MAX);
	rcu_पढ़ो_unlock();
पूर्ण

/* Built list of non-restricted congestion control values */
व्योम tcp_get_allowed_congestion_control(अक्षर *buf, माप_प्रकार maxlen)
अणु
	काष्ठा tcp_congestion_ops *ca;
	माप_प्रकार offs = 0;

	*buf = '\0';
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ca, &tcp_cong_list, list) अणु
		अगर (!(ca->flags & TCP_CONG_NON_RESTRICTED))
			जारी;
		offs += snम_लिखो(buf + offs, maxlen - offs,
				 "%s%s",
				 offs == 0 ? "" : " ", ca->name);

		अगर (WARN_ON_ONCE(offs >= maxlen))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Change list of non-restricted congestion control */
पूर्णांक tcp_set_allowed_congestion_control(अक्षर *val)
अणु
	काष्ठा tcp_congestion_ops *ca;
	अक्षर *saved_clone, *clone, *name;
	पूर्णांक ret = 0;

	saved_clone = clone = kstrdup(val, GFP_USER);
	अगर (!clone)
		वापस -ENOMEM;

	spin_lock(&tcp_cong_list_lock);
	/* pass 1 check क्रम bad entries */
	जबतक ((name = strsep(&clone, " ")) && *name) अणु
		ca = tcp_ca_find(name);
		अगर (!ca) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
	पूर्ण

	/* pass 2 clear old values */
	list_क्रम_each_entry_rcu(ca, &tcp_cong_list, list)
		ca->flags &= ~TCP_CONG_NON_RESTRICTED;

	/* pass 3 mark as allowed */
	जबतक ((name = strsep(&val, " ")) && *name) अणु
		ca = tcp_ca_find(name);
		WARN_ON(!ca);
		अगर (ca)
			ca->flags |= TCP_CONG_NON_RESTRICTED;
	पूर्ण
out:
	spin_unlock(&tcp_cong_list_lock);
	kमुक्त(saved_clone);

	वापस ret;
पूर्ण

/* Change congestion control क्रम socket. If load is false, then it is the
 * responsibility of the caller to call tcp_init_congestion_control or
 * tcp_reinit_congestion_control (अगर the current congestion control was
 * alपढ़ोy initialized.
 */
पूर्णांक tcp_set_congestion_control(काष्ठा sock *sk, स्थिर अक्षर *name, bool load,
			       bool cap_net_admin)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	स्थिर काष्ठा tcp_congestion_ops *ca;
	पूर्णांक err = 0;

	अगर (icsk->icsk_ca_dst_locked)
		वापस -EPERM;

	rcu_पढ़ो_lock();
	अगर (!load)
		ca = tcp_ca_find(name);
	अन्यथा
		ca = tcp_ca_find_स्वतःload(sock_net(sk), name);

	/* No change asking क्रम existing value */
	अगर (ca == icsk->icsk_ca_ops) अणु
		icsk->icsk_ca_setsockopt = 1;
		जाओ out;
	पूर्ण

	अगर (!ca)
		err = -ENOENT;
	अन्यथा अगर (!((ca->flags & TCP_CONG_NON_RESTRICTED) || cap_net_admin))
		err = -EPERM;
	अन्यथा अगर (!bpf_try_module_get(ca, ca->owner))
		err = -EBUSY;
	अन्यथा
		tcp_reinit_congestion_control(sk, ca);
 out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/* Slow start is used when congestion winकरोw is no greater than the slow start
 * threshold. We base on RFC2581 and also handle stretch ACKs properly.
 * We करो not implement RFC3465 Appropriate Byte Counting (ABC) per se but
 * something better;) a packet is only considered (s)acked in its entirety to
 * defend the ACK attacks described in the RFC. Slow start processes a stretch
 * ACK of degree N as अगर N acks of degree 1 are received back to back except
 * ABC caps N to 2. Slow start निकासs when cwnd grows over ssthresh and
 * वापसs the leftover acks to adjust cwnd in congestion aव्योमance mode.
 */
u32 tcp_slow_start(काष्ठा tcp_sock *tp, u32 acked)
अणु
	u32 cwnd = min(tp->snd_cwnd + acked, tp->snd_ssthresh);

	acked -= cwnd - tp->snd_cwnd;
	tp->snd_cwnd = min(cwnd, tp->snd_cwnd_clamp);

	वापस acked;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_slow_start);

/* In theory this is tp->snd_cwnd += 1 / tp->snd_cwnd (or alternative w),
 * क्रम every packet that was ACKed.
 */
व्योम tcp_cong_aव्योम_ai(काष्ठा tcp_sock *tp, u32 w, u32 acked)
अणु
	/* If credits accumulated at a higher w, apply them gently now. */
	अगर (tp->snd_cwnd_cnt >= w) अणु
		tp->snd_cwnd_cnt = 0;
		tp->snd_cwnd++;
	पूर्ण

	tp->snd_cwnd_cnt += acked;
	अगर (tp->snd_cwnd_cnt >= w) अणु
		u32 delta = tp->snd_cwnd_cnt / w;

		tp->snd_cwnd_cnt -= delta * w;
		tp->snd_cwnd += delta;
	पूर्ण
	tp->snd_cwnd = min(tp->snd_cwnd, tp->snd_cwnd_clamp);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_cong_aव्योम_ai);

/*
 * TCP Reno congestion control
 * This is special हाल used क्रम fallback as well.
 */
/* This is Jacobson's slow start and congestion aव्योमance.
 * SIGCOMM '88, p. 328.
 */
व्योम tcp_reno_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	/* In "safe" area, increase. */
	अगर (tcp_in_slow_start(tp)) अणु
		acked = tcp_slow_start(tp, acked);
		अगर (!acked)
			वापस;
	पूर्ण
	/* In dangerous area, increase slowly. */
	tcp_cong_aव्योम_ai(tp, tp->snd_cwnd, acked);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_reno_cong_aव्योम);

/* Slow start threshold is half the congestion winकरोw (min 2) */
u32 tcp_reno_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस max(tp->snd_cwnd >> 1U, 2U);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_reno_ssthresh);

u32 tcp_reno_unकरो_cwnd(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस max(tp->snd_cwnd, tp->prior_cwnd);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_reno_unकरो_cwnd);

काष्ठा tcp_congestion_ops tcp_reno = अणु
	.flags		= TCP_CONG_NON_RESTRICTED,
	.name		= "reno",
	.owner		= THIS_MODULE,
	.ssthresh	= tcp_reno_ssthresh,
	.cong_aव्योम	= tcp_reno_cong_aव्योम,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
पूर्ण;
