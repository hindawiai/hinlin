<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google LLC
 * Author: Will Deacon <will@kernel.org>
 */

#अगर_अघोषित __ARM64_KVM_PGTABLE_H__
#घोषणा __ARM64_KVM_PGTABLE_H__

#समावेश <linux/bits.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/types.h>

#घोषणा KVM_PGTABLE_MAX_LEVELS		4U

अटल अंतरभूत u64 kvm_get_parange(u64 mmfr0)
अणु
	u64 parange = cpuid_feature_extract_अचिन्हित_field(mmfr0,
				ID_AA64MMFR0_PARANGE_SHIFT);
	अगर (parange > ID_AA64MMFR0_PARANGE_MAX)
		parange = ID_AA64MMFR0_PARANGE_MAX;

	वापस parange;
पूर्ण

प्रकार u64 kvm_pte_t;

/**
 * काष्ठा kvm_pgtable_mm_ops - Memory management callbacks.
 * @zalloc_page:	Allocate a single zeroed memory page. The @arg parameter
 *			can be used by the walker to pass a memcache. The
 *			initial refcount of the page is 1.
 * @zalloc_pages_exact:	Allocate an exact number of zeroed memory pages. The
 *			@size parameter is in bytes, and is rounded-up to the
 *			next page boundary. The resulting allocation is
 *			physically contiguous.
 * @मुक्त_pages_exact:	Free an exact number of memory pages previously
 *			allocated by zalloc_pages_exact.
 * @get_page:		Increment the refcount on a page.
 * @put_page:		Decrement the refcount on a page. When the refcount
 *			reaches 0 the page is स्वतःmatically मुक्तd.
 * @page_count:		Return the refcount of a page.
 * @phys_to_virt:	Convert a physical address पूर्णांकo a भव address mapped
 *			in the current context.
 * @virt_to_phys:	Convert a भव address mapped in the current context
 *			पूर्णांकo a physical address.
 */
काष्ठा kvm_pgtable_mm_ops अणु
	व्योम*		(*zalloc_page)(व्योम *arg);
	व्योम*		(*zalloc_pages_exact)(माप_प्रकार size);
	व्योम		(*मुक्त_pages_exact)(व्योम *addr, माप_प्रकार size);
	व्योम		(*get_page)(व्योम *addr);
	व्योम		(*put_page)(व्योम *addr);
	पूर्णांक		(*page_count)(व्योम *addr);
	व्योम*		(*phys_to_virt)(phys_addr_t phys);
	phys_addr_t	(*virt_to_phys)(व्योम *addr);
पूर्ण;

/**
 * क्रमागत kvm_pgtable_stage2_flags - Stage-2 page-table flags.
 * @KVM_PGTABLE_S2_NOFWB:	Don't enक्रमce Normal-WB even अगर the CPUs have
 *				ARM64_HAS_STAGE2_FWB.
 * @KVM_PGTABLE_S2_IDMAP:	Only use identity mappings.
 */
क्रमागत kvm_pgtable_stage2_flags अणु
	KVM_PGTABLE_S2_NOFWB			= BIT(0),
	KVM_PGTABLE_S2_IDMAP			= BIT(1),
पूर्ण;

/**
 * काष्ठा kvm_pgtable - KVM page-table.
 * @ia_bits:		Maximum input address size, in bits.
 * @start_level:	Level at which the page-table walk starts.
 * @pgd:		Poपूर्णांकer to the first top-level entry of the page-table.
 * @mm_ops:		Memory management callbacks.
 * @mmu:		Stage-2 KVM MMU काष्ठा. Unused क्रम stage-1 page-tables.
 */
काष्ठा kvm_pgtable अणु
	u32					ia_bits;
	u32					start_level;
	kvm_pte_t				*pgd;
	काष्ठा kvm_pgtable_mm_ops		*mm_ops;

	/* Stage-2 only */
	काष्ठा kvm_s2_mmu			*mmu;
	क्रमागत kvm_pgtable_stage2_flags		flags;
पूर्ण;

/**
 * क्रमागत kvm_pgtable_prot - Page-table permissions and attributes.
 * @KVM_PGTABLE_PROT_X:		Execute permission.
 * @KVM_PGTABLE_PROT_W:		Write permission.
 * @KVM_PGTABLE_PROT_R:		Read permission.
 * @KVM_PGTABLE_PROT_DEVICE:	Device attributes.
 */
क्रमागत kvm_pgtable_prot अणु
	KVM_PGTABLE_PROT_X			= BIT(0),
	KVM_PGTABLE_PROT_W			= BIT(1),
	KVM_PGTABLE_PROT_R			= BIT(2),

	KVM_PGTABLE_PROT_DEVICE			= BIT(3),
