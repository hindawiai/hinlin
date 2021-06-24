<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2013 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Yu Liu, yu.liu@मुक्तscale.com
 *         Scott Wood, scottwood@मुक्तscale.com
 *         Ashish Kalra, ashish.kalra@मुक्तscale.com
 *         Varun Sethi, varun.sethi@मुक्तscale.com
 *         Alexander Graf, agraf@suse.de
 *
 * Description:
 * This file is based on arch/घातerpc/kvm/44x_tlb.c,
 * by Hollis Blanअक्षरd <hollisb@us.ibm.com>.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/log2.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/kvm_ppc.h>

#समावेश "e500.h"
#समावेश "trace_booke.h"
#समावेश "timing.h"
#समावेश "e500_mmu_host.h"

अटल अंतरभूत अचिन्हित पूर्णांक gtlb0_get_next_victim(
		काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	अचिन्हित पूर्णांक victim;

	victim = vcpu_e500->gtlb_nv[0]++;
	अगर (unlikely(vcpu_e500->gtlb_nv[0] >= vcpu_e500->gtlb_params[0].ways))
		vcpu_e500->gtlb_nv[0] = 0;

	वापस victim;
पूर्ण

अटल पूर्णांक tlb0_set_base(gva_t addr, पूर्णांक sets, पूर्णांक ways)
अणु
	पूर्णांक set_base;

	set_base = (addr >> PAGE_SHIFT) & (sets - 1);
	set_base *= ways;

	वापस set_base;
पूर्ण

अटल पूर्णांक gtlb0_set_base(काष्ठा kvmppc_vcpu_e500 *vcpu_e500, gva_t addr)
अणु
	वापस tlb0_set_base(addr, vcpu_e500->gtlb_params[0].sets,
			     vcpu_e500->gtlb_params[0].ways);
पूर्ण

अटल अचिन्हित पूर्णांक get_tlb_esel(काष्ठा kvm_vcpu *vcpu, पूर्णांक tlbsel)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक esel = get_tlb_esel_bit(vcpu);

	अगर (tlbsel == 0) अणु
		esel &= vcpu_e500->gtlb_params[0].ways - 1;
		esel += gtlb0_set_base(vcpu_e500, vcpu->arch.shared->mas2);
	पूर्ण अन्यथा अणु
		esel &= vcpu_e500->gtlb_params[tlbsel].entries - 1;
	पूर्ण

	वापस esel;
पूर्ण

/* Search the guest TLB क्रम a matching entry. */
अटल पूर्णांक kvmppc_e500_tlb_index(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
		gva_t eaddr, पूर्णांक tlbsel, अचिन्हित पूर्णांक pid, पूर्णांक as)
अणु
	पूर्णांक size = vcpu_e500->gtlb_params[tlbsel].entries;
	अचिन्हित पूर्णांक set_base, offset;
	पूर्णांक i;

	अगर (tlbsel == 0) अणु
		set_base = gtlb0_set_base(vcpu_e500, eaddr);
		size = vcpu_e500->gtlb_params[0].ways;
	पूर्ण अन्यथा अणु
		अगर (eaddr < vcpu_e500->tlb1_min_eaddr ||
				eaddr > vcpu_e500->tlb1_max_eaddr)
			वापस -1;
		set_base = 0;
	पूर्ण

	offset = vcpu_e500->gtlb_offset[tlbsel];

	क्रम (i = 0; i < size; i++) अणु
		काष्ठा kvm_book3e_206_tlb_entry *tlbe =
			&vcpu_e500->gtlb_arch[offset + set_base + i];
		अचिन्हित पूर्णांक tid;

		अगर (eaddr < get_tlb_eaddr(tlbe))
			जारी;

		अगर (eaddr > get_tlb_end(tlbe))
			जारी;

		tid = get_tlb_tid(tlbe);
		अगर (tid && (tid != pid))
			जारी;

		अगर (!get_tlb_v(tlbe))
			जारी;

		अगर (get_tlb_ts(tlbe) != as && as != -1)
			जारी;

		वापस set_base + i;
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम kvmppc_e500_deliver_tlb_miss(काष्ठा kvm_vcpu *vcpu,
		gva_t eaddr, पूर्णांक as)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	अचिन्हित पूर्णांक victim, tsized;
	पूर्णांक tlbsel;

	/* since we only have two TLBs, only lower bit is used. */
	tlbsel = (vcpu->arch.shared->mas4 >> 28) & 0x1;
	victim = (tlbsel == 0) ? gtlb0_get_next_victim(vcpu_e500) : 0;
	tsized = (vcpu->arch.shared->mas4 >> 7) & 0x1f;

	vcpu->arch.shared->mas0 = MAS0_TLBSEL(tlbsel) | MAS0_ESEL(victim)
		| MAS0_NV(vcpu_e500->gtlb_nv[tlbsel]);
	vcpu->arch.shared->mas1 = MAS1_VALID | (as ? MAS1_TS : 0)
		| MAS1_TID(get_tlbmiss_tid(vcpu))
		| MAS1_TSIZE(tsized);
	vcpu->arch.shared->mas2 = (eaddr & MAS2_EPN)
		| (vcpu->arch.shared->mas4 & MAS2_ATTRIB_MASK);
	vcpu->arch.shared->mas7_3 &= MAS3_U0 | MAS3_U1 | MAS3_U2 | MAS3_U3;
	vcpu->arch.shared->mas6 = (vcpu->arch.shared->mas6 & MAS6_SPID1)
		| (get_cur_pid(vcpu) << 16)
		| (as ? MAS6_SAS : 0);
पूर्ण

अटल व्योम kvmppc_recalc_tlb1map_range(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	पूर्णांक size = vcpu_e500->gtlb_params[1].entries;
	अचिन्हित पूर्णांक offset;
	gva_t eaddr;
	पूर्णांक i;

	vcpu_e500->tlb1_min_eaddr = ~0UL;
	vcpu_e500->tlb1_max_eaddr = 0;
	offset = vcpu_e500->gtlb_offset[1];

	क्रम (i = 0; i < size; i++) अणु
		काष्ठा kvm_book3e_206_tlb_entry *tlbe =
			&vcpu_e500->gtlb_arch[offset + i];

		अगर (!get_tlb_v(tlbe))
			जारी;

		eaddr = get_tlb_eaddr(tlbe);
		vcpu_e500->tlb1_min_eaddr =
				min(vcpu_e500->tlb1_min_eaddr, eaddr);

		eaddr = get_tlb_end(tlbe);
		vcpu_e500->tlb1_max_eaddr =
				max(vcpu_e500->tlb1_max_eaddr, eaddr);
	पूर्ण
पूर्ण

अटल पूर्णांक kvmppc_need_recalc_tlb1map_range(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
				काष्ठा kvm_book3e_206_tlb_entry *gtlbe)
अणु
	अचिन्हित दीर्घ start, end, size;

	size = get_tlb_bytes(gtlbe);
	start = get_tlb_eaddr(gtlbe) & ~(size - 1);
	end = start + size - 1;

	वापस vcpu_e500->tlb1_min_eaddr == start ||
			vcpu_e500->tlb1_max_eaddr == end;
पूर्ण

/* This function is supposed to be called क्रम a adding a new valid tlb entry */
अटल व्योम kvmppc_set_tlb1map_range(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_book3e_206_tlb_entry *gtlbe)
अणु
	अचिन्हित दीर्घ start, end, size;
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	अगर (!get_tlb_v(gtlbe))
		वापस;

	size = get_tlb_bytes(gtlbe);
	start = get_tlb_eaddr(gtlbe) & ~(size - 1);
	end = start + size - 1;

	vcpu_e500->tlb1_min_eaddr = min(vcpu_e500->tlb1_min_eaddr, start);
	vcpu_e500->tlb1_max_eaddr = max(vcpu_e500->tlb1_max_eaddr, end);
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_e500_gtlbe_invalidate(
				काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
				पूर्णांक tlbsel, पूर्णांक esel)
अणु
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe =
		get_entry(vcpu_e500, tlbsel, esel);

	अगर (unlikely(get_tlb_iprot(gtlbe)))
		वापस -1;

	अगर (tlbsel == 1 && kvmppc_need_recalc_tlb1map_range(vcpu_e500, gtlbe))
		kvmppc_recalc_tlb1map_range(vcpu_e500);

	gtlbe->mas1 = 0;

	वापस 0;
पूर्ण

पूर्णांक kvmppc_e500_emul_mt_mmucsr0(काष्ठा kvmppc_vcpu_e500 *vcpu_e500, uदीर्घ value)
अणु
	पूर्णांक esel;

	अगर (value & MMUCSR0_TLB0FI)
		क्रम (esel = 0; esel < vcpu_e500->gtlb_params[0].entries; esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, 0, esel);
	अगर (value & MMUCSR0_TLB1FI)
		क्रम (esel = 0; esel < vcpu_e500->gtlb_params[1].entries; esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, 1, esel);

	/* Invalidate all host shaकरोw mappings */
	kvmppc_core_flush_tlb(&vcpu_e500->vcpu);

	वापस EMULATE_DONE;
पूर्ण

पूर्णांक kvmppc_e500_emul_tlbivax(काष्ठा kvm_vcpu *vcpu, gva_t ea)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	अचिन्हित पूर्णांक ia;
	पूर्णांक esel, tlbsel;

	ia = (ea >> 2) & 0x1;

	/* since we only have two TLBs, only lower bit is used. */
	tlbsel = (ea >> 3) & 0x1;

	अगर (ia) अणु
		/* invalidate all entries */
		क्रम (esel = 0; esel < vcpu_e500->gtlb_params[tlbsel].entries;
		     esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, tlbsel, esel);
	पूर्ण अन्यथा अणु
		ea &= 0xfffff000;
		esel = kvmppc_e500_tlb_index(vcpu_e500, ea, tlbsel,
				get_cur_pid(vcpu), -1);
		अगर (esel >= 0)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, tlbsel, esel);
	पूर्ण

	/* Invalidate all host shaकरोw mappings */
	kvmppc_core_flush_tlb(&vcpu_e500->vcpu);

	वापस EMULATE_DONE;
पूर्ण

अटल व्योम tlbilx_all(काष्ठा kvmppc_vcpu_e500 *vcpu_e500, पूर्णांक tlbsel,
		       पूर्णांक pid, पूर्णांक type)
अणु
	काष्ठा kvm_book3e_206_tlb_entry *tlbe;
	पूर्णांक tid, esel;

	/* invalidate all entries */
	क्रम (esel = 0; esel < vcpu_e500->gtlb_params[tlbsel].entries; esel++) अणु
		tlbe = get_entry(vcpu_e500, tlbsel, esel);
		tid = get_tlb_tid(tlbe);
		अगर (type == 0 || tid == pid) अणु
			inval_gtlbe_on_host(vcpu_e500, tlbsel, esel);
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, tlbsel, esel);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tlbilx_one(काष्ठा kvmppc_vcpu_e500 *vcpu_e500, पूर्णांक pid,
		       gva_t ea)
