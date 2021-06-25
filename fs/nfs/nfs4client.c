<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#समावेश <linux/module.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/sunrpc/bc_xprt.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश "internal.h"
#समावेश "callback.h"
#समावेश "delegation.h"
#समावेश "nfs4session.h"
#समावेश "nfs4idmap.h"
#समावेश "pnfs.h"
#समावेश "netns.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_CLIENT

/*
 * Get a unique NFSv4.0 callback identअगरier which will be used
 * by the V4.0 callback service to lookup the nfs_client काष्ठा
 */
अटल पूर्णांक nfs_get_cb_ident_idr(काष्ठा nfs_client *clp, पूर्णांक minorversion)
अणु
	पूर्णांक ret = 0;
	काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);

	अगर (clp->rpc_ops->version != 4 || minorversion != 0)
		वापस ret;
	idr_preload(GFP_KERNEL);
	spin_lock(&nn->nfs_client_lock);
	ret = idr_alloc(&nn->cb_ident_idr, clp, 1, 0, GFP_NOWAIT);
	अगर (ret >= 0)
		clp->cl_cb_ident = ret;
	spin_unlock(&nn->nfs_client_lock);
	idr_preload_end();
	वापस ret < 0 ? ret : 0;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1
/*
 * Per auth flavor data server rpc clients
 */
काष्ठा nfs4_ds_server अणु
	काष्ठा list_head	list;   /* ds_clp->cl_ds_clients */
	काष्ठा rpc_clnt		*rpc_clnt;
पूर्ण;

/**
 * nfs4_find_ds_client - Common lookup हाल क्रम DS I/O
 * @ds_clp: poपूर्णांकer to the DS's nfs_client
 * @flavor: rpc auth flavour to match
 */
अटल काष्ठा nfs4_ds_server *
nfs4_find_ds_client(काष्ठा nfs_client *ds_clp, rpc_authflavor_t flavor)
अणु
	काष्ठा nfs4_ds_server *dss;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(dss, &ds_clp->cl_ds_clients, list) अणु
		अगर (dss->rpc_clnt->cl_auth->au_flavor != flavor)
			जारी;
		जाओ out;
	पूर्ण
	dss = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस dss;
पूर्ण

अटल काष्ठा nfs4_ds_server *
nfs4_add_ds_client(काष्ठा nfs_client *ds_clp, rpc_authflavor_t flavor,
			   काष्ठा nfs4_ds_server *new)
अणु
	काष्ठा nfs4_ds_server *dss;

	spin_lock(&ds_clp->cl_lock);
	list_क्रम_each_entry(dss, &ds_clp->cl_ds_clients, list) अणु
		अगर (dss->rpc_clnt->cl_auth->au_flavor != flavor)
			जारी;
		जाओ out;
	पूर्ण
	अगर (new)
		list_add_rcu(&new->list, &ds_clp->cl_ds_clients);
	dss = new;
out:
	spin_unlock(&ds_clp->cl_lock); /* need some lock to protect list */
	वापस dss;
पूर्ण

अटल काष्ठा nfs4_ds_server *
nfs4_alloc_ds_server(काष्ठा nfs_client *ds_clp, rpc_authflavor_t flavor)
अणु
	काष्ठा nfs4_ds_server *dss;

	dss = kदो_स्मृति(माप(*dss), GFP_NOFS);
	अगर (dss == शून्य)
		वापस ERR_PTR(-ENOMEM);

	dss->rpc_clnt = rpc_clone_client_set_auth(ds_clp->cl_rpcclient, flavor);
	अगर (IS_ERR(dss->rpc_clnt)) अणु
		पूर्णांक err = PTR_ERR(dss->rpc_clnt);
		kमुक्त (dss);
		वापस ERR_PTR(err);
	पूर्ण
	INIT_LIST_HEAD(&dss->list);

	वापस dss;
पूर्ण

अटल व्योम
nfs4_मुक्त_ds_server(काष्ठा nfs4_ds_server *dss)
अणु
	rpc_release_client(dss->rpc_clnt);
	kमुक्त(dss);
पूर्ण

/**
 * nfs4_find_or_create_ds_client - Find or create a DS rpc client
 * @ds_clp: poपूर्णांकer to the DS's nfs_client
 * @inode: poपूर्णांकer to the inode
 *
 * Find or create a DS rpc client with th MDS server rpc client auth flavor
 * in the nfs_client cl_ds_clients list.
 */
काष्ठा rpc_clnt *
nfs4_find_or_create_ds_client(काष्ठा nfs_client *ds_clp, काष्ठा inode *inode)
अणु
	काष्ठा nfs4_ds_server *dss, *new;
	rpc_authflavor_t flavor = NFS_SERVER(inode)->client->cl_auth->au_flavor;

	dss = nfs4_find_ds_client(ds_clp, flavor);
	अगर (dss != शून्य)
		जाओ out;
	new = nfs4_alloc_ds_server(ds_clp, flavor);
	अगर (IS_ERR(new))
		वापस ERR_CAST(new);
	dss = nfs4_add_ds_client(ds_clp, flavor, new);
	अगर (dss != new)
		nfs4_मुक्त_ds_server(new);
out:
	वापस dss->rpc_clnt;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_find_or_create_ds_client);

