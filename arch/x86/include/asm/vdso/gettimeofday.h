<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Fast user context implementation of घड़ी_समय_लो, समय_लोofday, and समय.
 *
 * Copyright (C) 2019 ARM Limited.
 * Copyright 2006 Andi Kleen, SUSE Lअसल.
 * 32 Bit compat layer by Stefani Seibold <stefani@seibold.net>
 *  sponsored by Rohde & Schwarz GmbH & Co. KG Munich/Germany
 */
#अगर_अघोषित __ASM_VDSO_GETTIMखातापूर्णDAY_H
#घोषणा __ASM_VDSO_GETTIMखातापूर्णDAY_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <uapi/linux/समय.स>
#समावेश <यंत्र/vgtod.h>
#समावेश <यंत्र/vvar.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/pvघड़ी.h>
#समावेश <घड़ीsource/hyperv_समयr.h>

#घोषणा __vdso_data (VVAR(_vdso_data))
#घोषणा __समयns_vdso_data (TIMENS(_vdso_data))

#घोषणा VDSO_HAS_TIME 1

#घोषणा VDSO_HAS_CLOCK_GETRES 1

/*
 * Declare the memory-mapped vघड़ी data pages.  These come from hypervisors.
 * If we ever reपूर्णांकroduce something like direct access to an MMIO घड़ी like
 * the HPET again, it will go here as well.
 *
 * A load from any of these pages will segfault अगर the घड़ी in question is
 * disabled, so appropriate compiler barriers and checks need to be used
 * to prevent stray loads.
 *
 * These declarations MUST NOT be स्थिर.  The compiler will assume that
 * an बाह्य स्थिर variable has genuinely स्थिरant contents, and the
 * resulting code won't work, since the whole poपूर्णांक is that these pages
 * change over समय, possibly जबतक we're accessing them.
 */

#अगर_घोषित CONFIG_PARAVIRT_CLOCK
/*
 * This is the vCPU 0 pvघड़ी page.  We only use pvघड़ी from the vDSO
 * अगर the hypervisor tells us that all vCPUs can get valid data from the
 * vCPU 0 page.
 */
बाह्य काष्ठा pvघड़ी_vsyscall_समय_info pvघड़ी_page
	__attribute__((visibility("hidden")));
#पूर्ण_अगर

#अगर_घोषित CONFIG_HYPERV_TIMER
बाह्य काष्ठा ms_hyperv_tsc_page hvघड़ी_page
	__attribute__((visibility("hidden")));
#पूर्ण_अगर

