<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Declarations क्रम error reporting tracepoपूर्णांकs.
 *
 * Copyright (C) 2021, Google LLC.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM error_report

#अगर !defined(_TRACE_ERROR_REPORT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_ERROR_REPORT_H

#समावेश <linux/tracepoपूर्णांक.h>

#अगर_अघोषित __ERROR_REPORT_DECLARE_TRACE_ENUMS_ONCE_ONLY
#घोषणा __ERROR_REPORT_DECLARE_TRACE_ENUMS_ONCE_ONLY

क्रमागत error_detector अणु
	ERROR_DETECTOR_KFENCE,
	ERROR_DETECTOR_KASAN
पूर्ण;

#पूर्ण_अगर /* __ERROR_REPORT_DECLARE_TRACE_ENUMS_ONCE_ONLY */

#घोषणा error_detector_list	\
	EM(ERROR_DETECTOR_KFENCE, "kfence")	\
	EMe(ERROR_DETECTOR_KASAN, "kasan")
/* Always end the list with an EMe. */

#अघोषित EM
#अघोषित EMe

#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

error_detector_list

#अघोषित EM
#अघोषित EMe

#घोषणा EM(a, b) अणु a, b पूर्ण,
#घोषणा EMe(a, b) अणु a, b पूर्ण

#घोषणा show_error_detector_list(val) \
	__prपूर्णांक_symbolic(val, error_detector_list)

DECLARE_EVENT_CLASS(error_report_ढाँचा,
		    TP_PROTO(क्रमागत error_detector error_detector, अचिन्हित दीर्घ id),
		    TP_ARGS(error_detector, id),
		    TP_STRUCT__entry(__field(क्रमागत error_detector, error_detector)
					     __field(अचिन्हित दीर्घ, id)),
		    TP_fast_assign(__entry->error_detector = error_detector;
				   __entry->id = id;),
		    TP_prपूर्णांकk("[%s] %lx",
			      show_error_detector_list(__entry->error_detector),
			      __entry->id));

/**
 * error_report_end - called after prपूर्णांकing the error report
 * @error_detector:	लघु string describing the error detection tool
 * @id:			pseuकरो-unique descriptor identअगरying the report
 *			(e.g. the memory access address)
 *
 * This event occurs right after a debugging tool finishes prपूर्णांकing the error
 * report.
 */
DEFINE_EVENT(error_report_ढाँचा, error_report_end,
	     TP_PROTO(क्रमागत error_detector error_detector, अचिन्हित दीर्घ id),
	     TP_ARGS(error_detector, id));

#पूर्ण_अगर /* _TRACE_ERROR_REPORT_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
