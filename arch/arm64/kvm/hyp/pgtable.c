<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Stand-alone page-table allocator क्रम hyp stage-1 and guest stage-2.
 * No bombay mix was harmed in the writing of this file.
 *
 * Copyright (C) 2020 Google LLC
 * Author: Will Deacon <will@kernel.org>
 */

#समावेश <linux/bitfield.h>
#समावेश <यंत्र/kvm_pgtable.h>
#समावेश <यंत्र/stage2_pgtable.h>

#घोषणा KVM_PTE_VALID			BIT(0)

#घोषणा KVM_PTE_TYPE			BIT(1)
#घोषणा KVM_PTE_TYPE_BLOCK		0
#घोषणा KVM_PTE_TYPE_PAGE		1
#घोषणा KVM_PTE_TYPE_TABLE		1

#घोषणा KVM_PTE_ADDR_MASK		GENMASK(47, PAGE_SHIFT)
#घोषणा KVM_PTE_ADDR_51_48		GENMASK(15, 12)

#घोषणा KVM_PTE_LEAF_ATTR_LO		GENMASK(11, 2)

#घोषणा KVM_PTE_LEAF_ATTR_LO_S1_ATTRIDX	GENMASK(4, 2)
#घोषणा KVM_PTE_LEAF_ATTR_LO_S1_AP	GENMASK(7, 6)
#घोषणा KVM_PTE_LEAF_ATTR_LO_S1_AP_RO	3
#घोषणा KVM_PTE_LEAF_ATTR_LO_S1_AP_RW	1
#घोषणा KVM_PTE_LEAF_ATTR_LO_S1_SH	GENMASK(9, 8)
#घोषणा KVM_PTE_LEAF_ATTR_LO_S1_SH_IS	3
#घोषणा KVM_PTE_LEAF_ATTR_LO_S1_AF	BIT(10)

#घोषणा KVM_PTE_LEAF_ATTR_LO_S2_MEMATTR	GENMASK(5, 2)
#घोषणा KVM_PTE_LEAF_ATTR_LO_S2_S2AP_R	BIT(6)
#घोषणा KVM_PTE_LEAF_ATTR_LO_S2_S2AP_W	BIT(7)
#घोषणा KVM_PTE_LEAF_ATTR_LO_S2_SH	GENMASK(9, 8)
#घोषणा KVM_PTE_LEAF_ATTR_LO_S2_SH_IS	3
#घोषणा KVM_PTE_LEAF_ATTR_LO_S2_AF	BIT(10)

#घोषणा KVM_PTE_LEAF_ATTR_HI		GENMASK(63, 51)

#घोषणा KVM_PTE_LEAF_ATTR_HI_S1_XN	BIT(54)

#घोषणा KVM_PTE_LEAF_ATTR_HI_S2_XN	BIT(54)

#घोषणा KVM_PTE_LEAF_ATTR_S2_PERMS	(KVM_PTE_LEAF_ATTR_LO_S2_S2AP_R | \
					 KVM_PTE_LEAF_ATTR_LO_S2_S2AP_W | \
					 KVM_PTE_LEAF_ATTR_HI_S2_XN)

#घोषणा KVM_PTE_LEAF_ATTR_S2_IGNORED	GENMASK(58, 55)

#घोषणा KVM_INVALID_PTE_OWNER_MASK	GENMASK(63, 56)
#घोषणा KVM_MAX_OWNER_ID		1

काष्ठा kvm_pgtable_walk_data अणु
	काष्ठा kvm_pgtable		*pgt;
	काष्ठा kvm_pgtable_walker	*walker;

	u64				addr;
	u64				end;
पूर्ण;

अटल u64 kvm_granule_shअगरt(u32 level)
अणु
	/* Assumes KVM_PGTABLE_MAX_LEVELS is 4 */
	वापस ARM64_HW_PGTABLE_LEVEL_SHIFT(level);
पूर्ण

अटल u64 kvm_granule_size(u32 level)
अणु
	वापस BIT(kvm_granule_shअगरt(level));
पूर्ण

#घोषणा KVM_PHYS_INVALID (-1ULL)

अटल bool kvm_phys_is_valid(u64 phys)
अणु
	वापस phys < BIT(id_aa64mmfr0_parange_to_phys_shअगरt(ID_AA64MMFR0_PARANGE_MAX));
पूर्ण

अटल bool kvm_level_supports_block_mapping(u32 level)
अणु
	/*
	 * Reject invalid block mappings and करोn't bother with 4TB mappings क्रम
	 * 52-bit PAs.
	 */
	वापस !(level == 0 || (PAGE_SIZE != SZ_4K && level == 1));
पूर्ण

अटल bool kvm_block_mapping_supported(u64 addr, u64 end, u64 phys, u32 level)
अणु
	u64 granule = kvm_granule_size(level);

	अगर (!kvm_level_supports_block_mapping(level))
		वापस false;

	अगर (granule > (end - addr))
		वापस false;

	अगर (kvm_phys_is_valid(phys) && !IS_ALIGNED(phys, granule))
		वापस false;

	वापस IS_ALIGNED(addr, granule);
पूर्ण

अटल u32 kvm_pgtable_idx(काष्ठा kvm_pgtable_walk_data *data, u32 level)
अणु
	u64 shअगरt = kvm_granule_shअगरt(level);
	u64 mask = BIT(PAGE_SHIFT - 3) - 1;

	वापस (data->addr >> shअगरt) & mask;
पूर्ण

अटल u32 __kvm_pgd_page_idx(काष्ठा kvm_pgtable *pgt, u64 addr)
अणु
	u64 shअगरt = kvm_granule_shअगरt(pgt->start_level - 1); /* May underflow */
	u64 mask = BIT(pgt->ia_bits) - 1;

	वापस (addr & mask) >> shअगरt;
