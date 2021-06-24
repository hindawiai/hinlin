<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Interconnect framework tracepoपूर्णांकs
 * Copyright (c) 2019, Linaro Ltd.
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM पूर्णांकerconnect

#अगर !defined(_TRACE_INTERCONNECT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_INTERCONNECT_H

#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(icc_set_bw,

	TP_PROTO(काष्ठा icc_path *p, काष्ठा icc_node *n, पूर्णांक i,
		 u32 avg_bw, u32 peak_bw),

	TP_ARGS(p, n, i, avg_bw, peak_bw),

	TP_STRUCT__entry(
		__string(path_name, p->name)
		__string(dev, dev_name(p->reqs[i].dev))
		__string(node_name, n->name)
		__field(u32, avg_bw)
		__field(u32, peak_bw)
		__field(u32, node_avg_bw)
		__field(u32, node_peak_bw)
	),

	TP_fast_assign(
		__assign_str(path_name, p->name);
		__assign_str(dev, dev_name(p->reqs[i].dev));
		__assign_str(node_name, n->name);
		__entry->avg_bw = avg_bw;
		__entry->peak_bw = peak_bw;
		__entry->node_avg_bw = n->avg_bw;
		__entry->node_peak_bw = n->peak_bw;
	),

	TP_prपूर्णांकk("path=%s dev=%s node=%s avg_bw=%u peak_bw=%u agg_avg=%u agg_peak=%u",
		  __get_str(path_name),
		  __get_str(dev),
		  __get_str(node_name),
		  __entry->avg_bw,
		  __entry->peak_bw,
		  __entry->node_avg_bw,
		  __entry->node_peak_bw)
);

TRACE_EVENT(icc_set_bw_end,

	TP_PROTO(काष्ठा icc_path *p, पूर्णांक ret),

	TP_ARGS(p, ret),

	TP_STRUCT__entry(
		__string(path_name, p->name)
		__string(dev, dev_name(p->reqs[0].dev))
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__assign_str(path_name, p->name);
		__assign_str(dev, dev_name(p->reqs[0].dev));
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("path=%s dev=%s ret=%d",
		  __get_str(path_name),
		  __get_str(dev),
		  __entry->ret)
);

#पूर्ण_अगर /* _TRACE_INTERCONNECT_H */

/* This part must be outside protection */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
