<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 SiFive
 */

#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ptdump.h>

#समावेश <यंत्र/ptdump.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/kasan.h>

#घोषणा pt_dump_seq_म_लिखो(m, fmt, args...)	\
(अणु						\
	अगर (m)					\
		seq_म_लिखो(m, fmt, ##args);	\
पूर्ण)

#घोषणा pt_dump_seq_माला_दो(m, fmt)	\
(अणु					\
	अगर (m)				\
		seq_म_लिखो(m, fmt);	\
पूर्ण)

/*
 * The page dumper groups page table entries of the same type पूर्णांकo a single
 * description. It uses pg_state to track the range inक्रमmation जबतक
 * iterating over the pte entries. When the continuity is broken it then
 * dumps out a description of the range.
 */
काष्ठा pg_state अणु
	काष्ठा ptdump_state ptdump;
	काष्ठा seq_file *seq;
	स्थिर काष्ठा addr_marker *marker;
	अचिन्हित दीर्घ start_address;
	अचिन्हित दीर्घ start_pa;
	अचिन्हित दीर्घ last_pa;
	पूर्णांक level;
	u64 current_prot;
	bool check_wx;
	अचिन्हित दीर्घ wx_pages;
पूर्ण;

/* Address marker */
काष्ठा addr_marker अणु
	अचिन्हित दीर्घ start_address;
	स्थिर अक्षर *name;
पूर्ण;

/* Private inक्रमmation क्रम debugfs */
काष्ठा ptd_mm_info अणु
	काष्ठा mm_काष्ठा		*mm;
	स्थिर काष्ठा addr_marker	*markers;
	अचिन्हित दीर्घ base_addr;
	अचिन्हित दीर्घ end;
पूर्ण;

क्रमागत address_markers_idx अणु
#अगर_घोषित CONFIG_KASAN
	KASAN_SHADOW_START_NR,
	KASAN_SHADOW_END_NR,
#पूर्ण_अगर
	FIXMAP_START_NR,
	FIXMAP_END_NR,
	PCI_IO_START_NR,
	PCI_IO_END_NR,
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	VMEMMAP_START_NR,
	VMEMMAP_END_NR,
#पूर्ण_अगर
	VMALLOC_START_NR,
	VMALLOC_END_NR,
	PAGE_OFFSET_NR,
#अगर_घोषित CONFIG_64BIT
	MODULES_MAPPING_NR,
	KERNEL_MAPPING_NR,
#पूर्ण_अगर
	END_OF_SPACE_NR
पूर्ण;

अटल काष्ठा addr_marker address_markers[] = अणु
#अगर_घोषित CONFIG_KASAN
	अणु0, "Kasan shadow start"पूर्ण,
	अणु0, "Kasan shadow end"पूर्ण,
#पूर्ण_अगर
	अणु0, "Fixmap start"पूर्ण,
	अणु0, "Fixmap end"पूर्ण,
	अणु0, "PCI I/O start"पूर्ण,
	अणु0, "PCI I/O end"पूर्ण,
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	अणु0, "vmemmap start"पूर्ण,
	अणु0, "vmemmap end"पूर्ण,
#पूर्ण_अगर
	अणु0, "vmalloc() area"पूर्ण,
	अणु0, "vmalloc() end"पूर्ण,
	अणु0, "Linear mapping"पूर्ण,
#अगर_घोषित CONFIG_64BIT
	अणु0, "Modules mapping"पूर्ण,
	अणु0, "Kernel mapping (kernel, BPF)"पूर्ण,
#पूर्ण_अगर
	अणु-1, शून्यपूर्ण,
पूर्ण;

अटल काष्ठा ptd_mm_info kernel_ptd_info = अणु
	.mm		= &init_mm,
	.markers	= address_markers,
	.base_addr	= 0,
	.end		= अच_दीर्घ_उच्च,
पूर्ण;

#अगर_घोषित CONFIG_EFI
अटल काष्ठा addr_marker efi_addr_markers[] = अणु
		अणु 0,		"UEFI runtime start" पूर्ण,
		अणु SZ_1G,	"UEFI runtime end" पूर्ण,
		अणु -1,		शून्य पूर्ण
पूर्ण;

अटल काष्ठा ptd_mm_info efi_ptd_info = अणु
	.mm		= &efi_mm,
	.markers	= efi_addr_markers,
	.base_addr	= 0,
	.end		= SZ_2G,
पूर्ण;
#पूर्ण_अगर

/* Page Table Entry */
काष्ठा prot_bits अणु
	u64 mask;
	u64 val;
	स्थिर अक्षर *set;
	स्थिर अक्षर *clear;
पूर्ण;

अटल स्थिर काष्ठा prot_bits pte_bits[] = अणु
	अणु
		.mask = _PAGE_SOFT,
		.val = _PAGE_SOFT,
		.set = "RSW",
		.clear = "   ",
	पूर्ण, अणु
		.mask = _PAGE_सूचीTY,
		.val = _PAGE_सूचीTY,
		.set = "D",
		.clear = ".",
	पूर्ण, अणु
		.mask = _PAGE_ACCESSED,
		.val = _PAGE_ACCESSED,
		.set = "A",
		.clear = ".",
	पूर्ण, अणु
		.mask = _PAGE_GLOBAL,
		.val = _PAGE_GLOBAL,
		.set = "G",
		.clear = ".",
	पूर्ण, अणु
		.mask = _PAGE_USER,
		.val = _PAGE_USER,
		.set = "U",
		.clear = ".",
	पूर्ण, अणु
		.mask = _PAGE_EXEC,
		.val = _PAGE_EXEC,
		.set = "X",
		.clear = ".",
	पूर्ण, अणु
		.mask = _PAGE_WRITE,
		.val = _PAGE_WRITE,
		.set = "W",
		.clear = ".",
	पूर्ण, अणु
		.mask = _PAGE_READ,
		.val = _PAGE_READ,
		.set = "R",
		.clear = ".",
	पूर्ण, अणु
		.mask = _PAGE_PRESENT,
		.val = _PAGE_PRESENT,
		.set = "V",
		.clear = ".",
	पूर्ण
पूर्ण;

/* Page Level */
काष्ठा pg_level अणु
	स्थिर अक्षर *name;
	u64 mask;
पूर्ण;

अटल काष्ठा pg_level pg_level[] = अणु
	अणु /* pgd */
		.name = "PGD",
	पूर्ण, अणु /* p4d */
		.name = (CONFIG_PGTABLE_LEVELS > 4) ? "P4D" : "PGD",
	पूर्ण, अणु /* pud */
		.name = (CONFIG_PGTABLE_LEVELS > 3) ? "PUD" : "PGD",
	पूर्ण, अणु /* pmd */
		.name = (CONFIG_PGTABLE_LEVELS > 2) ? "PMD" : "PGD",
	पूर्ण, अणु /* pte */
		.name = "PTE",
	पूर्ण,
पूर्ण;

अटल व्योम dump_prot(काष्ठा pg_state *st)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pte_bits); i++) अणु
		स्थिर अक्षर *s;

		अगर ((st->current_prot & pte_bits[i].mask) == pte_bits[i].val)
			s = pte_bits[i].set;
		अन्यथा
			s = pte_bits[i].clear;

		अगर (s)
			pt_dump_seq_म_लिखो(st->seq, " %s", s);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_64BIT
