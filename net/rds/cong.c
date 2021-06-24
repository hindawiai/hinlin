<शैली गुरु>
/*
 * Copyright (c) 2007, 2017 Oracle and/or its affiliates. All rights reserved.
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
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/bitops.h>
#समावेश <linux/export.h>

#समावेश "rds.h"

/*
 * This file implements the receive side of the unconventional congestion
 * management in RDS.
 *
 * Messages रुकोing in the receive queue on the receiving socket are accounted
 * against the sockets SO_RCVBUF option value.  Only the payload bytes in the
 * message are accounted क्रम.  If the number of bytes queued equals or exceeds
 * rcvbuf then the socket is congested.  All sends attempted to this socket's
 * address should वापस block or वापस -EWOULDBLOCK.
 *
 * Applications are expected to be reasonably tuned such that this situation
 * very rarely occurs.  An application encountering this "back-pressure" is
 * considered a bug.
 *
 * This is implemented by having each node मुख्यtain biपंचांगaps which indicate
 * which ports on bound addresses are congested.  As the biपंचांगap changes it is
 * sent through all the connections which terminate in the local address of the
 * biपंचांगap which changed.
 *
 * The biपंचांगaps are allocated as connections are brought up.  This aव्योमs
 * allocation in the पूर्णांकerrupt handling path which queues messages on sockets.
 * The dense biपंचांगaps let transports send the entire biपंचांगap on any biपंचांगap change
 * reasonably efficiently.  This is much easier to implement than some
 * finer-grained communication of per-port congestion.  The sender करोes a very
 * inexpensive bit test to test अगर the port it's about to send to is congested
 * or not.
 */

/*
 * Interaction with poll is a tad tricky. We want all processes stuck in
 * poll to wake up and check whether a congested destination became uncongested.
 * The really sad thing is we have no idea which destinations the application
 * wants to send to - we करोn't even know which rds_connections are involved.
 * So until we implement a more flexible rds poll पूर्णांकerface, we have to make
 * करो with this:
 * We मुख्यtain a global counter that is incremented each समय a congestion map
 * update is received. Each rds socket tracks this value, and अगर rds_poll
 * finds that the saved generation number is smaller than the global generation
 * number, it wakes up the process.
 */
अटल atomic_t		rds_cong_generation = ATOMIC_INIT(0);

/*
 * Congestion monitoring
 */
अटल LIST_HEAD(rds_cong_monitor);
अटल DEFINE_RWLOCK(rds_cong_monitor_lock);

/*
 * Yes, a global lock.  It's used so infrequently that it's worth keeping it
 * global to simplअगरy the locking.  It's only used in the following
 * circumstances:
 *
 *  - on connection buildup to associate a conn with its maps
 *  - on map changes to inक्रमm conns of a new map to send
 *
 *  It's sadly ordered under the socket callback lock and the connection lock.
 *  Receive paths can mark ports congested from पूर्णांकerrupt context so the
 *  lock masks पूर्णांकerrupts.
 */
अटल DEFINE_SPINLOCK(rds_cong_lock);
अटल काष्ठा rb_root rds_cong_tree = RB_ROOT;

अटल काष्ठा rds_cong_map *rds_cong_tree_walk(स्थिर काष्ठा in6_addr *addr,
					       काष्ठा rds_cong_map *insert)
