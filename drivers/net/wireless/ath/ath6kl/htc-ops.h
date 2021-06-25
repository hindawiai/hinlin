<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
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

#अगर_अघोषित HTC_OPS_H
#घोषणा HTC_OPS_H

#समावेश "htc.h"
#समावेश "debug.h"

अटल अंतरभूत व्योम *ath6kl_htc_create(काष्ठा ath6kl *ar)
अणु
	वापस ar->htc_ops->create(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_htc_रुको_target(काष्ठा htc_target *target)
अणु
	वापस target->dev->ar->htc_ops->रुको_target(target);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_htc_start(काष्ठा htc_target *target)
अणु
	वापस target->dev->ar->htc_ops->start(target);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_htc_conn_service(काष्ठा htc_target *target,
					  काष्ठा htc_service_connect_req *req,
					  काष्ठा htc_service_connect_resp *resp)
अणु
	वापस target->dev->ar->htc_ops->conn_service(target, req, resp);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_htc_tx(काष्ठा htc_target *target,
				काष्ठा htc_packet *packet)
अणु
	वापस target->dev->ar->htc_ops->tx(target, packet);
पूर्ण

अटल अंतरभूत व्योम ath6kl_htc_stop(काष्ठा htc_target *target)
अणु
	वापस target->dev->ar->htc_ops->stop(target);
पूर्ण

अटल अंतरभूत व्योम ath6kl_htc_cleanup(काष्ठा htc_target *target)
अणु
	वापस target->dev->ar->htc_ops->cleanup(target);
पूर्ण

अटल अंतरभूत व्योम ath6kl_htc_flush_txep(काष्ठा htc_target *target,
					 क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक,
					 u16 tag)
अणु
	वापस target->dev->ar->htc_ops->flush_txep(target, endpoपूर्णांक, tag);
पूर्ण

अटल अंतरभूत व्योम ath6kl_htc_flush_rx_buf(काष्ठा htc_target *target)
अणु
	वापस target->dev->ar->htc_ops->flush_rx_buf(target);
पूर्ण

अटल अंतरभूत व्योम ath6kl_htc_activity_changed(काष्ठा htc_target *target,
					       क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक,
					       bool active)
अणु
	वापस target->dev->ar->htc_ops->activity_changed(target, endpoपूर्णांक,
							  active);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_htc_get_rxbuf_num(काष्ठा htc_target *target,
					   क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक)
अणु
	वापस target->dev->ar->htc_ops->get_rxbuf_num(target, endpoपूर्णांक);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_htc_add_rxbuf_multiple(काष्ठा htc_target *target,
						काष्ठा list_head *pktq)
अणु
	वापस target->dev->ar->htc_ops->add_rxbuf_multiple(target, pktq);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_htc_credit_setup(काष्ठा htc_target *target,
					  काष्ठा ath6kl_htc_credit_info *info)
अणु
	वापस target->dev->ar->htc_ops->credit_setup(target, info);
पूर्ण

अटल अंतरभूत व्योम ath6kl_htc_tx_complete(काष्ठा ath6kl *ar,
					  काष्ठा sk_buff *skb)
अणु
	ar->htc_ops->tx_complete(ar, skb);
पूर्ण


अटल अंतरभूत व्योम ath6kl_htc_rx_complete(काष्ठा ath6kl *ar,
					  काष्ठा sk_buff *skb, u8 pipe)
अणु
	ar->htc_ops->rx_complete(ar, skb, pipe);
पूर्ण


#पूर्ण_अगर
