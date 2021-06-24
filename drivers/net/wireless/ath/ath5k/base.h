<शैली गुरु>
/*-
 * Copyright (c) 2002-2007 Sam Leffler, Errno Consulting
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement क्रम further binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 */

/*
 * Definitions क्रम the Atheros Wireless LAN controller driver.
 */
#अगर_अघोषित _DEV_ATH5K_BASE_H
#घोषणा _DEV_ATH5K_BASE_H

काष्ठा ieee80211_vअगर;
काष्ठा ieee80211_hw;
काष्ठा ath5k_hw;
काष्ठा ath5k_txq;
काष्ठा ieee80211_channel;
काष्ठा ath_bus_ops;
काष्ठा ieee80211_tx_control;
क्रमागत nl80211_अगरtype;

क्रमागत ath5k_srev_type अणु
	AR5K_VERSION_MAC,
	AR5K_VERSION_RAD,
पूर्ण;

काष्ठा ath5k_srev_name अणु
	स्थिर अक्षर		*sr_name;
	क्रमागत ath5k_srev_type	sr_type;
	u_पूर्णांक			sr_val;
पूर्ण;

काष्ठा ath5k_buf अणु
	काष्ठा list_head		list;
	काष्ठा ath5k_desc		*desc;		/* भव addr of desc */
	dma_addr_t			daddr;		/* physical addr of desc */
	काष्ठा sk_buff			*skb;		/* skbuff क्रम buf */
	dma_addr_t			skbaddr;	/* physical addr of skb data */
	काष्ठा ieee80211_tx_rate	rates[4];	/* number of multi-rate stages */
पूर्ण;

काष्ठा ath5k_vअगर अणु
	bool			assoc; /* are we associated or not */
	क्रमागत nl80211_अगरtype	opmode;
	पूर्णांक			bslot;
	काष्ठा ath5k_buf	*bbuf; /* beacon buffer */
पूर्ण;

काष्ठा ath5k_vअगर_iter_data अणु
	स्थिर u8	*hw_macaddr;
	u8		mask[ETH_ALEN];
	u8		active_mac[ETH_ALEN]; /* first active MAC */
	bool		need_set_hw_addr;
	bool		found_active;
	bool		any_assoc;
	क्रमागत nl80211_अगरtype opmode;
	पूर्णांक n_stas;
पूर्ण;

व्योम ath5k_vअगर_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर);
bool ath5k_any_vअगर_assoc(काष्ठा ath5k_hw *ah);

पूर्णांक ath5k_start(काष्ठा ieee80211_hw *hw);
व्योम ath5k_stop(काष्ठा ieee80211_hw *hw);

व्योम ath5k_beacon_update_समयrs(काष्ठा ath5k_hw *ah, u64 bc_tsf);
पूर्णांक ath5k_beacon_update(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
व्योम ath5k_beacon_config(काष्ठा ath5k_hw *ah);
व्योम ath5k_set_beacon_filter(काष्ठा ieee80211_hw *hw, bool enable);

व्योम ath5k_update_bssid_mask_and_opmode(काष्ठा ath5k_hw *ah,
					काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक ath5k_chan_set(काष्ठा ath5k_hw *ah, काष्ठा cfg80211_chan_def *chandef);
व्योम ath5k_txbuf_मुक्त_skb(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf);
व्योम ath5k_rxbuf_मुक्त_skb(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf);
व्योम ath5k_tx_queue(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
		    काष्ठा ath5k_txq *txq, काष्ठा ieee80211_tx_control *control);

स्थिर अक्षर *ath5k_chip_name(क्रमागत ath5k_srev_type type, u_पूर्णांक16_t val);

पूर्णांक ath5k_init_ah(काष्ठा ath5k_hw *ah, स्थिर काष्ठा ath_bus_ops *bus_ops);
व्योम ath5k_deinit_ah(काष्ठा ath5k_hw *ah);

/* Check whether BSSID mask is supported */
#घोषणा ath5k_hw_hasbssidmask(_ah) (ah->ah_version == AR5K_AR5212)

/* Check whether भव EOL is supported */
#घोषणा ath5k_hw_hasveol(_ah) (ah->ah_version != AR5K_AR5210)

#पूर्ण_अगर	/* _DEV_ATH5K_BASE_H */
