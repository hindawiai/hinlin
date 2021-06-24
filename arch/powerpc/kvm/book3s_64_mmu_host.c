<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 SUSE Linux Products GmbH. All rights reserved.
 *
 * Authors:
 *     Alexander Graf <agraf@suse.de>
 *     Kevin Wolf <mail@kevin-wolf.de>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/pkeys.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/book3s/64/mmu-hash.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश "trace_pr.h"
#समावेश "book3s.h"

#घोषणा PTE_SIZE 12

व्योम kvmppc_mmu_invalidate_pte(काष्ठा kvm_vcpu *vcpu, काष्ठा hpte_cache *pte)
अणु
	mmu_hash_ops.hpte_invalidate(pte->slot, pte->host_vpn,
				     pte->pagesize, pte->pagesize,
				     MMU_SEGSIZE_256M, false);
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
	अगर (map->valid && (map->guest_vsid == gvsid)) अणु
		trace_kvm_book3s_slb_found(gvsid, map->host_vsid);
		वापस map;
	पूर्ण

	map = &to_book3s(vcpu)->sid_map[SID_MAP_MASK - sid_map_mask];
	अगर (map->valid && (map->guest_vsid == gvsid)) अणु
		trace_kvm_book3s_slb_found(gvsid, map->host_vsid);
		वापस map;
	पूर्ण

	trace_kvm_book3s_slb_fail(sid_map_mask, gvsid);
	वापस शून्य;
पूर्ण

पूर्णांक kvmppc_mmu_map_page(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_pte *orig_pte,
			bool isग_लिखो)
अणु
	अचिन्हित दीर्घ vpn;
	kvm_pfn_t hpaddr;
	uदीर्घ hash, hpteg;
	u64 vsid;
	पूर्णांक ret;
	पूर्णांक rflags = 0x192;
	पूर्णांक vflags = 0;
	पूर्णांक attempt = 0;
	काष्ठा kvmppc_sid_map *map;
	पूर्णांक r = 0;
	पूर्णांक hpsize = MMU_PAGE_4K;
	bool writable;
	अचिन्हित दीर्घ mmu_seq;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा hpte_cache *cpte;
	अचिन्हित दीर्घ gfn = orig_pte->raddr >> PAGE_SHIFT;
	अचिन्हित दीर्घ pfn;

	/* used to check क्रम invalidations in progress */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	/* Get host physical address क्रम gpa */
	pfn = kvmppc_gpa_to_pfn(vcpu, orig_pte->raddr, isग_लिखो, &writable);
	अगर (is_error_noslot_pfn(pfn)) अणु
		prपूर्णांकk(KERN_INFO "Couldn't get guest page for gpa %lx!\n",
		       orig_pte->raddr);
		r = -EINVAL;
		जाओ out;
	पूर्ण
	hpaddr = pfn << PAGE_SHIFT;

	/* and ग_लिखो the mapping ea -> hpa पूर्णांकo the pt */
	vcpu->arch.mmu.esid_to_vsid(vcpu, orig_pte->eaddr >> SID_SHIFT, &vsid);
	map = find_sid_vsid(vcpu, vsid);
	अगर (!map) अणु
		ret = kvmppc_mmu_map_segment(vcpu, orig_pte->eaddr);
		WARN_ON(ret < 0);
		map = find_sid_vsid(vcpu, vsid);
	पूर्ण
	अगर (!map) अणु
		prपूर्णांकk(KERN_ERR "KVM: Segment map for 0x%llx (0x%lx) failed\n",
				vsid, orig_pte->eaddr);
		WARN_ON(true);
		r = -EINVAL;
		जाओ out;
	पूर्ण

	vpn = hpt_vpn(orig_pte->eaddr, map->host_vsid, MMU_SEGSIZE_256M);

	kvm_set_pfn_accessed(pfn);
	अगर (!orig_pte->may_ग_लिखो || !writable)
		rflags |= PP_RXRX;
	अन्यथा अणु
		mark_page_dirty(vcpu->kvm, gfn);
		kvm_set_pfn_dirty(pfn);
	पूर्ण

	अगर (!orig_pte->may_execute)
		rflags |= HPTE_R_N;
	अन्यथा
		kvmppc_mmu_flush_icache(pfn);

	rflags |= pte_to_hpte_pkey_bits(0, HPTE_USE_KERNEL_KEY);
	rflags = (rflags & ~HPTE_R_WIMG) | orig_pte->wimg;

	/*
	 * Use 64K pages अगर possible; otherwise, on 64K page kernels,
	 * we need to transfer 4 more bits from guest real to host real addr.
	 */
	अगर (vsid & VSID_64K)
		hpsize = MMU_PAGE_64K;
	अन्यथा
		hpaddr |= orig_pte->raddr & (~0xfffULL & ~PAGE_MASK);

	hash = hpt_hash(vpn, mmu_psize_defs[hpsize].shअगरt, MMU_SEGSIZE_256M);

	cpte = kvmppc_mmu_hpte_cache_next(vcpu);

	spin_lock(&kvm->mmu_lock);
	अगर (!cpte || mmu_notअगरier_retry(kvm, mmu_seq)) अणु
		r = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

