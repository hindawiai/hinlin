<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vMTRR implementation
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 * Copyright(C) 2015 Intel Corporation.
 *
 * Authors:
 *   Yaniv Kamay  <yaniv@qumranet.com>
 *   Avi Kivity   <avi@qumranet.com>
 *   Marcelo Tosatti <mtosatti@redhat.com>
 *   Paolo Bonzini <pbonzini@redhat.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/mtrr.h>

#समावेश "cpuid.h"
#समावेश "mmu.h"

#घोषणा IA32_MTRR_DEF_TYPE_E		(1ULL << 11)
#घोषणा IA32_MTRR_DEF_TYPE_FE		(1ULL << 10)
#घोषणा IA32_MTRR_DEF_TYPE_TYPE_MASK	(0xff)

अटल bool msr_mtrr_valid(अचिन्हित msr)
अणु
	चयन (msr) अणु
	हाल 0x200 ... 0x200 + 2 * KVM_NR_VAR_MTRR - 1:
	हाल MSR_MTRRfix64K_00000:
	हाल MSR_MTRRfix16K_80000:
	हाल MSR_MTRRfix16K_A0000:
	हाल MSR_MTRRfix4K_C0000:
	हाल MSR_MTRRfix4K_C8000:
	हाल MSR_MTRRfix4K_D0000:
	हाल MSR_MTRRfix4K_D8000:
	हाल MSR_MTRRfix4K_E0000:
	हाल MSR_MTRRfix4K_E8000:
	हाल MSR_MTRRfix4K_F0000:
	हाल MSR_MTRRfix4K_F8000:
	हाल MSR_MTRRdefType:
	हाल MSR_IA32_CR_PAT:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool valid_mtrr_type(अचिन्हित t)
अणु
	वापस t < 8 && (1 << t) & 0x73; /* 0, 1, 4, 5, 6 */
पूर्ण

bool kvm_mtrr_valid(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data)
अणु
	पूर्णांक i;
	u64 mask;

	अगर (!msr_mtrr_valid(msr))
		वापस false;

	अगर (msr == MSR_IA32_CR_PAT) अणु
		वापस kvm_pat_valid(data);
	पूर्ण अन्यथा अगर (msr == MSR_MTRRdefType) अणु
		अगर (data & ~0xcff)
			वापस false;
		वापस valid_mtrr_type(data & 0xff);
	पूर्ण अन्यथा अगर (msr >= MSR_MTRRfix64K_00000 && msr <= MSR_MTRRfix4K_F8000) अणु
		क्रम (i = 0; i < 8 ; i++)
			अगर (!valid_mtrr_type((data >> (i * 8)) & 0xff))
				वापस false;
		वापस true;
	पूर्ण

	/* variable MTRRs */
	WARN_ON(!(msr >= 0x200 && msr < 0x200 + 2 * KVM_NR_VAR_MTRR));

	mask = kvm_vcpu_reserved_gpa_bits_raw(vcpu);
	अगर ((msr & 1) == 0) अणु
		/* MTRR base */
		अगर (!valid_mtrr_type(data & 0xff))
			वापस false;
		mask |= 0xf00;
	पूर्ण अन्यथा
		/* MTRR mask */
		mask |= 0x7ff;

	वापस (data & mask) == 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_mtrr_valid);

अटल bool mtrr_is_enabled(काष्ठा kvm_mtrr *mtrr_state)
अणु
	वापस !!(mtrr_state->deftype & IA32_MTRR_DEF_TYPE_E);
पूर्ण

अटल bool fixed_mtrr_is_enabled(काष्ठा kvm_mtrr *mtrr_state)
अणु
	वापस !!(mtrr_state->deftype & IA32_MTRR_DEF_TYPE_FE);
पूर्ण

अटल u8 mtrr_शेष_type(काष्ठा kvm_mtrr *mtrr_state)
अणु
	वापस mtrr_state->deftype & IA32_MTRR_DEF_TYPE_TYPE_MASK;
पूर्ण

