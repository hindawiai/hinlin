<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  KVM paraभव घड़ी driver. A घड़ीsource implementation
    Copyright (C) 2008 Glauber de Oliveira Costa, Red Hat Inc.
*/

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/kvm_para.h>
#समावेश <यंत्र/pvघड़ी.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/apic.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/set_memory.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mem_encrypt.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/kvmघड़ी.h>

अटल पूर्णांक kvmघड़ी __initdata = 1;
अटल पूर्णांक kvmघड़ी_vsyscall __initdata = 1;
अटल पूर्णांक msr_kvm_प्रणाली_समय __ro_after_init = MSR_KVM_SYSTEM_TIME;
अटल पूर्णांक msr_kvm_wall_घड़ी __ro_after_init = MSR_KVM_WALL_CLOCK;
अटल u64 kvm_sched_घड़ी_offset __ro_after_init;

अटल पूर्णांक __init parse_no_kvmघड़ी(अक्षर *arg)
अणु
	kvmघड़ी = 0;
	वापस 0;
पूर्ण
early_param("no-kvmclock", parse_no_kvmघड़ी);

अटल पूर्णांक __init parse_no_kvmघड़ी_vsyscall(अक्षर *arg)
अणु
	kvmघड़ी_vsyscall = 0;
	वापस 0;
पूर्ण
early_param("no-kvmclock-vsyscall", parse_no_kvmघड़ी_vsyscall);

/* Aligned to page sizes to match whats mapped via vsyscalls to userspace */
#घोषणा HVC_BOOT_ARRAY_SIZE \
	(PAGE_SIZE / माप(काष्ठा pvघड़ी_vsyscall_समय_info))

अटल काष्ठा pvघड़ी_vsyscall_समय_info
			hv_घड़ी_boot[HVC_BOOT_ARRAY_SIZE] __bss_decrypted __aligned(PAGE_SIZE);
अटल काष्ठा pvघड़ी_wall_घड़ी wall_घड़ी __bss_decrypted;
अटल DEFINE_PER_CPU(काष्ठा pvघड़ी_vsyscall_समय_info *, hv_घड़ी_per_cpu);
अटल काष्ठा pvघड़ी_vsyscall_समय_info *hvघड़ी_mem;

अटल अंतरभूत काष्ठा pvघड़ी_vcpu_समय_info *this_cpu_pvti(व्योम)
अणु
	वापस &this_cpu_पढ़ो(hv_घड़ी_per_cpu)->pvti;
पूर्ण

अटल अंतरभूत काष्ठा pvघड़ी_vsyscall_समय_info *this_cpu_hvघड़ी(व्योम)
अणु
	वापस this_cpu_पढ़ो(hv_घड़ी_per_cpu);
पूर्ण

/*
 * The wallघड़ी is the समय of day when we booted. Since then, some समय may
 * have elapsed since the hypervisor wrote the data. So we try to account क्रम
 * that with प्रणाली समय
 */
अटल व्योम kvm_get_wallघड़ी(काष्ठा बारpec64 *now)
अणु
	wrmsrl(msr_kvm_wall_घड़ी, slow_virt_to_phys(&wall_घड़ी));
	preempt_disable();
	pvघड़ी_पढ़ो_wallघड़ी(&wall_घड़ी, this_cpu_pvti(), now);
	preempt_enable();
पूर्ण

अटल पूर्णांक kvm_set_wallघड़ी(स्थिर काष्ठा बारpec64 *now)
अणु
	वापस -ENODEV;
पूर्ण

अटल u64 kvm_घड़ी_पढ़ो(व्योम)
अणु
	u64 ret;

	preempt_disable_notrace();
	ret = pvघड़ी_घड़ीsource_पढ़ो(this_cpu_pvti());
	preempt_enable_notrace();
	वापस ret;
पूर्ण

अटल u64 kvm_घड़ी_get_cycles(काष्ठा घड़ीsource *cs)
अणु
	वापस kvm_घड़ी_पढ़ो();
पूर्ण

अटल u64 kvm_sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस kvm_घड़ी_पढ़ो() - kvm_sched_घड़ी_offset;
पूर्ण

अटल अंतरभूत व्योम kvm_sched_घड़ी_init(bool stable)
अणु
	अगर (!stable)
		clear_sched_घड़ी_stable();
	kvm_sched_घड़ी_offset = kvm_घड़ी_पढ़ो();
	paravirt_set_sched_घड़ी(kvm_sched_घड़ी_पढ़ो);

	pr_info("kvm-clock: using sched offset of %llu cycles",
		kvm_sched_घड़ी_offset);

	BUILD_BUG_ON(माप(kvm_sched_घड़ी_offset) >
		माप(((काष्ठा pvघड़ी_vcpu_समय_info *)शून्य)->प्रणाली_समय));
पूर्ण

