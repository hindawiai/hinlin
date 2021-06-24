<शैली गुरु>
/*
*  Copyright (c) 2001 The Regents of the University of Michigan.
*  All rights reserved.
*
*  Kendrick Smith <kmsmith@umich.edu>
*  Andy Adamson <kandros@umich.edu>
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
*/

#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>
#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/sunrpc/svcauth_gss.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/jhash.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश "xdr4.h"
#समावेश "xdr4cb.h"
#समावेश "vfs.h"
#समावेश "current_stateid.h"

#समावेश "netns.h"
#समावेश "pnfs.h"
#समावेश "filecache.h"
#समावेश "trace.h"

#घोषणा NFSDDBG_FACILITY                NFSDDBG_PROC

#घोषणा all_ones अणुअणु~0,~0पूर्ण,~0पूर्ण
अटल स्थिर stateid_t one_stateid = अणु
	.si_generation = ~0,
	.si_opaque = all_ones,
पूर्ण;
अटल स्थिर stateid_t zero_stateid = अणु
	/* all fields zero */
पूर्ण;
अटल स्थिर stateid_t currentstateid = अणु
	.si_generation = 1,
पूर्ण;
अटल स्थिर stateid_t बंद_stateid = अणु
	.si_generation = 0xffffffffU,
पूर्ण;

अटल u64 current_sessionid = 1;

#घोषणा ZERO_STATEID(stateid) (!स_भेद((stateid), &zero_stateid, माप(stateid_t)))
#घोषणा ONE_STATEID(stateid)  (!स_भेद((stateid), &one_stateid, माप(stateid_t)))
#घोषणा CURRENT_STATEID(stateid) (!स_भेद((stateid), &currentstateid, माप(stateid_t)))
#घोषणा CLOSE_STATEID(stateid)  (!स_भेद((stateid), &बंद_stateid, माप(stateid_t)))

/* क्रमward declarations */
अटल bool check_क्रम_locks(काष्ठा nfs4_file *fp, काष्ठा nfs4_lockowner *lowner);
अटल व्योम nfs4_मुक्त_ol_stateid(काष्ठा nfs4_stid *stid);
व्योम nfsd4_end_grace(काष्ठा nfsd_net *nn);
अटल व्योम _मुक्त_cpntf_state_locked(काष्ठा nfsd_net *nn, काष्ठा nfs4_cpntf_state *cps);

/* Locking: */

/*
 * Currently used क्रम the del_recall_lru and file hash table.  In an
 * efक्रमt to decrease the scope of the client_mutex, this spinlock may
 * eventually cover more:
 */
अटल DEFINE_SPINLOCK(state_lock);

क्रमागत nfsd4_st_mutex_lock_subclass अणु
	OPEN_STATEID_MUTEX = 0,
	LOCK_STATEID_MUTEX = 1,
पूर्ण;

