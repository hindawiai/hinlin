<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Handle fileserver selection and rotation.
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "internal.h"
#समावेश "afs_fs.h"

/*
 * Begin iteration through a server list, starting with the vnode's last used
 * server अगर possible, or the last recorded good server अगर not.
 */
अटल bool afs_start_fs_iteration(काष्ठा afs_operation *op,
				   काष्ठा afs_vnode *vnode)
अणु
	काष्ठा afs_server *server;
	व्योम *cb_server;
	पूर्णांक i;

	पढ़ो_lock(&op->volume->servers_lock);
	op->server_list = afs_get_serverlist(
		rcu_dereference_रक्षित(op->volume->servers,
					  lockdep_is_held(&op->volume->servers_lock)));
	पढ़ो_unlock(&op->volume->servers_lock);

	op->untried = (1UL << op->server_list->nr_servers) - 1;
	op->index = READ_ONCE(op->server_list->preferred);

	cb_server = vnode->cb_server;
	अगर (cb_server) अणु
		/* See अगर the vnode's preferred record is still available */
		क्रम (i = 0; i < op->server_list->nr_servers; i++) अणु
			server = op->server_list->servers[i].server;
			अगर (server == cb_server) अणु
				op->index = i;
				जाओ found_पूर्णांकerest;
			पूर्ण
		पूर्ण

		/* If we have a lock outstanding on a server that's no दीर्घer
		 * serving this vnode, then we can't चयन to another server
		 * and have to वापस an error.
		 */
		अगर (op->flags & AFS_OPERATION_CUR_ONLY) अणु
			op->error = -ESTALE;
			वापस false;
		पूर्ण

		/* Note that the callback promise is effectively broken */
		ग_लिखो_seqlock(&vnode->cb_lock);
		ASSERTCMP(cb_server, ==, vnode->cb_server);
		vnode->cb_server = शून्य;
		अगर (test_and_clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags))
			vnode->cb_अवरोध++;
		ग_लिखो_sequnlock(&vnode->cb_lock);
	पूर्ण

found_पूर्णांकerest:
	वापस true;
पूर्ण

/*
 * Post volume busy note.
 */
अटल व्योम afs_busy(काष्ठा afs_volume *volume, u32 पात_code)
अणु
	स्थिर अक्षर *m;

	चयन (पात_code) अणु
	हाल VOFFLINE:		m = "offline";		अवरोध;
	हाल VRESTARTING:	m = "restarting";	अवरोध;
	हाल VSALVAGING:	m = "being salvaged";	अवरोध;
	शेष:		m = "busy";		अवरोध;
	पूर्ण

	pr_notice("kAFS: Volume %llu '%s' is %s\n", volume->vid, volume->name, m);
पूर्ण

/*
 * Sleep and retry the operation to the same fileserver.
 */
अटल bool afs_sleep_and_retry(काष्ठा afs_operation *op)
अणु
	अगर (!(op->flags & AFS_OPERATION_UNINTR)) अणु
		msleep_पूर्णांकerruptible(1000);
		अगर (संकेत_pending(current)) अणु
			op->error = -ERESTARTSYS;
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		msleep(1000);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Select the fileserver to use.  May be called multiple बार to rotate
 * through the fileservers.
 */
