<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_MUTEX_H
#घोषणा _LIBLOCKDEP_MUTEX_H

#समावेश <pthपढ़ो.h>
#समावेश "common.h"

काष्ठा liblockdep_pthपढ़ो_mutex अणु
	pthपढ़ो_mutex_t mutex;
	काष्ठा lock_class_key key;
	काष्ठा lockdep_map dep_map;
पूर्ण;

प्रकार काष्ठा liblockdep_pthपढ़ो_mutex liblockdep_pthपढ़ो_mutex_t;

#घोषणा LIBLOCKDEP_PTHREAD_MUTEX_INITIALIZER(mtx)			\
		(स्थिर काष्ठा liblockdep_pthपढ़ो_mutex) अणु		\
	.mutex = PTHREAD_MUTEX_INITIALIZER,				\
	.dep_map = STATIC_LOCKDEP_MAP_INIT(#mtx, &((&(mtx))->dep_map)),	\
पूर्ण

अटल अंतरभूत पूर्णांक __mutex_init(liblockdep_pthपढ़ो_mutex_t *lock,
				स्थिर अक्षर *name,
				काष्ठा lock_class_key *key,
				स्थिर pthपढ़ो_mutexattr_t *__mutexattr)
अणु
	lockdep_init_map(&lock->dep_map, name, key, 0);
	वापस pthपढ़ो_mutex_init(&lock->mutex, __mutexattr);
पूर्ण

#घोषणा liblockdep_pthपढ़ो_mutex_init(mutex, mutexattr)			\
(अणु									\
	lockdep_रेजिस्टर_key(&(mutex)->key);				\
	__mutex_init((mutex), #mutex, &(mutex)->key, (mutexattr));	\
पूर्ण)

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_mutex_lock(liblockdep_pthपढ़ो_mutex_t *lock)
अणु
	lock_acquire(&lock->dep_map, 0, 0, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_mutex_lock(&lock->mutex);
पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_mutex_unlock(liblockdep_pthपढ़ो_mutex_t *lock)
अणु
	lock_release(&lock->dep_map, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_mutex_unlock(&lock->mutex);
पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_mutex_trylock(liblockdep_pthपढ़ो_mutex_t *lock)
अणु
	lock_acquire(&lock->dep_map, 0, 1, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	वापस pthपढ़ो_mutex_trylock(&lock->mutex) == 0 ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक liblockdep_pthपढ़ो_mutex_destroy(liblockdep_pthपढ़ो_mutex_t *lock)
अणु
	lockdep_reset_lock(&lock->dep_map);
	lockdep_unरेजिस्टर_key(&lock->key);
	वापस pthपढ़ो_mutex_destroy(&lock->mutex);
पूर्ण

#अगर_घोषित __USE_LIBLOCKDEP

#घोषणा pthपढ़ो_mutex_t         liblockdep_pthपढ़ो_mutex_t
#घोषणा pthपढ़ो_mutex_init      liblockdep_pthपढ़ो_mutex_init
#घोषणा pthपढ़ो_mutex_lock      liblockdep_pthपढ़ो_mutex_lock
#घोषणा pthपढ़ो_mutex_unlock    liblockdep_pthपढ़ो_mutex_unlock
#घोषणा pthपढ़ो_mutex_trylock   liblockdep_pthपढ़ो_mutex_trylock
#घोषणा pthपढ़ो_mutex_destroy   liblockdep_pthपढ़ो_mutex_destroy

#पूर्ण_अगर

#पूर्ण_अगर
