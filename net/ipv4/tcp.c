<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Implementation of the Transmission Control Protocol(TCP).
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Mark Evans, <evansmp@uhura.aston.ac.uk>
 *		Corey Minyard <wf-rch!minyard@relay.EU.net>
 *		Florian La Roche, <flla@stud.uni-sb.de>
 *		Charles Hedrick, <hedrick@klinzhai.rutgers.edu>
 *		Linus Torvalds, <torvalds@cs.helsinki.fi>
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *		Matthew Dillon, <dillon@apollo.west.oic.com>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Jorge Cwik, <jorge@laser.satlink.net>
 *
 * Fixes:
 *		Alan Cox	:	Numerous verअगरy_area() calls
 *		Alan Cox	:	Set the ACK bit on a reset
 *		Alan Cox	:	Stopped it crashing अगर it बंदd जबतक
 *					sk->inuse=1 and was trying to connect
 *					(tcp_err()).
 *		Alan Cox	:	All icmp error handling was broken
 *					poपूर्णांकers passed where wrong and the
 *					socket was looked up backwards. Nobody
 *					tested any icmp error code obviously.
 *		Alan Cox	:	tcp_err() now handled properly. It
 *					wakes people on errors. poll
 *					behaves and the icmp error race
 *					has gone by moving it पूर्णांकo sock.c
 *		Alan Cox	:	tcp_send_reset() fixed to work क्रम
 *					everything not just packets क्रम
 *					unknown sockets.
 *		Alan Cox	:	tcp option processing.
 *		Alan Cox	:	Reset tweaked (still not 100%) [Had
 *					syn rule wrong]
 *		Herp Rosmanith  :	More reset fixes
 *		Alan Cox	:	No दीर्घer acks invalid rst frames.
 *					Acking any kind of RST is right out.
 *		Alan Cox	:	Sets an ignore me flag on an rst
 *					receive otherwise odd bits of prattle
 *					escape still
 *		Alan Cox	:	Fixed another acking RST frame bug.
 *					Should stop LAN workplace lockups.
 *		Alan Cox	: 	Some tidyups using the new skb list
 *					facilities
 *		Alan Cox	:	sk->keepखोलो now seems to work
 *		Alan Cox	:	Pulls options out correctly on accepts
 *		Alan Cox	:	Fixed assorted sk->rqueue->next errors
 *		Alan Cox	:	PSH करोesn't end a TCP पढ़ो. Switched a
 *					bit to skb ops.
 *		Alan Cox	:	Tidied tcp_data to aव्योम a potential
 *					nasty.
 *		Alan Cox	:	Added some better commenting, as the
 *					tcp is hard to follow
 *		Alan Cox	:	Removed incorrect check क्रम 20 * psh
 *	Michael O'Reilly	:	ack < copied bug fix.
 *	Johannes Stille		:	Misc tcp fixes (not all in yet).
 *		Alan Cox	:	FIN with no memory -> CRASH
 *		Alan Cox	:	Added socket option proto entries.
 *					Also added awareness of them to accept.
 *		Alan Cox	:	Added TCP options (SOL_TCP)
 *		Alan Cox	:	Switched wakeup calls to callbacks,
 *					so the kernel can layer network
 *					sockets.
 *		Alan Cox	:	Use ip_tos/ip_ttl settings.
 *		Alan Cox	:	Handle FIN (more) properly (we hope).
 *		Alan Cox	:	RST frames sent on unsynchronised
 *					state ack error.
 *		Alan Cox	:	Put in missing check क्रम SYN bit.
 *		Alan Cox	:	Added tcp_select_winकरोw() aka NET2E
 *					winकरोw non shrink trick.
 *		Alan Cox	:	Added a couple of small NET2E समयr
 *					fixes
 *		Charles Hedrick :	TCP fixes
 *		Toomas Tamm	:	TCP winकरोw fixes
 *		Alan Cox	:	Small URG fix to rlogin ^C ack fight
 *		Charles Hedrick	:	Rewrote most of it to actually work
 *		Linus		:	Rewrote tcp_पढ़ो() and URG handling
 *					completely
 *		Gerhard Koerting:	Fixed some missing समयr handling
 *		Matthew Dillon  :	Reworked TCP machine states as per RFC
 *		Gerhard Koerting:	PC/TCP workarounds
 *		Adam Caldwell	:	Assorted समयr/timing errors
 *		Matthew Dillon	:	Fixed another RST bug
 *		Alan Cox	:	Move to kernel side addressing changes.
 *		Alan Cox	:	Beginning work on TCP fastpathing
 *					(not yet usable)
 *		Arnt Gulbअक्रमsen:	Turboअक्षरged tcp_check() routine.
 *		Alan Cox	:	TCP fast path debugging
 *		Alan Cox	:	Winकरोw clamping
 *		Michael Riepe	:	Bug in tcp_check()
 *		Matt Dillon	:	More TCP improvements and RST bug fixes
 *		Matt Dillon	:	Yet more small nasties हटाओ from the
 *					TCP code (Be very nice to this man अगर
 *					tcp finally works 100%) 8)
 *		Alan Cox	:	BSD accept semantics.
 *		Alan Cox	:	Reset on बंदकरोwn bug.
 *	Peter De Schrijver	:	ENOTCONN check missing in tcp_sendto().
 *		Michael Pall	:	Handle poll() after URG properly in
 *					all हालs.
 *		Michael Pall	:	Unकरो the last fix in tcp_पढ़ो_urg()
 *					(multi URG PUSH broke rlogin).
 *		Michael Pall	:	Fix the multi URG PUSH problem in
 *					tcp_पढ़ोable(), poll() after URG
 *					works now.
 *		Michael Pall	:	recv(...,MSG_OOB) never blocks in the
 *					BSD api.
 *		Alan Cox	:	Changed the semantics of sk->socket to
 *					fix a race and a संकेत problem with
 *					accept() and async I/O.
 *		Alan Cox	:	Relaxed the rules on tcp_sendto().
 *		Yury Shevchuk	:	Really fixed accept() blocking problem.
 *		Craig I. Hagan  :	Allow क्रम BSD compatible TIME_WAIT क्रम
 *					clients/servers which listen in on
 *					fixed ports.
 *		Alan Cox	:	Cleaned the above up and shrank it to
 *					a sensible code size.
 *		Alan Cox	:	Self connect lockup fix.
 *		Alan Cox	:	No connect to multicast.
 *		Ross Biro	:	Close unaccepted children on master
 *					socket बंद.
 *		Alan Cox	:	Reset tracing code.
 *		Alan Cox	:	Spurious resets on shutकरोwn.
 *		Alan Cox	:	Giant 15 minute/60 second समयr error
 *		Alan Cox	:	Small whoops in polling beक्रमe an
 *					accept.
 *		Alan Cox	:	Kept the state trace facility since
 *					it's handy क्रम debugging.
 *		Alan Cox	:	More reset handler fixes.
 *		Alan Cox	:	Started rewriting the code based on
 *					the RFC's क्रम other useful protocol
 *					references see: Comer, KA9Q NOS, and
 *					क्रम a reference on the dअगरference
 *					between specअगरications and how BSD
 *					works see the 4.4lite source.
 *		A.N.Kuznetsov	:	Don't समय रुको on completion of tidy
 *					बंद.
 *		Linus Torvalds	:	Fin/Shutकरोwn & copied_seq changes.
 *		Linus Torvalds	:	Fixed BSD port reuse to work first syn
 *		Alan Cox	:	Reimplemented समयrs as per the RFC
 *					and using multiple समयrs क्रम sanity.
 *		Alan Cox	:	Small bug fixes, and a lot of new
 *					comments.
 *		Alan Cox	:	Fixed dual पढ़ोer crash by locking
 *					the buffers (much like datagram.c)
 *		Alan Cox	:	Fixed stuck sockets in probe. A probe
 *					now माला_लो fed up of retrying without
 *					(even a no space) answer.
 *		Alan Cox	:	Extracted closing code better
 *		Alan Cox	:	Fixed the closing state machine to
 *					resemble the RFC.
 *		Alan Cox	:	More 'per spec' fixes.
 *		Jorge Cwik	:	Even faster checksumming.
 *		Alan Cox	:	tcp_data() करोesn't ack illegal PSH
 *					only frames. At least one pc tcp stack
 *					generates them.
 *		Alan Cox	:	Cache last socket.
 *		Alan Cox	:	Per route irtt.
 *		Matt Day	:	poll()->select() match BSD precisely on error
 *		Alan Cox	:	New buffers
 *		Marc Tamsky	:	Various sk->prot->retransmits and
 *					sk->retransmits misupdating fixed.
 *					Fixed tcp_ग_लिखो_समयout: stuck बंद,
 *					and TCP syn retries माला_लो used now.
 *		Mark Yarvis	:	In tcp_पढ़ो_wakeup(), करोn't send an
 *					ack अगर state is TCP_CLOSED.
 *		Alan Cox	:	Look up device on a retransmit - routes may
 *					change. Doesn't yet cope with MSS shrink right
 *					but it's a start!
 *		Marc Tamsky	:	Closing in closing fixes.
 *		Mike Shaver	:	RFC1122 verअगरications.
 *		Alan Cox	:	rcv_saddr errors.
 *		Alan Cox	:	Block द्विगुन connect().
 *		Alan Cox	:	Small hooks क्रम enSKIP.
 *		Alexey Kuznetsov:	Path MTU discovery.
 *		Alan Cox	:	Support soft errors.
 *		Alan Cox	:	Fix MTU discovery pathological हाल
 *					when the remote claims no mtu!
 *		Marc Tamsky	:	TCP_CLOSE fix.
 *		Colin (G3TNE)	:	Send a reset on syn ack replies in
 *					winकरोw but wrong (fixes NT lpd problems)
 *		Pedro Roque	:	Better TCP winकरोw handling, delayed ack.
 *		Joerg Reuter	:	No modअगरication of locked buffers in
 *					tcp_करो_retransmit()
 *		Eric Schenk	:	Changed receiver side silly winकरोw
 *					aव्योमance algorithm to BSD style
 *					algorithm. This द्विगुनs throughput
 *					against machines running Solaris,
 *					and seems to result in general
 *					improvement.
 *	Stefan Magdalinski	:	adjusted tcp_पढ़ोable() to fix FIONREAD
 *	Willy Konynenberg	:	Transparent proxying support.
 *	Mike McLagan		:	Routing by source
 *		Keith Owens	:	Do proper merging with partial SKB's in
 *					tcp_करो_sendmsg to aव्योम burstiness.
 *		Eric Schenk	:	Fix fast बंद करोwn bug with
 *					shutकरोwn() followed by बंद().
 *		Andi Kleen 	:	Make poll agree with SIGIO
 *	Salvatore Sanfilippo	:	Support SO_LINGER with linger == 1 and
 *					lingerसमय == 0 (RFC 793 ABORT Call)
 *	Hirokazu Takahashi	:	Use copy_from_user() instead of
 *					csum_and_copy_from_user() अगर possible.
 *
 * Description of States:
 *
 *	TCP_SYN_SENT		sent a connection request, रुकोing क्रम ack
 *
 *	TCP_SYN_RECV		received a connection request, sent ack,
 *				रुकोing क्रम final ack in three-way handshake.
 *
 *	TCP_ESTABLISHED		connection established
 *
 *	TCP_FIN_WAIT1		our side has shutकरोwn, रुकोing to complete
 *				transmission of reमुख्यing buffered data
 *
 *	TCP_FIN_WAIT2		all buffered data sent, रुकोing क्रम remote
 *				to shutकरोwn
 *
 *	TCP_CLOSING		both sides have shutकरोwn but we still have
 *				data we have to finish sending
 *
 *	TCP_TIME_WAIT		समयout to catch resent junk beक्रमe entering
 *				बंदd, can only be entered from FIN_WAIT2
 *				or CLOSING.  Required because the other end
 *				may not have gotten our last ACK causing it
 *				to retransmit the data packet (which we ignore)
 *
 *	TCP_CLOSE_WAIT		remote side has shutकरोwn and is रुकोing क्रम
 *				us to finish writing our data and to shutकरोwn
 *				(we have to बंद() to move on to LAST_ACK)
 *
 *	TCP_LAST_ACK		out side has shutकरोwn after remote has
 *				shutकरोwn.  There may still be data in our
 *				buffer that we have to finish sending
 *
 *	TCP_CLOSE		socket is finished
 */

#घोषणा pr_fmt(fmt) "TCP: " fmt

#समावेश <crypto/hash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/poll.h>
#समावेश <linux/inet_diag.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/splice.h>
#समावेश <linux/net.h>
#समावेश <linux/socket.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/memblock.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश <linux/cache.h>
#समावेश <linux/err.h>
#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/btf.h>

#समावेश <net/icmp.h>
#समावेश <net/inet_common.h>
#समावेश <net/tcp.h>
#समावेश <net/mptcp.h>
#समावेश <net/xfrm.h>
#समावेश <net/ip.h>
#समावेश <net/sock.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <net/busy_poll.h>

/* Track pending CMSGs. */
क्रमागत अणु
	TCP_CMSG_INQ = 1,
	TCP_CMSG_TS = 2
पूर्ण;

काष्ठा percpu_counter tcp_orphan_count;
EXPORT_SYMBOL_GPL(tcp_orphan_count);

दीर्घ sysctl_tcp_mem[3] __पढ़ो_mostly;
EXPORT_SYMBOL(sysctl_tcp_mem);

atomic_दीर्घ_t tcp_memory_allocated;	/* Current allocated memory. */
EXPORT_SYMBOL(tcp_memory_allocated);

#अगर IS_ENABLED(CONFIG_SMC)
DEFINE_STATIC_KEY_FALSE(tcp_have_smc);
EXPORT_SYMBOL(tcp_have_smc);
#पूर्ण_अगर

/*
 * Current number of TCP sockets.
 */
काष्ठा percpu_counter tcp_sockets_allocated;
EXPORT_SYMBOL(tcp_sockets_allocated);

/*
 * TCP splice context
 */
काष्ठा tcp_splice_state अणु
	काष्ठा pipe_inode_info *pipe;
	माप_प्रकार len;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/*
 * Pressure flag: try to collapse.
 * Technical note: it is used by multiple contexts non atomically.
 * All the __sk_mem_schedule() is of this nature: accounting
 * is strict, actions are advisory and have some latency.
 */
अचिन्हित दीर्घ tcp_memory_pressure __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(tcp_memory_pressure);

DEFINE_STATIC_KEY_FALSE(tcp_rx_skb_cache_key);
EXPORT_SYMBOL(tcp_rx_skb_cache_key);

DEFINE_STATIC_KEY_FALSE(tcp_tx_skb_cache_key);

व्योम tcp_enter_memory_pressure(काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ val;

	अगर (READ_ONCE(tcp_memory_pressure))
		वापस;
	val = jअगरfies;

	अगर (!val)
		val--;
	अगर (!cmpxchg(&tcp_memory_pressure, 0, val))
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPMEMORYPRESSURES);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_enter_memory_pressure);

व्योम tcp_leave_memory_pressure(काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ val;

	अगर (!READ_ONCE(tcp_memory_pressure))
		वापस;
	val = xchg(&tcp_memory_pressure, 0);
	अगर (val)
		NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPMEMORYPRESSURESCHRONO,
			      jअगरfies_to_msecs(jअगरfies - val));
पूर्ण
EXPORT_SYMBOL_GPL(tcp_leave_memory_pressure);

/* Convert seconds to retransmits based on initial and max समयout */
अटल u8 secs_to_retrans(पूर्णांक seconds, पूर्णांक समयout, पूर्णांक rto_max)
अणु
	u8 res = 0;

	अगर (seconds > 0) अणु
		पूर्णांक period = समयout;

		res = 1;
		जबतक (seconds > period && res < 255) अणु
			res++;
			समयout <<= 1;
			अगर (समयout > rto_max)
				समयout = rto_max;
			period += समयout;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

/* Convert retransmits to seconds based on initial and max समयout */
अटल पूर्णांक retrans_to_secs(u8 retrans, पूर्णांक समयout, पूर्णांक rto_max)
अणु
	पूर्णांक period = 0;

	अगर (retrans > 0) अणु
		period = समयout;
		जबतक (--retrans) अणु
			समयout <<= 1;
			अगर (समयout > rto_max)
				समयout = rto_max;
			period += समयout;
		पूर्ण
	पूर्ण
	वापस period;
पूर्ण

अटल u64 tcp_compute_delivery_rate(स्थिर काष्ठा tcp_sock *tp)
अणु
	u32 rate = READ_ONCE(tp->rate_delivered);
	u32 पूर्णांकv = READ_ONCE(tp->rate_पूर्णांकerval_us);
	u64 rate64 = 0;

	अगर (rate && पूर्णांकv) अणु
		rate64 = (u64)rate * tp->mss_cache * USEC_PER_SEC;
		करो_भाग(rate64, पूर्णांकv);
	पूर्ण
	वापस rate64;
पूर्ण

/* Address-family independent initialization क्रम a tcp_sock.
 *
 * NOTE: A lot of things set to zero explicitly by call to
 *       sk_alloc() so need not be करोne here.
 */
व्योम tcp_init_sock(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	tp->out_of_order_queue = RB_ROOT;
	sk->tcp_rtx_queue = RB_ROOT;
	tcp_init_xmit_समयrs(sk);
	INIT_LIST_HEAD(&tp->tsq_node);
	INIT_LIST_HEAD(&tp->tsorted_sent_queue);

	icsk->icsk_rto = TCP_TIMEOUT_INIT;
	icsk->icsk_rto_min = TCP_RTO_MIN;
	icsk->icsk_delack_max = TCP_DELACK_MAX;
	tp->mdev_us = jअगरfies_to_usecs(TCP_TIMEOUT_INIT);
	minmax_reset(&tp->rtt_min, tcp_jअगरfies32, ~0U);

	/* So many TCP implementations out there (incorrectly) count the
	 * initial SYN frame in their delayed-ACK and congestion control
	 * algorithms that we must have the following bandaid to talk
	 * efficiently to them.  -DaveM
	 */
	tp->snd_cwnd = TCP_INIT_CWND;

	/* There's a bubble in the pipe until at least the first ACK. */
	tp->app_limited = ~0U;

	/* See draft-stevens-tcpca-spec-01 क्रम discussion of the
	 * initialization of these values.
	 */
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	tp->snd_cwnd_clamp = ~0;
	tp->mss_cache = TCP_MSS_DEFAULT;

	tp->reordering = sock_net(sk)->ipv4.sysctl_tcp_reordering;
	tcp_assign_congestion_control(sk);

	tp->tsoffset = 0;
	tp->rack.reo_wnd_steps = 1;

	sk->sk_ग_लिखो_space = sk_stream_ग_लिखो_space;
	sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

	icsk->icsk_sync_mss = tcp_sync_mss;

	WRITE_ONCE(sk->sk_sndbuf, sock_net(sk)->ipv4.sysctl_tcp_wmem[1]);
	WRITE_ONCE(sk->sk_rcvbuf, sock_net(sk)->ipv4.sysctl_tcp_rmem[1]);

	sk_sockets_allocated_inc(sk);
	sk->sk_route_क्रमced_caps = NETIF_F_GSO;
पूर्ण
EXPORT_SYMBOL(tcp_init_sock);

अटल व्योम tcp_tx_बारtamp(काष्ठा sock *sk, u16 tsflags)
अणु
	काष्ठा sk_buff *skb = tcp_ग_लिखो_queue_tail(sk);

	अगर (tsflags && skb) अणु
		काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
		काष्ठा tcp_skb_cb *tcb = TCP_SKB_CB(skb);

		sock_tx_बारtamp(sk, tsflags, &shinfo->tx_flags);
		अगर (tsflags & SOF_TIMESTAMPING_TX_ACK)
			tcb->txstamp_ack = 1;
		अगर (tsflags & SOF_TIMESTAMPING_TX_RECORD_MASK)
			shinfo->tskey = TCP_SKB_CB(skb)->seq + skb->len - 1;
	पूर्ण
पूर्ण

अटल bool tcp_stream_is_पढ़ोable(काष्ठा sock *sk, पूर्णांक target)
अणु
	अगर (tcp_epollin_पढ़ोy(sk, target))
		वापस true;

	अगर (sk->sk_prot->stream_memory_पढ़ो)
		वापस sk->sk_prot->stream_memory_पढ़ो(sk);
	वापस false;
पूर्ण

/*
 *	Wait क्रम a TCP event.
 *
 *	Note that we करोn't need to lock the socket, as the upper poll layers
 *	take care of normal races (between the test and the event) and we करोn't
 *	go look at any of the socket buffers directly.
 */
__poll_t tcp_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको)
अणु
	__poll_t mask;
	काष्ठा sock *sk = sock->sk;
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक state;

	sock_poll_रुको(file, sock, रुको);

	state = inet_sk_state_load(sk);
	अगर (state == TCP_LISTEN)
		वापस inet_csk_listen_poll(sk);

	/* Socket is not locked. We are रक्षित from async events
	 * by poll logic and correct handling of state changes
	 * made by other thपढ़ोs is impossible in any हाल.
	 */

	mask = 0;

	/*
	 * EPOLLHUP is certainly not करोne right. But poll() करोesn't
	 * have a notion of HUP in just one direction, and क्रम a
	 * socket the पढ़ो side is more पूर्णांकeresting.
	 *
	 * Some poll() करोcumentation says that EPOLLHUP is incompatible
	 * with the EPOLLOUT/POLLWR flags, so somebody should check this
	 * all. But careful, it tends to be safer to वापस too many
	 * bits than too few, and you can easily अवरोध real applications
	 * अगर you करोn't tell them that something has hung up!
	 *
	 * Check-me.
	 *
	 * Check number 1. EPOLLHUP is _UNMASKABLE_ event (see UNIX98 and
	 * our fs/select.c). It means that after we received खातापूर्ण,
	 * poll always वापसs immediately, making impossible poll() on ग_लिखो()
	 * in state CLOSE_WAIT. One solution is evident --- to set EPOLLHUP
	 * अगर and only अगर shutकरोwn has been made in both directions.
	 * Actually, it is पूर्णांकeresting to look how Solaris and DUX
	 * solve this dilemma. I would prefer, अगर EPOLLHUP were maskable,
	 * then we could set it on SND_SHUTDOWN. BTW examples given
	 * in Stevens' books assume exactly this behaviour, it explains
	 * why EPOLLHUP is incompatible with EPOLLOUT.	--ANK
	 *
	 * NOTE. Check क्रम TCP_CLOSE is added. The goal is to prevent
	 * blocking on fresh not-connected or disconnected socket. --ANK
	 */
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK || state == TCP_CLOSE)
		mask |= EPOLLHUP;
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;

	/* Connected or passive Fast Open socket? */
	अगर (state != TCP_SYN_SENT &&
	    (state != TCP_SYN_RECV || rcu_access_poपूर्णांकer(tp->fastखोलो_rsk))) अणु
		पूर्णांक target = sock_rcvlowat(sk, 0, पूर्णांक_उच्च);

		अगर (READ_ONCE(tp->urg_seq) == READ_ONCE(tp->copied_seq) &&
		    !sock_flag(sk, SOCK_URGINLINE) &&
		    tp->urg_data)
			target++;

		अगर (tcp_stream_is_पढ़ोable(sk, target))
			mask |= EPOLLIN | EPOLLRDNORM;

		अगर (!(sk->sk_shutकरोwn & SEND_SHUTDOWN)) अणु
			अगर (__sk_stream_is_ग_लिखोable(sk, 1)) अणु
				mask |= EPOLLOUT | EPOLLWRNORM;
			पूर्ण अन्यथा अणु  /* send SIGIO later */
				sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
				set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);

				/* Race अवरोधer. If space is मुक्तd after
				 * wspace test but beक्रमe the flags are set,
				 * IO संकेत will be lost. Memory barrier
				 * pairs with the input side.
				 */
				smp_mb__after_atomic();
				अगर (__sk_stream_is_ग_लिखोable(sk, 1))
					mask |= EPOLLOUT | EPOLLWRNORM;
			पूर्ण
		पूर्ण अन्यथा
			mask |= EPOLLOUT | EPOLLWRNORM;

		अगर (tp->urg_data & TCP_URG_VALID)
			mask |= EPOLLPRI;
	पूर्ण अन्यथा अगर (state == TCP_SYN_SENT && inet_sk(sk)->defer_connect) अणु
		/* Active TCP fastखोलो socket with defer_connect
		 * Return EPOLLOUT so application can call ग_लिखो()
		 * in order क्रम kernel to generate SYN+data
		 */
		mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण
	/* This barrier is coupled with smp_wmb() in tcp_reset() */
	smp_rmb();
	अगर (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR;

	वापस mask;
पूर्ण
EXPORT_SYMBOL(tcp_poll);

पूर्णांक tcp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक answ;
	bool slow;

	चयन (cmd) अणु
	हाल SIOCINQ:
		अगर (sk->sk_state == TCP_LISTEN)
			वापस -EINVAL;

		slow = lock_sock_fast(sk);
		answ = tcp_inq(sk);
		unlock_sock_fast(sk, slow);
		अवरोध;
	हाल SIOCATMARK:
		answ = tp->urg_data &&
		       READ_ONCE(tp->urg_seq) == READ_ONCE(tp->copied_seq);
		अवरोध;
	हाल SIOCOUTQ:
		अगर (sk->sk_state == TCP_LISTEN)
			वापस -EINVAL;

		अगर ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV))
			answ = 0;
		अन्यथा
			answ = READ_ONCE(tp->ग_लिखो_seq) - tp->snd_una;
		अवरोध;
	हाल SIOCOUTQNSD:
		अगर (sk->sk_state == TCP_LISTEN)
			वापस -EINVAL;

		अगर ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV))
			answ = 0;
		अन्यथा
			answ = READ_ONCE(tp->ग_लिखो_seq) -
			       READ_ONCE(tp->snd_nxt);
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस put_user(answ, (पूर्णांक __user *)arg);
पूर्ण
EXPORT_SYMBOL(tcp_ioctl);

