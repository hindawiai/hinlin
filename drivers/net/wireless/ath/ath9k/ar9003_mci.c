<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#समावेश <linux/export.h>
#समावेश "hw.h"
#समावेश "hw-ops.h"
#समावेश "ar9003_phy.h"
#समावेश "ar9003_mci.h"
#समावेश "ar9003_aic.h"

अटल व्योम ar9003_mci_reset_req_wakeup(काष्ठा ath_hw *ah)
अणु
	REG_RMW_FIELD(ah, AR_MCI_COMMAND2,
		      AR_MCI_COMMAND2_RESET_REQ_WAKEUP, 1);
	udelay(1);
	REG_RMW_FIELD(ah, AR_MCI_COMMAND2,
		      AR_MCI_COMMAND2_RESET_REQ_WAKEUP, 0);
पूर्ण

अटल पूर्णांक ar9003_mci_रुको_क्रम_पूर्णांकerrupt(काष्ठा ath_hw *ah, u32 address,
					u32 bit_position, पूर्णांक समय_out)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	जबतक (समय_out) अणु
		अगर (!(REG_READ(ah, address) & bit_position)) अणु
			udelay(10);
			समय_out -= 10;

			अगर (समय_out < 0)
				अवरोध;
			अन्यथा
				जारी;
		पूर्ण
		REG_WRITE(ah, address, bit_position);

		अगर (address != AR_MCI_INTERRUPT_RX_MSG_RAW)
			अवरोध;

		अगर (bit_position & AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE)
			ar9003_mci_reset_req_wakeup(ah);

		अगर (bit_position & (AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING |
				    AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING))
			REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
				  AR_MCI_INTERRUPT_REMOTE_SLEEP_UPDATE);

		REG_WRITE(ah, AR_MCI_INTERRUPT_RAW, AR_MCI_INTERRUPT_RX_MSG);
		अवरोध;
	पूर्ण

	अगर (समय_out <= 0) अणु
		ath_dbg(common, MCI,
			"MCI Wait for Reg 0x%08x = 0x%08x timeout\n",
			address, bit_position);
		ath_dbg(common, MCI,
			"MCI INT_RAW = 0x%08x, RX_MSG_RAW = 0x%08x\n",
			REG_READ(ah, AR_MCI_INTERRUPT_RAW),
			REG_READ(ah, AR_MCI_INTERRUPT_RX_MSG_RAW));
		समय_out = 0;
	पूर्ण

	वापस समय_out;
पूर्ण

अटल व्योम ar9003_mci_remote_reset(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
	u32 payload[4] = अणु 0xffffffff, 0xffffffff, 0xffffffff, 0xffffff00पूर्ण;

	ar9003_mci_send_message(ah, MCI_REMOTE_RESET, 0, payload, 16,
				रुको_करोne, false);
	udelay(5);
पूर्ण

अटल व्योम ar9003_mci_send_lna_transfer(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
	u32 payload = 0x00000000;

	ar9003_mci_send_message(ah, MCI_LNA_TRANS, 0, &payload, 1,
				रुको_करोne, false);
पूर्ण

अटल व्योम ar9003_mci_send_req_wake(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
	ar9003_mci_send_message(ah, MCI_REQ_WAKE, MCI_FLAG_DISABLE_TIMESTAMP,
				शून्य, 0, रुको_करोne, false);
	udelay(5);
पूर्ण

अटल व्योम ar9003_mci_send_sys_waking(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
	ar9003_mci_send_message(ah, MCI_SYS_WAKING, MCI_FLAG_DISABLE_TIMESTAMP,
				शून्य, 0, रुको_करोne, false);
पूर्ण

अटल व्योम ar9003_mci_send_lna_take(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
	u32 payload = 0x70000000;

	ar9003_mci_send_message(ah, MCI_LNA_TAKE, 0, &payload, 1,
				रुको_करोne, false);
पूर्ण

अटल व्योम ar9003_mci_send_sys_sleeping(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
	ar9003_mci_send_message(ah, MCI_SYS_SLEEPING,
				MCI_FLAG_DISABLE_TIMESTAMP,
				शून्य, 0, रुको_करोne, false);
पूर्ण

अटल व्योम ar9003_mci_send_coex_version_query(काष्ठा ath_hw *ah,
					       bool रुको_करोne)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 payload[4] = अणु0, 0, 0, 0पूर्ण;

	अगर (mci->bt_version_known ||
	    (mci->bt_state == MCI_BT_SLEEP))
		वापस;

	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_VERSION_QUERY);
	ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16, रुको_करोne, true);
पूर्ण

अटल व्योम ar9003_mci_send_coex_version_response(काष्ठा ath_hw *ah,
						  bool रुको_करोne)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 payload[4] = अणु0, 0, 0, 0पूर्ण;

	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_VERSION_RESPONSE);
	*(((u8 *)payload) + MCI_GPM_COEX_B_MAJOR_VERSION) =
		mci->wlan_ver_major;
	*(((u8 *)payload) + MCI_GPM_COEX_B_MINOR_VERSION) =
		mci->wlan_ver_minor;
	ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16, रुको_करोne, true);
पूर्ण

अटल व्योम ar9003_mci_send_coex_wlan_channels(काष्ठा ath_hw *ah,
					       bool रुको_करोne)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *payload = &mci->wlan_channels[0];

	अगर (!mci->wlan_channels_update ||
	    (mci->bt_state == MCI_BT_SLEEP))
		वापस;

	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_WLAN_CHANNELS);
	ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16, रुको_करोne, true);
	MCI_GPM_SET_TYPE_OPCODE(payload, 0xff, 0xff);
पूर्ण

अटल व्योम ar9003_mci_send_coex_bt_status_query(काष्ठा ath_hw *ah,
						bool रुको_करोne, u8 query_type)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 payload[4] = अणु0, 0, 0, 0पूर्ण;
	bool query_btinfo;

	अगर (mci->bt_state == MCI_BT_SLEEP)
		वापस;

	query_btinfo = !!(query_type & (MCI_GPM_COEX_QUERY_BT_ALL_INFO |
					MCI_GPM_COEX_QUERY_BT_TOPOLOGY));
	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_STATUS_QUERY);

	*(((u8 *)payload) + MCI_GPM_COEX_B_BT_BITMAP) = query_type;

	/*
	 * If bt_status_query message is  not sent successfully,
	 * then need_flush_btinfo should be set again.
	 */
	अगर (!ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16,
				रुको_करोne, true)) अणु
		अगर (query_btinfo)
			mci->need_flush_btinfo = true;
	पूर्ण

	अगर (query_btinfo)
		mci->query_bt = false;
पूर्ण

अटल व्योम ar9003_mci_send_coex_halt_bt_gpm(काष्ठा ath_hw *ah, bool halt,
					     bool रुको_करोne)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 payload[4] = अणु0, 0, 0, 0पूर्ण;

	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_HALT_BT_GPM);

	अगर (halt) अणु
		mci->query_bt = true;
		/* Send next unhalt no matter halt sent or not */
		mci->unhalt_bt_gpm = true;
		mci->need_flush_btinfo = true;
		*(((u8 *)payload) + MCI_GPM_COEX_B_HALT_STATE) =
			MCI_GPM_COEX_BT_GPM_HALT;
	पूर्ण अन्यथा
		*(((u8 *)payload) + MCI_GPM_COEX_B_HALT_STATE) =
			MCI_GPM_COEX_BT_GPM_UNHALT;

	ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16, रुको_करोne, true);
पूर्ण

