<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Network fileप्रणाली support module tracepoपूर्णांकs
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM netfs

#अगर !defined(_TRACE_NETFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NETFS_H

#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Define क्रमागतs क्रम tracing inक्रमmation.
 */
#अगर_अघोषित __NETFS_DECLARE_TRACE_ENUMS_ONCE_ONLY
#घोषणा __NETFS_DECLARE_TRACE_ENUMS_ONCE_ONLY

क्रमागत netfs_पढ़ो_trace अणु
	netfs_पढ़ो_trace_expanded,
	netfs_पढ़ो_trace_पढ़ोahead,
	netfs_पढ़ो_trace_पढ़ोpage,
	netfs_पढ़ो_trace_ग_लिखो_begin,
पूर्ण;

क्रमागत netfs_rreq_trace अणु
	netfs_rreq_trace_assess,
	netfs_rreq_trace_करोne,
	netfs_rreq_trace_मुक्त,
	netfs_rreq_trace_resubmit,
	netfs_rreq_trace_unlock,
	netfs_rreq_trace_unmark,
	netfs_rreq_trace_ग_लिखो,
पूर्ण;

क्रमागत netfs_sreq_trace अणु
	netfs_sreq_trace_करोwnload_instead,
	netfs_sreq_trace_मुक्त,
	netfs_sreq_trace_prepare,
	netfs_sreq_trace_resubmit_लघु,
	netfs_sreq_trace_submit,
	netfs_sreq_trace_terminated,
	netfs_sreq_trace_ग_लिखो,
	netfs_sreq_trace_ग_लिखो_skip,
	netfs_sreq_trace_ग_लिखो_term,
पूर्ण;

क्रमागत netfs_failure अणु
	netfs_fail_check_ग_लिखो_begin,
	netfs_fail_copy_to_cache,
	netfs_fail_पढ़ो,
	netfs_fail_लघु_पढ़ोpage,
	netfs_fail_लघु_ग_लिखो_begin,
	netfs_fail_prepare_ग_लिखो,
पूर्ण;

#पूर्ण_अगर

#घोषणा netfs_पढ़ो_traces					\
	EM(netfs_पढ़ो_trace_expanded,		"EXPANDED ")	\
	EM(netfs_पढ़ो_trace_पढ़ोahead,		"READAHEAD")	\
	EM(netfs_पढ़ो_trace_पढ़ोpage,		"READPAGE ")	\
	E_(netfs_पढ़ो_trace_ग_लिखो_begin,	"WRITEBEGN")

#घोषणा netfs_rreq_traces					\
	EM(netfs_rreq_trace_assess,		"ASSESS")	\
	EM(netfs_rreq_trace_करोne,		"DONE  ")	\
	EM(netfs_rreq_trace_मुक्त,		"FREE  ")	\
	EM(netfs_rreq_trace_resubmit,		"RESUBM")	\
	EM(netfs_rreq_trace_unlock,		"UNLOCK")	\
	EM(netfs_rreq_trace_unmark,		"UNMARK")	\
	E_(netfs_rreq_trace_ग_लिखो,		"WRITE ")

#घोषणा netfs_sreq_sources					\
	EM(NETFS_FILL_WITH_ZEROES,		"ZERO")		\
	EM(NETFS_DOWNLOAD_FROM_SERVER,		"DOWN")		\
	EM(NETFS_READ_FROM_CACHE,		"READ")		\
	E_(NETFS_INVALID_READ,			"INVL")		\

#घोषणा netfs_sreq_traces					\
	EM(netfs_sreq_trace_करोwnload_instead,	"RDOWN")	\
	EM(netfs_sreq_trace_मुक्त,		"FREE ")	\
	EM(netfs_sreq_trace_prepare,		"PREP ")	\
	EM(netfs_sreq_trace_resubmit_लघु,	"SHORT")	\
	EM(netfs_sreq_trace_submit,		"SUBMT")	\
	EM(netfs_sreq_trace_terminated,		"TERM ")	\
	EM(netfs_sreq_trace_ग_लिखो,		"WRITE")	\
	EM(netfs_sreq_trace_ग_लिखो_skip,		"SKIP ")	\
	E_(netfs_sreq_trace_ग_लिखो_term,		"WTERM")

#घोषणा netfs_failures							\
	EM(netfs_fail_check_ग_लिखो_begin,	"check-write-begin")	\
	EM(netfs_fail_copy_to_cache,		"copy-to-cache")	\
	EM(netfs_fail_पढ़ो,			"read")			\
	EM(netfs_fail_लघु_पढ़ोpage,		"short-readpage")	\
	EM(netfs_fail_लघु_ग_लिखो_begin,	"short-write-begin")	\
	E_(netfs_fail_prepare_ग_लिखो,		"prep-write")


