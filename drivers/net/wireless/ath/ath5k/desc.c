<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2007-2008 Pavel Roskin <proski@gnu.org>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
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
 *
 */

/******************************\
 Hardware Descriptor Functions
\******************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"


/**
 * DOC: Hardware descriptor functions
 *
 * Here we handle the processing of the low-level hw descriptors
 * that hw पढ़ोs and ग_लिखोs via DMA क्रम each TX and RX attempt (that means
 * we can also have descriptors क्रम failed TX/RX tries). We have two kind of
 * descriptors क्रम RX and TX, control descriptors tell the hw how to send or
 * receive a packet where to पढ़ो/ग_लिखो it from/to etc and status descriptors
 * that contain inक्रमmation about how the packet was sent or received (errors
 * included).
 *
 * Descriptor क्रमmat is not exactly the same क्रम each MAC chip version so we
 * have function poपूर्णांकers on &काष्ठा ath5k_hw we initialize at runसमय based on
 * the chip used.
 */


/************************\
* TX Control descriptors *
\************************/

/**
 * ath5k_hw_setup_2word_tx_desc() - Initialize a 2-word tx control descriptor
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @pkt_len: Frame length in bytes
 * @hdr_len: Header length in bytes (only used on AR5210)
 * @padsize: Any padding we've added to the frame length
 * @type: One of क्रमागत ath5k_pkt_type
 * @tx_घातer: Tx घातer in 0.5dB steps
 * @tx_rate0: HW idx क्रम transmission rate
 * @tx_tries0: Max number of retransmissions
 * @key_index: Index on key table to use क्रम encryption
 * @antenna_mode: Which antenna to use (0 क्रम स्वतः)
 * @flags: One of AR5K_TXDESC_* flags (desc.h)
 * @rtscts_rate: HW idx क्रम RTS/CTS transmission rate
 * @rtscts_duration: What to put on duration field on the header of RTS/CTS
 *
 * Internal function to initialize a 2-Word TX control descriptor
 * found on AR5210 and AR5211 MACs chips.
 *
 * Returns 0 on success or -EINVAL on false input
 */
अटल पूर्णांक
ath5k_hw_setup_2word_tx_desc(काष्ठा ath5k_hw *ah,
			काष्ठा ath5k_desc *desc,
			अचिन्हित पूर्णांक pkt_len, अचिन्हित पूर्णांक hdr_len,
			पूर्णांक padsize,
			क्रमागत ath5k_pkt_type type,
			अचिन्हित पूर्णांक tx_घातer,
			अचिन्हित पूर्णांक tx_rate0, अचिन्हित पूर्णांक tx_tries0,
			अचिन्हित पूर्णांक key_index,
			अचिन्हित पूर्णांक antenna_mode,
			अचिन्हित पूर्णांक flags,
			अचिन्हित पूर्णांक rtscts_rate, अचिन्हित पूर्णांक rtscts_duration)
