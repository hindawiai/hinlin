<शैली गुरु>
/*
 * Copyright (c) 2006, 2018 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <net/tcp.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/addrconf.h>

#समावेश "rds.h"
#समावेश "tcp.h"

/* only क्रम info exporting */
अटल DEFINE_SPINLOCK(rds_tcp_tc_list_lock);
अटल LIST_HEAD(rds_tcp_tc_list);

/* rds_tcp_tc_count counts only IPv4 connections.
 * rds6_tcp_tc_count counts both IPv4 and IPv6 connections.
 */
अटल अचिन्हित पूर्णांक rds_tcp_tc_count;
#अगर IS_ENABLED(CONFIG_IPV6)
अटल अचिन्हित पूर्णांक rds6_tcp_tc_count;
#पूर्ण_अगर

/* Track rds_tcp_connection काष्ठाs so they can be cleaned up */
अटल DEFINE_SPINLOCK(rds_tcp_conn_lock);
अटल LIST_HEAD(rds_tcp_conn_list);
अटल atomic_t rds_tcp_unloading = ATOMIC_INIT(0);

अटल काष्ठा kmem_cache *rds_tcp_conn_slab;

अटल पूर्णांक rds_tcp_skbuf_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *fpos);

अटल पूर्णांक rds_tcp_min_sndbuf = SOCK_MIN_SNDBUF;
अटल पूर्णांक rds_tcp_min_rcvbuf = SOCK_MIN_RCVBUF;

अटल काष्ठा ctl_table rds_tcp_sysctl_table[] = अणु
#घोषणा	RDS_TCP_SNDBUF	0
	अणु
		.procname       = "rds_tcp_sndbuf",
		/* data is per-net poपूर्णांकer */
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = rds_tcp_skbuf_handler,
		.extra1		= &rds_tcp_min_sndbuf,
	पूर्ण,
#घोषणा	RDS_TCP_RCVBUF	1
	अणु
		.procname       = "rds_tcp_rcvbuf",
		/* data is per-net poपूर्णांकer */
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = rds_tcp_skbuf_handler,
		.extra1		= &rds_tcp_min_rcvbuf,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

u32 rds_tcp_ग_लिखो_seq(काष्ठा rds_tcp_connection *tc)
अणु
	/* seq# of the last byte of data in tcp send buffer */
	वापस tcp_sk(tc->t_sock->sk)->ग_लिखो_seq;
पूर्ण

u32 rds_tcp_snd_una(काष्ठा rds_tcp_connection *tc)
अणु
	वापस tcp_sk(tc->t_sock->sk)->snd_una;
पूर्ण

व्योम rds_tcp_restore_callbacks(काष्ठा socket *sock,
			       काष्ठा rds_tcp_connection *tc)
अणु
	rdsdebug("restoring sock %p callbacks from tc %p\n", sock, tc);
	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);

	/* करोne under the callback_lock to serialize with ग_लिखो_space */
	spin_lock(&rds_tcp_tc_list_lock);
	list_del_init(&tc->t_list_item);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds6_tcp_tc_count--;
#पूर्ण_अगर
	अगर (!tc->t_cpath->cp_conn->c_isv6)
		rds_tcp_tc_count--;
	spin_unlock(&rds_tcp_tc_list_lock);

	tc->t_sock = शून्य;

	sock->sk->sk_ग_लिखो_space = tc->t_orig_ग_लिखो_space;
	sock->sk->sk_data_पढ़ोy = tc->t_orig_data_पढ़ोy;
	sock->sk->sk_state_change = tc->t_orig_state_change;
	sock->sk->sk_user_data = शून्य;

	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);
पूर्ण

/*
 * rds_tcp_reset_callbacks() चयनes the to the new sock and
 * वापसs the existing tc->t_sock.
 *
 * The only functions that set tc->t_sock are rds_tcp_set_callbacks
 * and rds_tcp_reset_callbacks.  Send and receive trust that
 * it is set.  The असलence of RDS_CONN_UP bit protects those paths
 * from being called जबतक it isn't set.
 */
