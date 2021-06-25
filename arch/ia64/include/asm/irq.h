<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_IRQ_H
#घोषणा _ASM_IA64_IRQ_H

/*
 * Copyright (C) 1999-2000, 2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 *
 * 11/24/98	S.Eranian 	updated TIMER_IRQ and irq_canonicalize
 * 01/20/99	S.Eranian	added keyboard पूर्णांकerrupt
 * 02/29/00     D.Mosberger	moved most things पूर्णांकo hw_irq.h
 */

#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/native/irq.h>

#घोषणा NR_IRQS		IA64_NATIVE_NR_IRQS

अटल __अंतरभूत__ पूर्णांक
irq_canonicalize (पूर्णांक irq)
अणु
	/*
	 * We करो the legacy thing here of pretending that irqs < 16
	 * are 8259 irqs.  This really shouldn't be necessary at all,
	 * but we keep it here as serial.c still uses it...
	 */
	वापस ((irq == 2) ? 9 : irq);
पूर्ण

बाह्य व्योम set_irq_affinity_info (अचिन्हित पूर्णांक irq, पूर्णांक dest, पूर्णांक redir);

पूर्णांक create_irq(व्योम);
व्योम destroy_irq(अचिन्हित पूर्णांक irq);

#पूर्ण_अगर /* _ASM_IA64_IRQ_H */
