<शैली गुरु>
/*
 * Copyright (c) 2015 Qualcomm Atheros Inc.
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

#अगर_अघोषित REG_WOW_H
#घोषणा REG_WOW_H

#घोषणा AR_WOW_PATTERN                  0x825C
#घोषणा AR_WOW_COUNT                    0x8260
#घोषणा AR_WOW_BCN_EN                   0x8270
#घोषणा AR_WOW_BCN_TIMO                 0x8274
#घोषणा AR_WOW_KEEP_ALIVE_TIMO          0x8278
#घोषणा AR_WOW_KEEP_ALIVE               0x827c
#घोषणा AR_WOW_KEEP_ALIVE_DELAY         0x8288
#घोषणा AR_WOW_PATTERN_MATCH            0x828c

/*
 * AR_WOW_LENGTH1
 * bit 31:24 pattern 0 length
 * bit 23:16 pattern 1 length
 * bit 15:8 pattern 2 length
 * bit 7:0 pattern 3 length
 *
 * AR_WOW_LENGTH2
 * bit 31:24 pattern 4 length
 * bit 23:16 pattern 5 length
 * bit 15:8 pattern 6 length
 * bit 7:0 pattern 7 length
 *
 * AR_WOW_LENGTH3
 * bit 31:24 pattern 8 length
 * bit 23:16 pattern 9 length
 * bit 15:8 pattern 10 length
 * bit 7:0 pattern 11 length
 *
 * AR_WOW_LENGTH4
 * bit 31:24 pattern 12 length
 * bit 23:16 pattern 13 length
 * bit 15:8 pattern 14 length
 * bit 7:0 pattern 15 length
 */
#घोषणा AR_WOW_LENGTH1                  0x8360
#घोषणा AR_WOW_LENGTH2                  0X8364
#घोषणा AR_WOW_LENGTH3                  0X8380
#घोषणा AR_WOW_LENGTH4                  0X8384

#घोषणा AR_WOW_PATTERN_MATCH_LT_256B    0x8368
#घोषणा AR_MAC_PCU_WOW4                 0x8370

#घोषणा AR_SW_WOW_CONTROL               0x20018
#घोषणा AR_SW_WOW_ENABLE                0x1
#घोषणा AR_SWITCH_TO_REFCLK             0x2
#घोषणा AR_RESET_CONTROL                0x4
#घोषणा AR_RESET_VALUE_MASK             0x8
#घोषणा AR_HW_WOW_DISABLE               0x10
#घोषणा AR_CLR_MAC_INTERRUPT            0x20
#घोषणा AR_CLR_KA_INTERRUPT             0x40

#घोषणा AR_WOW_BACK_OFF_SHIFT(x)        ((x & 0xf) << 27) /* in usecs */
#घोषणा AR_WOW_MAC_INTR_EN              0x00040000
#घोषणा AR_WOW_MAGIC_EN                 0x00010000
#घोषणा AR_WOW_PATTERN_EN(x)            (x & 0xff)
#घोषणा AR_WOW_PAT_FOUND_SHIFT          8
#घोषणा AR_WOW_PATTERN_FOUND(x)         (x & (0xff << AR_WOW_PAT_FOUND_SHIFT))
#घोषणा AR_WOW_PATTERN_FOUND_MASK       ((0xff) << AR_WOW_PAT_FOUND_SHIFT)
#घोषणा AR_WOW_MAGIC_PAT_FOUND          0x00020000
#घोषणा AR_WOW_MAC_INTR                 0x00080000
#घोषणा AR_WOW_KEEP_ALIVE_FAIL          0x00100000
#घोषणा AR_WOW_BEACON_FAIL              0x00200000

#घोषणा AR_WOW_STATUS(x)                (x & (AR_WOW_PATTERN_FOUND_MASK | \
                                              AR_WOW_MAGIC_PAT_FOUND    | \
                                              AR_WOW_KEEP_ALIVE_FAIL    | \
                                              AR_WOW_BEACON_FAIL))
#घोषणा AR_WOW_CLEAR_EVENTS(x)          (x & ~(AR_WOW_PATTERN_EN(0xff) | \
                                               AR_WOW_MAGIC_EN |	\
                                               AR_WOW_MAC_INTR_EN |	\
                                               AR_WOW_BEACON_FAIL |	\
                                               AR_WOW_KEEP_ALIVE_FAIL))

