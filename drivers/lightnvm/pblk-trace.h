<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM pblk

#अगर !defined(_TRACE_PBLK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PBLK_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा ppa_addr;

#घोषणा show_chunk_flags(state) __prपूर्णांक_flags(state, "",	\
	अणु NVM_CHK_ST_FREE,		"FREE",		पूर्ण,	\
	अणु NVM_CHK_ST_CLOSED,		"CLOSED",	पूर्ण,	\
	अणु NVM_CHK_ST_OPEN,		"OPEN",		पूर्ण,	\
	अणु NVM_CHK_ST_OFFLINE,		"OFFLINE",	पूर्ण)

#घोषणा show_line_state(state) __prपूर्णांक_symbolic(state,		\
	अणु PBLK_LINESTATE_NEW,		"NEW",		पूर्ण,	\
	अणु PBLK_LINESTATE_FREE,		"FREE",		पूर्ण,	\
	अणु PBLK_LINESTATE_OPEN,		"OPEN",		पूर्ण,	\
	अणु PBLK_LINESTATE_CLOSED,	"CLOSED",	पूर्ण,	\
	अणु PBLK_LINESTATE_GC,		"GC",		पूर्ण,	\
	अणु PBLK_LINESTATE_BAD,		"BAD",		पूर्ण,	\
	अणु PBLK_LINESTATE_CORRUPT,	"CORRUPT"	पूर्ण)


#घोषणा show_pblk_state(state) __prपूर्णांक_symbolic(state,		\
	अणु PBLK_STATE_RUNNING,		"RUNNING",	पूर्ण,	\
	अणु PBLK_STATE_STOPPING,		"STOPPING",	पूर्ण,	\
	अणु PBLK_STATE_RECOVERING,	"RECOVERING",	पूर्ण,	\
	अणु PBLK_STATE_STOPPED,		"STOPPED"	पूर्ण)

#घोषणा show_chunk_erase_state(state) __prपूर्णांक_symbolic(state,	\
	अणु PBLK_CHUNK_RESET_START,	"START",	पूर्ण,	\
	अणु PBLK_CHUNK_RESET_DONE,	"OK",		पूर्ण,	\
	अणु PBLK_CHUNK_RESET_FAILED,	"FAILED"	पूर्ण)


TRACE_EVENT(pblk_chunk_reset,

	TP_PROTO(स्थिर अक्षर *name, काष्ठा ppa_addr *ppa, पूर्णांक state),

	TP_ARGS(name, ppa, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(u64, ppa)
		__field(पूर्णांक, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->ppa = ppa->ppa;
		__entry->state = state;
	),

	TP_prपूर्णांकk("dev=%s grp=%llu pu=%llu chk=%llu state=%s", __get_str(name),
			(u64)(((काष्ठा ppa_addr *)(&__entry->ppa))->m.grp),
			(u64)(((काष्ठा ppa_addr *)(&__entry->ppa))->m.pu),
			(u64)(((काष्ठा ppa_addr *)(&__entry->ppa))->m.chk),
			show_chunk_erase_state((पूर्णांक)__entry->state))

);

TRACE_EVENT(pblk_chunk_state,

	TP_PROTO(स्थिर अक्षर *name, काष्ठा ppa_addr *ppa, पूर्णांक state),

	TP_ARGS(name, ppa, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(u64, ppa)
		__field(पूर्णांक, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->ppa = ppa->ppa;
		__entry->state = state;
	),

	TP_prपूर्णांकk("dev=%s grp=%llu pu=%llu chk=%llu state=%s", __get_str(name),
			(u64)(((काष्ठा ppa_addr *)(&__entry->ppa))->m.grp),
			(u64)(((काष्ठा ppa_addr *)(&__entry->ppa))->m.pu),
			(u64)(((काष्ठा ppa_addr *)(&__entry->ppa))->m.chk),
			show_chunk_flags((पूर्णांक)__entry->state))

);

TRACE_EVENT(pblk_line_state,

	TP_PROTO(स्थिर अक्षर *name, पूर्णांक line, पूर्णांक state),

	TP_ARGS(name, line, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(पूर्णांक, line)
		__field(पूर्णांक, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->line = line;
		__entry->state = state;
	),

	TP_prपूर्णांकk("dev=%s line=%d state=%s", __get_str(name),
			(पूर्णांक)__entry->line,
			show_line_state((पूर्णांक)__entry->state))

);

TRACE_EVENT(pblk_state,

	TP_PROTO(स्थिर अक्षर *name, पूर्णांक state),

	TP_ARGS(name, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(पूर्णांक, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->state = state;
	),

	TP_prपूर्णांकk("dev=%s state=%s", __get_str(name),
			show_pblk_state((पूर्णांक)__entry->state))

);

#पूर्ण_अगर /* !defined(_TRACE_PBLK_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/lightnvm
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता pblk-trace
#समावेश <trace/define_trace.h>
