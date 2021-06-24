<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tracepoपूर्णांकs definitions.
 *
 * Copyright (c) 2018-2020, Silicon Laboratories, Inc.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM wfx

#अगर !defined(_WFX_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _WFX_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <net/mac80211.h>

#समावेश "bus.h"
#समावेश "hif_api_cmd.h"
#समावेश "hif_api_mib.h"

/* The hell below need some explanations. For each symbolic number, we need to
 * define it with TRACE_DEFINE_ENUM() and in a list क्रम __prपूर्णांक_symbolic.
 *
 *   1. Define a new macro that call TRACE_DEFINE_ENUM():
 *
 *          #घोषणा xxx_name(sym) TRACE_DEFINE_ENUM(sym);
 *
 *   2. Define list of all symbols:
 *
 *          #घोषणा list_names     \
 *             ...                 \
 *             xxx_name(XXX)       \
 *             ...
 *
 *   3. Instantiate that list_names:
 *
 *          list_names
 *
 *   4. Redefine xxx_name() as an entry of array क्रम __prपूर्णांक_symbolic()
 *
 *          #अघोषित xxx_name
 *          #घोषणा xxx_name(msg) अणु msg, #msg पूर्ण,
 *
 *   5. list_name can now nearly be used with __prपूर्णांक_symbolic() but,
 *      __prपूर्णांक_symbolic() dislike last comma of list. So we define a new list
 *      with a dummy element:
 *
 *          #घोषणा list_क्रम_prपूर्णांक_symbolic list_names अणु -1, शून्य पूर्ण
 */

#घोषणा _hअगर_msg_list                       \
	hअगर_cnf_name(ADD_KEY)               \
	hअगर_cnf_name(BEACON_TRANSMIT)       \
	hअगर_cnf_name(EDCA_QUEUE_PARAMS)     \
	hअगर_cnf_name(JOIN)                  \
	hअगर_cnf_name(MAP_LINK)              \
	hअगर_cnf_name(READ_MIB)              \
	hअगर_cnf_name(REMOVE_KEY)            \
	hअगर_cnf_name(RESET)                 \
	hअगर_cnf_name(SET_BSS_PARAMS)        \
	hअगर_cnf_name(SET_PM_MODE)           \
	hअगर_cnf_name(START)                 \
	hअगर_cnf_name(START_SCAN)            \
	hअगर_cnf_name(STOP_SCAN)             \
	hअगर_cnf_name(TX)                    \
	hअगर_cnf_name(MULTI_TRANSMIT)        \
	hअगर_cnf_name(UPDATE_IE)             \
	hअगर_cnf_name(WRITE_MIB)             \
	hअगर_cnf_name(CONFIGURATION)         \
	hअगर_cnf_name(CONTROL_GPIO)          \
	hअगर_cnf_name(PREVENT_ROLLBACK)      \
	hअगर_cnf_name(SET_SL_MAC_KEY)        \
	hअगर_cnf_name(SL_CONFIGURE)          \
	hअगर_cnf_name(SL_EXCHANGE_PUB_KEYS)  \
	hअगर_cnf_name(SHUT_DOWN)             \
	hअगर_ind_name(EVENT)                 \
	hअगर_ind_name(JOIN_COMPLETE)         \
	hअगर_ind_name(RX)                    \
	hअगर_ind_name(SCAN_CMPL)             \
	hअगर_ind_name(SET_PM_MODE_CMPL)      \
	hअगर_ind_name(SUSPEND_RESUME_TX)     \
	hअगर_ind_name(SL_EXCHANGE_PUB_KEYS)  \
	hअगर_ind_name(ERROR)                 \
	hअगर_ind_name(EXCEPTION)             \
	hअगर_ind_name(GENERIC)               \
	hअगर_ind_name(WAKEUP)                \
	hअगर_ind_name(STARTUP)

#घोषणा hअगर_msg_list_क्रमागत _hअगर_msg_list

#अघोषित hअगर_cnf_name
#अघोषित hअगर_ind_name
#घोषणा hअगर_cnf_name(msg) TRACE_DEFINE_ENUM(HIF_CNF_ID_##msg);
#घोषणा hअगर_ind_name(msg) TRACE_DEFINE_ENUM(HIF_IND_ID_##msg);
hअगर_msg_list_क्रमागत
#अघोषित hअगर_cnf_name
#अघोषित hअगर_ind_name
#घोषणा hअगर_cnf_name(msg) अणु HIF_CNF_ID_##msg, #msg पूर्ण,
#घोषणा hअगर_ind_name(msg) अणु HIF_IND_ID_##msg, #msg पूर्ण,
#घोषणा hअगर_msg_list hअगर_msg_list_क्रमागत अणु -1, शून्य पूर्ण