अटल u8 mtrr_disabled_type(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * Intel SDM 11.11.2.2: all MTRRs are disabled when
	 * IA32_MTRR_DEF_TYPE.E bit is cleared, and the UC
	 * memory type is applied to all of physical memory.
	 *
	 * However, भव machines can be run with CPUID such that
	 * there are no MTRRs.  In that हाल, the firmware will never
	 * enable MTRRs and it is obviously undesirable to run the
	 * guest entirely with UC memory and we use WB.
	 */
	अगर (guest_cpuid_has(vcpu, X86_FEATURE_MTRR))
		वापस MTRR_TYPE_UNCACHABLE;
	अन्यथा
		वापस MTRR_TYPE_WRBACK;
पूर्ण

/*
* Three terms are used in the following code:
* - segment, it indicates the address segments covered by fixed MTRRs.
* - unit, it corresponds to the MSR entry in the segment.
* - range, a range is covered in one memory cache type.
*/
काष्ठा fixed_mtrr_segment अणु
	u64 start;
	u64 end;

	पूर्णांक range_shअगरt;

	/* the start position in kvm_mtrr.fixed_ranges[]. */
	पूर्णांक range_start;
पूर्ण;

अटल काष्ठा fixed_mtrr_segment fixed_seg_table[] = अणु
	/* MSR_MTRRfix64K_00000, 1 unit. 64K fixed mtrr. */
	अणु
		.start = 0x0,
		.end = 0x80000,
		.range_shअगरt = 16, /* 64K */
		.range_start = 0,
	पूर्ण,

	/*
	 * MSR_MTRRfix16K_80000 ... MSR_MTRRfix16K_A0000, 2 units,
	 * 16K fixed mtrr.
	 */
	अणु
		.start = 0x80000,
		.end = 0xc0000,
		.range_shअगरt = 14, /* 16K */
		.range_start = 8,
	पूर्ण,

	/*
	 * MSR_MTRRfix4K_C0000 ... MSR_MTRRfix4K_F8000, 8 units,
	 * 4K fixed mtrr.
	 */
	अणु
		.start = 0xc0000,
		.end = 0x100000,
		.range_shअगरt = 12, /* 12K */
		.range_start = 24,
	पूर्ण
पूर्ण;

/*
 * The size of unit is covered in one MSR, one MSR entry contains
 * 8 ranges so that unit size is always 8 * 2^range_shअगरt.
 */
अटल u64 fixed_mtrr_seg_unit_size(पूर्णांक seg)
अणु
	वापस 8 << fixed_seg_table[seg].range_shअगरt;
पूर्ण

अटल bool fixed_msr_to_seg_unit(u32 msr, पूर्णांक *seg, पूर्णांक *unit)
अणु
	चयन (msr) अणु
	हाल MSR_MTRRfix64K_00000:
		*seg = 0;
		*unit = 0;
		अवरोध;
	हाल MSR_MTRRfix16K_80000 ... MSR_MTRRfix16K_A0000:
		*seg = 1;
		*unit = array_index_nospec(
			msr - MSR_MTRRfix16K_80000,
			MSR_MTRRfix16K_A0000 - MSR_MTRRfix16K_80000 + 1);
		अवरोध;
	हाल MSR_MTRRfix4K_C0000 ... MSR_MTRRfix4K_F8000:
		*seg = 2;
		*unit = array_index_nospec(
			msr - MSR_MTRRfix4K_C0000,
			MSR_MTRRfix4K_F8000 - MSR_MTRRfix4K_C0000 + 1);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम fixed_mtrr_seg_unit_range(पूर्णांक seg, पूर्णांक unit, u64 *start, u64 *end)
अणु
	काष्ठा fixed_mtrr_segment *mtrr_seg = &fixed_seg_table[seg];
	u64 unit_size = fixed_mtrr_seg_unit_size(seg);

	*start = mtrr_seg->start + unit * unit_size;
	*end = *start + unit_size;
	WARN_ON(*end > mtrr_seg->end);
पूर्ण

अटल पूर्णांक fixed_mtrr_seg_unit_range_index(पूर्णांक seg, पूर्णांक unit)
अणु
	काष्ठा fixed_mtrr_segment *mtrr_seg = &fixed_seg_table[seg];

	WARN_ON(mtrr_seg->start + unit * fixed_mtrr_seg_unit_size(seg)
		> mtrr_seg->end);

	/* each unit has 8 ranges. */
	वापस mtrr_seg->range_start + 8 * unit;
पूर्ण

अटल पूर्णांक fixed_mtrr_seg_end_range_index(पूर्णांक seg)
अणु
	काष्ठा fixed_mtrr_segment *mtrr_seg = &fixed_seg_table[seg];
	पूर्णांक n;

	n = (mtrr_seg->end - mtrr_seg->start) >> mtrr_seg->range_shअगरt;
	वापस mtrr_seg->range_start + n - 1;
पूर्ण

अटल bool fixed_msr_to_range(u32 msr, u64 *start, u64 *end)
अणु
	पूर्णांक seg, unit;

	अगर (!fixed_msr_to_seg_unit(msr, &seg, &unit))
		वापस false;

	fixed_mtrr_seg_unit_range(seg, unit, start, end);
	वापस true;
पूर्ण

अटल पूर्णांक fixed_msr_to_range_index(u32 msr)
अणु
	पूर्णांक seg, unit;

	अगर (!fixed_msr_to_seg_unit(msr, &seg, &unit))
		वापस -1;

	वापस fixed_mtrr_seg_unit_range_index(seg, unit);
पूर्ण

अटल पूर्णांक fixed_mtrr_addr_to_seg(u64 addr)
अणु
	काष्ठा fixed_mtrr_segment *mtrr_seg;
	पूर्णांक seg, seg_num = ARRAY_SIZE(fixed_seg_table);

	क्रम (seg = 0; seg < seg_num; seg++) अणु
		mtrr_seg = &fixed_seg_table[seg];
		अगर (mtrr_seg->start <= addr && addr < mtrr_seg->end)
			वापस seg;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक fixed_mtrr_addr_seg_to_range_index(u64 addr, पूर्णांक seg)
अणु
	काष्ठा fixed_mtrr_segment *mtrr_seg;
	पूर्णांक index;

	mtrr_seg = &fixed_seg_table[seg];
	index = mtrr_seg->range_start;
	index += (addr - mtrr_seg->start) >> mtrr_seg->range_shअगरt;
	वापस index;
पूर्ण

अटल u64 fixed_mtrr_range_end_addr(पूर्णांक seg, पूर्णांक index)
अणु
	काष्ठा fixed_mtrr_segment *mtrr_seg = &fixed_seg_table[seg];
	पूर्णांक pos = index - mtrr_seg->range_start;

	वापस mtrr_seg->start + ((pos + 1) << mtrr_seg->range_shअगरt);
पूर्ण

अटल व्योम var_mtrr_range(काष्ठा kvm_mtrr_range *range, u64 *start, u64 *end)
अणु
	u64 mask;

	*start = range->base & PAGE_MASK;

	mask = range->mask & PAGE_MASK;

	/* This cannot overflow because writing to the reserved bits of
	 * variable MTRRs causes a #GP.
	 */
	*end = (*start | ~mask) + 1;
पूर्ण

अटल व्योम update_mtrr(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	काष्ठा kvm_mtrr *mtrr_state = &vcpu->arch.mtrr_state;
	gfn_t start, end;
	पूर्णांक index;

	अगर (msr == MSR_IA32_CR_PAT || !tdp_enabled ||
	      !kvm_arch_has_noncoherent_dma(vcpu->kvm))
		वापस;

	अगर (!mtrr_is_enabled(mtrr_state) && msr != MSR_MTRRdefType)
		वापस;

	/* fixed MTRRs. */
	अगर (fixed_msr_to_range(msr, &start, &end)) अणु
		अगर (!fixed_mtrr_is_enabled(mtrr_state))
			वापस;
	पूर्ण अन्यथा अगर (msr == MSR_MTRRdefType) अणु
		start = 0x0;
		end = ~0ULL;
	पूर्ण अन्यथा अणु
		/* variable range MTRRs. */
		index = (msr - 0x200) / 2;
		var_mtrr_range(&mtrr_state->var_ranges[index], &start, &end);
	पूर्ण

	kvm_zap_gfn_range(vcpu->kvm, gpa_to_gfn(start), gpa_to_gfn(end));
पूर्ण

अटल bool var_mtrr_range_is_valid(काष्ठा kvm_mtrr_range *range)
अणु
	वापस (range->mask & (1 << 11)) != 0;
पूर्ण

अटल व्योम set_var_mtrr_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data)
अणु
	काष्ठा kvm_mtrr *mtrr_state = &vcpu->arch.mtrr_state;
	काष्ठा kvm_mtrr_range *पंचांगp, *cur;
	पूर्णांक index, is_mtrr_mask;

	index = (msr - 0x200) / 2;
	is_mtrr_mask = msr - 0x200 - 2 * index;
	cur = &mtrr_state->var_ranges[index];

	/* हटाओ the entry अगर it's in the list. */
	अगर (var_mtrr_range_is_valid(cur))
		list_del(&mtrr_state->var_ranges[index].node);

	/*
	 * Set all illegal GPA bits in the mask, since those bits must
	 * implicitly be 0.  The bits are then cleared when पढ़ोing them.
	 */
	अगर (!is_mtrr_mask)
		cur->base = data;
	अन्यथा
		cur->mask = data | kvm_vcpu_reserved_gpa_bits_raw(vcpu);

	/* add it to the list अगर it's enabled. */
	अगर (var_mtrr_range_is_valid(cur)) अणु
		list_क्रम_each_entry(पंचांगp, &mtrr_state->head, node)
			अगर (cur->base >= पंचांगp->base)
				अवरोध;
		list_add_tail(&cur->node, &पंचांगp->node);
	पूर्ण
पूर्ण

पूर्णांक kvm_mtrr_set_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data)
अणु
	पूर्णांक index;

	अगर (!kvm_mtrr_valid(vcpu, msr, data))
		वापस 1;

	index = fixed_msr_to_range_index(msr);
	अगर (index >= 0)
		*(u64 *)&vcpu->arch.mtrr_state.fixed_ranges[index] = data;
	अन्यथा अगर (msr == MSR_MTRRdefType)
		vcpu->arch.mtrr_state.deftype = data;
	अन्यथा अगर (msr == MSR_IA32_CR_PAT)
		vcpu->arch.pat = data;
	अन्यथा
		set_var_mtrr_msr(vcpu, msr, data);

	update_mtrr(vcpu, msr);
	वापस 0;