अटल अंतरभूत व्योम tcp_mark_push(काष्ठा tcp_sock *tp, काष्ठा sk_buff *skb)
अणु
	TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_PSH;
	tp->pushed_seq = tp->ग_लिखो_seq;
पूर्ण

अटल अंतरभूत bool क्रमced_push(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस after(tp->ग_लिखो_seq, tp->pushed_seq + (tp->max_winकरोw >> 1));
पूर्ण

अटल व्योम skb_entail(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_skb_cb *tcb = TCP_SKB_CB(skb);

	skb->csum    = 0;
	tcb->seq     = tcb->end_seq = tp->ग_लिखो_seq;
	tcb->tcp_flags = TCPHDR_ACK;
	tcb->sacked  = 0;
	__skb_header_release(skb);
	tcp_add_ग_लिखो_queue_tail(sk, skb);
	sk_wmem_queued_add(sk, skb->truesize);
	sk_mem_अक्षरge(sk, skb->truesize);
	अगर (tp->nonagle & TCP_NAGLE_PUSH)
		tp->nonagle &= ~TCP_NAGLE_PUSH;

	tcp_slow_start_after_idle_check(sk);
पूर्ण

अटल अंतरभूत व्योम tcp_mark_urg(काष्ठा tcp_sock *tp, पूर्णांक flags)
अणु
	अगर (flags & MSG_OOB)
		tp->snd_up = tp->ग_लिखो_seq;
पूर्ण

/* If a not yet filled skb is pushed, करो not send it अगर
 * we have data packets in Qdisc or NIC queues :
 * Because TX completion will happen लघुly, it gives a chance
 * to coalesce future sendmsg() payload पूर्णांकo this skb, without
 * need क्रम a समयr, and with no latency trade off.
 * As packets containing data payload have a bigger truesize
 * than pure acks (dataless) packets, the last checks prevent
 * स्वतःcorking अगर we only have an ACK in Qdisc/NIC queues,
 * or अगर TX completion was delayed after we processed ACK packet.
 */
अटल bool tcp_should_स्वतःcork(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				पूर्णांक size_goal)
अणु
	वापस skb->len < size_goal &&
	       sock_net(sk)->ipv4.sysctl_tcp_स्वतःcorking &&
	       !tcp_rtx_queue_empty(sk) &&
	       refcount_पढ़ो(&sk->sk_wmem_alloc) > skb->truesize;
पूर्ण

व्योम tcp_push(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक mss_now,
	      पूर्णांक nonagle, पूर्णांक size_goal)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *skb;

	skb = tcp_ग_लिखो_queue_tail(sk);
	अगर (!skb)
		वापस;
	अगर (!(flags & MSG_MORE) || क्रमced_push(tp))
		tcp_mark_push(tp, skb);

	tcp_mark_urg(tp, flags);

	अगर (tcp_should_स्वतःcork(sk, skb, size_goal)) अणु

		/* aव्योम atomic op अगर TSQ_THROTTLED bit is alपढ़ोy set */
		अगर (!test_bit(TSQ_THROTTLED, &sk->sk_tsq_flags)) अणु
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPAUTOCORKING);
			set_bit(TSQ_THROTTLED, &sk->sk_tsq_flags);
		पूर्ण
		/* It is possible TX completion alपढ़ोy happened
		 * beक्रमe we set TSQ_THROTTLED.
		 */
		अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) > skb->truesize)
			वापस;
	पूर्ण

	अगर (flags & MSG_MORE)
		nonagle = TCP_NAGLE_CORK;

	__tcp_push_pending_frames(sk, mss_now, nonagle);
पूर्ण

अटल पूर्णांक tcp_splice_data_recv(पढ़ो_descriptor_t *rd_desc, काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक offset, माप_प्रकार len)
अणु
	काष्ठा tcp_splice_state *tss = rd_desc->arg.data;
	पूर्णांक ret;

	ret = skb_splice_bits(skb, skb->sk, offset, tss->pipe,
			      min(rd_desc->count, len), tss->flags);
	अगर (ret > 0)
		rd_desc->count -= ret;
	वापस ret;
पूर्ण

अटल पूर्णांक __tcp_splice_पढ़ो(काष्ठा sock *sk, काष्ठा tcp_splice_state *tss)
अणु
	/* Store TCP splice context inक्रमmation in पढ़ो_descriptor_t. */
	पढ़ो_descriptor_t rd_desc = अणु
		.arg.data = tss,
		.count	  = tss->len,
	पूर्ण;

	वापस tcp_पढ़ो_sock(sk, &rd_desc, tcp_splice_data_recv);
पूर्ण

/**
 *  tcp_splice_पढ़ो - splice data from TCP socket to a pipe
 * @sock:	socket to splice from
 * @ppos:	position (not valid)
 * @pipe:	pipe to splice to
 * @len:	number of bytes to splice
 * @flags:	splice modअगरier flags
 *
 * Description:
 *    Will पढ़ो pages from given socket and fill them पूर्णांकo a pipe.
 *
 **/
sमाप_प्रकार tcp_splice_पढ़ो(काष्ठा socket *sock, loff_t *ppos,
			काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tcp_splice_state tss = अणु
		.pipe = pipe,
		.len = len,
		.flags = flags,
	पूर्ण;
	दीर्घ समयo;
	sमाप_प्रकार spliced;
	पूर्णांक ret;

	sock_rps_record_flow(sk);
	/*
	 * We can't seek on a socket input
	 */
	अगर (unlikely(*ppos))
		वापस -ESPIPE;

	ret = spliced = 0;

	lock_sock(sk);

	समयo = sock_rcvसमयo(sk, sock->file->f_flags & O_NONBLOCK);
	जबतक (tss.len) अणु
		ret = __tcp_splice_पढ़ो(sk, &tss);
		अगर (ret < 0)
			अवरोध;
		अन्यथा अगर (!ret) अणु
			अगर (spliced)
				अवरोध;
			अगर (sock_flag(sk, SOCK_DONE))
				अवरोध;
			अगर (sk->sk_err) अणु
				ret = sock_error(sk);
				अवरोध;
			पूर्ण
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				अवरोध;
			अगर (sk->sk_state == TCP_CLOSE) अणु
				/*
				 * This occurs when user tries to पढ़ो
				 * from never connected socket.
				 */
				ret = -ENOTCONN;
				अवरोध;
			पूर्ण
			अगर (!समयo) अणु
				ret = -EAGAIN;
				अवरोध;
			पूर्ण
			/* अगर __tcp_splice_पढ़ो() got nothing जबतक we have
			 * an skb in receive queue, we करो not want to loop.
			 * This might happen with URG data.
			 */
			अगर (!skb_queue_empty(&sk->sk_receive_queue))
				अवरोध;
			sk_रुको_data(sk, &समयo, शून्य);
			अगर (संकेत_pending(current)) अणु
				ret = sock_पूर्णांकr_त्रुटि_सं(समयo);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		tss.len -= ret;
		spliced += ret;

		अगर (!समयo)
			अवरोध;
		release_sock(sk);
		lock_sock(sk);

		अगर (sk->sk_err || sk->sk_state == TCP_CLOSE ||
		    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
		    संकेत_pending(current))
			अवरोध;
	पूर्ण

	release_sock(sk);

	अगर (spliced)
		वापस spliced;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcp_splice_पढ़ो);

काष्ठा sk_buff *sk_stream_alloc_skb(काष्ठा sock *sk, पूर्णांक size, gfp_t gfp,
				    bool क्रमce_schedule)
अणु
	काष्ठा sk_buff *skb;

	अगर (likely(!size)) अणु
		skb = sk->sk_tx_skb_cache;
		अगर (skb) अणु
			skb->truesize = SKB_TRUESIZE(skb_end_offset(skb));
			sk->sk_tx_skb_cache = शून्य;
			pskb_trim(skb, 0);
			INIT_LIST_HEAD(&skb->tcp_tsorted_anchor);
			skb_shinfo(skb)->tx_flags = 0;
			स_रखो(TCP_SKB_CB(skb), 0, माप(काष्ठा tcp_skb_cb));
			वापस skb;
		पूर्ण
	पूर्ण
	/* The TCP header must be at least 32-bit aligned.  */
	size = ALIGN(size, 4);

	अगर (unlikely(tcp_under_memory_pressure(sk)))
		sk_mem_reclaim_partial(sk);

	skb = alloc_skb_fclone(size + sk->sk_prot->max_header, gfp);
	अगर (likely(skb)) अणु
		bool mem_scheduled;

		अगर (क्रमce_schedule) अणु
			mem_scheduled = true;
			sk_क्रमced_mem_schedule(sk, skb->truesize);
		पूर्ण अन्यथा अणु
			mem_scheduled = sk_wmem_schedule(sk, skb->truesize);
		पूर्ण
		अगर (likely(mem_scheduled)) अणु
			skb_reserve(skb, sk->sk_prot->max_header);
			/*
			 * Make sure that we have exactly size bytes
			 * available to the caller, no more, no less.
			 */
			skb->reserved_tailroom = skb->end - skb->tail - size;
			INIT_LIST_HEAD(&skb->tcp_tsorted_anchor);
			वापस skb;
		पूर्ण
		__kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		sk->sk_prot->enter_memory_pressure(sk);
		sk_stream_moderate_sndbuf(sk);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक tcp_xmit_size_goal(काष्ठा sock *sk, u32 mss_now,
				       पूर्णांक large_allowed)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 new_size_goal, size_goal;

	अगर (!large_allowed)
		वापस mss_now;

	/* Note : tcp_tso_स्वतःsize() will eventually split this later */
	new_size_goal = sk->sk_gso_max_size - 1 - MAX_TCP_HEADER;
	new_size_goal = tcp_bound_to_half_wnd(tp, new_size_goal);

	/* We try hard to aव्योम भागides here */
	size_goal = tp->gso_segs * mss_now;
	अगर (unlikely(new_size_goal < size_goal ||
		     new_size_goal >= size_goal + mss_now)) अणु
		tp->gso_segs = min_t(u16, new_size_goal / mss_now,
				     sk->sk_gso_max_segs);
		size_goal = tp->gso_segs * mss_now;
	पूर्ण

	वापस max(size_goal, mss_now);
पूर्ण

पूर्णांक tcp_send_mss(काष्ठा sock *sk, पूर्णांक *size_goal, पूर्णांक flags)
अणु
	पूर्णांक mss_now;

	mss_now = tcp_current_mss(sk);
	*size_goal = tcp_xmit_size_goal(sk, mss_now, !(flags & MSG_OOB));

	वापस mss_now;
पूर्ण

/* In some हालs, both sendpage() and sendmsg() could have added
 * an skb to the ग_लिखो queue, but failed adding payload on it.
 * We need to हटाओ it to consume less memory, but more
 * importantly be able to generate EPOLLOUT क्रम Edge Trigger epoll()
 * users.
 */
व्योम tcp_हटाओ_empty_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (skb && !skb->len) अणु
		tcp_unlink_ग_लिखो_queue(skb, sk);
		अगर (tcp_ग_लिखो_queue_empty(sk))
			tcp_chrono_stop(sk, TCP_CHRONO_BUSY);
		sk_wmem_मुक्त_skb(sk, skb);
	पूर्ण
पूर्ण

काष्ठा sk_buff *tcp_build_frag(काष्ठा sock *sk, पूर्णांक size_goal, पूर्णांक flags,
			       काष्ठा page *page, पूर्णांक offset, माप_प्रकार *size)
अणु
	काष्ठा sk_buff *skb = tcp_ग_लिखो_queue_tail(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	bool can_coalesce;
	पूर्णांक copy, i;

	अगर (!skb || (copy = size_goal - skb->len) <= 0 ||
	    !tcp_skb_can_collapse_to(skb)) अणु
new_segment:
		अगर (!sk_stream_memory_मुक्त(sk))
			वापस शून्य;

		skb = sk_stream_alloc_skb(sk, 0, sk->sk_allocation,
					  tcp_rtx_and_ग_लिखो_queues_empty(sk));
		अगर (!skb)
			वापस शून्य;

#अगर_घोषित CONFIG_TLS_DEVICE
		skb->decrypted = !!(flags & MSG_SENDPAGE_DECRYPTED);
#पूर्ण_अगर
		skb_entail(sk, skb);
		copy = size_goal;
	पूर्ण

	अगर (copy > *size)
		copy = *size;

	i = skb_shinfo(skb)->nr_frags;
	can_coalesce = skb_can_coalesce(skb, i, page, offset);
	अगर (!can_coalesce && i >= sysctl_max_skb_frags) अणु
		tcp_mark_push(tp, skb);
		जाओ new_segment;
	पूर्ण
	अगर (!sk_wmem_schedule(sk, copy))
		वापस शून्य;

	अगर (can_coalesce) अणु
		skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], copy);
	पूर्ण अन्यथा अणु
		get_page(page);
		skb_fill_page_desc(skb, i, page, offset, copy);
	पूर्ण

	अगर (!(flags & MSG_NO_SHARED_FRAGS))
		skb_shinfo(skb)->flags |= SKBFL_SHARED_FRAG;

	skb->len += copy;
	skb->data_len += copy;
	skb->truesize += copy;
	sk_wmem_queued_add(sk, copy);
	sk_mem_अक्षरge(sk, copy);
	skb->ip_summed = CHECKSUM_PARTIAL;
	WRITE_ONCE(tp->ग_लिखो_seq, tp->ग_लिखो_seq + copy);
	TCP_SKB_CB(skb)->end_seq += copy;
	tcp_skb_pcount_set(skb, 0);

	*size = copy;
	वापस skb;
पूर्ण

sमाप_प्रकार करो_tcp_sendpages(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			 माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक mss_now, size_goal;
	पूर्णांक err;
	sमाप_प्रकार copied;
	दीर्घ समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);

	अगर (IS_ENABLED(CONFIG_DEBUG_VM) &&
	    WARN_ONCE(!sendpage_ok(page),
		      "page must not be a Slab one and have page_count > 0"))
		वापस -EINVAL;

	/* Wait क्रम a connection to finish. One exception is TCP Fast Open
	 * (passive side) where data is allowed to be sent beक्रमe a connection
	 * is fully established.
	 */
	अगर (((1 << sk->sk_state) & ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) &&
	    !tcp_passive_fastखोलो(sk)) अणु
		err = sk_stream_रुको_connect(sk, &समयo);
		अगर (err != 0)
			जाओ out_err;
	पूर्ण

	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	mss_now = tcp_send_mss(sk, &size_goal, flags);
	copied = 0;

	err = -EPIPE;
	अगर (sk->sk_err || (sk->sk_shutकरोwn & SEND_SHUTDOWN))
		जाओ out_err;

	जबतक (size > 0) अणु
		काष्ठा sk_buff *skb;
		माप_प्रकार copy = size;

		skb = tcp_build_frag(sk, size_goal, flags, page, offset, &copy);
		अगर (!skb)
			जाओ रुको_क्रम_space;

		अगर (!copied)
			TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_PSH;

		copied += copy;
		offset += copy;
		size -= copy;
		अगर (!size)
			जाओ out;

		अगर (skb->len < size_goal || (flags & MSG_OOB))
			जारी;

		अगर (क्रमced_push(tp)) अणु
			tcp_mark_push(tp, skb);
			__tcp_push_pending_frames(sk, mss_now, TCP_NAGLE_PUSH);
		पूर्ण अन्यथा अगर (skb == tcp_send_head(sk))
			tcp_push_one(sk, mss_now);
		जारी;

रुको_क्रम_space:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		tcp_push(sk, flags & ~MSG_MORE, mss_now,
			 TCP_NAGLE_PUSH, size_goal);

		err = sk_stream_रुको_memory(sk, &समयo);
		अगर (err != 0)
			जाओ करो_error;

		mss_now = tcp_send_mss(sk, &size_goal, flags);
	पूर्ण

out:
	अगर (copied) अणु
		tcp_tx_बारtamp(sk, sk->sk_tsflags);
		अगर (!(flags & MSG_SENDPAGE_NOTLAST))
			tcp_push(sk, flags, mss_now, tp->nonagle, size_goal);
	पूर्ण
	वापस copied;

करो_error:
	tcp_हटाओ_empty_skb(sk, tcp_ग_लिखो_queue_tail(sk));
	अगर (copied)
		जाओ out;
out_err:
	/* make sure we wake any epoll edge trigger रुकोer */
	अगर (unlikely(tcp_rtx_and_ग_लिखो_queues_empty(sk) && err == -EAGAIN)) अणु
		sk->sk_ग_लिखो_space(sk);
		tcp_chrono_stop(sk, TCP_CHRONO_SNDBUF_LIMITED);
	पूर्ण
	वापस sk_stream_error(sk, flags, err);
पूर्ण
EXPORT_SYMBOL_GPL(करो_tcp_sendpages);

पूर्णांक tcp_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (!(sk->sk_route_caps & NETIF_F_SG))
		वापस sock_no_sendpage_locked(sk, page, offset, size, flags);

	tcp_rate_check_app_limited(sk);  /* is sending application-limited? */

	वापस करो_tcp_sendpages(sk, page, offset, size, flags);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_sendpage_locked);

