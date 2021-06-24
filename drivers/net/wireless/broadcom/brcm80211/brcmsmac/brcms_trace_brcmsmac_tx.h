<शैली गुरु>
/*
 * Copyright (c) 2011 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर !defined(__TRACE_BRCMSMAC_TX_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __TRACE_BRCMSMAC_TX_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM brcmsmac_tx

TRACE_EVENT(brcms_txdesc,
	TP_PROTO(स्थिर काष्ठा device *dev,
		 व्योम *txh, माप_प्रकार txh_len),
	TP_ARGS(dev, txh, txh_len),
	TP_STRUCT__entry(
		__string(dev, dev_name(dev))
		__dynamic_array(u8, txh, txh_len)
	),
	TP_fast_assign(
		__assign_str(dev, dev_name(dev));
		स_नकल(__get_dynamic_array(txh), txh, txh_len);
	),
	TP_prपूर्णांकk("[%s] txdesc", __get_str(dev))
);

TRACE_EVENT(brcms_txstatus,
	TP_PROTO(स्थिर काष्ठा device *dev, u16 framelen, u16 frameid,
		 u16 status, u16 lasttxसमय, u16 sequence, u16 phyerr,
		 u16 ackphyrxsh),
	TP_ARGS(dev, framelen, frameid, status, lasttxसमय, sequence, phyerr,
		ackphyrxsh),
	TP_STRUCT__entry(
		__string(dev, dev_name(dev))
		__field(u16, framelen)
		__field(u16, frameid)
		__field(u16, status)
		__field(u16, lasttxसमय)
		__field(u16, sequence)
		__field(u16, phyerr)
		__field(u16, ackphyrxsh)
	),
	TP_fast_assign(
		__assign_str(dev, dev_name(dev));
		__entry->framelen = framelen;
		__entry->frameid = frameid;
		__entry->status = status;
		__entry->lasttxसमय = lasttxसमय;
		__entry->sequence = sequence;
		__entry->phyerr = phyerr;
		__entry->ackphyrxsh = ackphyrxsh;
	),
	TP_prपूर्णांकk("[%s] FrameId %#04x TxStatus %#04x LastTxTime %#04x "
		  "Seq %#04x PHYTxStatus %#04x RxAck %#04x",
		  __get_str(dev), __entry->frameid, __entry->status,
		  __entry->lasttxसमय, __entry->sequence, __entry->phyerr,
		  __entry->ackphyrxsh)
);

TRACE_EVENT(brcms_ampdu_session,
	TP_PROTO(स्थिर काष्ठा device *dev, अचिन्हित max_ampdu_len,
		 u16 max_ampdu_frames, u16 ampdu_len, u16 ampdu_frames,
		 u16 dma_len),
	TP_ARGS(dev, max_ampdu_len, max_ampdu_frames, ampdu_len, ampdu_frames,
		dma_len),
	TP_STRUCT__entry(
		__string(dev, dev_name(dev))
		__field(अचिन्हित, max_ampdu_len)
		__field(u16, max_ampdu_frames)
		__field(u16, ampdu_len)
		__field(u16, ampdu_frames)
		__field(u16, dma_len)
	),
	TP_fast_assign(
		__assign_str(dev, dev_name(dev));
		__entry->max_ampdu_len = max_ampdu_len;
		__entry->max_ampdu_frames = max_ampdu_frames;
		__entry->ampdu_len = ampdu_len;
		__entry->ampdu_frames = ampdu_frames;
		__entry->dma_len = dma_len;
	),
	TP_prपूर्णांकk("[%s] ampdu session max_len=%u max_frames=%u len=%u frames=%u dma_len=%u",
		  __get_str(dev), __entry->max_ampdu_len,
		  __entry->max_ampdu_frames, __entry->ampdu_len,
		  __entry->ampdu_frames, __entry->dma_len)
);
#पूर्ण_अगर /* __TRACE_BRCMSMAC_TX_H */

#अगर_घोषित CONFIG_BRCM_TRACING

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता brcms_trace_brcmsmac_tx
#समावेश <trace/define_trace.h>

#पूर्ण_अगर /* CONFIG_BRCM_TRACING */
