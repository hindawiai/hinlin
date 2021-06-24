<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/nommu.c
 *
 * ARM uCLinux supporting functions.
 */
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/mpu.h>
#समावेश <यंत्र/procinfo.h>

#समावेश "mm.h"

अचिन्हित दीर्घ vectors_base;

#अगर_घोषित CONFIG_ARM_MPU
काष्ठा mpu_rgn_info mpu_rgn_info;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_CP15
#अगर_घोषित CONFIG_CPU_HIGH_VECTOR
अचिन्हित दीर्घ setup_vectors_base(व्योम)
अणु
	अचिन्हित दीर्घ reg = get_cr();

	set_cr(reg | CR_V);
	वापस 0xffff0000;
पूर्ण
#अन्यथा /* CONFIG_CPU_HIGH_VECTOR */
/* Write exception base address to VBAR */
अटल अंतरभूत व्योम set_vbar(अचिन्हित दीर्घ val)
अणु
	यंत्र("mcr p15, 0, %0, c12, c0, 0" : : "r" (val) : "cc");
पूर्ण

/*
 * Security extensions, bits[7:4], permitted values,
 * 0b0000 - not implemented, 0b0001/0b0010 - implemented
 */
अटल अंतरभूत bool security_extensions_enabled(व्योम)
अणु
	/* Check CPUID Identअगरication Scheme beक्रमe ID_PFR1 पढ़ो */
	अगर ((पढ़ो_cpuid_id() & 0x000f0000) == 0x000f0000)
		वापस cpuid_feature_extract(CPUID_EXT_PFR1, 4) ||
			cpuid_feature_extract(CPUID_EXT_PFR1, 20);
	वापस 0;
पूर्ण

अचिन्हित दीर्घ setup_vectors_base(व्योम)
अणु
	अचिन्हित दीर्घ base = 0, reg = get_cr();

	set_cr(reg & ~CR_V);
	अगर (security_extensions_enabled()) अणु
		अगर (IS_ENABLED(CONFIG_REMAP_VECTORS_TO_RAM))
			base = CONFIG_DRAM_BASE;
		set_vbar(base);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_REMAP_VECTORS_TO_RAM)) अणु
		अगर (CONFIG_DRAM_BASE != 0)
			pr_err("Security extensions not enabled, vectors cannot be remapped to RAM, vectors base will be 0x00000000\n");
	पूर्ण

	वापस base;
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_HIGH_VECTOR */
#पूर्ण_अगर /* CONFIG_CPU_CP15 */

व्योम __init arm_mm_memblock_reserve(व्योम)
अणु
#अगर_अघोषित CONFIG_CPU_V7M
	vectors_base = IS_ENABLED(CONFIG_CPU_CP15) ? setup_vectors_base() : 0;
	/*
	 * Register the exception vector page.
	 * some architectures which the DRAM is the exception vector to trap,
	 * alloc_page अवरोधs with error, although it is not शून्य, but "0."
	 */
	memblock_reserve(vectors_base, 2 * PAGE_SIZE);
#अन्यथा /* अगरndef CONFIG_CPU_V7M */
	/*
	 * There is no dedicated vector page on V7-M. So nothing needs to be
	 * reserved here.
	 */
#पूर्ण_अगर
	/*
	 * In any हाल, always ensure address 0 is never used as many things
	 * get very confused अगर 0 is वापसed as a legitimate address.
	 */
	memblock_reserve(0, 1);
पूर्ण

अटल व्योम __init adjust_lowmem_bounds_mpu(व्योम)
अणु
	अचिन्हित दीर्घ pmsa = पढ़ो_cpuid_ext(CPUID_EXT_MMFR0) & MMFR0_PMSA;

	चयन (pmsa) अणु
	हाल MMFR0_PMSAv7:
		pmsav7_adjust_lowmem_bounds();
		अवरोध;
	हाल MMFR0_PMSAv8:
		pmsav8_adjust_lowmem_bounds();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init mpu_setup(व्योम)