पूर्णांक tcp_sendpage(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
		 माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक ret;

	lock_sock(sk);
	ret = tcp_sendpage_locked(sk, page, offset, size, flags);
	release_sock(sk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcp_sendpage);

व्योम tcp_मुक्त_fastखोलो_req(काष्ठा tcp_sock *tp)
अणु
	अगर (tp->fastखोलो_req) अणु
		kमुक्त(tp->fastखोलो_req);
		tp->fastखोलो_req = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tcp_sendmsg_fastखोलो(काष्ठा sock *sk, काष्ठा msghdr *msg,
				पूर्णांक *copied, माप_प्रकार size,
				काष्ठा ubuf_info *uarg)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा sockaddr *uaddr = msg->msg_name;
	पूर्णांक err, flags;

	अगर (!(sock_net(sk)->ipv4.sysctl_tcp_fastखोलो & TFO_CLIENT_ENABLE) ||
	    (uaddr && msg->msg_namelen >= माप(uaddr->sa_family) &&
	     uaddr->sa_family == AF_UNSPEC))
		वापस -EOPNOTSUPP;
	अगर (tp->fastखोलो_req)
		वापस -EALREADY; /* Another Fast Open is in progress */

	tp->fastखोलो_req = kzalloc(माप(काष्ठा tcp_fastखोलो_request),
				   sk->sk_allocation);
	अगर (unlikely(!tp->fastखोलो_req))
		वापस -ENOBUFS;
	tp->fastखोलो_req->data = msg;
	tp->fastखोलो_req->size = size;
	tp->fastखोलो_req->uarg = uarg;

	अगर (inet->defer_connect) अणु
		err = tcp_connect(sk);
		/* Same failure procedure as in tcp_v4/6_connect */
		अगर (err) अणु
			tcp_set_state(sk, TCP_CLOSE);
			inet->inet_dport = 0;
			sk->sk_route_caps = 0;
		पूर्ण
	पूर्ण
	flags = (msg->msg_flags & MSG_DONTWAIT) ? O_NONBLOCK : 0;
	err = __inet_stream_connect(sk->sk_socket, uaddr,
				    msg->msg_namelen, flags, 1);
	/* fastखोलो_req could alपढ़ोy be मुक्तd in __inet_stream_connect
	 * अगर the connection बार out or माला_लो rst
	 */
	अगर (tp->fastखोलो_req) अणु
		*copied = tp->fastखोलो_req->copied;
		tcp_मुक्त_fastखोलो_req(tp);
		inet->defer_connect = 0;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक tcp_sendmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा ubuf_info *uarg = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा sockcm_cookie sockc;
	पूर्णांक flags, err, copied = 0;
	पूर्णांक mss_now = 0, size_goal, copied_syn = 0;
	पूर्णांक process_backlog = 0;
	bool zc = false;
	दीर्घ समयo;

	flags = msg->msg_flags;

	अगर (flags & MSG_ZEROCOPY && size && sock_flag(sk, SOCK_ZEROCOPY)) अणु
		skb = tcp_ग_लिखो_queue_tail(sk);
		uarg = msg_zerocopy_पुनः_स्मृति(sk, size, skb_zcopy(skb));
		अगर (!uarg) अणु
			err = -ENOBUFS;
			जाओ out_err;
		पूर्ण

		zc = sk->sk_route_caps & NETIF_F_SG;
		अगर (!zc)
			uarg->zerocopy = 0;
	पूर्ण

	अगर (unlikely(flags & MSG_FASTOPEN || inet_sk(sk)->defer_connect) &&
	    !tp->repair) अणु
		err = tcp_sendmsg_fastखोलो(sk, msg, &copied_syn, size, uarg);
		अगर (err == -EINPROGRESS && copied_syn > 0)
			जाओ out;
		अन्यथा अगर (err)
			जाओ out_err;
	पूर्ण

	समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);

	tcp_rate_check_app_limited(sk);  /* is sending application-limited? */

	/* Wait क्रम a connection to finish. One exception is TCP Fast Open
	 * (passive side) where data is allowed to be sent beक्रमe a connection
	 * is fully established.
	 */
	अगर (((1 << sk->sk_state) & ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) &&
	    !tcp_passive_fastखोलो(sk)) अणु
		err = sk_stream_रुको_connect(sk, &समयo);
		अगर (err != 0)
			जाओ करो_error;
	पूर्ण

	अगर (unlikely(tp->repair)) अणु
		अगर (tp->repair_queue == TCP_RECV_QUEUE) अणु
			copied = tcp_send_rcvq(sk, msg, size);
			जाओ out_nopush;
		पूर्ण

		err = -EINVAL;
		अगर (tp->repair_queue == TCP_NO_QUEUE)
			जाओ out_err;

		/* 'common' sending to sendq */
	पूर्ण

	sockcm_init(&sockc, sk);
	अगर (msg->msg_controllen) अणु
		err = sock_cmsg_send(sk, msg, &sockc);
		अगर (unlikely(err)) अणु
			err = -EINVAL;
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* This should be in poll */
	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	/* Ok commence sending. */
	copied = 0;

restart:
	mss_now = tcp_send_mss(sk, &size_goal, flags);

	err = -EPIPE;
	अगर (sk->sk_err || (sk->sk_shutकरोwn & SEND_SHUTDOWN))
		जाओ करो_error;

	जबतक (msg_data_left(msg)) अणु
		पूर्णांक copy = 0;

		skb = tcp_ग_लिखो_queue_tail(sk);
		अगर (skb)
			copy = size_goal - skb->len;

		अगर (copy <= 0 || !tcp_skb_can_collapse_to(skb)) अणु
			bool first_skb;

new_segment:
			अगर (!sk_stream_memory_मुक्त(sk))
				जाओ रुको_क्रम_space;

			अगर (unlikely(process_backlog >= 16)) अणु
				process_backlog = 0;
				अगर (sk_flush_backlog(sk))
					जाओ restart;
			पूर्ण
			first_skb = tcp_rtx_and_ग_लिखो_queues_empty(sk);
			skb = sk_stream_alloc_skb(sk, 0, sk->sk_allocation,
						  first_skb);
			अगर (!skb)
				जाओ रुको_क्रम_space;

			process_backlog++;
			skb->ip_summed = CHECKSUM_PARTIAL;

			skb_entail(sk, skb);
			copy = size_goal;

			/* All packets are restored as अगर they have
			 * alपढ़ोy been sent. skb_mstamp_ns isn't set to
			 * aव्योम wrong rtt estimation.
			 */
			अगर (tp->repair)
				TCP_SKB_CB(skb)->sacked |= TCPCB_REPAIRED;
		पूर्ण

		/* Try to append data to the end of skb. */
		अगर (copy > msg_data_left(msg))
			copy = msg_data_left(msg);

		/* Where to copy to? */
		अगर (skb_availroom(skb) > 0 && !zc) अणु
			/* We have some space in skb head. Superb! */
			copy = min_t(पूर्णांक, copy, skb_availroom(skb));
			err = skb_add_data_nocache(sk, skb, &msg->msg_iter, copy);
			अगर (err)
				जाओ करो_fault;
		पूर्ण अन्यथा अगर (!zc) अणु
			bool merge = true;
			पूर्णांक i = skb_shinfo(skb)->nr_frags;
			काष्ठा page_frag *pfrag = sk_page_frag(sk);

			अगर (!sk_page_frag_refill(sk, pfrag))
				जाओ रुको_क्रम_space;

			अगर (!skb_can_coalesce(skb, i, pfrag->page,
					      pfrag->offset)) अणु
				अगर (i >= sysctl_max_skb_frags) अणु
					tcp_mark_push(tp, skb);
					जाओ new_segment;
				पूर्ण
				merge = false;
			पूर्ण

			copy = min_t(पूर्णांक, copy, pfrag->size - pfrag->offset);

			अगर (!sk_wmem_schedule(sk, copy))
				जाओ रुको_क्रम_space;

			err = skb_copy_to_page_nocache(sk, &msg->msg_iter, skb,
						       pfrag->page,
						       pfrag->offset,
						       copy);
			अगर (err)
				जाओ करो_error;

			/* Update the skb. */
			अगर (merge) अणु
				skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], copy);
			पूर्ण अन्यथा अणु
				skb_fill_page_desc(skb, i, pfrag->page,
						   pfrag->offset, copy);
				page_ref_inc(pfrag->page);
			पूर्ण
			pfrag->offset += copy;
		पूर्ण अन्यथा अणु
			err = skb_zerocopy_iter_stream(sk, skb, msg, copy, uarg);
			अगर (err == -EMSGSIZE || err == -EEXIST) अणु
				tcp_mark_push(tp, skb);
				जाओ new_segment;
			पूर्ण
			अगर (err < 0)
				जाओ करो_error;
			copy = err;
		पूर्ण

		अगर (!copied)
			TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_PSH;

		WRITE_ONCE(tp->ग_लिखो_seq, tp->ग_लिखो_seq + copy);
		TCP_SKB_CB(skb)->end_seq += copy;
		tcp_skb_pcount_set(skb, 0);

		copied += copy;
		अगर (!msg_data_left(msg)) अणु
			अगर (unlikely(flags & MSG_EOR))
				TCP_SKB_CB(skb)->eor = 1;
			जाओ out;
		पूर्ण

		अगर (skb->len < size_goal || (flags & MSG_OOB) || unlikely(tp->repair))
			जारी;

		अगर (क्रमced_push(tp)) अणु
			tcp_mark_push(tp, skb);
			__tcp_push_pending_frames(sk, mss_now, TCP_NAGLE_PUSH);
		पूर्ण अन्यथा अगर (skb == tcp_send_head(sk))
			tcp_push_one(sk, mss_now);
		जारी;

रुको_क्रम_space:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		अगर (copied)
			tcp_push(sk, flags & ~MSG_MORE, mss_now,
				 TCP_NAGLE_PUSH, size_goal);

		err = sk_stream_रुको_memory(sk, &समयo);
		अगर (err != 0)
			जाओ करो_error;

		mss_now = tcp_send_mss(sk, &size_goal, flags);
	पूर्ण

out:
	अगर (copied) अणु
		tcp_tx_बारtamp(sk, sockc.tsflags);
		tcp_push(sk, flags, mss_now, tp->nonagle, size_goal);
	पूर्ण
out_nopush:
	net_zcopy_put(uarg);
	वापस copied + copied_syn;

करो_error:
	skb = tcp_ग_लिखो_queue_tail(sk);
करो_fault:
	tcp_हटाओ_empty_skb(sk, skb);

	अगर (copied + copied_syn)
		जाओ out;
out_err:
	net_zcopy_put_पात(uarg, true);
	err = sk_stream_error(sk, flags, err);
	/* make sure we wake any epoll edge trigger रुकोer */
	अगर (unlikely(tcp_rtx_and_ग_लिखो_queues_empty(sk) && err == -EAGAIN)) अणु
		sk->sk_ग_लिखो_space(sk);
		tcp_chrono_stop(sk, TCP_CHRONO_SNDBUF_LIMITED);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_sendmsg_locked);

पूर्णांक tcp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	पूर्णांक ret;

	lock_sock(sk);
	ret = tcp_sendmsg_locked(sk, msg, size);
	release_sock(sk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcp_sendmsg);

/*
 *	Handle पढ़ोing urgent data. BSD has very simple semantics क्रम
 *	this, no blocking and very strange errors 8)
 */

अटल पूर्णांक tcp_recv_urg(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len, पूर्णांक flags)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* No URG data to पढ़ो. */
	अगर (sock_flag(sk, SOCK_URGINLINE) || !tp->urg_data ||
	    tp->urg_data == TCP_URG_READ)
		वापस -EINVAL;	/* Yes this is right ! */

	अगर (sk->sk_state == TCP_CLOSE && !sock_flag(sk, SOCK_DONE))
		वापस -ENOTCONN;

	अगर (tp->urg_data & TCP_URG_VALID) अणु
		पूर्णांक err = 0;
		अक्षर c = tp->urg_data;

		अगर (!(flags & MSG_PEEK))
			tp->urg_data = TCP_URG_READ;

		/* Read urgent data. */
		msg->msg_flags |= MSG_OOB;

		अगर (len > 0) अणु
			अगर (!(flags & MSG_TRUNC))
				err = स_नकल_to_msg(msg, &c, 1);
			len = 1;
		पूर्ण अन्यथा
			msg->msg_flags |= MSG_TRUNC;

		वापस err ? -EFAULT : len;
	पूर्ण

	अगर (sk->sk_state == TCP_CLOSE || (sk->sk_shutकरोwn & RCV_SHUTDOWN))
		वापस 0;

	/* Fixed the recv(..., MSG_OOB) behaviour.  BSD करोcs and
	 * the available implementations agree in this हाल:
	 * this call should never block, independent of the
	 * blocking state of the socket.
	 * Mike <pall@rz.uni-karlsruhe.de>
	 */
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक tcp_peek_sndq(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक copied = 0, err = 0;

	/* XXX -- need to support SO_PEEK_OFF */

	skb_rbtree_walk(skb, &sk->tcp_rtx_queue) अणु
		err = skb_copy_datagram_msg(skb, 0, msg, skb->len);
		अगर (err)
			वापस err;
		copied += skb->len;
	पूर्ण

	skb_queue_walk(&sk->sk_ग_लिखो_queue, skb) अणु
		err = skb_copy_datagram_msg(skb, 0, msg, skb->len);
		अगर (err)
			अवरोध;

		copied += skb->len;
	पूर्ण

	वापस err ?: copied;
पूर्ण

/* Clean up the receive buffer क्रम full frames taken by the user,
 * then send an ACK अगर necessary.  COPIED is the number of bytes
 * tcp_recvmsg has given to the user so far, it speeds up the
 * calculation of whether or not we must ACK क्रम the sake of
 * a winकरोw update.
 */
व्योम tcp_cleanup_rbuf(काष्ठा sock *sk, पूर्णांक copied)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	bool समय_प्रकारo_ack = false;

	काष्ठा sk_buff *skb = skb_peek(&sk->sk_receive_queue);

	WARN(skb && !beक्रमe(tp->copied_seq, TCP_SKB_CB(skb)->end_seq),
	     "cleanup rbuf bug: copied %X seq %X rcvnxt %X\n",
	     tp->copied_seq, TCP_SKB_CB(skb)->end_seq, tp->rcv_nxt);

	अगर (inet_csk_ack_scheduled(sk)) अणु
		स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

		अगर (/* Once-per-two-segments ACK was not sent by tcp_input.c */
		    tp->rcv_nxt - tp->rcv_wup > icsk->icsk_ack.rcv_mss ||
		    /*
		     * If this पढ़ो emptied पढ़ो buffer, we send ACK, अगर
		     * connection is not bidirectional, user drained
		     * receive buffer and there was a small segment
		     * in queue.
		     */
		    (copied > 0 &&
		     ((icsk->icsk_ack.pending & ICSK_ACK_PUSHED2) ||
		      ((icsk->icsk_ack.pending & ICSK_ACK_PUSHED) &&
		       !inet_csk_in_pingpong_mode(sk))) &&
		      !atomic_पढ़ो(&sk->sk_rmem_alloc)))
			समय_प्रकारo_ack = true;
	पूर्ण

	/* We send an ACK अगर we can now advertise a non-zero winकरोw
	 * which has been उठाओd "significantly".
	 *
	 * Even अगर winकरोw उठाओd up to infinity, करो not send winकरोw खोलो ACK
	 * in states, where we will not receive more. It is useless.
	 */
	अगर (copied > 0 && !समय_प्रकारo_ack && !(sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		__u32 rcv_winकरोw_now = tcp_receive_winकरोw(tp);

		/* Optimize, __tcp_select_winकरोw() is not cheap. */
		अगर (2*rcv_winकरोw_now <= tp->winकरोw_clamp) अणु
			__u32 new_winकरोw = __tcp_select_winकरोw(sk);

			/* Send ACK now, अगर this पढ़ो मुक्तd lots of space
			 * in our buffer. Certainly, new_winकरोw is new winकरोw.
			 * We can advertise it now, अगर it is not less than current one.
			 * "Lots" means "at least twice" here.
			 */
			अगर (new_winकरोw && new_winकरोw >= 2 * rcv_winकरोw_now)
				समय_प्रकारo_ack = true;
		पूर्ण
	पूर्ण
	अगर (समय_प्रकारo_ack)
		tcp_send_ack(sk);
पूर्ण

अटल काष्ठा sk_buff *tcp_recv_skb(काष्ठा sock *sk, u32 seq, u32 *off)
अणु
	काष्ठा sk_buff *skb;
	u32 offset;

	जबतक ((skb = skb_peek(&sk->sk_receive_queue)) != शून्य) अणु
		offset = seq - TCP_SKB_CB(skb)->seq;
		अगर (unlikely(TCP_SKB_CB(skb)->tcp_flags & TCPHDR_SYN)) अणु
			pr_err_once("%s: found a SYN, please report !\n", __func__);
			offset--;
		पूर्ण
		अगर (offset < skb->len || (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)) अणु
			*off = offset;
			वापस skb;
		पूर्ण
		/* This looks weird, but this can happen अगर TCP collapsing
		 * splitted a fat GRO packet, जबतक we released socket lock
		 * in skb_splice_bits()
		 */
		sk_eat_skb(sk, skb);
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * This routine provides an alternative to tcp_recvmsg() क्रम routines
 * that would like to handle copying from skbuffs directly in 'sendfile'
 * fashion.
 * Note:
 *	- It is assumed that the socket was locked by the caller.
 *	- The routine करोes not block.
 *	- At present, there is no support क्रम पढ़ोing OOB data
 *	  or क्रम 'peeking' the socket using this routine
 *	  (although both would be easy to implement).
 */
पूर्णांक tcp_पढ़ो_sock(काष्ठा sock *sk, पढ़ो_descriptor_t *desc,
		  sk_पढ़ो_actor_t recv_actor)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 seq = tp->copied_seq;
	u32 offset;
	पूर्णांक copied = 0;

	अगर (sk->sk_state == TCP_LISTEN)
		वापस -ENOTCONN;
	जबतक ((skb = tcp_recv_skb(sk, seq, &offset)) != शून्य) अणु
		अगर (offset < skb->len) अणु
			पूर्णांक used;
			माप_प्रकार len;

			len = skb->len - offset;
			/* Stop पढ़ोing अगर we hit a patch of urgent data */
			अगर (tp->urg_data) अणु
				u32 urg_offset = tp->urg_seq - seq;
				अगर (urg_offset < len)
					len = urg_offset;
				अगर (!len)
					अवरोध;
			पूर्ण
			used = recv_actor(desc, skb, offset, len);
			अगर (used <= 0) अणु
				अगर (!copied)
					copied = used;
				अवरोध;
			पूर्ण अन्यथा अगर (used <= len) अणु
				seq += used;
				copied += used;
				offset += used;
			पूर्ण
			/* If recv_actor drops the lock (e.g. TCP splice
			 * receive) the skb poपूर्णांकer might be invalid when
			 * getting here: tcp_collapse might have deleted it
			 * जबतक aggregating skbs from the socket queue.
			 */
			skb = tcp_recv_skb(sk, seq - 1, &offset);
			अगर (!skb)
				अवरोध;
			/* TCP coalescing might have appended data to the skb.
			 * Try to splice more frags
			 */
			अगर (offset + 1 != skb->len)
				जारी;
		पूर्ण
		अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN) अणु
			sk_eat_skb(sk, skb);
			++seq;
			अवरोध;
		पूर्ण
		sk_eat_skb(sk, skb);
		अगर (!desc->count)
			अवरोध;
		WRITE_ONCE(tp->copied_seq, seq);
	पूर्ण
	WRITE_ONCE(tp->copied_seq, seq);

	tcp_rcv_space_adjust(sk);

	/* Clean up data we have पढ़ो: This will करो ACK frames. */
	अगर (copied > 0) अणु
		tcp_recv_skb(sk, seq, &offset);
		tcp_cleanup_rbuf(sk, copied);
	पूर्ण
	वापस copied;
पूर्ण
EXPORT_SYMBOL(tcp_पढ़ो_sock);

पूर्णांक tcp_peek_len(काष्ठा socket *sock)
अणु
	वापस tcp_inq(sock->sk);
पूर्ण
EXPORT_SYMBOL(tcp_peek_len);

/* Make sure sk_rcvbuf is big enough to satisfy SO_RCVLOWAT hपूर्णांक */
पूर्णांक tcp_set_rcvlowat(काष्ठा sock *sk, पूर्णांक val)
अणु
	पूर्णांक cap;

	अगर (sk->sk_userlocks & SOCK_RCVBUF_LOCK)
		cap = sk->sk_rcvbuf >> 1;
	अन्यथा
		cap = sock_net(sk)->ipv4.sysctl_tcp_rmem[2] >> 1;
	val = min(val, cap);
	WRITE_ONCE(sk->sk_rcvlowat, val ? : 1);

	/* Check अगर we need to संकेत EPOLLIN right now */
	tcp_data_पढ़ोy(sk);

	अगर (sk->sk_userlocks & SOCK_RCVBUF_LOCK)
		वापस 0;

	val <<= 1;
	अगर (val > sk->sk_rcvbuf) अणु
		WRITE_ONCE(sk->sk_rcvbuf, val);
		tcp_sk(sk)->winकरोw_clamp = tcp_win_from_space(sk, val);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_set_rcvlowat);

अटल व्योम tcp_update_recv_tstamps(काष्ठा sk_buff *skb,
				    काष्ठा scm_बारtamping_पूर्णांकernal *tss)
अणु
	अगर (skb->tstamp)
		tss->ts[0] = kसमय_प्रकारo_बारpec64(skb->tstamp);
	अन्यथा
		tss->ts[0] = (काष्ठा बारpec64) अणु0पूर्ण;

	अगर (skb_hwtstamps(skb)->hwtstamp)
		tss->ts[2] = kसमय_प्रकारo_बारpec64(skb_hwtstamps(skb)->hwtstamp);
	अन्यथा
		tss->ts[2] = (काष्ठा बारpec64) अणु0पूर्ण;
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल स्थिर काष्ठा vm_operations_काष्ठा tcp_vm_ops = अणु
पूर्ण;

पूर्णांक tcp_mmap(काष्ठा file *file, काष्ठा socket *sock,
	     काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_flags & (VM_WRITE | VM_EXEC))
		वापस -EPERM;
	vma->vm_flags &= ~(VM_MAYWRITE | VM_MAYEXEC);

	/* Inकाष्ठा vm_insert_page() to not mmap_पढ़ो_lock(mm) */
	vma->vm_flags |= VM_MIXEDMAP;

	vma->vm_ops = &tcp_vm_ops;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_mmap);

