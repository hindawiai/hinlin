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
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/addrconf.h>

#समावेश "rds.h"
#समावेश "loop.h"

#घोषणा RDS_CONNECTION_HASH_BITS 12
#घोषणा RDS_CONNECTION_HASH_ENTRIES (1 << RDS_CONNECTION_HASH_BITS)
#घोषणा RDS_CONNECTION_HASH_MASK (RDS_CONNECTION_HASH_ENTRIES - 1)

/* converting this to RCU is a chore क्रम another day.. */
अटल DEFINE_SPINLOCK(rds_conn_lock);
अटल अचिन्हित दीर्घ rds_conn_count;
अटल काष्ठा hlist_head rds_conn_hash[RDS_CONNECTION_HASH_ENTRIES];
अटल काष्ठा kmem_cache *rds_conn_slab;

अटल काष्ठा hlist_head *rds_conn_bucket(स्थिर काष्ठा in6_addr *laddr,
					  स्थिर काष्ठा in6_addr *faddr)
अणु
	अटल u32 rds6_hash_secret __पढ़ो_mostly;
	अटल u32 rds_hash_secret __पढ़ो_mostly;

	u32 lhash, fhash, hash;

	net_get_अक्रमom_once(&rds_hash_secret, माप(rds_hash_secret));
	net_get_अक्रमom_once(&rds6_hash_secret, माप(rds6_hash_secret));

	lhash = (__क्रमce u32)laddr->s6_addr32[3];
#अगर IS_ENABLED(CONFIG_IPV6)
	fhash = __ipv6_addr_jhash(faddr, rds6_hash_secret);
#अन्यथा
	fhash = (__क्रमce u32)faddr->s6_addr32[3];
#पूर्ण_अगर
	hash = __inet_ehashfn(lhash, 0, fhash, 0, rds_hash_secret);

	वापस &rds_conn_hash[hash & RDS_CONNECTION_HASH_MASK];
पूर्ण

#घोषणा rds_conn_info_set(var, test, suffix) करो अणु		\
	अगर (test)						\
		var |= RDS_INFO_CONNECTION_FLAG_##suffix;	\
पूर्ण जबतक (0)

/* rcu पढ़ो lock must be held or the connection spinlock */
अटल काष्ठा rds_connection *rds_conn_lookup(काष्ठा net *net,
					      काष्ठा hlist_head *head,
					      स्थिर काष्ठा in6_addr *laddr,
					      स्थिर काष्ठा in6_addr *faddr,
					      काष्ठा rds_transport *trans,
					      u8 tos, पूर्णांक dev_अगर)
अणु
	काष्ठा rds_connection *conn, *ret = शून्य;

	hlist_क्रम_each_entry_rcu(conn, head, c_hash_node) अणु
		अगर (ipv6_addr_equal(&conn->c_faddr, faddr) &&
		    ipv6_addr_equal(&conn->c_laddr, laddr) &&
		    conn->c_trans == trans &&
		    conn->c_tos == tos &&
		    net == rds_conn_net(conn) &&
		    conn->c_dev_अगर == dev_अगर) अणु
			ret = conn;
			अवरोध;
		पूर्ण
	पूर्ण
	rdsdebug("returning conn %p for %pI6c -> %pI6c\n", ret,
		 laddr, faddr);
	वापस ret;
पूर्ण

/*
 * This is called by transports as they're bringing करोwn a connection.
 * It clears partial message state so that the transport can start sending
 * and receiving over this connection again in the future.  It is up to
 * the transport to have serialized this call with its send and recv.
 */