bool afs_select_fileserver(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_addr_list *alist;
	काष्ठा afs_server *server;
	काष्ठा afs_vnode *vnode = op->file[0].vnode;
	काष्ठा afs_error e;
	u32 rtt;
	पूर्णांक error = op->ac.error, i;

	_enter("%lx[%d],%lx[%d],%d,%d",
	       op->untried, op->index,
	       op->ac.tried, op->ac.index,
	       error, op->ac.पात_code);

	अगर (op->flags & AFS_OPERATION_STOP) अणु
		_leave(" = f [stopped]");
		वापस false;
	पूर्ण

	op->nr_iterations++;

	/* Evaluate the result of the previous operation, अगर there was one. */
	चयन (error) अणु
	हाल लघु_उच्च:
		जाओ start;

	हाल 0:
	शेष:
		/* Success or local failure.  Stop. */
		op->error = error;
		op->flags |= AFS_OPERATION_STOP;
		_leave(" = f [okay/local %d]", error);
		वापस false;

	हाल -ECONNABORTED:
		/* The far side rejected the operation on some grounds.  This
		 * might involve the server being busy or the volume having been moved.
		 */
		चयन (op->ac.पात_code) अणु
		हाल VNOVOL:
			/* This fileserver करोesn't know about the volume.
			 * - May indicate that the VL is wrong - retry once and compare
			 *   the results.
			 * - May indicate that the fileserver couldn't attach to the vol.
			 */
			अगर (op->flags & AFS_OPERATION_VNOVOL) अणु
				op->error = -EREMOTEIO;
				जाओ next_server;
			पूर्ण

			ग_लिखो_lock(&op->volume->servers_lock);
			op->server_list->vnovol_mask |= 1 << op->index;
			ग_लिखो_unlock(&op->volume->servers_lock);

			set_bit(AFS_VOLUME_NEEDS_UPDATE, &op->volume->flags);
			error = afs_check_volume_status(op->volume, op);
			अगर (error < 0)
				जाओ failed_set_error;

			अगर (test_bit(AFS_VOLUME_DELETED, &op->volume->flags)) अणु
				op->error = -ENOMEDIUM;
				जाओ failed;
			पूर्ण

			/* If the server list didn't change, then assume that
			 * it's the fileserver having trouble.
			 */
			अगर (rcu_access_poपूर्णांकer(op->volume->servers) == op->server_list) अणु
				op->error = -EREMOTEIO;
				जाओ next_server;
			पूर्ण

			/* Try again */
			op->flags |= AFS_OPERATION_VNOVOL;
			_leave(" = t [vnovol]");
			वापस true;

		हाल VSALVAGE: /* TODO: Should this वापस an error or iterate? */
		हाल VVOLEXISTS:
		हाल VNOSERVICE:
		हाल VONLINE:
		हाल VDISKFULL:
		हाल VOVERQUOTA:
			op->error = afs_पात_to_error(op->ac.पात_code);
			जाओ next_server;

		हाल VOFFLINE:
			अगर (!test_and_set_bit(AFS_VOLUME_OFFLINE, &op->volume->flags)) अणु
				afs_busy(op->volume, op->ac.पात_code);
				clear_bit(AFS_VOLUME_BUSY, &op->volume->flags);
			पूर्ण
			अगर (op->flags & AFS_OPERATION_NO_VSLEEP) अणु
				op->error = -EADV;
				जाओ failed;
			पूर्ण
			अगर (op->flags & AFS_OPERATION_CUR_ONLY) अणु
				op->error = -ESTALE;
				जाओ failed;
			पूर्ण
			जाओ busy;

		हाल VSALVAGING:
		हाल VRESTARTING:
		हाल VBUSY:
			/* Retry after going round all the servers unless we
			 * have a file lock we need to मुख्यtain.
			 */
			अगर (op->flags & AFS_OPERATION_NO_VSLEEP) अणु
				op->error = -EBUSY;
				जाओ failed;
			पूर्ण
			अगर (!test_and_set_bit(AFS_VOLUME_BUSY, &op->volume->flags)) अणु
				afs_busy(op->volume, op->ac.पात_code);
				clear_bit(AFS_VOLUME_OFFLINE, &op->volume->flags);
			पूर्ण
		busy:
			अगर (op->flags & AFS_OPERATION_CUR_ONLY) अणु
				अगर (!afs_sleep_and_retry(op))
					जाओ failed;

				 /* Retry with same server & address */
				_leave(" = t [vbusy]");
				वापस true;
			पूर्ण

			op->flags |= AFS_OPERATION_VBUSY;
			जाओ next_server;

		हाल VMOVED:
			/* The volume migrated to another server.  We consider
			 * consider all locks and callbacks broken and request
			 * an update from the VLDB.
			 *
			 * We also limit the number of VMOVED hops we will
			 * honour, just in हाल someone sets up a loop.
			 */
			अगर (op->flags & AFS_OPERATION_VMOVED) अणु
				op->error = -EREMOTEIO;
				जाओ failed;
			पूर्ण
			op->flags |= AFS_OPERATION_VMOVED;

			set_bit(AFS_VOLUME_WAIT, &op->volume->flags);
			set_bit(AFS_VOLUME_NEEDS_UPDATE, &op->volume->flags);
			error = afs_check_volume_status(op->volume, op);
			अगर (error < 0)
				जाओ failed_set_error;

			/* If the server list didn't change, then the VLDB is
			 * out of sync with the fileservers.  This is hopefully
			 * a temporary condition, however, so we करोn't want to
			 * permanently block access to the file.
			 *
			 * TODO: Try other fileservers अगर we can.
			 *
			 * TODO: Retry a few बार with sleeps.
			 */
			अगर (rcu_access_poपूर्णांकer(op->volume->servers) == op->server_list) अणु
				op->error = -ENOMEDIUM;
				जाओ failed;
			पूर्ण

			जाओ restart_from_beginning;

		शेष:
			clear_bit(AFS_VOLUME_OFFLINE, &op->volume->flags);
			clear_bit(AFS_VOLUME_BUSY, &op->volume->flags);
			op->error = afs_पात_to_error(op->ac.पात_code);
			जाओ failed;
		पूर्ण

	हाल -ETIMEDOUT:
	हाल -ETIME:
		अगर (op->error != -EDESTADDRREQ)
			जाओ iterate_address;
		fallthrough;
	हाल -ERFKILL:
	हाल -EADDRNOTAVAIL:
	हाल -ENETUNREACH:
	हाल -EHOSTUNREACH:
	हाल -EHOSTDOWN:
	हाल -ECONNREFUSED:
		_debug("no conn");
		op->error = error;
		जाओ iterate_address;

	हाल -ECONNRESET:
		_debug("call reset");
		op->error = error;
		जाओ failed;
	पूर्ण

restart_from_beginning:
	_debug("restart");
	afs_end_cursor(&op->ac);
	op->server = शून्य;
	afs_put_serverlist(op->net, op->server_list);
	op->server_list = शून्य;
start:
	_debug("start");
	/* See अगर we need to करो an update of the volume record.  Note that the
	 * volume may have moved or even have been deleted.
	 */
	error = afs_check_volume_status(op->volume, op);
	अगर (error < 0)
		जाओ failed_set_error;

	अगर (!afs_start_fs_iteration(op, vnode))
		जाओ failed;

	_debug("__ VOL %llx __", op->volume->vid);

pick_server:
	_debug("pick [%lx]", op->untried);

	error = afs_रुको_क्रम_fs_probes(op->server_list, op->untried);
	अगर (error < 0)
		जाओ failed_set_error;

	/* Pick the untried server with the lowest RTT.  If we have outstanding
	 * callbacks, we stick with the server we're alपढ़ोy using अगर we can.
	 */
	अगर (op->server) अणु
		_debug("server %u", op->index);
		अगर (test_bit(op->index, &op->untried))
			जाओ selected_server;
		op->server = शून्य;
		_debug("no server");
	पूर्ण

	op->index = -1;
	rtt = U32_MAX;
	क्रम (i = 0; i < op->server_list->nr_servers; i++) अणु
		काष्ठा afs_server *s = op->server_list->servers[i].server;

		अगर (!test_bit(i, &op->untried) ||
		    !test_bit(AFS_SERVER_FL_RESPONDING, &s->flags))
			जारी;
		अगर (s->probe.rtt < rtt) अणु
			op->index = i;
			rtt = s->probe.rtt;
		पूर्ण
	पूर्ण

	अगर (op->index == -1)
		जाओ no_more_servers;

selected_server:
	_debug("use %d", op->index);
	__clear_bit(op->index, &op->untried);

	/* We're starting on a dअगरferent fileserver from the list.  We need to
	 * check it, create a callback पूर्णांकercept, find its address list and
	 * probe its capabilities beक्रमe we use it.
	 */
	ASSERTCMP(op->ac.alist, ==, शून्य);
	server = op->server_list->servers[op->index].server;

	अगर (!afs_check_server_record(op, server))
		जाओ failed;

	_debug("USING SERVER: %pU", &server->uuid);

	op->flags |= AFS_OPERATION_RETRY_SERVER;
	op->server = server;
	अगर (vnode->cb_server != server) अणु
		vnode->cb_server = server;
		vnode->cb_s_अवरोध = server->cb_s_अवरोध;
		vnode->cb_v_अवरोध = vnode->volume->cb_v_अवरोध;
		clear_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);
	पूर्ण

	पढ़ो_lock(&server->fs_lock);
	alist = rcu_dereference_रक्षित(server->addresses,
					  lockdep_is_held(&server->fs_lock));
	afs_get_addrlist(alist);
	पढ़ो_unlock(&server->fs_lock);

