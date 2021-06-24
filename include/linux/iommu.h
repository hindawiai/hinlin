<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007-2008 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <joerg.roedel@amd.com>
 */

#अगर_अघोषित __LINUX_IOMMU_H
#घोषणा __LINUX_IOMMU_H

#समावेश <linux/scatterlist.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/ioasid.h>
#समावेश <uapi/linux/iommu.h>

#घोषणा IOMMU_READ	(1 << 0)
#घोषणा IOMMU_WRITE	(1 << 1)
#घोषणा IOMMU_CACHE	(1 << 2) /* DMA cache coherency */
#घोषणा IOMMU_NOEXEC	(1 << 3)
#घोषणा IOMMU_MMIO	(1 << 4) /* e.g. things like MSI करोorbells */
/*
 * Where the bus hardware includes a privilege level as part of its access type
 * markings, and certain devices are capable of issuing transactions marked as
 * either 'supervisor' or 'user', the IOMMU_PRIV flag requests that the other
 * given permission flags only apply to accesses at the higher privilege level,
 * and that unprivileged transactions should have as little access as possible.
 * This would usually imply the same permissions as kernel mappings on the CPU,
 * अगर the IOMMU page table क्रमmat is equivalent.
 */
#घोषणा IOMMU_PRIV	(1 << 5)

काष्ठा iommu_ops;
काष्ठा iommu_group;
काष्ठा bus_type;
काष्ठा device;
काष्ठा iommu_करोमुख्य;
काष्ठा notअगरier_block;
काष्ठा iommu_sva;
काष्ठा iommu_fault_event;

/* iommu fault flags */
#घोषणा IOMMU_FAULT_READ	0x0
#घोषणा IOMMU_FAULT_WRITE	0x1

प्रकार पूर्णांक (*iommu_fault_handler_t)(काष्ठा iommu_करोमुख्य *,
			काष्ठा device *, अचिन्हित दीर्घ, पूर्णांक, व्योम *);
प्रकार पूर्णांक (*iommu_dev_fault_handler_t)(काष्ठा iommu_fault *, व्योम *);

काष्ठा iommu_करोमुख्य_geometry अणु
	dma_addr_t aperture_start; /* First address that can be mapped    */
	dma_addr_t aperture_end;   /* Last address that can be mapped     */
	bool क्रमce_aperture;       /* DMA only allowed in mappable range? */
पूर्ण;

/* Doमुख्य feature flags */
#घोषणा __IOMMU_DOMAIN_PAGING	(1U << 0)  /* Support क्रम iommu_map/unmap */
#घोषणा __IOMMU_DOMAIN_DMA_API	(1U << 1)  /* Doमुख्य क्रम use in DMA-API
					      implementation              */
#घोषणा __IOMMU_DOMAIN_PT	(1U << 2)  /* Doमुख्य is identity mapped   */

/*
 * This are the possible करोमुख्य-types
 *
 *	IOMMU_DOMAIN_BLOCKED	- All DMA is blocked, can be used to isolate
 *				  devices
 *	IOMMU_DOMAIN_IDENTITY	- DMA addresses are प्रणाली physical addresses
 *	IOMMU_DOMAIN_UNMANAGED	- DMA mappings managed by IOMMU-API user, used
 *				  क्रम VMs
 *	IOMMU_DOMAIN_DMA	- Internally used क्रम DMA-API implementations.
 *				  This flag allows IOMMU drivers to implement
 *				  certain optimizations क्रम these करोमुख्यs
 */
#घोषणा IOMMU_DOMAIN_BLOCKED	(0U)
#घोषणा IOMMU_DOMAIN_IDENTITY	(__IOMMU_DOMAIN_PT)
#घोषणा IOMMU_DOMAIN_UNMANAGED	(__IOMMU_DOMAIN_PAGING)
#घोषणा IOMMU_DOMAIN_DMA	(__IOMMU_DOMAIN_PAGING |	\
				 __IOMMU_DOMAIN_DMA_API)

काष्ठा iommu_करोमुख्य अणु
	अचिन्हित type;
	स्थिर काष्ठा iommu_ops *ops;
	अचिन्हित दीर्घ pgsize_biपंचांगap;	/* Biपंचांगap of page sizes in use */
	iommu_fault_handler_t handler;
	व्योम *handler_token;
	काष्ठा iommu_करोमुख्य_geometry geometry;
	व्योम *iova_cookie;
पूर्ण;

क्रमागत iommu_cap अणु
	IOMMU_CAP_CACHE_COHERENCY,	/* IOMMU can enक्रमce cache coherent DMA
					   transactions */
	IOMMU_CAP_INTR_REMAP,		/* IOMMU supports पूर्णांकerrupt isolation */
	IOMMU_CAP_NOEXEC,		/* IOMMU_NOEXEC flag */
पूर्ण;

