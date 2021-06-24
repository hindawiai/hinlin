<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmast.c
 *
 * AST and BAST functionality क्रम local and remote nodes
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */


#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/socket.h>
#समावेश <linux/inet.h>
#समावेश <linux/spinlock.h>


#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"

#घोषणा MLOG_MASK_PREFIX ML_DLM
#समावेश "../cluster/masklog.h"

अटल व्योम dlm_update_lvb(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
			   काष्ठा dlm_lock *lock);
अटल पूर्णांक dlm_should_cancel_bast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock);

/* Should be called as an ast माला_लो queued to see अगर the new
 * lock level will obsolete a pending bast.
 * For example, अगर dlm_thपढ़ो queued a bast क्रम an EX lock that
 * was blocking another EX, but beक्रमe sending the bast the
 * lock owner करोwnconverted to NL, the bast is now obsolete.
 * Only the ast should be sent.
 * This is needed because the lock and convert paths can queue
 * asts out-of-band (not रुकोing क्रम dlm_thपढ़ो) in order to
 * allow क्रम LKM_NOQUEUE to get immediate responses. */
अटल पूर्णांक dlm_should_cancel_bast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock)
अणु
	निश्चित_spin_locked(&dlm->ast_lock);
	निश्चित_spin_locked(&lock->spinlock);

	अगर (lock->ml.highest_blocked == LKM_IVMODE)
		वापस 0;
	BUG_ON(lock->ml.highest_blocked == LKM_NLMODE);

	अगर (lock->bast_pending &&
	    list_empty(&lock->bast_list))
		/* old bast alपढ़ोy sent, ok */
		वापस 0;

	अगर (lock->ml.type == LKM_EXMODE)
		/* EX blocks anything left, any bast still valid */
		वापस 0;
	अन्यथा अगर (lock->ml.type == LKM_NLMODE)
		/* NL blocks nothing, no reason to send any bast, cancel it */
		वापस 1;
	अन्यथा अगर (lock->ml.highest_blocked != LKM_EXMODE)
		/* PR only blocks EX */
		वापस 1;

	वापस 0;
पूर्ण

