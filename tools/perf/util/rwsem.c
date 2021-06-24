<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util.h"
#समावेश "rwsem.h"

पूर्णांक init_rwsem(काष्ठा rw_semaphore *sem)
अणु
	वापस pthपढ़ो_rwlock_init(&sem->lock, शून्य);
पूर्ण

पूर्णांक निकास_rwsem(काष्ठा rw_semaphore *sem)
अणु
	वापस pthपढ़ो_rwlock_destroy(&sem->lock);
पूर्ण

पूर्णांक करोwn_पढ़ो(काष्ठा rw_semaphore *sem)
अणु
	वापस perf_singlethपढ़ोed ? 0 : pthपढ़ो_rwlock_rdlock(&sem->lock);
पूर्ण

पूर्णांक up_पढ़ो(काष्ठा rw_semaphore *sem)
अणु
	वापस perf_singlethपढ़ोed ? 0 : pthपढ़ो_rwlock_unlock(&sem->lock);
पूर्ण

पूर्णांक करोwn_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	वापस perf_singlethपढ़ोed ? 0 : pthपढ़ो_rwlock_wrlock(&sem->lock);
पूर्ण

पूर्णांक up_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	वापस perf_singlethपढ़ोed ? 0 : pthपढ़ो_rwlock_unlock(&sem->lock);
पूर्ण
