<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS security handling
 *
 * Copyright (C) 2007, 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sched.h>
#समावेश <linux/hashtable.h>
#समावेश <keys/rxrpc-type.h>
#समावेश "internal.h"

अटल DEFINE_HASHTABLE(afs_permits_cache, 10);
अटल DEFINE_SPINLOCK(afs_permits_lock);

/*
 * get a key
 */
काष्ठा key *afs_request_key(काष्ठा afs_cell *cell)
अणु
	काष्ठा key *key;

	_enter("{%x}", key_serial(cell->anonymous_key));

	_debug("key %s", cell->anonymous_key->description);
	key = request_key_net(&key_type_rxrpc, cell->anonymous_key->description,
			      cell->net->net, शून्य);
	अगर (IS_ERR(key)) अणु
		अगर (PTR_ERR(key) != -ENOKEY) अणु
			_leave(" = %ld", PTR_ERR(key));
			वापस key;
		पूर्ण

		/* act as anonymous user */
		_leave(" = {%x} [anon]", key_serial(cell->anonymous_key));
		वापस key_get(cell->anonymous_key);
	पूर्ण अन्यथा अणु
		/* act as authorised user */
		_leave(" = {%x} [auth]", key_serial(key));
		वापस key;
	पूर्ण
पूर्ण

/*
 * Get a key when pathwalk is in rcuwalk mode.
 */
काष्ठा key *afs_request_key_rcu(काष्ठा afs_cell *cell)
अणु
	काष्ठा key *key;

	_enter("{%x}", key_serial(cell->anonymous_key));

	_debug("key %s", cell->anonymous_key->description);
	key = request_key_net_rcu(&key_type_rxrpc,
				  cell->anonymous_key->description,
				  cell->net->net);
	अगर (IS_ERR(key)) अणु
		अगर (PTR_ERR(key) != -ENOKEY) अणु
			_leave(" = %ld", PTR_ERR(key));
			वापस key;
		पूर्ण

		/* act as anonymous user */
		_leave(" = {%x} [anon]", key_serial(cell->anonymous_key));
		वापस key_get(cell->anonymous_key);
	पूर्ण अन्यथा अणु
		/* act as authorised user */
		_leave(" = {%x} [auth]", key_serial(key));
		वापस key;
	पूर्ण
पूर्ण

/*
 * Dispose of a list of permits.
 */
अटल व्योम afs_permits_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा afs_permits *permits =
		container_of(rcu, काष्ठा afs_permits, rcu);
	पूर्णांक i;

	क्रम (i = 0; i < permits->nr_permits; i++)
		key_put(permits->permits[i].key);
	kमुक्त(permits);
पूर्ण

/*
 * Discard a permission cache.
 */
व्योम afs_put_permits(काष्ठा afs_permits *permits)
अणु
	अगर (permits && refcount_dec_and_test(&permits->usage)) अणु
		spin_lock(&afs_permits_lock);
		hash_del_rcu(&permits->hash_node);
		spin_unlock(&afs_permits_lock);
		call_rcu(&permits->rcu, afs_permits_rcu);
	पूर्ण
पूर्ण

/*
 * Clear a permit cache on callback अवरोध.
 */
व्योम afs_clear_permits(काष्ठा afs_vnode *vnode)
अणु
	काष्ठा afs_permits *permits;

	spin_lock(&vnode->lock);
	permits = rcu_dereference_रक्षित(vnode->permit_cache,
					    lockdep_is_held(&vnode->lock));
	RCU_INIT_POINTER(vnode->permit_cache, शून्य);
	spin_unlock(&vnode->lock);

	afs_put_permits(permits);
पूर्ण

/*
 * Hash a list of permits.  Use simple addition to make it easy to add an extra
 * one at an as-yet indeterminate position in the list.
 */
अटल व्योम afs_hash_permits(काष्ठा afs_permits *permits)
अणु
	अचिन्हित दीर्घ h = permits->nr_permits;
	पूर्णांक i;

	क्रम (i = 0; i < permits->nr_permits; i++) अणु
		h += (अचिन्हित दीर्घ)permits->permits[i].key / माप(व्योम *);
		h += permits->permits[i].access;
	पूर्ण

	permits->h = h;