पूर्ण;

#घोषणा PAGE_HYP		(KVM_PGTABLE_PROT_R | KVM_PGTABLE_PROT_W)
#घोषणा PAGE_HYP_EXEC		(KVM_PGTABLE_PROT_R | KVM_PGTABLE_PROT_X)
#घोषणा PAGE_HYP_RO		(KVM_PGTABLE_PROT_R)
#घोषणा PAGE_HYP_DEVICE		(PAGE_HYP | KVM_PGTABLE_PROT_DEVICE)

/**
 * काष्ठा kvm_mem_range - Range of Intermediate Physical Addresses
 * @start:	Start of the range.
 * @end:	End of the range.
 */
काष्ठा kvm_mem_range अणु
	u64 start;
	u64 end;
पूर्ण;

/**
 * क्रमागत kvm_pgtable_walk_flags - Flags to control a depth-first page-table walk.
 * @KVM_PGTABLE_WALK_LEAF:		Visit leaf entries, including invalid
 *					entries.
 * @KVM_PGTABLE_WALK_TABLE_PRE:		Visit table entries beक्रमe their
 *					children.
 * @KVM_PGTABLE_WALK_TABLE_POST:	Visit table entries after their
 *					children.
 */
क्रमागत kvm_pgtable_walk_flags अणु
	KVM_PGTABLE_WALK_LEAF			= BIT(0),
	KVM_PGTABLE_WALK_TABLE_PRE		= BIT(1),
	KVM_PGTABLE_WALK_TABLE_POST		= BIT(2),
पूर्ण;

प्रकार पूर्णांक (*kvm_pgtable_visitor_fn_t)(u64 addr, u64 end, u32 level,
					kvm_pte_t *ptep,
					क्रमागत kvm_pgtable_walk_flags flag,
					व्योम * स्थिर arg);

/**
 * काष्ठा kvm_pgtable_walker - Hook पूर्णांकo a page-table walk.
 * @cb:		Callback function to invoke during the walk.
 * @arg:	Argument passed to the callback function.
 * @flags:	Bitwise-OR of flags to identअगरy the entry types on which to
 *		invoke the callback function.
 */
काष्ठा kvm_pgtable_walker अणु
	स्थिर kvm_pgtable_visitor_fn_t		cb;
	व्योम * स्थिर				arg;
	स्थिर क्रमागत kvm_pgtable_walk_flags	flags;
पूर्ण;

/**
 * kvm_pgtable_hyp_init() - Initialise a hypervisor stage-1 page-table.
 * @pgt:	Uninitialised page-table काष्ठाure to initialise.
 * @va_bits:	Maximum भव address bits.
 * @mm_ops:	Memory management callbacks.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_hyp_init(काष्ठा kvm_pgtable *pgt, u32 va_bits,
			 काष्ठा kvm_pgtable_mm_ops *mm_ops);

/**
 * kvm_pgtable_hyp_destroy() - Destroy an unused hypervisor stage-1 page-table.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_hyp_init().
 *
 * The page-table is assumed to be unreachable by any hardware walkers prior
 * to मुक्तing and thereक्रमe no TLB invalidation is perक्रमmed.
 */
व्योम kvm_pgtable_hyp_destroy(काष्ठा kvm_pgtable *pgt);

/**
 * kvm_pgtable_hyp_map() - Install a mapping in a hypervisor stage-1 page-table.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_hyp_init().
 * @addr:	Virtual address at which to place the mapping.
 * @size:	Size of the mapping.
 * @phys:	Physical address of the memory to map.
 * @prot:	Permissions and attributes क्रम the mapping.
 *
 * The offset of @addr within a page is ignored, @size is rounded-up to
 * the next page boundary and @phys is rounded-करोwn to the previous page
 * boundary.
 *
 * If device attributes are not explicitly requested in @prot, then the
 * mapping will be normal, cacheable. Attempts to install a new mapping
 * क्रम a भव address that is alपढ़ोy mapped will be rejected with an
 * error and a WARN().
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_hyp_map(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size, u64 phys,
			क्रमागत kvm_pgtable_prot prot);

/**
 * kvm_get_vtcr() - Helper to स्थिरruct VTCR_EL2
 * @mmfr0:	Sanitized value of SYS_ID_AA64MMFR0_EL1 रेजिस्टर.
 * @mmfr1:	Sanitized value of SYS_ID_AA64MMFR1_EL1 रेजिस्टर.
 * @phys_shfit:	Value to set in VTCR_EL2.T0SZ.
 *
 * The VTCR value is common across all the physical CPUs on the प्रणाली.
 * We use प्रणाली wide sanitised values to fill in dअगरferent fields,
 * except क्रम Hardware Management of Access Flags. HA Flag is set
 * unconditionally on all CPUs, as it is safe to run with or without
 * the feature and the bit is RES0 on CPUs that करोn't support it.
 *
 * Return: VTCR_EL2 value
 */
