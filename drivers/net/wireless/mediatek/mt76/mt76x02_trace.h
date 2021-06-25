<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#अगर !defined(__MT76x02_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MT76x02_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "mt76x02.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mt76x02

#घोषणा MAXNAME		32
#घोषणा DEV_ENTRY	__array(अक्षर, wiphy_name, 32)
#घोषणा DEV_ASSIGN	strlcpy(__entry->wiphy_name,	\
				wiphy_name(mt76_hw(dev)->wiphy), MAXNAME)
#घोषणा DEV_PR_FMT	"%s"
#घोषणा DEV_PR_ARG	__entry->wiphy_name

#घोषणा TXID_ENTRY	__field(u8, wcid) __field(u8, pktid)
#घोषणा TXID_PR_FMT	" [%d:%d]"
#घोषणा TXID_PR_ARG	__entry->wcid, __entry->pktid

DECLARE_EVENT_CLASS(dev_evt,
	TP_PROTO(काष्ठा mt76x02_dev *dev),
	TP_ARGS(dev),
	TP_STRUCT__entry(
		DEV_ENTRY
	),
	TP_fast_assign(
		DEV_ASSIGN;
	),
	TP_prपूर्णांकk(DEV_PR_FMT, DEV_PR_ARG)
);

DEFINE_EVENT(dev_evt, mac_txstat_poll,
	TP_PROTO(काष्ठा mt76x02_dev *dev),
	TP_ARGS(dev)
);

TRACE_EVENT(mac_txstat_fetch,
	TP_PROTO(काष्ठा mt76x02_dev *dev,
		 काष्ठा mt76x02_tx_status *stat),

	TP_ARGS(dev, stat),

	TP_STRUCT__entry(
		DEV_ENTRY
		TXID_ENTRY
		__field(bool, success)
		__field(bool, aggr)
		__field(bool, ack_req)
		__field(u16, rate)
		__field(u8, retry)
	),

	TP_fast_assign(
		DEV_ASSIGN;
		__entry->success = stat->success;
		__entry->aggr = stat->aggr;
		__entry->ack_req = stat->ack_req;
		__entry->wcid = stat->wcid;
		__entry->pktid = stat->pktid;
		__entry->rate = stat->rate;
		__entry->retry = stat->retry;
	),

	TP_prपूर्णांकk(
		DEV_PR_FMT TXID_PR_FMT
		" success:%d aggr:%d ack_req:%d"
		" rate:%04x retry:%d",
		DEV_PR_ARG, TXID_PR_ARG,
		__entry->success, __entry->aggr, __entry->ack_req,
		__entry->rate, __entry->retry
	)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता mt76x02_trace

#समावेश <trace/define_trace.h>
