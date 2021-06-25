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
#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"
#समावेश "exp_rcv.h"
#समावेश "ipoib.h"

अटल u8 __get_ib_hdr_len(काष्ठा ib_header *hdr)
अणु
	काष्ठा ib_other_headers *ohdr;
	u8 opcode;

	अगर (ib_get_lnh(hdr) == HFI1_LRH_BTH)
		ohdr = &hdr->u.oth;
	अन्यथा
		ohdr = &hdr->u.l.oth;
	opcode = ib_bth_get_opcode(ohdr);
	वापस hdr_len_by_opcode[opcode] == 0 ?
	       0 : hdr_len_by_opcode[opcode] - (12 + 8);
पूर्ण

अटल u8 __get_16b_hdr_len(काष्ठा hfi1_16b_header *hdr)
अणु
	काष्ठा ib_other_headers *ohdr = शून्य;
	u8 opcode;
	u8 l4 = hfi1_16B_get_l4(hdr);

	अगर (l4 == OPA_16B_L4_FM) अणु
		opcode = IB_OPCODE_UD_SEND_ONLY;
		वापस (8 + 8); /* No BTH */
	पूर्ण

	अगर (l4 == OPA_16B_L4_IB_LOCAL)
		ohdr = &hdr->u.oth;
	अन्यथा
		ohdr = &hdr->u.l.oth;

	opcode = ib_bth_get_opcode(ohdr);
	वापस hdr_len_by_opcode[opcode] == 0 ?
	       0 : hdr_len_by_opcode[opcode] - (12 + 8 + 8);
पूर्ण

u8 hfi1_trace_packet_hdr_len(काष्ठा hfi1_packet *packet)
अणु
	अगर (packet->etype != RHF_RCV_TYPE_BYPASS)
		वापस __get_ib_hdr_len(packet->hdr);
	अन्यथा
		वापस __get_16b_hdr_len(packet->hdr);
पूर्ण

u8 hfi1_trace_opa_hdr_len(काष्ठा hfi1_opa_header *opa_hdr)
अणु
	अगर (!opa_hdr->hdr_type)
		वापस __get_ib_hdr_len(&opa_hdr->ibh);
	अन्यथा
		वापस __get_16b_hdr_len(&opa_hdr->opah);
पूर्ण

स्थिर अक्षर *hfi1_trace_get_packet_l4_str(u8 l4)
अणु
	अगर (l4)
		वापस "16B";
	अन्यथा
		वापस "9B";
पूर्ण

स्थिर अक्षर *hfi1_trace_get_packet_l2_str(u8 l2)
अणु
	चयन (l2) अणु
	हाल 0:
		वापस "0";
	हाल 1:
		वापस "1";
	हाल 2:
		वापस "16B";
	हाल 3:
		वापस "9B";
	पूर्ण
	वापस "";
पूर्ण

#घोषणा IMM_PRN  "imm:%d"
#घोषणा RETH_PRN "reth vaddr:0x%.16llx rkey:0x%.8x dlen:0x%.8x"
#घोषणा AETH_PRN "aeth syn:0x%.2x %s msn:0x%.8x"
#घोषणा DETH_PRN "deth qkey:0x%.8x sqpn:0x%.6x"
#घोषणा DETH_ENTROPY_PRN "deth qkey:0x%.8x sqpn:0x%.6x entropy:0x%.2x"
#घोषणा IETH_PRN "ieth rkey:0x%.8x"
#घोषणा ATOMICACKETH_PRN "origdata:%llx"
#घोषणा ATOMICETH_PRN "vaddr:0x%llx rkey:0x%.8x sdata:%llx cdata:%llx"
#घोषणा TID_RDMA_KDETH "kdeth0 0x%x kdeth1 0x%x"
#घोषणा TID_RDMA_KDETH_DATA "kdeth0 0x%x: kver %u sh %u intr %u tidctrl %u tid %x offset %x kdeth1 0x%x: jkey %x"
#घोषणा TID_READ_REQ_PRN "tid_flow_psn 0x%x tid_flow_qp 0x%x verbs_qp 0x%x"
#घोषणा TID_READ_RSP_PRN "verbs_qp 0x%x"
#घोषणा TID_WRITE_REQ_PRN "original_qp 0x%x"
#घोषणा TID_WRITE_RSP_PRN "tid_flow_psn 0x%x tid_flow_qp 0x%x verbs_qp 0x%x"
#घोषणा TID_WRITE_DATA_PRN "verbs_qp 0x%x"
#घोषणा TID_ACK_PRN "tid_flow_psn 0x%x verbs_psn 0x%x tid_flow_qp 0x%x verbs_qp 0x%x"
#घोषणा TID_RESYNC_PRN "verbs_qp 0x%x"

