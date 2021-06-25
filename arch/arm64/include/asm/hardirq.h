<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_HARसूचीQ_H
#घोषणा __ASM_HARसूचीQ_H

#समावेश <linux/cache.h>
#समावेश <linux/percpu.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/sysreg.h>

#घोषणा ack_bad_irq ack_bad_irq
#समावेश <यंत्र-generic/hardirq.h>

#घोषणा __ARCH_IRQ_EXIT_IRQS_DISABLED	1

काष्ठा nmi_ctx अणु
	u64 hcr;
	अचिन्हित पूर्णांक cnt;
पूर्ण;

DECLARE_PER_CPU(काष्ठा nmi_ctx, nmi_contexts);

#घोषणा arch_nmi_enter()						\
करो अणु									\
	काष्ठा nmi_ctx *___ctx;						\
	u64 ___hcr;							\
									\
	अगर (!is_kernel_in_hyp_mode())					\
		अवरोध;							\
									\
	___ctx = this_cpu_ptr(&nmi_contexts);				\
	अगर (___ctx->cnt) अणु						\
		___ctx->cnt++;						\
		अवरोध;							\
	पूर्ण								\
									\
	___hcr = पढ़ो_sysreg(hcr_el2);					\
	अगर (!(___hcr & HCR_TGE)) अणु					\
		ग_लिखो_sysreg(___hcr | HCR_TGE, hcr_el2);		\
		isb();							\
	पूर्ण								\
	/*								\
	 * Make sure the sysreg ग_लिखो is perक्रमmed beक्रमe ___ctx->cnt	\
	 * is set to 1. NMIs that see cnt == 1 will rely on us.		\
	 */								\
	barrier();							\
	___ctx->cnt = 1;                                                \
	/*								\
	 * Make sure ___ctx->cnt is set beक्रमe we save ___hcr. We	\
	 * करोn't want ___ctx->hcr to be overwritten.			\
	 */								\
	barrier();							\
	___ctx->hcr = ___hcr;						\
पूर्ण जबतक (0)

#घोषणा arch_nmi_निकास()							\
करो अणु									\
	काष्ठा nmi_ctx *___ctx;						\
	u64 ___hcr;							\
									\
	अगर (!is_kernel_in_hyp_mode())					\
		अवरोध;							\
									\
	___ctx = this_cpu_ptr(&nmi_contexts);				\
	___hcr = ___ctx->hcr;						\
	/*								\
	 * Make sure we पढ़ो ___ctx->hcr beक्रमe we release		\
	 * ___ctx->cnt as it makes ___ctx->hcr updatable again.		\
	 */								\
	barrier();							\
	___ctx->cnt--;							\
	/*								\
	 * Make sure ___ctx->cnt release is visible beक्रमe we		\
	 * restore the sysreg. Otherwise a new NMI occurring		\
	 * right after ग_लिखो_sysreg() can be fooled and think		\
	 * we secured things क्रम it.					\
	 */								\
	barrier();							\
	अगर (!___ctx->cnt && !(___hcr & HCR_TGE))			\
		ग_लिखो_sysreg(___hcr, hcr_el2);				\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	बाह्य अचिन्हित दीर्घ irq_err_count;
	irq_err_count++;
पूर्ण

#पूर्ण_अगर /* __ASM_HARसूचीQ_H */
