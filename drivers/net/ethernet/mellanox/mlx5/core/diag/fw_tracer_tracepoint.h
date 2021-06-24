<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर !defined(__LIB_TRACER_TRACEPOINT_H__) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __LIB_TRACER_TRACEPOINT_H__

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "fw_tracer.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mlx5

/* Tracepoपूर्णांक क्रम FWTracer messages: */
TRACE_EVENT(mlx5_fw,
	TP_PROTO(स्थिर काष्ठा mlx5_fw_tracer *tracer, u64 trace_बारtamp,
		 bool lost, u8 event_id, स्थिर अक्षर *msg),

	TP_ARGS(tracer, trace_बारtamp, lost, event_id, msg),

	TP_STRUCT__entry(
		__string(dev_name, dev_name(tracer->dev->device))
		__field(u64, trace_बारtamp)
		__field(bool, lost)
		__field(u8, event_id)
		__string(msg, msg)
	),

	TP_fast_assign(
		__assign_str(dev_name,
			     dev_name(tracer->dev->device));
		__entry->trace_बारtamp = trace_बारtamp;
		__entry->lost = lost;
		__entry->event_id = event_id;
		__assign_str(msg, msg);
	),

	TP_prपूर्णांकk("%s [0x%llx] %d [0x%x] %s",
		  __get_str(dev_name),
		  __entry->trace_बारtamp,
		  __entry->lost, __entry->event_id,
		  __get_str(msg))
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH ./diag
#घोषणा TRACE_INCLUDE_खाता fw_tracer_tracepoपूर्णांक
#समावेश <trace/define_trace.h>
