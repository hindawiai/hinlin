<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016, Rashmica Gupta, IBM Corp.
 *
 * This traverses the kernel भव memory and dumps the pages that are in
 * the hash pagetable, aदीर्घ with their flags to
 * /sys/kernel/debug/kernel_hash_pagetable.
 *
 * If radix is enabled then there is no hash page table and so no debugfs file
 * is generated.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/pgभाग.स>

काष्ठा pg_state अणु
	काष्ठा seq_file *seq;
	स्थिर काष्ठा addr_marker *marker;
	अचिन्हित दीर्घ start_address;
	अचिन्हित पूर्णांक level;
	u64 current_flags;
पूर्ण;

काष्ठा addr_marker अणु
	अचिन्हित दीर्घ start_address;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा addr_marker address_markers[] = अणु
	अणु 0,	"Start of kernel VM" पूर्ण,
	अणु 0,	"vmalloc() Area" पूर्ण,
	अणु 0,	"vmalloc() End" पूर्ण,
	अणु 0,	"isa I/O start" पूर्ण,
	अणु 0,	"isa I/O end" पूर्ण,
	अणु 0,	"phb I/O start" पूर्ण,
	अणु 0,	"phb I/O end" पूर्ण,
	अणु 0,	"I/O remap start" पूर्ण,
	अणु 0,	"I/O remap end" पूर्ण,
	अणु 0,	"vmemmap start" पूर्ण,
	अणु -1,	शून्य पूर्ण,
पूर्ण;

काष्ठा flag_info अणु
	u64		mask;
	u64		val;
	स्थिर अक्षर	*set;
	स्थिर अक्षर	*clear;
	bool		is_val;
	पूर्णांक		shअगरt;
पूर्ण;

अटल स्थिर काष्ठा flag_info v_flag_array[] = अणु
	अणु
		.mask   = SLB_VSID_B,
		.val    = SLB_VSID_B_256M,
		.set    = "ssize: 256M",
		.clear  = "ssize: 1T  ",
	पूर्ण, अणु
		.mask	= HPTE_V_SECONDARY,
		.val	= HPTE_V_SECONDARY,
		.set	= "secondary",
		.clear	= "primary  ",
	पूर्ण, अणु
		.mask	= HPTE_V_VALID,
		.val	= HPTE_V_VALID,
		.set	= "valid  ",
		.clear	= "invalid",
	पूर्ण, अणु
		.mask	= HPTE_V_BOLTED,
		.val	= HPTE_V_BOLTED,
		.set	= "bolted",
		.clear	= "",
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा flag_info r_flag_array[] = अणु
	अणु
		.mask	= HPTE_R_PP0 | HPTE_R_PP,
		.val	= PP_RWXX,
		.set	= "prot:RW--",
	पूर्ण, अणु
		.mask	= HPTE_R_PP0 | HPTE_R_PP,
		.val	= PP_RWRX,
		.set	= "prot:RWR-",
	पूर्ण, अणु
		.mask	= HPTE_R_PP0 | HPTE_R_PP,
		.val	= PP_RWRW,
		.set	= "prot:RWRW",
	पूर्ण, अणु
		.mask	= HPTE_R_PP0 | HPTE_R_PP,
		.val	= PP_RXRX,
		.set	= "prot:R-R-",
	पूर्ण, अणु
		.mask	= HPTE_R_PP0 | HPTE_R_PP,
		.val	= PP_RXXX,
		.set	= "prot:R---",
	पूर्ण, अणु
		.mask	= HPTE_R_KEY_HI | HPTE_R_KEY_LO,
		.val	= HPTE_R_KEY_HI | HPTE_R_KEY_LO,
		.set	= "key",
		.clear	= "",
		.is_val = true,
	पूर्ण, अणु
		.mask	= HPTE_R_R,
		.val	= HPTE_R_R,
		.set	= "ref",
		.clear	= "   ",
	पूर्ण, अणु
		.mask	= HPTE_R_C,
		.val	= HPTE_R_C,
		.set	= "changed",
		.clear	= "       ",
	पूर्ण, अणु
		.mask	= HPTE_R_N,
		.val	= HPTE_R_N,
		.set	= "no execute",
	पूर्ण, अणु
		.mask	= HPTE_R_WIMG,
		.val	= HPTE_R_W,
		.set	= "writethru",
	पूर्ण, अणु
		.mask	= HPTE_R_WIMG,
		.val	= HPTE_R_I,
		.set	= "no cache",
	पूर्ण, अणु
		.mask	= HPTE_R_WIMG,
		.val	= HPTE_R_G,
		.set	= "guarded",
	पूर्ण
पूर्ण;

