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

#अगर_घोषित USE_SIMPLE_SYNC_SRCU
#घोषणा synchronize_srcu(sp) synchronize_srcu_original(sp)
#पूर्ण_अगर

#समावेश <srcu.c>

#अगर_घोषित USE_SIMPLE_SYNC_SRCU
#अघोषित synchronize_srcu

#समावेश "simple_sync_srcu.c"
#पूर्ण_अगर
