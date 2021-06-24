<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __KVM_TYPES_H__
#घोषणा __KVM_TYPES_H__

काष्ठा kvm;
काष्ठा kvm_async_pf;
काष्ठा kvm_device_ops;
काष्ठा kvm_पूर्णांकerrupt;
काष्ठा kvm_irq_routing_table;
काष्ठा kvm_memory_slot;
काष्ठा kvm_one_reg;
काष्ठा kvm_run;
काष्ठा kvm_userspace_memory_region;
काष्ठा kvm_vcpu;
काष्ठा kvm_vcpu_init;
काष्ठा kvm_memslots;

क्रमागत kvm_mr_change;

#समावेश <linux/types.h>

#समावेश <यंत्र/kvm_types.h>

/*
 * Address types:
 *
 *  gva - guest भव address
 *  gpa - guest physical address
 *  gfn - guest frame number
 *  hva - host भव address
 *  hpa - host physical address
 *  hfn - host frame number
 */

प्रकार अचिन्हित दीर्घ  gva_t;
प्रकार u64            gpa_t;
प्रकार u64            gfn_t;

#घोषणा GPA_INVALID	(~(gpa_t)0)

प्रकार अचिन्हित दीर्घ  hva_t;
प्रकार u64            hpa_t;
प्रकार u64            hfn_t;

प्रकार hfn_t kvm_pfn_t;

काष्ठा gfn_to_hva_cache अणु
	u64 generation;
	gpa_t gpa;
	अचिन्हित दीर्घ hva;
	अचिन्हित दीर्घ len;
	काष्ठा kvm_memory_slot *memslot;
पूर्ण;

काष्ठा gfn_to_pfn_cache अणु
	u64 generation;
	gfn_t gfn;
	kvm_pfn_t pfn;
	bool dirty;
पूर्ण;

#अगर_घोषित KVM_ARCH_NR_OBJS_PER_MEMORY_CACHE
/*
 * Memory caches are used to pपुनः_स्मृतिate memory ahead of various MMU flows,
 * e.g. page fault handlers.  Gracefully handling allocation failures deep in
 * MMU flows is problematic, as is triggering reclaim, I/O, etc... जबतक
 * holding MMU locks.  Note, these caches act more like prefetch buffers than
 * classical caches, i.e. objects are not वापसed to the cache on being मुक्तd.
 */
काष्ठा kvm_mmu_memory_cache अणु
	पूर्णांक nobjs;
	gfp_t gfp_zero;
	काष्ठा kmem_cache *kmem_cache;
	व्योम *objects[KVM_ARCH_NR_OBJS_PER_MEMORY_CACHE];
पूर्ण;
#पूर्ण_अगर


#पूर्ण_अगर /* __KVM_TYPES_H__ */