अटल व्योम rds_conn_path_reset(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_connection *conn = cp->cp_conn;

	rdsdebug("connection %pI6c to %pI6c reset\n",
		 &conn->c_laddr, &conn->c_faddr);

	rds_stats_inc(s_conn_reset);
	rds_send_path_reset(cp);
	cp->cp_flags = 0;

	/* Do not clear next_rx_seq here, अन्यथा we cannot distinguish
	 * retransmitted packets from new packets, and will hand all
	 * of them to the application. That is not consistent with the
	 * reliability guarantees of RDS. */
पूर्ण

अटल व्योम __rds_conn_path_init(काष्ठा rds_connection *conn,
				 काष्ठा rds_conn_path *cp, bool is_outgoing)
अणु
	spin_lock_init(&cp->cp_lock);
	cp->cp_next_tx_seq = 1;
	init_रुकोqueue_head(&cp->cp_रुकोq);
	INIT_LIST_HEAD(&cp->cp_send_queue);
	INIT_LIST_HEAD(&cp->cp_retrans);

	cp->cp_conn = conn;
	atomic_set(&cp->cp_state, RDS_CONN_DOWN);
	cp->cp_send_gen = 0;
	cp->cp_reconnect_jअगरfies = 0;
	cp->cp_conn->c_proposed_version = RDS_PROTOCOL_VERSION;
	INIT_DELAYED_WORK(&cp->cp_send_w, rds_send_worker);
	INIT_DELAYED_WORK(&cp->cp_recv_w, rds_recv_worker);
	INIT_DELAYED_WORK(&cp->cp_conn_w, rds_connect_worker);
	INIT_WORK(&cp->cp_करोwn_w, rds_shutकरोwn_worker);
	mutex_init(&cp->cp_cm_lock);
	cp->cp_flags = 0;
पूर्ण

/*
 * There is only every one 'conn' क्रम a given pair of addresses in the
 * प्रणाली at a समय.  They contain messages to be retransmitted and so
 * span the lअगरeसमय of the actual underlying transport connections.
 *
 * For now they are not garbage collected once they're created.  They
 * are torn करोwn as the module is हटाओd, अगर ever.
 */
अटल काष्ठा rds_connection *__rds_conn_create(काष्ठा net *net,
						स्थिर काष्ठा in6_addr *laddr,
						स्थिर काष्ठा in6_addr *faddr,
						काष्ठा rds_transport *trans,
						gfp_t gfp, u8 tos,
						पूर्णांक is_outgoing,
						पूर्णांक dev_अगर)
अणु
	काष्ठा rds_connection *conn, *parent = शून्य;
	काष्ठा hlist_head *head = rds_conn_bucket(laddr, faddr);
	काष्ठा rds_transport *loop_trans;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, i;
	पूर्णांक npaths = (trans->t_mp_capable ? RDS_MPATH_WORKERS : 1);

	rcu_पढ़ो_lock();
	conn = rds_conn_lookup(net, head, laddr, faddr, trans, tos, dev_अगर);
	अगर (conn &&
	    conn->c_loopback &&
	    conn->c_trans != &rds_loop_transport &&
	    ipv6_addr_equal(laddr, faddr) &&
	    !is_outgoing) अणु
		/* This is a looped back IB connection, and we're
		 * called by the code handling the incoming connect.
		 * We need a second connection object पूर्णांकo which we
		 * can stick the other QP. */
		parent = conn;
		conn = parent->c_passive;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (conn)
		जाओ out;

	conn = kmem_cache_zalloc(rds_conn_slab, gfp);
	अगर (!conn) अणु
		conn = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	conn->c_path = kसुस्मृति(npaths, माप(काष्ठा rds_conn_path), gfp);
	अगर (!conn->c_path) अणु
		kmem_cache_मुक्त(rds_conn_slab, conn);
		conn = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	INIT_HLIST_NODE(&conn->c_hash_node);
	conn->c_laddr = *laddr;
	conn->c_isv6 = !ipv6_addr_v4mapped(laddr);
	conn->c_faddr = *faddr;
	conn->c_dev_अगर = dev_अगर;
	conn->c_tos = tos;

#अगर IS_ENABLED(CONFIG_IPV6)
	/* If the local address is link local, set c_bound_अगर to be the
	 * index used क्रम this connection.  Otherwise, set it to 0 as
	 * the socket is not bound to an पूर्णांकerface.  c_bound_अगर is used
	 * to look up a socket when a packet is received
	 */
	अगर (ipv6_addr_type(laddr) & IPV6_ADDR_LINKLOCAL)
		conn->c_bound_अगर = dev_अगर;
	अन्यथा
#पूर्ण_अगर
		conn->c_bound_अगर = 0;

	rds_conn_net_set(conn, net);

	ret = rds_cong_get_maps(conn);
	अगर (ret) अणु
		kमुक्त(conn->c_path);
		kmem_cache_मुक्त(rds_conn_slab, conn);
		conn = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	/*
	 * This is where a connection becomes loopback.  If *any* RDS sockets
	 * can bind to the destination address then we'd rather the messages
	 * flow through loopback rather than either transport.
	 */
	loop_trans = rds_trans_get_preferred(net, faddr, conn->c_dev_अगर);
	अगर (loop_trans) अणु
		rds_trans_put(loop_trans);
		conn->c_loopback = 1;
		अगर (trans->t_prefer_loopback) अणु
			अगर (likely(is_outgoing)) अणु
				/* "outgoing" connection to local address.
				 * Protocol says it wants the connection
				 * handled by the loopback transport.
				 * This is what TCP करोes.
				 */
				trans = &rds_loop_transport;
			पूर्ण अन्यथा अणु
				/* No transport currently in use
				 * should end up here, but अगर it
				 * करोes, reset/destroy the connection.
				 */
				kmem_cache_मुक्त(rds_conn_slab, conn);
				conn = ERR_PTR(-EOPNOTSUPP);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	conn->c_trans = trans;

	init_रुकोqueue_head(&conn->c_hs_रुकोq);
	क्रम (i = 0; i < npaths; i++) अणु
		__rds_conn_path_init(conn, &conn->c_path[i],
				     is_outgoing);
		conn->c_path[i].cp_index = i;
	पूर्ण
	rcu_पढ़ो_lock();
	अगर (rds_destroy_pending(conn))
		ret = -ENETDOWN;
	अन्यथा
		ret = trans->conn_alloc(conn, GFP_ATOMIC);
	अगर (ret) अणु
		rcu_पढ़ो_unlock();
		kमुक्त(conn->c_path);
		kmem_cache_मुक्त(rds_conn_slab, conn);
		conn = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	rdsdebug("allocated conn %p for %pI6c -> %pI6c over %s %s\n",
		 conn, laddr, faddr,
		 strnlen(trans->t_name, माप(trans->t_name)) ?
		 trans->t_name : "[unknown]", is_outgoing ? "(outgoing)" : "");

	/*
	 * Since we ran without holding the conn lock, someone could
	 * have created the same conn (either normal or passive) in the
	 * पूर्णांकerim. We check जबतक holding the lock. If we won, we complete
	 * init and वापस our conn. If we lost, we rollback and वापस the
	 * other one.
	 */
	spin_lock_irqsave(&rds_conn_lock, flags);
	अगर (parent) अणु
		/* Creating passive conn */
		अगर (parent->c_passive) अणु
			trans->conn_मुक्त(conn->c_path[0].cp_transport_data);
			kमुक्त(conn->c_path);
			kmem_cache_मुक्त(rds_conn_slab, conn);
			conn = parent->c_passive;
		पूर्ण अन्यथा अणु
			parent->c_passive = conn;
			rds_cong_add_conn(conn);
			rds_conn_count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Creating normal conn */
		काष्ठा rds_connection *found;

		found = rds_conn_lookup(net, head, laddr, faddr, trans,
					tos, dev_अगर);
		अगर (found) अणु
			काष्ठा rds_conn_path *cp;
			पूर्णांक i;

			क्रम (i = 0; i < npaths; i++) अणु
				cp = &conn->c_path[i];
				/* The ->conn_alloc invocation may have
				 * allocated resource क्रम all paths, so all
				 * of them may have to be मुक्तd here.
				 */
				अगर (cp->cp_transport_data)
					trans->conn_मुक्त(cp->cp_transport_data);
			पूर्ण
			kमुक्त(conn->c_path);
			kmem_cache_मुक्त(rds_conn_slab, conn);
			conn = found;
		पूर्ण अन्यथा अणु
			conn->c_my_gen_num = rds_gen_num;
			conn->c_peer_gen_num = 0;
			hlist_add_head_rcu(&conn->c_hash_node, head);
			rds_cong_add_conn(conn);
			rds_conn_count++;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rds_conn_lock, flags);
	rcu_पढ़ो_unlock();

