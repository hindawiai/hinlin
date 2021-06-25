<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016, Rashmica Gupta, IBM Corp.
 *
 * This traverses the kernel pagetables and dumps the
 * inक्रमmation about the used sections of memory to
 * /sys/kernel/debug/kernel_pagetables.
 *
 * Derived from the arm64 implementation:
 * Copyright (c) 2014, The Linux Foundation, Laura Abbott.
 * (C) Copyright 2008 Intel Corporation, Arjan van de Ven.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hugetlb.h>

#समावेश <mm/mmu_decl.h>

#समावेश "ptdump.h"

/*
 * To visualise what is happening,
 *
 *  - PTRS_PER_P** = how many entries there are in the corresponding P**
 *  - P**_SHIFT = how many bits of the address we use to index पूर्णांकo the
 * corresponding P**
 *  - P**_SIZE is how much memory we can access through the table - not the
 * size of the table itself.
 * P**=अणुPGD, PUD, PMD, PTEपूर्ण
 *
 *
 * Each entry of the PGD poपूर्णांकs to a PUD. Each entry of a PUD poपूर्णांकs to a
 * PMD. Each entry of a PMD poपूर्णांकs to a PTE. And every PTE entry poपूर्णांकs to
 * a page.
 *
 * In the हाल where there are only 3 levels, the PUD is folded पूर्णांकo the
 * PGD: every PUD has only one entry which poपूर्णांकs to the PMD.
 *
 * The page dumper groups page table entries of the same type पूर्णांकo a single
 * description. It uses pg_state to track the range inक्रमmation जबतक
 * iterating over the PTE entries. When the continuity is broken it then
 * dumps out a description of the range - ie PTEs that are भवly contiguous
 * with the same PTE flags are chunked together. This is to make it clear how
 * dअगरferent areas of the kernel भव memory are used.
 *
 */
काष्ठा pg_state अणु
	काष्ठा seq_file *seq;
	स्थिर काष्ठा addr_marker *marker;
	अचिन्हित दीर्घ start_address;
	अचिन्हित दीर्घ start_pa;
	अचिन्हित दीर्घ last_pa;
	अचिन्हित दीर्घ page_size;
	अचिन्हित पूर्णांक level;
	u64 current_flags;
	bool check_wx;
	अचिन्हित दीर्घ wx_pages;
पूर्ण;

काष्ठा addr_marker अणु
	अचिन्हित दीर्घ start_address;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा addr_marker address_markers[] = अणु
	अणु 0,	"Start of kernel VM" पूर्ण,
#अगर_घोषित MODULES_VADDR
	अणु 0,	"modules start" पूर्ण,
	अणु 0,	"modules end" पूर्ण,
#पूर्ण_अगर
	अणु 0,	"vmalloc() Area" पूर्ण,
	अणु 0,	"vmalloc() End" पूर्ण,
#अगर_घोषित CONFIG_PPC64
	अणु 0,	"isa I/O start" पूर्ण,
	अणु 0,	"isa I/O end" पूर्ण,
	अणु 0,	"phb I/O start" पूर्ण,
	अणु 0,	"phb I/O end" पूर्ण,
	अणु 0,	"I/O remap start" पूर्ण,
	अणु 0,	"I/O remap end" पूर्ण,
	अणु 0,	"vmemmap start" पूर्ण,
#अन्यथा
	अणु 0,	"Early I/O remap start" पूर्ण,
	अणु 0,	"Early I/O remap end" पूर्ण,
#अगर_घोषित CONFIG_HIGHMEM
	अणु 0,	"Highmem PTEs start" पूर्ण,
	अणु 0,	"Highmem PTEs end" पूर्ण,
#पूर्ण_अगर
	अणु 0,	"Fixmap start" पूर्ण,
	अणु 0,	"Fixmap end" पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KASAN
	अणु 0,	"kasan shadow mem start" पूर्ण,
	अणु 0,	"kasan shadow mem end" पूर्ण,
#पूर्ण_अगर
	अणु -1,	शून्य पूर्ण,
पूर्ण;

