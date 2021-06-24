<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS TLB handling, this file is part of the Linux host kernel so that
 * TLB handlers run from KSEG0
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/srcu.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbdebug.h>

#अघोषित CONFIG_MIPS_MT
#समावेश <यंत्र/r4kcache.h>
#घोषणा CONFIG_MIPS_MT

अचिन्हित दीर्घ GUESTID_MASK;
EXPORT_SYMBOL_GPL(GUESTID_MASK);
अचिन्हित दीर्घ GUESTID_FIRST_VERSION;
EXPORT_SYMBOL_GPL(GUESTID_FIRST_VERSION);
अचिन्हित दीर्घ GUESTID_VERSION_MASK;
EXPORT_SYMBOL_GPL(GUESTID_VERSION_MASK);

अटल u32 kvm_mips_get_root_asid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा mm_काष्ठा *gpa_mm = &vcpu->kvm->arch.gpa_mm;

	अगर (cpu_has_guestid)
		वापस 0;
	अन्यथा
		वापस cpu_asid(smp_processor_id(), gpa_mm);
पूर्ण

अटल पूर्णांक _kvm_mips_host_tlb_inv(अचिन्हित दीर्घ entryhi)
अणु
	पूर्णांक idx;

	ग_लिखो_c0_entryhi(entryhi);
	mtc0_tlbw_hazard();

	tlb_probe();
	tlb_probe_hazard();
	idx = पढ़ो_c0_index();

	अगर (idx >= current_cpu_data.tlbsize)
		BUG();

	अगर (idx >= 0) अणु
		ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(idx));
		ग_लिखो_c0_entrylo0(0);
		ग_लिखो_c0_entrylo1(0);
		mtc0_tlbw_hazard();

		tlb_ग_लिखो_indexed();
		tlbw_use_hazard();
	पूर्ण

	वापस idx;
पूर्ण

/* GuestID management */

/**
 * clear_root_gid() - Set GuestCtl1.RID क्रम normal root operation.
 */
अटल अंतरभूत व्योम clear_root_gid(व्योम)
अणु
	अगर (cpu_has_guestid) अणु
		clear_c0_guestctl1(MIPS_GCTL1_RID);
		mtc0_tlbw_hazard();
	पूर्ण
पूर्ण

/**
 * set_root_gid_to_guest_gid() - Set GuestCtl1.RID to match GuestCtl1.ID.
 *
 * Sets the root GuestID to match the current guest GuestID, क्रम TLB operation
 * on the GPA->RPA mappings in the root TLB.
 *
 * The caller must be sure to disable HTW जबतक the root GID is set, and
 * possibly दीर्घer अगर TLB रेजिस्टरs are modअगरied.
 */
अटल अंतरभूत व्योम set_root_gid_to_guest_gid(व्योम)
अणु
	अचिन्हित पूर्णांक guestctl1;

	अगर (cpu_has_guestid) अणु
		back_to_back_c0_hazard();
		guestctl1 = पढ़ो_c0_guestctl1();
		guestctl1 = (guestctl1 & ~MIPS_GCTL1_RID) |
			((guestctl1 & MIPS_GCTL1_ID) >> MIPS_GCTL1_ID_SHIFT)
						     << MIPS_GCTL1_RID_SHIFT;
		ग_लिखो_c0_guestctl1(guestctl1);
		mtc0_tlbw_hazard();
	पूर्ण
पूर्ण