व्योम rds_tcp_reset_callbacks(काष्ठा socket *sock,
			     काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;
	काष्ठा socket *osock = tc->t_sock;

	अगर (!osock)
		जाओ newsock;

	/* Need to resolve a duelling SYN between peers.
	 * We have an outstanding SYN to this peer, which may
	 * potentially have transitioned to the RDS_CONN_UP state,
	 * so we must quiesce any send thपढ़ोs beक्रमe resetting
	 * cp_transport_data. We quiesce these thपढ़ोs by setting
	 * cp_state to something other than RDS_CONN_UP, and then
	 * रुकोing क्रम any existing thपढ़ोs in rds_send_xmit to
	 * complete release_in_xmit(). (Subsequent thपढ़ोs entering
	 * rds_send_xmit() will bail on !rds_conn_up().
	 *
	 * However an incoming syn-ack at this poपूर्णांक would end up
	 * marking the conn as RDS_CONN_UP, and would again permit
	 * rds_send_xmi() thपढ़ोs through, so ideally we would
	 * synchronize on RDS_CONN_UP after lock_sock(), but cannot
	 * करो that: रुकोing on !RDS_IN_XMIT after lock_sock() may
	 * end up deadlocking with tcp_sendmsg(), and the RDS_IN_XMIT
	 * would not get set. As a result, we set c_state to
	 * RDS_CONN_RESETTTING, to ensure that rds_tcp_state_change
	 * cannot mark rds_conn_path_up() in the winकरोw beक्रमe lock_sock()
	 */
	atomic_set(&cp->cp_state, RDS_CONN_RESETTING);
	रुको_event(cp->cp_रुकोq, !test_bit(RDS_IN_XMIT, &cp->cp_flags));
	lock_sock(osock->sk);
	/* reset receive side state क्रम rds_tcp_data_recv() क्रम osock  */
	cancel_delayed_work_sync(&cp->cp_send_w);
	cancel_delayed_work_sync(&cp->cp_recv_w);
	अगर (tc->t_tinc) अणु
		rds_inc_put(&tc->t_tinc->ti_inc);
		tc->t_tinc = शून्य;
	पूर्ण
	tc->t_tinc_hdr_rem = माप(काष्ठा rds_header);
	tc->t_tinc_data_rem = 0;
	rds_tcp_restore_callbacks(osock, tc);
	release_sock(osock->sk);
	sock_release(osock);
newsock:
	rds_send_path_reset(cp);
	lock_sock(sock->sk);
	rds_tcp_set_callbacks(sock, cp);
	release_sock(sock->sk);
पूर्ण

/* Add tc to rds_tcp_tc_list and set tc->t_sock. See comments
 * above rds_tcp_reset_callbacks क्रम notes about synchronization
 * with data path
 */
व्योम rds_tcp_set_callbacks(काष्ठा socket *sock, काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;

	rdsdebug("setting sock %p callbacks to tc %p\n", sock, tc);
	ग_लिखो_lock_bh(&sock->sk->sk_callback_lock);

	/* करोne under the callback_lock to serialize with ग_लिखो_space */
	spin_lock(&rds_tcp_tc_list_lock);
	list_add_tail(&tc->t_list_item, &rds_tcp_tc_list);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds6_tcp_tc_count++;
#पूर्ण_अगर
	अगर (!tc->t_cpath->cp_conn->c_isv6)
		rds_tcp_tc_count++;
	spin_unlock(&rds_tcp_tc_list_lock);

	/* accepted sockets need our listen data पढ़ोy unकरोne */
	अगर (sock->sk->sk_data_पढ़ोy == rds_tcp_listen_data_पढ़ोy)
		sock->sk->sk_data_पढ़ोy = sock->sk->sk_user_data;

	tc->t_sock = sock;
	tc->t_cpath = cp;
	tc->t_orig_data_पढ़ोy = sock->sk->sk_data_पढ़ोy;
	tc->t_orig_ग_लिखो_space = sock->sk->sk_ग_लिखो_space;
	tc->t_orig_state_change = sock->sk->sk_state_change;

	sock->sk->sk_user_data = cp;
	sock->sk->sk_data_पढ़ोy = rds_tcp_data_पढ़ोy;
	sock->sk->sk_ग_लिखो_space = rds_tcp_ग_लिखो_space;
	sock->sk->sk_state_change = rds_tcp_state_change;

	ग_लिखो_unlock_bh(&sock->sk->sk_callback_lock);
पूर्ण

/* Handle RDS_INFO_TCP_SOCKETS socket option.  It only वापसs IPv4
 * connections क्रम backward compatibility.
 */
अटल व्योम rds_tcp_tc_info(काष्ठा socket *rds_sock, अचिन्हित पूर्णांक len,
			    काष्ठा rds_info_iterator *iter,
			    काष्ठा rds_info_lengths *lens)
अणु
	काष्ठा rds_info_tcp_socket tsinfo;
	काष्ठा rds_tcp_connection *tc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rds_tcp_tc_list_lock, flags);

	अगर (len / माप(tsinfo) < rds_tcp_tc_count)
		जाओ out;

	list_क्रम_each_entry(tc, &rds_tcp_tc_list, t_list_item) अणु
		काष्ठा inet_sock *inet = inet_sk(tc->t_sock->sk);

		अगर (tc->t_cpath->cp_conn->c_isv6)
			जारी;

		tsinfo.local_addr = inet->inet_saddr;
		tsinfo.local_port = inet->inet_sport;
		tsinfo.peer_addr = inet->inet_daddr;
		tsinfo.peer_port = inet->inet_dport;

		tsinfo.hdr_rem = tc->t_tinc_hdr_rem;
		tsinfo.data_rem = tc->t_tinc_data_rem;
		tsinfo.last_sent_nxt = tc->t_last_sent_nxt;
		tsinfo.last_expected_una = tc->t_last_expected_una;
		tsinfo.last_seen_una = tc->t_last_seen_una;
		tsinfo.tos = tc->t_cpath->cp_conn->c_tos;

		rds_info_copy(iter, &tsinfo, माप(tsinfo));
	पूर्ण

out:
	lens->nr = rds_tcp_tc_count;
	lens->each = माप(tsinfo);

	spin_unlock_irqrestore(&rds_tcp_tc_list_lock, flags);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* Handle RDS6_INFO_TCP_SOCKETS socket option. It वापसs both IPv4 and
 * IPv6 connections. IPv4 connection address is वापसed in an IPv4 mapped
 * address.
 */
अटल व्योम rds6_tcp_tc_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			     काष्ठा rds_info_iterator *iter,
			     काष्ठा rds_info_lengths *lens)
