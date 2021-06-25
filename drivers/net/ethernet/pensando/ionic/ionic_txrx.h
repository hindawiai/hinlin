<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#अगर_अघोषित _IONIC_TXRX_H_
#घोषणा _IONIC_TXRX_H_

व्योम ionic_tx_flush(काष्ठा ionic_cq *cq);

व्योम ionic_rx_fill(काष्ठा ionic_queue *q);
व्योम ionic_rx_empty(काष्ठा ionic_queue *q);
व्योम ionic_tx_empty(काष्ठा ionic_queue *q);
पूर्णांक ionic_rx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक ionic_tx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक ionic_txrx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
netdev_tx_t ionic_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);

bool ionic_rx_service(काष्ठा ionic_cq *cq, काष्ठा ionic_cq_info *cq_info);
bool ionic_tx_service(काष्ठा ionic_cq *cq, काष्ठा ionic_cq_info *cq_info);

#पूर्ण_अगर /* _IONIC_TXRX_H_ */
