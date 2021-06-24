<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS fileserver probing
 *
 * Copyright (C) 2018, 2020 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश "afs_fs.h"
#समावेश "internal.h"
#समावेश "protocol_yfs.h"

अटल अचिन्हित पूर्णांक afs_fs_probe_fast_poll_पूर्णांकerval = 30 * HZ;
अटल अचिन्हित पूर्णांक afs_fs_probe_slow_poll_पूर्णांकerval = 5 * 60 * HZ;

/*
 * Start the probe polling समयr.  We have to supply it with an inc on the
 * outstanding server count.
 */
अटल व्योम afs_schedule_fs_probe(काष्ठा afs_net *net,
				  काष्ठा afs_server *server, bool fast)
अणु
	अचिन्हित दीर्घ atj;

	अगर (!net->live)
		वापस;

	atj = server->probed_at;
	atj += fast ? afs_fs_probe_fast_poll_पूर्णांकerval : afs_fs_probe_slow_poll_पूर्णांकerval;

	afs_inc_servers_outstanding(net);
	अगर (समयr_reduce(&net->fs_probe_समयr, atj))
		afs_dec_servers_outstanding(net);
पूर्ण

/*
 * Handle the completion of a set of probes.
 */
अटल व्योम afs_finished_fs_probe(काष्ठा afs_net *net, काष्ठा afs_server *server)
अणु
	bool responded = server->probe.responded;

	ग_लिखो_seqlock(&net->fs_lock);
	अगर (responded) अणु
		list_add_tail(&server->probe_link, &net->fs_probe_slow);
	पूर्ण अन्यथा अणु
		server->rtt = अच_पूर्णांक_उच्च;
		clear_bit(AFS_SERVER_FL_RESPONDING, &server->flags);
		list_add_tail(&server->probe_link, &net->fs_probe_fast);
	पूर्ण
	ग_लिखो_sequnlock(&net->fs_lock);

	afs_schedule_fs_probe(net, server, !responded);
पूर्ण

/*
 * Handle the completion of a probe.
 */
अटल व्योम afs_करोne_one_fs_probe(काष्ठा afs_net *net, काष्ठा afs_server *server)
अणु
	_enter("");

	अगर (atomic_dec_and_test(&server->probe_outstanding))
		afs_finished_fs_probe(net, server);

	wake_up_all(&server->probe_wq);
पूर्ण

/*
 * Handle inability to send a probe due to ENOMEM when trying to allocate a
 * call काष्ठा.
 */
अटल व्योम afs_fs_probe_not_करोne(काष्ठा afs_net *net,
				  काष्ठा afs_server *server,
				  काष्ठा afs_addr_cursor *ac)
अणु
	काष्ठा afs_addr_list *alist = ac->alist;
	अचिन्हित पूर्णांक index = ac->index;

	_enter("");

	trace_afs_io_error(0, -ENOMEM, afs_io_error_fs_probe_fail);
	spin_lock(&server->probe_lock);

	server->probe.local_failure = true;
	अगर (server->probe.error == 0)
		server->probe.error = -ENOMEM;

	set_bit(index, &alist->failed);

	spin_unlock(&server->probe_lock);
	वापस afs_करोne_one_fs_probe(net, server);
पूर्ण

/*
 * Process the result of probing a fileserver.  This is called after successful
 * or failed delivery of an FS.GetCapabilities operation.
 */
व्योम afs_fileserver_probe_result(काष्ठा afs_call *call)
अणु
	काष्ठा afs_addr_list *alist = call->alist;
	काष्ठा afs_server *server = call->server;
	अचिन्हित पूर्णांक index = call->addr_ix;
	अचिन्हित पूर्णांक rtt_us = 0;
	पूर्णांक ret = call->error;

	_enter("%pU,%u", &server->uuid, index);

	spin_lock(&server->probe_lock);

	चयन (ret) अणु
	हाल 0:
		server->probe.error = 0;
		जाओ responded;
	हाल -ECONNABORTED:
		अगर (!server->probe.responded) अणु
			server->probe.पात_code = call->पात_code;
			server->probe.error = ret;
		पूर्ण
		जाओ responded;
	हाल -ENOMEM:
	हाल -ENONET:
		clear_bit(index, &alist->responded);
		server->probe.local_failure = true;
		trace_afs_io_error(call->debug_id, ret, afs_io_error_fs_probe_fail);
		जाओ out;
	हाल -ECONNRESET: /* Responded, but call expired. */
	हाल -ERFKILL:
	हाल -EADDRNOTAVAIL:
	हाल -ENETUNREACH:
	हाल -EHOSTUNREACH:
	हाल -EHOSTDOWN:
	हाल -ECONNREFUSED:
	हाल -ETIMEDOUT:
	हाल -ETIME:
	शेष:
		clear_bit(index, &alist->responded);
		set_bit(index, &alist->failed);
		अगर (!server->probe.responded &&
		    (server->probe.error == 0 ||
		     server->probe.error == -ETIMEDOUT ||
		     server->probe.error == -ETIME))
			server->probe.error = ret;
		trace_afs_io_error(call->debug_id, ret, afs_io_error_fs_probe_fail);
		जाओ out;
	पूर्ण

