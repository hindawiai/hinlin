<शैली गुरु>
/*
 * Copyright (c) 2009 Atheros Communications Inc.
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
#समावेश <यंत्र/unaligned.h>

#समावेश "ath.h"
#समावेश "reg.h"

#घोषणा REG_READ			(common->ops->पढ़ो)
#घोषणा REG_WRITE(_ah, _reg, _val)	(common->ops->ग_लिखो)(_ah, _val, _reg)

/**
 * ath_hw_set_bssid_mask - filter out bssids we listen
 *
 * @common: the ath_common काष्ठा क्रम the device.
 *
 * BSSID masking is a method used by AR5212 and newer hardware to inक्रमm PCU
 * which bits of the पूर्णांकerface's MAC address should be looked at when trying
 * to decide which packets to ACK. In station mode and AP mode with a single
 * BSS every bit matters since we lock to only one BSS. In AP mode with
 * multiple BSSes (भव पूर्णांकerfaces) not every bit matters because hw must
 * accept frames क्रम all BSSes and so we tweak some bits of our mac address
 * in order to have multiple BSSes.
 *
 * NOTE: This is a simple filter and करोes *not* filter out all
 * relevant frames. Some frames that are not क्रम us might get ACKed from us
 * by PCU because they just match the mask.
 *
 * When handling multiple BSSes you can get the BSSID mask by computing the
 * set of  ~ ( MAC XOR BSSID ) क्रम all bssids we handle.
 *
 * When you करो this you are essentially computing the common bits of all your
 * BSSes. Later it is assumed the hardware will "and" (&) the BSSID mask with
 * the MAC address to obtain the relevant bits and compare the result with
 * (frame's BSSID & mask) to see अगर they match.
 *
 * Simple example: on your card you have have two BSSes you have created with
 * BSSID-01 and BSSID-02. Lets assume BSSID-01 will not use the MAC address.
 * There is another BSSID-03 but you are not part of it. For simplicity's sake,
 * assuming only 4 bits क्रम a mac address and क्रम BSSIDs you can then have:
 *
 *                  \
 * MAC:        0001 |
 * BSSID-01:   0100 | --> Beदीर्घs to us
 * BSSID-02:   1001 |
 *                  /
 * -------------------
 * BSSID-03:   0110  | --> External
 * -------------------
 *
 * Our bssid_mask would then be:
 *
 *             On loop iteration क्रम BSSID-01:
 *             ~(0001 ^ 0100)  -> ~(0101)
 *                             ->   1010
 *             bssid_mask      =    1010
 *
 *             On loop iteration क्रम BSSID-02:
 *             bssid_mask &= ~(0001   ^   1001)
 *             bssid_mask =   (1010)  & ~(0001 ^ 1001)
 *             bssid_mask =   (1010)  & ~(1000)
 *             bssid_mask =   (1010)  &  (0111)
 *             bssid_mask =   0010
 *
 * A bssid_mask of 0010 means "only pay attention to the second least
 * signअगरicant bit". This is because its the only bit common
 * amongst the MAC and all BSSIDs we support. To finकरोut what the real
 * common bit is we can simply "&" the bssid_mask now with any BSSID we have
 * or our MAC address (we assume the hardware uses the MAC address).
 *
 * Now, suppose there's an incoming frame क्रम BSSID-03:
 *
 * IFRAME-01:  0110
 *
 * An easy eye-inspeciton of this alपढ़ोy should tell you that this frame
 * will not pass our check. This is because the bssid_mask tells the
 * hardware to only look at the second least signअगरicant bit and the
 * common bit amongst the MAC and BSSIDs is 0, this frame has the 2nd LSB
 * as 1, which करोes not match 0.
 *
 * So with IFRAME-01 we *assume* the hardware will करो:
 *
 *     allow = (IFRAME-01 & bssid_mask) == (bssid_mask & MAC) ? 1 : 0;
 *  --> allow = (0110 & 0010) == (0010 & 0001) ? 1 : 0;
 *  --> allow = (0010) == 0000 ? 1 : 0;
 *  --> allow = 0
 *
 *  Lets now test a frame that should work:
 *
 * IFRAME-02:  0001 (we should allow)
 *
 *     allow = (IFRAME-02 & bssid_mask) == (bssid_mask & MAC) ? 1 : 0;
 *  --> allow = (0001 & 0010) ==  (0010 & 0001) ? 1 :0;
 *  --> allow = (0000) == (0000)
 *  --> allow = 1
 *
 * Other examples:
 *
 * IFRAME-03:  0100 --> allowed
 * IFRAME-04:  1001 --> allowed
 * IFRAME-05:  1101 --> allowed but its not क्रम us!!!
 *
 */
व्योम ath_hw_setbssidmask(काष्ठा ath_common *common)
अणु
	व्योम *ah = common->ah;
	u32 id1;

	REG_WRITE(ah, AR_STA_ID0, get_unaligned_le32(common->macaddr));
	id1 = REG_READ(ah, AR_STA_ID1) & ~AR_STA_ID1_SADH_MASK;
	id1 |= get_unaligned_le16(common->macaddr + 4);
	REG_WRITE(ah, AR_STA_ID1, id1);

	REG_WRITE(ah, AR_BSSMSKL, get_unaligned_le32(common->bssidmask));
	REG_WRITE(ah, AR_BSSMSKU, get_unaligned_le16(common->bssidmask + 4));
पूर्ण
EXPORT_SYMBOL(ath_hw_setbssidmask);


/**
 * ath_hw_cycle_counters_update - common function to update cycle counters
 *
 * @common: the ath_common काष्ठा क्रम the device.
 *
 * This function is used to update all cycle counters in one place.
 * It has to be called जबतक holding common->cc_lock!
 */
व्योम ath_hw_cycle_counters_update(काष्ठा ath_common *common)
अणु
	u32 cycles, busy, rx, tx;
	व्योम *ah = common->ah;

	/* मुक्तze */
	REG_WRITE(ah, AR_MIBC, AR_MIBC_FMC);

	/* पढ़ो */
	cycles = REG_READ(ah, AR_CCCNT);
	busy = REG_READ(ah, AR_RCCNT);
	rx = REG_READ(ah, AR_RFCNT);
	tx = REG_READ(ah, AR_TFCNT);

	/* clear */
	REG_WRITE(ah, AR_CCCNT, 0);
	REG_WRITE(ah, AR_RFCNT, 0);
	REG_WRITE(ah, AR_RCCNT, 0);
	REG_WRITE(ah, AR_TFCNT, 0);

	/* unमुक्तze */
	REG_WRITE(ah, AR_MIBC, 0);

	/* update all cycle counters here */
	common->cc_ani.cycles += cycles;
	common->cc_ani.rx_busy += busy;
	common->cc_ani.rx_frame += rx;
	common->cc_ani.tx_frame += tx;

	common->cc_survey.cycles += cycles;
	common->cc_survey.rx_busy += busy;
	common->cc_survey.rx_frame += rx;
	common->cc_survey.tx_frame += tx;
पूर्ण
EXPORT_SYMBOL(ath_hw_cycle_counters_update);

पूर्णांक32_t ath_hw_get_listen_समय(काष्ठा ath_common *common)
अणु
	काष्ठा ath_cycle_counters *cc = &common->cc_ani;
	पूर्णांक32_t listen_समय;

	listen_समय = (cc->cycles - cc->rx_frame - cc->tx_frame) /
		      (common->घड़ीrate * 1000);

	स_रखो(cc, 0, माप(*cc));

	वापस listen_समय;
पूर्ण
EXPORT_SYMBOL(ath_hw_get_listen_समय);