पूर्ण

पूर्णांक kvm_mtrr_get_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *pdata)
अणु
	पूर्णांक index;

	/* MSR_MTRRcap is a पढ़ोonly MSR. */
	अगर (msr == MSR_MTRRcap) अणु
		/*
		 * SMRR = 0
		 * WC = 1
		 * FIX = 1
		 * VCNT = KVM_NR_VAR_MTRR
		 */
		*pdata = 0x500 | KVM_NR_VAR_MTRR;
		वापस 0;
	पूर्ण

	अगर (!msr_mtrr_valid(msr))
		वापस 1;

	index = fixed_msr_to_range_index(msr);
	अगर (index >= 0)
		*pdata = *(u64 *)&vcpu->arch.mtrr_state.fixed_ranges[index];
	अन्यथा अगर (msr == MSR_MTRRdefType)
		*pdata = vcpu->arch.mtrr_state.deftype;
	अन्यथा अगर (msr == MSR_IA32_CR_PAT)
		*pdata = vcpu->arch.pat;
	अन्यथा अणु	/* Variable MTRRs */
		पूर्णांक is_mtrr_mask;

		index = (msr - 0x200) / 2;
		is_mtrr_mask = msr - 0x200 - 2 * index;
		अगर (!is_mtrr_mask)
			*pdata = vcpu->arch.mtrr_state.var_ranges[index].base;
		अन्यथा
			*pdata = vcpu->arch.mtrr_state.var_ranges[index].mask;

		*pdata &= ~kvm_vcpu_reserved_gpa_bits_raw(vcpu);
	पूर्ण

	वापस 0;
