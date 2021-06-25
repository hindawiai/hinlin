<शैली गुरु>
/*
 * net/tipc/socket.c: TIPC socket API
 *
 * Copyright (c) 2001-2007, 2012-2019, Ericsson AB
 * Copyright (c) 2004-2008, 2010-2013, Wind River Systems
 * Copyright (c) 2020-2021, Red Hat Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/rhashtable.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "core.h"
#समावेश "name_table.h"
#समावेश "node.h"
#समावेश "link.h"
#समावेश "name_distr.h"
#समावेश "socket.h"
#समावेश "bcast.h"
#समावेश "netlink.h"
#समावेश "group.h"
#समावेश "trace.h"

#घोषणा NAGLE_START_INIT	4
#घोषणा NAGLE_START_MAX		1024
#घोषणा CONN_TIMEOUT_DEFAULT    8000    /* शेष connect समयout = 8s */
#घोषणा CONN_PROBING_INTV	msecs_to_jअगरfies(3600000)  /* [ms] => 1 h */
#घोषणा TIPC_MAX_PORT		0xffffffff
#घोषणा TIPC_MIN_PORT		1
#घोषणा TIPC_ACK_RATE		4       /* ACK at 1/4 of rcv winकरोw size */

क्रमागत अणु
	TIPC_LISTEN = TCP_LISTEN,
	TIPC_ESTABLISHED = TCP_ESTABLISHED,
	TIPC_OPEN = TCP_CLOSE,
	TIPC_DISCONNECTING = TCP_CLOSE_WAIT,
	TIPC_CONNECTING = TCP_SYN_SENT,
पूर्ण;

काष्ठा sockaddr_pair अणु
	काष्ठा sockaddr_tipc sock;
	काष्ठा sockaddr_tipc member;
पूर्ण;

/**
 * काष्ठा tipc_sock - TIPC socket काष्ठाure
 * @sk: socket - पूर्णांकeracts with 'port' and with user via the socket API
 * @conn_type: TIPC type used when connection was established
 * @conn_instance: TIPC instance used when connection was established
 * @published: non-zero अगर port has one or more associated names
 * @max_pkt: maximum packet size "hint" used when building messages sent by port
 * @maxnagle: maximum size of msg which can be subject to nagle
 * @portid: unique port identity in TIPC socket hash table
 * @phdr: preक्रमmatted message header used when sending messages
 * @cong_links: list of congested links
 * @खुलाations: list of खुलाations क्रम port
 * @blocking_link: address of the congested link we are currently sleeping on
 * @pub_count: total # of खुलाations port has made during its lअगरeसमय
 * @conn_समयout: the समय we can रुको क्रम an unresponded setup request
 * @probe_unacked: probe has not received ack yet
 * @dupl_rcvcnt: number of bytes counted twice, in both backlog and rcv queue
 * @cong_link_cnt: number of congested links
 * @snt_unacked: # messages sent by socket, and not yet acked by peer
 * @snd_win: send winकरोw size
 * @peer_caps: peer capabilities mask
 * @rcv_unacked: # messages पढ़ो by user, but not yet acked back to peer
 * @rcv_win: receive winकरोw size
 * @peer: 'connected' peer क्रम dgram/rdm
 * @node: hash table node
 * @mc_method: cookie क्रम use between socket and broadcast layer
 * @rcu: rcu काष्ठा क्रम tipc_sock
 * @group: TIPC communications group
 * @oneway: message count in one direction (FIXME)
 * @nagle_start: current nagle value
 * @snd_backlog: send backlog count
 * @msg_acc: messages accepted; used in managing backlog and nagle
 * @pkt_cnt: TIPC socket packet count
 * @expect_ack: whether this TIPC socket is expecting an ack
 * @nodelay: setsockopt() TIPC_NODELAY setting
 * @group_is_खोलो: TIPC socket group is fully खोलो (FIXME)
 */
काष्ठा tipc_sock अणु
	काष्ठा sock sk;
	u32 conn_type;
	u32 conn_instance;
	u32 max_pkt;
	u32 maxnagle;
	u32 portid;
	काष्ठा tipc_msg phdr;
	काष्ठा list_head cong_links;
	काष्ठा list_head खुलाations;
	u32 pub_count;
	atomic_t dupl_rcvcnt;
	u16 conn_समयout;
	bool probe_unacked;
	u16 cong_link_cnt;
	u16 snt_unacked;
	u16 snd_win;
	u16 peer_caps;
	u16 rcv_unacked;
	u16 rcv_win;
	काष्ठा sockaddr_tipc peer;
	काष्ठा rhash_head node;
	काष्ठा tipc_mc_method mc_method;
	काष्ठा rcu_head rcu;
	काष्ठा tipc_group *group;
	u32 oneway;
	u32 nagle_start;
	u16 snd_backlog;
	u16 msg_acc;
	u16 pkt_cnt;
	bool expect_ack;
	bool nodelay;
	bool group_is_खोलो;
	bool published;
पूर्ण;

अटल पूर्णांक tipc_sk_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल व्योम tipc_data_पढ़ोy(काष्ठा sock *sk);
अटल व्योम tipc_ग_लिखो_space(काष्ठा sock *sk);
अटल व्योम tipc_sock_deकाष्ठा(काष्ठा sock *sk);
अटल पूर्णांक tipc_release(काष्ठा socket *sock);
अटल पूर्णांक tipc_accept(काष्ठा socket *sock, काष्ठा socket *new_sock, पूर्णांक flags,
		       bool kern);
अटल व्योम tipc_sk_समयout(काष्ठा समयr_list *t);
अटल पूर्णांक tipc_sk_publish(काष्ठा tipc_sock *tsk, काष्ठा tipc_uaddr *ua);
अटल पूर्णांक tipc_sk_withdraw(काष्ठा tipc_sock *tsk, काष्ठा tipc_uaddr *ua);
अटल पूर्णांक tipc_sk_leave(काष्ठा tipc_sock *tsk);
अटल काष्ठा tipc_sock *tipc_sk_lookup(काष्ठा net *net, u32 portid);
अटल पूर्णांक tipc_sk_insert(काष्ठा tipc_sock *tsk);
अटल व्योम tipc_sk_हटाओ(काष्ठा tipc_sock *tsk);
अटल पूर्णांक __tipc_sendstream(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार dsz);
अटल पूर्णांक __tipc_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार dsz);
अटल व्योम tipc_sk_push_backlog(काष्ठा tipc_sock *tsk, bool nagle_ack);

अटल स्थिर काष्ठा proto_ops packet_ops;
अटल स्थिर काष्ठा proto_ops stream_ops;
अटल स्थिर काष्ठा proto_ops msg_ops;
अटल काष्ठा proto tipc_proto;
अटल स्थिर काष्ठा rhashtable_params tsk_rht_params;

अटल u32 tsk_own_node(काष्ठा tipc_sock *tsk)
अणु
	वापस msg_prevnode(&tsk->phdr);
पूर्ण

अटल u32 tsk_peer_node(काष्ठा tipc_sock *tsk)
अणु
	वापस msg_destnode(&tsk->phdr);
पूर्ण

अटल u32 tsk_peer_port(काष्ठा tipc_sock *tsk)
अणु
	वापस msg_destport(&tsk->phdr);
पूर्ण

अटल  bool tsk_unreliable(काष्ठा tipc_sock *tsk)
अणु
	वापस msg_src_droppable(&tsk->phdr) != 0;
पूर्ण

अटल व्योम tsk_set_unreliable(काष्ठा tipc_sock *tsk, bool unreliable)
अणु
	msg_set_src_droppable(&tsk->phdr, unreliable ? 1 : 0);
पूर्ण

अटल bool tsk_unवापसable(काष्ठा tipc_sock *tsk)
अणु
	वापस msg_dest_droppable(&tsk->phdr) != 0;
पूर्ण

अटल व्योम tsk_set_unवापसable(काष्ठा tipc_sock *tsk, bool unवापसable)
अणु
	msg_set_dest_droppable(&tsk->phdr, unवापसable ? 1 : 0);
पूर्ण

अटल पूर्णांक tsk_importance(काष्ठा tipc_sock *tsk)
अणु
	वापस msg_importance(&tsk->phdr);
पूर्ण

अटल काष्ठा tipc_sock *tipc_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस container_of(sk, काष्ठा tipc_sock, sk);
पूर्ण

पूर्णांक tsk_set_importance(काष्ठा sock *sk, पूर्णांक imp)
अणु
	अगर (imp > TIPC_CRITICAL_IMPORTANCE)
		वापस -EINVAL;
	msg_set_importance(&tipc_sk(sk)->phdr, (u32)imp);
	वापस 0;
पूर्ण

अटल bool tsk_conn_cong(काष्ठा tipc_sock *tsk)
अणु
	वापस tsk->snt_unacked > tsk->snd_win;
पूर्ण

अटल u16 tsk_blocks(पूर्णांक len)
अणु
	वापस ((len / FLOWCTL_BLK_SZ) + 1);
पूर्ण

/* tsk_blocks(): translate a buffer size in bytes to number of
 * advertisable blocks, taking पूर्णांकo account the ratio truesize(len)/len
 * We can trust that this ratio is always < 4 क्रम len >= FLOWCTL_BLK_SZ
 */
अटल u16 tsk_adv_blocks(पूर्णांक len)
अणु
	वापस len / FLOWCTL_BLK_SZ / 4;
पूर्ण

/* tsk_inc(): increment counter क्रम sent or received data
 * - If block based flow control is not supported by peer we
 *   fall back to message based ditto, incrementing the counter
 */
अटल u16 tsk_inc(काष्ठा tipc_sock *tsk, पूर्णांक msglen)
अणु
	अगर (likely(tsk->peer_caps & TIPC_BLOCK_FLOWCTL))
		वापस ((msglen / FLOWCTL_BLK_SZ) + 1);
	वापस 1;
पूर्ण

/* tsk_set_nagle - enable/disable nagle property by manipulating maxnagle
 */
अटल व्योम tsk_set_nagle(काष्ठा tipc_sock *tsk)
अणु
	काष्ठा sock *sk = &tsk->sk;

	tsk->maxnagle = 0;
	अगर (sk->sk_type != SOCK_STREAM)
		वापस;
	अगर (tsk->nodelay)
		वापस;
	अगर (!(tsk->peer_caps & TIPC_NAGLE))
		वापस;
	/* Limit node local buffer size to aव्योम receive queue overflow */
	अगर (tsk->max_pkt == MAX_MSG_SIZE)
		tsk->maxnagle = 1500;
	अन्यथा
		tsk->maxnagle = tsk->max_pkt;
पूर्ण

/**
 * tsk_advance_rx_queue - discard first buffer in socket receive queue
 * @sk: network socket
 *
 * Caller must hold socket lock
 */
अटल व्योम tsk_advance_rx_queue(काष्ठा sock *sk)
अणु
	trace_tipc_sk_advance_rx(sk, शून्य, TIPC_DUMP_SK_RCVQ, " ");
	kमुक्त_skb(__skb_dequeue(&sk->sk_receive_queue));
पूर्ण

/* tipc_sk_respond() : send response message back to sender
 */
अटल व्योम tipc_sk_respond(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	u32 selector;
	u32 dnode;
	u32 onode = tipc_own_addr(sock_net(sk));

	अगर (!tipc_msg_reverse(onode, &skb, err))
		वापस;

	trace_tipc_sk_rej_msg(sk, skb, TIPC_DUMP_NONE, "@sk_respond!");
	dnode = msg_destnode(buf_msg(skb));
	selector = msg_origport(buf_msg(skb));
	tipc_node_xmit_skb(sock_net(sk), skb, dnode, selector);
पूर्ण

/**
 * tsk_rej_rx_queue - reject all buffers in socket receive queue
 * @sk: network socket
 * @error: response error code
 *
 * Caller must hold socket lock
 */
अटल व्योम tsk_rej_rx_queue(काष्ठा sock *sk, पूर्णांक error)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&sk->sk_receive_queue)))
		tipc_sk_respond(sk, skb, error);
पूर्ण

अटल bool tipc_sk_connected(काष्ठा sock *sk)
अणु
	वापस sk->sk_state == TIPC_ESTABLISHED;
पूर्ण

/* tipc_sk_type_connectionless - check अगर the socket is datagram socket
 * @sk: socket
 *
 * Returns true अगर connection less, false otherwise
 */
अटल bool tipc_sk_type_connectionless(काष्ठा sock *sk)
अणु
	वापस sk->sk_type == SOCK_RDM || sk->sk_type == SOCK_DGRAM;
पूर्ण

/* tsk_peer_msg - verअगरy अगर message was sent by connected port's peer
 *
 * Handles हालs where the node's network address has changed from
 * the शेष of <0.0.0> to its configured setting.
 */
अटल bool tsk_peer_msg(काष्ठा tipc_sock *tsk, काष्ठा tipc_msg *msg)
अणु
	काष्ठा sock *sk = &tsk->sk;
	u32 self = tipc_own_addr(sock_net(sk));
	u32 peer_port = tsk_peer_port(tsk);
	u32 orig_node, peer_node;

	अगर (unlikely(!tipc_sk_connected(sk)))
		वापस false;

	अगर (unlikely(msg_origport(msg) != peer_port))
		वापस false;

	orig_node = msg_orignode(msg);
	peer_node = tsk_peer_node(tsk);

	अगर (likely(orig_node == peer_node))
		वापस true;

	अगर (!orig_node && peer_node == self)
		वापस true;

	अगर (!peer_node && orig_node == self)
		वापस true;

	वापस false;
पूर्ण

/* tipc_set_sk_state - set the sk_state of the socket
 * @sk: socket
 *
 * Caller must hold socket lock
 *
 * Returns 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_set_sk_state(काष्ठा sock *sk, पूर्णांक state)
अणु
	पूर्णांक oldsk_state = sk->sk_state;
	पूर्णांक res = -EINVAL;

	चयन (state) अणु
	हाल TIPC_OPEN:
		res = 0;
		अवरोध;
	हाल TIPC_LISTEN:
	हाल TIPC_CONNECTING:
		अगर (oldsk_state == TIPC_OPEN)
			res = 0;
		अवरोध;
	हाल TIPC_ESTABLISHED:
		अगर (oldsk_state == TIPC_CONNECTING ||
		    oldsk_state == TIPC_OPEN)
			res = 0;
		अवरोध;
	हाल TIPC_DISCONNECTING:
		अगर (oldsk_state == TIPC_CONNECTING ||
		    oldsk_state == TIPC_ESTABLISHED)
			res = 0;
		अवरोध;
	पूर्ण

	अगर (!res)
		sk->sk_state = state;

	वापस res;
पूर्ण

अटल पूर्णांक tipc_sk_sock_err(काष्ठा socket *sock, दीर्घ *समयout)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = sock_error(sk);
	पूर्णांक typ = sock->type;

	अगर (err)
		वापस err;
	अगर (typ == SOCK_STREAM || typ == SOCK_SEQPACKET) अणु
		अगर (sk->sk_state == TIPC_DISCONNECTING)
			वापस -EPIPE;
		अन्यथा अगर (!tipc_sk_connected(sk))
			वापस -ENOTCONN;
	पूर्ण
	अगर (!*समयout)
		वापस -EAGAIN;
	अगर (संकेत_pending(current))
		वापस sock_पूर्णांकr_त्रुटि_सं(*समयout);

	वापस 0;
पूर्ण

#घोषणा tipc_रुको_क्रम_cond(sock_, समयo_, condition_)			       \
(अणु                                                                             \
	DEFINE_WAIT_FUNC(रुको_, woken_wake_function);                          \
	काष्ठा sock *sk_;						       \
	पूर्णांक rc_;							       \
									       \
	जबतक ((rc_ = !(condition_))) अणु					       \
		/* coupled with smp_wmb() in tipc_sk_proto_rcv() */            \
		smp_rmb();                                                     \
		sk_ = (sock_)->sk;					       \
		rc_ = tipc_sk_sock_err((sock_), समयo_);		       \
		अगर (rc_)						       \
			अवरोध;						       \
		add_रुको_queue(sk_sleep(sk_), &रुको_);                         \
		release_sock(sk_);					       \
		*(समयo_) = रुको_woken(&रुको_, TASK_INTERRUPTIBLE, *(समयo_)); \
		sched_annotate_sleep();				               \
		lock_sock(sk_);						       \
		हटाओ_रुको_queue(sk_sleep(sk_), &रुको_);		       \
	पूर्ण								       \
	rc_;								       \
पूर्ण)

/**
 * tipc_sk_create - create a TIPC socket
 * @net: network namespace (must be शेष network)
 * @sock: pre-allocated socket काष्ठाure
 * @protocol: protocol indicator (must be 0)
 * @kern: caused by kernel or by userspace?
 *
 * This routine creates additional data काष्ठाures used by the TIPC socket,
 * initializes them, and links them together.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_sk_create(काष्ठा net *net, काष्ठा socket *sock,
			  पूर्णांक protocol, पूर्णांक kern)
अणु
	स्थिर काष्ठा proto_ops *ops;
	काष्ठा sock *sk;
	काष्ठा tipc_sock *tsk;
	काष्ठा tipc_msg *msg;

	/* Validate arguments */
	अगर (unlikely(protocol != 0))
		वापस -EPROTONOSUPPORT;

	चयन (sock->type) अणु
	हाल SOCK_STREAM:
		ops = &stream_ops;
		अवरोध;
	हाल SOCK_SEQPACKET:
		ops = &packet_ops;
		अवरोध;
	हाल SOCK_DGRAM:
	हाल SOCK_RDM:
		ops = &msg_ops;
		अवरोध;
	शेष:
		वापस -EPROTOTYPE;
	पूर्ण

	/* Allocate socket's protocol area */
	sk = sk_alloc(net, AF_TIPC, GFP_KERNEL, &tipc_proto, kern);
	अगर (sk == शून्य)
		वापस -ENOMEM;

	tsk = tipc_sk(sk);
	tsk->max_pkt = MAX_PKT_DEFAULT;
	tsk->maxnagle = 0;
	tsk->nagle_start = NAGLE_START_INIT;
	INIT_LIST_HEAD(&tsk->खुलाations);
	INIT_LIST_HEAD(&tsk->cong_links);
	msg = &tsk->phdr;

	/* Finish initializing socket data काष्ठाures */
	sock->ops = ops;
	sock_init_data(sock, sk);
	tipc_set_sk_state(sk, TIPC_OPEN);
	अगर (tipc_sk_insert(tsk)) अणु
		pr_warn("Socket create failed; port number exhausted\n");
		वापस -EINVAL;
	पूर्ण

	/* Ensure tsk is visible beक्रमe we पढ़ो own_addr. */
	smp_mb();

	tipc_msg_init(tipc_own_addr(net), msg, TIPC_LOW_IMPORTANCE,
		      TIPC_NAMED_MSG, NAMED_H_SIZE, 0);

	msg_set_origport(msg, tsk->portid);
	समयr_setup(&sk->sk_समयr, tipc_sk_समयout, 0);
	sk->sk_shutकरोwn = 0;
	sk->sk_backlog_rcv = tipc_sk_backlog_rcv;
	sk->sk_rcvbuf = sysctl_tipc_rmem[1];
	sk->sk_data_पढ़ोy = tipc_data_पढ़ोy;
	sk->sk_ग_लिखो_space = tipc_ग_लिखो_space;
	sk->sk_deकाष्ठा = tipc_sock_deकाष्ठा;
	tsk->conn_समयout = CONN_TIMEOUT_DEFAULT;
	tsk->group_is_खोलो = true;
	atomic_set(&tsk->dupl_rcvcnt, 0);

	/* Start out with safe limits until we receive an advertised winकरोw */
	tsk->snd_win = tsk_adv_blocks(RCVBUF_MIN);
	tsk->rcv_win = tsk->snd_win;

	अगर (tipc_sk_type_connectionless(sk)) अणु
		tsk_set_unवापसable(tsk, true);
		अगर (sock->type == SOCK_DGRAM)
			tsk_set_unreliable(tsk, true);
	पूर्ण
	__skb_queue_head_init(&tsk->mc_method.deferredq);
	trace_tipc_sk_create(sk, शून्य, TIPC_DUMP_NONE, " ");
	वापस 0;