#घोषणा ADDR_FORMAT	"0x%016lx"
#अन्यथा
#घोषणा ADDR_FORMAT	"0x%08lx"
#पूर्ण_अगर
अटल व्योम dump_addr(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	अटल स्थिर अक्षर units[] = "KMGTPE";
	स्थिर अक्षर *unit = units;
	अचिन्हित दीर्घ delta;

	pt_dump_seq_म_लिखो(st->seq, ADDR_FORMAT "-" ADDR_FORMAT "   ",
			   st->start_address, addr);

	pt_dump_seq_म_लिखो(st->seq, " " ADDR_FORMAT " ", st->start_pa);
	delta = (addr - st->start_address) >> 10;

	जबतक (!(delta & 1023) && unit[1]) अणु
		delta >>= 10;
		unit++;
	पूर्ण

	pt_dump_seq_म_लिखो(st->seq, "%9lu%c %s", delta, *unit,
			   pg_level[st->level].name);
पूर्ण

अटल व्योम note_prot_wx(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	अगर (!st->check_wx)
		वापस;

	अगर ((st->current_prot & (_PAGE_WRITE | _PAGE_EXEC)) !=
	    (_PAGE_WRITE | _PAGE_EXEC))
		वापस;

	WARN_ONCE(1, "riscv/mm: Found insecure W+X mapping at address %p/%pS\n",
		  (व्योम *)st->start_address, (व्योम *)st->start_address);

	st->wx_pages += (addr - st->start_address) / PAGE_SIZE;
पूर्ण

अटल व्योम note_page(काष्ठा ptdump_state *pt_st, अचिन्हित दीर्घ addr,
		      पूर्णांक level, u64 val)
अणु
	काष्ठा pg_state *st = container_of(pt_st, काष्ठा pg_state, ptdump);
	u64 pa = PFN_PHYS(pte_pfn(__pte(val)));
	u64 prot = 0;

	अगर (level >= 0)
		prot = val & pg_level[level].mask;

	अगर (st->level == -1) अणु
		st->level = level;
		st->current_prot = prot;
		st->start_address = addr;
		st->start_pa = pa;
		st->last_pa = pa;
		pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
	पूर्ण अन्यथा अगर (prot != st->current_prot ||
		   level != st->level || addr >= st->marker[1].start_address) अणु
		अगर (st->current_prot) अणु
			note_prot_wx(st, addr);
			dump_addr(st, addr);
			dump_prot(st);
			pt_dump_seq_माला_दो(st->seq, "\n");
		पूर्ण

		जबतक (addr >= st->marker[1].start_address) अणु
			st->marker++;
			pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n",
					   st->marker->name);
		पूर्ण

		st->start_address = addr;
		st->start_pa = pa;
		st->last_pa = pa;
		st->current_prot = prot;
		st->level = level;
	पूर्ण अन्यथा अणु
		st->last_pa = pa;
	पूर्ण
पूर्ण

अटल व्योम ptdump_walk(काष्ठा seq_file *s, काष्ठा ptd_mm_info *pinfo)
अणु
	काष्ठा pg_state st = अणु
		.seq = s,
		.marker = pinfo->markers,
		.level = -1,
		.ptdump = अणु
			.note_page = note_page,
			.range = (काष्ठा ptdump_range[]) अणु
				अणुpinfo->base_addr, pinfo->endपूर्ण,
				अणु0, 0पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण;

	ptdump_walk_pgd(&st.ptdump, pinfo->mm, शून्य);
पूर्ण

व्योम ptdump_check_wx(व्योम)
अणु
	काष्ठा pg_state st = अणु
		.seq = शून्य,
		.marker = (काष्ठा addr_marker[]) अणु
			अणु0, शून्यपूर्ण,
			अणु-1, शून्यपूर्ण,
		पूर्ण,
		.level = -1,
		.check_wx = true,
		.ptdump = अणु
			.note_page = note_page,
			.range = (काष्ठा ptdump_range[]) अणु
				अणुKERN_VIRT_START, अच_दीर्घ_उच्चपूर्ण,
				अणु0, 0पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण;

	ptdump_walk_pgd(&st.ptdump, &init_mm, शून्य);

	अगर (st.wx_pages)
		pr_warn("Checked W+X mappings: failed, %lu W+X pages found\n",
			st.wx_pages);
	अन्यथा
		pr_info("Checked W+X mappings: passed, no W+X pages found\n");
पूर्ण

अटल पूर्णांक ptdump_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ptdump_walk(m, m->निजी);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ptdump);

