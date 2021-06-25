<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/set_memory.h>
#समावेश <linux/ptdump.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mm.h>
#समावेश <linux/kasan.h>
#समावेश <यंत्र/ptdump.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/sections.h>

अटल अचिन्हित दीर्घ max_addr;

काष्ठा addr_marker अणु
	अचिन्हित दीर्घ start_address;
	स्थिर अक्षर *name;
पूर्ण;

क्रमागत address_markers_idx अणु
	IDENTITY_BEFORE_NR = 0,
	IDENTITY_BEFORE_END_NR,
	KERNEL_START_NR,
	KERNEL_END_NR,
	IDENTITY_AFTER_NR,
	IDENTITY_AFTER_END_NR,
#अगर_घोषित CONFIG_KASAN
	KASAN_SHADOW_START_NR,
	KASAN_SHADOW_END_NR,
#पूर्ण_अगर
	VMEMMAP_NR,
	VMEMMAP_END_NR,
	VMALLOC_NR,
	VMALLOC_END_NR,
	MODULES_NR,
	MODULES_END_NR,
पूर्ण;

अटल काष्ठा addr_marker address_markers[] = अणु
	[IDENTITY_BEFORE_NR]	= अणु0, "Identity Mapping Start"पूर्ण,
	[IDENTITY_BEFORE_END_NR] = अणु(अचिन्हित दीर्घ)_stext, "Identity Mapping End"पूर्ण,
	[KERNEL_START_NR]	= अणु(अचिन्हित दीर्घ)_stext, "Kernel Image Start"पूर्ण,
	[KERNEL_END_NR]		= अणु(अचिन्हित दीर्घ)_end, "Kernel Image End"पूर्ण,
	[IDENTITY_AFTER_NR]	= अणु(अचिन्हित दीर्घ)_end, "Identity Mapping Start"पूर्ण,
	[IDENTITY_AFTER_END_NR]	= अणु0, "Identity Mapping End"पूर्ण,
#अगर_घोषित CONFIG_KASAN
	[KASAN_SHADOW_START_NR]	= अणुKASAN_SHADOW_START, "Kasan Shadow Start"पूर्ण,
	[KASAN_SHADOW_END_NR]	= अणुKASAN_SHADOW_END, "Kasan Shadow End"पूर्ण,
#पूर्ण_अगर
	[VMEMMAP_NR]		= अणु0, "vmemmap Area Start"पूर्ण,
	[VMEMMAP_END_NR]	= अणु0, "vmemmap Area End"पूर्ण,
	[VMALLOC_NR]		= अणु0, "vmalloc Area Start"पूर्ण,
	[VMALLOC_END_NR]	= अणु0, "vmalloc Area End"पूर्ण,
	[MODULES_NR]		= अणु0, "Modules Area Start"पूर्ण,
	[MODULES_END_NR]	= अणु0, "Modules Area End"पूर्ण,
	अणु -1, शून्य पूर्ण
पूर्ण;

काष्ठा pg_state अणु
	काष्ठा ptdump_state ptdump;
	काष्ठा seq_file *seq;
	पूर्णांक level;
	अचिन्हित पूर्णांक current_prot;
	bool check_wx;
	अचिन्हित दीर्घ wx_pages;
	अचिन्हित दीर्घ start_address;
	स्थिर काष्ठा addr_marker *marker;
पूर्ण;