#घोषणा OP(transport, op) IB_OPCODE_## transport ## _ ## op

अटल स्थिर अक्षर *parse_syndrome(u8 syndrome)
अणु
	चयन (syndrome >> 5) अणु
	हाल 0:
		वापस "ACK";
	हाल 1:
		वापस "RNRNAK";
	हाल 3:
		वापस "NAK";
	पूर्ण
	वापस "";
पूर्ण

व्योम hfi1_trace_parse_9b_bth(काष्ठा ib_other_headers *ohdr,
			     u8 *ack, bool *becn, bool *fecn, u8 *mig,
			     u8 *se, u8 *pad, u8 *opcode, u8 *tver,
			     u16 *pkey, u32 *psn, u32 *qpn)
अणु
	*ack = ib_bth_get_ackreq(ohdr);
	*becn = ib_bth_get_becn(ohdr);
	*fecn = ib_bth_get_fecn(ohdr);
	*mig = ib_bth_get_migreq(ohdr);
	*se = ib_bth_get_se(ohdr);
	*pad = ib_bth_get_pad(ohdr);
	*opcode = ib_bth_get_opcode(ohdr);
	*tver = ib_bth_get_tver(ohdr);
	*pkey = ib_bth_get_pkey(ohdr);
	*psn = mask_psn(ib_bth_get_psn(ohdr));
	*qpn = ib_bth_get_qpn(ohdr);
पूर्ण

व्योम hfi1_trace_parse_16b_bth(काष्ठा ib_other_headers *ohdr,
			      u8 *ack, u8 *mig, u8 *opcode,
			      u8 *pad, u8 *se, u8 *tver,
			      u32 *psn, u32 *qpn)
अणु
	*ack = ib_bth_get_ackreq(ohdr);
	*mig = ib_bth_get_migreq(ohdr);
	*opcode = ib_bth_get_opcode(ohdr);
	*pad = ib_bth_get_pad(ohdr);
	*se = ib_bth_get_se(ohdr);
	*tver = ib_bth_get_tver(ohdr);
	*psn = mask_psn(ib_bth_get_psn(ohdr));
	*qpn = ib_bth_get_qpn(ohdr);
पूर्ण

व्योम hfi1_trace_parse_9b_hdr(काष्ठा ib_header *hdr, bool sc5,
			     u8 *lnh, u8 *lver, u8 *sl, u8 *sc,
			     u16 *len, u32 *dlid, u32 *slid)
अणु
	*lnh = ib_get_lnh(hdr);
	*lver = ib_get_lver(hdr);
	*sl = ib_get_sl(hdr);
	*sc = ib_get_sc(hdr) | (sc5 << 4);
	*len = ib_get_len(hdr);
	*dlid = ib_get_dlid(hdr);
	*slid = ib_get_slid(hdr);
पूर्ण

व्योम hfi1_trace_parse_16b_hdr(काष्ठा hfi1_16b_header *hdr,
			      u8 *age, bool *becn, bool *fecn,
			      u8 *l4, u8 *rc, u8 *sc,
			      u16 *entropy, u16 *len, u16 *pkey,
			      u32 *dlid, u32 *slid)
