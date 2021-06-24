<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Generic socket support routines. Memory allocators, socket lock/release
 *		handler क्रम protocols to use and generic option handler.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Florian La Roche, <flla@stud.uni-sb.de>
 *		Alan Cox, <A.Cox@swansea.ac.uk>
 *
 * Fixes:
 *		Alan Cox	: 	Numerous verअगरy_area() problems
 *		Alan Cox	:	Connecting on a connecting socket
 *					now वापसs an error क्रम tcp.
 *		Alan Cox	:	sock->protocol is set correctly.
 *					and is not someबार left as 0.
 *		Alan Cox	:	connect handles icmp errors on a
 *					connect properly. Unक्रमtunately there
 *					is a restart syscall nasty there. I
 *					can't match BSD without hacking the C
 *					library. Ideas urgently sought!
 *		Alan Cox	:	Disallow bind() to addresses that are
 *					not ours - especially broadcast ones!!
 *		Alan Cox	:	Socket 1024 _IS_ ok क्रम users. (fencepost)
 *		Alan Cox	:	sock_wमुक्त/sock_rमुक्त करोn't destroy sockets,
 *					instead they leave that क्रम the DESTROY समयr.
 *		Alan Cox	:	Clean up error flag in accept
 *		Alan Cox	:	TCP ack handling is buggy, the DESTROY समयr
 *					was buggy. Put a हटाओ_sock() in the handler
 *					क्रम memory when we hit 0. Also altered the समयr
 *					code. The ACK stuff can रुको and needs major
 *					TCP layer surgery.
 *		Alan Cox	:	Fixed TCP ack bug, हटाओd हटाओ sock
 *					and fixed समयr/inet_bh race.
 *		Alan Cox	:	Added zapped flag क्रम TCP
 *		Alan Cox	:	Move kमुक्त_skb पूर्णांकo skbuff.c and tidied up surplus code
 *		Alan Cox	:	क्रम new sk_buff allocations wदो_स्मृति/rदो_स्मृति now call alloc_skb
 *		Alan Cox	:	kमुक्त_s calls now are kमुक्त_skbmem so we can track skb resources
 *		Alan Cox	:	Supports socket option broadcast now as करोes udp. Packet and raw need fixing.
 *		Alan Cox	:	Added RCVBUF,SNDBUF size setting. It suddenly occurred to me how easy it was so...
 *		Rick Sladkey	:	Relaxed UDP rules क्रम matching packets.
 *		C.E.Hawkins	:	IFF_PROMISC/SIOCGHWADDR support
 *	Pauline Middelink	:	identd support
 *		Alan Cox	:	Fixed connect() taking संकेतs I think.
 *		Alan Cox	:	SO_LINGER supported
 *		Alan Cox	:	Error reporting fixes
 *		Anonymous	:	inet_create tidied up (sk->reuse setting)
 *		Alan Cox	:	inet sockets करोn't set sk->type!
 *		Alan Cox	:	Split socket option code
 *		Alan Cox	:	Callbacks
 *		Alan Cox	:	Nagle flag क्रम Charles & Johannes stuff
 *		Alex		:	Removed restriction on inet fioctl
 *		Alan Cox	:	Splitting INET from NET core
 *		Alan Cox	:	Fixed bogus SO_TYPE handling in माला_लोockopt()
 *		Adam Caldwell	:	Missing वापस in SO_DONTROUTE/SO_DEBUG code
 *		Alan Cox	:	Split IP from generic code
 *		Alan Cox	:	New kमुक्त_skbmem()
 *		Alan Cox	:	Make SO_DEBUG superuser only.
 *		Alan Cox	:	Allow anyone to clear SO_DEBUG
 *					(compatibility fix)
 *		Alan Cox	:	Added optimistic memory grabbing क्रम AF_UNIX throughput.
 *		Alan Cox	:	Allocator क्रम a socket is settable.
 *		Alan Cox	:	SO_ERROR includes soft errors.
 *		Alan Cox	:	Allow शून्य arguments on some SO_ opts
 *		Alan Cox	: 	Generic socket allocation to make hooks
 *					easier (suggested by Craig Metz).
 *		Michael Pall	:	SO_ERROR वापसs positive त्रुटि_सं again
 *              Steve Whitehouse:       Added शेष deकाष्ठाor to मुक्त
 *                                      protocol निजी data.
 *              Steve Whitehouse:       Added various other शेष routines
 *                                      common to several socket families.
 *              Chris Evans     :       Call suser() check last on F_SETOWN
 *		Jay Schulist	:	Added SO_ATTACH_FILTER and SO_DETACH_FILTER.
 *		Andi Kleen	:	Add sock_kदो_स्मृति()/sock_kमुक्त_s()
 *		Andi Kleen	:	Fix ग_लिखो_space callback
 *		Chris Evans	:	Security fixes - चिन्हितness again
 *		Arnalकरो C. Melo :       cleanups, use skb_queue_purge
 *
 * To Fix:
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/errqueue.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/poll.h>
#समावेश <linux/tcp.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/user_namespace.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>

#समावेश <linux/netdevice.h>
#समावेश <net/protocol.h>
#समावेश <linux/skbuff.h>
#समावेश <net/net_namespace.h>
#समावेश <net/request_sock.h>
#समावेश <net/sock.h>
#समावेश <linux/net_tstamp.h>
#समावेश <net/xfrm.h>
#समावेश <linux/ipsec.h>
#समावेश <net/cls_cgroup.h>
#समावेश <net/netprio_cgroup.h>
#समावेश <linux/sock_diag.h>

#समावेश <linux/filter.h>
#समावेश <net/sock_reuseport.h>
#समावेश <net/bpf_sk_storage.h>

#समावेश <trace/events/sock.h>

#समावेश <net/tcp.h>
#समावेश <net/busy_poll.h>

अटल DEFINE_MUTEX(proto_list_mutex);
अटल LIST_HEAD(proto_list);

अटल व्योम sock_inuse_add(काष्ठा net *net, पूर्णांक val);

/**
 * sk_ns_capable - General socket capability test
 * @sk: Socket to use a capability on or through
 * @user_ns: The user namespace of the capability to use
 * @cap: The capability to use
 *
 * Test to see अगर the खोलोer of the socket had when the socket was
 * created and the current process has the capability @cap in the user
 * namespace @user_ns.
 */
bool sk_ns_capable(स्थिर काष्ठा sock *sk,
		   काष्ठा user_namespace *user_ns, पूर्णांक cap)
अणु
	वापस file_ns_capable(sk->sk_socket->file, user_ns, cap) &&
		ns_capable(user_ns, cap);
पूर्ण
EXPORT_SYMBOL(sk_ns_capable);

/**
 * sk_capable - Socket global capability test
 * @sk: Socket to use a capability on or through
 * @cap: The global capability to use
 *
 * Test to see अगर the खोलोer of the socket had when the socket was
 * created and the current process has the capability @cap in all user
 * namespaces.
 */
bool sk_capable(स्थिर काष्ठा sock *sk, पूर्णांक cap)
अणु
	वापस sk_ns_capable(sk, &init_user_ns, cap);
पूर्ण
EXPORT_SYMBOL(sk_capable);

/**
 * sk_net_capable - Network namespace socket capability test
 * @sk: Socket to use a capability on or through
 * @cap: The capability to use
 *
 * Test to see अगर the खोलोer of the socket had when the socket was created
 * and the current process has the capability @cap over the network namespace
 * the socket is a member of.
 */
bool sk_net_capable(स्थिर काष्ठा sock *sk, पूर्णांक cap)
अणु
	वापस sk_ns_capable(sk, sock_net(sk)->user_ns, cap);
पूर्ण
EXPORT_SYMBOL(sk_net_capable);

/*
 * Each address family might have dअगरferent locking rules, so we have
 * one slock key per address family and separate keys क्रम पूर्णांकernal and
 * userspace sockets.
 */
अटल काष्ठा lock_class_key af_family_keys[AF_MAX];
अटल काष्ठा lock_class_key af_family_kern_keys[AF_MAX];
अटल काष्ठा lock_class_key af_family_slock_keys[AF_MAX];
अटल काष्ठा lock_class_key af_family_kern_slock_keys[AF_MAX];

/*
 * Make lock validator output more पढ़ोable. (we pre-स्थिरruct these
 * strings build-समय, so that runसमय initialization of socket
 * locks is fast):
 */

#घोषणा _sock_locks(x)						  \
  x "AF_UNSPEC",	x "AF_UNIX"     ,	x "AF_INET"     , \
  x "AF_AX25"  ,	x "AF_IPX"      ,	x "AF_APPLETALK", \
  x "AF_NETROM",	x "AF_BRIDGE"   ,	x "AF_ATMPVC"   , \
  x "AF_X25"   ,	x "AF_INET6"    ,	x "AF_ROSE"     , \
  x "AF_DECnet",	x "AF_NETBEUI"  ,	x "AF_SECURITY" , \
  x "AF_KEY"   ,	x "AF_NETLINK"  ,	x "AF_PACKET"   , \
  x "AF_ASH"   ,	x "AF_ECONET"   ,	x "AF_ATMSVC"   , \
  x "AF_RDS"   ,	x "AF_SNA"      ,	x "AF_IRDA"     , \
  x "AF_PPPOX" ,	x "AF_WANPIPE"  ,	x "AF_LLC"      , \
  x "27"       ,	x "28"          ,	x "AF_CAN"      , \
  x "AF_TIPC"  ,	x "AF_BLUETOOTH",	x "IUCV"        , \
  x "AF_RXRPC" ,	x "AF_ISDN"     ,	x "AF_PHONET"   , \
  x "AF_IEEE802154",	x "AF_CAIF"	,	x "AF_ALG"      , \
  x "AF_NFC"   ,	x "AF_VSOCK"    ,	x "AF_KCM"      , \
  x "AF_QIPCRTR",	x "AF_SMC"	,	x "AF_XDP"	, \
  x "AF_MAX"

अटल स्थिर अक्षर *स्थिर af_family_key_strings[AF_MAX+1] = अणु
	_sock_locks("sk_lock-")
पूर्ण;
अटल स्थिर अक्षर *स्थिर af_family_slock_key_strings[AF_MAX+1] = अणु
	_sock_locks("slock-")
पूर्ण;
अटल स्थिर अक्षर *स्थिर af_family_घड़ी_key_strings[AF_MAX+1] = अणु
	_sock_locks("clock-")
पूर्ण;

अटल स्थिर अक्षर *स्थिर af_family_kern_key_strings[AF_MAX+1] = अणु
	_sock_locks("k-sk_lock-")
पूर्ण;
अटल स्थिर अक्षर *स्थिर af_family_kern_slock_key_strings[AF_MAX+1] = अणु
	_sock_locks("k-slock-")
पूर्ण;
अटल स्थिर अक्षर *स्थिर af_family_kern_घड़ी_key_strings[AF_MAX+1] = अणु
	_sock_locks("k-clock-")
पूर्ण;
अटल स्थिर अक्षर *स्थिर af_family_rlock_key_strings[AF_MAX+1] = अणु
	_sock_locks("rlock-")
पूर्ण;
अटल स्थिर अक्षर *स्थिर af_family_wlock_key_strings[AF_MAX+1] = अणु
	_sock_locks("wlock-")
पूर्ण;
अटल स्थिर अक्षर *स्थिर af_family_elock_key_strings[AF_MAX+1] = अणु
	_sock_locks("elock-")
पूर्ण;

/*
 * sk_callback_lock and sk queues locking rules are per-address-family,
 * so split the lock classes by using a per-AF key:
 */
अटल काष्ठा lock_class_key af_callback_keys[AF_MAX];
अटल काष्ठा lock_class_key af_rlock_keys[AF_MAX];
अटल काष्ठा lock_class_key af_wlock_keys[AF_MAX];
अटल काष्ठा lock_class_key af_elock_keys[AF_MAX];
अटल काष्ठा lock_class_key af_kern_callback_keys[AF_MAX];

/* Run समय adjustable parameters. */
__u32 sysctl_wmem_max __पढ़ो_mostly = SK_WMEM_MAX;
EXPORT_SYMBOL(sysctl_wmem_max);
__u32 sysctl_rmem_max __पढ़ो_mostly = SK_RMEM_MAX;
EXPORT_SYMBOL(sysctl_rmem_max);
__u32 sysctl_wmem_शेष __पढ़ो_mostly = SK_WMEM_MAX;
__u32 sysctl_rmem_शेष __पढ़ो_mostly = SK_RMEM_MAX;

/* Maximal space eaten by iovec or ancillary data plus some space */
पूर्णांक sysctl_opपंचांगem_max __पढ़ो_mostly = माप(अचिन्हित दीर्घ)*(2*UIO_MAXIOV+512);
EXPORT_SYMBOL(sysctl_opपंचांगem_max);

पूर्णांक sysctl_tstamp_allow_data __पढ़ो_mostly = 1;

DEFINE_STATIC_KEY_FALSE(meदो_स्मृति_socks_key);
EXPORT_SYMBOL_GPL(meदो_स्मृति_socks_key);

/**
 * sk_set_meदो_स्मृति - sets %SOCK_MEMALLOC
 * @sk: socket to set it on
 *
 * Set %SOCK_MEMALLOC on a socket क्रम access to emergency reserves.
 * It's the responsibility of the admin to adjust min_मुक्त_kbytes
 * to meet the requirements
 */
व्योम sk_set_meदो_स्मृति(काष्ठा sock *sk)
अणु
	sock_set_flag(sk, SOCK_MEMALLOC);
	sk->sk_allocation |= __GFP_MEMALLOC;
	अटल_branch_inc(&meदो_स्मृति_socks_key);
पूर्ण
EXPORT_SYMBOL_GPL(sk_set_meदो_स्मृति);

व्योम sk_clear_meदो_स्मृति(काष्ठा sock *sk)
अणु
	sock_reset_flag(sk, SOCK_MEMALLOC);
	sk->sk_allocation &= ~__GFP_MEMALLOC;
	अटल_branch_dec(&meदो_स्मृति_socks_key);

	/*
	 * SOCK_MEMALLOC is allowed to ignore rmem limits to ensure क्रमward
	 * progress of swapping. SOCK_MEMALLOC may be cleared जबतक
	 * it has rmem allocations due to the last swapfile being deactivated
	 * but there is a risk that the socket is unusable due to exceeding
	 * the rmem limits. Reclaim the reserves and obey rmem limits again.
	 */
	sk_mem_reclaim(sk);
पूर्ण
EXPORT_SYMBOL_GPL(sk_clear_meदो_स्मृति);

पूर्णांक __sk_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक noreclaim_flag;

	/* these should have been dropped beक्रमe queueing */
	BUG_ON(!sock_flag(sk, SOCK_MEMALLOC));

	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	ret = sk->sk_backlog_rcv(sk, skb);
	meदो_स्मृति_noreclaim_restore(noreclaim_flag);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__sk_backlog_rcv);

अटल पूर्णांक sock_get_समयout(दीर्घ समयo, व्योम *optval, bool old_समयval)
अणु
	काष्ठा __kernel_sock_समयval tv;

	अगर (समयo == MAX_SCHEDULE_TIMEOUT) अणु
		tv.tv_sec = 0;
		tv.tv_usec = 0;
	पूर्ण अन्यथा अणु
		tv.tv_sec = समयo / HZ;
		tv.tv_usec = ((समयo % HZ) * USEC_PER_SEC) / HZ;
	पूर्ण

	अगर (old_समयval && in_compat_syscall() && !COMPAT_USE_64BIT_TIME) अणु
		काष्ठा old_समयval32 tv32 = अणु tv.tv_sec, tv.tv_usec पूर्ण;
		*(काष्ठा old_समयval32 *)optval = tv32;
		वापस माप(tv32);
	पूर्ण

	अगर (old_समयval) अणु
		काष्ठा __kernel_old_समयval old_tv;
		old_tv.tv_sec = tv.tv_sec;
		old_tv.tv_usec = tv.tv_usec;
		*(काष्ठा __kernel_old_समयval *)optval = old_tv;
		वापस माप(old_tv);
	पूर्ण

	*(काष्ठा __kernel_sock_समयval *)optval = tv;
	वापस माप(tv);
पूर्ण

अटल पूर्णांक sock_set_समयout(दीर्घ *समयo_p, sockptr_t optval, पूर्णांक optlen,
			    bool old_समयval)
