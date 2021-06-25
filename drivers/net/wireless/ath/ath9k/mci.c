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

#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश "ath9k.h"
#समावेश "mci.h"

अटल स्थिर u8 ath_mci_duty_cycle[] = अणु 55, 50, 60, 70, 80, 85, 90, 95, 98 पूर्ण;

अटल काष्ठा ath_mci_profile_info*
ath_mci_find_profile(काष्ठा ath_mci_profile *mci,
		     काष्ठा ath_mci_profile_info *info)
अणु
	काष्ठा ath_mci_profile_info *entry;

	अगर (list_empty(&mci->info))
		वापस शून्य;

	list_क्रम_each_entry(entry, &mci->info, list) अणु
		अगर (entry->conn_handle == info->conn_handle)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool ath_mci_add_profile(काष्ठा ath_common *common,
				काष्ठा ath_mci_profile *mci,
				काष्ठा ath_mci_profile_info *info)
अणु
	काष्ठा ath_mci_profile_info *entry;
	u8 voice_priority[] = अणु 110, 110, 110, 112, 110, 110, 114, 116, 118 पूर्ण;

	अगर ((mci->num_sco == ATH_MCI_MAX_SCO_PROखाता) &&
	    (info->type == MCI_GPM_COEX_PROखाता_VOICE))
		वापस false;

	अगर (((NUM_PROF(mci) - mci->num_sco) == ATH_MCI_MAX_ACL_PROखाता) &&
	    (info->type != MCI_GPM_COEX_PROखाता_VOICE))
		वापस false;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस false;

	स_नकल(entry, info, 10);
	INC_PROF(mci, info);
	list_add_tail(&entry->list, &mci->info);
	अगर (info->type == MCI_GPM_COEX_PROखाता_VOICE) अणु
		अगर (info->voice_type < माप(voice_priority))
			mci->voice_priority = voice_priority[info->voice_type];
		अन्यथा
			mci->voice_priority = 110;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम ath_mci_del_profile(काष्ठा ath_common *common,
				काष्ठा ath_mci_profile *mci,
				काष्ठा ath_mci_profile_info *entry)
अणु
	अगर (!entry)
		वापस;

	DEC_PROF(mci, entry);
	list_del(&entry->list);
	kमुक्त(entry);
पूर्ण

व्योम ath_mci_flush_profile(काष्ठा ath_mci_profile *mci)
अणु
	काष्ठा ath_mci_profile_info *info, *tinfo;

	mci->aggr_limit = 0;
	mci->num_mgmt = 0;

	अगर (list_empty(&mci->info))
		वापस;

	list_क्रम_each_entry_safe(info, tinfo, &mci->info, list) अणु
		list_del(&info->list);
		DEC_PROF(mci, info);
		kमुक्त(info);
	पूर्ण
पूर्ण

अटल व्योम ath_mci_adjust_aggr_limit(काष्ठा ath_btcoex *btcoex)
अणु
	काष्ठा ath_mci_profile *mci = &btcoex->mci;
	u32 wlan_airसमय = btcoex->btcoex_period *
				(100 - btcoex->duty_cycle) / 100;

	/*
	 * Scale: wlan_airसमय is in ms, aggr_limit is in 0.25 ms.
	 * When wlan_airसमय is less than 4ms, aggregation limit has to be
	 * adjusted half of wlan_airसमय to ensure that the aggregation can fit
	 * without collision with BT traffic.
	 */
	अगर ((wlan_airसमय <= 4) &&
	    (!mci->aggr_limit || (mci->aggr_limit > (2 * wlan_airसमय))))
		mci->aggr_limit = 2 * wlan_airसमय;
पूर्ण

