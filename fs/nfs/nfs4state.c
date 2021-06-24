<शैली गुरु>
/*
 *  fs/nfs/nfs4state.c
 *
 *  Client-side XDR क्रम NFSv4.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Implementation of the NFSv4 state model.  For the समय being,
 * this is minimal, but will be made much more complex in a
 * subsequent patch.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/sunrpc/clnt.h>

#समावेश "nfs4_fs.h"
#समावेश "callback.h"
#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "nfs4idmap.h"
#समावेश "nfs4session.h"
#समावेश "pnfs.h"
#समावेश "netns.h"
#समावेश "nfs4trace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_STATE

#घोषणा OPENOWNER_POOL_SIZE	8

स्थिर nfs4_stateid zero_stateid = अणु
	अणु .data = अणु 0 पूर्ण पूर्ण,
	.type = NFS4_SPECIAL_STATEID_TYPE,
पूर्ण;
स्थिर nfs4_stateid invalid_stateid = अणु
	अणु
		/* Funky initialiser keeps older gcc versions happy */
		.data = अणु 0xff, 0xff, 0xff, 0xff, 0 पूर्ण,
	पूर्ण,
	.type = NFS4_INVALID_STATEID_TYPE,
पूर्ण;

स्थिर nfs4_stateid current_stateid = अणु
	अणु
		/* Funky initialiser keeps older gcc versions happy */
		.data = अणु 0x0, 0x0, 0x0, 0x1, 0 पूर्ण,
	पूर्ण,
	.type = NFS4_SPECIAL_STATEID_TYPE,
पूर्ण;

अटल DEFINE_MUTEX(nfs_clid_init_mutex);

अटल पूर्णांक nfs4_setup_state_renewal(काष्ठा nfs_client *clp)
अणु
	पूर्णांक status;
	काष्ठा nfs_fsinfo fsinfo;

	अगर (!test_bit(NFS_CS_CHECK_LEASE_TIME, &clp->cl_res_state)) अणु
		nfs4_schedule_state_renewal(clp);
		वापस 0;
	पूर्ण

	status = nfs4_proc_get_lease_समय(clp, &fsinfo);
	अगर (status == 0) अणु
		nfs4_set_lease_period(clp, fsinfo.lease_समय * HZ);
		nfs4_schedule_state_renewal(clp);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक nfs4_init_clientid(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs4_setclientid_res clid = अणु
		.clientid = clp->cl_clientid,
		.confirm = clp->cl_confirm,
	पूर्ण;
	अचिन्हित लघु port;
	पूर्णांक status;
	काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);

	अगर (test_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state))
		जाओ करो_confirm;
	port = nn->nfs_callback_tcpport;
	अगर (clp->cl_addr.ss_family == AF_INET6)
		port = nn->nfs_callback_tcpport6;

	status = nfs4_proc_setclientid(clp, NFS4_CALLBACK, port, cred, &clid);
	अगर (status != 0)
		जाओ out;
	clp->cl_clientid = clid.clientid;
	clp->cl_confirm = clid.confirm;
	set_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
करो_confirm:
	status = nfs4_proc_setclientid_confirm(clp, &clid, cred);
	अगर (status != 0)
		जाओ out;
	clear_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
	nfs4_setup_state_renewal(clp);
out:
	वापस status;
पूर्ण

/**
 * nfs40_discover_server_trunking - Detect server IP address trunking (mv0)
 *
 * @clp: nfs_client under test
 * @result: OUT: found nfs_client, or clp
 * @cred: credential to use क्रम trunking test
 *
 * Returns zero, a negative त्रुटि_सं, or a negative NFS4ERR status.
 * If zero is वापसed, an nfs_client poपूर्णांकer is planted in
 * "result".
 *
 * Note: The वापसed client may not yet be marked पढ़ोy.
 */
पूर्णांक nfs40_discover_server_trunking(काष्ठा nfs_client *clp,
				   काष्ठा nfs_client **result,
				   स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs4_setclientid_res clid = अणु
		.clientid = clp->cl_clientid,
		.confirm = clp->cl_confirm,
	पूर्ण;
	काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);
	अचिन्हित लघु port;
	पूर्णांक status;

	port = nn->nfs_callback_tcpport;
	अगर (clp->cl_addr.ss_family == AF_INET6)
		port = nn->nfs_callback_tcpport6;

	status = nfs4_proc_setclientid(clp, NFS4_CALLBACK, port, cred, &clid);
	अगर (status != 0)
		जाओ out;
	clp->cl_clientid = clid.clientid;
	clp->cl_confirm = clid.confirm;

	status = nfs40_walk_client_list(clp, result, cred);
	अगर (status == 0) अणु
		/* Sustain the lease, even अगर it's empty.  If the clientid4
		 * goes stale it's of no use क्रम trunking discovery. */
		nfs4_schedule_state_renewal(*result);

		/* If the client state need to recover, करो it. */
		अगर (clp->cl_state)
			nfs4_schedule_state_manager(clp);
	पूर्ण
out:
	वापस status;
पूर्ण

स्थिर काष्ठा cred *nfs4_get_machine_cred(काष्ठा nfs_client *clp)
अणु
	वापस get_cred(rpc_machine_cred());
पूर्ण

अटल व्योम nfs4_root_machine_cred(काष्ठा nfs_client *clp)
अणु

	/* Force root creds instead of machine */
	clp->cl_principal = शून्य;
	clp->cl_rpcclient->cl_principal = शून्य;
पूर्ण

अटल स्थिर काष्ठा cred *
nfs4_get_renew_cred_server_locked(काष्ठा nfs_server *server)
अणु
	स्थिर काष्ठा cred *cred = शून्य;
	काष्ठा nfs4_state_owner *sp;
	काष्ठा rb_node *pos;

	क्रम (pos = rb_first(&server->state_owners);
	     pos != शून्य;
	     pos = rb_next(pos)) अणु
		sp = rb_entry(pos, काष्ठा nfs4_state_owner, so_server_node);
		अगर (list_empty(&sp->so_states))
			जारी;
		cred = get_cred(sp->so_cred);
		अवरोध;
	पूर्ण
	वापस cred;
पूर्ण

/**
 * nfs4_get_renew_cred - Acquire credential क्रम a renew operation
 * @clp: client state handle
 *
 * Returns an rpc_cred with reference count bumped, or शून्य.
 * Caller must hold clp->cl_lock.
 */
