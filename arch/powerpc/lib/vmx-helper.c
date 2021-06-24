<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) IBM Corporation, 2011
 *
 * Authors: Sukadev Bhattiprolu <sukadev@linux.vnet.ibm.com>
 *          Anton Blanअक्षरd <anton@au.ibm.com>
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

पूर्णांक enter_vmx_usercopy(व्योम)
अणु
	अगर (in_पूर्णांकerrupt())
		वापस 0;

	preempt_disable();
	/*
	 * We need to disable page faults as they can call schedule and
	 * thus make us lose the VMX context. So on page faults, we just
	 * fail which will cause a fallback to the normal non-vmx copy.
	 */
	pagefault_disable();

	enable_kernel_altivec();

	वापस 1;
पूर्ण

/*
 * This function must वापस 0 because we tail call optimise when calling
 * from __copy_tofrom_user_घातer7 which वापसs 0 on success.
 */
पूर्णांक निकास_vmx_usercopy(व्योम)
अणु
	disable_kernel_altivec();
	pagefault_enable();
	preempt_enable();
	वापस 0;
पूर्ण

पूर्णांक enter_vmx_ops(व्योम)
अणु
	अगर (in_पूर्णांकerrupt())
		वापस 0;

	preempt_disable();

	enable_kernel_altivec();

	वापस 1;
पूर्ण

/*
 * All calls to this function will be optimised पूर्णांकo tail calls. We are
 * passed a poपूर्णांकer to the destination which we वापस as required by a
 * स_नकल implementation.
 */
व्योम *निकास_vmx_ops(व्योम *dest)
अणु
	disable_kernel_altivec();
	preempt_enable();
	वापस dest;
पूर्ण
