<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/mach/irq.h
 *
 *  Copyright (C) 1995-2000 Russell King.
 */
#अगर_अघोषित __ASM_ARM_MACH_IRQ_H
#घोषणा __ASM_ARM_MACH_IRQ_H

#समावेश <linux/irq.h>

काष्ठा seq_file;

/*
 * This is पूर्णांकernal.  Do not use it.
 */
बाह्य व्योम init_FIQ(पूर्णांक);
बाह्य पूर्णांक show_fiq_list(काष्ठा seq_file *, पूर्णांक);

/*
 * This is क्रम easy migration, but should be changed in the source
 */
#घोषणा करो_bad_IRQ(desc)				\
करो अणु							\
	raw_spin_lock(&desc->lock);			\
	handle_bad_irq(desc);				\
	raw_spin_unlock(&desc->lock);			\
पूर्ण जबतक(0)

#पूर्ण_अगर
