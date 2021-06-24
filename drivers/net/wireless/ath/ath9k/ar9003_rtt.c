<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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

#समावेश "hw.h"
#समावेश "hw-ops.h"
#समावेश "ar9003_phy.h"
#समावेश "ar9003_rtt.h"

#घोषणा RTT_RESTORE_TIMEOUT          1000
#घोषणा RTT_ACCESS_TIMEOUT           100
#घोषणा RTT_BAD_VALUE                0x0bad0bad

/*
 * RTT (Radio Retention Table) hardware implementation inक्रमmation
 *
 * There is an पूर्णांकernal table (i.e. the rtt) क्रम each chain (or bank).
 * Each table contains 6 entries and each entry is corresponding to
 * a specअगरic calibration parameter as depicted below.
 *  0~2 - DC offset DAC calibration: loop, low, high (offsetI/Q_...)
 *  3   - Filter cal (filterfc)
 *  4   - RX gain settings
 *  5   - Peak detector offset calibration (agc_caldac)
 */

व्योम ar9003_hw_rtt_enable(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_PHY_RTT_CTRL, 1);
पूर्ण

व्योम ar9003_hw_rtt_disable(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_PHY_RTT_CTRL, 0);
पूर्ण

व्योम ar9003_hw_rtt_set_mask(काष्ठा ath_hw *ah, u32 rtt_mask)
अणु
	REG_RMW_FIELD(ah, AR_PHY_RTT_CTRL,
		      AR_PHY_RTT_CTRL_RESTORE_MASK, rtt_mask);
पूर्ण

bool ar9003_hw_rtt_क्रमce_restore(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_रुको(ah, AR_PHY_RTT_CTRL,
			   AR_PHY_RTT_CTRL_FORCE_RADIO_RESTORE,
			   0, RTT_RESTORE_TIMEOUT))
		वापस false;

	REG_RMW_FIELD(ah, AR_PHY_RTT_CTRL,
		      AR_PHY_RTT_CTRL_FORCE_RADIO_RESTORE, 1);

	अगर (!ath9k_hw_रुको(ah, AR_PHY_RTT_CTRL,
			   AR_PHY_RTT_CTRL_FORCE_RADIO_RESTORE,
			   0, RTT_RESTORE_TIMEOUT))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम ar9003_hw_rtt_load_hist_entry(काष्ठा ath_hw *ah, u8 chain,
					  u32 index, u32 data28)
अणु
	u32 val;

	val = SM(data28, AR_PHY_RTT_SW_RTT_TABLE_DATA);
	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_1_B(chain), val);

	val = SM(0, AR_PHY_RTT_SW_RTT_TABLE_ACCESS) |
	      SM(1, AR_PHY_RTT_SW_RTT_TABLE_WRITE) |
	      SM(index, AR_PHY_RTT_SW_RTT_TABLE_ADDR);
	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain), val);
	udelay(1);

	val |= SM(1, AR_PHY_RTT_SW_RTT_TABLE_ACCESS);
	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain), val);
	udelay(1);

	अगर (!ath9k_hw_रुको(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain),
			   AR_PHY_RTT_SW_RTT_TABLE_ACCESS, 0,
			   RTT_ACCESS_TIMEOUT))
		वापस;

	val &= ~SM(1, AR_PHY_RTT_SW_RTT_TABLE_WRITE);
	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain), val);
	udelay(1);

	ath9k_hw_रुको(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain),
		      AR_PHY_RTT_SW_RTT_TABLE_ACCESS, 0,
		      RTT_ACCESS_TIMEOUT);
पूर्ण