#घोषणा _hअगर_mib_list                                \
	hअगर_mib_name(ARP_IP_ADDRESSES_TABLE)         \
	hअगर_mib_name(ARP_KEEP_ALIVE_PERIOD)          \
	hअगर_mib_name(BEACON_FILTER_ENABLE)           \
	hअगर_mib_name(BEACON_FILTER_TABLE)            \
	hअगर_mib_name(BEACON_STATS)                   \
	hअगर_mib_name(BEACON_WAKEUP_PERIOD)           \
	hअगर_mib_name(BLOCK_ACK_POLICY)               \
	hअगर_mib_name(CCA_CONFIG)                     \
	hअगर_mib_name(CONFIG_DATA_FILTER)             \
	hअगर_mib_name(COUNTERS_TABLE)                 \
	hअगर_mib_name(CURRENT_TX_POWER_LEVEL)         \
	hअगर_mib_name(DOT11_MAC_ADDRESS)              \
	hअगर_mib_name(DOT11_MAX_RECEIVE_LIFETIME)     \
	hअगर_mib_name(DOT11_MAX_TRANSMIT_MSDU_LIFETIME) \
	hअगर_mib_name(DOT11_RTS_THRESHOLD)            \
	hअगर_mib_name(DOT11_WEP_DEFAULT_KEY_ID)       \
	hअगर_mib_name(ETHERTYPE_DATAFRAME_CONDITION)  \
	hअगर_mib_name(EXTENDED_COUNTERS_TABLE)        \
	hअगर_mib_name(GL_BLOCK_ACK_INFO)              \
	hअगर_mib_name(GL_OPERATIONAL_POWER_MODE)      \
	hअगर_mib_name(GL_SET_MULTI_MSG)               \
	hअगर_mib_name(GRP_SEQ_COUNTER)                \
	hअगर_mib_name(INACTIVITY_TIMER)               \
	hअगर_mib_name(INTERFACE_PROTECTION)           \
	hअगर_mib_name(IPV4_ADDR_DATAFRAME_CONDITION)  \
	hअगर_mib_name(IPV6_ADDR_DATAFRAME_CONDITION)  \
	hअगर_mib_name(KEEP_ALIVE_PERIOD)              \
	hअगर_mib_name(MAC_ADDR_DATAFRAME_CONDITION)   \
	hअगर_mib_name(MAGIC_DATAFRAME_CONDITION)      \
	hअगर_mib_name(MAX_TX_POWER_LEVEL)             \
	hअगर_mib_name(NON_ERP_PROTECTION)             \
	hअगर_mib_name(NS_IP_ADDRESSES_TABLE)          \
	hअगर_mib_name(OVERRIDE_INTERNAL_TX_RATE)      \
	hअगर_mib_name(PORT_DATAFRAME_CONDITION)       \
	hअगर_mib_name(PROTECTED_MGMT_POLICY)          \
	hअगर_mib_name(RCPI_RSSI_THRESHOLD)            \
	hअगर_mib_name(RX_FILTER)                      \
	hअगर_mib_name(SET_ASSOCIATION_MODE)           \
	hअगर_mib_name(SET_DATA_FILTERING)             \
	hअगर_mib_name(SET_HT_PROTECTION)              \
	hअगर_mib_name(SET_TX_RATE_RETRY_POLICY)       \
	hअगर_mib_name(SET_UAPSD_INFORMATION)          \
	hअगर_mib_name(SLOT_TIME)                      \
	hअगर_mib_name(STATISTICS_TABLE)               \
	hअगर_mib_name(TEMPLATE_FRAME)                 \
	hअगर_mib_name(TSF_COUNTER)                    \
	hअगर_mib_name(UC_MC_BC_DATAFRAME_CONDITION)

#घोषणा hअगर_mib_list_क्रमागत _hअगर_mib_list

