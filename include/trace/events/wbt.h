<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM wbt

#अगर !defined(_TRACE_WBT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_WBT_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "../../../block/blk-wbt.h"

/**
 * wbt_stat - trace stats क्रम blk_wb
 * @stat: array of पढ़ो/ग_लिखो stats
 */
TRACE_EVENT(wbt_stat,

	TP_PROTO(काष्ठा backing_dev_info *bdi, काष्ठा blk_rq_stat *stat),

	TP_ARGS(bdi, stat),

	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(s64, rmean)
		__field(u64, rmin)
		__field(u64, rmax)
		__field(s64, rnr_samples)
		__field(s64, rसमय)
		__field(s64, wmean)
		__field(u64, wmin)
		__field(u64, wmax)
		__field(s64, wnr_samples)
		__field(s64, wसमय)
	),

	TP_fast_assign(
		strlcpy(__entry->name, bdi_dev_name(bdi),
			ARRAY_SIZE(__entry->name));
		__entry->rmean		= stat[0].mean;
		__entry->rmin		= stat[0].min;
		__entry->rmax		= stat[0].max;
		__entry->rnr_samples	= stat[0].nr_samples;
		__entry->wmean		= stat[1].mean;
		__entry->wmin		= stat[1].min;
		__entry->wmax		= stat[1].max;
		__entry->wnr_samples	= stat[1].nr_samples;
	),

	TP_prपूर्णांकk("%s: rmean=%llu, rmin=%llu, rmax=%llu, rsamples=%llu, "
		  "wmean=%llu, wmin=%llu, wmax=%llu, wsamples=%llu",
		  __entry->name, __entry->rmean, __entry->rmin, __entry->rmax,
		  __entry->rnr_samples, __entry->wmean, __entry->wmin,
		  __entry->wmax, __entry->wnr_samples)
);

/**
 * wbt_lat - trace latency event
 * @lat: latency trigger
 */
TRACE_EVENT(wbt_lat,

	TP_PROTO(काष्ठा backing_dev_info *bdi, अचिन्हित दीर्घ lat),

	TP_ARGS(bdi, lat),

	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(अचिन्हित दीर्घ, lat)
	),

	TP_fast_assign(
		strlcpy(__entry->name, bdi_dev_name(bdi),
			ARRAY_SIZE(__entry->name));
		__entry->lat = भाग_u64(lat, 1000);
	),

	TP_prपूर्णांकk("%s: latency %lluus", __entry->name,
			(अचिन्हित दीर्घ दीर्घ) __entry->lat)
);

/**
 * wbt_step - trace wb event step
 * @msg: context message
 * @step: the current scale step count
 * @winकरोw: the current monitoring winकरोw
 * @bg: the current background queue limit
 * @normal: the current normal ग_लिखोback limit
 * @max: the current max throughput ग_लिखोback limit
 */
TRACE_EVENT(wbt_step,

	TP_PROTO(काष्ठा backing_dev_info *bdi, स्थिर अक्षर *msg,
		 पूर्णांक step, अचिन्हित दीर्घ winकरोw, अचिन्हित पूर्णांक bg,
		 अचिन्हित पूर्णांक normal, अचिन्हित पूर्णांक max),

	TP_ARGS(bdi, msg, step, winकरोw, bg, normal, max),

	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(स्थिर अक्षर *, msg)
		__field(पूर्णांक, step)
		__field(अचिन्हित दीर्घ, winकरोw)
		__field(अचिन्हित पूर्णांक, bg)
		__field(अचिन्हित पूर्णांक, normal)
		__field(अचिन्हित पूर्णांक, max)
	),

	TP_fast_assign(
		strlcpy(__entry->name, bdi_dev_name(bdi),
			ARRAY_SIZE(__entry->name));
		__entry->msg	= msg;
		__entry->step	= step;
		__entry->winकरोw	= भाग_u64(winकरोw, 1000);
		__entry->bg	= bg;
		__entry->normal	= normal;
		__entry->max	= max;
	),

	TP_prपूर्णांकk("%s: %s: step=%d, window=%luus, background=%u, normal=%u, max=%u",
		  __entry->name, __entry->msg, __entry->step, __entry->winकरोw,
		  __entry->bg, __entry->normal, __entry->max)
);

/**
 * wbt_समयr - trace wb समयr event
 * @status: समयr state status
 * @step: the current scale step count
 * @inflight: tracked ग_लिखोs inflight
 */
TRACE_EVENT(wbt_समयr,

	TP_PROTO(काष्ठा backing_dev_info *bdi, अचिन्हित पूर्णांक status,
		 पूर्णांक step, अचिन्हित पूर्णांक inflight),

	TP_ARGS(bdi, status, step, inflight),

	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(अचिन्हित पूर्णांक, status)
		__field(पूर्णांक, step)
		__field(अचिन्हित पूर्णांक, inflight)
	),

	TP_fast_assign(
		strlcpy(__entry->name, bdi_dev_name(bdi),
			ARRAY_SIZE(__entry->name));
		__entry->status		= status;
		__entry->step		= step;
		__entry->inflight	= inflight;
	),

	TP_prपूर्णांकk("%s: status=%u, step=%d, inflight=%u", __entry->name,
		  __entry->status, __entry->step, __entry->inflight)
);

#पूर्ण_अगर /* _TRACE_WBT_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
