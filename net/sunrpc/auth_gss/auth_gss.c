<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * linux/net/sunrpc/auth_gss/auth_gss.c
 *
 * RPCSEC_GSS client authentication.
 *
 *  Copyright (c) 2000 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Dug Song       <dugsong@monkey.org>
 *  Andy Adamson   <andros@umich.edu>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/sunrpc/auth_gss.h>
#समावेश <linux/sunrpc/gss_krb5.h>
#समावेश <linux/sunrpc/svcauth_gss.h>
#समावेश <linux/sunrpc/gss_err.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hashtable.h>

#समावेश "auth_gss_internal.h"
#समावेश "../netns.h"

#समावेश <trace/events/rpcgss.h>

अटल स्थिर काष्ठा rpc_authops authgss_ops;

अटल स्थिर काष्ठा rpc_creकरोps gss_creकरोps;
अटल स्थिर काष्ठा rpc_creकरोps gss_nullops;

#घोषणा GSS_RETRY_EXPIRED 5
अटल अचिन्हित पूर्णांक gss_expired_cred_retry_delay = GSS_RETRY_EXPIRED;

#घोषणा GSS_KEY_EXPIRE_TIMEO 240
अटल अचिन्हित पूर्णांक gss_key_expire_समयo = GSS_KEY_EXPIRE_TIMEO;

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_AUTH
#पूर्ण_अगर

#घोषणा GSS_CRED_SLACK		(RPC_MAX_AUTH_SIZE * 2)
/* length of a krb5 verअगरier (48), plus data added beक्रमe arguments when
 * using पूर्णांकegrity (two 4-byte पूर्णांकegers): */
#घोषणा GSS_VERF_SLACK		100

अटल DEFINE_HASHTABLE(gss_auth_hash_table, 4);
अटल DEFINE_SPINLOCK(gss_auth_hash_lock);

काष्ठा gss_pipe अणु
	काष्ठा rpc_pipe_dir_object pकरो;
	काष्ठा rpc_pipe *pipe;
	काष्ठा rpc_clnt *clnt;
	स्थिर अक्षर *name;
	काष्ठा kref kref;
पूर्ण;

काष्ठा gss_auth अणु
	काष्ठा kref kref;
	काष्ठा hlist_node hash;
	काष्ठा rpc_auth rpc_auth;
	काष्ठा gss_api_mech *mech;
	क्रमागत rpc_gss_svc service;
	काष्ठा rpc_clnt *client;
	काष्ठा net *net;
	/*
	 * There are two upcall pipes; dentry[1], named "gssd", is used
	 * क्रम the new text-based upcall; dentry[0] is named after the
	 * mechanism (क्रम example, "krb5") and exists क्रम
	 * backwards-compatibility with older gssd's.
	 */
	काष्ठा gss_pipe *gss_pipe[2];
	स्थिर अक्षर *target_name;
पूर्ण;

/* pipe_version >= 0 अगर and only अगर someone has a pipe खोलो. */
अटल DEFINE_SPINLOCK(pipe_version_lock);
अटल काष्ठा rpc_रुको_queue pipe_version_rpc_रुकोqueue;
अटल DECLARE_WAIT_QUEUE_HEAD(pipe_version_रुकोqueue);
अटल व्योम gss_put_auth(काष्ठा gss_auth *gss_auth);

अटल व्योम gss_मुक्त_ctx(काष्ठा gss_cl_ctx *);
अटल स्थिर काष्ठा rpc_pipe_ops gss_upcall_ops_v0;
अटल स्थिर काष्ठा rpc_pipe_ops gss_upcall_ops_v1;

अटल अंतरभूत काष्ठा gss_cl_ctx *
gss_get_ctx(काष्ठा gss_cl_ctx *ctx)
अणु
	refcount_inc(&ctx->count);
	वापस ctx;
पूर्ण

अटल अंतरभूत व्योम
gss_put_ctx(काष्ठा gss_cl_ctx *ctx)
अणु
	अगर (refcount_dec_and_test(&ctx->count))
		gss_मुक्त_ctx(ctx);
पूर्ण

/* gss_cred_set_ctx:
 * called by gss_upcall_callback and gss_create_upcall in order
 * to set the gss context. The actual exchange of an old context
 * and a new one is रक्षित by the pipe->lock.
 */
अटल व्योम
gss_cred_set_ctx(काष्ठा rpc_cred *cred, काष्ठा gss_cl_ctx *ctx)
अणु
	काष्ठा gss_cred *gss_cred = container_of(cred, काष्ठा gss_cred, gc_base);

	अगर (!test_bit(RPCAUTH_CRED_NEW, &cred->cr_flags))
		वापस;
	gss_get_ctx(ctx);
	rcu_assign_poपूर्णांकer(gss_cred->gc_ctx, ctx);
	set_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	smp_mb__beक्रमe_atomic();
	clear_bit(RPCAUTH_CRED_NEW, &cred->cr_flags);
पूर्ण

अटल काष्ठा gss_cl_ctx *
gss_cred_get_ctx(काष्ठा rpc_cred *cred)
अणु
	काष्ठा gss_cred *gss_cred = container_of(cred, काष्ठा gss_cred, gc_base);
	काष्ठा gss_cl_ctx *ctx = शून्य;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(gss_cred->gc_ctx);
	अगर (ctx)
		gss_get_ctx(ctx);
	rcu_पढ़ो_unlock();
	वापस ctx;
पूर्ण

अटल काष्ठा gss_cl_ctx *
gss_alloc_context(व्योम)
अणु
	काष्ठा gss_cl_ctx *ctx;

	ctx = kzalloc(माप(*ctx), GFP_NOFS);
	अगर (ctx != शून्य) अणु
		ctx->gc_proc = RPC_GSS_PROC_DATA;
		ctx->gc_seq = 1;	/* NetApp 6.4R1 करोesn't accept seq. no. 0 */
		spin_lock_init(&ctx->gc_seq_lock);
		refcount_set(&ctx->count,1);
	पूर्ण
	वापस ctx;
पूर्ण

#घोषणा GSSD_MIN_TIMEOUT (60 * 60)
अटल स्थिर व्योम *
gss_fill_context(स्थिर व्योम *p, स्थिर व्योम *end, काष्ठा gss_cl_ctx *ctx, काष्ठा gss_api_mech *gm)
अणु
	स्थिर व्योम *q;
	अचिन्हित पूर्णांक seclen;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित दीर्घ now = jअगरfies;
	u32 winकरोw_size;
	पूर्णांक ret;

	/* First अचिन्हित पूर्णांक gives the reमुख्यing lअगरeसमय in seconds of the
	 * credential - e.g. the reमुख्यing TGT lअगरeसमय क्रम Kerberos or
	 * the -t value passed to GSSD.
	 */
	p = simple_get_bytes(p, end, &समयout, माप(समयout));
	अगर (IS_ERR(p))
		जाओ err;
	अगर (समयout == 0)
		समयout = GSSD_MIN_TIMEOUT;
	ctx->gc_expiry = now + ((अचिन्हित दीर्घ)समयout * HZ);
	/* Sequence number winकरोw. Determines the maximum number of
	 * simultaneous requests
	 */
	p = simple_get_bytes(p, end, &winकरोw_size, माप(winकरोw_size));
	अगर (IS_ERR(p))
		जाओ err;
	ctx->gc_win = winकरोw_size;
	/* gssd संकेतs an error by passing ctx->gc_win = 0: */
	अगर (ctx->gc_win == 0) अणु
		/*
		 * in which हाल, p poपूर्णांकs to an error code. Anything other
		 * than -EKEYEXPIRED माला_लो converted to -EACCES.
		 */
		p = simple_get_bytes(p, end, &ret, माप(ret));
		अगर (!IS_ERR(p))
			p = (ret == -EKEYEXPIRED) ? ERR_PTR(-EKEYEXPIRED) :
						    ERR_PTR(-EACCES);
		जाओ err;
	पूर्ण
	/* copy the opaque wire context */
	p = simple_get_netobj(p, end, &ctx->gc_wire_ctx);
	अगर (IS_ERR(p))
		जाओ err;
	/* import the opaque security context */
	p  = simple_get_bytes(p, end, &seclen, माप(seclen));
	अगर (IS_ERR(p))
		जाओ err;
	q = (स्थिर व्योम *)((स्थिर अक्षर *)p + seclen);
	अगर (unlikely(q > end || q < p)) अणु
		p = ERR_PTR(-EFAULT);
		जाओ err;
	पूर्ण
	ret = gss_import_sec_context(p, seclen, gm, &ctx->gc_gss_ctx, शून्य, GFP_NOFS);
	अगर (ret < 0) अणु
		trace_rpcgss_import_ctx(ret);
		p = ERR_PTR(ret);
		जाओ err;
	पूर्ण

	/* is there any trailing data? */
	अगर (q == end) अणु
		p = q;
		जाओ करोne;
	पूर्ण

	/* pull in acceptor name (अगर there is one) */
	p = simple_get_netobj(q, end, &ctx->gc_acceptor);
	अगर (IS_ERR(p))
		जाओ err;
करोne:
	trace_rpcgss_context(winकरोw_size, ctx->gc_expiry, now, समयout,
			     ctx->gc_acceptor.len, ctx->gc_acceptor.data);
err:
	वापस p;
पूर्ण

/* XXX: Need some करोcumentation about why UPCALL_BUF_LEN is so small.
 *	Is user space expecting no more than UPCALL_BUF_LEN bytes?
 *	Note that there are now _two_ NI_MAXHOST sized data items
 *	being passed in this string.
 */
#घोषणा UPCALL_BUF_LEN	256

काष्ठा gss_upcall_msg अणु
	refcount_t count;
	kuid_t	uid;
	स्थिर अक्षर *service_name;
	काष्ठा rpc_pipe_msg msg;
	काष्ठा list_head list;
	काष्ठा gss_auth *auth;
	काष्ठा rpc_pipe *pipe;
	काष्ठा rpc_रुको_queue rpc_रुकोqueue;
	रुको_queue_head_t रुकोqueue;
	काष्ठा gss_cl_ctx *ctx;
	अक्षर databuf[UPCALL_BUF_LEN];
पूर्ण;

