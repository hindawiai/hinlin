<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/auth.c
 *
 * Generic RPC client authentication API.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hash.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/spinlock.h>

#समावेश <trace/events/sunrpc.h>

#घोषणा RPC_CREDCACHE_DEFAULT_HASHBITS	(4)
काष्ठा rpc_cred_cache अणु
	काष्ठा hlist_head	*hashtable;
	अचिन्हित पूर्णांक		hashbits;
	spinlock_t		lock;
पूर्ण;

अटल अचिन्हित पूर्णांक auth_hashbits = RPC_CREDCACHE_DEFAULT_HASHBITS;

अटल स्थिर काष्ठा rpc_authops __rcu *auth_flavors[RPC_AUTH_MAXFLAVOR] = अणु
	[RPC_AUTH_शून्य] = (स्थिर काष्ठा rpc_authops __क्रमce __rcu *)&authnull_ops,
	[RPC_AUTH_UNIX] = (स्थिर काष्ठा rpc_authops __क्रमce __rcu *)&authunix_ops,
	शून्य,			/* others can be loadable modules */
पूर्ण;

अटल LIST_HEAD(cred_unused);
अटल अचिन्हित दीर्घ number_cred_unused;

अटल काष्ठा cred machine_cred = अणु
	.usage = ATOMIC_INIT(1),
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	.magic = CRED_MAGIC,
#पूर्ण_अगर
पूर्ण;

/*
 * Return the machine_cred poपूर्णांकer to be used whenever
 * the a generic machine credential is needed.
 */
स्थिर काष्ठा cred *rpc_machine_cred(व्योम)
अणु
	वापस &machine_cred;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_machine_cred);

#घोषणा MAX_HASHTABLE_BITS (14)
अटल पूर्णांक param_set_hashtbl_sz(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ num;
	अचिन्हित पूर्णांक nbits;
	पूर्णांक ret;

	अगर (!val)
		जाओ out_inval;
	ret = kम_से_अदीर्घ(val, 0, &num);
	अगर (ret)
		जाओ out_inval;
	nbits = fls(num - 1);
	अगर (nbits > MAX_HASHTABLE_BITS || nbits < 2)
		जाओ out_inval;
	*(अचिन्हित पूर्णांक *)kp->arg = nbits;
	वापस 0;
out_inval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक param_get_hashtbl_sz(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित पूर्णांक nbits;

	nbits = *(अचिन्हित पूर्णांक *)kp->arg;
	वापस प्र_लिखो(buffer, "%u\n", 1U << nbits);
पूर्ण

#घोषणा param_check_hashtbl_sz(name, p) __param_check(name, p, अचिन्हित पूर्णांक);

अटल स्थिर काष्ठा kernel_param_ops param_ops_hashtbl_sz = अणु
	.set = param_set_hashtbl_sz,
	.get = param_get_hashtbl_sz,
पूर्ण;

module_param_named(auth_hashtable_size, auth_hashbits, hashtbl_sz, 0644);
MODULE_PARM_DESC(auth_hashtable_size, "RPC credential cache hashtable size");

अटल अचिन्हित दीर्घ auth_max_cred_cachesize = अच_दीर्घ_उच्च;
module_param(auth_max_cred_cachesize, uदीर्घ, 0644);
MODULE_PARM_DESC(auth_max_cred_cachesize, "RPC credential maximum total cache size");

अटल u32
pseuकरोflavor_to_flavor(u32 flavor) अणु
	अगर (flavor > RPC_AUTH_MAXFLAVOR)
		वापस RPC_AUTH_GSS;
	वापस flavor;
पूर्ण

पूर्णांक
rpcauth_रेजिस्टर(स्थिर काष्ठा rpc_authops *ops)
अणु
	स्थिर काष्ठा rpc_authops *old;
	rpc_authflavor_t flavor;

	अगर ((flavor = ops->au_flavor) >= RPC_AUTH_MAXFLAVOR)
		वापस -EINVAL;
	old = cmpxchg((स्थिर काष्ठा rpc_authops ** __क्रमce)&auth_flavors[flavor], शून्य, ops);
	अगर (old == शून्य || old == ops)
		वापस 0;
	वापस -EPERM;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_रेजिस्टर);

पूर्णांक
rpcauth_unरेजिस्टर(स्थिर काष्ठा rpc_authops *ops)
अणु
	स्थिर काष्ठा rpc_authops *old;
	rpc_authflavor_t flavor;

	अगर ((flavor = ops->au_flavor) >= RPC_AUTH_MAXFLAVOR)
		वापस -EINVAL;

	old = cmpxchg((स्थिर काष्ठा rpc_authops ** __क्रमce)&auth_flavors[flavor], ops, शून्य);
	अगर (old == ops || old == शून्य)
		वापस 0;
	वापस -EPERM;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_unरेजिस्टर);