/*
 * If we करोn't करो that, there is the possibility that the guest
 * will calibrate under heavy load - thus, getting a lower lpj -
 * and execute the delays themselves without load. This is wrong,
 * because no delay loop can finish beक्रमehand.
 * Any heuristics is subject to fail, because ultimately, a large
 * poll of guests can be running and trouble each other. So we preset
 * lpj here
 */
अटल अचिन्हित दीर्घ kvm_get_tsc_khz(व्योम)
अणु
	setup_क्रमce_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);
	वापस pvघड़ी_प्रकारsc_khz(this_cpu_pvti());
पूर्ण

अटल व्योम __init kvm_get_preset_lpj(व्योम)
अणु
	अचिन्हित दीर्घ khz;
	u64 lpj;

	khz = kvm_get_tsc_khz();

	lpj = ((u64)khz * 1000);
	करो_भाग(lpj, HZ);
	preset_lpj = lpj;
पूर्ण

bool kvm_check_and_clear_guest_छोड़ोd(व्योम)
अणु
	काष्ठा pvघड़ी_vsyscall_समय_info *src = this_cpu_hvघड़ी();
	bool ret = false;

	अगर (!src)
		वापस ret;

	अगर ((src->pvti.flags & PVCLOCK_GUEST_STOPPED) != 0) अणु
		src->pvti.flags &= ~PVCLOCK_GUEST_STOPPED;
		pvघड़ी_प्रकारouch_watchकरोgs();
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_cs_enable(काष्ठा घड़ीsource *cs)
अणु
	vघड़ीs_set_used(VDSO_CLOCKMODE_PVCLOCK);
	वापस 0;
पूर्ण

काष्ठा घड़ीsource kvm_घड़ी = अणु
	.name	= "kvm-clock",
	.पढ़ो	= kvm_घड़ी_get_cycles,
	.rating	= 400,
	.mask	= CLOCKSOURCE_MASK(64),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
	.enable	= kvm_cs_enable,
पूर्ण;
EXPORT_SYMBOL_GPL(kvm_घड़ी);

अटल व्योम kvm_रेजिस्टर_घड़ी(अक्षर *txt)
अणु
	काष्ठा pvघड़ी_vsyscall_समय_info *src = this_cpu_hvघड़ी();
	u64 pa;

	अगर (!src)
		वापस;

	pa = slow_virt_to_phys(&src->pvti) | 0x01ULL;
	wrmsrl(msr_kvm_प्रणाली_समय, pa);
	pr_info("kvm-clock: cpu %d, msr %llx, %s", smp_processor_id(), pa, txt);
पूर्ण

अटल व्योम kvm_save_sched_घड़ी_state(व्योम)
अणु
पूर्ण

अटल व्योम kvm_restore_sched_घड़ी_state(व्योम)
अणु
	kvm_रेजिस्टर_घड़ी("primary cpu clock, resume");
पूर्ण

#अगर_घोषित CONFIG_X86_LOCAL_APIC
अटल व्योम kvm_setup_secondary_घड़ी(व्योम)
अणु
	kvm_रेजिस्टर_घड़ी("secondary cpu clock");
पूर्ण
#पूर्ण_अगर

व्योम kvmघड़ी_disable(व्योम)
अणु
	native_ग_लिखो_msr(msr_kvm_प्रणाली_समय, 0, 0);
पूर्ण

अटल व्योम __init kvmघड़ी_init_mem(व्योम)
अणु
	अचिन्हित दीर्घ ncpus;
	अचिन्हित पूर्णांक order;
	काष्ठा page *p;
	पूर्णांक r;

	अगर (HVC_BOOT_ARRAY_SIZE >= num_possible_cpus())
		वापस;

	ncpus = num_possible_cpus() - HVC_BOOT_ARRAY_SIZE;
	order = get_order(ncpus * माप(*hvघड़ी_mem));

	p = alloc_pages(GFP_KERNEL, order);
	अगर (!p) अणु
		pr_warn("%s: failed to alloc %d pages", __func__, (1U << order));
		वापस;
	पूर्ण

	hvघड़ी_mem = page_address(p);

	/*
	 * hvघड़ी is shared between the guest and the hypervisor, must
	 * be mapped decrypted.
	 */
	अगर (sev_active()) अणु
		r = set_memory_decrypted((अचिन्हित दीर्घ) hvघड़ी_mem,
					 1UL << order);
		अगर (r) अणु
			__मुक्त_pages(p, order);
			hvघड़ी_mem = शून्य;
			pr_warn("kvmclock: set_memory_decrypted() failed. Disabling\n");
			वापस;
		पूर्ण
	पूर्ण

	स_रखो(hvघड़ी_mem, 0, PAGE_SIZE << order);
पूर्ण

अटल पूर्णांक __init kvm_setup_vsyscall_समयinfo(व्योम)
अणु
	kvmघड़ी_init_mem();

