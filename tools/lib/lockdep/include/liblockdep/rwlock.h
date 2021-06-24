<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_RWLOCK_H
#घोषणा _LIBLOCKDEP_RWLOCK_H

#समावेश <pthपढ़ो.h>
#समावेश "common.h"

काष्ठा liblockdep_pthपढ़ो_rwlock अणु
	pthपढ़ो_rwlock_t rwlock;
	काष्ठा lockdep_map dep_map;
पूर्ण;

प्रकार काष्ठा liblockdep_pthपढ़ो_rwlock liblockdep_pthपढ़ो_rwlock_t;

#घोषणा LIBLOCKDEP_PTHREAD_RWLOCK_INITIALIZER(rwl)			\
		(काष्ठा liblockdep_pthपढ़ो_rwlock) अणु			\
	.rwlock = PTHREAD_RWLOCK_INITIALIZER,				\
	.dep_map = STATIC_LOCKDEP_MAP_INIT(#rwl, &((&(rwl))->dep_map)),	\
पूर्ण

अटल अंतरभूत पूर्णांक __rwlock_init(liblockdep_pthपढ़ो_rwlock_t *lock,
				स्थिर अक्षर *name,
				काष्ठा lock_class_key *key,
				स्थिर pthपढ़ो_rwlockattr_t *attr)
अणु
	lockdep_init_map(&lock->dep_map, name, key, 0);

	वापस pthपढ़ो_rwlock_init(&lock->rwlock, attr);
पूर्ण

#घोषणा liblockdep_pthपढ़ो_rwlock_init(lock, attr)		\
(अणु							\
	अटल काष्ठा lock_class_key __key;		\
							\
	__rwlock_init((lock), #lock, &__key, (attr));	\
पूर्ण)

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_rwlock_rdlock(liblockdep_pthपढ़ो_rwlock_t *lock)
अणु
	lock_acquire(&lock->dep_map, 0, 0, 2, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_rwlock_rdlock(&lock->rwlock);

पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_rwlock_unlock(liblockdep_pthपढ़ो_rwlock_t *lock)
अणु
	lock_release(&lock->dep_map, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_rwlock_unlock(&lock->rwlock);
पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_rwlock_wrlock(liblockdep_pthपढ़ो_rwlock_t *lock)
अणु
	lock_acquire(&lock->dep_map, 0, 0, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_rwlock_wrlock(&lock->rwlock);
पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_rwlock_tryrdlock(liblockdep_pthपढ़ो_rwlock_t *lock)
अणु
	lock_acquire(&lock->dep_map, 0, 1, 2, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_rwlock_tryrdlock(&lock->rwlock) == 0 ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_rwlock_trywrlock(liblockdep_pthपढ़ो_rwlock_t *lock)
अणु
	lock_acquire(&lock->dep_map, 0, 1, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_rwlock_trywrlock(&lock->rwlock) == 0 ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_rwlock_destroy(liblockdep_pthपढ़ो_rwlock_t *lock)
अणु
	वापस pthपढ़ो_rwlock_destroy(&lock->rwlock);
पूर्ण

#अगर_घोषित __USE_LIBLOCKDEP

#घोषणा pthपढ़ो_rwlock_t		liblockdep_pthपढ़ो_rwlock_t
#घोषणा pthपढ़ो_rwlock_init		liblockdep_pthपढ़ो_rwlock_init
#घोषणा pthपढ़ो_rwlock_rdlock		liblockdep_pthपढ़ो_rwlock_rdlock
#घोषणा pthपढ़ो_rwlock_unlock		liblockdep_pthपढ़ो_rwlock_unlock
#घोषणा pthपढ़ो_rwlock_wrlock		liblockdep_pthपढ़ो_rwlock_wrlock
#घोषणा pthपढ़ो_rwlock_tryrdlock	liblockdep_pthपढ़ो_rwlock_tryrdlock
#घोषणा pthपढ़ो_rwlock_trywrlock	liblockdep_pthपढ़ो_rwlock_trywrlock
#घोषणा pthपढ़ो_rwlock_destroy		liblockdep_rwlock_destroy

#पूर्ण_अगर

#पूर्ण_अगर