पूर्ण

अटल व्योम tipc_sk_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा tipc_sock *tsk = container_of(head, काष्ठा tipc_sock, rcu);

	sock_put(&tsk->sk);
पूर्ण

/* Caller should hold socket lock क्रम the socket. */
अटल व्योम __tipc_shutकरोwn(काष्ठा socket *sock, पूर्णांक error)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा net *net = sock_net(sk);
	दीर्घ समयout = msecs_to_jअगरfies(CONN_TIMEOUT_DEFAULT);
	u32 dnode = tsk_peer_node(tsk);
	काष्ठा sk_buff *skb;

	/* Aव्योम that hi-prio shutकरोwn msgs bypass msgs in link wakeup queue */
	tipc_रुको_क्रम_cond(sock, &समयout, (!tsk->cong_link_cnt &&
					    !tsk_conn_cong(tsk)));

	/* Push out delayed messages अगर in Nagle mode */
	tipc_sk_push_backlog(tsk, false);
	/* Remove pending SYN */
	__skb_queue_purge(&sk->sk_ग_लिखो_queue);

	/* Remove partially received buffer अगर any */
	skb = skb_peek(&sk->sk_receive_queue);
	अगर (skb && TIPC_SKB_CB(skb)->bytes_पढ़ो) अणु
		__skb_unlink(skb, &sk->sk_receive_queue);
		kमुक्त_skb(skb);
	पूर्ण

	/* Reject all unreceived messages अगर connectionless */
	अगर (tipc_sk_type_connectionless(sk)) अणु
		tsk_rej_rx_queue(sk, error);
		वापस;
	पूर्ण

	चयन (sk->sk_state) अणु
	हाल TIPC_CONNECTING:
	हाल TIPC_ESTABLISHED:
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
		tipc_node_हटाओ_conn(net, dnode, tsk->portid);
		/* Send a FIN+/- to its peer */
		skb = __skb_dequeue(&sk->sk_receive_queue);
		अगर (skb) अणु
			__skb_queue_purge(&sk->sk_receive_queue);
			tipc_sk_respond(sk, skb, error);
			अवरोध;
		पूर्ण
		skb = tipc_msg_create(TIPC_CRITICAL_IMPORTANCE,
				      TIPC_CONN_MSG, SHORT_H_SIZE, 0, dnode,
				      tsk_own_node(tsk), tsk_peer_port(tsk),
				      tsk->portid, error);
		अगर (skb)
			tipc_node_xmit_skb(net, skb, dnode, tsk->portid);
		अवरोध;
	हाल TIPC_LISTEN:
		/* Reject all SYN messages */
		tsk_rej_rx_queue(sk, error);
		अवरोध;
	शेष:
		__skb_queue_purge(&sk->sk_receive_queue);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * tipc_release - destroy a TIPC socket
 * @sock: socket to destroy
 *
 * This routine cleans up any messages that are still queued on the socket.
 * For DGRAM and RDM socket types, all queued messages are rejected.
 * For SEQPACKET and STREAM socket types, the first message is rejected
 * and any others are discarded.  (If the first message on a STREAM socket
 * is partially-पढ़ो, it is discarded and the next one is rejected instead.)
 *
 * NOTE: Rejected messages are not necessarily वापसed to the sender!  They
 * are वापसed or discarded according to the "destination droppable" setting
 * specअगरied क्रम the message by the sender.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk;

	/*
	 * Exit अगर socket isn't fully initialized (occurs when a failed accept()
	 * releases a pre-allocated child socket that was never used)
	 */
	अगर (sk == शून्य)
		वापस 0;

	tsk = tipc_sk(sk);
	lock_sock(sk);

	trace_tipc_sk_release(sk, शून्य, TIPC_DUMP_ALL, " ");
	__tipc_shutकरोwn(sock, TIPC_ERR_NO_PORT);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	tipc_sk_leave(tsk);
	tipc_sk_withdraw(tsk, शून्य);
	__skb_queue_purge(&tsk->mc_method.deferredq);
	sk_stop_समयr(sk, &sk->sk_समयr);
	tipc_sk_हटाओ(tsk);

	sock_orphan(sk);
	/* Reject any messages that accumulated in backlog queue */
	release_sock(sk);
	tipc_dest_list_purge(&tsk->cong_links);
	tsk->cong_link_cnt = 0;
	call_rcu(&tsk->rcu, tipc_sk_callback);
	sock->sk = शून्य;

	वापस 0;
पूर्ण

/**
 * __tipc_bind - associate or disassocate TIPC name(s) with a socket
 * @sock: socket काष्ठाure
 * @skaddr: socket address describing name(s) and desired operation
 * @alen: size of socket address data काष्ठाure
 *
 * Name and name sequence binding is indicated using a positive scope value;
 * a negative scope value unbinds the specअगरied name.  Specअगरying no name
 * (i.e. a socket address length of 0) unbinds all names from the socket.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 *
 * NOTE: This routine करोesn't need to take the socket lock since it doesn't
 *       access any non-स्थिरant socket inक्रमmation.
 */
अटल पूर्णांक __tipc_bind(काष्ठा socket *sock, काष्ठा sockaddr *skaddr, पूर्णांक alen)
अणु
	काष्ठा tipc_uaddr *ua = (काष्ठा tipc_uaddr *)skaddr;
	काष्ठा tipc_sock *tsk = tipc_sk(sock->sk);
	bool unbind = false;

	अगर (unlikely(!alen))
		वापस tipc_sk_withdraw(tsk, शून्य);

	अगर (ua->addrtype == TIPC_SERVICE_ADDR) अणु
		ua->addrtype = TIPC_SERVICE_RANGE;
		ua->sr.upper = ua->sr.lower;
	पूर्ण
	अगर (ua->scope < 0) अणु
		unbind = true;
		ua->scope = -ua->scope;
	पूर्ण
	/* Users may still use deprecated TIPC_ZONE_SCOPE */
	अगर (ua->scope != TIPC_NODE_SCOPE)
		ua->scope = TIPC_CLUSTER_SCOPE;

	अगर (tsk->group)
		वापस -EACCES;

	अगर (unbind)
		वापस tipc_sk_withdraw(tsk, ua);
	वापस tipc_sk_publish(tsk, ua);
पूर्ण

पूर्णांक tipc_sk_bind(काष्ठा socket *sock, काष्ठा sockaddr *skaddr, पूर्णांक alen)
अणु
	पूर्णांक res;

	lock_sock(sock->sk);
	res = __tipc_bind(sock, skaddr, alen);
	release_sock(sock->sk);
	वापस res;
पूर्ण

अटल पूर्णांक tipc_bind(काष्ठा socket *sock, काष्ठा sockaddr *skaddr, पूर्णांक alen)
अणु
	काष्ठा tipc_uaddr *ua = (काष्ठा tipc_uaddr *)skaddr;
	u32 atype = ua->addrtype;

	अगर (alen) अणु
		अगर (!tipc_uaddr_valid(ua, alen))
			वापस -EINVAL;
		अगर (atype == TIPC_SOCKET_ADDR)
			वापस -EAFNOSUPPORT;
		अगर (ua->sr.type < TIPC_RESERVED_TYPES) अणु
			pr_warn_once("Can't bind to reserved service type %u\n",
				     ua->sr.type);
			वापस -EACCES;
		पूर्ण
	पूर्ण
	वापस tipc_sk_bind(sock, skaddr, alen);
पूर्ण

/**
 * tipc_getname - get port ID of socket or peer socket
 * @sock: socket काष्ठाure
 * @uaddr: area क्रम वापसed socket address
 * @peer: 0 = own ID, 1 = current peer ID, 2 = current/क्रमmer peer ID
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 *
 * NOTE: This routine करोesn't need to take the socket lock since it only
 *       accesses socket inक्रमmation that is unchanging (or which changes in
 *       a completely predictable manner).
 */
अटल पूर्णांक tipc_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			पूर्णांक peer)
अणु
	काष्ठा sockaddr_tipc *addr = (काष्ठा sockaddr_tipc *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);

	स_रखो(addr, 0, माप(*addr));
	अगर (peer) अणु
		अगर ((!tipc_sk_connected(sk)) &&
		    ((peer != 2) || (sk->sk_state != TIPC_DISCONNECTING)))
			वापस -ENOTCONN;
		addr->addr.id.ref = tsk_peer_port(tsk);
		addr->addr.id.node = tsk_peer_node(tsk);
	पूर्ण अन्यथा अणु
		addr->addr.id.ref = tsk->portid;
		addr->addr.id.node = tipc_own_addr(sock_net(sk));
	पूर्ण

	addr->addrtype = TIPC_SOCKET_ADDR;
	addr->family = AF_TIPC;
	addr->scope = 0;
	addr->addr.name.करोमुख्य = 0;

	वापस माप(*addr);
पूर्ण

/**
 * tipc_poll - पढ़ो and possibly block on pollmask
 * @file: file काष्ठाure associated with the socket
 * @sock: socket क्रम which to calculate the poll bits
 * @रुको: ???
 *
 * Return: pollmask value
 *
 * COMMENTARY:
 * It appears that the usual socket locking mechanisms are not useful here
 * since the pollmask info is potentially out-of-date the moment this routine
 * निकासs.  TCP and other protocols seem to rely on higher level poll routines
 * to handle any preventable race conditions, so TIPC will करो the same ...
 *
 * IMPORTANT: The fact that a पढ़ो or ग_लिखो operation is indicated करोes NOT
 * imply that the operation will succeed, merely that it should be perक्रमmed
 * and will not block.
 */
