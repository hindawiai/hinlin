<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/svcauth.h
 *
 * RPC server-side authentication stuff.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _LINUX_SUNRPC_SVCAUTH_H_
#घोषणा _LINUX_SUNRPC_SVCAUTH_H_

#समावेश <linux/माला.स>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/cache.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/hash.h>
#समावेश <linux/stringhash.h>
#समावेश <linux/cred.h>

काष्ठा svc_cred अणु
	kuid_t			cr_uid;
	kgid_t			cr_gid;
	काष्ठा group_info	*cr_group_info;
	u32			cr_flavor; /* pseuकरोflavor */
	/* name of क्रमm servicetype/hostname@REALM, passed करोwn by
	 * gss-proxy: */
	अक्षर			*cr_raw_principal;
	/* name of क्रमm servicetype@hostname, passed करोwn by
	 * rpc.svcgssd, or computed from the above: */
	अक्षर			*cr_principal;
	अक्षर			*cr_targ_princ;
	काष्ठा gss_api_mech	*cr_gss_mech;
पूर्ण;

अटल अंतरभूत व्योम init_svc_cred(काष्ठा svc_cred *cred)
अणु
	cred->cr_group_info = शून्य;
	cred->cr_raw_principal = शून्य;
	cred->cr_principal = शून्य;
	cred->cr_targ_princ = शून्य;
	cred->cr_gss_mech = शून्य;
पूर्ण

अटल अंतरभूत व्योम मुक्त_svc_cred(काष्ठा svc_cred *cred)
अणु
	अगर (cred->cr_group_info)
		put_group_info(cred->cr_group_info);
	kमुक्त(cred->cr_raw_principal);
	kमुक्त(cred->cr_principal);
	kमुक्त(cred->cr_targ_princ);
	gss_mech_put(cred->cr_gss_mech);
	init_svc_cred(cred);
पूर्ण

काष्ठा svc_rqst;		/* क्रमward decl */
काष्ठा in6_addr;

/* Authentication is करोne in the context of a करोमुख्य.
 *
 * Currently, the nfs server uses the auth_करोमुख्य to stand
 * क्रम the "client" listed in /etc/exports.
 *
 * More generally, a करोमुख्य might represent a group of clients using
 * a common mechanism क्रम authentication and having a common mapping
 * between local identity (uid) and network identity.  All clients
 * in a करोमुख्य have similar general access rights.  Each करोमुख्य can
 * contain multiple principals which will have dअगरferent specअगरic right
 * based on normal Discretionary Access Control.
 *
 * A करोमुख्य is created by an authentication flavour module based on name
 * only.  Userspace then fills in detail on demand.
 *
 * In the हाल of auth_unix and auth_null, the auth_करोमुख्य is also
 * associated with entries in another cache representing the mapping
 * of ip addresses to the given client.
 */
काष्ठा auth_करोमुख्य अणु
	काष्ठा kref		ref;
	काष्ठा hlist_node	hash;
	अक्षर			*name;
	काष्ठा auth_ops		*flavour;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

/*
 * Each authentication flavour रेजिस्टरs an auth_ops
 * काष्ठाure.
 * name is simply the name.
 * flavour gives the auth flavour. It determines where the flavour is रेजिस्टरed
 * accept() is given a request and should verअगरy it.
 *   It should inspect the authenticator and verअगरier, and possibly the data.
 *    If there is a problem with the authentication *authp should be set.
 *    The वापस value of accept() can indicate:
 *      OK - authorised. client and credential are set in rqstp.
 *           reqbuf poपूर्णांकs to arguments
 *           resbuf poपूर्णांकs to good place क्रम results.  verfier
 *             is (probably) alपढ़ोy in place.  Certainly space is
 *	       reserved क्रम it.
 *      DROP - simply drop the request. It may have been deferred
 *      GARBAGE - rpc garbage_args error
 *      SYSERR - rpc प्रणाली_err error
 *      DENIED - authp holds reason क्रम denial.
 *      COMPLETE - the reply is encoded alपढ़ोy and पढ़ोy to be sent; no
 *		further processing is necessary.  (This is used क्रम processing
 *		null procedure calls which are used to set up encryption
 *		contexts.)
 *
 *   accept is passed the proc number so that it can accept शून्य rpc requests
 *   even अगर it cannot authenticate the client (as is someबार appropriate).
 *
 * release() is given a request after the procedure has been run.
 *  It should sign/encrypt the results अगर needed
 * It should वापस:
 *    OK - the resbuf is पढ़ोy to be sent
 *    DROP - the reply should be quitely dropped
 *    DENIED - authp holds a reason क्रम MSG_DENIED
 *    SYSERR - rpc प्रणाली_err
 *
 * करोमुख्य_release()
 *   This call releases a करोमुख्य.
 * set_client()
 *   Givens a pending request (काष्ठा svc_rqst), finds and assigns
 *   an appropriate 'auth_domain' as the client.
 */