#अघोषित hअगर_mib_name
#घोषणा hअगर_mib_name(mib) TRACE_DEFINE_ENUM(HIF_MIB_ID_##mib);
hअगर_mib_list_क्रमागत
#अघोषित hअगर_mib_name
#घोषणा hअगर_mib_name(mib) अणु HIF_MIB_ID_##mib, #mib पूर्ण,
#घोषणा hअगर_mib_list hअगर_mib_list_क्रमागत अणु -1, शून्य पूर्ण

DECLARE_EVENT_CLASS(hअगर_data,
	TP_PROTO(स्थिर काष्ठा hअगर_msg *hअगर, पूर्णांक tx_fill_level, bool is_recv),
	TP_ARGS(hअगर, tx_fill_level, is_recv),
	TP_STRUCT__entry(
		__field(पूर्णांक, tx_fill_level)
		__field(पूर्णांक, msg_id)
		__field(स्थिर अक्षर *, msg_type)
		__field(पूर्णांक, msg_len)
		__field(पूर्णांक, buf_len)
		__field(पूर्णांक, अगर_id)
		__field(पूर्णांक, mib)
		__array(u8, buf, 128)
	),
	TP_fast_assign(
		पूर्णांक header_len;

		__entry->tx_fill_level = tx_fill_level;
		__entry->msg_len = le16_to_cpu(hअगर->len);
		__entry->msg_id = hअगर->id;
		__entry->अगर_id = hअगर->पूर्णांकerface;
		अगर (is_recv)
			__entry->msg_type = __entry->msg_id & 0x80 ? "IND" : "CNF";
		अन्यथा
			__entry->msg_type = "REQ";
		अगर (!is_recv &&
		    (__entry->msg_id == HIF_REQ_ID_READ_MIB ||
		     __entry->msg_id == HIF_REQ_ID_WRITE_MIB)) अणु
			__entry->mib = le16_to_cpup((__le16 *)hअगर->body);
			header_len = 4;
		पूर्ण अन्यथा अणु
			__entry->mib = -1;
			header_len = 0;
		पूर्ण
		__entry->buf_len = min_t(पूर्णांक, __entry->msg_len,
					 माप(__entry->buf))
				   - माप(काष्ठा hअगर_msg) - header_len;
		स_नकल(__entry->buf, hअगर->body + header_len, __entry->buf_len);
	),
	TP_prपूर्णांकk("%d:%d:%s_%s%s%s: %s%s (%d bytes)",
		__entry->tx_fill_level,
		__entry->अगर_id,
		__entry->msg_type,
		__prपूर्णांक_symbolic(__entry->msg_id, hअगर_msg_list),
		__entry->mib != -1 ? "/" : "",
		__entry->mib != -1 ? __prपूर्णांक_symbolic(__entry->mib, hअगर_mib_list) : "",
		__prपूर्णांक_hex(__entry->buf, __entry->buf_len),
		__entry->msg_len > माप(__entry->buf) ? " ..." : "",
		__entry->msg_len
	)
);
DEFINE_EVENT(hअगर_data, hअगर_send,
	TP_PROTO(स्थिर काष्ठा hअगर_msg *hअगर, पूर्णांक tx_fill_level, bool is_recv),
	TP_ARGS(hअगर, tx_fill_level, is_recv));
#घोषणा _trace_hअगर_send(hअगर, tx_fill_level)\
	trace_hअगर_send(hअगर, tx_fill_level, false)
DEFINE_EVENT(hअगर_data, hअगर_recv,
	TP_PROTO(स्थिर काष्ठा hअगर_msg *hअगर, पूर्णांक tx_fill_level, bool is_recv),
	TP_ARGS(hअगर, tx_fill_level, is_recv));
#घोषणा _trace_hअगर_recv(hअगर, tx_fill_level)\
	trace_hअगर_recv(hअगर, tx_fill_level, true)

#घोषणा wfx_reg_list_क्रमागत                                 \
	wfx_reg_name(WFX_REG_CONFIG,       "CONFIG")      \
	wfx_reg_name(WFX_REG_CONTROL,      "CONTROL")     \
	wfx_reg_name(WFX_REG_IN_OUT_QUEUE, "QUEUE")       \
	wfx_reg_name(WFX_REG_AHB_DPORT,    "AHB")         \
	wfx_reg_name(WFX_REG_BASE_ADDR,    "BASE_ADDR")   \
	wfx_reg_name(WFX_REG_SRAM_DPORT,   "SRAM")        \
	wfx_reg_name(WFX_REG_SET_GEN_R_W,  "SET_GEN_R_W") \
	wfx_reg_name(WFX_REG_FRAME_OUT,    "FRAME_OUT")