अटल __poll_t tipc_poll(काष्ठा file *file, काष्ठा socket *sock,
			      poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	__poll_t revents = 0;

	sock_poll_रुको(file, sock, रुको);
	trace_tipc_sk_poll(sk, शून्य, TIPC_DUMP_ALL, " ");

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		revents |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		revents |= EPOLLHUP;

	चयन (sk->sk_state) अणु
	हाल TIPC_ESTABLISHED:
		अगर (!tsk->cong_link_cnt && !tsk_conn_cong(tsk))
			revents |= EPOLLOUT;
		fallthrough;
	हाल TIPC_LISTEN:
	हाल TIPC_CONNECTING:
		अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
			revents |= EPOLLIN | EPOLLRDNORM;
		अवरोध;
	हाल TIPC_OPEN:
		अगर (tsk->group_is_खोलो && !tsk->cong_link_cnt)
			revents |= EPOLLOUT;
		अगर (!tipc_sk_type_connectionless(sk))
			अवरोध;
		अगर (skb_queue_empty_lockless(&sk->sk_receive_queue))
			अवरोध;
		revents |= EPOLLIN | EPOLLRDNORM;
		अवरोध;
	हाल TIPC_DISCONNECTING:
		revents = EPOLLIN | EPOLLRDNORM | EPOLLHUP;
		अवरोध;
	पूर्ण
	वापस revents;
पूर्ण

/**
 * tipc_sendmcast - send multicast message
 * @sock: socket काष्ठाure
 * @ua: destination address काष्ठा
 * @msg: message to send
 * @dlen: length of data to send
 * @समयout: समयout to रुको क्रम wakeup
 *
 * Called from function tipc_sendmsg(), which has करोne all sanity checks
 * Return: the number of bytes sent on success, or त्रुटि_सं
 */
अटल पूर्णांक tipc_sendmcast(काष्ठा  socket *sock, काष्ठा tipc_uaddr *ua,
			  काष्ठा msghdr *msg, माप_प्रकार dlen, दीर्घ समयout)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक mtu = tipc_bcast_get_mtu(net);
	काष्ठा sk_buff_head pkts;
	काष्ठा tipc_nlist dsts;
	पूर्णांक rc;

	अगर (tsk->group)
		वापस -EACCES;

	/* Block or वापस अगर any destination link is congested */
	rc = tipc_रुको_क्रम_cond(sock, &समयout, !tsk->cong_link_cnt);
	अगर (unlikely(rc))
		वापस rc;

	/* Lookup destination nodes */
	tipc_nlist_init(&dsts, tipc_own_addr(net));
	tipc_nametbl_lookup_mcast_nodes(net, ua, &dsts);
	अगर (!dsts.local && !dsts.remote)
		वापस -EHOSTUNREACH;

	/* Build message header */
	msg_set_type(hdr, TIPC_MCAST_MSG);
	msg_set_hdr_sz(hdr, MCAST_H_SIZE);
	msg_set_lookup_scope(hdr, TIPC_CLUSTER_SCOPE);
	msg_set_destport(hdr, 0);
	msg_set_destnode(hdr, 0);
	msg_set_nametype(hdr, ua->sr.type);
	msg_set_namelower(hdr, ua->sr.lower);
	msg_set_nameupper(hdr, ua->sr.upper);

	/* Build message as chain of buffers */
	__skb_queue_head_init(&pkts);
	rc = tipc_msg_build(hdr, msg, 0, dlen, mtu, &pkts);

	/* Send message अगर build was successful */
	अगर (unlikely(rc == dlen)) अणु
		trace_tipc_sk_sendmcast(sk, skb_peek(&pkts),
					TIPC_DUMP_SK_SNDQ, " ");
		rc = tipc_mcast_xmit(net, &pkts, &tsk->mc_method, &dsts,
				     &tsk->cong_link_cnt);
	पूर्ण

	tipc_nlist_purge(&dsts);

	वापस rc ? rc : dlen;
पूर्ण

/**
 * tipc_send_group_msg - send a message to a member in the group
 * @net: network namespace
 * @tsk: tipc socket
 * @m: message to send
 * @mb: group member
 * @dnode: destination node
 * @dport: destination port
 * @dlen: total length of message data
 */
अटल पूर्णांक tipc_send_group_msg(काष्ठा net *net, काष्ठा tipc_sock *tsk,
			       काष्ठा msghdr *m, काष्ठा tipc_member *mb,
			       u32 dnode, u32 dport, पूर्णांक dlen)
अणु
	u16 bc_snd_nxt = tipc_group_bc_snd_nxt(tsk->group);
	काष्ठा tipc_mc_method *method = &tsk->mc_method;
	पूर्णांक blks = tsk_blocks(GROUP_H_SIZE + dlen);
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	काष्ठा sk_buff_head pkts;
	पूर्णांक mtu, rc;

	/* Complete message header */
	msg_set_type(hdr, TIPC_GRP_UCAST_MSG);
	msg_set_hdr_sz(hdr, GROUP_H_SIZE);
	msg_set_destport(hdr, dport);
	msg_set_destnode(hdr, dnode);
	msg_set_grp_bc_seqno(hdr, bc_snd_nxt);

	/* Build message as chain of buffers */
	__skb_queue_head_init(&pkts);
	mtu = tipc_node_get_mtu(net, dnode, tsk->portid, false);
	rc = tipc_msg_build(hdr, m, 0, dlen, mtu, &pkts);
	अगर (unlikely(rc != dlen))
		वापस rc;

	/* Send message */
	rc = tipc_node_xmit(net, &pkts, dnode, tsk->portid);
	अगर (unlikely(rc == -ELINKCONG)) अणु
		tipc_dest_push(&tsk->cong_links, dnode, 0);
		tsk->cong_link_cnt++;
	पूर्ण

	/* Update send winकरोw */
	tipc_group_update_member(mb, blks);

	/* A broadcast sent within next EXPIRE period must follow same path */
	method->rcast = true;
	method->mandatory = true;
	वापस dlen;
पूर्ण

/**
 * tipc_send_group_unicast - send message to a member in the group
 * @sock: socket काष्ठाure
 * @m: message to send
 * @dlen: total length of message data
 * @समयout: समयout to रुको क्रम wakeup
 *
 * Called from function tipc_sendmsg(), which has करोne all sanity checks
 * Return: the number of bytes sent on success, or त्रुटि_सं
 */
अटल पूर्णांक tipc_send_group_unicast(काष्ठा socket *sock, काष्ठा msghdr *m,
				   पूर्णांक dlen, दीर्घ समयout)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_uaddr *ua = (काष्ठा tipc_uaddr *)m->msg_name;
	पूर्णांक blks = tsk_blocks(GROUP_H_SIZE + dlen);
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा net *net = sock_net(sk);
	काष्ठा tipc_member *mb = शून्य;
	u32 node, port;
	पूर्णांक rc;

	node = ua->sk.node;
	port = ua->sk.ref;
	अगर (!port && !node)
		वापस -EHOSTUNREACH;

	/* Block or वापस अगर destination link or member is congested */
	rc = tipc_रुको_क्रम_cond(sock, &समयout,
				!tipc_dest_find(&tsk->cong_links, node, 0) &&
				tsk->group &&
				!tipc_group_cong(tsk->group, node, port, blks,
						 &mb));
	अगर (unlikely(rc))
		वापस rc;

	अगर (unlikely(!mb))
		वापस -EHOSTUNREACH;

	rc = tipc_send_group_msg(net, tsk, m, mb, node, port, dlen);

	वापस rc ? rc : dlen;
पूर्ण

/**
 * tipc_send_group_anycast - send message to any member with given identity
 * @sock: socket काष्ठाure
 * @m: message to send
 * @dlen: total length of message data
 * @समयout: समयout to रुको क्रम wakeup
 *
 * Called from function tipc_sendmsg(), which has करोne all sanity checks
 * Return: the number of bytes sent on success, or त्रुटि_सं
 */
अटल पूर्णांक tipc_send_group_anycast(काष्ठा socket *sock, काष्ठा msghdr *m,
				   पूर्णांक dlen, दीर्घ समयout)
अणु
	काष्ठा tipc_uaddr *ua = (काष्ठा tipc_uaddr *)m->msg_name;
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा list_head *cong_links = &tsk->cong_links;
	पूर्णांक blks = tsk_blocks(GROUP_H_SIZE + dlen);
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	काष्ठा tipc_member *first = शून्य;
	काष्ठा tipc_member *mbr = शून्य;
	काष्ठा net *net = sock_net(sk);
	u32 node, port, exclude;
	काष्ठा list_head dsts;
	पूर्णांक lookups = 0;
	पूर्णांक dstcnt, rc;
	bool cong;

	INIT_LIST_HEAD(&dsts);
	ua->sa.type = msg_nametype(hdr);
	ua->scope = msg_lookup_scope(hdr);

	जबतक (++lookups < 4) अणु
		exclude = tipc_group_exclude(tsk->group);

		first = शून्य;

		/* Look क्रम a non-congested destination member, अगर any */
		जबतक (1) अणु
			अगर (!tipc_nametbl_lookup_group(net, ua, &dsts, &dstcnt,
						       exclude, false))
				वापस -EHOSTUNREACH;
			tipc_dest_pop(&dsts, &node, &port);
			cong = tipc_group_cong(tsk->group, node, port, blks,
					       &mbr);
			अगर (!cong)
				अवरोध;
			अगर (mbr == first)
				अवरोध;
			अगर (!first)
				first = mbr;
		पूर्ण

		/* Start over अगर destination was not in member list */
		अगर (unlikely(!mbr))
			जारी;

		अगर (likely(!cong && !tipc_dest_find(cong_links, node, 0)))
			अवरोध;

		/* Block or वापस अगर destination link or member is congested */
		rc = tipc_रुको_क्रम_cond(sock, &समयout,
					!tipc_dest_find(cong_links, node, 0) &&
					tsk->group &&
					!tipc_group_cong(tsk->group, node, port,
							 blks, &mbr));
		अगर (unlikely(rc))
			वापस rc;

		/* Send, unless destination disappeared जबतक रुकोing */
		अगर (likely(mbr))
			अवरोध;
	पूर्ण

	अगर (unlikely(lookups >= 4))
		वापस -EHOSTUNREACH;

	rc = tipc_send_group_msg(net, tsk, m, mbr, node, port, dlen);

	वापस rc ? rc : dlen;
पूर्ण

/**
 * tipc_send_group_bcast - send message to all members in communication group
 * @sock: socket काष्ठाure
 * @m: message to send
 * @dlen: total length of message data
 * @समयout: समयout to रुको क्रम wakeup
 *
 * Called from function tipc_sendmsg(), which has करोne all sanity checks
 * Return: the number of bytes sent on success, or त्रुटि_सं
 */
अटल पूर्णांक tipc_send_group_bcast(काष्ठा socket *sock, काष्ठा msghdr *m,
				 पूर्णांक dlen, दीर्घ समयout)
अणु
	काष्ठा tipc_uaddr *ua = (काष्ठा tipc_uaddr *)m->msg_name;
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_nlist *dsts;
	काष्ठा tipc_mc_method *method = &tsk->mc_method;
	bool ack = method->mandatory && method->rcast;
	पूर्णांक blks = tsk_blocks(MCAST_H_SIZE + dlen);
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	पूर्णांक mtu = tipc_bcast_get_mtu(net);
	काष्ठा sk_buff_head pkts;
	पूर्णांक rc = -EHOSTUNREACH;

	/* Block or वापस अगर any destination link or member is congested */
	rc = tipc_रुको_क्रम_cond(sock, &समयout,
				!tsk->cong_link_cnt && tsk->group &&
				!tipc_group_bc_cong(tsk->group, blks));
	अगर (unlikely(rc))
		वापस rc;

	dsts = tipc_group_dests(tsk->group);
	अगर (!dsts->local && !dsts->remote)
		वापस -EHOSTUNREACH;

	/* Complete message header */
	अगर (ua) अणु
		msg_set_type(hdr, TIPC_GRP_MCAST_MSG);
		msg_set_nameinst(hdr, ua->sa.instance);
	पूर्ण अन्यथा अणु
		msg_set_type(hdr, TIPC_GRP_BCAST_MSG);
		msg_set_nameinst(hdr, 0);
	पूर्ण
	msg_set_hdr_sz(hdr, GROUP_H_SIZE);
	msg_set_destport(hdr, 0);
	msg_set_destnode(hdr, 0);
	msg_set_grp_bc_seqno(hdr, tipc_group_bc_snd_nxt(tsk->group));

	/* Aव्योम getting stuck with repeated क्रमced replicasts */
	msg_set_grp_bc_ack_req(hdr, ack);

	/* Build message as chain of buffers */
	__skb_queue_head_init(&pkts);
	rc = tipc_msg_build(hdr, m, 0, dlen, mtu, &pkts);
	अगर (unlikely(rc != dlen))
		वापस rc;

	/* Send message */
	rc = tipc_mcast_xmit(net, &pkts, method, dsts, &tsk->cong_link_cnt);
	अगर (unlikely(rc))
		वापस rc;

	/* Update broadcast sequence number and send winकरोws */
	tipc_group_update_bc_members(tsk->group, blks, ack);

	/* Broadcast link is now मुक्त to choose method क्रम next broadcast */
	method->mandatory = false;
	method->expires = jअगरfies;

	वापस dlen;
पूर्ण

/**
 * tipc_send_group_mcast - send message to all members with given identity
 * @sock: socket काष्ठाure
 * @m: message to send
 * @dlen: total length of message data
 * @समयout: समयout to रुको क्रम wakeup
 *
 * Called from function tipc_sendmsg(), which has करोne all sanity checks
 * Return: the number of bytes sent on success, or त्रुटि_सं
 */
अटल पूर्णांक tipc_send_group_mcast(काष्ठा socket *sock, काष्ठा msghdr *m,
				 पूर्णांक dlen, दीर्घ समयout)
अणु
	काष्ठा tipc_uaddr *ua = (काष्ठा tipc_uaddr *)m->msg_name;
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_group *grp = tsk->group;
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	काष्ठा net *net = sock_net(sk);
	काष्ठा list_head dsts;
	u32 dstcnt, exclude;

	INIT_LIST_HEAD(&dsts);
	ua->sa.type = msg_nametype(hdr);
	ua->scope = msg_lookup_scope(hdr);
	exclude = tipc_group_exclude(grp);

	अगर (!tipc_nametbl_lookup_group(net, ua, &dsts, &dstcnt, exclude, true))
		वापस -EHOSTUNREACH;

	अगर (dstcnt == 1) अणु
		tipc_dest_pop(&dsts, &ua->sk.node, &ua->sk.ref);
		वापस tipc_send_group_unicast(sock, m, dlen, समयout);
	पूर्ण

	tipc_dest_list_purge(&dsts);
	वापस tipc_send_group_bcast(sock, m, dlen, समयout);
पूर्ण

/**
 * tipc_sk_mcast_rcv - Deliver multicast messages to all destination sockets
 * @net: the associated network namespace
 * @arrvq: queue with arriving messages, to be cloned after destination lookup
 * @inputq: queue with cloned messages, delivered to socket after dest lookup
 *
 * Multi-thपढ़ोed: parallel calls with reference to same queues may occur
 */
व्योम tipc_sk_mcast_rcv(काष्ठा net *net, काष्ठा sk_buff_head *arrvq,
		       काष्ठा sk_buff_head *inputq)
अणु
	u32 self = tipc_own_addr(net);
	काष्ठा sk_buff *skb, *_skb;
	u32 portid, onode;
	काष्ठा sk_buff_head पंचांगpq;
	काष्ठा list_head dports;
	काष्ठा tipc_msg *hdr;
	काष्ठा tipc_uaddr ua;
	पूर्णांक user, mtyp, hlen;
	bool exact;

	__skb_queue_head_init(&पंचांगpq);
	INIT_LIST_HEAD(&dports);
	ua.addrtype = TIPC_SERVICE_RANGE;

	skb = tipc_skb_peek(arrvq, &inputq->lock);
	क्रम (; skb; skb = tipc_skb_peek(arrvq, &inputq->lock)) अणु
		hdr = buf_msg(skb);
		user = msg_user(hdr);
		mtyp = msg_type(hdr);
		hlen = skb_headroom(skb) + msg_hdr_sz(hdr);
		onode = msg_orignode(hdr);
		ua.sr.type = msg_nametype(hdr);

		अगर (mtyp == TIPC_GRP_UCAST_MSG || user == GROUP_PROTOCOL) अणु
			spin_lock_bh(&inputq->lock);
			अगर (skb_peek(arrvq) == skb) अणु
				__skb_dequeue(arrvq);
				__skb_queue_tail(inputq, skb);
			पूर्ण
			kमुक्त_skb(skb);
			spin_unlock_bh(&inputq->lock);
			जारी;
		पूर्ण

		/* Group messages require exact scope match */
		अगर (msg_in_group(hdr)) अणु
			ua.sr.lower = 0;
			ua.sr.upper = ~0;
			ua.scope = msg_lookup_scope(hdr);
			exact = true;
		पूर्ण अन्यथा अणु
			/* TIPC_NODE_SCOPE means "any scope" in this context */
			अगर (onode == self)
				ua.scope = TIPC_NODE_SCOPE;
			अन्यथा
				ua.scope = TIPC_CLUSTER_SCOPE;
			exact = false;
			ua.sr.lower = msg_namelower(hdr);
			ua.sr.upper = msg_nameupper(hdr);
		पूर्ण

		/* Create destination port list: */
		tipc_nametbl_lookup_mcast_sockets(net, &ua, exact, &dports);

		/* Clone message per destination */
		जबतक (tipc_dest_pop(&dports, शून्य, &portid)) अणु
			_skb = __pskb_copy(skb, hlen, GFP_ATOMIC);
			अगर (_skb) अणु
				msg_set_destport(buf_msg(_skb), portid);
				__skb_queue_tail(&पंचांगpq, _skb);
				जारी;
			पूर्ण
			pr_warn("Failed to clone mcast rcv buffer\n");
		पूर्ण
		/* Append to inputq अगर not alपढ़ोy करोne by other thपढ़ो */
		spin_lock_bh(&inputq->lock);
		अगर (skb_peek(arrvq) == skb) अणु
			skb_queue_splice_tail_init(&पंचांगpq, inputq);
			/* Decrease the skb's refcnt as increasing in the
			 * function tipc_skb_peek
			 */
			kमुक्त_skb(__skb_dequeue(arrvq));
		पूर्ण
		spin_unlock_bh(&inputq->lock);
		__skb_queue_purge(&पंचांगpq);
		kमुक्त_skb(skb);
	पूर्ण
	tipc_sk_rcv(net, inputq);
पूर्ण

/* tipc_sk_push_backlog(): send accumulated buffers in socket ग_लिखो queue
 *                         when socket is in Nagle mode
 */
अटल व्योम tipc_sk_push_backlog(काष्ठा tipc_sock *tsk, bool nagle_ack)
अणु
	काष्ठा sk_buff_head *txq = &tsk->sk.sk_ग_लिखो_queue;
	काष्ठा sk_buff *skb = skb_peek_tail(txq);
	काष्ठा net *net = sock_net(&tsk->sk);
	u32 dnode = tsk_peer_node(tsk);
	पूर्णांक rc;

	अगर (nagle_ack) अणु
		tsk->pkt_cnt += skb_queue_len(txq);
		अगर (!tsk->pkt_cnt || tsk->msg_acc / tsk->pkt_cnt < 2) अणु
			tsk->oneway = 0;
			अगर (tsk->nagle_start < NAGLE_START_MAX)
				tsk->nagle_start *= 2;
			tsk->expect_ack = false;
			pr_debug("tsk %10u: bad nagle %u -> %u, next start %u!\n",
				 tsk->portid, tsk->msg_acc, tsk->pkt_cnt,
				 tsk->nagle_start);
		पूर्ण अन्यथा अणु
			tsk->nagle_start = NAGLE_START_INIT;
			अगर (skb) अणु
				msg_set_ack_required(buf_msg(skb));
				tsk->expect_ack = true;
			पूर्ण अन्यथा अणु
				tsk->expect_ack = false;
			पूर्ण
		पूर्ण
		tsk->msg_acc = 0;
		tsk->pkt_cnt = 0;
	पूर्ण

	अगर (!skb || tsk->cong_link_cnt)
		वापस;

	/* Do not send SYN again after congestion */
	अगर (msg_is_syn(buf_msg(skb)))
		वापस;

	अगर (tsk->msg_acc)
		tsk->pkt_cnt += skb_queue_len(txq);
	tsk->snt_unacked += tsk->snd_backlog;
	tsk->snd_backlog = 0;
	rc = tipc_node_xmit(net, txq, dnode, tsk->portid);
	अगर (rc == -ELINKCONG)
		tsk->cong_link_cnt = 1;
पूर्ण

/**
 * tipc_sk_conn_proto_rcv - receive a connection mng protocol message
 * @tsk: receiving socket
 * @skb: poपूर्णांकer to message buffer.
 * @inputq: buffer list containing the buffers
 * @xmitq: output message area
 */
अटल व्योम tipc_sk_conn_proto_rcv(काष्ठा tipc_sock *tsk, काष्ठा sk_buff *skb,
				   काष्ठा sk_buff_head *inputq,
				   काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	u32 onode = tsk_own_node(tsk);
	काष्ठा sock *sk = &tsk->sk;
	पूर्णांक mtyp = msg_type(hdr);
	bool was_cong;

	/* Ignore अगर connection cannot be validated: */
	अगर (!tsk_peer_msg(tsk, hdr)) अणु
		trace_tipc_sk_drop_msg(sk, skb, TIPC_DUMP_NONE, "@proto_rcv!");
		जाओ निकास;
	पूर्ण

	अगर (unlikely(msg_errcode(hdr))) अणु
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
		tipc_node_हटाओ_conn(sock_net(sk), tsk_peer_node(tsk),
				      tsk_peer_port(tsk));
		sk->sk_state_change(sk);

		/* State change is ignored अगर socket alपढ़ोy awake,
		 * - convert msg to पात msg and add to inqueue
		 */
		msg_set_user(hdr, TIPC_CRITICAL_IMPORTANCE);
		msg_set_type(hdr, TIPC_CONN_MSG);
		msg_set_size(hdr, BASIC_H_SIZE);
		msg_set_hdr_sz(hdr, BASIC_H_SIZE);
		__skb_queue_tail(inputq, skb);
		वापस;
	पूर्ण

	tsk->probe_unacked = false;

	अगर (mtyp == CONN_PROBE) अणु
		msg_set_type(hdr, CONN_PROBE_REPLY);
		अगर (tipc_msg_reverse(onode, &skb, TIPC_OK))
			__skb_queue_tail(xmitq, skb);
		वापस;
	पूर्ण अन्यथा अगर (mtyp == CONN_ACK) अणु
		was_cong = tsk_conn_cong(tsk);
		tipc_sk_push_backlog(tsk, msg_nagle_ack(hdr));
		tsk->snt_unacked -= msg_conn_ack(hdr);
		अगर (tsk->peer_caps & TIPC_BLOCK_FLOWCTL)
			tsk->snd_win = msg_adv_win(hdr);
		अगर (was_cong && !tsk_conn_cong(tsk))
			sk->sk_ग_लिखो_space(sk);
	पूर्ण अन्यथा अगर (mtyp != CONN_PROBE_REPLY) अणु
		pr_warn("Received unknown CONN_PROTO msg\n");
	पूर्ण
निकास:
	kमुक्त_skb(skb);
पूर्ण

/**
 * tipc_sendmsg - send message in connectionless manner
 * @sock: socket काष्ठाure
 * @m: message to send
 * @dsz: amount of user data to be sent
 *
 * Message must have an destination specअगरied explicitly.
 * Used क्रम SOCK_RDM and SOCK_DGRAM messages,
 * and क्रम 'SYN' messages on SOCK_SEQPACKET and SOCK_STREAM connections.
 * (Note: 'SYN+' is prohibited on SOCK_STREAM.)
 *
 * Return: the number of bytes sent on success, or त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_sendmsg(काष्ठा socket *sock,
			काष्ठा msghdr *m, माप_प्रकार dsz)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक ret;

	lock_sock(sk);
	ret = __tipc_sendmsg(sock, m, dsz);
	release_sock(sk);

	वापस ret;
पूर्ण

अटल पूर्णांक __tipc_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार dlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_uaddr *ua = (काष्ठा tipc_uaddr *)m->msg_name;
	दीर्घ समयout = sock_sndसमयo(sk, m->msg_flags & MSG_DONTWAIT);
	काष्ठा list_head *clinks = &tsk->cong_links;
	bool syn = !tipc_sk_type_connectionless(sk);
	काष्ठा tipc_group *grp = tsk->group;
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	काष्ठा tipc_socket_addr skaddr;
	काष्ठा sk_buff_head pkts;
	पूर्णांक atype, mtu, rc;

	अगर (unlikely(dlen > TIPC_MAX_USER_MSG_SIZE))
		वापस -EMSGSIZE;

	अगर (ua) अणु
		अगर (!tipc_uaddr_valid(ua, m->msg_namelen))
			वापस -EINVAL;
		 atype = ua->addrtype;
	पूर्ण

	/* If socket beदीर्घs to a communication group follow other paths */
	अगर (grp) अणु
		अगर (!ua)
			वापस tipc_send_group_bcast(sock, m, dlen, समयout);
		अगर (atype == TIPC_SERVICE_ADDR)
			वापस tipc_send_group_anycast(sock, m, dlen, समयout);
		अगर (atype == TIPC_SOCKET_ADDR)
			वापस tipc_send_group_unicast(sock, m, dlen, समयout);
		अगर (atype == TIPC_SERVICE_RANGE)
			वापस tipc_send_group_mcast(sock, m, dlen, समयout);
		वापस -EINVAL;
	पूर्ण

	अगर (!ua) अणु
		ua = (काष्ठा tipc_uaddr *)&tsk->peer;
		अगर (!syn && ua->family != AF_TIPC)
			वापस -EDESTADDRREQ;
		atype = ua->addrtype;
	पूर्ण

	अगर (unlikely(syn)) अणु
		अगर (sk->sk_state == TIPC_LISTEN)
			वापस -EPIPE;
		अगर (sk->sk_state != TIPC_OPEN)
			वापस -EISCONN;
		अगर (tsk->published)
			वापस -EOPNOTSUPP;
		अगर (atype == TIPC_SERVICE_ADDR) अणु
			tsk->conn_type = ua->sa.type;
			tsk->conn_instance = ua->sa.instance;
		पूर्ण
		msg_set_syn(hdr, 1);
	पूर्ण

	/* Determine destination */
	अगर (atype == TIPC_SERVICE_RANGE) अणु
		वापस tipc_sendmcast(sock, ua, m, dlen, समयout);
	पूर्ण अन्यथा अगर (atype == TIPC_SERVICE_ADDR) अणु
		skaddr.node = ua->lookup_node;
		ua->scope = tipc_node2scope(skaddr.node);
		अगर (!tipc_nametbl_lookup_anycast(net, ua, &skaddr))
			वापस -EHOSTUNREACH;
	पूर्ण अन्यथा अगर (atype == TIPC_SOCKET_ADDR) अणु
		skaddr = ua->sk;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* Block or वापस अगर destination link is congested */
	rc = tipc_रुको_क्रम_cond(sock, &समयout,
				!tipc_dest_find(clinks, skaddr.node, 0));
	अगर (unlikely(rc))
		वापस rc;

	/* Finally build message header */
	msg_set_destnode(hdr, skaddr.node);
	msg_set_destport(hdr, skaddr.ref);
	अगर (atype == TIPC_SERVICE_ADDR) अणु
		msg_set_type(hdr, TIPC_NAMED_MSG);
		msg_set_hdr_sz(hdr, NAMED_H_SIZE);
		msg_set_nametype(hdr, ua->sa.type);
		msg_set_nameinst(hdr, ua->sa.instance);
		msg_set_lookup_scope(hdr, ua->scope);
	पूर्ण अन्यथा अणु /* TIPC_SOCKET_ADDR */
		msg_set_type(hdr, TIPC_सूचीECT_MSG);
		msg_set_lookup_scope(hdr, 0);
		msg_set_hdr_sz(hdr, BASIC_H_SIZE);
	पूर्ण

	/* Add message body */
	__skb_queue_head_init(&pkts);
	mtu = tipc_node_get_mtu(net, skaddr.node, tsk->portid, true);
	rc = tipc_msg_build(hdr, m, 0, dlen, mtu, &pkts);
	अगर (unlikely(rc != dlen))
		वापस rc;
	अगर (unlikely(syn && !tipc_msg_skb_clone(&pkts, &sk->sk_ग_लिखो_queue))) अणु
		__skb_queue_purge(&pkts);
		वापस -ENOMEM;
	पूर्ण

	/* Send message */
	trace_tipc_sk_sendmsg(sk, skb_peek(&pkts), TIPC_DUMP_SK_SNDQ, " ");
	rc = tipc_node_xmit(net, &pkts, skaddr.node, tsk->portid);
	अगर (unlikely(rc == -ELINKCONG)) अणु
		tipc_dest_push(clinks, skaddr.node, 0);
		tsk->cong_link_cnt++;
		rc = 0;
	पूर्ण

	अगर (unlikely(syn && !rc))
		tipc_set_sk_state(sk, TIPC_CONNECTING);

	वापस rc ? rc : dlen;
पूर्ण

/**
 * tipc_sendstream - send stream-oriented data
 * @sock: socket काष्ठाure
 * @m: data to send
 * @dsz: total length of data to be transmitted
 *
 * Used क्रम SOCK_STREAM data.
 *
 * Return: the number of bytes sent on success (or partial success),
 * or त्रुटि_सं अगर no data sent
 */
अटल पूर्णांक tipc_sendstream(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार dsz)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक ret;

	lock_sock(sk);
	ret = __tipc_sendstream(sock, m, dsz);
	release_sock(sk);

	वापस ret;
पूर्ण

अटल पूर्णांक __tipc_sendstream(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार dlen)
अणु
	काष्ठा sock *sk = sock->sk;
	DECLARE_SOCKADDR(काष्ठा sockaddr_tipc *, dest, m->msg_name);
	दीर्घ समयout = sock_sndसमयo(sk, m->msg_flags & MSG_DONTWAIT);
	काष्ठा sk_buff_head *txq = &sk->sk_ग_लिखो_queue;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	काष्ठा net *net = sock_net(sk);
	काष्ठा sk_buff *skb;
	u32 dnode = tsk_peer_node(tsk);
	पूर्णांक maxnagle = tsk->maxnagle;
	पूर्णांक maxpkt = tsk->max_pkt;
	पूर्णांक send, sent = 0;
	पूर्णांक blocks, rc = 0;

	अगर (unlikely(dlen > पूर्णांक_उच्च))
		वापस -EMSGSIZE;

	/* Handle implicit connection setup */
	अगर (unlikely(dest)) अणु
		rc = __tipc_sendmsg(sock, m, dlen);
		अगर (dlen && dlen == rc) अणु
			tsk->peer_caps = tipc_node_get_capabilities(net, dnode);
			tsk->snt_unacked = tsk_inc(tsk, dlen + msg_hdr_sz(hdr));
		पूर्ण
		वापस rc;
	पूर्ण

	करो अणु
		rc = tipc_रुको_क्रम_cond(sock, &समयout,
					(!tsk->cong_link_cnt &&
					 !tsk_conn_cong(tsk) &&
					 tipc_sk_connected(sk)));
		अगर (unlikely(rc))
			अवरोध;
		send = min_t(माप_प्रकार, dlen - sent, TIPC_MAX_USER_MSG_SIZE);
		blocks = tsk->snd_backlog;
		अगर (tsk->oneway++ >= tsk->nagle_start && maxnagle &&
		    send <= maxnagle) अणु
			rc = tipc_msg_append(hdr, m, send, maxnagle, txq);
			अगर (unlikely(rc < 0))
				अवरोध;
			blocks += rc;
			tsk->msg_acc++;
			अगर (blocks <= 64 && tsk->expect_ack) अणु
				tsk->snd_backlog = blocks;
				sent += send;
				अवरोध;
			पूर्ण अन्यथा अगर (blocks > 64) अणु
				tsk->pkt_cnt += skb_queue_len(txq);
			पूर्ण अन्यथा अणु
				skb = skb_peek_tail(txq);
				अगर (skb) अणु
					msg_set_ack_required(buf_msg(skb));
					tsk->expect_ack = true;
				पूर्ण अन्यथा अणु
					tsk->expect_ack = false;
				पूर्ण
				tsk->msg_acc = 0;
				tsk->pkt_cnt = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = tipc_msg_build(hdr, m, sent, send, maxpkt, txq);
			अगर (unlikely(rc != send))
				अवरोध;
			blocks += tsk_inc(tsk, send + MIN_H_SIZE);
		पूर्ण
		trace_tipc_sk_sendstream(sk, skb_peek(txq),
					 TIPC_DUMP_SK_SNDQ, " ");
		rc = tipc_node_xmit(net, txq, dnode, tsk->portid);
		अगर (unlikely(rc == -ELINKCONG)) अणु
			tsk->cong_link_cnt = 1;
			rc = 0;
		पूर्ण
		अगर (likely(!rc)) अणु
			tsk->snt_unacked += blocks;
			tsk->snd_backlog = 0;
			sent += send;
		पूर्ण
	पूर्ण जबतक (sent < dlen && !rc);

	वापस sent ? sent : rc;
पूर्ण

/**
 * tipc_send_packet - send a connection-oriented message
 * @sock: socket काष्ठाure
 * @m: message to send
 * @dsz: length of data to be transmitted
 *
 * Used क्रम SOCK_SEQPACKET messages.
 *
 * Return: the number of bytes sent on success, or त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_send_packet(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार dsz)
अणु
	अगर (dsz > TIPC_MAX_USER_MSG_SIZE)
		वापस -EMSGSIZE;

	वापस tipc_sendstream(sock, m, dsz);
पूर्ण

/* tipc_sk_finish_conn - complete the setup of a connection
 */
अटल व्योम tipc_sk_finish_conn(काष्ठा tipc_sock *tsk, u32 peer_port,
				u32 peer_node)
अणु
	काष्ठा sock *sk = &tsk->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा tipc_msg *msg = &tsk->phdr;

	msg_set_syn(msg, 0);
	msg_set_destnode(msg, peer_node);
	msg_set_destport(msg, peer_port);
	msg_set_type(msg, TIPC_CONN_MSG);
	msg_set_lookup_scope(msg, 0);
	msg_set_hdr_sz(msg, SHORT_H_SIZE);

	sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + CONN_PROBING_INTV);
	tipc_set_sk_state(sk, TIPC_ESTABLISHED);
	tipc_node_add_conn(net, peer_node, tsk->portid, peer_port);
	tsk->max_pkt = tipc_node_get_mtu(net, peer_node, tsk->portid, true);
	tsk->peer_caps = tipc_node_get_capabilities(net, peer_node);
	tsk_set_nagle(tsk);
	__skb_queue_purge(&sk->sk_ग_लिखो_queue);
	अगर (tsk->peer_caps & TIPC_BLOCK_FLOWCTL)
		वापस;

	/* Fall back to message based flow control */
	tsk->rcv_win = FLOWCTL_MSG_WIN;
	tsk->snd_win = FLOWCTL_MSG_WIN;
पूर्ण

/**
 * tipc_sk_set_orig_addr - capture sender's address क्रम received message
 * @m: descriptor क्रम message info
 * @skb: received message
 *
 * Note: Address is not captured अगर not requested by receiver.
 */
अटल व्योम tipc_sk_set_orig_addr(काष्ठा msghdr *m, काष्ठा sk_buff *skb)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_pair *, srcaddr, m->msg_name);
	काष्ठा tipc_msg *hdr = buf_msg(skb);

	अगर (!srcaddr)
		वापस;

	srcaddr->sock.family = AF_TIPC;
	srcaddr->sock.addrtype = TIPC_SOCKET_ADDR;
	srcaddr->sock.scope = 0;
	srcaddr->sock.addr.id.ref = msg_origport(hdr);
	srcaddr->sock.addr.id.node = msg_orignode(hdr);
	srcaddr->sock.addr.name.करोमुख्य = 0;
	m->msg_namelen = माप(काष्ठा sockaddr_tipc);

	अगर (!msg_in_group(hdr))
		वापस;

	/* Group message users may also want to know sending member's id */
	srcaddr->member.family = AF_TIPC;
	srcaddr->member.addrtype = TIPC_SERVICE_ADDR;
	srcaddr->member.scope = 0;
	srcaddr->member.addr.name.name.type = msg_nametype(hdr);
	srcaddr->member.addr.name.name.instance = TIPC_SKB_CB(skb)->orig_member;
	srcaddr->member.addr.name.करोमुख्य = 0;
	m->msg_namelen = माप(*srcaddr);
