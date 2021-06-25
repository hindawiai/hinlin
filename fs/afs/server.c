<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS server record management
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश "afs_fs.h"
#समावेश "internal.h"
#समावेश "protocol_yfs.h"

अटल अचिन्हित afs_server_gc_delay = 10;	/* Server record समयout in seconds */
अटल atomic_t afs_server_debug_id;

अटल काष्ठा afs_server *afs_maybe_use_server(काष्ठा afs_server *,
					       क्रमागत afs_server_trace);
अटल व्योम __afs_put_server(काष्ठा afs_net *, काष्ठा afs_server *);

/*
 * Find a server by one of its addresses.
 */
काष्ठा afs_server *afs_find_server(काष्ठा afs_net *net,
				   स्थिर काष्ठा sockaddr_rxrpc *srx)
अणु
	स्थिर काष्ठा afs_addr_list *alist;
	काष्ठा afs_server *server = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक seq = 0, dअगरf;

	rcu_पढ़ो_lock();

	करो अणु
		अगर (server)
			afs_unuse_server_noसमय(net, server, afs_server_trace_put_find_rsq);
		server = शून्य;
		पढ़ो_seqbegin_or_lock(&net->fs_addr_lock, &seq);

		अगर (srx->transport.family == AF_INET6) अणु
			स्थिर काष्ठा sockaddr_in6 *a = &srx->transport.sin6, *b;
			hlist_क्रम_each_entry_rcu(server, &net->fs_addresses6, addr6_link) अणु
				alist = rcu_dereference(server->addresses);
				क्रम (i = alist->nr_ipv4; i < alist->nr_addrs; i++) अणु
					b = &alist->addrs[i].transport.sin6;
					dअगरf = ((u16 __क्रमce)a->sin6_port -
						(u16 __क्रमce)b->sin6_port);
					अगर (dअगरf == 0)
						dअगरf = स_भेद(&a->sin6_addr,
							      &b->sin6_addr,
							      माप(काष्ठा in6_addr));
					अगर (dअगरf == 0)
						जाओ found;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा sockaddr_in *a = &srx->transport.sin, *b;
			hlist_क्रम_each_entry_rcu(server, &net->fs_addresses4, addr4_link) अणु
				alist = rcu_dereference(server->addresses);
				क्रम (i = 0; i < alist->nr_ipv4; i++) अणु
					b = &alist->addrs[i].transport.sin;
					dअगरf = ((u16 __क्रमce)a->sin_port -
						(u16 __क्रमce)b->sin_port);
					अगर (dअगरf == 0)
						dअगरf = ((u32 __क्रमce)a->sin_addr.s_addr -
							(u32 __क्रमce)b->sin_addr.s_addr);
					अगर (dअगरf == 0)
						जाओ found;
				पूर्ण
			पूर्ण
		पूर्ण

		server = शून्य;
		जारी;
	found:
		server = afs_maybe_use_server(server, afs_server_trace_get_by_addr);

	पूर्ण जबतक (need_seqretry(&net->fs_addr_lock, seq));

	करोne_seqretry(&net->fs_addr_lock, seq);

	rcu_पढ़ो_unlock();
	वापस server;
पूर्ण

/*
 * Look up a server by its UUID and mark it active.
 */
काष्ठा afs_server *afs_find_server_by_uuid(काष्ठा afs_net *net, स्थिर uuid_t *uuid)
अणु
	काष्ठा afs_server *server = शून्य;
	काष्ठा rb_node *p;
	पूर्णांक dअगरf, seq = 0;

	_enter("%pU", uuid);

	करो अणु
		/* Unक्रमtunately, rbtree walking करोesn't give reliable results
		 * under just the RCU पढ़ो lock, so we have to check क्रम
		 * changes.
		 */
		अगर (server)
			afs_unuse_server(net, server, afs_server_trace_put_uuid_rsq);
		server = शून्य;

		पढ़ो_seqbegin_or_lock(&net->fs_lock, &seq);

		p = net->fs_servers.rb_node;
		जबतक (p) अणु
			server = rb_entry(p, काष्ठा afs_server, uuid_rb);

			dअगरf = स_भेद(uuid, &server->uuid, माप(*uuid));
			अगर (dअगरf < 0) अणु
				p = p->rb_left;
			पूर्ण अन्यथा अगर (dअगरf > 0) अणु
				p = p->rb_right;
			पूर्ण अन्यथा अणु
				afs_use_server(server, afs_server_trace_get_by_uuid);
				अवरोध;
			पूर्ण

			server = शून्य;
		पूर्ण
	पूर्ण जबतक (need_seqretry(&net->fs_lock, seq));

	करोne_seqretry(&net->fs_lock, seq);

	_leave(" = %p", server);
	वापस server;
