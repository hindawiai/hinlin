<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 * Copyright (c) 2020, Linaro Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/qrtr.h>
#समावेश <linux/workqueue.h>
#समावेश <net/sock.h>

#समावेश "qrtr.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/qrtr.h>

अटल RADIX_TREE(nodes, GFP_KERNEL);

अटल काष्ठा अणु
	काष्ठा socket *sock;
	काष्ठा sockaddr_qrtr bcast_sq;
	काष्ठा list_head lookups;
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा work;
	पूर्णांक local_node;
पूर्ण qrtr_ns;

अटल स्थिर अक्षर * स्थिर qrtr_ctrl_pkt_strings[] = अणु
	[QRTR_TYPE_HELLO]	= "hello",
	[QRTR_TYPE_BYE]		= "bye",
	[QRTR_TYPE_NEW_SERVER]	= "new-server",
	[QRTR_TYPE_DEL_SERVER]	= "del-server",
	[QRTR_TYPE_DEL_CLIENT]	= "del-client",
	[QRTR_TYPE_RESUME_TX]	= "resume-tx",
	[QRTR_TYPE_EXIT]	= "exit",
	[QRTR_TYPE_PING]	= "ping",
	[QRTR_TYPE_NEW_LOOKUP]	= "new-lookup",
	[QRTR_TYPE_DEL_LOOKUP]	= "del-lookup",
पूर्ण;

काष्ठा qrtr_server_filter अणु
	अचिन्हित पूर्णांक service;
	अचिन्हित पूर्णांक instance;
	अचिन्हित पूर्णांक अगरilter;
पूर्ण;

काष्ठा qrtr_lookup अणु
	अचिन्हित पूर्णांक service;
	अचिन्हित पूर्णांक instance;

	काष्ठा sockaddr_qrtr sq;
	काष्ठा list_head li;
पूर्ण;

काष्ठा qrtr_server अणु
	अचिन्हित पूर्णांक service;
	अचिन्हित पूर्णांक instance;

	अचिन्हित पूर्णांक node;
	अचिन्हित पूर्णांक port;

	काष्ठा list_head qli;
पूर्ण;

काष्ठा qrtr_node अणु
	अचिन्हित पूर्णांक id;
	काष्ठा radix_tree_root servers;
पूर्ण;

अटल काष्ठा qrtr_node *node_get(अचिन्हित पूर्णांक node_id)
अणु
	काष्ठा qrtr_node *node;

	node = radix_tree_lookup(&nodes, node_id);
	अगर (node)
		वापस node;

	/* If node didn't exist, allocate and insert it to the tree */
	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस शून्य;

	node->id = node_id;

	radix_tree_insert(&nodes, node_id, node);

	वापस node;
पूर्ण

अटल पूर्णांक server_match(स्थिर काष्ठा qrtr_server *srv,
			स्थिर काष्ठा qrtr_server_filter *f)
अणु
	अचिन्हित पूर्णांक अगरilter = f->अगरilter;

	अगर (f->service != 0 && srv->service != f->service)
		वापस 0;
	अगर (!अगरilter && f->instance)
		अगरilter = ~0;

	वापस (srv->instance & अगरilter) == f->instance;
पूर्ण

अटल पूर्णांक service_announce_new(काष्ठा sockaddr_qrtr *dest,
				काष्ठा qrtr_server *srv)
अणु
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा kvec iv;

	trace_qrtr_ns_service_announce_new(srv->service, srv->instance,
					   srv->node, srv->port);

	iv.iov_base = &pkt;
	iv.iov_len = माप(pkt);

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_NEW_SERVER);
	pkt.server.service = cpu_to_le32(srv->service);
	pkt.server.instance = cpu_to_le32(srv->instance);
	pkt.server.node = cpu_to_le32(srv->node);
	pkt.server.port = cpu_to_le32(srv->port);

	msg.msg_name = (काष्ठा sockaddr *)dest;
	msg.msg_namelen = माप(*dest);

	वापस kernel_sendmsg(qrtr_ns.sock, &msg, &iv, 1, माप(pkt));