#अगर_घोषित CONFIG_X86_64
	अगर (per_cpu(hv_घड़ी_per_cpu, 0) && kvmघड़ी_vsyscall) अणु
		u8 flags;

		flags = pvघड़ी_पढ़ो_flags(&hv_घड़ी_boot[0].pvti);
		अगर (!(flags & PVCLOCK_TSC_STABLE_BIT))
			वापस 0;

		kvm_घड़ी.vdso_घड़ी_mode = VDSO_CLOCKMODE_PVCLOCK;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण
early_initcall(kvm_setup_vsyscall_समयinfo);

अटल पूर्णांक kvmघड़ी_setup_percpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा pvघड़ी_vsyscall_समय_info *p = per_cpu(hv_घड़ी_per_cpu, cpu);

	/*
	 * The per cpu area setup replicates CPU0 data to all cpu
	 * poपूर्णांकers. So carefully check. CPU0 has been set up in init
	 * alपढ़ोy.
	 */
	अगर (!cpu || (p && p != per_cpu(hv_घड़ी_per_cpu, 0)))
		वापस 0;

	/* Use the अटल page क्रम the first CPUs, allocate otherwise */
	अगर (cpu < HVC_BOOT_ARRAY_SIZE)
		p = &hv_घड़ी_boot[cpu];
	अन्यथा अगर (hvघड़ी_mem)
		p = hvघड़ी_mem + cpu - HVC_BOOT_ARRAY_SIZE;
	अन्यथा
		वापस -ENOMEM;

	per_cpu(hv_घड़ी_per_cpu, cpu) = p;
	वापस p ? 0 : -ENOMEM;
पूर्ण

व्योम __init kvmघड़ी_init(व्योम)
अणु
	u8 flags;

	अगर (!kvm_para_available() || !kvmघड़ी)
		वापस;

	अगर (kvm_para_has_feature(KVM_FEATURE_CLOCKSOURCE2)) अणु
		msr_kvm_प्रणाली_समय = MSR_KVM_SYSTEM_TIME_NEW;
		msr_kvm_wall_घड़ी = MSR_KVM_WALL_CLOCK_NEW;
	पूर्ण अन्यथा अगर (!kvm_para_has_feature(KVM_FEATURE_CLOCKSOURCE)) अणु
		वापस;
	पूर्ण

	अगर (cpuhp_setup_state(CPUHP_BP_PREPARE_DYN, "kvmclock:setup_percpu",
			      kvmघड़ी_setup_percpu, शून्य) < 0) अणु
		वापस;
	पूर्ण

	pr_info("kvm-clock: Using msrs %x and %x",
		msr_kvm_प्रणाली_समय, msr_kvm_wall_घड़ी);

	this_cpu_ग_लिखो(hv_घड़ी_per_cpu, &hv_घड़ी_boot[0]);
	kvm_रेजिस्टर_घड़ी("primary cpu clock");
	pvघड़ी_set_pvti_cpu0_va(hv_घड़ी_boot);

	अगर (kvm_para_has_feature(KVM_FEATURE_CLOCKSOURCE_STABLE_BIT))
		pvघड़ी_set_flags(PVCLOCK_TSC_STABLE_BIT);

	flags = pvघड़ी_पढ़ो_flags(&hv_घड़ी_boot[0].pvti);
	kvm_sched_घड़ी_init(flags & PVCLOCK_TSC_STABLE_BIT);

	x86_platक्रमm.calibrate_tsc = kvm_get_tsc_khz;
	x86_platक्रमm.calibrate_cpu = kvm_get_tsc_khz;
	x86_platक्रमm.get_wallघड़ी = kvm_get_wallघड़ी;
	x86_platक्रमm.set_wallघड़ी = kvm_set_wallघड़ी;
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	x86_cpuinit.early_percpu_घड़ी_init = kvm_setup_secondary_घड़ी;
#पूर्ण_अगर
	x86_platक्रमm.save_sched_घड़ी_state = kvm_save_sched_घड़ी_state;
	x86_platक्रमm.restore_sched_घड़ी_state = kvm_restore_sched_घड़ी_state;
	kvm_get_preset_lpj();

	/*
	 * X86_FEATURE_NONSTOP_TSC is TSC runs at स्थिरant rate
	 * with P/T states and करोes not stop in deep C-states.
	 *
	 * Invariant TSC exposed by host means kvmघड़ी is not necessary:
	 * can use TSC as घड़ीsource.
	 *
	 */
	अगर (boot_cpu_has(X86_FEATURE_CONSTANT_TSC) &&
	    boot_cpu_has(X86_FEATURE_NONSTOP_TSC) &&
	    !check_tsc_unstable())
		kvm_घड़ी.rating = 299;

	घड़ीsource_रेजिस्टर_hz(&kvm_घड़ी, NSEC_PER_SEC);
	pv_info.name = "KVM";
पूर्ण
