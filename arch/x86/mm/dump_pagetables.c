<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Debug helper to dump the current kernel pagetables of the प्रणाली
 * so that we can see what the various memory ranges are set to.
 *
 * (C) Copyright 2008 Intel Corporation
 *
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kasan.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pci.h>
#समावेश <linux/ptdump.h>

#समावेश <यंत्र/e820/types.h>

/*
 * The dumper groups pagetable entries of the same type पूर्णांकo one, and क्रम
 * that it needs to keep some state when walking, and flush this state
 * when a "break" in the continuity is found.
 */
काष्ठा pg_state अणु
	काष्ठा ptdump_state ptdump;
	पूर्णांक level;
	pgprotval_t current_prot;
	pgprotval_t effective_prot;
	pgprotval_t prot_levels[5];
	अचिन्हित दीर्घ start_address;
	स्थिर काष्ठा addr_marker *marker;
	अचिन्हित दीर्घ lines;
	bool to_dmesg;
	bool check_wx;
	अचिन्हित दीर्घ wx_pages;
	काष्ठा seq_file *seq;
पूर्ण;

काष्ठा addr_marker अणु
	अचिन्हित दीर्घ start_address;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ max_lines;
पूर्ण;

/* Address space markers hपूर्णांकs */

#अगर_घोषित CONFIG_X86_64

क्रमागत address_markers_idx अणु
	USER_SPACE_NR = 0,
	KERNEL_SPACE_NR,
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	LDT_NR,
#पूर्ण_अगर
	LOW_KERNEL_NR,
	VMALLOC_START_NR,
	VMEMMAP_START_NR,
#अगर_घोषित CONFIG_KASAN
	KASAN_SHADOW_START_NR,
	KASAN_SHADOW_END_NR,
#पूर्ण_अगर
	CPU_ENTRY_AREA_NR,
#अगर_घोषित CONFIG_X86_ESPFIX64
	ESPFIX_START_NR,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EFI
	EFI_END_NR,
#पूर्ण_अगर
	HIGH_KERNEL_NR,
	MODULES_VADDR_NR,
	MODULES_END_NR,
	FIXADDR_START_NR,
	END_OF_SPACE_NR,
पूर्ण;

अटल काष्ठा addr_marker address_markers[] = अणु
	[USER_SPACE_NR]		= अणु 0,			"User Space" पूर्ण,
	[KERNEL_SPACE_NR]	= अणु (1UL << 63),	"Kernel Space" पूर्ण,
	[LOW_KERNEL_NR]		= अणु 0UL,		"Low Kernel Mapping" पूर्ण,
	[VMALLOC_START_NR]	= अणु 0UL,		"vmalloc() Area" पूर्ण,
	[VMEMMAP_START_NR]	= अणु 0UL,		"Vmemmap" पूर्ण,
#अगर_घोषित CONFIG_KASAN
	/*
	 * These fields get initialized with the (dynamic)
	 * KASAN_SHADOW_अणुSTART,ENDपूर्ण values in pt_dump_init().
	 */
	[KASAN_SHADOW_START_NR]	= अणु 0UL,		"KASAN shadow" पूर्ण,
	[KASAN_SHADOW_END_NR]	= अणु 0UL,		"KASAN shadow end" पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	[LDT_NR]		= अणु 0UL,		"LDT remap" पूर्ण,
#पूर्ण_अगर
	[CPU_ENTRY_AREA_NR]	= अणु CPU_ENTRY_AREA_BASE,"CPU entry Area" पूर्ण,
#अगर_घोषित CONFIG_X86_ESPFIX64
	[ESPFIX_START_NR]	= अणु ESPFIX_BASE_ADDR,	"ESPfix Area", 16 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EFI
	[EFI_END_NR]		= अणु EFI_VA_END,		"EFI Runtime Services" पूर्ण,
