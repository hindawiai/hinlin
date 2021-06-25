<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Handle vlserver selection and rotation.
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "internal.h"
#समावेश "afs_vl.h"

/*
 * Begin an operation on a volume location server.
 */
bool afs_begin_vlserver_operation(काष्ठा afs_vl_cursor *vc, काष्ठा afs_cell *cell,
				  काष्ठा key *key)
अणु
	स_रखो(vc, 0, माप(*vc));
	vc->cell = cell;
	vc->key = key;
	vc->error = -EDESTADDRREQ;
	vc->ac.error = लघु_उच्च;

	अगर (संकेत_pending(current)) अणु
		vc->error = -EINTR;
		vc->flags |= AFS_VL_CURSOR_STOP;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Begin iteration through a server list, starting with the last used server अगर
 * possible, or the last recorded good server अगर not.
 */
अटल bool afs_start_vl_iteration(काष्ठा afs_vl_cursor *vc)
अणु
	काष्ठा afs_cell *cell = vc->cell;
	अचिन्हित पूर्णांक dns_lookup_count;

	अगर (cell->dns_source == DNS_RECORD_UNAVAILABLE ||
	    cell->dns_expiry <= kसमय_get_real_seconds()) अणु
		dns_lookup_count = smp_load_acquire(&cell->dns_lookup_count);
		set_bit(AFS_CELL_FL_DO_LOOKUP, &cell->flags);
		afs_queue_cell(cell, afs_cell_trace_get_queue_dns);

		अगर (cell->dns_source == DNS_RECORD_UNAVAILABLE) अणु
			अगर (रुको_var_event_पूर्णांकerruptible(
				    &cell->dns_lookup_count,
				    smp_load_acquire(&cell->dns_lookup_count)
				    != dns_lookup_count) < 0) अणु
				vc->error = -ERESTARTSYS;
				वापस false;
			पूर्ण
		पूर्ण

		/* Status load is ordered after lookup counter load */
		अगर (cell->dns_source == DNS_RECORD_UNAVAILABLE) अणु
			vc->error = -EDESTADDRREQ;
			वापस false;
		पूर्ण
	पूर्ण

	पढ़ो_lock(&cell->vl_servers_lock);
	vc->server_list = afs_get_vlserverlist(
		rcu_dereference_रक्षित(cell->vl_servers,
					  lockdep_is_held(&cell->vl_servers_lock)));
	पढ़ो_unlock(&cell->vl_servers_lock);
	अगर (!vc->server_list->nr_servers)
		वापस false;

	vc->untried = (1UL << vc->server_list->nr_servers) - 1;
	vc->index = -1;
	वापस true;
पूर्ण

/*
 * Select the vlserver to use.  May be called multiple बार to rotate
 * through the vlservers.
 */
bool afs_select_vlserver(काष्ठा afs_vl_cursor *vc)
अणु
	काष्ठा afs_addr_list *alist;
	काष्ठा afs_vlserver *vlserver;
	काष्ठा afs_error e;
	u32 rtt;
	पूर्णांक error = vc->ac.error, i;

	_enter("%lx[%d],%lx[%d],%d,%d",
	       vc->untried, vc->index,
	       vc->ac.tried, vc->ac.index,
	       error, vc->ac.पात_code);

	अगर (vc->flags & AFS_VL_CURSOR_STOP) अणु
		_leave(" = f [stopped]");
		वापस false;
	पूर्ण

	vc->nr_iterations++;

	/* Evaluate the result of the previous operation, अगर there was one. */
	चयन (error) अणु
	हाल लघु_उच्च:
		जाओ start;

	शेष:
	हाल 0:
		/* Success or local failure.  Stop. */
		vc->error = error;
		vc->flags |= AFS_VL_CURSOR_STOP;
		_leave(" = f [okay/local %d]", vc->ac.error);
		वापस false;

	हाल -ECONNABORTED:
		/* The far side rejected the operation on some grounds.  This
		 * might involve the server being busy or the volume having been moved.
		 */
		चयन (vc->ac.पात_code) अणु
		हाल AFSVL_IO:
		हाल AFSVL_BADVOLOPER:
		हाल AFSVL_NOMEM:
			/* The server went weird. */
			vc->error = -EREMOTEIO;
			//ग_लिखो_lock(&vc->cell->vl_servers_lock);
			//vc->server_list->weird_mask |= 1 << vc->index;
			//ग_लिखो_unlock(&vc->cell->vl_servers_lock);
			जाओ next_server;

		शेष:
			vc->error = afs_पात_to_error(vc->ac.पात_code);
			जाओ failed;
		पूर्ण

	हाल -ERFKILL:
	हाल -EADDRNOTAVAIL:
	हाल -ENETUNREACH:
	हाल -EHOSTUNREACH:
	हाल -EHOSTDOWN:
	हाल -ECONNREFUSED:
	हाल -ETIMEDOUT:
	हाल -ETIME:
		_debug("no conn %d", error);
		vc->error = error;
		जाओ iterate_address;

	हाल -ECONNRESET:
		_debug("call reset");
		vc->error = error;
		vc->flags |= AFS_VL_CURSOR_RETRY;
		जाओ next_server;

	हाल -EOPNOTSUPP:
		_debug("notsupp");
		जाओ next_server;
	पूर्ण