अणु
	काष्ठा rds6_info_tcp_socket tsinfo6;
	काष्ठा rds_tcp_connection *tc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rds_tcp_tc_list_lock, flags);

	अगर (len / माप(tsinfo6) < rds6_tcp_tc_count)
		जाओ out;

	list_क्रम_each_entry(tc, &rds_tcp_tc_list, t_list_item) अणु
		काष्ठा sock *sk = tc->t_sock->sk;
		काष्ठा inet_sock *inet = inet_sk(sk);

		tsinfo6.local_addr = sk->sk_v6_rcv_saddr;
		tsinfo6.local_port = inet->inet_sport;
		tsinfo6.peer_addr = sk->sk_v6_daddr;
		tsinfo6.peer_port = inet->inet_dport;

		tsinfo6.hdr_rem = tc->t_tinc_hdr_rem;
		tsinfo6.data_rem = tc->t_tinc_data_rem;
		tsinfo6.last_sent_nxt = tc->t_last_sent_nxt;
		tsinfo6.last_expected_una = tc->t_last_expected_una;
		tsinfo6.last_seen_una = tc->t_last_seen_una;

		rds_info_copy(iter, &tsinfo6, माप(tsinfo6));
	पूर्ण

out:
	lens->nr = rds6_tcp_tc_count;
	lens->each = माप(tsinfo6);

	spin_unlock_irqrestore(&rds_tcp_tc_list_lock, flags);
पूर्ण
#पूर्ण_अगर

पूर्णांक rds_tcp_laddr_check(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			__u32 scope_id)
अणु
	काष्ठा net_device *dev = शून्य;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्णांक ret;
