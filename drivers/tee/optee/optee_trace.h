<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * optee trace poपूर्णांकs
 *
 * Copyright (C) 2021 Synaptics Incorporated
 * Author: Jisheng Zhang <jszhang@kernel.org>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM optee

#अगर !defined(_TRACE_OPTEE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_OPTEE_H

#समावेश <linux/arm-smccc.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "optee_private.h"

TRACE_EVENT(optee_invoke_fn_begin,
	TP_PROTO(काष्ठा optee_rpc_param *param),
	TP_ARGS(param),

	TP_STRUCT__entry(
		__field(व्योम *, param)
		__array(u32, args, 8)
	),

	TP_fast_assign(
		__entry->param = param;
		BUILD_BUG_ON(माप(*param) < माप(__entry->args));
		स_नकल(__entry->args, param, माप(__entry->args));
	),

	TP_prपूर्णांकk("param=%p (%x, %x, %x, %x, %x, %x, %x, %x)", __entry->param,
		  __entry->args[0], __entry->args[1], __entry->args[2],
		  __entry->args[3], __entry->args[4], __entry->args[5],
		  __entry->args[6], __entry->args[7])
);

TRACE_EVENT(optee_invoke_fn_end,
	TP_PROTO(काष्ठा optee_rpc_param *param, काष्ठा arm_smccc_res *res),
	TP_ARGS(param, res),

	TP_STRUCT__entry(
		__field(व्योम *, param)
		__array(अचिन्हित दीर्घ, rets, 4)
	),

	TP_fast_assign(
		__entry->param = param;
		BUILD_BUG_ON(माप(*res) < माप(__entry->rets));
		स_नकल(__entry->rets, res, माप(__entry->rets));
	),

	TP_prपूर्णांकk("param=%p ret (%lx, %lx, %lx, %lx)", __entry->param,
		  __entry->rets[0], __entry->rets[1], __entry->rets[2],
		  __entry->rets[3])
);
#पूर्ण_अगर /* _TRACE_OPTEE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता optee_trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
