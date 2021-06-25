<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/svcauth.c
 *
 * The generic पूर्णांकerface क्रम RPC authentication on the server side.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 *
 * CHANGES
 * 19-Apr-2000 Chris Evans      - Security fix
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/svcauth.h>
#समावेश <linux/err.h>
#समावेश <linux/hash.h>

#समावेश <trace/events/sunrpc.h>

#समावेश "sunrpc.h"

#घोषणा RPCDBG_FACILITY	RPCDBG_AUTH


/*
 * Table of authenticators
 */
बाह्य काष्ठा auth_ops svcauth_null;
बाह्य काष्ठा auth_ops svcauth_unix;

अटल काष्ठा auth_ops __rcu *authtab[RPC_AUTH_MAXFLAVOR] = अणु
	[RPC_AUTH_शून्य] = (काष्ठा auth_ops __क्रमce __rcu *)&svcauth_null,
	[RPC_AUTH_UNIX] = (काष्ठा auth_ops __क्रमce __rcu *)&svcauth_unix,
पूर्ण;

अटल काष्ठा auth_ops *
svc_get_auth_ops(rpc_authflavor_t flavor)
अणु
	काष्ठा auth_ops		*aops;

	अगर (flavor >= RPC_AUTH_MAXFLAVOR)
		वापस शून्य;
	rcu_पढ़ो_lock();
	aops = rcu_dereference(authtab[flavor]);
	अगर (aops != शून्य && !try_module_get(aops->owner))
		aops = शून्य;
	rcu_पढ़ो_unlock();
	वापस aops;
पूर्ण

अटल व्योम
svc_put_auth_ops(काष्ठा auth_ops *aops)
अणु
	module_put(aops->owner);
पूर्ण

पूर्णांक
svc_authenticate(काष्ठा svc_rqst *rqstp, __be32 *authp)
अणु
	rpc_authflavor_t	flavor;
	काष्ठा auth_ops		*aops;

	*authp = rpc_auth_ok;

	flavor = svc_getnl(&rqstp->rq_arg.head[0]);

	dprपूर्णांकk("svc: svc_authenticate (%d)\n", flavor);

	aops = svc_get_auth_ops(flavor);
	अगर (aops == शून्य) अणु
		*authp = rpc_autherr_badcred;
		वापस SVC_DENIED;
	पूर्ण

	rqstp->rq_auth_slack = 0;
	init_svc_cred(&rqstp->rq_cred);

	rqstp->rq_authop = aops;
	वापस aops->accept(rqstp, authp);
पूर्ण
EXPORT_SYMBOL_GPL(svc_authenticate);

पूर्णांक svc_set_client(काष्ठा svc_rqst *rqstp)
अणु
	rqstp->rq_client = शून्य;
	वापस rqstp->rq_authop->set_client(rqstp);
पूर्ण
EXPORT_SYMBOL_GPL(svc_set_client);

/* A request, which was authenticated, has now executed.
 * Time to finalise the credentials and verअगरier
 * and release and resources
 */
पूर्णांक svc_authorise(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा auth_ops *aops = rqstp->rq_authop;
	पूर्णांक rv = 0;

	rqstp->rq_authop = शून्य;

	अगर (aops) अणु
		rv = aops->release(rqstp);
		svc_put_auth_ops(aops);
	पूर्ण
	वापस rv;
पूर्ण

पूर्णांक
svc_auth_रेजिस्टर(rpc_authflavor_t flavor, काष्ठा auth_ops *aops)
अणु
	काष्ठा auth_ops *old;
	पूर्णांक rv = -EINVAL;

	अगर (flavor < RPC_AUTH_MAXFLAVOR) अणु
		old = cmpxchg((काष्ठा auth_ops ** __क्रमce)&authtab[flavor], शून्य, aops);
		अगर (old == शून्य || old == aops)
			rv = 0;
	पूर्ण
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(svc_auth_रेजिस्टर);

व्योम
svc_auth_unरेजिस्टर(rpc_authflavor_t flavor)
अणु
	अगर (flavor < RPC_AUTH_MAXFLAVOR)
		rcu_assign_poपूर्णांकer(authtab[flavor], शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(svc_auth_unरेजिस्टर);

/**************************************************
 * 'auth_domains' are stored in a hash table indexed by name.
 * When the last reference to an 'auth_domain' is dropped,
 * the object is unhashed and मुक्तd.
 * If auth_करोमुख्य_lookup fails to find an entry, it will वापस
 * it's second argument 'new'.  If this is non-null, it will
 * have been atomically linked पूर्णांकo the table.
 */

#घोषणा	DN_HASHBITS	6
#घोषणा	DN_HASHMAX	(1<<DN_HASHBITS)

अटल काष्ठा hlist_head	auth_करोमुख्य_table[DN_HASHMAX];
अटल DEFINE_SPINLOCK(auth_करोमुख्य_lock);

अटल व्योम auth_करोमुख्य_release(काष्ठा kref *kref)
	__releases(&auth_करोमुख्य_lock)
अणु
	काष्ठा auth_करोमुख्य *करोm = container_of(kref, काष्ठा auth_करोमुख्य, ref);

	hlist_del_rcu(&करोm->hash);
	करोm->flavour->करोमुख्य_release(करोm);
	spin_unlock(&auth_करोमुख्य_lock);
पूर्ण

व्योम auth_करोमुख्य_put(काष्ठा auth_करोमुख्य *करोm)
अणु
	kref_put_lock(&करोm->ref, auth_करोमुख्य_release, &auth_करोमुख्य_lock);
पूर्ण
EXPORT_SYMBOL_GPL(auth_करोमुख्य_put);

काष्ठा auth_करोमुख्य *
auth_करोमुख्य_lookup(अक्षर *name, काष्ठा auth_करोमुख्य *new)
अणु
	काष्ठा auth_करोमुख्य *hp;
	काष्ठा hlist_head *head;

	head = &auth_करोमुख्य_table[hash_str(name, DN_HASHBITS)];

	spin_lock(&auth_करोमुख्य_lock);

	hlist_क्रम_each_entry(hp, head, hash) अणु
		अगर (म_भेद(hp->name, name)==0) अणु
			kref_get(&hp->ref);
			spin_unlock(&auth_करोमुख्य_lock);
			वापस hp;
		पूर्ण
	पूर्ण
	अगर (new)
		hlist_add_head_rcu(&new->hash, head);
	spin_unlock(&auth_करोमुख्य_lock);
	वापस new;
पूर्ण
EXPORT_SYMBOL_GPL(auth_करोमुख्य_lookup);

काष्ठा auth_करोमुख्य *auth_करोमुख्य_find(अक्षर *name)
अणु
	काष्ठा auth_करोमुख्य *hp;
	काष्ठा hlist_head *head;

	head = &auth_करोमुख्य_table[hash_str(name, DN_HASHBITS)];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(hp, head, hash) अणु
		अगर (म_भेद(hp->name, name)==0) अणु
			अगर (!kref_get_unless_zero(&hp->ref))
				hp = शून्य;
			rcu_पढ़ो_unlock();
			वापस hp;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(auth_करोमुख्य_find);

/**
 * auth_करोमुख्य_cleanup - check that the auth_करोमुख्य table is empty
 *
 * On module unload the auth_करोमुख्य_table must be empty.  To make it
 * easier to catch bugs which करोn't clean up करोमुख्यs properly, we
 * warn अगर anything reमुख्यs in the table at cleanup समय.
 *
 * Note that we cannot proactively हटाओ the करोमुख्यs at this stage.
 * The ->release() function might be in a module that has alपढ़ोy been
 * unloaded.
 */

व्योम auth_करोमुख्य_cleanup(व्योम)
अणु
	पूर्णांक h;
	काष्ठा auth_करोमुख्य *hp;

	क्रम (h = 0; h < DN_HASHMAX; h++)
		hlist_क्रम_each_entry(hp, &auth_करोमुख्य_table[h], hash)
			pr_warn("svc: domain %s still present at module unload.\n",
				hp->name);
पूर्ण
