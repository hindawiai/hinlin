<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	ip6_flowlabel.c		IPv6 flowlabel manager.
 *
 *	Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in6.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/jump_label_ratelimit.h>

#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>

#समावेश <net/ipv6.h>
#समावेश <net/rawv6.h>
#समावेश <net/transp_v6.h>

#समावेश <linux/uaccess.h>

#घोषणा FL_MIN_LINGER	6	/* Minimal linger. It is set to 6sec specअगरied
				   in old IPv6 RFC. Well, it was reasonable value.
				 */
#घोषणा FL_MAX_LINGER	150	/* Maximal linger समयout */

/* FL hash table */

#घोषणा FL_MAX_PER_SOCK	32
#घोषणा FL_MAX_SIZE	4096
#घोषणा FL_HASH_MASK	255
#घोषणा FL_HASH(l)	(ntohl(l)&FL_HASH_MASK)

अटल atomic_t fl_size = ATOMIC_INIT(0);
अटल काष्ठा ip6_flowlabel __rcu *fl_ht[FL_HASH_MASK+1];

अटल व्योम ip6_fl_gc(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(ip6_fl_gc_समयr, ip6_fl_gc);

/* FL hash table lock: it protects only of GC */

अटल DEFINE_SPINLOCK(ip6_fl_lock);

/* Big socket sock */

अटल DEFINE_SPINLOCK(ip6_sk_fl_lock);

DEFINE_STATIC_KEY_DEFERRED_FALSE(ipv6_flowlabel_exclusive, HZ);
EXPORT_SYMBOL(ipv6_flowlabel_exclusive);

#घोषणा क्रम_each_fl_rcu(hash, fl)				\
	क्रम (fl = rcu_dereference_bh(fl_ht[(hash)]);		\
	     fl != शून्य;					\
	     fl = rcu_dereference_bh(fl->next))
#घोषणा क्रम_each_fl_जारी_rcu(fl)				\
	क्रम (fl = rcu_dereference_bh(fl->next);			\
	     fl != शून्य;					\
	     fl = rcu_dereference_bh(fl->next))

#घोषणा क्रम_each_sk_fl_rcu(np, sfl)				\
	क्रम (sfl = rcu_dereference_bh(np->ipv6_fl_list);	\
	     sfl != शून्य;					\
	     sfl = rcu_dereference_bh(sfl->next))

अटल अंतरभूत काष्ठा ip6_flowlabel *__fl_lookup(काष्ठा net *net, __be32 label)
अणु
	काष्ठा ip6_flowlabel *fl;

	क्रम_each_fl_rcu(FL_HASH(label), fl) अणु
		अगर (fl->label == label && net_eq(fl->fl_net, net))
			वापस fl;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा ip6_flowlabel *fl_lookup(काष्ठा net *net, __be32 label)
अणु
	काष्ठा ip6_flowlabel *fl;

	rcu_पढ़ो_lock_bh();
	fl = __fl_lookup(net, label);
	अगर (fl && !atomic_inc_not_zero(&fl->users))
		fl = शून्य;
	rcu_पढ़ो_unlock_bh();
	वापस fl;
पूर्ण

अटल bool fl_shared_exclusive(काष्ठा ip6_flowlabel *fl)
अणु
	वापस fl->share == IPV6_FL_S_EXCL ||
	       fl->share == IPV6_FL_S_PROCESS ||
	       fl->share == IPV6_FL_S_USER;
पूर्ण

अटल व्योम fl_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा ip6_flowlabel *fl = container_of(head, काष्ठा ip6_flowlabel, rcu);

	अगर (fl->share == IPV6_FL_S_PROCESS)
		put_pid(fl->owner.pid);
	kमुक्त(fl->opt);
	kमुक्त(fl);
पूर्ण


अटल व्योम fl_मुक्त(काष्ठा ip6_flowlabel *fl)
अणु
	अगर (!fl)
		वापस;

	अगर (fl_shared_exclusive(fl) || fl->opt)
		अटल_branch_slow_dec_deferred(&ipv6_flowlabel_exclusive);

	call_rcu(&fl->rcu, fl_मुक्त_rcu);
पूर्ण

अटल व्योम fl_release(काष्ठा ip6_flowlabel *fl)
अणु
	spin_lock_bh(&ip6_fl_lock);

	fl->lastuse = jअगरfies;
	अगर (atomic_dec_and_test(&fl->users)) अणु
		अचिन्हित दीर्घ ttd = fl->lastuse + fl->linger;
		अगर (समय_after(ttd, fl->expires))
			fl->expires = ttd;
		ttd = fl->expires;
		अगर (fl->opt && fl->share == IPV6_FL_S_EXCL) अणु
			काष्ठा ipv6_txoptions *opt = fl->opt;
			fl->opt = शून्य;
			kमुक्त(opt);
		पूर्ण
		अगर (!समयr_pending(&ip6_fl_gc_समयr) ||
		    समय_after(ip6_fl_gc_समयr.expires, ttd))
			mod_समयr(&ip6_fl_gc_समयr, ttd);
	पूर्ण
	spin_unlock_bh(&ip6_fl_lock);
पूर्ण

अटल व्योम ip6_fl_gc(काष्ठा समयr_list *unused)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ sched = 0;

	spin_lock(&ip6_fl_lock);

	क्रम (i = 0; i <= FL_HASH_MASK; i++) अणु
		काष्ठा ip6_flowlabel *fl;
		काष्ठा ip6_flowlabel __rcu **flp;

		flp = &fl_ht[i];
		जबतक ((fl = rcu_dereference_रक्षित(*flp,
						       lockdep_is_held(&ip6_fl_lock))) != शून्य) अणु
			अगर (atomic_पढ़ो(&fl->users) == 0) अणु
				अचिन्हित दीर्घ ttd = fl->lastuse + fl->linger;
				अगर (समय_after(ttd, fl->expires))
					fl->expires = ttd;
				ttd = fl->expires;
				अगर (समय_after_eq(now, ttd)) अणु
					*flp = fl->next;
					fl_मुक्त(fl);
					atomic_dec(&fl_size);
					जारी;
				पूर्ण
				अगर (!sched || समय_beक्रमe(ttd, sched))
					sched = ttd;
			पूर्ण
			flp = &fl->next;
		पूर्ण
	पूर्ण
	अगर (!sched && atomic_पढ़ो(&fl_size))
		sched = now + FL_MAX_LINGER;
	अगर (sched) अणु
		mod_समयr(&ip6_fl_gc_समयr, sched);
	पूर्ण
	spin_unlock(&ip6_fl_lock);
पूर्ण

अटल व्योम __net_निकास ip6_fl_purge(काष्ठा net *net)
अणु
	पूर्णांक i;

	spin_lock_bh(&ip6_fl_lock);
	क्रम (i = 0; i <= FL_HASH_MASK; i++) अणु
		काष्ठा ip6_flowlabel *fl;
		काष्ठा ip6_flowlabel __rcu **flp;

		flp = &fl_ht[i];
		जबतक ((fl = rcu_dereference_रक्षित(*flp,
						       lockdep_is_held(&ip6_fl_lock))) != शून्य) अणु
			अगर (net_eq(fl->fl_net, net) &&
			    atomic_पढ़ो(&fl->users) == 0) अणु
				*flp = fl->next;
				fl_मुक्त(fl);
				atomic_dec(&fl_size);
				जारी;
			पूर्ण
			flp = &fl->next;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ip6_fl_lock);
