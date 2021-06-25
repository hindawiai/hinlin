<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_OSQ_LOCK_H
#घोषणा __LINUX_OSQ_LOCK_H

/*
 * An MCS like lock especially tailored क्रम optimistic spinning क्रम sleeping
 * lock implementations (mutex, rwsem, etc).
 */
काष्ठा optimistic_spin_node अणु
	काष्ठा optimistic_spin_node *next, *prev;
	पूर्णांक locked; /* 1 अगर lock acquired */
	पूर्णांक cpu; /* encoded CPU # + 1 value */
पूर्ण;

काष्ठा optimistic_spin_queue अणु
	/*
	 * Stores an encoded value of the CPU # of the tail node in the queue.
	 * If the queue is empty, then it's set to OSQ_UNLOCKED_VAL.
	 */
	atomic_t tail;
पूर्ण;

#घोषणा OSQ_UNLOCKED_VAL (0)

/* Init macro and function. */
#घोषणा OSQ_LOCK_UNLOCKED अणु ATOMIC_INIT(OSQ_UNLOCKED_VAL) पूर्ण

अटल अंतरभूत व्योम osq_lock_init(काष्ठा optimistic_spin_queue *lock)
अणु
	atomic_set(&lock->tail, OSQ_UNLOCKED_VAL);
पूर्ण

बाह्य bool osq_lock(काष्ठा optimistic_spin_queue *lock);
बाह्य व्योम osq_unlock(काष्ठा optimistic_spin_queue *lock);

अटल अंतरभूत bool osq_is_locked(काष्ठा optimistic_spin_queue *lock)
अणु
	वापस atomic_पढ़ो(&lock->tail) != OSQ_UNLOCKED_VAL;
पूर्ण

#पूर्ण_अगर
