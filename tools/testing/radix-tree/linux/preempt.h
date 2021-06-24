<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PREEMPT_H
#घोषणा __LINUX_PREEMPT_H

बाह्य पूर्णांक preempt_count;

#घोषणा preempt_disable()	uatomic_inc(&preempt_count)
#घोषणा preempt_enable()	uatomic_dec(&preempt_count)

अटल अंतरभूत पूर्णांक in_पूर्णांकerrupt(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __LINUX_PREEMPT_H */