काष्ठा auth_ops अणु
	अक्षर *	name;
	काष्ठा module *owner;
	पूर्णांक	flavour;
	पूर्णांक	(*accept)(काष्ठा svc_rqst *rq, __be32 *authp);
	पूर्णांक	(*release)(काष्ठा svc_rqst *rq);
	व्योम	(*करोमुख्य_release)(काष्ठा auth_करोमुख्य *);
	पूर्णांक	(*set_client)(काष्ठा svc_rqst *rq);
पूर्ण;

#घोषणा	SVC_GARBAGE	1
#घोषणा	SVC_SYSERR	2
#घोषणा	SVC_VALID	3
#घोषणा	SVC_NEGATIVE	4
#घोषणा	SVC_OK		5
#घोषणा	SVC_DROP	6
#घोषणा	SVC_CLOSE	7	/* Like SVC_DROP, but request is definitely
				 * lost so अगर there is a tcp connection, it
				 * should be बंदd
				 */
#घोषणा	SVC_DENIED	8
#घोषणा	SVC_PENDING	9
#घोषणा	SVC_COMPLETE	10

काष्ठा svc_xprt;

बाह्य पूर्णांक	svc_authenticate(काष्ठा svc_rqst *rqstp, __be32 *authp);
बाह्य पूर्णांक	svc_authorise(काष्ठा svc_rqst *rqstp);
बाह्य पूर्णांक	svc_set_client(काष्ठा svc_rqst *rqstp);
बाह्य पूर्णांक	svc_auth_रेजिस्टर(rpc_authflavor_t flavor, काष्ठा auth_ops *aops);
बाह्य व्योम	svc_auth_unरेजिस्टर(rpc_authflavor_t flavor);

बाह्य काष्ठा auth_करोमुख्य *unix_करोमुख्य_find(अक्षर *name);
बाह्य व्योम auth_करोमुख्य_put(काष्ठा auth_करोमुख्य *item);
बाह्य पूर्णांक auth_unix_add_addr(काष्ठा net *net, काष्ठा in6_addr *addr, काष्ठा auth_करोमुख्य *करोm);
बाह्य काष्ठा auth_करोमुख्य *auth_करोमुख्य_lookup(अक्षर *name, काष्ठा auth_करोमुख्य *new);
बाह्य काष्ठा auth_करोमुख्य *auth_करोमुख्य_find(अक्षर *name);
बाह्य काष्ठा auth_करोमुख्य *auth_unix_lookup(काष्ठा net *net, काष्ठा in6_addr *addr);
बाह्य पूर्णांक auth_unix_क्रमget_old(काष्ठा auth_करोमुख्य *करोm);
बाह्य व्योम svcauth_unix_purge(काष्ठा net *net);
बाह्य व्योम svcauth_unix_info_release(काष्ठा svc_xprt *xpt);
बाह्य पूर्णांक svcauth_unix_set_client(काष्ठा svc_rqst *rqstp);

बाह्य पूर्णांक unix_gid_cache_create(काष्ठा net *net);
बाह्य व्योम unix_gid_cache_destroy(काष्ठा net *net);

/*
 * The <stringhash.h> functions are good enough that we करोn't need to
 * use hash_32() on them; just extracting the high bits is enough.
 */
अटल अंतरभूत अचिन्हित दीर्घ hash_str(अक्षर स्थिर *name, पूर्णांक bits)
अणु
	वापस hashlen_hash(hashlen_string(शून्य, name)) >> (32 - bits);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hash_mem(अक्षर स्थिर *buf, पूर्णांक length, पूर्णांक bits)
अणु
	वापस full_name_hash(शून्य, buf, length) >> (32 - bits);
पूर्ण

#पूर्ण_अगर /* _LINUX_SUNRPC_SVCAUTH_H_ */
