<शैली गुरु>
#अगर !defined(_TRACE_TEGRA_APB_DMA_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_TEGRA_APB_DMA_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/dmaengine.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM tegra_apb_dma

TRACE_EVENT(tegra_dma_tx_status,
	TP_PROTO(काष्ठा dma_chan *dc, dma_cookie_t cookie, काष्ठा dma_tx_state *state),
	TP_ARGS(dc, cookie, state),
	TP_STRUCT__entry(
		__string(chan,	dev_name(&dc->dev->device))
		__field(dma_cookie_t, cookie)
		__field(__u32,	residue)
	),
	TP_fast_assign(
		__assign_str(chan, dev_name(&dc->dev->device));
		__entry->cookie = cookie;
		__entry->residue = state ? state->residue : (u32)-1;
	),
	TP_prपूर्णांकk("channel %s: dma cookie %d, residue %u",
		  __get_str(chan), __entry->cookie, __entry->residue)
);

TRACE_EVENT(tegra_dma_complete_cb,
	TP_PROTO(काष्ठा dma_chan *dc, पूर्णांक count, व्योम *ptr),
	TP_ARGS(dc, count, ptr),
	TP_STRUCT__entry(
		__string(chan,	dev_name(&dc->dev->device))
		__field(पूर्णांक,	count)
		__field(व्योम *,	ptr)
		),
	TP_fast_assign(
		__assign_str(chan, dev_name(&dc->dev->device));
		__entry->count = count;
		__entry->ptr = ptr;
		),
	TP_prपूर्णांकk("channel %s: done %d, ptr %p",
		  __get_str(chan), __entry->count, __entry->ptr)
);

TRACE_EVENT(tegra_dma_isr,
	TP_PROTO(काष्ठा dma_chan *dc, पूर्णांक irq),
	TP_ARGS(dc, irq),
	TP_STRUCT__entry(
		__string(chan,	dev_name(&dc->dev->device))
		__field(पूर्णांक,	irq)
	),
	TP_fast_assign(
		__assign_str(chan, dev_name(&dc->dev->device));
		__entry->irq = irq;
	),
	TP_prपूर्णांकk("%s: irq %d\n",  __get_str(chan), __entry->irq)
);

#पूर्ण_अगर /* _TRACE_TEGRA_APB_DMA_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
