<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Basic authentication token and access key management
 *
 * Copyright (C) 2004-2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/poison.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/ima.h>
#समावेश <linux/err.h>
#समावेश "internal.h"

काष्ठा kmem_cache *key_jar;
काष्ठा rb_root		key_serial_tree; /* tree of keys indexed by serial */
DEFINE_SPINLOCK(key_serial_lock);

काष्ठा rb_root	key_user_tree; /* tree of quota records indexed by UID */
DEFINE_SPINLOCK(key_user_lock);

अचिन्हित पूर्णांक key_quota_root_maxkeys = 1000000;	/* root's key count quota */
अचिन्हित पूर्णांक key_quota_root_maxbytes = 25000000; /* root's key space quota */
अचिन्हित पूर्णांक key_quota_maxkeys = 200;		/* general key count quota */
अचिन्हित पूर्णांक key_quota_maxbytes = 20000;	/* general key space quota */

अटल LIST_HEAD(key_types_list);
अटल DECLARE_RWSEM(key_types_sem);

/* We serialise key instantiation and link */
DEFINE_MUTEX(key_स्थिरruction_mutex);

#अगर_घोषित KEY_DEBUGGING
व्योम __key_check(स्थिर काष्ठा key *key)
अणु
	prपूर्णांकk("__key_check: key %p {%08x} should be {%08x}\n",
	       key, key->magic, KEY_DEBUG_MAGIC);
	BUG();
पूर्ण
#पूर्ण_अगर

/*
 * Get the key quota record क्रम a user, allocating a new record अगर one करोesn't
 * alपढ़ोy exist.
 */
काष्ठा key_user *key_user_lookup(kuid_t uid)
अणु
	काष्ठा key_user *candidate = शून्य, *user;
	काष्ठा rb_node *parent, **p;

try_again:
	parent = शून्य;
	p = &key_user_tree.rb_node;
	spin_lock(&key_user_lock);

	/* search the tree क्रम a user record with a matching UID */
	जबतक (*p) अणु
		parent = *p;
		user = rb_entry(parent, काष्ठा key_user, node);

		अगर (uid_lt(uid, user->uid))
			p = &(*p)->rb_left;
		अन्यथा अगर (uid_gt(uid, user->uid))
			p = &(*p)->rb_right;
		अन्यथा
			जाओ found;
	पूर्ण

	/* अगर we get here, we failed to find a match in the tree */
	अगर (!candidate) अणु
		/* allocate a candidate user record अगर we करोn't alपढ़ोy have
		 * one */
		spin_unlock(&key_user_lock);

		user = शून्य;
		candidate = kदो_स्मृति(माप(काष्ठा key_user), GFP_KERNEL);
		अगर (unlikely(!candidate))
			जाओ out;

		/* the allocation may have scheduled, so we need to repeat the
		 * search lest someone अन्यथा added the record whilst we were
		 * asleep */
		जाओ try_again;
	पूर्ण

	/* अगर we get here, then the user record still hadn't appeared on the
	 * second pass - so we use the candidate record */
	refcount_set(&candidate->usage, 1);
	atomic_set(&candidate->nkeys, 0);
	atomic_set(&candidate->nikeys, 0);
	candidate->uid = uid;
	candidate->qnkeys = 0;
	candidate->qnbytes = 0;
	spin_lock_init(&candidate->lock);
	mutex_init(&candidate->cons_lock);

	rb_link_node(&candidate->node, parent, p);
	rb_insert_color(&candidate->node, &key_user_tree);
	spin_unlock(&key_user_lock);
	user = candidate;
	जाओ out;

	/* okay - we found a user record क्रम this UID */
found:
	refcount_inc(&user->usage);
	spin_unlock(&key_user_lock);
	kमुक्त(candidate);
out:
	वापस user;
पूर्ण

/*
 * Dispose of a user काष्ठाure
 */
व्योम key_user_put(काष्ठा key_user *user)
अणु
	अगर (refcount_dec_and_lock(&user->usage, &key_user_lock)) अणु
		rb_erase(&user->node, &key_user_tree);
		spin_unlock(&key_user_lock);

		kमुक्त(user);
	पूर्ण
पूर्ण

/*
 * Allocate a serial number क्रम a key.  These are asचिन्हित अक्रमomly to aव्योम
 * security issues through covert channel problems.
 */
अटल अंतरभूत व्योम key_alloc_serial(काष्ठा key *key)
अणु
	काष्ठा rb_node *parent, **p;
	काष्ठा key *xkey;

	/* propose a अक्रमom serial number and look क्रम a hole क्रम it in the
	 * serial number tree */
	करो अणु
		get_अक्रमom_bytes(&key->serial, माप(key->serial));

		key->serial >>= 1; /* negative numbers are not permitted */
	पूर्ण जबतक (key->serial < 3);

	spin_lock(&key_serial_lock);

