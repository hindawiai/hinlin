<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_KVM_PAGE_TRACK_H
#घोषणा _ASM_X86_KVM_PAGE_TRACK_H

क्रमागत kvm_page_track_mode अणु
	KVM_PAGE_TRACK_WRITE,
	KVM_PAGE_TRACK_MAX,
पूर्ण;

/*
 * The notअगरier represented by @kvm_page_track_notअगरier_node is linked पूर्णांकo
 * the head which will be notअगरied when guest is triggering the track event.
 *
 * Write access on the head is रक्षित by kvm->mmu_lock, पढ़ो access
 * is रक्षित by track_srcu.
 */
काष्ठा kvm_page_track_notअगरier_head अणु
	काष्ठा srcu_काष्ठा track_srcu;
	काष्ठा hlist_head track_notअगरier_list;
पूर्ण;

काष्ठा kvm_page_track_notअगरier_node अणु
	काष्ठा hlist_node node;

	/*
	 * It is called when guest is writing the ग_लिखो-tracked page
	 * and ग_लिखो emulation is finished at that समय.
	 *
	 * @vcpu: the vcpu where the ग_लिखो access happened.
	 * @gpa: the physical address written by guest.
	 * @new: the data was written to the address.
	 * @bytes: the written length.
	 * @node: this node
	 */
	व्योम (*track_ग_लिखो)(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, स्थिर u8 *new,
			    पूर्णांक bytes, काष्ठा kvm_page_track_notअगरier_node *node);
	/*
	 * It is called when memory slot is being moved or हटाओd
	 * users can drop ग_लिखो-protection क्रम the pages in that memory slot
	 *
	 * @kvm: the kvm where memory slot being moved or हटाओd
	 * @slot: the memory slot being moved or हटाओd
	 * @node: this node
	 */
	व्योम (*track_flush_slot)(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot,
			    काष्ठा kvm_page_track_notअगरier_node *node);
पूर्ण;

व्योम kvm_page_track_init(काष्ठा kvm *kvm);
व्योम kvm_page_track_cleanup(काष्ठा kvm *kvm);

व्योम kvm_page_track_मुक्त_memslot(काष्ठा kvm_memory_slot *slot);
पूर्णांक kvm_page_track_create_memslot(काष्ठा kvm_memory_slot *slot,
				  अचिन्हित दीर्घ npages);

व्योम kvm_slot_page_track_add_page(काष्ठा kvm *kvm,
				  काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				  क्रमागत kvm_page_track_mode mode);
व्योम kvm_slot_page_track_हटाओ_page(काष्ठा kvm *kvm,
				     काष्ठा kvm_memory_slot *slot, gfn_t gfn,
				     क्रमागत kvm_page_track_mode mode);
bool kvm_page_track_is_active(काष्ठा kvm_vcpu *vcpu, gfn_t gfn,
			      क्रमागत kvm_page_track_mode mode);

व्योम
kvm_page_track_रेजिस्टर_notअगरier(काष्ठा kvm *kvm,
				 काष्ठा kvm_page_track_notअगरier_node *n);
व्योम
kvm_page_track_unरेजिस्टर_notअगरier(काष्ठा kvm *kvm,
				   काष्ठा kvm_page_track_notअगरier_node *n);
व्योम kvm_page_track_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, स्थिर u8 *new,
			  पूर्णांक bytes);
व्योम kvm_page_track_flush_slot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot);
#पूर्ण_अगर