स्थिर काष्ठा cred *nfs4_get_renew_cred(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा cred *cred = शून्य;
	काष्ठा nfs_server *server;

	/* Use machine credentials अगर available */
	cred = nfs4_get_machine_cred(clp);
	अगर (cred != शून्य)
		जाओ out;

	spin_lock(&clp->cl_lock);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		cred = nfs4_get_renew_cred_server_locked(server);
		अगर (cred != शून्य)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock(&clp->cl_lock);

out:
	वापस cred;
पूर्ण

अटल व्योम nfs4_end_drain_slot_table(काष्ठा nfs4_slot_table *tbl)
अणु
	अगर (test_and_clear_bit(NFS4_SLOT_TBL_DRAINING, &tbl->slot_tbl_state)) अणु
		spin_lock(&tbl->slot_tbl_lock);
		nfs41_wake_slot_table(tbl);
		spin_unlock(&tbl->slot_tbl_lock);
	पूर्ण
पूर्ण

अटल व्योम nfs4_end_drain_session(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_session *ses = clp->cl_session;

	अगर (clp->cl_slot_tbl) अणु
		nfs4_end_drain_slot_table(clp->cl_slot_tbl);
		वापस;
	पूर्ण

	अगर (ses != शून्य) अणु
		nfs4_end_drain_slot_table(&ses->bc_slot_table);
		nfs4_end_drain_slot_table(&ses->fc_slot_table);
	पूर्ण
पूर्ण

अटल पूर्णांक nfs4_drain_slot_tbl(काष्ठा nfs4_slot_table *tbl)
अणु
	set_bit(NFS4_SLOT_TBL_DRAINING, &tbl->slot_tbl_state);
	spin_lock(&tbl->slot_tbl_lock);
	अगर (tbl->highest_used_slotid != NFS4_NO_SLOT) अणु
		reinit_completion(&tbl->complete);
		spin_unlock(&tbl->slot_tbl_lock);
		वापस रुको_क्रम_completion_पूर्णांकerruptible(&tbl->complete);
	पूर्ण
	spin_unlock(&tbl->slot_tbl_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_begin_drain_session(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_session *ses = clp->cl_session;
	पूर्णांक ret;

	अगर (clp->cl_slot_tbl)
		वापस nfs4_drain_slot_tbl(clp->cl_slot_tbl);

	/* back channel */
	ret = nfs4_drain_slot_tbl(&ses->bc_slot_table);
	अगर (ret)
		वापस ret;
	/* क्रमe channel */
	वापस nfs4_drain_slot_tbl(&ses->fc_slot_table);
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)

अटल व्योम nfs41_finish_session_reset(काष्ठा nfs_client *clp)
अणु
	clear_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
	clear_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state);
	/* create_session negotiated new slot table */
	clear_bit(NFS4CLNT_BIND_CONN_TO_SESSION, &clp->cl_state);
	nfs4_setup_state_renewal(clp);
पूर्ण

पूर्णांक nfs41_init_clientid(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक status;

	अगर (test_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state))
		जाओ करो_confirm;
	status = nfs4_proc_exchange_id(clp, cred);
	अगर (status != 0)
		जाओ out;
	set_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
करो_confirm:
	status = nfs4_proc_create_session(clp, cred);
	अगर (status != 0)
		जाओ out;
	nfs41_finish_session_reset(clp);
	nfs_mark_client_पढ़ोy(clp, NFS_CS_READY);
out:
	वापस status;
पूर्ण

/**
 * nfs41_discover_server_trunking - Detect server IP address trunking (mv1)
 *
 * @clp: nfs_client under test
 * @result: OUT: found nfs_client, or clp
 * @cred: credential to use क्रम trunking test
 *
 * Returns NFS4_OK, a negative त्रुटि_सं, or a negative NFS4ERR status.
 * If NFS4_OK is वापसed, an nfs_client poपूर्णांकer is planted in
 * "result".
 *
 * Note: The वापसed client may not yet be marked पढ़ोy.
 */
पूर्णांक nfs41_discover_server_trunking(काष्ठा nfs_client *clp,
				   काष्ठा nfs_client **result,
				   स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक status;

	status = nfs4_proc_exchange_id(clp, cred);
	अगर (status != NFS4_OK)
		वापस status;

	status = nfs41_walk_client_list(clp, result, cred);
	अगर (status < 0)
		वापस status;
	अगर (clp != *result)
		वापस 0;

	/*
	 * Purge state अगर the client id was established in a prior
	 * instance and the client id could not have arrived on the
	 * server via Transparent State Migration.
	 */
	अगर (clp->cl_exchange_flags & EXCHGID4_FLAG_CONFIRMED_R) अणु
		अगर (!test_bit(NFS_CS_TSM_POSSIBLE, &clp->cl_flags))
			set_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state);
		अन्यथा
			set_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
	पूर्ण
	nfs4_schedule_state_manager(clp);
	status = nfs_रुको_client_init_complete(clp);
	अगर (status < 0)
		nfs_put_client(clp);
	वापस status;
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

/**
 * nfs4_get_clid_cred - Acquire credential क्रम a setclientid operation
 * @clp: client state handle
 *
 * Returns a cred with reference count bumped, or शून्य.
 */
स्थिर काष्ठा cred *nfs4_get_clid_cred(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा cred *cred;

	cred = nfs4_get_machine_cred(clp);
	वापस cred;
पूर्ण

अटल काष्ठा nfs4_state_owner *
nfs4_find_state_owner_locked(काष्ठा nfs_server *server, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rb_node **p = &server->state_owners.rb_node,
		       *parent = शून्य;
	काष्ठा nfs4_state_owner *sp;
	पूर्णांक cmp;

	जबतक (*p != शून्य) अणु
		parent = *p;
		sp = rb_entry(parent, काष्ठा nfs4_state_owner, so_server_node);
		cmp = cred_fscmp(cred, sp->so_cred);

		अगर (cmp < 0)
			p = &parent->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &parent->rb_right;
		अन्यथा अणु
			अगर (!list_empty(&sp->so_lru))
				list_del_init(&sp->so_lru);
			atomic_inc(&sp->so_count);
			वापस sp;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_state_owner *
nfs4_insert_state_owner_locked(काष्ठा nfs4_state_owner *new)
अणु
	काष्ठा nfs_server *server = new->so_server;
	काष्ठा rb_node **p = &server->state_owners.rb_node,
		       *parent = शून्य;
	काष्ठा nfs4_state_owner *sp;
	पूर्णांक cmp;

	जबतक (*p != शून्य) अणु
		parent = *p;
		sp = rb_entry(parent, काष्ठा nfs4_state_owner, so_server_node);
		cmp = cred_fscmp(new->so_cred, sp->so_cred);

		अगर (cmp < 0)
			p = &parent->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &parent->rb_right;
		अन्यथा अणु
			अगर (!list_empty(&sp->so_lru))
				list_del_init(&sp->so_lru);
			atomic_inc(&sp->so_count);
			वापस sp;
		पूर्ण
	पूर्ण
	rb_link_node(&new->so_server_node, parent, p);
	rb_insert_color(&new->so_server_node, &server->state_owners);
	वापस new;
पूर्ण

अटल व्योम
nfs4_हटाओ_state_owner_locked(काष्ठा nfs4_state_owner *sp)
अणु
	काष्ठा nfs_server *server = sp->so_server;

	अगर (!RB_EMPTY_NODE(&sp->so_server_node))
		rb_erase(&sp->so_server_node, &server->state_owners);
पूर्ण

अटल व्योम
nfs4_init_seqid_counter(काष्ठा nfs_seqid_counter *sc)
अणु
	sc->create_समय = kसमय_get();
	sc->flags = 0;
	sc->counter = 0;
	spin_lock_init(&sc->lock);
	INIT_LIST_HEAD(&sc->list);
	rpc_init_रुको_queue(&sc->रुको, "Seqid_waitqueue");
पूर्ण

अटल व्योम
nfs4_destroy_seqid_counter(काष्ठा nfs_seqid_counter *sc)
अणु
	rpc_destroy_रुको_queue(&sc->रुको);
पूर्ण

/*
 * nfs4_alloc_state_owner(): this is called on the OPEN or CREATE path to
 * create a new state_owner.
 *
 */
अटल काष्ठा nfs4_state_owner *
nfs4_alloc_state_owner(काष्ठा nfs_server *server,
		स्थिर काष्ठा cred *cred,
		gfp_t gfp_flags)
अणु
	काष्ठा nfs4_state_owner *sp;

	sp = kzalloc(माप(*sp), gfp_flags);
	अगर (!sp)
		वापस शून्य;
	sp->so_seqid.owner_id = ida_simple_get(&server->खोलोowner_id, 0, 0,
						gfp_flags);
	अगर (sp->so_seqid.owner_id < 0) अणु
		kमुक्त(sp);
		वापस शून्य;
	पूर्ण
	sp->so_server = server;
	sp->so_cred = get_cred(cred);
	spin_lock_init(&sp->so_lock);
	INIT_LIST_HEAD(&sp->so_states);
	nfs4_init_seqid_counter(&sp->so_seqid);
	atomic_set(&sp->so_count, 1);
	INIT_LIST_HEAD(&sp->so_lru);
	seqcount_spinlock_init(&sp->so_reclaim_seqcount, &sp->so_lock);
	mutex_init(&sp->so_delegवापस_mutex);
	वापस sp;
पूर्ण

अटल व्योम
nfs4_reset_state_owner(काष्ठा nfs4_state_owner *sp)
अणु
	/* This state_owner is no दीर्घer usable, but must
	 * reमुख्य in place so that state recovery can find it
	 * and the खोलोs associated with it.
	 * It may also be used क्रम new 'open' request to
	 * वापस a delegation to the server.
	 * So update the 'create_time' so that it looks like
	 * a new state_owner.  This will cause the server to
	 * request an OPEN_CONFIRM to start a new sequence.
	 */
	sp->so_seqid.create_समय = kसमय_get();
पूर्ण

अटल व्योम nfs4_मुक्त_state_owner(काष्ठा nfs4_state_owner *sp)
अणु
	nfs4_destroy_seqid_counter(&sp->so_seqid);
	put_cred(sp->so_cred);
	ida_simple_हटाओ(&sp->so_server->खोलोowner_id, sp->so_seqid.owner_id);
	kमुक्त(sp);
पूर्ण

अटल व्योम nfs4_gc_state_owners(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_state_owner *sp, *पंचांगp;
	अचिन्हित दीर्घ समय_min, समय_max;
	LIST_HEAD(करोomed);

	spin_lock(&clp->cl_lock);
	समय_max = jअगरfies;
	समय_min = (दीर्घ)समय_max - (दीर्घ)clp->cl_lease_समय;
	list_क्रम_each_entry_safe(sp, पंचांगp, &server->state_owners_lru, so_lru) अणु
		/* NB: LRU is sorted so that oldest is at the head */
		अगर (समय_in_range(sp->so_expires, समय_min, समय_max))
			अवरोध;
		list_move(&sp->so_lru, &करोomed);
		nfs4_हटाओ_state_owner_locked(sp);
	पूर्ण
	spin_unlock(&clp->cl_lock);

	list_क्रम_each_entry_safe(sp, पंचांगp, &करोomed, so_lru) अणु
		list_del(&sp->so_lru);
		nfs4_मुक्त_state_owner(sp);
	पूर्ण
पूर्ण

/**
 * nfs4_get_state_owner - Look up a state owner given a credential
 * @server: nfs_server to search
 * @cred: RPC credential to match
 * @gfp_flags: allocation mode
 *
 * Returns a poपूर्णांकer to an instantiated nfs4_state_owner काष्ठा, or शून्य.
 */
काष्ठा nfs4_state_owner *nfs4_get_state_owner(काष्ठा nfs_server *server,
					      स्थिर काष्ठा cred *cred,
					      gfp_t gfp_flags)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_state_owner *sp, *new;

	spin_lock(&clp->cl_lock);
	sp = nfs4_find_state_owner_locked(server, cred);
	spin_unlock(&clp->cl_lock);
	अगर (sp != शून्य)
		जाओ out;
	new = nfs4_alloc_state_owner(server, cred, gfp_flags);
	अगर (new == शून्य)
		जाओ out;
	spin_lock(&clp->cl_lock);
	sp = nfs4_insert_state_owner_locked(new);
	spin_unlock(&clp->cl_lock);
	अगर (sp != new)
		nfs4_मुक्त_state_owner(new);
out:
	nfs4_gc_state_owners(server);
	वापस sp;
पूर्ण

/**
 * nfs4_put_state_owner - Release a nfs4_state_owner
 * @sp: state owner data to release
 *
 * Note that we keep released state owners on an LRU
 * list.
 * This caches valid state owners so that they can be
 * reused, to aव्योम the OPEN_CONFIRM on minor version 0.
 * It also pins the uniquअगरier of dropped state owners क्रम
 * a जबतक, to ensure that those state owner names are
 * never reused.
 */
व्योम nfs4_put_state_owner(काष्ठा nfs4_state_owner *sp)
अणु
	काष्ठा nfs_server *server = sp->so_server;
	काष्ठा nfs_client *clp = server->nfs_client;

	अगर (!atomic_dec_and_lock(&sp->so_count, &clp->cl_lock))
		वापस;

	sp->so_expires = jअगरfies;
	list_add_tail(&sp->so_lru, &server->state_owners_lru);
	spin_unlock(&clp->cl_lock);
पूर्ण

/**
 * nfs4_purge_state_owners - Release all cached state owners
 * @server: nfs_server with cached state owners to release
 * @head: resulting list of state owners
 *
 * Called at umount समय.  Reमुख्यing state owners will be on
 * the LRU with ref count of zero.
 * Note that the state owners are not मुक्तd, but are added
 * to the list @head, which can later be used as an argument
 * to nfs4_मुक्त_state_owners.
 */
व्योम nfs4_purge_state_owners(काष्ठा nfs_server *server, काष्ठा list_head *head)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_state_owner *sp, *पंचांगp;

	spin_lock(&clp->cl_lock);
	list_क्रम_each_entry_safe(sp, पंचांगp, &server->state_owners_lru, so_lru) अणु
		list_move(&sp->so_lru, head);
		nfs4_हटाओ_state_owner_locked(sp);
	पूर्ण
	spin_unlock(&clp->cl_lock);
पूर्ण

/**
 * nfs4_मुक्त_state_owners - Release all cached state owners
 * @head: resulting list of state owners
 *
 * Frees a list of state owners that was generated by
 * nfs4_purge_state_owners
 */
व्योम nfs4_मुक्त_state_owners(काष्ठा list_head *head)
अणु
	काष्ठा nfs4_state_owner *sp, *पंचांगp;

	list_क्रम_each_entry_safe(sp, पंचांगp, head, so_lru) अणु
		list_del(&sp->so_lru);
		nfs4_मुक्त_state_owner(sp);
	पूर्ण
पूर्ण

अटल काष्ठा nfs4_state *
nfs4_alloc_खोलो_state(व्योम)
अणु
	काष्ठा nfs4_state *state;

	state = kzalloc(माप(*state), GFP_NOFS);
	अगर (!state)
		वापस शून्य;
	refcount_set(&state->count, 1);
	INIT_LIST_HEAD(&state->lock_states);
	spin_lock_init(&state->state_lock);
	seqlock_init(&state->seqlock);
	init_रुकोqueue_head(&state->रुकोq);
	वापस state;
पूर्ण

व्योम
nfs4_state_set_mode_locked(काष्ठा nfs4_state *state, भ_शेषe_t भ_शेषe)
अणु
	अगर (state->state == भ_शेषe)
		वापस;
	/* NB! List reordering - see the reclaim code क्रम why.  */
	अगर ((भ_शेषe & FMODE_WRITE) != (state->state & FMODE_WRITE)) अणु
		अगर (भ_शेषe & FMODE_WRITE)
			list_move(&state->खोलो_states, &state->owner->so_states);
		अन्यथा
			list_move_tail(&state->खोलो_states, &state->owner->so_states);
	पूर्ण
	state->state = भ_शेषe;
पूर्ण

अटल काष्ठा nfs4_state *
__nfs4_find_state_byowner(काष्ठा inode *inode, काष्ठा nfs4_state_owner *owner)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs4_state *state;

	list_क्रम_each_entry_rcu(state, &nfsi->खोलो_states, inode_states) अणु
		अगर (state->owner != owner)
			जारी;
		अगर (!nfs4_valid_खोलो_stateid(state))
			जारी;
		अगर (refcount_inc_not_zero(&state->count))
			वापस state;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
nfs4_मुक्त_खोलो_state(काष्ठा nfs4_state *state)
अणु
	kमुक्त_rcu(state, rcu_head);
पूर्ण

काष्ठा nfs4_state *
nfs4_get_खोलो_state(काष्ठा inode *inode, काष्ठा nfs4_state_owner *owner)
अणु
	काष्ठा nfs4_state *state, *new;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	rcu_पढ़ो_lock();
	state = __nfs4_find_state_byowner(inode, owner);
	rcu_पढ़ो_unlock();
	अगर (state)
		जाओ out;
	new = nfs4_alloc_खोलो_state();
	spin_lock(&owner->so_lock);
	spin_lock(&inode->i_lock);
	state = __nfs4_find_state_byowner(inode, owner);
	अगर (state == शून्य && new != शून्य) अणु
		state = new;
		state->owner = owner;
		atomic_inc(&owner->so_count);
		ihold(inode);
		state->inode = inode;
		list_add_rcu(&state->inode_states, &nfsi->खोलो_states);
		spin_unlock(&inode->i_lock);
		/* Note: The reclaim code dictates that we add stateless
		 * and पढ़ो-only stateids to the end of the list */
		list_add_tail(&state->खोलो_states, &owner->so_states);
		spin_unlock(&owner->so_lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&inode->i_lock);
		spin_unlock(&owner->so_lock);
		अगर (new)
			nfs4_मुक्त_खोलो_state(new);
	पूर्ण
out:
	वापस state;
पूर्ण

व्योम nfs4_put_खोलो_state(काष्ठा nfs4_state *state)
अणु
	काष्ठा inode *inode = state->inode;
	काष्ठा nfs4_state_owner *owner = state->owner;

	अगर (!refcount_dec_and_lock(&state->count, &owner->so_lock))
		वापस;
	spin_lock(&inode->i_lock);
	list_del_rcu(&state->inode_states);
	list_del(&state->खोलो_states);
	spin_unlock(&inode->i_lock);
	spin_unlock(&owner->so_lock);
	nfs4_inode_वापस_delegation_on_बंद(inode);
	iput(inode);
	nfs4_मुक्त_खोलो_state(state);
	nfs4_put_state_owner(owner);
पूर्ण

/*
 * Close the current file.
 */
अटल व्योम __nfs4_बंद(काष्ठा nfs4_state *state,
		भ_शेषe_t भ_शेषe, gfp_t gfp_mask, पूर्णांक रुको)
अणु
	काष्ठा nfs4_state_owner *owner = state->owner;
	पूर्णांक call_बंद = 0;
	भ_शेषe_t newstate;

	atomic_inc(&owner->so_count);
	/* Protect against nfs4_find_state() */
	spin_lock(&owner->so_lock);
	चयन (भ_शेषe & (FMODE_READ | FMODE_WRITE)) अणु
		हाल FMODE_READ:
			state->n_rकरोnly--;
			अवरोध;
		हाल FMODE_WRITE:
			state->n_wronly--;
			अवरोध;
		हाल FMODE_READ|FMODE_WRITE:
			state->n_rdwr--;
	पूर्ण
	newstate = FMODE_READ|FMODE_WRITE;
	अगर (state->n_rdwr == 0) अणु
		अगर (state->n_rकरोnly == 0) अणु
			newstate &= ~FMODE_READ;
			call_बंद |= test_bit(NFS_O_RDONLY_STATE, &state->flags);
			call_बंद |= test_bit(NFS_O_RDWR_STATE, &state->flags);
		पूर्ण
		अगर (state->n_wronly == 0) अणु
			newstate &= ~FMODE_WRITE;
			call_बंद |= test_bit(NFS_O_WRONLY_STATE, &state->flags);
			call_बंद |= test_bit(NFS_O_RDWR_STATE, &state->flags);
		पूर्ण
		अगर (newstate == 0)
			clear_bit(NFS_DELEGATED_STATE, &state->flags);
	पूर्ण
	nfs4_state_set_mode_locked(state, newstate);
	spin_unlock(&owner->so_lock);

	अगर (!call_बंद) अणु
		nfs4_put_खोलो_state(state);
		nfs4_put_state_owner(owner);
	पूर्ण अन्यथा
		nfs4_करो_बंद(state, gfp_mask, रुको);
पूर्ण

व्योम nfs4_बंद_state(काष्ठा nfs4_state *state, भ_शेषe_t भ_शेषe)
अणु
	__nfs4_बंद(state, भ_शेषe, GFP_NOFS, 0);
पूर्ण

व्योम nfs4_बंद_sync(काष्ठा nfs4_state *state, भ_शेषe_t भ_शेषe)
अणु
	__nfs4_बंद(state, भ_शेषe, GFP_KERNEL, 1);
पूर्ण

/*
 * Search the state->lock_states क्रम an existing lock_owner
 * that is compatible with either of the given owners.
 * If the second is non-zero, then the first refers to a Posix-lock
 * owner (current->files) and the second refers to a flock/OFD
 * owner (काष्ठा file*).  In that हाल, prefer a match क्रम the first
 * owner.
 * If both sorts of locks are held on the one file we cannot know
 * which stateid was पूर्णांकended to be used, so a "correct" choice cannot
 * be made.  Failing that, a "consistent" choice is preferable.  The
 * consistent choice we make is to prefer the first owner, that of a
 * Posix lock.
 */
अटल काष्ठा nfs4_lock_state *
__nfs4_find_lock_state(काष्ठा nfs4_state *state,
		       fl_owner_t fl_owner, fl_owner_t fl_owner2)
अणु
	काष्ठा nfs4_lock_state *pos, *ret = शून्य;
	list_क्रम_each_entry(pos, &state->lock_states, ls_locks) अणु
		अगर (pos->ls_owner == fl_owner) अणु
			ret = pos;
			अवरोध;
		पूर्ण
		अगर (pos->ls_owner == fl_owner2)
			ret = pos;
	पूर्ण
	अगर (ret)
		refcount_inc(&ret->ls_count);
	वापस ret;
पूर्ण

/*
 * Return a compatible lock_state. If no initialized lock_state काष्ठाure
 * exists, वापस an uninitialized one.
 *
 */
अटल काष्ठा nfs4_lock_state *nfs4_alloc_lock_state(काष्ठा nfs4_state *state, fl_owner_t fl_owner)
अणु
	काष्ठा nfs4_lock_state *lsp;
	काष्ठा nfs_server *server = state->owner->so_server;

	lsp = kzalloc(माप(*lsp), GFP_NOFS);
	अगर (lsp == शून्य)
		वापस शून्य;
	nfs4_init_seqid_counter(&lsp->ls_seqid);
	refcount_set(&lsp->ls_count, 1);
	lsp->ls_state = state;
	lsp->ls_owner = fl_owner;
	lsp->ls_seqid.owner_id = ida_simple_get(&server->lockowner_id, 0, 0, GFP_NOFS);
	अगर (lsp->ls_seqid.owner_id < 0)
		जाओ out_मुक्त;
	INIT_LIST_HEAD(&lsp->ls_locks);
	वापस lsp;
out_मुक्त:
	kमुक्त(lsp);
	वापस शून्य;
पूर्ण

व्योम nfs4_मुक्त_lock_state(काष्ठा nfs_server *server, काष्ठा nfs4_lock_state *lsp)
अणु
	ida_simple_हटाओ(&server->lockowner_id, lsp->ls_seqid.owner_id);
	nfs4_destroy_seqid_counter(&lsp->ls_seqid);
	kमुक्त(lsp);
पूर्ण

/*
 * Return a compatible lock_state. If no initialized lock_state काष्ठाure
 * exists, वापस an uninitialized one.
 *
 */
अटल काष्ठा nfs4_lock_state *nfs4_get_lock_state(काष्ठा nfs4_state *state, fl_owner_t owner)
अणु
	काष्ठा nfs4_lock_state *lsp, *new = शून्य;
	
	क्रम(;;) अणु
		spin_lock(&state->state_lock);
		lsp = __nfs4_find_lock_state(state, owner, शून्य);
		अगर (lsp != शून्य)
			अवरोध;
		अगर (new != शून्य) अणु
			list_add(&new->ls_locks, &state->lock_states);
			set_bit(LK_STATE_IN_USE, &state->flags);
			lsp = new;
			new = शून्य;
			अवरोध;
		पूर्ण
		spin_unlock(&state->state_lock);
		new = nfs4_alloc_lock_state(state, owner);
		अगर (new == शून्य)
			वापस शून्य;
	पूर्ण
	spin_unlock(&state->state_lock);
	अगर (new != शून्य)
		nfs4_मुक्त_lock_state(state->owner->so_server, new);
	वापस lsp;
पूर्ण

/*
 * Release reference to lock_state, and मुक्त it अगर we see that
 * it is no दीर्घer in use
 */
व्योम nfs4_put_lock_state(काष्ठा nfs4_lock_state *lsp)
अणु
	काष्ठा nfs_server *server;
	काष्ठा nfs4_state *state;

	अगर (lsp == शून्य)
		वापस;
	state = lsp->ls_state;
	अगर (!refcount_dec_and_lock(&lsp->ls_count, &state->state_lock))
		वापस;
	list_del(&lsp->ls_locks);
	अगर (list_empty(&state->lock_states))
		clear_bit(LK_STATE_IN_USE, &state->flags);
	spin_unlock(&state->state_lock);
	server = state->owner->so_server;
	अगर (test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags)) अणु
		काष्ठा nfs_client *clp = server->nfs_client;

		clp->cl_mvops->मुक्त_lock_state(server, lsp);
	पूर्ण अन्यथा
		nfs4_मुक्त_lock_state(server, lsp);
पूर्ण

अटल व्योम nfs4_fl_copy_lock(काष्ठा file_lock *dst, काष्ठा file_lock *src)
अणु
	काष्ठा nfs4_lock_state *lsp = src->fl_u.nfs4_fl.owner;

	dst->fl_u.nfs4_fl.owner = lsp;
	refcount_inc(&lsp->ls_count);
पूर्ण

अटल व्योम nfs4_fl_release_lock(काष्ठा file_lock *fl)
अणु
	nfs4_put_lock_state(fl->fl_u.nfs4_fl.owner);
पूर्ण

अटल स्थिर काष्ठा file_lock_operations nfs4_fl_lock_ops = अणु
	.fl_copy_lock = nfs4_fl_copy_lock,
	.fl_release_निजी = nfs4_fl_release_lock,
पूर्ण;

पूर्णांक nfs4_set_lock_state(काष्ठा nfs4_state *state, काष्ठा file_lock *fl)
अणु
	काष्ठा nfs4_lock_state *lsp;

	अगर (fl->fl_ops != शून्य)
		वापस 0;
	lsp = nfs4_get_lock_state(state, fl->fl_owner);
	अगर (lsp == शून्य)
		वापस -ENOMEM;
	fl->fl_u.nfs4_fl.owner = lsp;
	fl->fl_ops = &nfs4_fl_lock_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_copy_lock_stateid(nfs4_stateid *dst,
		काष्ठा nfs4_state *state,
		स्थिर काष्ठा nfs_lock_context *l_ctx)
अणु
	काष्ठा nfs4_lock_state *lsp;
	fl_owner_t fl_owner, fl_flock_owner;
	पूर्णांक ret = -ENOENT;

	अगर (l_ctx == शून्य)
		जाओ out;

	अगर (test_bit(LK_STATE_IN_USE, &state->flags) == 0)
		जाओ out;

	fl_owner = l_ctx->lockowner;
	fl_flock_owner = l_ctx->खोलो_context->flock_owner;

	spin_lock(&state->state_lock);
	lsp = __nfs4_find_lock_state(state, fl_owner, fl_flock_owner);
	अगर (lsp && test_bit(NFS_LOCK_LOST, &lsp->ls_flags))
		ret = -EIO;
	अन्यथा अगर (lsp != शून्य && test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags) != 0) अणु
		nfs4_stateid_copy(dst, &lsp->ls_stateid);
		ret = 0;
	पूर्ण
	spin_unlock(&state->state_lock);
	nfs4_put_lock_state(lsp);
out:
	वापस ret;
पूर्ण

bool nfs4_copy_खोलो_stateid(nfs4_stateid *dst, काष्ठा nfs4_state *state)
अणु
	bool ret;
	स्थिर nfs4_stateid *src;
	पूर्णांक seq;

	करो अणु
		ret = false;
		src = &zero_stateid;
		seq = पढ़ो_seqbegin(&state->seqlock);
		अगर (test_bit(NFS_OPEN_STATE, &state->flags)) अणु
			src = &state->खोलो_stateid;
			ret = true;
		पूर्ण
		nfs4_stateid_copy(dst, src);
	पूर्ण जबतक (पढ़ो_seqretry(&state->seqlock, seq));
	वापस ret;
पूर्ण

/*
 * Byte-range lock aware utility to initialize the stateid of पढ़ो/ग_लिखो
 * requests.
 */
पूर्णांक nfs4_select_rw_stateid(काष्ठा nfs4_state *state,
		भ_शेषe_t भ_शेषe, स्थिर काष्ठा nfs_lock_context *l_ctx,
		nfs4_stateid *dst, स्थिर काष्ठा cred **cred)
अणु
	पूर्णांक ret;

	अगर (!nfs4_valid_खोलो_stateid(state))
		वापस -EIO;
	अगर (cred != शून्य)
		*cred = शून्य;
	ret = nfs4_copy_lock_stateid(dst, state, l_ctx);
	अगर (ret == -EIO)
		/* A lost lock - करोn't even consider delegations */
		जाओ out;
	/* वापसs true अगर delegation stateid found and copied */
	अगर (nfs4_copy_delegation_stateid(state->inode, भ_शेषe, dst, cred)) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	अगर (ret != -ENOENT)
		/* nfs4_copy_delegation_stateid() didn't over-ग_लिखो
		 * dst, so it still has the lock stateid which we now
		 * choose to use.
		 */
		जाओ out;
	ret = nfs4_copy_खोलो_stateid(dst, state) ? 0 : -EAGAIN;
out:
	अगर (nfs_server_capable(state->inode, NFS_CAP_STATEID_NFSV41))
		dst->seqid = 0;
	वापस ret;
पूर्ण

काष्ठा nfs_seqid *nfs_alloc_seqid(काष्ठा nfs_seqid_counter *counter, gfp_t gfp_mask)
अणु
	काष्ठा nfs_seqid *new;

	new = kदो_स्मृति(माप(*new), gfp_mask);
	अगर (new == शून्य)
		वापस ERR_PTR(-ENOMEM);
	new->sequence = counter;
	INIT_LIST_HEAD(&new->list);
	new->task = शून्य;
	वापस new;
पूर्ण

व्योम nfs_release_seqid(काष्ठा nfs_seqid *seqid)
अणु
	काष्ठा nfs_seqid_counter *sequence;

	अगर (seqid == शून्य || list_empty(&seqid->list))
		वापस;
	sequence = seqid->sequence;
	spin_lock(&sequence->lock);
	list_del_init(&seqid->list);
	अगर (!list_empty(&sequence->list)) अणु
		काष्ठा nfs_seqid *next;

		next = list_first_entry(&sequence->list,
				काष्ठा nfs_seqid, list);
		rpc_wake_up_queued_task(&sequence->रुको, next->task);
	पूर्ण
	spin_unlock(&sequence->lock);
पूर्ण

व्योम nfs_मुक्त_seqid(काष्ठा nfs_seqid *seqid)
अणु
	nfs_release_seqid(seqid);
	kमुक्त(seqid);
पूर्ण

/*
 * Increment the seqid अगर the OPEN/OPEN_DOWNGRADE/CLOSE succeeded, or
 * failed with a seqid incrementing error -
 * see comments nfs4.h:seqid_mutating_error()
 */
अटल व्योम nfs_increment_seqid(पूर्णांक status, काष्ठा nfs_seqid *seqid)
अणु
	चयन (status) अणु
		हाल 0:
			अवरोध;
		हाल -NFS4ERR_BAD_SEQID:
			अगर (seqid->sequence->flags & NFS_SEQID_CONFIRMED)
				वापस;
			pr_warn_ratelimited("NFS: v4 server returned a bad"
					" sequence-id error on an"
					" unconfirmed sequence %p!\n",
					seqid->sequence);
			वापस;
		हाल -NFS4ERR_STALE_CLIENTID:
		हाल -NFS4ERR_STALE_STATEID:
		हाल -NFS4ERR_BAD_STATEID:
		हाल -NFS4ERR_BADXDR:
		हाल -NFS4ERR_RESOURCE:
		हाल -NFS4ERR_NOखाताHANDLE:
		हाल -NFS4ERR_MOVED:
			/* Non-seqid mutating errors */
			वापस;
	पूर्ण
	/*
	 * Note: no locking needed as we are guaranteed to be first
	 * on the sequence list
	 */
	seqid->sequence->counter++;
पूर्ण

व्योम nfs_increment_खोलो_seqid(पूर्णांक status, काष्ठा nfs_seqid *seqid)
अणु
	काष्ठा nfs4_state_owner *sp;

	अगर (seqid == शून्य)
		वापस;

	sp = container_of(seqid->sequence, काष्ठा nfs4_state_owner, so_seqid);
	अगर (status == -NFS4ERR_BAD_SEQID)
		nfs4_reset_state_owner(sp);
	अगर (!nfs4_has_session(sp->so_server->nfs_client))
		nfs_increment_seqid(status, seqid);
पूर्ण

/*
 * Increment the seqid अगर the LOCK/LOCKU succeeded, or
 * failed with a seqid incrementing error -
 * see comments nfs4.h:seqid_mutating_error()
 */
व्योम nfs_increment_lock_seqid(पूर्णांक status, काष्ठा nfs_seqid *seqid)
अणु
	अगर (seqid != शून्य)
		nfs_increment_seqid(status, seqid);
पूर्ण

पूर्णांक nfs_रुको_on_sequence(काष्ठा nfs_seqid *seqid, काष्ठा rpc_task *task)
अणु
	काष्ठा nfs_seqid_counter *sequence;
	पूर्णांक status = 0;

	अगर (seqid == शून्य)
		जाओ out;
	sequence = seqid->sequence;
	spin_lock(&sequence->lock);
	seqid->task = task;
	अगर (list_empty(&seqid->list))
		list_add_tail(&seqid->list, &sequence->list);
	अगर (list_first_entry(&sequence->list, काष्ठा nfs_seqid, list) == seqid)
		जाओ unlock;
	rpc_sleep_on(&sequence->रुको, task, शून्य);
	status = -EAGAIN;
unlock:
	spin_unlock(&sequence->lock);
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_run_state_manager(व्योम *);

अटल व्योम nfs4_clear_state_manager_bit(काष्ठा nfs_client *clp)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state);
	smp_mb__after_atomic();
	wake_up_bit(&clp->cl_state, NFS4CLNT_MANAGER_RUNNING);
	rpc_wake_up(&clp->cl_rpcरुकोq);
पूर्ण

/*
 * Schedule the nfs_client asynchronous state management routine
 */
व्योम nfs4_schedule_state_manager(काष्ठा nfs_client *clp)
अणु
	काष्ठा task_काष्ठा *task;
	अक्षर buf[INET6_ADDRSTRLEN + माप("-manager") + 1];

	set_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state);
	अगर (test_and_set_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state) != 0)
		वापस;
	__module_get(THIS_MODULE);
	refcount_inc(&clp->cl_count);

	/* The rcu_पढ़ो_lock() is not strictly necessary, as the state
	 * manager is the only thपढ़ो that ever changes the rpc_xprt
	 * after it's initialized.  At this point, we're single thपढ़ोed. */
	rcu_पढ़ो_lock();
	snम_लिखो(buf, माप(buf), "%s-manager",
			rpc_peeraddr2str(clp->cl_rpcclient, RPC_DISPLAY_ADDR));
	rcu_पढ़ो_unlock();
	task = kthपढ़ो_run(nfs4_run_state_manager, clp, "%s", buf);
	अगर (IS_ERR(task)) अणु
		prपूर्णांकk(KERN_ERR "%s: kthread_run: %ld\n",
			__func__, PTR_ERR(task));
		nfs4_clear_state_manager_bit(clp);
		nfs_put_client(clp);
		module_put(THIS_MODULE);
	पूर्ण
