<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * IOMMU user API definitions
 */

#अगर_अघोषित _UAPI_IOMMU_H
#घोषणा _UAPI_IOMMU_H

#समावेश <linux/types.h>

#घोषणा IOMMU_FAULT_PERM_READ	(1 << 0) /* पढ़ो */
#घोषणा IOMMU_FAULT_PERM_WRITE	(1 << 1) /* ग_लिखो */
#घोषणा IOMMU_FAULT_PERM_EXEC	(1 << 2) /* exec */
#घोषणा IOMMU_FAULT_PERM_PRIV	(1 << 3) /* privileged */

/* Generic fault types, can be expanded IRQ remapping fault */
क्रमागत iommu_fault_type अणु
	IOMMU_FAULT_DMA_UNRECOV = 1,	/* unrecoverable fault */
	IOMMU_FAULT_PAGE_REQ,		/* page request fault */
पूर्ण;

क्रमागत iommu_fault_reason अणु
	IOMMU_FAULT_REASON_UNKNOWN = 0,

	/* Could not access the PASID table (fetch caused बाह्यal पात) */
	IOMMU_FAULT_REASON_PASID_FETCH,

	/* PASID entry is invalid or has configuration errors */
	IOMMU_FAULT_REASON_BAD_PASID_ENTRY,

	/*
	 * PASID is out of range (e.g. exceeds the maximum PASID
	 * supported by the IOMMU) or disabled.
	 */
	IOMMU_FAULT_REASON_PASID_INVALID,

	/*
	 * An बाह्यal पात occurred fetching (or updating) a translation
	 * table descriptor
	 */
	IOMMU_FAULT_REASON_WALK_EABT,

	/*
	 * Could not access the page table entry (Bad address),
	 * actual translation fault
	 */
	IOMMU_FAULT_REASON_PTE_FETCH,

	/* Protection flag check failed */
	IOMMU_FAULT_REASON_PERMISSION,

	/* access flag check failed */
	IOMMU_FAULT_REASON_ACCESS,

	/* Output address of a translation stage caused Address Size fault */
	IOMMU_FAULT_REASON_OOR_ADDRESS,
पूर्ण;

/**
 * काष्ठा iommu_fault_unrecoverable - Unrecoverable fault data
 * @reason: reason of the fault, from &क्रमागत iommu_fault_reason
 * @flags: parameters of this fault (IOMMU_FAULT_UNRECOV_* values)
 * @pasid: Process Address Space ID
 * @perm: requested permission access using by the incoming transaction
 *        (IOMMU_FAULT_PERM_* values)
 * @addr: offending page address
 * @fetch_addr: address that caused a fetch पात, अगर any
 */
काष्ठा iommu_fault_unrecoverable अणु
	__u32	reason;
#घोषणा IOMMU_FAULT_UNRECOV_PASID_VALID		(1 << 0)
#घोषणा IOMMU_FAULT_UNRECOV_ADDR_VALID		(1 << 1)
#घोषणा IOMMU_FAULT_UNRECOV_FETCH_ADDR_VALID	(1 << 2)
	__u32	flags;
	__u32	pasid;
	__u32	perm;
	__u64	addr;
	__u64	fetch_addr;
पूर्ण;

/**
 * काष्ठा iommu_fault_page_request - Page Request data
 * @flags: encodes whether the corresponding fields are valid and whether this
 *         is the last page in group (IOMMU_FAULT_PAGE_REQUEST_* values).
 *         When IOMMU_FAULT_PAGE_RESPONSE_NEEDS_PASID is set, the page response
 *         must have the same PASID value as the page request. When it is clear,
 *         the page response should not have a PASID.
 * @pasid: Process Address Space ID
 * @grpid: Page Request Group Index
 * @perm: requested page permissions (IOMMU_FAULT_PERM_* values)
 * @addr: page address
 * @निजी_data: device-specअगरic निजी inक्रमmation
 */