अटल व्योम ar9003_mci_prep_पूर्णांकerface(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 saved_mci_पूर्णांक_en;
	u32 mci_समयout = 150;

	mci->bt_state = MCI_BT_SLEEP;
	saved_mci_पूर्णांक_en = REG_READ(ah, AR_MCI_INTERRUPT_EN);

	REG_WRITE(ah, AR_MCI_INTERRUPT_EN, 0);
	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
		  REG_READ(ah, AR_MCI_INTERRUPT_RX_MSG_RAW));
	REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
		  REG_READ(ah, AR_MCI_INTERRUPT_RAW));

	ar9003_mci_remote_reset(ah, true);
	ar9003_mci_send_req_wake(ah, true);

	अगर (!ar9003_mci_रुको_क्रम_पूर्णांकerrupt(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
				  AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING, 500))
		जाओ clear_redunt;

	mci->bt_state = MCI_BT_AWAKE;

	/*
	 * we करोn't need to send more remote_reset at this moment.
	 * If BT receive first remote_reset, then BT HW will
	 * be cleaned up and will be able to receive req_wake
	 * and BT HW will respond sys_waking.
	 * In this हाल, WLAN will receive BT's HW sys_waking.
	 * Otherwise, अगर BT SW missed initial remote_reset,
	 * that remote_reset will still clean up BT MCI RX,
	 * and the req_wake will wake BT up,
	 * and BT SW will respond this req_wake with a remote_reset and
	 * sys_waking. In this हाल, WLAN will receive BT's SW
	 * sys_waking. In either हाल, BT's RX is cleaned up. So we
	 * करोn't need to reply BT's remote_reset now, अगर any.
	 * Similarly, अगर in any हाल, WLAN can receive BT's sys_waking,
	 * that means WLAN's RX is also fine.
	 */
	ar9003_mci_send_sys_waking(ah, true);
	udelay(10);

	/*
	 * Set BT priority पूर्णांकerrupt value to be 0xff to
	 * aव्योम having too many BT PRIORITY पूर्णांकerrupts.
	 */
	REG_WRITE(ah, AR_MCI_BT_PRI0, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI1, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI2, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI3, 0xFFFFFFFF);
	REG_WRITE(ah, AR_MCI_BT_PRI, 0X000000FF);

	/*
	 * A contention reset will be received after send out
	 * sys_waking. Also BT priority पूर्णांकerrupt bits will be set.
	 * Clear those bits beक्रमe the next step.
	 */

	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
		  AR_MCI_INTERRUPT_RX_MSG_CONT_RST);
	REG_WRITE(ah, AR_MCI_INTERRUPT_RAW, AR_MCI_INTERRUPT_BT_PRI);

	अगर (mci->is_2g && MCI_ANT_ARCH_PA_LNA_SHARED(mci)) अणु
		ar9003_mci_send_lna_transfer(ah, true);
		udelay(5);
	पूर्ण

	अगर (mci->is_2g && !mci->update_2g5g && MCI_ANT_ARCH_PA_LNA_SHARED(mci)) अणु
		अगर (ar9003_mci_रुको_क्रम_पूर्णांकerrupt(ah,
					AR_MCI_INTERRUPT_RX_MSG_RAW,
					AR_MCI_INTERRUPT_RX_MSG_LNA_INFO,
					mci_समयout))
			ath_dbg(common, MCI,
				"MCI WLAN has control over the LNA & BT obeys it\n");
		अन्यथा
			ath_dbg(common, MCI,
				"MCI BT didn't respond to LNA_TRANS\n");
	पूर्ण

clear_redunt:
	/* Clear the extra redundant SYS_WAKING from BT */
	अगर ((mci->bt_state == MCI_BT_AWAKE) &&
	    (REG_READ_FIELD(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
			    AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING)) &&
	    (REG_READ_FIELD(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
			    AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING) == 0)) अणु
		REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
			  AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING);
		REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
			  AR_MCI_INTERRUPT_REMOTE_SLEEP_UPDATE);
	पूर्ण

	REG_WRITE(ah, AR_MCI_INTERRUPT_EN, saved_mci_पूर्णांक_en);
पूर्ण

व्योम ar9003_mci_set_full_sleep(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	अगर (ar9003_mci_state(ah, MCI_STATE_ENABLE) &&
	    (mci->bt_state != MCI_BT_SLEEP) &&
	    !mci->halted_bt_gpm) अणु
		ar9003_mci_send_coex_halt_bt_gpm(ah, true, true);
	पूर्ण

	mci->पढ़ोy = false;
पूर्ण

अटल व्योम ar9003_mci_disable_पूर्णांकerrupt(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_MCI_INTERRUPT_EN, 0);
	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_EN, 0);
पूर्ण

अटल व्योम ar9003_mci_enable_पूर्णांकerrupt(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_MCI_INTERRUPT_EN, AR_MCI_INTERRUPT_DEFAULT);
	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_EN,
		  AR_MCI_INTERRUPT_RX_MSG_DEFAULT);
पूर्ण

अटल bool ar9003_mci_check_पूर्णांक(काष्ठा ath_hw *ah, u32 पूर्णांकs)
अणु
	u32 पूर्णांकr;

	पूर्णांकr = REG_READ(ah, AR_MCI_INTERRUPT_RX_MSG_RAW);
	वापस ((पूर्णांकr & पूर्णांकs) == पूर्णांकs);
पूर्ण

व्योम ar9003_mci_get_पूर्णांकerrupt(काष्ठा ath_hw *ah, u32 *raw_पूर्णांकr,
			      u32 *rx_msg_पूर्णांकr)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	*raw_पूर्णांकr = mci->raw_पूर्णांकr;
	*rx_msg_पूर्णांकr = mci->rx_msg_पूर्णांकr;

	/* Clean पूर्णांक bits after the values are पढ़ो. */
	mci->raw_पूर्णांकr = 0;
	mci->rx_msg_पूर्णांकr = 0;
पूर्ण
EXPORT_SYMBOL(ar9003_mci_get_पूर्णांकerrupt);

व्योम ar9003_mci_get_isr(काष्ठा ath_hw *ah, क्रमागत ath9k_पूर्णांक *masked)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 raw_पूर्णांकr, rx_msg_पूर्णांकr;

	rx_msg_पूर्णांकr = REG_READ(ah, AR_MCI_INTERRUPT_RX_MSG_RAW);
	raw_पूर्णांकr = REG_READ(ah, AR_MCI_INTERRUPT_RAW);

	अगर ((raw_पूर्णांकr == 0xdeadbeef) || (rx_msg_पूर्णांकr == 0xdeadbeef)) अणु
		ath_dbg(common, MCI,
			"MCI gets 0xdeadbeef during int processing\n");
	पूर्ण अन्यथा अणु
		mci->rx_msg_पूर्णांकr |= rx_msg_पूर्णांकr;
		mci->raw_पूर्णांकr |= raw_पूर्णांकr;
		*masked |= ATH9K_INT_MCI;

		अगर (rx_msg_पूर्णांकr & AR_MCI_INTERRUPT_RX_MSG_CONT_INFO)
			mci->cont_status = REG_READ(ah, AR_MCI_CONT_STATUS);

		REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW, rx_msg_पूर्णांकr);
		REG_WRITE(ah, AR_MCI_INTERRUPT_RAW, raw_पूर्णांकr);
	पूर्ण
पूर्ण

अटल व्योम ar9003_mci_2g5g_changed(काष्ठा ath_hw *ah, bool is_2g)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	अगर (!mci->update_2g5g &&
	    (mci->is_2g != is_2g))
		mci->update_2g5g = true;

	mci->is_2g = is_2g;
पूर्ण