पूर्ण

अटल u32 kvm_pgd_page_idx(काष्ठा kvm_pgtable_walk_data *data)
अणु
	वापस __kvm_pgd_page_idx(data->pgt, data->addr);
पूर्ण

अटल u32 kvm_pgd_pages(u32 ia_bits, u32 start_level)
अणु
	काष्ठा kvm_pgtable pgt = अणु
		.ia_bits	= ia_bits,
		.start_level	= start_level,
	पूर्ण;

	वापस __kvm_pgd_page_idx(&pgt, -1ULL) + 1;
पूर्ण

अटल bool kvm_pte_valid(kvm_pte_t pte)
अणु
	वापस pte & KVM_PTE_VALID;
पूर्ण

अटल bool kvm_pte_table(kvm_pte_t pte, u32 level)
अणु
	अगर (level == KVM_PGTABLE_MAX_LEVELS - 1)
		वापस false;

	अगर (!kvm_pte_valid(pte))
		वापस false;

	वापस FIELD_GET(KVM_PTE_TYPE, pte) == KVM_PTE_TYPE_TABLE;
पूर्ण

अटल u64 kvm_pte_to_phys(kvm_pte_t pte)
अणु
	u64 pa = pte & KVM_PTE_ADDR_MASK;

	अगर (PAGE_SHIFT == 16)
		pa |= FIELD_GET(KVM_PTE_ADDR_51_48, pte) << 48;

	वापस pa;
पूर्ण

अटल kvm_pte_t kvm_phys_to_pte(u64 pa)
अणु
	kvm_pte_t pte = pa & KVM_PTE_ADDR_MASK;

	अगर (PAGE_SHIFT == 16)
		pte |= FIELD_PREP(KVM_PTE_ADDR_51_48, pa >> 48);

	वापस pte;
पूर्ण

अटल kvm_pte_t *kvm_pte_follow(kvm_pte_t pte, काष्ठा kvm_pgtable_mm_ops *mm_ops)
अणु
	वापस mm_ops->phys_to_virt(kvm_pte_to_phys(pte));
पूर्ण

अटल व्योम kvm_clear_pte(kvm_pte_t *ptep)
अणु
	WRITE_ONCE(*ptep, 0);
पूर्ण

अटल व्योम kvm_set_table_pte(kvm_pte_t *ptep, kvm_pte_t *childp,
			      काष्ठा kvm_pgtable_mm_ops *mm_ops)
अणु
	kvm_pte_t old = *ptep, pte = kvm_phys_to_pte(mm_ops->virt_to_phys(childp));

	pte |= FIELD_PREP(KVM_PTE_TYPE, KVM_PTE_TYPE_TABLE);
	pte |= KVM_PTE_VALID;

	WARN_ON(kvm_pte_valid(old));
	smp_store_release(ptep, pte);
पूर्ण

अटल kvm_pte_t kvm_init_valid_leaf_pte(u64 pa, kvm_pte_t attr, u32 level)
अणु
	kvm_pte_t pte = kvm_phys_to_pte(pa);
	u64 type = (level == KVM_PGTABLE_MAX_LEVELS - 1) ? KVM_PTE_TYPE_PAGE :
							   KVM_PTE_TYPE_BLOCK;

	pte |= attr & (KVM_PTE_LEAF_ATTR_LO | KVM_PTE_LEAF_ATTR_HI);
	pte |= FIELD_PREP(KVM_PTE_TYPE, type);
	pte |= KVM_PTE_VALID;

	वापस pte;
पूर्ण

अटल kvm_pte_t kvm_init_invalid_leaf_owner(u8 owner_id)
अणु
	वापस FIELD_PREP(KVM_INVALID_PTE_OWNER_MASK, owner_id);
पूर्ण

अटल पूर्णांक kvm_pgtable_visitor_cb(काष्ठा kvm_pgtable_walk_data *data, u64 addr,
				  u32 level, kvm_pte_t *ptep,
				  क्रमागत kvm_pgtable_walk_flags flag)
अणु
	काष्ठा kvm_pgtable_walker *walker = data->walker;
	वापस walker->cb(addr, data->end, level, ptep, flag, walker->arg);
पूर्ण

अटल पूर्णांक __kvm_pgtable_walk(काष्ठा kvm_pgtable_walk_data *data,
			      kvm_pte_t *pgtable, u32 level);

अटल अंतरभूत पूर्णांक __kvm_pgtable_visit(काष्ठा kvm_pgtable_walk_data *data,
				      kvm_pte_t *ptep, u32 level)
अणु
	पूर्णांक ret = 0;
	u64 addr = data->addr;
	kvm_pte_t *childp, pte = *ptep;
	bool table = kvm_pte_table(pte, level);
	क्रमागत kvm_pgtable_walk_flags flags = data->walker->flags;

	अगर (table && (flags & KVM_PGTABLE_WALK_TABLE_PRE)) अणु
		ret = kvm_pgtable_visitor_cb(data, addr, level, ptep,
					     KVM_PGTABLE_WALK_TABLE_PRE);
	पूर्ण

	अगर (!table && (flags & KVM_PGTABLE_WALK_LEAF)) अणु
		ret = kvm_pgtable_visitor_cb(data, addr, level, ptep,
					     KVM_PGTABLE_WALK_LEAF);
		pte = *ptep;
		table = kvm_pte_table(pte, level);
	पूर्ण

	अगर (ret)
		जाओ out;

	अगर (!table) अणु
		data->addr = ALIGN_DOWN(data->addr, kvm_granule_size(level));
		data->addr += kvm_granule_size(level);
		जाओ out;
	पूर्ण

	childp = kvm_pte_follow(pte, data->pgt->mm_ops);
	ret = __kvm_pgtable_walk(data, childp, level + 1);
	अगर (ret)
		जाओ out;

	अगर (flags & KVM_PGTABLE_WALK_TABLE_POST) अणु
		ret = kvm_pgtable_visitor_cb(data, addr, level, ptep,
					     KVM_PGTABLE_WALK_TABLE_POST);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक __kvm_pgtable_walk(काष्ठा kvm_pgtable_walk_data *data,
			      kvm_pte_t *pgtable, u32 level)
