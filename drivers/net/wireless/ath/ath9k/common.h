<शैली गुरु>
/*
 * Copyright (c) 2009-2011 Atheros Communications Inc.
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

#समावेश <net/mac80211.h>

#समावेश "../ath.h"

#समावेश "hw.h"
#समावेश "hw-ops.h"

#समावेश "common-init.h"
#समावेश "common-beacon.h"
#समावेश "common-debug.h"
#समावेश "common-spectral.h"

/* Common header क्रम Atheros 802.11n base driver cores */

#घोषणा WME_BA_BMP_SIZE         64
#घोषणा WME_MAX_BA              WME_BA_BMP_SIZE
#घोषणा ATH_TID_MAX_BUFS        (2 * WME_MAX_BA)

#घोषणा ATH_RSSI_DUMMY_MARKER   127
#घोषणा ATH_RSSI_LPF_LEN 		10
#घोषणा RSSI_LPF_THRESHOLD		-20
#घोषणा ATH_RSSI_EP_MULTIPLIER     (1<<7)
#घोषणा ATH_EP_MUL(x, mul)         ((x) * (mul))
#घोषणा ATH_RSSI_IN(x)             (ATH_EP_MUL((x), ATH_RSSI_EP_MULTIPLIER))
#घोषणा ATH_LPF_RSSI(x, y, len) \
    ((x != ATH_RSSI_DUMMY_MARKER) ? (((x) * ((len) - 1) + (y)) / (len)) : (y))
#घोषणा ATH_RSSI_LPF(x, y) करो अणु                     			\
    अगर ((y) >= RSSI_LPF_THRESHOLD)                         		\
	x = ATH_LPF_RSSI((x), ATH_RSSI_IN((y)), ATH_RSSI_LPF_LEN);  	\
पूर्ण जबतक (0)
#घोषणा ATH_EP_RND(x, mul) 						\
	(((x) + ((mul)/2)) / (mul))

#घोषणा IEEE80211_MS_TO_TU(x)   (((x) * 1000) / 1024)

काष्ठा ath_beacon_config अणु
	काष्ठा ieee80211_vअगर *मुख्य_vअगर;
	पूर्णांक beacon_पूर्णांकerval;
	u16 dtim_period;
	u16 bmiss_समयout;
	u8 dtim_count;
	u8 enable_beacon;
	bool ibss_creator;
	u32 nexttbtt;
	u32 पूर्णांकval;
पूर्ण;

bool ath9k_cmn_rx_accept(काष्ठा ath_common *common,
			 काष्ठा ieee80211_hdr *hdr,
			 काष्ठा ieee80211_rx_status *rxs,
			 काष्ठा ath_rx_status *rx_stats,
			 bool *decrypt_error,
			 अचिन्हित पूर्णांक rxfilter);
व्योम ath9k_cmn_rx_skb_postprocess(काष्ठा ath_common *common,
				  काष्ठा sk_buff *skb,
				  काष्ठा ath_rx_status *rx_stats,
				  काष्ठा ieee80211_rx_status *rxs,
				  bool decrypt_error);
पूर्णांक ath9k_cmn_process_rate(काष्ठा ath_common *common,
			   काष्ठा ieee80211_hw *hw,
			   काष्ठा ath_rx_status *rx_stats,
			   काष्ठा ieee80211_rx_status *rxs);
व्योम ath9k_cmn_process_rssi(काष्ठा ath_common *common,
			    काष्ठा ieee80211_hw *hw,
			    काष्ठा ath_rx_status *rx_stats,
			    काष्ठा ieee80211_rx_status *rxs);
पूर्णांक ath9k_cmn_get_hw_crypto_keytype(काष्ठा sk_buff *skb);
काष्ठा ath9k_channel *ath9k_cmn_get_channel(काष्ठा ieee80211_hw *hw,
					    काष्ठा ath_hw *ah,
					    काष्ठा cfg80211_chan_def *chandef);
पूर्णांक ath9k_cmn_count_streams(अचिन्हित पूर्णांक chainmask, पूर्णांक max);
व्योम ath9k_cmn_btcoex_bt_stomp(काष्ठा ath_common *common,
				  क्रमागत ath_stomp_type stomp_type);
व्योम ath9k_cmn_update_txघात(काष्ठा ath_hw *ah, u16 cur_txघात,
			    u16 new_txघात, u16 *txघातer);
व्योम ath9k_cmn_init_crypto(काष्ठा ath_hw *ah);
