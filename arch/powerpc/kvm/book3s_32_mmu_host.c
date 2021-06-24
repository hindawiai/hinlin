<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 SUSE Linux Products GmbH. All rights reserved.
 *
 * Authors:
 *     Alexander Graf <agraf@suse.de>
 */

#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/book3s/32/mmu-hash.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश "book3s.h"

/* #घोषणा DEBUG_MMU */
/* #घोषणा DEBUG_SR */

#अगर_घोषित DEBUG_MMU
#घोषणा dprपूर्णांकk_mmu(a, ...) prपूर्णांकk(KERN_INFO a, __VA_ARGS__)
#अन्यथा
#घोषणा dprपूर्णांकk_mmu(a, ...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित DEBUG_SR
#घोषणा dprपूर्णांकk_sr(a, ...) prपूर्णांकk(KERN_INFO a, __VA_ARGS__)
#अन्यथा
#घोषणा dprपूर्णांकk_sr(a, ...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर PAGE_SHIFT != 12
#त्रुटि Unknown page size
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
#त्रुटि XXX need to grab mmu_hash_lock
#पूर्ण_अगर

#अगर_घोषित CONFIG_PTE_64BIT
#त्रुटि Only 32 bit pages are supported क्रम now
#पूर्ण_अगर

अटल uदीर्घ htab;
अटल u32 htabmask;

व्योम kvmppc_mmu_invalidate_pte(काष्ठा kvm_vcpu *vcpu, काष्ठा hpte_cache *pte)
अणु
	अस्थिर u32 *pteg;

	/* Remove from host HTAB */
	pteg = (u32*)pte->slot;
	pteg[0] = 0;

	/* And make sure it's gone from the TLB too */
	यंत्र अस्थिर ("sync");
	यंत्र अस्थिर ("tlbie %0" : : "r" (pte->pte.eaddr) : "memory");
	यंत्र अस्थिर ("sync");
	यंत्र अस्थिर ("tlbsync");
पूर्ण

/* We keep 512 gvsid->hvsid entries, mapping the guest ones to the array using
 * a hash, so we करोn't waste cycles on looping */
अटल u16 kvmppc_sid_hash(काष्ठा kvm_vcpu *vcpu, u64 gvsid)
अणु
	वापस (u16)(((gvsid >> (SID_MAP_BITS * 7)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 6)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 5)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 4)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 3)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 2)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 1)) & SID_MAP_MASK) ^
		     ((gvsid >> (SID_MAP_BITS * 0)) & SID_MAP_MASK));
पूर्ण


अटल काष्ठा kvmppc_sid_map *find_sid_vsid(काष्ठा kvm_vcpu *vcpu, u64 gvsid)
अणु
	काष्ठा kvmppc_sid_map *map;
	u16 sid_map_mask;

	अगर (kvmppc_get_msr(vcpu) & MSR_PR)
		gvsid |= VSID_PR;

	sid_map_mask = kvmppc_sid_hash(vcpu, gvsid);
	map = &to_book3s(vcpu)->sid_map[sid_map_mask];
	अगर (map->guest_vsid == gvsid) अणु
		dprपूर्णांकk_sr("SR: Searching 0x%llx -> 0x%llx\n",
			    gvsid, map->host_vsid);
		वापस map;
	पूर्ण

	map = &to_book3s(vcpu)->sid_map[SID_MAP_MASK - sid_map_mask];
	अगर (map->guest_vsid == gvsid) अणु
		dprपूर्णांकk_sr("SR: Searching 0x%llx -> 0x%llx\n",
			    gvsid, map->host_vsid);
		वापस map;
	पूर्ण

	dprपूर्णांकk_sr("SR: Searching 0x%llx -> not found\n", gvsid);
	वापस शून्य;
पूर्ण

अटल u32 *kvmppc_mmu_get_pteg(काष्ठा kvm_vcpu *vcpu, u32 vsid, u32 eaddr,
				bool primary)
अणु
	u32 page, hash;
	uदीर्घ pteg = htab;

	page = (eaddr & ~ESID_MASK) >> 12;

	hash = ((vsid ^ page) << 6);
	अगर (!primary)
		hash = ~hash;

	hash &= htabmask;

	pteg |= hash;

	dprपूर्णांकk_mmu("htab: %lx | hash: %x | htabmask: %x | pteg: %lx\n",
		htab, hash, htabmask, pteg);

	वापस (u32*)pteg;
पूर्ण

बाह्य अक्षर etext[];

पूर्णांक kvmppc_mmu_map_page(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_pte *orig_pte,
			bool isग_लिखो)
