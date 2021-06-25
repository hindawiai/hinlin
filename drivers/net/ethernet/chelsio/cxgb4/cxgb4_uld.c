<शैली गुरु>
/*
 * cxgb4_uld.c:Chelsio Upper Layer Driver Interface क्रम T4/T5/T6 SGE management
 *
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
 *
 *  Written by: Atul Gupta (atul.gupta@chelsio.com)
 *  Written by: Hariprasad Shenai (hariprasad@chelsio.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/pci.h>

#समावेश "cxgb4.h"
#समावेश "cxgb4_uld.h"
#समावेश "t4_regs.h"
#समावेश "t4fw_api.h"
#समावेश "t4_msg.h"

#घोषणा क्रम_each_uldrxq(m, i) क्रम (i = 0; i < ((m)->nrxq + (m)->nciq); i++)

/* Flush the aggregated lro sessions */
अटल व्योम uldrx_flush_handler(काष्ठा sge_rspq *q)
अणु
	काष्ठा adapter *adap = q->adap;

	अगर (adap->uld[q->uld].lro_flush)
		adap->uld[q->uld].lro_flush(&q->lro_mgr);
पूर्ण

/**
 *	uldrx_handler - response queue handler क्रम ULD queues
 *	@q: the response queue that received the packet
 *	@rsp: the response queue descriptor holding the offload message
 *	@gl: the gather list of packet fragments
 *
 *	Deliver an ingress offload packet to a ULD.  All processing is करोne by
 *	the ULD, we just मुख्यtain statistics.
 */
अटल पूर्णांक uldrx_handler(काष्ठा sge_rspq *q, स्थिर __be64 *rsp,
			 स्थिर काष्ठा pkt_gl *gl)
अणु
	काष्ठा adapter *adap = q->adap;
	काष्ठा sge_ofld_rxq *rxq = container_of(q, काष्ठा sge_ofld_rxq, rspq);
	पूर्णांक ret;

	/* FW can send CPLs encapsulated in a CPL_FW4_MSG */
	अगर (((स्थिर काष्ठा rss_header *)rsp)->opcode == CPL_FW4_MSG &&
	    ((स्थिर काष्ठा cpl_fw4_msg *)(rsp + 1))->type == FW_TYPE_RSSCPL)
		rsp += 2;

	अगर (q->flush_handler)
		ret = adap->uld[q->uld].lro_rx_handler(adap->uld[q->uld].handle,
				rsp, gl, &q->lro_mgr,
				&q->napi);
	अन्यथा
		ret = adap->uld[q->uld].rx_handler(adap->uld[q->uld].handle,
				rsp, gl);

	अगर (ret) अणु
		rxq->stats.nomem++;
		वापस -1;
	पूर्ण

	अगर (!gl)
		rxq->stats.imm++;
	अन्यथा अगर (gl == CXGB4_MSG_AN)
		rxq->stats.an++;
	अन्यथा
		rxq->stats.pkts++;
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_uld_rxqs(काष्ठा adapter *adap,
			  काष्ठा sge_uld_rxq_info *rxq_info, bool lro)
अणु
	अचिन्हित पूर्णांक nq = rxq_info->nrxq + rxq_info->nciq;
	काष्ठा sge_ofld_rxq *q = rxq_info->uldrxq;
	अचिन्हित लघु *ids = rxq_info->rspq_id;
	पूर्णांक i, err, msi_idx, que_idx = 0;
	काष्ठा sge *s = &adap->sge;
	अचिन्हित पूर्णांक per_chan;

	per_chan = rxq_info->nrxq / adap->params.nports;

	अगर (adap->flags & CXGB4_USING_MSIX)
		msi_idx = 1;
	अन्यथा
		msi_idx = -((पूर्णांक)s->पूर्णांकrq.असल_id + 1);

	क्रम (i = 0; i < nq; i++, q++) अणु
		अगर (i == rxq_info->nrxq) अणु
			/* start allocation of concentrator queues */
			per_chan = rxq_info->nciq / adap->params.nports;
			que_idx = 0;
		पूर्ण

		अगर (msi_idx >= 0) अणु
			msi_idx = cxgb4_get_msix_idx_from_bmap(adap);
			अगर (msi_idx < 0) अणु
				err = -ENOSPC;
				जाओ मुक्तout;
			पूर्ण

			snम_लिखो(adap->msix_info[msi_idx].desc,
				 माप(adap->msix_info[msi_idx].desc),
				 "%s-%s%d",
				 adap->port[0]->name, rxq_info->name, i);

			q->msix = &adap->msix_info[msi_idx];
		पूर्ण
		err = t4_sge_alloc_rxq(adap, &q->rspq, false,
				       adap->port[que_idx++ / per_chan],
				       msi_idx,
				       q->fl.size ? &q->fl : शून्य,
				       uldrx_handler,
				       lro ? uldrx_flush_handler : शून्य,
				       0);
		अगर (err)
			जाओ मुक्तout;

		स_रखो(&q->stats, 0, माप(q->stats));
		अगर (ids)
			ids[i] = q->rspq.असल_id;
	पूर्ण
	वापस 0;
