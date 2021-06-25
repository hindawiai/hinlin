<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/net/sunrpc/auth_unix.c
 *
 * UNIX-style authentication; no AUTH_SHORT support
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/mempool.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/user_namespace.h>


#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_AUTH
#पूर्ण_अगर

अटल काष्ठा rpc_auth		unix_auth;
अटल स्थिर काष्ठा rpc_creकरोps	unix_creकरोps;
अटल mempool_t		*unix_pool;

अटल काष्ठा rpc_auth *
unx_create(स्थिर काष्ठा rpc_auth_create_args *args, काष्ठा rpc_clnt *clnt)
अणु
	refcount_inc(&unix_auth.au_count);
	वापस &unix_auth;
पूर्ण

अटल व्योम
unx_destroy(काष्ठा rpc_auth *auth)
अणु
पूर्ण

/*
 * Lookup AUTH_UNIX creds क्रम current process
 */
अटल काष्ठा rpc_cred *
unx_lookup_cred(काष्ठा rpc_auth *auth, काष्ठा auth_cred *acred, पूर्णांक flags)
अणु
	काष्ठा rpc_cred *ret = mempool_alloc(unix_pool, GFP_NOFS);

	rpcauth_init_cred(ret, acred, auth, &unix_creकरोps);
	ret->cr_flags = 1UL << RPCAUTH_CRED_UPTODATE;
	वापस ret;
पूर्ण

अटल व्योम
unx_मुक्त_cred_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा rpc_cred *rpc_cred = container_of(head, काष्ठा rpc_cred, cr_rcu);

	put_cred(rpc_cred->cr_cred);
	mempool_मुक्त(rpc_cred, unix_pool);
पूर्ण

अटल व्योम
unx_destroy_cred(काष्ठा rpc_cred *cred)
अणु
	call_rcu(&cred->cr_rcu, unx_मुक्त_cred_callback);
पूर्ण

/*
 * Match credentials against current the auth_cred.
 */
