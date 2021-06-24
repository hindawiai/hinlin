<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2009 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2015        Intel Deutschland GmbH
 * Copyright(c) 2018 - 2019 Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर !defined(__IWLWIFI_DEVICE_TRACE_DATA) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __IWLWIFI_DEVICE_TRACE_DATA

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iwlwअगरi_data

TRACE_EVENT(iwlwअगरi_dev_tx_tb,
	TP_PROTO(स्थिर काष्ठा device *dev, काष्ठा sk_buff *skb,
		 u8 *data_src, dma_addr_t phys, माप_प्रकार data_len),
	TP_ARGS(dev, skb, data_src, phys, data_len),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u64, phys)

		__dynamic_array(u8, data,
				iwl_trace_data(skb) ? data_len : 0)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->phys = phys;
		अगर (iwl_trace_data(skb))
			स_नकल(__get_dynamic_array(data), data_src, data_len);
	),
	TP_prपूर्णांकk("[%s] TX frame data", __get_str(dev))
);

TRACE_EVENT(iwlwअगरi_dev_rx_data,
	TP_PROTO(स्थिर काष्ठा device *dev,
		 स्थिर काष्ठा iwl_trans *trans,
		 व्योम *rxbuf, माप_प्रकार len),
	TP_ARGS(dev, trans, rxbuf, len),
	TP_STRUCT__entry(
		DEV_ENTRY
		__dynamic_array(u8, data,
				len - iwl_rx_trace_len(trans, rxbuf, len, शून्य))
	),
	TP_fast_assign(
		माप_प्रकार offs = iwl_rx_trace_len(trans, rxbuf, len, शून्य);
		DEV_ASSIGN;
		अगर (offs < len)
			स_नकल(__get_dynamic_array(data),
			       ((u8 *)rxbuf) + offs, len - offs);
	),
	TP_prपूर्णांकk("[%s] RX frame data", __get_str(dev))
);
#पूर्ण_अगर /* __IWLWIFI_DEVICE_TRACE_DATA */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता iwl-devtrace-data
#समावेश <trace/define_trace.h>