पूर्ण

अटल पूर्णांक service_announce_del(काष्ठा sockaddr_qrtr *dest,
				काष्ठा qrtr_server *srv)
अणु
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा kvec iv;
	पूर्णांक ret;

	trace_qrtr_ns_service_announce_del(srv->service, srv->instance,
					   srv->node, srv->port);

	iv.iov_base = &pkt;
	iv.iov_len = माप(pkt);

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_DEL_SERVER);
	pkt.server.service = cpu_to_le32(srv->service);
	pkt.server.instance = cpu_to_le32(srv->instance);
	pkt.server.node = cpu_to_le32(srv->node);
	pkt.server.port = cpu_to_le32(srv->port);

	msg.msg_name = (काष्ठा sockaddr *)dest;
	msg.msg_namelen = माप(*dest);

	ret = kernel_sendmsg(qrtr_ns.sock, &msg, &iv, 1, माप(pkt));
	अगर (ret < 0)
		pr_err("failed to announce del service\n");

	वापस ret;
पूर्ण

अटल व्योम lookup_notअगरy(काष्ठा sockaddr_qrtr *to, काष्ठा qrtr_server *srv,
			  bool new)
अणु
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा kvec iv;
	पूर्णांक ret;

	iv.iov_base = &pkt;
	iv.iov_len = माप(pkt);

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = new ? cpu_to_le32(QRTR_TYPE_NEW_SERVER) :
			cpu_to_le32(QRTR_TYPE_DEL_SERVER);
	अगर (srv) अणु
		pkt.server.service = cpu_to_le32(srv->service);
		pkt.server.instance = cpu_to_le32(srv->instance);
		pkt.server.node = cpu_to_le32(srv->node);
		pkt.server.port = cpu_to_le32(srv->port);
	पूर्ण

	msg.msg_name = (काष्ठा sockaddr *)to;
	msg.msg_namelen = माप(*to);

	ret = kernel_sendmsg(qrtr_ns.sock, &msg, &iv, 1, माप(pkt));
	अगर (ret < 0)
		pr_err("failed to send lookup notification\n");
पूर्ण

अटल पूर्णांक announce_servers(काष्ठा sockaddr_qrtr *sq)
अणु
	काष्ठा radix_tree_iter iter;
	काष्ठा qrtr_server *srv;
	काष्ठा qrtr_node *node;
	व्योम __rcu **slot;
	पूर्णांक ret;

	node = node_get(qrtr_ns.local_node);
	अगर (!node)
		वापस 0;

	rcu_पढ़ो_lock();
	/* Announce the list of servers रेजिस्टरed in this node */
	radix_tree_क्रम_each_slot(slot, &node->servers, &iter, 0) अणु
		srv = radix_tree_deref_slot(slot);
		अगर (!srv)
			जारी;
		अगर (radix_tree_deref_retry(srv)) अणु
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
		slot = radix_tree_iter_resume(slot, &iter);
		rcu_पढ़ो_unlock();

		ret = service_announce_new(sq, srv);
		अगर (ret < 0) अणु
			pr_err("failed to announce new service\n");
			वापस ret;
		पूर्ण

		rcu_पढ़ो_lock();
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल काष्ठा qrtr_server *server_add(अचिन्हित पूर्णांक service,
				      अचिन्हित पूर्णांक instance,
				      अचिन्हित पूर्णांक node_id,
				      अचिन्हित पूर्णांक port)
