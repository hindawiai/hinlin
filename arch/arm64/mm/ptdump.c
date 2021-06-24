<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 * Debug helper to dump the current kernel pagetables of the प्रणाली
 * so that we can see what the various memory ranges are set to.
 *
 * Derived from x86 and arm implementation:
 * (C) Copyright 2008 Intel Corporation
 *
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/ptdump.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/ptdump.h>


क्रमागत address_markers_idx अणु
	PAGE_OFFSET_NR = 0,
	PAGE_END_NR,
#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
	KASAN_START_NR,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा addr_marker address_markers[] = अणु
	अणु PAGE_OFFSET,			"Linear Mapping start" पूर्ण,
	अणु 0 /* PAGE_END */,		"Linear Mapping end" पूर्ण,
#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
	अणु 0 /* KASAN_SHADOW_START */,	"Kasan shadow start" पूर्ण,
	अणु KASAN_SHADOW_END,		"Kasan shadow end" पूर्ण,
#पूर्ण_अगर
	अणु BPF_JIT_REGION_START,		"BPF start" पूर्ण,
	अणु BPF_JIT_REGION_END,		"BPF end" पूर्ण,
	अणु MODULES_VADDR,		"Modules start" पूर्ण,
	अणु MODULES_END,			"Modules end" पूर्ण,
	अणु VMALLOC_START,		"vmalloc() area" पूर्ण,
	अणु VMALLOC_END,			"vmalloc() end" पूर्ण,
	अणु FIXADDR_START,		"Fixmap start" पूर्ण,
	अणु FIXADDR_TOP,			"Fixmap end" पूर्ण,
	अणु PCI_IO_START,			"PCI I/O start" पूर्ण,
	अणु PCI_IO_END,			"PCI I/O end" पूर्ण,
	अणु VMEMMAP_START,		"vmemmap start" पूर्ण,
	अणु VMEMMAP_START + VMEMMAP_SIZE,	"vmemmap end" पूर्ण,
	अणु -1,				शून्य पूर्ण,
पूर्ण;

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
	पूर्णांक level;
	u64 current_prot;
	bool check_wx;
	अचिन्हित दीर्घ wx_pages;
	अचिन्हित दीर्घ uxn_pages;
पूर्ण;

काष्ठा prot_bits अणु
	u64		mask;
	u64		val;
	स्थिर अक्षर	*set;
	स्थिर अक्षर	*clear;
पूर्ण;

अटल स्थिर काष्ठा prot_bits pte_bits[] = अणु
	अणु
		.mask	= PTE_VALID,
		.val	= PTE_VALID,
		.set	= " ",
		.clear	= "F",
	पूर्ण, अणु
		.mask	= PTE_USER,
		.val	= PTE_USER,
		.set	= "USR",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= PTE_RDONLY,
		.val	= PTE_RDONLY,
		.set	= "ro",
		.clear	= "RW",
	पूर्ण, अणु
		.mask	= PTE_PXN,
		.val	= PTE_PXN,
		.set	= "NX",
		.clear	= "x ",
	पूर्ण, अणु
		.mask	= PTE_SHARED,
		.val	= PTE_SHARED,
		.set	= "SHD",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= PTE_AF,
		.val	= PTE_AF,
		.set	= "AF",
		.clear	= "  ",
	पूर्ण, अणु
		.mask	= PTE_NG,
		.val	= PTE_NG,
		.set	= "NG",
		.clear	= "  ",
	पूर्ण, अणु
		.mask	= PTE_CONT,
		.val	= PTE_CONT,
		.set	= "CON",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= PTE_TABLE_BIT,
		.val	= PTE_TABLE_BIT,
		.set	= "   ",
		.clear	= "BLK",
	पूर्ण, अणु
		.mask	= PTE_UXN,
		.val	= PTE_UXN,
		.set	= "UXN",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= PTE_GP,
		.val	= PTE_GP,
		.set	= "GP",
		.clear	= "  ",
	पूर्ण, अणु
		.mask	= PTE_ATTRINDX_MASK,
		.val	= PTE_ATTRINDX(MT_DEVICE_nGnRnE),
		.set	= "DEVICE/nGnRnE",
	पूर्ण, अणु
		.mask	= PTE_ATTRINDX_MASK,
		.val	= PTE_ATTRINDX(MT_DEVICE_nGnRE),
		.set	= "DEVICE/nGnRE",
	पूर्ण, अणु
		.mask	= PTE_ATTRINDX_MASK,
		.val	= PTE_ATTRINDX(MT_DEVICE_GRE),
		.set	= "DEVICE/GRE",
	पूर्ण, अणु
		.mask	= PTE_ATTRINDX_MASK,
		.val	= PTE_ATTRINDX(MT_NORMAL_NC),
		.set	= "MEM/NORMAL-NC",
	पूर्ण, अणु
		.mask	= PTE_ATTRINDX_MASK,
		.val	= PTE_ATTRINDX(MT_NORMAL),
		.set	= "MEM/NORMAL",
	पूर्ण, अणु
		.mask	= PTE_ATTRINDX_MASK,
		.val	= PTE_ATTRINDX(MT_NORMAL_TAGGED),
		.set	= "MEM/NORMAL-TAGGED",
	पूर्ण
