<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2020 Intel Corporation.
 *
 */

/*
 * This file contains HFI1 support क्रम IPOIB functionality
 */

#अगर_अघोषित HFI1_IPOIB_H
#घोषणा HFI1_IPOIB_H

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/atomic.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/list.h>
#समावेश <linux/अगर_infiniband.h>

#समावेश "hfi.h"
#समावेश "iowait.h"
#समावेश "netdev.h"

#समावेश <rdma/ib_verbs.h>

#घोषणा HFI1_IPOIB_ENTROPY_SHIFT   24

#घोषणा HFI1_IPOIB_TXREQ_NAME_LEN   32

#घोषणा HFI1_IPOIB_PSEUDO_LEN 20
#घोषणा HFI1_IPOIB_ENCAP_LEN 4

काष्ठा hfi1_ipoib_dev_priv;

जोड़ hfi1_ipoib_flow अणु
	u16 as_पूर्णांक;
	काष्ठा अणु
		u8 tx_queue;
		u8 sc5;
	पूर्ण __attribute__((__packed__));
पूर्ण;

/**
 * काष्ठा hfi1_ipoib_circ_buf - List of items to be processed
 * @items: ring of items
 * @head: ring head
 * @tail: ring tail
 * @max_items: max items + 1 that the ring can contain
 * @producer_lock: producer sync lock
 * @consumer_lock: consumer sync lock
 */
काष्ठा ipoib_txreq;
काष्ठा hfi1_ipoib_circ_buf अणु
	काष्ठा ipoib_txreq **items;
	अचिन्हित दीर्घ head;
	अचिन्हित दीर्घ tail;
	अचिन्हित दीर्घ max_items;
	spinlock_t producer_lock; /* head sync lock */
	spinlock_t consumer_lock; /* tail sync lock */
पूर्ण;

/**
 * काष्ठा hfi1_ipoib_txq - IPOIB per Tx queue inक्रमmation
 * @priv: निजी poपूर्णांकer
 * @sde: sdma engine
 * @tx_list: tx request list
 * @sent_txreqs: count of txreqs posted to sdma
 * @stops: count of stops of queue
 * @ring_full: ring has been filled
 * @no_desc: descriptor लघुage seen
 * @flow: tracks when list needs to be flushed क्रम a flow change
 * @q_idx: ipoib Tx queue index
 * @pkts_sent: indicator packets have been sent from this queue
 * @रुको: ioरुको काष्ठाure
 * @complete_txreqs: count of txreqs completed by sdma
 * @napi: poपूर्णांकer to tx napi पूर्णांकerface
 * @tx_ring: ring of ipoib txreqs to be reaped by napi callback
 */
काष्ठा hfi1_ipoib_txq अणु
	काष्ठा hfi1_ipoib_dev_priv *priv;
	काष्ठा sdma_engine *sde;
	काष्ठा list_head tx_list;
	u64 sent_txreqs;
	atomic_t stops;
	atomic_t ring_full;
	atomic_t no_desc;
	जोड़ hfi1_ipoib_flow flow;
	u8 q_idx;
	bool pkts_sent;
	काष्ठा ioरुको रुको;

	atomic64_t ____cacheline_aligned_in_smp complete_txreqs;
	काष्ठा napi_काष्ठा *napi;
	काष्ठा hfi1_ipoib_circ_buf tx_ring;
पूर्ण;

काष्ठा hfi1_ipoib_dev_priv अणु
	काष्ठा hfi1_devdata *dd;
	काष्ठा net_device   *netdev;
	काष्ठा ib_device    *device;
	काष्ठा hfi1_ipoib_txq *txqs;
	काष्ठा kmem_cache *txreq_cache;
	काष्ठा napi_काष्ठा *tx_napis;
	u16 pkey;
	u16 pkey_index;
	u32 qkey;
	u8 port_num;

	स्थिर काष्ठा net_device_ops *netdev_ops;
	काष्ठा rvt_qp *qp;
पूर्ण;

/* hfi1 ipoib rdma netdev's निजी data काष्ठाure */
काष्ठा hfi1_ipoib_rdma_netdev अणु
	काष्ठा rdma_netdev rn;  /* keep this first */
	/* followed by device निजी data */
	काष्ठा hfi1_ipoib_dev_priv dev_priv;
पूर्ण;

अटल अंतरभूत काष्ठा hfi1_ipoib_dev_priv *
hfi1_ipoib_priv(स्थिर काष्ठा net_device *dev)
अणु
	वापस &((काष्ठा hfi1_ipoib_rdma_netdev *)netdev_priv(dev))->dev_priv;
पूर्ण

पूर्णांक hfi1_ipoib_send(काष्ठा net_device *dev,
		    काष्ठा sk_buff *skb,
		    काष्ठा ib_ah *address,
		    u32 dqpn);

पूर्णांक hfi1_ipoib_txreq_init(काष्ठा hfi1_ipoib_dev_priv *priv);
व्योम hfi1_ipoib_txreq_deinit(काष्ठा hfi1_ipoib_dev_priv *priv);

पूर्णांक hfi1_ipoib_rxq_init(काष्ठा net_device *dev);
व्योम hfi1_ipoib_rxq_deinit(काष्ठा net_device *dev);

व्योम hfi1_ipoib_napi_tx_enable(काष्ठा net_device *dev);
व्योम hfi1_ipoib_napi_tx_disable(काष्ठा net_device *dev);

काष्ठा sk_buff *hfi1_ipoib_prepare_skb(काष्ठा hfi1_netdev_rxq *rxq,
				       पूर्णांक size, व्योम *data);

पूर्णांक hfi1_ipoib_rn_get_params(काष्ठा ib_device *device,
			     u32 port_num,
			     क्रमागत rdma_netdev_t type,
			     काष्ठा rdma_netdev_alloc_params *params);

व्योम hfi1_ipoib_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक q);

#पूर्ण_अगर /* _IPOIB_H */
