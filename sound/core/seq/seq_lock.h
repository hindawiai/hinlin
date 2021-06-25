<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SND_SEQ_LOCK_H
#घोषणा __SND_SEQ_LOCK_H

#समावेश <linux/sched.h>

प्रकार atomic_t snd_use_lock_t;

/* initialize lock */
#घोषणा snd_use_lock_init(lockp) atomic_set(lockp, 0)

/* increment lock */
#घोषणा snd_use_lock_use(lockp) atomic_inc(lockp)

/* release lock */
#घोषणा snd_use_lock_मुक्त(lockp) atomic_dec(lockp)

/* रुको until all locks are released */
व्योम snd_use_lock_sync_helper(snd_use_lock_t *lock, स्थिर अक्षर *file, पूर्णांक line);
#घोषणा snd_use_lock_sync(lockp) snd_use_lock_sync_helper(lockp, __BASE_खाता__, __LINE__)

#पूर्ण_अगर /* __SND_SEQ_LOCK_H */