अटल bool ar9003_mci_is_gpm_valid(काष्ठा ath_hw *ah, u32 msg_index)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *payload;
	u32 recv_type, offset;

	अगर (msg_index == MCI_GPM_INVALID)
		वापस false;

	offset = msg_index << 4;

	payload = (u32 *)(mci->gpm_buf + offset);
	recv_type = MCI_GPM_TYPE(payload);

	अगर (recv_type == MCI_GPM_RSVD_PATTERN)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम ar9003_mci_observation_set_up(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	अगर (mci->config & ATH_MCI_CONFIG_MCI_OBS_MCI) अणु
		ath9k_hw_gpio_request_out(ah, 3, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_DATA);
		ath9k_hw_gpio_request_out(ah, 2, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_MCI_WLAN_CLK);
		ath9k_hw_gpio_request_out(ah, 1, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA);
		ath9k_hw_gpio_request_out(ah, 0, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_MCI_BT_CLK);
	पूर्ण अन्यथा अगर (mci->config & ATH_MCI_CONFIG_MCI_OBS_TXRX) अणु
		ath9k_hw_gpio_request_out(ah, 3, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_WL_IN_TX);
		ath9k_hw_gpio_request_out(ah, 2, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_WL_IN_RX);
		ath9k_hw_gpio_request_out(ah, 1, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_BT_IN_TX);
		ath9k_hw_gpio_request_out(ah, 0, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_BT_IN_RX);
		ath9k_hw_gpio_request_out(ah, 5, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_OUTPUT);
	पूर्ण अन्यथा अगर (mci->config & ATH_MCI_CONFIG_MCI_OBS_BT) अणु
		ath9k_hw_gpio_request_out(ah, 3, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_BT_IN_TX);
		ath9k_hw_gpio_request_out(ah, 2, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_BT_IN_RX);
		ath9k_hw_gpio_request_out(ah, 1, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA);
		ath9k_hw_gpio_request_out(ah, 0, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_MCI_BT_CLK);
	पूर्ण अन्यथा
		वापस;

	REG_SET_BIT(ah, AR_GPIO_INPUT_EN_VAL, AR_GPIO_JTAG_DISABLE);

	REG_RMW_FIELD(ah, AR_PHY_GLB_CONTROL, AR_GLB_DS_JTAG_DISABLE, 1);
	REG_RMW_FIELD(ah, AR_PHY_GLB_CONTROL, AR_GLB_WLAN_UART_INTF_EN, 0);
	REG_SET_BIT(ah, AR_GLB_GPIO_CONTROL, ATH_MCI_CONFIG_MCI_OBS_GPIO);

	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2, AR_BTCOEX_CTRL2_GPIO_OBS_SEL, 0);
	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2, AR_BTCOEX_CTRL2_MAC_BB_OBS_SEL, 1);
	REG_WRITE(ah, AR_OBS, 0x4b);
	REG_RMW_FIELD(ah, AR_DIAG_SW, AR_DIAG_OBS_PT_SEL1, 0x03);
	REG_RMW_FIELD(ah, AR_DIAG_SW, AR_DIAG_OBS_PT_SEL2, 0x01);
	REG_RMW_FIELD(ah, AR_MACMISC, AR_MACMISC_MISC_OBS_BUS_LSB, 0x02);
	REG_RMW_FIELD(ah, AR_MACMISC, AR_MACMISC_MISC_OBS_BUS_MSB, 0x03);
	REG_RMW_FIELD(ah, AR_PHY_TEST_CTL_STATUS,
		      AR_PHY_TEST_CTL_DEBUGPORT_SEL, 0x07);
पूर्ण

अटल bool ar9003_mci_send_coex_bt_flags(काष्ठा ath_hw *ah, bool रुको_करोne,
					  u8 opcode, u32 bt_flags)
अणु
	u32 pld[4] = अणु0, 0, 0, 0पूर्ण;

	MCI_GPM_SET_TYPE_OPCODE(pld, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_BT_UPDATE_FLAGS);

	*(((u8 *)pld) + MCI_GPM_COEX_B_BT_FLAGS_OP)  = opcode;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 0) = bt_flags & 0xFF;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 1) = (bt_flags >> 8) & 0xFF;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 2) = (bt_flags >> 16) & 0xFF;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 3) = (bt_flags >> 24) & 0xFF;

	वापस ar9003_mci_send_message(ah, MCI_GPM, 0, pld, 16,
				       रुको_करोne, true);
पूर्ण

