<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support KVM gust page tracking
 *
 * This feature allows us to track page access in guest. Currently, only
 * ग_लिखो access is tracked.
 *
 * Copyright(C) 2015 Intel Corporation.
 *
 * Author:
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/rculist.h>

#समावेश <यंत्र/kvm_page_track.h>

#समावेश "mmu_internal.h"

व्योम kvm_page_track_मुक्त_memslot(काष्ठा kvm_memory_slot *slot)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KVM_PAGE_TRACK_MAX; i++) अणु
		kvमुक्त(slot->arch.gfn_track[i]);
		slot->arch.gfn_track[i] = शून्य;
	पूर्ण
पूर्ण

पूर्णांक kvm_page_track_create_memslot(काष्ठा kvm_memory_slot *slot,
				  अचिन्हित दीर्घ npages)
अणु
	पूर्णांक  i;

	क्रम (i = 0; i < KVM_PAGE_TRACK_MAX; i++) अणु
		slot->arch.gfn_track[i] =
			kvसुस्मृति(npages, माप(*slot->arch.gfn_track[i]),
				 GFP_KERNEL_ACCOUNT);
		अगर (!slot->arch.gfn_track[i])
			जाओ track_मुक्त;
	पूर्ण

	वापस 0;

track_मुक्त:
	kvm_page_track_मुक्त_memslot(slot);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत bool page_track_mode_is_valid(क्रमागत kvm_page_track_mode mode)
अणु
	अगर (mode < 0 || mode >= KVM_PAGE_TRACK_MAX)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम update_gfn_track(काष्ठा kvm_memory_slot *slot, gfn_t gfn,
			     क्रमागत kvm_page_track_mode mode, लघु count)
अणु
	पूर्णांक index, val;

	index = gfn_to_index(gfn, slot->base_gfn, PG_LEVEL_4K);

	val = slot->arch.gfn_track[mode][index];

	अगर (WARN_ON(val + count < 0 || val + count > अच_लघु_उच्च))
		वापस;

	slot->arch.gfn_track[mode][index] += count;
पूर्ण

/*
 * add guest page to the tracking pool so that corresponding access on that
 * page will be पूर्णांकercepted.
 *
 * It should be called under the protection both of mmu-lock and kvm->srcu
 * or kvm->slots_lock.
 *
 * @kvm: the guest instance we are पूर्णांकerested in.
 * @slot: the @gfn beदीर्घs to.
 * @gfn: the guest page.
 * @mode: tracking mode, currently only ग_लिखो track is supported.
 */
व्योम kvm_slot_page_track_add_page(काष्ठा kvm *kvm,
				  काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				  क्रमागत kvm_page_track_mode mode)
अणु

	अगर (WARN_ON(!page_track_mode_is_valid(mode)))
		वापस;

	update_gfn_track(slot, gfn, mode, 1);

	/*
	 * new track stops large page mapping क्रम the
	 * tracked page.
	 */
	kvm_mmu_gfn_disallow_lpage(slot, gfn);

	अगर (mode == KVM_PAGE_TRACK_WRITE)
		अगर (kvm_mmu_slot_gfn_ग_लिखो_protect(kvm, slot, gfn))
			kvm_flush_remote_tlbs(kvm);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_slot_page_track_add_page);

/*
 * हटाओ the guest page from the tracking pool which stops the पूर्णांकerception
 * of corresponding access on that page. It is the opposed operation of
 * kvm_slot_page_track_add_page().
 *
 * It should be called under the protection both of mmu-lock and kvm->srcu
 * or kvm->slots_lock.
 *
 * @kvm: the guest instance we are पूर्णांकerested in.
 * @slot: the @gfn beदीर्घs to.
 * @gfn: the guest page.
 * @mode: tracking mode, currently only ग_लिखो track is supported.
 */
व्योम kvm_slot_page_track_हटाओ_page(काष्ठा kvm *kvm,
				     काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				     क्रमागत kvm_page_track_mode mode)
अणु
	अगर (WARN_ON(!page_track_mode_is_valid(mode)))
		वापस;

	update_gfn_track(slot, gfn, mode, -1);

	/*
	 * allow large page mapping क्रम the tracked page
	 * after the tracker is gone.
	 */
	kvm_mmu_gfn_allow_lpage(slot, gfn);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_slot_page_track_हटाओ_page);

/*
 * check अगर the corresponding access on the specअगरied guest page is tracked.
 */
bool kvm_page_track_is_active(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
			      क्रमागत kvm_page_track_mode mode)