पूर्ण

/*
 * Install a server record in the namespace tree.  If there's a clash, we stick
 * it पूर्णांकo a list anchored on whichever afs_server काष्ठा is actually in the
 * tree.
 */
अटल काष्ठा afs_server *afs_install_server(काष्ठा afs_cell *cell,
					     काष्ठा afs_server *candidate)
अणु
	स्थिर काष्ठा afs_addr_list *alist;
	काष्ठा afs_server *server, *next;
	काष्ठा afs_net *net = cell->net;
	काष्ठा rb_node **pp, *p;
	पूर्णांक dअगरf;

	_enter("%p", candidate);

	ग_लिखो_seqlock(&net->fs_lock);

	/* Firstly install the server in the UUID lookup tree */
	pp = &net->fs_servers.rb_node;
	p = शून्य;
	जबतक (*pp) अणु
		p = *pp;
		_debug("- consider %p", p);
		server = rb_entry(p, काष्ठा afs_server, uuid_rb);
		dअगरf = स_भेद(&candidate->uuid, &server->uuid, माप(uuid_t));
		अगर (dअगरf < 0) अणु
			pp = &(*pp)->rb_left;
		पूर्ण अन्यथा अगर (dअगरf > 0) अणु
			pp = &(*pp)->rb_right;
		पूर्ण अन्यथा अणु
			अगर (server->cell == cell)
				जाओ exists;

			/* We have the same UUID representing servers in
			 * dअगरferent cells.  Append the new server to the list.
			 */
			क्रम (;;) अणु
				next = rcu_dereference_रक्षित(
					server->uuid_next,
					lockdep_is_held(&net->fs_lock.lock));
				अगर (!next)
					अवरोध;
				server = next;
			पूर्ण
			rcu_assign_poपूर्णांकer(server->uuid_next, candidate);
			candidate->uuid_prev = server;
			server = candidate;
			जाओ added_dup;
		पूर्ण
	पूर्ण

	server = candidate;
	rb_link_node(&server->uuid_rb, p, pp);
	rb_insert_color(&server->uuid_rb, &net->fs_servers);
	hlist_add_head_rcu(&server->proc_link, &net->fs_proc);

added_dup:
	ग_लिखो_seqlock(&net->fs_addr_lock);
	alist = rcu_dereference_रक्षित(server->addresses,
					  lockdep_is_held(&net->fs_addr_lock.lock));

	/* Secondly, अगर the server has any IPv4 and/or IPv6 addresses, install
	 * it in the IPv4 and/or IPv6 reverse-map lists.
	 *
	 * TODO: For speed we want to use something other than a flat list
	 * here; even sorting the list in terms of lowest address would help a
	 * bit, but anything we might want to करो माला_लो messy and memory
	 * पूर्णांकensive.
	 */
	अगर (alist->nr_ipv4 > 0)
		hlist_add_head_rcu(&server->addr4_link, &net->fs_addresses4);
	अगर (alist->nr_addrs > alist->nr_ipv4)
		hlist_add_head_rcu(&server->addr6_link, &net->fs_addresses6);

	ग_लिखो_sequnlock(&net->fs_addr_lock);

exists:
	afs_get_server(server, afs_server_trace_get_install);
	ग_लिखो_sequnlock(&net->fs_lock);
	वापस server;
पूर्ण

/*
 * Allocate a new server record and mark it active.
 */
अटल काष्ठा afs_server *afs_alloc_server(काष्ठा afs_cell *cell,
					   स्थिर uuid_t *uuid,
					   काष्ठा afs_addr_list *alist)
