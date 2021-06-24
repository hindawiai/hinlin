<शैली गुरु>
/*
 * Copyright (c) 2008-2009 Atheros Communications Inc.
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

#अगर_अघोषित ATH_REGISTERS_H
#घोषणा ATH_REGISTERS_H

#घोषणा AR_MIBC			0x0040
#घोषणा AR_MIBC_COW		0x00000001
#घोषणा AR_MIBC_FMC		0x00000002
#घोषणा AR_MIBC_CMC		0x00000004
#घोषणा AR_MIBC_MCS		0x00000008

#घोषणा AR_STA_ID0		0x8000
#घोषणा AR_STA_ID1		0x8004
#घोषणा AR_STA_ID1_SADH_MASK	0x0000ffff

/*
 * BSSID mask रेजिस्टरs. See ath_hw_set_bssid_mask()
 * क्रम detailed करोcumentation about these रेजिस्टरs.
 */
#घोषणा AR_BSSMSKL		0x80e0
#घोषणा AR_BSSMSKU		0x80e4

#घोषणा AR_TFCNT		0x80ec
#घोषणा AR_RFCNT		0x80f0
#घोषणा AR_RCCNT		0x80f4
#घोषणा AR_CCCNT		0x80f8

#घोषणा AR_KEYTABLE_0           0x8800
#घोषणा AR_KEYTABLE(_n)         (AR_KEYTABLE_0 + ((_n)*32))
#घोषणा AR_KEY_CACHE_SIZE       128
#घोषणा AR_RSVD_KEYTABLE_ENTRIES 4
#घोषणा AR_KEY_TYPE             0x00000007
#घोषणा AR_KEYTABLE_TYPE_40     0x00000000
#घोषणा AR_KEYTABLE_TYPE_104    0x00000001
#घोषणा AR_KEYTABLE_TYPE_128    0x00000003
#घोषणा AR_KEYTABLE_TYPE_TKIP   0x00000004
#घोषणा AR_KEYTABLE_TYPE_AES    0x00000005
#घोषणा AR_KEYTABLE_TYPE_CCM    0x00000006
#घोषणा AR_KEYTABLE_TYPE_CLR    0x00000007
#घोषणा AR_KEYTABLE_ANT         0x00000008
#घोषणा AR_KEYTABLE_VALID       0x00008000
#घोषणा AR_KEYTABLE_KEY0(_n)    (AR_KEYTABLE(_n) + 0)
#घोषणा AR_KEYTABLE_KEY1(_n)    (AR_KEYTABLE(_n) + 4)
#घोषणा AR_KEYTABLE_KEY2(_n)    (AR_KEYTABLE(_n) + 8)
#घोषणा AR_KEYTABLE_KEY3(_n)    (AR_KEYTABLE(_n) + 12)
#घोषणा AR_KEYTABLE_KEY4(_n)    (AR_KEYTABLE(_n) + 16)
#घोषणा AR_KEYTABLE_TYPE(_n)    (AR_KEYTABLE(_n) + 20)
#घोषणा AR_KEYTABLE_MAC0(_n)    (AR_KEYTABLE(_n) + 24)
#घोषणा AR_KEYTABLE_MAC1(_n)    (AR_KEYTABLE(_n) + 28)

#पूर्ण_अगर /* ATH_REGISTERS_H */
