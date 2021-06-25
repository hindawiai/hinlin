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

#अगर_अघोषित _BRCM_AMPDU_H_
#घोषणा _BRCM_AMPDU_H_

/*
 * Data काष्ठाure representing an in-progress session क्रम accumulating
 * frames क्रम AMPDU.
 *
 * wlc: poपूर्णांकer to common driver data
 * skb_list: queue of skb's क्रम AMPDU
 * max_ampdu_len: maximum length क्रम this AMPDU
 * max_ampdu_frames: maximum number of frames क्रम this AMPDU
 * ampdu_len: total number of bytes accumulated क्रम this AMPDU
 * dma_len: DMA length of this AMPDU
 */
काष्ठा brcms_ampdu_session अणु
	काष्ठा brcms_c_info *wlc;
	काष्ठा sk_buff_head skb_list;
	अचिन्हित max_ampdu_len;
	u16 max_ampdu_frames;
	u16 ampdu_len;
	u16 dma_len;
पूर्ण;

व्योम brcms_c_ampdu_reset_session(काष्ठा brcms_ampdu_session *session,
				 काष्ठा brcms_c_info *wlc);
पूर्णांक brcms_c_ampdu_add_frame(काष्ठा brcms_ampdu_session *session,
			    काष्ठा sk_buff *p);
व्योम brcms_c_ampdu_finalize(काष्ठा brcms_ampdu_session *session);

काष्ठा ampdu_info *brcms_c_ampdu_attach(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_ampdu_detach(काष्ठा ampdu_info *ampdu);
व्योम brcms_c_ampdu_करोtxstatus(काष्ठा ampdu_info *ampdu, काष्ठा scb *scb,
			      काष्ठा sk_buff *p, काष्ठा tx_status *txs);
व्योम brcms_c_ampdu_macaddr_upd(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_ampdu_shm_upd(काष्ठा ampdu_info *ampdu);

#पूर्ण_अगर				/* _BRCM_AMPDU_H_ */