अणु
	अचिन्हित दीर्घ pmsa = पढ़ो_cpuid_ext(CPUID_EXT_MMFR0) & MMFR0_PMSA;

	चयन (pmsa) अणु
	हाल MMFR0_PMSAv7:
		pmsav7_setup();
		अवरोध;
	हाल MMFR0_PMSAv8:
		pmsav8_setup();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम __init adjust_lowmem_bounds(व्योम)
अणु
	phys_addr_t end;
	adjust_lowmem_bounds_mpu();
	end = memblock_end_of_DRAM();
	high_memory = __va(end - 1) + 1;
	memblock_set_current_limit(end);
पूर्ण

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps, and sets up the zero page, bad page and bad page tables.
 */
व्योम __init paging_init(स्थिर काष्ठा machine_desc *mdesc)
अणु
	early_trap_init((व्योम *)vectors_base);
	mpu_setup();
	booपंचांगem_init();
पूर्ण

/*
 * We करोn't need to करो anything here क्रम nommu machines.
 */
व्योम setup_mm_क्रम_reboot(व्योम)
अणु
पूर्ण

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	__cpuc_flush_dcache_area(page_address(page), PAGE_SIZE);
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
	__cpuc_flush_dcache_area(page_address(page), PAGE_SIZE);
पूर्ण
EXPORT_SYMBOL(flush_kernel_dcache_page);

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ uaddr, व्योम *dst, स्थिर व्योम *src,
		       अचिन्हित दीर्घ len)
अणु
	स_नकल(dst, src, len);
	अगर (vma->vm_flags & VM_EXEC)
		__cpuc_coherent_user_range(uaddr, uaddr + len);
पूर्ण

व्योम __iomem *__arm_ioremap_pfn(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ offset,
				माप_प्रकार size, अचिन्हित पूर्णांक mtype)
अणु
	अगर (pfn >= (0x100000000ULL >> PAGE_SHIFT))
		वापस शून्य;
	वापस (व्योम __iomem *) (offset + (pfn << PAGE_SHIFT));
पूर्ण
EXPORT_SYMBOL(__arm_ioremap_pfn);

व्योम __iomem *__arm_ioremap_caller(phys_addr_t phys_addr, माप_प्रकार size,
				   अचिन्हित पूर्णांक mtype, व्योम *caller)
अणु
	वापस (व्योम __iomem *)phys_addr;
पूर्ण

व्योम __iomem * (*arch_ioremap_caller)(phys_addr_t, माप_प्रकार, अचिन्हित पूर्णांक, व्योम *);

व्योम __iomem *ioremap(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस __arm_ioremap_caller(res_cookie, size, MT_DEVICE,
				    __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम __iomem *ioremap_cache(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस __arm_ioremap_caller(res_cookie, size, MT_DEVICE_CACHED,
				    __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap_cache);

व्योम __iomem *ioremap_wc(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस __arm_ioremap_caller(res_cookie, size, MT_DEVICE_WC,
				    __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap_wc);

#अगर_घोषित CONFIG_PCI

#समावेश <यंत्र/mach/map.h>

व्योम __iomem *pci_remap_cfgspace(resource_माप_प्रकार res_cookie, माप_प्रकार size)
अणु
	वापस arch_ioremap_caller(res_cookie, size, MT_UNCACHED,
				   __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL_GPL(pci_remap_cfgspace);
#पूर्ण_अगर

व्योम *arch_memremap_wb(phys_addr_t phys_addr, माप_प्रकार size)
अणु
	वापस (व्योम *)phys_addr;
पूर्ण

व्योम __iounmap(अस्थिर व्योम __iomem *addr)
अणु
पूर्ण
EXPORT_SYMBOL(__iounmap);

व्योम (*arch_iounmap)(अस्थिर व्योम __iomem *);

व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
पूर्ण
EXPORT_SYMBOL(iounmap);