पूर्णांक kvm_vz_host_tlb_inv(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ va)
अणु
	पूर्णांक idx;
	अचिन्हित दीर्घ flags, old_entryhi;

	local_irq_save(flags);
	htw_stop();

	/* Set root GuestID क्रम root probe and ग_लिखो of guest TLB entry */
	set_root_gid_to_guest_gid();

	old_entryhi = पढ़ो_c0_entryhi();

	idx = _kvm_mips_host_tlb_inv((va & VPN2_MASK) |
				     kvm_mips_get_root_asid(vcpu));

	ग_लिखो_c0_entryhi(old_entryhi);
	clear_root_gid();
	mtc0_tlbw_hazard();

	htw_start();
	local_irq_restore(flags);

	/*
	 * We करोn't want to get reserved inकाष्ठाion exceptions क्रम missing tlb
	 * entries.
	 */
	अगर (cpu_has_vtag_icache)
		flush_icache_all();

	अगर (idx > 0)
		kvm_debug("%s: Invalidated root entryhi %#lx @ idx %d\n",
			  __func__, (va & VPN2_MASK) |
				    kvm_mips_get_root_asid(vcpu), idx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vz_host_tlb_inv);

/**
 * kvm_vz_guest_tlb_lookup() - Lookup a guest VZ TLB mapping.
 * @vcpu:	KVM VCPU poपूर्णांकer.
 * @gpa:	Guest भव address in a TLB mapped guest segment.
 * @gpa:	Ponter to output guest physical address it maps to.
 *
 * Converts a guest भव address in a guest TLB mapped segment to a guest
 * physical address, by probing the guest TLB.
 *
 * Returns:	0 अगर guest TLB mapping exists क्रम @gva. *@gpa will have been
 *		written.
 *		-EFAULT अगर no guest TLB mapping exists क्रम @gva. *@gpa may not
 *		have been written.
 */
पूर्णांक kvm_vz_guest_tlb_lookup(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva,
			    अचिन्हित दीर्घ *gpa)
अणु
	अचिन्हित दीर्घ o_entryhi, o_entrylo[2], o_pagemask;
	अचिन्हित पूर्णांक o_index;
	अचिन्हित दीर्घ entrylo[2], pagemask, pagemaskbit, pa;
	अचिन्हित दीर्घ flags;
	पूर्णांक index;

	/* Probe the guest TLB क्रम a mapping */
	local_irq_save(flags);
	/* Set root GuestID क्रम root probe of guest TLB entry */
	htw_stop();
	set_root_gid_to_guest_gid();

	o_entryhi = पढ़ो_gc0_entryhi();
	o_index = पढ़ो_gc0_index();

	ग_लिखो_gc0_entryhi((o_entryhi & 0x3ff) | (gva & ~0xfffl));
	mtc0_tlbw_hazard();
	guest_tlb_probe();
	tlb_probe_hazard();

	index = पढ़ो_gc0_index();
	अगर (index < 0) अणु
		/* No match, fail */
		ग_लिखो_gc0_entryhi(o_entryhi);
		ग_लिखो_gc0_index(o_index);

		clear_root_gid();
		htw_start();
		local_irq_restore(flags);
		वापस -EFAULT;
	पूर्ण

	/* Match! पढ़ो the TLB entry */
	o_entrylo[0] = पढ़ो_gc0_entrylo0();
	o_entrylo[1] = पढ़ो_gc0_entrylo1();
	o_pagemask = पढ़ो_gc0_pagemask();

	mtc0_tlbr_hazard();
	guest_tlb_पढ़ो();
	tlb_पढ़ो_hazard();

	entrylo[0] = पढ़ो_gc0_entrylo0();
	entrylo[1] = पढ़ो_gc0_entrylo1();
	pagemask = ~पढ़ो_gc0_pagemask() & ~0x1fffl;

	ग_लिखो_gc0_entryhi(o_entryhi);
	ग_लिखो_gc0_index(o_index);
	ग_लिखो_gc0_entrylo0(o_entrylo[0]);
	ग_लिखो_gc0_entrylo1(o_entrylo[1]);
	ग_लिखो_gc0_pagemask(o_pagemask);

	clear_root_gid();
	htw_start();
	local_irq_restore(flags);

	/* Select one of the EntryLo values and पूर्णांकerpret the GPA */
	pagemaskbit = (pagemask ^ (pagemask & (pagemask - 1))) >> 1;
	pa = entrylo[!!(gva & pagemaskbit)];

	/*
	 * TLB entry may have become invalid since TLB probe अगर physical FTLB
	 * entries are shared between thपढ़ोs (e.g. I6400).
	 */
	अगर (!(pa & ENTRYLO_V))
		वापस -EFAULT;

	/*
	 * Note, this करोesn't take guest MIPS32 XPA पूर्णांकo account, where PFN is
	 * split with XI/RI in the middle.
	 */
	pa = (pa << 6) & ~0xfffl;
	pa |= gva & ~(pagemask | pagemaskbit);

	*gpa = pa;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vz_guest_tlb_lookup);