पूर्ण

व्योम kvm_vcpu_mtrr_init(काष्ठा kvm_vcpu *vcpu)
अणु
	INIT_LIST_HEAD(&vcpu->arch.mtrr_state.head);
पूर्ण

काष्ठा mtrr_iter अणु
	/* input fields. */
	काष्ठा kvm_mtrr *mtrr_state;
	u64 start;
	u64 end;

	/* output fields. */
	पूर्णांक mem_type;
	/* mtrr is completely disabled? */
	bool mtrr_disabled;
	/* [start, end) is not fully covered in MTRRs? */
	bool partial_map;

	/* निजी fields. */
	जोड़ अणु
		/* used क्रम fixed MTRRs. */
		काष्ठा अणु
			पूर्णांक index;
			पूर्णांक seg;
		पूर्ण;

		/* used क्रम var MTRRs. */
		काष्ठा अणु
			काष्ठा kvm_mtrr_range *range;
			/* max address has been covered in var MTRRs. */
			u64 start_max;
		पूर्ण;
	पूर्ण;

	bool fixed;
पूर्ण;

अटल bool mtrr_lookup_fixed_start(काष्ठा mtrr_iter *iter)
अणु
	पूर्णांक seg, index;

	अगर (!fixed_mtrr_is_enabled(iter->mtrr_state))
		वापस false;

	seg = fixed_mtrr_addr_to_seg(iter->start);
	अगर (seg < 0)
		वापस false;

	iter->fixed = true;
	index = fixed_mtrr_addr_seg_to_range_index(iter->start, seg);
	iter->index = index;
	iter->seg = seg;
	वापस true;