अणु
	u32 idx;
	पूर्णांक ret = 0;

	अगर (WARN_ON_ONCE(level >= KVM_PGTABLE_MAX_LEVELS))
		वापस -EINVAL;

	क्रम (idx = kvm_pgtable_idx(data, level); idx < PTRS_PER_PTE; ++idx) अणु
		kvm_pte_t *ptep = &pgtable[idx];

		अगर (data->addr >= data->end)
			अवरोध;

		ret = __kvm_pgtable_visit(data, ptep, level);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _kvm_pgtable_walk(काष्ठा kvm_pgtable_walk_data *data)
अणु
	u32 idx;
	पूर्णांक ret = 0;
	काष्ठा kvm_pgtable *pgt = data->pgt;
	u64 limit = BIT(pgt->ia_bits);

	अगर (data->addr > limit || data->end > limit)
		वापस -दुस्फल;

	अगर (!pgt->pgd)
		वापस -EINVAL;

	क्रम (idx = kvm_pgd_page_idx(data); data->addr < data->end; ++idx) अणु
		kvm_pte_t *ptep = &pgt->pgd[idx * PTRS_PER_PTE];

		ret = __kvm_pgtable_walk(data, ptep, pgt->start_level);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक kvm_pgtable_walk(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size,
		     काष्ठा kvm_pgtable_walker *walker)
अणु
	काष्ठा kvm_pgtable_walk_data walk_data = अणु
		.pgt	= pgt,
		.addr	= ALIGN_DOWN(addr, PAGE_SIZE),
		.end	= PAGE_ALIGN(walk_data.addr + size),
		.walker	= walker,
	पूर्ण;

	वापस _kvm_pgtable_walk(&walk_data);
पूर्ण

काष्ठा hyp_map_data अणु
	u64				phys;
	kvm_pte_t			attr;
	काष्ठा kvm_pgtable_mm_ops	*mm_ops;
पूर्ण;

अटल पूर्णांक hyp_set_prot_attr(क्रमागत kvm_pgtable_prot prot, kvm_pte_t *ptep)
अणु
	bool device = prot & KVM_PGTABLE_PROT_DEVICE;
	u32 mtype = device ? MT_DEVICE_nGnRE : MT_NORMAL;
	kvm_pte_t attr = FIELD_PREP(KVM_PTE_LEAF_ATTR_LO_S1_ATTRIDX, mtype);
	u32 sh = KVM_PTE_LEAF_ATTR_LO_S1_SH_IS;
	u32 ap = (prot & KVM_PGTABLE_PROT_W) ? KVM_PTE_LEAF_ATTR_LO_S1_AP_RW :
					       KVM_PTE_LEAF_ATTR_LO_S1_AP_RO;

	अगर (!(prot & KVM_PGTABLE_PROT_R))
		वापस -EINVAL;

	अगर (prot & KVM_PGTABLE_PROT_X) अणु
		अगर (prot & KVM_PGTABLE_PROT_W)
			वापस -EINVAL;

		अगर (device)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		attr |= KVM_PTE_LEAF_ATTR_HI_S1_XN;
	पूर्ण

	attr |= FIELD_PREP(KVM_PTE_LEAF_ATTR_LO_S1_AP, ap);
	attr |= FIELD_PREP(KVM_PTE_LEAF_ATTR_LO_S1_SH, sh);
	attr |= KVM_PTE_LEAF_ATTR_LO_S1_AF;
	*ptep = attr;

	वापस 0;
पूर्ण

अटल bool hyp_map_walker_try_leaf(u64 addr, u64 end, u32 level,
				    kvm_pte_t *ptep, काष्ठा hyp_map_data *data)
अणु
	kvm_pte_t new, old = *ptep;
	u64 granule = kvm_granule_size(level), phys = data->phys;

	अगर (!kvm_block_mapping_supported(addr, end, phys, level))
		वापस false;

	/* Tolerate KVM recreating the exact same mapping */
	new = kvm_init_valid_leaf_pte(phys, data->attr, level);
	अगर (old != new && !WARN_ON(kvm_pte_valid(old)))
		smp_store_release(ptep, new);

	data->phys += granule;
	वापस true;
पूर्ण

अटल पूर्णांक hyp_map_walker(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
			  क्रमागत kvm_pgtable_walk_flags flag, व्योम * स्थिर arg)
अणु
	kvm_pte_t *childp;
	काष्ठा hyp_map_data *data = arg;
	काष्ठा kvm_pgtable_mm_ops *mm_ops = data->mm_ops;

	अगर (hyp_map_walker_try_leaf(addr, end, level, ptep, arg))
		वापस 0;

	अगर (WARN_ON(level == KVM_PGTABLE_MAX_LEVELS - 1))
		वापस -EINVAL;

	childp = (kvm_pte_t *)mm_ops->zalloc_page(शून्य);
	अगर (!childp)
		वापस -ENOMEM;

	kvm_set_table_pte(ptep, childp, mm_ops);
	वापस 0;
पूर्ण

पूर्णांक kvm_pgtable_hyp_map(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size, u64 phys,
			क्रमागत kvm_pgtable_prot prot)