out:
	वापस conn;
पूर्ण

काष्ठा rds_connection *rds_conn_create(काष्ठा net *net,
				       स्थिर काष्ठा in6_addr *laddr,
				       स्थिर काष्ठा in6_addr *faddr,
				       काष्ठा rds_transport *trans, u8 tos,
				       gfp_t gfp, पूर्णांक dev_अगर)
अणु
	वापस __rds_conn_create(net, laddr, faddr, trans, gfp, tos, 0, dev_अगर);
पूर्ण
EXPORT_SYMBOL_GPL(rds_conn_create);

काष्ठा rds_connection *rds_conn_create_outgoing(काष्ठा net *net,
						स्थिर काष्ठा in6_addr *laddr,
						स्थिर काष्ठा in6_addr *faddr,
						काष्ठा rds_transport *trans,
						u8 tos, gfp_t gfp, पूर्णांक dev_अगर)
अणु
	वापस __rds_conn_create(net, laddr, faddr, trans, gfp, tos, 1, dev_अगर);
पूर्ण
EXPORT_SYMBOL_GPL(rds_conn_create_outgoing);

व्योम rds_conn_shutकरोwn(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_connection *conn = cp->cp_conn;

	/* shut it करोwn unless it's करोwn alपढ़ोy */
	अगर (!rds_conn_path_transition(cp, RDS_CONN_DOWN, RDS_CONN_DOWN)) अणु
		/*
		 * Quiesce the connection mgmt handlers beक्रमe we start tearing
		 * things करोwn. We करोn't hold the mutex क्रम the entire
		 * duration of the shutकरोwn operation, अन्यथा we may be
		 * deadlocking with the CM handler. Instead, the CM event
		 * handler is supposed to check क्रम state DISCONNECTING
		 */
		mutex_lock(&cp->cp_cm_lock);
		अगर (!rds_conn_path_transition(cp, RDS_CONN_UP,
					      RDS_CONN_DISCONNECTING) &&
		    !rds_conn_path_transition(cp, RDS_CONN_ERROR,
					      RDS_CONN_DISCONNECTING)) अणु
			rds_conn_path_error(cp,
					    "shutdown called in state %d\n",
					    atomic_पढ़ो(&cp->cp_state));
			mutex_unlock(&cp->cp_cm_lock);
			वापस;
		पूर्ण
		mutex_unlock(&cp->cp_cm_lock);

		रुको_event(cp->cp_रुकोq,
			   !test_bit(RDS_IN_XMIT, &cp->cp_flags));
		रुको_event(cp->cp_रुकोq,
			   !test_bit(RDS_RECV_REFILL, &cp->cp_flags));

		conn->c_trans->conn_path_shutकरोwn(cp);
		rds_conn_path_reset(cp);

		अगर (!rds_conn_path_transition(cp, RDS_CONN_DISCONNECTING,
					      RDS_CONN_DOWN) &&
		    !rds_conn_path_transition(cp, RDS_CONN_ERROR,
					      RDS_CONN_DOWN)) अणु
			/* This can happen - eg when we're in the middle of tearing
			 * करोwn the connection, and someone unloads the rds module.
			 * Quite reproducible with loopback connections.
			 * Mostly harmless.
			 *
			 * Note that this also happens with rds-tcp because
			 * we could have triggered rds_conn_path_drop in irq
			 * mode from rds_tcp_state change on the receipt of
			 * a FIN, thus we need to recheck क्रम RDS_CONN_ERROR
			 * here.
			 */
			rds_conn_path_error(cp, "%s: failed to transition "
					    "to state DOWN, current state "
					    "is %d\n", __func__,
					    atomic_पढ़ो(&cp->cp_state));
			वापस;
		पूर्ण
	पूर्ण

	/* Then reconnect अगर it's still live.
	 * The passive side of an IB loopback connection is never added
	 * to the conn hash, so we never trigger a reconnect on this
	 * conn - the reconnect is always triggered by the active peer. */
	cancel_delayed_work_sync(&cp->cp_conn_w);
	rcu_पढ़ो_lock();
	अगर (!hlist_unhashed(&conn->c_hash_node)) अणु
		rcu_पढ़ो_unlock();
		rds_queue_reconnect(cp);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/* destroy a single rds_conn_path. rds_conn_destroy() iterates over
 * all paths using rds_conn_path_destroy()
 */
अटल व्योम rds_conn_path_destroy(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_message *rm, *rपंचांगp;

	अगर (!cp->cp_transport_data)
		वापस;

	/* make sure lingering queued work won't try to ref the conn */
	cancel_delayed_work_sync(&cp->cp_send_w);
	cancel_delayed_work_sync(&cp->cp_recv_w);

	rds_conn_path_drop(cp, true);
	flush_work(&cp->cp_करोwn_w);

	/* tear करोwn queued messages */
	list_क्रम_each_entry_safe(rm, rपंचांगp,
				 &cp->cp_send_queue,
				 m_conn_item) अणु
		list_del_init(&rm->m_conn_item);
		BUG_ON(!list_empty(&rm->m_sock_item));
		rds_message_put(rm);
	पूर्ण
	अगर (cp->cp_xmit_rm)
		rds_message_put(cp->cp_xmit_rm);

	WARN_ON(delayed_work_pending(&cp->cp_send_w));
	WARN_ON(delayed_work_pending(&cp->cp_recv_w));
	WARN_ON(delayed_work_pending(&cp->cp_conn_w));
	WARN_ON(work_pending(&cp->cp_करोwn_w));

	cp->cp_conn->c_trans->conn_मुक्त(cp->cp_transport_data);
पूर्ण

/*
 * Stop and मुक्त a connection.
 *
 * This can only be used in very limited circumstances.  It assumes that once
 * the conn has been shutकरोwn that no one अन्यथा is referencing the connection.
 * We can only ensure this in the rmmod path in the current code.
 */
व्योम rds_conn_destroy(काष्ठा rds_connection *conn)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	काष्ठा rds_conn_path *cp;
	पूर्णांक npaths = (conn->c_trans->t_mp_capable ? RDS_MPATH_WORKERS : 1);

	rdsdebug("freeing conn %p for %pI4 -> "
		 "%pI4\n", conn, &conn->c_laddr,
		 &conn->c_faddr);

	/* Ensure conn will not be scheduled क्रम reconnect */
	spin_lock_irq(&rds_conn_lock);
	hlist_del_init_rcu(&conn->c_hash_node);
	spin_unlock_irq(&rds_conn_lock);
	synchronize_rcu();

	/* shut the connection करोwn */
	क्रम (i = 0; i < npaths; i++) अणु
		cp = &conn->c_path[i];
		rds_conn_path_destroy(cp);
		BUG_ON(!list_empty(&cp->cp_retrans));
	पूर्ण

	/*
	 * The congestion maps aren't freed up here.  They're
	 * मुक्तd by rds_cong_निकास() after all the connections
	 * have been मुक्तd.
	 */
	rds_cong_हटाओ_conn(conn);

	kमुक्त(conn->c_path);
	kmem_cache_मुक्त(rds_conn_slab, conn);

	spin_lock_irqsave(&rds_conn_lock, flags);
	rds_conn_count--;
	spin_unlock_irqrestore(&rds_conn_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rds_conn_destroy);

अटल व्योम __rds_inc_msg_cp(काष्ठा rds_incoming *inc,
			     काष्ठा rds_info_iterator *iter,
			     व्योम *saddr, व्योम *daddr, पूर्णांक flip, bool isv6)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (isv6)
		rds6_inc_info_copy(inc, iter, saddr, daddr, flip);
	अन्यथा
#पूर्ण_अगर
		rds_inc_info_copy(inc, iter, *(__be32 *)saddr,
				  *(__be32 *)daddr, flip);
पूर्ण

अटल व्योम rds_conn_message_info_cmn(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
				      काष्ठा rds_info_iterator *iter,
				      काष्ठा rds_info_lengths *lens,
				      पूर्णांक want_send, bool isv6)
अणु
	काष्ठा hlist_head *head;
	काष्ठा list_head *list;
	काष्ठा rds_connection *conn;
	काष्ठा rds_message *rm;
	अचिन्हित पूर्णांक total = 0;
	अचिन्हित दीर्घ flags;
	माप_प्रकार i;
	पूर्णांक j;

	अगर (isv6)
		len /= माप(काष्ठा rds6_info_message);
	अन्यथा
		len /= माप(काष्ठा rds_info_message);

	rcu_पढ़ो_lock();

	क्रम (i = 0, head = rds_conn_hash; i < ARRAY_SIZE(rds_conn_hash);
	     i++, head++) अणु
		hlist_क्रम_each_entry_rcu(conn, head, c_hash_node) अणु
			काष्ठा rds_conn_path *cp;
			पूर्णांक npaths;

			अगर (!isv6 && conn->c_isv6)
				जारी;

			npaths = (conn->c_trans->t_mp_capable ?
				 RDS_MPATH_WORKERS : 1);

			क्रम (j = 0; j < npaths; j++) अणु
				cp = &conn->c_path[j];
				अगर (want_send)
					list = &cp->cp_send_queue;
				अन्यथा
					list = &cp->cp_retrans;

				spin_lock_irqsave(&cp->cp_lock, flags);

				/* XXX too lazy to मुख्यtain counts.. */
				list_क्रम_each_entry(rm, list, m_conn_item) अणु
					total++;
					अगर (total <= len)
						__rds_inc_msg_cp(&rm->m_inc,
								 iter,
								 &conn->c_laddr,
								 &conn->c_faddr,
								 0, isv6);
				पूर्ण

				spin_unlock_irqrestore(&cp->cp_lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	lens->nr = total;
	अगर (isv6)
		lens->each = माप(काष्ठा rds6_info_message);
	अन्यथा
		lens->each = माप(काष्ठा rds_info_message);
पूर्ण

अटल व्योम rds_conn_message_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
				  काष्ठा rds_info_iterator *iter,
				  काष्ठा rds_info_lengths *lens,
				  पूर्णांक want_send)
अणु
	rds_conn_message_info_cmn(sock, len, iter, lens, want_send, false);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम rds6_conn_message_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
				   काष्ठा rds_info_iterator *iter,
				   काष्ठा rds_info_lengths *lens,
				   पूर्णांक want_send)
अणु
	rds_conn_message_info_cmn(sock, len, iter, lens, want_send, true);
पूर्ण
#पूर्ण_अगर

अटल व्योम rds_conn_message_info_send(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
				       काष्ठा rds_info_iterator *iter,
				       काष्ठा rds_info_lengths *lens)
अणु
	rds_conn_message_info(sock, len, iter, lens, 1);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम rds6_conn_message_info_send(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
					काष्ठा rds_info_iterator *iter,
					काष्ठा rds_info_lengths *lens)
अणु
	rds6_conn_message_info(sock, len, iter, lens, 1);
पूर्ण
#पूर्ण_अगर

अटल व्योम rds_conn_message_info_retrans(काष्ठा socket *sock,
					  अचिन्हित पूर्णांक len,
					  काष्ठा rds_info_iterator *iter,
					  काष्ठा rds_info_lengths *lens)
अणु
	rds_conn_message_info(sock, len, iter, lens, 0);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम rds6_conn_message_info_retrans(काष्ठा socket *sock,
					   अचिन्हित पूर्णांक len,
					   काष्ठा rds_info_iterator *iter,
					   काष्ठा rds_info_lengths *lens)
अणु
	rds6_conn_message_info(sock, len, iter, lens, 0);
पूर्ण
#पूर्ण_अगर

व्योम rds_क्रम_each_conn_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			  काष्ठा rds_info_iterator *iter,
			  काष्ठा rds_info_lengths *lens,
			  पूर्णांक (*visitor)(काष्ठा rds_connection *, व्योम *),
			  u64 *buffer,
			  माप_प्रकार item_len)