attempt_insertion:
	parent = शून्य;
	p = &key_serial_tree.rb_node;

	जबतक (*p) अणु
		parent = *p;
		xkey = rb_entry(parent, काष्ठा key, serial_node);

		अगर (key->serial < xkey->serial)
			p = &(*p)->rb_left;
		अन्यथा अगर (key->serial > xkey->serial)
			p = &(*p)->rb_right;
		अन्यथा
			जाओ serial_exists;
	पूर्ण

	/* we've found a suitable hole - arrange क्रम this key to occupy it */
	rb_link_node(&key->serial_node, parent, p);
	rb_insert_color(&key->serial_node, &key_serial_tree);

	spin_unlock(&key_serial_lock);
	वापस;

	/* we found a key with the proposed serial number - walk the tree from
	 * that poपूर्णांक looking क्रम the next unused serial number */
serial_exists:
	क्रम (;;) अणु
		key->serial++;
		अगर (key->serial < 3) अणु
			key->serial = 3;
			जाओ attempt_insertion;
		पूर्ण

		parent = rb_next(parent);
		अगर (!parent)
			जाओ attempt_insertion;

		xkey = rb_entry(parent, काष्ठा key, serial_node);
		अगर (key->serial < xkey->serial)
			जाओ attempt_insertion;
	पूर्ण
पूर्ण

/**
 * key_alloc - Allocate a key of the specअगरied type.
 * @type: The type of key to allocate.
 * @desc: The key description to allow the key to be searched out.
 * @uid: The owner of the new key.
 * @gid: The group ID क्रम the new key's group permissions.
 * @cred: The credentials specअगरying UID namespace.
 * @perm: The permissions mask of the new key.
 * @flags: Flags specअगरying quota properties.
 * @restrict_link: Optional link restriction क्रम new keyrings.
 *
 * Allocate a key of the specअगरied type with the attributes given.  The key is
 * वापसed in an uninstantiated state and the caller needs to instantiate the
 * key beक्रमe वापसing.
 *
 * The restrict_link काष्ठाure (अगर not शून्य) will be मुक्तd when the
 * keyring is destroyed, so it must be dynamically allocated.
 *
 * The user's key count quota is updated to reflect the creation of the key and
 * the user's key data quota has the शेष क्रम the key type reserved.  The
 * instantiation function should amend this as necessary.  If insufficient
 * quota is available, -EDQUOT will be वापसed.
 *
 * The LSM security modules can prevent a key being created, in which हाल
 * -EACCES will be वापसed.
 *
 * Returns a poपूर्णांकer to the new key अगर successful and an error code otherwise.
 *
 * Note that the caller needs to ensure the key type isn't uninstantiated.
 * Internally this can be करोne by locking key_types_sem.  Externally, this can
 * be करोne by either never unरेजिस्टरing the key type, or making sure
 * key_alloc() calls करोn't race with module unloading.
 */
काष्ठा key *key_alloc(काष्ठा key_type *type, स्थिर अक्षर *desc,
		      kuid_t uid, kgid_t gid, स्थिर काष्ठा cred *cred,
		      key_perm_t perm, अचिन्हित दीर्घ flags,
		      काष्ठा key_restriction *restrict_link)
अणु
	काष्ठा key_user *user = शून्य;
	काष्ठा key *key;
	माप_प्रकार desclen, quotalen;
	पूर्णांक ret;

	key = ERR_PTR(-EINVAL);
	अगर (!desc || !*desc)
		जाओ error;

	अगर (type->vet_description) अणु
		ret = type->vet_description(desc);
		अगर (ret < 0) अणु
			key = ERR_PTR(ret);
			जाओ error;
		पूर्ण
	पूर्ण

	desclen = म_माप(desc);
	quotalen = desclen + 1 + type->def_datalen;

	/* get hold of the key tracking क्रम this user */
	user = key_user_lookup(uid);
	अगर (!user)
		जाओ no_memory_1;

	/* check that the user's quota permits allocation of another key and
	 * its description */
	अगर (!(flags & KEY_ALLOC_NOT_IN_QUOTA)) अणु
		अचिन्हित maxkeys = uid_eq(uid, GLOBAL_ROOT_UID) ?
			key_quota_root_maxkeys : key_quota_maxkeys;
		अचिन्हित maxbytes = uid_eq(uid, GLOBAL_ROOT_UID) ?
			key_quota_root_maxbytes : key_quota_maxbytes;

		spin_lock(&user->lock);
		अगर (!(flags & KEY_ALLOC_QUOTA_OVERRUN)) अणु
			अगर (user->qnkeys + 1 > maxkeys ||
			    user->qnbytes + quotalen > maxbytes ||
			    user->qnbytes + quotalen < user->qnbytes)
				जाओ no_quota;
		पूर्ण

		user->qnkeys++;
		user->qnbytes += quotalen;
		spin_unlock(&user->lock);
	पूर्ण

	/* allocate and initialise the key and its description */
	key = kmem_cache_zalloc(key_jar, GFP_KERNEL);
	अगर (!key)
		जाओ no_memory_2;

	key->index_key.desc_len = desclen;
	key->index_key.description = kmemdup(desc, desclen + 1, GFP_KERNEL);
	अगर (!key->index_key.description)
		जाओ no_memory_3;
	key->index_key.type = type;
	key_set_index_key(&key->index_key);

	refcount_set(&key->usage, 1);
	init_rwsem(&key->sem);
	lockdep_set_class(&key->sem, &type->lock_class);
	key->user = user;
	key->quotalen = quotalen;
	key->datalen = type->def_datalen;
	key->uid = uid;
	key->gid = gid;
	key->perm = perm;
	key->restrict_link = restrict_link;
	key->last_used_at = kसमय_get_real_seconds();

	अगर (!(flags & KEY_ALLOC_NOT_IN_QUOTA))
		key->flags |= 1 << KEY_FLAG_IN_QUOTA;
	अगर (flags & KEY_ALLOC_BUILT_IN)
		key->flags |= 1 << KEY_FLAG_BUILTIN;
	अगर (flags & KEY_ALLOC_UID_KEYRING)
		key->flags |= 1 << KEY_FLAG_UID_KEYRING;
	अगर (flags & KEY_ALLOC_SET_KEEP)
		key->flags |= 1 << KEY_FLAG_KEEP;