अटल पूर्णांक __init ptdump_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, j;

#अगर_घोषित CONFIG_KASAN
	address_markers[KASAN_SHADOW_START_NR].start_address = KASAN_SHADOW_START;
	address_markers[KASAN_SHADOW_END_NR].start_address = KASAN_SHADOW_END;
#पूर्ण_अगर
	address_markers[FIXMAP_START_NR].start_address = FIXADDR_START;
	address_markers[FIXMAP_END_NR].start_address = FIXADDR_TOP;
	address_markers[PCI_IO_START_NR].start_address = PCI_IO_START;
	address_markers[PCI_IO_END_NR].start_address = PCI_IO_END;
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	address_markers[VMEMMAP_START_NR].start_address = VMEMMAP_START;
	address_markers[VMEMMAP_END_NR].start_address = VMEMMAP_END;
#पूर्ण_अगर
	address_markers[VMALLOC_START_NR].start_address = VMALLOC_START;
	address_markers[VMALLOC_END_NR].start_address = VMALLOC_END;
	address_markers[PAGE_OFFSET_NR].start_address = PAGE_OFFSET;
#अगर_घोषित CONFIG_64BIT
	address_markers[MODULES_MAPPING_NR].start_address = MODULES_VADDR;
	address_markers[KERNEL_MAPPING_NR].start_address = kernel_virt_addr;
#पूर्ण_अगर

	kernel_ptd_info.base_addr = KERN_VIRT_START;

	क्रम (i = 0; i < ARRAY_SIZE(pg_level); i++)
		क्रम (j = 0; j < ARRAY_SIZE(pte_bits); j++)
			pg_level[i].mask |= pte_bits[j].mask;

	debugfs_create_file("kernel_page_tables", 0400, शून्य, &kernel_ptd_info,
			    &ptdump_fops);
#अगर_घोषित CONFIG_EFI
	अगर (efi_enabled(EFI_RUNTIME_SERVICES))
		debugfs_create_file("efi_page_tables", 0400, शून्य, &efi_ptd_info,
				    &ptdump_fops);
#पूर्ण_अगर

	वापस 0;
पूर्ण

device_initcall(ptdump_init);
