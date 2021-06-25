<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
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

#समावेश <net/mac80211.h>

#समावेश "types.h"
#समावेश "d11.h"
#समावेश "rate.h"
#समावेश "phy/phy_hal.h"
#समावेश "channel.h"
#समावेश "main.h"
#समावेश "stf.h"
#समावेश "debug.h"

#घोषणा MIN_SPATIAL_EXPANSION	0
#घोषणा MAX_SPATIAL_EXPANSION	1

#घोषणा BRCMS_STF_SS_STBC_RX(wlc) (BRCMS_ISNPHY(wlc->band) && \
	NREV_GT(wlc->band->phyrev, 3) && NREV_LE(wlc->band->phyrev, 6))

#घोषणा NSTS_1	1
#घोषणा NSTS_2	2
#घोषणा NSTS_3	3
#घोषणा NSTS_4	4

अटल स्थिर u8 txcore_शेष[5] = अणु
	(0),			/* biपंचांगap of the core enabled */
	(0x01),			/* For Nsts = 1, enable core 1 */
	(0x03),			/* For Nsts = 2, enable core 1 & 2 */
	(0x07),			/* For Nsts = 3, enable core 1, 2 & 3 */
	(0x0f)			/* For Nsts = 4, enable all cores */
पूर्ण;

अटल व्योम brcms_c_stf_stbc_rx_ht_update(काष्ठा brcms_c_info *wlc, पूर्णांक val)
अणु
	/* MIMOPHYs rev3-6 cannot receive STBC with only one rx core active */
	अगर (BRCMS_STF_SS_STBC_RX(wlc)) अणु
		अगर ((wlc->stf->rxstreams == 1) && (val != HT_CAP_RX_STBC_NO))
			वापस;
	पूर्ण

	अगर (wlc->pub->up) अणु
		brcms_c_update_beacon(wlc);
		brcms_c_update_probe_resp(wlc, true);
	पूर्ण
पूर्ण

/*
 * every WLC_TEMPSENSE_PERIOD seconds temperature check to decide whether to
 * turn on/off txchain.
 */