#अगर_घोषित KEY_DEBUGGING
	key->magic = KEY_DEBUG_MAGIC;
#पूर्ण_अगर

	/* let the security module know about the key */
	ret = security_key_alloc(key, cred, flags);
	अगर (ret < 0)
		जाओ security_error;

	/* publish the key by giving it a serial number */
	refcount_inc(&key->करोमुख्य_tag->usage);
	atomic_inc(&user->nkeys);
	key_alloc_serial(key);

error:
	वापस key;

security_error:
	kमुक्त(key->description);
	kmem_cache_मुक्त(key_jar, key);
	अगर (!(flags & KEY_ALLOC_NOT_IN_QUOTA)) अणु
		spin_lock(&user->lock);
		user->qnkeys--;
		user->qnbytes -= quotalen;
		spin_unlock(&user->lock);
	पूर्ण
	key_user_put(user);
	key = ERR_PTR(ret);
	जाओ error;

no_memory_3:
	kmem_cache_मुक्त(key_jar, key);
no_memory_2:
	अगर (!(flags & KEY_ALLOC_NOT_IN_QUOTA)) अणु
		spin_lock(&user->lock);
		user->qnkeys--;
		user->qnbytes -= quotalen;
		spin_unlock(&user->lock);
	पूर्ण
	key_user_put(user);
no_memory_1:
	key = ERR_PTR(-ENOMEM);
	जाओ error;

no_quota:
	spin_unlock(&user->lock);
	key_user_put(user);
	key = ERR_PTR(-EDQUOT);
	जाओ error;
पूर्ण
EXPORT_SYMBOL(key_alloc);

/**
 * key_payload_reserve - Adjust data quota reservation क्रम the key's payload
 * @key: The key to make the reservation क्रम.
 * @datalen: The amount of data payload the caller now wants.
 *
 * Adjust the amount of the owning user's key data quota that a key reserves.
 * If the amount is increased, then -EDQUOT may be वापसed अगर there isn't
 * enough मुक्त quota available.
 *
 * If successful, 0 is वापसed.
 */
पूर्णांक key_payload_reserve(काष्ठा key *key, माप_प्रकार datalen)
अणु
	पूर्णांक delta = (पूर्णांक)datalen - key->datalen;
	पूर्णांक ret = 0;

	key_check(key);

	/* conढाँचा the quota adjusपंचांगent */
	अगर (delta != 0 && test_bit(KEY_FLAG_IN_QUOTA, &key->flags)) अणु
		अचिन्हित maxbytes = uid_eq(key->user->uid, GLOBAL_ROOT_UID) ?
			key_quota_root_maxbytes : key_quota_maxbytes;

		spin_lock(&key->user->lock);

		अगर (delta > 0 &&
		    (key->user->qnbytes + delta > maxbytes ||
		     key->user->qnbytes + delta < key->user->qnbytes)) अणु
			ret = -EDQUOT;
		पूर्ण
		अन्यथा अणु
			key->user->qnbytes += delta;
			key->quotalen += delta;
		पूर्ण
		spin_unlock(&key->user->lock);
	पूर्ण

	/* change the recorded data length अगर that didn't generate an error */
	अगर (ret == 0)
		key->datalen = datalen;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(key_payload_reserve);

/*
 * Change the key state to being instantiated.
 */
अटल व्योम mark_key_instantiated(काष्ठा key *key, पूर्णांक reject_error)
अणु
	/* Commit the payload beक्रमe setting the state; barrier versus
	 * key_पढ़ो_state().
	 */
	smp_store_release(&key->state,
			  (reject_error < 0) ? reject_error : KEY_IS_POSITIVE);
पूर्ण

/*
 * Instantiate a key and link it पूर्णांकo the target keyring atomically.  Must be
 * called with the target keyring's semaphore writelocked.  The target key's
 * semaphore need not be locked as instantiation is serialised by
 * key_स्थिरruction_mutex.
 */
अटल पूर्णांक __key_instantiate_and_link(काष्ठा key *key,
				      काष्ठा key_preparsed_payload *prep,
				      काष्ठा key *keyring,
				      काष्ठा key *authkey,
				      काष्ठा assoc_array_edit **_edit)
