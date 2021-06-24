<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NET4:	Implementation of BSD Unix करोमुख्य sockets.
 *
 * Authors:	Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *
 * Fixes:
 *		Linus Torvalds	:	Assorted bug cures.
 *		Niibe Yutaka	:	async I/O support.
 *		Carsten Paeth	:	PF_UNIX check, address fixes.
 *		Alan Cox	:	Limit size of allocated blocks.
 *		Alan Cox	:	Fixed the stupid socketpair bug.
 *		Alan Cox	:	BSD compatibility fine tuning.
 *		Alan Cox	:	Fixed a bug in connect when पूर्णांकerrupted.
 *		Alan Cox	:	Sorted out a proper draft version of
 *					file descriptor passing hacked up from
 *					Mike Shaver's work.
 *		Marty Leisner	:	Fixes to fd passing
 *		Nick Nevin	:	recvmsg bugfix.
 *		Alan Cox	:	Started proper garbage collector
 *		Heiko EiBfeldt	:	Missing verअगरy_area check
 *		Alan Cox	:	Started POSIXisms
 *		Andreas Schwab	:	Replace inode by dentry क्रम proper
 *					reference counting
 *		Kirk Petersen	:	Made this a module
 *	    Christoph Rohland	:	Elegant non-blocking accept/connect algorithm.
 *					Lots of bug fixes.
 *	     Alexey Kuznetosv	:	Repaired (I hope) bugs पूर्णांकroduces
 *					by above two patches.
 *	     Andrea Arcangeli	:	If possible we block in connect(2)
 *					अगर the max backlog of the listen socket
 *					is been reached. This won't अवरोध
 *					old apps and it will aव्योम huge amount
 *					of socks hashed (this क्रम unix_gc()
 *					perक्रमmances reasons).
 *					Security fix that limits the max
 *					number of socks to 2*max_files and
 *					the number of skb queueable in the
 *					dgram receiver.
 *		Artur Skawina   :	Hash function optimizations
 *	     Alexey Kuznetsov   :	Full scale SMP. Lot of bugs are पूर्णांकroduced 8)
 *	      Malcolm Beattie   :	Set peercred क्रम socketpair
 *	     Michal Ostrowski   :       Module initialization cleanup.
 *	     Arnalकरो C. Melo	:	Remove MOD_अणुINC,DECपूर्ण_USE_COUNT,
 *	     				the core infraकाष्ठाure is करोing that
 *	     				क्रम all net proto families now (2.5.69+)
 *
 * Known dअगरferences from reference BSD that was tested:
 *
 *	[TO FIX]
 *	ECONNREFUSED is not वापसed from one end of a connected() socket to the
 *		other the moment one end बंदs.
 *	ख_स्थिति() करोesn't वापस st_dev=0, and give the blksize as high water mark
 *		and a fake inode identअगरier (nor the BSD first socket ख_स्थिति twice bug).
 *	[NOT TO FIX]
 *	accept() वापसs a path name even अगर the connecting socket has बंदd
 *		in the meanसमय (BSD loses the path and gives up).
 *	accept() वापसs 0 length path क्रम an unbound connector. BSD वापसs 16
 *		and a null first byte in the path (but not क्रम gethost/peername - BSD bug ??)
 *	socketpair(...SOCK_RAW..) करोesn't panic the kernel.
 *	BSD af_unix apparently has connect क्रमgetting to block properly.
 *		(need to check this with the POSIX spec in detail)
 *
 * Dअगरferences from 2.0.0-11-... (ANK)
 *	Bug fixes and improvements.
 *		- client shutकरोwn समाप्तed server socket.
 *		- हटाओd all useless cli/sti pairs.
 *
 *	Semantic changes/extensions.
 *		- generic control message passing.
 *		- SCM_CREDENTIALS control message.
 *		- "Abstract" (not FS based) socket bindings.
 *		  Abstract names are sequences of bytes (not zero terminated)
 *		  started by 0, so that this name space करोes not पूर्णांकersect
 *		  with BSD names.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/dcache.h>
#समावेश <linux/namei.h>
#समावेश <linux/socket.h>
#समावेश <linux/un.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/af_unix.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/scm.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/mount.h>
#समावेश <net/checksum.h>
#समावेश <linux/security.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/file.h>

#समावेश "scm.h"

काष्ठा hlist_head unix_socket_table[2 * UNIX_HASH_SIZE];
EXPORT_SYMBOL_GPL(unix_socket_table);
DEFINE_SPINLOCK(unix_table_lock);
EXPORT_SYMBOL_GPL(unix_table_lock);
अटल atomic_दीर्घ_t unix_nr_socks;


अटल काष्ठा hlist_head *unix_sockets_unbound(व्योम *addr)
अणु
	अचिन्हित दीर्घ hash = (अचिन्हित दीर्घ)addr;

	hash ^= hash >> 16;
	hash ^= hash >> 8;
	hash %= UNIX_HASH_SIZE;
	वापस &unix_socket_table[UNIX_HASH_SIZE + hash];
पूर्ण

#घोषणा UNIX_ABSTRACT(sk)	(unix_sk(sk)->addr->hash < UNIX_HASH_SIZE)

