<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kasan.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/mem_detect.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/uv.h>

अचिन्हित दीर्घ kasan_vmax;
अटल अचिन्हित दीर्घ segment_pos __initdata;
अटल अचिन्हित दीर्घ segment_low __initdata;
अटल अचिन्हित दीर्घ pgalloc_pos __initdata;
अटल अचिन्हित दीर्घ pgalloc_low __initdata;
अटल अचिन्हित दीर्घ pgalloc_मुक्तable __initdata;
अटल bool has_edat __initdata;
अटल bool has_nx __initdata;

#घोषणा __sha(x) ((अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)x))

अटल pgd_t early_pg_dir[PTRS_PER_PGD] __initdata __aligned(PAGE_SIZE);

अटल व्योम __init kasan_early_panic(स्थिर अक्षर *reason)
अणु
	sclp_early_prपूर्णांकk("The Linux kernel failed to boot with the KernelAddressSanitizer:\n");
	sclp_early_prपूर्णांकk(reason);
	disabled_रुको();
पूर्ण

अटल व्योम * __init kasan_early_alloc_segment(व्योम)
अणु
	segment_pos -= _SEGMENT_SIZE;

	अगर (segment_pos < segment_low)
		kasan_early_panic("out of memory during initialisation\n");

	वापस (व्योम *)segment_pos;
पूर्ण

अटल व्योम * __init kasan_early_alloc_pages(अचिन्हित पूर्णांक order)
अणु
	pgalloc_pos -= (PAGE_SIZE << order);

	अगर (pgalloc_pos < pgalloc_low)
		kasan_early_panic("out of memory during initialisation\n");

	वापस (व्योम *)pgalloc_pos;
पूर्ण

