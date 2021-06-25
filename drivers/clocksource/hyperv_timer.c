<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Clocksource driver क्रम the synthetic counter and समयrs
 * provided by the Hyper-V hypervisor to guest VMs, as described
 * in the Hyper-V Top Level Functional Spec (TLFS). This driver
 * is inकाष्ठाion set architecture independent.
 *
 * Copyright (C) 2019, Microsoft, Inc.
 *
 * Author:  Michael Kelley <mikelley@microsoft.com>
 */

#समावेश <linux/percpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/acpi.h>
#समावेश <घड़ीsource/hyperv_समयr.h>
#समावेश <यंत्र/hyperv-tlfs.h>
#समावेश <यंत्र/mshyperv.h>

अटल काष्ठा घड़ी_event_device __percpu *hv_घड़ी_event;
अटल u64 hv_sched_घड़ी_offset __ro_after_init;

/*
 * If false, we're using the old mechanism क्रम sसमयr0 पूर्णांकerrupts
 * where it sends a VMbus message when it expires. The old
 * mechanism is used when running on older versions of Hyper-V
 * that करोn't support Direct Mode. While Hyper-V provides
 * four sसमयr's per CPU, Linux uses only sसमयr0.
 *
 * Because Direct Mode करोes not require processing a VMbus
 * message, sसमयr पूर्णांकerrupts can be enabled earlier in the
 * process of booting a CPU, and consistent with when समयr
 * पूर्णांकerrupts are enabled क्रम other घड़ीsource drivers.
 * However, क्रम legacy versions of Hyper-V when Direct Mode
 * is not enabled, setting up sसमयr पूर्णांकerrupts must be
 * delayed until VMbus is initialized and can process the
 * पूर्णांकerrupt message.
 */
अटल bool direct_mode_enabled;

अटल पूर्णांक sसमयr0_irq = -1;
अटल पूर्णांक sसमयr0_message_sपूर्णांक;
अटल DEFINE_PER_CPU(दीर्घ, sसमयr0_evt);

/*
 * Common code क्रम sसमयr0 पूर्णांकerrupts coming via Direct Mode or
 * as a VMbus message.
 */
व्योम hv_sसमयr0_isr(व्योम)
अणु
	काष्ठा घड़ी_event_device *ce;

	ce = this_cpu_ptr(hv_घड़ी_event);
	ce->event_handler(ce);
पूर्ण
EXPORT_SYMBOL_GPL(hv_sसमयr0_isr);

/*
 * sसमयr0 पूर्णांकerrupt handler क्रम architectures that support
 * per-cpu पूर्णांकerrupts, which also implies Direct Mode.
 */
अटल irqवापस_t hv_sसमयr0_percpu_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	hv_sसमयr0_isr();
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hv_ce_set_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *evt)
अणु
	u64 current_tick;

	current_tick = hv_पढ़ो_reference_counter();
	current_tick += delta;
	hv_set_रेजिस्टर(HV_REGISTER_STIMER0_COUNT, current_tick);
	वापस 0;
पूर्ण

