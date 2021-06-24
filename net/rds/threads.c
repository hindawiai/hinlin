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
#समावेश <linux/अक्रमom.h>
#समावेश <linux/export.h>

#समावेश "rds.h"

/*
 * All of connection management is simplअगरied by serializing it through
 * work queues that execute in a connection managing thपढ़ो.
 *
 * TCP wants to send acks through sendpage() in response to data_पढ़ोy(),
 * but it needs a process context to करो so.
 *
 * The receive paths need to allocate but can't drop packets (!) so we have
 * a thपढ़ो around to block allocating अगर the receive fast path sees an
 * allocation failure.
 */

/* Gअक्रम Unअगरied Theory of connection lअगरe cycle:
 * At any poपूर्णांक in समय, the connection can be in one of these states:
 * DOWN, CONNECTING, UP, DISCONNECTING, ERROR
 *
 * The following transitions are possible:
 *  ANY		  -> ERROR
 *  UP		  -> DISCONNECTING
 *  ERROR	  -> DISCONNECTING
 *  DISCONNECTING -> DOWN
 *  DOWN	  -> CONNECTING
 *  CONNECTING	  -> UP
 *
 * Transition to state DISCONNECTING/DOWN:
 *  -	Inside the shutकरोwn worker; synchronizes with xmit path
 *	through RDS_IN_XMIT, and with connection management callbacks
 *	via c_cm_lock.
 *
 *	For receive callbacks, we rely on the underlying transport
 *	(TCP, IB/RDMA) to provide the necessary synchronisation.
 */
काष्ठा workqueue_काष्ठा *rds_wq;
EXPORT_SYMBOL_GPL(rds_wq);

व्योम rds_connect_path_complete(काष्ठा rds_conn_path *cp, पूर्णांक curr)
अणु
	अगर (!rds_conn_path_transition(cp, curr, RDS_CONN_UP)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Cannot transition to state UP, "
				"current state is %d\n",
				__func__,
				atomic_पढ़ो(&cp->cp_state));
		rds_conn_path_drop(cp, false);
		वापस;
	पूर्ण

	rdsdebug("conn %p for %pI6c to %pI6c complete\n",
		 cp->cp_conn, &cp->cp_conn->c_laddr, &cp->cp_conn->c_faddr);

	cp->cp_reconnect_jअगरfies = 0;
	set_bit(0, &cp->cp_conn->c_map_queued);
	rcu_पढ़ो_lock();
	अगर (!rds_destroy_pending(cp->cp_conn)) अणु
		queue_delayed_work(rds_wq, &cp->cp_send_w, 0);
		queue_delayed_work(rds_wq, &cp->cp_recv_w, 0);
	पूर्ण
	rcu_पढ़ो_unlock();
	cp->cp_conn->c_proposed_version = RDS_PROTOCOL_VERSION;
पूर्ण
EXPORT_SYMBOL_GPL(rds_connect_path_complete);

व्योम rds_connect_complete(काष्ठा rds_connection *conn)
अणु
	rds_connect_path_complete(&conn->c_path[0], RDS_CONN_CONNECTING);
पूर्ण
EXPORT_SYMBOL_GPL(rds_connect_complete);

/*
 * This अक्रमom exponential backoff is relied on to eventually resolve racing
 * connects.
 *
 * If connect attempts race then both parties drop both connections and come
 * here to रुको क्रम a अक्रमom amount of समय beक्रमe trying again.  Eventually
 * the backoff range will be so much greater than the समय it takes to
 * establish a connection that one of the pair will establish the connection
 * beक्रमe the other's अक्रमom delay fires.
 *
 * Connection attempts that arrive जबतक a connection is alपढ़ोy established
 * are also considered to be racing connects.  This lets a connection from
 * a rebooted machine replace an existing stale connection beक्रमe the transport
 * notices that the connection has failed.
 *
 * We should *always* start with a अक्रमom backoff; otherwise a broken connection
 * will always take several iterations to be re-established.
 */
व्योम rds_queue_reconnect(काष्ठा rds_conn_path *cp)
अणु
	अचिन्हित दीर्घ अक्रम;
	काष्ठा rds_connection *conn = cp->cp_conn;

	rdsdebug("conn %p for %pI6c to %pI6c reconnect jiffies %lu\n",
		 conn, &conn->c_laddr, &conn->c_faddr,
		 cp->cp_reconnect_jअगरfies);

	/* let peer with smaller addr initiate reconnect, to aव्योम duels */
	अगर (conn->c_trans->t_type == RDS_TRANS_TCP &&
	    rds_addr_cmp(&conn->c_laddr, &conn->c_faddr) >= 0)
		वापस;

	set_bit(RDS_RECONNECT_PENDING, &cp->cp_flags);
	अगर (cp->cp_reconnect_jअगरfies == 0) अणु
		cp->cp_reconnect_jअगरfies = rds_sysctl_reconnect_min_jअगरfies;
		rcu_पढ़ो_lock();
		अगर (!rds_destroy_pending(cp->cp_conn))
			queue_delayed_work(rds_wq, &cp->cp_conn_w, 0);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	get_अक्रमom_bytes(&अक्रम, माप(अक्रम));
	rdsdebug("%lu delay %lu ceil conn %p for %pI6c -> %pI6c\n",
		 अक्रम % cp->cp_reconnect_jअगरfies, cp->cp_reconnect_jअगरfies,
		 conn, &conn->c_laddr, &conn->c_faddr);
	rcu_पढ़ो_lock();
	अगर (!rds_destroy_pending(cp->cp_conn))
		queue_delayed_work(rds_wq, &cp->cp_conn_w,
				   अक्रम % cp->cp_reconnect_jअगरfies);
	rcu_पढ़ो_unlock();

	cp->cp_reconnect_jअगरfies = min(cp->cp_reconnect_jअगरfies * 2,
					rds_sysctl_reconnect_max_jअगरfies);