अटल व्योम ath_mci_update_scheme(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &btcoex->mci;
	काष्ठा ath9k_hw_mci *mci_hw = &sc->sc_ah->btcoex_hw.mci;
	काष्ठा ath_mci_profile_info *info;
	u32 num_profile = NUM_PROF(mci);

	अगर (mci_hw->config & ATH_MCI_CONFIG_DISABLE_TUNING)
		जाओ skip_tuning;

	mci->aggr_limit = 0;
	btcoex->duty_cycle = ath_mci_duty_cycle[num_profile];
	btcoex->btcoex_period = ATH_MCI_DEF_BT_PERIOD;
	अगर (NUM_PROF(mci))
		btcoex->bt_stomp_type = ATH_BTCOEX_STOMP_LOW;
	अन्यथा
		btcoex->bt_stomp_type = mci->num_mgmt ? ATH_BTCOEX_STOMP_ALL :
							ATH_BTCOEX_STOMP_LOW;

	अगर (num_profile == 1) अणु
		info = list_first_entry(&mci->info,
					काष्ठा ath_mci_profile_info,
					list);
		अगर (mci->num_sco) अणु
			अगर (info->T == 12)
				mci->aggr_limit = 8;
			अन्यथा अगर (info->T == 6) अणु
				mci->aggr_limit = 6;
				btcoex->duty_cycle = 30;
			पूर्ण अन्यथा
				mci->aggr_limit = 6;
			ath_dbg(common, MCI,
				"Single SCO, aggregation limit %d 1/4 ms\n",
				mci->aggr_limit);
		पूर्ण अन्यथा अगर (mci->num_pan || mci->num_other_acl) अणु
			/*
			 * For single PAN/FTP profile, allocate 35% क्रम BT
			 * to improve WLAN throughput.
			 */
			btcoex->duty_cycle = AR_SREV_9565(sc->sc_ah) ? 40 : 35;
			btcoex->btcoex_period = 53;
			ath_dbg(common, MCI,
				"Single PAN/FTP bt period %d ms dutycycle %d\n",
				btcoex->duty_cycle, btcoex->btcoex_period);
		पूर्ण अन्यथा अगर (mci->num_hid) अणु
			btcoex->duty_cycle = 30;
			mci->aggr_limit = 6;
			ath_dbg(common, MCI,
				"Multiple attempt/timeout single HID "
				"aggregation limit 1.5 ms dutycycle 30%%\n");
		पूर्ण
	पूर्ण अन्यथा अगर (num_profile == 2) अणु
		अगर (mci->num_hid == 2)
			btcoex->duty_cycle = 30;
		mci->aggr_limit = 6;
		ath_dbg(common, MCI,
			"Two BT profiles aggr limit 1.5 ms dutycycle %d%%\n",
			btcoex->duty_cycle);
	पूर्ण अन्यथा अगर (num_profile >= 3) अणु
		mci->aggr_limit = 4;
		ath_dbg(common, MCI,
			"Three or more profiles aggregation limit 1 ms\n");
	पूर्ण

skip_tuning:
	अगर (IS_CHAN_2GHZ(sc->sc_ah->curchan)) अणु
		अगर (IS_CHAN_HT(sc->sc_ah->curchan))
			ath_mci_adjust_aggr_limit(btcoex);
		अन्यथा
			btcoex->btcoex_period >>= 1;
	पूर्ण

	ath9k_btcoex_समयr_छोड़ो(sc);
	ath9k_hw_btcoex_disable(sc->sc_ah);

	अगर (IS_CHAN_5GHZ(sc->sc_ah->curchan))
		वापस;

	btcoex->duty_cycle += (mci->num_bdr ? ATH_MCI_BDR_DUTY_CYCLE : 0);
	अगर (btcoex->duty_cycle > ATH_MCI_MAX_DUTY_CYCLE)
		btcoex->duty_cycle = ATH_MCI_MAX_DUTY_CYCLE;

	btcoex->btcoex_no_stomp =  btcoex->btcoex_period *
		(100 - btcoex->duty_cycle) / 100;

	ath9k_hw_btcoex_enable(sc->sc_ah);
	ath9k_btcoex_समयr_resume(sc);
पूर्ण

अटल व्योम ath_mci_cal_msg(काष्ठा ath_softc *sc, u8 opcode, u8 *rx_payload)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 payload[4] = अणु0, 0, 0, 0पूर्ण;

	चयन (opcode) अणु
	हाल MCI_GPM_BT_CAL_REQ:
		अगर (mci_hw->bt_state == MCI_BT_AWAKE) अणु
			mci_hw->bt_state = MCI_BT_CAL_START;
			ath9k_queue_reset(sc, RESET_TYPE_MCI);
		पूर्ण
		ath_dbg(common, MCI, "MCI State : %d\n", mci_hw->bt_state);
		अवरोध;
	हाल MCI_GPM_BT_CAL_GRANT:
		MCI_GPM_SET_CAL_TYPE(payload, MCI_GPM_WLAN_CAL_DONE);
		ar9003_mci_send_message(sc->sc_ah, MCI_GPM, 0, payload,
					16, false, true);
		अवरोध;
	शेष:
		ath_dbg(common, MCI, "Unknown GPM CAL message\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath9k_mci_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath_softc *sc = container_of(work, काष्ठा ath_softc, mci_work);

	ath_mci_update_scheme(sc);
पूर्ण

अटल व्योम ath_mci_update_stomp_txprio(u8 cur_txprio, u8 *stomp_prio)
अणु
	अगर (cur_txprio < stomp_prio[ATH_BTCOEX_STOMP_NONE])
		stomp_prio[ATH_BTCOEX_STOMP_NONE] = cur_txprio;

	अगर (cur_txprio > stomp_prio[ATH_BTCOEX_STOMP_ALL])
		stomp_prio[ATH_BTCOEX_STOMP_ALL] = cur_txprio;

	अगर ((cur_txprio > ATH_MCI_HI_PRIO) &&
	    (cur_txprio < stomp_prio[ATH_BTCOEX_STOMP_LOW]))
		stomp_prio[ATH_BTCOEX_STOMP_LOW] = cur_txprio;
पूर्ण

अटल व्योम ath_mci_set_concur_txprio(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &btcoex->mci;
	u8 stomp_txprio[ATH_BTCOEX_STOMP_MAX];

	स_रखो(stomp_txprio, 0, माप(stomp_txprio));
	अगर (mci->num_mgmt) अणु
		stomp_txprio[ATH_BTCOEX_STOMP_ALL] = ATH_MCI_INQUIRY_PRIO;
		अगर (!mci->num_pan && !mci->num_other_acl)
			stomp_txprio[ATH_BTCOEX_STOMP_NONE] =
				ATH_MCI_INQUIRY_PRIO;
	पूर्ण अन्यथा अणु
		u8 prof_prio[] = अणु 50, 90, 94, 52 पूर्ण;/* RFCOMM, A2DP, HID, PAN */

		stomp_txprio[ATH_BTCOEX_STOMP_LOW] =
		stomp_txprio[ATH_BTCOEX_STOMP_NONE] = 0xff;

		अगर (mci->num_sco)
			ath_mci_update_stomp_txprio(mci->voice_priority,
						    stomp_txprio);
		अगर (mci->num_other_acl)
			ath_mci_update_stomp_txprio(prof_prio[0], stomp_txprio);
		अगर (mci->num_a2dp)
			ath_mci_update_stomp_txprio(prof_prio[1], stomp_txprio);
		अगर (mci->num_hid)
			ath_mci_update_stomp_txprio(prof_prio[2], stomp_txprio);
		अगर (mci->num_pan)
			ath_mci_update_stomp_txprio(prof_prio[3], stomp_txprio);

		अगर (stomp_txprio[ATH_BTCOEX_STOMP_NONE] == 0xff)
			stomp_txprio[ATH_BTCOEX_STOMP_NONE] = 0;

		अगर (stomp_txprio[ATH_BTCOEX_STOMP_LOW] == 0xff)
			stomp_txprio[ATH_BTCOEX_STOMP_LOW] = 0;
	पूर्ण
	ath9k_hw_btcoex_set_concur_txprio(sc->sc_ah, stomp_txprio);
पूर्ण

अटल u8 ath_mci_process_profile(काष्ठा ath_softc *sc,
				  काष्ठा ath_mci_profile_info *info)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &btcoex->mci;
	काष्ठा ath_mci_profile_info *entry = शून्य;

	entry = ath_mci_find_profile(mci, info);
	अगर (entry) अणु
		/*
		 * Two MCI पूर्णांकerrupts are generated जबतक connecting to
		 * headset and A2DP profile, but only one MCI पूर्णांकerrupt
		 * is generated with last added profile type जबतक disconnecting
		 * both profiles.
		 * So जबतक adding second profile type decrement
		 * the first one.
		 */
		अगर (entry->type != info->type) अणु
			DEC_PROF(mci, entry);
			INC_PROF(mci, info);
		पूर्ण
		स_नकल(entry, info, 10);
	पूर्ण

	अगर (info->start) अणु
		अगर (!entry && !ath_mci_add_profile(common, mci, info))
			वापस 0;
	पूर्ण अन्यथा
		ath_mci_del_profile(common, mci, entry);

	ath_mci_set_concur_txprio(sc);
	वापस 1;
पूर्ण

अटल u8 ath_mci_process_status(काष्ठा ath_softc *sc,
				 काष्ठा ath_mci_profile_status *status)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &btcoex->mci;
	काष्ठा ath_mci_profile_info info;
	पूर्णांक i = 0, old_num_mgmt = mci->num_mgmt;

	/* Link status type are not handled */
	अगर (status->is_link)
		वापस 0;

	info.conn_handle = status->conn_handle;
	अगर (ath_mci_find_profile(mci, &info))
		वापस 0;

	अगर (status->conn_handle >= ATH_MCI_MAX_PROखाता)
		वापस 0;

	अगर (status->is_critical)
		__set_bit(status->conn_handle, mci->status);
	अन्यथा
		__clear_bit(status->conn_handle, mci->status);

	mci->num_mgmt = 0;
	करो अणु
		अगर (test_bit(i, mci->status))
			mci->num_mgmt++;
	पूर्ण जबतक (++i < ATH_MCI_MAX_PROखाता);

	ath_mci_set_concur_txprio(sc);
	अगर (old_num_mgmt != mci->num_mgmt)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम ath_mci_msg(काष्ठा ath_softc *sc, u8 opcode, u8 *rx_payload)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_mci_profile_info profile_info;
	काष्ठा ath_mci_profile_status profile_status;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	u8 major, minor, update_scheme = 0;
	u32 seq_num;

	अगर (ar9003_mci_state(ah, MCI_STATE_NEED_FLUSH_BT_INFO) &&
	    ar9003_mci_state(ah, MCI_STATE_ENABLE)) अणु
		ath_dbg(common, MCI, "(MCI) Need to flush BT profiles\n");
		ath_mci_flush_profile(&sc->btcoex.mci);
		ar9003_mci_state(ah, MCI_STATE_SEND_STATUS_QUERY);
	पूर्ण

	चयन (opcode) अणु
	हाल MCI_GPM_COEX_VERSION_QUERY:
		ar9003_mci_state(ah, MCI_STATE_SEND_WLAN_COEX_VERSION);
		अवरोध;
	हाल MCI_GPM_COEX_VERSION_RESPONSE:
		major = *(rx_payload + MCI_GPM_COEX_B_MAJOR_VERSION);
		minor = *(rx_payload + MCI_GPM_COEX_B_MINOR_VERSION);
		ar9003_mci_set_bt_version(ah, major, minor);
		अवरोध;
	हाल MCI_GPM_COEX_STATUS_QUERY:
		ar9003_mci_send_wlan_channels(ah);
		अवरोध;
	हाल MCI_GPM_COEX_BT_PROखाता_INFO:
		स_नकल(&profile_info,
		       (rx_payload + MCI_GPM_COEX_B_PROखाता_TYPE), 10);

		अगर ((profile_info.type == MCI_GPM_COEX_PROखाता_UNKNOWN) ||
		    (profile_info.type >= MCI_GPM_COEX_PROखाता_MAX)) अणु
			ath_dbg(common, MCI,
				"Illegal profile type = %d, state = %d\n",
				profile_info.type,
				profile_info.start);
			अवरोध;
		पूर्ण

		update_scheme += ath_mci_process_profile(sc, &profile_info);
		अवरोध;
	हाल MCI_GPM_COEX_BT_STATUS_UPDATE:
		profile_status.is_link = *(rx_payload +
					   MCI_GPM_COEX_B_STATUS_TYPE);
		profile_status.conn_handle = *(rx_payload +
					       MCI_GPM_COEX_B_STATUS_LINKID);
		profile_status.is_critical = *(rx_payload +
					       MCI_GPM_COEX_B_STATUS_STATE);

		seq_num = *((u32 *)(rx_payload + 12));
		ath_dbg(common, MCI,
			"BT_Status_Update: is_link=%d, linkId=%d, state=%d, SEQ=%u\n",
			profile_status.is_link, profile_status.conn_handle,
			profile_status.is_critical, seq_num);

		update_scheme += ath_mci_process_status(sc, &profile_status);
		अवरोध;
	शेष:
		ath_dbg(common, MCI, "Unknown GPM COEX message = 0x%02x\n", opcode);
		अवरोध;
	पूर्ण
	अगर (update_scheme)
		ieee80211_queue_work(sc->hw, &sc->mci_work);
पूर्ण

पूर्णांक ath_mci_setup(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_mci_coex *mci = &sc->mci_coex;
	काष्ठा ath_mci_buf *buf = &mci->sched_buf;
	पूर्णांक ret;

	buf->bf_addr = dmam_alloc_coherent(sc->dev,
				  ATH_MCI_SCHED_BUF_SIZE + ATH_MCI_GPM_BUF_SIZE,
				  &buf->bf_paddr, GFP_KERNEL);

	अगर (buf->bf_addr == शून्य) अणु
		ath_dbg(common, FATAL, "MCI buffer alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(buf->bf_addr, MCI_GPM_RSVD_PATTERN,
	       ATH_MCI_SCHED_BUF_SIZE + ATH_MCI_GPM_BUF_SIZE);

	mci->sched_buf.bf_len = ATH_MCI_SCHED_BUF_SIZE;

	mci->gpm_buf.bf_len = ATH_MCI_GPM_BUF_SIZE;
	mci->gpm_buf.bf_addr = mci->sched_buf.bf_addr + mci->sched_buf.bf_len;
	mci->gpm_buf.bf_paddr = mci->sched_buf.bf_paddr + mci->sched_buf.bf_len;

	ret = ar9003_mci_setup(sc->sc_ah, mci->gpm_buf.bf_paddr,
			       mci->gpm_buf.bf_addr, (mci->gpm_buf.bf_len >> 4),
			       mci->sched_buf.bf_paddr);
	अगर (ret) अणु
		ath_err(common, "Failed to initialize MCI\n");
		वापस ret;
	पूर्ण

	INIT_WORK(&sc->mci_work, ath9k_mci_work);
	ath_dbg(common, MCI, "MCI Initialized\n");

	वापस 0;
पूर्ण

व्योम ath_mci_cleanup(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_hw *ah = sc->sc_ah;

	ar9003_mci_cleanup(ah);

	ath_dbg(common, MCI, "MCI De-Initialized\n");
पूर्ण

व्योम ath_mci_पूर्णांकr(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_mci_coex *mci = &sc->mci_coex;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 mci_पूर्णांक, mci_पूर्णांक_rxmsg;
	u32 offset, subtype, opcode;
	u32 *pgpm;
	u32 more_data = MCI_GPM_MORE;
	bool skip_gpm = false;

	ar9003_mci_get_पूर्णांकerrupt(sc->sc_ah, &mci_पूर्णांक, &mci_पूर्णांक_rxmsg);

	अगर (ar9003_mci_state(ah, MCI_STATE_ENABLE) == 0) अणु
		ar9003_mci_state(ah, MCI_STATE_INIT_GPM_OFFSET);
		वापस;
	पूर्ण

	अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE) अणु
		u32 payload[4] = अणु 0xffffffff, 0xffffffff,
				   0xffffffff, 0xffffff00पूर्ण;

		/*
		 * The following REMOTE_RESET and SYS_WAKING used to sent
		 * only when BT wake up. Now they are always sent, as a
		 * recovery method to reset BT MCI's RX alignment.
		 */
		ar9003_mci_send_message(ah, MCI_REMOTE_RESET, 0,
					payload, 16, true, false);
		ar9003_mci_send_message(ah, MCI_SYS_WAKING, 0,
					शून्य, 0, true, false);

		mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE;
		ar9003_mci_state(ah, MCI_STATE_RESET_REQ_WAKE);

		/*
		 * always करो this क्रम recovery and 2G/5G toggling and LNA_TRANS
		 */
		ar9003_mci_state(ah, MCI_STATE_SET_BT_AWAKE);
	पूर्ण

	अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING) अणु
		mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING;

		अगर ((mci_hw->bt_state == MCI_BT_SLEEP) &&
		    (ar9003_mci_state(ah, MCI_STATE_REMOTE_SLEEP) !=
		     MCI_BT_SLEEP))
			ar9003_mci_state(ah, MCI_STATE_SET_BT_AWAKE);
	पूर्ण

	अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING) अणु
		mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING;

		अगर ((mci_hw->bt_state == MCI_BT_AWAKE) &&
		    (ar9003_mci_state(ah, MCI_STATE_REMOTE_SLEEP) !=
		     MCI_BT_AWAKE))
			mci_hw->bt_state = MCI_BT_SLEEP;
	पूर्ण

	अगर ((mci_पूर्णांक & AR_MCI_INTERRUPT_RX_INVALID_HDR) ||
	    (mci_पूर्णांक & AR_MCI_INTERRUPT_CONT_INFO_TIMEOUT)) अणु
		ar9003_mci_state(ah, MCI_STATE_RECOVER_RX);
		skip_gpm = true;
	पूर्ण

	अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_SCHD_INFO) अणु
		mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_SCHD_INFO;
		ar9003_mci_state(ah, MCI_STATE_LAST_SCHD_MSG_OFFSET);
	पूर्ण

	अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_GPM) अणु
		mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_GPM;

		जबतक (more_data == MCI_GPM_MORE) अणु
			अगर (test_bit(ATH_OP_HW_RESET, &common->op_flags))
				वापस;

			pgpm = mci->gpm_buf.bf_addr;
			offset = ar9003_mci_get_next_gpm_offset(ah, &more_data);

			अगर (offset == MCI_GPM_INVALID)
				अवरोध;

			pgpm += (offset >> 2);

			/*
			 * The first dword is समयr.
			 * The real data starts from 2nd dword.
			 */
			subtype = MCI_GPM_TYPE(pgpm);
			opcode = MCI_GPM_OPCODE(pgpm);

			अगर (skip_gpm)
				जाओ recycle;

			अगर (MCI_GPM_IS_CAL_TYPE(subtype)) अणु
				ath_mci_cal_msg(sc, subtype, (u8 *)pgpm);
			पूर्ण अन्यथा अणु
				चयन (subtype) अणु
				हाल MCI_GPM_COEX_AGENT:
					ath_mci_msg(sc, opcode, (u8 *)pgpm);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		recycle:
			MCI_GPM_RECYCLE(pgpm);
		पूर्ण
	पूर्ण

	अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_HW_MSG_MASK) अणु
		अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_LNA_CONTROL)
			mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_LNA_CONTROL;

		अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_LNA_INFO)
			mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_LNA_INFO;

		अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_CONT_INFO) अणु
			पूर्णांक value_dbm = MS(mci_hw->cont_status,
					   AR_MCI_CONT_RSSI_POWER);

			mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_CONT_INFO;

			ath_dbg(common, MCI,
				"MCI CONT_INFO: (%s) pri = %d pwr = %d dBm\n",
				MS(mci_hw->cont_status, AR_MCI_CONT_TXRX) ?
				"tx" : "rx",
				MS(mci_hw->cont_status, AR_MCI_CONT_PRIORITY),
				value_dbm);
		पूर्ण

		अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_CONT_NACK)
			mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_CONT_NACK;

		अगर (mci_पूर्णांक_rxmsg & AR_MCI_INTERRUPT_RX_MSG_CONT_RST)
			mci_पूर्णांक_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_CONT_RST;
	पूर्ण

	अगर ((mci_पूर्णांक & AR_MCI_INTERRUPT_RX_INVALID_HDR) ||
	    (mci_पूर्णांक & AR_MCI_INTERRUPT_CONT_INFO_TIMEOUT)) अणु
		mci_पूर्णांक &= ~(AR_MCI_INTERRUPT_RX_INVALID_HDR |
			     AR_MCI_INTERRUPT_CONT_INFO_TIMEOUT);
		ath_mci_msg(sc, MCI_GPM_COEX_NOOP, शून्य);
	पूर्ण