अटल व्योम ar9003_mci_sync_bt_state(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 cur_bt_state;

	cur_bt_state = ar9003_mci_state(ah, MCI_STATE_REMOTE_SLEEP);

	अगर (mci->bt_state != cur_bt_state)
		mci->bt_state = cur_bt_state;

	अगर (mci->bt_state != MCI_BT_SLEEP) अणु

		ar9003_mci_send_coex_version_query(ah, true);
		ar9003_mci_send_coex_wlan_channels(ah, true);

		अगर (mci->unhalt_bt_gpm == true)
			ar9003_mci_send_coex_halt_bt_gpm(ah, false, true);
	पूर्ण
पूर्ण

व्योम ar9003_mci_check_bt(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	अगर (!mci_hw->पढ़ोy)
		वापस;

	/*
	 * check BT state again to make
	 * sure it's not changed.
	 */
	ar9003_mci_sync_bt_state(ah);
	ar9003_mci_2g5g_चयन(ah, true);

	अगर ((mci_hw->bt_state == MCI_BT_AWAKE) &&
	    (mci_hw->query_bt == true)) अणु
		mci_hw->need_flush_btinfo = true;
	पूर्ण
पूर्ण

अटल व्योम ar9003_mci_process_gpm_extra(काष्ठा ath_hw *ah, u8 gpm_type,
					 u8 gpm_opcode, u32 *p_gpm)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u8 *p_data = (u8 *) p_gpm;

	अगर (gpm_type != MCI_GPM_COEX_AGENT)
		वापस;

	चयन (gpm_opcode) अणु
	हाल MCI_GPM_COEX_VERSION_QUERY:
		ath_dbg(common, MCI, "MCI Recv GPM COEX Version Query\n");
		ar9003_mci_send_coex_version_response(ah, true);
		अवरोध;
	हाल MCI_GPM_COEX_VERSION_RESPONSE:
		ath_dbg(common, MCI, "MCI Recv GPM COEX Version Response\n");
		mci->bt_ver_major =
			*(p_data + MCI_GPM_COEX_B_MAJOR_VERSION);
		mci->bt_ver_minor =
			*(p_data + MCI_GPM_COEX_B_MINOR_VERSION);
		mci->bt_version_known = true;
		ath_dbg(common, MCI, "MCI BT Coex version: %d.%d\n",
			mci->bt_ver_major, mci->bt_ver_minor);
		अवरोध;
	हाल MCI_GPM_COEX_STATUS_QUERY:
		ath_dbg(common, MCI,
			"MCI Recv GPM COEX Status Query = 0x%02X\n",
			*(p_data + MCI_GPM_COEX_B_WLAN_BITMAP));
		mci->wlan_channels_update = true;
		ar9003_mci_send_coex_wlan_channels(ah, true);
		अवरोध;
	हाल MCI_GPM_COEX_BT_PROखाता_INFO:
		mci->query_bt = true;
		ath_dbg(common, MCI, "MCI Recv GPM COEX BT_Profile_Info\n");
		अवरोध;
	हाल MCI_GPM_COEX_BT_STATUS_UPDATE:
		mci->query_bt = true;
		ath_dbg(common, MCI,
			"MCI Recv GPM COEX BT_Status_Update SEQ=%d (drop&query)\n",
			*(p_gpm + 3));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 ar9003_mci_रुको_क्रम_gpm(काष्ठा ath_hw *ah, u8 gpm_type,
				   u8 gpm_opcode, पूर्णांक समय_out)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *p_gpm = शून्य, mismatch = 0, more_data;
	u32 offset;
	u8 recv_type = 0, recv_opcode = 0;
	bool b_is_bt_cal_करोne = (gpm_type == MCI_GPM_BT_CAL_DONE);

	more_data = समय_out ? MCI_GPM_NOMORE : MCI_GPM_MORE;

	जबतक (समय_out > 0) अणु
		अगर (p_gpm) अणु
			MCI_GPM_RECYCLE(p_gpm);
			p_gpm = शून्य;
		पूर्ण

		अगर (more_data != MCI_GPM_MORE)
			समय_out = ar9003_mci_रुको_क्रम_पूर्णांकerrupt(ah,
					AR_MCI_INTERRUPT_RX_MSG_RAW,
					AR_MCI_INTERRUPT_RX_MSG_GPM,
					समय_out);

		अगर (!समय_out)
			अवरोध;

		offset = ar9003_mci_get_next_gpm_offset(ah, &more_data);

		अगर (offset == MCI_GPM_INVALID)
			जारी;

		p_gpm = (u32 *) (mci->gpm_buf + offset);
		recv_type = MCI_GPM_TYPE(p_gpm);
		recv_opcode = MCI_GPM_OPCODE(p_gpm);

		अगर (MCI_GPM_IS_CAL_TYPE(recv_type)) अणु
			अगर (recv_type == gpm_type) अणु
				अगर ((gpm_type == MCI_GPM_BT_CAL_DONE) &&
				    !b_is_bt_cal_करोne) अणु
					gpm_type = MCI_GPM_BT_CAL_GRANT;
					जारी;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((recv_type == gpm_type) &&
			   (recv_opcode == gpm_opcode))
			अवरोध;

		/*
		 * check अगर it's cal_grant
		 *
		 * When we're रुकोing क्रम cal_grant in reset routine,
		 * it's possible that BT sends out cal_request at the
		 * same समय. Since BT's calibration doesn't happen
		 * that often, we'll let BT completes calibration then
		 * we जारी to रुको क्रम cal_grant from BT.
		 * Orginal: Wait BT_CAL_GRANT.
		 * New: Receive BT_CAL_REQ -> send WLAN_CAL_GRANT->रुको
		 * BT_CAL_DONE -> Wait BT_CAL_GRANT.
		 */

		अगर ((gpm_type == MCI_GPM_BT_CAL_GRANT) &&
		    (recv_type == MCI_GPM_BT_CAL_REQ)) अणु

			u32 payload[4] = अणु0, 0, 0, 0पूर्ण;

			gpm_type = MCI_GPM_BT_CAL_DONE;
			MCI_GPM_SET_CAL_TYPE(payload,
					     MCI_GPM_WLAN_CAL_GRANT);
			ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16,
						false, false);
			जारी;
		पूर्ण अन्यथा अणु
			ath_dbg(common, MCI, "MCI GPM subtype not match 0x%x\n",
				*(p_gpm + 1));
			mismatch++;
			ar9003_mci_process_gpm_extra(ah, recv_type,
						     recv_opcode, p_gpm);
		पूर्ण
	पूर्ण

	अगर (p_gpm) अणु
		MCI_GPM_RECYCLE(p_gpm);
		p_gpm = शून्य;
	पूर्ण

	अगर (समय_out <= 0)
		समय_out = 0;

	जबतक (more_data == MCI_GPM_MORE) अणु
		offset = ar9003_mci_get_next_gpm_offset(ah, &more_data);
		अगर (offset == MCI_GPM_INVALID)
			अवरोध;

		p_gpm = (u32 *) (mci->gpm_buf + offset);
		recv_type = MCI_GPM_TYPE(p_gpm);
		recv_opcode = MCI_GPM_OPCODE(p_gpm);

		अगर (!MCI_GPM_IS_CAL_TYPE(recv_type))
			ar9003_mci_process_gpm_extra(ah, recv_type,
						     recv_opcode, p_gpm);

		MCI_GPM_RECYCLE(p_gpm);
	पूर्ण

	वापस समय_out;
पूर्ण

bool ar9003_mci_start_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 payload[4] = अणु0, 0, 0, 0पूर्ण;

	ar9003_mci_2g5g_changed(ah, IS_CHAN_2GHZ(chan));

	अगर (mci_hw->bt_state != MCI_BT_CAL_START)
		वापस false;

	mci_hw->bt_state = MCI_BT_CAL;

	/*
	 * MCI FIX: disable mci पूर्णांकerrupt here. This is to aव्योम
	 * SW_MSG_DONE or RX_MSG bits to trigger MCI_INT and
	 * lead to mci_पूर्णांकr reentry.
	 */
	ar9003_mci_disable_पूर्णांकerrupt(ah);

	MCI_GPM_SET_CAL_TYPE(payload, MCI_GPM_WLAN_CAL_GRANT);
	ar9003_mci_send_message(ah, MCI_GPM, 0, payload,
				16, true, false);

	/* Wait BT calibration to be completed क्रम 25ms */

	अगर (ar9003_mci_रुको_क्रम_gpm(ah, MCI_GPM_BT_CAL_DONE,
				    0, 25000))
		ath_dbg(common, MCI, "MCI BT_CAL_DONE received\n");
	अन्यथा
		ath_dbg(common, MCI,
			"MCI BT_CAL_DONE not received\n");

	mci_hw->bt_state = MCI_BT_AWAKE;
	/* MCI FIX: enable mci पूर्णांकerrupt here */
	ar9003_mci_enable_पूर्णांकerrupt(ah);

	वापस true;
पूर्ण

पूर्णांक ar9003_mci_end_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			 काष्ठा ath9k_hw_cal_data *caldata)
अणु
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	अगर (!mci_hw->पढ़ोy)
		वापस 0;

	अगर (!IS_CHAN_2GHZ(chan) || (mci_hw->bt_state != MCI_BT_SLEEP))
		जाओ निकास;

	अगर (!ar9003_mci_check_पूर्णांक(ah, AR_MCI_INTERRUPT_RX_MSG_REMOTE_RESET) &&
	    !ar9003_mci_check_पूर्णांक(ah, AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE))
		जाओ निकास;

	/*
	 * BT is sleeping. Check अगर BT wakes up during
	 * WLAN calibration. If BT wakes up during
	 * WLAN calibration, need to go through all
	 * message exchanges again and recal.
	 */
	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
		  (AR_MCI_INTERRUPT_RX_MSG_REMOTE_RESET |
		   AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE));

	ar9003_mci_remote_reset(ah, true);
	ar9003_mci_send_sys_waking(ah, true);
	udelay(1);

	अगर (IS_CHAN_2GHZ(chan))
		ar9003_mci_send_lna_transfer(ah, true);

	mci_hw->bt_state = MCI_BT_AWAKE;

	REG_CLR_BIT(ah, AR_PHY_TIMING4,
		    1 << AR_PHY_TIMING_CONTROL4_DO_GAIN_DC_IQ_CAL_SHIFT);

	अगर (caldata) अणु
		clear_bit(TXIQCAL_DONE, &caldata->cal_flags);
		clear_bit(TXCLCAL_DONE, &caldata->cal_flags);
		clear_bit(RTT_DONE, &caldata->cal_flags);
	पूर्ण

	अगर (!ath9k_hw_init_cal(ah, chan))
		वापस -EIO;

	REG_SET_BIT(ah, AR_PHY_TIMING4,
		    1 << AR_PHY_TIMING_CONTROL4_DO_GAIN_DC_IQ_CAL_SHIFT);

निकास:
	ar9003_mci_enable_पूर्णांकerrupt(ah);
	वापस 0;
पूर्ण

अटल व्योम ar9003_mci_mute_bt(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	/* disable all MCI messages */
	REG_WRITE(ah, AR_MCI_MSG_ATTRIBUTES_TABLE, 0xffff0000);
	REG_WRITE(ah, AR_BTCOEX_WL_WEIGHTS0, 0xffffffff);
	REG_WRITE(ah, AR_BTCOEX_WL_WEIGHTS1, 0xffffffff);
	REG_WRITE(ah, AR_BTCOEX_WL_WEIGHTS2, 0xffffffff);
	REG_WRITE(ah, AR_BTCOEX_WL_WEIGHTS3, 0xffffffff);
	REG_SET_BIT(ah, AR_MCI_TX_CTRL, AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);

	/* रुको pending HW messages to flush out */
	udelay(10);

	/*
	 * Send LNA_TAKE and SYS_SLEEPING when
	 * 1. reset not after resuming from full sleep
	 * 2. beक्रमe reset MCI RX, to quiet BT and aव्योम MCI RX misalignment
	 */
	अगर (MCI_ANT_ARCH_PA_LNA_SHARED(mci)) अणु
		ar9003_mci_send_lna_take(ah, true);
		udelay(5);
	पूर्ण

	ar9003_mci_send_sys_sleeping(ah, true);
पूर्ण

अटल व्योम ar9003_mci_osla_setup(काष्ठा ath_hw *ah, bool enable)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 thresh;

	अगर (!enable) अणु
		REG_CLR_BIT(ah, AR_BTCOEX_CTRL,
			    AR_BTCOEX_CTRL_ONE_STEP_LOOK_AHEAD_EN);
		वापस;
	पूर्ण
	REG_RMW_FIELD(ah, AR_MCI_SCHD_TABLE_2, AR_MCI_SCHD_TABLE_2_HW_BASED, 1);
	REG_RMW_FIELD(ah, AR_MCI_SCHD_TABLE_2,
		      AR_MCI_SCHD_TABLE_2_MEM_BASED, 1);

	अगर (AR_SREV_9565(ah))
		REG_RMW_FIELD(ah, AR_MCI_MISC, AR_MCI_MISC_HW_FIX_EN, 1);

	अगर (!(mci->config & ATH_MCI_CONFIG_DISABLE_AGGR_THRESH)) अणु
		thresh = MS(mci->config, ATH_MCI_CONFIG_AGGR_THRESH);
		REG_RMW_FIELD(ah, AR_BTCOEX_CTRL,
			      AR_BTCOEX_CTRL_AGGR_THRESH, thresh);
		REG_RMW_FIELD(ah, AR_BTCOEX_CTRL,
			      AR_BTCOEX_CTRL_TIME_TO_NEXT_BT_THRESH_EN, 1);
	पूर्ण अन्यथा
		REG_RMW_FIELD(ah, AR_BTCOEX_CTRL,
			      AR_BTCOEX_CTRL_TIME_TO_NEXT_BT_THRESH_EN, 0);

	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL,
		      AR_BTCOEX_CTRL_ONE_STEP_LOOK_AHEAD_EN, 1);