अणु
	*age = hfi1_16B_get_age(hdr);
	*becn = hfi1_16B_get_becn(hdr);
	*fecn = hfi1_16B_get_fecn(hdr);
	*l4 = hfi1_16B_get_l4(hdr);
	*rc = hfi1_16B_get_rc(hdr);
	*sc = hfi1_16B_get_sc(hdr);
	*entropy = hfi1_16B_get_entropy(hdr);
	*len = hfi1_16B_get_len(hdr);
	*pkey = hfi1_16B_get_pkey(hdr);
	*dlid = hfi1_16B_get_dlid(hdr);
	*slid = hfi1_16B_get_slid(hdr);
पूर्ण

#घोषणा LRH_PRN "len:%d sc:%d dlid:0x%.4x slid:0x%.4x "
#घोषणा LRH_9B_PRN "lnh:%d,%s lver:%d sl:%d"
#घोषणा LRH_16B_PRN "age:%d becn:%d fecn:%d l4:%d " \
		    "rc:%d sc:%d pkey:0x%.4x entropy:0x%.4x"
स्थिर अक्षर *hfi1_trace_fmt_lrh(काष्ठा trace_seq *p, bool bypass,
			       u8 age, bool becn, bool fecn, u8 l4,
			       u8 lnh, स्थिर अक्षर *lnh_name, u8 lver,
			       u8 rc, u8 sc, u8 sl, u16 entropy,
			       u16 len, u16 pkey, u32 dlid, u32 slid)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, LRH_PRN, len, sc, dlid, slid);

	अगर (bypass)
		trace_seq_म_लिखो(p, LRH_16B_PRN,
				 age, becn, fecn, l4, rc, sc, pkey, entropy);

	अन्यथा
		trace_seq_म_लिखो(p, LRH_9B_PRN,
				 lnh, lnh_name, lver, sl);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

#घोषणा BTH_9B_PRN \
	"op:0x%.2x,%s se:%d m:%d pad:%d tver:%d pkey:0x%.4x " \
	"f:%d b:%d qpn:0x%.6x a:%d psn:0x%.8x"
#घोषणा BTH_16B_PRN \
	"op:0x%.2x,%s se:%d m:%d pad:%d tver:%d " \
	"qpn:0x%.6x a:%d psn:0x%.8x"
#घोषणा L4_FM_16B_PRN \
	"op:0x%.2x,%s dest_qpn:0x%.6x src_qpn:0x%.6x"
स्थिर अक्षर *hfi1_trace_fmt_rest(काष्ठा trace_seq *p, bool bypass, u8 l4,
				u8 ack, bool becn, bool fecn, u8 mig,
				u8 se, u8 pad, u8 opcode, स्थिर अक्षर *opname,
				u8 tver, u16 pkey, u32 psn, u32 qpn,
				u32 dest_qpn, u32 src_qpn)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	अगर (bypass)
		अगर (l4 == OPA_16B_L4_FM)
			trace_seq_म_लिखो(p, L4_FM_16B_PRN,
					 opcode, opname, dest_qpn, src_qpn);
		अन्यथा
			trace_seq_म_लिखो(p, BTH_16B_PRN,
					 opcode, opname,
					 se, mig, pad, tver, qpn, ack, psn);

	अन्यथा
		trace_seq_म_लिखो(p, BTH_9B_PRN,
				 opcode, opname,
				 se, mig, pad, tver, pkey, fecn, becn,
				 qpn, ack, psn);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *parse_everbs_hdrs(
	काष्ठा trace_seq *p,
	u8 opcode, u8 l4, u32 dest_qpn, u32 src_qpn,
	व्योम *ehdrs)