अटल पूर्णांक get_pipe_version(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	पूर्णांक ret;

	spin_lock(&pipe_version_lock);
	अगर (sn->pipe_version >= 0) अणु
		atomic_inc(&sn->pipe_users);
		ret = sn->pipe_version;
	पूर्ण अन्यथा
		ret = -EAGAIN;
	spin_unlock(&pipe_version_lock);
	वापस ret;
पूर्ण

अटल व्योम put_pipe_version(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	अगर (atomic_dec_and_lock(&sn->pipe_users, &pipe_version_lock)) अणु
		sn->pipe_version = -1;
		spin_unlock(&pipe_version_lock);
	पूर्ण
पूर्ण

अटल व्योम
gss_release_msg(काष्ठा gss_upcall_msg *gss_msg)
अणु
	काष्ठा net *net = gss_msg->auth->net;
	अगर (!refcount_dec_and_test(&gss_msg->count))
		वापस;
	put_pipe_version(net);
	BUG_ON(!list_empty(&gss_msg->list));
	अगर (gss_msg->ctx != शून्य)
		gss_put_ctx(gss_msg->ctx);
	rpc_destroy_रुको_queue(&gss_msg->rpc_रुकोqueue);
	gss_put_auth(gss_msg->auth);
	kमुक्त_स्थिर(gss_msg->service_name);
	kमुक्त(gss_msg);
पूर्ण

अटल काष्ठा gss_upcall_msg *
__gss_find_upcall(काष्ठा rpc_pipe *pipe, kuid_t uid, स्थिर काष्ठा gss_auth *auth)
अणु
	काष्ठा gss_upcall_msg *pos;
	list_क्रम_each_entry(pos, &pipe->in_करोwncall, list) अणु
		अगर (!uid_eq(pos->uid, uid))
			जारी;
		अगर (auth && pos->auth->service != auth->service)
			जारी;
		refcount_inc(&pos->count);
		वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Try to add an upcall to the pipefs queue.
 * If an upcall owned by our uid alपढ़ोy exists, then we वापस a reference
 * to that upcall instead of adding the new upcall.
 */
अटल अंतरभूत काष्ठा gss_upcall_msg *
gss_add_msg(काष्ठा gss_upcall_msg *gss_msg)
अणु
	काष्ठा rpc_pipe *pipe = gss_msg->pipe;
	काष्ठा gss_upcall_msg *old;

	spin_lock(&pipe->lock);
	old = __gss_find_upcall(pipe, gss_msg->uid, gss_msg->auth);
	अगर (old == शून्य) अणु
		refcount_inc(&gss_msg->count);
		list_add(&gss_msg->list, &pipe->in_करोwncall);
	पूर्ण अन्यथा
		gss_msg = old;
	spin_unlock(&pipe->lock);
	वापस gss_msg;
पूर्ण

अटल व्योम
__gss_unhash_msg(काष्ठा gss_upcall_msg *gss_msg)
अणु
	list_del_init(&gss_msg->list);
	rpc_wake_up_status(&gss_msg->rpc_रुकोqueue, gss_msg->msg.त्रुटि_सं);
	wake_up_all(&gss_msg->रुकोqueue);
	refcount_dec(&gss_msg->count);
पूर्ण

अटल व्योम
gss_unhash_msg(काष्ठा gss_upcall_msg *gss_msg)
अणु
	काष्ठा rpc_pipe *pipe = gss_msg->pipe;

	अगर (list_empty(&gss_msg->list))
		वापस;
	spin_lock(&pipe->lock);
	अगर (!list_empty(&gss_msg->list))
		__gss_unhash_msg(gss_msg);
	spin_unlock(&pipe->lock);
पूर्ण

अटल व्योम
gss_handle_करोwncall_result(काष्ठा gss_cred *gss_cred, काष्ठा gss_upcall_msg *gss_msg)
अणु
	चयन (gss_msg->msg.त्रुटि_सं) अणु
	हाल 0:
		अगर (gss_msg->ctx == शून्य)
			अवरोध;
		clear_bit(RPCAUTH_CRED_NEGATIVE, &gss_cred->gc_base.cr_flags);
		gss_cred_set_ctx(&gss_cred->gc_base, gss_msg->ctx);
		अवरोध;
	हाल -EKEYEXPIRED:
		set_bit(RPCAUTH_CRED_NEGATIVE, &gss_cred->gc_base.cr_flags);
	पूर्ण
	gss_cred->gc_upcall_बारtamp = jअगरfies;
	gss_cred->gc_upcall = शून्य;
	rpc_wake_up_status(&gss_msg->rpc_रुकोqueue, gss_msg->msg.त्रुटि_सं);
पूर्ण

अटल व्योम
gss_upcall_callback(काष्ठा rpc_task *task)
अणु
	काष्ठा gss_cred *gss_cred = container_of(task->tk_rqstp->rq_cred,
			काष्ठा gss_cred, gc_base);
	काष्ठा gss_upcall_msg *gss_msg = gss_cred->gc_upcall;
	काष्ठा rpc_pipe *pipe = gss_msg->pipe;

	spin_lock(&pipe->lock);
	gss_handle_करोwncall_result(gss_cred, gss_msg);
	spin_unlock(&pipe->lock);
	task->tk_status = gss_msg->msg.त्रुटि_सं;
	gss_release_msg(gss_msg);
पूर्ण

अटल व्योम gss_encode_v0_msg(काष्ठा gss_upcall_msg *gss_msg,
			      स्थिर काष्ठा cred *cred)
अणु
	काष्ठा user_namespace *userns = cred->user_ns;

	uid_t uid = from_kuid_munged(userns, gss_msg->uid);
	स_नकल(gss_msg->databuf, &uid, माप(uid));
	gss_msg->msg.data = gss_msg->databuf;
	gss_msg->msg.len = माप(uid);

	BUILD_BUG_ON(माप(uid) > माप(gss_msg->databuf));
पूर्ण

अटल sमाप_प्रकार
gss_v0_upcall(काष्ठा file *file, काष्ठा rpc_pipe_msg *msg,
		अक्षर __user *buf, माप_प्रकार buflen)
अणु
	काष्ठा gss_upcall_msg *gss_msg = container_of(msg,
						      काष्ठा gss_upcall_msg,
						      msg);
	अगर (msg->copied == 0)
		gss_encode_v0_msg(gss_msg, file->f_cred);
	वापस rpc_pipe_generic_upcall(file, msg, buf, buflen);
पूर्ण

अटल पूर्णांक gss_encode_v1_msg(काष्ठा gss_upcall_msg *gss_msg,
				स्थिर अक्षर *service_name,
				स्थिर अक्षर *target_name,
				स्थिर काष्ठा cred *cred)
अणु
	काष्ठा user_namespace *userns = cred->user_ns;
	काष्ठा gss_api_mech *mech = gss_msg->auth->mech;
	अक्षर *p = gss_msg->databuf;
	माप_प्रकार buflen = माप(gss_msg->databuf);
	पूर्णांक len;

	len = scnम_लिखो(p, buflen, "mech=%s uid=%d", mech->gm_name,
			from_kuid_munged(userns, gss_msg->uid));
	buflen -= len;
	p += len;
	gss_msg->msg.len = len;

	/*
	 * target= is a full service principal that names the remote
	 * identity that we are authenticating to.
	 */
	अगर (target_name) अणु
		len = scnम_लिखो(p, buflen, " target=%s", target_name);
		buflen -= len;
		p += len;
		gss_msg->msg.len += len;
	पूर्ण

	/*
	 * gssd uses service= and srchost= to select a matching key from
	 * the प्रणाली's keytab to use as the source principal.
	 *
	 * service= is the service name part of the source principal,
	 * or "*" (meaning choose any).
	 *
	 * srchost= is the hostname part of the source principal. When
	 * not provided, gssd uses the local hostname.
	 */
	अगर (service_name) अणु
		अक्षर *c = म_अक्षर(service_name, '@');

		अगर (!c)
			len = scnम_लिखो(p, buflen, " service=%s",
					service_name);
		अन्यथा
			len = scnम_लिखो(p, buflen,
					" service=%.*s srchost=%s",
					(पूर्णांक)(c - service_name),
					service_name, c + 1);
		buflen -= len;
		p += len;
		gss_msg->msg.len += len;
	पूर्ण

	अगर (mech->gm_upcall_enctypes) अणु
		len = scnम_लिखो(p, buflen, " enctypes=%s",
				mech->gm_upcall_enctypes);
		buflen -= len;
		p += len;
		gss_msg->msg.len += len;
	पूर्ण
	trace_rpcgss_upcall_msg(gss_msg->databuf);
	len = scnम_लिखो(p, buflen, "\n");
	अगर (len == 0)
		जाओ out_overflow;
	gss_msg->msg.len += len;
	gss_msg->msg.data = gss_msg->databuf;
	वापस 0;
out_overflow:
	WARN_ON_ONCE(1);
	वापस -ENOMEM;
पूर्ण

अटल sमाप_प्रकार
gss_v1_upcall(काष्ठा file *file, काष्ठा rpc_pipe_msg *msg,
		अक्षर __user *buf, माप_प्रकार buflen)
अणु
	काष्ठा gss_upcall_msg *gss_msg = container_of(msg,
						      काष्ठा gss_upcall_msg,
						      msg);
	पूर्णांक err;
	अगर (msg->copied == 0) अणु
		err = gss_encode_v1_msg(gss_msg,
					gss_msg->service_name,
					gss_msg->auth->target_name,
					file->f_cred);
		अगर (err)
			वापस err;
	पूर्ण
	वापस rpc_pipe_generic_upcall(file, msg, buf, buflen);
पूर्ण

अटल काष्ठा gss_upcall_msg *
gss_alloc_msg(काष्ठा gss_auth *gss_auth,
		kuid_t uid, स्थिर अक्षर *service_name)
अणु
	काष्ठा gss_upcall_msg *gss_msg;
	पूर्णांक vers;
	पूर्णांक err = -ENOMEM;

	gss_msg = kzalloc(माप(*gss_msg), GFP_NOFS);
	अगर (gss_msg == शून्य)
		जाओ err;
	vers = get_pipe_version(gss_auth->net);
	err = vers;
	अगर (err < 0)
		जाओ err_मुक्त_msg;
	gss_msg->pipe = gss_auth->gss_pipe[vers]->pipe;
	INIT_LIST_HEAD(&gss_msg->list);
	rpc_init_रुको_queue(&gss_msg->rpc_रुकोqueue, "RPCSEC_GSS upcall waitq");
	init_रुकोqueue_head(&gss_msg->रुकोqueue);
	refcount_set(&gss_msg->count, 1);
	gss_msg->uid = uid;
	gss_msg->auth = gss_auth;
	kref_get(&gss_auth->kref);
	अगर (service_name) अणु
		gss_msg->service_name = kstrdup_स्थिर(service_name, GFP_NOFS);
		अगर (!gss_msg->service_name) अणु
			err = -ENOMEM;
			जाओ err_put_pipe_version;
		पूर्ण
	पूर्ण
	वापस gss_msg;
err_put_pipe_version:
	put_pipe_version(gss_auth->net);
err_मुक्त_msg:
	kमुक्त(gss_msg);
err:
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा gss_upcall_msg *
gss_setup_upcall(काष्ठा gss_auth *gss_auth, काष्ठा rpc_cred *cred)
अणु
	काष्ठा gss_cred *gss_cred = container_of(cred,
			काष्ठा gss_cred, gc_base);
	काष्ठा gss_upcall_msg *gss_new, *gss_msg;
	kuid_t uid = cred->cr_cred->fsuid;

	gss_new = gss_alloc_msg(gss_auth, uid, gss_cred->gc_principal);
	अगर (IS_ERR(gss_new))
		वापस gss_new;
	gss_msg = gss_add_msg(gss_new);
	अगर (gss_msg == gss_new) अणु
		पूर्णांक res;
		refcount_inc(&gss_msg->count);
		res = rpc_queue_upcall(gss_new->pipe, &gss_new->msg);
		अगर (res) अणु
			gss_unhash_msg(gss_new);
			refcount_dec(&gss_msg->count);
			gss_release_msg(gss_new);
			gss_msg = ERR_PTR(res);
		पूर्ण
	पूर्ण अन्यथा
		gss_release_msg(gss_new);
	वापस gss_msg;
पूर्ण

अटल व्योम warn_gssd(व्योम)
अणु
	dprपूर्णांकk("AUTH_GSS upcall failed. Please check user daemon is running.\n");
पूर्ण

अटल अंतरभूत पूर्णांक
gss_refresh_upcall(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_cred *cred = task->tk_rqstp->rq_cred;
	काष्ठा gss_auth *gss_auth = container_of(cred->cr_auth,
			काष्ठा gss_auth, rpc_auth);
	काष्ठा gss_cred *gss_cred = container_of(cred,
			काष्ठा gss_cred, gc_base);
	काष्ठा gss_upcall_msg *gss_msg;
	काष्ठा rpc_pipe *pipe;
	पूर्णांक err = 0;

	gss_msg = gss_setup_upcall(gss_auth, cred);
	अगर (PTR_ERR(gss_msg) == -EAGAIN) अणु
		/* XXX: warning on the first, under the assumption we
		 * shouldn't normally hit this हाल on a refresh. */
		warn_gssd();
		rpc_sleep_on_समयout(&pipe_version_rpc_रुकोqueue,
				task, शून्य, jअगरfies + (15 * HZ));
		err = -EAGAIN;
		जाओ out;
	पूर्ण
	अगर (IS_ERR(gss_msg)) अणु
		err = PTR_ERR(gss_msg);
		जाओ out;
	पूर्ण
	pipe = gss_msg->pipe;
	spin_lock(&pipe->lock);
	अगर (gss_cred->gc_upcall != शून्य)
		rpc_sleep_on(&gss_cred->gc_upcall->rpc_रुकोqueue, task, शून्य);
	अन्यथा अगर (gss_msg->ctx == शून्य && gss_msg->msg.त्रुटि_सं >= 0) अणु
		gss_cred->gc_upcall = gss_msg;
		/* gss_upcall_callback will release the reference to gss_upcall_msg */
		refcount_inc(&gss_msg->count);
		rpc_sleep_on(&gss_msg->rpc_रुकोqueue, task, gss_upcall_callback);
	पूर्ण अन्यथा अणु
		gss_handle_करोwncall_result(gss_cred, gss_msg);
		err = gss_msg->msg.त्रुटि_सं;
	पूर्ण
	spin_unlock(&pipe->lock);
	gss_release_msg(gss_msg);
out:
	trace_rpcgss_upcall_result(from_kuid(&init_user_ns,
					     cred->cr_cred->fsuid), err);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक
gss_create_upcall(काष्ठा gss_auth *gss_auth, काष्ठा gss_cred *gss_cred)
अणु
	काष्ठा net *net = gss_auth->net;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा rpc_pipe *pipe;
	काष्ठा rpc_cred *cred = &gss_cred->gc_base;
	काष्ठा gss_upcall_msg *gss_msg;
	DEFINE_WAIT(रुको);
	पूर्णांक err;

retry:
	err = 0;
	/* अगर gssd is करोwn, just skip upcalling altogether */
	अगर (!gssd_running(net)) अणु
		warn_gssd();
		err = -EACCES;
		जाओ out;
	पूर्ण
	gss_msg = gss_setup_upcall(gss_auth, cred);
	अगर (PTR_ERR(gss_msg) == -EAGAIN) अणु
		err = रुको_event_पूर्णांकerruptible_समयout(pipe_version_रुकोqueue,
				sn->pipe_version >= 0, 15 * HZ);
		अगर (sn->pipe_version < 0) अणु
			warn_gssd();
			err = -EACCES;
		पूर्ण
		अगर (err < 0)
			जाओ out;
		जाओ retry;
	पूर्ण
	अगर (IS_ERR(gss_msg)) अणु
		err = PTR_ERR(gss_msg);
		जाओ out;
	पूर्ण
	pipe = gss_msg->pipe;
	क्रम (;;) अणु
		prepare_to_रुको(&gss_msg->रुकोqueue, &रुको, TASK_KILLABLE);
		spin_lock(&pipe->lock);
		अगर (gss_msg->ctx != शून्य || gss_msg->msg.त्रुटि_सं < 0) अणु
			अवरोध;
		पूर्ण
		spin_unlock(&pipe->lock);
		अगर (fatal_संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ out_पूर्णांकr;
		पूर्ण
		schedule();
	पूर्ण
	अगर (gss_msg->ctx) अणु
		trace_rpcgss_ctx_init(gss_cred);
		gss_cred_set_ctx(cred, gss_msg->ctx);
	पूर्ण अन्यथा अणु
		err = gss_msg->msg.त्रुटि_सं;
	पूर्ण
	spin_unlock(&pipe->lock);
out_पूर्णांकr:
	finish_रुको(&gss_msg->रुकोqueue, &रुको);
	gss_release_msg(gss_msg);
out:
	trace_rpcgss_upcall_result(from_kuid(&init_user_ns,
					     cred->cr_cred->fsuid), err);
	वापस err;
पूर्ण

#घोषणा MSG_BUF_MAXSIZE 1024

अटल sमाप_प्रकार
gss_pipe_करोwncall(काष्ठा file *filp, स्थिर अक्षर __user *src, माप_प्रकार mlen)
अणु
	स्थिर व्योम *p, *end;
	व्योम *buf;
	काष्ठा gss_upcall_msg *gss_msg;
	काष्ठा rpc_pipe *pipe = RPC_I(file_inode(filp))->pipe;
	काष्ठा gss_cl_ctx *ctx;
	uid_t id;
	kuid_t uid;
	sमाप_प्रकार err = -EFBIG;

	अगर (mlen > MSG_BUF_MAXSIZE)
		जाओ out;
	err = -ENOMEM;
	buf = kदो_स्मृति(mlen, GFP_NOFS);
	अगर (!buf)
		जाओ out;

	err = -EFAULT;
	अगर (copy_from_user(buf, src, mlen))
		जाओ err;

	end = (स्थिर व्योम *)((अक्षर *)buf + mlen);
	p = simple_get_bytes(buf, end, &id, माप(id));
	अगर (IS_ERR(p)) अणु
		err = PTR_ERR(p);
		जाओ err;
	पूर्ण

	uid = make_kuid(current_user_ns(), id);
	अगर (!uid_valid(uid)) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = -ENOMEM;
	ctx = gss_alloc_context();
	अगर (ctx == शून्य)
		जाओ err;

	err = -ENOENT;
	/* Find a matching upcall */
	spin_lock(&pipe->lock);
	gss_msg = __gss_find_upcall(pipe, uid, शून्य);
	अगर (gss_msg == शून्य) अणु
		spin_unlock(&pipe->lock);
		जाओ err_put_ctx;
	पूर्ण
	list_del_init(&gss_msg->list);
	spin_unlock(&pipe->lock);

	p = gss_fill_context(p, end, ctx, gss_msg->auth->mech);
	अगर (IS_ERR(p)) अणु
		err = PTR_ERR(p);
		चयन (err) अणु
		हाल -EACCES:
		हाल -EKEYEXPIRED:
			gss_msg->msg.त्रुटि_सं = err;
			err = mlen;
			अवरोध;
		हाल -EFAULT:
		हाल -ENOMEM:
		हाल -EINVAL:
		हाल -ENOSYS:
			gss_msg->msg.त्रुटि_सं = -EAGAIN;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_CRIT "%s: bad return from "
				"gss_fill_context: %zd\n", __func__, err);
			gss_msg->msg.त्रुटि_सं = -EIO;
		पूर्ण
		जाओ err_release_msg;
	पूर्ण
	gss_msg->ctx = gss_get_ctx(ctx);
	err = mlen;

err_release_msg:
	spin_lock(&pipe->lock);
	__gss_unhash_msg(gss_msg);
	spin_unlock(&pipe->lock);
	gss_release_msg(gss_msg);
err_put_ctx:
	gss_put_ctx(ctx);
err:
	kमुक्त(buf);
out:
	वापस err;
पूर्ण

अटल पूर्णांक gss_pipe_खोलो(काष्ठा inode *inode, पूर्णांक new_version)
अणु
	काष्ठा net *net = inode->i_sb->s_fs_info;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	पूर्णांक ret = 0;

	spin_lock(&pipe_version_lock);
	अगर (sn->pipe_version < 0) अणु
		/* First खोलो of any gss pipe determines the version: */
		sn->pipe_version = new_version;
		rpc_wake_up(&pipe_version_rpc_रुकोqueue);
		wake_up(&pipe_version_रुकोqueue);
	पूर्ण अन्यथा अगर (sn->pipe_version != new_version) अणु
		/* Trying to खोलो a pipe of a dअगरferent version */
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	atomic_inc(&sn->pipe_users);
out:
	spin_unlock(&pipe_version_lock);
	वापस ret;

पूर्ण

अटल पूर्णांक gss_pipe_खोलो_v0(काष्ठा inode *inode)
अणु
	वापस gss_pipe_खोलो(inode, 0);
पूर्ण

अटल पूर्णांक gss_pipe_खोलो_v1(काष्ठा inode *inode)
अणु
	वापस gss_pipe_खोलो(inode, 1);
पूर्ण

अटल व्योम
gss_pipe_release(काष्ठा inode *inode)
अणु
	काष्ठा net *net = inode->i_sb->s_fs_info;
	काष्ठा rpc_pipe *pipe = RPC_I(inode)->pipe;
	काष्ठा gss_upcall_msg *gss_msg;

restart:
	spin_lock(&pipe->lock);
	list_क्रम_each_entry(gss_msg, &pipe->in_करोwncall, list) अणु

		अगर (!list_empty(&gss_msg->msg.list))
			जारी;
		gss_msg->msg.त्रुटि_सं = -EPIPE;
		refcount_inc(&gss_msg->count);
		__gss_unhash_msg(gss_msg);
		spin_unlock(&pipe->lock);
		gss_release_msg(gss_msg);
		जाओ restart;
	पूर्ण
	spin_unlock(&pipe->lock);

	put_pipe_version(net);
पूर्ण

अटल व्योम
gss_pipe_destroy_msg(काष्ठा rpc_pipe_msg *msg)
अणु
	काष्ठा gss_upcall_msg *gss_msg = container_of(msg, काष्ठा gss_upcall_msg, msg);

	अगर (msg->त्रुटि_सं < 0) अणु
		refcount_inc(&gss_msg->count);
		gss_unhash_msg(gss_msg);
		अगर (msg->त्रुटि_सं == -ETIMEDOUT)
			warn_gssd();
		gss_release_msg(gss_msg);
	पूर्ण
	gss_release_msg(gss_msg);
पूर्ण

अटल व्योम gss_pipe_dentry_destroy(काष्ठा dentry *dir,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	काष्ठा gss_pipe *gss_pipe = pकरो->pकरो_data;
	काष्ठा rpc_pipe *pipe = gss_pipe->pipe;

	अगर (pipe->dentry != शून्य) अणु
		rpc_unlink(pipe->dentry);
		pipe->dentry = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक gss_pipe_dentry_create(काष्ठा dentry *dir,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	काष्ठा gss_pipe *p = pकरो->pकरो_data;
	काष्ठा dentry *dentry;

	dentry = rpc_mkpipe_dentry(dir, p->name, p->clnt, p->pipe);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);
	p->pipe->dentry = dentry;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rpc_pipe_dir_object_ops gss_pipe_dir_object_ops = अणु
	.create = gss_pipe_dentry_create,
	.destroy = gss_pipe_dentry_destroy,
पूर्ण;

अटल काष्ठा gss_pipe *gss_pipe_alloc(काष्ठा rpc_clnt *clnt,
		स्थिर अक्षर *name,
		स्थिर काष्ठा rpc_pipe_ops *upcall_ops)
अणु
	काष्ठा gss_pipe *p;
	पूर्णांक err = -ENOMEM;

	p = kदो_स्मृति(माप(*p), GFP_KERNEL);
	अगर (p == शून्य)
		जाओ err;
	p->pipe = rpc_mkpipe_data(upcall_ops, RPC_PIPE_WAIT_FOR_OPEN);
	अगर (IS_ERR(p->pipe)) अणु
		err = PTR_ERR(p->pipe);
		जाओ err_मुक्त_gss_pipe;
	पूर्ण
	p->name = name;
	p->clnt = clnt;
	kref_init(&p->kref);
	rpc_init_pipe_dir_object(&p->pकरो,
			&gss_pipe_dir_object_ops,
			p);
	वापस p;
err_मुक्त_gss_pipe:
	kमुक्त(p);
err:
	वापस ERR_PTR(err);
पूर्ण

काष्ठा gss_alloc_pकरो अणु
	काष्ठा rpc_clnt *clnt;
	स्थिर अक्षर *name;
	स्थिर काष्ठा rpc_pipe_ops *upcall_ops;
पूर्ण;

अटल पूर्णांक gss_pipe_match_pकरो(काष्ठा rpc_pipe_dir_object *pकरो, व्योम *data)
अणु
	काष्ठा gss_pipe *gss_pipe;
	काष्ठा gss_alloc_pकरो *args = data;

	अगर (pकरो->pकरो_ops != &gss_pipe_dir_object_ops)
		वापस 0;
	gss_pipe = container_of(pकरो, काष्ठा gss_pipe, pकरो);
	अगर (म_भेद(gss_pipe->name, args->name) != 0)
		वापस 0;
	अगर (!kref_get_unless_zero(&gss_pipe->kref))
		वापस 0;
	वापस 1;
पूर्ण

अटल काष्ठा rpc_pipe_dir_object *gss_pipe_alloc_pकरो(व्योम *data)
अणु
	काष्ठा gss_pipe *gss_pipe;
	काष्ठा gss_alloc_pकरो *args = data;

	gss_pipe = gss_pipe_alloc(args->clnt, args->name, args->upcall_ops);
	अगर (!IS_ERR(gss_pipe))
		वापस &gss_pipe->pकरो;
	वापस शून्य;
पूर्ण

अटल काष्ठा gss_pipe *gss_pipe_get(काष्ठा rpc_clnt *clnt,
		स्थिर अक्षर *name,
		स्थिर काष्ठा rpc_pipe_ops *upcall_ops)
अणु
	काष्ठा net *net = rpc_net_ns(clnt);
	काष्ठा rpc_pipe_dir_object *pकरो;
	काष्ठा gss_alloc_pकरो args = अणु
		.clnt = clnt,
		.name = name,
		.upcall_ops = upcall_ops,
	पूर्ण;

	pकरो = rpc_find_or_alloc_pipe_dir_object(net,
			&clnt->cl_pipedir_objects,
			gss_pipe_match_pकरो,
			gss_pipe_alloc_pकरो,
			&args);
	अगर (pकरो != शून्य)
		वापस container_of(pकरो, काष्ठा gss_pipe, pकरो);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम __gss_pipe_मुक्त(काष्ठा gss_pipe *p)
अणु
	काष्ठा rpc_clnt *clnt = p->clnt;
	काष्ठा net *net = rpc_net_ns(clnt);

	rpc_हटाओ_pipe_dir_object(net,
			&clnt->cl_pipedir_objects,
			&p->pकरो);
	rpc_destroy_pipe_data(p->pipe);
	kमुक्त(p);
पूर्ण

अटल व्योम __gss_pipe_release(काष्ठा kref *kref)
अणु
	काष्ठा gss_pipe *p = container_of(kref, काष्ठा gss_pipe, kref);

	__gss_pipe_मुक्त(p);
पूर्ण

अटल व्योम gss_pipe_मुक्त(काष्ठा gss_pipe *p)
अणु
	अगर (p != शून्य)
		kref_put(&p->kref, __gss_pipe_release);
पूर्ण

/*
 * NOTE: we have the opportunity to use dअगरferent
 * parameters based on the input flavor (which must be a pseuकरोflavor)
 */
अटल काष्ठा gss_auth *
gss_create_new(स्थिर काष्ठा rpc_auth_create_args *args, काष्ठा rpc_clnt *clnt)
अणु
	rpc_authflavor_t flavor = args->pseuकरोflavor;
	काष्ठा gss_auth *gss_auth;
	काष्ठा gss_pipe *gss_pipe;
	काष्ठा rpc_auth * auth;
	पूर्णांक err = -ENOMEM; /* XXX? */

	अगर (!try_module_get(THIS_MODULE))
		वापस ERR_PTR(err);
	अगर (!(gss_auth = kदो_स्मृति(माप(*gss_auth), GFP_KERNEL)))
		जाओ out_dec;
	INIT_HLIST_NODE(&gss_auth->hash);
	gss_auth->target_name = शून्य;
	अगर (args->target_name) अणु
		gss_auth->target_name = kstrdup(args->target_name, GFP_KERNEL);
		अगर (gss_auth->target_name == शून्य)
			जाओ err_मुक्त;
	पूर्ण
	gss_auth->client = clnt;
	gss_auth->net = get_net(rpc_net_ns(clnt));
	err = -EINVAL;
	gss_auth->mech = gss_mech_get_by_pseuकरोflavor(flavor);
	अगर (!gss_auth->mech)
		जाओ err_put_net;
	gss_auth->service = gss_pseuकरोflavor_to_service(gss_auth->mech, flavor);
	अगर (gss_auth->service == 0)
		जाओ err_put_mech;
	अगर (!gssd_running(gss_auth->net))
		जाओ err_put_mech;
	auth = &gss_auth->rpc_auth;
	auth->au_cslack = GSS_CRED_SLACK >> 2;
	auth->au_rslack = GSS_KRB5_MAX_SLACK_NEEDED >> 2;
	auth->au_verfsize = GSS_VERF_SLACK >> 2;
	auth->au_ralign = GSS_VERF_SLACK >> 2;
	__set_bit(RPCAUTH_AUTH_UPDATE_SLACK, &auth->au_flags);
	auth->au_ops = &authgss_ops;
	auth->au_flavor = flavor;
	अगर (gss_pseuकरोflavor_to_datatouch(gss_auth->mech, flavor))
		__set_bit(RPCAUTH_AUTH_DATATOUCH, &auth->au_flags);
	refcount_set(&auth->au_count, 1);
	kref_init(&gss_auth->kref);

	err = rpcauth_init_credcache(auth);
	अगर (err)
		जाओ err_put_mech;
	/*
	 * Note: अगर we created the old pipe first, then someone who
	 * examined the directory at the right moment might conclude
	 * that we supported only the old pipe.  So we instead create
	 * the new pipe first.
	 */
	gss_pipe = gss_pipe_get(clnt, "gssd", &gss_upcall_ops_v1);
	अगर (IS_ERR(gss_pipe)) अणु
		err = PTR_ERR(gss_pipe);
		जाओ err_destroy_credcache;
	पूर्ण
	gss_auth->gss_pipe[1] = gss_pipe;

	gss_pipe = gss_pipe_get(clnt, gss_auth->mech->gm_name,
			&gss_upcall_ops_v0);
	अगर (IS_ERR(gss_pipe)) अणु
		err = PTR_ERR(gss_pipe);
		जाओ err_destroy_pipe_1;
	पूर्ण
	gss_auth->gss_pipe[0] = gss_pipe;

	वापस gss_auth;
err_destroy_pipe_1:
	gss_pipe_मुक्त(gss_auth->gss_pipe[1]);
err_destroy_credcache:
	rpcauth_destroy_credcache(auth);
err_put_mech:
	gss_mech_put(gss_auth->mech);
err_put_net:
	put_net(gss_auth->net);
err_मुक्त:
	kमुक्त(gss_auth->target_name);
	kमुक्त(gss_auth);
out_dec:
	module_put(THIS_MODULE);
	trace_rpcgss_createauth(flavor, err);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
gss_मुक्त(काष्ठा gss_auth *gss_auth)
अणु
	gss_pipe_मुक्त(gss_auth->gss_pipe[0]);
	gss_pipe_मुक्त(gss_auth->gss_pipe[1]);
	gss_mech_put(gss_auth->mech);
	put_net(gss_auth->net);
	kमुक्त(gss_auth->target_name);

	kमुक्त(gss_auth);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम
gss_मुक्त_callback(काष्ठा kref *kref)
अणु
	काष्ठा gss_auth *gss_auth = container_of(kref, काष्ठा gss_auth, kref);

	gss_मुक्त(gss_auth);
पूर्ण

अटल व्योम
gss_put_auth(काष्ठा gss_auth *gss_auth)
अणु
	kref_put(&gss_auth->kref, gss_मुक्त_callback);
पूर्ण

अटल व्योम
gss_destroy(काष्ठा rpc_auth *auth)
अणु
	काष्ठा gss_auth *gss_auth = container_of(auth,
			काष्ठा gss_auth, rpc_auth);

	अगर (hash_hashed(&gss_auth->hash)) अणु
		spin_lock(&gss_auth_hash_lock);
		hash_del(&gss_auth->hash);
		spin_unlock(&gss_auth_hash_lock);
	पूर्ण

	gss_pipe_मुक्त(gss_auth->gss_pipe[0]);
	gss_auth->gss_pipe[0] = शून्य;
	gss_pipe_मुक्त(gss_auth->gss_pipe[1]);
	gss_auth->gss_pipe[1] = शून्य;
	rpcauth_destroy_credcache(auth);

	gss_put_auth(gss_auth);
पूर्ण

/*
 * Auths may be shared between rpc clients that were cloned from a
 * common client with the same xprt, अगर they also share the flavor and
 * target_name.
 *
 * The auth is looked up from the oldest parent sharing the same
 * cl_xprt, and the auth itself references only that common parent
 * (which is guaranteed to last as दीर्घ as any of its descendants).
 */
अटल काष्ठा gss_auth *
gss_auth_find_or_add_hashed(स्थिर काष्ठा rpc_auth_create_args *args,
		काष्ठा rpc_clnt *clnt,
		काष्ठा gss_auth *new)
अणु
	काष्ठा gss_auth *gss_auth;
	अचिन्हित दीर्घ hashval = (अचिन्हित दीर्घ)clnt;

	spin_lock(&gss_auth_hash_lock);
	hash_क्रम_each_possible(gss_auth_hash_table,
			gss_auth,
			hash,
			hashval) अणु
		अगर (gss_auth->client != clnt)
			जारी;
		अगर (gss_auth->rpc_auth.au_flavor != args->pseuकरोflavor)
			जारी;
		अगर (gss_auth->target_name != args->target_name) अणु
			अगर (gss_auth->target_name == शून्य)
				जारी;
			अगर (args->target_name == शून्य)
				जारी;
			अगर (म_भेद(gss_auth->target_name, args->target_name))
				जारी;
		पूर्ण
		अगर (!refcount_inc_not_zero(&gss_auth->rpc_auth.au_count))
			जारी;
		जाओ out;
	पूर्ण
	अगर (new)
		hash_add(gss_auth_hash_table, &new->hash, hashval);
	gss_auth = new;
out:
	spin_unlock(&gss_auth_hash_lock);
	वापस gss_auth;
पूर्ण

अटल काष्ठा gss_auth *
gss_create_hashed(स्थिर काष्ठा rpc_auth_create_args *args,
		  काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा gss_auth *gss_auth;
	काष्ठा gss_auth *new;

	gss_auth = gss_auth_find_or_add_hashed(args, clnt, शून्य);
	अगर (gss_auth != शून्य)
		जाओ out;
	new = gss_create_new(args, clnt);
	अगर (IS_ERR(new))
		वापस new;
	gss_auth = gss_auth_find_or_add_hashed(args, clnt, new);
	अगर (gss_auth != new)
		gss_destroy(&new->rpc_auth);
out:
	वापस gss_auth;
पूर्ण

अटल काष्ठा rpc_auth *
gss_create(स्थिर काष्ठा rpc_auth_create_args *args, काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा gss_auth *gss_auth;
	काष्ठा rpc_xprt_चयन *xps = rcu_access_poपूर्णांकer(clnt->cl_xpi.xpi_xpचयन);

	जबतक (clnt != clnt->cl_parent) अणु
		काष्ठा rpc_clnt *parent = clnt->cl_parent;
		/* Find the original parent क्रम this transport */
		अगर (rcu_access_poपूर्णांकer(parent->cl_xpi.xpi_xpचयन) != xps)
			अवरोध;
		clnt = parent;
	पूर्ण

	gss_auth = gss_create_hashed(args, clnt);
	अगर (IS_ERR(gss_auth))
		वापस ERR_CAST(gss_auth);
	वापस &gss_auth->rpc_auth;
पूर्ण

अटल काष्ठा gss_cred *
gss_dup_cred(काष्ठा gss_auth *gss_auth, काष्ठा gss_cred *gss_cred)
अणु
	काष्ठा gss_cred *new;

	/* Make a copy of the cred so that we can reference count it */
	new = kzalloc(माप(*gss_cred), GFP_NOFS);
	अगर (new) अणु
		काष्ठा auth_cred acred = अणु
			.cred = gss_cred->gc_base.cr_cred,
		पूर्ण;
		काष्ठा gss_cl_ctx *ctx =
			rcu_dereference_रक्षित(gss_cred->gc_ctx, 1);

		rpcauth_init_cred(&new->gc_base, &acred,
				&gss_auth->rpc_auth,
				&gss_nullops);
		new->gc_base.cr_flags = 1UL << RPCAUTH_CRED_UPTODATE;
		new->gc_service = gss_cred->gc_service;
		new->gc_principal = gss_cred->gc_principal;
		kref_get(&gss_auth->kref);
		rcu_assign_poपूर्णांकer(new->gc_ctx, ctx);
		gss_get_ctx(ctx);
	पूर्ण
	वापस new;
पूर्ण

/*
 * gss_send_destroy_context will cause the RPCSEC_GSS to send a शून्य RPC call
 * to the server with the GSS control procedure field set to
 * RPC_GSS_PROC_DESTROY. This should normally cause the server to release
 * all RPCSEC_GSS state associated with that context.
 */
अटल व्योम
gss_send_destroy_context(काष्ठा rpc_cred *cred)
अणु
	काष्ठा gss_cred *gss_cred = container_of(cred, काष्ठा gss_cred, gc_base);
	काष्ठा gss_auth *gss_auth = container_of(cred->cr_auth, काष्ठा gss_auth, rpc_auth);
	काष्ठा gss_cl_ctx *ctx = rcu_dereference_रक्षित(gss_cred->gc_ctx, 1);
	काष्ठा gss_cred *new;
	काष्ठा rpc_task *task;

	new = gss_dup_cred(gss_auth, gss_cred);
	अगर (new) अणु
		ctx->gc_proc = RPC_GSS_PROC_DESTROY;

		trace_rpcgss_ctx_destroy(gss_cred);
		task = rpc_call_null(gss_auth->client, &new->gc_base,
				     RPC_TASK_ASYNC);
		अगर (!IS_ERR(task))
			rpc_put_task(task);

		put_rpccred(&new->gc_base);
	पूर्ण
पूर्ण

/* gss_destroy_cred (and gss_मुक्त_ctx) are used to clean up after failure
 * to create a new cred or context, so they check that things have been
 * allocated beक्रमe मुक्तing them. */
अटल व्योम
gss_करो_मुक्त_ctx(काष्ठा gss_cl_ctx *ctx)
अणु
	gss_delete_sec_context(&ctx->gc_gss_ctx);
	kमुक्त(ctx->gc_wire_ctx.data);
	kमुक्त(ctx->gc_acceptor.data);
	kमुक्त(ctx);
पूर्ण

अटल व्योम
gss_मुक्त_ctx_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा gss_cl_ctx *ctx = container_of(head, काष्ठा gss_cl_ctx, gc_rcu);
	gss_करो_मुक्त_ctx(ctx);
पूर्ण

अटल व्योम
gss_मुक्त_ctx(काष्ठा gss_cl_ctx *ctx)
अणु
	call_rcu(&ctx->gc_rcu, gss_मुक्त_ctx_callback);
पूर्ण

अटल व्योम
gss_मुक्त_cred(काष्ठा gss_cred *gss_cred)
अणु
	kमुक्त(gss_cred);
पूर्ण

अटल व्योम
gss_मुक्त_cred_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा gss_cred *gss_cred = container_of(head, काष्ठा gss_cred, gc_base.cr_rcu);
	gss_मुक्त_cred(gss_cred);
पूर्ण

अटल व्योम
gss_destroy_nullcred(काष्ठा rpc_cred *cred)
अणु
	काष्ठा gss_cred *gss_cred = container_of(cred, काष्ठा gss_cred, gc_base);
	काष्ठा gss_auth *gss_auth = container_of(cred->cr_auth, काष्ठा gss_auth, rpc_auth);
	काष्ठा gss_cl_ctx *ctx = rcu_dereference_रक्षित(gss_cred->gc_ctx, 1);

	RCU_INIT_POINTER(gss_cred->gc_ctx, शून्य);
	put_cred(cred->cr_cred);
	call_rcu(&cred->cr_rcu, gss_मुक्त_cred_callback);
	अगर (ctx)
		gss_put_ctx(ctx);
	gss_put_auth(gss_auth);
पूर्ण

अटल व्योम
gss_destroy_cred(काष्ठा rpc_cred *cred)
अणु
	अगर (test_and_clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags) != 0)
		gss_send_destroy_context(cred);
	gss_destroy_nullcred(cred);
पूर्ण

अटल पूर्णांक
gss_hash_cred(काष्ठा auth_cred *acred, अचिन्हित पूर्णांक hashbits)
अणु
	वापस hash_64(from_kuid(&init_user_ns, acred->cred->fsuid), hashbits);
पूर्ण

/*
 * Lookup RPCSEC_GSS cred क्रम the current process
 */
अटल काष्ठा rpc_cred *
gss_lookup_cred(काष्ठा rpc_auth *auth, काष्ठा auth_cred *acred, पूर्णांक flags)
अणु
	वापस rpcauth_lookup_credcache(auth, acred, flags, GFP_NOFS);
पूर्ण

अटल काष्ठा rpc_cred *
gss_create_cred(काष्ठा rpc_auth *auth, काष्ठा auth_cred *acred, पूर्णांक flags, gfp_t gfp)
अणु
	काष्ठा gss_auth *gss_auth = container_of(auth, काष्ठा gss_auth, rpc_auth);
	काष्ठा gss_cred	*cred = शून्य;
	पूर्णांक err = -ENOMEM;

	अगर (!(cred = kzalloc(माप(*cred), gfp)))
		जाओ out_err;

	rpcauth_init_cred(&cred->gc_base, acred, auth, &gss_creकरोps);
	/*
	 * Note: in order to क्रमce a call to call_refresh(), we deliberately
	 * fail to flag the credential as RPCAUTH_CRED_UPTODATE.
	 */
	cred->gc_base.cr_flags = 1UL << RPCAUTH_CRED_NEW;
	cred->gc_service = gss_auth->service;
	cred->gc_principal = acred->principal;
	kref_get(&gss_auth->kref);
	वापस &cred->gc_base;

out_err:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
gss_cred_init(काष्ठा rpc_auth *auth, काष्ठा rpc_cred *cred)
अणु
	काष्ठा gss_auth *gss_auth = container_of(auth, काष्ठा gss_auth, rpc_auth);
	काष्ठा gss_cred *gss_cred = container_of(cred,काष्ठा gss_cred, gc_base);
	पूर्णांक err;

	करो अणु
		err = gss_create_upcall(gss_auth, gss_cred);
	पूर्ण जबतक (err == -EAGAIN);
	वापस err;
पूर्ण

अटल अक्षर *
gss_stringअगरy_acceptor(काष्ठा rpc_cred *cred)
अणु
	अक्षर *string = शून्य;
	काष्ठा gss_cred *gss_cred = container_of(cred, काष्ठा gss_cred, gc_base);
	काष्ठा gss_cl_ctx *ctx;
	अचिन्हित पूर्णांक len;
	काष्ठा xdr_netobj *acceptor;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(gss_cred->gc_ctx);
	अगर (!ctx)
		जाओ out;

	len = ctx->gc_acceptor.len;
	rcu_पढ़ो_unlock();

	/* no poपूर्णांक अगर there's no string */
	अगर (!len)
		वापस शून्य;
पुनः_स्मृति:
	string = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!string)
		वापस शून्य;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(gss_cred->gc_ctx);

	/* did the ctx disappear or was it replaced by one with no acceptor? */
	अगर (!ctx || !ctx->gc_acceptor.len) अणु
		kमुक्त(string);
		string = शून्य;
		जाओ out;
	पूर्ण

	acceptor = &ctx->gc_acceptor;

	/*
	 * Did we find a new acceptor that's दीर्घer than the original? Allocate
	 * a दीर्घer buffer and try again.
	 */
	अगर (len < acceptor->len) अणु
		len = acceptor->len;
		rcu_पढ़ो_unlock();
		kमुक्त(string);
		जाओ पुनः_स्मृति;
	पूर्ण

	स_नकल(string, acceptor->data, acceptor->len);
	string[acceptor->len] = '\0';
out:
	rcu_पढ़ो_unlock();
	वापस string;
पूर्ण

/*
 * Returns -EACCES अगर GSS context is शून्य or will expire within the
 * समयout (miliseconds)
 */
अटल पूर्णांक
gss_key_समयout(काष्ठा rpc_cred *rc)
अणु
	काष्ठा gss_cred *gss_cred = container_of(rc, काष्ठा gss_cred, gc_base);
	काष्ठा gss_cl_ctx *ctx;
	अचिन्हित दीर्घ समयout = jअगरfies + (gss_key_expire_समयo * HZ);
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(gss_cred->gc_ctx);
	अगर (!ctx || समय_after(समयout, ctx->gc_expiry))
		ret = -EACCES;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक
gss_match(काष्ठा auth_cred *acred, काष्ठा rpc_cred *rc, पूर्णांक flags)
अणु
	काष्ठा gss_cred *gss_cred = container_of(rc, काष्ठा gss_cred, gc_base);
	काष्ठा gss_cl_ctx *ctx;
	पूर्णांक ret;

	अगर (test_bit(RPCAUTH_CRED_NEW, &rc->cr_flags))
		जाओ out;
	/* Don't match with creds that have expired. */
	rcu_पढ़ो_lock();
	ctx = rcu_dereference(gss_cred->gc_ctx);
	अगर (!ctx || समय_after(jअगरfies, ctx->gc_expiry)) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (!test_bit(RPCAUTH_CRED_UPTODATE, &rc->cr_flags))
		वापस 0;
out:
	अगर (acred->principal != शून्य) अणु
		अगर (gss_cred->gc_principal == शून्य)
			वापस 0;
		ret = म_भेद(acred->principal, gss_cred->gc_principal) == 0;
	पूर्ण अन्यथा अणु
		अगर (gss_cred->gc_principal != शून्य)
			वापस 0;
		ret = uid_eq(rc->cr_cred->fsuid, acred->cred->fsuid);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Marshal credentials.
 *
 * The expensive part is computing the verअगरier. We can't cache a
 * pre-computed version of the verअगरier because the seqno, which
 * is dअगरferent every समय, is included in the MIC.
 */
अटल पूर्णांक gss_marshal(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_cred *cred = req->rq_cred;
	काष्ठा gss_cred	*gss_cred = container_of(cred, काष्ठा gss_cred,
						 gc_base);
	काष्ठा gss_cl_ctx	*ctx = gss_cred_get_ctx(cred);
	__be32		*p, *cred_len;
	u32             maj_stat = 0;
	काष्ठा xdr_netobj mic;
	काष्ठा kvec	iov;
	काष्ठा xdr_buf	verf_buf;
	पूर्णांक status;

	/* Credential */

	p = xdr_reserve_space(xdr, 7 * माप(*p) +
			      ctx->gc_wire_ctx.len);
	अगर (!p)
		जाओ marshal_failed;
	*p++ = rpc_auth_gss;
	cred_len = p++;

	spin_lock(&ctx->gc_seq_lock);
	req->rq_seqno = (ctx->gc_seq < MAXSEQ) ? ctx->gc_seq++ : MAXSEQ;
	spin_unlock(&ctx->gc_seq_lock);
	अगर (req->rq_seqno == MAXSEQ)
		जाओ expired;
	trace_rpcgss_seqno(task);

	*p++ = cpu_to_be32(RPC_GSS_VERSION);
	*p++ = cpu_to_be32(ctx->gc_proc);
	*p++ = cpu_to_be32(req->rq_seqno);
	*p++ = cpu_to_be32(gss_cred->gc_service);
	p = xdr_encode_netobj(p, &ctx->gc_wire_ctx);
	*cred_len = cpu_to_be32((p - (cred_len + 1)) << 2);

	/* Verअगरier */

	/* We compute the checksum क्रम the verअगरier over the xdr-encoded bytes
	 * starting with the xid and ending at the end of the credential: */
	iov.iov_base = req->rq_snd_buf.head[0].iov_base;
	iov.iov_len = (u8 *)p - (u8 *)iov.iov_base;
	xdr_buf_from_iov(&iov, &verf_buf);

	p = xdr_reserve_space(xdr, माप(*p));
	अगर (!p)
		जाओ marshal_failed;
	*p++ = rpc_auth_gss;
	mic.data = (u8 *)(p + 1);
	maj_stat = gss_get_mic(ctx->gc_gss_ctx, &verf_buf, &mic);
	अगर (maj_stat == GSS_S_CONTEXT_EXPIRED)
		जाओ expired;
	अन्यथा अगर (maj_stat != 0)
		जाओ bad_mic;
	अगर (xdr_stream_encode_opaque_अंतरभूत(xdr, (व्योम **)&p, mic.len) < 0)
		जाओ marshal_failed;
	status = 0;
out:
	gss_put_ctx(ctx);
	वापस status;
expired:
	clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	status = -EKEYEXPIRED;
	जाओ out;
marshal_failed:
	status = -EMSGSIZE;
	जाओ out;
bad_mic:
	trace_rpcgss_get_mic(task, maj_stat);
	status = -EIO;
	जाओ out;
पूर्ण

अटल पूर्णांक gss_renew_cred(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_cred *oldcred = task->tk_rqstp->rq_cred;
	काष्ठा gss_cred *gss_cred = container_of(oldcred,
						 काष्ठा gss_cred,
						 gc_base);
	काष्ठा rpc_auth *auth = oldcred->cr_auth;
	काष्ठा auth_cred acred = अणु
		.cred = oldcred->cr_cred,
		.principal = gss_cred->gc_principal,
	पूर्ण;
	काष्ठा rpc_cred *new;

	new = gss_lookup_cred(auth, &acred, RPCAUTH_LOOKUP_NEW);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);

	task->tk_rqstp->rq_cred = new;
	put_rpccred(oldcred);
	वापस 0;
पूर्ण

अटल पूर्णांक gss_cred_is_negative_entry(काष्ठा rpc_cred *cred)
अणु
	अगर (test_bit(RPCAUTH_CRED_NEGATIVE, &cred->cr_flags)) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		अचिन्हित दीर्घ begin, expire;
		काष्ठा gss_cred *gss_cred;

		gss_cred = container_of(cred, काष्ठा gss_cred, gc_base);
		begin = gss_cred->gc_upcall_बारtamp;
		expire = begin + gss_expired_cred_retry_delay * HZ;

		अगर (समय_in_range_खोलो(now, begin, expire))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
* Refresh credentials. XXX - finish
*/
अटल पूर्णांक
gss_refresh(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_cred *cred = task->tk_rqstp->rq_cred;
	पूर्णांक ret = 0;

	अगर (gss_cred_is_negative_entry(cred))
		वापस -EKEYEXPIRED;

	अगर (!test_bit(RPCAUTH_CRED_NEW, &cred->cr_flags) &&
			!test_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags)) अणु
		ret = gss_renew_cred(task);
		अगर (ret < 0)
			जाओ out;
		cred = task->tk_rqstp->rq_cred;
	पूर्ण

	अगर (test_bit(RPCAUTH_CRED_NEW, &cred->cr_flags))
		ret = gss_refresh_upcall(task);
out:
	वापस ret;
पूर्ण

/* Dummy refresh routine: used only when destroying the context */
अटल पूर्णांक
gss_refresh_null(काष्ठा rpc_task *task)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
gss_validate(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_cred *cred = task->tk_rqstp->rq_cred;
	काष्ठा gss_cl_ctx *ctx = gss_cred_get_ctx(cred);
	__be32		*p, *seq = शून्य;
	काष्ठा kvec	iov;
	काष्ठा xdr_buf	verf_buf;
	काष्ठा xdr_netobj mic;
	u32		len, maj_stat;
	पूर्णांक		status;

	p = xdr_अंतरभूत_decode(xdr, 2 * माप(*p));
	अगर (!p)
		जाओ validate_failed;
	अगर (*p++ != rpc_auth_gss)
		जाओ validate_failed;
	len = be32_to_cpup(p);
	अगर (len > RPC_MAX_AUTH_SIZE)
		जाओ validate_failed;
	p = xdr_अंतरभूत_decode(xdr, len);
	अगर (!p)
		जाओ validate_failed;

	seq = kदो_स्मृति(4, GFP_NOFS);
	अगर (!seq)
		जाओ validate_failed;
	*seq = cpu_to_be32(task->tk_rqstp->rq_seqno);
	iov.iov_base = seq;
	iov.iov_len = 4;
	xdr_buf_from_iov(&iov, &verf_buf);
	mic.data = (u8 *)p;
	mic.len = len;
	maj_stat = gss_verअगरy_mic(ctx->gc_gss_ctx, &verf_buf, &mic);
	अगर (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	अगर (maj_stat)
		जाओ bad_mic;

	/* We leave it to unwrap to calculate au_rslack. For now we just
	 * calculate the length of the verअगरier: */
	अगर (test_bit(RPCAUTH_AUTH_UPDATE_SLACK, &cred->cr_auth->au_flags))
		cred->cr_auth->au_verfsize = XDR_QUADLEN(len) + 2;
	status = 0;
out:
	gss_put_ctx(ctx);
	kमुक्त(seq);
	वापस status;

validate_failed:
	status = -EIO;
	जाओ out;
bad_mic:
	trace_rpcgss_verअगरy_mic(task, maj_stat);
	status = -EACCES;
	जाओ out;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
gss_wrap_req_पूर्णांकeg(काष्ठा rpc_cred *cred, काष्ठा gss_cl_ctx *ctx,
		   काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_rqst *rqstp = task->tk_rqstp;
	काष्ठा xdr_buf पूर्णांकeg_buf, *snd_buf = &rqstp->rq_snd_buf;
	काष्ठा xdr_netobj mic;
	__be32 *p, *पूर्णांकeg_len;
	u32 offset, maj_stat;

	p = xdr_reserve_space(xdr, 2 * माप(*p));
	अगर (!p)
		जाओ wrap_failed;
	पूर्णांकeg_len = p++;
	*p = cpu_to_be32(rqstp->rq_seqno);

	अगर (rpcauth_wrap_req_encode(task, xdr))
		जाओ wrap_failed;

	offset = (u8 *)p - (u8 *)snd_buf->head[0].iov_base;
	अगर (xdr_buf_subsegment(snd_buf, &पूर्णांकeg_buf,
				offset, snd_buf->len - offset))
		जाओ wrap_failed;
	*पूर्णांकeg_len = cpu_to_be32(पूर्णांकeg_buf.len);

	p = xdr_reserve_space(xdr, 0);
	अगर (!p)
		जाओ wrap_failed;
	mic.data = (u8 *)(p + 1);
	maj_stat = gss_get_mic(ctx->gc_gss_ctx, &पूर्णांकeg_buf, &mic);
	अगर (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	अन्यथा अगर (maj_stat)
		जाओ bad_mic;
	/* Check that the trailing MIC fit in the buffer, after the fact */
	अगर (xdr_stream_encode_opaque_अंतरभूत(xdr, (व्योम **)&p, mic.len) < 0)
		जाओ wrap_failed;
	वापस 0;
wrap_failed:
	वापस -EMSGSIZE;
bad_mic:
	trace_rpcgss_get_mic(task, maj_stat);
	वापस -EIO;
पूर्ण

अटल व्योम
priv_release_snd_buf(काष्ठा rpc_rqst *rqstp)
अणु
	पूर्णांक i;

	क्रम (i=0; i < rqstp->rq_enc_pages_num; i++)
		__मुक्त_page(rqstp->rq_enc_pages[i]);
	kमुक्त(rqstp->rq_enc_pages);
	rqstp->rq_release_snd_buf = शून्य;
पूर्ण

अटल पूर्णांक
alloc_enc_pages(काष्ठा rpc_rqst *rqstp)
अणु
	काष्ठा xdr_buf *snd_buf = &rqstp->rq_snd_buf;
	पूर्णांक first, last, i;

	अगर (rqstp->rq_release_snd_buf)
		rqstp->rq_release_snd_buf(rqstp);

	अगर (snd_buf->page_len == 0) अणु
		rqstp->rq_enc_pages_num = 0;
		वापस 0;
	पूर्ण

	first = snd_buf->page_base >> PAGE_SHIFT;
	last = (snd_buf->page_base + snd_buf->page_len - 1) >> PAGE_SHIFT;
	rqstp->rq_enc_pages_num = last - first + 1 + 1;
	rqstp->rq_enc_pages
		= kदो_स्मृति_array(rqstp->rq_enc_pages_num,
				माप(काष्ठा page *),
				GFP_NOFS);
	अगर (!rqstp->rq_enc_pages)
		जाओ out;
	क्रम (i=0; i < rqstp->rq_enc_pages_num; i++) अणु
		rqstp->rq_enc_pages[i] = alloc_page(GFP_NOFS);
		अगर (rqstp->rq_enc_pages[i] == शून्य)
			जाओ out_मुक्त;
	पूर्ण
	rqstp->rq_release_snd_buf = priv_release_snd_buf;
	वापस 0;
out_मुक्त:
	rqstp->rq_enc_pages_num = i;
	priv_release_snd_buf(rqstp);
out:
	वापस -EAGAIN;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
gss_wrap_req_priv(काष्ठा rpc_cred *cred, काष्ठा gss_cl_ctx *ctx,
		  काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_rqst *rqstp = task->tk_rqstp;
	काष्ठा xdr_buf	*snd_buf = &rqstp->rq_snd_buf;
	u32		pad, offset, maj_stat;
	पूर्णांक		status;
	__be32		*p, *opaque_len;
	काष्ठा page	**inpages;
	पूर्णांक		first;
	काष्ठा kvec	*iov;

	status = -EIO;
	p = xdr_reserve_space(xdr, 2 * माप(*p));
	अगर (!p)
		जाओ wrap_failed;
	opaque_len = p++;
	*p = cpu_to_be32(rqstp->rq_seqno);

	अगर (rpcauth_wrap_req_encode(task, xdr))
		जाओ wrap_failed;

	status = alloc_enc_pages(rqstp);
	अगर (unlikely(status))
		जाओ wrap_failed;
	first = snd_buf->page_base >> PAGE_SHIFT;
	inpages = snd_buf->pages + first;
	snd_buf->pages = rqstp->rq_enc_pages;
	snd_buf->page_base -= first << PAGE_SHIFT;
	/*
	 * Move the tail पूर्णांकo its own page, in हाल gss_wrap needs
	 * more space in the head when wrapping.
	 *
	 * Still... Why can't gss_wrap just slide the tail करोwn?
	 */
	अगर (snd_buf->page_len || snd_buf->tail[0].iov_len) अणु
		अक्षर *पंचांगp;

		पंचांगp = page_address(rqstp->rq_enc_pages[rqstp->rq_enc_pages_num - 1]);
		स_नकल(पंचांगp, snd_buf->tail[0].iov_base, snd_buf->tail[0].iov_len);
		snd_buf->tail[0].iov_base = पंचांगp;
	पूर्ण
	offset = (u8 *)p - (u8 *)snd_buf->head[0].iov_base;
	maj_stat = gss_wrap(ctx->gc_gss_ctx, offset, snd_buf, inpages);
	/* slack space should prevent this ever happening: */
	अगर (unlikely(snd_buf->len > snd_buf->buflen))
		जाओ wrap_failed;
	/* We're assuming that when GSS_S_CONTEXT_EXPIRED, the encryption was
	 * करोne anyway, so it's safe to put the request on the wire: */
	अगर (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	अन्यथा अगर (maj_stat)
		जाओ bad_wrap;

	*opaque_len = cpu_to_be32(snd_buf->len - offset);
	/* guess whether the pad goes पूर्णांकo the head or the tail: */
	अगर (snd_buf->page_len || snd_buf->tail[0].iov_len)
		iov = snd_buf->tail;
	अन्यथा
		iov = snd_buf->head;
	p = iov->iov_base + iov->iov_len;
	pad = xdr_pad_size(snd_buf->len - offset);
	स_रखो(p, 0, pad);
	iov->iov_len += pad;
	snd_buf->len += pad;

	वापस 0;
wrap_failed:
	वापस status;
bad_wrap:
	trace_rpcgss_wrap(task, maj_stat);
	वापस -EIO;
पूर्ण

अटल पूर्णांक gss_wrap_req(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_cred *cred = task->tk_rqstp->rq_cred;
	काष्ठा gss_cred	*gss_cred = container_of(cred, काष्ठा gss_cred,
			gc_base);
	काष्ठा gss_cl_ctx *ctx = gss_cred_get_ctx(cred);
	पूर्णांक status;

	status = -EIO;
	अगर (ctx->gc_proc != RPC_GSS_PROC_DATA) अणु
		/* The spec seems a little ambiguous here, but I think that not
		 * wrapping context deकाष्ठाion requests makes the most sense.
		 */
		status = rpcauth_wrap_req_encode(task, xdr);
		जाओ out;
	पूर्ण
	चयन (gss_cred->gc_service) अणु
	हाल RPC_GSS_SVC_NONE:
		status = rpcauth_wrap_req_encode(task, xdr);
		अवरोध;
	हाल RPC_GSS_SVC_INTEGRITY:
		status = gss_wrap_req_पूर्णांकeg(cred, ctx, task, xdr);
		अवरोध;
	हाल RPC_GSS_SVC_PRIVACY:
		status = gss_wrap_req_priv(cred, ctx, task, xdr);
		अवरोध;
	शेष:
		status = -EIO;
	पूर्ण
out:
	gss_put_ctx(ctx);
	वापस status;
पूर्ण

/**
 * gss_update_rslack - Possibly update RPC receive buffer size estimates
 * @task: rpc_task क्रम incoming RPC Reply being unwrapped
 * @cred: controlling rpc_cred क्रम @task
 * @beक्रमe: XDR words needed beक्रमe each RPC Reply message
 * @after: XDR words needed following each RPC Reply message
 *
 */
अटल व्योम gss_update_rslack(काष्ठा rpc_task *task, काष्ठा rpc_cred *cred,
			      अचिन्हित पूर्णांक beक्रमe, अचिन्हित पूर्णांक after)
अणु
	काष्ठा rpc_auth *auth = cred->cr_auth;

	अगर (test_and_clear_bit(RPCAUTH_AUTH_UPDATE_SLACK, &auth->au_flags)) अणु
		auth->au_ralign = auth->au_verfsize + beक्रमe;
		auth->au_rslack = auth->au_verfsize + after;
		trace_rpcgss_update_slack(task, auth);
	पूर्ण
पूर्ण

अटल पूर्णांक
gss_unwrap_resp_auth(काष्ठा rpc_task *task, काष्ठा rpc_cred *cred)
अणु
	gss_update_rslack(task, cred, 0, 0);
	वापस 0;
पूर्ण

/*
 * RFC 2203, Section 5.3.2.2
 *
 *	काष्ठा rpc_gss_पूर्णांकeg_data अणु
 *		opaque databody_पूर्णांकeg<>;
 *		opaque checksum<>;
 *	पूर्ण;
 *
 *	काष्ठा rpc_gss_data_t अणु
 *		अचिन्हित पूर्णांक seq_num;
 *		proc_req_arg_t arg;
 *	पूर्ण;
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक
gss_unwrap_resp_पूर्णांकeg(काष्ठा rpc_task *task, काष्ठा rpc_cred *cred,
		      काष्ठा gss_cl_ctx *ctx, काष्ठा rpc_rqst *rqstp,
		      काष्ठा xdr_stream *xdr)
अणु
	काष्ठा xdr_buf gss_data, *rcv_buf = &rqstp->rq_rcv_buf;
	u32 len, offset, seqno, maj_stat;
	काष्ठा xdr_netobj mic;
	पूर्णांक ret;

	ret = -EIO;
	mic.data = शून्य;

	/* opaque databody_पूर्णांकeg<>; */
	अगर (xdr_stream_decode_u32(xdr, &len))
		जाओ unwrap_failed;
	अगर (len & 3)
		जाओ unwrap_failed;
	offset = rcv_buf->len - xdr_stream_reमुख्यing(xdr);
	अगर (xdr_stream_decode_u32(xdr, &seqno))
		जाओ unwrap_failed;
	अगर (seqno != rqstp->rq_seqno)
		जाओ bad_seqno;
	अगर (xdr_buf_subsegment(rcv_buf, &gss_data, offset, len))
		जाओ unwrap_failed;

	/*
	 * The xdr_stream now poपूर्णांकs to the beginning of the
	 * upper layer payload, to be passed below to
	 * rpcauth_unwrap_resp_decode(). The checksum, which
	 * follows the upper layer payload in @rcv_buf, is
	 * located and parsed without updating the xdr_stream.
	 */

	/* opaque checksum<>; */
	offset += len;
	अगर (xdr_decode_word(rcv_buf, offset, &len))
		जाओ unwrap_failed;
	offset += माप(__be32);
	अगर (offset + len > rcv_buf->len)
		जाओ unwrap_failed;
	mic.len = len;
	mic.data = kदो_स्मृति(len, GFP_NOFS);
	अगर (!mic.data)
		जाओ unwrap_failed;
	अगर (पढ़ो_bytes_from_xdr_buf(rcv_buf, offset, mic.data, mic.len))
		जाओ unwrap_failed;

	maj_stat = gss_verअगरy_mic(ctx->gc_gss_ctx, &gss_data, &mic);
	अगर (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	अगर (maj_stat != GSS_S_COMPLETE)
		जाओ bad_mic;

	gss_update_rslack(task, cred, 2, 2 + 1 + XDR_QUADLEN(mic.len));
	ret = 0;

out:
	kमुक्त(mic.data);
	वापस ret;

unwrap_failed:
	trace_rpcgss_unwrap_failed(task);
	जाओ out;
bad_seqno:
	trace_rpcgss_bad_seqno(task, rqstp->rq_seqno, seqno);
	जाओ out;
bad_mic:
	trace_rpcgss_verअगरy_mic(task, maj_stat);
	जाओ out;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
gss_unwrap_resp_priv(काष्ठा rpc_task *task, काष्ठा rpc_cred *cred,
		     काष्ठा gss_cl_ctx *ctx, काष्ठा rpc_rqst *rqstp,
		     काष्ठा xdr_stream *xdr)
अणु
	काष्ठा xdr_buf *rcv_buf = &rqstp->rq_rcv_buf;
	काष्ठा kvec *head = rqstp->rq_rcv_buf.head;
	u32 offset, opaque_len, maj_stat;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 2 * माप(*p));
	अगर (unlikely(!p))
		जाओ unwrap_failed;
	opaque_len = be32_to_cpup(p++);
	offset = (u8 *)(p) - (u8 *)head->iov_base;
	अगर (offset + opaque_len > rcv_buf->len)
		जाओ unwrap_failed;

	maj_stat = gss_unwrap(ctx->gc_gss_ctx, offset,
			      offset + opaque_len, rcv_buf);
	अगर (maj_stat == GSS_S_CONTEXT_EXPIRED)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
	अगर (maj_stat != GSS_S_COMPLETE)
		जाओ bad_unwrap;
	/* gss_unwrap decrypted the sequence number */
	अगर (be32_to_cpup(p++) != rqstp->rq_seqno)
		जाओ bad_seqno;

	/* gss_unwrap redacts the opaque blob from the head iovec.
	 * rcv_buf has changed, thus the stream needs to be reset.
	 */
	xdr_init_decode(xdr, rcv_buf, p, rqstp);

	gss_update_rslack(task, cred, 2 + ctx->gc_gss_ctx->align,
			  2 + ctx->gc_gss_ctx->slack);

	वापस 0;
unwrap_failed:
	trace_rpcgss_unwrap_failed(task);
	वापस -EIO;
bad_seqno:
	trace_rpcgss_bad_seqno(task, rqstp->rq_seqno, be32_to_cpup(--p));
	वापस -EIO;
bad_unwrap:
	trace_rpcgss_unwrap(task, maj_stat);
	वापस -EIO;
पूर्ण

अटल bool
gss_seq_is_newer(u32 new, u32 old)
अणु
	वापस (s32)(new - old) > 0;
पूर्ण

अटल bool
gss_xmit_need_reencode(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_cred *cred = req->rq_cred;
	काष्ठा gss_cl_ctx *ctx = gss_cred_get_ctx(cred);
	u32 win, seq_xmit = 0;
	bool ret = true;

	अगर (!ctx)
		जाओ out;

	अगर (gss_seq_is_newer(req->rq_seqno, READ_ONCE(ctx->gc_seq)))
		जाओ out_ctx;

	seq_xmit = READ_ONCE(ctx->gc_seq_xmit);
	जबतक (gss_seq_is_newer(req->rq_seqno, seq_xmit)) अणु
		u32 पंचांगp = seq_xmit;

		seq_xmit = cmpxchg(&ctx->gc_seq_xmit, पंचांगp, req->rq_seqno);
		अगर (seq_xmit == पंचांगp) अणु
			ret = false;
			जाओ out_ctx;
		पूर्ण
	पूर्ण

	win = ctx->gc_win;
	अगर (win > 0)
		ret = !gss_seq_is_newer(req->rq_seqno, seq_xmit - win);

out_ctx:
	gss_put_ctx(ctx);
out:
	trace_rpcgss_need_reencode(task, seq_xmit, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
gss_unwrap_resp(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_rqst *rqstp = task->tk_rqstp;
	काष्ठा rpc_cred *cred = rqstp->rq_cred;
	काष्ठा gss_cred *gss_cred = container_of(cred, काष्ठा gss_cred,
			gc_base);
	काष्ठा gss_cl_ctx *ctx = gss_cred_get_ctx(cred);
	पूर्णांक status = -EIO;

	अगर (ctx->gc_proc != RPC_GSS_PROC_DATA)
		जाओ out_decode;
	चयन (gss_cred->gc_service) अणु
	हाल RPC_GSS_SVC_NONE:
		status = gss_unwrap_resp_auth(task, cred);
		अवरोध;
	हाल RPC_GSS_SVC_INTEGRITY:
		status = gss_unwrap_resp_पूर्णांकeg(task, cred, ctx, rqstp, xdr);
		अवरोध;
	हाल RPC_GSS_SVC_PRIVACY:
		status = gss_unwrap_resp_priv(task, cred, ctx, rqstp, xdr);
		अवरोध;
	पूर्ण
	अगर (status)
		जाओ out;

out_decode:
	status = rpcauth_unwrap_resp_decode(task, xdr);
out:
	gss_put_ctx(ctx);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा rpc_authops authgss_ops = अणु
	.owner		= THIS_MODULE,
	.au_flavor	= RPC_AUTH_GSS,
	.au_name	= "RPCSEC_GSS",
	.create		= gss_create,
	.destroy	= gss_destroy,
	.hash_cred	= gss_hash_cred,
	.lookup_cred	= gss_lookup_cred,
	.crcreate	= gss_create_cred,
	.info2flavor	= gss_mech_info2flavor,
	.flavor2info	= gss_mech_flavor2info,
पूर्ण;

अटल स्थिर काष्ठा rpc_creकरोps gss_creकरोps = अणु
	.cr_name		= "AUTH_GSS",
	.crdestroy		= gss_destroy_cred,
	.cr_init		= gss_cred_init,
	.crmatch		= gss_match,
	.crmarshal		= gss_marshal,
	.crrefresh		= gss_refresh,
	.crvalidate		= gss_validate,
	.crwrap_req		= gss_wrap_req,
	.crunwrap_resp		= gss_unwrap_resp,
	.crkey_समयout		= gss_key_समयout,
	.crstringअगरy_acceptor	= gss_stringअगरy_acceptor,
	.crneed_reencode	= gss_xmit_need_reencode,
पूर्ण;

अटल स्थिर काष्ठा rpc_creकरोps gss_nullops = अणु
	.cr_name		= "AUTH_GSS",
	.crdestroy		= gss_destroy_nullcred,
	.crmatch		= gss_match,
	.crmarshal		= gss_marshal,
	.crrefresh		= gss_refresh_null,
	.crvalidate		= gss_validate,
	.crwrap_req		= gss_wrap_req,
	.crunwrap_resp		= gss_unwrap_resp,
	.crstringअगरy_acceptor	= gss_stringअगरy_acceptor,
पूर्ण;

अटल स्थिर काष्ठा rpc_pipe_ops gss_upcall_ops_v0 = अणु
	.upcall		= gss_v0_upcall,
	.करोwncall	= gss_pipe_करोwncall,
	.destroy_msg	= gss_pipe_destroy_msg,
	.खोलो_pipe	= gss_pipe_खोलो_v0,
	.release_pipe	= gss_pipe_release,
पूर्ण;

अटल स्थिर काष्ठा rpc_pipe_ops gss_upcall_ops_v1 = अणु
	.upcall		= gss_v1_upcall,
	.करोwncall	= gss_pipe_करोwncall,
	.destroy_msg	= gss_pipe_destroy_msg,
	.खोलो_pipe	= gss_pipe_खोलो_v1,
	.release_pipe	= gss_pipe_release,
पूर्ण;

अटल __net_init पूर्णांक rpcsec_gss_init_net(काष्ठा net *net)
अणु
	वापस gss_svc_init_net(net);
पूर्ण

अटल __net_निकास व्योम rpcsec_gss_निकास_net(काष्ठा net *net)
अणु
	gss_svc_shutकरोwn_net(net);
पूर्ण

अटल काष्ठा pernet_operations rpcsec_gss_net_ops = अणु
	.init = rpcsec_gss_init_net,
	.निकास = rpcsec_gss_निकास_net,
पूर्ण;

/*
 * Initialize RPCSEC_GSS module
 */
अटल पूर्णांक __init init_rpcsec_gss(व्योम)
अणु
	पूर्णांक err = 0;

	err = rpcauth_रेजिस्टर(&authgss_ops);
	अगर (err)
		जाओ out;
	err = gss_svc_init();
	अगर (err)
		जाओ out_unरेजिस्टर;
	err = रेजिस्टर_pernet_subsys(&rpcsec_gss_net_ops);
	अगर (err)
		जाओ out_svc_निकास;
	rpc_init_रुको_queue(&pipe_version_rpc_रुकोqueue, "gss pipe version");
	वापस 0;
out_svc_निकास:
	gss_svc_shutकरोwn();
out_unरेजिस्टर:
	rpcauth_unरेजिस्टर(&authgss_ops);
out:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_rpcsec_gss(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&rpcsec_gss_net_ops);
	gss_svc_shutकरोwn();
	rpcauth_unरेजिस्टर(&authgss_ops);
	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */
पूर्ण

MODULE_ALIAS("rpc-auth-6");
MODULE_LICENSE("GPL");
module_param_named(expired_cred_retry_delay,
		   gss_expired_cred_retry_delay,
		   uपूर्णांक, 0644);
MODULE_PARM_DESC(expired_cred_retry_delay, "Timeout (in seconds) until "
		"the RPC engine retries an expired credential");

module_param_named(key_expire_समयo,
		   gss_key_expire_समयo,
		   uपूर्णांक, 0644);
MODULE_PARM_DESC(key_expire_समयo, "Time (in seconds) at the end of a "
		"credential keys lifetime where the NFS layer cleans up "
		"prior to key expiration");

module_init(init_rpcsec_gss)
module_निकास(निकास_rpcsec_gss)
