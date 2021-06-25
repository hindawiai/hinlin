<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/nfs/delegation.c
 *
 * Copyright (C) 2004 Trond Myklebust
 *
 * NFS file delegation management
 *
 */
#समावेश <linux/completion.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/iversion.h>

#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_xdr.h>

#समावेश "nfs4_fs.h"
#समावेश "nfs4session.h"
#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "nfs4trace.h"

#घोषणा NFS_DEFAULT_DELEGATION_WATERMARK (5000U)

अटल atomic_दीर्घ_t nfs_active_delegations;
अटल अचिन्हित nfs_delegation_watermark = NFS_DEFAULT_DELEGATION_WATERMARK;

अटल व्योम __nfs_मुक्त_delegation(काष्ठा nfs_delegation *delegation)
अणु
	put_cred(delegation->cred);
	delegation->cred = शून्य;
	kमुक्त_rcu(delegation, rcu);
पूर्ण

अटल व्योम nfs_mark_delegation_revoked(काष्ठा nfs_delegation *delegation)
अणु
	अगर (!test_and_set_bit(NFS_DELEGATION_REVOKED, &delegation->flags)) अणु
		delegation->stateid.type = NFS4_INVALID_STATEID_TYPE;
		atomic_दीर्घ_dec(&nfs_active_delegations);
		अगर (!test_bit(NFS_DELEGATION_RETURNING, &delegation->flags))
			nfs_clear_verअगरier_delegated(delegation->inode);
	पूर्ण
पूर्ण

अटल काष्ठा nfs_delegation *nfs_get_delegation(काष्ठा nfs_delegation *delegation)
अणु
	refcount_inc(&delegation->refcount);
	वापस delegation;
पूर्ण

अटल व्योम nfs_put_delegation(काष्ठा nfs_delegation *delegation)
अणु
	अगर (refcount_dec_and_test(&delegation->refcount))
		__nfs_मुक्त_delegation(delegation);
पूर्ण

अटल व्योम nfs_मुक्त_delegation(काष्ठा nfs_delegation *delegation)
अणु
	nfs_mark_delegation_revoked(delegation);
	nfs_put_delegation(delegation);
पूर्ण

/**
 * nfs_mark_delegation_referenced - set delegation's REFERENCED flag
 * @delegation: delegation to process
 *
 */
व्योम nfs_mark_delegation_referenced(काष्ठा nfs_delegation *delegation)
अणु
	set_bit(NFS_DELEGATION_REFERENCED, &delegation->flags);
पूर्ण

अटल bool
nfs4_is_valid_delegation(स्थिर काष्ठा nfs_delegation *delegation,
		भ_शेषe_t flags)
अणु
	अगर (delegation != शून्य && (delegation->type & flags) == flags &&
	    !test_bit(NFS_DELEGATION_REVOKED, &delegation->flags) &&
	    !test_bit(NFS_DELEGATION_RETURNING, &delegation->flags))
		वापस true;
	वापस false;
पूर्ण

काष्ठा nfs_delegation *nfs4_get_valid_delegation(स्थिर काष्ठा inode *inode)
अणु
	काष्ठा nfs_delegation *delegation;

	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (nfs4_is_valid_delegation(delegation, 0))
		वापस delegation;
	वापस शून्य;
पूर्ण

अटल पूर्णांक
nfs4_करो_check_delegation(काष्ठा inode *inode, भ_शेषe_t flags, bool mark)
अणु
	काष्ठा nfs_delegation *delegation;
	पूर्णांक ret = 0;

	flags &= FMODE_READ|FMODE_WRITE;
	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (nfs4_is_valid_delegation(delegation, flags)) अणु
		अगर (mark)
			nfs_mark_delegation_referenced(delegation);
		ret = 1;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
/**
 * nfs4_have_delegation - check अगर inode has a delegation, mark it
 * NFS_DELEGATION_REFERENCED अगर there is one.
 * @inode: inode to check
 * @flags: delegation types to check क्रम
 *
 * Returns one अगर inode has the indicated delegation, otherwise zero.
 */
पूर्णांक nfs4_have_delegation(काष्ठा inode *inode, भ_शेषe_t flags)
अणु
	वापस nfs4_करो_check_delegation(inode, flags, true);
पूर्ण

/*
 * nfs4_check_delegation - check अगर inode has a delegation, करो not mark
 * NFS_DELEGATION_REFERENCED अगर it has one.
 */
पूर्णांक nfs4_check_delegation(काष्ठा inode *inode, भ_शेषe_t flags)
अणु
	वापस nfs4_करो_check_delegation(inode, flags, false);
पूर्ण

अटल पूर्णांक nfs_delegation_claim_locks(काष्ठा nfs4_state *state, स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा inode *inode = state->inode;
	काष्ठा file_lock *fl;
	काष्ठा file_lock_context *flctx = inode->i_flctx;
	काष्ठा list_head *list;
	पूर्णांक status = 0;

	अगर (flctx == शून्य)
		जाओ out;

	list = &flctx->flc_posix;
	spin_lock(&flctx->flc_lock);
restart:
	list_क्रम_each_entry(fl, list, fl_list) अणु
		अगर (nfs_file_खोलो_context(fl->fl_file)->state != state)
			जारी;
		spin_unlock(&flctx->flc_lock);
		status = nfs4_lock_delegation_recall(fl, state, stateid);
		अगर (status < 0)
			जाओ out;
		spin_lock(&flctx->flc_lock);
	पूर्ण
	अगर (list == &flctx->flc_posix) अणु
		list = &flctx->flc_flock;
		जाओ restart;
	पूर्ण
	spin_unlock(&flctx->flc_lock);
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs_delegation_claim_खोलोs(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid, भ_शेषe_t type)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs4_state_owner *sp;
	काष्ठा nfs4_state *state;
	अचिन्हित पूर्णांक seq;
	पूर्णांक err;

again:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ctx, &nfsi->खोलो_files, list) अणु
		state = ctx->state;
		अगर (state == शून्य)
			जारी;
		अगर (!test_bit(NFS_DELEGATED_STATE, &state->flags))
			जारी;
		अगर (!nfs4_valid_खोलो_stateid(state))
			जारी;
		अगर (!nfs4_stateid_match(&state->stateid, stateid))
			जारी;
		अगर (!get_nfs_खोलो_context(ctx))
			जारी;
		rcu_पढ़ो_unlock();
		sp = state->owner;
		/* Block nfs4_proc_unlck */
		mutex_lock(&sp->so_delegवापस_mutex);
		seq = raw_seqcount_begin(&sp->so_reclaim_seqcount);
		err = nfs4_खोलो_delegation_recall(ctx, state, stateid);
		अगर (!err)
			err = nfs_delegation_claim_locks(state, stateid);
		अगर (!err && पढ़ो_seqcount_retry(&sp->so_reclaim_seqcount, seq))
			err = -EAGAIN;
		mutex_unlock(&sp->so_delegवापस_mutex);
		put_nfs_खोलो_context(ctx);
		अगर (err != 0)
			वापस err;
		जाओ again;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/**
 * nfs_inode_reclaim_delegation - process a delegation reclaim request
 * @inode: inode to process
 * @cred: credential to use क्रम request
 * @type: delegation type
 * @stateid: delegation stateid
 * @pagemod_limit: ग_लिखो delegation "space_limit"
 *
 */
