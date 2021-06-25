<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * kref.h - library routines क्रम handling generic reference counted objects
 *
 * Copyright (C) 2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2004 IBM Corp.
 *
 * based on kobject.h which was:
 * Copyright (C) 2002-2003 Patrick Mochel <mochel@osdl.org>
 * Copyright (C) 2002-2003 Open Source Development Lअसल
 */

#अगर_अघोषित _KREF_H_
#घोषणा _KREF_H_

#समावेश <linux/spinlock.h>
#समावेश <linux/refcount.h>

काष्ठा kref अणु
	refcount_t refcount;
पूर्ण;

#घोषणा KREF_INIT(n)	अणु .refcount = REFCOUNT_INIT(n), पूर्ण

/**
 * kref_init - initialize object.
 * @kref: object in question.
 */
अटल अंतरभूत व्योम kref_init(काष्ठा kref *kref)
अणु
	refcount_set(&kref->refcount, 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kref_पढ़ो(स्थिर काष्ठा kref *kref)
अणु
	वापस refcount_पढ़ो(&kref->refcount);
पूर्ण

/**
 * kref_get - increment refcount क्रम object.
 * @kref: object.
 */
अटल अंतरभूत व्योम kref_get(काष्ठा kref *kref)
अणु
	refcount_inc(&kref->refcount);
पूर्ण

/**
 * kref_put - decrement refcount क्रम object.
 * @kref: object.
 * @release: poपूर्णांकer to the function that will clean up the object when the
 *	     last reference to the object is released.
 *	     This poपूर्णांकer is required, and it is not acceptable to pass kमुक्त
 *	     in as this function.
 *
 * Decrement the refcount, and अगर 0, call release().
 * Return 1 अगर the object was हटाओd, otherwise वापस 0.  Beware, अगर this
 * function वापसs 0, you still can not count on the kref from reमुख्यing in
 * memory.  Only use the वापस value अगर you want to see अगर the kref is now
 * gone, not present.
 */
अटल अंतरभूत पूर्णांक kref_put(काष्ठा kref *kref, व्योम (*release)(काष्ठा kref *kref))
अणु
	अगर (refcount_dec_and_test(&kref->refcount)) अणु
		release(kref);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kref_put_mutex(काष्ठा kref *kref,
				 व्योम (*release)(काष्ठा kref *kref),
				 काष्ठा mutex *lock)
अणु
	अगर (refcount_dec_and_mutex_lock(&kref->refcount, lock)) अणु
		release(kref);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kref_put_lock(काष्ठा kref *kref,
				व्योम (*release)(काष्ठा kref *kref),
				spinlock_t *lock)
अणु
	अगर (refcount_dec_and_lock(&kref->refcount, lock)) अणु
		release(kref);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * kref_get_unless_zero - Increment refcount क्रम object unless it is zero.
 * @kref: object.
 *
 * Return non-zero अगर the increment succeeded. Otherwise वापस 0.
 *
 * This function is पूर्णांकended to simplअगरy locking around refcounting क्रम
 * objects that can be looked up from a lookup काष्ठाure, and which are
 * हटाओd from that lookup काष्ठाure in the object deकाष्ठाor.
 * Operations on such objects require at least a पढ़ो lock around
 * lookup + kref_get, and a ग_लिखो lock around kref_put + हटाओ from lookup
 * काष्ठाure. Furthermore, RCU implementations become extremely tricky.
 * With a lookup followed by a kref_get_unless_zero *with वापस value check*
 * locking in the kref_put path can be deferred to the actual removal from
 * the lookup काष्ठाure and RCU lookups become trivial.
 */
अटल अंतरभूत पूर्णांक __must_check kref_get_unless_zero(काष्ठा kref *kref)
अणु
	वापस refcount_inc_not_zero(&kref->refcount);
पूर्ण
#पूर्ण_अगर /* _KREF_H_ */
