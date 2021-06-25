<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS vlserver probing
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश "afs_fs.h"
#समावेश "internal.h"
#समावेश "protocol_yfs.h"


/*
 * Handle the completion of a set of probes.
 */
अटल व्योम afs_finished_vl_probe(काष्ठा afs_vlserver *server)
अणु
	अगर (!(server->probe.flags & AFS_VLSERVER_PROBE_RESPONDED)) अणु
		server->rtt = अच_पूर्णांक_उच्च;
		clear_bit(AFS_VLSERVER_FL_RESPONDING, &server->flags);
	पूर्ण

	clear_bit_unlock(AFS_VLSERVER_FL_PROBING, &server->flags);
	wake_up_bit(&server->flags, AFS_VLSERVER_FL_PROBING);
पूर्ण

/*
 * Handle the completion of a probe RPC call.
 */
अटल व्योम afs_करोne_one_vl_probe(काष्ठा afs_vlserver *server, bool wake_up)
अणु
	अगर (atomic_dec_and_test(&server->probe_outstanding)) अणु
		afs_finished_vl_probe(server);
		wake_up = true;
	पूर्ण

	अगर (wake_up)
		wake_up_all(&server->probe_wq);
पूर्ण

/*
 * Process the result of probing a vlserver.  This is called after successful
 * or failed delivery of an VL.GetCapabilities operation.
 */
व्योम afs_vlserver_probe_result(काष्ठा afs_call *call)
अणु
	काष्ठा afs_addr_list *alist = call->alist;
	काष्ठा afs_vlserver *server = call->vlserver;
	अचिन्हित पूर्णांक server_index = call->server_index;
	अचिन्हित पूर्णांक rtt_us = 0;
	अचिन्हित पूर्णांक index = call->addr_ix;
	bool have_result = false;
	पूर्णांक ret = call->error;

	_enter("%s,%u,%u,%d,%d", server->name, server_index, index, ret, call->पात_code);

	spin_lock(&server->probe_lock);

	चयन (ret) अणु
	हाल 0:
		server->probe.error = 0;
		जाओ responded;
	हाल -ECONNABORTED:
		अगर (!(server->probe.flags & AFS_VLSERVER_PROBE_RESPONDED)) अणु
			server->probe.पात_code = call->पात_code;
			server->probe.error = ret;
		पूर्ण
		जाओ responded;
	हाल -ENOMEM:
	हाल -ENONET:
	हाल -EKEYEXPIRED:
	हाल -EKEYREVOKED:
	हाल -EKEYREJECTED:
		server->probe.flags |= AFS_VLSERVER_PROBE_LOCAL_FAILURE;
		अगर (server->probe.error == 0)
			server->probe.error = ret;
		trace_afs_io_error(call->debug_id, ret, afs_io_error_vl_probe_fail);
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
		अगर (!(server->probe.flags & AFS_VLSERVER_PROBE_RESPONDED) &&
		    (server->probe.error == 0 ||
		     server->probe.error == -ETIMEDOUT ||
		     server->probe.error == -ETIME))
			server->probe.error = ret;
		trace_afs_io_error(call->debug_id, ret, afs_io_error_vl_probe_fail);
		जाओ out;
	पूर्ण

responded:
	set_bit(index, &alist->responded);
	clear_bit(index, &alist->failed);

	अगर (call->service_id == YFS_VL_SERVICE) अणु
		server->probe.flags |= AFS_VLSERVER_PROBE_IS_YFS;
		set_bit(AFS_VLSERVER_FL_IS_YFS, &server->flags);
		alist->addrs[index].srx_service = call->service_id;
	पूर्ण अन्यथा अणु
		server->probe.flags |= AFS_VLSERVER_PROBE_NOT_YFS;
		अगर (!(server->probe.flags & AFS_VLSERVER_PROBE_IS_YFS)) अणु
			clear_bit(AFS_VLSERVER_FL_IS_YFS, &server->flags);
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
	server->probe.flags |= AFS_VLSERVER_PROBE_RESPONDED;
	set_bit(AFS_VLSERVER_FL_PROBED, &server->flags);
	set_bit(AFS_VLSERVER_FL_RESPONDING, &server->flags);
	have_result = true;
out:
	spin_unlock(&server->probe_lock);

	_debug("probe [%u][%u] %pISpc rtt=%u ret=%d",
	       server_index, index, &alist->addrs[index].transport, rtt_us, ret);

	afs_करोne_one_vl_probe(server, have_result);
पूर्ण

/*
 * Probe all of a vlserver's addresses to find out the best route and to
 * query its capabilities.
 */
अटल bool afs_करो_probe_vlserver(काष्ठा afs_net *net,
				  काष्ठा afs_vlserver *server,
				  काष्ठा key *key,
				  अचिन्हित पूर्णांक server_index,
				  काष्ठा afs_error *_e)