restart_from_beginning:
	_debug("restart");
	afs_end_cursor(&vc->ac);
	afs_put_vlserverlist(vc->cell->net, vc->server_list);
	vc->server_list = शून्य;
	अगर (vc->flags & AFS_VL_CURSOR_RETRIED)
		जाओ failed;
	vc->flags |= AFS_VL_CURSOR_RETRIED;
start:
	_debug("start");

	अगर (!afs_start_vl_iteration(vc))
		जाओ failed;

	error = afs_send_vl_probes(vc->cell->net, vc->key, vc->server_list);
	अगर (error < 0)
		जाओ failed_set_error;

pick_server:
	_debug("pick [%lx]", vc->untried);

	error = afs_रुको_क्रम_vl_probes(vc->server_list, vc->untried);
	अगर (error < 0)
		जाओ failed_set_error;

	/* Pick the untried server with the lowest RTT. */
	vc->index = vc->server_list->preferred;
	अगर (test_bit(vc->index, &vc->untried))
		जाओ selected_server;

	vc->index = -1;
	rtt = U32_MAX;
	क्रम (i = 0; i < vc->server_list->nr_servers; i++) अणु
		काष्ठा afs_vlserver *s = vc->server_list->servers[i].server;

		अगर (!test_bit(i, &vc->untried) ||
		    !test_bit(AFS_VLSERVER_FL_RESPONDING, &s->flags))
			जारी;
		अगर (s->probe.rtt < rtt) अणु
			vc->index = i;
			rtt = s->probe.rtt;
		पूर्ण
	पूर्ण

	अगर (vc->index == -1)
		जाओ no_more_servers;

selected_server:
	_debug("use %d", vc->index);
	__clear_bit(vc->index, &vc->untried);

	/* We're starting on a dअगरferent vlserver from the list.  We need to
	 * check it, find its address list and probe its capabilities beक्रमe we
	 * use it.
	 */
	ASSERTCMP(vc->ac.alist, ==, शून्य);
	vlserver = vc->server_list->servers[vc->index].server;
	vc->server = vlserver;

	_debug("USING VLSERVER: %s", vlserver->name);

	पढ़ो_lock(&vlserver->lock);
	alist = rcu_dereference_रक्षित(vlserver->addresses,
					  lockdep_is_held(&vlserver->lock));
	afs_get_addrlist(alist);
	पढ़ो_unlock(&vlserver->lock);

	स_रखो(&vc->ac, 0, माप(vc->ac));

	अगर (!vc->ac.alist)
		vc->ac.alist = alist;
	अन्यथा
		afs_put_addrlist(alist);

	vc->ac.index = -1;

iterate_address:
	ASSERT(vc->ac.alist);
	/* Iterate over the current server's address list to try and find an
	 * address on which it will respond to us.
	 */
	अगर (!afs_iterate_addresses(&vc->ac))
		जाओ next_server;

	_debug("VL address %d/%d", vc->ac.index, vc->ac.alist->nr_addrs);

	_leave(" = t %pISpc", &vc->ac.alist->addrs[vc->ac.index].transport);
	वापस true;

