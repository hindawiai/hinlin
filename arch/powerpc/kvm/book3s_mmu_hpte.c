<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 SUSE Linux Products GmbH. All rights reserved.
 *
 * Authors:
 *     Alexander Graf <agraf@suse.de>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/hash.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/hw_irq.h>

#समावेश "trace_pr.h"

#घोषणा PTE_SIZE	12

अटल काष्ठा kmem_cache *hpte_cache;

अटल अंतरभूत u64 kvmppc_mmu_hash_pte(u64 eaddr)
अणु
	वापस hash_64(eaddr >> PTE_SIZE, HPTEG_HASH_BITS_PTE);
पूर्ण

अटल अंतरभूत u64 kvmppc_mmu_hash_pte_दीर्घ(u64 eaddr)
अणु
	वापस hash_64((eaddr & 0x0ffff000) >> PTE_SIZE,
		       HPTEG_HASH_BITS_PTE_LONG);
पूर्ण

अटल अंतरभूत u64 kvmppc_mmu_hash_vpte(u64 vpage)
अणु
	वापस hash_64(vpage & 0xfffffffffULL, HPTEG_HASH_BITS_VPTE);
पूर्ण

अटल अंतरभूत u64 kvmppc_mmu_hash_vpte_दीर्घ(u64 vpage)
अणु
	वापस hash_64((vpage & 0xffffff000ULL) >> 12,
		       HPTEG_HASH_BITS_VPTE_LONG);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल अंतरभूत u64 kvmppc_mmu_hash_vpte_64k(u64 vpage)
अणु
	वापस hash_64((vpage & 0xffffffff0ULL) >> 4,
		       HPTEG_HASH_BITS_VPTE_64K);
पूर्ण
#पूर्ण_अगर

व्योम kvmppc_mmu_hpte_cache_map(काष्ठा kvm_vcpu *vcpu, काष्ठा hpte_cache *pte)
अणु
	u64 index;
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	trace_kvm_book3s_mmu_map(pte);

	spin_lock(&vcpu3s->mmu_lock);

	/* Add to ePTE list */
	index = kvmppc_mmu_hash_pte(pte->pte.eaddr);
	hlist_add_head_rcu(&pte->list_pte, &vcpu3s->hpte_hash_pte[index]);

	/* Add to ePTE_दीर्घ list */
	index = kvmppc_mmu_hash_pte_दीर्घ(pte->pte.eaddr);
	hlist_add_head_rcu(&pte->list_pte_दीर्घ,
			   &vcpu3s->hpte_hash_pte_दीर्घ[index]);

	/* Add to vPTE list */
	index = kvmppc_mmu_hash_vpte(pte->pte.vpage);
	hlist_add_head_rcu(&pte->list_vpte, &vcpu3s->hpte_hash_vpte[index]);

	/* Add to vPTE_दीर्घ list */
	index = kvmppc_mmu_hash_vpte_दीर्घ(pte->pte.vpage);
	hlist_add_head_rcu(&pte->list_vpte_दीर्घ,
			   &vcpu3s->hpte_hash_vpte_दीर्घ[index]);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Add to vPTE_64k list */
	index = kvmppc_mmu_hash_vpte_64k(pte->pte.vpage);
	hlist_add_head_rcu(&pte->list_vpte_64k,
			   &vcpu3s->hpte_hash_vpte_64k[index]);
#पूर्ण_अगर

	vcpu3s->hpte_cache_count++;

	spin_unlock(&vcpu3s->mmu_lock);
पूर्ण

अटल व्योम मुक्त_pte_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा hpte_cache *pte = container_of(head, काष्ठा hpte_cache, rcu_head);
	kmem_cache_मुक्त(hpte_cache, pte);
पूर्ण

अटल व्योम invalidate_pte(काष्ठा kvm_vcpu *vcpu, काष्ठा hpte_cache *pte)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	trace_kvm_book3s_mmu_invalidate(pte);

	/* Dअगरferent क्रम 32 and 64 bit */
	kvmppc_mmu_invalidate_pte(vcpu, pte);

	spin_lock(&vcpu3s->mmu_lock);

	/* pte alपढ़ोy invalidated in between? */
	अगर (hlist_unhashed(&pte->list_pte)) अणु
		spin_unlock(&vcpu3s->mmu_lock);
		वापस;
	पूर्ण

	hlist_del_init_rcu(&pte->list_pte);
	hlist_del_init_rcu(&pte->list_pte_दीर्घ);
	hlist_del_init_rcu(&pte->list_vpte);
	hlist_del_init_rcu(&pte->list_vpte_दीर्घ);
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	hlist_del_init_rcu(&pte->list_vpte_64k);
#पूर्ण_अगर
	vcpu3s->hpte_cache_count--;

	spin_unlock(&vcpu3s->mmu_lock);

	call_rcu(&pte->rcu_head, मुक्त_pte_rcu);