#पूर्ण_अगर

	अगर (ipv6_addr_v4mapped(addr)) अणु
		अगर (inet_addr_type(net, addr->s6_addr32[3]) == RTN_LOCAL)
			वापस 0;
		वापस -EADDRNOTAVAIL;
	पूर्ण

	/* If the scope_id is specअगरied, check only those addresses
	 * hosted on the specअगरied पूर्णांकerface.
	 */
	अगर (scope_id != 0) अणु
		rcu_पढ़ो_lock();
		dev = dev_get_by_index_rcu(net, scope_id);
		/* scope_id is not valid... */
		अगर (!dev) अणु
			rcu_पढ़ो_unlock();
			वापस -EADDRNOTAVAIL;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	ret = ipv6_chk_addr(net, addr, dev, 0);
	अगर (ret)
		वापस 0;
#पूर्ण_अगर
	वापस -EADDRNOTAVAIL;
पूर्ण

अटल व्योम rds_tcp_conn_मुक्त(व्योम *arg)
अणु
	काष्ठा rds_tcp_connection *tc = arg;
	अचिन्हित दीर्घ flags;

	rdsdebug("freeing tc %p\n", tc);

	spin_lock_irqsave(&rds_tcp_conn_lock, flags);
	अगर (!tc->t_tcp_node_detached)
		list_del(&tc->t_tcp_node);
	spin_unlock_irqrestore(&rds_tcp_conn_lock, flags);

	kmem_cache_मुक्त(rds_tcp_conn_slab, tc);
पूर्ण

अटल पूर्णांक rds_tcp_conn_alloc(काष्ठा rds_connection *conn, gfp_t gfp)
अणु
	काष्ठा rds_tcp_connection *tc;
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < RDS_MPATH_WORKERS; i++) अणु
		tc = kmem_cache_alloc(rds_tcp_conn_slab, gfp);
		अगर (!tc) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
		mutex_init(&tc->t_conn_path_lock);
		tc->t_sock = शून्य;
		tc->t_tinc = शून्य;
		tc->t_tinc_hdr_rem = माप(काष्ठा rds_header);
		tc->t_tinc_data_rem = 0;

		conn->c_path[i].cp_transport_data = tc;
		tc->t_cpath = &conn->c_path[i];
		tc->t_tcp_node_detached = true;

		rdsdebug("rds_conn_path [%d] tc %p\n", i,
			 conn->c_path[i].cp_transport_data);
	पूर्ण
	spin_lock_irq(&rds_tcp_conn_lock);
	क्रम (i = 0; i < RDS_MPATH_WORKERS; i++) अणु
		tc = conn->c_path[i].cp_transport_data;
		tc->t_tcp_node_detached = false;
		list_add_tail(&tc->t_tcp_node, &rds_tcp_conn_list);
	पूर्ण
	spin_unlock_irq(&rds_tcp_conn_lock);
fail:
	अगर (ret) अणु
		क्रम (j = 0; j < i; j++)
			rds_tcp_conn_मुक्त(conn->c_path[j].cp_transport_data);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool list_has_conn(काष्ठा list_head *list, काष्ठा rds_connection *conn)
अणु
	काष्ठा rds_tcp_connection *tc, *_tc;

	list_क्रम_each_entry_safe(tc, _tc, list, t_tcp_node) अणु
		अगर (tc->t_cpath->cp_conn == conn)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम rds_tcp_set_unloading(व्योम)
अणु
	atomic_set(&rds_tcp_unloading, 1);
पूर्ण

अटल bool rds_tcp_is_unloading(काष्ठा rds_connection *conn)
अणु
	वापस atomic_पढ़ो(&rds_tcp_unloading) != 0;
पूर्ण