व्योम brcms_c_tempsense_upd(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_phy_pub *pi = wlc->band->pi;
	uपूर्णांक active_chains, txchain;

	/* Check अगर the chip is too hot. Disable one Tx chain, अगर it is */
	/* high 4 bits are क्रम Rx chain, low 4 bits are  क्रम Tx chain */
	active_chains = wlc_phy_stf_chain_active_get(pi);
	txchain = active_chains & 0xf;

	अगर (wlc->stf->txchain == wlc->stf->hw_txchain) अणु
		अगर (txchain && (txchain < wlc->stf->hw_txchain))
			/* turn off 1 tx chain */
			brcms_c_stf_txchain_set(wlc, txchain, true);
	पूर्ण अन्यथा अगर (wlc->stf->txchain < wlc->stf->hw_txchain) अणु
		अगर (txchain == wlc->stf->hw_txchain)
			/* turn back on txchain */
			brcms_c_stf_txchain_set(wlc, txchain, true);
	पूर्ण
पूर्ण

व्योम
brcms_c_stf_ss_algo_channel_get(काष्ठा brcms_c_info *wlc, u16 *ss_algo_channel,
			    u16 chanspec)
अणु
	काष्ठा tx_घातer घातer = अणु पूर्ण;
	u8 siso_mcs_id, cdd_mcs_id, stbc_mcs_id;

	/* Clear previous settings */
	*ss_algo_channel = 0;

	अगर (!wlc->pub->up) अणु
		*ss_algo_channel = (u16) -1;
		वापस;
	पूर्ण

	wlc_phy_txघातer_get_current(wlc->band->pi, &घातer,
				    CHSPEC_CHANNEL(chanspec));

	siso_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WL_TX_POWER_MCS40_SISO_FIRST : WL_TX_POWER_MCS20_SISO_FIRST;
	cdd_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WL_TX_POWER_MCS40_CDD_FIRST : WL_TX_POWER_MCS20_CDD_FIRST;
	stbc_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WL_TX_POWER_MCS40_STBC_FIRST : WL_TX_POWER_MCS20_STBC_FIRST;

	/* criteria to choose stf mode */

	/*
	 * the "+3dbm (12 0.25db units)" is to account क्रम the fact that with
	 * CDD, tx occurs on both chains
	 */
	अगर (घातer.target[siso_mcs_id] > (घातer.target[cdd_mcs_id] + 12))
		setbit(ss_algo_channel, PHY_TXC1_MODE_SISO);
	अन्यथा
		setbit(ss_algo_channel, PHY_TXC1_MODE_CDD);

	/*
	 * STBC is ORed पूर्णांकo to algo channel as STBC requires per-packet SCB
	 * capability check so cannot be शेष mode of operation. One of
	 * SISO, CDD have to be set
	 */
	अगर (घातer.target[siso_mcs_id] <= (घातer.target[stbc_mcs_id] + 12))
		setbit(ss_algo_channel, PHY_TXC1_MODE_STBC);
पूर्ण

अटल bool brcms_c_stf_stbc_tx_set(काष्ठा brcms_c_info *wlc, s32 पूर्णांक_val)
अणु
	अगर ((पूर्णांक_val != AUTO) && (पूर्णांक_val != OFF) && (पूर्णांक_val != ON))
		वापस false;

	अगर ((पूर्णांक_val == ON) && (wlc->stf->txstreams == 1))
		वापस false;

	wlc->bandstate[BAND_2G_INDEX]->band_stf_stbc_tx = (s8) पूर्णांक_val;
	wlc->bandstate[BAND_5G_INDEX]->band_stf_stbc_tx = (s8) पूर्णांक_val;

	वापस true;
पूर्ण

bool brcms_c_stf_stbc_rx_set(काष्ठा brcms_c_info *wlc, s32 पूर्णांक_val)
अणु
	अगर ((पूर्णांक_val != HT_CAP_RX_STBC_NO)
	    && (पूर्णांक_val != HT_CAP_RX_STBC_ONE_STREAM))
		वापस false;

	अगर (BRCMS_STF_SS_STBC_RX(wlc)) अणु
		अगर ((पूर्णांक_val != HT_CAP_RX_STBC_NO)
		    && (wlc->stf->rxstreams == 1))
			वापस false;
	पूर्ण

	brcms_c_stf_stbc_rx_ht_update(wlc, पूर्णांक_val);
	वापस true;
पूर्ण

अटल पूर्णांक brcms_c_stf_txcore_set(काष्ठा brcms_c_info *wlc, u8 Nsts,
				  u8 core_mask)
अणु
	brcms_dbg_ht(wlc->hw->d11core, "wl%d: Nsts %d core_mask %x\n",
		     wlc->pub->unit, Nsts, core_mask);

	अगर (hweight8(core_mask) > wlc->stf->txstreams)
		core_mask = 0;

	अगर ((hweight8(core_mask) == wlc->stf->txstreams) &&
	    ((core_mask & ~wlc->stf->txchain)
	     || !(core_mask & wlc->stf->txchain)))
		core_mask = wlc->stf->txchain;

	wlc->stf->txcore[Nsts] = core_mask;
	/* Nsts = 1..4, txcore index = 1..4 */
	अगर (Nsts == 1) अणु
		/* Needs to update beacon and ucode generated response
		 * frames when 1 stream core map changed
		 */
		wlc->stf->phytxant = core_mask << PHY_TXC_ANT_SHIFT;
		brcms_b_txant_set(wlc->hw, wlc->stf->phytxant);
		अगर (wlc->clk) अणु
			brcms_c_suspend_mac_and_रुको(wlc);
			brcms_c_beacon_phytxctl_txant_upd(wlc, wlc->bcn_rspec);
			brcms_c_enable_mac(wlc);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcms_c_stf_spatial_policy_set(काष्ठा brcms_c_info *wlc, पूर्णांक val)
अणु
	पूर्णांक i;
	u8 core_mask = 0;

	brcms_dbg_ht(wlc->hw->d11core, "wl%d: val %x\n", wlc->pub->unit,
		     val);

	wlc->stf->spatial_policy = (s8) val;
	क्रम (i = 1; i <= MAX_STREAMS_SUPPORTED; i++) अणु
		core_mask = (val == MAX_SPATIAL_EXPANSION) ?
		    wlc->stf->txchain : txcore_शेष[i];
		brcms_c_stf_txcore_set(wlc, (u8) i, core_mask);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Centralized txant update function. call it whenever wlc->stf->txant and/or
 * wlc->stf->txchain change.
 *
 * Antennas are controlled by ucode indirectly, which drives PHY or GPIO to
 * achieve various tx/rx antenna selection schemes
 *
 * legacy phy, bit 6 and bit 7 means antenna 0 and 1 respectively, bit6+bit7
 * means स्वतः(last rx).
 * क्रम NREV<3, bit 6 and bit 7 means antenna 0 and 1 respectively, bit6+bit7
 * means last rx and करो tx-antenna selection क्रम SISO transmissions
 * क्रम NREV=3, bit 6 and bit _8_ means antenna 0 and 1 respectively, bit6+bit7
 * means last rx and करो tx-antenna selection क्रम SISO transmissions
 * क्रम NREV>=7, bit 6 and bit 7 mean antenna 0 and 1 respectively, nit6+bit7
 * means both cores active
*/
अटल व्योम _brcms_c_stf_phy_txant_upd(काष्ठा brcms_c_info *wlc)
अणु
	s8 txant;

	txant = (s8) wlc->stf->txant;
	अगर (BRCMS_PHY_11N_CAP(wlc->band)) अणु
		अगर (txant == ANT_TX_FORCE_0) अणु
			wlc->stf->phytxant = PHY_TXC_ANT_0;
		पूर्ण अन्यथा अगर (txant == ANT_TX_FORCE_1) अणु
			wlc->stf->phytxant = PHY_TXC_ANT_1;

			अगर (BRCMS_ISNPHY(wlc->band) &&
			    NREV_GE(wlc->band->phyrev, 3)
			    && NREV_LT(wlc->band->phyrev, 7))
				wlc->stf->phytxant = PHY_TXC_ANT_2;
		पूर्ण अन्यथा अणु
			अगर (BRCMS_ISLCNPHY(wlc->band) ||
			    BRCMS_ISSSLPNPHY(wlc->band))
				wlc->stf->phytxant = PHY_TXC_LCNPHY_ANT_LAST;
			अन्यथा अणु
				/* catch out of sync wlc->stf->txcore */
				WARN_ON(wlc->stf->txchain <= 0);
				wlc->stf->phytxant =
				    wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (txant == ANT_TX_FORCE_0)
			wlc->stf->phytxant = PHY_TXC_OLD_ANT_0;
		अन्यथा अगर (txant == ANT_TX_FORCE_1)
			wlc->stf->phytxant = PHY_TXC_OLD_ANT_1;
		अन्यथा
			wlc->stf->phytxant = PHY_TXC_OLD_ANT_LAST;
	पूर्ण

	brcms_b_txant_set(wlc->hw, wlc->stf->phytxant);
पूर्ण

पूर्णांक brcms_c_stf_txchain_set(काष्ठा brcms_c_info *wlc, s32 पूर्णांक_val, bool क्रमce)
अणु
	u8 txchain = (u8) पूर्णांक_val;
	u8 txstreams;
	uपूर्णांक i;

	अगर (wlc->stf->txchain == txchain)
		वापस 0;

	अगर ((txchain & ~wlc->stf->hw_txchain)
	    || !(txchain & wlc->stf->hw_txchain))
		वापस -EINVAL;

	/*
	 * अगर nrate override is configured to be non-SISO STF mode, reject
	 * reducing txchain to 1
	 */
	txstreams = (u8) hweight8(txchain);
	अगर (txstreams > MAX_STREAMS_SUPPORTED)
		वापस -EINVAL;

	wlc->stf->txchain = txchain;
	wlc->stf->txstreams = txstreams;
	brcms_c_stf_stbc_tx_set(wlc, wlc->band->band_stf_stbc_tx);
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_2G_INDEX]);
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_5G_INDEX]);
	wlc->stf->txant =
	    (wlc->stf->txstreams == 1) ? ANT_TX_FORCE_0 : ANT_TX_DEF;
	_brcms_c_stf_phy_txant_upd(wlc);

	wlc_phy_stf_chain_set(wlc->band->pi, wlc->stf->txchain,
			      wlc->stf->rxchain);

	क्रम (i = 1; i <= MAX_STREAMS_SUPPORTED; i++)
		brcms_c_stf_txcore_set(wlc, (u8) i, txcore_शेष[i]);

	वापस 0;