अणु
	पूर्णांक ret;
	काष्ठा hyp_map_data map_data = अणु
		.phys	= ALIGN_DOWN(phys, PAGE_SIZE),
		.mm_ops	= pgt->mm_ops,
	पूर्ण;
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb	= hyp_map_walker,
		.flags	= KVM_PGTABLE_WALK_LEAF,
		.arg	= &map_data,
	पूर्ण;

	ret = hyp_set_prot_attr(prot, &map_data.attr);
	अगर (ret)
		वापस ret;

	ret = kvm_pgtable_walk(pgt, addr, size, &walker);
	dsb(ishst);
	isb();
	वापस ret;
पूर्ण

पूर्णांक kvm_pgtable_hyp_init(काष्ठा kvm_pgtable *pgt, u32 va_bits,
			 काष्ठा kvm_pgtable_mm_ops *mm_ops)
अणु
	u64 levels = ARM64_HW_PGTABLE_LEVELS(va_bits);

	pgt->pgd = (kvm_pte_t *)mm_ops->zalloc_page(शून्य);
	अगर (!pgt->pgd)
		वापस -ENOMEM;

	pgt->ia_bits		= va_bits;
	pgt->start_level	= KVM_PGTABLE_MAX_LEVELS - levels;
	pgt->mm_ops		= mm_ops;
	pgt->mmu		= शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक hyp_मुक्त_walker(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
			   क्रमागत kvm_pgtable_walk_flags flag, व्योम * स्थिर arg)
अणु
	काष्ठा kvm_pgtable_mm_ops *mm_ops = arg;

	mm_ops->put_page((व्योम *)kvm_pte_follow(*ptep, mm_ops));
	वापस 0;
पूर्ण

व्योम kvm_pgtable_hyp_destroy(काष्ठा kvm_pgtable *pgt)
अणु
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb	= hyp_मुक्त_walker,
		.flags	= KVM_PGTABLE_WALK_TABLE_POST,
		.arg	= pgt->mm_ops,
	पूर्ण;

	WARN_ON(kvm_pgtable_walk(pgt, 0, BIT(pgt->ia_bits), &walker));
	pgt->mm_ops->put_page(pgt->pgd);
	pgt->pgd = शून्य;
पूर्ण

काष्ठा stage2_map_data अणु
	u64				phys;
	kvm_pte_t			attr;
	u8				owner_id;

	kvm_pte_t			*anchor;
	kvm_pte_t			*childp;

	काष्ठा kvm_s2_mmu		*mmu;
	व्योम				*memcache;

	काष्ठा kvm_pgtable_mm_ops	*mm_ops;
पूर्ण;

u64 kvm_get_vtcr(u64 mmfr0, u64 mmfr1, u32 phys_shअगरt)
अणु
	u64 vtcr = VTCR_EL2_FLAGS;
	u8 lvls;

	vtcr |= kvm_get_parange(mmfr0) << VTCR_EL2_PS_SHIFT;
	vtcr |= VTCR_EL2_T0SZ(phys_shअगरt);
	/*
	 * Use a minimum 2 level page table to prevent splitting
	 * host PMD huge pages at stage2.
	 */
	lvls = stage2_pgtable_levels(phys_shअगरt);
	अगर (lvls < 2)
		lvls = 2;
	vtcr |= VTCR_EL2_LVLS_TO_SL0(lvls);

	/*
	 * Enable the Hardware Access Flag management, unconditionally
	 * on all CPUs. The features is RES0 on CPUs without the support
	 * and must be ignored by the CPUs.
	 */
	vtcr |= VTCR_EL2_HA;

	/* Set the vmid bits */
	vtcr |= (get_vmid_bits(mmfr1) == 16) ?
		VTCR_EL2_VS_16BIT :
		VTCR_EL2_VS_8BIT;

	वापस vtcr;
पूर्ण

अटल bool stage2_has_fwb(काष्ठा kvm_pgtable *pgt)
अणु
	अगर (!cpus_have_स्थिर_cap(ARM64_HAS_STAGE2_FWB))
		वापस false;

	वापस !(pgt->flags & KVM_PGTABLE_S2_NOFWB);
पूर्ण

#घोषणा KVM_S2_MEMATTR(pgt, attr) PAGE_S2_MEMATTR(attr, stage2_has_fwb(pgt))

अटल पूर्णांक stage2_set_prot_attr(काष्ठा kvm_pgtable *pgt, क्रमागत kvm_pgtable_prot prot,
				kvm_pte_t *ptep)
अणु
	bool device = prot & KVM_PGTABLE_PROT_DEVICE;
	kvm_pte_t attr = device ? KVM_S2_MEMATTR(pgt, DEVICE_nGnRE) :
			    KVM_S2_MEMATTR(pgt, NORMAL);
	u32 sh = KVM_PTE_LEAF_ATTR_LO_S2_SH_IS;

	अगर (!(prot & KVM_PGTABLE_PROT_X))
		attr |= KVM_PTE_LEAF_ATTR_HI_S2_XN;
	अन्यथा अगर (device)
		वापस -EINVAL;

	अगर (prot & KVM_PGTABLE_PROT_R)
		attr |= KVM_PTE_LEAF_ATTR_LO_S2_S2AP_R;

	अगर (prot & KVM_PGTABLE_PROT_W)
		attr |= KVM_PTE_LEAF_ATTR_LO_S2_S2AP_W;

	attr |= FIELD_PREP(KVM_PTE_LEAF_ATTR_LO_S2_SH, sh);
	attr |= KVM_PTE_LEAF_ATTR_LO_S2_AF;
	*ptep = attr;

	वापस 0;
पूर्ण

अटल bool stage2_pte_needs_update(kvm_pte_t old, kvm_pte_t new)
अणु
	अगर (!kvm_pte_valid(old) || !kvm_pte_valid(new))
		वापस true;

	वापस ((old ^ new) & (~KVM_PTE_LEAF_ATTR_S2_PERMS));
