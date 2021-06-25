<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright SUSE Linux Products GmbH 2009
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/highस्मृति.स>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/book3s/64/mmu-hash.h>

/* #घोषणा DEBUG_MMU */

#अगर_घोषित DEBUG_MMU
#घोषणा dprपूर्णांकk(X...) prपूर्णांकk(KERN_INFO X)
#अन्यथा
#घोषणा dprपूर्णांकk(X...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल काष्ठा kvmppc_slb *kvmppc_mmu_book3s_64_find_slbe(
				काष्ठा kvm_vcpu *vcpu,
				gva_t eaddr)
अणु
	पूर्णांक i;
	u64 esid = GET_ESID(eaddr);
	u64 esid_1t = GET_ESID_1T(eaddr);

	क्रम (i = 0; i < vcpu->arch.slb_nr; i++) अणु
		u64 cmp_esid = esid;

		अगर (!vcpu->arch.slb[i].valid)
			जारी;

		अगर (vcpu->arch.slb[i].tb)
			cmp_esid = esid_1t;

		अगर (vcpu->arch.slb[i].esid == cmp_esid)
			वापस &vcpu->arch.slb[i];
	पूर्ण

	dprपूर्णांकk("KVM: No SLB entry found for 0x%lx [%llx | %llx]\n",
		eaddr, esid, esid_1t);
	क्रम (i = 0; i < vcpu->arch.slb_nr; i++) अणु
	    अगर (vcpu->arch.slb[i].vsid)
		dprपूर्णांकk("  %d: %c%c%c %llx %llx\n", i,
			vcpu->arch.slb[i].valid ? 'v' : ' ',
			vcpu->arch.slb[i].large ? 'l' : ' ',
			vcpu->arch.slb[i].tb    ? 't' : ' ',
			vcpu->arch.slb[i].esid,
			vcpu->arch.slb[i].vsid);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक kvmppc_slb_sid_shअगरt(काष्ठा kvmppc_slb *slbe)
अणु
	वापस slbe->tb ? SID_SHIFT_1T : SID_SHIFT;
पूर्ण

अटल u64 kvmppc_slb_offset_mask(काष्ठा kvmppc_slb *slbe)
अणु
	वापस (1ul << kvmppc_slb_sid_shअगरt(slbe)) - 1;
पूर्ण

अटल u64 kvmppc_slb_calc_vpn(काष्ठा kvmppc_slb *slb, gva_t eaddr)
अणु
	eaddr &= kvmppc_slb_offset_mask(slb);

	वापस (eaddr >> VPN_SHIFT) |
		((slb->vsid) << (kvmppc_slb_sid_shअगरt(slb) - VPN_SHIFT));
पूर्ण

अटल u64 kvmppc_mmu_book3s_64_ea_to_vp(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
					 bool data)
अणु
	काष्ठा kvmppc_slb *slb;

	slb = kvmppc_mmu_book3s_64_find_slbe(vcpu, eaddr);
	अगर (!slb)
		वापस 0;

	वापस kvmppc_slb_calc_vpn(slb, eaddr);
पूर्ण

अटल पूर्णांक mmu_pagesize(पूर्णांक mmu_pg)
अणु
	चयन (mmu_pg) अणु
	हाल MMU_PAGE_64K:
		वापस 16;
	हाल MMU_PAGE_16M:
		वापस 24;
	पूर्ण
	वापस 12;
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_64_get_pagesize(काष्ठा kvmppc_slb *slbe)
अणु
	वापस mmu_pagesize(slbe->base_page_size);
पूर्ण

अटल u32 kvmppc_mmu_book3s_64_get_page(काष्ठा kvmppc_slb *slbe, gva_t eaddr)
अणु
	पूर्णांक p = kvmppc_mmu_book3s_64_get_pagesize(slbe);

	वापस ((eaddr & kvmppc_slb_offset_mask(slbe)) >> p);
पूर्ण

