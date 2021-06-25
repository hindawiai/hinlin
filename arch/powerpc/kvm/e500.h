<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008-2011 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Yu Liu <yu.liu@मुक्तscale.com>
 *         Scott Wood <scottwood@मुक्तscale.com>
 *         Ashish Kalra <ashish.kalra@मुक्तscale.com>
 *         Varun Sethi <varun.sethi@मुक्तscale.com>
 *
 * Description:
 * This file is based on arch/घातerpc/kvm/44x_tlb.h and
 * arch/घातerpc/include/यंत्र/kvm_44x.h by Hollis Blanअक्षरd <hollisb@us.ibm.com>,
 * Copyright IBM Corp. 2007-2008
 */

#अगर_अघोषित KVM_E500_H
#घोषणा KVM_E500_H

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/nohash/mmu-book3e.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cputhपढ़ोs.h>

क्रमागत vcpu_ftr अणु
	VCPU_FTR_MMU_V2
पूर्ण;

#घोषणा E500_PID_NUM   3
#घोषणा E500_TLB_NUM   2

/* entry is mapped somewhere in host TLB */
#घोषणा E500_TLB_VALID		(1 << 31)
/* TLB1 entry is mapped by host TLB1, tracked by biपंचांगaps */
#घोषणा E500_TLB_BITMAP		(1 << 30)
/* TLB1 entry is mapped by host TLB0 */
#घोषणा E500_TLB_TLB0		(1 << 29)
/* bits [6-5] MAS2_X1 and MAS2_X0 and [4-0] bits क्रम WIMGE */
#घोषणा E500_TLB_MAS2_ATTR	(0x7f)

काष्ठा tlbe_ref अणु
	kvm_pfn_t pfn;		/* valid only क्रम TLB0, except briefly */
	अचिन्हित पूर्णांक flags;	/* E500_TLB_* */
पूर्ण;

काष्ठा tlbe_priv अणु
	काष्ठा tlbe_ref ref;
पूर्ण;

#अगर_घोषित CONFIG_KVM_E500V2
काष्ठा vcpu_id_table;
#पूर्ण_अगर

काष्ठा kvmppc_e500_tlb_params अणु
	पूर्णांक entries, ways, sets;
पूर्ण;

काष्ठा kvmppc_vcpu_e500 अणु
	काष्ठा kvm_vcpu vcpu;

	/* Unmodअगरied copy of the guest's TLB -- shared with host userspace. */
	काष्ठा kvm_book3e_206_tlb_entry *gtlb_arch;

	/* Starting entry number in gtlb_arch[] */
	पूर्णांक gtlb_offset[E500_TLB_NUM];

	/* KVM पूर्णांकernal inक्रमmation associated with each guest TLB entry */
	काष्ठा tlbe_priv *gtlb_priv[E500_TLB_NUM];

	काष्ठा kvmppc_e500_tlb_params gtlb_params[E500_TLB_NUM];

	अचिन्हित पूर्णांक gtlb_nv[E500_TLB_NUM];

	अचिन्हित पूर्णांक host_tlb1_nv;

	u32 svr;
	u32 l1csr0;
	u32 l1csr1;
	u32 hid0;
	u32 hid1;
	u64 mcar;

	काष्ठा page **shared_tlb_pages;
	पूर्णांक num_shared_tlb_pages;

	u64 *g2h_tlb1_map;
	अचिन्हित पूर्णांक *h2g_tlb1_rmap;

	/* Minimum and maximum address mapped my TLB1 */
	अचिन्हित दीर्घ tlb1_min_eaddr;
	अचिन्हित दीर्घ tlb1_max_eaddr;

