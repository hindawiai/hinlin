<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* irq.h: IRQ रेजिस्टरs on the 64-bit Sparc.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998 Jakub Jelinek (jj@ultra.linux.cz)
 */

#अगर_अघोषित _SPARC64_IRQ_H
#घोषणा _SPARC64_IRQ_H

#समावेश <linux/linkage.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/pil.h>
#समावेश <यंत्र/ptrace.h>

/* IMAP/ICLR रेजिस्टर defines */
#घोषणा IMAP_VALID		0x80000000UL	/* IRQ Enabled		*/
#घोषणा IMAP_TID_UPA		0x7c000000UL	/* UPA TargetID		*/
#घोषणा IMAP_TID_JBUS		0x7c000000UL	/* JBUS TargetID	*/
#घोषणा IMAP_TID_SHIFT		26
#घोषणा IMAP_AID_SAFARI		0x7c000000UL	/* Safari AgentID	*/
#घोषणा IMAP_AID_SHIFT		26
#घोषणा IMAP_NID_SAFARI		0x03e00000UL	/* Safari NodeID	*/
#घोषणा IMAP_NID_SHIFT		21
#घोषणा IMAP_IGN		0x000007c0UL	/* IRQ Group Number	*/
#घोषणा IMAP_INO		0x0000003fUL	/* IRQ Number		*/
#घोषणा IMAP_INR		0x000007ffUL	/* Full पूर्णांकerrupt number*/

#घोषणा ICLR_IDLE		0x00000000UL	/* Idle state		*/
#घोषणा ICLR_TRANSMIT		0x00000001UL	/* Transmit state	*/
#घोषणा ICLR_PENDING		0x00000003UL	/* Pending state	*/

/* The largest number of unique पूर्णांकerrupt sources we support.
 * If this needs to ever be larger than 255, you need to change
 * the type of ino_bucket->irq as appropriate.
 *
 * ino_bucket->irq allocation is made during अणुsun4v_,पूर्णbuild_irq().
 */
#घोषणा NR_IRQS		(2048)

व्योम irq_install_pre_handler(पूर्णांक irq,
			     व्योम (*func)(अचिन्हित पूर्णांक, व्योम *, व्योम *),
			     व्योम *arg1, व्योम *arg2);
#घोषणा irq_canonicalize(irq)	(irq)
अचिन्हित पूर्णांक build_irq(पूर्णांक inofixup, अचिन्हित दीर्घ iclr, अचिन्हित दीर्घ imap);
अचिन्हित पूर्णांक sun4v_build_irq(u32 devhandle, अचिन्हित पूर्णांक devino);
अचिन्हित पूर्णांक sun4v_build_virq(u32 devhandle, अचिन्हित पूर्णांक devino);
अचिन्हित पूर्णांक sun4v_build_msi(u32 devhandle, अचिन्हित पूर्णांक *irq_p,
			     अचिन्हित पूर्णांक msi_devino_start,
			     अचिन्हित पूर्णांक msi_devino_end);
व्योम sun4v_destroy_msi(अचिन्हित पूर्णांक irq);
अचिन्हित पूर्णांक sun4u_build_msi(u32 portid, अचिन्हित पूर्णांक *irq_p,
			     अचिन्हित पूर्णांक msi_devino_start,
			     अचिन्हित पूर्णांक msi_devino_end,
			     अचिन्हित दीर्घ imap_base,
			     अचिन्हित दीर्घ iclr_base);
व्योम sun4u_destroy_msi(अचिन्हित पूर्णांक irq);

अचिन्हित पूर्णांक irq_alloc(अचिन्हित पूर्णांक dev_handle, अचिन्हित पूर्णांक dev_ino);
व्योम irq_मुक्त(अचिन्हित पूर्णांक irq);

व्योम __init init_IRQ(व्योम);
व्योम fixup_irqs(व्योम);

अटल अंतरभूत व्योम set_softपूर्णांक(अचिन्हित दीर्घ bits)
अणु
	__यंत्र__ __अस्थिर__("wr	%0, 0x0, %%set_softint"
			     : /* No outमाला_दो */
			     : "r" (bits));
पूर्ण

अटल अंतरभूत व्योम clear_softपूर्णांक(अचिन्हित दीर्घ bits)
अणु
	__यंत्र__ __अस्थिर__("wr	%0, 0x0, %%clear_softint"
			     : /* No outमाला_दो */
			     : "r" (bits));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_softपूर्णांक(व्योम)
अणु
	अचिन्हित दीर्घ retval;

	__यंत्र__ __अस्थिर__("rd	%%softint, %0"
			     : "=r" (retval));
	वापस retval;
पूर्ण

व्योम arch_trigger_cpumask_backtrace(स्थिर काष्ठा cpumask *mask,
				    bool exclude_self);
#घोषणा arch_trigger_cpumask_backtrace arch_trigger_cpumask_backtrace

बाह्य व्योम *hardirq_stack[NR_CPUS];
बाह्य व्योम *softirq_stack[NR_CPUS];

#घोषणा NO_IRQ		0xffffffff

#पूर्ण_अगर