अणु
	काष्ठा afs_server *server;
	काष्ठा afs_net *net = cell->net;

	_enter("");

	server = kzalloc(माप(काष्ठा afs_server), GFP_KERNEL);
	अगर (!server)
		जाओ enomem;

	atomic_set(&server->ref, 1);
	atomic_set(&server->active, 1);
	server->debug_id = atomic_inc_वापस(&afs_server_debug_id);
	RCU_INIT_POINTER(server->addresses, alist);
	server->addr_version = alist->version;
	server->uuid = *uuid;
	rwlock_init(&server->fs_lock);
	init_रुकोqueue_head(&server->probe_wq);
	INIT_LIST_HEAD(&server->probe_link);
	spin_lock_init(&server->probe_lock);
	server->cell = cell;
	server->rtt = अच_पूर्णांक_उच्च;

	afs_inc_servers_outstanding(net);
	trace_afs_server(server, 1, 1, afs_server_trace_alloc);
	_leave(" = %p", server);
	वापस server;

enomem:
	_leave(" = NULL [nomem]");
	वापस शून्य;
पूर्ण

/*
 * Look up an address record क्रम a server
 */
अटल काष्ठा afs_addr_list *afs_vl_lookup_addrs(काष्ठा afs_cell *cell,
						 काष्ठा key *key, स्थिर uuid_t *uuid)
अणु
	काष्ठा afs_vl_cursor vc;
	काष्ठा afs_addr_list *alist = शून्य;
	पूर्णांक ret;

	ret = -ERESTARTSYS;
	अगर (afs_begin_vlserver_operation(&vc, cell, key)) अणु
		जबतक (afs_select_vlserver(&vc)) अणु
			अगर (test_bit(AFS_VLSERVER_FL_IS_YFS, &vc.server->flags))
				alist = afs_yfsvl_get_endpoपूर्णांकs(&vc, uuid);
			अन्यथा
				alist = afs_vl_get_addrs_u(&vc, uuid);
		पूर्ण

		ret = afs_end_vlserver_operation(&vc);
	पूर्ण

	वापस ret < 0 ? ERR_PTR(ret) : alist;
पूर्ण

/*
 * Get or create a fileserver record.
 */
काष्ठा afs_server *afs_lookup_server(काष्ठा afs_cell *cell, काष्ठा key *key,
				     स्थिर uuid_t *uuid, u32 addr_version)
अणु
	काष्ठा afs_addr_list *alist;
	काष्ठा afs_server *server, *candidate;

	_enter("%p,%pU", cell->net, uuid);

	server = afs_find_server_by_uuid(cell->net, uuid);
	अगर (server) अणु
		अगर (server->addr_version != addr_version)
			set_bit(AFS_SERVER_FL_NEEDS_UPDATE, &server->flags);
		वापस server;
	पूर्ण

	alist = afs_vl_lookup_addrs(cell, key, uuid);
	अगर (IS_ERR(alist))
		वापस ERR_CAST(alist);

	candidate = afs_alloc_server(cell, uuid, alist);
	अगर (!candidate) अणु
		afs_put_addrlist(alist);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	server = afs_install_server(cell, candidate);
	अगर (server != candidate) अणु
		afs_put_addrlist(alist);
		kमुक्त(candidate);
	पूर्ण अन्यथा अणु
		/* Immediately dispatch an asynchronous probe to each पूर्णांकerface
		 * on the fileserver.  This will make sure the repeat-probing
		 * service is started.
		 */
		afs_fs_probe_fileserver(cell->net, server, key, true);
	पूर्ण

	वापस server;
पूर्ण

/*
 * Set the server समयr to fire after a given delay, assuming it's not alपढ़ोy
 * set क्रम an earlier समय.
 */
अटल व्योम afs_set_server_समयr(काष्ठा afs_net *net, समय64_t delay)
अणु
	अगर (net->live) अणु
		afs_inc_servers_outstanding(net);
		अगर (समयr_reduce(&net->fs_समयr, jअगरfies + delay * HZ))
			afs_dec_servers_outstanding(net);
	पूर्ण
पूर्ण

/*
 * Server management समयr.  We have an increment on fs_outstanding that we
 * need to pass aदीर्घ to the work item.
 */
व्योम afs_servers_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा afs_net *net = container_of(समयr, काष्ठा afs_net, fs_समयr);

	_enter("");
	अगर (!queue_work(afs_wq, &net->fs_manager))
		afs_dec_servers_outstanding(net);
पूर्ण

/*
 * Get a reference on a server object.
 */