पूर्ण

/*
 * Schedule a lease recovery attempt
 */
व्योम nfs4_schedule_lease_recovery(काष्ठा nfs_client *clp)
अणु
	अगर (!clp)
		वापस;
	अगर (!test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state))
		set_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state);
	dprपूर्णांकk("%s: scheduling lease recovery for server %s\n", __func__,
			clp->cl_hostname);
	nfs4_schedule_state_manager(clp);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_schedule_lease_recovery);

/**
 * nfs4_schedule_migration_recovery - trigger migration recovery
 *
 * @server: FSID that is migrating
 *
 * Returns zero अगर recovery has started, otherwise a negative NFS4ERR
 * value is वापसed.
 */
पूर्णांक nfs4_schedule_migration_recovery(स्थिर काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;

	अगर (server->fh_expire_type != NFS4_FH_PERSISTENT) अणु
		pr_err("NFS: volatile file handles not supported (server %s)\n",
				clp->cl_hostname);
		वापस -NFS4ERR_IO;
	पूर्ण

	अगर (test_bit(NFS_MIG_FAILED, &server->mig_status))
		वापस -NFS4ERR_IO;

	dprपूर्णांकk("%s: scheduling migration recovery for (%llx:%llx) on %s\n",
			__func__,
			(अचिन्हित दीर्घ दीर्घ)server->fsid.major,
			(अचिन्हित दीर्घ दीर्घ)server->fsid.minor,
			clp->cl_hostname);

	set_bit(NFS_MIG_IN_TRANSITION,
			&((काष्ठा nfs_server *)server)->mig_status);
	set_bit(NFS4CLNT_MOVED, &clp->cl_state);

	nfs4_schedule_state_manager(clp);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_schedule_migration_recovery);