अटल hva_t kvmppc_mmu_book3s_64_get_pteg(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvmppc_slb *slbe, gva_t eaddr,
				bool second)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u64 hash, pteg, htअसलize;
	u32 ssize;
	hva_t r;
	u64 vpn;

	htअसलize = ((1 << ((vcpu_book3s->sdr1 & 0x1f) + 11)) - 1);

	vpn = kvmppc_slb_calc_vpn(slbe, eaddr);
	ssize = slbe->tb ? MMU_SEGSIZE_1T : MMU_SEGSIZE_256M;
	hash = hpt_hash(vpn, kvmppc_mmu_book3s_64_get_pagesize(slbe), ssize);
	अगर (second)
		hash = ~hash;
	hash &= ((1ULL << 39ULL) - 1ULL);
	hash &= htअसलize;
	hash <<= 7ULL;

	pteg = vcpu_book3s->sdr1 & 0xfffffffffffc0000ULL;
	pteg |= hash;

	dprपूर्णांकk("MMU: page=0x%x sdr1=0x%llx pteg=0x%llx vsid=0x%llx\n",
		page, vcpu_book3s->sdr1, pteg, slbe->vsid);

	/* When running a PAPR guest, SDR1 contains a HVA address instead
           of a GPA */
	अगर (vcpu->arch.papr_enabled)
		r = pteg;
	अन्यथा
		r = gfn_to_hva(vcpu->kvm, pteg >> PAGE_SHIFT);

	अगर (kvm_is_error_hva(r))
		वापस r;
	वापस r | (pteg & ~PAGE_MASK);
पूर्ण

अटल u64 kvmppc_mmu_book3s_64_get_avpn(काष्ठा kvmppc_slb *slbe, gva_t eaddr)
अणु
	पूर्णांक p = kvmppc_mmu_book3s_64_get_pagesize(slbe);
	u64 avpn;

	avpn = kvmppc_mmu_book3s_64_get_page(slbe, eaddr);
	avpn |= slbe->vsid << (kvmppc_slb_sid_shअगरt(slbe) - p);

	अगर (p < 16)
		avpn >>= ((80 - p) - 56) - 8;	/* 16 - p */
	अन्यथा
		avpn <<= p - 16;

	वापस avpn;
पूर्ण

/*
 * Return page size encoded in the second word of a HPTE, or
 * -1 क्रम an invalid encoding क्रम the base page size indicated by
 * the SLB entry.  This करोesn't handle mixed pagesize segments yet.
 */
अटल पूर्णांक decode_pagesize(काष्ठा kvmppc_slb *slbe, u64 r)
अणु
	चयन (slbe->base_page_size) अणु
	हाल MMU_PAGE_64K:
		अगर ((r & 0xf000) == 0x1000)
			वापस MMU_PAGE_64K;
		अवरोध;
	हाल MMU_PAGE_16M:
		अगर ((r & 0xff000) == 0)
			वापस MMU_PAGE_16M;
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_64_xlate(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
				      काष्ठा kvmppc_pte *gpte, bool data,
				      bool isग_लिखो)
अणु
	काष्ठा kvmppc_slb *slbe;
	hva_t ptegp;
	u64 pteg[16];
	u64 avpn = 0;
	u64 v, r;
	u64 v_val, v_mask;
	u64 eaddr_mask;
	पूर्णांक i;
	u8 pp, key = 0;
	bool found = false;
	bool second = false;
	पूर्णांक pgsize;
	uदीर्घ mp_ea = vcpu->arch.magic_page_ea;

	/* Magic page override */
	अगर (unlikely(mp_ea) &&
	    unlikely((eaddr & ~0xfffULL) == (mp_ea & ~0xfffULL)) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR)) अणु
		gpte->eaddr = eaddr;
		gpte->vpage = kvmppc_mmu_book3s_64_ea_to_vp(vcpu, eaddr, data);
		gpte->raddr = vcpu->arch.magic_page_pa | (gpte->raddr & 0xfff);
		gpte->raddr &= KVM_PAM;
		gpte->may_execute = true;
		gpte->may_पढ़ो = true;
		gpte->may_ग_लिखो = true;
		gpte->page_size = MMU_PAGE_4K;
		gpte->wimg = HPTE_R_M;

		वापस 0;
	पूर्ण

	slbe = kvmppc_mmu_book3s_64_find_slbe(vcpu, eaddr);
	अगर (!slbe)
		जाओ no_seg_found;

	avpn = kvmppc_mmu_book3s_64_get_avpn(slbe, eaddr);
	v_val = avpn & HPTE_V_AVPN;

	अगर (slbe->tb)
		v_val |= SLB_VSID_B_1T;
	अगर (slbe->large)
		v_val |= HPTE_V_LARGE;
	v_val |= HPTE_V_VALID;

	v_mask = SLB_VSID_B | HPTE_V_AVPN | HPTE_V_LARGE | HPTE_V_VALID |
		HPTE_V_SECONDARY;

	pgsize = slbe->large ? MMU_PAGE_16M : MMU_PAGE_4K;

	mutex_lock(&vcpu->kvm->arch.hpt_mutex);