काष्ठा afs_server *afs_get_server(काष्ठा afs_server *server,
				  क्रमागत afs_server_trace reason)
अणु
	अचिन्हित पूर्णांक u = atomic_inc_वापस(&server->ref);

	trace_afs_server(server, u, atomic_पढ़ो(&server->active), reason);
	वापस server;
पूर्ण

/*
 * Try to get a reference on a server object.
 */
अटल काष्ठा afs_server *afs_maybe_use_server(काष्ठा afs_server *server,
					       क्रमागत afs_server_trace reason)
अणु
	अचिन्हित पूर्णांक r = atomic_fetch_add_unless(&server->ref, 1, 0);
	अचिन्हित पूर्णांक a;

	अगर (r == 0)
		वापस शून्य;

	a = atomic_inc_वापस(&server->active);
	trace_afs_server(server, r, a, reason);
	वापस server;
पूर्ण

/*
 * Get an active count on a server object.
 */
काष्ठा afs_server *afs_use_server(काष्ठा afs_server *server, क्रमागत afs_server_trace reason)
अणु
	अचिन्हित पूर्णांक r = atomic_inc_वापस(&server->ref);
	अचिन्हित पूर्णांक a = atomic_inc_वापस(&server->active);

	trace_afs_server(server, r, a, reason);
	वापस server;
पूर्ण

/*
 * Release a reference on a server record.
 */
व्योम afs_put_server(काष्ठा afs_net *net, काष्ठा afs_server *server,
		    क्रमागत afs_server_trace reason)
अणु
	अचिन्हित पूर्णांक usage;

	अगर (!server)
		वापस;

	usage = atomic_dec_वापस(&server->ref);
	trace_afs_server(server, usage, atomic_पढ़ो(&server->active), reason);
	अगर (unlikely(usage == 0))
		__afs_put_server(net, server);
पूर्ण

/*
 * Drop an active count on a server object without updating the last-unused
 * समय.
 */
व्योम afs_unuse_server_noसमय(काष्ठा afs_net *net, काष्ठा afs_server *server,
			     क्रमागत afs_server_trace reason)
अणु
	अगर (server) अणु
		अचिन्हित पूर्णांक active = atomic_dec_वापस(&server->active);

		अगर (active == 0)
			afs_set_server_समयr(net, afs_server_gc_delay);
		afs_put_server(net, server, reason);
	पूर्ण
पूर्ण

/*
 * Drop an active count on a server object.
 */
व्योम afs_unuse_server(काष्ठा afs_net *net, काष्ठा afs_server *server,
		      क्रमागत afs_server_trace reason)
अणु
	अगर (server) अणु
		server->unuse_समय = kसमय_get_real_seconds();
		afs_unuse_server_noसमय(net, server, reason);
	पूर्ण
पूर्ण

अटल व्योम afs_server_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा afs_server *server = container_of(rcu, काष्ठा afs_server, rcu);

	trace_afs_server(server, atomic_पढ़ो(&server->ref),
			 atomic_पढ़ो(&server->active), afs_server_trace_मुक्त);
	afs_put_addrlist(rcu_access_poपूर्णांकer(server->addresses));
	kमुक्त(server);
पूर्ण

अटल व्योम __afs_put_server(काष्ठा afs_net *net, काष्ठा afs_server *server)
अणु
	call_rcu(&server->rcu, afs_server_rcu);
	afs_dec_servers_outstanding(net);
पूर्ण

अटल व्योम afs_give_up_callbacks(काष्ठा afs_net *net, काष्ठा afs_server *server)
अणु
	काष्ठा afs_addr_list *alist = rcu_access_poपूर्णांकer(server->addresses);
	काष्ठा afs_addr_cursor ac = अणु
		.alist	= alist,
		.index	= alist->preferred,
		.error	= 0,
	पूर्ण;

	afs_fs_give_up_all_callbacks(net, server, &ac, शून्य);
पूर्ण

/*
 * destroy a dead server
 */
अटल व्योम afs_destroy_server(काष्ठा afs_net *net, काष्ठा afs_server *server)
अणु
	अगर (test_bit(AFS_SERVER_FL_MAY_HAVE_CB, &server->flags))
		afs_give_up_callbacks(net, server);

	afs_put_server(net, server, afs_server_trace_destroy);
पूर्ण

/*
 * Garbage collect any expired servers.
 */