अणु
	kvm_pfn_t hpaddr;
	u64 vpn;
	u64 vsid;
	काष्ठा kvmppc_sid_map *map;
	अस्थिर u32 *pteg;
	u32 eaddr = orig_pte->eaddr;
	u32 pteg0, pteg1;
	रेजिस्टर पूर्णांक rr = 0;
	bool primary = false;
	bool evict = false;
	काष्ठा hpte_cache *pte;
	पूर्णांक r = 0;
	bool writable;

	/* Get host physical address क्रम gpa */
	hpaddr = kvmppc_gpa_to_pfn(vcpu, orig_pte->raddr, isग_लिखो, &writable);
	अगर (is_error_noslot_pfn(hpaddr)) अणु
		prपूर्णांकk(KERN_INFO "Couldn't get guest page for gpa %lx!\n",
				 orig_pte->raddr);
		r = -EINVAL;
		जाओ out;
	पूर्ण
	hpaddr <<= PAGE_SHIFT;

	/* and ग_लिखो the mapping ea -> hpa पूर्णांकo the pt */
	vcpu->arch.mmu.esid_to_vsid(vcpu, orig_pte->eaddr >> SID_SHIFT, &vsid);
	map = find_sid_vsid(vcpu, vsid);
	अगर (!map) अणु
		kvmppc_mmu_map_segment(vcpu, eaddr);
		map = find_sid_vsid(vcpu, vsid);
	पूर्ण
	BUG_ON(!map);

	vsid = map->host_vsid;
	vpn = (vsid << (SID_SHIFT - VPN_SHIFT)) |
		((eaddr & ~ESID_MASK) >> VPN_SHIFT);
next_pteg:
	अगर (rr == 16) अणु
		primary = !primary;
		evict = true;
		rr = 0;
	पूर्ण

	pteg = kvmppc_mmu_get_pteg(vcpu, vsid, eaddr, primary);

	/* not evicting yet */
	अगर (!evict && (pteg[rr] & PTE_V)) अणु
		rr += 2;
		जाओ next_pteg;
	पूर्ण

	dprपूर्णांकk_mmu("KVM: old PTEG: %p (%d)\n", pteg, rr);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[0], pteg[1]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[2], pteg[3]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[4], pteg[5]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[6], pteg[7]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[8], pteg[9]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[10], pteg[11]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[12], pteg[13]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[14], pteg[15]);

	pteg0 = ((eaddr & 0x0fffffff) >> 22) | (vsid << 7) | PTE_V |
		(primary ? 0 : PTE_SEC);
	pteg1 = hpaddr | PTE_M | PTE_R | PTE_C;

	अगर (orig_pte->may_ग_लिखो && writable) अणु
		pteg1 |= PP_RWRW;
		mark_page_dirty(vcpu->kvm, orig_pte->raddr >> PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		pteg1 |= PP_RWRX;
	पूर्ण

	अगर (orig_pte->may_execute)
		kvmppc_mmu_flush_icache(hpaddr >> PAGE_SHIFT);

	local_irq_disable();

	अगर (pteg[rr]) अणु
		pteg[rr] = 0;
		यंत्र अस्थिर ("sync");
	पूर्ण
	pteg[rr + 1] = pteg1;
	pteg[rr] = pteg0;
	यंत्र अस्थिर ("sync");

	local_irq_enable();

	dprपूर्णांकk_mmu("KVM: new PTEG: %p\n", pteg);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[0], pteg[1]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[2], pteg[3]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[4], pteg[5]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[6], pteg[7]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[8], pteg[9]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[10], pteg[11]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[12], pteg[13]);
	dprपूर्णांकk_mmu("KVM:   %08x - %08x\n", pteg[14], pteg[15]);


	/* Now tell our Shaकरोw PTE code about the new page */

	pte = kvmppc_mmu_hpte_cache_next(vcpu);
	अगर (!pte) अणु
		kvm_release_pfn_clean(hpaddr >> PAGE_SHIFT);
		r = -EAGAIN;
		जाओ out;
	पूर्ण

	dprपूर्णांकk_mmu("KVM: %c%c Map 0x%llx: [%lx] 0x%llx (0x%llx) -> %lx\n",
		    orig_pte->may_ग_लिखो ? 'w' : '-',
		    orig_pte->may_execute ? 'x' : '-',
		    orig_pte->eaddr, (uदीर्घ)pteg, vpn,
		    orig_pte->vpage, hpaddr);

	pte->slot = (uदीर्घ)&pteg[rr];
	pte->host_vpn = vpn;
	pte->pte = *orig_pte;
	pte->pfn = hpaddr >> PAGE_SHIFT;

	kvmppc_mmu_hpte_cache_map(vcpu, pte);

	kvm_release_pfn_clean(hpaddr >> PAGE_SHIFT);
out:
	वापस r;
पूर्ण