अटल skb_frag_t *skb_advance_to_frag(काष्ठा sk_buff *skb, u32 offset_skb,
				       u32 *offset_frag)
अणु
	skb_frag_t *frag;

	offset_skb -= skb_headlen(skb);
	अगर ((पूर्णांक)offset_skb < 0 || skb_has_frag_list(skb))
		वापस शून्य;

	frag = skb_shinfo(skb)->frags;
	जबतक (offset_skb) अणु
		अगर (skb_frag_size(frag) > offset_skb) अणु
			*offset_frag = offset_skb;
			वापस frag;
		पूर्ण
		offset_skb -= skb_frag_size(frag);
		++frag;
	पूर्ण
	*offset_frag = 0;
	वापस frag;
पूर्ण

अटल bool can_map_frag(स्थिर skb_frag_t *frag)
अणु
	वापस skb_frag_size(frag) == PAGE_SIZE && !skb_frag_off(frag);
पूर्ण

अटल पूर्णांक find_next_mappable_frag(स्थिर skb_frag_t *frag,
				   पूर्णांक reमुख्यing_in_skb)
अणु
	पूर्णांक offset = 0;

	अगर (likely(can_map_frag(frag)))
		वापस 0;

	जबतक (offset < reमुख्यing_in_skb && !can_map_frag(frag)) अणु
		offset += skb_frag_size(frag);
		++frag;
	पूर्ण
	वापस offset;
पूर्ण

अटल व्योम tcp_zerocopy_set_hपूर्णांक_क्रम_skb(काष्ठा sock *sk,
					  काष्ठा tcp_zerocopy_receive *zc,
					  काष्ठा sk_buff *skb, u32 offset)
अणु
	u32 frag_offset, partial_frag_reमुख्यder = 0;
	पूर्णांक mappable_offset;
	skb_frag_t *frag;

	/* worst हाल: skip to next skb. try to improve on this हाल below */
	zc->recv_skip_hपूर्णांक = skb->len - offset;

	/* Find the frag containing this offset (and how far पूर्णांकo that frag) */
	frag = skb_advance_to_frag(skb, offset, &frag_offset);
	अगर (!frag)
		वापस;

	अगर (frag_offset) अणु
		काष्ठा skb_shared_info *info = skb_shinfo(skb);

		/* We पढ़ो part of the last frag, must recvmsg() rest of skb. */
		अगर (frag == &info->frags[info->nr_frags - 1])
			वापस;

		/* Else, we must at least पढ़ो the reमुख्यder in this frag. */
		partial_frag_reमुख्यder = skb_frag_size(frag) - frag_offset;
		zc->recv_skip_hपूर्णांक -= partial_frag_reमुख्यder;
		++frag;
	पूर्ण

	/* partial_frag_reमुख्यder: If part way through a frag, must पढ़ो rest.
	 * mappable_offset: Bytes till next mappable frag, *not* counting bytes
	 * in partial_frag_reमुख्यder.
	 */
	mappable_offset = find_next_mappable_frag(frag, zc->recv_skip_hपूर्णांक);
	zc->recv_skip_hपूर्णांक = mappable_offset + partial_frag_reमुख्यder;
पूर्ण

अटल पूर्णांक tcp_recvmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			      पूर्णांक nonblock, पूर्णांक flags,
			      काष्ठा scm_बारtamping_पूर्णांकernal *tss,
			      पूर्णांक *cmsg_flags);
अटल पूर्णांक receive_fallback_to_copy(काष्ठा sock *sk,
				    काष्ठा tcp_zerocopy_receive *zc, पूर्णांक inq,
				    काष्ठा scm_बारtamping_पूर्णांकernal *tss)
अणु
	अचिन्हित दीर्घ copy_address = (अचिन्हित दीर्घ)zc->copybuf_address;
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा iovec iov;
	पूर्णांक err;

	zc->length = 0;
	zc->recv_skip_hपूर्णांक = 0;

	अगर (copy_address != zc->copybuf_address)
		वापस -EINVAL;

	err = import_single_range(READ, (व्योम __user *)copy_address,
				  inq, &iov, &msg.msg_iter);
	अगर (err)
		वापस err;

	err = tcp_recvmsg_locked(sk, &msg, inq, /*nonblock=*/1, /*flags=*/0,
				 tss, &zc->msg_flags);
	अगर (err < 0)
		वापस err;

	zc->copybuf_len = err;
	अगर (likely(zc->copybuf_len)) अणु
		काष्ठा sk_buff *skb;
		u32 offset;

		skb = tcp_recv_skb(sk, tcp_sk(sk)->copied_seq, &offset);
		अगर (skb)
			tcp_zerocopy_set_hपूर्णांक_क्रम_skb(sk, zc, skb, offset);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tcp_copy_straggler_data(काष्ठा tcp_zerocopy_receive *zc,
				   काष्ठा sk_buff *skb, u32 copylen,
				   u32 *offset, u32 *seq)
अणु
	अचिन्हित दीर्घ copy_address = (अचिन्हित दीर्घ)zc->copybuf_address;
	काष्ठा msghdr msg = अणुपूर्ण;
	काष्ठा iovec iov;
	पूर्णांक err;

	अगर (copy_address != zc->copybuf_address)
		वापस -EINVAL;

	err = import_single_range(READ, (व्योम __user *)copy_address,
				  copylen, &iov, &msg.msg_iter);
	अगर (err)
		वापस err;
	err = skb_copy_datagram_msg(skb, *offset, &msg, copylen);
	अगर (err)
		वापस err;
	zc->recv_skip_hपूर्णांक -= copylen;
	*offset += copylen;
	*seq += copylen;
	वापस (__s32)copylen;
पूर्ण

अटल पूर्णांक tcp_zc_handle_leftover(काष्ठा tcp_zerocopy_receive *zc,
				  काष्ठा sock *sk,
				  काष्ठा sk_buff *skb,
				  u32 *seq,
				  s32 copybuf_len,
				  काष्ठा scm_बारtamping_पूर्णांकernal *tss)
अणु
	u32 offset, copylen = min_t(u32, copybuf_len, zc->recv_skip_hपूर्णांक);

	अगर (!copylen)
		वापस 0;
	/* skb is null अगर inq < PAGE_SIZE. */
	अगर (skb) अणु
		offset = *seq - TCP_SKB_CB(skb)->seq;
	पूर्ण अन्यथा अणु
		skb = tcp_recv_skb(sk, *seq, &offset);
		अगर (TCP_SKB_CB(skb)->has_rxtstamp) अणु
			tcp_update_recv_tstamps(skb, tss);
			zc->msg_flags |= TCP_CMSG_TS;
		पूर्ण
	पूर्ण

	zc->copybuf_len = tcp_copy_straggler_data(zc, skb, copylen, &offset,
						  seq);
	वापस zc->copybuf_len < 0 ? 0 : copylen;
पूर्ण

अटल पूर्णांक tcp_zerocopy_vm_insert_batch_error(काष्ठा vm_area_काष्ठा *vma,
					      काष्ठा page **pending_pages,
					      अचिन्हित दीर्घ pages_reमुख्यing,
					      अचिन्हित दीर्घ *address,
					      u32 *length,
					      u32 *seq,
					      काष्ठा tcp_zerocopy_receive *zc,
					      u32 total_bytes_to_map,
					      पूर्णांक err)
अणु
	/* At least one page did not map. Try zapping अगर we skipped earlier. */
	अगर (err == -EBUSY &&
	    zc->flags & TCP_RECEIVE_ZEROCOPY_FLAG_TLB_CLEAN_HINT) अणु
		u32 maybe_zap_len;

		maybe_zap_len = total_bytes_to_map -  /* All bytes to map */
				*length + /* Mapped or pending */
				(pages_reमुख्यing * PAGE_SIZE); /* Failed map. */
		zap_page_range(vma, *address, maybe_zap_len);
		err = 0;
	पूर्ण

	अगर (!err) अणु
		अचिन्हित दीर्घ leftover_pages = pages_reमुख्यing;
		पूर्णांक bytes_mapped;

		/* We called zap_page_range, try to reinsert. */
		err = vm_insert_pages(vma, *address,
				      pending_pages,
				      &pages_reमुख्यing);
		bytes_mapped = PAGE_SIZE * (leftover_pages - pages_reमुख्यing);
		*seq += bytes_mapped;
		*address += bytes_mapped;
	पूर्ण
	अगर (err) अणु
		/* Either we were unable to zap, OR we zapped, retried an
		 * insert, and still had an issue. Either ways, pages_reमुख्यing
		 * is the number of pages we were unable to map, and we unroll
		 * some state we speculatively touched beक्रमe.
		 */
		स्थिर पूर्णांक bytes_not_mapped = PAGE_SIZE * pages_reमुख्यing;

		*length -= bytes_not_mapped;
		zc->recv_skip_hपूर्णांक += bytes_not_mapped;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक tcp_zerocopy_vm_insert_batch(काष्ठा vm_area_काष्ठा *vma,
					काष्ठा page **pages,
					अचिन्हित पूर्णांक pages_to_map,
					अचिन्हित दीर्घ *address,
					u32 *length,
					u32 *seq,
					काष्ठा tcp_zerocopy_receive *zc,
					u32 total_bytes_to_map)
अणु
	अचिन्हित दीर्घ pages_reमुख्यing = pages_to_map;
	अचिन्हित पूर्णांक pages_mapped;
	अचिन्हित पूर्णांक bytes_mapped;
	पूर्णांक err;

	err = vm_insert_pages(vma, *address, pages, &pages_reमुख्यing);
	pages_mapped = pages_to_map - (अचिन्हित पूर्णांक)pages_reमुख्यing;
	bytes_mapped = PAGE_SIZE * pages_mapped;
	/* Even अगर vm_insert_pages fails, it may have partially succeeded in
	 * mapping (some but not all of the pages).
	 */
	*seq += bytes_mapped;
	*address += bytes_mapped;

	अगर (likely(!err))
		वापस 0;

	/* Error: maybe zap and retry + rollback state क्रम failed inserts. */
	वापस tcp_zerocopy_vm_insert_batch_error(vma, pages + pages_mapped,
		pages_reमुख्यing, address, length, seq, zc, total_bytes_to_map,
		err);
पूर्ण

#घोषणा TCP_VALID_ZC_MSG_FLAGS   (TCP_CMSG_TS)
अटल व्योम tcp_recv_बारtamp(काष्ठा msghdr *msg, स्थिर काष्ठा sock *sk,
			       काष्ठा scm_बारtamping_पूर्णांकernal *tss);
अटल व्योम tcp_zc_finalize_rx_tstamp(काष्ठा sock *sk,
				      काष्ठा tcp_zerocopy_receive *zc,
				      काष्ठा scm_बारtamping_पूर्णांकernal *tss)
अणु
	अचिन्हित दीर्घ msg_control_addr;
	काष्ठा msghdr cmsg_dummy;

	msg_control_addr = (अचिन्हित दीर्घ)zc->msg_control;
	cmsg_dummy.msg_control = (व्योम *)msg_control_addr;
	cmsg_dummy.msg_controllen =
		(__kernel_माप_प्रकार)zc->msg_controllen;
	cmsg_dummy.msg_flags = in_compat_syscall()
		? MSG_CMSG_COMPAT : 0;
	cmsg_dummy.msg_control_is_user = true;
	zc->msg_flags = 0;
	अगर (zc->msg_control == msg_control_addr &&
	    zc->msg_controllen == cmsg_dummy.msg_controllen) अणु
		tcp_recv_बारtamp(&cmsg_dummy, sk, tss);
		zc->msg_control = (__u64)
			((uपूर्णांकptr_t)cmsg_dummy.msg_control);
		zc->msg_controllen =
			(__u64)cmsg_dummy.msg_controllen;
		zc->msg_flags = (__u32)cmsg_dummy.msg_flags;
	पूर्ण
पूर्ण

#घोषणा TCP_ZEROCOPY_PAGE_BATCH_SIZE 32
अटल पूर्णांक tcp_zerocopy_receive(काष्ठा sock *sk,
				काष्ठा tcp_zerocopy_receive *zc,
				काष्ठा scm_बारtamping_पूर्णांकernal *tss)
अणु
	u32 length = 0, offset, vma_len, avail_len, copylen = 0;
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)zc->address;
	काष्ठा page *pages[TCP_ZEROCOPY_PAGE_BATCH_SIZE];
	s32 copybuf_len = zc->copybuf_len;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	स्थिर skb_frag_t *frags = शून्य;
	अचिन्हित पूर्णांक pages_to_map = 0;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा sk_buff *skb = शून्य;
	u32 seq = tp->copied_seq;
	u32 total_bytes_to_map;
	पूर्णांक inq = tcp_inq(sk);
	पूर्णांक ret;

	zc->copybuf_len = 0;
	zc->msg_flags = 0;

	अगर (address & (PAGE_SIZE - 1) || address != zc->address)
		वापस -EINVAL;

	अगर (sk->sk_state == TCP_LISTEN)
		वापस -ENOTCONN;

	sock_rps_record_flow(sk);

	अगर (inq && inq <= copybuf_len)
		वापस receive_fallback_to_copy(sk, zc, inq, tss);

	अगर (inq < PAGE_SIZE) अणु
		zc->length = 0;
		zc->recv_skip_hपूर्णांक = inq;
		अगर (!inq && sock_flag(sk, SOCK_DONE))
			वापस -EIO;
		वापस 0;
	पूर्ण

	mmap_पढ़ो_lock(current->mm);

	vma = find_vma(current->mm, address);
	अगर (!vma || vma->vm_start > address || vma->vm_ops != &tcp_vm_ops) अणु
		mmap_पढ़ो_unlock(current->mm);
		वापस -EINVAL;
	पूर्ण
	vma_len = min_t(अचिन्हित दीर्घ, zc->length, vma->vm_end - address);
	avail_len = min_t(u32, vma_len, inq);
	total_bytes_to_map = avail_len & ~(PAGE_SIZE - 1);
	अगर (total_bytes_to_map) अणु
		अगर (!(zc->flags & TCP_RECEIVE_ZEROCOPY_FLAG_TLB_CLEAN_HINT))
			zap_page_range(vma, address, total_bytes_to_map);
		zc->length = total_bytes_to_map;
		zc->recv_skip_hपूर्णांक = 0;
	पूर्ण अन्यथा अणु
		zc->length = avail_len;
		zc->recv_skip_hपूर्णांक = avail_len;
	पूर्ण
	ret = 0;
	जबतक (length + PAGE_SIZE <= zc->length) अणु
		पूर्णांक mappable_offset;
		काष्ठा page *page;

		अगर (zc->recv_skip_hपूर्णांक < PAGE_SIZE) अणु
			u32 offset_frag;

			अगर (skb) अणु
				अगर (zc->recv_skip_hपूर्णांक > 0)
					अवरोध;
				skb = skb->next;
				offset = seq - TCP_SKB_CB(skb)->seq;
			पूर्ण अन्यथा अणु
				skb = tcp_recv_skb(sk, seq, &offset);
			पूर्ण

			अगर (TCP_SKB_CB(skb)->has_rxtstamp) अणु
				tcp_update_recv_tstamps(skb, tss);
				zc->msg_flags |= TCP_CMSG_TS;
			पूर्ण
			zc->recv_skip_hपूर्णांक = skb->len - offset;
			frags = skb_advance_to_frag(skb, offset, &offset_frag);
			अगर (!frags || offset_frag)
				अवरोध;
		पूर्ण

		mappable_offset = find_next_mappable_frag(frags,
							  zc->recv_skip_hपूर्णांक);
		अगर (mappable_offset) अणु
			zc->recv_skip_hपूर्णांक = mappable_offset;
			अवरोध;
		पूर्ण
		page = skb_frag_page(frags);
		prefetchw(page);
		pages[pages_to_map++] = page;
		length += PAGE_SIZE;
		zc->recv_skip_hपूर्णांक -= PAGE_SIZE;
		frags++;
		अगर (pages_to_map == TCP_ZEROCOPY_PAGE_BATCH_SIZE ||
		    zc->recv_skip_hपूर्णांक < PAGE_SIZE) अणु
			/* Either full batch, or we're about to go to next skb
			 * (and we cannot unroll failed ops across skbs).
			 */
			ret = tcp_zerocopy_vm_insert_batch(vma, pages,
							   pages_to_map,
							   &address, &length,
							   &seq, zc,
							   total_bytes_to_map);
			अगर (ret)
				जाओ out;
			pages_to_map = 0;
		पूर्ण
	पूर्ण
	अगर (pages_to_map) अणु
		ret = tcp_zerocopy_vm_insert_batch(vma, pages, pages_to_map,
						   &address, &length, &seq,
						   zc, total_bytes_to_map);
	पूर्ण
out:
	mmap_पढ़ो_unlock(current->mm);
	/* Try to copy straggler data. */
	अगर (!ret)
		copylen = tcp_zc_handle_leftover(zc, sk, skb, &seq, copybuf_len, tss);

	अगर (length + copylen) अणु
		WRITE_ONCE(tp->copied_seq, seq);
		tcp_rcv_space_adjust(sk);

		/* Clean up data we have पढ़ो: This will करो ACK frames. */
		tcp_recv_skb(sk, seq, &offset);
		tcp_cleanup_rbuf(sk, length + copylen);
		ret = 0;
		अगर (length == zc->length)
			zc->recv_skip_hपूर्णांक = 0;
	पूर्ण अन्यथा अणु
		अगर (!zc->recv_skip_hपूर्णांक && sock_flag(sk, SOCK_DONE))
			ret = -EIO;
	पूर्ण
	zc->length = length;
	वापस ret;
पूर्ण
#पूर्ण_अगर

/* Similar to __sock_recv_बारtamp, but करोes not require an skb */
अटल व्योम tcp_recv_बारtamp(काष्ठा msghdr *msg, स्थिर काष्ठा sock *sk,
			       काष्ठा scm_बारtamping_पूर्णांकernal *tss)
अणु
	पूर्णांक new_tstamp = sock_flag(sk, SOCK_TSTAMP_NEW);
	bool has_बारtamping = false;

	अगर (tss->ts[0].tv_sec || tss->ts[0].tv_nsec) अणु
		अगर (sock_flag(sk, SOCK_RCVTSTAMP)) अणु
			अगर (sock_flag(sk, SOCK_RCVTSTAMPNS)) अणु
				अगर (new_tstamp) अणु
					काष्ठा __kernel_बारpec kts = अणु
						.tv_sec = tss->ts[0].tv_sec,
						.tv_nsec = tss->ts[0].tv_nsec,
					पूर्ण;
					put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMPNS_NEW,
						 माप(kts), &kts);
				पूर्ण अन्यथा अणु
					काष्ठा __kernel_old_बारpec ts_old = अणु
						.tv_sec = tss->ts[0].tv_sec,
						.tv_nsec = tss->ts[0].tv_nsec,
					पूर्ण;
					put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMPNS_OLD,
						 माप(ts_old), &ts_old);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (new_tstamp) अणु
					काष्ठा __kernel_sock_समयval stv = अणु
						.tv_sec = tss->ts[0].tv_sec,
						.tv_usec = tss->ts[0].tv_nsec / 1000,
					पूर्ण;
					put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMP_NEW,
						 माप(stv), &stv);
				पूर्ण अन्यथा अणु
					काष्ठा __kernel_old_समयval tv = अणु
						.tv_sec = tss->ts[0].tv_sec,
						.tv_usec = tss->ts[0].tv_nsec / 1000,
					पूर्ण;
					put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMP_OLD,
						 माप(tv), &tv);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (sk->sk_tsflags & SOF_TIMESTAMPING_SOFTWARE)
			has_बारtamping = true;
		अन्यथा
			tss->ts[0] = (काष्ठा बारpec64) अणु0पूर्ण;
	पूर्ण

	अगर (tss->ts[2].tv_sec || tss->ts[2].tv_nsec) अणु
		अगर (sk->sk_tsflags & SOF_TIMESTAMPING_RAW_HARDWARE)
			has_बारtamping = true;
		अन्यथा
			tss->ts[2] = (काष्ठा बारpec64) अणु0पूर्ण;
	पूर्ण

	अगर (has_बारtamping) अणु
		tss->ts[1] = (काष्ठा बारpec64) अणु0पूर्ण;
		अगर (sock_flag(sk, SOCK_TSTAMP_NEW))
			put_cmsg_scm_बारtamping64(msg, tss);
		अन्यथा
			put_cmsg_scm_बारtamping(msg, tss);
	पूर्ण
पूर्ण

