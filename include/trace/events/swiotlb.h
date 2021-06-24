<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM swiotlb

#अगर !defined(_TRACE_SWIOTLB_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SWIOTLB_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(swiotlb_bounced,

	TP_PROTO(काष्ठा device *dev,
		 dma_addr_t dev_addr,
		 माप_प्रकार size,
		 क्रमागत swiotlb_क्रमce swiotlb_क्रमce),

	TP_ARGS(dev, dev_addr, size, swiotlb_क्रमce),

	TP_STRUCT__entry(
		__string(	dev_name,	dev_name(dev)		)
		__field(	u64,	dma_mask			)
		__field(	dma_addr_t,	dev_addr		)
		__field(	माप_प्रकार,	size				)
		__field(	क्रमागत swiotlb_क्रमce,	swiotlb_क्रमce	)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name(dev));
		__entry->dma_mask = (dev->dma_mask ? *dev->dma_mask : 0);
		__entry->dev_addr = dev_addr;
		__entry->size = size;
		__entry->swiotlb_क्रमce = swiotlb_क्रमce;
	),

	TP_prपूर्णांकk("dev_name: %s dma_mask=%llx dev_addr=%llx "
		"size=%zu %s",
		__get_str(dev_name),
		__entry->dma_mask,
		(अचिन्हित दीर्घ दीर्घ)__entry->dev_addr,
		__entry->size,
		__prपूर्णांक_symbolic(__entry->swiotlb_क्रमce,
			अणु SWIOTLB_NORMAL,	"NORMAL" पूर्ण,
			अणु SWIOTLB_FORCE,	"FORCE" पूर्ण,
			अणु SWIOTLB_NO_FORCE,	"NO_FORCE" पूर्ण))
);

#पूर्ण_अगर /*  _TRACE_SWIOTLB_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