#अघोषित wfx_reg_name
#घोषणा wfx_reg_name(sym, name) TRACE_DEFINE_ENUM(sym);
wfx_reg_list_क्रमागत
#अघोषित wfx_reg_name
#घोषणा wfx_reg_name(sym, name) अणु sym, name पूर्ण,
#घोषणा wfx_reg_list wfx_reg_list_क्रमागत अणु -1, शून्य पूर्ण

DECLARE_EVENT_CLASS(io_data,
	TP_PROTO(पूर्णांक reg, पूर्णांक addr, स्थिर व्योम *io_buf, माप_प्रकार len),
	TP_ARGS(reg, addr, io_buf, len),
	TP_STRUCT__entry(
		__field(पूर्णांक, reg)
		__field(पूर्णांक, addr)
		__field(पूर्णांक, msg_len)
		__field(पूर्णांक, buf_len)
		__array(u8, buf, 32)
		__array(u8, addr_str, 10)
	),
	TP_fast_assign(
		__entry->reg = reg;
		__entry->addr = addr;
		__entry->msg_len = len;
		__entry->buf_len = min_t(पूर्णांक, माप(__entry->buf),
					 __entry->msg_len);
		स_नकल(__entry->buf, io_buf, __entry->buf_len);
		अगर (addr >= 0)
			snम_लिखो(__entry->addr_str, 10, "/%08x", addr);
		अन्यथा
			__entry->addr_str[0] = 0;
	),
	TP_prपूर्णांकk("%s%s: %s%s (%d bytes)",
		__prपूर्णांक_symbolic(__entry->reg, wfx_reg_list),
		__entry->addr_str,
		__prपूर्णांक_hex(__entry->buf, __entry->buf_len),
		__entry->msg_len > माप(__entry->buf) ? " ..." : "",
		__entry->msg_len
	)
);
DEFINE_EVENT(io_data, io_ग_लिखो,
	TP_PROTO(पूर्णांक reg, पूर्णांक addr, स्थिर व्योम *io_buf, माप_प्रकार len),
	TP_ARGS(reg, addr, io_buf, len));
#घोषणा _trace_io_ind_ग_लिखो(reg, addr, io_buf, len)\
	trace_io_ग_लिखो(reg, addr, io_buf, len)
#घोषणा _trace_io_ग_लिखो(reg, io_buf, len) trace_io_ग_लिखो(reg, -1, io_buf, len)
DEFINE_EVENT(io_data, io_पढ़ो,
	TP_PROTO(पूर्णांक reg, पूर्णांक addr, स्थिर व्योम *io_buf, माप_प्रकार len),
	TP_ARGS(reg, addr, io_buf, len));
#घोषणा _trace_io_ind_पढ़ो(reg, addr, io_buf, len)\
	trace_io_पढ़ो(reg, addr, io_buf, len)
#घोषणा _trace_io_पढ़ो(reg, io_buf, len) trace_io_पढ़ो(reg, -1, io_buf, len)

DECLARE_EVENT_CLASS(io_data32,
	TP_PROTO(पूर्णांक reg, पूर्णांक addr, u32 val),
	TP_ARGS(reg, addr, val),
	TP_STRUCT__entry(
		__field(पूर्णांक, reg)
		__field(पूर्णांक, addr)
		__field(पूर्णांक, val)
		__array(u8, addr_str, 10)
	),
	TP_fast_assign(
		__entry->reg = reg;
		__entry->addr = addr;
		__entry->val = val;
		अगर (addr >= 0)
			snम_लिखो(__entry->addr_str, 10, "/%08x", addr);
		अन्यथा
			__entry->addr_str[0] = 0;
	),
	TP_prपूर्णांकk("%s%s: %08x",
		__prपूर्णांक_symbolic(__entry->reg, wfx_reg_list),
		__entry->addr_str,
		__entry->val
	)
);
DEFINE_EVENT(io_data32, io_ग_लिखो32,
	TP_PROTO(पूर्णांक reg, पूर्णांक addr, u32 val),
	TP_ARGS(reg, addr, val));
#घोषणा _trace_io_ind_ग_लिखो32(reg, addr, val) trace_io_ग_लिखो32(reg, addr, val)
#घोषणा _trace_io_ग_लिखो32(reg, val) trace_io_ग_लिखो32(reg, -1, val)
DEFINE_EVENT(io_data32, io_पढ़ो32,
	TP_PROTO(पूर्णांक reg, पूर्णांक addr, u32 val),
	TP_ARGS(reg, addr, val));
