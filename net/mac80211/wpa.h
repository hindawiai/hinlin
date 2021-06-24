<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2002-2004, Instant802 Networks, Inc.
 */

#अगर_अघोषित WPA_H
#घोषणा WPA_H

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश "ieee80211_i.h"

ieee80211_tx_result
ieee80211_tx_h_michael_mic_add(काष्ठा ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_rx_h_michael_mic_verअगरy(काष्ठा ieee80211_rx_data *rx);

ieee80211_tx_result
ieee80211_crypto_tkip_encrypt(काष्ठा ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_tkip_decrypt(काष्ठा ieee80211_rx_data *rx);

ieee80211_tx_result
ieee80211_crypto_ccmp_encrypt(काष्ठा ieee80211_tx_data *tx,
			      अचिन्हित पूर्णांक mic_len);
ieee80211_rx_result
ieee80211_crypto_ccmp_decrypt(काष्ठा ieee80211_rx_data *rx,
			      अचिन्हित पूर्णांक mic_len);

ieee80211_tx_result
ieee80211_crypto_aes_cmac_encrypt(काष्ठा ieee80211_tx_data *tx);
ieee80211_tx_result
ieee80211_crypto_aes_cmac_256_encrypt(काष्ठा ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_aes_cmac_decrypt(काष्ठा ieee80211_rx_data *rx);
ieee80211_rx_result
ieee80211_crypto_aes_cmac_256_decrypt(काष्ठा ieee80211_rx_data *rx);
ieee80211_tx_result
ieee80211_crypto_aes_gmac_encrypt(काष्ठा ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_aes_gmac_decrypt(काष्ठा ieee80211_rx_data *rx);
ieee80211_tx_result
ieee80211_crypto_hw_encrypt(काष्ठा ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_hw_decrypt(काष्ठा ieee80211_rx_data *rx);

ieee80211_tx_result
ieee80211_crypto_gcmp_encrypt(काष्ठा ieee80211_tx_data *tx);
ieee80211_rx_result
ieee80211_crypto_gcmp_decrypt(काष्ठा ieee80211_rx_data *rx);

#पूर्ण_अगर /* WPA_H */