responded:
	clear_bit(index, &alist->failed);

	अगर (call->service_id == YFS_FS_SERVICE) अणु
		server->probe.is_yfs = true;
		set_bit(AFS_SERVER_FL_IS_YFS, &server->flags);
		alist->addrs[index].srx_service = call->service_id;
	पूर्ण अन्यथा अणु
		server->probe.not_yfs = true;
		अगर (!server->probe.is_yfs) अणु
			clear_bit(AFS_SERVER_FL_IS_YFS, &server->flags);
			alist->addrs[index].srx_service = call->service_id;
		पूर्ण
	पूर्ण

	अगर (rxrpc_kernel_get_srtt(call->net->socket, call->rxcall, &rtt_us) &&
	    rtt_us < server->probe.rtt) अणु
		server->probe.rtt = rtt_us;
		server->rtt = rtt_us;
		alist->preferred = index;
	पूर्ण

	smp_wmb(); /* Set rtt beक्रमe responded. */
	server->probe.responded = true;
	set_bit(index, &alist->responded);
	set_bit(AFS_SERVER_FL_RESPONDING, &server->flags);
out:
	spin_unlock(&server->probe_lock);

	_debug("probe %pU [%u] %pISpc rtt=%u ret=%d",
	       &server->uuid, index, &alist->addrs[index].transport,
	       rtt_us, ret);

	वापस afs_करोne_one_fs_probe(call->net, server);
पूर्ण

/*
 * Probe one or all of a fileserver's addresses to find out the best route and
 * to query its capabilities.
 */
व्योम afs_fs_probe_fileserver(काष्ठा afs_net *net, काष्ठा afs_server *server,
			     काष्ठा key *key, bool all)
अणु
	काष्ठा afs_addr_cursor ac = अणु
		.index = 0,
	पूर्ण;

	_enter("%pU", &server->uuid);

	पढ़ो_lock(&server->fs_lock);
	ac.alist = rcu_dereference_रक्षित(server->addresses,
					     lockdep_is_held(&server->fs_lock));
	afs_get_addrlist(ac.alist);
	पढ़ो_unlock(&server->fs_lock);

	server->probed_at = jअगरfies;
	atomic_set(&server->probe_outstanding, all ? ac.alist->nr_addrs : 1);
	स_रखो(&server->probe, 0, माप(server->probe));
	server->probe.rtt = अच_पूर्णांक_उच्च;

	ac.index = ac.alist->preferred;
	अगर (ac.index < 0 || ac.index >= ac.alist->nr_addrs)
		all = true;

	अगर (all) अणु
		क्रम (ac.index = 0; ac.index < ac.alist->nr_addrs; ac.index++)
			अगर (!afs_fs_get_capabilities(net, server, &ac, key))
				afs_fs_probe_not_करोne(net, server, &ac);
	पूर्ण अन्यथा अणु
		अगर (!afs_fs_get_capabilities(net, server, &ac, key))
			afs_fs_probe_not_करोne(net, server, &ac);
	पूर्ण

	afs_put_addrlist(ac.alist);
पूर्ण

/*
 * Wait क्रम the first as-yet untried fileserver to respond.
 */
