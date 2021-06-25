<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM समयr

#अगर !defined(_TRACE_TIMER_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_TIMER_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/समयr.h>

DECLARE_EVENT_CLASS(समयr_class,

	TP_PROTO(काष्ठा समयr_list *समयr),

	TP_ARGS(समयr),

	TP_STRUCT__entry(
		__field( व्योम *,	समयr	)
	),

	TP_fast_assign(
		__entry->समयr	= समयr;
	),

	TP_prपूर्णांकk("timer=%p", __entry->समयr)
);

/**
 * समयr_init - called when the समयr is initialized
 * @समयr:	poपूर्णांकer to काष्ठा समयr_list
 */
DEFINE_EVENT(समयr_class, समयr_init,

	TP_PROTO(काष्ठा समयr_list *समयr),

	TP_ARGS(समयr)
);

#घोषणा decode_समयr_flags(flags)			\
	__prपूर्णांक_flags(flags, "|",			\
		अणु  TIMER_MIGRATING,	"M" पूर्ण,		\
		अणु  TIMER_DEFERRABLE,	"D" पूर्ण,		\
		अणु  TIMER_PINNED,	"P" पूर्ण,		\
		अणु  TIMER_IRQSAFE,	"I" पूर्ण)

/**
 * समयr_start - called when the समयr is started
 * @समयr:	poपूर्णांकer to काष्ठा समयr_list
 * @expires:	the समयrs expiry समय
 */
TRACE_EVENT(समयr_start,

	TP_PROTO(काष्ठा समयr_list *समयr,
		अचिन्हित दीर्घ expires,
		अचिन्हित पूर्णांक flags),

	TP_ARGS(समयr, expires, flags),

	TP_STRUCT__entry(
		__field( व्योम *,	समयr		)
		__field( व्योम *,	function	)
		__field( अचिन्हित दीर्घ,	expires		)
		__field( अचिन्हित दीर्घ,	now		)
		__field( अचिन्हित पूर्णांक,	flags		)
	),

	TP_fast_assign(
		__entry->समयr		= समयr;
		__entry->function	= समयr->function;
		__entry->expires	= expires;
		__entry->now		= jअगरfies;
		__entry->flags		= flags;
	),

	TP_prपूर्णांकk("timer=%p function=%ps expires=%lu [timeout=%ld] cpu=%u idx=%u flags=%s",
		  __entry->समयr, __entry->function, __entry->expires,
		  (दीर्घ)__entry->expires - __entry->now,
		  __entry->flags & TIMER_CPUMASK,
		  __entry->flags >> TIMER_ARRAYSHIFT,
		  decode_समयr_flags(__entry->flags & TIMER_TRACE_FLAGMASK))
);

/**
 * समयr_expire_entry - called immediately beक्रमe the समयr callback
 * @समयr:	poपूर्णांकer to काष्ठा समयr_list
 *
 * Allows to determine the समयr latency.
 */
TRACE_EVENT(समयr_expire_entry,

	TP_PROTO(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ baseclk),

	TP_ARGS(समयr, baseclk),

	TP_STRUCT__entry(
		__field( व्योम *,	समयr	)
		__field( अचिन्हित दीर्घ,	now	)
		__field( व्योम *,	function)
		__field( अचिन्हित दीर्घ,	baseclk	)
	),

	TP_fast_assign(
		__entry->समयr		= समयr;
		__entry->now		= jअगरfies;
		__entry->function	= समयr->function;
		__entry->baseclk	= baseclk;
	),

	TP_prपूर्णांकk("timer=%p function=%ps now=%lu baseclk=%lu",
		  __entry->समयr, __entry->function, __entry->now,
		  __entry->baseclk)
);

/**
 * समयr_expire_निकास - called immediately after the समयr callback वापसs
 * @समयr:	poपूर्णांकer to काष्ठा समयr_list
 *
 * When used in combination with the समयr_expire_entry tracepoपूर्णांक we can
 * determine the runसमय of the समयr callback function.
 *
 * NOTE: Do NOT dereference समयr in TP_fast_assign. The poपूर्णांकer might
 * be invalid. We solely track the poपूर्णांकer.
 */