अटल व्योम afs_gc_servers(काष्ठा afs_net *net, काष्ठा afs_server *gc_list)
अणु
	काष्ठा afs_server *server, *next, *prev;
	पूर्णांक active;

	जबतक ((server = gc_list)) अणु
		gc_list = server->gc_next;

		ग_लिखो_seqlock(&net->fs_lock);

		active = atomic_पढ़ो(&server->active);
		अगर (active == 0) अणु
			trace_afs_server(server, atomic_पढ़ो(&server->ref),
					 active, afs_server_trace_gc);
			next = rcu_dereference_रक्षित(
				server->uuid_next, lockdep_is_held(&net->fs_lock.lock));
			prev = server->uuid_prev;
			अगर (!prev) अणु
				/* The one at the front is in the tree */
				अगर (!next) अणु
					rb_erase(&server->uuid_rb, &net->fs_servers);
				पूर्ण अन्यथा अणु
					rb_replace_node_rcu(&server->uuid_rb,
							    &next->uuid_rb,
							    &net->fs_servers);
					next->uuid_prev = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* This server is not at the front */
				rcu_assign_poपूर्णांकer(prev->uuid_next, next);
				अगर (next)
					next->uuid_prev = prev;
			पूर्ण

			list_del(&server->probe_link);
			hlist_del_rcu(&server->proc_link);
			अगर (!hlist_unhashed(&server->addr4_link))
				hlist_del_rcu(&server->addr4_link);
			अगर (!hlist_unhashed(&server->addr6_link))
				hlist_del_rcu(&server->addr6_link);
		पूर्ण
		ग_लिखो_sequnlock(&net->fs_lock);

		अगर (active == 0)
			afs_destroy_server(net, server);
	पूर्ण
पूर्ण

/*
 * Manage the records of servers known to be within a network namespace.  This
 * includes garbage collecting unused servers.
 *
 * Note also that we were given an increment on net->servers_outstanding by
 * whoever queued us that we need to deal with beक्रमe वापसing.
 */