अटल पूर्णांक tcp_inq_hपूर्णांक(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	u32 copied_seq = READ_ONCE(tp->copied_seq);
	u32 rcv_nxt = READ_ONCE(tp->rcv_nxt);
	पूर्णांक inq;

	inq = rcv_nxt - copied_seq;
	अगर (unlikely(inq < 0 || copied_seq != READ_ONCE(tp->copied_seq))) अणु
		lock_sock(sk);
		inq = tp->rcv_nxt - tp->copied_seq;
		release_sock(sk);
	पूर्ण
	/* After receiving a FIN, tell the user-space to जारी पढ़ोing
	 * by वापसing a non-zero inq.
	 */
	अगर (inq == 0 && sock_flag(sk, SOCK_DONE))
		inq = 1;
	वापस inq;
पूर्ण

/*
 *	This routine copies from a sock काष्ठा पूर्णांकo the user buffer.
 *
 *	Technical note: in 2.3 we work on _locked_ socket, so that
 *	tricks with *seq access order and skb->users are not required.
 *	Probably, code can be easily improved even more.
 */

अटल पूर्णांक tcp_recvmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			      पूर्णांक nonblock, पूर्णांक flags,
			      काष्ठा scm_बारtamping_पूर्णांकernal *tss,
			      पूर्णांक *cmsg_flags)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक copied = 0;
	u32 peek_seq;
	u32 *seq;
	अचिन्हित दीर्घ used;
	पूर्णांक err;
	पूर्णांक target;		/* Read at least this many bytes */
	दीर्घ समयo;
	काष्ठा sk_buff *skb, *last;
	u32 urg_hole = 0;

	err = -ENOTCONN;
	अगर (sk->sk_state == TCP_LISTEN)
		जाओ out;

	अगर (tp->recvmsg_inq)
		*cmsg_flags = TCP_CMSG_INQ;
	समयo = sock_rcvसमयo(sk, nonblock);

	/* Urgent data needs to be handled specially. */
	अगर (flags & MSG_OOB)
		जाओ recv_urg;

	अगर (unlikely(tp->repair)) अणु
		err = -EPERM;
		अगर (!(flags & MSG_PEEK))
			जाओ out;

		अगर (tp->repair_queue == TCP_SEND_QUEUE)
			जाओ recv_sndq;

		err = -EINVAL;
		अगर (tp->repair_queue == TCP_NO_QUEUE)
			जाओ out;

		/* 'common' recv queue MSG_PEEK-ing */
	पूर्ण

	seq = &tp->copied_seq;
	अगर (flags & MSG_PEEK) अणु
		peek_seq = tp->copied_seq;
		seq = &peek_seq;
	पूर्ण

	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);

	करो अणु
		u32 offset;

		/* Are we at urgent data? Stop अगर we have पढ़ो anything or have SIGURG pending. */
		अगर (tp->urg_data && tp->urg_seq == *seq) अणु
			अगर (copied)
				अवरोध;
			अगर (संकेत_pending(current)) अणु
				copied = समयo ? sock_पूर्णांकr_त्रुटि_सं(समयo) : -EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Next get a buffer. */

		last = skb_peek_tail(&sk->sk_receive_queue);
		skb_queue_walk(&sk->sk_receive_queue, skb) अणु
			last = skb;
			/* Now that we have two receive queues this
			 * shouldn't happen.
			 */
			अगर (WARN(beक्रमe(*seq, TCP_SKB_CB(skb)->seq),
				 "TCP recvmsg seq # bug: copied %X, seq %X, rcvnxt %X, fl %X\n",
				 *seq, TCP_SKB_CB(skb)->seq, tp->rcv_nxt,
				 flags))
				अवरोध;

			offset = *seq - TCP_SKB_CB(skb)->seq;
			अगर (unlikely(TCP_SKB_CB(skb)->tcp_flags & TCPHDR_SYN)) अणु
				pr_err_once("%s: found a SYN, please report !\n", __func__);
				offset--;
			पूर्ण
			अगर (offset < skb->len)
				जाओ found_ok_skb;
			अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
				जाओ found_fin_ok;
			WARN(!(flags & MSG_PEEK),
			     "TCP recvmsg seq # bug 2: copied %X, seq %X, rcvnxt %X, fl %X\n",
			     *seq, TCP_SKB_CB(skb)->seq, tp->rcv_nxt, flags);
		पूर्ण

		/* Well, अगर we have backlog, try to process it now yet. */

		अगर (copied >= target && !READ_ONCE(sk->sk_backlog.tail))
			अवरोध;

		अगर (copied) अणु
			अगर (sk->sk_err ||
			    sk->sk_state == TCP_CLOSE ||
			    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
			    !समयo ||
			    संकेत_pending(current))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (sock_flag(sk, SOCK_DONE))
				अवरोध;

			अगर (sk->sk_err) अणु
				copied = sock_error(sk);
				अवरोध;
			पूर्ण

			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				अवरोध;

			अगर (sk->sk_state == TCP_CLOSE) अणु
				/* This occurs when user tries to पढ़ो
				 * from never connected socket.
				 */
				copied = -ENOTCONN;
				अवरोध;
			पूर्ण

			अगर (!समयo) अणु
				copied = -EAGAIN;
				अवरोध;
			पूर्ण

			अगर (संकेत_pending(current)) अणु
				copied = sock_पूर्णांकr_त्रुटि_सं(समयo);
				अवरोध;
			पूर्ण
		पूर्ण

		tcp_cleanup_rbuf(sk, copied);

		अगर (copied >= target) अणु
			/* Do not sleep, just process backlog. */
			release_sock(sk);
			lock_sock(sk);
		पूर्ण अन्यथा अणु
			sk_रुको_data(sk, &समयo, last);
		पूर्ण

		अगर ((flags & MSG_PEEK) &&
		    (peek_seq - copied - urg_hole != tp->copied_seq)) अणु
			net_dbg_ratelimited("TCP(%s:%d): Application bug, race in MSG_PEEK\n",
					    current->comm,
					    task_pid_nr(current));
			peek_seq = tp->copied_seq;
		पूर्ण
		जारी;

found_ok_skb:
		/* Ok so how much can we use? */
		used = skb->len - offset;
		अगर (len < used)
			used = len;

		/* Do we have urgent data here? */
		अगर (tp->urg_data) अणु
			u32 urg_offset = tp->urg_seq - *seq;
			अगर (urg_offset < used) अणु
				अगर (!urg_offset) अणु
					अगर (!sock_flag(sk, SOCK_URGINLINE)) अणु
						WRITE_ONCE(*seq, *seq + 1);
						urg_hole++;
						offset++;
						used--;
						अगर (!used)
							जाओ skip_copy;
					पूर्ण
				पूर्ण अन्यथा
					used = urg_offset;
			पूर्ण
		पूर्ण

		अगर (!(flags & MSG_TRUNC)) अणु
			err = skb_copy_datagram_msg(skb, offset, msg, used);
			अगर (err) अणु
				/* Exception. Bailout! */
				अगर (!copied)
					copied = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण

		WRITE_ONCE(*seq, *seq + used);
		copied += used;
		len -= used;

		tcp_rcv_space_adjust(sk);

skip_copy:
		अगर (tp->urg_data && after(tp->copied_seq, tp->urg_seq)) अणु
			tp->urg_data = 0;
			tcp_fast_path_check(sk);
		पूर्ण

		अगर (TCP_SKB_CB(skb)->has_rxtstamp) अणु
			tcp_update_recv_tstamps(skb, tss);
			*cmsg_flags |= TCP_CMSG_TS;
		पूर्ण

		अगर (used + offset < skb->len)
			जारी;

		अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
			जाओ found_fin_ok;
		अगर (!(flags & MSG_PEEK))
			sk_eat_skb(sk, skb);
		जारी;

found_fin_ok:
		/* Process the FIN. */
		WRITE_ONCE(*seq, *seq + 1);
		अगर (!(flags & MSG_PEEK))
			sk_eat_skb(sk, skb);
		अवरोध;
	पूर्ण जबतक (len > 0);

	/* According to UNIX98, msg_name/msg_namelen are ignored
	 * on connected socket. I was just happy when found this 8) --ANK
	 */

	/* Clean up data we have पढ़ो: This will करो ACK frames. */
	tcp_cleanup_rbuf(sk, copied);
	वापस copied;

out:
	वापस err;

recv_urg:
	err = tcp_recv_urg(sk, msg, len, flags);
	जाओ out;

recv_sndq:
	err = tcp_peek_sndq(sk, msg, len);
	जाओ out;
पूर्ण

पूर्णांक tcp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक nonblock,
		पूर्णांक flags, पूर्णांक *addr_len)
अणु
	पूर्णांक cmsg_flags = 0, ret, inq;
	काष्ठा scm_बारtamping_पूर्णांकernal tss;

	अगर (unlikely(flags & MSG_ERRQUEUE))
		वापस inet_recv_error(sk, msg, len, addr_len);

	अगर (sk_can_busy_loop(sk) &&
	    skb_queue_empty_lockless(&sk->sk_receive_queue) &&
	    sk->sk_state == TCP_ESTABLISHED)
		sk_busy_loop(sk, nonblock);

	lock_sock(sk);
	ret = tcp_recvmsg_locked(sk, msg, len, nonblock, flags, &tss,
				 &cmsg_flags);
	release_sock(sk);

	अगर (cmsg_flags && ret >= 0) अणु
		अगर (cmsg_flags & TCP_CMSG_TS)
			tcp_recv_बारtamp(msg, sk, &tss);
		अगर (cmsg_flags & TCP_CMSG_INQ) अणु
			inq = tcp_inq_hपूर्णांक(sk);
			put_cmsg(msg, SOL_TCP, TCP_CM_INQ, माप(inq), &inq);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tcp_recvmsg);

व्योम tcp_set_state(काष्ठा sock *sk, पूर्णांक state)
अणु
	पूर्णांक oldstate = sk->sk_state;

	/* We defined a new क्रमागत क्रम TCP states that are exported in BPF
	 * so as not क्रमce the पूर्णांकernal TCP states to be frozen. The
	 * following checks will detect अगर an पूर्णांकernal state value ever
	 * dअगरfers from the BPF value. If this ever happens, then we will
	 * need to remap the पूर्णांकernal value to the BPF value beक्रमe calling
	 * tcp_call_bpf_2arg.
	 */
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_ESTABLISHED != (पूर्णांक)TCP_ESTABLISHED);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_SYN_SENT != (पूर्णांक)TCP_SYN_SENT);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_SYN_RECV != (पूर्णांक)TCP_SYN_RECV);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_FIN_WAIT1 != (पूर्णांक)TCP_FIN_WAIT1);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_FIN_WAIT2 != (पूर्णांक)TCP_FIN_WAIT2);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_TIME_WAIT != (पूर्णांक)TCP_TIME_WAIT);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_CLOSE != (पूर्णांक)TCP_CLOSE);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_CLOSE_WAIT != (पूर्णांक)TCP_CLOSE_WAIT);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_LAST_ACK != (पूर्णांक)TCP_LAST_ACK);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_LISTEN != (पूर्णांक)TCP_LISTEN);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_CLOSING != (पूर्णांक)TCP_CLOSING);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_NEW_SYN_RECV != (पूर्णांक)TCP_NEW_SYN_RECV);
	BUILD_BUG_ON((पूर्णांक)BPF_TCP_MAX_STATES != (पूर्णांक)TCP_MAX_STATES);

	/* bpf uapi header bpf.h defines an anonymous क्रमागत with values
	 * BPF_TCP_* used by bpf programs. Currently gcc built vmlinux
	 * is able to emit this क्रमागत in DWARF due to the above BUILD_BUG_ON.
	 * But clang built vmlinux करोes not have this क्रमागत in DWARF
	 * since clang हटाओs the above code beक्रमe generating IR/debuginfo.
	 * Let us explicitly emit the type debuginfo to ensure the
	 * above-mentioned anonymous क्रमागत in the vmlinux DWARF and hence BTF
	 * regardless of which compiler is used.
	 */
	BTF_TYPE_EMIT_ENUM(BPF_TCP_ESTABLISHED);

	अगर (BPF_SOCK_OPS_TEST_FLAG(tcp_sk(sk), BPF_SOCK_OPS_STATE_CB_FLAG))
		tcp_call_bpf_2arg(sk, BPF_SOCK_OPS_STATE_CB, oldstate, state);

	चयन (state) अणु
	हाल TCP_ESTABLISHED:
		अगर (oldstate != TCP_ESTABLISHED)
			TCP_INC_STATS(sock_net(sk), TCP_MIB_CURRESTAB);
		अवरोध;

	हाल TCP_CLOSE:
		अगर (oldstate == TCP_CLOSE_WAIT || oldstate == TCP_ESTABLISHED)
			TCP_INC_STATS(sock_net(sk), TCP_MIB_ESTABRESETS);

		sk->sk_prot->unhash(sk);
		अगर (inet_csk(sk)->icsk_bind_hash &&
		    !(sk->sk_userlocks & SOCK_BINDPORT_LOCK))
			inet_put_port(sk);
		fallthrough;
	शेष:
		अगर (oldstate == TCP_ESTABLISHED)
			TCP_DEC_STATS(sock_net(sk), TCP_MIB_CURRESTAB);
	पूर्ण

	/* Change state AFTER socket is unhashed to aव्योम बंदd
	 * socket sitting in hash tables.
	 */
	inet_sk_state_store(sk, state);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_set_state);

/*
 *	State processing on a बंद. This implements the state shअगरt क्रम
 *	sending our FIN frame. Note that we only send a FIN क्रम some
 *	states. A shutकरोwn() may have alपढ़ोy sent the FIN, or we may be
 *	बंदd.
 */

अटल स्थिर अचिन्हित अक्षर new_state[16] = अणु
  /* current state:        new state:      action:	*/
  [0 /* (Invalid) */]	= TCP_CLOSE,
  [TCP_ESTABLISHED]	= TCP_FIN_WAIT1 | TCP_ACTION_FIN,
  [TCP_SYN_SENT]	= TCP_CLOSE,
  [TCP_SYN_RECV]	= TCP_FIN_WAIT1 | TCP_ACTION_FIN,
  [TCP_FIN_WAIT1]	= TCP_FIN_WAIT1,
  [TCP_FIN_WAIT2]	= TCP_FIN_WAIT2,
  [TCP_TIME_WAIT]	= TCP_CLOSE,
  [TCP_CLOSE]		= TCP_CLOSE,
  [TCP_CLOSE_WAIT]	= TCP_LAST_ACK  | TCP_ACTION_FIN,
  [TCP_LAST_ACK]	= TCP_LAST_ACK,
  [TCP_LISTEN]		= TCP_CLOSE,
  [TCP_CLOSING]		= TCP_CLOSING,
  [TCP_NEW_SYN_RECV]	= TCP_CLOSE,	/* should not happen ! */
पूर्ण;

अटल पूर्णांक tcp_बंद_state(काष्ठा sock *sk)
अणु
	पूर्णांक next = (पूर्णांक)new_state[sk->sk_state];
	पूर्णांक ns = next & TCP_STATE_MASK;

	tcp_set_state(sk, ns);

	वापस next & TCP_ACTION_FIN;
पूर्ण

/*
 *	Shutकरोwn the sending side of a connection. Much like बंद except
 *	that we करोn't receive shut करोwn or sock_set_flag(sk, SOCK_DEAD).
 */

व्योम tcp_shutकरोwn(काष्ठा sock *sk, पूर्णांक how)
अणु
	/*	We need to grab some memory, and put together a FIN,
	 *	and then put it पूर्णांकo the queue to be sent.
	 *		Tim MacKenzie(tym@dibbler.cs.monash.edu.au) 4 Dec '92.
	 */
	अगर (!(how & SEND_SHUTDOWN))
		वापस;

	/* If we've already sent a FIN, or it's a बंदd state, skip this. */
	अगर ((1 << sk->sk_state) &
	    (TCPF_ESTABLISHED | TCPF_SYN_SENT |
	     TCPF_SYN_RECV | TCPF_CLOSE_WAIT)) अणु
		/* Clear out any half completed packets.  FIN अगर needed. */
		अगर (tcp_बंद_state(sk))
			tcp_send_fin(sk);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcp_shutकरोwn);

bool tcp_check_oom(काष्ठा sock *sk, पूर्णांक shअगरt)
अणु
	bool too_many_orphans, out_of_socket_memory;

	too_many_orphans = tcp_too_many_orphans(sk, shअगरt);
	out_of_socket_memory = tcp_out_of_memory(sk);

	अगर (too_many_orphans)
		net_info_ratelimited("too many orphaned sockets\n");
	अगर (out_of_socket_memory)
		net_info_ratelimited("out of memory -- consider tuning tcp_mem\n");
	वापस too_many_orphans || out_of_socket_memory;
पूर्ण

