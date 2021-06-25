<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * Copyright (C) 2006 Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित __ASM_IRQ_REGS_H
#घोषणा __ASM_IRQ_REGS_H

#घोषणा ARCH_HAS_OWN_IRQ_REGS

#समावेश <linux/thपढ़ो_info.h>

अटल अंतरभूत काष्ठा pt_regs *get_irq_regs(व्योम)
अणु
	वापस current_thपढ़ो_info()->regs;
पूर्ण

अटल अंतरभूत काष्ठा pt_regs *set_irq_regs(काष्ठा pt_regs *new_regs)
अणु
	काष्ठा pt_regs *old_regs;

	old_regs = get_irq_regs();
	current_thपढ़ो_info()->regs = new_regs;

	वापस old_regs;
पूर्ण

#पूर्ण_अगर /* __ASM_IRQ_REGS_H */
