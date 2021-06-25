<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Mutexes: blocking mutual exclusion locks
 *
 * started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * This file contains mutex debugging related पूर्णांकernal prototypes, क्रम the
 * !CONFIG_DEBUG_MUTEXES हाल. Most of them are NOPs:
 */

#घोषणा debug_mutex_wake_रुकोer(lock, रुकोer)		करो अणु पूर्ण जबतक (0)
#घोषणा debug_mutex_मुक्त_रुकोer(रुकोer)			करो अणु पूर्ण जबतक (0)
#घोषणा debug_mutex_add_रुकोer(lock, रुकोer, ti)	करो अणु पूर्ण जबतक (0)
#घोषणा debug_mutex_हटाओ_रुकोer(lock, रुकोer, ti)     करो अणु पूर्ण जबतक (0)
#घोषणा debug_mutex_unlock(lock)			करो अणु पूर्ण जबतक (0)
#घोषणा debug_mutex_init(lock, name, key)		करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम
debug_mutex_lock_common(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer)
अणु
पूर्ण
