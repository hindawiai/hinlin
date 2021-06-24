<शैली गुरु>
/*
 * This file is part of the Chelsio T4/T5/T6 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2017 Chelsio Communications, Inc. All rights reserved.
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
#समावेश "smt.h"
#समावेश "t4_msg.h"
#समावेश "t4fw_api.h"
#समावेश "t4_regs.h"
#समावेश "t4_values.h"

काष्ठा smt_data *t4_init_smt(व्योम)
अणु
	अचिन्हित पूर्णांक smt_size;
	काष्ठा smt_data *s;
	पूर्णांक i;

	smt_size = SMT_SIZE;

	s = kvzalloc(काष्ठा_size(s, smtab, smt_size), GFP_KERNEL);
	अगर (!s)
		वापस शून्य;
	s->smt_size = smt_size;
	rwlock_init(&s->lock);
	क्रम (i = 0; i < s->smt_size; ++i) अणु
		s->smtab[i].idx = i;
		s->smtab[i].state = SMT_STATE_UNUSED;
		eth_zero_addr(s->smtab[i].src_mac);
		spin_lock_init(&s->smtab[i].lock);
		s->smtab[i].refcnt = 0;
	पूर्ण
	वापस s;
पूर्ण

अटल काष्ठा smt_entry *find_or_alloc_smte(काष्ठा smt_data *s, u8 *smac)
अणु
	काष्ठा smt_entry *first_मुक्त = शून्य;
	काष्ठा smt_entry *e, *end;

	क्रम (e = &s->smtab[0], end = &s->smtab[s->smt_size]; e != end; ++e) अणु
		अगर (e->refcnt == 0) अणु
			अगर (!first_मुक्त)
				first_मुक्त = e;
		पूर्ण अन्यथा अणु
			अगर (e->state == SMT_STATE_SWITCHING) अणु
				/* This entry is actually in use. See अगर we can
				 * re-use it ?
				 */
				अगर (स_भेद(e->src_mac, smac, ETH_ALEN) == 0)
					जाओ found_reuse;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (first_मुक्त) अणु
		e = first_मुक्त;
		जाओ found;
	पूर्ण
	वापस शून्य;

found:
	e->state = SMT_STATE_UNUSED;

found_reuse:
	वापस e;
पूर्ण

अटल व्योम t4_smte_मुक्त(काष्ठा smt_entry *e)
अणु
	अगर (e->refcnt == 0) अणु  /* hasn't been recycled */
		e->state = SMT_STATE_UNUSED;
	पूर्ण
पूर्ण

/**
 * cxgb4_smt_release - Release SMT entry
 * @e: smt entry to release
 *
 * Releases ref count and मुक्तs up an smt entry from SMT table
 */
व्योम cxgb4_smt_release(काष्ठा smt_entry *e)
अणु
	spin_lock_bh(&e->lock);
	अगर ((--e->refcnt) == 0)
		t4_smte_मुक्त(e);
	spin_unlock_bh(&e->lock);
पूर्ण
EXPORT_SYMBOL(cxgb4_smt_release);

व्योम करो_smt_ग_लिखो_rpl(काष्ठा adapter *adap, स्थिर काष्ठा cpl_smt_ग_लिखो_rpl *rpl)
अणु
	अचिन्हित पूर्णांक smtidx = TID_TID_G(GET_TID(rpl));
	काष्ठा smt_data *s = adap->smt;

	अगर (unlikely(rpl->status != CPL_ERR_NONE)) अणु
		काष्ठा smt_entry *e = &s->smtab[smtidx];

		dev_err(adap->pdev_dev,
			"Unexpected SMT_WRITE_RPL status %u for entry %u\n",
			rpl->status, smtidx);
		spin_lock(&e->lock);
		e->state = SMT_STATE_ERROR;
		spin_unlock(&e->lock);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ग_लिखो_smt_entry(काष्ठा adapter *adapter, काष्ठा smt_entry *e)