पूर्ण

/*
 * Cache the CallerAccess result obtained from करोing a fileserver operation
 * that वापसed a vnode status क्रम a particular key.  If a callback अवरोध
 * occurs whilst the operation was in progress then we have to ditch the cache
 * as the ACL *may* have changed.
 */
व्योम afs_cache_permit(काष्ठा afs_vnode *vnode, काष्ठा key *key,
		      अचिन्हित पूर्णांक cb_अवरोध, काष्ठा afs_status_cb *scb)
अणु
	काष्ठा afs_permits *permits, *xpermits, *replacement, *zap, *new = शून्य;
	afs_access_t caller_access = scb->status.caller_access;
	माप_प्रकार size = 0;
	bool changed = false;
	पूर्णांक i, j;

	_enter("{%llx:%llu},%x,%x",
	       vnode->fid.vid, vnode->fid.vnode, key_serial(key), caller_access);

	rcu_पढ़ो_lock();

	/* Check क्रम the common हाल first: We got back the same access as last
	 * समय we tried and alपढ़ोy have it recorded.
	 */
	permits = rcu_dereference(vnode->permit_cache);
	अगर (permits) अणु
		अगर (!permits->invalidated) अणु
			क्रम (i = 0; i < permits->nr_permits; i++) अणु
				अगर (permits->permits[i].key < key)
					जारी;
				अगर (permits->permits[i].key > key)
					अवरोध;
				अगर (permits->permits[i].access != caller_access) अणु
					changed = true;
					अवरोध;
				पूर्ण

				अगर (afs_cb_is_broken(cb_अवरोध, vnode)) अणु
					changed = true;
					अवरोध;
				पूर्ण

				/* The cache is still good. */
				rcu_पढ़ो_unlock();
				वापस;
			पूर्ण
		पूर्ण

		changed |= permits->invalidated;
		size = permits->nr_permits;

		/* If this set of permits is now wrong, clear the permits
		 * poपूर्णांकer so that no one tries to use the stale inक्रमmation.
		 */
		अगर (changed) अणु
			spin_lock(&vnode->lock);
			अगर (permits != rcu_access_poपूर्णांकer(vnode->permit_cache))
				जाओ someone_अन्यथा_changed_it_unlock;
			RCU_INIT_POINTER(vnode->permit_cache, शून्य);
			spin_unlock(&vnode->lock);

			afs_put_permits(permits);
			permits = शून्य;
			size = 0;
		पूर्ण
	पूर्ण

	अगर (afs_cb_is_broken(cb_अवरोध, vnode))
		जाओ someone_अन्यथा_changed_it;

	/* We need a ref on any permits list we want to copy as we'll have to
	 * drop the lock to करो memory allocation.
	 */
	अगर (permits && !refcount_inc_not_zero(&permits->usage))
		जाओ someone_अन्यथा_changed_it;

	rcu_पढ़ो_unlock();

	/* Speculatively create a new list with the revised permission set.  We
	 * discard this अगर we find an extant match alपढ़ोy in the hash, but
	 * it's easier to compare with स_भेद this way.
	 *
	 * We fill in the key poपूर्णांकers at this समय, but we करोn't get the refs
	 * yet.
	 */
	size++;
	new = kzalloc(माप(काष्ठा afs_permits) +
		      माप(काष्ठा afs_permit) * size, GFP_NOFS);
	अगर (!new)
		जाओ out_put;

	refcount_set(&new->usage, 1);
	new->nr_permits = size;
	i = j = 0;
	अगर (permits) अणु
		क्रम (i = 0; i < permits->nr_permits; i++) अणु
			अगर (j == i && permits->permits[i].key > key) अणु
				new->permits[j].key = key;
				new->permits[j].access = caller_access;
				j++;
			पूर्ण
			new->permits[j].key = permits->permits[i].key;
			new->permits[j].access = permits->permits[i].access;
			j++;
		पूर्ण
	पूर्ण

	अगर (j == i) अणु
		new->permits[j].key = key;
		new->permits[j].access = caller_access;
	पूर्ण

	afs_hash_permits(new);

	/* Now see अगर the permit list we want is actually alपढ़ोy available */
	spin_lock(&afs_permits_lock);

	hash_क्रम_each_possible(afs_permits_cache, xpermits, hash_node, new->h) अणु
		अगर (xpermits->h != new->h ||
		    xpermits->invalidated ||
		    xpermits->nr_permits != new->nr_permits ||
		    स_भेद(xpermits->permits, new->permits,
			   new->nr_permits * माप(काष्ठा afs_permit)) != 0)
			जारी;

		अगर (refcount_inc_not_zero(&xpermits->usage)) अणु
			replacement = xpermits;
			जाओ found;
		पूर्ण

		अवरोध;
	पूर्ण

	क्रम (i = 0; i < new->nr_permits; i++)
		key_get(new->permits[i].key);
	hash_add_rcu(afs_permits_cache, &new->hash_node, new->h);
	replacement = new;
	new = शून्य;

