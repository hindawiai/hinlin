<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर !defined(__MT7601U_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MT7601U_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "mt7601u.h"
#समावेश "mac.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mt7601u

#घोषणा MAXNAME		32
#घोषणा DEV_ENTRY	__array(अक्षर, wiphy_name, 32)
#घोषणा DEV_ASSIGN	strlcpy(__entry->wiphy_name,			\
				wiphy_name(dev->hw->wiphy), MAXNAME)
#घोषणा DEV_PR_FMT	"%s "
#घोषणा DEV_PR_ARG	__entry->wiphy_name

#घोषणा REG_ENTRY	__field(u32, reg) __field(u32, val)
#घोषणा REG_ASSIGN	__entry->reg = reg; __entry->val = val
#घोषणा REG_PR_FMT	"%04x=%08x"
#घोषणा REG_PR_ARG	__entry->reg, __entry->val

DECLARE_EVENT_CLASS(dev_reg_evtu,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u32 reg, u32 val),
	TP_ARGS(dev, reg, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		REG_ENTRY
	),
	TP_fast_assign(
		DEV_ASSIGN;
		REG_ASSIGN;
	),
	TP_prपूर्णांकk(
		DEV_PR_FMT REG_PR_FMT,
		DEV_PR_ARG, REG_PR_ARG
	)
);

DEFINE_EVENT(dev_reg_evtu, reg_पढ़ो,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u32 reg, u32 val),
	TP_ARGS(dev, reg, val)
);

DEFINE_EVENT(dev_reg_evtu, reg_ग_लिखो,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u32 reg, u32 val),
	TP_ARGS(dev, reg, val)
);

TRACE_EVENT(mt_submit_urb,
	TP_PROTO(काष्ठा mt7601u_dev *dev, काष्ठा urb *u),
	TP_ARGS(dev, u),
	TP_STRUCT__entry(
		DEV_ENTRY __field(अचिन्हित, pipe) __field(u32, len)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->pipe = u->pipe;
		__entry->len = u->transfer_buffer_length;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "p:%08x len:%u",
		  DEV_PR_ARG, __entry->pipe, __entry->len)
);

#घोषणा trace_mt_submit_urb_sync(__dev, __pipe, __len) (अणु	\
	काष्ठा urb u;					\
	u.pipe = __pipe;				\
	u.transfer_buffer_length = __len;		\
	trace_mt_submit_urb(__dev, &u);			\
पूर्ण)

TRACE_EVENT(mt_mcu_msg_send,
	TP_PROTO(काष्ठा mt7601u_dev *dev,
		 काष्ठा sk_buff *skb, u32 csum, bool resp),
	TP_ARGS(dev, skb, csum, resp),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, info)
		__field(u32, csum)
		__field(bool, resp)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->info = *(u32 *)skb->data;
		__entry->csum = csum;
		__entry->resp = resp;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "i:%08x c:%08x r:%d",
		  DEV_PR_ARG, __entry->info, __entry->csum, __entry->resp)
);

TRACE_EVENT(mt_vend_req,
	TP_PROTO(काष्ठा mt7601u_dev *dev, अचिन्हित pipe, u8 req, u8 req_type,
		 u16 val, u16 offset, व्योम *buf, माप_प्रकार buflen, पूर्णांक ret),
	TP_ARGS(dev, pipe, req, req_type, val, offset, buf, buflen, ret),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(अचिन्हित, pipe) __field(u8, req) __field(u8, req_type)
		__field(u16, val) __field(u16, offset) __field(व्योम*, buf)
		__field(पूर्णांक, buflen) __field(पूर्णांक, ret)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->pipe = pipe;
		__entry->req = req;
		__entry->req_type = req_type;
		__entry->val = val;
		__entry->offset = offset;
		__entry->buf = buf;
		__entry->buflen = buflen;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk(DEV_PR_FMT
		  "%d p:%08x req:%02hhx %02hhx val:%04hx %04hx buf:%d %d",
		  DEV_PR_ARG, __entry->ret, __entry->pipe, __entry->req,
		  __entry->req_type, __entry->val, __entry->offset,
		  !!__entry->buf, __entry->buflen)
);

TRACE_EVENT(ee_पढ़ो,
	TP_PROTO(काष्ठा mt7601u_dev *dev, पूर्णांक offset, u16 val),
	TP_ARGS(dev, offset, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(पूर्णांक, o) __field(u16, v)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->o = offset;
		__entry->v = val;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "%04x=%04x", DEV_PR_ARG, __entry->o, __entry->v)
);

DECLARE_EVENT_CLASS(dev_rf_reg_evt,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 bank, u8 reg, u8 val),
	TP_ARGS(dev, bank, reg, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u8, bank)
		__field(u8, reg)
		__field(u8, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		REG_ASSIGN;
		__entry->bank = bank;
	),
	TP_prपूर्णांकk(
		DEV_PR_FMT "%02hhx:%02hhx=%02hhx",
		DEV_PR_ARG, __entry->bank, __entry->reg, __entry->val
	)
);

DEFINE_EVENT(dev_rf_reg_evt, rf_पढ़ो,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 bank, u8 reg, u8 val),
	TP_ARGS(dev, bank, reg, val)
);

DEFINE_EVENT(dev_rf_reg_evt, rf_ग_लिखो,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 bank, u8 reg, u8 val),
	TP_ARGS(dev, bank, reg, val)
);

DECLARE_EVENT_CLASS(dev_bbp_reg_evt,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 reg, u8 val),
	TP_ARGS(dev, reg, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u8, reg)
		__field(u8, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		REG_ASSIGN;
	),
	TP_prपूर्णांकk(
		DEV_PR_FMT "%02hhx=%02hhx",
		DEV_PR_ARG, __entry->reg, __entry->val
	)
);