पूर्ण

अटल bool stage2_pte_is_counted(kvm_pte_t pte)
अणु
	/*
	 * The refcount tracks valid entries as well as invalid entries अगर they
	 * encode ownership of a page to another entity than the page-table
	 * owner, whose id is 0.
	 */
	वापस !!pte;
पूर्ण

अटल व्योम stage2_put_pte(kvm_pte_t *ptep, काष्ठा kvm_s2_mmu *mmu, u64 addr,
			   u32 level, काष्ठा kvm_pgtable_mm_ops *mm_ops)
अणु
	/*
	 * Clear the existing PTE, and perक्रमm अवरोध-beक्रमe-make with
	 * TLB मुख्यtenance अगर it was valid.
	 */
	अगर (kvm_pte_valid(*ptep)) अणु
		kvm_clear_pte(ptep);
		kvm_call_hyp(__kvm_tlb_flush_vmid_ipa, mmu, addr, level);
	पूर्ण

	mm_ops->put_page(ptep);
पूर्ण

अटल पूर्णांक stage2_map_walker_try_leaf(u64 addr, u64 end, u32 level,
				      kvm_pte_t *ptep,
				      काष्ठा stage2_map_data *data)
अणु
	kvm_pte_t new, old = *ptep;
	u64 granule = kvm_granule_size(level), phys = data->phys;
	काष्ठा kvm_pgtable_mm_ops *mm_ops = data->mm_ops;

	अगर (!kvm_block_mapping_supported(addr, end, phys, level))
		वापस -E2BIG;

	अगर (kvm_phys_is_valid(phys))
		new = kvm_init_valid_leaf_pte(phys, data->attr, level);
	अन्यथा
		new = kvm_init_invalid_leaf_owner(data->owner_id);

	अगर (stage2_pte_is_counted(old)) अणु
		/*
		 * Skip updating the PTE अगर we are trying to recreate the exact
		 * same mapping or only change the access permissions. Instead,
		 * the vCPU will निकास one more समय from guest अगर still needed
		 * and then go through the path of relaxing permissions.
		 */
		अगर (!stage2_pte_needs_update(old, new))
			वापस -EAGAIN;

		stage2_put_pte(ptep, data->mmu, addr, level, mm_ops);
	पूर्ण

	smp_store_release(ptep, new);
	अगर (stage2_pte_is_counted(new))
		mm_ops->get_page(ptep);
	अगर (kvm_phys_is_valid(phys))
		data->phys += granule;
	वापस 0;
पूर्ण

अटल पूर्णांक stage2_map_walk_table_pre(u64 addr, u64 end, u32 level,
				     kvm_pte_t *ptep,
				     काष्ठा stage2_map_data *data)
अणु
	अगर (data->anchor)
		वापस 0;

	अगर (!kvm_block_mapping_supported(addr, end, data->phys, level))
		वापस 0;

	data->childp = kvm_pte_follow(*ptep, data->mm_ops);
	kvm_clear_pte(ptep);

	/*
	 * Invalidate the whole stage-2, as we may have numerous leaf
	 * entries below us which would otherwise need invalidating
	 * inभागidually.
	 */
	kvm_call_hyp(__kvm_tlb_flush_vmid, data->mmu);
	data->anchor = ptep;
	वापस 0;
पूर्ण

अटल पूर्णांक stage2_map_walk_leaf(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
				काष्ठा stage2_map_data *data)
अणु
	काष्ठा kvm_pgtable_mm_ops *mm_ops = data->mm_ops;
	kvm_pte_t *childp, pte = *ptep;
	पूर्णांक ret;

	अगर (data->anchor) अणु
		अगर (stage2_pte_is_counted(pte))
			mm_ops->put_page(ptep);

		वापस 0;
	पूर्ण

	ret = stage2_map_walker_try_leaf(addr, end, level, ptep, data);
	अगर (ret != -E2BIG)
		वापस ret;

	अगर (WARN_ON(level == KVM_PGTABLE_MAX_LEVELS - 1))
		वापस -EINVAL;

	अगर (!data->memcache)
		वापस -ENOMEM;

	childp = mm_ops->zalloc_page(data->memcache);
	अगर (!childp)
		वापस -ENOMEM;

	/*
	 * If we've run पूर्णांकo an existing block mapping then replace it with
	 * a table. Accesses beyond 'end' that fall within the new table
	 * will be mapped lazily.
	 */
	अगर (stage2_pte_is_counted(pte))
		stage2_put_pte(ptep, data->mmu, addr, level, mm_ops);

	kvm_set_table_pte(ptep, childp, mm_ops);
	mm_ops->get_page(ptep);

	वापस 0;
पूर्ण

अटल पूर्णांक stage2_map_walk_table_post(u64 addr, u64 end, u32 level,
				      kvm_pte_t *ptep,
				      काष्ठा stage2_map_data *data)
अणु
	काष्ठा kvm_pgtable_mm_ops *mm_ops = data->mm_ops;
	kvm_pte_t *childp;
	पूर्णांक ret = 0;

	अगर (!data->anchor)
		वापस 0;

	अगर (data->anchor == ptep) अणु
		childp = data->childp;
		data->anchor = शून्य;
		data->childp = शून्य;
		ret = stage2_map_walk_leaf(addr, end, level, ptep, data);
	पूर्ण अन्यथा अणु
		childp = kvm_pte_follow(*ptep, mm_ops);
	पूर्ण

	mm_ops->put_page(childp);
	mm_ops->put_page(ptep);

	वापस ret;
पूर्ण