पूर्ण

अटल व्योम ar9003_mci_stat_setup(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	अगर (!AR_SREV_9565(ah))
		वापस;

	अगर (mci->config & ATH_MCI_CONFIG_MCI_STAT_DBG) अणु
		REG_RMW_FIELD(ah, AR_MCI_DBG_CNT_CTRL,
			      AR_MCI_DBG_CNT_CTRL_ENABLE, 1);
		REG_RMW_FIELD(ah, AR_MCI_DBG_CNT_CTRL,
			      AR_MCI_DBG_CNT_CTRL_BT_LINKID,
			      MCI_STAT_ALL_BT_LINKID);
	पूर्ण अन्यथा अणु
		REG_RMW_FIELD(ah, AR_MCI_DBG_CNT_CTRL,
			      AR_MCI_DBG_CNT_CTRL_ENABLE, 0);
	पूर्ण
पूर्ण

अटल व्योम ar9003_mci_set_btcoex_ctrl_9565_1ANT(काष्ठा ath_hw *ah)
अणु
	u32 regval;

	regval = SM(1, AR_BTCOEX_CTRL_AR9462_MODE) |
		 SM(1, AR_BTCOEX_CTRL_WBTIMER_EN) |
		 SM(1, AR_BTCOEX_CTRL_PA_SHARED) |
		 SM(1, AR_BTCOEX_CTRL_LNA_SHARED) |
		 SM(1, AR_BTCOEX_CTRL_NUM_ANTENNAS) |
		 SM(1, AR_BTCOEX_CTRL_RX_CHAIN_MASK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_ACK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_BCN) |
		 SM(0, AR_BTCOEX_CTRL_ONE_STEP_LOOK_AHEAD_EN);

	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2,
		      AR_BTCOEX_CTRL2_TX_CHAIN_MASK, 0x1);
	REG_WRITE(ah, AR_BTCOEX_CTRL, regval);
पूर्ण

अटल व्योम ar9003_mci_set_btcoex_ctrl_9565_2ANT(काष्ठा ath_hw *ah)
अणु
	u32 regval;

	regval = SM(1, AR_BTCOEX_CTRL_AR9462_MODE) |
		 SM(1, AR_BTCOEX_CTRL_WBTIMER_EN) |
		 SM(0, AR_BTCOEX_CTRL_PA_SHARED) |
		 SM(0, AR_BTCOEX_CTRL_LNA_SHARED) |
		 SM(2, AR_BTCOEX_CTRL_NUM_ANTENNAS) |
		 SM(1, AR_BTCOEX_CTRL_RX_CHAIN_MASK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_ACK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_BCN) |
		 SM(0, AR_BTCOEX_CTRL_ONE_STEP_LOOK_AHEAD_EN);

	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2,
		      AR_BTCOEX_CTRL2_TX_CHAIN_MASK, 0x0);
	REG_WRITE(ah, AR_BTCOEX_CTRL, regval);
पूर्ण

अटल व्योम ar9003_mci_set_btcoex_ctrl_9462(काष्ठा ath_hw *ah)
अणु
	u32 regval;

        regval = SM(1, AR_BTCOEX_CTRL_AR9462_MODE) |
		 SM(1, AR_BTCOEX_CTRL_WBTIMER_EN) |
		 SM(1, AR_BTCOEX_CTRL_PA_SHARED) |
		 SM(1, AR_BTCOEX_CTRL_LNA_SHARED) |
		 SM(2, AR_BTCOEX_CTRL_NUM_ANTENNAS) |
		 SM(3, AR_BTCOEX_CTRL_RX_CHAIN_MASK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_ACK) |
		 SM(0, AR_BTCOEX_CTRL_1_CHAIN_BCN) |
		 SM(0, AR_BTCOEX_CTRL_ONE_STEP_LOOK_AHEAD_EN);

	REG_WRITE(ah, AR_BTCOEX_CTRL, regval);
पूर्ण

पूर्णांक ar9003_mci_reset(काष्ठा ath_hw *ah, bool en_पूर्णांक, bool is_2g,
		     bool is_full_sleep)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 regval, i;

	ath_dbg(common, MCI, "MCI Reset (full_sleep = %d, is_2g = %d)\n",
		is_full_sleep, is_2g);

	अगर (REG_READ(ah, AR_BTCOEX_CTRL) == 0xdeadbeef) अणु
		ath_err(common, "BTCOEX control register is dead\n");
		वापस -EINVAL;
	पूर्ण

	/* Program MCI DMA related रेजिस्टरs */
	REG_WRITE(ah, AR_MCI_GPM_0, mci->gpm_addr);
	REG_WRITE(ah, AR_MCI_GPM_1, mci->gpm_len);
	REG_WRITE(ah, AR_MCI_SCHD_TABLE_0, mci->sched_addr);

	/*
	* To aव्योम MCI state machine be affected by incoming remote MCI msgs,
	* MCI mode will be enabled later, right beक्रमe reset the MCI TX and RX.
	*/
	अगर (AR_SREV_9565(ah)) अणु
		u8 ant = MS(mci->config, ATH_MCI_CONFIG_ANT_ARCH);

		अगर (ant == ATH_MCI_ANT_ARCH_1_ANT_PA_LNA_SHARED)
			ar9003_mci_set_btcoex_ctrl_9565_1ANT(ah);
		अन्यथा
			ar9003_mci_set_btcoex_ctrl_9565_2ANT(ah);
	पूर्ण अन्यथा अणु
		ar9003_mci_set_btcoex_ctrl_9462(ah);
	पूर्ण

	अगर (is_2g && !(mci->config & ATH_MCI_CONFIG_DISABLE_OSLA))
		ar9003_mci_osla_setup(ah, true);
	अन्यथा
		ar9003_mci_osla_setup(ah, false);

	REG_SET_BIT(ah, AR_PHY_GLB_CONTROL,
		    AR_BTCOEX_CTRL_SPDT_ENABLE);
	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL3,
		      AR_BTCOEX_CTRL3_CONT_INFO_TIMEOUT, 20);

	REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2, AR_BTCOEX_CTRL2_RX_DEWEIGHT, 0);
	REG_RMW_FIELD(ah, AR_PCU_MISC, AR_PCU_BT_ANT_PREVENT_RX, 0);

	/* Set the समय out to 3.125ms (5 BT slots) */
	REG_RMW_FIELD(ah, AR_BTCOEX_WL_LNA, AR_BTCOEX_WL_LNA_TIMEOUT, 0x3D090);

	/* concurrent tx priority */
	अगर (mci->config & ATH_MCI_CONFIG_CONCUR_TX) अणु
		REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2,
			      AR_BTCOEX_CTRL2_DESC_BASED_TXPWR_ENABLE, 0);
		REG_RMW_FIELD(ah, AR_BTCOEX_CTRL2,
			      AR_BTCOEX_CTRL2_TXPWR_THRESH, 0x7f);
		REG_RMW_FIELD(ah, AR_BTCOEX_CTRL,
			      AR_BTCOEX_CTRL_REDUCE_TXPWR, 0);
		क्रम (i = 0; i < 8; i++)
			REG_WRITE(ah, AR_BTCOEX_MAX_TXPWR(i), 0x7f7f7f7f);
	पूर्ण

	regval = MS(mci->config, ATH_MCI_CONFIG_CLK_DIV);
	REG_RMW_FIELD(ah, AR_MCI_TX_CTRL, AR_MCI_TX_CTRL_CLK_DIV, regval);
	REG_SET_BIT(ah, AR_BTCOEX_CTRL, AR_BTCOEX_CTRL_MCI_MODE_EN);

	/* Resetting the Rx and Tx paths of MCI */
	regval = REG_READ(ah, AR_MCI_COMMAND2);
	regval |= SM(1, AR_MCI_COMMAND2_RESET_TX);
	REG_WRITE(ah, AR_MCI_COMMAND2, regval);

	udelay(1);

	regval &= ~SM(1, AR_MCI_COMMAND2_RESET_TX);
	REG_WRITE(ah, AR_MCI_COMMAND2, regval);

	अगर (is_full_sleep) अणु
		ar9003_mci_mute_bt(ah);
		udelay(100);
	पूर्ण

	/* Check pending GPM msg beक्रमe MCI Reset Rx */
	ar9003_mci_check_gpm_offset(ah);

	regval |= SM(1, AR_MCI_COMMAND2_RESET_RX);
	REG_WRITE(ah, AR_MCI_COMMAND2, regval);
	udelay(1);
	regval &= ~SM(1, AR_MCI_COMMAND2_RESET_RX);
	REG_WRITE(ah, AR_MCI_COMMAND2, regval);

	/* Init GPM offset after MCI Reset Rx */
	ar9003_mci_state(ah, MCI_STATE_INIT_GPM_OFFSET);

	REG_WRITE(ah, AR_MCI_MSG_ATTRIBUTES_TABLE,
		  (SM(0xe801, AR_MCI_MSG_ATTRIBUTES_TABLE_INVALID_HDR) |
		   SM(0x0000, AR_MCI_MSG_ATTRIBUTES_TABLE_CHECKSUM)));

	अगर (MCI_ANT_ARCH_PA_LNA_SHARED(mci))
		REG_CLR_BIT(ah, AR_MCI_TX_CTRL,
			    AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);
	अन्यथा
		REG_SET_BIT(ah, AR_MCI_TX_CTRL,
			    AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);

	ar9003_mci_observation_set_up(ah);

	mci->पढ़ोy = true;
	ar9003_mci_prep_पूर्णांकerface(ah);
	ar9003_mci_stat_setup(ah);

	अगर (en_पूर्णांक)
		ar9003_mci_enable_पूर्णांकerrupt(ah);

	अगर (ath9k_hw_is_aic_enabled(ah))
		ar9003_aic_start_normal(ah);

	वापस 0;