पूर्ण

व्योम ath_mci_enable(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	अगर (!common->btcoex_enabled)
		वापस;

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_MCI)
		sc->sc_ah->imask |= ATH9K_INT_MCI;
पूर्ण

व्योम ath9k_mci_update_wlan_channels(काष्ठा ath_softc *sc, bool allow_all)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	काष्ठा ath9k_channel *chan = ah->curchan;
	u32 channelmap[] = अणु0x00000000, 0xffff0000, 0xffffffff, 0x7fffffffपूर्ण;
	पूर्णांक i;
	s16 chan_start, chan_end;
	u16 wlan_chan;

	अगर (!chan || !IS_CHAN_2GHZ(chan))
		वापस;

	अगर (allow_all)
		जाओ send_wlan_chan;

	wlan_chan = chan->channel - 2402;

	chan_start = wlan_chan - 10;
	chan_end = wlan_chan + 10;

	अगर (IS_CHAN_HT40PLUS(chan))
		chan_end += 20;
	अन्यथा अगर (IS_CHAN_HT40MINUS(chan))
		chan_start -= 20;

	/* adjust side band */
	chan_start -= 7;
	chan_end += 7;

	अगर (chan_start <= 0)
		chan_start = 0;
	अगर (chan_end >= ATH_MCI_NUM_BT_CHANNELS)
		chan_end = ATH_MCI_NUM_BT_CHANNELS - 1;

	ath_dbg(ath9k_hw_common(ah), MCI,
		"WLAN current channel %d mask BT channel %d - %d\n",
		wlan_chan, chan_start, chan_end);

	क्रम (i = chan_start; i < chan_end; i++)
		MCI_GPM_CLR_CHANNEL_BIT(&channelmap, i);