/**
 * nfs4_schedule_lease_moved_recovery - start lease-moved recovery
 *
 * @clp: server to check क्रम moved leases
 *
 */
व्योम nfs4_schedule_lease_moved_recovery(काष्ठा nfs_client *clp)
अणु
	dprपूर्णांकk("%s: scheduling lease-moved recovery for client ID %llx on %s\n",
		__func__, clp->cl_clientid, clp->cl_hostname);

	set_bit(NFS4CLNT_LEASE_MOVED, &clp->cl_state);
	nfs4_schedule_state_manager(clp);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_schedule_lease_moved_recovery);

पूर्णांक nfs4_रुको_clnt_recover(काष्ठा nfs_client *clp)
अणु
	पूर्णांक res;

	might_sleep();

	refcount_inc(&clp->cl_count);
	res = रुको_on_bit_action(&clp->cl_state, NFS4CLNT_MANAGER_RUNNING,
				 nfs_रुको_bit_समाप्तable, TASK_KILLABLE);
	अगर (res)
		जाओ out;
	अगर (clp->cl_cons_state < 0)
		res = clp->cl_cons_state;
out:
	nfs_put_client(clp);
	वापस res;
पूर्ण

पूर्णांक nfs4_client_recover_expired_lease(काष्ठा nfs_client *clp)
अणु
	अचिन्हित पूर्णांक loop;
	पूर्णांक ret;

	क्रम (loop = NFS4_MAX_LOOP_ON_RECOVER; loop != 0; loop--) अणु
		ret = nfs4_रुको_clnt_recover(clp);
		अगर (ret != 0)
			अवरोध;
		अगर (!test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state) &&
		    !test_bit(NFS4CLNT_CHECK_LEASE,&clp->cl_state))
			अवरोध;
		nfs4_schedule_state_manager(clp);
		ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * nfs40_handle_cb_pathकरोwn - वापस all delegations after NFS4ERR_CB_PATH_DOWN
 * @clp: client to process
 *
 * Set the NFS4CLNT_LEASE_EXPIRED state in order to क्रमce a
 * resend of the SETCLIENTID and hence re-establish the
 * callback channel. Then वापस all existing delegations.
 */
अटल व्योम nfs40_handle_cb_pathकरोwn(काष्ठा nfs_client *clp)
अणु
	set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
	nfs_expire_all_delegations(clp);
	dprपूर्णांकk("%s: handling CB_PATHDOWN recovery for server %s\n", __func__,
			clp->cl_hostname);
पूर्ण

व्योम nfs4_schedule_path_करोwn_recovery(काष्ठा nfs_client *clp)
अणु
	nfs40_handle_cb_pathकरोwn(clp);
	nfs4_schedule_state_manager(clp);
पूर्ण

अटल पूर्णांक nfs4_state_mark_reclaim_reboot(काष्ठा nfs_client *clp, काष्ठा nfs4_state *state)
अणु

	अगर (!nfs4_valid_खोलो_stateid(state))
		वापस 0;
	set_bit(NFS_STATE_RECLAIM_REBOOT, &state->flags);
	/* Don't recover state that expired beक्रमe the reboot */
	अगर (test_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags)) अणु
		clear_bit(NFS_STATE_RECLAIM_REBOOT, &state->flags);
		वापस 0;
	पूर्ण
	set_bit(NFS_OWNER_RECLAIM_REBOOT, &state->owner->so_flags);
	set_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state);
	वापस 1;
