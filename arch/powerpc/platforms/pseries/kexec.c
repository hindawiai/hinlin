<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright 2006 Michael Ellerman, IBM Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/plpar_wrappers.h>

#समावेश "pseries.h"

व्योम pseries_kexec_cpu_करोwn(पूर्णांक crash_shutकरोwn, पूर्णांक secondary)
अणु
	/*
	 * Don't risk a hypervisor call if we're crashing
	 * XXX: Why? The hypervisor is not crashing. It might be better
	 * to at least attempt unरेजिस्टर to aव्योम the hypervisor stepping
	 * on our memory.
	 */
	अगर (firmware_has_feature(FW_FEATURE_SPLPAR) && !crash_shutकरोwn) अणु
		पूर्णांक ret;
		पूर्णांक cpu = smp_processor_id();
		पूर्णांक hwcpu = hard_smp_processor_id();

		अगर (get_lppaca()->dtl_enable_mask) अणु
			ret = unरेजिस्टर_dtl(hwcpu);
			अगर (ret) अणु
				pr_err("WARNING: DTL deregistration for cpu "
				       "%d (hw %d) failed with %d\n",
				       cpu, hwcpu, ret);
			पूर्ण
		पूर्ण

		ret = unरेजिस्टर_slb_shaकरोw(hwcpu);
		अगर (ret) अणु
			pr_err("WARNING: SLB shadow buffer deregistration "
			       "for cpu %d (hw %d) failed with %d\n",
			       cpu, hwcpu, ret);
		पूर्ण

		ret = unरेजिस्टर_vpa(hwcpu);
		अगर (ret) अणु
			pr_err("WARNING: VPA deregistration for cpu %d "
			       "(hw %d) failed with %d\n", cpu, hwcpu, ret);
		पूर्ण
	पूर्ण

	अगर (xive_enabled()) अणु
		xive_tearकरोwn_cpu();

		अगर (!secondary)
			xive_shutकरोwn();
	पूर्ण अन्यथा
		xics_kexec_tearकरोwn_cpu(secondary);
पूर्ण
