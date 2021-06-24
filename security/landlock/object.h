<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Landlock LSM - Object management
 *
 * Copyright तऊ 2016-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#अगर_अघोषित _SECURITY_LANDLOCK_OBJECT_H
#घोषणा _SECURITY_LANDLOCK_OBJECT_H

#समावेश <linux/compiler_types.h>
#समावेश <linux/refcount.h>
#समावेश <linux/spinlock.h>

काष्ठा landlock_object;

/**
 * काष्ठा landlock_object_underops - Operations on an underlying object
 */
काष्ठा landlock_object_underops अणु
	/**
	 * @release: Releases the underlying object (e.g. iput() क्रम an inode).
	 */
	व्योम (*release)(काष्ठा landlock_object *स्थिर object)
		__releases(object->lock);
पूर्ण;

/**
 * काष्ठा landlock_object - Security blob tied to a kernel object
 *
 * The goal of this काष्ठाure is to enable to tie a set of ephemeral access
 * rights (pertaining to dअगरferent करोमुख्यs) to a kernel object (e.g an inode)
 * in a safe way.  This implies to handle concurrent use and modअगरication.
 *
 * The lअगरeसमय of a &काष्ठा landlock_object depends on the rules referring to
 * it.
 */
काष्ठा landlock_object अणु
	/**
	 * @usage: This counter is used to tie an object to the rules matching
	 * it or to keep it alive जबतक adding a new rule.  If this counter
	 * reaches zero, this काष्ठा must not be modअगरied, but this counter can
	 * still be पढ़ो from within an RCU पढ़ो-side critical section.  When
	 * adding a new rule to an object with a usage counter of zero, we must
	 * रुको until the poपूर्णांकer to this object is set to शून्य (or recycled).
	 */
	refcount_t usage;
	/**
	 * @lock: Protects against concurrent modअगरications.  This lock must be
	 * held from the समय @usage drops to zero until any weak references
	 * from @underobj to this object have been cleaned up.
	 *
	 * Lock ordering: inode->i_lock nests inside this.
	 */
	spinlock_t lock;
	/**
	 * @underobj: Used when cleaning up an object and to mark an object as
	 * tied to its underlying kernel काष्ठाure.  This poपूर्णांकer is रक्षित
	 * by @lock.  Cf. landlock_release_inodes() and release_inode().
	 */
	व्योम *underobj;
	जोड़ अणु
		/**
		 * @rcu_मुक्त: Enables lockless use of @usage, @lock and
		 * @underobj from within an RCU पढ़ो-side critical section.
		 * @rcu_मुक्त and @underops are only used by
		 * landlock_put_object().
		 */
		काष्ठा rcu_head rcu_मुक्त;
		/**
		 * @underops: Enables landlock_put_object() to release the
		 * underlying object (e.g. inode).
		 */
		स्थिर काष्ठा landlock_object_underops *underops;
	पूर्ण;
पूर्ण;

काष्ठा landlock_object *landlock_create_object(
		स्थिर काष्ठा landlock_object_underops *स्थिर underops,
		व्योम *स्थिर underobj);

व्योम landlock_put_object(काष्ठा landlock_object *स्थिर object);

अटल अंतरभूत व्योम landlock_get_object(काष्ठा landlock_object *स्थिर object)
अणु
	अगर (object)
		refcount_inc(&object->usage);
पूर्ण

#पूर्ण_अगर /* _SECURITY_LANDLOCK_OBJECT_H */
