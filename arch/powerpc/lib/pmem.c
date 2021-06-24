<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2017 IBM Corporation. All rights reserved.
 */

#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/libnvdimm.h>

#समावेश <यंत्र/cacheflush.h>

अटल अंतरभूत व्योम __clean_pmem_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अचिन्हित दीर्घ shअगरt = l1_dcache_shअगरt();
	अचिन्हित दीर्घ bytes = l1_dcache_bytes();
	व्योम *addr = (व्योम *)(start & ~(bytes - 1));
	अचिन्हित दीर्घ size = stop - (अचिन्हित दीर्घ)addr + (bytes - 1);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < size >> shअगरt; i++, addr += bytes)
		यंत्र अस्थिर(PPC_DCBSTPS(%0, %1): :"i"(0), "r"(addr): "memory");
पूर्ण

अटल अंतरभूत व्योम __flush_pmem_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अचिन्हित दीर्घ shअगरt = l1_dcache_shअगरt();
	अचिन्हित दीर्घ bytes = l1_dcache_bytes();
	व्योम *addr = (व्योम *)(start & ~(bytes - 1));
	अचिन्हित दीर्घ size = stop - (अचिन्हित दीर्घ)addr + (bytes - 1);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < size >> shअगरt; i++, addr += bytes)
		यंत्र अस्थिर(PPC_DCBFPS(%0, %1): :"i"(0), "r"(addr): "memory");
पूर्ण

अटल अंतरभूत व्योम clean_pmem_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस __clean_pmem_range(start, stop);
पूर्ण

अटल अंतरभूत व्योम flush_pmem_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस __flush_pmem_range(start, stop);
पूर्ण

/*
 * CONFIG_ARCH_HAS_PMEM_API symbols
 */
व्योम arch_wb_cache_pmem(व्योम *addr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) addr;
	clean_pmem_range(start, start + size);
पूर्ण
EXPORT_SYMBOL_GPL(arch_wb_cache_pmem);

व्योम arch_invalidate_pmem(व्योम *addr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) addr;
	flush_pmem_range(start, start + size);
पूर्ण
EXPORT_SYMBOL_GPL(arch_invalidate_pmem);

/*
 * CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE symbols
 */
दीर्घ __copy_from_user_flushcache(व्योम *dest, स्थिर व्योम __user *src,
		अचिन्हित size)
अणु
	अचिन्हित दीर्घ copied, start = (अचिन्हित दीर्घ) dest;

	copied = __copy_from_user(dest, src, size);
	clean_pmem_range(start, start + size);

	वापस copied;
पूर्ण

व्योम स_नकल_flushcache(व्योम *dest, स्थिर व्योम *src, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) dest;

	स_नकल(dest, src, size);
	clean_pmem_range(start, start + size);
पूर्ण
EXPORT_SYMBOL(स_नकल_flushcache);

व्योम स_नकल_page_flushcache(अक्षर *to, काष्ठा page *page, माप_प्रकार offset,
	माप_प्रकार len)
अणु
	स_नकल_flushcache(to, page_to_virt(page) + offset, len);
पूर्ण
EXPORT_SYMBOL(स_नकल_page_flushcache);