/**
 * kvm_vz_local_flush_roottlb_all_guests() - Flush all root TLB entries क्रम
 * guests.
 *
 * Invalidate all entries in root tlb which are GPA mappings.
 */
व्योम kvm_vz_local_flush_roottlb_all_guests(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ old_entryhi, old_pagemask, old_guestctl1;
	पूर्णांक entry;

	अगर (WARN_ON(!cpu_has_guestid))
		वापस;

	local_irq_save(flags);
	htw_stop();

	/* TLBR may clobber EntryHi.ASID, PageMask, and GuestCtl1.RID */
	old_entryhi = पढ़ो_c0_entryhi();
	old_pagemask = पढ़ो_c0_pagemask();
	old_guestctl1 = पढ़ो_c0_guestctl1();

	/*
	 * Invalidate guest entries in root TLB जबतक leaving root entries
	 * पूर्णांकact when possible.
	 */
	क्रम (entry = 0; entry < current_cpu_data.tlbsize; entry++) अणु
		ग_लिखो_c0_index(entry);
		mtc0_tlbw_hazard();
		tlb_पढ़ो();
		tlb_पढ़ो_hazard();

		/* Don't invalidate non-guest (RVA) mappings in the root TLB */
		अगर (!(पढ़ो_c0_guestctl1() & MIPS_GCTL1_RID))
			जारी;

		/* Make sure all entries dअगरfer. */
		ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(entry));
		ग_लिखो_c0_entrylo0(0);
		ग_लिखो_c0_entrylo1(0);
		ग_लिखो_c0_guestctl1(0);
		mtc0_tlbw_hazard();
		tlb_ग_लिखो_indexed();
	पूर्ण

	ग_लिखो_c0_entryhi(old_entryhi);
	ग_लिखो_c0_pagemask(old_pagemask);
	ग_लिखो_c0_guestctl1(old_guestctl1);
	tlbw_use_hazard();

	htw_start();
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vz_local_flush_roottlb_all_guests);

/**
 * kvm_vz_local_flush_guesttlb_all() - Flush all guest TLB entries.
 *
 * Invalidate all entries in guest tlb irrespective of guestid.
 */
व्योम kvm_vz_local_flush_guesttlb_all(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ old_index;
	अचिन्हित दीर्घ old_entryhi;
	अचिन्हित दीर्घ old_entrylo[2];
	अचिन्हित दीर्घ old_pagemask;
	पूर्णांक entry;
	u64 cvmmemctl2 = 0;

	local_irq_save(flags);

	/* Preserve all clobbered guest रेजिस्टरs */
	old_index = पढ़ो_gc0_index();
	old_entryhi = पढ़ो_gc0_entryhi();
	old_entrylo[0] = पढ़ो_gc0_entrylo0();
	old_entrylo[1] = पढ़ो_gc0_entrylo1();
	old_pagemask = पढ़ो_gc0_pagemask();

	चयन (current_cpu_type()) अणु
	हाल CPU_CAVIUM_OCTEON3:
		/* Inhibit machine check due to multiple matching TLB entries */
		cvmmemctl2 = पढ़ो_c0_cvmmemctl2();
		cvmmemctl2 |= CVMMEMCTL2_INHIBITTS;
		ग_लिखो_c0_cvmmemctl2(cvmmemctl2);
		अवरोध;
	पूर्ण

	/* Invalidate guest entries in guest TLB */
	ग_लिखो_gc0_entrylo0(0);
	ग_लिखो_gc0_entrylo1(0);
	ग_लिखो_gc0_pagemask(0);
	क्रम (entry = 0; entry < current_cpu_data.guest.tlbsize; entry++) अणु
		/* Make sure all entries dअगरfer. */
		ग_लिखो_gc0_index(entry);
		ग_लिखो_gc0_entryhi(UNIQUE_GUEST_ENTRYHI(entry));
		mtc0_tlbw_hazard();
		guest_tlb_ग_लिखो_indexed();
	पूर्ण

	अगर (cvmmemctl2) अणु
		cvmmemctl2 &= ~CVMMEMCTL2_INHIBITTS;
		ग_लिखो_c0_cvmmemctl2(cvmmemctl2);
	पूर्ण

	ग_लिखो_gc0_index(old_index);
	ग_लिखो_gc0_entryhi(old_entryhi);
	ग_लिखो_gc0_entrylo0(old_entrylo[0]);
	ग_लिखो_gc0_entrylo1(old_entrylo[1]);
	ग_लिखो_gc0_pagemask(old_pagemask);
	tlbw_use_hazard();

	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vz_local_flush_guesttlb_all);

