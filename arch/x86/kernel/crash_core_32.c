<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/crash_core.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/setup.h>

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु
#अगर_घोषित CONFIG_NUMA
	VMCOREINFO_SYMBOL(node_data);
	VMCOREINFO_LENGTH(node_data, MAX_NUMNODES);
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_PAE
	VMCOREINFO_CONFIG(X86_PAE);
#पूर्ण_अगर
पूर्ण