/* These are the possible reserved region types */
क्रमागत iommu_resv_type अणु
	/* Memory regions which must be mapped 1:1 at all बार */
	IOMMU_RESV_सूचीECT,
	/*
	 * Memory regions which are advertised to be 1:1 but are
	 * commonly considered relaxable in some conditions,
	 * क्रम instance in device assignment use हाल (USB, Graphics)
	 */
	IOMMU_RESV_सूचीECT_RELAXABLE,
	/* Arbitrary "never map this or give it to a device" address ranges */
	IOMMU_RESV_RESERVED,
	/* Hardware MSI region (untranslated) */
	IOMMU_RESV_MSI,
	/* Software-managed MSI translation winकरोw */
	IOMMU_RESV_SW_MSI,
पूर्ण;

/**
 * काष्ठा iommu_resv_region - descriptor क्रम a reserved memory region
 * @list: Linked list poपूर्णांकers
 * @start: System physical start address of the region
 * @length: Length of the region in bytes
 * @prot: IOMMU Protection flags (READ/WRITE/...)
 * @type: Type of the reserved region
 */
काष्ठा iommu_resv_region अणु
	काष्ठा list_head	list;
	phys_addr_t		start;
	माप_प्रकार			length;
	पूर्णांक			prot;
	क्रमागत iommu_resv_type	type;
पूर्ण;

/**
 * क्रमागत iommu_dev_features - Per device IOMMU features
 * @IOMMU_DEV_FEAT_AUX: Auxiliary करोमुख्य feature
 * @IOMMU_DEV_FEAT_SVA: Shared Virtual Addresses
 * @IOMMU_DEV_FEAT_IOPF: I/O Page Faults such as PRI or Stall. Generally
 *			 enabling %IOMMU_DEV_FEAT_SVA requires
 *			 %IOMMU_DEV_FEAT_IOPF, but some devices manage I/O Page
 *			 Faults themselves instead of relying on the IOMMU. When
 *			 supported, this feature must be enabled beक्रमe and
 *			 disabled after %IOMMU_DEV_FEAT_SVA.
 *
 * Device drivers query whether a feature is supported using
 * iommu_dev_has_feature(), and enable it using iommu_dev_enable_feature().
 */
क्रमागत iommu_dev_features अणु
	IOMMU_DEV_FEAT_AUX,
	IOMMU_DEV_FEAT_SVA,
	IOMMU_DEV_FEAT_IOPF,
पूर्ण;

#घोषणा IOMMU_PASID_INVALID	(-1U)

#अगर_घोषित CONFIG_IOMMU_API

/**
 * काष्ठा iommu_iotlb_gather - Range inक्रमmation क्रम a pending IOTLB flush
 *
 * @start: IOVA representing the start of the range to be flushed
 * @end: IOVA representing the end of the range to be flushed (inclusive)
 * @pgsize: The पूर्णांकerval at which to perक्रमm the flush
 *
 * This काष्ठाure is पूर्णांकended to be updated by multiple calls to the
 * ->unmap() function in काष्ठा iommu_ops beक्रमe eventually being passed
 * पूर्णांकo ->iotlb_sync().
 */
काष्ठा iommu_iotlb_gather अणु
	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		end;
	माप_प्रकार			pgsize;
	काष्ठा page		*मुक्तlist;
पूर्ण;

/**
 * काष्ठा iommu_ops - iommu ops and capabilities
 * @capable: check capability
 * @करोमुख्य_alloc: allocate iommu करोमुख्य
 * @करोमुख्य_मुक्त: मुक्त iommu करोमुख्य
 * @attach_dev: attach device to an iommu करोमुख्य
 * @detach_dev: detach device from an iommu करोमुख्य
 * @map: map a physically contiguous memory region to an iommu करोमुख्य
 * @unmap: unmap a physically contiguous memory region from an iommu करोमुख्य
 * @flush_iotlb_all: Synchronously flush all hardware TLBs क्रम this करोमुख्य
 * @iotlb_sync_map: Sync mappings created recently using @map to the hardware
 * @iotlb_sync: Flush all queued ranges from the hardware TLBs and empty flush
 *            queue
 * @iova_to_phys: translate iova to physical address
 * @probe_device: Add device to iommu driver handling
 * @release_device: Remove device from iommu driver handling
 * @probe_finalize: Do final setup work after the device is added to an IOMMU
 *                  group and attached to the groups करोमुख्य
 * @device_group: find iommu group क्रम a particular device
 * @enable_nesting: Enable nesting
 * @set_pgtable_quirks: Set io page table quirks (IO_PGTABLE_QUIRK_*)
 * @get_resv_regions: Request list of reserved regions क्रम a device
 * @put_resv_regions: Free list of reserved regions क्रम a device
 * @apply_resv_region: Temporary helper call-back क्रम iova reserved ranges
 * @of_xlate: add OF master IDs to iommu grouping
 * @is_attach_deferred: Check अगर करोमुख्य attach should be deferred from iommu
 *                      driver init to device driver init (शेष no)
 * @dev_has/enable/disable_feat: per device entries to check/enable/disable
 *                               iommu specअगरic features.
 * @dev_feat_enabled: check enabled feature
 * @aux_attach/detach_dev: aux-करोमुख्य specअगरic attach/detach entries.
 * @aux_get_pasid: get the pasid given an aux-करोमुख्य
 * @sva_bind: Bind process address space to device
 * @sva_unbind: Unbind process address space from device
 * @sva_get_pasid: Get PASID associated to a SVA handle
 * @page_response: handle page request response
 * @cache_invalidate: invalidate translation caches
 * @sva_bind_gpasid: bind guest pasid and mm
 * @sva_unbind_gpasid: unbind guest pasid and mm
 * @def_करोमुख्य_type: device शेष करोमुख्य type, वापस value:
 *		- IOMMU_DOMAIN_IDENTITY: must use an identity करोमुख्य
 *		- IOMMU_DOMAIN_DMA: must use a dma करोमुख्य
 *		- 0: use the शेष setting
 * @pgsize_biपंचांगap: biपंचांगap of all possible supported page sizes
 * @owner: Driver module providing these ops
 */