पूर्णांक afs_रुको_क्रम_fs_probes(काष्ठा afs_server_list *slist, अचिन्हित दीर्घ untried)
अणु
	काष्ठा रुको_queue_entry *रुकोs;
	काष्ठा afs_server *server;
	अचिन्हित पूर्णांक rtt = अच_पूर्णांक_उच्च, rtt_s;
	bool have_responders = false;
	पूर्णांक pref = -1, i;

	_enter("%u,%lx", slist->nr_servers, untried);

	/* Only रुको क्रम servers that have a probe outstanding. */
	क्रम (i = 0; i < slist->nr_servers; i++) अणु
		अगर (test_bit(i, &untried)) अणु
			server = slist->servers[i].server;
			अगर (!atomic_पढ़ो(&server->probe_outstanding))
				__clear_bit(i, &untried);
			अगर (server->probe.responded)
				have_responders = true;
		पूर्ण
	पूर्ण
	अगर (have_responders || !untried)
		वापस 0;

	रुकोs = kदो_स्मृति(array_size(slist->nr_servers, माप(*रुकोs)), GFP_KERNEL);
	अगर (!रुकोs)
		वापस -ENOMEM;

	क्रम (i = 0; i < slist->nr_servers; i++) अणु
		अगर (test_bit(i, &untried)) अणु
			server = slist->servers[i].server;
			init_रुकोqueue_entry(&रुकोs[i], current);
			add_रुको_queue(&server->probe_wq, &रुकोs[i]);
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		bool still_probing = false;

		set_current_state(TASK_INTERRUPTIBLE);
		क्रम (i = 0; i < slist->nr_servers; i++) अणु
			अगर (test_bit(i, &untried)) अणु
				server = slist->servers[i].server;
				अगर (server->probe.responded)
					जाओ stop;
				अगर (atomic_पढ़ो(&server->probe_outstanding))
					still_probing = true;
			पूर्ण
		पूर्ण

		अगर (!still_probing || संकेत_pending(current))
			जाओ stop;
		schedule();
	पूर्ण

stop:
	set_current_state(TASK_RUNNING);

	क्रम (i = 0; i < slist->nr_servers; i++) अणु
		अगर (test_bit(i, &untried)) अणु
			server = slist->servers[i].server;
			rtt_s = READ_ONCE(server->rtt);
			अगर (test_bit(AFS_SERVER_FL_RESPONDING, &server->flags) &&
			    rtt_s < rtt) अणु
				pref = i;
				rtt = rtt_s;
			पूर्ण

			हटाओ_रुको_queue(&server->probe_wq, &रुकोs[i]);
		पूर्ण
	पूर्ण

	kमुक्त(रुकोs);

	अगर (pref == -1 && संकेत_pending(current))
		वापस -ERESTARTSYS;

	अगर (pref >= 0)
		slist->preferred = pref;
	वापस 0;
पूर्ण

/*
 * Probe समयr.  We have an increment on fs_outstanding that we need to pass
 * aदीर्घ to the work item.
 */
व्योम afs_fs_probe_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा afs_net *net = container_of(समयr, काष्ठा afs_net, fs_probe_समयr);

	अगर (!net->live || !queue_work(afs_wq, &net->fs_prober))
		afs_dec_servers_outstanding(net);
पूर्ण

/*
 * Dispatch a probe to a server.
 */
अटल व्योम afs_dispatch_fs_probe(काष्ठा afs_net *net, काष्ठा afs_server *server, bool all)
	__releases(&net->fs_lock)
अणु
	काष्ठा key *key = शून्य;

	/* We हटाओ it from the queues here - it will be added back to
	 * one of the queues on the completion of the probe.
	 */
	list_del_init(&server->probe_link);

	afs_get_server(server, afs_server_trace_get_probe);
	ग_लिखो_sequnlock(&net->fs_lock);

	afs_fs_probe_fileserver(net, server, key, all);
	afs_put_server(net, server, afs_server_trace_put_probe);
पूर्ण

/*
 * Probe a server immediately without रुकोing क्रम its due समय to come
 * round.  This is used when all of the addresses have been tried.
 */
व्योम afs_probe_fileserver(काष्ठा afs_net *net, काष्ठा afs_server *server)
अणु
	ग_लिखो_seqlock(&net->fs_lock);
	अगर (!list_empty(&server->probe_link))
		वापस afs_dispatch_fs_probe(net, server, true);
	ग_लिखो_sequnlock(&net->fs_lock);
पूर्ण