व्योम afs_manage_servers(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_net *net = container_of(work, काष्ठा afs_net, fs_manager);
	काष्ठा afs_server *gc_list = शून्य;
	काष्ठा rb_node *cursor;
	समय64_t now = kसमय_get_real_seconds(), next_manage = TIME64_MAX;
	bool purging = !net->live;

	_enter("");

	/* Trawl the server list looking क्रम servers that have expired from
	 * lack of use.
	 */
	पढ़ो_seqlock_excl(&net->fs_lock);

	क्रम (cursor = rb_first(&net->fs_servers); cursor; cursor = rb_next(cursor)) अणु
		काष्ठा afs_server *server =
			rb_entry(cursor, काष्ठा afs_server, uuid_rb);
		पूर्णांक active = atomic_पढ़ो(&server->active);

		_debug("manage %pU %u", &server->uuid, active);

		अगर (purging) अणु
			trace_afs_server(server, atomic_पढ़ो(&server->ref),
					 active, afs_server_trace_purging);
			अगर (active != 0)
				pr_notice("Can't purge s=%08x\n", server->debug_id);
		पूर्ण

		अगर (active == 0) अणु
			समय64_t expire_at = server->unuse_समय;

			अगर (!test_bit(AFS_SERVER_FL_VL_FAIL, &server->flags) &&
			    !test_bit(AFS_SERVER_FL_NOT_FOUND, &server->flags))
				expire_at += afs_server_gc_delay;
			अगर (purging || expire_at <= now) अणु
				server->gc_next = gc_list;
				gc_list = server;
			पूर्ण अन्यथा अगर (expire_at < next_manage) अणु
				next_manage = expire_at;
			पूर्ण
		पूर्ण
	पूर्ण

	पढ़ो_sequnlock_excl(&net->fs_lock);

	/* Update the समयr on the way out.  We have to pass an increment on
	 * servers_outstanding in the namespace that we are in to the समयr or
	 * the work scheduler.
	 */
	अगर (!purging && next_manage < TIME64_MAX) अणु
		now = kसमय_get_real_seconds();

		अगर (next_manage - now <= 0) अणु
			अगर (queue_work(afs_wq, &net->fs_manager))
				afs_inc_servers_outstanding(net);
		पूर्ण अन्यथा अणु
			afs_set_server_समयr(net, next_manage - now);
		पूर्ण
	पूर्ण

	afs_gc_servers(net, gc_list);

	afs_dec_servers_outstanding(net);
	_leave(" [%d]", atomic_पढ़ो(&net->servers_outstanding));
पूर्ण

अटल व्योम afs_queue_server_manager(काष्ठा afs_net *net)
अणु
	afs_inc_servers_outstanding(net);
	अगर (!queue_work(afs_wq, &net->fs_manager))
		afs_dec_servers_outstanding(net);
पूर्ण

/*
 * Purge list of servers.
 */
व्योम afs_purge_servers(काष्ठा afs_net *net)
अणु
	_enter("");

	अगर (del_समयr_sync(&net->fs_समयr))
		afs_dec_servers_outstanding(net);

	afs_queue_server_manager(net);

	_debug("wait");
	atomic_dec(&net->servers_outstanding);
	रुको_var_event(&net->servers_outstanding,
		       !atomic_पढ़ो(&net->servers_outstanding));
	_leave("");
पूर्ण

/*
 * Get an update क्रम a server's address list.
 */
अटल noअंतरभूत bool afs_update_server_record(काष्ठा afs_operation *op,
					      काष्ठा afs_server *server)
अणु
	काष्ठा afs_addr_list *alist, *discard;

	_enter("");

	trace_afs_server(server, atomic_पढ़ो(&server->ref), atomic_पढ़ो(&server->active),
			 afs_server_trace_update);

	alist = afs_vl_lookup_addrs(op->volume->cell, op->key, &server->uuid);
	अगर (IS_ERR(alist)) अणु
		अगर ((PTR_ERR(alist) == -ERESTARTSYS ||
		     PTR_ERR(alist) == -EINTR) &&
		    (op->flags & AFS_OPERATION_UNINTR) &&
		    server->addresses) अणु
			_leave(" = t [intr]");
			वापस true;
		पूर्ण
		op->error = PTR_ERR(alist);
		_leave(" = f [%d]", op->error);
		वापस false;
	पूर्ण

	discard = alist;
	अगर (server->addr_version != alist->version) अणु
		ग_लिखो_lock(&server->fs_lock);
		discard = rcu_dereference_रक्षित(server->addresses,
						    lockdep_is_held(&server->fs_lock));
		rcu_assign_poपूर्णांकer(server->addresses, alist);
		server->addr_version = alist->version;
		ग_लिखो_unlock(&server->fs_lock);
	पूर्ण

	afs_put_addrlist(discard);
	_leave(" = t");
	वापस true;
पूर्ण

/*
 * See अगर a server's address list needs updating.
 */
bool afs_check_server_record(काष्ठा afs_operation *op, काष्ठा afs_server *server)
अणु
	bool success;
	पूर्णांक ret, retries = 0;

	_enter("");

	ASSERT(server);

retry:
	अगर (test_bit(AFS_SERVER_FL_UPDATING, &server->flags))
		जाओ रुको;
	अगर (test_bit(AFS_SERVER_FL_NEEDS_UPDATE, &server->flags))
		जाओ update;
	_leave(" = t [good]");
	वापस true;

update:
	अगर (!test_and_set_bit_lock(AFS_SERVER_FL_UPDATING, &server->flags)) अणु
		clear_bit(AFS_SERVER_FL_NEEDS_UPDATE, &server->flags);
		success = afs_update_server_record(op, server);
		clear_bit_unlock(AFS_SERVER_FL_UPDATING, &server->flags);
		wake_up_bit(&server->flags, AFS_SERVER_FL_UPDATING);
		_leave(" = %d", success);
		वापस success;
	पूर्ण

रुको:
	ret = रुको_on_bit(&server->flags, AFS_SERVER_FL_UPDATING,
			  (op->flags & AFS_OPERATION_UNINTR) ?
			  TASK_UNINTERRUPTIBLE : TASK_INTERRUPTIBLE);
	अगर (ret == -ERESTARTSYS) अणु
		op->error = ret;
		_leave(" = f [intr]");
		वापस false;
	पूर्ण

	retries++;
	अगर (retries == 4) अणु
		_leave(" = f [stale]");
		ret = -ESTALE;
		वापस false;
	पूर्ण
	जाओ retry;
पूर्ण