मुक्तout:
	q = rxq_info->uldrxq;
	क्रम ( ; i; i--, q++) अणु
		अगर (q->rspq.desc)
			मुक्त_rspq_fl(adap, &q->rspq,
				     q->fl.size ? &q->fl : शून्य);
		अगर (q->msix)
			cxgb4_मुक्त_msix_idx_in_bmap(adap, q->msix->idx);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
setup_sge_queues_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type, bool lro)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];
	पूर्णांक i, ret;

	ret = alloc_uld_rxqs(adap, rxq_info, lro);
	अगर (ret)
		वापस ret;

	/* Tell uP to route control queue completions to rdma rspq */
	अगर (adap->flags & CXGB4_FULL_INIT_DONE && uld_type == CXGB4_ULD_RDMA) अणु
		काष्ठा sge *s = &adap->sge;
		अचिन्हित पूर्णांक cmplqid;
		u32 param, cmकरोp;

		cmकरोp = FW_PARAMS_PARAM_DMAQ_EQ_CMPLIQID_CTRL;
		क्रम_each_port(adap, i) अणु
			cmplqid = rxq_info->uldrxq[i].rspq.cntxt_id;
			param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
				 FW_PARAMS_PARAM_X_V(cmकरोp) |
				 FW_PARAMS_PARAM_YZ_V(s->ctrlq[i].q.cntxt_id));
			ret = t4_set_params(adap, adap->mbox, adap->pf,
					    0, 1, &param, &cmplqid);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम t4_मुक्त_uld_rxqs(काष्ठा adapter *adap, पूर्णांक n,
			     काष्ठा sge_ofld_rxq *q)
अणु
	क्रम ( ; n; n--, q++) अणु
		अगर (q->rspq.desc)
			मुक्त_rspq_fl(adap, &q->rspq,
				     q->fl.size ? &q->fl : शून्य);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_sge_queues_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];

	अगर (adap->flags & CXGB4_FULL_INIT_DONE && uld_type == CXGB4_ULD_RDMA) अणु
		काष्ठा sge *s = &adap->sge;
		u32 param, cmकरोp, cmplqid = 0;
		पूर्णांक i;

		cmकरोp = FW_PARAMS_PARAM_DMAQ_EQ_CMPLIQID_CTRL;
		क्रम_each_port(adap, i) अणु
			param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
				 FW_PARAMS_PARAM_X_V(cmकरोp) |
				 FW_PARAMS_PARAM_YZ_V(s->ctrlq[i].q.cntxt_id));
			t4_set_params(adap, adap->mbox, adap->pf,
				      0, 1, &param, &cmplqid);
		पूर्ण
	पूर्ण

	अगर (rxq_info->nciq)
		t4_मुक्त_uld_rxqs(adap, rxq_info->nciq,
				 rxq_info->uldrxq + rxq_info->nrxq);
	t4_मुक्त_uld_rxqs(adap, rxq_info->nrxq, rxq_info->uldrxq);
पूर्ण

अटल पूर्णांक cfg_queues_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type,
			  स्थिर काष्ठा cxgb4_uld_info *uld_info)
