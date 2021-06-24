<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Tracepoपूर्णांक header क्रम s390 diagnose calls
 *
 * Copyright IBM Corp. 2015
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM s390

#अगर !defined(_TRACE_S390_DIAG_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_S390_DIAG_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता

#घोषणा TRACE_INCLUDE_PATH यंत्र/trace
#घोषणा TRACE_INCLUDE_खाता diag

TRACE_EVENT(s390_diagnose,
	TP_PROTO(अचिन्हित लघु nr),
	TP_ARGS(nr),
	TP_STRUCT__entry(
		__field(अचिन्हित लघु, nr)
	),
	TP_fast_assign(
		__entry->nr = nr;
	),
	TP_prपूर्णांकk("nr=0x%x", __entry->nr)
);

#अगर_घोषित CONFIG_TRACEPOINTS
व्योम trace_s390_diagnose_norecursion(पूर्णांक diag_nr);
#अन्यथा
अटल अंतरभूत व्योम trace_s390_diagnose_norecursion(पूर्णांक diag_nr) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _TRACE_S390_DIAG_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