अणु
	जोड़ ib_ehdrs *eh = ehdrs;
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	अगर (l4 == OPA_16B_L4_FM) अणु
		trace_seq_म_लिखो(p, "mgmt pkt");
		जाओ out;
	पूर्ण

	चयन (opcode) अणु
	/* imm */
	हाल OP(RC, SEND_LAST_WITH_IMMEDIATE):
	हाल OP(UC, SEND_LAST_WITH_IMMEDIATE):
	हाल OP(RC, SEND_ONLY_WITH_IMMEDIATE):
	हाल OP(UC, SEND_ONLY_WITH_IMMEDIATE):
	हाल OP(RC, RDMA_WRITE_LAST_WITH_IMMEDIATE):
	हाल OP(UC, RDMA_WRITE_LAST_WITH_IMMEDIATE):
		trace_seq_म_लिखो(p, IMM_PRN,
				 be32_to_cpu(eh->imm_data));
		अवरोध;
	/* reth + imm */
	हाल OP(RC, RDMA_WRITE_ONLY_WITH_IMMEDIATE):
	हाल OP(UC, RDMA_WRITE_ONLY_WITH_IMMEDIATE):
		trace_seq_म_लिखो(p, RETH_PRN " " IMM_PRN,
				 get_ib_reth_vaddr(&eh->rc.reth),
				 be32_to_cpu(eh->rc.reth.rkey),
				 be32_to_cpu(eh->rc.reth.length),
				 be32_to_cpu(eh->rc.imm_data));
		अवरोध;
	/* reth */
	हाल OP(RC, RDMA_READ_REQUEST):
	हाल OP(RC, RDMA_WRITE_FIRST):
	हाल OP(UC, RDMA_WRITE_FIRST):
	हाल OP(RC, RDMA_WRITE_ONLY):
	हाल OP(UC, RDMA_WRITE_ONLY):
		trace_seq_म_लिखो(p, RETH_PRN,
				 get_ib_reth_vaddr(&eh->rc.reth),
				 be32_to_cpu(eh->rc.reth.rkey),
				 be32_to_cpu(eh->rc.reth.length));
		अवरोध;
	हाल OP(RC, RDMA_READ_RESPONSE_FIRST):
	हाल OP(RC, RDMA_READ_RESPONSE_LAST):
	हाल OP(RC, RDMA_READ_RESPONSE_ONLY):
	हाल OP(RC, ACKNOWLEDGE):
		trace_seq_म_लिखो(p, AETH_PRN, be32_to_cpu(eh->aeth) >> 24,
				 parse_syndrome(be32_to_cpu(eh->aeth) >> 24),
				 be32_to_cpu(eh->aeth) & IB_MSN_MASK);
		अवरोध;
	हाल OP(TID_RDMA, WRITE_REQ):
		trace_seq_म_लिखो(p, TID_RDMA_KDETH " " RETH_PRN " "
				 TID_WRITE_REQ_PRN,
				 le32_to_cpu(eh->tid_rdma.w_req.kdeth0),
				 le32_to_cpu(eh->tid_rdma.w_req.kdeth1),
				 ib_u64_get(&eh->tid_rdma.w_req.reth.vaddr),
				 be32_to_cpu(eh->tid_rdma.w_req.reth.rkey),
				 be32_to_cpu(eh->tid_rdma.w_req.reth.length),
				 be32_to_cpu(eh->tid_rdma.w_req.verbs_qp));
		अवरोध;
	हाल OP(TID_RDMA, WRITE_RESP):
		trace_seq_म_लिखो(p, TID_RDMA_KDETH " " AETH_PRN " "
				 TID_WRITE_RSP_PRN,
				 le32_to_cpu(eh->tid_rdma.w_rsp.kdeth0),
				 le32_to_cpu(eh->tid_rdma.w_rsp.kdeth1),
				 be32_to_cpu(eh->tid_rdma.w_rsp.aeth) >> 24,
				 parse_syndrome(/* aeth */
					 be32_to_cpu(eh->tid_rdma.w_rsp.aeth)
					 >> 24),
				 (be32_to_cpu(eh->tid_rdma.w_rsp.aeth) &
				  IB_MSN_MASK),
				 be32_to_cpu(eh->tid_rdma.w_rsp.tid_flow_psn),
				 be32_to_cpu(eh->tid_rdma.w_rsp.tid_flow_qp),
				 be32_to_cpu(eh->tid_rdma.w_rsp.verbs_qp));
		अवरोध;
	हाल OP(TID_RDMA, WRITE_DATA_LAST):
	हाल OP(TID_RDMA, WRITE_DATA):
		trace_seq_म_लिखो(p, TID_RDMA_KDETH_DATA " " TID_WRITE_DATA_PRN,
				 le32_to_cpu(eh->tid_rdma.w_data.kdeth0),
				 KDETH_GET(eh->tid_rdma.w_data.kdeth0, KVER),
				 KDETH_GET(eh->tid_rdma.w_data.kdeth0, SH),
				 KDETH_GET(eh->tid_rdma.w_data.kdeth0, INTR),
				 KDETH_GET(eh->tid_rdma.w_data.kdeth0, TIDCTRL),
				 KDETH_GET(eh->tid_rdma.w_data.kdeth0, TID),
				 KDETH_GET(eh->tid_rdma.w_data.kdeth0, OFFSET),
				 le32_to_cpu(eh->tid_rdma.w_data.kdeth1),
				 KDETH_GET(eh->tid_rdma.w_data.kdeth1, JKEY),
				 be32_to_cpu(eh->tid_rdma.w_data.verbs_qp));
		अवरोध;
	हाल OP(TID_RDMA, READ_REQ):
		trace_seq_म_लिखो(p, TID_RDMA_KDETH " " RETH_PRN " "
				 TID_READ_REQ_PRN,
				 le32_to_cpu(eh->tid_rdma.r_req.kdeth0),
				 le32_to_cpu(eh->tid_rdma.r_req.kdeth1),
				 ib_u64_get(&eh->tid_rdma.r_req.reth.vaddr),
				 be32_to_cpu(eh->tid_rdma.r_req.reth.rkey),
				 be32_to_cpu(eh->tid_rdma.r_req.reth.length),
				 be32_to_cpu(eh->tid_rdma.r_req.tid_flow_psn),
				 be32_to_cpu(eh->tid_rdma.r_req.tid_flow_qp),
				 be32_to_cpu(eh->tid_rdma.r_req.verbs_qp));
		अवरोध;
	हाल OP(TID_RDMA, READ_RESP):
		trace_seq_म_लिखो(p, TID_RDMA_KDETH_DATA " " AETH_PRN " "
				 TID_READ_RSP_PRN,
				 le32_to_cpu(eh->tid_rdma.r_rsp.kdeth0),
				 KDETH_GET(eh->tid_rdma.r_rsp.kdeth0, KVER),
				 KDETH_GET(eh->tid_rdma.r_rsp.kdeth0, SH),
				 KDETH_GET(eh->tid_rdma.r_rsp.kdeth0, INTR),
				 KDETH_GET(eh->tid_rdma.r_rsp.kdeth0, TIDCTRL),
				 KDETH_GET(eh->tid_rdma.r_rsp.kdeth0, TID),
				 KDETH_GET(eh->tid_rdma.r_rsp.kdeth0, OFFSET),
				 le32_to_cpu(eh->tid_rdma.r_rsp.kdeth1),
				 KDETH_GET(eh->tid_rdma.r_rsp.kdeth1, JKEY),
				 be32_to_cpu(eh->tid_rdma.r_rsp.aeth) >> 24,
				 parse_syndrome(/* aeth */
					 be32_to_cpu(eh->tid_rdma.r_rsp.aeth)
					 >> 24),
				 (be32_to_cpu(eh->tid_rdma.r_rsp.aeth) &
				  IB_MSN_MASK),
				 be32_to_cpu(eh->tid_rdma.r_rsp.verbs_qp));
		अवरोध;
	हाल OP(TID_RDMA, ACK):
		trace_seq_म_लिखो(p, TID_RDMA_KDETH " " AETH_PRN " "
				 TID_ACK_PRN,
				 le32_to_cpu(eh->tid_rdma.ack.kdeth0),
				 le32_to_cpu(eh->tid_rdma.ack.kdeth1),
				 be32_to_cpu(eh->tid_rdma.ack.aeth) >> 24,
				 parse_syndrome(/* aeth */
					 be32_to_cpu(eh->tid_rdma.ack.aeth)
					 >> 24),
				 (be32_to_cpu(eh->tid_rdma.ack.aeth) &
				  IB_MSN_MASK),
				 be32_to_cpu(eh->tid_rdma.ack.tid_flow_psn),
				 be32_to_cpu(eh->tid_rdma.ack.verbs_psn),
				 be32_to_cpu(eh->tid_rdma.ack.tid_flow_qp),
				 be32_to_cpu(eh->tid_rdma.ack.verbs_qp));
		अवरोध;
	हाल OP(TID_RDMA, RESYNC):
		trace_seq_म_लिखो(p, TID_RDMA_KDETH " " TID_RESYNC_PRN,
				 le32_to_cpu(eh->tid_rdma.resync.kdeth0),
				 le32_to_cpu(eh->tid_rdma.resync.kdeth1),
				 be32_to_cpu(eh->tid_rdma.resync.verbs_qp));
		अवरोध;
	/* aeth + atomicacketh */
	हाल OP(RC, ATOMIC_ACKNOWLEDGE):
		trace_seq_म_लिखो(p, AETH_PRN " " ATOMICACKETH_PRN,
				 be32_to_cpu(eh->at.aeth) >> 24,
				 parse_syndrome(be32_to_cpu(eh->at.aeth) >> 24),
				 be32_to_cpu(eh->at.aeth) & IB_MSN_MASK,
				 ib_u64_get(&eh->at.atomic_ack_eth));
		अवरोध;
	/* atomiceth */
	हाल OP(RC, COMPARE_SWAP):
	हाल OP(RC, FETCH_ADD):
		trace_seq_म_लिखो(p, ATOMICETH_PRN,
				 get_ib_ateth_vaddr(&eh->atomic_eth),
				 eh->atomic_eth.rkey,
				 get_ib_ateth_swap(&eh->atomic_eth),
				 get_ib_ateth_compare(&eh->atomic_eth));
		अवरोध;
	/* deth */
	हाल OP(UD, SEND_ONLY):
		trace_seq_म_लिखो(p, DETH_ENTROPY_PRN,
				 be32_to_cpu(eh->ud.deth[0]),
				 be32_to_cpu(eh->ud.deth[1]) & RVT_QPN_MASK,
				 be32_to_cpu(eh->ud.deth[1]) >>
					     HFI1_IPOIB_ENTROPY_SHIFT);
		अवरोध;
	हाल OP(UD, SEND_ONLY_WITH_IMMEDIATE):
		trace_seq_म_लिखो(p, DETH_PRN,
				 be32_to_cpu(eh->ud.deth[0]),
				 be32_to_cpu(eh->ud.deth[1]) & RVT_QPN_MASK);
		अवरोध;
	/* ieth */
	हाल OP(RC, SEND_LAST_WITH_INVALIDATE):
	हाल OP(RC, SEND_ONLY_WITH_INVALIDATE):
		trace_seq_म_लिखो(p, IETH_PRN,
				 be32_to_cpu(eh->ieth));
		अवरोध;
	पूर्ण
