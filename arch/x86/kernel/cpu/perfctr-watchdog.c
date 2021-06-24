<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * local apic based NMI watchकरोg क्रम various CPUs.
 *
 * This file also handles reservation of perक्रमmance counters क्रम coordination
 * with other users.
 *
 * Note that these events normally करोn't tick when the CPU idles. This means
 * the frequency varies with CPU load.
 *
 * Original code क्रम K7/P6 written by Keith Owens
 *
 */

#समावेश <linux/percpu.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/nmi.h>
#समावेश <linux/kprobes.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/perf_event.h>

/*
 * this number is calculated from Intel's MSR_P4_CRU_ESCR5 register and it's
 * offset from MSR_P4_BSU_ESCR0.
 *
 * It will be the max क्रम all platक्रमms (क्रम now)
 */
#घोषणा NMI_MAX_COUNTER_BITS 66

/*
 * perfctr_nmi_owner tracks the ownership of the perfctr रेजिस्टरs:
 * evtsel_nmi_owner tracks the ownership of the event selection
 * - dअगरferent perक्रमmance counters/ event selection may be reserved क्रम
 *   dअगरferent subप्रणालीs this reservation प्रणाली just tries to coordinate
 *   things a little
 */
अटल DECLARE_BITMAP(perfctr_nmi_owner, NMI_MAX_COUNTER_BITS);
अटल DECLARE_BITMAP(evntsel_nmi_owner, NMI_MAX_COUNTER_BITS);

/* converts an msr to an appropriate reservation bit */
अटल अंतरभूत अचिन्हित पूर्णांक nmi_perfctr_msr_to_bit(अचिन्हित पूर्णांक msr)
अणु
	/* वापसs the bit offset of the perक्रमmance counter रेजिस्टर */
	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_HYGON:
	हाल X86_VENDOR_AMD:
		अगर (msr >= MSR_F15H_PERF_CTR)
			वापस (msr - MSR_F15H_PERF_CTR) >> 1;
		वापस msr - MSR_K7_PERFCTR0;
	हाल X86_VENDOR_INTEL:
		अगर (cpu_has(&boot_cpu_data, X86_FEATURE_ARCH_PERFMON))
			वापस msr - MSR_ARCH_PERFMON_PERFCTR0;

		चयन (boot_cpu_data.x86) अणु
		हाल 6:
			वापस msr - MSR_P6_PERFCTR0;
		हाल 11:
			वापस msr - MSR_KNC_PERFCTR0;
		हाल 15:
			वापस msr - MSR_P4_BPU_PERFCTR0;
		पूर्ण
		अवरोध;
	हाल X86_VENDOR_ZHAOXIN:
	हाल X86_VENDOR_CENTAUR:
		वापस msr - MSR_ARCH_PERFMON_PERFCTR0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * converts an msr to an appropriate reservation bit
 * वापसs the bit offset of the event selection रेजिस्टर
 */
अटल अंतरभूत अचिन्हित पूर्णांक nmi_evntsel_msr_to_bit(अचिन्हित पूर्णांक msr)
अणु
	/* वापसs the bit offset of the event selection रेजिस्टर */
	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_HYGON:
	हाल X86_VENDOR_AMD:
		अगर (msr >= MSR_F15H_PERF_CTL)
			वापस (msr - MSR_F15H_PERF_CTL) >> 1;
		वापस msr - MSR_K7_EVNTSEL0;
	हाल X86_VENDOR_INTEL:
		अगर (cpu_has(&boot_cpu_data, X86_FEATURE_ARCH_PERFMON))
			वापस msr - MSR_ARCH_PERFMON_EVENTSEL0;

		चयन (boot_cpu_data.x86) अणु
		हाल 6:
			वापस msr - MSR_P6_EVNTSEL0;
		हाल 11:
			वापस msr - MSR_KNC_EVNTSEL0;
		हाल 15:
			वापस msr - MSR_P4_BSU_ESCR0;
		पूर्ण
		अवरोध;
	हाल X86_VENDOR_ZHAOXIN:
	हाल X86_VENDOR_CENTAUR:
		वापस msr - MSR_ARCH_PERFMON_EVENTSEL0;
	पूर्ण
	वापस 0;

पूर्ण

पूर्णांक reserve_perfctr_nmi(अचिन्हित पूर्णांक msr)
अणु
	अचिन्हित पूर्णांक counter;

	counter = nmi_perfctr_msr_to_bit(msr);
	/* रेजिस्टर not managed by the allocator? */
	अगर (counter > NMI_MAX_COUNTER_BITS)
		वापस 1;

	अगर (!test_and_set_bit(counter, perfctr_nmi_owner))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(reserve_perfctr_nmi);

व्योम release_perfctr_nmi(अचिन्हित पूर्णांक msr)
अणु
	अचिन्हित पूर्णांक counter;

	counter = nmi_perfctr_msr_to_bit(msr);
	/* रेजिस्टर not managed by the allocator? */
	अगर (counter > NMI_MAX_COUNTER_BITS)
		वापस;

	clear_bit(counter, perfctr_nmi_owner);
पूर्ण
EXPORT_SYMBOL(release_perfctr_nmi);

पूर्णांक reserve_evntsel_nmi(अचिन्हित पूर्णांक msr)
अणु
	अचिन्हित पूर्णांक counter;

	counter = nmi_evntsel_msr_to_bit(msr);
	/* रेजिस्टर not managed by the allocator? */
	अगर (counter > NMI_MAX_COUNTER_BITS)
		वापस 1;

	अगर (!test_and_set_bit(counter, evntsel_nmi_owner))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(reserve_evntsel_nmi);

व्योम release_evntsel_nmi(अचिन्हित पूर्णांक msr)
अणु
	अचिन्हित पूर्णांक counter;

	counter = nmi_evntsel_msr_to_bit(msr);
	/* रेजिस्टर not managed by the allocator? */
	अगर (counter > NMI_MAX_COUNTER_BITS)
		वापस;

	clear_bit(counter, evntsel_nmi_owner);
पूर्ण
EXPORT_SYMBOL(release_evntsel_nmi);
