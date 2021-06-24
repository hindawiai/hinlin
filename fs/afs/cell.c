<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS cell and server record management
 *
 * Copyright (C) 2002, 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/key.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dns_resolver.h>
#समावेश <linux/sched.h>
#समावेश <linux/inet.h>
#समावेश <linux/namei.h>
#समावेश <keys/rxrpc-type.h>
#समावेश "internal.h"

अटल अचिन्हित __पढ़ो_mostly afs_cell_gc_delay = 10;
अटल अचिन्हित __पढ़ो_mostly afs_cell_min_ttl = 10 * 60;
अटल अचिन्हित __पढ़ो_mostly afs_cell_max_ttl = 24 * 60 * 60;
अटल atomic_t cell_debug_id;

अटल व्योम afs_queue_cell_manager(काष्ठा afs_net *);
अटल व्योम afs_manage_cell_work(काष्ठा work_काष्ठा *);

अटल व्योम afs_dec_cells_outstanding(काष्ठा afs_net *net)
अणु
	अगर (atomic_dec_and_test(&net->cells_outstanding))
		wake_up_var(&net->cells_outstanding);
पूर्ण

/*
 * Set the cell समयr to fire after a given delay, assuming it's not alपढ़ोy
 * set क्रम an earlier समय.
 */
अटल व्योम afs_set_cell_समयr(काष्ठा afs_net *net, समय64_t delay)
अणु
	अगर (net->live) अणु
		atomic_inc(&net->cells_outstanding);
		अगर (समयr_reduce(&net->cells_समयr, jअगरfies + delay * HZ))
			afs_dec_cells_outstanding(net);
	पूर्ण अन्यथा अणु
		afs_queue_cell_manager(net);
	पूर्ण
पूर्ण

/*
 * Look up and get an activation reference on a cell record.  The caller must
 * hold net->cells_lock at least पढ़ो-locked.
 */
अटल काष्ठा afs_cell *afs_find_cell_locked(काष्ठा afs_net *net,
					     स्थिर अक्षर *name, अचिन्हित पूर्णांक namesz,
					     क्रमागत afs_cell_trace reason)
अणु
	काष्ठा afs_cell *cell = शून्य;
	काष्ठा rb_node *p;
	पूर्णांक n;

	_enter("%*.*s", namesz, namesz, name);

	अगर (name && namesz == 0)
		वापस ERR_PTR(-EINVAL);
	अगर (namesz > AFS_MAXCELLNAME)
		वापस ERR_PTR(-ENAMETOOLONG);

	अगर (!name) अणु
		cell = net->ws_cell;
		अगर (!cell)
			वापस ERR_PTR(-EDESTADDRREQ);
		जाओ found;
	पूर्ण

	p = net->cells.rb_node;
	जबतक (p) अणु
		cell = rb_entry(p, काष्ठा afs_cell, net_node);

		n = strnहालcmp(cell->name, name,
				min_t(माप_प्रकार, cell->name_len, namesz));
		अगर (n == 0)
			n = cell->name_len - namesz;
		अगर (n < 0)
			p = p->rb_left;
		अन्यथा अगर (n > 0)
			p = p->rb_right;
		अन्यथा
			जाओ found;
	पूर्ण

	वापस ERR_PTR(-ENOENT);

found:
	वापस afs_use_cell(cell, reason);
पूर्ण

/*
 * Look up and get an activation reference on a cell record.
 */
काष्ठा afs_cell *afs_find_cell(काष्ठा afs_net *net,
			       स्थिर अक्षर *name, अचिन्हित पूर्णांक namesz,
			       क्रमागत afs_cell_trace reason)
अणु
	काष्ठा afs_cell *cell;

	करोwn_पढ़ो(&net->cells_lock);
	cell = afs_find_cell_locked(net, name, namesz, reason);
	up_पढ़ो(&net->cells_lock);
	वापस cell;
पूर्ण

/*
 * Set up a cell record and fill in its name, VL server address list and
 * allocate an anonymous key
 */
अटल काष्ठा afs_cell *afs_alloc_cell(काष्ठा afs_net *net,
				       स्थिर अक्षर *name, अचिन्हित पूर्णांक namelen,
				       स्थिर अक्षर *addresses)
