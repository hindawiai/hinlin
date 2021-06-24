<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Key garbage collector
 *
 * Copyright (C) 2009-2011 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <keys/keyring-type.h>
#समावेश "internal.h"

/*
 * Delay between key revocation/expiry in seconds
 */
अचिन्हित key_gc_delay = 5 * 60;

/*
 * Reaper क्रम unused keys.
 */
अटल व्योम key_garbage_collector(काष्ठा work_काष्ठा *work);
DECLARE_WORK(key_gc_work, key_garbage_collector);

/*
 * Reaper क्रम links from keyrings to dead keys.
 */
अटल व्योम key_gc_समयr_func(काष्ठा समयr_list *);
अटल DEFINE_TIMER(key_gc_समयr, key_gc_समयr_func);

अटल समय64_t key_gc_next_run = TIME64_MAX;
अटल काष्ठा key_type *key_gc_dead_keytype;

अटल अचिन्हित दीर्घ key_gc_flags;
#घोषणा KEY_GC_KEY_EXPIRED	0	/* A key expired and needs unlinking */
#घोषणा KEY_GC_REAP_KEYTYPE	1	/* A keytype is being unरेजिस्टरed */
#घोषणा KEY_GC_REAPING_KEYTYPE	2	/* Cleared when keytype reaped */


/*
 * Any key whose type माला_लो unरेजिस्टरed will be re-typed to this अगर it can't be
 * immediately unlinked.
 */
काष्ठा key_type key_type_dead = अणु
	.name = ".dead",
पूर्ण;

/*
 * Schedule a garbage collection run.
 * - समय precision isn't particularly important
 */
व्योम key_schedule_gc(समय64_t gc_at)
अणु
	अचिन्हित दीर्घ expires;
	समय64_t now = kसमय_get_real_seconds();

	kenter("%lld", gc_at - now);

	अगर (gc_at <= now || test_bit(KEY_GC_REAP_KEYTYPE, &key_gc_flags)) अणु
		kdebug("IMMEDIATE");
		schedule_work(&key_gc_work);
	पूर्ण अन्यथा अगर (gc_at < key_gc_next_run) अणु
		kdebug("DEFERRED");
		key_gc_next_run = gc_at;
		expires = jअगरfies + (gc_at - now) * HZ;
		mod_समयr(&key_gc_समयr, expires);
	पूर्ण
पूर्ण

/*
 * Schedule a dead links collection run.
 */
व्योम key_schedule_gc_links(व्योम)
अणु
	set_bit(KEY_GC_KEY_EXPIRED, &key_gc_flags);
	schedule_work(&key_gc_work);
पूर्ण

/*
 * Some key's cleanup समय was met after it expired, so we need to get the
 * reaper to go through a cycle finding expired keys.
 */
अटल व्योम key_gc_समयr_func(काष्ठा समयr_list *unused)
अणु
	kenter("");
	key_gc_next_run = TIME64_MAX;
	key_schedule_gc_links();
पूर्ण

/*
 * Reap keys of dead type.
 *
 * We use three flags to make sure we see three complete cycles of the garbage
 * collector: the first to mark keys of that type as being dead, the second to
 * collect dead links and the third to clean up the dead keys.  We have to be
 * careful as there may alपढ़ोy be a cycle in progress.
 *
 * The caller must be holding key_types_sem.
 */
व्योम key_gc_keytype(काष्ठा key_type *ktype)
अणु
	kenter("%s", ktype->name);

	key_gc_dead_keytype = ktype;
	set_bit(KEY_GC_REAPING_KEYTYPE, &key_gc_flags);
	smp_mb();
	set_bit(KEY_GC_REAP_KEYTYPE, &key_gc_flags);

	kdebug("schedule");
	schedule_work(&key_gc_work);

	kdebug("sleep");
	रुको_on_bit(&key_gc_flags, KEY_GC_REAPING_KEYTYPE,
		    TASK_UNINTERRUPTIBLE);

	key_gc_dead_keytype = शून्य;
	kleave("");
पूर्ण

/*
 * Garbage collect a list of unreferenced, detached keys
 */
अटल noअंतरभूत व्योम key_gc_unused_keys(काष्ठा list_head *keys)
अणु
	जबतक (!list_empty(keys)) अणु
		काष्ठा key *key =
			list_entry(keys->next, काष्ठा key, graveyard_link);
		लघु state = key->state;

		list_del(&key->graveyard_link);

		kdebug("- %u", key->serial);
		key_check(key);

#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
		हटाओ_watch_list(key->watchers, key->serial);
		key->watchers = शून्य;