अटल पूर्णांक hv_ce_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	hv_set_रेजिस्टर(HV_REGISTER_STIMER0_COUNT, 0);
	hv_set_रेजिस्टर(HV_REGISTER_STIMER0_CONFIG, 0);
	अगर (direct_mode_enabled && sसमयr0_irq >= 0)
		disable_percpu_irq(sसमयr0_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक hv_ce_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	जोड़ hv_sसमयr_config समयr_cfg;

	समयr_cfg.as_uपूर्णांक64 = 0;
	समयr_cfg.enable = 1;
	समयr_cfg.स्वतः_enable = 1;
	अगर (direct_mode_enabled) अणु
		/*
		 * When it expires, the समयr will directly पूर्णांकerrupt
		 * on the specअगरied hardware vector/IRQ.
		 */
		समयr_cfg.direct_mode = 1;
		समयr_cfg.apic_vector = HYPERV_STIMER0_VECTOR;
		अगर (sसमयr0_irq >= 0)
			enable_percpu_irq(sसमयr0_irq, IRQ_TYPE_NONE);
	पूर्ण अन्यथा अणु
		/*
		 * When it expires, the समयr will generate a VMbus message,
		 * to be handled by the normal VMbus पूर्णांकerrupt handler.
		 */
		समयr_cfg.direct_mode = 0;
		समयr_cfg.sपूर्णांकx = sसमयr0_message_sपूर्णांक;
	पूर्ण
	hv_set_रेजिस्टर(HV_REGISTER_STIMER0_CONFIG, समयr_cfg.as_uपूर्णांक64);
	वापस 0;
पूर्ण

/*
 * hv_sसमयr_init - Per-cpu initialization of the घड़ीevent
 */
अटल पूर्णांक hv_sसमयr_init(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *ce;

	अगर (!hv_घड़ी_event)
		वापस 0;

	ce = per_cpu_ptr(hv_घड़ी_event, cpu);
	ce->name = "Hyper-V clockevent";
	ce->features = CLOCK_EVT_FEAT_ONESHOT;
	ce->cpumask = cpumask_of(cpu);
	ce->rating = 1000;
	ce->set_state_shutकरोwn = hv_ce_shutकरोwn;
	ce->set_state_oneshot = hv_ce_set_oneshot;
	ce->set_next_event = hv_ce_set_next_event;

	घड़ीevents_config_and_रेजिस्टर(ce,
					HV_CLOCK_HZ,
					HV_MIN_DELTA_TICKS,
					HV_MAX_MAX_DELTA_TICKS);
	वापस 0;
पूर्ण

/*
 * hv_sसमयr_cleanup - Per-cpu cleanup of the घड़ीevent
 */
पूर्णांक hv_sसमयr_cleanup(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *ce;

	अगर (!hv_घड़ी_event)
		वापस 0;

	/*
	 * In the legacy हाल where Direct Mode is not enabled
	 * (which can only be on x86/64), sसमयr cleanup happens
	 * relatively early in the CPU offlining process. We
	 * must unbind the sसमयr-based घड़ीevent device so
	 * that the LAPIC समयr can take over until घड़ीevents
	 * are no दीर्घer needed in the offlining process. Note
	 * that घड़ीevents_unbind_device() eventually calls
	 * hv_ce_shutकरोwn().
	 *
	 * The unbind should not be करोne when Direct Mode is
	 * enabled because we may be on an architecture where
	 * there are no other घड़ीevent devices to fallback to.
	 */
	ce = per_cpu_ptr(hv_घड़ी_event, cpu);
	अगर (direct_mode_enabled)
		hv_ce_shutकरोwn(ce);
	अन्यथा
		घड़ीevents_unbind_device(ce, cpu);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hv_sसमयr_cleanup);

/*
 * These placeholders are overridden by arch specअगरic code on
 * architectures that need special setup of the sसमयr0 IRQ because
 * they करोn't support per-cpu IRQs (such as x86/x64).
 */
व्योम __weak hv_setup_sसमयr0_handler(व्योम (*handler)(व्योम))
अणु
पूर्ण;

व्योम __weak hv_हटाओ_sसमयr0_handler(व्योम)
अणु
पूर्ण;

/* Called only on architectures with per-cpu IRQs (i.e., not x86/x64) */
अटल पूर्णांक hv_setup_sसमयr0_irq(व्योम)
अणु
	पूर्णांक ret;

	ret = acpi_रेजिस्टर_gsi(शून्य, HYPERV_STIMER0_VECTOR,
			ACPI_EDGE_SENSITIVE, ACPI_ACTIVE_HIGH);
	अगर (ret < 0) अणु
		pr_err("Can't register Hyper-V stimer0 GSI. Error %d", ret);
		वापस ret;
	पूर्ण
	sसमयr0_irq = ret;

	ret = request_percpu_irq(sसमयr0_irq, hv_sसमयr0_percpu_isr,
		"Hyper-V stimer0", &sसमयr0_evt);
	अगर (ret) अणु
		pr_err("Can't request Hyper-V stimer0 IRQ %d. Error %d",
			sसमयr0_irq, ret);
		acpi_unरेजिस्टर_gsi(sसमयr0_irq);
		sसमयr0_irq = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम hv_हटाओ_sसमयr0_irq(व्योम)
अणु
	अगर (sसमयr0_irq == -1) अणु
		hv_हटाओ_sसमयr0_handler();
	पूर्ण अन्यथा अणु
		मुक्त_percpu_irq(sसमयr0_irq, &sसमयr0_evt);
		acpi_unरेजिस्टर_gsi(sसमयr0_irq);
		sसमयr0_irq = -1;
	पूर्ण
पूर्ण

/* hv_sसमयr_alloc - Global initialization of the घड़ीevent and sसमयr0 */
पूर्णांक hv_sसमयr_alloc(bool have_percpu_irqs)
अणु
	पूर्णांक ret;

	/*
	 * Synthetic समयrs are always available except on old versions of
	 * Hyper-V on x86.  In that हाल, वापस as error as Linux will use a
	 * घड़ीevent based on emulated LAPIC समयr hardware.
	 */
	अगर (!(ms_hyperv.features & HV_MSR_SYNTIMER_AVAILABLE))
		वापस -EINVAL;

	hv_घड़ी_event = alloc_percpu(काष्ठा घड़ी_event_device);
	अगर (!hv_घड़ी_event)
		वापस -ENOMEM;

	direct_mode_enabled = ms_hyperv.misc_features &
			HV_STIMER_सूचीECT_MODE_AVAILABLE;

	/*
	 * If Direct Mode isn't enabled, the reमुख्यder of the initialization
	 * is करोne later by hv_sसमयr_legacy_init()
	 */
	अगर (!direct_mode_enabled)
		वापस 0;

	अगर (have_percpu_irqs) अणु
		ret = hv_setup_sसमयr0_irq();
		अगर (ret)
			जाओ मुक्त_घड़ी_event;
	पूर्ण अन्यथा अणु
		hv_setup_sसमयr0_handler(hv_sसमयr0_isr);
	पूर्ण

	/*
	 * Since we are in Direct Mode, sसमयr initialization
	 * can be करोne now with a CPUHP value in the same range
	 * as other घड़ीevent devices.
	 */
	ret = cpuhp_setup_state(CPUHP_AP_HYPERV_TIMER_STARTING,
			"clockevents/hyperv/stimer:starting",
			hv_sसमयr_init, hv_sसमयr_cleanup);
	अगर (ret < 0) अणु
		hv_हटाओ_sसमयr0_irq();
		जाओ मुक्त_घड़ी_event;
	पूर्ण
	वापस ret;

मुक्त_घड़ी_event:
	मुक्त_percpu(hv_घड़ी_event);
	hv_घड़ी_event = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hv_sसमयr_alloc);

/*
 * hv_sसमयr_legacy_init -- Called from the VMbus driver to handle
 * the हाल when Direct Mode is not enabled, and the sसमयr
 * must be initialized late in the CPU onlining process.
 *
 */
व्योम hv_sसमयr_legacy_init(अचिन्हित पूर्णांक cpu, पूर्णांक sपूर्णांक)
अणु
	अगर (direct_mode_enabled)
		वापस;

	/*
	 * This function माला_लो called by each vCPU, so setting the
	 * global sसमयr_message_sपूर्णांक value each समय is conceptually
	 * not ideal, but the value passed in is always the same and
	 * it aव्योमs पूर्णांकroducing yet another पूर्णांकerface पूर्णांकo this
	 * घड़ीsource driver just to set the sपूर्णांक in the legacy हाल.
	 */
	sसमयr0_message_sपूर्णांक = sपूर्णांक;
	(व्योम)hv_sसमयr_init(cpu);
पूर्ण
EXPORT_SYMBOL_GPL(hv_sसमयr_legacy_init);

/*
 * hv_sसमयr_legacy_cleanup -- Called from the VMbus driver to
 * handle the हाल when Direct Mode is not enabled, and the
 * sसमयr must be cleaned up early in the CPU offlining
 * process.
 */
व्योम hv_sसमयr_legacy_cleanup(अचिन्हित पूर्णांक cpu)
अणु
	अगर (direct_mode_enabled)
		वापस;
	(व्योम)hv_sसमयr_cleanup(cpu);
पूर्ण
EXPORT_SYMBOL_GPL(hv_sसमयr_legacy_cleanup);

/*
 * Do a global cleanup of घड़ीevents क्रम the हालs of kexec and
 * vmbus निकास
 */
व्योम hv_sसमयr_global_cleanup(व्योम)
अणु
	पूर्णांक	cpu;

	/*
	 * hv_sसमय_legacy_cleanup() will stop the sसमयr अगर Direct
	 * Mode is not enabled, and fallback to the LAPIC समयr.
	 */
	क्रम_each_present_cpu(cpu) अणु
		hv_sसमयr_legacy_cleanup(cpu);
	पूर्ण

	अगर (!hv_घड़ी_event)
		वापस;

	अगर (direct_mode_enabled) अणु
		cpuhp_हटाओ_state(CPUHP_AP_HYPERV_TIMER_STARTING);
		hv_हटाओ_sसमयr0_irq();
		sसमयr0_irq = -1;
	पूर्ण
	मुक्त_percpu(hv_घड़ी_event);
	hv_घड़ी_event = शून्य;

पूर्ण
EXPORT_SYMBOL_GPL(hv_sसमयr_global_cleanup);

/*
 * Code and definitions क्रम the Hyper-V घड़ीsources.  Two
 * घड़ीsources are defined: one that पढ़ोs the Hyper-V defined MSR, and
 * the other that uses the TSC reference page feature as defined in the
 * TLFS.  The MSR version is क्रम compatibility with old versions of
 * Hyper-V and 32-bit x86.  The TSC reference page version is preferred.
 */

u64 (*hv_पढ़ो_reference_counter)(व्योम);
EXPORT_SYMBOL_GPL(hv_पढ़ो_reference_counter);

अटल जोड़ अणु
	काष्ठा ms_hyperv_tsc_page page;
	u8 reserved[PAGE_SIZE];
पूर्ण tsc_pg __aligned(PAGE_SIZE);

काष्ठा ms_hyperv_tsc_page *hv_get_tsc_page(व्योम)
अणु
	वापस &tsc_pg.page;
पूर्ण
EXPORT_SYMBOL_GPL(hv_get_tsc_page);

अटल u64 notrace पढ़ो_hv_घड़ी_प्रकारsc(व्योम)
अणु
	u64 current_tick = hv_पढ़ो_tsc_page(hv_get_tsc_page());

	अगर (current_tick == U64_MAX)
		current_tick = hv_get_रेजिस्टर(HV_REGISTER_TIME_REF_COUNT);

	वापस current_tick;
पूर्ण

अटल u64 notrace पढ़ो_hv_घड़ी_प्रकारsc_cs(काष्ठा घड़ीsource *arg)
अणु
	वापस पढ़ो_hv_घड़ी_प्रकारsc();
पूर्ण

अटल u64 notrace पढ़ो_hv_sched_घड़ी_प्रकारsc(व्योम)
अणु
	वापस (पढ़ो_hv_घड़ी_प्रकारsc() - hv_sched_घड़ी_offset) *
		(NSEC_PER_SEC / HV_CLOCK_HZ);
पूर्ण

अटल व्योम suspend_hv_घड़ी_प्रकारsc(काष्ठा घड़ीsource *arg)
अणु
	u64 tsc_msr;

	/* Disable the TSC page */
	tsc_msr = hv_get_रेजिस्टर(HV_REGISTER_REFERENCE_TSC);
	tsc_msr &= ~BIT_ULL(0);
	hv_set_रेजिस्टर(HV_REGISTER_REFERENCE_TSC, tsc_msr);
पूर्ण


अटल व्योम resume_hv_घड़ी_प्रकारsc(काष्ठा घड़ीsource *arg)
अणु
	phys_addr_t phys_addr = virt_to_phys(&tsc_pg);
	u64 tsc_msr;

	/* Re-enable the TSC page */
	tsc_msr = hv_get_रेजिस्टर(HV_REGISTER_REFERENCE_TSC);
	tsc_msr &= GENMASK_ULL(11, 0);
	tsc_msr |= BIT_ULL(0) | (u64)phys_addr;
	hv_set_रेजिस्टर(HV_REGISTER_REFERENCE_TSC, tsc_msr);
पूर्ण

#अगर_घोषित HAVE_VDSO_CLOCKMODE_HVCLOCK
अटल पूर्णांक hv_cs_enable(काष्ठा घड़ीsource *cs)
अणु
	vघड़ीs_set_used(VDSO_CLOCKMODE_HVCLOCK);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा घड़ीsource hyperv_cs_tsc = अणु
	.name	= "hyperv_clocksource_tsc_page",
	.rating	= 500,
	.पढ़ो	= पढ़ो_hv_घड़ी_प्रकारsc_cs,
	.mask	= CLOCKSOURCE_MASK(64),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
	.suspend= suspend_hv_घड़ी_प्रकारsc,
	.resume	= resume_hv_घड़ी_प्रकारsc,
#अगर_घोषित HAVE_VDSO_CLOCKMODE_HVCLOCK
	.enable = hv_cs_enable,
	.vdso_घड़ी_mode = VDSO_CLOCKMODE_HVCLOCK,
#अन्यथा
	.vdso_घड़ी_mode = VDSO_CLOCKMODE_NONE,
#पूर्ण_अगर
पूर्ण;

अटल u64 notrace पढ़ो_hv_घड़ी_msr(व्योम)
अणु
	/*
	 * Read the partition counter to get the current tick count. This count
	 * is set to 0 when the partition is created and is incremented in
	 * 100 nanosecond units.
	 */
	वापस hv_get_रेजिस्टर(HV_REGISTER_TIME_REF_COUNT);
पूर्ण

अटल u64 notrace पढ़ो_hv_घड़ी_msr_cs(काष्ठा घड़ीsource *arg)
अणु
	वापस पढ़ो_hv_घड़ी_msr();
पूर्ण

अटल u64 notrace पढ़ो_hv_sched_घड़ी_msr(व्योम)
अणु
	वापस (पढ़ो_hv_घड़ी_msr() - hv_sched_घड़ी_offset) *
		(NSEC_PER_SEC / HV_CLOCK_HZ);
पूर्ण

अटल काष्ठा घड़ीsource hyperv_cs_msr = अणु
	.name	= "hyperv_clocksource_msr",
	.rating	= 500,
	.पढ़ो	= पढ़ो_hv_घड़ी_msr_cs,
	.mask	= CLOCKSOURCE_MASK(64),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

/*
 * Reference to pv_ops must be अंतरभूत so objtool
 * detection of noinstr violations can work correctly.
 */
#अगर_घोषित CONFIG_GENERIC_SCHED_CLOCK
अटल __always_अंतरभूत व्योम hv_setup_sched_घड़ी(व्योम *sched_घड़ी)
अणु
	/*
	 * We're on an architecture with generic sched घड़ी (not x86/x64).
	 * The Hyper-V sched घड़ी पढ़ो function वापसs nanoseconds, not
	 * the normal 100ns units of the Hyper-V synthetic घड़ी.
	 */
	sched_घड़ी_रेजिस्टर(sched_घड़ी, 64, NSEC_PER_SEC);
पूर्ण
#या_अगर defined CONFIG_PARAVIRT
अटल __always_अंतरभूत व्योम hv_setup_sched_घड़ी(व्योम *sched_घड़ी)
अणु
	/* We're on x86/x64 *and* using PV ops */
	paravirt_set_sched_घड़ी(sched_घड़ी);
पूर्ण
#अन्यथा /* !CONFIG_GENERIC_SCHED_CLOCK && !CONFIG_PARAVIRT */
अटल __always_अंतरभूत व्योम hv_setup_sched_घड़ी(व्योम *sched_घड़ी) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_SCHED_CLOCK */

अटल bool __init hv_init_tsc_घड़ीsource(व्योम)
अणु
	u64		tsc_msr;
	phys_addr_t	phys_addr;

	अगर (!(ms_hyperv.features & HV_MSR_REFERENCE_TSC_AVAILABLE))
		वापस false;

	अगर (hv_root_partition)
		वापस false;

	/*
	 * If Hyper-V offers TSC_INVARIANT, then the भवized TSC correctly
	 * handles frequency and offset changes due to live migration,
	 * छोड़ो/resume, and other VM management operations.  So lower the
	 * Hyper-V Reference TSC rating, causing the generic TSC to be used.
	 * TSC_INVARIANT is not offered on ARM64, so the Hyper-V Reference
	 * TSC will be preferred over the भवized ARM64 arch counter.
	 * While the Hyper-V MSR घड़ीsource won't be used since the
	 * Reference TSC घड़ीsource is present, change its rating as
	 * well क्रम consistency.
	 */
	अगर (ms_hyperv.features & HV_ACCESS_TSC_INVARIANT) अणु
		hyperv_cs_tsc.rating = 250;
		hyperv_cs_msr.rating = 250;
	पूर्ण

	hv_पढ़ो_reference_counter = पढ़ो_hv_घड़ी_प्रकारsc;
	phys_addr = virt_to_phys(hv_get_tsc_page());

	/*
	 * The Hyper-V TLFS specअगरies to preserve the value of reserved
	 * bits in रेजिस्टरs. So पढ़ो the existing value, preserve the
	 * low order 12 bits, and add in the guest physical address
	 * (which alपढ़ोy has at least the low 12 bits set to zero since
	 * it is page aligned). Also set the "enable" bit, which is bit 0.
	 */
	tsc_msr = hv_get_रेजिस्टर(HV_REGISTER_REFERENCE_TSC);
	tsc_msr &= GENMASK_ULL(11, 0);
	tsc_msr = tsc_msr | 0x1 | (u64)phys_addr;
	hv_set_रेजिस्टर(HV_REGISTER_REFERENCE_TSC, tsc_msr);

	घड़ीsource_रेजिस्टर_hz(&hyperv_cs_tsc, NSEC_PER_SEC/100);

	hv_sched_घड़ी_offset = hv_पढ़ो_reference_counter();
	hv_setup_sched_घड़ी(पढ़ो_hv_sched_घड़ी_प्रकारsc);

	वापस true;
पूर्ण

व्योम __init hv_init_घड़ीsource(व्योम)
अणु
	/*
	 * Try to set up the TSC page घड़ीsource. If it succeeds, we're
	 * करोne. Otherwise, set up the MSR घड़ीsource.  At least one of
	 * these will always be available except on very old versions of
	 * Hyper-V on x86.  In that हाल we won't have a Hyper-V
	 * घड़ीsource, but Linux will still run with a घड़ीsource based
	 * on the emulated PIT or LAPIC समयr.
	 */
	अगर (hv_init_tsc_घड़ीsource())
		वापस;

	अगर (!(ms_hyperv.features & HV_MSR_TIME_REF_COUNT_AVAILABLE))
		वापस;

	hv_पढ़ो_reference_counter = पढ़ो_hv_घड़ी_msr;
	घड़ीsource_रेजिस्टर_hz(&hyperv_cs_msr, NSEC_PER_SEC/100);

	hv_sched_घड़ी_offset = hv_पढ़ो_reference_counter();
	hv_setup_sched_घड़ी(पढ़ो_hv_sched_घड़ी_msr);
पूर्ण
EXPORT_SYMBOL_GPL(hv_init_घड़ीsource);