u64 kvm_get_vtcr(u64 mmfr0, u64 mmfr1, u32 phys_shअगरt);

/**
 * kvm_pgtable_stage2_init_flags() - Initialise a guest stage-2 page-table.
 * @pgt:	Uninitialised page-table काष्ठाure to initialise.
 * @arch:	Arch-specअगरic KVM काष्ठाure representing the guest भव
 *		machine.
 * @mm_ops:	Memory management callbacks.
 * @flags:	Stage-2 configuration flags.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_init_flags(काष्ठा kvm_pgtable *pgt, काष्ठा kvm_arch *arch,
				  काष्ठा kvm_pgtable_mm_ops *mm_ops,
				  क्रमागत kvm_pgtable_stage2_flags flags);

#घोषणा kvm_pgtable_stage2_init(pgt, arch, mm_ops) \
	kvm_pgtable_stage2_init_flags(pgt, arch, mm_ops, 0)

/**
 * kvm_pgtable_stage2_destroy() - Destroy an unused guest stage-2 page-table.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 *
 * The page-table is assumed to be unreachable by any hardware walkers prior
 * to मुक्तing and thereक्रमe no TLB invalidation is perक्रमmed.
 */
व्योम kvm_pgtable_stage2_destroy(काष्ठा kvm_pgtable *pgt);

/**
 * kvm_pgtable_stage2_map() - Install a mapping in a guest stage-2 page-table.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address at which to place the mapping.
 * @size:	Size of the mapping.
 * @phys:	Physical address of the memory to map.
 * @prot:	Permissions and attributes क्रम the mapping.
 * @mc:		Cache of pre-allocated and zeroed memory from which to allocate
 *		page-table pages.
 *
 * The offset of @addr within a page is ignored, @size is rounded-up to
 * the next page boundary and @phys is rounded-करोwn to the previous page
 * boundary.
 *
 * If device attributes are not explicitly requested in @prot, then the
 * mapping will be normal, cacheable.
 *
 * Note that the update of a valid leaf PTE in this function will be पातed,
 * अगर it's trying to recreate the exact same mapping or only change the access
 * permissions. Instead, the vCPU will निकास one more समय from guest अगर still
 * needed and then go through the path of relaxing permissions.
 *
 * Note that this function will both coalesce existing table entries and split
 * existing block mappings, relying on page-faults to fault back areas outside
 * of the new mapping lazily.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_map(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size,
			   u64 phys, क्रमागत kvm_pgtable_prot prot,
			   व्योम *mc);

/**
 * kvm_pgtable_stage2_set_owner() - Unmap and annotate pages in the IPA space to
 *				    track ownership.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Base पूर्णांकermediate physical address to annotate.
 * @size:	Size of the annotated range.
 * @mc:		Cache of pre-allocated and zeroed memory from which to allocate
 *		page-table pages.
 * @owner_id:	Unique identअगरier क्रम the owner of the page.
 *
 * By शेष, all page-tables are owned by identअगरier 0. This function can be
 * used to mark portions of the IPA space as owned by other entities. When a
 * stage 2 is used with identity-mappings, these annotations allow to use the
 * page-table data काष्ठाure as a simple rmap.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_set_owner(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size,
				 व्योम *mc, u8 owner_id);

/**
 * kvm_pgtable_stage2_unmap() - Remove a mapping from a guest stage-2 page-table.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address from which to हटाओ the mapping.
 * @size:	Size of the mapping.
 *
 * The offset of @addr within a page is ignored and @size is rounded-up to
 * the next page boundary.
 *
 * TLB invalidation is perक्रमmed क्रम each page-table entry cleared during the
 * unmapping operation and the reference count क्रम the page-table page
 * containing the cleared entry is decremented, with unreferenced pages being
 * मुक्तd. Unmapping a cacheable page will ensure that it is clean to the PoC अगर
 * FWB is not supported by the CPU.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_unmap(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size);

/**
 * kvm_pgtable_stage2_wrprotect() - Write-protect guest stage-2 address range
 *                                  without TLB invalidation.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address from which to ग_लिखो-protect,
 * @size:	Size of the range.
 *
 * The offset of @addr within a page is ignored and @size is rounded-up to
 * the next page boundary.
 *
 * Note that it is the caller's responsibility to invalidate the TLB after
 * calling this function to ensure that the updated permissions are visible
 * to the CPUs.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_wrprotect(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size);

/**
 * kvm_pgtable_stage2_mkyoung() - Set the access flag in a page-table entry.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address to identअगरy the page-table entry.
 *
 * The offset of @addr within a page is ignored.
 *
 * If there is a valid, leaf page-table entry used to translate @addr, then
 * set the access flag in that entry.
 *
 * Return: The old page-table entry prior to setting the flag, 0 on failure.
 */