अणु
	काष्ठा sge *s = &adap->sge;
	काष्ठा sge_uld_rxq_info *rxq_info;
	पूर्णांक i, nrxq, ciq_size;

	rxq_info = kzalloc(माप(*rxq_info), GFP_KERNEL);
	अगर (!rxq_info)
		वापस -ENOMEM;

	अगर (adap->flags & CXGB4_USING_MSIX && uld_info->nrxq > s->nqs_per_uld) अणु
		i = s->nqs_per_uld;
		rxq_info->nrxq = roundup(i, adap->params.nports);
	पूर्ण अन्यथा अणु
		i = min_t(पूर्णांक, uld_info->nrxq,
			  num_online_cpus());
		rxq_info->nrxq = roundup(i, adap->params.nports);
	पूर्ण
	अगर (!uld_info->ciq) अणु
		rxq_info->nciq = 0;
	पूर्ण अन्यथा  अणु
		अगर (adap->flags & CXGB4_USING_MSIX)
			rxq_info->nciq = min_t(पूर्णांक, s->nqs_per_uld,
					       num_online_cpus());
		अन्यथा
			rxq_info->nciq = min_t(पूर्णांक, MAX_OFLD_QSETS,
					       num_online_cpus());
		rxq_info->nciq = ((rxq_info->nciq / adap->params.nports) *
				  adap->params.nports);
		rxq_info->nciq = max_t(पूर्णांक, rxq_info->nciq,
				       adap->params.nports);
	पूर्ण

	nrxq = rxq_info->nrxq + rxq_info->nciq; /* total rxq's */
	rxq_info->uldrxq = kसुस्मृति(nrxq, माप(काष्ठा sge_ofld_rxq),
				   GFP_KERNEL);
	अगर (!rxq_info->uldrxq) अणु
		kमुक्त(rxq_info);
		वापस -ENOMEM;
	पूर्ण

	rxq_info->rspq_id = kसुस्मृति(nrxq, माप(अचिन्हित लघु), GFP_KERNEL);
	अगर (!rxq_info->rspq_id) अणु
		kमुक्त(rxq_info->uldrxq);
		kमुक्त(rxq_info);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < rxq_info->nrxq; i++) अणु
		काष्ठा sge_ofld_rxq *r = &rxq_info->uldrxq[i];

		init_rspq(adap, &r->rspq, 5, 1, uld_info->rxq_size, 64);
		r->rspq.uld = uld_type;
		r->fl.size = 72;
	पूर्ण

	ciq_size = 64 + adap->vres.cq.size + adap->tids.nftids;
	अगर (ciq_size > SGE_MAX_IQ_SIZE) अणु
		dev_warn(adap->pdev_dev, "CIQ size too small for available IQs\n");
		ciq_size = SGE_MAX_IQ_SIZE;
	पूर्ण

	क्रम (i = rxq_info->nrxq; i < nrxq; i++) अणु
		काष्ठा sge_ofld_rxq *r = &rxq_info->uldrxq[i];

		init_rspq(adap, &r->rspq, 5, 1, ciq_size, 64);
		r->rspq.uld = uld_type;
	पूर्ण

	स_नकल(rxq_info->name, uld_info->name, IFNAMSIZ);
	adap->sge.uld_rxq_info[uld_type] = rxq_info;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_queues_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];

	adap->sge.uld_rxq_info[uld_type] = शून्य;
	kमुक्त(rxq_info->rspq_id);
	kमुक्त(rxq_info->uldrxq);
	kमुक्त(rxq_info);
पूर्ण

अटल पूर्णांक
request_msix_queue_irqs_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];
	काष्ठा msix_info *minfo;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err = 0;

	क्रम_each_uldrxq(rxq_info, idx) अणु
		minfo = rxq_info->uldrxq[idx].msix;
		err = request_irq(minfo->vec,
				  t4_sge_पूर्णांकr_msix, 0,
				  minfo->desc,
				  &rxq_info->uldrxq[idx].rspq);
		अगर (err)
			जाओ unwind;

		cxgb4_set_msix_aff(adap, minfo->vec,
				   &minfo->aff_mask, idx);
	पूर्ण
	वापस 0;

