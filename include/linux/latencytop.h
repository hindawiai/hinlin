<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * latencytop.h: Infraकाष्ठाure क्रम displaying latency
 *
 * (C) Copyright 2008 Intel Corporation
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 *
 */

#अगर_अघोषित _INCLUDE_GUARD_LATENCYTOP_H_
#घोषणा _INCLUDE_GUARD_LATENCYTOP_H_

#समावेश <linux/compiler.h>
काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_LATENCYTOP

#घोषणा LT_SAVECOUNT		32
#घोषणा LT_BACKTRACEDEPTH	12

काष्ठा latency_record अणु
	अचिन्हित दीर्घ	backtrace[LT_BACKTRACEDEPTH];
	अचिन्हित पूर्णांक	count;
	अचिन्हित दीर्घ	समय;
	अचिन्हित दीर्घ	max;
पूर्ण;



बाह्य पूर्णांक latencytop_enabled;
व्योम __account_scheduler_latency(काष्ठा task_काष्ठा *task, पूर्णांक usecs, पूर्णांक पूर्णांकer);
अटल अंतरभूत व्योम
account_scheduler_latency(काष्ठा task_काष्ठा *task, पूर्णांक usecs, पूर्णांक पूर्णांकer)
अणु
	अगर (unlikely(latencytop_enabled))
		__account_scheduler_latency(task, usecs, पूर्णांकer);
पूर्ण

व्योम clear_tsk_latency_tracing(काष्ठा task_काष्ठा *p);

पूर्णांक sysctl_latencytop(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos);

#अन्यथा

अटल अंतरभूत व्योम
account_scheduler_latency(काष्ठा task_काष्ठा *task, पूर्णांक usecs, पूर्णांक पूर्णांकer)
अणु
पूर्ण

अटल अंतरभूत व्योम clear_tsk_latency_tracing(काष्ठा task_काष्ठा *p)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
