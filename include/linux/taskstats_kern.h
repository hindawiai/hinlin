<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* taskstats_kern.h - kernel header क्रम per-task statistics पूर्णांकerface
 *
 * Copyright (C) Shailabh Nagar, IBM Corp. 2006
 *           (C) Balbir Singh,   IBM Corp. 2006
 */

#अगर_अघोषित _LINUX_TASKSTATS_KERN_H
#घोषणा _LINUX_TASKSTATS_KERN_H

#समावेश <linux/taskstats.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_TASKSTATS
बाह्य काष्ठा kmem_cache *taskstats_cache;
बाह्य काष्ठा mutex taskstats_निकास_mutex;

अटल अंतरभूत व्योम taskstats_tgid_मुक्त(काष्ठा संकेत_काष्ठा *sig)
अणु
	अगर (sig->stats)
		kmem_cache_मुक्त(taskstats_cache, sig->stats);
पूर्ण

बाह्य व्योम taskstats_निकास(काष्ठा task_काष्ठा *, पूर्णांक group_dead);
बाह्य व्योम taskstats_init_early(व्योम);
#अन्यथा
अटल अंतरभूत व्योम taskstats_निकास(काष्ठा task_काष्ठा *tsk, पूर्णांक group_dead)
अणुपूर्ण
अटल अंतरभूत व्योम taskstats_tgid_मुक्त(काष्ठा संकेत_काष्ठा *sig)
अणुपूर्ण
अटल अंतरभूत व्योम taskstats_init_early(व्योम)
अणुपूर्ण
#पूर्ण_अगर /* CONFIG_TASKSTATS */

#पूर्ण_अगर

