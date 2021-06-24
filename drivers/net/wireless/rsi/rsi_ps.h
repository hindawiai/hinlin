<शैली गुरु>
/*
 * Copyright (c) 2017 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_PS_H__
#घोषणा __RSI_PS_H__

#घोषणा PS_CONFIRM_INDEX	12
#घोषणा RSI_DEF_DS_WAKEUP_PERIOD	200
#घोषणा RSI_DEF_LISTEN_INTERVAL		200
#घोषणा RSI_SLEEP_TYPE_LP		1

क्रमागत ps_state अणु
	PS_NONE = 0,
	PS_ENABLE_REQ_SENT = 1,
	PS_DISABLE_REQ_SENT = 2,
	PS_ENABLED = 3
पूर्ण;

काष्ठा ps_sleep_params अणु
	u8 enable;
	u8 sleep_type;
	u8 connected_sleep;
	u8 reserved1;
	__le16 num_bcns_per_lis_पूर्णांक;
	__le16 wakeup_type;
	__le32 sleep_duration;
पूर्ण __packed;

काष्ठा rsi_ps_info अणु
	u8 enabled;
	u8 sleep_type;
	u8 tx_threshold;
	u8 rx_threshold;
	u8 tx_hysterisis;
	u8 rx_hysterisis;
	u16 monitor_पूर्णांकerval;
	u32 listen_पूर्णांकerval;
	u16 num_bcns_per_lis_पूर्णांक;
	u32 dtim_पूर्णांकerval_duration;
	u16 num_dtims_per_sleep;
	u32 deep_sleep_wakeup_period;
पूर्ण __packed;

अक्षर *str_psstate(क्रमागत ps_state state);
व्योम rsi_enable_ps(काष्ठा rsi_hw *adapter, काष्ठा ieee80211_vअगर *vअगर);
व्योम rsi_disable_ps(काष्ठा rsi_hw *adapter, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक rsi_handle_ps_confirm(काष्ठा rsi_hw *adapter, u8 *msg);
व्योम rsi_शेष_ps_params(काष्ठा rsi_hw *hw);
व्योम rsi_conf_uapsd(काष्ठा rsi_hw *adapter, काष्ठा ieee80211_vअगर *vअगर);
#पूर्ण_अगर