अणु
	काष्ठा qrtr_server *srv;
	काष्ठा qrtr_server *old;
	काष्ठा qrtr_node *node;

	अगर (!service || !port)
		वापस शून्य;

	srv = kzalloc(माप(*srv), GFP_KERNEL);
	अगर (!srv)
		वापस शून्य;

	srv->service = service;
	srv->instance = instance;
	srv->node = node_id;
	srv->port = port;

	node = node_get(node_id);
	अगर (!node)
		जाओ err;

	/* Delete the old server on the same port */
	old = radix_tree_lookup(&node->servers, port);
	अगर (old) अणु
		radix_tree_delete(&node->servers, port);
		kमुक्त(old);
	पूर्ण

	radix_tree_insert(&node->servers, port, srv);

	trace_qrtr_ns_server_add(srv->service, srv->instance,
				 srv->node, srv->port);

	वापस srv;

err:
	kमुक्त(srv);
	वापस शून्य;
पूर्ण

अटल पूर्णांक server_del(काष्ठा qrtr_node *node, अचिन्हित पूर्णांक port)
अणु
	काष्ठा qrtr_lookup *lookup;
	काष्ठा qrtr_server *srv;
	काष्ठा list_head *li;

	srv = radix_tree_lookup(&node->servers, port);
	अगर (!srv)
		वापस -ENOENT;

	radix_tree_delete(&node->servers, port);

	/* Broadcast the removal of local servers */
	अगर (srv->node == qrtr_ns.local_node)
		service_announce_del(&qrtr_ns.bcast_sq, srv);

	/* Announce the service's disappearance to observers */
	list_क्रम_each(li, &qrtr_ns.lookups) अणु
		lookup = container_of(li, काष्ठा qrtr_lookup, li);
		अगर (lookup->service && lookup->service != srv->service)
			जारी;
		अगर (lookup->instance && lookup->instance != srv->instance)
			जारी;

		lookup_notअगरy(&lookup->sq, srv, false);
	पूर्ण

	kमुक्त(srv);

	वापस 0;
पूर्ण

अटल पूर्णांक say_hello(काष्ठा sockaddr_qrtr *dest)
अणु
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा kvec iv;
	पूर्णांक ret;

	iv.iov_base = &pkt;
	iv.iov_len = माप(pkt);

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_HELLO);

	msg.msg_name = (काष्ठा sockaddr *)dest;
	msg.msg_namelen = माप(*dest);

	ret = kernel_sendmsg(qrtr_ns.sock, &msg, &iv, 1, माप(pkt));
	अगर (ret < 0)
		pr_err("failed to send hello msg\n");

	वापस ret;
पूर्ण

/* Announce the list of servers रेजिस्टरed on the local node */
अटल पूर्णांक ctrl_cmd_hello(काष्ठा sockaddr_qrtr *sq)
अणु
	पूर्णांक ret;

	ret = say_hello(sq);
	अगर (ret < 0)
		वापस ret;

	वापस announce_servers(sq);
पूर्ण

अटल पूर्णांक ctrl_cmd_bye(काष्ठा sockaddr_qrtr *from)
अणु
	काष्ठा qrtr_node *local_node;
	काष्ठा radix_tree_iter iter;
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा qrtr_server *srv;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा qrtr_node *node;
	व्योम __rcu **slot;
	काष्ठा kvec iv;
	पूर्णांक ret;

	iv.iov_base = &pkt;
	iv.iov_len = माप(pkt);

	node = node_get(from->sq_node);
	अगर (!node)
		वापस 0;

	rcu_पढ़ो_lock();
	/* Advertise removal of this client to all servers of remote node */
	radix_tree_क्रम_each_slot(slot, &node->servers, &iter, 0) अणु
		srv = radix_tree_deref_slot(slot);
		अगर (!srv)
			जारी;
		अगर (radix_tree_deref_retry(srv)) अणु
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
		slot = radix_tree_iter_resume(slot, &iter);
		rcu_पढ़ो_unlock();
		server_del(node, srv->port);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Advertise the removal of this client to all local servers */
	local_node = node_get(qrtr_ns.local_node);
	अगर (!local_node)
		वापस 0;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_BYE);
	pkt.client.node = cpu_to_le32(from->sq_node);

	rcu_पढ़ो_lock();
	radix_tree_क्रम_each_slot(slot, &local_node->servers, &iter, 0) अणु
		srv = radix_tree_deref_slot(slot);
		अगर (!srv)
			जारी;
		अगर (radix_tree_deref_retry(srv)) अणु
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
		slot = radix_tree_iter_resume(slot, &iter);
		rcu_पढ़ो_unlock();

		sq.sq_family = AF_QIPCRTR;
		sq.sq_node = srv->node;
		sq.sq_port = srv->port;

		msg.msg_name = (काष्ठा sockaddr *)&sq;
		msg.msg_namelen = माप(sq);

		ret = kernel_sendmsg(qrtr_ns.sock, &msg, &iv, 1, माप(pkt));
		अगर (ret < 0) अणु
			pr_err("failed to send bye cmd\n");
			वापस ret;
		पूर्ण
		rcu_पढ़ो_lock();
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cmd_del_client(काष्ठा sockaddr_qrtr *from,
			       अचिन्हित पूर्णांक node_id, अचिन्हित पूर्णांक port)