अणु
	काष्ठा hlist_head *head;
	काष्ठा rds_connection *conn;
	माप_प्रकार i;

	rcu_पढ़ो_lock();

	lens->nr = 0;
	lens->each = item_len;

	क्रम (i = 0, head = rds_conn_hash; i < ARRAY_SIZE(rds_conn_hash);
	     i++, head++) अणु
		hlist_क्रम_each_entry_rcu(conn, head, c_hash_node) अणु

			/* XXX no c_lock usage.. */
			अगर (!visitor(conn, buffer))
				जारी;

			/* We copy as much as we can fit in the buffer,
			 * but we count all items so that the caller
			 * can resize the buffer. */
			अगर (len >= item_len) अणु
				rds_info_copy(iter, buffer, item_len);
				len -= item_len;
			पूर्ण
			lens->nr++;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rds_क्रम_each_conn_info);

अटल व्योम rds_walk_conn_path_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
				    काष्ठा rds_info_iterator *iter,
				    काष्ठा rds_info_lengths *lens,
				    पूर्णांक (*visitor)(काष्ठा rds_conn_path *, व्योम *),
				    u64 *buffer,
				    माप_प्रकार item_len)
अणु
	काष्ठा hlist_head *head;
	काष्ठा rds_connection *conn;
	माप_प्रकार i;

	rcu_पढ़ो_lock();

	lens->nr = 0;
	lens->each = item_len;

	क्रम (i = 0, head = rds_conn_hash; i < ARRAY_SIZE(rds_conn_hash);
	     i++, head++) अणु
		hlist_क्रम_each_entry_rcu(conn, head, c_hash_node) अणु
			काष्ठा rds_conn_path *cp;

			/* XXX We only copy the inक्रमmation from the first
			 * path क्रम now.  The problem is that अगर there are
			 * more than one underlying paths, we cannot report
			 * inक्रमmation of all of them using the existing
			 * API.  For example, there is only one next_tx_seq,
			 * which path's next_tx_seq should we report?  It is
			 * a bug in the design of MPRDS.
			 */
			cp = conn->c_path;

			/* XXX no cp_lock usage.. */
			अगर (!visitor(cp, buffer))
				जारी;

			/* We copy as much as we can fit in the buffer,
			 * but we count all items so that the caller
			 * can resize the buffer.
			 */
			अगर (len >= item_len) अणु
				rds_info_copy(iter, buffer, item_len);
				len -= item_len;
			पूर्ण
			lens->nr++;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक rds_conn_info_visitor(काष्ठा rds_conn_path *cp, व्योम *buffer)