/*
 * This is a little fiddly, as we use all three of the walk flags. The idea
 * is that the TABLE_PRE callback runs क्रम table entries on the way करोwn,
 * looking क्रम table entries which we could conceivably replace with a
 * block entry क्रम this mapping. If it finds one, then it sets the 'anchor'
 * field in 'struct stage2_map_data' to poपूर्णांक at the table entry, beक्रमe
 * clearing the entry to zero and descending पूर्णांकo the now detached table.
 *
 * The behaviour of the LEAF callback then depends on whether or not the
 * anchor has been set. If not, then we're not using a block mapping higher
 * up the table and we perक्रमm the mapping at the existing leaves instead.
 * If, on the other hand, the anchor _is_ set, then we drop references to
 * all valid leaves so that the pages beneath the anchor can be मुक्तd.
 *
 * Finally, the TABLE_POST callback करोes nothing अगर the anchor has not
 * been set, but otherwise मुक्तs the page-table pages जबतक walking back up
 * the page-table, installing the block entry when it revisits the anchor
 * poपूर्णांकer and clearing the anchor to शून्य.
 */
अटल पूर्णांक stage2_map_walker(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
			     क्रमागत kvm_pgtable_walk_flags flag, व्योम * स्थिर arg)
अणु
	काष्ठा stage2_map_data *data = arg;

	चयन (flag) अणु
	हाल KVM_PGTABLE_WALK_TABLE_PRE:
		वापस stage2_map_walk_table_pre(addr, end, level, ptep, data);
	हाल KVM_PGTABLE_WALK_LEAF:
		वापस stage2_map_walk_leaf(addr, end, level, ptep, data);
	हाल KVM_PGTABLE_WALK_TABLE_POST:
		वापस stage2_map_walk_table_post(addr, end, level, ptep, data);
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_pgtable_stage2_map(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size,
			   u64 phys, क्रमागत kvm_pgtable_prot prot,
			   व्योम *mc)
अणु
	पूर्णांक ret;
	काष्ठा stage2_map_data map_data = अणु
		.phys		= ALIGN_DOWN(phys, PAGE_SIZE),
		.mmu		= pgt->mmu,
		.memcache	= mc,
		.mm_ops		= pgt->mm_ops,
	पूर्ण;
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb		= stage2_map_walker,
		.flags		= KVM_PGTABLE_WALK_TABLE_PRE |
				  KVM_PGTABLE_WALK_LEAF |
				  KVM_PGTABLE_WALK_TABLE_POST,
		.arg		= &map_data,
	पूर्ण;

	अगर (WARN_ON((pgt->flags & KVM_PGTABLE_S2_IDMAP) && (addr != phys)))
		वापस -EINVAL;

	ret = stage2_set_prot_attr(pgt, prot, &map_data.attr);
	अगर (ret)
		वापस ret;

	ret = kvm_pgtable_walk(pgt, addr, size, &walker);
	dsb(ishst);
	वापस ret;
पूर्ण

पूर्णांक kvm_pgtable_stage2_set_owner(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size,
				 व्योम *mc, u8 owner_id)
अणु
	पूर्णांक ret;
	काष्ठा stage2_map_data map_data = अणु
		.phys		= KVM_PHYS_INVALID,
		.mmu		= pgt->mmu,
		.memcache	= mc,
		.mm_ops		= pgt->mm_ops,
		.owner_id	= owner_id,
	पूर्ण;
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb		= stage2_map_walker,
		.flags		= KVM_PGTABLE_WALK_TABLE_PRE |
				  KVM_PGTABLE_WALK_LEAF |
				  KVM_PGTABLE_WALK_TABLE_POST,
		.arg		= &map_data,
	पूर्ण;

	अगर (owner_id > KVM_MAX_OWNER_ID)
		वापस -EINVAL;

	ret = kvm_pgtable_walk(pgt, addr, size, &walker);
	वापस ret;
पूर्ण

अटल bool stage2_pte_cacheable(काष्ठा kvm_pgtable *pgt, kvm_pte_t pte)
अणु
	u64 memattr = pte & KVM_PTE_LEAF_ATTR_LO_S2_MEMATTR;
	वापस memattr == KVM_S2_MEMATTR(pgt, NORMAL);
पूर्ण

अटल पूर्णांक stage2_unmap_walker(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
			       क्रमागत kvm_pgtable_walk_flags flag,
			       व्योम * स्थिर arg)
अणु
	काष्ठा kvm_pgtable *pgt = arg;
	काष्ठा kvm_s2_mmu *mmu = pgt->mmu;
	काष्ठा kvm_pgtable_mm_ops *mm_ops = pgt->mm_ops;
	kvm_pte_t pte = *ptep, *childp = शून्य;
	bool need_flush = false;

	अगर (!kvm_pte_valid(pte)) अणु
		अगर (stage2_pte_is_counted(pte)) अणु
			kvm_clear_pte(ptep);
			mm_ops->put_page(ptep);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (kvm_pte_table(pte, level)) अणु
		childp = kvm_pte_follow(pte, mm_ops);

		अगर (mm_ops->page_count(childp) != 1)
			वापस 0;
	पूर्ण अन्यथा अगर (stage2_pte_cacheable(pgt, pte)) अणु
		need_flush = !stage2_has_fwb(pgt);
	पूर्ण

	/*
	 * This is similar to the map() path in that we unmap the entire
	 * block entry and rely on the reमुख्यing portions being faulted
	 * back lazily.
	 */
	stage2_put_pte(ptep, mmu, addr, level, mm_ops);

	अगर (need_flush) अणु
		__flush_dcache_area(kvm_pte_follow(pte, mm_ops),
				    kvm_granule_size(level));
	पूर्ण

	अगर (childp)
		mm_ops->put_page(childp);

	वापस 0;
पूर्ण