out:
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

स्थिर अक्षर *parse_sdma_flags(
	काष्ठा trace_seq *p,
	u64 desc0, u64 desc1)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	अक्षर flags[5] = अणु 'x', 'x', 'x', 'x', 0 पूर्ण;

	flags[0] = (desc1 & SDMA_DESC1_INT_REQ_FLAG) ? 'I' : '-';
	flags[1] = (desc1 & SDMA_DESC1_HEAD_TO_HOST_FLAG) ?  'H' : '-';
	flags[2] = (desc0 & SDMA_DESC0_FIRST_DESC_FLAG) ? 'F' : '-';
	flags[3] = (desc0 & SDMA_DESC0_LAST_DESC_FLAG) ? 'L' : '-';
	trace_seq_म_लिखो(p, "%s", flags);
	अगर (desc0 & SDMA_DESC0_FIRST_DESC_FLAG)
		trace_seq_म_लिखो(p, " amode:%u aidx:%u alen:%u",
				 (u8)((desc1 >> SDMA_DESC1_HEADER_MODE_SHIFT) &
				      SDMA_DESC1_HEADER_MODE_MASK),
				 (u8)((desc1 >> SDMA_DESC1_HEADER_INDEX_SHIFT) &
				      SDMA_DESC1_HEADER_INDEX_MASK),
				 (u8)((desc1 >> SDMA_DESC1_HEADER_DWS_SHIFT) &
				      SDMA_DESC1_HEADER_DWS_MASK));
	वापस ret;
