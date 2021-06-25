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

#अगर_अघोषित MCI_H
#घोषणा MCI_H

#समावेश "ar9003_mci.h"

#घोषणा ATH_MCI_SCHED_BUF_SIZE		(16 * 16) /* 16 entries, 4 dword each */
#घोषणा ATH_MCI_GPM_MAX_ENTRY		16
#घोषणा ATH_MCI_GPM_BUF_SIZE		(ATH_MCI_GPM_MAX_ENTRY * 16)
#घोषणा ATH_MCI_DEF_BT_PERIOD		40
#घोषणा ATH_MCI_BDR_DUTY_CYCLE		20
#घोषणा ATH_MCI_MAX_DUTY_CYCLE		90

#घोषणा ATH_MCI_DEF_AGGR_LIMIT		6 /* in 0.24 ms */
#घोषणा ATH_MCI_MAX_ACL_PROखाता		7
#घोषणा ATH_MCI_MAX_SCO_PROखाता		1
#घोषणा ATH_MCI_MAX_PROखाता		(ATH_MCI_MAX_ACL_PROखाता +\
					 ATH_MCI_MAX_SCO_PROखाता)

#घोषणा ATH_MCI_INQUIRY_PRIO         62
#घोषणा ATH_MCI_HI_PRIO              60
#घोषणा ATH_MCI_NUM_BT_CHANNELS      79
#घोषणा ATH_MCI_CONCUR_TX_SWITCH      5

#घोषणा MCI_GPM_SET_CHANNEL_BIT(_p_gpm, _bt_chan)			  \
	करो अणु								  \
		अगर (_bt_chan < ATH_MCI_NUM_BT_CHANNELS) अणु		  \
			*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_CHANNEL_MAP + \
				(_bt_chan / 8)) |= (1 << (_bt_chan & 7)); \
		पूर्ण							  \
	पूर्ण जबतक (0)

#घोषणा MCI_GPM_CLR_CHANNEL_BIT(_p_gpm, _bt_chan)			  \
	करो अणु								  \
		अगर (_bt_chan < ATH_MCI_NUM_BT_CHANNELS) अणु		  \
			*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_CHANNEL_MAP + \
				(_bt_chan / 8)) &= ~(1 << (_bt_chan & 7));\
		पूर्ण							  \
	पूर्ण जबतक (0)

#घोषणा INC_PROF(_mci, _info) करो अणु		 \
		चयन (_info->type) अणु		 \
		हाल MCI_GPM_COEX_PROखाता_RFCOMM:\
			_mci->num_other_acl++;	 \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_A2DP:	 \
			_mci->num_a2dp++;	 \
			अगर (!_info->edr)	 \
				_mci->num_bdr++; \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_HID:	 \
			_mci->num_hid++;	 \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_BNEP:	 \
			_mci->num_pan++;	 \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_VOICE: \
		हाल MCI_GPM_COEX_PROखाता_A2DPVO:\
			_mci->num_sco++;	 \
			अवरोध;			 \
		शेष:			 \
			अवरोध;			 \
		पूर्ण				 \
	पूर्ण जबतक (0)

#घोषणा DEC_PROF(_mci, _info) करो अणु		 \
		चयन (_info->type) अणु		 \
		हाल MCI_GPM_COEX_PROखाता_RFCOMM:\
			_mci->num_other_acl--;	 \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_A2DP:	 \
			_mci->num_a2dp--;	 \
			अगर (!_info->edr)	 \
				_mci->num_bdr--; \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_HID:	 \
			_mci->num_hid--;	 \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_BNEP:	 \
			_mci->num_pan--;	 \
			अवरोध;			 \
		हाल MCI_GPM_COEX_PROखाता_VOICE: \
		हाल MCI_GPM_COEX_PROखाता_A2DPVO:\
			_mci->num_sco--;	 \
			अवरोध;			 \
		शेष:			 \
			अवरोध;			 \
		पूर्ण				 \
	पूर्ण जबतक (0)

#घोषणा NUM_PROF(_mci)	(_mci->num_other_acl + _mci->num_a2dp + \
			 _mci->num_hid + _mci->num_pan + _mci->num_sco)

काष्ठा ath_mci_profile_info अणु
	u8 type;
	u8 conn_handle;
	bool start;
	bool master;
	bool edr;
	u8 voice_type;
	u16 T;		/* Voice: Tvoice, HID: Tsnअगरf,        in slots */
	u8 W;		/* Voice: Wvoice, HID: Snअगरf समयout, in slots */
	u8 A;		/*		  HID: Snअगरf attempt, in slots */
	काष्ठा list_head list;
पूर्ण;

काष्ठा ath_mci_profile_status अणु
	bool is_critical;
	bool is_link;
	u8 conn_handle;
पूर्ण;

काष्ठा ath_mci_profile अणु
	काष्ठा list_head info;
	DECLARE_BITMAP(status, ATH_MCI_MAX_PROखाता);
	u16 aggr_limit;
	u8 num_mgmt;
	u8 num_sco;
	u8 num_a2dp;
	u8 num_hid;
	u8 num_pan;
	u8 num_other_acl;
	u8 num_bdr;
	u8 voice_priority;
पूर्ण;

काष्ठा ath_mci_buf अणु
	व्योम *bf_addr;		/* भव addr of desc */
	dma_addr_t bf_paddr;    /* physical addr of buffer */
	u32 bf_len;		/* len of data */
पूर्ण;

काष्ठा ath_mci_coex अणु
	काष्ठा ath_mci_buf sched_buf;
	काष्ठा ath_mci_buf gpm_buf;
पूर्ण;

व्योम ath_mci_flush_profile(काष्ठा ath_mci_profile *mci);
पूर्णांक ath_mci_setup(काष्ठा ath_softc *sc);
व्योम ath_mci_cleanup(काष्ठा ath_softc *sc);
व्योम ath_mci_पूर्णांकr(काष्ठा ath_softc *sc);
व्योम ath9k_mci_update_rssi(काष्ठा ath_softc *sc);

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
व्योम ath_mci_enable(काष्ठा ath_softc *sc);
व्योम ath9k_mci_update_wlan_channels(काष्ठा ath_softc *sc, bool allow_all);
व्योम ath9k_mci_set_txघातer(काष्ठा ath_softc *sc, bool setchannel,
			   bool concur_tx);
#अन्यथा
अटल अंतरभूत व्योम ath_mci_enable(काष्ठा ath_softc *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_mci_update_wlan_channels(काष्ठा ath_softc *sc,
						  bool allow_all)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_mci_set_txघातer(काष्ठा ath_softc *sc, bool setchannel,
					 bool concur_tx)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */

#पूर्ण_अगर /* MCI_H*/