पूर्ण

व्योम ar9003_mci_stop_bt(काष्ठा ath_hw *ah, bool save_fullsleep)
अणु
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	ar9003_mci_disable_पूर्णांकerrupt(ah);

	अगर (mci_hw->पढ़ोy && !save_fullsleep) अणु
		ar9003_mci_mute_bt(ah);
		udelay(20);
		REG_WRITE(ah, AR_BTCOEX_CTRL, 0);
	पूर्ण

	mci_hw->bt_state = MCI_BT_SLEEP;
	mci_hw->पढ़ोy = false;
पूर्ण

अटल व्योम ar9003_mci_send_2g5g_status(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 to_set, to_clear;

	अगर (!mci->update_2g5g || (mci->bt_state == MCI_BT_SLEEP))
		वापस;

	अगर (mci->is_2g) अणु
		to_clear = MCI_2G_FLAGS_CLEAR_MASK;
		to_set = MCI_2G_FLAGS_SET_MASK;
	पूर्ण अन्यथा अणु
		to_clear = MCI_5G_FLAGS_CLEAR_MASK;
		to_set = MCI_5G_FLAGS_SET_MASK;
	पूर्ण

	अगर (to_clear)
		ar9003_mci_send_coex_bt_flags(ah, रुको_करोne,
					      MCI_GPM_COEX_BT_FLAGS_CLEAR,
					      to_clear);
	अगर (to_set)
		ar9003_mci_send_coex_bt_flags(ah, रुको_करोne,
					      MCI_GPM_COEX_BT_FLAGS_SET,
					      to_set);
पूर्ण

अटल व्योम ar9003_mci_queue_unsent_gpm(काष्ठा ath_hw *ah, u8 header,
					u32 *payload, bool queue)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u8 type, opcode;

	/* check अगर the message is to be queued */
	अगर (header != MCI_GPM)
		वापस;

	type = MCI_GPM_TYPE(payload);
	opcode = MCI_GPM_OPCODE(payload);

	अगर (type != MCI_GPM_COEX_AGENT)
		वापस;

	चयन (opcode) अणु
	हाल MCI_GPM_COEX_BT_UPDATE_FLAGS:
		अगर (*(((u8 *)payload) + MCI_GPM_COEX_B_BT_FLAGS_OP) ==
		    MCI_GPM_COEX_BT_FLAGS_READ)
			अवरोध;

		mci->update_2g5g = queue;

		अवरोध;
	हाल MCI_GPM_COEX_WLAN_CHANNELS:
		mci->wlan_channels_update = queue;
		अवरोध;
	हाल MCI_GPM_COEX_HALT_BT_GPM:
		अगर (*(((u8 *)payload) + MCI_GPM_COEX_B_HALT_STATE) ==
		    MCI_GPM_COEX_BT_GPM_UNHALT) अणु
			mci->unhalt_bt_gpm = queue;

			अगर (!queue)
				mci->halted_bt_gpm = false;
		पूर्ण

		अगर (*(((u8 *)payload) + MCI_GPM_COEX_B_HALT_STATE) ==
				MCI_GPM_COEX_BT_GPM_HALT) अणु

			mci->halted_bt_gpm = !queue;
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम ar9003_mci_2g5g_चयन(काष्ठा ath_hw *ah, bool क्रमce)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	अगर (!mci->update_2g5g && !क्रमce)
		वापस;

	अगर (mci->is_2g) अणु
		ar9003_mci_send_2g5g_status(ah, true);
		ar9003_mci_send_lna_transfer(ah, true);
		udelay(5);

		REG_CLR_BIT(ah, AR_MCI_TX_CTRL,
			    AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);
		REG_CLR_BIT(ah, AR_PHY_GLB_CONTROL,
			    AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL);

		अगर (!(mci->config & ATH_MCI_CONFIG_DISABLE_OSLA))
			ar9003_mci_osla_setup(ah, true);

		अगर (AR_SREV_9462(ah))
			REG_WRITE(ah, AR_SELFGEN_MASK, 0x02);
	पूर्ण अन्यथा अणु
		ar9003_mci_send_lna_take(ah, true);
		udelay(5);

		REG_SET_BIT(ah, AR_MCI_TX_CTRL,
			    AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);
		REG_SET_BIT(ah, AR_PHY_GLB_CONTROL,
			    AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL);

		ar9003_mci_osla_setup(ah, false);
		ar9003_mci_send_2g5g_status(ah, true);
	पूर्ण
पूर्ण

bool ar9003_mci_send_message(काष्ठा ath_hw *ah, u8 header, u32 flag,
			     u32 *payload, u8 len, bool रुको_करोne,
			     bool check_bt)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	bool msg_sent = false;
	u32 regval;
	u32 saved_mci_पूर्णांक_en;
	पूर्णांक i;

	saved_mci_पूर्णांक_en = REG_READ(ah, AR_MCI_INTERRUPT_EN);
	regval = REG_READ(ah, AR_BTCOEX_CTRL);

	अगर ((regval == 0xdeadbeef) || !(regval & AR_BTCOEX_CTRL_MCI_MODE_EN)) अणु
		ath_dbg(common, MCI,
			"MCI Not sending 0x%x. MCI is not enabled. full_sleep = %d\n",
			header, (ah->घातer_mode == ATH9K_PM_FULL_SLEEP) ? 1 : 0);
		ar9003_mci_queue_unsent_gpm(ah, header, payload, true);
		वापस false;
	पूर्ण अन्यथा अगर (check_bt && (mci->bt_state == MCI_BT_SLEEP)) अणु
		ath_dbg(common, MCI,
			"MCI Don't send message 0x%x. BT is in sleep state\n",
			header);
		ar9003_mci_queue_unsent_gpm(ah, header, payload, true);
		वापस false;
	पूर्ण

	अगर (रुको_करोne)
		REG_WRITE(ah, AR_MCI_INTERRUPT_EN, 0);

	/* Need to clear SW_MSG_DONE raw bit beक्रमe रुको */

	REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
		  (AR_MCI_INTERRUPT_SW_MSG_DONE |
		   AR_MCI_INTERRUPT_MSG_FAIL_MASK));

	अगर (payload) अणु
		क्रम (i = 0; (i * 4) < len; i++)
			REG_WRITE(ah, (AR_MCI_TX_PAYLOAD0 + i * 4),
				  *(payload + i));
	पूर्ण

	REG_WRITE(ah, AR_MCI_COMMAND0,
		  (SM((flag & MCI_FLAG_DISABLE_TIMESTAMP),
		      AR_MCI_COMMAND0_DISABLE_TIMESTAMP) |
		   SM(len, AR_MCI_COMMAND0_LEN) |
		   SM(header, AR_MCI_COMMAND0_HEADER)));

	अगर (रुको_करोne &&
	    !(ar9003_mci_रुको_क्रम_पूर्णांकerrupt(ah, AR_MCI_INTERRUPT_RAW,
					    AR_MCI_INTERRUPT_SW_MSG_DONE, 500)))
		ar9003_mci_queue_unsent_gpm(ah, header, payload, true);
	अन्यथा अणु
		ar9003_mci_queue_unsent_gpm(ah, header, payload, false);
		msg_sent = true;
	पूर्ण

	अगर (रुको_करोne)
		REG_WRITE(ah, AR_MCI_INTERRUPT_EN, saved_mci_पूर्णांक_en);

	वापस msg_sent;