पूर्ण

पूर्णांक nfs4_state_mark_reclaim_nograce(काष्ठा nfs_client *clp, काष्ठा nfs4_state *state)
अणु
	अगर (!nfs4_valid_खोलो_stateid(state))
		वापस 0;
	set_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags);
	clear_bit(NFS_STATE_RECLAIM_REBOOT, &state->flags);
	set_bit(NFS_OWNER_RECLAIM_NOGRACE, &state->owner->so_flags);
	set_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state);
	वापस 1;
पूर्ण

पूर्णांक nfs4_schedule_stateid_recovery(स्थिर काष्ठा nfs_server *server, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;

	अगर (!nfs4_state_mark_reclaim_nograce(clp, state))
		वापस -EBADF;
	nfs_inode_find_delegation_state_and_recover(state->inode,
			&state->stateid);
	dprपूर्णांकk("%s: scheduling stateid recovery for server %s\n", __func__,
			clp->cl_hostname);
	nfs4_schedule_state_manager(clp);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_schedule_stateid_recovery);

अटल काष्ठा nfs4_lock_state *
nfs_state_find_lock_state_by_stateid(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs4_lock_state *pos;

	list_क्रम_each_entry(pos, &state->lock_states, ls_locks) अणु
		अगर (!test_bit(NFS_LOCK_INITIALIZED, &pos->ls_flags))
			जारी;
		अगर (nfs4_stateid_match_or_older(&pos->ls_stateid, stateid))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool nfs_state_lock_state_matches_stateid(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *stateid)
अणु
	bool found = false;

	अगर (test_bit(LK_STATE_IN_USE, &state->flags)) अणु
		spin_lock(&state->state_lock);
		अगर (nfs_state_find_lock_state_by_stateid(state, stateid))
			found = true;
		spin_unlock(&state->state_lock);
	पूर्ण
	वापस found;
पूर्ण

व्योम nfs_inode_find_state_and_recover(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs_client *clp = NFS_SERVER(inode)->nfs_client;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs4_state *state;
	bool found = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ctx, &nfsi->खोलो_files, list) अणु
		state = ctx->state;
		अगर (state == शून्य)
			जारी;
		अगर (nfs4_stateid_match_or_older(&state->stateid, stateid) &&
		    nfs4_state_mark_reclaim_nograce(clp, state)) अणु
			found = true;
			जारी;
		पूर्ण
		अगर (test_bit(NFS_OPEN_STATE, &state->flags) &&
		    nfs4_stateid_match_or_older(&state->खोलो_stateid, stateid) &&
		    nfs4_state_mark_reclaim_nograce(clp, state)) अणु
			found = true;
			जारी;
		पूर्ण
		अगर (nfs_state_lock_state_matches_stateid(state, stateid) &&
		    nfs4_state_mark_reclaim_nograce(clp, state))
			found = true;
	पूर्ण
	rcu_पढ़ो_unlock();

	nfs_inode_find_delegation_state_and_recover(inode, stateid);
	अगर (found)
		nfs4_schedule_state_manager(clp);
पूर्ण

अटल व्योम nfs4_state_mark_खोलो_context_bad(काष्ठा nfs4_state *state, पूर्णांक err)
अणु
	काष्ठा inode *inode = state->inode;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_खोलो_context *ctx;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ctx, &nfsi->खोलो_files, list) अणु
		अगर (ctx->state != state)
			जारी;
		set_bit(NFS_CONTEXT_BAD, &ctx->flags);
		pr_warn("NFSv4: state recovery failed for open file %pd2, "
				"error = %d\n", ctx->dentry, err);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम nfs4_state_mark_recovery_failed(काष्ठा nfs4_state *state, पूर्णांक error)
अणु
	set_bit(NFS_STATE_RECOVERY_FAILED, &state->flags);
	nfs4_state_mark_खोलो_context_bad(state, error);
पूर्ण


अटल पूर्णांक nfs4_reclaim_locks(काष्ठा nfs4_state *state, स्थिर काष्ठा nfs4_state_recovery_ops *ops)
अणु
	काष्ठा inode *inode = state->inode;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा file_lock *fl;
	काष्ठा nfs4_lock_state *lsp;
	पूर्णांक status = 0;
	काष्ठा file_lock_context *flctx = inode->i_flctx;
	काष्ठा list_head *list;

	अगर (flctx == शून्य)
		वापस 0;

	list = &flctx->flc_posix;

	/* Guard against delegation वापसs and new lock/unlock calls */
	करोwn_ग_लिखो(&nfsi->rwsem);
	spin_lock(&flctx->flc_lock);
restart:
	list_क्रम_each_entry(fl, list, fl_list) अणु
		अगर (nfs_file_खोलो_context(fl->fl_file)->state != state)
			जारी;
		spin_unlock(&flctx->flc_lock);
		status = ops->recover_lock(state, fl);
		चयन (status) अणु
		हाल 0:
			अवरोध;
		हाल -ETIMEDOUT:
		हाल -ESTALE:
		हाल -NFS4ERR_ADMIN_REVOKED:
		हाल -NFS4ERR_STALE_STATEID:
		हाल -NFS4ERR_BAD_STATEID:
		हाल -NFS4ERR_EXPIRED:
		हाल -NFS4ERR_NO_GRACE:
		हाल -NFS4ERR_STALE_CLIENTID:
		हाल -NFS4ERR_BADSESSION:
		हाल -NFS4ERR_BADSLOT:
		हाल -NFS4ERR_BAD_HIGH_SLOT:
		हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
			जाओ out;
		शेष:
			pr_err("NFS: %s: unhandled error %d\n",
					__func__, status);
			fallthrough;
		हाल -ENOMEM:
		हाल -NFS4ERR_DENIED:
		हाल -NFS4ERR_RECLAIM_BAD:
		हाल -NFS4ERR_RECLAIM_CONFLICT:
			lsp = fl->fl_u.nfs4_fl.owner;
			अगर (lsp)
				set_bit(NFS_LOCK_LOST, &lsp->ls_flags);
			status = 0;
		पूर्ण
		spin_lock(&flctx->flc_lock);
	पूर्ण
	अगर (list == &flctx->flc_posix) अणु
		list = &flctx->flc_flock;
		जाओ restart;
	पूर्ण
	spin_unlock(&flctx->flc_lock);
out:
	up_ग_लिखो(&nfsi->rwsem);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_2