#घोषणा AR_WOW2_PATTERN_EN(x)           ((x & 0xff) << 0)
#घोषणा AR_WOW2_PATTERN_FOUND_SHIFT     8
#घोषणा AR_WOW2_PATTERN_FOUND(x)        (x & (0xff << AR_WOW2_PATTERN_FOUND_SHIFT))
#घोषणा AR_WOW2_PATTERN_FOUND_MASK      ((0xff) << AR_WOW2_PATTERN_FOUND_SHIFT)

#घोषणा AR_WOW_STATUS2(x)               (x & AR_WOW2_PATTERN_FOUND_MASK)
#घोषणा AR_WOW_CLEAR_EVENTS2(x)         (x & ~(AR_WOW2_PATTERN_EN(0xff)))

#घोषणा AR_WOW_AIFS_CNT(x)              (x & 0xff)
#घोषणा AR_WOW_SLOT_CNT(x)              ((x & 0xff) << 8)
#घोषणा AR_WOW_KEEP_ALIVE_CNT(x)        ((x & 0xff) << 16)

#घोषणा AR_WOW_BEACON_FAIL_EN           0x00000001
#घोषणा AR_WOW_BEACON_TIMO              0x40000000
#घोषणा AR_WOW_KEEP_ALIVE_NEVER         0xffffffff
#घोषणा AR_WOW_KEEP_ALIVE_AUTO_DIS      0x00000001
#घोषणा AR_WOW_KEEP_ALIVE_FAIL_DIS      0x00000002
#घोषणा AR_WOW_KEEP_ALIVE_DELAY_VALUE   0x000003e8 /* 1 msec */
#घोषणा AR_WOW_BMISSTHRESHOLD           0x20
#घोषणा AR_WOW_PAT_END_OF_PKT(x)        (x & 0xf)
#घोषणा AR_WOW_PAT_OFF_MATCH(x)         ((x & 0xf) << 8)
#घोषणा AR_WOW_PAT_BACKOFF              0x00000004
#घोषणा AR_WOW_CNT_AIFS_CNT             0x00000022
#घोषणा AR_WOW_CNT_SLOT_CNT             0x00000009
#घोषणा AR_WOW_CNT_KA_CNT               0x00000008

#घोषणा AR_WOW_TRANSMIT_BUFFER          0xe000
#घोषणा AR_WOW_TXBUF(i)                 (AR_WOW_TRANSMIT_BUFFER + ((i) << 2))
#घोषणा AR_WOW_KA_DESC_WORD2            0xe000
#घोषणा AR_WOW_TB_PATTERN(i)            (0xe100 + (i << 8))
#घोषणा AR_WOW_TB_MASK(i)               (0xec00 + (i << 5))
#घोषणा AR_WOW_PATTERN_SUPPORTED_LEGACY 0xff
#घोषणा AR_WOW_PATTERN_SUPPORTED        0xffff
#घोषणा AR_WOW_LENGTH_MAX               0xff
#घोषणा AR_WOW_LEN1_SHIFT(_i)           ((0x3 - ((_i) & 0x3)) << 0x3)
#घोषणा AR_WOW_LENGTH1_MASK(_i)         (AR_WOW_LENGTH_MAX << AR_WOW_LEN1_SHIFT(_i))
#घोषणा AR_WOW_LEN2_SHIFT(_i)           ((0x7 - ((_i) & 0x7)) << 0x3)
#घोषणा AR_WOW_LENGTH2_MASK(_i)         (AR_WOW_LENGTH_MAX << AR_WOW_LEN2_SHIFT(_i))
#घोषणा AR_WOW_LEN3_SHIFT(_i)           ((0xb - ((_i) & 0xb)) << 0x3)
#घोषणा AR_WOW_LENGTH3_MASK(_i)         (AR_WOW_LENGTH_MAX << AR_WOW_LEN3_SHIFT(_i))
#घोषणा AR_WOW_LEN4_SHIFT(_i)           ((0xf - ((_i) & 0xf)) << 0x3)
#घोषणा AR_WOW_LENGTH4_MASK(_i)         (AR_WOW_LENGTH_MAX << AR_WOW_LEN4_SHIFT(_i))

#पूर्ण_अगर /* REG_WOW_H */
