<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Debug helper to dump the current kernel pagetables of the प्रणाली
 * so that we can see what the various memory ranges are set to.
 *
 * Derived from x86 implementation:
 * (C) Copyright 2008 Intel Corporation
 *
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/करोमुख्य.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/ptdump.h>

अटल काष्ठा addr_marker address_markers[] = अणु
#अगर_घोषित CONFIG_KASAN
	अणु KASAN_SHADOW_START,	"Kasan shadow start"पूर्ण,
	अणु KASAN_SHADOW_END,	"Kasan shadow end"पूर्ण,
#पूर्ण_अगर
	अणु MODULES_VADDR,	"Modules" पूर्ण,
	अणु PAGE_OFFSET,		"Kernel Mapping" पूर्ण,
	अणु 0,			"vmalloc() Area" पूर्ण,
	अणु VMALLOC_END,		"vmalloc() End" पूर्ण,
	अणु FIXADDR_START,	"Fixmap Area" पूर्ण,
	अणु VECTORS_BASE,	"Vectors" पूर्ण,
	अणु VECTORS_BASE + PAGE_SIZE * 2, "Vectors End" पूर्ण,
	अणु -1,			शून्य पूर्ण,
पूर्ण;

#घोषणा pt_dump_seq_म_लिखो(m, fmt, args...) \
(अणु                      \
	अगर (m)					\
		seq_म_लिखो(m, fmt, ##args);	\
पूर्ण)

#घोषणा pt_dump_seq_माला_दो(m, fmt)    \
(अणु						\
	अगर (m)					\
		seq_म_लिखो(m, fmt);	\
पूर्ण)

काष्ठा pg_state अणु
	काष्ठा seq_file *seq;
	स्थिर काष्ठा addr_marker *marker;
	अचिन्हित दीर्घ start_address;
	अचिन्हित level;
	u64 current_prot;
	bool check_wx;
	अचिन्हित दीर्घ wx_pages;
	स्थिर अक्षर *current_करोमुख्य;
पूर्ण;

काष्ठा prot_bits अणु
	u64		mask;
	u64		val;
	स्थिर अक्षर	*set;
	स्थिर अक्षर	*clear;
	bool		ro_bit;
	bool		nx_bit;
पूर्ण;

अटल स्थिर काष्ठा prot_bits pte_bits[] = अणु
	अणु
		.mask	= L_PTE_USER,
		.val	= L_PTE_USER,
		.set	= "USR",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= L_PTE_RDONLY,
		.val	= L_PTE_RDONLY,
		.set	= "ro",
		.clear	= "RW",
		.ro_bit	= true,
	पूर्ण, अणु
		.mask	= L_PTE_XN,
		.val	= L_PTE_XN,
		.set	= "NX",
		.clear	= "x ",
		.nx_bit	= true,
	पूर्ण, अणु
		.mask	= L_PTE_SHARED,
		.val	= L_PTE_SHARED,
		.set	= "SHD",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_UNCACHED,
		.set	= "SO/UNCACHED",
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_BUFFERABLE,
		.set	= "MEM/BUFFERABLE/WC",
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_WRITETHROUGH,
		.set	= "MEM/CACHED/WT",
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_WRITEBACK,
		.set	= "MEM/CACHED/WBRA",
#अगर_अघोषित CONFIG_ARM_LPAE
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_MINICACHE,
		.set	= "MEM/MINICACHE",
#पूर्ण_अगर
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_WRITEALLOC,
		.set	= "MEM/CACHED/WBWA",
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_DEV_SHARED,
		.set	= "DEV/SHARED",
#अगर_अघोषित CONFIG_ARM_LPAE
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_DEV_NONSHARED,
		.set	= "DEV/NONSHARED",
#पूर्ण_अगर
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_DEV_WC,
		.set	= "DEV/WC",
	पूर्ण, अणु
		.mask	= L_PTE_MT_MASK,
		.val	= L_PTE_MT_DEV_CACHED,
		.set	= "DEV/CACHED",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा prot_bits section_bits[] = अणु
#अगर_घोषित CONFIG_ARM_LPAE
	अणु
		.mask	= PMD_SECT_USER,
		.val	= PMD_SECT_USER,
		.set	= "USR",
	पूर्ण, अणु
		.mask	= L_PMD_SECT_RDONLY | PMD_SECT_AP2,
		.val	= L_PMD_SECT_RDONLY | PMD_SECT_AP2,
		.set	= "ro",
		.clear	= "RW",
		.ro_bit	= true,
#या_अगर __LINUX_ARM_ARCH__ >= 6
	अणु
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_APX | PMD_SECT_AP_WRITE,
		.set	= "    ro",
		.ro_bit	= true,
	पूर्ण, अणु
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_AP_WRITE,
		.set	= "    RW",
	पूर्ण, अणु
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_AP_READ,
		.set	= "USR ro",
	पूर्ण, अणु
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.set	= "USR RW",
#अन्यथा /* ARMv4/ARMv5  */
	/* These are approximate */
	अणु
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = 0,
		.set    = "    ro",
		.ro_bit	= true,
	पूर्ण, अणु
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = PMD_SECT_AP_WRITE,
		.set    = "    RW",
	पूर्ण, अणु
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = PMD_SECT_AP_READ,
		.set    = "USR ro",
	पूर्ण, अणु
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.set    = "USR RW",
#पूर्ण_अगर
	पूर्ण, अणु
		.mask	= PMD_SECT_XN,
		.val	= PMD_SECT_XN,
		.set	= "NX",
		.clear	= "x ",
		.nx_bit	= true,
	पूर्ण, अणु
		.mask	= PMD_SECT_S,
		.val	= PMD_SECT_S,
		.set	= "SHD",
		.clear	= "   ",
	पूर्ण,
पूर्ण;

काष्ठा pg_level अणु
	स्थिर काष्ठा prot_bits *bits;
	माप_प्रकार num;
	u64 mask;
	स्थिर काष्ठा prot_bits *ro_bit;
	स्थिर काष्ठा prot_bits *nx_bit;
पूर्ण;

अटल काष्ठा pg_level pg_level[] = अणु
	अणु
	पूर्ण, अणु /* pgd */
	पूर्ण, अणु /* p4d */
	पूर्ण, अणु /* pud */
	पूर्ण, अणु /* pmd */
		.bits	= section_bits,
		.num	= ARRAY_SIZE(section_bits),
	पूर्ण, अणु /* pte */
		.bits	= pte_bits,
		.num	= ARRAY_SIZE(pte_bits),
	पूर्ण,
पूर्ण;

अटल व्योम dump_prot(काष्ठा pg_state *st, स्थिर काष्ठा prot_bits *bits, माप_प्रकार num)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < num; i++, bits++) अणु
		स्थिर अक्षर *s;

		अगर ((st->current_prot & bits->mask) == bits->val)
			s = bits->set;
		अन्यथा
			s = bits->clear;

		अगर (s)
			pt_dump_seq_म_लिखो(st->seq, " %s", s);
	पूर्ण