पूर्णांक kvm_pgtable_stage2_unmap(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size)
अणु
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb	= stage2_unmap_walker,
		.arg	= pgt,
		.flags	= KVM_PGTABLE_WALK_LEAF | KVM_PGTABLE_WALK_TABLE_POST,
	पूर्ण;

	वापस kvm_pgtable_walk(pgt, addr, size, &walker);
पूर्ण

काष्ठा stage2_attr_data अणु
	kvm_pte_t	attr_set;
	kvm_pte_t	attr_clr;
	kvm_pte_t	pte;
	u32		level;
पूर्ण;

अटल पूर्णांक stage2_attr_walker(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
			      क्रमागत kvm_pgtable_walk_flags flag,
			      व्योम * स्थिर arg)
अणु
	kvm_pte_t pte = *ptep;
	काष्ठा stage2_attr_data *data = arg;

	अगर (!kvm_pte_valid(pte))
		वापस 0;

	data->level = level;
	data->pte = pte;
	pte &= ~data->attr_clr;
	pte |= data->attr_set;

	/*
	 * We may race with the CPU trying to set the access flag here,
	 * but worst-हाल the access flag update माला_लो lost and will be
	 * set on the next access instead.
	 */
	अगर (data->pte != pte)
		WRITE_ONCE(*ptep, pte);

	वापस 0;
पूर्ण

अटल पूर्णांक stage2_update_leaf_attrs(काष्ठा kvm_pgtable *pgt, u64 addr,
				    u64 size, kvm_pte_t attr_set,
				    kvm_pte_t attr_clr, kvm_pte_t *orig_pte,
				    u32 *level)
अणु
	पूर्णांक ret;
	kvm_pte_t attr_mask = KVM_PTE_LEAF_ATTR_LO | KVM_PTE_LEAF_ATTR_HI;
	काष्ठा stage2_attr_data data = अणु
		.attr_set	= attr_set & attr_mask,
		.attr_clr	= attr_clr & attr_mask,
	पूर्ण;
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb		= stage2_attr_walker,
		.arg		= &data,
		.flags		= KVM_PGTABLE_WALK_LEAF,
	पूर्ण;

	ret = kvm_pgtable_walk(pgt, addr, size, &walker);
	अगर (ret)
		वापस ret;

	अगर (orig_pte)
		*orig_pte = data.pte;

	अगर (level)
		*level = data.level;
	वापस 0;
पूर्ण

पूर्णांक kvm_pgtable_stage2_wrprotect(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size)
अणु
	वापस stage2_update_leaf_attrs(pgt, addr, size, 0,
					KVM_PTE_LEAF_ATTR_LO_S2_S2AP_W,
					शून्य, शून्य);
पूर्ण

kvm_pte_t kvm_pgtable_stage2_mkyoung(काष्ठा kvm_pgtable *pgt, u64 addr)
अणु
	kvm_pte_t pte = 0;
	stage2_update_leaf_attrs(pgt, addr, 1, KVM_PTE_LEAF_ATTR_LO_S2_AF, 0,
				 &pte, शून्य);
	dsb(ishst);
	वापस pte;
पूर्ण

kvm_pte_t kvm_pgtable_stage2_mkold(काष्ठा kvm_pgtable *pgt, u64 addr)
अणु
	kvm_pte_t pte = 0;
	stage2_update_leaf_attrs(pgt, addr, 1, 0, KVM_PTE_LEAF_ATTR_LO_S2_AF,
				 &pte, शून्य);
	/*
	 * "But where's the TLBI?!", you scream.
	 * "Over in the core code", I sigh.
	 *
	 * See the '->clear_flush_young()' callback on the KVM mmu notअगरier.
	 */
	वापस pte;
पूर्ण

bool kvm_pgtable_stage2_is_young(काष्ठा kvm_pgtable *pgt, u64 addr)
अणु
	kvm_pte_t pte = 0;
	stage2_update_leaf_attrs(pgt, addr, 1, 0, 0, &pte, शून्य);
	वापस pte & KVM_PTE_LEAF_ATTR_LO_S2_AF;
पूर्ण

पूर्णांक kvm_pgtable_stage2_relax_perms(काष्ठा kvm_pgtable *pgt, u64 addr,
				   क्रमागत kvm_pgtable_prot prot)
अणु
	पूर्णांक ret;
	u32 level;
	kvm_pte_t set = 0, clr = 0;

	अगर (prot & KVM_PGTABLE_PROT_R)
		set |= KVM_PTE_LEAF_ATTR_LO_S2_S2AP_R;

	अगर (prot & KVM_PGTABLE_PROT_W)
		set |= KVM_PTE_LEAF_ATTR_LO_S2_S2AP_W;

	अगर (prot & KVM_PGTABLE_PROT_X)
		clr |= KVM_PTE_LEAF_ATTR_HI_S2_XN;

	ret = stage2_update_leaf_attrs(pgt, addr, 1, set, clr, शून्य, &level);
	अगर (!ret)
		kvm_call_hyp(__kvm_tlb_flush_vmid_ipa, pgt->mmu, addr, level);
	वापस ret;
पूर्ण

अटल पूर्णांक stage2_flush_walker(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
			       क्रमागत kvm_pgtable_walk_flags flag,
			       व्योम * स्थिर arg)
अणु
	काष्ठा kvm_pgtable *pgt = arg;
	काष्ठा kvm_pgtable_mm_ops *mm_ops = pgt->mm_ops;
	kvm_pte_t pte = *ptep;

	अगर (!kvm_pte_valid(pte) || !stage2_pte_cacheable(pgt, pte))
		वापस 0;

	__flush_dcache_area(kvm_pte_follow(pte, mm_ops), kvm_granule_size(level));
	वापस 0;
पूर्ण

