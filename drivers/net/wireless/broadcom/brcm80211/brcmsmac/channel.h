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

#अगर_अघोषित _BRCM_CHANNEL_H_
#घोषणा _BRCM_CHANNEL_H_

/* conversion क्रम phy txpwr calculations that use .25 dB units */
#घोषणा BRCMS_TXPWR_DB_FACTOR 4

/* bits क्रम locale_info flags */
#घोषणा BRCMS_PEAK_CONDUCTED	0x00	/* Peak क्रम locals */
#घोषणा BRCMS_EIRP		0x01	/* Flag क्रम EIRP */
#घोषणा BRCMS_DFS_TPC		0x02	/* Flag क्रम DFS TPC */
#घोषणा BRCMS_NO_OFDM		0x04	/* Flag क्रम No OFDM */
#घोषणा BRCMS_NO_40MHZ		0x08	/* Flag क्रम No MIMO 40MHz */
#घोषणा BRCMS_NO_MIMO		0x10	/* Flag क्रम No MIMO, 20 or 40 MHz */
#घोषणा BRCMS_RADAR_TYPE_EU       0x20	/* Flag क्रम EU */
#घोषणा BRCMS_DFS_FCC             BRCMS_DFS_TPC	/* Flag क्रम DFS FCC */

#घोषणा BRCMS_DFS_EU (BRCMS_DFS_TPC | BRCMS_RADAR_TYPE_EU) /* Flag क्रम DFS EU */

काष्ठा brcms_cm_info *brcms_c_channel_mgr_attach(काष्ठा brcms_c_info *wlc);

व्योम brcms_c_channel_mgr_detach(काष्ठा brcms_cm_info *wlc_cm);

bool brcms_c_valid_chanspec_db(काष्ठा brcms_cm_info *wlc_cm, u16 chspec);

व्योम brcms_c_channel_reg_limits(काष्ठा brcms_cm_info *wlc_cm, u16 chanspec,
				काष्ठा txpwr_limits *txpwr);
व्योम brcms_c_channel_set_chanspec(काष्ठा brcms_cm_info *wlc_cm, u16 chanspec,
				  u8 local_स्थिरraपूर्णांक_qdbm);
व्योम brcms_c_regd_init(काष्ठा brcms_c_info *wlc);

#पूर्ण_अगर				/* _WLC_CHANNEL_H */