#घोषणा pt_dump_seq_म_लिखो(m, fmt, args...)	\
(अणु						\
	काष्ठा seq_file *__m = (m);		\
						\
	अगर (__m)				\
		seq_म_लिखो(__m, fmt, ##args);	\
पूर्ण)

#घोषणा pt_dump_seq_माला_दो(m, fmt)		\
(अणु						\
	काष्ठा seq_file *__m = (m);		\
						\
	अगर (__m)				\
		seq_म_लिखो(__m, fmt);		\
पूर्ण)

अटल व्योम prपूर्णांक_prot(काष्ठा seq_file *m, अचिन्हित पूर्णांक pr, पूर्णांक level)
अणु
	अटल स्थिर अक्षर * स्थिर level_name[] =
		अणु "ASCE", "PGD", "PUD", "PMD", "PTE" पूर्ण;

	pt_dump_seq_म_लिखो(m, "%s ", level_name[level]);
	अगर (pr & _PAGE_INVALID) अणु
		pt_dump_seq_म_लिखो(m, "I\n");
		वापस;
	पूर्ण
	pt_dump_seq_माला_दो(m, (pr & _PAGE_PROTECT) ? "RO " : "RW ");
	pt_dump_seq_माला_दो(m, (pr & _PAGE_NOEXEC) ? "NX\n" : "X\n");
पूर्ण

अटल व्योम note_prot_wx(काष्ठा pg_state *st, अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_DEBUG_WX
	अगर (!st->check_wx)
		वापस;
	अगर (st->current_prot & _PAGE_INVALID)
		वापस;
	अगर (st->current_prot & _PAGE_PROTECT)
		वापस;
	अगर (st->current_prot & _PAGE_NOEXEC)
		वापस;
	/* The first lowcore page is currently still W+X. */
	अगर (addr == PAGE_SIZE)
		वापस;
	WARN_ONCE(1, "s390/mm: Found insecure W+X mapping at address %pS\n",
		  (व्योम *)st->start_address);
	st->wx_pages += (addr - st->start_address) / PAGE_SIZE;
#पूर्ण_अगर /* CONFIG_DEBUG_WX */
पूर्ण

अटल व्योम note_page(काष्ठा ptdump_state *pt_st, अचिन्हित दीर्घ addr, पूर्णांक level, u64 val)
अणु
	पूर्णांक width = माप(अचिन्हित दीर्घ) * 2;
	अटल स्थिर अक्षर units[] = "KMGTPE";
	स्थिर अक्षर *unit = units;
	अचिन्हित दीर्घ delta;
	काष्ठा pg_state *st;
	काष्ठा seq_file *m;
	अचिन्हित पूर्णांक prot;

	st = container_of(pt_st, काष्ठा pg_state, ptdump);
	m = st->seq;
	prot = val & (_PAGE_PROTECT | _PAGE_NOEXEC);
	अगर (level == 4 && (val & _PAGE_INVALID))
		prot = _PAGE_INVALID;
	/* For pmd_none() & मित्रs val माला_लो passed as zero. */
	अगर (level != 4 && !val)
		prot = _PAGE_INVALID;
	/* Final flush from generic code. */
	अगर (level == -1)
		addr = max_addr;
	अगर (st->level == -1) अणु
		pt_dump_seq_म_लिखो(m, "---[ %s ]---\n", st->marker->name);
		st->start_address = addr;
		st->current_prot = prot;
		st->level = level;
	पूर्ण अन्यथा अगर (prot != st->current_prot || level != st->level ||
		   addr >= st->marker[1].start_address) अणु
		note_prot_wx(st, addr);
		pt_dump_seq_म_लिखो(m, "0x%0*lx-0x%0*lx ",
				   width, st->start_address,
				   width, addr);
		delta = (addr - st->start_address) >> 10;
		जबतक (!(delta & 0x3ff) && unit[1]) अणु
			delta >>= 10;
			unit++;
		पूर्ण
		pt_dump_seq_म_लिखो(m, "%9lu%c ", delta, *unit);
		prपूर्णांक_prot(m, st->current_prot, st->level);
		जबतक (addr >= st->marker[1].start_address) अणु
			st->marker++;
			pt_dump_seq_म_लिखो(m, "---[ %s ]---\n", st->marker->name);
		पूर्ण
		st->start_address = addr;
		st->current_prot = prot;
		st->level = level;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_WX
व्योम ptdump_check_wx(व्योम)
अणु
	काष्ठा pg_state st = अणु
		.ptdump = अणु
			.note_page = note_page,
			.range = (काष्ठा ptdump_range[]) अणु
				अणु.start = 0, .end = max_addrपूर्ण,
				अणु.start = 0, .end = 0पूर्ण,
			पूर्ण
		पूर्ण,
		.seq = शून्य,
		.level = -1,
		.current_prot = 0,
		.check_wx = true,
		.wx_pages = 0,
		.start_address = 0,
		.marker = (काष्ठा addr_marker[]) अणु
			अणु .start_address =  0, .name = शून्यपूर्ण,
			अणु .start_address = -1, .name = शून्यपूर्ण,
		पूर्ण,
	पूर्ण;

	अगर (!MACHINE_HAS_NX)
		वापस;
	ptdump_walk_pgd(&st.ptdump, &init_mm, शून्य);
	अगर (st.wx_pages)
		pr_warn("Checked W+X mappings: FAILED, %lu W+X pages found\n", st.wx_pages);
	अन्यथा
		pr_info("Checked W+X mappings: passed, no unexpected W+X pages found\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_WX */

#अगर_घोषित CONFIG_PTDUMP_DEBUGFS
अटल पूर्णांक ptdump_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा pg_state st = अणु
		.ptdump = अणु
			.note_page = note_page,
			.range = (काष्ठा ptdump_range[]) अणु
				अणु.start = 0, .end = max_addrपूर्ण,
				अणु.start = 0, .end = 0पूर्ण,
			पूर्ण
		पूर्ण,
		.seq = m,
		.level = -1,
		.current_prot = 0,
		.check_wx = false,
		.wx_pages = 0,
		.start_address = 0,
		.marker = address_markers,
	पूर्ण;

	get_online_mems();
	mutex_lock(&cpa_mutex);
	ptdump_walk_pgd(&st.ptdump, &init_mm, शून्य);
	mutex_unlock(&cpa_mutex);
	put_online_mems();
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ptdump);
#पूर्ण_अगर /* CONFIG_PTDUMP_DEBUGFS */

/*
 * Heapsort from lib/sort.c is not a stable sorting algorithm, करो a simple
 * insertion sort to preserve the original order of markers with the same
 * start address.
 */
अटल व्योम sort_address_markers(व्योम)
अणु
	काष्ठा addr_marker पंचांगp;
	पूर्णांक i, j;

	क्रम (i = 1; i < ARRAY_SIZE(address_markers) - 1; i++) अणु
		पंचांगp = address_markers[i];
		क्रम (j = i - 1; j >= 0 && address_markers[j].start_address > पंचांगp.start_address; j--)
			address_markers[j + 1] = address_markers[j];
		address_markers[j + 1] = पंचांगp;
	पूर्ण
पूर्ण

अटल पूर्णांक pt_dump_init(व्योम)
अणु
	/*
	 * Figure out the maximum भव address being accessible with the
	 * kernel ASCE. We need this to keep the page table walker functions
	 * from accessing non-existent entries.
	 */
	max_addr = (S390_lowcore.kernel_asce & _REGION_ENTRY_TYPE_MASK) >> 2;
	max_addr = 1UL << (max_addr * 11 + 31);
	address_markers[IDENTITY_AFTER_END_NR].start_address = ident_map_size;
	address_markers[MODULES_NR].start_address = MODULES_VADDR;
	address_markers[MODULES_END_NR].start_address = MODULES_END;
	address_markers[VMEMMAP_NR].start_address = (अचिन्हित दीर्घ) vmemmap;
	address_markers[VMEMMAP_END_NR].start_address = (अचिन्हित दीर्घ)vmemmap + vmemmap_size;
	address_markers[VMALLOC_NR].start_address = VMALLOC_START;
	address_markers[VMALLOC_END_NR].start_address = VMALLOC_END;
	sort_address_markers();
#अगर_घोषित CONFIG_PTDUMP_DEBUGFS
	debugfs_create_file("kernel_page_tables", 0400, शून्य, शून्य, &ptdump_fops);
#पूर्ण_अगर /* CONFIG_PTDUMP_DEBUGFS */
	वापस 0;
पूर्ण
device_initcall(pt_dump_init);
