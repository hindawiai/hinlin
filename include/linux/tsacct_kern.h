<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tsacct_kern.h - kernel header क्रम प्रणाली accounting over taskstats पूर्णांकerface
 *
 * Copyright (C) Jay Lan	SGI
 */

#अगर_अघोषित _LINUX_TSACCT_KERN_H
#घोषणा _LINUX_TSACCT_KERN_H

#समावेश <linux/taskstats.h>

#अगर_घोषित CONFIG_TASKSTATS
बाह्य व्योम bacct_add_tsk(काष्ठा user_namespace *user_ns,
			  काष्ठा pid_namespace *pid_ns,
			  काष्ठा taskstats *stats, काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत व्योम bacct_add_tsk(काष्ठा user_namespace *user_ns,
				 काष्ठा pid_namespace *pid_ns,
				 काष्ठा taskstats *stats, काष्ठा task_काष्ठा *tsk)
अणुपूर्ण
#पूर्ण_अगर /* CONFIG_TASKSTATS */

#अगर_घोषित CONFIG_TASK_XACCT
बाह्य व्योम xacct_add_tsk(काष्ठा taskstats *stats, काष्ठा task_काष्ठा *p);
बाह्य व्योम acct_update_पूर्णांकegrals(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम acct_account_cpuसमय(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम acct_clear_पूर्णांकegrals(काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत व्योम xacct_add_tsk(काष्ठा taskstats *stats, काष्ठा task_काष्ठा *p)
अणुपूर्ण
अटल अंतरभूत व्योम acct_update_पूर्णांकegrals(काष्ठा task_काष्ठा *tsk)
अणुपूर्ण
अटल अंतरभूत व्योम acct_account_cpuसमय(काष्ठा task_काष्ठा *tsk)
अणुपूर्ण
अटल अंतरभूत व्योम acct_clear_पूर्णांकegrals(काष्ठा task_काष्ठा *tsk)
अणुपूर्ण
#पूर्ण_अगर /* CONFIG_TASK_XACCT */

#पूर्ण_अगर