unwind:
	जबतक (idx-- > 0) अणु
		minfo = rxq_info->uldrxq[idx].msix;
		cxgb4_clear_msix_aff(minfo->vec, minfo->aff_mask);
		cxgb4_मुक्त_msix_idx_in_bmap(adap, minfo->idx);
		मुक्त_irq(minfo->vec, &rxq_info->uldrxq[idx].rspq);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम
मुक्त_msix_queue_irqs_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];
	काष्ठा msix_info *minfo;
	अचिन्हित पूर्णांक idx;

	क्रम_each_uldrxq(rxq_info, idx) अणु
		minfo = rxq_info->uldrxq[idx].msix;
		cxgb4_clear_msix_aff(minfo->vec, minfo->aff_mask);
		cxgb4_मुक्त_msix_idx_in_bmap(adap, minfo->idx);
		मुक्त_irq(minfo->vec, &rxq_info->uldrxq[idx].rspq);
	पूर्ण
पूर्ण

अटल व्योम enable_rx_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];
	पूर्णांक idx;

	क्रम_each_uldrxq(rxq_info, idx) अणु
		काष्ठा sge_rspq *q = &rxq_info->uldrxq[idx].rspq;

		अगर (!q)
			जारी;

		cxgb4_enable_rx(adap, q);
	पूर्ण
पूर्ण

अटल व्योम quiesce_rx_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];
	पूर्णांक idx;

	क्रम_each_uldrxq(rxq_info, idx) अणु
		काष्ठा sge_rspq *q = &rxq_info->uldrxq[idx].rspq;

		अगर (!q)
			जारी;

		cxgb4_quiesce_rx(q);
	पूर्ण
पूर्ण

अटल व्योम
मुक्त_sge_txq_uld(काष्ठा adapter *adap, काष्ठा sge_uld_txq_info *txq_info)
अणु
	पूर्णांक nq = txq_info->ntxq;
	पूर्णांक i;

	क्रम (i = 0; i < nq; i++) अणु
		काष्ठा sge_uld_txq *txq = &txq_info->uldtxq[i];

		अगर (txq && txq->q.desc) अणु
			tasklet_समाप्त(&txq->qresume_tsk);
			t4_ofld_eq_मुक्त(adap, adap->mbox, adap->pf, 0,
					txq->q.cntxt_id);
			मुक्त_tx_desc(adap, &txq->q, txq->q.in_use, false);
			kमुक्त(txq->q.sdesc);
			__skb_queue_purge(&txq->sendq);
			मुक्त_txq(adap, &txq->q);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
alloc_sge_txq_uld(काष्ठा adapter *adap, काष्ठा sge_uld_txq_info *txq_info,
		  अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge *s = &adap->sge;
	पूर्णांक nq = txq_info->ntxq;
	पूर्णांक i, j, err;

	j = nq / adap->params.nports;
	क्रम (i = 0; i < nq; i++) अणु
		काष्ठा sge_uld_txq *txq = &txq_info->uldtxq[i];

		txq->q.size = 1024;
		err = t4_sge_alloc_uld_txq(adap, txq, adap->port[i / j],
					   s->fw_evtq.cntxt_id, uld_type);
		अगर (err)
			जाओ मुक्तout;
	पूर्ण
	वापस 0;
मुक्तout:
	मुक्त_sge_txq_uld(adap, txq_info);
	वापस err;
पूर्ण

अटल व्योम
release_sge_txq_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type)
अणु
	काष्ठा sge_uld_txq_info *txq_info = शून्य;
	पूर्णांक tx_uld_type = TX_ULD(uld_type);

	txq_info = adap->sge.uld_txq_info[tx_uld_type];

	अगर (txq_info && atomic_dec_and_test(&txq_info->users)) अणु
		मुक्त_sge_txq_uld(adap, txq_info);
		kमुक्त(txq_info->uldtxq);
		kमुक्त(txq_info);
		adap->sge.uld_txq_info[tx_uld_type] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
setup_sge_txq_uld(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type,
		  स्थिर काष्ठा cxgb4_uld_info *uld_info)