/*
 * A रुकोqueue क्रम all in-progress 4.0 CLOSE operations that are रुकोing क्रम
 * the refcount on the खोलो stateid to drop.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(बंद_wq);

/*
 * A रुकोqueue where a ग_लिखोr to clients/#/ctl destroying a client can
 * रुको क्रम cl_rpc_users to drop to 0 and then क्रम the client to be
 * unhashed.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(expiry_wq);

अटल काष्ठा kmem_cache *client_slab;
अटल काष्ठा kmem_cache *खोलोowner_slab;
अटल काष्ठा kmem_cache *lockowner_slab;
अटल काष्ठा kmem_cache *file_slab;
अटल काष्ठा kmem_cache *stateid_slab;
अटल काष्ठा kmem_cache *deleg_slab;
अटल काष्ठा kmem_cache *odstate_slab;

अटल व्योम मुक्त_session(काष्ठा nfsd4_session *);

अटल स्थिर काष्ठा nfsd4_callback_ops nfsd4_cb_recall_ops;
अटल स्थिर काष्ठा nfsd4_callback_ops nfsd4_cb_notअगरy_lock_ops;

अटल bool is_session_dead(काष्ठा nfsd4_session *ses)
अणु
	वापस ses->se_flags & NFS4_SESSION_DEAD;
पूर्ण

अटल __be32 mark_session_dead_locked(काष्ठा nfsd4_session *ses, पूर्णांक ref_held_by_me)
अणु
	अगर (atomic_पढ़ो(&ses->se_ref) > ref_held_by_me)
		वापस nfserr_jukebox;
	ses->se_flags |= NFS4_SESSION_DEAD;
	वापस nfs_ok;
पूर्ण

अटल bool is_client_expired(काष्ठा nfs4_client *clp)
अणु
	वापस clp->cl_समय == 0;
पूर्ण

अटल __be32 get_client_locked(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_निश्चित_held(&nn->client_lock);

	अगर (is_client_expired(clp))
		वापस nfserr_expired;
	atomic_inc(&clp->cl_rpc_users);
	वापस nfs_ok;
पूर्ण

/* must be called under the client_lock */
अटल अंतरभूत व्योम
renew_client_locked(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (is_client_expired(clp)) अणु
		WARN_ON(1);
		prपूर्णांकk("%s: client (clientid %08x/%08x) already expired\n",
			__func__,
			clp->cl_clientid.cl_boot,
			clp->cl_clientid.cl_id);
		वापस;
	पूर्ण

	list_move_tail(&clp->cl_lru, &nn->client_lru);
	clp->cl_समय = kसमय_get_bootसमय_seconds();
पूर्ण

अटल व्योम put_client_renew_locked(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_निश्चित_held(&nn->client_lock);

	अगर (!atomic_dec_and_test(&clp->cl_rpc_users))
		वापस;
	अगर (!is_client_expired(clp))
		renew_client_locked(clp);
	अन्यथा
		wake_up_all(&expiry_wq);
पूर्ण

अटल व्योम put_client_renew(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (!atomic_dec_and_lock(&clp->cl_rpc_users, &nn->client_lock))
		वापस;
	अगर (!is_client_expired(clp))
		renew_client_locked(clp);
	अन्यथा
		wake_up_all(&expiry_wq);
	spin_unlock(&nn->client_lock);
पूर्ण

अटल __be32 nfsd4_get_session_locked(काष्ठा nfsd4_session *ses)
अणु
	__be32 status;

	अगर (is_session_dead(ses))
		वापस nfserr_badsession;
	status = get_client_locked(ses->se_client);
	अगर (status)
		वापस status;
	atomic_inc(&ses->se_ref);
	वापस nfs_ok;
पूर्ण

अटल व्योम nfsd4_put_session_locked(काष्ठा nfsd4_session *ses)
अणु
	काष्ठा nfs4_client *clp = ses->se_client;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_निश्चित_held(&nn->client_lock);

	अगर (atomic_dec_and_test(&ses->se_ref) && is_session_dead(ses))
		मुक्त_session(ses);
	put_client_renew_locked(clp);
पूर्ण

अटल व्योम nfsd4_put_session(काष्ठा nfsd4_session *ses)
अणु
	काष्ठा nfs4_client *clp = ses->se_client;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	spin_lock(&nn->client_lock);
	nfsd4_put_session_locked(ses);
	spin_unlock(&nn->client_lock);
पूर्ण

अटल काष्ठा nfsd4_blocked_lock *
find_blocked_lock(काष्ठा nfs4_lockowner *lo, काष्ठा knfsd_fh *fh,
			काष्ठा nfsd_net *nn)
अणु
	काष्ठा nfsd4_blocked_lock *cur, *found = शून्य;

	spin_lock(&nn->blocked_locks_lock);
	list_क्रम_each_entry(cur, &lo->lo_blocked, nbl_list) अणु
		अगर (fh_match(fh, &cur->nbl_fh)) अणु
			list_del_init(&cur->nbl_list);
			list_del_init(&cur->nbl_lru);
			found = cur;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&nn->blocked_locks_lock);
	अगर (found)
		locks_delete_block(&found->nbl_lock);
	वापस found;
पूर्ण

अटल काष्ठा nfsd4_blocked_lock *
find_or_allocate_block(काष्ठा nfs4_lockowner *lo, काष्ठा knfsd_fh *fh,
			काष्ठा nfsd_net *nn)
अणु
	काष्ठा nfsd4_blocked_lock *nbl;

	nbl = find_blocked_lock(lo, fh, nn);
	अगर (!nbl) अणु
		nbl= kदो_स्मृति(माप(*nbl), GFP_KERNEL);
		अगर (nbl) अणु
			INIT_LIST_HEAD(&nbl->nbl_list);
			INIT_LIST_HEAD(&nbl->nbl_lru);
			fh_copy_shallow(&nbl->nbl_fh, fh);
			locks_init_lock(&nbl->nbl_lock);
			nfsd4_init_cb(&nbl->nbl_cb, lo->lo_owner.so_client,
					&nfsd4_cb_notअगरy_lock_ops,
					NFSPROC4_CLNT_CB_NOTIFY_LOCK);
		पूर्ण
	पूर्ण
	वापस nbl;
पूर्ण

अटल व्योम
मुक्त_blocked_lock(काष्ठा nfsd4_blocked_lock *nbl)
अणु
	locks_delete_block(&nbl->nbl_lock);
	locks_release_निजी(&nbl->nbl_lock);
	kमुक्त(nbl);
पूर्ण

अटल व्योम
हटाओ_blocked_locks(काष्ठा nfs4_lockowner *lo)
अणु
	काष्ठा nfs4_client *clp = lo->lo_owner.so_client;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा nfsd4_blocked_lock *nbl;
	LIST_HEAD(reaplist);

	/* Dequeue all blocked locks */
	spin_lock(&nn->blocked_locks_lock);
	जबतक (!list_empty(&lo->lo_blocked)) अणु
		nbl = list_first_entry(&lo->lo_blocked,
					काष्ठा nfsd4_blocked_lock,
					nbl_list);
		list_del_init(&nbl->nbl_list);
		list_move(&nbl->nbl_lru, &reaplist);
	पूर्ण
	spin_unlock(&nn->blocked_locks_lock);

	/* Now मुक्त them */
	जबतक (!list_empty(&reaplist)) अणु
		nbl = list_first_entry(&reaplist, काष्ठा nfsd4_blocked_lock,
					nbl_lru);
		list_del_init(&nbl->nbl_lru);
		मुक्त_blocked_lock(nbl);
	पूर्ण
पूर्ण

अटल व्योम
nfsd4_cb_notअगरy_lock_prepare(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfsd4_blocked_lock	*nbl = container_of(cb,
						काष्ठा nfsd4_blocked_lock, nbl_cb);
	locks_delete_block(&nbl->nbl_lock);
पूर्ण

अटल पूर्णांक
nfsd4_cb_notअगरy_lock_करोne(काष्ठा nfsd4_callback *cb, काष्ठा rpc_task *task)
अणु
	/*
	 * Since this is just an optimization, we करोn't try very hard अगर it
	 * turns out not to succeed. We'll requeue it on NFS4ERR_DELAY, and
	 * just quit trying on anything अन्यथा.
	 */
	चयन (task->tk_status) अणु
	हाल -NFS4ERR_DELAY:
		rpc_delay(task, 1 * HZ);
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम
nfsd4_cb_notअगरy_lock_release(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfsd4_blocked_lock	*nbl = container_of(cb,
						काष्ठा nfsd4_blocked_lock, nbl_cb);

	मुक्त_blocked_lock(nbl);
पूर्ण

अटल स्थिर काष्ठा nfsd4_callback_ops nfsd4_cb_notअगरy_lock_ops = अणु
	.prepare	= nfsd4_cb_notअगरy_lock_prepare,
	.करोne		= nfsd4_cb_notअगरy_lock_करोne,
	.release	= nfsd4_cb_notअगरy_lock_release,
पूर्ण;

/*
 * We store the NONE, READ, WRITE, and BOTH bits separately in the
 * st_अणुaccess,denyपूर्ण_bmap field of the stateid, in order to track not
 * only what share bits are currently in क्रमce, but also what
 * combinations of share bits previous खोलोs have used.  This allows us
 * to enक्रमce the recommendation of rfc 3530 14.2.19 that the server
 * वापस an error अगर the client attempt to करोwngrade to a combination
 * of share bits not explicable by closing some of its previous खोलोs.
 *
 * XXX: This enक्रमcement is actually incomplete, since we करोn't keep
 * track of access/deny bit combinations; so, e.g., we allow:
 *
 *	OPEN allow पढ़ो, deny ग_लिखो
 *	OPEN allow both, deny none
 *	DOWNGRADE allow पढ़ो, deny none
 *
 * which we should reject.
 */
अटल अचिन्हित पूर्णांक
bmap_to_share_mode(अचिन्हित दीर्घ bmap)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक access = 0;

	क्रम (i = 1; i < 4; i++) अणु
		अगर (test_bit(i, &bmap))
			access |= i;
	पूर्ण
	वापस access;
पूर्ण

/* set share access क्रम a given stateid */
अटल अंतरभूत व्योम
set_access(u32 access, काष्ठा nfs4_ol_stateid *stp)
अणु
	अचिन्हित अक्षर mask = 1 << access;

	WARN_ON_ONCE(access > NFS4_SHARE_ACCESS_BOTH);
	stp->st_access_bmap |= mask;
पूर्ण

/* clear share access क्रम a given stateid */
अटल अंतरभूत व्योम
clear_access(u32 access, काष्ठा nfs4_ol_stateid *stp)
अणु
	अचिन्हित अक्षर mask = 1 << access;

	WARN_ON_ONCE(access > NFS4_SHARE_ACCESS_BOTH);
	stp->st_access_bmap &= ~mask;
पूर्ण

/* test whether a given stateid has access */
अटल अंतरभूत bool
test_access(u32 access, काष्ठा nfs4_ol_stateid *stp)
अणु
	अचिन्हित अक्षर mask = 1 << access;

	वापस (bool)(stp->st_access_bmap & mask);
पूर्ण

/* set share deny क्रम a given stateid */
अटल अंतरभूत व्योम
set_deny(u32 deny, काष्ठा nfs4_ol_stateid *stp)
अणु
	अचिन्हित अक्षर mask = 1 << deny;

	WARN_ON_ONCE(deny > NFS4_SHARE_DENY_BOTH);
	stp->st_deny_bmap |= mask;
पूर्ण

/* clear share deny क्रम a given stateid */
अटल अंतरभूत व्योम
clear_deny(u32 deny, काष्ठा nfs4_ol_stateid *stp)
अणु
	अचिन्हित अक्षर mask = 1 << deny;

	WARN_ON_ONCE(deny > NFS4_SHARE_DENY_BOTH);
	stp->st_deny_bmap &= ~mask;
पूर्ण

/* test whether a given stateid is denying specअगरic access */
अटल अंतरभूत bool
test_deny(u32 deny, काष्ठा nfs4_ol_stateid *stp)
अणु
	अचिन्हित अक्षर mask = 1 << deny;

	वापस (bool)(stp->st_deny_bmap & mask);
पूर्ण

अटल पूर्णांक nfs4_access_to_omode(u32 access)
अणु
	चयन (access & NFS4_SHARE_ACCESS_BOTH) अणु
	हाल NFS4_SHARE_ACCESS_READ:
		वापस O_RDONLY;
	हाल NFS4_SHARE_ACCESS_WRITE:
		वापस O_WRONLY;
	हाल NFS4_SHARE_ACCESS_BOTH:
		वापस O_RDWR;
	पूर्ण
	WARN_ON_ONCE(1);
	वापस O_RDONLY;
पूर्ण

अटल अंतरभूत पूर्णांक
access_permit_पढ़ो(काष्ठा nfs4_ol_stateid *stp)
अणु
	वापस test_access(NFS4_SHARE_ACCESS_READ, stp) ||
		test_access(NFS4_SHARE_ACCESS_BOTH, stp) ||
		test_access(NFS4_SHARE_ACCESS_WRITE, stp);
पूर्ण

अटल अंतरभूत पूर्णांक
access_permit_ग_लिखो(काष्ठा nfs4_ol_stateid *stp)
अणु
	वापस test_access(NFS4_SHARE_ACCESS_WRITE, stp) ||
		test_access(NFS4_SHARE_ACCESS_BOTH, stp);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_stateowner *
nfs4_get_stateowner(काष्ठा nfs4_stateowner *sop)
अणु
	atomic_inc(&sop->so_count);
	वापस sop;
पूर्ण

अटल पूर्णांक
same_owner_str(काष्ठा nfs4_stateowner *sop, काष्ठा xdr_netobj *owner)
अणु
	वापस (sop->so_owner.len == owner->len) &&
		0 == स_भेद(sop->so_owner.data, owner->data, owner->len);
पूर्ण

अटल काष्ठा nfs4_खोलोowner *
find_खोलोstateowner_str_locked(अचिन्हित पूर्णांक hashval, काष्ठा nfsd4_खोलो *खोलो,
			काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_stateowner *so;

	lockdep_निश्चित_held(&clp->cl_lock);

	list_क्रम_each_entry(so, &clp->cl_ownerstr_hashtbl[hashval],
			    so_strhash) अणु
		अगर (!so->so_is_खोलो_owner)
			जारी;
		अगर (same_owner_str(so, &खोलो->op_owner))
			वापस खोलोowner(nfs4_get_stateowner(so));
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_खोलोowner *
find_खोलोstateowner_str(अचिन्हित पूर्णांक hashval, काष्ठा nfsd4_खोलो *खोलो,
			काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_खोलोowner *oo;

	spin_lock(&clp->cl_lock);
	oo = find_खोलोstateowner_str_locked(hashval, खोलो, clp);
	spin_unlock(&clp->cl_lock);
	वापस oo;
पूर्ण

अटल अंतरभूत u32
opaque_hashval(स्थिर व्योम *ptr, पूर्णांक nbytes)
अणु
	अचिन्हित अक्षर *cptr = (अचिन्हित अक्षर *) ptr;

	u32 x = 0;
	जबतक (nbytes--) अणु
		x *= 37;
		x += *cptr++;
	पूर्ण
	वापस x;
पूर्ण

अटल व्योम nfsd4_मुक्त_file_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा nfs4_file *fp = container_of(rcu, काष्ठा nfs4_file, fi_rcu);

	kmem_cache_मुक्त(file_slab, fp);
पूर्ण

व्योम
put_nfs4_file(काष्ठा nfs4_file *fi)
अणु
	might_lock(&state_lock);

	अगर (refcount_dec_and_lock(&fi->fi_ref, &state_lock)) अणु
		hlist_del_rcu(&fi->fi_hash);
		spin_unlock(&state_lock);
		WARN_ON_ONCE(!list_empty(&fi->fi_clnt_odstate));
		WARN_ON_ONCE(!list_empty(&fi->fi_delegations));
		call_rcu(&fi->fi_rcu, nfsd4_मुक्त_file_rcu);
	पूर्ण
पूर्ण

अटल काष्ठा nfsd_file *
__nfs4_get_fd(काष्ठा nfs4_file *f, पूर्णांक oflag)
अणु
	अगर (f->fi_fds[oflag])
		वापस nfsd_file_get(f->fi_fds[oflag]);
	वापस शून्य;
पूर्ण

अटल काष्ठा nfsd_file *
find_ग_लिखोable_file_locked(काष्ठा nfs4_file *f)
अणु
	काष्ठा nfsd_file *ret;

	lockdep_निश्चित_held(&f->fi_lock);

	ret = __nfs4_get_fd(f, O_WRONLY);
	अगर (!ret)
		ret = __nfs4_get_fd(f, O_RDWR);
	वापस ret;
पूर्ण

अटल काष्ठा nfsd_file *
find_ग_लिखोable_file(काष्ठा nfs4_file *f)
अणु
	काष्ठा nfsd_file *ret;

	spin_lock(&f->fi_lock);
	ret = find_ग_लिखोable_file_locked(f);
	spin_unlock(&f->fi_lock);

	वापस ret;
पूर्ण

अटल काष्ठा nfsd_file *
find_पढ़ोable_file_locked(काष्ठा nfs4_file *f)
अणु
	काष्ठा nfsd_file *ret;

	lockdep_निश्चित_held(&f->fi_lock);

	ret = __nfs4_get_fd(f, O_RDONLY);
	अगर (!ret)
		ret = __nfs4_get_fd(f, O_RDWR);
	वापस ret;
पूर्ण

अटल काष्ठा nfsd_file *
find_पढ़ोable_file(काष्ठा nfs4_file *f)
अणु
	काष्ठा nfsd_file *ret;

	spin_lock(&f->fi_lock);
	ret = find_पढ़ोable_file_locked(f);
	spin_unlock(&f->fi_lock);

	वापस ret;
पूर्ण

काष्ठा nfsd_file *
find_any_file(काष्ठा nfs4_file *f)
अणु
	काष्ठा nfsd_file *ret;

	अगर (!f)
		वापस शून्य;
	spin_lock(&f->fi_lock);
	ret = __nfs4_get_fd(f, O_RDWR);
	अगर (!ret) अणु
		ret = __nfs4_get_fd(f, O_WRONLY);
		अगर (!ret)
			ret = __nfs4_get_fd(f, O_RDONLY);
	पूर्ण
	spin_unlock(&f->fi_lock);
	वापस ret;
पूर्ण

अटल काष्ठा nfsd_file *find_deleg_file(काष्ठा nfs4_file *f)
अणु
	काष्ठा nfsd_file *ret = शून्य;

	spin_lock(&f->fi_lock);
	अगर (f->fi_deleg_file)
		ret = nfsd_file_get(f->fi_deleg_file);
	spin_unlock(&f->fi_lock);
	वापस ret;
पूर्ण

अटल atomic_दीर्घ_t num_delegations;
अचिन्हित दीर्घ max_delegations;

/*
 * Open owner state (share locks)
 */

/* hash tables क्रम lock and खोलो owners */
#घोषणा OWNER_HASH_BITS              8
#घोषणा OWNER_HASH_SIZE             (1 << OWNER_HASH_BITS)
#घोषणा OWNER_HASH_MASK             (OWNER_HASH_SIZE - 1)

अटल अचिन्हित पूर्णांक ownerstr_hashval(काष्ठा xdr_netobj *ownername)
अणु
	अचिन्हित पूर्णांक ret;

	ret = opaque_hashval(ownername->data, ownername->len);
	वापस ret & OWNER_HASH_MASK;
पूर्ण

/* hash table क्रम nfs4_file */
#घोषणा खाता_HASH_BITS                   8
#घोषणा खाता_HASH_SIZE                  (1 << खाता_HASH_BITS)

अटल अचिन्हित पूर्णांक file_hashval(काष्ठा svc_fh *fh)
अणु
	काष्ठा inode *inode = d_inode(fh->fh_dentry);

	/* XXX: why not (here & in file cache) use inode? */
	वापस (अचिन्हित पूर्णांक)hash_दीर्घ(inode->i_ino, खाता_HASH_BITS);
पूर्ण

अटल काष्ठा hlist_head file_hashtbl[खाता_HASH_SIZE];

अटल व्योम
__nfs4_file_get_access(काष्ठा nfs4_file *fp, u32 access)
अणु
	lockdep_निश्चित_held(&fp->fi_lock);

	अगर (access & NFS4_SHARE_ACCESS_WRITE)
		atomic_inc(&fp->fi_access[O_WRONLY]);
	अगर (access & NFS4_SHARE_ACCESS_READ)
		atomic_inc(&fp->fi_access[O_RDONLY]);
पूर्ण

अटल __be32
nfs4_file_get_access(काष्ठा nfs4_file *fp, u32 access)
अणु
	lockdep_निश्चित_held(&fp->fi_lock);

	/* Does this access mode make sense? */
	अगर (access & ~NFS4_SHARE_ACCESS_BOTH)
		वापस nfserr_inval;

	/* Does it conflict with a deny mode alपढ़ोy set? */
	अगर ((access & fp->fi_share_deny) != 0)
		वापस nfserr_share_denied;

	__nfs4_file_get_access(fp, access);
	वापस nfs_ok;
पूर्ण

अटल __be32 nfs4_file_check_deny(काष्ठा nfs4_file *fp, u32 deny)
अणु
	/* Common हाल is that there is no deny mode. */
	अगर (deny) अणु
		/* Does this deny mode make sense? */
		अगर (deny & ~NFS4_SHARE_DENY_BOTH)
			वापस nfserr_inval;

		अगर ((deny & NFS4_SHARE_DENY_READ) &&
		    atomic_पढ़ो(&fp->fi_access[O_RDONLY]))
			वापस nfserr_share_denied;

		अगर ((deny & NFS4_SHARE_DENY_WRITE) &&
		    atomic_पढ़ो(&fp->fi_access[O_WRONLY]))
			वापस nfserr_share_denied;
	पूर्ण
	वापस nfs_ok;
पूर्ण

अटल व्योम __nfs4_file_put_access(काष्ठा nfs4_file *fp, पूर्णांक oflag)
अणु
	might_lock(&fp->fi_lock);

	अगर (atomic_dec_and_lock(&fp->fi_access[oflag], &fp->fi_lock)) अणु
		काष्ठा nfsd_file *f1 = शून्य;
		काष्ठा nfsd_file *f2 = शून्य;

		swap(f1, fp->fi_fds[oflag]);
		अगर (atomic_पढ़ो(&fp->fi_access[1 - oflag]) == 0)
			swap(f2, fp->fi_fds[O_RDWR]);
		spin_unlock(&fp->fi_lock);
		अगर (f1)
			nfsd_file_put(f1);
		अगर (f2)
			nfsd_file_put(f2);
	पूर्ण
पूर्ण

अटल व्योम nfs4_file_put_access(काष्ठा nfs4_file *fp, u32 access)
अणु
	WARN_ON_ONCE(access & ~NFS4_SHARE_ACCESS_BOTH);

	अगर (access & NFS4_SHARE_ACCESS_WRITE)
		__nfs4_file_put_access(fp, O_WRONLY);
	अगर (access & NFS4_SHARE_ACCESS_READ)
		__nfs4_file_put_access(fp, O_RDONLY);
पूर्ण

/*
 * Allocate a new खोलो/delegation state counter. This is needed क्रम
 * pNFS क्रम proper वापस on बंद semantics.
 *
 * Note that we only allocate it क्रम pNFS-enabled exports, otherwise
 * all poपूर्णांकers to काष्ठा nfs4_clnt_odstate are always शून्य.
 */
अटल काष्ठा nfs4_clnt_odstate *
alloc_clnt_odstate(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_clnt_odstate *co;

	co = kmem_cache_zalloc(odstate_slab, GFP_KERNEL);
	अगर (co) अणु
		co->co_client = clp;
		refcount_set(&co->co_odcount, 1);
	पूर्ण
	वापस co;
पूर्ण

अटल व्योम
hash_clnt_odstate_locked(काष्ठा nfs4_clnt_odstate *co)
अणु
	काष्ठा nfs4_file *fp = co->co_file;

	lockdep_निश्चित_held(&fp->fi_lock);
	list_add(&co->co_perfile, &fp->fi_clnt_odstate);
पूर्ण

अटल अंतरभूत व्योम
get_clnt_odstate(काष्ठा nfs4_clnt_odstate *co)
अणु
	अगर (co)
		refcount_inc(&co->co_odcount);
पूर्ण

अटल व्योम
put_clnt_odstate(काष्ठा nfs4_clnt_odstate *co)
अणु
	काष्ठा nfs4_file *fp;

	अगर (!co)
		वापस;

	fp = co->co_file;
	अगर (refcount_dec_and_lock(&co->co_odcount, &fp->fi_lock)) अणु
		list_del(&co->co_perfile);
		spin_unlock(&fp->fi_lock);

		nfsd4_वापस_all_file_layouts(co->co_client, fp);
		kmem_cache_मुक्त(odstate_slab, co);
	पूर्ण
पूर्ण

अटल काष्ठा nfs4_clnt_odstate *
find_or_hash_clnt_odstate(काष्ठा nfs4_file *fp, काष्ठा nfs4_clnt_odstate *new)
अणु
	काष्ठा nfs4_clnt_odstate *co;
	काष्ठा nfs4_client *cl;

	अगर (!new)
		वापस शून्य;

	cl = new->co_client;

	spin_lock(&fp->fi_lock);
	list_क्रम_each_entry(co, &fp->fi_clnt_odstate, co_perfile) अणु
		अगर (co->co_client == cl) अणु
			get_clnt_odstate(co);
			जाओ out;
		पूर्ण
	पूर्ण
	co = new;
	co->co_file = fp;
	hash_clnt_odstate_locked(new);
out:
	spin_unlock(&fp->fi_lock);
	वापस co;
पूर्ण

काष्ठा nfs4_stid *nfs4_alloc_stid(काष्ठा nfs4_client *cl, काष्ठा kmem_cache *slab,
				  व्योम (*sc_मुक्त)(काष्ठा nfs4_stid *))
अणु
	काष्ठा nfs4_stid *stid;
	पूर्णांक new_id;

	stid = kmem_cache_zalloc(slab, GFP_KERNEL);
	अगर (!stid)
		वापस शून्य;

	idr_preload(GFP_KERNEL);
	spin_lock(&cl->cl_lock);
	/* Reserving 0 क्रम start of file in nfsdfs "states" file: */
	new_id = idr_alloc_cyclic(&cl->cl_stateids, stid, 1, 0, GFP_NOWAIT);
	spin_unlock(&cl->cl_lock);
	idr_preload_end();
	अगर (new_id < 0)
		जाओ out_मुक्त;

	stid->sc_मुक्त = sc_मुक्त;
	stid->sc_client = cl;
	stid->sc_stateid.si_opaque.so_id = new_id;
	stid->sc_stateid.si_opaque.so_clid = cl->cl_clientid;
	/* Will be incremented beक्रमe वापस to client: */
	refcount_set(&stid->sc_count, 1);
	spin_lock_init(&stid->sc_lock);
	INIT_LIST_HEAD(&stid->sc_cp_list);

	/*
	 * It shouldn't be a problem to reuse an opaque stateid value.
	 * I करोn't think it is क्रम 4.1.  But with 4.0 I worry that, क्रम
	 * example, a stray ग_लिखो retransmission could be accepted by
	 * the server when it should have been rejected.  Thereक्रमe,
	 * aकरोpt a trick from the sctp code to attempt to maximize the
	 * amount of समय until an id is reused, by ensuring they always
	 * "increase" (mod पूर्णांक_उच्च):
	 */
	वापस stid;
out_मुक्त:
	kmem_cache_मुक्त(slab, stid);
	वापस शून्य;
पूर्ण

/*
 * Create a unique stateid_t to represent each COPY.
 */
अटल पूर्णांक nfs4_init_cp_state(काष्ठा nfsd_net *nn, copy_stateid_t *stid,
			      अचिन्हित अक्षर sc_type)
अणु
	पूर्णांक new_id;

	stid->stid.si_opaque.so_clid.cl_boot = (u32)nn->boot_समय;
	stid->stid.si_opaque.so_clid.cl_id = nn->s2s_cp_cl_id;
	stid->sc_type = sc_type;

	idr_preload(GFP_KERNEL);
	spin_lock(&nn->s2s_cp_lock);
	new_id = idr_alloc_cyclic(&nn->s2s_cp_stateids, stid, 0, 0, GFP_NOWAIT);
	stid->stid.si_opaque.so_id = new_id;
	stid->stid.si_generation = 1;
	spin_unlock(&nn->s2s_cp_lock);
	idr_preload_end();
	अगर (new_id < 0)
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक nfs4_init_copy_state(काष्ठा nfsd_net *nn, काष्ठा nfsd4_copy *copy)
अणु
	वापस nfs4_init_cp_state(nn, &copy->cp_stateid, NFS4_COPY_STID);
पूर्ण

काष्ठा nfs4_cpntf_state *nfs4_alloc_init_cpntf_state(काष्ठा nfsd_net *nn,
						     काष्ठा nfs4_stid *p_stid)
अणु
	काष्ठा nfs4_cpntf_state *cps;

	cps = kzalloc(माप(काष्ठा nfs4_cpntf_state), GFP_KERNEL);
	अगर (!cps)
		वापस शून्य;
	cps->cpntf_समय = kसमय_get_bootसमय_seconds();
	refcount_set(&cps->cp_stateid.sc_count, 1);
	अगर (!nfs4_init_cp_state(nn, &cps->cp_stateid, NFS4_COPYNOTIFY_STID))
		जाओ out_मुक्त;
	spin_lock(&nn->s2s_cp_lock);
	list_add(&cps->cp_list, &p_stid->sc_cp_list);
	spin_unlock(&nn->s2s_cp_lock);
	वापस cps;
out_मुक्त:
	kमुक्त(cps);
	वापस शून्य;
पूर्ण

व्योम nfs4_मुक्त_copy_state(काष्ठा nfsd4_copy *copy)
अणु
	काष्ठा nfsd_net *nn;

	WARN_ON_ONCE(copy->cp_stateid.sc_type != NFS4_COPY_STID);
	nn = net_generic(copy->cp_clp->net, nfsd_net_id);
	spin_lock(&nn->s2s_cp_lock);
	idr_हटाओ(&nn->s2s_cp_stateids,
		   copy->cp_stateid.stid.si_opaque.so_id);
	spin_unlock(&nn->s2s_cp_lock);
पूर्ण

अटल व्योम nfs4_मुक्त_cpntf_statelist(काष्ठा net *net, काष्ठा nfs4_stid *stid)
अणु
	काष्ठा nfs4_cpntf_state *cps;
	काष्ठा nfsd_net *nn;

	nn = net_generic(net, nfsd_net_id);
	spin_lock(&nn->s2s_cp_lock);
	जबतक (!list_empty(&stid->sc_cp_list)) अणु
		cps = list_first_entry(&stid->sc_cp_list,
				       काष्ठा nfs4_cpntf_state, cp_list);
		_मुक्त_cpntf_state_locked(nn, cps);
	पूर्ण
	spin_unlock(&nn->s2s_cp_lock);
पूर्ण

अटल काष्ठा nfs4_ol_stateid * nfs4_alloc_खोलो_stateid(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_stid *stid;

	stid = nfs4_alloc_stid(clp, stateid_slab, nfs4_मुक्त_ol_stateid);
	अगर (!stid)
		वापस शून्य;

	वापस खोलोlockstateid(stid);
पूर्ण

अटल व्योम nfs4_मुक्त_deleg(काष्ठा nfs4_stid *stid)
अणु
	kmem_cache_मुक्त(deleg_slab, stid);
	atomic_दीर्घ_dec(&num_delegations);
पूर्ण

/*
 * When we recall a delegation, we should be careful not to hand it
 * out again straight away.
 * To ensure this we keep a pair of bloom filters ('new' and 'old')
 * in which the filehandles of recalled delegations are "stored".
 * If a filehandle appear in either filter, a delegation is blocked.
 * When a delegation is recalled, the filehandle is stored in the "new"
 * filter.
 * Every 30 seconds we swap the filters and clear the "new" one,
 * unless both are empty of course.
 *
 * Each filter is 256 bits.  We hash the filehandle to 32bit and use the
 * low 3 bytes as hash-table indices.
 *
 * 'blocked_delegations_lock', which is always taken in block_delegations(),
 * is used to manage concurrent access.  Testing करोes not need the lock
 * except when swapping the two filters.
 */
अटल DEFINE_SPINLOCK(blocked_delegations_lock);
अटल काष्ठा bloom_pair अणु
	पूर्णांक	entries, old_entries;
	समय64_t swap_समय;
	पूर्णांक	new; /* index पूर्णांकo 'set' */
	DECLARE_BITMAP(set[2], 256);
पूर्ण blocked_delegations;

अटल पूर्णांक delegation_blocked(काष्ठा knfsd_fh *fh)
अणु
	u32 hash;
	काष्ठा bloom_pair *bd = &blocked_delegations;

	अगर (bd->entries == 0)
		वापस 0;
	अगर (kसमय_get_seconds() - bd->swap_समय > 30) अणु
		spin_lock(&blocked_delegations_lock);
		अगर (kसमय_get_seconds() - bd->swap_समय > 30) अणु
			bd->entries -= bd->old_entries;
			bd->old_entries = bd->entries;
			स_रखो(bd->set[bd->new], 0,
			       माप(bd->set[0]));
			bd->new = 1-bd->new;
			bd->swap_समय = kसमय_get_seconds();
		पूर्ण
		spin_unlock(&blocked_delegations_lock);
	पूर्ण
	hash = jhash(&fh->fh_base, fh->fh_size, 0);
	अगर (test_bit(hash&255, bd->set[0]) &&
	    test_bit((hash>>8)&255, bd->set[0]) &&
	    test_bit((hash>>16)&255, bd->set[0]))
		वापस 1;

	अगर (test_bit(hash&255, bd->set[1]) &&
	    test_bit((hash>>8)&255, bd->set[1]) &&
	    test_bit((hash>>16)&255, bd->set[1]))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम block_delegations(काष्ठा knfsd_fh *fh)
अणु
	u32 hash;
	काष्ठा bloom_pair *bd = &blocked_delegations;

	hash = jhash(&fh->fh_base, fh->fh_size, 0);

	spin_lock(&blocked_delegations_lock);
	__set_bit(hash&255, bd->set[bd->new]);
	__set_bit((hash>>8)&255, bd->set[bd->new]);
	__set_bit((hash>>16)&255, bd->set[bd->new]);
	अगर (bd->entries == 0)
		bd->swap_समय = kसमय_get_seconds();
	bd->entries += 1;
	spin_unlock(&blocked_delegations_lock);
पूर्ण

अटल काष्ठा nfs4_delegation *
alloc_init_deleg(काष्ठा nfs4_client *clp, काष्ठा nfs4_file *fp,
		 काष्ठा svc_fh *current_fh,
		 काष्ठा nfs4_clnt_odstate *odstate)
अणु
	काष्ठा nfs4_delegation *dp;
	दीर्घ n;

	dprपूर्णांकk("NFSD alloc_init_deleg\n");
	n = atomic_दीर्घ_inc_वापस(&num_delegations);
	अगर (n < 0 || n > max_delegations)
		जाओ out_dec;
	अगर (delegation_blocked(&current_fh->fh_handle))
		जाओ out_dec;
	dp = delegstateid(nfs4_alloc_stid(clp, deleg_slab, nfs4_मुक्त_deleg));
	अगर (dp == शून्य)
		जाओ out_dec;

	/*
	 * delegation seqid's are never incremented.  The 4.1 special
	 * meaning of seqid 0 isn't meaningful, really, but let's aव्योम
	 * 0 anyway just क्रम consistency and use 1:
	 */
	dp->dl_stid.sc_stateid.si_generation = 1;
	INIT_LIST_HEAD(&dp->dl_perfile);
	INIT_LIST_HEAD(&dp->dl_perclnt);
	INIT_LIST_HEAD(&dp->dl_recall_lru);
	dp->dl_clnt_odstate = odstate;
	get_clnt_odstate(odstate);
	dp->dl_type = NFS4_OPEN_DELEGATE_READ;
	dp->dl_retries = 1;
	nfsd4_init_cb(&dp->dl_recall, dp->dl_stid.sc_client,
		      &nfsd4_cb_recall_ops, NFSPROC4_CLNT_CB_RECALL);
	get_nfs4_file(fp);
	dp->dl_stid.sc_file = fp;
	वापस dp;
out_dec:
	atomic_दीर्घ_dec(&num_delegations);
	वापस शून्य;
पूर्ण

व्योम
nfs4_put_stid(काष्ठा nfs4_stid *s)
अणु
	काष्ठा nfs4_file *fp = s->sc_file;
	काष्ठा nfs4_client *clp = s->sc_client;

	might_lock(&clp->cl_lock);

	अगर (!refcount_dec_and_lock(&s->sc_count, &clp->cl_lock)) अणु
		wake_up_all(&बंद_wq);
		वापस;
	पूर्ण
	idr_हटाओ(&clp->cl_stateids, s->sc_stateid.si_opaque.so_id);
	nfs4_मुक्त_cpntf_statelist(clp->net, s);
	spin_unlock(&clp->cl_lock);
	s->sc_मुक्त(s);
	अगर (fp)
		put_nfs4_file(fp);
पूर्ण

व्योम
nfs4_inc_and_copy_stateid(stateid_t *dst, काष्ठा nfs4_stid *stid)
अणु
	stateid_t *src = &stid->sc_stateid;

	spin_lock(&stid->sc_lock);
	अगर (unlikely(++src->si_generation == 0))
		src->si_generation = 1;
	स_नकल(dst, src, माप(*dst));
	spin_unlock(&stid->sc_lock);
पूर्ण

अटल व्योम put_deleg_file(काष्ठा nfs4_file *fp)
अणु
	काष्ठा nfsd_file *nf = शून्य;

	spin_lock(&fp->fi_lock);
	अगर (--fp->fi_delegees == 0)
		swap(nf, fp->fi_deleg_file);
	spin_unlock(&fp->fi_lock);

	अगर (nf)
		nfsd_file_put(nf);
पूर्ण

अटल व्योम nfs4_unlock_deleg_lease(काष्ठा nfs4_delegation *dp)
अणु
	काष्ठा nfs4_file *fp = dp->dl_stid.sc_file;
	काष्ठा nfsd_file *nf = fp->fi_deleg_file;

	WARN_ON_ONCE(!fp->fi_delegees);

	vfs_setlease(nf->nf_file, F_UNLCK, शून्य, (व्योम **)&dp);
	put_deleg_file(fp);
पूर्ण

अटल व्योम destroy_unhashed_deleg(काष्ठा nfs4_delegation *dp)
अणु
	put_clnt_odstate(dp->dl_clnt_odstate);
	nfs4_unlock_deleg_lease(dp);
	nfs4_put_stid(&dp->dl_stid);
पूर्ण

व्योम nfs4_unhash_stid(काष्ठा nfs4_stid *s)
अणु
	s->sc_type = 0;
पूर्ण

/**
 * nfs4_delegation_exists - Discover अगर this delegation alपढ़ोy exists
 * @clp:     a poपूर्णांकer to the nfs4_client we're granting a delegation to
 * @fp:      a poपूर्णांकer to the nfs4_file we're granting a delegation on
 *
 * Return:
 *      On success: true अगरf an existing delegation is found
 */

अटल bool
nfs4_delegation_exists(काष्ठा nfs4_client *clp, काष्ठा nfs4_file *fp)
अणु
	काष्ठा nfs4_delegation *searchdp = शून्य;
	काष्ठा nfs4_client *searchclp = शून्य;

	lockdep_निश्चित_held(&state_lock);
	lockdep_निश्चित_held(&fp->fi_lock);

	list_क्रम_each_entry(searchdp, &fp->fi_delegations, dl_perfile) अणु
		searchclp = searchdp->dl_stid.sc_client;
		अगर (clp == searchclp) अणु
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * hash_delegation_locked - Add a delegation to the appropriate lists
 * @dp:     a poपूर्णांकer to the nfs4_delegation we are adding.
 * @fp:     a poपूर्णांकer to the nfs4_file we're granting a delegation on
 *
 * Return:
 *      On success: शून्य अगर the delegation was successfully hashed.
 *
 *      On error: -EAGAIN अगर one was previously granted to this
 *                 nfs4_client क्रम this nfs4_file. Delegation is not hashed.
 *
 */

अटल पूर्णांक
hash_delegation_locked(काष्ठा nfs4_delegation *dp, काष्ठा nfs4_file *fp)
अणु
	काष्ठा nfs4_client *clp = dp->dl_stid.sc_client;

	lockdep_निश्चित_held(&state_lock);
	lockdep_निश्चित_held(&fp->fi_lock);

	अगर (nfs4_delegation_exists(clp, fp))
		वापस -EAGAIN;
	refcount_inc(&dp->dl_stid.sc_count);
	dp->dl_stid.sc_type = NFS4_DELEG_STID;
	list_add(&dp->dl_perfile, &fp->fi_delegations);
	list_add(&dp->dl_perclnt, &clp->cl_delegations);
	वापस 0;
पूर्ण

अटल bool
unhash_delegation_locked(काष्ठा nfs4_delegation *dp)
अणु
	काष्ठा nfs4_file *fp = dp->dl_stid.sc_file;

	lockdep_निश्चित_held(&state_lock);

	अगर (list_empty(&dp->dl_perfile))
		वापस false;

	dp->dl_stid.sc_type = NFS4_CLOSED_DELEG_STID;
	/* Ensure that deleg अवरोध won't try to requeue it */
	++dp->dl_समय;
	spin_lock(&fp->fi_lock);
	list_del_init(&dp->dl_perclnt);
	list_del_init(&dp->dl_recall_lru);
	list_del_init(&dp->dl_perfile);
	spin_unlock(&fp->fi_lock);
	वापस true;
पूर्ण

अटल व्योम destroy_delegation(काष्ठा nfs4_delegation *dp)
अणु
	bool unhashed;

	spin_lock(&state_lock);
	unhashed = unhash_delegation_locked(dp);
	spin_unlock(&state_lock);
	अगर (unhashed)
		destroy_unhashed_deleg(dp);
पूर्ण

अटल व्योम revoke_delegation(काष्ठा nfs4_delegation *dp)
अणु
	काष्ठा nfs4_client *clp = dp->dl_stid.sc_client;

	WARN_ON(!list_empty(&dp->dl_recall_lru));

	अगर (clp->cl_minorversion) अणु
		dp->dl_stid.sc_type = NFS4_REVOKED_DELEG_STID;
		refcount_inc(&dp->dl_stid.sc_count);
		spin_lock(&clp->cl_lock);
		list_add(&dp->dl_recall_lru, &clp->cl_revoked);
		spin_unlock(&clp->cl_lock);
	पूर्ण
	destroy_unhashed_deleg(dp);
पूर्ण

/* 
 * SETCLIENTID state 
 */

अटल अचिन्हित पूर्णांक clientid_hashval(u32 id)
अणु
	वापस id & CLIENT_HASH_MASK;
पूर्ण

अटल अचिन्हित पूर्णांक clientstr_hashval(काष्ठा xdr_netobj name)
अणु
	वापस opaque_hashval(name.data, 8) & CLIENT_HASH_MASK;
पूर्ण

/*
 * A stateid that had a deny mode associated with it is being released
 * or करोwngraded. Recalculate the deny mode on the file.
 */
अटल व्योम
recalculate_deny_mode(काष्ठा nfs4_file *fp)
अणु
	काष्ठा nfs4_ol_stateid *stp;

	spin_lock(&fp->fi_lock);
	fp->fi_share_deny = 0;
	list_क्रम_each_entry(stp, &fp->fi_stateids, st_perfile)
		fp->fi_share_deny |= bmap_to_share_mode(stp->st_deny_bmap);
	spin_unlock(&fp->fi_lock);
पूर्ण

अटल व्योम
reset_जोड़_bmap_deny(u32 deny, काष्ठा nfs4_ol_stateid *stp)
अणु
	पूर्णांक i;
	bool change = false;

	क्रम (i = 1; i < 4; i++) अणु
		अगर ((i & deny) != i) अणु
			change = true;
			clear_deny(i, stp);
		पूर्ण
	पूर्ण

	/* Recalculate per-file deny mode अगर there was a change */
	अगर (change)
		recalculate_deny_mode(stp->st_stid.sc_file);
पूर्ण

/* release all access and file references क्रम a given stateid */
अटल व्योम
release_all_access(काष्ठा nfs4_ol_stateid *stp)
अणु
	पूर्णांक i;
	काष्ठा nfs4_file *fp = stp->st_stid.sc_file;

	अगर (fp && stp->st_deny_bmap != 0)
		recalculate_deny_mode(fp);

	क्रम (i = 1; i < 4; i++) अणु
		अगर (test_access(i, stp))
			nfs4_file_put_access(stp->st_stid.sc_file, i);
		clear_access(i, stp);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nfs4_मुक्त_stateowner(काष्ठा nfs4_stateowner *sop)
अणु
	kमुक्त(sop->so_owner.data);
	sop->so_ops->so_मुक्त(sop);
पूर्ण

अटल व्योम nfs4_put_stateowner(काष्ठा nfs4_stateowner *sop)
अणु
	काष्ठा nfs4_client *clp = sop->so_client;

	might_lock(&clp->cl_lock);

	अगर (!atomic_dec_and_lock(&sop->so_count, &clp->cl_lock))
		वापस;
	sop->so_ops->so_unhash(sop);
	spin_unlock(&clp->cl_lock);
	nfs4_मुक्त_stateowner(sop);
पूर्ण

अटल bool
nfs4_ol_stateid_unhashed(स्थिर काष्ठा nfs4_ol_stateid *stp)
अणु
	वापस list_empty(&stp->st_perfile);
पूर्ण

अटल bool unhash_ol_stateid(काष्ठा nfs4_ol_stateid *stp)
अणु
	काष्ठा nfs4_file *fp = stp->st_stid.sc_file;

	lockdep_निश्चित_held(&stp->st_stateowner->so_client->cl_lock);

	अगर (list_empty(&stp->st_perfile))
		वापस false;

	spin_lock(&fp->fi_lock);
	list_del_init(&stp->st_perfile);
	spin_unlock(&fp->fi_lock);
	list_del(&stp->st_perstateowner);
	वापस true;
पूर्ण

अटल व्योम nfs4_मुक्त_ol_stateid(काष्ठा nfs4_stid *stid)
अणु
	काष्ठा nfs4_ol_stateid *stp = खोलोlockstateid(stid);

	put_clnt_odstate(stp->st_clnt_odstate);
	release_all_access(stp);
	अगर (stp->st_stateowner)
		nfs4_put_stateowner(stp->st_stateowner);
	kmem_cache_मुक्त(stateid_slab, stid);
पूर्ण

अटल व्योम nfs4_मुक्त_lock_stateid(काष्ठा nfs4_stid *stid)
अणु
	काष्ठा nfs4_ol_stateid *stp = खोलोlockstateid(stid);
	काष्ठा nfs4_lockowner *lo = lockowner(stp->st_stateowner);
	काष्ठा nfsd_file *nf;

	nf = find_any_file(stp->st_stid.sc_file);
	अगर (nf) अणु
		get_file(nf->nf_file);
		filp_बंद(nf->nf_file, (fl_owner_t)lo);
		nfsd_file_put(nf);
	पूर्ण
	nfs4_मुक्त_ol_stateid(stid);
पूर्ण

/*
 * Put the persistent reference to an alपढ़ोy unhashed generic stateid, जबतक
 * holding the cl_lock. If it's the last reference, then put it onto the
 * reaplist क्रम later deकाष्ठाion.
 */
अटल व्योम put_ol_stateid_locked(काष्ठा nfs4_ol_stateid *stp,
				       काष्ठा list_head *reaplist)
अणु
	काष्ठा nfs4_stid *s = &stp->st_stid;
	काष्ठा nfs4_client *clp = s->sc_client;

	lockdep_निश्चित_held(&clp->cl_lock);

	WARN_ON_ONCE(!list_empty(&stp->st_locks));

	अगर (!refcount_dec_and_test(&s->sc_count)) अणु
		wake_up_all(&बंद_wq);
		वापस;
	पूर्ण

	idr_हटाओ(&clp->cl_stateids, s->sc_stateid.si_opaque.so_id);
	list_add(&stp->st_locks, reaplist);
पूर्ण

अटल bool unhash_lock_stateid(काष्ठा nfs4_ol_stateid *stp)
अणु
	lockdep_निश्चित_held(&stp->st_stid.sc_client->cl_lock);

	अगर (!unhash_ol_stateid(stp))
		वापस false;
	list_del_init(&stp->st_locks);
	nfs4_unhash_stid(&stp->st_stid);
	वापस true;
पूर्ण

अटल व्योम release_lock_stateid(काष्ठा nfs4_ol_stateid *stp)
अणु
	काष्ठा nfs4_client *clp = stp->st_stid.sc_client;
	bool unhashed;

	spin_lock(&clp->cl_lock);
	unhashed = unhash_lock_stateid(stp);
	spin_unlock(&clp->cl_lock);
	अगर (unhashed)
		nfs4_put_stid(&stp->st_stid);
पूर्ण

अटल व्योम unhash_lockowner_locked(काष्ठा nfs4_lockowner *lo)
अणु
	काष्ठा nfs4_client *clp = lo->lo_owner.so_client;

	lockdep_निश्चित_held(&clp->cl_lock);

	list_del_init(&lo->lo_owner.so_strhash);
पूर्ण

/*
 * Free a list of generic stateids that were collected earlier after being
 * fully unhashed.
 */
अटल व्योम
मुक्त_ol_stateid_reaplist(काष्ठा list_head *reaplist)
अणु
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा nfs4_file *fp;

	might_sleep();

	जबतक (!list_empty(reaplist)) अणु
		stp = list_first_entry(reaplist, काष्ठा nfs4_ol_stateid,
				       st_locks);
		list_del(&stp->st_locks);
		fp = stp->st_stid.sc_file;
		stp->st_stid.sc_मुक्त(&stp->st_stid);
		अगर (fp)
			put_nfs4_file(fp);
	पूर्ण
पूर्ण

अटल व्योम release_खोलो_stateid_locks(काष्ठा nfs4_ol_stateid *खोलो_stp,
				       काष्ठा list_head *reaplist)
अणु
	काष्ठा nfs4_ol_stateid *stp;

	lockdep_निश्चित_held(&खोलो_stp->st_stid.sc_client->cl_lock);

	जबतक (!list_empty(&खोलो_stp->st_locks)) अणु
		stp = list_entry(खोलो_stp->st_locks.next,
				काष्ठा nfs4_ol_stateid, st_locks);
		WARN_ON(!unhash_lock_stateid(stp));
		put_ol_stateid_locked(stp, reaplist);
	पूर्ण
पूर्ण

अटल bool unhash_खोलो_stateid(काष्ठा nfs4_ol_stateid *stp,
				काष्ठा list_head *reaplist)
अणु
	lockdep_निश्चित_held(&stp->st_stid.sc_client->cl_lock);

	अगर (!unhash_ol_stateid(stp))
		वापस false;
	release_खोलो_stateid_locks(stp, reaplist);
	वापस true;
पूर्ण

अटल व्योम release_खोलो_stateid(काष्ठा nfs4_ol_stateid *stp)
अणु
	LIST_HEAD(reaplist);

	spin_lock(&stp->st_stid.sc_client->cl_lock);
	अगर (unhash_खोलो_stateid(stp, &reaplist))
		put_ol_stateid_locked(stp, &reaplist);
	spin_unlock(&stp->st_stid.sc_client->cl_lock);
	मुक्त_ol_stateid_reaplist(&reaplist);
पूर्ण

अटल व्योम unhash_खोलोowner_locked(काष्ठा nfs4_खोलोowner *oo)
अणु
	काष्ठा nfs4_client *clp = oo->oo_owner.so_client;

	lockdep_निश्चित_held(&clp->cl_lock);

	list_del_init(&oo->oo_owner.so_strhash);
	list_del_init(&oo->oo_perclient);
पूर्ण

अटल व्योम release_last_बंदd_stateid(काष्ठा nfs4_खोलोowner *oo)
अणु
	काष्ठा nfsd_net *nn = net_generic(oo->oo_owner.so_client->net,
					  nfsd_net_id);
	काष्ठा nfs4_ol_stateid *s;

	spin_lock(&nn->client_lock);
	s = oo->oo_last_बंदd_stid;
	अगर (s) अणु
		list_del_init(&oo->oo_बंद_lru);
		oo->oo_last_बंदd_stid = शून्य;
	पूर्ण
	spin_unlock(&nn->client_lock);
	अगर (s)
		nfs4_put_stid(&s->st_stid);
पूर्ण

अटल व्योम release_खोलोowner(काष्ठा nfs4_खोलोowner *oo)
अणु
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा nfs4_client *clp = oo->oo_owner.so_client;
	काष्ठा list_head reaplist;

	INIT_LIST_HEAD(&reaplist);

	spin_lock(&clp->cl_lock);
	unhash_खोलोowner_locked(oo);
	जबतक (!list_empty(&oo->oo_owner.so_stateids)) अणु
		stp = list_first_entry(&oo->oo_owner.so_stateids,
				काष्ठा nfs4_ol_stateid, st_perstateowner);
		अगर (unhash_खोलो_stateid(stp, &reaplist))
			put_ol_stateid_locked(stp, &reaplist);
	पूर्ण
	spin_unlock(&clp->cl_lock);
	मुक्त_ol_stateid_reaplist(&reaplist);
	release_last_बंदd_stateid(oo);
	nfs4_put_stateowner(&oo->oo_owner);
पूर्ण

अटल अंतरभूत पूर्णांक
hash_sessionid(काष्ठा nfs4_sessionid *sessionid)
अणु
	काष्ठा nfsd4_sessionid *sid = (काष्ठा nfsd4_sessionid *)sessionid;

	वापस sid->sequence % SESSION_HASH_SIZE;
पूर्ण

#अगर_घोषित CONFIG_SUNRPC_DEBUG
अटल अंतरभूत व्योम
dump_sessionid(स्थिर अक्षर *fn, काष्ठा nfs4_sessionid *sessionid)
अणु
	u32 *ptr = (u32 *)(&sessionid->data[0]);
	dprपूर्णांकk("%s: %u:%u:%u:%u\n", fn, ptr[0], ptr[1], ptr[2], ptr[3]);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
dump_sessionid(स्थिर अक्षर *fn, काष्ठा nfs4_sessionid *sessionid)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Bump the seqid on cstate->replay_owner, and clear replay_owner अगर it
 * won't be used क्रम replay.
 */
व्योम nfsd4_bump_seqid(काष्ठा nfsd4_compound_state *cstate, __be32 nfserr)
अणु
	काष्ठा nfs4_stateowner *so = cstate->replay_owner;

	अगर (nfserr == nfserr_replay_me)
		वापस;

	अगर (!seqid_mutating_err(ntohl(nfserr))) अणु
		nfsd4_cstate_clear_replay(cstate);
		वापस;
	पूर्ण
	अगर (!so)
		वापस;
	अगर (so->so_is_खोलो_owner)
		release_last_बंदd_stateid(खोलोowner(so));
	so->so_seqid++;
	वापस;
पूर्ण

अटल व्योम
gen_sessionid(काष्ठा nfsd4_session *ses)
अणु
	काष्ठा nfs4_client *clp = ses->se_client;
	काष्ठा nfsd4_sessionid *sid;

	sid = (काष्ठा nfsd4_sessionid *)ses->se_sessionid.data;
	sid->clientid = clp->cl_clientid;
	sid->sequence = current_sessionid++;
	sid->reserved = 0;
पूर्ण

/*
 * The protocol defines ca_maxresponssize_cached to include the size of
 * the rpc header, but all we need to cache is the data starting after
 * the end of the initial SEQUENCE operation--the rest we regenerate
 * each समय.  Thereक्रमe we can advertise a ca_maxresponssize_cached
 * value that is the number of bytes in our cache plus a few additional
 * bytes.  In order to stay on the safe side, and not promise more than
 * we can cache, those additional bytes must be the minimum possible: 24
 * bytes of rpc header (xid through accept state, with AUTH_शून्य
 * verअगरier), 12 क्रम the compound header (with zero-length tag), and 44
 * क्रम the SEQUENCE op response:
 */
#घोषणा NFSD_MIN_HDR_SEQ_SZ  (24 + 12 + 44)

अटल व्योम
मुक्त_session_slots(काष्ठा nfsd4_session *ses)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ses->se_fchannel.maxreqs; i++) अणु
		मुक्त_svc_cred(&ses->se_slots[i]->sl_cred);
		kमुक्त(ses->se_slots[i]);
	पूर्ण
पूर्ण

/*
 * We करोn't actually need to cache the rpc and session headers, so we
 * can allocate a little less क्रम each slot:
 */
अटल अंतरभूत u32 slot_bytes(काष्ठा nfsd4_channel_attrs *ca)
अणु
	u32 size;

	अगर (ca->maxresp_cached < NFSD_MIN_HDR_SEQ_SZ)
		size = 0;
	अन्यथा
		size = ca->maxresp_cached - NFSD_MIN_HDR_SEQ_SZ;
	वापस size + माप(काष्ठा nfsd4_slot);
पूर्ण

/*
 * XXX: If we run out of reserved DRC memory we could (up to a poपूर्णांक)
 * re-negotiate active sessions and reduce their slot usage to make
 * room क्रम new connections. For now we just fail the create session.
 */
अटल u32 nfsd4_get_drc_mem(काष्ठा nfsd4_channel_attrs *ca, काष्ठा nfsd_net *nn)
अणु
	u32 slotsize = slot_bytes(ca);
	u32 num = ca->maxreqs;
	अचिन्हित दीर्घ avail, total_avail;
	अचिन्हित पूर्णांक scale_factor;

	spin_lock(&nfsd_drc_lock);
	अगर (nfsd_drc_max_mem > nfsd_drc_mem_used)
		total_avail = nfsd_drc_max_mem - nfsd_drc_mem_used;
	अन्यथा
		/* We have handed out more space than we chose in
		 * set_max_drc() to allow.  That isn't really a
		 * problem as दीर्घ as that करोesn't make us think we
		 * have lots more due to पूर्णांकeger overflow.
		 */
		total_avail = 0;
	avail = min((अचिन्हित दीर्घ)NFSD_MAX_MEM_PER_SESSION, total_avail);
	/*
	 * Never use more than a fraction of the reमुख्यing memory,
	 * unless it's the only way to give this client a slot.
	 * The chosen fraction is either 1/8 or 1/number of thपढ़ोs,
	 * whichever is smaller.  This ensures there are adequate
	 * slots to support multiple clients per thपढ़ो.
	 * Give the client one slot even अगर that would require
	 * over-allocation--it is better than failure.
	 */
	scale_factor = max_t(अचिन्हित पूर्णांक, 8, nn->nfsd_serv->sv_nrthपढ़ोs);

	avail = clamp_t(अचिन्हित दीर्घ, avail, slotsize,
			total_avail/scale_factor);
	num = min_t(पूर्णांक, num, avail / slotsize);
	num = max_t(पूर्णांक, num, 1);
	nfsd_drc_mem_used += num * slotsize;
	spin_unlock(&nfsd_drc_lock);

	वापस num;
पूर्ण

अटल व्योम nfsd4_put_drc_mem(काष्ठा nfsd4_channel_attrs *ca)
अणु
	पूर्णांक slotsize = slot_bytes(ca);

	spin_lock(&nfsd_drc_lock);
	nfsd_drc_mem_used -= slotsize * ca->maxreqs;
	spin_unlock(&nfsd_drc_lock);
पूर्ण

अटल काष्ठा nfsd4_session *alloc_session(काष्ठा nfsd4_channel_attrs *fattrs,
					   काष्ठा nfsd4_channel_attrs *battrs)
अणु
	पूर्णांक numslots = fattrs->maxreqs;
	पूर्णांक slotsize = slot_bytes(fattrs);
	काष्ठा nfsd4_session *new;
	पूर्णांक mem, i;

	BUILD_BUG_ON(NFSD_MAX_SLOTS_PER_SESSION * माप(काष्ठा nfsd4_slot *)
			+ माप(काष्ठा nfsd4_session) > PAGE_SIZE);
	mem = numslots * माप(काष्ठा nfsd4_slot *);

	new = kzalloc(माप(*new) + mem, GFP_KERNEL);
	अगर (!new)
		वापस शून्य;
	/* allocate each काष्ठा nfsd4_slot and data cache in one piece */
	क्रम (i = 0; i < numslots; i++) अणु
		new->se_slots[i] = kzalloc(slotsize, GFP_KERNEL);
		अगर (!new->se_slots[i])
			जाओ out_मुक्त;
	पूर्ण

	स_नकल(&new->se_fchannel, fattrs, माप(काष्ठा nfsd4_channel_attrs));
	स_नकल(&new->se_bchannel, battrs, माप(काष्ठा nfsd4_channel_attrs));

	वापस new;
out_मुक्त:
	जबतक (i--)
		kमुक्त(new->se_slots[i]);
	kमुक्त(new);
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_conn(काष्ठा nfsd4_conn *c)
अणु
	svc_xprt_put(c->cn_xprt);
	kमुक्त(c);
पूर्ण

अटल व्योम nfsd4_conn_lost(काष्ठा svc_xpt_user *u)
अणु
	काष्ठा nfsd4_conn *c = container_of(u, काष्ठा nfsd4_conn, cn_xpt_user);
	काष्ठा nfs4_client *clp = c->cn_session->se_client;

	spin_lock(&clp->cl_lock);
	अगर (!list_empty(&c->cn_persession)) अणु
		list_del(&c->cn_persession);
		मुक्त_conn(c);
	पूर्ण
	nfsd4_probe_callback(clp);
	spin_unlock(&clp->cl_lock);
पूर्ण

अटल काष्ठा nfsd4_conn *alloc_conn(काष्ठा svc_rqst *rqstp, u32 flags)
अणु
	काष्ठा nfsd4_conn *conn;

	conn = kदो_स्मृति(माप(काष्ठा nfsd4_conn), GFP_KERNEL);
	अगर (!conn)
		वापस शून्य;
	svc_xprt_get(rqstp->rq_xprt);
	conn->cn_xprt = rqstp->rq_xprt;
	conn->cn_flags = flags;
	INIT_LIST_HEAD(&conn->cn_xpt_user.list);
	वापस conn;
पूर्ण

अटल व्योम __nfsd4_hash_conn(काष्ठा nfsd4_conn *conn, काष्ठा nfsd4_session *ses)
अणु
	conn->cn_session = ses;
	list_add(&conn->cn_persession, &ses->se_conns);
पूर्ण

अटल व्योम nfsd4_hash_conn(काष्ठा nfsd4_conn *conn, काष्ठा nfsd4_session *ses)
अणु
	काष्ठा nfs4_client *clp = ses->se_client;

	spin_lock(&clp->cl_lock);
	__nfsd4_hash_conn(conn, ses);
	spin_unlock(&clp->cl_lock);
पूर्ण

अटल पूर्णांक nfsd4_रेजिस्टर_conn(काष्ठा nfsd4_conn *conn)
अणु
	conn->cn_xpt_user.callback = nfsd4_conn_lost;
	वापस रेजिस्टर_xpt_user(conn->cn_xprt, &conn->cn_xpt_user);
पूर्ण

अटल व्योम nfsd4_init_conn(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_conn *conn, काष्ठा nfsd4_session *ses)
अणु
	पूर्णांक ret;

	nfsd4_hash_conn(conn, ses);
	ret = nfsd4_रेजिस्टर_conn(conn);
	अगर (ret)
		/* oops; xprt is alपढ़ोy करोwn: */
		nfsd4_conn_lost(&conn->cn_xpt_user);
	/* We may have gained or lost a callback channel: */
	nfsd4_probe_callback_sync(ses->se_client);
पूर्ण

अटल काष्ठा nfsd4_conn *alloc_conn_from_crses(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_create_session *cses)
अणु
	u32 dir = NFS4_CDFC4_FORE;

	अगर (cses->flags & SESSION4_BACK_CHAN)
		dir |= NFS4_CDFC4_BACK;
	वापस alloc_conn(rqstp, dir);
पूर्ण

/* must be called under client_lock */
अटल व्योम nfsd4_del_conns(काष्ठा nfsd4_session *s)
अणु
	काष्ठा nfs4_client *clp = s->se_client;
	काष्ठा nfsd4_conn *c;

	spin_lock(&clp->cl_lock);
	जबतक (!list_empty(&s->se_conns)) अणु
		c = list_first_entry(&s->se_conns, काष्ठा nfsd4_conn, cn_persession);
		list_del_init(&c->cn_persession);
		spin_unlock(&clp->cl_lock);

		unरेजिस्टर_xpt_user(c->cn_xprt, &c->cn_xpt_user);
		मुक्त_conn(c);

		spin_lock(&clp->cl_lock);
	पूर्ण
	spin_unlock(&clp->cl_lock);
पूर्ण

अटल व्योम __मुक्त_session(काष्ठा nfsd4_session *ses)
अणु
	मुक्त_session_slots(ses);
	kमुक्त(ses);
पूर्ण

अटल व्योम मुक्त_session(काष्ठा nfsd4_session *ses)
अणु
	nfsd4_del_conns(ses);
	nfsd4_put_drc_mem(&ses->se_fchannel);
	__मुक्त_session(ses);
पूर्ण

अटल व्योम init_session(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_session *new, काष्ठा nfs4_client *clp, काष्ठा nfsd4_create_session *cses)
अणु
	पूर्णांक idx;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	new->se_client = clp;
	gen_sessionid(new);

	INIT_LIST_HEAD(&new->se_conns);

	new->se_cb_seq_nr = 1;
	new->se_flags = cses->flags;
	new->se_cb_prog = cses->callback_prog;
	new->se_cb_sec = cses->cb_sec;
	atomic_set(&new->se_ref, 0);
	idx = hash_sessionid(&new->se_sessionid);
	list_add(&new->se_hash, &nn->sessionid_hashtbl[idx]);
	spin_lock(&clp->cl_lock);
	list_add(&new->se_perclnt, &clp->cl_sessions);
	spin_unlock(&clp->cl_lock);

	अणु
		काष्ठा sockaddr *sa = svc_addr(rqstp);
		/*
		 * This is a little silly; with sessions there's no real
		 * use क्रम the callback address.  Use the peer address
		 * as a reasonable शेष क्रम now, but consider fixing
		 * the rpc client not to require an address in the
		 * future:
		 */
		rpc_copy_addr((काष्ठा sockaddr *)&clp->cl_cb_conn.cb_addr, sa);
		clp->cl_cb_conn.cb_addrlen = svc_addr_len(sa);
	पूर्ण
पूर्ण

/* caller must hold client_lock */
अटल काष्ठा nfsd4_session *
__find_in_sessionid_hashtbl(काष्ठा nfs4_sessionid *sessionid, काष्ठा net *net)
अणु
	काष्ठा nfsd4_session *elem;
	पूर्णांक idx;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	lockdep_निश्चित_held(&nn->client_lock);

	dump_sessionid(__func__, sessionid);
	idx = hash_sessionid(sessionid);
	/* Search in the appropriate list */
	list_क्रम_each_entry(elem, &nn->sessionid_hashtbl[idx], se_hash) अणु
		अगर (!स_भेद(elem->se_sessionid.data, sessionid->data,
			    NFS4_MAX_SESSIONID_LEN)) अणु
			वापस elem;
		पूर्ण
	पूर्ण

	dprपूर्णांकk("%s: session not found\n", __func__);
	वापस शून्य;
पूर्ण

अटल काष्ठा nfsd4_session *
find_in_sessionid_hashtbl(काष्ठा nfs4_sessionid *sessionid, काष्ठा net *net,
		__be32 *ret)
अणु
	काष्ठा nfsd4_session *session;
	__be32 status = nfserr_badsession;

	session = __find_in_sessionid_hashtbl(sessionid, net);
	अगर (!session)
		जाओ out;
	status = nfsd4_get_session_locked(session);
	अगर (status)
		session = शून्य;
out:
	*ret = status;
	वापस session;
पूर्ण

/* caller must hold client_lock */
अटल व्योम
unhash_session(काष्ठा nfsd4_session *ses)
अणु
	काष्ठा nfs4_client *clp = ses->se_client;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_निश्चित_held(&nn->client_lock);

	list_del(&ses->se_hash);
	spin_lock(&ses->se_client->cl_lock);
	list_del(&ses->se_perclnt);
	spin_unlock(&ses->se_client->cl_lock);
पूर्ण

/* SETCLIENTID and SETCLIENTID_CONFIRM Helper functions */
अटल पूर्णांक
STALE_CLIENTID(clientid_t *clid, काष्ठा nfsd_net *nn)
अणु
	/*
	 * We're assuming the clid was not given out from a boot
	 * precisely 2^32 (about 136 years) beक्रमe this one.  That seems
	 * a safe assumption:
	 */
	अगर (clid->cl_boot == (u32)nn->boot_समय)
		वापस 0;
	trace_nfsd_clid_stale(clid);
	वापस 1;
पूर्ण

/* 
 * XXX Should we use a slab cache ?
 * This type of memory management is somewhat inefficient, but we use it
 * anyway since SETCLIENTID is not a common operation.
 */
अटल काष्ठा nfs4_client *alloc_client(काष्ठा xdr_netobj name)
अणु
	काष्ठा nfs4_client *clp;
	पूर्णांक i;

	clp = kmem_cache_zalloc(client_slab, GFP_KERNEL);
	अगर (clp == शून्य)
		वापस शून्य;
	xdr_netobj_dup(&clp->cl_name, &name, GFP_KERNEL);
	अगर (clp->cl_name.data == शून्य)
		जाओ err_no_name;
	clp->cl_ownerstr_hashtbl = kदो_स्मृति_array(OWNER_HASH_SIZE,
						 माप(काष्ठा list_head),
						 GFP_KERNEL);
	अगर (!clp->cl_ownerstr_hashtbl)
		जाओ err_no_hashtbl;
	क्रम (i = 0; i < OWNER_HASH_SIZE; i++)
		INIT_LIST_HEAD(&clp->cl_ownerstr_hashtbl[i]);
	INIT_LIST_HEAD(&clp->cl_sessions);
	idr_init(&clp->cl_stateids);
	atomic_set(&clp->cl_rpc_users, 0);
	clp->cl_cb_state = NFSD4_CB_UNKNOWN;
	INIT_LIST_HEAD(&clp->cl_idhash);
	INIT_LIST_HEAD(&clp->cl_खोलोowners);
	INIT_LIST_HEAD(&clp->cl_delegations);
	INIT_LIST_HEAD(&clp->cl_lru);
	INIT_LIST_HEAD(&clp->cl_revoked);
#अगर_घोषित CONFIG_NFSD_PNFS
	INIT_LIST_HEAD(&clp->cl_lo_states);
#पूर्ण_अगर
	INIT_LIST_HEAD(&clp->async_copies);
	spin_lock_init(&clp->async_lock);
	spin_lock_init(&clp->cl_lock);
	rpc_init_रुको_queue(&clp->cl_cb_रुकोq, "Backchannel slot table");
	वापस clp;
err_no_hashtbl:
	kमुक्त(clp->cl_name.data);
err_no_name:
	kmem_cache_मुक्त(client_slab, clp);
	वापस शून्य;
पूर्ण

अटल व्योम __मुक्त_client(काष्ठा kref *k)
अणु
	काष्ठा nfsdfs_client *c = container_of(k, काष्ठा nfsdfs_client, cl_ref);
	काष्ठा nfs4_client *clp = container_of(c, काष्ठा nfs4_client, cl_nfsdfs);

	मुक्त_svc_cred(&clp->cl_cred);
	kमुक्त(clp->cl_ownerstr_hashtbl);
	kमुक्त(clp->cl_name.data);
	kमुक्त(clp->cl_nii_करोमुख्य.data);
	kमुक्त(clp->cl_nii_name.data);
	idr_destroy(&clp->cl_stateids);
	kmem_cache_मुक्त(client_slab, clp);
पूर्ण

अटल व्योम drop_client(काष्ठा nfs4_client *clp)
अणु
	kref_put(&clp->cl_nfsdfs.cl_ref, __मुक्त_client);
पूर्ण

अटल व्योम
मुक्त_client(काष्ठा nfs4_client *clp)
अणु
	जबतक (!list_empty(&clp->cl_sessions)) अणु
		काष्ठा nfsd4_session *ses;
		ses = list_entry(clp->cl_sessions.next, काष्ठा nfsd4_session,
				se_perclnt);
		list_del(&ses->se_perclnt);
		WARN_ON_ONCE(atomic_पढ़ो(&ses->se_ref));
		मुक्त_session(ses);
	पूर्ण
	rpc_destroy_रुको_queue(&clp->cl_cb_रुकोq);
	अगर (clp->cl_nfsd_dentry) अणु
		nfsd_client_सूची_हटाओ(clp->cl_nfsd_dentry);
		clp->cl_nfsd_dentry = शून्य;
		wake_up_all(&expiry_wq);
	पूर्ण
	drop_client(clp);
पूर्ण

/* must be called under the client_lock */
अटल व्योम
unhash_client_locked(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	काष्ठा nfsd4_session *ses;

	lockdep_निश्चित_held(&nn->client_lock);

	/* Mark the client as expired! */
	clp->cl_समय = 0;
	/* Make it invisible */
	अगर (!list_empty(&clp->cl_idhash)) अणु
		list_del_init(&clp->cl_idhash);
		अगर (test_bit(NFSD4_CLIENT_CONFIRMED, &clp->cl_flags))
			rb_erase(&clp->cl_namenode, &nn->conf_name_tree);
		अन्यथा
			rb_erase(&clp->cl_namenode, &nn->unconf_name_tree);
	पूर्ण
	list_del_init(&clp->cl_lru);
	spin_lock(&clp->cl_lock);
	list_क्रम_each_entry(ses, &clp->cl_sessions, se_perclnt)
		list_del_init(&ses->se_hash);
	spin_unlock(&clp->cl_lock);
पूर्ण

अटल व्योम
unhash_client(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	spin_lock(&nn->client_lock);
	unhash_client_locked(clp);
	spin_unlock(&nn->client_lock);
पूर्ण

अटल __be32 mark_client_expired_locked(काष्ठा nfs4_client *clp)
अणु
	अगर (atomic_पढ़ो(&clp->cl_rpc_users))
		वापस nfserr_jukebox;
	unhash_client_locked(clp);
	वापस nfs_ok;
पूर्ण

अटल व्योम
__destroy_client(काष्ठा nfs4_client *clp)
अणु
	पूर्णांक i;
	काष्ठा nfs4_खोलोowner *oo;
	काष्ठा nfs4_delegation *dp;
	काष्ठा list_head reaplist;

	INIT_LIST_HEAD(&reaplist);
	spin_lock(&state_lock);
	जबतक (!list_empty(&clp->cl_delegations)) अणु
		dp = list_entry(clp->cl_delegations.next, काष्ठा nfs4_delegation, dl_perclnt);
		WARN_ON(!unhash_delegation_locked(dp));
		list_add(&dp->dl_recall_lru, &reaplist);
	पूर्ण
	spin_unlock(&state_lock);
	जबतक (!list_empty(&reaplist)) अणु
		dp = list_entry(reaplist.next, काष्ठा nfs4_delegation, dl_recall_lru);
		list_del_init(&dp->dl_recall_lru);
		destroy_unhashed_deleg(dp);
	पूर्ण
	जबतक (!list_empty(&clp->cl_revoked)) अणु
		dp = list_entry(clp->cl_revoked.next, काष्ठा nfs4_delegation, dl_recall_lru);
		list_del_init(&dp->dl_recall_lru);
		nfs4_put_stid(&dp->dl_stid);
	पूर्ण
	जबतक (!list_empty(&clp->cl_खोलोowners)) अणु
		oo = list_entry(clp->cl_खोलोowners.next, काष्ठा nfs4_खोलोowner, oo_perclient);
		nfs4_get_stateowner(&oo->oo_owner);
		release_खोलोowner(oo);
	पूर्ण
	क्रम (i = 0; i < OWNER_HASH_SIZE; i++) अणु
		काष्ठा nfs4_stateowner *so, *पंचांगp;

		list_क्रम_each_entry_safe(so, पंचांगp, &clp->cl_ownerstr_hashtbl[i],
					 so_strhash) अणु
			/* Should be no खोलोowners at this poपूर्णांक */
			WARN_ON_ONCE(so->so_is_खोलो_owner);
			हटाओ_blocked_locks(lockowner(so));
		पूर्ण
	पूर्ण
	nfsd4_वापस_all_client_layouts(clp);
	nfsd4_shutकरोwn_copy(clp);
	nfsd4_shutकरोwn_callback(clp);
	अगर (clp->cl_cb_conn.cb_xprt)
		svc_xprt_put(clp->cl_cb_conn.cb_xprt);
	मुक्त_client(clp);
	wake_up_all(&expiry_wq);
पूर्ण

अटल व्योम
destroy_client(काष्ठा nfs4_client *clp)
अणु
	unhash_client(clp);
	__destroy_client(clp);
पूर्ण

अटल व्योम inc_reclaim_complete(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	अगर (!nn->track_reclaim_completes)
		वापस;
	अगर (!nfsd4_find_reclaim_client(clp->cl_name, nn))
		वापस;
	अगर (atomic_inc_वापस(&nn->nr_reclaim_complete) ==
			nn->reclaim_str_hashtbl_size) अणु
		prपूर्णांकk(KERN_INFO "NFSD: all clients done reclaiming, ending NFSv4 grace period (net %x)\n",
				clp->net->ns.inum);
		nfsd4_end_grace(nn);
	पूर्ण
पूर्ण

अटल व्योम expire_client(काष्ठा nfs4_client *clp)
अणु
	unhash_client(clp);
	nfsd4_client_record_हटाओ(clp);
	__destroy_client(clp);
पूर्ण

अटल व्योम copy_verf(काष्ठा nfs4_client *target, nfs4_verअगरier *source)
अणु
	स_नकल(target->cl_verअगरier.data, source->data,
			माप(target->cl_verअगरier.data));
पूर्ण

अटल व्योम copy_clid(काष्ठा nfs4_client *target, काष्ठा nfs4_client *source)
अणु
	target->cl_clientid.cl_boot = source->cl_clientid.cl_boot; 
	target->cl_clientid.cl_id = source->cl_clientid.cl_id; 
पूर्ण

अटल पूर्णांक copy_cred(काष्ठा svc_cred *target, काष्ठा svc_cred *source)
अणु
	target->cr_principal = kstrdup(source->cr_principal, GFP_KERNEL);
	target->cr_raw_principal = kstrdup(source->cr_raw_principal,
								GFP_KERNEL);
	target->cr_targ_princ = kstrdup(source->cr_targ_princ, GFP_KERNEL);
	अगर ((source->cr_principal && !target->cr_principal) ||
	    (source->cr_raw_principal && !target->cr_raw_principal) ||
	    (source->cr_targ_princ && !target->cr_targ_princ))
		वापस -ENOMEM;

	target->cr_flavor = source->cr_flavor;
	target->cr_uid = source->cr_uid;
	target->cr_gid = source->cr_gid;
	target->cr_group_info = source->cr_group_info;
	get_group_info(target->cr_group_info);
	target->cr_gss_mech = source->cr_gss_mech;
	अगर (source->cr_gss_mech)
		gss_mech_get(source->cr_gss_mech);
	वापस 0;
पूर्ण

अटल पूर्णांक
compare_blob(स्थिर काष्ठा xdr_netobj *o1, स्थिर काष्ठा xdr_netobj *o2)
अणु
	अगर (o1->len < o2->len)
		वापस -1;
	अगर (o1->len > o2->len)
		वापस 1;
	वापस स_भेद(o1->data, o2->data, o1->len);
पूर्ण

अटल पूर्णांक
same_verf(nfs4_verअगरier *v1, nfs4_verअगरier *v2)
अणु
	वापस 0 == स_भेद(v1->data, v2->data, माप(v1->data));
पूर्ण

अटल पूर्णांक
same_clid(clientid_t *cl1, clientid_t *cl2)
अणु
	वापस (cl1->cl_boot == cl2->cl_boot) && (cl1->cl_id == cl2->cl_id);
पूर्ण

अटल bool groups_equal(काष्ठा group_info *g1, काष्ठा group_info *g2)
अणु
	पूर्णांक i;

	अगर (g1->ngroups != g2->ngroups)
		वापस false;
	क्रम (i=0; i<g1->ngroups; i++)
		अगर (!gid_eq(g1->gid[i], g2->gid[i]))
			वापस false;
	वापस true;
पूर्ण

/*
 * RFC 3530 language requires clid_inuse be वापसed when the
 * "principal" associated with a requests dअगरfers from that previously
 * used.  We use uid, gid's, and gss principal string as our best
 * approximation.  We also करोn't want to allow non-gss use of a client
 * established using gss: in theory cr_principal should catch that
 * change, but in practice cr_principal can be null even in the gss हाल
 * since gssd करोesn't always pass करोwn a principal string.
 */
अटल bool is_gss_cred(काष्ठा svc_cred *cr)
अणु
	/* Is cr_flavor one of the gss "pseudoflavors"?: */
	वापस (cr->cr_flavor > RPC_AUTH_MAXFLAVOR);
पूर्ण


अटल bool
same_creds(काष्ठा svc_cred *cr1, काष्ठा svc_cred *cr2)
अणु
	अगर ((is_gss_cred(cr1) != is_gss_cred(cr2))
		|| (!uid_eq(cr1->cr_uid, cr2->cr_uid))
		|| (!gid_eq(cr1->cr_gid, cr2->cr_gid))
		|| !groups_equal(cr1->cr_group_info, cr2->cr_group_info))
		वापस false;
	/* XXX: check that cr_targ_princ fields match ? */
	अगर (cr1->cr_principal == cr2->cr_principal)
		वापस true;
	अगर (!cr1->cr_principal || !cr2->cr_principal)
		वापस false;
	वापस 0 == म_भेद(cr1->cr_principal, cr2->cr_principal);
पूर्ण

अटल bool svc_rqst_पूर्णांकegrity_रक्षित(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_cred *cr = &rqstp->rq_cred;
	u32 service;

	अगर (!cr->cr_gss_mech)
		वापस false;
	service = gss_pseuकरोflavor_to_service(cr->cr_gss_mech, cr->cr_flavor);
	वापस service == RPC_GSS_SVC_INTEGRITY ||
	       service == RPC_GSS_SVC_PRIVACY;
पूर्ण

bool nfsd4_mach_creds_match(काष्ठा nfs4_client *cl, काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_cred *cr = &rqstp->rq_cred;

	अगर (!cl->cl_mach_cred)
		वापस true;
	अगर (cl->cl_cred.cr_gss_mech != cr->cr_gss_mech)
		वापस false;
	अगर (!svc_rqst_पूर्णांकegrity_रक्षित(rqstp))
		वापस false;
	अगर (cl->cl_cred.cr_raw_principal)
		वापस 0 == म_भेद(cl->cl_cred.cr_raw_principal,
						cr->cr_raw_principal);
	अगर (!cr->cr_principal)
		वापस false;
	वापस 0 == म_भेद(cl->cl_cred.cr_principal, cr->cr_principal);
पूर्ण

अटल व्योम gen_confirm(काष्ठा nfs4_client *clp, काष्ठा nfsd_net *nn)
अणु
	__be32 verf[2];

	/*
	 * This is opaque to client, so no need to byte-swap. Use
	 * __क्रमce to keep sparse happy
	 */
	verf[0] = (__क्रमce __be32)(u32)kसमय_get_real_seconds();
	verf[1] = (__क्रमce __be32)nn->clverअगरier_counter++;
	स_नकल(clp->cl_confirm.data, verf, माप(clp->cl_confirm.data));
पूर्ण

अटल व्योम gen_clid(काष्ठा nfs4_client *clp, काष्ठा nfsd_net *nn)
अणु
	clp->cl_clientid.cl_boot = (u32)nn->boot_समय;
	clp->cl_clientid.cl_id = nn->clientid_counter++;
	gen_confirm(clp, nn);
पूर्ण

अटल काष्ठा nfs4_stid *
find_stateid_locked(काष्ठा nfs4_client *cl, stateid_t *t)
अणु
	काष्ठा nfs4_stid *ret;

	ret = idr_find(&cl->cl_stateids, t->si_opaque.so_id);
	अगर (!ret || !ret->sc_type)
		वापस शून्य;
	वापस ret;
पूर्ण

अटल काष्ठा nfs4_stid *
find_stateid_by_type(काष्ठा nfs4_client *cl, stateid_t *t, अक्षर typemask)
अणु
	काष्ठा nfs4_stid *s;

	spin_lock(&cl->cl_lock);
	s = find_stateid_locked(cl, t);
	अगर (s != शून्य) अणु
		अगर (typemask & s->sc_type)
			refcount_inc(&s->sc_count);
		अन्यथा
			s = शून्य;
	पूर्ण
	spin_unlock(&cl->cl_lock);
	वापस s;
पूर्ण

अटल काष्ठा nfs4_client *get_nfsdfs_clp(काष्ठा inode *inode)
अणु
	काष्ठा nfsdfs_client *nc;
	nc = get_nfsdfs_client(inode);
	अगर (!nc)
		वापस शून्य;
	वापस container_of(nc, काष्ठा nfs4_client, cl_nfsdfs);
पूर्ण

अटल व्योम seq_quote_mem(काष्ठा seq_file *m, अक्षर *data, पूर्णांक len)
अणु
	seq_म_लिखो(m, "\"");
	seq_escape_mem_ascii(m, data, len);
	seq_म_लिखो(m, "\"");
पूर्ण

अटल पूर्णांक client_info_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा inode *inode = m->निजी;
	काष्ठा nfs4_client *clp;
	u64 clid;

	clp = get_nfsdfs_clp(inode);
	अगर (!clp)
		वापस -ENXIO;
	स_नकल(&clid, &clp->cl_clientid, माप(clid));
	seq_म_लिखो(m, "clientid: 0x%llx\n", clid);
	seq_म_लिखो(m, "address: \"%pISpc\"\n", (काष्ठा sockaddr *)&clp->cl_addr);
	अगर (test_bit(NFSD4_CLIENT_CONFIRMED, &clp->cl_flags))
		seq_माला_दो(m, "status: confirmed\n");
	अन्यथा
		seq_माला_दो(m, "status: unconfirmed\n");
	seq_म_लिखो(m, "name: ");
	seq_quote_mem(m, clp->cl_name.data, clp->cl_name.len);
	seq_म_लिखो(m, "\nminor version: %d\n", clp->cl_minorversion);
	अगर (clp->cl_nii_करोमुख्य.data) अणु
		seq_म_लिखो(m, "Implementation domain: ");
		seq_quote_mem(m, clp->cl_nii_करोमुख्य.data,
					clp->cl_nii_करोमुख्य.len);
		seq_म_लिखो(m, "\nImplementation name: ");
		seq_quote_mem(m, clp->cl_nii_name.data, clp->cl_nii_name.len);
		seq_म_लिखो(m, "\nImplementation time: [%lld, %ld]\n",
			clp->cl_nii_समय.tv_sec, clp->cl_nii_समय.tv_nsec);
	पूर्ण
	drop_client(clp);

	वापस 0;
पूर्ण

अटल पूर्णांक client_info_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, client_info_show, inode);
पूर्ण

अटल स्थिर काष्ठा file_operations client_info_fops = अणु
	.खोलो		= client_info_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल व्योम *states_start(काष्ठा seq_file *s, loff_t *pos)
	__acquires(&clp->cl_lock)
अणु
	काष्ठा nfs4_client *clp = s->निजी;
	अचिन्हित दीर्घ id = *pos;
	व्योम *ret;

	spin_lock(&clp->cl_lock);
	ret = idr_get_next_ul(&clp->cl_stateids, &id);
	*pos = id;
	वापस ret;
पूर्ण

अटल व्योम *states_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा nfs4_client *clp = s->निजी;
	अचिन्हित दीर्घ id = *pos;
	व्योम *ret;

	id = *pos;
	id++;
	ret = idr_get_next_ul(&clp->cl_stateids, &id);
	*pos = id;
	वापस ret;
पूर्ण

अटल व्योम states_stop(काष्ठा seq_file *s, व्योम *v)
	__releases(&clp->cl_lock)
अणु
	काष्ठा nfs4_client *clp = s->निजी;

	spin_unlock(&clp->cl_lock);
पूर्ण

अटल व्योम nfs4_show_fname(काष्ठा seq_file *s, काष्ठा nfsd_file *f)
अणु
         seq_म_लिखो(s, "filename: \"%pD2\"", f->nf_file);
पूर्ण

अटल व्योम nfs4_show_superblock(काष्ठा seq_file *s, काष्ठा nfsd_file *f)
अणु
	काष्ठा inode *inode = f->nf_inode;

	seq_म_लिखो(s, "superblock: \"%02x:%02x:%ld\"",
					MAJOR(inode->i_sb->s_dev),
					 MINOR(inode->i_sb->s_dev),
					 inode->i_ino);
पूर्ण

अटल व्योम nfs4_show_owner(काष्ठा seq_file *s, काष्ठा nfs4_stateowner *oo)
अणु
	seq_म_लिखो(s, "owner: ");
	seq_quote_mem(s, oo->so_owner.data, oo->so_owner.len);
पूर्ण

अटल व्योम nfs4_show_stateid(काष्ठा seq_file *s, stateid_t *stid)
अणु
	seq_म_लिखो(s, "0x%.8x", stid->si_generation);
	seq_म_लिखो(s, "%12phN", &stid->si_opaque);
पूर्ण

अटल पूर्णांक nfs4_show_खोलो(काष्ठा seq_file *s, काष्ठा nfs4_stid *st)
अणु
	काष्ठा nfs4_ol_stateid *ols;
	काष्ठा nfs4_file *nf;
	काष्ठा nfsd_file *file;
	काष्ठा nfs4_stateowner *oo;
	अचिन्हित पूर्णांक access, deny;

	अगर (st->sc_type != NFS4_OPEN_STID && st->sc_type != NFS4_LOCK_STID)
		वापस 0; /* XXX: or SEQ_SKIP? */
	ols = खोलोlockstateid(st);
	oo = ols->st_stateowner;
	nf = st->sc_file;
	file = find_any_file(nf);
	अगर (!file)
		वापस 0;

	seq_म_लिखो(s, "- ");
	nfs4_show_stateid(s, &st->sc_stateid);
	seq_म_लिखो(s, ": { type: open, ");

	access = bmap_to_share_mode(ols->st_access_bmap);
	deny   = bmap_to_share_mode(ols->st_deny_bmap);

	seq_म_लिखो(s, "access: %s%s, ",
		access & NFS4_SHARE_ACCESS_READ ? "r" : "-",
		access & NFS4_SHARE_ACCESS_WRITE ? "w" : "-");
	seq_म_लिखो(s, "deny: %s%s, ",
		deny & NFS4_SHARE_ACCESS_READ ? "r" : "-",
		deny & NFS4_SHARE_ACCESS_WRITE ? "w" : "-");

	nfs4_show_superblock(s, file);
	seq_म_लिखो(s, ", ");
	nfs4_show_fname(s, file);
	seq_म_लिखो(s, ", ");
	nfs4_show_owner(s, oo);
	seq_म_लिखो(s, " }\n");
	nfsd_file_put(file);

	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_show_lock(काष्ठा seq_file *s, काष्ठा nfs4_stid *st)
अणु
	काष्ठा nfs4_ol_stateid *ols;
	काष्ठा nfs4_file *nf;
	काष्ठा nfsd_file *file;
	काष्ठा nfs4_stateowner *oo;

	ols = खोलोlockstateid(st);
	oo = ols->st_stateowner;
	nf = st->sc_file;
	file = find_any_file(nf);
	अगर (!file)
		वापस 0;

	seq_म_लिखो(s, "- ");
	nfs4_show_stateid(s, &st->sc_stateid);
	seq_म_लिखो(s, ": { type: lock, ");

	/*
	 * Note: a lock stateid isn't really the same thing as a lock,
	 * it's the locking state held by one owner on a file, and there
	 * may be multiple (or no) lock ranges associated with it.
	 * (Same क्रम the matter is true of खोलो stateids.)
	 */

	nfs4_show_superblock(s, file);
	/* XXX: खोलो stateid? */
	seq_म_लिखो(s, ", ");
	nfs4_show_fname(s, file);
	seq_म_लिखो(s, ", ");
	nfs4_show_owner(s, oo);
	seq_म_लिखो(s, " }\n");
	nfsd_file_put(file);

	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_show_deleg(काष्ठा seq_file *s, काष्ठा nfs4_stid *st)
अणु
	काष्ठा nfs4_delegation *ds;
	काष्ठा nfs4_file *nf;
	काष्ठा nfsd_file *file;

	ds = delegstateid(st);
	nf = st->sc_file;
	file = find_deleg_file(nf);
	अगर (!file)
		वापस 0;

	seq_म_लिखो(s, "- ");
	nfs4_show_stateid(s, &st->sc_stateid);
	seq_म_लिखो(s, ": { type: deleg, ");

	/* Kinda dead code as दीर्घ as we only support पढ़ो delegs: */
	seq_म_लिखो(s, "access: %s, ",
		ds->dl_type == NFS4_OPEN_DELEGATE_READ ? "r" : "w");

	/* XXX: lease समय, whether it's being recalled. */

	nfs4_show_superblock(s, file);
	seq_म_लिखो(s, ", ");
	nfs4_show_fname(s, file);
	seq_म_लिखो(s, " }\n");
	nfsd_file_put(file);

	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_show_layout(काष्ठा seq_file *s, काष्ठा nfs4_stid *st)
अणु
	काष्ठा nfs4_layout_stateid *ls;
	काष्ठा nfsd_file *file;

	ls = container_of(st, काष्ठा nfs4_layout_stateid, ls_stid);
	file = ls->ls_file;

	seq_म_लिखो(s, "- ");
	nfs4_show_stateid(s, &st->sc_stateid);
	seq_म_लिखो(s, ": { type: layout, ");

	/* XXX: What अन्यथा would be useful? */

	nfs4_show_superblock(s, file);
	seq_म_लिखो(s, ", ");
	nfs4_show_fname(s, file);
	seq_म_लिखो(s, " }\n");

	वापस 0;
पूर्ण

अटल पूर्णांक states_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा nfs4_stid *st = v;

	चयन (st->sc_type) अणु
	हाल NFS4_OPEN_STID:
		वापस nfs4_show_खोलो(s, st);
	हाल NFS4_LOCK_STID:
		वापस nfs4_show_lock(s, st);
	हाल NFS4_DELEG_STID:
		वापस nfs4_show_deleg(s, st);
	हाल NFS4_LAYOUT_STID:
		वापस nfs4_show_layout(s, st);
	शेष:
		वापस 0; /* XXX: or SEQ_SKIP? */
	पूर्ण
	/* XXX: copy stateids? */
पूर्ण

अटल काष्ठा seq_operations states_seq_ops = अणु
	.start = states_start,
	.next = states_next,
	.stop = states_stop,
	.show = states_show
पूर्ण;

अटल पूर्णांक client_states_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *s;
	काष्ठा nfs4_client *clp;
	पूर्णांक ret;

	clp = get_nfsdfs_clp(inode);
	अगर (!clp)
		वापस -ENXIO;

	ret = seq_खोलो(file, &states_seq_ops);
	अगर (ret)
		वापस ret;
	s = file->निजी_data;
	s->निजी = clp;
	वापस 0;
पूर्ण

अटल पूर्णांक client_खोलोs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा nfs4_client *clp = m->निजी;

	/* XXX: alternatively, we could get/drop in seq start/stop */
	drop_client(clp);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations client_states_fops = अणु
	.खोलो		= client_states_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= client_खोलोs_release,
पूर्ण;

/*
 * Normally we refuse to destroy clients that are in use, but here the
 * administrator is telling us to just करो it.  We also want to रुको
 * so the caller has a guarantee that the client's locks are gone by
 * the समय the ग_लिखो वापसs:
 */
अटल व्योम क्रमce_expire_client(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);
	bool alपढ़ोy_expired;

	spin_lock(&clp->cl_lock);
	clp->cl_समय = 0;
	spin_unlock(&clp->cl_lock);

	रुको_event(expiry_wq, atomic_पढ़ो(&clp->cl_rpc_users) == 0);
	spin_lock(&nn->client_lock);
	alपढ़ोy_expired = list_empty(&clp->cl_lru);
	अगर (!alपढ़ोy_expired)
		unhash_client_locked(clp);
	spin_unlock(&nn->client_lock);

	अगर (!alपढ़ोy_expired)
		expire_client(clp);
	अन्यथा
		रुको_event(expiry_wq, clp->cl_nfsd_dentry == शून्य);
पूर्ण

अटल sमाप_प्रकार client_ctl_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार size, loff_t *pos)
अणु
	अक्षर *data;
	काष्ठा nfs4_client *clp;

	data = simple_transaction_get(file, buf, size);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	अगर (size != 7 || 0 != स_भेद(data, "expire\n", 7))
		वापस -EINVAL;
	clp = get_nfsdfs_clp(file_inode(file));
	अगर (!clp)
		वापस -ENXIO;
	क्रमce_expire_client(clp);
	drop_client(clp);
	वापस 7;
पूर्ण

अटल स्थिर काष्ठा file_operations client_ctl_fops = अणु
	.ग_लिखो		= client_ctl_ग_लिखो,
	.release	= simple_transaction_release,
पूर्ण;

अटल स्थिर काष्ठा tree_descr client_files[] = अणु
	[0] = अणु"info", &client_info_fops, S_IRUSRपूर्ण,
	[1] = अणु"states", &client_states_fops, S_IRUSRपूर्ण,
	[2] = अणु"ctl", &client_ctl_fops, S_IWUSRपूर्ण,
	[3] = अणु""पूर्ण,
पूर्ण;

अटल काष्ठा nfs4_client *create_client(काष्ठा xdr_netobj name,
		काष्ठा svc_rqst *rqstp, nfs4_verअगरier *verf)
अणु
	काष्ठा nfs4_client *clp;
	काष्ठा sockaddr *sa = svc_addr(rqstp);
	पूर्णांक ret;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा dentry *dentries[ARRAY_SIZE(client_files)];

	clp = alloc_client(name);
	अगर (clp == शून्य)
		वापस शून्य;

	ret = copy_cred(&clp->cl_cred, &rqstp->rq_cred);
	अगर (ret) अणु
		मुक्त_client(clp);
		वापस शून्य;
	पूर्ण
	gen_clid(clp, nn);
	kref_init(&clp->cl_nfsdfs.cl_ref);
	nfsd4_init_cb(&clp->cl_cb_null, clp, शून्य, NFSPROC4_CLNT_CB_शून्य);
	clp->cl_समय = kसमय_get_bootसमय_seconds();
	clear_bit(0, &clp->cl_cb_slot_busy);
	copy_verf(clp, verf);
	स_नकल(&clp->cl_addr, sa, माप(काष्ठा sockaddr_storage));
	clp->cl_cb_session = शून्य;
	clp->net = net;
	clp->cl_nfsd_dentry = nfsd_client_सूची_गढ़ो(
		nn, &clp->cl_nfsdfs,
		clp->cl_clientid.cl_id - nn->clientid_base,
		client_files, dentries);
	clp->cl_nfsd_info_dentry = dentries[0];
	अगर (!clp->cl_nfsd_dentry) अणु
		मुक्त_client(clp);
		वापस शून्य;
	पूर्ण
	वापस clp;
पूर्ण

अटल व्योम
add_clp_to_name_tree(काष्ठा nfs4_client *new_clp, काष्ठा rb_root *root)
अणु
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;
	काष्ठा nfs4_client *clp;

	जबतक (*new) अणु
		clp = rb_entry(*new, काष्ठा nfs4_client, cl_namenode);
		parent = *new;

		अगर (compare_blob(&clp->cl_name, &new_clp->cl_name) > 0)
			new = &((*new)->rb_left);
		अन्यथा
			new = &((*new)->rb_right);
	पूर्ण

	rb_link_node(&new_clp->cl_namenode, parent, new);
	rb_insert_color(&new_clp->cl_namenode, root);
पूर्ण

अटल काष्ठा nfs4_client *
find_clp_in_name_tree(काष्ठा xdr_netobj *name, काष्ठा rb_root *root)
अणु
	पूर्णांक cmp;
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा nfs4_client *clp;

	जबतक (node) अणु
		clp = rb_entry(node, काष्ठा nfs4_client, cl_namenode);
		cmp = compare_blob(&clp->cl_name, name);
		अगर (cmp > 0)
			node = node->rb_left;
		अन्यथा अगर (cmp < 0)
			node = node->rb_right;
		अन्यथा
			वापस clp;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
add_to_unconfirmed(काष्ठा nfs4_client *clp)
अणु
	अचिन्हित पूर्णांक idhashval;
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_निश्चित_held(&nn->client_lock);

	clear_bit(NFSD4_CLIENT_CONFIRMED, &clp->cl_flags);
	add_clp_to_name_tree(clp, &nn->unconf_name_tree);
	idhashval = clientid_hashval(clp->cl_clientid.cl_id);
	list_add(&clp->cl_idhash, &nn->unconf_id_hashtbl[idhashval]);
	renew_client_locked(clp);
पूर्ण

अटल व्योम
move_to_confirmed(काष्ठा nfs4_client *clp)
अणु
	अचिन्हित पूर्णांक idhashval = clientid_hashval(clp->cl_clientid.cl_id);
	काष्ठा nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_निश्चित_held(&nn->client_lock);

	dprपूर्णांकk("NFSD: move_to_confirm nfs4_client %p\n", clp);
	list_move(&clp->cl_idhash, &nn->conf_id_hashtbl[idhashval]);
	rb_erase(&clp->cl_namenode, &nn->unconf_name_tree);
	add_clp_to_name_tree(clp, &nn->conf_name_tree);
	अगर (!test_and_set_bit(NFSD4_CLIENT_CONFIRMED, &clp->cl_flags) &&
	    clp->cl_nfsd_dentry &&
	    clp->cl_nfsd_info_dentry)
		fsnotअगरy_dentry(clp->cl_nfsd_info_dentry, FS_MODIFY);
	renew_client_locked(clp);
पूर्ण

अटल काष्ठा nfs4_client *
find_client_in_id_table(काष्ठा list_head *tbl, clientid_t *clid, bool sessions)
अणु
	काष्ठा nfs4_client *clp;
	अचिन्हित पूर्णांक idhashval = clientid_hashval(clid->cl_id);

	list_क्रम_each_entry(clp, &tbl[idhashval], cl_idhash) अणु
		अगर (same_clid(&clp->cl_clientid, clid)) अणु
			अगर ((bool)clp->cl_minorversion != sessions)
				वापस शून्य;
			renew_client_locked(clp);
			वापस clp;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_client *
find_confirmed_client(clientid_t *clid, bool sessions, काष्ठा nfsd_net *nn)
अणु
	काष्ठा list_head *tbl = nn->conf_id_hashtbl;

	lockdep_निश्चित_held(&nn->client_lock);
	वापस find_client_in_id_table(tbl, clid, sessions);
पूर्ण

अटल काष्ठा nfs4_client *
find_unconfirmed_client(clientid_t *clid, bool sessions, काष्ठा nfsd_net *nn)
अणु
	काष्ठा list_head *tbl = nn->unconf_id_hashtbl;

	lockdep_निश्चित_held(&nn->client_lock);
	वापस find_client_in_id_table(tbl, clid, sessions);
पूर्ण

अटल bool clp_used_exchangeid(काष्ठा nfs4_client *clp)
अणु
	वापस clp->cl_exchange_flags != 0;
पूर्ण 

अटल काष्ठा nfs4_client *
find_confirmed_client_by_name(काष्ठा xdr_netobj *name, काष्ठा nfsd_net *nn)
अणु
	lockdep_निश्चित_held(&nn->client_lock);
	वापस find_clp_in_name_tree(name, &nn->conf_name_tree);
पूर्ण

अटल काष्ठा nfs4_client *
find_unconfirmed_client_by_name(काष्ठा xdr_netobj *name, काष्ठा nfsd_net *nn)
अणु
	lockdep_निश्चित_held(&nn->client_lock);
	वापस find_clp_in_name_tree(name, &nn->unconf_name_tree);
पूर्ण

अटल व्योम
gen_callback(काष्ठा nfs4_client *clp, काष्ठा nfsd4_setclientid *se, काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfs4_cb_conn *conn = &clp->cl_cb_conn;
	काष्ठा sockaddr	*sa = svc_addr(rqstp);
	u32 scopeid = rpc_get_scope_id(sa);
	अचिन्हित लघु expected_family;

	/* Currently, we only support tcp and tcp6 क्रम the callback channel */
	अगर (se->se_callback_netid_len == 3 &&
	    !स_भेद(se->se_callback_netid_val, "tcp", 3))
		expected_family = AF_INET;
	अन्यथा अगर (se->se_callback_netid_len == 4 &&
		 !स_भेद(se->se_callback_netid_val, "tcp6", 4))
		expected_family = AF_INET6;
	अन्यथा
		जाओ out_err;

	conn->cb_addrlen = rpc_uaddr2sockaddr(clp->net, se->se_callback_addr_val,
					    se->se_callback_addr_len,
					    (काष्ठा sockaddr *)&conn->cb_addr,
					    माप(conn->cb_addr));

	अगर (!conn->cb_addrlen || conn->cb_addr.ss_family != expected_family)
		जाओ out_err;

	अगर (conn->cb_addr.ss_family == AF_INET6)
		((काष्ठा sockaddr_in6 *)&conn->cb_addr)->sin6_scope_id = scopeid;

	conn->cb_prog = se->se_callback_prog;
	conn->cb_ident = se->se_callback_ident;
	स_नकल(&conn->cb_saddr, &rqstp->rq_daddr, rqstp->rq_daddrlen);
	trace_nfsd_cb_args(clp, conn);
	वापस;
out_err:
	conn->cb_addr.ss_family = AF_UNSPEC;
	conn->cb_addrlen = 0;
	trace_nfsd_cb_nodelegs(clp);
	वापस;
पूर्ण

/*
 * Cache a reply. nfsd4_check_resp_size() has bounded the cache size.
 */
अटल व्योम
nfsd4_store_cache_entry(काष्ठा nfsd4_compoundres *resp)
अणु
	काष्ठा xdr_buf *buf = resp->xdr->buf;
	काष्ठा nfsd4_slot *slot = resp->cstate.slot;
	अचिन्हित पूर्णांक base;

	dprपूर्णांकk("--> %s slot %p\n", __func__, slot);

	slot->sl_flags |= NFSD4_SLOT_INITIALIZED;
	slot->sl_opcnt = resp->opcnt;
	slot->sl_status = resp->cstate.status;
	मुक्त_svc_cred(&slot->sl_cred);
	copy_cred(&slot->sl_cred, &resp->rqstp->rq_cred);

	अगर (!nfsd4_cache_this(resp)) अणु
		slot->sl_flags &= ~NFSD4_SLOT_CACHED;
		वापस;
	पूर्ण
	slot->sl_flags |= NFSD4_SLOT_CACHED;

	base = resp->cstate.data_offset;
	slot->sl_datalen = buf->len - base;
	अगर (पढ़ो_bytes_from_xdr_buf(buf, base, slot->sl_data, slot->sl_datalen))
		WARN(1, "%s: sessions DRC could not cache compound\n",
		     __func__);
	वापस;
पूर्ण

/*
 * Encode the replay sequence operation from the slot values.
 * If cachethis is FALSE encode the uncached rep error on the next
 * operation which sets resp->p and increments resp->opcnt क्रम
 * nfs4svc_encode_compoundres.
 *
 */
अटल __be32
nfsd4_enc_sequence_replay(काष्ठा nfsd4_compoundargs *args,
			  काष्ठा nfsd4_compoundres *resp)
अणु
	काष्ठा nfsd4_op *op;
	काष्ठा nfsd4_slot *slot = resp->cstate.slot;

	/* Encode the replayed sequence operation */
	op = &args->ops[resp->opcnt - 1];
	nfsd4_encode_operation(resp, op);

	अगर (slot->sl_flags & NFSD4_SLOT_CACHED)
		वापस op->status;
	अगर (args->opcnt == 1) अणु
		/*
		 * The original operation wasn't a solo sequence--we
		 * always cache those--so this retry must not match the
		 * original:
		 */
		op->status = nfserr_seq_false_retry;
	पूर्ण अन्यथा अणु
		op = &args->ops[resp->opcnt++];
		op->status = nfserr_retry_uncached_rep;
		nfsd4_encode_operation(resp, op);
	पूर्ण
	वापस op->status;
पूर्ण

/*
 * The sequence operation is not cached because we can use the slot and
 * session values.
 */
अटल __be32
nfsd4_replay_cache_entry(काष्ठा nfsd4_compoundres *resp,
			 काष्ठा nfsd4_sequence *seq)
अणु
	काष्ठा nfsd4_slot *slot = resp->cstate.slot;
	काष्ठा xdr_stream *xdr = resp->xdr;
	__be32 *p;
	__be32 status;

	dprपूर्णांकk("--> %s slot %p\n", __func__, slot);

	status = nfsd4_enc_sequence_replay(resp->rqstp->rq_argp, resp);
	अगर (status)
		वापस status;

	p = xdr_reserve_space(xdr, slot->sl_datalen);
	अगर (!p) अणु
		WARN_ON_ONCE(1);
		वापस nfserr_serverfault;
	पूर्ण
	xdr_encode_opaque_fixed(p, slot->sl_data, slot->sl_datalen);
	xdr_commit_encode(xdr);

	resp->opcnt = slot->sl_opcnt;
	वापस slot->sl_status;
पूर्ण

/*
 * Set the exchange_id flags वापसed by the server.
 */
अटल व्योम
nfsd4_set_ex_flags(काष्ठा nfs4_client *new, काष्ठा nfsd4_exchange_id *clid)
अणु
#अगर_घोषित CONFIG_NFSD_PNFS
	new->cl_exchange_flags |= EXCHGID4_FLAG_USE_PNFS_MDS;
#अन्यथा
	new->cl_exchange_flags |= EXCHGID4_FLAG_USE_NON_PNFS;
#पूर्ण_अगर

	/* Referrals are supported, Migration is not. */
	new->cl_exchange_flags |= EXCHGID4_FLAG_SUPP_MOVED_REFER;

	/* set the wire flags to वापस to client. */
	clid->flags = new->cl_exchange_flags;
पूर्ण

अटल bool client_has_खोलोowners(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_खोलोowner *oo;

	list_क्रम_each_entry(oo, &clp->cl_खोलोowners, oo_perclient) अणु
		अगर (!list_empty(&oo->oo_owner.so_stateids))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool client_has_state(काष्ठा nfs4_client *clp)
अणु
	वापस client_has_खोलोowners(clp)
#अगर_घोषित CONFIG_NFSD_PNFS
		|| !list_empty(&clp->cl_lo_states)
#पूर्ण_अगर
		|| !list_empty(&clp->cl_delegations)
		|| !list_empty(&clp->cl_sessions)
		|| !list_empty(&clp->async_copies);
पूर्ण

अटल __be32 copy_impl_id(काष्ठा nfs4_client *clp,
				काष्ठा nfsd4_exchange_id *exid)
अणु
	अगर (!exid->nii_करोमुख्य.data)
		वापस 0;
	xdr_netobj_dup(&clp->cl_nii_करोमुख्य, &exid->nii_करोमुख्य, GFP_KERNEL);
	अगर (!clp->cl_nii_करोमुख्य.data)
		वापस nfserr_jukebox;
	xdr_netobj_dup(&clp->cl_nii_name, &exid->nii_name, GFP_KERNEL);
	अगर (!clp->cl_nii_name.data)
		वापस nfserr_jukebox;
	clp->cl_nii_समय = exid->nii_समय;
	वापस 0;
पूर्ण

__be32
nfsd4_exchange_id(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_exchange_id *exid = &u->exchange_id;
	काष्ठा nfs4_client *conf, *new;
	काष्ठा nfs4_client *unconf = शून्य;
	__be32 status;
	अक्षर			addr_str[INET6_ADDRSTRLEN];
	nfs4_verअगरier		verf = exid->verअगरier;
	काष्ठा sockaddr		*sa = svc_addr(rqstp);
	bool	update = exid->flags & EXCHGID4_FLAG_UPD_CONFIRMED_REC_A;
	काष्ठा nfsd_net		*nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	rpc_ntop(sa, addr_str, माप(addr_str));
	dprपूर्णांकk("%s rqstp=%p exid=%p clname.len=%u clname.data=%p "
		"ip_addr=%s flags %x, spa_how %u\n",
		__func__, rqstp, exid, exid->clname.len, exid->clname.data,
		addr_str, exid->flags, exid->spa_how);

	अगर (exid->flags & ~EXCHGID4_FLAG_MASK_A)
		वापस nfserr_inval;

	new = create_client(exid->clname, rqstp, &verf);
	अगर (new == शून्य)
		वापस nfserr_jukebox;
	status = copy_impl_id(new, exid);
	अगर (status)
		जाओ out_nolock;

	चयन (exid->spa_how) अणु
	हाल SP4_MACH_CRED:
		exid->spo_must_enक्रमce[0] = 0;
		exid->spo_must_enक्रमce[1] = (
			1 << (OP_BIND_CONN_TO_SESSION - 32) |
			1 << (OP_EXCHANGE_ID - 32) |
			1 << (OP_CREATE_SESSION - 32) |
			1 << (OP_DESTROY_SESSION - 32) |
			1 << (OP_DESTROY_CLIENTID - 32));

		exid->spo_must_allow[0] &= (1 << (OP_CLOSE) |
					1 << (OP_OPEN_DOWNGRADE) |
					1 << (OP_LOCKU) |
					1 << (OP_DELEGRETURN));

		exid->spo_must_allow[1] &= (
					1 << (OP_TEST_STATEID - 32) |
					1 << (OP_FREE_STATEID - 32));
		अगर (!svc_rqst_पूर्णांकegrity_रक्षित(rqstp)) अणु
			status = nfserr_inval;
			जाओ out_nolock;
		पूर्ण
		/*
		 * Someबार userspace करोesn't give us a principal.
		 * Which is a bug, really.  Anyway, we can't enक्रमce
		 * MACH_CRED in that हाल, better to give up now:
		 */
		अगर (!new->cl_cred.cr_principal &&
					!new->cl_cred.cr_raw_principal) अणु
			status = nfserr_serverfault;
			जाओ out_nolock;
		पूर्ण
		new->cl_mach_cred = true;
		अवरोध;
	हाल SP4_NONE:
		अवरोध;
	शेष:				/* checked by xdr code */
		WARN_ON_ONCE(1);
		fallthrough;
	हाल SP4_SSV:
		status = nfserr_encr_alg_unsupp;
		जाओ out_nolock;
	पूर्ण

	/* Cases below refer to rfc 5661 section 18.35.4: */
	spin_lock(&nn->client_lock);
	conf = find_confirmed_client_by_name(&exid->clname, nn);
	अगर (conf) अणु
		bool creds_match = same_creds(&conf->cl_cred, &rqstp->rq_cred);
		bool verfs_match = same_verf(&verf, &conf->cl_verअगरier);

		अगर (update) अणु
			अगर (!clp_used_exchangeid(conf)) अणु /* buggy client */
				status = nfserr_inval;
				जाओ out;
			पूर्ण
			अगर (!nfsd4_mach_creds_match(conf, rqstp)) अणु
				status = nfserr_wrong_cred;
				जाओ out;
			पूर्ण
			अगर (!creds_match) अणु /* हाल 9 */
				status = nfserr_perm;
				जाओ out;
			पूर्ण
			अगर (!verfs_match) अणु /* हाल 8 */
				status = nfserr_not_same;
				जाओ out;
			पूर्ण
			/* हाल 6 */
			exid->flags |= EXCHGID4_FLAG_CONFIRMED_R;
			जाओ out_copy;
		पूर्ण
		अगर (!creds_match) अणु /* हाल 3 */
			अगर (client_has_state(conf)) अणु
				status = nfserr_clid_inuse;
				जाओ out;
			पूर्ण
			जाओ out_new;
		पूर्ण
		अगर (verfs_match) अणु /* हाल 2 */
			conf->cl_exchange_flags |= EXCHGID4_FLAG_CONFIRMED_R;
			जाओ out_copy;
		पूर्ण
		/* हाल 5, client reboot */
		conf = शून्य;
		जाओ out_new;
	पूर्ण

	अगर (update) अणु /* हाल 7 */
		status = nfserr_noent;
		जाओ out;
	पूर्ण

	unconf  = find_unconfirmed_client_by_name(&exid->clname, nn);
	अगर (unconf) /* हाल 4, possible retry or client restart */
		unhash_client_locked(unconf);

	/* हाल 1 (normal हाल) */
out_new:
	अगर (conf) अणु
		status = mark_client_expired_locked(conf);
		अगर (status)
			जाओ out;
	पूर्ण
	new->cl_minorversion = cstate->minorversion;
	new->cl_spo_must_allow.u.words[0] = exid->spo_must_allow[0];
	new->cl_spo_must_allow.u.words[1] = exid->spo_must_allow[1];

	add_to_unconfirmed(new);
	swap(new, conf);
out_copy:
	exid->clientid.cl_boot = conf->cl_clientid.cl_boot;
	exid->clientid.cl_id = conf->cl_clientid.cl_id;

	exid->seqid = conf->cl_cs_slot.sl_seqid + 1;
	nfsd4_set_ex_flags(conf, exid);

	dprपूर्णांकk("nfsd4_exchange_id seqid %d flags %x\n",
		conf->cl_cs_slot.sl_seqid, conf->cl_exchange_flags);
	status = nfs_ok;

out:
	spin_unlock(&nn->client_lock);
out_nolock:
	अगर (new)
		expire_client(new);
	अगर (unconf)
		expire_client(unconf);
	वापस status;
पूर्ण

अटल __be32
check_slot_seqid(u32 seqid, u32 slot_seqid, पूर्णांक slot_inuse)
अणु
	dprपूर्णांकk("%s enter. seqid %d slot_seqid %d\n", __func__, seqid,
		slot_seqid);

	/* The slot is in use, and no response has been sent. */
	अगर (slot_inuse) अणु
		अगर (seqid == slot_seqid)
			वापस nfserr_jukebox;
		अन्यथा
			वापस nfserr_seq_misordered;
	पूर्ण
	/* Note अचिन्हित 32-bit arithmetic handles wraparound: */
	अगर (likely(seqid == slot_seqid + 1))
		वापस nfs_ok;
	अगर (seqid == slot_seqid)
		वापस nfserr_replay_cache;
	वापस nfserr_seq_misordered;
पूर्ण

/*
 * Cache the create session result पूर्णांकo the create session single DRC
 * slot cache by saving the xdr काष्ठाure. sl_seqid has been set.
 * Do this क्रम solo or embedded create session operations.
 */
अटल व्योम
nfsd4_cache_create_session(काष्ठा nfsd4_create_session *cr_ses,
			   काष्ठा nfsd4_clid_slot *slot, __be32 nfserr)
अणु
	slot->sl_status = nfserr;
	स_नकल(&slot->sl_cr_ses, cr_ses, माप(*cr_ses));
पूर्ण

अटल __be32
nfsd4_replay_create_session(काष्ठा nfsd4_create_session *cr_ses,
			    काष्ठा nfsd4_clid_slot *slot)
अणु
	स_नकल(cr_ses, &slot->sl_cr_ses, माप(*cr_ses));
	वापस slot->sl_status;
पूर्ण

#घोषणा NFSD_MIN_REQ_HDR_SEQ_SZ	((\
			2 * 2 + /* credential,verअगरier: AUTH_शून्य, length 0 */ \
			1 +	/* MIN tag is length with zero, only length */ \
			3 +	/* version, opcount, opcode */ \
			XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + \
				/* seqid, slotID, slotID, cache */ \
			4 ) * माप(__be32))

#घोषणा NFSD_MIN_RESP_HDR_SEQ_SZ ((\
			2 +	/* verअगरier: AUTH_शून्य, length 0 */\
			1 +	/* status */ \
			1 +	/* MIN tag is length with zero, only length */ \
			3 +	/* opcount, opcode, opstatus*/ \
			XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + \
				/* seqid, slotID, slotID, slotID, status */ \
			5 ) * माप(__be32))

अटल __be32 check_क्रमechannel_attrs(काष्ठा nfsd4_channel_attrs *ca, काष्ठा nfsd_net *nn)
अणु
	u32 maxrpc = nn->nfsd_serv->sv_max_mesg;

	अगर (ca->maxreq_sz < NFSD_MIN_REQ_HDR_SEQ_SZ)
		वापस nfserr_toosmall;
	अगर (ca->maxresp_sz < NFSD_MIN_RESP_HDR_SEQ_SZ)
		वापस nfserr_toosmall;
	ca->headerpadsz = 0;
	ca->maxreq_sz = min_t(u32, ca->maxreq_sz, maxrpc);
	ca->maxresp_sz = min_t(u32, ca->maxresp_sz, maxrpc);
	ca->maxops = min_t(u32, ca->maxops, NFSD_MAX_OPS_PER_COMPOUND);
	ca->maxresp_cached = min_t(u32, ca->maxresp_cached,
			NFSD_SLOT_CACHE_SIZE + NFSD_MIN_HDR_SEQ_SZ);
	ca->maxreqs = min_t(u32, ca->maxreqs, NFSD_MAX_SLOTS_PER_SESSION);
	/*
	 * Note decreasing slot size below client's request may make it
	 * dअगरficult क्रम client to function correctly, whereas
	 * decreasing the number of slots will (just?) affect
	 * perक्रमmance.  When लघु on memory we thereक्रमe prefer to
	 * decrease number of slots instead of their size.  Clients that
	 * request larger slots than they need will get poor results:
	 * Note that we always allow at least one slot, because our
	 * accounting is soft and provides no guarantees either way.
	 */
	ca->maxreqs = nfsd4_get_drc_mem(ca, nn);

	वापस nfs_ok;
पूर्ण

/*
 * Server's NFSv4.1 backchannel support is AUTH_SYS-only क्रम now.
 * These are based on similar macros in linux/sunrpc/msg_prot.h .
 */
#घोषणा RPC_MAX_HEADER_WITH_AUTH_SYS \
	(RPC_CALLHDRSIZE + 2 * (2 + UNX_CALLSLACK))

#घोषणा RPC_MAX_REPHEADER_WITH_AUTH_SYS \
	(RPC_REPHDRSIZE + (2 + NUL_REPLYSLACK))

#घोषणा NFSD_CB_MAX_REQ_SZ	((NFS4_enc_cb_recall_sz + \
				 RPC_MAX_HEADER_WITH_AUTH_SYS) * माप(__be32))
#घोषणा NFSD_CB_MAX_RESP_SZ	((NFS4_dec_cb_recall_sz + \
				 RPC_MAX_REPHEADER_WITH_AUTH_SYS) * \
				 माप(__be32))

अटल __be32 check_backchannel_attrs(काष्ठा nfsd4_channel_attrs *ca)
अणु
	ca->headerpadsz = 0;

	अगर (ca->maxreq_sz < NFSD_CB_MAX_REQ_SZ)
		वापस nfserr_toosmall;
	अगर (ca->maxresp_sz < NFSD_CB_MAX_RESP_SZ)
		वापस nfserr_toosmall;
	ca->maxresp_cached = 0;
	अगर (ca->maxops < 2)
		वापस nfserr_toosmall;

	वापस nfs_ok;
पूर्ण

अटल __be32 nfsd4_check_cb_sec(काष्ठा nfsd4_cb_sec *cbs)
अणु
	चयन (cbs->flavor) अणु
	हाल RPC_AUTH_शून्य:
	हाल RPC_AUTH_UNIX:
		वापस nfs_ok;
	शेष:
		/*
		 * GSS हाल: the spec करोesn't allow us to वापस this
		 * error.  But it also करोesn't allow us not to support
		 * GSS.
		 * I'd rather this fail hard than वापस some error the
		 * client might think it can alपढ़ोy handle:
		 */
		वापस nfserr_encr_alg_unsupp;
	पूर्ण
पूर्ण

__be32
nfsd4_create_session(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_create_session *cr_ses = &u->create_session;
	काष्ठा sockaddr *sa = svc_addr(rqstp);
	काष्ठा nfs4_client *conf, *unconf;
	काष्ठा nfs4_client *old = शून्य;
	काष्ठा nfsd4_session *new;
	काष्ठा nfsd4_conn *conn;
	काष्ठा nfsd4_clid_slot *cs_slot = शून्य;
	__be32 status = 0;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	अगर (cr_ses->flags & ~SESSION4_FLAG_MASK_A)
		वापस nfserr_inval;
	status = nfsd4_check_cb_sec(&cr_ses->cb_sec);
	अगर (status)
		वापस status;
	status = check_क्रमechannel_attrs(&cr_ses->क्रमe_channel, nn);
	अगर (status)
		वापस status;
	status = check_backchannel_attrs(&cr_ses->back_channel);
	अगर (status)
		जाओ out_release_drc_mem;
	status = nfserr_jukebox;
	new = alloc_session(&cr_ses->क्रमe_channel, &cr_ses->back_channel);
	अगर (!new)
		जाओ out_release_drc_mem;
	conn = alloc_conn_from_crses(rqstp, cr_ses);
	अगर (!conn)
		जाओ out_मुक्त_session;

	spin_lock(&nn->client_lock);
	unconf = find_unconfirmed_client(&cr_ses->clientid, true, nn);
	conf = find_confirmed_client(&cr_ses->clientid, true, nn);
	WARN_ON_ONCE(conf && unconf);

	अगर (conf) अणु
		status = nfserr_wrong_cred;
		अगर (!nfsd4_mach_creds_match(conf, rqstp))
			जाओ out_मुक्त_conn;
		cs_slot = &conf->cl_cs_slot;
		status = check_slot_seqid(cr_ses->seqid, cs_slot->sl_seqid, 0);
		अगर (status) अणु
			अगर (status == nfserr_replay_cache)
				status = nfsd4_replay_create_session(cr_ses, cs_slot);
			जाओ out_मुक्त_conn;
		पूर्ण
	पूर्ण अन्यथा अगर (unconf) अणु
		अगर (!same_creds(&unconf->cl_cred, &rqstp->rq_cred) ||
		    !rpc_cmp_addr(sa, (काष्ठा sockaddr *) &unconf->cl_addr)) अणु
			status = nfserr_clid_inuse;
			जाओ out_मुक्त_conn;
		पूर्ण
		status = nfserr_wrong_cred;
		अगर (!nfsd4_mach_creds_match(unconf, rqstp))
			जाओ out_मुक्त_conn;
		cs_slot = &unconf->cl_cs_slot;
		status = check_slot_seqid(cr_ses->seqid, cs_slot->sl_seqid, 0);
		अगर (status) अणु
			/* an unconfirmed replay वापसs misordered */
			status = nfserr_seq_misordered;
			जाओ out_मुक्त_conn;
		पूर्ण
		old = find_confirmed_client_by_name(&unconf->cl_name, nn);
		अगर (old) अणु
			status = mark_client_expired_locked(old);
			अगर (status) अणु
				old = शून्य;
				जाओ out_मुक्त_conn;
			पूर्ण
		पूर्ण
		move_to_confirmed(unconf);
		conf = unconf;
	पूर्ण अन्यथा अणु
		status = nfserr_stale_clientid;
		जाओ out_मुक्त_conn;
	पूर्ण
	status = nfs_ok;
	/* Persistent sessions are not supported */
	cr_ses->flags &= ~SESSION4_PERSIST;
	/* Upshअगरting from TCP to RDMA is not supported */
	cr_ses->flags &= ~SESSION4_RDMA;

	init_session(rqstp, new, conf, cr_ses);
	nfsd4_get_session_locked(new);

	स_नकल(cr_ses->sessionid.data, new->se_sessionid.data,
	       NFS4_MAX_SESSIONID_LEN);
	cs_slot->sl_seqid++;
	cr_ses->seqid = cs_slot->sl_seqid;

	/* cache solo and embedded create sessions under the client_lock */
	nfsd4_cache_create_session(cr_ses, cs_slot, status);
	spin_unlock(&nn->client_lock);
	/* init connection and backchannel */
	nfsd4_init_conn(rqstp, conn, new);
	nfsd4_put_session(new);
	अगर (old)
		expire_client(old);
	वापस status;
out_मुक्त_conn:
	spin_unlock(&nn->client_lock);
	मुक्त_conn(conn);
	अगर (old)
		expire_client(old);
out_मुक्त_session:
	__मुक्त_session(new);
out_release_drc_mem:
	nfsd4_put_drc_mem(&cr_ses->क्रमe_channel);
	वापस status;
पूर्ण

अटल __be32 nfsd4_map_bcts_dir(u32 *dir)
अणु
	चयन (*dir) अणु
	हाल NFS4_CDFC4_FORE:
	हाल NFS4_CDFC4_BACK:
		वापस nfs_ok;
	हाल NFS4_CDFC4_FORE_OR_BOTH:
	हाल NFS4_CDFC4_BACK_OR_BOTH:
		*dir = NFS4_CDFC4_BOTH;
		वापस nfs_ok;
	पूर्ण
	वापस nfserr_inval;
पूर्ण

__be32 nfsd4_backchannel_ctl(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_backchannel_ctl *bc = &u->backchannel_ctl;
	काष्ठा nfsd4_session *session = cstate->session;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	__be32 status;

	status = nfsd4_check_cb_sec(&bc->bc_cb_sec);
	अगर (status)
		वापस status;
	spin_lock(&nn->client_lock);
	session->se_cb_prog = bc->bc_cb_program;
	session->se_cb_sec = bc->bc_cb_sec;
	spin_unlock(&nn->client_lock);

	nfsd4_probe_callback(session->se_client);

	वापस nfs_ok;
पूर्ण

अटल काष्ठा nfsd4_conn *__nfsd4_find_conn(काष्ठा svc_xprt *xpt, काष्ठा nfsd4_session *s)
अणु
	काष्ठा nfsd4_conn *c;

	list_क्रम_each_entry(c, &s->se_conns, cn_persession) अणु
		अगर (c->cn_xprt == xpt) अणु
			वापस c;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल __be32 nfsd4_match_existing_connection(काष्ठा svc_rqst *rqst,
				काष्ठा nfsd4_session *session, u32 req)
अणु
	काष्ठा nfs4_client *clp = session->se_client;
	काष्ठा svc_xprt *xpt = rqst->rq_xprt;
	काष्ठा nfsd4_conn *c;
	__be32 status;

	/* Following the last paragraph of RFC 5661 Section 18.34.3: */
	spin_lock(&clp->cl_lock);
	c = __nfsd4_find_conn(xpt, session);
	अगर (!c)
		status = nfserr_noent;
	अन्यथा अगर (req == c->cn_flags)
		status = nfs_ok;
	अन्यथा अगर (req == NFS4_CDFC4_FORE_OR_BOTH &&
				c->cn_flags != NFS4_CDFC4_BACK)
		status = nfs_ok;
	अन्यथा अगर (req == NFS4_CDFC4_BACK_OR_BOTH &&
				c->cn_flags != NFS4_CDFC4_FORE)
		status = nfs_ok;
	अन्यथा
		status = nfserr_inval;
	spin_unlock(&clp->cl_lock);
	वापस status;
पूर्ण

__be32 nfsd4_bind_conn_to_session(काष्ठा svc_rqst *rqstp,
		     काष्ठा nfsd4_compound_state *cstate,
		     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_bind_conn_to_session *bcts = &u->bind_conn_to_session;
	__be32 status;
	काष्ठा nfsd4_conn *conn;
	काष्ठा nfsd4_session *session;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (!nfsd4_last_compound_op(rqstp))
		वापस nfserr_not_only_op;
	spin_lock(&nn->client_lock);
	session = find_in_sessionid_hashtbl(&bcts->sessionid, net, &status);
	spin_unlock(&nn->client_lock);
	अगर (!session)
		जाओ out_no_session;
	status = nfserr_wrong_cred;
	अगर (!nfsd4_mach_creds_match(session->se_client, rqstp))
		जाओ out;
	status = nfsd4_match_existing_connection(rqstp, session, bcts->dir);
	अगर (status == nfs_ok || status == nfserr_inval)
		जाओ out;
	status = nfsd4_map_bcts_dir(&bcts->dir);
	अगर (status)
		जाओ out;
	conn = alloc_conn(rqstp, bcts->dir);
	status = nfserr_jukebox;
	अगर (!conn)
		जाओ out;
	nfsd4_init_conn(rqstp, conn, session);
	status = nfs_ok;
out:
	nfsd4_put_session(session);
out_no_session:
	वापस status;
पूर्ण

अटल bool nfsd4_compound_in_session(काष्ठा nfsd4_compound_state *cstate, काष्ठा nfs4_sessionid *sid)
अणु
	अगर (!cstate->session)
		वापस false;
	वापस !स_भेद(sid, &cstate->session->se_sessionid, माप(*sid));
पूर्ण

__be32
nfsd4_destroy_session(काष्ठा svc_rqst *r, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfs4_sessionid *sessionid = &u->destroy_session.sessionid;
	काष्ठा nfsd4_session *ses;
	__be32 status;
	पूर्णांक ref_held_by_me = 0;
	काष्ठा net *net = SVC_NET(r);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	status = nfserr_not_only_op;
	अगर (nfsd4_compound_in_session(cstate, sessionid)) अणु
		अगर (!nfsd4_last_compound_op(r))
			जाओ out;
		ref_held_by_me++;
	पूर्ण
	dump_sessionid(__func__, sessionid);
	spin_lock(&nn->client_lock);
	ses = find_in_sessionid_hashtbl(sessionid, net, &status);
	अगर (!ses)
		जाओ out_client_lock;
	status = nfserr_wrong_cred;
	अगर (!nfsd4_mach_creds_match(ses->se_client, r))
		जाओ out_put_session;
	status = mark_session_dead_locked(ses, 1 + ref_held_by_me);
	अगर (status)
		जाओ out_put_session;
	unhash_session(ses);
	spin_unlock(&nn->client_lock);

	nfsd4_probe_callback_sync(ses->se_client);

	spin_lock(&nn->client_lock);
	status = nfs_ok;
out_put_session:
	nfsd4_put_session_locked(ses);
out_client_lock:
	spin_unlock(&nn->client_lock);
out:
	वापस status;
पूर्ण

अटल __be32 nfsd4_sequence_check_conn(काष्ठा nfsd4_conn *new, काष्ठा nfsd4_session *ses)
अणु
	काष्ठा nfs4_client *clp = ses->se_client;
	काष्ठा nfsd4_conn *c;
	__be32 status = nfs_ok;
	पूर्णांक ret;

	spin_lock(&clp->cl_lock);
	c = __nfsd4_find_conn(new->cn_xprt, ses);
	अगर (c)
		जाओ out_मुक्त;
	status = nfserr_conn_not_bound_to_session;
	अगर (clp->cl_mach_cred)
		जाओ out_मुक्त;
	__nfsd4_hash_conn(new, ses);
	spin_unlock(&clp->cl_lock);
	ret = nfsd4_रेजिस्टर_conn(new);
	अगर (ret)
		/* oops; xprt is alपढ़ोy करोwn: */
		nfsd4_conn_lost(&new->cn_xpt_user);
	वापस nfs_ok;
out_मुक्त:
	spin_unlock(&clp->cl_lock);
	मुक्त_conn(new);
	वापस status;
पूर्ण

अटल bool nfsd4_session_too_many_ops(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_session *session)
अणु
	काष्ठा nfsd4_compoundargs *args = rqstp->rq_argp;

	वापस args->opcnt > session->se_fchannel.maxops;
पूर्ण

अटल bool nfsd4_request_too_big(काष्ठा svc_rqst *rqstp,
				  काष्ठा nfsd4_session *session)
अणु
	काष्ठा xdr_buf *xb = &rqstp->rq_arg;

	वापस xb->len > session->se_fchannel.maxreq_sz;
पूर्ण

अटल bool replay_matches_cache(काष्ठा svc_rqst *rqstp,
		 काष्ठा nfsd4_sequence *seq, काष्ठा nfsd4_slot *slot)
अणु
	काष्ठा nfsd4_compoundargs *argp = rqstp->rq_argp;

	अगर ((bool)(slot->sl_flags & NFSD4_SLOT_CACHETHIS) !=
	    (bool)seq->cachethis)
		वापस false;
	/*
	 * If there's an error then the reply can have fewer ops than
	 * the call.
	 */
	अगर (slot->sl_opcnt < argp->opcnt && !slot->sl_status)
		वापस false;
	/*
	 * But अगर we cached a reply with *more* ops than the call you're
	 * sending us now, then this new call is clearly not really a
	 * replay of the old one:
	 */
	अगर (slot->sl_opcnt > argp->opcnt)
		वापस false;
	/* This is the only check explicitly called by spec: */
	अगर (!same_creds(&rqstp->rq_cred, &slot->sl_cred))
		वापस false;
	/*
	 * There may be more comparisons we could actually करो, but the
	 * spec करोesn't require us to catch every हाल where the calls
	 * करोn't match (that would require caching the call as well as
	 * the reply), so we करोn't bother.
	 */
	वापस true;
पूर्ण

__be32
nfsd4_sequence(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_sequence *seq = &u->sequence;
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	काष्ठा xdr_stream *xdr = resp->xdr;
	काष्ठा nfsd4_session *session;
	काष्ठा nfs4_client *clp;
	काष्ठा nfsd4_slot *slot;
	काष्ठा nfsd4_conn *conn;
	__be32 status;
	पूर्णांक buflen;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (resp->opcnt != 1)
		वापस nfserr_sequence_pos;

	/*
	 * Will be either used or मुक्तd by nfsd4_sequence_check_conn
	 * below.
	 */
	conn = alloc_conn(rqstp, NFS4_CDFC4_FORE);
	अगर (!conn)
		वापस nfserr_jukebox;

	spin_lock(&nn->client_lock);
	session = find_in_sessionid_hashtbl(&seq->sessionid, net, &status);
	अगर (!session)
		जाओ out_no_session;
	clp = session->se_client;

	status = nfserr_too_many_ops;
	अगर (nfsd4_session_too_many_ops(rqstp, session))
		जाओ out_put_session;

	status = nfserr_req_too_big;
	अगर (nfsd4_request_too_big(rqstp, session))
		जाओ out_put_session;

	status = nfserr_badslot;
	अगर (seq->slotid >= session->se_fchannel.maxreqs)
		जाओ out_put_session;

	slot = session->se_slots[seq->slotid];
	dprपूर्णांकk("%s: slotid %d\n", __func__, seq->slotid);

	/* We करो not negotiate the number of slots yet, so set the
	 * maxslots to the session maxreqs which is used to encode
	 * sr_highest_slotid and the sr_target_slot id to maxslots */
	seq->maxslots = session->se_fchannel.maxreqs;

	status = check_slot_seqid(seq->seqid, slot->sl_seqid,
					slot->sl_flags & NFSD4_SLOT_INUSE);
	अगर (status == nfserr_replay_cache) अणु
		status = nfserr_seq_misordered;
		अगर (!(slot->sl_flags & NFSD4_SLOT_INITIALIZED))
			जाओ out_put_session;
		status = nfserr_seq_false_retry;
		अगर (!replay_matches_cache(rqstp, seq, slot))
			जाओ out_put_session;
		cstate->slot = slot;
		cstate->session = session;
		cstate->clp = clp;
		/* Return the cached reply status and set cstate->status
		 * क्रम nfsd4_proc_compound processing */
		status = nfsd4_replay_cache_entry(resp, seq);
		cstate->status = nfserr_replay_cache;
		जाओ out;
	पूर्ण
	अगर (status)
		जाओ out_put_session;

	status = nfsd4_sequence_check_conn(conn, session);
	conn = शून्य;
	अगर (status)
		जाओ out_put_session;

	buflen = (seq->cachethis) ?
			session->se_fchannel.maxresp_cached :
			session->se_fchannel.maxresp_sz;
	status = (seq->cachethis) ? nfserr_rep_too_big_to_cache :
				    nfserr_rep_too_big;
	अगर (xdr_restrict_buflen(xdr, buflen - rqstp->rq_auth_slack))
		जाओ out_put_session;
	svc_reserve(rqstp, buflen);

	status = nfs_ok;
	/* Success! bump slot seqid */
	slot->sl_seqid = seq->seqid;
	slot->sl_flags |= NFSD4_SLOT_INUSE;
	अगर (seq->cachethis)
		slot->sl_flags |= NFSD4_SLOT_CACHETHIS;
	अन्यथा
		slot->sl_flags &= ~NFSD4_SLOT_CACHETHIS;

	cstate->slot = slot;
	cstate->session = session;
	cstate->clp = clp;

out:
	चयन (clp->cl_cb_state) अणु
	हाल NFSD4_CB_DOWN:
		seq->status_flags = SEQ4_STATUS_CB_PATH_DOWN;
		अवरोध;
	हाल NFSD4_CB_FAULT:
		seq->status_flags = SEQ4_STATUS_BACKCHANNEL_FAULT;
		अवरोध;
	शेष:
		seq->status_flags = 0;
	पूर्ण
	अगर (!list_empty(&clp->cl_revoked))
		seq->status_flags |= SEQ4_STATUS_RECALLABLE_STATE_REVOKED;
out_no_session:
	अगर (conn)
		मुक्त_conn(conn);
	spin_unlock(&nn->client_lock);
	वापस status;
out_put_session:
	nfsd4_put_session_locked(session);
	जाओ out_no_session;
पूर्ण

व्योम
nfsd4_sequence_करोne(काष्ठा nfsd4_compoundres *resp)
अणु
	काष्ठा nfsd4_compound_state *cs = &resp->cstate;

	अगर (nfsd4_has_session(cs)) अणु
		अगर (cs->status != nfserr_replay_cache) अणु
			nfsd4_store_cache_entry(resp);
			cs->slot->sl_flags &= ~NFSD4_SLOT_INUSE;
		पूर्ण
		/* Drop session reference that was taken in nfsd4_sequence() */
		nfsd4_put_session(cs->session);
	पूर्ण अन्यथा अगर (cs->clp)
		put_client_renew(cs->clp);
पूर्ण

__be32
nfsd4_destroy_clientid(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_destroy_clientid *dc = &u->destroy_clientid;
	काष्ठा nfs4_client *conf, *unconf;
	काष्ठा nfs4_client *clp = शून्य;
	__be32 status = 0;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	spin_lock(&nn->client_lock);
	unconf = find_unconfirmed_client(&dc->clientid, true, nn);
	conf = find_confirmed_client(&dc->clientid, true, nn);
	WARN_ON_ONCE(conf && unconf);

	अगर (conf) अणु
		अगर (client_has_state(conf)) अणु
			status = nfserr_clientid_busy;
			जाओ out;
		पूर्ण
		status = mark_client_expired_locked(conf);
		अगर (status)
			जाओ out;
		clp = conf;
	पूर्ण अन्यथा अगर (unconf)
		clp = unconf;
	अन्यथा अणु
		status = nfserr_stale_clientid;
		जाओ out;
	पूर्ण
	अगर (!nfsd4_mach_creds_match(clp, rqstp)) अणु
		clp = शून्य;
		status = nfserr_wrong_cred;
		जाओ out;
	पूर्ण
	unhash_client_locked(clp);
out:
	spin_unlock(&nn->client_lock);
	अगर (clp)
		expire_client(clp);
	वापस status;
पूर्ण

__be32
nfsd4_reclaim_complete(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_reclaim_complete *rc = &u->reclaim_complete;
	काष्ठा nfs4_client *clp = cstate->clp;
	__be32 status = 0;

	अगर (rc->rca_one_fs) अणु
		अगर (!cstate->current_fh.fh_dentry)
			वापस nfserr_nofilehandle;
		/*
		 * We करोn't take advantage of the rca_one_fs हाल.
		 * That's OK, it's optional, we can safely ignore it.
		 */
		वापस nfs_ok;
	पूर्ण

	status = nfserr_complete_alपढ़ोy;
	अगर (test_and_set_bit(NFSD4_CLIENT_RECLAIM_COMPLETE, &clp->cl_flags))
		जाओ out;

	status = nfserr_stale_clientid;
	अगर (is_client_expired(clp))
		/*
		 * The following error isn't really legal.
		 * But we only get here अगर the client just explicitly
		 * destroyed the client.  Surely it no दीर्घer cares what
		 * error it माला_लो back on an operation क्रम the dead
		 * client.
		 */
		जाओ out;

	status = nfs_ok;
	nfsd4_client_record_create(clp);
	inc_reclaim_complete(clp);
out:
	वापस status;
पूर्ण

__be32
nfsd4_setclientid(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		  जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_setclientid *setclid = &u->setclientid;
	काष्ठा xdr_netobj 	clname = setclid->se_name;
	nfs4_verअगरier		clverअगरier = setclid->se_verf;
	काष्ठा nfs4_client	*conf, *new;
	काष्ठा nfs4_client	*unconf = शून्य;
	__be32 			status;
	काष्ठा nfsd_net		*nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	new = create_client(clname, rqstp, &clverअगरier);
	अगर (new == शून्य)
		वापस nfserr_jukebox;
	/* Cases below refer to rfc 3530 section 14.2.33: */
	spin_lock(&nn->client_lock);
	conf = find_confirmed_client_by_name(&clname, nn);
	अगर (conf && client_has_state(conf)) अणु
		/* हाल 0: */
		status = nfserr_clid_inuse;
		अगर (clp_used_exchangeid(conf))
			जाओ out;
		अगर (!same_creds(&conf->cl_cred, &rqstp->rq_cred)) अणु
			trace_nfsd_clid_inuse_err(conf);
			जाओ out;
		पूर्ण
	पूर्ण
	unconf = find_unconfirmed_client_by_name(&clname, nn);
	अगर (unconf)
		unhash_client_locked(unconf);
	/* We need to handle only हाल 1: probable callback update */
	अगर (conf && same_verf(&conf->cl_verअगरier, &clverअगरier)) अणु
		copy_clid(new, conf);
		gen_confirm(new, nn);
	पूर्ण
	new->cl_minorversion = 0;
	gen_callback(new, setclid, rqstp);
	add_to_unconfirmed(new);
	setclid->se_clientid.cl_boot = new->cl_clientid.cl_boot;
	setclid->se_clientid.cl_id = new->cl_clientid.cl_id;
	स_नकल(setclid->se_confirm.data, new->cl_confirm.data, माप(setclid->se_confirm.data));
	new = शून्य;
	status = nfs_ok;
out:
	spin_unlock(&nn->client_lock);
	अगर (new)
		मुक्त_client(new);
	अगर (unconf)
		expire_client(unconf);
	वापस status;
पूर्ण


__be32
nfsd4_setclientid_confirm(काष्ठा svc_rqst *rqstp,
			काष्ठा nfsd4_compound_state *cstate,
			जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_setclientid_confirm *setclientid_confirm =
			&u->setclientid_confirm;
	काष्ठा nfs4_client *conf, *unconf;
	काष्ठा nfs4_client *old = शून्य;
	nfs4_verअगरier confirm = setclientid_confirm->sc_confirm; 
	clientid_t * clid = &setclientid_confirm->sc_clientid;
	__be32 status;
	काष्ठा nfsd_net	*nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	अगर (STALE_CLIENTID(clid, nn))
		वापस nfserr_stale_clientid;

	spin_lock(&nn->client_lock);
	conf = find_confirmed_client(clid, false, nn);
	unconf = find_unconfirmed_client(clid, false, nn);
	/*
	 * We try hard to give out unique clientid's, so अगर we get an
	 * attempt to confirm the same clientid with a dअगरferent cred,
	 * the client may be buggy; this should never happen.
	 *
	 * Nevertheless, RFC 7530 recommends INUSE क्रम this हाल:
	 */
	status = nfserr_clid_inuse;
	अगर (unconf && !same_creds(&unconf->cl_cred, &rqstp->rq_cred))
		जाओ out;
	अगर (conf && !same_creds(&conf->cl_cred, &rqstp->rq_cred))
		जाओ out;
	/* हालs below refer to rfc 3530 section 14.2.34: */
	अगर (!unconf || !same_verf(&confirm, &unconf->cl_confirm)) अणु
		अगर (conf && same_verf(&confirm, &conf->cl_confirm)) अणु
			/* हाल 2: probable retransmit */
			status = nfs_ok;
		पूर्ण अन्यथा /* हाल 4: client hasn't noticed we rebooted yet? */
			status = nfserr_stale_clientid;
		जाओ out;
	पूर्ण
	status = nfs_ok;
	अगर (conf) अणु /* हाल 1: callback update */
		old = unconf;
		unhash_client_locked(old);
		nfsd4_change_callback(conf, &unconf->cl_cb_conn);
	पूर्ण अन्यथा अणु /* हाल 3: normal हाल; new or rebooted client */
		old = find_confirmed_client_by_name(&unconf->cl_name, nn);
		अगर (old) अणु
			status = nfserr_clid_inuse;
			अगर (client_has_state(old)
					&& !same_creds(&unconf->cl_cred,
							&old->cl_cred))
				जाओ out;
			status = mark_client_expired_locked(old);
			अगर (status) अणु
				old = शून्य;
				जाओ out;
			पूर्ण
		पूर्ण
		move_to_confirmed(unconf);
		conf = unconf;
	पूर्ण
	get_client_locked(conf);
	spin_unlock(&nn->client_lock);
	nfsd4_probe_callback(conf);
	spin_lock(&nn->client_lock);
	put_client_renew_locked(conf);
out:
	spin_unlock(&nn->client_lock);
	अगर (old)
		expire_client(old);
	वापस status;
पूर्ण

अटल काष्ठा nfs4_file *nfsd4_alloc_file(व्योम)
अणु
	वापस kmem_cache_alloc(file_slab, GFP_KERNEL);
पूर्ण

/* OPEN Share state helper functions */
अटल व्योम nfsd4_init_file(काष्ठा svc_fh *fh, अचिन्हित पूर्णांक hashval,
				काष्ठा nfs4_file *fp)
अणु
	lockdep_निश्चित_held(&state_lock);

	refcount_set(&fp->fi_ref, 1);
	spin_lock_init(&fp->fi_lock);
	INIT_LIST_HEAD(&fp->fi_stateids);
	INIT_LIST_HEAD(&fp->fi_delegations);
	INIT_LIST_HEAD(&fp->fi_clnt_odstate);
	fh_copy_shallow(&fp->fi_fhandle, &fh->fh_handle);
	fp->fi_deleg_file = शून्य;
	fp->fi_had_conflict = false;
	fp->fi_share_deny = 0;
	स_रखो(fp->fi_fds, 0, माप(fp->fi_fds));
	स_रखो(fp->fi_access, 0, माप(fp->fi_access));
	fp->fi_aliased = false;
	fp->fi_inode = d_inode(fh->fh_dentry);
#अगर_घोषित CONFIG_NFSD_PNFS
	INIT_LIST_HEAD(&fp->fi_lo_states);
	atomic_set(&fp->fi_lo_recalls, 0);
#पूर्ण_अगर
	hlist_add_head_rcu(&fp->fi_hash, &file_hashtbl[hashval]);
पूर्ण

व्योम
nfsd4_मुक्त_sद_असल(व्योम)
अणु
	kmem_cache_destroy(client_slab);
	kmem_cache_destroy(खोलोowner_slab);
	kmem_cache_destroy(lockowner_slab);
	kmem_cache_destroy(file_slab);
	kmem_cache_destroy(stateid_slab);
	kmem_cache_destroy(deleg_slab);
	kmem_cache_destroy(odstate_slab);
पूर्ण

पूर्णांक
nfsd4_init_sद_असल(व्योम)
अणु
	client_slab = kmem_cache_create("nfsd4_clients",
			माप(काष्ठा nfs4_client), 0, 0, शून्य);
	अगर (client_slab == शून्य)
		जाओ out;
	खोलोowner_slab = kmem_cache_create("nfsd4_openowners",
			माप(काष्ठा nfs4_खोलोowner), 0, 0, शून्य);
	अगर (खोलोowner_slab == शून्य)
		जाओ out_मुक्त_client_slab;
	lockowner_slab = kmem_cache_create("nfsd4_lockowners",
			माप(काष्ठा nfs4_lockowner), 0, 0, शून्य);
	अगर (lockowner_slab == शून्य)
		जाओ out_मुक्त_खोलोowner_slab;
	file_slab = kmem_cache_create("nfsd4_files",
			माप(काष्ठा nfs4_file), 0, 0, शून्य);
	अगर (file_slab == शून्य)
		जाओ out_मुक्त_lockowner_slab;
	stateid_slab = kmem_cache_create("nfsd4_stateids",
			माप(काष्ठा nfs4_ol_stateid), 0, 0, शून्य);
	अगर (stateid_slab == शून्य)
		जाओ out_मुक्त_file_slab;
	deleg_slab = kmem_cache_create("nfsd4_delegations",
			माप(काष्ठा nfs4_delegation), 0, 0, शून्य);
	अगर (deleg_slab == शून्य)
		जाओ out_मुक्त_stateid_slab;
	odstate_slab = kmem_cache_create("nfsd4_odstate",
			माप(काष्ठा nfs4_clnt_odstate), 0, 0, शून्य);
	अगर (odstate_slab == शून्य)
		जाओ out_मुक्त_deleg_slab;
	वापस 0;

out_मुक्त_deleg_slab:
	kmem_cache_destroy(deleg_slab);
out_मुक्त_stateid_slab:
	kmem_cache_destroy(stateid_slab);
out_मुक्त_file_slab:
	kmem_cache_destroy(file_slab);
out_मुक्त_lockowner_slab:
	kmem_cache_destroy(lockowner_slab);
out_मुक्त_खोलोowner_slab:
	kmem_cache_destroy(खोलोowner_slab);
out_मुक्त_client_slab:
	kmem_cache_destroy(client_slab);
out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम init_nfs4_replay(काष्ठा nfs4_replay *rp)
अणु
	rp->rp_status = nfserr_serverfault;
	rp->rp_buflen = 0;
	rp->rp_buf = rp->rp_ibuf;
	mutex_init(&rp->rp_mutex);
पूर्ण

अटल व्योम nfsd4_cstate_assign_replay(काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfs4_stateowner *so)
अणु
	अगर (!nfsd4_has_session(cstate)) अणु
		mutex_lock(&so->so_replay.rp_mutex);
		cstate->replay_owner = nfs4_get_stateowner(so);
	पूर्ण
पूर्ण

व्योम nfsd4_cstate_clear_replay(काष्ठा nfsd4_compound_state *cstate)
अणु
	काष्ठा nfs4_stateowner *so = cstate->replay_owner;

	अगर (so != शून्य) अणु
		cstate->replay_owner = शून्य;
		mutex_unlock(&so->so_replay.rp_mutex);
		nfs4_put_stateowner(so);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *alloc_stateowner(काष्ठा kmem_cache *slab, काष्ठा xdr_netobj *owner, काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfs4_stateowner *sop;

	sop = kmem_cache_alloc(slab, GFP_KERNEL);
	अगर (!sop)
		वापस शून्य;

	xdr_netobj_dup(&sop->so_owner, owner, GFP_KERNEL);
	अगर (!sop->so_owner.data) अणु
		kmem_cache_मुक्त(slab, sop);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&sop->so_stateids);
	sop->so_client = clp;
	init_nfs4_replay(&sop->so_replay);
	atomic_set(&sop->so_count, 1);
	वापस sop;
पूर्ण

अटल व्योम hash_खोलोowner(काष्ठा nfs4_खोलोowner *oo, काष्ठा nfs4_client *clp, अचिन्हित पूर्णांक strhashval)
अणु
	lockdep_निश्चित_held(&clp->cl_lock);

	list_add(&oo->oo_owner.so_strhash,
		 &clp->cl_ownerstr_hashtbl[strhashval]);
	list_add(&oo->oo_perclient, &clp->cl_खोलोowners);
पूर्ण

अटल व्योम nfs4_unhash_खोलोowner(काष्ठा nfs4_stateowner *so)
अणु
	unhash_खोलोowner_locked(खोलोowner(so));
पूर्ण

अटल व्योम nfs4_मुक्त_खोलोowner(काष्ठा nfs4_stateowner *so)
अणु
	काष्ठा nfs4_खोलोowner *oo = खोलोowner(so);

	kmem_cache_मुक्त(खोलोowner_slab, oo);
पूर्ण

अटल स्थिर काष्ठा nfs4_stateowner_operations खोलोowner_ops = अणु
	.so_unhash =	nfs4_unhash_खोलोowner,
	.so_मुक्त =	nfs4_मुक्त_खोलोowner,
पूर्ण;

अटल काष्ठा nfs4_ol_stateid *
nfsd4_find_existing_खोलो(काष्ठा nfs4_file *fp, काष्ठा nfsd4_खोलो *खोलो)
अणु
	काष्ठा nfs4_ol_stateid *local, *ret = शून्य;
	काष्ठा nfs4_खोलोowner *oo = खोलो->op_खोलोowner;

	lockdep_निश्चित_held(&fp->fi_lock);

	list_क्रम_each_entry(local, &fp->fi_stateids, st_perfile) अणु
		/* ignore lock owners */
		अगर (local->st_stateowner->so_is_खोलो_owner == 0)
			जारी;
		अगर (local->st_stateowner != &oo->oo_owner)
			जारी;
		अगर (local->st_stid.sc_type == NFS4_OPEN_STID) अणु
			ret = local;
			refcount_inc(&ret->st_stid.sc_count);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल __be32
nfsd4_verअगरy_खोलो_stid(काष्ठा nfs4_stid *s)
अणु
	__be32 ret = nfs_ok;

	चयन (s->sc_type) अणु
	शेष:
		अवरोध;
	हाल 0:
	हाल NFS4_CLOSED_STID:
	हाल NFS4_CLOSED_DELEG_STID:
		ret = nfserr_bad_stateid;
		अवरोध;
	हाल NFS4_REVOKED_DELEG_STID:
		ret = nfserr_deleg_revoked;
	पूर्ण
	वापस ret;
पूर्ण

/* Lock the stateid st_mutex, and deal with races with CLOSE */
अटल __be32
nfsd4_lock_ol_stateid(काष्ठा nfs4_ol_stateid *stp)
अणु
	__be32 ret;

	mutex_lock_nested(&stp->st_mutex, LOCK_STATEID_MUTEX);
	ret = nfsd4_verअगरy_खोलो_stid(&stp->st_stid);
	अगर (ret != nfs_ok)
		mutex_unlock(&stp->st_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा nfs4_ol_stateid *
nfsd4_find_and_lock_existing_खोलो(काष्ठा nfs4_file *fp, काष्ठा nfsd4_खोलो *खोलो)
अणु
	काष्ठा nfs4_ol_stateid *stp;
	क्रम (;;) अणु
		spin_lock(&fp->fi_lock);
		stp = nfsd4_find_existing_खोलो(fp, खोलो);
		spin_unlock(&fp->fi_lock);
		अगर (!stp || nfsd4_lock_ol_stateid(stp) == nfs_ok)
			अवरोध;
		nfs4_put_stid(&stp->st_stid);
	पूर्ण
	वापस stp;
पूर्ण

अटल काष्ठा nfs4_खोलोowner *
alloc_init_खोलो_stateowner(अचिन्हित पूर्णांक strhashval, काष्ठा nfsd4_खोलो *खोलो,
			   काष्ठा nfsd4_compound_state *cstate)
अणु
	काष्ठा nfs4_client *clp = cstate->clp;
	काष्ठा nfs4_खोलोowner *oo, *ret;

	oo = alloc_stateowner(खोलोowner_slab, &खोलो->op_owner, clp);
	अगर (!oo)
		वापस शून्य;
	oo->oo_owner.so_ops = &खोलोowner_ops;
	oo->oo_owner.so_is_खोलो_owner = 1;
	oo->oo_owner.so_seqid = खोलो->op_seqid;
	oo->oo_flags = 0;
	अगर (nfsd4_has_session(cstate))
		oo->oo_flags |= NFS4_OO_CONFIRMED;
	oo->oo_समय = 0;
	oo->oo_last_बंदd_stid = शून्य;
	INIT_LIST_HEAD(&oo->oo_बंद_lru);
	spin_lock(&clp->cl_lock);
	ret = find_खोलोstateowner_str_locked(strhashval, खोलो, clp);
	अगर (ret == शून्य) अणु
		hash_खोलोowner(oo, clp, strhashval);
		ret = oo;
	पूर्ण अन्यथा
		nfs4_मुक्त_stateowner(&oo->oo_owner);

	spin_unlock(&clp->cl_lock);
	वापस ret;
पूर्ण

अटल काष्ठा nfs4_ol_stateid *
init_खोलो_stateid(काष्ठा nfs4_file *fp, काष्ठा nfsd4_खोलो *खोलो)
अणु

	काष्ठा nfs4_खोलोowner *oo = खोलो->op_खोलोowner;
	काष्ठा nfs4_ol_stateid *retstp = शून्य;
	काष्ठा nfs4_ol_stateid *stp;

	stp = खोलो->op_stp;
	/* We are moving these outside of the spinlocks to aव्योम the warnings */
	mutex_init(&stp->st_mutex);
	mutex_lock_nested(&stp->st_mutex, OPEN_STATEID_MUTEX);

retry:
	spin_lock(&oo->oo_owner.so_client->cl_lock);
	spin_lock(&fp->fi_lock);

	retstp = nfsd4_find_existing_खोलो(fp, खोलो);
	अगर (retstp)
		जाओ out_unlock;

	खोलो->op_stp = शून्य;
	refcount_inc(&stp->st_stid.sc_count);
	stp->st_stid.sc_type = NFS4_OPEN_STID;
	INIT_LIST_HEAD(&stp->st_locks);
	stp->st_stateowner = nfs4_get_stateowner(&oo->oo_owner);
	get_nfs4_file(fp);
	stp->st_stid.sc_file = fp;
	stp->st_access_bmap = 0;
	stp->st_deny_bmap = 0;
	stp->st_खोलोstp = शून्य;
	list_add(&stp->st_perstateowner, &oo->oo_owner.so_stateids);
	list_add(&stp->st_perfile, &fp->fi_stateids);

out_unlock:
	spin_unlock(&fp->fi_lock);
	spin_unlock(&oo->oo_owner.so_client->cl_lock);
	अगर (retstp) अणु
		/* Handle races with CLOSE */
		अगर (nfsd4_lock_ol_stateid(retstp) != nfs_ok) अणु
			nfs4_put_stid(&retstp->st_stid);
			जाओ retry;
		पूर्ण
		/* To keep mutex tracking happy */
		mutex_unlock(&stp->st_mutex);
		stp = retstp;
	पूर्ण
	वापस stp;
पूर्ण

/*
 * In the 4.0 हाल we need to keep the owners around a little जबतक to handle
 * CLOSE replay. We still करो need to release any file access that is held by
 * them beक्रमe वापसing however.
 */
अटल व्योम
move_to_बंद_lru(काष्ठा nfs4_ol_stateid *s, काष्ठा net *net)
अणु
	काष्ठा nfs4_ol_stateid *last;
	काष्ठा nfs4_खोलोowner *oo = खोलोowner(s->st_stateowner);
	काष्ठा nfsd_net *nn = net_generic(s->st_stid.sc_client->net,
						nfsd_net_id);

	dprपूर्णांकk("NFSD: move_to_close_lru nfs4_openowner %p\n", oo);

	/*
	 * We know that we hold one reference via nfsd4_बंद, and another
	 * "persistent" reference क्रम the client. If the refcount is higher
	 * than 2, then there are still calls in progress that are using this
	 * stateid. We can't put the sc_file reference until they are finished.
	 * Wait क्रम the refcount to drop to 2. Since it has been unhashed,
	 * there should be no danger of the refcount going back up again at
	 * this poपूर्णांक.
	 */
	रुको_event(बंद_wq, refcount_पढ़ो(&s->st_stid.sc_count) == 2);

	release_all_access(s);
	अगर (s->st_stid.sc_file) अणु
		put_nfs4_file(s->st_stid.sc_file);
		s->st_stid.sc_file = शून्य;
	पूर्ण

	spin_lock(&nn->client_lock);
	last = oo->oo_last_बंदd_stid;
	oo->oo_last_बंदd_stid = s;
	list_move_tail(&oo->oo_बंद_lru, &nn->बंद_lru);
	oo->oo_समय = kसमय_get_bootसमय_seconds();
	spin_unlock(&nn->client_lock);
	अगर (last)
		nfs4_put_stid(&last->st_stid);
पूर्ण

/* search file_hashtbl[] क्रम file */
अटल काष्ठा nfs4_file *
find_file_locked(काष्ठा svc_fh *fh, अचिन्हित पूर्णांक hashval)
अणु
	काष्ठा nfs4_file *fp;

	hlist_क्रम_each_entry_rcu(fp, &file_hashtbl[hashval], fi_hash,
				lockdep_is_held(&state_lock)) अणु
		अगर (fh_match(&fp->fi_fhandle, &fh->fh_handle)) अणु
			अगर (refcount_inc_not_zero(&fp->fi_ref))
				वापस fp;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_file *insert_file(काष्ठा nfs4_file *new, काष्ठा svc_fh *fh,
				     अचिन्हित पूर्णांक hashval)
अणु
	काष्ठा nfs4_file *fp;
	काष्ठा nfs4_file *ret = शून्य;
	bool alias_found = false;

	spin_lock(&state_lock);
	hlist_क्रम_each_entry_rcu(fp, &file_hashtbl[hashval], fi_hash,
				 lockdep_is_held(&state_lock)) अणु
		अगर (fh_match(&fp->fi_fhandle, &fh->fh_handle)) अणु
			अगर (refcount_inc_not_zero(&fp->fi_ref))
				ret = fp;
		पूर्ण अन्यथा अगर (d_inode(fh->fh_dentry) == fp->fi_inode)
			fp->fi_aliased = alias_found = true;
	पूर्ण
	अगर (likely(ret == शून्य)) अणु
		nfsd4_init_file(fh, hashval, new);
		new->fi_aliased = alias_found;
		ret = new;
	पूर्ण
	spin_unlock(&state_lock);
	वापस ret;
पूर्ण

अटल काष्ठा nfs4_file * find_file(काष्ठा svc_fh *fh)
अणु
	काष्ठा nfs4_file *fp;
	अचिन्हित पूर्णांक hashval = file_hashval(fh);

	rcu_पढ़ो_lock();
	fp = find_file_locked(fh, hashval);
	rcu_पढ़ो_unlock();
	वापस fp;
पूर्ण

अटल काष्ठा nfs4_file *
find_or_add_file(काष्ठा nfs4_file *new, काष्ठा svc_fh *fh)
अणु
	काष्ठा nfs4_file *fp;
	अचिन्हित पूर्णांक hashval = file_hashval(fh);

	rcu_पढ़ो_lock();
	fp = find_file_locked(fh, hashval);
	rcu_पढ़ो_unlock();
	अगर (fp)
		वापस fp;

	वापस insert_file(new, fh, hashval);
पूर्ण

/*
 * Called to check deny when READ with all zero stateid or
 * WRITE with all zero or all one stateid
 */
अटल __be32
nfs4_share_conflict(काष्ठा svc_fh *current_fh, अचिन्हित पूर्णांक deny_type)
अणु
	काष्ठा nfs4_file *fp;
	__be32 ret = nfs_ok;

	fp = find_file(current_fh);
	अगर (!fp)
		वापस ret;
	/* Check क्रम conflicting share reservations */
	spin_lock(&fp->fi_lock);
	अगर (fp->fi_share_deny & deny_type)
		ret = nfserr_locked;
	spin_unlock(&fp->fi_lock);
	put_nfs4_file(fp);
	वापस ret;
पूर्ण

अटल व्योम nfsd4_cb_recall_prepare(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_delegation *dp = cb_to_delegation(cb);
	काष्ठा nfsd_net *nn = net_generic(dp->dl_stid.sc_client->net,
					  nfsd_net_id);

	block_delegations(&dp->dl_stid.sc_file->fi_fhandle);

	/*
	 * We can't करो this in nfsd_अवरोध_deleg_cb because it is
	 * alपढ़ोy holding inode->i_lock.
	 *
	 * If the dl_समय != 0, then we know that it has alपढ़ोy been
	 * queued क्रम a lease अवरोध. Don't queue it again.
	 */
	spin_lock(&state_lock);
	अगर (dp->dl_समय == 0) अणु
		dp->dl_समय = kसमय_get_bootसमय_seconds();
		list_add_tail(&dp->dl_recall_lru, &nn->del_recall_lru);
	पूर्ण
	spin_unlock(&state_lock);
पूर्ण

अटल पूर्णांक nfsd4_cb_recall_करोne(काष्ठा nfsd4_callback *cb,
		काष्ठा rpc_task *task)
अणु
	काष्ठा nfs4_delegation *dp = cb_to_delegation(cb);

	अगर (dp->dl_stid.sc_type == NFS4_CLOSED_DELEG_STID ||
	    dp->dl_stid.sc_type == NFS4_REVOKED_DELEG_STID)
	        वापस 1;

	चयन (task->tk_status) अणु
	हाल 0:
		वापस 1;
	हाल -NFS4ERR_DELAY:
		rpc_delay(task, 2 * HZ);
		वापस 0;
	हाल -EBADHANDLE:
	हाल -NFS4ERR_BAD_STATEID:
		/*
		 * Race: client probably got cb_recall beक्रमe खोलो reply
		 * granting delegation.
		 */
		अगर (dp->dl_retries--) अणु
			rpc_delay(task, 2 * HZ);
			वापस 0;
		पूर्ण
		fallthrough;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम nfsd4_cb_recall_release(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_delegation *dp = cb_to_delegation(cb);

	nfs4_put_stid(&dp->dl_stid);
पूर्ण

अटल स्थिर काष्ठा nfsd4_callback_ops nfsd4_cb_recall_ops = अणु
	.prepare	= nfsd4_cb_recall_prepare,
	.करोne		= nfsd4_cb_recall_करोne,
	.release	= nfsd4_cb_recall_release,
पूर्ण;

अटल व्योम nfsd_अवरोध_one_deleg(काष्ठा nfs4_delegation *dp)
अणु
	/*
	 * We're assuming the state code never drops its reference
	 * without first removing the lease.  Since we're in this lease
	 * callback (and since the lease code is serialized by the
	 * i_lock) we know the server hasn't हटाओd the lease yet, and
	 * we know it's safe to take a reference.
	 */
	refcount_inc(&dp->dl_stid.sc_count);
	nfsd4_run_cb(&dp->dl_recall);
पूर्ण

/* Called from अवरोध_lease() with i_lock held. */
अटल bool
nfsd_अवरोध_deleg_cb(काष्ठा file_lock *fl)
अणु
	bool ret = false;
	काष्ठा nfs4_delegation *dp = (काष्ठा nfs4_delegation *)fl->fl_owner;
	काष्ठा nfs4_file *fp = dp->dl_stid.sc_file;

	trace_nfsd_deleg_अवरोध(&dp->dl_stid.sc_stateid);

	/*
	 * We करोn't want the locks code to समयout the lease क्रम us;
	 * we'll remove it ourself if a delegation isn't वापसed
	 * in समय:
	 */
	fl->fl_अवरोध_समय = 0;

	spin_lock(&fp->fi_lock);
	fp->fi_had_conflict = true;
	nfsd_अवरोध_one_deleg(dp);
	spin_unlock(&fp->fi_lock);
	वापस ret;
पूर्ण

अटल bool nfsd_अवरोधer_owns_lease(काष्ठा file_lock *fl)
अणु
	काष्ठा nfs4_delegation *dl = fl->fl_owner;
	काष्ठा svc_rqst *rqst;
	काष्ठा nfs4_client *clp;

	अगर (!i_am_nfsd())
		वापस शून्य;
	rqst = kthपढ़ो_data(current);
	/* Note rq_prog == NFS_ACL_PROGRAM is also possible: */
	अगर (rqst->rq_prog != NFS_PROGRAM || rqst->rq_vers < 4)
		वापस शून्य;
	clp = *(rqst->rq_lease_अवरोधer);
	वापस dl->dl_stid.sc_client == clp;
पूर्ण

अटल पूर्णांक
nfsd_change_deleg_cb(काष्ठा file_lock *onlist, पूर्णांक arg,
		     काष्ठा list_head *dispose)
अणु
	अगर (arg & F_UNLCK)
		वापस lease_modअगरy(onlist, arg, dispose);
	अन्यथा
		वापस -EAGAIN;
पूर्ण

अटल स्थिर काष्ठा lock_manager_operations nfsd_lease_mng_ops = अणु
	.lm_अवरोधer_owns_lease = nfsd_अवरोधer_owns_lease,
	.lm_अवरोध = nfsd_अवरोध_deleg_cb,
	.lm_change = nfsd_change_deleg_cb,
पूर्ण;

अटल __be32 nfsd4_check_seqid(काष्ठा nfsd4_compound_state *cstate, काष्ठा nfs4_stateowner *so, u32 seqid)
अणु
	अगर (nfsd4_has_session(cstate))
		वापस nfs_ok;
	अगर (seqid == so->so_seqid - 1)
		वापस nfserr_replay_me;
	अगर (seqid == so->so_seqid)
		वापस nfs_ok;
	वापस nfserr_bad_seqid;
पूर्ण

अटल काष्ठा nfs4_client *lookup_clientid(clientid_t *clid, bool sessions,
						काष्ठा nfsd_net *nn)
अणु
	काष्ठा nfs4_client *found;

	spin_lock(&nn->client_lock);
	found = find_confirmed_client(clid, sessions, nn);
	अगर (found)
		atomic_inc(&found->cl_rpc_users);
	spin_unlock(&nn->client_lock);
	वापस found;
पूर्ण

अटल __be32 set_client(clientid_t *clid,
		काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfsd_net *nn)
अणु
	अगर (cstate->clp) अणु
		अगर (!same_clid(&cstate->clp->cl_clientid, clid))
			वापस nfserr_stale_clientid;
		वापस nfs_ok;
	पूर्ण
	अगर (STALE_CLIENTID(clid, nn))
		वापस nfserr_stale_clientid;
	/*
	 * We're in the 4.0 हाल (otherwise the SEQUENCE op would have
	 * set cstate->clp), so session = false:
	 */
	cstate->clp = lookup_clientid(clid, false, nn);
	अगर (!cstate->clp)
		वापस nfserr_expired;
	वापस nfs_ok;
पूर्ण

__be32
nfsd4_process_खोलो1(काष्ठा nfsd4_compound_state *cstate,
		    काष्ठा nfsd4_खोलो *खोलो, काष्ठा nfsd_net *nn)
अणु
	clientid_t *clientid = &खोलो->op_clientid;
	काष्ठा nfs4_client *clp = शून्य;
	अचिन्हित पूर्णांक strhashval;
	काष्ठा nfs4_खोलोowner *oo = शून्य;
	__be32 status;

	/*
	 * In हाल we need it later, after we've alपढ़ोy created the
	 * file and करोn't want to risk a further failure:
	 */
	खोलो->op_file = nfsd4_alloc_file();
	अगर (खोलो->op_file == शून्य)
		वापस nfserr_jukebox;

	status = set_client(clientid, cstate, nn);
	अगर (status)
		वापस status;
	clp = cstate->clp;

	strhashval = ownerstr_hashval(&खोलो->op_owner);
	oo = find_खोलोstateowner_str(strhashval, खोलो, clp);
	खोलो->op_खोलोowner = oo;
	अगर (!oo) अणु
		जाओ new_owner;
	पूर्ण
	अगर (!(oo->oo_flags & NFS4_OO_CONFIRMED)) अणु
		/* Replace unconfirmed owners without checking क्रम replay. */
		release_खोलोowner(oo);
		खोलो->op_खोलोowner = शून्य;
		जाओ new_owner;
	पूर्ण
	status = nfsd4_check_seqid(cstate, &oo->oo_owner, खोलो->op_seqid);
	अगर (status)
		वापस status;
	जाओ alloc_stateid;
new_owner:
	oo = alloc_init_खोलो_stateowner(strhashval, खोलो, cstate);
	अगर (oo == शून्य)
		वापस nfserr_jukebox;
	खोलो->op_खोलोowner = oo;
alloc_stateid:
	खोलो->op_stp = nfs4_alloc_खोलो_stateid(clp);
	अगर (!खोलो->op_stp)
		वापस nfserr_jukebox;

	अगर (nfsd4_has_session(cstate) &&
	    (cstate->current_fh.fh_export->ex_flags & NFSEXP_PNFS)) अणु
		खोलो->op_odstate = alloc_clnt_odstate(clp);
		अगर (!खोलो->op_odstate)
			वापस nfserr_jukebox;
	पूर्ण

	वापस nfs_ok;
पूर्ण

अटल अंतरभूत __be32
nfs4_check_delegmode(काष्ठा nfs4_delegation *dp, पूर्णांक flags)
अणु
	अगर ((flags & WR_STATE) && (dp->dl_type == NFS4_OPEN_DELEGATE_READ))
		वापस nfserr_खोलोmode;
	अन्यथा
		वापस nfs_ok;
पूर्ण

अटल पूर्णांक share_access_to_flags(u32 share_access)
अणु
	वापस share_access == NFS4_SHARE_ACCESS_READ ? RD_STATE : WR_STATE;
पूर्ण

अटल काष्ठा nfs4_delegation *find_deleg_stateid(काष्ठा nfs4_client *cl, stateid_t *s)
अणु
	काष्ठा nfs4_stid *ret;

	ret = find_stateid_by_type(cl, s,
				NFS4_DELEG_STID|NFS4_REVOKED_DELEG_STID);
	अगर (!ret)
		वापस शून्य;
	वापस delegstateid(ret);
पूर्ण

अटल bool nfsd4_is_deleg_cur(काष्ठा nfsd4_खोलो *खोलो)
अणु
	वापस खोलो->op_claim_type == NFS4_OPEN_CLAIM_DELEGATE_CUR ||
	       खोलो->op_claim_type == NFS4_OPEN_CLAIM_DELEG_CUR_FH;
पूर्ण

अटल __be32
nfs4_check_deleg(काष्ठा nfs4_client *cl, काष्ठा nfsd4_खोलो *खोलो,
		काष्ठा nfs4_delegation **dp)
अणु
	पूर्णांक flags;
	__be32 status = nfserr_bad_stateid;
	काष्ठा nfs4_delegation *deleg;

	deleg = find_deleg_stateid(cl, &खोलो->op_delegate_stateid);
	अगर (deleg == शून्य)
		जाओ out;
	अगर (deleg->dl_stid.sc_type == NFS4_REVOKED_DELEG_STID) अणु
		nfs4_put_stid(&deleg->dl_stid);
		अगर (cl->cl_minorversion)
			status = nfserr_deleg_revoked;
		जाओ out;
	पूर्ण
	flags = share_access_to_flags(खोलो->op_share_access);
	status = nfs4_check_delegmode(deleg, flags);
	अगर (status) अणु
		nfs4_put_stid(&deleg->dl_stid);
		जाओ out;
	पूर्ण
	*dp = deleg;
out:
	अगर (!nfsd4_is_deleg_cur(खोलो))
		वापस nfs_ok;
	अगर (status)
		वापस status;
	खोलो->op_खोलोowner->oo_flags |= NFS4_OO_CONFIRMED;
	वापस nfs_ok;
पूर्ण

अटल अंतरभूत पूर्णांक nfs4_access_to_access(u32 nfs4_access)
अणु
	पूर्णांक flags = 0;

	अगर (nfs4_access & NFS4_SHARE_ACCESS_READ)
		flags |= NFSD_MAY_READ;
	अगर (nfs4_access & NFS4_SHARE_ACCESS_WRITE)
		flags |= NFSD_MAY_WRITE;
	वापस flags;
पूर्ण

अटल अंतरभूत __be32
nfsd4_truncate(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fh,
		काष्ठा nfsd4_खोलो *खोलो)
अणु
	काष्ठा iattr iattr = अणु
		.ia_valid = ATTR_SIZE,
		.ia_size = 0,
	पूर्ण;
	अगर (!खोलो->op_truncate)
		वापस 0;
	अगर (!(खोलो->op_share_access & NFS4_SHARE_ACCESS_WRITE))
		वापस nfserr_inval;
	वापस nfsd_setattr(rqstp, fh, &iattr, 0, (समय64_t)0);
पूर्ण

अटल __be32 nfs4_get_vfs_file(काष्ठा svc_rqst *rqstp, काष्ठा nfs4_file *fp,
		काष्ठा svc_fh *cur_fh, काष्ठा nfs4_ol_stateid *stp,
		काष्ठा nfsd4_खोलो *खोलो)
अणु
	काष्ठा nfsd_file *nf = शून्य;
	__be32 status;
	पूर्णांक oflag = nfs4_access_to_omode(खोलो->op_share_access);
	पूर्णांक access = nfs4_access_to_access(खोलो->op_share_access);
	अचिन्हित अक्षर old_access_bmap, old_deny_bmap;

	spin_lock(&fp->fi_lock);

	/*
	 * Are we trying to set a deny mode that would conflict with
	 * current access?
	 */
	status = nfs4_file_check_deny(fp, खोलो->op_share_deny);
	अगर (status != nfs_ok) अणु
		spin_unlock(&fp->fi_lock);
		जाओ out;
	पूर्ण

	/* set access to the file */
	status = nfs4_file_get_access(fp, खोलो->op_share_access);
	अगर (status != nfs_ok) अणु
		spin_unlock(&fp->fi_lock);
		जाओ out;
	पूर्ण

	/* Set access bits in stateid */
	old_access_bmap = stp->st_access_bmap;
	set_access(खोलो->op_share_access, stp);

	/* Set new deny mask */
	old_deny_bmap = stp->st_deny_bmap;
	set_deny(खोलो->op_share_deny, stp);
	fp->fi_share_deny |= (खोलो->op_share_deny & NFS4_SHARE_DENY_BOTH);

	अगर (!fp->fi_fds[oflag]) अणु
		spin_unlock(&fp->fi_lock);
		status = nfsd_file_acquire(rqstp, cur_fh, access, &nf);
		अगर (status)
			जाओ out_put_access;
		spin_lock(&fp->fi_lock);
		अगर (!fp->fi_fds[oflag]) अणु
			fp->fi_fds[oflag] = nf;
			nf = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock(&fp->fi_lock);
	अगर (nf)
		nfsd_file_put(nf);

	status = nfsत्रुटि_सं(nfsd_खोलो_अवरोध_lease(cur_fh->fh_dentry->d_inode,
								access));
	अगर (status)
		जाओ out_put_access;

	status = nfsd4_truncate(rqstp, cur_fh, खोलो);
	अगर (status)
		जाओ out_put_access;
out:
	वापस status;
out_put_access:
	stp->st_access_bmap = old_access_bmap;
	nfs4_file_put_access(fp, खोलो->op_share_access);
	reset_जोड़_bmap_deny(bmap_to_share_mode(old_deny_bmap), stp);
	जाओ out;
पूर्ण

अटल __be32
nfs4_upgrade_खोलो(काष्ठा svc_rqst *rqstp, काष्ठा nfs4_file *fp, काष्ठा svc_fh *cur_fh, काष्ठा nfs4_ol_stateid *stp, काष्ठा nfsd4_खोलो *खोलो)
अणु
	__be32 status;
	अचिन्हित अक्षर old_deny_bmap = stp->st_deny_bmap;

	अगर (!test_access(खोलो->op_share_access, stp))
		वापस nfs4_get_vfs_file(rqstp, fp, cur_fh, stp, खोलो);

	/* test and set deny mode */
	spin_lock(&fp->fi_lock);
	status = nfs4_file_check_deny(fp, खोलो->op_share_deny);
	अगर (status == nfs_ok) अणु
		set_deny(खोलो->op_share_deny, stp);
		fp->fi_share_deny |=
				(खोलो->op_share_deny & NFS4_SHARE_DENY_BOTH);
	पूर्ण
	spin_unlock(&fp->fi_lock);

	अगर (status != nfs_ok)
		वापस status;

	status = nfsd4_truncate(rqstp, cur_fh, खोलो);
	अगर (status != nfs_ok)
		reset_जोड़_bmap_deny(old_deny_bmap, stp);
	वापस status;
पूर्ण

/* Should we give out recallable state?: */
अटल bool nfsd4_cb_channel_good(काष्ठा nfs4_client *clp)
अणु
	अगर (clp->cl_cb_state == NFSD4_CB_UP)
		वापस true;
	/*
	 * In the sessions हाल, since we करोn't have to establish a
	 * separate connection क्रम callbacks, we assume it's OK
	 * until we hear otherwise:
	 */
	वापस clp->cl_minorversion && clp->cl_cb_state == NFSD4_CB_UNKNOWN;
पूर्ण

अटल काष्ठा file_lock *nfs4_alloc_init_lease(काष्ठा nfs4_delegation *dp,
						पूर्णांक flag)
अणु
	काष्ठा file_lock *fl;

	fl = locks_alloc_lock();
	अगर (!fl)
		वापस शून्य;
	fl->fl_lmops = &nfsd_lease_mng_ops;
	fl->fl_flags = FL_DELEG;
	fl->fl_type = flag == NFS4_OPEN_DELEGATE_READ? F_RDLCK: F_WRLCK;
	fl->fl_end = OFFSET_MAX;
	fl->fl_owner = (fl_owner_t)dp;
	fl->fl_pid = current->tgid;
	fl->fl_file = dp->dl_stid.sc_file->fi_deleg_file->nf_file;
	वापस fl;
पूर्ण

अटल पूर्णांक nfsd4_check_conflicting_खोलोs(काष्ठा nfs4_client *clp,
					 काष्ठा nfs4_file *fp)
अणु
	काष्ठा nfs4_ol_stateid *st;
	काष्ठा file *f = fp->fi_deleg_file->nf_file;
	काष्ठा inode *ino = locks_inode(f);
	पूर्णांक ग_लिखोs;

	ग_लिखोs = atomic_पढ़ो(&ino->i_ग_लिखोcount);
	अगर (!ग_लिखोs)
		वापस 0;
	/*
	 * There could be multiple filehandles (hence multiple
	 * nfs4_files) referencing this file, but that's not too
	 * common; let's just give up in that हाल rather than
	 * trying to go look up all the clients using that other
	 * nfs4_file as well:
	 */
	अगर (fp->fi_aliased)
		वापस -EAGAIN;
	/*
	 * If there's a बंद in progress, make sure that we see it
	 * clear any fi_fds[] entries beक्रमe we see it decrement
	 * i_ग_लिखोcount:
	 */
	smp_mb__after_atomic();

	अगर (fp->fi_fds[O_WRONLY])
		ग_लिखोs--;
	अगर (fp->fi_fds[O_RDWR])
		ग_लिखोs--;
	अगर (ग_लिखोs > 0)
		वापस -EAGAIN; /* There may be non-NFSv4 ग_लिखोrs */
	/*
	 * It's possible there are non-NFSv4 ग_लिखो खोलोs in progress,
	 * but अगर they haven't incremented i_ग_लिखोcount yet then they
	 * also haven't called break lease yet; so, they'll अवरोध this
	 * lease soon enough.  So, all that's left to check क्रम is NFSv4
	 * खोलोs:
	 */
	spin_lock(&fp->fi_lock);
	list_क्रम_each_entry(st, &fp->fi_stateids, st_perfile) अणु
		अगर (st->st_खोलोstp == शून्य /* it's an खोलो */ &&
		    access_permit_ग_लिखो(st) &&
		    st->st_stid.sc_client != clp) अणु
			spin_unlock(&fp->fi_lock);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	spin_unlock(&fp->fi_lock);
	/*
	 * There's a small chance that we could be racing with another
	 * NFSv4 खोलो.  However, any खोलो that hasn't added itself to
	 * the fi_stateids list also hasn't called अवरोध_lease yet; so,
	 * they'll अवरोध this lease soon enough.
	 */
	वापस 0;
पूर्ण

अटल काष्ठा nfs4_delegation *
nfs4_set_delegation(काष्ठा nfs4_client *clp, काष्ठा svc_fh *fh,
		    काष्ठा nfs4_file *fp, काष्ठा nfs4_clnt_odstate *odstate)
अणु
	पूर्णांक status = 0;
	काष्ठा nfs4_delegation *dp;
	काष्ठा nfsd_file *nf;
	काष्ठा file_lock *fl;

	/*
	 * The fi_had_conflict and nfs_get_existing_delegation checks
	 * here are just optimizations; we'll need to recheck them at
	 * the end:
	 */
	अगर (fp->fi_had_conflict)
		वापस ERR_PTR(-EAGAIN);

	nf = find_पढ़ोable_file(fp);
	अगर (!nf) अणु
		/*
		 * We probably could attempt another खोलो and get a पढ़ो
		 * delegation, but क्रम now, करोn't bother until the
		 * client actually sends us one.
		 */
		वापस ERR_PTR(-EAGAIN);
	पूर्ण
	spin_lock(&state_lock);
	spin_lock(&fp->fi_lock);
	अगर (nfs4_delegation_exists(clp, fp))
		status = -EAGAIN;
	अन्यथा अगर (!fp->fi_deleg_file) अणु
		fp->fi_deleg_file = nf;
		/* increment early to prevent fi_deleg_file from being
		 * cleared */
		fp->fi_delegees = 1;
		nf = शून्य;
	पूर्ण अन्यथा
		fp->fi_delegees++;
	spin_unlock(&fp->fi_lock);
	spin_unlock(&state_lock);
	अगर (nf)
		nfsd_file_put(nf);
	अगर (status)
		वापस ERR_PTR(status);

	status = -ENOMEM;
	dp = alloc_init_deleg(clp, fp, fh, odstate);
	अगर (!dp)
		जाओ out_delegees;

	fl = nfs4_alloc_init_lease(dp, NFS4_OPEN_DELEGATE_READ);
	अगर (!fl)
		जाओ out_clnt_odstate;

	status = vfs_setlease(fp->fi_deleg_file->nf_file, fl->fl_type, &fl, शून्य);
	अगर (fl)
		locks_मुक्त_lock(fl);
	अगर (status)
		जाओ out_clnt_odstate;
	status = nfsd4_check_conflicting_खोलोs(clp, fp);
	अगर (status)
		जाओ out_unlock;

	spin_lock(&state_lock);
	spin_lock(&fp->fi_lock);
	अगर (fp->fi_had_conflict)
		status = -EAGAIN;
	अन्यथा
		status = hash_delegation_locked(dp, fp);
	spin_unlock(&fp->fi_lock);
	spin_unlock(&state_lock);

	अगर (status)
		जाओ out_unlock;

	वापस dp;
out_unlock:
	vfs_setlease(fp->fi_deleg_file->nf_file, F_UNLCK, शून्य, (व्योम **)&dp);
out_clnt_odstate:
	put_clnt_odstate(dp->dl_clnt_odstate);
	nfs4_put_stid(&dp->dl_stid);
out_delegees:
	put_deleg_file(fp);
	वापस ERR_PTR(status);
पूर्ण

अटल व्योम nfsd4_खोलो_deleg_none_ext(काष्ठा nfsd4_खोलो *खोलो, पूर्णांक status)
अणु
	खोलो->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
	अगर (status == -EAGAIN)
		खोलो->op_why_no_deleg = WND4_CONTENTION;
	अन्यथा अणु
		खोलो->op_why_no_deleg = WND4_RESOURCE;
		चयन (खोलो->op_deleg_want) अणु
		हाल NFS4_SHARE_WANT_READ_DELEG:
		हाल NFS4_SHARE_WANT_WRITE_DELEG:
		हाल NFS4_SHARE_WANT_ANY_DELEG:
			अवरोध;
		हाल NFS4_SHARE_WANT_CANCEL:
			खोलो->op_why_no_deleg = WND4_CANCELLED;
			अवरोध;
		हाल NFS4_SHARE_WANT_NO_DELEG:
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Attempt to hand out a delegation.
 *
 * Note we करोn't support write delegations, and won't until the vfs has
 * proper support क्रम them.
 */
अटल व्योम
nfs4_खोलो_delegation(काष्ठा svc_fh *fh, काष्ठा nfsd4_खोलो *खोलो,
			काष्ठा nfs4_ol_stateid *stp)
अणु
	काष्ठा nfs4_delegation *dp;
	काष्ठा nfs4_खोलोowner *oo = खोलोowner(stp->st_stateowner);
	काष्ठा nfs4_client *clp = stp->st_stid.sc_client;
	पूर्णांक cb_up;
	पूर्णांक status = 0;

	cb_up = nfsd4_cb_channel_good(oo->oo_owner.so_client);
	खोलो->op_recall = 0;
	चयन (खोलो->op_claim_type) अणु
		हाल NFS4_OPEN_CLAIM_PREVIOUS:
			अगर (!cb_up)
				खोलो->op_recall = 1;
			अगर (खोलो->op_delegate_type != NFS4_OPEN_DELEGATE_READ)
				जाओ out_no_deleg;
			अवरोध;
		हाल NFS4_OPEN_CLAIM_शून्य:
		हाल NFS4_OPEN_CLAIM_FH:
			/*
			 * Let's not give out any delegations till everyone's
			 * had the chance to reclaim theirs, *and* until
			 * NLM locks have all been reclaimed:
			 */
			अगर (locks_in_grace(clp->net))
				जाओ out_no_deleg;
			अगर (!cb_up || !(oo->oo_flags & NFS4_OO_CONFIRMED))
				जाओ out_no_deleg;
			अवरोध;
		शेष:
			जाओ out_no_deleg;
	पूर्ण
	dp = nfs4_set_delegation(clp, fh, stp->st_stid.sc_file, stp->st_clnt_odstate);
	अगर (IS_ERR(dp))
		जाओ out_no_deleg;

	स_नकल(&खोलो->op_delegate_stateid, &dp->dl_stid.sc_stateid, माप(dp->dl_stid.sc_stateid));

	trace_nfsd_deleg_पढ़ो(&dp->dl_stid.sc_stateid);
	खोलो->op_delegate_type = NFS4_OPEN_DELEGATE_READ;
	nfs4_put_stid(&dp->dl_stid);
	वापस;
out_no_deleg:
	खोलो->op_delegate_type = NFS4_OPEN_DELEGATE_NONE;
	अगर (खोलो->op_claim_type == NFS4_OPEN_CLAIM_PREVIOUS &&
	    खोलो->op_delegate_type != NFS4_OPEN_DELEGATE_NONE) अणु
		dprपूर्णांकk("NFSD: WARNING: refusing delegation reclaim\n");
		खोलो->op_recall = 1;
	पूर्ण

	/* 4.1 client asking क्रम a delegation? */
	अगर (खोलो->op_deleg_want)
		nfsd4_खोलो_deleg_none_ext(खोलो, status);
	वापस;
पूर्ण

अटल व्योम nfsd4_deleg_xgrade_none_ext(काष्ठा nfsd4_खोलो *खोलो,
					काष्ठा nfs4_delegation *dp)
अणु
	अगर (खोलो->op_deleg_want == NFS4_SHARE_WANT_READ_DELEG &&
	    dp->dl_type == NFS4_OPEN_DELEGATE_WRITE) अणु
		खोलो->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
		खोलो->op_why_no_deleg = WND4_NOT_SUPP_DOWNGRADE;
	पूर्ण अन्यथा अगर (खोलो->op_deleg_want == NFS4_SHARE_WANT_WRITE_DELEG &&
		   dp->dl_type == NFS4_OPEN_DELEGATE_WRITE) अणु
		खोलो->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
		खोलो->op_why_no_deleg = WND4_NOT_SUPP_UPGRADE;
	पूर्ण
	/* Otherwise the client must be confused wanting a delegation
	 * it alपढ़ोy has, thereक्रमe we करोn't वापस
	 * NFS4_OPEN_DELEGATE_NONE_EXT and reason.
	 */
पूर्ण

__be32
nfsd4_process_खोलो2(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *current_fh, काष्ठा nfsd4_खोलो *खोलो)
अणु
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	काष्ठा nfs4_client *cl = खोलो->op_खोलोowner->oo_owner.so_client;
	काष्ठा nfs4_file *fp = शून्य;
	काष्ठा nfs4_ol_stateid *stp = शून्य;
	काष्ठा nfs4_delegation *dp = शून्य;
	__be32 status;
	bool new_stp = false;

	/*
	 * Lookup file; अगर found, lookup stateid and check खोलो request,
	 * and check क्रम delegations in the process of being recalled.
	 * If not found, create the nfs4_file काष्ठा
	 */
	fp = find_or_add_file(खोलो->op_file, current_fh);
	अगर (fp != खोलो->op_file) अणु
		status = nfs4_check_deleg(cl, खोलो, &dp);
		अगर (status)
			जाओ out;
		stp = nfsd4_find_and_lock_existing_खोलो(fp, खोलो);
	पूर्ण अन्यथा अणु
		खोलो->op_file = शून्य;
		status = nfserr_bad_stateid;
		अगर (nfsd4_is_deleg_cur(खोलो))
			जाओ out;
	पूर्ण

	अगर (!stp) अणु
		stp = init_खोलो_stateid(fp, खोलो);
		अगर (!खोलो->op_stp)
			new_stp = true;
	पूर्ण

	/*
	 * OPEN the file, or upgrade an existing OPEN.
	 * If truncate fails, the OPEN fails.
	 *
	 * stp is alपढ़ोy locked.
	 */
	अगर (!new_stp) अणु
		/* Stateid was found, this is an OPEN upgrade */
		status = nfs4_upgrade_खोलो(rqstp, fp, current_fh, stp, खोलो);
		अगर (status) अणु
			mutex_unlock(&stp->st_mutex);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = nfs4_get_vfs_file(rqstp, fp, current_fh, stp, खोलो);
		अगर (status) अणु
			stp->st_stid.sc_type = NFS4_CLOSED_STID;
			release_खोलो_stateid(stp);
			mutex_unlock(&stp->st_mutex);
			जाओ out;
		पूर्ण

		stp->st_clnt_odstate = find_or_hash_clnt_odstate(fp,
							खोलो->op_odstate);
		अगर (stp->st_clnt_odstate == खोलो->op_odstate)
			खोलो->op_odstate = शून्य;
	पूर्ण

	nfs4_inc_and_copy_stateid(&खोलो->op_stateid, &stp->st_stid);
	mutex_unlock(&stp->st_mutex);

	अगर (nfsd4_has_session(&resp->cstate)) अणु
		अगर (खोलो->op_deleg_want & NFS4_SHARE_WANT_NO_DELEG) अणु
			खोलो->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
			खोलो->op_why_no_deleg = WND4_NOT_WANTED;
			जाओ nodeleg;
		पूर्ण
	पूर्ण

	/*
	* Attempt to hand out a delegation. No error वापस, because the
	* OPEN succeeds even अगर we fail.
	*/
	nfs4_खोलो_delegation(current_fh, खोलो, stp);
nodeleg:
	status = nfs_ok;
	trace_nfsd_खोलो(&stp->st_stid.sc_stateid);
out:
	/* 4.1 client trying to upgrade/करोwngrade delegation? */
	अगर (खोलो->op_delegate_type == NFS4_OPEN_DELEGATE_NONE && dp &&
	    खोलो->op_deleg_want)
		nfsd4_deleg_xgrade_none_ext(खोलो, dp);

	अगर (fp)
		put_nfs4_file(fp);
	अगर (status == 0 && खोलो->op_claim_type == NFS4_OPEN_CLAIM_PREVIOUS)
		खोलो->op_खोलोowner->oo_flags |= NFS4_OO_CONFIRMED;
	/*
	* To finish the खोलो response, we just need to set the rflags.
	*/
	खोलो->op_rflags = NFS4_OPEN_RESULT_LOCKTYPE_POSIX;
	अगर (nfsd4_has_session(&resp->cstate))
		खोलो->op_rflags |= NFS4_OPEN_RESULT_MAY_NOTIFY_LOCK;
	अन्यथा अगर (!(खोलो->op_खोलोowner->oo_flags & NFS4_OO_CONFIRMED))
		खोलो->op_rflags |= NFS4_OPEN_RESULT_CONFIRM;

	अगर (dp)
		nfs4_put_stid(&dp->dl_stid);
	अगर (stp)
		nfs4_put_stid(&stp->st_stid);

	वापस status;
पूर्ण

व्योम nfsd4_cleanup_खोलो_state(काष्ठा nfsd4_compound_state *cstate,
			      काष्ठा nfsd4_खोलो *खोलो)
अणु
	अगर (खोलो->op_खोलोowner) अणु
		काष्ठा nfs4_stateowner *so = &खोलो->op_खोलोowner->oo_owner;

		nfsd4_cstate_assign_replay(cstate, so);
		nfs4_put_stateowner(so);
	पूर्ण
	अगर (खोलो->op_file)
		kmem_cache_मुक्त(file_slab, खोलो->op_file);
	अगर (खोलो->op_stp)
		nfs4_put_stid(&खोलो->op_stp->st_stid);
	अगर (खोलो->op_odstate)
		kmem_cache_मुक्त(odstate_slab, खोलो->op_odstate);
पूर्ण

__be32
nfsd4_renew(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	    जोड़ nfsd4_op_u *u)
अणु
	clientid_t *clid = &u->renew;
	काष्ठा nfs4_client *clp;
	__be32 status;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	trace_nfsd_clid_renew(clid);
	status = set_client(clid, cstate, nn);
	अगर (status)
		वापस status;
	clp = cstate->clp;
	अगर (!list_empty(&clp->cl_delegations)
			&& clp->cl_cb_state != NFSD4_CB_UP)
		वापस nfserr_cb_path_करोwn;
	वापस nfs_ok;
पूर्ण

व्योम
nfsd4_end_grace(काष्ठा nfsd_net *nn)
अणु
	/* करो nothing अगर grace period alपढ़ोy ended */
	अगर (nn->grace_ended)
		वापस;

	trace_nfsd_grace_complete(nn);
	nn->grace_ended = true;
	/*
	 * If the server goes करोwn again right now, an NFSv4
	 * client will still be allowed to reclaim after it comes back up,
	 * even अगर it hasn't yet had a chance to reclaim state this समय.
	 *
	 */
	nfsd4_record_grace_करोne(nn);
	/*
	 * At this poपूर्णांक, NFSv4 clients can still reclaim.  But अगर the
	 * server crashes, any that have not yet reclaimed will be out
	 * of luck on the next boot.
	 *
	 * (NFSv4.1+ clients are considered to have reclaimed once they
	 * call RECLAIM_COMPLETE.  NFSv4.0 clients are considered to
	 * have reclaimed after their first OPEN.)
	 */
	locks_end_grace(&nn->nfsd4_manager);
	/*
	 * At this poपूर्णांक, and once lockd and/or any other containers
	 * निकास their grace period, further reclaims will fail and
	 * regular locking can resume.
	 */
पूर्ण

/*
 * If we've रुकोed a lease period but there are still clients trying to
 * reclaim, रुको a little दीर्घer to give them a chance to finish.
 */
अटल bool clients_still_reclaiming(काष्ठा nfsd_net *nn)
अणु
	समय64_t द्विगुन_grace_period_end = nn->boot_समय +
					   2 * nn->nfsd4_lease;

	अगर (nn->track_reclaim_completes &&
			atomic_पढ़ो(&nn->nr_reclaim_complete) ==
			nn->reclaim_str_hashtbl_size)
		वापस false;
	अगर (!nn->somebody_reclaimed)
		वापस false;
	nn->somebody_reclaimed = false;
	/*
	 * If we've given them *two* lease times to reclaim, and they're
	 * still not करोne, give up:
	 */
	अगर (kसमय_get_bootसमय_seconds() > द्विगुन_grace_period_end)
		वापस false;
	वापस true;
पूर्ण

काष्ठा laundry_समय अणु
	समय64_t cutoff;
	समय64_t new_समयo;
पूर्ण;

अटल bool state_expired(काष्ठा laundry_समय *lt, समय64_t last_refresh)
अणु
	समय64_t समय_reमुख्यing;

	अगर (last_refresh < lt->cutoff)
		वापस true;
	समय_reमुख्यing = last_refresh - lt->cutoff;
	lt->new_समयo = min(lt->new_समयo, समय_reमुख्यing);
	वापस false;
पूर्ण

अटल समय64_t
nfs4_laundromat(काष्ठा nfsd_net *nn)
अणु
	काष्ठा nfs4_client *clp;
	काष्ठा nfs4_खोलोowner *oo;
	काष्ठा nfs4_delegation *dp;
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा nfsd4_blocked_lock *nbl;
	काष्ठा list_head *pos, *next, reaplist;
	काष्ठा laundry_समय lt = अणु
		.cutoff = kसमय_get_bootसमय_seconds() - nn->nfsd4_lease,
		.new_समयo = nn->nfsd4_lease
	पूर्ण;
	काष्ठा nfs4_cpntf_state *cps;
	copy_stateid_t *cps_t;
	पूर्णांक i;

	अगर (clients_still_reclaiming(nn)) अणु
		lt.new_समयo = 0;
		जाओ out;
	पूर्ण
	nfsd4_end_grace(nn);
	INIT_LIST_HEAD(&reaplist);

	spin_lock(&nn->s2s_cp_lock);
	idr_क्रम_each_entry(&nn->s2s_cp_stateids, cps_t, i) अणु
		cps = container_of(cps_t, काष्ठा nfs4_cpntf_state, cp_stateid);
		अगर (cps->cp_stateid.sc_type == NFS4_COPYNOTIFY_STID &&
				state_expired(&lt, cps->cpntf_समय))
			_मुक्त_cpntf_state_locked(nn, cps);
	पूर्ण
	spin_unlock(&nn->s2s_cp_lock);

	spin_lock(&nn->client_lock);
	list_क्रम_each_safe(pos, next, &nn->client_lru) अणु
		clp = list_entry(pos, काष्ठा nfs4_client, cl_lru);
		अगर (!state_expired(&lt, clp->cl_समय))
			अवरोध;
		अगर (mark_client_expired_locked(clp)) अणु
			trace_nfsd_clid_expired(&clp->cl_clientid);
			जारी;
		पूर्ण
		list_add(&clp->cl_lru, &reaplist);
	पूर्ण
	spin_unlock(&nn->client_lock);
	list_क्रम_each_safe(pos, next, &reaplist) अणु
		clp = list_entry(pos, काष्ठा nfs4_client, cl_lru);
		trace_nfsd_clid_purged(&clp->cl_clientid);
		list_del_init(&clp->cl_lru);
		expire_client(clp);
	पूर्ण
	spin_lock(&state_lock);
	list_क्रम_each_safe(pos, next, &nn->del_recall_lru) अणु
		dp = list_entry (pos, काष्ठा nfs4_delegation, dl_recall_lru);
		अगर (!state_expired(&lt, dp->dl_समय))
			अवरोध;
		WARN_ON(!unhash_delegation_locked(dp));
		list_add(&dp->dl_recall_lru, &reaplist);
	पूर्ण
	spin_unlock(&state_lock);
	जबतक (!list_empty(&reaplist)) अणु
		dp = list_first_entry(&reaplist, काष्ठा nfs4_delegation,
					dl_recall_lru);
		list_del_init(&dp->dl_recall_lru);
		revoke_delegation(dp);
	पूर्ण

	spin_lock(&nn->client_lock);
	जबतक (!list_empty(&nn->बंद_lru)) अणु
		oo = list_first_entry(&nn->बंद_lru, काष्ठा nfs4_खोलोowner,
					oo_बंद_lru);
		अगर (!state_expired(&lt, oo->oo_समय))
			अवरोध;
		list_del_init(&oo->oo_बंद_lru);
		stp = oo->oo_last_बंदd_stid;
		oo->oo_last_बंदd_stid = शून्य;
		spin_unlock(&nn->client_lock);
		nfs4_put_stid(&stp->st_stid);
		spin_lock(&nn->client_lock);
	पूर्ण
	spin_unlock(&nn->client_lock);

	/*
	 * It's possible क्रम a client to try and acquire an alपढ़ोy held lock
	 * that is being held क्रम a दीर्घ समय, and then lose पूर्णांकerest in it.
	 * So, we clean out any un-revisited request after a lease period
	 * under the assumption that the client is no दीर्घer पूर्णांकerested.
	 *
	 * RFC5661, sec. 9.6 states that the client must not rely on getting
	 * notअगरications and must जारी to poll क्रम locks, even when the
	 * server supports them. Thus this shouldn't lead to clients blocking
	 * indefinitely once the lock करोes become मुक्त.
	 */
	BUG_ON(!list_empty(&reaplist));
	spin_lock(&nn->blocked_locks_lock);
	जबतक (!list_empty(&nn->blocked_locks_lru)) अणु
		nbl = list_first_entry(&nn->blocked_locks_lru,
					काष्ठा nfsd4_blocked_lock, nbl_lru);
		अगर (!state_expired(&lt, nbl->nbl_समय))
			अवरोध;
		list_move(&nbl->nbl_lru, &reaplist);
		list_del_init(&nbl->nbl_list);
	पूर्ण
	spin_unlock(&nn->blocked_locks_lock);

	जबतक (!list_empty(&reaplist)) अणु
		nbl = list_first_entry(&reaplist,
					काष्ठा nfsd4_blocked_lock, nbl_lru);
		list_del_init(&nbl->nbl_lru);
		मुक्त_blocked_lock(nbl);
	पूर्ण
out:
	वापस max_t(समय64_t, lt.new_समयo, NFSD_LAUNDROMAT_MINTIMEOUT);
पूर्ण

अटल काष्ठा workqueue_काष्ठा *laundry_wq;
अटल व्योम laundromat_मुख्य(काष्ठा work_काष्ठा *);

अटल व्योम
laundromat_मुख्य(काष्ठा work_काष्ठा *laundry)
अणु
	समय64_t t;
	काष्ठा delayed_work *dwork = to_delayed_work(laundry);
	काष्ठा nfsd_net *nn = container_of(dwork, काष्ठा nfsd_net,
					   laundromat_work);

	t = nfs4_laundromat(nn);
	queue_delayed_work(laundry_wq, &nn->laundromat_work, t*HZ);
पूर्ण

अटल अंतरभूत __be32 nfs4_check_fh(काष्ठा svc_fh *fhp, काष्ठा nfs4_stid *stp)
अणु
	अगर (!fh_match(&fhp->fh_handle, &stp->sc_file->fi_fhandle))
		वापस nfserr_bad_stateid;
	वापस nfs_ok;
पूर्ण

अटल
__be32 nfs4_check_खोलोmode(काष्ठा nfs4_ol_stateid *stp, पूर्णांक flags)
अणु
        __be32 status = nfserr_खोलोmode;

	/* For lock stateid's, we test the parent खोलो, not the lock: */
	अगर (stp->st_खोलोstp)
		stp = stp->st_खोलोstp;
	अगर ((flags & WR_STATE) && !access_permit_ग_लिखो(stp))
                जाओ out;
	अगर ((flags & RD_STATE) && !access_permit_पढ़ो(stp))
                जाओ out;
	status = nfs_ok;
out:
	वापस status;
पूर्ण

अटल अंतरभूत __be32
check_special_stateids(काष्ठा net *net, svc_fh *current_fh, stateid_t *stateid, पूर्णांक flags)
अणु
	अगर (ONE_STATEID(stateid) && (flags & RD_STATE))
		वापस nfs_ok;
	अन्यथा अगर (खोलोs_in_grace(net)) अणु
		/* Answer in reमुख्यing हालs depends on existence of
		 * conflicting state; so we must रुको out the grace period. */
		वापस nfserr_grace;
	पूर्ण अन्यथा अगर (flags & WR_STATE)
		वापस nfs4_share_conflict(current_fh,
				NFS4_SHARE_DENY_WRITE);
	अन्यथा /* (flags & RD_STATE) && ZERO_STATEID(stateid) */
		वापस nfs4_share_conflict(current_fh,
				NFS4_SHARE_DENY_READ);
पूर्ण

/*
 * Allow READ/WRITE during grace period on recovered state only क्रम files
 * that are not able to provide mandatory locking.
 */
अटल अंतरभूत पूर्णांक
grace_disallows_io(काष्ठा net *net, काष्ठा inode *inode)
अणु
	वापस खोलोs_in_grace(net) && mandatory_lock(inode);
पूर्ण

अटल __be32 check_stateid_generation(stateid_t *in, stateid_t *ref, bool has_session)
अणु
	/*
	 * When sessions are used the stateid generation number is ignored
	 * when it is zero.
	 */
	अगर (has_session && in->si_generation == 0)
		वापस nfs_ok;

	अगर (in->si_generation == ref->si_generation)
		वापस nfs_ok;

	/* If the client sends us a stateid from the future, it's buggy: */
	अगर (nfsd4_stateid_generation_after(in, ref))
		वापस nfserr_bad_stateid;
	/*
	 * However, we could see a stateid from the past, even from a
	 * non-buggy client.  For example, अगर the client sends a lock
	 * जबतक some IO is outstanding, the lock may bump si_generation
	 * जबतक the IO is still in flight.  The client could aव्योम that
	 * situation by रुकोing क्रम responses on all the IO requests,
	 * but better perक्रमmance may result in retrying IO that
	 * receives an old_stateid error अगर requests are rarely
	 * reordered in flight:
	 */
	वापस nfserr_old_stateid;
पूर्ण

अटल __be32 nfsd4_stid_check_stateid_generation(stateid_t *in, काष्ठा nfs4_stid *s, bool has_session)
अणु
	__be32 ret;

	spin_lock(&s->sc_lock);
	ret = nfsd4_verअगरy_खोलो_stid(s);
	अगर (ret == nfs_ok)
		ret = check_stateid_generation(in, &s->sc_stateid, has_session);
	spin_unlock(&s->sc_lock);
	वापस ret;
पूर्ण

अटल __be32 nfsd4_check_खोलोowner_confirmed(काष्ठा nfs4_ol_stateid *ols)
अणु
	अगर (ols->st_stateowner->so_is_खोलो_owner &&
	    !(खोलोowner(ols->st_stateowner)->oo_flags & NFS4_OO_CONFIRMED))
		वापस nfserr_bad_stateid;
	वापस nfs_ok;
पूर्ण

अटल __be32 nfsd4_validate_stateid(काष्ठा nfs4_client *cl, stateid_t *stateid)
अणु
	काष्ठा nfs4_stid *s;
	__be32 status = nfserr_bad_stateid;

	अगर (ZERO_STATEID(stateid) || ONE_STATEID(stateid) ||
		CLOSE_STATEID(stateid))
		वापस status;
	अगर (!same_clid(&stateid->si_opaque.so_clid, &cl->cl_clientid))
		वापस status;
	spin_lock(&cl->cl_lock);
	s = find_stateid_locked(cl, stateid);
	अगर (!s)
		जाओ out_unlock;
	status = nfsd4_stid_check_stateid_generation(stateid, s, 1);
	अगर (status)
		जाओ out_unlock;
	चयन (s->sc_type) अणु
	हाल NFS4_DELEG_STID:
		status = nfs_ok;
		अवरोध;
	हाल NFS4_REVOKED_DELEG_STID:
		status = nfserr_deleg_revoked;
		अवरोध;
	हाल NFS4_OPEN_STID:
	हाल NFS4_LOCK_STID:
		status = nfsd4_check_खोलोowner_confirmed(खोलोlockstateid(s));
		अवरोध;
	शेष:
		prपूर्णांकk("unknown stateid type %x\n", s->sc_type);
		fallthrough;
	हाल NFS4_CLOSED_STID:
	हाल NFS4_CLOSED_DELEG_STID:
		status = nfserr_bad_stateid;
	पूर्ण
out_unlock:
	spin_unlock(&cl->cl_lock);
	वापस status;
पूर्ण

__be32
nfsd4_lookup_stateid(काष्ठा nfsd4_compound_state *cstate,
		     stateid_t *stateid, अचिन्हित अक्षर typemask,
		     काष्ठा nfs4_stid **s, काष्ठा nfsd_net *nn)
अणु
	__be32 status;
	bool वापस_revoked = false;

	/*
	 *  only वापस revoked delegations अगर explicitly asked.
	 *  otherwise we report revoked or bad_stateid status.
	 */
	अगर (typemask & NFS4_REVOKED_DELEG_STID)
		वापस_revoked = true;
	अन्यथा अगर (typemask & NFS4_DELEG_STID)
		typemask |= NFS4_REVOKED_DELEG_STID;

	अगर (ZERO_STATEID(stateid) || ONE_STATEID(stateid) ||
		CLOSE_STATEID(stateid))
		वापस nfserr_bad_stateid;
	status = set_client(&stateid->si_opaque.so_clid, cstate, nn);
	अगर (status == nfserr_stale_clientid) अणु
		अगर (cstate->session)
			वापस nfserr_bad_stateid;
		वापस nfserr_stale_stateid;
	पूर्ण
	अगर (status)
		वापस status;
	*s = find_stateid_by_type(cstate->clp, stateid, typemask);
	अगर (!*s)
		वापस nfserr_bad_stateid;
	अगर (((*s)->sc_type == NFS4_REVOKED_DELEG_STID) && !वापस_revoked) अणु
		nfs4_put_stid(*s);
		अगर (cstate->minorversion)
			वापस nfserr_deleg_revoked;
		वापस nfserr_bad_stateid;
	पूर्ण
	वापस nfs_ok;
पूर्ण

अटल काष्ठा nfsd_file *
nfs4_find_file(काष्ठा nfs4_stid *s, पूर्णांक flags)
अणु
	अगर (!s)
		वापस शून्य;

	चयन (s->sc_type) अणु
	हाल NFS4_DELEG_STID:
		अगर (WARN_ON_ONCE(!s->sc_file->fi_deleg_file))
			वापस शून्य;
		वापस nfsd_file_get(s->sc_file->fi_deleg_file);
	हाल NFS4_OPEN_STID:
	हाल NFS4_LOCK_STID:
		अगर (flags & RD_STATE)
			वापस find_पढ़ोable_file(s->sc_file);
		अन्यथा
			वापस find_ग_लिखोable_file(s->sc_file);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल __be32
nfs4_check_olstateid(काष्ठा nfs4_ol_stateid *ols, पूर्णांक flags)
अणु
	__be32 status;

	status = nfsd4_check_खोलोowner_confirmed(ols);
	अगर (status)
		वापस status;
	वापस nfs4_check_खोलोmode(ols, flags);
पूर्ण

अटल __be32
nfs4_check_file(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, काष्ठा nfs4_stid *s,
		काष्ठा nfsd_file **nfp, पूर्णांक flags)
अणु
	पूर्णांक acc = (flags & RD_STATE) ? NFSD_MAY_READ : NFSD_MAY_WRITE;
	काष्ठा nfsd_file *nf;
	__be32 status;

	nf = nfs4_find_file(s, flags);
	अगर (nf) अणु
		status = nfsd_permission(rqstp, fhp->fh_export, fhp->fh_dentry,
				acc | NFSD_MAY_OWNER_OVERRIDE);
		अगर (status) अणु
			nfsd_file_put(nf);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = nfsd_file_acquire(rqstp, fhp, acc, &nf);
		अगर (status)
			वापस status;
	पूर्ण
	*nfp = nf;
out:
	वापस status;
पूर्ण
अटल व्योम
_मुक्त_cpntf_state_locked(काष्ठा nfsd_net *nn, काष्ठा nfs4_cpntf_state *cps)
अणु
	WARN_ON_ONCE(cps->cp_stateid.sc_type != NFS4_COPYNOTIFY_STID);
	अगर (!refcount_dec_and_test(&cps->cp_stateid.sc_count))
		वापस;
	list_del(&cps->cp_list);
	idr_हटाओ(&nn->s2s_cp_stateids,
		   cps->cp_stateid.stid.si_opaque.so_id);
	kमुक्त(cps);
पूर्ण
/*
 * A READ from an पूर्णांकer server to server COPY will have a
 * copy stateid. Look up the copy notअगरy stateid from the
 * idr काष्ठाure and take a reference on it.
 */
__be32 manage_cpntf_state(काष्ठा nfsd_net *nn, stateid_t *st,
			  काष्ठा nfs4_client *clp,
			  काष्ठा nfs4_cpntf_state **cps)
अणु
	copy_stateid_t *cps_t;
	काष्ठा nfs4_cpntf_state *state = शून्य;

	अगर (st->si_opaque.so_clid.cl_id != nn->s2s_cp_cl_id)
		वापस nfserr_bad_stateid;
	spin_lock(&nn->s2s_cp_lock);
	cps_t = idr_find(&nn->s2s_cp_stateids, st->si_opaque.so_id);
	अगर (cps_t) अणु
		state = container_of(cps_t, काष्ठा nfs4_cpntf_state,
				     cp_stateid);
		अगर (state->cp_stateid.sc_type != NFS4_COPYNOTIFY_STID) अणु
			state = शून्य;
			जाओ unlock;
		पूर्ण
		अगर (!clp)
			refcount_inc(&state->cp_stateid.sc_count);
		अन्यथा
			_मुक्त_cpntf_state_locked(nn, state);
	पूर्ण
unlock:
	spin_unlock(&nn->s2s_cp_lock);
	अगर (!state)
		वापस nfserr_bad_stateid;
	अगर (!clp && state)
		*cps = state;
	वापस 0;
पूर्ण

अटल __be32 find_cpntf_state(काष्ठा nfsd_net *nn, stateid_t *st,
			       काष्ठा nfs4_stid **stid)
अणु
	__be32 status;
	काष्ठा nfs4_cpntf_state *cps = शून्य;
	काष्ठा nfs4_client *found;

	status = manage_cpntf_state(nn, st, शून्य, &cps);
	अगर (status)
		वापस status;

	cps->cpntf_समय = kसमय_get_bootसमय_seconds();

	status = nfserr_expired;
	found = lookup_clientid(&cps->cp_p_clid, true, nn);
	अगर (!found)
		जाओ out;

	*stid = find_stateid_by_type(found, &cps->cp_p_stateid,
			NFS4_DELEG_STID|NFS4_OPEN_STID|NFS4_LOCK_STID);
	अगर (*stid)
		status = nfs_ok;
	अन्यथा
		status = nfserr_bad_stateid;

	put_client_renew(found);
out:
	nfs4_put_cpntf_state(nn, cps);
	वापस status;
पूर्ण

व्योम nfs4_put_cpntf_state(काष्ठा nfsd_net *nn, काष्ठा nfs4_cpntf_state *cps)
अणु
	spin_lock(&nn->s2s_cp_lock);
	_मुक्त_cpntf_state_locked(nn, cps);
	spin_unlock(&nn->s2s_cp_lock);
पूर्ण

/*
 * Checks क्रम stateid operations
 */
__be32
nfs4_preprocess_stateid_op(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, काष्ठा svc_fh *fhp,
		stateid_t *stateid, पूर्णांक flags, काष्ठा nfsd_file **nfp,
		काष्ठा nfs4_stid **cstid)
अणु
	काष्ठा inode *ino = d_inode(fhp->fh_dentry);
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा nfs4_stid *s = शून्य;
	__be32 status;

	अगर (nfp)
		*nfp = शून्य;

	अगर (grace_disallows_io(net, ino))
		वापस nfserr_grace;

	अगर (ZERO_STATEID(stateid) || ONE_STATEID(stateid)) अणु
		status = check_special_stateids(net, fhp, stateid, flags);
		जाओ करोne;
	पूर्ण

	status = nfsd4_lookup_stateid(cstate, stateid,
				NFS4_DELEG_STID|NFS4_OPEN_STID|NFS4_LOCK_STID,
				&s, nn);
	अगर (status == nfserr_bad_stateid)
		status = find_cpntf_state(nn, stateid, &s);
	अगर (status)
		वापस status;
	status = nfsd4_stid_check_stateid_generation(stateid, s,
			nfsd4_has_session(cstate));
	अगर (status)
		जाओ out;

	चयन (s->sc_type) अणु
	हाल NFS4_DELEG_STID:
		status = nfs4_check_delegmode(delegstateid(s), flags);
		अवरोध;
	हाल NFS4_OPEN_STID:
	हाल NFS4_LOCK_STID:
		status = nfs4_check_olstateid(खोलोlockstateid(s), flags);
		अवरोध;
	शेष:
		status = nfserr_bad_stateid;
		अवरोध;
	पूर्ण
	अगर (status)
		जाओ out;
	status = nfs4_check_fh(fhp, s);

करोne:
	अगर (status == nfs_ok && nfp)
		status = nfs4_check_file(rqstp, fhp, s, nfp, flags);
out:
	अगर (s) अणु
		अगर (!status && cstid)
			*cstid = s;
		अन्यथा
			nfs4_put_stid(s);
	पूर्ण
	वापस status;
पूर्ण

/*
 * Test अगर the stateid is valid
 */
__be32
nfsd4_test_stateid(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_test_stateid *test_stateid = &u->test_stateid;
	काष्ठा nfsd4_test_stateid_id *stateid;
	काष्ठा nfs4_client *cl = cstate->clp;

	list_क्रम_each_entry(stateid, &test_stateid->ts_stateid_list, ts_id_list)
		stateid->ts_id_status =
			nfsd4_validate_stateid(cl, &stateid->ts_id_stateid);

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_मुक्त_lock_stateid(stateid_t *stateid, काष्ठा nfs4_stid *s)
अणु
	काष्ठा nfs4_ol_stateid *stp = खोलोlockstateid(s);
	__be32 ret;

	ret = nfsd4_lock_ol_stateid(stp);
	अगर (ret)
		जाओ out_put_stid;

	ret = check_stateid_generation(stateid, &s->sc_stateid, 1);
	अगर (ret)
		जाओ out;

	ret = nfserr_locks_held;
	अगर (check_क्रम_locks(stp->st_stid.sc_file,
			    lockowner(stp->st_stateowner)))
		जाओ out;

	release_lock_stateid(stp);
	ret = nfs_ok;

out:
	mutex_unlock(&stp->st_mutex);
out_put_stid:
	nfs4_put_stid(s);
	वापस ret;
पूर्ण

__be32
nfsd4_मुक्त_stateid(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_मुक्त_stateid *मुक्त_stateid = &u->मुक्त_stateid;
	stateid_t *stateid = &मुक्त_stateid->fr_stateid;
	काष्ठा nfs4_stid *s;
	काष्ठा nfs4_delegation *dp;
	काष्ठा nfs4_client *cl = cstate->clp;
	__be32 ret = nfserr_bad_stateid;

	spin_lock(&cl->cl_lock);
	s = find_stateid_locked(cl, stateid);
	अगर (!s)
		जाओ out_unlock;
	spin_lock(&s->sc_lock);
	चयन (s->sc_type) अणु
	हाल NFS4_DELEG_STID:
		ret = nfserr_locks_held;
		अवरोध;
	हाल NFS4_OPEN_STID:
		ret = check_stateid_generation(stateid, &s->sc_stateid, 1);
		अगर (ret)
			अवरोध;
		ret = nfserr_locks_held;
		अवरोध;
	हाल NFS4_LOCK_STID:
		spin_unlock(&s->sc_lock);
		refcount_inc(&s->sc_count);
		spin_unlock(&cl->cl_lock);
		ret = nfsd4_मुक्त_lock_stateid(stateid, s);
		जाओ out;
	हाल NFS4_REVOKED_DELEG_STID:
		spin_unlock(&s->sc_lock);
		dp = delegstateid(s);
		list_del_init(&dp->dl_recall_lru);
		spin_unlock(&cl->cl_lock);
		nfs4_put_stid(s);
		ret = nfs_ok;
		जाओ out;
	/* Default falls through and वापसs nfserr_bad_stateid */
	पूर्ण
	spin_unlock(&s->sc_lock);
out_unlock:
	spin_unlock(&cl->cl_lock);
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
setlkflg (पूर्णांक type)
अणु
	वापस (type == NFS4_READW_LT || type == NFS4_READ_LT) ?
		RD_STATE : WR_STATE;
पूर्ण

अटल __be32 nfs4_seqid_op_checks(काष्ठा nfsd4_compound_state *cstate, stateid_t *stateid, u32 seqid, काष्ठा nfs4_ol_stateid *stp)
अणु
	काष्ठा svc_fh *current_fh = &cstate->current_fh;
	काष्ठा nfs4_stateowner *sop = stp->st_stateowner;
	__be32 status;

	status = nfsd4_check_seqid(cstate, sop, seqid);
	अगर (status)
		वापस status;
	status = nfsd4_lock_ol_stateid(stp);
	अगर (status != nfs_ok)
		वापस status;
	status = check_stateid_generation(stateid, &stp->st_stid.sc_stateid, nfsd4_has_session(cstate));
	अगर (status == nfs_ok)
		status = nfs4_check_fh(current_fh, &stp->st_stid);
	अगर (status != nfs_ok)
		mutex_unlock(&stp->st_mutex);
	वापस status;
पूर्ण

/* 
 * Checks क्रम sequence id mutating operations. 
 */
अटल __be32
nfs4_preprocess_seqid_op(काष्ठा nfsd4_compound_state *cstate, u32 seqid,
			 stateid_t *stateid, अक्षर typemask,
			 काष्ठा nfs4_ol_stateid **stpp,
			 काष्ठा nfsd_net *nn)
अणु
	__be32 status;
	काष्ठा nfs4_stid *s;
	काष्ठा nfs4_ol_stateid *stp = शून्य;

	trace_nfsd_preprocess(seqid, stateid);

	*stpp = शून्य;
	status = nfsd4_lookup_stateid(cstate, stateid, typemask, &s, nn);
	अगर (status)
		वापस status;
	stp = खोलोlockstateid(s);
	nfsd4_cstate_assign_replay(cstate, stp->st_stateowner);

	status = nfs4_seqid_op_checks(cstate, stateid, seqid, stp);
	अगर (!status)
		*stpp = stp;
	अन्यथा
		nfs4_put_stid(&stp->st_stid);
	वापस status;
पूर्ण

अटल __be32 nfs4_preprocess_confirmed_seqid_op(काष्ठा nfsd4_compound_state *cstate, u32 seqid,
						 stateid_t *stateid, काष्ठा nfs4_ol_stateid **stpp, काष्ठा nfsd_net *nn)
अणु
	__be32 status;
	काष्ठा nfs4_खोलोowner *oo;
	काष्ठा nfs4_ol_stateid *stp;

	status = nfs4_preprocess_seqid_op(cstate, seqid, stateid,
						NFS4_OPEN_STID, &stp, nn);
	अगर (status)
		वापस status;
	oo = खोलोowner(stp->st_stateowner);
	अगर (!(oo->oo_flags & NFS4_OO_CONFIRMED)) अणु
		mutex_unlock(&stp->st_mutex);
		nfs4_put_stid(&stp->st_stid);
		वापस nfserr_bad_stateid;
	पूर्ण
	*stpp = stp;
	वापस nfs_ok;
पूर्ण

__be32
nfsd4_खोलो_confirm(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_खोलो_confirm *oc = &u->खोलो_confirm;
	__be32 status;
	काष्ठा nfs4_खोलोowner *oo;
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	dprपूर्णांकk("NFSD: nfsd4_open_confirm on file %pd\n",
			cstate->current_fh.fh_dentry);

	status = fh_verअगरy(rqstp, &cstate->current_fh, S_IFREG, 0);
	अगर (status)
		वापस status;

	status = nfs4_preprocess_seqid_op(cstate,
					oc->oc_seqid, &oc->oc_req_stateid,
					NFS4_OPEN_STID, &stp, nn);
	अगर (status)
		जाओ out;
	oo = खोलोowner(stp->st_stateowner);
	status = nfserr_bad_stateid;
	अगर (oo->oo_flags & NFS4_OO_CONFIRMED) अणु
		mutex_unlock(&stp->st_mutex);
		जाओ put_stateid;
	पूर्ण
	oo->oo_flags |= NFS4_OO_CONFIRMED;
	nfs4_inc_and_copy_stateid(&oc->oc_resp_stateid, &stp->st_stid);
	mutex_unlock(&stp->st_mutex);
	trace_nfsd_खोलो_confirm(oc->oc_seqid, &stp->st_stid.sc_stateid);
	nfsd4_client_record_create(oo->oo_owner.so_client);
	status = nfs_ok;
put_stateid:
	nfs4_put_stid(&stp->st_stid);
out:
	nfsd4_bump_seqid(cstate, status);
	वापस status;
पूर्ण

अटल अंतरभूत व्योम nfs4_stateid_करोwngrade_bit(काष्ठा nfs4_ol_stateid *stp, u32 access)
अणु
	अगर (!test_access(access, stp))
		वापस;
	nfs4_file_put_access(stp->st_stid.sc_file, access);
	clear_access(access, stp);
पूर्ण

अटल अंतरभूत व्योम nfs4_stateid_करोwngrade(काष्ठा nfs4_ol_stateid *stp, u32 to_access)
अणु
	चयन (to_access) अणु
	हाल NFS4_SHARE_ACCESS_READ:
		nfs4_stateid_करोwngrade_bit(stp, NFS4_SHARE_ACCESS_WRITE);
		nfs4_stateid_करोwngrade_bit(stp, NFS4_SHARE_ACCESS_BOTH);
		अवरोध;
	हाल NFS4_SHARE_ACCESS_WRITE:
		nfs4_stateid_करोwngrade_bit(stp, NFS4_SHARE_ACCESS_READ);
		nfs4_stateid_करोwngrade_bit(stp, NFS4_SHARE_ACCESS_BOTH);
		अवरोध;
	हाल NFS4_SHARE_ACCESS_BOTH:
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

__be32
nfsd4_खोलो_करोwngrade(काष्ठा svc_rqst *rqstp,
		     काष्ठा nfsd4_compound_state *cstate, जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_खोलो_करोwngrade *od = &u->खोलो_करोwngrade;
	__be32 status;
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	dprपूर्णांकk("NFSD: nfsd4_open_downgrade on file %pd\n", 
			cstate->current_fh.fh_dentry);

	/* We करोn't yet support WANT bits: */
	अगर (od->od_deleg_want)
		dprपूर्णांकk("NFSD: %s: od_deleg_want=0x%x ignored\n", __func__,
			od->od_deleg_want);

	status = nfs4_preprocess_confirmed_seqid_op(cstate, od->od_seqid,
					&od->od_stateid, &stp, nn);
	अगर (status)
		जाओ out; 
	status = nfserr_inval;
	अगर (!test_access(od->od_share_access, stp)) अणु
		dprपूर्णांकk("NFSD: access not a subset of current bitmap: 0x%hhx, input access=%08x\n",
			stp->st_access_bmap, od->od_share_access);
		जाओ put_stateid;
	पूर्ण
	अगर (!test_deny(od->od_share_deny, stp)) अणु
		dprपूर्णांकk("NFSD: deny not a subset of current bitmap: 0x%hhx, input deny=%08x\n",
			stp->st_deny_bmap, od->od_share_deny);
		जाओ put_stateid;
	पूर्ण
	nfs4_stateid_करोwngrade(stp, od->od_share_access);
	reset_जोड़_bmap_deny(od->od_share_deny, stp);
	nfs4_inc_and_copy_stateid(&od->od_stateid, &stp->st_stid);
	status = nfs_ok;
put_stateid:
	mutex_unlock(&stp->st_mutex);
	nfs4_put_stid(&stp->st_stid);
out:
	nfsd4_bump_seqid(cstate, status);
	वापस status;
पूर्ण

अटल व्योम nfsd4_बंद_खोलो_stateid(काष्ठा nfs4_ol_stateid *s)
अणु
	काष्ठा nfs4_client *clp = s->st_stid.sc_client;
	bool unhashed;
	LIST_HEAD(reaplist);

	spin_lock(&clp->cl_lock);
	unhashed = unhash_खोलो_stateid(s, &reaplist);

	अगर (clp->cl_minorversion) अणु
		अगर (unhashed)
			put_ol_stateid_locked(s, &reaplist);
		spin_unlock(&clp->cl_lock);
		मुक्त_ol_stateid_reaplist(&reaplist);
	पूर्ण अन्यथा अणु
		spin_unlock(&clp->cl_lock);
		मुक्त_ol_stateid_reaplist(&reaplist);
		अगर (unhashed)
			move_to_बंद_lru(s, clp->net);
	पूर्ण
पूर्ण

/*
 * nfs4_unlock_state() called after encode
 */
__be32
nfsd4_बंद(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_बंद *बंद = &u->बंद;
	__be32 status;
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprपूर्णांकk("NFSD: nfsd4_close on file %pd\n", 
			cstate->current_fh.fh_dentry);

	status = nfs4_preprocess_seqid_op(cstate, बंद->cl_seqid,
					&बंद->cl_stateid,
					NFS4_OPEN_STID|NFS4_CLOSED_STID,
					&stp, nn);
	nfsd4_bump_seqid(cstate, status);
	अगर (status)
		जाओ out; 

	stp->st_stid.sc_type = NFS4_CLOSED_STID;

	/*
	 * Technically we करोn't _really_ have to increment or copy it, since
	 * it should just be gone after this operation and we clobber the
	 * copied value below, but we जारी to करो so here just to ensure
	 * that racing ops see that there was a state change.
	 */
	nfs4_inc_and_copy_stateid(&बंद->cl_stateid, &stp->st_stid);

	nfsd4_बंद_खोलो_stateid(stp);
	mutex_unlock(&stp->st_mutex);

	/* v4.1+ suggests that we send a special stateid in here, since the
	 * clients should just ignore this anyway. Since this is not useful
	 * क्रम v4.0 clients either, we set it to the special बंद_stateid
	 * universally.
	 *
	 * See RFC5661 section 18.2.4, and RFC7530 section 16.2.5
	 */
	स_नकल(&बंद->cl_stateid, &बंद_stateid, माप(बंद->cl_stateid));

	/* put reference from nfs4_preprocess_seqid_op */
	nfs4_put_stid(&stp->st_stid);
out:
	वापस status;
पूर्ण

__be32
nfsd4_delegवापस(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		  जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_delegवापस *dr = &u->delegवापस;
	काष्ठा nfs4_delegation *dp;
	stateid_t *stateid = &dr->dr_stateid;
	काष्ठा nfs4_stid *s;
	__be32 status;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	अगर ((status = fh_verअगरy(rqstp, &cstate->current_fh, S_IFREG, 0)))
		वापस status;

	status = nfsd4_lookup_stateid(cstate, stateid, NFS4_DELEG_STID, &s, nn);
	अगर (status)
		जाओ out;
	dp = delegstateid(s);
	status = nfsd4_stid_check_stateid_generation(stateid, &dp->dl_stid, nfsd4_has_session(cstate));
	अगर (status)
		जाओ put_stateid;

	destroy_delegation(dp);
put_stateid:
	nfs4_put_stid(&dp->dl_stid);
out:
	वापस status;
पूर्ण

/* last octet in a range */
अटल अंतरभूत u64
last_byte_offset(u64 start, u64 len)
अणु
	u64 end;

	WARN_ON_ONCE(!len);
	end = start + len;
	वापस end > start ? end - 1: NFS4_MAX_UINT64;
पूर्ण

/*
 * TODO: Linux file offsets are _चिन्हित_ 64-bit quantities, which means that
 * we can't properly handle lock requests that go beyond the (2^63 - 1)-th
 * byte, because of sign extension problems.  Since NFSv4 calls क्रम 64-bit
 * locking, this prevents us from being completely protocol-compliant.  The
 * real solution to this problem is to start using अचिन्हित file offsets in
 * the VFS, but this is a very deep change!
 */
अटल अंतरभूत व्योम
nfs4_transक्रमm_lock_offset(काष्ठा file_lock *lock)
अणु
	अगर (lock->fl_start < 0)
		lock->fl_start = OFFSET_MAX;
	अगर (lock->fl_end < 0)
		lock->fl_end = OFFSET_MAX;
पूर्ण

अटल fl_owner_t
nfsd4_fl_get_owner(fl_owner_t owner)
अणु
	काष्ठा nfs4_lockowner *lo = (काष्ठा nfs4_lockowner *)owner;

	nfs4_get_stateowner(&lo->lo_owner);
	वापस owner;
पूर्ण

अटल व्योम
nfsd4_fl_put_owner(fl_owner_t owner)
अणु
	काष्ठा nfs4_lockowner *lo = (काष्ठा nfs4_lockowner *)owner;

	अगर (lo)
		nfs4_put_stateowner(&lo->lo_owner);
पूर्ण

अटल व्योम
nfsd4_lm_notअगरy(काष्ठा file_lock *fl)
अणु
	काष्ठा nfs4_lockowner		*lo = (काष्ठा nfs4_lockowner *)fl->fl_owner;
	काष्ठा net			*net = lo->lo_owner.so_client->net;
	काष्ठा nfsd_net			*nn = net_generic(net, nfsd_net_id);
	काष्ठा nfsd4_blocked_lock	*nbl = container_of(fl,
						काष्ठा nfsd4_blocked_lock, nbl_lock);
	bool queue = false;

	/* An empty list means that something अन्यथा is going to be using it */
	spin_lock(&nn->blocked_locks_lock);
	अगर (!list_empty(&nbl->nbl_list)) अणु
		list_del_init(&nbl->nbl_list);
		list_del_init(&nbl->nbl_lru);
		queue = true;
	पूर्ण
	spin_unlock(&nn->blocked_locks_lock);

	अगर (queue)
		nfsd4_run_cb(&nbl->nbl_cb);
पूर्ण

अटल स्थिर काष्ठा lock_manager_operations nfsd_posix_mng_ops  = अणु
	.lm_notअगरy = nfsd4_lm_notअगरy,
	.lm_get_owner = nfsd4_fl_get_owner,
	.lm_put_owner = nfsd4_fl_put_owner,
पूर्ण;

अटल अंतरभूत व्योम
nfs4_set_lock_denied(काष्ठा file_lock *fl, काष्ठा nfsd4_lock_denied *deny)
अणु
	काष्ठा nfs4_lockowner *lo;

	अगर (fl->fl_lmops == &nfsd_posix_mng_ops) अणु
		lo = (काष्ठा nfs4_lockowner *) fl->fl_owner;
		xdr_netobj_dup(&deny->ld_owner, &lo->lo_owner.so_owner,
						GFP_KERNEL);
		अगर (!deny->ld_owner.data)
			/* We just करोn't care that much */
			जाओ nevermind;
		deny->ld_clientid = lo->lo_owner.so_client->cl_clientid;
	पूर्ण अन्यथा अणु
nevermind:
		deny->ld_owner.len = 0;
		deny->ld_owner.data = शून्य;
		deny->ld_clientid.cl_boot = 0;
		deny->ld_clientid.cl_id = 0;
	पूर्ण
	deny->ld_start = fl->fl_start;
	deny->ld_length = NFS4_MAX_UINT64;
	अगर (fl->fl_end != NFS4_MAX_UINT64)
		deny->ld_length = fl->fl_end - fl->fl_start + 1;        
	deny->ld_type = NFS4_READ_LT;
	अगर (fl->fl_type != F_RDLCK)
		deny->ld_type = NFS4_WRITE_LT;
पूर्ण

अटल काष्ठा nfs4_lockowner *
find_lockowner_str_locked(काष्ठा nfs4_client *clp, काष्ठा xdr_netobj *owner)
अणु
	अचिन्हित पूर्णांक strhashval = ownerstr_hashval(owner);
	काष्ठा nfs4_stateowner *so;

	lockdep_निश्चित_held(&clp->cl_lock);

	list_क्रम_each_entry(so, &clp->cl_ownerstr_hashtbl[strhashval],
			    so_strhash) अणु
		अगर (so->so_is_खोलो_owner)
			जारी;
		अगर (same_owner_str(so, owner))
			वापस lockowner(nfs4_get_stateowner(so));
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_lockowner *
find_lockowner_str(काष्ठा nfs4_client *clp, काष्ठा xdr_netobj *owner)
अणु
	काष्ठा nfs4_lockowner *lo;

	spin_lock(&clp->cl_lock);
	lo = find_lockowner_str_locked(clp, owner);
	spin_unlock(&clp->cl_lock);
	वापस lo;
पूर्ण

अटल व्योम nfs4_unhash_lockowner(काष्ठा nfs4_stateowner *sop)
अणु
	unhash_lockowner_locked(lockowner(sop));
पूर्ण

अटल व्योम nfs4_मुक्त_lockowner(काष्ठा nfs4_stateowner *sop)
अणु
	काष्ठा nfs4_lockowner *lo = lockowner(sop);

	kmem_cache_मुक्त(lockowner_slab, lo);
पूर्ण

अटल स्थिर काष्ठा nfs4_stateowner_operations lockowner_ops = अणु
	.so_unhash =	nfs4_unhash_lockowner,
	.so_मुक्त =	nfs4_मुक्त_lockowner,
पूर्ण;

/*
 * Alloc a lock owner काष्ठाure.
 * Called in nfsd4_lock - thereक्रमe, OPEN and OPEN_CONFIRM (अगर needed) has 
 * occurred. 
 *
 * strhashval = ownerstr_hashval
 */
अटल काष्ठा nfs4_lockowner *
alloc_init_lock_stateowner(अचिन्हित पूर्णांक strhashval, काष्ठा nfs4_client *clp,
			   काष्ठा nfs4_ol_stateid *खोलो_stp,
			   काष्ठा nfsd4_lock *lock)
अणु
	काष्ठा nfs4_lockowner *lo, *ret;

	lo = alloc_stateowner(lockowner_slab, &lock->lk_new_owner, clp);
	अगर (!lo)
		वापस शून्य;
	INIT_LIST_HEAD(&lo->lo_blocked);
	INIT_LIST_HEAD(&lo->lo_owner.so_stateids);
	lo->lo_owner.so_is_खोलो_owner = 0;
	lo->lo_owner.so_seqid = lock->lk_new_lock_seqid;
	lo->lo_owner.so_ops = &lockowner_ops;
	spin_lock(&clp->cl_lock);
	ret = find_lockowner_str_locked(clp, &lock->lk_new_owner);
	अगर (ret == शून्य) अणु
		list_add(&lo->lo_owner.so_strhash,
			 &clp->cl_ownerstr_hashtbl[strhashval]);
		ret = lo;
	पूर्ण अन्यथा
		nfs4_मुक्त_stateowner(&lo->lo_owner);

	spin_unlock(&clp->cl_lock);
	वापस ret;
पूर्ण

अटल काष्ठा nfs4_ol_stateid *
find_lock_stateid(स्थिर काष्ठा nfs4_lockowner *lo,
		  स्थिर काष्ठा nfs4_ol_stateid *ost)
अणु
	काष्ठा nfs4_ol_stateid *lst;

	lockdep_निश्चित_held(&ost->st_stid.sc_client->cl_lock);

	/* If ost is not hashed, ost->st_locks will not be valid */
	अगर (!nfs4_ol_stateid_unhashed(ost))
		list_क्रम_each_entry(lst, &ost->st_locks, st_locks) अणु
			अगर (lst->st_stateowner == &lo->lo_owner) अणु
				refcount_inc(&lst->st_stid.sc_count);
				वापस lst;
			पूर्ण
		पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_ol_stateid *
init_lock_stateid(काष्ठा nfs4_ol_stateid *stp, काष्ठा nfs4_lockowner *lo,
		  काष्ठा nfs4_file *fp, काष्ठा inode *inode,
		  काष्ठा nfs4_ol_stateid *खोलो_stp)
अणु
	काष्ठा nfs4_client *clp = lo->lo_owner.so_client;
	काष्ठा nfs4_ol_stateid *retstp;

	mutex_init(&stp->st_mutex);
	mutex_lock_nested(&stp->st_mutex, OPEN_STATEID_MUTEX);
retry:
	spin_lock(&clp->cl_lock);
	अगर (nfs4_ol_stateid_unhashed(खोलो_stp))
		जाओ out_बंद;
	retstp = find_lock_stateid(lo, खोलो_stp);
	अगर (retstp)
		जाओ out_found;
	refcount_inc(&stp->st_stid.sc_count);
	stp->st_stid.sc_type = NFS4_LOCK_STID;
	stp->st_stateowner = nfs4_get_stateowner(&lo->lo_owner);
	get_nfs4_file(fp);
	stp->st_stid.sc_file = fp;
	stp->st_access_bmap = 0;
	stp->st_deny_bmap = खोलो_stp->st_deny_bmap;
	stp->st_खोलोstp = खोलो_stp;
	spin_lock(&fp->fi_lock);
	list_add(&stp->st_locks, &खोलो_stp->st_locks);
	list_add(&stp->st_perstateowner, &lo->lo_owner.so_stateids);
	list_add(&stp->st_perfile, &fp->fi_stateids);
	spin_unlock(&fp->fi_lock);
	spin_unlock(&clp->cl_lock);
	वापस stp;
out_found:
	spin_unlock(&clp->cl_lock);
	अगर (nfsd4_lock_ol_stateid(retstp) != nfs_ok) अणु
		nfs4_put_stid(&retstp->st_stid);
		जाओ retry;
	पूर्ण
	/* To keep mutex tracking happy */
	mutex_unlock(&stp->st_mutex);
	वापस retstp;
out_बंद:
	spin_unlock(&clp->cl_lock);
	mutex_unlock(&stp->st_mutex);
	वापस शून्य;
पूर्ण

अटल काष्ठा nfs4_ol_stateid *
find_or_create_lock_stateid(काष्ठा nfs4_lockowner *lo, काष्ठा nfs4_file *fi,
			    काष्ठा inode *inode, काष्ठा nfs4_ol_stateid *ost,
			    bool *new)
अणु
	काष्ठा nfs4_stid *ns = शून्य;
	काष्ठा nfs4_ol_stateid *lst;
	काष्ठा nfs4_खोलोowner *oo = खोलोowner(ost->st_stateowner);
	काष्ठा nfs4_client *clp = oo->oo_owner.so_client;

	*new = false;
	spin_lock(&clp->cl_lock);
	lst = find_lock_stateid(lo, ost);
	spin_unlock(&clp->cl_lock);
	अगर (lst != शून्य) अणु
		अगर (nfsd4_lock_ol_stateid(lst) == nfs_ok)
			जाओ out;
		nfs4_put_stid(&lst->st_stid);
	पूर्ण
	ns = nfs4_alloc_stid(clp, stateid_slab, nfs4_मुक्त_lock_stateid);
	अगर (ns == शून्य)
		वापस शून्य;

	lst = init_lock_stateid(खोलोlockstateid(ns), lo, fi, inode, ost);
	अगर (lst == खोलोlockstateid(ns))
		*new = true;
	अन्यथा
		nfs4_put_stid(ns);
out:
	वापस lst;
पूर्ण

अटल पूर्णांक
check_lock_length(u64 offset, u64 length)
अणु
	वापस ((length == 0) || ((length != NFS4_MAX_UINT64) &&
		(length > ~offset)));
पूर्ण

अटल व्योम get_lock_access(काष्ठा nfs4_ol_stateid *lock_stp, u32 access)
अणु
	काष्ठा nfs4_file *fp = lock_stp->st_stid.sc_file;

	lockdep_निश्चित_held(&fp->fi_lock);

	अगर (test_access(access, lock_stp))
		वापस;
	__nfs4_file_get_access(fp, access);
	set_access(access, lock_stp);
पूर्ण

अटल __be32
lookup_or_create_lock_state(काष्ठा nfsd4_compound_state *cstate,
			    काष्ठा nfs4_ol_stateid *ost,
			    काष्ठा nfsd4_lock *lock,
			    काष्ठा nfs4_ol_stateid **plst, bool *new)
अणु
	__be32 status;
	काष्ठा nfs4_file *fi = ost->st_stid.sc_file;
	काष्ठा nfs4_खोलोowner *oo = खोलोowner(ost->st_stateowner);
	काष्ठा nfs4_client *cl = oo->oo_owner.so_client;
	काष्ठा inode *inode = d_inode(cstate->current_fh.fh_dentry);
	काष्ठा nfs4_lockowner *lo;
	काष्ठा nfs4_ol_stateid *lst;
	अचिन्हित पूर्णांक strhashval;

	lo = find_lockowner_str(cl, &lock->lk_new_owner);
	अगर (!lo) अणु
		strhashval = ownerstr_hashval(&lock->lk_new_owner);
		lo = alloc_init_lock_stateowner(strhashval, cl, ost, lock);
		अगर (lo == शून्य)
			वापस nfserr_jukebox;
	पूर्ण अन्यथा अणु
		/* with an existing lockowner, seqids must be the same */
		status = nfserr_bad_seqid;
		अगर (!cstate->minorversion &&
		    lock->lk_new_lock_seqid != lo->lo_owner.so_seqid)
			जाओ out;
	पूर्ण

	lst = find_or_create_lock_stateid(lo, fi, inode, ost, new);
	अगर (lst == शून्य) अणु
		status = nfserr_jukebox;
		जाओ out;
	पूर्ण

	status = nfs_ok;
	*plst = lst;
out:
	nfs4_put_stateowner(&lo->lo_owner);
	वापस status;
पूर्ण

/*
 *  LOCK operation 
 */
__be32
nfsd4_lock(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_lock *lock = &u->lock;
	काष्ठा nfs4_खोलोowner *खोलो_sop = शून्य;
	काष्ठा nfs4_lockowner *lock_sop = शून्य;
	काष्ठा nfs4_ol_stateid *lock_stp = शून्य;
	काष्ठा nfs4_ol_stateid *खोलो_stp = शून्य;
	काष्ठा nfs4_file *fp;
	काष्ठा nfsd_file *nf = शून्य;
	काष्ठा nfsd4_blocked_lock *nbl = शून्य;
	काष्ठा file_lock *file_lock = शून्य;
	काष्ठा file_lock *conflock = शून्य;
	__be32 status = 0;
	पूर्णांक lkflg;
	पूर्णांक err;
	bool new = false;
	अचिन्हित अक्षर fl_type;
	अचिन्हित पूर्णांक fl_flags = FL_POSIX;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprपूर्णांकk("NFSD: nfsd4_lock: start=%Ld length=%Ld\n",
		(दीर्घ दीर्घ) lock->lk_offset,
		(दीर्घ दीर्घ) lock->lk_length);

	अगर (check_lock_length(lock->lk_offset, lock->lk_length))
		 वापस nfserr_inval;

	अगर ((status = fh_verअगरy(rqstp, &cstate->current_fh,
				S_IFREG, NFSD_MAY_LOCK))) अणु
		dprपूर्णांकk("NFSD: nfsd4_lock: permission denied!\n");
		वापस status;
	पूर्ण

	अगर (lock->lk_is_new) अणु
		अगर (nfsd4_has_session(cstate))
			/* See rfc 5661 18.10.3: given clientid is ignored: */
			स_नकल(&lock->lk_new_clientid,
				&cstate->clp->cl_clientid,
				माप(clientid_t));

		/* validate and update खोलो stateid and खोलो seqid */
		status = nfs4_preprocess_confirmed_seqid_op(cstate,
				        lock->lk_new_खोलो_seqid,
		                        &lock->lk_new_खोलो_stateid,
					&खोलो_stp, nn);
		अगर (status)
			जाओ out;
		mutex_unlock(&खोलो_stp->st_mutex);
		खोलो_sop = खोलोowner(खोलो_stp->st_stateowner);
		status = nfserr_bad_stateid;
		अगर (!same_clid(&खोलो_sop->oo_owner.so_client->cl_clientid,
						&lock->lk_new_clientid))
			जाओ out;
		status = lookup_or_create_lock_state(cstate, खोलो_stp, lock,
							&lock_stp, &new);
	पूर्ण अन्यथा अणु
		status = nfs4_preprocess_seqid_op(cstate,
				       lock->lk_old_lock_seqid,
				       &lock->lk_old_lock_stateid,
				       NFS4_LOCK_STID, &lock_stp, nn);
	पूर्ण
	अगर (status)
		जाओ out;
	lock_sop = lockowner(lock_stp->st_stateowner);

	lkflg = setlkflg(lock->lk_type);
	status = nfs4_check_खोलोmode(lock_stp, lkflg);
	अगर (status)
		जाओ out;

	status = nfserr_grace;
	अगर (locks_in_grace(net) && !lock->lk_reclaim)
		जाओ out;
	status = nfserr_no_grace;
	अगर (!locks_in_grace(net) && lock->lk_reclaim)
		जाओ out;

	fp = lock_stp->st_stid.sc_file;
	चयन (lock->lk_type) अणु
		हाल NFS4_READW_LT:
			अगर (nfsd4_has_session(cstate))
				fl_flags |= FL_SLEEP;
			fallthrough;
		हाल NFS4_READ_LT:
			spin_lock(&fp->fi_lock);
			nf = find_पढ़ोable_file_locked(fp);
			अगर (nf)
				get_lock_access(lock_stp, NFS4_SHARE_ACCESS_READ);
			spin_unlock(&fp->fi_lock);
			fl_type = F_RDLCK;
			अवरोध;
		हाल NFS4_WRITEW_LT:
			अगर (nfsd4_has_session(cstate))
				fl_flags |= FL_SLEEP;
			fallthrough;
		हाल NFS4_WRITE_LT:
			spin_lock(&fp->fi_lock);
			nf = find_ग_लिखोable_file_locked(fp);
			अगर (nf)
				get_lock_access(lock_stp, NFS4_SHARE_ACCESS_WRITE);
			spin_unlock(&fp->fi_lock);
			fl_type = F_WRLCK;
			अवरोध;
		शेष:
			status = nfserr_inval;
		जाओ out;
	पूर्ण

	अगर (!nf) अणु
		status = nfserr_खोलोmode;
		जाओ out;
	पूर्ण

	nbl = find_or_allocate_block(lock_sop, &fp->fi_fhandle, nn);
	अगर (!nbl) अणु
		dprपूर्णांकk("NFSD: %s: unable to allocate block!\n", __func__);
		status = nfserr_jukebox;
		जाओ out;
	पूर्ण

	file_lock = &nbl->nbl_lock;
	file_lock->fl_type = fl_type;
	file_lock->fl_owner = (fl_owner_t)lockowner(nfs4_get_stateowner(&lock_sop->lo_owner));
	file_lock->fl_pid = current->tgid;
	file_lock->fl_file = nf->nf_file;
	file_lock->fl_flags = fl_flags;
	file_lock->fl_lmops = &nfsd_posix_mng_ops;
	file_lock->fl_start = lock->lk_offset;
	file_lock->fl_end = last_byte_offset(lock->lk_offset, lock->lk_length);
	nfs4_transक्रमm_lock_offset(file_lock);

	conflock = locks_alloc_lock();
	अगर (!conflock) अणु
		dprपूर्णांकk("NFSD: %s: unable to allocate lock!\n", __func__);
		status = nfserr_jukebox;
		जाओ out;
	पूर्ण

	अगर (fl_flags & FL_SLEEP) अणु
		nbl->nbl_समय = kसमय_get_bootसमय_seconds();
		spin_lock(&nn->blocked_locks_lock);
		list_add_tail(&nbl->nbl_list, &lock_sop->lo_blocked);
		list_add_tail(&nbl->nbl_lru, &nn->blocked_locks_lru);
		spin_unlock(&nn->blocked_locks_lock);
	पूर्ण

	err = vfs_lock_file(nf->nf_file, F_SETLK, file_lock, conflock);
	चयन (err) अणु
	हाल 0: /* success! */
		nfs4_inc_and_copy_stateid(&lock->lk_resp_stateid, &lock_stp->st_stid);
		status = 0;
		अगर (lock->lk_reclaim)
			nn->somebody_reclaimed = true;
		अवरोध;
	हाल खाता_LOCK_DEFERRED:
		nbl = शून्य;
		fallthrough;
	हाल -EAGAIN:		/* conflock holds conflicting lock */
		status = nfserr_denied;
		dprपूर्णांकk("NFSD: nfsd4_lock: conflicting lock found!\n");
		nfs4_set_lock_denied(conflock, &lock->lk_denied);
		अवरोध;
	हाल -EDEADLK:
		status = nfserr_deadlock;
		अवरोध;
	शेष:
		dprपूर्णांकk("NFSD: nfsd4_lock: vfs_lock_file() failed! status %d\n",err);
		status = nfsत्रुटि_सं(err);
		अवरोध;
	पूर्ण
out:
	अगर (nbl) अणु
		/* dequeue it अगर we queued it beक्रमe */
		अगर (fl_flags & FL_SLEEP) अणु
			spin_lock(&nn->blocked_locks_lock);
			list_del_init(&nbl->nbl_list);
			list_del_init(&nbl->nbl_lru);
			spin_unlock(&nn->blocked_locks_lock);
		पूर्ण
		मुक्त_blocked_lock(nbl);
	पूर्ण
	अगर (nf)
		nfsd_file_put(nf);
	अगर (lock_stp) अणु
		/* Bump seqid manually अगर the 4.0 replay owner is खोलोowner */
		अगर (cstate->replay_owner &&
		    cstate->replay_owner != &lock_sop->lo_owner &&
		    seqid_mutating_err(ntohl(status)))
			lock_sop->lo_owner.so_seqid++;

		/*
		 * If this is a new, never-beक्रमe-used stateid, and we are
		 * वापसing an error, then just go ahead and release it.
		 */
		अगर (status && new)
			release_lock_stateid(lock_stp);

		mutex_unlock(&lock_stp->st_mutex);

		nfs4_put_stid(&lock_stp->st_stid);
	पूर्ण
	अगर (खोलो_stp)
		nfs4_put_stid(&खोलो_stp->st_stid);
	nfsd4_bump_seqid(cstate, status);
	अगर (conflock)
		locks_मुक्त_lock(conflock);
	वापस status;
पूर्ण

/*
 * The NFSv4 spec allows a client to करो a LOCKT without holding an OPEN,
 * so we करो a temporary खोलो here just to get an खोलो file to pass to
 * vfs_test_lock.  (Arguably perhaps test_lock should be करोne with an
 * inode operation.)
 */
अटल __be32 nfsd_test_lock(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, काष्ठा file_lock *lock)
अणु
	काष्ठा nfsd_file *nf;
	__be32 err;

	err = nfsd_file_acquire(rqstp, fhp, NFSD_MAY_READ, &nf);
	अगर (err)
		वापस err;
	fh_lock(fhp); /* to block new leases till after test_lock: */
	err = nfsत्रुटि_सं(nfsd_खोलो_अवरोध_lease(fhp->fh_dentry->d_inode,
							NFSD_MAY_READ));
	अगर (err)
		जाओ out;
	err = nfsत्रुटि_सं(vfs_test_lock(nf->nf_file, lock));
out:
	fh_unlock(fhp);
	nfsd_file_put(nf);
	वापस err;
पूर्ण

/*
 * LOCKT operation
 */
__be32
nfsd4_lockt(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	    जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_lockt *lockt = &u->lockt;
	काष्ठा file_lock *file_lock = शून्य;
	काष्ठा nfs4_lockowner *lo = शून्य;
	__be32 status;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	अगर (locks_in_grace(SVC_NET(rqstp)))
		वापस nfserr_grace;

	अगर (check_lock_length(lockt->lt_offset, lockt->lt_length))
		 वापस nfserr_inval;

	अगर (!nfsd4_has_session(cstate)) अणु
		status = set_client(&lockt->lt_clientid, cstate, nn);
		अगर (status)
			जाओ out;
	पूर्ण

	अगर ((status = fh_verअगरy(rqstp, &cstate->current_fh, S_IFREG, 0)))
		जाओ out;

	file_lock = locks_alloc_lock();
	अगर (!file_lock) अणु
		dprपूर्णांकk("NFSD: %s: unable to allocate lock!\n", __func__);
		status = nfserr_jukebox;
		जाओ out;
	पूर्ण

	चयन (lockt->lt_type) अणु
		हाल NFS4_READ_LT:
		हाल NFS4_READW_LT:
			file_lock->fl_type = F_RDLCK;
			अवरोध;
		हाल NFS4_WRITE_LT:
		हाल NFS4_WRITEW_LT:
			file_lock->fl_type = F_WRLCK;
			अवरोध;
		शेष:
			dprपूर्णांकk("NFSD: nfs4_lockt: bad lock type!\n");
			status = nfserr_inval;
			जाओ out;
	पूर्ण

	lo = find_lockowner_str(cstate->clp, &lockt->lt_owner);
	अगर (lo)
		file_lock->fl_owner = (fl_owner_t)lo;
	file_lock->fl_pid = current->tgid;
	file_lock->fl_flags = FL_POSIX;

	file_lock->fl_start = lockt->lt_offset;
	file_lock->fl_end = last_byte_offset(lockt->lt_offset, lockt->lt_length);

	nfs4_transक्रमm_lock_offset(file_lock);

	status = nfsd_test_lock(rqstp, &cstate->current_fh, file_lock);
	अगर (status)
		जाओ out;

	अगर (file_lock->fl_type != F_UNLCK) अणु
		status = nfserr_denied;
		nfs4_set_lock_denied(file_lock, &lockt->lt_denied);
	पूर्ण
out:
	अगर (lo)
		nfs4_put_stateowner(&lo->lo_owner);
	अगर (file_lock)
		locks_मुक्त_lock(file_lock);
	वापस status;
पूर्ण

__be32
nfsd4_locku(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	    जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_locku *locku = &u->locku;
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा nfsd_file *nf = शून्य;
	काष्ठा file_lock *file_lock = शून्य;
	__be32 status;
	पूर्णांक err;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	dprपूर्णांकk("NFSD: nfsd4_locku: start=%Ld length=%Ld\n",
		(दीर्घ दीर्घ) locku->lu_offset,
		(दीर्घ दीर्घ) locku->lu_length);

	अगर (check_lock_length(locku->lu_offset, locku->lu_length))
		 वापस nfserr_inval;

	status = nfs4_preprocess_seqid_op(cstate, locku->lu_seqid,
					&locku->lu_stateid, NFS4_LOCK_STID,
					&stp, nn);
	अगर (status)
		जाओ out;
	nf = find_any_file(stp->st_stid.sc_file);
	अगर (!nf) अणु
		status = nfserr_lock_range;
		जाओ put_stateid;
	पूर्ण
	file_lock = locks_alloc_lock();
	अगर (!file_lock) अणु
		dprपूर्णांकk("NFSD: %s: unable to allocate lock!\n", __func__);
		status = nfserr_jukebox;
		जाओ put_file;
	पूर्ण

	file_lock->fl_type = F_UNLCK;
	file_lock->fl_owner = (fl_owner_t)lockowner(nfs4_get_stateowner(stp->st_stateowner));
	file_lock->fl_pid = current->tgid;
	file_lock->fl_file = nf->nf_file;
	file_lock->fl_flags = FL_POSIX;
	file_lock->fl_lmops = &nfsd_posix_mng_ops;
	file_lock->fl_start = locku->lu_offset;

	file_lock->fl_end = last_byte_offset(locku->lu_offset,
						locku->lu_length);
	nfs4_transक्रमm_lock_offset(file_lock);

	err = vfs_lock_file(nf->nf_file, F_SETLK, file_lock, शून्य);
	अगर (err) अणु
		dprपूर्णांकk("NFSD: nfs4_locku: vfs_lock_file failed!\n");
		जाओ out_nfserr;
	पूर्ण
	nfs4_inc_and_copy_stateid(&locku->lu_stateid, &stp->st_stid);
put_file:
	nfsd_file_put(nf);
put_stateid:
	mutex_unlock(&stp->st_mutex);
	nfs4_put_stid(&stp->st_stid);
out:
	nfsd4_bump_seqid(cstate, status);
	अगर (file_lock)
		locks_मुक्त_lock(file_lock);
	वापस status;

out_nfserr:
	status = nfsत्रुटि_सं(err);
	जाओ put_file;
पूर्ण

/*
 * वापसs
 * 	true:  locks held by lockowner
 * 	false: no locks held by lockowner
 */
अटल bool
check_क्रम_locks(काष्ठा nfs4_file *fp, काष्ठा nfs4_lockowner *lowner)
अणु
	काष्ठा file_lock *fl;
	पूर्णांक status = false;
	काष्ठा nfsd_file *nf = find_any_file(fp);
	काष्ठा inode *inode;
	काष्ठा file_lock_context *flctx;

	अगर (!nf) अणु
		/* Any valid lock stateid should have some sort of access */
		WARN_ON_ONCE(1);
		वापस status;
	पूर्ण

	inode = locks_inode(nf->nf_file);
	flctx = inode->i_flctx;

	अगर (flctx && !list_empty_careful(&flctx->flc_posix)) अणु
		spin_lock(&flctx->flc_lock);
		list_क्रम_each_entry(fl, &flctx->flc_posix, fl_list) अणु
			अगर (fl->fl_owner == (fl_owner_t)lowner) अणु
				status = true;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&flctx->flc_lock);
	पूर्ण
	nfsd_file_put(nf);
	वापस status;
पूर्ण

__be32
nfsd4_release_lockowner(काष्ठा svc_rqst *rqstp,
			काष्ठा nfsd4_compound_state *cstate,
			जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_release_lockowner *rlockowner = &u->release_lockowner;
	clientid_t *clid = &rlockowner->rl_clientid;
	काष्ठा nfs4_stateowner *sop;
	काष्ठा nfs4_lockowner *lo = शून्य;
	काष्ठा nfs4_ol_stateid *stp;
	काष्ठा xdr_netobj *owner = &rlockowner->rl_owner;
	अचिन्हित पूर्णांक hashval = ownerstr_hashval(owner);
	__be32 status;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	काष्ठा nfs4_client *clp;
	LIST_HEAD (reaplist);

	dprपूर्णांकk("nfsd4_release_lockowner clientid: (%08x/%08x):\n",
		clid->cl_boot, clid->cl_id);

	status = set_client(clid, cstate, nn);
	अगर (status)
		वापस status;

	clp = cstate->clp;
	/* Find the matching lock stateowner */
	spin_lock(&clp->cl_lock);
	list_क्रम_each_entry(sop, &clp->cl_ownerstr_hashtbl[hashval],
			    so_strhash) अणु

		अगर (sop->so_is_खोलो_owner || !same_owner_str(sop, owner))
			जारी;

		/* see अगर there are still any locks associated with it */
		lo = lockowner(sop);
		list_क्रम_each_entry(stp, &sop->so_stateids, st_perstateowner) अणु
			अगर (check_क्रम_locks(stp->st_stid.sc_file, lo)) अणु
				status = nfserr_locks_held;
				spin_unlock(&clp->cl_lock);
				वापस status;
			पूर्ण
		पूर्ण

		nfs4_get_stateowner(sop);
		अवरोध;
	पूर्ण
	अगर (!lo) अणु
		spin_unlock(&clp->cl_lock);
		वापस status;
	पूर्ण

	unhash_lockowner_locked(lo);
	जबतक (!list_empty(&lo->lo_owner.so_stateids)) अणु
		stp = list_first_entry(&lo->lo_owner.so_stateids,
				       काष्ठा nfs4_ol_stateid,
				       st_perstateowner);
		WARN_ON(!unhash_lock_stateid(stp));
		put_ol_stateid_locked(stp, &reaplist);
	पूर्ण
	spin_unlock(&clp->cl_lock);
	मुक्त_ol_stateid_reaplist(&reaplist);
	हटाओ_blocked_locks(lo);
	nfs4_put_stateowner(&lo->lo_owner);

	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा nfs4_client_reclaim *
alloc_reclaim(व्योम)
अणु
	वापस kदो_स्मृति(माप(काष्ठा nfs4_client_reclaim), GFP_KERNEL);
पूर्ण

bool
nfs4_has_reclaimed_state(काष्ठा xdr_netobj name, काष्ठा nfsd_net *nn)
अणु
	काष्ठा nfs4_client_reclaim *crp;

	crp = nfsd4_find_reclaim_client(name, nn);
	वापस (crp && crp->cr_clp);
पूर्ण

/*
 * failure => all reset bets are off, nfserr_no_grace...
 *
 * The caller is responsible क्रम मुक्तing name.data अगर शून्य is वापसed (it
 * will be मुक्तd in nfs4_हटाओ_reclaim_record in the normal हाल).
 */
काष्ठा nfs4_client_reclaim *
nfs4_client_to_reclaim(काष्ठा xdr_netobj name, काष्ठा xdr_netobj princhash,
		काष्ठा nfsd_net *nn)
अणु
	अचिन्हित पूर्णांक strhashval;
	काष्ठा nfs4_client_reclaim *crp;

	trace_nfsd_clid_reclaim(nn, name.len, name.data);
	crp = alloc_reclaim();
	अगर (crp) अणु
		strhashval = clientstr_hashval(name);
		INIT_LIST_HEAD(&crp->cr_strhash);
		list_add(&crp->cr_strhash, &nn->reclaim_str_hashtbl[strhashval]);
		crp->cr_name.data = name.data;
		crp->cr_name.len = name.len;
		crp->cr_princhash.data = princhash.data;
		crp->cr_princhash.len = princhash.len;
		crp->cr_clp = शून्य;
		nn->reclaim_str_hashtbl_size++;
	पूर्ण
	वापस crp;
पूर्ण

व्योम
nfs4_हटाओ_reclaim_record(काष्ठा nfs4_client_reclaim *crp, काष्ठा nfsd_net *nn)
अणु
	list_del(&crp->cr_strhash);
	kमुक्त(crp->cr_name.data);
	kमुक्त(crp->cr_princhash.data);
	kमुक्त(crp);
	nn->reclaim_str_hashtbl_size--;
पूर्ण

व्योम
nfs4_release_reclaim(काष्ठा nfsd_net *nn)
अणु
	काष्ठा nfs4_client_reclaim *crp = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < CLIENT_HASH_SIZE; i++) अणु
		जबतक (!list_empty(&nn->reclaim_str_hashtbl[i])) अणु
			crp = list_entry(nn->reclaim_str_hashtbl[i].next,
			                काष्ठा nfs4_client_reclaim, cr_strhash);
			nfs4_हटाओ_reclaim_record(crp, nn);
		पूर्ण
	पूर्ण
	WARN_ON_ONCE(nn->reclaim_str_hashtbl_size);
पूर्ण

/*
 * called from OPEN, CLAIM_PREVIOUS with a new clientid. */
काष्ठा nfs4_client_reclaim *
nfsd4_find_reclaim_client(काष्ठा xdr_netobj name, काष्ठा nfsd_net *nn)
अणु
	अचिन्हित पूर्णांक strhashval;
	काष्ठा nfs4_client_reclaim *crp = शून्य;

	trace_nfsd_clid_find(nn, name.len, name.data);

	strhashval = clientstr_hashval(name);
	list_क्रम_each_entry(crp, &nn->reclaim_str_hashtbl[strhashval], cr_strhash) अणु
		अगर (compare_blob(&crp->cr_name, &name) == 0) अणु
			वापस crp;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

__be32
nfs4_check_खोलो_reclaim(काष्ठा nfs4_client *clp)
अणु
	अगर (test_bit(NFSD4_CLIENT_RECLAIM_COMPLETE, &clp->cl_flags))
		वापस nfserr_no_grace;

	अगर (nfsd4_client_record_check(clp))
		वापस nfserr_reclaim_bad;

	वापस nfs_ok;
पूर्ण

/*
 * Since the lअगरeसमय of a delegation isn't limited to that of an खोलो, a
 * client may quite reasonably hang on to a delegation as दीर्घ as it has
 * the inode cached.  This becomes an obvious problem the first समय a
 * client's inode cache approaches the size of the server's total memory.
 *
 * For now we aव्योम this problem by imposing a hard limit on the number
 * of delegations, which varies according to the server's memory size.
 */
अटल व्योम
set_max_delegations(व्योम)
अणु
	/*
	 * Allow at most 4 delegations per megabyte of RAM.  Quick
	 * estimates suggest that in the worst हाल (where every delegation
	 * is क्रम a dअगरferent inode), a delegation could take about 1.5K,
	 * giving a worst हाल usage of about 6% of memory.
	 */
	max_delegations = nr_मुक्त_buffer_pages() >> (20 - 2 - PAGE_SHIFT);
पूर्ण

अटल पूर्णांक nfs4_state_create_net(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	पूर्णांक i;

	nn->conf_id_hashtbl = kदो_स्मृति_array(CLIENT_HASH_SIZE,
					    माप(काष्ठा list_head),
					    GFP_KERNEL);
	अगर (!nn->conf_id_hashtbl)
		जाओ err;
	nn->unconf_id_hashtbl = kदो_स्मृति_array(CLIENT_HASH_SIZE,
					      माप(काष्ठा list_head),
					      GFP_KERNEL);
	अगर (!nn->unconf_id_hashtbl)
		जाओ err_unconf_id;
	nn->sessionid_hashtbl = kदो_स्मृति_array(SESSION_HASH_SIZE,
					      माप(काष्ठा list_head),
					      GFP_KERNEL);
	अगर (!nn->sessionid_hashtbl)
		जाओ err_sessionid;

	क्रम (i = 0; i < CLIENT_HASH_SIZE; i++) अणु
		INIT_LIST_HEAD(&nn->conf_id_hashtbl[i]);
		INIT_LIST_HEAD(&nn->unconf_id_hashtbl[i]);
	पूर्ण
	क्रम (i = 0; i < SESSION_HASH_SIZE; i++)
		INIT_LIST_HEAD(&nn->sessionid_hashtbl[i]);
	nn->conf_name_tree = RB_ROOT;
	nn->unconf_name_tree = RB_ROOT;
	nn->boot_समय = kसमय_get_real_seconds();
	nn->grace_ended = false;
	nn->nfsd4_manager.block_खोलोs = true;
	INIT_LIST_HEAD(&nn->nfsd4_manager.list);
	INIT_LIST_HEAD(&nn->client_lru);
	INIT_LIST_HEAD(&nn->बंद_lru);
	INIT_LIST_HEAD(&nn->del_recall_lru);
	spin_lock_init(&nn->client_lock);
	spin_lock_init(&nn->s2s_cp_lock);
	idr_init(&nn->s2s_cp_stateids);

	spin_lock_init(&nn->blocked_locks_lock);
	INIT_LIST_HEAD(&nn->blocked_locks_lru);

	INIT_DELAYED_WORK(&nn->laundromat_work, laundromat_मुख्य);
	get_net(net);

	वापस 0;

err_sessionid:
	kमुक्त(nn->unconf_id_hashtbl);
err_unconf_id:
	kमुक्त(nn->conf_id_hashtbl);
err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम
nfs4_state_destroy_net(काष्ठा net *net)
अणु
	पूर्णांक i;
	काष्ठा nfs4_client *clp = शून्य;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	क्रम (i = 0; i < CLIENT_HASH_SIZE; i++) अणु
		जबतक (!list_empty(&nn->conf_id_hashtbl[i])) अणु
			clp = list_entry(nn->conf_id_hashtbl[i].next, काष्ठा nfs4_client, cl_idhash);
			destroy_client(clp);
		पूर्ण
	पूर्ण

	WARN_ON(!list_empty(&nn->blocked_locks_lru));

	क्रम (i = 0; i < CLIENT_HASH_SIZE; i++) अणु
		जबतक (!list_empty(&nn->unconf_id_hashtbl[i])) अणु
			clp = list_entry(nn->unconf_id_hashtbl[i].next, काष्ठा nfs4_client, cl_idhash);
			destroy_client(clp);
		पूर्ण
	पूर्ण

	kमुक्त(nn->sessionid_hashtbl);
	kमुक्त(nn->unconf_id_hashtbl);
	kमुक्त(nn->conf_id_hashtbl);
	put_net(net);
पूर्ण

पूर्णांक
nfs4_state_start_net(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	पूर्णांक ret;

	ret = nfs4_state_create_net(net);
	अगर (ret)
		वापस ret;
	locks_start_grace(net, &nn->nfsd4_manager);
	nfsd4_client_tracking_init(net);
	अगर (nn->track_reclaim_completes && nn->reclaim_str_hashtbl_size == 0)
		जाओ skip_grace;
	prपूर्णांकk(KERN_INFO "NFSD: starting %lld-second grace period (net %x)\n",
	       nn->nfsd4_grace, net->ns.inum);
	trace_nfsd_grace_start(nn);
	queue_delayed_work(laundry_wq, &nn->laundromat_work, nn->nfsd4_grace * HZ);
	वापस 0;

skip_grace:
	prपूर्णांकk(KERN_INFO "NFSD: no clients to reclaim, skipping NFSv4 grace period (net %x)\n",
			net->ns.inum);
	queue_delayed_work(laundry_wq, &nn->laundromat_work, nn->nfsd4_lease * HZ);
	nfsd4_end_grace(nn);
	वापस 0;
पूर्ण

/* initialization to perक्रमm when the nfsd service is started: */

पूर्णांक
nfs4_state_start(व्योम)
अणु
	पूर्णांक ret;

	laundry_wq = alloc_workqueue("%s", WQ_UNBOUND, 0, "nfsd4");
	अगर (laundry_wq == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ret = nfsd4_create_callback_queue();
	अगर (ret)
		जाओ out_मुक्त_laundry;

	set_max_delegations();
	वापस 0;

out_मुक्त_laundry:
	destroy_workqueue(laundry_wq);
out:
	वापस ret;
पूर्ण

व्योम
nfs4_state_shutकरोwn_net(काष्ठा net *net)
अणु
	काष्ठा nfs4_delegation *dp = शून्य;
	काष्ठा list_head *pos, *next, reaplist;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	cancel_delayed_work_sync(&nn->laundromat_work);
	locks_end_grace(&nn->nfsd4_manager);

	INIT_LIST_HEAD(&reaplist);
	spin_lock(&state_lock);
	list_क्रम_each_safe(pos, next, &nn->del_recall_lru) अणु
		dp = list_entry (pos, काष्ठा nfs4_delegation, dl_recall_lru);
		WARN_ON(!unhash_delegation_locked(dp));
		list_add(&dp->dl_recall_lru, &reaplist);
	पूर्ण
	spin_unlock(&state_lock);
	list_क्रम_each_safe(pos, next, &reaplist) अणु
		dp = list_entry (pos, काष्ठा nfs4_delegation, dl_recall_lru);
		list_del_init(&dp->dl_recall_lru);
		destroy_unhashed_deleg(dp);
	पूर्ण

	nfsd4_client_tracking_निकास(net);
	nfs4_state_destroy_net(net);
पूर्ण

व्योम
nfs4_state_shutकरोwn(व्योम)
अणु
	destroy_workqueue(laundry_wq);
	nfsd4_destroy_callback_queue();
पूर्ण

अटल व्योम
get_stateid(काष्ठा nfsd4_compound_state *cstate, stateid_t *stateid)
अणु
	अगर (HAS_CSTATE_FLAG(cstate, CURRENT_STATE_ID_FLAG) &&
	    CURRENT_STATEID(stateid))
		स_नकल(stateid, &cstate->current_stateid, माप(stateid_t));
पूर्ण

अटल व्योम
put_stateid(काष्ठा nfsd4_compound_state *cstate, stateid_t *stateid)
अणु
	अगर (cstate->minorversion) अणु
		स_नकल(&cstate->current_stateid, stateid, माप(stateid_t));
		SET_CSTATE_FLAG(cstate, CURRENT_STATE_ID_FLAG);
	पूर्ण
पूर्ण

व्योम
clear_current_stateid(काष्ठा nfsd4_compound_state *cstate)
अणु
	CLEAR_CSTATE_FLAG(cstate, CURRENT_STATE_ID_FLAG);
पूर्ण

/*
 * functions to set current state id
 */
व्योम
nfsd4_set_खोलोकरोwngradestateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	put_stateid(cstate, &u->खोलो_करोwngrade.od_stateid);
पूर्ण

व्योम
nfsd4_set_खोलोstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	put_stateid(cstate, &u->खोलो.op_stateid);
पूर्ण

व्योम
nfsd4_set_बंदstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	put_stateid(cstate, &u->बंद.cl_stateid);
पूर्ण

व्योम
nfsd4_set_lockstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	put_stateid(cstate, &u->lock.lk_resp_stateid);
पूर्ण

/*
 * functions to consume current state id
 */

व्योम
nfsd4_get_खोलोकरोwngradestateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->खोलो_करोwngrade.od_stateid);
पूर्ण

व्योम
nfsd4_get_delegवापसstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->delegवापस.dr_stateid);
पूर्ण

व्योम
nfsd4_get_मुक्तstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->मुक्त_stateid.fr_stateid);
पूर्ण

व्योम
nfsd4_get_setattrstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->setattr.sa_stateid);
पूर्ण

व्योम
nfsd4_get_बंदstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->बंद.cl_stateid);
पूर्ण

व्योम
nfsd4_get_lockustateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->locku.lu_stateid);
पूर्ण

व्योम
nfsd4_get_पढ़ोstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->पढ़ो.rd_stateid);
पूर्ण

व्योम
nfsd4_get_ग_लिखोstateid(काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	get_stateid(cstate, &u->ग_लिखो.wr_stateid);
पूर्ण