काष्ठा iommu_fault_page_request अणु
#घोषणा IOMMU_FAULT_PAGE_REQUEST_PASID_VALID	(1 << 0)
#घोषणा IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE	(1 << 1)
#घोषणा IOMMU_FAULT_PAGE_REQUEST_PRIV_DATA	(1 << 2)
#घोषणा IOMMU_FAULT_PAGE_RESPONSE_NEEDS_PASID	(1 << 3)
	__u32	flags;
	__u32	pasid;
	__u32	grpid;
	__u32	perm;
	__u64	addr;
	__u64	निजी_data[2];
पूर्ण;

/**
 * काष्ठा iommu_fault - Generic fault data
 * @type: fault type from &क्रमागत iommu_fault_type
 * @padding: reserved क्रम future use (should be zero)
 * @event: fault event, when @type is %IOMMU_FAULT_DMA_UNRECOV
 * @prm: Page Request message, when @type is %IOMMU_FAULT_PAGE_REQ
 * @padding2: sets the fault size to allow क्रम future extensions
 */
काष्ठा iommu_fault अणु
	__u32	type;
	__u32	padding;
	जोड़ अणु
		काष्ठा iommu_fault_unrecoverable event;
		काष्ठा iommu_fault_page_request prm;
		__u8 padding2[56];
	पूर्ण;
पूर्ण;

/**
 * क्रमागत iommu_page_response_code - Return status of fault handlers
 * @IOMMU_PAGE_RESP_SUCCESS: Fault has been handled and the page tables
 *	populated, retry the access. This is "Success" in PCI PRI.
 * @IOMMU_PAGE_RESP_FAILURE: General error. Drop all subsequent faults from
 *	this device अगर possible. This is "Response Failure" in PCI PRI.
 * @IOMMU_PAGE_RESP_INVALID: Could not handle this fault, करोn't retry the
 *	access. This is "Invalid Request" in PCI PRI.
 */
क्रमागत iommu_page_response_code अणु
	IOMMU_PAGE_RESP_SUCCESS = 0,
	IOMMU_PAGE_RESP_INVALID,
	IOMMU_PAGE_RESP_FAILURE,
पूर्ण;

/**
 * काष्ठा iommu_page_response - Generic page response inक्रमmation
 * @argsz: User filled size of this data
 * @version: API version of this काष्ठाure
 * @flags: encodes whether the corresponding fields are valid
 *         (IOMMU_FAULT_PAGE_RESPONSE_* values)
 * @pasid: Process Address Space ID
 * @grpid: Page Request Group Index
 * @code: response code from &क्रमागत iommu_page_response_code
 */
काष्ठा iommu_page_response अणु
	__u32	argsz;
#घोषणा IOMMU_PAGE_RESP_VERSION_1	1
	__u32	version;
#घोषणा IOMMU_PAGE_RESP_PASID_VALID	(1 << 0)
	__u32	flags;
	__u32	pasid;
	__u32	grpid;
	__u32	code;
पूर्ण;

/* defines the granularity of the invalidation */
क्रमागत iommu_inv_granularity अणु
	IOMMU_INV_GRANU_DOMAIN,	/* करोमुख्य-selective invalidation */
	IOMMU_INV_GRANU_PASID,	/* PASID-selective invalidation */
	IOMMU_INV_GRANU_ADDR,	/* page-selective invalidation */
	IOMMU_INV_GRANU_NR,	/* number of invalidation granularities */
पूर्ण;

/**
 * काष्ठा iommu_inv_addr_info - Address Selective Invalidation Structure
 *
 * @flags: indicates the granularity of the address-selective invalidation
 * - If the PASID bit is set, the @pasid field is populated and the invalidation
 *   relates to cache entries tagged with this PASID and matching the address
 *   range.
 * - If ARCHID bit is set, @archid is populated and the invalidation relates
 *   to cache entries tagged with this architecture specअगरic ID and matching
 *   the address range.
 * - Both PASID and ARCHID can be set as they may tag dअगरferent caches.
 * - If neither PASID or ARCHID is set, global addr invalidation applies.
 * - The LEAF flag indicates whether only the leaf PTE caching needs to be
 *   invalidated and other paging काष्ठाure caches can be preserved.
 * @pasid: process address space ID
 * @archid: architecture-specअगरic ID
 * @addr: first stage/level input address
 * @granule_size: page/block size of the mapping in bytes
 * @nb_granules: number of contiguous granules to be invalidated
 */