अणु
	काष्ठा afs_vlserver_list *vllist;
	काष्ठा afs_cell *cell;
	पूर्णांक i, ret;

	ASSERT(name);
	अगर (namelen == 0)
		वापस ERR_PTR(-EINVAL);
	अगर (namelen > AFS_MAXCELLNAME) अणु
		_leave(" = -ENAMETOOLONG");
		वापस ERR_PTR(-ENAMETOOLONG);
	पूर्ण

	/* Prohibit cell names that contain unprपूर्णांकable अक्षरs, '/' and '@' or
	 * that begin with a करोt.  This also precludes "@cell".
	 */
	अगर (name[0] == '.')
		वापस ERR_PTR(-EINVAL);
	क्रम (i = 0; i < namelen; i++) अणु
		अक्षर ch = name[i];
		अगर (!है_छाप(ch) || ch == '/' || ch == '@')
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	_enter("%*.*s,%s", namelen, namelen, name, addresses);

	cell = kzalloc(माप(काष्ठा afs_cell), GFP_KERNEL);
	अगर (!cell) अणु
		_leave(" = -ENOMEM");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	cell->name = kदो_स्मृति(namelen + 1, GFP_KERNEL);
	अगर (!cell->name) अणु
		kमुक्त(cell);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	cell->net = net;
	cell->name_len = namelen;
	क्रम (i = 0; i < namelen; i++)
		cell->name[i] = छोटे(name[i]);
	cell->name[i] = 0;

	atomic_set(&cell->ref, 1);
	atomic_set(&cell->active, 0);
	INIT_WORK(&cell->manager, afs_manage_cell_work);
	cell->volumes = RB_ROOT;
	INIT_HLIST_HEAD(&cell->proc_volumes);
	seqlock_init(&cell->volume_lock);
	cell->fs_servers = RB_ROOT;
	seqlock_init(&cell->fs_lock);
	rwlock_init(&cell->vl_servers_lock);
	cell->flags = (1 << AFS_CELL_FL_CHECK_ALIAS);

	/* Provide a VL server list, filling it in अगर we were given a list of
	 * addresses to use.
	 */
	अगर (addresses) अणु
		vllist = afs_parse_text_addrs(net,
					      addresses, म_माप(addresses), ':',
					      VL_SERVICE, AFS_VL_PORT);
		अगर (IS_ERR(vllist)) अणु
			ret = PTR_ERR(vllist);
			जाओ parse_failed;
		पूर्ण

		vllist->source = DNS_RECORD_FROM_CONFIG;
		vllist->status = DNS_LOOKUP_NOT_DONE;
		cell->dns_expiry = TIME64_MAX;
	पूर्ण अन्यथा अणु
		ret = -ENOMEM;
		vllist = afs_alloc_vlserver_list(0);
		अगर (!vllist)
			जाओ error;
		vllist->source = DNS_RECORD_UNAVAILABLE;
		vllist->status = DNS_LOOKUP_NOT_DONE;
		cell->dns_expiry = kसमय_get_real_seconds();
	पूर्ण

	rcu_assign_poपूर्णांकer(cell->vl_servers, vllist);

	cell->dns_source = vllist->source;
	cell->dns_status = vllist->status;
	smp_store_release(&cell->dns_lookup_count, 1); /* vs source/status */
	atomic_inc(&net->cells_outstanding);
	cell->debug_id = atomic_inc_वापस(&cell_debug_id);
	trace_afs_cell(cell->debug_id, 1, 0, afs_cell_trace_alloc);

	_leave(" = %p", cell);
	वापस cell;

parse_failed:
	अगर (ret == -EINVAL)
		prपूर्णांकk(KERN_ERR "kAFS: bad VL server IP address\n");