send_wlan_chan:
	/* update and send wlan channels info to BT */
	क्रम (i = 0; i < 4; i++)
		mci->wlan_channels[i] = channelmap[i];
	ar9003_mci_send_wlan_channels(ah);
	ar9003_mci_state(ah, MCI_STATE_SEND_VERSION_QUERY);
पूर्ण

व्योम ath9k_mci_set_txघातer(काष्ठा ath_softc *sc, bool setchannel,
			   bool concur_tx)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_hw_mci *mci_hw = &sc->sc_ah->btcoex_hw.mci;
	bool old_concur_tx = mci_hw->concur_tx;

	अगर (!(mci_hw->config & ATH_MCI_CONFIG_CONCUR_TX)) अणु
		mci_hw->concur_tx = false;
		वापस;
	पूर्ण

	अगर (!IS_CHAN_2GHZ(ah->curchan))
		वापस;

	अगर (setchannel) अणु
		काष्ठा ath9k_hw_cal_data *caldata = &sc->cur_chan->caldata;
		अगर (IS_CHAN_HT40PLUS(ah->curchan) &&
		    (ah->curchan->channel > caldata->channel) &&
		    (ah->curchan->channel <= caldata->channel + 20))
			वापस;
		अगर (IS_CHAN_HT40MINUS(ah->curchan) &&
		    (ah->curchan->channel < caldata->channel) &&
		    (ah->curchan->channel >= caldata->channel - 20))
			वापस;
		mci_hw->concur_tx = false;
	पूर्ण अन्यथा
		mci_hw->concur_tx = concur_tx;

	अगर (old_concur_tx != mci_hw->concur_tx)
		ath9k_hw_set_txघातerlimit(ah, sc->cur_chan->txघातer, false);