व्योम nfs_inode_reclaim_delegation(काष्ठा inode *inode, स्थिर काष्ठा cred *cred,
				  भ_शेषe_t type,
				  स्थिर nfs4_stateid *stateid,
				  अचिन्हित दीर्घ pagemod_limit)
अणु
	काष्ठा nfs_delegation *delegation;
	स्थिर काष्ठा cred *oldcred = शून्य;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (delegation != शून्य) अणु
		spin_lock(&delegation->lock);
		अगर (nfs4_is_valid_delegation(delegation, 0)) अणु
			nfs4_stateid_copy(&delegation->stateid, stateid);
			delegation->type = type;
			delegation->pagemod_limit = pagemod_limit;
			oldcred = delegation->cred;
			delegation->cred = get_cred(cred);
			clear_bit(NFS_DELEGATION_NEED_RECLAIM,
				  &delegation->flags);
			spin_unlock(&delegation->lock);
			rcu_पढ़ो_unlock();
			put_cred(oldcred);
			trace_nfs4_reclaim_delegation(inode, type);
			वापस;
		पूर्ण
		/* We appear to have raced with a delegation वापस. */
		spin_unlock(&delegation->lock);
	पूर्ण
	rcu_पढ़ो_unlock();
	nfs_inode_set_delegation(inode, cred, type, stateid, pagemod_limit);
पूर्ण

अटल पूर्णांक nfs_करो_वापस_delegation(काष्ठा inode *inode, काष्ठा nfs_delegation *delegation, पूर्णांक issync)
अणु
	स्थिर काष्ठा cred *cred;
	पूर्णांक res = 0;

	अगर (!test_bit(NFS_DELEGATION_REVOKED, &delegation->flags)) अणु
		spin_lock(&delegation->lock);
		cred = get_cred(delegation->cred);
		spin_unlock(&delegation->lock);
		res = nfs4_proc_delegवापस(inode, cred,
				&delegation->stateid,
				issync);
		put_cred(cred);
	पूर्ण
	वापस res;
पूर्ण

अटल काष्ठा inode *nfs_delegation_grab_inode(काष्ठा nfs_delegation *delegation)
अणु
	काष्ठा inode *inode = शून्य;

	spin_lock(&delegation->lock);
	अगर (delegation->inode != शून्य)
		inode = igrab(delegation->inode);
	अगर (!inode)
		set_bit(NFS_DELEGATION_INODE_FREEING, &delegation->flags);
	spin_unlock(&delegation->lock);
	वापस inode;
पूर्ण

अटल काष्ठा nfs_delegation *
nfs_start_delegation_वापस_locked(काष्ठा nfs_inode *nfsi)
अणु
	काष्ठा nfs_delegation *ret = शून्य;
	काष्ठा nfs_delegation *delegation = rcu_dereference(nfsi->delegation);

	अगर (delegation == शून्य)
		जाओ out;
	spin_lock(&delegation->lock);
	अगर (!test_and_set_bit(NFS_DELEGATION_RETURNING, &delegation->flags)) अणु
		/* Refcount matched in nfs_end_delegation_वापस() */
		ret = nfs_get_delegation(delegation);
	पूर्ण
	spin_unlock(&delegation->lock);
	अगर (ret)
		nfs_clear_verअगरier_delegated(&nfsi->vfs_inode);
out:
	वापस ret;
पूर्ण

अटल काष्ठा nfs_delegation *
nfs_start_delegation_वापस(काष्ठा nfs_inode *nfsi)
अणु
	काष्ठा nfs_delegation *delegation;

	rcu_पढ़ो_lock();
	delegation = nfs_start_delegation_वापस_locked(nfsi);
	rcu_पढ़ो_unlock();
	वापस delegation;
पूर्ण

अटल व्योम
nfs_पात_delegation_वापस(काष्ठा nfs_delegation *delegation,
		काष्ठा nfs_client *clp)
अणु

	spin_lock(&delegation->lock);
	clear_bit(NFS_DELEGATION_RETURNING, &delegation->flags);
	set_bit(NFS_DELEGATION_RETURN, &delegation->flags);
	spin_unlock(&delegation->lock);
	set_bit(NFS4CLNT_DELEGRETURN, &clp->cl_state);
पूर्ण