व्योम __tcp_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक data_was_unपढ़ो = 0;
	पूर्णांक state;

	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		tcp_set_state(sk, TCP_CLOSE);

		/* Special हाल. */
		inet_csk_listen_stop(sk);

		जाओ adjudge_to_death;
	पूर्ण

	/*  We need to flush the recv. buffs.  We करो this only on the
	 *  descriptor बंद, not protocol-sourced बंदs, because the
	 *  पढ़ोer process may not have drained the data yet!
	 */
	जबतक ((skb = __skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		u32 len = TCP_SKB_CB(skb)->end_seq - TCP_SKB_CB(skb)->seq;

		अगर (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
			len--;
		data_was_unपढ़ो += len;
		__kमुक्त_skb(skb);
	पूर्ण

	sk_mem_reclaim(sk);

	/* If socket has been alपढ़ोy reset (e.g. in tcp_reset()) - समाप्त it. */
	अगर (sk->sk_state == TCP_CLOSE)
		जाओ adjudge_to_death;

	/* As outlined in RFC 2525, section 2.17, we send a RST here because
	 * data was lost. To witness the awful effects of the old behavior of
	 * always करोing a FIN, run an older 2.1.x kernel or 2.0.x, start a bulk
	 * GET in an FTP client, suspend the process, रुको क्रम the client to
	 * advertise a zero winकरोw, then समाप्त -9 the FTP client, wheee...
	 * Note: समयout is always zero in such a हाल.
	 */
	अगर (unlikely(tcp_sk(sk)->repair)) अणु
		sk->sk_prot->disconnect(sk, 0);
	पूर्ण अन्यथा अगर (data_was_unपढ़ो) अणु
		/* Unपढ़ो data was tossed, zap the connection. */
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONCLOSE);
		tcp_set_state(sk, TCP_CLOSE);
		tcp_send_active_reset(sk, sk->sk_allocation);
	पूर्ण अन्यथा अगर (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingerसमय) अणु
		/* Check zero linger _after_ checking क्रम unपढ़ो data. */
		sk->sk_prot->disconnect(sk, 0);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
	पूर्ण अन्यथा अगर (tcp_बंद_state(sk)) अणु
		/* We FIN अगर the application ate all the data beक्रमe
		 * zapping the connection.
		 */

		/* RED-PEN. Formally speaking, we have broken TCP state
		 * machine. State transitions:
		 *
		 * TCP_ESTABLISHED -> TCP_FIN_WAIT1
		 * TCP_SYN_RECV	-> TCP_FIN_WAIT1 (क्रमget it, it's impossible)
		 * TCP_CLOSE_WAIT -> TCP_LAST_ACK
		 *
		 * are legal only when FIN has been sent (i.e. in winकरोw),
		 * rather than queued out of winकरोw. Purists blame.
		 *
		 * F.e. "RFC state" is ESTABLISHED,
		 * अगर Linux state is FIN-WAIT-1, but FIN is still not sent.
		 *
		 * The visible declinations are that someबार
		 * we enter समय-रुको state, when it is not required really
		 * (harmless), करो not send active resets, when they are
		 * required by specs (TCP_ESTABLISHED, TCP_CLOSE_WAIT, when
		 * they look as CLOSING or LAST_ACK क्रम Linux)
		 * Probably, I missed some more holelets.
		 * 						--ANK
		 * XXX (TFO) - To start off we करोn't support SYN+ACK+FIN
		 * in a single packet! (May consider it later but will
		 * probably need API support or TCP_CORK SYN-ACK until
		 * data is written and socket is बंदd.)
		 */
		tcp_send_fin(sk);
	पूर्ण

	sk_stream_रुको_बंद(sk, समयout);

adjudge_to_death:
	state = sk->sk_state;
	sock_hold(sk);
	sock_orphan(sk);

	local_bh_disable();
	bh_lock_sock(sk);
	/* हटाओ backlog अगर any, without releasing ownership. */
	__release_sock(sk);

	percpu_counter_inc(sk->sk_prot->orphan_count);

	/* Have we alपढ़ोy been destroyed by a softirq or backlog? */
	अगर (state != TCP_CLOSE && sk->sk_state == TCP_CLOSE)
		जाओ out;

	/*	This is a (useful) BSD violating of the RFC. There is a
	 *	problem with TCP as specअगरied in that the other end could
	 *	keep a socket खोलो क्रमever with no application left this end.
	 *	We use a 1 minute समयout (about the same as BSD) then समाप्त
	 *	our end. If they send after that then tough - BUT: दीर्घ enough
	 *	that we won't make the old 4*rto = almost no समय - whoops
	 *	reset mistake.
	 *
	 *	Nope, it was not mistake. It is really desired behaviour
	 *	f.e. on http servers, when such sockets are useless, but
	 *	consume signअगरicant resources. Let's करो it with special
	 *	linger2	option.					--ANK
	 */

	अगर (sk->sk_state == TCP_FIN_WAIT2) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);
		अगर (tp->linger2 < 0) अणु
			tcp_set_state(sk, TCP_CLOSE);
			tcp_send_active_reset(sk, GFP_ATOMIC);
			__NET_INC_STATS(sock_net(sk),
					LINUX_MIB_TCPABORTONLINGER);
		पूर्ण अन्यथा अणु
			स्थिर पूर्णांक पंचांगo = tcp_fin_समय(sk);

			अगर (पंचांगo > TCP_TIMEWAIT_LEN) अणु
				inet_csk_reset_keepalive_समयr(sk,
						पंचांगo - TCP_TIMEWAIT_LEN);
			पूर्ण अन्यथा अणु
				tcp_समय_रुको(sk, TCP_FIN_WAIT2, पंचांगo);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (sk->sk_state != TCP_CLOSE) अणु
		sk_mem_reclaim(sk);
		अगर (tcp_check_oom(sk, 0)) अणु
			tcp_set_state(sk, TCP_CLOSE);
			tcp_send_active_reset(sk, GFP_ATOMIC);
			__NET_INC_STATS(sock_net(sk),
					LINUX_MIB_TCPABORTONMEMORY);
		पूर्ण अन्यथा अगर (!check_net(sock_net(sk))) अणु
			/* Not possible to send reset; just बंद */
			tcp_set_state(sk, TCP_CLOSE);
		पूर्ण
	पूर्ण

	अगर (sk->sk_state == TCP_CLOSE) अणु
		काष्ठा request_sock *req;

		req = rcu_dereference_रक्षित(tcp_sk(sk)->fastखोलो_rsk,
						lockdep_sock_is_held(sk));
		/* We could get here with a non-शून्य req अगर the socket is
		 * पातed (e.g., बंदd with unपढ़ो data) beक्रमe 3WHS
		 * finishes.
		 */
		अगर (req)
			reqsk_fastखोलो_हटाओ(sk, req, false);
		inet_csk_destroy_sock(sk);
	पूर्ण
	/* Otherwise, socket is reprieved until protocol बंद. */

out:
	bh_unlock_sock(sk);
	local_bh_enable();
पूर्ण

व्योम tcp_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	lock_sock(sk);
	__tcp_बंद(sk, समयout);
	release_sock(sk);
	sock_put(sk);
पूर्ण
EXPORT_SYMBOL(tcp_बंद);

/* These states need RST on ABORT according to RFC793 */

अटल अंतरभूत bool tcp_need_reset(पूर्णांक state)
अणु
	वापस (1 << state) &
	       (TCPF_ESTABLISHED | TCPF_CLOSE_WAIT | TCPF_FIN_WAIT1 |
		TCPF_FIN_WAIT2 | TCPF_SYN_RECV);
पूर्ण

अटल व्योम tcp_rtx_queue_purge(काष्ठा sock *sk)
अणु
	काष्ठा rb_node *p = rb_first(&sk->tcp_rtx_queue);

	tcp_sk(sk)->highest_sack = शून्य;
	जबतक (p) अणु
		काष्ठा sk_buff *skb = rb_to_skb(p);

		p = rb_next(p);
		/* Since we are deleting whole queue, no need to
		 * list_del(&skb->tcp_tsorted_anchor)
		 */
		tcp_rtx_queue_unlink(skb, sk);
		sk_wmem_मुक्त_skb(sk, skb);
	पूर्ण
पूर्ण

व्योम tcp_ग_लिखो_queue_purge(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;

	tcp_chrono_stop(sk, TCP_CHRONO_BUSY);
	जबतक ((skb = __skb_dequeue(&sk->sk_ग_लिखो_queue)) != शून्य) अणु
		tcp_skb_tsorted_anchor_cleanup(skb);
		sk_wmem_मुक्त_skb(sk, skb);
	पूर्ण
	tcp_rtx_queue_purge(sk);
	skb = sk->sk_tx_skb_cache;
	अगर (skb) अणु
		__kमुक्त_skb(skb);
		sk->sk_tx_skb_cache = शून्य;
	पूर्ण
	INIT_LIST_HEAD(&tcp_sk(sk)->tsorted_sent_queue);
	sk_mem_reclaim(sk);
	tcp_clear_all_retrans_hपूर्णांकs(tcp_sk(sk));
	tcp_sk(sk)->packets_out = 0;
	inet_csk(sk)->icsk_backoff = 0;
पूर्ण

पूर्णांक tcp_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक old_state = sk->sk_state;
	u32 seq;

	अगर (old_state != TCP_CLOSE)
		tcp_set_state(sk, TCP_CLOSE);

	/* ABORT function of RFC793 */
	अगर (old_state == TCP_LISTEN) अणु
		inet_csk_listen_stop(sk);
	पूर्ण अन्यथा अगर (unlikely(tp->repair)) अणु
		sk->sk_err = ECONNABORTED;
	पूर्ण अन्यथा अगर (tcp_need_reset(old_state) ||
		   (tp->snd_nxt != tp->ग_लिखो_seq &&
		    (1 << old_state) & (TCPF_CLOSING | TCPF_LAST_ACK))) अणु
		/* The last check adjusts क्रम discrepancy of Linux wrt. RFC
		 * states
		 */
		tcp_send_active_reset(sk, gfp_any());
		sk->sk_err = ECONNRESET;
	पूर्ण अन्यथा अगर (old_state == TCP_SYN_SENT)
		sk->sk_err = ECONNRESET;

	tcp_clear_xmit_समयrs(sk);
	__skb_queue_purge(&sk->sk_receive_queue);
	अगर (sk->sk_rx_skb_cache) अणु
		__kमुक्त_skb(sk->sk_rx_skb_cache);
		sk->sk_rx_skb_cache = शून्य;
	पूर्ण
	WRITE_ONCE(tp->copied_seq, tp->rcv_nxt);
	tp->urg_data = 0;
	tcp_ग_लिखो_queue_purge(sk);
	tcp_fastखोलो_active_disable_ofo_check(sk);
	skb_rbtree_purge(&tp->out_of_order_queue);

	inet->inet_dport = 0;

	अगर (!(sk->sk_userlocks & SOCK_BINDADDR_LOCK))
		inet_reset_saddr(sk);

	sk->sk_shutकरोwn = 0;
	sock_reset_flag(sk, SOCK_DONE);
	tp->srtt_us = 0;
	tp->mdev_us = jअगरfies_to_usecs(TCP_TIMEOUT_INIT);
	tp->rcv_rtt_last_tsecr = 0;

	seq = tp->ग_लिखो_seq + tp->max_winकरोw + 2;
	अगर (!seq)
		seq = 1;
	WRITE_ONCE(tp->ग_लिखो_seq, seq);

	icsk->icsk_backoff = 0;
	icsk->icsk_probes_out = 0;
	icsk->icsk_probes_tstamp = 0;
	icsk->icsk_rto = TCP_TIMEOUT_INIT;
	icsk->icsk_rto_min = TCP_RTO_MIN;
	icsk->icsk_delack_max = TCP_DELACK_MAX;
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	tp->snd_cwnd = TCP_INIT_CWND;
	tp->snd_cwnd_cnt = 0;
	tp->winकरोw_clamp = 0;
	tp->delivered = 0;
	tp->delivered_ce = 0;
	अगर (icsk->icsk_ca_ops->release)
		icsk->icsk_ca_ops->release(sk);
	स_रखो(icsk->icsk_ca_priv, 0, माप(icsk->icsk_ca_priv));
	icsk->icsk_ca_initialized = 0;
	tcp_set_ca_state(sk, TCP_CA_Open);
	tp->is_sack_reneg = 0;
	tcp_clear_retrans(tp);
	tp->total_retrans = 0;
	inet_csk_delack_init(sk);
	/* Initialize rcv_mss to TCP_MIN_MSS to aव्योम भागision by 0
	 * issue in __tcp_select_winकरोw()
	 */
	icsk->icsk_ack.rcv_mss = TCP_MIN_MSS;
	स_रखो(&tp->rx_opt, 0, माप(tp->rx_opt));
	__sk_dst_reset(sk);
	dst_release(sk->sk_rx_dst);
	sk->sk_rx_dst = शून्य;
	tcp_saved_syn_मुक्त(tp);
	tp->compressed_ack = 0;
	tp->segs_in = 0;
	tp->segs_out = 0;
	tp->bytes_sent = 0;
	tp->bytes_acked = 0;
	tp->bytes_received = 0;
	tp->bytes_retrans = 0;
	tp->data_segs_in = 0;
	tp->data_segs_out = 0;
	tp->duplicate_sack[0].start_seq = 0;
	tp->duplicate_sack[0].end_seq = 0;
	tp->dsack_dups = 0;
	tp->reord_seen = 0;
	tp->retrans_out = 0;
	tp->sacked_out = 0;
	tp->tlp_high_seq = 0;
	tp->last_oow_ack_समय = 0;
	/* There's a bubble in the pipe until at least the first ACK. */
	tp->app_limited = ~0U;
	tp->rack.mstamp = 0;
	tp->rack.advanced = 0;
	tp->rack.reo_wnd_steps = 1;
	tp->rack.last_delivered = 0;
	tp->rack.reo_wnd_persist = 0;
	tp->rack.dsack_seen = 0;
	tp->syn_data_acked = 0;
	tp->rx_opt.saw_tstamp = 0;
	tp->rx_opt.dsack = 0;
	tp->rx_opt.num_sacks = 0;
	tp->rcv_ooopack = 0;


	/* Clean up fastखोलो related fields */
	tcp_मुक्त_fastखोलो_req(tp);
	inet->defer_connect = 0;
	tp->fastखोलो_client_fail = 0;

	WARN_ON(inet->inet_num && !icsk->icsk_bind_hash);

	अगर (sk->sk_frag.page) अणु
		put_page(sk->sk_frag.page);
		sk->sk_frag.page = शून्य;
		sk->sk_frag.offset = 0;
	पूर्ण

	sk->sk_error_report(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_disconnect);

अटल अंतरभूत bool tcp_can_repair_sock(स्थिर काष्ठा sock *sk)
अणु
	वापस ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN) &&
		(sk->sk_state != TCP_LISTEN);
पूर्ण

अटल पूर्णांक tcp_repair_set_winकरोw(काष्ठा tcp_sock *tp, sockptr_t optbuf, पूर्णांक len)
अणु
	काष्ठा tcp_repair_winकरोw opt;

	अगर (!tp->repair)
		वापस -EPERM;

	अगर (len != माप(opt))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&opt, optbuf, माप(opt)))
		वापस -EFAULT;

	अगर (opt.max_winकरोw < opt.snd_wnd)
		वापस -EINVAL;

	अगर (after(opt.snd_wl1, tp->rcv_nxt + opt.rcv_wnd))
		वापस -EINVAL;

	अगर (after(opt.rcv_wup, tp->rcv_nxt))
		वापस -EINVAL;

	tp->snd_wl1	= opt.snd_wl1;
	tp->snd_wnd	= opt.snd_wnd;
	tp->max_winकरोw	= opt.max_winकरोw;

	tp->rcv_wnd	= opt.rcv_wnd;
	tp->rcv_wup	= opt.rcv_wup;

	वापस 0;
पूर्ण

अटल पूर्णांक tcp_repair_options_est(काष्ठा sock *sk, sockptr_t optbuf,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा tcp_repair_opt opt;
	माप_प्रकार offset = 0;

	जबतक (len >= माप(opt)) अणु
		अगर (copy_from_sockptr_offset(&opt, optbuf, offset, माप(opt)))
			वापस -EFAULT;

		offset += माप(opt);
		len -= माप(opt);

		चयन (opt.opt_code) अणु
		हाल TCPOPT_MSS:
			tp->rx_opt.mss_clamp = opt.opt_val;
			tcp_mtup_init(sk);
			अवरोध;
		हाल TCPOPT_WINDOW:
			अणु
				u16 snd_wscale = opt.opt_val & 0xFFFF;
				u16 rcv_wscale = opt.opt_val >> 16;

				अगर (snd_wscale > TCP_MAX_WSCALE || rcv_wscale > TCP_MAX_WSCALE)
					वापस -EFBIG;

				tp->rx_opt.snd_wscale = snd_wscale;
				tp->rx_opt.rcv_wscale = rcv_wscale;
				tp->rx_opt.wscale_ok = 1;
			पूर्ण
			अवरोध;
		हाल TCPOPT_SACK_PERM:
			अगर (opt.opt_val != 0)
				वापस -EINVAL;

			tp->rx_opt.sack_ok |= TCP_SACK_SEEN;
			अवरोध;
		हाल TCPOPT_TIMESTAMP:
			अगर (opt.opt_val != 0)
				वापस -EINVAL;

			tp->rx_opt.tstamp_ok = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_STATIC_KEY_FALSE(tcp_tx_delay_enabled);
EXPORT_SYMBOL(tcp_tx_delay_enabled);

अटल व्योम tcp_enable_tx_delay(व्योम)
अणु
	अगर (!अटल_branch_unlikely(&tcp_tx_delay_enabled)) अणु
		अटल पूर्णांक __tcp_tx_delay_enabled = 0;

		अगर (cmpxchg(&__tcp_tx_delay_enabled, 0, 1) == 0) अणु
			अटल_branch_enable(&tcp_tx_delay_enabled);
			pr_info("TCP_TX_DELAY enabled\n");
		पूर्ण
	पूर्ण
पूर्ण

/* When set indicates to always queue non-full frames.  Later the user clears
 * this option and we transmit any pending partial frames in the queue.  This is
 * meant to be used aदीर्घside sendfile() to get properly filled frames when the
 * user (क्रम example) must ग_लिखो out headers with a ग_लिखो() call first and then
 * use sendfile to send out the data parts.
 *
 * TCP_CORK can be set together with TCP_NODELAY and it is stronger than
 * TCP_NODELAY.
 */
अटल व्योम __tcp_sock_set_cork(काष्ठा sock *sk, bool on)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (on) अणु
		tp->nonagle |= TCP_NAGLE_CORK;
	पूर्ण अन्यथा अणु
		tp->nonagle &= ~TCP_NAGLE_CORK;
		अगर (tp->nonagle & TCP_NAGLE_OFF)
			tp->nonagle |= TCP_NAGLE_PUSH;
		tcp_push_pending_frames(sk);
	पूर्ण
पूर्ण

व्योम tcp_sock_set_cork(काष्ठा sock *sk, bool on)
अणु
	lock_sock(sk);
	__tcp_sock_set_cork(sk, on);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_cork);

/* TCP_NODELAY is weaker than TCP_CORK, so that this option on corked socket is
 * remembered, but it is not activated until cork is cleared.
 *
 * However, when TCP_NODELAY is set we make an explicit push, which overrides
 * even TCP_CORK क्रम currently queued segments.
 */
अटल व्योम __tcp_sock_set_nodelay(काष्ठा sock *sk, bool on)
अणु
	अगर (on) अणु
		tcp_sk(sk)->nonagle |= TCP_NAGLE_OFF|TCP_NAGLE_PUSH;
		tcp_push_pending_frames(sk);
	पूर्ण अन्यथा अणु
		tcp_sk(sk)->nonagle &= ~TCP_NAGLE_OFF;
	पूर्ण
पूर्ण

व्योम tcp_sock_set_nodelay(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	__tcp_sock_set_nodelay(sk, true);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_nodelay);

अटल व्योम __tcp_sock_set_quickack(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर (!val) अणु
		inet_csk_enter_pingpong_mode(sk);
		वापस;
	पूर्ण

	inet_csk_निकास_pingpong_mode(sk);
	अगर ((1 << sk->sk_state) & (TCPF_ESTABLISHED | TCPF_CLOSE_WAIT) &&
	    inet_csk_ack_scheduled(sk)) अणु
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_PUSHED;
		tcp_cleanup_rbuf(sk, 1);
		अगर (!(val & 1))
			inet_csk_enter_pingpong_mode(sk);
	पूर्ण
पूर्ण

व्योम tcp_sock_set_quickack(काष्ठा sock *sk, पूर्णांक val)
अणु
	lock_sock(sk);
	__tcp_sock_set_quickack(sk, val);
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_quickack);

पूर्णांक tcp_sock_set_syncnt(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर (val < 1 || val > MAX_TCP_SYNCNT)
		वापस -EINVAL;

	lock_sock(sk);
	inet_csk(sk)->icsk_syn_retries = val;
	release_sock(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_syncnt);

व्योम tcp_sock_set_user_समयout(काष्ठा sock *sk, u32 val)
अणु
	lock_sock(sk);
	inet_csk(sk)->icsk_user_समयout = val;
	release_sock(sk);
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_user_समयout);

पूर्णांक tcp_sock_set_keepidle_locked(काष्ठा sock *sk, पूर्णांक val)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (val < 1 || val > MAX_TCP_KEEPIDLE)
		वापस -EINVAL;

	tp->keepalive_समय = val * HZ;
	अगर (sock_flag(sk, SOCK_KEEPOPEN) &&
	    !((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN))) अणु
		u32 elapsed = keepalive_समय_elapsed(tp);

		अगर (tp->keepalive_समय > elapsed)
			elapsed = tp->keepalive_समय - elapsed;
		अन्यथा
			elapsed = 0;
		inet_csk_reset_keepalive_समयr(sk, elapsed);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tcp_sock_set_keepidle(काष्ठा sock *sk, पूर्णांक val)
अणु
	पूर्णांक err;

	lock_sock(sk);
	err = tcp_sock_set_keepidle_locked(sk, val);
	release_sock(sk);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_keepidle);

पूर्णांक tcp_sock_set_keepपूर्णांकvl(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर (val < 1 || val > MAX_TCP_KEEPINTVL)
		वापस -EINVAL;

	lock_sock(sk);
	tcp_sk(sk)->keepalive_पूर्णांकvl = val * HZ;
	release_sock(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_keepपूर्णांकvl);

पूर्णांक tcp_sock_set_keepcnt(काष्ठा sock *sk, पूर्णांक val)
अणु
	अगर (val < 1 || val > MAX_TCP_KEEPCNT)
		वापस -EINVAL;

	lock_sock(sk);
	tcp_sk(sk)->keepalive_probes = val;
	release_sock(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_sock_set_keepcnt);

पूर्णांक tcp_set_winकरोw_clamp(काष्ठा sock *sk, पूर्णांक val)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!val) अणु
		अगर (sk->sk_state != TCP_CLOSE)
			वापस -EINVAL;
		tp->winकरोw_clamp = 0;
	पूर्ण अन्यथा अणु
		tp->winकरोw_clamp = val < SOCK_MIN_RCVBUF / 2 ?
			SOCK_MIN_RCVBUF / 2 : val;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	Socket option code क्रम TCP.
 */