DEFINE_EVENT(dev_bbp_reg_evt, bbp_पढ़ो,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 reg, u8 val),
	TP_ARGS(dev, reg, val)
);

DEFINE_EVENT(dev_bbp_reg_evt, bbp_ग_लिखो,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 reg, u8 val),
	TP_ARGS(dev, reg, val)
);

DECLARE_EVENT_CLASS(dev_simple_evt,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 val),
	TP_ARGS(dev, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u8, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->val = val;
	),
	TP_prपूर्णांकk(
		DEV_PR_FMT "%02hhx", DEV_PR_ARG, __entry->val
	)
);

DEFINE_EVENT(dev_simple_evt, temp_mode,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 val),
	TP_ARGS(dev, val)
);

DEFINE_EVENT(dev_simple_evt, पढ़ो_temp,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 val),
	TP_ARGS(dev, val)
);

DEFINE_EVENT(dev_simple_evt, freq_cal_adjust,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 val),
	TP_ARGS(dev, val)
);

TRACE_EVENT(freq_cal_offset,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 phy_mode, s8 freq_off),
	TP_ARGS(dev, phy_mode, freq_off),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u8, phy_mode)
		__field(s8, freq_off)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->phy_mode = phy_mode;
		__entry->freq_off = freq_off;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "phy:%02hhx off:%02hhx",
		  DEV_PR_ARG, __entry->phy_mode, __entry->freq_off)
);

TRACE_EVENT(mt_rx,
	TP_PROTO(काष्ठा mt7601u_dev *dev, काष्ठा mt7601u_rxwi *rxwi, u32 f),
	TP_ARGS(dev, rxwi, f),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field_काष्ठा(काष्ठा mt7601u_rxwi, rxwi)
		__field(u32, fce_info)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->rxwi = *rxwi;
		__entry->fce_info = f;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "rxi:%08x ctl:%08x frag_sn:%04hx rate:%04hx "
		  "uknw:%02hhx z:%02hhx%02hhx%02hhx snr:%02hhx "
		  "ant:%02hhx gain:%02hhx freq_o:%02hhx "
		  "r:%08x ea:%08x fce:%08x", DEV_PR_ARG,
		  le32_to_cpu(__entry->rxwi.rxinfo),
		  le32_to_cpu(__entry->rxwi.ctl),
		  le16_to_cpu(__entry->rxwi.frag_sn),
		  le16_to_cpu(__entry->rxwi.rate),
		  __entry->rxwi.unknown,
		  __entry->rxwi.zero[0], __entry->rxwi.zero[1],
		  __entry->rxwi.zero[2],
		  __entry->rxwi.snr, __entry->rxwi.ant,
		  __entry->rxwi.gain, __entry->rxwi.freq_off,
		  __entry->rxwi.resv2, __entry->rxwi.expert_ant,
		  __entry->fce_info)
);

TRACE_EVENT(mt_tx,
	TP_PROTO(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb,
		 काष्ठा mt76_sta *sta, काष्ठा mt76_txwi *h),
	TP_ARGS(dev, skb, sta, h),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field_काष्ठा(काष्ठा mt76_txwi, h)
		__field(काष्ठा sk_buff *, skb)
		__field(काष्ठा mt76_sta *, sta)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->h = *h;
		__entry->skb = skb;
		__entry->sta = sta;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "skb:%p sta:%p  flg:%04hx rate_ctl:%04hx "
		  "ack:%02hhx wcid:%02hhx len_ctl:%05hx", DEV_PR_ARG,
		  __entry->skb, __entry->sta,
		  le16_to_cpu(__entry->h.flags),
		  le16_to_cpu(__entry->h.rate_ctl),
		  __entry->h.ack_ctl, __entry->h.wcid,
		  le16_to_cpu(__entry->h.len_ctl))
);

TRACE_EVENT(mt_tx_dma_करोne,
	TP_PROTO(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb),
	TP_ARGS(dev, skb),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(काष्ठा sk_buff *, skb)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->skb = skb;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "%p", DEV_PR_ARG, __entry->skb)
);

TRACE_EVENT(mt_tx_status_cleaned,
	TP_PROTO(काष्ठा mt7601u_dev *dev, पूर्णांक cleaned),
	TP_ARGS(dev, cleaned),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(पूर्णांक, cleaned)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->cleaned = cleaned;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "%d", DEV_PR_ARG, __entry->cleaned)
);

TRACE_EVENT(mt_tx_status,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u32 stat1, u32 stat2),
	TP_ARGS(dev, stat1, stat2),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, stat1)	__field(u32, stat2)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->stat1 = stat1;
		__entry->stat2 = stat2;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "%08x %08x",
		  DEV_PR_ARG, __entry->stat1, __entry->stat2)
);

TRACE_EVENT(mt_rx_dma_aggr,
	TP_PROTO(काष्ठा mt7601u_dev *dev, पूर्णांक cnt, bool paged),
	TP_ARGS(dev, cnt, paged),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u8, cnt)
		__field(bool, paged)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->cnt = cnt;
		__entry->paged = paged;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "cnt:%d paged:%d",
		  DEV_PR_ARG, __entry->cnt, __entry->paged)
);

DEFINE_EVENT(dev_simple_evt, set_key,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 val),
	TP_ARGS(dev, val)
);

TRACE_EVENT(set_shared_key,
	TP_PROTO(काष्ठा mt7601u_dev *dev, u8 vid, u8 key),
	TP_ARGS(dev, vid, key),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u8, vid)
		__field(u8, key)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->vid = vid;
		__entry->key = key;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "phy:%02hhx off:%02hhx",
		  DEV_PR_ARG, __entry->vid, __entry->key)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
