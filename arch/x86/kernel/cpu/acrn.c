<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACRN detection support
 *
 * Copyright (C) 2019 Intel Corporation. All rights reserved.
 *
 * Jason Chen CJ <jason.cj.chen@पूर्णांकel.com>
 * Zhao Yakui <yakui.zhao@पूर्णांकel.com>
 *
 */

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/acrn.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/irq_regs.h>

अटल u32 __init acrn_detect(व्योम)
अणु
	वापस acrn_cpuid_base();
पूर्ण

अटल व्योम __init acrn_init_platक्रमm(व्योम)
अणु
	/* Setup the IDT क्रम ACRN hypervisor callback */
	alloc_पूर्णांकr_gate(HYPERVISOR_CALLBACK_VECTOR, यंत्र_sysvec_acrn_hv_callback);
पूर्ण

अटल bool acrn_x2apic_available(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_X2APIC);
पूर्ण

अटल व्योम (*acrn_पूर्णांकr_handler)(व्योम);

DEFINE_IDTENTRY_SYSVEC(sysvec_acrn_hv_callback)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	/*
	 * The hypervisor requires that the APIC EOI should be acked.
	 * If the APIC EOI is not acked, the APIC ISR bit क्रम the
	 * HYPERVISOR_CALLBACK_VECTOR will not be cleared and then it
	 * will block the पूर्णांकerrupt whose vector is lower than
	 * HYPERVISOR_CALLBACK_VECTOR.
	 */
	ack_APIC_irq();
	inc_irq_stat(irq_hv_callback_count);

	अगर (acrn_पूर्णांकr_handler)
		acrn_पूर्णांकr_handler();

	set_irq_regs(old_regs);
पूर्ण

व्योम acrn_setup_पूर्णांकr_handler(व्योम (*handler)(व्योम))
अणु
	acrn_पूर्णांकr_handler = handler;
पूर्ण
EXPORT_SYMBOL_GPL(acrn_setup_पूर्णांकr_handler);

व्योम acrn_हटाओ_पूर्णांकr_handler(व्योम)
अणु
	acrn_पूर्णांकr_handler = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(acrn_हटाओ_पूर्णांकr_handler);

स्थिर __initस्थिर काष्ठा hypervisor_x86 x86_hyper_acrn = अणु
	.name                   = "ACRN",
	.detect                 = acrn_detect,
	.type			= X86_HYPER_ACRN,
	.init.init_platक्रमm     = acrn_init_platक्रमm,
	.init.x2apic_available  = acrn_x2apic_available,
पूर्ण;