#घोषणा pt_dump_seq_म_लिखो(m, fmt, args...)	\
(अणु						\
	अगर (m)					\
		seq_म_लिखो(m, fmt, ##args);	\
पूर्ण)

#घोषणा pt_dump_seq_अ_दो(m, c)		\
(अणु					\
	अगर (m)				\
		seq_अ_दो(m, c);		\
पूर्ण)

व्योम pt_dump_size(काष्ठा seq_file *m, अचिन्हित दीर्घ size)
अणु
	अटल स्थिर अक्षर units[] = "KMGTPE";
	स्थिर अक्षर *unit = units;

	/* Work out what appropriate unit to use */
	जबतक (!(size & 1023) && unit[1]) अणु
		size >>= 10;
		unit++;
	पूर्ण
	pt_dump_seq_म_लिखो(m, "%9lu%c ", size, *unit);
पूर्ण

अटल व्योम dump_flag_info(काष्ठा pg_state *st, स्थिर काष्ठा flag_info
		*flag, u64 pte, पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++, flag++) अणु
		स्थिर अक्षर *s = शून्य;
		u64 val;

		/* flag not defined so करोn't check it */
		अगर (flag->mask == 0)
			जारी;
		/* Some 'flags' are actually values */
		अगर (flag->is_val) अणु
			val = pte & flag->val;
			अगर (flag->shअगरt)
				val = val >> flag->shअगरt;
			pt_dump_seq_म_लिखो(st->seq, "  %s:%llx", flag->set, val);
		पूर्ण अन्यथा अणु
			अगर ((pte & flag->mask) == flag->val)
				s = flag->set;
			अन्यथा
				s = flag->clear;
			अगर (s)
				pt_dump_seq_म_लिखो(st->seq, "  %s", s);
		पूर्ण
		st->current_flags &= ~flag->mask;
	पूर्ण
	अगर (st->current_flags != 0)
		pt_dump_seq_म_लिखो(st->seq, "  unknown flags:%llx", st->current_flags);
पूर्ण

अटल व्योम dump_addr(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ delta;

#अगर_घोषित CONFIG_PPC64
#घोषणा REG		"0x%016lx"
#अन्यथा
#घोषणा REG		"0x%08lx"
#पूर्ण_अगर

	pt_dump_seq_म_लिखो(st->seq, REG "-" REG " ", st->start_address, addr - 1);
	अगर (st->start_pa == st->last_pa && st->start_address + st->page_size != addr) अणु
		pt_dump_seq_म_लिखो(st->seq, "[" REG "]", st->start_pa);
		delta = st->page_size >> 10;
	पूर्ण अन्यथा अणु
		pt_dump_seq_म_लिखो(st->seq, " " REG " ", st->start_pa);
		delta = (addr - st->start_address) >> 10;
	पूर्ण
	pt_dump_size(st->seq, delta);
पूर्ण

अटल व्योम note_prot_wx(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	pte_t pte = __pte(st->current_flags);

	अगर (!IS_ENABLED(CONFIG_PPC_DEBUG_WX) || !st->check_wx)
		वापस;

	अगर (!pte_ग_लिखो(pte) || !pte_exec(pte))
		वापस;

	WARN_ONCE(1, "powerpc/mm: Found insecure W+X mapping at address %p/%pS\n",
		  (व्योम *)st->start_address, (व्योम *)st->start_address);

	st->wx_pages += (addr - st->start_address) / PAGE_SIZE;
पूर्ण

अटल व्योम note_page_update_state(काष्ठा pg_state *st, अचिन्हित दीर्घ addr,
				   अचिन्हित पूर्णांक level, u64 val, अचिन्हित दीर्घ page_size)
अणु
	u64 flag = val & pg_level[level].mask;
	u64 pa = val & PTE_RPN_MASK;

	st->level = level;
	st->current_flags = flag;
	st->start_address = addr;
	st->start_pa = pa;
	st->page_size = page_size;

	जबतक (addr >= st->marker[1].start_address) अणु
		st->marker++;
		pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
	पूर्ण
पूर्ण

अटल व्योम note_page(काष्ठा pg_state *st, अचिन्हित दीर्घ addr,
	       अचिन्हित पूर्णांक level, u64 val, अचिन्हित दीर्घ page_size)
अणु
	u64 flag = val & pg_level[level].mask;
	u64 pa = val & PTE_RPN_MASK;

	/* At first no level is set */
	अगर (!st->level) अणु
		pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
		note_page_update_state(st, addr, level, val, page_size);
	/*
	 * Dump the section of भव memory when:
	 *   - the PTE flags from one entry to the next dअगरfers.
	 *   - we change levels in the tree.
	 *   - the address is in a dअगरferent section of memory and is thus
	 *   used क्रम a dअगरferent purpose, regardless of the flags.
	 *   - the pa of this page is not adjacent to the last inspected page
	 */
	पूर्ण अन्यथा अगर (flag != st->current_flags || level != st->level ||
		   addr >= st->marker[1].start_address ||
		   (pa != st->last_pa + st->page_size &&
		    (pa != st->start_pa || st->start_pa != st->last_pa))) अणु

		/* Check the PTE flags */
		अगर (st->current_flags) अणु
			note_prot_wx(st, addr);
			dump_addr(st, addr);

			/* Dump all the flags */
			अगर (pg_level[st->level].flag)
				dump_flag_info(st, pg_level[st->level].flag,
					  st->current_flags,
					  pg_level[st->level].num);

			pt_dump_seq_अ_दो(st->seq, '\n');
		पूर्ण

		/*
		 * Address indicates we have passed the end of the
		 * current section of भव memory
		 */
		note_page_update_state(st, addr, level, val, page_size);
	पूर्ण
	st->last_pa = pa;
पूर्ण

अटल व्योम walk_pte(काष्ठा pg_state *st, pmd_t *pmd, अचिन्हित दीर्घ start)
अणु
	pte_t *pte = pte_offset_kernel(pmd, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++, pte++) अणु
		addr = start + i * PAGE_SIZE;
		note_page(st, addr, 4, pte_val(*pte), PAGE_SIZE);

	पूर्ण
पूर्ण

अटल व्योम walk_hugepd(काष्ठा pg_state *st, hugepd_t *phpd, अचिन्हित दीर्घ start,
			पूर्णांक pdshअगरt, पूर्णांक level)
अणु
#अगर_घोषित CONFIG_ARCH_HAS_HUGEPD
	अचिन्हित पूर्णांक i;
	पूर्णांक shअगरt = hugepd_shअगरt(*phpd);
	पूर्णांक ptrs_per_hpd = pdshअगरt - shअगरt > 0 ? 1 << (pdshअगरt - shअगरt) : 1;

	अगर (start & ((1 << shअगरt) - 1))
		वापस;

	क्रम (i = 0; i < ptrs_per_hpd; i++) अणु
		अचिन्हित दीर्घ addr = start + (i << shअगरt);
		pte_t *pte = hugepte_offset(*phpd, addr, pdshअगरt);

		note_page(st, addr, level + 1, pte_val(*pte), 1 << shअगरt);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम walk_pmd(काष्ठा pg_state *st, pud_t *pud, अचिन्हित दीर्घ start)
अणु
	pmd_t *pmd = pmd_offset(pud, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PMD; i++, pmd++) अणु
		addr = start + i * PMD_SIZE;
		अगर (!pmd_none(*pmd) && !pmd_is_leaf(*pmd))
			/* pmd exists */
			walk_pte(st, pmd, addr);
		अन्यथा
			note_page(st, addr, 3, pmd_val(*pmd), PMD_SIZE);
	पूर्ण
पूर्ण

अटल व्योम walk_pud(काष्ठा pg_state *st, p4d_t *p4d, अचिन्हित दीर्घ start)
अणु
	pud_t *pud = pud_offset(p4d, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PUD; i++, pud++) अणु
		addr = start + i * PUD_SIZE;
		अगर (!pud_none(*pud) && !pud_is_leaf(*pud))
			/* pud exists */
			walk_pmd(st, pud, addr);
		अन्यथा
			note_page(st, addr, 2, pud_val(*pud), PUD_SIZE);
	पूर्ण
पूर्ण

अटल व्योम walk_pagetables(काष्ठा pg_state *st)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ addr = st->start_address & PGसूची_MASK;
	pgd_t *pgd = pgd_offset_k(addr);

	/*
	 * Traverse the linux pagetable काष्ठाure and dump pages that are in
	 * the hash pagetable.
	 */
	क्रम (i = pgd_index(addr); i < PTRS_PER_PGD; i++, pgd++, addr += PGसूची_SIZE) अणु
		p4d_t *p4d = p4d_offset(pgd, 0);

		अगर (p4d_none(*p4d) || p4d_is_leaf(*p4d))
			note_page(st, addr, 1, p4d_val(*p4d), PGसूची_SIZE);
		अन्यथा अगर (is_hugepd(__hugepd(p4d_val(*p4d))))
			walk_hugepd(st, (hugepd_t *)p4d, addr, PGसूची_SHIFT, 1);
		अन्यथा
			/* p4d exists */
			walk_pud(st, p4d, addr);
	पूर्ण
पूर्ण

अटल व्योम populate_markers(व्योम)
अणु
	पूर्णांक i = 0;

#अगर_घोषित CONFIG_PPC64
	address_markers[i++].start_address = PAGE_OFFSET;
#अन्यथा
	address_markers[i++].start_address = TASK_SIZE;
#पूर्ण_अगर
#अगर_घोषित MODULES_VADDR
	address_markers[i++].start_address = MODULES_VADDR;
	address_markers[i++].start_address = MODULES_END;
#पूर्ण_अगर
	address_markers[i++].start_address = VMALLOC_START;
	address_markers[i++].start_address = VMALLOC_END;
#अगर_घोषित CONFIG_PPC64
	address_markers[i++].start_address = ISA_IO_BASE;
	address_markers[i++].start_address = ISA_IO_END;
	address_markers[i++].start_address = PHB_IO_BASE;
	address_markers[i++].start_address = PHB_IO_END;
	address_markers[i++].start_address = IOREMAP_BASE;
	address_markers[i++].start_address = IOREMAP_END;
	/* What is the अगरdef about? */
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	address_markers[i++].start_address =  H_VMEMMAP_START;
#अन्यथा
	address_markers[i++].start_address =  VMEMMAP_BASE;
#पूर्ण_अगर
#अन्यथा /* !CONFIG_PPC64 */
	address_markers[i++].start_address = ioremap_bot;
	address_markers[i++].start_address = IOREMAP_TOP;
#अगर_घोषित CONFIG_HIGHMEM
	address_markers[i++].start_address = PKMAP_BASE;
	address_markers[i++].start_address = PKMAP_ADDR(LAST_PKMAP);
#पूर्ण_अगर
	address_markers[i++].start_address = FIXADDR_START;
	address_markers[i++].start_address = FIXADDR_TOP;
#अगर_घोषित CONFIG_KASAN
	address_markers[i++].start_address = KASAN_SHADOW_START;
	address_markers[i++].start_address = KASAN_SHADOW_END;
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PPC64 */
पूर्ण

अटल पूर्णांक ptdump_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा pg_state st = अणु
		.seq = m,
		.marker = address_markers,
		.start_address = IS_ENABLED(CONFIG_PPC64) ? PAGE_OFFSET : TASK_SIZE,
	पूर्ण;

#अगर_घोषित CONFIG_PPC64
	अगर (!radix_enabled())
		st.start_address = KERN_VIRT_START;
#पूर्ण_अगर

	/* Traverse kernel page tables */
	walk_pagetables(&st);
	note_page(&st, 0, 0, 0, 0);
	वापस 0;
पूर्ण


अटल पूर्णांक ptdump_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ptdump_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations ptdump_fops = अणु
	.खोलो		= ptdump_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल व्योम build_pgtable_complete_mask(व्योम)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(pg_level); i++)
		अगर (pg_level[i].flag)
			क्रम (j = 0; j < pg_level[i].num; j++)
				pg_level[i].mask |= pg_level[i].flag[j].mask;
पूर्ण

#अगर_घोषित CONFIG_PPC_DEBUG_WX
व्योम ptdump_check_wx(व्योम)
अणु
	काष्ठा pg_state st = अणु
		.seq = शून्य,
		.marker = address_markers,
		.check_wx = true,
		.start_address = IS_ENABLED(CONFIG_PPC64) ? PAGE_OFFSET : TASK_SIZE,
	पूर्ण;

#अगर_घोषित CONFIG_PPC64
	अगर (!radix_enabled())
		st.start_address = KERN_VIRT_START;
#पूर्ण_अगर

	walk_pagetables(&st);

	अगर (st.wx_pages)
		pr_warn("Checked W+X mappings: FAILED, %lu W+X pages found\n",
			st.wx_pages);
	अन्यथा
		pr_info("Checked W+X mappings: passed, no W+X pages found\n");
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ptdump_init(व्योम)
अणु
	populate_markers();
	build_pgtable_complete_mask();
	debugfs_create_file("kernel_page_tables", 0400, शून्य, शून्य,
			    &ptdump_fops);
	वापस 0;
पूर्ण
device_initcall(ptdump_init);