अटल व्योम rds_tcp_destroy_conns(व्योम)
अणु
	काष्ठा rds_tcp_connection *tc, *_tc;
	LIST_HEAD(पंचांगp_list);

	/* aव्योम calling conn_destroy with irqs off */
	spin_lock_irq(&rds_tcp_conn_lock);
	list_क्रम_each_entry_safe(tc, _tc, &rds_tcp_conn_list, t_tcp_node) अणु
		अगर (!list_has_conn(&पंचांगp_list, tc->t_cpath->cp_conn))
			list_move_tail(&tc->t_tcp_node, &पंचांगp_list);
	पूर्ण
	spin_unlock_irq(&rds_tcp_conn_lock);

	list_क्रम_each_entry_safe(tc, _tc, &पंचांगp_list, t_tcp_node)
		rds_conn_destroy(tc->t_cpath->cp_conn);
पूर्ण

अटल व्योम rds_tcp_निकास(व्योम);

अटल u8 rds_tcp_get_tos_map(u8 tos)
अणु
	/* all user tos mapped to शेष 0 क्रम TCP transport */
	वापस 0;
पूर्ण

काष्ठा rds_transport rds_tcp_transport = अणु
	.laddr_check		= rds_tcp_laddr_check,
	.xmit_path_prepare	= rds_tcp_xmit_path_prepare,
	.xmit_path_complete	= rds_tcp_xmit_path_complete,
	.xmit			= rds_tcp_xmit,
	.recv_path		= rds_tcp_recv_path,
	.conn_alloc		= rds_tcp_conn_alloc,
	.conn_मुक्त		= rds_tcp_conn_मुक्त,
	.conn_path_connect	= rds_tcp_conn_path_connect,
	.conn_path_shutकरोwn	= rds_tcp_conn_path_shutकरोwn,
	.inc_copy_to_user	= rds_tcp_inc_copy_to_user,
	.inc_मुक्त		= rds_tcp_inc_मुक्त,
	.stats_info_copy	= rds_tcp_stats_info_copy,
	.निकास			= rds_tcp_निकास,
	.get_tos_map		= rds_tcp_get_tos_map,
	.t_owner		= THIS_MODULE,
	.t_name			= "tcp",
	.t_type			= RDS_TRANS_TCP,
	.t_prefer_loopback	= 1,
	.t_mp_capable		= 1,
	.t_unloading		= rds_tcp_is_unloading,
पूर्ण;

अटल अचिन्हित पूर्णांक rds_tcp_netid;

/* per-network namespace निजी data क्रम this module */
काष्ठा rds_tcp_net अणु
	काष्ठा socket *rds_tcp_listen_sock;
	काष्ठा work_काष्ठा rds_tcp_accept_w;
	काष्ठा ctl_table_header *rds_tcp_sysctl;
	काष्ठा ctl_table *ctl_table;
	पूर्णांक sndbuf_size;
	पूर्णांक rcvbuf_size;
पूर्ण;

/* All module specअगरic customizations to the RDS-TCP socket should be करोne in
 * rds_tcp_tune() and applied after socket creation.
 */
व्योम rds_tcp_tune(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);

	tcp_sock_set_nodelay(sock->sk);
	lock_sock(sk);
	अगर (rtn->sndbuf_size > 0) अणु
		sk->sk_sndbuf = rtn->sndbuf_size;
		sk->sk_userlocks |= SOCK_SNDBUF_LOCK;
	पूर्ण
	अगर (rtn->rcvbuf_size > 0) अणु
		sk->sk_sndbuf = rtn->rcvbuf_size;
		sk->sk_userlocks |= SOCK_RCVBUF_LOCK;
	पूर्ण
	release_sock(sk);
पूर्ण

अटल व्योम rds_tcp_accept_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rds_tcp_net *rtn = container_of(work,
					       काष्ठा rds_tcp_net,
					       rds_tcp_accept_w);

	जबतक (rds_tcp_accept_one(rtn->rds_tcp_listen_sock) == 0)
		cond_resched();
पूर्ण

व्योम rds_tcp_accept_work(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);

	queue_work(rds_wq, &rtn->rds_tcp_accept_w);
पूर्ण