अणु
	काष्ठा __kernel_sock_समयval tv;

	अगर (old_समयval && in_compat_syscall() && !COMPAT_USE_64BIT_TIME) अणु
		काष्ठा old_समयval32 tv32;

		अगर (optlen < माप(tv32))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&tv32, optval, माप(tv32)))
			वापस -EFAULT;
		tv.tv_sec = tv32.tv_sec;
		tv.tv_usec = tv32.tv_usec;
	पूर्ण अन्यथा अगर (old_समयval) अणु
		काष्ठा __kernel_old_समयval old_tv;

		अगर (optlen < माप(old_tv))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&old_tv, optval, माप(old_tv)))
			वापस -EFAULT;
		tv.tv_sec = old_tv.tv_sec;
		tv.tv_usec = old_tv.tv_usec;
	पूर्ण अन्यथा अणु
		अगर (optlen < माप(tv))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&tv, optval, माप(tv)))
			वापस -EFAULT;
	पूर्ण
	अगर (tv.tv_usec < 0 || tv.tv_usec >= USEC_PER_SEC)
		वापस -गलत_तर्क;

	अगर (tv.tv_sec < 0) अणु
		अटल पूर्णांक warned __पढ़ो_mostly;

		*समयo_p = 0;
		अगर (warned < 10 && net_ratelimit()) अणु
			warned++;
			pr_info("%s: `%s' (pid %d) tries to set negative timeout\n",
				__func__, current->comm, task_pid_nr(current));
		पूर्ण
		वापस 0;
	पूर्ण
	*समयo_p = MAX_SCHEDULE_TIMEOUT;
	अगर (tv.tv_sec == 0 && tv.tv_usec == 0)
		वापस 0;
	अगर (tv.tv_sec < (MAX_SCHEDULE_TIMEOUT / HZ - 1))
		*समयo_p = tv.tv_sec * HZ + DIV_ROUND_UP((अचिन्हित दीर्घ)tv.tv_usec, USEC_PER_SEC / HZ);
	वापस 0;
पूर्ण

अटल bool sock_needs_netstamp(स्थिर काष्ठा sock *sk)
अणु
	चयन (sk->sk_family) अणु
	हाल AF_UNSPEC:
	हाल AF_UNIX:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम sock_disable_बारtamp(काष्ठा sock *sk, अचिन्हित दीर्घ flags)
अणु
	अगर (sk->sk_flags & flags) अणु
		sk->sk_flags &= ~flags;
		अगर (sock_needs_netstamp(sk) &&
		    !(sk->sk_flags & SK_FLAGS_TIMESTAMP))
			net_disable_बारtamp();
	पूर्ण
पूर्ण


पूर्णांक __sock_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff_head *list = &sk->sk_receive_queue;

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf) अणु
		atomic_inc(&sk->sk_drops);
		trace_sock_rcvqueue_full(sk, skb);
		वापस -ENOMEM;
	पूर्ण

	अगर (!sk_rmem_schedule(sk, skb, skb->truesize)) अणु
		atomic_inc(&sk->sk_drops);
		वापस -ENOBUFS;
	पूर्ण

	skb->dev = शून्य;
	skb_set_owner_r(skb, sk);

	/* we escape from rcu रक्षित region, make sure we करोnt leak
	 * a norefcounted dst
	 */
	skb_dst_क्रमce(skb);

	spin_lock_irqsave(&list->lock, flags);
	sock_skb_set_dropcount(sk, skb);
	__skb_queue_tail(list, skb);
	spin_unlock_irqrestore(&list->lock, flags);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__sock_queue_rcv_skb);

पूर्णांक sock_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = sk_filter(sk, skb);
	अगर (err)
		वापस err;

	वापस __sock_queue_rcv_skb(sk, skb);
पूर्ण
EXPORT_SYMBOL(sock_queue_rcv_skb);

पूर्णांक __sk_receive_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		     स्थिर पूर्णांक nested, अचिन्हित पूर्णांक trim_cap, bool refcounted)
अणु
	पूर्णांक rc = NET_RX_SUCCESS;

	अगर (sk_filter_trim_cap(sk, skb, trim_cap))
		जाओ discard_and_rअन्यथा;

	skb->dev = शून्य;

	अगर (sk_rcvqueues_full(sk, sk->sk_rcvbuf)) अणु
		atomic_inc(&sk->sk_drops);
		जाओ discard_and_rअन्यथा;
	पूर्ण
	अगर (nested)
		bh_lock_sock_nested(sk);
	अन्यथा
		bh_lock_sock(sk);
	अगर (!sock_owned_by_user(sk)) अणु
		/*
		 * trylock + unlock semantics:
		 */
		mutex_acquire(&sk->sk_lock.dep_map, 0, 1, _RET_IP_);

		rc = sk_backlog_rcv(sk, skb);

		mutex_release(&sk->sk_lock.dep_map, _RET_IP_);
	पूर्ण अन्यथा अगर (sk_add_backlog(sk, skb, READ_ONCE(sk->sk_rcvbuf))) अणु
		bh_unlock_sock(sk);
		atomic_inc(&sk->sk_drops);
		जाओ discard_and_rअन्यथा;
	पूर्ण

	bh_unlock_sock(sk);
out:
	अगर (refcounted)
		sock_put(sk);
	वापस rc;
discard_and_rअन्यथा:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(__sk_receive_skb);

INसूचीECT_CALLABLE_DECLARE(काष्ठा dst_entry *ip6_dst_check(काष्ठा dst_entry *,
							  u32));
INसूचीECT_CALLABLE_DECLARE(काष्ठा dst_entry *ipv4_dst_check(काष्ठा dst_entry *,
							   u32));
काष्ठा dst_entry *__sk_dst_check(काष्ठा sock *sk, u32 cookie)
अणु
	काष्ठा dst_entry *dst = __sk_dst_get(sk);

	अगर (dst && dst->obsolete &&
	    INसूचीECT_CALL_INET(dst->ops->check, ip6_dst_check, ipv4_dst_check,
			       dst, cookie) == शून्य) अणु
		sk_tx_queue_clear(sk);
		sk->sk_dst_pending_confirm = 0;
		RCU_INIT_POINTER(sk->sk_dst_cache, शून्य);
		dst_release(dst);
		वापस शून्य;
	पूर्ण

	वापस dst;
पूर्ण
EXPORT_SYMBOL(__sk_dst_check);

काष्ठा dst_entry *sk_dst_check(काष्ठा sock *sk, u32 cookie)
अणु
	काष्ठा dst_entry *dst = sk_dst_get(sk);

	अगर (dst && dst->obsolete &&
	    INसूचीECT_CALL_INET(dst->ops->check, ip6_dst_check, ipv4_dst_check,
			       dst, cookie) == शून्य) अणु
		sk_dst_reset(sk);
		dst_release(dst);
		वापस शून्य;
	पूर्ण

	वापस dst;
पूर्ण
EXPORT_SYMBOL(sk_dst_check);

अटल पूर्णांक sock_bindtoindex_locked(काष्ठा sock *sk, पूर्णांक अगरindex)
अणु
	पूर्णांक ret = -ENOPROTOOPT;
#अगर_घोषित CONFIG_NETDEVICES
	काष्ठा net *net = sock_net(sk);

	/* Sorry... */
	ret = -EPERM;
	अगर (sk->sk_bound_dev_अगर && !ns_capable(net->user_ns, CAP_NET_RAW))
		जाओ out;

	ret = -EINVAL;
	अगर (अगरindex < 0)
		जाओ out;

	sk->sk_bound_dev_अगर = अगरindex;
	अगर (sk->sk_prot->rehash)
		sk->sk_prot->rehash(sk);
	sk_dst_reset(sk);

	ret = 0;

out:
#पूर्ण_अगर

	वापस ret;
पूर्ण

पूर्णांक sock_bindtoindex(काष्ठा sock *sk, पूर्णांक अगरindex, bool lock_sk)
अणु
	पूर्णांक ret;

	अगर (lock_sk)
		lock_sock(sk);
	ret = sock_bindtoindex_locked(sk, अगरindex);
	अगर (lock_sk)
		release_sock(sk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sock_bindtoindex);

अटल पूर्णांक sock_setbindtodevice(काष्ठा sock *sk, sockptr_t optval, पूर्णांक optlen)
अणु
	पूर्णांक ret = -ENOPROTOOPT;
#अगर_घोषित CONFIG_NETDEVICES
	काष्ठा net *net = sock_net(sk);
	अक्षर devname[IFNAMSIZ];
	पूर्णांक index;

	ret = -EINVAL;
	अगर (optlen < 0)
		जाओ out;

	/* Bind this socket to a particular device like "eth0",
	 * as specअगरied in the passed पूर्णांकerface name. If the
	 * name is "" or the option length is zero the socket
	 * is not bound.
	 */
	अगर (optlen > IFNAMSIZ - 1)
		optlen = IFNAMSIZ - 1;
	स_रखो(devname, 0, माप(devname));

	ret = -EFAULT;
	अगर (copy_from_sockptr(devname, optval, optlen))
		जाओ out;

	index = 0;
	अगर (devname[0] != '\0') अणु
		काष्ठा net_device *dev;

		rcu_पढ़ो_lock();
		dev = dev_get_by_name_rcu(net, devname);
		अगर (dev)
			index = dev->अगरindex;
		rcu_पढ़ो_unlock();
		ret = -ENODEV;
		अगर (!dev)
			जाओ out;
	पूर्ण

	वापस sock_bindtoindex(sk, index, true);
out:
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक sock_getbindtodevice(काष्ठा sock *sk, अक्षर __user *optval,
				पूर्णांक __user *optlen, पूर्णांक len)
अणु
	पूर्णांक ret = -ENOPROTOOPT;
#अगर_घोषित CONFIG_NETDEVICES
	काष्ठा net *net = sock_net(sk);
	अक्षर devname[IFNAMSIZ];

	अगर (sk->sk_bound_dev_अगर == 0) अणु
		len = 0;
		जाओ zero;
	पूर्ण

	ret = -EINVAL;
	अगर (len < IFNAMSIZ)
		जाओ out;

	ret = netdev_get_name(net, devname, sk->sk_bound_dev_अगर);
	अगर (ret)
		जाओ out;

	len = म_माप(devname) + 1;

	ret = -EFAULT;
	अगर (copy_to_user(optval, devname, len))
		जाओ out;

zero:
	ret = -EFAULT;
	अगर (put_user(len, optlen))
		जाओ out;

	ret = 0;

out:
#पूर्ण_अगर

	वापस ret;
पूर्ण

bool sk_mc_loop(काष्ठा sock *sk)
अणु
	अगर (dev_recursion_level())
		वापस false;
	अगर (!sk)
		वापस true;
	चयन (sk->sk_family) अणु
	हाल AF_INET:
		वापस inet_sk(sk)->mc_loop;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		वापस inet6_sk(sk)->mc_loop;
#पूर्ण_अगर
	पूर्ण
	WARN_ON_ONCE(1);
	वापस true;
पूर्ण
EXPORT_SYMBOL(sk_mc_loop);

व्योम sock_set_reuseaddr(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	sk->sk_reuse = SK_CAN_REUSE;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_set_reuseaddr);

व्योम sock_set_reuseport(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	sk->sk_reuseport = true;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_set_reuseport);

व्योम sock_no_linger(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	sk->sk_lingerसमय = 0;
	sock_set_flag(sk, SOCK_LINGER);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_no_linger);

व्योम sock_set_priority(काष्ठा sock *sk, u32 priority)
अणु
	lock_sock(sk);
	sk->sk_priority = priority;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_set_priority);

व्योम sock_set_sndसमयo(काष्ठा sock *sk, s64 secs)
अणु
	lock_sock(sk);
	अगर (secs && secs < MAX_SCHEDULE_TIMEOUT / HZ - 1)
		sk->sk_sndसमयo = secs * HZ;
	अन्यथा
		sk->sk_sndसमयo = MAX_SCHEDULE_TIMEOUT;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_set_sndसमयo);

अटल व्योम __sock_set_बारtamps(काष्ठा sock *sk, bool val, bool new, bool ns)
अणु
	अगर (val)  अणु
		sock_valbool_flag(sk, SOCK_TSTAMP_NEW, new);
		sock_valbool_flag(sk, SOCK_RCVTSTAMPNS, ns);
		sock_set_flag(sk, SOCK_RCVTSTAMP);
		sock_enable_बारtamp(sk, SOCK_TIMESTAMP);
	पूर्ण अन्यथा अणु
		sock_reset_flag(sk, SOCK_RCVTSTAMP);
		sock_reset_flag(sk, SOCK_RCVTSTAMPNS);
	पूर्ण
पूर्ण

व्योम sock_enable_बारtamps(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	__sock_set_बारtamps(sk, true, false, true);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_enable_बारtamps);

व्योम sock_set_keepalive(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	अगर (sk->sk_prot->keepalive)
		sk->sk_prot->keepalive(sk, true);
	sock_valbool_flag(sk, SOCK_KEEPOPEN, true);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_set_keepalive);

अटल व्योम __sock_set_rcvbuf(काष्ठा sock *sk, पूर्णांक val)
अणु
	/* Ensure val * 2 fits पूर्णांकo an पूर्णांक, to prevent max_t() from treating it
	 * as a negative value.
	 */
	val = min_t(पूर्णांक, val, पूर्णांक_उच्च / 2);
	sk->sk_userlocks |= SOCK_RCVBUF_LOCK;

	/* We द्विगुन it on the way in to account क्रम "struct sk_buff" etc.
	 * overhead.   Applications assume that the SO_RCVBUF setting they make
	 * will allow that much actual data to be received on that socket.
	 *
	 * Applications are unaware that "struct sk_buff" and other overheads
	 * allocate from the receive buffer during socket buffer allocation.
	 *
	 * And after considering the possible alternatives, वापसing the value
	 * we actually used in माला_लोockopt is the most desirable behavior.
	 */
	WRITE_ONCE(sk->sk_rcvbuf, max_t(पूर्णांक, val * 2, SOCK_MIN_RCVBUF));
पूर्ण

व्योम sock_set_rcvbuf(काष्ठा sock *sk, पूर्णांक val)
अणु
	lock_sock(sk);
	__sock_set_rcvbuf(sk, val);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_set_rcvbuf);

अटल व्योम __sock_set_mark(काष्ठा sock *sk, u32 val)
अणु
	अगर (val != sk->sk_mark) अणु
		sk->sk_mark = val;
		sk_dst_reset(sk);
	पूर्ण
पूर्ण

व्योम sock_set_mark(काष्ठा sock *sk, u32 val)
अणु
	lock_sock(sk);
	__sock_set_mark(sk, val);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(sock_set_mark);

/*
 *	This is meant क्रम all protocols to use and covers goings on
 *	at the socket level. Everything here is generic.
 */

पूर्णांक sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		    sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock_txसमय sk_txसमय;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक val;
	पूर्णांक valbool;
	काष्ठा linger ling;
	पूर्णांक ret = 0;

	/*
	 *	Options without arguments
	 */

	अगर (optname == SO_BINDTODEVICE)
		वापस sock_setbindtodevice(sk, optval, optlen);

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(val)))
		वापस -EFAULT;

	valbool = val ? 1 : 0;

	lock_sock(sk);

	चयन (optname) अणु
	हाल SO_DEBUG:
		अगर (val && !capable(CAP_NET_ADMIN))
			ret = -EACCES;
		अन्यथा
			sock_valbool_flag(sk, SOCK_DBG, valbool);
		अवरोध;
	हाल SO_REUSEADDR:
		sk->sk_reuse = (valbool ? SK_CAN_REUSE : SK_NO_REUSE);
		अवरोध;
	हाल SO_REUSEPORT:
		sk->sk_reuseport = valbool;
		अवरोध;
	हाल SO_TYPE:
	हाल SO_PROTOCOL:
	हाल SO_DOMAIN:
	हाल SO_ERROR:
		ret = -ENOPROTOOPT;
		अवरोध;
	हाल SO_DONTROUTE:
		sock_valbool_flag(sk, SOCK_LOCALROUTE, valbool);
		sk_dst_reset(sk);
		अवरोध;
	हाल SO_BROADCAST:
		sock_valbool_flag(sk, SOCK_BROADCAST, valbool);
		अवरोध;
	हाल SO_SNDBUF:
		/* Don't error on this BSD doesn't and अगर you think
		 * about it this is right. Otherwise apps have to
		 * play 'guess the biggest size' games. RCVBUF/SNDBUF
		 * are treated in BSD as hपूर्णांकs
		 */
		val = min_t(u32, val, sysctl_wmem_max);
