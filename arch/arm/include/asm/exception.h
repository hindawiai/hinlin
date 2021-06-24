<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Annotations क्रम marking C functions as exception handlers.
 *
 * These should only be used क्रम C functions that are called from the low
 * level exception entry code and not any पूर्णांकervening C code.
 */
#अगर_अघोषित __ASM_ARM_EXCEPTION_H
#घोषणा __ASM_ARM_EXCEPTION_H

#समावेश <linux/पूर्णांकerrupt.h>

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
#घोषणा __exception_irq_entry	__irq_entry
#अन्यथा
#घोषणा __exception_irq_entry
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARM_EXCEPTION_H */