पूर्ण

/**
 * tipc_sk_anc_data_recv - optionally capture ancillary data क्रम received message
 * @m: descriptor क्रम message info
 * @skb: received message buffer
 * @tsk: TIPC port associated with message
 *
 * Note: Ancillary data is not captured अगर not requested by receiver.
 *
 * Return: 0 अगर successful, otherwise त्रुटि_सं
 */
अटल पूर्णांक tipc_sk_anc_data_recv(काष्ठा msghdr *m, काष्ठा sk_buff *skb,
				 काष्ठा tipc_sock *tsk)
अणु
	काष्ठा tipc_msg *msg;
	u32 anc_data[3];
	u32 err;
	u32 dest_type;
	पूर्णांक has_name;
	पूर्णांक res;

	अगर (likely(m->msg_controllen == 0))
		वापस 0;
	msg = buf_msg(skb);

	/* Optionally capture errored message object(s) */
	err = msg ? msg_errcode(msg) : 0;
	अगर (unlikely(err)) अणु
		anc_data[0] = err;
		anc_data[1] = msg_data_sz(msg);
		res = put_cmsg(m, SOL_TIPC, TIPC_ERRINFO, 8, anc_data);
		अगर (res)
			वापस res;
		अगर (anc_data[1]) अणु
			अगर (skb_linearize(skb))
				वापस -ENOMEM;
			msg = buf_msg(skb);
			res = put_cmsg(m, SOL_TIPC, TIPC_RETDATA, anc_data[1],
				       msg_data(msg));
			अगर (res)
				वापस res;
		पूर्ण
	पूर्ण

	/* Optionally capture message destination object */
	dest_type = msg ? msg_type(msg) : TIPC_सूचीECT_MSG;
	चयन (dest_type) अणु
	हाल TIPC_NAMED_MSG:
		has_name = 1;
		anc_data[0] = msg_nametype(msg);
		anc_data[1] = msg_namelower(msg);
		anc_data[2] = msg_namelower(msg);
		अवरोध;
	हाल TIPC_MCAST_MSG:
		has_name = 1;
		anc_data[0] = msg_nametype(msg);
		anc_data[1] = msg_namelower(msg);
		anc_data[2] = msg_nameupper(msg);
		अवरोध;
	हाल TIPC_CONN_MSG:
		has_name = (tsk->conn_type != 0);
		anc_data[0] = tsk->conn_type;
		anc_data[1] = tsk->conn_instance;
		anc_data[2] = tsk->conn_instance;
		अवरोध;
	शेष:
		has_name = 0;
	पूर्ण
	अगर (has_name) अणु
		res = put_cmsg(m, SOL_TIPC, TIPC_DESTNAME, 12, anc_data);
		अगर (res)
			वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *tipc_sk_build_ack(काष्ठा tipc_sock *tsk)
अणु
	काष्ठा sock *sk = &tsk->sk;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा tipc_msg *msg;
	u32 peer_port = tsk_peer_port(tsk);
	u32 dnode = tsk_peer_node(tsk);

	अगर (!tipc_sk_connected(sk))
		वापस शून्य;
	skb = tipc_msg_create(CONN_MANAGER, CONN_ACK, INT_H_SIZE, 0,
			      dnode, tsk_own_node(tsk), peer_port,
			      tsk->portid, TIPC_OK);
	अगर (!skb)
		वापस शून्य;
	msg = buf_msg(skb);
	msg_set_conn_ack(msg, tsk->rcv_unacked);
	tsk->rcv_unacked = 0;

	/* Adjust to and advertize the correct winकरोw limit */
	अगर (tsk->peer_caps & TIPC_BLOCK_FLOWCTL) अणु
		tsk->rcv_win = tsk_adv_blocks(tsk->sk.sk_rcvbuf);
		msg_set_adv_win(msg, tsk->rcv_win);
	पूर्ण
	वापस skb;
पूर्ण

अटल व्योम tipc_sk_send_ack(काष्ठा tipc_sock *tsk)
अणु
	काष्ठा sk_buff *skb;

	skb = tipc_sk_build_ack(tsk);
	अगर (!skb)
		वापस;

	tipc_node_xmit_skb(sock_net(&tsk->sk), skb, tsk_peer_node(tsk),
			   msg_link_selector(buf_msg(skb)));
पूर्ण

अटल पूर्णांक tipc_रुको_क्रम_rcvmsg(काष्ठा socket *sock, दीर्घ *समयop)
अणु
	काष्ठा sock *sk = sock->sk;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	दीर्घ समयo = *समयop;
	पूर्णांक err = sock_error(sk);

	अगर (err)
		वापस err;

	क्रम (;;) अणु
		अगर (समयo && skb_queue_empty(&sk->sk_receive_queue)) अणु
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
				err = -ENOTCONN;
				अवरोध;
			पूर्ण
			add_रुको_queue(sk_sleep(sk), &रुको);
			release_sock(sk);
			समयo = रुको_woken(&रुको, TASK_INTERRUPTIBLE, समयo);
			sched_annotate_sleep();
			lock_sock(sk);
			हटाओ_रुको_queue(sk_sleep(sk), &रुको);
		पूर्ण
		err = 0;
		अगर (!skb_queue_empty(&sk->sk_receive_queue))
			अवरोध;
		err = -EAGAIN;
		अगर (!समयo)
			अवरोध;
		err = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			अवरोध;

		err = sock_error(sk);
		अगर (err)
			अवरोध;
	पूर्ण
	*समयop = समयo;
	वापस err;
पूर्ण