अणु
	काष्ठा rds_info_connection *cinfo = buffer;
	काष्ठा rds_connection *conn = cp->cp_conn;

	अगर (conn->c_isv6)
		वापस 0;

	cinfo->next_tx_seq = cp->cp_next_tx_seq;
	cinfo->next_rx_seq = cp->cp_next_rx_seq;
	cinfo->laddr = conn->c_laddr.s6_addr32[3];
	cinfo->faddr = conn->c_faddr.s6_addr32[3];
	cinfo->tos = conn->c_tos;
	म_नकलन(cinfo->transport, conn->c_trans->t_name,
		माप(cinfo->transport));
	cinfo->flags = 0;

	rds_conn_info_set(cinfo->flags, test_bit(RDS_IN_XMIT, &cp->cp_flags),
			  SENDING);
	/* XXX Future: वापस the state rather than these funky bits */
	rds_conn_info_set(cinfo->flags,
			  atomic_पढ़ो(&cp->cp_state) == RDS_CONN_CONNECTING,
			  CONNECTING);
	rds_conn_info_set(cinfo->flags,
			  atomic_पढ़ो(&cp->cp_state) == RDS_CONN_UP,
			  CONNECTED);
	वापस 1;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक rds6_conn_info_visitor(काष्ठा rds_conn_path *cp, व्योम *buffer)