अणु
	काष्ठा afs_addr_cursor ac = अणु
		.index = 0,
	पूर्ण;
	काष्ठा afs_call *call;
	bool in_progress = false;

	_enter("%s", server->name);

	पढ़ो_lock(&server->lock);
	ac.alist = rcu_dereference_रक्षित(server->addresses,
					     lockdep_is_held(&server->lock));
	पढ़ो_unlock(&server->lock);

	atomic_set(&server->probe_outstanding, ac.alist->nr_addrs);
	स_रखो(&server->probe, 0, माप(server->probe));
	server->probe.rtt = अच_पूर्णांक_उच्च;

	क्रम (ac.index = 0; ac.index < ac.alist->nr_addrs; ac.index++) अणु
		call = afs_vl_get_capabilities(net, &ac, key, server,
					       server_index);
		अगर (!IS_ERR(call)) अणु
			afs_put_call(call);
			in_progress = true;
		पूर्ण अन्यथा अणु
			afs_prioritise_error(_e, PTR_ERR(call), ac.पात_code);
			afs_करोne_one_vl_probe(server, false);
		पूर्ण
	पूर्ण

	वापस in_progress;
पूर्ण

/*
 * Send off probes to all unprobed servers.
 */
पूर्णांक afs_send_vl_probes(काष्ठा afs_net *net, काष्ठा key *key,
		       काष्ठा afs_vlserver_list *vllist)
अणु
	काष्ठा afs_vlserver *server;
	काष्ठा afs_error e;
	bool in_progress = false;
	पूर्णांक i;

	e.error = 0;
	e.responded = false;
	क्रम (i = 0; i < vllist->nr_servers; i++) अणु
		server = vllist->servers[i].server;
		अगर (test_bit(AFS_VLSERVER_FL_PROBED, &server->flags))
			जारी;

		अगर (!test_and_set_bit_lock(AFS_VLSERVER_FL_PROBING, &server->flags) &&
		    afs_करो_probe_vlserver(net, server, key, i, &e))
			in_progress = true;
	पूर्ण

	वापस in_progress ? 0 : e.error;
पूर्ण

/*
 * Wait क्रम the first as-yet untried server to respond.
 */
पूर्णांक afs_रुको_क्रम_vl_probes(काष्ठा afs_vlserver_list *vllist,
			   अचिन्हित दीर्घ untried)
अणु
	काष्ठा रुको_queue_entry *रुकोs;
	काष्ठा afs_vlserver *server;
	अचिन्हित पूर्णांक rtt = अच_पूर्णांक_उच्च, rtt_s;
	bool have_responders = false;
	पूर्णांक pref = -1, i;

	_enter("%u,%lx", vllist->nr_servers, untried);

	/* Only रुको क्रम servers that have a probe outstanding. */
	क्रम (i = 0; i < vllist->nr_servers; i++) अणु
		अगर (test_bit(i, &untried)) अणु
			server = vllist->servers[i].server;
			अगर (!test_bit(AFS_VLSERVER_FL_PROBING, &server->flags))
				__clear_bit(i, &untried);
			अगर (server->probe.flags & AFS_VLSERVER_PROBE_RESPONDED)
				have_responders = true;
		पूर्ण
	पूर्ण
	अगर (have_responders || !untried)
		वापस 0;

	रुकोs = kदो_स्मृति(array_size(vllist->nr_servers, माप(*रुकोs)), GFP_KERNEL);
	अगर (!रुकोs)
		वापस -ENOMEM;

	क्रम (i = 0; i < vllist->nr_servers; i++) अणु
		अगर (test_bit(i, &untried)) अणु
			server = vllist->servers[i].server;
			init_रुकोqueue_entry(&रुकोs[i], current);
			add_रुको_queue(&server->probe_wq, &रुकोs[i]);
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		bool still_probing = false;

		set_current_state(TASK_INTERRUPTIBLE);
		क्रम (i = 0; i < vllist->nr_servers; i++) अणु
			अगर (test_bit(i, &untried)) अणु
				server = vllist->servers[i].server;
				अगर (server->probe.flags & AFS_VLSERVER_PROBE_RESPONDED)
					जाओ stop;
				अगर (test_bit(AFS_VLSERVER_FL_PROBING, &server->flags))
					still_probing = true;
			पूर्ण
		पूर्ण

		अगर (!still_probing || संकेत_pending(current))
			जाओ stop;
		schedule();
	पूर्ण

stop:
	set_current_state(TASK_RUNNING);

	क्रम (i = 0; i < vllist->nr_servers; i++) अणु
		अगर (test_bit(i, &untried)) अणु
			server = vllist->servers[i].server;
			rtt_s = READ_ONCE(server->rtt);
			अगर (test_bit(AFS_VLSERVER_FL_RESPONDING, &server->flags) &&
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
		vllist->preferred = pref;

	_leave(" = 0 [%u]", pref);
	वापस 0;
पूर्ण