next_server:
	_debug("next");
	afs_end_cursor(&vc->ac);
	जाओ pick_server;

no_more_servers:
	/* That's all the servers poked to no good effect.  Try again अगर some
	 * of them were busy.
	 */
	अगर (vc->flags & AFS_VL_CURSOR_RETRY)
		जाओ restart_from_beginning;

	e.error = -EDESTADDRREQ;
	e.responded = false;
	क्रम (i = 0; i < vc->server_list->nr_servers; i++) अणु
		काष्ठा afs_vlserver *s = vc->server_list->servers[i].server;

		अगर (test_bit(AFS_VLSERVER_FL_RESPONDING, &s->flags))
			e.responded = true;
		afs_prioritise_error(&e, READ_ONCE(s->probe.error),
				     s->probe.पात_code);
	पूर्ण

	error = e.error;

failed_set_error:
	vc->error = error;
failed:
	vc->flags |= AFS_VL_CURSOR_STOP;
	afs_end_cursor(&vc->ac);
	_leave(" = f [failed %d]", vc->error);
	वापस false;
पूर्ण

/*
 * Dump cursor state in the हाल of the error being EDESTADDRREQ.
 */
अटल व्योम afs_vl_dump_edestaddrreq(स्थिर काष्ठा afs_vl_cursor *vc)
अणु
	अटल पूर्णांक count;
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_AFS_DEBUG_CURSOR) || count > 3)
		वापस;
	count++;

	rcu_पढ़ो_lock();
	pr_notice("EDESTADDR occurred\n");
	pr_notice("VC: ut=%lx ix=%u ni=%hu fl=%hx err=%hd\n",
		  vc->untried, vc->index, vc->nr_iterations, vc->flags, vc->error);

	अगर (vc->server_list) अणु
		स्थिर काष्ठा afs_vlserver_list *sl = vc->server_list;
		pr_notice("VC: SL nr=%u ix=%u\n",
			  sl->nr_servers, sl->index);
		क्रम (i = 0; i < sl->nr_servers; i++) अणु
			स्थिर काष्ठा afs_vlserver *s = sl->servers[i].server;
			pr_notice("VC: server %s+%hu fl=%lx E=%hd\n",
				  s->name, s->port, s->flags, s->probe.error);
			अगर (s->addresses) अणु
				स्थिर काष्ठा afs_addr_list *a =
					rcu_dereference(s->addresses);
				pr_notice("VC:  - nr=%u/%u/%u pf=%u\n",
					  a->nr_ipv4, a->nr_addrs, a->max_addrs,
					  a->preferred);
				pr_notice("VC:  - R=%lx F=%lx\n",
					  a->responded, a->failed);
				अगर (a == vc->ac.alist)
					pr_notice("VC:  - current\n");
			पूर्ण
		पूर्ण
	पूर्ण

	pr_notice("AC: t=%lx ax=%u ac=%d er=%d r=%u ni=%u\n",
		  vc->ac.tried, vc->ac.index, vc->ac.पात_code, vc->ac.error,
		  vc->ac.responded, vc->ac.nr_iterations);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Tidy up a volume location server cursor and unlock the vnode.
 */
पूर्णांक afs_end_vlserver_operation(काष्ठा afs_vl_cursor *vc)
अणु
	काष्ठा afs_net *net = vc->cell->net;

	अगर (vc->error == -EDESTADDRREQ ||
	    vc->error == -EADDRNOTAVAIL ||
	    vc->error == -ENETUNREACH ||
	    vc->error == -EHOSTUNREACH)
		afs_vl_dump_edestaddrreq(vc);

	afs_end_cursor(&vc->ac);
	afs_put_vlserverlist(net, vc->server_list);

	अगर (vc->error == -ECONNABORTED)
		vc->error = afs_पात_to_error(vc->ac.पात_code);

	वापस vc->error;
पूर्ण