अटल __net_init पूर्णांक rds_tcp_init_net(काष्ठा net *net)
अणु
	काष्ठा rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);
	काष्ठा ctl_table *tbl;
	पूर्णांक err = 0;

	स_रखो(rtn, 0, माप(*rtn));

	/* अणुsnd, rcvपूर्णbuf_size शेष to 0, which implies we let the
	 * stack pick the value, and permit स्वतः-tuning of buffer size.
	 */
	अगर (net == &init_net) अणु
		tbl = rds_tcp_sysctl_table;
	पूर्ण अन्यथा अणु
		tbl = kmemdup(rds_tcp_sysctl_table,
			      माप(rds_tcp_sysctl_table), GFP_KERNEL);
		अगर (!tbl) अणु
			pr_warn("could not set allocate sysctl table\n");
			वापस -ENOMEM;
		पूर्ण
		rtn->ctl_table = tbl;
	पूर्ण
	tbl[RDS_TCP_SNDBUF].data = &rtn->sndbuf_size;
	tbl[RDS_TCP_RCVBUF].data = &rtn->rcvbuf_size;
	rtn->rds_tcp_sysctl = रेजिस्टर_net_sysctl(net, "net/rds/tcp", tbl);
	अगर (!rtn->rds_tcp_sysctl) अणु
		pr_warn("could not register sysctl\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
	rtn->rds_tcp_listen_sock = rds_tcp_listen_init(net, true);
#अन्यथा
	rtn->rds_tcp_listen_sock = rds_tcp_listen_init(net, false);
#पूर्ण_अगर
	अगर (!rtn->rds_tcp_listen_sock) अणु
		pr_warn("could not set up IPv6 listen sock\n");

#अगर IS_ENABLED(CONFIG_IPV6)
		/* Try IPv4 as some प्रणालीs disable IPv6 */
		rtn->rds_tcp_listen_sock = rds_tcp_listen_init(net, false);
		अगर (!rtn->rds_tcp_listen_sock) अणु
#पूर्ण_अगर
			unरेजिस्टर_net_sysctl_table(rtn->rds_tcp_sysctl);
			rtn->rds_tcp_sysctl = शून्य;
			err = -EAFNOSUPPORT;
			जाओ fail;
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	INIT_WORK(&rtn->rds_tcp_accept_w, rds_tcp_accept_worker);
	वापस 0;

fail:
	अगर (net != &init_net)
		kमुक्त(tbl);
	वापस err;
पूर्ण

अटल व्योम rds_tcp_समाप्त_sock(काष्ठा net *net)
अणु
	काष्ठा rds_tcp_connection *tc, *_tc;
	LIST_HEAD(पंचांगp_list);
	काष्ठा rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);
	काष्ठा socket *lsock = rtn->rds_tcp_listen_sock;

	rtn->rds_tcp_listen_sock = शून्य;
	rds_tcp_listen_stop(lsock, &rtn->rds_tcp_accept_w);
	spin_lock_irq(&rds_tcp_conn_lock);
	list_क्रम_each_entry_safe(tc, _tc, &rds_tcp_conn_list, t_tcp_node) अणु
		काष्ठा net *c_net = पढ़ो_pnet(&tc->t_cpath->cp_conn->c_net);

		अगर (net != c_net)
			जारी;
		अगर (!list_has_conn(&पंचांगp_list, tc->t_cpath->cp_conn)) अणु
			list_move_tail(&tc->t_tcp_node, &पंचांगp_list);
		पूर्ण अन्यथा अणु
			list_del(&tc->t_tcp_node);
			tc->t_tcp_node_detached = true;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&rds_tcp_conn_lock);
	list_क्रम_each_entry_safe(tc, _tc, &पंचांगp_list, t_tcp_node)
		rds_conn_destroy(tc->t_cpath->cp_conn);
पूर्ण

अटल व्योम __net_निकास rds_tcp_निकास_net(काष्ठा net *net)
अणु
	काष्ठा rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);

	rds_tcp_समाप्त_sock(net);

	अगर (rtn->rds_tcp_sysctl)
		unरेजिस्टर_net_sysctl_table(rtn->rds_tcp_sysctl);

	अगर (net != &init_net)
		kमुक्त(rtn->ctl_table);
पूर्ण

