<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * iommu trace poपूर्णांकs
 *
 * Copyright (C) 2013 Shuah Khan <shuah.kh@samsung.com>
 *
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iommu

#अगर !defined(_TRACE_IOMMU_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_IOMMU_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा device;

DECLARE_EVENT_CLASS(iommu_group_event,

	TP_PROTO(पूर्णांक group_id, काष्ठा device *dev),

	TP_ARGS(group_id, dev),

	TP_STRUCT__entry(
		__field(पूर्णांक, gid)
		__string(device, dev_name(dev))
	),

	TP_fast_assign(
		__entry->gid = group_id;
		__assign_str(device, dev_name(dev));
	),

	TP_prपूर्णांकk("IOMMU: groupID=%d device=%s",
			__entry->gid, __get_str(device)
	)
);

DEFINE_EVENT(iommu_group_event, add_device_to_group,

	TP_PROTO(पूर्णांक group_id, काष्ठा device *dev),

	TP_ARGS(group_id, dev)

);

DEFINE_EVENT(iommu_group_event, हटाओ_device_from_group,

	TP_PROTO(पूर्णांक group_id, काष्ठा device *dev),

	TP_ARGS(group_id, dev)
);

DECLARE_EVENT_CLASS(iommu_device_event,

	TP_PROTO(काष्ठा device *dev),

	TP_ARGS(dev),

	TP_STRUCT__entry(
		__string(device, dev_name(dev))
	),

	TP_fast_assign(
		__assign_str(device, dev_name(dev));
	),

	TP_prपूर्णांकk("IOMMU: device=%s", __get_str(device)
	)
);

DEFINE_EVENT(iommu_device_event, attach_device_to_करोमुख्य,

	TP_PROTO(काष्ठा device *dev),

	TP_ARGS(dev)
);

DEFINE_EVENT(iommu_device_event, detach_device_from_करोमुख्य,

	TP_PROTO(काष्ठा device *dev),

	TP_ARGS(dev)
);

TRACE_EVENT(map,

	TP_PROTO(अचिन्हित दीर्घ iova, phys_addr_t paddr, माप_प्रकार size),

	TP_ARGS(iova, paddr, size),

	TP_STRUCT__entry(
		__field(u64, iova)
		__field(u64, paddr)
		__field(माप_प्रकार, size)
	),

	TP_fast_assign(
		__entry->iova = iova;
		__entry->paddr = paddr;
		__entry->size = size;
	),

	TP_prपूर्णांकk("IOMMU: iova=0x%016llx paddr=0x%016llx size=%zu",
			__entry->iova, __entry->paddr, __entry->size
	)
);

TRACE_EVENT(unmap,

	TP_PROTO(अचिन्हित दीर्घ iova, माप_प्रकार size, माप_प्रकार unmapped_size),

	TP_ARGS(iova, size, unmapped_size),

	TP_STRUCT__entry(
		__field(u64, iova)
		__field(माप_प्रकार, size)
		__field(माप_प्रकार, unmapped_size)
	),

	TP_fast_assign(
		__entry->iova = iova;
		__entry->size = size;
		__entry->unmapped_size = unmapped_size;
	),

	TP_prपूर्णांकk("IOMMU: iova=0x%016llx size=%zu unmapped_size=%zu",
			__entry->iova, __entry->size, __entry->unmapped_size
	)
);

DECLARE_EVENT_CLASS(iommu_error,

	TP_PROTO(काष्ठा device *dev, अचिन्हित दीर्घ iova, पूर्णांक flags),

	TP_ARGS(dev, iova, flags),

	TP_STRUCT__entry(
		__string(device, dev_name(dev))
		__string(driver, dev_driver_string(dev))
		__field(u64, iova)
		__field(पूर्णांक, flags)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(dev));
		__assign_str(driver, dev_driver_string(dev));
		__entry->iova = iova;
		__entry->flags = flags;
	),

	TP_prपूर्णांकk("IOMMU:%s %s iova=0x%016llx flags=0x%04x",
			__get_str(driver), __get_str(device),
			__entry->iova, __entry->flags
	)
);

DEFINE_EVENT(iommu_error, io_page_fault,

	TP_PROTO(काष्ठा device *dev, अचिन्हित दीर्घ iova, पूर्णांक flags),

	TP_ARGS(dev, iova, flags)
);
#पूर्ण_अगर /* _TRACE_IOMMU_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
