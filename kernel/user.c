<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The "user cache".
 *
 * (C) Copyright 1991-2000 Linus Torvalds
 *
 * We have a per-user काष्ठाure to keep track of how many
 * processes, files etc the user has claimed, in order to be
 * able to have per-user limits क्रम प्रणाली resources. 
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/key.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/proc_ns.h>

/*
 * userns count is 1 क्रम root user, 1 क्रम init_uts_ns,
 * and 1 क्रम... ?
 */
काष्ठा user_namespace init_user_ns = अणु
	.uid_map = अणु
		.nr_extents = 1,
		अणु
			.extent[0] = अणु
				.first = 0,
				.lower_first = 0,
				.count = 4294967295U,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.gid_map = अणु
		.nr_extents = 1,
		अणु
			.extent[0] = अणु
				.first = 0,
				.lower_first = 0,
				.count = 4294967295U,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.projid_map = अणु
		.nr_extents = 1,
		अणु
			.extent[0] = अणु
				.first = 0,
				.lower_first = 0,
				.count = 4294967295U,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.ns.count = REFCOUNT_INIT(3),
	.owner = GLOBAL_ROOT_UID,
	.group = GLOBAL_ROOT_GID,
	.ns.inum = PROC_USER_INIT_INO,
#अगर_घोषित CONFIG_USER_NS
	.ns.ops = &userns_operations,
#पूर्ण_अगर
	.flags = USERNS_INIT_FLAGS,
#अगर_घोषित CONFIG_KEYS
	.keyring_name_list = LIST_HEAD_INIT(init_user_ns.keyring_name_list),
	.keyring_sem = __RWSEM_INITIALIZER(init_user_ns.keyring_sem),
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL_GPL(init_user_ns);

/*
 * UID task count cache, to get fast user lookup in "alloc_uid"
 * when changing user ID's (ie setuid() and मित्रs).
 */

#घोषणा UIDHASH_BITS	(CONFIG_BASE_SMALL ? 3 : 7)
#घोषणा UIDHASH_SZ	(1 << UIDHASH_BITS)
#घोषणा UIDHASH_MASK		(UIDHASH_SZ - 1)
#घोषणा __uidhashfn(uid)	(((uid >> UIDHASH_BITS) + uid) & UIDHASH_MASK)
#घोषणा uidhashentry(uid)	(uidhash_table + __uidhashfn((__kuid_val(uid))))

अटल काष्ठा kmem_cache *uid_cachep;
अटल काष्ठा hlist_head uidhash_table[UIDHASH_SZ];

/*
 * The uidhash_lock is mostly taken from process context, but it is
 * occasionally also taken from softirq/tasklet context, when
 * task-काष्ठाs get RCU-मुक्तd. Hence all locking must be softirq-safe.
 * But मुक्त_uid() is also called with local पूर्णांकerrupts disabled, and running
 * local_bh_enable() with local पूर्णांकerrupts disabled is an error - we'll run
 * softirq callbacks, and they can unconditionally enable पूर्णांकerrupts, and
 * the caller of मुक्त_uid() didn't expect that..
 */
अटल DEFINE_SPINLOCK(uidhash_lock);

/* root_user.__count is 1, क्रम init task cred */
काष्ठा user_काष्ठा root_user = अणु
	.__count	= REFCOUNT_INIT(1),
	.processes	= ATOMIC_INIT(1),
	.संक_बाकी	= ATOMIC_INIT(0),
	.locked_shm     = 0,
	.uid		= GLOBAL_ROOT_UID,
	.ratelimit	= RATELIMIT_STATE_INIT(root_user.ratelimit, 0, 0),
पूर्ण;

/*
 * These routines must be called with the uidhash spinlock held!
 */
अटल व्योम uid_hash_insert(काष्ठा user_काष्ठा *up, काष्ठा hlist_head *hashent)
अणु
	hlist_add_head(&up->uidhash_node, hashent);
पूर्ण