#अगर_घोषित CONFIG_KVM_E500V2
	u32 pid[E500_PID_NUM];

	/* vcpu id table */
	काष्ठा vcpu_id_table *idt;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा kvmppc_vcpu_e500 *to_e500(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस container_of(vcpu, काष्ठा kvmppc_vcpu_e500, vcpu);
पूर्ण


/* This geometry is the legacy शेष -- can be overridden by userspace */
#घोषणा KVM_E500_TLB0_WAY_SIZE		128
#घोषणा KVM_E500_TLB0_WAY_NUM		2

#घोषणा KVM_E500_TLB0_SIZE  (KVM_E500_TLB0_WAY_SIZE * KVM_E500_TLB0_WAY_NUM)
#घोषणा KVM_E500_TLB1_SIZE  16

#घोषणा index_of(tlbsel, esel)	(((tlbsel) << 16) | ((esel) & 0xFFFF))
#घोषणा tlbsel_of(index)	((index) >> 16)
#घोषणा esel_of(index)		((index) & 0xFFFF)

#घोषणा E500_TLB_USER_PERM_MASK (MAS3_UX|MAS3_UR|MAS3_UW)
#घोषणा E500_TLB_SUPER_PERM_MASK (MAS3_SX|MAS3_SR|MAS3_SW)
#घोषणा MAS2_ATTRIB_MASK \
	  (MAS2_X0 | MAS2_X1 | MAS2_E | MAS2_G)
#घोषणा MAS3_ATTRIB_MASK \
	  (MAS3_U0 | MAS3_U1 | MAS3_U2 | MAS3_U3 \
	   | E500_TLB_USER_PERM_MASK | E500_TLB_SUPER_PERM_MASK)

पूर्णांक kvmppc_e500_emul_mt_mmucsr0(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
				uदीर्घ value);
पूर्णांक kvmppc_e500_emul_tlbwe(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvmppc_e500_emul_tlbre(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvmppc_e500_emul_tlbivax(काष्ठा kvm_vcpu *vcpu, gva_t ea);
पूर्णांक kvmppc_e500_emul_tlbilx(काष्ठा kvm_vcpu *vcpu, पूर्णांक type, gva_t ea);
पूर्णांक kvmppc_e500_emul_tlbsx(काष्ठा kvm_vcpu *vcpu, gva_t ea);
पूर्णांक kvmppc_e500_tlb_init(काष्ठा kvmppc_vcpu_e500 *vcpu_e500);
व्योम kvmppc_e500_tlb_uninit(काष्ठा kvmppc_vcpu_e500 *vcpu_e500);

व्योम kvmppc_get_sregs_e500_tlb(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);
पूर्णांक kvmppc_set_sregs_e500_tlb(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);

पूर्णांक kvmppc_get_one_reg_e500_tlb(काष्ठा kvm_vcpu *vcpu, u64 id,
				जोड़ kvmppc_one_reg *val);
पूर्णांक kvmppc_set_one_reg_e500_tlb(काष्ठा kvm_vcpu *vcpu, u64 id,
			       जोड़ kvmppc_one_reg *val);

#अगर_घोषित CONFIG_KVM_E500V2
अचिन्हित पूर्णांक kvmppc_e500_get_sid(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
				 अचिन्हित पूर्णांक as, अचिन्हित पूर्णांक gid,
				 अचिन्हित पूर्णांक pr, पूर्णांक aव्योम_recursion);
#पूर्ण_अगर

/* TLB helper functions */
अटल अंतरभूत अचिन्हित पूर्णांक
get_tlb_size(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस (tlbe->mas1 >> 7) & 0x1f;
पूर्ण

अटल अंतरभूत gva_t get_tlb_eaddr(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस tlbe->mas2 & MAS2_EPN;
पूर्ण

अटल अंतरभूत u64 get_tlb_bytes(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	अचिन्हित पूर्णांक pgsize = get_tlb_size(tlbe);
	वापस 1ULL << 10 << pgsize;
पूर्ण

अटल अंतरभूत gva_t get_tlb_end(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	u64 bytes = get_tlb_bytes(tlbe);
	वापस get_tlb_eaddr(tlbe) + bytes - 1;
पूर्ण

अटल अंतरभूत u64 get_tlb_raddr(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस tlbe->mas7_3 & ~0xfffULL;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
get_tlb_tid(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस (tlbe->mas1 >> 16) & 0xff;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
get_tlb_ts(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस (tlbe->mas1 >> 12) & 0x1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
get_tlb_v(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस (tlbe->mas1 >> 31) & 0x1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
get_tlb_iprot(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस (tlbe->mas1 >> 30) & 0x1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
get_tlb_tsize(स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस (tlbe->mas1 & MAS1_TSIZE_MASK) >> MAS1_TSIZE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_cur_pid(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.pid & 0xff;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_cur_as(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(vcpu->arch.shared->msr & (MSR_IS | MSR_DS));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_cur_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(vcpu->arch.shared->msr & MSR_PR);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_cur_spid(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (vcpu->arch.shared->mas6 >> 16) & 0xff;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_cur_sas(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.shared->mas6 & 0x1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_tlb_tlbsel(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * Manual says that tlbsel has 2 bits wide.
	 * Since we only have two TLBs, only lower bit is used.
	 */
	वापस (vcpu->arch.shared->mas0 >> 28) & 0x1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_tlb_nv_bit(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.shared->mas0 & 0xfff;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_tlb_esel_bit(स्थिर काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (vcpu->arch.shared->mas0 >> 16) & 0xfff;
पूर्ण

अटल अंतरभूत पूर्णांक tlbe_is_host_safe(स्थिर काष्ठा kvm_vcpu *vcpu,
			स्थिर काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	gpa_t gpa;

	अगर (!get_tlb_v(tlbe))
		वापस 0;

#अगर_अघोषित CONFIG_KVM_BOOKE_HV
	/* Does it match current guest AS? */
	/* XXX what about IS != DS? */
	अगर (get_tlb_ts(tlbe) != !!(vcpu->arch.shared->msr & MSR_IS))
		वापस 0;
#पूर्ण_अगर

	gpa = get_tlb_raddr(tlbe);
	अगर (!gfn_to_memslot(vcpu->kvm, gpa >> PAGE_SHIFT))
		/* Mapping is not क्रम RAM. */
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत काष्ठा kvm_book3e_206_tlb_entry *get_entry(
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500, पूर्णांक tlbsel, पूर्णांक entry)
अणु
	पूर्णांक offset = vcpu_e500->gtlb_offset[tlbsel];
	वापस &vcpu_e500->gtlb_arch[offset + entry];
पूर्ण

व्योम kvmppc_e500_tlbil_one(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
			   काष्ठा kvm_book3e_206_tlb_entry *gtlbe);
व्योम kvmppc_e500_tlbil_all(काष्ठा kvmppc_vcpu_e500 *vcpu_e500);

#अगर_घोषित CONFIG_KVM_BOOKE_HV
#घोषणा kvmppc_e500_get_tlb_stid(vcpu, gtlbe)       get_tlb_tid(gtlbe)
#घोषणा get_tlbmiss_tid(vcpu)           get_cur_pid(vcpu)
#घोषणा get_tlb_sts(gtlbe)              (gtlbe->mas1 & MAS1_TS)

/*
 * These functions should be called with preemption disabled
 * and the वापसed value is valid only in that context
 */
अटल अंतरभूत पूर्णांक get_thपढ़ो_specअगरic_lpid(पूर्णांक vm_lpid)
अणु
	पूर्णांक vcpu_lpid = vm_lpid;

	अगर (thपढ़ोs_per_core == 2)
		vcpu_lpid |= smp_processor_id() & 1;

	वापस vcpu_lpid;
पूर्ण

अटल अंतरभूत पूर्णांक get_lpid(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस get_thपढ़ो_specअगरic_lpid(vcpu->kvm->arch.lpid);
पूर्ण
#अन्यथा
अचिन्हित पूर्णांक kvmppc_e500_get_tlb_stid(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_book3e_206_tlb_entry *gtlbe);

अटल अंतरभूत अचिन्हित पूर्णांक get_tlbmiss_tid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	अचिन्हित पूर्णांक tidseld = (vcpu->arch.shared->mas4 >> 16) & 0xf;

	वापस vcpu_e500->pid[tidseld];
पूर्ण

/* Force TS=1 क्रम all guest mappings. */
#घोषणा get_tlb_sts(gtlbe)              (MAS1_TS)
#पूर्ण_अगर /* !BOOKE_HV */

अटल अंतरभूत bool has_feature(स्थिर काष्ठा kvm_vcpu *vcpu,
			       क्रमागत vcpu_ftr ftr)
अणु
	bool has_ftr;
	चयन (ftr) अणु
	हाल VCPU_FTR_MMU_V2:
		has_ftr = ((vcpu->arch.mmucfg & MMUCFG_MAVN) == MMUCFG_MAVN_V2);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस has_ftr;
पूर्ण

#पूर्ण_अगर /* KVM_E500_H */
