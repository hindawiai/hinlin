<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_VECTOR_KERN_H
#घोषणा __UM_VECTOR_KERN_H

#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "vector_user.h"

/* Queue काष्ठाure specially adapted क्रम multiple enqueue/dequeue
 * in a mmsgrecv/mmsgsend context
 */

/* Dequeue method */

#घोषणा QUEUE_SENDMSG 0
#घोषणा QUEUE_SENDMMSG 1

#घोषणा VECTOR_RX 1
#घोषणा VECTOR_TX (1 << 1)
#घोषणा VECTOR_BPF (1 << 2)
#घोषणा VECTOR_QDISC_BYPASS (1 << 3)
#घोषणा VECTOR_BPF_FLASH (1 << 4)

#घोषणा ETH_MAX_PACKET 1500
#घोषणा ETH_HEADER_OTHER 32 /* just in हाल someone decides to go mad on QnQ */

#घोषणा MAX_FILTER_PROG (2 << 16)

काष्ठा vector_queue अणु
	काष्ठा mmsghdr *mmsg_vector;
	व्योम **skbuff_vector;
	 /* backlink to device which owns us */
	काष्ठा net_device *dev;
	spinlock_t head_lock;
	spinlock_t tail_lock;
	पूर्णांक queue_depth, head, tail, max_depth, max_iov_frags;
	लघु options;
पूर्ण;

काष्ठा vector_estats अणु
	uपूर्णांक64_t rx_queue_max;
	uपूर्णांक64_t rx_queue_running_average;
	uपूर्णांक64_t tx_queue_max;
	uपूर्णांक64_t tx_queue_running_average;
	uपूर्णांक64_t rx_encaps_errors;
	uपूर्णांक64_t tx_समयout_count;
	uपूर्णांक64_t tx_restart_queue;
	uपूर्णांक64_t tx_kicks;
	uपूर्णांक64_t tx_flow_control_xon;
	uपूर्णांक64_t tx_flow_control_xoff;
	uपूर्णांक64_t rx_csum_offload_good;
	uपूर्णांक64_t rx_csum_offload_errors;
	uपूर्णांक64_t sg_ok;
	uपूर्णांक64_t sg_linearized;
पूर्ण;

#घोषणा VERIFY_HEADER_NOK -1
#घोषणा VERIFY_HEADER_OK 0
#घोषणा VERIFY_CSUM_OK 1

काष्ठा vector_निजी अणु
	काष्ठा list_head list;
	spinlock_t lock;
	काष्ठा net_device *dev;

	पूर्णांक unit;

	/* Timeout समयr in TX */

	काष्ठा समयr_list tl;

	/* Scheduled "remove device" work */
	काष्ठा work_काष्ठा reset_tx;
	काष्ठा vector_fds *fds;

	काष्ठा vector_queue *rx_queue;
	काष्ठा vector_queue *tx_queue;

	पूर्णांक rx_irq;
	पूर्णांक tx_irq;

	काष्ठा arglist *parsed;

	व्योम *transport_data; /* transport specअगरic params अगर needed */

	पूर्णांक max_packet;
	पूर्णांक req_size; /* dअगरferent from max packet - used क्रम TSO */
	पूर्णांक headroom;

	पूर्णांक options;

	/* remote address अगर any - some transports will leave this as null */

	पूर्णांक header_size;
	पूर्णांक rx_header_size;
	पूर्णांक coalesce;

	व्योम *header_rxbuffer;
	व्योम *header_txbuffer;

	पूर्णांक (*क्रमm_header)(uपूर्णांक8_t *header,
		काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp);
	पूर्णांक (*verअगरy_header)(uपूर्णांक8_t *header,
		काष्ठा sk_buff *skb, काष्ठा vector_निजी *vp);

	spinlock_t stats_lock;

	काष्ठा tasklet_काष्ठा tx_poll;
	bool rexmit_scheduled;
	bool खोलोed;
	bool in_ग_लिखो_poll;
	bool in_error;

	/* guest allowed to use ethtool flash to load bpf */
	bool bpf_via_flash;

	/* ethtool stats */

	काष्ठा vector_estats estats;
	काष्ठा sock_fprog *bpf;

	अक्षर user[];
पूर्ण;

बाह्य पूर्णांक build_transport_data(काष्ठा vector_निजी *vp);

#पूर्ण_अगर
