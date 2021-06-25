<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
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

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर.h>
#समावेश "rsi_debugfs.h"
#समावेश "rsi_mgmt.h"
#समावेश "rsi_common.h"
#समावेश "rsi_ps.h"

अक्षर *str_psstate(क्रमागत ps_state state)
अणु
	चयन (state) अणु
	हाल PS_NONE:
		वापस "PS_NONE";
	हाल PS_DISABLE_REQ_SENT:
		वापस "PS_DISABLE_REQ_SENT";
	हाल PS_ENABLE_REQ_SENT:
		वापस "PS_ENABLE_REQ_SENT";
	हाल PS_ENABLED:
		वापस "PS_ENABLED";
	शेष:
		वापस "INVALID_STATE";
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rsi_modअगरy_ps_state(काष्ठा rsi_hw *adapter,
				       क्रमागत ps_state nstate)
अणु
	rsi_dbg(INFO_ZONE, "PS state changed %s => %s\n",
		str_psstate(adapter->ps_state),
		str_psstate(nstate));

	adapter->ps_state = nstate;
पूर्ण

व्योम rsi_शेष_ps_params(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_ps_info *ps_info = &adapter->ps_info;

	ps_info->enabled = true;
	ps_info->sleep_type = RSI_SLEEP_TYPE_LP;
	ps_info->tx_threshold = 0;
	ps_info->rx_threshold = 0;
	ps_info->tx_hysterisis = 0;
	ps_info->rx_hysterisis = 0;
	ps_info->monitor_पूर्णांकerval = 0;
	ps_info->listen_पूर्णांकerval = RSI_DEF_LISTEN_INTERVAL;
	ps_info->num_bcns_per_lis_पूर्णांक = 0;
	ps_info->dtim_पूर्णांकerval_duration = 0;
	ps_info->num_dtims_per_sleep = 0;
	ps_info->deep_sleep_wakeup_period = RSI_DEF_DS_WAKEUP_PERIOD;
पूर्ण

व्योम rsi_enable_ps(काष्ठा rsi_hw *adapter, काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (adapter->ps_state != PS_NONE) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Cannot accept enable PS in %s state\n",
			__func__, str_psstate(adapter->ps_state));
		वापस;
	पूर्ण

	अगर (rsi_send_ps_request(adapter, true, vअगर)) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to send PS request to device\n",
			__func__);
		वापस;
	पूर्ण

	rsi_modअगरy_ps_state(adapter, PS_ENABLE_REQ_SENT);
पूर्ण

/* This function is used to disable घातer save */
व्योम rsi_disable_ps(काष्ठा rsi_hw *adapter, काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (adapter->ps_state != PS_ENABLED) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Cannot accept disable PS in %s state\n",
			__func__, str_psstate(adapter->ps_state));
		वापस;
	पूर्ण

	अगर (rsi_send_ps_request(adapter, false, vअगर)) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to send PS request to device\n",
			__func__);
		वापस;
	पूर्ण

	rsi_modअगरy_ps_state(adapter, PS_DISABLE_REQ_SENT);
पूर्ण

व्योम rsi_conf_uapsd(काष्ठा rsi_hw *adapter, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret;

	अगर (adapter->ps_state != PS_ENABLED)
		वापस;

	ret = rsi_send_ps_request(adapter, false, vअगर);
	अगर (!ret)
		ret = rsi_send_ps_request(adapter, true, vअगर);
	अगर (ret)
		rsi_dbg(ERR_ZONE,
			"%s: Failed to send PS request to device\n",
			__func__);
पूर्ण

पूर्णांक rsi_handle_ps_confirm(काष्ठा rsi_hw *adapter, u8 *msg)
अणु
	u16 cfm_type = get_unaligned_le16(msg + PS_CONFIRM_INDEX);

	चयन (cfm_type) अणु
	हाल RSI_SLEEP_REQUEST:
		अगर (adapter->ps_state == PS_ENABLE_REQ_SENT)
			rsi_modअगरy_ps_state(adapter, PS_ENABLED);
		अवरोध;
	हाल RSI_WAKEUP_REQUEST:
		अगर (adapter->ps_state == PS_DISABLE_REQ_SENT)
			rsi_modअगरy_ps_state(adapter, PS_NONE);
		अवरोध;
	शेष:
		rsi_dbg(ERR_ZONE,
			"Invalid PS confirm type %x in state %s\n",
			cfm_type, str_psstate(adapter->ps_state));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

