<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/smp.h>
#समावेश <linux/export.h>

अटल व्योम __wbinvd(व्योम *dummy)
अणु
	wbinvd();
पूर्ण

व्योम wbinvd_on_cpu(पूर्णांक cpu)
अणु
	smp_call_function_single(cpu, __wbinvd, शून्य, 1);
पूर्ण
EXPORT_SYMBOL(wbinvd_on_cpu);

पूर्णांक wbinvd_on_all_cpus(व्योम)
अणु
	on_each_cpu(__wbinvd, शून्य, 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(wbinvd_on_all_cpus);
