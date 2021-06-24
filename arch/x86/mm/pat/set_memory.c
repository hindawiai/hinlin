<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002 Andi Kleen, SuSE Lअसल.
 * Thanks to Ben LaHaise क्रम precious feedback.
 */
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/pfn.h>
#समावेश <linux/percpu.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/set_memory.h>

#समावेश "../mm_internal.h"

/*
 * The current flushing context - we pass it instead of 5 arguments:
 */
काष्ठा cpa_data अणु
	अचिन्हित दीर्घ	*vaddr;
	pgd_t		*pgd;
	pgprot_t	mask_set;
	pgprot_t	mask_clr;
	अचिन्हित दीर्घ	numpages;
	अचिन्हित दीर्घ	curpage;
	अचिन्हित दीर्घ	pfn;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	क्रमce_split		: 1,
			क्रमce_अटल_prot	: 1,
			क्रमce_flush_all		: 1;
	काष्ठा page	**pages;
पूर्ण;

क्रमागत cpa_warn अणु
	CPA_CONFLICT,
	CPA_PROTECT,
	CPA_DETECT,
पूर्ण;

अटल स्थिर पूर्णांक cpa_warn_level = CPA_PROTECT;

/*
 * Serialize cpa() (क्रम !DEBUG_PAGEALLOC which uses large identity mappings)
 * using cpa_lock. So that we करोn't allow any other cpu, with stale large tlb
 * entries change the page attribute in parallel to some other cpu
 * splitting a large page entry aदीर्घ with changing the attribute.
 */
अटल DEFINE_SPINLOCK(cpa_lock);

#घोषणा CPA_FLUSHTLB 1
#घोषणा CPA_ARRAY 2
#घोषणा CPA_PAGES_ARRAY 4
#घोषणा CPA_NO_CHECK_ALIAS 8 /* Do not search क्रम aliases */

अटल अंतरभूत pgprot_t cachemode2pgprot(क्रमागत page_cache_mode pcm)
अणु
	वापस __pgprot(cachemode2protval(pcm));
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल अचिन्हित दीर्घ direct_pages_count[PG_LEVEL_NUM];

व्योम update_page_count(पूर्णांक level, अचिन्हित दीर्घ pages)
अणु
	/* Protect against CPA */
	spin_lock(&pgd_lock);
	direct_pages_count[level] += pages;
	spin_unlock(&pgd_lock);
पूर्ण

अटल व्योम split_page_count(पूर्णांक level)
अणु
	अगर (direct_pages_count[level] == 0)
		वापस;

	direct_pages_count[level]--;
	अगर (प्रणाली_state == SYSTEM_RUNNING) अणु
		अगर (level == PG_LEVEL_2M)
			count_vm_event(सूचीECT_MAP_LEVEL2_SPLIT);
		अन्यथा अगर (level == PG_LEVEL_1G)
			count_vm_event(सूचीECT_MAP_LEVEL3_SPLIT);
	पूर्ण
	direct_pages_count[level - 1] += PTRS_PER_PTE;
पूर्ण

व्योम arch_report_meminfo(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "DirectMap4k:    %8lu kB\n",
			direct_pages_count[PG_LEVEL_4K] << 2);
#अगर defined(CONFIG_X86_64) || defined(CONFIG_X86_PAE)
	seq_म_लिखो(m, "DirectMap2M:    %8lu kB\n",
			direct_pages_count[PG_LEVEL_2M] << 11);
#अन्यथा
	seq_म_लिखो(m, "DirectMap4M:    %8lu kB\n",
			direct_pages_count[PG_LEVEL_2M] << 12);
#पूर्ण_अगर
	अगर (direct_gbpages)
		seq_म_लिखो(m, "DirectMap1G:    %8lu kB\n",
			direct_pages_count[PG_LEVEL_1G] << 20);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम split_page_count(पूर्णांक level) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_CPA_STATISTICS

अटल अचिन्हित दीर्घ cpa_1g_checked;
अटल अचिन्हित दीर्घ cpa_1g_sameprot;
अटल अचिन्हित दीर्घ cpa_1g_preserved;
अटल अचिन्हित दीर्घ cpa_2m_checked;
अटल अचिन्हित दीर्घ cpa_2m_sameprot;
अटल अचिन्हित दीर्घ cpa_2m_preserved;
अटल अचिन्हित दीर्घ cpa_4k_install;

अटल अंतरभूत व्योम cpa_inc_1g_checked(व्योम)
अणु
	cpa_1g_checked++;
पूर्ण

अटल अंतरभूत व्योम cpa_inc_2m_checked(व्योम)
अणु
	cpa_2m_checked++;
पूर्ण

अटल अंतरभूत व्योम cpa_inc_4k_install(व्योम)
अणु
	data_race(cpa_4k_install++);
पूर्ण

अटल अंतरभूत व्योम cpa_inc_lp_sameprot(पूर्णांक level)
अणु
	अगर (level == PG_LEVEL_1G)
		cpa_1g_sameprot++;
	अन्यथा
		cpa_2m_sameprot++;
पूर्ण

अटल अंतरभूत व्योम cpa_inc_lp_preserved(पूर्णांक level)
अणु
	अगर (level == PG_LEVEL_1G)
		cpa_1g_preserved++;
	अन्यथा
		cpa_2m_preserved++;
पूर्ण

अटल पूर्णांक cpastats_show(काष्ठा seq_file *m, व्योम *p)
अणु
	seq_म_लिखो(m, "1G pages checked:     %16lu\n", cpa_1g_checked);
	seq_म_लिखो(m, "1G pages sameprot:    %16lu\n", cpa_1g_sameprot);
	seq_म_लिखो(m, "1G pages preserved:   %16lu\n", cpa_1g_preserved);
	seq_म_लिखो(m, "2M pages checked:     %16lu\n", cpa_2m_checked);
	seq_म_लिखो(m, "2M pages sameprot:    %16lu\n", cpa_2m_sameprot);
	seq_म_लिखो(m, "2M pages preserved:   %16lu\n", cpa_2m_preserved);
	seq_म_लिखो(m, "4K pages set-checked: %16lu\n", cpa_4k_install);
	वापस 0;
पूर्ण

अटल पूर्णांक cpastats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, cpastats_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations cpastats_fops = अणु
	.खोलो		= cpastats_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक __init cpa_stats_init(व्योम)
अणु
	debugfs_create_file("cpa_stats", S_IRUSR, arch_debugfs_dir, शून्य,
			    &cpastats_fops);
	वापस 0;