#अगर_घोषित CONFIG_TIME_NS
अटल __always_अंतरभूत
स्थिर काष्ठा vdso_data *__arch_get_समयns_vdso_data(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस __समयns_vdso_data;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित BUILD_VDSO32

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	दीर्घ ret;

	यंत्र ("syscall" : "=a" (ret), "=m" (*_ts) :
	     "0" (__NR_घड़ी_समय_लो), "D" (_clkid), "S" (_ts) :
	     "rcx", "r11");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ समय_लोofday_fallback(काष्ठा __kernel_old_समयval *_tv,
			   काष्ठा समयzone *_tz)
अणु
	दीर्घ ret;

	यंत्र("syscall" : "=a" (ret) :
	    "0" (__NR_समय_लोofday), "D" (_tv), "S" (_tz) : "memory");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_getres_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	दीर्घ ret;

	यंत्र ("syscall" : "=a" (ret), "=m" (*_ts) :
	     "0" (__NR_घड़ी_getres), "D" (_clkid), "S" (_ts) :
	     "rcx", "r11");

	वापस ret;
पूर्ण

#अन्यथा

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	दीर्घ ret;

	यंत्र (
		"mov %%ebx, %%edx \n"
		"mov %[clock], %%ebx \n"
		"call __kernel_vsyscall \n"
		"mov %%edx, %%ebx \n"
		: "=a" (ret), "=m" (*_ts)
		: "0" (__NR_घड़ी_समय_लो64), [घड़ी] "g" (_clkid), "c" (_ts)
		: "edx");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_समय_लो32_fallback(घड़ीid_t _clkid, काष्ठा old_बारpec32 *_ts)
अणु
	दीर्घ ret;

	यंत्र (
		"mov %%ebx, %%edx \n"
		"mov %[clock], %%ebx \n"
		"call __kernel_vsyscall \n"
		"mov %%edx, %%ebx \n"
		: "=a" (ret), "=m" (*_ts)
		: "0" (__NR_घड़ी_समय_लो), [घड़ी] "g" (_clkid), "c" (_ts)
		: "edx");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ समय_लोofday_fallback(काष्ठा __kernel_old_समयval *_tv,
			   काष्ठा समयzone *_tz)
अणु
	दीर्घ ret;

	यंत्र(
		"mov %%ebx, %%edx \n"
		"mov %2, %%ebx \n"
		"call __kernel_vsyscall \n"
		"mov %%edx, %%ebx \n"
		: "=a" (ret)
		: "0" (__NR_समय_लोofday), "g" (_tv), "c" (_tz)
		: "memory", "edx");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत दीर्घ
घड़ी_getres_fallback(घड़ीid_t _clkid, काष्ठा __kernel_बारpec *_ts)
अणु
	दीर्घ ret;

	यंत्र (
		"mov %%ebx, %%edx \n"
		"mov %[clock], %%ebx \n"
		"call __kernel_vsyscall \n"
		"mov %%edx, %%ebx \n"
		: "=a" (ret), "=m" (*_ts)
		: "0" (__NR_घड़ी_getres_समय64), [घड़ी] "g" (_clkid), "c" (_ts)
		: "edx");

	वापस ret;
पूर्ण

अटल __always_अंतरभूत
दीर्घ घड़ी_getres32_fallback(घड़ीid_t _clkid, काष्ठा old_बारpec32 *_ts)
अणु
	दीर्घ ret;

	यंत्र (
		"mov %%ebx, %%edx \n"
		"mov %[clock], %%ebx \n"
		"call __kernel_vsyscall \n"
		"mov %%edx, %%ebx \n"
		: "=a" (ret), "=m" (*_ts)
		: "0" (__NR_घड़ी_getres), [घड़ी] "g" (_clkid), "c" (_ts)
		: "edx");

	वापस ret;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PARAVIRT_CLOCK
अटल u64 vपढ़ो_pvघड़ी(व्योम)
अणु
	स्थिर काष्ठा pvघड़ी_vcpu_समय_info *pvti = &pvघड़ी_page.pvti;
	u32 version;
	u64 ret;

	/*
	 * Note: The kernel and hypervisor must guarantee that cpu ID
	 * number maps 1:1 to per-CPU pvघड़ी समय info.
	 *
	 * Because the hypervisor is entirely unaware of guest userspace
	 * preemption, it cannot guarantee that per-CPU pvघड़ी समय
	 * info is updated अगर the underlying CPU changes or that that
	 * version is increased whenever underlying CPU changes.
	 *
	 * On KVM, we are guaranteed that pvti updates क्रम any vCPU are
	 * atomic as seen by *all* vCPUs.  This is an even stronger
	 * guarantee than we get with a normal seqlock.
	 *
	 * On Xen, we करोn't appear to have that guarantee, but Xen still
	 * supplies a valid seqlock using the version field.
	 *
	 * We only करो pvघड़ी vdso timing at all अगर
	 * PVCLOCK_TSC_STABLE_BIT is set, and we पूर्णांकerpret that bit to
	 * mean that all vCPUs have matching pvti and that the TSC is
	 * synced, so we can just look at vCPU 0's pvti.
	 */

	करो अणु
		version = pvघड़ी_पढ़ो_begin(pvti);

		अगर (unlikely(!(pvti->flags & PVCLOCK_TSC_STABLE_BIT)))
			वापस U64_MAX;

		ret = __pvघड़ी_पढ़ो_cycles(pvti, rdtsc_ordered());
	पूर्ण जबतक (pvघड़ी_पढ़ो_retry(pvti, version));

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HYPERV_TIMER
अटल u64 vपढ़ो_hvघड़ी(व्योम)
अणु
	वापस hv_पढ़ो_tsc_page(&hvघड़ी_page);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u64 __arch_get_hw_counter(s32 घड़ी_mode,
					स्थिर काष्ठा vdso_data *vd)
अणु
	अगर (likely(घड़ी_mode == VDSO_CLOCKMODE_TSC))
		वापस (u64)rdtsc_ordered();
	/*
	 * For any memory-mapped vघड़ी type, we need to make sure that gcc
	 * करोesn't cleverly hoist a load beक्रमe the mode check.  Otherwise we
	 * might end up touching the memory-mapped page even अगर the vघड़ी in
	 * question isn't enabled, which will segfault.  Hence the barriers.
	 */
#अगर_घोषित CONFIG_PARAVIRT_CLOCK
	अगर (घड़ी_mode == VDSO_CLOCKMODE_PVCLOCK) अणु
		barrier();
		वापस vपढ़ो_pvघड़ी();
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_HYPERV_TIMER
	अगर (घड़ी_mode == VDSO_CLOCKMODE_HVCLOCK) अणु
		barrier();
		वापस vपढ़ो_hvघड़ी();
	पूर्ण
#पूर्ण_अगर
	वापस U64_MAX;
पूर्ण

अटल __always_अंतरभूत स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम)
अणु
	वापस __vdso_data;
पूर्ण

अटल अंतरभूत bool arch_vdso_घड़ीsource_ok(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस true;
पूर्ण
#घोषणा vdso_घड़ीsource_ok arch_vdso_घड़ीsource_ok

/*
 * Clocksource पढ़ो value validation to handle PV and HyperV घड़ीsources
 * which can be invalidated asynchronously and indicate invalidation by
 * वापसing U64_MAX, which can be effectively tested by checking क्रम a
 * negative value after casting it to s64.
 */
अटल अंतरभूत bool arch_vdso_cycles_ok(u64 cycles)
अणु
	वापस (s64)cycles >= 0;
पूर्ण
#घोषणा vdso_cycles_ok arch_vdso_cycles_ok

/*
 * x86 specअगरic delta calculation.
 *
 * The regular implementation assumes that घड़ीsource पढ़ोs are globally
 * monotonic. The TSC can be slightly off across sockets which can cause
 * the regular delta calculation (@cycles - @last) to वापस a huge समय
 * jump.
 *
 * Thereक्रमe it needs to be verअगरied that @cycles are greater than
 * @last. If not then use @last, which is the base समय of the current
 * conversion period.
 *
 * This variant also हटाओs the masking of the subtraction because the
 * घड़ीsource mask of all VDSO capable घड़ीsources on x86 is U64_MAX
 * which would result in a poपूर्णांकless operation. The compiler cannot
 * optimize it away as the mask comes from the vdso data and is not compile
 * समय स्थिरant.
 */
अटल __always_अंतरभूत
u64 vdso_calc_delta(u64 cycles, u64 last, u64 mask, u32 mult)
अणु
	अगर (cycles > last)
		वापस (cycles - last) * mult;
	वापस 0;
पूर्ण
#घोषणा vdso_calc_delta vdso_calc_delta

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_GETTIMखातापूर्णDAY_H */