अणु
	काष्ठा sge_uld_txq_info *txq_info = शून्य;
	पूर्णांक tx_uld_type, i;

	tx_uld_type = TX_ULD(uld_type);
	txq_info = adap->sge.uld_txq_info[tx_uld_type];

	अगर ((tx_uld_type == CXGB4_TX_OFLD) && txq_info &&
	    (atomic_inc_वापस(&txq_info->users) > 1))
		वापस 0;

	txq_info = kzalloc(माप(*txq_info), GFP_KERNEL);
	अगर (!txq_info)
		वापस -ENOMEM;
	अगर (uld_type == CXGB4_ULD_CRYPTO) अणु
		i = min_t(पूर्णांक, adap->vres.ncrypto_fc,
			  num_online_cpus());
		txq_info->ntxq = roundकरोwn(i, adap->params.nports);
		अगर (txq_info->ntxq <= 0) अणु
			dev_warn(adap->pdev_dev, "Crypto Tx Queues can't be zero\n");
			kमुक्त(txq_info);
			वापस -EINVAL;
		पूर्ण

	पूर्ण अन्यथा अणु
		i = min_t(पूर्णांक, uld_info->ntxq, num_online_cpus());
		txq_info->ntxq = roundup(i, adap->params.nports);
	पूर्ण
	txq_info->uldtxq = kसुस्मृति(txq_info->ntxq, माप(काष्ठा sge_uld_txq),
				   GFP_KERNEL);
	अगर (!txq_info->uldtxq) अणु
		kमुक्त(txq_info);
		वापस -ENOMEM;
	पूर्ण

	अगर (alloc_sge_txq_uld(adap, txq_info, tx_uld_type)) अणु
		kमुक्त(txq_info->uldtxq);
		kमुक्त(txq_info);
		वापस -ENOMEM;
	पूर्ण

	atomic_inc(&txq_info->users);
	adap->sge.uld_txq_info[tx_uld_type] = txq_info;
	वापस 0;
पूर्ण

अटल व्योम uld_queue_init(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld_type,
			   काष्ठा cxgb4_lld_info *lli)
अणु
	काष्ठा sge_uld_rxq_info *rxq_info = adap->sge.uld_rxq_info[uld_type];
	पूर्णांक tx_uld_type = TX_ULD(uld_type);
	काष्ठा sge_uld_txq_info *txq_info = adap->sge.uld_txq_info[tx_uld_type];

	lli->rxq_ids = rxq_info->rspq_id;
	lli->nrxq = rxq_info->nrxq;
	lli->ciq_ids = rxq_info->rspq_id + rxq_info->nrxq;
	lli->nciq = rxq_info->nciq;
	lli->ntxq = txq_info->ntxq;
पूर्ण

