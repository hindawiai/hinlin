<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2015-2018 Broadcom */

#अगर !defined(_V3D_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _V3D_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM v3d
#घोषणा TRACE_INCLUDE_खाता v3d_trace

TRACE_EVENT(v3d_submit_cl_ioctl,
	    TP_PROTO(काष्ठा drm_device *dev, u32 ct1qba, u32 ct1qea),
	    TP_ARGS(dev, ct1qba, ct1qea),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u32, ct1qba)
			     __field(u32, ct1qea)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->ct1qba = ct1qba;
			   __entry->ct1qea = ct1qea;
			   ),

	    TP_prपूर्णांकk("dev=%u, RCL 0x%08x..0x%08x",
		      __entry->dev,
		      __entry->ct1qba,
		      __entry->ct1qea)
);

TRACE_EVENT(v3d_submit_cl,
	    TP_PROTO(काष्ठा drm_device *dev, bool is_render,
		     uपूर्णांक64_t seqno,
		     u32 ctnqba, u32 ctnqea),
	    TP_ARGS(dev, is_render, seqno, ctnqba, ctnqea),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(bool, is_render)
			     __field(u64, seqno)
			     __field(u32, ctnqba)
			     __field(u32, ctnqea)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->is_render = is_render;
			   __entry->seqno = seqno;
			   __entry->ctnqba = ctnqba;
			   __entry->ctnqea = ctnqea;
			   ),

	    TP_prपूर्णांकk("dev=%u, %s, seqno=%llu, 0x%08x..0x%08x",
		      __entry->dev,
		      __entry->is_render ? "RCL" : "BCL",
		      __entry->seqno,
		      __entry->ctnqba,
		      __entry->ctnqea)
);

TRACE_EVENT(v3d_bcl_irq,
	    TP_PROTO(काष्ठा drm_device *dev,
		     uपूर्णांक64_t seqno),
	    TP_ARGS(dev, seqno),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->seqno = seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, seqno=%llu",
		      __entry->dev,
		      __entry->seqno)
);

TRACE_EVENT(v3d_rcl_irq,
	    TP_PROTO(काष्ठा drm_device *dev,
		     uपूर्णांक64_t seqno),
	    TP_ARGS(dev, seqno),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->seqno = seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, seqno=%llu",
		      __entry->dev,
		      __entry->seqno)
);

TRACE_EVENT(v3d_tfu_irq,
	    TP_PROTO(काष्ठा drm_device *dev,
		     uपूर्णांक64_t seqno),
	    TP_ARGS(dev, seqno),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->seqno = seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, seqno=%llu",
		      __entry->dev,
		      __entry->seqno)
);

TRACE_EVENT(v3d_csd_irq,
	    TP_PROTO(काष्ठा drm_device *dev,
		     uपूर्णांक64_t seqno),
	    TP_ARGS(dev, seqno),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->seqno = seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, seqno=%llu",
		      __entry->dev,
		      __entry->seqno)
);

TRACE_EVENT(v3d_submit_tfu_ioctl,
	    TP_PROTO(काष्ठा drm_device *dev, u32 iia),
	    TP_ARGS(dev, iia),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u32, iia)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->iia = iia;
			   ),

	    TP_prपूर्णांकk("dev=%u, IIA 0x%08x",
		      __entry->dev,
		      __entry->iia)
);

TRACE_EVENT(v3d_submit_tfu,
	    TP_PROTO(काष्ठा drm_device *dev,
		     uपूर्णांक64_t seqno),
	    TP_ARGS(dev, seqno),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->seqno = seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, seqno=%llu",
		      __entry->dev,
		      __entry->seqno)
);

TRACE_EVENT(v3d_submit_csd_ioctl,
	    TP_PROTO(काष्ठा drm_device *dev, u32 cfg5, u32 cfg6),
	    TP_ARGS(dev, cfg5, cfg6),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u32, cfg5)
			     __field(u32, cfg6)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->cfg5 = cfg5;
			   __entry->cfg6 = cfg6;
			   ),

	    TP_prपूर्णांकk("dev=%u, CFG5 0x%08x, CFG6 0x%08x",
		      __entry->dev,
		      __entry->cfg5,
		      __entry->cfg6)
);

TRACE_EVENT(v3d_submit_csd,
	    TP_PROTO(काष्ठा drm_device *dev,
		     uपूर्णांक64_t seqno),
	    TP_ARGS(dev, seqno),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->seqno = seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, seqno=%llu",
		      __entry->dev,
		      __entry->seqno)
);

TRACE_EVENT(v3d_cache_clean_begin,
	    TP_PROTO(काष्ठा drm_device *dev),
	    TP_ARGS(dev),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   ),

	    TP_prपूर्णांकk("dev=%u",
		      __entry->dev)
);

TRACE_EVENT(v3d_cache_clean_end,
	    TP_PROTO(काष्ठा drm_device *dev),
	    TP_ARGS(dev),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   ),

	    TP_prपूर्णांकk("dev=%u",
		      __entry->dev)
);

TRACE_EVENT(v3d_reset_begin,
	    TP_PROTO(काष्ठा drm_device *dev),
	    TP_ARGS(dev),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   ),

	    TP_prपूर्णांकk("dev=%u",
		      __entry->dev)
);

TRACE_EVENT(v3d_reset_end,
	    TP_PROTO(काष्ठा drm_device *dev),
	    TP_ARGS(dev),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   ),

	    TP_prपूर्णांकk("dev=%u",
		      __entry->dev)
);

#पूर्ण_अगर /* _V3D_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#समावेश <trace/define_trace.h>