पूर्ण

व्योम rds_connect_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rds_conn_path *cp = container_of(work,
						काष्ठा rds_conn_path,
						cp_conn_w.work);
	काष्ठा rds_connection *conn = cp->cp_conn;
	पूर्णांक ret;

	अगर (cp->cp_index > 0 &&
	    rds_addr_cmp(&cp->cp_conn->c_laddr, &cp->cp_conn->c_faddr) >= 0)
		वापस;
	clear_bit(RDS_RECONNECT_PENDING, &cp->cp_flags);
	ret = rds_conn_path_transition(cp, RDS_CONN_DOWN, RDS_CONN_CONNECTING);
	अगर (ret) अणु
		ret = conn->c_trans->conn_path_connect(cp);
		rdsdebug("conn %p for %pI6c to %pI6c dispatched, ret %d\n",
			 conn, &conn->c_laddr, &conn->c_faddr, ret);

		अगर (ret) अणु
			अगर (rds_conn_path_transition(cp,
						     RDS_CONN_CONNECTING,
						     RDS_CONN_DOWN))
				rds_queue_reconnect(cp);
			अन्यथा
				rds_conn_path_error(cp, "connect failed\n");
		पूर्ण
	पूर्ण
पूर्ण

व्योम rds_send_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rds_conn_path *cp = container_of(work,
						काष्ठा rds_conn_path,
						cp_send_w.work);
	पूर्णांक ret;

	अगर (rds_conn_path_state(cp) == RDS_CONN_UP) अणु
		clear_bit(RDS_LL_SEND_FULL, &cp->cp_flags);
		ret = rds_send_xmit(cp);
		cond_resched();
		rdsdebug("conn %p ret %d\n", cp->cp_conn, ret);
		चयन (ret) अणु
		हाल -EAGAIN:
			rds_stats_inc(s_send_immediate_retry);
			queue_delayed_work(rds_wq, &cp->cp_send_w, 0);
			अवरोध;
		हाल -ENOMEM:
			rds_stats_inc(s_send_delayed_retry);
			queue_delayed_work(rds_wq, &cp->cp_send_w, 2);
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rds_recv_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rds_conn_path *cp = container_of(work,
						काष्ठा rds_conn_path,
						cp_recv_w.work);
	पूर्णांक ret;

	अगर (rds_conn_path_state(cp) == RDS_CONN_UP) अणु
		ret = cp->cp_conn->c_trans->recv_path(cp);
		rdsdebug("conn %p ret %d\n", cp->cp_conn, ret);
		चयन (ret) अणु
		हाल -EAGAIN:
			rds_stats_inc(s_recv_immediate_retry);
			queue_delayed_work(rds_wq, &cp->cp_recv_w, 0);
			अवरोध;
		हाल -ENOMEM:
			rds_stats_inc(s_recv_delayed_retry);
			queue_delayed_work(rds_wq, &cp->cp_recv_w, 2);
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rds_shutकरोwn_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rds_conn_path *cp = container_of(work,
						काष्ठा rds_conn_path,
						cp_करोwn_w);

	rds_conn_shutकरोwn(cp);
पूर्ण

व्योम rds_thपढ़ोs_निकास(व्योम)
अणु
	destroy_workqueue(rds_wq);
पूर्ण

पूर्णांक rds_thपढ़ोs_init(व्योम)
अणु
	rds_wq = create_singlethपढ़ो_workqueue("krdsd");
	अगर (!rds_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Compare two IPv6 addresses.  Return 0 अगर the two addresses are equal.
 * Return 1 अगर the first is greater.  Return -1 अगर the second is greater.
 */
पूर्णांक rds_addr_cmp(स्थिर काष्ठा in6_addr *addr1,
		 स्थिर काष्ठा in6_addr *addr2)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर __be64 *a1, *a2;
	u64 x, y;

	a1 = (__be64 *)addr1;
	a2 = (__be64 *)addr2;

	अगर (*a1 != *a2) अणु
		अगर (be64_to_cpu(*a1) < be64_to_cpu(*a2))
			वापस -1;
		अन्यथा
			वापस 1;
	पूर्ण अन्यथा अणु
		x = be64_to_cpu(*++a1);
		y = be64_to_cpu(*++a2);
		अगर (x < y)
			वापस -1;
		अन्यथा अगर (x > y)
			वापस 1;
		अन्यथा
			वापस 0;
	पूर्ण
#अन्यथा
	u32 a, b;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (addr1->s6_addr32[i] != addr2->s6_addr32[i]) अणु
			a = ntohl(addr1->s6_addr32[i]);
			b = ntohl(addr2->s6_addr32[i]);
			अगर (a < b)
				वापस -1;
			अन्यथा अगर (a > b)
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(rds_addr_cmp);