अटल व्योम uid_hash_हटाओ(काष्ठा user_काष्ठा *up)
अणु
	hlist_del_init(&up->uidhash_node);
पूर्ण

अटल काष्ठा user_काष्ठा *uid_hash_find(kuid_t uid, काष्ठा hlist_head *hashent)
अणु
	काष्ठा user_काष्ठा *user;

	hlist_क्रम_each_entry(user, hashent, uidhash_node) अणु
		अगर (uid_eq(user->uid, uid)) अणु
			refcount_inc(&user->__count);
			वापस user;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* IRQs are disabled and uidhash_lock is held upon function entry.
 * IRQ state (as stored in flags) is restored and uidhash_lock released
 * upon function निकास.
 */
अटल व्योम मुक्त_user(काष्ठा user_काष्ठा *up, अचिन्हित दीर्घ flags)
	__releases(&uidhash_lock)
अणु
	uid_hash_हटाओ(up);
	spin_unlock_irqrestore(&uidhash_lock, flags);
	kmem_cache_मुक्त(uid_cachep, up);
पूर्ण

/*
 * Locate the user_काष्ठा क्रम the passed UID.  If found, take a ref on it.  The
 * caller must unकरो that ref with मुक्त_uid().
 *
 * If the user_काष्ठा could not be found, वापस शून्य.
 */
काष्ठा user_काष्ठा *find_user(kuid_t uid)
अणु
	काष्ठा user_काष्ठा *ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uidhash_lock, flags);
	ret = uid_hash_find(uid, uidhashentry(uid));
	spin_unlock_irqrestore(&uidhash_lock, flags);
	वापस ret;
पूर्ण

व्योम मुक्त_uid(काष्ठा user_काष्ठा *up)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!up)
		वापस;

	अगर (refcount_dec_and_lock_irqsave(&up->__count, &uidhash_lock, &flags))
		मुक्त_user(up, flags);
पूर्ण

काष्ठा user_काष्ठा *alloc_uid(kuid_t uid)
अणु
	काष्ठा hlist_head *hashent = uidhashentry(uid);
	काष्ठा user_काष्ठा *up, *new;

	spin_lock_irq(&uidhash_lock);
	up = uid_hash_find(uid, hashent);
	spin_unlock_irq(&uidhash_lock);

	अगर (!up) अणु
		new = kmem_cache_zalloc(uid_cachep, GFP_KERNEL);
		अगर (!new)
			वापस शून्य;

		new->uid = uid;
		refcount_set(&new->__count, 1);
		ratelimit_state_init(&new->ratelimit, HZ, 100);
		ratelimit_set_flags(&new->ratelimit, RATELIMIT_MSG_ON_RELEASE);

		/*
		 * Beक्रमe adding this, check whether we raced
		 * on adding the same user alपढ़ोy..
		 */
		spin_lock_irq(&uidhash_lock);
		up = uid_hash_find(uid, hashent);
		अगर (up) अणु
			kmem_cache_मुक्त(uid_cachep, new);
		पूर्ण अन्यथा अणु
			uid_hash_insert(new, hashent);
			up = new;
		पूर्ण
		spin_unlock_irq(&uidhash_lock);
	पूर्ण

	वापस up;
पूर्ण

अटल पूर्णांक __init uid_cache_init(व्योम)
अणु
	पूर्णांक n;

	uid_cachep = kmem_cache_create("uid_cache", माप(काष्ठा user_काष्ठा),
			0, SLAB_HWCACHE_ALIGN|SLAB_PANIC, शून्य);

	क्रम(n = 0; n < UIDHASH_SZ; ++n)
		INIT_HLIST_HEAD(uidhash_table + n);

	/* Insert the root user immediately (init alपढ़ोy runs as root) */
	spin_lock_irq(&uidhash_lock);
	uid_hash_insert(&root_user, uidhashentry(GLOBAL_ROOT_UID));
	spin_unlock_irq(&uidhash_lock);

	वापस 0;
पूर्ण
subsys_initcall(uid_cache_init);