map_again:
	hpteg = ((hash & htab_hash_mask) * HPTES_PER_GROUP);

	/* In हाल we tried normal mapping alपढ़ोy, let's nuke old entries */
	अगर (attempt > 1)
		अगर (mmu_hash_ops.hpte_हटाओ(hpteg) < 0) अणु
			r = -1;
			जाओ out_unlock;
		पूर्ण

	ret = mmu_hash_ops.hpte_insert(hpteg, vpn, hpaddr, rflags, vflags,
				       hpsize, hpsize, MMU_SEGSIZE_256M);

	अगर (ret == -1) अणु
		/* If we couldn't map a primary PTE, try a secondary */
		hash = ~hash;
		vflags ^= HPTE_V_SECONDARY;
		attempt++;
		जाओ map_again;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		r = -EIO;
		जाओ out_unlock;
	पूर्ण अन्यथा अणु
		trace_kvm_book3s_64_mmu_map(rflags, hpteg,
					    vpn, hpaddr, orig_pte);

		/*
		 * The mmu_hash_ops code may give us a secondary entry even
		 * though we asked क्रम a primary. Fix up.
		 */
		अगर ((ret & _PTEIDX_SECONDARY) && !(vflags & HPTE_V_SECONDARY)) अणु
			hash = ~hash;
			hpteg = ((hash & htab_hash_mask) * HPTES_PER_GROUP);
		पूर्ण

		cpte->slot = hpteg + (ret & 7);
		cpte->host_vpn = vpn;
		cpte->pte = *orig_pte;
		cpte->pfn = pfn;
		cpte->pagesize = hpsize;

		kvmppc_mmu_hpte_cache_map(vcpu, cpte);
		cpte = शून्य;
	पूर्ण

