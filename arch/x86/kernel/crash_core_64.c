<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/crash_core.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/setup.h>

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु
	u64 sme_mask = sme_me_mask;

	VMCOREINFO_NUMBER(phys_base);
	VMCOREINFO_SYMBOL(init_top_pgt);
	vmcoreinfo_append_str("NUMBER(pgtable_l5_enabled)=%d\n",
			      pgtable_l5_enabled());

#अगर_घोषित CONFIG_NUMA
	VMCOREINFO_SYMBOL(node_data);
	VMCOREINFO_LENGTH(node_data, MAX_NUMNODES);
#पूर्ण_अगर
	vmcoreinfo_append_str("KERNELOFFSET=%lx\n", kaslr_offset());
	VMCOREINFO_NUMBER(KERNEL_IMAGE_SIZE);
	VMCOREINFO_NUMBER(sme_mask);
पूर्ण