अटल काष्ठा pernet_operations rds_tcp_net_ops = अणु
	.init = rds_tcp_init_net,
	.निकास = rds_tcp_निकास_net,
	.id = &rds_tcp_netid,
	.size = माप(काष्ठा rds_tcp_net),
पूर्ण;

व्योम *rds_tcp_listen_sock_def_पढ़ोable(काष्ठा net *net)
अणु
	काष्ठा rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);
	काष्ठा socket *lsock = rtn->rds_tcp_listen_sock;

	अगर (!lsock)
		वापस शून्य;

	वापस lsock->sk->sk_user_data;
पूर्ण

/* when sysctl is used to modअगरy some kernel socket parameters,this
 * function  resets the RDS connections in that netns  so that we can
 * restart with new parameters.  The assumption is that such reset
 * events are few and far-between.
 */
अटल व्योम rds_tcp_sysctl_reset(काष्ठा net *net)
अणु
	काष्ठा rds_tcp_connection *tc, *_tc;

	spin_lock_irq(&rds_tcp_conn_lock);
	list_क्रम_each_entry_safe(tc, _tc, &rds_tcp_conn_list, t_tcp_node) अणु
		काष्ठा net *c_net = पढ़ो_pnet(&tc->t_cpath->cp_conn->c_net);

		अगर (net != c_net || !tc->t_sock)
			जारी;

		/* reconnect with new parameters */
		rds_conn_path_drop(tc->t_cpath, false);
	पूर्ण
	spin_unlock_irq(&rds_tcp_conn_lock);
पूर्ण

अटल पूर्णांक rds_tcp_skbuf_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *fpos)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	पूर्णांक err;

	err = proc_करोपूर्णांकvec_minmax(ctl, ग_लिखो, buffer, lenp, fpos);
	अगर (err < 0) अणु
		pr_warn("Invalid input. Must be >= %d\n",
			*(पूर्णांक *)(ctl->extra1));
		वापस err;
	पूर्ण
	अगर (ग_लिखो)
		rds_tcp_sysctl_reset(net);
	वापस 0;
पूर्ण

अटल व्योम rds_tcp_निकास(व्योम)
अणु
	rds_tcp_set_unloading();
	synchronize_rcu();
	rds_info_deरेजिस्टर_func(RDS_INFO_TCP_SOCKETS, rds_tcp_tc_info);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_deरेजिस्टर_func(RDS6_INFO_TCP_SOCKETS, rds6_tcp_tc_info);
#पूर्ण_अगर
	unरेजिस्टर_pernet_device(&rds_tcp_net_ops);
	rds_tcp_destroy_conns();
	rds_trans_unरेजिस्टर(&rds_tcp_transport);
	rds_tcp_recv_निकास();
	kmem_cache_destroy(rds_tcp_conn_slab);
पूर्ण
module_निकास(rds_tcp_निकास);

अटल पूर्णांक rds_tcp_init(व्योम)
अणु
	पूर्णांक ret;

	rds_tcp_conn_slab = kmem_cache_create("rds_tcp_connection",
					      माप(काष्ठा rds_tcp_connection),
					      0, 0, शून्य);
	अगर (!rds_tcp_conn_slab) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = rds_tcp_recv_init();
	अगर (ret)
		जाओ out_slab;

	ret = रेजिस्टर_pernet_device(&rds_tcp_net_ops);
	अगर (ret)
		जाओ out_recv;

	rds_trans_रेजिस्टर(&rds_tcp_transport);

	rds_info_रेजिस्टर_func(RDS_INFO_TCP_SOCKETS, rds_tcp_tc_info);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_रेजिस्टर_func(RDS6_INFO_TCP_SOCKETS, rds6_tcp_tc_info);
#पूर्ण_अगर

	जाओ out;
out_recv:
	rds_tcp_recv_निकास();
out_slab:
	kmem_cache_destroy(rds_tcp_conn_slab);
out:
	वापस ret;
पूर्ण
module_init(rds_tcp_init);

MODULE_AUTHOR("Oracle Corporation <rds-devel@oss.oracle.com>");
MODULE_DESCRIPTION("RDS: TCP transport");
MODULE_LICENSE("Dual BSD/GPL");
