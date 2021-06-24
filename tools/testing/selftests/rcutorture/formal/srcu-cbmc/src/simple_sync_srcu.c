<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <config.h>

#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकघोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>

#समावेश "int_typedefs.h"

#समावेश "barriers.h"
#समावेश "bug_on.h"
#समावेश "locks.h"
#समावेश "misc.h"
#समावेश "preempt.h"
#समावेश "percpu.h"
#समावेश "workqueues.h"

#समावेश <linux/srcu.h>

/* Functions needed from modअगरy_srcu.c */
bool try_check_zero(काष्ठा srcu_काष्ठा *sp, पूर्णांक idx, पूर्णांक trycount);
व्योम srcu_flip(काष्ठा srcu_काष्ठा *sp);

/* Simpler implementation of synchronize_srcu that ignores batching. */
व्योम synchronize_srcu(काष्ठा srcu_काष्ठा *sp)
अणु
	पूर्णांक idx;
	/*
	 * This code assumes that try_check_zero will succeed anyway,
	 * so there is no poपूर्णांक in multiple tries.
	 */
	स्थिर पूर्णांक trycount = 1;

	might_sleep();

	/* Ignore the lock, as multiple ग_लिखोrs aren't working yet anyway. */

	idx = 1 ^ (sp->completed & 1);

	/* For comments see srcu_advance_batches. */

	assume(try_check_zero(sp, idx, trycount));

	srcu_flip(sp);

	assume(try_check_zero(sp, idx^1, trycount));
पूर्ण
