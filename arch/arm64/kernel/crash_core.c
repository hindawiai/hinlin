<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Linaro.
 * Copyright (C) Huawei Futurewei Technologies.
 */

#समावेश <linux/crash_core.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/pgtable-hwdef.h>

अटल अंतरभूत u64 get_tcr_el1_t1sz(व्योम);

अटल अंतरभूत u64 get_tcr_el1_t1sz(व्योम)
अणु
	वापस (पढ़ो_sysreg(tcr_el1) & TCR_T1SZ_MASK) >> TCR_T1SZ_OFFSET;
पूर्ण

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु
	VMCOREINFO_NUMBER(VA_BITS);
	/* Please note VMCOREINFO_NUMBER() uses "%d", not "%x" */
	vmcoreinfo_append_str("NUMBER(kimage_voffset)=0x%llx\n",
						kimage_voffset);
	vmcoreinfo_append_str("NUMBER(PHYS_OFFSET)=0x%llx\n",
						PHYS_OFFSET);
	vmcoreinfo_append_str("NUMBER(TCR_EL1_T1SZ)=0x%llx\n",
						get_tcr_el1_t1sz());
	vmcoreinfo_append_str("KERNELOFFSET=%lx\n", kaslr_offset());
	vmcoreinfo_append_str("NUMBER(KERNELPACMASK)=0x%llx\n",
						प्रणाली_supports_address_auth() ?
						ptrauth_kernel_pac_mask() : 0);
पूर्ण