पूर्ण;

काष्ठा pg_level अणु
	स्थिर काष्ठा prot_bits *bits;
	स्थिर अक्षर *name;
	माप_प्रकार num;
	u64 mask;
पूर्ण;

अटल काष्ठा pg_level pg_level[] = अणु
	अणु /* pgd */
		.name	= "PGD",
		.bits	= pte_bits,
		.num	= ARRAY_SIZE(pte_bits),
	पूर्ण, अणु /* p4d */
		.name	= "P4D",
		.bits	= pte_bits,
		.num	= ARRAY_SIZE(pte_bits),
	पूर्ण, अणु /* pud */
		.name	= (CONFIG_PGTABLE_LEVELS > 3) ? "PUD" : "PGD",
		.bits	= pte_bits,
		.num	= ARRAY_SIZE(pte_bits),
	पूर्ण, अणु /* pmd */
		.name	= (CONFIG_PGTABLE_LEVELS > 2) ? "PMD" : "PGD",
		.bits	= pte_bits,
		.num	= ARRAY_SIZE(pte_bits),
	पूर्ण, अणु /* pte */
		.name	= "PTE",
		.bits	= pte_bits,
		.num	= ARRAY_SIZE(pte_bits),
	पूर्ण,
पूर्ण;

अटल व्योम dump_prot(काष्ठा pg_state *st, स्थिर काष्ठा prot_bits *bits,
			माप_प्रकार num)
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

