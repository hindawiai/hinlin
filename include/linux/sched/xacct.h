<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_XACCT_H
#घोषणा _LINUX_SCHED_XACCT_H

/*
 * Extended task accounting methods:
 */

#समावेश <linux/sched.h>

#अगर_घोषित CONFIG_TASK_XACCT
अटल अंतरभूत व्योम add_rअक्षर(काष्ठा task_काष्ठा *tsk, sमाप_प्रकार amt)
अणु
	tsk->ioac.rअक्षर += amt;
पूर्ण

अटल अंतरभूत व्योम add_wअक्षर(काष्ठा task_काष्ठा *tsk, sमाप_प्रकार amt)
अणु
	tsk->ioac.wअक्षर += amt;
पूर्ण

अटल अंतरभूत व्योम inc_syscr(काष्ठा task_काष्ठा *tsk)
अणु
	tsk->ioac.syscr++;
पूर्ण

अटल अंतरभूत व्योम inc_syscw(काष्ठा task_काष्ठा *tsk)
अणु
	tsk->ioac.syscw++;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम add_rअक्षर(काष्ठा task_काष्ठा *tsk, sमाप_प्रकार amt)
अणु
पूर्ण

अटल अंतरभूत व्योम add_wअक्षर(काष्ठा task_काष्ठा *tsk, sमाप_प्रकार amt)
अणु
पूर्ण

अटल अंतरभूत व्योम inc_syscr(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण

अटल अंतरभूत व्योम inc_syscw(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_XACCT_H */