अणु
	पूर्णांक tlbsel, esel;

	क्रम (tlbsel = 0; tlbsel < 2; tlbsel++) अणु
		esel = kvmppc_e500_tlb_index(vcpu_e500, ea, tlbsel, pid, -1);
		अगर (esel >= 0) अणु
			inval_gtlbe_on_host(vcpu_e500, tlbsel, esel);
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, tlbsel, esel);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक kvmppc_e500_emul_tlbilx(काष्ठा kvm_vcpu *vcpu, पूर्णांक type, gva_t ea)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक pid = get_cur_spid(vcpu);

	अगर (type == 0 || type == 1) अणु
		tlbilx_all(vcpu_e500, 0, pid, type);
		tlbilx_all(vcpu_e500, 1, pid, type);
	पूर्ण अन्यथा अगर (type == 3) अणु
		tlbilx_one(vcpu_e500, pid, ea);
	पूर्ण

	वापस EMULATE_DONE;
पूर्ण

पूर्णांक kvmppc_e500_emul_tlbre(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक tlbsel, esel;
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe;

	tlbsel = get_tlb_tlbsel(vcpu);
	esel = get_tlb_esel(vcpu, tlbsel);

	gtlbe = get_entry(vcpu_e500, tlbsel, esel);
	vcpu->arch.shared->mas0 &= ~MAS0_NV(~0);
	vcpu->arch.shared->mas0 |= MAS0_NV(vcpu_e500->gtlb_nv[tlbsel]);
	vcpu->arch.shared->mas1 = gtlbe->mas1;
	vcpu->arch.shared->mas2 = gtlbe->mas2;
	vcpu->arch.shared->mas7_3 = gtlbe->mas7_3;

	वापस EMULATE_DONE;
पूर्ण

पूर्णांक kvmppc_e500_emul_tlbsx(काष्ठा kvm_vcpu *vcpu, gva_t ea)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक as = !!get_cur_sas(vcpu);
	अचिन्हित पूर्णांक pid = get_cur_spid(vcpu);
	पूर्णांक esel, tlbsel;
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe = शून्य;

	क्रम (tlbsel = 0; tlbsel < 2; tlbsel++) अणु
		esel = kvmppc_e500_tlb_index(vcpu_e500, ea, tlbsel, pid, as);
		अगर (esel >= 0) अणु
			gtlbe = get_entry(vcpu_e500, tlbsel, esel);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (gtlbe) अणु
		esel &= vcpu_e500->gtlb_params[tlbsel].ways - 1;

		vcpu->arch.shared->mas0 = MAS0_TLBSEL(tlbsel) | MAS0_ESEL(esel)
			| MAS0_NV(vcpu_e500->gtlb_nv[tlbsel]);
		vcpu->arch.shared->mas1 = gtlbe->mas1;
		vcpu->arch.shared->mas2 = gtlbe->mas2;
		vcpu->arch.shared->mas7_3 = gtlbe->mas7_3;
	पूर्ण अन्यथा अणु
		पूर्णांक victim;

		/* since we only have two TLBs, only lower bit is used. */
		tlbsel = vcpu->arch.shared->mas4 >> 28 & 0x1;
		victim = (tlbsel == 0) ? gtlb0_get_next_victim(vcpu_e500) : 0;

		vcpu->arch.shared->mas0 = MAS0_TLBSEL(tlbsel)
			| MAS0_ESEL(victim)
			| MAS0_NV(vcpu_e500->gtlb_nv[tlbsel]);
		vcpu->arch.shared->mas1 =
			  (vcpu->arch.shared->mas6 & MAS6_SPID0)
			| ((vcpu->arch.shared->mas6 & MAS6_SAS) ? MAS1_TS : 0)
			| (vcpu->arch.shared->mas4 & MAS4_TSIZED(~0));
		vcpu->arch.shared->mas2 &= MAS2_EPN;
		vcpu->arch.shared->mas2 |= vcpu->arch.shared->mas4 &
					   MAS2_ATTRIB_MASK;
		vcpu->arch.shared->mas7_3 &= MAS3_U0 | MAS3_U1 |
					     MAS3_U2 | MAS3_U3;
	पूर्ण

	kvmppc_set_निकास_type(vcpu, EMULATED_TLBSX_EXITS);
	वापस EMULATE_DONE;
पूर्ण

पूर्णांक kvmppc_e500_emul_tlbwe(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe;
	पूर्णांक tlbsel, esel;
	पूर्णांक recal = 0;
	पूर्णांक idx;

	tlbsel = get_tlb_tlbsel(vcpu);
	esel = get_tlb_esel(vcpu, tlbsel);

	gtlbe = get_entry(vcpu_e500, tlbsel, esel);

	अगर (get_tlb_v(gtlbe)) अणु
		inval_gtlbe_on_host(vcpu_e500, tlbsel, esel);
		अगर ((tlbsel == 1) &&
			kvmppc_need_recalc_tlb1map_range(vcpu_e500, gtlbe))
			recal = 1;
	पूर्ण

	gtlbe->mas1 = vcpu->arch.shared->mas1;
	gtlbe->mas2 = vcpu->arch.shared->mas2;
	अगर (!(vcpu->arch.shared->msr & MSR_CM))
		gtlbe->mas2 &= 0xffffffffUL;
	gtlbe->mas7_3 = vcpu->arch.shared->mas7_3;

	trace_kvm_booke206_gtlb_ग_लिखो(vcpu->arch.shared->mas0, gtlbe->mas1,
	                              gtlbe->mas2, gtlbe->mas7_3);

	अगर (tlbsel == 1) अणु
		/*
		 * If a valid tlb1 entry is overwritten then recalculate the
		 * min/max TLB1 map address range otherwise no need to look
		 * in tlb1 array.
		 */
		अगर (recal)
			kvmppc_recalc_tlb1map_range(vcpu_e500);
		अन्यथा
			kvmppc_set_tlb1map_range(vcpu, gtlbe);
	पूर्ण

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	/* Invalidate shaकरोw mappings क्रम the about-to-be-clobbered TLBE. */
	अगर (tlbe_is_host_safe(vcpu, gtlbe)) अणु
		u64 eaddr = get_tlb_eaddr(gtlbe);
		u64 raddr = get_tlb_raddr(gtlbe);

		अगर (tlbsel == 0) अणु
			gtlbe->mas1 &= ~MAS1_TSIZE(~0);
			gtlbe->mas1 |= MAS1_TSIZE(BOOK3E_PAGESZ_4K);
		पूर्ण

		/* Premap the faulting page */
		kvmppc_mmu_map(vcpu, eaddr, raddr, index_of(tlbsel, esel));
	पूर्ण

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

	kvmppc_set_निकास_type(vcpu, EMULATED_TLBWE_EXITS);
	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_e500_tlb_search(काष्ठा kvm_vcpu *vcpu,
				  gva_t eaddr, अचिन्हित पूर्णांक pid, पूर्णांक as)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	पूर्णांक esel, tlbsel;

	क्रम (tlbsel = 0; tlbsel < 2; tlbsel++) अणु
		esel = kvmppc_e500_tlb_index(vcpu_e500, eaddr, tlbsel, pid, as);
		अगर (esel >= 0)
			वापस index_of(tlbsel, esel);
	पूर्ण

	वापस -1;
पूर्ण

/* 'linear_address' is actually an encoding of AS|PID|EADDR . */
पूर्णांक kvmppc_core_vcpu_translate(काष्ठा kvm_vcpu *vcpu,
                               काष्ठा kvm_translation *tr)
अणु
	पूर्णांक index;
	gva_t eaddr;
	u8 pid;
	u8 as;

	eaddr = tr->linear_address;
	pid = (tr->linear_address >> 32) & 0xff;
	as = (tr->linear_address >> 40) & 0x1;

	index = kvmppc_e500_tlb_search(vcpu, eaddr, pid, as);
	अगर (index < 0) अणु
		tr->valid = 0;
		वापस 0;
	पूर्ण

	tr->physical_address = kvmppc_mmu_xlate(vcpu, index, eaddr);
	/* XXX what करोes "writeable" and "usermode" even mean? */
	tr->valid = 1;

	वापस 0;
पूर्ण


पूर्णांक kvmppc_mmu_itlb_index(काष्ठा kvm_vcpu *vcpu, gva_t eaddr)
अणु
	अचिन्हित पूर्णांक as = !!(vcpu->arch.shared->msr & MSR_IS);

	वापस kvmppc_e500_tlb_search(vcpu, eaddr, get_cur_pid(vcpu), as);
पूर्ण

पूर्णांक kvmppc_mmu_dtlb_index(काष्ठा kvm_vcpu *vcpu, gva_t eaddr)
अणु
	अचिन्हित पूर्णांक as = !!(vcpu->arch.shared->msr & MSR_DS);

	वापस kvmppc_e500_tlb_search(vcpu, eaddr, get_cur_pid(vcpu), as);
पूर्ण

व्योम kvmppc_mmu_itlb_miss(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक as = !!(vcpu->arch.shared->msr & MSR_IS);

	kvmppc_e500_deliver_tlb_miss(vcpu, vcpu->arch.regs.nip, as);
पूर्ण

व्योम kvmppc_mmu_dtlb_miss(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक as = !!(vcpu->arch.shared->msr & MSR_DS);

	kvmppc_e500_deliver_tlb_miss(vcpu, vcpu->arch.fault_dear, as);
पूर्ण

gpa_t kvmppc_mmu_xlate(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक index,
			gva_t eaddr)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe;
	u64 pgmask;

	gtlbe = get_entry(vcpu_e500, tlbsel_of(index), esel_of(index));
	pgmask = get_tlb_bytes(gtlbe) - 1;

	वापस get_tlb_raddr(gtlbe) | (eaddr & pgmask);
पूर्ण

/*****************************************/

अटल व्योम मुक्त_gtlb(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	पूर्णांक i;

	kvmppc_core_flush_tlb(&vcpu_e500->vcpu);
	kमुक्त(vcpu_e500->g2h_tlb1_map);
	kमुक्त(vcpu_e500->gtlb_priv[0]);
	kमुक्त(vcpu_e500->gtlb_priv[1]);

	अगर (vcpu_e500->shared_tlb_pages) अणु
		vमुक्त((व्योम *)(round_करोwn((uपूर्णांकptr_t)vcpu_e500->gtlb_arch,
					  PAGE_SIZE)));

		क्रम (i = 0; i < vcpu_e500->num_shared_tlb_pages; i++) अणु
			set_page_dirty_lock(vcpu_e500->shared_tlb_pages[i]);
			put_page(vcpu_e500->shared_tlb_pages[i]);
		पूर्ण

		vcpu_e500->num_shared_tlb_pages = 0;

		kमुक्त(vcpu_e500->shared_tlb_pages);
		vcpu_e500->shared_tlb_pages = शून्य;
	पूर्ण अन्यथा अणु
		kमुक्त(vcpu_e500->gtlb_arch);
	पूर्ण

	vcpu_e500->gtlb_arch = शून्य;
पूर्ण

व्योम kvmppc_get_sregs_e500_tlb(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs)
अणु
	sregs->u.e.mas0 = vcpu->arch.shared->mas0;
	sregs->u.e.mas1 = vcpu->arch.shared->mas1;
	sregs->u.e.mas2 = vcpu->arch.shared->mas2;
	sregs->u.e.mas7_3 = vcpu->arch.shared->mas7_3;
	sregs->u.e.mas4 = vcpu->arch.shared->mas4;
	sregs->u.e.mas6 = vcpu->arch.shared->mas6;

	sregs->u.e.mmucfg = vcpu->arch.mmucfg;
	sregs->u.e.tlbcfg[0] = vcpu->arch.tlbcfg[0];
	sregs->u.e.tlbcfg[1] = vcpu->arch.tlbcfg[1];
	sregs->u.e.tlbcfg[2] = 0;
	sregs->u.e.tlbcfg[3] = 0;
पूर्ण

पूर्णांक kvmppc_set_sregs_e500_tlb(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs)
अणु
	अगर (sregs->u.e.features & KVM_SREGS_E_ARCH206_MMU) अणु
		vcpu->arch.shared->mas0 = sregs->u.e.mas0;
		vcpu->arch.shared->mas1 = sregs->u.e.mas1;
		vcpu->arch.shared->mas2 = sregs->u.e.mas2;
		vcpu->arch.shared->mas7_3 = sregs->u.e.mas7_3;
		vcpu->arch.shared->mas4 = sregs->u.e.mas4;
		vcpu->arch.shared->mas6 = sregs->u.e.mas6;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kvmppc_get_one_reg_e500_tlb(काष्ठा kvm_vcpu *vcpu, u64 id,
				जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;
	दीर्घ पूर्णांक i;

	चयन (id) अणु
	हाल KVM_REG_PPC_MAS0:
		*val = get_reg_val(id, vcpu->arch.shared->mas0);
		अवरोध;
	हाल KVM_REG_PPC_MAS1:
		*val = get_reg_val(id, vcpu->arch.shared->mas1);
		अवरोध;
	हाल KVM_REG_PPC_MAS2:
		*val = get_reg_val(id, vcpu->arch.shared->mas2);
		अवरोध;
	हाल KVM_REG_PPC_MAS7_3:
		*val = get_reg_val(id, vcpu->arch.shared->mas7_3);
		अवरोध;
	हाल KVM_REG_PPC_MAS4:
		*val = get_reg_val(id, vcpu->arch.shared->mas4);
		अवरोध;
	हाल KVM_REG_PPC_MAS6:
		*val = get_reg_val(id, vcpu->arch.shared->mas6);
		अवरोध;
	हाल KVM_REG_PPC_MMUCFG:
		*val = get_reg_val(id, vcpu->arch.mmucfg);
		अवरोध;
	हाल KVM_REG_PPC_EPTCFG:
		*val = get_reg_val(id, vcpu->arch.eptcfg);
		अवरोध;
	हाल KVM_REG_PPC_TLB0CFG:
	हाल KVM_REG_PPC_TLB1CFG:
	हाल KVM_REG_PPC_TLB2CFG:
	हाल KVM_REG_PPC_TLB3CFG:
		i = id - KVM_REG_PPC_TLB0CFG;
		*val = get_reg_val(id, vcpu->arch.tlbcfg[i]);
		अवरोध;
	हाल KVM_REG_PPC_TLB0PS:
	हाल KVM_REG_PPC_TLB1PS:
	हाल KVM_REG_PPC_TLB2PS:
	हाल KVM_REG_PPC_TLB3PS:
		i = id - KVM_REG_PPC_TLB0PS;
		*val = get_reg_val(id, vcpu->arch.tlbps[i]);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvmppc_set_one_reg_e500_tlb(काष्ठा kvm_vcpu *vcpu, u64 id,
			       जोड़ kvmppc_one_reg *val)
अणु
	पूर्णांक r = 0;
	दीर्घ पूर्णांक i;

	चयन (id) अणु
	हाल KVM_REG_PPC_MAS0:
		vcpu->arch.shared->mas0 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MAS1:
		vcpu->arch.shared->mas1 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MAS2:
		vcpu->arch.shared->mas2 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MAS7_3:
		vcpu->arch.shared->mas7_3 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MAS4:
		vcpu->arch.shared->mas4 = set_reg_val(id, *val);
		अवरोध;
	हाल KVM_REG_PPC_MAS6:
		vcpu->arch.shared->mas6 = set_reg_val(id, *val);
		अवरोध;
	/* Only allow MMU रेजिस्टरs to be set to the config supported by KVM */
	हाल KVM_REG_PPC_MMUCFG: अणु
		u32 reg = set_reg_val(id, *val);
		अगर (reg != vcpu->arch.mmucfg)
			r = -EINVAL;
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_EPTCFG: अणु
		u32 reg = set_reg_val(id, *val);
		अगर (reg != vcpu->arch.eptcfg)
			r = -EINVAL;
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TLB0CFG:
	हाल KVM_REG_PPC_TLB1CFG:
	हाल KVM_REG_PPC_TLB2CFG:
	हाल KVM_REG_PPC_TLB3CFG: अणु
		/* MMU geometry (N_ENTRY/ASSOC) can be set only using SW_TLB */
		u32 reg = set_reg_val(id, *val);
		i = id - KVM_REG_PPC_TLB0CFG;
		अगर (reg != vcpu->arch.tlbcfg[i])
			r = -EINVAL;
		अवरोध;
	पूर्ण
	हाल KVM_REG_PPC_TLB0PS:
	हाल KVM_REG_PPC_TLB1PS:
	हाल KVM_REG_PPC_TLB2PS:
	हाल KVM_REG_PPC_TLB3PS: अणु
		u32 reg = set_reg_val(id, *val);
		i = id - KVM_REG_PPC_TLB0PS;
		अगर (reg != vcpu->arch.tlbps[i])
			r = -EINVAL;
		अवरोध;
	पूर्ण
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक vcpu_mmu_geometry_update(काष्ठा kvm_vcpu *vcpu,
		काष्ठा kvm_book3e_206_tlb_params *params)
अणु
	vcpu->arch.tlbcfg[0] &= ~(TLBnCFG_N_ENTRY | TLBnCFG_ASSOC);
	अगर (params->tlb_sizes[0] <= 2048)
		vcpu->arch.tlbcfg[0] |= params->tlb_sizes[0];
	vcpu->arch.tlbcfg[0] |= params->tlb_ways[0] << TLBnCFG_ASSOC_SHIFT;

	vcpu->arch.tlbcfg[1] &= ~(TLBnCFG_N_ENTRY | TLBnCFG_ASSOC);
	vcpu->arch.tlbcfg[1] |= params->tlb_sizes[1];
	vcpu->arch.tlbcfg[1] |= params->tlb_ways[1] << TLBnCFG_ASSOC_SHIFT;
	वापस 0;
पूर्ण

पूर्णांक kvm_vcpu_ioctl_config_tlb(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_config_tlb *cfg)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	काष्ठा kvm_book3e_206_tlb_params params;
	अक्षर *virt;
	काष्ठा page **pages;
	काष्ठा tlbe_priv *privs[2] = अणुपूर्ण;
	u64 *g2h_biपंचांगap;
	माप_प्रकार array_len;
	u32 sets;
	पूर्णांक num_pages, ret, i;

	अगर (cfg->mmu_type != KVM_MMU_FSL_BOOKE_NOHV)
		वापस -EINVAL;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)cfg->params,
			   माप(params)))
		वापस -EFAULT;

	अगर (params.tlb_sizes[1] > 64)
		वापस -EINVAL;
	अगर (params.tlb_ways[1] != params.tlb_sizes[1])
		वापस -EINVAL;
	अगर (params.tlb_sizes[2] != 0 || params.tlb_sizes[3] != 0)
		वापस -EINVAL;
	अगर (params.tlb_ways[2] != 0 || params.tlb_ways[3] != 0)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(params.tlb_ways[0]))
		वापस -EINVAL;

	sets = params.tlb_sizes[0] >> ilog2(params.tlb_ways[0]);
	अगर (!is_घातer_of_2(sets))
		वापस -EINVAL;

	array_len = params.tlb_sizes[0] + params.tlb_sizes[1];
	array_len *= माप(काष्ठा kvm_book3e_206_tlb_entry);

	अगर (cfg->array_len < array_len)
		वापस -EINVAL;

	num_pages = DIV_ROUND_UP(cfg->array + array_len - 1, PAGE_SIZE) -
		    cfg->array / PAGE_SIZE;
	pages = kदो_स्मृति_array(num_pages, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	ret = get_user_pages_fast(cfg->array, num_pages, FOLL_WRITE, pages);
	अगर (ret < 0)
		जाओ मुक्त_pages;

	अगर (ret != num_pages) अणु
		num_pages = ret;
		ret = -EFAULT;
		जाओ put_pages;
	पूर्ण

	virt = vmap(pages, num_pages, VM_MAP, PAGE_KERNEL);
	अगर (!virt) अणु
		ret = -ENOMEM;
		जाओ put_pages;
	पूर्ण

	privs[0] = kसुस्मृति(params.tlb_sizes[0], माप(*privs[0]), GFP_KERNEL);
	अगर (!privs[0]) अणु
		ret = -ENOMEM;
		जाओ put_pages;
	पूर्ण

	privs[1] = kसुस्मृति(params.tlb_sizes[1], माप(*privs[1]), GFP_KERNEL);
	अगर (!privs[1]) अणु
		ret = -ENOMEM;
		जाओ मुक्त_privs_first;
	पूर्ण

	g2h_biपंचांगap = kसुस्मृति(params.tlb_sizes[1],
			     माप(*g2h_biपंचांगap),
			     GFP_KERNEL);
	अगर (!g2h_biपंचांगap) अणु
		ret = -ENOMEM;
		जाओ मुक्त_privs_second;
	पूर्ण

	मुक्त_gtlb(vcpu_e500);

	vcpu_e500->gtlb_priv[0] = privs[0];
	vcpu_e500->gtlb_priv[1] = privs[1];
	vcpu_e500->g2h_tlb1_map = g2h_biपंचांगap;

	vcpu_e500->gtlb_arch = (काष्ठा kvm_book3e_206_tlb_entry *)
		(virt + (cfg->array & (PAGE_SIZE - 1)));

	vcpu_e500->gtlb_params[0].entries = params.tlb_sizes[0];
	vcpu_e500->gtlb_params[1].entries = params.tlb_sizes[1];

	vcpu_e500->gtlb_offset[0] = 0;
	vcpu_e500->gtlb_offset[1] = params.tlb_sizes[0];

	/* Update vcpu's MMU geometry based on SW_TLB input */
	vcpu_mmu_geometry_update(vcpu, &params);

	vcpu_e500->shared_tlb_pages = pages;
	vcpu_e500->num_shared_tlb_pages = num_pages;

	vcpu_e500->gtlb_params[0].ways = params.tlb_ways[0];
	vcpu_e500->gtlb_params[0].sets = sets;

	vcpu_e500->gtlb_params[1].ways = params.tlb_sizes[1];
	vcpu_e500->gtlb_params[1].sets = 1;

	kvmppc_recalc_tlb1map_range(vcpu_e500);
	वापस 0;
 मुक्त_privs_second:
	kमुक्त(privs[1]);
 मुक्त_privs_first:
	kमुक्त(privs[0]);
 put_pages:
	क्रम (i = 0; i < num_pages; i++)
		put_page(pages[i]);
 मुक्त_pages:
	kमुक्त(pages);
	वापस ret;
पूर्ण

पूर्णांक kvm_vcpu_ioctl_dirty_tlb(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा kvm_dirty_tlb *dirty)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	kvmppc_recalc_tlb1map_range(vcpu_e500);
	kvmppc_core_flush_tlb(vcpu);
	वापस 0;
पूर्ण

/* Vcpu's MMU शेष configuration */
अटल पूर्णांक vcpu_mmu_init(काष्ठा kvm_vcpu *vcpu,
		       काष्ठा kvmppc_e500_tlb_params *params)
अणु
	/* Initialize RASIZE, PIDSIZE, NTLBS and MAVN fields with host values*/
	vcpu->arch.mmucfg = mfspr(SPRN_MMUCFG) & ~MMUCFG_LPIDSIZE;

	/* Initialize TLBnCFG fields with host values and SW_TLB geometry*/
	vcpu->arch.tlbcfg[0] = mfspr(SPRN_TLB0CFG) &
			     ~(TLBnCFG_N_ENTRY | TLBnCFG_ASSOC);
	vcpu->arch.tlbcfg[0] |= params[0].entries;
	vcpu->arch.tlbcfg[0] |= params[0].ways << TLBnCFG_ASSOC_SHIFT;

	vcpu->arch.tlbcfg[1] = mfspr(SPRN_TLB1CFG) &
			     ~(TLBnCFG_N_ENTRY | TLBnCFG_ASSOC);
	vcpu->arch.tlbcfg[1] |= params[1].entries;
	vcpu->arch.tlbcfg[1] |= params[1].ways << TLBnCFG_ASSOC_SHIFT;

	अगर (has_feature(vcpu, VCPU_FTR_MMU_V2)) अणु
		vcpu->arch.tlbps[0] = mfspr(SPRN_TLB0PS);
		vcpu->arch.tlbps[1] = mfspr(SPRN_TLB1PS);

		vcpu->arch.mmucfg &= ~MMUCFG_LRAT;

		/* Guest mmu emulation currently करोesn't handle E.PT */
		vcpu->arch.eptcfg = 0;
		vcpu->arch.tlbcfg[0] &= ~TLBnCFG_PT;
		vcpu->arch.tlbcfg[1] &= ~TLBnCFG_IND;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kvmppc_e500_tlb_init(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	काष्ठा kvm_vcpu *vcpu = &vcpu_e500->vcpu;

	अगर (e500_mmu_host_init(vcpu_e500))
		जाओ मुक्त_vcpu;

	vcpu_e500->gtlb_params[0].entries = KVM_E500_TLB0_SIZE;
	vcpu_e500->gtlb_params[1].entries = KVM_E500_TLB1_SIZE;

	vcpu_e500->gtlb_params[0].ways = KVM_E500_TLB0_WAY_NUM;
	vcpu_e500->gtlb_params[0].sets =
		KVM_E500_TLB0_SIZE / KVM_E500_TLB0_WAY_NUM;

	vcpu_e500->gtlb_params[1].ways = KVM_E500_TLB1_SIZE;
	vcpu_e500->gtlb_params[1].sets = 1;

	vcpu_e500->gtlb_arch = kदो_स्मृति_array(KVM_E500_TLB0_SIZE +
					     KVM_E500_TLB1_SIZE,
					     माप(*vcpu_e500->gtlb_arch),
					     GFP_KERNEL);
	अगर (!vcpu_e500->gtlb_arch)
		वापस -ENOMEM;

	vcpu_e500->gtlb_offset[0] = 0;
	vcpu_e500->gtlb_offset[1] = KVM_E500_TLB0_SIZE;

	vcpu_e500->gtlb_priv[0] = kसुस्मृति(vcpu_e500->gtlb_params[0].entries,
					  माप(काष्ठा tlbe_ref),
					  GFP_KERNEL);
	अगर (!vcpu_e500->gtlb_priv[0])
		जाओ मुक्त_vcpu;

	vcpu_e500->gtlb_priv[1] = kसुस्मृति(vcpu_e500->gtlb_params[1].entries,
					  माप(काष्ठा tlbe_ref),
					  GFP_KERNEL);
	अगर (!vcpu_e500->gtlb_priv[1])
		जाओ मुक्त_vcpu;

	vcpu_e500->g2h_tlb1_map = kसुस्मृति(vcpu_e500->gtlb_params[1].entries,
					  माप(*vcpu_e500->g2h_tlb1_map),
					  GFP_KERNEL);
	अगर (!vcpu_e500->g2h_tlb1_map)
		जाओ मुक्त_vcpu;

	vcpu_mmu_init(vcpu, vcpu_e500->gtlb_params);

	kvmppc_recalc_tlb1map_range(vcpu_e500);
	वापस 0;
 मुक्त_vcpu:
	मुक्त_gtlb(vcpu_e500);
	वापस -1;
पूर्ण

व्योम kvmppc_e500_tlb_uninit(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	मुक्त_gtlb(vcpu_e500);
	e500_mmu_host_uninit(vcpu_e500);
पूर्ण
