<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Fallback per-CPU frame poपूर्णांकer holder
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _ASM_GENERIC_IRQ_REGS_H
#घोषणा _ASM_GENERIC_IRQ_REGS_H

#समावेश <linux/percpu.h>

/*
 * Per-cpu current frame poपूर्णांकer - the location of the last exception frame on
 * the stack
 */
DECLARE_PER_CPU(काष्ठा pt_regs *, __irq_regs);

अटल अंतरभूत काष्ठा pt_regs *get_irq_regs(व्योम)
अणु
	वापस __this_cpu_पढ़ो(__irq_regs);
पूर्ण

अटल अंतरभूत काष्ठा pt_regs *set_irq_regs(काष्ठा pt_regs *new_regs)
अणु
	काष्ठा pt_regs *old_regs;

	old_regs = __this_cpu_पढ़ो(__irq_regs);
	__this_cpu_ग_लिखो(__irq_regs, new_regs);
	वापस old_regs;
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_IRQ_REGS_H */