व्योम __dlm_queue_ast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock)
अणु
	काष्ठा dlm_lock_resource *res;

	BUG_ON(!dlm);
	BUG_ON(!lock);

	res = lock->lockres;

	निश्चित_spin_locked(&dlm->ast_lock);

	अगर (!list_empty(&lock->ast_list)) अणु
		mlog(ML_ERROR, "%s: res %.*s, lock %u:%llu, "
		     "AST list not empty, pending %d, newlevel %d\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     lock->ast_pending, lock->ml.type);
		BUG();
	पूर्ण
	अगर (lock->ast_pending)
		mlog(0, "%s: res %.*s, lock %u:%llu, AST getting flushed\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));

	/* putting lock on list, add a ref */
	dlm_lock_get(lock);
	spin_lock(&lock->spinlock);

	/* check to see अगर this ast obsoletes the bast */
	अगर (dlm_should_cancel_bast(dlm, lock)) अणु
		mlog(0, "%s: res %.*s, lock %u:%llu, Cancelling BAST\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));
		lock->bast_pending = 0;
		list_del_init(&lock->bast_list);
		lock->ml.highest_blocked = LKM_IVMODE;
		/* removing lock from list, हटाओ a ref.  guaranteed
		 * this won't be the last ref because of the get above,
		 * so res->spinlock will not be taken here */
		dlm_lock_put(lock);
		/* मुक्त up the reserved bast that we are cancelling.
		 * guaranteed that this will not be the last reserved
		 * ast because *both* an ast and a bast were reserved
		 * to get to this poपूर्णांक.  the res->spinlock will not be
		 * taken here */
		dlm_lockres_release_ast(dlm, res);
	पूर्ण
	list_add_tail(&lock->ast_list, &dlm->pending_asts);
	lock->ast_pending = 1;
	spin_unlock(&lock->spinlock);
पूर्ण

व्योम dlm_queue_ast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock)
अणु
	BUG_ON(!dlm);
	BUG_ON(!lock);

	spin_lock(&dlm->ast_lock);
	__dlm_queue_ast(dlm, lock);
	spin_unlock(&dlm->ast_lock);
पूर्ण


व्योम __dlm_queue_bast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock *lock)
अणु
	काष्ठा dlm_lock_resource *res;

	BUG_ON(!dlm);
	BUG_ON(!lock);

	निश्चित_spin_locked(&dlm->ast_lock);

	res = lock->lockres;

	BUG_ON(!list_empty(&lock->bast_list));
	अगर (lock->bast_pending)
		mlog(0, "%s: res %.*s, lock %u:%llu, BAST getting flushed\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));

	/* putting lock on list, add a ref */
	dlm_lock_get(lock);
	spin_lock(&lock->spinlock);
	list_add_tail(&lock->bast_list, &dlm->pending_basts);
	lock->bast_pending = 1;
	spin_unlock(&lock->spinlock);
पूर्ण

अटल व्योम dlm_update_lvb(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
			   काष्ठा dlm_lock *lock)
अणु
	काष्ठा dlm_lockstatus *lksb = lock->lksb;
	BUG_ON(!lksb);

	/* only updates अगर this node masters the lockres */
	spin_lock(&res->spinlock);
	अगर (res->owner == dlm->node_num) अणु
		/* check the lksb flags क्रम the direction */
		अगर (lksb->flags & DLM_LKSB_GET_LVB) अणु
			mlog(0, "getting lvb from lockres for %s node\n",
				  lock->ml.node == dlm->node_num ? "master" :
				  "remote");
			स_नकल(lksb->lvb, res->lvb, DLM_LVB_LEN);
		पूर्ण
		/* Do nothing क्रम lvb put requests - they should be करोne in
 		 * place when the lock is करोwnconverted - otherwise we risk
 		 * racing माला_लो and माला_दो which could result in old lvb data
 		 * being propagated. We leave the put flag set and clear it
 		 * here. In the future we might want to clear it at the समय
 		 * the put is actually करोne.
		 */
	पूर्ण
	spin_unlock(&res->spinlock);

	/* reset any lvb flags on the lksb */
	lksb->flags &= ~(DLM_LKSB_PUT_LVB|DLM_LKSB_GET_LVB);
पूर्ण

व्योम dlm_करो_local_ast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
		      काष्ठा dlm_lock *lock)
अणु
	dlm_astlockfunc_t *fn;

	mlog(0, "%s: res %.*s, lock %u:%llu, Local AST\n", dlm->name,
	     res->lockname.len, res->lockname.name,
	     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
	     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));

	fn = lock->ast;
	BUG_ON(lock->ml.node != dlm->node_num);

	dlm_update_lvb(dlm, res, lock);
	(*fn)(lock->astdata);
पूर्ण


पूर्णांक dlm_करो_remote_ast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
		      काष्ठा dlm_lock *lock)
अणु
	पूर्णांक ret;
	काष्ठा dlm_lockstatus *lksb;
	पूर्णांक lksbflags;

	mlog(0, "%s: res %.*s, lock %u:%llu, Remote AST\n", dlm->name,
	     res->lockname.len, res->lockname.name,
	     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
	     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));

	lksb = lock->lksb;
	BUG_ON(lock->ml.node == dlm->node_num);

	lksbflags = lksb->flags;
	dlm_update_lvb(dlm, res, lock);

	/* lock request came from another node
	 * go करो the ast over there */
	ret = dlm_send_proxy_ast(dlm, res, lock, lksbflags);
	वापस ret;
पूर्ण

व्योम dlm_करो_local_bast(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
		       काष्ठा dlm_lock *lock, पूर्णांक blocked_type)
अणु
	dlm_bastlockfunc_t *fn = lock->bast;

	BUG_ON(lock->ml.node != dlm->node_num);

	mlog(0, "%s: res %.*s, lock %u:%llu, Local BAST, blocked %d\n",
	     dlm->name, res->lockname.len, res->lockname.name,
	     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
	     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
	     blocked_type);

	(*fn)(lock->astdata, blocked_type);
पूर्ण