अटल स्थिर काष्ठा rpc_authops *
rpcauth_get_authops(rpc_authflavor_t flavor)
अणु
	स्थिर काष्ठा rpc_authops *ops;

	अगर (flavor >= RPC_AUTH_MAXFLAVOR)
		वापस शून्य;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(auth_flavors[flavor]);
	अगर (ops == शून्य) अणु
		rcu_पढ़ो_unlock();
		request_module("rpc-auth-%u", flavor);
		rcu_पढ़ो_lock();
		ops = rcu_dereference(auth_flavors[flavor]);
		अगर (ops == शून्य)
			जाओ out;
	पूर्ण
	अगर (!try_module_get(ops->owner))
		ops = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस ops;
पूर्ण

अटल व्योम
rpcauth_put_authops(स्थिर काष्ठा rpc_authops *ops)
अणु
	module_put(ops->owner);
पूर्ण

/**
 * rpcauth_get_pseuकरोflavor - check अगर security flavor is supported
 * @flavor: a security flavor
 * @info: a GSS mech OID, quality of protection, and service value
 *
 * Verअगरies that an appropriate kernel module is available or alपढ़ोy loaded.
 * Returns an equivalent pseuकरोflavor, or RPC_AUTH_MAXFLAVOR अगर "flavor" is
 * not supported locally.
 */
rpc_authflavor_t
rpcauth_get_pseuकरोflavor(rpc_authflavor_t flavor, काष्ठा rpcsec_gss_info *info)
अणु
	स्थिर काष्ठा rpc_authops *ops = rpcauth_get_authops(flavor);
	rpc_authflavor_t pseuकरोflavor;

	अगर (!ops)
		वापस RPC_AUTH_MAXFLAVOR;
	pseuकरोflavor = flavor;
	अगर (ops->info2flavor != शून्य)
		pseuकरोflavor = ops->info2flavor(info);

	rpcauth_put_authops(ops);
	वापस pseuकरोflavor;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_get_pseuकरोflavor);

/**
 * rpcauth_get_gssinfo - find GSS tuple matching a GSS pseuकरोflavor
 * @pseuकरोflavor: GSS pseuकरोflavor to match
 * @info: rpcsec_gss_info काष्ठाure to fill in
 *
 * Returns zero and fills in "info" अगर pseuकरोflavor matches a
 * supported mechanism.
 */
पूर्णांक
rpcauth_get_gssinfo(rpc_authflavor_t pseuकरोflavor, काष्ठा rpcsec_gss_info *info)
अणु
	rpc_authflavor_t flavor = pseuकरोflavor_to_flavor(pseuकरोflavor);
	स्थिर काष्ठा rpc_authops *ops;
	पूर्णांक result;

	ops = rpcauth_get_authops(flavor);
	अगर (ops == शून्य)
		वापस -ENOENT;

	result = -ENOENT;
	अगर (ops->flavor2info != शून्य)
		result = ops->flavor2info(pseuकरोflavor, info);

	rpcauth_put_authops(ops);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_get_gssinfo);

काष्ठा rpc_auth *
rpcauth_create(स्थिर काष्ठा rpc_auth_create_args *args, काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_auth	*auth = ERR_PTR(-EINVAL);
	स्थिर काष्ठा rpc_authops *ops;
	u32 flavor = pseuकरोflavor_to_flavor(args->pseuकरोflavor);

	ops = rpcauth_get_authops(flavor);
	अगर (ops == शून्य)
		जाओ out;

	auth = ops->create(args, clnt);

	rpcauth_put_authops(ops);
	अगर (IS_ERR(auth))
		वापस auth;
	अगर (clnt->cl_auth)
		rpcauth_release(clnt->cl_auth);
	clnt->cl_auth = auth;

out:
	वापस auth;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_create);

व्योम
rpcauth_release(काष्ठा rpc_auth *auth)
अणु
	अगर (!refcount_dec_and_test(&auth->au_count))
		वापस;
	auth->au_ops->destroy(auth);