करो_second:
	ptegp = kvmppc_mmu_book3s_64_get_pteg(vcpu, slbe, eaddr, second);
	अगर (kvm_is_error_hva(ptegp))
		जाओ no_page_found;

	अगर(copy_from_user(pteg, (व्योम __user *)ptegp, माप(pteg))) अणु
		prपूर्णांकk_ratelimited(KERN_ERR
			"KVM: Can't copy data from 0x%lx!\n", ptegp);
		जाओ no_page_found;
	पूर्ण

	अगर ((kvmppc_get_msr(vcpu) & MSR_PR) && slbe->Kp)
		key = 4;
	अन्यथा अगर (!(kvmppc_get_msr(vcpu) & MSR_PR) && slbe->Ks)
		key = 4;

	क्रम (i=0; i<16; i+=2) अणु
		u64 pte0 = be64_to_cpu(pteg[i]);
		u64 pte1 = be64_to_cpu(pteg[i + 1]);

		/* Check all relevant fields of 1st dword */
		अगर ((pte0 & v_mask) == v_val) अणु
			/* If large page bit is set, check pgsize encoding */
			अगर (slbe->large &&
			    (vcpu->arch.hflags & BOOK3S_HFLAG_MULTI_PGSIZE)) अणु
				pgsize = decode_pagesize(slbe, pte1);
				अगर (pgsize < 0)
					जारी;
			पूर्ण
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		अगर (second)
			जाओ no_page_found;
		v_val |= HPTE_V_SECONDARY;
		second = true;
		जाओ करो_second;
	पूर्ण

	v = be64_to_cpu(pteg[i]);
	r = be64_to_cpu(pteg[i+1]);
	pp = (r & HPTE_R_PP) | key;
	अगर (r & HPTE_R_PP0)
		pp |= 8;

	gpte->eaddr = eaddr;
	gpte->vpage = kvmppc_mmu_book3s_64_ea_to_vp(vcpu, eaddr, data);

	eaddr_mask = (1ull << mmu_pagesize(pgsize)) - 1;
	gpte->raddr = (r & HPTE_R_RPN & ~eaddr_mask) | (eaddr & eaddr_mask);
	gpte->page_size = pgsize;
	gpte->may_execute = ((r & HPTE_R_N) ? false : true);
	अगर (unlikely(vcpu->arch.disable_kernel_nx) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR))
		gpte->may_execute = true;
	gpte->may_पढ़ो = false;
	gpte->may_ग_लिखो = false;
	gpte->wimg = r & HPTE_R_WIMG;

	चयन (pp) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 6:
		gpte->may_ग_लिखो = true;
		fallthrough;
	हाल 3:
	हाल 5:
	हाल 7:
	हाल 10:
		gpte->may_पढ़ो = true;
		अवरोध;
	पूर्ण

	dprपूर्णांकk("KVM MMU: Translated 0x%lx [0x%llx] -> 0x%llx "
		"-> 0x%lx\n",
		eaddr, avpn, gpte->vpage, gpte->raddr);

	/* Update PTE R and C bits, so the guest's swapper knows we used the
	 * page */
	अगर (gpte->may_पढ़ो && !(r & HPTE_R_R)) अणु
		/*
		 * Set the accessed flag.
		 * We have to ग_लिखो this back with a single byte ग_लिखो
		 * because another vcpu may be accessing this on
		 * non-PAPR platक्रमms such as mac99, and this is
		 * what real hardware करोes.
		 */
                अक्षर __user *addr = (अक्षर __user *) (ptegp + (i + 1) * माप(u64));
		r |= HPTE_R_R;
		put_user(r >> 8, addr + 6);
	पूर्ण
	अगर (isग_लिखो && gpte->may_ग_लिखो && !(r & HPTE_R_C)) अणु
		/* Set the dirty flag */
		/* Use a single byte ग_लिखो */
                अक्षर __user *addr = (अक्षर __user *) (ptegp + (i + 1) * माप(u64));
		r |= HPTE_R_C;
		put_user(r, addr + 7);
	पूर्ण

	mutex_unlock(&vcpu->kvm->arch.hpt_mutex);

	अगर (!gpte->may_पढ़ो || (isग_लिखो && !gpte->may_ग_लिखो))
		वापस -EPERM;
	वापस 0;

