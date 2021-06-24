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

/* #घोषणा DEBUG_MMU */
/* #घोषणा DEBUG_MMU_PTE */
/* #घोषणा DEBUG_MMU_PTE_IP 0xfff14c40 */

#अगर_घोषित DEBUG_MMU
#घोषणा dprपूर्णांकk(X...) prपूर्णांकk(KERN_INFO X)
#अन्यथा
#घोषणा dprपूर्णांकk(X...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित DEBUG_MMU_PTE
#घोषणा dprपूर्णांकk_pte(X...) prपूर्णांकk(KERN_INFO X)
#अन्यथा
#घोषणा dprपूर्णांकk_pte(X...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#घोषणा PTEG_FLAG_ACCESSED	0x00000100
#घोषणा PTEG_FLAG_सूचीTY		0x00000080
#अगर_अघोषित SID_SHIFT
#घोषणा SID_SHIFT		28
#पूर्ण_अगर

अटल अंतरभूत bool check_debug_ip(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित DEBUG_MMU_PTE_IP
	वापस vcpu->arch.regs.nip == DEBUG_MMU_PTE_IP;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 sr_vsid(u32 sr_raw)
अणु
	वापस sr_raw & 0x0fffffff;
पूर्ण

अटल अंतरभूत bool sr_valid(u32 sr_raw)
अणु
	वापस (sr_raw & 0x80000000) ? false : true;
पूर्ण

अटल अंतरभूत bool sr_ks(u32 sr_raw)
अणु
	वापस (sr_raw & 0x40000000) ? true: false;
पूर्ण

अटल अंतरभूत bool sr_kp(u32 sr_raw)
अणु
	वापस (sr_raw & 0x20000000) ? true: false;
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_32_xlate_bat(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
					  काष्ठा kvmppc_pte *pte, bool data,
					  bool isग_लिखो);
अटल पूर्णांक kvmppc_mmu_book3s_32_esid_to_vsid(काष्ठा kvm_vcpu *vcpu, uदीर्घ esid,
					     u64 *vsid);

अटल u32 find_sr(काष्ठा kvm_vcpu *vcpu, gva_t eaddr)
अणु
	वापस kvmppc_get_sr(vcpu, (eaddr >> 28) & 0xf);
पूर्ण

अटल u64 kvmppc_mmu_book3s_32_ea_to_vp(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
					 bool data)
अणु
	u64 vsid;
	काष्ठा kvmppc_pte pte;

	अगर (!kvmppc_mmu_book3s_32_xlate_bat(vcpu, eaddr, &pte, data, false))
		वापस pte.vpage;

	kvmppc_mmu_book3s_32_esid_to_vsid(vcpu, eaddr >> SID_SHIFT, &vsid);
	वापस (((u64)eaddr >> 12) & 0xffff) | (vsid << 16);
पूर्ण

अटल hva_t kvmppc_mmu_book3s_32_get_pteg(काष्ठा kvm_vcpu *vcpu,
				      u32 sre, gva_t eaddr,
				      bool primary)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u32 page, hash, pteg, htabmask;
	hva_t r;

	page = (eaddr & 0x0FFFFFFF) >> 12;
	htabmask = ((vcpu_book3s->sdr1 & 0x1FF) << 16) | 0xFFC0;

	hash = ((sr_vsid(sre) ^ page) << 6);
	अगर (!primary)
		hash = ~hash;
	hash &= htabmask;

	pteg = (vcpu_book3s->sdr1 & 0xffff0000) | hash;

	dprपूर्णांकk("MMU: pc=0x%lx eaddr=0x%lx sdr1=0x%llx pteg=0x%x vsid=0x%x\n",
		kvmppc_get_pc(vcpu), eaddr, vcpu_book3s->sdr1, pteg,
		sr_vsid(sre));

	r = gfn_to_hva(vcpu->kvm, pteg >> PAGE_SHIFT);
	अगर (kvm_is_error_hva(r))
		वापस r;
	वापस r | (pteg & ~PAGE_MASK);
पूर्ण

अटल u32 kvmppc_mmu_book3s_32_get_ptem(u32 sre, gva_t eaddr, bool primary)
अणु
	वापस ((eaddr & 0x0fffffff) >> 22) | (sr_vsid(sre) << 7) |
	       (primary ? 0 : 0x40) | 0x80000000;
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_32_xlate_bat(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
					  काष्ठा kvmppc_pte *pte, bool data,
					  bool isग_लिखो)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	काष्ठा kvmppc_bat *bat;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (data)
			bat = &vcpu_book3s->dbat[i];
		अन्यथा
			bat = &vcpu_book3s->ibat[i];

		अगर (kvmppc_get_msr(vcpu) & MSR_PR) अणु
			अगर (!bat->vp)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!bat->vs)
				जारी;
		पूर्ण

		अगर (check_debug_ip(vcpu))
		अणु
			dprपूर्णांकk_pte("%cBAT %02d: 0x%lx - 0x%x (0x%x)\n",
				    data ? 'd' : 'i', i, eaddr, bat->bepi,
				    bat->bepi_mask);
		पूर्ण
		अगर ((eaddr & bat->bepi_mask) == bat->bepi) अणु
			u64 vsid;
			kvmppc_mmu_book3s_32_esid_to_vsid(vcpu,
				eaddr >> SID_SHIFT, &vsid);
			vsid <<= 16;
			pte->vpage = (((u64)eaddr >> 12) & 0xffff) | vsid;

			pte->raddr = bat->brpn | (eaddr & ~bat->bepi_mask);
			pte->may_पढ़ो = bat->pp;
			pte->may_ग_लिखो = bat->pp > 1;
			pte->may_execute = true;
			अगर (!pte->may_पढ़ो) अणु
				prपूर्णांकk(KERN_INFO "BAT is not readable!\n");
				जारी;
			पूर्ण
			अगर (isग_लिखो && !pte->may_ग_लिखो) अणु
				dprपूर्णांकk_pte("BAT is read-only!\n");
				जारी;
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_32_xlate_pte(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
				     काष्ठा kvmppc_pte *pte, bool data,
				     bool isग_लिखो, bool primary)