/*
 * Probe dispatcher to regularly dispatch probes to keep NAT alive.
 */
व्योम afs_fs_probe_dispatcher(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_net *net = container_of(work, काष्ठा afs_net, fs_prober);
	काष्ठा afs_server *fast, *slow, *server;
	अचिन्हित दीर्घ nowj, समयr_at, poll_at;
	bool first_pass = true, set_समयr = false;

	अगर (!net->live)
		वापस;

	_enter("");

	अगर (list_empty(&net->fs_probe_fast) && list_empty(&net->fs_probe_slow)) अणु
		_leave(" [none]");
		वापस;
	पूर्ण

again:
	ग_लिखो_seqlock(&net->fs_lock);

	fast = slow = server = शून्य;
	nowj = jअगरfies;
	समयr_at = nowj + MAX_JIFFY_OFFSET;

	अगर (!list_empty(&net->fs_probe_fast)) अणु
		fast = list_first_entry(&net->fs_probe_fast, काष्ठा afs_server, probe_link);
		poll_at = fast->probed_at + afs_fs_probe_fast_poll_पूर्णांकerval;
		अगर (समय_beक्रमe(nowj, poll_at)) अणु
			समयr_at = poll_at;
			set_समयr = true;
			fast = शून्य;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&net->fs_probe_slow)) अणु
		slow = list_first_entry(&net->fs_probe_slow, काष्ठा afs_server, probe_link);
		poll_at = slow->probed_at + afs_fs_probe_slow_poll_पूर्णांकerval;
		अगर (समय_beक्रमe(nowj, poll_at)) अणु
			अगर (समय_beक्रमe(poll_at, समयr_at))
			    समयr_at = poll_at;
			set_समयr = true;
			slow = शून्य;
		पूर्ण
	पूर्ण

	server = fast ?: slow;
	अगर (server)
		_debug("probe %pU", &server->uuid);

	अगर (server && (first_pass || !need_resched())) अणु
		afs_dispatch_fs_probe(net, server, server == fast);
		first_pass = false;
		जाओ again;
	पूर्ण

	ग_लिखो_sequnlock(&net->fs_lock);

	अगर (server) अणु
		अगर (!queue_work(afs_wq, &net->fs_prober))
			afs_dec_servers_outstanding(net);
		_leave(" [requeue]");
	पूर्ण अन्यथा अगर (set_समयr) अणु
		अगर (समयr_reduce(&net->fs_probe_समयr, समयr_at))
			afs_dec_servers_outstanding(net);
		_leave(" [timer]");
	पूर्ण अन्यथा अणु
		afs_dec_servers_outstanding(net);
		_leave(" [quiesce]");
	पूर्ण
पूर्ण

/*
 * Wait क्रम a probe on a particular fileserver to complete क्रम 2s.
 */
पूर्णांक afs_रुको_क्रम_one_fs_probe(काष्ठा afs_server *server, bool is_पूर्णांकr)
अणु
	काष्ठा रुको_queue_entry रुको;
	अचिन्हित दीर्घ timo = 2 * HZ;

	अगर (atomic_पढ़ो(&server->probe_outstanding) == 0)
		जाओ करोnt_रुको;

	init_रुको_entry(&रुको, 0);
	क्रम (;;) अणु
		prepare_to_रुको_event(&server->probe_wq, &रुको,
				      is_पूर्णांकr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		अगर (timo == 0 ||
		    server->probe.responded ||
		    atomic_पढ़ो(&server->probe_outstanding) == 0 ||
		    (is_पूर्णांकr && संकेत_pending(current)))
			अवरोध;
		timo = schedule_समयout(timo);
	पूर्ण

	finish_रुको(&server->probe_wq, &रुको);

करोnt_रुको:
	अगर (server->probe.responded)
		वापस 0;
	अगर (is_पूर्णांकr && संकेत_pending(current))
		वापस -ERESTARTSYS;
	अगर (timo == 0)
		वापस -ETIME;
	वापस -EDESTADDRREQ;
पूर्ण

/*
 * Clean up the probing when the namespace is समाप्तed off.
 */
व्योम afs_fs_probe_cleanup(काष्ठा afs_net *net)
अणु
	अगर (del_समयr_sync(&net->fs_probe_समयr))
		afs_dec_servers_outstanding(net);
पूर्ण