no_page_found:
	mutex_unlock(&vcpu->kvm->arch.hpt_mutex);
	वापस -ENOENT;

no_seg_found:
	dprपूर्णांकk("KVM MMU: Trigger segment fault\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम kvmppc_mmu_book3s_64_slbmte(काष्ठा kvm_vcpu *vcpu, u64 rs, u64 rb)
अणु
	u64 esid, esid_1t;
	पूर्णांक slb_nr;
	काष्ठा kvmppc_slb *slbe;

	dprपूर्णांकk("KVM MMU: slbmte(0x%llx, 0x%llx)\n", rs, rb);

	esid = GET_ESID(rb);
	esid_1t = GET_ESID_1T(rb);
	slb_nr = rb & 0xfff;

	अगर (slb_nr > vcpu->arch.slb_nr)
		वापस;

	slbe = &vcpu->arch.slb[slb_nr];

	slbe->large = (rs & SLB_VSID_L) ? 1 : 0;
	slbe->tb    = (rs & SLB_VSID_B_1T) ? 1 : 0;
	slbe->esid  = slbe->tb ? esid_1t : esid;
	slbe->vsid  = (rs & ~SLB_VSID_B) >> (kvmppc_slb_sid_shअगरt(slbe) - 16);
	slbe->valid = (rb & SLB_ESID_V) ? 1 : 0;
	slbe->Ks    = (rs & SLB_VSID_KS) ? 1 : 0;
	slbe->Kp    = (rs & SLB_VSID_KP) ? 1 : 0;
	slbe->nx    = (rs & SLB_VSID_N) ? 1 : 0;
	slbe->class = (rs & SLB_VSID_C) ? 1 : 0;

	slbe->base_page_size = MMU_PAGE_4K;
	अगर (slbe->large) अणु
		अगर (vcpu->arch.hflags & BOOK3S_HFLAG_MULTI_PGSIZE) अणु
			चयन (rs & SLB_VSID_LP) अणु
			हाल SLB_VSID_LP_00:
				slbe->base_page_size = MMU_PAGE_16M;
				अवरोध;
			हाल SLB_VSID_LP_01:
				slbe->base_page_size = MMU_PAGE_64K;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			slbe->base_page_size = MMU_PAGE_16M;
	पूर्ण

	slbe->orige = rb & (ESID_MASK | SLB_ESID_V);
	slbe->origv = rs;

	/* Map the new segment */
	kvmppc_mmu_map_segment(vcpu, esid << SID_SHIFT);
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_64_slbfee(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
				       uदीर्घ *ret_slb)
अणु
	काष्ठा kvmppc_slb *slbe = kvmppc_mmu_book3s_64_find_slbe(vcpu, eaddr);

	अगर (slbe) अणु
		*ret_slb = slbe->origv;
		वापस 0;
	पूर्ण
	*ret_slb = 0;
	वापस -ENOENT;
पूर्ण

अटल u64 kvmppc_mmu_book3s_64_slbmfee(काष्ठा kvm_vcpu *vcpu, u64 slb_nr)
अणु
	काष्ठा kvmppc_slb *slbe;

	अगर (slb_nr > vcpu->arch.slb_nr)
		वापस 0;

	slbe = &vcpu->arch.slb[slb_nr];

	वापस slbe->orige;
पूर्ण

अटल u64 kvmppc_mmu_book3s_64_slbmfev(काष्ठा kvm_vcpu *vcpu, u64 slb_nr)
अणु
	काष्ठा kvmppc_slb *slbe;

	अगर (slb_nr > vcpu->arch.slb_nr)
		वापस 0;

	slbe = &vcpu->arch.slb[slb_nr];

	वापस slbe->origv;
पूर्ण

अटल व्योम kvmppc_mmu_book3s_64_slbie(काष्ठा kvm_vcpu *vcpu, u64 ea)
अणु
	काष्ठा kvmppc_slb *slbe;
	u64 seg_size;

	dprपूर्णांकk("KVM MMU: slbie(0x%llx)\n", ea);

	slbe = kvmppc_mmu_book3s_64_find_slbe(vcpu, ea);

	अगर (!slbe)
		वापस;

	dprपूर्णांकk("KVM MMU: slbie(0x%llx, 0x%llx)\n", ea, slbe->esid);

	slbe->valid = false;
	slbe->orige = 0;
	slbe->origv = 0;

	seg_size = 1ull << kvmppc_slb_sid_shअगरt(slbe);
	kvmppc_mmu_flush_segment(vcpu, ea & ~(seg_size - 1), seg_size);
पूर्ण

अटल व्योम kvmppc_mmu_book3s_64_slbia(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	dprपूर्णांकk("KVM MMU: slbia()\n");

	क्रम (i = 1; i < vcpu->arch.slb_nr; i++) अणु
		vcpu->arch.slb[i].valid = false;
		vcpu->arch.slb[i].orige = 0;
		vcpu->arch.slb[i].origv = 0;
	पूर्ण

	अगर (kvmppc_get_msr(vcpu) & MSR_IR) अणु
		kvmppc_mmu_flush_segments(vcpu);
		kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu));
	पूर्ण