अटल पूर्णांक
unx_match(काष्ठा auth_cred *acred, काष्ठा rpc_cred *cred, पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक groups = 0;
	अचिन्हित पूर्णांक i;

	अगर (cred->cr_cred == acred->cred)
		वापस 1;

	अगर (!uid_eq(cred->cr_cred->fsuid, acred->cred->fsuid) || !gid_eq(cred->cr_cred->fsgid, acred->cred->fsgid))
		वापस 0;

	अगर (acred->cred->group_info != शून्य)
		groups = acred->cred->group_info->ngroups;
	अगर (groups > UNX_NGROUPS)
		groups = UNX_NGROUPS;
	अगर (cred->cr_cred->group_info == शून्य)
		वापस groups == 0;
	अगर (groups != cred->cr_cred->group_info->ngroups)
		वापस 0;

	क्रम (i = 0; i < groups ; i++)
		अगर (!gid_eq(cred->cr_cred->group_info->gid[i], acred->cred->group_info->gid[i]))
			वापस 0;
	वापस 1;
पूर्ण

/*
 * Marshal credentials.
 * Maybe we should keep a cached credential क्रम perक्रमmance reasons.
 */
अटल पूर्णांक
unx_marshal(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_clnt	*clnt = task->tk_client;
	काष्ठा rpc_cred	*cred = task->tk_rqstp->rq_cred;
	__be32		*p, *cred_len, *gidarr_len;
	पूर्णांक		i;
	काष्ठा group_info *gi = cred->cr_cred->group_info;
	काष्ठा user_namespace *userns = clnt->cl_cred ?
		clnt->cl_cred->user_ns : &init_user_ns;

	/* Credential */

	p = xdr_reserve_space(xdr, 3 * माप(*p));
	अगर (!p)
		जाओ marshal_failed;
	*p++ = rpc_auth_unix;
	cred_len = p++;
	*p++ = xdr_zero;	/* stamp */
	अगर (xdr_stream_encode_opaque(xdr, clnt->cl_nodename,
				     clnt->cl_nodelen) < 0)
		जाओ marshal_failed;
	p = xdr_reserve_space(xdr, 3 * माप(*p));
	अगर (!p)
		जाओ marshal_failed;
	*p++ = cpu_to_be32(from_kuid_munged(userns, cred->cr_cred->fsuid));
	*p++ = cpu_to_be32(from_kgid_munged(userns, cred->cr_cred->fsgid));

	gidarr_len = p++;
	अगर (gi)
		क्रम (i = 0; i < UNX_NGROUPS && i < gi->ngroups; i++)
			*p++ = cpu_to_be32(from_kgid_munged(userns, gi->gid[i]));
	*gidarr_len = cpu_to_be32(p - gidarr_len - 1);
	*cred_len = cpu_to_be32((p - cred_len - 1) << 2);
	p = xdr_reserve_space(xdr, (p - gidarr_len - 1) << 2);
	अगर (!p)
		जाओ marshal_failed;

	/* Verअगरier */

	p = xdr_reserve_space(xdr, 2 * माप(*p));
	अगर (!p)
		जाओ marshal_failed;
	*p++ = rpc_auth_null;
	*p   = xdr_zero;

	वापस 0;

marshal_failed:
	वापस -EMSGSIZE;
पूर्ण

/*
 * Refresh credentials. This is a no-op क्रम AUTH_UNIX
 */
अटल पूर्णांक
unx_refresh(काष्ठा rpc_task *task)
अणु
	set_bit(RPCAUTH_CRED_UPTODATE, &task->tk_rqstp->rq_cred->cr_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
unx_validate(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_auth *auth = task->tk_rqstp->rq_cred->cr_auth;
	__be32 *p;
	u32 size;

	p = xdr_अंतरभूत_decode(xdr, 2 * माप(*p));
	अगर (!p)
		वापस -EIO;
	चयन (*p++) अणु
	हाल rpc_auth_null:
	हाल rpc_auth_unix:
	हाल rpc_auth_लघु:
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण
	size = be32_to_cpup(p);
	अगर (size > RPC_MAX_AUTH_SIZE)
		वापस -EIO;
	p = xdr_अंतरभूत_decode(xdr, size);
	अगर (!p)
		वापस -EIO;

	auth->au_verfsize = XDR_QUADLEN(size) + 2;
	auth->au_rslack = XDR_QUADLEN(size) + 2;
	auth->au_ralign = XDR_QUADLEN(size) + 2;
	वापस 0;
पूर्ण

पूर्णांक __init rpc_init_authunix(व्योम)
अणु
	unix_pool = mempool_create_kदो_स्मृति_pool(16, माप(काष्ठा rpc_cred));
	वापस unix_pool ? 0 : -ENOMEM;
पूर्ण

व्योम rpc_destroy_authunix(व्योम)
अणु
	mempool_destroy(unix_pool);
पूर्ण

स्थिर काष्ठा rpc_authops authunix_ops = अणु
	.owner		= THIS_MODULE,
	.au_flavor	= RPC_AUTH_UNIX,
	.au_name	= "UNIX",
	.create		= unx_create,
	.destroy	= unx_destroy,
	.lookup_cred	= unx_lookup_cred,
पूर्ण;

अटल
काष्ठा rpc_auth		unix_auth = अणु
	.au_cslack	= UNX_CALLSLACK,
	.au_rslack	= NUL_REPLYSLACK,
	.au_verfsize	= NUL_REPLYSLACK,
	.au_ops		= &authunix_ops,
	.au_flavor	= RPC_AUTH_UNIX,
	.au_count	= REFCOUNT_INIT(1),
पूर्ण;

अटल
स्थिर काष्ठा rpc_creकरोps unix_creकरोps = अणु
	.cr_name	= "AUTH_UNIX",
	.crdestroy	= unx_destroy_cred,
	.crmatch	= unx_match,
	.crmarshal	= unx_marshal,
	.crwrap_req	= rpcauth_wrap_req_encode,
	.crrefresh	= unx_refresh,
	.crvalidate	= unx_validate,
	.crunwrap_resp	= rpcauth_unwrap_resp_decode,
पूर्ण;