found:
	spin_unlock(&afs_permits_lock);

	kमुक्त(new);

	rcu_पढ़ो_lock();
	spin_lock(&vnode->lock);
	zap = rcu_access_poपूर्णांकer(vnode->permit_cache);
	अगर (!afs_cb_is_broken(cb_अवरोध, vnode) && zap == permits)
		rcu_assign_poपूर्णांकer(vnode->permit_cache, replacement);
	अन्यथा
		zap = replacement;
	spin_unlock(&vnode->lock);
	rcu_पढ़ो_unlock();
	afs_put_permits(zap);
out_put:
	afs_put_permits(permits);
	वापस;

someone_अन्यथा_changed_it_unlock:
	spin_unlock(&vnode->lock);
someone_अन्यथा_changed_it:
	/* Someone अन्यथा changed the cache under us - करोn't recheck at this
	 * समय.
	 */
	rcu_पढ़ो_unlock();
	वापस;
पूर्ण

अटल bool afs_check_permit_rcu(काष्ठा afs_vnode *vnode, काष्ठा key *key,
				 afs_access_t *_access)
अणु
	स्थिर काष्ठा afs_permits *permits;
	पूर्णांक i;

	_enter("{%llx:%llu},%x",
	       vnode->fid.vid, vnode->fid.vnode, key_serial(key));

	/* check the permits to see अगर we've got one yet */
	अगर (key == vnode->volume->cell->anonymous_key) अणु
		*_access = vnode->status.anon_access;
		_leave(" = t [anon %x]", *_access);
		वापस true;
	पूर्ण

	permits = rcu_dereference(vnode->permit_cache);
	अगर (permits) अणु
		क्रम (i = 0; i < permits->nr_permits; i++) अणु
			अगर (permits->permits[i].key < key)
				जारी;
			अगर (permits->permits[i].key > key)
				अवरोध;

			*_access = permits->permits[i].access;
			_leave(" = %u [perm %x]", !permits->invalidated, *_access);
			वापस !permits->invalidated;
		पूर्ण
	पूर्ण

	_leave(" = f");
	वापस false;
पूर्ण

/*
 * check with the fileserver to see अगर the directory or parent directory is
 * permitted to be accessed with this authorisation, and अगर so, what access it
 * is granted
 */
पूर्णांक afs_check_permit(काष्ठा afs_vnode *vnode, काष्ठा key *key,
		     afs_access_t *_access)