DEFINE_EVENT(समयr_class, समयr_expire_निकास,

	TP_PROTO(काष्ठा समयr_list *समयr),

	TP_ARGS(समयr)
);

/**
 * समयr_cancel - called when the समयr is canceled
 * @समयr:	poपूर्णांकer to काष्ठा समयr_list
 */
DEFINE_EVENT(समयr_class, समयr_cancel,

	TP_PROTO(काष्ठा समयr_list *समयr),

	TP_ARGS(समयr)
);

#घोषणा decode_घड़ीid(type)						\
	__prपूर्णांक_symbolic(type,						\
		अणु CLOCK_REALTIME,	"CLOCK_REALTIME"	पूर्ण,	\
		अणु CLOCK_MONOTONIC,	"CLOCK_MONOTONIC"	पूर्ण,	\
		अणु CLOCK_BOOTTIME,	"CLOCK_BOOTTIME"	पूर्ण,	\
		अणु CLOCK_TAI,		"CLOCK_TAI"		पूर्ण)

#घोषणा decode_hrसमयr_mode(mode)					\
	__prपूर्णांक_symbolic(mode,						\
		अणु HRTIMER_MODE_ABS,		"ABS"		पूर्ण,	\
		अणु HRTIMER_MODE_REL,		"REL"		पूर्ण,	\
		अणु HRTIMER_MODE_ABS_PINNED,	"ABS|PINNED"	पूर्ण,	\
		अणु HRTIMER_MODE_REL_PINNED,	"REL|PINNED"	पूर्ण,	\
		अणु HRTIMER_MODE_ABS_SOFT,	"ABS|SOFT"	पूर्ण,	\
		अणु HRTIMER_MODE_REL_SOFT,	"REL|SOFT"	पूर्ण,	\
		अणु HRTIMER_MODE_ABS_PINNED_SOFT,	"ABS|PINNED|SOFT" पूर्ण,	\
		अणु HRTIMER_MODE_REL_PINNED_SOFT,	"REL|PINNED|SOFT" पूर्ण)

/**
 * hrसमयr_init - called when the hrसमयr is initialized
 * @hrसमयr:	poपूर्णांकer to काष्ठा hrसमयr
 * @घड़ीid:	the hrसमयrs घड़ी
 * @mode:	the hrसमयrs mode
 */
TRACE_EVENT(hrसमयr_init,

	TP_PROTO(काष्ठा hrसमयr *hrसमयr, घड़ीid_t घड़ीid,
		 क्रमागत hrसमयr_mode mode),

	TP_ARGS(hrसमयr, घड़ीid, mode),

	TP_STRUCT__entry(
		__field( व्योम *,		hrसमयr		)
		__field( घड़ीid_t,		घड़ीid		)
		__field( क्रमागत hrसमयr_mode,	mode		)
	),

	TP_fast_assign(
		__entry->hrसमयr	= hrसमयr;
		__entry->घड़ीid	= घड़ीid;
		__entry->mode		= mode;
	),

	TP_prपूर्णांकk("hrtimer=%p clockid=%s mode=%s", __entry->hrसमयr,
		  decode_घड़ीid(__entry->घड़ीid),
		  decode_hrसमयr_mode(__entry->mode))
);

/**
 * hrसमयr_start - called when the hrसमयr is started
 * @hrसमयr: poपूर्णांकer to काष्ठा hrसमयr
 */
TRACE_EVENT(hrसमयr_start,

	TP_PROTO(काष्ठा hrसमयr *hrसमयr, क्रमागत hrसमयr_mode mode),

	TP_ARGS(hrसमयr, mode),

	TP_STRUCT__entry(
		__field( व्योम *,	hrसमयr		)
		__field( व्योम *,	function	)
		__field( s64,		expires		)
		__field( s64,		softexpires	)
		__field( क्रमागत hrसमयr_mode,	mode	)
	),

	TP_fast_assign(
		__entry->hrसमयr	= hrसमयr;
		__entry->function	= hrसमयr->function;
		__entry->expires	= hrसमयr_get_expires(hrसमयr);
		__entry->softexpires	= hrसमयr_get_softexpires(hrसमयr);
		__entry->mode		= mode;
	),

	TP_prपूर्णांकk("hrtimer=%p function=%ps expires=%llu softexpires=%llu "
		  "mode=%s", __entry->hrसमयr, __entry->function,
		  (अचिन्हित दीर्घ दीर्घ) __entry->expires,
		  (अचिन्हित दीर्घ दीर्घ) __entry->softexpires,
		  decode_hrसमयr_mode(__entry->mode))
);

