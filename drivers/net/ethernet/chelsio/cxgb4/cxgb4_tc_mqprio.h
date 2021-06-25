<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2019 Chelsio Communications.  All rights reserved. */

#अगर_अघोषित __CXGB4_TC_MQPRIO_H__
#घोषणा __CXGB4_TC_MQPRIO_H__

#समावेश <net/pkt_cls.h>

#घोषणा CXGB4_EOSW_TXQ_DEFAULT_DESC_NUM 128

#घोषणा CXGB4_EOHW_TXQ_DEFAULT_DESC_NUM 1024

#घोषणा CXGB4_EOHW_RXQ_DEFAULT_DESC_NUM 1024
#घोषणा CXGB4_EOHW_RXQ_DEFAULT_DESC_SIZE 64
#घोषणा CXGB4_EOHW_RXQ_DEFAULT_INTR_USEC 5
#घोषणा CXGB4_EOHW_RXQ_DEFAULT_PKT_CNT 8

#घोषणा CXGB4_EOHW_FLQ_DEFAULT_DESC_NUM 72

#घोषणा CXGB4_FLOWC_WAIT_TIMEOUT (5 * HZ)

क्रमागत cxgb4_mqprio_state अणु
	CXGB4_MQPRIO_STATE_DISABLED = 0,
	CXGB4_MQPRIO_STATE_ACTIVE,
पूर्ण;

काष्ठा cxgb4_tc_port_mqprio अणु
	क्रमागत cxgb4_mqprio_state state; /* Current MQPRIO offload state */
	काष्ठा tc_mqprio_qopt_offload mqprio; /* MQPRIO offload params */
	काष्ठा sge_eosw_txq *eosw_txq; /* Netdev SW Tx queue array */
	u8 tc_hwtc_map[TC_QOPT_MAX_QUEUE]; /* MQPRIO tc to hardware tc map */
पूर्ण;

काष्ठा cxgb4_tc_mqprio अणु
	refcount_t refcnt; /* Refcount क्रम adapter-wide resources */
	काष्ठा mutex mqprio_mutex; /* Lock क्रम accessing MQPRIO info */
	काष्ठा cxgb4_tc_port_mqprio *port_mqprio; /* Per port MQPRIO info */
पूर्ण;

पूर्णांक cxgb4_setup_tc_mqprio(काष्ठा net_device *dev,
			  काष्ठा tc_mqprio_qopt_offload *mqprio);
व्योम cxgb4_mqprio_stop_offload(काष्ठा adapter *adap);
पूर्णांक cxgb4_init_tc_mqprio(काष्ठा adapter *adap);
व्योम cxgb4_cleanup_tc_mqprio(काष्ठा adapter *adap);
#पूर्ण_अगर /* __CXGB4_TC_MQPRIO_H__ */
