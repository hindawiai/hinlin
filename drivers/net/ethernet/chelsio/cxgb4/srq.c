<शैली गुरु>
/*
 * This file is part of the Chelsio T6 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2017-2018 Chelsio Communications, Inc. All rights reserved.
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
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#समावेश "cxgb4.h"
#समावेश "t4_msg.h"
#समावेश "srq.h"

काष्ठा srq_data *t4_init_srq(पूर्णांक srq_size)
अणु
	काष्ठा srq_data *s;

	s = kvzalloc(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस शून्य;

	s->srq_size = srq_size;
	init_completion(&s->comp);
	mutex_init(&s->lock);

	वापस s;
पूर्ण

/* cxgb4_get_srq_entry: पढ़ो the SRQ table entry
 * @dev: Poपूर्णांकer to the net_device
 * @idx: Index to the srq
 * @entryp: poपूर्णांकer to the srq entry
 *
 * Sends CPL_SRQ_TABLE_REQ message क्रम the given index.
 * Contents will be वापसed in CPL_SRQ_TABLE_RPL message.
 *
 * Returns zero अगर the पढ़ो is successful, अन्यथा a error
 * number will be वापसed. Caller should not use the srq
 * entry अगर the वापस value is non-zero.
 *
 *
 */
पूर्णांक cxgb4_get_srq_entry(काष्ठा net_device *dev,
			पूर्णांक srq_idx, काष्ठा srq_entry *entryp)
अणु
	काष्ठा cpl_srq_table_req *req;
	काष्ठा adapter *adap;
	काष्ठा sk_buff *skb;
	काष्ठा srq_data *s;
	पूर्णांक rc = -ENODEV;

	adap = netdev2adap(dev);
	s = adap->srq;

	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE) || !s)
		जाओ out;

	skb = alloc_skb(माप(*req), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;
	req = (काष्ठा cpl_srq_table_req *)
		__skb_put_zero(skb, माप(*req));
	INIT_TP_WR(req, 0);
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SRQ_TABLE_REQ,
					      TID_TID_V(srq_idx) |
				TID_QID_V(adap->sge.fw_evtq.असल_id)));
	req->idx = srq_idx;

	mutex_lock(&s->lock);

	s->entryp = entryp;
	t4_mgmt_tx(adap, skb);

	rc = रुको_क्रम_completion_समयout(&s->comp, SRQ_WAIT_TO);
	अगर (rc)
		rc = 0;
	अन्यथा /* !rc means we समयd out */
		rc = -ETIMEDOUT;

	WARN_ON_ONCE(entryp->idx != srq_idx);
	mutex_unlock(&s->lock);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(cxgb4_get_srq_entry);

व्योम करो_srq_table_rpl(काष्ठा adapter *adap,
		      स्थिर काष्ठा cpl_srq_table_rpl *rpl)
अणु
	अचिन्हित पूर्णांक idx = TID_TID_G(GET_TID(rpl));
	काष्ठा srq_data *s = adap->srq;
	काष्ठा srq_entry *e;

	अगर (unlikely(rpl->status != CPL_CONTAINS_READ_RPL)) अणु
		dev_err(adap->pdev_dev,
			"Unexpected SRQ_TABLE_RPL status %u for entry %u\n",
				rpl->status, idx);
		जाओ out;
	पूर्ण

	/* Store the पढ़ो entry */
	e = s->entryp;
	e->valid = 1;
	e->idx = idx;
	e->pdid = SRQT_PDID_G(be64_to_cpu(rpl->rsvd_pdid));
	e->qlen = SRQT_QLEN_G(be32_to_cpu(rpl->qlen_qbase));
	e->qbase = SRQT_QBASE_G(be32_to_cpu(rpl->qlen_qbase));
	e->cur_msn = be16_to_cpu(rpl->cur_msn);
	e->max_msn = be16_to_cpu(rpl->max_msn);
out:
	complete(&s->comp);
पूर्ण
