<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel IOMMU trace support
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM पूर्णांकel_iommu

#अगर !defined(_TRACE_INTEL_IOMMU_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_INTEL_IOMMU_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/पूर्णांकel-iommu.h>

TRACE_EVENT(qi_submit,
	TP_PROTO(काष्ठा पूर्णांकel_iommu *iommu, u64 qw0, u64 qw1, u64 qw2, u64 qw3),

	TP_ARGS(iommu, qw0, qw1, qw2, qw3),

	TP_STRUCT__entry(
		__field(u64, qw0)
		__field(u64, qw1)
		__field(u64, qw2)
		__field(u64, qw3)
		__string(iommu, iommu->name)
	),

	TP_fast_assign(
		__assign_str(iommu, iommu->name);
		__entry->qw0 = qw0;
		__entry->qw1 = qw1;
		__entry->qw2 = qw2;
		__entry->qw3 = qw3;
	),

	TP_prपूर्णांकk("%s %s: 0x%llx 0x%llx 0x%llx 0x%llx",
		  __prपूर्णांक_symbolic(__entry->qw0 & 0xf,
				   अणु QI_CC_TYPE,	"cc_inv" पूर्ण,
				   अणु QI_IOTLB_TYPE,	"iotlb_inv" पूर्ण,
				   अणु QI_DIOTLB_TYPE,	"dev_tlb_inv" पूर्ण,
				   अणु QI_IEC_TYPE,	"iec_inv" पूर्ण,
				   अणु QI_IWD_TYPE,	"inv_wait" पूर्ण,
				   अणु QI_EIOTLB_TYPE,	"p_iotlb_inv" पूर्ण,
				   अणु QI_PC_TYPE,	"pc_inv" पूर्ण,
				   अणु QI_DEIOTLB_TYPE,	"p_dev_tlb_inv" पूर्ण,
				   अणु QI_PGRP_RESP_TYPE,	"page_grp_resp" पूर्ण),
		__get_str(iommu),
		__entry->qw0, __entry->qw1, __entry->qw2, __entry->qw3
	)
);
#पूर्ण_अगर /* _TRACE_INTEL_IOMMU_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