पूर्ण

अटल व्योम note_prot_wx(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	अगर (!st->check_wx)
		वापस;
	अगर ((st->current_prot & pg_level[st->level].ro_bit->mask) ==
				pg_level[st->level].ro_bit->val)
		वापस;
	अगर ((st->current_prot & pg_level[st->level].nx_bit->mask) ==
				pg_level[st->level].nx_bit->val)
		वापस;

	WARN_ONCE(1, "arm/mm: Found insecure W+X mapping at address %pS\n",
			(व्योम *)st->start_address);

	st->wx_pages += (addr - st->start_address) / PAGE_SIZE;
पूर्ण

अटल व्योम note_page(काष्ठा pg_state *st, अचिन्हित दीर्घ addr,
		      अचिन्हित पूर्णांक level, u64 val, स्थिर अक्षर *करोमुख्य)
अणु
	अटल स्थिर अक्षर units[] = "KMGTPE";
	u64 prot = val & pg_level[level].mask;

	अगर (!st->level) अणु
		st->level = level;
		st->current_prot = prot;
		st->current_करोमुख्य = करोमुख्य;
		pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
	पूर्ण अन्यथा अगर (prot != st->current_prot || level != st->level ||
		   करोमुख्य != st->current_करोमुख्य ||
		   addr >= st->marker[1].start_address) अणु
		स्थिर अक्षर *unit = units;
		अचिन्हित दीर्घ delta;

		अगर (st->current_prot) अणु
			note_prot_wx(st, addr);
			pt_dump_seq_म_लिखो(st->seq, "0x%08lx-0x%08lx   ",
				   st->start_address, addr);

			delta = (addr - st->start_address) >> 10;
			जबतक (!(delta & 1023) && unit[1]) अणु
				delta >>= 10;
				unit++;
			पूर्ण
			pt_dump_seq_म_लिखो(st->seq, "%9lu%c", delta, *unit);
			अगर (st->current_करोमुख्य)
				pt_dump_seq_म_लिखो(st->seq, " %s",
							st->current_करोमुख्य);
			अगर (pg_level[st->level].bits)
				dump_prot(st, pg_level[st->level].bits, pg_level[st->level].num);
			pt_dump_seq_म_लिखो(st->seq, "\n");
		पूर्ण

		अगर (addr >= st->marker[1].start_address) अणु
			st->marker++;
			pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n",
							st->marker->name);
		पूर्ण
		st->start_address = addr;
		st->current_prot = prot;
		st->current_करोमुख्य = करोमुख्य;
		st->level = level;
	पूर्ण