/**
 * kvm_vz_save_guesttlb() - Save a range of guest TLB entries.
 * @buf:	Buffer to ग_लिखो TLB entries पूर्णांकo.
 * @index:	Start index.
 * @count:	Number of entries to save.
 *
 * Save a range of guest TLB entries. The caller must ensure पूर्णांकerrupts are
 * disabled.
 */
व्योम kvm_vz_save_guesttlb(काष्ठा kvm_mips_tlb *buf, अचिन्हित पूर्णांक index,
			  अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक end = index + count;
	अचिन्हित दीर्घ old_entryhi, old_entrylo0, old_entrylo1, old_pagemask;
	अचिन्हित पूर्णांक guestctl1 = 0;
	पूर्णांक old_index, i;

	/* Save रेजिस्टरs we're about to clobber */
	old_index = पढ़ो_gc0_index();
	old_entryhi = पढ़ो_gc0_entryhi();
	old_entrylo0 = पढ़ो_gc0_entrylo0();
	old_entrylo1 = पढ़ो_gc0_entrylo1();
	old_pagemask = पढ़ो_gc0_pagemask();

	/* Set root GuestID क्रम root probe */
	htw_stop();
	set_root_gid_to_guest_gid();
	अगर (cpu_has_guestid)
		guestctl1 = पढ़ो_c0_guestctl1();

	/* Read each entry from guest TLB */
	क्रम (i = index; i < end; ++i, ++buf) अणु
		ग_लिखो_gc0_index(i);

		mtc0_tlbr_hazard();
		guest_tlb_पढ़ो();
		tlb_पढ़ो_hazard();

		अगर (cpu_has_guestid &&
		    (पढ़ो_c0_guestctl1() ^ guestctl1) & MIPS_GCTL1_RID) अणु
			/* Entry invalid or beदीर्घs to another guest */
			buf->tlb_hi = UNIQUE_GUEST_ENTRYHI(i);
			buf->tlb_lo[0] = 0;
			buf->tlb_lo[1] = 0;
			buf->tlb_mask = 0;
		पूर्ण अन्यथा अणु
			/* Entry beदीर्घs to the right guest */
			buf->tlb_hi = पढ़ो_gc0_entryhi();
			buf->tlb_lo[0] = पढ़ो_gc0_entrylo0();
			buf->tlb_lo[1] = पढ़ो_gc0_entrylo1();
			buf->tlb_mask = पढ़ो_gc0_pagemask();
		पूर्ण
	पूर्ण

	/* Clear root GuestID again */
	clear_root_gid();
	htw_start();

	/* Restore clobbered रेजिस्टरs */
	ग_लिखो_gc0_index(old_index);
	ग_लिखो_gc0_entryhi(old_entryhi);
	ग_लिखो_gc0_entrylo0(old_entrylo0);
	ग_लिखो_gc0_entrylo1(old_entrylo1);
	ग_लिखो_gc0_pagemask(old_pagemask);

	tlbw_use_hazard();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vz_save_guesttlb);