अणु
	u32 sre;
	hva_t ptegp;
	u32 pteg[16];
	u32 pte0, pte1;
	u32 ptem = 0;
	पूर्णांक i;
	पूर्णांक found = 0;

	sre = find_sr(vcpu, eaddr);

	dprपूर्णांकk_pte("SR 0x%lx: vsid=0x%x, raw=0x%x\n", eaddr >> 28,
		    sr_vsid(sre), sre);

	pte->vpage = kvmppc_mmu_book3s_32_ea_to_vp(vcpu, eaddr, data);

	ptegp = kvmppc_mmu_book3s_32_get_pteg(vcpu, sre, eaddr, primary);
	अगर (kvm_is_error_hva(ptegp)) अणु
		prपूर्णांकk(KERN_INFO "KVM: Invalid PTEG!\n");
		जाओ no_page_found;
	पूर्ण

	ptem = kvmppc_mmu_book3s_32_get_ptem(sre, eaddr, primary);

	अगर(copy_from_user(pteg, (व्योम __user *)ptegp, माप(pteg))) अणु
		prपूर्णांकk_ratelimited(KERN_ERR
			"KVM: Can't copy data from 0x%lx!\n", ptegp);
		जाओ no_page_found;
	पूर्ण

	क्रम (i=0; i<16; i+=2) अणु
		pte0 = be32_to_cpu(pteg[i]);
		pte1 = be32_to_cpu(pteg[i + 1]);
		अगर (ptem == pte0) अणु
			u8 pp;

			pte->raddr = (pte1 & ~(0xFFFULL)) | (eaddr & 0xFFF);
			pp = pte1 & 3;

			अगर ((sr_kp(sre) &&  (kvmppc_get_msr(vcpu) & MSR_PR)) ||
			    (sr_ks(sre) && !(kvmppc_get_msr(vcpu) & MSR_PR)))
				pp |= 4;

			pte->may_ग_लिखो = false;
			pte->may_पढ़ो = false;
			pte->may_execute = true;
			चयन (pp) अणु
				हाल 0:
				हाल 1:
				हाल 2:
				हाल 6:
					pte->may_ग_लिखो = true;
					fallthrough;
				हाल 3:
				हाल 5:
				हाल 7:
					pte->may_पढ़ो = true;
					अवरोध;
			पूर्ण

			dprपूर्णांकk_pte("MMU: Found PTE -> %x %x - %x\n",
				    pte0, pte1, pp);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Update PTE C and A bits, so the guest's swapper knows we used the
	   page */
	अगर (found) अणु
		u32 pte_r = pte1;
		अक्षर __user *addr = (अक्षर __user *) (ptegp + (i+1) * माप(u32));

		/*
		 * Use single-byte ग_लिखोs to update the HPTE, to
		 * conक्रमm to what real hardware करोes.
		 */
		अगर (pte->may_पढ़ो && !(pte_r & PTEG_FLAG_ACCESSED)) अणु
			pte_r |= PTEG_FLAG_ACCESSED;
			put_user(pte_r >> 8, addr + 2);
		पूर्ण
		अगर (isग_लिखो && pte->may_ग_लिखो && !(pte_r & PTEG_FLAG_सूचीTY)) अणु
			pte_r |= PTEG_FLAG_सूचीTY;
			put_user(pte_r, addr + 3);
		पूर्ण
		अगर (!pte->may_पढ़ो || (isग_लिखो && !pte->may_ग_लिखो))
			वापस -EPERM;
		वापस 0;
	पूर्ण

no_page_found:

	अगर (check_debug_ip(vcpu)) अणु
		dprपूर्णांकk_pte("KVM MMU: No PTE found (sdr1=0x%llx ptegp=0x%lx)\n",
			    to_book3s(vcpu)->sdr1, ptegp);
		क्रम (i=0; i<16; i+=2) अणु
			dprपूर्णांकk_pte("   %02d: 0x%x - 0x%x (0x%x)\n",
				    i, be32_to_cpu(pteg[i]),
				    be32_to_cpu(pteg[i+1]), ptem);
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_32_xlate(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
				      काष्ठा kvmppc_pte *pte, bool data,
				      bool isग_लिखो)