पूर्ण

अटल व्योम walk_pte(काष्ठा pg_state *st, pmd_t *pmd, अचिन्हित दीर्घ start,
		     स्थिर अक्षर *करोमुख्य)
अणु
	pte_t *pte = pte_offset_kernel(pmd, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++, pte++) अणु
		addr = start + i * PAGE_SIZE;
		note_page(st, addr, 5, pte_val(*pte), करोमुख्य);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *get_करोमुख्य_name(pmd_t *pmd)
अणु
#अगर_अघोषित CONFIG_ARM_LPAE
	चयन (pmd_val(*pmd) & PMD_DOMAIN_MASK) अणु
	हाल PMD_DOMAIN(DOMAIN_KERNEL):
		वापस "KERNEL ";
	हाल PMD_DOMAIN(DOMAIN_USER):
		वापस "USER   ";
	हाल PMD_DOMAIN(DOMAIN_IO):
		वापस "IO     ";
	हाल PMD_DOMAIN(DOMAIN_VECTORS):
		वापस "VECTORS";
	शेष:
		वापस "unknown";
	पूर्ण
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

अटल व्योम walk_pmd(काष्ठा pg_state *st, pud_t *pud, अचिन्हित दीर्घ start)
अणु
	pmd_t *pmd = pmd_offset(pud, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित i;
	स्थिर अक्षर *करोमुख्य;

	क्रम (i = 0; i < PTRS_PER_PMD; i++, pmd++) अणु
		addr = start + i * PMD_SIZE;
		करोमुख्य = get_करोमुख्य_name(pmd);
		अगर (pmd_none(*pmd) || pmd_large(*pmd) || !pmd_present(*pmd))
			note_page(st, addr, 3, pmd_val(*pmd), करोमुख्य);
		अन्यथा
			walk_pte(st, pmd, addr, करोमुख्य);

		अगर (SECTION_SIZE < PMD_SIZE && pmd_large(pmd[1])) अणु
			addr += SECTION_SIZE;
			pmd++;
			करोमुख्य = get_करोमुख्य_name(pmd);
			note_page(st, addr, 4, pmd_val(*pmd), करोमुख्य);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम walk_pud(काष्ठा pg_state *st, p4d_t *p4d, अचिन्हित दीर्घ start)
अणु
	pud_t *pud = pud_offset(p4d, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित i;

	क्रम (i = 0; i < PTRS_PER_PUD; i++, pud++) अणु
		addr = start + i * PUD_SIZE;
		अगर (!pud_none(*pud)) अणु
			walk_pmd(st, pud, addr);
		पूर्ण अन्यथा अणु
			note_page(st, addr, 3, pud_val(*pud), शून्य);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम walk_p4d(काष्ठा pg_state *st, pgd_t *pgd, अचिन्हित दीर्घ start)
अणु
	p4d_t *p4d = p4d_offset(pgd, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित i;

	क्रम (i = 0; i < PTRS_PER_P4D; i++, p4d++) अणु
		addr = start + i * P4D_SIZE;
		अगर (!p4d_none(*p4d)) अणु
			walk_pud(st, p4d, addr);
		पूर्ण अन्यथा अणु
			note_page(st, addr, 2, p4d_val(*p4d), शून्य);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम walk_pgd(काष्ठा pg_state *st, काष्ठा mm_काष्ठा *mm,
			अचिन्हित दीर्घ start)
अणु
	pgd_t *pgd = pgd_offset(mm, 0UL);
	अचिन्हित i;
	अचिन्हित दीर्घ addr;

	क्रम (i = 0; i < PTRS_PER_PGD; i++, pgd++) अणु
		addr = start + i * PGसूची_SIZE;
		अगर (!pgd_none(*pgd)) अणु
			walk_p4d(st, pgd, addr);
		पूर्ण अन्यथा अणु
			note_page(st, addr, 1, pgd_val(*pgd), शून्य);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ptdump_walk_pgd(काष्ठा seq_file *m, काष्ठा ptdump_info *info)
अणु
	काष्ठा pg_state st = अणु
		.seq = m,
		.marker = info->markers,
		.check_wx = false,
	पूर्ण;

	walk_pgd(&st, info->mm, info->base_addr);
	note_page(&st, 0, 0, 0, शून्य);
पूर्ण

अटल व्योम __init ptdump_initialize(व्योम)
अणु
	अचिन्हित i, j;

	क्रम (i = 0; i < ARRAY_SIZE(pg_level); i++)
		अगर (pg_level[i].bits)
			क्रम (j = 0; j < pg_level[i].num; j++) अणु
				pg_level[i].mask |= pg_level[i].bits[j].mask;
				अगर (pg_level[i].bits[j].ro_bit)
					pg_level[i].ro_bit = &pg_level[i].bits[j];
				अगर (pg_level[i].bits[j].nx_bit)
					pg_level[i].nx_bit = &pg_level[i].bits[j];
			पूर्ण
#अगर_घोषित CONFIG_KASAN
	address_markers[4].start_address = VMALLOC_START;
#अन्यथा
	address_markers[2].start_address = VMALLOC_START;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा ptdump_info kernel_ptdump_info = अणु
	.mm = &init_mm,
	.markers = address_markers,
	.base_addr = 0,
पूर्ण;

व्योम ptdump_check_wx(व्योम)
अणु
	काष्ठा pg_state st = अणु
		.seq = शून्य,
		.marker = (काष्ठा addr_marker[]) अणु
			अणु 0, शून्यपूर्ण,
			अणु -1, शून्यपूर्ण,
		पूर्ण,
		.check_wx = true,
	पूर्ण;

	walk_pgd(&st, &init_mm, 0);
	note_page(&st, 0, 0, 0, शून्य);
	अगर (st.wx_pages)
		pr_warn("Checked W+X mappings: FAILED, %lu W+X pages found\n",
			st.wx_pages);
	अन्यथा
		pr_info("Checked W+X mappings: passed, no W+X pages found\n");
पूर्ण

अटल पूर्णांक __init ptdump_init(व्योम)
अणु
	ptdump_initialize();
	ptdump_debugfs_रेजिस्टर(&kernel_ptdump_info, "kernel_page_tables");
	वापस 0;
पूर्ण
__initcall(ptdump_init);