काष्ठा iommu_inv_addr_info अणु
#घोषणा IOMMU_INV_ADDR_FLAGS_PASID	(1 << 0)
#घोषणा IOMMU_INV_ADDR_FLAGS_ARCHID	(1 << 1)
#घोषणा IOMMU_INV_ADDR_FLAGS_LEAF	(1 << 2)
	__u32	flags;
	__u32	archid;
	__u64	pasid;
	__u64	addr;
	__u64	granule_size;
	__u64	nb_granules;
पूर्ण;

/**
 * काष्ठा iommu_inv_pasid_info - PASID Selective Invalidation Structure
 *
 * @flags: indicates the granularity of the PASID-selective invalidation
 * - If the PASID bit is set, the @pasid field is populated and the invalidation
 *   relates to cache entries tagged with this PASID and matching the address
 *   range.
 * - If the ARCHID bit is set, the @archid is populated and the invalidation
 *   relates to cache entries tagged with this architecture specअगरic ID and
 *   matching the address range.
 * - Both PASID and ARCHID can be set as they may tag dअगरferent caches.
 * - At least one of PASID or ARCHID must be set.
 * @pasid: process address space ID
 * @archid: architecture-specअगरic ID
 */
काष्ठा iommu_inv_pasid_info अणु
#घोषणा IOMMU_INV_PASID_FLAGS_PASID	(1 << 0)
#घोषणा IOMMU_INV_PASID_FLAGS_ARCHID	(1 << 1)
	__u32	flags;
	__u32	archid;
	__u64	pasid;
पूर्ण;

/**
 * काष्ठा iommu_cache_invalidate_info - First level/stage invalidation
 *     inक्रमmation
 * @argsz: User filled size of this data
 * @version: API version of this काष्ठाure
 * @cache: bitfield that allows to select which caches to invalidate
 * @granularity: defines the lowest granularity used क्रम the invalidation:
 *     करोमुख्य > PASID > addr
 * @padding: reserved क्रम future use (should be zero)
 * @pasid_info: invalidation data when @granularity is %IOMMU_INV_GRANU_PASID
 * @addr_info: invalidation data when @granularity is %IOMMU_INV_GRANU_ADDR
 *
 * Not all the combinations of cache/granularity are valid:
 *
 * +--------------+---------------+---------------+---------------+
 * | type /       |   DEV_IOTLB   |     IOTLB     |      PASID    |
 * | granularity  |               |               |      cache    |
 * +==============+===============+===============+===============+
 * | DOMAIN       |       N/A     |       Y       |       Y       |
 * +--------------+---------------+---------------+---------------+
 * | PASID        |       Y       |       Y       |       Y       |
 * +--------------+---------------+---------------+---------------+
 * | ADDR         |       Y       |       Y       |       N/A     |
 * +--------------+---------------+---------------+---------------+
 *
 * Invalidations by %IOMMU_INV_GRANU_DOMAIN करोn't take any argument other than
 * @version and @cache.
 *
 * If multiple cache types are invalidated simultaneously, they all
 * must support the used granularity.
 */
काष्ठा iommu_cache_invalidate_info अणु
	__u32	argsz;
#घोषणा IOMMU_CACHE_INVALIDATE_INFO_VERSION_1 1
	__u32	version;
/* IOMMU paging काष्ठाure cache */
#घोषणा IOMMU_CACHE_INV_TYPE_IOTLB	(1 << 0) /* IOMMU IOTLB */
#घोषणा IOMMU_CACHE_INV_TYPE_DEV_IOTLB	(1 << 1) /* Device IOTLB */
#घोषणा IOMMU_CACHE_INV_TYPE_PASID	(1 << 2) /* PASID cache */
#घोषणा IOMMU_CACHE_INV_TYPE_NR		(3)
	__u8	cache;
	__u8	granularity;
	__u8	padding[6];
	जोड़ अणु
		काष्ठा iommu_inv_pasid_info pasid_info;
		काष्ठा iommu_inv_addr_info addr_info;
	पूर्ण granu;