व्योम ar9003_hw_rtt_load_hist(काष्ठा ath_hw *ah)
अणु
	पूर्णांक chain, i;

	क्रम (chain = 0; chain < AR9300_MAX_CHAINS; chain++) अणु
		अगर (!(ah->caps.rx_chainmask & (1 << chain)))
			जारी;
		क्रम (i = 0; i < MAX_RTT_TABLE_ENTRY; i++) अणु
			ar9003_hw_rtt_load_hist_entry(ah, chain, i,
					      ah->caldata->rtt_table[chain][i]);
			ath_dbg(ath9k_hw_common(ah), CALIBRATE,
				"Load RTT value at idx %d, chain %d: 0x%x\n",
				i, chain, ah->caldata->rtt_table[chain][i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_patch_rtt(काष्ठा ath_hw *ah, पूर्णांक index, पूर्णांक chain)
अणु
	पूर्णांक agc, caldac;

	अगर (!test_bit(SW_PKDET_DONE, &ah->caldata->cal_flags))
		वापस;

	अगर ((index != 5) || (chain >= 2))
		वापस;

	agc = REG_READ_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			     AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE);
	अगर (!agc)
		वापस;

	caldac = ah->caldata->caldac[chain];
	ah->caldata->rtt_table[chain][index] &= 0xFFFF05FF;
	caldac = (caldac & 0x20) | ((caldac & 0x1F) << 7);
	ah->caldata->rtt_table[chain][index] |= (caldac << 4);
पूर्ण

अटल पूर्णांक ar9003_hw_rtt_fill_hist_entry(काष्ठा ath_hw *ah, u8 chain, u32 index)
अणु
	u32 val;

	val = SM(0, AR_PHY_RTT_SW_RTT_TABLE_ACCESS) |
	      SM(0, AR_PHY_RTT_SW_RTT_TABLE_WRITE) |
	      SM(index, AR_PHY_RTT_SW_RTT_TABLE_ADDR);

	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain), val);
	udelay(1);

	val |= SM(1, AR_PHY_RTT_SW_RTT_TABLE_ACCESS);
	REG_WRITE(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain), val);
	udelay(1);

	अगर (!ath9k_hw_रुको(ah, AR_PHY_RTT_TABLE_SW_INTF_B(chain),
			   AR_PHY_RTT_SW_RTT_TABLE_ACCESS, 0,
			   RTT_ACCESS_TIMEOUT))
		वापस RTT_BAD_VALUE;

	val = MS(REG_READ(ah, AR_PHY_RTT_TABLE_SW_INTF_1_B(chain)),
		 AR_PHY_RTT_SW_RTT_TABLE_DATA);


	वापस val;
पूर्ण

व्योम ar9003_hw_rtt_fill_hist(काष्ठा ath_hw *ah)
अणु
	पूर्णांक chain, i;

	क्रम (chain = 0; chain < AR9300_MAX_CHAINS; chain++) अणु
		अगर (!(ah->caps.rx_chainmask & (1 << chain)))
			जारी;
		क्रम (i = 0; i < MAX_RTT_TABLE_ENTRY; i++) अणु
			ah->caldata->rtt_table[chain][i] =
				ar9003_hw_rtt_fill_hist_entry(ah, chain, i);

			ar9003_hw_patch_rtt(ah, i, chain);

			ath_dbg(ath9k_hw_common(ah), CALIBRATE,
				"RTT value at idx %d, chain %d is: 0x%x\n",
				i, chain, ah->caldata->rtt_table[chain][i]);
		पूर्ण
	पूर्ण

	set_bit(RTT_DONE, &ah->caldata->cal_flags);
पूर्ण

व्योम ar9003_hw_rtt_clear_hist(काष्ठा ath_hw *ah)
अणु
	पूर्णांक chain, i;

	क्रम (chain = 0; chain < AR9300_MAX_CHAINS; chain++) अणु
		अगर (!(ah->caps.rx_chainmask & (1 << chain)))
			जारी;
		क्रम (i = 0; i < MAX_RTT_TABLE_ENTRY; i++)
			ar9003_hw_rtt_load_hist_entry(ah, chain, i, 0);
	पूर्ण

	अगर (ah->caldata)
		clear_bit(RTT_DONE, &ah->caldata->cal_flags);
पूर्ण

bool ar9003_hw_rtt_restore(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	bool restore;

	अगर (!ah->caldata)
		वापस false;

	अगर (test_bit(SW_PKDET_DONE, &ah->caldata->cal_flags)) अणु
		अगर (IS_CHAN_2GHZ(chan))अणु
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(0),
				      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR,
				      ah->caldata->caldac[0]);
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(1),
				      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR,
				      ah->caldata->caldac[1]);
		पूर्ण अन्यथा अणु
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(0),
				      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR,
				      ah->caldata->caldac[0]);
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(1),
				      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR,
				      ah->caldata->caldac[1]);
		पूर्ण
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(1),
			      AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE, 0x1);
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(0),
			      AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE, 0x1);
	पूर्ण

	अगर (!test_bit(RTT_DONE, &ah->caldata->cal_flags))
		वापस false;

	ar9003_hw_rtt_enable(ah);

	अगर (test_bit(SW_PKDET_DONE, &ah->caldata->cal_flags))
		ar9003_hw_rtt_set_mask(ah, 0x30);
	अन्यथा
		ar9003_hw_rtt_set_mask(ah, 0x10);

	अगर (!ath9k_hw_rfbus_req(ah)) अणु
		ath_err(ath9k_hw_common(ah), "Could not stop baseband\n");
		restore = false;
		जाओ fail;
	पूर्ण

	ar9003_hw_rtt_load_hist(ah);
	restore = ar9003_hw_rtt_क्रमce_restore(ah);

fail:
	ath9k_hw_rfbus_करोne(ah);
	ar9003_hw_rtt_disable(ah);
	वापस restore;
पूर्ण