अटल व्योम * __init kasan_early_crst_alloc(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ *table;

	table = kasan_early_alloc_pages(CRST_ALLOC_ORDER);
	अगर (table)
		crst_table_init(table, val);
	वापस table;
पूर्ण

अटल pte_t * __init kasan_early_pte_alloc(व्योम)
अणु
	अटल व्योम *pte_leftover;
	pte_t *pte;

	BUILD_BUG_ON(_PAGE_TABLE_SIZE * 2 != PAGE_SIZE);

	अगर (!pte_leftover) अणु
		pte_leftover = kasan_early_alloc_pages(0);
		pte = pte_leftover + _PAGE_TABLE_SIZE;
	पूर्ण अन्यथा अणु
		pte = pte_leftover;
		pte_leftover = शून्य;
	पूर्ण
	स_रखो64((u64 *)pte, _PAGE_INVALID, PTRS_PER_PTE);
	वापस pte;
पूर्ण

क्रमागत populate_mode अणु
	POPULATE_ONE2ONE,
	POPULATE_MAP,
	POPULATE_ZERO_SHADOW,
	POPULATE_SHALLOW
पूर्ण;
अटल व्योम __init kasan_early_pgtable_populate(अचिन्हित दीर्घ address,
						अचिन्हित दीर्घ end,
						क्रमागत populate_mode mode)
अणु
	अचिन्हित दीर्घ pgt_prot_zero, pgt_prot, sgt_prot;
	pgd_t *pg_dir;
	p4d_t *p4_dir;
	pud_t *pu_dir;
	pmd_t *pm_dir;
	pte_t *pt_dir;

	pgt_prot_zero = pgprot_val(PAGE_KERNEL_RO);
	अगर (!has_nx)
		pgt_prot_zero &= ~_PAGE_NOEXEC;
	pgt_prot = pgprot_val(PAGE_KERNEL);
	sgt_prot = pgprot_val(SEGMENT_KERNEL);
	अगर (!has_nx || mode == POPULATE_ONE2ONE) अणु
		pgt_prot &= ~_PAGE_NOEXEC;
		sgt_prot &= ~_SEGMENT_ENTRY_NOEXEC;
	पूर्ण

	जबतक (address < end) अणु
		pg_dir = pgd_offset_k(address);
		अगर (pgd_none(*pg_dir)) अणु
			अगर (mode == POPULATE_ZERO_SHADOW &&
			    IS_ALIGNED(address, PGसूची_SIZE) &&
			    end - address >= PGसूची_SIZE) अणु
				pgd_populate(&init_mm, pg_dir,
						kasan_early_shaकरोw_p4d);
				address = (address + PGसूची_SIZE) & PGसूची_MASK;
				जारी;
			पूर्ण
			p4_dir = kasan_early_crst_alloc(_REGION2_ENTRY_EMPTY);
			pgd_populate(&init_mm, pg_dir, p4_dir);
		पूर्ण

		अगर (mode == POPULATE_SHALLOW) अणु
			address = (address + P4D_SIZE) & P4D_MASK;
			जारी;
		पूर्ण

		p4_dir = p4d_offset(pg_dir, address);
		अगर (p4d_none(*p4_dir)) अणु
			अगर (mode == POPULATE_ZERO_SHADOW &&
			    IS_ALIGNED(address, P4D_SIZE) &&
			    end - address >= P4D_SIZE) अणु
				p4d_populate(&init_mm, p4_dir,
						kasan_early_shaकरोw_pud);
				address = (address + P4D_SIZE) & P4D_MASK;
				जारी;
			पूर्ण
			pu_dir = kasan_early_crst_alloc(_REGION3_ENTRY_EMPTY);
			p4d_populate(&init_mm, p4_dir, pu_dir);
		पूर्ण

		pu_dir = pud_offset(p4_dir, address);
		अगर (pud_none(*pu_dir)) अणु
			अगर (mode == POPULATE_ZERO_SHADOW &&
			    IS_ALIGNED(address, PUD_SIZE) &&
			    end - address >= PUD_SIZE) अणु
				pud_populate(&init_mm, pu_dir,
						kasan_early_shaकरोw_pmd);
				address = (address + PUD_SIZE) & PUD_MASK;
				जारी;
			पूर्ण
			pm_dir = kasan_early_crst_alloc(_SEGMENT_ENTRY_EMPTY);
			pud_populate(&init_mm, pu_dir, pm_dir);
		पूर्ण

		pm_dir = pmd_offset(pu_dir, address);
		अगर (pmd_none(*pm_dir)) अणु
			अगर (mode == POPULATE_ZERO_SHADOW &&
			    IS_ALIGNED(address, PMD_SIZE) &&
			    end - address >= PMD_SIZE) अणु
				pmd_populate(&init_mm, pm_dir,
						kasan_early_shaकरोw_pte);
				address = (address + PMD_SIZE) & PMD_MASK;
				जारी;
			पूर्ण
			/* the first megabyte of 1:1 is mapped with 4k pages */
			अगर (has_edat && address && end - address >= PMD_SIZE &&
			    mode != POPULATE_ZERO_SHADOW) अणु
				व्योम *page;

				अगर (mode == POPULATE_ONE2ONE) अणु
					page = (व्योम *)address;
				पूर्ण अन्यथा अणु
					page = kasan_early_alloc_segment();
					स_रखो(page, 0, _SEGMENT_SIZE);
				पूर्ण
				pmd_val(*pm_dir) = __pa(page) | sgt_prot;
				address = (address + PMD_SIZE) & PMD_MASK;
				जारी;
			पूर्ण

			pt_dir = kasan_early_pte_alloc();
			pmd_populate(&init_mm, pm_dir, pt_dir);
		पूर्ण अन्यथा अगर (pmd_large(*pm_dir)) अणु
			address = (address + PMD_SIZE) & PMD_MASK;
			जारी;
		पूर्ण

		pt_dir = pte_offset_kernel(pm_dir, address);
		अगर (pte_none(*pt_dir)) अणु
			व्योम *page;

			चयन (mode) अणु
			हाल POPULATE_ONE2ONE:
				page = (व्योम *)address;
				pte_val(*pt_dir) = __pa(page) | pgt_prot;
				अवरोध;
			हाल POPULATE_MAP:
				page = kasan_early_alloc_pages(0);
				स_रखो(page, 0, PAGE_SIZE);
				pte_val(*pt_dir) = __pa(page) | pgt_prot;
				अवरोध;
			हाल POPULATE_ZERO_SHADOW:
				page = kasan_early_shaकरोw_page;
				pte_val(*pt_dir) = __pa(page) | pgt_prot_zero;
				अवरोध;
			हाल POPULATE_SHALLOW:
				/* should never happen */
				अवरोध;
			पूर्ण
		पूर्ण
		address += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल व्योम __init kasan_set_pgd(pgd_t *pgd, अचिन्हित दीर्घ asce_type)
अणु
	अचिन्हित दीर्घ asce_bits;

	asce_bits = asce_type | _ASCE_TABLE_LENGTH;
	S390_lowcore.kernel_asce = (__pa(pgd) & PAGE_MASK) | asce_bits;
	S390_lowcore.user_asce = S390_lowcore.kernel_asce;

	__ctl_load(S390_lowcore.kernel_asce, 1, 1);
	__ctl_load(S390_lowcore.kernel_asce, 7, 7);
	__ctl_load(S390_lowcore.kernel_asce, 13, 13);
पूर्ण

अटल व्योम __init kasan_enable_dat(व्योम)
अणु
	psw_t psw;

	psw.mask = __extract_psw();
	psw_bits(psw).dat = 1;
	psw_bits(psw).as = PSW_BITS_AS_HOME;
	__load_psw_mask(psw.mask);
पूर्ण

अटल व्योम __init kasan_early_detect_facilities(व्योम)
अणु
	अगर (test_facility(8)) अणु
		has_edat = true;
		__ctl_set_bit(0, 23);
	पूर्ण
	अगर (!noexec_disabled && test_facility(130)) अणु
		has_nx = true;
		__ctl_set_bit(0, 20);
	पूर्ण
पूर्ण

अटल bool __init has_uv_sec_stor_limit(व्योम)
अणु
	/*
	 * keep these conditions in line with setup_uv()
	 */
	अगर (!is_prot_virt_host())
		वापस false;

	अगर (is_prot_virt_guest())
		वापस false;

	अगर (!test_facility(158))
		वापस false;

	वापस !!uv_info.max_sec_stor_addr;
पूर्ण

व्योम __init kasan_early_init(व्योम)
अणु
	अचिन्हित दीर्घ untracked_mem_end;
	अचिन्हित दीर्घ shaकरोw_alloc_size;
	अचिन्हित दीर्घ vmax_unlimited;
	अचिन्हित दीर्घ initrd_end;
	अचिन्हित दीर्घ memsize;
	अचिन्हित दीर्घ pgt_prot = pgprot_val(PAGE_KERNEL_RO);
	pte_t pte_z;
	pmd_t pmd_z = __pmd(__pa(kasan_early_shaकरोw_pte) | _SEGMENT_ENTRY);
	pud_t pud_z = __pud(__pa(kasan_early_shaकरोw_pmd) | _REGION3_ENTRY);
	p4d_t p4d_z = __p4d(__pa(kasan_early_shaकरोw_pud) | _REGION2_ENTRY);

	kasan_early_detect_facilities();
	अगर (!has_nx)
		pgt_prot &= ~_PAGE_NOEXEC;
	pte_z = __pte(__pa(kasan_early_shaकरोw_page) | pgt_prot);

	memsize = get_mem_detect_end();
	अगर (!memsize)
		kasan_early_panic("cannot detect physical memory size\n");
	/*
	 * Kasan currently supports standby memory but only अगर it follows
	 * online memory (शेष allocation), i.e. no memory holes.
	 * - memsize represents end of online memory
	 * - ident_map_size represents online + standby and memory limits
	 *   accounted.
	 * Kasan maps "memsize" right away.
	 * [0, memsize]			- as identity mapping
	 * [__sha(0), __sha(memsize)]	- shaकरोw memory क्रम identity mapping
	 * The rest [memsize, ident_map_size] अगर memsize < ident_map_size
	 * could be mapped/unmapped dynamically later during memory hotplug.
	 */
	memsize = min(memsize, ident_map_size);

	BUILD_BUG_ON(!IS_ALIGNED(KASAN_SHADOW_START, P4D_SIZE));
	BUILD_BUG_ON(!IS_ALIGNED(KASAN_SHADOW_END, P4D_SIZE));
	crst_table_init((अचिन्हित दीर्घ *)early_pg_dir, _REGION2_ENTRY_EMPTY);
	untracked_mem_end = kasan_vmax = vmax_unlimited = _REGION1_SIZE;
	अगर (has_uv_sec_stor_limit())
		kasan_vmax = min(vmax_unlimited, uv_info.max_sec_stor_addr);

	/* init kasan zero shaकरोw */
	crst_table_init((अचिन्हित दीर्घ *)kasan_early_shaकरोw_p4d,
				p4d_val(p4d_z));
	crst_table_init((अचिन्हित दीर्घ *)kasan_early_shaकरोw_pud,
				pud_val(pud_z));
	crst_table_init((अचिन्हित दीर्घ *)kasan_early_shaकरोw_pmd,
				pmd_val(pmd_z));
	स_रखो64((u64 *)kasan_early_shaकरोw_pte, pte_val(pte_z), PTRS_PER_PTE);

	shaकरोw_alloc_size = memsize >> KASAN_SHADOW_SCALE_SHIFT;
	pgalloc_low = round_up((अचिन्हित दीर्घ)_end, _SEGMENT_SIZE);
	अगर (IS_ENABLED(CONFIG_BLK_DEV_INITRD)) अणु
		initrd_end =
		    round_up(INITRD_START + INITRD_SIZE, _SEGMENT_SIZE);
		pgalloc_low = max(pgalloc_low, initrd_end);
	पूर्ण

	अगर (pgalloc_low + shaकरोw_alloc_size > memsize)
		kasan_early_panic("out of memory during initialisation\n");

	अगर (has_edat) अणु
		segment_pos = round_करोwn(memsize, _SEGMENT_SIZE);
		segment_low = segment_pos - shaकरोw_alloc_size;
		pgalloc_pos = segment_low;
	पूर्ण अन्यथा अणु
		pgalloc_pos = memsize;
	पूर्ण
	init_mm.pgd = early_pg_dir;
	/*
	 * Current memory layout:
	 * +- 0 -------------+	   +- shaकरोw start -+
	 * | 1:1 ram mapping |	  /| 1/8 ram	    |
	 * |		     |	 / |		    |
	 * +- end of ram ----+	/  +----------------+
	 * | ... gap ...     | /   |		    |
	 * |		     |/    |	kasan	    |
	 * +- shaकरोw start --+	   |	zero	    |
	 * | 1/8 addr space  |	   |	page	    |
	 * +- shaकरोw end    -+	   |	mapping	    |
	 * | ... gap ...     |\    |  (untracked)   |
	 * +- vदो_स्मृति area  -+ \   |		    |
	 * | vदो_स्मृति_size    |	\  |		    |
	 * +- modules vaddr -+	 \ +----------------+
	 * | 2Gb	     |	  \|	  unmapped  | allocated per module
	 * +-----------------+	   +- shaकरोw end ---+
	 *
	 * Current memory layout (KASAN_VMALLOC):
	 * +- 0 -------------+	   +- shaकरोw start -+
	 * | 1:1 ram mapping |	  /| 1/8 ram	    |
	 * |		     |	 / |		    |
	 * +- end of ram ----+	/  +----------------+
	 * | ... gap ...     | /   |	kasan	    |
	 * |		     |/    |	zero	    |
	 * +- shaकरोw start --+	   |	page	    |
	 * | 1/8 addr space  |	   |	mapping     |
	 * +- shaकरोw end    -+	   |  (untracked)   |
	 * | ... gap ...     |\    |		    |
	 * +- vदो_स्मृति area  -+ \   +- vदो_स्मृति area -+
	 * | vदो_स्मृति_size    |	\  |shallow populate|
	 * +- modules vaddr -+	 \ +- modules area -+
	 * | 2Gb	     |	  \|shallow populate|
	 * +-----------------+	   +- shaकरोw end ---+
	 */
	/* populate kasan shaकरोw (क्रम identity mapping and zero page mapping) */
	kasan_early_pgtable_populate(__sha(0), __sha(memsize), POPULATE_MAP);
	अगर (IS_ENABLED(CONFIG_MODULES))
		untracked_mem_end = kasan_vmax - MODULES_LEN;
	अगर (IS_ENABLED(CONFIG_KASAN_VMALLOC)) अणु
		untracked_mem_end = kasan_vmax - vदो_स्मृति_size - MODULES_LEN;
		/* shallowly populate kasan shaकरोw क्रम vदो_स्मृति and modules */
		kasan_early_pgtable_populate(__sha(untracked_mem_end), __sha(kasan_vmax),
					     POPULATE_SHALLOW);
	पूर्ण
	/* populate kasan shaकरोw क्रम untracked memory */
	kasan_early_pgtable_populate(__sha(ident_map_size), __sha(untracked_mem_end),
				     POPULATE_ZERO_SHADOW);
	kasan_early_pgtable_populate(__sha(kasan_vmax), __sha(vmax_unlimited),
				     POPULATE_ZERO_SHADOW);
	/* memory allocated क्रम identity mapping काष्ठाs will be मुक्तd later */
	pgalloc_मुक्तable = pgalloc_pos;
	/* populate identity mapping */
	kasan_early_pgtable_populate(0, memsize, POPULATE_ONE2ONE);
	kasan_set_pgd(early_pg_dir, _ASCE_TYPE_REGION2);
	kasan_enable_dat();
	/* enable kasan */
	init_task.kasan_depth = 0;
	memblock_reserve(pgalloc_pos, memsize - pgalloc_pos);
	sclp_early_prपूर्णांकk("KernelAddressSanitizer initialized\n");
पूर्ण

व्योम __init kasan_copy_shaकरोw_mapping(व्योम)
अणु
	/*
	 * At this poपूर्णांक we are still running on early pages setup early_pg_dir,
	 * जबतक swapper_pg_dir has just been initialized with identity mapping.
	 * Carry over shaकरोw memory region from early_pg_dir to swapper_pg_dir.
	 */

	pgd_t *pg_dir_src;
	pgd_t *pg_dir_dst;
	p4d_t *p4_dir_src;
	p4d_t *p4_dir_dst;

	pg_dir_src = pgd_offset_raw(early_pg_dir, KASAN_SHADOW_START);
	pg_dir_dst = pgd_offset_raw(init_mm.pgd, KASAN_SHADOW_START);
	p4_dir_src = p4d_offset(pg_dir_src, KASAN_SHADOW_START);
	p4_dir_dst = p4d_offset(pg_dir_dst, KASAN_SHADOW_START);
	स_नकल(p4_dir_dst, p4_dir_src,
	       (KASAN_SHADOW_SIZE >> P4D_SHIFT) * माप(p4d_t));
पूर्ण

व्योम __init kasan_मुक्त_early_identity(व्योम)
अणु
	memblock_मुक्त(pgalloc_pos, pgalloc_मुक्तable - pgalloc_pos);
पूर्ण