पूर्ण

अटल DEFINE_SPINLOCK(rpc_credcache_lock);

/*
 * On success, the caller is responsible क्रम मुक्तing the reference
 * held by the hashtable
 */
अटल bool
rpcauth_unhash_cred_locked(काष्ठा rpc_cred *cred)
अणु
	अगर (!test_and_clear_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags))
		वापस false;
	hlist_del_rcu(&cred->cr_hash);
	वापस true;
पूर्ण

अटल bool
rpcauth_unhash_cred(काष्ठा rpc_cred *cred)
अणु
	spinlock_t *cache_lock;
	bool ret;

	अगर (!test_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags))
		वापस false;
	cache_lock = &cred->cr_auth->au_credcache->lock;
	spin_lock(cache_lock);
	ret = rpcauth_unhash_cred_locked(cred);
	spin_unlock(cache_lock);
	वापस ret;
पूर्ण

/*
 * Initialize RPC credential cache
 */
पूर्णांक
rpcauth_init_credcache(काष्ठा rpc_auth *auth)
अणु
	काष्ठा rpc_cred_cache *new;
	अचिन्हित पूर्णांक hashsize;

	new = kदो_स्मृति(माप(*new), GFP_KERNEL);
	अगर (!new)
		जाओ out_nocache;
	new->hashbits = auth_hashbits;
	hashsize = 1U << new->hashbits;
	new->hashtable = kसुस्मृति(hashsize, माप(new->hashtable[0]), GFP_KERNEL);
	अगर (!new->hashtable)
		जाओ out_nohashtbl;
	spin_lock_init(&new->lock);
	auth->au_credcache = new;
	वापस 0;
out_nohashtbl:
	kमुक्त(new);
out_nocache:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_init_credcache);

अक्षर *
rpcauth_stringअगरy_acceptor(काष्ठा rpc_cred *cred)
अणु
	अगर (!cred->cr_ops->crstringअगरy_acceptor)
		वापस शून्य;
	वापस cred->cr_ops->crstringअगरy_acceptor(cred);
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_stringअगरy_acceptor);

/*
 * Destroy a list of credentials
 */
अटल अंतरभूत
व्योम rpcauth_destroy_credlist(काष्ठा list_head *head)
अणु
	काष्ठा rpc_cred *cred;

	जबतक (!list_empty(head)) अणु
		cred = list_entry(head->next, काष्ठा rpc_cred, cr_lru);
		list_del_init(&cred->cr_lru);
		put_rpccred(cred);
	पूर्ण
पूर्ण

अटल व्योम
rpcauth_lru_add_locked(काष्ठा rpc_cred *cred)
अणु
	अगर (!list_empty(&cred->cr_lru))
		वापस;
	number_cred_unused++;
	list_add_tail(&cred->cr_lru, &cred_unused);
पूर्ण

अटल व्योम
rpcauth_lru_add(काष्ठा rpc_cred *cred)
अणु
	अगर (!list_empty(&cred->cr_lru))
		वापस;
	spin_lock(&rpc_credcache_lock);
	rpcauth_lru_add_locked(cred);
	spin_unlock(&rpc_credcache_lock);
पूर्ण

अटल व्योम
rpcauth_lru_हटाओ_locked(काष्ठा rpc_cred *cred)
अणु
	अगर (list_empty(&cred->cr_lru))
		वापस;
	number_cred_unused--;
	list_del_init(&cred->cr_lru);
पूर्ण

अटल व्योम
rpcauth_lru_हटाओ(काष्ठा rpc_cred *cred)
अणु
	अगर (list_empty(&cred->cr_lru))
		वापस;
	spin_lock(&rpc_credcache_lock);
	rpcauth_lru_हटाओ_locked(cred);
	spin_unlock(&rpc_credcache_lock);
पूर्ण

/*
 * Clear the RPC credential cache, and delete those credentials
 * that are not referenced.
 */
