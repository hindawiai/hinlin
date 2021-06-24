<शैली गुरु>
#अगर_अघोषित KVM_सूचीTY_RING_H
#घोषणा KVM_सूचीTY_RING_H

#समावेश <linux/kvm.h>

/**
 * kvm_dirty_ring: KVM पूर्णांकernal dirty ring काष्ठाure
 *
 * @dirty_index: मुक्त running counter that poपूर्णांकs to the next slot in
 *               dirty_ring->dirty_gfns, where a new dirty page should go
 * @reset_index: मुक्त running counter that poपूर्णांकs to the next dirty page
 *               in dirty_ring->dirty_gfns क्रम which dirty trap needs to
 *               be reenabled
 * @size:        size of the compact list, dirty_ring->dirty_gfns
 * @soft_limit:  when the number of dirty pages in the list reaches this
 *               limit, vcpu that owns this ring should निकास to userspace
 *               to allow userspace to harvest all the dirty pages
 * @dirty_gfns:  the array to keep the dirty gfns
 * @index:       index of this dirty ring
 */
काष्ठा kvm_dirty_ring अणु
	u32 dirty_index;
	u32 reset_index;
	u32 size;
	u32 soft_limit;
	काष्ठा kvm_dirty_gfn *dirty_gfns;
	पूर्णांक index;
पूर्ण;

#अगर (KVM_सूचीTY_LOG_PAGE_OFFSET == 0)
/*
 * If KVM_सूचीTY_LOG_PAGE_OFFSET not defined, kvm_dirty_ring.o should
 * not be included as well, so define these nop functions क्रम the arch.
 */
अटल अंतरभूत u32 kvm_dirty_ring_get_rsvd_entries(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_dirty_ring_alloc(काष्ठा kvm_dirty_ring *ring,
				       पूर्णांक index, u32 size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा kvm_dirty_ring *kvm_dirty_ring_get(काष्ठा kvm *kvm)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_dirty_ring_reset(काष्ठा kvm *kvm,
				       काष्ठा kvm_dirty_ring *ring)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kvm_dirty_ring_push(काष्ठा kvm_dirty_ring *ring,
				       u32 slot, u64 offset)
अणु
पूर्ण

अटल अंतरभूत काष्ठा page *kvm_dirty_ring_get_page(काष्ठा kvm_dirty_ring *ring,
						   u32 offset)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम kvm_dirty_ring_मुक्त(काष्ठा kvm_dirty_ring *ring)
अणु
पूर्ण

अटल अंतरभूत bool kvm_dirty_ring_soft_full(काष्ठा kvm_dirty_ring *ring)
अणु
	वापस true;
पूर्ण

#अन्यथा /* KVM_सूचीTY_LOG_PAGE_OFFSET == 0 */

u32 kvm_dirty_ring_get_rsvd_entries(व्योम);
पूर्णांक kvm_dirty_ring_alloc(काष्ठा kvm_dirty_ring *ring, पूर्णांक index, u32 size);
काष्ठा kvm_dirty_ring *kvm_dirty_ring_get(काष्ठा kvm *kvm);

/*
 * called with kvm->slots_lock held, वापसs the number of
 * processed pages.
 */
पूर्णांक kvm_dirty_ring_reset(काष्ठा kvm *kvm, काष्ठा kvm_dirty_ring *ring);

/*
 * वापसs =0: successfully pushed
 *         <0: unable to push, need to रुको
 */
व्योम kvm_dirty_ring_push(काष्ठा kvm_dirty_ring *ring, u32 slot, u64 offset);

/* क्रम use in vm_operations_काष्ठा */
काष्ठा page *kvm_dirty_ring_get_page(काष्ठा kvm_dirty_ring *ring, u32 offset);

व्योम kvm_dirty_ring_मुक्त(काष्ठा kvm_dirty_ring *ring);
bool kvm_dirty_ring_soft_full(काष्ठा kvm_dirty_ring *ring);

#पूर्ण_अगर /* KVM_सूचीTY_LOG_PAGE_OFFSET == 0 */

#पूर्ण_अगर	/* KVM_सूचीTY_RING_H */
