<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ipi

#अगर !defined(_TRACE_IPI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_IPI_H

#समावेश <linux/tracepoपूर्णांक.h>

/**
 * ipi_उठाओ - called when a smp cross call is made
 *
 * @mask: mask of recipient CPUs क्रम the IPI
 * @reason: string identअगरying the IPI purpose
 *
 * It is necessary क्रम @reason to be a अटल string declared with
 * __tracepoपूर्णांक_string.
 */
TRACE_EVENT(ipi_उठाओ,

	TP_PROTO(स्थिर काष्ठा cpumask *mask, स्थिर अक्षर *reason),

	TP_ARGS(mask, reason),

	TP_STRUCT__entry(
		__biपंचांगask(target_cpus, nr_cpumask_bits)
		__field(स्थिर अक्षर *, reason)
	),

	TP_fast_assign(
		__assign_biपंचांगask(target_cpus, cpumask_bits(mask), nr_cpumask_bits);
		__entry->reason = reason;
	),

	TP_prपूर्णांकk("target_mask=%s (%s)", __get_biपंचांगask(target_cpus), __entry->reason)
);

DECLARE_EVENT_CLASS(ipi_handler,

	TP_PROTO(स्थिर अक्षर *reason),

	TP_ARGS(reason),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, reason)
	),

	TP_fast_assign(
		__entry->reason = reason;
	),

	TP_prपूर्णांकk("(%s)", __entry->reason)
);

/**
 * ipi_entry - called immediately beक्रमe the IPI handler
 *
 * @reason: string identअगरying the IPI purpose
 *
 * It is necessary क्रम @reason to be a अटल string declared with
 * __tracepoपूर्णांक_string, ideally the same as used with trace_ipi_उठाओ
 * क्रम that IPI.
 */
DEFINE_EVENT(ipi_handler, ipi_entry,

	TP_PROTO(स्थिर अक्षर *reason),

	TP_ARGS(reason)
);

/**
 * ipi_निकास - called immediately after the IPI handler वापसs
 *
 * @reason: string identअगरying the IPI purpose
 *
 * It is necessary क्रम @reason to be a अटल string declared with
 * __tracepoपूर्णांक_string, ideally the same as used with trace_ipi_उठाओ क्रम
 * that IPI.
 */
DEFINE_EVENT(ipi_handler, ipi_निकास,

	TP_PROTO(स्थिर अक्षर *reason),

	TP_ARGS(reason)
);

#पूर्ण_अगर /* _TRACE_IPI_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
