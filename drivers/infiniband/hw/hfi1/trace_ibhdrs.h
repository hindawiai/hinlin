<शैली गुरु>
/*
 * Copyright(c) 2015 - 2017 Intel Corporation.
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
#अगर !defined(__HFI1_TRACE_IBHDRS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HFI1_TRACE_IBHDRS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "hfi.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hfi1_ibhdrs

#घोषणा ib_opcode_name(opcode) अणु IB_OPCODE_##opcode, #opcode  पूर्ण
#घोषणा show_ib_opcode(opcode)                             \
__prपूर्णांक_symbolic(opcode,                                   \
	ib_opcode_name(RC_SEND_FIRST),                     \
	ib_opcode_name(RC_SEND_MIDDLE),                    \
	ib_opcode_name(RC_SEND_LAST),                      \
	ib_opcode_name(RC_SEND_LAST_WITH_IMMEDIATE),       \
	ib_opcode_name(RC_SEND_ONLY),                      \
	ib_opcode_name(RC_SEND_ONLY_WITH_IMMEDIATE),       \
	ib_opcode_name(RC_RDMA_WRITE_FIRST),               \
	ib_opcode_name(RC_RDMA_WRITE_MIDDLE),              \
	ib_opcode_name(RC_RDMA_WRITE_LAST),                \
	ib_opcode_name(RC_RDMA_WRITE_LAST_WITH_IMMEDIATE), \
	ib_opcode_name(RC_RDMA_WRITE_ONLY),                \
	ib_opcode_name(RC_RDMA_WRITE_ONLY_WITH_IMMEDIATE), \
	ib_opcode_name(RC_RDMA_READ_REQUEST),              \
	ib_opcode_name(RC_RDMA_READ_RESPONSE_FIRST),       \
	ib_opcode_name(RC_RDMA_READ_RESPONSE_MIDDLE),      \
	ib_opcode_name(RC_RDMA_READ_RESPONSE_LAST),        \
	ib_opcode_name(RC_RDMA_READ_RESPONSE_ONLY),        \
	ib_opcode_name(RC_ACKNOWLEDGE),                    \
	ib_opcode_name(RC_ATOMIC_ACKNOWLEDGE),             \
	ib_opcode_name(RC_COMPARE_SWAP),                   \
	ib_opcode_name(RC_FETCH_ADD),                      \
	ib_opcode_name(RC_SEND_LAST_WITH_INVALIDATE),      \
	ib_opcode_name(RC_SEND_ONLY_WITH_INVALIDATE),      \
	ib_opcode_name(TID_RDMA_WRITE_REQ),	           \
	ib_opcode_name(TID_RDMA_WRITE_RESP),	           \
	ib_opcode_name(TID_RDMA_WRITE_DATA),	           \
	ib_opcode_name(TID_RDMA_WRITE_DATA_LAST),          \
	ib_opcode_name(TID_RDMA_READ_REQ),	           \
	ib_opcode_name(TID_RDMA_READ_RESP),	           \
	ib_opcode_name(TID_RDMA_RESYNC),	           \
	ib_opcode_name(TID_RDMA_ACK),                      \
	ib_opcode_name(UC_SEND_FIRST),                     \
	ib_opcode_name(UC_SEND_MIDDLE),                    \
	ib_opcode_name(UC_SEND_LAST),                      \
	ib_opcode_name(UC_SEND_LAST_WITH_IMMEDIATE),       \
	ib_opcode_name(UC_SEND_ONLY),                      \
	ib_opcode_name(UC_SEND_ONLY_WITH_IMMEDIATE),       \
	ib_opcode_name(UC_RDMA_WRITE_FIRST),               \
	ib_opcode_name(UC_RDMA_WRITE_MIDDLE),              \
	ib_opcode_name(UC_RDMA_WRITE_LAST),                \
	ib_opcode_name(UC_RDMA_WRITE_LAST_WITH_IMMEDIATE), \
	ib_opcode_name(UC_RDMA_WRITE_ONLY),                \
	ib_opcode_name(UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE), \
	ib_opcode_name(UD_SEND_ONLY),                      \
	ib_opcode_name(UD_SEND_ONLY_WITH_IMMEDIATE),       \
	ib_opcode_name(CNP))

u8 ibhdr_exhdr_len(काष्ठा ib_header *hdr);
स्थिर अक्षर *parse_everbs_hdrs(काष्ठा trace_seq *p, u8 opcode,
			      u8 l4, u32 dest_qpn, u32 src_qpn,
			      व्योम *ehdrs);
u8 hfi1_trace_opa_hdr_len(काष्ठा hfi1_opa_header *opah);
u8 hfi1_trace_packet_hdr_len(काष्ठा hfi1_packet *packet);
स्थिर अक्षर *hfi1_trace_get_packet_l4_str(u8 l4);
व्योम hfi1_trace_parse_9b_bth(काष्ठा ib_other_headers *ohdr,
			     u8 *ack, bool *becn, bool *fecn, u8 *mig,
			     u8 *se, u8 *pad, u8 *opcode, u8 *tver,
			     u16 *pkey, u32 *psn, u32 *qpn);
व्योम hfi1_trace_parse_9b_hdr(काष्ठा ib_header *hdr, bool sc5,
			     u8 *lnh, u8 *lver, u8 *sl, u8 *sc,
			     u16 *len, u32 *dlid, u32 *slid);
व्योम hfi1_trace_parse_16b_bth(काष्ठा ib_other_headers *ohdr,
			      u8 *ack, u8 *mig, u8 *opcode,
			      u8 *pad, u8 *se, u8 *tver,
			      u32 *psn, u32 *qpn);
व्योम hfi1_trace_parse_16b_hdr(काष्ठा hfi1_16b_header *hdr,
			      u8 *age, bool *becn, bool *fecn,
			      u8 *l4, u8 *rc, u8 *sc,
			      u16 *entropy, u16 *len, u16 *pkey,
			      u32 *dlid, u32 *slid);

स्थिर अक्षर *hfi1_trace_fmt_lrh(काष्ठा trace_seq *p, bool bypass,
			       u8 age, bool becn, bool fecn, u8 l4,
			       u8 lnh, स्थिर अक्षर *lnh_name, u8 lver,
			       u8 rc, u8 sc, u8 sl, u16 entropy,
			       u16 len, u16 pkey, u32 dlid, u32 slid);

स्थिर अक्षर *hfi1_trace_fmt_rest(काष्ठा trace_seq *p, bool bypass, u8 l4,
				u8 ack, bool becn, bool fecn, u8 mig,
				u8 se, u8 pad, u8 opcode, स्थिर अक्षर *opname,
				u8 tver, u16 pkey, u32 psn, u32 qpn,
				u32 dest_qpn, u32 src_qpn);

स्थिर अक्षर *hfi1_trace_get_packet_l2_str(u8 l2);

#घोषणा __parse_ib_ehdrs(op, l4, dest_qpn, src_qpn, ehdrs) \
			 parse_everbs_hdrs(p, op, l4, dest_qpn, src_qpn, ehdrs)

#घोषणा lrh_name(lrh) अणु HFI1_##lrh, #lrh पूर्ण
#घोषणा show_lnh(lrh)                    \
__prपूर्णांक_symbolic(lrh,                    \
	lrh_name(LRH_BTH),               \
	lrh_name(LRH_GRH))

DECLARE_EVENT_CLASS(hfi1_input_ibhdr_ढाँचा,
		    TP_PROTO(काष्ठा hfi1_devdata *dd,
			     काष्ठा hfi1_packet *packet,
			     bool sc5),
		    TP_ARGS(dd, packet, sc5),
		    TP_STRUCT__entry(
			DD_DEV_ENTRY(dd)
			__field(u8, etype)
			__field(u8, ack)
			__field(u8, age)
			__field(bool, becn)
			__field(bool, fecn)
			__field(u8, l2)
			__field(u8, l4)
			__field(u8, lnh)
			__field(u8, lver)
			__field(u8, mig)
			__field(u8, opcode)
			__field(u8, pad)
			__field(u8, rc)
			__field(u8, sc)
			__field(u8, se)
			__field(u8, sl)
			__field(u8, tver)
			__field(u16, entropy)
			__field(u16, len)
			__field(u16, pkey)
			__field(u32, dlid)
			__field(u32, psn)
			__field(u32, qpn)
			__field(u32, slid)
			__field(u32, dest_qpn)
			__field(u32, src_qpn)
			/* extended headers */
			__dynamic_array(u8, ehdrs,
					hfi1_trace_packet_hdr_len(packet))
			),
		    TP_fast_assign(
			DD_DEV_ASSIGN(dd);

			__entry->etype = packet->etype;
			__entry->l2 = hfi1_16B_get_l2(packet->hdr);
			__entry->dest_qpn = 0;
			__entry->src_qpn = 0;
			अगर (__entry->etype == RHF_RCV_TYPE_BYPASS) अणु
				hfi1_trace_parse_16b_hdr(packet->hdr,
							 &__entry->age,
							 &__entry->becn,
							 &__entry->fecn,
							 &__entry->l4,
							 &__entry->rc,
							 &__entry->sc,
							 &__entry->entropy,
							 &__entry->len,
							 &__entry->pkey,
							 &__entry->dlid,
							 &__entry->slid);

				अगर (__entry->l4 == OPA_16B_L4_FM) अणु
					__entry->opcode = IB_OPCODE_UD_SEND_ONLY;
					__entry->dest_qpn = hfi1_16B_get_dest_qpn(packet->mgmt);
					__entry->src_qpn = hfi1_16B_get_src_qpn(packet->mgmt);
				पूर्ण  अन्यथा अणु
					hfi1_trace_parse_16b_bth(packet->ohdr,
								 &__entry->ack,
								 &__entry->mig,
								 &__entry->opcode,
								 &__entry->pad,
								 &__entry->se,
								 &__entry->tver,
								 &__entry->psn,
								 &__entry->qpn);
				पूर्ण
			पूर्ण अन्यथा अणु
				__entry->l4 = OPA_16B_L4_9B;
				hfi1_trace_parse_9b_hdr(packet->hdr, sc5,
							&__entry->lnh,
							&__entry->lver,
							&__entry->sl,
							&__entry->sc,
							&__entry->len,
							&__entry->dlid,
							&__entry->slid);

				  hfi1_trace_parse_9b_bth(packet->ohdr,
							  &__entry->ack,
							  &__entry->becn,
							  &__entry->fecn,
							  &__entry->mig,
							  &__entry->se,
							  &__entry->pad,
							  &__entry->opcode,
							  &__entry->tver,
							  &__entry->pkey,
							  &__entry->psn,
							  &__entry->qpn);
			पूर्ण
			/* extended headers */
			अगर (__entry->l4 != OPA_16B_L4_FM)
				स_नकल(__get_dynamic_array(ehdrs),
				       &packet->ohdr->u,
				       __get_dynamic_array_len(ehdrs));
			 ),
		    TP_prपूर्णांकk("[%s] (%s) %s %s hlen:%d %s",
			      __get_str(dev),
			      __entry->etype != RHF_RCV_TYPE_BYPASS ?
					show_packettype(__entry->etype) :
					hfi1_trace_get_packet_l2_str(
						__entry->l2),
			      hfi1_trace_fmt_lrh(p,
						 __entry->etype ==
							RHF_RCV_TYPE_BYPASS,
						 __entry->age,
						 __entry->becn,
						 __entry->fecn,
						 __entry->l4,
						 __entry->lnh,
						 show_lnh(__entry->lnh),
						 __entry->lver,
						 __entry->rc,
						 __entry->sc,
						 __entry->sl,
						 __entry->entropy,
						 __entry->len,
						 __entry->pkey,
						 __entry->dlid,
						 __entry->slid),
			      hfi1_trace_fmt_rest(p,
						  __entry->etype ==
							RHF_RCV_TYPE_BYPASS,
						  __entry->l4,
						  __entry->ack,
						  __entry->becn,
						  __entry->fecn,
						  __entry->mig,
						  __entry->se,
						  __entry->pad,
						  __entry->opcode,
						  show_ib_opcode(__entry->opcode),
						  __entry->tver,
						  __entry->pkey,
						  __entry->psn,
						  __entry->qpn,
						  __entry->dest_qpn,
						  __entry->src_qpn),
			      /* extended headers */
			      __get_dynamic_array_len(ehdrs),
			      __parse_ib_ehdrs(
					__entry->opcode,
					__entry->l4,
					__entry->dest_qpn,
					__entry->src_qpn,
					(व्योम *)__get_dynamic_array(ehdrs))
			     )
);

