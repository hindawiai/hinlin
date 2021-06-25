<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित IRQ_POLL_H
#घोषणा IRQ_POLL_H

काष्ठा irq_poll;
प्रकार पूर्णांक (irq_poll_fn)(काष्ठा irq_poll *, पूर्णांक);

काष्ठा irq_poll अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ state;
	पूर्णांक weight;
	irq_poll_fn *poll;
पूर्ण;

क्रमागत अणु
	IRQ_POLL_F_SCHED	= 0,
	IRQ_POLL_F_DISABLE	= 1,
पूर्ण;

बाह्य व्योम irq_poll_sched(काष्ठा irq_poll *);
बाह्य व्योम irq_poll_init(काष्ठा irq_poll *, पूर्णांक, irq_poll_fn *);
बाह्य व्योम irq_poll_complete(काष्ठा irq_poll *);
बाह्य व्योम irq_poll_enable(काष्ठा irq_poll *);
बाह्य व्योम irq_poll_disable(काष्ठा irq_poll *);

#पूर्ण_अगर