अणु
	पूर्णांक r;
	uदीर्घ mp_ea = vcpu->arch.magic_page_ea;

	pte->eaddr = eaddr;
	pte->page_size = MMU_PAGE_4K;

	/* Magic page override */
	अगर (unlikely(mp_ea) &&
	    unlikely((eaddr & ~0xfffULL) == (mp_ea & ~0xfffULL)) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR)) अणु
		pte->vpage = kvmppc_mmu_book3s_32_ea_to_vp(vcpu, eaddr, data);
		pte->raddr = vcpu->arch.magic_page_pa | (pte->raddr & 0xfff);
		pte->raddr &= KVM_PAM;
		pte->may_execute = true;
		pte->may_पढ़ो = true;
		pte->may_ग_लिखो = true;

		वापस 0;
	पूर्ण

	r = kvmppc_mmu_book3s_32_xlate_bat(vcpu, eaddr, pte, data, isग_लिखो);
	अगर (r < 0)
		r = kvmppc_mmu_book3s_32_xlate_pte(vcpu, eaddr, pte,
						   data, isग_लिखो, true);
	अगर (r == -ENOENT)
		r = kvmppc_mmu_book3s_32_xlate_pte(vcpu, eaddr, pte,
						   data, isग_लिखो, false);

	वापस r;
पूर्ण


अटल u32 kvmppc_mmu_book3s_32_mfsrin(काष्ठा kvm_vcpu *vcpu, u32 srnum)
अणु
	वापस kvmppc_get_sr(vcpu, srnum);
पूर्ण

अटल व्योम kvmppc_mmu_book3s_32_mtsrin(काष्ठा kvm_vcpu *vcpu, u32 srnum,
					uदीर्घ value)
अणु
	kvmppc_set_sr(vcpu, srnum, value);
	kvmppc_mmu_map_segment(vcpu, srnum << SID_SHIFT);
पूर्ण

अटल व्योम kvmppc_mmu_book3s_32_tlbie(काष्ठा kvm_vcpu *vcpu, uदीर्घ ea, bool large)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *v;

	/* flush this VA on all cpus */
	kvm_क्रम_each_vcpu(i, v, vcpu->kvm)
		kvmppc_mmu_pte_flush(v, ea, 0x0FFFF000);
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_32_esid_to_vsid(काष्ठा kvm_vcpu *vcpu, uदीर्घ esid,
					     u64 *vsid)
अणु
	uदीर्घ ea = esid << SID_SHIFT;
	u32 sr;
	u64 gvsid = esid;
	u64 msr = kvmppc_get_msr(vcpu);

	अगर (msr & (MSR_DR|MSR_IR)) अणु
		sr = find_sr(vcpu, ea);
		अगर (sr_valid(sr))
			gvsid = sr_vsid(sr);
	पूर्ण

	/* In हाल we only have one of MSR_IR or MSR_DR set, let's put
	   that in the real-mode context (and hope RM करोesn't access
	   high memory) */
	चयन (msr & (MSR_DR|MSR_IR)) अणु
	हाल 0:
		*vsid = VSID_REAL | esid;
		अवरोध;
	हाल MSR_IR:
		*vsid = VSID_REAL_IR | gvsid;
		अवरोध;
	हाल MSR_DR:
		*vsid = VSID_REAL_DR | gvsid;
		अवरोध;
	हाल MSR_DR|MSR_IR:
		अगर (sr_valid(sr))
			*vsid = sr_vsid(sr);
		अन्यथा
			*vsid = VSID_BAT | gvsid;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (msr & MSR_PR)
		*vsid |= VSID_PR;

	वापस 0;
पूर्ण

अटल bool kvmppc_mmu_book3s_32_is_dcbz32(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस true;
पूर्ण


व्योम kvmppc_mmu_book3s_32_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_mmu *mmu = &vcpu->arch.mmu;

	mmu->mtsrin = kvmppc_mmu_book3s_32_mtsrin;
	mmu->mfsrin = kvmppc_mmu_book3s_32_mfsrin;
	mmu->xlate = kvmppc_mmu_book3s_32_xlate;
	mmu->tlbie = kvmppc_mmu_book3s_32_tlbie;
	mmu->esid_to_vsid = kvmppc_mmu_book3s_32_esid_to_vsid;
	mmu->ea_to_vp = kvmppc_mmu_book3s_32_ea_to_vp;
	mmu->is_dcbz32 = kvmppc_mmu_book3s_32_is_dcbz32;

	mmu->slbmte = शून्य;
	mmu->slbmfee = शून्य;
	mmu->slbmfev = शून्य;
	mmu->slbfee = शून्य;
	mmu->slbie = शून्य;
	mmu->slbia = शून्य;
पूर्ण