अटल पूर्णांक calculate_pagesize(काष्ठा pg_state *st, पूर्णांक ps, अक्षर s[])
अणु
	अटल स्थिर अक्षर units[] = "BKMGTPE";
	स्थिर अक्षर *unit = units;

	जबतक (ps > 9 && unit[1]) अणु
		ps -= 10;
		unit++;
	पूर्ण
	seq_म_लिखो(st->seq, "  %s_ps: %i%c\t", s, 1<<ps, *unit);
	वापस ps;
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
			seq_म_लिखो(st->seq, "  %s:%llx", flag->set, val);
		पूर्ण अन्यथा अणु
			अगर ((pte & flag->mask) == flag->val)
				s = flag->set;
			अन्यथा
				s = flag->clear;
			अगर (s)
				seq_म_लिखो(st->seq, "  %s", s);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dump_hpte_info(काष्ठा pg_state *st, अचिन्हित दीर्घ ea, u64 v, u64 r,
		अचिन्हित दीर्घ rpn, पूर्णांक bps, पूर्णांक aps, अचिन्हित दीर्घ lp)
अणु
	पूर्णांक aps_index;

	जबतक (ea >= st->marker[1].start_address) अणु
		st->marker++;
		seq_म_लिखो(st->seq, "---[ %s ]---\n", st->marker->name);
	पूर्ण
	seq_म_लिखो(st->seq, "0x%lx:\t", ea);
	seq_म_लिखो(st->seq, "AVPN:%llx\t", HPTE_V_AVPN_VAL(v));
	dump_flag_info(st, v_flag_array, v, ARRAY_SIZE(v_flag_array));
	seq_म_लिखो(st->seq, "  rpn: %lx\t", rpn);
	dump_flag_info(st, r_flag_array, r, ARRAY_SIZE(r_flag_array));

	calculate_pagesize(st, bps, "base");
	aps_index = calculate_pagesize(st, aps, "actual");
	अगर (aps_index != 2)
		seq_म_लिखो(st->seq, "LP enc: %lx", lp);
	seq_अ_दो(st->seq, '\n');
पूर्ण


अटल पूर्णांक native_find(अचिन्हित दीर्घ ea, पूर्णांक psize, bool primary, u64 *v, u64
		*r)
अणु
	काष्ठा hash_pte *hptep;
	अचिन्हित दीर्घ hash, vsid, vpn, hpte_group, want_v, hpte_v;
	पूर्णांक i, ssize = mmu_kernel_ssize;
	अचिन्हित दीर्घ shअगरt = mmu_psize_defs[psize].shअगरt;

	/* calculate hash */
	vsid = get_kernel_vsid(ea, ssize);
	vpn  = hpt_vpn(ea, vsid, ssize);
	hash = hpt_hash(vpn, shअगरt, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/* to check in the secondary hash table, we invert the hash */
	अगर (!primary)
		hash = ~hash;
	hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	क्रम (i = 0; i < HPTES_PER_GROUP; i++) अणु
		hptep = htab_address + hpte_group;
		hpte_v = be64_to_cpu(hptep->v);

		अगर (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID)) अणु
			/* HPTE matches */
			*v = be64_to_cpu(hptep->v);
			*r = be64_to_cpu(hptep->r);
			वापस 0;
		पूर्ण
		++hpte_group;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक pseries_find(अचिन्हित दीर्घ ea, पूर्णांक psize, bool primary, u64 *v, u64 *r)