#घोषणा _trace_io_ind_पढ़ो32(reg, addr, val) trace_io_पढ़ो32(reg, addr, val)
#घोषणा _trace_io_पढ़ो32(reg, val) trace_io_पढ़ो32(reg, -1, val)

DECLARE_EVENT_CLASS(piggyback,
	TP_PROTO(u32 val, bool ignored),
	TP_ARGS(val, ignored),
	TP_STRUCT__entry(
		__field(पूर्णांक, val)
		__field(bool, ignored)
	),
	TP_fast_assign(
		__entry->val = val;
		__entry->ignored = ignored;
	),
	TP_prपूर्णांकk("CONTROL: %08x%s",
		__entry->val,
		__entry->ignored ? " (ignored)" : ""
	)
);
DEFINE_EVENT(piggyback, piggyback,
	TP_PROTO(u32 val, bool ignored),
	TP_ARGS(val, ignored));
#घोषणा _trace_piggyback(val, ignored) trace_piggyback(val, ignored)

TRACE_EVENT(bh_stats,
	TP_PROTO(पूर्णांक ind, पूर्णांक req, पूर्णांक cnf, पूर्णांक busy, bool release),
	TP_ARGS(ind, req, cnf, busy, release),
	TP_STRUCT__entry(
		__field(पूर्णांक, ind)
		__field(पूर्णांक, req)
		__field(पूर्णांक, cnf)
		__field(पूर्णांक, busy)
		__field(bool, release)
	),
	TP_fast_assign(
		__entry->ind = ind;
		__entry->req = req;
		__entry->cnf = cnf;
		__entry->busy = busy;
		__entry->release = release;
	),
	TP_prपूर्णांकk("IND/REQ/CNF:%3d/%3d/%3d, REQ in progress:%3d, WUP: %s",
		__entry->ind,
		__entry->req,
		__entry->cnf,
		__entry->busy,
		__entry->release ? "release" : "keep"
	)
);
#घोषणा _trace_bh_stats(ind, req, cnf, busy, release)\
	trace_bh_stats(ind, req, cnf, busy, release)