/**
 * tipc_recvmsg - receive packet-oriented message
 * @sock: network socket
 * @m: descriptor क्रम message info
 * @buflen: length of user buffer area
 * @flags: receive flags
 *
 * Used क्रम SOCK_DGRAM, SOCK_RDM, and SOCK_SEQPACKET messages.
 * If the complete message करोesn't fit in user area, truncate it.
 *
 * Return: size of वापसed message data, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
			माप_प्रकार buflen,	पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	bool connected = !tipc_sk_type_connectionless(sk);
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	पूर्णांक rc, err, hlen, dlen, copy;
	काष्ठा sk_buff_head xmitq;
	काष्ठा tipc_msg *hdr;
	काष्ठा sk_buff *skb;
	bool grp_evt;
	दीर्घ समयout;

	/* Catch invalid receive requests */
	अगर (unlikely(!buflen))
		वापस -EINVAL;

	lock_sock(sk);
	अगर (unlikely(connected && sk->sk_state == TIPC_OPEN)) अणु
		rc = -ENOTCONN;
		जाओ निकास;
	पूर्ण
	समयout = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	/* Step rcv queue to first msg with data or error; रुको अगर necessary */
	करो अणु
		rc = tipc_रुको_क्रम_rcvmsg(sock, &समयout);
		अगर (unlikely(rc))
			जाओ निकास;
		skb = skb_peek(&sk->sk_receive_queue);
		hdr = buf_msg(skb);
		dlen = msg_data_sz(hdr);
		hlen = msg_hdr_sz(hdr);
		err = msg_errcode(hdr);
		grp_evt = msg_is_grp_evt(hdr);
		अगर (likely(dlen || err))
			अवरोध;
		tsk_advance_rx_queue(sk);
	पूर्ण जबतक (1);

	/* Collect msg meta data, including error code and rejected data */
	tipc_sk_set_orig_addr(m, skb);
	rc = tipc_sk_anc_data_recv(m, skb, tsk);
	अगर (unlikely(rc))
		जाओ निकास;
	hdr = buf_msg(skb);

	/* Capture data अगर non-error msg, otherwise just set वापस value */
	अगर (likely(!err)) अणु
		copy = min_t(पूर्णांक, dlen, buflen);
		अगर (unlikely(copy != dlen))
			m->msg_flags |= MSG_TRUNC;
		rc = skb_copy_datagram_msg(skb, hlen, m, copy);
	पूर्ण अन्यथा अणु
		copy = 0;
		rc = 0;
		अगर (err != TIPC_CONN_SHUTDOWN && connected && !m->msg_control)
			rc = -ECONNRESET;
	पूर्ण
	अगर (unlikely(rc))
		जाओ निकास;

	/* Mark message as group event अगर applicable */
	अगर (unlikely(grp_evt)) अणु
		अगर (msg_grp_evt(hdr) == TIPC_WITHDRAWN)
			m->msg_flags |= MSG_EOR;
		m->msg_flags |= MSG_OOB;
		copy = 0;
	पूर्ण

	/* Caption of data or error code/rejected data was successful */
	अगर (unlikely(flags & MSG_PEEK))
		जाओ निकास;

	/* Send group flow control advertisement when applicable */
	अगर (tsk->group && msg_in_group(hdr) && !grp_evt) अणु
		__skb_queue_head_init(&xmitq);
		tipc_group_update_rcv_win(tsk->group, tsk_blocks(hlen + dlen),
					  msg_orignode(hdr), msg_origport(hdr),
					  &xmitq);
		tipc_node_distr_xmit(sock_net(sk), &xmitq);
	पूर्ण

	tsk_advance_rx_queue(sk);

	अगर (likely(!connected))
		जाओ निकास;

	/* Send connection flow control advertisement when applicable */
	tsk->rcv_unacked += tsk_inc(tsk, hlen + dlen);
	अगर (tsk->rcv_unacked >= tsk->rcv_win / TIPC_ACK_RATE)
		tipc_sk_send_ack(tsk);
निकास:
	release_sock(sk);
	वापस rc ? rc : copy;
पूर्ण

/**
 * tipc_recvstream - receive stream-oriented data
 * @sock: network socket
 * @m: descriptor क्रम message info
 * @buflen: total size of user buffer area
 * @flags: receive flags
 *
 * Used क्रम SOCK_STREAM messages only.  If not enough data is available
 * will optionally रुको क्रम more; never truncates data.
 *
 * Return: size of वापसed message data, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_recvstream(काष्ठा socket *sock, काष्ठा msghdr *m,
			   माप_प्रकार buflen, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा tipc_msg *hdr;
	काष्ठा tipc_skb_cb *skb_cb;
	bool peek = flags & MSG_PEEK;
	पूर्णांक offset, required, copy, copied = 0;
	पूर्णांक hlen, dlen, err, rc;
	दीर्घ समयout;

	/* Catch invalid receive attempts */
	अगर (unlikely(!buflen))
		वापस -EINVAL;

	lock_sock(sk);

	अगर (unlikely(sk->sk_state == TIPC_OPEN)) अणु
		rc = -ENOTCONN;
		जाओ निकास;
	पूर्ण
	required = sock_rcvlowat(sk, flags & MSG_WAITALL, buflen);
	समयout = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	करो अणु
		/* Look at first msg in receive queue; रुको अगर necessary */
		rc = tipc_रुको_क्रम_rcvmsg(sock, &समयout);
		अगर (unlikely(rc))
			अवरोध;
		skb = skb_peek(&sk->sk_receive_queue);
		skb_cb = TIPC_SKB_CB(skb);
		hdr = buf_msg(skb);
		dlen = msg_data_sz(hdr);
		hlen = msg_hdr_sz(hdr);
		err = msg_errcode(hdr);

		/* Discard any empty non-errored (SYN-) message */
		अगर (unlikely(!dlen && !err)) अणु
			tsk_advance_rx_queue(sk);
			जारी;
		पूर्ण

		/* Collect msg meta data, incl. error code and rejected data */
		अगर (!copied) अणु
			tipc_sk_set_orig_addr(m, skb);
			rc = tipc_sk_anc_data_recv(m, skb, tsk);
			अगर (rc)
				अवरोध;
			hdr = buf_msg(skb);
		पूर्ण

		/* Copy data अगर msg ok, otherwise वापस error/partial data */
		अगर (likely(!err)) अणु
			offset = skb_cb->bytes_पढ़ो;
			copy = min_t(पूर्णांक, dlen - offset, buflen - copied);
			rc = skb_copy_datagram_msg(skb, hlen + offset, m, copy);
			अगर (unlikely(rc))
				अवरोध;
			copied += copy;
			offset += copy;
			अगर (unlikely(offset < dlen)) अणु
				अगर (!peek)
					skb_cb->bytes_पढ़ो = offset;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = 0;
			अगर ((err != TIPC_CONN_SHUTDOWN) && !m->msg_control)
				rc = -ECONNRESET;
			अगर (copied || rc)
				अवरोध;
		पूर्ण

		अगर (unlikely(peek))
			अवरोध;

		tsk_advance_rx_queue(sk);

		/* Send connection flow control advertisement when applicable */
		tsk->rcv_unacked += tsk_inc(tsk, hlen + dlen);
		अगर (tsk->rcv_unacked >= tsk->rcv_win / TIPC_ACK_RATE)
			tipc_sk_send_ack(tsk);

		/* Exit अगर all requested data or FIN/error received */
		अगर (copied == buflen || err)
			अवरोध;

	पूर्ण जबतक (!skb_queue_empty(&sk->sk_receive_queue) || copied < required);
निकास:
	release_sock(sk);
	वापस copied ? copied : rc;
पूर्ण

/**
 * tipc_ग_लिखो_space - wake up thपढ़ो अगर port congestion is released
 * @sk: socket
 */
अटल व्योम tipc_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLOUT |
						EPOLLWRNORM | EPOLLWRBAND);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * tipc_data_पढ़ोy - wake up thपढ़ोs to indicate messages have been received
 * @sk: socket
 */
अटल व्योम tipc_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_sync_poll(&wq->रुको, EPOLLIN |
						EPOLLRDNORM | EPOLLRDBAND);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम tipc_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	__skb_queue_purge(&sk->sk_receive_queue);
पूर्ण

अटल व्योम tipc_sk_proto_rcv(काष्ठा sock *sk,
			      काष्ठा sk_buff_head *inputq,
			      काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा sk_buff *skb = __skb_dequeue(inputq);
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	काष्ठा tipc_group *grp = tsk->group;
	bool wakeup = false;

	चयन (msg_user(hdr)) अणु
	हाल CONN_MANAGER:
		tipc_sk_conn_proto_rcv(tsk, skb, inputq, xmitq);
		वापस;
	हाल SOCK_WAKEUP:
		tipc_dest_del(&tsk->cong_links, msg_orignode(hdr), 0);
		/* coupled with smp_rmb() in tipc_रुको_क्रम_cond() */
		smp_wmb();
		tsk->cong_link_cnt--;
		wakeup = true;
		tipc_sk_push_backlog(tsk, false);
		अवरोध;
	हाल GROUP_PROTOCOL:
		tipc_group_proto_rcv(grp, &wakeup, hdr, inputq, xmitq);
		अवरोध;
	हाल TOP_SRV:
		tipc_group_member_evt(tsk->group, &wakeup, &sk->sk_rcvbuf,
				      hdr, inputq, xmitq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (wakeup)
		sk->sk_ग_लिखो_space(sk);

	kमुक्त_skb(skb);
पूर्ण

/**
 * tipc_sk_filter_connect - check incoming message क्रम a connection-based socket
 * @tsk: TIPC socket
 * @skb: poपूर्णांकer to message buffer.
 * @xmitq: क्रम Nagle ACK अगर any
 * Return: true अगर message should be added to receive queue, false otherwise
 */
अटल bool tipc_sk_filter_connect(काष्ठा tipc_sock *tsk, काष्ठा sk_buff *skb,
				   काष्ठा sk_buff_head *xmitq)
अणु
	काष्ठा sock *sk = &tsk->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	bool con_msg = msg_connected(hdr);
	u32 pport = tsk_peer_port(tsk);
	u32 pnode = tsk_peer_node(tsk);
	u32 oport = msg_origport(hdr);
	u32 onode = msg_orignode(hdr);
	पूर्णांक err = msg_errcode(hdr);
	अचिन्हित दीर्घ delay;

	अगर (unlikely(msg_mcast(hdr)))
		वापस false;
	tsk->oneway = 0;

	चयन (sk->sk_state) अणु
	हाल TIPC_CONNECTING:
		/* Setup ACK */
		अगर (likely(con_msg)) अणु
			अगर (err)
				अवरोध;
			tipc_sk_finish_conn(tsk, oport, onode);
			msg_set_importance(&tsk->phdr, msg_importance(hdr));
			/* ACK+ message with data is added to receive queue */
			अगर (msg_data_sz(hdr))
				वापस true;
			/* Empty ACK-, - wake up sleeping connect() and drop */
			sk->sk_state_change(sk);
			msg_set_dest_droppable(hdr, 1);
			वापस false;
		पूर्ण
		/* Ignore connectionless message अगर not from listening socket */
		अगर (oport != pport || onode != pnode)
			वापस false;

		/* Rejected SYN */
		अगर (err != TIPC_ERR_OVERLOAD)
			अवरोध;

		/* Prepare क्रम new setup attempt अगर we have a SYN clone */
		अगर (skb_queue_empty(&sk->sk_ग_लिखो_queue))
			अवरोध;
		get_अक्रमom_bytes(&delay, 2);
		delay %= (tsk->conn_समयout / 4);
		delay = msecs_to_jअगरfies(delay + 100);
		sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + delay);
		वापस false;
	हाल TIPC_OPEN:
	हाल TIPC_DISCONNECTING:
		वापस false;
	हाल TIPC_LISTEN:
		/* Accept only SYN message */
		अगर (!msg_is_syn(hdr) &&
		    tipc_node_get_capabilities(net, onode) & TIPC_SYN_BIT)
			वापस false;
		अगर (!con_msg && !err)
			वापस true;
		वापस false;
	हाल TIPC_ESTABLISHED:
		अगर (!skb_queue_empty(&sk->sk_ग_लिखो_queue))
			tipc_sk_push_backlog(tsk, false);
		/* Accept only connection-based messages sent by peer */
		अगर (likely(con_msg && !err && pport == oport &&
			   pnode == onode)) अणु
			अगर (msg_ack_required(hdr)) अणु
				काष्ठा sk_buff *skb;

				skb = tipc_sk_build_ack(tsk);
				अगर (skb) अणु
					msg_set_nagle_ack(buf_msg(skb));
					__skb_queue_tail(xmitq, skb);
				पूर्ण
			पूर्ण
			वापस true;
		पूर्ण
		अगर (!tsk_peer_msg(tsk, hdr))
			वापस false;
		अगर (!err)
			वापस true;
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
		tipc_node_हटाओ_conn(net, pnode, tsk->portid);
		sk->sk_state_change(sk);
		वापस true;
	शेष:
		pr_err("Unknown sk_state %u\n", sk->sk_state);
	पूर्ण
	/* Abort connection setup attempt */
	tipc_set_sk_state(sk, TIPC_DISCONNECTING);
	sk->sk_err = ECONNREFUSED;
	sk->sk_state_change(sk);
	वापस true;
पूर्ण

/**
 * rcvbuf_limit - get proper overload limit of socket receive queue
 * @sk: socket
 * @skb: message
 *
 * For connection oriented messages, irrespective of importance,
 * शेष queue limit is 2 MB.
 *
 * For connectionless messages, queue limits are based on message
 * importance as follows:
 *
 * TIPC_LOW_IMPORTANCE       (2 MB)
 * TIPC_MEDIUM_IMPORTANCE    (4 MB)
 * TIPC_HIGH_IMPORTANCE      (8 MB)
 * TIPC_CRITICAL_IMPORTANCE  (16 MB)
 *
 * Return: overload limit according to corresponding message importance
 */
अटल अचिन्हित पूर्णांक rcvbuf_limit(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_msg *hdr = buf_msg(skb);

	अगर (unlikely(msg_in_group(hdr)))
		वापस READ_ONCE(sk->sk_rcvbuf);

	अगर (unlikely(!msg_connected(hdr)))
		वापस READ_ONCE(sk->sk_rcvbuf) << msg_importance(hdr);

	अगर (likely(tsk->peer_caps & TIPC_BLOCK_FLOWCTL))
		वापस READ_ONCE(sk->sk_rcvbuf);

	वापस FLOWCTL_MSG_LIM;
पूर्ण

/**
 * tipc_sk_filter_rcv - validate incoming message
 * @sk: socket
 * @skb: poपूर्णांकer to message.
 * @xmitq: output message area (FIXME)
 *
 * Enqueues message on receive queue अगर acceptable; optionally handles
 * disconnect indication क्रम a connected socket.
 *
 * Called with socket lock alपढ़ोy taken
 */
अटल व्योम tipc_sk_filter_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			       काष्ठा sk_buff_head *xmitq)
अणु
	bool sk_conn = !tipc_sk_type_connectionless(sk);
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_group *grp = tsk->group;
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	काष्ठा net *net = sock_net(sk);
	काष्ठा sk_buff_head inputq;
	पूर्णांक mtyp = msg_type(hdr);
	पूर्णांक limit, err = TIPC_OK;

	trace_tipc_sk_filter_rcv(sk, skb, TIPC_DUMP_ALL, " ");
	TIPC_SKB_CB(skb)->bytes_पढ़ो = 0;
	__skb_queue_head_init(&inputq);
	__skb_queue_tail(&inputq, skb);

	अगर (unlikely(!msg_isdata(hdr)))
		tipc_sk_proto_rcv(sk, &inputq, xmitq);

	अगर (unlikely(grp))
		tipc_group_filter_msg(grp, &inputq, xmitq);

	अगर (unlikely(!grp) && mtyp == TIPC_MCAST_MSG)
		tipc_mcast_filter_msg(net, &tsk->mc_method.deferredq, &inputq);

	/* Validate and add to receive buffer अगर there is space */
	जबतक ((skb = __skb_dequeue(&inputq))) अणु
		hdr = buf_msg(skb);
		limit = rcvbuf_limit(sk, skb);
		अगर ((sk_conn && !tipc_sk_filter_connect(tsk, skb, xmitq)) ||
		    (!sk_conn && msg_connected(hdr)) ||
		    (!grp && msg_in_group(hdr)))
			err = TIPC_ERR_NO_PORT;
		अन्यथा अगर (sk_rmem_alloc_get(sk) + skb->truesize >= limit) अणु
			trace_tipc_sk_dump(sk, skb, TIPC_DUMP_ALL,
					   "err_overload2!");
			atomic_inc(&sk->sk_drops);
			err = TIPC_ERR_OVERLOAD;
		पूर्ण

		अगर (unlikely(err)) अणु
			अगर (tipc_msg_reverse(tipc_own_addr(net), &skb, err)) अणु
				trace_tipc_sk_rej_msg(sk, skb, TIPC_DUMP_NONE,
						      "@filter_rcv!");
				__skb_queue_tail(xmitq, skb);
			पूर्ण
			err = TIPC_OK;
			जारी;
		पूर्ण
		__skb_queue_tail(&sk->sk_receive_queue, skb);
		skb_set_owner_r(skb, sk);
		trace_tipc_sk_overlimit2(sk, skb, TIPC_DUMP_ALL,
					 "rcvq >90% allocated!");
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
पूर्ण

/**
 * tipc_sk_backlog_rcv - handle incoming message from backlog queue
 * @sk: socket
 * @skb: message
 *
 * Caller must hold socket lock
 */
अटल पूर्णांक tipc_sk_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक beक्रमe = sk_rmem_alloc_get(sk);
	काष्ठा sk_buff_head xmitq;
	अचिन्हित पूर्णांक added;

	__skb_queue_head_init(&xmitq);

	tipc_sk_filter_rcv(sk, skb, &xmitq);
	added = sk_rmem_alloc_get(sk) - beक्रमe;
	atomic_add(added, &tipc_sk(sk)->dupl_rcvcnt);

	/* Send pending response/rejected messages, अगर any */
	tipc_node_distr_xmit(sock_net(sk), &xmitq);
	वापस 0;
पूर्ण

/**
 * tipc_sk_enqueue - extract all buffers with destination 'dport' from
 *                   inputq and try adding them to socket or backlog queue
 * @inputq: list of incoming buffers with potentially dअगरferent destinations
 * @sk: socket where the buffers should be enqueued
 * @dport: port number क्रम the socket
 * @xmitq: output queue
 *
 * Caller must hold socket lock
 */
अटल व्योम tipc_sk_enqueue(काष्ठा sk_buff_head *inputq, काष्ठा sock *sk,
			    u32 dport, काष्ठा sk_buff_head *xmitq)
अणु
	अचिन्हित दीर्घ समय_limit = jअगरfies + 2;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक lim;
	atomic_t *dcnt;
	u32 onode;

	जबतक (skb_queue_len(inputq)) अणु
		अगर (unlikely(समय_after_eq(jअगरfies, समय_limit)))
			वापस;

		skb = tipc_skb_dequeue(inputq, dport);
		अगर (unlikely(!skb))
			वापस;

		/* Add message directly to receive queue अगर possible */
		अगर (!sock_owned_by_user(sk)) अणु
			tipc_sk_filter_rcv(sk, skb, xmitq);
			जारी;
		पूर्ण

		/* Try backlog, compensating क्रम द्विगुन-counted bytes */
		dcnt = &tipc_sk(sk)->dupl_rcvcnt;
		अगर (!sk->sk_backlog.len)
			atomic_set(dcnt, 0);
		lim = rcvbuf_limit(sk, skb) + atomic_पढ़ो(dcnt);
		अगर (likely(!sk_add_backlog(sk, skb, lim))) अणु
			trace_tipc_sk_overlimit1(sk, skb, TIPC_DUMP_ALL,
						 "bklg & rcvq >90% allocated!");
			जारी;
		पूर्ण

		trace_tipc_sk_dump(sk, skb, TIPC_DUMP_ALL, "err_overload!");
		/* Overload => reject message back to sender */
		onode = tipc_own_addr(sock_net(sk));
		atomic_inc(&sk->sk_drops);
		अगर (tipc_msg_reverse(onode, &skb, TIPC_ERR_OVERLOAD)) अणु
			trace_tipc_sk_rej_msg(sk, skb, TIPC_DUMP_ALL,
					      "@sk_enqueue!");
			__skb_queue_tail(xmitq, skb);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/**
 * tipc_sk_rcv - handle a chain of incoming buffers
 * @net: the associated network namespace
 * @inputq: buffer list containing the buffers
 * Consumes all buffers in list until inputq is empty
 * Note: may be called in multiple thपढ़ोs referring to the same queue
 */
व्योम tipc_sk_rcv(काष्ठा net *net, काष्ठा sk_buff_head *inputq)
अणु
	काष्ठा sk_buff_head xmitq;
	u32 dnode, dport = 0;
	पूर्णांक err;
	काष्ठा tipc_sock *tsk;
	काष्ठा sock *sk;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&xmitq);
	जबतक (skb_queue_len(inputq)) अणु
		dport = tipc_skb_peek_port(inputq, dport);
		tsk = tipc_sk_lookup(net, dport);

		अगर (likely(tsk)) अणु
			sk = &tsk->sk;
			अगर (likely(spin_trylock_bh(&sk->sk_lock.slock))) अणु
				tipc_sk_enqueue(inputq, sk, dport, &xmitq);
				spin_unlock_bh(&sk->sk_lock.slock);
			पूर्ण
			/* Send pending response/rejected messages, अगर any */
			tipc_node_distr_xmit(sock_net(sk), &xmitq);
			sock_put(sk);
			जारी;
		पूर्ण
		/* No destination socket => dequeue skb अगर still there */
		skb = tipc_skb_dequeue(inputq, dport);
		अगर (!skb)
			वापस;

		/* Try secondary lookup अगर unresolved named message */
		err = TIPC_ERR_NO_PORT;
		अगर (tipc_msg_lookup_dest(net, skb, &err))
			जाओ xmit;

		/* Prepare क्रम message rejection */
		अगर (!tipc_msg_reverse(tipc_own_addr(net), &skb, err))
			जारी;

		trace_tipc_sk_rej_msg(शून्य, skb, TIPC_DUMP_NONE, "@sk_rcv!");