kvm_pte_t kvm_pgtable_stage2_mkyoung(काष्ठा kvm_pgtable *pgt, u64 addr);

/**
 * kvm_pgtable_stage2_mkold() - Clear the access flag in a page-table entry.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address to identअगरy the page-table entry.
 *
 * The offset of @addr within a page is ignored.
 *
 * If there is a valid, leaf page-table entry used to translate @addr, then
 * clear the access flag in that entry.
 *
 * Note that it is the caller's responsibility to invalidate the TLB after
 * calling this function to ensure that the updated permissions are visible
 * to the CPUs.
 *
 * Return: The old page-table entry prior to clearing the flag, 0 on failure.
 */
kvm_pte_t kvm_pgtable_stage2_mkold(काष्ठा kvm_pgtable *pgt, u64 addr);

/**
 * kvm_pgtable_stage2_relax_perms() - Relax the permissions enक्रमced by a
 *				      page-table entry.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address to identअगरy the page-table entry.
 * @prot:	Additional permissions to grant क्रम the mapping.
 *
 * The offset of @addr within a page is ignored.
 *
 * If there is a valid, leaf page-table entry used to translate @addr, then
 * relax the permissions in that entry according to the पढ़ो, ग_लिखो and
 * execute permissions specअगरied by @prot. No permissions are हटाओd, and
 * TLB invalidation is perक्रमmed after updating the entry.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_relax_perms(काष्ठा kvm_pgtable *pgt, u64 addr,
				   क्रमागत kvm_pgtable_prot prot);

/**
 * kvm_pgtable_stage2_is_young() - Test whether a page-table entry has the
 *				   access flag set.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address to identअगरy the page-table entry.
 *
 * The offset of @addr within a page is ignored.
 *
 * Return: True अगर the page-table entry has the access flag set, false otherwise.
 */
bool kvm_pgtable_stage2_is_young(काष्ठा kvm_pgtable *pgt, u64 addr);

/**
 * kvm_pgtable_stage2_flush_range() - Clean and invalidate data cache to Poपूर्णांक
 * 				      of Coherency क्रम guest stage-2 address
 *				      range.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Intermediate physical address from which to flush.
 * @size:	Size of the range.
 *
 * The offset of @addr within a page is ignored and @size is rounded-up to
 * the next page boundary.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_flush(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size);

/**
 * kvm_pgtable_walk() - Walk a page-table.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_*_init().
 * @addr:	Input address क्रम the start of the walk.
 * @size:	Size of the range to walk.
 * @walker:	Walker callback description.
 *
 * The offset of @addr within a page is ignored and @size is rounded-up to
 * the next page boundary.
 *
 * The walker will walk the page-table entries corresponding to the input
 * address range specअगरied, visiting entries according to the walker flags.
 * Invalid entries are treated as leaf entries. Leaf entries are reloaded
 * after invoking the walker callback, allowing the walker to descend पूर्णांकo
 * a newly installed table.
 *
 * Returning a negative error code from the walker callback function will
 * terminate the walk immediately with the same error code.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_walk(काष्ठा kvm_pgtable *pgt, u64 addr, u64 size,
		     काष्ठा kvm_pgtable_walker *walker);

/**
 * kvm_pgtable_stage2_find_range() - Find a range of Intermediate Physical
 *				     Addresses with compatible permission
 *				     attributes.
 * @pgt:	Page-table काष्ठाure initialised by kvm_pgtable_stage2_init*().
 * @addr:	Address that must be covered by the range.
 * @prot:	Protection attributes that the range must be compatible with.
 * @range:	Range काष्ठाure used to limit the search space at call समय and
 *		that will hold the result.
 *
 * The offset of @addr within a page is ignored. An IPA is compatible with @prot
 * अगरf its corresponding stage-2 page-table entry has शेष ownership and, अगर
 * valid, is mapped with protection attributes identical to @prot.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक kvm_pgtable_stage2_find_range(काष्ठा kvm_pgtable *pgt, u64 addr,
				  क्रमागत kvm_pgtable_prot prot,
				  काष्ठा kvm_mem_range *range);
#पूर्ण_अगर	/* __ARM64_KVM_PGTABLE_H__ */
