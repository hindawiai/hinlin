<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Mutexes: blocking mutual exclusion locks
 *
 * started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * This file contains mutex debugging related पूर्णांकernal declarations,
 * prototypes and अंतरभूत functions, क्रम the CONFIG_DEBUG_MUTEXES हाल.
 * More details are in kernel/mutex-debug.c.
 */

/*
 * This must be called with lock->रुको_lock held.
 */
बाह्य व्योम debug_mutex_lock_common(काष्ठा mutex *lock,
				    काष्ठा mutex_रुकोer *रुकोer);
बाह्य व्योम debug_mutex_wake_रुकोer(काष्ठा mutex *lock,
				    काष्ठा mutex_रुकोer *रुकोer);
बाह्य व्योम debug_mutex_मुक्त_रुकोer(काष्ठा mutex_रुकोer *रुकोer);
बाह्य व्योम debug_mutex_add_रुकोer(काष्ठा mutex *lock,
				   काष्ठा mutex_रुकोer *रुकोer,
				   काष्ठा task_काष्ठा *task);
बाह्य व्योम debug_mutex_हटाओ_रुकोer(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer,
				काष्ठा task_काष्ठा *task);
बाह्य व्योम debug_mutex_unlock(काष्ठा mutex *lock);
बाह्य व्योम debug_mutex_init(काष्ठा mutex *lock, स्थिर अक्षर *name,
			     काष्ठा lock_class_key *key);
