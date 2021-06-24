<शैली गुरु>
/*
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __LIBCXGB_CM_H__
#घोषणा __LIBCXGB_CM_H__


#समावेश <net/tcp.h>

#समावेश <cxgb4.h>
#समावेश <t4_msg.h>
#समावेश <l2t.h>

व्योम
cxgb_get_4tuple(काष्ठा cpl_pass_accept_req *, क्रमागत chip_type,
		पूर्णांक *, __u8 *, __u8 *, __be16 *, __be16 *);
काष्ठा dst_entry *
cxgb_find_route(काष्ठा cxgb4_lld_info *,
		काष्ठा net_device *(*)(काष्ठा net_device *),
		__be32, __be32, __be16,	__be16, u8);
काष्ठा dst_entry *
cxgb_find_route6(काष्ठा cxgb4_lld_info *,
		 काष्ठा net_device *(*)(काष्ठा net_device *),
		 __u8 *, __u8 *, __be16, __be16, u8, __u32);

/* Returns whether a CPL status conveys negative advice.
 */
अटल अंतरभूत bool cxgb_is_neg_adv(अचिन्हित पूर्णांक status)
अणु
	वापस status == CPL_ERR_RTX_NEG_ADVICE ||
	       status == CPL_ERR_PERSIST_NEG_ADVICE ||
	       status == CPL_ERR_KEEPALV_NEG_ADVICE;
पूर्ण

अटल अंतरभूत व्योम
cxgb_best_mtu(स्थिर अचिन्हित लघु *mtus, अचिन्हित लघु mtu,
	      अचिन्हित पूर्णांक *idx, पूर्णांक use_ts, पूर्णांक ipv6)
अणु
	अचिन्हित लघु hdr_size = (ipv6 ?
				   माप(काष्ठा ipv6hdr) :
				   माप(काष्ठा iphdr)) +
				  माप(काष्ठा tcphdr) +
				  (use_ts ?
				   round_up(TCPOLEN_TIMESTAMP, 4) : 0);
	अचिन्हित लघु data_size = mtu - hdr_size;

	cxgb4_best_aligned_mtu(mtus, hdr_size, data_size, 8, idx);
पूर्ण

अटल अंतरभूत u32 cxgb_compute_wscale(u32 win)
अणु
	u32 wscale = 0;

	जबतक (wscale < 14 && (65535 << wscale) < win)
		wscale++;
	वापस wscale;
पूर्ण

अटल अंतरभूत व्योम
cxgb_mk_tid_release(काष्ठा sk_buff *skb, u32 len, u32 tid, u16 chan)
अणु
	काष्ठा cpl_tid_release *req;

	req = __skb_put_zero(skb, len);

	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_TID_RELEASE, tid));
	set_wr_txq(skb, CPL_PRIORITY_SETUP, chan);
पूर्ण

अटल अंतरभूत व्योम
cxgb_mk_बंद_con_req(काष्ठा sk_buff *skb, u32 len, u32 tid, u16 chan,
		      व्योम *handle, arp_err_handler_t handler)
अणु
	काष्ठा cpl_बंद_con_req *req;

	req = __skb_put_zero(skb, len);

	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_CLOSE_CON_REQ, tid));
	set_wr_txq(skb, CPL_PRIORITY_DATA, chan);
	t4_set_arp_err_handler(skb, handle, handler);
पूर्ण

अटल अंतरभूत व्योम
cxgb_mk_पात_req(काष्ठा sk_buff *skb, u32 len, u32 tid, u16 chan,
		  व्योम *handle, arp_err_handler_t handler)
अणु
	काष्ठा cpl_पात_req *req;

	req = __skb_put_zero(skb, len);

	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ABORT_REQ, tid));
	req->cmd = CPL_ABORT_SEND_RST;
	set_wr_txq(skb, CPL_PRIORITY_DATA, chan);
	t4_set_arp_err_handler(skb, handle, handler);
पूर्ण

अटल अंतरभूत व्योम
cxgb_mk_पात_rpl(काष्ठा sk_buff *skb, u32 len, u32 tid, u16 chan)
अणु
	काष्ठा cpl_पात_rpl *rpl;

	rpl = __skb_put_zero(skb, len);

	INIT_TP_WR(rpl, tid);
	OPCODE_TID(rpl) = cpu_to_be32(MK_OPCODE_TID(CPL_ABORT_RPL, tid));
	rpl->cmd = CPL_ABORT_NO_RST;
	set_wr_txq(skb, CPL_PRIORITY_DATA, chan);
पूर्ण

अटल अंतरभूत व्योम
cxgb_mk_rx_data_ack(काष्ठा sk_buff *skb, u32 len, u32 tid, u16 chan,
		    u32 credit_dack)
अणु
	काष्ठा cpl_rx_data_ack *req;

	req = __skb_put_zero(skb, len);

	INIT_TP_WR(req, tid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_RX_DATA_ACK, tid));
	req->credit_dack = cpu_to_be32(credit_dack);
	set_wr_txq(skb, CPL_PRIORITY_ACK, chan);
पूर्ण
#पूर्ण_अगर