retry_server:
	स_रखो(&op->ac, 0, माप(op->ac));

	अगर (!op->ac.alist)
		op->ac.alist = alist;
	अन्यथा
		afs_put_addrlist(alist);

	op->ac.index = -1;

iterate_address:
	ASSERT(op->ac.alist);
	/* Iterate over the current server's address list to try and find an
	 * address on which it will respond to us.
	 */
	अगर (!afs_iterate_addresses(&op->ac))
		जाओ out_of_addresses;

	_debug("address [%u] %u/%u %pISp",
	       op->index, op->ac.index, op->ac.alist->nr_addrs,
	       &op->ac.alist->addrs[op->ac.index].transport);

	_leave(" = t");
	वापस true;

out_of_addresses:
	/* We've now had a failure to respond on all of a server's addresses -
	 * immediately probe them again and consider retrying the server.
	 */
	afs_probe_fileserver(op->net, op->server);
	अगर (op->flags & AFS_OPERATION_RETRY_SERVER) अणु
		alist = op->ac.alist;
		error = afs_रुको_क्रम_one_fs_probe(
			op->server, !(op->flags & AFS_OPERATION_UNINTR));
		चयन (error) अणु
		हाल 0:
			op->flags &= ~AFS_OPERATION_RETRY_SERVER;
			जाओ retry_server;
		हाल -ERESTARTSYS:
			जाओ failed_set_error;
		हाल -ETIME:
		हाल -EDESTADDRREQ:
			जाओ next_server;
		पूर्ण
	पूर्ण

