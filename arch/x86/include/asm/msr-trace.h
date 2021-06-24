<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM msr

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता msr-trace

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH यंत्र/

#अगर !defined(_TRACE_MSR_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_MSR_H

#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Tracing क्रम x86 model specअगरic रेजिस्टरs. Directly maps to the
 * RDMSR/WRMSR inकाष्ठाions.
 */

DECLARE_EVENT_CLASS(msr_trace_class,
	    TP_PROTO(अचिन्हित msr, u64 val, पूर्णांक failed),
	    TP_ARGS(msr, val, failed),
	    TP_STRUCT__entry(
		    __field(	अचिन्हित,	msr )
		    __field(    u64,		val )
		    __field(    पूर्णांक,		failed )
	    ),
	    TP_fast_assign(
		    __entry->msr = msr;
		    __entry->val = val;
		    __entry->failed = failed;
	    ),
	    TP_prपूर्णांकk("%x, value %llx%s",
		      __entry->msr,
		      __entry->val,
		      __entry->failed ? " #GP" : "")
);

DEFINE_EVENT(msr_trace_class, पढ़ो_msr,
	     TP_PROTO(अचिन्हित msr, u64 val, पूर्णांक failed),
	     TP_ARGS(msr, val, failed)
);

DEFINE_EVENT(msr_trace_class, ग_लिखो_msr,
	     TP_PROTO(अचिन्हित msr, u64 val, पूर्णांक failed),
	     TP_ARGS(msr, val, failed)
);

DEFINE_EVENT(msr_trace_class, rdpmc,
	     TP_PROTO(अचिन्हित msr, u64 val, पूर्णांक failed),
	     TP_ARGS(msr, val, failed)
);

#पूर्ण_अगर /* _TRACE_MSR_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