अटल व्योम nfs42_complete_copies(काष्ठा nfs4_state_owner *sp, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs4_copy_state *copy;

	अगर (!test_bit(NFS_CLNT_DST_SSC_COPY_STATE, &state->flags) &&
		!test_bit(NFS_CLNT_SRC_SSC_COPY_STATE, &state->flags))
		वापस;

	spin_lock(&sp->so_server->nfs_client->cl_lock);
	list_क्रम_each_entry(copy, &sp->so_server->ss_copies, copies) अणु
		अगर ((test_bit(NFS_CLNT_DST_SSC_COPY_STATE, &state->flags) &&
				!nfs4_stateid_match_other(&state->stateid,
				&copy->parent_dst_state->stateid)))
				जारी;
		copy->flags = 1;
		अगर (test_and_clear_bit(NFS_CLNT_DST_SSC_COPY_STATE,
				&state->flags)) अणु
			clear_bit(NFS_CLNT_SRC_SSC_COPY_STATE, &state->flags);
			complete(&copy->completion);
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(copy, &sp->so_server->ss_copies, src_copies) अणु
		अगर ((test_bit(NFS_CLNT_SRC_SSC_COPY_STATE, &state->flags) &&
				!nfs4_stateid_match_other(&state->stateid,
				&copy->parent_src_state->stateid)))
				जारी;
		copy->flags = 1;
		अगर (test_and_clear_bit(NFS_CLNT_DST_SSC_COPY_STATE,
				&state->flags))
			complete(&copy->completion);
	पूर्ण
	spin_unlock(&sp->so_server->nfs_client->cl_lock);
पूर्ण
#अन्यथा /* !CONFIG_NFS_V4_2 */
अटल अंतरभूत व्योम nfs42_complete_copies(काष्ठा nfs4_state_owner *sp,
					 काष्ठा nfs4_state *state)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

अटल पूर्णांक __nfs4_reclaim_खोलो_state(काष्ठा nfs4_state_owner *sp, काष्ठा nfs4_state *state,
				     स्थिर काष्ठा nfs4_state_recovery_ops *ops)
अणु
	काष्ठा nfs4_lock_state *lock;
	पूर्णांक status;

	status = ops->recover_खोलो(sp, state);
	अगर (status < 0)
		वापस status;

	status = nfs4_reclaim_locks(state, ops);
	अगर (status < 0)
		वापस status;

	अगर (!test_bit(NFS_DELEGATED_STATE, &state->flags)) अणु
		spin_lock(&state->state_lock);
		list_क्रम_each_entry(lock, &state->lock_states, ls_locks) अणु
			trace_nfs4_state_lock_reclaim(state, lock);
			अगर (!test_bit(NFS_LOCK_INITIALIZED, &lock->ls_flags))
				pr_warn_ratelimited("NFS: %s: Lock reclaim failed!\n", __func__);
		पूर्ण
		spin_unlock(&state->state_lock);
	पूर्ण

	nfs42_complete_copies(sp, state);
	clear_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_reclaim_खोलो_state(काष्ठा nfs4_state_owner *sp, स्थिर काष्ठा nfs4_state_recovery_ops *ops)
अणु
	काष्ठा nfs4_state *state;
	अचिन्हित पूर्णांक loop = 0;
	पूर्णांक status = 0;
#अगर_घोषित CONFIG_NFS_V4_2
	bool found_ssc_copy_state = false;
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

	/* Note: we rely on the sp->so_states list being ordered 
	 * so that we always reclaim खोलो(O_RDWR) and/or खोलो(O_WRITE)
	 * states first.
	 * This is needed to ensure that the server won't give us any
	 * पढ़ो delegations that we have to वापस अगर, say, we are
	 * recovering after a network partition or a reboot from a
	 * server that करोesn't support a grace period.
	 */
	spin_lock(&sp->so_lock);
	raw_ग_लिखो_seqcount_begin(&sp->so_reclaim_seqcount);
restart:
	list_क्रम_each_entry(state, &sp->so_states, खोलो_states) अणु
		अगर (!test_and_clear_bit(ops->state_flag_bit, &state->flags))
			जारी;
		अगर (!nfs4_valid_खोलो_stateid(state))
			जारी;
		अगर (state->state == 0)
			जारी;
#अगर_घोषित CONFIG_NFS_V4_2
		अगर (test_bit(NFS_SRV_SSC_COPY_STATE, &state->flags)) अणु
			nfs4_state_mark_recovery_failed(state, -EIO);
			found_ssc_copy_state = true;
			जारी;
		पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
		refcount_inc(&state->count);
		spin_unlock(&sp->so_lock);
		status = __nfs4_reclaim_खोलो_state(sp, state, ops);

		चयन (status) अणु
		शेष:
			अगर (status >= 0) अणु
				loop = 0;
				अवरोध;
			पूर्ण
			prपूर्णांकk(KERN_ERR "NFS: %s: unhandled error %d\n", __func__, status);
			fallthrough;
		हाल -ENOENT:
		हाल -ENOMEM:
		हाल -EACCES:
		हाल -EROFS:
		हाल -EIO:
		हाल -ESTALE:
			/* Open state on this file cannot be recovered */
			nfs4_state_mark_recovery_failed(state, status);
			अवरोध;
		हाल -EAGAIN:
			ssleep(1);
			अगर (loop++ < 10) अणु
				set_bit(ops->state_flag_bit, &state->flags);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -NFS4ERR_ADMIN_REVOKED:
		हाल -NFS4ERR_STALE_STATEID:
		हाल -NFS4ERR_OLD_STATEID:
		हाल -NFS4ERR_BAD_STATEID:
		हाल -NFS4ERR_RECLAIM_BAD:
		हाल -NFS4ERR_RECLAIM_CONFLICT:
			nfs4_state_mark_reclaim_nograce(sp->so_server->nfs_client, state);
			अवरोध;
		हाल -NFS4ERR_EXPIRED:
		हाल -NFS4ERR_NO_GRACE:
			nfs4_state_mark_reclaim_nograce(sp->so_server->nfs_client, state);
			fallthrough;
		हाल -NFS4ERR_STALE_CLIENTID:
		हाल -NFS4ERR_BADSESSION:
		हाल -NFS4ERR_BADSLOT:
		हाल -NFS4ERR_BAD_HIGH_SLOT:
		हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		हाल -ETIMEDOUT:
			जाओ out_err;
		पूर्ण
		nfs4_put_खोलो_state(state);
		spin_lock(&sp->so_lock);
		जाओ restart;
	पूर्ण
	raw_ग_लिखो_seqcount_end(&sp->so_reclaim_seqcount);
	spin_unlock(&sp->so_lock);
#अगर_घोषित CONFIG_NFS_V4_2
	अगर (found_ssc_copy_state)
		वापस -EIO;
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
	वापस 0;
out_err:
	nfs4_put_खोलो_state(state);
	spin_lock(&sp->so_lock);
	raw_ग_लिखो_seqcount_end(&sp->so_reclaim_seqcount);
	spin_unlock(&sp->so_lock);
	वापस status;
पूर्ण

अटल व्योम nfs4_clear_खोलो_state(काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs4_lock_state *lock;

	clear_bit(NFS_DELEGATED_STATE, &state->flags);
	clear_bit(NFS_O_RDONLY_STATE, &state->flags);
	clear_bit(NFS_O_WRONLY_STATE, &state->flags);
	clear_bit(NFS_O_RDWR_STATE, &state->flags);
	spin_lock(&state->state_lock);
	list_क्रम_each_entry(lock, &state->lock_states, ls_locks) अणु
		lock->ls_seqid.flags = 0;
		clear_bit(NFS_LOCK_INITIALIZED, &lock->ls_flags);
	पूर्ण
	spin_unlock(&state->state_lock);
पूर्ण

अटल व्योम nfs4_reset_seqids(काष्ठा nfs_server *server,
	पूर्णांक (*mark_reclaim)(काष्ठा nfs_client *clp, काष्ठा nfs4_state *state))
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_state_owner *sp;
	काष्ठा rb_node *pos;
	काष्ठा nfs4_state *state;

	spin_lock(&clp->cl_lock);
	क्रम (pos = rb_first(&server->state_owners);
	     pos != शून्य;
	     pos = rb_next(pos)) अणु
		sp = rb_entry(pos, काष्ठा nfs4_state_owner, so_server_node);
		sp->so_seqid.flags = 0;
		spin_lock(&sp->so_lock);
		list_क्रम_each_entry(state, &sp->so_states, खोलो_states) अणु
			अगर (mark_reclaim(clp, state))
				nfs4_clear_खोलो_state(state);
		पूर्ण
		spin_unlock(&sp->so_lock);
	पूर्ण
	spin_unlock(&clp->cl_lock);
पूर्ण

अटल व्योम nfs4_state_mark_reclaim_helper(काष्ठा nfs_client *clp,
	पूर्णांक (*mark_reclaim)(काष्ठा nfs_client *clp, काष्ठा nfs4_state *state))
अणु
	काष्ठा nfs_server *server;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		nfs4_reset_seqids(server, mark_reclaim);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम nfs4_state_start_reclaim_reboot(काष्ठा nfs_client *clp)
अणु
	/* Mark all delegations क्रम reclaim */
	nfs_delegation_mark_reclaim(clp);
	nfs4_state_mark_reclaim_helper(clp, nfs4_state_mark_reclaim_reboot);
पूर्ण

अटल पूर्णांक nfs4_reclaim_complete(काष्ठा nfs_client *clp,
				 स्थिर काष्ठा nfs4_state_recovery_ops *ops,
				 स्थिर काष्ठा cred *cred)
अणु
	/* Notअगरy the server we're करोne reclaiming our state */
	अगर (ops->reclaim_complete)
		वापस ops->reclaim_complete(clp, cred);
	वापस 0;
पूर्ण

अटल व्योम nfs4_clear_reclaim_server(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_state_owner *sp;
	काष्ठा rb_node *pos;
	काष्ठा nfs4_state *state;

	spin_lock(&clp->cl_lock);
	क्रम (pos = rb_first(&server->state_owners);
	     pos != शून्य;
	     pos = rb_next(pos)) अणु
		sp = rb_entry(pos, काष्ठा nfs4_state_owner, so_server_node);
		spin_lock(&sp->so_lock);
		list_क्रम_each_entry(state, &sp->so_states, खोलो_states) अणु
			अगर (!test_and_clear_bit(NFS_STATE_RECLAIM_REBOOT,
						&state->flags))
				जारी;
			nfs4_state_mark_reclaim_nograce(clp, state);
		पूर्ण
		spin_unlock(&sp->so_lock);
	पूर्ण
	spin_unlock(&clp->cl_lock);
पूर्ण

अटल पूर्णांक nfs4_state_clear_reclaim_reboot(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_server *server;

	अगर (!test_and_clear_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state))
		वापस 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		nfs4_clear_reclaim_server(server);
	rcu_पढ़ो_unlock();

	nfs_delegation_reap_unclaimed(clp);
	वापस 1;
पूर्ण

अटल व्योम nfs4_state_end_reclaim_reboot(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा nfs4_state_recovery_ops *ops;
	स्थिर काष्ठा cred *cred;
	पूर्णांक err;

	अगर (!nfs4_state_clear_reclaim_reboot(clp))
		वापस;
	ops = clp->cl_mvops->reboot_recovery_ops;
	cred = nfs4_get_clid_cred(clp);
	err = nfs4_reclaim_complete(clp, ops, cred);
	put_cred(cred);
	अगर (err == -NFS4ERR_CONN_NOT_BOUND_TO_SESSION)
		set_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state);
पूर्ण

अटल व्योम nfs4_state_start_reclaim_nograce(काष्ठा nfs_client *clp)
अणु
	nfs_mark_test_expired_all_delegations(clp);
	nfs4_state_mark_reclaim_helper(clp, nfs4_state_mark_reclaim_nograce);
पूर्ण

अटल पूर्णांक nfs4_recovery_handle_error(काष्ठा nfs_client *clp, पूर्णांक error)
अणु
	चयन (error) अणु
	हाल 0:
		अवरोध;
	हाल -NFS4ERR_CB_PATH_DOWN:
		nfs40_handle_cb_pathकरोwn(clp);
		अवरोध;
	हाल -NFS4ERR_NO_GRACE:
		nfs4_state_end_reclaim_reboot(clp);
		अवरोध;
	हाल -NFS4ERR_STALE_CLIENTID:
		set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
		nfs4_state_start_reclaim_reboot(clp);
		अवरोध;
	हाल -NFS4ERR_EXPIRED:
		set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
		nfs4_state_start_reclaim_nograce(clp);
		अवरोध;
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_BADSLOT:
	हाल -NFS4ERR_BAD_HIGH_SLOT:
	हाल -NFS4ERR_DEADSESSION:
	हाल -NFS4ERR_SEQ_FALSE_RETRY:
	हाल -NFS4ERR_SEQ_MISORDERED:
		set_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state);
		/* Zero session reset errors */
		अवरोध;
	हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		set_bit(NFS4CLNT_BIND_CONN_TO_SESSION, &clp->cl_state);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: failed to handle error %d for server %s\n",
				__func__, error, clp->cl_hostname);
		वापस error;
	पूर्ण
	dprपूर्णांकk("%s: handled error %d for server %s\n", __func__, error,
			clp->cl_hostname);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_करो_reclaim(काष्ठा nfs_client *clp, स्थिर काष्ठा nfs4_state_recovery_ops *ops)
अणु
	काष्ठा nfs4_state_owner *sp;
	काष्ठा nfs_server *server;
	काष्ठा rb_node *pos;
	LIST_HEAD(मुक्तme);
	पूर्णांक status = 0;

restart:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		nfs4_purge_state_owners(server, &मुक्तme);
		spin_lock(&clp->cl_lock);
		क्रम (pos = rb_first(&server->state_owners);
		     pos != शून्य;
		     pos = rb_next(pos)) अणु
			sp = rb_entry(pos,
				काष्ठा nfs4_state_owner, so_server_node);
			अगर (!test_and_clear_bit(ops->owner_flag_bit,
							&sp->so_flags))
				जारी;
			अगर (!atomic_inc_not_zero(&sp->so_count))
				जारी;
			spin_unlock(&clp->cl_lock);
			rcu_पढ़ो_unlock();

			status = nfs4_reclaim_खोलो_state(sp, ops);
			अगर (status < 0) अणु
				set_bit(ops->owner_flag_bit, &sp->so_flags);
				nfs4_put_state_owner(sp);
				status = nfs4_recovery_handle_error(clp, status);
				वापस (status != 0) ? status : -EAGAIN;
			पूर्ण

			nfs4_put_state_owner(sp);
			जाओ restart;
		पूर्ण
		spin_unlock(&clp->cl_lock);
	पूर्ण
	rcu_पढ़ो_unlock();
	nfs4_मुक्त_state_owners(&मुक्तme);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_check_lease(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा cred *cred;
	स्थिर काष्ठा nfs4_state_मुख्यtenance_ops *ops =
		clp->cl_mvops->state_renewal_ops;
	पूर्णांक status;

	/* Is the client alपढ़ोy known to have an expired lease? */
	अगर (test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state))
		वापस 0;
	cred = ops->get_state_renewal_cred(clp);
	अगर (cred == शून्य) अणु
		cred = nfs4_get_clid_cred(clp);
		status = -ENOKEY;
		अगर (cred == शून्य)
			जाओ out;
	पूर्ण
	status = ops->renew_lease(clp, cred);
	put_cred(cred);
	अगर (status == -ETIMEDOUT) अणु
		set_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state);
		वापस 0;
	पूर्ण
out:
	वापस nfs4_recovery_handle_error(clp, status);
पूर्ण

/* Set NFS4CLNT_LEASE_EXPIRED and reclaim reboot state क्रम all v4.0 errors
 * and क्रम recoverable errors on EXCHANGE_ID क्रम v4.1
 */
अटल पूर्णांक nfs4_handle_reclaim_lease_error(काष्ठा nfs_client *clp, पूर्णांक status)
अणु
	चयन (status) अणु
	हाल -NFS4ERR_SEQ_MISORDERED:
		अगर (test_and_set_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state))
			वापस -ESERVERFAULT;
		/* Lease confirmation error: retry after purging the lease */
		ssleep(1);
		clear_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
		अवरोध;
	हाल -NFS4ERR_STALE_CLIENTID:
		clear_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
		nfs4_state_start_reclaim_reboot(clp);
		अवरोध;
	हाल -NFS4ERR_CLID_INUSE:
		pr_err("NFS: Server %s reports our clientid is in use\n",
			clp->cl_hostname);
		nfs_mark_client_पढ़ोy(clp, -EPERM);
		clear_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
		वापस -EPERM;
	हाल -EACCES:
	हाल -NFS4ERR_DELAY:
	हाल -EAGAIN:
		ssleep(1);
		अवरोध;

	हाल -NFS4ERR_MINOR_VERS_MISMATCH:
		अगर (clp->cl_cons_state == NFS_CS_SESSION_INITING)
			nfs_mark_client_पढ़ोy(clp, -EPROTONOSUPPORT);
		dprपूर्णांकk("%s: exit with error %d for server %s\n",
				__func__, -EPROTONOSUPPORT, clp->cl_hostname);
		वापस -EPROTONOSUPPORT;
	हाल -NFS4ERR_NOT_SAME: /* FixMe: implement recovery
				 * in nfs4_exchange_id */
	शेष:
		dprपूर्णांकk("%s: exit with error %d for server %s\n", __func__,
				status, clp->cl_hostname);
		वापस status;
	पूर्ण
	set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
	dprपूर्णांकk("%s: handled error %d for server %s\n", __func__, status,
			clp->cl_hostname);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_establish_lease(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा cred *cred;
	स्थिर काष्ठा nfs4_state_recovery_ops *ops =
		clp->cl_mvops->reboot_recovery_ops;
	पूर्णांक status;

	status = nfs4_begin_drain_session(clp);
	अगर (status != 0)
		वापस status;
	cred = nfs4_get_clid_cred(clp);
	अगर (cred == शून्य)
		वापस -ENOENT;
	status = ops->establish_clid(clp, cred);
	put_cred(cred);
	अगर (status != 0)
		वापस status;
	pnfs_destroy_all_layouts(clp);
	वापस 0;
पूर्ण

/*
 * Returns zero or a negative त्रुटि_सं.  NFS4ERR values are converted
 * to local त्रुटि_सं values.
 */
अटल पूर्णांक nfs4_reclaim_lease(काष्ठा nfs_client *clp)
अणु
	पूर्णांक status;

	status = nfs4_establish_lease(clp);
	अगर (status < 0)
		वापस nfs4_handle_reclaim_lease_error(clp, status);
	अगर (test_and_clear_bit(NFS4CLNT_SERVER_SCOPE_MISMATCH, &clp->cl_state))
		nfs4_state_start_reclaim_nograce(clp);
	अगर (!test_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state))
		set_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state);
	clear_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state);
	clear_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_purge_lease(काष्ठा nfs_client *clp)
अणु
	पूर्णांक status;

	status = nfs4_establish_lease(clp);
	अगर (status < 0)
		वापस nfs4_handle_reclaim_lease_error(clp, status);
	clear_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state);
	set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
	nfs4_state_start_reclaim_nograce(clp);
	वापस 0;
पूर्ण

/*
 * Try remote migration of one FSID from a source server to a
 * destination server.  The source server provides a list of
 * potential destinations.
 *
 * Returns zero or a negative NFS4ERR status code.
 */
अटल पूर्णांक nfs4_try_migration(काष्ठा nfs_server *server, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_fs_locations *locations = शून्य;
	काष्ठा inode *inode;
	काष्ठा page *page;
	पूर्णांक status, result;

	dprपूर्णांकk("--> %s: FSID %llx:%llx on \"%s\"\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)server->fsid.major,
			(अचिन्हित दीर्घ दीर्घ)server->fsid.minor,
			clp->cl_hostname);

	result = 0;
	page = alloc_page(GFP_KERNEL);
	locations = kदो_स्मृति(माप(काष्ठा nfs4_fs_locations), GFP_KERNEL);
	अगर (page == शून्य || locations == शून्य) अणु
		dprपूर्णांकk("<-- %s: no memory\n", __func__);
		जाओ out;
	पूर्ण

	inode = d_inode(server->super->s_root);
	result = nfs4_proc_get_locations(inode, locations, page, cred);
	अगर (result) अणु
		dprपूर्णांकk("<-- %s: failed to retrieve fs_locations: %d\n",
			__func__, result);
		जाओ out;
	पूर्ण

	result = -NFS4ERR_NXIO;
	अगर (!(locations->fattr.valid & NFS_ATTR_FATTR_V4_LOCATIONS)) अणु
		dprपूर्णांकk("<-- %s: No fs_locations data, migration skipped\n",
			__func__);
		जाओ out;
	पूर्ण

	status = nfs4_begin_drain_session(clp);
	अगर (status != 0) अणु
		result = status;
		जाओ out;
	पूर्ण

	status = nfs4_replace_transport(server, locations);
	अगर (status != 0) अणु
		dprपूर्णांकk("<-- %s: failed to replace transport: %d\n",
			__func__, status);
		जाओ out;
	पूर्ण

	result = 0;
	dprपूर्णांकk("<-- %s: migration succeeded\n", __func__);

out:
	अगर (page != शून्य)
		__मुक्त_page(page);
	kमुक्त(locations);
	अगर (result) अणु
		pr_err("NFS: migration recovery failed (server %s)\n",
				clp->cl_hostname);
		set_bit(NFS_MIG_FAILED, &server->mig_status);
	पूर्ण
	वापस result;
पूर्ण

/*
 * Returns zero or a negative NFS4ERR status code.
 */
अटल पूर्णांक nfs4_handle_migration(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा nfs4_state_मुख्यtenance_ops *ops =
				clp->cl_mvops->state_renewal_ops;
	काष्ठा nfs_server *server;
	स्थिर काष्ठा cred *cred;

	dprपूर्णांकk("%s: migration reported on \"%s\"\n", __func__,
			clp->cl_hostname);

	cred = ops->get_state_renewal_cred(clp);
	अगर (cred == शून्य)
		वापस -NFS4ERR_NOENT;

	clp->cl_mig_gen++;
restart:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		पूर्णांक status;

		अगर (server->mig_gen == clp->cl_mig_gen)
			जारी;
		server->mig_gen = clp->cl_mig_gen;

		अगर (!test_and_clear_bit(NFS_MIG_IN_TRANSITION,
						&server->mig_status))
			जारी;

		rcu_पढ़ो_unlock();
		status = nfs4_try_migration(server, cred);
		अगर (status < 0) अणु
			put_cred(cred);
			वापस status;
		पूर्ण
		जाओ restart;
	पूर्ण
	rcu_पढ़ो_unlock();
	put_cred(cred);
	वापस 0;
पूर्ण

/*
 * Test each nfs_server on the clp's cl_superblocks list to see
 * अगर it's moved to another server.  Stop when the server no दीर्घer
 * वापसs NFS4ERR_LEASE_MOVED.
 */
अटल पूर्णांक nfs4_handle_lease_moved(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा nfs4_state_मुख्यtenance_ops *ops =
				clp->cl_mvops->state_renewal_ops;
	काष्ठा nfs_server *server;
	स्थिर काष्ठा cred *cred;

	dprपूर्णांकk("%s: lease moved reported on \"%s\"\n", __func__,
			clp->cl_hostname);

	cred = ops->get_state_renewal_cred(clp);
	अगर (cred == शून्य)
		वापस -NFS4ERR_NOENT;

	clp->cl_mig_gen++;
restart:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		काष्ठा inode *inode;
		पूर्णांक status;

		अगर (server->mig_gen == clp->cl_mig_gen)
			जारी;
		server->mig_gen = clp->cl_mig_gen;

		rcu_पढ़ो_unlock();

		inode = d_inode(server->super->s_root);
		status = nfs4_proc_fsid_present(inode, cred);
		अगर (status != -NFS4ERR_MOVED)
			जाओ restart;	/* wasn't this one */
		अगर (nfs4_try_migration(server, cred) == -NFS4ERR_LEASE_MOVED)
			जाओ restart;	/* there are more */
		जाओ out;
	पूर्ण
	rcu_पढ़ो_unlock();

out:
	put_cred(cred);
	वापस 0;
पूर्ण

/**
 * nfs4_discover_server_trunking - Detect server IP address trunking
 *
 * @clp: nfs_client under test
 * @result: OUT: found nfs_client, or clp
 *
 * Returns zero or a negative त्रुटि_सं.  If zero is वापसed,
 * an nfs_client poपूर्णांकer is planted in "result".
 *
 * Note: since we are invoked in process context, and
 * not from inside the state manager, we cannot use
 * nfs4_handle_reclaim_lease_error().
 */
पूर्णांक nfs4_discover_server_trunking(काष्ठा nfs_client *clp,
				  काष्ठा nfs_client **result)
अणु
	स्थिर काष्ठा nfs4_state_recovery_ops *ops =
				clp->cl_mvops->reboot_recovery_ops;
	काष्ठा rpc_clnt *clnt;
	स्थिर काष्ठा cred *cred;
	पूर्णांक i, status;

	dprपूर्णांकk("NFS: %s: testing '%s'\n", __func__, clp->cl_hostname);

	clnt = clp->cl_rpcclient;
	i = 0;

	mutex_lock(&nfs_clid_init_mutex);
again:
	status  = -ENOENT;
	cred = nfs4_get_clid_cred(clp);
	अगर (cred == शून्य)
		जाओ out_unlock;

	status = ops->detect_trunking(clp, result, cred);
	put_cred(cred);
	चयन (status) अणु
	हाल 0:
	हाल -EINTR:
	हाल -ERESTARTSYS:
		अवरोध;
	हाल -ETIMEDOUT:
		अगर (clnt->cl_softrtry)
			अवरोध;
		fallthrough;
	हाल -NFS4ERR_DELAY:
	हाल -EAGAIN:
		ssleep(1);
		fallthrough;
	हाल -NFS4ERR_STALE_CLIENTID:
		dprपूर्णांकk("NFS: %s after status %d, retrying\n",
			__func__, status);
		जाओ again;
	हाल -EACCES:
		अगर (i++ == 0) अणु
			nfs4_root_machine_cred(clp);
			जाओ again;
		पूर्ण
		अगर (clnt->cl_auth->au_flavor == RPC_AUTH_UNIX)
			अवरोध;
		fallthrough;
	हाल -NFS4ERR_CLID_INUSE:
	हाल -NFS4ERR_WRONGSEC:
		/* No poपूर्णांक in retrying अगर we alपढ़ोy used RPC_AUTH_UNIX */
		अगर (clnt->cl_auth->au_flavor == RPC_AUTH_UNIX) अणु
			status = -EPERM;
			अवरोध;
		पूर्ण
		clnt = rpc_clone_client_set_auth(clnt, RPC_AUTH_UNIX);
		अगर (IS_ERR(clnt)) अणु
			status = PTR_ERR(clnt);
			अवरोध;
		पूर्ण
		/* Note: this is safe because we haven't yet marked the
		 * client as पढ़ोy, so we are the only user of
		 * clp->cl_rpcclient
		 */
		clnt = xchg(&clp->cl_rpcclient, clnt);
		rpc_shutकरोwn_client(clnt);
		clnt = clp->cl_rpcclient;
		जाओ again;

	हाल -NFS4ERR_MINOR_VERS_MISMATCH:
		status = -EPROTONOSUPPORT;
		अवरोध;

	हाल -EKEYEXPIRED:
	हाल -NFS4ERR_NOT_SAME: /* FixMe: implement recovery
				 * in nfs4_exchange_id */
		status = -EKEYEXPIRED;
		अवरोध;
	शेष:
		pr_warn("NFS: %s unhandled error %d. Exiting with error EIO\n",
				__func__, status);
		status = -EIO;
	पूर्ण

out_unlock:
	mutex_unlock(&nfs_clid_init_mutex);
	dprपूर्णांकk("NFS: %s: status = %d\n", __func__, status);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1
व्योम nfs4_schedule_session_recovery(काष्ठा nfs4_session *session, पूर्णांक err)
अणु
	काष्ठा nfs_client *clp = session->clp;

	चयन (err) अणु
	शेष:
		set_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state);
		अवरोध;
	हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		set_bit(NFS4CLNT_BIND_CONN_TO_SESSION, &clp->cl_state);
	पूर्ण
	nfs4_schedule_state_manager(clp);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_schedule_session_recovery);

व्योम nfs41_notअगरy_server(काष्ठा nfs_client *clp)
अणु
	/* Use CHECK_LEASE to ping the server with a SEQUENCE */
	set_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state);
	nfs4_schedule_state_manager(clp);
पूर्ण

अटल व्योम nfs4_reset_all_state(काष्ठा nfs_client *clp)
अणु
	अगर (test_and_set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state) == 0) अणु
		set_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state);
		clear_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
		nfs4_state_start_reclaim_nograce(clp);
		dprपूर्णांकk("%s: scheduling reset of all state for server %s!\n",
				__func__, clp->cl_hostname);
		nfs4_schedule_state_manager(clp);
	पूर्ण
पूर्ण

