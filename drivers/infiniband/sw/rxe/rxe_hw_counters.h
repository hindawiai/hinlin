<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2017 Mellanox Technologies Ltd. All rights reserved.
 */

#अगर_अघोषित RXE_HW_COUNTERS_H
#घोषणा RXE_HW_COUNTERS_H

/*
 * when adding counters to क्रमागत also add
 * them to rxe_counter_name[] vector.
 */
क्रमागत rxe_counters अणु
	RXE_CNT_SENT_PKTS,
	RXE_CNT_RCVD_PKTS,
	RXE_CNT_DUP_REQ,
	RXE_CNT_OUT_OF_SEQ_REQ,
	RXE_CNT_RCV_RNR,
	RXE_CNT_SND_RNR,
	RXE_CNT_RCV_SEQ_ERR,
	RXE_CNT_COMPLETER_SCHED,
	RXE_CNT_RETRY_EXCEEDED,
	RXE_CNT_RNR_RETRY_EXCEEDED,
	RXE_CNT_COMP_RETRY,
	RXE_CNT_SEND_ERR,
	RXE_CNT_LINK_DOWNED,
	RXE_CNT_RDMA_SEND,
	RXE_CNT_RDMA_RECV,
	RXE_NUM_OF_COUNTERS
पूर्ण;

काष्ठा rdma_hw_stats *rxe_ib_alloc_hw_stats(काष्ठा ib_device *ibdev,
					    u32 port_num);
पूर्णांक rxe_ib_get_hw_stats(काष्ठा ib_device *ibdev,
			काष्ठा rdma_hw_stats *stats,
			u32 port, पूर्णांक index);
#पूर्ण_अगर /* RXE_HW_COUNTERS_H */