व्योम
rpcauth_clear_credcache(काष्ठा rpc_cred_cache *cache)
अणु
	LIST_HEAD(मुक्त);
	काष्ठा hlist_head *head;
	काष्ठा rpc_cred	*cred;
	अचिन्हित पूर्णांक hashsize = 1U << cache->hashbits;
	पूर्णांक		i;

	spin_lock(&rpc_credcache_lock);
	spin_lock(&cache->lock);
	क्रम (i = 0; i < hashsize; i++) अणु
		head = &cache->hashtable[i];
		जबतक (!hlist_empty(head)) अणु
			cred = hlist_entry(head->first, काष्ठा rpc_cred, cr_hash);
			rpcauth_unhash_cred_locked(cred);
			/* Note: We now hold a reference to cred */
			rpcauth_lru_हटाओ_locked(cred);
			list_add_tail(&cred->cr_lru, &मुक्त);
		पूर्ण
	पूर्ण
	spin_unlock(&cache->lock);
	spin_unlock(&rpc_credcache_lock);
	rpcauth_destroy_credlist(&मुक्त);
पूर्ण

/*
 * Destroy the RPC credential cache
 */
व्योम
rpcauth_destroy_credcache(काष्ठा rpc_auth *auth)
अणु
	काष्ठा rpc_cred_cache *cache = auth->au_credcache;

	अगर (cache) अणु
		auth->au_credcache = शून्य;
		rpcauth_clear_credcache(cache);
		kमुक्त(cache->hashtable);
		kमुक्त(cache);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_destroy_credcache);


#घोषणा RPC_AUTH_EXPIRY_MORATORIUM (60 * HZ)

/*
 * Remove stale credentials. Aव्योम sleeping inside the loop.
 */
अटल दीर्घ
rpcauth_prune_expired(काष्ठा list_head *मुक्त, पूर्णांक nr_to_scan)
अणु
	काष्ठा rpc_cred *cred, *next;
	अचिन्हित दीर्घ expired = jअगरfies - RPC_AUTH_EXPIRY_MORATORIUM;
	दीर्घ मुक्तd = 0;

	list_क्रम_each_entry_safe(cred, next, &cred_unused, cr_lru) अणु

		अगर (nr_to_scan-- == 0)
			अवरोध;
		अगर (refcount_पढ़ो(&cred->cr_count) > 1) अणु
			rpcauth_lru_हटाओ_locked(cred);
			जारी;
		पूर्ण
		/*
		 * Enक्रमce a 60 second garbage collection moratorium
		 * Note that the cred_unused list must be समय-ordered.
		 */
		अगर (!समय_in_range(cred->cr_expire, expired, jअगरfies))
			जारी;
		अगर (!rpcauth_unhash_cred(cred))
			जारी;

		rpcauth_lru_हटाओ_locked(cred);
		मुक्तd++;
		list_add_tail(&cred->cr_lru, मुक्त);
	पूर्ण
	वापस मुक्तd ? मुक्तd : SHRINK_STOP;
पूर्ण

अटल अचिन्हित दीर्घ
rpcauth_cache_करो_shrink(पूर्णांक nr_to_scan)
अणु
	LIST_HEAD(मुक्त);
	अचिन्हित दीर्घ मुक्तd;

	spin_lock(&rpc_credcache_lock);
	मुक्तd = rpcauth_prune_expired(&मुक्त, nr_to_scan);
	spin_unlock(&rpc_credcache_lock);
	rpcauth_destroy_credlist(&मुक्त);

	वापस मुक्तd;
पूर्ण

/*
 * Run memory cache shrinker.
 */
अटल अचिन्हित दीर्घ
rpcauth_cache_shrink_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)

अणु
	अगर ((sc->gfp_mask & GFP_KERNEL) != GFP_KERNEL)
		वापस SHRINK_STOP;

	/* nothing left, करोn't come back */
	अगर (list_empty(&cred_unused))
		वापस SHRINK_STOP;

	वापस rpcauth_cache_करो_shrink(sc->nr_to_scan);
पूर्ण

अटल अचिन्हित दीर्घ
rpcauth_cache_shrink_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)

अणु
	वापस number_cred_unused * sysctl_vfs_cache_pressure / 100;
पूर्ण

अटल व्योम
rpcauth_cache_enक्रमce_limit(व्योम)
अणु
	अचिन्हित दीर्घ dअगरf;
	अचिन्हित पूर्णांक nr_to_scan;

	अगर (number_cred_unused <= auth_max_cred_cachesize)
		वापस;
	dअगरf = number_cred_unused - auth_max_cred_cachesize;
	nr_to_scan = 100;
	अगर (dअगरf < nr_to_scan)
		nr_to_scan = dअगरf;
	rpcauth_cache_करो_shrink(nr_to_scan);
पूर्ण

/*
 * Look up a process' credentials in the authentication cache
 */
