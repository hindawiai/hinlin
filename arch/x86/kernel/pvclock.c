<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  paraभव घड़ी -- common code used by kvm/xen

*/

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/sched.h>
#समावेश <linux/gfp.h>
#समावेश <linux/memblock.h>
#समावेश <linux/nmi.h>

#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/pvघड़ी.h>
#समावेश <यंत्र/vgtod.h>

अटल u8 valid_flags __पढ़ो_mostly = 0;
अटल काष्ठा pvघड़ी_vsyscall_समय_info *pvti_cpu0_va __पढ़ो_mostly;

व्योम pvघड़ी_set_flags(u8 flags)
अणु
	valid_flags = flags;
पूर्ण

अचिन्हित दीर्घ pvघड़ी_प्रकारsc_khz(काष्ठा pvघड़ी_vcpu_समय_info *src)
अणु
	u64 pv_tsc_khz = 1000000ULL << 32;

	करो_भाग(pv_tsc_khz, src->tsc_to_प्रणाली_mul);
	अगर (src->tsc_shअगरt < 0)
		pv_tsc_khz <<= -src->tsc_shअगरt;
	अन्यथा
		pv_tsc_khz >>= src->tsc_shअगरt;
	वापस pv_tsc_khz;
पूर्ण

व्योम pvघड़ी_प्रकारouch_watchकरोgs(व्योम)
अणु
	touch_softlockup_watchकरोg_sync();
	घड़ीsource_touch_watchकरोg();
	rcu_cpu_stall_reset();
	reset_hung_task_detector();
पूर्ण

अटल atomic64_t last_value = ATOMIC64_INIT(0);

व्योम pvघड़ी_resume(व्योम)
अणु
	atomic64_set(&last_value, 0);
पूर्ण

u8 pvघड़ी_पढ़ो_flags(काष्ठा pvघड़ी_vcpu_समय_info *src)
अणु
	अचिन्हित version;
	u8 flags;

	करो अणु
		version = pvघड़ी_पढ़ो_begin(src);
		flags = src->flags;
	पूर्ण जबतक (pvघड़ी_पढ़ो_retry(src, version));

	वापस flags & valid_flags;
पूर्ण

u64 pvघड़ी_घड़ीsource_पढ़ो(काष्ठा pvघड़ी_vcpu_समय_info *src)
अणु
	अचिन्हित version;
	u64 ret;
	u64 last;
	u8 flags;

	करो अणु
		version = pvघड़ी_पढ़ो_begin(src);
		ret = __pvघड़ी_पढ़ो_cycles(src, rdtsc_ordered());
		flags = src->flags;
	पूर्ण जबतक (pvघड़ी_पढ़ो_retry(src, version));

	अगर (unlikely((flags & PVCLOCK_GUEST_STOPPED) != 0)) अणु
		src->flags &= ~PVCLOCK_GUEST_STOPPED;
		pvघड़ी_प्रकारouch_watchकरोgs();
	पूर्ण

	अगर ((valid_flags & PVCLOCK_TSC_STABLE_BIT) &&
		(flags & PVCLOCK_TSC_STABLE_BIT))
		वापस ret;

	/*
	 * Assumption here is that last_value, a global accumulator, always goes
	 * क्रमward. If we are less than that, we should not be much smaller.
	 * We assume there is an error margin we're inside, and then the correction
	 * करोes not sacrअगरice accuracy.
	 *
	 * For पढ़ोs: global may have changed between test and वापस,
	 * but this means someone अन्यथा updated poked the घड़ी at a later समय.
	 * We just need to make sure we are not seeing a backwards event.
	 *
	 * For updates: last_value = ret is not enough, since two vcpus could be
	 * updating at the same समय, and one of them could be slightly behind,
	 * making the assumption that last_value always go क्रमward fail to hold.
	 */
	last = atomic64_पढ़ो(&last_value);
	करो अणु
		अगर (ret < last)
			वापस last;
		last = atomic64_cmpxchg(&last_value, last, ret);
	पूर्ण जबतक (unlikely(last != ret));

	वापस ret;
पूर्ण

व्योम pvघड़ी_पढ़ो_wallघड़ी(काष्ठा pvघड़ी_wall_घड़ी *wall_घड़ी,
			    काष्ठा pvघड़ी_vcpu_समय_info *vcpu_समय,
			    काष्ठा बारpec64 *ts)
अणु
	u32 version;
	u64 delta;
	काष्ठा बारpec64 now;

	/* get wallघड़ी at प्रणाली boot */
	करो अणु
		version = wall_घड़ी->version;
		rmb();		/* fetch version beक्रमe समय */
		/*
		 * Note: wall_घड़ी->sec is a u32 value, so it can
		 * only store dates between 1970 and 2106. To allow
		 * बार beyond that, we need to create a new hypercall
		 * पूर्णांकerface with an extended pvघड़ी_wall_घड़ी काष्ठाure
		 * like ARM has.
		 */
		now.tv_sec  = wall_घड़ी->sec;
		now.tv_nsec = wall_घड़ी->nsec;
		rmb();		/* fetch समय beक्रमe checking version */
	पूर्ण जबतक ((wall_घड़ी->version & 1) || (version != wall_घड़ी->version));

	delta = pvघड़ी_घड़ीsource_पढ़ो(vcpu_समय);	/* समय since प्रणाली boot */
	delta += now.tv_sec * NSEC_PER_SEC + now.tv_nsec;

	now.tv_nsec = करो_भाग(delta, NSEC_PER_SEC);
	now.tv_sec = delta;

	set_normalized_बारpec64(ts, now.tv_sec, now.tv_nsec);
पूर्ण

व्योम pvघड़ी_set_pvti_cpu0_va(काष्ठा pvघड़ी_vsyscall_समय_info *pvti)
अणु
	WARN_ON(vघड़ी_was_used(VDSO_CLOCKMODE_PVCLOCK));
	pvti_cpu0_va = pvti;
पूर्ण

काष्ठा pvघड़ी_vsyscall_समय_info *pvघड़ी_get_pvti_cpu0_va(व्योम)
अणु
	वापस pvti_cpu0_va;
पूर्ण
EXPORT_SYMBOL_GPL(pvघड़ी_get_pvti_cpu0_va);
