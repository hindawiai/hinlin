<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * KVM dirty ring implementation
 *
 * Copyright 2019 Red Hat, Inc.
 */
#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kvm_dirty_ring.h>
#समावेश <trace/events/kvm.h>
#समावेश "mmu_lock.h"

पूर्णांक __weak kvm_cpu_dirty_log_size(व्योम)
अणु
	वापस 0;
पूर्ण

u32 kvm_dirty_ring_get_rsvd_entries(व्योम)
अणु
	वापस KVM_सूचीTY_RING_RSVD_ENTRIES + kvm_cpu_dirty_log_size();
पूर्ण

अटल u32 kvm_dirty_ring_used(काष्ठा kvm_dirty_ring *ring)
अणु
	वापस READ_ONCE(ring->dirty_index) - READ_ONCE(ring->reset_index);
पूर्ण

bool kvm_dirty_ring_soft_full(काष्ठा kvm_dirty_ring *ring)
अणु
	वापस kvm_dirty_ring_used(ring) >= ring->soft_limit;
पूर्ण

अटल bool kvm_dirty_ring_full(काष्ठा kvm_dirty_ring *ring)
अणु
	वापस kvm_dirty_ring_used(ring) >= ring->size;
पूर्ण

काष्ठा kvm_dirty_ring *kvm_dirty_ring_get(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vcpu *vcpu = kvm_get_running_vcpu();

	WARN_ON_ONCE(vcpu->kvm != kvm);

	वापस &vcpu->dirty_ring;
पूर्ण

अटल व्योम kvm_reset_dirty_gfn(काष्ठा kvm *kvm, u32 slot, u64 offset, u64 mask)
अणु
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक as_id, id;

	as_id = slot >> 16;
	id = (u16)slot;

	अगर (as_id >= KVM_ADDRESS_SPACE_NUM || id >= KVM_USER_MEM_SLOTS)
		वापस;

	memslot = id_to_memslot(__kvm_memslots(kvm, as_id), id);

	अगर (!memslot || (offset + __fls(mask)) >= memslot->npages)
		वापस;

	KVM_MMU_LOCK(kvm);
	kvm_arch_mmu_enable_log_dirty_pt_masked(kvm, memslot, offset, mask);
	KVM_MMU_UNLOCK(kvm);
पूर्ण

पूर्णांक kvm_dirty_ring_alloc(काष्ठा kvm_dirty_ring *ring, पूर्णांक index, u32 size)
अणु
	ring->dirty_gfns = vzalloc(size);
	अगर (!ring->dirty_gfns)
		वापस -ENOMEM;

	ring->size = size / माप(काष्ठा kvm_dirty_gfn);
	ring->soft_limit = ring->size - kvm_dirty_ring_get_rsvd_entries();
	ring->dirty_index = 0;
	ring->reset_index = 0;
	ring->index = index;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kvm_dirty_gfn_set_invalid(काष्ठा kvm_dirty_gfn *gfn)
अणु
	gfn->flags = 0;
पूर्ण

अटल अंतरभूत व्योम kvm_dirty_gfn_set_dirtied(काष्ठा kvm_dirty_gfn *gfn)
अणु
	gfn->flags = KVM_सूचीTY_GFN_F_सूचीTY;
पूर्ण

अटल अंतरभूत bool kvm_dirty_gfn_invalid(काष्ठा kvm_dirty_gfn *gfn)
अणु
	वापस gfn->flags == 0;
पूर्ण

अटल अंतरभूत bool kvm_dirty_gfn_harvested(काष्ठा kvm_dirty_gfn *gfn)
अणु
	वापस gfn->flags & KVM_सूचीTY_GFN_F_RESET;
पूर्ण

पूर्णांक kvm_dirty_ring_reset(काष्ठा kvm *kvm, काष्ठा kvm_dirty_ring *ring)
अणु
	u32 cur_slot, next_slot;
	u64 cur_offset, next_offset;
	अचिन्हित दीर्घ mask;
	पूर्णांक count = 0;
	काष्ठा kvm_dirty_gfn *entry;
	bool first_round = true;

	/* This is only needed to make compilers happy */
	cur_slot = cur_offset = mask = 0;

	जबतक (true) अणु
		entry = &ring->dirty_gfns[ring->reset_index & (ring->size - 1)];

		अगर (!kvm_dirty_gfn_harvested(entry))
			अवरोध;

		next_slot = READ_ONCE(entry->slot);
		next_offset = READ_ONCE(entry->offset);

		/* Update the flags to reflect that this GFN is reset */
		kvm_dirty_gfn_set_invalid(entry);

		ring->reset_index++;
		count++;
		/*
		 * Try to coalesce the reset operations when the guest is
		 * scanning pages in the same slot.
		 */
		अगर (!first_round && next_slot == cur_slot) अणु
			s64 delta = next_offset - cur_offset;

			अगर (delta >= 0 && delta < BITS_PER_LONG) अणु
				mask |= 1ull << delta;
				जारी;
			पूर्ण

			/* Backwards visit, careful about overflows!  */
			अगर (delta > -BITS_PER_LONG && delta < 0 &&
			    (mask << -delta >> -delta) == mask) अणु
				cur_offset = next_offset;
				mask = (mask << -delta) | 1;
				जारी;
			पूर्ण
		पूर्ण
		kvm_reset_dirty_gfn(kvm, cur_slot, cur_offset, mask);
		cur_slot = next_slot;
		cur_offset = next_offset;
		mask = 1;
		first_round = false;
	पूर्ण

	kvm_reset_dirty_gfn(kvm, cur_slot, cur_offset, mask);

	trace_kvm_dirty_ring_reset(ring);

	वापस count;
पूर्ण

व्योम kvm_dirty_ring_push(काष्ठा kvm_dirty_ring *ring, u32 slot, u64 offset)
अणु
	काष्ठा kvm_dirty_gfn *entry;

	/* It should never get full */
	WARN_ON_ONCE(kvm_dirty_ring_full(ring));

	entry = &ring->dirty_gfns[ring->dirty_index & (ring->size - 1)];

	entry->slot = slot;
	entry->offset = offset;
	/*
	 * Make sure the data is filled in beक्रमe we publish this to
	 * the userspace program.  There's no paired kernel-side पढ़ोer.
	 */
	smp_wmb();
	kvm_dirty_gfn_set_dirtied(entry);
	ring->dirty_index++;
	trace_kvm_dirty_ring_push(ring, slot, offset);
पूर्ण

काष्ठा page *kvm_dirty_ring_get_page(काष्ठा kvm_dirty_ring *ring, u32 offset)
अणु
	वापस vदो_स्मृति_to_page((व्योम *)ring->dirty_gfns + offset * PAGE_SIZE);
पूर्ण

व्योम kvm_dirty_ring_मुक्त(काष्ठा kvm_dirty_ring *ring)
अणु
	vमुक्त(ring->dirty_gfns);
	ring->dirty_gfns = शून्य;
पूर्ण