काष्ठा rpc_cred *
rpcauth_lookup_credcache(काष्ठा rpc_auth *auth, काष्ठा auth_cred * acred,
		पूर्णांक flags, gfp_t gfp)
अणु
	LIST_HEAD(मुक्त);
	काष्ठा rpc_cred_cache *cache = auth->au_credcache;
	काष्ठा rpc_cred	*cred = शून्य,
			*entry, *new;
	अचिन्हित पूर्णांक nr;

	nr = auth->au_ops->hash_cred(acred, cache->hashbits);

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(entry, &cache->hashtable[nr], cr_hash) अणु
		अगर (!entry->cr_ops->crmatch(acred, entry, flags))
			जारी;
		cred = get_rpccred(entry);
		अगर (cred)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (cred != शून्य)
		जाओ found;

	new = auth->au_ops->crcreate(auth, acred, flags, gfp);
	अगर (IS_ERR(new)) अणु
		cred = new;
		जाओ out;
	पूर्ण

	spin_lock(&cache->lock);
	hlist_क्रम_each_entry(entry, &cache->hashtable[nr], cr_hash) अणु
		अगर (!entry->cr_ops->crmatch(acred, entry, flags))
			जारी;
		cred = get_rpccred(entry);
		अगर (cred)
			अवरोध;
	पूर्ण
	अगर (cred == शून्य) अणु
		cred = new;
		set_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags);
		refcount_inc(&cred->cr_count);
		hlist_add_head_rcu(&cred->cr_hash, &cache->hashtable[nr]);
	पूर्ण अन्यथा
		list_add_tail(&new->cr_lru, &मुक्त);
	spin_unlock(&cache->lock);
	rpcauth_cache_enक्रमce_limit();
found:
	अगर (test_bit(RPCAUTH_CRED_NEW, &cred->cr_flags) &&
	    cred->cr_ops->cr_init != शून्य &&
	    !(flags & RPCAUTH_LOOKUP_NEW)) अणु
		पूर्णांक res = cred->cr_ops->cr_init(auth, cred);
		अगर (res < 0) अणु
			put_rpccred(cred);
			cred = ERR_PTR(res);
		पूर्ण
	पूर्ण
	rpcauth_destroy_credlist(&मुक्त);
out:
	वापस cred;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_lookup_credcache);

काष्ठा rpc_cred *
rpcauth_lookupcred(काष्ठा rpc_auth *auth, पूर्णांक flags)
अणु
	काष्ठा auth_cred acred;
	काष्ठा rpc_cred *ret;
	स्थिर काष्ठा cred *cred = current_cred();

	स_रखो(&acred, 0, माप(acred));
	acred.cred = cred;
	ret = auth->au_ops->lookup_cred(auth, &acred, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_lookupcred);

व्योम
rpcauth_init_cred(काष्ठा rpc_cred *cred, स्थिर काष्ठा auth_cred *acred,
		  काष्ठा rpc_auth *auth, स्थिर काष्ठा rpc_creकरोps *ops)
अणु
	INIT_HLIST_NODE(&cred->cr_hash);
	INIT_LIST_HEAD(&cred->cr_lru);
	refcount_set(&cred->cr_count, 1);
	cred->cr_auth = auth;
	cred->cr_flags = 0;
	cred->cr_ops = ops;
	cred->cr_expire = jअगरfies;
	cred->cr_cred = get_cred(acred->cred);
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_init_cred);

अटल काष्ठा rpc_cred *
rpcauth_bind_root_cred(काष्ठा rpc_task *task, पूर्णांक lookupflags)
अणु
	काष्ठा rpc_auth *auth = task->tk_client->cl_auth;
	काष्ठा auth_cred acred = अणु
		.cred = get_task_cred(&init_task),
	पूर्ण;
	काष्ठा rpc_cred *ret;

	ret = auth->au_ops->lookup_cred(auth, &acred, lookupflags);
	put_cred(acred.cred);
	वापस ret;
पूर्ण

अटल काष्ठा rpc_cred *
rpcauth_bind_machine_cred(काष्ठा rpc_task *task, पूर्णांक lookupflags)
अणु
	काष्ठा rpc_auth *auth = task->tk_client->cl_auth;
	काष्ठा auth_cred acred = अणु
		.principal = task->tk_client->cl_principal,
		.cred = init_task.cred,
	पूर्ण;

	अगर (!acred.principal)
		वापस शून्य;
	वापस auth->au_ops->lookup_cred(auth, &acred, lookupflags);