/*
 * Export क्रमागत symbols via userspace.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b) TRACE_DEFINE_ENUM(a);
#घोषणा E_(a, b) TRACE_DEFINE_ENUM(a);

netfs_पढ़ो_traces;
netfs_rreq_traces;
netfs_sreq_sources;
netfs_sreq_traces;
netfs_failures;

/*
 * Now redefine the EM() and E_() macros to map the क्रमागतs to the strings that
 * will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b)	अणु a, b पूर्ण,
#घोषणा E_(a, b)	अणु a, b पूर्ण

TRACE_EVENT(netfs_पढ़ो,
	    TP_PROTO(काष्ठा netfs_पढ़ो_request *rreq,
		     loff_t start, माप_प्रकार len,
		     क्रमागत netfs_पढ़ो_trace what),

	    TP_ARGS(rreq, start, len, what),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		rreq		)
		    __field(अचिन्हित पूर्णांक,		cookie		)
		    __field(loff_t,			start		)
		    __field(माप_प्रकार,			len		)
		    __field(क्रमागत netfs_पढ़ो_trace,	what		)
			     ),

	    TP_fast_assign(
		    __entry->rreq	= rreq->debug_id;
		    __entry->cookie	= rreq->cookie_debug_id;
		    __entry->start	= start;
		    __entry->len	= len;
		    __entry->what	= what;
			   ),

	    TP_prपूर्णांकk("R=%08x %s c=%08x s=%llx %zx",
		      __entry->rreq,
		      __prपूर्णांक_symbolic(__entry->what, netfs_पढ़ो_traces),
		      __entry->cookie,
		      __entry->start, __entry->len)
	    );

TRACE_EVENT(netfs_rreq,
	    TP_PROTO(काष्ठा netfs_पढ़ो_request *rreq,
		     क्रमागत netfs_rreq_trace what),

	    TP_ARGS(rreq, what),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		rreq		)
		    __field(अचिन्हित लघु,		flags		)
		    __field(क्रमागत netfs_rreq_trace,	what		)
			     ),

	    TP_fast_assign(
		    __entry->rreq	= rreq->debug_id;
		    __entry->flags	= rreq->flags;
		    __entry->what	= what;
			   ),

	    TP_prपूर्णांकk("R=%08x %s f=%02x",
		      __entry->rreq,
		      __prपूर्णांक_symbolic(__entry->what, netfs_rreq_traces),
		      __entry->flags)
	    );

TRACE_EVENT(netfs_sreq,
	    TP_PROTO(काष्ठा netfs_पढ़ो_subrequest *sreq,
		     क्रमागत netfs_sreq_trace what),

	    TP_ARGS(sreq, what),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		rreq		)
		    __field(अचिन्हित लघु,		index		)
		    __field(लघु,			error		)
		    __field(अचिन्हित लघु,		flags		)
		    __field(क्रमागत netfs_पढ़ो_source,	source		)
		    __field(क्रमागत netfs_sreq_trace,	what		)
		    __field(माप_प्रकार,			len		)
		    __field(माप_प्रकार,			transferred	)
		    __field(loff_t,			start		)
			     ),

	    TP_fast_assign(
		    __entry->rreq	= sreq->rreq->debug_id;
		    __entry->index	= sreq->debug_index;
		    __entry->error	= sreq->error;
		    __entry->flags	= sreq->flags;
		    __entry->source	= sreq->source;
		    __entry->what	= what;
		    __entry->len	= sreq->len;
		    __entry->transferred = sreq->transferred;
		    __entry->start	= sreq->start;
			   ),

	    TP_prपूर्णांकk("R=%08x[%u] %s %s f=%02x s=%llx %zx/%zx e=%d",
		      __entry->rreq, __entry->index,
		      __prपूर्णांक_symbolic(__entry->what, netfs_sreq_traces),
		      __prपूर्णांक_symbolic(__entry->source, netfs_sreq_sources),
		      __entry->flags,
		      __entry->start, __entry->transferred, __entry->len,
		      __entry->error)
	    );

TRACE_EVENT(netfs_failure,
	    TP_PROTO(काष्ठा netfs_पढ़ो_request *rreq,
		     काष्ठा netfs_पढ़ो_subrequest *sreq,
		     पूर्णांक error, क्रमागत netfs_failure what),

	    TP_ARGS(rreq, sreq, error, what),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		rreq		)
		    __field(अचिन्हित लघु,		index		)
		    __field(लघु,			error		)
		    __field(अचिन्हित लघु,		flags		)
		    __field(क्रमागत netfs_पढ़ो_source,	source		)
		    __field(क्रमागत netfs_failure,		what		)
		    __field(माप_प्रकार,			len		)
		    __field(माप_प्रकार,			transferred	)
		    __field(loff_t,			start		)
			     ),

	    TP_fast_assign(
		    __entry->rreq	= rreq->debug_id;
		    __entry->index	= sreq ? sreq->debug_index : 0;
		    __entry->error	= error;
		    __entry->flags	= sreq ? sreq->flags : 0;
		    __entry->source	= sreq ? sreq->source : NETFS_INVALID_READ;
		    __entry->what	= what;
		    __entry->len	= sreq ? sreq->len : 0;
		    __entry->transferred = sreq ? sreq->transferred : 0;
		    __entry->start	= sreq ? sreq->start : 0;
			   ),

	    TP_prपूर्णांकk("R=%08x[%u] %s f=%02x s=%llx %zx/%zx %s e=%d",
		      __entry->rreq, __entry->index,
		      __prपूर्णांक_symbolic(__entry->source, netfs_sreq_sources),
		      __entry->flags,
		      __entry->start, __entry->transferred, __entry->len,
		      __prपूर्णांक_symbolic(__entry->what, netfs_failures),
		      __entry->error)
	    );

#पूर्ण_अगर /* _TRACE_NETFS_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