set_sndbuf:
		/* Ensure val * 2 fits पूर्णांकo an पूर्णांक, to prevent max_t()
		 * from treating it as a negative value.
		 */
		val = min_t(पूर्णांक, val, पूर्णांक_उच्च / 2);
		sk->sk_userlocks |= SOCK_SNDBUF_LOCK;
		WRITE_ONCE(sk->sk_sndbuf,
			   max_t(पूर्णांक, val * 2, SOCK_MIN_SNDBUF));
		/* Wake up sending tasks अगर we upped the value. */
		sk->sk_ग_लिखो_space(sk);
		अवरोध;

	हाल SO_SNDBUFFORCE:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		/* No negative values (to prevent underflow, as val will be
		 * multiplied by 2).
		 */
		अगर (val < 0)
			val = 0;
		जाओ set_sndbuf;

	हाल SO_RCVBUF:
		/* Don't error on this BSD doesn't and अगर you think
		 * about it this is right. Otherwise apps have to
		 * play 'guess the biggest size' games. RCVBUF/SNDBUF
		 * are treated in BSD as hपूर्णांकs
		 */
		__sock_set_rcvbuf(sk, min_t(u32, val, sysctl_rmem_max));
		अवरोध;

	हाल SO_RCVBUFFORCE:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		/* No negative values (to prevent underflow, as val will be
		 * multiplied by 2).
		 */
		__sock_set_rcvbuf(sk, max(val, 0));
		अवरोध;

	हाल SO_KEEPALIVE:
		अगर (sk->sk_prot->keepalive)
			sk->sk_prot->keepalive(sk, valbool);
		sock_valbool_flag(sk, SOCK_KEEPOPEN, valbool);
		अवरोध;

	हाल SO_OOBINLINE:
		sock_valbool_flag(sk, SOCK_URGINLINE, valbool);
		अवरोध;

	हाल SO_NO_CHECK:
		sk->sk_no_check_tx = valbool;
		अवरोध;

	हाल SO_PRIORITY:
		अगर ((val >= 0 && val <= 6) ||
		    ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
			sk->sk_priority = val;
		अन्यथा
			ret = -EPERM;
		अवरोध;

	हाल SO_LINGER:
		अगर (optlen < माप(ling)) अणु
			ret = -EINVAL;	/* 1003.1g */
			अवरोध;
		पूर्ण
		अगर (copy_from_sockptr(&ling, optval, माप(ling))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (!ling.l_onoff)
			sock_reset_flag(sk, SOCK_LINGER);
		अन्यथा अणु
#अगर (BITS_PER_LONG == 32)
			अगर ((अचिन्हित पूर्णांक)ling.l_linger >= MAX_SCHEDULE_TIMEOUT/HZ)
				sk->sk_lingerसमय = MAX_SCHEDULE_TIMEOUT;
			अन्यथा
#पूर्ण_अगर
				sk->sk_lingerसमय = (अचिन्हित पूर्णांक)ling.l_linger * HZ;
			sock_set_flag(sk, SOCK_LINGER);
		पूर्ण
		अवरोध;

	हाल SO_BSDCOMPAT:
		अवरोध;

	हाल SO_PASSCRED:
		अगर (valbool)
			set_bit(SOCK_PASSCRED, &sock->flags);
		अन्यथा
			clear_bit(SOCK_PASSCRED, &sock->flags);
		अवरोध;

	हाल SO_TIMESTAMP_OLD:
		__sock_set_बारtamps(sk, valbool, false, false);
		अवरोध;
	हाल SO_TIMESTAMP_NEW:
		__sock_set_बारtamps(sk, valbool, true, false);
		अवरोध;
	हाल SO_TIMESTAMPNS_OLD:
		__sock_set_बारtamps(sk, valbool, false, true);
		अवरोध;
	हाल SO_TIMESTAMPNS_NEW:
		__sock_set_बारtamps(sk, valbool, true, true);
		अवरोध;
	हाल SO_TIMESTAMPING_NEW:
	हाल SO_TIMESTAMPING_OLD:
		अगर (val & ~SOF_TIMESTAMPING_MASK) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (val & SOF_TIMESTAMPING_OPT_ID &&
		    !(sk->sk_tsflags & SOF_TIMESTAMPING_OPT_ID)) अणु
			अगर (sk->sk_protocol == IPPROTO_TCP &&
			    sk->sk_type == SOCK_STREAM) अणु
				अगर ((1 << sk->sk_state) &
				    (TCPF_CLOSE | TCPF_LISTEN)) अणु
					ret = -EINVAL;
					अवरोध;
				पूर्ण
				sk->sk_tskey = tcp_sk(sk)->snd_una;
			पूर्ण अन्यथा अणु
				sk->sk_tskey = 0;
			पूर्ण
		पूर्ण

		अगर (val & SOF_TIMESTAMPING_OPT_STATS &&
		    !(val & SOF_TIMESTAMPING_OPT_TSONLY)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		sk->sk_tsflags = val;
		sock_valbool_flag(sk, SOCK_TSTAMP_NEW, optname == SO_TIMESTAMPING_NEW);

		अगर (val & SOF_TIMESTAMPING_RX_SOFTWARE)
			sock_enable_बारtamp(sk,
					      SOCK_TIMESTAMPING_RX_SOFTWARE);
		अन्यथा
			sock_disable_बारtamp(sk,
					       (1UL << SOCK_TIMESTAMPING_RX_SOFTWARE));
		अवरोध;

	हाल SO_RCVLOWAT:
		अगर (val < 0)
			val = पूर्णांक_उच्च;
		अगर (sock->ops->set_rcvlowat)
			ret = sock->ops->set_rcvlowat(sk, val);
		अन्यथा
			WRITE_ONCE(sk->sk_rcvlowat, val ? : 1);
		अवरोध;

	हाल SO_RCVTIMEO_OLD:
	हाल SO_RCVTIMEO_NEW:
		ret = sock_set_समयout(&sk->sk_rcvसमयo, optval,
				       optlen, optname == SO_RCVTIMEO_OLD);
		अवरोध;

	हाल SO_SNDTIMEO_OLD:
	हाल SO_SNDTIMEO_NEW:
		ret = sock_set_समयout(&sk->sk_sndसमयo, optval,
				       optlen, optname == SO_SNDTIMEO_OLD);
		अवरोध;

	हाल SO_ATTACH_FILTER: अणु
		काष्ठा sock_fprog fprog;

		ret = copy_bpf_fprog_from_user(&fprog, optval, optlen);
		अगर (!ret)
			ret = sk_attach_filter(&fprog, sk);
		अवरोध;
	पूर्ण
	हाल SO_ATTACH_BPF:
		ret = -EINVAL;
		अगर (optlen == माप(u32)) अणु
			u32 ufd;

			ret = -EFAULT;
			अगर (copy_from_sockptr(&ufd, optval, माप(ufd)))
				अवरोध;

			ret = sk_attach_bpf(ufd, sk);
		पूर्ण
		अवरोध;

	हाल SO_ATTACH_REUSEPORT_CBPF: अणु
		काष्ठा sock_fprog fprog;

		ret = copy_bpf_fprog_from_user(&fprog, optval, optlen);
		अगर (!ret)
			ret = sk_reuseport_attach_filter(&fprog, sk);
		अवरोध;
	पूर्ण
	हाल SO_ATTACH_REUSEPORT_EBPF:
		ret = -EINVAL;
		अगर (optlen == माप(u32)) अणु
			u32 ufd;

			ret = -EFAULT;
			अगर (copy_from_sockptr(&ufd, optval, माप(ufd)))
				अवरोध;

			ret = sk_reuseport_attach_bpf(ufd, sk);
		पूर्ण
		अवरोध;

	हाल SO_DETACH_REUSEPORT_BPF:
		ret = reuseport_detach_prog(sk);
		अवरोध;

	हाल SO_DETACH_FILTER:
		ret = sk_detach_filter(sk);
		अवरोध;

	हाल SO_LOCK_FILTER:
		अगर (sock_flag(sk, SOCK_FILTER_LOCKED) && !valbool)
			ret = -EPERM;
		अन्यथा
			sock_valbool_flag(sk, SOCK_FILTER_LOCKED, valbool);
		अवरोध;

	हाल SO_PASSSEC:
		अगर (valbool)
			set_bit(SOCK_PASSSEC, &sock->flags);
		अन्यथा
			clear_bit(SOCK_PASSSEC, &sock->flags);
		अवरोध;
	हाल SO_MARK:
		अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		__sock_set_mark(sk, val);
		अवरोध;

	हाल SO_RXQ_OVFL:
		sock_valbool_flag(sk, SOCK_RXQ_OVFL, valbool);
		अवरोध;

	हाल SO_WIFI_STATUS:
		sock_valbool_flag(sk, SOCK_WIFI_STATUS, valbool);
		अवरोध;

	हाल SO_PEEK_OFF:
		अगर (sock->ops->set_peek_off)
			ret = sock->ops->set_peek_off(sk, val);
		अन्यथा
			ret = -EOPNOTSUPP;
		अवरोध;

	हाल SO_NOFCS:
		sock_valbool_flag(sk, SOCK_NOFCS, valbool);
		अवरोध;

	हाल SO_SELECT_ERR_QUEUE:
		sock_valbool_flag(sk, SOCK_SELECT_ERR_QUEUE, valbool);
		अवरोध;

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	हाल SO_BUSY_POLL:
		/* allow unprivileged users to decrease the value */
		अगर ((val > sk->sk_ll_usec) && !capable(CAP_NET_ADMIN))
			ret = -EPERM;
		अन्यथा अणु
			अगर (val < 0)
				ret = -EINVAL;
			अन्यथा
				sk->sk_ll_usec = val;
		पूर्ण
		अवरोध;
	हाल SO_PREFER_BUSY_POLL:
		अगर (valbool && !capable(CAP_NET_ADMIN))
			ret = -EPERM;
		अन्यथा
			WRITE_ONCE(sk->sk_prefer_busy_poll, valbool);
		अवरोध;
	हाल SO_BUSY_POLL_BUDGET:
		अगर (val > READ_ONCE(sk->sk_busy_poll_budget) && !capable(CAP_NET_ADMIN)) अणु
			ret = -EPERM;
		पूर्ण अन्यथा अणु
			अगर (val < 0 || val > U16_MAX)
				ret = -EINVAL;
			अन्यथा
				WRITE_ONCE(sk->sk_busy_poll_budget, val);
		पूर्ण
		अवरोध;
#पूर्ण_अगर

	हाल SO_MAX_PACING_RATE:
		अणु
		अचिन्हित दीर्घ ulval = (val == ~0U) ? ~0UL : (अचिन्हित पूर्णांक)val;

		अगर (माप(ulval) != माप(val) &&
		    optlen >= माप(ulval) &&
		    copy_from_sockptr(&ulval, optval, माप(ulval))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (ulval != ~0UL)
			cmpxchg(&sk->sk_pacing_status,
				SK_PACING_NONE,
				SK_PACING_NEEDED);
		sk->sk_max_pacing_rate = ulval;
		sk->sk_pacing_rate = min(sk->sk_pacing_rate, ulval);
		अवरोध;
		पूर्ण
	हाल SO_INCOMING_CPU:
		WRITE_ONCE(sk->sk_incoming_cpu, val);
		अवरोध;

	हाल SO_CNX_ADVICE:
		अगर (val == 1)
			dst_negative_advice(sk);
		अवरोध;

	हाल SO_ZEROCOPY:
		अगर (sk->sk_family == PF_INET || sk->sk_family == PF_INET6) अणु
			अगर (!((sk->sk_type == SOCK_STREAM &&
			       sk->sk_protocol == IPPROTO_TCP) ||
			      (sk->sk_type == SOCK_DGRAM &&
			       sk->sk_protocol == IPPROTO_UDP)))
				ret = -ENOTSUPP;
		पूर्ण अन्यथा अगर (sk->sk_family != PF_RDS) अणु
			ret = -ENOTSUPP;
		पूर्ण
		अगर (!ret) अणु
			अगर (val < 0 || val > 1)
				ret = -EINVAL;
			अन्यथा
				sock_valbool_flag(sk, SOCK_ZEROCOPY, valbool);
		पूर्ण
		अवरोध;

	हाल SO_TXTIME:
		अगर (optlen != माप(काष्ठा sock_txसमय)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण अन्यथा अगर (copy_from_sockptr(&sk_txसमय, optval,
			   माप(काष्ठा sock_txसमय))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण अन्यथा अगर (sk_txसमय.flags & ~SOF_TXTIME_FLAGS_MASK) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		/* CLOCK_MONOTONIC is only used by sch_fq, and this packet
		 * scheduler has enough safe guards.
		 */
		अगर (sk_txसमय.घड़ीid != CLOCK_MONOTONIC &&
		    !ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण
		sock_valbool_flag(sk, SOCK_TXTIME, true);
		sk->sk_घड़ीid = sk_txसमय.घड़ीid;
		sk->sk_txसमय_deadline_mode =
			!!(sk_txसमय.flags & SOF_TXTIME_DEADLINE_MODE);
		sk->sk_txसमय_report_errors =
			!!(sk_txसमय.flags & SOF_TXTIME_REPORT_ERRORS);
		अवरोध;

	हाल SO_BINDTOIFINDEX:
		ret = sock_bindtoindex_locked(sk, val);
		अवरोध;

	शेष:
		ret = -ENOPROTOOPT;
		अवरोध;
	पूर्ण
	release_sock(sk);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sock_setsockopt);


अटल व्योम cred_to_ucred(काष्ठा pid *pid, स्थिर काष्ठा cred *cred,
			  काष्ठा ucred *ucred)
अणु
	ucred->pid = pid_vnr(pid);
	ucred->uid = ucred->gid = -1;
	अगर (cred) अणु
		काष्ठा user_namespace *current_ns = current_user_ns();

		ucred->uid = from_kuid_munged(current_ns, cred->euid);
		ucred->gid = from_kgid_munged(current_ns, cred->egid);
	पूर्ण
पूर्ण

अटल पूर्णांक groups_to_user(gid_t __user *dst, स्थिर काष्ठा group_info *src)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	पूर्णांक i;

	क्रम (i = 0; i < src->ngroups; i++)
		अगर (put_user(from_kgid_munged(user_ns, src->gid[i]), dst + i))
			वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;

	जोड़ अणु
		पूर्णांक val;
		u64 val64;
		अचिन्हित दीर्घ ulval;
		काष्ठा linger ling;
		काष्ठा old_समयval32 पंचांग32;
		काष्ठा __kernel_old_समयval पंचांग;
		काष्ठा  __kernel_sock_समयval sपंचांग;
		काष्ठा sock_txसमय txसमय;
	पूर्ण v;

	पूर्णांक lv = माप(पूर्णांक);
	पूर्णांक len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (len < 0)
		वापस -EINVAL;

	स_रखो(&v, 0, माप(v));

	चयन (optname) अणु
	हाल SO_DEBUG:
		v.val = sock_flag(sk, SOCK_DBG);
		अवरोध;

	हाल SO_DONTROUTE:
		v.val = sock_flag(sk, SOCK_LOCALROUTE);
		अवरोध;

	हाल SO_BROADCAST:
		v.val = sock_flag(sk, SOCK_BROADCAST);
		अवरोध;

	हाल SO_SNDBUF:
		v.val = sk->sk_sndbuf;
		अवरोध;

	हाल SO_RCVBUF:
		v.val = sk->sk_rcvbuf;
		अवरोध;

	हाल SO_REUSEADDR:
		v.val = sk->sk_reuse;
		अवरोध;

	हाल SO_REUSEPORT:
		v.val = sk->sk_reuseport;
		अवरोध;

	हाल SO_KEEPALIVE:
		v.val = sock_flag(sk, SOCK_KEEPOPEN);
		अवरोध;

	हाल SO_TYPE:
		v.val = sk->sk_type;
		अवरोध;

	हाल SO_PROTOCOL:
		v.val = sk->sk_protocol;
		अवरोध;

	हाल SO_DOMAIN:
		v.val = sk->sk_family;
		अवरोध;

	हाल SO_ERROR:
		v.val = -sock_error(sk);
		अगर (v.val == 0)
			v.val = xchg(&sk->sk_err_soft, 0);
		अवरोध;

	हाल SO_OOBINLINE:
		v.val = sock_flag(sk, SOCK_URGINLINE);
		अवरोध;

	हाल SO_NO_CHECK:
		v.val = sk->sk_no_check_tx;
		अवरोध;

	हाल SO_PRIORITY:
		v.val = sk->sk_priority;
		अवरोध;

	हाल SO_LINGER:
		lv		= माप(v.ling);
		v.ling.l_onoff	= sock_flag(sk, SOCK_LINGER);
		v.ling.l_linger	= sk->sk_lingerसमय / HZ;
		अवरोध;

	हाल SO_BSDCOMPAT:
		अवरोध;

	हाल SO_TIMESTAMP_OLD:
		v.val = sock_flag(sk, SOCK_RCVTSTAMP) &&
				!sock_flag(sk, SOCK_TSTAMP_NEW) &&
				!sock_flag(sk, SOCK_RCVTSTAMPNS);
		अवरोध;

	हाल SO_TIMESTAMPNS_OLD:
		v.val = sock_flag(sk, SOCK_RCVTSTAMPNS) && !sock_flag(sk, SOCK_TSTAMP_NEW);
		अवरोध;

	हाल SO_TIMESTAMP_NEW:
		v.val = sock_flag(sk, SOCK_RCVTSTAMP) && sock_flag(sk, SOCK_TSTAMP_NEW);
		अवरोध;

	हाल SO_TIMESTAMPNS_NEW:
		v.val = sock_flag(sk, SOCK_RCVTSTAMPNS) && sock_flag(sk, SOCK_TSTAMP_NEW);
		अवरोध;

	हाल SO_TIMESTAMPING_OLD:
		v.val = sk->sk_tsflags;
		अवरोध;

	हाल SO_RCVTIMEO_OLD:
	हाल SO_RCVTIMEO_NEW:
		lv = sock_get_समयout(sk->sk_rcvसमयo, &v, SO_RCVTIMEO_OLD == optname);
		अवरोध;

	हाल SO_SNDTIMEO_OLD:
	हाल SO_SNDTIMEO_NEW:
		lv = sock_get_समयout(sk->sk_sndसमयo, &v, SO_SNDTIMEO_OLD == optname);
		अवरोध;

	हाल SO_RCVLOWAT:
		v.val = sk->sk_rcvlowat;
		अवरोध;

	हाल SO_SNDLOWAT:
		v.val = 1;
		अवरोध;

	हाल SO_PASSCRED:
		v.val = !!test_bit(SOCK_PASSCRED, &sock->flags);
		अवरोध;

	हाल SO_PEERCRED:
	अणु
		काष्ठा ucred peercred;
		अगर (len > माप(peercred))
			len = माप(peercred);
		cred_to_ucred(sk->sk_peer_pid, sk->sk_peer_cred, &peercred);
		अगर (copy_to_user(optval, &peercred, len))
			वापस -EFAULT;
		जाओ lenout;
	पूर्ण

	हाल SO_PEERGROUPS:
	अणु
		पूर्णांक ret, n;

		अगर (!sk->sk_peer_cred)
			वापस -ENODATA;

		n = sk->sk_peer_cred->group_info->ngroups;
		अगर (len < n * माप(gid_t)) अणु
			len = n * माप(gid_t);
			वापस put_user(len, optlen) ? -EFAULT : -दुस्फल;
		पूर्ण
		len = n * माप(gid_t);

		ret = groups_to_user((gid_t __user *)optval,
				     sk->sk_peer_cred->group_info);
		अगर (ret)
			वापस ret;
		जाओ lenout;
	पूर्ण

	हाल SO_PEERNAME:
	अणु
		अक्षर address[128];

		lv = sock->ops->getname(sock, (काष्ठा sockaddr *)address, 2);
		अगर (lv < 0)
			वापस -ENOTCONN;
		अगर (lv < len)
			वापस -EINVAL;
		अगर (copy_to_user(optval, address, len))
			वापस -EFAULT;
		जाओ lenout;
	पूर्ण

	/* Dubious BSD thing... Probably nobody even uses it, but
	 * the UNIX standard wants it क्रम whatever reason... -DaveM
	 */
	हाल SO_ACCEPTCONN:
		v.val = sk->sk_state == TCP_LISTEN;
		अवरोध;

	हाल SO_PASSSEC:
		v.val = !!test_bit(SOCK_PASSSEC, &sock->flags);
		अवरोध;

	हाल SO_PEERSEC:
		वापस security_socket_getpeersec_stream(sock, optval, optlen, len);

	हाल SO_MARK:
		v.val = sk->sk_mark;
		अवरोध;

	हाल SO_RXQ_OVFL:
		v.val = sock_flag(sk, SOCK_RXQ_OVFL);
		अवरोध;

	हाल SO_WIFI_STATUS:
		v.val = sock_flag(sk, SOCK_WIFI_STATUS);
		अवरोध;

	हाल SO_PEEK_OFF:
		अगर (!sock->ops->set_peek_off)
			वापस -EOPNOTSUPP;

		v.val = sk->sk_peek_off;
		अवरोध;
	हाल SO_NOFCS:
		v.val = sock_flag(sk, SOCK_NOFCS);
		अवरोध;

	हाल SO_BINDTODEVICE:
		वापस sock_getbindtodevice(sk, optval, optlen, len);

	हाल SO_GET_FILTER:
		len = sk_get_filter(sk, (काष्ठा sock_filter __user *)optval, len);
		अगर (len < 0)
			वापस len;

		जाओ lenout;

	हाल SO_LOCK_FILTER:
		v.val = sock_flag(sk, SOCK_FILTER_LOCKED);
		अवरोध;

	हाल SO_BPF_EXTENSIONS:
		v.val = bpf_tell_extensions();
		अवरोध;

	हाल SO_SELECT_ERR_QUEUE:
		v.val = sock_flag(sk, SOCK_SELECT_ERR_QUEUE);
		अवरोध;

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	हाल SO_BUSY_POLL:
		v.val = sk->sk_ll_usec;
		अवरोध;
	हाल SO_PREFER_BUSY_POLL:
		v.val = READ_ONCE(sk->sk_prefer_busy_poll);
		अवरोध;
#पूर्ण_अगर

	हाल SO_MAX_PACING_RATE:
		अगर (माप(v.ulval) != माप(v.val) && len >= माप(v.ulval)) अणु
			lv = माप(v.ulval);
			v.ulval = sk->sk_max_pacing_rate;
		पूर्ण अन्यथा अणु
			/* 32bit version */
			v.val = min_t(अचिन्हित दीर्घ, sk->sk_max_pacing_rate, ~0U);
		पूर्ण
		अवरोध;

	हाल SO_INCOMING_CPU:
		v.val = READ_ONCE(sk->sk_incoming_cpu);
		अवरोध;

	हाल SO_MEMINFO:
	अणु
		u32 meminfo[SK_MEMINFO_VARS];

		sk_get_meminfo(sk, meminfo);

		len = min_t(अचिन्हित पूर्णांक, len, माप(meminfo));
		अगर (copy_to_user(optval, &meminfo, len))
			वापस -EFAULT;

		जाओ lenout;
	पूर्ण

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	हाल SO_INCOMING_NAPI_ID:
		v.val = READ_ONCE(sk->sk_napi_id);

		/* aggregate non-NAPI IDs करोwn to 0 */
		अगर (v.val < MIN_NAPI_ID)
			v.val = 0;

		अवरोध;
#पूर्ण_अगर

	हाल SO_COOKIE:
		lv = माप(u64);
		अगर (len < lv)
			वापस -EINVAL;
		v.val64 = sock_gen_cookie(sk);
		अवरोध;

	हाल SO_ZEROCOPY:
		v.val = sock_flag(sk, SOCK_ZEROCOPY);
		अवरोध;

	हाल SO_TXTIME:
		lv = माप(v.txसमय);
		v.txसमय.घड़ीid = sk->sk_घड़ीid;
		v.txसमय.flags |= sk->sk_txसमय_deadline_mode ?
				  SOF_TXTIME_DEADLINE_MODE : 0;
		v.txसमय.flags |= sk->sk_txसमय_report_errors ?
				  SOF_TXTIME_REPORT_ERRORS : 0;
		अवरोध;

	हाल SO_BINDTOIFINDEX:
		v.val = sk->sk_bound_dev_अगर;
		अवरोध;

	शेष:
		/* We implement the SO_SNDLOWAT etc to not be settable
		 * (1003.1g 7).
		 */
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (len > lv)
		len = lv;
	अगर (copy_to_user(optval, &v, len))
		वापस -EFAULT;
lenout:
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * Initialize an sk_lock.
 *
 * (We also रेजिस्टर the sk_lock with the lock validator.)
 */
अटल अंतरभूत व्योम sock_lock_init(काष्ठा sock *sk)
अणु
	अगर (sk->sk_kern_sock)
		sock_lock_init_class_and_name(
			sk,
			af_family_kern_slock_key_strings[sk->sk_family],
			af_family_kern_slock_keys + sk->sk_family,
			af_family_kern_key_strings[sk->sk_family],
			af_family_kern_keys + sk->sk_family);
	अन्यथा
		sock_lock_init_class_and_name(
			sk,
			af_family_slock_key_strings[sk->sk_family],
			af_family_slock_keys + sk->sk_family,
			af_family_key_strings[sk->sk_family],
			af_family_keys + sk->sk_family);
पूर्ण

/*
 * Copy all fields from osk to nsk but nsk->sk_refcnt must not change yet,
 * even temporarly, because of RCU lookups. sk_node should also be left as is.
 * We must not copy fields between sk_करोntcopy_begin and sk_करोntcopy_end
 */
अटल व्योम sock_copy(काष्ठा sock *nsk, स्थिर काष्ठा sock *osk)
अणु
	स्थिर काष्ठा proto *prot = READ_ONCE(osk->sk_prot);
#अगर_घोषित CONFIG_SECURITY_NETWORK
	व्योम *sptr = nsk->sk_security;
#पूर्ण_अगर

	/* If we move sk_tx_queue_mapping out of the निजी section,
	 * we must check अगर sk_tx_queue_clear() is called after
	 * sock_copy() in sk_clone_lock().
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा sock, sk_tx_queue_mapping) <
		     दुरत्व(काष्ठा sock, sk_करोntcopy_begin) ||
		     दुरत्व(काष्ठा sock, sk_tx_queue_mapping) >=
		     दुरत्व(काष्ठा sock, sk_करोntcopy_end));

	स_नकल(nsk, osk, दुरत्व(काष्ठा sock, sk_करोntcopy_begin));

	स_नकल(&nsk->sk_करोntcopy_end, &osk->sk_करोntcopy_end,
	       prot->obj_size - दुरत्व(काष्ठा sock, sk_करोntcopy_end));

#अगर_घोषित CONFIG_SECURITY_NETWORK
	nsk->sk_security = sptr;
	security_sk_clone(osk, nsk);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा sock *sk_prot_alloc(काष्ठा proto *prot, gfp_t priority,
		पूर्णांक family)
अणु
	काष्ठा sock *sk;
	काष्ठा kmem_cache *slab;

	slab = prot->slab;
	अगर (slab != शून्य) अणु
		sk = kmem_cache_alloc(slab, priority & ~__GFP_ZERO);
		अगर (!sk)
			वापस sk;
		अगर (want_init_on_alloc(priority))
			sk_prot_clear_nulls(sk, prot->obj_size);
	पूर्ण अन्यथा
		sk = kदो_स्मृति(prot->obj_size, priority);

	अगर (sk != शून्य) अणु
		अगर (security_sk_alloc(sk, family, priority))
			जाओ out_मुक्त;

		अगर (!try_module_get(prot->owner))
			जाओ out_मुक्त_sec;
	पूर्ण

	वापस sk;

out_मुक्त_sec:
	security_sk_मुक्त(sk);
out_मुक्त:
	अगर (slab != शून्य)
		kmem_cache_मुक्त(slab, sk);
	अन्यथा
		kमुक्त(sk);
	वापस शून्य;
पूर्ण

अटल व्योम sk_prot_मुक्त(काष्ठा proto *prot, काष्ठा sock *sk)
अणु
	काष्ठा kmem_cache *slab;
	काष्ठा module *owner;

	owner = prot->owner;
	slab = prot->slab;

	cgroup_sk_मुक्त(&sk->sk_cgrp_data);
	mem_cgroup_sk_मुक्त(sk);
	security_sk_मुक्त(sk);
	अगर (slab != शून्य)
		kmem_cache_मुक्त(slab, sk);
	अन्यथा
		kमुक्त(sk);
	module_put(owner);
पूर्ण

/**
 *	sk_alloc - All socket objects are allocated here
 *	@net: the applicable net namespace
 *	@family: protocol family
 *	@priority: क्रम allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)
 *	@prot: काष्ठा proto associated with this new sock instance
 *	@kern: is this to be a kernel socket?
 */
काष्ठा sock *sk_alloc(काष्ठा net *net, पूर्णांक family, gfp_t priority,
		      काष्ठा proto *prot, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	sk = sk_prot_alloc(prot, priority | __GFP_ZERO, family);
	अगर (sk) अणु
		sk->sk_family = family;
		/*
		 * See comment in काष्ठा sock definition to understand
		 * why we need sk_prot_creator -acme
		 */
		sk->sk_prot = sk->sk_prot_creator = prot;
		sk->sk_kern_sock = kern;
		sock_lock_init(sk);
		sk->sk_net_refcnt = kern ? 0 : 1;
		अगर (likely(sk->sk_net_refcnt)) अणु
			get_net(net);
			sock_inuse_add(net, 1);
		पूर्ण

		sock_net_set(sk, net);
		refcount_set(&sk->sk_wmem_alloc, 1);

		mem_cgroup_sk_alloc(sk);
		cgroup_sk_alloc(&sk->sk_cgrp_data);
		sock_update_classid(&sk->sk_cgrp_data);
		sock_update_netprioidx(&sk->sk_cgrp_data);
		sk_tx_queue_clear(sk);
	पूर्ण

	वापस sk;
पूर्ण
EXPORT_SYMBOL(sk_alloc);

/* Sockets having SOCK_RCU_FREE will call this function after one RCU
 * grace period. This is the हाल क्रम UDP sockets and TCP listeners.
 */
अटल व्योम __sk_deकाष्ठा(काष्ठा rcu_head *head)
अणु
	काष्ठा sock *sk = container_of(head, काष्ठा sock, sk_rcu);
	काष्ठा sk_filter *filter;

	अगर (sk->sk_deकाष्ठा)
		sk->sk_deकाष्ठा(sk);

	filter = rcu_dereference_check(sk->sk_filter,
				       refcount_पढ़ो(&sk->sk_wmem_alloc) == 0);
	अगर (filter) अणु
		sk_filter_unअक्षरge(sk, filter);
		RCU_INIT_POINTER(sk->sk_filter, शून्य);
	पूर्ण

	sock_disable_बारtamp(sk, SK_FLAGS_TIMESTAMP);

#अगर_घोषित CONFIG_BPF_SYSCALL
	bpf_sk_storage_मुक्त(sk);
#पूर्ण_अगर

	अगर (atomic_पढ़ो(&sk->sk_omem_alloc))
		pr_debug("%s: optmem leakage (%d bytes) detected\n",
			 __func__, atomic_पढ़ो(&sk->sk_omem_alloc));

	अगर (sk->sk_frag.page) अणु
		put_page(sk->sk_frag.page);
		sk->sk_frag.page = शून्य;
	पूर्ण

	अगर (sk->sk_peer_cred)
		put_cred(sk->sk_peer_cred);
	put_pid(sk->sk_peer_pid);
	अगर (likely(sk->sk_net_refcnt))
		put_net(sock_net(sk));
	sk_prot_मुक्त(sk->sk_prot_creator, sk);
पूर्ण

व्योम sk_deकाष्ठा(काष्ठा sock *sk)
अणु
	bool use_call_rcu = sock_flag(sk, SOCK_RCU_FREE);

	अगर (rcu_access_poपूर्णांकer(sk->sk_reuseport_cb)) अणु
		reuseport_detach_sock(sk);
		use_call_rcu = true;
	पूर्ण

	अगर (use_call_rcu)
		call_rcu(&sk->sk_rcu, __sk_deकाष्ठा);
	अन्यथा
		__sk_deकाष्ठा(&sk->sk_rcu);
पूर्ण

अटल व्योम __sk_मुक्त(काष्ठा sock *sk)
अणु
	अगर (likely(sk->sk_net_refcnt))
		sock_inuse_add(sock_net(sk), -1);

	अगर (unlikely(sk->sk_net_refcnt && sock_diag_has_destroy_listeners(sk)))
		sock_diag_broadcast_destroy(sk);
	अन्यथा
		sk_deकाष्ठा(sk);
पूर्ण

व्योम sk_मुक्त(काष्ठा sock *sk)
अणु
	/*
	 * We subtract one from sk_wmem_alloc and can know अगर
	 * some packets are still in some tx queue.
	 * If not null, sock_wमुक्त() will call __sk_मुक्त(sk) later
	 */
	अगर (refcount_dec_and_test(&sk->sk_wmem_alloc))
		__sk_मुक्त(sk);
पूर्ण
EXPORT_SYMBOL(sk_मुक्त);

अटल व्योम sk_init_common(काष्ठा sock *sk)
अणु
	skb_queue_head_init(&sk->sk_receive_queue);
	skb_queue_head_init(&sk->sk_ग_लिखो_queue);
	skb_queue_head_init(&sk->sk_error_queue);

	rwlock_init(&sk->sk_callback_lock);
	lockdep_set_class_and_name(&sk->sk_receive_queue.lock,
			af_rlock_keys + sk->sk_family,
			af_family_rlock_key_strings[sk->sk_family]);
	lockdep_set_class_and_name(&sk->sk_ग_लिखो_queue.lock,
			af_wlock_keys + sk->sk_family,
			af_family_wlock_key_strings[sk->sk_family]);
	lockdep_set_class_and_name(&sk->sk_error_queue.lock,
			af_elock_keys + sk->sk_family,
			af_family_elock_key_strings[sk->sk_family]);
	lockdep_set_class_and_name(&sk->sk_callback_lock,
			af_callback_keys + sk->sk_family,
			af_family_घड़ी_key_strings[sk->sk_family]);
पूर्ण

/**
 *	sk_clone_lock - clone a socket, and lock its clone
 *	@sk: the socket to clone
 *	@priority: क्रम allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)
 *
 *	Caller must unlock socket even in error path (bh_unlock_sock(newsk))
 */
काष्ठा sock *sk_clone_lock(स्थिर काष्ठा sock *sk, स्थिर gfp_t priority)
अणु
	काष्ठा proto *prot = READ_ONCE(sk->sk_prot);
	काष्ठा sk_filter *filter;
	bool is_अक्षरged = true;
	काष्ठा sock *newsk;

	newsk = sk_prot_alloc(prot, priority, sk->sk_family);
	अगर (!newsk)
		जाओ out;

	sock_copy(newsk, sk);

	newsk->sk_prot_creator = prot;

	/* SANITY */
	अगर (likely(newsk->sk_net_refcnt))
		get_net(sock_net(newsk));
	sk_node_init(&newsk->sk_node);
	sock_lock_init(newsk);
	bh_lock_sock(newsk);
	newsk->sk_backlog.head	= newsk->sk_backlog.tail = शून्य;
	newsk->sk_backlog.len = 0;

	atomic_set(&newsk->sk_rmem_alloc, 0);

	/* sk_wmem_alloc set to one (see sk_मुक्त() and sock_wमुक्त()) */
	refcount_set(&newsk->sk_wmem_alloc, 1);

	atomic_set(&newsk->sk_omem_alloc, 0);
	sk_init_common(newsk);

	newsk->sk_dst_cache	= शून्य;
	newsk->sk_dst_pending_confirm = 0;
	newsk->sk_wmem_queued	= 0;
	newsk->sk_क्रमward_alloc = 0;
	atomic_set(&newsk->sk_drops, 0);
	newsk->sk_send_head	= शून्य;
	newsk->sk_userlocks	= sk->sk_userlocks & ~SOCK_BINDPORT_LOCK;
	atomic_set(&newsk->sk_zckey, 0);

	sock_reset_flag(newsk, SOCK_DONE);

	/* sk->sk_memcg will be populated at accept() समय */
	newsk->sk_memcg = शून्य;

	cgroup_sk_clone(&newsk->sk_cgrp_data);

	rcu_पढ़ो_lock();
	filter = rcu_dereference(sk->sk_filter);
	अगर (filter != शून्य)
		/* though it's an empty new sock, the अक्षरging may fail
		 * अगर sysctl_opपंचांगem_max was changed between creation of
		 * original socket and cloning
		 */
		is_अक्षरged = sk_filter_अक्षरge(newsk, filter);
	RCU_INIT_POINTER(newsk->sk_filter, filter);
	rcu_पढ़ो_unlock();

	अगर (unlikely(!is_अक्षरged || xfrm_sk_clone_policy(newsk, sk))) अणु
		/* We need to make sure that we करोn't unअक्षरge the new
		 * socket अगर we couldn't अक्षरge it in the first place
		 * as otherwise we unअक्षरge the parent's filter.
		 */
		अगर (!is_अक्षरged)
			RCU_INIT_POINTER(newsk->sk_filter, शून्य);
		sk_मुक्त_unlock_clone(newsk);
		newsk = शून्य;
		जाओ out;
	पूर्ण
	RCU_INIT_POINTER(newsk->sk_reuseport_cb, शून्य);

	अगर (bpf_sk_storage_clone(sk, newsk)) अणु
		sk_मुक्त_unlock_clone(newsk);
		newsk = शून्य;
		जाओ out;
	पूर्ण

	/* Clear sk_user_data अगर parent had the poपूर्णांकer tagged
	 * as not suitable क्रम copying when cloning.
	 */
	अगर (sk_user_data_is_nocopy(newsk))
		newsk->sk_user_data = शून्य;

	newsk->sk_err	   = 0;
	newsk->sk_err_soft = 0;
	newsk->sk_priority = 0;
	newsk->sk_incoming_cpu = raw_smp_processor_id();
	अगर (likely(newsk->sk_net_refcnt))
		sock_inuse_add(sock_net(newsk), 1);

	/* Beक्रमe updating sk_refcnt, we must commit prior changes to memory
	 * (Documentation/RCU/rculist_nulls.rst क्रम details)
	 */
	smp_wmb();
	refcount_set(&newsk->sk_refcnt, 2);

	/* Increment the counter in the same काष्ठा proto as the master
	 * sock (sk_refcnt_debug_inc uses newsk->sk_prot->socks, that
	 * is the same as sk->sk_prot->socks, as this field was copied
	 * with स_नकल).
	 *
	 * This _changes_ the previous behaviour, where
	 * tcp_create_खोलोreq_child always was incrementing the
	 * equivalent to tcp_prot->socks (inet_sock_nr), so this have
	 * to be taken पूर्णांकo account in all callers. -acme
	 */
	sk_refcnt_debug_inc(newsk);
	sk_set_socket(newsk, शून्य);
	sk_tx_queue_clear(newsk);
	RCU_INIT_POINTER(newsk->sk_wq, शून्य);

	अगर (newsk->sk_prot->sockets_allocated)
		sk_sockets_allocated_inc(newsk);

	अगर (sock_needs_netstamp(sk) && newsk->sk_flags & SK_FLAGS_TIMESTAMP)
		net_enable_बारtamp();
out:
	वापस newsk;
पूर्ण
EXPORT_SYMBOL_GPL(sk_clone_lock);

व्योम sk_मुक्त_unlock_clone(काष्ठा sock *sk)
अणु
	/* It is still raw copy of parent, so invalidate
	 * deकाष्ठाor and make plain sk_मुक्त() */
	sk->sk_deकाष्ठा = शून्य;
	bh_unlock_sock(sk);
	sk_मुक्त(sk);
पूर्ण
EXPORT_SYMBOL_GPL(sk_मुक्त_unlock_clone);

व्योम sk_setup_caps(काष्ठा sock *sk, काष्ठा dst_entry *dst)
अणु
	u32 max_segs = 1;

	sk_dst_set(sk, dst);
	sk->sk_route_caps = dst->dev->features | sk->sk_route_क्रमced_caps;
	अगर (sk->sk_route_caps & NETIF_F_GSO)
		sk->sk_route_caps |= NETIF_F_GSO_SOFTWARE;
	sk->sk_route_caps &= ~sk->sk_route_nocaps;
	अगर (sk_can_gso(sk)) अणु
		अगर (dst->header_len && !xfrm_dst_offload_ok(dst)) अणु
			sk->sk_route_caps &= ~NETIF_F_GSO_MASK;
		पूर्ण अन्यथा अणु
			sk->sk_route_caps |= NETIF_F_SG | NETIF_F_HW_CSUM;
			sk->sk_gso_max_size = dst->dev->gso_max_size;
			max_segs = max_t(u32, dst->dev->gso_max_segs, 1);
		पूर्ण
	पूर्ण
	sk->sk_gso_max_segs = max_segs;
पूर्ण
EXPORT_SYMBOL_GPL(sk_setup_caps);

/*
 *	Simple resource managers क्रम sockets.
 */


/*
 * Write buffer deकाष्ठाor स्वतःmatically called from kमुक्त_skb.
 */
व्योम sock_wमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	अचिन्हित पूर्णांक len = skb->truesize;

	अगर (!sock_flag(sk, SOCK_USE_WRITE_QUEUE)) अणु
		/*
		 * Keep a reference on sk_wmem_alloc, this will be released
		 * after sk_ग_लिखो_space() call
		 */
		WARN_ON(refcount_sub_and_test(len - 1, &sk->sk_wmem_alloc));
		sk->sk_ग_लिखो_space(sk);
		len = 1;
	पूर्ण
	/*
	 * अगर sk_wmem_alloc reaches 0, we must finish what sk_मुक्त()
	 * could not करो because of in-flight packets
	 */
	अगर (refcount_sub_and_test(len, &sk->sk_wmem_alloc))
		__sk_मुक्त(sk);
पूर्ण
EXPORT_SYMBOL(sock_wमुक्त);

/* This variant of sock_wमुक्त() is used by TCP,
 * since it sets SOCK_USE_WRITE_QUEUE.
 */
व्योम __sock_wमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;

	अगर (refcount_sub_and_test(skb->truesize, &sk->sk_wmem_alloc))
		__sk_मुक्त(sk);
पूर्ण

व्योम skb_set_owner_w(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	skb_orphan(skb);
	skb->sk = sk;
#अगर_घोषित CONFIG_INET
	अगर (unlikely(!sk_fullsock(sk))) अणु
		skb->deकाष्ठाor = sock_edemux;
		sock_hold(sk);
		वापस;
	पूर्ण
#पूर्ण_अगर
	skb->deकाष्ठाor = sock_wमुक्त;
	skb_set_hash_from_sk(skb, sk);
	/*
	 * We used to take a refcount on sk, but following operation
	 * is enough to guarantee sk_मुक्त() wont मुक्त this sock until
	 * all in-flight packets are completed
	 */
	refcount_add(skb->truesize, &sk->sk_wmem_alloc);
पूर्ण
EXPORT_SYMBOL(skb_set_owner_w);

अटल bool can_skb_orphan_partial(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_TLS_DEVICE
	/* Drivers depend on in-order delivery क्रम crypto offload,
	 * partial orphan अवरोधs out-of-order-OK logic.
	 */
	अगर (skb->decrypted)
		वापस false;
#पूर्ण_अगर
	वापस (skb->deकाष्ठाor == sock_wमुक्त ||
		(IS_ENABLED(CONFIG_INET) && skb->deकाष्ठाor == tcp_wमुक्त));
पूर्ण

/* This helper is used by netem, as it can hold packets in its
 * delay queue. We want to allow the owner socket to send more
 * packets, as अगर they were alपढ़ोy TX completed by a typical driver.
 * But we also want to keep skb->sk set because some packet schedulers
 * rely on it (sch_fq क्रम example).
 */
व्योम skb_orphan_partial(काष्ठा sk_buff *skb)
अणु
	अगर (skb_is_tcp_pure_ack(skb))
		वापस;

	अगर (can_skb_orphan_partial(skb) && skb_set_owner_sk_safe(skb, skb->sk))
		वापस;

	skb_orphan(skb);
पूर्ण
EXPORT_SYMBOL(skb_orphan_partial);

/*
 * Read buffer deकाष्ठाor स्वतःmatically called from kमुक्त_skb.
 */
व्योम sock_rमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;
	अचिन्हित पूर्णांक len = skb->truesize;

	atomic_sub(len, &sk->sk_rmem_alloc);
	sk_mem_unअक्षरge(sk, len);
पूर्ण
EXPORT_SYMBOL(sock_rमुक्त);

/*
 * Buffer deकाष्ठाor क्रम skbs that are not used directly in पढ़ो or ग_लिखो
 * path, e.g. क्रम error handler skbs. Automatically called from kमुक्त_skb.
 */
व्योम sock_eमुक्त(काष्ठा sk_buff *skb)
अणु
	sock_put(skb->sk);
पूर्ण
EXPORT_SYMBOL(sock_eमुक्त);

/* Buffer deकाष्ठाor क्रम prefetch/receive path where reference count may
 * not be held, e.g. क्रम listen sockets.
 */
#अगर_घोषित CONFIG_INET
व्योम sock_pमुक्त(काष्ठा sk_buff *skb)
अणु
	अगर (sk_is_refcounted(skb->sk))
		sock_gen_put(skb->sk);
पूर्ण
EXPORT_SYMBOL(sock_pमुक्त);
#पूर्ण_अगर /* CONFIG_INET */

kuid_t sock_i_uid(काष्ठा sock *sk)
अणु
	kuid_t uid;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	uid = sk->sk_socket ? SOCK_INODE(sk->sk_socket)->i_uid : GLOBAL_ROOT_UID;
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	वापस uid;
पूर्ण
EXPORT_SYMBOL(sock_i_uid);

अचिन्हित दीर्घ sock_i_ino(काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ ino;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	ino = sk->sk_socket ? SOCK_INODE(sk->sk_socket)->i_ino : 0;
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	वापस ino;
पूर्ण
EXPORT_SYMBOL(sock_i_ino);

/*
 * Allocate a skb from the socket's send buffer.
 */
काष्ठा sk_buff *sock_wदो_स्मृति(काष्ठा sock *sk, अचिन्हित दीर्घ size, पूर्णांक क्रमce,
			     gfp_t priority)
अणु
	अगर (क्रमce ||
	    refcount_पढ़ो(&sk->sk_wmem_alloc) < READ_ONCE(sk->sk_sndbuf)) अणु
		काष्ठा sk_buff *skb = alloc_skb(size, priority);

		अगर (skb) अणु
			skb_set_owner_w(skb, sk);
			वापस skb;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(sock_wदो_स्मृति);

अटल व्योम sock_oमुक्त(काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;

	atomic_sub(skb->truesize, &sk->sk_omem_alloc);
पूर्ण

काष्ठा sk_buff *sock_oदो_स्मृति(काष्ठा sock *sk, अचिन्हित दीर्घ size,
			     gfp_t priority)
अणु
	काष्ठा sk_buff *skb;

	/* small safe race: SKB_TRUESIZE may dअगरfer from final skb->truesize */
	अगर (atomic_पढ़ो(&sk->sk_omem_alloc) + SKB_TRUESIZE(size) >
	    sysctl_opपंचांगem_max)
		वापस शून्य;

	skb = alloc_skb(size, priority);
	अगर (!skb)
		वापस शून्य;

	atomic_add(skb->truesize, &sk->sk_omem_alloc);
	skb->sk = sk;
	skb->deकाष्ठाor = sock_oमुक्त;
	वापस skb;
पूर्ण

/*
 * Allocate a memory block from the socket's option memory buffer.
 */
व्योम *sock_kदो_स्मृति(काष्ठा sock *sk, पूर्णांक size, gfp_t priority)
अणु
	अगर ((अचिन्हित पूर्णांक)size <= sysctl_opपंचांगem_max &&
	    atomic_पढ़ो(&sk->sk_omem_alloc) + size < sysctl_opपंचांगem_max) अणु
		व्योम *mem;
		/* First करो the add, to aव्योम the race अगर kदो_स्मृति
		 * might sleep.
		 */
		atomic_add(size, &sk->sk_omem_alloc);
		mem = kदो_स्मृति(size, priority);
		अगर (mem)
			वापस mem;
		atomic_sub(size, &sk->sk_omem_alloc);
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(sock_kदो_स्मृति);

/* Free an option memory block. Note, we actually want the अंतरभूत
 * here as this allows gcc to detect the nullअगरy and fold away the
 * condition entirely.
 */
अटल अंतरभूत व्योम __sock_kमुक्त_s(काष्ठा sock *sk, व्योम *mem, पूर्णांक size,
				  स्थिर bool nullअगरy)
अणु
	अगर (WARN_ON_ONCE(!mem))
		वापस;
	अगर (nullअगरy)
		kमुक्त_sensitive(mem);
	अन्यथा
		kमुक्त(mem);
	atomic_sub(size, &sk->sk_omem_alloc);
पूर्ण

व्योम sock_kमुक्त_s(काष्ठा sock *sk, व्योम *mem, पूर्णांक size)
अणु
	__sock_kमुक्त_s(sk, mem, size, false);
पूर्ण
EXPORT_SYMBOL(sock_kमुक्त_s);

व्योम sock_kzमुक्त_s(काष्ठा sock *sk, व्योम *mem, पूर्णांक size)
अणु
	__sock_kमुक्त_s(sk, mem, size, true);
पूर्ण
EXPORT_SYMBOL(sock_kzमुक्त_s);

/* It is almost रुको_क्रम_tcp_memory minus release_sock/lock_sock.
   I think, these locks should be हटाओd क्रम datagram sockets.
 */
अटल दीर्घ sock_रुको_क्रम_wmem(काष्ठा sock *sk, दीर्घ समयo)
अणु
	DEFINE_WAIT(रुको);

	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);
	क्रम (;;) अणु
		अगर (!समयo)
			अवरोध;
		अगर (संकेत_pending(current))
			अवरोध;
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) < READ_ONCE(sk->sk_sndbuf))
			अवरोध;
		अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN)
			अवरोध;
		अगर (sk->sk_err)
			अवरोध;
		समयo = schedule_समयout(समयo);
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	वापस समयo;
पूर्ण


/*
 *	Generic send/receive buffer handlers
 */

काष्ठा sk_buff *sock_alloc_send_pskb(काष्ठा sock *sk, अचिन्हित दीर्घ header_len,
				     अचिन्हित दीर्घ data_len, पूर्णांक noblock,
				     पूर्णांक *errcode, पूर्णांक max_page_order)
अणु
	काष्ठा sk_buff *skb;
	दीर्घ समयo;
	पूर्णांक err;

	समयo = sock_sndसमयo(sk, noblock);
	क्रम (;;) अणु
		err = sock_error(sk);
		अगर (err != 0)
			जाओ failure;

		err = -EPIPE;
		अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN)
			जाओ failure;

		अगर (sk_wmem_alloc_get(sk) < READ_ONCE(sk->sk_sndbuf))
			अवरोध;

		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		err = -EAGAIN;
		अगर (!समयo)
			जाओ failure;
		अगर (संकेत_pending(current))
			जाओ पूर्णांकerrupted;
		समयo = sock_रुको_क्रम_wmem(sk, समयo);
	पूर्ण
	skb = alloc_skb_with_frags(header_len, data_len, max_page_order,
				   errcode, sk->sk_allocation);
	अगर (skb)
		skb_set_owner_w(skb, sk);
	वापस skb;

पूर्णांकerrupted:
	err = sock_पूर्णांकr_त्रुटि_सं(समयo);
failure:
	*errcode = err;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(sock_alloc_send_pskb);

काष्ठा sk_buff *sock_alloc_send_skb(काष्ठा sock *sk, अचिन्हित दीर्घ size,
				    पूर्णांक noblock, पूर्णांक *errcode)
अणु
	वापस sock_alloc_send_pskb(sk, size, 0, noblock, errcode, 0);
पूर्ण
EXPORT_SYMBOL(sock_alloc_send_skb);

पूर्णांक __sock_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg, काष्ठा cmsghdr *cmsg,
		     काष्ठा sockcm_cookie *sockc)
अणु
	u32 tsflags;

	चयन (cmsg->cmsg_type) अणु
	हाल SO_MARK:
		अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (cmsg->cmsg_len != CMSG_LEN(माप(u32)))
			वापस -EINVAL;
		sockc->mark = *(u32 *)CMSG_DATA(cmsg);
		अवरोध;
	हाल SO_TIMESTAMPING_OLD:
		अगर (cmsg->cmsg_len != CMSG_LEN(माप(u32)))
			वापस -EINVAL;

		tsflags = *(u32 *)CMSG_DATA(cmsg);
		अगर (tsflags & ~SOF_TIMESTAMPING_TX_RECORD_MASK)
			वापस -EINVAL;

		sockc->tsflags &= ~SOF_TIMESTAMPING_TX_RECORD_MASK;
		sockc->tsflags |= tsflags;
		अवरोध;
	हाल SCM_TXTIME:
		अगर (!sock_flag(sk, SOCK_TXTIME))
			वापस -EINVAL;
		अगर (cmsg->cmsg_len != CMSG_LEN(माप(u64)))
			वापस -EINVAL;
		sockc->transmit_समय = get_unaligned((u64 *)CMSG_DATA(cmsg));
		अवरोध;
	/* SCM_RIGHTS and SCM_CREDENTIALS are semantically in SOL_UNIX. */
	हाल SCM_RIGHTS:
	हाल SCM_CREDENTIALS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__sock_cmsg_send);

पूर्णांक sock_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg,
		   काष्ठा sockcm_cookie *sockc)
अणु
	काष्ठा cmsghdr *cmsg;
	पूर्णांक ret;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;
		अगर (cmsg->cmsg_level != SOL_SOCKET)
			जारी;
		ret = __sock_cmsg_send(sk, msg, cmsg, sockc);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sock_cmsg_send);

अटल व्योम sk_enter_memory_pressure(काष्ठा sock *sk)
अणु
	अगर (!sk->sk_prot->enter_memory_pressure)
		वापस;

	sk->sk_prot->enter_memory_pressure(sk);
पूर्ण

अटल व्योम sk_leave_memory_pressure(काष्ठा sock *sk)
अणु
	अगर (sk->sk_prot->leave_memory_pressure) अणु
		sk->sk_prot->leave_memory_pressure(sk);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ *memory_pressure = sk->sk_prot->memory_pressure;

		अगर (memory_pressure && READ_ONCE(*memory_pressure))
			WRITE_ONCE(*memory_pressure, 0);
	पूर्ण
पूर्ण

#घोषणा SKB_FRAG_PAGE_ORDER	get_order(32768)
DEFINE_STATIC_KEY_FALSE(net_high_order_alloc_disable_key);

/**
 * skb_page_frag_refill - check that a page_frag contains enough room
 * @sz: minimum size of the fragment we want to get
 * @pfrag: poपूर्णांकer to page_frag
 * @gfp: priority क्रम memory allocation
 *
 * Note: While this allocator tries to use high order pages, there is
 * no guarantee that allocations succeed. Thereक्रमe, @sz MUST be
 * less or equal than PAGE_SIZE.
 */
bool skb_page_frag_refill(अचिन्हित पूर्णांक sz, काष्ठा page_frag *pfrag, gfp_t gfp)
अणु
	अगर (pfrag->page) अणु
		अगर (page_ref_count(pfrag->page) == 1) अणु
			pfrag->offset = 0;
			वापस true;
		पूर्ण
		अगर (pfrag->offset + sz <= pfrag->size)
			वापस true;
		put_page(pfrag->page);
	पूर्ण

	pfrag->offset = 0;
	अगर (SKB_FRAG_PAGE_ORDER &&
	    !अटल_branch_unlikely(&net_high_order_alloc_disable_key)) अणु
		/* Aव्योम direct reclaim but allow kswapd to wake */
		pfrag->page = alloc_pages((gfp & ~__GFP_सूचीECT_RECLAIM) |
					  __GFP_COMP | __GFP_NOWARN |
					  __GFP_NORETRY,
					  SKB_FRAG_PAGE_ORDER);
		अगर (likely(pfrag->page)) अणु
			pfrag->size = PAGE_SIZE << SKB_FRAG_PAGE_ORDER;
			वापस true;
		पूर्ण
	पूर्ण
	pfrag->page = alloc_page(gfp);
	अगर (likely(pfrag->page)) अणु
		pfrag->size = PAGE_SIZE;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(skb_page_frag_refill);

bool sk_page_frag_refill(काष्ठा sock *sk, काष्ठा page_frag *pfrag)
अणु
	अगर (likely(skb_page_frag_refill(32U, pfrag, sk->sk_allocation)))
		वापस true;

	sk_enter_memory_pressure(sk);
	sk_stream_moderate_sndbuf(sk);
	वापस false;
पूर्ण
EXPORT_SYMBOL(sk_page_frag_refill);

व्योम __lock_sock(काष्ठा sock *sk)
	__releases(&sk->sk_lock.slock)
	__acquires(&sk->sk_lock.slock)
अणु
	DEFINE_WAIT(रुको);

	क्रम (;;) अणु
		prepare_to_रुको_exclusive(&sk->sk_lock.wq, &रुको,
					TASK_UNINTERRUPTIBLE);
		spin_unlock_bh(&sk->sk_lock.slock);
		schedule();
		spin_lock_bh(&sk->sk_lock.slock);
		अगर (!sock_owned_by_user(sk))
			अवरोध;
	पूर्ण
	finish_रुको(&sk->sk_lock.wq, &रुको);
पूर्ण

व्योम __release_sock(काष्ठा sock *sk)
	__releases(&sk->sk_lock.slock)
	__acquires(&sk->sk_lock.slock)
अणु
	काष्ठा sk_buff *skb, *next;

	जबतक ((skb = sk->sk_backlog.head) != शून्य) अणु
		sk->sk_backlog.head = sk->sk_backlog.tail = शून्य;

		spin_unlock_bh(&sk->sk_lock.slock);

		करो अणु
			next = skb->next;
			prefetch(next);
			WARN_ON_ONCE(skb_dst_is_noref(skb));
			skb_mark_not_on_list(skb);
			sk_backlog_rcv(sk, skb);

			cond_resched();

			skb = next;
		पूर्ण जबतक (skb != शून्य);

		spin_lock_bh(&sk->sk_lock.slock);
	पूर्ण

	/*
	 * Doing the zeroing here guarantee we can not loop क्रमever
	 * जबतक a wild producer attempts to flood us.
	 */
	sk->sk_backlog.len = 0;
पूर्ण

व्योम __sk_flush_backlog(काष्ठा sock *sk)
अणु
	spin_lock_bh(&sk->sk_lock.slock);
	__release_sock(sk);
	spin_unlock_bh(&sk->sk_lock.slock);
पूर्ण

/**
 * sk_रुको_data - रुको क्रम data to arrive at sk_receive_queue
 * @sk:    sock to रुको on
 * @समयo: क्रम how दीर्घ
 * @skb:   last skb seen on sk_receive_queue
 *
 * Now socket state including sk->sk_err is changed only under lock,
 * hence we may omit checks after joining रुको queue.
 * We check receive queue beक्रमe schedule() only as optimization;
 * it is very likely that release_sock() added new data.
 */
पूर्णांक sk_रुको_data(काष्ठा sock *sk, दीर्घ *समयo, स्थिर काष्ठा sk_buff *skb)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	पूर्णांक rc;

	add_रुको_queue(sk_sleep(sk), &रुको);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	rc = sk_रुको_event(sk, समयo, skb_peek_tail(&sk->sk_receive_queue) != skb, &रुको);
	sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(sk_रुको_data);

/**
 *	__sk_mem_उठाओ_allocated - increase memory_allocated
 *	@sk: socket
 *	@size: memory size to allocate
 *	@amt: pages to allocate
 *	@kind: allocation type
 *
 *	Similar to __sk_mem_schedule(), but करोes not update sk_क्रमward_alloc
 */
पूर्णांक __sk_mem_उठाओ_allocated(काष्ठा sock *sk, पूर्णांक size, पूर्णांक amt, पूर्णांक kind)
अणु
	काष्ठा proto *prot = sk->sk_prot;
	दीर्घ allocated = sk_memory_allocated_add(sk, amt);
	bool अक्षरged = true;

	अगर (mem_cgroup_sockets_enabled && sk->sk_memcg &&
	    !(अक्षरged = mem_cgroup_अक्षरge_skmem(sk->sk_memcg, amt)))
		जाओ suppress_allocation;

	/* Under limit. */
	अगर (allocated <= sk_prot_mem_limits(sk, 0)) अणु
		sk_leave_memory_pressure(sk);
		वापस 1;
	पूर्ण

	/* Under pressure. */
	अगर (allocated > sk_prot_mem_limits(sk, 1))
		sk_enter_memory_pressure(sk);

	/* Over hard limit. */
	अगर (allocated > sk_prot_mem_limits(sk, 2))
		जाओ suppress_allocation;

	/* guarantee minimum buffer size under pressure */
	अगर (kind == SK_MEM_RECV) अणु
		अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) < sk_get_rmem0(sk, prot))
			वापस 1;

	पूर्ण अन्यथा अणु /* SK_MEM_SEND */
		पूर्णांक wmem0 = sk_get_wmem0(sk, prot);

		अगर (sk->sk_type == SOCK_STREAM) अणु
			अगर (sk->sk_wmem_queued < wmem0)
				वापस 1;
		पूर्ण अन्यथा अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) < wmem0) अणु
				वापस 1;
		पूर्ण
	पूर्ण

	अगर (sk_has_memory_pressure(sk)) अणु
		u64 alloc;

		अगर (!sk_under_memory_pressure(sk))
			वापस 1;
		alloc = sk_sockets_allocated_पढ़ो_positive(sk);
		अगर (sk_prot_mem_limits(sk, 2) > alloc *
		    sk_mem_pages(sk->sk_wmem_queued +
				 atomic_पढ़ो(&sk->sk_rmem_alloc) +
				 sk->sk_क्रमward_alloc))
			वापस 1;
	पूर्ण

suppress_allocation:

	अगर (kind == SK_MEM_SEND && sk->sk_type == SOCK_STREAM) अणु
		sk_stream_moderate_sndbuf(sk);

		/* Fail only अगर socket is _under_ its sndbuf.
		 * In this हाल we cannot block, so that we have to fail.
		 */
		अगर (sk->sk_wmem_queued + size >= sk->sk_sndbuf)
			वापस 1;
	पूर्ण

	अगर (kind == SK_MEM_SEND || (kind == SK_MEM_RECV && अक्षरged))
		trace_sock_exceed_buf_limit(sk, prot, allocated, kind);

	sk_memory_allocated_sub(sk, amt);

	अगर (mem_cgroup_sockets_enabled && sk->sk_memcg)
		mem_cgroup_unअक्षरge_skmem(sk->sk_memcg, amt);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__sk_mem_उठाओ_allocated);

/**
 *	__sk_mem_schedule - increase sk_क्रमward_alloc and memory_allocated
 *	@sk: socket
 *	@size: memory size to allocate
 *	@kind: allocation type
 *
 *	If kind is SK_MEM_SEND, it means wmem allocation. Otherwise it means
 *	rmem allocation. This function assumes that protocols which have
 *	memory_pressure use sk_wmem_queued as ग_लिखो buffer accounting.
 */
पूर्णांक __sk_mem_schedule(काष्ठा sock *sk, पूर्णांक size, पूर्णांक kind)
अणु
	पूर्णांक ret, amt = sk_mem_pages(size);

	sk->sk_क्रमward_alloc += amt << SK_MEM_QUANTUM_SHIFT;
	ret = __sk_mem_उठाओ_allocated(sk, size, amt, kind);
	अगर (!ret)
		sk->sk_क्रमward_alloc -= amt << SK_MEM_QUANTUM_SHIFT;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__sk_mem_schedule);

/**
 *	__sk_mem_reduce_allocated - reclaim memory_allocated
 *	@sk: socket
 *	@amount: number of quanta
 *
 *	Similar to __sk_mem_reclaim(), but करोes not update sk_क्रमward_alloc
 */
व्योम __sk_mem_reduce_allocated(काष्ठा sock *sk, पूर्णांक amount)
अणु
	sk_memory_allocated_sub(sk, amount);

	अगर (mem_cgroup_sockets_enabled && sk->sk_memcg)
		mem_cgroup_unअक्षरge_skmem(sk->sk_memcg, amount);

	अगर (sk_under_memory_pressure(sk) &&
	    (sk_memory_allocated(sk) < sk_prot_mem_limits(sk, 0)))
		sk_leave_memory_pressure(sk);
पूर्ण
EXPORT_SYMBOL(__sk_mem_reduce_allocated);

/**
 *	__sk_mem_reclaim - reclaim sk_क्रमward_alloc and memory_allocated
 *	@sk: socket
 *	@amount: number of bytes (rounded करोwn to a SK_MEM_QUANTUM multiple)
 */
व्योम __sk_mem_reclaim(काष्ठा sock *sk, पूर्णांक amount)
अणु
	amount >>= SK_MEM_QUANTUM_SHIFT;
	sk->sk_क्रमward_alloc -= amount << SK_MEM_QUANTUM_SHIFT;
	__sk_mem_reduce_allocated(sk, amount);
पूर्ण
EXPORT_SYMBOL(__sk_mem_reclaim);

पूर्णांक sk_set_peek_off(काष्ठा sock *sk, पूर्णांक val)
अणु
	sk->sk_peek_off = val;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sk_set_peek_off);

/*
 * Set of शेष routines क्रम initialising काष्ठा proto_ops when
 * the protocol करोes not support a particular function. In certain
 * हालs where it makes no sense क्रम a protocol to have a "do nothing"
 * function, some शेष processing is provided.
 */

पूर्णांक sock_no_bind(काष्ठा socket *sock, काष्ठा sockaddr *saddr, पूर्णांक len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_bind);

पूर्णांक sock_no_connect(काष्ठा socket *sock, काष्ठा sockaddr *saddr,
		    पूर्णांक len, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_connect);

पूर्णांक sock_no_socketpair(काष्ठा socket *sock1, काष्ठा socket *sock2)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_socketpair);

पूर्णांक sock_no_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		   bool kern)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_accept);

पूर्णांक sock_no_getname(काष्ठा socket *sock, काष्ठा sockaddr *saddr,
		    पूर्णांक peer)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_getname);

पूर्णांक sock_no_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_ioctl);

पूर्णांक sock_no_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_listen);

पूर्णांक sock_no_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_shutकरोwn);

पूर्णांक sock_no_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_sendmsg);

पूर्णांक sock_no_sendmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *m, माप_प्रकार len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_sendmsg_locked);

पूर्णांक sock_no_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार len,
		    पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(sock_no_recvmsg);

पूर्णांक sock_no_mmap(काष्ठा file *file, काष्ठा socket *sock, काष्ठा vm_area_काष्ठा *vma)
अणु
	/* Mirror missing mmap method error code */
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(sock_no_mmap);

/*
 * When a file is received (via SCM_RIGHTS, etc), we must bump the
 * various sock-based usage counts.
 */
व्योम __receive_sock(काष्ठा file *file)
अणु
	काष्ठा socket *sock;

	sock = sock_from_file(file);
	अगर (sock) अणु
		sock_update_netprioidx(&sock->sk->sk_cgrp_data);
		sock_update_classid(&sock->sk->sk_cgrp_data);
	पूर्ण
पूर्ण

sमाप_प्रकार sock_no_sendpage(काष्ठा socket *sock, काष्ठा page *page, पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	sमाप_प्रकार res;
	काष्ठा msghdr msg = अणु.msg_flags = flagsपूर्ण;
	काष्ठा kvec iov;
	अक्षर *kaddr = kmap(page);
	iov.iov_base = kaddr + offset;
	iov.iov_len = size;
	res = kernel_sendmsg(sock, &msg, &iov, 1, size);
	kunmap(page);
	वापस res;
पूर्ण
EXPORT_SYMBOL(sock_no_sendpage);

sमाप_प्रकार sock_no_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page,
				पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	sमाप_प्रकार res;
	काष्ठा msghdr msg = अणु.msg_flags = flagsपूर्ण;
	काष्ठा kvec iov;
	अक्षर *kaddr = kmap(page);

	iov.iov_base = kaddr + offset;
	iov.iov_len = size;
	res = kernel_sendmsg_locked(sk, &msg, &iov, 1, size);
	kunmap(page);
	वापस res;
पूर्ण
EXPORT_SYMBOL(sock_no_sendpage_locked);

/*
 *	Default Socket Callbacks
 */

अटल व्योम sock_def_wakeup(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_all(&wq->रुको);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम sock_def_error_report(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_poll(&wq->रुको, EPOLLERR);
	sk_wake_async(sk, SOCK_WAKE_IO, POLL_ERR);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम sock_def_पढ़ोable(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLIN | EPOLLPRI |
						EPOLLRDNORM | EPOLLRDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम sock_def_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();

	/* Do not wake up a ग_लिखोr until he can make "significant"
	 * progress.  --DaveM
	 */
	अगर ((refcount_पढ़ो(&sk->sk_wmem_alloc) << 1) <= READ_ONCE(sk->sk_sndbuf)) अणु
		wq = rcu_dereference(sk->sk_wq);
		अगर (skwq_has_sleeper(wq))
			wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLOUT |
						EPOLLWRNORM | EPOLLWRBAND);

		/* Should agree with poll, otherwise some programs अवरोध */
		अगर (sock_ग_लिखोable(sk))
			sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम sock_def_deकाष्ठा(काष्ठा sock *sk)
अणु
पूर्ण

व्योम sk_send_sigurg(काष्ठा sock *sk)
अणु
	अगर (sk->sk_socket && sk->sk_socket->file)
		अगर (send_sigurg(&sk->sk_socket->file->f_owner))
			sk_wake_async(sk, SOCK_WAKE_URG, POLL_PRI);
पूर्ण
EXPORT_SYMBOL(sk_send_sigurg);

व्योम sk_reset_समयr(काष्ठा sock *sk, काष्ठा समयr_list* समयr,
		    अचिन्हित दीर्घ expires)
अणु
	अगर (!mod_समयr(समयr, expires))
		sock_hold(sk);
पूर्ण
EXPORT_SYMBOL(sk_reset_समयr);

व्योम sk_stop_समयr(काष्ठा sock *sk, काष्ठा समयr_list* समयr)
अणु
	अगर (del_समयr(समयr))
		__sock_put(sk);
पूर्ण
EXPORT_SYMBOL(sk_stop_समयr);

व्योम sk_stop_समयr_sync(काष्ठा sock *sk, काष्ठा समयr_list *समयr)
अणु
	अगर (del_समयr_sync(समयr))
		__sock_put(sk);
पूर्ण
EXPORT_SYMBOL(sk_stop_समयr_sync);

व्योम sock_init_data(काष्ठा socket *sock, काष्ठा sock *sk)
अणु
	sk_init_common(sk);
	sk->sk_send_head	=	शून्य;

	समयr_setup(&sk->sk_समयr, शून्य, 0);

	sk->sk_allocation	=	GFP_KERNEL;
	sk->sk_rcvbuf		=	sysctl_rmem_शेष;
	sk->sk_sndbuf		=	sysctl_wmem_शेष;
	sk->sk_state		=	TCP_CLOSE;
	sk_set_socket(sk, sock);

	sock_set_flag(sk, SOCK_ZAPPED);

	अगर (sock) अणु
		sk->sk_type	=	sock->type;
		RCU_INIT_POINTER(sk->sk_wq, &sock->wq);
		sock->sk	=	sk;
		sk->sk_uid	=	SOCK_INODE(sock)->i_uid;
	पूर्ण अन्यथा अणु
		RCU_INIT_POINTER(sk->sk_wq, शून्य);
		sk->sk_uid	=	make_kuid(sock_net(sk)->user_ns, 0);
	पूर्ण

	rwlock_init(&sk->sk_callback_lock);
	अगर (sk->sk_kern_sock)
		lockdep_set_class_and_name(
			&sk->sk_callback_lock,
			af_kern_callback_keys + sk->sk_family,
			af_family_kern_घड़ी_key_strings[sk->sk_family]);
	अन्यथा
		lockdep_set_class_and_name(
			&sk->sk_callback_lock,
			af_callback_keys + sk->sk_family,
			af_family_घड़ी_key_strings[sk->sk_family]);

	sk->sk_state_change	=	sock_def_wakeup;
	sk->sk_data_पढ़ोy	=	sock_def_पढ़ोable;
	sk->sk_ग_लिखो_space	=	sock_def_ग_लिखो_space;
	sk->sk_error_report	=	sock_def_error_report;
	sk->sk_deकाष्ठा		=	sock_def_deकाष्ठा;

	sk->sk_frag.page	=	शून्य;
	sk->sk_frag.offset	=	0;
	sk->sk_peek_off		=	-1;

	sk->sk_peer_pid 	=	शून्य;
	sk->sk_peer_cred	=	शून्य;
	sk->sk_ग_लिखो_pending	=	0;
	sk->sk_rcvlowat		=	1;
	sk->sk_rcvसमयo		=	MAX_SCHEDULE_TIMEOUT;
	sk->sk_sndसमयo		=	MAX_SCHEDULE_TIMEOUT;

	sk->sk_stamp = SK_DEFAULT_STAMP;
#अगर BITS_PER_LONG==32
	seqlock_init(&sk->sk_stamp_seq);
#पूर्ण_अगर
	atomic_set(&sk->sk_zckey, 0);

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	sk->sk_napi_id		=	0;
	sk->sk_ll_usec		=	sysctl_net_busy_पढ़ो;
#पूर्ण_अगर

	sk->sk_max_pacing_rate = ~0UL;
	sk->sk_pacing_rate = ~0UL;
	WRITE_ONCE(sk->sk_pacing_shअगरt, 10);
	sk->sk_incoming_cpu = -1;

	sk_rx_queue_clear(sk);
	/*
	 * Beक्रमe updating sk_refcnt, we must commit prior changes to memory
	 * (Documentation/RCU/rculist_nulls.rst क्रम details)
	 */
	smp_wmb();
	refcount_set(&sk->sk_refcnt, 1);
	atomic_set(&sk->sk_drops, 0);
पूर्ण
EXPORT_SYMBOL(sock_init_data);

व्योम lock_sock_nested(काष्ठा sock *sk, पूर्णांक subclass)
अणु
	might_sleep();
	spin_lock_bh(&sk->sk_lock.slock);
	अगर (sk->sk_lock.owned)
		__lock_sock(sk);
	sk->sk_lock.owned = 1;
	spin_unlock(&sk->sk_lock.slock);
	/*
	 * The sk_lock has mutex_lock() semantics here:
	 */
	mutex_acquire(&sk->sk_lock.dep_map, subclass, 0, _RET_IP_);
	local_bh_enable();
पूर्ण
EXPORT_SYMBOL(lock_sock_nested);

व्योम release_sock(काष्ठा sock *sk)
अणु
	spin_lock_bh(&sk->sk_lock.slock);
	अगर (sk->sk_backlog.tail)
		__release_sock(sk);

	/* Warning : release_cb() might need to release sk ownership,
	 * ie call sock_release_ownership(sk) beक्रमe us.
	 */
	अगर (sk->sk_prot->release_cb)
		sk->sk_prot->release_cb(sk);

	sock_release_ownership(sk);
	अगर (रुकोqueue_active(&sk->sk_lock.wq))
		wake_up(&sk->sk_lock.wq);
	spin_unlock_bh(&sk->sk_lock.slock);
पूर्ण
EXPORT_SYMBOL(release_sock);

/**
 * lock_sock_fast - fast version of lock_sock
 * @sk: socket
 *
 * This version should be used क्रम very small section, where process wont block
 * वापस false अगर fast path is taken:
 *
 *   sk_lock.slock locked, owned = 0, BH disabled
 *
 * वापस true अगर slow path is taken:
 *
 *   sk_lock.slock unlocked, owned = 1, BH enabled
 */
bool lock_sock_fast(काष्ठा sock *sk) __acquires(&sk->sk_lock.slock)
अणु
	might_sleep();
	spin_lock_bh(&sk->sk_lock.slock);

	अगर (!sk->sk_lock.owned)
		/*
		 * Note : We must disable BH
		 */
		वापस false;

	__lock_sock(sk);
	sk->sk_lock.owned = 1;
	spin_unlock(&sk->sk_lock.slock);
	/*
	 * The sk_lock has mutex_lock() semantics here:
	 */
	mutex_acquire(&sk->sk_lock.dep_map, 0, 0, _RET_IP_);
	__acquire(&sk->sk_lock.slock);
	local_bh_enable();
	वापस true;
पूर्ण
EXPORT_SYMBOL(lock_sock_fast);

पूर्णांक sock_gettstamp(काष्ठा socket *sock, व्योम __user *userstamp,
		   bool समयval, bool समय32)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा बारpec64 ts;

	sock_enable_बारtamp(sk, SOCK_TIMESTAMP);
	ts = kसमय_प्रकारo_बारpec64(sock_पढ़ो_बारtamp(sk));
	अगर (ts.tv_sec == -1)
		वापस -ENOENT;
	अगर (ts.tv_sec == 0) अणु
		kसमय_प्रकार kt = kसमय_get_real();
		sock_ग_लिखो_बारtamp(sk, kt);
		ts = kसमय_प्रकारo_बारpec64(kt);
	पूर्ण

	अगर (समयval)
		ts.tv_nsec /= 1000;

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
	अगर (समय32)
		वापस put_old_बारpec32(&ts, userstamp);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPARC64
	/* beware of padding in sparc64 समयval */
	अगर (समयval && !in_compat_syscall()) अणु
		काष्ठा __kernel_old_समयval __user tv = अणु
			.tv_sec = ts.tv_sec,
			.tv_usec = ts.tv_nsec,
		पूर्ण;
		अगर (copy_to_user(userstamp, &tv, माप(tv)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	वापस put_बारpec64(&ts, userstamp);
पूर्ण
EXPORT_SYMBOL(sock_gettstamp);

व्योम sock_enable_बारtamp(काष्ठा sock *sk, क्रमागत sock_flags flag)
अणु
	अगर (!sock_flag(sk, flag)) अणु
		अचिन्हित दीर्घ previous_flags = sk->sk_flags;

		sock_set_flag(sk, flag);
		/*
		 * we just set one of the two flags which require net
		 * समय stamping, but समय stamping might have been on
		 * alपढ़ोy because of the other one
		 */
		अगर (sock_needs_netstamp(sk) &&
		    !(previous_flags & SK_FLAGS_TIMESTAMP))
			net_enable_बारtamp();
	पूर्ण
पूर्ण

पूर्णांक sock_recv_errqueue(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len,
		       पूर्णांक level, पूर्णांक type)
अणु
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sk_buff *skb;
	पूर्णांक copied, err;

	err = -EAGAIN;
	skb = sock_dequeue_err_skb(sk);
	अगर (skb == शून्य)
		जाओ out;

	copied = skb->len;
	अगर (copied > len) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ out_मुक्त_skb;

	sock_recv_बारtamp(msg, sk, skb);

	serr = SKB_EXT_ERR(skb);
	put_cmsg(msg, level, type, माप(serr->ee), &serr->ee);

	msg->msg_flags |= MSG_ERRQUEUE;
	err = copied;

out_मुक्त_skb:
	kमुक्त_skb(skb);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(sock_recv_errqueue);

/*
 *	Get a socket option on an socket.
 *
 *	FIX: POSIX 1003.1g is very ambiguous here. It states that
 *	asynchronous errors should be reported by माला_लोockopt. We assume
 *	this means अगर you specअगरy SO_ERROR (otherwise whats the poपूर्णांक of it).
 */
पूर्णांक sock_common_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;

	वापस sk->sk_prot->माला_लोockopt(sk, level, optname, optval, optlen);
पूर्ण
EXPORT_SYMBOL(sock_common_माला_लोockopt);

पूर्णांक sock_common_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
			पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक addr_len = 0;
	पूर्णांक err;

	err = sk->sk_prot->recvmsg(sk, msg, size, flags & MSG_DONTWAIT,
				   flags & ~MSG_DONTWAIT, &addr_len);
	अगर (err >= 0)
		msg->msg_namelen = addr_len;
	वापस err;
पूर्ण
EXPORT_SYMBOL(sock_common_recvmsg);

/*
 *	Set socket options on an inet socket.
 */
पूर्णांक sock_common_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			   sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;

	वापस sk->sk_prot->setsockopt(sk, level, optname, optval, optlen);
पूर्ण
EXPORT_SYMBOL(sock_common_setsockopt);

व्योम sk_common_release(काष्ठा sock *sk)
अणु
	अगर (sk->sk_prot->destroy)
		sk->sk_prot->destroy(sk);

	/*
	 * Observation: when sk_common_release is called, processes have
	 * no access to socket. But net still has.
	 * Step one, detach it from networking:
	 *
	 * A. Remove from hash tables.
	 */

	sk->sk_prot->unhash(sk);

	/*
	 * In this poपूर्णांक socket cannot receive new packets, but it is possible
	 * that some packets are in flight because some CPU runs receiver and
	 * did hash table lookup beक्रमe we unhashed socket. They will achieve
	 * receive queue and will be purged by socket deकाष्ठाor.
	 *
	 * Also we still have packets pending on receive queue and probably,
	 * our own packets रुकोing in device queues. sock_destroy will drain
	 * receive queue, but transmitted packets will delay socket deकाष्ठाion
	 * until the last reference will be released.
	 */

	sock_orphan(sk);

	xfrm_sk_मुक्त_policy(sk);

	sk_refcnt_debug_release(sk);

	sock_put(sk);
पूर्ण
EXPORT_SYMBOL(sk_common_release);

व्योम sk_get_meminfo(स्थिर काष्ठा sock *sk, u32 *mem)
अणु
	स_रखो(mem, 0, माप(*mem) * SK_MEMINFO_VARS);

	mem[SK_MEMINFO_RMEM_ALLOC] = sk_rmem_alloc_get(sk);
	mem[SK_MEMINFO_RCVBUF] = READ_ONCE(sk->sk_rcvbuf);
	mem[SK_MEMINFO_WMEM_ALLOC] = sk_wmem_alloc_get(sk);
	mem[SK_MEMINFO_SNDBUF] = READ_ONCE(sk->sk_sndbuf);
	mem[SK_MEMINFO_FWD_ALLOC] = sk->sk_क्रमward_alloc;
	mem[SK_MEMINFO_WMEM_QUEUED] = READ_ONCE(sk->sk_wmem_queued);
	mem[SK_MEMINFO_OPTMEM] = atomic_पढ़ो(&sk->sk_omem_alloc);
	mem[SK_MEMINFO_BACKLOG] = READ_ONCE(sk->sk_backlog.len);
	mem[SK_MEMINFO_DROPS] = atomic_पढ़ो(&sk->sk_drops);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
#घोषणा PROTO_INUSE_NR	64	/* should be enough क्रम the first समय */
काष्ठा prot_inuse अणु
	पूर्णांक val[PROTO_INUSE_NR];
पूर्ण;

अटल DECLARE_BITMAP(proto_inuse_idx, PROTO_INUSE_NR);

व्योम sock_prot_inuse_add(काष्ठा net *net, काष्ठा proto *prot, पूर्णांक val)
अणु
	__this_cpu_add(net->core.prot_inuse->val[prot->inuse_idx], val);
पूर्ण
EXPORT_SYMBOL_GPL(sock_prot_inuse_add);

पूर्णांक sock_prot_inuse_get(काष्ठा net *net, काष्ठा proto *prot)
अणु
	पूर्णांक cpu, idx = prot->inuse_idx;
	पूर्णांक res = 0;

	क्रम_each_possible_cpu(cpu)
		res += per_cpu_ptr(net->core.prot_inuse, cpu)->val[idx];

	वापस res >= 0 ? res : 0;
पूर्ण
EXPORT_SYMBOL_GPL(sock_prot_inuse_get);

अटल व्योम sock_inuse_add(काष्ठा net *net, पूर्णांक val)
अणु
	this_cpu_add(*net->core.sock_inuse, val);
पूर्ण

पूर्णांक sock_inuse_get(काष्ठा net *net)
अणु
	पूर्णांक cpu, res = 0;

	क्रम_each_possible_cpu(cpu)
		res += *per_cpu_ptr(net->core.sock_inuse, cpu);

	वापस res;
पूर्ण

EXPORT_SYMBOL_GPL(sock_inuse_get);

अटल पूर्णांक __net_init sock_inuse_init_net(काष्ठा net *net)
अणु
	net->core.prot_inuse = alloc_percpu(काष्ठा prot_inuse);
	अगर (net->core.prot_inuse == शून्य)
		वापस -ENOMEM;

	net->core.sock_inuse = alloc_percpu(पूर्णांक);
	अगर (net->core.sock_inuse == शून्य)
		जाओ out;

	वापस 0;

out:
	मुक्त_percpu(net->core.prot_inuse);
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास sock_inuse_निकास_net(काष्ठा net *net)
अणु
	मुक्त_percpu(net->core.prot_inuse);
	मुक्त_percpu(net->core.sock_inuse);
पूर्ण

अटल काष्ठा pernet_operations net_inuse_ops = अणु
	.init = sock_inuse_init_net,
	.निकास = sock_inuse_निकास_net,
पूर्ण;

अटल __init पूर्णांक net_inuse_init(व्योम)
अणु
	अगर (रेजिस्टर_pernet_subsys(&net_inuse_ops))
		panic("Cannot initialize net inuse counters");

	वापस 0;
पूर्ण

core_initcall(net_inuse_init);

अटल पूर्णांक assign_proto_idx(काष्ठा proto *prot)
अणु
	prot->inuse_idx = find_first_zero_bit(proto_inuse_idx, PROTO_INUSE_NR);

	अगर (unlikely(prot->inuse_idx == PROTO_INUSE_NR - 1)) अणु
		pr_err("PROTO_INUSE_NR exhausted\n");
		वापस -ENOSPC;
	पूर्ण

	set_bit(prot->inuse_idx, proto_inuse_idx);
	वापस 0;
पूर्ण

अटल व्योम release_proto_idx(काष्ठा proto *prot)
अणु
	अगर (prot->inuse_idx != PROTO_INUSE_NR - 1)
		clear_bit(prot->inuse_idx, proto_inuse_idx);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक assign_proto_idx(काष्ठा proto *prot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम release_proto_idx(काष्ठा proto *prot)
अणु
पूर्ण

अटल व्योम sock_inuse_add(काष्ठा net *net, पूर्णांक val)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम tw_prot_cleanup(काष्ठा समयरुको_sock_ops *twsk_prot)
अणु
	अगर (!twsk_prot)
		वापस;
	kमुक्त(twsk_prot->twsk_slab_name);
	twsk_prot->twsk_slab_name = शून्य;
	kmem_cache_destroy(twsk_prot->twsk_slab);
	twsk_prot->twsk_slab = शून्य;
पूर्ण

अटल पूर्णांक tw_prot_init(स्थिर काष्ठा proto *prot)
अणु
	काष्ठा समयरुको_sock_ops *twsk_prot = prot->twsk_prot;

	अगर (!twsk_prot)
		वापस 0;

	twsk_prot->twsk_slab_name = kaप्र_लिखो(GFP_KERNEL, "tw_sock_%s",
					      prot->name);
	अगर (!twsk_prot->twsk_slab_name)
		वापस -ENOMEM;

	twsk_prot->twsk_slab =
		kmem_cache_create(twsk_prot->twsk_slab_name,
				  twsk_prot->twsk_obj_size, 0,
				  SLAB_ACCOUNT | prot->slab_flags,
				  शून्य);
	अगर (!twsk_prot->twsk_slab) अणु
		pr_crit("%s: Can't create timewait sock SLAB cache!\n",
			prot->name);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम req_prot_cleanup(काष्ठा request_sock_ops *rsk_prot)
अणु
	अगर (!rsk_prot)
		वापस;
	kमुक्त(rsk_prot->slab_name);
	rsk_prot->slab_name = शून्य;
	kmem_cache_destroy(rsk_prot->slab);
	rsk_prot->slab = शून्य;
पूर्ण

अटल पूर्णांक req_prot_init(स्थिर काष्ठा proto *prot)
अणु
	काष्ठा request_sock_ops *rsk_prot = prot->rsk_prot;

	अगर (!rsk_prot)
		वापस 0;

	rsk_prot->slab_name = kaप्र_लिखो(GFP_KERNEL, "request_sock_%s",
					prot->name);
	अगर (!rsk_prot->slab_name)
		वापस -ENOMEM;

	rsk_prot->slab = kmem_cache_create(rsk_prot->slab_name,
					   rsk_prot->obj_size, 0,
					   SLAB_ACCOUNT | prot->slab_flags,
					   शून्य);

	अगर (!rsk_prot->slab) अणु
		pr_crit("%s: Can't create request sock SLAB cache!\n",
			prot->name);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक proto_रेजिस्टर(काष्ठा proto *prot, पूर्णांक alloc_slab)
अणु
	पूर्णांक ret = -ENOBUFS;

	अगर (alloc_slab) अणु
		prot->slab = kmem_cache_create_usercopy(prot->name,
					prot->obj_size, 0,
					SLAB_HWCACHE_ALIGN | SLAB_ACCOUNT |
					prot->slab_flags,
					prot->useroffset, prot->usersize,
					शून्य);

		अगर (prot->slab == शून्य) अणु
			pr_crit("%s: Can't create sock SLAB cache!\n",
				prot->name);
			जाओ out;
		पूर्ण

		अगर (req_prot_init(prot))
			जाओ out_मुक्त_request_sock_slab;

		अगर (tw_prot_init(prot))
			जाओ out_मुक्त_समयरुको_sock_slab;
	पूर्ण

	mutex_lock(&proto_list_mutex);
	ret = assign_proto_idx(prot);
	अगर (ret) अणु
		mutex_unlock(&proto_list_mutex);
		जाओ out_मुक्त_समयरुको_sock_slab;
	पूर्ण
	list_add(&prot->node, &proto_list);
	mutex_unlock(&proto_list_mutex);
	वापस ret;

out_मुक्त_समयरुको_sock_slab:
	अगर (alloc_slab)
		tw_prot_cleanup(prot->twsk_prot);
out_मुक्त_request_sock_slab:
	अगर (alloc_slab) अणु
		req_prot_cleanup(prot->rsk_prot);

		kmem_cache_destroy(prot->slab);
		prot->slab = शून्य;
	पूर्ण
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(proto_रेजिस्टर);

व्योम proto_unरेजिस्टर(काष्ठा proto *prot)
अणु
	mutex_lock(&proto_list_mutex);
	release_proto_idx(prot);
	list_del(&prot->node);
	mutex_unlock(&proto_list_mutex);

	kmem_cache_destroy(prot->slab);
	prot->slab = शून्य;

	req_prot_cleanup(prot->rsk_prot);
	tw_prot_cleanup(prot->twsk_prot);
पूर्ण
EXPORT_SYMBOL(proto_unरेजिस्टर);

पूर्णांक sock_load_diag_module(पूर्णांक family, पूर्णांक protocol)
अणु
	अगर (!protocol) अणु
		अगर (!sock_is_रेजिस्टरed(family))
			वापस -ENOENT;

		वापस request_module("net-pf-%d-proto-%d-type-%d", PF_NETLINK,
				      NETLINK_SOCK_DIAG, family);
	पूर्ण

#अगर_घोषित CONFIG_INET
	अगर (family == AF_INET &&
	    protocol != IPPROTO_RAW &&
	    protocol < MAX_INET_PROTOS &&
	    !rcu_access_poपूर्णांकer(inet_protos[protocol]))
		वापस -ENOENT;
#पूर्ण_अगर

	वापस request_module("net-pf-%d-proto-%d-type-%d-%d", PF_NETLINK,
			      NETLINK_SOCK_DIAG, family, protocol);
पूर्ण
EXPORT_SYMBOL(sock_load_diag_module);

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *proto_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(proto_list_mutex)
अणु
	mutex_lock(&proto_list_mutex);
	वापस seq_list_start_head(&proto_list, *pos);
पूर्ण

अटल व्योम *proto_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &proto_list, pos);
पूर्ण

अटल व्योम proto_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(proto_list_mutex)
अणु
	mutex_unlock(&proto_list_mutex);
पूर्ण

अटल अक्षर proto_method_implemented(स्थिर व्योम *method)
अणु
	वापस method == शून्य ? 'n' : 'y';
पूर्ण
अटल दीर्घ sock_prot_memory_allocated(काष्ठा proto *proto)
अणु
	वापस proto->memory_allocated != शून्य ? proto_memory_allocated(proto) : -1L;
पूर्ण

अटल स्थिर अक्षर *sock_prot_memory_pressure(काष्ठा proto *proto)
अणु
	वापस proto->memory_pressure != शून्य ?
	proto_memory_pressure(proto) ? "yes" : "no" : "NI";
पूर्ण

अटल व्योम proto_seq_म_लिखो(काष्ठा seq_file *seq, काष्ठा proto *proto)
अणु

	seq_म_लिखो(seq, "%-9s %4u %6d  %6ld   %-3s %6u   %-3s  %-10s "
			"%2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c\n",
		   proto->name,
		   proto->obj_size,
		   sock_prot_inuse_get(seq_file_net(seq), proto),
		   sock_prot_memory_allocated(proto),
		   sock_prot_memory_pressure(proto),
		   proto->max_header,
		   proto->slab == शून्य ? "no" : "yes",
		   module_name(proto->owner),
		   proto_method_implemented(proto->बंद),
		   proto_method_implemented(proto->connect),
		   proto_method_implemented(proto->disconnect),
		   proto_method_implemented(proto->accept),
		   proto_method_implemented(proto->ioctl),
		   proto_method_implemented(proto->init),
		   proto_method_implemented(proto->destroy),
		   proto_method_implemented(proto->shutकरोwn),
		   proto_method_implemented(proto->setsockopt),
		   proto_method_implemented(proto->माला_लोockopt),
		   proto_method_implemented(proto->sendmsg),
		   proto_method_implemented(proto->recvmsg),
		   proto_method_implemented(proto->sendpage),
		   proto_method_implemented(proto->bind),
		   proto_method_implemented(proto->backlog_rcv),
		   proto_method_implemented(proto->hash),
		   proto_method_implemented(proto->unhash),
		   proto_method_implemented(proto->get_port),
		   proto_method_implemented(proto->enter_memory_pressure));
पूर्ण

अटल पूर्णांक proto_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == &proto_list)
		seq_म_लिखो(seq, "%-9s %-4s %-8s %-6s %-5s %-7s %-4s %-10s %s",
			   "protocol",
			   "size",
			   "sockets",
			   "memory",
			   "press",
			   "maxhdr",
			   "slab",
			   "module",
			   "cl co di ac io in de sh ss gs se re sp bi br ha uh gp em\n");
	अन्यथा
		proto_seq_म_लिखो(seq, list_entry(v, काष्ठा proto, node));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations proto_seq_ops = अणु
	.start  = proto_seq_start,
	.next   = proto_seq_next,
	.stop   = proto_seq_stop,
	.show   = proto_seq_show,
पूर्ण;

अटल __net_init पूर्णांक proto_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net("protocols", 0444, net->proc_net, &proto_seq_ops,
			माप(काष्ठा seq_net_निजी)))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल __net_निकास व्योम proto_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("protocols", net->proc_net);
पूर्ण


अटल __net_initdata काष्ठा pernet_operations proto_net_ops = अणु
	.init = proto_init_net,
	.निकास = proto_निकास_net,
पूर्ण;

अटल पूर्णांक __init proto_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&proto_net_ops);
पूर्ण

subsys_initcall(proto_init);

#पूर्ण_अगर /* PROC_FS */

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
bool sk_busy_loop_end(व्योम *p, अचिन्हित दीर्घ start_समय)
अणु
	काष्ठा sock *sk = p;

	वापस !skb_queue_empty_lockless(&sk->sk_receive_queue) ||
	       sk_busy_loop_समयout(sk, start_समय);
पूर्ण
EXPORT_SYMBOL(sk_busy_loop_end);
#पूर्ण_अगर /* CONFIG_NET_RX_BUSY_POLL */

पूर्णांक sock_bind_add(काष्ठा sock *sk, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	अगर (!sk->sk_prot->bind_add)
		वापस -EOPNOTSUPP;
	वापस sk->sk_prot->bind_add(sk, addr, addr_len);
पूर्ण
EXPORT_SYMBOL(sock_bind_add);