#पूर्ण_अगर

		/* Throw away the key data अगर the key is instantiated */
		अगर (state == KEY_IS_POSITIVE && key->type->destroy)
			key->type->destroy(key);

		security_key_मुक्त(key);

		/* deal with the user's key tracking and quota */
		अगर (test_bit(KEY_FLAG_IN_QUOTA, &key->flags)) अणु
			spin_lock(&key->user->lock);
			key->user->qnkeys--;
			key->user->qnbytes -= key->quotalen;
			spin_unlock(&key->user->lock);
		पूर्ण

		atomic_dec(&key->user->nkeys);
		अगर (state != KEY_IS_UNINSTANTIATED)
			atomic_dec(&key->user->nikeys);

		key_user_put(key->user);
		key_put_tag(key->करोमुख्य_tag);
		kमुक्त(key->description);

		memzero_explicit(key, माप(*key));
		kmem_cache_मुक्त(key_jar, key);
	पूर्ण
पूर्ण

/*
 * Garbage collector क्रम unused keys.
 *
 * This is करोne in process context so that we करोn't have to disable पूर्णांकerrupts
 * all over the place.  key_put() schedules this rather than trying to करो the
 * cleanup itself, which means key_put() करोesn't have to sleep.
 */
अटल व्योम key_garbage_collector(काष्ठा work_काष्ठा *work)
अणु
	अटल LIST_HEAD(graveyard);
	अटल u8 gc_state;		/* Internal persistent state */
#घोषणा KEY_GC_REAP_AGAIN	0x01	/* - Need another cycle */
#घोषणा KEY_GC_REAPING_LINKS	0x02	/* - We need to reap links */
#घोषणा KEY_GC_SET_TIMER	0x04	/* - We need to restart the समयr */
#घोषणा KEY_GC_REAPING_DEAD_1	0x10	/* - We need to mark dead keys */
#घोषणा KEY_GC_REAPING_DEAD_2	0x20	/* - We need to reap dead key links */
#घोषणा KEY_GC_REAPING_DEAD_3	0x40	/* - We need to reap dead keys */
#घोषणा KEY_GC_FOUND_DEAD_KEY	0x80	/* - We found at least one dead key */

	काष्ठा rb_node *cursor;
	काष्ठा key *key;
	समय64_t new_समयr, limit;

	kenter("[%lx,%x]", key_gc_flags, gc_state);

	limit = kसमय_get_real_seconds();
	अगर (limit > key_gc_delay)
		limit -= key_gc_delay;
	अन्यथा
		limit = key_gc_delay;

	/* Work out what we're going to be करोing in this pass */
	gc_state &= KEY_GC_REAPING_DEAD_1 | KEY_GC_REAPING_DEAD_2;
	gc_state <<= 1;
	अगर (test_and_clear_bit(KEY_GC_KEY_EXPIRED, &key_gc_flags))
		gc_state |= KEY_GC_REAPING_LINKS | KEY_GC_SET_TIMER;

	अगर (test_and_clear_bit(KEY_GC_REAP_KEYTYPE, &key_gc_flags))
		gc_state |= KEY_GC_REAPING_DEAD_1;
	kdebug("new pass %x", gc_state);

	new_समयr = TIME64_MAX;

	/* As only this function is permitted to हटाओ things from the key
	 * serial tree, अगर cursor is non-शून्य then it will always poपूर्णांक to a
	 * valid node in the tree - even अगर lock got dropped.
	 */
	spin_lock(&key_serial_lock);
	cursor = rb_first(&key_serial_tree);

जारी_scanning:
	जबतक (cursor) अणु
		key = rb_entry(cursor, काष्ठा key, serial_node);
		cursor = rb_next(cursor);

		अगर (refcount_पढ़ो(&key->usage) == 0)
			जाओ found_unreferenced_key;

		अगर (unlikely(gc_state & KEY_GC_REAPING_DEAD_1)) अणु
			अगर (key->type == key_gc_dead_keytype) अणु
				gc_state |= KEY_GC_FOUND_DEAD_KEY;
				set_bit(KEY_FLAG_DEAD, &key->flags);
				key->perm = 0;
				जाओ skip_dead_key;
			पूर्ण अन्यथा अगर (key->type == &key_type_keyring &&
				   key->restrict_link) अणु
				जाओ found_restricted_keyring;
			पूर्ण
		पूर्ण

		अगर (gc_state & KEY_GC_SET_TIMER) अणु
			अगर (key->expiry > limit && key->expiry < new_समयr) अणु
				kdebug("will expire %x in %lld",
				       key_serial(key), key->expiry - limit);
				new_समयr = key->expiry;
			पूर्ण
		पूर्ण

		अगर (unlikely(gc_state & KEY_GC_REAPING_DEAD_2))
			अगर (key->type == key_gc_dead_keytype)
				gc_state |= KEY_GC_FOUND_DEAD_KEY;

		अगर ((gc_state & KEY_GC_REAPING_LINKS) ||
		    unlikely(gc_state & KEY_GC_REAPING_DEAD_2)) अणु
			अगर (key->type == &key_type_keyring)
				जाओ found_keyring;
		पूर्ण

		अगर (unlikely(gc_state & KEY_GC_REAPING_DEAD_3))
			अगर (key->type == key_gc_dead_keytype)
				जाओ destroy_dead_key;

	skip_dead_key:
		अगर (spin_is_contended(&key_serial_lock) || need_resched())
			जाओ contended;
	पूर्ण