xmit:
		dnode = msg_destnode(buf_msg(skb));
		tipc_node_xmit_skb(net, skb, dnode, dport);
	पूर्ण
पूर्ण

अटल पूर्णांक tipc_रुको_क्रम_connect(काष्ठा socket *sock, दीर्घ *समयo_p)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा sock *sk = sock->sk;
	पूर्णांक करोne;

	करो अणु
		पूर्णांक err = sock_error(sk);
		अगर (err)
			वापस err;
		अगर (!*समयo_p)
			वापस -ETIMEDOUT;
		अगर (संकेत_pending(current))
			वापस sock_पूर्णांकr_त्रुटि_सं(*समयo_p);
		अगर (sk->sk_state == TIPC_DISCONNECTING)
			अवरोध;

		add_रुको_queue(sk_sleep(sk), &रुको);
		करोne = sk_रुको_event(sk, समयo_p, tipc_sk_connected(sk),
				     &रुको);
		हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	पूर्ण जबतक (!करोne);
	वापस 0;
पूर्ण

अटल bool tipc_sockaddr_is_sane(काष्ठा sockaddr_tipc *addr)
अणु
	अगर (addr->family != AF_TIPC)
		वापस false;
	अगर (addr->addrtype == TIPC_SERVICE_RANGE)
		वापस (addr->addr.nameseq.lower <= addr->addr.nameseq.upper);
	वापस (addr->addrtype == TIPC_SERVICE_ADDR ||
		addr->addrtype == TIPC_SOCKET_ADDR);
पूर्ण

/**
 * tipc_connect - establish a connection to another TIPC port
 * @sock: socket काष्ठाure
 * @dest: socket address क्रम destination port
 * @destlen: size of socket address data काष्ठाure
 * @flags: file-related flags associated with socket
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_connect(काष्ठा socket *sock, काष्ठा sockaddr *dest,
			पूर्णांक destlen, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा sockaddr_tipc *dst = (काष्ठा sockaddr_tipc *)dest;
	काष्ठा msghdr m = अणुशून्य,पूर्ण;
	दीर्घ समयout = (flags & O_NONBLOCK) ? 0 : tsk->conn_समयout;
	पूर्णांक previous;
	पूर्णांक res = 0;

	अगर (destlen != माप(काष्ठा sockaddr_tipc))
		वापस -EINVAL;

	lock_sock(sk);

	अगर (tsk->group) अणु
		res = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (dst->family == AF_UNSPEC) अणु
		स_रखो(&tsk->peer, 0, माप(काष्ठा sockaddr_tipc));
		अगर (!tipc_sk_type_connectionless(sk))
			res = -EINVAL;
		जाओ निकास;
	पूर्ण
	अगर (!tipc_sockaddr_is_sane(dst)) अणु
		res = -EINVAL;
		जाओ निकास;
	पूर्ण
	/* DGRAM/RDM connect(), just save the destaddr */
	अगर (tipc_sk_type_connectionless(sk)) अणु
		स_नकल(&tsk->peer, dest, destlen);
		जाओ निकास;
	पूर्ण अन्यथा अगर (dst->addrtype == TIPC_SERVICE_RANGE) अणु
		res = -EINVAL;
		जाओ निकास;
	पूर्ण

	previous = sk->sk_state;

	चयन (sk->sk_state) अणु
	हाल TIPC_OPEN:
		/* Send a 'SYN-' to destination */
		m.msg_name = dest;
		m.msg_namelen = destlen;

		/* If connect is in non-blocking हाल, set MSG_DONTWAIT to
		 * indicate send_msg() is never blocked.
		 */
		अगर (!समयout)
			m.msg_flags = MSG_DONTWAIT;

		res = __tipc_sendmsg(sock, &m, 0);
		अगर ((res < 0) && (res != -EWOULDBLOCK))
			जाओ निकास;

		/* Just entered TIPC_CONNECTING state; the only
		 * dअगरference is that वापस value in non-blocking
		 * हाल is EINPROGRESS, rather than EALREADY.
		 */
		res = -EINPROGRESS;
		fallthrough;
	हाल TIPC_CONNECTING:
		अगर (!समयout) अणु
			अगर (previous == TIPC_CONNECTING)
				res = -EALREADY;
			जाओ निकास;
		पूर्ण
		समयout = msecs_to_jअगरfies(समयout);
		/* Wait until an 'ACK' or 'RST' arrives, or a समयout occurs */
		res = tipc_रुको_क्रम_connect(sock, &समयout);
		अवरोध;
	हाल TIPC_ESTABLISHED:
		res = -EISCONN;
		अवरोध;
	शेष:
		res = -EINVAL;
	पूर्ण

निकास:
	release_sock(sk);
	वापस res;
पूर्ण

/**
 * tipc_listen - allow socket to listen क्रम incoming connections
 * @sock: socket काष्ठाure
 * @len: (unused)
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_listen(काष्ठा socket *sock, पूर्णांक len)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक res;

	lock_sock(sk);
	res = tipc_set_sk_state(sk, TIPC_LISTEN);
	release_sock(sk);

	वापस res;
पूर्ण

अटल पूर्णांक tipc_रुको_क्रम_accept(काष्ठा socket *sock, दीर्घ समयo)
अणु
	काष्ठा sock *sk = sock->sk;
	DEFINE_WAIT(रुको);
	पूर्णांक err;

	/* True wake-one mechanism क्रम incoming connections: only
	 * one process माला_लो woken up, not the 'whole herd'.
	 * Since we करो not 'race & poll' क्रम established sockets
	 * anymore, the common हाल will execute the loop only once.
	*/
	क्रम (;;) अणु
		prepare_to_रुको_exclusive(sk_sleep(sk), &रुको,
					  TASK_INTERRUPTIBLE);
		अगर (समयo && skb_queue_empty(&sk->sk_receive_queue)) अणु
			release_sock(sk);
			समयo = schedule_समयout(समयo);
			lock_sock(sk);
		पूर्ण
		err = 0;
		अगर (!skb_queue_empty(&sk->sk_receive_queue))
			अवरोध;
		err = -EAGAIN;
		अगर (!समयo)
			अवरोध;
		err = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			अवरोध;
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	वापस err;
पूर्ण

/**
 * tipc_accept - रुको क्रम connection request
 * @sock: listening socket
 * @new_sock: new socket that is to be connected
 * @flags: file-related flags associated with socket
 * @kern: caused by kernel or by userspace?
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_accept(काष्ठा socket *sock, काष्ठा socket *new_sock, पूर्णांक flags,
		       bool kern)
अणु
	काष्ठा sock *new_sk, *sk = sock->sk;
	काष्ठा sk_buff *buf;
	काष्ठा tipc_sock *new_tsock;
	काष्ठा tipc_msg *msg;
	दीर्घ समयo;
	पूर्णांक res;

	lock_sock(sk);

	अगर (sk->sk_state != TIPC_LISTEN) अणु
		res = -EINVAL;
		जाओ निकास;
	पूर्ण
	समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);
	res = tipc_रुको_क्रम_accept(sock, समयo);
	अगर (res)
		जाओ निकास;

	buf = skb_peek(&sk->sk_receive_queue);

	res = tipc_sk_create(sock_net(sock->sk), new_sock, 0, kern);
	अगर (res)
		जाओ निकास;
	security_sk_clone(sock->sk, new_sock->sk);

	new_sk = new_sock->sk;
	new_tsock = tipc_sk(new_sk);
	msg = buf_msg(buf);

	/* we lock on new_sk; but lockdep sees the lock on sk */
	lock_sock_nested(new_sk, SINGLE_DEPTH_NESTING);

	/*
	 * Reject any stray messages received by new socket
	 * beक्रमe the socket lock was taken (very, very unlikely)
	 */
	tsk_rej_rx_queue(new_sk, TIPC_ERR_NO_PORT);

	/* Connect new socket to it's peer */
	tipc_sk_finish_conn(new_tsock, msg_origport(msg), msg_orignode(msg));

	tsk_set_importance(new_sk, msg_importance(msg));
	अगर (msg_named(msg)) अणु
		new_tsock->conn_type = msg_nametype(msg);
		new_tsock->conn_instance = msg_nameinst(msg);
	पूर्ण

	/*
	 * Respond to 'SYN-' by discarding it & returning 'ACK'-.
	 * Respond to 'SYN+' by queuing it on new socket.
	 */
	अगर (!msg_data_sz(msg)) अणु
		काष्ठा msghdr m = अणुशून्य,पूर्ण;

		tsk_advance_rx_queue(sk);
		__tipc_sendstream(new_sock, &m, 0);
	पूर्ण अन्यथा अणु
		__skb_dequeue(&sk->sk_receive_queue);
		__skb_queue_head(&new_sk->sk_receive_queue, buf);
		skb_set_owner_r(buf, new_sk);
	पूर्ण
	release_sock(new_sk);
निकास:
	release_sock(sk);
	वापस res;
पूर्ण

/**
 * tipc_shutकरोwn - shutकरोwn socket connection
 * @sock: socket काष्ठाure
 * @how: direction to बंद (must be SHUT_RDWR)
 *
 * Terminates connection (अगर necessary), then purges socket's receive queue.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक res;

	अगर (how != SHUT_RDWR)
		वापस -EINVAL;

	lock_sock(sk);

	trace_tipc_sk_shutकरोwn(sk, शून्य, TIPC_DUMP_ALL, " ");
	__tipc_shutकरोwn(sock, TIPC_CONN_SHUTDOWN);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	अगर (sk->sk_state == TIPC_DISCONNECTING) अणु
		/* Discard any unreceived messages */
		__skb_queue_purge(&sk->sk_receive_queue);

		res = 0;
	पूर्ण अन्यथा अणु
		res = -ENOTCONN;
	पूर्ण
	/* Wake up anyone sleeping in poll. */
	sk->sk_state_change(sk);

	release_sock(sk);
	वापस res;
पूर्ण

अटल व्योम tipc_sk_check_probing_state(काष्ठा sock *sk,
					काष्ठा sk_buff_head *list)
अणु
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	u32 pnode = tsk_peer_node(tsk);
	u32 pport = tsk_peer_port(tsk);
	u32 self = tsk_own_node(tsk);
	u32 oport = tsk->portid;
	काष्ठा sk_buff *skb;

	अगर (tsk->probe_unacked) अणु
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
		sk->sk_err = ECONNABORTED;
		tipc_node_हटाओ_conn(sock_net(sk), pnode, pport);
		sk->sk_state_change(sk);
		वापस;
	पूर्ण
	/* Prepare new probe */
	skb = tipc_msg_create(CONN_MANAGER, CONN_PROBE, INT_H_SIZE, 0,
			      pnode, self, pport, oport, TIPC_OK);
	अगर (skb)
		__skb_queue_tail(list, skb);
	tsk->probe_unacked = true;
	sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + CONN_PROBING_INTV);
पूर्ण

अटल व्योम tipc_sk_retry_connect(काष्ठा sock *sk, काष्ठा sk_buff_head *list)
अणु
	काष्ठा tipc_sock *tsk = tipc_sk(sk);

	/* Try again later अगर dest link is congested */
	अगर (tsk->cong_link_cnt) अणु
		sk_reset_समयr(sk, &sk->sk_समयr, msecs_to_jअगरfies(100));
		वापस;
	पूर्ण
	/* Prepare SYN क्रम retransmit */
	tipc_msg_skb_clone(&sk->sk_ग_लिखो_queue, list);
पूर्ण

अटल व्योम tipc_sk_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	u32 pnode = tsk_peer_node(tsk);
	काष्ठा sk_buff_head list;
	पूर्णांक rc = 0;

	__skb_queue_head_init(&list);
	bh_lock_sock(sk);

	/* Try again later अगर socket is busy */
	अगर (sock_owned_by_user(sk)) अणु
		sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + HZ / 20);
		bh_unlock_sock(sk);
		sock_put(sk);
		वापस;
	पूर्ण

	अगर (sk->sk_state == TIPC_ESTABLISHED)
		tipc_sk_check_probing_state(sk, &list);
	अन्यथा अगर (sk->sk_state == TIPC_CONNECTING)
		tipc_sk_retry_connect(sk, &list);

	bh_unlock_sock(sk);

	अगर (!skb_queue_empty(&list))
		rc = tipc_node_xmit(sock_net(sk), &list, pnode, tsk->portid);

	/* SYN messages may cause link congestion */
	अगर (rc == -ELINKCONG) अणु
		tipc_dest_push(&tsk->cong_links, pnode, 0);
		tsk->cong_link_cnt = 1;
	पूर्ण
	sock_put(sk);
पूर्ण

अटल पूर्णांक tipc_sk_publish(काष्ठा tipc_sock *tsk, काष्ठा tipc_uaddr *ua)
अणु
	काष्ठा sock *sk = &tsk->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा tipc_socket_addr skaddr;
	काष्ठा खुलाation *p;
	u32 key;

	अगर (tipc_sk_connected(sk))
		वापस -EINVAL;
	key = tsk->portid + tsk->pub_count + 1;
	अगर (key == tsk->portid)
		वापस -EADDRINUSE;
	skaddr.ref = tsk->portid;
	skaddr.node = tipc_own_addr(net);
	p = tipc_nametbl_publish(net, ua, &skaddr, key);
	अगर (unlikely(!p))
		वापस -EINVAL;

	list_add(&p->binding_sock, &tsk->खुलाations);
	tsk->pub_count++;
	tsk->published = true;
	वापस 0;
पूर्ण

अटल पूर्णांक tipc_sk_withdraw(काष्ठा tipc_sock *tsk, काष्ठा tipc_uaddr *ua)
अणु
	काष्ठा net *net = sock_net(&tsk->sk);
	काष्ठा खुलाation *safe, *p;
	काष्ठा tipc_uaddr _ua;
	पूर्णांक rc = -EINVAL;

	list_क्रम_each_entry_safe(p, safe, &tsk->खुलाations, binding_sock) अणु
		अगर (!ua) अणु
			tipc_uaddr(&_ua, TIPC_SERVICE_RANGE, p->scope,
				   p->sr.type, p->sr.lower, p->sr.upper);
			tipc_nametbl_withdraw(net, &_ua, &p->sk, p->key);
			जारी;
		पूर्ण
		/* Unbind specअगरic खुलाation */
		अगर (p->scope != ua->scope)
			जारी;
		अगर (p->sr.type != ua->sr.type)
			जारी;
		अगर (p->sr.lower != ua->sr.lower)
			जारी;
		अगर (p->sr.upper != ua->sr.upper)
			अवरोध;
		tipc_nametbl_withdraw(net, ua, &p->sk, p->key);
		rc = 0;
		अवरोध;
	पूर्ण
	अगर (list_empty(&tsk->खुलाations)) अणु
		tsk->published = 0;
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

/* tipc_sk_reinit: set non-zero address in all existing sockets
 *                 when we go from standalone to network mode.
 */