अणु
	पूर्णांक ret, awaken;

	key_check(key);
	key_check(keyring);

	awaken = 0;
	ret = -EBUSY;

	mutex_lock(&key_स्थिरruction_mutex);

	/* can't instantiate twice */
	अगर (key->state == KEY_IS_UNINSTANTIATED) अणु
		/* instantiate the key */
		ret = key->type->instantiate(key, prep);

		अगर (ret == 0) अणु
			/* mark the key as being instantiated */
			atomic_inc(&key->user->nikeys);
			mark_key_instantiated(key, 0);
			notअगरy_key(key, NOTIFY_KEY_INSTANTIATED, 0);

			अगर (test_and_clear_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags))
				awaken = 1;

			/* and link it पूर्णांकo the destination keyring */
			अगर (keyring) अणु
				अगर (test_bit(KEY_FLAG_KEEP, &keyring->flags))
					set_bit(KEY_FLAG_KEEP, &key->flags);

				__key_link(keyring, key, _edit);
			पूर्ण

			/* disable the authorisation key */
			अगर (authkey)
				key_invalidate(authkey);

			अगर (prep->expiry != TIME64_MAX) अणु
				key->expiry = prep->expiry;
				key_schedule_gc(prep->expiry + key_gc_delay);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&key_स्थिरruction_mutex);

	/* wake up anyone रुकोing क्रम a key to be स्थिरructed */
	अगर (awaken)
		wake_up_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT);

	वापस ret;
पूर्ण

/**
 * key_instantiate_and_link - Instantiate a key and link it पूर्णांकo the keyring.
 * @key: The key to instantiate.
 * @data: The data to use to instantiate the keyring.
 * @datalen: The length of @data.
 * @keyring: Keyring to create a link in on success (or शून्य).
 * @authkey: The authorisation token permitting instantiation.
 *
 * Instantiate a key that's in the uninstantiated state using the provided data
 * and, अगर successful, link it in to the destination keyring अगर one is
 * supplied.
 *
 * If successful, 0 is वापसed, the authorisation token is revoked and anyone
 * रुकोing क्रम the key is woken up.  If the key was alपढ़ोy instantiated,
 * -EBUSY will be वापसed.
 */
पूर्णांक key_instantiate_and_link(काष्ठा key *key,
			     स्थिर व्योम *data,
			     माप_प्रकार datalen,
			     काष्ठा key *keyring,
			     काष्ठा key *authkey)
अणु
	काष्ठा key_preparsed_payload prep;
	काष्ठा assoc_array_edit *edit = शून्य;
	पूर्णांक ret;

	स_रखो(&prep, 0, माप(prep));
	prep.orig_description = key->description;
	prep.data = data;
	prep.datalen = datalen;
	prep.quotalen = key->type->def_datalen;
	prep.expiry = TIME64_MAX;
	अगर (key->type->preparse) अणु
		ret = key->type->preparse(&prep);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	अगर (keyring) अणु
		ret = __key_link_lock(keyring, &key->index_key);
		अगर (ret < 0)
			जाओ error;

		ret = __key_link_begin(keyring, &key->index_key, &edit);
		अगर (ret < 0)
			जाओ error_link_end;

		अगर (keyring->restrict_link && keyring->restrict_link->check) अणु
			काष्ठा key_restriction *keyres = keyring->restrict_link;

			ret = keyres->check(keyring, key->type, &prep.payload,
					    keyres->key);
			अगर (ret < 0)
				जाओ error_link_end;
		पूर्ण
	पूर्ण

	ret = __key_instantiate_and_link(key, &prep, keyring, authkey, &edit);

error_link_end:
	अगर (keyring)
		__key_link_end(keyring, &key->index_key, edit);

error:
	अगर (key->type->preparse)
		key->type->मुक्त_preparse(&prep);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(key_instantiate_and_link);

/**
 * key_reject_and_link - Negatively instantiate a key and link it पूर्णांकo the keyring.
 * @key: The key to instantiate.
 * @समयout: The समयout on the negative key.
 * @error: The error to वापस when the key is hit.
 * @keyring: Keyring to create a link in on success (or शून्य).
 * @authkey: The authorisation token permitting instantiation.
 *
 * Negatively instantiate a key that's in the uninstantiated state and, अगर
 * successful, set its समयout and stored error and link it in to the
 * destination keyring अगर one is supplied.  The key and any links to the key
 * will be स्वतःmatically garbage collected after the समयout expires.
 *
 * Negative keys are used to rate limit repeated request_key() calls by causing
 * them to वापस the stored error code (typically ENOKEY) until the negative
 * key expires.
 *
 * If successful, 0 is वापसed, the authorisation token is revoked and anyone
 * रुकोing क्रम the key is woken up.  If the key was alपढ़ोy instantiated,
 * -EBUSY will be वापसed.
 */
पूर्णांक key_reject_and_link(काष्ठा key *key,
			अचिन्हित समयout,
			अचिन्हित error,
			काष्ठा key *keyring,
			काष्ठा key *authkey)