पूर्ण

अटल काष्ठा ip6_flowlabel *fl_पूर्णांकern(काष्ठा net *net,
				       काष्ठा ip6_flowlabel *fl, __be32 label)
अणु
	काष्ठा ip6_flowlabel *lfl;

	fl->label = label & IPV6_FLOWLABEL_MASK;

	spin_lock_bh(&ip6_fl_lock);
	अगर (label == 0) अणु
		क्रम (;;) अणु
			fl->label = htonl(pअक्रमom_u32())&IPV6_FLOWLABEL_MASK;
			अगर (fl->label) अणु
				lfl = __fl_lookup(net, fl->label);
				अगर (!lfl)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * we dropper the ip6_fl_lock, so this entry could reappear
		 * and we need to recheck with it.
		 *
		 * OTOH no need to search the active socket first, like it is
		 * करोne in ipv6_flowlabel_opt - sock is locked, so new entry
		 * with the same label can only appear on another sock
		 */
		lfl = __fl_lookup(net, fl->label);
		अगर (lfl) अणु
			atomic_inc(&lfl->users);
			spin_unlock_bh(&ip6_fl_lock);
			वापस lfl;
		पूर्ण
	पूर्ण

	fl->lastuse = jअगरfies;
	fl->next = fl_ht[FL_HASH(fl->label)];
	rcu_assign_poपूर्णांकer(fl_ht[FL_HASH(fl->label)], fl);
	atomic_inc(&fl_size);
	spin_unlock_bh(&ip6_fl_lock);
	वापस शून्य;