अणु
	काष्ठा rds6_info_connection *cinfo6 = buffer;
	काष्ठा rds_connection *conn = cp->cp_conn;

	cinfo6->next_tx_seq = cp->cp_next_tx_seq;
	cinfo6->next_rx_seq = cp->cp_next_rx_seq;
	cinfo6->laddr = conn->c_laddr;
	cinfo6->faddr = conn->c_faddr;
	म_नकलन(cinfo6->transport, conn->c_trans->t_name,
		माप(cinfo6->transport));
	cinfo6->flags = 0;

	rds_conn_info_set(cinfo6->flags, test_bit(RDS_IN_XMIT, &cp->cp_flags),
			  SENDING);
	/* XXX Future: वापस the state rather than these funky bits */
	rds_conn_info_set(cinfo6->flags,
			  atomic_पढ़ो(&cp->cp_state) == RDS_CONN_CONNECTING,
			  CONNECTING);
	rds_conn_info_set(cinfo6->flags,
			  atomic_पढ़ो(&cp->cp_state) == RDS_CONN_UP,
			  CONNECTED);
	/* Just वापस 1 as there is no error हाल. This is a helper function
	 * क्रम rds_walk_conn_path_info() and it wants a वापस value.
	 */
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल व्योम rds_conn_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			  काष्ठा rds_info_iterator *iter,
			  काष्ठा rds_info_lengths *lens)
