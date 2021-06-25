<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * iommu trace poपूर्णांकs
 *
 * Copyright (C) 2013 Shuah Khan <shuah.kh@samsung.com>
 *
 */

#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/iommu.h>

/* iommu_group_event */
EXPORT_TRACEPOINT_SYMBOL_GPL(add_device_to_group);
EXPORT_TRACEPOINT_SYMBOL_GPL(हटाओ_device_from_group);

/* iommu_device_event */
EXPORT_TRACEPOINT_SYMBOL_GPL(attach_device_to_करोमुख्य);
EXPORT_TRACEPOINT_SYMBOL_GPL(detach_device_from_करोमुख्य);

/* iommu_map_unmap */
EXPORT_TRACEPOINT_SYMBOL_GPL(map);
EXPORT_TRACEPOINT_SYMBOL_GPL(unmap);

/* iommu_error */
EXPORT_TRACEPOINT_SYMBOL_GPL(io_page_fault);