पूर्ण

अटल bool match_var_range(काष्ठा mtrr_iter *iter,
			    काष्ठा kvm_mtrr_range *range)
अणु
	u64 start, end;

	var_mtrr_range(range, &start, &end);
	अगर (!(start >= iter->end || end <= iter->start)) अणु
		iter->range = range;

		/*
		 * the function is called when we करो kvm_mtrr.head walking.
		 * Range has the minimum base address which पूर्णांकerleaves
		 * [looker->start_max, looker->end).
		 */
		iter->partial_map |= iter->start_max < start;

		/* update the max address has been covered. */
		iter->start_max = max(iter->start_max, end);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम __mtrr_lookup_var_next(काष्ठा mtrr_iter *iter)
अणु
	काष्ठा kvm_mtrr *mtrr_state = iter->mtrr_state;

	list_क्रम_each_entry_जारी(iter->range, &mtrr_state->head, node)
		अगर (match_var_range(iter, iter->range))
			वापस;

	iter->range = शून्य;
	iter->partial_map |= iter->start_max < iter->end;
पूर्ण

अटल व्योम mtrr_lookup_var_start(काष्ठा mtrr_iter *iter)
अणु
	काष्ठा kvm_mtrr *mtrr_state = iter->mtrr_state;

	iter->fixed = false;
	iter->start_max = iter->start;
	iter->range = शून्य;
	iter->range = list_prepare_entry(iter->range, &mtrr_state->head, node);

	__mtrr_lookup_var_next(iter);
पूर्ण

अटल व्योम mtrr_lookup_fixed_next(काष्ठा mtrr_iter *iter)
अणु
	/* terminate the lookup. */
	अगर (fixed_mtrr_range_end_addr(iter->seg, iter->index) >= iter->end) अणु
		iter->fixed = false;
		iter->range = शून्य;
		वापस;
	पूर्ण

	iter->index++;

	/* have looked up क्रम all fixed MTRRs. */
	अगर (iter->index >= ARRAY_SIZE(iter->mtrr_state->fixed_ranges))
		वापस mtrr_lookup_var_start(iter);

	/* चयन to next segment. */
	अगर (iter->index > fixed_mtrr_seg_end_range_index(iter->seg))
		iter->seg++;
पूर्ण

अटल व्योम mtrr_lookup_var_next(काष्ठा mtrr_iter *iter)
अणु
	__mtrr_lookup_var_next(iter);
पूर्ण

अटल व्योम mtrr_lookup_start(काष्ठा mtrr_iter *iter)
अणु
	अगर (!mtrr_is_enabled(iter->mtrr_state)) अणु
		iter->mtrr_disabled = true;
		वापस;
	पूर्ण

	अगर (!mtrr_lookup_fixed_start(iter))
		mtrr_lookup_var_start(iter);
पूर्ण

अटल व्योम mtrr_lookup_init(काष्ठा mtrr_iter *iter,
			     काष्ठा kvm_mtrr *mtrr_state, u64 start, u64 end)
अणु
	iter->mtrr_state = mtrr_state;
	iter->start = start;
	iter->end = end;
	iter->mtrr_disabled = false;
	iter->partial_map = false;
	iter->fixed = false;
	iter->range = शून्य;

	mtrr_lookup_start(iter);
पूर्ण