अणु
	काष्ठा rb_node **p = &rds_cong_tree.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rds_cong_map *map;

	जबतक (*p) अणु
		पूर्णांक dअगरf;

		parent = *p;
		map = rb_entry(parent, काष्ठा rds_cong_map, m_rb_node);

		dअगरf = rds_addr_cmp(addr, &map->m_addr);
		अगर (dअगरf < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (dअगरf > 0)
			p = &(*p)->rb_right;
		अन्यथा
			वापस map;
	पूर्ण

	अगर (insert) अणु
		rb_link_node(&insert->m_rb_node, parent, p);
		rb_insert_color(&insert->m_rb_node, &rds_cong_tree);
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * There is only ever one biपंचांगap क्रम any address.  Connections try and allocate
 * these biपंचांगaps in the process getting poपूर्णांकers to them.  The biपंचांगaps are only
 * ever मुक्तd as the module is हटाओd after all connections have been मुक्तd.
 */
अटल काष्ठा rds_cong_map *rds_cong_from_addr(स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा rds_cong_map *map;
	काष्ठा rds_cong_map *ret = शून्य;
	अचिन्हित दीर्घ zp;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ flags;

	map = kzalloc(माप(काष्ठा rds_cong_map), GFP_KERNEL);
	अगर (!map)
		वापस शून्य;

	map->m_addr = *addr;
	init_रुकोqueue_head(&map->m_रुकोq);
	INIT_LIST_HEAD(&map->m_conn_list);

	क्रम (i = 0; i < RDS_CONG_MAP_PAGES; i++) अणु
		zp = get_zeroed_page(GFP_KERNEL);
		अगर (zp == 0)
			जाओ out;
		map->m_page_addrs[i] = zp;
	पूर्ण

	spin_lock_irqsave(&rds_cong_lock, flags);
	ret = rds_cong_tree_walk(addr, map);
	spin_unlock_irqrestore(&rds_cong_lock, flags);

	अगर (!ret) अणु
		ret = map;
		map = शून्य;
	पूर्ण

out:
	अगर (map) अणु
		क्रम (i = 0; i < RDS_CONG_MAP_PAGES && map->m_page_addrs[i]; i++)
			मुक्त_page(map->m_page_addrs[i]);
		kमुक्त(map);
	पूर्ण

	rdsdebug("map %p for addr %pI6c\n", ret, addr);

	वापस ret;
पूर्ण

/*
 * Put the conn on its local map's list.  This is called when the conn is
 * really added to the hash.  It's nested under the rds_conn_lock, sadly.
 */
व्योम rds_cong_add_conn(काष्ठा rds_connection *conn)
अणु
	अचिन्हित दीर्घ flags;

	rdsdebug("conn %p now on map %p\n", conn, conn->c_lcong);
	spin_lock_irqsave(&rds_cong_lock, flags);
	list_add_tail(&conn->c_map_item, &conn->c_lcong->m_conn_list);
	spin_unlock_irqrestore(&rds_cong_lock, flags);
पूर्ण

व्योम rds_cong_हटाओ_conn(काष्ठा rds_connection *conn)
अणु
	अचिन्हित दीर्घ flags;

	rdsdebug("removing conn %p from map %p\n", conn, conn->c_lcong);
	spin_lock_irqsave(&rds_cong_lock, flags);
	list_del_init(&conn->c_map_item);
	spin_unlock_irqrestore(&rds_cong_lock, flags);
पूर्ण

पूर्णांक rds_cong_get_maps(काष्ठा rds_connection *conn)
अणु
	conn->c_lcong = rds_cong_from_addr(&conn->c_laddr);
	conn->c_fcong = rds_cong_from_addr(&conn->c_faddr);

	अगर (!(conn->c_lcong && conn->c_fcong))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम rds_cong_queue_updates(काष्ठा rds_cong_map *map)
अणु
	काष्ठा rds_connection *conn;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rds_cong_lock, flags);

	list_क्रम_each_entry(conn, &map->m_conn_list, c_map_item) अणु
		काष्ठा rds_conn_path *cp = &conn->c_path[0];

		rcu_पढ़ो_lock();
		अगर (!test_and_set_bit(0, &conn->c_map_queued) &&
		    !rds_destroy_pending(cp->cp_conn)) अणु
			rds_stats_inc(s_cong_update_queued);
			/* We cannot अंतरभूत the call to rds_send_xmit() here
			 * क्रम two reasons (both pertaining to a TCP transport):
			 * 1. When we get here from the receive path, we
			 *    are alपढ़ोy holding the sock_lock (held by
			 *    tcp_v4_rcv()). So inlining calls to
			 *    tcp_setsockopt and/or tcp_sendmsg will deadlock
			 *    when it tries to get the sock_lock())
			 * 2. Interrupts are masked so that we can mark the
			 *    port congested from both send and recv paths.
			 *    (See comment around declaration of rdc_cong_lock).
			 *    An attempt to get the sock_lock() here will
			 *    thereक्रमe trigger warnings.
			 * Defer the xmit to rds_send_worker() instead.
			 */
			queue_delayed_work(rds_wq, &cp->cp_send_w, 0);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	spin_unlock_irqrestore(&rds_cong_lock, flags);
पूर्ण

व्योम rds_cong_map_updated(काष्ठा rds_cong_map *map, uपूर्णांक64_t porपंचांगask)
अणु
	rdsdebug("waking map %p for %pI4\n",
	  map, &map->m_addr);
	rds_stats_inc(s_cong_update_received);
	atomic_inc(&rds_cong_generation);
	अगर (रुकोqueue_active(&map->m_रुकोq))
		wake_up(&map->m_रुकोq);
	अगर (रुकोqueue_active(&rds_poll_रुकोq))
		wake_up_all(&rds_poll_रुकोq);

	अगर (porपंचांगask && !list_empty(&rds_cong_monitor)) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा rds_sock *rs;

		पढ़ो_lock_irqsave(&rds_cong_monitor_lock, flags);
		list_क्रम_each_entry(rs, &rds_cong_monitor, rs_cong_list) अणु
			spin_lock(&rs->rs_lock);
			rs->rs_cong_notअगरy |= (rs->rs_cong_mask & porपंचांगask);
			rs->rs_cong_mask &= ~porपंचांगask;
			spin_unlock(&rs->rs_lock);
			अगर (rs->rs_cong_notअगरy)
				rds_wake_sk_sleep(rs);
		पूर्ण
		पढ़ो_unlock_irqrestore(&rds_cong_monitor_lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rds_cong_map_updated);

पूर्णांक rds_cong_updated_since(अचिन्हित दीर्घ *recent)
अणु
	अचिन्हित दीर्घ gen = atomic_पढ़ो(&rds_cong_generation);

	अगर (likely(*recent == gen))
		वापस 0;
	*recent = gen;
	वापस 1;
पूर्ण

/*
 * We're called under the locking that protects the sockets receive buffer
 * consumption.  This makes it a lot easier क्रम the caller to only call us
 * when it knows that an existing set bit needs to be cleared, and vice versa.
 * We can't block and we need to deal with concurrent sockets working against
 * the same per-address map.
 */
व्योम rds_cong_set_bit(काष्ठा rds_cong_map *map, __be16 port)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ off;

	rdsdebug("setting congestion for %pI4:%u in map %p\n",
	  &map->m_addr, ntohs(port), map);

	i = be16_to_cpu(port) / RDS_CONG_MAP_PAGE_BITS;
	off = be16_to_cpu(port) % RDS_CONG_MAP_PAGE_BITS;

	set_bit_le(off, (व्योम *)map->m_page_addrs[i]);
पूर्ण

व्योम rds_cong_clear_bit(काष्ठा rds_cong_map *map, __be16 port)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ off;

	rdsdebug("clearing congestion for %pI4:%u in map %p\n",
	  &map->m_addr, ntohs(port), map);

	i = be16_to_cpu(port) / RDS_CONG_MAP_PAGE_BITS;
	off = be16_to_cpu(port) % RDS_CONG_MAP_PAGE_BITS;

	clear_bit_le(off, (व्योम *)map->m_page_addrs[i]);
पूर्ण

अटल पूर्णांक rds_cong_test_bit(काष्ठा rds_cong_map *map, __be16 port)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ off;

	i = be16_to_cpu(port) / RDS_CONG_MAP_PAGE_BITS;
	off = be16_to_cpu(port) % RDS_CONG_MAP_PAGE_BITS;

	वापस test_bit_le(off, (व्योम *)map->m_page_addrs[i]);
पूर्ण

व्योम rds_cong_add_socket(काष्ठा rds_sock *rs)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&rds_cong_monitor_lock, flags);
	अगर (list_empty(&rs->rs_cong_list))
		list_add(&rs->rs_cong_list, &rds_cong_monitor);
	ग_लिखो_unlock_irqrestore(&rds_cong_monitor_lock, flags);
