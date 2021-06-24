<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  include/linux/संकेतfd.h
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 */
#अगर_अघोषित _LINUX_SIGNALFD_H
#घोषणा _LINUX_SIGNALFD_H

#समावेश <uapi/linux/संकेतfd.h>
#समावेश <linux/sched/संकेत.स>

#अगर_घोषित CONFIG_SIGNALFD

/*
 * Deliver the संकेत to listening संकेतfd.
 */
अटल अंतरभूत व्योम संकेतfd_notअगरy(काष्ठा task_काष्ठा *tsk, पूर्णांक sig)
अणु
	अगर (unlikely(रुकोqueue_active(&tsk->sighand->संकेतfd_wqh)))
		wake_up(&tsk->sighand->संकेतfd_wqh);
पूर्ण

बाह्य व्योम संकेतfd_cleanup(काष्ठा sighand_काष्ठा *sighand);

#अन्यथा /* CONFIG_SIGNALFD */

अटल अंतरभूत व्योम संकेतfd_notअगरy(काष्ठा task_काष्ठा *tsk, पूर्णांक sig) अणु पूर्ण

अटल अंतरभूत व्योम संकेतfd_cleanup(काष्ठा sighand_काष्ठा *sighand) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SIGNALFD */

#पूर्ण_अगर /* _LINUX_SIGNALFD_H */