पूर्ण

अटल काष्ठा rpc_cred *
rpcauth_bind_new_cred(काष्ठा rpc_task *task, पूर्णांक lookupflags)
अणु
	काष्ठा rpc_auth *auth = task->tk_client->cl_auth;

	वापस rpcauth_lookupcred(auth, lookupflags);
पूर्ण

अटल पूर्णांक
rpcauth_bindcred(काष्ठा rpc_task *task, स्थिर काष्ठा cred *cred, पूर्णांक flags)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_cred *new = शून्य;
	पूर्णांक lookupflags = 0;
	काष्ठा rpc_auth *auth = task->tk_client->cl_auth;
	काष्ठा auth_cred acred = अणु
		.cred = cred,
	पूर्ण;

	अगर (flags & RPC_TASK_ASYNC)
		lookupflags |= RPCAUTH_LOOKUP_NEW;
	अगर (task->tk_op_cred)
		/* Task must use exactly this rpc_cred */
		new = get_rpccred(task->tk_op_cred);
	अन्यथा अगर (cred != शून्य && cred != &machine_cred)
		new = auth->au_ops->lookup_cred(auth, &acred, lookupflags);
	अन्यथा अगर (cred == &machine_cred)
		new = rpcauth_bind_machine_cred(task, lookupflags);

	/* If machine cred couldn't be bound, try a root cred */
	अगर (new)
		;
	अन्यथा अगर (cred == &machine_cred || (flags & RPC_TASK_ROOTCREDS))
		new = rpcauth_bind_root_cred(task, lookupflags);
	अन्यथा अगर (flags & RPC_TASK_शून्यCREDS)
		new = authnull_ops.lookup_cred(शून्य, शून्य, 0);
	अन्यथा
		new = rpcauth_bind_new_cred(task, lookupflags);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);
	put_rpccred(req->rq_cred);
	req->rq_cred = new;
	वापस 0;
पूर्ण

व्योम
put_rpccred(काष्ठा rpc_cred *cred)
अणु
	अगर (cred == शून्य)
		वापस;
	rcu_पढ़ो_lock();
	अगर (refcount_dec_and_test(&cred->cr_count))
		जाओ destroy;
	अगर (refcount_पढ़ो(&cred->cr_count) != 1 ||
	    !test_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags))
		जाओ out;
	अगर (test_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags) != 0) अणु
		cred->cr_expire = jअगरfies;
		rpcauth_lru_add(cred);
		/* Race अवरोधer */
		अगर (unlikely(!test_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags)))
			rpcauth_lru_हटाओ(cred);
	पूर्ण अन्यथा अगर (rpcauth_unhash_cred(cred)) अणु
		rpcauth_lru_हटाओ(cred);
		अगर (refcount_dec_and_test(&cred->cr_count))
			जाओ destroy;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस;
destroy:
	rcu_पढ़ो_unlock();
	cred->cr_ops->crdestroy(cred);
पूर्ण
EXPORT_SYMBOL_GPL(put_rpccred);

/**
 * rpcauth_marshcred - Append RPC credential to end of @xdr
 * @task: controlling RPC task
 * @xdr: xdr_stream containing initial portion of RPC Call header
 *
 * On success, an appropriate verअगरier is added to @xdr, @xdr is
 * updated to poपूर्णांक past the verअगरier, and zero is वापसed.
 * Otherwise, @xdr is in an undefined state and a negative त्रुटि_सं
 * is वापसed.
 */