अटल व्योम note_prot_uxn(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	अगर (!st->check_wx)
		वापस;

	अगर ((st->current_prot & PTE_UXN) == PTE_UXN)
		वापस;

	WARN_ONCE(1, "arm64/mm: Found non-UXN mapping at address %p/%pS\n",
		  (व्योम *)st->start_address, (व्योम *)st->start_address);

	st->uxn_pages += (addr - st->start_address) / PAGE_SIZE;
पूर्ण

अटल व्योम note_prot_wx(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
	अगर (!st->check_wx)
		वापस;
	अगर ((st->current_prot & PTE_RDONLY) == PTE_RDONLY)
		वापस;
	अगर ((st->current_prot & PTE_PXN) == PTE_PXN)
		वापस;

	WARN_ONCE(1, "arm64/mm: Found insecure W+X mapping at address %p/%pS\n",
		  (व्योम *)st->start_address, (व्योम *)st->start_address);

	st->wx_pages += (addr - st->start_address) / PAGE_SIZE;
पूर्ण

अटल व्योम note_page(काष्ठा ptdump_state *pt_st, अचिन्हित दीर्घ addr, पूर्णांक level,
		      u64 val)
अणु
	काष्ठा pg_state *st = container_of(pt_st, काष्ठा pg_state, ptdump);
	अटल स्थिर अक्षर units[] = "KMGTPE";
	u64 prot = 0;

	अगर (level >= 0)
		prot = val & pg_level[level].mask;

	अगर (st->level == -1) अणु
		st->level = level;
		st->current_prot = prot;
		st->start_address = addr;
		pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
	पूर्ण अन्यथा अगर (prot != st->current_prot || level != st->level ||
		   addr >= st->marker[1].start_address) अणु
		स्थिर अक्षर *unit = units;
		अचिन्हित दीर्घ delta;

		अगर (st->current_prot) अणु
			note_prot_uxn(st, addr);
			note_prot_wx(st, addr);
		पूर्ण

		pt_dump_seq_म_लिखो(st->seq, "0x%016lx-0x%016lx   ",
				   st->start_address, addr);

		delta = (addr - st->start_address) >> 10;
		जबतक (!(delta & 1023) && unit[1]) अणु
			delta >>= 10;
			unit++;
		पूर्ण
		pt_dump_seq_म_लिखो(st->seq, "%9lu%c %s", delta, *unit,
				   pg_level[st->level].name);
		अगर (st->current_prot && pg_level[st->level].bits)
			dump_prot(st, pg_level[st->level].bits,
				  pg_level[st->level].num);
		pt_dump_seq_माला_दो(st->seq, "\n");

		अगर (addr >= st->marker[1].start_address) अणु
			st->marker++;
			pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
		पूर्ण

		st->start_address = addr;
		st->current_prot = prot;
		st->level = level;
	पूर्ण

	अगर (addr >= st->marker[1].start_address) अणु
		st->marker++;
		pt_dump_seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
	पूर्ण

पूर्ण

व्योम ptdump_walk(काष्ठा seq_file *s, काष्ठा ptdump_info *info)
अणु
	अचिन्हित दीर्घ end = ~0UL;
	काष्ठा pg_state st;

	अगर (info->base_addr < TASK_SIZE_64)
		end = TASK_SIZE_64;

	st = (काष्ठा pg_state)अणु
		.seq = s,
		.marker = info->markers,
		.level = -1,
		.ptdump = अणु
			.note_page = note_page,
			.range = (काष्ठा ptdump_range[])अणु
				अणुinfo->base_addr, endपूर्ण,
				अणु0, 0पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण;

	ptdump_walk_pgd(&st.ptdump, info->mm, शून्य);
पूर्ण

अटल व्योम __init ptdump_initialize(व्योम)
अणु
	अचिन्हित i, j;

	क्रम (i = 0; i < ARRAY_SIZE(pg_level); i++)
		अगर (pg_level[i].bits)
			क्रम (j = 0; j < pg_level[i].num; j++)
				pg_level[i].mask |= pg_level[i].bits[j].mask;
पूर्ण

अटल काष्ठा ptdump_info kernel_ptdump_info = अणु
	.mm		= &init_mm,
	.markers	= address_markers,
	.base_addr	= PAGE_OFFSET,
पूर्ण;

व्योम ptdump_check_wx(व्योम)
अणु
	काष्ठा pg_state st = अणु
		.seq = शून्य,
		.marker = (काष्ठा addr_marker[]) अणु
			अणु 0, शून्यपूर्ण,
			अणु -1, शून्यपूर्ण,
		पूर्ण,
		.level = -1,
		.check_wx = true,
		.ptdump = अणु
			.note_page = note_page,
			.range = (काष्ठा ptdump_range[]) अणु
				अणुPAGE_OFFSET, ~0ULपूर्ण,
				अणु0, 0पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण;

	ptdump_walk_pgd(&st.ptdump, &init_mm, शून्य);

	अगर (st.wx_pages || st.uxn_pages)
		pr_warn("Checked W+X mappings: FAILED, %lu W+X pages found, %lu non-UXN pages found\n",
			st.wx_pages, st.uxn_pages);
	अन्यथा
		pr_info("Checked W+X mappings: passed, no W+X pages found\n");
पूर्ण

अटल पूर्णांक __init ptdump_init(व्योम)
अणु
	address_markers[PAGE_END_NR].start_address = PAGE_END;
#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
	address_markers[KASAN_START_NR].start_address = KASAN_SHADOW_START;
#पूर्ण_अगर
	ptdump_initialize();
	ptdump_debugfs_रेजिस्टर(&kernel_ptdump_info, "kernel_page_tables");
	वापस 0;
पूर्ण
device_initcall(ptdump_init);