out_unlock:
	spin_unlock(&kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	अगर (cpte)
		kvmppc_mmu_hpte_cache_मुक्त(cpte);

out:
	वापस r;
पूर्ण

व्योम kvmppc_mmu_unmap_page(काष्ठा kvm_vcpu *vcpu, काष्ठा kvmppc_pte *pte)
अणु
	u64 mask = 0xfffffffffULL;
	u64 vsid;

	vcpu->arch.mmu.esid_to_vsid(vcpu, pte->eaddr >> SID_SHIFT, &vsid);
	अगर (vsid & VSID_64K)
		mask = 0xffffffff0ULL;
	kvmppc_mmu_pte_vflush(vcpu, pte->vpage, mask);
पूर्ण

अटल काष्ठा kvmppc_sid_map *create_sid_map(काष्ठा kvm_vcpu *vcpu, u64 gvsid)
अणु
	अचिन्हित दीर्घ vsid_bits = VSID_BITS_65_256M;
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
	अगर (vcpu_book3s->proto_vsid_next == vcpu_book3s->proto_vsid_max) अणु
		vcpu_book3s->proto_vsid_next = vcpu_book3s->proto_vsid_first;
		स_रखो(vcpu_book3s->sid_map, 0,
		       माप(काष्ठा kvmppc_sid_map) * SID_MAP_NUM);
		kvmppc_mmu_pte_flush(vcpu, 0, 0);
		kvmppc_mmu_flush_segments(vcpu);
	पूर्ण

	अगर (mmu_has_feature(MMU_FTR_68_BIT_VA))
		vsid_bits = VSID_BITS_256M;

	map->host_vsid = vsid_scramble(vcpu_book3s->proto_vsid_next++,
				       VSID_MULTIPLIER_256M, vsid_bits);

	map->guest_vsid = gvsid;
	map->valid = true;

	trace_kvm_book3s_slb_map(sid_map_mask, gvsid, map->host_vsid);

	वापस map;
पूर्ण

अटल पूर्णांक kvmppc_mmu_next_segment(काष्ठा kvm_vcpu *vcpu, uदीर्घ esid)
अणु
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
	पूर्णांक i;
	पूर्णांक max_slb_size = 64;
	पूर्णांक found_inval = -1;
	पूर्णांक r;

	/* Are we overwriting? */
	क्रम (i = 0; i < svcpu->slb_max; i++) अणु
		अगर (!(svcpu->slb[i].esid & SLB_ESID_V))
			found_inval = i;
		अन्यथा अगर ((svcpu->slb[i].esid & ESID_MASK) == esid) अणु
			r = i;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Found a spare entry that was invalidated beक्रमe */
	अगर (found_inval >= 0) अणु
		r = found_inval;
		जाओ out;
	पूर्ण

	/* No spare invalid entry, so create one */

	अगर (mmu_slb_size < 64)
		max_slb_size = mmu_slb_size;

	/* Overflowing -> purge */
	अगर ((svcpu->slb_max) == max_slb_size)
		kvmppc_mmu_flush_segments(vcpu);

	r = svcpu->slb_max;
	svcpu->slb_max++;

out:
	svcpu_put(svcpu);
	वापस r;
पूर्ण

पूर्णांक kvmppc_mmu_map_segment(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr)
अणु
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
	u64 esid = eaddr >> SID_SHIFT;
	u64 slb_esid = (eaddr & ESID_MASK) | SLB_ESID_V;
	u64 slb_vsid = SLB_VSID_USER;
	u64 gvsid;
	पूर्णांक slb_index;
	काष्ठा kvmppc_sid_map *map;
	पूर्णांक r = 0;

	slb_index = kvmppc_mmu_next_segment(vcpu, eaddr & ESID_MASK);

	अगर (vcpu->arch.mmu.esid_to_vsid(vcpu, esid, &gvsid)) अणु
		/* Invalidate an entry */
		svcpu->slb[slb_index].esid = 0;
		r = -ENOENT;
		जाओ out;
	पूर्ण

	map = find_sid_vsid(vcpu, gvsid);
	अगर (!map)
		map = create_sid_map(vcpu, gvsid);

	map->guest_esid = esid;

	slb_vsid |= (map->host_vsid << 12);
	slb_vsid &= ~SLB_VSID_KP;
	slb_esid |= slb_index;

#अगर_घोषित CONFIG_PPC_64K_PAGES
	/* Set host segment base page size to 64K अगर possible */
	अगर (gvsid & VSID_64K)
		slb_vsid |= mmu_psize_defs[MMU_PAGE_64K].sllp;
#पूर्ण_अगर

	svcpu->slb[slb_index].esid = slb_esid;
	svcpu->slb[slb_index].vsid = slb_vsid;

	trace_kvm_book3s_slbmte(slb_vsid, slb_esid);

out:
	svcpu_put(svcpu);
	वापस r;
पूर्ण

व्योम kvmppc_mmu_flush_segment(काष्ठा kvm_vcpu *vcpu, uदीर्घ ea, uदीर्घ seg_size)
अणु
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
	uदीर्घ seg_mask = -seg_size;
	पूर्णांक i;

	क्रम (i = 0; i < svcpu->slb_max; i++) अणु
		अगर ((svcpu->slb[i].esid & SLB_ESID_V) &&
		    (svcpu->slb[i].esid & seg_mask) == ea) अणु
			/* Invalidate this entry */
			svcpu->slb[i].esid = 0;
		पूर्ण
	पूर्ण

	svcpu_put(svcpu);
पूर्ण

व्योम kvmppc_mmu_flush_segments(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu = svcpu_get(vcpu);
	svcpu->slb_max = 0;
	svcpu->slb[0].esid = 0;
	svcpu_put(svcpu);
पूर्ण

व्योम kvmppc_mmu_destroy_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_mmu_hpte_destroy(vcpu);
	__destroy_context(to_book3s(vcpu)->context_id[0]);
पूर्ण

पूर्णांक kvmppc_mmu_init_pr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	पूर्णांक err;

	err = hash__alloc_context_id();
	अगर (err < 0)
		वापस -1;
	vcpu3s->context_id[0] = err;

	vcpu3s->proto_vsid_max = ((u64)(vcpu3s->context_id[0] + 1)
				  << ESID_BITS) - 1;
	vcpu3s->proto_vsid_first = (u64)vcpu3s->context_id[0] << ESID_BITS;
	vcpu3s->proto_vsid_next = vcpu3s->proto_vsid_first;

	kvmppc_mmu_hpte_init(vcpu);

	वापस 0;
पूर्ण