error:
	kमुक्त(cell->name);
	kमुक्त(cell);
	_leave(" = %d", ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * afs_lookup_cell - Look up or create a cell record.
 * @net:	The network namespace
 * @name:	The name of the cell.
 * @namesz:	The म_माप of the cell name.
 * @vllist:	A colon/comma separated list of numeric IP addresses or शून्य.
 * @excl:	T अगर an error should be given अगर the cell name alपढ़ोy exists.
 *
 * Look up a cell record by name and query the DNS क्रम VL server addresses अगर
 * needed.  Note that that actual DNS query is punted off to the manager thपढ़ो
 * so that this function can वापस immediately अगर पूर्णांकerrupted whilst allowing
 * cell records to be shared even अगर not yet fully स्थिरructed.
 */
काष्ठा afs_cell *afs_lookup_cell(काष्ठा afs_net *net,
				 स्थिर अक्षर *name, अचिन्हित पूर्णांक namesz,
				 स्थिर अक्षर *vllist, bool excl)
अणु
	काष्ठा afs_cell *cell, *candidate, *cursor;
	काष्ठा rb_node *parent, **pp;
	क्रमागत afs_cell_state state;
	पूर्णांक ret, n;

	_enter("%s,%s", name, vllist);

	अगर (!excl) अणु
		cell = afs_find_cell(net, name, namesz, afs_cell_trace_use_lookup);
		अगर (!IS_ERR(cell))
			जाओ रुको_क्रम_cell;
	पूर्ण

	/* Assume we're probably going to create a cell and pपुनः_स्मृतिate and
	 * mostly set up a candidate record.  We can then use this to stash the
	 * name, the net namespace and VL server addresses.
	 *
	 * We also want to करो this beक्रमe we hold any locks as it may involve
	 * upcalling to userspace to make DNS queries.
	 */
	candidate = afs_alloc_cell(net, name, namesz, vllist);
	अगर (IS_ERR(candidate)) अणु
		_leave(" = %ld", PTR_ERR(candidate));
		वापस candidate;
	पूर्ण

	/* Find the insertion poपूर्णांक and check to see अगर someone अन्यथा added a
	 * cell whilst we were allocating.
	 */
	करोwn_ग_लिखो(&net->cells_lock);

	pp = &net->cells.rb_node;
	parent = शून्य;
	जबतक (*pp) अणु
		parent = *pp;
		cursor = rb_entry(parent, काष्ठा afs_cell, net_node);

		n = strnहालcmp(cursor->name, name,
				min_t(माप_प्रकार, cursor->name_len, namesz));
		अगर (n == 0)
			n = cursor->name_len - namesz;
		अगर (n < 0)
			pp = &(*pp)->rb_left;
		अन्यथा अगर (n > 0)
			pp = &(*pp)->rb_right;
		अन्यथा
			जाओ cell_alपढ़ोy_exists;
	पूर्ण

	cell = candidate;
	candidate = शून्य;
	atomic_set(&cell->active, 2);
	trace_afs_cell(cell->debug_id, atomic_पढ़ो(&cell->ref), 2, afs_cell_trace_insert);
	rb_link_node_rcu(&cell->net_node, parent, pp);
	rb_insert_color(&cell->net_node, &net->cells);
	up_ग_लिखो(&net->cells_lock);

	afs_queue_cell(cell, afs_cell_trace_get_queue_new);

रुको_क्रम_cell:
	trace_afs_cell(cell->debug_id, atomic_पढ़ो(&cell->ref), atomic_पढ़ो(&cell->active),
		       afs_cell_trace_रुको);
	_debug("wait_for_cell");
	रुको_var_event(&cell->state,
		       (अणु
			       state = smp_load_acquire(&cell->state); /* vs error */
			       state == AFS_CELL_ACTIVE || state == AFS_CELL_REMOVED;
		       पूर्ण));

	/* Check the state obtained from the रुको check. */
	अगर (state == AFS_CELL_REMOVED) अणु
		ret = cell->error;
		जाओ error;
	पूर्ण

	_leave(" = %p [cell]", cell);
	वापस cell;

cell_alपढ़ोy_exists:
	_debug("cell exists");
	cell = cursor;
	अगर (excl) अणु
		ret = -EEXIST;
	पूर्ण अन्यथा अणु
		afs_use_cell(cursor, afs_cell_trace_use_lookup);
		ret = 0;
	पूर्ण
	up_ग_लिखो(&net->cells_lock);
	अगर (candidate)
		afs_put_cell(candidate, afs_cell_trace_put_candidate);
	अगर (ret == 0)
		जाओ रुको_क्रम_cell;
	जाओ error_noput;
error:
	afs_unuse_cell(net, cell, afs_cell_trace_unuse_lookup);
error_noput:
	_leave(" = %d [error]", ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * set the root cell inक्रमmation
 * - can be called with a module parameter string
 * - can be called from a ग_लिखो to /proc/fs/afs/rootcell
 */
पूर्णांक afs_cell_init(काष्ठा afs_net *net, स्थिर अक्षर *rootcell)
अणु
	काष्ठा afs_cell *old_root, *new_root;
	स्थिर अक्षर *cp, *vllist;
	माप_प्रकार len;

	_enter("");

	अगर (!rootcell) अणु
		/* module is loaded with no parameters, or built अटलally.
		 * - in the future we might initialize cell DB here.
		 */
		_leave(" = 0 [no root]");
		वापस 0;
	पूर्ण

	cp = म_अक्षर(rootcell, ':');
	अगर (!cp) अणु
		_debug("kAFS: no VL server IP addresses specified");
		vllist = शून्य;
		len = म_माप(rootcell);
	पूर्ण अन्यथा अणु
		vllist = cp + 1;
		len = cp - rootcell;
	पूर्ण

	/* allocate a cell record क्रम the root cell */
	new_root = afs_lookup_cell(net, rootcell, len, vllist, false);
	अगर (IS_ERR(new_root)) अणु
		_leave(" = %ld", PTR_ERR(new_root));
		वापस PTR_ERR(new_root);
	पूर्ण

	अगर (!test_and_set_bit(AFS_CELL_FL_NO_GC, &new_root->flags))
		afs_use_cell(new_root, afs_cell_trace_use_pin);

	/* install the new cell */
	करोwn_ग_लिखो(&net->cells_lock);
	afs_see_cell(new_root, afs_cell_trace_see_ws);
	old_root = net->ws_cell;
	net->ws_cell = new_root;
	up_ग_लिखो(&net->cells_lock);

	afs_unuse_cell(net, old_root, afs_cell_trace_unuse_ws);
	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * Update a cell's VL server address list from the DNS.
 */
अटल पूर्णांक afs_update_cell(काष्ठा afs_cell *cell)
अणु
	काष्ठा afs_vlserver_list *vllist, *old = शून्य, *p;
	अचिन्हित पूर्णांक min_ttl = READ_ONCE(afs_cell_min_ttl);
	अचिन्हित पूर्णांक max_ttl = READ_ONCE(afs_cell_max_ttl);
	समय64_t now, expiry = 0;
	पूर्णांक ret = 0;

	_enter("%s", cell->name);

	vllist = afs_dns_query(cell, &expiry);
	अगर (IS_ERR(vllist)) अणु
		ret = PTR_ERR(vllist);

		_debug("%s: fail %d", cell->name, ret);
		अगर (ret == -ENOMEM)
			जाओ out_wake;

		ret = -ENOMEM;
		vllist = afs_alloc_vlserver_list(0);
		अगर (!vllist)
			जाओ out_wake;

		चयन (ret) अणु
		हाल -ENODATA:
		हाल -EDESTADDRREQ:
			vllist->status = DNS_LOOKUP_GOT_NOT_FOUND;
			अवरोध;
		हाल -EAGAIN:
		हाल -ECONNREFUSED:
			vllist->status = DNS_LOOKUP_GOT_TEMP_FAILURE;
			अवरोध;
		शेष:
			vllist->status = DNS_LOOKUP_GOT_LOCAL_FAILURE;
			अवरोध;
		पूर्ण
	पूर्ण

	_debug("%s: got list %d %d", cell->name, vllist->source, vllist->status);
	cell->dns_status = vllist->status;

	now = kसमय_get_real_seconds();
	अगर (min_ttl > max_ttl)
		max_ttl = min_ttl;
	अगर (expiry < now + min_ttl)
		expiry = now + min_ttl;
	अन्यथा अगर (expiry > now + max_ttl)
		expiry = now + max_ttl;

	_debug("%s: status %d", cell->name, vllist->status);
	अगर (vllist->source == DNS_RECORD_UNAVAILABLE) अणु
		चयन (vllist->status) अणु
		हाल DNS_LOOKUP_GOT_NOT_FOUND:
			/* The DNS said that the cell करोes not exist or there
			 * weren't any addresses to be had.
			 */
			cell->dns_expiry = expiry;
			अवरोध;

		हाल DNS_LOOKUP_BAD:
		हाल DNS_LOOKUP_GOT_LOCAL_FAILURE:
		हाल DNS_LOOKUP_GOT_TEMP_FAILURE:
		हाल DNS_LOOKUP_GOT_NS_FAILURE:
		शेष:
			cell->dns_expiry = now + 10;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		cell->dns_expiry = expiry;
	पूर्ण

	/* Replace the VL server list अगर the new record has servers or the old
	 * record करोesn't.
	 */
	ग_लिखो_lock(&cell->vl_servers_lock);
	p = rcu_dereference_रक्षित(cell->vl_servers, true);
	अगर (vllist->nr_servers > 0 || p->nr_servers == 0) अणु
		rcu_assign_poपूर्णांकer(cell->vl_servers, vllist);
		cell->dns_source = vllist->source;
		old = p;
	पूर्ण
	ग_लिखो_unlock(&cell->vl_servers_lock);
	afs_put_vlserverlist(cell->net, old);

out_wake:
	smp_store_release(&cell->dns_lookup_count,
			  cell->dns_lookup_count + 1); /* vs source/status */
	wake_up_var(&cell->dns_lookup_count);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Destroy a cell record
 */
अटल व्योम afs_cell_destroy(काष्ठा rcu_head *rcu)
अणु
	काष्ठा afs_cell *cell = container_of(rcu, काष्ठा afs_cell, rcu);
	काष्ठा afs_net *net = cell->net;
	पूर्णांक u;

	_enter("%p{%s}", cell, cell->name);

	u = atomic_पढ़ो(&cell->ref);
	ASSERTCMP(u, ==, 0);
	trace_afs_cell(cell->debug_id, u, atomic_पढ़ो(&cell->active), afs_cell_trace_मुक्त);

	afs_put_vlserverlist(net, rcu_access_poपूर्णांकer(cell->vl_servers));
	afs_unuse_cell(net, cell->alias_of, afs_cell_trace_unuse_alias);
	key_put(cell->anonymous_key);
	kमुक्त(cell->name);
	kमुक्त(cell);

	afs_dec_cells_outstanding(net);
	_leave(" [destroyed]");
पूर्ण

/*
 * Queue the cell manager.
 */
अटल व्योम afs_queue_cell_manager(काष्ठा afs_net *net)
अणु
	पूर्णांक outstanding = atomic_inc_वापस(&net->cells_outstanding);

	_enter("%d", outstanding);

	अगर (!queue_work(afs_wq, &net->cells_manager))
		afs_dec_cells_outstanding(net);
पूर्ण

/*
 * Cell management समयr.  We have an increment on cells_outstanding that we
 * need to pass aदीर्घ to the work item.
 */
व्योम afs_cells_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा afs_net *net = container_of(समयr, काष्ठा afs_net, cells_समयr);

	_enter("");
	अगर (!queue_work(afs_wq, &net->cells_manager))
		afs_dec_cells_outstanding(net);
पूर्ण

/*
 * Get a reference on a cell record.
 */
काष्ठा afs_cell *afs_get_cell(काष्ठा afs_cell *cell, क्रमागत afs_cell_trace reason)
अणु
	पूर्णांक u;

	अगर (atomic_पढ़ो(&cell->ref) <= 0)
		BUG();

	u = atomic_inc_वापस(&cell->ref);
	trace_afs_cell(cell->debug_id, u, atomic_पढ़ो(&cell->active), reason);
	वापस cell;
पूर्ण

/*
 * Drop a reference on a cell record.
 */
व्योम afs_put_cell(काष्ठा afs_cell *cell, क्रमागत afs_cell_trace reason)
अणु
	अगर (cell) अणु
		अचिन्हित पूर्णांक debug_id = cell->debug_id;
		अचिन्हित पूर्णांक u, a;

		a = atomic_पढ़ो(&cell->active);
		u = atomic_dec_वापस(&cell->ref);
		trace_afs_cell(debug_id, u, a, reason);
		अगर (u == 0) अणु
			a = atomic_पढ़ो(&cell->active);
			WARN(a != 0, "Cell active count %u > 0\n", a);
			call_rcu(&cell->rcu, afs_cell_destroy);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Note a cell becoming more active.
 */
काष्ठा afs_cell *afs_use_cell(काष्ठा afs_cell *cell, क्रमागत afs_cell_trace reason)
अणु
	पूर्णांक u, a;

	अगर (atomic_पढ़ो(&cell->ref) <= 0)
		BUG();

	u = atomic_पढ़ो(&cell->ref);
	a = atomic_inc_वापस(&cell->active);
	trace_afs_cell(cell->debug_id, u, a, reason);
	वापस cell;
पूर्ण

/*
 * Record a cell becoming less active.  When the active counter reaches 1, it
 * is scheduled क्रम deकाष्ठाion, but may get reactivated.
 */
व्योम afs_unuse_cell(काष्ठा afs_net *net, काष्ठा afs_cell *cell, क्रमागत afs_cell_trace reason)
अणु
	अचिन्हित पूर्णांक debug_id;
	समय64_t now, expire_delay;
	पूर्णांक u, a;

	अगर (!cell)
		वापस;

	_enter("%s", cell->name);

	now = kसमय_get_real_seconds();
	cell->last_inactive = now;
	expire_delay = 0;
	अगर (cell->vl_servers->nr_servers)
		expire_delay = afs_cell_gc_delay;

	debug_id = cell->debug_id;
	u = atomic_पढ़ो(&cell->ref);
	a = atomic_dec_वापस(&cell->active);
	trace_afs_cell(debug_id, u, a, reason);
	WARN_ON(a == 0);
	अगर (a == 1)
		/* 'cell' may now be garbage collected. */
		afs_set_cell_समयr(net, expire_delay);
पूर्ण

/*
 * Note that a cell has been seen.
 */
व्योम afs_see_cell(काष्ठा afs_cell *cell, क्रमागत afs_cell_trace reason)
अणु
	पूर्णांक u, a;

	u = atomic_पढ़ो(&cell->ref);
	a = atomic_पढ़ो(&cell->active);
	trace_afs_cell(cell->debug_id, u, a, reason);
पूर्ण

/*
 * Queue a cell क्रम management, giving the workqueue a ref to hold.
 */
व्योम afs_queue_cell(काष्ठा afs_cell *cell, क्रमागत afs_cell_trace reason)
अणु
	afs_get_cell(cell, reason);
	अगर (!queue_work(afs_wq, &cell->manager))
		afs_put_cell(cell, afs_cell_trace_put_queue_fail);
पूर्ण

/*
 * Allocate a key to use as a placeholder क्रम anonymous user security.
 */
अटल पूर्णांक afs_alloc_anon_key(काष्ठा afs_cell *cell)
अणु
	काष्ठा key *key;
	अक्षर keyname[4 + AFS_MAXCELLNAME + 1], *cp, *dp;

	/* Create a key to represent an anonymous user. */
	स_नकल(keyname, "afs@", 4);
	dp = keyname + 4;
	cp = cell->name;
	करो अणु
		*dp++ = छोटे(*cp);
	पूर्ण जबतक (*cp++);

	key = rxrpc_get_null_key(keyname);
	अगर (IS_ERR(key))
		वापस PTR_ERR(key);

	cell->anonymous_key = key;

	_debug("anon key %p{%x}",
	       cell->anonymous_key, key_serial(cell->anonymous_key));
	वापस 0;
पूर्ण

/*
 * Activate a cell.
 */
अटल पूर्णांक afs_activate_cell(काष्ठा afs_net *net, काष्ठा afs_cell *cell)
अणु
	काष्ठा hlist_node **p;
	काष्ठा afs_cell *pcell;
	पूर्णांक ret;

	अगर (!cell->anonymous_key) अणु
		ret = afs_alloc_anon_key(cell);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_AFS_FSCACHE
	cell->cache = fscache_acquire_cookie(afs_cache_netfs.primary_index,
					     &afs_cell_cache_index_def,
					     cell->name, म_माप(cell->name),
					     शून्य, 0,
					     cell, 0, true);
#पूर्ण_अगर
	ret = afs_proc_cell_setup(cell);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&net->proc_cells_lock);
	क्रम (p = &net->proc_cells.first; *p; p = &(*p)->next) अणु
		pcell = hlist_entry(*p, काष्ठा afs_cell, proc_link);
		अगर (म_भेद(cell->name, pcell->name) < 0)
			अवरोध;
	पूर्ण

	cell->proc_link.pprev = p;
	cell->proc_link.next = *p;
	rcu_assign_poपूर्णांकer(*p, &cell->proc_link.next);
	अगर (cell->proc_link.next)
		cell->proc_link.next->pprev = &cell->proc_link.next;

	afs_dynroot_सूची_गढ़ो(net, cell);
	mutex_unlock(&net->proc_cells_lock);
	वापस 0;
पूर्ण

/*
 * Deactivate a cell.
 */
अटल व्योम afs_deactivate_cell(काष्ठा afs_net *net, काष्ठा afs_cell *cell)
अणु
	_enter("%s", cell->name);

	afs_proc_cell_हटाओ(cell);

	mutex_lock(&net->proc_cells_lock);
	hlist_del_rcu(&cell->proc_link);
	afs_dynroot_सूची_हटाओ(net, cell);
	mutex_unlock(&net->proc_cells_lock);

#अगर_घोषित CONFIG_AFS_FSCACHE
	fscache_relinquish_cookie(cell->cache, शून्य, false);
	cell->cache = शून्य;
#पूर्ण_अगर

	_leave("");
पूर्ण

/*
 * Manage a cell record, initialising and destroying it, मुख्यtaining its DNS
 * records.
 */
अटल व्योम afs_manage_cell(काष्ठा afs_cell *cell)
अणु
	काष्ठा afs_net *net = cell->net;
	पूर्णांक ret, active;

	_enter("%s", cell->name);

again:
	_debug("state %u", cell->state);
	चयन (cell->state) अणु
	हाल AFS_CELL_INACTIVE:
	हाल AFS_CELL_FAILED:
		करोwn_ग_लिखो(&net->cells_lock);
		active = 1;
		अगर (atomic_try_cmpxchg_relaxed(&cell->active, &active, 0)) अणु
			rb_erase(&cell->net_node, &net->cells);
			trace_afs_cell(cell->debug_id, atomic_पढ़ो(&cell->ref), 0,
				       afs_cell_trace_unuse_delete);
			smp_store_release(&cell->state, AFS_CELL_REMOVED);
		पूर्ण
		up_ग_लिखो(&net->cells_lock);
		अगर (cell->state == AFS_CELL_REMOVED) अणु
			wake_up_var(&cell->state);
			जाओ final_deकाष्ठाion;
		पूर्ण
		अगर (cell->state == AFS_CELL_FAILED)
			जाओ करोne;
		smp_store_release(&cell->state, AFS_CELL_UNSET);
		wake_up_var(&cell->state);
		जाओ again;

	हाल AFS_CELL_UNSET:
		smp_store_release(&cell->state, AFS_CELL_ACTIVATING);
		wake_up_var(&cell->state);
		जाओ again;

	हाल AFS_CELL_ACTIVATING:
		ret = afs_activate_cell(net, cell);
		अगर (ret < 0)
			जाओ activation_failed;

		smp_store_release(&cell->state, AFS_CELL_ACTIVE);
		wake_up_var(&cell->state);
		जाओ again;

	हाल AFS_CELL_ACTIVE:
		अगर (atomic_पढ़ो(&cell->active) > 1) अणु
			अगर (test_and_clear_bit(AFS_CELL_FL_DO_LOOKUP, &cell->flags)) अणु
				ret = afs_update_cell(cell);
				अगर (ret < 0)
					cell->error = ret;
			पूर्ण
			जाओ करोne;
		पूर्ण
		smp_store_release(&cell->state, AFS_CELL_DEACTIVATING);
		wake_up_var(&cell->state);
		जाओ again;

	हाल AFS_CELL_DEACTIVATING:
		अगर (atomic_पढ़ो(&cell->active) > 1)
			जाओ reverse_deactivation;
		afs_deactivate_cell(net, cell);
		smp_store_release(&cell->state, AFS_CELL_INACTIVE);
		wake_up_var(&cell->state);
		जाओ again;

	हाल AFS_CELL_REMOVED:
		जाओ करोne;

	शेष:
		अवरोध;
	पूर्ण
	_debug("bad state %u", cell->state);
	BUG(); /* Unhandled state */

activation_failed:
	cell->error = ret;
	afs_deactivate_cell(net, cell);

	smp_store_release(&cell->state, AFS_CELL_FAILED); /* vs error */
	wake_up_var(&cell->state);
	जाओ again;

reverse_deactivation:
	smp_store_release(&cell->state, AFS_CELL_ACTIVE);
	wake_up_var(&cell->state);
	_leave(" [deact->act]");
	वापस;

करोne:
	_leave(" [done %u]", cell->state);
	वापस;

final_deकाष्ठाion:
	/* The root volume is pinning the cell */
	afs_put_volume(cell->net, cell->root_volume, afs_volume_trace_put_cell_root);
	cell->root_volume = शून्य;
	afs_put_cell(cell, afs_cell_trace_put_destroy);
पूर्ण

अटल व्योम afs_manage_cell_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_cell *cell = container_of(work, काष्ठा afs_cell, manager);

	afs_manage_cell(cell);
	afs_put_cell(cell, afs_cell_trace_put_queue_work);
पूर्ण

/*
 * Manage the records of cells known to a network namespace.  This includes
 * updating the DNS records and garbage collecting unused cells that were
 * स्वतःmatically added.
 *
 * Note that स्थिरructed cell records may only be हटाओd from net->cells by
 * this work item, so it is safe क्रम this work item to stash a cursor poपूर्णांकing
 * पूर्णांकo the tree and then वापस to caller (provided it skips cells that are
 * still under स्थिरruction).
 *
 * Note also that we were given an increment on net->cells_outstanding by
 * whoever queued us that we need to deal with beक्रमe वापसing.
 */
व्योम afs_manage_cells(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_net *net = container_of(work, काष्ठा afs_net, cells_manager);
	काष्ठा rb_node *cursor;
	समय64_t now = kसमय_get_real_seconds(), next_manage = TIME64_MAX;
	bool purging = !net->live;

	_enter("");

	/* Trawl the cell database looking क्रम cells that have expired from
	 * lack of use and cells whose DNS results have expired and dispatch
	 * their managers.
	 */
	करोwn_पढ़ो(&net->cells_lock);

	क्रम (cursor = rb_first(&net->cells); cursor; cursor = rb_next(cursor)) अणु
		काष्ठा afs_cell *cell =
			rb_entry(cursor, काष्ठा afs_cell, net_node);
		अचिन्हित active;
		bool sched_cell = false;

		active = atomic_पढ़ो(&cell->active);
		trace_afs_cell(cell->debug_id, atomic_पढ़ो(&cell->ref),
			       active, afs_cell_trace_manage);

		ASSERTCMP(active, >=, 1);

		अगर (purging) अणु
			अगर (test_and_clear_bit(AFS_CELL_FL_NO_GC, &cell->flags)) अणु
				active = atomic_dec_वापस(&cell->active);
				trace_afs_cell(cell->debug_id, atomic_पढ़ो(&cell->ref),
					       active, afs_cell_trace_unuse_pin);
			पूर्ण
		पूर्ण

		अगर (active == 1) अणु
			काष्ठा afs_vlserver_list *vllist;
			समय64_t expire_at = cell->last_inactive;

			पढ़ो_lock(&cell->vl_servers_lock);
			vllist = rcu_dereference_रक्षित(
				cell->vl_servers,
				lockdep_is_held(&cell->vl_servers_lock));
			अगर (vllist->nr_servers > 0)
				expire_at += afs_cell_gc_delay;
			पढ़ो_unlock(&cell->vl_servers_lock);
			अगर (purging || expire_at <= now)
				sched_cell = true;
			अन्यथा अगर (expire_at < next_manage)
				next_manage = expire_at;
		पूर्ण

		अगर (!purging) अणु
			अगर (test_bit(AFS_CELL_FL_DO_LOOKUP, &cell->flags))
				sched_cell = true;
		पूर्ण

		अगर (sched_cell)
			afs_queue_cell(cell, afs_cell_trace_get_queue_manage);
	पूर्ण

	up_पढ़ो(&net->cells_lock);

	/* Update the समयr on the way out.  We have to pass an increment on
	 * cells_outstanding in the namespace that we are in to the समयr or
	 * the work scheduler.
	 */
	अगर (!purging && next_manage < TIME64_MAX) अणु
		now = kसमय_get_real_seconds();

		अगर (next_manage - now <= 0) अणु
			अगर (queue_work(afs_wq, &net->cells_manager))
				atomic_inc(&net->cells_outstanding);
		पूर्ण अन्यथा अणु
			afs_set_cell_समयr(net, next_manage - now);
		पूर्ण
	पूर्ण

	afs_dec_cells_outstanding(net);
	_leave(" [%d]", atomic_पढ़ो(&net->cells_outstanding));
पूर्ण

/*
 * Purge in-memory cell database.
 */
व्योम afs_cell_purge(काष्ठा afs_net *net)
अणु
	काष्ठा afs_cell *ws;

	_enter("");

	करोwn_ग_लिखो(&net->cells_lock);
	ws = net->ws_cell;
	net->ws_cell = शून्य;
	up_ग_लिखो(&net->cells_lock);
	afs_unuse_cell(net, ws, afs_cell_trace_unuse_ws);

	_debug("del timer");
	अगर (del_समयr_sync(&net->cells_समयr))
		atomic_dec(&net->cells_outstanding);

	_debug("kick mgr");
	afs_queue_cell_manager(net);

	_debug("wait");
	रुको_var_event(&net->cells_outstanding,
		       !atomic_पढ़ो(&net->cells_outstanding));
	_leave("");
पूर्ण
