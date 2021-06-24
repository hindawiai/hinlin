<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/cpufeature.h>

अटल पूर्णांक disable_nx;

/*
 * noexec = on|off
 *
 * Control non-executable mappings क्रम processes.
 *
 * on      Enable
 * off     Disable
 */
अटल पूर्णांक __init noexec_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;
	अगर (!म_भेदन(str, "on", 2)) अणु
		disable_nx = 0;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "off", 3)) अणु
		disable_nx = 1;
	पूर्ण
	x86_configure_nx();
	वापस 0;
पूर्ण
early_param("noexec", noexec_setup);

व्योम x86_configure_nx(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_NX) && !disable_nx)
		__supported_pte_mask |= _PAGE_NX;
	अन्यथा
		__supported_pte_mask &= ~_PAGE_NX;
पूर्ण

व्योम __init x86_report_nx(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_NX)) अणु
		prपूर्णांकk(KERN_NOTICE "Notice: NX (Execute Disable) protection "
		       "missing in CPU!\n");
	पूर्ण अन्यथा अणु
#अगर defined(CONFIG_X86_64) || defined(CONFIG_X86_PAE)
		अगर (disable_nx) अणु
			prपूर्णांकk(KERN_INFO "NX (Execute Disable) protection: "
			       "disabled by kernel command line option\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO "NX (Execute Disable) protection: "
			       "active\n");
		पूर्ण
#अन्यथा
		/* 32bit non-PAE kernel, NX cannot be used */
		prपूर्णांकk(KERN_NOTICE "Notice: NX (Execute Disable) protection "
		       "cannot be enabled: non-PAE kernel!\n");
#पूर्ण_अगर
	पूर्ण
पूर्ण
