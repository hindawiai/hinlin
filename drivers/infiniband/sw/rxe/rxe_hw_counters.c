<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2017 Mellanox Technologies Ltd. All rights reserved.
 */

#समावेश "rxe.h"
#समावेश "rxe_hw_counters.h"

अटल स्थिर अक्षर * स्थिर rxe_counter_name[] = अणु
	[RXE_CNT_SENT_PKTS]           =  "sent_pkts",
	[RXE_CNT_RCVD_PKTS]           =  "rcvd_pkts",
	[RXE_CNT_DUP_REQ]             =  "duplicate_request",
	[RXE_CNT_OUT_OF_SEQ_REQ]      =  "out_of_seq_request",
	[RXE_CNT_RCV_RNR]             =  "rcvd_rnr_err",
	[RXE_CNT_SND_RNR]             =  "send_rnr_err",
	[RXE_CNT_RCV_SEQ_ERR]         =  "rcvd_seq_err",
	[RXE_CNT_COMPLETER_SCHED]     =  "ack_deferred",
	[RXE_CNT_RETRY_EXCEEDED]      =  "retry_exceeded_err",
	[RXE_CNT_RNR_RETRY_EXCEEDED]  =  "retry_rnr_exceeded_err",
	[RXE_CNT_COMP_RETRY]          =  "completer_retry_err",
	[RXE_CNT_SEND_ERR]            =  "send_err",
	[RXE_CNT_LINK_DOWNED]         =  "link_downed",
	[RXE_CNT_RDMA_SEND]           =  "rdma_sends",
	[RXE_CNT_RDMA_RECV]           =  "rdma_recvs",
पूर्ण;

पूर्णांक rxe_ib_get_hw_stats(काष्ठा ib_device *ibdev,
			काष्ठा rdma_hw_stats *stats,
			u32 port, पूर्णांक index)
अणु
	काष्ठा rxe_dev *dev = to_rdev(ibdev);
	अचिन्हित पूर्णांक cnt;

	अगर (!port || !stats)
		वापस -EINVAL;

	क्रम (cnt = 0; cnt  < ARRAY_SIZE(rxe_counter_name); cnt++)
		stats->value[cnt] = atomic64_पढ़ो(&dev->stats_counters[cnt]);

	वापस ARRAY_SIZE(rxe_counter_name);
पूर्ण

काष्ठा rdma_hw_stats *rxe_ib_alloc_hw_stats(काष्ठा ib_device *ibdev,
					    u32 port_num)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(rxe_counter_name) != RXE_NUM_OF_COUNTERS);
	/* We support only per port stats */
	अगर (!port_num)
		वापस शून्य;

	वापस rdma_alloc_hw_stats_काष्ठा(rxe_counter_name,
					  ARRAY_SIZE(rxe_counter_name),
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
पूर्ण