/**
 * hrसमयr_expire_entry - called immediately beक्रमe the hrसमयr callback
 * @hrसमयr:	poपूर्णांकer to काष्ठा hrसमयr
 * @now:	poपूर्णांकer to variable which contains current समय of the
 *		समयrs base.
 *
 * Allows to determine the समयr latency.
 */
TRACE_EVENT(hrसमयr_expire_entry,

	TP_PROTO(काष्ठा hrसमयr *hrसमयr, kसमय_प्रकार *now),

	TP_ARGS(hrसमयr, now),

	TP_STRUCT__entry(
		__field( व्योम *,	hrसमयr	)
		__field( s64,		now	)
		__field( व्योम *,	function)
	),

	TP_fast_assign(
		__entry->hrसमयr	= hrसमयr;
		__entry->now		= *now;
		__entry->function	= hrसमयr->function;
	),

	TP_prपूर्णांकk("hrtimer=%p function=%ps now=%llu",
		  __entry->hrसमयr, __entry->function,
		  (अचिन्हित दीर्घ दीर्घ) __entry->now)
);

DECLARE_EVENT_CLASS(hrसमयr_class,

	TP_PROTO(काष्ठा hrसमयr *hrसमयr),

	TP_ARGS(hrसमयr),

	TP_STRUCT__entry(
		__field( व्योम *,	hrसमयr	)
	),

	TP_fast_assign(
		__entry->hrसमयr	= hrसमयr;
	),

	TP_prपूर्णांकk("hrtimer=%p", __entry->hrसमयr)
);

/**
 * hrसमयr_expire_निकास - called immediately after the hrसमयr callback वापसs
 * @hrसमयr:	poपूर्णांकer to काष्ठा hrसमयr
 *
 * When used in combination with the hrसमयr_expire_entry tracepoपूर्णांक we can
 * determine the runसमय of the callback function.
 */
DEFINE_EVENT(hrसमयr_class, hrसमयr_expire_निकास,

	TP_PROTO(काष्ठा hrसमयr *hrसमयr),

	TP_ARGS(hrसमयr)
);

/**
 * hrसमयr_cancel - called when the hrसमयr is canceled
 * @hrसमयr:	poपूर्णांकer to काष्ठा hrसमयr
 */
DEFINE_EVENT(hrसमयr_class, hrसमयr_cancel,

	TP_PROTO(काष्ठा hrसमयr *hrसमयr),

	TP_ARGS(hrसमयr)
);

/**
 * iसमयr_state - called when iसमयr is started or canceled
 * @which:	name of the पूर्णांकerval समयr
 * @value:	the iसमयrs value, iसमयr is canceled अगर value->it_value is
 *		zero, otherwise it is started
 * @expires:	the iसमयrs expiry समय
 */
TRACE_EVENT(iसमयr_state,

	TP_PROTO(पूर्णांक which, स्थिर काष्ठा iसमयrspec64 *स्थिर value,
		 अचिन्हित दीर्घ दीर्घ expires),

	TP_ARGS(which, value, expires),

	TP_STRUCT__entry(
		__field(	पूर्णांक,			which		)
		__field(	अचिन्हित दीर्घ दीर्घ,	expires		)
		__field(	दीर्घ,			value_sec	)
		__field(	दीर्घ,			value_nsec	)
		__field(	दीर्घ,			पूर्णांकerval_sec	)
		__field(	दीर्घ,			पूर्णांकerval_nsec	)
	),

	TP_fast_assign(
		__entry->which		= which;
		__entry->expires	= expires;
		__entry->value_sec	= value->it_value.tv_sec;
		__entry->value_nsec	= value->it_value.tv_nsec;
		__entry->पूर्णांकerval_sec	= value->it_पूर्णांकerval.tv_sec;
		__entry->पूर्णांकerval_nsec	= value->it_पूर्णांकerval.tv_nsec;
	),

	TP_prपूर्णांकk("which=%d expires=%llu it_value=%ld.%06ld it_interval=%ld.%06ld",
		  __entry->which, __entry->expires,
		  __entry->value_sec, __entry->value_nsec / NSEC_PER_USEC,
		  __entry->पूर्णांकerval_sec, __entry->पूर्णांकerval_nsec / NSEC_PER_USEC)
);