#पूर्ण_अगर
	[HIGH_KERNEL_NR]	= अणु __START_KERNEL_map,	"High Kernel Mapping" पूर्ण,
	[MODULES_VADDR_NR]	= अणु MODULES_VADDR,	"Modules" पूर्ण,
	[MODULES_END_NR]	= अणु MODULES_END,	"End Modules" पूर्ण,
	[FIXADDR_START_NR]	= अणु FIXADDR_START,	"Fixmap Area" पूर्ण,
	[END_OF_SPACE_NR]	= अणु -1,			शून्य पूर्ण
पूर्ण;

#घोषणा INIT_PGD	((pgd_t *) &init_top_pgt)

#अन्यथा /* CONFIG_X86_64 */

क्रमागत address_markers_idx अणु
	USER_SPACE_NR = 0,
	KERNEL_SPACE_NR,
	VMALLOC_START_NR,
	VMALLOC_END_NR,
#अगर_घोषित CONFIG_HIGHMEM
	PKMAP_BASE_NR,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	LDT_NR,
#पूर्ण_अगर
	CPU_ENTRY_AREA_NR,
	FIXADDR_START_NR,
	END_OF_SPACE_NR,
पूर्ण;

अटल काष्ठा addr_marker address_markers[] = अणु
	[USER_SPACE_NR]		= अणु 0,			"User Space" पूर्ण,
	[KERNEL_SPACE_NR]	= अणु PAGE_OFFSET,	"Kernel Mapping" पूर्ण,
	[VMALLOC_START_NR]	= अणु 0UL,		"vmalloc() Area" पूर्ण,
	[VMALLOC_END_NR]	= अणु 0UL,		"vmalloc() End" पूर्ण,
#अगर_घोषित CONFIG_HIGHMEM
	[PKMAP_BASE_NR]		= अणु 0UL,		"Persistent kmap() Area" पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	[LDT_NR]		= अणु 0UL,		"LDT remap" पूर्ण,
#पूर्ण_अगर
	[CPU_ENTRY_AREA_NR]	= अणु 0UL,		"CPU entry area" पूर्ण,
	[FIXADDR_START_NR]	= अणु 0UL,		"Fixmap area" पूर्ण,
	[END_OF_SPACE_NR]	= अणु -1,			शून्य पूर्ण
पूर्ण;

#घोषणा INIT_PGD	(swapper_pg_dir)

#पूर्ण_अगर /* !CONFIG_X86_64 */

/* Multipliers क्रम offsets within the PTEs */
#घोषणा PTE_LEVEL_MULT (PAGE_SIZE)
#घोषणा PMD_LEVEL_MULT (PTRS_PER_PTE * PTE_LEVEL_MULT)
#घोषणा PUD_LEVEL_MULT (PTRS_PER_PMD * PMD_LEVEL_MULT)
#घोषणा P4D_LEVEL_MULT (PTRS_PER_PUD * PUD_LEVEL_MULT)
#घोषणा PGD_LEVEL_MULT (PTRS_PER_P4D * P4D_LEVEL_MULT)