पूर्ण

अटल व्योम kvmppc_mmu_pte_flush_all(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hpte_cache *pte;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < HPTEG_HASH_NUM_VPTE_LONG; i++) अणु
		काष्ठा hlist_head *list = &vcpu3s->hpte_hash_vpte_दीर्घ[i];

		hlist_क्रम_each_entry_rcu(pte, list, list_vpte_दीर्घ)
			invalidate_pte(vcpu, pte);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम kvmppc_mmu_pte_flush_page(काष्ठा kvm_vcpu *vcpu, uदीर्घ guest_ea)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hlist_head *list;
	काष्ठा hpte_cache *pte;

	/* Find the list of entries in the map */
	list = &vcpu3s->hpte_hash_pte[kvmppc_mmu_hash_pte(guest_ea)];

	rcu_पढ़ो_lock();

	/* Check the list क्रम matching entries and invalidate */
	hlist_क्रम_each_entry_rcu(pte, list, list_pte)
		अगर ((pte->pte.eaddr & ~0xfffUL) == guest_ea)
			invalidate_pte(vcpu, pte);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम kvmppc_mmu_pte_flush_दीर्घ(काष्ठा kvm_vcpu *vcpu, uदीर्घ guest_ea)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hlist_head *list;
	काष्ठा hpte_cache *pte;

	/* Find the list of entries in the map */
	list = &vcpu3s->hpte_hash_pte_दीर्घ[
			kvmppc_mmu_hash_pte_दीर्घ(guest_ea)];

	rcu_पढ़ो_lock();

	/* Check the list क्रम matching entries and invalidate */
	hlist_क्रम_each_entry_rcu(pte, list, list_pte_दीर्घ)
		अगर ((pte->pte.eaddr & 0x0ffff000UL) == guest_ea)
			invalidate_pte(vcpu, pte);

	rcu_पढ़ो_unlock();
पूर्ण

व्योम kvmppc_mmu_pte_flush(काष्ठा kvm_vcpu *vcpu, uदीर्घ guest_ea, uदीर्घ ea_mask)
अणु
	trace_kvm_book3s_mmu_flush("", vcpu, guest_ea, ea_mask);
	guest_ea &= ea_mask;

	चयन (ea_mask) अणु
	हाल ~0xfffUL:
		kvmppc_mmu_pte_flush_page(vcpu, guest_ea);
		अवरोध;
	हाल 0x0ffff000:
		kvmppc_mmu_pte_flush_दीर्घ(vcpu, guest_ea);
		अवरोध;
	हाल 0:
		/* Doing a complete flush -> start from scratch */
		kvmppc_mmu_pte_flush_all(vcpu);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

/* Flush with mask 0xfffffffff */
अटल व्योम kvmppc_mmu_pte_vflush_लघु(काष्ठा kvm_vcpu *vcpu, u64 guest_vp)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hlist_head *list;
	काष्ठा hpte_cache *pte;
	u64 vp_mask = 0xfffffffffULL;

	list = &vcpu3s->hpte_hash_vpte[kvmppc_mmu_hash_vpte(guest_vp)];

	rcu_पढ़ो_lock();

	/* Check the list क्रम matching entries and invalidate */
	hlist_क्रम_each_entry_rcu(pte, list, list_vpte)
		अगर ((pte->pte.vpage & vp_mask) == guest_vp)
			invalidate_pte(vcpu, pte);

	rcu_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/* Flush with mask 0xffffffff0 */
अटल व्योम kvmppc_mmu_pte_vflush_64k(काष्ठा kvm_vcpu *vcpu, u64 guest_vp)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hlist_head *list;
	काष्ठा hpte_cache *pte;
	u64 vp_mask = 0xffffffff0ULL;

	list = &vcpu3s->hpte_hash_vpte_64k[
		kvmppc_mmu_hash_vpte_64k(guest_vp)];

	rcu_पढ़ो_lock();

	/* Check the list क्रम matching entries and invalidate */
	hlist_क्रम_each_entry_rcu(pte, list, list_vpte_64k)
		अगर ((pte->pte.vpage & vp_mask) == guest_vp)
			invalidate_pte(vcpu, pte);

	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर

/* Flush with mask 0xffffff000 */
अटल व्योम kvmppc_mmu_pte_vflush_दीर्घ(काष्ठा kvm_vcpu *vcpu, u64 guest_vp)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hlist_head *list;
	काष्ठा hpte_cache *pte;
	u64 vp_mask = 0xffffff000ULL;

	list = &vcpu3s->hpte_hash_vpte_दीर्घ[
		kvmppc_mmu_hash_vpte_दीर्घ(guest_vp)];

	rcu_पढ़ो_lock();

	/* Check the list क्रम matching entries and invalidate */
	hlist_क्रम_each_entry_rcu(pte, list, list_vpte_दीर्घ)
		अगर ((pte->pte.vpage & vp_mask) == guest_vp)
			invalidate_pte(vcpu, pte);

	rcu_पढ़ो_unlock();
पूर्ण

व्योम kvmppc_mmu_pte_vflush(काष्ठा kvm_vcpu *vcpu, u64 guest_vp, u64 vp_mask)
अणु
	trace_kvm_book3s_mmu_flush("v", vcpu, guest_vp, vp_mask);
	guest_vp &= vp_mask;

	चयन(vp_mask) अणु
	हाल 0xfffffffffULL:
		kvmppc_mmu_pte_vflush_लघु(vcpu, guest_vp);
		अवरोध;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल 0xffffffff0ULL:
		kvmppc_mmu_pte_vflush_64k(vcpu, guest_vp);
		अवरोध;
#पूर्ण_अगर
	हाल 0xffffff000ULL:
		kvmppc_mmu_pte_vflush_दीर्घ(vcpu, guest_vp);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण
पूर्ण

व्योम kvmppc_mmu_pte_pflush(काष्ठा kvm_vcpu *vcpu, uदीर्घ pa_start, uदीर्घ pa_end)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hpte_cache *pte;
	पूर्णांक i;

	trace_kvm_book3s_mmu_flush("p", vcpu, pa_start, pa_end);

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < HPTEG_HASH_NUM_VPTE_LONG; i++) अणु
		काष्ठा hlist_head *list = &vcpu3s->hpte_hash_vpte_दीर्घ[i];

		hlist_क्रम_each_entry_rcu(pte, list, list_vpte_दीर्घ)
			अगर ((pte->pte.raddr >= pa_start) &&
			    (pte->pte.raddr < pa_end))
				invalidate_pte(vcpu, pte);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

काष्ठा hpte_cache *kvmppc_mmu_hpte_cache_next(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	काष्ठा hpte_cache *pte;

	अगर (vcpu3s->hpte_cache_count == HPTEG_CACHE_NUM)
		kvmppc_mmu_pte_flush_all(vcpu);

	pte = kmem_cache_zalloc(hpte_cache, GFP_KERNEL);

	वापस pte;
पूर्ण

व्योम kvmppc_mmu_hpte_cache_मुक्त(काष्ठा hpte_cache *pte)
अणु
	kmem_cache_मुक्त(hpte_cache, pte);
पूर्ण

व्योम kvmppc_mmu_hpte_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_mmu_pte_flush(vcpu, 0, 0);
पूर्ण

अटल व्योम kvmppc_mmu_hpte_init_hash(काष्ठा hlist_head *hash_list, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		INIT_HLIST_HEAD(&hash_list[i]);
पूर्ण

पूर्णांक kvmppc_mmu_hpte_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	/* init hpte lookup hashes */
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_pte,
				  ARRAY_SIZE(vcpu3s->hpte_hash_pte));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_pte_दीर्घ,
				  ARRAY_SIZE(vcpu3s->hpte_hash_pte_दीर्घ));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte,
				  ARRAY_SIZE(vcpu3s->hpte_hash_vpte));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte_दीर्घ,
				  ARRAY_SIZE(vcpu3s->hpte_hash_vpte_दीर्घ));
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte_64k,
				  ARRAY_SIZE(vcpu3s->hpte_hash_vpte_64k));
#पूर्ण_अगर

	spin_lock_init(&vcpu3s->mmu_lock);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_mmu_hpte_sysinit(व्योम)
अणु
	/* init hpte slab cache */
	hpte_cache = kmem_cache_create("kvm-spt", माप(काष्ठा hpte_cache),
				       माप(काष्ठा hpte_cache), 0, शून्य);

	वापस 0;
पूर्ण

व्योम kvmppc_mmu_hpte_sysनिकास(व्योम)
अणु
	kmem_cache_destroy(hpte_cache);
पूर्ण