पूर्ण

व्योम rds_cong_हटाओ_socket(काष्ठा rds_sock *rs)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rds_cong_map *map;

	ग_लिखो_lock_irqsave(&rds_cong_monitor_lock, flags);
	list_del_init(&rs->rs_cong_list);
	ग_लिखो_unlock_irqrestore(&rds_cong_monitor_lock, flags);

	/* update congestion map क्रम now-बंदd port */
	spin_lock_irqsave(&rds_cong_lock, flags);
	map = rds_cong_tree_walk(&rs->rs_bound_addr, शून्य);
	spin_unlock_irqrestore(&rds_cong_lock, flags);

	अगर (map && rds_cong_test_bit(map, rs->rs_bound_port)) अणु
		rds_cong_clear_bit(map, rs->rs_bound_port);
		rds_cong_queue_updates(map);
	पूर्ण
पूर्ण

पूर्णांक rds_cong_रुको(काष्ठा rds_cong_map *map, __be16 port, पूर्णांक nonblock,
		  काष्ठा rds_sock *rs)
अणु
	अगर (!rds_cong_test_bit(map, port))
		वापस 0;
	अगर (nonblock) अणु
		अगर (rs && rs->rs_cong_monitor) अणु
			अचिन्हित दीर्घ flags;

			/* It would have been nice to have an atomic set_bit on
			 * a uपूर्णांक64_t. */
			spin_lock_irqsave(&rs->rs_lock, flags);
			rs->rs_cong_mask |= RDS_CONG_MONITOR_MASK(ntohs(port));
			spin_unlock_irqrestore(&rs->rs_lock, flags);

			/* Test again - a congestion update may have arrived in
			 * the meanसमय. */
			अगर (!rds_cong_test_bit(map, port))
				वापस 0;
		पूर्ण
		rds_stats_inc(s_cong_send_error);
		वापस -ENOBUFS;
	पूर्ण

	rds_stats_inc(s_cong_send_blocked);
	rdsdebug("waiting on map %p for port %u\n", map, be16_to_cpu(port));

	वापस रुको_event_पूर्णांकerruptible(map->m_रुकोq,
					!rds_cong_test_bit(map, port));
पूर्ण

व्योम rds_cong_निकास(व्योम)
अणु
	काष्ठा rb_node *node;
	काष्ठा rds_cong_map *map;
	अचिन्हित दीर्घ i;

	जबतक ((node = rb_first(&rds_cong_tree))) अणु
		map = rb_entry(node, काष्ठा rds_cong_map, m_rb_node);
		rdsdebug("freeing map %p\n", map);
		rb_erase(&map->m_rb_node, &rds_cong_tree);
		क्रम (i = 0; i < RDS_CONG_MAP_PAGES && map->m_page_addrs[i]; i++)
			मुक्त_page(map->m_page_addrs[i]);
		kमुक्त(map);
	पूर्ण
पूर्ण

/*
 * Allocate a RDS message containing a congestion update.
 */
काष्ठा rds_message *rds_cong_update_alloc(काष्ठा rds_connection *conn)
अणु
	काष्ठा rds_cong_map *map = conn->c_lcong;
	काष्ठा rds_message *rm;

	rm = rds_message_map_pages(map->m_page_addrs, RDS_CONG_MAP_BYTES);
	अगर (!IS_ERR(rm))
		rm->m_inc.i_hdr.h_flags = RDS_FLAG_CONG_BITMAP;

	वापस rm;
पूर्ण
