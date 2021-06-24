<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2019 Chelsio Communications.  All rights reserved. */

#समावेश "cxgb4.h"
#समावेश "cxgb4_tc_mqprio.h"
#समावेश "sched.h"

अटल पूर्णांक cxgb4_mqprio_validate(काष्ठा net_device *dev,
				 काष्ठा tc_mqprio_qopt_offload *mqprio)
अणु
	u64 min_rate = 0, max_rate = 0, max_link_rate;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	u32 speed, qcount = 0, qoffset = 0;
	u32 start_a, start_b, end_a, end_b;
	पूर्णांक ret;
	u8 i, j;

	अगर (!mqprio->qopt.num_tc)
		वापस 0;

	अगर (mqprio->qopt.hw != TC_MQPRIO_HW_OFFLOAD_TCS) अणु
		netdev_err(dev, "Only full TC hardware offload is supported\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (mqprio->mode != TC_MQPRIO_MODE_CHANNEL) अणु
		netdev_err(dev, "Only channel mode offload is supported\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (mqprio->shaper != TC_MQPRIO_SHAPER_BW_RATE) अणु
		netdev_err(dev,	"Only bandwidth rate shaper supported\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (mqprio->qopt.num_tc > adap->params.nsched_cls) अणु
		netdev_err(dev,
			   "Only %u traffic classes supported by hardware\n",
			   adap->params.nsched_cls);
		वापस -दुस्फल;
	पूर्ण

	ret = t4_get_link_params(pi, शून्य, &speed, शून्य);
	अगर (ret) अणु
		netdev_err(dev, "Failed to get link speed, ret: %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	/* Convert from Mbps to bps */
	max_link_rate = (u64)speed * 1000 * 1000;

	क्रम (i = 0; i < mqprio->qopt.num_tc; i++) अणु
		qoffset = max_t(u16, mqprio->qopt.offset[i], qoffset);
		qcount += mqprio->qopt.count[i];

		start_a = mqprio->qopt.offset[i];
		end_a = start_a + mqprio->qopt.count[i] - 1;
		क्रम (j = i + 1; j < mqprio->qopt.num_tc; j++) अणु
			start_b = mqprio->qopt.offset[j];
			end_b = start_b + mqprio->qopt.count[j] - 1;

			/* If queue count is 0, then the traffic
			 * beदीर्घing to this class will not use
			 * ETHOFLD queues. So, no need to validate
			 * further.
			 */
			अगर (!mqprio->qopt.count[i])
				अवरोध;

			अगर (!mqprio->qopt.count[j])
				जारी;

			अगर (max_t(u32, start_a, start_b) <=
			    min_t(u32, end_a, end_b)) अणु
				netdev_err(dev,
					   "Queues can't overlap across tc\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* Convert byte per second to bits per second */
		min_rate += (mqprio->min_rate[i] * 8);
		max_rate += (mqprio->max_rate[i] * 8);
	पूर्ण

	अगर (qoffset >= adap->tids.neotids || qcount > adap->tids.neotids)
		वापस -ENOMEM;

	अगर (min_rate > max_link_rate || max_rate > max_link_rate) अणु
		netdev_err(dev,
			   "Total Min/Max (%llu/%llu) Rate > supported (%llu)\n",
			   min_rate, max_rate, max_link_rate);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_init_eosw_txq(काष्ठा net_device *dev,
			       काष्ठा sge_eosw_txq *eosw_txq,
			       u32 eotid, u32 hwqid)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा tx_sw_desc *ring;

	स_रखो(eosw_txq, 0, माप(*eosw_txq));

	ring = kसुस्मृति(CXGB4_EOSW_TXQ_DEFAULT_DESC_NUM,
		       माप(*ring), GFP_KERNEL);
	अगर (!ring)
		वापस -ENOMEM;

	eosw_txq->desc = ring;
	eosw_txq->ndesc = CXGB4_EOSW_TXQ_DEFAULT_DESC_NUM;
	spin_lock_init(&eosw_txq->lock);
	eosw_txq->state = CXGB4_EO_STATE_CLOSED;
	eosw_txq->eotid = eotid;
	eosw_txq->hwtid = adap->tids.eotid_base + eosw_txq->eotid;
	eosw_txq->cred = adap->params.ofldq_wr_cred;
	eosw_txq->hwqid = hwqid;
	eosw_txq->netdev = dev;
	tasklet_setup(&eosw_txq->qresume_tsk, cxgb4_ethofld_restart);
	वापस 0;
पूर्ण

अटल व्योम cxgb4_clean_eosw_txq(काष्ठा net_device *dev,
				 काष्ठा sge_eosw_txq *eosw_txq)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	cxgb4_eosw_txq_मुक्त_desc(adap, eosw_txq, eosw_txq->ndesc);
	eosw_txq->pidx = 0;
	eosw_txq->last_pidx = 0;
	eosw_txq->cidx = 0;
	eosw_txq->last_cidx = 0;
	eosw_txq->flowc_idx = 0;
	eosw_txq->inuse = 0;
	eosw_txq->cred = adap->params.ofldq_wr_cred;
	eosw_txq->ncompl = 0;
	eosw_txq->last_compl = 0;
	eosw_txq->state = CXGB4_EO_STATE_CLOSED;
पूर्ण

अटल व्योम cxgb4_मुक्त_eosw_txq(काष्ठा net_device *dev,
				काष्ठा sge_eosw_txq *eosw_txq)
अणु
	spin_lock_bh(&eosw_txq->lock);
	cxgb4_clean_eosw_txq(dev, eosw_txq);
	kमुक्त(eosw_txq->desc);
	spin_unlock_bh(&eosw_txq->lock);
	tasklet_समाप्त(&eosw_txq->qresume_tsk);
पूर्ण

अटल पूर्णांक cxgb4_mqprio_alloc_hw_resources(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge_ofld_rxq *eorxq;
	काष्ठा sge_eohw_txq *eotxq;
	पूर्णांक ret, msix = 0;
	u32 i;

	/* Allocate ETHOFLD hardware queue काष्ठाures अगर not करोne alपढ़ोy */
	अगर (!refcount_पढ़ो(&adap->tc_mqprio->refcnt)) अणु
		adap->sge.eohw_rxq = kसुस्मृति(adap->sge.eoqsets,
					     माप(काष्ठा sge_ofld_rxq),
					     GFP_KERNEL);
		अगर (!adap->sge.eohw_rxq)
			वापस -ENOMEM;

		adap->sge.eohw_txq = kसुस्मृति(adap->sge.eoqsets,
					     माप(काष्ठा sge_eohw_txq),
					     GFP_KERNEL);
		अगर (!adap->sge.eohw_txq) अणु
			kमुक्त(adap->sge.eohw_rxq);
			वापस -ENOMEM;
		पूर्ण

		refcount_set(&adap->tc_mqprio->refcnt, 1);
	पूर्ण अन्यथा अणु
		refcount_inc(&adap->tc_mqprio->refcnt);
	पूर्ण

	अगर (!(adap->flags & CXGB4_USING_MSIX))
		msix = -((पूर्णांक)adap->sge.पूर्णांकrq.असल_id + 1);

	क्रम (i = 0; i < pi->nqsets; i++) अणु
		eorxq = &adap->sge.eohw_rxq[pi->first_qset + i];
		eotxq = &adap->sge.eohw_txq[pi->first_qset + i];

		/* Allocate Rxqs क्रम receiving ETHOFLD Tx completions */
		अगर (msix >= 0) अणु
			msix = cxgb4_get_msix_idx_from_bmap(adap);
			अगर (msix < 0) अणु
				ret = msix;
				जाओ out_मुक्त_queues;
			पूर्ण

			eorxq->msix = &adap->msix_info[msix];
			snम_लिखो(eorxq->msix->desc,
				 माप(eorxq->msix->desc),
				 "%s-eorxq%d", dev->name, i);
		पूर्ण

		init_rspq(adap, &eorxq->rspq,
			  CXGB4_EOHW_RXQ_DEFAULT_INTR_USEC,
			  CXGB4_EOHW_RXQ_DEFAULT_PKT_CNT,
			  CXGB4_EOHW_RXQ_DEFAULT_DESC_NUM,
			  CXGB4_EOHW_RXQ_DEFAULT_DESC_SIZE);

		eorxq->fl.size = CXGB4_EOHW_FLQ_DEFAULT_DESC_NUM;

		ret = t4_sge_alloc_rxq(adap, &eorxq->rspq, false,
				       dev, msix, &eorxq->fl,
				       cxgb4_ethofld_rx_handler,
				       शून्य, 0);
		अगर (ret)
			जाओ out_मुक्त_queues;

		/* Allocate ETHOFLD hardware Txqs */
		eotxq->q.size = CXGB4_EOHW_TXQ_DEFAULT_DESC_NUM;
		ret = t4_sge_alloc_ethofld_txq(adap, eotxq, dev,
					       eorxq->rspq.cntxt_id);
		अगर (ret)
			जाओ out_मुक्त_queues;

		/* Allocate IRQs, set IRQ affinity, and start Rx */
		अगर (adap->flags & CXGB4_USING_MSIX) अणु
			ret = request_irq(eorxq->msix->vec, t4_sge_पूर्णांकr_msix, 0,
					  eorxq->msix->desc, &eorxq->rspq);
			अगर (ret)
				जाओ out_मुक्त_msix;

			cxgb4_set_msix_aff(adap, eorxq->msix->vec,
					   &eorxq->msix->aff_mask, i);
		पूर्ण

		अगर (adap->flags & CXGB4_FULL_INIT_DONE)
			cxgb4_enable_rx(adap, &eorxq->rspq);
	पूर्ण

	वापस 0;

out_मुक्त_msix:
	जबतक (i-- > 0) अणु
		eorxq = &adap->sge.eohw_rxq[pi->first_qset + i];

		अगर (adap->flags & CXGB4_FULL_INIT_DONE)
			cxgb4_quiesce_rx(&eorxq->rspq);

		अगर (adap->flags & CXGB4_USING_MSIX) अणु
			cxgb4_clear_msix_aff(eorxq->msix->vec,
					     eorxq->msix->aff_mask);
			मुक्त_irq(eorxq->msix->vec, &eorxq->rspq);
		पूर्ण
	पूर्ण

out_मुक्त_queues:
	क्रम (i = 0; i < pi->nqsets; i++) अणु
		eorxq = &adap->sge.eohw_rxq[pi->first_qset + i];
		eotxq = &adap->sge.eohw_txq[pi->first_qset + i];

		अगर (eorxq->rspq.desc)
			मुक्त_rspq_fl(adap, &eorxq->rspq, &eorxq->fl);
		अगर (eorxq->msix)
			cxgb4_मुक्त_msix_idx_in_bmap(adap, eorxq->msix->idx);
		t4_sge_मुक्त_ethofld_txq(adap, eotxq);
	पूर्ण

	अगर (refcount_dec_and_test(&adap->tc_mqprio->refcnt)) अणु
		kमुक्त(adap->sge.eohw_txq);
		kमुक्त(adap->sge.eohw_rxq);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cxgb4_mqprio_मुक्त_hw_resources(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge_ofld_rxq *eorxq;
	काष्ठा sge_eohw_txq *eotxq;
	u32 i;

	/* Return अगर no ETHOFLD काष्ठाures have been allocated yet */
	अगर (!refcount_पढ़ो(&adap->tc_mqprio->refcnt))
		वापस;

	/* Return अगर no hardware queues have been allocated */
	अगर (!adap->sge.eohw_rxq[pi->first_qset].rspq.desc)
		वापस;

	क्रम (i = 0; i < pi->nqsets; i++) अणु
		eorxq = &adap->sge.eohw_rxq[pi->first_qset + i];
		eotxq = &adap->sge.eohw_txq[pi->first_qset + i];

		/* Device removal path will alपढ़ोy disable NAPI
		 * beक्रमe unरेजिस्टरing netdevice. So, only disable
		 * NAPI अगर we're not in device removal path
		 */
		अगर (!(adap->flags & CXGB4_SHUTTING_DOWN))
			cxgb4_quiesce_rx(&eorxq->rspq);

		अगर (adap->flags & CXGB4_USING_MSIX) अणु
			cxgb4_clear_msix_aff(eorxq->msix->vec,
					     eorxq->msix->aff_mask);
			मुक्त_irq(eorxq->msix->vec, &eorxq->rspq);
			cxgb4_मुक्त_msix_idx_in_bmap(adap, eorxq->msix->idx);
		पूर्ण

		मुक्त_rspq_fl(adap, &eorxq->rspq, &eorxq->fl);
		t4_sge_मुक्त_ethofld_txq(adap, eotxq);
	पूर्ण

	/* Free up ETHOFLD काष्ठाures अगर there are no users */
	अगर (refcount_dec_and_test(&adap->tc_mqprio->refcnt)) अणु
		kमुक्त(adap->sge.eohw_txq);
		kमुक्त(adap->sge.eohw_rxq);
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb4_mqprio_alloc_tc(काष्ठा net_device *dev,
				 काष्ठा tc_mqprio_qopt_offload *mqprio)
अणु
	काष्ठा ch_sched_params p = अणु
		.type = SCHED_CLASS_TYPE_PACKET,
		.u.params.level = SCHED_CLASS_LEVEL_CL_RL,
		.u.params.mode = SCHED_CLASS_MODE_FLOW,
		.u.params.rateunit = SCHED_CLASS_RATEUNIT_BITS,
		.u.params.ratemode = SCHED_CLASS_RATEMODE_ABS,
		.u.params.class = SCHED_CLS_NONE,
		.u.params.weight = 0,
		.u.params.pktsize = dev->mtu,
	पूर्ण;
	काष्ठा cxgb4_tc_port_mqprio *tc_port_mqprio;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sched_class *e;
	पूर्णांक ret;
	u8 i;

	tc_port_mqprio = &adap->tc_mqprio->port_mqprio[pi->port_id];
	p.u.params.channel = pi->tx_chan;
	क्रम (i = 0; i < mqprio->qopt.num_tc; i++) अणु
		/* Convert from bytes per second to Kbps */
		p.u.params.minrate = भाग_u64(mqprio->min_rate[i] * 8, 1000);
		p.u.params.maxrate = भाग_u64(mqprio->max_rate[i] * 8, 1000);

		/* Request larger burst buffer क्रम smaller MTU, so
		 * that hardware can work on more data per burst
		 * cycle.
		 */
		अगर (dev->mtu <= ETH_DATA_LEN)
			p.u.params.burstsize = 8 * dev->mtu;

		e = cxgb4_sched_class_alloc(dev, &p);
		अगर (!e) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण

		tc_port_mqprio->tc_hwtc_map[i] = e->idx;
	पूर्ण

	वापस 0;

out_err:
	जबतक (i--)
		cxgb4_sched_class_मुक्त(dev, tc_port_mqprio->tc_hwtc_map[i]);

	वापस ret;
पूर्ण

अटल व्योम cxgb4_mqprio_मुक्त_tc(काष्ठा net_device *dev)
अणु
	काष्ठा cxgb4_tc_port_mqprio *tc_port_mqprio;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	u8 i;

	tc_port_mqprio = &adap->tc_mqprio->port_mqprio[pi->port_id];
	क्रम (i = 0; i < tc_port_mqprio->mqprio.qopt.num_tc; i++)
		cxgb4_sched_class_मुक्त(dev, tc_port_mqprio->tc_hwtc_map[i]);
पूर्ण

अटल पूर्णांक cxgb4_mqprio_class_bind(काष्ठा net_device *dev,
				   काष्ठा sge_eosw_txq *eosw_txq,
				   u8 tc)
अणु
	काष्ठा ch_sched_flowc fe;
	पूर्णांक ret;

	init_completion(&eosw_txq->completion);

	fe.tid = eosw_txq->eotid;
	fe.class = tc;

	ret = cxgb4_sched_class_bind(dev, &fe, SCHED_FLOWC);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&eosw_txq->completion,
					  CXGB4_FLOWC_WAIT_TIMEOUT);
	अगर (!ret)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम cxgb4_mqprio_class_unbind(काष्ठा net_device *dev,
				      काष्ठा sge_eosw_txq *eosw_txq,
				      u8 tc)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा ch_sched_flowc fe;

	/* If we're shutting करोwn, पूर्णांकerrupts are disabled and no completions
	 * come back. So, skip रुकोing क्रम completions in this scenario.
	 */
	अगर (!(adap->flags & CXGB4_SHUTTING_DOWN))
		init_completion(&eosw_txq->completion);

	fe.tid = eosw_txq->eotid;
	fe.class = tc;
	cxgb4_sched_class_unbind(dev, &fe, SCHED_FLOWC);

	अगर (!(adap->flags & CXGB4_SHUTTING_DOWN))
		रुको_क्रम_completion_समयout(&eosw_txq->completion,
					    CXGB4_FLOWC_WAIT_TIMEOUT);
पूर्ण

अटल पूर्णांक cxgb4_mqprio_enable_offload(काष्ठा net_device *dev,
				       काष्ठा tc_mqprio_qopt_offload *mqprio)
अणु
	काष्ठा cxgb4_tc_port_mqprio *tc_port_mqprio;
	u32 qoffset, qcount, tot_qcount, qid, hwqid;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge_eosw_txq *eosw_txq;
	पूर्णांक eotid, ret;
	u16 i, j;
	u8 hwtc;

	ret = cxgb4_mqprio_alloc_hw_resources(dev);
	अगर (ret)
		वापस -ENOMEM;

	tc_port_mqprio = &adap->tc_mqprio->port_mqprio[pi->port_id];
	क्रम (i = 0; i < mqprio->qopt.num_tc; i++) अणु
		qoffset = mqprio->qopt.offset[i];
		qcount = mqprio->qopt.count[i];
		क्रम (j = 0; j < qcount; j++) अणु
			eotid = cxgb4_get_मुक्त_eotid(&adap->tids);
			अगर (eotid < 0) अणु
				ret = -ENOMEM;
				जाओ out_मुक्त_eotids;
			पूर्ण

			qid = qoffset + j;
			hwqid = pi->first_qset + (eotid % pi->nqsets);
			eosw_txq = &tc_port_mqprio->eosw_txq[qid];
			ret = cxgb4_init_eosw_txq(dev, eosw_txq,
						  eotid, hwqid);
			अगर (ret)
				जाओ out_मुक्त_eotids;

			cxgb4_alloc_eotid(&adap->tids, eotid, eosw_txq);

			hwtc = tc_port_mqprio->tc_hwtc_map[i];
			ret = cxgb4_mqprio_class_bind(dev, eosw_txq, hwtc);
			अगर (ret)
				जाओ out_मुक्त_eotids;
		पूर्ण
	पूर्ण

	स_नकल(&tc_port_mqprio->mqprio, mqprio,
	       माप(काष्ठा tc_mqprio_qopt_offload));

	/* Inक्रमm the stack about the configured tc params.
	 *
	 * Set the correct queue map. If no queue count has been
	 * specअगरied, then send the traffic through शेष NIC
	 * queues; instead of ETHOFLD queues.
	 */
	ret = netdev_set_num_tc(dev, mqprio->qopt.num_tc);
	अगर (ret)
		जाओ out_मुक्त_eotids;

	tot_qcount = pi->nqsets;
	क्रम (i = 0; i < mqprio->qopt.num_tc; i++) अणु
		qcount = mqprio->qopt.count[i];
		अगर (qcount) अणु
			qoffset = mqprio->qopt.offset[i] + pi->nqsets;
		पूर्ण अन्यथा अणु
			qcount = pi->nqsets;
			qoffset = 0;
		पूर्ण

		ret = netdev_set_tc_queue(dev, i, qcount, qoffset);
		अगर (ret)
			जाओ out_reset_tc;

		tot_qcount += mqprio->qopt.count[i];
	पूर्ण

	ret = netअगर_set_real_num_tx_queues(dev, tot_qcount);
	अगर (ret)
		जाओ out_reset_tc;

	tc_port_mqprio->state = CXGB4_MQPRIO_STATE_ACTIVE;
	वापस 0;

out_reset_tc:
	netdev_reset_tc(dev);
	i = mqprio->qopt.num_tc;

out_मुक्त_eotids:
	जबतक (i-- > 0) अणु
		qoffset = mqprio->qopt.offset[i];
		qcount = mqprio->qopt.count[i];
		क्रम (j = 0; j < qcount; j++) अणु
			eosw_txq = &tc_port_mqprio->eosw_txq[qoffset + j];

			hwtc = tc_port_mqprio->tc_hwtc_map[i];
			cxgb4_mqprio_class_unbind(dev, eosw_txq, hwtc);

			cxgb4_मुक्त_eotid(&adap->tids, eosw_txq->eotid);
			cxgb4_मुक्त_eosw_txq(dev, eosw_txq);
		पूर्ण
	पूर्ण

	cxgb4_mqprio_मुक्त_hw_resources(dev);
	वापस ret;
पूर्ण

अटल व्योम cxgb4_mqprio_disable_offload(काष्ठा net_device *dev)
अणु
	काष्ठा cxgb4_tc_port_mqprio *tc_port_mqprio;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge_eosw_txq *eosw_txq;
	u32 qoffset, qcount;
	u16 i, j;
	u8 hwtc;

	tc_port_mqprio = &adap->tc_mqprio->port_mqprio[pi->port_id];
	अगर (tc_port_mqprio->state != CXGB4_MQPRIO_STATE_ACTIVE)
		वापस;

	netdev_reset_tc(dev);
	netअगर_set_real_num_tx_queues(dev, pi->nqsets);

	क्रम (i = 0; i < tc_port_mqprio->mqprio.qopt.num_tc; i++) अणु
		qoffset = tc_port_mqprio->mqprio.qopt.offset[i];
		qcount = tc_port_mqprio->mqprio.qopt.count[i];
		क्रम (j = 0; j < qcount; j++) अणु
			eosw_txq = &tc_port_mqprio->eosw_txq[qoffset + j];

			hwtc = tc_port_mqprio->tc_hwtc_map[i];
			cxgb4_mqprio_class_unbind(dev, eosw_txq, hwtc);

			cxgb4_मुक्त_eotid(&adap->tids, eosw_txq->eotid);
			cxgb4_मुक्त_eosw_txq(dev, eosw_txq);
		पूर्ण
	पूर्ण

	cxgb4_mqprio_मुक्त_hw_resources(dev);

	/* Free up the traffic classes */
	cxgb4_mqprio_मुक्त_tc(dev);

	स_रखो(&tc_port_mqprio->mqprio, 0,
	       माप(काष्ठा tc_mqprio_qopt_offload));

	tc_port_mqprio->state = CXGB4_MQPRIO_STATE_DISABLED;
पूर्ण

पूर्णांक cxgb4_setup_tc_mqprio(काष्ठा net_device *dev,
			  काष्ठा tc_mqprio_qopt_offload *mqprio)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	bool needs_bring_up = false;
	पूर्णांक ret;

	ret = cxgb4_mqprio_validate(dev, mqprio);
	अगर (ret)
		वापस ret;

	mutex_lock(&adap->tc_mqprio->mqprio_mutex);

	/* To configure tc params, the current allocated EOTIDs must
	 * be मुक्तd up. However, they can't be freed up if there's
	 * traffic running on the पूर्णांकerface. So, ensure पूर्णांकerface is
	 * करोwn beक्रमe configuring tc params.
	 */
	अगर (netअगर_running(dev)) अणु
		netअगर_tx_stop_all_queues(dev);
		netअगर_carrier_off(dev);
		needs_bring_up = true;
	पूर्ण

	cxgb4_mqprio_disable_offload(dev);

	/* If requested क्रम clear, then just वापस since resources are
	 * alपढ़ोy मुक्तd up by now.
	 */
	अगर (!mqprio->qopt.num_tc)
		जाओ out;

	/* Allocate मुक्त available traffic classes and configure
	 * their rate parameters.
	 */
	ret = cxgb4_mqprio_alloc_tc(dev, mqprio);
	अगर (ret)
		जाओ out;

	ret = cxgb4_mqprio_enable_offload(dev, mqprio);
	अगर (ret) अणु
		cxgb4_mqprio_मुक्त_tc(dev);
		जाओ out;
	पूर्ण

out:
	अगर (needs_bring_up) अणु
		netअगर_tx_start_all_queues(dev);
		netअगर_carrier_on(dev);
	पूर्ण

	mutex_unlock(&adap->tc_mqprio->mqprio_mutex);
	वापस ret;
पूर्ण

व्योम cxgb4_mqprio_stop_offload(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_tc_port_mqprio *tc_port_mqprio;
	काष्ठा net_device *dev;
	u8 i;

	अगर (!adap->tc_mqprio || !adap->tc_mqprio->port_mqprio)
		वापस;

	mutex_lock(&adap->tc_mqprio->mqprio_mutex);
	क्रम_each_port(adap, i) अणु
		dev = adap->port[i];
		अगर (!dev)
			जारी;

		tc_port_mqprio = &adap->tc_mqprio->port_mqprio[i];
		अगर (!tc_port_mqprio->mqprio.qopt.num_tc)
			जारी;

		cxgb4_mqprio_disable_offload(dev);
	पूर्ण
	mutex_unlock(&adap->tc_mqprio->mqprio_mutex);
पूर्ण

पूर्णांक cxgb4_init_tc_mqprio(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_tc_port_mqprio *tc_port_mqprio, *port_mqprio;
	काष्ठा cxgb4_tc_mqprio *tc_mqprio;
	काष्ठा sge_eosw_txq *eosw_txq;
	पूर्णांक ret = 0;
	u8 i;

	tc_mqprio = kzalloc(माप(*tc_mqprio), GFP_KERNEL);
	अगर (!tc_mqprio)
		वापस -ENOMEM;

	tc_port_mqprio = kसुस्मृति(adap->params.nports, माप(*tc_port_mqprio),
				 GFP_KERNEL);
	अगर (!tc_port_mqprio) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_mqprio;
	पूर्ण

	mutex_init(&tc_mqprio->mqprio_mutex);

	tc_mqprio->port_mqprio = tc_port_mqprio;
	क्रम (i = 0; i < adap->params.nports; i++) अणु
		port_mqprio = &tc_mqprio->port_mqprio[i];
		eosw_txq = kसुस्मृति(adap->tids.neotids, माप(*eosw_txq),
				   GFP_KERNEL);
		अगर (!eosw_txq) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_ports;
		पूर्ण
		port_mqprio->eosw_txq = eosw_txq;
	पूर्ण

	adap->tc_mqprio = tc_mqprio;
	refcount_set(&adap->tc_mqprio->refcnt, 0);
	वापस 0;

out_मुक्त_ports:
	क्रम (i = 0; i < adap->params.nports; i++) अणु
		port_mqprio = &tc_mqprio->port_mqprio[i];
		kमुक्त(port_mqprio->eosw_txq);
	पूर्ण
	kमुक्त(tc_port_mqprio);

out_मुक्त_mqprio:
	kमुक्त(tc_mqprio);
	वापस ret;
पूर्ण

व्योम cxgb4_cleanup_tc_mqprio(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_tc_port_mqprio *port_mqprio;
	u8 i;

	अगर (adap->tc_mqprio) अणु
		mutex_lock(&adap->tc_mqprio->mqprio_mutex);
		अगर (adap->tc_mqprio->port_mqprio) अणु
			क्रम (i = 0; i < adap->params.nports; i++) अणु
				काष्ठा net_device *dev = adap->port[i];

				अगर (dev)
					cxgb4_mqprio_disable_offload(dev);
				port_mqprio = &adap->tc_mqprio->port_mqprio[i];
				kमुक्त(port_mqprio->eosw_txq);
			पूर्ण
			kमुक्त(adap->tc_mqprio->port_mqprio);
		पूर्ण
		mutex_unlock(&adap->tc_mqprio->mqprio_mutex);
		kमुक्त(adap->tc_mqprio);
	पूर्ण
पूर्ण