अणु
	काष्ठा assoc_array_edit *edit = शून्य;
	पूर्णांक ret, awaken, link_ret = 0;

	key_check(key);
	key_check(keyring);

	awaken = 0;
	ret = -EBUSY;

	अगर (keyring) अणु
		अगर (keyring->restrict_link)
			वापस -EPERM;

		link_ret = __key_link_lock(keyring, &key->index_key);
		अगर (link_ret == 0) अणु
			link_ret = __key_link_begin(keyring, &key->index_key, &edit);
			अगर (link_ret < 0)
				__key_link_end(keyring, &key->index_key, edit);
		पूर्ण
	पूर्ण

	mutex_lock(&key_स्थिरruction_mutex);

	/* can't instantiate twice */
	अगर (key->state == KEY_IS_UNINSTANTIATED) अणु
		/* mark the key as being negatively instantiated */
		atomic_inc(&key->user->nikeys);
		mark_key_instantiated(key, -error);
		notअगरy_key(key, NOTIFY_KEY_INSTANTIATED, -error);
		key->expiry = kसमय_get_real_seconds() + समयout;
		key_schedule_gc(key->expiry + key_gc_delay);

		अगर (test_and_clear_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags))
			awaken = 1;

		ret = 0;

		/* and link it पूर्णांकo the destination keyring */
		अगर (keyring && link_ret == 0)
			__key_link(keyring, key, &edit);

		/* disable the authorisation key */
		अगर (authkey)
			key_invalidate(authkey);
	पूर्ण

	mutex_unlock(&key_स्थिरruction_mutex);

	अगर (keyring && link_ret == 0)
		__key_link_end(keyring, &key->index_key, edit);

	/* wake up anyone रुकोing क्रम a key to be स्थिरructed */
	अगर (awaken)
		wake_up_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT);

	वापस ret == 0 ? link_ret : ret;
पूर्ण
EXPORT_SYMBOL(key_reject_and_link);

/**
 * key_put - Discard a reference to a key.
 * @key: The key to discard a reference from.
 *
 * Discard a reference to a key, and when all the references are gone, we
 * schedule the cleanup task to come and pull it out of the tree in process
 * context at some later समय.
 */
व्योम key_put(काष्ठा key *key)
अणु
	अगर (key) अणु
		key_check(key);

		अगर (refcount_dec_and_test(&key->usage))
			schedule_work(&key_gc_work);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(key_put);

/*
 * Find a key by its serial number.
 */
काष्ठा key *key_lookup(key_serial_t id)
अणु
	काष्ठा rb_node *n;
	काष्ठा key *key;

	spin_lock(&key_serial_lock);

	/* search the tree क्रम the specअगरied key */
	n = key_serial_tree.rb_node;
	जबतक (n) अणु
		key = rb_entry(n, काष्ठा key, serial_node);

		अगर (id < key->serial)
			n = n->rb_left;
		अन्यथा अगर (id > key->serial)
			n = n->rb_right;
		अन्यथा
			जाओ found;
	पूर्ण

not_found:
	key = ERR_PTR(-ENOKEY);
	जाओ error;

found:
	/* A key is allowed to be looked up only अगर someone still owns a
	 * reference to it - otherwise it's aरुकोing the gc.
	 */
	अगर (!refcount_inc_not_zero(&key->usage))
		जाओ not_found;

error:
	spin_unlock(&key_serial_lock);
	वापस key;
पूर्ण

/*
 * Find and lock the specअगरied key type against removal.
 *
 * We वापस with the sem पढ़ो-locked अगर successful.  If the type wasn't
 * available -ENOKEY is वापसed instead.
 */
काष्ठा key_type *key_type_lookup(स्थिर अक्षर *type)
अणु
	काष्ठा key_type *ktype;

	करोwn_पढ़ो(&key_types_sem);

	/* look up the key type to see अगर it's one of the रेजिस्टरed kernel
	 * types */
	list_क्रम_each_entry(ktype, &key_types_list, link) अणु
		अगर (म_भेद(ktype->name, type) == 0)
			जाओ found_kernel_type;
	पूर्ण

	up_पढ़ो(&key_types_sem);
	ktype = ERR_PTR(-ENOKEY);

found_kernel_type:
	वापस ktype;
पूर्ण

व्योम key_set_समयout(काष्ठा key *key, अचिन्हित समयout)
अणु
	समय64_t expiry = 0;

	/* make the changes with the locks held to prevent races */
	करोwn_ग_लिखो(&key->sem);

	अगर (समयout > 0)
		expiry = kसमय_get_real_seconds() + समयout;

	key->expiry = expiry;
	key_schedule_gc(key->expiry + key_gc_delay);

	up_ग_लिखो(&key->sem);
पूर्ण
EXPORT_SYMBOL_GPL(key_set_समयout);

/*
 * Unlock a key type locked by key_type_lookup().
 */
व्योम key_type_put(काष्ठा key_type *ktype)
अणु
	up_पढ़ो(&key_types_sem);
पूर्ण

/*
 * Attempt to update an existing key.
 *
 * The key is given to us with an incremented refcount that we need to discard
 * अगर we get an error.
 */
अटल अंतरभूत key_ref_t __key_update(key_ref_t key_ref,
				     काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा key *key = key_ref_to_ptr(key_ref);
	पूर्णांक ret;

	/* need ग_लिखो permission on the key to update it */
	ret = key_permission(key_ref, KEY_NEED_WRITE);
	अगर (ret < 0)
		जाओ error;

	ret = -EEXIST;
	अगर (!key->type->update)
		जाओ error;

	करोwn_ग_लिखो(&key->sem);

	ret = key->type->update(key, prep);
	अगर (ret == 0) अणु
		/* Updating a negative key positively instantiates it */
		mark_key_instantiated(key, 0);
		notअगरy_key(key, NOTIFY_KEY_UPDATED, 0);
	पूर्ण

	up_ग_लिखो(&key->sem);

	अगर (ret < 0)
		जाओ error;
out:
	वापस key_ref;

error:
	key_put(key);
	key_ref = ERR_PTR(ret);
	जाओ out;
पूर्ण

/**
 * key_create_or_update - Update or create and instantiate a key.
 * @keyring_ref: A poपूर्णांकer to the destination keyring with possession flag.
 * @type: The type of key.
 * @description: The searchable description क्रम the key.
 * @payload: The data to use to instantiate or update the key.
 * @plen: The length of @payload.
 * @perm: The permissions mask क्रम a new key.
 * @flags: The quota flags क्रम a new key.
 *
 * Search the destination keyring क्रम a key of the same description and अगर one
 * is found, update it, otherwise create and instantiate a new one and create a
 * link to it from that keyring.
 *
 * If perm is KEY_PERM_UNDEF then an appropriate key permissions mask will be
 * concocted.
 *
 * Returns a poपूर्णांकer to the new key अगर successful, -ENODEV अगर the key type
 * wasn't available, -ENOTDIR if the keyring wasn't a keyring, -EACCES अगर the
 * caller isn't permitted to modअगरy the keyring or the LSM did not permit
 * creation of the key.
 *
 * On success, the possession flag from the keyring ref will be tacked on to
 * the key ref beक्रमe it is वापसed.
 */
key_ref_t key_create_or_update(key_ref_t keyring_ref,
			       स्थिर अक्षर *type,
			       स्थिर अक्षर *description,
			       स्थिर व्योम *payload,
			       माप_प्रकार plen,
			       key_perm_t perm,
			       अचिन्हित दीर्घ flags)
अणु
	काष्ठा keyring_index_key index_key = अणु
		.description	= description,
	पूर्ण;
	काष्ठा key_preparsed_payload prep;
	काष्ठा assoc_array_edit *edit = शून्य;
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा key *keyring, *key = शून्य;
	key_ref_t key_ref;
	पूर्णांक ret;
	काष्ठा key_restriction *restrict_link = शून्य;

	/* look up the key type to see अगर it's one of the रेजिस्टरed kernel
	 * types */
	index_key.type = key_type_lookup(type);
	अगर (IS_ERR(index_key.type)) अणु
		key_ref = ERR_PTR(-ENODEV);
		जाओ error;
	पूर्ण

	key_ref = ERR_PTR(-EINVAL);
	अगर (!index_key.type->instantiate ||
	    (!index_key.description && !index_key.type->preparse))
		जाओ error_put_type;

	keyring = key_ref_to_ptr(keyring_ref);

	key_check(keyring);

	अगर (!(flags & KEY_ALLOC_BYPASS_RESTRICTION))
		restrict_link = keyring->restrict_link;

	key_ref = ERR_PTR(-ENOTसूची);
	अगर (keyring->type != &key_type_keyring)
		जाओ error_put_type;

	स_रखो(&prep, 0, माप(prep));
	prep.orig_description = description;
	prep.data = payload;
	prep.datalen = plen;
	prep.quotalen = index_key.type->def_datalen;
	prep.expiry = TIME64_MAX;
	अगर (index_key.type->preparse) अणु
		ret = index_key.type->preparse(&prep);
		अगर (ret < 0) अणु
			key_ref = ERR_PTR(ret);
			जाओ error_मुक्त_prep;
		पूर्ण
		अगर (!index_key.description)
			index_key.description = prep.description;
		key_ref = ERR_PTR(-EINVAL);
		अगर (!index_key.description)
			जाओ error_मुक्त_prep;
	पूर्ण
	index_key.desc_len = म_माप(index_key.description);
	key_set_index_key(&index_key);

	ret = __key_link_lock(keyring, &index_key);
	अगर (ret < 0) अणु
		key_ref = ERR_PTR(ret);
		जाओ error_मुक्त_prep;
	पूर्ण

	ret = __key_link_begin(keyring, &index_key, &edit);
	अगर (ret < 0) अणु
		key_ref = ERR_PTR(ret);
		जाओ error_link_end;
	पूर्ण

	अगर (restrict_link && restrict_link->check) अणु
		ret = restrict_link->check(keyring, index_key.type,
					   &prep.payload, restrict_link->key);
		अगर (ret < 0) अणु
			key_ref = ERR_PTR(ret);
			जाओ error_link_end;
		पूर्ण
	पूर्ण

	/* अगर we're going to allocate a new key, we're going to have
	 * to modअगरy the keyring */
	ret = key_permission(keyring_ref, KEY_NEED_WRITE);
	अगर (ret < 0) अणु
		key_ref = ERR_PTR(ret);
		जाओ error_link_end;
	पूर्ण

	/* अगर it's possible to update this type of key, search क्रम an existing
	 * key of the same type and description in the destination keyring and
	 * update that instead अगर possible
	 */
	अगर (index_key.type->update) अणु
		key_ref = find_key_to_update(keyring_ref, &index_key);
		अगर (key_ref)
			जाओ found_matching_key;
	पूर्ण

	/* अगर the client करोesn't provide, decide on the permissions we want */
	अगर (perm == KEY_PERM_UNDEF) अणु
		perm = KEY_POS_VIEW | KEY_POS_SEARCH | KEY_POS_LINK | KEY_POS_SETATTR;
		perm |= KEY_USR_VIEW;

		अगर (index_key.type->पढ़ो)
			perm |= KEY_POS_READ;

		अगर (index_key.type == &key_type_keyring ||
		    index_key.type->update)
			perm |= KEY_POS_WRITE;
	पूर्ण

	/* allocate a new key */
	key = key_alloc(index_key.type, index_key.description,
			cred->fsuid, cred->fsgid, cred, perm, flags, शून्य);
	अगर (IS_ERR(key)) अणु
		key_ref = ERR_CAST(key);
		जाओ error_link_end;
	पूर्ण

	/* instantiate it and link it पूर्णांकo the target keyring */
	ret = __key_instantiate_and_link(key, &prep, keyring, शून्य, &edit);
	अगर (ret < 0) अणु
		key_put(key);
		key_ref = ERR_PTR(ret);
		जाओ error_link_end;
	पूर्ण

	ima_post_key_create_or_update(keyring, key, payload, plen,
				      flags, true);

	key_ref = make_key_ref(key, is_key_possessed(keyring_ref));

error_link_end:
	__key_link_end(keyring, &index_key, edit);
error_मुक्त_prep:
	अगर (index_key.type->preparse)
		index_key.type->मुक्त_preparse(&prep);
error_put_type:
	key_type_put(index_key.type);
error:
	वापस key_ref;

 found_matching_key:
	/* we found a matching key, so we're going to try to update it
	 * - we can drop the locks first as we have the key pinned
	 */
	__key_link_end(keyring, &index_key, edit);

	key = key_ref_to_ptr(key_ref);
	अगर (test_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags)) अणु
		ret = रुको_क्रम_key_स्थिरruction(key, true);
		अगर (ret < 0) अणु
			key_ref_put(key_ref);
			key_ref = ERR_PTR(ret);
			जाओ error_मुक्त_prep;
		पूर्ण
	पूर्ण

	key_ref = __key_update(key_ref, &prep);

	अगर (!IS_ERR(key_ref))
		ima_post_key_create_or_update(keyring, key,
					      payload, plen,
					      flags, false);

	जाओ error_मुक्त_prep;
