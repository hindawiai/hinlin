<शैली गुरु>
#अगर_अघोषित _PERF_RWSEM_H
#घोषणा _PERF_RWSEM_H

#समावेश <pthपढ़ो.h>

काष्ठा rw_semaphore अणु
	pthपढ़ो_rwlock_t lock;
पूर्ण;

पूर्णांक init_rwsem(काष्ठा rw_semaphore *sem);
पूर्णांक निकास_rwsem(काष्ठा rw_semaphore *sem);

पूर्णांक करोwn_पढ़ो(काष्ठा rw_semaphore *sem);
पूर्णांक up_पढ़ो(काष्ठा rw_semaphore *sem);

पूर्णांक करोwn_ग_लिखो(काष्ठा rw_semaphore *sem);
पूर्णांक up_ग_लिखो(काष्ठा rw_semaphore *sem);

#पूर्ण_अगर /* _PERF_RWSEM_H */