पूर्णांक dlm_proxy_ast_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			  व्योम **ret_data)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक locklen;
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा dlm_lock *lock = शून्य;
	काष्ठा dlm_proxy_ast *past = (काष्ठा dlm_proxy_ast *) msg->buf;
	अक्षर *name;
	काष्ठा list_head *head = शून्य;
	__be64 cookie;
	u32 flags;
	u8 node;

	अगर (!dlm_grab(dlm)) अणु
		dlm_error(DLM_REJECTED);
		वापस DLM_REJECTED;
	पूर्ण

	mlog_bug_on_msg(!dlm_करोमुख्य_fully_joined(dlm),
			"Domain %s not fully joined!\n", dlm->name);

	name = past->name;
	locklen = past->namelen;
	cookie = past->cookie;
	flags = be32_to_cpu(past->flags);
	node = past->node_idx;

	अगर (locklen > DLM_LOCKID_NAME_MAX) अणु
		ret = DLM_IVBUFLEN;
		mlog(ML_ERROR, "Invalid name length (%d) in proxy ast "
		     "handler!\n", locklen);
		जाओ leave;
	पूर्ण

	अगर ((flags & (LKM_PUT_LVB|LKM_GET_LVB)) ==
	     (LKM_PUT_LVB|LKM_GET_LVB)) अणु
		mlog(ML_ERROR, "Both PUT and GET lvb specified, (0x%x)\n",
		     flags);
		ret = DLM_BADARGS;
		जाओ leave;
	पूर्ण

	mlog(0, "lvb: %s\n", flags & LKM_PUT_LVB ? "put lvb" :
		  (flags & LKM_GET_LVB ? "get lvb" : "none"));

	mlog(0, "type=%d, blocked_type=%d\n", past->type, past->blocked_type);

	अगर (past->type != DLM_AST &&
	    past->type != DLM_BAST) अणु
		mlog(ML_ERROR, "Unknown ast type! %d, cookie=%u:%llu"
		     "name=%.*s, node=%u\n", past->type,
		     dlm_get_lock_cookie_node(be64_to_cpu(cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(cookie)),
		     locklen, name, node);
		ret = DLM_IVLOCKID;
		जाओ leave;
	पूर्ण

	res = dlm_lookup_lockres(dlm, name, locklen);
	अगर (!res) अणु
		mlog(0, "Got %sast for unknown lockres! cookie=%u:%llu, "
		     "name=%.*s, node=%u\n", (past->type == DLM_AST ? "" : "b"),
		     dlm_get_lock_cookie_node(be64_to_cpu(cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(cookie)),
		     locklen, name, node);
		ret = DLM_IVLOCKID;
		जाओ leave;
	पूर्ण

	/* cannot get a proxy ast message अगर this node owns it */
	BUG_ON(res->owner == dlm->node_num);

	mlog(0, "%s: res %.*s\n", dlm->name, res->lockname.len,
	     res->lockname.name);

	spin_lock(&res->spinlock);
	अगर (res->state & DLM_LOCK_RES_RECOVERING) अणु
		mlog(0, "Responding with DLM_RECOVERING!\n");
		ret = DLM_RECOVERING;
		जाओ unlock_out;
	पूर्ण
	अगर (res->state & DLM_LOCK_RES_MIGRATING) अणु
		mlog(0, "Responding with DLM_MIGRATING!\n");
		ret = DLM_MIGRATING;
		जाओ unlock_out;
	पूर्ण
	/* try convert queue क्रम both ast/bast */
	head = &res->converting;
	lock = शून्य;
	list_क्रम_each_entry(lock, head, list) अणु
		अगर (lock->ml.cookie == cookie)
			जाओ करो_ast;
	पूर्ण

	/* अगर not on convert, try blocked क्रम ast, granted क्रम bast */
	अगर (past->type == DLM_AST)
		head = &res->blocked;
	अन्यथा
		head = &res->granted;

	list_क्रम_each_entry(lock, head, list) अणु
		/* अगर lock is found but unlock is pending ignore the bast */
		अगर (lock->ml.cookie == cookie) अणु
			अगर (lock->unlock_pending)
				अवरोध;
			जाओ करो_ast;
		पूर्ण
	पूर्ण

	mlog(0, "Got %sast for unknown lock! cookie=%u:%llu, name=%.*s, "
	     "node=%u\n", past->type == DLM_AST ? "" : "b",
	     dlm_get_lock_cookie_node(be64_to_cpu(cookie)),
	     dlm_get_lock_cookie_seq(be64_to_cpu(cookie)),
	     locklen, name, node);

	ret = DLM_NORMAL;
unlock_out:
	spin_unlock(&res->spinlock);
	जाओ leave;

करो_ast:
	ret = DLM_NORMAL;
	अगर (past->type == DLM_AST) अणु
		/* करो not alter lock refcount.  चयनing lists. */
		list_move_tail(&lock->list, &res->granted);
		mlog(0, "%s: res %.*s, lock %u:%llu, Granted type %d => %d\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(cookie)),
		     lock->ml.type, lock->ml.convert_type);

		अगर (lock->ml.convert_type != LKM_IVMODE) अणु
			lock->ml.type = lock->ml.convert_type;
			lock->ml.convert_type = LKM_IVMODE;
		पूर्ण अन्यथा अणु
			// should alपढ़ोy be there....
		पूर्ण

		lock->lksb->status = DLM_NORMAL;

		/* अगर we requested the lvb, fetch it पूर्णांकo our lksb now */
		अगर (flags & LKM_GET_LVB) अणु
			BUG_ON(!(lock->lksb->flags & DLM_LKSB_GET_LVB));
			स_नकल(lock->lksb->lvb, past->lvb, DLM_LVB_LEN);
		पूर्ण
	पूर्ण
	spin_unlock(&res->spinlock);

	अगर (past->type == DLM_AST)
		dlm_करो_local_ast(dlm, res, lock);
	अन्यथा
		dlm_करो_local_bast(dlm, res, lock, past->blocked_type);

leave:
	अगर (res)
		dlm_lockres_put(res);

	dlm_put(dlm);
	वापस ret;
पूर्ण



पूर्णांक dlm_send_proxy_ast_msg(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
			   काष्ठा dlm_lock *lock, पूर्णांक msg_type,
			   पूर्णांक blocked_type, पूर्णांक flags)
अणु
	पूर्णांक ret = 0;
	काष्ठा dlm_proxy_ast past;
	काष्ठा kvec vec[2];
	माप_प्रकार veclen = 1;
	पूर्णांक status;

	mlog(0, "%s: res %.*s, to %u, type %d, blocked_type %d\n", dlm->name,
	     res->lockname.len, res->lockname.name, lock->ml.node, msg_type,
	     blocked_type);

	स_रखो(&past, 0, माप(काष्ठा dlm_proxy_ast));
	past.node_idx = dlm->node_num;
	past.type = msg_type;
	past.blocked_type = blocked_type;
	past.namelen = res->lockname.len;
	स_नकल(past.name, res->lockname.name, past.namelen);
	past.cookie = lock->ml.cookie;

	vec[0].iov_len = माप(काष्ठा dlm_proxy_ast);
	vec[0].iov_base = &past;
	अगर (flags & DLM_LKSB_GET_LVB) अणु
		be32_add_cpu(&past.flags, LKM_GET_LVB);
		vec[1].iov_len = DLM_LVB_LEN;
		vec[1].iov_base = lock->lksb->lvb;
		veclen++;
	पूर्ण

	ret = o2net_send_message_vec(DLM_PROXY_AST_MSG, dlm->key, vec, veclen,
				     lock->ml.node, &status);
	अगर (ret < 0)
		mlog(ML_ERROR, "%s: res %.*s, error %d send AST to node %u\n",
		     dlm->name, res->lockname.len, res->lockname.name, ret,
		     lock->ml.node);
	अन्यथा अणु
		अगर (status == DLM_RECOVERING) अणु
			mlog(ML_ERROR, "sent AST to node %u, it thinks this "
			     "node is dead!\n", lock->ml.node);
			BUG();
		पूर्ण अन्यथा अगर (status == DLM_MIGRATING) अणु
			mlog(ML_ERROR, "sent AST to node %u, it returned "
			     "DLM_MIGRATING!\n", lock->ml.node);
			BUG();
		पूर्ण अन्यथा अगर (status != DLM_NORMAL && status != DLM_IVLOCKID) अणु
			mlog(ML_ERROR, "AST to node %u returned %d!\n",
			     lock->ml.node, status);
			/* ignore it */
		पूर्ण
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण
