<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Do sleep inside a spin-lock
 *  Copyright (c) 1999 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश "seq_lock.h"

/* रुको until all locks are released */
व्योम snd_use_lock_sync_helper(snd_use_lock_t *lockp, स्थिर अक्षर *file, पूर्णांक line)
अणु
	पूर्णांक warn_count = 5 * HZ;

	अगर (atomic_पढ़ो(lockp) < 0) अणु
		pr_warn("ALSA: seq_lock: lock trouble [counter = %d] in %s:%d\n", atomic_पढ़ो(lockp), file, line);
		वापस;
	पूर्ण
	जबतक (atomic_पढ़ो(lockp) > 0) अणु
		अगर (warn_count-- == 0)
			pr_warn("ALSA: seq_lock: waiting [%d left] in %s:%d\n", atomic_पढ़ो(lockp), file, line);
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_use_lock_sync_helper);