अणु
	u32 frame_type;
	काष्ठा ath5k_hw_2w_tx_ctl *tx_ctl;
	अचिन्हित पूर्णांक frame_len;

	tx_ctl = &desc->ud.ds_tx5210.tx_ctl;

	/*
	 * Validate input
	 * - Zero retries करोn't make sense.
	 * - A zero rate will put the HW पूर्णांकo a mode where it continuously sends
	 *   noise on the channel, so it is important to aव्योम this.
	 */
	अगर (unlikely(tx_tries0 == 0)) अणु
		ATH5K_ERR(ah, "zero retries\n");
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(tx_rate0 == 0)) अणु
		ATH5K_ERR(ah, "zero rate\n");
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	/* Clear descriptor */
	स_रखो(&desc->ud.ds_tx5210, 0, माप(काष्ठा ath5k_hw_5210_tx_desc));

	/* Setup control descriptor */

	/* Verअगरy and set frame length */

	/* हटाओ padding we might have added beक्रमe */
	frame_len = pkt_len - padsize + FCS_LEN;

	अगर (frame_len & ~AR5K_2W_TX_DESC_CTL0_FRAME_LEN)
		वापस -EINVAL;

	tx_ctl->tx_control_0 = frame_len & AR5K_2W_TX_DESC_CTL0_FRAME_LEN;

	/* Verअगरy and set buffer length */

	/* NB: beacon's BufLen must be a multiple of 4 bytes */
	अगर (type == AR5K_PKT_TYPE_BEACON)
		pkt_len = roundup(pkt_len, 4);

	अगर (pkt_len & ~AR5K_2W_TX_DESC_CTL1_BUF_LEN)
		वापस -EINVAL;

	tx_ctl->tx_control_1 = pkt_len & AR5K_2W_TX_DESC_CTL1_BUF_LEN;

	/*
	 * Verअगरy and set header length (only 5210)
	 */
	अगर (ah->ah_version == AR5K_AR5210) अणु
		अगर (hdr_len & ~AR5K_2W_TX_DESC_CTL0_HEADER_LEN_5210)
			वापस -EINVAL;
		tx_ctl->tx_control_0 |=
			AR5K_REG_SM(hdr_len, AR5K_2W_TX_DESC_CTL0_HEADER_LEN_5210);
	पूर्ण

	/*Dअगरferences between 5210-5211*/
	अगर (ah->ah_version == AR5K_AR5210) अणु
		चयन (type) अणु
		हाल AR5K_PKT_TYPE_BEACON:
		हाल AR5K_PKT_TYPE_PROBE_RESP:
			frame_type = AR5K_AR5210_TX_DESC_FRAME_TYPE_NO_DELAY;
			अवरोध;
		हाल AR5K_PKT_TYPE_PIFS:
			frame_type = AR5K_AR5210_TX_DESC_FRAME_TYPE_PIFS;
			अवरोध;
		शेष:
			frame_type = type;
			अवरोध;
		पूर्ण

		tx_ctl->tx_control_0 |=
		AR5K_REG_SM(frame_type, AR5K_2W_TX_DESC_CTL0_FRAME_TYPE_5210) |
		AR5K_REG_SM(tx_rate0, AR5K_2W_TX_DESC_CTL0_XMIT_RATE);

	पूर्ण अन्यथा अणु
		tx_ctl->tx_control_0 |=
			AR5K_REG_SM(tx_rate0, AR5K_2W_TX_DESC_CTL0_XMIT_RATE) |
			AR5K_REG_SM(antenna_mode,
				AR5K_2W_TX_DESC_CTL0_ANT_MODE_XMIT);
		tx_ctl->tx_control_1 |=
			AR5K_REG_SM(type, AR5K_2W_TX_DESC_CTL1_FRAME_TYPE_5211);
	पूर्ण

