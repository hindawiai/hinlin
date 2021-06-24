<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_TX_H
#घोषणा HINIC_TX_H

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/u64_stats_sync.h>

#समावेश "hinic_common.h"
#समावेश "hinic_hw_qp.h"

काष्ठा hinic_txq_stats अणु
	u64     pkts;
	u64     bytes;
	u64     tx_busy;
	u64     tx_wake;
	u64     tx_dropped;
	u64	big_frags_pkts;

	काष्ठा u64_stats_sync   syncp;
पूर्ण;

काष्ठा hinic_txq अणु
	काष्ठा net_device       *netdev;
	काष्ठा hinic_sq         *sq;

	काष्ठा hinic_txq_stats  txq_stats;

	पूर्णांक                     max_sges;
	काष्ठा hinic_sge        *sges;
	काष्ठा hinic_sge        *मुक्त_sges;

	अक्षर                    *irq_name;
	काष्ठा napi_काष्ठा      napi;
पूर्ण;

व्योम hinic_txq_clean_stats(काष्ठा hinic_txq *txq);

व्योम hinic_txq_get_stats(काष्ठा hinic_txq *txq, काष्ठा hinic_txq_stats *stats);

netdev_tx_t hinic_lb_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);

netdev_tx_t hinic_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev);

पूर्णांक hinic_init_txq(काष्ठा hinic_txq *txq, काष्ठा hinic_sq *sq,
		   काष्ठा net_device *netdev);

व्योम hinic_clean_txq(काष्ठा hinic_txq *txq);

#पूर्ण_अगर
