<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2019 The Linux Foundation. All rights reserved.
 */

#अगर !defined(_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "core.h"

#घोषणा _TRACE_H_

/* create empty functions when tracing is disabled */
#अगर !defined(CONFIG_ATH11K_TRACING)
#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_ATH11K_TRACING || __CHECKER__ */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ath11k

TRACE_EVENT(ath11k_htt_pktlog,
	    TP_PROTO(काष्ठा ath11k *ar, स्थिर व्योम *buf, u16 buf_len,
		     u32 pktlog_checksum),

	TP_ARGS(ar, buf, buf_len, pktlog_checksum),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->ab->dev))
		__string(driver, dev_driver_string(ar->ab->dev))
		__field(u16, buf_len)
		__field(u32, pktlog_checksum)
		__dynamic_array(u8, pktlog, buf_len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->ab->dev));
		__assign_str(driver, dev_driver_string(ar->ab->dev));
		__entry->buf_len = buf_len;
		__entry->pktlog_checksum = pktlog_checksum;
		स_नकल(__get_dynamic_array(pktlog), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s %s size %u pktlog_checksum %d",
		__get_str(driver),
		__get_str(device),
		__entry->buf_len,
		__entry->pktlog_checksum
	 )
);

TRACE_EVENT(ath11k_htt_ppdu_stats,
	    TP_PROTO(काष्ठा ath11k *ar, स्थिर व्योम *data, माप_प्रकार len),

	TP_ARGS(ar, data, len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->ab->dev))
		__string(driver, dev_driver_string(ar->ab->dev))
		__field(u16, len)
		__dynamic_array(u8, ppdu, len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->ab->dev));
		__assign_str(driver, dev_driver_string(ar->ab->dev));
		__entry->len = len;
		स_नकल(__get_dynamic_array(ppdu), data, len);
	),

	TP_prपूर्णांकk(
		"%s %s ppdu len %d",
		__get_str(driver),
		__get_str(device),
		__entry->len
	 )
);

TRACE_EVENT(ath11k_htt_rxdesc,
	    TP_PROTO(काष्ठा ath11k *ar, स्थिर व्योम *data, माप_प्रकार len),

	TP_ARGS(ar, data, len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->ab->dev))
		__string(driver, dev_driver_string(ar->ab->dev))
		__field(u16, len)
		__dynamic_array(u8, rxdesc, len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->ab->dev));
		__assign_str(driver, dev_driver_string(ar->ab->dev));
		__entry->len = len;
		स_नकल(__get_dynamic_array(rxdesc), data, len);
	),

	TP_prपूर्णांकk(
		"%s %s rxdesc len %d",
		__get_str(driver),
		__get_str(device),
		__entry->len
	 )
);

#पूर्ण_अगर /* _TRACE_H_ || TRACE_HEADER_MULTI_READ*/

/* we करोn't want to use include/trace/events */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
