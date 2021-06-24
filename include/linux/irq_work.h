<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IRQ_WORK_H
#घोषणा _LINUX_IRQ_WORK_H

#समावेश <linux/smp_types.h>

/*
 * An entry can be in one of four states:
 *
 * मुक्त	     शून्य, 0 -> अणुclaimedपूर्ण       : मुक्त to be used
 * claimed   शून्य, 3 -> अणुpendingपूर्ण       : claimed to be enqueued
 * pending   next, 3 -> अणुbusyपूर्ण          : queued, pending callback
 * busy      शून्य, 2 -> अणुमुक्त, claimedपूर्ण : callback in progress, can be claimed
 */

काष्ठा irq_work अणु
	काष्ठा __call_single_node node;
	व्योम (*func)(काष्ठा irq_work *);
पूर्ण;

#घोषणा __IRQ_WORK_INIT(_func, _flags) (काष्ठा irq_work)अणु	\
	.node = अणु .u_flags = (_flags), पूर्ण,			\
	.func = (_func),					\
पूर्ण

#घोषणा IRQ_WORK_INIT(_func) __IRQ_WORK_INIT(_func, 0)
#घोषणा IRQ_WORK_INIT_LAZY(_func) __IRQ_WORK_INIT(_func, IRQ_WORK_LAZY)
#घोषणा IRQ_WORK_INIT_HARD(_func) __IRQ_WORK_INIT(_func, IRQ_WORK_HARD_IRQ)

#घोषणा DEFINE_IRQ_WORK(name, _f)				\
	काष्ठा irq_work name = IRQ_WORK_INIT(_f)

अटल अंतरभूत
व्योम init_irq_work(काष्ठा irq_work *work, व्योम (*func)(काष्ठा irq_work *))
अणु
	*work = IRQ_WORK_INIT(func);
पूर्ण

अटल अंतरभूत bool irq_work_is_pending(काष्ठा irq_work *work)
अणु
	वापस atomic_पढ़ो(&work->node.a_flags) & IRQ_WORK_PENDING;
पूर्ण

अटल अंतरभूत bool irq_work_is_busy(काष्ठा irq_work *work)
अणु
	वापस atomic_पढ़ो(&work->node.a_flags) & IRQ_WORK_BUSY;
पूर्ण

bool irq_work_queue(काष्ठा irq_work *work);
bool irq_work_queue_on(काष्ठा irq_work *work, पूर्णांक cpu);

व्योम irq_work_tick(व्योम);
व्योम irq_work_sync(काष्ठा irq_work *work);

#अगर_घोषित CONFIG_IRQ_WORK
#समावेश <यंत्र/irq_work.h>

व्योम irq_work_run(व्योम);
bool irq_work_needs_cpu(व्योम);
व्योम irq_work_single(व्योम *arg);
#अन्यथा
अटल अंतरभूत bool irq_work_needs_cpu(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम irq_work_run(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम irq_work_single(व्योम *arg) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_IRQ_WORK_H */