अणु
	काष्ठा afs_permits *permits;
	bool valid = false;
	पूर्णांक i, ret;

	_enter("{%llx:%llu},%x",
	       vnode->fid.vid, vnode->fid.vnode, key_serial(key));

	/* check the permits to see अगर we've got one yet */
	अगर (key == vnode->volume->cell->anonymous_key) अणु
		_debug("anon");
		*_access = vnode->status.anon_access;
		valid = true;
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		permits = rcu_dereference(vnode->permit_cache);
		अगर (permits) अणु
			क्रम (i = 0; i < permits->nr_permits; i++) अणु
				अगर (permits->permits[i].key < key)
					जारी;
				अगर (permits->permits[i].key > key)
					अवरोध;

				*_access = permits->permits[i].access;
				valid = !permits->invalidated;
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (!valid) अणु
		/* Check the status on the file we're actually पूर्णांकerested in
		 * (the post-processing will cache the result).
		 */
		_debug("no valid permit");

		ret = afs_fetch_status(vnode, key, false, _access);
		अगर (ret < 0) अणु
			*_access = 0;
			_leave(" = %d", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	_leave(" = 0 [access %x]", *_access);
	वापस 0;
पूर्ण

/*
 * check the permissions on an AFS file
 * - AFS ACLs are attached to directories only, and a file is controlled by its
 *   parent directory's ACL
 */
पूर्णांक afs_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		   पूर्णांक mask)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	afs_access_t access;
	काष्ठा key *key;
	पूर्णांक ret = 0;

	_enter("{{%llx:%llu},%lx},%x,",
	       vnode->fid.vid, vnode->fid.vnode, vnode->flags, mask);

	अगर (mask & MAY_NOT_BLOCK) अणु
		key = afs_request_key_rcu(vnode->volume->cell);
		अगर (IS_ERR(key))
			वापस -ECHILD;

		ret = -ECHILD;
		अगर (!afs_check_validity(vnode) ||
		    !afs_check_permit_rcu(vnode, key, &access))
			जाओ error;
	पूर्ण अन्यथा अणु
		key = afs_request_key(vnode->volume->cell);
		अगर (IS_ERR(key)) अणु
			_leave(" = %ld [key]", PTR_ERR(key));
			वापस PTR_ERR(key);
		पूर्ण

		ret = afs_validate(vnode, key);
		अगर (ret < 0)
			जाओ error;

		/* check the permits to see अगर we've got one yet */
		ret = afs_check_permit(vnode, key, &access);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	/* पूर्णांकerpret the access mask */
	_debug("REQ %x ACC %x on %s",
	       mask, access, S_ISसूची(inode->i_mode) ? "dir" : "file");

	ret = 0;
	अगर (S_ISसूची(inode->i_mode)) अणु
		अगर (mask & (MAY_EXEC | MAY_READ | MAY_CHसूची)) अणु
			अगर (!(access & AFS_ACE_LOOKUP))
				जाओ permission_denied;
		पूर्ण
		अगर (mask & MAY_WRITE) अणु
			अगर (!(access & (AFS_ACE_DELETE | /* सूची_हटाओ, unlink, नाम from */
					AFS_ACE_INSERT))) /* create, सूची_गढ़ो, symlink, नाम to */
				जाओ permission_denied;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(access & AFS_ACE_LOOKUP))
			जाओ permission_denied;
		अगर ((mask & MAY_EXEC) && !(inode->i_mode & S_IXUSR))
			जाओ permission_denied;
		अगर (mask & (MAY_EXEC | MAY_READ)) अणु
			अगर (!(access & AFS_ACE_READ))
				जाओ permission_denied;
			अगर (!(inode->i_mode & S_IRUSR))
				जाओ permission_denied;
		पूर्ण अन्यथा अगर (mask & MAY_WRITE) अणु
			अगर (!(access & AFS_ACE_WRITE))
				जाओ permission_denied;
			अगर (!(inode->i_mode & S_IWUSR))
				जाओ permission_denied;
		पूर्ण
	पूर्ण

	key_put(key);
	_leave(" = %d", ret);
	वापस ret;

permission_denied:
	ret = -EACCES;
error:
	key_put(key);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

व्योम __निकास afs_clean_up_permit_cache(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HASH_SIZE(afs_permits_cache); i++)
		WARN_ON_ONCE(!hlist_empty(&afs_permits_cache[i]));

पूर्ण
