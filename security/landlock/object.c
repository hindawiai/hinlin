<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Landlock LSM - Object management
 *
 * Copyright तऊ 2016-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#समावेश <linux/bug.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "object.h"

काष्ठा landlock_object *landlock_create_object(
		स्थिर काष्ठा landlock_object_underops *स्थिर underops,
		व्योम *स्थिर underobj)
अणु
	काष्ठा landlock_object *new_object;

	अगर (WARN_ON_ONCE(!underops || !underobj))
		वापस ERR_PTR(-ENOENT);
	new_object = kzalloc(माप(*new_object), GFP_KERNEL_ACCOUNT);
	अगर (!new_object)
		वापस ERR_PTR(-ENOMEM);
	refcount_set(&new_object->usage, 1);
	spin_lock_init(&new_object->lock);
	new_object->underops = underops;
	new_object->underobj = underobj;
	वापस new_object;
पूर्ण

/*
 * The caller must own the object (i.e. thanks to object->usage) to safely put
 * it.
 */
व्योम landlock_put_object(काष्ठा landlock_object *स्थिर object)
अणु
	/*
	 * The call to @object->underops->release(object) might sleep, e.g.
	 * because of iput().
	 */
	might_sleep();
	अगर (!object)
		वापस;

	/*
	 * If the @object's refcount cannot drop to zero, we can just decrement
	 * the refcount without holding a lock. Otherwise, the decrement must
	 * happen under @object->lock क्रम synchronization with things like
	 * get_inode_object().
	 */
	अगर (refcount_dec_and_lock(&object->usage, &object->lock)) अणु
		__acquire(&object->lock);
		/*
		 * With @object->lock initially held, हटाओ the reference from
		 * @object->underobj to @object (अगर it still exists).
		 */
		object->underops->release(object);
		kमुक्त_rcu(object, rcu_मुक्त);
	पूर्ण
पूर्ण