पूर्णांक kvm_pgtable_stage2_flush(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size)
अणु
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb	= stage2_flush_walker,
		.flags	= KVM_PGTABLE_WALK_LEAF,
		.arg	= pgt,
	पूर्ण;

	अगर (stage2_has_fwb(pgt))
		वापस 0;

	वापस kvm_pgtable_walk(pgt, addr, size, &walker);
पूर्ण

पूर्णांक kvm_pgtable_stage2_init_flags(काष्ठा kvm_pgtable *pgt, काष्ठा kvm_arch *arch,
				  काष्ठा kvm_pgtable_mm_ops *mm_ops,
				  क्रमागत kvm_pgtable_stage2_flags flags)
अणु
	माप_प्रकार pgd_sz;
	u64 vtcr = arch->vtcr;
	u32 ia_bits = VTCR_EL2_IPA(vtcr);
	u32 sl0 = FIELD_GET(VTCR_EL2_SL0_MASK, vtcr);
	u32 start_level = VTCR_EL2_TGRAN_SL0_BASE - sl0;

	pgd_sz = kvm_pgd_pages(ia_bits, start_level) * PAGE_SIZE;
	pgt->pgd = mm_ops->zalloc_pages_exact(pgd_sz);
	अगर (!pgt->pgd)
		वापस -ENOMEM;

	pgt->ia_bits		= ia_bits;
	pgt->start_level	= start_level;
	pgt->mm_ops		= mm_ops;
	pgt->mmu		= &arch->mmu;
	pgt->flags		= flags;

	/* Ensure zeroed PGD pages are visible to the hardware walker */
	dsb(ishst);
	वापस 0;
पूर्ण

अटल पूर्णांक stage2_मुक्त_walker(u64 addr, u64 end, u32 level, kvm_pte_t *ptep,
			      क्रमागत kvm_pgtable_walk_flags flag,
			      व्योम * स्थिर arg)
अणु
	काष्ठा kvm_pgtable_mm_ops *mm_ops = arg;
	kvm_pte_t pte = *ptep;

	अगर (!stage2_pte_is_counted(pte))
		वापस 0;

	mm_ops->put_page(ptep);

	अगर (kvm_pte_table(pte, level))
		mm_ops->put_page(kvm_pte_follow(pte, mm_ops));

	वापस 0;
पूर्ण

व्योम kvm_pgtable_stage2_destroy(काष्ठा kvm_pgtable *pgt)
अणु
	माप_प्रकार pgd_sz;
	काष्ठा kvm_pgtable_walker walker = अणु
		.cb	= stage2_मुक्त_walker,
		.flags	= KVM_PGTABLE_WALK_LEAF |
			  KVM_PGTABLE_WALK_TABLE_POST,
		.arg	= pgt->mm_ops,
	पूर्ण;

	WARN_ON(kvm_pgtable_walk(pgt, 0, BIT(pgt->ia_bits), &walker));
	pgd_sz = kvm_pgd_pages(pgt->ia_bits, pgt->start_level) * PAGE_SIZE;
	pgt->mm_ops->मुक्त_pages_exact(pgt->pgd, pgd_sz);
	pgt->pgd = शून्य;
पूर्ण

#घोषणा KVM_PTE_LEAF_S2_COMPAT_MASK	(KVM_PTE_LEAF_ATTR_S2_PERMS | \
					 KVM_PTE_LEAF_ATTR_LO_S2_MEMATTR | \
					 KVM_PTE_LEAF_ATTR_S2_IGNORED)

अटल पूर्णांक stage2_check_permission_walker(u64 addr, u64 end, u32 level,
					  kvm_pte_t *ptep,
					  क्रमागत kvm_pgtable_walk_flags flag,
					  व्योम * स्थिर arg)
अणु
	kvm_pte_t old_attr, pte = *ptep, *new_attr = arg;

	/*
	 * Compatible mappings are either invalid and owned by the page-table
	 * owner (whose id is 0), or valid with matching permission attributes.
	 */
	अगर (kvm_pte_valid(pte)) अणु
		old_attr = pte & KVM_PTE_LEAF_S2_COMPAT_MASK;
		अगर (old_attr != *new_attr)
			वापस -EEXIST;
	पूर्ण अन्यथा अगर (pte) अणु
		वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kvm_pgtable_stage2_find_range(काष्ठा kvm_pgtable *pgt, u64 addr,
				  क्रमागत kvm_pgtable_prot prot,
				  काष्ठा kvm_mem_range *range)
अणु
	kvm_pte_t attr;
	काष्ठा kvm_pgtable_walker check_perm_walker = अणु
		.cb		= stage2_check_permission_walker,
		.flags		= KVM_PGTABLE_WALK_LEAF,
		.arg		= &attr,
	पूर्ण;
	u64 granule, start, end;
	u32 level;
	पूर्णांक ret;

	ret = stage2_set_prot_attr(pgt, prot, &attr);
	अगर (ret)
		वापस ret;
	attr &= KVM_PTE_LEAF_S2_COMPAT_MASK;

	क्रम (level = pgt->start_level; level < KVM_PGTABLE_MAX_LEVELS; level++) अणु
		granule = kvm_granule_size(level);
		start = ALIGN_DOWN(addr, granule);
		end = start + granule;

		अगर (!kvm_level_supports_block_mapping(level))
			जारी;

		अगर (start < range->start || range->end < end)
			जारी;

		/*
		 * Check the presence of existing mappings with incompatible
		 * permissions within the current block range, and try one level
		 * deeper अगर one is found.
		 */
		ret = kvm_pgtable_walk(pgt, start, granule, &check_perm_walker);
		अगर (ret != -EEXIST)
			अवरोध;
	पूर्ण

	अगर (!ret) अणु
		range->start = start;
		range->end = end;
	पूर्ण

	वापस ret;
पूर्ण
