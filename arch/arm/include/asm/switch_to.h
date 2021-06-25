<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_SWITCH_TO_H
#घोषणा __ASM_ARM_SWITCH_TO_H

#समावेश <linux/thपढ़ो_info.h>

/*
 * For v7 SMP cores running a preemptible kernel we may be pre-empted
 * during a TLB मुख्यtenance operation, so execute an inner-shareable dsb
 * to ensure that the मुख्यtenance completes in हाल we migrate to another
 * CPU.
 */
#अगर defined(CONFIG_PREEMPTION) && defined(CONFIG_SMP) && defined(CONFIG_CPU_V7)
#घोषणा __complete_pending_tlbi()	dsb(ish)
#अन्यथा
#घोषणा __complete_pending_tlbi()
#पूर्ण_अगर

/*
 * चयन_to(prev, next) should चयन from task `prev' to `next'
 * `prev' will never be the same as `next'.  schedule() itself
 * contains the memory barrier to tell GCC not to cache `current'.
 */
बाह्य काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *, काष्ठा thपढ़ो_info *, काष्ठा thपढ़ो_info *);

#घोषणा चयन_to(prev,next,last)					\
करो अणु									\
	__complete_pending_tlbi();					\
	last = __चयन_to(prev,task_thपढ़ो_info(prev), task_thपढ़ो_info(next));	\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_ARM_SWITCH_TO_H */
