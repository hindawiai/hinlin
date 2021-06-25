<शैली गुरु>
/*
 * Copyright(c) 2015 - 2020 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/utsname.h>
#समावेश <linux/rculist.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/opa_addr.h>
#समावेश <linux/nospec.h>

#समावेश "hfi.h"
#समावेश "common.h"
#समावेश "device.h"
#समावेश "trace.h"
#समावेश "qp.h"
#समावेश "verbs_txreq.h"
#समावेश "debugfs.h"
#समावेश "vnic.h"
#समावेश "fault.h"
#समावेश "affinity.h"
#समावेश "ipoib.h"

अटल अचिन्हित पूर्णांक hfi1_lkey_table_size = 16;
module_param_named(lkey_table_size, hfi1_lkey_table_size, uपूर्णांक,
		   S_IRUGO);
MODULE_PARM_DESC(lkey_table_size,
		 "LKEY table size in bits (2^n, 1 <= n <= 23)");

अटल अचिन्हित पूर्णांक hfi1_max_pds = 0xFFFF;
module_param_named(max_pds, hfi1_max_pds, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_pds,
		 "Maximum number of protection domains to support");

अटल अचिन्हित पूर्णांक hfi1_max_ahs = 0xFFFF;
module_param_named(max_ahs, hfi1_max_ahs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_ahs, "Maximum number of address handles to support");

अचिन्हित पूर्णांक hfi1_max_cqes = 0x2FFFFF;
module_param_named(max_cqes, hfi1_max_cqes, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_cqes,
		 "Maximum number of completion queue entries to support");

अचिन्हित पूर्णांक hfi1_max_cqs = 0x1FFFF;
module_param_named(max_cqs, hfi1_max_cqs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_cqs, "Maximum number of completion queues to support");

अचिन्हित पूर्णांक hfi1_max_qp_wrs = 0x3FFF;
module_param_named(max_qp_wrs, hfi1_max_qp_wrs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_qp_wrs, "Maximum number of QP WRs to support");

अचिन्हित पूर्णांक hfi1_max_qps = 32768;
module_param_named(max_qps, hfi1_max_qps, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_qps, "Maximum number of QPs to support");

अचिन्हित पूर्णांक hfi1_max_sges = 0x60;
module_param_named(max_sges, hfi1_max_sges, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_sges, "Maximum number of SGEs to support");

अचिन्हित पूर्णांक hfi1_max_mcast_grps = 16384;
module_param_named(max_mcast_grps, hfi1_max_mcast_grps, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_mcast_grps,
		 "Maximum number of multicast groups to support");

अचिन्हित पूर्णांक hfi1_max_mcast_qp_attached = 16;
module_param_named(max_mcast_qp_attached, hfi1_max_mcast_qp_attached,
		   uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_mcast_qp_attached,
		 "Maximum number of attached QPs to support");

अचिन्हित पूर्णांक hfi1_max_srqs = 1024;
module_param_named(max_srqs, hfi1_max_srqs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_srqs, "Maximum number of SRQs to support");

अचिन्हित पूर्णांक hfi1_max_srq_sges = 128;
module_param_named(max_srq_sges, hfi1_max_srq_sges, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_srq_sges, "Maximum number of SRQ SGEs to support");

अचिन्हित पूर्णांक hfi1_max_srq_wrs = 0x1FFFF;
module_param_named(max_srq_wrs, hfi1_max_srq_wrs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_srq_wrs, "Maximum number of SRQ WRs support");

अचिन्हित लघु piothreshold = 256;
module_param(piothreshold, uलघु, S_IRUGO);
MODULE_PARM_DESC(piothreshold, "size used to determine sdma vs. pio");

अटल अचिन्हित पूर्णांक sge_copy_mode;
module_param(sge_copy_mode, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(sge_copy_mode,
		 "Verbs copy mode: 0 use memcpy, 1 use cacheless copy, 2 adapt based on WSS");

अटल व्योम verbs_sdma_complete(
	काष्ठा sdma_txreq *cookie,
	पूर्णांक status);

अटल पूर्णांक pio_रुको(काष्ठा rvt_qp *qp,
		    काष्ठा send_context *sc,
		    काष्ठा hfi1_pkt_state *ps,
		    u32 flag);

/* Length of buffer to create verbs txreq cache name */
#घोषणा TXREQ_NAME_LEN 24

अटल uपूर्णांक wss_threshold = 80;
module_param(wss_threshold, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(wss_threshold, "Percentage (1-100) of LLC to use as a threshold for a cacheless copy");
अटल uपूर्णांक wss_clean_period = 256;
module_param(wss_clean_period, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(wss_clean_period, "Count of verbs copies before an entry in the page copy table is cleaned");

/*
 * Translate ib_wr_opcode पूर्णांकo ib_wc_opcode.
 */
स्थिर क्रमागत ib_wc_opcode ib_hfi1_wc_opcode[] = अणु
	[IB_WR_RDMA_WRITE] = IB_WC_RDMA_WRITE,
	[IB_WR_TID_RDMA_WRITE] = IB_WC_RDMA_WRITE,
	[IB_WR_RDMA_WRITE_WITH_IMM] = IB_WC_RDMA_WRITE,
	[IB_WR_SEND] = IB_WC_SEND,
	[IB_WR_SEND_WITH_IMM] = IB_WC_SEND,
	[IB_WR_RDMA_READ] = IB_WC_RDMA_READ,
	[IB_WR_TID_RDMA_READ] = IB_WC_RDMA_READ,
	[IB_WR_ATOMIC_CMP_AND_SWP] = IB_WC_COMP_SWAP,
	[IB_WR_ATOMIC_FETCH_AND_ADD] = IB_WC_FETCH_ADD,
	[IB_WR_SEND_WITH_INV] = IB_WC_SEND,
	[IB_WR_LOCAL_INV] = IB_WC_LOCAL_INV,
	[IB_WR_REG_MR] = IB_WC_REG_MR
पूर्ण;

/*
 * Length of header by opcode, 0 --> not supported
 */
स्थिर u8 hdr_len_by_opcode[256] = अणु
	/* RC */
	[IB_OPCODE_RC_SEND_FIRST]                     = 12 + 8,
	[IB_OPCODE_RC_SEND_MIDDLE]                    = 12 + 8,
	[IB_OPCODE_RC_SEND_LAST]                      = 12 + 8,
	[IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_RC_SEND_ONLY]                      = 12 + 8,
	[IB_OPCODE_RC_SEND_ONLY_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_RC_RDMA_WRITE_FIRST]               = 12 + 8 + 16,
	[IB_OPCODE_RC_RDMA_WRITE_MIDDLE]              = 12 + 8,
	[IB_OPCODE_RC_RDMA_WRITE_LAST]                = 12 + 8,
	[IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE] = 12 + 8 + 4,
	[IB_OPCODE_RC_RDMA_WRITE_ONLY]                = 12 + 8 + 16,
	[IB_OPCODE_RC_RDMA_WRITE_ONLY_WITH_IMMEDIATE] = 12 + 8 + 20,
	[IB_OPCODE_RC_RDMA_READ_REQUEST]              = 12 + 8 + 16,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST]       = 12 + 8 + 4,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE]      = 12 + 8,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST]        = 12 + 8 + 4,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY]        = 12 + 8 + 4,
	[IB_OPCODE_RC_ACKNOWLEDGE]                    = 12 + 8 + 4,
	[IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE]             = 12 + 8 + 4 + 8,
	[IB_OPCODE_RC_COMPARE_SWAP]                   = 12 + 8 + 28,
	[IB_OPCODE_RC_FETCH_ADD]                      = 12 + 8 + 28,
	[IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE]      = 12 + 8 + 4,
	[IB_OPCODE_RC_SEND_ONLY_WITH_INVALIDATE]      = 12 + 8 + 4,
	[IB_OPCODE_TID_RDMA_READ_REQ]                 = 12 + 8 + 36,
	[IB_OPCODE_TID_RDMA_READ_RESP]                = 12 + 8 + 36,
	[IB_OPCODE_TID_RDMA_WRITE_REQ]                = 12 + 8 + 36,
	[IB_OPCODE_TID_RDMA_WRITE_RESP]               = 12 + 8 + 36,
	[IB_OPCODE_TID_RDMA_WRITE_DATA]               = 12 + 8 + 36,
	[IB_OPCODE_TID_RDMA_WRITE_DATA_LAST]          = 12 + 8 + 36,
	[IB_OPCODE_TID_RDMA_ACK]                      = 12 + 8 + 36,
	[IB_OPCODE_TID_RDMA_RESYNC]                   = 12 + 8 + 36,
	/* UC */
	[IB_OPCODE_UC_SEND_FIRST]                     = 12 + 8,
	[IB_OPCODE_UC_SEND_MIDDLE]                    = 12 + 8,
	[IB_OPCODE_UC_SEND_LAST]                      = 12 + 8,
	[IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_UC_SEND_ONLY]                      = 12 + 8,
	[IB_OPCODE_UC_SEND_ONLY_WITH_IMMEDIATE]       = 12 + 8 + 4,
	[IB_OPCODE_UC_RDMA_WRITE_FIRST]               = 12 + 8 + 16,
	[IB_OPCODE_UC_RDMA_WRITE_MIDDLE]              = 12 + 8,
	[IB_OPCODE_UC_RDMA_WRITE_LAST]                = 12 + 8,
	[IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE] = 12 + 8 + 4,
	[IB_OPCODE_UC_RDMA_WRITE_ONLY]                = 12 + 8 + 16,
	[IB_OPCODE_UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE] = 12 + 8 + 20,
	/* UD */
	[IB_OPCODE_UD_SEND_ONLY]                      = 12 + 8 + 8,
	[IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE]       = 12 + 8 + 12
पूर्ण;