#घोषणा pt_dump_seq_म_लिखो(m, to_dmesg, fmt, args...)		\
(अणु								\
	अगर (to_dmesg)					\
		prपूर्णांकk(KERN_INFO fmt, ##args);			\
	अन्यथा							\
		अगर (m)						\
			seq_म_लिखो(m, fmt, ##args);		\
पूर्ण)

#घोषणा pt_dump_cont_म_लिखो(m, to_dmesg, fmt, args...)		\
(अणु								\
	अगर (to_dmesg)					\
		prपूर्णांकk(KERN_CONT fmt, ##args);			\
	अन्यथा							\
		अगर (m)						\
			seq_म_लिखो(m, fmt, ##args);		\
पूर्ण)

/*
 * Prपूर्णांक a पढ़ोable क्रमm of a pgprot_t to the seq_file
 */
अटल व्योम prपूर्णांकk_prot(काष्ठा seq_file *m, pgprotval_t pr, पूर्णांक level, bool dmsg)
अणु
	अटल स्थिर अक्षर * स्थिर level_name[] =
		अणु "pgd", "p4d", "pud", "pmd", "pte" पूर्ण;

	अगर (!(pr & _PAGE_PRESENT)) अणु
		/* Not present */
		pt_dump_cont_म_लिखो(m, dmsg, "                              ");
	पूर्ण अन्यथा अणु
		अगर (pr & _PAGE_USER)
			pt_dump_cont_म_लिखो(m, dmsg, "USR ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "    ");
		अगर (pr & _PAGE_RW)
			pt_dump_cont_म_लिखो(m, dmsg, "RW ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "ro ");
		अगर (pr & _PAGE_PWT)
			pt_dump_cont_म_लिखो(m, dmsg, "PWT ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "    ");
		अगर (pr & _PAGE_PCD)
			pt_dump_cont_म_लिखो(m, dmsg, "PCD ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "    ");

		/* Bit 7 has a dअगरferent meaning on level 3 vs 4 */
		अगर (level <= 3 && pr & _PAGE_PSE)
			pt_dump_cont_म_लिखो(m, dmsg, "PSE ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "    ");
		अगर ((level == 4 && pr & _PAGE_PAT) ||
		    ((level == 3 || level == 2) && pr & _PAGE_PAT_LARGE))
			pt_dump_cont_म_लिखो(m, dmsg, "PAT ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "    ");
		अगर (pr & _PAGE_GLOBAL)
			pt_dump_cont_म_लिखो(m, dmsg, "GLB ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "    ");
		अगर (pr & _PAGE_NX)
			pt_dump_cont_म_लिखो(m, dmsg, "NX ");
		अन्यथा
			pt_dump_cont_म_लिखो(m, dmsg, "x  ");
	पूर्ण
	pt_dump_cont_म_लिखो(m, dmsg, "%s\n", level_name[level]);
पूर्ण

अटल व्योम note_wx(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ npages;

	npages = (addr - st->start_address) / PAGE_SIZE;

#अगर_घोषित CONFIG_PCI_BIOS
	/*
	 * If PCI BIOS is enabled, the PCI BIOS area is क्रमced to WX.
	 * Inक्रमm about it, but aव्योम the warning.
	 */
	अगर (pcibios_enabled && st->start_address >= PAGE_OFFSET + BIOS_BEGIN &&
	    addr <= PAGE_OFFSET + BIOS_END) अणु
		pr_warn_once("x86/mm: PCI BIOS W+X mapping %lu pages\n", npages);
		वापस;
	पूर्ण
#पूर्ण_अगर
	/* Account the WX pages */
	st->wx_pages += npages;
	WARN_ONCE(__supported_pte_mask & _PAGE_NX,
		  "x86/mm: Found insecure W+X mapping at address %pS\n",
		  (व्योम *)st->start_address);
पूर्ण

अटल व्योम effective_prot(काष्ठा ptdump_state *pt_st, पूर्णांक level, u64 val)
अणु
	काष्ठा pg_state *st = container_of(pt_st, काष्ठा pg_state, ptdump);
	pgprotval_t prot = val & PTE_FLAGS_MASK;
	pgprotval_t effective;

	अगर (level > 0) अणु
		pgprotval_t higher_prot = st->prot_levels[level - 1];

		effective = (higher_prot & prot & (_PAGE_USER | _PAGE_RW)) |
			    ((higher_prot | prot) & _PAGE_NX);
	पूर्ण अन्यथा अणु
		effective = prot;
	पूर्ण

	st->prot_levels[level] = effective;
पूर्ण

/*
 * This function माला_लो called on a अवरोध in a continuous series
 * of PTE entries; the next one is dअगरferent so we need to
 * prपूर्णांक what we collected so far.
 */
अटल व्योम note_page(काष्ठा ptdump_state *pt_st, अचिन्हित दीर्घ addr, पूर्णांक level,
		      u64 val)
अणु
	काष्ठा pg_state *st = container_of(pt_st, काष्ठा pg_state, ptdump);
	pgprotval_t new_prot, new_eff;
	pgprotval_t cur, eff;
	अटल स्थिर अक्षर units[] = "BKMGTPE";
	काष्ठा seq_file *m = st->seq;

	new_prot = val & PTE_FLAGS_MASK;
	अगर (!val)
		new_eff = 0;
	अन्यथा
		new_eff = st->prot_levels[level];

	/*
	 * If we have a "break" in the series, we need to flush the state that
	 * we have now. "break" is either changing perms, levels or
	 * address space marker.
	 */
	cur = st->current_prot;
	eff = st->effective_prot;

	अगर (st->level == -1) अणु
		/* First entry */
		st->current_prot = new_prot;
		st->effective_prot = new_eff;
		st->level = level;
		st->marker = address_markers;
		st->lines = 0;
		pt_dump_seq_म_लिखो(m, st->to_dmesg, "---[ %s ]---\n",
				   st->marker->name);
	पूर्ण अन्यथा अगर (new_prot != cur || new_eff != eff || level != st->level ||
		   addr >= st->marker[1].start_address) अणु
		स्थिर अक्षर *unit = units;
		अचिन्हित दीर्घ delta;
		पूर्णांक width = माप(अचिन्हित दीर्घ) * 2;

		अगर (st->check_wx && (eff & _PAGE_RW) && !(eff & _PAGE_NX))
			note_wx(st, addr);

		/*
		 * Now prपूर्णांक the actual finished series
		 */
		अगर (!st->marker->max_lines ||
		    st->lines < st->marker->max_lines) अणु
			pt_dump_seq_म_लिखो(m, st->to_dmesg,
					   "0x%0*lx-0x%0*lx   ",
					   width, st->start_address,
					   width, addr);

			delta = addr - st->start_address;
			जबतक (!(delta & 1023) && unit[1]) अणु
				delta >>= 10;
				unit++;
			पूर्ण
			pt_dump_cont_म_लिखो(m, st->to_dmesg, "%9lu%c ",
					    delta, *unit);
			prपूर्णांकk_prot(m, st->current_prot, st->level,
				    st->to_dmesg);
		पूर्ण
		st->lines++;

		/*
		 * We prपूर्णांक markers क्रम special areas of address space,
		 * such as the start of vदो_स्मृति space etc.
		 * This helps in the पूर्णांकerpretation.
		 */
		अगर (addr >= st->marker[1].start_address) अणु
			अगर (st->marker->max_lines &&
			    st->lines > st->marker->max_lines) अणु
				अचिन्हित दीर्घ nskip =
					st->lines - st->marker->max_lines;
				pt_dump_seq_म_लिखो(m, st->to_dmesg,
						   "... %lu entr%s skipped ... \n",
						   nskip,
						   nskip == 1 ? "y" : "ies");
			पूर्ण
			st->marker++;
			st->lines = 0;
			pt_dump_seq_म_लिखो(m, st->to_dmesg, "---[ %s ]---\n",
					   st->marker->name);
		पूर्ण

		st->start_address = addr;
		st->current_prot = new_prot;
		st->effective_prot = new_eff;
		st->level = level;
	पूर्ण
पूर्ण

अटल व्योम ptdump_walk_pgd_level_core(काष्ठा seq_file *m,
				       काष्ठा mm_काष्ठा *mm, pgd_t *pgd,
				       bool checkwx, bool dmesg)
अणु
	स्थिर काष्ठा ptdump_range ptdump_ranges[] = अणु
#अगर_घोषित CONFIG_X86_64
	अणु0, PTRS_PER_PGD * PGD_LEVEL_MULT / 2पूर्ण,
	अणुGUARD_HOLE_END_ADDR, ~0ULपूर्ण,
#अन्यथा
	अणु0, ~0ULपूर्ण,
#पूर्ण_अगर
	अणु0, 0पूर्ण
पूर्ण;

	काष्ठा pg_state st = अणु
		.ptdump = अणु
			.note_page	= note_page,
			.effective_prot = effective_prot,
			.range		= ptdump_ranges
		पूर्ण,
		.level = -1,
		.to_dmesg	= dmesg,
		.check_wx	= checkwx,
		.seq		= m
	पूर्ण;

	ptdump_walk_pgd(&st.ptdump, mm, pgd);

	अगर (!checkwx)
		वापस;
	अगर (st.wx_pages)
		pr_info("x86/mm: Checked W+X mappings: FAILED, %lu W+X pages found.\n",
			st.wx_pages);
	अन्यथा
		pr_info("x86/mm: Checked W+X mappings: passed, no W+X pages found.\n");
पूर्ण

व्योम ptdump_walk_pgd_level(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm)
अणु
	ptdump_walk_pgd_level_core(m, mm, mm->pgd, false, true);
पूर्ण

व्योम ptdump_walk_pgd_level_debugfs(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm,
				   bool user)
अणु
	pgd_t *pgd = mm->pgd;
#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	अगर (user && boot_cpu_has(X86_FEATURE_PTI))
		pgd = kernel_to_user_pgdp(pgd);
#पूर्ण_अगर
	ptdump_walk_pgd_level_core(m, mm, pgd, false, false);
पूर्ण
EXPORT_SYMBOL_GPL(ptdump_walk_pgd_level_debugfs);

व्योम ptdump_walk_user_pgd_level_checkwx(व्योम)
अणु
#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	pgd_t *pgd = INIT_PGD;

	अगर (!(__supported_pte_mask & _PAGE_NX) ||
	    !boot_cpu_has(X86_FEATURE_PTI))
		वापस;

	pr_info("x86/mm: Checking user space page tables\n");
	pgd = kernel_to_user_pgdp(pgd);
	ptdump_walk_pgd_level_core(शून्य, &init_mm, pgd, true, false);
#पूर्ण_अगर
पूर्ण

व्योम ptdump_walk_pgd_level_checkwx(व्योम)
अणु
	ptdump_walk_pgd_level_core(शून्य, &init_mm, INIT_PGD, true, false);
पूर्ण

अटल पूर्णांक __init pt_dump_init(व्योम)
अणु
	/*
	 * Various markers are not compile-समय स्थिरants, so assign them
	 * here.
	 */
#अगर_घोषित CONFIG_X86_64
	address_markers[LOW_KERNEL_NR].start_address = PAGE_OFFSET;
	address_markers[VMALLOC_START_NR].start_address = VMALLOC_START;
	address_markers[VMEMMAP_START_NR].start_address = VMEMMAP_START;
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	address_markers[LDT_NR].start_address = LDT_BASE_ADDR;
#पूर्ण_अगर
#अगर_घोषित CONFIG_KASAN
	address_markers[KASAN_SHADOW_START_NR].start_address = KASAN_SHADOW_START;
	address_markers[KASAN_SHADOW_END_NR].start_address = KASAN_SHADOW_END;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_32
	address_markers[VMALLOC_START_NR].start_address = VMALLOC_START;
	address_markers[VMALLOC_END_NR].start_address = VMALLOC_END;
# अगरdef CONFIG_HIGHMEM
	address_markers[PKMAP_BASE_NR].start_address = PKMAP_BASE;
# endअगर
	address_markers[FIXADDR_START_NR].start_address = FIXADDR_START;
	address_markers[CPU_ENTRY_AREA_NR].start_address = CPU_ENTRY_AREA_BASE;
# अगरdef CONFIG_MODIFY_LDT_SYSCALL
	address_markers[LDT_NR].start_address = LDT_BASE_ADDR;
# endअगर
#पूर्ण_अगर
	वापस 0;
पूर्ण
__initcall(pt_dump_init);