अणु
	काष्ठा kvm_memory_slot *slot;
	पूर्णांक index;

	अगर (WARN_ON(!page_track_mode_is_valid(mode)))
		वापस false;

	slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);
	अगर (!slot)
		वापस false;

	index = gfn_to_index(gfn, slot->base_gfn, PG_LEVEL_4K);
	वापस !!READ_ONCE(slot->arch.gfn_track[mode][index]);
पूर्ण

व्योम kvm_page_track_cleanup(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_page_track_notअगरier_head *head;

	head = &kvm->arch.track_notअगरier_head;
	cleanup_srcu_काष्ठा(&head->track_srcu);
पूर्ण

व्योम kvm_page_track_init(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_page_track_notअगरier_head *head;

	head = &kvm->arch.track_notअगरier_head;
	init_srcu_काष्ठा(&head->track_srcu);
	INIT_HLIST_HEAD(&head->track_notअगरier_list);
पूर्ण

/*
 * रेजिस्टर the notअगरier so that event पूर्णांकerception क्रम the tracked guest
 * pages can be received.
 */
व्योम
kvm_page_track_रेजिस्टर_notअगरier(काष्ठा kvm *kvm,
				 काष्ठा kvm_page_track_notअगरier_node *n)
अणु
	काष्ठा kvm_page_track_notअगरier_head *head;

	head = &kvm->arch.track_notअगरier_head;

	ग_लिखो_lock(&kvm->mmu_lock);
	hlist_add_head_rcu(&n->node, &head->track_notअगरier_list);
	ग_लिखो_unlock(&kvm->mmu_lock);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_page_track_रेजिस्टर_notअगरier);

/*
 * stop receiving the event पूर्णांकerception. It is the opposed operation of
 * kvm_page_track_रेजिस्टर_notअगरier().
 */
व्योम
kvm_page_track_unरेजिस्टर_notअगरier(काष्ठा kvm *kvm,
				   काष्ठा kvm_page_track_notअगरier_node *n)
अणु
	काष्ठा kvm_page_track_notअगरier_head *head;

	head = &kvm->arch.track_notअगरier_head;

	ग_लिखो_lock(&kvm->mmu_lock);
	hlist_del_rcu(&n->node);
	ग_लिखो_unlock(&kvm->mmu_lock);
	synchronize_srcu(&head->track_srcu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_page_track_unरेजिस्टर_notअगरier);

/*
 * Notअगरy the node that ग_लिखो access is पूर्णांकercepted and ग_लिखो emulation is
 * finished at this समय.
 *
 * The node should figure out अगर the written page is the one that node is
 * पूर्णांकerested in by itself.
 */
व्योम kvm_page_track_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, स्थिर u8 *new,
			  पूर्णांक bytes)
अणु
	काष्ठा kvm_page_track_notअगरier_head *head;
	काष्ठा kvm_page_track_notअगरier_node *n;
	पूर्णांक idx;

	head = &vcpu->kvm->arch.track_notअगरier_head;

	अगर (hlist_empty(&head->track_notअगरier_list))
		वापस;

	idx = srcu_पढ़ो_lock(&head->track_srcu);
	hlist_क्रम_each_entry_srcu(n, &head->track_notअगरier_list, node,
				srcu_पढ़ो_lock_held(&head->track_srcu))
		अगर (n->track_ग_लिखो)
			n->track_ग_लिखो(vcpu, gpa, new, bytes, n);
	srcu_पढ़ो_unlock(&head->track_srcu, idx);
पूर्ण

/*
 * Notअगरy the node that memory slot is being हटाओd or moved so that it can
 * drop ग_लिखो-protection क्रम the pages in the memory slot.
 *
 * The node should figure out it has any ग_लिखो-रक्षित pages in this slot
 * by itself.
 */
व्योम kvm_page_track_flush_slot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
	काष्ठा kvm_page_track_notअगरier_head *head;
	काष्ठा kvm_page_track_notअगरier_node *n;
	पूर्णांक idx;

	head = &kvm->arch.track_notअगरier_head;

	अगर (hlist_empty(&head->track_notअगरier_list))
		वापस;

	idx = srcu_पढ़ो_lock(&head->track_srcu);
	hlist_क्रम_each_entry_srcu(n, &head->track_notअगरier_list, node,
				srcu_पढ़ो_lock_held(&head->track_srcu))
		अगर (n->track_flush_slot)
			n->track_flush_slot(kvm, slot, n);
	srcu_पढ़ो_unlock(&head->track_srcu, idx);
पूर्ण
