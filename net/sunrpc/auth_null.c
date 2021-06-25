<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/net/sunrpc/auth_null.c
 *
 * AUTH_शून्य authentication. Really :-)
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/sunrpc/clnt.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_AUTH
#पूर्ण_अगर

अटल काष्ठा rpc_auth null_auth;
अटल काष्ठा rpc_cred null_cred;

अटल काष्ठा rpc_auth *
nul_create(स्थिर काष्ठा rpc_auth_create_args *args, काष्ठा rpc_clnt *clnt)
अणु
	refcount_inc(&null_auth.au_count);
	वापस &null_auth;
पूर्ण

अटल व्योम
nul_destroy(काष्ठा rpc_auth *auth)
अणु
पूर्ण

/*
 * Lookup शून्य creds क्रम current process
 */
अटल काष्ठा rpc_cred *
nul_lookup_cred(काष्ठा rpc_auth *auth, काष्ठा auth_cred *acred, पूर्णांक flags)
अणु
	वापस get_rpccred(&null_cred);
पूर्ण

/*
 * Destroy cred handle.
 */
अटल व्योम
nul_destroy_cred(काष्ठा rpc_cred *cred)
अणु
पूर्ण

/*
 * Match cred handle against current process
 */
अटल पूर्णांक
nul_match(काष्ठा auth_cred *acred, काष्ठा rpc_cred *cred, पूर्णांक taskflags)
अणु
	वापस 1;
पूर्ण

/*
 * Marshal credential.
 */
अटल पूर्णांक
nul_marshal(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 * माप(*p));
	अगर (!p)
		वापस -EMSGSIZE;
	/* Credential */
	*p++ = rpc_auth_null;
	*p++ = xdr_zero;
	/* Verअगरier */
	*p++ = rpc_auth_null;
	*p   = xdr_zero;
	वापस 0;
पूर्ण

/*
 * Refresh credential. This is a no-op क्रम AUTH_शून्य
 */
अटल पूर्णांक
nul_refresh(काष्ठा rpc_task *task)
अणु
	set_bit(RPCAUTH_CRED_UPTODATE, &task->tk_rqstp->rq_cred->cr_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
nul_validate(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 2 * माप(*p));
	अगर (!p)
		वापस -EIO;
	अगर (*p++ != rpc_auth_null)
		वापस -EIO;
	अगर (*p != xdr_zero)
		वापस -EIO;
	वापस 0;
पूर्ण

स्थिर काष्ठा rpc_authops authnull_ops = अणु
	.owner		= THIS_MODULE,
	.au_flavor	= RPC_AUTH_शून्य,
	.au_name	= "NULL",
	.create		= nul_create,
	.destroy	= nul_destroy,
	.lookup_cred	= nul_lookup_cred,
पूर्ण;

अटल
काष्ठा rpc_auth null_auth = अणु
	.au_cslack	= NUL_CALLSLACK,
	.au_rslack	= NUL_REPLYSLACK,
	.au_verfsize	= NUL_REPLYSLACK,
	.au_ralign	= NUL_REPLYSLACK,
	.au_ops		= &authnull_ops,
	.au_flavor	= RPC_AUTH_शून्य,
	.au_count	= REFCOUNT_INIT(1),
पूर्ण;

अटल
स्थिर काष्ठा rpc_creकरोps null_creकरोps = अणु
	.cr_name	= "AUTH_NULL",
	.crdestroy	= nul_destroy_cred,
	.crmatch	= nul_match,
	.crmarshal	= nul_marshal,
	.crwrap_req	= rpcauth_wrap_req_encode,
	.crrefresh	= nul_refresh,
	.crvalidate	= nul_validate,
	.crunwrap_resp	= rpcauth_unwrap_resp_decode,
पूर्ण;

अटल
काष्ठा rpc_cred null_cred = अणु
	.cr_lru		= LIST_HEAD_INIT(null_cred.cr_lru),
	.cr_auth	= &null_auth,
	.cr_ops		= &null_creकरोps,
	.cr_count	= REFCOUNT_INIT(2),
	.cr_flags	= 1UL << RPCAUTH_CRED_UPTODATE,
पूर्ण;