अटल व्योम
nfs4_shutकरोwn_ds_clients(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_ds_server *dss;

	जबतक (!list_empty(&clp->cl_ds_clients)) अणु
		dss = list_entry(clp->cl_ds_clients.next,
					काष्ठा nfs4_ds_server, list);
		list_del(&dss->list);
		rpc_shutकरोwn_client(dss->rpc_clnt);
		kमुक्त (dss);
	पूर्ण
पूर्ण

अटल व्योम
nfs4_cleanup_callback(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_copy_state *cp_state;

	जबतक (!list_empty(&clp->pending_cb_stateids)) अणु
		cp_state = list_entry(clp->pending_cb_stateids.next,
					काष्ठा nfs4_copy_state, copies);
		list_del(&cp_state->copies);
		kमुक्त(cp_state);
	पूर्ण
पूर्ण

व्योम nfs41_shutकरोwn_client(काष्ठा nfs_client *clp)
अणु
	अगर (nfs4_has_session(clp)) अणु
		nfs4_cleanup_callback(clp);
		nfs4_shutकरोwn_ds_clients(clp);
		nfs4_destroy_session(clp->cl_session);
		nfs4_destroy_clientid(clp);
	पूर्ण

पूर्ण
#पूर्ण_अगर	/* CONFIG_NFS_V4_1 */

व्योम nfs40_shutकरोwn_client(काष्ठा nfs_client *clp)
अणु
	अगर (clp->cl_slot_tbl) अणु
		nfs4_shutकरोwn_slot_table(clp->cl_slot_tbl);
		kमुक्त(clp->cl_slot_tbl);
	पूर्ण
पूर्ण

काष्ठा nfs_client *nfs4_alloc_client(स्थिर काष्ठा nfs_client_initdata *cl_init)
अणु
	पूर्णांक err;
	काष्ठा nfs_client *clp = nfs_alloc_client(cl_init);
	अगर (IS_ERR(clp))
		वापस clp;

	err = nfs_get_cb_ident_idr(clp, cl_init->minorversion);
	अगर (err)
		जाओ error;

	अगर (cl_init->minorversion > NFS4_MAX_MINOR_VERSION) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	spin_lock_init(&clp->cl_lock);
	INIT_DELAYED_WORK(&clp->cl_renewd, nfs4_renew_state);
	INIT_LIST_HEAD(&clp->cl_ds_clients);
	rpc_init_रुको_queue(&clp->cl_rpcरुकोq, "NFS client");
	clp->cl_state = 1 << NFS4CLNT_LEASE_EXPIRED;
	clp->cl_mvops = nfs_v4_minor_ops[cl_init->minorversion];
	clp->cl_mig_gen = 1;
#अगर IS_ENABLED(CONFIG_NFS_V4_1)
	init_रुकोqueue_head(&clp->cl_lock_रुकोq);
#पूर्ण_अगर
	INIT_LIST_HEAD(&clp->pending_cb_stateids);
	वापस clp;

error:
	nfs_मुक्त_client(clp);
	वापस ERR_PTR(err);
पूर्ण

/*
 * Destroy the NFS4 callback service
 */
अटल व्योम nfs4_destroy_callback(काष्ठा nfs_client *clp)
अणु
	अगर (__test_and_clear_bit(NFS_CS_CALLBACK, &clp->cl_res_state))
		nfs_callback_करोwn(clp->cl_mvops->minor_version, clp->cl_net);
पूर्ण

अटल व्योम nfs4_shutकरोwn_client(काष्ठा nfs_client *clp)
अणु
	अगर (__test_and_clear_bit(NFS_CS_RENEWD, &clp->cl_res_state))
		nfs4_समाप्त_renewd(clp);
	clp->cl_mvops->shutकरोwn_client(clp);
	nfs4_destroy_callback(clp);
	अगर (__test_and_clear_bit(NFS_CS_IDMAP, &clp->cl_res_state))
		nfs_idmap_delete(clp);

	rpc_destroy_रुको_queue(&clp->cl_rpcरुकोq);
	kमुक्त(clp->cl_serverowner);
	kमुक्त(clp->cl_serverscope);
	kमुक्त(clp->cl_implid);
	kमुक्त(clp->cl_owner_id);
पूर्ण

व्योम nfs4_मुक्त_client(काष्ठा nfs_client *clp)
अणु
	nfs4_shutकरोwn_client(clp);
	nfs_मुक्त_client(clp);
पूर्ण

/*
 * Initialize the NFS4 callback service
 */
अटल पूर्णांक nfs4_init_callback(काष्ठा nfs_client *clp)
अणु
	काष्ठा rpc_xprt *xprt;
	पूर्णांक error;

	xprt = rcu_dereference_raw(clp->cl_rpcclient->cl_xprt);

	अगर (nfs4_has_session(clp)) अणु
		error = xprt_setup_backchannel(xprt, NFS41_BC_MIN_CALLBACKS);
		अगर (error < 0)
			वापस error;
	पूर्ण

	error = nfs_callback_up(clp->cl_mvops->minor_version, xprt);
	अगर (error < 0) अणु
		dprपूर्णांकk("%s: failed to start callback. Error = %d\n",
			__func__, error);
		वापस error;
	पूर्ण
	__set_bit(NFS_CS_CALLBACK, &clp->cl_res_state);

	वापस 0;
पूर्ण

/**
 * nfs40_init_client - nfs_client initialization tasks क्रम NFSv4.0
 * @clp: nfs_client to initialize
 *
 * Returns zero on success, or a negative त्रुटि_सं अगर some error occurred.
 */
पूर्णांक nfs40_init_client(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_slot_table *tbl;
	पूर्णांक ret;

	tbl = kzalloc(माप(*tbl), GFP_NOFS);
	अगर (tbl == शून्य)
		वापस -ENOMEM;

	ret = nfs4_setup_slot_table(tbl, NFS4_MAX_SLOT_TABLE,
					"NFSv4.0 transport Slot table");
	अगर (ret) अणु
		kमुक्त(tbl);
		वापस ret;
	पूर्ण

	clp->cl_slot_tbl = tbl;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)

/**
 * nfs41_init_client - nfs_client initialization tasks क्रम NFSv4.1+
 * @clp: nfs_client to initialize
 *
 * Returns zero on success, or a negative त्रुटि_सं अगर some error occurred.
 */
पूर्णांक nfs41_init_client(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs4_session *session = शून्य;

	/*
	 * Create the session and mark it expired.
	 * When a SEQUENCE operation encounters the expired session
	 * it will करो session recovery to initialize it.
	 */
	session = nfs4_alloc_session(clp);
	अगर (!session)
		वापस -ENOMEM;

	clp->cl_session = session;

	/*
	 * The create session reply races with the server back
	 * channel probe. Mark the client NFS_CS_SESSION_INITING
	 * so that the client back channel can find the
	 * nfs_client काष्ठा
	 */
	nfs_mark_client_पढ़ोy(clp, NFS_CS_SESSION_INITING);
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_NFS_V4_1 */

/*
 * Initialize the minor version specअगरic parts of an NFS4 client record
 */
अटल पूर्णांक nfs4_init_client_minor_version(काष्ठा nfs_client *clp)
अणु
	पूर्णांक ret;

	ret = clp->cl_mvops->init_client(clp);
	अगर (ret)
		वापस ret;
	वापस nfs4_init_callback(clp);
पूर्ण

/**
 * nfs4_init_client - Initialise an NFS4 client record
 *
 * @clp: nfs_client to initialise
 * @cl_init: poपूर्णांकer to nfs_client_initdata
 *
 * Returns poपूर्णांकer to an NFS client, or an ERR_PTR value.
 */
काष्ठा nfs_client *nfs4_init_client(काष्ठा nfs_client *clp,
				    स्थिर काष्ठा nfs_client_initdata *cl_init)
अणु
	अक्षर buf[INET6_ADDRSTRLEN + 1];
	स्थिर अक्षर *ip_addr = cl_init->ip_addr;
	काष्ठा nfs_client *old;
	पूर्णांक error;

	अगर (clp->cl_cons_state == NFS_CS_READY)
		/* the client is initialised alपढ़ोy */
		वापस clp;

	/* Check NFS protocol revision and initialize RPC op vector */
	clp->rpc_ops = &nfs_v4_clientops;

	अगर (clp->cl_minorversion != 0)
		__set_bit(NFS_CS_INFINITE_SLOTS, &clp->cl_flags);
	__set_bit(NFS_CS_DISCRTRY, &clp->cl_flags);
	__set_bit(NFS_CS_NO_RETRANS_TIMEOUT, &clp->cl_flags);

	error = nfs_create_rpc_client(clp, cl_init, RPC_AUTH_GSS_KRB5I);
	अगर (error == -EINVAL)
		error = nfs_create_rpc_client(clp, cl_init, RPC_AUTH_UNIX);
	अगर (error < 0)
		जाओ error;

	/* If no clientaddr= option was specअगरied, find a usable cb address */
	अगर (ip_addr == शून्य) अणु
		काष्ठा sockaddr_storage cb_addr;
		काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&cb_addr;

		error = rpc_localaddr(clp->cl_rpcclient, sap, माप(cb_addr));
		अगर (error < 0)
			जाओ error;
		error = rpc_ntop(sap, buf, माप(buf));
		अगर (error < 0)
			जाओ error;
		ip_addr = (स्थिर अक्षर *)buf;
	पूर्ण
	strlcpy(clp->cl_ipaddr, ip_addr, माप(clp->cl_ipaddr));

	error = nfs_idmap_new(clp);
	अगर (error < 0) अणु
		dprपूर्णांकk("%s: failed to create idmapper. Error = %d\n",
			__func__, error);
		जाओ error;
	पूर्ण
	__set_bit(NFS_CS_IDMAP, &clp->cl_res_state);

	error = nfs4_init_client_minor_version(clp);
	अगर (error < 0)
		जाओ error;

	error = nfs4_discover_server_trunking(clp, &old);
	अगर (error < 0)
		जाओ error;

	अगर (clp != old) अणु
		clp->cl_preserve_clid = true;
		/*
		 * Mark the client as having failed initialization so other
		 * processes walking the nfs_client_list in nfs_match_client()
		 * won't try to use it.
		 */
		nfs_mark_client_पढ़ोy(clp, -EPERM);
	पूर्ण
	clear_bit(NFS_CS_TSM_POSSIBLE, &clp->cl_flags);
	nfs_put_client(clp);
	वापस old;

error:
	nfs_mark_client_पढ़ोy(clp, error);
	nfs_put_client(clp);
	वापस ERR_PTR(error);
पूर्ण

/*
 * SETCLIENTID just did a callback update with the callback ident in
 * "drop," but server trunking discovery claims "drop" and "keep" are
 * actually the same server.  Swap the callback IDs so that "keep"
 * will जारी to use the callback ident the server now knows about,
 * and so that "keep"'s original callback ident is destroyed when
 * "drop" is मुक्तd.
 */
अटल व्योम nfs4_swap_callback_idents(काष्ठा nfs_client *keep,
				      काष्ठा nfs_client *drop)
अणु
	काष्ठा nfs_net *nn = net_generic(keep->cl_net, nfs_net_id);
	अचिन्हित पूर्णांक save = keep->cl_cb_ident;

	अगर (keep->cl_cb_ident == drop->cl_cb_ident)
		वापस;

	dprपूर्णांकk("%s: keeping callback ident %u and dropping ident %u\n",
		__func__, keep->cl_cb_ident, drop->cl_cb_ident);

	spin_lock(&nn->nfs_client_lock);

	idr_replace(&nn->cb_ident_idr, keep, drop->cl_cb_ident);
	keep->cl_cb_ident = drop->cl_cb_ident;

	idr_replace(&nn->cb_ident_idr, drop, save);
	drop->cl_cb_ident = save;

	spin_unlock(&nn->nfs_client_lock);
पूर्ण

अटल bool nfs4_match_client_owner_id(स्थिर काष्ठा nfs_client *clp1,
		स्थिर काष्ठा nfs_client *clp2)
अणु
	अगर (clp1->cl_owner_id == शून्य || clp2->cl_owner_id == शून्य)
		वापस true;
	वापस म_भेद(clp1->cl_owner_id, clp2->cl_owner_id) == 0;
पूर्ण

अटल bool nfs4_same_verअगरier(nfs4_verअगरier *v1, nfs4_verअगरier *v2)
अणु
	वापस स_भेद(v1->data, v2->data, माप(v1->data)) == 0;
पूर्ण

अटल पूर्णांक nfs4_match_client(काष्ठा nfs_client  *pos,  काष्ठा nfs_client *new,
			     काष्ठा nfs_client **prev, काष्ठा nfs_net *nn)
अणु
	पूर्णांक status;

	अगर (pos->rpc_ops != new->rpc_ops)
		वापस 1;

	अगर (pos->cl_minorversion != new->cl_minorversion)
		वापस 1;

	/* If "pos" isn't marked ready, we can't trust the
	 * reमुख्यing fields in "pos", especially the client
	 * ID and serverowner fields.  Wait क्रम CREATE_SESSION
	 * to finish. */
	अगर (pos->cl_cons_state > NFS_CS_READY) अणु
		refcount_inc(&pos->cl_count);
		spin_unlock(&nn->nfs_client_lock);

		nfs_put_client(*prev);
		*prev = pos;

		status = nfs_रुको_client_init_complete(pos);
		spin_lock(&nn->nfs_client_lock);

		अगर (status < 0)
			वापस status;
	पूर्ण

	अगर (pos->cl_cons_state != NFS_CS_READY)
		वापस 1;

	अगर (pos->cl_clientid != new->cl_clientid)
		वापस 1;

	/* NFSv4.1 always uses the unअगरorm string, however someone
	 * might चयन the uniquअगरier string on us.
	 */
	अगर (!nfs4_match_client_owner_id(pos, new))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * nfs40_walk_client_list - Find server that recognizes a client ID
 *
 * @new: nfs_client with client ID to test
 * @result: OUT: found nfs_client, or new
 * @cred: credential to use क्रम trunking test
 *
 * Returns zero, a negative त्रुटि_सं, or a negative NFS4ERR status.
 * If zero is वापसed, an nfs_client poपूर्णांकer is planted in "result."
 *
 * NB: nfs40_walk_client_list() relies on the new nfs_client being
 *     the last nfs_client on the list.
 */
पूर्णांक nfs40_walk_client_list(काष्ठा nfs_client *new,
			   काष्ठा nfs_client **result,
			   स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_net *nn = net_generic(new->cl_net, nfs_net_id);
	काष्ठा nfs_client *pos, *prev = शून्य;
	काष्ठा nfs4_setclientid_res clid = अणु
		.clientid	= new->cl_clientid,
		.confirm	= new->cl_confirm,
	पूर्ण;
	पूर्णांक status = -NFS4ERR_STALE_CLIENTID;

	spin_lock(&nn->nfs_client_lock);
	list_क्रम_each_entry(pos, &nn->nfs_client_list, cl_share_link) अणु

		अगर (pos == new)
			जाओ found;

		status = nfs4_match_client(pos, new, &prev, nn);
		अगर (status < 0)
			जाओ out_unlock;
		अगर (status != 0)
			जारी;
		/*
		 * We just sent a new SETCLIENTID, which should have
		 * caused the server to वापस a new cl_confirm.  So अगर
		 * cl_confirm is the same, then this is a dअगरferent
		 * server that just वापसed the same cl_confirm by
		 * coincidence:
		 */
		अगर ((new != pos) && nfs4_same_verअगरier(&pos->cl_confirm,
						       &new->cl_confirm))
			जारी;
		/*
		 * But अगर the cl_confirm's are dअगरferent, then the only
		 * way that a SETCLIENTID_CONFIRM to pos can succeed is
		 * अगर new and pos poपूर्णांक to the same server:
		 */
found:
		refcount_inc(&pos->cl_count);
		spin_unlock(&nn->nfs_client_lock);

		nfs_put_client(prev);
		prev = pos;

		status = nfs4_proc_setclientid_confirm(pos, &clid, cred);
		चयन (status) अणु
		हाल -NFS4ERR_STALE_CLIENTID:
			अवरोध;
		हाल 0:
			nfs4_swap_callback_idents(pos, new);
			pos->cl_confirm = new->cl_confirm;
			nfs_mark_client_पढ़ोy(pos, NFS_CS_READY);

			prev = शून्य;
			*result = pos;
			जाओ out;
		हाल -ERESTARTSYS:
		हाल -ETIMEDOUT:
			/* The callback path may have been inadvertently
			 * changed. Schedule recovery!
			 */
			nfs4_schedule_path_करोwn_recovery(pos);
			जाओ out;
		शेष:
			जाओ out;
		पूर्ण

		spin_lock(&nn->nfs_client_lock);
	पूर्ण
out_unlock:
	spin_unlock(&nn->nfs_client_lock);

	/* No match found. The server lost our clientid */
out:
	nfs_put_client(prev);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1
/*
 * Returns true अगर the server major ids match
 */
bool
nfs4_check_serverowner_major_id(काष्ठा nfs41_server_owner *o1,
				काष्ठा nfs41_server_owner *o2)
अणु
	अगर (o1->major_id_sz != o2->major_id_sz)
		वापस false;
	वापस स_भेद(o1->major_id, o2->major_id, o1->major_id_sz) == 0;
पूर्ण

/*
 * Returns true अगर the server scopes match
 */
अटल bool
nfs4_check_server_scope(काष्ठा nfs41_server_scope *s1,
			काष्ठा nfs41_server_scope *s2)
अणु
	अगर (s1->server_scope_sz != s2->server_scope_sz)
		वापस false;
	वापस स_भेद(s1->server_scope, s2->server_scope,
					s1->server_scope_sz) == 0;
पूर्ण

/**
 * nfs4_detect_session_trunking - Checks क्रम session trunking.
 * @clp:    original mount nfs_client
 * @res:    result काष्ठाure from an exchange_id using the original mount
 *          nfs_client with a new multi_addr transport
 * @xprt:   poपूर्णांकer to the transport to add.
 *
 * Called after a successful EXCHANGE_ID on a multi-addr connection.
 * Upon success, add the transport.
 *
 * Returns zero on success, otherwise -EINVAL
 *
 * Note: since the exchange_id क्रम the new multi_addr transport uses the
 * same nfs_client from the original mount, the cl_owner_id is reused,
 * so eir_clientowner is the same.
 */
पूर्णांक nfs4_detect_session_trunking(काष्ठा nfs_client *clp,
				 काष्ठा nfs41_exchange_id_res *res,
				 काष्ठा rpc_xprt *xprt)
अणु
	/* Check eir_clientid */
	अगर (clp->cl_clientid != res->clientid)
		जाओ out_err;

	/* Check eir_server_owner so_major_id */
	अगर (!nfs4_check_serverowner_major_id(clp->cl_serverowner,
					     res->server_owner))
		जाओ out_err;

	/* Check eir_server_owner so_minor_id */
	अगर (clp->cl_serverowner->minor_id != res->server_owner->minor_id)
		जाओ out_err;

	/* Check eir_server_scope */
	अगर (!nfs4_check_server_scope(clp->cl_serverscope, res->server_scope))
		जाओ out_err;

	pr_info("NFS:  %s: Session trunking succeeded for %s\n",
		clp->cl_hostname,
		xprt->address_strings[RPC_DISPLAY_ADDR]);

	वापस 0;
out_err:
	pr_info("NFS:  %s: Session trunking failed for %s\n", clp->cl_hostname,
		xprt->address_strings[RPC_DISPLAY_ADDR]);

	वापस -EINVAL;
पूर्ण

/**
 * nfs41_walk_client_list - Find nfs_client that matches a client/server owner
 *
 * @new: nfs_client with client ID to test
 * @result: OUT: found nfs_client, or new
 * @cred: credential to use क्रम trunking test
 *
 * Returns zero, a negative त्रुटि_सं, or a negative NFS4ERR status.
 * If zero is वापसed, an nfs_client poपूर्णांकer is planted in "result."
 *
 * NB: nfs41_walk_client_list() relies on the new nfs_client being
 *     the last nfs_client on the list.
 */
पूर्णांक nfs41_walk_client_list(काष्ठा nfs_client *new,
			   काष्ठा nfs_client **result,
			   स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_net *nn = net_generic(new->cl_net, nfs_net_id);
	काष्ठा nfs_client *pos, *prev = शून्य;
	पूर्णांक status = -NFS4ERR_STALE_CLIENTID;

	spin_lock(&nn->nfs_client_lock);
	list_क्रम_each_entry(pos, &nn->nfs_client_list, cl_share_link) अणु

		अगर (pos == new)
			जाओ found;

		status = nfs4_match_client(pos, new, &prev, nn);
		अगर (status < 0)
			जाओ out;
		अगर (status != 0)
			जारी;

		/*
		 * Note that session trunking is just a special subहाल of
		 * client id trunking. In either हाल, we want to fall back
		 * to using the existing nfs_client.
		 */
		अगर (!nfs4_check_serverowner_major_id(pos->cl_serverowner,
						     new->cl_serverowner))
			जारी;

found:
		refcount_inc(&pos->cl_count);
		*result = pos;
		status = 0;
		अवरोध;
	पूर्ण

out:
	spin_unlock(&nn->nfs_client_lock);
	nfs_put_client(prev);
	वापस status;
पूर्ण
#पूर्ण_अगर	/* CONFIG_NFS_V4_1 */

अटल व्योम nfs4_destroy_server(काष्ठा nfs_server *server)
अणु
	LIST_HEAD(मुक्तme);

	nfs_server_वापस_all_delegations(server);
	unset_pnfs_layoutdriver(server);
	nfs4_purge_state_owners(server, &मुक्तme);
	nfs4_मुक्त_state_owners(&मुक्तme);
पूर्ण

/*
 * NFSv4.0 callback thपढ़ो helper
 *
 * Find a client by callback identअगरier
 */
काष्ठा nfs_client *
nfs4_find_client_ident(काष्ठा net *net, पूर्णांक cb_ident)
अणु
	काष्ठा nfs_client *clp;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	spin_lock(&nn->nfs_client_lock);
	clp = idr_find(&nn->cb_ident_idr, cb_ident);
	अगर (clp)
		refcount_inc(&clp->cl_count);
	spin_unlock(&nn->nfs_client_lock);
	वापस clp;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
/* Common match routine क्रम v4.0 and v4.1 callback services */
अटल bool nfs4_cb_match_client(स्थिर काष्ठा sockaddr *addr,
		काष्ठा nfs_client *clp, u32 minorversion)
अणु
	काष्ठा sockaddr *clap = (काष्ठा sockaddr *)&clp->cl_addr;

	/* Don't match clients that failed to initialise */
	अगर (!(clp->cl_cons_state == NFS_CS_READY ||
	    clp->cl_cons_state == NFS_CS_SESSION_INITING))
		वापस false;

	smp_rmb();

	/* Match the version and minorversion */
	अगर (clp->rpc_ops->version != 4 ||
	    clp->cl_minorversion != minorversion)
		वापस false;

	/* Match only the IP address, not the port number */
	वापस rpc_cmp_addr(addr, clap);
पूर्ण

/*
 * NFSv4.1 callback thपढ़ो helper
 * For CB_COMPOUND calls, find a client by IP address, protocol version,
 * minorversion, and sessionID
 *
 * Returns शून्य अगर no such client
 */
काष्ठा nfs_client *
nfs4_find_client_sessionid(काष्ठा net *net, स्थिर काष्ठा sockaddr *addr,
			   काष्ठा nfs4_sessionid *sid, u32 minorversion)
अणु
	काष्ठा nfs_client *clp;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	spin_lock(&nn->nfs_client_lock);
	list_क्रम_each_entry(clp, &nn->nfs_client_list, cl_share_link) अणु
		अगर (!nfs4_cb_match_client(addr, clp, minorversion))
			जारी;

		अगर (!nfs4_has_session(clp))
			जारी;

		/* Match sessionid*/
		अगर (स_भेद(clp->cl_session->sess_id.data,
		    sid->data, NFS4_MAX_SESSIONID_LEN) != 0)
			जारी;

		refcount_inc(&clp->cl_count);
		spin_unlock(&nn->nfs_client_lock);
		वापस clp;
	पूर्ण
	spin_unlock(&nn->nfs_client_lock);
	वापस शून्य;
पूर्ण

#अन्यथा /* CONFIG_NFS_V4_1 */

काष्ठा nfs_client *
nfs4_find_client_sessionid(काष्ठा net *net, स्थिर काष्ठा sockaddr *addr,
			   काष्ठा nfs4_sessionid *sid, u32 minorversion)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

/*
 * Set up an NFS4 client
 */
अटल पूर्णांक nfs4_set_client(काष्ठा nfs_server *server,
		स्थिर अक्षर *hostname,
		स्थिर काष्ठा sockaddr *addr,
		स्थिर माप_प्रकार addrlen,
		स्थिर अक्षर *ip_addr,
		पूर्णांक proto, स्थिर काष्ठा rpc_समयout *समयparms,
		u32 minorversion, अचिन्हित पूर्णांक nconnect,
		काष्ठा net *net)
अणु
	काष्ठा nfs_client_initdata cl_init = अणु
		.hostname = hostname,
		.addr = addr,
		.addrlen = addrlen,
		.ip_addr = ip_addr,
		.nfs_mod = &nfs_v4,
		.proto = proto,
		.minorversion = minorversion,
		.net = net,
		.समयparms = समयparms,
		.cred = server->cred,
	पूर्ण;
	काष्ठा nfs_client *clp;

	अगर (minorversion == 0)
		__set_bit(NFS_CS_REUSEPORT, &cl_init.init_flags);
	अगर (proto == XPRT_TRANSPORT_TCP)
		cl_init.nconnect = nconnect;

	अगर (server->flags & NFS_MOUNT_NORESVPORT)
		__set_bit(NFS_CS_NORESVPORT, &cl_init.init_flags);
	अगर (server->options & NFS_OPTION_MIGRATION)
		__set_bit(NFS_CS_MIGRATION, &cl_init.init_flags);
	अगर (test_bit(NFS_MIG_TSM_POSSIBLE, &server->mig_status))
		__set_bit(NFS_CS_TSM_POSSIBLE, &cl_init.init_flags);
	server->port = rpc_get_port(addr);

	/* Allocate or find a client reference we can use */
	clp = nfs_get_client(&cl_init);
	अगर (IS_ERR(clp))
		वापस PTR_ERR(clp);

	अगर (server->nfs_client == clp) अणु
		nfs_put_client(clp);
		वापस -ELOOP;
	पूर्ण

	/*
	 * Query क्रम the lease समय on clientid setup or renewal
	 *
	 * Note that this will be set on nfs_clients that were created
	 * only क्रम the DS role and did not set this bit, but now will
	 * serve a dual role.
	 */
	set_bit(NFS_CS_CHECK_LEASE_TIME, &clp->cl_res_state);

	server->nfs_client = clp;
	वापस 0;
पूर्ण

/*
 * Set up a pNFS Data Server client.
 *
 * Return any existing nfs_client that matches server address,port,version
 * and minorversion.
 *
 * For a new nfs_client, use a soft mount (शेष), a low retrans and a
 * low समयout पूर्णांकerval so that अगर a connection is lost, we retry through
 * the MDS.
 */
काष्ठा nfs_client *nfs4_set_ds_client(काष्ठा nfs_server *mds_srv,
		स्थिर काष्ठा sockaddr *ds_addr, पूर्णांक ds_addrlen,
		पूर्णांक ds_proto, अचिन्हित पूर्णांक ds_समयo, अचिन्हित पूर्णांक ds_retrans,
		u32 minor_version)
अणु
	काष्ठा rpc_समयout ds_समयout;
	काष्ठा nfs_client *mds_clp = mds_srv->nfs_client;
	काष्ठा nfs_client_initdata cl_init = अणु
		.addr = ds_addr,
		.addrlen = ds_addrlen,
		.nodename = mds_clp->cl_rpcclient->cl_nodename,
		.ip_addr = mds_clp->cl_ipaddr,
		.nfs_mod = &nfs_v4,
		.proto = ds_proto,
		.minorversion = minor_version,
		.net = mds_clp->cl_net,
		.समयparms = &ds_समयout,
		.cred = mds_srv->cred,
	पूर्ण;
	अक्षर buf[INET6_ADDRSTRLEN + 1];

	अगर (rpc_ntop(ds_addr, buf, माप(buf)) <= 0)
		वापस ERR_PTR(-EINVAL);
	cl_init.hostname = buf;

	अगर (mds_clp->cl_nconnect > 1 && ds_proto == XPRT_TRANSPORT_TCP)
		cl_init.nconnect = mds_clp->cl_nconnect;

	अगर (mds_srv->flags & NFS_MOUNT_NORESVPORT)
		__set_bit(NFS_CS_NORESVPORT, &cl_init.init_flags);

	/*
	 * Set an authflavor equual to the MDS value. Use the MDS nfs_client
	 * cl_ipaddr so as to use the same EXCHANGE_ID co_ownerid as the MDS
	 * (section 13.1 RFC 5661).
	 */
	nfs_init_समयout_values(&ds_समयout, ds_proto, ds_समयo, ds_retrans);
	वापस nfs_get_client(&cl_init);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_set_ds_client);

/*
 * Session has been established, and the client marked पढ़ोy.
 * Limit the mount rsize, wsize and dtsize using negotiated क्रमe
 * channel attributes.
 */
अटल व्योम nfs4_session_limit_rwsize(काष्ठा nfs_server *server)
अणु
#अगर_घोषित CONFIG_NFS_V4_1
	काष्ठा nfs4_session *sess;
	u32 server_resp_sz;
	u32 server_rqst_sz;

	अगर (!nfs4_has_session(server->nfs_client))
		वापस;
	sess = server->nfs_client->cl_session;
	server_resp_sz = sess->fc_attrs.max_resp_sz - nfs41_maxपढ़ो_overhead;
	server_rqst_sz = sess->fc_attrs.max_rqst_sz - nfs41_maxग_लिखो_overhead;

	अगर (server->dtsize > server_resp_sz)
		server->dtsize = server_resp_sz;
	अगर (server->rsize > server_resp_sz)
		server->rsize = server_resp_sz;
	अगर (server->wsize > server_rqst_sz)
		server->wsize = server_rqst_sz;
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
पूर्ण

/*
 * Limit xattr sizes using the channel attributes.
 */
अटल व्योम nfs4_session_limit_xasize(काष्ठा nfs_server *server)
अणु
#अगर_घोषित CONFIG_NFS_V4_2
	काष्ठा nfs4_session *sess;
	u32 server_gxa_sz;
	u32 server_sxa_sz;
	u32 server_lxa_sz;

	अगर (!nfs4_has_session(server->nfs_client))
		वापस;

	sess = server->nfs_client->cl_session;

	server_gxa_sz = sess->fc_attrs.max_resp_sz - nfs42_maxgetxattr_overhead;
	server_sxa_sz = sess->fc_attrs.max_rqst_sz - nfs42_maxsetxattr_overhead;
	server_lxa_sz = sess->fc_attrs.max_resp_sz -
	    nfs42_maxlistxattrs_overhead;

	अगर (server->gxasize > server_gxa_sz)
		server->gxasize = server_gxa_sz;
	अगर (server->sxasize > server_sxa_sz)
		server->sxasize = server_sxa_sz;
	अगर (server->lxasize > server_lxa_sz)
		server->lxasize = server_lxa_sz;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक nfs4_server_common_setup(काष्ठा nfs_server *server,
		काष्ठा nfs_fh *mntfh, bool auth_probe)
अणु
	काष्ठा nfs_fattr *fattr;
	पूर्णांक error;

	/* data servers support only a subset of NFSv4.1 */
	अगर (is_ds_only_client(server->nfs_client))
		वापस -EPROTONOSUPPORT;

	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य)
		वापस -ENOMEM;

	/* We must ensure the session is initialised first */
	error = nfs4_init_session(server->nfs_client);
	अगर (error < 0)
		जाओ out;

	/* Set the basic capabilities */
	server->caps |= server->nfs_client->cl_mvops->init_caps;
	अगर (server->flags & NFS_MOUNT_NORसूचीPLUS)
			server->caps &= ~NFS_CAP_READसूचीPLUS;
	अगर (server->nfs_client->cl_proto == XPRT_TRANSPORT_RDMA)
		server->caps &= ~NFS_CAP_READ_PLUS;
	/*
	 * Don't use NFS uid/gid mapping if we're using AUTH_SYS or lower
	 * authentication.
	 */
	अगर (nfs4_disable_idmapping &&
			server->client->cl_auth->au_flavor == RPC_AUTH_UNIX)
		server->caps |= NFS_CAP_UIDGID_NOMAP;


	/* Probe the root fh to retrieve its FSID and filehandle */
	error = nfs4_get_rootfh(server, mntfh, auth_probe);
	अगर (error < 0)
		जाओ out;

	dprपूर्णांकk("Server FSID: %llx:%llx\n",
			(अचिन्हित दीर्घ दीर्घ) server->fsid.major,
			(अचिन्हित दीर्घ दीर्घ) server->fsid.minor);
	nfs_display_fhandle(mntfh, "Pseudo-fs root FH");

	error = nfs_probe_fsinfo(server, mntfh, fattr);
	अगर (error < 0)
		जाओ out;

	nfs4_session_limit_rwsize(server);
	nfs4_session_limit_xasize(server);

	अगर (server->namelen == 0 || server->namelen > NFS4_MAXNAMLEN)
		server->namelen = NFS4_MAXNAMLEN;

	nfs_server_insert_lists(server);
	server->mount_समय = jअगरfies;
	server->destroy = nfs4_destroy_server;
out:
	nfs_मुक्त_fattr(fattr);
	वापस error;
पूर्ण

/*
 * Create a version 4 volume record
 */
अटल पूर्णांक nfs4_init_server(काष्ठा nfs_server *server, काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा rpc_समयout समयparms;
	पूर्णांक error;

	nfs_init_समयout_values(&समयparms, ctx->nfs_server.protocol,
				ctx->समयo, ctx->retrans);

	/* Initialise the client representation from the mount data */
	server->flags = ctx->flags;
	server->options = ctx->options;
	server->auth_info = ctx->auth_info;

	/* Use the first specअगरied auth flavor. If this flavor isn't
	 * allowed by the server, use the SECINFO path to try the
	 * other specअगरied flavors */
	अगर (ctx->auth_info.flavor_len >= 1)
		ctx->selected_flavor = ctx->auth_info.flavors[0];
	अन्यथा
		ctx->selected_flavor = RPC_AUTH_UNIX;

	/* Get a client record */
	error = nfs4_set_client(server,
				ctx->nfs_server.hostname,
				&ctx->nfs_server.address,
				ctx->nfs_server.addrlen,
				ctx->client_address,
				ctx->nfs_server.protocol,
				&समयparms,
				ctx->minorversion,
				ctx->nfs_server.nconnect,
				fc->net_ns);
	अगर (error < 0)
		वापस error;

	अगर (ctx->rsize)
		server->rsize = nfs_block_size(ctx->rsize, शून्य);
	अगर (ctx->wsize)
		server->wsize = nfs_block_size(ctx->wsize, शून्य);

	server->acregmin = ctx->acregmin * HZ;
	server->acregmax = ctx->acregmax * HZ;
	server->acdirmin = ctx->acdirmin * HZ;
	server->acdirmax = ctx->acdirmax * HZ;
	server->port     = ctx->nfs_server.port;

	वापस nfs_init_server_rpcclient(server, &समयparms,
					 ctx->selected_flavor);
पूर्ण

/*
 * Create a version 4 volume record
 * - keyed on server and FSID
 */
काष्ठा nfs_server *nfs4_create_server(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा nfs_server *server;
	bool auth_probe;
	पूर्णांक error;

	server = nfs_alloc_server();
	अगर (!server)
		वापस ERR_PTR(-ENOMEM);

	server->cred = get_cred(fc->cred);

	auth_probe = ctx->auth_info.flavor_len < 1;

	/* set up the general RPC client */
	error = nfs4_init_server(server, fc);
	अगर (error < 0)
		जाओ error;

	error = nfs4_server_common_setup(server, ctx->mntfh, auth_probe);
	अगर (error < 0)
		जाओ error;

	वापस server;

error:
	nfs_मुक्त_server(server);
	वापस ERR_PTR(error);
पूर्ण

/*
 * Create an NFS4 referral server record
 */
काष्ठा nfs_server *nfs4_create_referral_server(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा nfs_client *parent_client;
	काष्ठा nfs_server *server, *parent_server;
	bool auth_probe;
	पूर्णांक error;

	server = nfs_alloc_server();
	अगर (!server)
		वापस ERR_PTR(-ENOMEM);

	parent_server = NFS_SB(ctx->clone_data.sb);
	parent_client = parent_server->nfs_client;

	server->cred = get_cred(parent_server->cred);

	/* Initialise the client representation from the parent server */
	nfs_server_copy_userdata(server, parent_server);

	/* Get a client representation */
#अगर IS_ENABLED(CONFIG_SUNRPC_XPRT_RDMA)
	rpc_set_port(&ctx->nfs_server.address, NFS_RDMA_PORT);
	error = nfs4_set_client(server,
				ctx->nfs_server.hostname,
				&ctx->nfs_server.address,
				ctx->nfs_server.addrlen,
				parent_client->cl_ipaddr,
				XPRT_TRANSPORT_RDMA,
				parent_server->client->cl_समयout,
				parent_client->cl_mvops->minor_version,
				parent_client->cl_nconnect,
				parent_client->cl_net);
	अगर (!error)
		जाओ init_server;
#पूर्ण_अगर	/* IS_ENABLED(CONFIG_SUNRPC_XPRT_RDMA) */

	rpc_set_port(&ctx->nfs_server.address, NFS_PORT);
	error = nfs4_set_client(server,
				ctx->nfs_server.hostname,
				&ctx->nfs_server.address,
				ctx->nfs_server.addrlen,
				parent_client->cl_ipaddr,
				XPRT_TRANSPORT_TCP,
				parent_server->client->cl_समयout,
				parent_client->cl_mvops->minor_version,
				parent_client->cl_nconnect,
				parent_client->cl_net);
	अगर (error < 0)
		जाओ error;

#अगर IS_ENABLED(CONFIG_SUNRPC_XPRT_RDMA)
init_server:
#पूर्ण_अगर
	error = nfs_init_server_rpcclient(server, parent_server->client->cl_समयout,
					  ctx->selected_flavor);
	अगर (error < 0)
		जाओ error;

	auth_probe = parent_server->auth_info.flavor_len < 1;

	error = nfs4_server_common_setup(server, ctx->mntfh, auth_probe);
	अगर (error < 0)
		जाओ error;

	वापस server;

error:
	nfs_मुक्त_server(server);
	वापस ERR_PTR(error);
पूर्ण

/*
 * Grab the destination's particulars, including lease expiry समय.
 *
 * Returns zero अगर probe succeeded and retrieved FSID matches the FSID
 * we have cached.
 */
अटल पूर्णांक nfs_probe_destination(काष्ठा nfs_server *server)
अणु
	काष्ठा inode *inode = d_inode(server->super->s_root);
	काष्ठा nfs_fattr *fattr;
	पूर्णांक error;

	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य)
		वापस -ENOMEM;

	/* Sanity: the probe won't work अगर the destination server
	 * करोes not recognize the migrated FH. */
	error = nfs_probe_fsinfo(server, NFS_FH(inode), fattr);

	nfs_मुक्त_fattr(fattr);
	वापस error;
पूर्ण

/**
 * nfs4_update_server - Move an nfs_server to a dअगरferent nfs_client
 *
 * @server: represents FSID to be moved
 * @hostname: new end-poपूर्णांक's hostname
 * @sap: new end-poपूर्णांक's socket address
 * @salen: size of "sap"
 * @net: net namespace
 *
 * The nfs_server must be quiescent beक्रमe this function is invoked.
 * Either its session is drained (NFSv4.1+), or its transport is
 * plugged and drained (NFSv4.0).
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 */
पूर्णांक nfs4_update_server(काष्ठा nfs_server *server, स्थिर अक्षर *hostname,
		       काष्ठा sockaddr *sap, माप_प्रकार salen, काष्ठा net *net)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा rpc_clnt *clnt = server->client;
	काष्ठा xprt_create xargs = अणु
		.ident		= clp->cl_proto,
		.net		= net,
		.dstaddr	= sap,
		.addrlen	= salen,
		.servername	= hostname,
	पूर्ण;
	अक्षर buf[INET6_ADDRSTRLEN + 1];
	काष्ठा sockaddr_storage address;
	काष्ठा sockaddr *localaddr = (काष्ठा sockaddr *)&address;
	पूर्णांक error;

	error = rpc_चयन_client_transport(clnt, &xargs, clnt->cl_समयout);
	अगर (error != 0)
		वापस error;

	error = rpc_localaddr(clnt, localaddr, माप(address));
	अगर (error != 0)
		वापस error;

	अगर (rpc_ntop(localaddr, buf, माप(buf)) == 0)
		वापस -EAFNOSUPPORT;

	nfs_server_हटाओ_lists(server);
	set_bit(NFS_MIG_TSM_POSSIBLE, &server->mig_status);
	error = nfs4_set_client(server, hostname, sap, salen, buf,
				clp->cl_proto, clnt->cl_समयout,
				clp->cl_minorversion,
				clp->cl_nconnect, net);
	clear_bit(NFS_MIG_TSM_POSSIBLE, &server->mig_status);
	अगर (error != 0) अणु
		nfs_server_insert_lists(server);
		वापस error;
	पूर्ण
	nfs_put_client(clp);

	अगर (server->nfs_client->cl_hostname == शून्य)
		server->nfs_client->cl_hostname = kstrdup(hostname, GFP_KERNEL);
	nfs_server_insert_lists(server);

	वापस nfs_probe_destination(server);
पूर्ण
