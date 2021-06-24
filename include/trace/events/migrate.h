<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM migrate

#अगर !defined(_TRACE_MIGRATE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_MIGRATE_H

#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा MIGRATE_MODE						\
	EM( MIGRATE_ASYNC,	"MIGRATE_ASYNC")		\
	EM( MIGRATE_SYNC_LIGHT,	"MIGRATE_SYNC_LIGHT")		\
	EMe(MIGRATE_SYNC,	"MIGRATE_SYNC")


#घोषणा MIGRATE_REASON						\
	EM( MR_COMPACTION,	"compaction")			\
	EM( MR_MEMORY_FAILURE,	"memory_failure")		\
	EM( MR_MEMORY_HOTPLUG,	"memory_hotplug")		\
	EM( MR_SYSCALL,		"syscall_or_cpuset")		\
	EM( MR_MEMPOLICY_MBIND,	"mempolicy_mbind")		\
	EM( MR_NUMA_MISPLACED,	"numa_misplaced")		\
	EM( MR_CONTIG_RANGE,	"contig_range")			\
	EMe(MR_LONGTERM_PIN,	"longterm_pin")

/*
 * First define the क्रमागतs in the above macros to be exported to userspace
 * via TRACE_DEFINE_ENUM().
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

MIGRATE_MODE
MIGRATE_REASON

/*
 * Now redefine the EM() and EMe() macros to map the क्रमागतs to the strings
 * that will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	अणुa, bपूर्ण,
#घोषणा EMe(a, b)	अणुa, bपूर्ण

TRACE_EVENT(mm_migrate_pages,

	TP_PROTO(अचिन्हित दीर्घ succeeded, अचिन्हित दीर्घ failed,
		 अचिन्हित दीर्घ thp_succeeded, अचिन्हित दीर्घ thp_failed,
		 अचिन्हित दीर्घ thp_split, क्रमागत migrate_mode mode, पूर्णांक reason),

	TP_ARGS(succeeded, failed, thp_succeeded, thp_failed,
		thp_split, mode, reason),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,		succeeded)
		__field(	अचिन्हित दीर्घ,		failed)
		__field(	अचिन्हित दीर्घ,		thp_succeeded)
		__field(	अचिन्हित दीर्घ,		thp_failed)
		__field(	अचिन्हित दीर्घ,		thp_split)
		__field(	क्रमागत migrate_mode,	mode)
		__field(	पूर्णांक,			reason)
	),

	TP_fast_assign(
		__entry->succeeded	= succeeded;
		__entry->failed		= failed;
		__entry->thp_succeeded	= thp_succeeded;
		__entry->thp_failed	= thp_failed;
		__entry->thp_split	= thp_split;
		__entry->mode		= mode;
		__entry->reason		= reason;
	),

	TP_prपूर्णांकk("nr_succeeded=%lu nr_failed=%lu nr_thp_succeeded=%lu nr_thp_failed=%lu nr_thp_split=%lu mode=%s reason=%s",
		__entry->succeeded,
		__entry->failed,
		__entry->thp_succeeded,
		__entry->thp_failed,
		__entry->thp_split,
		__prपूर्णांक_symbolic(__entry->mode, MIGRATE_MODE),
		__prपूर्णांक_symbolic(__entry->reason, MIGRATE_REASON))
);

TRACE_EVENT(mm_migrate_pages_start,

	TP_PROTO(क्रमागत migrate_mode mode, पूर्णांक reason),

	TP_ARGS(mode, reason),

	TP_STRUCT__entry(
		__field(क्रमागत migrate_mode, mode)
		__field(पूर्णांक, reason)
	),

	TP_fast_assign(
		__entry->mode	= mode;
		__entry->reason	= reason;
	),

	TP_prपूर्णांकk("mode=%s reason=%s",
		  __prपूर्णांक_symbolic(__entry->mode, MIGRATE_MODE),
		  __prपूर्णांक_symbolic(__entry->reason, MIGRATE_REASON))
);

#पूर्ण_अगर /* _TRACE_MIGRATE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
