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

#अगर_अघोषित _BRCM_STF_H_
#घोषणा _BRCM_STF_H_

#समावेश "types.h"

पूर्णांक brcms_c_stf_attach(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_stf_detach(काष्ठा brcms_c_info *wlc);

व्योम brcms_c_tempsense_upd(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_stf_ss_algo_channel_get(काष्ठा brcms_c_info *wlc,
				     u16 *ss_algo_channel, u16 chanspec);
व्योम brcms_c_stf_ss_update(काष्ठा brcms_c_info *wlc, काष्ठा brcms_band *band);
व्योम brcms_c_stf_phy_txant_upd(काष्ठा brcms_c_info *wlc);
पूर्णांक brcms_c_stf_txchain_set(काष्ठा brcms_c_info *wlc, s32 पूर्णांक_val, bool क्रमce);
bool brcms_c_stf_stbc_rx_set(काष्ठा brcms_c_info *wlc, s32 पूर्णांक_val);
व्योम brcms_c_stf_phy_txant_upd(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_stf_phy_chain_calc(काष्ठा brcms_c_info *wlc);
u16 brcms_c_stf_phytxchain_sel(काष्ठा brcms_c_info *wlc, u32 rspec);
u16 brcms_c_stf_d11hdrs_phyctl_txant(काष्ठा brcms_c_info *wlc, u32 rspec);

#पूर्ण_अगर				/* _BRCM_STF_H_ */
