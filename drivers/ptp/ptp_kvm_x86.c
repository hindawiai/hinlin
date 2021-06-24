<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtual PTP 1588 घड़ी क्रम use with KVM guests
 *
 * Copyright (C) 2017 Red Hat Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/pvघड़ी.h>
#समावेश <यंत्र/kvmघड़ी.h>
#समावेश <linux/module.h>
#समावेश <uapi/यंत्र/kvm_para.h>
#समावेश <uapi/linux/kvm_para.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/ptp_kvm.h>

काष्ठा pvघड़ी_vsyscall_समय_info *hv_घड़ी;

अटल phys_addr_t घड़ी_pair_gpa;
अटल काष्ठा kvm_घड़ी_pairing घड़ी_pair;

पूर्णांक kvm_arch_ptp_init(व्योम)
अणु
	दीर्घ ret;

	अगर (!kvm_para_available())
		वापस -ENODEV;

	घड़ी_pair_gpa = slow_virt_to_phys(&घड़ी_pair);
	hv_घड़ी = pvघड़ी_get_pvti_cpu0_va();
	अगर (!hv_घड़ी)
		वापस -ENODEV;

	ret = kvm_hypercall2(KVM_HC_CLOCK_PAIRING, घड़ी_pair_gpa,
			     KVM_CLOCK_PAIRING_WALLCLOCK);
	अगर (ret == -KVM_ENOSYS || ret == -KVM_EOPNOTSUPP)
		वापस -ENODEV;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_ptp_get_घड़ी(काष्ठा बारpec64 *ts)
अणु
	दीर्घ ret;

	ret = kvm_hypercall2(KVM_HC_CLOCK_PAIRING,
			     घड़ी_pair_gpa,
			     KVM_CLOCK_PAIRING_WALLCLOCK);
	अगर (ret != 0) अणु
		pr_err_ratelimited("clock offset hypercall ret %lu\n", ret);
		वापस -EOPNOTSUPP;
	पूर्ण

	ts->tv_sec = घड़ी_pair.sec;
	ts->tv_nsec = घड़ी_pair.nsec;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_ptp_get_crosststamp(u64 *cycle, काष्ठा बारpec64 *tspec,
			      काष्ठा घड़ीsource **cs)
अणु
	काष्ठा pvघड़ी_vcpu_समय_info *src;
	अचिन्हित पूर्णांक version;
	दीर्घ ret;
	पूर्णांक cpu;

	cpu = smp_processor_id();
	src = &hv_घड़ी[cpu].pvti;

	करो अणु
		/*
		 * We are using a TSC value पढ़ो in the hosts
		 * kvm_hc_घड़ी_pairing handling.
		 * So any changes to tsc_to_प्रणाली_mul
		 * and tsc_shअगरt or any other pvघड़ी
		 * data invalidate that measurement.
		 */
		version = pvघड़ी_पढ़ो_begin(src);

		ret = kvm_hypercall2(KVM_HC_CLOCK_PAIRING,
				     घड़ी_pair_gpa,
				     KVM_CLOCK_PAIRING_WALLCLOCK);
		अगर (ret != 0) अणु
			pr_err_ratelimited("clock pairing hypercall ret %lu\n", ret);
			वापस -EOPNOTSUPP;
		पूर्ण
		tspec->tv_sec = घड़ी_pair.sec;
		tspec->tv_nsec = घड़ी_pair.nsec;
		*cycle = __pvघड़ी_पढ़ो_cycles(src, घड़ी_pair.tsc);
	पूर्ण जबतक (pvघड़ी_पढ़ो_retry(src, version));

	*cs = &kvm_घड़ी;

	वापस 0;
पूर्ण