अटल स्थिर opcode_handler opcode_handler_tbl[256] = अणु
	/* RC */
	[IB_OPCODE_RC_SEND_FIRST]                     = &hfi1_rc_rcv,
	[IB_OPCODE_RC_SEND_MIDDLE]                    = &hfi1_rc_rcv,
	[IB_OPCODE_RC_SEND_LAST]                      = &hfi1_rc_rcv,
	[IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE]       = &hfi1_rc_rcv,
	[IB_OPCODE_RC_SEND_ONLY]                      = &hfi1_rc_rcv,
	[IB_OPCODE_RC_SEND_ONLY_WITH_IMMEDIATE]       = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_WRITE_FIRST]               = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_WRITE_MIDDLE]              = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_WRITE_LAST]                = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE] = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_WRITE_ONLY]                = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_WRITE_ONLY_WITH_IMMEDIATE] = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_READ_REQUEST]              = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST]       = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE]      = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST]        = &hfi1_rc_rcv,
	[IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY]        = &hfi1_rc_rcv,
	[IB_OPCODE_RC_ACKNOWLEDGE]                    = &hfi1_rc_rcv,
	[IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE]             = &hfi1_rc_rcv,
	[IB_OPCODE_RC_COMPARE_SWAP]                   = &hfi1_rc_rcv,
	[IB_OPCODE_RC_FETCH_ADD]                      = &hfi1_rc_rcv,
	[IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE]      = &hfi1_rc_rcv,
	[IB_OPCODE_RC_SEND_ONLY_WITH_INVALIDATE]      = &hfi1_rc_rcv,

	/* TID RDMA has separate handlers क्रम dअगरferent opcodes.*/
	[IB_OPCODE_TID_RDMA_WRITE_REQ]       = &hfi1_rc_rcv_tid_rdma_ग_लिखो_req,
	[IB_OPCODE_TID_RDMA_WRITE_RESP]      = &hfi1_rc_rcv_tid_rdma_ग_लिखो_resp,
	[IB_OPCODE_TID_RDMA_WRITE_DATA]      = &hfi1_rc_rcv_tid_rdma_ग_लिखो_data,
	[IB_OPCODE_TID_RDMA_WRITE_DATA_LAST] = &hfi1_rc_rcv_tid_rdma_ग_लिखो_data,
	[IB_OPCODE_TID_RDMA_READ_REQ]        = &hfi1_rc_rcv_tid_rdma_पढ़ो_req,
	[IB_OPCODE_TID_RDMA_READ_RESP]       = &hfi1_rc_rcv_tid_rdma_पढ़ो_resp,
	[IB_OPCODE_TID_RDMA_RESYNC]          = &hfi1_rc_rcv_tid_rdma_resync,
	[IB_OPCODE_TID_RDMA_ACK]             = &hfi1_rc_rcv_tid_rdma_ack,

	/* UC */
	[IB_OPCODE_UC_SEND_FIRST]                     = &hfi1_uc_rcv,
	[IB_OPCODE_UC_SEND_MIDDLE]                    = &hfi1_uc_rcv,
	[IB_OPCODE_UC_SEND_LAST]                      = &hfi1_uc_rcv,
	[IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE]       = &hfi1_uc_rcv,
	[IB_OPCODE_UC_SEND_ONLY]                      = &hfi1_uc_rcv,
	[IB_OPCODE_UC_SEND_ONLY_WITH_IMMEDIATE]       = &hfi1_uc_rcv,
	[IB_OPCODE_UC_RDMA_WRITE_FIRST]               = &hfi1_uc_rcv,
	[IB_OPCODE_UC_RDMA_WRITE_MIDDLE]              = &hfi1_uc_rcv,
	[IB_OPCODE_UC_RDMA_WRITE_LAST]                = &hfi1_uc_rcv,
	[IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE] = &hfi1_uc_rcv,
	[IB_OPCODE_UC_RDMA_WRITE_ONLY]                = &hfi1_uc_rcv,
	[IB_OPCODE_UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE] = &hfi1_uc_rcv,
	/* UD */
	[IB_OPCODE_UD_SEND_ONLY]                      = &hfi1_ud_rcv,
	[IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE]       = &hfi1_ud_rcv,
	/* CNP */
	[IB_OPCODE_CNP]				      = &hfi1_cnp_rcv
पूर्ण;

#घोषणा OPMASK 0x1f

अटल स्थिर u32 pio_opmask[BIT(3)] = अणु
	/* RC */
	[IB_OPCODE_RC >> 5] =
		BIT(RC_OP(SEND_ONLY) & OPMASK) |
		BIT(RC_OP(SEND_ONLY_WITH_IMMEDIATE) & OPMASK) |
		BIT(RC_OP(RDMA_WRITE_ONLY) & OPMASK) |
		BIT(RC_OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE) & OPMASK) |
		BIT(RC_OP(RDMA_READ_REQUEST) & OPMASK) |
		BIT(RC_OP(ACKNOWLEDGE) & OPMASK) |
		BIT(RC_OP(ATOMIC_ACKNOWLEDGE) & OPMASK) |
		BIT(RC_OP(COMPARE_SWAP) & OPMASK) |
		BIT(RC_OP(FETCH_ADD) & OPMASK),
	/* UC */
	[IB_OPCODE_UC >> 5] =
		BIT(UC_OP(SEND_ONLY) & OPMASK) |
		BIT(UC_OP(SEND_ONLY_WITH_IMMEDIATE) & OPMASK) |
		BIT(UC_OP(RDMA_WRITE_ONLY) & OPMASK) |
		BIT(UC_OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE) & OPMASK),
पूर्ण;

/*
 * System image GUID.
 */
__be64 ib_hfi1_sys_image_guid;

/*
 * Make sure the QP is पढ़ोy and able to accept the given opcode.
 */
अटल अंतरभूत opcode_handler qp_ok(काष्ठा hfi1_packet *packet)
अणु
	अगर (!(ib_rvt_state_ops[packet->qp->state] & RVT_PROCESS_RECV_OK))
		वापस शून्य;
	अगर (((packet->opcode & RVT_OPCODE_QP_MASK) ==
	     packet->qp->allowed_ops) ||
	    (packet->opcode == IB_OPCODE_CNP))
		वापस opcode_handler_tbl[packet->opcode];

	वापस शून्य;
पूर्ण

अटल u64 hfi1_fault_tx(काष्ठा rvt_qp *qp, u8 opcode, u64 pbc)
अणु
#अगर_घोषित CONFIG_FAULT_INJECTION
	अगर ((opcode & IB_OPCODE_MSP) == IB_OPCODE_MSP) अणु
		/*
		 * In order to drop non-IB traffic we
		 * set PbcInsertHrc to NONE (0x2).
		 * The packet will still be delivered
		 * to the receiving node but a
		 * KHdrHCRCErr (KDETH packet with a bad
		 * HCRC) will be triggered and the
		 * packet will not be delivered to the
		 * correct context.
		 */
		pbc &= ~PBC_INSERT_HCRC_SMASK;
		pbc |= (u64)PBC_IHCRC_NONE << PBC_INSERT_HCRC_SHIFT;
	पूर्ण अन्यथा अणु
		/*
		 * In order to drop regular verbs
		 * traffic we set the PbcTestEbp
		 * flag. The packet will still be
		 * delivered to the receiving node but
		 * a 'late ebp error' will be
		 * triggered and will be dropped.
		 */
		pbc |= PBC_TEST_EBP;
	पूर्ण
#पूर्ण_अगर
	वापस pbc;
पूर्ण

अटल opcode_handler tid_qp_ok(पूर्णांक opcode, काष्ठा hfi1_packet *packet)
अणु
	अगर (packet->qp->ibqp.qp_type != IB_QPT_RC ||
	    !(ib_rvt_state_ops[packet->qp->state] & RVT_PROCESS_RECV_OK))
		वापस शून्य;
	अगर ((opcode & RVT_OPCODE_QP_MASK) == IB_OPCODE_TID_RDMA)
		वापस opcode_handler_tbl[opcode];
	वापस शून्य;
पूर्ण

व्योम hfi1_kdeth_eager_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा ib_header *hdr = packet->hdr;
	u32 tlen = packet->tlen;
	काष्ठा hfi1_pportdata *ppd = rcd->ppd;
	काष्ठा hfi1_ibport *ibp = &ppd->ibport_data;
	काष्ठा rvt_dev_info *rdi = &ppd->dd->verbs_dev.rdi;
	opcode_handler opcode_handler;
	अचिन्हित दीर्घ flags;
	u32 qp_num;
	पूर्णांक lnh;
	u8 opcode;

	/* DW == LRH (2) + BTH (3) + KDETH (9) + CRC (1) */
	अगर (unlikely(tlen < 15 * माप(u32)))
		जाओ drop;

	lnh = be16_to_cpu(hdr->lrh[0]) & 3;
	अगर (lnh != HFI1_LRH_BTH)
		जाओ drop;

	packet->ohdr = &hdr->u.oth;
	trace_input_ibhdr(rcd->dd, packet, !!(rhf_dc_info(packet->rhf)));

	opcode = (be32_to_cpu(packet->ohdr->bth[0]) >> 24);
	inc_opstats(tlen, &rcd->opstats->stats[opcode]);

	/* verbs_qp can be picked up from any tid_rdma header काष्ठा */
	qp_num = be32_to_cpu(packet->ohdr->u.tid_rdma.r_req.verbs_qp) &
		RVT_QPN_MASK;

	rcu_पढ़ो_lock();
	packet->qp = rvt_lookup_qpn(rdi, &ibp->rvp, qp_num);
	अगर (!packet->qp)
		जाओ drop_rcu;
	spin_lock_irqsave(&packet->qp->r_lock, flags);
	opcode_handler = tid_qp_ok(opcode, packet);
	अगर (likely(opcode_handler))
		opcode_handler(packet);
	अन्यथा
		जाओ drop_unlock;
	spin_unlock_irqrestore(&packet->qp->r_lock, flags);
	rcu_पढ़ो_unlock();

	वापस;
drop_unlock:
	spin_unlock_irqrestore(&packet->qp->r_lock, flags);
drop_rcu:
	rcu_पढ़ो_unlock();
drop:
	ibp->rvp.n_pkt_drops++;
पूर्ण

व्योम hfi1_kdeth_expected_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा ib_header *hdr = packet->hdr;
	u32 tlen = packet->tlen;
	काष्ठा hfi1_pportdata *ppd = rcd->ppd;
	काष्ठा hfi1_ibport *ibp = &ppd->ibport_data;
	काष्ठा rvt_dev_info *rdi = &ppd->dd->verbs_dev.rdi;
	opcode_handler opcode_handler;
	अचिन्हित दीर्घ flags;
	u32 qp_num;
	पूर्णांक lnh;
	u8 opcode;

	/* DW == LRH (2) + BTH (3) + KDETH (9) + CRC (1) */
	अगर (unlikely(tlen < 15 * माप(u32)))
		जाओ drop;

	lnh = be16_to_cpu(hdr->lrh[0]) & 3;
	अगर (lnh != HFI1_LRH_BTH)
		जाओ drop;

	packet->ohdr = &hdr->u.oth;
	trace_input_ibhdr(rcd->dd, packet, !!(rhf_dc_info(packet->rhf)));

	opcode = (be32_to_cpu(packet->ohdr->bth[0]) >> 24);
	inc_opstats(tlen, &rcd->opstats->stats[opcode]);

	/* verbs_qp can be picked up from any tid_rdma header काष्ठा */
	qp_num = be32_to_cpu(packet->ohdr->u.tid_rdma.r_rsp.verbs_qp) &
		RVT_QPN_MASK;

	rcu_पढ़ो_lock();
	packet->qp = rvt_lookup_qpn(rdi, &ibp->rvp, qp_num);
	अगर (!packet->qp)
		जाओ drop_rcu;
	spin_lock_irqsave(&packet->qp->r_lock, flags);
	opcode_handler = tid_qp_ok(opcode, packet);
	अगर (likely(opcode_handler))
		opcode_handler(packet);
	अन्यथा
		जाओ drop_unlock;
	spin_unlock_irqrestore(&packet->qp->r_lock, flags);
	rcu_पढ़ो_unlock();

	वापस;
drop_unlock:
	spin_unlock_irqrestore(&packet->qp->r_lock, flags);
drop_rcu:
	rcu_पढ़ो_unlock();
drop:
	ibp->rvp.n_pkt_drops++;
पूर्ण

अटल पूर्णांक hfi1_करो_pkey_check(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा hfi1_pportdata *ppd = rcd->ppd;
	काष्ठा hfi1_16b_header *hdr = packet->hdr;
	u16 pkey;

	/* Pkey check needed only क्रम bypass packets */
	अगर (packet->etype != RHF_RCV_TYPE_BYPASS)
		वापस 0;

	/* Perक्रमm pkey check */
	pkey = hfi1_16B_get_pkey(hdr);
	वापस ingress_pkey_check(ppd, pkey, packet->sc,
				  packet->qp->s_pkey_index,
				  packet->slid, true);
पूर्ण

अटल अंतरभूत व्योम hfi1_handle_packet(काष्ठा hfi1_packet *packet,
				      bool is_mcast)
अणु
	u32 qp_num;
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा hfi1_pportdata *ppd = rcd->ppd;
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(rcd);
	काष्ठा rvt_dev_info *rdi = &ppd->dd->verbs_dev.rdi;
	opcode_handler packet_handler;
	अचिन्हित दीर्घ flags;

	inc_opstats(packet->tlen, &rcd->opstats->stats[packet->opcode]);

	अगर (unlikely(is_mcast)) अणु
		काष्ठा rvt_mcast *mcast;
		काष्ठा rvt_mcast_qp *p;

		अगर (!packet->grh)
			जाओ drop;
		mcast = rvt_mcast_find(&ibp->rvp,
				       &packet->grh->dgid,
				       opa_get_lid(packet->dlid, 9B));
		अगर (!mcast)
			जाओ drop;
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(p, &mcast->qp_list, list) अणु
			packet->qp = p->qp;
			अगर (hfi1_करो_pkey_check(packet))
				जाओ unlock_drop;
			spin_lock_irqsave(&packet->qp->r_lock, flags);
			packet_handler = qp_ok(packet);
			अगर (likely(packet_handler))
				packet_handler(packet);
			अन्यथा
				ibp->rvp.n_pkt_drops++;
			spin_unlock_irqrestore(&packet->qp->r_lock, flags);
		पूर्ण
		rcu_पढ़ो_unlock();
		/*
		 * Notअगरy rvt_multicast_detach() अगर it is रुकोing क्रम us
		 * to finish.
		 */
		अगर (atomic_dec_वापस(&mcast->refcount) <= 1)
			wake_up(&mcast->रुको);
	पूर्ण अन्यथा अणु
		/* Get the destination QP number. */
		अगर (packet->etype == RHF_RCV_TYPE_BYPASS &&
		    hfi1_16B_get_l4(packet->hdr) == OPA_16B_L4_FM)
			qp_num = hfi1_16B_get_dest_qpn(packet->mgmt);
		अन्यथा
			qp_num = ib_bth_get_qpn(packet->ohdr);

		rcu_पढ़ो_lock();
		packet->qp = rvt_lookup_qpn(rdi, &ibp->rvp, qp_num);
		अगर (!packet->qp)
			जाओ unlock_drop;

		अगर (hfi1_करो_pkey_check(packet))
			जाओ unlock_drop;

		spin_lock_irqsave(&packet->qp->r_lock, flags);
		packet_handler = qp_ok(packet);
		अगर (likely(packet_handler))
			packet_handler(packet);
		अन्यथा
			ibp->rvp.n_pkt_drops++;
		spin_unlock_irqrestore(&packet->qp->r_lock, flags);
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस;
unlock_drop:
	rcu_पढ़ो_unlock();
drop:
	ibp->rvp.n_pkt_drops++;
पूर्ण

/**
 * hfi1_ib_rcv - process an incoming packet
 * @packet: data packet inक्रमmation
 *
 * This is called to process an incoming packet at पूर्णांकerrupt level.
 */
व्योम hfi1_ib_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;

	trace_input_ibhdr(rcd->dd, packet, !!(rhf_dc_info(packet->rhf)));
	hfi1_handle_packet(packet, hfi1_check_mcast(packet->dlid));
पूर्ण

व्योम hfi1_16B_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;

	trace_input_ibhdr(rcd->dd, packet, false);
	hfi1_handle_packet(packet, hfi1_check_mcast(packet->dlid));
पूर्ण

/*
 * This is called from a समयr to check क्रम QPs
 * which need kernel memory in order to send a packet.
 */
अटल व्योम mem_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_ibdev *dev = from_समयr(dev, t, mem_समयr);
	काष्ठा list_head *list = &dev->memरुको;
	काष्ठा rvt_qp *qp = शून्य;
	काष्ठा ioरुको *रुको;
	अचिन्हित दीर्घ flags;
	काष्ठा hfi1_qp_priv *priv;

	ग_लिखो_seqlock_irqsave(&dev->ioरुको_lock, flags);
	अगर (!list_empty(list)) अणु
		रुको = list_first_entry(list, काष्ठा ioरुको, list);
		qp = ioरुको_to_qp(रुको);
		priv = qp->priv;
		list_del_init(&priv->s_ioरुको.list);
		priv->s_ioरुको.lock = शून्य;
		/* refcount held until actual wake up */
		अगर (!list_empty(list))
			mod_समयr(&dev->mem_समयr, jअगरfies + 1);
	पूर्ण
	ग_लिखो_sequnlock_irqrestore(&dev->ioरुको_lock, flags);

	अगर (qp)
		hfi1_qp_wakeup(qp, RVT_S_WAIT_KMEM);
पूर्ण

/*
 * This is called with progress side lock held.
 */
/* New API */
अटल व्योम verbs_sdma_complete(
	काष्ठा sdma_txreq *cookie,
	पूर्णांक status)
अणु
	काष्ठा verbs_txreq *tx =
		container_of(cookie, काष्ठा verbs_txreq, txreq);
	काष्ठा rvt_qp *qp = tx->qp;

	spin_lock(&qp->s_lock);
	अगर (tx->wqe) अणु
		rvt_send_complete(qp, tx->wqe, IB_WC_SUCCESS);
	पूर्ण अन्यथा अगर (qp->ibqp.qp_type == IB_QPT_RC) अणु
		काष्ठा hfi1_opa_header *hdr;

		hdr = &tx->phdr.hdr;
		अगर (unlikely(status == SDMA_TXREQ_S_ABORTED))
			hfi1_rc_verbs_पातed(qp, hdr);
		hfi1_rc_send_complete(qp, hdr);
	पूर्ण
	spin_unlock(&qp->s_lock);

	hfi1_put_txreq(tx);
पूर्ण

व्योम hfi1_रुको_kmem(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा ib_device *ibdev = ibqp->device;
	काष्ठा hfi1_ibdev *dev = to_idev(ibdev);

	अगर (list_empty(&priv->s_ioरुको.list)) अणु
		अगर (list_empty(&dev->memरुको))
			mod_समयr(&dev->mem_समयr, jअगरfies + 1);
		qp->s_flags |= RVT_S_WAIT_KMEM;
		list_add_tail(&priv->s_ioरुको.list, &dev->memरुको);
		priv->s_ioरुको.lock = &dev->ioरुको_lock;
		trace_hfi1_qpsleep(qp, RVT_S_WAIT_KMEM);
		rvt_get_qp(qp);
	पूर्ण
पूर्ण

अटल पूर्णांक रुको_kmem(काष्ठा hfi1_ibdev *dev,
		     काष्ठा rvt_qp *qp,
		     काष्ठा hfi1_pkt_state *ps)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		ग_लिखो_seqlock(&dev->ioरुको_lock);
		list_add_tail(&ps->s_txreq->txreq.list,
			      &ps->रुको->tx_head);
		hfi1_रुको_kmem(qp);
		ग_लिखो_sequnlock(&dev->ioरुको_lock);
		hfi1_qp_unbusy(qp, ps->रुको);
		ret = -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&qp->s_lock, flags);

	वापस ret;
पूर्ण

/*
 * This routine calls txadds क्रम each sg entry.
 *
 * Add failures will revert the sge cursor
 */
अटल noअंतरभूत पूर्णांक build_verbs_ulp_payload(
	काष्ठा sdma_engine *sde,
	u32 length,
	काष्ठा verbs_txreq *tx)
अणु
	काष्ठा rvt_sge_state *ss = tx->ss;
	काष्ठा rvt_sge *sg_list = ss->sg_list;
	काष्ठा rvt_sge sge = ss->sge;
	u8 num_sge = ss->num_sge;
	u32 len;
	पूर्णांक ret = 0;

	जबतक (length) अणु
		len = rvt_get_sge_length(&ss->sge, length);
		WARN_ON_ONCE(len == 0);
		ret = sdma_txadd_kvaddr(
			sde->dd,
			&tx->txreq,
			ss->sge.vaddr,
			len);
		अगर (ret)
			जाओ bail_txadd;
		rvt_update_sge(ss, len, false);
		length -= len;
	पूर्ण
	वापस ret;
bail_txadd:
	/* unwind cursor */
	ss->sge = sge;
	ss->num_sge = num_sge;
	ss->sg_list = sg_list;
	वापस ret;
पूर्ण

/**
 * update_tx_opstats - record stats by opcode
 * @qp: the qp
 * @ps: transmit packet state
 * @plen: the plen in dwords
 *
 * This is a routine to record the tx opstats after a
 * packet has been presented to the egress mechanism.
 */
अटल व्योम update_tx_opstats(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			      u32 plen)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	काष्ठा hfi1_opcode_stats_perctx *s = get_cpu_ptr(dd->tx_opstats);

	inc_opstats(plen * 4, &s->stats[ps->opcode]);
	put_cpu_ptr(s);
#पूर्ण_अगर
पूर्ण

/*
 * Build the number of DMA descriptors needed to send length bytes of data.
 *
 * NOTE: DMA mapping is held in the tx until completed in the ring or
 *       the tx desc is मुक्तd without having been submitted to the ring
 *
 * This routine ensures all the helper routine calls succeed.
 */
/* New API */
अटल पूर्णांक build_verbs_tx_desc(
	काष्ठा sdma_engine *sde,
	u32 length,
	काष्ठा verbs_txreq *tx,
	काष्ठा hfi1_ahg_info *ahg_info,
	u64 pbc)
अणु
	पूर्णांक ret = 0;
	काष्ठा hfi1_sdma_header *phdr = &tx->phdr;
	u16 hdrbytes = (tx->hdr_dwords + माप(pbc) / 4) << 2;
	u8 extra_bytes = 0;

	अगर (tx->phdr.hdr.hdr_type) अणु
		/*
		 * hdrbytes accounts क्रम PBC. Need to subtract 8 bytes
		 * beक्रमe calculating padding.
		 */
		extra_bytes = hfi1_get_16b_padding(hdrbytes - 8, length) +
			      (SIZE_OF_CRC << 2) + SIZE_OF_LT;
	पूर्ण
	अगर (!ahg_info->ahgcount) अणु
		ret = sdma_txinit_ahg(
			&tx->txreq,
			ahg_info->tx_flags,
			hdrbytes + length +
			extra_bytes,
			ahg_info->ahgidx,
			0,
			शून्य,
			0,
			verbs_sdma_complete);
		अगर (ret)
			जाओ bail_txadd;
		phdr->pbc = cpu_to_le64(pbc);
		ret = sdma_txadd_kvaddr(
			sde->dd,
			&tx->txreq,
			phdr,
			hdrbytes);
		अगर (ret)
			जाओ bail_txadd;
	पूर्ण अन्यथा अणु
		ret = sdma_txinit_ahg(
			&tx->txreq,
			ahg_info->tx_flags,
			length,
			ahg_info->ahgidx,
			ahg_info->ahgcount,
			ahg_info->ahgdesc,
			hdrbytes,
			verbs_sdma_complete);
		अगर (ret)
			जाओ bail_txadd;
	पूर्ण
	/* add the ulp payload - अगर any. tx->ss can be शून्य क्रम acks */
	अगर (tx->ss) अणु
		ret = build_verbs_ulp_payload(sde, length, tx);
		अगर (ret)
			जाओ bail_txadd;
	पूर्ण

	/* add icrc, lt byte, and padding to flit */
	अगर (extra_bytes)
		ret = sdma_txadd_daddr(sde->dd, &tx->txreq,
				       sde->dd->sdma_pad_phys, extra_bytes);

bail_txadd:
	वापस ret;
पूर्ण

अटल u64 update_hcrc(u8 opcode, u64 pbc)
अणु
	अगर ((opcode & IB_OPCODE_TID_RDMA) == IB_OPCODE_TID_RDMA) अणु
		pbc &= ~PBC_INSERT_HCRC_SMASK;
		pbc |= (u64)PBC_IHCRC_LKDETH << PBC_INSERT_HCRC_SHIFT;
	पूर्ण
	वापस pbc;
पूर्ण

पूर्णांक hfi1_verbs_send_dma(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			u64 pbc)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ahg_info *ahg_info = priv->s_ahg;
	u32 hdrwords = ps->s_txreq->hdr_dwords;
	u32 len = ps->s_txreq->s_cur_size;
	u32 plen;
	काष्ठा hfi1_ibdev *dev = ps->dev;
	काष्ठा hfi1_pportdata *ppd = ps->ppd;
	काष्ठा verbs_txreq *tx;
	u8 sc5 = priv->s_sc;
	पूर्णांक ret;
	u32 dwords;

	अगर (ps->s_txreq->phdr.hdr.hdr_type) अणु
		u8 extra_bytes = hfi1_get_16b_padding((hdrwords << 2), len);

		dwords = (len + extra_bytes + (SIZE_OF_CRC << 2) +
			  SIZE_OF_LT) >> 2;
	पूर्ण अन्यथा अणु
		dwords = (len + 3) >> 2;
	पूर्ण
	plen = hdrwords + dwords + माप(pbc) / 4;

	tx = ps->s_txreq;
	अगर (!sdma_txreq_built(&tx->txreq)) अणु
		अगर (likely(pbc == 0)) अणु
			u32 vl = sc_to_vlt(dd_from_ibdev(qp->ibqp.device), sc5);

			/* No vl15 here */
			/* set PBC_DC_INFO bit (aka SC[4]) in pbc */
			अगर (ps->s_txreq->phdr.hdr.hdr_type)
				pbc |= PBC_PACKET_BYPASS |
				       PBC_INSERT_BYPASS_ICRC;
			अन्यथा
				pbc |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);

			pbc = create_pbc(ppd,
					 pbc,
					 qp->srate_mbps,
					 vl,
					 plen);

			अगर (unlikely(hfi1_dbg_should_fault_tx(qp, ps->opcode)))
				pbc = hfi1_fault_tx(qp, ps->opcode, pbc);
			अन्यथा
				/* Update HCRC based on packet opcode */
				pbc = update_hcrc(ps->opcode, pbc);
		पूर्ण
		tx->wqe = qp->s_wqe;
		ret = build_verbs_tx_desc(tx->sde, len, tx, ahg_info, pbc);
		अगर (unlikely(ret))
			जाओ bail_build;
	पूर्ण
	ret =  sdma_send_txreq(tx->sde, ps->रुको, &tx->txreq, ps->pkts_sent);
	अगर (unlikely(ret < 0)) अणु
		अगर (ret == -ECOMM)
			जाओ bail_ecomm;
		वापस ret;
	पूर्ण

	update_tx_opstats(qp, ps, plen);
	trace_sdma_output_ibhdr(dd_from_ibdev(qp->ibqp.device),
				&ps->s_txreq->phdr.hdr, ib_is_sc5(sc5));
	वापस ret;

bail_ecomm:
	/* The current one got "sent" */
	वापस 0;
bail_build:
	ret = रुको_kmem(dev, qp, ps);
	अगर (!ret) अणु
		/* मुक्त txreq - bad state */
		hfi1_put_txreq(ps->s_txreq);
		ps->s_txreq = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * If we are now in the error state, वापस zero to flush the
 * send work request.
 */
अटल पूर्णांक pio_रुको(काष्ठा rvt_qp *qp,
		    काष्ठा send_context *sc,
		    काष्ठा hfi1_pkt_state *ps,
		    u32 flag)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_devdata *dd = sc->dd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/*
	 * Note that as soon as want_buffer() is called and
	 * possibly beक्रमe it वापसs, sc_piobufavail()
	 * could be called. Thereक्रमe, put QP on the I/O रुको list beक्रमe
	 * enabling the PIO avail पूर्णांकerrupt.
	 */
	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		ग_लिखो_seqlock(&sc->रुकोlock);
		list_add_tail(&ps->s_txreq->txreq.list,
			      &ps->रुको->tx_head);
		अगर (list_empty(&priv->s_ioरुको.list)) अणु
			काष्ठा hfi1_ibdev *dev = &dd->verbs_dev;
			पूर्णांक was_empty;

			dev->n_pioरुको += !!(flag & RVT_S_WAIT_PIO);
			dev->n_piodrain += !!(flag & HFI1_S_WAIT_PIO_DRAIN);
			qp->s_flags |= flag;
			was_empty = list_empty(&sc->pioरुको);
			ioरुको_get_priority(&priv->s_ioरुको);
			ioरुको_queue(ps->pkts_sent, &priv->s_ioरुको,
				     &sc->pioरुको);
			priv->s_ioरुको.lock = &sc->रुकोlock;
			trace_hfi1_qpsleep(qp, RVT_S_WAIT_PIO);
			rvt_get_qp(qp);
			/* counting: only call wantpiobuf_पूर्णांकr अगर first user */
			अगर (was_empty)
				hfi1_sc_wantpiobuf_पूर्णांकr(sc, 1);
		पूर्ण
		ग_लिखो_sequnlock(&sc->रुकोlock);
		hfi1_qp_unbusy(qp, ps->रुको);
		ret = -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&qp->s_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम verbs_pio_complete(व्योम *arg, पूर्णांक code)
अणु
	काष्ठा rvt_qp *qp = (काष्ठा rvt_qp *)arg;
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	अगर (ioरुको_pio_dec(&priv->s_ioरुको))
		ioरुको_drain_wakeup(&priv->s_ioरुको);
पूर्ण

पूर्णांक hfi1_verbs_send_pio(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			u64 pbc)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	u32 hdrwords = ps->s_txreq->hdr_dwords;
	काष्ठा rvt_sge_state *ss = ps->s_txreq->ss;
	u32 len = ps->s_txreq->s_cur_size;
	u32 dwords;
	u32 plen;
	काष्ठा hfi1_pportdata *ppd = ps->ppd;
	u32 *hdr;
	u8 sc5;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा send_context *sc;
	काष्ठा pio_buf *pbuf;
	पूर्णांक wc_status = IB_WC_SUCCESS;
	पूर्णांक ret = 0;
	pio_release_cb cb = शून्य;
	u8 extra_bytes = 0;

	अगर (ps->s_txreq->phdr.hdr.hdr_type) अणु
		u8 pad_size = hfi1_get_16b_padding((hdrwords << 2), len);

		extra_bytes = pad_size + (SIZE_OF_CRC << 2) + SIZE_OF_LT;
		dwords = (len + extra_bytes) >> 2;
		hdr = (u32 *)&ps->s_txreq->phdr.hdr.opah;
	पूर्ण अन्यथा अणु
		dwords = (len + 3) >> 2;
		hdr = (u32 *)&ps->s_txreq->phdr.hdr.ibh;
	पूर्ण
	plen = hdrwords + dwords + माप(pbc) / 4;

	/* only RC/UC use complete */
	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
		cb = verbs_pio_complete;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* vl15 special हाल taken care of in ud.c */
	sc5 = priv->s_sc;
	sc = ps->s_txreq->psc;

	अगर (likely(pbc == 0)) अणु
		u8 vl = sc_to_vlt(dd_from_ibdev(qp->ibqp.device), sc5);

		/* set PBC_DC_INFO bit (aka SC[4]) in pbc */
		अगर (ps->s_txreq->phdr.hdr.hdr_type)
			pbc |= PBC_PACKET_BYPASS | PBC_INSERT_BYPASS_ICRC;
		अन्यथा
			pbc |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);

		pbc = create_pbc(ppd, pbc, qp->srate_mbps, vl, plen);
		अगर (unlikely(hfi1_dbg_should_fault_tx(qp, ps->opcode)))
			pbc = hfi1_fault_tx(qp, ps->opcode, pbc);
		अन्यथा
			/* Update HCRC based on packet opcode */
			pbc = update_hcrc(ps->opcode, pbc);
	पूर्ण
	अगर (cb)
		ioरुको_pio_inc(&priv->s_ioरुको);
	pbuf = sc_buffer_alloc(sc, plen, cb, qp);
	अगर (IS_ERR_OR_शून्य(pbuf)) अणु
		अगर (cb)
			verbs_pio_complete(qp, 0);
		अगर (IS_ERR(pbuf)) अणु
			/*
			 * If we have filled the PIO buffers to capacity and are
			 * not in an active state this request is not going to
			 * go out to so just complete it with an error or अन्यथा a
			 * ULP or the core may be stuck रुकोing.
			 */
			hfi1_cdbg(
				PIO,
				"alloc failed. state not active, completing");
			wc_status = IB_WC_GENERAL_ERR;
			जाओ pio_bail;
		पूर्ण अन्यथा अणु
			/*
			 * This is a normal occurrence. The PIO buffs are full
			 * up but we are still happily sending, well we could be
			 * so lets जारी to queue the request.
			 */
			hfi1_cdbg(PIO, "alloc failed. state active, queuing");
			ret = pio_रुको(qp, sc, ps, RVT_S_WAIT_PIO);
			अगर (!ret)
				/* txreq not queued - मुक्त */
				जाओ bail;
			/* tx consumed in रुको */
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dwords == 0) अणु
		pio_copy(ppd->dd, pbuf, pbc, hdr, hdrwords);
	पूर्ण अन्यथा अणु
		seg_pio_copy_start(pbuf, pbc,
				   hdr, hdrwords * 4);
		अगर (ss) अणु
			जबतक (len) अणु
				व्योम *addr = ss->sge.vaddr;
				u32 slen = rvt_get_sge_length(&ss->sge, len);

				rvt_update_sge(ss, slen, false);
				seg_pio_copy_mid(pbuf, addr, slen);
				len -= slen;
			पूर्ण
		पूर्ण
		/* add icrc, lt byte, and padding to flit */
		अगर (extra_bytes)
			seg_pio_copy_mid(pbuf, ppd->dd->sdma_pad_dma,
					 extra_bytes);

		seg_pio_copy_end(pbuf);
	पूर्ण

	update_tx_opstats(qp, ps, plen);
	trace_pio_output_ibhdr(dd_from_ibdev(qp->ibqp.device),
			       &ps->s_txreq->phdr.hdr, ib_is_sc5(sc5));

pio_bail:
	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (qp->s_wqe) अणु
		rvt_send_complete(qp, qp->s_wqe, wc_status);
	पूर्ण अन्यथा अगर (qp->ibqp.qp_type == IB_QPT_RC) अणु
		अगर (unlikely(wc_status == IB_WC_GENERAL_ERR))
			hfi1_rc_verbs_पातed(qp, &ps->s_txreq->phdr.hdr);
		hfi1_rc_send_complete(qp, &ps->s_txreq->phdr.hdr);
	पूर्ण
	spin_unlock_irqrestore(&qp->s_lock, flags);

	ret = 0;

bail:
	hfi1_put_txreq(ps->s_txreq);
	वापस ret;
पूर्ण

/*
 * egress_pkey_matches_entry - वापस 1 अगर the pkey matches ent (ent
 * being an entry from the partition key table), वापस 0
 * otherwise. Use the matching criteria क्रम egress partition keys
 * specअगरied in the OPAv1 spec., section 9.1l.7.
 */
अटल अंतरभूत पूर्णांक egress_pkey_matches_entry(u16 pkey, u16 ent)
अणु
	u16 mkey = pkey & PKEY_LOW_15_MASK;
	u16 mentry = ent & PKEY_LOW_15_MASK;

	अगर (mkey == mentry) अणु
		/*
		 * If pkey[15] is set (full partition member),
		 * is bit 15 in the corresponding table element
		 * clear (limited member)?
		 */
		अगर (pkey & PKEY_MEMBER_MASK)
			वापस !!(ent & PKEY_MEMBER_MASK);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * egress_pkey_check - check P_KEY of a packet
 * @ppd:  Physical IB port data
 * @slid: SLID क्रम packet
 * @pkey: PKEY क्रम header
 * @sc5:  SC क्रम packet
 * @s_pkey_index: It will be used क्रम look up optimization क्रम kernel contexts
 * only. If it is negative value, then it means user contexts is calling this
 * function.
 *
 * It checks अगर hdr's pkey is valid.
 *
 * Return: 0 on success, otherwise, 1
 */
पूर्णांक egress_pkey_check(काष्ठा hfi1_pportdata *ppd, u32 slid, u16 pkey,
		      u8 sc5, पूर्णांक8_t s_pkey_index)
अणु
	काष्ठा hfi1_devdata *dd;
	पूर्णांक i;
	पूर्णांक is_user_ctxt_mechanism = (s_pkey_index < 0);

	अगर (!(ppd->part_enक्रमce & HFI1_PART_ENFORCE_OUT))
		वापस 0;

	/* If SC15, pkey[0:14] must be 0x7fff */
	अगर ((sc5 == 0xf) && ((pkey & PKEY_LOW_15_MASK) != PKEY_LOW_15_MASK))
		जाओ bad;

	/* Is the pkey = 0x0, or 0x8000? */
	अगर ((pkey & PKEY_LOW_15_MASK) == 0)
		जाओ bad;

	/*
	 * For the kernel contexts only, अगर a qp is passed पूर्णांकo the function,
	 * the most likely matching pkey has index qp->s_pkey_index
	 */
	अगर (!is_user_ctxt_mechanism &&
	    egress_pkey_matches_entry(pkey, ppd->pkeys[s_pkey_index])) अणु
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < MAX_PKEY_VALUES; i++) अणु
		अगर (egress_pkey_matches_entry(pkey, ppd->pkeys[i]))
			वापस 0;
	पूर्ण
bad:
	/*
	 * For the user-context mechanism, the P_KEY check would only happen
	 * once per SDMA request, not once per packet.  Thereक्रमe, there's no
	 * need to increment the counter क्रम the user-context mechanism.
	 */
	अगर (!is_user_ctxt_mechanism) अणु
		incr_cntr64(&ppd->port_xmit_स्थिरraपूर्णांक_errors);
		dd = ppd->dd;
		अगर (!(dd->err_info_xmit_स्थिरraपूर्णांक.status &
		      OPA_EI_STATUS_SMASK)) अणु
			dd->err_info_xmit_स्थिरraपूर्णांक.status |=
				OPA_EI_STATUS_SMASK;
			dd->err_info_xmit_स्थिरraपूर्णांक.slid = slid;
			dd->err_info_xmit_स्थिरraपूर्णांक.pkey = pkey;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * get_send_routine - choose an egress routine
 *
 * Choose an egress routine based on QP type
 * and size
 */
अटल अंतरभूत send_routine get_send_routine(काष्ठा rvt_qp *qp,
					    काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा verbs_txreq *tx = ps->s_txreq;

	अगर (unlikely(!(dd->flags & HFI1_HAS_SEND_DMA)))
		वापस dd->process_pio_send;
	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_SMI:
		वापस dd->process_pio_send;
	हाल IB_QPT_GSI:
	हाल IB_QPT_UD:
		अवरोध;
	हाल IB_QPT_UC:
	हाल IB_QPT_RC:
		priv->s_running_pkt_size =
			(tx->s_cur_size + priv->s_running_pkt_size) / 2;
		अगर (piothreshold &&
		    priv->s_running_pkt_size <= min(piothreshold, qp->pmtu) &&
		    (BIT(ps->opcode & OPMASK) & pio_opmask[ps->opcode >> 5]) &&
		    ioरुको_sdma_pending(&priv->s_ioरुको) == 0 &&
		    !sdma_txreq_built(&tx->txreq))
			वापस dd->process_pio_send;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस dd->process_dma_send;
पूर्ण

/**
 * hfi1_verbs_send - send a packet
 * @qp: the QP to send on
 * @ps: the state of the packet to send
 *
 * Return zero अगर packet is sent or queued OK.
 * Return non-zero and clear qp->s_flags RVT_S_BUSY otherwise.
 */
पूर्णांक hfi1_verbs_send(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_other_headers *ohdr = शून्य;
	send_routine sr;
	पूर्णांक ret;
	u16 pkey;
	u32 slid;
	u8 l4 = 0;

	/* locate the pkey within the headers */
	अगर (ps->s_txreq->phdr.hdr.hdr_type) अणु
		काष्ठा hfi1_16b_header *hdr = &ps->s_txreq->phdr.hdr.opah;

		l4 = hfi1_16B_get_l4(hdr);
		अगर (l4 == OPA_16B_L4_IB_LOCAL)
			ohdr = &hdr->u.oth;
		अन्यथा अगर (l4 == OPA_16B_L4_IB_GLOBAL)
			ohdr = &hdr->u.l.oth;

		slid = hfi1_16B_get_slid(hdr);
		pkey = hfi1_16B_get_pkey(hdr);
	पूर्ण अन्यथा अणु
		काष्ठा ib_header *hdr = &ps->s_txreq->phdr.hdr.ibh;
		u8 lnh = ib_get_lnh(hdr);

		अगर (lnh == HFI1_LRH_GRH)
			ohdr = &hdr->u.l.oth;
		अन्यथा
			ohdr = &hdr->u.oth;
		slid = ib_get_slid(hdr);
		pkey = ib_bth_get_pkey(ohdr);
	पूर्ण

	अगर (likely(l4 != OPA_16B_L4_FM))
		ps->opcode = ib_bth_get_opcode(ohdr);
	अन्यथा
		ps->opcode = IB_OPCODE_UD_SEND_ONLY;

	sr = get_send_routine(qp, ps);
	ret = egress_pkey_check(dd->pport, slid, pkey,
				priv->s_sc, qp->s_pkey_index);
	अगर (unlikely(ret)) अणु
		/*
		 * The value we are वापसing here करोes not get propagated to
		 * the verbs caller. Thus we need to complete the request with
		 * error otherwise the caller could be sitting रुकोing on the
		 * completion event. Only करो this क्रम PIO. SDMA has its own
		 * mechanism क्रम handling the errors. So क्रम SDMA we can just
		 * वापस.
		 */
		अगर (sr == dd->process_pio_send) अणु
			अचिन्हित दीर्घ flags;

			hfi1_cdbg(PIO, "%s() Failed. Completing with err",
				  __func__);
			spin_lock_irqsave(&qp->s_lock, flags);
			rvt_send_complete(qp, qp->s_wqe, IB_WC_GENERAL_ERR);
			spin_unlock_irqrestore(&qp->s_lock, flags);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	अगर (sr == dd->process_dma_send && ioरुको_pio_pending(&priv->s_ioरुको))
		वापस pio_रुको(qp,
				ps->s_txreq->psc,
				ps,
				HFI1_S_WAIT_PIO_DRAIN);
	वापस sr(qp, ps, 0);
पूर्ण

/**
 * hfi1_fill_device_attr - Fill in rvt dev info device attributes.
 * @dd: the device data काष्ठाure
 */
अटल व्योम hfi1_fill_device_attr(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा rvt_dev_info *rdi = &dd->verbs_dev.rdi;
	u32 ver = dd->dc8051_ver;

	स_रखो(&rdi->dparms.props, 0, माप(rdi->dparms.props));

	rdi->dparms.props.fw_ver = ((u64)(dc8051_ver_maj(ver)) << 32) |
		((u64)(dc8051_ver_min(ver)) << 16) |
		(u64)dc8051_ver_patch(ver);

	rdi->dparms.props.device_cap_flags = IB_DEVICE_BAD_PKEY_CNTR |
			IB_DEVICE_BAD_QKEY_CNTR | IB_DEVICE_SHUTDOWN_PORT |
			IB_DEVICE_SYS_IMAGE_GUID | IB_DEVICE_RC_RNR_NAK_GEN |
			IB_DEVICE_PORT_ACTIVE_EVENT | IB_DEVICE_SRQ_RESIZE |
			IB_DEVICE_MEM_MGT_EXTENSIONS |
			IB_DEVICE_RDMA_NETDEV_OPA;
	rdi->dparms.props.page_size_cap = PAGE_SIZE;
	rdi->dparms.props.venकरोr_id = dd->oui1 << 16 | dd->oui2 << 8 | dd->oui3;
	rdi->dparms.props.venकरोr_part_id = dd->pcidev->device;
	rdi->dparms.props.hw_ver = dd->minrev;
	rdi->dparms.props.sys_image_guid = ib_hfi1_sys_image_guid;
	rdi->dparms.props.max_mr_size = U64_MAX;
	rdi->dparms.props.max_fast_reg_page_list_len = अच_पूर्णांक_उच्च;
	rdi->dparms.props.max_qp = hfi1_max_qps;
	rdi->dparms.props.max_qp_wr =
		(hfi1_max_qp_wrs >= HFI1_QP_WQE_INVALID ?
		 HFI1_QP_WQE_INVALID - 1 : hfi1_max_qp_wrs);
	rdi->dparms.props.max_send_sge = hfi1_max_sges;
	rdi->dparms.props.max_recv_sge = hfi1_max_sges;
	rdi->dparms.props.max_sge_rd = hfi1_max_sges;
	rdi->dparms.props.max_cq = hfi1_max_cqs;
	rdi->dparms.props.max_ah = hfi1_max_ahs;
	rdi->dparms.props.max_cqe = hfi1_max_cqes;
	rdi->dparms.props.max_pd = hfi1_max_pds;
	rdi->dparms.props.max_qp_rd_atom = HFI1_MAX_RDMA_ATOMIC;
	rdi->dparms.props.max_qp_init_rd_atom = 255;
	rdi->dparms.props.max_srq = hfi1_max_srqs;
	rdi->dparms.props.max_srq_wr = hfi1_max_srq_wrs;
	rdi->dparms.props.max_srq_sge = hfi1_max_srq_sges;
	rdi->dparms.props.atomic_cap = IB_ATOMIC_GLOB;
	rdi->dparms.props.max_pkeys = hfi1_get_npkeys(dd);
	rdi->dparms.props.max_mcast_grp = hfi1_max_mcast_grps;
	rdi->dparms.props.max_mcast_qp_attach = hfi1_max_mcast_qp_attached;
	rdi->dparms.props.max_total_mcast_qp_attach =
					rdi->dparms.props.max_mcast_qp_attach *
					rdi->dparms.props.max_mcast_grp;
पूर्ण

अटल अंतरभूत u16 opa_speed_to_ib(u16 in)
अणु
	u16 out = 0;

	अगर (in & OPA_LINK_SPEED_25G)
		out |= IB_SPEED_EDR;
	अगर (in & OPA_LINK_SPEED_12_5G)
		out |= IB_SPEED_FDR;

	वापस out;
पूर्ण

/*
 * Convert a single OPA link width (no multiple flags) to an IB value.
 * A zero OPA link width means link करोwn, which means the IB width value
 * is a करोn't care.
 */
अटल अंतरभूत u16 opa_width_to_ib(u16 in)
अणु
	चयन (in) अणु
	हाल OPA_LINK_WIDTH_1X:
	/* map 2x and 3x to 1x as they करोn't exist in IB */
	हाल OPA_LINK_WIDTH_2X:
	हाल OPA_LINK_WIDTH_3X:
		वापस IB_WIDTH_1X;
	शेष: /* link करोwn or unknown, वापस our largest width */
	हाल OPA_LINK_WIDTH_4X:
		वापस IB_WIDTH_4X;
	पूर्ण
पूर्ण

अटल पूर्णांक query_port(काष्ठा rvt_dev_info *rdi, u32 port_num,
		      काष्ठा ib_port_attr *props)
अणु
	काष्ठा hfi1_ibdev *verbs_dev = dev_from_rdi(rdi);
	काष्ठा hfi1_devdata *dd = dd_from_dev(verbs_dev);
	काष्ठा hfi1_pportdata *ppd = &dd->pport[port_num - 1];
	u32 lid = ppd->lid;

	/* props being zeroed by the caller, aव्योम zeroing it here */
	props->lid = lid ? lid : 0;
	props->lmc = ppd->lmc;
	/* OPA logical states match IB logical states */
	props->state = driver_lstate(ppd);
	props->phys_state = driver_pstate(ppd);
	props->gid_tbl_len = HFI1_GUIDS_PER_PORT;
	props->active_width = (u8)opa_width_to_ib(ppd->link_width_active);
	/* see rate_show() in ib core/sysfs.c */
	props->active_speed = opa_speed_to_ib(ppd->link_speed_active);
	props->max_vl_num = ppd->vls_supported;

	/* Once we are a "first class" citizen and have added the OPA MTUs to
	 * the core we can advertise the larger MTU क्रमागत to the ULPs, क्रम now
	 * advertise only 4K.
	 *
	 * Those applications which are either OPA aware or pass the MTU क्रमागत
	 * from the Path Records to us will get the new 8k MTU.  Those that
	 * attempt to process the MTU क्रमागत may fail in various ways.
	 */
	props->max_mtu = mtu_to_क्रमागत((!valid_ib_mtu(hfi1_max_mtu) ?
				      4096 : hfi1_max_mtu), IB_MTU_4096);
	props->active_mtu = !valid_ib_mtu(ppd->ibmtu) ? props->max_mtu :
		mtu_to_क्रमागत(ppd->ibmtu, IB_MTU_4096);
	props->phys_mtu = HFI1_CAP_IS_KSET(AIP) ? hfi1_max_mtu :
				ib_mtu_क्रमागत_to_पूर्णांक(props->max_mtu);

	वापस 0;
पूर्ण

अटल पूर्णांक modअगरy_device(काष्ठा ib_device *device,
			 पूर्णांक device_modअगरy_mask,
			 काष्ठा ib_device_modअगरy *device_modअगरy)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(device);
	अचिन्हित i;
	पूर्णांक ret;

	अगर (device_modअगरy_mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
				   IB_DEVICE_MODIFY_NODE_DESC)) अणु
		ret = -EOPNOTSUPP;
		जाओ bail;
	पूर्ण

	अगर (device_modअगरy_mask & IB_DEVICE_MODIFY_NODE_DESC) अणु
		स_नकल(device->node_desc, device_modअगरy->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		क्रम (i = 0; i < dd->num_pports; i++) अणु
			काष्ठा hfi1_ibport *ibp = &dd->pport[i].ibport_data;

			hfi1_node_desc_chg(ibp);
		पूर्ण
	पूर्ण

	अगर (device_modअगरy_mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID) अणु
		ib_hfi1_sys_image_guid =
			cpu_to_be64(device_modअगरy->sys_image_guid);
		क्रम (i = 0; i < dd->num_pports; i++) अणु
			काष्ठा hfi1_ibport *ibp = &dd->pport[i].ibport_data;

			hfi1_sys_guid_chg(ibp);
		पूर्ण
	पूर्ण

	ret = 0;

bail:
	वापस ret;
पूर्ण

अटल पूर्णांक shut_करोwn_port(काष्ठा rvt_dev_info *rdi, u32 port_num)
अणु
	काष्ठा hfi1_ibdev *verbs_dev = dev_from_rdi(rdi);
	काष्ठा hfi1_devdata *dd = dd_from_dev(verbs_dev);
	काष्ठा hfi1_pportdata *ppd = &dd->pport[port_num - 1];
	पूर्णांक ret;

	set_link_करोwn_reason(ppd, OPA_LINKDOWN_REASON_UNKNOWN, 0,
			     OPA_LINKDOWN_REASON_UNKNOWN);
	ret = set_link_state(ppd, HLS_DN_DOWNDEF);
	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_get_guid_be(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_ibport *rvp,
			    पूर्णांक guid_index, __be64 *guid)
अणु
	काष्ठा hfi1_ibport *ibp = container_of(rvp, काष्ठा hfi1_ibport, rvp);

	अगर (guid_index >= HFI1_GUIDS_PER_PORT)
		वापस -EINVAL;

	*guid = get_sguid(ibp, guid_index);
	वापस 0;
पूर्ण

/*
 * convert ah port,sl to sc
 */
u8 ah_to_sc(काष्ठा ib_device *ibdev, काष्ठा rdma_ah_attr *ah)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, rdma_ah_get_port_num(ah));

	वापस ibp->sl_to_sc[rdma_ah_get_sl(ah)];
पूर्ण

अटल पूर्णांक hfi1_check_ah(काष्ठा ib_device *ibdev, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd;
	u8 sc5;
	u8 sl;

	अगर (hfi1_check_mcast(rdma_ah_get_dlid(ah_attr)) &&
	    !(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
		वापस -EINVAL;

	/* test the mapping क्रम validity */
	ibp = to_iport(ibdev, rdma_ah_get_port_num(ah_attr));
	ppd = ppd_from_ibp(ibp);
	dd = dd_from_ppd(ppd);

	sl = rdma_ah_get_sl(ah_attr);
	अगर (sl >= ARRAY_SIZE(ibp->sl_to_sc))
		वापस -EINVAL;
	sl = array_index_nospec(sl, ARRAY_SIZE(ibp->sl_to_sc));

	sc5 = ibp->sl_to_sc[sl];
	अगर (sc_to_vlt(dd, sc5) > num_vls && sc_to_vlt(dd, sc5) != 0xf)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम hfi1_notअगरy_new_ah(काष्ठा ib_device *ibdev,
			       काष्ठा rdma_ah_attr *ah_attr,
			       काष्ठा rvt_ah *ah)
अणु
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd;
	u8 sc5;
	काष्ठा rdma_ah_attr *attr = &ah->attr;

	/*
	 * Do not trust पढ़ोing anything from rvt_ah at this poपूर्णांक as it is not
	 * करोne being setup. We can however modअगरy things which we need to set.
	 */

	ibp = to_iport(ibdev, rdma_ah_get_port_num(ah_attr));
	ppd = ppd_from_ibp(ibp);
	sc5 = ibp->sl_to_sc[rdma_ah_get_sl(&ah->attr)];
	hfi1_update_ah_attr(ibdev, attr);
	hfi1_make_opa_lid(attr);
	dd = dd_from_ppd(ppd);
	ah->vl = sc_to_vlt(dd, sc5);
	अगर (ah->vl < num_vls || ah->vl == 15)
		ah->log_pmtu = ilog2(dd->vld[ah->vl].mtu);
पूर्ण

/**
 * hfi1_get_npkeys - वापस the size of the PKEY table क्रम context 0
 * @dd: the hfi1_ib device
 */
अचिन्हित hfi1_get_npkeys(काष्ठा hfi1_devdata *dd)
अणु
	वापस ARRAY_SIZE(dd->pport[0].pkeys);
पूर्ण

अटल व्योम init_ibport(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_ibport *ibp = &ppd->ibport_data;
	माप_प्रकार sz = ARRAY_SIZE(ibp->sl_to_sc);
	पूर्णांक i;

	क्रम (i = 0; i < sz; i++) अणु
		ibp->sl_to_sc[i] = i;
		ibp->sc_to_sl[i] = i;
	पूर्ण

	क्रम (i = 0; i < RVT_MAX_TRAP_LISTS ; i++)
		INIT_LIST_HEAD(&ibp->rvp.trap_lists[i].list);
	समयr_setup(&ibp->rvp.trap_समयr, hfi1_handle_trap_समयr, 0);

	spin_lock_init(&ibp->rvp.lock);
	/* Set the prefix to the शेष value (see ch. 4.1.1) */
	ibp->rvp.gid_prefix = IB_DEFAULT_GID_PREFIX;
	ibp->rvp.sm_lid = 0;
	/*
	 * Below should only set bits defined in OPA PortInfo.CapabilityMask
	 * and PortInfo.CapabilityMask3
	 */
	ibp->rvp.port_cap_flags = IB_PORT_AUTO_MIGR_SUP |
		IB_PORT_CAP_MASK_NOTICE_SUP;
	ibp->rvp.port_cap3_flags = OPA_CAP_MASK3_IsSharedSpaceSupported;
	ibp->rvp.pma_counter_select[0] = IB_PMA_PORT_XMIT_DATA;
	ibp->rvp.pma_counter_select[1] = IB_PMA_PORT_RCV_DATA;
	ibp->rvp.pma_counter_select[2] = IB_PMA_PORT_XMIT_PKTS;
	ibp->rvp.pma_counter_select[3] = IB_PMA_PORT_RCV_PKTS;
	ibp->rvp.pma_counter_select[4] = IB_PMA_PORT_XMIT_WAIT;

	RCU_INIT_POINTER(ibp->rvp.qp[0], शून्य);
	RCU_INIT_POINTER(ibp->rvp.qp[1], शून्य);
पूर्ण

अटल व्योम hfi1_get_dev_fw_str(काष्ठा ib_device *ibdev, अक्षर *str)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);
	काष्ठा hfi1_ibdev *dev = dev_from_rdi(rdi);
	u32 ver = dd_from_dev(dev)->dc8051_ver;

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%u.%u.%u", dc8051_ver_maj(ver),
		 dc8051_ver_min(ver), dc8051_ver_patch(ver));
पूर्ण

अटल स्थिर अक्षर * स्थिर driver_cntr_names[] = अणु
	/* must be element 0*/
	"DRIVER_KernIntr",
	"DRIVER_ErrorIntr",
	"DRIVER_Tx_Errs",
	"DRIVER_Rcv_Errs",
	"DRIVER_HW_Errs",
	"DRIVER_NoPIOBufs",
	"DRIVER_CtxtsOpen",
	"DRIVER_RcvLen_Errs",
	"DRIVER_EgrBufFull",
	"DRIVER_EgrHdrFull"
पूर्ण;

अटल DEFINE_MUTEX(cntr_names_lock); /* protects the *_cntr_names bufers */
अटल स्थिर अक्षर **dev_cntr_names;
अटल स्थिर अक्षर **port_cntr_names;
पूर्णांक num_driver_cntrs = ARRAY_SIZE(driver_cntr_names);
अटल पूर्णांक num_dev_cntrs;
अटल पूर्णांक num_port_cntrs;
अटल पूर्णांक cntr_names_initialized;

/*
 * Convert a list of names separated by '\n' पूर्णांकo an array of शून्य terminated
 * strings. Optionally some entries can be reserved in the array to hold extra
 * बाह्यal strings.
 */
अटल पूर्णांक init_cntr_names(स्थिर अक्षर *names_in,
			   स्थिर माप_प्रकार names_len,
			   पूर्णांक num_extra_names,
			   पूर्णांक *num_cntrs,
			   स्थिर अक्षर ***cntr_names)
अणु
	अक्षर *names_out, *p, **q;
	पूर्णांक i, n;

	n = 0;
	क्रम (i = 0; i < names_len; i++)
		अगर (names_in[i] == '\n')
			n++;

	names_out = kदो_स्मृति((n + num_extra_names) * माप(अक्षर *) + names_len,
			    GFP_KERNEL);
	अगर (!names_out) अणु
		*num_cntrs = 0;
		*cntr_names = शून्य;
		वापस -ENOMEM;
	पूर्ण

	p = names_out + (n + num_extra_names) * माप(अक्षर *);
	स_नकल(p, names_in, names_len);

	q = (अक्षर **)names_out;
	क्रम (i = 0; i < n; i++) अणु
		q[i] = p;
		p = म_अक्षर(p, '\n');
		*p++ = '\0';
	पूर्ण

	*num_cntrs = n;
	*cntr_names = (स्थिर अक्षर **)names_out;
	वापस 0;
पूर्ण

अटल काष्ठा rdma_hw_stats *alloc_hw_stats(काष्ठा ib_device *ibdev,
					    u32 port_num)
अणु
	पूर्णांक i, err;

	mutex_lock(&cntr_names_lock);
	अगर (!cntr_names_initialized) अणु
		काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);

		err = init_cntr_names(dd->cntrnames,
				      dd->cntrnameslen,
				      num_driver_cntrs,
				      &num_dev_cntrs,
				      &dev_cntr_names);
		अगर (err) अणु
			mutex_unlock(&cntr_names_lock);
			वापस शून्य;
		पूर्ण

		क्रम (i = 0; i < num_driver_cntrs; i++)
			dev_cntr_names[num_dev_cntrs + i] =
				driver_cntr_names[i];

		err = init_cntr_names(dd->portcntrnames,
				      dd->portcntrnameslen,
				      0,
				      &num_port_cntrs,
				      &port_cntr_names);
		अगर (err) अणु
			kमुक्त(dev_cntr_names);
			dev_cntr_names = शून्य;
			mutex_unlock(&cntr_names_lock);
			वापस शून्य;
		पूर्ण
		cntr_names_initialized = 1;
	पूर्ण
	mutex_unlock(&cntr_names_lock);

	अगर (!port_num)
		वापस rdma_alloc_hw_stats_काष्ठा(
				dev_cntr_names,
				num_dev_cntrs + num_driver_cntrs,
				RDMA_HW_STATS_DEFAULT_LIFESPAN);
	अन्यथा
		वापस rdma_alloc_hw_stats_काष्ठा(
				port_cntr_names,
				num_port_cntrs,
				RDMA_HW_STATS_DEFAULT_LIFESPAN);
पूर्ण

अटल u64 hfi1_sps_पूर्णांकs(व्योम)
अणु
	अचिन्हित दीर्घ index, flags;
	काष्ठा hfi1_devdata *dd;
	u64 sps_पूर्णांकs = 0;

	xa_lock_irqsave(&hfi1_dev_table, flags);
	xa_क्रम_each(&hfi1_dev_table, index, dd) अणु
		sps_पूर्णांकs += get_all_cpu_total(dd->पूर्णांक_counter);
	पूर्ण
	xa_unlock_irqrestore(&hfi1_dev_table, flags);
	वापस sps_पूर्णांकs;
पूर्ण

अटल पूर्णांक get_hw_stats(काष्ठा ib_device *ibdev, काष्ठा rdma_hw_stats *stats,
			u32 port, पूर्णांक index)
अणु
	u64 *values;
	पूर्णांक count;

	अगर (!port) अणु
		u64 *stats = (u64 *)&hfi1_stats;
		पूर्णांक i;

		hfi1_पढ़ो_cntrs(dd_from_ibdev(ibdev), शून्य, &values);
		values[num_dev_cntrs] = hfi1_sps_पूर्णांकs();
		क्रम (i = 1; i < num_driver_cntrs; i++)
			values[num_dev_cntrs + i] = stats[i];
		count = num_dev_cntrs + num_driver_cntrs;
	पूर्ण अन्यथा अणु
		काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);

		hfi1_पढ़ो_portcntrs(ppd_from_ibp(ibp), शून्य, &values);
		count = num_port_cntrs;
	पूर्ण

	स_नकल(stats->value, values, count * माप(u64));
	वापस count;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops hfi1_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_HFI1,

	.alloc_hw_stats = alloc_hw_stats,
	.alloc_rdma_netdev = hfi1_vnic_alloc_rn,
	.get_dev_fw_str = hfi1_get_dev_fw_str,
	.get_hw_stats = get_hw_stats,
	.init_port = hfi1_create_port_files,
	.modअगरy_device = modअगरy_device,
	/* keep process mad in the driver */
	.process_mad = hfi1_process_mad,
	.rdma_netdev_get_params = hfi1_ipoib_rn_get_params,
पूर्ण;

/**
 * hfi1_रेजिस्टर_ib_device - रेजिस्टर our device with the infiniband core
 * @dd: the device data काष्ठाure
 * Return 0 अगर successful, त्रुटि_सं अगर unsuccessful.
 */
पूर्णांक hfi1_रेजिस्टर_ib_device(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_ibdev *dev = &dd->verbs_dev;
	काष्ठा ib_device *ibdev = &dev->rdi.ibdev;
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	काष्ठा hfi1_ibport *ibp = &ppd->ibport_data;
	अचिन्हित i;
	पूर्णांक ret;

	क्रम (i = 0; i < dd->num_pports; i++)
		init_ibport(ppd + i);

	/* Only need to initialize non-zero fields. */

	समयr_setup(&dev->mem_समयr, mem_समयr, 0);

	seqlock_init(&dev->ioरुको_lock);
	seqlock_init(&dev->txरुको_lock);
	INIT_LIST_HEAD(&dev->txरुको);
	INIT_LIST_HEAD(&dev->memरुको);

	ret = verbs_txreq_init(dev);
	अगर (ret)
		जाओ err_verbs_txreq;

	/* Use first-port GUID as node guid */
	ibdev->node_guid = get_sguid(ibp, HFI1_PORT_GUID_INDEX);

	/*
	 * The प्रणाली image GUID is supposed to be the same क्रम all
	 * HFIs in a single प्रणाली but since there can be other
	 * device types in the प्रणाली, we can't be sure this is unique.
	 */
	अगर (!ib_hfi1_sys_image_guid)
		ib_hfi1_sys_image_guid = ibdev->node_guid;
	ibdev->phys_port_cnt = dd->num_pports;
	ibdev->dev.parent = &dd->pcidev->dev;

	ib_set_device_ops(ibdev, &hfi1_dev_ops);

	strlcpy(ibdev->node_desc, init_utsname()->nodename,
		माप(ibdev->node_desc));

	/*
	 * Fill in rvt info object.
	 */
	dd->verbs_dev.rdi.driver_f.get_pci_dev = get_pci_dev;
	dd->verbs_dev.rdi.driver_f.check_ah = hfi1_check_ah;
	dd->verbs_dev.rdi.driver_f.notअगरy_new_ah = hfi1_notअगरy_new_ah;
	dd->verbs_dev.rdi.driver_f.get_guid_be = hfi1_get_guid_be;
	dd->verbs_dev.rdi.driver_f.query_port_state = query_port;
	dd->verbs_dev.rdi.driver_f.shut_करोwn_port = shut_करोwn_port;
	dd->verbs_dev.rdi.driver_f.cap_mask_chg = hfi1_cap_mask_chg;
	/*
	 * Fill in rvt info device attributes.
	 */
	hfi1_fill_device_attr(dd);

	/* queue pair */
	dd->verbs_dev.rdi.dparms.qp_table_size = hfi1_qp_table_size;
	dd->verbs_dev.rdi.dparms.qpn_start = 0;
	dd->verbs_dev.rdi.dparms.qpn_inc = 1;
	dd->verbs_dev.rdi.dparms.qos_shअगरt = dd->qos_shअगरt;
	dd->verbs_dev.rdi.dparms.qpn_res_start = RVT_KDETH_QP_BASE;
	dd->verbs_dev.rdi.dparms.qpn_res_end = RVT_AIP_QP_MAX;
	dd->verbs_dev.rdi.dparms.max_rdma_atomic = HFI1_MAX_RDMA_ATOMIC;
	dd->verbs_dev.rdi.dparms.psn_mask = PSN_MASK;
	dd->verbs_dev.rdi.dparms.psn_shअगरt = PSN_SHIFT;
	dd->verbs_dev.rdi.dparms.psn_modअगरy_mask = PSN_MODIFY_MASK;
	dd->verbs_dev.rdi.dparms.core_cap_flags = RDMA_CORE_PORT_INTEL_OPA |
						RDMA_CORE_CAP_OPA_AH;
	dd->verbs_dev.rdi.dparms.max_mad_size = OPA_MGMT_MAD_SIZE;

	dd->verbs_dev.rdi.driver_f.qp_priv_alloc = qp_priv_alloc;
	dd->verbs_dev.rdi.driver_f.qp_priv_init = hfi1_qp_priv_init;
	dd->verbs_dev.rdi.driver_f.qp_priv_मुक्त = qp_priv_मुक्त;
	dd->verbs_dev.rdi.driver_f.मुक्त_all_qps = मुक्त_all_qps;
	dd->verbs_dev.rdi.driver_f.notअगरy_qp_reset = notअगरy_qp_reset;
	dd->verbs_dev.rdi.driver_f.करो_send = hfi1_करो_send_from_rvt;
	dd->verbs_dev.rdi.driver_f.schedule_send = hfi1_schedule_send;
	dd->verbs_dev.rdi.driver_f.schedule_send_no_lock = _hfi1_schedule_send;
	dd->verbs_dev.rdi.driver_f.get_pmtu_from_attr = get_pmtu_from_attr;
	dd->verbs_dev.rdi.driver_f.notअगरy_error_qp = notअगरy_error_qp;
	dd->verbs_dev.rdi.driver_f.flush_qp_रुकोers = flush_qp_रुकोers;
	dd->verbs_dev.rdi.driver_f.stop_send_queue = stop_send_queue;
	dd->verbs_dev.rdi.driver_f.quiesce_qp = quiesce_qp;
	dd->verbs_dev.rdi.driver_f.notअगरy_error_qp = notअगरy_error_qp;
	dd->verbs_dev.rdi.driver_f.mtu_from_qp = mtu_from_qp;
	dd->verbs_dev.rdi.driver_f.mtu_to_path_mtu = mtu_to_path_mtu;
	dd->verbs_dev.rdi.driver_f.check_modअगरy_qp = hfi1_check_modअगरy_qp;
	dd->verbs_dev.rdi.driver_f.modअगरy_qp = hfi1_modअगरy_qp;
	dd->verbs_dev.rdi.driver_f.notअगरy_restart_rc = hfi1_restart_rc;
	dd->verbs_dev.rdi.driver_f.setup_wqe = hfi1_setup_wqe;
	dd->verbs_dev.rdi.driver_f.comp_vect_cpu_lookup =
						hfi1_comp_vect_mappings_lookup;

	/* completeion queue */
	dd->verbs_dev.rdi.ibdev.num_comp_vectors = dd->comp_vect_possible_cpus;
	dd->verbs_dev.rdi.dparms.node = dd->node;

	/* misc settings */
	dd->verbs_dev.rdi.flags = 0; /* Let rdmavt handle it all */
	dd->verbs_dev.rdi.dparms.lkey_table_size = hfi1_lkey_table_size;
	dd->verbs_dev.rdi.dparms.nports = dd->num_pports;
	dd->verbs_dev.rdi.dparms.npkeys = hfi1_get_npkeys(dd);
	dd->verbs_dev.rdi.dparms.sge_copy_mode = sge_copy_mode;
	dd->verbs_dev.rdi.dparms.wss_threshold = wss_threshold;
	dd->verbs_dev.rdi.dparms.wss_clean_period = wss_clean_period;
	dd->verbs_dev.rdi.dparms.reserved_operations = 1;
	dd->verbs_dev.rdi.dparms.extra_rdma_atomic = HFI1_TID_RDMA_WRITE_CNT;

	/* post send table */
	dd->verbs_dev.rdi.post_parms = hfi1_post_parms;

	/* opcode translation table */
	dd->verbs_dev.rdi.wc_opcode = ib_hfi1_wc_opcode;

	ppd = dd->pport;
	क्रम (i = 0; i < dd->num_pports; i++, ppd++)
		rvt_init_port(&dd->verbs_dev.rdi,
			      &ppd->ibport_data.rvp,
			      i,
			      ppd->pkeys);

	rdma_set_device_sysfs_group(&dd->verbs_dev.rdi.ibdev,
				    &ib_hfi1_attr_group);

	ret = rvt_रेजिस्टर_device(&dd->verbs_dev.rdi);
	अगर (ret)
		जाओ err_verbs_txreq;

	ret = hfi1_verbs_रेजिस्टर_sysfs(dd);
	अगर (ret)
		जाओ err_class;

	वापस ret;

err_class:
	rvt_unरेजिस्टर_device(&dd->verbs_dev.rdi);
err_verbs_txreq:
	verbs_txreq_निकास(dev);
	dd_dev_err(dd, "cannot register verbs: %d!\n", -ret);
	वापस ret;
पूर्ण

व्योम hfi1_unरेजिस्टर_ib_device(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_ibdev *dev = &dd->verbs_dev;

	hfi1_verbs_unरेजिस्टर_sysfs(dd);

	rvt_unरेजिस्टर_device(&dd->verbs_dev.rdi);

	अगर (!list_empty(&dev->txरुको))
		dd_dev_err(dd, "txwait list not empty!\n");
	अगर (!list_empty(&dev->memरुको))
		dd_dev_err(dd, "memwait list not empty!\n");

	del_समयr_sync(&dev->mem_समयr);
	verbs_txreq_निकास(dev);

	mutex_lock(&cntr_names_lock);
	kमुक्त(dev_cntr_names);
	kमुक्त(port_cntr_names);
	dev_cntr_names = शून्य;
	port_cntr_names = शून्य;
	cntr_names_initialized = 0;
	mutex_unlock(&cntr_names_lock);
पूर्ण

व्योम hfi1_cnp_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(packet->rcd);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा ib_header *hdr = packet->hdr;
	काष्ठा rvt_qp *qp = packet->qp;
	u32 lqpn, rqpn = 0;
	u16 rlid = 0;
	u8 sl, sc5, svc_type;

	चयन (packet->qp->ibqp.qp_type) अणु
	हाल IB_QPT_UC:
		rlid = rdma_ah_get_dlid(&qp->remote_ah_attr);
		rqpn = qp->remote_qpn;
		svc_type = IB_CC_SVCTYPE_UC;
		अवरोध;
	हाल IB_QPT_RC:
		rlid = rdma_ah_get_dlid(&qp->remote_ah_attr);
		rqpn = qp->remote_qpn;
		svc_type = IB_CC_SVCTYPE_RC;
		अवरोध;
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
	हाल IB_QPT_UD:
		svc_type = IB_CC_SVCTYPE_UD;
		अवरोध;
	शेष:
		ibp->rvp.n_pkt_drops++;
		वापस;
	पूर्ण

	sc5 = hfi1_9B_get_sc5(hdr, packet->rhf);
	sl = ibp->sc_to_sl[sc5];
	lqpn = qp->ibqp.qp_num;

	process_becn(ppd, sl, rlid, lqpn, rqpn, svc_type);
पूर्ण
