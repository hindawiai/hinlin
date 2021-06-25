<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/auth.h
 *
 * Declarations क्रम the RPC client authentication machinery.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _LINUX_SUNRPC_AUTH_H
#घोषणा _LINUX_SUNRPC_AUTH_H

#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/xdr.h>

#समावेश <linux/atomic.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/utsname.h>

/*
 * Maximum size of AUTH_NONE authentication inक्रमmation, in XDR words.
 */
#घोषणा NUL_CALLSLACK	(4)
#घोषणा NUL_REPLYSLACK	(2)

/*
 * Size of the nodename buffer. RFC1831 specअगरies a hard limit of 255 bytes,
 * but Linux hostnames are actually limited to __NEW_UTS_LEN bytes.
 */
#घोषणा UNX_MAXNODENAME	__NEW_UTS_LEN
#घोषणा UNX_CALLSLACK	(21 + XDR_QUADLEN(UNX_MAXNODENAME))
#घोषणा UNX_NGROUPS	16

काष्ठा rpcsec_gss_info;

काष्ठा auth_cred अणु
	स्थिर काष्ठा cred *cred;
	स्थिर अक्षर *principal;	/* If present, this is a machine credential */
पूर्ण;

/*
 * Client user credentials
 */
काष्ठा rpc_auth;
काष्ठा rpc_creकरोps;
काष्ठा rpc_cred अणु
	काष्ठा hlist_node	cr_hash;	/* hash chain */
	काष्ठा list_head	cr_lru;		/* lru garbage collection */
	काष्ठा rcu_head		cr_rcu;
	काष्ठा rpc_auth *	cr_auth;
	स्थिर काष्ठा rpc_creकरोps *cr_ops;
	अचिन्हित दीर्घ		cr_expire;	/* when to gc */
	अचिन्हित दीर्घ		cr_flags;	/* various flags */
	refcount_t		cr_count;	/* ref count */
	स्थिर काष्ठा cred	*cr_cred;

	/* per-flavor data */
पूर्ण;
#घोषणा RPCAUTH_CRED_NEW	0
#घोषणा RPCAUTH_CRED_UPTODATE	1
#घोषणा RPCAUTH_CRED_HASHED	2
#घोषणा RPCAUTH_CRED_NEGATIVE	3

स्थिर काष्ठा cred *rpc_machine_cred(व्योम);

/*
 * Client authentication handle
 */
काष्ठा rpc_cred_cache;
काष्ठा rpc_authops;
काष्ठा rpc_auth अणु
	अचिन्हित पूर्णांक		au_cslack;	/* call cred size estimate */
	अचिन्हित पूर्णांक		au_rslack;	/* reply cred size estimate */
	अचिन्हित पूर्णांक		au_verfsize;	/* size of reply verअगरier */
	अचिन्हित पूर्णांक		au_ralign;	/* words beक्रमe UL header */

	अचिन्हित दीर्घ		au_flags;
	स्थिर काष्ठा rpc_authops *au_ops;
	rpc_authflavor_t	au_flavor;	/* pseuकरोflavor (note may
						 * dअगरfer from the flavor in
						 * au_ops->au_flavor in gss
						 * हाल) */
	refcount_t		au_count;	/* Reference counter */

	काष्ठा rpc_cred_cache *	au_credcache;
	/* per-flavor data */
पूर्ण;

/* rpc_auth au_flags */
#घोषणा RPCAUTH_AUTH_DATATOUCH		(1)
#घोषणा RPCAUTH_AUTH_UPDATE_SLACK	(2)

काष्ठा rpc_auth_create_args अणु
	rpc_authflavor_t pseuकरोflavor;
	स्थिर अक्षर *target_name;
पूर्ण;

/* Flags क्रम rpcauth_lookupcred() */
#घोषणा RPCAUTH_LOOKUP_NEW		0x01	/* Accept an uninitialised cred */

/*
 * Client authentication ops
 */
काष्ठा rpc_authops अणु
	काष्ठा module		*owner;
	rpc_authflavor_t	au_flavor;	/* flavor (RPC_AUTH_*) */
	अक्षर *			au_name;
	काष्ठा rpc_auth *	(*create)(स्थिर काष्ठा rpc_auth_create_args *,
					  काष्ठा rpc_clnt *);
	व्योम			(*destroy)(काष्ठा rpc_auth *);

	पूर्णांक			(*hash_cred)(काष्ठा auth_cred *, अचिन्हित पूर्णांक);
	काष्ठा rpc_cred *	(*lookup_cred)(काष्ठा rpc_auth *, काष्ठा auth_cred *, पूर्णांक);
	काष्ठा rpc_cred *	(*crcreate)(काष्ठा rpc_auth*, काष्ठा auth_cred *, पूर्णांक, gfp_t);
	rpc_authflavor_t	(*info2flavor)(काष्ठा rpcsec_gss_info *);
	पूर्णांक			(*flavor2info)(rpc_authflavor_t,
						काष्ठा rpcsec_gss_info *);
	पूर्णांक			(*key_समयout)(काष्ठा rpc_auth *,
						काष्ठा rpc_cred *);
