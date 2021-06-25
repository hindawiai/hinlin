<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2018 Intel Corporation.
 *
 */
#अगर_अघोषित _HFI1_OPFN_H
#घोषणा _HFI1_OPFN_H

/**
 * DOC: Omni Path Feature Negotion (OPFN)
 *
 * OPFN is a discovery protocol क्रम Intel Omni-Path fabric that
 * allows two RC QPs to negotiate a common feature that both QPs
 * can support. Currently, the only OPA feature that OPFN
 * supports is TID RDMA.
 *
 * Architecture
 *
 * OPFN involves the communication between two QPs on the HFI
 * level on an Omni-Path fabric, and ULPs have no knowledge of
 * OPFN at all.
 *
 * Implementation
 *
 * OPFN extends the existing IB RC protocol with the following
 * changes:
 * -- Uses Bit 24 (reserved) of DWORD 1 of Base Transport
 *    Header (BTH1) to indicate that the RC QP supports OPFN;
 * -- Uses a combination of RC COMPARE_SWAP opcode (0x13) and
 *    the address U64_MAX (0xFFFFFFFFFFFFFFFF) as an OPFN
 *    request; The 64-bit data carried with the request/response
 *    contains the parameters क्रम negotiation and will be
 *    defined in tid_rdma.c file;
 * -- Defines IB_WR_RESERVED3 as IB_WR_OPFN.
 *
 * The OPFN communication will be triggered when an RC QP
 * receives a request with Bit 24 of BTH1 set. The responder QP
 * will then post send an OPFN request with its local
 * parameters, which will be sent to the requester QP once all
 * existing requests on the responder QP side have been sent.
 * Once the requester QP receives the OPFN request, it will
 * keep a copy of the responder QP's parameters, and वापस a
 * response packet with its own local parameters. The responder
 * QP receives the response packet and keeps a copy of the requester
 * QP's parameters. After this exchange, each side has the parameters
 * क्रम both sides and thereक्रमe can select the right parameters
 * क्रम future transactions
 */

#समावेश <linux/workqueue.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdmavt_qp.h>

/* STL Verbs Extended */
#घोषणा IB_BTHE_E_SHIFT           24
#घोषणा HFI1_VERBS_E_ATOMIC_VADDR U64_MAX

क्रमागत hfi1_opfn_codes अणु
	STL_VERBS_EXTD_NONE = 0,
	STL_VERBS_EXTD_TID_RDMA,
	STL_VERBS_EXTD_MAX
पूर्ण;

काष्ठा hfi1_opfn_data अणु
	u8 extended;
	u16 requested;
	u16 completed;
	क्रमागत hfi1_opfn_codes curr;
	/* serialize opfn function calls */
	spinlock_t lock;
	काष्ठा work_काष्ठा opfn_work;
पूर्ण;

/* WR opcode क्रम OPFN */
#घोषणा IB_WR_OPFN IB_WR_RESERVED3

व्योम opfn_send_conn_request(काष्ठा work_काष्ठा *work);
व्योम opfn_conn_response(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
			काष्ठा ib_atomic_eth *ateth);
व्योम opfn_conn_reply(काष्ठा rvt_qp *qp, u64 data);
व्योम opfn_conn_error(काष्ठा rvt_qp *qp);
व्योम opfn_qp_init(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask);
व्योम opfn_trigger_conn_request(काष्ठा rvt_qp *qp, u32 bth1);
पूर्णांक opfn_init(व्योम);
व्योम opfn_निकास(व्योम);

#पूर्ण_अगर /* _HFI1_OPFN_H */