व्योम tipc_sk_reinit(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा rhashtable_iter iter;
	काष्ठा tipc_sock *tsk;
	काष्ठा tipc_msg *msg;

	rhashtable_walk_enter(&tn->sk_rht, &iter);

	करो अणु
		rhashtable_walk_start(&iter);

		जबतक ((tsk = rhashtable_walk_next(&iter)) && !IS_ERR(tsk)) अणु
			sock_hold(&tsk->sk);
			rhashtable_walk_stop(&iter);
			lock_sock(&tsk->sk);
			msg = &tsk->phdr;
			msg_set_prevnode(msg, tipc_own_addr(net));
			msg_set_orignode(msg, tipc_own_addr(net));
			release_sock(&tsk->sk);
			rhashtable_walk_start(&iter);
			sock_put(&tsk->sk);
		पूर्ण

		rhashtable_walk_stop(&iter);
	पूर्ण जबतक (tsk == ERR_PTR(-EAGAIN));

	rhashtable_walk_निकास(&iter);
पूर्ण

अटल काष्ठा tipc_sock *tipc_sk_lookup(काष्ठा net *net, u32 portid)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	काष्ठा tipc_sock *tsk;

	rcu_पढ़ो_lock();
	tsk = rhashtable_lookup(&tn->sk_rht, &portid, tsk_rht_params);
	अगर (tsk)
		sock_hold(&tsk->sk);
	rcu_पढ़ो_unlock();

	वापस tsk;
पूर्ण

अटल पूर्णांक tipc_sk_insert(काष्ठा tipc_sock *tsk)
अणु
	काष्ठा sock *sk = &tsk->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	u32 reमुख्यing = (TIPC_MAX_PORT - TIPC_MIN_PORT) + 1;
	u32 portid = pअक्रमom_u32() % reमुख्यing + TIPC_MIN_PORT;

	जबतक (reमुख्यing--) अणु
		portid++;
		अगर ((portid < TIPC_MIN_PORT) || (portid > TIPC_MAX_PORT))
			portid = TIPC_MIN_PORT;
		tsk->portid = portid;
		sock_hold(&tsk->sk);
		अगर (!rhashtable_lookup_insert_fast(&tn->sk_rht, &tsk->node,
						   tsk_rht_params))
			वापस 0;
		sock_put(&tsk->sk);
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम tipc_sk_हटाओ(काष्ठा tipc_sock *tsk)
अणु
	काष्ठा sock *sk = &tsk->sk;
	काष्ठा tipc_net *tn = net_generic(sock_net(sk), tipc_net_id);

	अगर (!rhashtable_हटाओ_fast(&tn->sk_rht, &tsk->node, tsk_rht_params)) अणु
		WARN_ON(refcount_पढ़ो(&sk->sk_refcnt) == 1);
		__sock_put(sk);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rhashtable_params tsk_rht_params = अणु
	.nelem_hपूर्णांक = 192,
	.head_offset = दुरत्व(काष्ठा tipc_sock, node),
	.key_offset = दुरत्व(काष्ठा tipc_sock, portid),
	.key_len = माप(u32), /* portid */
	.max_size = 1048576,
	.min_size = 256,
	.स्वतःmatic_shrinking = true,
पूर्ण;

पूर्णांक tipc_sk_rht_init(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);

	वापस rhashtable_init(&tn->sk_rht, &tsk_rht_params);
पूर्ण

व्योम tipc_sk_rht_destroy(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);

	/* Wait क्रम socket पढ़ोers to complete */
	synchronize_net();

	rhashtable_destroy(&tn->sk_rht);
पूर्ण

अटल पूर्णांक tipc_sk_join(काष्ठा tipc_sock *tsk, काष्ठा tipc_group_req *mreq)
अणु
	काष्ठा net *net = sock_net(&tsk->sk);
	काष्ठा tipc_group *grp = tsk->group;
	काष्ठा tipc_msg *hdr = &tsk->phdr;
	काष्ठा tipc_uaddr ua;
	पूर्णांक rc;

	अगर (mreq->type < TIPC_RESERVED_TYPES)
		वापस -EACCES;
	अगर (mreq->scope > TIPC_NODE_SCOPE)
		वापस -EINVAL;
	अगर (mreq->scope != TIPC_NODE_SCOPE)
		mreq->scope = TIPC_CLUSTER_SCOPE;
	अगर (grp)
		वापस -EACCES;
	grp = tipc_group_create(net, tsk->portid, mreq, &tsk->group_is_खोलो);
	अगर (!grp)
		वापस -ENOMEM;
	tsk->group = grp;
	msg_set_lookup_scope(hdr, mreq->scope);
	msg_set_nametype(hdr, mreq->type);
	msg_set_dest_droppable(hdr, true);
	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, mreq->scope,
		   mreq->type, mreq->instance, mreq->instance);
	tipc_nametbl_build_group(net, grp, &ua);
	rc = tipc_sk_publish(tsk, &ua);
	अगर (rc) अणु
		tipc_group_delete(net, grp);
		tsk->group = शून्य;
		वापस rc;
	पूर्ण
	/* Eliminate any risk that a broadcast overtakes sent JOINs */
	tsk->mc_method.rcast = true;
	tsk->mc_method.mandatory = true;
	tipc_group_join(net, grp, &tsk->sk.sk_rcvbuf);
	वापस rc;
पूर्ण

अटल पूर्णांक tipc_sk_leave(काष्ठा tipc_sock *tsk)
अणु
	काष्ठा net *net = sock_net(&tsk->sk);
	काष्ठा tipc_group *grp = tsk->group;
	काष्ठा tipc_uaddr ua;
	पूर्णांक scope;

	अगर (!grp)
		वापस -EINVAL;
	ua.addrtype = TIPC_SERVICE_RANGE;
	tipc_group_self(grp, &ua.sr, &scope);
	ua.scope = scope;
	tipc_group_delete(net, grp);
	tsk->group = शून्य;
	tipc_sk_withdraw(tsk, &ua);
	वापस 0;
पूर्ण

/**
 * tipc_setsockopt - set socket option
 * @sock: socket काष्ठाure
 * @lvl: option level
 * @opt: option identअगरier
 * @ov: poपूर्णांकer to new option value
 * @ol: length of option value
 *
 * For stream sockets only, accepts and ignores all IPPROTO_TCP options
 * (to ease compatibility).
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_setsockopt(काष्ठा socket *sock, पूर्णांक lvl, पूर्णांक opt,
			   sockptr_t ov, अचिन्हित पूर्णांक ol)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_group_req mreq;
	u32 value = 0;
	पूर्णांक res = 0;

	अगर ((lvl == IPPROTO_TCP) && (sock->type == SOCK_STREAM))
		वापस 0;
	अगर (lvl != SOL_TIPC)
		वापस -ENOPROTOOPT;

	चयन (opt) अणु
	हाल TIPC_IMPORTANCE:
	हाल TIPC_SRC_DROPPABLE:
	हाल TIPC_DEST_DROPPABLE:
	हाल TIPC_CONN_TIMEOUT:
	हाल TIPC_NODELAY:
		अगर (ol < माप(value))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&value, ov, माप(u32)))
			वापस -EFAULT;
		अवरोध;
	हाल TIPC_GROUP_JOIN:
		अगर (ol < माप(mreq))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&mreq, ov, माप(mreq)))
			वापस -EFAULT;
		अवरोध;
	शेष:
		अगर (!sockptr_is_null(ov) || ol)
			वापस -EINVAL;
	पूर्ण

	lock_sock(sk);

	चयन (opt) अणु
	हाल TIPC_IMPORTANCE:
		res = tsk_set_importance(sk, value);
		अवरोध;
	हाल TIPC_SRC_DROPPABLE:
		अगर (sock->type != SOCK_STREAM)
			tsk_set_unreliable(tsk, value);
		अन्यथा
			res = -ENOPROTOOPT;
		अवरोध;
	हाल TIPC_DEST_DROPPABLE:
		tsk_set_unवापसable(tsk, value);
		अवरोध;
	हाल TIPC_CONN_TIMEOUT:
		tipc_sk(sk)->conn_समयout = value;
		अवरोध;
	हाल TIPC_MCAST_BROADCAST:
		tsk->mc_method.rcast = false;
		tsk->mc_method.mandatory = true;
		अवरोध;
	हाल TIPC_MCAST_REPLICAST:
		tsk->mc_method.rcast = true;
		tsk->mc_method.mandatory = true;
		अवरोध;
	हाल TIPC_GROUP_JOIN:
		res = tipc_sk_join(tsk, &mreq);
		अवरोध;
	हाल TIPC_GROUP_LEAVE:
		res = tipc_sk_leave(tsk);
		अवरोध;
	हाल TIPC_NODELAY:
		tsk->nodelay = !!value;
		tsk_set_nagle(tsk);
		अवरोध;
	शेष:
		res = -EINVAL;
	पूर्ण

	release_sock(sk);

	वापस res;
पूर्ण

/**
 * tipc_माला_लोockopt - get socket option
 * @sock: socket काष्ठाure
 * @lvl: option level
 * @opt: option identअगरier
 * @ov: receptacle क्रम option value
 * @ol: receptacle क्रम length of option value
 *
 * For stream sockets only, वापसs 0 length result क्रम all IPPROTO_TCP options
 * (to ease compatibility).
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक tipc_माला_लोockopt(काष्ठा socket *sock, पूर्णांक lvl, पूर्णांक opt,
			   अक्षर __user *ov, पूर्णांक __user *ol)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा tipc_sock *tsk = tipc_sk(sk);
	काष्ठा tipc_service_range seq;
	पूर्णांक len, scope;
	u32 value;
	पूर्णांक res;

	अगर ((lvl == IPPROTO_TCP) && (sock->type == SOCK_STREAM))
		वापस put_user(0, ol);
	अगर (lvl != SOL_TIPC)
		वापस -ENOPROTOOPT;
	res = get_user(len, ol);
	अगर (res)
		वापस res;

	lock_sock(sk);

	चयन (opt) अणु
	हाल TIPC_IMPORTANCE:
		value = tsk_importance(tsk);
		अवरोध;
	हाल TIPC_SRC_DROPPABLE:
		value = tsk_unreliable(tsk);
		अवरोध;
	हाल TIPC_DEST_DROPPABLE:
		value = tsk_unवापसable(tsk);
		अवरोध;
	हाल TIPC_CONN_TIMEOUT:
		value = tsk->conn_समयout;
		/* no need to set "res", since alपढ़ोy 0 at this poपूर्णांक */
		अवरोध;
	हाल TIPC_NODE_RECVQ_DEPTH:
		value = 0; /* was tipc_queue_size, now obsolete */
		अवरोध;
	हाल TIPC_SOCK_RECVQ_DEPTH:
		value = skb_queue_len(&sk->sk_receive_queue);
		अवरोध;
	हाल TIPC_SOCK_RECVQ_USED:
		value = sk_rmem_alloc_get(sk);
		अवरोध;
	हाल TIPC_GROUP_JOIN:
		seq.type = 0;
		अगर (tsk->group)
			tipc_group_self(tsk->group, &seq, &scope);
		value = seq.type;
		अवरोध;
	शेष:
		res = -EINVAL;
	पूर्ण

	release_sock(sk);

	अगर (res)
		वापस res;	/* "get" failed */

	अगर (len < माप(value))
		वापस -EINVAL;

	अगर (copy_to_user(ov, &value, माप(value)))
		वापस -EFAULT;

	वापस put_user(माप(value), ol);
पूर्ण

अटल पूर्णांक tipc_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा net *net = sock_net(sock->sk);
	काष्ठा tipc_sioc_nodeid_req nr = अणु0पूर्ण;
	काष्ठा tipc_sioc_ln_req lnr;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल SIOCGETLINKNAME:
		अगर (copy_from_user(&lnr, argp, माप(lnr)))
			वापस -EFAULT;
		अगर (!tipc_node_get_linkname(net,
					    lnr.bearer_id & 0xffff, lnr.peer,
					    lnr.linkname, TIPC_MAX_LINK_NAME)) अणु
			अगर (copy_to_user(argp, &lnr, माप(lnr)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		वापस -EADDRNOTAVAIL;
	हाल SIOCGETNODEID:
		अगर (copy_from_user(&nr, argp, माप(nr)))
			वापस -EFAULT;
		अगर (!tipc_node_get_id(net, nr.peer, nr.node_id))
			वापस -EADDRNOTAVAIL;
		अगर (copy_to_user(argp, &nr, माप(nr)))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक tipc_socketpair(काष्ठा socket *sock1, काष्ठा socket *sock2)
अणु
	काष्ठा tipc_sock *tsk2 = tipc_sk(sock2->sk);
	काष्ठा tipc_sock *tsk1 = tipc_sk(sock1->sk);
	u32 onode = tipc_own_addr(sock_net(sock1->sk));

	tsk1->peer.family = AF_TIPC;
	tsk1->peer.addrtype = TIPC_SOCKET_ADDR;
	tsk1->peer.scope = TIPC_NODE_SCOPE;
	tsk1->peer.addr.id.ref = tsk2->portid;
	tsk1->peer.addr.id.node = onode;
	tsk2->peer.family = AF_TIPC;
	tsk2->peer.addrtype = TIPC_SOCKET_ADDR;
	tsk2->peer.scope = TIPC_NODE_SCOPE;
	tsk2->peer.addr.id.ref = tsk1->portid;
	tsk2->peer.addr.id.node = onode;

	tipc_sk_finish_conn(tsk1, tsk2->portid, onode);
	tipc_sk_finish_conn(tsk2, tsk1->portid, onode);
	वापस 0;
पूर्ण

/* Protocol चयनes क्रम the various types of TIPC sockets */

अटल स्थिर काष्ठा proto_ops msg_ops = अणु
	.owner		= THIS_MODULE,
	.family		= AF_TIPC,
	.release	= tipc_release,
	.bind		= tipc_bind,
	.connect	= tipc_connect,
	.socketpair	= tipc_socketpair,
	.accept		= sock_no_accept,
	.getname	= tipc_getname,
	.poll		= tipc_poll,
	.ioctl		= tipc_ioctl,
	.listen		= sock_no_listen,
	.shutकरोwn	= tipc_shutकरोwn,
	.setsockopt	= tipc_setsockopt,
	.माला_लोockopt	= tipc_माला_लोockopt,
	.sendmsg	= tipc_sendmsg,
	.recvmsg	= tipc_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage
पूर्ण;

अटल स्थिर काष्ठा proto_ops packet_ops = अणु
	.owner		= THIS_MODULE,
	.family		= AF_TIPC,
	.release	= tipc_release,
	.bind		= tipc_bind,
	.connect	= tipc_connect,
	.socketpair	= tipc_socketpair,
	.accept		= tipc_accept,
	.getname	= tipc_getname,
	.poll		= tipc_poll,
	.ioctl		= tipc_ioctl,
	.listen		= tipc_listen,
	.shutकरोwn	= tipc_shutकरोwn,
	.setsockopt	= tipc_setsockopt,
	.माला_लोockopt	= tipc_माला_लोockopt,
	.sendmsg	= tipc_send_packet,
	.recvmsg	= tipc_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage
पूर्ण;

अटल स्थिर काष्ठा proto_ops stream_ops = अणु
	.owner		= THIS_MODULE,
	.family		= AF_TIPC,
	.release	= tipc_release,
	.bind		= tipc_bind,
	.connect	= tipc_connect,
	.socketpair	= tipc_socketpair,
	.accept		= tipc_accept,
	.getname	= tipc_getname,
	.poll		= tipc_poll,
	.ioctl		= tipc_ioctl,
	.listen		= tipc_listen,
	.shutकरोwn	= tipc_shutकरोwn,
	.setsockopt	= tipc_setsockopt,
	.माला_लोockopt	= tipc_माला_लोockopt,
	.sendmsg	= tipc_sendstream,
	.recvmsg	= tipc_recvstream,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage
पूर्ण;

अटल स्थिर काष्ठा net_proto_family tipc_family_ops = अणु
	.owner		= THIS_MODULE,
	.family		= AF_TIPC,
	.create		= tipc_sk_create
पूर्ण;

अटल काष्ठा proto tipc_proto = अणु
	.name		= "TIPC",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा tipc_sock),
	.sysctl_rmem	= sysctl_tipc_rmem
पूर्ण;

/**
 * tipc_socket_init - initialize TIPC socket पूर्णांकerface
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
पूर्णांक tipc_socket_init(व्योम)
अणु
	पूर्णांक res;

	res = proto_रेजिस्टर(&tipc_proto, 1);
	अगर (res) अणु
		pr_err("Failed to register TIPC protocol type\n");
		जाओ out;
	पूर्ण

	res = sock_रेजिस्टर(&tipc_family_ops);
	अगर (res) अणु
		pr_err("Failed to register TIPC socket type\n");
		proto_unरेजिस्टर(&tipc_proto);
		जाओ out;
	पूर्ण
 out:
	वापस res;
पूर्ण

/**
 * tipc_socket_stop - stop TIPC socket पूर्णांकerface
 */
व्योम tipc_socket_stop(व्योम)
अणु
	sock_unरेजिस्टर(tipc_family_ops.family);
	proto_unरेजिस्टर(&tipc_proto);
पूर्ण

/* Caller should hold socket lock क्रम the passed tipc socket. */
अटल पूर्णांक __tipc_nl_add_sk_con(काष्ठा sk_buff *skb, काष्ठा tipc_sock *tsk)
अणु
	u32 peer_node;
	u32 peer_port;
	काष्ठा nlattr *nest;

	peer_node = tsk_peer_node(tsk);
	peer_port = tsk_peer_port(tsk);

	nest = nla_nest_start_noflag(skb, TIPC_NLA_SOCK_CON);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, TIPC_NLA_CON_NODE, peer_node))
		जाओ msg_full;
	अगर (nla_put_u32(skb, TIPC_NLA_CON_SOCK, peer_port))
		जाओ msg_full;

	अगर (tsk->conn_type != 0) अणु
		अगर (nla_put_flag(skb, TIPC_NLA_CON_FLAG))
			जाओ msg_full;
		अगर (nla_put_u32(skb, TIPC_NLA_CON_TYPE, tsk->conn_type))
			जाओ msg_full;
		अगर (nla_put_u32(skb, TIPC_NLA_CON_INST, tsk->conn_instance))
			जाओ msg_full;
	पूर्ण
	nla_nest_end(skb, nest);

	वापस 0;

msg_full:
	nla_nest_cancel(skb, nest);

	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक __tipc_nl_add_sk_info(काष्ठा sk_buff *skb, काष्ठा tipc_sock
			  *tsk)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा sock *sk = &tsk->sk;

	अगर (nla_put_u32(skb, TIPC_NLA_SOCK_REF, tsk->portid) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_ADDR, tipc_own_addr(net)))
		वापस -EMSGSIZE;

	अगर (tipc_sk_connected(sk)) अणु
		अगर (__tipc_nl_add_sk_con(skb, tsk))
			वापस -EMSGSIZE;
	पूर्ण अन्यथा अगर (!list_empty(&tsk->खुलाations)) अणु
		अगर (nla_put_flag(skb, TIPC_NLA_SOCK_HAS_PUBL))
			वापस -EMSGSIZE;
	पूर्ण
	वापस 0;
पूर्ण

/* Caller should hold socket lock क्रम the passed tipc socket. */
अटल पूर्णांक __tipc_nl_add_sk(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			    काष्ठा tipc_sock *tsk)
अणु
	काष्ठा nlattr *attrs;
	व्योम *hdr;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &tipc_genl_family, NLM_F_MULTI, TIPC_NL_SOCK_GET);
	अगर (!hdr)
		जाओ msg_cancel;

	attrs = nla_nest_start_noflag(skb, TIPC_NLA_SOCK);
	अगर (!attrs)
		जाओ genlmsg_cancel;

	अगर (__tipc_nl_add_sk_info(skb, tsk))
		जाओ attr_msg_cancel;

	nla_nest_end(skb, attrs);
	genlmsg_end(skb, hdr);

	वापस 0;