#अगर_घोषित CONFIG_SECURITY_NETWORK
अटल व्योम unix_get_secdata(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु
	UNIXCB(skb).secid = scm->secid;
पूर्ण

अटल अंतरभूत व्योम unix_set_secdata(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु
	scm->secid = UNIXCB(skb).secid;
पूर्ण

अटल अंतरभूत bool unix_secdata_eq(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु
	वापस (scm->secid == UNIXCB(skb).secid);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम unix_get_secdata(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु पूर्ण

अटल अंतरभूत व्योम unix_set_secdata(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु पूर्ण

अटल अंतरभूत bool unix_secdata_eq(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECURITY_NETWORK */

/*
 *  SMP locking strategy:
 *    hash table is रक्षित with spinlock unix_table_lock
 *    each socket state is रक्षित by separate spin lock.
 */

अटल अंतरभूत अचिन्हित पूर्णांक unix_hash_fold(__wsum n)
अणु
	अचिन्हित पूर्णांक hash = (__क्रमce अचिन्हित पूर्णांक)csum_fold(n);

	hash ^= hash>>8;
	वापस hash&(UNIX_HASH_SIZE-1);
पूर्ण

#घोषणा unix_peer(sk) (unix_sk(sk)->peer)

अटल अंतरभूत पूर्णांक unix_our_peer(काष्ठा sock *sk, काष्ठा sock *osk)
अणु
	वापस unix_peer(osk) == sk;
पूर्ण

अटल अंतरभूत पूर्णांक unix_may_send(काष्ठा sock *sk, काष्ठा sock *osk)
अणु
	वापस unix_peer(osk) == शून्य || unix_our_peer(sk, osk);
पूर्ण

अटल अंतरभूत पूर्णांक unix_recvq_full(स्थिर काष्ठा sock *sk)
अणु
	वापस skb_queue_len(&sk->sk_receive_queue) > sk->sk_max_ack_backlog;
पूर्ण

अटल अंतरभूत पूर्णांक unix_recvq_full_lockless(स्थिर काष्ठा sock *sk)
अणु
	वापस skb_queue_len_lockless(&sk->sk_receive_queue) >
		READ_ONCE(sk->sk_max_ack_backlog);
पूर्ण

काष्ठा sock *unix_peer_get(काष्ठा sock *s)
अणु
	काष्ठा sock *peer;

	unix_state_lock(s);
	peer = unix_peer(s);
	अगर (peer)
		sock_hold(peer);
	unix_state_unlock(s);
	वापस peer;
पूर्ण
EXPORT_SYMBOL_GPL(unix_peer_get);

अटल अंतरभूत व्योम unix_release_addr(काष्ठा unix_address *addr)
अणु
	अगर (refcount_dec_and_test(&addr->refcnt))
		kमुक्त(addr);
पूर्ण

/*
 *	Check unix socket name:
 *		- should be not zero length.
 *	        - अगर started by not zero, should be शून्य terminated (FS object)
 *		- अगर started by zero, it is असलtract name.
 */

अटल पूर्णांक unix_mkname(काष्ठा sockaddr_un *sunaddr, पूर्णांक len, अचिन्हित पूर्णांक *hashp)
अणु
	*hashp = 0;

	अगर (len <= माप(लघु) || len > माप(*sunaddr))
		वापस -EINVAL;
	अगर (!sunaddr || sunaddr->sun_family != AF_UNIX)
		वापस -EINVAL;
	अगर (sunaddr->sun_path[0]) अणु
		/*
		 * This may look like an off by one error but it is a bit more
		 * subtle. 108 is the दीर्घest valid AF_UNIX path क्रम a binding.
		 * sun_path[108] करोesn't as such exist.  However in kernel space
		 * we are guaranteed that it is a valid memory location in our
		 * kernel address buffer.
		 */
		((अक्षर *)sunaddr)[len] = 0;
		len = म_माप(sunaddr->sun_path)+1+माप(लघु);
		वापस len;
	पूर्ण

	*hashp = unix_hash_fold(csum_partial(sunaddr, len, 0));
	वापस len;
पूर्ण

अटल व्योम __unix_हटाओ_socket(काष्ठा sock *sk)
अणु
	sk_del_node_init(sk);
पूर्ण

अटल व्योम __unix_insert_socket(काष्ठा hlist_head *list, काष्ठा sock *sk)
अणु
	WARN_ON(!sk_unhashed(sk));
	sk_add_node(sk, list);
पूर्ण

अटल अंतरभूत व्योम unix_हटाओ_socket(काष्ठा sock *sk)
अणु
	spin_lock(&unix_table_lock);
	__unix_हटाओ_socket(sk);
	spin_unlock(&unix_table_lock);
पूर्ण

अटल अंतरभूत व्योम unix_insert_socket(काष्ठा hlist_head *list, काष्ठा sock *sk)
अणु
	spin_lock(&unix_table_lock);
	__unix_insert_socket(list, sk);
	spin_unlock(&unix_table_lock);
पूर्ण

अटल काष्ठा sock *__unix_find_socket_byname(काष्ठा net *net,
					      काष्ठा sockaddr_un *sunname,
					      पूर्णांक len, पूर्णांक type, अचिन्हित पूर्णांक hash)
अणु
	काष्ठा sock *s;

	sk_क्रम_each(s, &unix_socket_table[hash ^ type]) अणु
		काष्ठा unix_sock *u = unix_sk(s);

		अगर (!net_eq(sock_net(s), net))
			जारी;

		अगर (u->addr->len == len &&
		    !स_भेद(u->addr->name, sunname, len))
			वापस s;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा sock *unix_find_socket_byname(काष्ठा net *net,
						   काष्ठा sockaddr_un *sunname,
						   पूर्णांक len, पूर्णांक type,
						   अचिन्हित पूर्णांक hash)
अणु
	काष्ठा sock *s;

	spin_lock(&unix_table_lock);
	s = __unix_find_socket_byname(net, sunname, len, type, hash);
	अगर (s)
		sock_hold(s);
	spin_unlock(&unix_table_lock);
	वापस s;
पूर्ण

अटल काष्ठा sock *unix_find_socket_byinode(काष्ठा inode *i)
अणु
	काष्ठा sock *s;

	spin_lock(&unix_table_lock);
	sk_क्रम_each(s,
		    &unix_socket_table[i->i_ino & (UNIX_HASH_SIZE - 1)]) अणु
		काष्ठा dentry *dentry = unix_sk(s)->path.dentry;

		अगर (dentry && d_backing_inode(dentry) == i) अणु
			sock_hold(s);
			जाओ found;
		पूर्ण
	पूर्ण
	s = शून्य;
found:
	spin_unlock(&unix_table_lock);
	वापस s;
पूर्ण

/* Support code क्रम asymmetrically connected dgram sockets
 *
 * If a datagram socket is connected to a socket not itself connected
 * to the first socket (eg, /dev/log), clients may only enqueue more
 * messages अगर the present receive queue of the server socket is not
 * "too large". This means there's a second ग_लिखोability condition
 * poll and sendmsg need to test. The dgram recv code will करो a wake
 * up on the peer_रुको रुको queue of a socket upon reception of a
 * datagram which needs to be propagated to sleeping would-be ग_लिखोrs
 * since these might not have sent anything so far. This can't be
 * accomplished via poll_रुको because the lअगरeसमय of the server
 * socket might be less than that of its clients अगर these अवरोध their
 * association with it or अगर the server socket is बंदd जबतक clients
 * are still connected to it and there's no way to inक्रमm "a polling
 * implementation" that it should let go of a certain रुको queue
 *
 * In order to propagate a wake up, a रुको_queue_entry_t of the client
 * socket is enqueued on the peer_रुको queue of the server socket
 * whose wake function करोes a wake_up on the ordinary client socket
 * रुको queue. This connection is established whenever a ग_लिखो (or
 * poll क्रम ग_लिखो) hit the flow control condition and broken when the
 * association to the server socket is dissolved or after a wake up
 * was relayed.
 */

अटल पूर्णांक unix_dgram_peer_wake_relay(रुको_queue_entry_t *q, अचिन्हित mode, पूर्णांक flags,
				      व्योम *key)
अणु
	काष्ठा unix_sock *u;
	रुको_queue_head_t *u_sleep;

	u = container_of(q, काष्ठा unix_sock, peer_wake);

	__हटाओ_रुको_queue(&unix_sk(u->peer_wake.निजी)->peer_रुको,
			    q);
	u->peer_wake.निजी = शून्य;

	/* relaying can only happen जबतक the wq still exists */
	u_sleep = sk_sleep(&u->sk);
	अगर (u_sleep)
		wake_up_पूर्णांकerruptible_poll(u_sleep, key_to_poll(key));

	वापस 0;
पूर्ण

अटल पूर्णांक unix_dgram_peer_wake_connect(काष्ठा sock *sk, काष्ठा sock *other)
अणु
	काष्ठा unix_sock *u, *u_other;
	पूर्णांक rc;

	u = unix_sk(sk);
	u_other = unix_sk(other);
	rc = 0;
	spin_lock(&u_other->peer_रुको.lock);

	अगर (!u->peer_wake.निजी) अणु
		u->peer_wake.निजी = other;
		__add_रुको_queue(&u_other->peer_रुको, &u->peer_wake);

		rc = 1;
	पूर्ण

	spin_unlock(&u_other->peer_रुको.lock);
	वापस rc;
पूर्ण

अटल व्योम unix_dgram_peer_wake_disconnect(काष्ठा sock *sk,
					    काष्ठा sock *other)
अणु
	काष्ठा unix_sock *u, *u_other;

	u = unix_sk(sk);
	u_other = unix_sk(other);
	spin_lock(&u_other->peer_रुको.lock);

	अगर (u->peer_wake.निजी == other) अणु
		__हटाओ_रुको_queue(&u_other->peer_रुको, &u->peer_wake);
		u->peer_wake.निजी = शून्य;
	पूर्ण

	spin_unlock(&u_other->peer_रुको.lock);
पूर्ण

अटल व्योम unix_dgram_peer_wake_disconnect_wakeup(काष्ठा sock *sk,
						   काष्ठा sock *other)
अणु
	unix_dgram_peer_wake_disconnect(sk, other);
	wake_up_पूर्णांकerruptible_poll(sk_sleep(sk),
				   EPOLLOUT |
				   EPOLLWRNORM |
				   EPOLLWRBAND);
पूर्ण

/* preconditions:
 *	- unix_peer(sk) == other
 *	- association is stable
 */
अटल पूर्णांक unix_dgram_peer_wake_me(काष्ठा sock *sk, काष्ठा sock *other)
अणु
	पूर्णांक connected;

	connected = unix_dgram_peer_wake_connect(sk, other);

	/* If other is SOCK_DEAD, we want to make sure we संकेत
	 * POLLOUT, such that a subsequent ग_लिखो() can get a
	 * -ECONNREFUSED. Otherwise, अगर we haven't queued any skbs
	 * to other and its full, we will hang रुकोing क्रम POLLOUT.
	 */
	अगर (unix_recvq_full(other) && !sock_flag(other, SOCK_DEAD))
		वापस 1;

	अगर (connected)
		unix_dgram_peer_wake_disconnect(sk, other);

	वापस 0;
पूर्ण

अटल पूर्णांक unix_writable(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_state != TCP_LISTEN &&
	       (refcount_पढ़ो(&sk->sk_wmem_alloc) << 2) <= sk->sk_sndbuf;
पूर्ण

अटल व्योम unix_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	अगर (unix_writable(sk)) अणु
		wq = rcu_dereference(sk->sk_wq);
		अगर (skwq_has_sleeper(wq))
			wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको,
				EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND);
		sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* When dgram socket disconnects (or changes its peer), we clear its receive
 * queue of packets arrived from previous peer. First, it allows to करो
 * flow control based only on wmem_alloc; second, sk connected to peer
 * may receive messages only from that peer. */
अटल व्योम unix_dgram_disconnected(काष्ठा sock *sk, काष्ठा sock *other)
अणु
	अगर (!skb_queue_empty(&sk->sk_receive_queue)) अणु
		skb_queue_purge(&sk->sk_receive_queue);
		wake_up_पूर्णांकerruptible_all(&unix_sk(sk)->peer_रुको);

		/* If one link of bidirectional dgram pipe is disconnected,
		 * we संकेत error. Messages are lost. Do not make this,
		 * when peer was not connected to us.
		 */
		अगर (!sock_flag(other, SOCK_DEAD) && unix_peer(other) == sk) अणु
			other->sk_err = ECONNRESET;
			other->sk_error_report(other);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम unix_sock_deकाष्ठाor(काष्ठा sock *sk)
अणु
	काष्ठा unix_sock *u = unix_sk(sk);

	skb_queue_purge(&sk->sk_receive_queue);

	WARN_ON(refcount_पढ़ो(&sk->sk_wmem_alloc));
	WARN_ON(!sk_unhashed(sk));
	WARN_ON(sk->sk_socket);
	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_info("Attempt to release alive unix socket: %p\n", sk);
		वापस;
	पूर्ण

	अगर (u->addr)
		unix_release_addr(u->addr);

	atomic_दीर्घ_dec(&unix_nr_socks);
	local_bh_disable();
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	local_bh_enable();
#अगर_घोषित UNIX_REFCNT_DEBUG
	pr_debug("UNIX %p is destroyed, %ld are still alive.\n", sk,
		atomic_दीर्घ_पढ़ो(&unix_nr_socks));
#पूर्ण_अगर
पूर्ण

अटल व्योम unix_release_sock(काष्ठा sock *sk, पूर्णांक embrion)
अणु
	काष्ठा unix_sock *u = unix_sk(sk);
	काष्ठा path path;
	काष्ठा sock *skpair;
	काष्ठा sk_buff *skb;
	पूर्णांक state;

	unix_हटाओ_socket(sk);

	/* Clear state */
	unix_state_lock(sk);
	sock_orphan(sk);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	path	     = u->path;
	u->path.dentry = शून्य;
	u->path.mnt = शून्य;
	state = sk->sk_state;
	sk->sk_state = TCP_CLOSE;

	skpair = unix_peer(sk);
	unix_peer(sk) = शून्य;

	unix_state_unlock(sk);

	wake_up_पूर्णांकerruptible_all(&u->peer_रुको);

	अगर (skpair != शून्य) अणु
		अगर (sk->sk_type == SOCK_STREAM || sk->sk_type == SOCK_SEQPACKET) अणु
			unix_state_lock(skpair);
			/* No more ग_लिखोs */
			skpair->sk_shutकरोwn = SHUTDOWN_MASK;
			अगर (!skb_queue_empty(&sk->sk_receive_queue) || embrion)
				skpair->sk_err = ECONNRESET;
			unix_state_unlock(skpair);
			skpair->sk_state_change(skpair);
			sk_wake_async(skpair, SOCK_WAKE_WAITD, POLL_HUP);
		पूर्ण

		unix_dgram_peer_wake_disconnect(sk, skpair);
		sock_put(skpair); /* It may now die */
	पूर्ण

	/* Try to flush out this socket. Throw out buffers at least */

	जबतक ((skb = skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		अगर (state == TCP_LISTEN)
			unix_release_sock(skb->sk, 1);
		/* passed fds are erased in the kमुक्त_skb hook	      */
		UNIXCB(skb).consumed = skb->len;
		kमुक्त_skb(skb);
	पूर्ण

	अगर (path.dentry)
		path_put(&path);

	sock_put(sk);

	/* ---- Socket is dead now and most probably destroyed ---- */

	/*
	 * Fixme: BSD dअगरference: In BSD all sockets connected to us get
	 *	  ECONNRESET and we die on the spot. In Linux we behave
	 *	  like files and pipes करो and रुको क्रम the last
	 *	  dereference.
	 *
	 * Can't we simply set sock->err?
	 *
	 *	  What the above comment करोes talk about? --ANK(980817)
	 */

	अगर (unix_tot_inflight)
		unix_gc();		/* Garbage collect fds */
पूर्ण

अटल व्योम init_peercred(काष्ठा sock *sk)
अणु
	put_pid(sk->sk_peer_pid);
	अगर (sk->sk_peer_cred)
		put_cred(sk->sk_peer_cred);
	sk->sk_peer_pid  = get_pid(task_tgid(current));
	sk->sk_peer_cred = get_current_cred();
पूर्ण

अटल व्योम copy_peercred(काष्ठा sock *sk, काष्ठा sock *peersk)
अणु
	put_pid(sk->sk_peer_pid);
	अगर (sk->sk_peer_cred)
		put_cred(sk->sk_peer_cred);
	sk->sk_peer_pid  = get_pid(peersk->sk_peer_pid);
	sk->sk_peer_cred = get_cred(peersk->sk_peer_cred);
पूर्ण

अटल पूर्णांक unix_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	पूर्णांक err;
	काष्ठा sock *sk = sock->sk;
	काष्ठा unix_sock *u = unix_sk(sk);

	err = -EOPNOTSUPP;
	अगर (sock->type != SOCK_STREAM && sock->type != SOCK_SEQPACKET)
		जाओ out;	/* Only stream/seqpacket sockets accept */
	err = -EINVAL;
	अगर (!u->addr)
		जाओ out;	/* No listens on an unbound socket */
	unix_state_lock(sk);
	अगर (sk->sk_state != TCP_CLOSE && sk->sk_state != TCP_LISTEN)
		जाओ out_unlock;
	अगर (backlog > sk->sk_max_ack_backlog)
		wake_up_पूर्णांकerruptible_all(&u->peer_रुको);
	sk->sk_max_ack_backlog	= backlog;
	sk->sk_state		= TCP_LISTEN;
	/* set credentials so connect can copy them */
	init_peercred(sk);
	err = 0;

out_unlock:
	unix_state_unlock(sk);
out:
	वापस err;
पूर्ण

अटल पूर्णांक unix_release(काष्ठा socket *);
अटल पूर्णांक unix_bind(काष्ठा socket *, काष्ठा sockaddr *, पूर्णांक);
अटल पूर्णांक unix_stream_connect(काष्ठा socket *, काष्ठा sockaddr *,
			       पूर्णांक addr_len, पूर्णांक flags);
अटल पूर्णांक unix_socketpair(काष्ठा socket *, काष्ठा socket *);
अटल पूर्णांक unix_accept(काष्ठा socket *, काष्ठा socket *, पूर्णांक, bool);
अटल पूर्णांक unix_getname(काष्ठा socket *, काष्ठा sockaddr *, पूर्णांक);
अटल __poll_t unix_poll(काष्ठा file *, काष्ठा socket *, poll_table *);
अटल __poll_t unix_dgram_poll(काष्ठा file *, काष्ठा socket *,
				    poll_table *);
अटल पूर्णांक unix_ioctl(काष्ठा socket *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक unix_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#पूर्ण_अगर
अटल पूर्णांक unix_shutकरोwn(काष्ठा socket *, पूर्णांक);
अटल पूर्णांक unix_stream_sendmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार);
अटल पूर्णांक unix_stream_recvmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार, पूर्णांक);
अटल sमाप_प्रकार unix_stream_sendpage(काष्ठा socket *, काष्ठा page *, पूर्णांक offset,
				    माप_प्रकार size, पूर्णांक flags);
अटल sमाप_प्रकार unix_stream_splice_पढ़ो(काष्ठा socket *,  loff_t *ppos,
				       काष्ठा pipe_inode_info *, माप_प्रकार size,
				       अचिन्हित पूर्णांक flags);
अटल पूर्णांक unix_dgram_sendmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार);
अटल पूर्णांक unix_dgram_recvmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार, पूर्णांक);
अटल पूर्णांक unix_dgram_connect(काष्ठा socket *, काष्ठा sockaddr *,
			      पूर्णांक, पूर्णांक);
अटल पूर्णांक unix_seqpacket_sendmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार);
अटल पूर्णांक unix_seqpacket_recvmsg(काष्ठा socket *, काष्ठा msghdr *, माप_प्रकार,
				  पूर्णांक);

अटल पूर्णांक unix_set_peek_off(काष्ठा sock *sk, पूर्णांक val)
अणु
	काष्ठा unix_sock *u = unix_sk(sk);

	अगर (mutex_lock_पूर्णांकerruptible(&u->iolock))
		वापस -EINTR;

	sk->sk_peek_off = val;
	mutex_unlock(&u->iolock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम unix_show_fdinfo(काष्ठा seq_file *m, काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा unix_sock *u;

	अगर (sk) अणु
		u = unix_sk(sock->sk);
		seq_म_लिखो(m, "scm_fds: %u\n",
			   atomic_पढ़ो(&u->scm_stat.nr_fds));
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा unix_show_fdinfo शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा proto_ops unix_stream_ops = अणु
	.family =	PF_UNIX,
	.owner =	THIS_MODULE,
	.release =	unix_release,
	.bind =		unix_bind,
	.connect =	unix_stream_connect,
	.socketpair =	unix_socketpair,
	.accept =	unix_accept,
	.getname =	unix_getname,
	.poll =		unix_poll,
	.ioctl =	unix_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl =	unix_compat_ioctl,
#पूर्ण_अगर
	.listen =	unix_listen,
	.shutकरोwn =	unix_shutकरोwn,
	.sendmsg =	unix_stream_sendmsg,
	.recvmsg =	unix_stream_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	unix_stream_sendpage,
	.splice_पढ़ो =	unix_stream_splice_पढ़ो,
	.set_peek_off =	unix_set_peek_off,
	.show_fdinfo =	unix_show_fdinfo,
पूर्ण;

अटल स्थिर काष्ठा proto_ops unix_dgram_ops = अणु
	.family =	PF_UNIX,
	.owner =	THIS_MODULE,
	.release =	unix_release,
	.bind =		unix_bind,
	.connect =	unix_dgram_connect,
	.socketpair =	unix_socketpair,
	.accept =	sock_no_accept,
	.getname =	unix_getname,
	.poll =		unix_dgram_poll,
	.ioctl =	unix_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl =	unix_compat_ioctl,
#पूर्ण_अगर
	.listen =	sock_no_listen,
	.shutकरोwn =	unix_shutकरोwn,
	.sendmsg =	unix_dgram_sendmsg,
	.recvmsg =	unix_dgram_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
	.set_peek_off =	unix_set_peek_off,
	.show_fdinfo =	unix_show_fdinfo,
पूर्ण;

अटल स्थिर काष्ठा proto_ops unix_seqpacket_ops = अणु
	.family =	PF_UNIX,
	.owner =	THIS_MODULE,
	.release =	unix_release,
	.bind =		unix_bind,
	.connect =	unix_stream_connect,
	.socketpair =	unix_socketpair,
	.accept =	unix_accept,
	.getname =	unix_getname,
	.poll =		unix_dgram_poll,
	.ioctl =	unix_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl =	unix_compat_ioctl,
#पूर्ण_अगर
	.listen =	unix_listen,
	.shutकरोwn =	unix_shutकरोwn,
	.sendmsg =	unix_seqpacket_sendmsg,
	.recvmsg =	unix_seqpacket_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
	.set_peek_off =	unix_set_peek_off,
	.show_fdinfo =	unix_show_fdinfo,
पूर्ण;

अटल काष्ठा proto unix_proto = अणु
	.name			= "UNIX",
	.owner			= THIS_MODULE,
	.obj_size		= माप(काष्ठा unix_sock),
पूर्ण;

अटल काष्ठा sock *unix_create1(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक kern)
अणु
	काष्ठा sock *sk = शून्य;
	काष्ठा unix_sock *u;

	atomic_दीर्घ_inc(&unix_nr_socks);
	अगर (atomic_दीर्घ_पढ़ो(&unix_nr_socks) > 2 * get_max_files())
		जाओ out;

	sk = sk_alloc(net, PF_UNIX, GFP_KERNEL, &unix_proto, kern);
	अगर (!sk)
		जाओ out;

	sock_init_data(sock, sk);

	sk->sk_allocation	= GFP_KERNEL_ACCOUNT;
	sk->sk_ग_लिखो_space	= unix_ग_लिखो_space;
	sk->sk_max_ack_backlog	= net->unx.sysctl_max_dgram_qlen;
	sk->sk_deकाष्ठा		= unix_sock_deकाष्ठाor;
	u	  = unix_sk(sk);
	u->path.dentry = शून्य;
	u->path.mnt = शून्य;
	spin_lock_init(&u->lock);
	atomic_दीर्घ_set(&u->inflight, 0);
	INIT_LIST_HEAD(&u->link);
	mutex_init(&u->iolock); /* single task पढ़ोing lock */
	mutex_init(&u->bindlock); /* single task binding lock */
	init_रुकोqueue_head(&u->peer_रुको);
	init_रुकोqueue_func_entry(&u->peer_wake, unix_dgram_peer_wake_relay);
	स_रखो(&u->scm_stat, 0, माप(काष्ठा scm_stat));
	unix_insert_socket(unix_sockets_unbound(sk), sk);
out:
	अगर (sk == शून्य)
		atomic_दीर्घ_dec(&unix_nr_socks);
	अन्यथा अणु
		local_bh_disable();
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
		local_bh_enable();
	पूर्ण
	वापस sk;
पूर्ण

अटल पूर्णांक unix_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		       पूर्णांक kern)
अणु
	अगर (protocol && protocol != PF_UNIX)
		वापस -EPROTONOSUPPORT;

	sock->state = SS_UNCONNECTED;

	चयन (sock->type) अणु
	हाल SOCK_STREAM:
		sock->ops = &unix_stream_ops;
		अवरोध;
		/*
		 *	Believe it or not BSD has AF_UNIX, SOCK_RAW though
		 *	nothing uses it.
		 */
	हाल SOCK_RAW:
		sock->type = SOCK_DGRAM;
		fallthrough;
	हाल SOCK_DGRAM:
		sock->ops = &unix_dgram_ops;
		अवरोध;
	हाल SOCK_SEQPACKET:
		sock->ops = &unix_seqpacket_ops;
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण

	वापस unix_create1(net, sock, kern) ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक unix_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (!sk)
		वापस 0;

	unix_release_sock(sk, 0);
	sock->sk = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक unix_स्वतःbind(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा unix_sock *u = unix_sk(sk);
	अटल u32 ordernum = 1;
	काष्ठा unix_address *addr;
	पूर्णांक err;
	अचिन्हित पूर्णांक retries = 0;

	err = mutex_lock_पूर्णांकerruptible(&u->bindlock);
	अगर (err)
		वापस err;

	अगर (u->addr)
		जाओ out;

	err = -ENOMEM;
	addr = kzalloc(माप(*addr) + माप(लघु) + 16, GFP_KERNEL);
	अगर (!addr)
		जाओ out;

	addr->name->sun_family = AF_UNIX;
	refcount_set(&addr->refcnt, 1);

retry:
	addr->len = प्र_लिखो(addr->name->sun_path+1, "%05x", ordernum) + 1 + माप(लघु);
	addr->hash = unix_hash_fold(csum_partial(addr->name, addr->len, 0));

	spin_lock(&unix_table_lock);
	ordernum = (ordernum+1)&0xFFFFF;

	अगर (__unix_find_socket_byname(net, addr->name, addr->len, sock->type,
				      addr->hash)) अणु
		spin_unlock(&unix_table_lock);
		/*
		 * __unix_find_socket_byname() may take दीर्घ समय अगर many names
		 * are alपढ़ोy in use.
		 */
		cond_resched();
		/* Give up अगर all names seems to be in use. */
		अगर (retries++ == 0xFFFFF) अणु
			err = -ENOSPC;
			kमुक्त(addr);
			जाओ out;
		पूर्ण
		जाओ retry;
	पूर्ण
	addr->hash ^= sk->sk_type;

	__unix_हटाओ_socket(sk);
	smp_store_release(&u->addr, addr);
	__unix_insert_socket(&unix_socket_table[addr->hash], sk);
	spin_unlock(&unix_table_lock);
	err = 0;

out:	mutex_unlock(&u->bindlock);
	वापस err;
पूर्ण

अटल काष्ठा sock *unix_find_other(काष्ठा net *net,
				    काष्ठा sockaddr_un *sunname, पूर्णांक len,
				    पूर्णांक type, अचिन्हित पूर्णांक hash, पूर्णांक *error)
अणु
	काष्ठा sock *u;
	काष्ठा path path;
	पूर्णांक err = 0;

	अगर (sunname->sun_path[0]) अणु
		काष्ठा inode *inode;
		err = kern_path(sunname->sun_path, LOOKUP_FOLLOW, &path);
		अगर (err)
			जाओ fail;
		inode = d_backing_inode(path.dentry);
		err = path_permission(&path, MAY_WRITE);
		अगर (err)
			जाओ put_fail;

		err = -ECONNREFUSED;
		अगर (!S_ISSOCK(inode->i_mode))
			जाओ put_fail;
		u = unix_find_socket_byinode(inode);
		अगर (!u)
			जाओ put_fail;

		अगर (u->sk_type == type)
			touch_aसमय(&path);

		path_put(&path);

		err = -EPROTOTYPE;
		अगर (u->sk_type != type) अणु
			sock_put(u);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -ECONNREFUSED;
		u = unix_find_socket_byname(net, sunname, len, type, hash);
		अगर (u) अणु
			काष्ठा dentry *dentry;
			dentry = unix_sk(u)->path.dentry;
			अगर (dentry)
				touch_aसमय(&unix_sk(u)->path);
		पूर्ण अन्यथा
			जाओ fail;
	पूर्ण
	वापस u;

put_fail:
	path_put(&path);
fail:
	*error = err;
	वापस शून्य;
पूर्ण

अटल पूर्णांक unix_mknod(स्थिर अक्षर *sun_path, umode_t mode, काष्ठा path *res)
अणु
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक err = 0;
	/*
	 * Get the parent directory, calculate the hash क्रम last
	 * component.
	 */
	dentry = kern_path_create(AT_FDCWD, sun_path, &path, 0);
	err = PTR_ERR(dentry);
	अगर (IS_ERR(dentry))
		वापस err;

	/*
	 * All right, let's create it.
	 */
	err = security_path_mknod(&path, dentry, mode, 0);
	अगर (!err) अणु
		err = vfs_mknod(mnt_user_ns(path.mnt), d_inode(path.dentry),
				dentry, mode, 0);
		अगर (!err) अणु
			res->mnt = mntget(path.mnt);
			res->dentry = dget(dentry);
		पूर्ण
	पूर्ण
	करोne_path_create(&path, dentry);
	वापस err;
पूर्ण

अटल पूर्णांक unix_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा unix_sock *u = unix_sk(sk);
	काष्ठा sockaddr_un *sunaddr = (काष्ठा sockaddr_un *)uaddr;
	अक्षर *sun_path = sunaddr->sun_path;
	पूर्णांक err;
	अचिन्हित पूर्णांक hash;
	काष्ठा unix_address *addr;
	काष्ठा hlist_head *list;
	काष्ठा path path = अणु पूर्ण;

	err = -EINVAL;
	अगर (addr_len < दुरत्वend(काष्ठा sockaddr_un, sun_family) ||
	    sunaddr->sun_family != AF_UNIX)
		जाओ out;

	अगर (addr_len == माप(लघु)) अणु
		err = unix_स्वतःbind(sock);
		जाओ out;
	पूर्ण

	err = unix_mkname(sunaddr, addr_len, &hash);
	अगर (err < 0)
		जाओ out;
	addr_len = err;

	अगर (sun_path[0]) अणु
		umode_t mode = S_IFSOCK |
		       (SOCK_INODE(sock)->i_mode & ~current_umask());
		err = unix_mknod(sun_path, mode, &path);
		अगर (err) अणु
			अगर (err == -EEXIST)
				err = -EADDRINUSE;
			जाओ out;
		पूर्ण
	पूर्ण

	err = mutex_lock_पूर्णांकerruptible(&u->bindlock);
	अगर (err)
		जाओ out_put;

	err = -EINVAL;
	अगर (u->addr)
		जाओ out_up;

	err = -ENOMEM;
	addr = kदो_स्मृति(माप(*addr)+addr_len, GFP_KERNEL);
	अगर (!addr)
		जाओ out_up;

	स_नकल(addr->name, sunaddr, addr_len);
	addr->len = addr_len;
	addr->hash = hash ^ sk->sk_type;
	refcount_set(&addr->refcnt, 1);

	अगर (sun_path[0]) अणु
		addr->hash = UNIX_HASH_SIZE;
		hash = d_backing_inode(path.dentry)->i_ino & (UNIX_HASH_SIZE - 1);
		spin_lock(&unix_table_lock);
		u->path = path;
		list = &unix_socket_table[hash];
	पूर्ण अन्यथा अणु
		spin_lock(&unix_table_lock);
		err = -EADDRINUSE;
		अगर (__unix_find_socket_byname(net, sunaddr, addr_len,
					      sk->sk_type, hash)) अणु
			unix_release_addr(addr);
			जाओ out_unlock;
		पूर्ण

		list = &unix_socket_table[addr->hash];
	पूर्ण

	err = 0;
	__unix_हटाओ_socket(sk);
	smp_store_release(&u->addr, addr);
	__unix_insert_socket(list, sk);

out_unlock:
	spin_unlock(&unix_table_lock);
out_up:
	mutex_unlock(&u->bindlock);
out_put:
	अगर (err)
		path_put(&path);
out:
	वापस err;
पूर्ण

अटल व्योम unix_state_द्विगुन_lock(काष्ठा sock *sk1, काष्ठा sock *sk2)
अणु
	अगर (unlikely(sk1 == sk2) || !sk2) अणु
		unix_state_lock(sk1);
		वापस;
	पूर्ण
	अगर (sk1 < sk2) अणु
		unix_state_lock(sk1);
		unix_state_lock_nested(sk2);
	पूर्ण अन्यथा अणु
		unix_state_lock(sk2);
		unix_state_lock_nested(sk1);
	पूर्ण
पूर्ण

अटल व्योम unix_state_द्विगुन_unlock(काष्ठा sock *sk1, काष्ठा sock *sk2)
अणु
	अगर (unlikely(sk1 == sk2) || !sk2) अणु
		unix_state_unlock(sk1);
		वापस;
	पूर्ण
	unix_state_unlock(sk1);
	unix_state_unlock(sk2);
पूर्ण

अटल पूर्णांक unix_dgram_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			      पूर्णांक alen, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा sockaddr_un *sunaddr = (काष्ठा sockaddr_un *)addr;
	काष्ठा sock *other;
	अचिन्हित पूर्णांक hash;
	पूर्णांक err;

	err = -EINVAL;
	अगर (alen < दुरत्वend(काष्ठा sockaddr, sa_family))
		जाओ out;

	अगर (addr->sa_family != AF_UNSPEC) अणु
		err = unix_mkname(sunaddr, alen, &hash);
		अगर (err < 0)
			जाओ out;
		alen = err;

		अगर (test_bit(SOCK_PASSCRED, &sock->flags) &&
		    !unix_sk(sk)->addr && (err = unix_स्वतःbind(sock)) != 0)
			जाओ out;

restart:
		other = unix_find_other(net, sunaddr, alen, sock->type, hash, &err);
		अगर (!other)
			जाओ out;

		unix_state_द्विगुन_lock(sk, other);

		/* Apparently VFS overslept socket death. Retry. */
		अगर (sock_flag(other, SOCK_DEAD)) अणु
			unix_state_द्विगुन_unlock(sk, other);
			sock_put(other);
			जाओ restart;
		पूर्ण

		err = -EPERM;
		अगर (!unix_may_send(sk, other))
			जाओ out_unlock;

		err = security_unix_may_send(sk->sk_socket, other->sk_socket);
		अगर (err)
			जाओ out_unlock;

	पूर्ण अन्यथा अणु
		/*
		 *	1003.1g अवरोधing connected state with AF_UNSPEC
		 */
		other = शून्य;
		unix_state_द्विगुन_lock(sk, other);
	पूर्ण

	/*
	 * If it was connected, reconnect.
	 */
	अगर (unix_peer(sk)) अणु
		काष्ठा sock *old_peer = unix_peer(sk);
		unix_peer(sk) = other;
		unix_dgram_peer_wake_disconnect_wakeup(sk, old_peer);

		unix_state_द्विगुन_unlock(sk, other);

		अगर (other != old_peer)
			unix_dgram_disconnected(sk, old_peer);
		sock_put(old_peer);
	पूर्ण अन्यथा अणु
		unix_peer(sk) = other;
		unix_state_द्विगुन_unlock(sk, other);
	पूर्ण
	वापस 0;

out_unlock:
	unix_state_द्विगुन_unlock(sk, other);
	sock_put(other);
out:
	वापस err;
पूर्ण

अटल दीर्घ unix_रुको_क्रम_peer(काष्ठा sock *other, दीर्घ समयo)
	__releases(&unix_sk(other)->lock)
अणु
	काष्ठा unix_sock *u = unix_sk(other);
	पूर्णांक sched;
	DEFINE_WAIT(रुको);

	prepare_to_रुको_exclusive(&u->peer_रुको, &रुको, TASK_INTERRUPTIBLE);

	sched = !sock_flag(other, SOCK_DEAD) &&
		!(other->sk_shutकरोwn & RCV_SHUTDOWN) &&
		unix_recvq_full(other);

	unix_state_unlock(other);

	अगर (sched)
		समयo = schedule_समयout(समयo);

	finish_रुको(&u->peer_रुको, &रुको);
	वापस समयo;
पूर्ण

अटल पूर्णांक unix_stream_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			       पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sockaddr_un *sunaddr = (काष्ठा sockaddr_un *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा unix_sock *u = unix_sk(sk), *newu, *otheru;
	काष्ठा sock *newsk = शून्य;
	काष्ठा sock *other = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	अचिन्हित पूर्णांक hash;
	पूर्णांक st;
	पूर्णांक err;
	दीर्घ समयo;

	err = unix_mkname(sunaddr, addr_len, &hash);
	अगर (err < 0)
		जाओ out;
	addr_len = err;

	अगर (test_bit(SOCK_PASSCRED, &sock->flags) && !u->addr &&
	    (err = unix_स्वतःbind(sock)) != 0)
		जाओ out;

	समयo = sock_sndसमयo(sk, flags & O_NONBLOCK);

	/* First of all allocate resources.
	   If we will make it after state is locked,
	   we will have to recheck all again in any हाल.
	 */

	err = -ENOMEM;

	/* create new sock क्रम complete connection */
	newsk = unix_create1(sock_net(sk), शून्य, 0);
	अगर (newsk == शून्य)
		जाओ out;

	/* Allocate skb क्रम sending to listening sock */
	skb = sock_wदो_स्मृति(newsk, 1, 0, GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ out;

restart:
	/*  Find listening sock. */
	other = unix_find_other(net, sunaddr, addr_len, sk->sk_type, hash, &err);
	अगर (!other)
		जाओ out;

	/* Latch state of peer */
	unix_state_lock(other);

	/* Apparently VFS overslept socket death. Retry. */
	अगर (sock_flag(other, SOCK_DEAD)) अणु
		unix_state_unlock(other);
		sock_put(other);
		जाओ restart;
	पूर्ण

	err = -ECONNREFUSED;
	अगर (other->sk_state != TCP_LISTEN)
		जाओ out_unlock;
	अगर (other->sk_shutकरोwn & RCV_SHUTDOWN)
		जाओ out_unlock;

	अगर (unix_recvq_full(other)) अणु
		err = -EAGAIN;
		अगर (!समयo)
			जाओ out_unlock;

		समयo = unix_रुको_क्रम_peer(other, समयo);

		err = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			जाओ out;
		sock_put(other);
		जाओ restart;
	पूर्ण

	/* Latch our state.

	   It is tricky place. We need to grab our state lock and cannot
	   drop lock on peer. It is dangerous because deadlock is
	   possible. Connect to self हाल and simultaneous
	   attempt to connect are eliminated by checking socket
	   state. other is TCP_LISTEN, अगर sk is TCP_LISTEN we
	   check this beक्रमe attempt to grab lock.

	   Well, and we have to recheck the state after socket locked.
	 */
	st = sk->sk_state;

	चयन (st) अणु
	हाल TCP_CLOSE:
		/* This is ok... जारी with connect */
		अवरोध;
	हाल TCP_ESTABLISHED:
		/* Socket is alपढ़ोy connected */
		err = -EISCONN;
		जाओ out_unlock;
	शेष:
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	unix_state_lock_nested(sk);

	अगर (sk->sk_state != st) अणु
		unix_state_unlock(sk);
		unix_state_unlock(other);
		sock_put(other);
		जाओ restart;
	पूर्ण

	err = security_unix_stream_connect(sk, other, newsk);
	अगर (err) अणु
		unix_state_unlock(sk);
		जाओ out_unlock;
	पूर्ण

	/* The way is खोलो! Fastly set all the necessary fields... */

	sock_hold(sk);
	unix_peer(newsk)	= sk;
	newsk->sk_state		= TCP_ESTABLISHED;
	newsk->sk_type		= sk->sk_type;
	init_peercred(newsk);
	newu = unix_sk(newsk);
	RCU_INIT_POINTER(newsk->sk_wq, &newu->peer_wq);
	otheru = unix_sk(other);

	/* copy address inक्रमmation from listening to new sock
	 *
	 * The contents of *(otheru->addr) and otheru->path
	 * are seen fully set up here, since we have found
	 * otheru in hash under unix_table_lock.  Insertion
	 * पूर्णांकo the hash chain we'd found it in had been करोne
	 * in an earlier critical area रक्षित by unix_table_lock,
	 * the same one where we'd set *(otheru->addr) contents,
	 * as well as otheru->path and otheru->addr itself.
	 *
	 * Using smp_store_release() here to set newu->addr
	 * is enough to make those stores, as well as stores
	 * to newu->path visible to anyone who माला_लो newu->addr
	 * by smp_load_acquire().  IOW, the same warranties
	 * as क्रम unix_sock instances bound in unix_bind() or
	 * in unix_स्वतःbind().
	 */
	अगर (otheru->path.dentry) अणु
		path_get(&otheru->path);
		newu->path = otheru->path;
	पूर्ण
	refcount_inc(&otheru->addr->refcnt);
	smp_store_release(&newu->addr, otheru->addr);

	/* Set credentials */
	copy_peercred(sk, other);

	sock->state	= SS_CONNECTED;
	sk->sk_state	= TCP_ESTABLISHED;
	sock_hold(newsk);

	smp_mb__after_atomic();	/* sock_hold() करोes an atomic_inc() */
	unix_peer(sk)	= newsk;

	unix_state_unlock(sk);

	/* take ten and and send info to listening sock */
	spin_lock(&other->sk_receive_queue.lock);
	__skb_queue_tail(&other->sk_receive_queue, skb);
	spin_unlock(&other->sk_receive_queue.lock);
	unix_state_unlock(other);
	other->sk_data_पढ़ोy(other);
	sock_put(other);
	वापस 0;

out_unlock:
	अगर (other)
		unix_state_unlock(other);

out:
	kमुक्त_skb(skb);
	अगर (newsk)
		unix_release_sock(newsk, 0);
	अगर (other)
		sock_put(other);
	वापस err;
पूर्ण

अटल पूर्णांक unix_socketpair(काष्ठा socket *socka, काष्ठा socket *sockb)
अणु
	काष्ठा sock *ska = socka->sk, *skb = sockb->sk;

	/* Join our sockets back to back */
	sock_hold(ska);
	sock_hold(skb);
	unix_peer(ska) = skb;
	unix_peer(skb) = ska;
	init_peercred(ska);
	init_peercred(skb);

	अगर (ska->sk_type != SOCK_DGRAM) अणु
		ska->sk_state = TCP_ESTABLISHED;
		skb->sk_state = TCP_ESTABLISHED;
		socka->state  = SS_CONNECTED;
		sockb->state  = SS_CONNECTED;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम unix_sock_inherit_flags(स्थिर काष्ठा socket *old,
				    काष्ठा socket *new)
अणु
	अगर (test_bit(SOCK_PASSCRED, &old->flags))
		set_bit(SOCK_PASSCRED, &new->flags);
	अगर (test_bit(SOCK_PASSSEC, &old->flags))
		set_bit(SOCK_PASSSEC, &new->flags);
पूर्ण

अटल पूर्णांक unix_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		       bool kern)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sock *tsk;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	err = -EOPNOTSUPP;
	अगर (sock->type != SOCK_STREAM && sock->type != SOCK_SEQPACKET)
		जाओ out;

	err = -EINVAL;
	अगर (sk->sk_state != TCP_LISTEN)
		जाओ out;

	/* If socket state is TCP_LISTEN it cannot change (क्रम now...),
	 * so that no locks are necessary.
	 */

	skb = skb_recv_datagram(sk, 0, flags&O_NONBLOCK, &err);
	अगर (!skb) अणु
		/* This means receive shutकरोwn. */
		अगर (err == 0)
			err = -EINVAL;
		जाओ out;
	पूर्ण

	tsk = skb->sk;
	skb_मुक्त_datagram(sk, skb);
	wake_up_पूर्णांकerruptible(&unix_sk(sk)->peer_रुको);

	/* attach accepted sock to socket */
	unix_state_lock(tsk);
	newsock->state = SS_CONNECTED;
	unix_sock_inherit_flags(sock, newsock);
	sock_graft(tsk, newsock);
	unix_state_unlock(tsk);
	वापस 0;

out:
	वापस err;
पूर्ण


अटल पूर्णांक unix_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक peer)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा unix_address *addr;
	DECLARE_SOCKADDR(काष्ठा sockaddr_un *, sunaddr, uaddr);
	पूर्णांक err = 0;

	अगर (peer) अणु
		sk = unix_peer_get(sk);

		err = -ENOTCONN;
		अगर (!sk)
			जाओ out;
		err = 0;
	पूर्ण अन्यथा अणु
		sock_hold(sk);
	पूर्ण

	addr = smp_load_acquire(&unix_sk(sk)->addr);
	अगर (!addr) अणु
		sunaddr->sun_family = AF_UNIX;
		sunaddr->sun_path[0] = 0;
		err = माप(लघु);
	पूर्ण अन्यथा अणु
		err = addr->len;
		स_नकल(sunaddr, addr->name, addr->len);
	पूर्ण
	sock_put(sk);
out:
	वापस err;
पूर्ण

अटल पूर्णांक unix_scm_to_skb(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb, bool send_fds)
अणु
	पूर्णांक err = 0;

	UNIXCB(skb).pid  = get_pid(scm->pid);
	UNIXCB(skb).uid = scm->creds.uid;
	UNIXCB(skb).gid = scm->creds.gid;
	UNIXCB(skb).fp = शून्य;
	unix_get_secdata(scm, skb);
	अगर (scm->fp && send_fds)
		err = unix_attach_fds(scm, skb);

	skb->deकाष्ठाor = unix_deकाष्ठा_scm;
	वापस err;
पूर्ण

अटल bool unix_passcred_enabled(स्थिर काष्ठा socket *sock,
				  स्थिर काष्ठा sock *other)
अणु
	वापस test_bit(SOCK_PASSCRED, &sock->flags) ||
	       !other->sk_socket ||
	       test_bit(SOCK_PASSCRED, &other->sk_socket->flags);
पूर्ण

/*
 * Some apps rely on ग_लिखो() giving SCM_CREDENTIALS
 * We include credentials अगर source or destination socket
 * निश्चितed SOCK_PASSCRED.
 */
अटल व्योम maybe_add_creds(काष्ठा sk_buff *skb, स्थिर काष्ठा socket *sock,
			    स्थिर काष्ठा sock *other)
अणु
	अगर (UNIXCB(skb).pid)
		वापस;
	अगर (unix_passcred_enabled(sock, other)) अणु
		UNIXCB(skb).pid  = get_pid(task_tgid(current));
		current_uid_gid(&UNIXCB(skb).uid, &UNIXCB(skb).gid);
	पूर्ण
पूर्ण

अटल पूर्णांक maybe_init_creds(काष्ठा scm_cookie *scm,
			    काष्ठा socket *socket,
			    स्थिर काष्ठा sock *other)
अणु
	पूर्णांक err;
	काष्ठा msghdr msg = अणु .msg_controllen = 0 पूर्ण;

	err = scm_send(socket, &msg, scm, false);
	अगर (err)
		वापस err;

	अगर (unix_passcred_enabled(socket, other)) अणु
		scm->pid = get_pid(task_tgid(current));
		current_uid_gid(&scm->creds.uid, &scm->creds.gid);
	पूर्ण
	वापस err;
पूर्ण

अटल bool unix_skb_scm_eq(काष्ठा sk_buff *skb,
			    काष्ठा scm_cookie *scm)
अणु
	स्थिर काष्ठा unix_skb_parms *u = &UNIXCB(skb);

	वापस u->pid == scm->pid &&
	       uid_eq(u->uid, scm->creds.uid) &&
	       gid_eq(u->gid, scm->creds.gid) &&
	       unix_secdata_eq(scm, skb);
पूर्ण

अटल व्योम scm_stat_add(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा scm_fp_list *fp = UNIXCB(skb).fp;
	काष्ठा unix_sock *u = unix_sk(sk);

	अगर (unlikely(fp && fp->count))
		atomic_add(fp->count, &u->scm_stat.nr_fds);
पूर्ण

अटल व्योम scm_stat_del(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा scm_fp_list *fp = UNIXCB(skb).fp;
	काष्ठा unix_sock *u = unix_sk(sk);

	अगर (unlikely(fp && fp->count))
		atomic_sub(fp->count, &u->scm_stat.nr_fds);
पूर्ण

/*
 *	Send AF_UNIX data.
 */

अटल पूर्णांक unix_dgram_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			      माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा unix_sock *u = unix_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_un *, sunaddr, msg->msg_name);
	काष्ठा sock *other = शून्य;
	पूर्णांक namelen = 0; /* fake GCC */
	पूर्णांक err;
	अचिन्हित पूर्णांक hash;
	काष्ठा sk_buff *skb;
	दीर्घ समयo;
	काष्ठा scm_cookie scm;
	पूर्णांक data_len = 0;
	पूर्णांक sk_locked;

	रुको_क्रम_unix_gc();
	err = scm_send(sock, msg, &scm, false);
	अगर (err < 0)
		वापस err;

	err = -EOPNOTSUPP;
	अगर (msg->msg_flags&MSG_OOB)
		जाओ out;

	अगर (msg->msg_namelen) अणु
		err = unix_mkname(sunaddr, msg->msg_namelen, &hash);
		अगर (err < 0)
			जाओ out;
		namelen = err;
	पूर्ण अन्यथा अणु
		sunaddr = शून्य;
		err = -ENOTCONN;
		other = unix_peer_get(sk);
		अगर (!other)
			जाओ out;
	पूर्ण

	अगर (test_bit(SOCK_PASSCRED, &sock->flags) && !u->addr
	    && (err = unix_स्वतःbind(sock)) != 0)
		जाओ out;

	err = -EMSGSIZE;
	अगर (len > sk->sk_sndbuf - 32)
		जाओ out;

	अगर (len > SKB_MAX_ALLOC) अणु
		data_len = min_t(माप_प्रकार,
				 len - SKB_MAX_ALLOC,
				 MAX_SKB_FRAGS * PAGE_SIZE);
		data_len = PAGE_ALIGN(data_len);

		BUILD_BUG_ON(SKB_MAX_ALLOC < PAGE_SIZE);
	पूर्ण

	skb = sock_alloc_send_pskb(sk, len - data_len, data_len,
				   msg->msg_flags & MSG_DONTWAIT, &err,
				   PAGE_ALLOC_COSTLY_ORDER);
	अगर (skb == शून्य)
		जाओ out;

	err = unix_scm_to_skb(&scm, skb, true);
	अगर (err < 0)
		जाओ out_मुक्त;

	skb_put(skb, len - data_len);
	skb->data_len = data_len;
	skb->len = len;
	err = skb_copy_datagram_from_iter(skb, 0, &msg->msg_iter, len);
	अगर (err)
		जाओ out_मुक्त;

	समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);

restart:
	अगर (!other) अणु
		err = -ECONNRESET;
		अगर (sunaddr == शून्य)
			जाओ out_मुक्त;

		other = unix_find_other(net, sunaddr, namelen, sk->sk_type,
					hash, &err);
		अगर (other == शून्य)
			जाओ out_मुक्त;
	पूर्ण

	अगर (sk_filter(other, skb) < 0) अणु
		/* Toss the packet but करो not वापस any error to the sender */
		err = len;
		जाओ out_मुक्त;
	पूर्ण

	sk_locked = 0;
	unix_state_lock(other);
restart_locked:
	err = -EPERM;
	अगर (!unix_may_send(sk, other))
		जाओ out_unlock;

	अगर (unlikely(sock_flag(other, SOCK_DEAD))) अणु
		/*
		 *	Check with 1003.1g - what should
		 *	datagram error
		 */
		unix_state_unlock(other);
		sock_put(other);

		अगर (!sk_locked)
			unix_state_lock(sk);

		err = 0;
		अगर (unix_peer(sk) == other) अणु
			unix_peer(sk) = शून्य;
			unix_dgram_peer_wake_disconnect_wakeup(sk, other);

			unix_state_unlock(sk);

			unix_dgram_disconnected(sk, other);
			sock_put(other);
			err = -ECONNREFUSED;
		पूर्ण अन्यथा अणु
			unix_state_unlock(sk);
		पूर्ण

		other = शून्य;
		अगर (err)
			जाओ out_मुक्त;
		जाओ restart;
	पूर्ण

	err = -EPIPE;
	अगर (other->sk_shutकरोwn & RCV_SHUTDOWN)
		जाओ out_unlock;

	अगर (sk->sk_type != SOCK_SEQPACKET) अणु
		err = security_unix_may_send(sk->sk_socket, other->sk_socket);
		अगर (err)
			जाओ out_unlock;
	पूर्ण

	/* other == sk && unix_peer(other) != sk अगर
	 * - unix_peer(sk) == शून्य, destination address bound to sk
	 * - unix_peer(sk) == sk by समय of get but disconnected beक्रमe lock
	 */
	अगर (other != sk &&
	    unlikely(unix_peer(other) != sk &&
	    unix_recvq_full_lockless(other))) अणु
		अगर (समयo) अणु
			समयo = unix_रुको_क्रम_peer(other, समयo);

			err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अगर (संकेत_pending(current))
				जाओ out_मुक्त;

			जाओ restart;
		पूर्ण

		अगर (!sk_locked) अणु
			unix_state_unlock(other);
			unix_state_द्विगुन_lock(sk, other);
		पूर्ण

		अगर (unix_peer(sk) != other ||
		    unix_dgram_peer_wake_me(sk, other)) अणु
			err = -EAGAIN;
			sk_locked = 1;
			जाओ out_unlock;
		पूर्ण

		अगर (!sk_locked) अणु
			sk_locked = 1;
			जाओ restart_locked;
		पूर्ण
	पूर्ण

	अगर (unlikely(sk_locked))
		unix_state_unlock(sk);

	अगर (sock_flag(other, SOCK_RCVTSTAMP))
		__net_बारtamp(skb);
	maybe_add_creds(skb, sock, other);
	scm_stat_add(other, skb);
	skb_queue_tail(&other->sk_receive_queue, skb);
	unix_state_unlock(other);
	other->sk_data_पढ़ोy(other);
	sock_put(other);
	scm_destroy(&scm);
	वापस len;

out_unlock:
	अगर (sk_locked)
		unix_state_unlock(sk);
	unix_state_unlock(other);
out_मुक्त:
	kमुक्त_skb(skb);
out:
	अगर (other)
		sock_put(other);
	scm_destroy(&scm);
	वापस err;
पूर्ण

/* We use paged skbs क्रम stream sockets, and limit occupancy to 32768
 * bytes, and a minimum of a full page.
 */
#घोषणा UNIX_SKB_FRAGS_SZ (PAGE_SIZE << get_order(32768))

अटल पूर्णांक unix_stream_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sock *other = शून्य;
	पूर्णांक err, size;
	काष्ठा sk_buff *skb;
	पूर्णांक sent = 0;
	काष्ठा scm_cookie scm;
	bool fds_sent = false;
	पूर्णांक data_len;

	रुको_क्रम_unix_gc();
	err = scm_send(sock, msg, &scm, false);
	अगर (err < 0)
		वापस err;

	err = -EOPNOTSUPP;
	अगर (msg->msg_flags&MSG_OOB)
		जाओ out_err;

	अगर (msg->msg_namelen) अणु
		err = sk->sk_state == TCP_ESTABLISHED ? -EISCONN : -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण अन्यथा अणु
		err = -ENOTCONN;
		other = unix_peer(sk);
		अगर (!other)
			जाओ out_err;
	पूर्ण

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN)
		जाओ pipe_err;

	जबतक (sent < len) अणु
		size = len - sent;

		/* Keep two messages in the pipe so it schedules better */
		size = min_t(पूर्णांक, size, (sk->sk_sndbuf >> 1) - 64);

		/* allow fallback to order-0 allocations */
		size = min_t(पूर्णांक, size, SKB_MAX_HEAD(0) + UNIX_SKB_FRAGS_SZ);

		data_len = max_t(पूर्णांक, 0, size - SKB_MAX_HEAD(0));

		data_len = min_t(माप_प्रकार, size, PAGE_ALIGN(data_len));

		skb = sock_alloc_send_pskb(sk, size - data_len, data_len,
					   msg->msg_flags & MSG_DONTWAIT, &err,
					   get_order(UNIX_SKB_FRAGS_SZ));
		अगर (!skb)
			जाओ out_err;

		/* Only send the fds in the first buffer */
		err = unix_scm_to_skb(&scm, skb, !fds_sent);
		अगर (err < 0) अणु
			kमुक्त_skb(skb);
			जाओ out_err;
		पूर्ण
		fds_sent = true;

		skb_put(skb, size - data_len);
		skb->data_len = data_len;
		skb->len = size;
		err = skb_copy_datagram_from_iter(skb, 0, &msg->msg_iter, size);
		अगर (err) अणु
			kमुक्त_skb(skb);
			जाओ out_err;
		पूर्ण

		unix_state_lock(other);

		अगर (sock_flag(other, SOCK_DEAD) ||
		    (other->sk_shutकरोwn & RCV_SHUTDOWN))
			जाओ pipe_err_मुक्त;

		maybe_add_creds(skb, sock, other);
		scm_stat_add(other, skb);
		skb_queue_tail(&other->sk_receive_queue, skb);
		unix_state_unlock(other);
		other->sk_data_पढ़ोy(other);
		sent += size;
	पूर्ण

	scm_destroy(&scm);

	वापस sent;

pipe_err_मुक्त:
	unix_state_unlock(other);
	kमुक्त_skb(skb);
pipe_err:
	अगर (sent == 0 && !(msg->msg_flags&MSG_NOSIGNAL))
		send_sig(SIGPIPE, current, 0);
	err = -EPIPE;
out_err:
	scm_destroy(&scm);
	वापस sent ? : err;
पूर्ण

अटल sमाप_प्रकार unix_stream_sendpage(काष्ठा socket *socket, काष्ठा page *page,
				    पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक err;
	bool send_sigpipe = false;
	bool init_scm = true;
	काष्ठा scm_cookie scm;
	काष्ठा sock *other, *sk = socket->sk;
	काष्ठा sk_buff *skb, *newskb = शून्य, *tail = शून्य;

	अगर (flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	other = unix_peer(sk);
	अगर (!other || sk->sk_state != TCP_ESTABLISHED)
		वापस -ENOTCONN;

	अगर (false) अणु
alloc_skb:
		unix_state_unlock(other);
		mutex_unlock(&unix_sk(other)->iolock);
		newskb = sock_alloc_send_pskb(sk, 0, 0, flags & MSG_DONTWAIT,
					      &err, 0);
		अगर (!newskb)
			जाओ err;
	पूर्ण

	/* we must acquire iolock as we modअगरy alपढ़ोy present
	 * skbs in the sk_receive_queue and mess with skb->len
	 */
	err = mutex_lock_पूर्णांकerruptible(&unix_sk(other)->iolock);
	अगर (err) अणु
		err = flags & MSG_DONTWAIT ? -EAGAIN : -ERESTARTSYS;
		जाओ err;
	पूर्ण

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		err = -EPIPE;
		send_sigpipe = true;
		जाओ err_unlock;
	पूर्ण

	unix_state_lock(other);

	अगर (sock_flag(other, SOCK_DEAD) ||
	    other->sk_shutकरोwn & RCV_SHUTDOWN) अणु
		err = -EPIPE;
		send_sigpipe = true;
		जाओ err_state_unlock;
	पूर्ण

	अगर (init_scm) अणु
		err = maybe_init_creds(&scm, socket, other);
		अगर (err)
			जाओ err_state_unlock;
		init_scm = false;
	पूर्ण

	skb = skb_peek_tail(&other->sk_receive_queue);
	अगर (tail && tail == skb) अणु
		skb = newskb;
	पूर्ण अन्यथा अगर (!skb || !unix_skb_scm_eq(skb, &scm)) अणु
		अगर (newskb) अणु
			skb = newskb;
		पूर्ण अन्यथा अणु
			tail = skb;
			जाओ alloc_skb;
		पूर्ण
	पूर्ण अन्यथा अगर (newskb) अणु
		/* this is fast path, we करोn't necessarily need to
		 * call to kमुक्त_skb even though with newskb == शून्य
		 * this - करोes no harm
		 */
		consume_skb(newskb);
		newskb = शून्य;
	पूर्ण

	अगर (skb_append_pagefrags(skb, page, offset, size)) अणु
		tail = skb;
		जाओ alloc_skb;
	पूर्ण

	skb->len += size;
	skb->data_len += size;
	skb->truesize += size;
	refcount_add(size, &sk->sk_wmem_alloc);

	अगर (newskb) अणु
		err = unix_scm_to_skb(&scm, skb, false);
		अगर (err)
			जाओ err_state_unlock;
		spin_lock(&other->sk_receive_queue.lock);
		__skb_queue_tail(&other->sk_receive_queue, newskb);
		spin_unlock(&other->sk_receive_queue.lock);
	पूर्ण

	unix_state_unlock(other);
	mutex_unlock(&unix_sk(other)->iolock);

	other->sk_data_पढ़ोy(other);
	scm_destroy(&scm);
	वापस size;

err_state_unlock:
	unix_state_unlock(other);
err_unlock:
	mutex_unlock(&unix_sk(other)->iolock);
err:
	kमुक्त_skb(newskb);
	अगर (send_sigpipe && !(flags & MSG_NOSIGNAL))
		send_sig(SIGPIPE, current, 0);
	अगर (!init_scm)
		scm_destroy(&scm);
	वापस err;
पूर्ण

अटल पूर्णांक unix_seqpacket_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  माप_प्रकार len)
अणु
	पूर्णांक err;
	काष्ठा sock *sk = sock->sk;

	err = sock_error(sk);
	अगर (err)
		वापस err;

	अगर (sk->sk_state != TCP_ESTABLISHED)
		वापस -ENOTCONN;

	अगर (msg->msg_namelen)
		msg->msg_namelen = 0;

	वापस unix_dgram_sendmsg(sock, msg, len);
पूर्ण

अटल पूर्णांक unix_seqpacket_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk->sk_state != TCP_ESTABLISHED)
		वापस -ENOTCONN;

	वापस unix_dgram_recvmsg(sock, msg, size, flags);
पूर्ण

अटल व्योम unix_copy_addr(काष्ठा msghdr *msg, काष्ठा sock *sk)
अणु
	काष्ठा unix_address *addr = smp_load_acquire(&unix_sk(sk)->addr);

	अगर (addr) अणु
		msg->msg_namelen = addr->len;
		स_नकल(msg->msg_name, addr->name, addr->len);
	पूर्ण
पूर्ण

अटल पूर्णांक unix_dgram_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			      माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा scm_cookie scm;
	काष्ठा sock *sk = sock->sk;
	काष्ठा unix_sock *u = unix_sk(sk);
	काष्ठा sk_buff *skb, *last;
	दीर्घ समयo;
	पूर्णांक skip;
	पूर्णांक err;

	err = -EOPNOTSUPP;
	अगर (flags&MSG_OOB)
		जाओ out;

	समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	करो अणु
		mutex_lock(&u->iolock);

		skip = sk_peek_offset(sk, flags);
		skb = __skb_try_recv_datagram(sk, &sk->sk_receive_queue, flags,
					      &skip, &err, &last);
		अगर (skb) अणु
			अगर (!(flags & MSG_PEEK))
				scm_stat_del(sk, skb);
			अवरोध;
		पूर्ण

		mutex_unlock(&u->iolock);

		अगर (err != -EAGAIN)
			अवरोध;
	पूर्ण जबतक (समयo &&
		 !__skb_रुको_क्रम_more_packets(sk, &sk->sk_receive_queue,
					      &err, &समयo, last));

	अगर (!skb) अणु /* implies iolock unlocked */
		unix_state_lock(sk);
		/* Signal खातापूर्ण on disconnected non-blocking SEQPACKET socket. */
		अगर (sk->sk_type == SOCK_SEQPACKET && err == -EAGAIN &&
		    (sk->sk_shutकरोwn & RCV_SHUTDOWN))
			err = 0;
		unix_state_unlock(sk);
		जाओ out;
	पूर्ण

	अगर (wq_has_sleeper(&u->peer_रुको))
		wake_up_पूर्णांकerruptible_sync_poll(&u->peer_रुको,
						EPOLLOUT | EPOLLWRNORM |
						EPOLLWRBAND);

	अगर (msg->msg_name)
		unix_copy_addr(msg, skb->sk);

	अगर (size > skb->len - skip)
		size = skb->len - skip;
	अन्यथा अगर (size < skb->len - skip)
		msg->msg_flags |= MSG_TRUNC;

	err = skb_copy_datagram_msg(skb, skip, msg, size);
	अगर (err)
		जाओ out_मुक्त;

	अगर (sock_flag(sk, SOCK_RCVTSTAMP))
		__sock_recv_बारtamp(msg, sk, skb);

	स_रखो(&scm, 0, माप(scm));

	scm_set_cred(&scm, UNIXCB(skb).pid, UNIXCB(skb).uid, UNIXCB(skb).gid);
	unix_set_secdata(&scm, skb);

	अगर (!(flags & MSG_PEEK)) अणु
		अगर (UNIXCB(skb).fp)
			unix_detach_fds(&scm, skb);

		sk_peek_offset_bwd(sk, skb->len);
	पूर्ण अन्यथा अणु
		/* It is questionable: on PEEK we could:
		   - करो not वापस fds - good, but too simple 8)
		   - वापस fds, and करो not वापस them on पढ़ो (old strategy,
		     apparently wrong)
		   - clone fds (I chose it क्रम now, it is the most universal
		     solution)

		   POSIX 1003.1g करोes not actually define this clearly
		   at all. POSIX 1003.1g करोesn't define a lot of things
		   clearly however!

		*/

		sk_peek_offset_fwd(sk, size);

		अगर (UNIXCB(skb).fp)
			scm.fp = scm_fp_dup(UNIXCB(skb).fp);
	पूर्ण
	err = (flags & MSG_TRUNC) ? skb->len - skip : size;

	scm_recv(sock, msg, &scm, flags);

out_मुक्त:
	skb_मुक्त_datagram(sk, skb);
	mutex_unlock(&u->iolock);
out:
	वापस err;
पूर्ण

/*
 *	Sleep until more data has arrived. But check क्रम races..
 */
अटल दीर्घ unix_stream_data_रुको(काष्ठा sock *sk, दीर्घ समयo,
				  काष्ठा sk_buff *last, अचिन्हित पूर्णांक last_len,
				  bool मुक्तzable)
अणु
	काष्ठा sk_buff *tail;
	DEFINE_WAIT(रुको);

	unix_state_lock(sk);

	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);

		tail = skb_peek_tail(&sk->sk_receive_queue);
		अगर (tail != last ||
		    (tail && tail->len != last_len) ||
		    sk->sk_err ||
		    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
		    संकेत_pending(current) ||
		    !समयo)
			अवरोध;

		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		unix_state_unlock(sk);
		अगर (मुक्तzable)
			समयo = मुक्तzable_schedule_समयout(समयo);
		अन्यथा
			समयo = schedule_समयout(समयo);
		unix_state_lock(sk);

		अगर (sock_flag(sk, SOCK_DEAD))
			अवरोध;

		sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	पूर्ण

	finish_रुको(sk_sleep(sk), &रुको);
	unix_state_unlock(sk);
	वापस समयo;
पूर्ण

अटल अचिन्हित पूर्णांक unix_skb_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->len - UNIXCB(skb).consumed;
पूर्ण

काष्ठा unix_stream_पढ़ो_state अणु
	पूर्णांक (*recv_actor)(काष्ठा sk_buff *, पूर्णांक, पूर्णांक,
			  काष्ठा unix_stream_पढ़ो_state *);
	काष्ठा socket *socket;
	काष्ठा msghdr *msg;
	काष्ठा pipe_inode_info *pipe;
	माप_प्रकार size;
	पूर्णांक flags;
	अचिन्हित पूर्णांक splice_flags;
पूर्ण;

अटल पूर्णांक unix_stream_पढ़ो_generic(काष्ठा unix_stream_पढ़ो_state *state,
				    bool मुक्तzable)
अणु
	काष्ठा scm_cookie scm;
	काष्ठा socket *sock = state->socket;
	काष्ठा sock *sk = sock->sk;
	काष्ठा unix_sock *u = unix_sk(sk);
	पूर्णांक copied = 0;
	पूर्णांक flags = state->flags;
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	bool check_creds = false;
	पूर्णांक target;
	पूर्णांक err = 0;
	दीर्घ समयo;
	पूर्णांक skip;
	माप_प्रकार size = state->size;
	अचिन्हित पूर्णांक last_len;

	अगर (unlikely(sk->sk_state != TCP_ESTABLISHED)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (unlikely(flags & MSG_OOB)) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	target = sock_rcvlowat(sk, flags & MSG_WAITALL, size);
	समयo = sock_rcvसमयo(sk, noblock);

	स_रखो(&scm, 0, माप(scm));

	/* Lock the socket to prevent queue disordering
	 * जबतक sleeps in स_नकल_tomsg
	 */
	mutex_lock(&u->iolock);

	skip = max(sk_peek_offset(sk, flags), 0);

	करो अणु
		पूर्णांक chunk;
		bool drop_skb;
		काष्ठा sk_buff *skb, *last;

reकरो:
		unix_state_lock(sk);
		अगर (sock_flag(sk, SOCK_DEAD)) अणु
			err = -ECONNRESET;
			जाओ unlock;
		पूर्ण
		last = skb = skb_peek(&sk->sk_receive_queue);
		last_len = last ? last->len : 0;
again:
		अगर (skb == शून्य) अणु
			अगर (copied >= target)
				जाओ unlock;

			/*
			 *	POSIX 1003.1g mandates this order.
			 */

			err = sock_error(sk);
			अगर (err)
				जाओ unlock;
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				जाओ unlock;

			unix_state_unlock(sk);
			अगर (!समयo) अणु
				err = -EAGAIN;
				अवरोध;
			पूर्ण

			mutex_unlock(&u->iolock);

			समयo = unix_stream_data_रुको(sk, समयo, last,
						      last_len, मुक्तzable);

			अगर (संकेत_pending(current)) अणु
				err = sock_पूर्णांकr_त्रुटि_सं(समयo);
				scm_destroy(&scm);
				जाओ out;
			पूर्ण

			mutex_lock(&u->iolock);
			जाओ reकरो;
unlock:
			unix_state_unlock(sk);
			अवरोध;
		पूर्ण

		जबतक (skip >= unix_skb_len(skb)) अणु
			skip -= unix_skb_len(skb);
			last = skb;
			last_len = skb->len;
			skb = skb_peek_next(skb, &sk->sk_receive_queue);
			अगर (!skb)
				जाओ again;
		पूर्ण

		unix_state_unlock(sk);

		अगर (check_creds) अणु
			/* Never glue messages from dअगरferent ग_लिखोrs */
			अगर (!unix_skb_scm_eq(skb, &scm))
				अवरोध;
		पूर्ण अन्यथा अगर (test_bit(SOCK_PASSCRED, &sock->flags)) अणु
			/* Copy credentials */
			scm_set_cred(&scm, UNIXCB(skb).pid, UNIXCB(skb).uid, UNIXCB(skb).gid);
			unix_set_secdata(&scm, skb);
			check_creds = true;
		पूर्ण

		/* Copy address just once */
		अगर (state->msg && state->msg->msg_name) अणु
			DECLARE_SOCKADDR(काष्ठा sockaddr_un *, sunaddr,
					 state->msg->msg_name);
			unix_copy_addr(state->msg, skb->sk);
			sunaddr = शून्य;
		पूर्ण

		chunk = min_t(अचिन्हित पूर्णांक, unix_skb_len(skb) - skip, size);
		skb_get(skb);
		chunk = state->recv_actor(skb, skip, chunk, state);
		drop_skb = !unix_skb_len(skb);
		/* skb is only safe to use अगर !drop_skb */
		consume_skb(skb);
		अगर (chunk < 0) अणु
			अगर (copied == 0)
				copied = -EFAULT;
			अवरोध;
		पूर्ण
		copied += chunk;
		size -= chunk;

		अगर (drop_skb) अणु
			/* the skb was touched by a concurrent पढ़ोer;
			 * we should not expect anything from this skb
			 * anymore and assume it invalid - we can be
			 * sure it was dropped from the socket queue
			 *
			 * let's report a लघु पढ़ो
			 */
			err = 0;
			अवरोध;
		पूर्ण

		/* Mark पढ़ो part of skb as used */
		अगर (!(flags & MSG_PEEK)) अणु
			UNIXCB(skb).consumed += chunk;

			sk_peek_offset_bwd(sk, chunk);

			अगर (UNIXCB(skb).fp) अणु
				scm_stat_del(sk, skb);
				unix_detach_fds(&scm, skb);
			पूर्ण

			अगर (unix_skb_len(skb))
				अवरोध;

			skb_unlink(skb, &sk->sk_receive_queue);
			consume_skb(skb);

			अगर (scm.fp)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* It is questionable, see note in unix_dgram_recvmsg.
			 */
			अगर (UNIXCB(skb).fp)
				scm.fp = scm_fp_dup(UNIXCB(skb).fp);

			sk_peek_offset_fwd(sk, chunk);

			अगर (UNIXCB(skb).fp)
				अवरोध;

			skip = 0;
			last = skb;
			last_len = skb->len;
			unix_state_lock(sk);
			skb = skb_peek_next(skb, &sk->sk_receive_queue);
			अगर (skb)
				जाओ again;
			unix_state_unlock(sk);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (size);

	mutex_unlock(&u->iolock);
	अगर (state->msg)
		scm_recv(sock, state->msg, &scm, flags);
	अन्यथा
		scm_destroy(&scm);
out:
	वापस copied ? : err;
पूर्ण

अटल पूर्णांक unix_stream_पढ़ो_actor(काष्ठा sk_buff *skb,
				  पूर्णांक skip, पूर्णांक chunk,
				  काष्ठा unix_stream_पढ़ो_state *state)
अणु
	पूर्णांक ret;

	ret = skb_copy_datagram_msg(skb, UNIXCB(skb).consumed + skip,
				    state->msg, chunk);
	वापस ret ?: chunk;
पूर्ण

अटल पूर्णांक unix_stream_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा unix_stream_पढ़ो_state state = अणु
		.recv_actor = unix_stream_पढ़ो_actor,
		.socket = sock,
		.msg = msg,
		.size = size,
		.flags = flags
	पूर्ण;

	वापस unix_stream_पढ़ो_generic(&state, true);
पूर्ण

अटल पूर्णांक unix_stream_splice_actor(काष्ठा sk_buff *skb,
				    पूर्णांक skip, पूर्णांक chunk,
				    काष्ठा unix_stream_पढ़ो_state *state)
अणु
	वापस skb_splice_bits(skb, state->socket->sk,
			       UNIXCB(skb).consumed + skip,
			       state->pipe, chunk, state->splice_flags);
पूर्ण

अटल sमाप_प्रकार unix_stream_splice_पढ़ो(काष्ठा socket *sock,  loff_t *ppos,
				       काष्ठा pipe_inode_info *pipe,
				       माप_प्रकार size, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा unix_stream_पढ़ो_state state = अणु
		.recv_actor = unix_stream_splice_actor,
		.socket = sock,
		.pipe = pipe,
		.size = size,
		.splice_flags = flags,
	पूर्ण;

	अगर (unlikely(*ppos))
		वापस -ESPIPE;

	अगर (sock->file->f_flags & O_NONBLOCK ||
	    flags & SPLICE_F_NONBLOCK)
		state.flags = MSG_DONTWAIT;

	वापस unix_stream_पढ़ो_generic(&state, false);
पूर्ण

अटल पूर्णांक unix_shutकरोwn(काष्ठा socket *sock, पूर्णांक mode)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sock *other;

	अगर (mode < SHUT_RD || mode > SHUT_RDWR)
		वापस -EINVAL;
	/* This maps:
	 * SHUT_RD   (0) -> RCV_SHUTDOWN  (1)
	 * SHUT_WR   (1) -> SEND_SHUTDOWN (2)
	 * SHUT_RDWR (2) -> SHUTDOWN_MASK (3)
	 */
	++mode;

	unix_state_lock(sk);
	sk->sk_shutकरोwn |= mode;
	other = unix_peer(sk);
	अगर (other)
		sock_hold(other);
	unix_state_unlock(sk);
	sk->sk_state_change(sk);

	अगर (other &&
		(sk->sk_type == SOCK_STREAM || sk->sk_type == SOCK_SEQPACKET)) अणु

		पूर्णांक peer_mode = 0;

		अगर (mode&RCV_SHUTDOWN)
			peer_mode |= SEND_SHUTDOWN;
		अगर (mode&SEND_SHUTDOWN)
			peer_mode |= RCV_SHUTDOWN;
		unix_state_lock(other);
		other->sk_shutकरोwn |= peer_mode;
		unix_state_unlock(other);
		other->sk_state_change(other);
		अगर (peer_mode == SHUTDOWN_MASK)
			sk_wake_async(other, SOCK_WAKE_WAITD, POLL_HUP);
		अन्यथा अगर (peer_mode & RCV_SHUTDOWN)
			sk_wake_async(other, SOCK_WAKE_WAITD, POLL_IN);
	पूर्ण
	अगर (other)
		sock_put(other);

	वापस 0;
पूर्ण

दीर्घ unix_inq_len(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;
	दीर्घ amount = 0;

	अगर (sk->sk_state == TCP_LISTEN)
		वापस -EINVAL;

	spin_lock(&sk->sk_receive_queue.lock);
	अगर (sk->sk_type == SOCK_STREAM ||
	    sk->sk_type == SOCK_SEQPACKET) अणु
		skb_queue_walk(&sk->sk_receive_queue, skb)
			amount += unix_skb_len(skb);
	पूर्ण अन्यथा अणु
		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb)
			amount = skb->len;
	पूर्ण
	spin_unlock(&sk->sk_receive_queue.lock);

	वापस amount;
पूर्ण
EXPORT_SYMBOL_GPL(unix_inq_len);

दीर्घ unix_outq_len(काष्ठा sock *sk)
अणु
	वापस sk_wmem_alloc_get(sk);
पूर्ण
EXPORT_SYMBOL_GPL(unix_outq_len);

अटल पूर्णांक unix_खोलो_file(काष्ठा sock *sk)
अणु
	काष्ठा path path;
	काष्ठा file *f;
	पूर्णांक fd;

	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!smp_load_acquire(&unix_sk(sk)->addr))
		वापस -ENOENT;

	path = unix_sk(sk)->path;
	अगर (!path.dentry)
		वापस -ENOENT;

	path_get(&path);

	fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (fd < 0)
		जाओ out;

	f = dentry_खोलो(&path, O_PATH, current_cred());
	अगर (IS_ERR(f)) अणु
		put_unused_fd(fd);
		fd = PTR_ERR(f);
		जाओ out;
	पूर्ण

	fd_install(fd, f);
out:
	path_put(&path);

	वापस fd;
पूर्ण

अटल पूर्णांक unix_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	दीर्घ amount = 0;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SIOCOUTQ:
		amount = unix_outq_len(sk);
		err = put_user(amount, (पूर्णांक __user *)arg);
		अवरोध;
	हाल SIOCINQ:
		amount = unix_inq_len(sk);
		अगर (amount < 0)
			err = amount;
		अन्यथा
			err = put_user(amount, (पूर्णांक __user *)arg);
		अवरोध;
	हाल SIOCUNIXखाता:
		err = unix_खोलो_file(sk);
		अवरोध;
	शेष:
		err = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक unix_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस unix_ioctl(sock, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल __poll_t unix_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	__poll_t mask;

	sock_poll_रुको(file, sock, रुको);
	mask = 0;

	/* exceptional events? */
	अगर (sk->sk_err)
		mask |= EPOLLERR;
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;

	/* पढ़ोable? */
	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* Connection-based need to check क्रम termination and startup */
	अगर ((sk->sk_type == SOCK_STREAM || sk->sk_type == SOCK_SEQPACKET) &&
	    sk->sk_state == TCP_CLOSE)
		mask |= EPOLLHUP;

	/*
	 * we set writable also when the other side has shut करोwn the
	 * connection. This prevents stuck sockets.
	 */
	अगर (unix_writable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	वापस mask;
पूर्ण

अटल __poll_t unix_dgram_poll(काष्ठा file *file, काष्ठा socket *sock,
				    poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk, *other;
	अचिन्हित पूर्णांक writable;
	__poll_t mask;

	sock_poll_रुको(file, sock, रुको);
	mask = 0;

	/* exceptional events? */
	अगर (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR |
			(sock_flag(sk, SOCK_SELECT_ERR_QUEUE) ? EPOLLPRI : 0);

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;

	/* पढ़ोable? */
	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* Connection-based need to check क्रम termination and startup */
	अगर (sk->sk_type == SOCK_SEQPACKET) अणु
		अगर (sk->sk_state == TCP_CLOSE)
			mask |= EPOLLHUP;
		/* connection hasn't started yet? */
		अगर (sk->sk_state == TCP_SYN_SENT)
			वापस mask;
	पूर्ण

	/* No ग_लिखो status requested, aव्योम expensive OUT tests. */
	अगर (!(poll_requested_events(रुको) & (EPOLLWRBAND|EPOLLWRNORM|EPOLLOUT)))
		वापस mask;

	writable = unix_writable(sk);
	अगर (writable) अणु
		unix_state_lock(sk);

		other = unix_peer(sk);
		अगर (other && unix_peer(other) != sk &&
		    unix_recvq_full(other) &&
		    unix_dgram_peer_wake_me(sk, other))
			writable = 0;

		unix_state_unlock(sk);
	पूर्ण

	अगर (writable)
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;
	अन्यथा
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	वापस mask;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

#घोषणा BUCKET_SPACE (BITS_PER_LONG - (UNIX_HASH_BITS + 1) - 1)

#घोषणा get_bucket(x) ((x) >> BUCKET_SPACE)
#घोषणा get_offset(x) ((x) & ((1L << BUCKET_SPACE) - 1))
#घोषणा set_bucket_offset(b, o) ((b) << BUCKET_SPACE | (o))

अटल काष्ठा sock *unix_from_bucket(काष्ठा seq_file *seq, loff_t *pos)
अणु
	अचिन्हित दीर्घ offset = get_offset(*pos);
	अचिन्हित दीर्घ bucket = get_bucket(*pos);
	काष्ठा sock *sk;
	अचिन्हित दीर्घ count = 0;

	क्रम (sk = sk_head(&unix_socket_table[bucket]); sk; sk = sk_next(sk)) अणु
		अगर (sock_net(sk) != seq_file_net(seq))
			जारी;
		अगर (++count == offset)
			अवरोध;
	पूर्ण

	वापस sk;
पूर्ण

अटल काष्ठा sock *unix_next_socket(काष्ठा seq_file *seq,
				     काष्ठा sock *sk,
				     loff_t *pos)
अणु
	अचिन्हित दीर्घ bucket;

	जबतक (sk > (काष्ठा sock *)SEQ_START_TOKEN) अणु
		sk = sk_next(sk);
		अगर (!sk)
			जाओ next_bucket;
		अगर (sock_net(sk) == seq_file_net(seq))
			वापस sk;
	पूर्ण

	करो अणु
		sk = unix_from_bucket(seq, pos);
		अगर (sk)
			वापस sk;

next_bucket:
		bucket = get_bucket(*pos) + 1;
		*pos = set_bucket_offset(bucket, 1);
	पूर्ण जबतक (bucket < ARRAY_SIZE(unix_socket_table));

	वापस शून्य;
पूर्ण

अटल व्योम *unix_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(unix_table_lock)
अणु
	spin_lock(&unix_table_lock);

	अगर (!*pos)
		वापस SEQ_START_TOKEN;

	अगर (get_bucket(*pos) >= ARRAY_SIZE(unix_socket_table))
		वापस शून्य;

	वापस unix_next_socket(seq, शून्य, pos);
पूर्ण

अटल व्योम *unix_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस unix_next_socket(seq, v, pos);
पूर्ण

अटल व्योम unix_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(unix_table_lock)
अणु
	spin_unlock(&unix_table_lock);
पूर्ण

अटल पूर्णांक unix_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "Num       RefCount Protocol Flags    Type St "
			 "Inode Path\n");
	अन्यथा अणु
		काष्ठा sock *s = v;
		काष्ठा unix_sock *u = unix_sk(s);
		unix_state_lock(s);

		seq_म_लिखो(seq, "%pK: %08X %08X %08X %04X %02X %5lu",
			s,
			refcount_पढ़ो(&s->sk_refcnt),
			0,
			s->sk_state == TCP_LISTEN ? __SO_ACCEPTCON : 0,
			s->sk_type,
			s->sk_socket ?
			(s->sk_state == TCP_ESTABLISHED ? SS_CONNECTED : SS_UNCONNECTED) :
			(s->sk_state == TCP_ESTABLISHED ? SS_CONNECTING : SS_DISCONNECTING),
			sock_i_ino(s));

		अगर (u->addr) अणु	// under unix_table_lock here
			पूर्णांक i, len;
			seq_अ_दो(seq, ' ');

			i = 0;
			len = u->addr->len - माप(लघु);
			अगर (!UNIX_ABSTRACT(s))
				len--;
			अन्यथा अणु
				seq_अ_दो(seq, '@');
				i++;
			पूर्ण
			क्रम ( ; i < len; i++)
				seq_अ_दो(seq, u->addr->name->sun_path[i] ?:
					 '@');
		पूर्ण
		unix_state_unlock(s);
		seq_अ_दो(seq, '\n');
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations unix_seq_ops = अणु
	.start  = unix_seq_start,
	.next   = unix_seq_next,
	.stop   = unix_seq_stop,
	.show   = unix_seq_show,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा net_proto_family unix_family_ops = अणु
	.family = PF_UNIX,
	.create = unix_create,
	.owner	= THIS_MODULE,
पूर्ण;


अटल पूर्णांक __net_init unix_net_init(काष्ठा net *net)
अणु
	पूर्णांक error = -ENOMEM;

	net->unx.sysctl_max_dgram_qlen = 10;
	अगर (unix_sysctl_रेजिस्टर(net))
		जाओ out;

#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_net("unix", 0, net->proc_net, &unix_seq_ops,
			माप(काष्ठा seq_net_निजी))) अणु
		unix_sysctl_unरेजिस्टर(net);
		जाओ out;
	पूर्ण
#पूर्ण_अगर
	error = 0;
out:
	वापस error;
पूर्ण

अटल व्योम __net_निकास unix_net_निकास(काष्ठा net *net)
अणु
	unix_sysctl_unरेजिस्टर(net);
	हटाओ_proc_entry("unix", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations unix_net_ops = अणु
	.init = unix_net_init,
	.निकास = unix_net_निकास,
पूर्ण;

अटल पूर्णांक __init af_unix_init(व्योम)
अणु
	पूर्णांक rc = -1;

	BUILD_BUG_ON(माप(काष्ठा unix_skb_parms) > माप_field(काष्ठा sk_buff, cb));

	rc = proto_रेजिस्टर(&unix_proto, 1);
	अगर (rc != 0) अणु
		pr_crit("%s: Cannot create unix_sock SLAB cache!\n", __func__);
		जाओ out;
	पूर्ण

	sock_रेजिस्टर(&unix_family_ops);
	रेजिस्टर_pernet_subsys(&unix_net_ops);
out:
	वापस rc;
पूर्ण

अटल व्योम __निकास af_unix_निकास(व्योम)
अणु
	sock_unरेजिस्टर(PF_UNIX);
	proto_unरेजिस्टर(&unix_proto);
	unरेजिस्टर_pernet_subsys(&unix_net_ops);
पूर्ण

/* Earlier than device_initcall() so that other drivers invoking
   request_module() करोn't end up in a loop when modprobe tries
   to use a UNIX socket. But later than subsys_initcall() because
   we depend on stuff initialised there */
fs_initcall(af_unix_init);
module_निकास(af_unix_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_UNIX);