अणु
	काष्ठा cpl_t6_smt_ग_लिखो_req *t6req;
	काष्ठा smt_data *s = adapter->smt;
	काष्ठा cpl_smt_ग_लिखो_req *req;
	काष्ठा sk_buff *skb;
	पूर्णांक size;
	u8 row;

	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5) अणु
		size = माप(*req);
		skb = alloc_skb(size, GFP_ATOMIC);
		अगर (!skb)
			वापस -ENOMEM;
		/* Source MAC Table (SMT) contains 256 SMAC entries
		 * organized in 128 rows of 2 entries each.
		 */
		req = (काष्ठा cpl_smt_ग_लिखो_req *)__skb_put(skb, size);
		INIT_TP_WR(req, 0);

		/* Each row contains an SMAC pair.
		 * LSB selects the SMAC entry within a row
		 */
		row = (e->idx >> 1);
		अगर (e->idx & 1) अणु
			req->pfvf1 = 0x0;
			स_नकल(req->src_mac1, e->src_mac, ETH_ALEN);

			/* fill pfvf0/src_mac0 with entry
			 * at prev index from smt-tab.
			 */
			req->pfvf0 = 0x0;
			स_नकल(req->src_mac0, s->smtab[e->idx - 1].src_mac,
			       ETH_ALEN);
		पूर्ण अन्यथा अणु
			req->pfvf0 = 0x0;
			स_नकल(req->src_mac0, e->src_mac, ETH_ALEN);

			/* fill pfvf1/src_mac1 with entry
			 * at next index from smt-tab
			 */
			req->pfvf1 = 0x0;
			स_नकल(req->src_mac1, s->smtab[e->idx + 1].src_mac,
			       ETH_ALEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		size = माप(*t6req);
		skb = alloc_skb(size, GFP_ATOMIC);
		अगर (!skb)
			वापस -ENOMEM;
		/* Source MAC Table (SMT) contains 256 SMAC entries */
		t6req = (काष्ठा cpl_t6_smt_ग_लिखो_req *)__skb_put(skb, size);
		INIT_TP_WR(t6req, 0);
		req = (काष्ठा cpl_smt_ग_लिखो_req *)t6req;

		/* fill pfvf0/src_mac0 from smt-tab */
		req->pfvf0 = 0x0;
		स_नकल(req->src_mac0, s->smtab[e->idx].src_mac, ETH_ALEN);
		row = e->idx;
	पूर्ण

	OPCODE_TID(req) =
		htonl(MK_OPCODE_TID(CPL_SMT_WRITE_REQ, e->idx |
				    TID_QID_V(adapter->sge.fw_evtq.असल_id)));
	req->params = htonl(SMTW_NORPL_V(0) |
			    SMTW_IDX_V(row) |
			    SMTW_OVLAN_IDX_V(0));
	t4_mgmt_tx(adapter, skb);
	वापस 0;
पूर्ण

अटल काष्ठा smt_entry *t4_smt_alloc_चयनing(काष्ठा adapter *adap, u16 pfvf,
						u8 *smac)
अणु
	काष्ठा smt_data *s = adap->smt;
	काष्ठा smt_entry *e;

	ग_लिखो_lock_bh(&s->lock);
	e = find_or_alloc_smte(s, smac);
	अगर (e) अणु
		spin_lock(&e->lock);
		अगर (!e->refcnt) अणु
			e->refcnt = 1;
			e->state = SMT_STATE_SWITCHING;
			e->pfvf = pfvf;
			स_नकल(e->src_mac, smac, ETH_ALEN);
			ग_लिखो_smt_entry(adap, e);
		पूर्ण अन्यथा अणु
			++e->refcnt;
		पूर्ण
		spin_unlock(&e->lock);
	पूर्ण
	ग_लिखो_unlock_bh(&s->lock);
	वापस e;
पूर्ण

/**
 * cxgb4_smt_alloc_चयनing - Allocates an SMT entry क्रम चयन filters.
 * @dev: net_device poपूर्णांकer
 * @smac: MAC address to add to SMT
 * Returns poपूर्णांकer to the SMT entry created
 *
 * Allocates an SMT entry to be used by चयनing rule of a filter.
 */
काष्ठा smt_entry *cxgb4_smt_alloc_चयनing(काष्ठा net_device *dev, u8 *smac)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	वापस t4_smt_alloc_चयनing(adap, 0x0, smac);
पूर्ण
EXPORT_SYMBOL(cxgb4_smt_alloc_चयनing);