पूर्ण

अटल व्योम ath9k_mci_stomp_audio(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &btcoex->mci;

	अगर (!mci->num_sco && !mci->num_a2dp)
		वापस;

	अगर (ah->stats.avgbrssi > 25) अणु
		btcoex->stomp_audio = 0;
		वापस;
	पूर्ण

	btcoex->stomp_audio++;
पूर्ण
व्योम ath9k_mci_update_rssi(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath9k_hw_mci *mci_hw = &sc->sc_ah->btcoex_hw.mci;

	ath9k_mci_stomp_audio(sc);

	अगर (!(mci_hw->config & ATH_MCI_CONFIG_CONCUR_TX))
		वापस;

	अगर (ah->stats.avgbrssi >= 40) अणु
		अगर (btcoex->rssi_count < 0)
			btcoex->rssi_count = 0;
		अगर (++btcoex->rssi_count >= ATH_MCI_CONCUR_TX_SWITCH) अणु
			btcoex->rssi_count = 0;
			ath9k_mci_set_txघातer(sc, false, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (btcoex->rssi_count > 0)
			btcoex->rssi_count = 0;
		अगर (--btcoex->rssi_count <= -ATH_MCI_CONCUR_TX_SWITCH) अणु
			btcoex->rssi_count = 0;
			ath9k_mci_set_txघातer(sc, false, false);
		पूर्ण
	पूर्ण
पूर्ण