पूर्ण
EXPORT_SYMBOL(key_create_or_update);

/**
 * key_update - Update a key's contents.
 * @key_ref: The poपूर्णांकer (plus possession flag) to the key.
 * @payload: The data to be used to update the key.
 * @plen: The length of @payload.
 *
 * Attempt to update the contents of a key with the given payload data.  The
 * caller must be granted Write permission on the key.  Negative keys can be
 * instantiated by this method.
 *
 * Returns 0 on success, -EACCES अगर not permitted and -EOPNOTSUPP अगर the key
 * type करोes not support updating.  The key type may वापस other errors.
 */
पूर्णांक key_update(key_ref_t key_ref, स्थिर व्योम *payload, माप_प्रकार plen)
अणु
	काष्ठा key_preparsed_payload prep;
	काष्ठा key *key = key_ref_to_ptr(key_ref);
	पूर्णांक ret;

	key_check(key);

	/* the key must be writable */
	ret = key_permission(key_ref, KEY_NEED_WRITE);
	अगर (ret < 0)
		वापस ret;

	/* attempt to update it अगर supported */
	अगर (!key->type->update)
		वापस -EOPNOTSUPP;

	स_रखो(&prep, 0, माप(prep));
	prep.data = payload;
	prep.datalen = plen;
	prep.quotalen = key->type->def_datalen;
	prep.expiry = TIME64_MAX;
	अगर (key->type->preparse) अणु
		ret = key->type->preparse(&prep);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	करोwn_ग_लिखो(&key->sem);

	ret = key->type->update(key, &prep);
	अगर (ret == 0) अणु
		/* Updating a negative key positively instantiates it */
		mark_key_instantiated(key, 0);
		notअगरy_key(key, NOTIFY_KEY_UPDATED, 0);
	पूर्ण

	up_ग_लिखो(&key->sem);

error:
	अगर (key->type->preparse)
		key->type->मुक्त_preparse(&prep);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(key_update);

/**
 * key_revoke - Revoke a key.
 * @key: The key to be revoked.
 *
 * Mark a key as being revoked and ask the type to मुक्त up its resources.  The
 * revocation समयout is set and the key and all its links will be
 * स्वतःmatically garbage collected after key_gc_delay amount of समय अगर they
 * are not manually dealt with first.
 */
