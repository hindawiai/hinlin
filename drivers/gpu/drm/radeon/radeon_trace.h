<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर !defined(_RADEON_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _RADEON_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/types.h>

#समावेश <drm/drm_file.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM radeon
#घोषणा TRACE_INCLUDE_खाता radeon_trace

TRACE_EVENT(radeon_bo_create,
	    TP_PROTO(काष्ठा radeon_bo *bo),
	    TP_ARGS(bo),
	    TP_STRUCT__entry(
			     __field(काष्ठा radeon_bo *, bo)
			     __field(u32, pages)
			     ),

	    TP_fast_assign(
			   __entry->bo = bo;
			   __entry->pages = bo->tbo.mem.num_pages;
			   ),
	    TP_prपूर्णांकk("bo=%p, pages=%u", __entry->bo, __entry->pages)
);

TRACE_EVENT(radeon_cs,
	    TP_PROTO(काष्ठा radeon_cs_parser *p),
	    TP_ARGS(p),
	    TP_STRUCT__entry(
			     __field(u32, ring)
			     __field(u32, dw)
			     __field(u32, fences)
			     ),

	    TP_fast_assign(
			   __entry->ring = p->ring;
			   __entry->dw = p->chunk_ib->length_dw;
			   __entry->fences = radeon_fence_count_emitted(
				p->rdev, p->ring);
			   ),
	    TP_prपूर्णांकk("ring=%u, dw=%u, fences=%u",
		      __entry->ring, __entry->dw,
		      __entry->fences)
);

TRACE_EVENT(radeon_vm_grab_id,
	    TP_PROTO(अचिन्हित vmid, पूर्णांक ring),
	    TP_ARGS(vmid, ring),
	    TP_STRUCT__entry(
			     __field(u32, vmid)
			     __field(u32, ring)
			     ),

	    TP_fast_assign(
			   __entry->vmid = vmid;
			   __entry->ring = ring;
			   ),
	    TP_prपूर्णांकk("vmid=%u, ring=%u", __entry->vmid, __entry->ring)
);

TRACE_EVENT(radeon_vm_bo_update,
	    TP_PROTO(काष्ठा radeon_bo_va *bo_va),
	    TP_ARGS(bo_va),
	    TP_STRUCT__entry(
			     __field(u64, soffset)
			     __field(u64, eoffset)
			     __field(u32, flags)
			     ),

	    TP_fast_assign(
			   __entry->soffset = bo_va->it.start;
			   __entry->eoffset = bo_va->it.last + 1;
			   __entry->flags = bo_va->flags;
			   ),
	    TP_prपूर्णांकk("soffs=%010llx, eoffs=%010llx, flags=%08x",
		      __entry->soffset, __entry->eoffset, __entry->flags)
);

TRACE_EVENT(radeon_vm_set_page,
	    TP_PROTO(uपूर्णांक64_t pe, uपूर्णांक64_t addr, अचिन्हित count,
		     uपूर्णांक32_t incr, uपूर्णांक32_t flags),
	    TP_ARGS(pe, addr, count, incr, flags),
	    TP_STRUCT__entry(
			     __field(u64, pe)
			     __field(u64, addr)
			     __field(u32, count)
			     __field(u32, incr)
			     __field(u32, flags)
			     ),

	    TP_fast_assign(
			   __entry->pe = pe;
			   __entry->addr = addr;
			   __entry->count = count;
			   __entry->incr = incr;
			   __entry->flags = flags;
			   ),
	    TP_prपूर्णांकk("pe=%010Lx, addr=%010Lx, incr=%u, flags=%08x, count=%u",
		      __entry->pe, __entry->addr, __entry->incr,
		      __entry->flags, __entry->count)
);

TRACE_EVENT(radeon_vm_flush,
	    TP_PROTO(uपूर्णांक64_t pd_addr, अचिन्हित ring, अचिन्हित id),
	    TP_ARGS(pd_addr, ring, id),
	    TP_STRUCT__entry(
			     __field(u64, pd_addr)
			     __field(u32, ring)
			     __field(u32, id)
			     ),

	    TP_fast_assign(
			   __entry->pd_addr = pd_addr;
			   __entry->ring = ring;
			   __entry->id = id;
			   ),
	    TP_prपूर्णांकk("pd_addr=%010Lx, ring=%u, id=%u",
		      __entry->pd_addr, __entry->ring, __entry->id)
);

DECLARE_EVENT_CLASS(radeon_fence_request,

	    TP_PROTO(काष्ठा drm_device *dev, पूर्णांक ring, u32 seqno),

	    TP_ARGS(dev, ring, seqno),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(पूर्णांक, ring)
			     __field(u32, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->ring = ring;
			   __entry->seqno = seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, ring=%d, seqno=%u",
		      __entry->dev, __entry->ring, __entry->seqno)
);

DEFINE_EVENT(radeon_fence_request, radeon_fence_emit,

	    TP_PROTO(काष्ठा drm_device *dev, पूर्णांक ring, u32 seqno),

	    TP_ARGS(dev, ring, seqno)
);

DEFINE_EVENT(radeon_fence_request, radeon_fence_रुको_begin,

	    TP_PROTO(काष्ठा drm_device *dev, पूर्णांक ring, u32 seqno),

	    TP_ARGS(dev, ring, seqno)
);

DEFINE_EVENT(radeon_fence_request, radeon_fence_रुको_end,

	    TP_PROTO(काष्ठा drm_device *dev, पूर्णांक ring, u32 seqno),

	    TP_ARGS(dev, ring, seqno)
);

DECLARE_EVENT_CLASS(radeon_semaphore_request,

	    TP_PROTO(पूर्णांक ring, काष्ठा radeon_semaphore *sem),

	    TP_ARGS(ring, sem),

	    TP_STRUCT__entry(
			     __field(पूर्णांक, ring)
			     __field(चिन्हित, रुकोers)
			     __field(uपूर्णांक64_t, gpu_addr)
			     ),

	    TP_fast_assign(
			   __entry->ring = ring;
			   __entry->रुकोers = sem->रुकोers;
			   __entry->gpu_addr = sem->gpu_addr;
			   ),

	    TP_prपूर्णांकk("ring=%u, waiters=%d, addr=%010Lx", __entry->ring,
		      __entry->रुकोers, __entry->gpu_addr)
);

DEFINE_EVENT(radeon_semaphore_request, radeon_semaphore_संकेतe,

	    TP_PROTO(पूर्णांक ring, काष्ठा radeon_semaphore *sem),

	    TP_ARGS(ring, sem)
);

DEFINE_EVENT(radeon_semaphore_request, radeon_semaphore_रुको,

	    TP_PROTO(पूर्णांक ring, काष्ठा radeon_semaphore *sem),

	    TP_ARGS(ring, sem)
);

#पूर्ण_अगर

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/radeon
#समावेश <trace/define_trace.h>