attr_msg_cancel:
	nla_nest_cancel(skb, attrs);
genlmsg_cancel:
	genlmsg_cancel(skb, hdr);
msg_cancel:
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक tipc_nl_sk_walk(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		    पूर्णांक (*skb_handler)(काष्ठा sk_buff *skb,
				       काष्ठा netlink_callback *cb,
				       काष्ठा tipc_sock *tsk))
अणु
	काष्ठा rhashtable_iter *iter = (व्योम *)cb->args[4];
	काष्ठा tipc_sock *tsk;
	पूर्णांक err;

	rhashtable_walk_start(iter);
	जबतक ((tsk = rhashtable_walk_next(iter)) != शून्य) अणु
		अगर (IS_ERR(tsk)) अणु
			err = PTR_ERR(tsk);
			अगर (err == -EAGAIN) अणु
				err = 0;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		sock_hold(&tsk->sk);
		rhashtable_walk_stop(iter);
		lock_sock(&tsk->sk);
		err = skb_handler(skb, cb, tsk);
		अगर (err) अणु
			release_sock(&tsk->sk);
			sock_put(&tsk->sk);
			जाओ out;
		पूर्ण
		release_sock(&tsk->sk);
		rhashtable_walk_start(iter);
		sock_put(&tsk->sk);
	पूर्ण
	rhashtable_walk_stop(iter);
out:
	वापस skb->len;
पूर्ण
EXPORT_SYMBOL(tipc_nl_sk_walk);

पूर्णांक tipc_dump_start(काष्ठा netlink_callback *cb)
अणु
	वापस __tipc_dump_start(cb, sock_net(cb->skb->sk));
पूर्ण
EXPORT_SYMBOL(tipc_dump_start);

पूर्णांक __tipc_dump_start(काष्ठा netlink_callback *cb, काष्ठा net *net)
अणु
	/* tipc_nl_name_table_dump() uses cb->args[0...3]. */
	काष्ठा rhashtable_iter *iter = (व्योम *)cb->args[4];
	काष्ठा tipc_net *tn = tipc_net(net);

	अगर (!iter) अणु
		iter = kदो_स्मृति(माप(*iter), GFP_KERNEL);
		अगर (!iter)
			वापस -ENOMEM;

		cb->args[4] = (दीर्घ)iter;
	पूर्ण

	rhashtable_walk_enter(&tn->sk_rht, iter);
	वापस 0;
पूर्ण

पूर्णांक tipc_dump_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा rhashtable_iter *hti = (व्योम *)cb->args[4];

	rhashtable_walk_निकास(hti);
	kमुक्त(hti);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tipc_dump_करोne);

पूर्णांक tipc_sk_fill_sock_diag(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			   काष्ठा tipc_sock *tsk, u32 sk_filter_state,
			   u64 (*tipc_diag_gen_cookie)(काष्ठा sock *sk))
अणु
	काष्ठा sock *sk = &tsk->sk;
	काष्ठा nlattr *attrs;
	काष्ठा nlattr *stat;

	/*filter response w.r.t sk_state*/
	अगर (!(sk_filter_state & (1 << sk->sk_state)))
		वापस 0;

	attrs = nla_nest_start_noflag(skb, TIPC_NLA_SOCK);
	अगर (!attrs)
		जाओ msg_cancel;

	अगर (__tipc_nl_add_sk_info(skb, tsk))
		जाओ attr_msg_cancel;

	अगर (nla_put_u32(skb, TIPC_NLA_SOCK_TYPE, (u32)sk->sk_type) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_TIPC_STATE, (u32)sk->sk_state) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_INO, sock_i_ino(sk)) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_UID,
			from_kuid_munged(sk_user_ns(NETLINK_CB(cb->skb).sk),
					 sock_i_uid(sk))) ||
	    nla_put_u64_64bit(skb, TIPC_NLA_SOCK_COOKIE,
			      tipc_diag_gen_cookie(sk),
			      TIPC_NLA_SOCK_PAD))
		जाओ attr_msg_cancel;

	stat = nla_nest_start_noflag(skb, TIPC_NLA_SOCK_STAT);
	अगर (!stat)
		जाओ attr_msg_cancel;

	अगर (nla_put_u32(skb, TIPC_NLA_SOCK_STAT_RCVQ,
			skb_queue_len(&sk->sk_receive_queue)) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_STAT_SENDQ,
			skb_queue_len(&sk->sk_ग_लिखो_queue)) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_STAT_DROP,
			atomic_पढ़ो(&sk->sk_drops)))
		जाओ stat_msg_cancel;

	अगर (tsk->cong_link_cnt &&
	    nla_put_flag(skb, TIPC_NLA_SOCK_STAT_LINK_CONG))
		जाओ stat_msg_cancel;

	अगर (tsk_conn_cong(tsk) &&
	    nla_put_flag(skb, TIPC_NLA_SOCK_STAT_CONN_CONG))
		जाओ stat_msg_cancel;

	nla_nest_end(skb, stat);

	अगर (tsk->group)
		अगर (tipc_group_fill_sock_diag(tsk->group, skb))
			जाओ stat_msg_cancel;

	nla_nest_end(skb, attrs);

	वापस 0;

stat_msg_cancel:
	nla_nest_cancel(skb, stat);
attr_msg_cancel:
	nla_nest_cancel(skb, attrs);
msg_cancel:
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL(tipc_sk_fill_sock_diag);

पूर्णांक tipc_nl_sk_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस tipc_nl_sk_walk(skb, cb, __tipc_nl_add_sk);
पूर्ण

/* Caller should hold socket lock क्रम the passed tipc socket. */
अटल पूर्णांक __tipc_nl_add_sk_publ(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb,
				 काष्ठा खुलाation *publ)
अणु
	व्योम *hdr;
	काष्ठा nlattr *attrs;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &tipc_genl_family, NLM_F_MULTI, TIPC_NL_PUBL_GET);
	अगर (!hdr)
		जाओ msg_cancel;

	attrs = nla_nest_start_noflag(skb, TIPC_NLA_PUBL);
	अगर (!attrs)
		जाओ genlmsg_cancel;

	अगर (nla_put_u32(skb, TIPC_NLA_PUBL_KEY, publ->key))
		जाओ attr_msg_cancel;
	अगर (nla_put_u32(skb, TIPC_NLA_PUBL_TYPE, publ->sr.type))
		जाओ attr_msg_cancel;
	अगर (nla_put_u32(skb, TIPC_NLA_PUBL_LOWER, publ->sr.lower))
		जाओ attr_msg_cancel;
	अगर (nla_put_u32(skb, TIPC_NLA_PUBL_UPPER, publ->sr.upper))
		जाओ attr_msg_cancel;

	nla_nest_end(skb, attrs);
	genlmsg_end(skb, hdr);

	वापस 0;

attr_msg_cancel:
	nla_nest_cancel(skb, attrs);
genlmsg_cancel:
	genlmsg_cancel(skb, hdr);
msg_cancel:
	वापस -EMSGSIZE;
पूर्ण

/* Caller should hold socket lock क्रम the passed tipc socket. */
अटल पूर्णांक __tipc_nl_list_sk_publ(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb,
				  काष्ठा tipc_sock *tsk, u32 *last_publ)
अणु
	पूर्णांक err;
	काष्ठा खुलाation *p;

	अगर (*last_publ) अणु
		list_क्रम_each_entry(p, &tsk->खुलाations, binding_sock) अणु
			अगर (p->key == *last_publ)
				अवरोध;
		पूर्ण
		अगर (p->key != *last_publ) अणु
			/* We never set seq or call nl_dump_check_consistent()
			 * this means that setting prev_seq here will cause the
			 * consistence check to fail in the netlink callback
			 * handler. Resulting in the last NLMSG_DONE message
			 * having the NLM_F_DUMP_INTR flag set.
			 */
			cb->prev_seq = 1;
			*last_publ = 0;
			वापस -EPIPE;
		पूर्ण
	पूर्ण अन्यथा अणु
		p = list_first_entry(&tsk->खुलाations, काष्ठा खुलाation,
				     binding_sock);
	पूर्ण

	list_क्रम_each_entry_from(p, &tsk->खुलाations, binding_sock) अणु
		err = __tipc_nl_add_sk_publ(skb, cb, p);
		अगर (err) अणु
			*last_publ = p->key;
			वापस err;
		पूर्ण
	पूर्ण
	*last_publ = 0;

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_publ_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक err;
	u32 tsk_portid = cb->args[0];
	u32 last_publ = cb->args[1];
	u32 करोne = cb->args[2];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा tipc_sock *tsk;

	अगर (!tsk_portid) अणु
		काष्ठा nlattr **attrs = genl_dumpit_info(cb)->attrs;
		काष्ठा nlattr *sock[TIPC_NLA_SOCK_MAX + 1];

		अगर (!attrs[TIPC_NLA_SOCK])
			वापस -EINVAL;

		err = nla_parse_nested_deprecated(sock, TIPC_NLA_SOCK_MAX,
						  attrs[TIPC_NLA_SOCK],
						  tipc_nl_sock_policy, शून्य);
		अगर (err)
			वापस err;

		अगर (!sock[TIPC_NLA_SOCK_REF])
			वापस -EINVAL;

		tsk_portid = nla_get_u32(sock[TIPC_NLA_SOCK_REF]);
	पूर्ण

	अगर (करोne)
		वापस 0;

	tsk = tipc_sk_lookup(net, tsk_portid);
	अगर (!tsk)
		वापस -EINVAL;

	lock_sock(&tsk->sk);
	err = __tipc_nl_list_sk_publ(skb, cb, tsk, &last_publ);
	अगर (!err)
		करोne = 1;
	release_sock(&tsk->sk);
	sock_put(&tsk->sk);

	cb->args[0] = tsk_portid;
	cb->args[1] = last_publ;
	cb->args[2] = करोne;

	वापस skb->len;
पूर्ण

/**
 * tipc_sk_filtering - check अगर a socket should be traced
 * @sk: the socket to be examined
 *
 * @sysctl_tipc_sk_filter is used as the socket tuple क्रम filtering:
 * (portid, sock type, name type, name lower, name upper)
 *
 * Return: true अगर the socket meets the socket tuple data
 * (value 0 = 'any') or when there is no tuple set (all = 0),
 * otherwise false
 */
bool tipc_sk_filtering(काष्ठा sock *sk)
अणु
	काष्ठा tipc_sock *tsk;
	काष्ठा खुलाation *p;
	u32 _port, _sktype, _type, _lower, _upper;
	u32 type = 0, lower = 0, upper = 0;

	अगर (!sk)
		वापस true;

	tsk = tipc_sk(sk);

	_port = sysctl_tipc_sk_filter[0];
	_sktype = sysctl_tipc_sk_filter[1];
	_type = sysctl_tipc_sk_filter[2];
	_lower = sysctl_tipc_sk_filter[3];
	_upper = sysctl_tipc_sk_filter[4];

	अगर (!_port && !_sktype && !_type && !_lower && !_upper)
		वापस true;

	अगर (_port)
		वापस (_port == tsk->portid);

	अगर (_sktype && _sktype != sk->sk_type)
		वापस false;

	अगर (tsk->published) अणु
		p = list_first_entry_or_null(&tsk->खुलाations,
					     काष्ठा खुलाation, binding_sock);
		अगर (p) अणु
			type = p->sr.type;
			lower = p->sr.lower;
			upper = p->sr.upper;
		पूर्ण
	पूर्ण

	अगर (!tipc_sk_type_connectionless(sk)) अणु
		type = tsk->conn_type;
		lower = tsk->conn_instance;
		upper = tsk->conn_instance;
	पूर्ण

	अगर ((_type && _type != type) || (_lower && _lower != lower) ||
	    (_upper && _upper != upper))
		वापस false;

	वापस true;
पूर्ण

u32 tipc_sock_get_portid(काष्ठा sock *sk)
अणु
	वापस (sk) ? (tipc_sk(sk))->portid : 0;
पूर्ण

/**
 * tipc_sk_overlimit1 - check अगर socket rx queue is about to be overloaded,
 *			both the rcv and backlog queues are considered
 * @sk: tipc sk to be checked
 * @skb: tipc msg to be checked
 *
 * Return: true अगर the socket rx queue allocation is > 90%, otherwise false
 */

bool tipc_sk_overlimit1(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	atomic_t *dcnt = &tipc_sk(sk)->dupl_rcvcnt;
	अचिन्हित पूर्णांक lim = rcvbuf_limit(sk, skb) + atomic_पढ़ो(dcnt);
	अचिन्हित पूर्णांक qsize = sk->sk_backlog.len + sk_rmem_alloc_get(sk);

	वापस (qsize > lim * 90 / 100);
पूर्ण

/**
 * tipc_sk_overlimit2 - check अगर socket rx queue is about to be overloaded,
 *			only the rcv queue is considered
 * @sk: tipc sk to be checked
 * @skb: tipc msg to be checked
 *
 * Return: true अगर the socket rx queue allocation is > 90%, otherwise false
 */

bool tipc_sk_overlimit2(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक lim = rcvbuf_limit(sk, skb);
	अचिन्हित पूर्णांक qsize = sk_rmem_alloc_get(sk);

	वापस (qsize > lim * 90 / 100);
पूर्ण

/**
 * tipc_sk_dump - dump TIPC socket
 * @sk: tipc sk to be dumped
 * @dqueues: biपंचांगask to decide अगर any socket queue to be dumped?
 *           - TIPC_DUMP_NONE: करोn't dump socket queues
 *           - TIPC_DUMP_SK_SNDQ: dump socket send queue
 *           - TIPC_DUMP_SK_RCVQ: dump socket rcv queue
 *           - TIPC_DUMP_SK_BKLGQ: dump socket backlog queue
 *           - TIPC_DUMP_ALL: dump all the socket queues above
 * @buf: वापसed buffer of dump data in क्रमmat
 */
पूर्णांक tipc_sk_dump(काष्ठा sock *sk, u16 dqueues, अक्षर *buf)
अणु
	पूर्णांक i = 0;
	माप_प्रकार sz = (dqueues) ? SK_LMAX : SK_LMIN;
	काष्ठा tipc_sock *tsk;
	काष्ठा खुलाation *p;
	bool tsk_connected;

	अगर (!sk) अणु
		i += scnम_लिखो(buf, sz, "sk data: (null)\n");
		वापस i;
	पूर्ण

	tsk = tipc_sk(sk);
	tsk_connected = !tipc_sk_type_connectionless(sk);

	i += scnम_लिखो(buf, sz, "sk data: %u", sk->sk_type);
	i += scnम_लिखो(buf + i, sz - i, " %d", sk->sk_state);
	i += scnम_लिखो(buf + i, sz - i, " %x", tsk_own_node(tsk));
	i += scnम_लिखो(buf + i, sz - i, " %u", tsk->portid);
	i += scnम_लिखो(buf + i, sz - i, " | %u", tsk_connected);
	अगर (tsk_connected) अणु
		i += scnम_लिखो(buf + i, sz - i, " %x", tsk_peer_node(tsk));
		i += scnम_लिखो(buf + i, sz - i, " %u", tsk_peer_port(tsk));
		i += scnम_लिखो(buf + i, sz - i, " %u", tsk->conn_type);
		i += scnम_लिखो(buf + i, sz - i, " %u", tsk->conn_instance);
	पूर्ण
	i += scnम_लिखो(buf + i, sz - i, " | %u", tsk->published);
	अगर (tsk->published) अणु
		p = list_first_entry_or_null(&tsk->खुलाations,
					     काष्ठा खुलाation, binding_sock);
		i += scnम_लिखो(buf + i, sz - i, " %u", (p) ? p->sr.type : 0);
		i += scnम_लिखो(buf + i, sz - i, " %u", (p) ? p->sr.lower : 0);
		i += scnम_लिखो(buf + i, sz - i, " %u", (p) ? p->sr.upper : 0);
	पूर्ण
	i += scnम_लिखो(buf + i, sz - i, " | %u", tsk->snd_win);
	i += scnम_लिखो(buf + i, sz - i, " %u", tsk->rcv_win);
	i += scnम_लिखो(buf + i, sz - i, " %u", tsk->max_pkt);
	i += scnम_लिखो(buf + i, sz - i, " %x", tsk->peer_caps);
	i += scnम_लिखो(buf + i, sz - i, " %u", tsk->cong_link_cnt);
	i += scnम_लिखो(buf + i, sz - i, " %u", tsk->snt_unacked);
	i += scnम_लिखो(buf + i, sz - i, " %u", tsk->rcv_unacked);
	i += scnम_लिखो(buf + i, sz - i, " %u", atomic_पढ़ो(&tsk->dupl_rcvcnt));
	i += scnम_लिखो(buf + i, sz - i, " %u", sk->sk_shutकरोwn);
	i += scnम_लिखो(buf + i, sz - i, " | %d", sk_wmem_alloc_get(sk));
	i += scnम_लिखो(buf + i, sz - i, " %d", sk->sk_sndbuf);
	i += scnम_लिखो(buf + i, sz - i, " | %d", sk_rmem_alloc_get(sk));
	i += scnम_लिखो(buf + i, sz - i, " %d", sk->sk_rcvbuf);
	i += scnम_लिखो(buf + i, sz - i, " | %d\n", READ_ONCE(sk->sk_backlog.len));

	अगर (dqueues & TIPC_DUMP_SK_SNDQ) अणु
		i += scnम_लिखो(buf + i, sz - i, "sk_write_queue: ");
		i += tipc_list_dump(&sk->sk_ग_लिखो_queue, false, buf + i);
	पूर्ण

	अगर (dqueues & TIPC_DUMP_SK_RCVQ) अणु
		i += scnम_लिखो(buf + i, sz - i, "sk_receive_queue: ");
		i += tipc_list_dump(&sk->sk_receive_queue, false, buf + i);
	पूर्ण

	अगर (dqueues & TIPC_DUMP_SK_BKLGQ) अणु
		i += scnम_लिखो(buf + i, sz - i, "sk_backlog:\n  head ");
		i += tipc_skb_dump(sk->sk_backlog.head, false, buf + i);
		अगर (sk->sk_backlog.tail != sk->sk_backlog.head) अणु
			i += scnम_लिखो(buf + i, sz - i, "  tail ");
			i += tipc_skb_dump(sk->sk_backlog.tail, false,
					   buf + i);
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण
