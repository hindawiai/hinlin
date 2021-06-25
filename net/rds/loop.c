<शैली गुरु>
/*
 * Copyright (c) 2006, 2017 Oracle and/or its affiliates. All rights reserved.
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
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/ipv6.h>

#समावेश "rds_single_path.h"
#समावेश "rds.h"
#समावेश "loop.h"

अटल DEFINE_SPINLOCK(loop_conns_lock);
अटल LIST_HEAD(loop_conns);
अटल atomic_t rds_loop_unloading = ATOMIC_INIT(0);

अटल व्योम rds_loop_set_unloading(व्योम)
अणु
	atomic_set(&rds_loop_unloading, 1);
पूर्ण

अटल bool rds_loop_is_unloading(काष्ठा rds_connection *conn)
अणु
	वापस atomic_पढ़ो(&rds_loop_unloading) != 0;
पूर्ण

/*
 * This 'loopback' transport is a special हाल क्रम flows that originate
 * and terminate on the same machine.
 *
 * Connection build-up notices अगर the destination address is thought of
 * as a local address by a transport.  At that समय it decides to use the
 * loopback transport instead of the bound transport of the sending socket.
 *
 * The loopback transport's sending path just hands the sent rds_message
 * straight to the receiving path via an embedded rds_incoming.
 */

/*
 * Usually a message transits both the sender and receiver's conns as it
 * flows to the receiver.  In the loopback हाल, though, the receive path
 * is handed the sending conn so the sense of the addresses is reversed.
 */
अटल पूर्णांक rds_loop_xmit(काष्ठा rds_connection *conn, काष्ठा rds_message *rm,
			 अचिन्हित पूर्णांक hdr_off, अचिन्हित पूर्णांक sg,
			 अचिन्हित पूर्णांक off)
अणु
	काष्ठा scatterlist *sgp = &rm->data.op_sg[sg];
	पूर्णांक ret = माप(काष्ठा rds_header) +
			be32_to_cpu(rm->m_inc.i_hdr.h_len);

	/* Do not send cong updates to loopback */
	अगर (rm->m_inc.i_hdr.h_flags & RDS_FLAG_CONG_BITMAP) अणु
		rds_cong_map_updated(conn->c_fcong, ~(u64) 0);
		ret = min_t(पूर्णांक, ret, sgp->length - conn->c_xmit_data_off);
		जाओ out;
	पूर्ण

	BUG_ON(hdr_off || sg || off);

	rds_inc_init(&rm->m_inc, conn, &conn->c_laddr);
	/* For the embedded inc. Matching put is in loop_inc_मुक्त() */
	rds_message_addref(rm);

	rds_recv_incoming(conn, &conn->c_laddr, &conn->c_faddr, &rm->m_inc,
			  GFP_KERNEL);

	rds_send_drop_acked(conn, be64_to_cpu(rm->m_inc.i_hdr.h_sequence),
			    शून्य);

	rds_inc_put(&rm->m_inc);
out:
	वापस ret;
पूर्ण

/*
 * See rds_loop_xmit(). Since our inc is embedded in the rm, we
 * make sure the rm lives at least until the inc is करोne.
 */
अटल व्योम rds_loop_inc_मुक्त(काष्ठा rds_incoming *inc)
अणु
	काष्ठा rds_message *rm = container_of(inc, काष्ठा rds_message, m_inc);

	rds_message_put(rm);
पूर्ण

/* we need to at least give the thपढ़ो something to succeed */
अटल पूर्णांक rds_loop_recv_path(काष्ठा rds_conn_path *cp)
अणु
	वापस 0;
पूर्ण

काष्ठा rds_loop_connection अणु
	काष्ठा list_head loop_node;
	काष्ठा rds_connection *conn;
पूर्ण;

/*
 * Even the loopback transport needs to keep track of its connections,
 * so it can call rds_conn_destroy() on them on निकास. N.B. there are
 * 1+ loopback addresses (127.*.*.*) so it's not a bug to have
 * multiple loopback conns allocated, although rather useless.
 */
अटल पूर्णांक rds_loop_conn_alloc(काष्ठा rds_connection *conn, gfp_t gfp)
अणु
	काष्ठा rds_loop_connection *lc;
	अचिन्हित दीर्घ flags;

	lc = kzalloc(माप(काष्ठा rds_loop_connection), gfp);
	अगर (!lc)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&lc->loop_node);
	lc->conn = conn;
	conn->c_transport_data = lc;

	spin_lock_irqsave(&loop_conns_lock, flags);
	list_add_tail(&lc->loop_node, &loop_conns);
	spin_unlock_irqrestore(&loop_conns_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम rds_loop_conn_मुक्त(व्योम *arg)
अणु
	काष्ठा rds_loop_connection *lc = arg;
	अचिन्हित दीर्घ flags;

	rdsdebug("lc %p\n", lc);
	spin_lock_irqsave(&loop_conns_lock, flags);
	list_del(&lc->loop_node);
	spin_unlock_irqrestore(&loop_conns_lock, flags);
	kमुक्त(lc);
पूर्ण

अटल पूर्णांक rds_loop_conn_path_connect(काष्ठा rds_conn_path *cp)
अणु
	rds_connect_complete(cp->cp_conn);
	वापस 0;
पूर्ण

अटल व्योम rds_loop_conn_path_shutकरोwn(काष्ठा rds_conn_path *cp)
अणु
पूर्ण

व्योम rds_loop_निकास(व्योम)
अणु
	काष्ठा rds_loop_connection *lc, *_lc;
	LIST_HEAD(पंचांगp_list);

	rds_loop_set_unloading();
	synchronize_rcu();
	/* aव्योम calling conn_destroy with irqs off */
	spin_lock_irq(&loop_conns_lock);
	list_splice(&loop_conns, &पंचांगp_list);
	INIT_LIST_HEAD(&loop_conns);
	spin_unlock_irq(&loop_conns_lock);

	list_क्रम_each_entry_safe(lc, _lc, &पंचांगp_list, loop_node) अणु
		WARN_ON(lc->conn->c_passive);
		rds_conn_destroy(lc->conn);
	पूर्ण
पूर्ण

अटल व्योम rds_loop_समाप्त_conns(काष्ठा net *net)
अणु
	काष्ठा rds_loop_connection *lc, *_lc;
	LIST_HEAD(पंचांगp_list);

	spin_lock_irq(&loop_conns_lock);
	list_क्रम_each_entry_safe(lc, _lc, &loop_conns, loop_node)  अणु
		काष्ठा net *c_net = पढ़ो_pnet(&lc->conn->c_net);

		अगर (net != c_net)
			जारी;
		list_move_tail(&lc->loop_node, &पंचांगp_list);
	पूर्ण
	spin_unlock_irq(&loop_conns_lock);

	list_क्रम_each_entry_safe(lc, _lc, &पंचांगp_list, loop_node) अणु
		WARN_ON(lc->conn->c_passive);
		rds_conn_destroy(lc->conn);
	पूर्ण
पूर्ण

अटल व्योम __net_निकास rds_loop_निकास_net(काष्ठा net *net)
अणु
	rds_loop_समाप्त_conns(net);
पूर्ण

अटल काष्ठा pernet_operations rds_loop_net_ops = अणु
	.निकास = rds_loop_निकास_net,
पूर्ण;

पूर्णांक rds_loop_net_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_device(&rds_loop_net_ops);
पूर्ण

व्योम rds_loop_net_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_device(&rds_loop_net_ops);
पूर्ण

/*
 * This is missing .xmit_* because loop करोesn't go through generic
 * rds_send_xmit() and करोesn't call rds_recv_incoming().  .listen_stop and
 * .laddr_check are missing because transport.c करोesn't iterate over
 * rds_loop_transport.
 */
काष्ठा rds_transport rds_loop_transport = अणु
	.xmit			= rds_loop_xmit,
	.recv_path		= rds_loop_recv_path,
	.conn_alloc		= rds_loop_conn_alloc,
	.conn_मुक्त		= rds_loop_conn_मुक्त,
	.conn_path_connect	= rds_loop_conn_path_connect,
	.conn_path_shutकरोwn	= rds_loop_conn_path_shutकरोwn,
	.inc_copy_to_user	= rds_message_inc_copy_to_user,
	.inc_मुक्त		= rds_loop_inc_मुक्त,
	.t_name			= "loopback",
	.t_type			= RDS_TRANS_LOOP,
	.t_unloading		= rds_loop_is_unloading,
पूर्ण;