#घोषणा _TX_FLAGS(_c, _flag)					\
	अगर (flags & AR5K_TXDESC_##_flag) अणु			\
		tx_ctl->tx_control_##_c |=			\
			AR5K_2W_TX_DESC_CTL##_c##_##_flag;	\
	पूर्ण
#घोषणा _TX_FLAGS_5211(_c, _flag)					\
	अगर (flags & AR5K_TXDESC_##_flag) अणु				\
		tx_ctl->tx_control_##_c |=				\
			AR5K_2W_TX_DESC_CTL##_c##_##_flag##_5211;	\
	पूर्ण
	_TX_FLAGS(0, CLRDMASK);
	_TX_FLAGS(0, INTREQ);
	_TX_FLAGS(0, RTSENA);

	अगर (ah->ah_version == AR5K_AR5211) अणु
		_TX_FLAGS_5211(0, VEOL);
		_TX_FLAGS_5211(1, NOACK);
	पूर्ण

#अघोषित _TX_FLAGS
#अघोषित _TX_FLAGS_5211

	/*
	 * WEP crap
	 */
	अगर (key_index != AR5K_TXKEYIX_INVALID) अणु
		tx_ctl->tx_control_0 |=
			AR5K_2W_TX_DESC_CTL0_ENCRYPT_KEY_VALID;
		tx_ctl->tx_control_1 |=
			AR5K_REG_SM(key_index,
			AR5K_2W_TX_DESC_CTL1_ENC_KEY_IDX);
	पूर्ण

	/*
	 * RTS/CTS Duration [5210 ?]
	 */
	अगर ((ah->ah_version == AR5K_AR5210) &&
			(flags & (AR5K_TXDESC_RTSENA | AR5K_TXDESC_CTSENA)))
		tx_ctl->tx_control_1 |= rtscts_duration &
				AR5K_2W_TX_DESC_CTL1_RTS_DURATION_5210;

	वापस 0;
पूर्ण

/**
 * ath5k_hw_setup_4word_tx_desc() - Initialize a 4-word tx control descriptor
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @pkt_len: Frame length in bytes
 * @hdr_len: Header length in bytes (only used on AR5210)
 * @padsize: Any padding we've added to the frame length
 * @type: One of क्रमागत ath5k_pkt_type
 * @tx_घातer: Tx घातer in 0.5dB steps
 * @tx_rate0: HW idx क्रम transmission rate
 * @tx_tries0: Max number of retransmissions
 * @key_index: Index on key table to use क्रम encryption
 * @antenna_mode: Which antenna to use (0 क्रम स्वतः)
 * @flags: One of AR5K_TXDESC_* flags (desc.h)
 * @rtscts_rate: HW idx क्रम RTS/CTS transmission rate
 * @rtscts_duration: What to put on duration field on the header of RTS/CTS
 *
 * Internal function to initialize a 4-Word TX control descriptor
 * found on AR5212 and later MACs chips.
 *
 * Returns 0 on success or -EINVAL on false input
 */
अटल पूर्णांक
ath5k_hw_setup_4word_tx_desc(काष्ठा ath5k_hw *ah,
			काष्ठा ath5k_desc *desc,
			अचिन्हित पूर्णांक pkt_len, अचिन्हित पूर्णांक hdr_len,
			पूर्णांक padsize,
			क्रमागत ath5k_pkt_type type,
			अचिन्हित पूर्णांक tx_घातer,
			अचिन्हित पूर्णांक tx_rate0, अचिन्हित पूर्णांक tx_tries0,
			अचिन्हित पूर्णांक key_index,
			अचिन्हित पूर्णांक antenna_mode,
			अचिन्हित पूर्णांक flags,
			अचिन्हित पूर्णांक rtscts_rate, अचिन्हित पूर्णांक rtscts_duration)
अणु
	काष्ठा ath5k_hw_4w_tx_ctl *tx_ctl;
	अचिन्हित पूर्णांक frame_len;

	/*
	 * Use local variables क्रम these to reduce load/store access on
	 * uncached memory
	 */
	u32 txctl0 = 0, txctl1 = 0, txctl2 = 0, txctl3 = 0;

	tx_ctl = &desc->ud.ds_tx5212.tx_ctl;

	/*
	 * Validate input
	 * - Zero retries करोn't make sense.
	 * - A zero rate will put the HW पूर्णांकo a mode where it continuously sends
	 *   noise on the channel, so it is important to aव्योम this.
	 */
	अगर (unlikely(tx_tries0 == 0)) अणु
		ATH5K_ERR(ah, "zero retries\n");
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(tx_rate0 == 0)) अणु
		ATH5K_ERR(ah, "zero rate\n");
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	tx_घातer += ah->ah_txघातer.txp_offset;
	अगर (tx_घातer > AR5K_TUNE_MAX_TXPOWER)
		tx_घातer = AR5K_TUNE_MAX_TXPOWER;

	/* Clear descriptor status area */
	स_रखो(&desc->ud.ds_tx5212.tx_stat, 0,
	       माप(desc->ud.ds_tx5212.tx_stat));

	/* Setup control descriptor */

	/* Verअगरy and set frame length */

	/* हटाओ padding we might have added beक्रमe */
	frame_len = pkt_len - padsize + FCS_LEN;

	अगर (frame_len & ~AR5K_4W_TX_DESC_CTL0_FRAME_LEN)
		वापस -EINVAL;

	txctl0 = frame_len & AR5K_4W_TX_DESC_CTL0_FRAME_LEN;

	/* Verअगरy and set buffer length */

	/* NB: beacon's BufLen must be a multiple of 4 bytes */
	अगर (type == AR5K_PKT_TYPE_BEACON)
		pkt_len = roundup(pkt_len, 4);

	अगर (pkt_len & ~AR5K_4W_TX_DESC_CTL1_BUF_LEN)
		वापस -EINVAL;

	txctl1 = pkt_len & AR5K_4W_TX_DESC_CTL1_BUF_LEN;

	txctl0 |= AR5K_REG_SM(tx_घातer, AR5K_4W_TX_DESC_CTL0_XMIT_POWER) |
		  AR5K_REG_SM(antenna_mode, AR5K_4W_TX_DESC_CTL0_ANT_MODE_XMIT);
	txctl1 |= AR5K_REG_SM(type, AR5K_4W_TX_DESC_CTL1_FRAME_TYPE);
	txctl2 = AR5K_REG_SM(tx_tries0, AR5K_4W_TX_DESC_CTL2_XMIT_TRIES0);
	txctl3 = tx_rate0 & AR5K_4W_TX_DESC_CTL3_XMIT_RATE0;

#घोषणा _TX_FLAGS(_c, _flag)					\
	अगर (flags & AR5K_TXDESC_##_flag) अणु			\
		txctl##_c |= AR5K_4W_TX_DESC_CTL##_c##_##_flag;	\
	पूर्ण

	_TX_FLAGS(0, CLRDMASK);
	_TX_FLAGS(0, VEOL);
	_TX_FLAGS(0, INTREQ);
	_TX_FLAGS(0, RTSENA);
	_TX_FLAGS(0, CTSENA);
	_TX_FLAGS(1, NOACK);

#अघोषित _TX_FLAGS

	/*
	 * WEP crap
	 */
	अगर (key_index != AR5K_TXKEYIX_INVALID) अणु
		txctl0 |= AR5K_4W_TX_DESC_CTL0_ENCRYPT_KEY_VALID;
		txctl1 |= AR5K_REG_SM(key_index,
				AR5K_4W_TX_DESC_CTL1_ENCRYPT_KEY_IDX);
	पूर्ण

	/*
	 * RTS/CTS
	 */
	अगर (flags & (AR5K_TXDESC_RTSENA | AR5K_TXDESC_CTSENA)) अणु
		अगर ((flags & AR5K_TXDESC_RTSENA) &&
				(flags & AR5K_TXDESC_CTSENA))
			वापस -EINVAL;
		txctl2 |= rtscts_duration & AR5K_4W_TX_DESC_CTL2_RTS_DURATION;
		txctl3 |= AR5K_REG_SM(rtscts_rate,
				AR5K_4W_TX_DESC_CTL3_RTS_CTS_RATE);
	पूर्ण

	tx_ctl->tx_control_0 = txctl0;
	tx_ctl->tx_control_1 = txctl1;
	tx_ctl->tx_control_2 = txctl2;
	tx_ctl->tx_control_3 = txctl3;

	वापस 0;
पूर्ण

/**
 * ath5k_hw_setup_mrr_tx_desc() - Initialize an MRR tx control descriptor
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @tx_rate1: HW idx क्रम rate used on transmission series 1
 * @tx_tries1: Max number of retransmissions क्रम transmission series 1
 * @tx_rate2: HW idx क्रम rate used on transmission series 2
 * @tx_tries2: Max number of retransmissions क्रम transmission series 2
 * @tx_rate3: HW idx क्रम rate used on transmission series 3
 * @tx_tries3: Max number of retransmissions क्रम transmission series 3
 *
 * Multi rate retry (MRR) tx control descriptors are available only on AR5212
 * MACs, they are part of the normal 4-word tx control descriptor (see above)
 * but we handle them through a separate function क्रम better असलtraction.
 *
 * Returns 0 on success or -EINVAL on invalid input
 */
पूर्णांक
ath5k_hw_setup_mrr_tx_desc(काष्ठा ath5k_hw *ah,
			काष्ठा ath5k_desc *desc,
			u_पूर्णांक tx_rate1, u_पूर्णांक tx_tries1,
			u_पूर्णांक tx_rate2, u_पूर्णांक tx_tries2,
			u_पूर्णांक tx_rate3, u_पूर्णांक tx_tries3)
अणु
	काष्ठा ath5k_hw_4w_tx_ctl *tx_ctl;

	/* no mrr support क्रम cards older than 5212 */
	अगर (ah->ah_version < AR5K_AR5212)
		वापस 0;

	/*
	 * Rates can be 0 as दीर्घ as the retry count is 0 too.
	 * A zero rate and nonzero retry count will put the HW पूर्णांकo a mode where
	 * it continuously sends noise on the channel, so it is important to
	 * aव्योम this.
	 */
	अगर (unlikely((tx_rate1 == 0 && tx_tries1 != 0) ||
		     (tx_rate2 == 0 && tx_tries2 != 0) ||
		     (tx_rate3 == 0 && tx_tries3 != 0))) अणु
		ATH5K_ERR(ah, "zero rate\n");
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (ah->ah_version == AR5K_AR5212) अणु
		tx_ctl = &desc->ud.ds_tx5212.tx_ctl;

#घोषणा _XTX_TRIES(_n)							\
	अगर (tx_tries##_n) अणु						\
		tx_ctl->tx_control_2 |=					\
		    AR5K_REG_SM(tx_tries##_n,				\
		    AR5K_4W_TX_DESC_CTL2_XMIT_TRIES##_n);		\
		tx_ctl->tx_control_3 |=					\
		    AR5K_REG_SM(tx_rate##_n,				\
		    AR5K_4W_TX_DESC_CTL3_XMIT_RATE##_n);		\
	पूर्ण

		_XTX_TRIES(1);
		_XTX_TRIES(2);
		_XTX_TRIES(3);

#अघोषित _XTX_TRIES

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


/***********************\
* TX Status descriptors *
\***********************/

/**
 * ath5k_hw_proc_2word_tx_status() - Process a tx status descriptor on 5210/1
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @ts: The &काष्ठा ath5k_tx_status
 */
अटल पूर्णांक
ath5k_hw_proc_2word_tx_status(काष्ठा ath5k_hw *ah,
				काष्ठा ath5k_desc *desc,
				काष्ठा ath5k_tx_status *ts)
अणु
	काष्ठा ath5k_hw_tx_status *tx_status;

	tx_status = &desc->ud.ds_tx5210.tx_stat;

	/* No frame has been send or error */
	अगर (unlikely((tx_status->tx_status_1 & AR5K_DESC_TX_STATUS1_DONE) == 0))
		वापस -EINPROGRESS;

	/*
	 * Get descriptor status
	 */
	ts->ts_tstamp = AR5K_REG_MS(tx_status->tx_status_0,
		AR5K_DESC_TX_STATUS0_SEND_TIMESTAMP);
	ts->ts_लघुretry = AR5K_REG_MS(tx_status->tx_status_0,
		AR5K_DESC_TX_STATUS0_SHORT_RETRY_COUNT);
	ts->ts_final_retry = AR5K_REG_MS(tx_status->tx_status_0,
		AR5K_DESC_TX_STATUS0_LONG_RETRY_COUNT);
	/*TODO: ts->ts_virtcol + test*/
	ts->ts_seqnum = AR5K_REG_MS(tx_status->tx_status_1,
		AR5K_DESC_TX_STATUS1_SEQ_NUM);
	ts->ts_rssi = AR5K_REG_MS(tx_status->tx_status_1,
		AR5K_DESC_TX_STATUS1_ACK_SIG_STRENGTH);
	ts->ts_antenna = 1;
	ts->ts_status = 0;
	ts->ts_final_idx = 0;

	अगर (!(tx_status->tx_status_0 & AR5K_DESC_TX_STATUS0_FRAME_XMIT_OK)) अणु
		अगर (tx_status->tx_status_0 &
				AR5K_DESC_TX_STATUS0_EXCESSIVE_RETRIES)
			ts->ts_status |= AR5K_TXERR_XRETRY;

		अगर (tx_status->tx_status_0 & AR5K_DESC_TX_STATUS0_FIFO_UNDERRUN)
			ts->ts_status |= AR5K_TXERR_FIFO;

		अगर (tx_status->tx_status_0 & AR5K_DESC_TX_STATUS0_FILTERED)
			ts->ts_status |= AR5K_TXERR_FILT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ath5k_hw_proc_4word_tx_status() - Process a tx status descriptor on 5212
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @ts: The &काष्ठा ath5k_tx_status
 */
अटल पूर्णांक
ath5k_hw_proc_4word_tx_status(काष्ठा ath5k_hw *ah,
				काष्ठा ath5k_desc *desc,
				काष्ठा ath5k_tx_status *ts)
अणु
	काष्ठा ath5k_hw_tx_status *tx_status;
	u32 txstat0, txstat1;

	tx_status = &desc->ud.ds_tx5212.tx_stat;

	txstat1 = READ_ONCE(tx_status->tx_status_1);

	/* No frame has been send or error */
	अगर (unlikely(!(txstat1 & AR5K_DESC_TX_STATUS1_DONE)))
		वापस -EINPROGRESS;

	txstat0 = READ_ONCE(tx_status->tx_status_0);

	/*
	 * Get descriptor status
	 */
	ts->ts_tstamp = AR5K_REG_MS(txstat0,
		AR5K_DESC_TX_STATUS0_SEND_TIMESTAMP);
	ts->ts_लघुretry = AR5K_REG_MS(txstat0,
		AR5K_DESC_TX_STATUS0_SHORT_RETRY_COUNT);
	ts->ts_final_retry = AR5K_REG_MS(txstat0,
		AR5K_DESC_TX_STATUS0_LONG_RETRY_COUNT);
	ts->ts_seqnum = AR5K_REG_MS(txstat1,
		AR5K_DESC_TX_STATUS1_SEQ_NUM);
	ts->ts_rssi = AR5K_REG_MS(txstat1,
		AR5K_DESC_TX_STATUS1_ACK_SIG_STRENGTH);
	ts->ts_antenna = (txstat1 &
		AR5K_DESC_TX_STATUS1_XMIT_ANTENNA_5212) ? 2 : 1;
	ts->ts_status = 0;

	ts->ts_final_idx = AR5K_REG_MS(txstat1,
			AR5K_DESC_TX_STATUS1_FINAL_TS_IX_5212);

	/* TX error */
	अगर (!(txstat0 & AR5K_DESC_TX_STATUS0_FRAME_XMIT_OK)) अणु
		अगर (txstat0 & AR5K_DESC_TX_STATUS0_EXCESSIVE_RETRIES)
			ts->ts_status |= AR5K_TXERR_XRETRY;

		अगर (txstat0 & AR5K_DESC_TX_STATUS0_FIFO_UNDERRUN)
			ts->ts_status |= AR5K_TXERR_FIFO;

		अगर (txstat0 & AR5K_DESC_TX_STATUS0_FILTERED)
			ts->ts_status |= AR5K_TXERR_FILT;
	पूर्ण

	वापस 0;
पूर्ण


/****************\
* RX Descriptors *
\****************/

/**
 * ath5k_hw_setup_rx_desc() - Initialize an rx control descriptor
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @size: RX buffer length in bytes
 * @flags: One of AR5K_RXDESC_* flags
 */
पूर्णांक
ath5k_hw_setup_rx_desc(काष्ठा ath5k_hw *ah,
			काष्ठा ath5k_desc *desc,
			u32 size, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ath5k_hw_rx_ctl *rx_ctl;

	rx_ctl = &desc->ud.ds_rx.rx_ctl;

	/*
	 * Clear the descriptor
	 * If we करोn't clean the status descriptor,
	 * जबतक scanning we get too many results,
	 * most of them भव, after some secs
	 * of scanning प्रणाली hangs. M.F.
	*/
	स_रखो(&desc->ud.ds_rx, 0, माप(काष्ठा ath5k_hw_all_rx_desc));

	अगर (unlikely(size & ~AR5K_DESC_RX_CTL1_BUF_LEN))
		वापस -EINVAL;

	/* Setup descriptor */
	rx_ctl->rx_control_1 = size & AR5K_DESC_RX_CTL1_BUF_LEN;

	अगर (flags & AR5K_RXDESC_INTREQ)
		rx_ctl->rx_control_1 |= AR5K_DESC_RX_CTL1_INTREQ;

	वापस 0;
पूर्ण

/**
 * ath5k_hw_proc_5210_rx_status() - Process the rx status descriptor on 5210/1
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @rs: The &काष्ठा ath5k_rx_status
 *
 * Internal function used to process an RX status descriptor
 * on AR5210/5211 MAC.
 *
 * Returns 0 on success or -EINPROGRESS in हाल we haven't received the who;e
 * frame yet.
 */
अटल पूर्णांक
ath5k_hw_proc_5210_rx_status(काष्ठा ath5k_hw *ah,
				काष्ठा ath5k_desc *desc,
				काष्ठा ath5k_rx_status *rs)
अणु
	काष्ठा ath5k_hw_rx_status *rx_status;

	rx_status = &desc->ud.ds_rx.rx_stat;

	/* No frame received / not पढ़ोy */
	अगर (unlikely(!(rx_status->rx_status_1 &
			AR5K_5210_RX_DESC_STATUS1_DONE)))
		वापस -EINPROGRESS;

	स_रखो(rs, 0, माप(काष्ठा ath5k_rx_status));

	/*
	 * Frame receive status
	 */
	rs->rs_datalen = rx_status->rx_status_0 &
		AR5K_5210_RX_DESC_STATUS0_DATA_LEN;
	rs->rs_rssi = AR5K_REG_MS(rx_status->rx_status_0,
		AR5K_5210_RX_DESC_STATUS0_RECEIVE_SIGNAL);
	rs->rs_rate = AR5K_REG_MS(rx_status->rx_status_0,
		AR5K_5210_RX_DESC_STATUS0_RECEIVE_RATE);
	rs->rs_more = !!(rx_status->rx_status_0 &
		AR5K_5210_RX_DESC_STATUS0_MORE);
	/* TODO: this बारtamp is 13 bit, later on we assume 15 bit!
	 * also the HAL code क्रम 5210 says the बारtamp is bits [10..22] of the
	 * TSF, and extends the बारtamp here to 15 bit.
	 * we need to check on 5210...
	 */
	rs->rs_tstamp = AR5K_REG_MS(rx_status->rx_status_1,
		AR5K_5210_RX_DESC_STATUS1_RECEIVE_TIMESTAMP);

	अगर (ah->ah_version == AR5K_AR5211)
		rs->rs_antenna = AR5K_REG_MS(rx_status->rx_status_0,
				AR5K_5210_RX_DESC_STATUS0_RECEIVE_ANT_5211);
	अन्यथा
		rs->rs_antenna = (rx_status->rx_status_0 &
				AR5K_5210_RX_DESC_STATUS0_RECEIVE_ANT_5210)
				? 2 : 1;

	/*
	 * Key table status
	 */
	अगर (rx_status->rx_status_1 & AR5K_5210_RX_DESC_STATUS1_KEY_INDEX_VALID)
		rs->rs_keyix = AR5K_REG_MS(rx_status->rx_status_1,
			AR5K_5210_RX_DESC_STATUS1_KEY_INDEX);
	अन्यथा
		rs->rs_keyix = AR5K_RXKEYIX_INVALID;

	/*
	 * Receive/descriptor errors
	 */
	अगर (!(rx_status->rx_status_1 &
			AR5K_5210_RX_DESC_STATUS1_FRAME_RECEIVE_OK)) अणु
		अगर (rx_status->rx_status_1 &
				AR5K_5210_RX_DESC_STATUS1_CRC_ERROR)
			rs->rs_status |= AR5K_RXERR_CRC;

		/* only on 5210 */
		अगर ((ah->ah_version == AR5K_AR5210) &&
		    (rx_status->rx_status_1 &
				AR5K_5210_RX_DESC_STATUS1_FIFO_OVERRUN_5210))
			rs->rs_status |= AR5K_RXERR_FIFO;

		अगर (rx_status->rx_status_1 &
				AR5K_5210_RX_DESC_STATUS1_PHY_ERROR) अणु
			rs->rs_status |= AR5K_RXERR_PHY;
			rs->rs_phyerr = AR5K_REG_MS(rx_status->rx_status_1,
				AR5K_5210_RX_DESC_STATUS1_PHY_ERROR);
		पूर्ण

		अगर (rx_status->rx_status_1 &
				AR5K_5210_RX_DESC_STATUS1_DECRYPT_CRC_ERROR)
			rs->rs_status |= AR5K_RXERR_DECRYPT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ath5k_hw_proc_5212_rx_status() - Process the rx status descriptor on 5212
 * @ah: The &काष्ठा ath5k_hw
 * @desc: The &काष्ठा ath5k_desc
 * @rs: The &काष्ठा ath5k_rx_status
 *
 * Internal function used to process an RX status descriptor
 * on AR5212 and later MAC.
 *
 * Returns 0 on success or -EINPROGRESS in हाल we haven't received the who;e
 * frame yet.
 */
अटल पूर्णांक
ath5k_hw_proc_5212_rx_status(काष्ठा ath5k_hw *ah,
				काष्ठा ath5k_desc *desc,
				काष्ठा ath5k_rx_status *rs)
अणु
	काष्ठा ath5k_hw_rx_status *rx_status;
	u32 rxstat0, rxstat1;

	rx_status = &desc->ud.ds_rx.rx_stat;
	rxstat1 = READ_ONCE(rx_status->rx_status_1);

	/* No frame received / not पढ़ोy */
	अगर (unlikely(!(rxstat1 & AR5K_5212_RX_DESC_STATUS1_DONE)))
		वापस -EINPROGRESS;

	स_रखो(rs, 0, माप(काष्ठा ath5k_rx_status));
	rxstat0 = READ_ONCE(rx_status->rx_status_0);

	/*
	 * Frame receive status
	 */
	rs->rs_datalen = rxstat0 & AR5K_5212_RX_DESC_STATUS0_DATA_LEN;
	rs->rs_rssi = AR5K_REG_MS(rxstat0,
		AR5K_5212_RX_DESC_STATUS0_RECEIVE_SIGNAL);
	rs->rs_rate = AR5K_REG_MS(rxstat0,
		AR5K_5212_RX_DESC_STATUS0_RECEIVE_RATE);
	rs->rs_antenna = AR5K_REG_MS(rxstat0,
		AR5K_5212_RX_DESC_STATUS0_RECEIVE_ANTENNA);
	rs->rs_more = !!(rxstat0 & AR5K_5212_RX_DESC_STATUS0_MORE);
	rs->rs_tstamp = AR5K_REG_MS(rxstat1,
		AR5K_5212_RX_DESC_STATUS1_RECEIVE_TIMESTAMP);

	/*
	 * Key table status
	 */
	अगर (rxstat1 & AR5K_5212_RX_DESC_STATUS1_KEY_INDEX_VALID)
		rs->rs_keyix = AR5K_REG_MS(rxstat1,
					   AR5K_5212_RX_DESC_STATUS1_KEY_INDEX);
	अन्यथा
		rs->rs_keyix = AR5K_RXKEYIX_INVALID;

	/*
	 * Receive/descriptor errors
	 */
	अगर (!(rxstat1 & AR5K_5212_RX_DESC_STATUS1_FRAME_RECEIVE_OK)) अणु
		अगर (rxstat1 & AR5K_5212_RX_DESC_STATUS1_CRC_ERROR)
			rs->rs_status |= AR5K_RXERR_CRC;

		अगर (rxstat1 & AR5K_5212_RX_DESC_STATUS1_PHY_ERROR) अणु
			rs->rs_status |= AR5K_RXERR_PHY;
			rs->rs_phyerr = AR5K_REG_MS(rxstat1,
				AR5K_5212_RX_DESC_STATUS1_PHY_ERROR_CODE);
			अगर (!ah->ah_capabilities.cap_has_phyerr_counters)
				ath5k_ani_phy_error_report(ah, rs->rs_phyerr);
		पूर्ण

		अगर (rxstat1 & AR5K_5212_RX_DESC_STATUS1_DECRYPT_CRC_ERROR)
			rs->rs_status |= AR5K_RXERR_DECRYPT;

		अगर (rxstat1 & AR5K_5212_RX_DESC_STATUS1_MIC_ERROR)
			rs->rs_status |= AR5K_RXERR_MIC;
	पूर्ण
	वापस 0;
पूर्ण


/********\
* Attach *
\********/

/**
 * ath5k_hw_init_desc_functions() - Init function poपूर्णांकers inside ah
 * @ah: The &काष्ठा ath5k_hw
 *
 * Maps the पूर्णांकernal descriptor functions to the function poपूर्णांकers on ah, used
 * from above. This is used as an असलtraction layer to handle the various chips
 * the same way.
 */
पूर्णांक
ath5k_hw_init_desc_functions(काष्ठा ath5k_hw *ah)
अणु
	अगर (ah->ah_version == AR5K_AR5212) अणु
		ah->ah_setup_tx_desc = ath5k_hw_setup_4word_tx_desc;
		ah->ah_proc_tx_desc = ath5k_hw_proc_4word_tx_status;
		ah->ah_proc_rx_desc = ath5k_hw_proc_5212_rx_status;
	पूर्ण अन्यथा अगर (ah->ah_version <= AR5K_AR5211) अणु
		ah->ah_setup_tx_desc = ath5k_hw_setup_2word_tx_desc;
		ah->ah_proc_tx_desc = ath5k_hw_proc_2word_tx_status;
		ah->ah_proc_rx_desc = ath5k_hw_proc_5210_rx_status;
	पूर्ण अन्यथा
		वापस -ENOTSUPP;
	वापस 0;
पूर्ण
