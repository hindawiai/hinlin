<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* irq.h: IRQ रेजिस्टरs on the Sparc.
 *
 * Copyright (C) 1995, 2007 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _SPARC_IRQ_H
#घोषणा _SPARC_IRQ_H

/* Allocated number of logical irq numbers.
 * sun4d boxes (ss2000e) should be OK with ~32.
 * Be on the safe side and make room क्रम 64
 */
#घोषणा NR_IRQS    64

#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा irq_canonicalize(irq)	(irq)

व्योम __init init_IRQ(व्योम);
व्योम __init sun4d_init_sbi_irq(व्योम);

#घोषणा NO_IRQ		0xffffffff

#पूर्ण_अगर