पूर्णांक t4_uld_mem_alloc(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;

	adap->uld = kसुस्मृति(CXGB4_ULD_MAX, माप(*adap->uld), GFP_KERNEL);
	अगर (!adap->uld)
		वापस -ENOMEM;

	s->uld_rxq_info = kसुस्मृति(CXGB4_ULD_MAX,
				  माप(काष्ठा sge_uld_rxq_info *),
				  GFP_KERNEL);
	अगर (!s->uld_rxq_info)
		जाओ err_uld;

	s->uld_txq_info = kसुस्मृति(CXGB4_TX_MAX,
				  माप(काष्ठा sge_uld_txq_info *),
				  GFP_KERNEL);
	अगर (!s->uld_txq_info)
		जाओ err_uld_rx;
	वापस 0;

err_uld_rx:
	kमुक्त(s->uld_rxq_info);
err_uld:
	kमुक्त(adap->uld);
	वापस -ENOMEM;
पूर्ण

व्योम t4_uld_mem_मुक्त(काष्ठा adapter *adap)
अणु
	काष्ठा sge *s = &adap->sge;

	kमुक्त(s->uld_txq_info);
	kमुक्त(s->uld_rxq_info);
	kमुक्त(adap->uld);
पूर्ण

/* This function should be called with uld_mutex taken. */
अटल व्योम cxgb4_shutकरोwn_uld_adapter(काष्ठा adapter *adap, क्रमागत cxgb4_uld type)
अणु
	अगर (adap->uld[type].handle) अणु
		adap->uld[type].handle = शून्य;
		adap->uld[type].add = शून्य;
		release_sge_txq_uld(adap, type);

		अगर (adap->flags & CXGB4_FULL_INIT_DONE)
			quiesce_rx_uld(adap, type);

		अगर (adap->flags & CXGB4_USING_MSIX)
			मुक्त_msix_queue_irqs_uld(adap, type);

		मुक्त_sge_queues_uld(adap, type);
		मुक्त_queues_uld(adap, type);
	पूर्ण
पूर्ण

व्योम t4_uld_clean_up(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक i;

	mutex_lock(&uld_mutex);
	क्रम (i = 0; i < CXGB4_ULD_MAX; i++) अणु
		अगर (!adap->uld[i].handle)
			जारी;

		cxgb4_shutकरोwn_uld_adapter(adap, i);
	पूर्ण
	mutex_unlock(&uld_mutex);
पूर्ण

अटल व्योम uld_init(काष्ठा adapter *adap, काष्ठा cxgb4_lld_info *lld)
अणु
	पूर्णांक i;

	lld->pdev = adap->pdev;
	lld->pf = adap->pf;
	lld->l2t = adap->l2t;
	lld->tids = &adap->tids;
	lld->ports = adap->port;
	lld->vr = &adap->vres;
	lld->mtus = adap->params.mtus;
	lld->nchan = adap->params.nports;
	lld->nports = adap->params.nports;
	lld->wr_cred = adap->params.ofldq_wr_cred;
	lld->crypto = adap->params.crypto;
	lld->iscsi_iolen = MAXRXDATA_G(t4_पढ़ो_reg(adap, TP_PARA_REG2_A));
	lld->iscsi_tagmask = t4_पढ़ो_reg(adap, ULP_RX_ISCSI_TAGMASK_A);
	lld->iscsi_pgsz_order = t4_पढ़ो_reg(adap, ULP_RX_ISCSI_PSZ_A);
	lld->iscsi_llimit = t4_पढ़ो_reg(adap, ULP_RX_ISCSI_LLIMIT_A);
	lld->iscsi_ppm = &adap->iscsi_ppm;
	lld->adapter_type = adap->params.chip;
	lld->cclk_ps = 1000000000 / adap->params.vpd.cclk;
	lld->udb_density = 1 << adap->params.sge.eq_qpp;
	lld->ucq_density = 1 << adap->params.sge.iq_qpp;
	lld->sge_host_page_size = 1 << (adap->params.sge.hps + 10);
	lld->filt_mode = adap->params.tp.vlan_pri_map;
	/* MODQ_REQ_MAP sets queues 0-3 to chan 0-3 */
	क्रम (i = 0; i < NCHAN; i++)
		lld->tx_modq[i] = i;
	lld->gts_reg = adap->regs + MYPF_REG(SGE_PF_GTS_A);
	lld->db_reg = adap->regs + MYPF_REG(SGE_PF_KDOORBELL_A);
	lld->fw_vers = adap->params.fw_vers;
	lld->dbfअगरo_पूर्णांक_thresh = dbfअगरo_पूर्णांक_thresh;
	lld->sge_ingpadboundary = adap->sge.fl_align;
	lld->sge_egrstatuspagesize = adap->sge.stat_len;
	lld->sge_pktshअगरt = adap->sge.pktshअगरt;
	lld->ulp_crypto = adap->params.crypto;
	lld->enable_fw_ofld_conn = adap->flags & CXGB4_FW_OFLD_CONN;
	lld->max_ordird_qp = adap->params.max_ordird_qp;
	lld->max_ird_adapter = adap->params.max_ird_adapter;
	lld->ulptx_memग_लिखो_dsgl = adap->params.ulptx_memग_लिखो_dsgl;
	lld->nodeid = dev_to_node(adap->pdev_dev);
	lld->fr_nsmr_tpte_wr_support = adap->params.fr_nsmr_tpte_wr_support;
	lld->ग_लिखो_w_imm_support = adap->params.ग_लिखो_w_imm_support;
	lld->ग_लिखो_cmpl_support = adap->params.ग_लिखो_cmpl_support;
पूर्ण

अटल पूर्णांक uld_attach(काष्ठा adapter *adap, अचिन्हित पूर्णांक uld)
अणु
	काष्ठा cxgb4_lld_info lli;
	व्योम *handle;

	uld_init(adap, &lli);
	uld_queue_init(adap, uld, &lli);

	handle = adap->uld[uld].add(&lli);
	अगर (IS_ERR(handle)) अणु
		dev_warn(adap->pdev_dev,
			 "could not attach to the %s driver, error %ld\n",
			 adap->uld[uld].name, PTR_ERR(handle));
		वापस PTR_ERR(handle);
	पूर्ण

	adap->uld[uld].handle = handle;
	t4_रेजिस्टर_netevent_notअगरier();

	अगर (adap->flags & CXGB4_FULL_INIT_DONE)
		adap->uld[uld].state_change(handle, CXGB4_STATE_UP);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
अटल bool cxgb4_uld_in_use(काष्ठा adapter *adap)
अणु
	स्थिर काष्ठा tid_info *t = &adap->tids;

	वापस (atomic_पढ़ो(&t->conns_in_use) || t->stids_in_use);
पूर्ण

/* cxgb4_set_ktls_feature: request FW to enable/disable ktls settings.
 * @adap: adapter info
 * @enable: 1 to enable / 0 to disable ktls settings.
 */
पूर्णांक cxgb4_set_ktls_feature(काष्ठा adapter *adap, bool enable)
अणु
	पूर्णांक ret = 0;
	u32 params =
		FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_KTLS_HW) |
		FW_PARAMS_PARAM_Y_V(enable) |
		FW_PARAMS_PARAM_Z_V(FW_PARAMS_PARAM_DEV_KTLS_HW_USER_ENABLE);

	अगर (enable) अणु
		अगर (!refcount_पढ़ो(&adap->chcr_ktls.ktls_refcount)) अणु
			/* At this moment अगर ULD connection are up means, other
			 * ULD is/are alपढ़ोy active, वापस failure.
			 */
			अगर (cxgb4_uld_in_use(adap)) अणु
				dev_dbg(adap->pdev_dev,
					"ULD connections (tid/stid) active. Can't enable kTLS\n");
				वापस -EINVAL;
			पूर्ण
			ret = t4_set_params(adap, adap->mbox, adap->pf,
					    0, 1, &params, &params);
			अगर (ret)
				वापस ret;
			refcount_set(&adap->chcr_ktls.ktls_refcount, 1);
			pr_debug("kTLS has been enabled. Restrictions placed on ULD support\n");
		पूर्ण अन्यथा अणु
			/* ktls settings alपढ़ोy up, just increment refcount. */
			refcount_inc(&adap->chcr_ktls.ktls_refcount);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* वापस failure अगर refcount is alपढ़ोy 0. */
		अगर (!refcount_पढ़ो(&adap->chcr_ktls.ktls_refcount))
			वापस -EINVAL;
		/* decrement refcount and test, अगर 0, disable ktls feature,
		 * अन्यथा वापस command success.
		 */
		अगर (refcount_dec_and_test(&adap->chcr_ktls.ktls_refcount)) अणु
			ret = t4_set_params(adap, adap->mbox, adap->pf,
					    0, 1, &params, &params);
			अगर (ret)
				वापस ret;
			pr_debug("kTLS is disabled. Restrictions on ULD support removed\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल व्योम cxgb4_uld_alloc_resources(काष्ठा adapter *adap,
				      क्रमागत cxgb4_uld type,
				      स्थिर काष्ठा cxgb4_uld_info *p)
अणु
	पूर्णांक ret = 0;

	अगर ((type == CXGB4_ULD_CRYPTO && !is_pci_uld(adap)) ||
	    (type != CXGB4_ULD_CRYPTO && !is_offload(adap)))
		वापस;
	अगर (type == CXGB4_ULD_ISCSIT && is_t4(adap->params.chip))
		वापस;
	ret = cfg_queues_uld(adap, type, p);
	अगर (ret)
		जाओ out;
	ret = setup_sge_queues_uld(adap, type, p->lro);
	अगर (ret)
		जाओ मुक्त_queues;
	अगर (adap->flags & CXGB4_USING_MSIX) अणु
		ret = request_msix_queue_irqs_uld(adap, type);
		अगर (ret)
			जाओ मुक्त_rxq;
	पूर्ण
	अगर (adap->flags & CXGB4_FULL_INIT_DONE)
		enable_rx_uld(adap, type);
	अगर (adap->uld[type].add)
		जाओ मुक्त_irq;
	ret = setup_sge_txq_uld(adap, type, p);
	अगर (ret)
		जाओ मुक्त_irq;
	adap->uld[type] = *p;
	ret = uld_attach(adap, type);
	अगर (ret)
		जाओ मुक्त_txq;
	वापस;
मुक्त_txq:
	release_sge_txq_uld(adap, type);
मुक्त_irq:
	अगर (adap->flags & CXGB4_FULL_INIT_DONE)
		quiesce_rx_uld(adap, type);
	अगर (adap->flags & CXGB4_USING_MSIX)
		मुक्त_msix_queue_irqs_uld(adap, type);
मुक्त_rxq:
	मुक्त_sge_queues_uld(adap, type);
मुक्त_queues:
	मुक्त_queues_uld(adap, type);
out:
	dev_warn(adap->pdev_dev,
		 "ULD registration failed for uld type %d\n", type);
पूर्ण

व्योम cxgb4_uld_enable(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_uld_list *uld_entry;

	mutex_lock(&uld_mutex);
	list_add_tail(&adap->list_node, &adapter_list);
	list_क्रम_each_entry(uld_entry, &uld_list, list_node)
		cxgb4_uld_alloc_resources(adap, uld_entry->uld_type,
					  &uld_entry->uld_info);
	mutex_unlock(&uld_mutex);
पूर्ण

/* cxgb4_रेजिस्टर_uld - रेजिस्टर an upper-layer driver
 * @type: the ULD type
 * @p: the ULD methods
 *
 * Registers an upper-layer driver with this driver and notअगरies the ULD
 * about any presently available devices that support its type.
 */
व्योम cxgb4_रेजिस्टर_uld(क्रमागत cxgb4_uld type,
			स्थिर काष्ठा cxgb4_uld_info *p)
अणु
	काष्ठा cxgb4_uld_list *uld_entry;
	काष्ठा adapter *adap;

	अगर (type >= CXGB4_ULD_MAX)
		वापस;

	uld_entry = kzalloc(माप(*uld_entry), GFP_KERNEL);
	अगर (!uld_entry)
		वापस;

	स_नकल(&uld_entry->uld_info, p, माप(काष्ठा cxgb4_uld_info));
	mutex_lock(&uld_mutex);
	list_क्रम_each_entry(adap, &adapter_list, list_node)
		cxgb4_uld_alloc_resources(adap, type, p);

	uld_entry->uld_type = type;
	list_add_tail(&uld_entry->list_node, &uld_list);
	mutex_unlock(&uld_mutex);
	वापस;
पूर्ण
EXPORT_SYMBOL(cxgb4_रेजिस्टर_uld);

/**
 *	cxgb4_unरेजिस्टर_uld - unरेजिस्टर an upper-layer driver
 *	@type: the ULD type
 *
 *	Unरेजिस्टरs an existing upper-layer driver.
 */
पूर्णांक cxgb4_unरेजिस्टर_uld(क्रमागत cxgb4_uld type)
अणु
	काष्ठा cxgb4_uld_list *uld_entry, *पंचांगp;
	काष्ठा adapter *adap;

	अगर (type >= CXGB4_ULD_MAX)
		वापस -EINVAL;

	mutex_lock(&uld_mutex);
	list_क्रम_each_entry(adap, &adapter_list, list_node) अणु
		अगर ((type == CXGB4_ULD_CRYPTO && !is_pci_uld(adap)) ||
		    (type != CXGB4_ULD_CRYPTO && !is_offload(adap)))
			जारी;
		अगर (type == CXGB4_ULD_ISCSIT && is_t4(adap->params.chip))
			जारी;

		cxgb4_shutकरोwn_uld_adapter(adap, type);
	पूर्ण

	list_क्रम_each_entry_safe(uld_entry, पंचांगp, &uld_list, list_node) अणु
		अगर (uld_entry->uld_type == type) अणु
			list_del(&uld_entry->list_node);
			kमुक्त(uld_entry);
		पूर्ण
	पूर्ण
	mutex_unlock(&uld_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cxgb4_unरेजिस्टर_uld);
