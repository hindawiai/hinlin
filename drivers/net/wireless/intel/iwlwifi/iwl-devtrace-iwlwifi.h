<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2009 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2015 Intel Mobile Communications GmbH
 * Copyright(c) 2016 - 2017 Intel Deutschland GmbH
 * Copyright(c) 2018        Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर !defined(__IWLWIFI_DEVICE_TRACE_IWLWIFI) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __IWLWIFI_DEVICE_TRACE_IWLWIFI

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iwlwअगरi

TRACE_EVENT(iwlwअगरi_dev_hcmd,
	TP_PROTO(स्थिर काष्ठा device *dev,
		 काष्ठा iwl_host_cmd *cmd, u16 total_size,
		 काष्ठा iwl_cmd_header_wide *hdr),
	TP_ARGS(dev, cmd, total_size, hdr),
	TP_STRUCT__entry(
		DEV_ENTRY
		__dynamic_array(u8, hcmd, total_size)
		__field(u32, flags)
	),
	TP_fast_assign(
		पूर्णांक i, offset = माप(काष्ठा iwl_cmd_header);

		अगर (hdr->group_id)
			offset = माप(काष्ठा iwl_cmd_header_wide);

		DEV_ASSIGN;
		__entry->flags = cmd->flags;
		स_नकल(__get_dynamic_array(hcmd), hdr, offset);

		क्रम (i = 0; i < IWL_MAX_CMD_TBS_PER_TFD; i++) अणु
			अगर (!cmd->len[i])
				जारी;
			स_नकल((u8 *)__get_dynamic_array(hcmd) + offset,
			       cmd->data[i], cmd->len[i]);
			offset += cmd->len[i];
		पूर्ण
	),
	TP_prपूर्णांकk("[%s] hcmd %#.2x.%#.2x (%ssync)",
		  __get_str(dev), ((u8 *)__get_dynamic_array(hcmd))[1],
		  ((u8 *)__get_dynamic_array(hcmd))[0],
		  __entry->flags & CMD_ASYNC ? "a" : "")
);

TRACE_EVENT(iwlwअगरi_dev_rx,
	TP_PROTO(स्थिर काष्ठा device *dev, स्थिर काष्ठा iwl_trans *trans,
		 काष्ठा iwl_rx_packet *pkt, माप_प्रकार len),
	TP_ARGS(dev, trans, pkt, len),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u16, cmd)
		__field(u8, hdr_offset)
		__dynamic_array(u8, rxbuf,
				iwl_rx_trace_len(trans, pkt, len, शून्य))
	),
	TP_fast_assign(
		माप_प्रकार hdr_offset = 0;

		DEV_ASSIGN;
		__entry->cmd = WIDE_ID(pkt->hdr.group_id, pkt->hdr.cmd);
		स_नकल(__get_dynamic_array(rxbuf), pkt,
		       iwl_rx_trace_len(trans, pkt, len, &hdr_offset));
		__entry->hdr_offset = hdr_offset;
	),
	TP_prपूर्णांकk("[%s] RX cmd %#.2x",
		  __get_str(dev), __entry->cmd)
);

TRACE_EVENT(iwlwअगरi_dev_tx,
	TP_PROTO(स्थिर काष्ठा device *dev, काष्ठा sk_buff *skb,
		 व्योम *tfd, माप_प्रकार tfdlen,
		 व्योम *buf0, माप_प्रकार buf0_len,
		 पूर्णांक hdr_len),
	TP_ARGS(dev, skb, tfd, tfdlen, buf0, buf0_len, hdr_len),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(व्योम *, skbaddr)
		__field(माप_प्रकार, framelen)
		__dynamic_array(u8, tfd, tfdlen)

		/*
		 * Do not insert between or below these items,
		 * we want to keep the frame together (except
		 * क्रम the possible padding).
		 */
		__dynamic_array(u8, buf0, buf0_len)
		__dynamic_array(u8, buf1, hdr_len > 0 && iwl_trace_data(skb) ?
						0 : skb->len - hdr_len)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->skbaddr = skb;
		__entry->framelen = buf0_len;
		अगर (hdr_len > 0)
			__entry->framelen += skb->len - hdr_len;
		स_नकल(__get_dynamic_array(tfd), tfd, tfdlen);
		स_नकल(__get_dynamic_array(buf0), buf0, buf0_len);
		अगर (hdr_len > 0 && !iwl_trace_data(skb))
			skb_copy_bits(skb, hdr_len,
				      __get_dynamic_array(buf1),
				      skb->len - hdr_len);
	),
	TP_prपूर्णांकk("[%s] TX %.2x (%zu bytes) skbaddr=%p",
		  __get_str(dev), ((u8 *)__get_dynamic_array(buf0))[0],
		  __entry->framelen, __entry->skbaddr)
);

TRACE_EVENT(iwlwअगरi_dev_ucode_event,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 समय, u32 data, u32 ev),
	TP_ARGS(dev, समय, data, ev),
	TP_STRUCT__entry(
		DEV_ENTRY

		__field(u32, समय)
		__field(u32, data)
		__field(u32, ev)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->समय = समय;
		__entry->data = data;
		__entry->ev = ev;
	),
	TP_prपूर्णांकk("[%s] EVT_LOGT:%010u:0x%08x:%04u",
		  __get_str(dev), __entry->समय, __entry->data, __entry->ev)
);
#पूर्ण_अगर /* __IWLWIFI_DEVICE_TRACE_IWLWIFI */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता iwl-devtrace-iwlwअगरi
#समावेश <trace/define_trace.h>
