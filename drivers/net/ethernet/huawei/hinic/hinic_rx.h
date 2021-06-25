<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_RX_H
#घोषणा HINIC_RX_H

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "hinic_hw_qp.h"

#घोषणा HINIC_RX_CSUM_OFFLOAD_EN	0xFFF
#घोषणा HINIC_RX_CSUM_HW_CHECK_NONE	BIT(7)
#घोषणा HINIC_RX_CSUM_IPSU_OTHER_ERR	BIT(8)

काष्ठा hinic_rxq_stats अणु
	u64                     pkts;
	u64                     bytes;
	u64			errors;
	u64			csum_errors;
	u64			other_errors;
	u64			alloc_skb_err;
	काष्ठा u64_stats_sync   syncp;
पूर्ण;

काष्ठा hinic_rxq अणु
	काष्ठा net_device       *netdev;
	काष्ठा hinic_rq         *rq;

	काष्ठा hinic_rxq_stats  rxq_stats;

	अक्षर                    *irq_name;
	u16			buf_len;
	u32			rx_buff_shअगरt;

	काष्ठा napi_काष्ठा      napi;
पूर्ण;

व्योम hinic_rxq_clean_stats(काष्ठा hinic_rxq *rxq);

व्योम hinic_rxq_get_stats(काष्ठा hinic_rxq *rxq, काष्ठा hinic_rxq_stats *stats);

पूर्णांक hinic_init_rxq(काष्ठा hinic_rxq *rxq, काष्ठा hinic_rq *rq,
		   काष्ठा net_device *netdev);

व्योम hinic_clean_rxq(काष्ठा hinic_rxq *rxq);

#पूर्ण_अगर
