<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Altivec XOR operations
 *
 * Copyright 2017 IBM Corp.
 */

#समावेश <linux/preempt.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/xor_altivec.h>
#समावेश "xor_vmx.h"

व्योम xor_altivec_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
		   अचिन्हित दीर्घ *v2_in)
अणु
	preempt_disable();
	enable_kernel_altivec();
	__xor_altivec_2(bytes, v1_in, v2_in);
	disable_kernel_altivec();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(xor_altivec_2);

व्योम xor_altivec_3(अचिन्हित दीर्घ bytes,  अचिन्हित दीर्घ *v1_in,
		   अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in)
अणु
	preempt_disable();
	enable_kernel_altivec();
	__xor_altivec_3(bytes, v1_in, v2_in, v3_in);
	disable_kernel_altivec();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(xor_altivec_3);

व्योम xor_altivec_4(अचिन्हित दीर्घ bytes,  अचिन्हित दीर्घ *v1_in,
		   अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in,
		   अचिन्हित दीर्घ *v4_in)
अणु
	preempt_disable();
	enable_kernel_altivec();
	__xor_altivec_4(bytes, v1_in, v2_in, v3_in, v4_in);
	disable_kernel_altivec();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(xor_altivec_4);

व्योम xor_altivec_5(अचिन्हित दीर्घ bytes,  अचिन्हित दीर्घ *v1_in,
		   अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in,
		   अचिन्हित दीर्घ *v4_in, अचिन्हित दीर्घ *v5_in)
अणु
	preempt_disable();
	enable_kernel_altivec();
	__xor_altivec_5(bytes, v1_in, v2_in, v3_in, v4_in, v5_in);
	disable_kernel_altivec();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(xor_altivec_5);