अटल bool mtrr_lookup_okay(काष्ठा mtrr_iter *iter)
अणु
	अगर (iter->fixed) अणु
		iter->mem_type = iter->mtrr_state->fixed_ranges[iter->index];
		वापस true;
	पूर्ण

	अगर (iter->range) अणु
		iter->mem_type = iter->range->base & 0xff;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम mtrr_lookup_next(काष्ठा mtrr_iter *iter)
अणु
	अगर (iter->fixed)
		mtrr_lookup_fixed_next(iter);
	अन्यथा
		mtrr_lookup_var_next(iter);
पूर्ण

#घोषणा mtrr_क्रम_each_mem_type(_iter_, _mtrr_, _gpa_start_, _gpa_end_) \
	क्रम (mtrr_lookup_init(_iter_, _mtrr_, _gpa_start_, _gpa_end_); \
	     mtrr_lookup_okay(_iter_); mtrr_lookup_next(_iter_))

u8 kvm_mtrr_get_guest_memory_type(काष्ठा kvm_vcpu *vcpu, gfn_t gfn)
अणु
	काष्ठा kvm_mtrr *mtrr_state = &vcpu->arch.mtrr_state;
	काष्ठा mtrr_iter iter;
	u64 start, end;
	पूर्णांक type = -1;
	स्थिर पूर्णांक wt_wb_mask = (1 << MTRR_TYPE_WRBACK)
			       | (1 << MTRR_TYPE_WRTHROUGH);

	start = gfn_to_gpa(gfn);
	end = start + PAGE_SIZE;

	mtrr_क्रम_each_mem_type(&iter, mtrr_state, start, end) अणु
		पूर्णांक curr_type = iter.mem_type;

		/*
		 * Please refer to Intel SDM Volume 3: 11.11.4.1 MTRR
		 * Precedences.
		 */

		अगर (type == -1) अणु
			type = curr_type;
			जारी;
		पूर्ण

		/*
		 * If two or more variable memory ranges match and the
		 * memory types are identical, then that memory type is
		 * used.
		 */
		अगर (type == curr_type)
			जारी;

		/*
		 * If two or more variable memory ranges match and one of
		 * the memory types is UC, the UC memory type used.
		 */
		अगर (curr_type == MTRR_TYPE_UNCACHABLE)
			वापस MTRR_TYPE_UNCACHABLE;

		/*
		 * If two or more variable memory ranges match and the
		 * memory types are WT and WB, the WT memory type is used.
		 */
		अगर (((1 << type) & wt_wb_mask) &&
		      ((1 << curr_type) & wt_wb_mask)) अणु
			type = MTRR_TYPE_WRTHROUGH;
			जारी;
		पूर्ण

		/*
		 * For overlaps not defined by the above rules, processor
		 * behavior is undefined.
		 */

		/* We use WB क्रम this undefined behavior. :( */
		वापस MTRR_TYPE_WRBACK;
	पूर्ण

	अगर (iter.mtrr_disabled)
		वापस mtrr_disabled_type(vcpu);

	/* not contained in any MTRRs. */
	अगर (type == -1)
		वापस mtrr_शेष_type(mtrr_state);

	/*
	 * We just check one page, partially covered by MTRRs is
	 * impossible.
	 */
	WARN_ON(iter.partial_map);

	वापस type;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_mtrr_get_guest_memory_type);

bool kvm_mtrr_check_gfn_range_consistency(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
					  पूर्णांक page_num)
अणु
	काष्ठा kvm_mtrr *mtrr_state = &vcpu->arch.mtrr_state;
	काष्ठा mtrr_iter iter;
	u64 start, end;
	पूर्णांक type = -1;

	start = gfn_to_gpa(gfn);
	end = gfn_to_gpa(gfn + page_num);
	mtrr_क्रम_each_mem_type(&iter, mtrr_state, start, end) अणु
		अगर (type == -1) अणु
			type = iter.mem_type;
			जारी;
		पूर्ण

		अगर (type != iter.mem_type)
			वापस false;
	पूर्ण

	अगर (iter.mtrr_disabled)
		वापस true;

	अगर (!iter.partial_map)
		वापस true;

	अगर (type == -1)
		वापस true;

	वापस type == mtrr_शेष_type(mtrr_state);
पूर्ण