next_server:
	_debug("next");
	afs_end_cursor(&op->ac);
	जाओ pick_server;

no_more_servers:
	/* That's all the servers poked to no good effect.  Try again अगर some
	 * of them were busy.
	 */
	अगर (op->flags & AFS_OPERATION_VBUSY)
		जाओ restart_from_beginning;

	e.error = -EDESTADDRREQ;
	e.responded = false;
	क्रम (i = 0; i < op->server_list->nr_servers; i++) अणु
		काष्ठा afs_server *s = op->server_list->servers[i].server;

		afs_prioritise_error(&e, READ_ONCE(s->probe.error),
				     s->probe.पात_code);
	पूर्ण

	error = e.error;

failed_set_error:
	op->error = error;
failed:
	op->flags |= AFS_OPERATION_STOP;
	afs_end_cursor(&op->ac);
	_leave(" = f [failed %d]", op->error);
	वापस false;
पूर्ण

/*
 * Dump cursor state in the हाल of the error being EDESTADDRREQ.
 */
व्योम afs_dump_edestaddrreq(स्थिर काष्ठा afs_operation *op)
अणु
	अटल पूर्णांक count;
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_AFS_DEBUG_CURSOR) || count > 3)
		वापस;
	count++;

	rcu_पढ़ो_lock();

	pr_notice("EDESTADDR occurred\n");
	pr_notice("FC: cbb=%x cbb2=%x fl=%x err=%hd\n",
		  op->file[0].cb_अवरोध_beक्रमe,
		  op->file[1].cb_अवरोध_beक्रमe, op->flags, op->error);
	pr_notice("FC: ut=%lx ix=%d ni=%u\n",
		  op->untried, op->index, op->nr_iterations);

	अगर (op->server_list) अणु
		स्थिर काष्ठा afs_server_list *sl = op->server_list;
		pr_notice("FC: SL nr=%u pr=%u vnov=%hx\n",
			  sl->nr_servers, sl->preferred, sl->vnovol_mask);
		क्रम (i = 0; i < sl->nr_servers; i++) अणु
			स्थिर काष्ठा afs_server *s = sl->servers[i].server;
			pr_notice("FC: server fl=%lx av=%u %pU\n",
				  s->flags, s->addr_version, &s->uuid);
			अगर (s->addresses) अणु
				स्थिर काष्ठा afs_addr_list *a =
					rcu_dereference(s->addresses);
				pr_notice("FC:  - av=%u nr=%u/%u/%u pr=%u\n",
					  a->version,
					  a->nr_ipv4, a->nr_addrs, a->max_addrs,
					  a->preferred);
				pr_notice("FC:  - R=%lx F=%lx\n",
					  a->responded, a->failed);
				अगर (a == op->ac.alist)
					pr_notice("FC:  - current\n");
			पूर्ण
		पूर्ण
	पूर्ण

	pr_notice("AC: t=%lx ax=%u ac=%d er=%d r=%u ni=%u\n",
		  op->ac.tried, op->ac.index, op->ac.पात_code, op->ac.error,
		  op->ac.responded, op->ac.nr_iterations);
	rcu_पढ़ो_unlock();
पूर्ण