अणु
	काष्ठा hash_pte ptes[4];
	अचिन्हित दीर्घ vsid, vpn, hash, hpte_group, want_v;
	पूर्णांक i, j, ssize = mmu_kernel_ssize;
	दीर्घ lpar_rc = 0;
	अचिन्हित दीर्घ shअगरt = mmu_psize_defs[psize].shअगरt;

	/* calculate hash */
	vsid = get_kernel_vsid(ea, ssize);
	vpn  = hpt_vpn(ea, vsid, ssize);
	hash = hpt_hash(vpn, shअगरt, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/* to check in the secondary hash table, we invert the hash */
	अगर (!primary)
		hash = ~hash;
	hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	/* see अगर we can find an entry in the hpte with this hash */
	क्रम (i = 0; i < HPTES_PER_GROUP; i += 4, hpte_group += 4) अणु
		lpar_rc = plpar_pte_पढ़ो_4(0, hpte_group, (व्योम *)ptes);

		अगर (lpar_rc)
			जारी;
		क्रम (j = 0; j < 4; j++) अणु
			अगर (HPTE_V_COMPARE(ptes[j].v, want_v) &&
					(ptes[j].v & HPTE_V_VALID)) अणु
				/* HPTE matches */
				*v = ptes[j].v;
				*r = ptes[j].r;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम decode_r(पूर्णांक bps, अचिन्हित दीर्घ r, अचिन्हित दीर्घ *rpn, पूर्णांक *aps,
		अचिन्हित दीर्घ *lp_bits)
अणु
	काष्ठा mmu_psize_def entry;
	अचिन्हित दीर्घ arpn, mask, lp;
	पूर्णांक penc = -2, idx = 0, shअगरt;

	/*.
	 * The LP field has 8 bits. Depending on the actual page size, some of
	 * these bits are concatenated with the APRN to get the RPN. The rest
	 * of the bits in the LP field is the LP value and is an encoding क्रम
	 * the base page size and the actual page size.
	 *
	 *  -	find the mmu entry क्रम our base page size
	 *  -	go through all page encodings and use the associated mask to
	 *	find an encoding that matches our encoding in the LP field.
	 */
	arpn = (r & HPTE_R_RPN) >> HPTE_R_RPN_SHIFT;
	lp = arpn & 0xff;

	entry = mmu_psize_defs[bps];
	जबतक (idx < MMU_PAGE_COUNT) अणु
		penc = entry.penc[idx];
		अगर ((penc != -1) && (mmu_psize_defs[idx].shअगरt)) अणु
			shअगरt = mmu_psize_defs[idx].shअगरt -  HPTE_R_RPN_SHIFT;
			mask = (0x1 << (shअगरt)) - 1;
			अगर ((lp & mask) == penc) अणु
				*aps = mmu_pमाप_प्रकारo_shअगरt(idx);
				*lp_bits = lp & mask;
				*rpn = arpn >> shअगरt;
				वापस;
			पूर्ण
		पूर्ण
		idx++;
	पूर्ण
पूर्ण

अटल पूर्णांक base_hpte_find(अचिन्हित दीर्घ ea, पूर्णांक psize, bool primary, u64 *v,
			  u64 *r)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_PSERIES) && firmware_has_feature(FW_FEATURE_LPAR))
		वापस pseries_find(ea, psize, primary, v, r);

	वापस native_find(ea, psize, primary, v, r);
पूर्ण

अटल अचिन्हित दीर्घ hpte_find(काष्ठा pg_state *st, अचिन्हित दीर्घ ea, पूर्णांक psize)
अणु
	अचिन्हित दीर्घ slot;
	u64 v  = 0, r = 0;
	अचिन्हित दीर्घ rpn, lp_bits;
	पूर्णांक base_psize = 0, actual_psize = 0;

	अगर (ea < PAGE_OFFSET)
		वापस -1;

	/* Look in primary table */
	slot = base_hpte_find(ea, psize, true, &v, &r);

	/* Look in secondary table */
	अगर (slot == -1)
		slot = base_hpte_find(ea, psize, false, &v, &r);

	/* No entry found */
	अगर (slot == -1)
		वापस -1;

	/*
	 * We found an entry in the hash page table:
	 *  - check that this has the same base page
	 *  - find the actual page size
	 *  - find the RPN
	 */
	base_psize = mmu_pमाप_प्रकारo_shअगरt(psize);

	अगर ((v & HPTE_V_LARGE) == HPTE_V_LARGE) अणु
		decode_r(psize, r, &rpn, &actual_psize, &lp_bits);
	पूर्ण अन्यथा अणु
		/* 4K actual page size */
		actual_psize = 12;
		rpn = (r & HPTE_R_RPN) >> HPTE_R_RPN_SHIFT;
		/* In this हाल there are no LP bits */
		lp_bits = -1;
	पूर्ण
	/*
	 * We didn't find a matching encoding, so the PTE we found isn't क्रम
	 * this address.
	 */
	अगर (actual_psize == -1)
		वापस -1;

	dump_hpte_info(st, ea, v, r, rpn, base_psize, actual_psize, lp_bits);
	वापस 0;
पूर्ण

अटल व्योम walk_pte(काष्ठा pg_state *st, pmd_t *pmd, अचिन्हित दीर्घ start)
अणु
	pte_t *pte = pte_offset_kernel(pmd, 0);
	अचिन्हित दीर्घ addr, pteval, psize;
	पूर्णांक i, status;

	क्रम (i = 0; i < PTRS_PER_PTE; i++, pte++) अणु
		addr = start + i * PAGE_SIZE;
		pteval = pte_val(*pte);

		अगर (addr < VMALLOC_END)
			psize = mmu_vदो_स्मृति_psize;
		अन्यथा
			psize = mmu_io_psize;

		/* check क्रम secret 4K mappings */
		अगर (IS_ENABLED(CONFIG_PPC_64K_PAGES) &&
		    ((pteval & H_PAGE_COMBO) == H_PAGE_COMBO ||
		     (pteval & H_PAGE_4K_PFN) == H_PAGE_4K_PFN))
			psize = mmu_io_psize;

		/* check क्रम hashpte */
		status = hpte_find(st, addr, psize);

		अगर (((pteval & H_PAGE_HASHPTE) != H_PAGE_HASHPTE)
				&& (status != -1)) अणु
		/* found a hpte that is not in the linux page tables */
			seq_म_लिखो(st->seq, "page probably bolted before linux"
				" pagetables were set: addr:%lx, pteval:%lx\n",
				addr, pteval);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम walk_pmd(काष्ठा pg_state *st, pud_t *pud, अचिन्हित दीर्घ start)