अणु
	काष्ठा qrtr_node *local_node;
	काष्ठा radix_tree_iter iter;
	काष्ठा qrtr_lookup *lookup;
	काष्ठा qrtr_ctrl_pkt pkt;
	काष्ठा msghdr msg = अणु पूर्ण;
	काष्ठा qrtr_server *srv;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा qrtr_node *node;
	काष्ठा list_head *पंचांगp;
	काष्ठा list_head *li;
	व्योम __rcu **slot;
	काष्ठा kvec iv;
	पूर्णांक ret;

	iv.iov_base = &pkt;
	iv.iov_len = माप(pkt);

	/* Don't accept spoofed messages */
	अगर (from->sq_node != node_id)
		वापस -EINVAL;

	/* Local DEL_CLIENT messages comes from the port being बंदd */
	अगर (from->sq_node == qrtr_ns.local_node && from->sq_port != port)
		वापस -EINVAL;

	/* Remove any lookups by this client */
	list_क्रम_each_safe(li, पंचांगp, &qrtr_ns.lookups) अणु
		lookup = container_of(li, काष्ठा qrtr_lookup, li);
		अगर (lookup->sq.sq_node != node_id)
			जारी;
		अगर (lookup->sq.sq_port != port)
			जारी;

		list_del(&lookup->li);
		kमुक्त(lookup);
	पूर्ण

	/* Remove the server beदीर्घing to this port */
	node = node_get(node_id);
	अगर (node)
		server_del(node, port);

	/* Advertise the removal of this client to all local servers */
	local_node = node_get(qrtr_ns.local_node);
	अगर (!local_node)
		वापस 0;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.cmd = cpu_to_le32(QRTR_TYPE_DEL_CLIENT);
	pkt.client.node = cpu_to_le32(node_id);
	pkt.client.port = cpu_to_le32(port);

	rcu_पढ़ो_lock();
	radix_tree_क्रम_each_slot(slot, &local_node->servers, &iter, 0) अणु
		srv = radix_tree_deref_slot(slot);
		अगर (!srv)
			जारी;
		अगर (radix_tree_deref_retry(srv)) अणु
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
		slot = radix_tree_iter_resume(slot, &iter);
		rcu_पढ़ो_unlock();

		sq.sq_family = AF_QIPCRTR;
		sq.sq_node = srv->node;
		sq.sq_port = srv->port;

		msg.msg_name = (काष्ठा sockaddr *)&sq;
		msg.msg_namelen = माप(sq);

		ret = kernel_sendmsg(qrtr_ns.sock, &msg, &iv, 1, माप(pkt));
		अगर (ret < 0) अणु
			pr_err("failed to send del client cmd\n");
			वापस ret;
		पूर्ण
		rcu_पढ़ो_lock();
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cmd_new_server(काष्ठा sockaddr_qrtr *from,
			       अचिन्हित पूर्णांक service, अचिन्हित पूर्णांक instance,
			       अचिन्हित पूर्णांक node_id, अचिन्हित पूर्णांक port)