अटल काष्ठा nfs_delegation *
nfs_detach_delegation_locked(काष्ठा nfs_inode *nfsi,
		काष्ठा nfs_delegation *delegation,
		काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_delegation *deleg_cur =
		rcu_dereference_रक्षित(nfsi->delegation,
				lockdep_is_held(&clp->cl_lock));

	अगर (deleg_cur == शून्य || delegation != deleg_cur)
		वापस शून्य;

	spin_lock(&delegation->lock);
	अगर (!delegation->inode) अणु
		spin_unlock(&delegation->lock);
		वापस शून्य;
	पूर्ण
	list_del_rcu(&delegation->super_list);
	delegation->inode = शून्य;
	rcu_assign_poपूर्णांकer(nfsi->delegation, शून्य);
	spin_unlock(&delegation->lock);
	वापस delegation;
पूर्ण

अटल काष्ठा nfs_delegation *nfs_detach_delegation(काष्ठा nfs_inode *nfsi,
		काष्ठा nfs_delegation *delegation,
		काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;

	spin_lock(&clp->cl_lock);
	delegation = nfs_detach_delegation_locked(nfsi, delegation, clp);
	spin_unlock(&clp->cl_lock);
	वापस delegation;
पूर्ण

अटल काष्ठा nfs_delegation *
nfs_inode_detach_delegation(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_delegation *delegation;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(nfsi->delegation);
	अगर (delegation != शून्य)
		delegation = nfs_detach_delegation(nfsi, delegation, server);
	rcu_पढ़ो_unlock();
	वापस delegation;
पूर्ण

अटल व्योम
nfs_update_delegation_cred(काष्ठा nfs_delegation *delegation,
		स्थिर काष्ठा cred *cred)
अणु
	स्थिर काष्ठा cred *old;

	अगर (cred_fscmp(delegation->cred, cred) != 0) अणु
		old = xchg(&delegation->cred, get_cred(cred));
		put_cred(old);
	पूर्ण
पूर्ण

अटल व्योम
nfs_update_inplace_delegation(काष्ठा nfs_delegation *delegation,
		स्थिर काष्ठा nfs_delegation *update)
अणु
	अगर (nfs4_stateid_is_newer(&update->stateid, &delegation->stateid)) अणु
		delegation->stateid.seqid = update->stateid.seqid;
		smp_wmb();
		delegation->type = update->type;
		delegation->pagemod_limit = update->pagemod_limit;
		अगर (test_bit(NFS_DELEGATION_REVOKED, &delegation->flags)) अणु
			delegation->change_attr = update->change_attr;
			nfs_update_delegation_cred(delegation, update->cred);
			/* smp_mb__beक्रमe_atomic() is implicit due to xchg() */
			clear_bit(NFS_DELEGATION_REVOKED, &delegation->flags);
			atomic_दीर्घ_inc(&nfs_active_delegations);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * nfs_inode_set_delegation - set up a delegation on an inode
 * @inode: inode to which delegation applies
 * @cred: cred to use क्रम subsequent delegation processing
 * @type: delegation type
 * @stateid: delegation stateid
 * @pagemod_limit: ग_लिखो delegation "space_limit"
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 */
पूर्णांक nfs_inode_set_delegation(काष्ठा inode *inode, स्थिर काष्ठा cred *cred,
				  भ_शेषe_t type,
				  स्थिर nfs4_stateid *stateid,
				  अचिन्हित दीर्घ pagemod_limit)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_delegation *delegation, *old_delegation;
	काष्ठा nfs_delegation *मुक्तme = शून्य;
	पूर्णांक status = 0;

	delegation = kदो_स्मृति(माप(*delegation), GFP_NOFS);
	अगर (delegation == शून्य)
		वापस -ENOMEM;
	nfs4_stateid_copy(&delegation->stateid, stateid);
	refcount_set(&delegation->refcount, 1);
	delegation->type = type;
	delegation->pagemod_limit = pagemod_limit;
	delegation->change_attr = inode_peek_iversion_raw(inode);
	delegation->cred = get_cred(cred);
	delegation->inode = inode;
	delegation->flags = 1<<NFS_DELEGATION_REFERENCED;
	spin_lock_init(&delegation->lock);

	spin_lock(&clp->cl_lock);
	old_delegation = rcu_dereference_रक्षित(nfsi->delegation,
					lockdep_is_held(&clp->cl_lock));
	अगर (old_delegation == शून्य)
		जाओ add_new;
	/* Is this an update of the existing delegation? */
	अगर (nfs4_stateid_match_other(&old_delegation->stateid,
				&delegation->stateid)) अणु
		spin_lock(&old_delegation->lock);
		nfs_update_inplace_delegation(old_delegation,
				delegation);
		spin_unlock(&old_delegation->lock);
		जाओ out;
	पूर्ण
	अगर (!test_bit(NFS_DELEGATION_REVOKED, &old_delegation->flags)) अणु
		/*
		 * Deal with broken servers that hand out two
		 * delegations क्रम the same file.
		 * Allow क्रम upgrades to a WRITE delegation, but
		 * nothing अन्यथा.
		 */
		dfprपूर्णांकk(खाता, "%s: server %s handed out "
				"a duplicate delegation!\n",
				__func__, clp->cl_hostname);
		अगर (delegation->type == old_delegation->type ||
		    !(delegation->type & FMODE_WRITE)) अणु
			मुक्तme = delegation;
			delegation = शून्य;
			जाओ out;
		पूर्ण
		अगर (test_and_set_bit(NFS_DELEGATION_RETURNING,
					&old_delegation->flags))
			जाओ out;
	पूर्ण
	मुक्तme = nfs_detach_delegation_locked(nfsi, old_delegation, clp);
	अगर (मुक्तme == शून्य)
		जाओ out;
add_new:
	/*
	 * If we didn't revalidate the change attribute beक्रमe setting
	 * the delegation, then pre-emptively ask क्रम a full attribute
	 * cache revalidation.
	 */
	spin_lock(&inode->i_lock);
	अगर (NFS_I(inode)->cache_validity & NFS_INO_INVALID_CHANGE)
		nfs_set_cache_invalid(inode,
			NFS_INO_INVALID_ATIME | NFS_INO_INVALID_CTIME |
			NFS_INO_INVALID_MTIME | NFS_INO_INVALID_SIZE |
			NFS_INO_INVALID_BLOCKS | NFS_INO_INVALID_NLINK |
			NFS_INO_INVALID_OTHER | NFS_INO_INVALID_DATA |
			NFS_INO_INVALID_ACCESS | NFS_INO_INVALID_ACL |
			NFS_INO_INVALID_XATTR);
	spin_unlock(&inode->i_lock);

	list_add_tail_rcu(&delegation->super_list, &server->delegations);
	rcu_assign_poपूर्णांकer(nfsi->delegation, delegation);
	delegation = शून्य;

	atomic_दीर्घ_inc(&nfs_active_delegations);

	trace_nfs4_set_delegation(inode, type);
out:
	spin_unlock(&clp->cl_lock);
	अगर (delegation != शून्य)
		__nfs_मुक्त_delegation(delegation);
	अगर (मुक्तme != शून्य) अणु
		nfs_करो_वापस_delegation(inode, मुक्तme, 0);
		nfs_मुक्त_delegation(मुक्तme);
	पूर्ण
	वापस status;
पूर्ण

/*
 * Basic procedure क्रम वापसing a delegation to the server
 */
अटल पूर्णांक nfs_end_delegation_वापस(काष्ठा inode *inode, काष्ठा nfs_delegation *delegation, पूर्णांक issync)
अणु
	काष्ठा nfs_client *clp = NFS_SERVER(inode)->nfs_client;
	पूर्णांक err = 0;

	अगर (delegation == शून्य)
		वापस 0;
	करो अणु
		अगर (test_bit(NFS_DELEGATION_REVOKED, &delegation->flags))
			अवरोध;
		err = nfs_delegation_claim_खोलोs(inode, &delegation->stateid,
				delegation->type);
		अगर (!issync || err != -EAGAIN)
			अवरोध;
		/*
		 * Guard against state recovery
		 */
		err = nfs4_रुको_clnt_recover(clp);
	पूर्ण जबतक (err == 0);

	अगर (err) अणु
		nfs_पात_delegation_वापस(delegation, clp);
		जाओ out;
	पूर्ण

	err = nfs_करो_वापस_delegation(inode, delegation, issync);
out:
	/* Refcount matched in nfs_start_delegation_वापस_locked() */
	nfs_put_delegation(delegation);
	वापस err;
पूर्ण

अटल bool nfs_delegation_need_वापस(काष्ठा nfs_delegation *delegation)
अणु
	bool ret = false;

	अगर (test_and_clear_bit(NFS_DELEGATION_RETURN, &delegation->flags))
		ret = true;
	अन्यथा अगर (test_bit(NFS_DELEGATION_RETURN_IF_CLOSED, &delegation->flags)) अणु
		काष्ठा inode *inode;

		spin_lock(&delegation->lock);
		inode = delegation->inode;
		अगर (inode && list_empty(&NFS_I(inode)->खोलो_files))
			ret = true;
		spin_unlock(&delegation->lock);
	पूर्ण
	अगर (ret)
		clear_bit(NFS_DELEGATION_RETURN_IF_CLOSED, &delegation->flags);
	अगर (test_bit(NFS_DELEGATION_RETURNING, &delegation->flags) ||
	    test_bit(NFS_DELEGATION_REVOKED, &delegation->flags))
		ret = false;

	वापस ret;
पूर्ण

अटल पूर्णांक nfs_server_वापस_marked_delegations(काष्ठा nfs_server *server,
		व्योम __always_unused *data)
अणु
	काष्ठा nfs_delegation *delegation;
	काष्ठा nfs_delegation *prev;
	काष्ठा inode *inode;
	काष्ठा inode *place_holder = शून्य;
	काष्ठा nfs_delegation *place_holder_deleg = शून्य;
	पूर्णांक err = 0;

restart:
	/*
	 * To aव्योम quadratic looping we hold a reference
	 * to an inode place_holder.  Each समय we restart, we
	 * list delegation in the server from the delegations
	 * of that inode.
	 * prev is an RCU-रक्षित poपूर्णांकer to a delegation which
	 * wasn't marked क्रम वापस and might be a good choice क्रम
	 * the next place_holder.
	 */
	prev = शून्य;
	delegation = शून्य;
	rcu_पढ़ो_lock();
	अगर (place_holder)
		delegation = rcu_dereference(NFS_I(place_holder)->delegation);
	अगर (!delegation || delegation != place_holder_deleg)
		delegation = list_entry_rcu(server->delegations.next,
					    काष्ठा nfs_delegation, super_list);
	list_क्रम_each_entry_from_rcu(delegation, &server->delegations, super_list) अणु
		काष्ठा inode *to_put = शून्य;

		अगर (test_bit(NFS_DELEGATION_INODE_FREEING, &delegation->flags))
			जारी;
		अगर (!nfs_delegation_need_वापस(delegation)) अणु
			अगर (nfs4_is_valid_delegation(delegation, 0))
				prev = delegation;
			जारी;
		पूर्ण

		अगर (prev) अणु
			काष्ठा inode *पंचांगp = nfs_delegation_grab_inode(prev);
			अगर (पंचांगp) अणु
				to_put = place_holder;
				place_holder = पंचांगp;
				place_holder_deleg = prev;
			पूर्ण
		पूर्ण

		inode = nfs_delegation_grab_inode(delegation);
		अगर (inode == शून्य) अणु
			rcu_पढ़ो_unlock();
			iput(to_put);
			जाओ restart;
		पूर्ण
		delegation = nfs_start_delegation_वापस_locked(NFS_I(inode));
		rcu_पढ़ो_unlock();

		iput(to_put);

		err = nfs_end_delegation_वापस(inode, delegation, 0);
		iput(inode);
		cond_resched();
		अगर (!err)
			जाओ restart;
		set_bit(NFS4CLNT_DELEGRETURN, &server->nfs_client->cl_state);
		जाओ out;
	पूर्ण
	rcu_पढ़ो_unlock();
out:
	iput(place_holder);
	वापस err;
पूर्ण

/**
 * nfs_client_वापस_marked_delegations - वापस previously marked delegations
 * @clp: nfs_client to process
 *
 * Note that this function is deचिन्हित to be called by the state
 * manager thपढ़ो. For this reason, it cannot flush the dirty data,
 * since that could deadlock in हाल of a state recovery error.
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 */
पूर्णांक nfs_client_वापस_marked_delegations(काष्ठा nfs_client *clp)
अणु
	वापस nfs_client_क्रम_each_server(clp,
			nfs_server_वापस_marked_delegations, शून्य);
पूर्ण

/**
 * nfs_inode_evict_delegation - वापस delegation, करोn't reclaim खोलोs
 * @inode: inode to process
 *
 * Does not protect against delegation reclaims, thereक्रमe really only safe
 * to be called from nfs4_clear_inode(). Guaranteed to always मुक्त
 * the delegation काष्ठाure.
 */
व्योम nfs_inode_evict_delegation(काष्ठा inode *inode)
अणु
	काष्ठा nfs_delegation *delegation;

	delegation = nfs_inode_detach_delegation(inode);
	अगर (delegation != शून्य) अणु
		set_bit(NFS_DELEGATION_RETURNING, &delegation->flags);
		set_bit(NFS_DELEGATION_INODE_FREEING, &delegation->flags);
		nfs_करो_वापस_delegation(inode, delegation, 1);
		nfs_मुक्त_delegation(delegation);
	पूर्ण
पूर्ण

/**
 * nfs4_inode_वापस_delegation - synchronously वापस a delegation
 * @inode: inode to process
 *
 * This routine will always flush any dirty data to disk on the
 * assumption that अगर we need to वापस the delegation, then
 * we should stop caching.
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 */
पूर्णांक nfs4_inode_वापस_delegation(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_delegation *delegation;
	पूर्णांक err = 0;

	nfs_wb_all(inode);
	delegation = nfs_start_delegation_वापस(nfsi);
	अगर (delegation != शून्य)
		err = nfs_end_delegation_वापस(inode, delegation, 1);
	वापस err;
पूर्ण

/**
 * nfs4_inode_वापस_delegation_on_बंद - asynchronously वापस a delegation
 * @inode: inode to process
 *
 * This routine is called on file बंद in order to determine अगर the
 * inode delegation needs to be वापसed immediately.
 */
व्योम nfs4_inode_वापस_delegation_on_बंद(काष्ठा inode *inode)
अणु
	काष्ठा nfs_delegation *delegation;
	काष्ठा nfs_delegation *ret = शून्य;

	अगर (!inode)
		वापस;
	rcu_पढ़ो_lock();
	delegation = nfs4_get_valid_delegation(inode);
	अगर (!delegation)
		जाओ out;
	अगर (test_bit(NFS_DELEGATION_RETURN_IF_CLOSED, &delegation->flags) ||
	    atomic_दीर्घ_पढ़ो(&nfs_active_delegations) >= nfs_delegation_watermark) अणु
		spin_lock(&delegation->lock);
		अगर (delegation->inode &&
		    list_empty(&NFS_I(inode)->खोलो_files) &&
		    !test_and_set_bit(NFS_DELEGATION_RETURNING, &delegation->flags)) अणु
			clear_bit(NFS_DELEGATION_RETURN_IF_CLOSED, &delegation->flags);
			/* Refcount matched in nfs_end_delegation_वापस() */
			ret = nfs_get_delegation(delegation);
		पूर्ण
		spin_unlock(&delegation->lock);
		अगर (ret)
			nfs_clear_verअगरier_delegated(inode);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	nfs_end_delegation_वापस(inode, ret, 0);
पूर्ण

/**
 * nfs4_inode_make_ग_लिखोable
 * @inode: poपूर्णांकer to inode
 *
 * Make the inode ग_लिखोable by वापसing the delegation अगर necessary
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 */
पूर्णांक nfs4_inode_make_ग_लिखोable(काष्ठा inode *inode)
अणु
	काष्ठा nfs_delegation *delegation;

	rcu_पढ़ो_lock();
	delegation = nfs4_get_valid_delegation(inode);
	अगर (delegation == शून्य ||
	    (nfs4_has_session(NFS_SERVER(inode)->nfs_client) &&
	     (delegation->type & FMODE_WRITE))) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस nfs4_inode_वापस_delegation(inode);
पूर्ण

अटल व्योम nfs_mark_वापस_अगर_बंदd_delegation(काष्ठा nfs_server *server,
		काष्ठा nfs_delegation *delegation)
अणु
	set_bit(NFS_DELEGATION_RETURN_IF_CLOSED, &delegation->flags);
	set_bit(NFS4CLNT_DELEGRETURN, &server->nfs_client->cl_state);
पूर्ण

अटल व्योम nfs_mark_वापस_delegation(काष्ठा nfs_server *server,
		काष्ठा nfs_delegation *delegation)
अणु
	set_bit(NFS_DELEGATION_RETURN, &delegation->flags);
	set_bit(NFS4CLNT_DELEGRETURN, &server->nfs_client->cl_state);
पूर्ण

अटल bool nfs_server_mark_वापस_all_delegations(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_delegation *delegation;
	bool ret = false;

	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list) अणु
		nfs_mark_वापस_delegation(server, delegation);
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम nfs_client_mark_वापस_all_delegations(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_server *server;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		nfs_server_mark_वापस_all_delegations(server);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम nfs_delegation_run_state_manager(काष्ठा nfs_client *clp)
अणु
	अगर (test_bit(NFS4CLNT_DELEGRETURN, &clp->cl_state))
		nfs4_schedule_state_manager(clp);
पूर्ण

/**
 * nfs_expire_all_delegations
 * @clp: client to process
 *
 */
व्योम nfs_expire_all_delegations(काष्ठा nfs_client *clp)
अणु
	nfs_client_mark_वापस_all_delegations(clp);
	nfs_delegation_run_state_manager(clp);
पूर्ण

/**
 * nfs_server_वापस_all_delegations - वापस delegations क्रम one superblock
 * @server: poपूर्णांकer to nfs_server to process
 *
 */
व्योम nfs_server_वापस_all_delegations(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	bool need_रुको;

	अगर (clp == शून्य)
		वापस;

	rcu_पढ़ो_lock();
	need_रुको = nfs_server_mark_वापस_all_delegations(server);
	rcu_पढ़ो_unlock();

	अगर (need_रुको) अणु
		nfs4_schedule_state_manager(clp);
		nfs4_रुको_clnt_recover(clp);
	पूर्ण
पूर्ण

अटल व्योम nfs_mark_वापस_unused_delegation_types(काष्ठा nfs_server *server,
						 भ_शेषe_t flags)
अणु
	काष्ठा nfs_delegation *delegation;

	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list) अणु
		अगर ((delegation->type == (FMODE_READ|FMODE_WRITE)) && !(flags & FMODE_WRITE))
			जारी;
		अगर (delegation->type & flags)
			nfs_mark_वापस_अगर_बंदd_delegation(server, delegation);
	पूर्ण
पूर्ण

अटल व्योम nfs_client_mark_वापस_unused_delegation_types(काष्ठा nfs_client *clp,
							भ_शेषe_t flags)
अणु
	काष्ठा nfs_server *server;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		nfs_mark_वापस_unused_delegation_types(server, flags);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम nfs_revoke_delegation(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs_delegation *delegation;
	nfs4_stateid पंचांगp;
	bool ret = false;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (delegation == शून्य)
		जाओ out;
	अगर (stateid == शून्य) अणु
		nfs4_stateid_copy(&पंचांगp, &delegation->stateid);
		stateid = &पंचांगp;
	पूर्ण अन्यथा अणु
		अगर (!nfs4_stateid_match_other(stateid, &delegation->stateid))
			जाओ out;
		spin_lock(&delegation->lock);
		अगर (stateid->seqid) अणु
			अगर (nfs4_stateid_is_newer(&delegation->stateid, stateid)) अणु
				spin_unlock(&delegation->lock);
				जाओ out;
			पूर्ण
			delegation->stateid.seqid = stateid->seqid;
		पूर्ण
		spin_unlock(&delegation->lock);
	पूर्ण
	nfs_mark_delegation_revoked(delegation);
	ret = true;
out:
	rcu_पढ़ो_unlock();
	अगर (ret)
		nfs_inode_find_state_and_recover(inode, stateid);
पूर्ण

व्योम nfs_हटाओ_bad_delegation(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid)
अणु
	nfs_revoke_delegation(inode, stateid);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_हटाओ_bad_delegation);

व्योम nfs_delegation_mark_वापसed(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs_delegation *delegation;

	अगर (!inode)
		वापस;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (!delegation)
		जाओ out_rcu_unlock;

	spin_lock(&delegation->lock);
	अगर (!nfs4_stateid_match_other(stateid, &delegation->stateid))
		जाओ out_spin_unlock;
	अगर (stateid->seqid) अणु
		/* If delegation->stateid is newer, करोnt mark as वापसed */
		अगर (nfs4_stateid_is_newer(&delegation->stateid, stateid))
			जाओ out_clear_वापसing;
		अगर (delegation->stateid.seqid != stateid->seqid)
			delegation->stateid.seqid = stateid->seqid;
	पूर्ण

	nfs_mark_delegation_revoked(delegation);

out_clear_वापसing:
	clear_bit(NFS_DELEGATION_RETURNING, &delegation->flags);
out_spin_unlock:
	spin_unlock(&delegation->lock);
out_rcu_unlock:
	rcu_पढ़ो_unlock();

	nfs_inode_find_state_and_recover(inode, stateid);
पूर्ण

/**
 * nfs_expire_unused_delegation_types
 * @clp: client to process
 * @flags: delegation types to expire
 *
 */
व्योम nfs_expire_unused_delegation_types(काष्ठा nfs_client *clp, भ_शेषe_t flags)
अणु
	nfs_client_mark_वापस_unused_delegation_types(clp, flags);
	nfs_delegation_run_state_manager(clp);
पूर्ण

अटल व्योम nfs_mark_वापस_unreferenced_delegations(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_delegation *delegation;

	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list) अणु
		अगर (test_and_clear_bit(NFS_DELEGATION_REFERENCED, &delegation->flags))
			जारी;
		nfs_mark_वापस_अगर_बंदd_delegation(server, delegation);
	पूर्ण
पूर्ण

/**
 * nfs_expire_unreferenced_delegations - Eliminate unused delegations
 * @clp: nfs_client to process
 *
 */
व्योम nfs_expire_unreferenced_delegations(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_server *server;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		nfs_mark_वापस_unreferenced_delegations(server);
	rcu_पढ़ो_unlock();

	nfs_delegation_run_state_manager(clp);
पूर्ण

/**
 * nfs_async_inode_वापस_delegation - asynchronously वापस a delegation
 * @inode: inode to process
 * @stateid: state ID inक्रमmation
 *
 * Returns zero on success, or a negative त्रुटि_सं value.
 */
पूर्णांक nfs_async_inode_वापस_delegation(काष्ठा inode *inode,
				      स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs_delegation *delegation;

	rcu_पढ़ो_lock();
	delegation = nfs4_get_valid_delegation(inode);
	अगर (delegation == शून्य)
		जाओ out_enoent;
	अगर (stateid != शून्य &&
	    !clp->cl_mvops->match_stateid(&delegation->stateid, stateid))
		जाओ out_enoent;
	nfs_mark_वापस_delegation(server, delegation);
	rcu_पढ़ो_unlock();

	nfs_delegation_run_state_manager(clp);
	वापस 0;
out_enoent:
	rcu_पढ़ो_unlock();
	वापस -ENOENT;
पूर्ण

अटल काष्ठा inode *
nfs_delegation_find_inode_server(काष्ठा nfs_server *server,
				 स्थिर काष्ठा nfs_fh *fhandle)
अणु
	काष्ठा nfs_delegation *delegation;
	काष्ठा super_block *मुक्तme = शून्य;
	काष्ठा inode *res = शून्य;

	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list) अणु
		spin_lock(&delegation->lock);
		अगर (delegation->inode != शून्य &&
		    !test_bit(NFS_DELEGATION_REVOKED, &delegation->flags) &&
		    nfs_compare_fh(fhandle, &NFS_I(delegation->inode)->fh) == 0) अणु
			अगर (nfs_sb_active(server->super)) अणु
				मुक्तme = server->super;
				res = igrab(delegation->inode);
			पूर्ण
			spin_unlock(&delegation->lock);
			अगर (res != शून्य)
				वापस res;
			अगर (मुक्तme) अणु
				rcu_पढ़ो_unlock();
				nfs_sb_deactive(मुक्तme);
				rcu_पढ़ो_lock();
			पूर्ण
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
		spin_unlock(&delegation->lock);
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

/**
 * nfs_delegation_find_inode - retrieve the inode associated with a delegation
 * @clp: client state handle
 * @fhandle: filehandle from a delegation recall
 *
 * Returns poपूर्णांकer to inode matching "fhandle," or शून्य अगर a matching inode
 * cannot be found.
 */
काष्ठा inode *nfs_delegation_find_inode(काष्ठा nfs_client *clp,
					स्थिर काष्ठा nfs_fh *fhandle)
अणु
	काष्ठा nfs_server *server;
	काष्ठा inode *res;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link) अणु
		res = nfs_delegation_find_inode_server(server, fhandle);
		अगर (res != ERR_PTR(-ENOENT)) अणु
			rcu_पढ़ो_unlock();
			वापस res;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल व्योम nfs_delegation_mark_reclaim_server(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_delegation *delegation;

	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list) अणु
		/*
		 * If the delegation may have been admin revoked, then we
		 * cannot reclaim it.
		 */
		अगर (test_bit(NFS_DELEGATION_TEST_EXPIRED, &delegation->flags))
			जारी;
		set_bit(NFS_DELEGATION_NEED_RECLAIM, &delegation->flags);
	पूर्ण
पूर्ण

/**
 * nfs_delegation_mark_reclaim - mark all delegations as needing to be reclaimed
 * @clp: nfs_client to process
 *
 */
व्योम nfs_delegation_mark_reclaim(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_server *server;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		nfs_delegation_mark_reclaim_server(server);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक nfs_server_reap_unclaimed_delegations(काष्ठा nfs_server *server,
		व्योम __always_unused *data)
अणु
	काष्ठा nfs_delegation *delegation;
	काष्ठा inode *inode;
restart:
	rcu_पढ़ो_lock();
restart_locked:
	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list) अणु
		अगर (test_bit(NFS_DELEGATION_INODE_FREEING,
					&delegation->flags) ||
		    test_bit(NFS_DELEGATION_RETURNING,
					&delegation->flags) ||
		    test_bit(NFS_DELEGATION_NEED_RECLAIM,
					&delegation->flags) == 0)
			जारी;
		inode = nfs_delegation_grab_inode(delegation);
		अगर (inode == शून्य)
			जाओ restart_locked;
		delegation = nfs_start_delegation_वापस_locked(NFS_I(inode));
		rcu_पढ़ो_unlock();
		अगर (delegation != शून्य) अणु
			अगर (nfs_detach_delegation(NFS_I(inode), delegation,
						server) != शून्य)
				nfs_मुक्त_delegation(delegation);
			/* Match nfs_start_delegation_वापस_locked */
			nfs_put_delegation(delegation);
		पूर्ण
		iput(inode);
		cond_resched();
		जाओ restart;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/**
 * nfs_delegation_reap_unclaimed - reap unclaimed delegations after reboot recovery is करोne
 * @clp: nfs_client to process
 *
 */
व्योम nfs_delegation_reap_unclaimed(काष्ठा nfs_client *clp)
अणु
	nfs_client_क्रम_each_server(clp, nfs_server_reap_unclaimed_delegations,
			शून्य);
पूर्ण

अटल अंतरभूत bool nfs4_server_rebooted(स्थिर काष्ठा nfs_client *clp)
अणु
	वापस (clp->cl_state & (BIT(NFS4CLNT_CHECK_LEASE) |
				BIT(NFS4CLNT_LEASE_EXPIRED) |
				BIT(NFS4CLNT_SESSION_RESET))) != 0;
पूर्ण

अटल व्योम nfs_mark_test_expired_delegation(काष्ठा nfs_server *server,
	    काष्ठा nfs_delegation *delegation)
अणु
	अगर (delegation->stateid.type == NFS4_INVALID_STATEID_TYPE)
		वापस;
	clear_bit(NFS_DELEGATION_NEED_RECLAIM, &delegation->flags);
	set_bit(NFS_DELEGATION_TEST_EXPIRED, &delegation->flags);
	set_bit(NFS4CLNT_DELEGATION_EXPIRED, &server->nfs_client->cl_state);
पूर्ण

अटल व्योम nfs_inode_mark_test_expired_delegation(काष्ठा nfs_server *server,
		काष्ठा inode *inode)
अणु
	काष्ठा nfs_delegation *delegation;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (delegation)
		nfs_mark_test_expired_delegation(server, delegation);
	rcu_पढ़ो_unlock();

पूर्ण

अटल व्योम nfs_delegation_mark_test_expired_server(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_delegation *delegation;

	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list)
		nfs_mark_test_expired_delegation(server, delegation);
पूर्ण

/**
 * nfs_mark_test_expired_all_delegations - mark all delegations क्रम testing
 * @clp: nfs_client to process
 *
 * Iterates through all the delegations associated with this server and
 * marks them as needing to be checked क्रम validity.
 */
व्योम nfs_mark_test_expired_all_delegations(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_server *server;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		nfs_delegation_mark_test_expired_server(server);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * nfs_test_expired_all_delegations - test all delegations क्रम a client
 * @clp: nfs_client to process
 *
 * Helper क्रम handling "recallable state revoked" status from server.
 */
व्योम nfs_test_expired_all_delegations(काष्ठा nfs_client *clp)
अणु
	nfs_mark_test_expired_all_delegations(clp);
	nfs4_schedule_state_manager(clp);
पूर्ण

अटल व्योम
nfs_delegation_test_मुक्त_expired(काष्ठा inode *inode,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	स्थिर काष्ठा nfs4_minor_version_ops *ops = server->nfs_client->cl_mvops;
	पूर्णांक status;

	अगर (!cred)
		वापस;
	status = ops->test_and_मुक्त_expired(server, stateid, cred);
	अगर (status == -NFS4ERR_EXPIRED || status == -NFS4ERR_BAD_STATEID)
		nfs_हटाओ_bad_delegation(inode, stateid);
पूर्ण

अटल पूर्णांक nfs_server_reap_expired_delegations(काष्ठा nfs_server *server,
		व्योम __always_unused *data)
अणु
	काष्ठा nfs_delegation *delegation;
	काष्ठा inode *inode;
	स्थिर काष्ठा cred *cred;
	nfs4_stateid stateid;
restart:
	rcu_पढ़ो_lock();
restart_locked:
	list_क्रम_each_entry_rcu(delegation, &server->delegations, super_list) अणु
		अगर (test_bit(NFS_DELEGATION_INODE_FREEING,
					&delegation->flags) ||
		    test_bit(NFS_DELEGATION_RETURNING,
					&delegation->flags) ||
		    test_bit(NFS_DELEGATION_TEST_EXPIRED,
					&delegation->flags) == 0)
			जारी;
		inode = nfs_delegation_grab_inode(delegation);
		अगर (inode == शून्य)
			जाओ restart_locked;
		spin_lock(&delegation->lock);
		cred = get_cred_rcu(delegation->cred);
		nfs4_stateid_copy(&stateid, &delegation->stateid);
		spin_unlock(&delegation->lock);
		clear_bit(NFS_DELEGATION_TEST_EXPIRED, &delegation->flags);
		rcu_पढ़ो_unlock();
		nfs_delegation_test_मुक्त_expired(inode, &stateid, cred);
		put_cred(cred);
		अगर (!nfs4_server_rebooted(server->nfs_client)) अणु
			iput(inode);
			cond_resched();
			जाओ restart;
		पूर्ण
		nfs_inode_mark_test_expired_delegation(server,inode);
		iput(inode);
		वापस -EAGAIN;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/**
 * nfs_reap_expired_delegations - reap expired delegations
 * @clp: nfs_client to process
 *
 * Iterates through all the delegations associated with this server and
 * checks अगर they have may have been revoked. This function is usually
 * expected to be called in हालs where the server may have lost its
 * lease.
 */
व्योम nfs_reap_expired_delegations(काष्ठा nfs_client *clp)
अणु
	nfs_client_क्रम_each_server(clp, nfs_server_reap_expired_delegations,
			शून्य);
पूर्ण

व्योम nfs_inode_find_delegation_state_and_recover(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs_client *clp = NFS_SERVER(inode)->nfs_client;
	काष्ठा nfs_delegation *delegation;
	bool found = false;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (delegation &&
	    nfs4_stateid_match_or_older(&delegation->stateid, stateid) &&
	    !test_bit(NFS_DELEGATION_REVOKED, &delegation->flags)) अणु
		nfs_mark_test_expired_delegation(NFS_SERVER(inode), delegation);
		found = true;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (found)
		nfs4_schedule_state_manager(clp);
पूर्ण

/**
 * nfs_delegations_present - check क्रम existence of delegations
 * @clp: client state handle
 *
 * Returns one अगर there are any nfs_delegation काष्ठाures attached
 * to this nfs_client.
 */
पूर्णांक nfs_delegations_present(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_server *server;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(server, &clp->cl_superblocks, client_link)
		अगर (!list_empty(&server->delegations)) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * nfs4_refresh_delegation_stateid - Update delegation stateid seqid
 * @dst: stateid to refresh
 * @inode: inode to check
 *
 * Returns "true" and updates "dst->seqid" * अगर inode had a delegation
 * that matches our delegation stateid. Otherwise "false" is वापसed.
 */
bool nfs4_refresh_delegation_stateid(nfs4_stateid *dst, काष्ठा inode *inode)
अणु
	काष्ठा nfs_delegation *delegation;
	bool ret = false;
	अगर (!inode)
		जाओ out;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	अगर (delegation != शून्य &&
	    nfs4_stateid_match_other(dst, &delegation->stateid) &&
	    nfs4_stateid_is_newer(&delegation->stateid, dst) &&
	    !test_bit(NFS_DELEGATION_REVOKED, &delegation->flags)) अणु
		dst->seqid = delegation->stateid.seqid;
		ret = true;
	पूर्ण
	rcu_पढ़ो_unlock();
out:
	वापस ret;
पूर्ण

/**
 * nfs4_copy_delegation_stateid - Copy inode's state ID inक्रमmation
 * @inode: inode to check
 * @flags: delegation type requirement
 * @dst: stateid data काष्ठाure to fill in
 * @cred: optional argument to retrieve credential
 *
 * Returns "true" and fills in "dst->data" * अगर inode had a delegation,
 * otherwise "false" is वापसed.
 */
bool nfs4_copy_delegation_stateid(काष्ठा inode *inode, भ_शेषe_t flags,
		nfs4_stateid *dst, स्थिर काष्ठा cred **cred)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_delegation *delegation;
	bool ret = false;

	flags &= FMODE_READ|FMODE_WRITE;
	rcu_पढ़ो_lock();
	delegation = rcu_dereference(nfsi->delegation);
	अगर (!delegation)
		जाओ out;
	spin_lock(&delegation->lock);
	ret = nfs4_is_valid_delegation(delegation, flags);
	अगर (ret) अणु
		nfs4_stateid_copy(dst, &delegation->stateid);
		nfs_mark_delegation_referenced(delegation);
		अगर (cred)
			*cred = get_cred(delegation->cred);
	पूर्ण
	spin_unlock(&delegation->lock);
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * nfs4_delegation_flush_on_बंद - Check अगर we must flush file on बंद
 * @inode: inode to check
 *
 * This function checks the number of outstanding ग_लिखोs to the file
 * against the delegation 'space_limit' field to see अगर
 * the spec requires us to flush the file on बंद.
 */
bool nfs4_delegation_flush_on_बंद(स्थिर काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_delegation *delegation;
	bool ret = true;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(nfsi->delegation);
	अगर (delegation == शून्य || !(delegation->type & FMODE_WRITE))
		जाओ out;
	अगर (atomic_दीर्घ_पढ़ो(&nfsi->nrequests) < delegation->pagemod_limit)
		ret = false;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

module_param_named(delegation_watermark, nfs_delegation_watermark, uपूर्णांक, 0644);