पूर्ण
late_initcall(cpa_stats_init);
#अन्यथा
अटल अंतरभूत व्योम cpa_inc_1g_checked(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpa_inc_2m_checked(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpa_inc_4k_install(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpa_inc_lp_sameprot(पूर्णांक level) अणु पूर्ण
अटल अंतरभूत व्योम cpa_inc_lp_preserved(पूर्णांक level) अणु पूर्ण
#पूर्ण_अगर


अटल अंतरभूत पूर्णांक
within(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस addr >= start && addr < end;
पूर्ण

अटल अंतरभूत पूर्णांक
within_inclusive(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस addr >= start && addr <= end;
पूर्ण

#अगर_घोषित CONFIG_X86_64

अटल अंतरभूत अचिन्हित दीर्घ highmap_start_pfn(व्योम)
अणु
	वापस __pa_symbol(_text) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ highmap_end_pfn(व्योम)
अणु
	/* Do not reference physical address outside the kernel. */
	वापस __pa_symbol(roundup(_brk_end, PMD_SIZE) - 1) >> PAGE_SHIFT;
पूर्ण

अटल bool __cpa_pfn_in_highmap(अचिन्हित दीर्घ pfn)
अणु
	/*
	 * Kernel text has an alias mapping at a high address, known
	 * here as "highmap".
	 */
	वापस within_inclusive(pfn, highmap_start_pfn(), highmap_end_pfn());
पूर्ण

#अन्यथा

अटल bool __cpa_pfn_in_highmap(अचिन्हित दीर्घ pfn)
अणु
	/* There is no highmap on 32-bit */
	वापस false;
पूर्ण

#पूर्ण_अगर

/*
 * See set_mce_nospec().
 *
 * Machine check recovery code needs to change cache mode of poisoned pages to
 * UC to aव्योम speculative access logging another error. But passing the
 * address of the 1:1 mapping to set_memory_uc() is a fine way to encourage a
 * speculative access. So we cheat and flip the top bit of the address. This
 * works fine क्रम the code that updates the page tables. But at the end of the
 * process we need to flush the TLB and cache and the non-canonical address
 * causes a #GP fault when used by the INVLPG and CLFLUSH inकाष्ठाions.
 *
 * But in the common हाल we alपढ़ोy have a canonical address. This code
 * will fix the top bit अगर needed and is a no-op otherwise.
 */
अटल अंतरभूत अचिन्हित दीर्घ fix_addr(अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_X86_64
	वापस (दीर्घ)(addr << 1) >> 1;
#अन्यथा
	वापस addr;
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ __cpa_addr(काष्ठा cpa_data *cpa, अचिन्हित दीर्घ idx)
अणु
	अगर (cpa->flags & CPA_PAGES_ARRAY) अणु
		काष्ठा page *page = cpa->pages[idx];

		अगर (unlikely(PageHighMem(page)))
			वापस 0;

		वापस (अचिन्हित दीर्घ)page_address(page);
	पूर्ण

	अगर (cpa->flags & CPA_ARRAY)
		वापस cpa->vaddr[idx];

	वापस *cpa->vaddr + idx * PAGE_SIZE;
पूर्ण

/*
 * Flushing functions
 */

अटल व्योम clflush_cache_range_opt(व्योम *vaddr, अचिन्हित पूर्णांक size)
अणु
	स्थिर अचिन्हित दीर्घ clflush_size = boot_cpu_data.x86_clflush_size;
	व्योम *p = (व्योम *)((अचिन्हित दीर्घ)vaddr & ~(clflush_size - 1));
	व्योम *vend = vaddr + size;

	अगर (p >= vend)
		वापस;

	क्रम (; p < vend; p += clflush_size)
		clflushopt(p);
पूर्ण

/**
 * clflush_cache_range - flush a cache range with clflush
 * @vaddr:	भव start address
 * @size:	number of bytes to flush
 *
 * CLFLUSHOPT is an unordered inकाष्ठाion which needs fencing with MFENCE or
 * SFENCE to aव्योम ordering issues.
 */
व्योम clflush_cache_range(व्योम *vaddr, अचिन्हित पूर्णांक size)
अणु
	mb();
	clflush_cache_range_opt(vaddr, size);
	mb();
पूर्ण
EXPORT_SYMBOL_GPL(clflush_cache_range);

#अगर_घोषित CONFIG_ARCH_HAS_PMEM_API
व्योम arch_invalidate_pmem(व्योम *addr, माप_प्रकार size)
अणु
	clflush_cache_range(addr, size);
पूर्ण
EXPORT_SYMBOL_GPL(arch_invalidate_pmem);
#पूर्ण_अगर

अटल व्योम __cpa_flush_all(व्योम *arg)
अणु
	अचिन्हित दीर्घ cache = (अचिन्हित दीर्घ)arg;

	/*
	 * Flush all to work around Errata in early athlons regarding
	 * large page flushing.
	 */
	__flush_tlb_all();

	अगर (cache && boot_cpu_data.x86 >= 4)
		wbinvd();
पूर्ण

अटल व्योम cpa_flush_all(अचिन्हित दीर्घ cache)
अणु
	BUG_ON(irqs_disabled() && !early_boot_irqs_disabled);

	on_each_cpu(__cpa_flush_all, (व्योम *) cache, 1);
पूर्ण

अटल व्योम __cpa_flush_tlb(व्योम *data)
अणु
	काष्ठा cpa_data *cpa = data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cpa->numpages; i++)
		flush_tlb_one_kernel(fix_addr(__cpa_addr(cpa, i)));
पूर्ण

अटल व्योम cpa_flush(काष्ठा cpa_data *data, पूर्णांक cache)
अणु
	काष्ठा cpa_data *cpa = data;
	अचिन्हित पूर्णांक i;

	BUG_ON(irqs_disabled() && !early_boot_irqs_disabled);

	अगर (cache && !अटल_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		cpa_flush_all(cache);
		वापस;
	पूर्ण

	अगर (cpa->क्रमce_flush_all || cpa->numpages > tlb_single_page_flush_उच्चमानing)
		flush_tlb_all();
	अन्यथा
		on_each_cpu(__cpa_flush_tlb, cpa, 1);

	अगर (!cache)
		वापस;

	mb();
	क्रम (i = 0; i < cpa->numpages; i++) अणु
		अचिन्हित दीर्घ addr = __cpa_addr(cpa, i);
		अचिन्हित पूर्णांक level;

		pte_t *pte = lookup_address(addr, &level);

		/*
		 * Only flush present addresses:
		 */
		अगर (pte && (pte_val(*pte) & _PAGE_PRESENT))
			clflush_cache_range_opt((व्योम *)fix_addr(addr), PAGE_SIZE);
	पूर्ण
	mb();
पूर्ण

अटल bool overlaps(अचिन्हित दीर्घ r1_start, अचिन्हित दीर्घ r1_end,
		     अचिन्हित दीर्घ r2_start, अचिन्हित दीर्घ r2_end)
अणु
	वापस (r1_start <= r2_end && r1_end >= r2_start) ||
		(r2_start <= r1_end && r2_end >= r1_start);
पूर्ण

#अगर_घोषित CONFIG_PCI_BIOS
/*
 * The BIOS area between 640k and 1Mb needs to be executable क्रम PCI BIOS
 * based config access (CONFIG_PCI_GOBIOS) support.
 */
#घोषणा BIOS_PFN	PFN_DOWN(BIOS_BEGIN)
#घोषणा BIOS_PFN_END	PFN_DOWN(BIOS_END - 1)

अटल pgprotval_t protect_pci_bios(अचिन्हित दीर्घ spfn, अचिन्हित दीर्घ epfn)
अणु
	अगर (pcibios_enabled && overlaps(spfn, epfn, BIOS_PFN, BIOS_PFN_END))
		वापस _PAGE_NX;
	वापस 0;
पूर्ण
#अन्यथा
अटल pgprotval_t protect_pci_bios(अचिन्हित दीर्घ spfn, अचिन्हित दीर्घ epfn)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * The .rodata section needs to be पढ़ो-only. Using the pfn catches all
 * aliases.  This also includes __ro_after_init, so करो not enक्रमce until
 * kernel_set_to_पढ़ोonly is true.
 */
अटल pgprotval_t protect_rodata(अचिन्हित दीर्घ spfn, अचिन्हित दीर्घ epfn)
अणु
	अचिन्हित दीर्घ epfn_ro, spfn_ro = PFN_DOWN(__pa_symbol(__start_rodata));

	/*
	 * Note: __end_rodata is at page aligned and not inclusive, so
	 * subtract 1 to get the last enक्रमced PFN in the rodata area.
	 */
	epfn_ro = PFN_DOWN(__pa_symbol(__end_rodata)) - 1;

	अगर (kernel_set_to_पढ़ोonly && overlaps(spfn, epfn, spfn_ro, epfn_ro))
		वापस _PAGE_RW;
	वापस 0;
पूर्ण

/*
 * Protect kernel text against becoming non executable by क्रमbidding
 * _PAGE_NX.  This protects only the high kernel mapping (_text -> _etext)
 * out of which the kernel actually executes.  Do not protect the low
 * mapping.
 *
 * This करोes not cover __inittext since that is gone after boot.
 */
अटल pgprotval_t protect_kernel_text(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ t_end = (अचिन्हित दीर्घ)_etext - 1;
	अचिन्हित दीर्घ t_start = (अचिन्हित दीर्घ)_text;

	अगर (overlaps(start, end, t_start, t_end))
		वापस _PAGE_NX;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_X86_64)
/*
 * Once the kernel maps the text as RO (kernel_set_to_पढ़ोonly is set),
 * kernel text mappings क्रम the large page aligned text, rodata sections
 * will be always पढ़ो-only. For the kernel identity mappings covering the
 * holes caused by this alignment can be anything that user asks.
 *
 * This will preserve the large page mappings क्रम kernel text/data at no
 * extra cost.
 */
अटल pgprotval_t protect_kernel_text_ro(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ t_end = (अचिन्हित दीर्घ)__end_rodata_hpage_align - 1;
	अचिन्हित दीर्घ t_start = (अचिन्हित दीर्घ)_text;
	अचिन्हित पूर्णांक level;

	अगर (!kernel_set_to_पढ़ोonly || !overlaps(start, end, t_start, t_end))
		वापस 0;
	/*
	 * Don't enक्रमce the !RW mapping क्रम the kernel text mapping, अगर
	 * the current mapping is alपढ़ोy using small page mapping.  No
	 * need to work hard to preserve large page mappings in this हाल.
	 *
	 * This also fixes the Linux Xen paravirt guest boot failure caused
	 * by unexpected पढ़ो-only mappings क्रम kernel identity
	 * mappings. In this paravirt guest हाल, the kernel text mapping
	 * and the kernel identity mapping share the same page-table pages,
	 * so the protections क्रम kernel text and identity mappings have to
	 * be the same.
	 */
	अगर (lookup_address(start, &level) && (level != PG_LEVEL_4K))
		वापस _PAGE_RW;
	वापस 0;
पूर्ण
#अन्यथा
अटल pgprotval_t protect_kernel_text_ro(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool conflicts(pgprot_t prot, pgprotval_t val)
अणु
	वापस (pgprot_val(prot) & ~val) != pgprot_val(prot);
पूर्ण

अटल अंतरभूत व्योम check_conflict(पूर्णांक warnlvl, pgprot_t prot, pgprotval_t val,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  अचिन्हित दीर्घ pfn, स्थिर अक्षर *txt)
अणु
	अटल स्थिर अक्षर *lvltxt[] = अणु
		[CPA_CONFLICT]	= "conflict",
		[CPA_PROTECT]	= "protect",
		[CPA_DETECT]	= "detect",
	पूर्ण;

	अगर (warnlvl > cpa_warn_level || !conflicts(prot, val))
		वापस;

	pr_warn("CPA %8s %10s: 0x%016lx - 0x%016lx PFN %lx req %016llx prevent %016llx\n",
		lvltxt[warnlvl], txt, start, end, pfn, (अचिन्हित दीर्घ दीर्घ)pgprot_val(prot),
		(अचिन्हित दीर्घ दीर्घ)val);
पूर्ण

/*
 * Certain areas of memory on x86 require very specअगरic protection flags,
 * क्रम example the BIOS area or kernel text. Callers करोn't always get this
 * right (again, ioremap() on BIOS memory is not uncommon) so this function
 * checks and fixes these known अटल required protection bits.
 */
अटल अंतरभूत pgprot_t अटल_protections(pgprot_t prot, अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ npg,
					  अचिन्हित दीर्घ lpsize, पूर्णांक warnlvl)
अणु
	pgprotval_t क्रमbidden, res;
	अचिन्हित दीर्घ end;

	/*
	 * There is no poपूर्णांक in checking RW/NX conflicts when the requested
	 * mapping is setting the page !PRESENT.
	 */
	अगर (!(pgprot_val(prot) & _PAGE_PRESENT))
		वापस prot;

	/* Operate on the भव address */
	end = start + npg * PAGE_SIZE - 1;

	res = protect_kernel_text(start, end);
	check_conflict(warnlvl, prot, res, start, end, pfn, "Text NX");
	क्रमbidden = res;

	/*
	 * Special हाल to preserve a large page. If the change spawns the
	 * full large page mapping then there is no poपूर्णांक to split it
	 * up. Happens with ftrace and is going to be हटाओd once ftrace
	 * चयनed to text_poke().
	 */
	अगर (lpsize != (npg * PAGE_SIZE) || (start & (lpsize - 1))) अणु
		res = protect_kernel_text_ro(start, end);
		check_conflict(warnlvl, prot, res, start, end, pfn, "Text RO");
		क्रमbidden |= res;
	पूर्ण

	/* Check the PFN directly */
	res = protect_pci_bios(pfn, pfn + npg - 1);
	check_conflict(warnlvl, prot, res, start, end, pfn, "PCIBIOS NX");
	क्रमbidden |= res;

	res = protect_rodata(pfn, pfn + npg - 1);
	check_conflict(warnlvl, prot, res, start, end, pfn, "Rodata RO");
	क्रमbidden |= res;

	वापस __pgprot(pgprot_val(prot) & ~क्रमbidden);
पूर्ण

/*
 * Lookup the page table entry क्रम a भव address in a specअगरic pgd.
 * Return a poपूर्णांकer to the entry and the level of the mapping.
 */
pte_t *lookup_address_in_pgd(pgd_t *pgd, अचिन्हित दीर्घ address,
			     अचिन्हित पूर्णांक *level)
अणु
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	*level = PG_LEVEL_NONE;

	अगर (pgd_none(*pgd))
		वापस शून्य;

	p4d = p4d_offset(pgd, address);
	अगर (p4d_none(*p4d))
		वापस शून्य;

	*level = PG_LEVEL_512G;
	अगर (p4d_large(*p4d) || !p4d_present(*p4d))
		वापस (pte_t *)p4d;

	pud = pud_offset(p4d, address);
	अगर (pud_none(*pud))
		वापस शून्य;

	*level = PG_LEVEL_1G;
	अगर (pud_large(*pud) || !pud_present(*pud))
		वापस (pte_t *)pud;

	pmd = pmd_offset(pud, address);
	अगर (pmd_none(*pmd))
		वापस शून्य;

	*level = PG_LEVEL_2M;
	अगर (pmd_large(*pmd) || !pmd_present(*pmd))
		वापस (pte_t *)pmd;

	*level = PG_LEVEL_4K;

	वापस pte_offset_kernel(pmd, address);
पूर्ण

/*
 * Lookup the page table entry क्रम a भव address. Return a poपूर्णांकer
 * to the entry and the level of the mapping.
 *
 * Note: We वापस pud and pmd either when the entry is marked large
 * or when the present bit is not set. Otherwise we would वापस a
 * poपूर्णांकer to a nonexisting mapping.
 */
pte_t *lookup_address(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक *level)
अणु
	वापस lookup_address_in_pgd(pgd_offset_k(address), address, level);
पूर्ण
EXPORT_SYMBOL_GPL(lookup_address);

/*
 * Lookup the page table entry क्रम a भव address in a given mm. Return a
 * poपूर्णांकer to the entry and the level of the mapping.
 */
pte_t *lookup_address_in_mm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			    अचिन्हित पूर्णांक *level)
अणु
	वापस lookup_address_in_pgd(pgd_offset(mm, address), address, level);
पूर्ण
EXPORT_SYMBOL_GPL(lookup_address_in_mm);

अटल pte_t *_lookup_address_cpa(काष्ठा cpa_data *cpa, अचिन्हित दीर्घ address,
				  अचिन्हित पूर्णांक *level)
अणु
	अगर (cpa->pgd)
		वापस lookup_address_in_pgd(cpa->pgd + pgd_index(address),
					       address, level);

	वापस lookup_address(address, level);
पूर्ण

/*
 * Lookup the PMD entry क्रम a भव address. Return a poपूर्णांकer to the entry
 * or शून्य अगर not present.
 */
pmd_t *lookup_pmd_address(अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset_k(address);
	अगर (pgd_none(*pgd))
		वापस शून्य;

	p4d = p4d_offset(pgd, address);
	अगर (p4d_none(*p4d) || p4d_large(*p4d) || !p4d_present(*p4d))
		वापस शून्य;

	pud = pud_offset(p4d, address);
	अगर (pud_none(*pud) || pud_large(*pud) || !pud_present(*pud))
		वापस शून्य;

	वापस pmd_offset(pud, address);
पूर्ण

/*
 * This is necessary because __pa() करोes not work on some
 * kinds of memory, like vदो_स्मृति() or the alloc_remap()
 * areas on 32-bit NUMA प्रणालीs.  The percpu areas can
 * end up in this kind of memory, क्रम instance.
 *
 * This could be optimized, but it is only पूर्णांकended to be
 * used at initialization समय, and keeping it
 * unoptimized should increase the testing coverage क्रम
 * the more obscure platक्रमms.
 */
phys_addr_t slow_virt_to_phys(व्योम *__virt_addr)
अणु
	अचिन्हित दीर्घ virt_addr = (अचिन्हित दीर्घ)__virt_addr;
	phys_addr_t phys_addr;
	अचिन्हित दीर्घ offset;
	क्रमागत pg_level level;
	pte_t *pte;

	pte = lookup_address(virt_addr, &level);
	BUG_ON(!pte);

	/*
	 * pXX_pfn() वापसs अचिन्हित दीर्घ, which must be cast to phys_addr_t
	 * beक्रमe being left-shअगरted PAGE_SHIFT bits -- this trick is to
	 * make 32-PAE kernel work correctly.
	 */
	चयन (level) अणु
	हाल PG_LEVEL_1G:
		phys_addr = (phys_addr_t)pud_pfn(*(pud_t *)pte) << PAGE_SHIFT;
		offset = virt_addr & ~PUD_PAGE_MASK;
		अवरोध;
	हाल PG_LEVEL_2M:
		phys_addr = (phys_addr_t)pmd_pfn(*(pmd_t *)pte) << PAGE_SHIFT;
		offset = virt_addr & ~PMD_PAGE_MASK;
		अवरोध;
	शेष:
		phys_addr = (phys_addr_t)pte_pfn(*pte) << PAGE_SHIFT;
		offset = virt_addr & ~PAGE_MASK;
	पूर्ण

	वापस (phys_addr_t)(phys_addr | offset);
पूर्ण
EXPORT_SYMBOL_GPL(slow_virt_to_phys);

/*
 * Set the new pmd in all the pgds we know about:
 */
अटल व्योम __set_pmd_pte(pte_t *kpte, अचिन्हित दीर्घ address, pte_t pte)
अणु
	/* change init_mm */
	set_pte_atomic(kpte, pte);
#अगर_घोषित CONFIG_X86_32
	अगर (!SHARED_KERNEL_PMD) अणु
		काष्ठा page *page;

		list_क्रम_each_entry(page, &pgd_list, lru) अणु
			pgd_t *pgd;
			p4d_t *p4d;
			pud_t *pud;
			pmd_t *pmd;

			pgd = (pgd_t *)page_address(page) + pgd_index(address);
			p4d = p4d_offset(pgd, address);
			pud = pud_offset(p4d, address);
			pmd = pmd_offset(pud, address);
			set_pte_atomic((pte_t *)pmd, pte);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल pgprot_t pgprot_clear_protnone_bits(pgprot_t prot)
अणु
	/*
	 * _PAGE_GLOBAL means "global page" क्रम present PTEs.
	 * But, it is also used to indicate _PAGE_PROTNONE
	 * क्रम non-present PTEs.
	 *
	 * This ensures that a _PAGE_GLOBAL PTE going from
	 * present to non-present is not confused as
	 * _PAGE_PROTNONE.
	 */
	अगर (!(pgprot_val(prot) & _PAGE_PRESENT))
		pgprot_val(prot) &= ~_PAGE_GLOBAL;

	वापस prot;
पूर्ण

अटल पूर्णांक __should_split_large_page(pte_t *kpte, अचिन्हित दीर्घ address,
				     काष्ठा cpa_data *cpa)
अणु
	अचिन्हित दीर्घ numpages, pmask, psize, lpaddr, pfn, old_pfn;
	pgprot_t old_prot, new_prot, req_prot, chk_prot;
	pte_t new_pte, *पंचांगp;
	क्रमागत pg_level level;

	/*
	 * Check क्रम races, another CPU might have split this page
	 * up alपढ़ोy:
	 */
	पंचांगp = _lookup_address_cpa(cpa, address, &level);
	अगर (पंचांगp != kpte)
		वापस 1;

	चयन (level) अणु
	हाल PG_LEVEL_2M:
		old_prot = pmd_pgprot(*(pmd_t *)kpte);
		old_pfn = pmd_pfn(*(pmd_t *)kpte);
		cpa_inc_2m_checked();
		अवरोध;
	हाल PG_LEVEL_1G:
		old_prot = pud_pgprot(*(pud_t *)kpte);
		old_pfn = pud_pfn(*(pud_t *)kpte);
		cpa_inc_1g_checked();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	psize = page_level_size(level);
	pmask = page_level_mask(level);

	/*
	 * Calculate the number of pages, which fit पूर्णांकo this large
	 * page starting at address:
	 */
	lpaddr = (address + psize) & pmask;
	numpages = (lpaddr - address) >> PAGE_SHIFT;
	अगर (numpages < cpa->numpages)
		cpa->numpages = numpages;

	/*
	 * We are safe now. Check whether the new pgprot is the same:
	 * Convert protection attributes to 4k-क्रमmat, as cpa->mask* are set
	 * up accordingly.
	 */

	/* Clear PSE (aka _PAGE_PAT) and move PAT bit to correct position */
	req_prot = pgprot_large_2_4k(old_prot);

	pgprot_val(req_prot) &= ~pgprot_val(cpa->mask_clr);
	pgprot_val(req_prot) |= pgprot_val(cpa->mask_set);

	/*
	 * req_prot is in क्रमmat of 4k pages. It must be converted to large
	 * page क्रमmat: the caching mode includes the PAT bit located at
	 * dअगरferent bit positions in the two क्रमmats.
	 */
	req_prot = pgprot_4k_2_large(req_prot);
	req_prot = pgprot_clear_protnone_bits(req_prot);
	अगर (pgprot_val(req_prot) & _PAGE_PRESENT)
		pgprot_val(req_prot) |= _PAGE_PSE;

	/*
	 * old_pfn poपूर्णांकs to the large page base pfn. So we need to add the
	 * offset of the भव address:
	 */
	pfn = old_pfn + ((address & (psize - 1)) >> PAGE_SHIFT);
	cpa->pfn = pfn;

	/*
	 * Calculate the large page base address and the number of 4K pages
	 * in the large page
	 */
	lpaddr = address & pmask;
	numpages = psize >> PAGE_SHIFT;

	/*
	 * Sanity check that the existing mapping is correct versus the अटल
	 * protections. अटल_protections() guards against !PRESENT, so no
	 * extra conditional required here.
	 */
	chk_prot = अटल_protections(old_prot, lpaddr, old_pfn, numpages,
				      psize, CPA_CONFLICT);

	अगर (WARN_ON_ONCE(pgprot_val(chk_prot) != pgprot_val(old_prot))) अणु
		/*
		 * Split the large page and tell the split code to
		 * enक्रमce अटल protections.
		 */
		cpa->क्रमce_अटल_prot = 1;
		वापस 1;
	पूर्ण

	/*
	 * Optimization: If the requested pgprot is the same as the current
	 * pgprot, then the large page can be preserved and no updates are
	 * required independent of alignment and length of the requested
	 * range. The above alपढ़ोy established that the current pgprot is
	 * correct, which in consequence makes the requested pgprot correct
	 * as well अगर it is the same. The अटल protection scan below will
	 * not come to a dअगरferent conclusion.
	 */
	अगर (pgprot_val(req_prot) == pgprot_val(old_prot)) अणु
		cpa_inc_lp_sameprot(level);
		वापस 0;
	पूर्ण

	/*
	 * If the requested range करोes not cover the full page, split it up
	 */
	अगर (address != lpaddr || cpa->numpages != numpages)
		वापस 1;

	/*
	 * Check whether the requested pgprot is conflicting with a अटल
	 * protection requirement in the large page.
	 */
	new_prot = अटल_protections(req_prot, lpaddr, old_pfn, numpages,
				      psize, CPA_DETECT);

	/*
	 * If there is a conflict, split the large page.
	 *
	 * There used to be a 4k wise evaluation trying really hard to
	 * preserve the large pages, but experimentation has shown, that this
	 * करोes not help at all. There might be corner हालs which would
	 * preserve one large page occasionally, but it's really not worth the
	 * extra code and cycles क्रम the common हाल.
	 */
	अगर (pgprot_val(req_prot) != pgprot_val(new_prot))
		वापस 1;

	/* All checks passed. Update the large page mapping. */
	new_pte = pfn_pte(old_pfn, new_prot);
	__set_pmd_pte(kpte, address, new_pte);
	cpa->flags |= CPA_FLUSHTLB;
	cpa_inc_lp_preserved(level);
	वापस 0;
पूर्ण

अटल पूर्णांक should_split_large_page(pte_t *kpte, अचिन्हित दीर्घ address,
				   काष्ठा cpa_data *cpa)
अणु
	पूर्णांक करो_split;

	अगर (cpa->क्रमce_split)
		वापस 1;

	spin_lock(&pgd_lock);
	करो_split = __should_split_large_page(kpte, address, cpa);
	spin_unlock(&pgd_lock);

	वापस करो_split;
पूर्ण

अटल व्योम split_set_pte(काष्ठा cpa_data *cpa, pte_t *pte, अचिन्हित दीर्घ pfn,
			  pgprot_t ref_prot, अचिन्हित दीर्घ address,
			  अचिन्हित दीर्घ size)
अणु
	अचिन्हित पूर्णांक npg = PFN_DOWN(size);
	pgprot_t prot;

	/*
	 * If should_split_large_page() discovered an inconsistent mapping,
	 * हटाओ the invalid protection in the split mapping.
	 */
	अगर (!cpa->क्रमce_अटल_prot)
		जाओ set;

	/* Hand in lpsize = 0 to enक्रमce the protection mechanism */
	prot = अटल_protections(ref_prot, address, pfn, npg, 0, CPA_PROTECT);

	अगर (pgprot_val(prot) == pgprot_val(ref_prot))
		जाओ set;

	/*
	 * If this is splitting a PMD, fix it up. PUD splits cannot be
	 * fixed trivially as that would require to rescan the newly
	 * installed PMD mappings after वापसing from split_large_page()
	 * so an eventual further split can allocate the necessary PTE
	 * pages. Warn क्रम now and revisit it in हाल this actually
	 * happens.
	 */
	अगर (size == PAGE_SIZE)
		ref_prot = prot;
	अन्यथा
		pr_warn_once("CPA: Cannot fixup static protections for PUD split\n");
set:
	set_pte(pte, pfn_pte(pfn, ref_prot));
पूर्ण

अटल पूर्णांक
__split_large_page(काष्ठा cpa_data *cpa, pte_t *kpte, अचिन्हित दीर्घ address,
		   काष्ठा page *base)
अणु
	अचिन्हित दीर्घ lpaddr, lpinc, ref_pfn, pfn, pfninc = 1;
	pte_t *pbase = (pte_t *)page_address(base);
	अचिन्हित पूर्णांक i, level;
	pgprot_t ref_prot;
	pte_t *पंचांगp;

	spin_lock(&pgd_lock);
	/*
	 * Check क्रम races, another CPU might have split this page
	 * up क्रम us alपढ़ोy:
	 */
	पंचांगp = _lookup_address_cpa(cpa, address, &level);
	अगर (पंचांगp != kpte) अणु
		spin_unlock(&pgd_lock);
		वापस 1;
	पूर्ण

	paravirt_alloc_pte(&init_mm, page_to_pfn(base));

	चयन (level) अणु
	हाल PG_LEVEL_2M:
		ref_prot = pmd_pgprot(*(pmd_t *)kpte);
		/*
		 * Clear PSE (aka _PAGE_PAT) and move
		 * PAT bit to correct position.
		 */
		ref_prot = pgprot_large_2_4k(ref_prot);
		ref_pfn = pmd_pfn(*(pmd_t *)kpte);
		lpaddr = address & PMD_MASK;
		lpinc = PAGE_SIZE;
		अवरोध;

	हाल PG_LEVEL_1G:
		ref_prot = pud_pgprot(*(pud_t *)kpte);
		ref_pfn = pud_pfn(*(pud_t *)kpte);
		pfninc = PMD_PAGE_SIZE >> PAGE_SHIFT;
		lpaddr = address & PUD_MASK;
		lpinc = PMD_SIZE;
		/*
		 * Clear the PSE flags अगर the PRESENT flag is not set
		 * otherwise pmd_present/pmd_huge will वापस true
		 * even on a non present pmd.
		 */
		अगर (!(pgprot_val(ref_prot) & _PAGE_PRESENT))
			pgprot_val(ref_prot) &= ~_PAGE_PSE;
		अवरोध;

	शेष:
		spin_unlock(&pgd_lock);
		वापस 1;
	पूर्ण

	ref_prot = pgprot_clear_protnone_bits(ref_prot);

	/*
	 * Get the target pfn from the original entry:
	 */
	pfn = ref_pfn;
	क्रम (i = 0; i < PTRS_PER_PTE; i++, pfn += pfninc, lpaddr += lpinc)
		split_set_pte(cpa, pbase + i, pfn, ref_prot, lpaddr, lpinc);

	अगर (virt_addr_valid(address)) अणु
		अचिन्हित दीर्घ pfn = PFN_DOWN(__pa(address));

		अगर (pfn_range_is_mapped(pfn, pfn + 1))
			split_page_count(level);
	पूर्ण

	/*
	 * Install the new, split up pagetable.
	 *
	 * We use the standard kernel pagetable protections क्रम the new
	 * pagetable protections, the actual ptes set above control the
	 * primary protection behavior:
	 */
	__set_pmd_pte(kpte, address, mk_pte(base, __pgprot(_KERNPG_TABLE)));

	/*
	 * Do a global flush tlb after splitting the large page
	 * and beक्रमe we करो the actual change page attribute in the PTE.
	 *
	 * Without this, we violate the TLB application note, that says:
	 * "The TLBs may contain both ordinary and large-page
	 *  translations क्रम a 4-KByte range of linear addresses. This
	 *  may occur अगर software modअगरies the paging काष्ठाures so that
	 *  the page size used क्रम the address range changes. If the two
	 *  translations dअगरfer with respect to page frame or attributes
	 *  (e.g., permissions), processor behavior is undefined and may
	 *  be implementation-specअगरic."
	 *
	 * We करो this global tlb flush inside the cpa_lock, so that we
	 * करोn't allow any other cpu, with stale tlb entries change the
	 * page attribute in parallel, that also falls पूर्णांकo the
	 * just split large page entry.
	 */
	flush_tlb_all();
	spin_unlock(&pgd_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक split_large_page(काष्ठा cpa_data *cpa, pte_t *kpte,
			    अचिन्हित दीर्घ address)
अणु
	काष्ठा page *base;

	अगर (!debug_pagealloc_enabled())
		spin_unlock(&cpa_lock);
	base = alloc_pages(GFP_KERNEL, 0);
	अगर (!debug_pagealloc_enabled())
		spin_lock(&cpa_lock);
	अगर (!base)
		वापस -ENOMEM;

	अगर (__split_large_page(cpa, kpte, address, base))
		__मुक्त_page(base);

	वापस 0;
पूर्ण

अटल bool try_to_मुक्त_pte_page(pte_t *pte)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++)
		अगर (!pte_none(pte[i]))
			वापस false;

	मुक्त_page((अचिन्हित दीर्घ)pte);
	वापस true;
पूर्ण

अटल bool try_to_मुक्त_pmd_page(pmd_t *pmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PMD; i++)
		अगर (!pmd_none(pmd[i]))
			वापस false;

	मुक्त_page((अचिन्हित दीर्घ)pmd);
	वापस true;
पूर्ण

अटल bool unmap_pte_range(pmd_t *pmd, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pte_t *pte = pte_offset_kernel(pmd, start);

	जबतक (start < end) अणु
		set_pte(pte, __pte(0));

		start += PAGE_SIZE;
		pte++;
	पूर्ण

	अगर (try_to_मुक्त_pte_page((pte_t *)pmd_page_vaddr(*pmd))) अणु
		pmd_clear(pmd);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम __unmap_pmd_range(pud_t *pud, pmd_t *pmd,
			      अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (unmap_pte_range(pmd, start, end))
		अगर (try_to_मुक्त_pmd_page((pmd_t *)pud_page_vaddr(*pud)))
			pud_clear(pud);
पूर्ण

अटल व्योम unmap_pmd_range(pud_t *pud, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pmd_t *pmd = pmd_offset(pud, start);

	/*
	 * Not on a 2MB page boundary?
	 */
	अगर (start & (PMD_SIZE - 1)) अणु
		अचिन्हित दीर्घ next_page = (start + PMD_SIZE) & PMD_MASK;
		अचिन्हित दीर्घ pre_end = min_t(अचिन्हित दीर्घ, end, next_page);

		__unmap_pmd_range(pud, pmd, start, pre_end);

		start = pre_end;
		pmd++;
	पूर्ण

	/*
	 * Try to unmap in 2M chunks.
	 */
	जबतक (end - start >= PMD_SIZE) अणु
		अगर (pmd_large(*pmd))
			pmd_clear(pmd);
		अन्यथा
			__unmap_pmd_range(pud, pmd, start, start + PMD_SIZE);

		start += PMD_SIZE;
		pmd++;
	पूर्ण

	/*
	 * 4K leftovers?
	 */
	अगर (start < end)
		वापस __unmap_pmd_range(pud, pmd, start, end);

	/*
	 * Try again to मुक्त the PMD page अगर haven't succeeded above.
	 */
	अगर (!pud_none(*pud))
		अगर (try_to_मुक्त_pmd_page((pmd_t *)pud_page_vaddr(*pud)))
			pud_clear(pud);
पूर्ण

अटल व्योम unmap_pud_range(p4d_t *p4d, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pud_t *pud = pud_offset(p4d, start);

	/*
	 * Not on a GB page boundary?
	 */
	अगर (start & (PUD_SIZE - 1)) अणु
		अचिन्हित दीर्घ next_page = (start + PUD_SIZE) & PUD_MASK;
		अचिन्हित दीर्घ pre_end	= min_t(अचिन्हित दीर्घ, end, next_page);

		unmap_pmd_range(pud, start, pre_end);

		start = pre_end;
		pud++;
	पूर्ण

	/*
	 * Try to unmap in 1G chunks?
	 */
	जबतक (end - start >= PUD_SIZE) अणु

		अगर (pud_large(*pud))
			pud_clear(pud);
		अन्यथा
			unmap_pmd_range(pud, start, start + PUD_SIZE);

		start += PUD_SIZE;
		pud++;
	पूर्ण

	/*
	 * 2M leftovers?
	 */
	अगर (start < end)
		unmap_pmd_range(pud, start, end);

	/*
	 * No need to try to मुक्त the PUD page because we'll मुक्त it in
	 * populate_pgd's error path
	 */
पूर्ण

अटल पूर्णांक alloc_pte_page(pmd_t *pmd)
अणु
	pte_t *pte = (pte_t *)get_zeroed_page(GFP_KERNEL);
	अगर (!pte)
		वापस -1;

	set_pmd(pmd, __pmd(__pa(pte) | _KERNPG_TABLE));
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_pmd_page(pud_t *pud)
अणु
	pmd_t *pmd = (pmd_t *)get_zeroed_page(GFP_KERNEL);
	अगर (!pmd)
		वापस -1;

	set_pud(pud, __pud(__pa(pmd) | _KERNPG_TABLE));
	वापस 0;
पूर्ण

अटल व्योम populate_pte(काष्ठा cpa_data *cpa,
			 अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			 अचिन्हित num_pages, pmd_t *pmd, pgprot_t pgprot)
अणु
	pte_t *pte;

	pte = pte_offset_kernel(pmd, start);

	pgprot = pgprot_clear_protnone_bits(pgprot);

	जबतक (num_pages-- && start < end) अणु
		set_pte(pte, pfn_pte(cpa->pfn, pgprot));

		start	 += PAGE_SIZE;
		cpa->pfn++;
		pte++;
	पूर्ण
पूर्ण

अटल दीर्घ populate_pmd(काष्ठा cpa_data *cpa,
			 अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			 अचिन्हित num_pages, pud_t *pud, pgprot_t pgprot)
अणु
	दीर्घ cur_pages = 0;
	pmd_t *pmd;
	pgprot_t pmd_pgprot;

	/*
	 * Not on a 2M boundary?
	 */
	अगर (start & (PMD_SIZE - 1)) अणु
		अचिन्हित दीर्घ pre_end = start + (num_pages << PAGE_SHIFT);
		अचिन्हित दीर्घ next_page = (start + PMD_SIZE) & PMD_MASK;

		pre_end   = min_t(अचिन्हित दीर्घ, pre_end, next_page);
		cur_pages = (pre_end - start) >> PAGE_SHIFT;
		cur_pages = min_t(अचिन्हित पूर्णांक, num_pages, cur_pages);

		/*
		 * Need a PTE page?
		 */
		pmd = pmd_offset(pud, start);
		अगर (pmd_none(*pmd))
			अगर (alloc_pte_page(pmd))
				वापस -1;

		populate_pte(cpa, start, pre_end, cur_pages, pmd, pgprot);

		start = pre_end;
	पूर्ण

	/*
	 * We mapped them all?
	 */
	अगर (num_pages == cur_pages)
		वापस cur_pages;

	pmd_pgprot = pgprot_4k_2_large(pgprot);

	जबतक (end - start >= PMD_SIZE) अणु

		/*
		 * We cannot use a 1G page so allocate a PMD page अगर needed.
		 */
		अगर (pud_none(*pud))
			अगर (alloc_pmd_page(pud))
				वापस -1;

		pmd = pmd_offset(pud, start);

		set_pmd(pmd, pmd_mkhuge(pfn_pmd(cpa->pfn,
					canon_pgprot(pmd_pgprot))));

		start	  += PMD_SIZE;
		cpa->pfn  += PMD_SIZE >> PAGE_SHIFT;
		cur_pages += PMD_SIZE >> PAGE_SHIFT;
	पूर्ण

	/*
	 * Map trailing 4K pages.
	 */
	अगर (start < end) अणु
		pmd = pmd_offset(pud, start);
		अगर (pmd_none(*pmd))
			अगर (alloc_pte_page(pmd))
				वापस -1;

		populate_pte(cpa, start, end, num_pages - cur_pages,
			     pmd, pgprot);
	पूर्ण
	वापस num_pages;
पूर्ण

अटल पूर्णांक populate_pud(काष्ठा cpa_data *cpa, अचिन्हित दीर्घ start, p4d_t *p4d,
			pgprot_t pgprot)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ end;
	दीर्घ cur_pages = 0;
	pgprot_t pud_pgprot;

	end = start + (cpa->numpages << PAGE_SHIFT);

	/*
	 * Not on a Gb page boundary? => map everything up to it with
	 * smaller pages.
	 */
	अगर (start & (PUD_SIZE - 1)) अणु
		अचिन्हित दीर्घ pre_end;
		अचिन्हित दीर्घ next_page = (start + PUD_SIZE) & PUD_MASK;

		pre_end   = min_t(अचिन्हित दीर्घ, end, next_page);
		cur_pages = (pre_end - start) >> PAGE_SHIFT;
		cur_pages = min_t(पूर्णांक, (पूर्णांक)cpa->numpages, cur_pages);

		pud = pud_offset(p4d, start);

		/*
		 * Need a PMD page?
		 */
		अगर (pud_none(*pud))
			अगर (alloc_pmd_page(pud))
				वापस -1;

		cur_pages = populate_pmd(cpa, start, pre_end, cur_pages,
					 pud, pgprot);
		अगर (cur_pages < 0)
			वापस cur_pages;

		start = pre_end;
	पूर्ण

	/* We mapped them all? */
	अगर (cpa->numpages == cur_pages)
		वापस cur_pages;

	pud = pud_offset(p4d, start);
	pud_pgprot = pgprot_4k_2_large(pgprot);

	/*
	 * Map everything starting from the Gb boundary, possibly with 1G pages
	 */
	जबतक (boot_cpu_has(X86_FEATURE_GBPAGES) && end - start >= PUD_SIZE) अणु
		set_pud(pud, pud_mkhuge(pfn_pud(cpa->pfn,
				   canon_pgprot(pud_pgprot))));

		start	  += PUD_SIZE;
		cpa->pfn  += PUD_SIZE >> PAGE_SHIFT;
		cur_pages += PUD_SIZE >> PAGE_SHIFT;
		pud++;
	पूर्ण

	/* Map trailing leftover */
	अगर (start < end) अणु
		दीर्घ पंचांगp;

		pud = pud_offset(p4d, start);
		अगर (pud_none(*pud))
			अगर (alloc_pmd_page(pud))
				वापस -1;

		पंचांगp = populate_pmd(cpa, start, end, cpa->numpages - cur_pages,
				   pud, pgprot);
		अगर (पंचांगp < 0)
			वापस cur_pages;

		cur_pages += पंचांगp;
	पूर्ण
	वापस cur_pages;
पूर्ण

/*
 * Restrictions क्रम kernel page table करो not necessarily apply when mapping in
 * an alternate PGD.
 */
अटल पूर्णांक populate_pgd(काष्ठा cpa_data *cpa, अचिन्हित दीर्घ addr)
अणु
	pgprot_t pgprot = __pgprot(_KERNPG_TABLE);
	pud_t *pud = शून्य;	/* shut up gcc */
	p4d_t *p4d;
	pgd_t *pgd_entry;
	दीर्घ ret;

	pgd_entry = cpa->pgd + pgd_index(addr);

	अगर (pgd_none(*pgd_entry)) अणु
		p4d = (p4d_t *)get_zeroed_page(GFP_KERNEL);
		अगर (!p4d)
			वापस -1;

		set_pgd(pgd_entry, __pgd(__pa(p4d) | _KERNPG_TABLE));
	पूर्ण

	/*
	 * Allocate a PUD page and hand it करोwn क्रम mapping.
	 */
	p4d = p4d_offset(pgd_entry, addr);
	अगर (p4d_none(*p4d)) अणु
		pud = (pud_t *)get_zeroed_page(GFP_KERNEL);
		अगर (!pud)
			वापस -1;

		set_p4d(p4d, __p4d(__pa(pud) | _KERNPG_TABLE));
	पूर्ण

	pgprot_val(pgprot) &= ~pgprot_val(cpa->mask_clr);
	pgprot_val(pgprot) |=  pgprot_val(cpa->mask_set);

	ret = populate_pud(cpa, addr, p4d, pgprot);
	अगर (ret < 0) अणु
		/*
		 * Leave the PUD page in place in हाल some other CPU or thपढ़ो
		 * alपढ़ोy found it, but हटाओ any useless entries we just
		 * added to it.
		 */
		unmap_pud_range(p4d, addr,
				addr + (cpa->numpages << PAGE_SHIFT));
		वापस ret;
	पूर्ण

	cpa->numpages = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक __cpa_process_fault(काष्ठा cpa_data *cpa, अचिन्हित दीर्घ vaddr,
			       पूर्णांक primary)
अणु
	अगर (cpa->pgd) अणु
		/*
		 * Right now, we only execute this code path when mapping
		 * the EFI भव memory map regions, no other users
		 * provide a ->pgd value. This may change in the future.
		 */
		वापस populate_pgd(cpa, vaddr);
	पूर्ण

	/*
	 * Ignore all non primary paths.
	 */
	अगर (!primary) अणु
		cpa->numpages = 1;
		वापस 0;
	पूर्ण

	/*
	 * Ignore the शून्य PTE क्रम kernel identity mapping, as it is expected
	 * to have holes.
	 * Also set numpages to '1' indicating that we processed cpa req क्रम
	 * one भव address page and its pfn. TBD: numpages can be set based
	 * on the initial value and the level वापसed by lookup_address().
	 */
	अगर (within(vaddr, PAGE_OFFSET,
		   PAGE_OFFSET + (max_pfn_mapped << PAGE_SHIFT))) अणु
		cpa->numpages = 1;
		cpa->pfn = __pa(vaddr) >> PAGE_SHIFT;
		वापस 0;

	पूर्ण अन्यथा अगर (__cpa_pfn_in_highmap(cpa->pfn)) अणु
		/* Faults in the highmap are OK, so करो not warn: */
		वापस -EFAULT;
	पूर्ण अन्यथा अणु
		WARN(1, KERN_WARNING "CPA: called for zero pte. "
			"vaddr = %lx cpa->vaddr = %lx\n", vaddr,
			*cpa->vaddr);

		वापस -EFAULT;
	पूर्ण
पूर्ण

अटल पूर्णांक __change_page_attr(काष्ठा cpa_data *cpa, पूर्णांक primary)
अणु
	अचिन्हित दीर्घ address;
	पूर्णांक करो_split, err;
	अचिन्हित पूर्णांक level;
	pte_t *kpte, old_pte;

	address = __cpa_addr(cpa, cpa->curpage);
repeat:
	kpte = _lookup_address_cpa(cpa, address, &level);
	अगर (!kpte)
		वापस __cpa_process_fault(cpa, address, primary);

	old_pte = *kpte;
	अगर (pte_none(old_pte))
		वापस __cpa_process_fault(cpa, address, primary);

	अगर (level == PG_LEVEL_4K) अणु
		pte_t new_pte;
		pgprot_t new_prot = pte_pgprot(old_pte);
		अचिन्हित दीर्घ pfn = pte_pfn(old_pte);

		pgprot_val(new_prot) &= ~pgprot_val(cpa->mask_clr);
		pgprot_val(new_prot) |= pgprot_val(cpa->mask_set);

		cpa_inc_4k_install();
		/* Hand in lpsize = 0 to enक्रमce the protection mechanism */
		new_prot = अटल_protections(new_prot, address, pfn, 1, 0,
					      CPA_PROTECT);

		new_prot = pgprot_clear_protnone_bits(new_prot);

		/*
		 * We need to keep the pfn from the existing PTE,
		 * after all we're only going to change it's attributes
		 * not the memory it poपूर्णांकs to
		 */
		new_pte = pfn_pte(pfn, new_prot);
		cpa->pfn = pfn;
		/*
		 * Do we really change anything ?
		 */
		अगर (pte_val(old_pte) != pte_val(new_pte)) अणु
			set_pte_atomic(kpte, new_pte);
			cpa->flags |= CPA_FLUSHTLB;
		पूर्ण
		cpa->numpages = 1;
		वापस 0;
	पूर्ण

	/*
	 * Check, whether we can keep the large page पूर्णांकact
	 * and just change the pte:
	 */
	करो_split = should_split_large_page(kpte, address, cpa);
	/*
	 * When the range fits पूर्णांकo the existing large page,
	 * वापस. cp->numpages and cpa->tlbflush have been updated in
	 * try_large_page:
	 */
	अगर (करो_split <= 0)
		वापस करो_split;

	/*
	 * We have to split the large page:
	 */
	err = split_large_page(cpa, kpte, address);
	अगर (!err)
		जाओ repeat;

	वापस err;
पूर्ण

अटल पूर्णांक __change_page_attr_set_clr(काष्ठा cpa_data *cpa, पूर्णांक checkalias);

अटल पूर्णांक cpa_process_alias(काष्ठा cpa_data *cpa)
अणु
	काष्ठा cpa_data alias_cpa;
	अचिन्हित दीर्घ laddr = (अचिन्हित दीर्घ)__va(cpa->pfn << PAGE_SHIFT);
	अचिन्हित दीर्घ vaddr;
	पूर्णांक ret;

	अगर (!pfn_range_is_mapped(cpa->pfn, cpa->pfn + 1))
		वापस 0;

	/*
	 * No need to reकरो, when the primary call touched the direct
	 * mapping alपढ़ोy:
	 */
	vaddr = __cpa_addr(cpa, cpa->curpage);
	अगर (!(within(vaddr, PAGE_OFFSET,
		    PAGE_OFFSET + (max_pfn_mapped << PAGE_SHIFT)))) अणु

		alias_cpa = *cpa;
		alias_cpa.vaddr = &laddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);
		alias_cpa.curpage = 0;

		cpa->क्रमce_flush_all = 1;

		ret = __change_page_attr_set_clr(&alias_cpa, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_X86_64
	/*
	 * If the primary call didn't touch the high mapping alपढ़ोy
	 * and the physical address is inside the kernel map, we need
	 * to touch the high mapped kernel as well:
	 */
	अगर (!within(vaddr, (अचिन्हित दीर्घ)_text, _brk_end) &&
	    __cpa_pfn_in_highmap(cpa->pfn)) अणु
		अचिन्हित दीर्घ temp_cpa_vaddr = (cpa->pfn << PAGE_SHIFT) +
					       __START_KERNEL_map - phys_base;
		alias_cpa = *cpa;
		alias_cpa.vaddr = &temp_cpa_vaddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);
		alias_cpa.curpage = 0;

		cpa->क्रमce_flush_all = 1;
		/*
		 * The high mapping range is imprecise, so ignore the
		 * वापस value.
		 */
		__change_page_attr_set_clr(&alias_cpa, 0);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक __change_page_attr_set_clr(काष्ठा cpa_data *cpa, पूर्णांक checkalias)
अणु
	अचिन्हित दीर्घ numpages = cpa->numpages;
	अचिन्हित दीर्घ rempages = numpages;
	पूर्णांक ret = 0;

	जबतक (rempages) अणु
		/*
		 * Store the reमुख्यing nr of pages क्रम the large page
		 * preservation check.
		 */
		cpa->numpages = rempages;
		/* क्रम array changes, we can't use large page */
		अगर (cpa->flags & (CPA_ARRAY | CPA_PAGES_ARRAY))
			cpa->numpages = 1;

		अगर (!debug_pagealloc_enabled())
			spin_lock(&cpa_lock);
		ret = __change_page_attr(cpa, checkalias);
		अगर (!debug_pagealloc_enabled())
			spin_unlock(&cpa_lock);
		अगर (ret)
			जाओ out;

		अगर (checkalias) अणु
			ret = cpa_process_alias(cpa);
			अगर (ret)
				जाओ out;
		पूर्ण

		/*
		 * Adjust the number of pages with the result of the
		 * CPA operation. Either a large page has been
		 * preserved or a single page update happened.
		 */
		BUG_ON(cpa->numpages > rempages || !cpa->numpages);
		rempages -= cpa->numpages;
		cpa->curpage += cpa->numpages;
	पूर्ण

out:
	/* Restore the original numpages */
	cpa->numpages = numpages;
	वापस ret;
पूर्ण

अटल पूर्णांक change_page_attr_set_clr(अचिन्हित दीर्घ *addr, पूर्णांक numpages,
				    pgprot_t mask_set, pgprot_t mask_clr,
				    पूर्णांक क्रमce_split, पूर्णांक in_flag,
				    काष्ठा page **pages)
अणु
	काष्ठा cpa_data cpa;
	पूर्णांक ret, cache, checkalias;

	स_रखो(&cpa, 0, माप(cpa));

	/*
	 * Check, अगर we are requested to set a not supported
	 * feature.  Clearing non-supported features is OK.
	 */
	mask_set = canon_pgprot(mask_set);

	अगर (!pgprot_val(mask_set) && !pgprot_val(mask_clr) && !क्रमce_split)
		वापस 0;

	/* Ensure we are PAGE_SIZE aligned */
	अगर (in_flag & CPA_ARRAY) अणु
		पूर्णांक i;
		क्रम (i = 0; i < numpages; i++) अणु
			अगर (addr[i] & ~PAGE_MASK) अणु
				addr[i] &= PAGE_MASK;
				WARN_ON_ONCE(1);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!(in_flag & CPA_PAGES_ARRAY)) अणु
		/*
		 * in_flag of CPA_PAGES_ARRAY implies it is aligned.
		 * No need to check in that हाल
		 */
		अगर (*addr & ~PAGE_MASK) अणु
			*addr &= PAGE_MASK;
			/*
			 * People should not be passing in unaligned addresses:
			 */
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण

	/* Must aव्योम aliasing mappings in the highmem code */
	kmap_flush_unused();

	vm_unmap_aliases();

	cpa.vaddr = addr;
	cpa.pages = pages;
	cpa.numpages = numpages;
	cpa.mask_set = mask_set;
	cpa.mask_clr = mask_clr;
	cpa.flags = 0;
	cpa.curpage = 0;
	cpa.क्रमce_split = क्रमce_split;

	अगर (in_flag & (CPA_ARRAY | CPA_PAGES_ARRAY))
		cpa.flags |= in_flag;

	/* No alias checking क्रम _NX bit modअगरications */
	checkalias = (pgprot_val(mask_set) | pgprot_val(mask_clr)) != _PAGE_NX;
	/* Has caller explicitly disabled alias checking? */
	अगर (in_flag & CPA_NO_CHECK_ALIAS)
		checkalias = 0;

	ret = __change_page_attr_set_clr(&cpa, checkalias);

	/*
	 * Check whether we really changed something:
	 */
	अगर (!(cpa.flags & CPA_FLUSHTLB))
		जाओ out;

	/*
	 * No need to flush, when we did not set any of the caching
	 * attributes:
	 */
	cache = !!pgprot2cachemode(mask_set);

	/*
	 * On error; flush everything to be sure.
	 */
	अगर (ret) अणु
		cpa_flush_all(cache);
		जाओ out;
	पूर्ण

	cpa_flush(&cpa, cache);
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक change_page_attr_set(अचिन्हित दीर्घ *addr, पूर्णांक numpages,
				       pgprot_t mask, पूर्णांक array)
अणु
	वापस change_page_attr_set_clr(addr, numpages, mask, __pgprot(0), 0,
		(array ? CPA_ARRAY : 0), शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक change_page_attr_clear(अचिन्हित दीर्घ *addr, पूर्णांक numpages,
					 pgprot_t mask, पूर्णांक array)
अणु
	वापस change_page_attr_set_clr(addr, numpages, __pgprot(0), mask, 0,
		(array ? CPA_ARRAY : 0), शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक cpa_set_pages_array(काष्ठा page **pages, पूर्णांक numpages,
				       pgprot_t mask)
अणु
	वापस change_page_attr_set_clr(शून्य, numpages, mask, __pgprot(0), 0,
		CPA_PAGES_ARRAY, pages);
पूर्ण

अटल अंतरभूत पूर्णांक cpa_clear_pages_array(काष्ठा page **pages, पूर्णांक numpages,
					 pgprot_t mask)
अणु
	वापस change_page_attr_set_clr(शून्य, numpages, __pgprot(0), mask, 0,
		CPA_PAGES_ARRAY, pages);
पूर्ण

/*
 * _set_memory_prot is an पूर्णांकernal helper क्रम callers that have been passed
 * a pgprot_t value from upper layers and a reservation has alपढ़ोy been taken.
 * If you want to set the pgprot to a specअगरic page protocol, use the
 * set_memory_xx() functions.
 */
पूर्णांक __set_memory_prot(अचिन्हित दीर्घ addr, पूर्णांक numpages, pgprot_t prot)
अणु
	वापस change_page_attr_set_clr(&addr, numpages, prot,
					__pgprot(~pgprot_val(prot)), 0, 0,
					शून्य);
पूर्ण

पूर्णांक _set_memory_uc(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	/*
	 * क्रम now UC MINUS. see comments in ioremap()
	 * If you really need strong UC use ioremap_uc(), but note
	 * that you cannot override IO areas with set_memory_*() as
	 * these helpers cannot work with IO memory.
	 */
	वापस change_page_attr_set(&addr, numpages,
				    cachemode2pgprot(_PAGE_CACHE_MODE_UC_MINUS),
				    0);
पूर्ण

पूर्णांक set_memory_uc(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	पूर्णांक ret;

	/*
	 * क्रम now UC MINUS. see comments in ioremap()
	 */
	ret = memtype_reserve(__pa(addr), __pa(addr) + numpages * PAGE_SIZE,
			      _PAGE_CACHE_MODE_UC_MINUS, शून्य);
	अगर (ret)
		जाओ out_err;

	ret = _set_memory_uc(addr, numpages);
	अगर (ret)
		जाओ out_मुक्त;

	वापस 0;

out_मुक्त:
	memtype_मुक्त(__pa(addr), __pa(addr) + numpages * PAGE_SIZE);
out_err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(set_memory_uc);

पूर्णांक _set_memory_wc(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	पूर्णांक ret;

	ret = change_page_attr_set(&addr, numpages,
				   cachemode2pgprot(_PAGE_CACHE_MODE_UC_MINUS),
				   0);
	अगर (!ret) अणु
		ret = change_page_attr_set_clr(&addr, numpages,
					       cachemode2pgprot(_PAGE_CACHE_MODE_WC),
					       __pgprot(_PAGE_CACHE_MASK),
					       0, 0, शून्य);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक set_memory_wc(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	पूर्णांक ret;

	ret = memtype_reserve(__pa(addr), __pa(addr) + numpages * PAGE_SIZE,
		_PAGE_CACHE_MODE_WC, शून्य);
	अगर (ret)
		वापस ret;

	ret = _set_memory_wc(addr, numpages);
	अगर (ret)
		memtype_मुक्त(__pa(addr), __pa(addr) + numpages * PAGE_SIZE);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(set_memory_wc);

पूर्णांक _set_memory_wt(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_page_attr_set(&addr, numpages,
				    cachemode2pgprot(_PAGE_CACHE_MODE_WT), 0);
पूर्ण

पूर्णांक _set_memory_wb(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	/* WB cache mode is hard wired to all cache attribute bits being 0 */
	वापस change_page_attr_clear(&addr, numpages,
				      __pgprot(_PAGE_CACHE_MASK), 0);
पूर्ण

पूर्णांक set_memory_wb(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	पूर्णांक ret;

	ret = _set_memory_wb(addr, numpages);
	अगर (ret)
		वापस ret;

	memtype_मुक्त(__pa(addr), __pa(addr) + numpages * PAGE_SIZE);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(set_memory_wb);

पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	अगर (!(__supported_pte_mask & _PAGE_NX))
		वापस 0;

	वापस change_page_attr_clear(&addr, numpages, __pgprot(_PAGE_NX), 0);
पूर्ण

पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	अगर (!(__supported_pte_mask & _PAGE_NX))
		वापस 0;

	वापस change_page_attr_set(&addr, numpages, __pgprot(_PAGE_NX), 0);
पूर्ण

पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_page_attr_clear(&addr, numpages, __pgprot(_PAGE_RW), 0);
पूर्ण

पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_page_attr_set(&addr, numpages, __pgprot(_PAGE_RW), 0);
पूर्ण

पूर्णांक set_memory_np(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_page_attr_clear(&addr, numpages, __pgprot(_PAGE_PRESENT), 0);
पूर्ण

पूर्णांक set_memory_np_noalias(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	पूर्णांक cpa_flags = CPA_NO_CHECK_ALIAS;

	वापस change_page_attr_set_clr(&addr, numpages, __pgprot(0),
					__pgprot(_PAGE_PRESENT), 0,
					cpa_flags, शून्य);
पूर्ण

पूर्णांक set_memory_4k(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_page_attr_set_clr(&addr, numpages, __pgprot(0),
					__pgprot(0), 1, 0, शून्य);
पूर्ण

पूर्णांक set_memory_nonglobal(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_page_attr_clear(&addr, numpages,
				      __pgprot(_PAGE_GLOBAL), 0);
पूर्ण

पूर्णांक set_memory_global(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_page_attr_set(&addr, numpages,
				    __pgprot(_PAGE_GLOBAL), 0);
पूर्ण

अटल पूर्णांक __set_memory_enc_dec(अचिन्हित दीर्घ addr, पूर्णांक numpages, bool enc)
अणु
	काष्ठा cpa_data cpa;
	पूर्णांक ret;

	/* Nothing to करो अगर memory encryption is not active */
	अगर (!mem_encrypt_active())
		वापस 0;

	/* Should not be working on unaligned addresses */
	अगर (WARN_ONCE(addr & ~PAGE_MASK, "misaligned address: %#lx\n", addr))
		addr &= PAGE_MASK;

	स_रखो(&cpa, 0, माप(cpa));
	cpa.vaddr = &addr;
	cpa.numpages = numpages;
	cpa.mask_set = enc ? __pgprot(_PAGE_ENC) : __pgprot(0);
	cpa.mask_clr = enc ? __pgprot(0) : __pgprot(_PAGE_ENC);
	cpa.pgd = init_mm.pgd;

	/* Must aव्योम aliasing mappings in the highmem code */
	kmap_flush_unused();
	vm_unmap_aliases();

	/*
	 * Beक्रमe changing the encryption attribute, we need to flush caches.
	 */
	cpa_flush(&cpa, !this_cpu_has(X86_FEATURE_SME_COHERENT));

	ret = __change_page_attr_set_clr(&cpa, 1);

	/*
	 * After changing the encryption attribute, we need to flush TLBs again
	 * in हाल any speculative TLB caching occurred (but no need to flush
	 * caches again).  We could just use cpa_flush_all(), but in हाल TLB
	 * flushing माला_लो optimized in the cpa_flush() path use the same logic
	 * as above.
	 */
	cpa_flush(&cpa, 0);

	वापस ret;
पूर्ण

पूर्णांक set_memory_encrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory_enc_dec(addr, numpages, true);
पूर्ण
EXPORT_SYMBOL_GPL(set_memory_encrypted);

पूर्णांक set_memory_decrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory_enc_dec(addr, numpages, false);
पूर्ण
EXPORT_SYMBOL_GPL(set_memory_decrypted);

पूर्णांक set_pages_uc(काष्ठा page *page, पूर्णांक numpages)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);

	वापस set_memory_uc(addr, numpages);
पूर्ण
EXPORT_SYMBOL(set_pages_uc);

अटल पूर्णांक _set_pages_array(काष्ठा page **pages, पूर्णांक numpages,
		क्रमागत page_cache_mode new_type)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	क्रमागत page_cache_mode set_type;
	पूर्णांक i;
	पूर्णांक मुक्त_idx;
	पूर्णांक ret;

	क्रम (i = 0; i < numpages; i++) अणु
		अगर (PageHighMem(pages[i]))
			जारी;
		start = page_to_pfn(pages[i]) << PAGE_SHIFT;
		end = start + PAGE_SIZE;
		अगर (memtype_reserve(start, end, new_type, शून्य))
			जाओ err_out;
	पूर्ण

	/* If WC, set to UC- first and then WC */
	set_type = (new_type == _PAGE_CACHE_MODE_WC) ?
				_PAGE_CACHE_MODE_UC_MINUS : new_type;

	ret = cpa_set_pages_array(pages, numpages,
				  cachemode2pgprot(set_type));
	अगर (!ret && new_type == _PAGE_CACHE_MODE_WC)
		ret = change_page_attr_set_clr(शून्य, numpages,
					       cachemode2pgprot(
						_PAGE_CACHE_MODE_WC),
					       __pgprot(_PAGE_CACHE_MASK),
					       0, CPA_PAGES_ARRAY, pages);
	अगर (ret)
		जाओ err_out;
	वापस 0; /* Success */
err_out:
	मुक्त_idx = i;
	क्रम (i = 0; i < मुक्त_idx; i++) अणु
		अगर (PageHighMem(pages[i]))
			जारी;
		start = page_to_pfn(pages[i]) << PAGE_SHIFT;
		end = start + PAGE_SIZE;
		memtype_मुक्त(start, end);
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक set_pages_array_uc(काष्ठा page **pages, पूर्णांक numpages)
अणु
	वापस _set_pages_array(pages, numpages, _PAGE_CACHE_MODE_UC_MINUS);
पूर्ण
EXPORT_SYMBOL(set_pages_array_uc);

पूर्णांक set_pages_array_wc(काष्ठा page **pages, पूर्णांक numpages)
अणु
	वापस _set_pages_array(pages, numpages, _PAGE_CACHE_MODE_WC);
पूर्ण
EXPORT_SYMBOL(set_pages_array_wc);

पूर्णांक set_pages_array_wt(काष्ठा page **pages, पूर्णांक numpages)
अणु
	वापस _set_pages_array(pages, numpages, _PAGE_CACHE_MODE_WT);
पूर्ण
EXPORT_SYMBOL_GPL(set_pages_array_wt);

पूर्णांक set_pages_wb(काष्ठा page *page, पूर्णांक numpages)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);

	वापस set_memory_wb(addr, numpages);
पूर्ण
EXPORT_SYMBOL(set_pages_wb);

पूर्णांक set_pages_array_wb(काष्ठा page **pages, पूर्णांक numpages)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	पूर्णांक i;

	/* WB cache mode is hard wired to all cache attribute bits being 0 */
	retval = cpa_clear_pages_array(pages, numpages,
			__pgprot(_PAGE_CACHE_MASK));
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < numpages; i++) अणु
		अगर (PageHighMem(pages[i]))
			जारी;
		start = page_to_pfn(pages[i]) << PAGE_SHIFT;
		end = start + PAGE_SIZE;
		memtype_मुक्त(start, end);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(set_pages_array_wb);

पूर्णांक set_pages_ro(काष्ठा page *page, पूर्णांक numpages)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);

	वापस set_memory_ro(addr, numpages);
पूर्ण

पूर्णांक set_pages_rw(काष्ठा page *page, पूर्णांक numpages)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);

	वापस set_memory_rw(addr, numpages);
पूर्ण

अटल पूर्णांक __set_pages_p(काष्ठा page *page, पूर्णांक numpages)
अणु
	अचिन्हित दीर्घ tempaddr = (अचिन्हित दीर्घ) page_address(page);
	काष्ठा cpa_data cpa = अणु .vaddr = &tempaddr,
				.pgd = शून्य,
				.numpages = numpages,
				.mask_set = __pgprot(_PAGE_PRESENT | _PAGE_RW),
				.mask_clr = __pgprot(0),
				.flags = 0पूर्ण;

	/*
	 * No alias checking needed क्रम setting present flag. otherwise,
	 * we may need to अवरोध large pages क्रम 64-bit kernel text
	 * mappings (this adds to complनिकासy अगर we want to करो this from
	 * atomic context especially). Let's keep it simple!
	 */
	वापस __change_page_attr_set_clr(&cpa, 0);
पूर्ण

अटल पूर्णांक __set_pages_np(काष्ठा page *page, पूर्णांक numpages)
अणु
	अचिन्हित दीर्घ tempaddr = (अचिन्हित दीर्घ) page_address(page);
	काष्ठा cpa_data cpa = अणु .vaddr = &tempaddr,
				.pgd = शून्य,
				.numpages = numpages,
				.mask_set = __pgprot(0),
				.mask_clr = __pgprot(_PAGE_PRESENT | _PAGE_RW),
				.flags = 0पूर्ण;

	/*
	 * No alias checking needed क्रम setting not present flag. otherwise,
	 * we may need to अवरोध large pages क्रम 64-bit kernel text
	 * mappings (this adds to complनिकासy अगर we want to करो this from
	 * atomic context especially). Let's keep it simple!
	 */
	वापस __change_page_attr_set_clr(&cpa, 0);
पूर्ण

पूर्णांक set_direct_map_invalid_noflush(काष्ठा page *page)
अणु
	वापस __set_pages_np(page, 1);
पूर्ण

पूर्णांक set_direct_map_शेष_noflush(काष्ठा page *page)
अणु
	वापस __set_pages_p(page, 1);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	अगर (PageHighMem(page))
		वापस;
	अगर (!enable) अणु
		debug_check_no_locks_मुक्तd(page_address(page),
					   numpages * PAGE_SIZE);
	पूर्ण

	/*
	 * The वापस value is ignored as the calls cannot fail.
	 * Large pages क्रम identity mappings are not used at boot समय
	 * and hence no memory allocations during large page split.
	 */
	अगर (enable)
		__set_pages_p(page, numpages);
	अन्यथा
		__set_pages_np(page, numpages);

	/*
	 * We should perक्रमm an IPI and flush all tlbs,
	 * but that can deadlock->flush only current cpu.
	 * Preemption needs to be disabled around __flush_tlb_all() due to
	 * CR3 reload in __native_flush_tlb().
	 */
	preempt_disable();
	__flush_tlb_all();
	preempt_enable();

	arch_flush_lazy_mmu_mode();
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */

bool kernel_page_present(काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक level;
	pte_t *pte;

	अगर (PageHighMem(page))
		वापस false;

	pte = lookup_address((अचिन्हित दीर्घ)page_address(page), &level);
	वापस (pte_val(*pte) & _PAGE_PRESENT);
पूर्ण

पूर्णांक __init kernel_map_pages_in_pgd(pgd_t *pgd, u64 pfn, अचिन्हित दीर्घ address,
				   अचिन्हित numpages, अचिन्हित दीर्घ page_flags)
अणु
	पूर्णांक retval = -EINVAL;

	काष्ठा cpa_data cpa = अणु
		.vaddr = &address,
		.pfn = pfn,
		.pgd = pgd,
		.numpages = numpages,
		.mask_set = __pgprot(0),
		.mask_clr = __pgprot(~page_flags & (_PAGE_NX|_PAGE_RW)),
		.flags = 0,
	पूर्ण;

	WARN_ONCE(num_online_cpus() > 1, "Don't call after initializing SMP");

	अगर (!(__supported_pte_mask & _PAGE_NX))
		जाओ out;

	अगर (!(page_flags & _PAGE_ENC))
		cpa.mask_clr = pgprot_encrypted(cpa.mask_clr);

	cpa.mask_set = __pgprot(_PAGE_PRESENT | page_flags);

	retval = __change_page_attr_set_clr(&cpa, 0);
	__flush_tlb_all();

out:
	वापस retval;
पूर्ण

/*
 * __flush_tlb_all() flushes mappings only on current CPU and hence this
 * function shouldn't be used in an SMP environment. Presently, it's used only
 * during boot (way beक्रमe smp_init()) by EFI subप्रणाली and hence is ok.
 */
पूर्णांक __init kernel_unmap_pages_in_pgd(pgd_t *pgd, अचिन्हित दीर्घ address,
				     अचिन्हित दीर्घ numpages)
अणु
	पूर्णांक retval;

	/*
	 * The typical sequence क्रम unmapping is to find a pte through
	 * lookup_address_in_pgd() (ideally, it should never वापस शून्य because
	 * the address is alपढ़ोy mapped) and change it's protections. As pfn is
	 * the *target* of a mapping, it's not useful जबतक unmapping.
	 */
	काष्ठा cpa_data cpa = अणु
		.vaddr		= &address,
		.pfn		= 0,
		.pgd		= pgd,
		.numpages	= numpages,
		.mask_set	= __pgprot(0),
		.mask_clr	= __pgprot(_PAGE_PRESENT | _PAGE_RW),
		.flags		= 0,
	पूर्ण;

	WARN_ONCE(num_online_cpus() > 1, "Don't call after initializing SMP");

	retval = __change_page_attr_set_clr(&cpa, 0);
	__flush_tlb_all();

	वापस retval;
पूर्ण

/*
 * The testहालs use पूर्णांकernal knowledge of the implementation that shouldn't
 * be exposed to the rest of the kernel. Include these directly here.
 */
#अगर_घोषित CONFIG_CPA_DEBUG
#समावेश "cpa-test.c"
#पूर्ण_अगर