अटल व्योम nfs41_handle_server_reboot(काष्ठा nfs_client *clp)
अणु
	अगर (test_and_set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state) == 0) अणु
		nfs4_state_start_reclaim_reboot(clp);
		dprपूर्णांकk("%s: server %s rebooted!\n", __func__,
				clp->cl_hostname);
		nfs4_schedule_state_manager(clp);
	पूर्ण
पूर्ण

अटल व्योम nfs41_handle_all_state_revoked(काष्ठा nfs_client *clp)
अणु
	nfs4_reset_all_state(clp);
	dprपूर्णांकk("%s: state revoked on server %s\n", __func__, clp->cl_hostname);
पूर्ण

अटल व्योम nfs41_handle_some_state_revoked(काष्ठा nfs_client *clp)
अणु
	nfs4_state_start_reclaim_nograce(clp);
	nfs4_schedule_state_manager(clp);

	dprपूर्णांकk("%s: state revoked on server %s\n", __func__, clp->cl_hostname);
पूर्ण

अटल व्योम nfs41_handle_recallable_state_revoked(काष्ठा nfs_client *clp)
अणु
	/* FIXME: For now, we destroy all layouts. */
	pnfs_destroy_all_layouts(clp);
	nfs_test_expired_all_delegations(clp);
	dprपूर्णांकk("%s: Recallable state revoked on server %s!\n", __func__,
			clp->cl_hostname);
पूर्ण

अटल व्योम nfs41_handle_backchannel_fault(काष्ठा nfs_client *clp)
अणु
	set_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state);
	nfs4_schedule_state_manager(clp);

	dprपूर्णांकk("%s: server %s declared a backchannel fault\n", __func__,
			clp->cl_hostname);
पूर्ण

अटल व्योम nfs41_handle_cb_path_करोwn(काष्ठा nfs_client *clp)
अणु
	अगर (test_and_set_bit(NFS4CLNT_BIND_CONN_TO_SESSION,
		&clp->cl_state) == 0)
		nfs4_schedule_state_manager(clp);
पूर्ण

व्योम nfs41_handle_sequence_flag_errors(काष्ठा nfs_client *clp, u32 flags,
		bool recovery)
अणु
	अगर (!flags)
		वापस;

	dprपूर्णांकk("%s: \"%s\" (client ID %llx) flags=0x%08x\n",
		__func__, clp->cl_hostname, clp->cl_clientid, flags);
	/*
	 * If we're called from the state manager thread, then assume we're
	 * alपढ़ोy handling the RECLAIM_NEEDED and/or STATE_REVOKED.
	 * Those flags are expected to reमुख्य set until we're करोne
	 * recovering (see RFC5661, section 18.46.3).
	 */
	अगर (recovery)
		जाओ out_recovery;

	अगर (flags & SEQ4_STATUS_RESTART_RECLAIM_NEEDED)
		nfs41_handle_server_reboot(clp);
	अगर (flags & (SEQ4_STATUS_EXPIRED_ALL_STATE_REVOKED))
		nfs41_handle_all_state_revoked(clp);
	अगर (flags & (SEQ4_STATUS_EXPIRED_SOME_STATE_REVOKED |
			    SEQ4_STATUS_ADMIN_STATE_REVOKED))
		nfs41_handle_some_state_revoked(clp);
	अगर (flags & SEQ4_STATUS_LEASE_MOVED)
		nfs4_schedule_lease_moved_recovery(clp);
	अगर (flags & SEQ4_STATUS_RECALLABLE_STATE_REVOKED)
		nfs41_handle_recallable_state_revoked(clp);
out_recovery:
	अगर (flags & SEQ4_STATUS_BACKCHANNEL_FAULT)
		nfs41_handle_backchannel_fault(clp);
	अन्यथा अगर (flags & (SEQ4_STATUS_CB_PATH_DOWN |
				SEQ4_STATUS_CB_PATH_DOWN_SESSION))
		nfs41_handle_cb_path_करोwn(clp);
पूर्ण

अटल पूर्णांक nfs4_reset_session(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा cred *cred;
	पूर्णांक status;

	अगर (!nfs4_has_session(clp))
		वापस 0;
	status = nfs4_begin_drain_session(clp);
	अगर (status != 0)
		वापस status;
	cred = nfs4_get_clid_cred(clp);
	status = nfs4_proc_destroy_session(clp->cl_session, cred);
	चयन (status) अणु
	हाल 0:
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_DEADSESSION:
		अवरोध;
	हाल -NFS4ERR_BACK_CHAN_BUSY:
	हाल -NFS4ERR_DELAY:
		set_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state);
		status = 0;
		ssleep(1);
		जाओ out;
	शेष:
		status = nfs4_recovery_handle_error(clp, status);
		जाओ out;
	पूर्ण

	स_रखो(clp->cl_session->sess_id.data, 0, NFS4_MAX_SESSIONID_LEN);
	status = nfs4_proc_create_session(clp, cred);
	अगर (status) अणु
		dprपूर्णांकk("%s: session reset failed with status %d for server %s!\n",
			__func__, status, clp->cl_hostname);
		status = nfs4_handle_reclaim_lease_error(clp, status);
		जाओ out;
	पूर्ण
	nfs41_finish_session_reset(clp);
	dprपूर्णांकk("%s: session reset was successful for server %s!\n",
			__func__, clp->cl_hostname);
out:
	put_cred(cred);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_bind_conn_to_session(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा cred *cred;
	पूर्णांक ret;

	अगर (!nfs4_has_session(clp))
		वापस 0;
	ret = nfs4_begin_drain_session(clp);
	अगर (ret != 0)
		वापस ret;
	cred = nfs4_get_clid_cred(clp);
	ret = nfs4_proc_bind_conn_to_session(clp, cred);
	put_cred(cred);
	clear_bit(NFS4CLNT_BIND_CONN_TO_SESSION, &clp->cl_state);
	चयन (ret) अणु
	हाल 0:
		dprपूर्णांकk("%s: bind_conn_to_session was successful for server %s!\n",
			__func__, clp->cl_hostname);
		अवरोध;
	हाल -NFS4ERR_DELAY:
		ssleep(1);
		set_bit(NFS4CLNT_BIND_CONN_TO_SESSION, &clp->cl_state);
		अवरोध;
	शेष:
		वापस nfs4_recovery_handle_error(clp, ret);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nfs4_layoutवापस_any_run(काष्ठा nfs_client *clp)
अणु
	पूर्णांक iomode = 0;

	अगर (test_and_clear_bit(NFS4CLNT_RECALL_ANY_LAYOUT_READ, &clp->cl_state))
		iomode += IOMODE_READ;
	अगर (test_and_clear_bit(NFS4CLNT_RECALL_ANY_LAYOUT_RW, &clp->cl_state))
		iomode += IOMODE_RW;
	/* Note: IOMODE_READ + IOMODE_RW == IOMODE_ANY */
	अगर (iomode) अणु
		pnfs_layout_वापस_unused_byclid(clp, iomode);
		set_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state);
	पूर्ण
पूर्ण
#अन्यथा /* CONFIG_NFS_V4_1 */
अटल पूर्णांक nfs4_reset_session(काष्ठा nfs_client *clp) अणु वापस 0; पूर्ण

अटल पूर्णांक nfs4_bind_conn_to_session(काष्ठा nfs_client *clp)
अणु
	वापस 0;
पूर्ण

अटल व्योम nfs4_layoutवापस_any_run(काष्ठा nfs_client *clp)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल व्योम nfs4_state_manager(काष्ठा nfs_client *clp)
अणु
	पूर्णांक status = 0;
	स्थिर अक्षर *section = "", *section_sep = "";

	/* Ensure exclusive access to NFSv4 state */
	करो अणु
		trace_nfs4_state_mgr(clp);
		clear_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state);
		अगर (test_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state)) अणु
			section = "purge state";
			status = nfs4_purge_lease(clp);
			अगर (status < 0)
				जाओ out_error;
			जारी;
		पूर्ण

		अगर (test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state)) अणु
			section = "lease expired";
			/* We're going to have to re-establish a clientid */
			status = nfs4_reclaim_lease(clp);
			अगर (status < 0)
				जाओ out_error;
			जारी;
		पूर्ण

		/* Initialize or reset the session */
		अगर (test_and_clear_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state)) अणु
			section = "reset session";
			status = nfs4_reset_session(clp);
			अगर (test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state))
				जारी;
			अगर (status < 0)
				जाओ out_error;
		पूर्ण

		/* Send BIND_CONN_TO_SESSION */
		अगर (test_and_clear_bit(NFS4CLNT_BIND_CONN_TO_SESSION,
				&clp->cl_state)) अणु
			section = "bind conn to session";
			status = nfs4_bind_conn_to_session(clp);
			अगर (status < 0)
				जाओ out_error;
			जारी;
		पूर्ण

		अगर (test_and_clear_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state)) अणु
			section = "check lease";
			status = nfs4_check_lease(clp);
			अगर (status < 0)
				जाओ out_error;
			जारी;
		पूर्ण

		अगर (test_and_clear_bit(NFS4CLNT_MOVED, &clp->cl_state)) अणु
			section = "migration";
			status = nfs4_handle_migration(clp);
			अगर (status < 0)
				जाओ out_error;
		पूर्ण

		अगर (test_and_clear_bit(NFS4CLNT_LEASE_MOVED, &clp->cl_state)) अणु
			section = "lease moved";
			status = nfs4_handle_lease_moved(clp);
			अगर (status < 0)
				जाओ out_error;
		पूर्ण

		/* First recover reboot state... */
		अगर (test_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state)) अणु
			section = "reclaim reboot";
			status = nfs4_करो_reclaim(clp,
				clp->cl_mvops->reboot_recovery_ops);
			अगर (status == -EAGAIN)
				जारी;
			अगर (status < 0)
				जाओ out_error;
			nfs4_state_end_reclaim_reboot(clp);
		पूर्ण

		/* Detect expired delegations... */
		अगर (test_and_clear_bit(NFS4CLNT_DELEGATION_EXPIRED, &clp->cl_state)) अणु
			section = "detect expired delegations";
			nfs_reap_expired_delegations(clp);
			जारी;
		पूर्ण

		/* Now recover expired state... */
		अगर (test_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state)) अणु
			section = "reclaim nograce";
			status = nfs4_करो_reclaim(clp,
				clp->cl_mvops->nograce_recovery_ops);
			अगर (status == -EAGAIN)
				जारी;
			अगर (status < 0)
				जाओ out_error;
			clear_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state);
		पूर्ण

		nfs4_end_drain_session(clp);
		nfs4_clear_state_manager_bit(clp);

		अगर (!test_and_set_bit(NFS4CLNT_RECALL_RUNNING, &clp->cl_state)) अणु
			अगर (test_and_clear_bit(NFS4CLNT_DELEGRETURN, &clp->cl_state)) अणु
				nfs_client_वापस_marked_delegations(clp);
				set_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state);
			पूर्ण
			nfs4_layoutवापस_any_run(clp);
			clear_bit(NFS4CLNT_RECALL_RUNNING, &clp->cl_state);
		पूर्ण

		/* Did we race with an attempt to give us more work? */
		अगर (!test_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state))
			वापस;
		अगर (test_and_set_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state) != 0)
			वापस;
	पूर्ण जबतक (refcount_पढ़ो(&clp->cl_count) > 1 && !संकेतled());
	जाओ out_drain;

out_error:
	अगर (म_माप(section))
		section_sep = ": ";
	trace_nfs4_state_mgr_failed(clp, section, status);
	pr_warn_ratelimited("NFS: state manager%s%s failed on NFSv4 server %s"
			" with error %d\n", section_sep, section,
			clp->cl_hostname, -status);
	ssleep(1);
out_drain:
	nfs4_end_drain_session(clp);
	nfs4_clear_state_manager_bit(clp);
पूर्ण

अटल पूर्णांक nfs4_run_state_manager(व्योम *ptr)
अणु
	काष्ठा nfs_client *clp = ptr;

	allow_संकेत(SIGKILL);
	nfs4_state_manager(clp);
	nfs_put_client(clp);
	module_put_and_निकास(0);
	वापस 0;
पूर्ण
