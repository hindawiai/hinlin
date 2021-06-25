<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>

#अगर_घोषित CONFIG_X86_64
अटल __always_अंतरभूत u64 canonical_address(u64 vaddr, u8 vaddr_bits)
अणु
	वापस ((s64)vaddr << (64 - vaddr_bits)) >> (64 - vaddr_bits);
पूर्ण

bool copy_from_kernel_nofault_allowed(स्थिर व्योम *unsafe_src, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)unsafe_src;

	/*
	 * Range covering the highest possible canonical userspace address
	 * as well as non-canonical address range. For the canonical range
	 * we also need to include the userspace guard page.
	 */
	वापस vaddr >= TASK_SIZE_MAX + PAGE_SIZE &&
	       canonical_address(vaddr, boot_cpu_data.x86_virt_bits) == vaddr;
पूर्ण
#अन्यथा
bool copy_from_kernel_nofault_allowed(स्थिर व्योम *unsafe_src, माप_प्रकार size)
अणु
	वापस (अचिन्हित दीर्घ)unsafe_src >= TASK_SIZE_MAX;
पूर्ण
#पूर्ण_अगर