पूर्णांक rpcauth_marshcred(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	स्थिर काष्ठा rpc_creकरोps *ops = task->tk_rqstp->rq_cred->cr_ops;

	वापस ops->crmarshal(task, xdr);
पूर्ण

/**
 * rpcauth_wrap_req_encode - XDR encode the RPC procedure
 * @task: controlling RPC task
 * @xdr: stream where on-the-wire bytes are to be marshalled
 *
 * On success, @xdr contains the encoded and wrapped message.
 * Otherwise, @xdr is in an undefined state.
 */
पूर्णांक rpcauth_wrap_req_encode(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	kxdreproc_t encode = task->tk_msg.rpc_proc->p_encode;

	encode(task->tk_rqstp, xdr, task->tk_msg.rpc_argp);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_wrap_req_encode);

/**
 * rpcauth_wrap_req - XDR encode and wrap the RPC procedure
 * @task: controlling RPC task
 * @xdr: stream where on-the-wire bytes are to be marshalled
 *
 * On success, @xdr contains the encoded and wrapped message,
 * and zero is वापसed. Otherwise, @xdr is in an undefined
 * state and a negative त्रुटि_सं is वापसed.
 */
पूर्णांक rpcauth_wrap_req(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	स्थिर काष्ठा rpc_creकरोps *ops = task->tk_rqstp->rq_cred->cr_ops;

	वापस ops->crwrap_req(task, xdr);
पूर्ण

/**
 * rpcauth_checkverf - Validate verअगरier in RPC Reply header
 * @task: controlling RPC task
 * @xdr: xdr_stream containing RPC Reply header
 *
 * On success, @xdr is updated to poपूर्णांक past the verअगरier and
 * zero is वापसed. Otherwise, @xdr is in an undefined state
 * and a negative त्रुटि_सं is वापसed.
 */
पूर्णांक
rpcauth_checkverf(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	स्थिर काष्ठा rpc_creकरोps *ops = task->tk_rqstp->rq_cred->cr_ops;

	वापस ops->crvalidate(task, xdr);
पूर्ण

/**
 * rpcauth_unwrap_resp_decode - Invoke XDR decode function
 * @task: controlling RPC task
 * @xdr: stream where the Reply message resides
 *
 * Returns zero on success; otherwise a negative त्रुटि_सं is वापसed.
 */
पूर्णांक
rpcauth_unwrap_resp_decode(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	kxdrdproc_t decode = task->tk_msg.rpc_proc->p_decode;

	वापस decode(task->tk_rqstp, xdr, task->tk_msg.rpc_resp);
पूर्ण
EXPORT_SYMBOL_GPL(rpcauth_unwrap_resp_decode);

/**
 * rpcauth_unwrap_resp - Invoke unwrap and decode function क्रम the cred
 * @task: controlling RPC task
 * @xdr: stream where the Reply message resides
 *
 * Returns zero on success; otherwise a negative त्रुटि_सं is वापसed.
 */
पूर्णांक
rpcauth_unwrap_resp(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	स्थिर काष्ठा rpc_creकरोps *ops = task->tk_rqstp->rq_cred->cr_ops;

	वापस ops->crunwrap_resp(task, xdr);
पूर्ण

bool
rpcauth_xmit_need_reencode(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_cred *cred = task->tk_rqstp->rq_cred;

	अगर (!cred || !cred->cr_ops->crneed_reencode)
		वापस false;
	वापस cred->cr_ops->crneed_reencode(task);
पूर्ण

पूर्णांक
rpcauth_refreshcred(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_cred	*cred;
	पूर्णांक err;

	cred = task->tk_rqstp->rq_cred;
	अगर (cred == शून्य) अणु
		err = rpcauth_bindcred(task, task->tk_msg.rpc_cred, task->tk_flags);
		अगर (err < 0)
			जाओ out;
		cred = task->tk_rqstp->rq_cred;
	पूर्ण

	err = cred->cr_ops->crrefresh(task);
out:
	अगर (err < 0)
		task->tk_status = err;
	वापस err;
पूर्ण

व्योम
rpcauth_invalcred(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_cred *cred = task->tk_rqstp->rq_cred;

	अगर (cred)
		clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags);
पूर्ण

पूर्णांक
rpcauth_uptodatecred(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_cred *cred = task->tk_rqstp->rq_cred;

	वापस cred == शून्य ||
		test_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags) != 0;
पूर्ण

अटल काष्ठा shrinker rpc_cred_shrinker = अणु
	.count_objects = rpcauth_cache_shrink_count,
	.scan_objects = rpcauth_cache_shrink_scan,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

पूर्णांक __init rpcauth_init_module(व्योम)
अणु
	पूर्णांक err;

	err = rpc_init_authunix();
	अगर (err < 0)
		जाओ out1;
	err = रेजिस्टर_shrinker(&rpc_cred_shrinker);
	अगर (err < 0)
		जाओ out2;
	वापस 0;
out2:
	rpc_destroy_authunix();
out1:
	वापस err;
पूर्ण

व्योम rpcauth_हटाओ_module(व्योम)
अणु
	rpc_destroy_authunix();
	unरेजिस्टर_shrinker(&rpc_cred_shrinker);
पूर्ण