contended:
	spin_unlock(&key_serial_lock);

maybe_resched:
	अगर (cursor) अणु
		cond_resched();
		spin_lock(&key_serial_lock);
		जाओ जारी_scanning;
	पूर्ण

	/* We've completed the pass.  Set the समयr अगर we need to and queue a
	 * new cycle अगर necessary.  We keep executing cycles until we find one
	 * where we didn't reap any keys.
	 */
	kdebug("pass complete");

	अगर (gc_state & KEY_GC_SET_TIMER && new_समयr != (समय64_t)TIME64_MAX) अणु
		new_समयr += key_gc_delay;
		key_schedule_gc(new_समयr);
	पूर्ण

	अगर (unlikely(gc_state & KEY_GC_REAPING_DEAD_2) ||
	    !list_empty(&graveyard)) अणु
		/* Make sure that all pending keyring payload deकाष्ठाions are
		 * fulfilled and that people aren't now looking at dead or
		 * dying keys that they करोn't have a reference upon or a link
		 * to.
		 */
		kdebug("gc sync");
		synchronize_rcu();
	पूर्ण

	अगर (!list_empty(&graveyard)) अणु
		kdebug("gc keys");
		key_gc_unused_keys(&graveyard);
	पूर्ण

	अगर (unlikely(gc_state & (KEY_GC_REAPING_DEAD_1 |
				 KEY_GC_REAPING_DEAD_2))) अणु
		अगर (!(gc_state & KEY_GC_FOUND_DEAD_KEY)) अणु
			/* No reमुख्यing dead keys: लघु circuit the reमुख्यing
			 * keytype reap cycles.
			 */
			kdebug("dead short");
			gc_state &= ~(KEY_GC_REAPING_DEAD_1 | KEY_GC_REAPING_DEAD_2);
			gc_state |= KEY_GC_REAPING_DEAD_3;
		पूर्ण अन्यथा अणु
			gc_state |= KEY_GC_REAP_AGAIN;
		पूर्ण
	पूर्ण

	अगर (unlikely(gc_state & KEY_GC_REAPING_DEAD_3)) अणु
		kdebug("dead wake");
		smp_mb();
		clear_bit(KEY_GC_REAPING_KEYTYPE, &key_gc_flags);
		wake_up_bit(&key_gc_flags, KEY_GC_REAPING_KEYTYPE);
	पूर्ण

	अगर (gc_state & KEY_GC_REAP_AGAIN)
		schedule_work(&key_gc_work);
	kleave(" [end %x]", gc_state);
	वापस;

	/* We found an unreferenced key - once we've हटाओd it from the tree,
	 * we can safely drop the lock.
	 */
found_unreferenced_key:
	kdebug("unrefd key %d", key->serial);
	rb_erase(&key->serial_node, &key_serial_tree);
	spin_unlock(&key_serial_lock);

	list_add_tail(&key->graveyard_link, &graveyard);
	gc_state |= KEY_GC_REAP_AGAIN;
	जाओ maybe_resched;

	/* We found a restricted keyring and need to update the restriction अगर
	 * it is associated with the dead key type.
	 */
found_restricted_keyring:
	spin_unlock(&key_serial_lock);
	keyring_restriction_gc(key, key_gc_dead_keytype);
	जाओ maybe_resched;

	/* We found a keyring and we need to check the payload क्रम links to
	 * dead or expired keys.  We करोn't flag another reap immediately as we
	 * have to रुको क्रम the old payload to be destroyed by RCU beक्रमe we
	 * can reap the keys to which it refers.
	 */
found_keyring:
	spin_unlock(&key_serial_lock);
	keyring_gc(key, limit);
	जाओ maybe_resched;

	/* We found a dead key that is still referenced.  Reset its type and
	 * destroy its payload with its semaphore held.
	 */
destroy_dead_key:
	spin_unlock(&key_serial_lock);
	kdebug("destroy key %d", key->serial);
	करोwn_ग_लिखो(&key->sem);
	key->type = &key_type_dead;
	अगर (key_gc_dead_keytype->destroy)
		key_gc_dead_keytype->destroy(key);
	स_रखो(&key->payload, KEY_DESTROY, माप(key->payload));
	up_ग_लिखो(&key->sem);
	जाओ maybe_resched;
पूर्ण
