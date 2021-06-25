<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM dma_fence

#अगर !defined(_TRACE_DMA_FENCE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_DMA_FENCE_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा dma_fence;

DECLARE_EVENT_CLASS(dma_fence,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence),

	TP_STRUCT__entry(
		__string(driver, fence->ops->get_driver_name(fence))
		__string(समयline, fence->ops->get_समयline_name(fence))
		__field(अचिन्हित पूर्णांक, context)
		__field(अचिन्हित पूर्णांक, seqno)
	),

	TP_fast_assign(
		__assign_str(driver, fence->ops->get_driver_name(fence))
		__assign_str(समयline, fence->ops->get_समयline_name(fence))
		__entry->context = fence->context;
		__entry->seqno = fence->seqno;
	),

	TP_prपूर्णांकk("driver=%s timeline=%s context=%u seqno=%u",
		  __get_str(driver), __get_str(समयline), __entry->context,
		  __entry->seqno)
);

DEFINE_EVENT(dma_fence, dma_fence_emit,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_init,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_destroy,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_enable_संकेत,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_संकेतed,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_रुको_start,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_रुको_end,

	TP_PROTO(काष्ठा dma_fence *fence),

	TP_ARGS(fence)
);

#पूर्ण_अगर /*  _TRACE_DMA_FENCE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