DEFINE_EVENT(hfi1_input_ibhdr_ढाँचा, input_ibhdr,
	     TP_PROTO(काष्ठा hfi1_devdata *dd,
		      काष्ठा hfi1_packet *packet, bool sc5),
	     TP_ARGS(dd, packet, sc5));

DECLARE_EVENT_CLASS(hfi1_output_ibhdr_ढाँचा,
		    TP_PROTO(काष्ठा hfi1_devdata *dd,
			     काष्ठा hfi1_opa_header *opah, bool sc5),
		    TP_ARGS(dd, opah, sc5),
		    TP_STRUCT__entry(
			DD_DEV_ENTRY(dd)
			__field(u8, hdr_type)
			__field(u8, ack)
			__field(u8, age)
			__field(bool, becn)
			__field(bool, fecn)
			__field(u8, l4)
			__field(u8, lnh)
			__field(u8, lver)
			__field(u8, mig)
			__field(u8, opcode)
			__field(u8, pad)
			__field(u8, rc)
			__field(u8, sc)
			__field(u8, se)
			__field(u8, sl)
			__field(u8, tver)
			__field(u16, entropy)
			__field(u16, len)
			__field(u16, pkey)
			__field(u32, dlid)
			__field(u32, psn)
			__field(u32, qpn)
			__field(u32, slid)
			__field(u32, dest_qpn)
			__field(u32, src_qpn)
			/* extended headers */
			__dynamic_array(u8, ehdrs,
					hfi1_trace_opa_hdr_len(opah))
			),
		    TP_fast_assign(
			काष्ठा ib_other_headers *ohdr;

			DD_DEV_ASSIGN(dd);

			__entry->hdr_type = opah->hdr_type;
			__entry->dest_qpn = 0;
			__entry->src_qpn = 0;
			अगर (__entry->hdr_type)  अणु
				hfi1_trace_parse_16b_hdr(&opah->opah,
							 &__entry->age,
							 &__entry->becn,
							 &__entry->fecn,
							 &__entry->l4,
							 &__entry->rc,
							 &__entry->sc,
							 &__entry->entropy,
							 &__entry->len,
							 &__entry->pkey,
							 &__entry->dlid,
							 &__entry->slid);

				अगर (__entry->l4 == OPA_16B_L4_FM) अणु
					ohdr = शून्य;
					__entry->opcode = IB_OPCODE_UD_SEND_ONLY;
					__entry->dest_qpn = hfi1_16B_get_dest_qpn(&opah->opah.u.mgmt);
					__entry->src_qpn = hfi1_16B_get_src_qpn(&opah->opah.u.mgmt);
				पूर्ण अन्यथा अणु
					अगर (__entry->l4 == OPA_16B_L4_IB_LOCAL)
						ohdr = &opah->opah.u.oth;
					अन्यथा
						ohdr = &opah->opah.u.l.oth;
					hfi1_trace_parse_16b_bth(ohdr,
								 &__entry->ack,
								 &__entry->mig,
								 &__entry->opcode,
								 &__entry->pad,
								 &__entry->se,
								 &__entry->tver,
								 &__entry->psn,
								 &__entry->qpn);
				पूर्ण
			पूर्ण अन्यथा अणु
				__entry->l4 = OPA_16B_L4_9B;
				hfi1_trace_parse_9b_hdr(&opah->ibh, sc5,
							&__entry->lnh,
							&__entry->lver,
							&__entry->sl,
							&__entry->sc,
							&__entry->len,
							&__entry->dlid,
							&__entry->slid);
				अगर (__entry->lnh == HFI1_LRH_BTH)
					ohdr = &opah->ibh.u.oth;
				अन्यथा
					ohdr = &opah->ibh.u.l.oth;
				hfi1_trace_parse_9b_bth(ohdr,
							&__entry->ack,
							&__entry->becn,
							&__entry->fecn,
							&__entry->mig,
							&__entry->se,
							&__entry->pad,
							&__entry->opcode,
							&__entry->tver,
							&__entry->pkey,
							&__entry->psn,
							&__entry->qpn);
			पूर्ण

			/* extended headers */
			अगर (__entry->l4 != OPA_16B_L4_FM)
				स_नकल(__get_dynamic_array(ehdrs),
				       &ohdr->u, __get_dynamic_array_len(ehdrs));
		    ),
		    TP_prपूर्णांकk("[%s] (%s) %s %s hlen:%d %s",
			      __get_str(dev),
			      hfi1_trace_get_packet_l4_str(__entry->l4),
			      hfi1_trace_fmt_lrh(p,
						 !!__entry->hdr_type,
						 __entry->age,
						 __entry->becn,
						 __entry->fecn,
						 __entry->l4,
						 __entry->lnh,
						 show_lnh(__entry->lnh),
						 __entry->lver,
						 __entry->rc,
						 __entry->sc,
						 __entry->sl,
						 __entry->entropy,
						 __entry->len,
						 __entry->pkey,
						 __entry->dlid,
						 __entry->slid),
			      hfi1_trace_fmt_rest(p,
						  !!__entry->hdr_type,
						  __entry->l4,
						  __entry->ack,
						  __entry->becn,
						  __entry->fecn,
						  __entry->mig,
						  __entry->se,
						  __entry->pad,
						  __entry->opcode,
						  show_ib_opcode(__entry->opcode),
						  __entry->tver,
						  __entry->pkey,
						  __entry->psn,
						  __entry->qpn,
						  __entry->dest_qpn,
						  __entry->src_qpn),
			      /* extended headers */
			      __get_dynamic_array_len(ehdrs),
			      __parse_ib_ehdrs(
					__entry->opcode,
					__entry->l4,
					__entry->dest_qpn,
					__entry->src_qpn,
					(व्योम *)__get_dynamic_array(ehdrs))
			     )
);

DEFINE_EVENT(hfi1_output_ibhdr_ढाँचा, pio_output_ibhdr,
	     TP_PROTO(काष्ठा hfi1_devdata *dd,
		      काष्ठा hfi1_opa_header *opah, bool sc5),
	     TP_ARGS(dd, opah, sc5));

DEFINE_EVENT(hfi1_output_ibhdr_ढाँचा, ack_output_ibhdr,
	     TP_PROTO(काष्ठा hfi1_devdata *dd,
		      काष्ठा hfi1_opa_header *opah, bool sc5),
	     TP_ARGS(dd, opah, sc5));

DEFINE_EVENT(hfi1_output_ibhdr_ढाँचा, sdma_output_ibhdr,
	     TP_PROTO(काष्ठा hfi1_devdata *dd,
		      काष्ठा hfi1_opa_header *opah, bool sc5),
	     TP_ARGS(dd, opah, sc5));


#पूर्ण_अगर /* __HFI1_TRACE_IBHDRS_H */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_ibhdrs
#समावेश <trace/define_trace.h>