पूर्ण

/*
 * update wlc->stf->ss_opmode which represents the operational stf_ss mode
 * we're using
 */
व्योम brcms_c_stf_ss_update(काष्ठा brcms_c_info *wlc, काष्ठा brcms_band *band)
अणु
	u8 prev_stf_ss;
	u8 upd_stf_ss;

	prev_stf_ss = wlc->stf->ss_opmode;

	/*
	 * NOTE: opmode can only be SISO or CDD as STBC is decided on a
	 * per-packet basis
	 */
	अगर (BRCMS_STBC_CAP_PHY(wlc) &&
	    wlc->stf->ss_algosel_स्वतः
	    && (wlc->stf->ss_algo_channel != (u16) -1)) अणु
		upd_stf_ss = (wlc->stf->txstreams == 1 ||
			      isset(&wlc->stf->ss_algo_channel,
				    PHY_TXC1_MODE_SISO)) ?
				    PHY_TXC1_MODE_SISO : PHY_TXC1_MODE_CDD;
	पूर्ण अन्यथा अणु
		अगर (wlc->band != band)
			वापस;
		upd_stf_ss = (wlc->stf->txstreams == 1) ?
				PHY_TXC1_MODE_SISO : band->band_stf_ss_mode;
	पूर्ण
	अगर (prev_stf_ss != upd_stf_ss) अणु
		wlc->stf->ss_opmode = upd_stf_ss;
		brcms_b_band_stf_ss_set(wlc->hw, upd_stf_ss);
	पूर्ण