अणु
	pmd_t *pmd = pmd_offset(pud, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PMD; i++, pmd++) अणु
		addr = start + i * PMD_SIZE;
		अगर (!pmd_none(*pmd))
			/* pmd exists */
			walk_pte(st, pmd, addr);
	पूर्ण
पूर्ण

अटल व्योम walk_pud(काष्ठा pg_state *st, p4d_t *p4d, अचिन्हित दीर्घ start)
अणु
	pud_t *pud = pud_offset(p4d, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PUD; i++, pud++) अणु
		addr = start + i * PUD_SIZE;
		अगर (!pud_none(*pud))
			/* pud exists */
			walk_pmd(st, pud, addr);
	पूर्ण
पूर्ण

अटल व्योम walk_p4d(काष्ठा pg_state *st, pgd_t *pgd, अचिन्हित दीर्घ start)
अणु
	p4d_t *p4d = p4d_offset(pgd, 0);
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_P4D; i++, p4d++) अणु
		addr = start + i * P4D_SIZE;
		अगर (!p4d_none(*p4d))
			/* p4d exists */
			walk_pud(st, p4d, addr);
	पूर्ण
पूर्ण

अटल व्योम walk_pagetables(काष्ठा pg_state *st)
अणु
	pgd_t *pgd = pgd_offset_k(0UL);
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ addr;

	/*
	 * Traverse the linux pagetable काष्ठाure and dump pages that are in
	 * the hash pagetable.
	 */
	क्रम (i = 0; i < PTRS_PER_PGD; i++, pgd++) अणु
		addr = KERN_VIRT_START + i * PGसूची_SIZE;
		अगर (!pgd_none(*pgd))
			/* pgd exists */
			walk_p4d(st, pgd, addr);
	पूर्ण
पूर्ण


अटल व्योम walk_linearmapping(काष्ठा pg_state *st)
अणु
	अचिन्हित दीर्घ addr;

	/*
	 * Traverse the linear mapping section of भव memory and dump pages
	 * that are in the hash pagetable.
	 */
	अचिन्हित दीर्घ psize = 1 << mmu_psize_defs[mmu_linear_psize].shअगरt;

	क्रम (addr = PAGE_OFFSET; addr < PAGE_OFFSET +
			memblock_end_of_DRAM(); addr += psize)
		hpte_find(st, addr, mmu_linear_psize);
पूर्ण

अटल व्योम walk_vmemmap(काष्ठा pg_state *st)
अणु
	काष्ठा vmemmap_backing *ptr = vmemmap_list;

	अगर (!IS_ENABLED(CONFIG_SPARSEMEM_VMEMMAP))
		वापस;
	/*
	 * Traverse the vmemmaped memory and dump pages that are in the hash
	 * pagetable.
	 */
	जबतक (ptr->list) अणु
		hpte_find(st, ptr->virt_addr, mmu_vmemmap_psize);
		ptr = ptr->list;
	पूर्ण
	seq_माला_दो(st->seq, "---[ vmemmap end ]---\n");
पूर्ण

अटल व्योम populate_markers(व्योम)
अणु
	address_markers[0].start_address = PAGE_OFFSET;
	address_markers[1].start_address = VMALLOC_START;
	address_markers[2].start_address = VMALLOC_END;
	address_markers[3].start_address = ISA_IO_BASE;
	address_markers[4].start_address = ISA_IO_END;
	address_markers[5].start_address = PHB_IO_BASE;
	address_markers[6].start_address = PHB_IO_END;
	address_markers[7].start_address = IOREMAP_BASE;
	address_markers[8].start_address = IOREMAP_END;
	address_markers[9].start_address =  H_VMEMMAP_START;
पूर्ण

अटल पूर्णांक ptdump_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा pg_state st = अणु
		.seq = m,
		.start_address = PAGE_OFFSET,
		.marker = address_markers,
	पूर्ण;
	/*
	 * Traverse the 0xc, 0xd and 0xf areas of the kernel भव memory and
	 * dump pages that are in the hash pagetable.
	 */
	walk_linearmapping(&st);
	walk_pagetables(&st);
	walk_vmemmap(&st);
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

अटल पूर्णांक ptdump_init(व्योम)
अणु
	अगर (!radix_enabled()) अणु
		populate_markers();
		debugfs_create_file("kernel_hash_pagetable", 0400, शून्य, शून्य,
				    &ptdump_fops);
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(ptdump_init);
