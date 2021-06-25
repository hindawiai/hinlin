<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SMP_TYPES_H
#घोषणा __LINUX_SMP_TYPES_H

#समावेश <linux/llist.h>

क्रमागत अणु
	CSD_FLAG_LOCK		= 0x01,

	IRQ_WORK_PENDING	= 0x01,
	IRQ_WORK_BUSY		= 0x02,
	IRQ_WORK_LAZY		= 0x04, /* No IPI, रुको क्रम tick */
	IRQ_WORK_HARD_IRQ	= 0x08, /* IRQ context on PREEMPT_RT */

	IRQ_WORK_CLAIMED	= (IRQ_WORK_PENDING | IRQ_WORK_BUSY),

	CSD_TYPE_ASYNC		= 0x00,
	CSD_TYPE_SYNC		= 0x10,
	CSD_TYPE_IRQ_WORK	= 0x20,
	CSD_TYPE_TTWU		= 0x30,

	CSD_FLAG_TYPE_MASK	= 0xF0,
पूर्ण;

/*
 * काष्ठा __call_single_node is the primary type on
 * smp.c:call_single_queue.
 *
 * flush_smp_call_function_queue() only पढ़ोs the type from
 * __call_single_node::u_flags as a regular load, the above
 * (anonymous) क्रमागत defines all the bits of this word.
 *
 * Other bits are not modअगरied until the type is known.
 *
 * CSD_TYPE_SYNC/ASYNC:
 *	काष्ठा अणु
 *		काष्ठा llist_node node;
 *		अचिन्हित पूर्णांक flags;
 *		smp_call_func_t func;
 *		व्योम *info;
 *	पूर्ण;
 *
 * CSD_TYPE_IRQ_WORK:
 *	काष्ठा अणु
 *		काष्ठा llist_node node;
 *		atomic_t flags;
 *		व्योम (*func)(काष्ठा irq_work *);
 *	पूर्ण;
 *
 * CSD_TYPE_TTWU:
 *	काष्ठा अणु
 *		काष्ठा llist_node node;
 *		अचिन्हित पूर्णांक flags;
 *	पूर्ण;
 *
 */

काष्ठा __call_single_node अणु
	काष्ठा llist_node	llist;
	जोड़ अणु
		अचिन्हित पूर्णांक	u_flags;
		atomic_t	a_flags;
	पूर्ण;
#अगर_घोषित CONFIG_64BIT
	u16 src, dst;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* __LINUX_SMP_TYPES_H */
