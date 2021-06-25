<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VFIO PCI mmap/mmap_fault tracepoपूर्णांकs
 *
 * Copyright (C) 2018 IBM Corp.  All rights reserved.
 *     Author: Alexey Kardashevskiy <aik@ozद_असल.ru>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM vfio_pci

#अगर !defined(_TRACE_VFIO_PCI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_VFIO_PCI_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(vfio_pci_nvgpu_mmap_fault,
	TP_PROTO(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ ua,
			vm_fault_t ret),
	TP_ARGS(pdev, hpa, ua, ret),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, name)
		__field(अचिन्हित दीर्घ, hpa)
		__field(अचिन्हित दीर्घ, ua)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->name = dev_name(&pdev->dev),
		__entry->hpa = hpa;
		__entry->ua = ua;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("%s: %lx -> %lx ret=%d", __entry->name, __entry->hpa,
			__entry->ua, __entry->ret)
);

TRACE_EVENT(vfio_pci_nvgpu_mmap,
	TP_PROTO(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ ua,
			अचिन्हित दीर्घ size, पूर्णांक ret),
	TP_ARGS(pdev, hpa, ua, size, ret),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, name)
		__field(अचिन्हित दीर्घ, hpa)
		__field(अचिन्हित दीर्घ, ua)
		__field(अचिन्हित दीर्घ, size)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->name = dev_name(&pdev->dev),
		__entry->hpa = hpa;
		__entry->ua = ua;
		__entry->size = size;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("%s: %lx -> %lx size=%lx ret=%d", __entry->name, __entry->hpa,
			__entry->ua, __entry->size, __entry->ret)
);

TRACE_EVENT(vfio_pci_npu2_mmap,
	TP_PROTO(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ ua,
			अचिन्हित दीर्घ size, पूर्णांक ret),
	TP_ARGS(pdev, hpa, ua, size, ret),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, name)
		__field(अचिन्हित दीर्घ, hpa)
		__field(अचिन्हित दीर्घ, ua)
		__field(अचिन्हित दीर्घ, size)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->name = dev_name(&pdev->dev),
		__entry->hpa = hpa;
		__entry->ua = ua;
		__entry->size = size;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("%s: %lx -> %lx size=%lx ret=%d", __entry->name, __entry->hpa,
			__entry->ua, __entry->size, __entry->ret)
);

#पूर्ण_अगर /* _TRACE_VFIO_PCI_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/vfio/pci
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