TRACE_EVENT(tx_stats,
	TP_PROTO(स्थिर काष्ठा hअगर_cnf_tx *tx_cnf, स्थिर काष्ठा sk_buff *skb,
		 पूर्णांक delay),
	TP_ARGS(tx_cnf, skb, delay),
	TP_STRUCT__entry(
		__field(पूर्णांक, pkt_id)
		__field(पूर्णांक, delay_media)
		__field(पूर्णांक, delay_queue)
		__field(पूर्णांक, delay_fw)
		__field(पूर्णांक, ack_failures)
		__field(पूर्णांक, flags)
		__array(पूर्णांक, rate, 4)
		__array(पूर्णांक, tx_count, 4)
	),
	TP_fast_assign(
		// Keep sync with wfx_rates definition in मुख्य.c
		अटल स्थिर पूर्णांक hw_rate[] = अणु 0, 1, 2, 3, 6, 7, 8, 9,
					       10, 11, 12, 13 पूर्ण;
		स्थिर काष्ठा ieee80211_tx_info *tx_info =
			(स्थिर काष्ठा ieee80211_tx_info *)skb->cb;
		स्थिर काष्ठा ieee80211_tx_rate *rates = tx_info->driver_rates;
		पूर्णांक i;

		__entry->pkt_id = tx_cnf->packet_id;
		__entry->delay_media = le32_to_cpu(tx_cnf->media_delay);
		__entry->delay_queue = le32_to_cpu(tx_cnf->tx_queue_delay);
		__entry->delay_fw = delay;
		__entry->ack_failures = tx_cnf->ack_failures;
		अगर (!tx_cnf->status || __entry->ack_failures)
			__entry->ack_failures += 1;

		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			अगर (rates[0].flags & IEEE80211_TX_RC_MCS)
				__entry->rate[i] = rates[i].idx;
			अन्यथा
				__entry->rate[i] = hw_rate[rates[i].idx];
			__entry->tx_count[i] = rates[i].count;
		पूर्ण
		__entry->flags = 0;
		अगर (rates[0].flags & IEEE80211_TX_RC_MCS)
			__entry->flags |= 0x01;
		अगर (rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
			__entry->flags |= 0x02;
		अगर (rates[0].flags & IEEE80211_TX_RC_GREEN_FIELD)
			__entry->flags |= 0x04;
		अगर (rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS)
			__entry->flags |= 0x08;
		अगर (tx_info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM)
			__entry->flags |= 0x10;
		अगर (tx_cnf->status)
			__entry->flags |= 0x20;
		अगर (tx_cnf->status == HIF_STATUS_TX_FAIL_REQUEUE)
			__entry->flags |= 0x40;
	),
	TP_prपूर्णांकk("packet ID: %08x, rate policy: %s %d|%d %d|%d %d|%d %d|%d -> %d attempt, Delays media/queue/total: %4dus/%4dus/%4dus",
		__entry->pkt_id,
		__prपूर्णांक_flags(__entry->flags, शून्य,
			अणु 0x01, "M" पूर्ण, अणु 0x02, "S" पूर्ण, अणु 0x04, "G" पूर्ण,
			अणु 0x08, "R" पूर्ण, अणु 0x10, "D" पूर्ण, अणु 0x20, "F" पूर्ण,
			अणु 0x40, "Q" पूर्ण),
		__entry->rate[0],
		__entry->tx_count[0],
		__entry->rate[1],
		__entry->tx_count[1],
		__entry->rate[2],
		__entry->tx_count[2],
		__entry->rate[3],
		__entry->tx_count[3],
		__entry->ack_failures,
		__entry->delay_media,
		__entry->delay_queue,
		__entry->delay_fw
	)
);
#घोषणा _trace_tx_stats(tx_cnf, skb, delay) trace_tx_stats(tx_cnf, skb, delay)

TRACE_EVENT(queues_stats,
	TP_PROTO(काष्ठा wfx_dev *wdev, स्थिर काष्ठा wfx_queue *elected_queue),
	TP_ARGS(wdev, elected_queue),
	TP_STRUCT__entry(
		__field(पूर्णांक, vअगर_id)
		__field(पूर्णांक, queue_id)
		__array(पूर्णांक, hw, IEEE80211_NUM_ACS * 2)
		__array(पूर्णांक, drv, IEEE80211_NUM_ACS * 2)
		__array(पूर्णांक, cab, IEEE80211_NUM_ACS * 2)
	),
	TP_fast_assign(
		स्थिर काष्ठा wfx_queue *queue;
		काष्ठा wfx_vअगर *wvअगर;
		पूर्णांक i, j;

		क्रम (j = 0; j < IEEE80211_NUM_ACS * 2; j++) अणु
			__entry->hw[j] = -1;
			__entry->drv[j] = -1;
			__entry->cab[j] = -1;
		पूर्ण
		__entry->vअगर_id = -1;
		__entry->queue_id = -1;
		wvअगर = शून्य;
		जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य) अणु
			क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
				j = wvअगर->id * IEEE80211_NUM_ACS + i;
				WARN_ON(j >= IEEE80211_NUM_ACS * 2);
				queue = &wvअगर->tx_queue[i];
				__entry->hw[j] = atomic_पढ़ो(&queue->pending_frames);
				__entry->drv[j] = skb_queue_len(&queue->normal);
				__entry->cab[j] = skb_queue_len(&queue->cab);
				अगर (queue == elected_queue) अणु
					__entry->vअगर_id = wvअगर->id;
					__entry->queue_id = i;
				पूर्ण
			पूर्ण
		पूर्ण
	),
	TP_prपूर्णांकk("got skb from %d/%d, pend. hw/norm/cab: [ %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d ] [ %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d ]",
		__entry->vअगर_id, __entry->queue_id,
		__entry->hw[0], __entry->drv[0], __entry->cab[0],
		__entry->hw[1], __entry->drv[1], __entry->cab[1],
		__entry->hw[2], __entry->drv[2], __entry->cab[2],
		__entry->hw[3], __entry->drv[3], __entry->cab[3],
		__entry->hw[4], __entry->drv[4], __entry->cab[4],
		__entry->hw[5], __entry->drv[5], __entry->cab[5],
		__entry->hw[6], __entry->drv[6], __entry->cab[6],
		__entry->hw[7], __entry->drv[7], __entry->cab[7]
	)
);

#पूर्ण_अगर

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता traces

#समावेश <trace/define_trace.h>