पूर्ण;

/**
 * काष्ठा iommu_gpasid_bind_data_vtd - Intel VT-d specअगरic data on device and guest
 * SVA binding.
 *
 * @flags:	VT-d PASID table entry attributes
 * @pat:	Page attribute table data to compute effective memory type
 * @emt:	Extended memory type
 *
 * Only guest vIOMMU selectable and effective options are passed करोwn to
 * the host IOMMU.
 */
काष्ठा iommu_gpasid_bind_data_vtd अणु
#घोषणा IOMMU_SVA_VTD_GPASID_SRE	(1 << 0) /* supervisor request */
#घोषणा IOMMU_SVA_VTD_GPASID_EAFE	(1 << 1) /* extended access enable */
#घोषणा IOMMU_SVA_VTD_GPASID_PCD	(1 << 2) /* page-level cache disable */
#घोषणा IOMMU_SVA_VTD_GPASID_PWT	(1 << 3) /* page-level ग_लिखो through */
#घोषणा IOMMU_SVA_VTD_GPASID_EMTE	(1 << 4) /* extended mem type enable */
#घोषणा IOMMU_SVA_VTD_GPASID_CD		(1 << 5) /* PASID-level cache disable */
#घोषणा IOMMU_SVA_VTD_GPASID_WPE	(1 << 6) /* Write protect enable */
#घोषणा IOMMU_SVA_VTD_GPASID_LAST	(1 << 7)
	__u64 flags;
	__u32 pat;
	__u32 emt;
पूर्ण;

#घोषणा IOMMU_SVA_VTD_GPASID_MTS_MASK	(IOMMU_SVA_VTD_GPASID_CD | \
					 IOMMU_SVA_VTD_GPASID_EMTE | \
					 IOMMU_SVA_VTD_GPASID_PCD |  \
					 IOMMU_SVA_VTD_GPASID_PWT)

/**
 * काष्ठा iommu_gpasid_bind_data - Inक्रमmation about device and guest PASID binding
 * @argsz:	User filled size of this data
 * @version:	Version of this data काष्ठाure
 * @क्रमmat:	PASID table entry क्रमmat
 * @flags:	Additional inक्रमmation on guest bind request
 * @gpgd:	Guest page directory base of the guest mm to bind
 * @hpasid:	Process address space ID used क्रम the guest mm in host IOMMU
 * @gpasid:	Process address space ID used क्रम the guest mm in guest IOMMU
 * @addr_width:	Guest भव address width
 * @padding:	Reserved क्रम future use (should be zero)
 * @vtd:	Intel VT-d specअगरic data
 *
 * Guest to host PASID mapping can be an identity or non-identity, where guest
 * has its own PASID space. For non-identअगरy mapping, guest to host PASID lookup
 * is needed when VM programs guest PASID पूर्णांकo an asचिन्हित device. VMM may
 * trap such PASID programming then request host IOMMU driver to convert guest
 * PASID to host PASID based on this bind data.
 */
काष्ठा iommu_gpasid_bind_data अणु
	__u32 argsz;
#घोषणा IOMMU_GPASID_BIND_VERSION_1	1
	__u32 version;
#घोषणा IOMMU_PASID_FORMAT_INTEL_VTD	1
#घोषणा IOMMU_PASID_FORMAT_LAST		2
	__u32 क्रमmat;
	__u32 addr_width;
#घोषणा IOMMU_SVA_GPASID_VAL	(1 << 0) /* guest PASID valid */
	__u64 flags;
	__u64 gpgd;
	__u64 hpasid;
	__u64 gpasid;
	__u8  padding[8];
	/* Venकरोr specअगरic data */
	जोड़ अणु
		काष्ठा iommu_gpasid_bind_data_vtd vtd;
	पूर्ण venकरोr;
पूर्ण;

#पूर्ण_अगर /* _UAPI_IOMMU_H */