पूर्ण

अटल व्योम kvmppc_mmu_book3s_64_mtsrin(काष्ठा kvm_vcpu *vcpu, u32 srnum,
					uदीर्घ value)
अणु
	u64 rb = 0, rs = 0;

	/*
	 * According to Book3 2.01 mtsrin is implemented as:
	 *
	 * The SLB entry specअगरied by (RB)32:35 is loaded from रेजिस्टर
	 * RS, as follows.
	 *
	 * SLBE Bit	Source			SLB Field
	 *
	 * 0:31		0x0000_0000		ESID-0:31
	 * 32:35	(RB)32:35		ESID-32:35
	 * 36		0b1			V
	 * 37:61	0x00_0000|| 0b0		VSID-0:24
	 * 62:88	(RS)37:63		VSID-25:51
	 * 89:91	(RS)33:35		Ks Kp N
	 * 92		(RS)36			L ((RS)36 must be 0b0)
	 * 93		0b0			C
	 */

	dprपूर्णांकk("KVM MMU: mtsrin(0x%x, 0x%lx)\n", srnum, value);

	/* ESID = srnum */
	rb |= (srnum & 0xf) << 28;
	/* Set the valid bit */
	rb |= 1 << 27;
	/* Index = ESID */
	rb |= srnum;

	/* VSID = VSID */
	rs |= (value & 0xfffffff) << 12;
	/* flags = flags */
	rs |= ((value >> 28) & 0x7) << 9;

	kvmppc_mmu_book3s_64_slbmte(vcpu, rs, rb);
पूर्ण

अटल व्योम kvmppc_mmu_book3s_64_tlbie(काष्ठा kvm_vcpu *vcpu, uदीर्घ va,
				       bool large)
अणु
	u64 mask = 0xFFFFFFFFFULL;
	दीर्घ i;
	काष्ठा kvm_vcpu *v;

	dprपूर्णांकk("KVM MMU: tlbie(0x%lx)\n", va);

	/*
	 * The tlbie inकाष्ठाion changed behaviour starting with
	 * POWER6.  POWER6 and later करोn't have the large page flag
	 * in the inकाष्ठाion but in the RB value, aदीर्घ with bits
	 * indicating page and segment sizes.
	 */
	अगर (vcpu->arch.hflags & BOOK3S_HFLAG_NEW_TLBIE) अणु
		/* POWER6 or later */
		अगर (va & 1) अणु		/* L bit */
			अगर ((va & 0xf000) == 0x1000)
				mask = 0xFFFFFFFF0ULL;	/* 64k page */
			अन्यथा
				mask = 0xFFFFFF000ULL;	/* 16M page */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* older processors, e.g. PPC970 */
		अगर (large)
			mask = 0xFFFFFF000ULL;
	पूर्ण
	/* flush this VA on all vcpus */
	kvm_क्रम_each_vcpu(i, v, vcpu->kvm)
		kvmppc_mmu_pte_vflush(v, va >> 12, mask);
पूर्ण