अटल पूर्णांक करो_tcp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक val;
	पूर्णांक err = 0;

	/* These are data/string values, all the others are पूर्णांकs */
	चयन (optname) अणु
	हाल TCP_CONGESTION: अणु
		अक्षर name[TCP_CA_NAME_MAX];

		अगर (optlen < 1)
			वापस -EINVAL;

		val = म_नकलन_from_sockptr(name, optval,
					min_t(दीर्घ, TCP_CA_NAME_MAX-1, optlen));
		अगर (val < 0)
			वापस -EFAULT;
		name[val] = 0;

		lock_sock(sk);
		err = tcp_set_congestion_control(sk, name, true,
						 ns_capable(sock_net(sk)->user_ns,
							    CAP_NET_ADMIN));
		release_sock(sk);
		वापस err;
	पूर्ण
	हाल TCP_ULP: अणु
		अक्षर name[TCP_ULP_NAME_MAX];

		अगर (optlen < 1)
			वापस -EINVAL;

		val = म_नकलन_from_sockptr(name, optval,
					min_t(दीर्घ, TCP_ULP_NAME_MAX - 1,
					      optlen));
		अगर (val < 0)
			वापस -EFAULT;
		name[val] = 0;

		lock_sock(sk);
		err = tcp_set_ulp(sk, name);
		release_sock(sk);
		वापस err;
	पूर्ण
	हाल TCP_FASTOPEN_KEY: अणु
		__u8 key[TCP_FASTOPEN_KEY_BUF_LENGTH];
		__u8 *backup_key = शून्य;

		/* Allow a backup key as well to facilitate key rotation
		 * First key is the active one.
		 */
		अगर (optlen != TCP_FASTOPEN_KEY_LENGTH &&
		    optlen != TCP_FASTOPEN_KEY_BUF_LENGTH)
			वापस -EINVAL;

		अगर (copy_from_sockptr(key, optval, optlen))
			वापस -EFAULT;

		अगर (optlen == TCP_FASTOPEN_KEY_BUF_LENGTH)
			backup_key = key + TCP_FASTOPEN_KEY_LENGTH;

		वापस tcp_fastखोलो_reset_cipher(net, sk, key, backup_key);
	पूर्ण
	शेष:
		/* fallthru */
		अवरोध;
	पूर्ण

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(val)))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल TCP_MAXSEG:
		/* Values greater than पूर्णांकerface MTU won't take effect. However
		 * at the poपूर्णांक when this call is करोne we typically करोn't yet
		 * know which पूर्णांकerface is going to be used
		 */
		अगर (val && (val < TCP_MIN_MSS || val > MAX_TCP_WINDOW)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		tp->rx_opt.user_mss = val;
		अवरोध;

	हाल TCP_NODELAY:
		__tcp_sock_set_nodelay(sk, val);
		अवरोध;

	हाल TCP_THIN_LINEAR_TIMEOUTS:
		अगर (val < 0 || val > 1)
			err = -EINVAL;
		अन्यथा
			tp->thin_lto = val;
		अवरोध;

	हाल TCP_THIN_DUPACK:
		अगर (val < 0 || val > 1)
			err = -EINVAL;
		अवरोध;

	हाल TCP_REPAIR:
		अगर (!tcp_can_repair_sock(sk))
			err = -EPERM;
		अन्यथा अगर (val == TCP_REPAIR_ON) अणु
			tp->repair = 1;
			sk->sk_reuse = SK_FORCE_REUSE;
			tp->repair_queue = TCP_NO_QUEUE;
		पूर्ण अन्यथा अगर (val == TCP_REPAIR_OFF) अणु
			tp->repair = 0;
			sk->sk_reuse = SK_NO_REUSE;
			tcp_send_winकरोw_probe(sk);
		पूर्ण अन्यथा अगर (val == TCP_REPAIR_OFF_NO_WP) अणु
			tp->repair = 0;
			sk->sk_reuse = SK_NO_REUSE;
		पूर्ण अन्यथा
			err = -EINVAL;

		अवरोध;

	हाल TCP_REPAIR_QUEUE:
		अगर (!tp->repair)
			err = -EPERM;
		अन्यथा अगर ((अचिन्हित पूर्णांक)val < TCP_QUEUES_NR)
			tp->repair_queue = val;
		अन्यथा
			err = -EINVAL;
		अवरोध;

	हाल TCP_QUEUE_SEQ:
		अगर (sk->sk_state != TCP_CLOSE) अणु
			err = -EPERM;
		पूर्ण अन्यथा अगर (tp->repair_queue == TCP_SEND_QUEUE) अणु
			अगर (!tcp_rtx_queue_empty(sk))
				err = -EPERM;
			अन्यथा
				WRITE_ONCE(tp->ग_लिखो_seq, val);
		पूर्ण अन्यथा अगर (tp->repair_queue == TCP_RECV_QUEUE) अणु
			अगर (tp->rcv_nxt != tp->copied_seq) अणु
				err = -EPERM;
			पूर्ण अन्यथा अणु
				WRITE_ONCE(tp->rcv_nxt, val);
				WRITE_ONCE(tp->copied_seq, val);
			पूर्ण
		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
		अवरोध;

	हाल TCP_REPAIR_OPTIONS:
		अगर (!tp->repair)
			err = -EINVAL;
		अन्यथा अगर (sk->sk_state == TCP_ESTABLISHED)
			err = tcp_repair_options_est(sk, optval, optlen);
		अन्यथा
			err = -EPERM;
		अवरोध;

	हाल TCP_CORK:
		__tcp_sock_set_cork(sk, val);
		अवरोध;

	हाल TCP_KEEPIDLE:
		err = tcp_sock_set_keepidle_locked(sk, val);
		अवरोध;
	हाल TCP_KEEPINTVL:
		अगर (val < 1 || val > MAX_TCP_KEEPINTVL)
			err = -EINVAL;
		अन्यथा
			tp->keepalive_पूर्णांकvl = val * HZ;
		अवरोध;
	हाल TCP_KEEPCNT:
		अगर (val < 1 || val > MAX_TCP_KEEPCNT)
			err = -EINVAL;
		अन्यथा
			tp->keepalive_probes = val;
		अवरोध;
	हाल TCP_SYNCNT:
		अगर (val < 1 || val > MAX_TCP_SYNCNT)
			err = -EINVAL;
		अन्यथा
			icsk->icsk_syn_retries = val;
		अवरोध;

	हाल TCP_SAVE_SYN:
		/* 0: disable, 1: enable, 2: start from ether_header */
		अगर (val < 0 || val > 2)
			err = -EINVAL;
		अन्यथा
			tp->save_syn = val;
		अवरोध;

	हाल TCP_LINGER2:
		अगर (val < 0)
			tp->linger2 = -1;
		अन्यथा अगर (val > TCP_FIN_TIMEOUT_MAX / HZ)
			tp->linger2 = TCP_FIN_TIMEOUT_MAX;
		अन्यथा
			tp->linger2 = val * HZ;
		अवरोध;

	हाल TCP_DEFER_ACCEPT:
		/* Translate value in seconds to number of retransmits */
		icsk->icsk_accept_queue.rskq_defer_accept =
			secs_to_retrans(val, TCP_TIMEOUT_INIT / HZ,
					TCP_RTO_MAX / HZ);
		अवरोध;

	हाल TCP_WINDOW_CLAMP:
		err = tcp_set_winकरोw_clamp(sk, val);
		अवरोध;

	हाल TCP_QUICKACK:
		__tcp_sock_set_quickack(sk, val);
		अवरोध;

#अगर_घोषित CONFIG_TCP_MD5SIG
	हाल TCP_MD5SIG:
	हाल TCP_MD5SIG_EXT:
		err = tp->af_specअगरic->md5_parse(sk, optname, optval, optlen);
		अवरोध;
#पूर्ण_अगर
	हाल TCP_USER_TIMEOUT:
		/* Cap the max समय in ms TCP will retry or probe the winकरोw
		 * beक्रमe giving up and पातing (ETIMEDOUT) a connection.
		 */
		अगर (val < 0)
			err = -EINVAL;
		अन्यथा
			icsk->icsk_user_समयout = val;
		अवरोध;

	हाल TCP_FASTOPEN:
		अगर (val >= 0 && ((1 << sk->sk_state) & (TCPF_CLOSE |
		    TCPF_LISTEN))) अणु
			tcp_fastखोलो_init_key_once(net);

			fastखोलो_queue_tune(sk, val);
		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
		अवरोध;
	हाल TCP_FASTOPEN_CONNECT:
		अगर (val > 1 || val < 0) अणु
			err = -EINVAL;
		पूर्ण अन्यथा अगर (net->ipv4.sysctl_tcp_fastखोलो & TFO_CLIENT_ENABLE) अणु
			अगर (sk->sk_state == TCP_CLOSE)
				tp->fastखोलो_connect = val;
			अन्यथा
				err = -EINVAL;
		पूर्ण अन्यथा अणु
			err = -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल TCP_FASTOPEN_NO_COOKIE:
		अगर (val > 1 || val < 0)
			err = -EINVAL;
		अन्यथा अगर (!((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN)))
			err = -EINVAL;
		अन्यथा
			tp->fastखोलो_no_cookie = val;
		अवरोध;
	हाल TCP_TIMESTAMP:
		अगर (!tp->repair)
			err = -EPERM;
		अन्यथा
			tp->tsoffset = val - tcp_समय_stamp_raw();
		अवरोध;
	हाल TCP_REPAIR_WINDOW:
		err = tcp_repair_set_winकरोw(tp, optval, optlen);
		अवरोध;
	हाल TCP_NOTSENT_LOWAT:
		tp->notsent_lowat = val;
		sk->sk_ग_लिखो_space(sk);
		अवरोध;
	हाल TCP_INQ:
		अगर (val > 1 || val < 0)
			err = -EINVAL;
		अन्यथा
			tp->recvmsg_inq = val;
		अवरोध;
	हाल TCP_TX_DELAY:
		अगर (val)
			tcp_enable_tx_delay();
		tp->tcp_tx_delay = val;
		अवरोध;
	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

पूर्णांक tcp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		   अचिन्हित पूर्णांक optlen)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (level != SOL_TCP)
		वापस icsk->icsk_af_ops->setsockopt(sk, level, optname,
						     optval, optlen);
	वापस करो_tcp_setsockopt(sk, level, optname, optval, optlen);
पूर्ण
EXPORT_SYMBOL(tcp_setsockopt);

अटल व्योम tcp_get_info_chrono_stats(स्थिर काष्ठा tcp_sock *tp,
				      काष्ठा tcp_info *info)
अणु
	u64 stats[__TCP_CHRONO_MAX], total = 0;
	क्रमागत tcp_chrono i;

	क्रम (i = TCP_CHRONO_BUSY; i < __TCP_CHRONO_MAX; ++i) अणु
		stats[i] = tp->chrono_stat[i - 1];
		अगर (i == tp->chrono_type)
			stats[i] += tcp_jअगरfies32 - tp->chrono_start;
		stats[i] *= USEC_PER_SEC / HZ;
		total += stats[i];
	पूर्ण

	info->tcpi_busy_समय = total;
	info->tcpi_rwnd_limited = stats[TCP_CHRONO_RWND_LIMITED];
	info->tcpi_sndbuf_limited = stats[TCP_CHRONO_SNDBUF_LIMITED];
पूर्ण

/* Return inक्रमmation about state of tcp endpoपूर्णांक in API क्रमmat. */
व्योम tcp_get_info(काष्ठा sock *sk, काष्ठा tcp_info *info)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk); /* अगरf sk_type == SOCK_STREAM */
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	अचिन्हित दीर्घ rate;
	u32 now;
	u64 rate64;
	bool slow;

	स_रखो(info, 0, माप(*info));
	अगर (sk->sk_type != SOCK_STREAM)
		वापस;

	info->tcpi_state = inet_sk_state_load(sk);

	/* Report meaningful fields क्रम all TCP states, including listeners */
	rate = READ_ONCE(sk->sk_pacing_rate);
	rate64 = (rate != ~0UL) ? rate : ~0ULL;
	info->tcpi_pacing_rate = rate64;

	rate = READ_ONCE(sk->sk_max_pacing_rate);
	rate64 = (rate != ~0UL) ? rate : ~0ULL;
	info->tcpi_max_pacing_rate = rate64;

	info->tcpi_reordering = tp->reordering;
	info->tcpi_snd_cwnd = tp->snd_cwnd;

	अगर (info->tcpi_state == TCP_LISTEN) अणु
		/* listeners aliased fields :
		 * tcpi_unacked -> Number of children पढ़ोy क्रम accept()
		 * tcpi_sacked  -> max backlog
		 */
		info->tcpi_unacked = READ_ONCE(sk->sk_ack_backlog);
		info->tcpi_sacked = READ_ONCE(sk->sk_max_ack_backlog);
		वापस;
	पूर्ण

	slow = lock_sock_fast(sk);

	info->tcpi_ca_state = icsk->icsk_ca_state;
	info->tcpi_retransmits = icsk->icsk_retransmits;
	info->tcpi_probes = icsk->icsk_probes_out;
	info->tcpi_backoff = icsk->icsk_backoff;

	अगर (tp->rx_opt.tstamp_ok)
		info->tcpi_options |= TCPI_OPT_TIMESTAMPS;
	अगर (tcp_is_sack(tp))
		info->tcpi_options |= TCPI_OPT_SACK;
	अगर (tp->rx_opt.wscale_ok) अणु
		info->tcpi_options |= TCPI_OPT_WSCALE;
		info->tcpi_snd_wscale = tp->rx_opt.snd_wscale;
		info->tcpi_rcv_wscale = tp->rx_opt.rcv_wscale;
	पूर्ण

	अगर (tp->ecn_flags & TCP_ECN_OK)
		info->tcpi_options |= TCPI_OPT_ECN;
	अगर (tp->ecn_flags & TCP_ECN_SEEN)
		info->tcpi_options |= TCPI_OPT_ECN_SEEN;
	अगर (tp->syn_data_acked)
		info->tcpi_options |= TCPI_OPT_SYN_DATA;

	info->tcpi_rto = jअगरfies_to_usecs(icsk->icsk_rto);
	info->tcpi_ato = jअगरfies_to_usecs(icsk->icsk_ack.ato);
	info->tcpi_snd_mss = tp->mss_cache;
	info->tcpi_rcv_mss = icsk->icsk_ack.rcv_mss;

	info->tcpi_unacked = tp->packets_out;
	info->tcpi_sacked = tp->sacked_out;

	info->tcpi_lost = tp->lost_out;
	info->tcpi_retrans = tp->retrans_out;

	now = tcp_jअगरfies32;
	info->tcpi_last_data_sent = jअगरfies_to_msecs(now - tp->lsndसमय);
	info->tcpi_last_data_recv = jअगरfies_to_msecs(now - icsk->icsk_ack.lrcvसमय);
	info->tcpi_last_ack_recv = jअगरfies_to_msecs(now - tp->rcv_tstamp);

	info->tcpi_pmtu = icsk->icsk_pmtu_cookie;
	info->tcpi_rcv_ssthresh = tp->rcv_ssthresh;
	info->tcpi_rtt = tp->srtt_us >> 3;
	info->tcpi_rttvar = tp->mdev_us >> 2;
	info->tcpi_snd_ssthresh = tp->snd_ssthresh;
	info->tcpi_advmss = tp->advmss;

	info->tcpi_rcv_rtt = tp->rcv_rtt_est.rtt_us >> 3;
	info->tcpi_rcv_space = tp->rcvq_space.space;

	info->tcpi_total_retrans = tp->total_retrans;

	info->tcpi_bytes_acked = tp->bytes_acked;
	info->tcpi_bytes_received = tp->bytes_received;
	info->tcpi_notsent_bytes = max_t(पूर्णांक, 0, tp->ग_लिखो_seq - tp->snd_nxt);
	tcp_get_info_chrono_stats(tp, info);

	info->tcpi_segs_out = tp->segs_out;
	info->tcpi_segs_in = tp->segs_in;

	info->tcpi_min_rtt = tcp_min_rtt(tp);
	info->tcpi_data_segs_in = tp->data_segs_in;
	info->tcpi_data_segs_out = tp->data_segs_out;

	info->tcpi_delivery_rate_app_limited = tp->rate_app_limited ? 1 : 0;
	rate64 = tcp_compute_delivery_rate(tp);
	अगर (rate64)
		info->tcpi_delivery_rate = rate64;
	info->tcpi_delivered = tp->delivered;
	info->tcpi_delivered_ce = tp->delivered_ce;
	info->tcpi_bytes_sent = tp->bytes_sent;
	info->tcpi_bytes_retrans = tp->bytes_retrans;
	info->tcpi_dsack_dups = tp->dsack_dups;
	info->tcpi_reord_seen = tp->reord_seen;
	info->tcpi_rcv_ooopack = tp->rcv_ooopack;
	info->tcpi_snd_wnd = tp->snd_wnd;
	info->tcpi_fastखोलो_client_fail = tp->fastखोलो_client_fail;
	unlock_sock_fast(sk, slow);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_get_info);

अटल माप_प्रकार tcp_opt_stats_get_size(व्योम)
अणु
	वापस
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_BUSY */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_RWND_LIMITED */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_SNDBUF_LIMITED */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_DATA_SEGS_OUT */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_TOTAL_RETRANS */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_PACING_RATE */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_DELIVERY_RATE */
		nla_total_size(माप(u32)) + /* TCP_NLA_SND_CWND */
		nla_total_size(माप(u32)) + /* TCP_NLA_REORDERING */
		nla_total_size(माप(u32)) + /* TCP_NLA_MIN_RTT */
		nla_total_size(माप(u8)) + /* TCP_NLA_RECUR_RETRANS */
		nla_total_size(माप(u8)) + /* TCP_NLA_DELIVERY_RATE_APP_LMT */
		nla_total_size(माप(u32)) + /* TCP_NLA_SNDQ_SIZE */
		nla_total_size(माप(u8)) + /* TCP_NLA_CA_STATE */
		nla_total_size(माप(u32)) + /* TCP_NLA_SND_SSTHRESH */
		nla_total_size(माप(u32)) + /* TCP_NLA_DELIVERED */
		nla_total_size(माप(u32)) + /* TCP_NLA_DELIVERED_CE */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_BYTES_SENT */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_BYTES_RETRANS */
		nla_total_size(माप(u32)) + /* TCP_NLA_DSACK_DUPS */
		nla_total_size(माप(u32)) + /* TCP_NLA_REORD_SEEN */
		nla_total_size(माप(u32)) + /* TCP_NLA_SRTT */
		nla_total_size(माप(u16)) + /* TCP_NLA_TIMEOUT_REHASH */
		nla_total_size(माप(u32)) + /* TCP_NLA_BYTES_NOTSENT */
		nla_total_size_64bit(माप(u64)) + /* TCP_NLA_EDT */
		nla_total_size(माप(u8)) + /* TCP_NLA_TTL */
		0;
पूर्ण

/* Returns TTL or hop limit of an incoming packet from skb. */
अटल u8 tcp_skb_ttl_or_hop_limit(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ip_hdr(skb)->ttl;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस ipv6_hdr(skb)->hop_limit;
	अन्यथा
		वापस 0;
पूर्ण

काष्ठा sk_buff *tcp_get_बारtamping_opt_stats(स्थिर काष्ठा sock *sk,
					       स्थिर काष्ठा sk_buff *orig_skb,
					       स्थिर काष्ठा sk_buff *ack_skb)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा sk_buff *stats;
	काष्ठा tcp_info info;
	अचिन्हित दीर्घ rate;
	u64 rate64;

	stats = alloc_skb(tcp_opt_stats_get_size(), GFP_ATOMIC);
	अगर (!stats)
		वापस शून्य;

	tcp_get_info_chrono_stats(tp, &info);
	nla_put_u64_64bit(stats, TCP_NLA_BUSY,
			  info.tcpi_busy_समय, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_RWND_LIMITED,
			  info.tcpi_rwnd_limited, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_SNDBUF_LIMITED,
			  info.tcpi_sndbuf_limited, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_DATA_SEGS_OUT,
			  tp->data_segs_out, TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_TOTAL_RETRANS,
			  tp->total_retrans, TCP_NLA_PAD);

	rate = READ_ONCE(sk->sk_pacing_rate);
	rate64 = (rate != ~0UL) ? rate : ~0ULL;
	nla_put_u64_64bit(stats, TCP_NLA_PACING_RATE, rate64, TCP_NLA_PAD);

	rate64 = tcp_compute_delivery_rate(tp);
	nla_put_u64_64bit(stats, TCP_NLA_DELIVERY_RATE, rate64, TCP_NLA_PAD);

	nla_put_u32(stats, TCP_NLA_SND_CWND, tp->snd_cwnd);
	nla_put_u32(stats, TCP_NLA_REORDERING, tp->reordering);
	nla_put_u32(stats, TCP_NLA_MIN_RTT, tcp_min_rtt(tp));

	nla_put_u8(stats, TCP_NLA_RECUR_RETRANS, inet_csk(sk)->icsk_retransmits);
	nla_put_u8(stats, TCP_NLA_DELIVERY_RATE_APP_LMT, !!tp->rate_app_limited);
	nla_put_u32(stats, TCP_NLA_SND_SSTHRESH, tp->snd_ssthresh);
	nla_put_u32(stats, TCP_NLA_DELIVERED, tp->delivered);
	nla_put_u32(stats, TCP_NLA_DELIVERED_CE, tp->delivered_ce);

	nla_put_u32(stats, TCP_NLA_SNDQ_SIZE, tp->ग_लिखो_seq - tp->snd_una);
	nla_put_u8(stats, TCP_NLA_CA_STATE, inet_csk(sk)->icsk_ca_state);

	nla_put_u64_64bit(stats, TCP_NLA_BYTES_SENT, tp->bytes_sent,
			  TCP_NLA_PAD);
	nla_put_u64_64bit(stats, TCP_NLA_BYTES_RETRANS, tp->bytes_retrans,
			  TCP_NLA_PAD);
	nla_put_u32(stats, TCP_NLA_DSACK_DUPS, tp->dsack_dups);
	nla_put_u32(stats, TCP_NLA_REORD_SEEN, tp->reord_seen);
	nla_put_u32(stats, TCP_NLA_SRTT, tp->srtt_us >> 3);
	nla_put_u16(stats, TCP_NLA_TIMEOUT_REHASH, tp->समयout_rehash);
	nla_put_u32(stats, TCP_NLA_BYTES_NOTSENT,
		    max_t(पूर्णांक, 0, tp->ग_लिखो_seq - tp->snd_nxt));
	nla_put_u64_64bit(stats, TCP_NLA_EDT, orig_skb->skb_mstamp_ns,
			  TCP_NLA_PAD);
	अगर (ack_skb)
		nla_put_u8(stats, TCP_NLA_TTL,
			   tcp_skb_ttl_or_hop_limit(ack_skb));

	वापस stats;
पूर्ण

अटल पूर्णांक करो_tcp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level,
		पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक val, len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल TCP_MAXSEG:
		val = tp->mss_cache;
		अगर (!val && ((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN)))
			val = tp->rx_opt.user_mss;
		अगर (tp->repair)
			val = tp->rx_opt.mss_clamp;
		अवरोध;
	हाल TCP_NODELAY:
		val = !!(tp->nonagle&TCP_NAGLE_OFF);
		अवरोध;
	हाल TCP_CORK:
		val = !!(tp->nonagle&TCP_NAGLE_CORK);
		अवरोध;
	हाल TCP_KEEPIDLE:
		val = keepalive_समय_when(tp) / HZ;
		अवरोध;
	हाल TCP_KEEPINTVL:
		val = keepalive_पूर्णांकvl_when(tp) / HZ;
		अवरोध;
	हाल TCP_KEEPCNT:
		val = keepalive_probes(tp);
		अवरोध;
	हाल TCP_SYNCNT:
		val = icsk->icsk_syn_retries ? : net->ipv4.sysctl_tcp_syn_retries;
		अवरोध;
	हाल TCP_LINGER2:
		val = tp->linger2;
		अगर (val >= 0)
			val = (val ? : net->ipv4.sysctl_tcp_fin_समयout) / HZ;
		अवरोध;
	हाल TCP_DEFER_ACCEPT:
		val = retrans_to_secs(icsk->icsk_accept_queue.rskq_defer_accept,
				      TCP_TIMEOUT_INIT / HZ, TCP_RTO_MAX / HZ);
		अवरोध;
	हाल TCP_WINDOW_CLAMP:
		val = tp->winकरोw_clamp;
		अवरोध;
	हाल TCP_INFO: अणु
		काष्ठा tcp_info info;

		अगर (get_user(len, optlen))
			वापस -EFAULT;

		tcp_get_info(sk, &info);

		len = min_t(अचिन्हित पूर्णांक, len, माप(info));
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &info, len))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल TCP_CC_INFO: अणु
		स्थिर काष्ठा tcp_congestion_ops *ca_ops;
		जोड़ tcp_cc_info info;
		माप_प्रकार sz = 0;
		पूर्णांक attr;

		अगर (get_user(len, optlen))
			वापस -EFAULT;

		ca_ops = icsk->icsk_ca_ops;
		अगर (ca_ops && ca_ops->get_info)
			sz = ca_ops->get_info(sk, ~0U, &attr, &info);

		len = min_t(अचिन्हित पूर्णांक, len, sz);
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, &info, len))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल TCP_QUICKACK:
		val = !inet_csk_in_pingpong_mode(sk);
		अवरोध;

	हाल TCP_CONGESTION:
		अगर (get_user(len, optlen))
			वापस -EFAULT;
		len = min_t(अचिन्हित पूर्णांक, len, TCP_CA_NAME_MAX);
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, icsk->icsk_ca_ops->name, len))
			वापस -EFAULT;
		वापस 0;

	हाल TCP_ULP:
		अगर (get_user(len, optlen))
			वापस -EFAULT;
		len = min_t(अचिन्हित पूर्णांक, len, TCP_ULP_NAME_MAX);
		अगर (!icsk->icsk_ulp_ops) अणु
			अगर (put_user(0, optlen))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, icsk->icsk_ulp_ops->name, len))
			वापस -EFAULT;
		वापस 0;

	हाल TCP_FASTOPEN_KEY: अणु
		u64 key[TCP_FASTOPEN_KEY_BUF_LENGTH / माप(u64)];
		अचिन्हित पूर्णांक key_len;

		अगर (get_user(len, optlen))
			वापस -EFAULT;

		key_len = tcp_fastखोलो_get_cipher(net, icsk, key) *
				TCP_FASTOPEN_KEY_LENGTH;
		len = min_t(अचिन्हित पूर्णांक, len, key_len);
		अगर (put_user(len, optlen))
			वापस -EFAULT;
		अगर (copy_to_user(optval, key, len))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल TCP_THIN_LINEAR_TIMEOUTS:
		val = tp->thin_lto;
		अवरोध;

	हाल TCP_THIN_DUPACK:
		val = 0;
		अवरोध;

	हाल TCP_REPAIR:
		val = tp->repair;
		अवरोध;

	हाल TCP_REPAIR_QUEUE:
		अगर (tp->repair)
			val = tp->repair_queue;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल TCP_REPAIR_WINDOW: अणु
		काष्ठा tcp_repair_winकरोw opt;

		अगर (get_user(len, optlen))
			वापस -EFAULT;

		अगर (len != माप(opt))
			वापस -EINVAL;

		अगर (!tp->repair)
			वापस -EPERM;

		opt.snd_wl1	= tp->snd_wl1;
		opt.snd_wnd	= tp->snd_wnd;
		opt.max_winकरोw	= tp->max_winकरोw;
		opt.rcv_wnd	= tp->rcv_wnd;
		opt.rcv_wup	= tp->rcv_wup;

		अगर (copy_to_user(optval, &opt, len))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल TCP_QUEUE_SEQ:
		अगर (tp->repair_queue == TCP_SEND_QUEUE)
			val = tp->ग_लिखो_seq;
		अन्यथा अगर (tp->repair_queue == TCP_RECV_QUEUE)
			val = tp->rcv_nxt;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल TCP_USER_TIMEOUT:
		val = icsk->icsk_user_समयout;
		अवरोध;

	हाल TCP_FASTOPEN:
		val = icsk->icsk_accept_queue.fastखोलोq.max_qlen;
		अवरोध;

	हाल TCP_FASTOPEN_CONNECT:
		val = tp->fastखोलो_connect;
		अवरोध;

	हाल TCP_FASTOPEN_NO_COOKIE:
		val = tp->fastखोलो_no_cookie;
		अवरोध;

	हाल TCP_TX_DELAY:
		val = tp->tcp_tx_delay;
		अवरोध;

	हाल TCP_TIMESTAMP:
		val = tcp_समय_stamp_raw() + tp->tsoffset;
		अवरोध;
	हाल TCP_NOTSENT_LOWAT:
		val = tp->notsent_lowat;
		अवरोध;
	हाल TCP_INQ:
		val = tp->recvmsg_inq;
		अवरोध;
	हाल TCP_SAVE_SYN:
		val = tp->save_syn;
		अवरोध;
	हाल TCP_SAVED_SYN: अणु
		अगर (get_user(len, optlen))
			वापस -EFAULT;

		lock_sock(sk);
		अगर (tp->saved_syn) अणु
			अगर (len < tcp_saved_syn_len(tp->saved_syn)) अणु
				अगर (put_user(tcp_saved_syn_len(tp->saved_syn),
					     optlen)) अणु
					release_sock(sk);
					वापस -EFAULT;
				पूर्ण
				release_sock(sk);
				वापस -EINVAL;
			पूर्ण
			len = tcp_saved_syn_len(tp->saved_syn);
			अगर (put_user(len, optlen)) अणु
				release_sock(sk);
				वापस -EFAULT;
			पूर्ण
			अगर (copy_to_user(optval, tp->saved_syn->data, len)) अणु
				release_sock(sk);
				वापस -EFAULT;
			पूर्ण
			tcp_saved_syn_मुक्त(tp);
			release_sock(sk);
		पूर्ण अन्यथा अणु
			release_sock(sk);
			len = 0;
			अगर (put_user(len, optlen))
				वापस -EFAULT;
		पूर्ण
		वापस 0;
	पूर्ण