काष्ठा iommu_ops अणु
	bool (*capable)(क्रमागत iommu_cap);

	/* Doमुख्य allocation and मुक्तing by the iommu driver */
	काष्ठा iommu_करोमुख्य *(*करोमुख्य_alloc)(अचिन्हित iommu_करोमुख्य_type);
	व्योम (*करोमुख्य_मुक्त)(काष्ठा iommu_करोमुख्य *);

	पूर्णांक (*attach_dev)(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);
	व्योम (*detach_dev)(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);
	पूर्णांक (*map)(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		   phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp);
	माप_प्रकार (*unmap)(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		     माप_प्रकार size, काष्ठा iommu_iotlb_gather *iotlb_gather);
	व्योम (*flush_iotlb_all)(काष्ठा iommu_करोमुख्य *करोमुख्य);
	व्योम (*iotlb_sync_map)(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			       माप_प्रकार size);
	व्योम (*iotlb_sync)(काष्ठा iommu_करोमुख्य *करोमुख्य,
			   काष्ठा iommu_iotlb_gather *iotlb_gather);
	phys_addr_t (*iova_to_phys)(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t iova);
	काष्ठा iommu_device *(*probe_device)(काष्ठा device *dev);
	व्योम (*release_device)(काष्ठा device *dev);
	व्योम (*probe_finalize)(काष्ठा device *dev);
	काष्ठा iommu_group *(*device_group)(काष्ठा device *dev);
	पूर्णांक (*enable_nesting)(काष्ठा iommu_करोमुख्य *करोमुख्य);
	पूर्णांक (*set_pgtable_quirks)(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  अचिन्हित दीर्घ quirks);

	/* Request/Free a list of reserved regions क्रम a device */
	व्योम (*get_resv_regions)(काष्ठा device *dev, काष्ठा list_head *list);
	व्योम (*put_resv_regions)(काष्ठा device *dev, काष्ठा list_head *list);
	व्योम (*apply_resv_region)(काष्ठा device *dev,
				  काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा iommu_resv_region *region);

	पूर्णांक (*of_xlate)(काष्ठा device *dev, काष्ठा of_phandle_args *args);
	bool (*is_attach_deferred)(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);

	/* Per device IOMMU features */
	bool (*dev_has_feat)(काष्ठा device *dev, क्रमागत iommu_dev_features f);
	bool (*dev_feat_enabled)(काष्ठा device *dev, क्रमागत iommu_dev_features f);
	पूर्णांक (*dev_enable_feat)(काष्ठा device *dev, क्रमागत iommu_dev_features f);
	पूर्णांक (*dev_disable_feat)(काष्ठा device *dev, क्रमागत iommu_dev_features f);

	/* Aux-करोमुख्य specअगरic attach/detach entries */
	पूर्णांक (*aux_attach_dev)(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);
	व्योम (*aux_detach_dev)(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);
	पूर्णांक (*aux_get_pasid)(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);

	काष्ठा iommu_sva *(*sva_bind)(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm,
				      व्योम *drvdata);
	व्योम (*sva_unbind)(काष्ठा iommu_sva *handle);
	u32 (*sva_get_pasid)(काष्ठा iommu_sva *handle);

	पूर्णांक (*page_response)(काष्ठा device *dev,
			     काष्ठा iommu_fault_event *evt,
			     काष्ठा iommu_page_response *msg);
	पूर्णांक (*cache_invalidate)(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
				काष्ठा iommu_cache_invalidate_info *inv_info);
	पूर्णांक (*sva_bind_gpasid)(काष्ठा iommu_करोमुख्य *करोमुख्य,
			काष्ठा device *dev, काष्ठा iommu_gpasid_bind_data *data);

	पूर्णांक (*sva_unbind_gpasid)(काष्ठा device *dev, u32 pasid);

	पूर्णांक (*def_करोमुख्य_type)(काष्ठा device *dev);

	अचिन्हित दीर्घ pgsize_biपंचांगap;
	काष्ठा module *owner;
पूर्ण;

/**
 * काष्ठा iommu_device - IOMMU core representation of one IOMMU hardware
 *			 instance
 * @list: Used by the iommu-core to keep a list of रेजिस्टरed iommus
 * @ops: iommu-ops क्रम talking to this iommu
 * @dev: काष्ठा device क्रम sysfs handling
 */
काष्ठा iommu_device अणु
	काष्ठा list_head list;
	स्थिर काष्ठा iommu_ops *ops;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा device *dev;
पूर्ण;

/**
 * काष्ठा iommu_fault_event - Generic fault event
 *
 * Can represent recoverable faults such as a page requests or
 * unrecoverable faults such as DMA or IRQ remapping faults.
 *
 * @fault: fault descriptor
 * @list: pending fault event list, used क्रम tracking responses
 */
काष्ठा iommu_fault_event अणु
	काष्ठा iommu_fault fault;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा iommu_fault_param - per-device IOMMU fault data
 * @handler: Callback function to handle IOMMU faults at device level
 * @data: handler निजी data
 * @faults: holds the pending faults which needs response
 * @lock: protect pending faults list
 */
काष्ठा iommu_fault_param अणु
	iommu_dev_fault_handler_t handler;
	व्योम *data;
	काष्ठा list_head faults;
	काष्ठा mutex lock;
पूर्ण;

/**
 * काष्ठा dev_iommu - Collection of per-device IOMMU data
 *
 * @fault_param: IOMMU detected device fault reporting data
 * @iopf_param:	 I/O Page Fault queue and data
 * @fwspec:	 IOMMU fwspec data
 * @iommu_dev:	 IOMMU device this device is linked to
 * @priv:	 IOMMU Driver निजी data
 *
 * TODO: migrate other per device data poपूर्णांकers under iommu_dev_data, e.g.
 *	काष्ठा iommu_group	*iommu_group;
 */
काष्ठा dev_iommu अणु
	काष्ठा mutex lock;
	काष्ठा iommu_fault_param	*fault_param;
	काष्ठा iopf_device_param	*iopf_param;
	काष्ठा iommu_fwspec		*fwspec;
	काष्ठा iommu_device		*iommu_dev;
	व्योम				*priv;
पूर्ण;

पूर्णांक iommu_device_रेजिस्टर(काष्ठा iommu_device *iommu,
			  स्थिर काष्ठा iommu_ops *ops,
			  काष्ठा device *hwdev);
व्योम iommu_device_unरेजिस्टर(काष्ठा iommu_device *iommu);
पूर्णांक  iommu_device_sysfs_add(काष्ठा iommu_device *iommu,
			    काष्ठा device *parent,
			    स्थिर काष्ठा attribute_group **groups,
			    स्थिर अक्षर *fmt, ...) __म_लिखो(4, 5);
व्योम iommu_device_sysfs_हटाओ(काष्ठा iommu_device *iommu);
पूर्णांक  iommu_device_link(काष्ठा iommu_device   *iommu, काष्ठा device *link);
व्योम iommu_device_unlink(काष्ठा iommu_device *iommu, काष्ठा device *link);
पूर्णांक iommu_deferred_attach(काष्ठा device *dev, काष्ठा iommu_करोमुख्य *करोमुख्य);

अटल अंतरभूत काष्ठा iommu_device *dev_to_iommu_device(काष्ठा device *dev)
अणु
	वापस (काष्ठा iommu_device *)dev_get_drvdata(dev);
पूर्ण

अटल अंतरभूत व्योम iommu_iotlb_gather_init(काष्ठा iommu_iotlb_gather *gather)
अणु
	*gather = (काष्ठा iommu_iotlb_gather) अणु
		.start	= अच_दीर्घ_उच्च,
	पूर्ण;
पूर्ण

#घोषणा IOMMU_GROUP_NOTIFY_ADD_DEVICE		1 /* Device added */
#घोषणा IOMMU_GROUP_NOTIFY_DEL_DEVICE		2 /* Pre Device हटाओd */
#घोषणा IOMMU_GROUP_NOTIFY_BIND_DRIVER		3 /* Pre Driver bind */
#घोषणा IOMMU_GROUP_NOTIFY_BOUND_DRIVER		4 /* Post Driver bind */
#घोषणा IOMMU_GROUP_NOTIFY_UNBIND_DRIVER	5 /* Pre Driver unbind */
#घोषणा IOMMU_GROUP_NOTIFY_UNBOUND_DRIVER	6 /* Post Driver unbind */

बाह्य पूर्णांक bus_set_iommu(काष्ठा bus_type *bus, स्थिर काष्ठा iommu_ops *ops);
बाह्य पूर्णांक bus_iommu_probe(काष्ठा bus_type *bus);
बाह्य bool iommu_present(काष्ठा bus_type *bus);
बाह्य bool iommu_capable(काष्ठा bus_type *bus, क्रमागत iommu_cap cap);
बाह्य काष्ठा iommu_करोमुख्य *iommu_करोमुख्य_alloc(काष्ठा bus_type *bus);
बाह्य काष्ठा iommu_group *iommu_group_get_by_id(पूर्णांक id);
बाह्य व्योम iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य);
बाह्य पूर्णांक iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
			       काष्ठा device *dev);
बाह्य व्योम iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				काष्ठा device *dev);
बाह्य पूर्णांक iommu_uapi_cache_invalidate(काष्ठा iommu_करोमुख्य *करोमुख्य,
				       काष्ठा device *dev,
				       व्योम __user *uinfo);

बाह्य पूर्णांक iommu_uapi_sva_bind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य,
				      काष्ठा device *dev, व्योम __user *udata);
बाह्य पूर्णांक iommu_uapi_sva_unbind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य,
					काष्ठा device *dev, व्योम __user *udata);
बाह्य पूर्णांक iommu_sva_unbind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev, ioasid_t pasid);
बाह्य काष्ठा iommu_करोमुख्य *iommu_get_करोमुख्य_क्रम_dev(काष्ठा device *dev);
बाह्य काष्ठा iommu_करोमुख्य *iommu_get_dma_करोमुख्य(काष्ठा device *dev);
बाह्य पूर्णांक iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		     phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot);
बाह्य पूर्णांक iommu_map_atomic(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			    phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot);
बाह्य माप_प्रकार iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			  माप_प्रकार size);
बाह्य माप_प्रकार iommu_unmap_fast(काष्ठा iommu_करोमुख्य *करोमुख्य,
			       अचिन्हित दीर्घ iova, माप_प्रकार size,
			       काष्ठा iommu_iotlb_gather *iotlb_gather);
बाह्य माप_प्रकार iommu_map_sg(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			   काष्ठा scatterlist *sg,अचिन्हित पूर्णांक nents, पूर्णांक prot);
बाह्य माप_प्रकार iommu_map_sg_atomic(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  अचिन्हित दीर्घ iova, काष्ठा scatterlist *sg,
				  अचिन्हित पूर्णांक nents, पूर्णांक prot);
बाह्य phys_addr_t iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t iova);
बाह्य व्योम iommu_set_fault_handler(काष्ठा iommu_करोमुख्य *करोमुख्य,
			iommu_fault_handler_t handler, व्योम *token);

बाह्य व्योम iommu_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *list);
बाह्य व्योम iommu_put_resv_regions(काष्ठा device *dev, काष्ठा list_head *list);
बाह्य व्योम generic_iommu_put_resv_regions(काष्ठा device *dev,
					   काष्ठा list_head *list);
बाह्य व्योम iommu_set_शेष_passthrough(bool cmd_line);
बाह्य व्योम iommu_set_शेष_translated(bool cmd_line);
बाह्य bool iommu_शेष_passthrough(व्योम);
बाह्य काष्ठा iommu_resv_region *
iommu_alloc_resv_region(phys_addr_t start, माप_प्रकार length, पूर्णांक prot,
			क्रमागत iommu_resv_type type);
बाह्य पूर्णांक iommu_get_group_resv_regions(काष्ठा iommu_group *group,
					काष्ठा list_head *head);

बाह्य पूर्णांक iommu_attach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
			      काष्ठा iommu_group *group);
बाह्य व्योम iommu_detach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
			       काष्ठा iommu_group *group);
बाह्य काष्ठा iommu_group *iommu_group_alloc(व्योम);
बाह्य व्योम *iommu_group_get_iommudata(काष्ठा iommu_group *group);
बाह्य व्योम iommu_group_set_iommudata(काष्ठा iommu_group *group,
				      व्योम *iommu_data,
				      व्योम (*release)(व्योम *iommu_data));
बाह्य पूर्णांक iommu_group_set_name(काष्ठा iommu_group *group, स्थिर अक्षर *name);
बाह्य पूर्णांक iommu_group_add_device(काष्ठा iommu_group *group,
				  काष्ठा device *dev);
बाह्य व्योम iommu_group_हटाओ_device(काष्ठा device *dev);
बाह्य पूर्णांक iommu_group_क्रम_each_dev(काष्ठा iommu_group *group, व्योम *data,
				    पूर्णांक (*fn)(काष्ठा device *, व्योम *));
बाह्य काष्ठा iommu_group *iommu_group_get(काष्ठा device *dev);
बाह्य काष्ठा iommu_group *iommu_group_ref_get(काष्ठा iommu_group *group);
बाह्य व्योम iommu_group_put(काष्ठा iommu_group *group);
बाह्य पूर्णांक iommu_group_रेजिस्टर_notअगरier(काष्ठा iommu_group *group,
					 काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक iommu_group_unरेजिस्टर_notअगरier(काष्ठा iommu_group *group,
					   काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक iommu_रेजिस्टर_device_fault_handler(काष्ठा device *dev,
					iommu_dev_fault_handler_t handler,
					व्योम *data);

बाह्य पूर्णांक iommu_unरेजिस्टर_device_fault_handler(काष्ठा device *dev);

बाह्य पूर्णांक iommu_report_device_fault(काष्ठा device *dev,
				     काष्ठा iommu_fault_event *evt);
बाह्य पूर्णांक iommu_page_response(काष्ठा device *dev,
			       काष्ठा iommu_page_response *msg);

बाह्य पूर्णांक iommu_group_id(काष्ठा iommu_group *group);
बाह्य काष्ठा iommu_करोमुख्य *iommu_group_शेष_करोमुख्य(काष्ठा iommu_group *);

पूर्णांक iommu_enable_nesting(काष्ठा iommu_करोमुख्य *करोमुख्य);
पूर्णांक iommu_set_pgtable_quirks(काष्ठा iommu_करोमुख्य *करोमुख्य,
		अचिन्हित दीर्घ quirks);

व्योम iommu_set_dma_strict(bool val);
bool iommu_get_dma_strict(काष्ठा iommu_करोमुख्य *करोमुख्य);

बाह्य पूर्णांक report_iommu_fault(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			      अचिन्हित दीर्घ iova, पूर्णांक flags);

अटल अंतरभूत व्योम iommu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	अगर (करोमुख्य->ops->flush_iotlb_all)
		करोमुख्य->ops->flush_iotlb_all(करोमुख्य);
पूर्ण

अटल अंतरभूत व्योम iommu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	अगर (करोमुख्य->ops->iotlb_sync)
		करोमुख्य->ops->iotlb_sync(करोमुख्य, iotlb_gather);

	iommu_iotlb_gather_init(iotlb_gather);
पूर्ण

अटल अंतरभूत व्योम iommu_iotlb_gather_add_page(काष्ठा iommu_करोमुख्य *करोमुख्य,
					       काष्ठा iommu_iotlb_gather *gather,
					       अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ start = iova, end = start + size - 1;

	/*
	 * If the new page is disjoपूर्णांक from the current range or is mapped at
	 * a dअगरferent granularity, then sync the TLB so that the gather
	 * काष्ठाure can be rewritten.
	 */
	अगर (gather->pgsize != size ||
	    end + 1 < gather->start || start > gather->end + 1) अणु
		अगर (gather->pgsize)
			iommu_iotlb_sync(करोमुख्य, gather);
		gather->pgsize = size;
	पूर्ण

	अगर (gather->end < end)
		gather->end = end;

	अगर (gather->start > start)
		gather->start = start;
पूर्ण

/* PCI device grouping function */
बाह्य काष्ठा iommu_group *pci_device_group(काष्ठा device *dev);
/* Generic device grouping function */
बाह्य काष्ठा iommu_group *generic_device_group(काष्ठा device *dev);
/* FSL-MC device grouping function */
काष्ठा iommu_group *fsl_mc_device_group(काष्ठा device *dev);

/**
 * काष्ठा iommu_fwspec - per-device IOMMU instance data
 * @ops: ops क्रम this device's IOMMU
 * @iommu_fwnode: firmware handle क्रम this device's IOMMU
 * @flags: IOMMU_FWSPEC_* flags
 * @num_ids: number of associated device IDs
 * @ids: IDs which this device may present to the IOMMU
 */
काष्ठा iommu_fwspec अणु
	स्थिर काष्ठा iommu_ops	*ops;
	काष्ठा fwnode_handle	*iommu_fwnode;
	u32			flags;
	अचिन्हित पूर्णांक		num_ids;
	u32			ids[];
पूर्ण;

/* ATS is supported */
#घोषणा IOMMU_FWSPEC_PCI_RC_ATS			(1 << 0)

/**
 * काष्ठा iommu_sva - handle to a device-mm bond
 */
काष्ठा iommu_sva अणु
	काष्ठा device			*dev;
पूर्ण;

पूर्णांक iommu_fwspec_init(काष्ठा device *dev, काष्ठा fwnode_handle *iommu_fwnode,
		      स्थिर काष्ठा iommu_ops *ops);
व्योम iommu_fwspec_मुक्त(काष्ठा device *dev);
पूर्णांक iommu_fwspec_add_ids(काष्ठा device *dev, u32 *ids, पूर्णांक num_ids);
स्थिर काष्ठा iommu_ops *iommu_ops_from_fwnode(काष्ठा fwnode_handle *fwnode);

अटल अंतरभूत काष्ठा iommu_fwspec *dev_iommu_fwspec_get(काष्ठा device *dev)
अणु
	अगर (dev->iommu)
		वापस dev->iommu->fwspec;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम dev_iommu_fwspec_set(काष्ठा device *dev,
					काष्ठा iommu_fwspec *fwspec)
अणु
	dev->iommu->fwspec = fwspec;
पूर्ण

अटल अंतरभूत व्योम *dev_iommu_priv_get(काष्ठा device *dev)
अणु
	अगर (dev->iommu)
		वापस dev->iommu->priv;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम dev_iommu_priv_set(काष्ठा device *dev, व्योम *priv)
अणु
	dev->iommu->priv = priv;
पूर्ण

पूर्णांक iommu_probe_device(काष्ठा device *dev);
व्योम iommu_release_device(काष्ठा device *dev);

पूर्णांक iommu_dev_enable_feature(काष्ठा device *dev, क्रमागत iommu_dev_features f);
पूर्णांक iommu_dev_disable_feature(काष्ठा device *dev, क्रमागत iommu_dev_features f);
bool iommu_dev_feature_enabled(काष्ठा device *dev, क्रमागत iommu_dev_features f);
पूर्णांक iommu_aux_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);
व्योम iommu_aux_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);
पूर्णांक iommu_aux_get_pasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev);

काष्ठा iommu_sva *iommu_sva_bind_device(काष्ठा device *dev,
					काष्ठा mm_काष्ठा *mm,
					व्योम *drvdata);
व्योम iommu_sva_unbind_device(काष्ठा iommu_sva *handle);
u32 iommu_sva_get_pasid(काष्ठा iommu_sva *handle);

#अन्यथा /* CONFIG_IOMMU_API */

काष्ठा iommu_ops अणुपूर्ण;
काष्ठा iommu_group अणुपूर्ण;
काष्ठा iommu_fwspec अणुपूर्ण;
काष्ठा iommu_device अणुपूर्ण;
काष्ठा iommu_fault_param अणुपूर्ण;
काष्ठा iommu_iotlb_gather अणुपूर्ण;

अटल अंतरभूत bool iommu_present(काष्ठा bus_type *bus)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool iommu_capable(काष्ठा bus_type *bus, क्रमागत iommu_cap cap)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा iommu_करोमुख्य *iommu_करोमुख्य_alloc(काष्ठा bus_type *bus)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा iommu_group *iommu_group_get_by_id(पूर्णांक id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				      काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				       काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत काष्ठा iommu_करोमुख्य *iommu_get_करोमुख्य_क्रम_dev(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			    phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_map_atomic(काष्ठा iommu_करोमुख्य *करोमुख्य,
				   अचिन्हित दीर्घ iova, phys_addr_t paddr,
				   माप_प्रकार size, पूर्णांक prot)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत माप_प्रकार iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार iommu_unmap_fast(काष्ठा iommu_करोमुख्य *करोमुख्य,
				      अचिन्हित दीर्घ iova, पूर्णांक gfp_order,
				      काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार iommu_map_sg(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  अचिन्हित दीर्घ iova, काष्ठा scatterlist *sg,
				  अचिन्हित पूर्णांक nents, पूर्णांक prot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार iommu_map_sg_atomic(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  अचिन्हित दीर्घ iova, काष्ठा scatterlist *sg,
				  अचिन्हित पूर्णांक nents, पूर्णांक prot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iommu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
पूर्ण

अटल अंतरभूत व्योम iommu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
पूर्ण

अटल अंतरभूत phys_addr_t iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t iova)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iommu_set_fault_handler(काष्ठा iommu_करोमुख्य *करोमुख्य,
				iommu_fault_handler_t handler, व्योम *token)
अणु
पूर्ण

अटल अंतरभूत व्योम iommu_get_resv_regions(काष्ठा device *dev,
					काष्ठा list_head *list)
अणु
पूर्ण

अटल अंतरभूत व्योम iommu_put_resv_regions(काष्ठा device *dev,
					काष्ठा list_head *list)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_get_group_resv_regions(काष्ठा iommu_group *group,
					       काष्ठा list_head *head)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम iommu_set_शेष_passthrough(bool cmd_line)
अणु
पूर्ण

अटल अंतरभूत व्योम iommu_set_शेष_translated(bool cmd_line)
अणु
पूर्ण

अटल अंतरभूत bool iommu_शेष_passthrough(व्योम)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_attach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
				     काष्ठा iommu_group *group)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम iommu_detach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
				      काष्ठा iommu_group *group)
अणु
पूर्ण

अटल अंतरभूत काष्ठा iommu_group *iommu_group_alloc(व्योम)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम *iommu_group_get_iommudata(काष्ठा iommu_group *group)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम iommu_group_set_iommudata(काष्ठा iommu_group *group,
					     व्योम *iommu_data,
					     व्योम (*release)(व्योम *iommu_data))
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_group_set_name(काष्ठा iommu_group *group,
				       स्थिर अक्षर *name)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_group_add_device(काष्ठा iommu_group *group,
					 काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम iommu_group_हटाओ_device(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_group_क्रम_each_dev(काष्ठा iommu_group *group,
					   व्योम *data,
					   पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा iommu_group *iommu_group_get(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम iommu_group_put(काष्ठा iommu_group *group)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_group_रेजिस्टर_notअगरier(काष्ठा iommu_group *group,
						काष्ठा notअगरier_block *nb)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_group_unरेजिस्टर_notअगरier(काष्ठा iommu_group *group,
						  काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक iommu_रेजिस्टर_device_fault_handler(काष्ठा device *dev,
					iommu_dev_fault_handler_t handler,
					व्योम *data)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_unरेजिस्टर_device_fault_handler(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक iommu_report_device_fault(काष्ठा device *dev, काष्ठा iommu_fault_event *evt)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_page_response(काष्ठा device *dev,
				      काष्ठा iommu_page_response *msg)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_group_id(काष्ठा iommu_group *group)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_set_pgtable_quirks(काष्ठा iommu_करोमुख्य *करोमुख्य,
		अचिन्हित दीर्घ quirks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_device_रेजिस्टर(काष्ठा iommu_device *iommu,
					स्थिर काष्ठा iommu_ops *ops,
					काष्ठा device *hwdev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा iommu_device *dev_to_iommu_device(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम iommu_iotlb_gather_init(काष्ठा iommu_iotlb_gather *gather)
अणु
पूर्ण

अटल अंतरभूत व्योम iommu_iotlb_gather_add_page(काष्ठा iommu_करोमुख्य *करोमुख्य,
					       काष्ठा iommu_iotlb_gather *gather,
					       अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
पूर्ण

अटल अंतरभूत व्योम iommu_device_unरेजिस्टर(काष्ठा iommu_device *iommu)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक  iommu_device_sysfs_add(काष्ठा iommu_device *iommu,
					  काष्ठा device *parent,
					  स्थिर काष्ठा attribute_group **groups,
					  स्थिर अक्षर *fmt, ...)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम iommu_device_sysfs_हटाओ(काष्ठा iommu_device *iommu)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_device_link(काष्ठा device *dev, काष्ठा device *link)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम iommu_device_unlink(काष्ठा device *dev, काष्ठा device *link)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_fwspec_init(काष्ठा device *dev,
				    काष्ठा fwnode_handle *iommu_fwnode,
				    स्थिर काष्ठा iommu_ops *ops)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम iommu_fwspec_मुक्त(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_fwspec_add_ids(काष्ठा device *dev, u32 *ids,
				       पूर्णांक num_ids)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत
स्थिर काष्ठा iommu_ops *iommu_ops_from_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool
iommu_dev_feature_enabled(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
iommu_dev_enable_feature(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक
iommu_dev_disable_feature(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक
iommu_aux_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम
iommu_aux_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
iommu_aux_get_pasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा iommu_sva *
iommu_sva_bind_device(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm, व्योम *drvdata)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम iommu_sva_unbind_device(काष्ठा iommu_sva *handle)
अणु
पूर्ण

अटल अंतरभूत u32 iommu_sva_get_pasid(काष्ठा iommu_sva *handle)
अणु
	वापस IOMMU_PASID_INVALID;
पूर्ण

अटल अंतरभूत पूर्णांक
iommu_uapi_cache_invalidate(काष्ठा iommu_करोमुख्य *करोमुख्य,
			    काष्ठा device *dev,
			    काष्ठा iommu_cache_invalidate_info *inv_info)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_uapi_sva_bind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य,
					     काष्ठा device *dev, व्योम __user *udata)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_uapi_sva_unbind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य,
					       काष्ठा device *dev, व्योम __user *udata)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_sva_unbind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य,
					  काष्ठा device *dev,
					  ioasid_t pasid)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा iommu_fwspec *dev_iommu_fwspec_get(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_IOMMU_API */

/**
 * iommu_map_sgtable - Map the given buffer to the IOMMU करोमुख्य
 * @करोमुख्य:	The IOMMU करोमुख्य to perक्रमm the mapping
 * @iova:	The start address to map the buffer
 * @sgt:	The sg_table object describing the buffer
 * @prot:	IOMMU protection bits
 *
 * Creates a mapping at @iova क्रम the buffer described by a scatterlist
 * stored in the given sg_table object in the provided IOMMU करोमुख्य.
 */
अटल अंतरभूत माप_प्रकार iommu_map_sgtable(काष्ठा iommu_करोमुख्य *करोमुख्य,
			अचिन्हित दीर्घ iova, काष्ठा sg_table *sgt, पूर्णांक prot)
अणु
	वापस iommu_map_sg(करोमुख्य, iova, sgt->sgl, sgt->orig_nents, prot);
पूर्ण

#अगर_घोषित CONFIG_IOMMU_DEBUGFS
बाह्य	काष्ठा dentry *iommu_debugfs_dir;
व्योम iommu_debugfs_setup(व्योम);
#अन्यथा
अटल अंतरभूत व्योम iommu_debugfs_setup(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_IOMMU_H */