व्योम key_revoke(काष्ठा key *key)
अणु
	समय64_t समय;

	key_check(key);

	/* make sure no one's trying to change or use the key when we mark it
	 * - we tell lockdep that we might nest because we might be revoking an
	 *   authorisation key whilst holding the sem on a key we've just
	 *   instantiated
	 */
	करोwn_ग_लिखो_nested(&key->sem, 1);
	अगर (!test_and_set_bit(KEY_FLAG_REVOKED, &key->flags)) अणु
		notअगरy_key(key, NOTIFY_KEY_REVOKED, 0);
		अगर (key->type->revoke)
			key->type->revoke(key);

		/* set the death समय to no more than the expiry समय */
		समय = kसमय_get_real_seconds();
		अगर (key->revoked_at == 0 || key->revoked_at > समय) अणु
			key->revoked_at = समय;
			key_schedule_gc(key->revoked_at + key_gc_delay);
		पूर्ण
	पूर्ण

	up_ग_लिखो(&key->sem);
पूर्ण
EXPORT_SYMBOL(key_revoke);

/**
 * key_invalidate - Invalidate a key.
 * @key: The key to be invalidated.
 *
 * Mark a key as being invalidated and have it cleaned up immediately.  The key
 * is ignored by all searches and other operations from this poपूर्णांक.
 */
व्योम key_invalidate(काष्ठा key *key)
अणु
	kenter("%d", key_serial(key));

	key_check(key);

	अगर (!test_bit(KEY_FLAG_INVALIDATED, &key->flags)) अणु
		करोwn_ग_लिखो_nested(&key->sem, 1);
		अगर (!test_and_set_bit(KEY_FLAG_INVALIDATED, &key->flags)) अणु
			notअगरy_key(key, NOTIFY_KEY_INVALIDATED, 0);
			key_schedule_gc_links();
		पूर्ण
		up_ग_लिखो(&key->sem);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(key_invalidate);

/**
 * generic_key_instantiate - Simple instantiation of a key from preparsed data
 * @key: The key to be instantiated
 * @prep: The preparsed data to load.
 *
 * Instantiate a key from preparsed data.  We assume we can just copy the data
 * in directly and clear the old poपूर्णांकers.
 *
 * This can be poपूर्णांकed to directly by the key type instantiate op poपूर्णांकer.
 */
पूर्णांक generic_key_instantiate(काष्ठा key *key, काष्ठा key_preparsed_payload *prep)
अणु
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	ret = key_payload_reserve(key, prep->quotalen);
	अगर (ret == 0) अणु
		rcu_assign_keypoपूर्णांकer(key, prep->payload.data[0]);
		key->payload.data[1] = prep->payload.data[1];
		key->payload.data[2] = prep->payload.data[2];
		key->payload.data[3] = prep->payload.data[3];
		prep->payload.data[0] = शून्य;
		prep->payload.data[1] = शून्य;
		prep->payload.data[2] = शून्य;
		prep->payload.data[3] = शून्य;
	पूर्ण
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(generic_key_instantiate);

/**
 * रेजिस्टर_key_type - Register a type of key.
 * @ktype: The new key type.
 *
 * Register a new key type.
 *
 * Returns 0 on success or -EEXIST अगर a type of this name alपढ़ोy exists.
 */
पूर्णांक रेजिस्टर_key_type(काष्ठा key_type *ktype)
अणु
	काष्ठा key_type *p;
	पूर्णांक ret;

	स_रखो(&ktype->lock_class, 0, माप(ktype->lock_class));

	ret = -EEXIST;
	करोwn_ग_लिखो(&key_types_sem);

	/* disallow key types with the same name */
	list_क्रम_each_entry(p, &key_types_list, link) अणु
		अगर (म_भेद(p->name, ktype->name) == 0)
			जाओ out;
	पूर्ण

	/* store the type */
	list_add(&ktype->link, &key_types_list);

	pr_notice("Key type %s registered\n", ktype->name);
	ret = 0;

out:
	up_ग_लिखो(&key_types_sem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_key_type);

/**
 * unरेजिस्टर_key_type - Unरेजिस्टर a type of key.
 * @ktype: The key type.
 *
 * Unरेजिस्टर a key type and mark all the extant keys of this type as dead.
 * Those keys of this type are then destroyed to get rid of their payloads and
 * they and their links will be garbage collected as soon as possible.
 */
व्योम unरेजिस्टर_key_type(काष्ठा key_type *ktype)
अणु
	करोwn_ग_लिखो(&key_types_sem);
	list_del_init(&ktype->link);
	करोwngrade_ग_लिखो(&key_types_sem);
	key_gc_keytype(ktype);
	pr_notice("Key type %s unregistered\n", ktype->name);
	up_पढ़ो(&key_types_sem);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_key_type);

/*
 * Initialise the key management state.
 */
व्योम __init key_init(व्योम)
अणु
	/* allocate a slab in which we can store keys */
	key_jar = kmem_cache_create("key_jar", माप(काष्ठा key),
			0, SLAB_HWCACHE_ALIGN|SLAB_PANIC, शून्य);

	/* add the special key types */
	list_add_tail(&key_type_keyring.link, &key_types_list);
	list_add_tail(&key_type_dead.link, &key_types_list);
	list_add_tail(&key_type_user.link, &key_types_list);
	list_add_tail(&key_type_logon.link, &key_types_list);

	/* record the root user tracking */
	rb_link_node(&root_key_user.node,
		     शून्य,
		     &key_user_tree.rb_node);

	rb_insert_color(&root_key_user.node,
			&key_user_tree);
पूर्ण