पूर्ण
EXPORT_SYMBOL(ar9003_mci_send_message);

व्योम ar9003_mci_init_cal_req(काष्ठा ath_hw *ah, bool *is_reusable)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 pld[4] = अणु0, 0, 0, 0पूर्ण;

	अगर ((mci_hw->bt_state != MCI_BT_AWAKE) ||
	    (mci_hw->config & ATH_MCI_CONFIG_DISABLE_MCI_CAL))
		वापस;

	MCI_GPM_SET_CAL_TYPE(pld, MCI_GPM_WLAN_CAL_REQ);
	pld[MCI_GPM_WLAN_CAL_W_SEQUENCE] = mci_hw->wlan_cal_seq++;

	ar9003_mci_send_message(ah, MCI_GPM, 0, pld, 16, true, false);

	अगर (ar9003_mci_रुको_क्रम_gpm(ah, MCI_GPM_BT_CAL_GRANT, 0, 50000)) अणु
		ath_dbg(common, MCI, "MCI BT_CAL_GRANT received\n");
	पूर्ण अन्यथा अणु
		*is_reusable = false;
		ath_dbg(common, MCI, "MCI BT_CAL_GRANT not received\n");
	पूर्ण
पूर्ण

व्योम ar9003_mci_init_cal_करोne(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 pld[4] = अणु0, 0, 0, 0पूर्ण;

	अगर ((mci_hw->bt_state != MCI_BT_AWAKE) ||
	    (mci_hw->config & ATH_MCI_CONFIG_DISABLE_MCI_CAL))
		वापस;

	MCI_GPM_SET_CAL_TYPE(pld, MCI_GPM_WLAN_CAL_DONE);
	pld[MCI_GPM_WLAN_CAL_W_SEQUENCE] = mci_hw->wlan_cal_करोne++;
	ar9003_mci_send_message(ah, MCI_GPM, 0, pld, 16, true, false);
पूर्ण

पूर्णांक ar9003_mci_setup(काष्ठा ath_hw *ah, u32 gpm_addr, व्योम *gpm_buf,
		     u16 len, u32 sched_addr)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->gpm_addr = gpm_addr;
	mci->gpm_buf = gpm_buf;
	mci->gpm_len = len;
	mci->sched_addr = sched_addr;

	वापस ar9003_mci_reset(ah, true, true, true);
पूर्ण
EXPORT_SYMBOL(ar9003_mci_setup);

व्योम ar9003_mci_cleanup(काष्ठा ath_hw *ah)
अणु
	/* Turn off MCI and Jupiter mode. */
	REG_WRITE(ah, AR_BTCOEX_CTRL, 0x00);
	ar9003_mci_disable_पूर्णांकerrupt(ah);
पूर्ण
EXPORT_SYMBOL(ar9003_mci_cleanup);

u32 ar9003_mci_state(काष्ठा ath_hw *ah, u32 state_type)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 value = 0, tsf;
	u8 query_type;

	चयन (state_type) अणु
	हाल MCI_STATE_ENABLE:
		अगर (mci->पढ़ोy) अणु
			value = REG_READ(ah, AR_BTCOEX_CTRL);

			अगर ((value == 0xdeadbeef) || (value == 0xffffffff))
				value = 0;
		पूर्ण
		value &= AR_BTCOEX_CTRL_MCI_MODE_EN;
		अवरोध;
	हाल MCI_STATE_INIT_GPM_OFFSET:
		value = MS(REG_READ(ah, AR_MCI_GPM_1), AR_MCI_GPM_WRITE_PTR);

		अगर (value < mci->gpm_len)
			mci->gpm_idx = value;
		अन्यथा
			mci->gpm_idx = 0;
		अवरोध;
	हाल MCI_STATE_LAST_SCHD_MSG_OFFSET:
		value = MS(REG_READ(ah, AR_MCI_RX_STATUS),
				    AR_MCI_RX_LAST_SCHD_MSG_INDEX);
		/* Make it in bytes */
		value <<= 4;
		अवरोध;
	हाल MCI_STATE_REMOTE_SLEEP:
		value = MS(REG_READ(ah, AR_MCI_RX_STATUS),
			   AR_MCI_RX_REMOTE_SLEEP) ?
			MCI_BT_SLEEP : MCI_BT_AWAKE;
		अवरोध;
	हाल MCI_STATE_SET_BT_AWAKE:
		mci->bt_state = MCI_BT_AWAKE;
		ar9003_mci_send_coex_version_query(ah, true);
		ar9003_mci_send_coex_wlan_channels(ah, true);

		अगर (mci->unhalt_bt_gpm)
			ar9003_mci_send_coex_halt_bt_gpm(ah, false, true);

		ar9003_mci_2g5g_चयन(ah, false);
		अवरोध;
	हाल MCI_STATE_RESET_REQ_WAKE:
		ar9003_mci_reset_req_wakeup(ah);
		mci->update_2g5g = true;

		अगर (mci->config & ATH_MCI_CONFIG_MCI_OBS_MASK) अणु
			/* Check अगर we still have control of the GPIOs */
			अगर ((REG_READ(ah, AR_GLB_GPIO_CONTROL) &
			     ATH_MCI_CONFIG_MCI_OBS_GPIO) !=
			    ATH_MCI_CONFIG_MCI_OBS_GPIO) अणु
				ar9003_mci_observation_set_up(ah);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल MCI_STATE_SEND_WLAN_COEX_VERSION:
		ar9003_mci_send_coex_version_response(ah, true);
		अवरोध;
	हाल MCI_STATE_SEND_VERSION_QUERY:
		ar9003_mci_send_coex_version_query(ah, true);
		अवरोध;
	हाल MCI_STATE_SEND_STATUS_QUERY:
		query_type = MCI_GPM_COEX_QUERY_BT_TOPOLOGY;
		ar9003_mci_send_coex_bt_status_query(ah, true, query_type);
		अवरोध;
	हाल MCI_STATE_RECOVER_RX:
		tsf = ath9k_hw_gettsf32(ah);
		अगर ((tsf - mci->last_recovery) <= MCI_RECOVERY_DUR_TSF) अणु
			ath_dbg(ath9k_hw_common(ah), MCI,
				"(MCI) ignore Rx recovery\n");
			अवरोध;
		पूर्ण
		ath_dbg(ath9k_hw_common(ah), MCI, "(MCI) RECOVER RX\n");
		mci->last_recovery = tsf;
		ar9003_mci_prep_पूर्णांकerface(ah);
		mci->query_bt = true;
		mci->need_flush_btinfo = true;
		ar9003_mci_send_coex_wlan_channels(ah, true);
		ar9003_mci_2g5g_चयन(ah, false);
		अवरोध;
	हाल MCI_STATE_NEED_FTP_STOMP:
		value = !(mci->config & ATH_MCI_CONFIG_DISABLE_FTP_STOMP);
		अवरोध;
	हाल MCI_STATE_NEED_FLUSH_BT_INFO:
		value = (!mci->unhalt_bt_gpm && mci->need_flush_btinfo) ? 1 : 0;
		mci->need_flush_btinfo = false;
		अवरोध;
	हाल MCI_STATE_AIC_CAL:
		अगर (ath9k_hw_is_aic_enabled(ah))
			value = ar9003_aic_calibration(ah);
		अवरोध;
	हाल MCI_STATE_AIC_START:
		अगर (ath9k_hw_is_aic_enabled(ah))
			ar9003_aic_start_normal(ah);
		अवरोध;
	हाल MCI_STATE_AIC_CAL_RESET:
		अगर (ath9k_hw_is_aic_enabled(ah))
			value = ar9003_aic_cal_reset(ah);
		अवरोध;
	हाल MCI_STATE_AIC_CAL_SINGLE:
		अगर (ath9k_hw_is_aic_enabled(ah))
			value = ar9003_aic_calibration_single(ah);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस value;
पूर्ण
EXPORT_SYMBOL(ar9003_mci_state);

व्योम ar9003_mci_bt_gain_ctrl(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	ath_dbg(common, MCI, "Give LNA and SPDT control to BT\n");

	ar9003_mci_send_lna_take(ah, true);
	udelay(50);

	REG_SET_BIT(ah, AR_PHY_GLB_CONTROL, AR_BTCOEX_CTRL_BT_OWN_SPDT_CTRL);
	mci->is_2g = false;
	mci->update_2g5g = true;
	ar9003_mci_send_2g5g_status(ah, true);

	/* Force another 2g5g update at next scanning */
	mci->update_2g5g = true;
पूर्ण

व्योम ar9003_mci_set_घातer_awake(काष्ठा ath_hw *ah)
अणु
	u32 btcoex_ctrl2, diag_sw;
	पूर्णांक i;
	u8 lna_ctrl, bt_sleep;

	क्रम (i = 0; i < AH_WAIT_TIMEOUT; i++) अणु
		btcoex_ctrl2 = REG_READ(ah, AR_BTCOEX_CTRL2);
		अगर (btcoex_ctrl2 != 0xdeadbeef)
			अवरोध;
		udelay(AH_TIME_QUANTUM);
	पूर्ण
	REG_WRITE(ah, AR_BTCOEX_CTRL2, (btcoex_ctrl2 | BIT(23)));

	क्रम (i = 0; i < AH_WAIT_TIMEOUT; i++) अणु
		diag_sw = REG_READ(ah, AR_DIAG_SW);
		अगर (diag_sw != 0xdeadbeef)
			अवरोध;
		udelay(AH_TIME_QUANTUM);
	पूर्ण
	REG_WRITE(ah, AR_DIAG_SW, (diag_sw | BIT(27) | BIT(19) | BIT(18)));
	lna_ctrl = REG_READ(ah, AR_OBS_BUS_CTRL) & 0x3;
	bt_sleep = MS(REG_READ(ah, AR_MCI_RX_STATUS), AR_MCI_RX_REMOTE_SLEEP);

	REG_WRITE(ah, AR_BTCOEX_CTRL2, btcoex_ctrl2);
	REG_WRITE(ah, AR_DIAG_SW, diag_sw);

	अगर (bt_sleep && (lna_ctrl == 2)) अणु
		REG_SET_BIT(ah, AR_BTCOEX_RC, 0x1);
		REG_CLR_BIT(ah, AR_BTCOEX_RC, 0x1);
		udelay(50);
	पूर्ण
पूर्ण

व्योम ar9003_mci_check_gpm_offset(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 offset;

	/*
	 * This should only be called beक्रमe "MAC Warm Reset" or "MCI Reset Rx".
	 */
	offset = MS(REG_READ(ah, AR_MCI_GPM_1), AR_MCI_GPM_WRITE_PTR);
	अगर (mci->gpm_idx == offset)
		वापस;
	ath_dbg(common, MCI, "GPM cached write pointer mismatch %d %d\n",
		mci->gpm_idx, offset);
	mci->query_bt = true;
	mci->need_flush_btinfo = true;
	mci->gpm_idx = 0;
पूर्ण

u32 ar9003_mci_get_next_gpm_offset(काष्ठा ath_hw *ah, u32 *more)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 offset, more_gpm = 0, gpm_ptr;

	/*
	 * This could be useful to aव्योम new GPM message पूर्णांकerrupt which
	 * may lead to spurious पूर्णांकerrupt after घातer sleep, or multiple
	 * entry of ath_mci_पूर्णांकr().
	 * Adding empty GPM check by वापसing HAL_MCI_GPM_INVALID can
	 * alleviate this effect, but clearing GPM RX पूर्णांकerrupt bit is
	 * safe, because whether this is called from hw or driver code
	 * there must be an पूर्णांकerrupt bit set/triggered initially
	 */
	REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_RAW,
			AR_MCI_INTERRUPT_RX_MSG_GPM);

	gpm_ptr = MS(REG_READ(ah, AR_MCI_GPM_1), AR_MCI_GPM_WRITE_PTR);
	offset = gpm_ptr;

	अगर (!offset)
		offset = mci->gpm_len - 1;
	अन्यथा अगर (offset >= mci->gpm_len) अणु
		अगर (offset != 0xFFFF)
			offset = 0;
	पूर्ण अन्यथा अणु
		offset--;
	पूर्ण

	अगर ((offset == 0xFFFF) || (gpm_ptr == mci->gpm_idx)) अणु
		offset = MCI_GPM_INVALID;
		more_gpm = MCI_GPM_NOMORE;
		जाओ out;
	पूर्ण
	क्रम (;;) अणु
		u32 temp_index;

		/* skip reserved GPM अगर any */

		अगर (offset != mci->gpm_idx)
			more_gpm = MCI_GPM_MORE;
		अन्यथा
			more_gpm = MCI_GPM_NOMORE;

		temp_index = mci->gpm_idx;

		अगर (temp_index >= mci->gpm_len)
			temp_index = 0;

		mci->gpm_idx++;

		अगर (mci->gpm_idx >= mci->gpm_len)
			mci->gpm_idx = 0;

		अगर (ar9003_mci_is_gpm_valid(ah, temp_index)) अणु
			offset = temp_index;
			अवरोध;
		पूर्ण

		अगर (more_gpm == MCI_GPM_NOMORE) अणु
			offset = MCI_GPM_INVALID;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (offset != MCI_GPM_INVALID)
		offset <<= 4;
out:
	अगर (more)
		*more = more_gpm;

	वापस offset;
पूर्ण
EXPORT_SYMBOL(ar9003_mci_get_next_gpm_offset);

व्योम ar9003_mci_set_bt_version(काष्ठा ath_hw *ah, u8 major, u8 minor)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->bt_ver_major = major;
	mci->bt_ver_minor = minor;
	mci->bt_version_known = true;
	ath_dbg(ath9k_hw_common(ah), MCI, "MCI BT version set: %d.%d\n",
		mci->bt_ver_major, mci->bt_ver_minor);
पूर्ण
EXPORT_SYMBOL(ar9003_mci_set_bt_version);

व्योम ar9003_mci_send_wlan_channels(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->wlan_channels_update = true;
	ar9003_mci_send_coex_wlan_channels(ah, true);
पूर्ण
EXPORT_SYMBOL(ar9003_mci_send_wlan_channels);

u16 ar9003_mci_get_max_txघातer(काष्ठा ath_hw *ah, u8 ctlmode)
अणु
	अगर (!ah->btcoex_hw.mci.concur_tx)
		जाओ out;

	अगर (ctlmode == CTL_2GHT20)
		वापस ATH_BTCOEX_HT20_MAX_TXPOWER;
	अन्यथा अगर (ctlmode == CTL_2GHT40)
		वापस ATH_BTCOEX_HT40_MAX_TXPOWER;

out:
	वापस -1;
पूर्ण
