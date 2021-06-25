<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * GPU memory trace poपूर्णांकs
 *
 * Copyright (C) 2020 Google, Inc.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM gpu_mem

#अगर !defined(_TRACE_GPU_MEM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_GPU_MEM_H

#समावेश <linux/tracepoपूर्णांक.h>

/*
 * The gpu_memory_total event indicates that there's an update to either the
 * global or process total gpu memory counters.
 *
 * This event should be emitted whenever the kernel device driver allocates,
 * मुक्तs, imports, unimports memory in the GPU addressable space.
 *
 * @gpu_id: This is the gpu id.
 *
 * @pid: Put 0 क्रम global total, जबतक positive pid क्रम process total.
 *
 * @size: Size of the allocation in bytes.
 *
 */
TRACE_EVENT(gpu_mem_total,

	TP_PROTO(uपूर्णांक32_t gpu_id, uपूर्णांक32_t pid, uपूर्णांक64_t size),

	TP_ARGS(gpu_id, pid, size),

	TP_STRUCT__entry(
		__field(uपूर्णांक32_t, gpu_id)
		__field(uपूर्णांक32_t, pid)
		__field(uपूर्णांक64_t, size)
	),

	TP_fast_assign(
		__entry->gpu_id = gpu_id;
		__entry->pid = pid;
		__entry->size = size;
	),

	TP_prपूर्णांकk("gpu_id=%u pid=%u size=%llu",
		__entry->gpu_id,
		__entry->pid,
		__entry->size)
);

#पूर्ण_अगर /* _TRACE_GPU_MEM_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