पूर्ण

पूर्णांक brcms_c_stf_attach(काष्ठा brcms_c_info *wlc)
अणु
	wlc->bandstate[BAND_2G_INDEX]->band_stf_ss_mode = PHY_TXC1_MODE_SISO;
	wlc->bandstate[BAND_5G_INDEX]->band_stf_ss_mode = PHY_TXC1_MODE_CDD;

	अगर (BRCMS_ISNPHY(wlc->band) &&
	    (wlc_phy_txघातer_hw_ctrl_get(wlc->band->pi) != PHY_TPC_HW_ON))
		wlc->bandstate[BAND_2G_INDEX]->band_stf_ss_mode =
		    PHY_TXC1_MODE_CDD;
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_2G_INDEX]);
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_5G_INDEX]);

	brcms_c_stf_stbc_rx_ht_update(wlc, HT_CAP_RX_STBC_NO);
	wlc->bandstate[BAND_2G_INDEX]->band_stf_stbc_tx = OFF;
	wlc->bandstate[BAND_5G_INDEX]->band_stf_stbc_tx = OFF;

	अगर (BRCMS_STBC_CAP_PHY(wlc)) अणु
		wlc->stf->ss_algosel_स्वतः = true;
		/* Init the शेष value */
		wlc->stf->ss_algo_channel = (u16) -1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम brcms_c_stf_detach(काष्ठा brcms_c_info *wlc)
अणु
पूर्ण

व्योम brcms_c_stf_phy_txant_upd(काष्ठा brcms_c_info *wlc)
अणु
	_brcms_c_stf_phy_txant_upd(wlc);
पूर्ण

व्योम brcms_c_stf_phy_chain_calc(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा ssb_sprom *sprom = &wlc->hw->d11core->bus->sprom;

	/* get available rx/tx chains */
	wlc->stf->hw_txchain = sprom->txchain;
	wlc->stf->hw_rxchain = sprom->rxchain;

	/* these parameter are पूर्णांकended to be used क्रम all PHY types */
	अगर (wlc->stf->hw_txchain == 0 || wlc->stf->hw_txchain == 0xf) अणु
		अगर (BRCMS_ISNPHY(wlc->band))
			wlc->stf->hw_txchain = TXCHAIN_DEF_NPHY;
		अन्यथा
			wlc->stf->hw_txchain = TXCHAIN_DEF;
	पूर्ण

	wlc->stf->txchain = wlc->stf->hw_txchain;
	wlc->stf->txstreams = (u8) hweight8(wlc->stf->hw_txchain);

	अगर (wlc->stf->hw_rxchain == 0 || wlc->stf->hw_rxchain == 0xf) अणु
		अगर (BRCMS_ISNPHY(wlc->band))
			wlc->stf->hw_rxchain = RXCHAIN_DEF_NPHY;
		अन्यथा
			wlc->stf->hw_rxchain = RXCHAIN_DEF;
	पूर्ण

	wlc->stf->rxchain = wlc->stf->hw_rxchain;
	wlc->stf->rxstreams = (u8) hweight8(wlc->stf->hw_rxchain);

	/* initialize the txcore table */
	स_नकल(wlc->stf->txcore, txcore_शेष, माप(wlc->stf->txcore));

	/* शेष spatial_policy */
	wlc->stf->spatial_policy = MIN_SPATIAL_EXPANSION;
	brcms_c_stf_spatial_policy_set(wlc, MIN_SPATIAL_EXPANSION);
पूर्ण

अटल u16 _brcms_c_stf_phytxchain_sel(काष्ठा brcms_c_info *wlc,
				       u32 rspec)
अणु
	u16 phytxant = wlc->stf->phytxant;

	अगर (rspec_stf(rspec) != PHY_TXC1_MODE_SISO)
		phytxant = wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
	अन्यथा अगर (wlc->stf->txant == ANT_TX_DEF)
		phytxant = wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
	phytxant &= PHY_TXC_ANT_MASK;
	वापस phytxant;
पूर्ण

u16 brcms_c_stf_phytxchain_sel(काष्ठा brcms_c_info *wlc, u32 rspec)
अणु
	वापस _brcms_c_stf_phytxchain_sel(wlc, rspec);
पूर्ण

u16 brcms_c_stf_d11hdrs_phyctl_txant(काष्ठा brcms_c_info *wlc, u32 rspec)
अणु
	u16 phytxant = wlc->stf->phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* क्रम non-siso rates or शेष setting, use the available chains */
	अगर (BRCMS_ISNPHY(wlc->band)) अणु
		phytxant = _brcms_c_stf_phytxchain_sel(wlc, rspec);
		mask = PHY_TXC_HTANT_MASK;
	पूर्ण
	phytxant |= phytxant & mask;
	वापस phytxant;
पूर्ण
