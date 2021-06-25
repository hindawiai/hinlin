<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित __ASM_SIMD_H
#घोषणा __ASM_SIMD_H

#समावेश <linux/compiler.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/percpu.h>
#समावेश <linux/preempt.h>
#समावेश <linux/types.h>

DECLARE_PER_CPU(bool, fpsimd_context_busy);

#अगर_घोषित CONFIG_KERNEL_MODE_NEON

/*
 * may_use_simd - whether it is allowable at this समय to issue SIMD
 *                inकाष्ठाions or access the SIMD रेजिस्टर file
 *
 * Callers must not assume that the result reमुख्यs true beyond the next
 * preempt_enable() or वापस from softirq context.
 */
अटल __must_check अंतरभूत bool may_use_simd(व्योम)
अणु
	/*
	 * We must make sure that the SVE has been initialized properly
	 * beक्रमe using the SIMD in kernel.
	 * fpsimd_context_busy is only set जबतक preemption is disabled,
	 * and is clear whenever preemption is enabled. Since
	 * this_cpu_पढ़ो() is atomic w.r.t. preemption, fpsimd_context_busy
	 * cannot change under our feet -- अगर it's set we cannot be
	 * migrated, and अगर it's clear we cannot be migrated to a CPU
	 * where it is set.
	 */
	वापस !WARN_ON(!प्रणाली_capabilities_finalized()) &&
	       प्रणाली_supports_fpsimd() &&
	       !in_irq() && !irqs_disabled() && !in_nmi() &&
	       !this_cpu_पढ़ो(fpsimd_context_busy);
पूर्ण

#अन्यथा /* ! CONFIG_KERNEL_MODE_NEON */

अटल __must_check अंतरभूत bool may_use_simd(व्योम) अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* ! CONFIG_KERNEL_MODE_NEON */

#पूर्ण_अगर