/**
 * kvm_vz_load_guesttlb() - Save a range of guest TLB entries.
 * @buf:	Buffer to पढ़ो TLB entries from.
 * @index:	Start index.
 * @count:	Number of entries to load.
 *
 * Load a range of guest TLB entries. The caller must ensure पूर्णांकerrupts are
 * disabled.
 */
व्योम kvm_vz_load_guesttlb(स्थिर काष्ठा kvm_mips_tlb *buf, अचिन्हित पूर्णांक index,
			  अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक end = index + count;
	अचिन्हित दीर्घ old_entryhi, old_entrylo0, old_entrylo1, old_pagemask;
	पूर्णांक old_index, i;

	/* Save रेजिस्टरs we're about to clobber */
	old_index = पढ़ो_gc0_index();
	old_entryhi = पढ़ो_gc0_entryhi();
	old_entrylo0 = पढ़ो_gc0_entrylo0();
	old_entrylo1 = पढ़ो_gc0_entrylo1();
	old_pagemask = पढ़ो_gc0_pagemask();

	/* Set root GuestID क्रम root probe */
	htw_stop();
	set_root_gid_to_guest_gid();

	/* Write each entry to guest TLB */
	क्रम (i = index; i < end; ++i, ++buf) अणु
		ग_लिखो_gc0_index(i);
		ग_लिखो_gc0_entryhi(buf->tlb_hi);
		ग_लिखो_gc0_entrylo0(buf->tlb_lo[0]);
		ग_लिखो_gc0_entrylo1(buf->tlb_lo[1]);
		ग_लिखो_gc0_pagemask(buf->tlb_mask);

		mtc0_tlbw_hazard();
		guest_tlb_ग_लिखो_indexed();
	पूर्ण

	/* Clear root GuestID again */
	clear_root_gid();
	htw_start();

	/* Restore clobbered रेजिस्टरs */
	ग_लिखो_gc0_index(old_index);
	ग_लिखो_gc0_entryhi(old_entryhi);
	ग_लिखो_gc0_entrylo0(old_entrylo0);
	ग_लिखो_gc0_entrylo1(old_entrylo1);
	ग_लिखो_gc0_pagemask(old_pagemask);

	tlbw_use_hazard();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_vz_load_guesttlb);

#अगर_घोषित CONFIG_CPU_LOONGSON64
व्योम kvm_loongson_clear_guest_vtlb(व्योम)
अणु
	पूर्णांक idx = पढ़ो_gc0_index();

	/* Set root GuestID क्रम root probe and ग_लिखो of guest TLB entry */
	set_root_gid_to_guest_gid();

	ग_लिखो_gc0_index(0);
	guest_tlbinvf();
	ग_लिखो_gc0_index(idx);

	clear_root_gid();
	set_c0_diag(LOONGSON_DIAG_ITLB | LOONGSON_DIAG_DTLB);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_loongson_clear_guest_vtlb);

व्योम kvm_loongson_clear_guest_ftlb(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक idx = पढ़ो_gc0_index();

	/* Set root GuestID क्रम root probe and ग_लिखो of guest TLB entry */
	set_root_gid_to_guest_gid();

	क्रम (i = current_cpu_data.tlbsizevtlb;
	     i < (current_cpu_data.tlbsizevtlb +
		     current_cpu_data.tlbsizeftlbsets);
	     i++) अणु
		ग_लिखो_gc0_index(i);
		guest_tlbinvf();
	पूर्ण
	ग_लिखो_gc0_index(idx);

	clear_root_gid();
	set_c0_diag(LOONGSON_DIAG_ITLB | LOONGSON_DIAG_DTLB);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_loongson_clear_guest_ftlb);
#पूर्ण_अगर