#अगर_घोषित CONFIG_MMU
	हाल TCP_ZEROCOPY_RECEIVE: अणु
		काष्ठा scm_बारtamping_पूर्णांकernal tss;
		काष्ठा tcp_zerocopy_receive zc = अणुपूर्ण;
		पूर्णांक err;

		अगर (get_user(len, optlen))
			वापस -EFAULT;
		अगर (len < 0 ||
		    len < दुरत्वend(काष्ठा tcp_zerocopy_receive, length))
			वापस -EINVAL;
		अगर (unlikely(len > माप(zc))) अणु
			err = check_zeroed_user(optval + माप(zc),
						len - माप(zc));
			अगर (err < 1)
				वापस err == 0 ? -EINVAL : err;
			len = माप(zc);
			अगर (put_user(len, optlen))
				वापस -EFAULT;
		पूर्ण
		अगर (copy_from_user(&zc, optval, len))
			वापस -EFAULT;
		अगर (zc.reserved)
			वापस -EINVAL;
		अगर (zc.msg_flags &  ~(TCP_VALID_ZC_MSG_FLAGS))
			वापस -EINVAL;
		lock_sock(sk);
		err = tcp_zerocopy_receive(sk, &zc, &tss);
		err = BPF_CGROUP_RUN_PROG_GETSOCKOPT_KERN(sk, level, optname,
							  &zc, &len, err);
		release_sock(sk);
		अगर (len >= दुरत्वend(काष्ठा tcp_zerocopy_receive, msg_flags))
			जाओ zerocopy_rcv_cmsg;
		चयन (len) अणु
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, msg_flags):
			जाओ zerocopy_rcv_cmsg;
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, msg_controllen):
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, msg_control):
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, flags):
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, copybuf_len):
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, copybuf_address):
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, err):
			जाओ zerocopy_rcv_sk_err;
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, inq):
			जाओ zerocopy_rcv_inq;
		हाल दुरत्वend(काष्ठा tcp_zerocopy_receive, length):
		शेष:
			जाओ zerocopy_rcv_out;
		पूर्ण
zerocopy_rcv_cmsg:
		अगर (zc.msg_flags & TCP_CMSG_TS)
			tcp_zc_finalize_rx_tstamp(sk, &zc, &tss);
		अन्यथा
			zc.msg_flags = 0;
zerocopy_rcv_sk_err:
		अगर (!err)
			zc.err = sock_error(sk);
zerocopy_rcv_inq:
		zc.inq = tcp_inq_hपूर्णांक(sk);
zerocopy_rcv_out:
		अगर (!err && copy_to_user(optval, &zc, len))
			err = -EFAULT;
		वापस err;
	पूर्ण
#पूर्ण_अगर
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

bool tcp_bpf_bypass_माला_लोockopt(पूर्णांक level, पूर्णांक optname)
अणु
	/* TCP करो_tcp_माला_लोockopt has optimized माला_लोockopt implementation
	 * to aव्योम extra socket lock क्रम TCP_ZEROCOPY_RECEIVE.
	 */
	अगर (level == SOL_TCP && optname == TCP_ZEROCOPY_RECEIVE)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(tcp_bpf_bypass_माला_लोockopt);

पूर्णांक tcp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, अक्षर __user *optval,
		   पूर्णांक __user *optlen)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (level != SOL_TCP)
		वापस icsk->icsk_af_ops->माला_लोockopt(sk, level, optname,
						     optval, optlen);
	वापस करो_tcp_माला_लोockopt(sk, level, optname, optval, optlen);
पूर्ण
EXPORT_SYMBOL(tcp_माला_लोockopt);

#अगर_घोषित CONFIG_TCP_MD5SIG
अटल DEFINE_PER_CPU(काष्ठा tcp_md5sig_pool, tcp_md5sig_pool);
अटल DEFINE_MUTEX(tcp_md5sig_mutex);
अटल bool tcp_md5sig_pool_populated = false;

अटल व्योम __tcp_alloc_md5sig_pool(व्योम)
अणु
	काष्ठा crypto_ahash *hash;
	पूर्णांक cpu;

	hash = crypto_alloc_ahash("md5", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(hash))
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		व्योम *scratch = per_cpu(tcp_md5sig_pool, cpu).scratch;
		काष्ठा ahash_request *req;

		अगर (!scratch) अणु
			scratch = kदो_स्मृति_node(माप(जोड़ tcp_md5sum_block) +
					       माप(काष्ठा tcphdr),
					       GFP_KERNEL,
					       cpu_to_node(cpu));
			अगर (!scratch)
				वापस;
			per_cpu(tcp_md5sig_pool, cpu).scratch = scratch;
		पूर्ण
		अगर (per_cpu(tcp_md5sig_pool, cpu).md5_req)
			जारी;

		req = ahash_request_alloc(hash, GFP_KERNEL);
		अगर (!req)
			वापस;

		ahash_request_set_callback(req, 0, शून्य, शून्य);

		per_cpu(tcp_md5sig_pool, cpu).md5_req = req;
	पूर्ण
	/* beक्रमe setting tcp_md5sig_pool_populated, we must commit all ग_लिखोs
	 * to memory. See smp_rmb() in tcp_get_md5sig_pool()
	 */
	smp_wmb();
	tcp_md5sig_pool_populated = true;
पूर्ण

bool tcp_alloc_md5sig_pool(व्योम)
अणु
	अगर (unlikely(!tcp_md5sig_pool_populated)) अणु
		mutex_lock(&tcp_md5sig_mutex);

		अगर (!tcp_md5sig_pool_populated) अणु
			__tcp_alloc_md5sig_pool();
			अगर (tcp_md5sig_pool_populated)
				अटल_branch_inc(&tcp_md5_needed);
		पूर्ण

		mutex_unlock(&tcp_md5sig_mutex);
	पूर्ण
	वापस tcp_md5sig_pool_populated;
पूर्ण
EXPORT_SYMBOL(tcp_alloc_md5sig_pool);


/**
 *	tcp_get_md5sig_pool - get md5sig_pool क्रम this user
 *
 *	We use percpu काष्ठाure, so अगर we succeed, we निकास with preemption
 *	and BH disabled, to make sure another thपढ़ो or softirq handling
 *	wont try to get same context.
 */
काष्ठा tcp_md5sig_pool *tcp_get_md5sig_pool(व्योम)
अणु
	local_bh_disable();

	अगर (tcp_md5sig_pool_populated) अणु
		/* coupled with smp_wmb() in __tcp_alloc_md5sig_pool() */
		smp_rmb();
		वापस this_cpu_ptr(&tcp_md5sig_pool);
	पूर्ण
	local_bh_enable();
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(tcp_get_md5sig_pool);

पूर्णांक tcp_md5_hash_skb_data(काष्ठा tcp_md5sig_pool *hp,
			  स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक header_len)
अणु
	काष्ठा scatterlist sg;
	स्थिर काष्ठा tcphdr *tp = tcp_hdr(skb);
	काष्ठा ahash_request *req = hp->md5_req;
	अचिन्हित पूर्णांक i;
	स्थिर अचिन्हित पूर्णांक head_data_len = skb_headlen(skb) > header_len ?
					   skb_headlen(skb) - header_len : 0;
	स्थिर काष्ठा skb_shared_info *shi = skb_shinfo(skb);
	काष्ठा sk_buff *frag_iter;

	sg_init_table(&sg, 1);

	sg_set_buf(&sg, ((u8 *) tp) + header_len, head_data_len);
	ahash_request_set_crypt(req, &sg, शून्य, head_data_len);
	अगर (crypto_ahash_update(req))
		वापस 1;

	क्रम (i = 0; i < shi->nr_frags; ++i) अणु
		स्थिर skb_frag_t *f = &shi->frags[i];
		अचिन्हित पूर्णांक offset = skb_frag_off(f);
		काष्ठा page *page = skb_frag_page(f) + (offset >> PAGE_SHIFT);

		sg_set_page(&sg, page, skb_frag_size(f),
			    offset_in_page(offset));
		ahash_request_set_crypt(req, &sg, शून्य, skb_frag_size(f));
		अगर (crypto_ahash_update(req))
			वापस 1;
	पूर्ण

	skb_walk_frags(skb, frag_iter)
		अगर (tcp_md5_hash_skb_data(hp, frag_iter, 0))
			वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tcp_md5_hash_skb_data);

पूर्णांक tcp_md5_hash_key(काष्ठा tcp_md5sig_pool *hp, स्थिर काष्ठा tcp_md5sig_key *key)
अणु
	u8 keylen = READ_ONCE(key->keylen); /* paired with WRITE_ONCE() in tcp_md5_करो_add */
	काष्ठा scatterlist sg;

	sg_init_one(&sg, key->key, keylen);
	ahash_request_set_crypt(hp->md5_req, &sg, शून्य, keylen);

	/* We use data_race() because tcp_md5_करो_add() might change key->key under us */
	वापस data_race(crypto_ahash_update(hp->md5_req));
पूर्ण
EXPORT_SYMBOL(tcp_md5_hash_key);

#पूर्ण_अगर

व्योम tcp_करोne(काष्ठा sock *sk)
अणु
	काष्ठा request_sock *req;

	/* We might be called with a new socket, after
	 * inet_csk_prepare_क्रमced_बंद() has been called
	 * so we can not use lockdep_sock_is_held(sk)
	 */
	req = rcu_dereference_रक्षित(tcp_sk(sk)->fastखोलो_rsk, 1);

	अगर (sk->sk_state == TCP_SYN_SENT || sk->sk_state == TCP_SYN_RECV)
		TCP_INC_STATS(sock_net(sk), TCP_MIB_ATTEMPTFAILS);

	tcp_set_state(sk, TCP_CLOSE);
	tcp_clear_xmit_समयrs(sk);
	अगर (req)
		reqsk_fastखोलो_हटाओ(sk, req, false);

	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_state_change(sk);
	अन्यथा
		inet_csk_destroy_sock(sk);
पूर्ण
EXPORT_SYMBOL_GPL(tcp_करोne);

पूर्णांक tcp_पात(काष्ठा sock *sk, पूर्णांक err)
अणु
	अगर (!sk_fullsock(sk)) अणु
		अगर (sk->sk_state == TCP_NEW_SYN_RECV) अणु
			काष्ठा request_sock *req = inet_reqsk(sk);

			local_bh_disable();
			inet_csk_reqsk_queue_drop(req->rsk_listener, req);
			local_bh_enable();
			वापस 0;
		पूर्ण
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Don't race with userspace socket बंदs such as tcp_बंद. */
	lock_sock(sk);

	अगर (sk->sk_state == TCP_LISTEN) अणु
		tcp_set_state(sk, TCP_CLOSE);
		inet_csk_listen_stop(sk);
	पूर्ण

	/* Don't race with BH socket बंदs such as inet_csk_listen_stop. */
	local_bh_disable();
	bh_lock_sock(sk);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_err = err;
		/* This barrier is coupled with smp_rmb() in tcp_poll() */
		smp_wmb();
		sk->sk_error_report(sk);
		अगर (tcp_need_reset(sk->sk_state))
			tcp_send_active_reset(sk, GFP_ATOMIC);
		tcp_करोne(sk);
	पूर्ण

	bh_unlock_sock(sk);
	local_bh_enable();
	tcp_ग_लिखो_queue_purge(sk);
	release_sock(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_पात);

बाह्य काष्ठा tcp_congestion_ops tcp_reno;

अटल __initdata अचिन्हित दीर्घ thash_entries;
अटल पूर्णांक __init set_thash_entries(अक्षर *str)
अणु
	sमाप_प्रकार ret;

	अगर (!str)
		वापस 0;

	ret = kम_से_अदीर्घ(str, 0, &thash_entries);
	अगर (ret)
		वापस 0;

	वापस 1;
पूर्ण
__setup("thash_entries=", set_thash_entries);

अटल व्योम __init tcp_init_mem(व्योम)
अणु
	अचिन्हित दीर्घ limit = nr_मुक्त_buffer_pages() / 16;

	limit = max(limit, 128UL);
	sysctl_tcp_mem[0] = limit / 4 * 3;		/* 4.68 % */
	sysctl_tcp_mem[1] = limit;			/* 6.25 % */
	sysctl_tcp_mem[2] = sysctl_tcp_mem[0] * 2;	/* 9.37 % */
पूर्ण

व्योम __init tcp_init(व्योम)
अणु
	पूर्णांक max_rshare, max_wshare, cnt;
	अचिन्हित दीर्घ limit;
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(TCP_MIN_SND_MSS <= MAX_TCP_OPTION_SPACE);
	BUILD_BUG_ON(माप(काष्ठा tcp_skb_cb) >
		     माप_field(काष्ठा sk_buff, cb));

	percpu_counter_init(&tcp_sockets_allocated, 0, GFP_KERNEL);
	percpu_counter_init(&tcp_orphan_count, 0, GFP_KERNEL);
	inet_hashinfo_init(&tcp_hashinfo);
	inet_hashinfo2_init(&tcp_hashinfo, "tcp_listen_portaddr_hash",
			    thash_entries, 21,  /* one slot per 2 MB*/
			    0, 64 * 1024);
	tcp_hashinfo.bind_bucket_cachep =
		kmem_cache_create("tcp_bind_bucket",
				  माप(काष्ठा inet_bind_bucket), 0,
				  SLAB_HWCACHE_ALIGN|SLAB_PANIC, शून्य);

	/* Size and allocate the मुख्य established and bind bucket
	 * hash tables.
	 *
	 * The methoकरोlogy is similar to that of the buffer cache.
	 */
	tcp_hashinfo.ehash =
		alloc_large_प्रणाली_hash("TCP established",
					माप(काष्ठा inet_ehash_bucket),
					thash_entries,
					17, /* one slot per 128 KB of memory */
					0,
					शून्य,
					&tcp_hashinfo.ehash_mask,
					0,
					thash_entries ? 0 : 512 * 1024);
	क्रम (i = 0; i <= tcp_hashinfo.ehash_mask; i++)
		INIT_HLIST_शून्यS_HEAD(&tcp_hashinfo.ehash[i].chain, i);

	अगर (inet_ehash_locks_alloc(&tcp_hashinfo))
		panic("TCP: failed to alloc ehash_locks");
	tcp_hashinfo.bhash =
		alloc_large_प्रणाली_hash("TCP bind",
					माप(काष्ठा inet_bind_hashbucket),
					tcp_hashinfo.ehash_mask + 1,
					17, /* one slot per 128 KB of memory */
					0,
					&tcp_hashinfo.bhash_size,
					शून्य,
					0,
					64 * 1024);
	tcp_hashinfo.bhash_size = 1U << tcp_hashinfo.bhash_size;
	क्रम (i = 0; i < tcp_hashinfo.bhash_size; i++) अणु
		spin_lock_init(&tcp_hashinfo.bhash[i].lock);
		INIT_HLIST_HEAD(&tcp_hashinfo.bhash[i].chain);
	पूर्ण


	cnt = tcp_hashinfo.ehash_mask + 1;
	sysctl_tcp_max_orphans = cnt / 2;

	tcp_init_mem();
	/* Set per-socket limits to no more than 1/128 the pressure threshold */
	limit = nr_मुक्त_buffer_pages() << (PAGE_SHIFT - 7);
	max_wshare = min(4UL*1024*1024, limit);
	max_rshare = min(6UL*1024*1024, limit);

	init_net.ipv4.sysctl_tcp_wmem[0] = SK_MEM_QUANTUM;
	init_net.ipv4.sysctl_tcp_wmem[1] = 16*1024;
	init_net.ipv4.sysctl_tcp_wmem[2] = max(64*1024, max_wshare);

	init_net.ipv4.sysctl_tcp_rmem[0] = SK_MEM_QUANTUM;
	init_net.ipv4.sysctl_tcp_rmem[1] = 131072;
	init_net.ipv4.sysctl_tcp_rmem[2] = max(131072, max_rshare);

	pr_info("Hash tables configured (established %u bind %u)\n",
		tcp_hashinfo.ehash_mask + 1, tcp_hashinfo.bhash_size);

	tcp_v4_init();
	tcp_metrics_init();
	BUG_ON(tcp_रेजिस्टर_congestion_control(&tcp_reno) != 0);
	tcp_tasklet_init();
	mptcp_init();
पूर्ण