पूर्ण



/* Socket flowlabel lists */

काष्ठा ip6_flowlabel *__fl6_sock_lookup(काष्ठा sock *sk, __be32 label)
अणु
	काष्ठा ipv6_fl_socklist *sfl;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	label &= IPV6_FLOWLABEL_MASK;

	rcu_पढ़ो_lock_bh();
	क्रम_each_sk_fl_rcu(np, sfl) अणु
		काष्ठा ip6_flowlabel *fl = sfl->fl;

		अगर (fl->label == label && atomic_inc_not_zero(&fl->users)) अणु
			fl->lastuse = jअगरfies;
			rcu_पढ़ो_unlock_bh();
			वापस fl;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock_bh();
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(__fl6_sock_lookup);

व्योम fl6_मुक्त_socklist(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_fl_socklist *sfl;

	अगर (!rcu_access_poपूर्णांकer(np->ipv6_fl_list))
		वापस;

	spin_lock_bh(&ip6_sk_fl_lock);
	जबतक ((sfl = rcu_dereference_रक्षित(np->ipv6_fl_list,
						lockdep_is_held(&ip6_sk_fl_lock))) != शून्य) अणु
		np->ipv6_fl_list = sfl->next;
		spin_unlock_bh(&ip6_sk_fl_lock);

		fl_release(sfl->fl);
		kमुक्त_rcu(sfl, rcu);

		spin_lock_bh(&ip6_sk_fl_lock);
	पूर्ण
	spin_unlock_bh(&ip6_sk_fl_lock);
पूर्ण

/* Service routines */


/*
   It is the only dअगरficult place. flowlabel enक्रमces equal headers
   beक्रमe and including routing header, however user may supply options
   following rthdr.
 */

काष्ठा ipv6_txoptions *fl6_merge_options(काष्ठा ipv6_txoptions *opt_space,
					 काष्ठा ip6_flowlabel *fl,
					 काष्ठा ipv6_txoptions *fopt)
अणु
	काष्ठा ipv6_txoptions *fl_opt = fl->opt;

	अगर (!fopt || fopt->opt_flen == 0)
		वापस fl_opt;

	अगर (fl_opt) अणु
		opt_space->hopopt = fl_opt->hopopt;
		opt_space->dst0opt = fl_opt->dst0opt;
		opt_space->srcrt = fl_opt->srcrt;
		opt_space->opt_nflen = fl_opt->opt_nflen;
	पूर्ण अन्यथा अणु
		अगर (fopt->opt_nflen == 0)
			वापस fopt;
		opt_space->hopopt = शून्य;
		opt_space->dst0opt = शून्य;
		opt_space->srcrt = शून्य;
		opt_space->opt_nflen = 0;
	पूर्ण
	opt_space->dst1opt = fopt->dst1opt;
	opt_space->opt_flen = fopt->opt_flen;
	opt_space->tot_len = fopt->tot_len;
	वापस opt_space;
पूर्ण
EXPORT_SYMBOL_GPL(fl6_merge_options);

अटल अचिन्हित दीर्घ check_linger(अचिन्हित दीर्घ ttl)
अणु
	अगर (ttl < FL_MIN_LINGER)
		वापस FL_MIN_LINGER*HZ;
	अगर (ttl > FL_MAX_LINGER && !capable(CAP_NET_ADMIN))
		वापस 0;
	वापस ttl*HZ;
पूर्ण

अटल पूर्णांक fl6_renew(काष्ठा ip6_flowlabel *fl, अचिन्हित दीर्घ linger, अचिन्हित दीर्घ expires)
अणु
	linger = check_linger(linger);
	अगर (!linger)
		वापस -EPERM;
	expires = check_linger(expires);
	अगर (!expires)
		वापस -EPERM;

	spin_lock_bh(&ip6_fl_lock);
	fl->lastuse = jअगरfies;
	अगर (समय_beक्रमe(fl->linger, linger))
		fl->linger = linger;
	अगर (समय_beक्रमe(expires, fl->linger))
		expires = fl->linger;
	अगर (समय_beक्रमe(fl->expires, fl->lastuse + expires))
		fl->expires = fl->lastuse + expires;
	spin_unlock_bh(&ip6_fl_lock);

	वापस 0;
पूर्ण

अटल काष्ठा ip6_flowlabel *
fl_create(काष्ठा net *net, काष्ठा sock *sk, काष्ठा in6_flowlabel_req *freq,
	  sockptr_t optval, पूर्णांक optlen, पूर्णांक *err_p)
अणु
	काष्ठा ip6_flowlabel *fl = शून्य;
	पूर्णांक olen;
	पूर्णांक addr_type;
	पूर्णांक err;

	olen = optlen - CMSG_ALIGN(माप(*freq));
	err = -EINVAL;
	अगर (olen > 64 * 1024)
		जाओ करोne;

	err = -ENOMEM;
	fl = kzalloc(माप(*fl), GFP_KERNEL);
	अगर (!fl)
		जाओ करोne;

	अगर (olen > 0) अणु
		काष्ठा msghdr msg;
		काष्ठा flowi6 flowi6;
		काष्ठा ipcm6_cookie ipc6;

		err = -ENOMEM;
		fl->opt = kदो_स्मृति(माप(*fl->opt) + olen, GFP_KERNEL);
		अगर (!fl->opt)
			जाओ करोne;

		स_रखो(fl->opt, 0, माप(*fl->opt));
		fl->opt->tot_len = माप(*fl->opt) + olen;
		err = -EFAULT;
		अगर (copy_from_sockptr_offset(fl->opt + 1, optval,
				CMSG_ALIGN(माप(*freq)), olen))
			जाओ करोne;

		msg.msg_controllen = olen;
		msg.msg_control = (व्योम *)(fl->opt+1);
		स_रखो(&flowi6, 0, माप(flowi6));

		ipc6.opt = fl->opt;
		err = ip6_datagram_send_ctl(net, sk, &msg, &flowi6, &ipc6);
		अगर (err)
			जाओ करोne;
		err = -EINVAL;
		अगर (fl->opt->opt_flen)
			जाओ करोne;
		अगर (fl->opt->opt_nflen == 0) अणु
			kमुक्त(fl->opt);
			fl->opt = शून्य;
		पूर्ण
	पूर्ण

	fl->fl_net = net;
	fl->expires = jअगरfies;
	err = fl6_renew(fl, freq->flr_linger, freq->flr_expires);
	अगर (err)
		जाओ करोne;
	fl->share = freq->flr_share;
	addr_type = ipv6_addr_type(&freq->flr_dst);
	अगर ((addr_type & IPV6_ADDR_MAPPED) ||
	    addr_type == IPV6_ADDR_ANY) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	fl->dst = freq->flr_dst;
	atomic_set(&fl->users, 1);
	चयन (fl->share) अणु
	हाल IPV6_FL_S_EXCL:
	हाल IPV6_FL_S_ANY:
		अवरोध;
	हाल IPV6_FL_S_PROCESS:
		fl->owner.pid = get_task_pid(current, PIDTYPE_PID);
		अवरोध;
	हाल IPV6_FL_S_USER:
		fl->owner.uid = current_euid();
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (fl_shared_exclusive(fl) || fl->opt)
		अटल_branch_deferred_inc(&ipv6_flowlabel_exclusive);
	वापस fl;

करोne:
	अगर (fl) अणु
		kमुक्त(fl->opt);
		kमुक्त(fl);
	पूर्ण
	*err_p = err;
	वापस शून्य;
पूर्ण

अटल पूर्णांक mem_check(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_fl_socklist *sfl;
	पूर्णांक room = FL_MAX_SIZE - atomic_पढ़ो(&fl_size);
	पूर्णांक count = 0;

	अगर (room > FL_MAX_SIZE - FL_MAX_PER_SOCK)
		वापस 0;

	rcu_पढ़ो_lock_bh();
	क्रम_each_sk_fl_rcu(np, sfl)
		count++;
	rcu_पढ़ो_unlock_bh();

	अगर (room <= 0 ||
	    ((count >= FL_MAX_PER_SOCK ||
	      (count > 0 && room < FL_MAX_SIZE/2) || room < FL_MAX_SIZE/4) &&
	     !capable(CAP_NET_ADMIN)))
		वापस -ENOBUFS;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fl_link(काष्ठा ipv6_pinfo *np, काष्ठा ipv6_fl_socklist *sfl,
		काष्ठा ip6_flowlabel *fl)
अणु
	spin_lock_bh(&ip6_sk_fl_lock);
	sfl->fl = fl;
	sfl->next = np->ipv6_fl_list;
	rcu_assign_poपूर्णांकer(np->ipv6_fl_list, sfl);
	spin_unlock_bh(&ip6_sk_fl_lock);
पूर्ण

पूर्णांक ipv6_flowlabel_opt_get(काष्ठा sock *sk, काष्ठा in6_flowlabel_req *freq,
			   पूर्णांक flags)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_fl_socklist *sfl;

	अगर (flags & IPV6_FL_F_REMOTE) अणु
		freq->flr_label = np->rcv_flowinfo & IPV6_FLOWLABEL_MASK;
		वापस 0;
	पूर्ण

	अगर (np->repflow) अणु
		freq->flr_label = np->flow_label;
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock_bh();

	क्रम_each_sk_fl_rcu(np, sfl) अणु
		अगर (sfl->fl->label == (np->flow_label & IPV6_FLOWLABEL_MASK)) अणु
			spin_lock_bh(&ip6_fl_lock);
			freq->flr_label = sfl->fl->label;
			freq->flr_dst = sfl->fl->dst;
			freq->flr_share = sfl->fl->share;
			freq->flr_expires = (sfl->fl->expires - jअगरfies) / HZ;
			freq->flr_linger = sfl->fl->linger / HZ;

			spin_unlock_bh(&ip6_fl_lock);
			rcu_पढ़ो_unlock_bh();
			वापस 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	वापस -ENOENT;
पूर्ण

#घोषणा socklist_dereference(__sflp) \
	rcu_dereference_रक्षित(__sflp, lockdep_is_held(&ip6_sk_fl_lock))

अटल पूर्णांक ipv6_flowlabel_put(काष्ठा sock *sk, काष्ठा in6_flowlabel_req *freq)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_fl_socklist __rcu **sflp;
	काष्ठा ipv6_fl_socklist *sfl;

	अगर (freq->flr_flags & IPV6_FL_F_REFLECT) अणु
		अगर (sk->sk_protocol != IPPROTO_TCP)
			वापस -ENOPROTOOPT;
		अगर (!np->repflow)
			वापस -ESRCH;
		np->flow_label = 0;
		np->repflow = 0;
		वापस 0;
	पूर्ण

	spin_lock_bh(&ip6_sk_fl_lock);
	क्रम (sflp = &np->ipv6_fl_list;
	     (sfl = socklist_dereference(*sflp)) != शून्य;
	     sflp = &sfl->next) अणु
		अगर (sfl->fl->label == freq->flr_label)
			जाओ found;
	पूर्ण
	spin_unlock_bh(&ip6_sk_fl_lock);
	वापस -ESRCH;
found:
	अगर (freq->flr_label == (np->flow_label & IPV6_FLOWLABEL_MASK))
		np->flow_label &= ~IPV6_FLOWLABEL_MASK;
	*sflp = sfl->next;
	spin_unlock_bh(&ip6_sk_fl_lock);
	fl_release(sfl->fl);
	kमुक्त_rcu(sfl, rcu);
	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_flowlabel_renew(काष्ठा sock *sk, काष्ठा in6_flowlabel_req *freq)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा ipv6_fl_socklist *sfl;
	पूर्णांक err;

	rcu_पढ़ो_lock_bh();
	क्रम_each_sk_fl_rcu(np, sfl) अणु
		अगर (sfl->fl->label == freq->flr_label) अणु
			err = fl6_renew(sfl->fl, freq->flr_linger,
					freq->flr_expires);
			rcu_पढ़ो_unlock_bh();
			वापस err;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock_bh();

	अगर (freq->flr_share == IPV6_FL_S_NONE &&
	    ns_capable(net->user_ns, CAP_NET_ADMIN)) अणु
		काष्ठा ip6_flowlabel *fl = fl_lookup(net, freq->flr_label);

		अगर (fl) अणु
			err = fl6_renew(fl, freq->flr_linger,
					freq->flr_expires);
			fl_release(fl);
			वापस err;
		पूर्ण
	पूर्ण
	वापस -ESRCH;
पूर्ण

अटल पूर्णांक ipv6_flowlabel_get(काष्ठा sock *sk, काष्ठा in6_flowlabel_req *freq,
		sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा ipv6_fl_socklist *sfl, *sfl1 = शून्य;
	काष्ठा ip6_flowlabel *fl, *fl1 = शून्य;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक err;

	अगर (freq->flr_flags & IPV6_FL_F_REFLECT) अणु
		अगर (net->ipv6.sysctl.flowlabel_consistency) अणु
			net_info_ratelimited("Can not set IPV6_FL_F_REFLECT if flowlabel_consistency sysctl is enable\n");
			वापस -EPERM;
		पूर्ण

		अगर (sk->sk_protocol != IPPROTO_TCP)
			वापस -ENOPROTOOPT;
		np->repflow = 1;
		वापस 0;
	पूर्ण

	अगर (freq->flr_label & ~IPV6_FLOWLABEL_MASK)
		वापस -EINVAL;
	अगर (net->ipv6.sysctl.flowlabel_state_ranges &&
	    (freq->flr_label & IPV6_FLOWLABEL_STATELESS_FLAG))
		वापस -दुस्फल;

	fl = fl_create(net, sk, freq, optval, optlen, &err);
	अगर (!fl)
		वापस err;

	sfl1 = kदो_स्मृति(माप(*sfl1), GFP_KERNEL);

	अगर (freq->flr_label) अणु
		err = -EEXIST;
		rcu_पढ़ो_lock_bh();
		क्रम_each_sk_fl_rcu(np, sfl) अणु
			अगर (sfl->fl->label == freq->flr_label) अणु
				अगर (freq->flr_flags & IPV6_FL_F_EXCL) अणु
					rcu_पढ़ो_unlock_bh();
					जाओ करोne;
				पूर्ण
				fl1 = sfl->fl;
				अगर (!atomic_inc_not_zero(&fl1->users))
					fl1 = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock_bh();

		अगर (!fl1)
			fl1 = fl_lookup(net, freq->flr_label);
		अगर (fl1) अणु
recheck:
			err = -EEXIST;
			अगर (freq->flr_flags&IPV6_FL_F_EXCL)
				जाओ release;
			err = -EPERM;
			अगर (fl1->share == IPV6_FL_S_EXCL ||
			    fl1->share != fl->share ||
			    ((fl1->share == IPV6_FL_S_PROCESS) &&
			     (fl1->owner.pid != fl->owner.pid)) ||
			    ((fl1->share == IPV6_FL_S_USER) &&
			     !uid_eq(fl1->owner.uid, fl->owner.uid)))
				जाओ release;

			err = -ENOMEM;
			अगर (!sfl1)
				जाओ release;
			अगर (fl->linger > fl1->linger)
				fl1->linger = fl->linger;
			अगर ((दीर्घ)(fl->expires - fl1->expires) > 0)
				fl1->expires = fl->expires;
			fl_link(np, sfl1, fl1);
			fl_मुक्त(fl);
			वापस 0;

release:
			fl_release(fl1);
			जाओ करोne;
		पूर्ण
	पूर्ण
	err = -ENOENT;
	अगर (!(freq->flr_flags & IPV6_FL_F_CREATE))
		जाओ करोne;

	err = -ENOMEM;
	अगर (!sfl1)
		जाओ करोne;

	err = mem_check(sk);
	अगर (err != 0)
		जाओ करोne;

	fl1 = fl_पूर्णांकern(net, fl, freq->flr_label);
	अगर (fl1)
		जाओ recheck;

	अगर (!freq->flr_label) अणु
		माप_प्रकार offset = दुरत्व(काष्ठा in6_flowlabel_req, flr_label);

		अगर (copy_to_sockptr_offset(optval, offset, &fl->label,
				माप(fl->label))) अणु
			/* Intentionally ignore fault. */
		पूर्ण
	पूर्ण

	fl_link(np, sfl1, fl);
	वापस 0;
करोne:
	fl_मुक्त(fl);
	kमुक्त(sfl1);
	वापस err;
पूर्ण

पूर्णांक ipv6_flowlabel_opt(काष्ठा sock *sk, sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा in6_flowlabel_req freq;

	अगर (optlen < माप(freq))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&freq, optval, माप(freq)))
		वापस -EFAULT;

	चयन (freq.flr_action) अणु
	हाल IPV6_FL_A_PUT:
		वापस ipv6_flowlabel_put(sk, &freq);
	हाल IPV6_FL_A_RENEW:
		वापस ipv6_flowlabel_renew(sk, &freq);
	हाल IPV6_FL_A_GET:
		वापस ipv6_flowlabel_get(sk, &freq, optval, optlen);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

काष्ठा ip6fl_iter_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा pid_namespace *pid_ns;
	पूर्णांक bucket;
पूर्ण;

#घोषणा ip6fl_seq_निजी(seq)	((काष्ठा ip6fl_iter_state *)(seq)->निजी)

अटल काष्ठा ip6_flowlabel *ip6fl_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा ip6_flowlabel *fl = शून्य;
	काष्ठा ip6fl_iter_state *state = ip6fl_seq_निजी(seq);
	काष्ठा net *net = seq_file_net(seq);

	क्रम (state->bucket = 0; state->bucket <= FL_HASH_MASK; ++state->bucket) अणु
		क्रम_each_fl_rcu(state->bucket, fl) अणु
			अगर (net_eq(fl->fl_net, net))
				जाओ out;
		पूर्ण
	पूर्ण
	fl = शून्य;
out:
	वापस fl;
पूर्ण

अटल काष्ठा ip6_flowlabel *ip6fl_get_next(काष्ठा seq_file *seq, काष्ठा ip6_flowlabel *fl)
अणु
	काष्ठा ip6fl_iter_state *state = ip6fl_seq_निजी(seq);
	काष्ठा net *net = seq_file_net(seq);

	क्रम_each_fl_जारी_rcu(fl) अणु
		अगर (net_eq(fl->fl_net, net))
			जाओ out;
	पूर्ण

try_again:
	अगर (++state->bucket <= FL_HASH_MASK) अणु
		क्रम_each_fl_rcu(state->bucket, fl) अणु
			अगर (net_eq(fl->fl_net, net))
				जाओ out;
		पूर्ण
		जाओ try_again;
	पूर्ण
	fl = शून्य;

out:
	वापस fl;
पूर्ण

अटल काष्ठा ip6_flowlabel *ip6fl_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा ip6_flowlabel *fl = ip6fl_get_first(seq);
	अगर (fl)
		जबतक (pos && (fl = ip6fl_get_next(seq, fl)) != शून्य)
			--pos;
	वापस pos ? शून्य : fl;
पूर्ण

अटल व्योम *ip6fl_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा ip6fl_iter_state *state = ip6fl_seq_निजी(seq);

	state->pid_ns = proc_pid_ns(file_inode(seq->file)->i_sb);

	rcu_पढ़ो_lock_bh();
	वापस *pos ? ip6fl_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *ip6fl_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा ip6_flowlabel *fl;

	अगर (v == SEQ_START_TOKEN)
		fl = ip6fl_get_first(seq);
	अन्यथा
		fl = ip6fl_get_next(seq, v);
	++*pos;
	वापस fl;
पूर्ण

अटल व्योम ip6fl_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल पूर्णांक ip6fl_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ip6fl_iter_state *state = ip6fl_seq_निजी(seq);
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Label S Owner  Users  Linger Expires  Dst                              Opt\n");
	पूर्ण अन्यथा अणु
		काष्ठा ip6_flowlabel *fl = v;
		seq_म_लिखो(seq,
			   "%05X %-1d %-6d %-6d %-6ld %-8ld %pi6 %-4d\n",
			   (अचिन्हित पूर्णांक)ntohl(fl->label),
			   fl->share,
			   ((fl->share == IPV6_FL_S_PROCESS) ?
			    pid_nr_ns(fl->owner.pid, state->pid_ns) :
			    ((fl->share == IPV6_FL_S_USER) ?
			     from_kuid_munged(seq_user_ns(seq), fl->owner.uid) :
			     0)),
			   atomic_पढ़ो(&fl->users),
			   fl->linger/HZ,
			   (दीर्घ)(fl->expires - jअगरfies)/HZ,
			   &fl->dst,
			   fl->opt ? fl->opt->opt_nflen : 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ip6fl_seq_ops = अणु
	.start	=	ip6fl_seq_start,
	.next	=	ip6fl_seq_next,
	.stop	=	ip6fl_seq_stop,
	.show	=	ip6fl_seq_show,
पूर्ण;

अटल पूर्णांक __net_init ip6_flowlabel_proc_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net("ip6_flowlabel", 0444, net->proc_net,
			&ip6fl_seq_ops, माप(काष्ठा ip6fl_iter_state)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ip6_flowlabel_proc_fini(काष्ठा net *net)
अणु
	हटाओ_proc_entry("ip6_flowlabel", net->proc_net);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ip6_flowlabel_proc_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ip6_flowlabel_proc_fini(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __net_निकास ip6_flowlabel_net_निकास(काष्ठा net *net)
अणु
	ip6_fl_purge(net);
	ip6_flowlabel_proc_fini(net);
पूर्ण

अटल काष्ठा pernet_operations ip6_flowlabel_net_ops = अणु
	.init = ip6_flowlabel_proc_init,
	.निकास = ip6_flowlabel_net_निकास,
पूर्ण;

पूर्णांक ip6_flowlabel_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&ip6_flowlabel_net_ops);
पूर्ण

व्योम ip6_flowlabel_cleanup(व्योम)
अणु
	अटल_key_deferred_flush(&ipv6_flowlabel_exclusive);
	del_समयr(&ip6_fl_gc_समयr);
	unरेजिस्टर_pernet_subsys(&ip6_flowlabel_net_ops);
पूर्ण