व्योम kvmppc_mmu_unmap_page(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_pte *pte)
अणु
	kvmppc_mmu_pte_vflush(vcpu, pte->vpage, 0xfffffffffULL);
पूर्ण

अटल काष्ठा kvmppc_sid_map *create_sid_map(काष्ठा kvm_vcpu *vcpu, u64 gvsid)
अणु
	काष्ठा kvmppc_sid_map *map;
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u16 sid_map_mask;
	अटल पूर्णांक backwards_map = 0;

	अगर (kvmppc_get_msr(vcpu) & MSR_PR)
		gvsid |= VSID_PR;

	/* We might get collisions that trap in preceding order, so let's
	   map them dअगरferently */

	sid_map_mask = kvmppc_sid_hash(vcpu, gvsid);
	अगर (backwards_map)
		sid_map_mask = SID_MAP_MASK - sid_map_mask;

	map = &to_book3s(vcpu)->sid_map[sid_map_mask];

	/* Make sure we're taking the other map next समय */
	backwards_map = !backwards_map;

	/* Uh-oh ... out of mappings. Let's flush! */
	अगर (vcpu_book3s->vsid_next >= VSID_POOL_SIZE) अणु
		vcpu_book3s->vsid_next = 0;
		स_रखो(vcpu_book3s->sid_map, 0,
		       माप(काष्ठा kvmppc_sid_map) * SID_MAP_NUM);
		kvmppc_mmu_pte_flush(vcpu, 0, 0);
		kvmppc_mmu_flush_segments(vcpu);
	पूर्ण
	map->host_vsid = vcpu_book3s->vsid_pool[vcpu_book3s->vsid_next];
	vcpu_book3s->vsid_next++;

	map->guest_vsid = gvsid;
	map->valid = true;

	वापस map;
पूर्ण

पूर्णांक kvmppc_mmu_map_segment(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr)
अणु
	u32 esid = eaddr >> SID_SHIFT;
	u64 gvsid;
	u32 sr;
	काष्ठा kvmppc_sid_map *map;
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
	पूर्णांक r = 0;

	अगर (vcpu->arch.mmu.esid_to_vsid(vcpu, esid, &gvsid)) अणु
		/* Invalidate an entry */
		svcpu->sr[esid] = SR_INVALID;
		r = -ENOENT;
		जाओ out;
	पूर्ण

	map = find_sid_vsid(vcpu, gvsid);
	अगर (!map)
		map = create_sid_map(vcpu, gvsid);

	map->guest_esid = esid;
	sr = map->host_vsid | SR_KP;
	svcpu->sr[esid] = sr;

	dprपूर्णांकk_sr("MMU: mtsr %d, 0x%x\n", esid, sr);

out:
	svcpu_put(svcpu);
	वापस r;
पूर्ण

व्योम kvmppc_mmu_flush_segments(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);

	dprपूर्णांकk_sr("MMU: flushing all segments (%d)\n", ARRAY_SIZE(svcpu->sr));
	क्रम (i = 0; i < ARRAY_SIZE(svcpu->sr); i++)
		svcpu->sr[i] = SR_INVALID;

	svcpu_put(svcpu);
पूर्ण

व्योम kvmppc_mmu_destroy_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	kvmppc_mmu_hpte_destroy(vcpu);
	preempt_disable();
	क्रम (i = 0; i < SID_CONTEXTS; i++)
		__destroy_context(to_book3s(vcpu)->context_id[i]);
	preempt_enable();
पूर्ण

/* From mm/mmu_context_hash32.c */
#घोषणा CTX_TO_VSID(c, id)	((((c) * (897 * 16)) + (id * 0x111)) & 0xffffff)

पूर्णांक kvmppc_mmu_init_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	पूर्णांक err;
	uदीर्घ sdr1;
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < SID_CONTEXTS; i++) अणु
		err = __init_new_context();
		अगर (err < 0)
			जाओ init_fail;
		vcpu3s->context_id[i] = err;

		/* Remember context id क्रम this combination */
		क्रम (j = 0; j < 16; j++)
			vcpu3s->vsid_pool[(i * 16) + j] = CTX_TO_VSID(err, j);
	पूर्ण

	vcpu3s->vsid_next = 0;

	/* Remember where the HTAB is */
	यंत्र ( "mfsdr1 %0" : "=r"(sdr1) );
	htabmask = ((sdr1 & 0x1FF) << 16) | 0xFFC0;
	htab = (uदीर्घ)__va(sdr1 & 0xffff0000);

	kvmppc_mmu_hpte_init(vcpu);

	वापस 0;

init_fail:
	क्रम (j = 0; j < i; j++) अणु
		अगर (!vcpu3s->context_id[j])
			जारी;

		__destroy_context(to_book3s(vcpu)->context_id[j]);
	पूर्ण

	वापस -1;
पूर्ण
