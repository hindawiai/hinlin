<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * irq.c: API क्रम in kernel पूर्णांकerrupt controller
 * Copyright (c) 2007, Intel Corporation.
 * Copyright 2009 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Yaozu (Eddie) Dong <Eddie.करोng@पूर्णांकel.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/kvm_host.h>

#समावेश "irq.h"
#समावेश "i8254.h"
#समावेश "x86.h"
#समावेश "xen.h"

/*
 * check अगर there are pending समयr events
 * to be processed.
 */
पूर्णांक kvm_cpu_has_pending_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (lapic_in_kernel(vcpu))
		वापस apic_has_pending_समयr(vcpu);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(kvm_cpu_has_pending_समयr);

/*
 * check अगर there is a pending userspace बाह्यal पूर्णांकerrupt
 */
अटल पूर्णांक pending_userspace_extपूर्णांक(काष्ठा kvm_vcpu *v)
अणु
	वापस v->arch.pending_बाह्यal_vector != -1;
पूर्ण

/*
 * check अगर there is pending पूर्णांकerrupt from
 * non-APIC source without पूर्णांकack.
 */
पूर्णांक kvm_cpu_has_extपूर्णांक(काष्ठा kvm_vcpu *v)
अणु
	/*
	 * FIXME: पूर्णांकerrupt.injected represents an पूर्णांकerrupt whose
	 * side-effects have alपढ़ोy been applied (e.g. bit from IRR
	 * alपढ़ोy moved to ISR). Thereक्रमe, it is incorrect to rely
	 * on पूर्णांकerrupt.injected to know अगर there is a pending
	 * पूर्णांकerrupt in the user-mode LAPIC.
	 * This leads to nVMX/nSVM not be able to distinguish
	 * अगर it should निकास from L2 to L1 on EXTERNAL_INTERRUPT on
	 * pending पूर्णांकerrupt or should re-inject an injected
	 * पूर्णांकerrupt.
	 */
	अगर (!lapic_in_kernel(v))
		वापस v->arch.पूर्णांकerrupt.injected;

	अगर (kvm_xen_has_पूर्णांकerrupt(v))
		वापस 1;

	अगर (!kvm_apic_accept_pic_पूर्णांकr(v))
		वापस 0;

	अगर (irqchip_split(v->kvm))
		वापस pending_userspace_extपूर्णांक(v);
	अन्यथा
		वापस v->kvm->arch.vpic->output;
पूर्ण

/*
 * check अगर there is injectable पूर्णांकerrupt:
 * when भव पूर्णांकerrupt delivery enabled,
 * पूर्णांकerrupt from apic will handled by hardware,
 * we करोn't need to check it here.
 */
पूर्णांक kvm_cpu_has_injectable_पूर्णांकr(काष्ठा kvm_vcpu *v)
अणु
	अगर (kvm_cpu_has_extपूर्णांक(v))
		वापस 1;

	अगर (!is_guest_mode(v) && kvm_vcpu_apicv_active(v))
		वापस 0;

	वापस kvm_apic_has_पूर्णांकerrupt(v) != -1; /* LAPIC */
पूर्ण
EXPORT_SYMBOL_GPL(kvm_cpu_has_injectable_पूर्णांकr);

/*
 * check अगर there is pending पूर्णांकerrupt without
 * पूर्णांकack.
 */
पूर्णांक kvm_cpu_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *v)
अणु
	अगर (kvm_cpu_has_extपूर्णांक(v))
		वापस 1;

	वापस kvm_apic_has_पूर्णांकerrupt(v) != -1;	/* LAPIC */
पूर्ण
EXPORT_SYMBOL_GPL(kvm_cpu_has_पूर्णांकerrupt);

/*
 * Read pending पूर्णांकerrupt(from non-APIC source)
 * vector and पूर्णांकack.
 */
अटल पूर्णांक kvm_cpu_get_extपूर्णांक(काष्ठा kvm_vcpu *v)
अणु
	अगर (!kvm_cpu_has_extपूर्णांक(v)) अणु
		WARN_ON(!lapic_in_kernel(v));
		वापस -1;
	पूर्ण

	अगर (!lapic_in_kernel(v))
		वापस v->arch.पूर्णांकerrupt.nr;

	अगर (kvm_xen_has_पूर्णांकerrupt(v))
		वापस v->kvm->arch.xen.upcall_vector;

	अगर (irqchip_split(v->kvm)) अणु
		पूर्णांक vector = v->arch.pending_बाह्यal_vector;

		v->arch.pending_बाह्यal_vector = -1;
		वापस vector;
	पूर्ण अन्यथा
		वापस kvm_pic_पढ़ो_irq(v->kvm); /* PIC */
पूर्ण

/*
 * Read pending पूर्णांकerrupt vector and पूर्णांकack.
 */
पूर्णांक kvm_cpu_get_पूर्णांकerrupt(काष्ठा kvm_vcpu *v)
अणु
	पूर्णांक vector = kvm_cpu_get_extपूर्णांक(v);
	अगर (vector != -1)
		वापस vector;			/* PIC */

	वापस kvm_get_apic_पूर्णांकerrupt(v);	/* APIC */
पूर्ण
EXPORT_SYMBOL_GPL(kvm_cpu_get_पूर्णांकerrupt);

व्योम kvm_inject_pending_समयr_irqs(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (lapic_in_kernel(vcpu))
		kvm_inject_apic_समयr_irqs(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_inject_pending_समयr_irqs);

व्योम __kvm_migrate_समयrs(काष्ठा kvm_vcpu *vcpu)
अणु
	__kvm_migrate_apic_समयr(vcpu);
	__kvm_migrate_pit_समयr(vcpu);
	अटल_call_cond(kvm_x86_migrate_समयrs)(vcpu);
पूर्ण

bool kvm_arch_irqfd_allowed(काष्ठा kvm *kvm, काष्ठा kvm_irqfd *args)
अणु
	bool resample = args->flags & KVM_IRQFD_FLAG_RESAMPLE;

	वापस resample ? irqchip_kernel(kvm) : irqchip_in_kernel(kvm);
पूर्ण