अणु
	u64 buffer[(माप(काष्ठा rds_info_connection) + 7) / 8];

	rds_walk_conn_path_info(sock, len, iter, lens,
				rds_conn_info_visitor,
				buffer,
				माप(काष्ठा rds_info_connection));
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम rds6_conn_info(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			   काष्ठा rds_info_iterator *iter,
			   काष्ठा rds_info_lengths *lens)
अणु
	u64 buffer[(माप(काष्ठा rds6_info_connection) + 7) / 8];

	rds_walk_conn_path_info(sock, len, iter, lens,
				rds6_conn_info_visitor,
				buffer,
				माप(काष्ठा rds6_info_connection));
पूर्ण
#पूर्ण_अगर

पूर्णांक rds_conn_init(व्योम)
अणु
	पूर्णांक ret;

	ret = rds_loop_net_init(); /* रेजिस्टर pernet callback */
	अगर (ret)
		वापस ret;

	rds_conn_slab = kmem_cache_create("rds_connection",
					  माप(काष्ठा rds_connection),
					  0, 0, शून्य);
	अगर (!rds_conn_slab) अणु
		rds_loop_net_निकास();
		वापस -ENOMEM;
	पूर्ण

	rds_info_रेजिस्टर_func(RDS_INFO_CONNECTIONS, rds_conn_info);
	rds_info_रेजिस्टर_func(RDS_INFO_SEND_MESSAGES,
			       rds_conn_message_info_send);
	rds_info_रेजिस्टर_func(RDS_INFO_RETRANS_MESSAGES,
			       rds_conn_message_info_retrans);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_रेजिस्टर_func(RDS6_INFO_CONNECTIONS, rds6_conn_info);
	rds_info_रेजिस्टर_func(RDS6_INFO_SEND_MESSAGES,
			       rds6_conn_message_info_send);
	rds_info_रेजिस्टर_func(RDS6_INFO_RETRANS_MESSAGES,
			       rds6_conn_message_info_retrans);
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम rds_conn_निकास(व्योम)
अणु
	rds_loop_net_निकास(); /* unरेजिस्टर pernet callback */
	rds_loop_निकास();

	WARN_ON(!hlist_empty(rds_conn_hash));

	kmem_cache_destroy(rds_conn_slab);

	rds_info_deरेजिस्टर_func(RDS_INFO_CONNECTIONS, rds_conn_info);
	rds_info_deरेजिस्टर_func(RDS_INFO_SEND_MESSAGES,
				 rds_conn_message_info_send);
	rds_info_deरेजिस्टर_func(RDS_INFO_RETRANS_MESSAGES,
				 rds_conn_message_info_retrans);