पूर्ण

स्थिर अक्षर *prपूर्णांक_u32_array(
	काष्ठा trace_seq *p,
	u32 *arr, पूर्णांक len)
अणु
	पूर्णांक i;
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	क्रम (i = 0; i < len ; i++)
		trace_seq_म_लिखो(p, "%s%#x", i == 0 ? "" : " ", arr[i]);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

u8 hfi1_trace_get_tid_ctrl(u32 ent)
अणु
	वापस EXP_TID_GET(ent, CTRL);
पूर्ण

u16 hfi1_trace_get_tid_len(u32 ent)
अणु
	वापस EXP_TID_GET(ent, LEN);
पूर्ण

u16 hfi1_trace_get_tid_idx(u32 ent)
अणु
	वापस EXP_TID_GET(ent, IDX);
पूर्ण

काष्ठा hfi1_ctxt_hist अणु
	atomic_t count;
	atomic_t data[255];
पूर्ण;

काष्ठा hfi1_ctxt_hist hist = अणु
	.count = ATOMIC_INIT(0)
पूर्ण;

स्थिर अक्षर *hfi1_trace_prपूर्णांक_rsm_hist(काष्ठा trace_seq *p, अचिन्हित पूर्णांक ctxt)
अणु
	पूर्णांक i, len = ARRAY_SIZE(hist.data);
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	अचिन्हित दीर्घ packet_count = atomic_fetch_inc(&hist.count);

	trace_seq_म_लिखो(p, "packet[%lu]", packet_count);
	क्रम (i = 0; i < len; ++i) अणु
		अचिन्हित दीर्घ val;
		atomic_t *count = &hist.data[i];

		अगर (ctxt == i)
			val = atomic_fetch_inc(count);
		अन्यथा
			val = atomic_पढ़ो(count);

		अगर (val)
			trace_seq_म_लिखो(p, "(%d:%lu)", i, val);
	पूर्ण
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

__hfi1_trace_fn(AFFINITY);
__hfi1_trace_fn(PKT);
__hfi1_trace_fn(PROC);
__hfi1_trace_fn(SDMA);
__hfi1_trace_fn(LINKVERB);
__hfi1_trace_fn(DEBUG);
__hfi1_trace_fn(SNOOP);
__hfi1_trace_fn(CNTR);
__hfi1_trace_fn(PIO);
__hfi1_trace_fn(DC8051);
__hfi1_trace_fn(FIRMWARE);
__hfi1_trace_fn(RCVCTRL);
__hfi1_trace_fn(TID);
__hfi1_trace_fn(MMU);
__hfi1_trace_fn(IOCTL);
