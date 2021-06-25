<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/highस्मृति.स>
#समावेश <linux/genभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/fixmap.h>

#अगर (CONFIG_ITCM_RAM_BASE == 0xffffffff)
#त्रुटि "You should define ITCM_RAM_BASE"
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_DTCM
#अगर (CONFIG_DTCM_RAM_BASE == 0xffffffff)
#त्रुटि "You should define DTCM_RAM_BASE"
#पूर्ण_अगर

#अगर (CONFIG_DTCM_RAM_BASE == CONFIG_ITCM_RAM_BASE)
#त्रुटि "You should define correct DTCM_RAM_BASE"
#पूर्ण_अगर
#पूर्ण_अगर

बाह्य अक्षर __tcm_start, __tcm_end, __dtcm_start;

अटल काष्ठा gen_pool *tcm_pool;

अटल व्योम __init tcm_mapping_init(व्योम)
अणु
	pte_t *tcm_pte;
	अचिन्हित दीर्घ vaddr, paddr;
	पूर्णांक i;

	paddr = CONFIG_ITCM_RAM_BASE;

	अगर (pfn_valid(PFN_DOWN(CONFIG_ITCM_RAM_BASE)))
		जाओ panic;

#अगर_अघोषित CONFIG_HAVE_DTCM
	क्रम (i = 0; i < TCM_NR_PAGES; i++) अणु
#अन्यथा
	क्रम (i = 0; i < CONFIG_ITCM_NR_PAGES; i++) अणु
#पूर्ण_अगर
		vaddr = __fix_to_virt(FIX_TCM - i);

		tcm_pte =
			pte_offset_kernel((pmd_t *)pgd_offset_k(vaddr), vaddr);

		set_pte(tcm_pte, pfn_pte(__phys_to_pfn(paddr), PAGE_KERNEL));

		flush_tlb_one(vaddr);

		paddr = paddr + PAGE_SIZE;
	पूर्ण

#अगर_घोषित CONFIG_HAVE_DTCM
	अगर (pfn_valid(PFN_DOWN(CONFIG_DTCM_RAM_BASE)))
		जाओ panic;

	paddr = CONFIG_DTCM_RAM_BASE;

	क्रम (i = 0; i < CONFIG_DTCM_NR_PAGES; i++) अणु
		vaddr = __fix_to_virt(FIX_TCM - CONFIG_ITCM_NR_PAGES - i);

		tcm_pte =
			pte_offset_kernel((pmd_t *) pgd_offset_k(vaddr), vaddr);

		set_pte(tcm_pte, pfn_pte(__phys_to_pfn(paddr), PAGE_KERNEL));

		flush_tlb_one(vaddr);

		paddr = paddr + PAGE_SIZE;
	पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_HAVE_DTCM
	स_नकल((व्योम *)__fix_to_virt(FIX_TCM),
				&__tcm_start, &__tcm_end - &__tcm_start);

	pr_info("%s: mapping tcm va:0x%08lx to pa:0x%08x\n",
			__func__, __fix_to_virt(FIX_TCM), CONFIG_ITCM_RAM_BASE);

	pr_info("%s: __tcm_start va:0x%08lx size:%d\n",
			__func__, (अचिन्हित दीर्घ)&__tcm_start, &__tcm_end - &__tcm_start);
#अन्यथा
	स_नकल((व्योम *)__fix_to_virt(FIX_TCM),
				&__tcm_start, &__dtcm_start - &__tcm_start);

	pr_info("%s: mapping itcm va:0x%08lx to pa:0x%08x\n",
			__func__, __fix_to_virt(FIX_TCM), CONFIG_ITCM_RAM_BASE);

	pr_info("%s: __itcm_start va:0x%08lx size:%d\n",
			__func__, (अचिन्हित दीर्घ)&__tcm_start, &__dtcm_start - &__tcm_start);

	स_नकल((व्योम *)__fix_to_virt(FIX_TCM - CONFIG_ITCM_NR_PAGES),
				&__dtcm_start, &__tcm_end - &__dtcm_start);

	pr_info("%s: mapping dtcm va:0x%08lx to pa:0x%08x\n",
			__func__, __fix_to_virt(FIX_TCM - CONFIG_ITCM_NR_PAGES),
						CONFIG_DTCM_RAM_BASE);

	pr_info("%s: __dtcm_start va:0x%08lx size:%d\n",
			__func__, (अचिन्हित दीर्घ)&__dtcm_start, &__tcm_end - &__dtcm_start);

#पूर्ण_अगर
	वापस;
panic:
	panic("TCM init error");
पूर्ण

व्योम *tcm_alloc(माप_प्रकार len)
अणु
	अचिन्हित दीर्घ vaddr;

	अगर (!tcm_pool)
		वापस शून्य;

	vaddr = gen_pool_alloc(tcm_pool, len);
	अगर (!vaddr)
		वापस शून्य;

	वापस (व्योम *) vaddr;
पूर्ण
EXPORT_SYMBOL(tcm_alloc);

व्योम tcm_मुक्त(व्योम *addr, माप_प्रकार len)
अणु
	gen_pool_मुक्त(tcm_pool, (अचिन्हित दीर्घ) addr, len);
पूर्ण
EXPORT_SYMBOL(tcm_मुक्त);

अटल पूर्णांक __init tcm_setup_pool(व्योम)
अणु
#अगर_अघोषित CONFIG_HAVE_DTCM
	u32 pool_size = (u32) (TCM_NR_PAGES * PAGE_SIZE)
				- (u32) (&__tcm_end - &__tcm_start);

	u32 tcm_pool_start = __fix_to_virt(FIX_TCM)
				+ (u32) (&__tcm_end - &__tcm_start);
#अन्यथा
	u32 pool_size = (u32) (CONFIG_DTCM_NR_PAGES * PAGE_SIZE)
				- (u32) (&__tcm_end - &__dtcm_start);

	u32 tcm_pool_start = __fix_to_virt(FIX_TCM - CONFIG_ITCM_NR_PAGES)
				+ (u32) (&__tcm_end - &__dtcm_start);
#पूर्ण_अगर
	पूर्णांक ret;

	tcm_pool = gen_pool_create(2, -1);

	ret = gen_pool_add(tcm_pool, tcm_pool_start, pool_size, -1);
	अगर (ret) अणु
		pr_err("%s: gen_pool add failed!\n", __func__);
		वापस ret;
	पूर्ण

	pr_info("%s: Added %d bytes @ 0x%08x to memory pool\n",
		__func__, pool_size, tcm_pool_start);

	वापस 0;
पूर्ण

अटल पूर्णांक __init tcm_init(व्योम)
अणु
	tcm_mapping_init();

	tcm_setup_pool();

	वापस 0;
पूर्ण
arch_initcall(tcm_init);