#अगर IS_ENABLED(CONFIG_IPV6)
	rds_info_deरेजिस्टर_func(RDS6_INFO_CONNECTIONS, rds6_conn_info);
	rds_info_deरेजिस्टर_func(RDS6_INFO_SEND_MESSAGES,
				 rds6_conn_message_info_send);
	rds_info_deरेजिस्टर_func(RDS6_INFO_RETRANS_MESSAGES,
				 rds6_conn_message_info_retrans);
#पूर्ण_अगर
पूर्ण

/*
 * Force a disconnect
 */
व्योम rds_conn_path_drop(काष्ठा rds_conn_path *cp, bool destroy)
अणु
	atomic_set(&cp->cp_state, RDS_CONN_ERROR);

	rcu_पढ़ो_lock();
	अगर (!destroy && rds_destroy_pending(cp->cp_conn)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	queue_work(rds_wq, &cp->cp_करोwn_w);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rds_conn_path_drop);

व्योम rds_conn_drop(काष्ठा rds_connection *conn)
अणु
	WARN_ON(conn->c_trans->t_mp_capable);
	rds_conn_path_drop(&conn->c_path[0], false);
पूर्ण
EXPORT_SYMBOL_GPL(rds_conn_drop);

/*
 * If the connection is करोwn, trigger a connect. We may have scheduled a
 * delayed reconnect however - in this हाल we should not पूर्णांकerfere.
 */
व्योम rds_conn_path_connect_अगर_करोwn(काष्ठा rds_conn_path *cp)
अणु
	rcu_पढ़ो_lock();
	अगर (rds_destroy_pending(cp->cp_conn)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	अगर (rds_conn_path_state(cp) == RDS_CONN_DOWN &&
	    !test_and_set_bit(RDS_RECONNECT_PENDING, &cp->cp_flags))
		queue_delayed_work(rds_wq, &cp->cp_conn_w, 0);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rds_conn_path_connect_अगर_करोwn);

/* Check connectivity of all paths
 */
व्योम rds_check_all_paths(काष्ठा rds_connection *conn)
अणु
	पूर्णांक i = 0;

	करो अणु
		rds_conn_path_connect_अगर_करोwn(&conn->c_path[i]);
	पूर्ण जबतक (++i < conn->c_npaths);
पूर्ण

व्योम rds_conn_connect_अगर_करोwn(काष्ठा rds_connection *conn)
अणु
	WARN_ON(conn->c_trans->t_mp_capable);
	rds_conn_path_connect_अगर_करोwn(&conn->c_path[0]);
पूर्ण
EXPORT_SYMBOL_GPL(rds_conn_connect_अगर_करोwn);

व्योम
__rds_conn_path_error(काष्ठा rds_conn_path *cp, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	vprपूर्णांकk(fmt, ap);
	बहु_पूर्ण(ap);

	rds_conn_path_drop(cp, false);
पूर्ण