पूर्ण;

काष्ठा rpc_creकरोps अणु
	स्थिर अक्षर *		cr_name;	/* Name of the auth flavour */
	पूर्णांक			(*cr_init)(काष्ठा rpc_auth *, काष्ठा rpc_cred *);
	व्योम			(*crdestroy)(काष्ठा rpc_cred *);

	पूर्णांक			(*crmatch)(काष्ठा auth_cred *, काष्ठा rpc_cred *, पूर्णांक);
	पूर्णांक			(*crmarshal)(काष्ठा rpc_task *task,
					     काष्ठा xdr_stream *xdr);
	पूर्णांक			(*crrefresh)(काष्ठा rpc_task *);
	पूर्णांक			(*crvalidate)(काष्ठा rpc_task *task,
					      काष्ठा xdr_stream *xdr);
	पूर्णांक			(*crwrap_req)(काष्ठा rpc_task *task,
					      काष्ठा xdr_stream *xdr);
	पूर्णांक			(*crunwrap_resp)(काष्ठा rpc_task *task,
						 काष्ठा xdr_stream *xdr);
	पूर्णांक			(*crkey_समयout)(काष्ठा rpc_cred *);
	अक्षर *			(*crstringअगरy_acceptor)(काष्ठा rpc_cred *);
	bool			(*crneed_reencode)(काष्ठा rpc_task *);
पूर्ण;

बाह्य स्थिर काष्ठा rpc_authops	authunix_ops;
बाह्य स्थिर काष्ठा rpc_authops	authnull_ops;

पूर्णांक __init		rpc_init_authunix(व्योम);
पूर्णांक __init		rpcauth_init_module(व्योम);
व्योम			rpcauth_हटाओ_module(व्योम);
व्योम 			rpc_destroy_authunix(व्योम);

पूर्णांक			rpcauth_रेजिस्टर(स्थिर काष्ठा rpc_authops *);
पूर्णांक			rpcauth_unरेजिस्टर(स्थिर काष्ठा rpc_authops *);
काष्ठा rpc_auth *	rpcauth_create(स्थिर काष्ठा rpc_auth_create_args *,
				काष्ठा rpc_clnt *);
व्योम			rpcauth_release(काष्ठा rpc_auth *);
rpc_authflavor_t	rpcauth_get_pseuकरोflavor(rpc_authflavor_t,
				काष्ठा rpcsec_gss_info *);
पूर्णांक			rpcauth_get_gssinfo(rpc_authflavor_t,
				काष्ठा rpcsec_gss_info *);
काष्ठा rpc_cred *	rpcauth_lookup_credcache(काष्ठा rpc_auth *, काष्ठा auth_cred *, पूर्णांक, gfp_t);
व्योम			rpcauth_init_cred(काष्ठा rpc_cred *, स्थिर काष्ठा auth_cred *, काष्ठा rpc_auth *, स्थिर काष्ठा rpc_creकरोps *);
काष्ठा rpc_cred *	rpcauth_lookupcred(काष्ठा rpc_auth *, पूर्णांक);
व्योम			put_rpccred(काष्ठा rpc_cred *);
पूर्णांक			rpcauth_marshcred(काष्ठा rpc_task *task,
					  काष्ठा xdr_stream *xdr);
पूर्णांक			rpcauth_checkverf(काष्ठा rpc_task *task,
					  काष्ठा xdr_stream *xdr);
पूर्णांक			rpcauth_wrap_req_encode(काष्ठा rpc_task *task,
						काष्ठा xdr_stream *xdr);
पूर्णांक			rpcauth_wrap_req(काष्ठा rpc_task *task,
					 काष्ठा xdr_stream *xdr);
पूर्णांक			rpcauth_unwrap_resp_decode(काष्ठा rpc_task *task,
						   काष्ठा xdr_stream *xdr);
पूर्णांक			rpcauth_unwrap_resp(काष्ठा rpc_task *task,
					    काष्ठा xdr_stream *xdr);
bool			rpcauth_xmit_need_reencode(काष्ठा rpc_task *task);
पूर्णांक			rpcauth_refreshcred(काष्ठा rpc_task *);
व्योम			rpcauth_invalcred(काष्ठा rpc_task *);
पूर्णांक			rpcauth_uptodatecred(काष्ठा rpc_task *);
पूर्णांक			rpcauth_init_credcache(काष्ठा rpc_auth *);
व्योम			rpcauth_destroy_credcache(काष्ठा rpc_auth *);
व्योम			rpcauth_clear_credcache(काष्ठा rpc_cred_cache *);
अक्षर *			rpcauth_stringअगरy_acceptor(काष्ठा rpc_cred *);

अटल अंतरभूत
काष्ठा rpc_cred *get_rpccred(काष्ठा rpc_cred *cred)
अणु
	अगर (cred != शून्य && refcount_inc_not_zero(&cred->cr_count))
		वापस cred;
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* _LINUX_SUNRPC_AUTH_H */
