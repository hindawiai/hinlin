<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Broadcom
 */

#अगर !defined(_VC4_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _VC4_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM vc4
#घोषणा TRACE_INCLUDE_खाता vc4_trace

TRACE_EVENT(vc4_रुको_क्रम_seqno_begin,
	    TP_PROTO(काष्ठा drm_device *dev, uपूर्णांक64_t seqno, uपूर्णांक64_t समयout),
	    TP_ARGS(dev, seqno, समयout),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, seqno)
			     __field(u64, समयout)
			     ),

	    TP_fast_assign(
			   __entry->dev = dev->primary->index;
			   __entry->seqno = seqno;
			   __entry->समयout = समयout;
			   ),

	    TP_prपूर्णांकk("dev=%u, seqno=%llu, timeout=%llu",
		      __entry->dev, __entry->seqno, __entry->समयout)
);

TRACE_EVENT(vc4_रुको_क्रम_seqno_end,
	    TP_PROTO(काष्ठा drm_device *dev, uपूर्णांक64_t seqno),
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
		      __entry->dev, __entry->seqno)
);

#पूर्ण_अगर /* _VC4_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/vc4
#समावेश <trace/define_trace.h>