अणु
	काष्ठा qrtr_lookup *lookup;
	काष्ठा qrtr_server *srv;
	काष्ठा list_head *li;
	पूर्णांक ret = 0;

	/* Ignore specअगरied node and port क्रम local servers */
	अगर (from->sq_node == qrtr_ns.local_node) अणु
		node_id = from->sq_node;
		port = from->sq_port;
	पूर्ण

	srv = server_add(service, instance, node_id, port);
	अगर (!srv)
		वापस -EINVAL;

	अगर (srv->node == qrtr_ns.local_node) अणु
		ret = service_announce_new(&qrtr_ns.bcast_sq, srv);
		अगर (ret < 0) अणु
			pr_err("failed to announce new service\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Notअगरy any potential lookups about the new server */
	list_क्रम_each(li, &qrtr_ns.lookups) अणु
		lookup = container_of(li, काष्ठा qrtr_lookup, li);
		अगर (lookup->service && lookup->service != service)
			जारी;
		अगर (lookup->instance && lookup->instance != instance)
			जारी;

		lookup_notअगरy(&lookup->sq, srv, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ctrl_cmd_del_server(काष्ठा sockaddr_qrtr *from,
			       अचिन्हित पूर्णांक service, अचिन्हित पूर्णांक instance,
			       अचिन्हित पूर्णांक node_id, अचिन्हित पूर्णांक port)
अणु
	काष्ठा qrtr_node *node;

	/* Ignore specअगरied node and port क्रम local servers*/
	अगर (from->sq_node == qrtr_ns.local_node) अणु
		node_id = from->sq_node;
		port = from->sq_port;
	पूर्ण

	/* Local servers may only unरेजिस्टर themselves */
	अगर (from->sq_node == qrtr_ns.local_node && from->sq_port != port)
		वापस -EINVAL;

	node = node_get(node_id);
	अगर (!node)
		वापस -ENOENT;

	वापस server_del(node, port);
पूर्ण

अटल पूर्णांक ctrl_cmd_new_lookup(काष्ठा sockaddr_qrtr *from,
			       अचिन्हित पूर्णांक service, अचिन्हित पूर्णांक instance)
अणु
	काष्ठा radix_tree_iter node_iter;
	काष्ठा qrtr_server_filter filter;
	काष्ठा radix_tree_iter srv_iter;
	काष्ठा qrtr_lookup *lookup;
	काष्ठा qrtr_node *node;
	व्योम __rcu **node_slot;
	व्योम __rcu **srv_slot;

	/* Accept only local observers */
	अगर (from->sq_node != qrtr_ns.local_node)
		वापस -EINVAL;

	lookup = kzalloc(माप(*lookup), GFP_KERNEL);
	अगर (!lookup)
		वापस -ENOMEM;

	lookup->sq = *from;
	lookup->service = service;
	lookup->instance = instance;
	list_add_tail(&lookup->li, &qrtr_ns.lookups);

	स_रखो(&filter, 0, माप(filter));
	filter.service = service;
	filter.instance = instance;

	rcu_पढ़ो_lock();
	radix_tree_क्रम_each_slot(node_slot, &nodes, &node_iter, 0) अणु
		node = radix_tree_deref_slot(node_slot);
		अगर (!node)
			जारी;
		अगर (radix_tree_deref_retry(node)) अणु
			node_slot = radix_tree_iter_retry(&node_iter);
			जारी;
		पूर्ण
		node_slot = radix_tree_iter_resume(node_slot, &node_iter);

		radix_tree_क्रम_each_slot(srv_slot, &node->servers,
					 &srv_iter, 0) अणु
			काष्ठा qrtr_server *srv;

			srv = radix_tree_deref_slot(srv_slot);
			अगर (!srv)
				जारी;
			अगर (radix_tree_deref_retry(srv)) अणु
				srv_slot = radix_tree_iter_retry(&srv_iter);
				जारी;
			पूर्ण

			अगर (!server_match(srv, &filter))
				जारी;

			srv_slot = radix_tree_iter_resume(srv_slot, &srv_iter);

			rcu_पढ़ो_unlock();
			lookup_notअगरy(from, srv, true);
			rcu_पढ़ो_lock();
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Empty notअगरication, to indicate end of listing */
	lookup_notअगरy(from, शून्य, true);

	वापस 0;
पूर्ण

अटल व्योम ctrl_cmd_del_lookup(काष्ठा sockaddr_qrtr *from,
				अचिन्हित पूर्णांक service, अचिन्हित पूर्णांक instance)
अणु
	काष्ठा qrtr_lookup *lookup;
	काष्ठा list_head *पंचांगp;
	काष्ठा list_head *li;

	list_क्रम_each_safe(li, पंचांगp, &qrtr_ns.lookups) अणु
		lookup = container_of(li, काष्ठा qrtr_lookup, li);
		अगर (lookup->sq.sq_node != from->sq_node)
			जारी;
		अगर (lookup->sq.sq_port != from->sq_port)
			जारी;
		अगर (lookup->service != service)
			जारी;
		अगर (lookup->instance && lookup->instance != instance)
			जारी;

		list_del(&lookup->li);
		kमुक्त(lookup);
	पूर्ण
पूर्ण

अटल व्योम qrtr_ns_worker(काष्ठा work_काष्ठा *work)
अणु
	स्थिर काष्ठा qrtr_ctrl_pkt *pkt;
	माप_प्रकार recv_buf_size = 4096;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा msghdr msg = अणु पूर्ण;
	अचिन्हित पूर्णांक cmd;
	sमाप_प्रकार msglen;
	व्योम *recv_buf;
	काष्ठा kvec iv;
	पूर्णांक ret;

	msg.msg_name = (काष्ठा sockaddr *)&sq;
	msg.msg_namelen = माप(sq);

	recv_buf = kzalloc(recv_buf_size, GFP_KERNEL);
	अगर (!recv_buf)
		वापस;

	क्रम (;;) अणु
		iv.iov_base = recv_buf;
		iv.iov_len = recv_buf_size;

		msglen = kernel_recvmsg(qrtr_ns.sock, &msg, &iv, 1,
					iv.iov_len, MSG_DONTWAIT);

		अगर (msglen == -EAGAIN)
			अवरोध;

		अगर (msglen < 0) अणु
			pr_err("error receiving packet: %zd\n", msglen);
			अवरोध;
		पूर्ण

		pkt = recv_buf;
		cmd = le32_to_cpu(pkt->cmd);
		अगर (cmd < ARRAY_SIZE(qrtr_ctrl_pkt_strings) &&
		    qrtr_ctrl_pkt_strings[cmd])
			trace_qrtr_ns_message(qrtr_ctrl_pkt_strings[cmd],
					      sq.sq_node, sq.sq_port);

		ret = 0;
		चयन (cmd) अणु
		हाल QRTR_TYPE_HELLO:
			ret = ctrl_cmd_hello(&sq);
			अवरोध;
		हाल QRTR_TYPE_BYE:
			ret = ctrl_cmd_bye(&sq);
			अवरोध;
		हाल QRTR_TYPE_DEL_CLIENT:
			ret = ctrl_cmd_del_client(&sq,
					le32_to_cpu(pkt->client.node),
					le32_to_cpu(pkt->client.port));
			अवरोध;
		हाल QRTR_TYPE_NEW_SERVER:
			ret = ctrl_cmd_new_server(&sq,
					le32_to_cpu(pkt->server.service),
					le32_to_cpu(pkt->server.instance),
					le32_to_cpu(pkt->server.node),
					le32_to_cpu(pkt->server.port));
			अवरोध;
		हाल QRTR_TYPE_DEL_SERVER:
			ret = ctrl_cmd_del_server(&sq,
					 le32_to_cpu(pkt->server.service),
					 le32_to_cpu(pkt->server.instance),
					 le32_to_cpu(pkt->server.node),
					 le32_to_cpu(pkt->server.port));
			अवरोध;
		हाल QRTR_TYPE_EXIT:
		हाल QRTR_TYPE_PING:
		हाल QRTR_TYPE_RESUME_TX:
			अवरोध;
		हाल QRTR_TYPE_NEW_LOOKUP:
			ret = ctrl_cmd_new_lookup(&sq,
					 le32_to_cpu(pkt->server.service),
					 le32_to_cpu(pkt->server.instance));
			अवरोध;
		हाल QRTR_TYPE_DEL_LOOKUP:
			ctrl_cmd_del_lookup(&sq,
				    le32_to_cpu(pkt->server.service),
				    le32_to_cpu(pkt->server.instance));
			अवरोध;
		पूर्ण

		अगर (ret < 0)
			pr_err("failed while handling packet from %d:%d",
			       sq.sq_node, sq.sq_port);
	पूर्ण

	kमुक्त(recv_buf);
पूर्ण

अटल व्योम qrtr_ns_data_पढ़ोy(काष्ठा sock *sk)
अणु
	queue_work(qrtr_ns.workqueue, &qrtr_ns.work);
पूर्ण

पूर्णांक qrtr_ns_init(व्योम)
अणु
	काष्ठा sockaddr_qrtr sq;
	पूर्णांक ret;

	INIT_LIST_HEAD(&qrtr_ns.lookups);
	INIT_WORK(&qrtr_ns.work, qrtr_ns_worker);

	ret = sock_create_kern(&init_net, AF_QIPCRTR, SOCK_DGRAM,
			       PF_QIPCRTR, &qrtr_ns.sock);
	अगर (ret < 0)
		वापस ret;

	ret = kernel_माला_लोockname(qrtr_ns.sock, (काष्ठा sockaddr *)&sq);
	अगर (ret < 0) अणु
		pr_err("failed to get socket name\n");
		जाओ err_sock;
	पूर्ण

	qrtr_ns.workqueue = alloc_workqueue("qrtr_ns_handler", WQ_UNBOUND, 1);
	अगर (!qrtr_ns.workqueue)
		जाओ err_sock;

	qrtr_ns.sock->sk->sk_data_पढ़ोy = qrtr_ns_data_पढ़ोy;

	sq.sq_port = QRTR_PORT_CTRL;
	qrtr_ns.local_node = sq.sq_node;

	ret = kernel_bind(qrtr_ns.sock, (काष्ठा sockaddr *)&sq, माप(sq));
	अगर (ret < 0) अणु
		pr_err("failed to bind to socket\n");
		जाओ err_wq;
	पूर्ण

	qrtr_ns.bcast_sq.sq_family = AF_QIPCRTR;
	qrtr_ns.bcast_sq.sq_node = QRTR_NODE_BCAST;
	qrtr_ns.bcast_sq.sq_port = QRTR_PORT_CTRL;

	ret = say_hello(&qrtr_ns.bcast_sq);
	अगर (ret < 0)
		जाओ err_wq;

	वापस 0;

err_wq:
	destroy_workqueue(qrtr_ns.workqueue);
err_sock:
	sock_release(qrtr_ns.sock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(qrtr_ns_init);

व्योम qrtr_ns_हटाओ(व्योम)
अणु
	cancel_work_sync(&qrtr_ns.work);
	destroy_workqueue(qrtr_ns.workqueue);
	sock_release(qrtr_ns.sock);
पूर्ण
EXPORT_SYMBOL_GPL(qrtr_ns_हटाओ);

MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Qualcomm IPC Router Nameservice");
MODULE_LICENSE("Dual BSD/GPL");