#अगर_घोषित CONFIG_PPC_64K_PAGES
अटल पूर्णांक segment_contains_magic_page(काष्ठा kvm_vcpu *vcpu, uदीर्घ esid)
अणु
	uदीर्घ mp_ea = vcpu->arch.magic_page_ea;

	वापस mp_ea && !(kvmppc_get_msr(vcpu) & MSR_PR) &&
		(mp_ea >> SID_SHIFT) == esid;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kvmppc_mmu_book3s_64_esid_to_vsid(काष्ठा kvm_vcpu *vcpu, uदीर्घ esid,
					     u64 *vsid)
अणु
	uदीर्घ ea = esid << SID_SHIFT;
	काष्ठा kvmppc_slb *slb;
	u64 gvsid = esid;
	uदीर्घ mp_ea = vcpu->arch.magic_page_ea;
	पूर्णांक pagesize = MMU_PAGE_64K;
	u64 msr = kvmppc_get_msr(vcpu);

	अगर (msr & (MSR_DR|MSR_IR)) अणु
		slb = kvmppc_mmu_book3s_64_find_slbe(vcpu, ea);
		अगर (slb) अणु
			gvsid = slb->vsid;
			pagesize = slb->base_page_size;
			अगर (slb->tb) अणु
				gvsid <<= SID_SHIFT_1T - SID_SHIFT;
				gvsid |= esid & ((1ul << (SID_SHIFT_1T - SID_SHIFT)) - 1);
				gvsid |= VSID_1T;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (msr & (MSR_DR|MSR_IR)) अणु
	हाल 0:
		gvsid = VSID_REAL | esid;
		अवरोध;
	हाल MSR_IR:
		gvsid |= VSID_REAL_IR;
		अवरोध;
	हाल MSR_DR:
		gvsid |= VSID_REAL_DR;
		अवरोध;
	हाल MSR_DR|MSR_IR:
		अगर (!slb)
			जाओ no_slb;

		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_PPC_64K_PAGES
	/*
	 * Mark this as a 64k segment अगर the host is using
	 * 64k pages, the host MMU supports 64k pages and
	 * the guest segment page size is >= 64k,
	 * but not अगर this segment contains the magic page.
	 */
	अगर (pagesize >= MMU_PAGE_64K &&
	    mmu_psize_defs[MMU_PAGE_64K].shअगरt &&
	    !segment_contains_magic_page(vcpu, esid))
		gvsid |= VSID_64K;
#पूर्ण_अगर

	अगर (kvmppc_get_msr(vcpu) & MSR_PR)
		gvsid |= VSID_PR;

	*vsid = gvsid;
	वापस 0;

no_slb:
	/* Catch magic page हाल */
	अगर (unlikely(mp_ea) &&
	    unlikely(esid == (mp_ea >> SID_SHIFT)) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR)) अणु
		*vsid = VSID_REAL | esid;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल bool kvmppc_mmu_book3s_64_is_dcbz32(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (to_book3s(vcpu)->hid[5] & 0x80);
पूर्ण

व्योम kvmppc_mmu_book3s_64_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_mmu *mmu = &vcpu->arch.mmu;

	mmu->mfsrin = शून्य;
	mmu->mtsrin = kvmppc_mmu_book3s_64_mtsrin;
	mmu->slbmte = kvmppc_mmu_book3s_64_slbmte;
	mmu->slbmfee = kvmppc_mmu_book3s_64_slbmfee;
	mmu->slbmfev = kvmppc_mmu_book3s_64_slbmfev;
	mmu->slbfee = kvmppc_mmu_book3s_64_slbfee;
	mmu->slbie = kvmppc_mmu_book3s_64_slbie;
	mmu->slbia = kvmppc_mmu_book3s_64_slbia;
	mmu->xlate = kvmppc_mmu_book3s_64_xlate;
	mmu->tlbie = kvmppc_mmu_book3s_64_tlbie;
	mmu->esid_to_vsid = kvmppc_mmu_book3s_64_esid_to_vsid;
	mmu->ea_to_vp = kvmppc_mmu_book3s_64_ea_to_vp;
	mmu->is_dcbz32 = kvmppc_mmu_book3s_64_is_dcbz32;

	vcpu->arch.hflags |= BOOK3S_HFLAG_SLB;
पूर्ण