/**
 * iसमयr_expire - called when iसमयr expires
 * @which:	type of the पूर्णांकerval समयr
 * @pid:	pid of the process which owns the समयr
 * @now:	current समय, used to calculate the latency of iसमयr
 */
TRACE_EVENT(iसमयr_expire,

	TP_PROTO(पूर्णांक which, काष्ठा pid *pid, अचिन्हित दीर्घ दीर्घ now),

	TP_ARGS(which, pid, now),

	TP_STRUCT__entry(
		__field( पूर्णांक ,			which	)
		__field( pid_t,			pid	)
		__field( अचिन्हित दीर्घ दीर्घ,	now	)
	),

	TP_fast_assign(
		__entry->which	= which;
		__entry->now	= now;
		__entry->pid	= pid_nr(pid);
	),

	TP_prपूर्णांकk("which=%d pid=%d now=%llu", __entry->which,
		  (पूर्णांक) __entry->pid, __entry->now)
);

#अगर_घोषित CONFIG_NO_HZ_COMMON

#घोषणा TICK_DEP_NAMES					\
		tick_dep_mask_name(NONE)		\
		tick_dep_name(POSIX_TIMER)		\
		tick_dep_name(PERF_EVENTS)		\
		tick_dep_name(SCHED)			\
		tick_dep_name(CLOCK_UNSTABLE)		\
		tick_dep_name_end(RCU)

#अघोषित tick_dep_name
#अघोषित tick_dep_mask_name
#अघोषित tick_dep_name_end

/* The MASK will convert to their bits and they need to be processed too */
#घोषणा tick_dep_name(sdep) TRACE_DEFINE_ENUM(TICK_DEP_BIT_##sdep); \
	TRACE_DEFINE_ENUM(TICK_DEP_MASK_##sdep);
#घोषणा tick_dep_name_end(sdep)  TRACE_DEFINE_ENUM(TICK_DEP_BIT_##sdep); \
	TRACE_DEFINE_ENUM(TICK_DEP_MASK_##sdep);
/* NONE only has a mask defined क्रम it */
#घोषणा tick_dep_mask_name(sdep) TRACE_DEFINE_ENUM(TICK_DEP_MASK_##sdep);

TICK_DEP_NAMES

#अघोषित tick_dep_name
#अघोषित tick_dep_mask_name
#अघोषित tick_dep_name_end

#घोषणा tick_dep_name(sdep) अणु TICK_DEP_MASK_##sdep, #sdep पूर्ण,
#घोषणा tick_dep_mask_name(sdep) अणु TICK_DEP_MASK_##sdep, #sdep पूर्ण,
#घोषणा tick_dep_name_end(sdep) अणु TICK_DEP_MASK_##sdep, #sdep पूर्ण

#घोषणा show_tick_dep_name(val)				\
	__prपूर्णांक_symbolic(val, TICK_DEP_NAMES)

TRACE_EVENT(tick_stop,

	TP_PROTO(पूर्णांक success, पूर्णांक dependency),

	TP_ARGS(success, dependency),

	TP_STRUCT__entry(
		__field( पूर्णांक ,		success	)
		__field( पूर्णांक ,		dependency )
	),

	TP_fast_assign(
		__entry->success	= success;
		__entry->dependency	= dependency;
	),

	TP_prपूर्णांकk("success=%d dependency=%s",  __entry->success, \
			show_tick_dep_name(__entry->dependency))
);
#पूर्ण_अगर

#पूर्ण_अगर /*  _TRACE_TIMER_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
