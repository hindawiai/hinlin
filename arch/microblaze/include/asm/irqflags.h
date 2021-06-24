<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_IRQFLAGS_H
#घोषणा _ASM_MICROBLAZE_IRQFLAGS_H

#समावेश <linux/types.h>
#समावेश <यंत्र/रेजिस्टरs.h>

#अगर CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर("	msrclr %0, %1	\n"
		     "	nop		\n"
		     : "=r"(flags)
		     : "i"(MSR_IE)
		     : "memory");
	वापस flags;
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_disable(व्योम)
अणु
	/* this uses r0 without declaring it - is that correct? */
	यंत्र अस्थिर("	msrclr r0, %0	\n"
		     "	nop		\n"
		     :
		     : "i"(MSR_IE)
		     : "memory");
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_enable(व्योम)
अणु
	/* this uses r0 without declaring it - is that correct? */
	यंत्र अस्थिर("	msrset	r0, %0	\n"
		     "	nop		\n"
		     :
		     : "i"(MSR_IE)
		     : "memory");
पूर्ण

#अन्यथा /* !CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags, पंचांगp;
	यंत्र अस्थिर ("	mfs	%0, rmsr	\n"
		      "	nop			\n"
		      "	andi	%1, %0, %2	\n"
		      "	mts	rmsr, %1	\n"
		      "	nop			\n"
		      : "=r"(flags), "=r"(पंचांगp)
		      : "i"(~MSR_IE)
		      : "memory");
	वापस flags;
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_disable(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;
	यंत्र अस्थिर("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     "	andi	%0, %0, %1	\n"
		     "	mts	rmsr, %0	\n"
		     "	nop			\n"
		     : "=r"(पंचांगp)
		     : "i"(~MSR_IE)
		     : "memory");
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;
	यंत्र अस्थिर("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     "	ori	%0, %0, %1	\n"
		     "	mts	rmsr, %0	\n"
		     "	nop			\n"
		     : "=r"(पंचांगp)
		     : "i"(MSR_IE)
		     : "memory");
पूर्ण

#पूर्ण_अगर /* CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	यंत्र अस्थिर("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     : "=r"(flags)
		     :
		     : "memory");
	वापस flags;
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर("	mts	rmsr, %0	\n"
		     "	nop			\n"
		     :
		     : "r"(flags)
		     : "memory");
पूर्ण

अटल अंतरभूत notrace bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags & MSR_IE) == 0;
पूर्ण

अटल अंतरभूत notrace bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

#पूर्ण_अगर /* _ASM_MICROBLAZE_IRQFLAGS_H */
