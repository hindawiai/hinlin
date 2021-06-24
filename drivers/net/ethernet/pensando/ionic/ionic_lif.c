<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/ethtool.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/cpumask.h>

#समावेश "ionic.h"
#समावेश "ionic_bus.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_txrx.h"
#समावेश "ionic_ethtool.h"
#समावेश "ionic_debugfs.h"

/* queuetype support level */
अटल स्थिर u8 ionic_qtype_versions[IONIC_QTYPE_MAX] = अणु
	[IONIC_QTYPE_ADMINQ]  = 0,   /* 0 = Base version with CQ support */
	[IONIC_QTYPE_NOTIFYQ] = 0,   /* 0 = Base version */
	[IONIC_QTYPE_RXQ]     = 0,   /* 0 = Base version with CQ+SG support */
	[IONIC_QTYPE_TXQ]     = 1,   /* 0 = Base version with CQ+SG support
				      * 1 =   ... with Tx SG version 1
				      */
पूर्ण;

अटल व्योम ionic_lअगर_rx_mode(काष्ठा ionic_lअगर *lअगर, अचिन्हित पूर्णांक rx_mode);
अटल पूर्णांक ionic_lअगर_addr_add(काष्ठा ionic_lअगर *lअगर, स्थिर u8 *addr);
अटल पूर्णांक ionic_lअगर_addr_del(काष्ठा ionic_lअगर *lअगर, स्थिर u8 *addr);
अटल व्योम ionic_link_status_check(काष्ठा ionic_lअगर *lअगर);
अटल व्योम ionic_lअगर_handle_fw_करोwn(काष्ठा ionic_lअगर *lअगर);
अटल व्योम ionic_lअगर_handle_fw_up(काष्ठा ionic_lअगर *lअगर);
अटल व्योम ionic_lअगर_set_netdev_info(काष्ठा ionic_lअगर *lअगर);

अटल व्योम ionic_txrx_deinit(काष्ठा ionic_lअगर *lअगर);
अटल पूर्णांक ionic_txrx_init(काष्ठा ionic_lअगर *lअगर);
अटल पूर्णांक ionic_start_queues(काष्ठा ionic_lअगर *lअगर);
अटल व्योम ionic_stop_queues(काष्ठा ionic_lअगर *lअगर);
अटल व्योम ionic_lअगर_queue_identअगरy(काष्ठा ionic_lअगर *lअगर);

अटल व्योम ionic_dim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा dim_cq_moder cur_moder;
	काष्ठा ionic_qcq *qcq;
	u32 new_coal;

	cur_moder = net_dim_get_rx_moderation(dim->mode, dim->profile_ix);
	qcq = container_of(dim, काष्ठा ionic_qcq, dim);
	new_coal = ionic_coal_usec_to_hw(qcq->q.lअगर->ionic, cur_moder.usec);
	qcq->पूर्णांकr.dim_coal_hw = new_coal ? new_coal : 1;
	dim->state = DIM_START_MEASURE;
पूर्ण

अटल व्योम ionic_lअगर_deferred_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ionic_lअगर *lअगर = container_of(work, काष्ठा ionic_lअगर, deferred.work);
	काष्ठा ionic_deferred *def = &lअगर->deferred;
	काष्ठा ionic_deferred_work *w = शून्य;

	करो अणु
		spin_lock_bh(&def->lock);
		अगर (!list_empty(&def->list)) अणु
			w = list_first_entry(&def->list,
					     काष्ठा ionic_deferred_work, list);
			list_del(&w->list);
		पूर्ण
		spin_unlock_bh(&def->lock);

		अगर (!w)
			अवरोध;

		चयन (w->type) अणु
		हाल IONIC_DW_TYPE_RX_MODE:
			ionic_lअगर_rx_mode(lअगर, w->rx_mode);
			अवरोध;
		हाल IONIC_DW_TYPE_RX_ADDR_ADD:
			ionic_lअगर_addr_add(lअगर, w->addr);
			अवरोध;
		हाल IONIC_DW_TYPE_RX_ADDR_DEL:
			ionic_lअगर_addr_del(lअगर, w->addr);
			अवरोध;
		हाल IONIC_DW_TYPE_LINK_STATUS:
			ionic_link_status_check(lअगर);
			अवरोध;
		हाल IONIC_DW_TYPE_LIF_RESET:
			अगर (w->fw_status)
				ionic_lअगर_handle_fw_up(lअगर);
			अन्यथा
				ionic_lअगर_handle_fw_करोwn(lअगर);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		kमुक्त(w);
		w = शून्य;
	पूर्ण जबतक (true);
पूर्ण

व्योम ionic_lअगर_deferred_enqueue(काष्ठा ionic_deferred *def,
				काष्ठा ionic_deferred_work *work)
अणु
	spin_lock_bh(&def->lock);
	list_add_tail(&work->list, &def->list);
	spin_unlock_bh(&def->lock);
	schedule_work(&def->work);
पूर्ण

अटल व्योम ionic_link_status_check(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा net_device *netdev = lअगर->netdev;
	u16 link_status;
	bool link_up;

	अगर (!test_bit(IONIC_LIF_F_LINK_CHECK_REQUESTED, lअगर->state))
		वापस;

	/* Don't put carrier back up if we're in a broken state */
	अगर (test_bit(IONIC_LIF_F_BROKEN, lअगर->state)) अणु
		clear_bit(IONIC_LIF_F_LINK_CHECK_REQUESTED, lअगर->state);
		वापस;
	पूर्ण

	link_status = le16_to_cpu(lअगर->info->status.link_status);
	link_up = link_status == IONIC_PORT_OPER_STATUS_UP;

	अगर (link_up) अणु
		पूर्णांक err = 0;

		अगर (netdev->flags & IFF_UP && netअगर_running(netdev)) अणु
			mutex_lock(&lअगर->queue_lock);
			err = ionic_start_queues(lअगर);
			अगर (err && err != -EBUSY) अणु
				netdev_err(lअगर->netdev,
					   "Failed to start queues: %d\n", err);
				set_bit(IONIC_LIF_F_BROKEN, lअगर->state);
				netअगर_carrier_off(lअगर->netdev);
			पूर्ण
			mutex_unlock(&lअगर->queue_lock);
		पूर्ण

		अगर (!err && !netअगर_carrier_ok(netdev)) अणु
			ionic_port_identअगरy(lअगर->ionic);
			netdev_info(netdev, "Link up - %d Gbps\n",
				    le32_to_cpu(lअगर->info->status.link_speed) / 1000);
			netअगर_carrier_on(netdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			netdev_info(netdev, "Link down\n");
			netअगर_carrier_off(netdev);
		पूर्ण

		अगर (netdev->flags & IFF_UP && netअगर_running(netdev)) अणु
			mutex_lock(&lअगर->queue_lock);
			ionic_stop_queues(lअगर);
			mutex_unlock(&lअगर->queue_lock);
		पूर्ण
	पूर्ण

	clear_bit(IONIC_LIF_F_LINK_CHECK_REQUESTED, lअगर->state);
पूर्ण

व्योम ionic_link_status_check_request(काष्ठा ionic_lअगर *lअगर, bool can_sleep)
अणु
	काष्ठा ionic_deferred_work *work;

	/* we only need one request outstanding at a समय */
	अगर (test_and_set_bit(IONIC_LIF_F_LINK_CHECK_REQUESTED, lअगर->state))
		वापस;

	अगर (!can_sleep) अणु
		work = kzalloc(माप(*work), GFP_ATOMIC);
		अगर (!work) अणु
			clear_bit(IONIC_LIF_F_LINK_CHECK_REQUESTED, lअगर->state);
			वापस;
		पूर्ण

		work->type = IONIC_DW_TYPE_LINK_STATUS;
		ionic_lअगर_deferred_enqueue(&lअगर->deferred, work);
	पूर्ण अन्यथा अणु
		ionic_link_status_check(lअगर);
	पूर्ण
पूर्ण

अटल irqवापस_t ionic_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा napi_काष्ठा *napi = data;

	napi_schedule_irqoff(napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ionic_request_irq(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा ionic_पूर्णांकr_info *पूर्णांकr = &qcq->पूर्णांकr;
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_queue *q = &qcq->q;
	स्थिर अक्षर *name;

	अगर (lअगर->रेजिस्टरed)
		name = lअगर->netdev->name;
	अन्यथा
		name = dev_name(dev);

	snम_लिखो(पूर्णांकr->name, माप(पूर्णांकr->name),
		 "%s-%s-%s", IONIC_DRV_NAME, name, q->name);

	वापस devm_request_irq(dev, पूर्णांकr->vector, ionic_isr,
				0, पूर्णांकr->name, &qcq->napi);
पूर्ण

अटल पूर्णांक ionic_पूर्णांकr_alloc(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_पूर्णांकr_info *पूर्णांकr)
अणु
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक index;

	index = find_first_zero_bit(ionic->पूर्णांकrs, ionic->nपूर्णांकrs);
	अगर (index == ionic->nपूर्णांकrs) अणु
		netdev_warn(lअगर->netdev, "%s: no intr, index=%d nintrs=%d\n",
			    __func__, index, ionic->nपूर्णांकrs);
		वापस -ENOSPC;
	पूर्ण

	set_bit(index, ionic->पूर्णांकrs);
	ionic_पूर्णांकr_init(&ionic->idev, पूर्णांकr, index);

	वापस 0;
पूर्ण

अटल व्योम ionic_पूर्णांकr_मुक्त(काष्ठा ionic *ionic, पूर्णांक index)
अणु
	अगर (index != IONIC_INTR_INDEX_NOT_ASSIGNED && index < ionic->nपूर्णांकrs)
		clear_bit(index, ionic->पूर्णांकrs);
पूर्ण

अटल पूर्णांक ionic_qcq_enable(काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा ionic_queue *q = &qcq->q;
	काष्ठा ionic_lअगर *lअगर = q->lअगर;
	काष्ठा ionic_dev *idev;
	काष्ठा device *dev;

	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.q_control = अणु
			.opcode = IONIC_CMD_Q_CONTROL,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.type = q->type,
			.index = cpu_to_le32(q->index),
			.oper = IONIC_Q_ENABLE,
		पूर्ण,
	पूर्ण;

	idev = &lअगर->ionic->idev;
	dev = lअगर->ionic->dev;

	dev_dbg(dev, "q_enable.index %d q_enable.qtype %d\n",
		ctx.cmd.q_control.index, ctx.cmd.q_control.type);

	अगर (qcq->flags & IONIC_QCQ_F_INTR) अणु
		irq_set_affinity_hपूर्णांक(qcq->पूर्णांकr.vector,
				      &qcq->पूर्णांकr.affinity_mask);
		napi_enable(&qcq->napi);
		ionic_पूर्णांकr_clean(idev->पूर्णांकr_ctrl, qcq->पूर्णांकr.index);
		ionic_पूर्णांकr_mask(idev->पूर्णांकr_ctrl, qcq->पूर्णांकr.index,
				IONIC_INTR_MASK_CLEAR);
	पूर्ण

	वापस ionic_adminq_post_रुको(lअगर, &ctx);
पूर्ण

अटल पूर्णांक ionic_qcq_disable(काष्ठा ionic_qcq *qcq, bool send_to_hw)
अणु
	काष्ठा ionic_queue *q;
	काष्ठा ionic_lअगर *lअगर;
	पूर्णांक err = 0;

	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.q_control = अणु
			.opcode = IONIC_CMD_Q_CONTROL,
			.oper = IONIC_Q_DISABLE,
		पूर्ण,
	पूर्ण;

	अगर (!qcq)
		वापस -ENXIO;

	q = &qcq->q;
	lअगर = q->lअगर;

	अगर (qcq->flags & IONIC_QCQ_F_INTR) अणु
		काष्ठा ionic_dev *idev = &lअगर->ionic->idev;

		cancel_work_sync(&qcq->dim.work);
		ionic_पूर्णांकr_mask(idev->पूर्णांकr_ctrl, qcq->पूर्णांकr.index,
				IONIC_INTR_MASK_SET);
		synchronize_irq(qcq->पूर्णांकr.vector);
		irq_set_affinity_hपूर्णांक(qcq->पूर्णांकr.vector, शून्य);
		napi_disable(&qcq->napi);
	पूर्ण

	अगर (send_to_hw) अणु
		ctx.cmd.q_control.lअगर_index = cpu_to_le16(lअगर->index);
		ctx.cmd.q_control.type = q->type;
		ctx.cmd.q_control.index = cpu_to_le32(q->index);
		dev_dbg(lअगर->ionic->dev, "q_disable.index %d q_disable.qtype %d\n",
			ctx.cmd.q_control.index, ctx.cmd.q_control.type);

		err = ionic_adminq_post_रुको(lअगर, &ctx);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ionic_lअगर_qcq_deinit(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;

	अगर (!qcq)
		वापस;

	अगर (!(qcq->flags & IONIC_QCQ_F_INITED))
		वापस;

	अगर (qcq->flags & IONIC_QCQ_F_INTR) अणु
		ionic_पूर्णांकr_mask(idev->पूर्णांकr_ctrl, qcq->पूर्णांकr.index,
				IONIC_INTR_MASK_SET);
		netअगर_napi_del(&qcq->napi);
	पूर्ण

	qcq->flags &= ~IONIC_QCQ_F_INITED;
पूर्ण

अटल व्योम ionic_qcq_पूर्णांकr_मुक्त(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	अगर (!(qcq->flags & IONIC_QCQ_F_INTR) || qcq->पूर्णांकr.vector == 0)
		वापस;

	irq_set_affinity_hपूर्णांक(qcq->पूर्णांकr.vector, शून्य);
	devm_मुक्त_irq(lअगर->ionic->dev, qcq->पूर्णांकr.vector, &qcq->napi);
	qcq->पूर्णांकr.vector = 0;
	ionic_पूर्णांकr_मुक्त(lअगर->ionic, qcq->पूर्णांकr.index);
	qcq->पूर्णांकr.index = IONIC_INTR_INDEX_NOT_ASSIGNED;
पूर्ण

अटल व्योम ionic_qcq_मुक्त(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;

	अगर (!qcq)
		वापस;

	ionic_debugfs_del_qcq(qcq);

	अगर (qcq->q_base) अणु
		dma_मुक्त_coherent(dev, qcq->q_size, qcq->q_base, qcq->q_base_pa);
		qcq->q_base = शून्य;
		qcq->q_base_pa = 0;
	पूर्ण

	अगर (qcq->cq_base) अणु
		dma_मुक्त_coherent(dev, qcq->cq_size, qcq->cq_base, qcq->cq_base_pa);
		qcq->cq_base = शून्य;
		qcq->cq_base_pa = 0;
	पूर्ण

	अगर (qcq->sg_base) अणु
		dma_मुक्त_coherent(dev, qcq->sg_size, qcq->sg_base, qcq->sg_base_pa);
		qcq->sg_base = शून्य;
		qcq->sg_base_pa = 0;
	पूर्ण

	ionic_qcq_पूर्णांकr_मुक्त(lअगर, qcq);

	अगर (qcq->cq.info) अणु
		devm_kमुक्त(dev, qcq->cq.info);
		qcq->cq.info = शून्य;
	पूर्ण
	अगर (qcq->q.info) अणु
		devm_kमुक्त(dev, qcq->q.info);
		qcq->q.info = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ionic_qcqs_मुक्त(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_qcq *adminqcq;
	अचिन्हित दीर्घ irqflags;

	अगर (lअगर->notअगरyqcq) अणु
		ionic_qcq_मुक्त(lअगर, lअगर->notअगरyqcq);
		devm_kमुक्त(dev, lअगर->notअगरyqcq);
		lअगर->notअगरyqcq = शून्य;
	पूर्ण

	अगर (lअगर->adminqcq) अणु
		spin_lock_irqsave(&lअगर->adminq_lock, irqflags);
		adminqcq = READ_ONCE(lअगर->adminqcq);
		lअगर->adminqcq = शून्य;
		spin_unlock_irqrestore(&lअगर->adminq_lock, irqflags);
		अगर (adminqcq) अणु
			ionic_qcq_मुक्त(lअगर, adminqcq);
			devm_kमुक्त(dev, adminqcq);
		पूर्ण
	पूर्ण

	अगर (lअगर->rxqcqs) अणु
		devm_kमुक्त(dev, lअगर->rxqstats);
		lअगर->rxqstats = शून्य;
		devm_kमुक्त(dev, lअगर->rxqcqs);
		lअगर->rxqcqs = शून्य;
	पूर्ण

	अगर (lअगर->txqcqs) अणु
		devm_kमुक्त(dev, lअगर->txqstats);
		lअगर->txqstats = शून्य;
		devm_kमुक्त(dev, lअगर->txqcqs);
		lअगर->txqcqs = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ionic_link_qcq_पूर्णांकerrupts(काष्ठा ionic_qcq *src_qcq,
				      काष्ठा ionic_qcq *n_qcq)
अणु
	अगर (WARN_ON(n_qcq->flags & IONIC_QCQ_F_INTR)) अणु
		ionic_पूर्णांकr_मुक्त(n_qcq->cq.lअगर->ionic, n_qcq->पूर्णांकr.index);
		n_qcq->flags &= ~IONIC_QCQ_F_INTR;
	पूर्ण

	n_qcq->पूर्णांकr.vector = src_qcq->पूर्णांकr.vector;
	n_qcq->पूर्णांकr.index = src_qcq->पूर्णांकr.index;
पूर्ण

अटल पूर्णांक ionic_alloc_qcq_पूर्णांकerrupt(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	पूर्णांक err;

	अगर (!(qcq->flags & IONIC_QCQ_F_INTR)) अणु
		qcq->पूर्णांकr.index = IONIC_INTR_INDEX_NOT_ASSIGNED;
		वापस 0;
	पूर्ण

	err = ionic_पूर्णांकr_alloc(lअगर, &qcq->पूर्णांकr);
	अगर (err) अणु
		netdev_warn(lअगर->netdev, "no intr for %s: %d\n",
			    qcq->q.name, err);
		जाओ err_out;
	पूर्ण

	err = ionic_bus_get_irq(lअगर->ionic, qcq->पूर्णांकr.index);
	अगर (err < 0) अणु
		netdev_warn(lअगर->netdev, "no vector for %s: %d\n",
			    qcq->q.name, err);
		जाओ err_out_मुक्त_पूर्णांकr;
	पूर्ण
	qcq->पूर्णांकr.vector = err;
	ionic_पूर्णांकr_mask_निश्चित(lअगर->ionic->idev.पूर्णांकr_ctrl, qcq->पूर्णांकr.index,
			       IONIC_INTR_MASK_SET);

	err = ionic_request_irq(lअगर, qcq);
	अगर (err) अणु
		netdev_warn(lअगर->netdev, "irq request failed %d\n", err);
		जाओ err_out_मुक्त_पूर्णांकr;
	पूर्ण

	/* try to get the irq on the local numa node first */
	qcq->पूर्णांकr.cpu = cpumask_local_spपढ़ो(qcq->पूर्णांकr.index,
					     dev_to_node(lअगर->ionic->dev));
	अगर (qcq->पूर्णांकr.cpu != -1)
		cpumask_set_cpu(qcq->पूर्णांकr.cpu, &qcq->पूर्णांकr.affinity_mask);

	netdev_dbg(lअगर->netdev, "%s: Interrupt index %d\n", qcq->q.name, qcq->पूर्णांकr.index);
	वापस 0;

err_out_मुक्त_पूर्णांकr:
	ionic_पूर्णांकr_मुक्त(lअगर->ionic, qcq->पूर्णांकr.index);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक ionic_qcq_alloc(काष्ठा ionic_lअगर *lअगर, अचिन्हित पूर्णांक type,
			   अचिन्हित पूर्णांक index,
			   स्थिर अक्षर *name, अचिन्हित पूर्णांक flags,
			   अचिन्हित पूर्णांक num_descs, अचिन्हित पूर्णांक desc_size,
			   अचिन्हित पूर्णांक cq_desc_size,
			   अचिन्हित पूर्णांक sg_desc_size,
			   अचिन्हित पूर्णांक pid, काष्ठा ionic_qcq **qcq)
अणु
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	काष्ठा device *dev = lअगर->ionic->dev;
	व्योम *q_base, *cq_base, *sg_base;
	dma_addr_t cq_base_pa = 0;
	dma_addr_t sg_base_pa = 0;
	dma_addr_t q_base_pa = 0;
	काष्ठा ionic_qcq *new;
	पूर्णांक err;

	*qcq = शून्य;

	new = devm_kzalloc(dev, माप(*new), GFP_KERNEL);
	अगर (!new) अणु
		netdev_err(lअगर->netdev, "Cannot allocate queue structure\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	new->q.dev = dev;
	new->flags = flags;

	new->q.info = devm_kसुस्मृति(dev, num_descs, माप(*new->q.info),
				   GFP_KERNEL);
	अगर (!new->q.info) अणु
		netdev_err(lअगर->netdev, "Cannot allocate queue info\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_qcq;
	पूर्ण

	new->q.type = type;
	new->q.max_sg_elems = lअगर->qtype_info[type].max_sg_elems;

	err = ionic_q_init(lअगर, idev, &new->q, index, name, num_descs,
			   desc_size, sg_desc_size, pid);
	अगर (err) अणु
		netdev_err(lअगर->netdev, "Cannot initialize queue\n");
		जाओ err_out_मुक्त_q_info;
	पूर्ण

	err = ionic_alloc_qcq_पूर्णांकerrupt(lअगर, new);
	अगर (err)
		जाओ err_out;

	new->cq.info = devm_kसुस्मृति(dev, num_descs, माप(*new->cq.info),
				    GFP_KERNEL);
	अगर (!new->cq.info) अणु
		netdev_err(lअगर->netdev, "Cannot allocate completion queue info\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_irq;
	पूर्ण

	err = ionic_cq_init(lअगर, &new->cq, &new->पूर्णांकr, num_descs, cq_desc_size);
	अगर (err) अणु
		netdev_err(lअगर->netdev, "Cannot initialize completion queue\n");
		जाओ err_out_मुक्त_cq_info;
	पूर्ण

	अगर (flags & IONIC_QCQ_F_NOTIFYQ) अणु
		पूर्णांक q_size, cq_size;

		/* q & cq need to be contiguous in हाल of notअगरyq */
		q_size = ALIGN(num_descs * desc_size, PAGE_SIZE);
		cq_size = ALIGN(num_descs * cq_desc_size, PAGE_SIZE);

		new->q_size = PAGE_SIZE + q_size + cq_size;
		new->q_base = dma_alloc_coherent(dev, new->q_size,
						 &new->q_base_pa, GFP_KERNEL);
		अगर (!new->q_base) अणु
			netdev_err(lअगर->netdev, "Cannot allocate qcq DMA memory\n");
			err = -ENOMEM;
			जाओ err_out_मुक्त_cq_info;
		पूर्ण
		q_base = PTR_ALIGN(new->q_base, PAGE_SIZE);
		q_base_pa = ALIGN(new->q_base_pa, PAGE_SIZE);
		ionic_q_map(&new->q, q_base, q_base_pa);

		cq_base = PTR_ALIGN(q_base + q_size, PAGE_SIZE);
		cq_base_pa = ALIGN(new->q_base_pa + q_size, PAGE_SIZE);
		ionic_cq_map(&new->cq, cq_base, cq_base_pa);
		ionic_cq_bind(&new->cq, &new->q);
	पूर्ण अन्यथा अणु
		new->q_size = PAGE_SIZE + (num_descs * desc_size);
		new->q_base = dma_alloc_coherent(dev, new->q_size, &new->q_base_pa,
						 GFP_KERNEL);
		अगर (!new->q_base) अणु
			netdev_err(lअगर->netdev, "Cannot allocate queue DMA memory\n");
			err = -ENOMEM;
			जाओ err_out_मुक्त_cq_info;
		पूर्ण
		q_base = PTR_ALIGN(new->q_base, PAGE_SIZE);
		q_base_pa = ALIGN(new->q_base_pa, PAGE_SIZE);
		ionic_q_map(&new->q, q_base, q_base_pa);

		new->cq_size = PAGE_SIZE + (num_descs * cq_desc_size);
		new->cq_base = dma_alloc_coherent(dev, new->cq_size, &new->cq_base_pa,
						  GFP_KERNEL);
		अगर (!new->cq_base) अणु
			netdev_err(lअगर->netdev, "Cannot allocate cq DMA memory\n");
			err = -ENOMEM;
			जाओ err_out_मुक्त_q;
		पूर्ण
		cq_base = PTR_ALIGN(new->cq_base, PAGE_SIZE);
		cq_base_pa = ALIGN(new->cq_base_pa, PAGE_SIZE);
		ionic_cq_map(&new->cq, cq_base, cq_base_pa);
		ionic_cq_bind(&new->cq, &new->q);
	पूर्ण

	अगर (flags & IONIC_QCQ_F_SG) अणु
		new->sg_size = PAGE_SIZE + (num_descs * sg_desc_size);
		new->sg_base = dma_alloc_coherent(dev, new->sg_size, &new->sg_base_pa,
						  GFP_KERNEL);
		अगर (!new->sg_base) अणु
			netdev_err(lअगर->netdev, "Cannot allocate sg DMA memory\n");
			err = -ENOMEM;
			जाओ err_out_मुक्त_cq;
		पूर्ण
		sg_base = PTR_ALIGN(new->sg_base, PAGE_SIZE);
		sg_base_pa = ALIGN(new->sg_base_pa, PAGE_SIZE);
		ionic_q_sg_map(&new->q, sg_base, sg_base_pa);
	पूर्ण

	INIT_WORK(&new->dim.work, ionic_dim_work);
	new->dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;

	*qcq = new;

	वापस 0;

err_out_मुक्त_cq:
	dma_मुक्त_coherent(dev, new->cq_size, new->cq_base, new->cq_base_pa);
err_out_मुक्त_q:
	dma_मुक्त_coherent(dev, new->q_size, new->q_base, new->q_base_pa);
err_out_मुक्त_cq_info:
	devm_kमुक्त(dev, new->cq.info);
err_out_मुक्त_irq:
	अगर (flags & IONIC_QCQ_F_INTR) अणु
		devm_मुक्त_irq(dev, new->पूर्णांकr.vector, &new->napi);
		ionic_पूर्णांकr_मुक्त(lअगर->ionic, new->पूर्णांकr.index);
	पूर्ण
err_out_मुक्त_q_info:
	devm_kमुक्त(dev, new->q.info);
err_out_मुक्त_qcq:
	devm_kमुक्त(dev, new);
err_out:
	dev_err(dev, "qcq alloc of %s%d failed %d\n", name, index, err);
	वापस err;
पूर्ण

अटल पूर्णांक ionic_qcqs_alloc(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	flags = IONIC_QCQ_F_INTR;
	err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_ADMINQ, 0, "admin", flags,
			      IONIC_ADMINQ_LENGTH,
			      माप(काष्ठा ionic_admin_cmd),
			      माप(काष्ठा ionic_admin_comp),
			      0, lअगर->kern_pid, &lअगर->adminqcq);
	अगर (err)
		वापस err;
	ionic_debugfs_add_qcq(lअगर, lअगर->adminqcq);

	अगर (lअगर->ionic->nnqs_per_lअगर) अणु
		flags = IONIC_QCQ_F_NOTIFYQ;
		err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_NOTIFYQ, 0, "notifyq",
				      flags, IONIC_NOTIFYQ_LENGTH,
				      माप(काष्ठा ionic_notअगरyq_cmd),
				      माप(जोड़ ionic_notअगरyq_comp),
				      0, lअगर->kern_pid, &lअगर->notअगरyqcq);
		अगर (err)
			जाओ err_out;
		ionic_debugfs_add_qcq(lअगर, lअगर->notअगरyqcq);

		/* Let the notअगरyq ride on the adminq पूर्णांकerrupt */
		ionic_link_qcq_पूर्णांकerrupts(lअगर->adminqcq, lअगर->notअगरyqcq);
	पूर्ण

	err = -ENOMEM;
	lअगर->txqcqs = devm_kसुस्मृति(dev, lअगर->ionic->ntxqs_per_lअगर,
				   माप(*lअगर->txqcqs), GFP_KERNEL);
	अगर (!lअगर->txqcqs)
		जाओ err_out;
	lअगर->rxqcqs = devm_kसुस्मृति(dev, lअगर->ionic->nrxqs_per_lअगर,
				   माप(*lअगर->rxqcqs), GFP_KERNEL);
	अगर (!lअगर->rxqcqs)
		जाओ err_out;

	lअगर->txqstats = devm_kसुस्मृति(dev, lअगर->ionic->ntxqs_per_lअगर + 1,
				     माप(*lअगर->txqstats), GFP_KERNEL);
	अगर (!lअगर->txqstats)
		जाओ err_out;
	lअगर->rxqstats = devm_kसुस्मृति(dev, lअगर->ionic->nrxqs_per_lअगर + 1,
				     माप(*lअगर->rxqstats), GFP_KERNEL);
	अगर (!lअगर->rxqstats)
		जाओ err_out;

	वापस 0;

err_out:
	ionic_qcqs_मुक्त(lअगर);
	वापस err;
पूर्ण

अटल व्योम ionic_qcq_sanitize(काष्ठा ionic_qcq *qcq)
अणु
	qcq->q.tail_idx = 0;
	qcq->q.head_idx = 0;
	qcq->cq.tail_idx = 0;
	qcq->cq.करोne_color = 1;
	स_रखो(qcq->q_base, 0, qcq->q_size);
	स_रखो(qcq->cq_base, 0, qcq->cq_size);
	स_रखो(qcq->sg_base, 0, qcq->sg_size);
पूर्ण

अटल पूर्णांक ionic_lअगर_txq_init(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_queue *q = &qcq->q;
	काष्ठा ionic_cq *cq = &qcq->cq;
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.q_init = अणु
			.opcode = IONIC_CMD_Q_INIT,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.type = q->type,
			.ver = lअगर->qtype_info[q->type].version,
			.index = cpu_to_le32(q->index),
			.flags = cpu_to_le16(IONIC_QINIT_F_IRQ |
					     IONIC_QINIT_F_SG),
			.pid = cpu_to_le16(q->pid),
			.ring_size = ilog2(q->num_descs),
			.ring_base = cpu_to_le64(q->base_pa),
			.cq_ring_base = cpu_to_le64(cq->base_pa),
			.sg_ring_base = cpu_to_le64(q->sg_base_pa),
			.features = cpu_to_le64(q->features),
		पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक पूर्णांकr_index;
	पूर्णांक err;

	पूर्णांकr_index = qcq->पूर्णांकr.index;

	ctx.cmd.q_init.पूर्णांकr_index = cpu_to_le16(पूर्णांकr_index);

	dev_dbg(dev, "txq_init.pid %d\n", ctx.cmd.q_init.pid);
	dev_dbg(dev, "txq_init.index %d\n", ctx.cmd.q_init.index);
	dev_dbg(dev, "txq_init.ring_base 0x%llx\n", ctx.cmd.q_init.ring_base);
	dev_dbg(dev, "txq_init.ring_size %d\n", ctx.cmd.q_init.ring_size);
	dev_dbg(dev, "txq_init.flags 0x%x\n", ctx.cmd.q_init.flags);
	dev_dbg(dev, "txq_init.ver %d\n", ctx.cmd.q_init.ver);
	dev_dbg(dev, "txq_init.intr_index %d\n", ctx.cmd.q_init.पूर्णांकr_index);

	ionic_qcq_sanitize(qcq);

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		वापस err;

	q->hw_type = ctx.comp.q_init.hw_type;
	q->hw_index = le32_to_cpu(ctx.comp.q_init.hw_index);
	q->dbval = IONIC_DBELL_QID(q->hw_index);

	dev_dbg(dev, "txq->hw_type %d\n", q->hw_type);
	dev_dbg(dev, "txq->hw_index %d\n", q->hw_index);

	अगर (test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
		netअगर_napi_add(lअगर->netdev, &qcq->napi, ionic_tx_napi,
			       NAPI_POLL_WEIGHT);

	qcq->flags |= IONIC_QCQ_F_INITED;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_lअगर_rxq_init(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_queue *q = &qcq->q;
	काष्ठा ionic_cq *cq = &qcq->cq;
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.q_init = अणु
			.opcode = IONIC_CMD_Q_INIT,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.type = q->type,
			.ver = lअगर->qtype_info[q->type].version,
			.index = cpu_to_le32(q->index),
			.flags = cpu_to_le16(IONIC_QINIT_F_IRQ |
					     IONIC_QINIT_F_SG),
			.पूर्णांकr_index = cpu_to_le16(cq->bound_पूर्णांकr->index),
			.pid = cpu_to_le16(q->pid),
			.ring_size = ilog2(q->num_descs),
			.ring_base = cpu_to_le64(q->base_pa),
			.cq_ring_base = cpu_to_le64(cq->base_pa),
			.sg_ring_base = cpu_to_le64(q->sg_base_pa),
			.features = cpu_to_le64(q->features),
		पूर्ण,
	पूर्ण;
	पूर्णांक err;

	dev_dbg(dev, "rxq_init.pid %d\n", ctx.cmd.q_init.pid);
	dev_dbg(dev, "rxq_init.index %d\n", ctx.cmd.q_init.index);
	dev_dbg(dev, "rxq_init.ring_base 0x%llx\n", ctx.cmd.q_init.ring_base);
	dev_dbg(dev, "rxq_init.ring_size %d\n", ctx.cmd.q_init.ring_size);
	dev_dbg(dev, "rxq_init.flags 0x%x\n", ctx.cmd.q_init.flags);
	dev_dbg(dev, "rxq_init.ver %d\n", ctx.cmd.q_init.ver);
	dev_dbg(dev, "rxq_init.intr_index %d\n", ctx.cmd.q_init.पूर्णांकr_index);

	ionic_qcq_sanitize(qcq);

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		वापस err;

	q->hw_type = ctx.comp.q_init.hw_type;
	q->hw_index = le32_to_cpu(ctx.comp.q_init.hw_index);
	q->dbval = IONIC_DBELL_QID(q->hw_index);

	dev_dbg(dev, "rxq->hw_type %d\n", q->hw_type);
	dev_dbg(dev, "rxq->hw_index %d\n", q->hw_index);

	अगर (test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
		netअगर_napi_add(lअगर->netdev, &qcq->napi, ionic_rx_napi,
			       NAPI_POLL_WEIGHT);
	अन्यथा
		netअगर_napi_add(lअगर->netdev, &qcq->napi, ionic_txrx_napi,
			       NAPI_POLL_WEIGHT);

	qcq->flags |= IONIC_QCQ_F_INITED;

	वापस 0;
पूर्ण

पूर्णांक ionic_lअगर_create_hwstamp_txq(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक num_desc, desc_sz, comp_sz, sg_desc_sz;
	अचिन्हित पूर्णांक txq_i, flags;
	काष्ठा ionic_qcq *txq;
	u64 features;
	पूर्णांक err;

	mutex_lock(&lअगर->queue_lock);

	अगर (lअगर->hwstamp_txq)
		जाओ out;

	features = IONIC_Q_F_2X_CQ_DESC | IONIC_TXQ_F_HWSTAMP;

	num_desc = IONIC_MIN_TXRX_DESC;
	desc_sz = माप(काष्ठा ionic_txq_desc);
	comp_sz = 2 * माप(काष्ठा ionic_txq_comp);

	अगर (lअगर->qtype_info[IONIC_QTYPE_TXQ].version >= 1 &&
	    lअगर->qtype_info[IONIC_QTYPE_TXQ].sg_desc_sz == माप(काष्ठा ionic_txq_sg_desc_v1))
		sg_desc_sz = माप(काष्ठा ionic_txq_sg_desc_v1);
	अन्यथा
		sg_desc_sz = माप(काष्ठा ionic_txq_sg_desc);

	txq_i = lअगर->ionic->ntxqs_per_lअगर;
	flags = IONIC_QCQ_F_TX_STATS | IONIC_QCQ_F_SG;

	err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_TXQ, txq_i, "hwstamp_tx", flags,
			      num_desc, desc_sz, comp_sz, sg_desc_sz,
			      lअगर->kern_pid, &txq);
	अगर (err)
		जाओ err_qcq_alloc;

	txq->q.features = features;

	ionic_link_qcq_पूर्णांकerrupts(lअगर->adminqcq, txq);
	ionic_debugfs_add_qcq(lअगर, txq);

	lअगर->hwstamp_txq = txq;

	अगर (netअगर_running(lअगर->netdev)) अणु
		err = ionic_lअगर_txq_init(lअगर, txq);
		अगर (err)
			जाओ err_qcq_init;

		अगर (test_bit(IONIC_LIF_F_UP, lअगर->state)) अणु
			err = ionic_qcq_enable(txq);
			अगर (err)
				जाओ err_qcq_enable;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&lअगर->queue_lock);

	वापस 0;

err_qcq_enable:
	ionic_lअगर_qcq_deinit(lअगर, txq);
err_qcq_init:
	lअगर->hwstamp_txq = शून्य;
	ionic_debugfs_del_qcq(txq);
	ionic_qcq_मुक्त(lअगर, txq);
	devm_kमुक्त(lअगर->ionic->dev, txq);
err_qcq_alloc:
	mutex_unlock(&lअगर->queue_lock);
	वापस err;
पूर्ण

पूर्णांक ionic_lअगर_create_hwstamp_rxq(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक num_desc, desc_sz, comp_sz, sg_desc_sz;
	अचिन्हित पूर्णांक rxq_i, flags;
	काष्ठा ionic_qcq *rxq;
	u64 features;
	पूर्णांक err;

	mutex_lock(&lअगर->queue_lock);

	अगर (lअगर->hwstamp_rxq)
		जाओ out;

	features = IONIC_Q_F_2X_CQ_DESC | IONIC_RXQ_F_HWSTAMP;

	num_desc = IONIC_MIN_TXRX_DESC;
	desc_sz = माप(काष्ठा ionic_rxq_desc);
	comp_sz = 2 * माप(काष्ठा ionic_rxq_comp);
	sg_desc_sz = माप(काष्ठा ionic_rxq_sg_desc);

	rxq_i = lअगर->ionic->nrxqs_per_lअगर;
	flags = IONIC_QCQ_F_RX_STATS | IONIC_QCQ_F_SG;

	err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_RXQ, rxq_i, "hwstamp_rx", flags,
			      num_desc, desc_sz, comp_sz, sg_desc_sz,
			      lअगर->kern_pid, &rxq);
	अगर (err)
		जाओ err_qcq_alloc;

	rxq->q.features = features;

	ionic_link_qcq_पूर्णांकerrupts(lअगर->adminqcq, rxq);
	ionic_debugfs_add_qcq(lअगर, rxq);

	lअगर->hwstamp_rxq = rxq;

	अगर (netअगर_running(lअगर->netdev)) अणु
		err = ionic_lअगर_rxq_init(lअगर, rxq);
		अगर (err)
			जाओ err_qcq_init;

		अगर (test_bit(IONIC_LIF_F_UP, lअगर->state)) अणु
			ionic_rx_fill(&rxq->q);
			err = ionic_qcq_enable(rxq);
			अगर (err)
				जाओ err_qcq_enable;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&lअगर->queue_lock);

	वापस 0;

err_qcq_enable:
	ionic_lअगर_qcq_deinit(lअगर, rxq);
err_qcq_init:
	lअगर->hwstamp_rxq = शून्य;
	ionic_debugfs_del_qcq(rxq);
	ionic_qcq_मुक्त(lअगर, rxq);
	devm_kमुक्त(lअगर->ionic->dev, rxq);
err_qcq_alloc:
	mutex_unlock(&lअगर->queue_lock);
	वापस err;
पूर्ण

पूर्णांक ionic_lअगर_config_hwstamp_rxq_all(काष्ठा ionic_lअगर *lअगर, bool rx_all)
अणु
	काष्ठा ionic_queue_params qparam;

	ionic_init_queue_params(lअगर, &qparam);

	अगर (rx_all)
		qparam.rxq_features = IONIC_Q_F_2X_CQ_DESC | IONIC_RXQ_F_HWSTAMP;
	अन्यथा
		qparam.rxq_features = 0;

	/* अगर we're not running, just set the values and वापस */
	अगर (!netअगर_running(lअगर->netdev)) अणु
		lअगर->rxq_features = qparam.rxq_features;
		वापस 0;
	पूर्ण

	वापस ionic_reconfigure_queues(lअगर, &qparam);
पूर्ण

पूर्णांक ionic_lअगर_set_hwstamp_txmode(काष्ठा ionic_lअगर *lअगर, u16 txstamp_mode)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.lअगर_setattr = अणु
			.opcode = IONIC_CMD_LIF_SETATTR,
			.index = cpu_to_le16(lअगर->index),
			.attr = IONIC_LIF_ATTR_TXSTAMP,
			.txstamp_mode = cpu_to_le16(txstamp_mode),
		पूर्ण,
	पूर्ण;

	वापस ionic_adminq_post_रुको(lअगर, &ctx);
पूर्ण

अटल व्योम ionic_lअगर_del_hwstamp_rxfilt(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.rx_filter_del = अणु
			.opcode = IONIC_CMD_RX_FILTER_DEL,
			.lअगर_index = cpu_to_le16(lअगर->index),
		पूर्ण,
	पूर्ण;
	काष्ठा ionic_rx_filter *f;
	u32 filter_id;
	पूर्णांक err;

	spin_lock_bh(&lअगर->rx_filters.lock);

	f = ionic_rx_filter_rxsteer(lअगर);
	अगर (!f) अणु
		spin_unlock_bh(&lअगर->rx_filters.lock);
		वापस;
	पूर्ण

	filter_id = f->filter_id;
	ionic_rx_filter_मुक्त(lअगर, f);

	spin_unlock_bh(&lअगर->rx_filters.lock);

	netdev_dbg(lअगर->netdev, "rx_filter del RXSTEER (id %d)\n", filter_id);

	ctx.cmd.rx_filter_del.filter_id = cpu_to_le32(filter_id);

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err && err != -EEXIST)
		netdev_dbg(lअगर->netdev, "failed to delete rx_filter RXSTEER (id %d)\n", filter_id);
पूर्ण

अटल पूर्णांक ionic_lअगर_add_hwstamp_rxfilt(काष्ठा ionic_lअगर *lअगर, u64 pkt_class)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.rx_filter_add = अणु
			.opcode = IONIC_CMD_RX_FILTER_ADD,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.match = cpu_to_le16(IONIC_RX_FILTER_STEER_PKTCLASS),
			.pkt_class = cpu_to_le64(pkt_class),
		पूर्ण,
	पूर्ण;
	u8 qtype;
	u32 qid;
	पूर्णांक err;

	अगर (!lअगर->hwstamp_rxq)
		वापस -EINVAL;

	qtype = lअगर->hwstamp_rxq->q.type;
	ctx.cmd.rx_filter_add.qtype = qtype;

	qid = lअगर->hwstamp_rxq->q.index;
	ctx.cmd.rx_filter_add.qid = cpu_to_le32(qid);

	netdev_dbg(lअगर->netdev, "rx_filter add RXSTEER\n");
	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err && err != -EEXIST)
		वापस err;

	वापस ionic_rx_filter_save(lअगर, 0, qid, 0, &ctx);
पूर्ण

पूर्णांक ionic_lअगर_set_hwstamp_rxfilt(काष्ठा ionic_lअगर *lअगर, u64 pkt_class)
अणु
	ionic_lअगर_del_hwstamp_rxfilt(lअगर);

	अगर (!pkt_class)
		वापस 0;

	वापस ionic_lअगर_add_hwstamp_rxfilt(lअगर, pkt_class);
पूर्ण

अटल bool ionic_notअगरyq_service(काष्ठा ionic_cq *cq,
				  काष्ठा ionic_cq_info *cq_info)
अणु
	जोड़ ionic_notअगरyq_comp *comp = cq_info->cq_desc;
	काष्ठा ionic_deferred_work *work;
	काष्ठा net_device *netdev;
	काष्ठा ionic_queue *q;
	काष्ठा ionic_lअगर *lअगर;
	u64 eid;

	q = cq->bound_q;
	lअगर = q->info[0].cb_arg;
	netdev = lअगर->netdev;
	eid = le64_to_cpu(comp->event.eid);

	/* Have we run out of new completions to process? */
	अगर ((s64)(eid - lअगर->last_eid) <= 0)
		वापस false;

	lअगर->last_eid = eid;

	dev_dbg(lअगर->ionic->dev, "notifyq event:\n");
	dynamic_hex_dump("event ", DUMP_PREFIX_OFFSET, 16, 1,
			 comp, माप(*comp), true);

	चयन (le16_to_cpu(comp->event.ecode)) अणु
	हाल IONIC_EVENT_LINK_CHANGE:
		ionic_link_status_check_request(lअगर, CAN_NOT_SLEEP);
		अवरोध;
	हाल IONIC_EVENT_RESET:
		work = kzalloc(माप(*work), GFP_ATOMIC);
		अगर (!work) अणु
			netdev_err(lअगर->netdev, "Reset event dropped\n");
		पूर्ण अन्यथा अणु
			work->type = IONIC_DW_TYPE_LIF_RESET;
			ionic_lअगर_deferred_enqueue(&lअगर->deferred, work);
		पूर्ण
		अवरोध;
	शेष:
		netdev_warn(netdev, "Notifyq event ecode=%d eid=%lld\n",
			    comp->event.ecode, eid);
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ionic_adminq_service(काष्ठा ionic_cq *cq,
				 काष्ठा ionic_cq_info *cq_info)
अणु
	काष्ठा ionic_admin_comp *comp = cq_info->cq_desc;

	अगर (!color_match(comp->color, cq->करोne_color))
		वापस false;

	ionic_q_service(cq->bound_q, cq_info, le16_to_cpu(comp->comp_index));

	वापस true;
पूर्ण

अटल पूर्णांक ionic_adminq_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ionic_पूर्णांकr_info *पूर्णांकr = napi_to_cq(napi)->bound_पूर्णांकr;
	काष्ठा ionic_lअगर *lअगर = napi_to_cq(napi)->lअगर;
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक rx_work = 0;
	पूर्णांक tx_work = 0;
	पूर्णांक n_work = 0;
	पूर्णांक a_work = 0;
	पूर्णांक work_करोne;
	पूर्णांक credits;

	अगर (lअगर->notअगरyqcq && lअगर->notअगरyqcq->flags & IONIC_QCQ_F_INITED)
		n_work = ionic_cq_service(&lअगर->notअगरyqcq->cq, budget,
					  ionic_notअगरyq_service, शून्य, शून्य);

	spin_lock_irqsave(&lअगर->adminq_lock, irqflags);
	अगर (lअगर->adminqcq && lअगर->adminqcq->flags & IONIC_QCQ_F_INITED)
		a_work = ionic_cq_service(&lअगर->adminqcq->cq, budget,
					  ionic_adminq_service, शून्य, शून्य);
	spin_unlock_irqrestore(&lअगर->adminq_lock, irqflags);

	अगर (lअगर->hwstamp_rxq)
		rx_work = ionic_cq_service(&lअगर->hwstamp_rxq->cq, budget,
					   ionic_rx_service, शून्य, शून्य);

	अगर (lअगर->hwstamp_txq)
		tx_work = ionic_cq_service(&lअगर->hwstamp_txq->cq, budget,
					   ionic_tx_service, शून्य, शून्य);

	work_करोne = max(max(n_work, a_work), max(rx_work, tx_work));
	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		flags |= IONIC_INTR_CRED_UNMASK;
		पूर्णांकr->rearm_count++;
	पूर्ण

	अगर (work_करोne || flags) अणु
		flags |= IONIC_INTR_CRED_RESET_COALESCE;
		credits = n_work + a_work + rx_work + tx_work;
		ionic_पूर्णांकr_credits(idev->पूर्णांकr_ctrl, पूर्णांकr->index, credits, flags);
	पूर्ण

	वापस work_करोne;
पूर्ण

व्योम ionic_get_stats64(काष्ठा net_device *netdev,
		       काष्ठा rtnl_link_stats64 *ns)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_lअगर_stats *ls;

	स_रखो(ns, 0, माप(*ns));
	ls = &lअगर->info->stats;

	ns->rx_packets = le64_to_cpu(ls->rx_ucast_packets) +
			 le64_to_cpu(ls->rx_mcast_packets) +
			 le64_to_cpu(ls->rx_bcast_packets);

	ns->tx_packets = le64_to_cpu(ls->tx_ucast_packets) +
			 le64_to_cpu(ls->tx_mcast_packets) +
			 le64_to_cpu(ls->tx_bcast_packets);

	ns->rx_bytes = le64_to_cpu(ls->rx_ucast_bytes) +
		       le64_to_cpu(ls->rx_mcast_bytes) +
		       le64_to_cpu(ls->rx_bcast_bytes);

	ns->tx_bytes = le64_to_cpu(ls->tx_ucast_bytes) +
		       le64_to_cpu(ls->tx_mcast_bytes) +
		       le64_to_cpu(ls->tx_bcast_bytes);

	ns->rx_dropped = le64_to_cpu(ls->rx_ucast_drop_packets) +
			 le64_to_cpu(ls->rx_mcast_drop_packets) +
			 le64_to_cpu(ls->rx_bcast_drop_packets);

	ns->tx_dropped = le64_to_cpu(ls->tx_ucast_drop_packets) +
			 le64_to_cpu(ls->tx_mcast_drop_packets) +
			 le64_to_cpu(ls->tx_bcast_drop_packets);

	ns->multicast = le64_to_cpu(ls->rx_mcast_packets);

	ns->rx_over_errors = le64_to_cpu(ls->rx_queue_empty);

	ns->rx_missed_errors = le64_to_cpu(ls->rx_dma_error) +
			       le64_to_cpu(ls->rx_queue_disabled) +
			       le64_to_cpu(ls->rx_desc_fetch_error) +
			       le64_to_cpu(ls->rx_desc_data_error);

	ns->tx_पातed_errors = le64_to_cpu(ls->tx_dma_error) +
				le64_to_cpu(ls->tx_queue_disabled) +
				le64_to_cpu(ls->tx_desc_fetch_error) +
				le64_to_cpu(ls->tx_desc_data_error);

	ns->rx_errors = ns->rx_over_errors +
			ns->rx_missed_errors;

	ns->tx_errors = ns->tx_पातed_errors;
पूर्ण

अटल पूर्णांक ionic_lअगर_addr_add(काष्ठा ionic_lअगर *lअगर, स्थिर u8 *addr)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.rx_filter_add = अणु
			.opcode = IONIC_CMD_RX_FILTER_ADD,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.match = cpu_to_le16(IONIC_RX_FILTER_MATCH_MAC),
		पूर्ण,
	पूर्ण;
	काष्ठा ionic_rx_filter *f;
	पूर्णांक err;

	/* करोn't bother अगर we alपढ़ोy have it */
	spin_lock_bh(&lअगर->rx_filters.lock);
	f = ionic_rx_filter_by_addr(lअगर, addr);
	spin_unlock_bh(&lअगर->rx_filters.lock);
	अगर (f)
		वापस 0;

	netdev_dbg(lअगर->netdev, "rx_filter add ADDR %pM\n", addr);

	स_नकल(ctx.cmd.rx_filter_add.mac.addr, addr, ETH_ALEN);
	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err && err != -EEXIST)
		वापस err;

	वापस ionic_rx_filter_save(lअगर, 0, IONIC_RXQ_INDEX_ANY, 0, &ctx);
पूर्ण

अटल पूर्णांक ionic_lअगर_addr_del(काष्ठा ionic_lअगर *lअगर, स्थिर u8 *addr)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.rx_filter_del = अणु
			.opcode = IONIC_CMD_RX_FILTER_DEL,
			.lअगर_index = cpu_to_le16(lअगर->index),
		पूर्ण,
	पूर्ण;
	काष्ठा ionic_rx_filter *f;
	पूर्णांक err;

	spin_lock_bh(&lअगर->rx_filters.lock);
	f = ionic_rx_filter_by_addr(lअगर, addr);
	अगर (!f) अणु
		spin_unlock_bh(&lअगर->rx_filters.lock);
		वापस -ENOENT;
	पूर्ण

	netdev_dbg(lअगर->netdev, "rx_filter del ADDR %pM (id %d)\n",
		   addr, f->filter_id);

	ctx.cmd.rx_filter_del.filter_id = cpu_to_le32(f->filter_id);
	ionic_rx_filter_मुक्त(lअगर, f);
	spin_unlock_bh(&lअगर->rx_filters.lock);

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err && err != -EEXIST)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_lअगर_addr(काष्ठा ionic_lअगर *lअगर, स्थिर u8 *addr, bool add,
			  bool can_sleep)
अणु
	काष्ठा ionic_deferred_work *work;
	अचिन्हित पूर्णांक nmfilters;
	अचिन्हित पूर्णांक nufilters;

	अगर (add) अणु
		/* Do we have space क्रम this filter?  We test the counters
		 * here beक्रमe checking the need क्रम deferral so that we
		 * can वापस an overflow error to the stack.
		 */
		nmfilters = le32_to_cpu(lअगर->identity->eth.max_mcast_filters);
		nufilters = le32_to_cpu(lअगर->identity->eth.max_ucast_filters);

		अगर ((is_multicast_ether_addr(addr) && lअगर->nmcast < nmfilters))
			lअगर->nmcast++;
		अन्यथा अगर (!is_multicast_ether_addr(addr) &&
			 lअगर->nucast < nufilters)
			lअगर->nucast++;
		अन्यथा
			वापस -ENOSPC;
	पूर्ण अन्यथा अणु
		अगर (is_multicast_ether_addr(addr) && lअगर->nmcast)
			lअगर->nmcast--;
		अन्यथा अगर (!is_multicast_ether_addr(addr) && lअगर->nucast)
			lअगर->nucast--;
	पूर्ण

	अगर (!can_sleep) अणु
		work = kzalloc(माप(*work), GFP_ATOMIC);
		अगर (!work)
			वापस -ENOMEM;
		work->type = add ? IONIC_DW_TYPE_RX_ADDR_ADD :
				   IONIC_DW_TYPE_RX_ADDR_DEL;
		स_नकल(work->addr, addr, ETH_ALEN);
		netdev_dbg(lअगर->netdev, "deferred: rx_filter %s %pM\n",
			   add ? "add" : "del", addr);
		ionic_lअगर_deferred_enqueue(&lअगर->deferred, work);
	पूर्ण अन्यथा अणु
		netdev_dbg(lअगर->netdev, "rx_filter %s %pM\n",
			   add ? "add" : "del", addr);
		अगर (add)
			वापस ionic_lअगर_addr_add(lअगर, addr);
		अन्यथा
			वापस ionic_lअगर_addr_del(lअगर, addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_addr_add(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	वापस ionic_lअगर_addr(netdev_priv(netdev), addr, ADD_ADDR, CAN_SLEEP);
पूर्ण

अटल पूर्णांक ionic_nकरो_addr_add(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	वापस ionic_lअगर_addr(netdev_priv(netdev), addr, ADD_ADDR, CAN_NOT_SLEEP);
पूर्ण

अटल पूर्णांक ionic_addr_del(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	वापस ionic_lअगर_addr(netdev_priv(netdev), addr, DEL_ADDR, CAN_SLEEP);
पूर्ण

अटल पूर्णांक ionic_nकरो_addr_del(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	वापस ionic_lअगर_addr(netdev_priv(netdev), addr, DEL_ADDR, CAN_NOT_SLEEP);
पूर्ण

अटल व्योम ionic_lअगर_rx_mode(काष्ठा ionic_lअगर *lअगर, अचिन्हित पूर्णांक rx_mode)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.rx_mode_set = अणु
			.opcode = IONIC_CMD_RX_MODE_SET,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.rx_mode = cpu_to_le16(rx_mode),
		पूर्ण,
	पूर्ण;
	अक्षर buf[128];
	पूर्णांक err;
	पूर्णांक i;
#घोषणा REMAIN(__x) (माप(buf) - (__x))

	i = scnम_लिखो(buf, माप(buf), "rx_mode 0x%04x -> 0x%04x:",
		      lअगर->rx_mode, rx_mode);
	अगर (rx_mode & IONIC_RX_MODE_F_UNICAST)
		i += scnम_लिखो(&buf[i], REMAIN(i), " RX_MODE_F_UNICAST");
	अगर (rx_mode & IONIC_RX_MODE_F_MULTICAST)
		i += scnम_लिखो(&buf[i], REMAIN(i), " RX_MODE_F_MULTICAST");
	अगर (rx_mode & IONIC_RX_MODE_F_BROADCAST)
		i += scnम_लिखो(&buf[i], REMAIN(i), " RX_MODE_F_BROADCAST");
	अगर (rx_mode & IONIC_RX_MODE_F_PROMISC)
		i += scnम_लिखो(&buf[i], REMAIN(i), " RX_MODE_F_PROMISC");
	अगर (rx_mode & IONIC_RX_MODE_F_ALLMULTI)
		i += scnम_लिखो(&buf[i], REMAIN(i), " RX_MODE_F_ALLMULTI");
	netdev_dbg(lअगर->netdev, "lif%d %s\n", lअगर->index, buf);

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		netdev_warn(lअगर->netdev, "set rx_mode 0x%04x failed: %d\n",
			    rx_mode, err);
	अन्यथा
		lअगर->rx_mode = rx_mode;
पूर्ण

अटल व्योम ionic_set_rx_mode(काष्ठा net_device *netdev, bool can_sleep)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_deferred_work *work;
	अचिन्हित पूर्णांक nfilters;
	अचिन्हित पूर्णांक rx_mode;

	rx_mode = IONIC_RX_MODE_F_UNICAST;
	rx_mode |= (netdev->flags & IFF_MULTICAST) ? IONIC_RX_MODE_F_MULTICAST : 0;
	rx_mode |= (netdev->flags & IFF_BROADCAST) ? IONIC_RX_MODE_F_BROADCAST : 0;
	rx_mode |= (netdev->flags & IFF_PROMISC) ? IONIC_RX_MODE_F_PROMISC : 0;
	rx_mode |= (netdev->flags & IFF_ALLMULTI) ? IONIC_RX_MODE_F_ALLMULTI : 0;

	/* sync unicast addresses
	 * next check to see अगर we're in an overflow state
	 *    अगर so, we track that we overflowed and enable NIC PROMISC
	 *    अन्यथा अगर the overflow is set and not needed
	 *       we हटाओ our overflow flag and check the netdev flags
	 *       to see अगर we can disable NIC PROMISC
	 */
	अगर (can_sleep)
		__dev_uc_sync(netdev, ionic_addr_add, ionic_addr_del);
	अन्यथा
		__dev_uc_sync(netdev, ionic_nकरो_addr_add, ionic_nकरो_addr_del);
	nfilters = le32_to_cpu(lअगर->identity->eth.max_ucast_filters);
	अगर (netdev_uc_count(netdev) + 1 > nfilters) अणु
		rx_mode |= IONIC_RX_MODE_F_PROMISC;
		lअगर->uc_overflow = true;
	पूर्ण अन्यथा अगर (lअगर->uc_overflow) अणु
		lअगर->uc_overflow = false;
		अगर (!(netdev->flags & IFF_PROMISC))
			rx_mode &= ~IONIC_RX_MODE_F_PROMISC;
	पूर्ण

	/* same क्रम multicast */
	अगर (can_sleep)
		__dev_mc_sync(netdev, ionic_addr_add, ionic_addr_del);
	अन्यथा
		__dev_mc_sync(netdev, ionic_nकरो_addr_add, ionic_nकरो_addr_del);
	nfilters = le32_to_cpu(lअगर->identity->eth.max_mcast_filters);
	अगर (netdev_mc_count(netdev) > nfilters) अणु
		rx_mode |= IONIC_RX_MODE_F_ALLMULTI;
		lअगर->mc_overflow = true;
	पूर्ण अन्यथा अगर (lअगर->mc_overflow) अणु
		lअगर->mc_overflow = false;
		अगर (!(netdev->flags & IFF_ALLMULTI))
			rx_mode &= ~IONIC_RX_MODE_F_ALLMULTI;
	पूर्ण

	अगर (lअगर->rx_mode != rx_mode) अणु
		अगर (!can_sleep) अणु
			work = kzalloc(माप(*work), GFP_ATOMIC);
			अगर (!work) अणु
				netdev_err(lअगर->netdev, "rxmode change dropped\n");
				वापस;
			पूर्ण
			work->type = IONIC_DW_TYPE_RX_MODE;
			work->rx_mode = rx_mode;
			netdev_dbg(lअगर->netdev, "deferred: rx_mode\n");
			ionic_lअगर_deferred_enqueue(&lअगर->deferred, work);
		पूर्ण अन्यथा अणु
			ionic_lअगर_rx_mode(lअगर, rx_mode);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ionic_nकरो_set_rx_mode(काष्ठा net_device *netdev)
अणु
	ionic_set_rx_mode(netdev, CAN_NOT_SLEEP);
पूर्ण

अटल __le64 ionic_netdev_features_to_nic(netdev_features_t features)
अणु
	u64 wanted = 0;

	अगर (features & NETIF_F_HW_VLAN_CTAG_TX)
		wanted |= IONIC_ETH_HW_VLAN_TX_TAG;
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		wanted |= IONIC_ETH_HW_VLAN_RX_STRIP;
	अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER)
		wanted |= IONIC_ETH_HW_VLAN_RX_FILTER;
	अगर (features & NETIF_F_RXHASH)
		wanted |= IONIC_ETH_HW_RX_HASH;
	अगर (features & NETIF_F_RXCSUM)
		wanted |= IONIC_ETH_HW_RX_CSUM;
	अगर (features & NETIF_F_SG)
		wanted |= IONIC_ETH_HW_TX_SG;
	अगर (features & NETIF_F_HW_CSUM)
		wanted |= IONIC_ETH_HW_TX_CSUM;
	अगर (features & NETIF_F_TSO)
		wanted |= IONIC_ETH_HW_TSO;
	अगर (features & NETIF_F_TSO6)
		wanted |= IONIC_ETH_HW_TSO_IPV6;
	अगर (features & NETIF_F_TSO_ECN)
		wanted |= IONIC_ETH_HW_TSO_ECN;
	अगर (features & NETIF_F_GSO_GRE)
		wanted |= IONIC_ETH_HW_TSO_GRE;
	अगर (features & NETIF_F_GSO_GRE_CSUM)
		wanted |= IONIC_ETH_HW_TSO_GRE_CSUM;
	अगर (features & NETIF_F_GSO_IPXIP4)
		wanted |= IONIC_ETH_HW_TSO_IPXIP4;
	अगर (features & NETIF_F_GSO_IPXIP6)
		wanted |= IONIC_ETH_HW_TSO_IPXIP6;
	अगर (features & NETIF_F_GSO_UDP_TUNNEL)
		wanted |= IONIC_ETH_HW_TSO_UDP;
	अगर (features & NETIF_F_GSO_UDP_TUNNEL_CSUM)
		wanted |= IONIC_ETH_HW_TSO_UDP_CSUM;

	वापस cpu_to_le64(wanted);
पूर्ण

अटल पूर्णांक ionic_set_nic_features(काष्ठा ionic_lअगर *lअगर,
				  netdev_features_t features)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.lअगर_setattr = अणु
			.opcode = IONIC_CMD_LIF_SETATTR,
			.index = cpu_to_le16(lअगर->index),
			.attr = IONIC_LIF_ATTR_FEATURES,
		पूर्ण,
	पूर्ण;
	u64 vlan_flags = IONIC_ETH_HW_VLAN_TX_TAG |
			 IONIC_ETH_HW_VLAN_RX_STRIP |
			 IONIC_ETH_HW_VLAN_RX_FILTER;
	u64 old_hw_features;
	पूर्णांक err;

	ctx.cmd.lअगर_setattr.features = ionic_netdev_features_to_nic(features);

	अगर (lअगर->phc)
		ctx.cmd.lअगर_setattr.features |= cpu_to_le64(IONIC_ETH_HW_TIMESTAMP);

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		वापस err;

	old_hw_features = lअगर->hw_features;
	lअगर->hw_features = le64_to_cpu(ctx.cmd.lअगर_setattr.features &
				       ctx.comp.lअगर_setattr.features);

	अगर ((old_hw_features ^ lअगर->hw_features) & IONIC_ETH_HW_RX_HASH)
		ionic_lअगर_rss_config(lअगर, lअगर->rss_types, शून्य, शून्य);

	अगर ((vlan_flags & features) &&
	    !(vlan_flags & le64_to_cpu(ctx.comp.lअगर_setattr.features)))
		dev_info_once(lअगर->ionic->dev, "NIC is not supporting vlan offload, likely in SmartNIC mode\n");

	अगर (lअगर->hw_features & IONIC_ETH_HW_VLAN_TX_TAG)
		dev_dbg(dev, "feature ETH_HW_VLAN_TX_TAG\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_VLAN_RX_STRIP)
		dev_dbg(dev, "feature ETH_HW_VLAN_RX_STRIP\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_VLAN_RX_FILTER)
		dev_dbg(dev, "feature ETH_HW_VLAN_RX_FILTER\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_RX_HASH)
		dev_dbg(dev, "feature ETH_HW_RX_HASH\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TX_SG)
		dev_dbg(dev, "feature ETH_HW_TX_SG\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TX_CSUM)
		dev_dbg(dev, "feature ETH_HW_TX_CSUM\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_RX_CSUM)
		dev_dbg(dev, "feature ETH_HW_RX_CSUM\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO)
		dev_dbg(dev, "feature ETH_HW_TSO\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_IPV6)
		dev_dbg(dev, "feature ETH_HW_TSO_IPV6\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_ECN)
		dev_dbg(dev, "feature ETH_HW_TSO_ECN\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_GRE)
		dev_dbg(dev, "feature ETH_HW_TSO_GRE\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_GRE_CSUM)
		dev_dbg(dev, "feature ETH_HW_TSO_GRE_CSUM\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_IPXIP4)
		dev_dbg(dev, "feature ETH_HW_TSO_IPXIP4\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_IPXIP6)
		dev_dbg(dev, "feature ETH_HW_TSO_IPXIP6\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_UDP)
		dev_dbg(dev, "feature ETH_HW_TSO_UDP\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_UDP_CSUM)
		dev_dbg(dev, "feature ETH_HW_TSO_UDP_CSUM\n");
	अगर (lअगर->hw_features & IONIC_ETH_HW_TIMESTAMP)
		dev_dbg(dev, "feature ETH_HW_TIMESTAMP\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_init_nic_features(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा net_device *netdev = lअगर->netdev;
	netdev_features_t features;
	पूर्णांक err;

	/* set up what we expect to support by शेष */
	features = NETIF_F_HW_VLAN_CTAG_TX |
		   NETIF_F_HW_VLAN_CTAG_RX |
		   NETIF_F_HW_VLAN_CTAG_FILTER |
		   NETIF_F_RXHASH |
		   NETIF_F_SG |
		   NETIF_F_HW_CSUM |
		   NETIF_F_RXCSUM |
		   NETIF_F_TSO |
		   NETIF_F_TSO6 |
		   NETIF_F_TSO_ECN;

	err = ionic_set_nic_features(lअगर, features);
	अगर (err)
		वापस err;

	/* tell the netdev what we actually can support */
	netdev->features |= NETIF_F_HIGHDMA;

	अगर (lअगर->hw_features & IONIC_ETH_HW_VLAN_TX_TAG)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX;
	अगर (lअगर->hw_features & IONIC_ETH_HW_VLAN_RX_STRIP)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX;
	अगर (lअगर->hw_features & IONIC_ETH_HW_VLAN_RX_FILTER)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	अगर (lअगर->hw_features & IONIC_ETH_HW_RX_HASH)
		netdev->hw_features |= NETIF_F_RXHASH;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TX_SG)
		netdev->hw_features |= NETIF_F_SG;

	अगर (lअगर->hw_features & IONIC_ETH_HW_TX_CSUM)
		netdev->hw_enc_features |= NETIF_F_HW_CSUM;
	अगर (lअगर->hw_features & IONIC_ETH_HW_RX_CSUM)
		netdev->hw_enc_features |= NETIF_F_RXCSUM;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO)
		netdev->hw_enc_features |= NETIF_F_TSO;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_IPV6)
		netdev->hw_enc_features |= NETIF_F_TSO6;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_ECN)
		netdev->hw_enc_features |= NETIF_F_TSO_ECN;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_GRE)
		netdev->hw_enc_features |= NETIF_F_GSO_GRE;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_GRE_CSUM)
		netdev->hw_enc_features |= NETIF_F_GSO_GRE_CSUM;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_IPXIP4)
		netdev->hw_enc_features |= NETIF_F_GSO_IPXIP4;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_IPXIP6)
		netdev->hw_enc_features |= NETIF_F_GSO_IPXIP6;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_UDP)
		netdev->hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL;
	अगर (lअगर->hw_features & IONIC_ETH_HW_TSO_UDP_CSUM)
		netdev->hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;

	netdev->hw_features |= netdev->hw_enc_features;
	netdev->features |= netdev->hw_features;
	netdev->vlan_features |= netdev->features & ~NETIF_F_VLAN_FEATURES;

	netdev->priv_flags |= IFF_UNICAST_FLT |
			      IFF_LIVE_ADDR_CHANGE;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_set_features(काष्ठा net_device *netdev,
			      netdev_features_t features)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	पूर्णांक err;

	netdev_dbg(netdev, "%s: lif->features=0x%08llx new_features=0x%08llx\n",
		   __func__, (u64)lअगर->netdev->features, (u64)features);

	err = ionic_set_nic_features(lअगर, features);

	वापस err;
पूर्ण

अटल पूर्णांक ionic_set_mac_address(काष्ठा net_device *netdev, व्योम *sa)
अणु
	काष्ठा sockaddr *addr = sa;
	u8 *mac;
	पूर्णांक err;

	mac = (u8 *)addr->sa_data;
	अगर (ether_addr_equal(netdev->dev_addr, mac))
		वापस 0;

	err = eth_prepare_mac_addr_change(netdev, addr);
	अगर (err)
		वापस err;

	अगर (!is_zero_ether_addr(netdev->dev_addr)) अणु
		netdev_info(netdev, "deleting mac addr %pM\n",
			    netdev->dev_addr);
		ionic_addr_del(netdev, netdev->dev_addr);
	पूर्ण

	eth_commit_mac_addr_change(netdev, addr);
	netdev_info(netdev, "updating mac addr %pM\n", mac);

	वापस ionic_addr_add(netdev, mac);
पूर्ण

अटल व्योम ionic_stop_queues_reconfig(काष्ठा ionic_lअगर *lअगर)
अणु
	/* Stop and clean the queues beक्रमe reconfiguration */
	mutex_lock(&lअगर->queue_lock);
	netअगर_device_detach(lअगर->netdev);
	ionic_stop_queues(lअगर);
	ionic_txrx_deinit(lअगर);
पूर्ण

अटल पूर्णांक ionic_start_queues_reconfig(काष्ठा ionic_lअगर *lअगर)
अणु
	पूर्णांक err;

	/* Re-init the queues after reconfiguration */

	/* The only way txrx_init can fail here is अगर communication
	 * with FW is suddenly broken.  There's not much we can करो
	 * at this poपूर्णांक - error messages have alपढ़ोy been prपूर्णांकed,
	 * so we can जारी on and the user can eventually करो a
	 * DOWN and UP to try to reset and clear the issue.
	 */
	err = ionic_txrx_init(lअगर);
	mutex_unlock(&lअगर->queue_lock);
	ionic_link_status_check_request(lअगर, CAN_SLEEP);
	netअगर_device_attach(lअगर->netdev);

	वापस err;
पूर्ण

अटल पूर्णांक ionic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.lअगर_setattr = अणु
			.opcode = IONIC_CMD_LIF_SETATTR,
			.index = cpu_to_le16(lअगर->index),
			.attr = IONIC_LIF_ATTR_MTU,
			.mtu = cpu_to_le32(new_mtu),
		पूर्ण,
	पूर्ण;
	पूर्णांक err;

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		वापस err;

	/* अगर we're not running, nothing more to करो */
	अगर (!netअगर_running(netdev)) अणु
		netdev->mtu = new_mtu;
		वापस 0;
	पूर्ण

	ionic_stop_queues_reconfig(lअगर);
	netdev->mtu = new_mtu;
	वापस ionic_start_queues_reconfig(lअगर);
पूर्ण

अटल व्योम ionic_tx_समयout_work(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा ionic_lअगर *lअगर = container_of(ws, काष्ठा ionic_lअगर, tx_समयout_work);

	अगर (test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
		वापस;

	/* अगर we were stopped beक्रमe this scheduled job was launched,
	 * करोn't bother the queues as they are alपढ़ोy stopped.
	 */
	अगर (!netअगर_running(lअगर->netdev))
		वापस;

	ionic_stop_queues_reconfig(lअगर);
	ionic_start_queues_reconfig(lअगर);
पूर्ण

अटल व्योम ionic_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	netdev_info(lअगर->netdev, "Tx Timeout triggered - txq %d\n", txqueue);
	schedule_work(&lअगर->tx_समयout_work);
पूर्ण

अटल पूर्णांक ionic_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto,
				 u16 vid)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.rx_filter_add = अणु
			.opcode = IONIC_CMD_RX_FILTER_ADD,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.match = cpu_to_le16(IONIC_RX_FILTER_MATCH_VLAN),
			.vlan.vlan = cpu_to_le16(vid),
		पूर्ण,
	पूर्ण;
	पूर्णांक err;

	netdev_dbg(netdev, "rx_filter add VLAN %d\n", vid);
	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		वापस err;

	वापस ionic_rx_filter_save(lअगर, 0, IONIC_RXQ_INDEX_ANY, 0, &ctx);
पूर्ण

अटल पूर्णांक ionic_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto,
				  u16 vid)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.rx_filter_del = अणु
			.opcode = IONIC_CMD_RX_FILTER_DEL,
			.lअगर_index = cpu_to_le16(lअगर->index),
		पूर्ण,
	पूर्ण;
	काष्ठा ionic_rx_filter *f;

	spin_lock_bh(&lअगर->rx_filters.lock);

	f = ionic_rx_filter_by_vlan(lअगर, vid);
	अगर (!f) अणु
		spin_unlock_bh(&lअगर->rx_filters.lock);
		वापस -ENOENT;
	पूर्ण

	netdev_dbg(netdev, "rx_filter del VLAN %d (id %d)\n",
		   vid, f->filter_id);

	ctx.cmd.rx_filter_del.filter_id = cpu_to_le32(f->filter_id);
	ionic_rx_filter_मुक्त(lअगर, f);
	spin_unlock_bh(&lअगर->rx_filters.lock);

	वापस ionic_adminq_post_रुको(lअगर, &ctx);
पूर्ण

पूर्णांक ionic_lअगर_rss_config(काष्ठा ionic_lअगर *lअगर, स्थिर u16 types,
			 स्थिर u8 *key, स्थिर u32 *indir)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.lअगर_setattr = अणु
			.opcode = IONIC_CMD_LIF_SETATTR,
			.attr = IONIC_LIF_ATTR_RSS,
			.rss.addr = cpu_to_le64(lअगर->rss_ind_tbl_pa),
		पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i, tbl_sz;

	अगर (lअगर->hw_features & IONIC_ETH_HW_RX_HASH) अणु
		lअगर->rss_types = types;
		ctx.cmd.lअगर_setattr.rss.types = cpu_to_le16(types);
	पूर्ण

	अगर (key)
		स_नकल(lअगर->rss_hash_key, key, IONIC_RSS_HASH_KEY_SIZE);

	अगर (indir) अणु
		tbl_sz = le16_to_cpu(lअगर->ionic->ident.lअगर.eth.rss_ind_tbl_sz);
		क्रम (i = 0; i < tbl_sz; i++)
			lअगर->rss_ind_tbl[i] = indir[i];
	पूर्ण

	स_नकल(ctx.cmd.lअगर_setattr.rss.key, lअगर->rss_hash_key,
	       IONIC_RSS_HASH_KEY_SIZE);

	वापस ionic_adminq_post_रुको(lअगर, &ctx);
पूर्ण

अटल पूर्णांक ionic_lअगर_rss_init(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक tbl_sz;
	अचिन्हित पूर्णांक i;

	lअगर->rss_types = IONIC_RSS_TYPE_IPV4     |
			 IONIC_RSS_TYPE_IPV4_TCP |
			 IONIC_RSS_TYPE_IPV4_UDP |
			 IONIC_RSS_TYPE_IPV6     |
			 IONIC_RSS_TYPE_IPV6_TCP |
			 IONIC_RSS_TYPE_IPV6_UDP;

	/* Fill indirection table with 'default' values */
	tbl_sz = le16_to_cpu(lअगर->ionic->ident.lअगर.eth.rss_ind_tbl_sz);
	क्रम (i = 0; i < tbl_sz; i++)
		lअगर->rss_ind_tbl[i] = ethtool_rxfh_indir_शेष(i, lअगर->nxqs);

	वापस ionic_lअगर_rss_config(lअगर, lअगर->rss_types, शून्य, शून्य);
पूर्ण

अटल व्योम ionic_lअगर_rss_deinit(काष्ठा ionic_lअगर *lअगर)
अणु
	पूर्णांक tbl_sz;

	tbl_sz = le16_to_cpu(lअगर->ionic->ident.lअगर.eth.rss_ind_tbl_sz);
	स_रखो(lअगर->rss_ind_tbl, 0, tbl_sz);
	स_रखो(lअगर->rss_hash_key, 0, IONIC_RSS_HASH_KEY_SIZE);

	ionic_lअगर_rss_config(lअगर, 0x0, शून्य, शून्य);
पूर्ण

अटल व्योम ionic_lअगर_quiesce(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.lअगर_setattr = अणु
			.opcode = IONIC_CMD_LIF_SETATTR,
			.index = cpu_to_le16(lअगर->index),
			.attr = IONIC_LIF_ATTR_STATE,
			.state = IONIC_LIF_QUIESCE,
		पूर्ण,
	पूर्ण;
	पूर्णांक err;

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		netdev_err(lअगर->netdev, "lif quiesce failed %d\n", err);
पूर्ण

अटल व्योम ionic_txrx_disable(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	अगर (lअगर->txqcqs) अणु
		क्रम (i = 0; i < lअगर->nxqs; i++)
			err = ionic_qcq_disable(lअगर->txqcqs[i], (err != -ETIMEDOUT));
	पूर्ण

	अगर (lअगर->hwstamp_txq)
		err = ionic_qcq_disable(lअगर->hwstamp_txq, (err != -ETIMEDOUT));

	अगर (lअगर->rxqcqs) अणु
		क्रम (i = 0; i < lअगर->nxqs; i++)
			err = ionic_qcq_disable(lअगर->rxqcqs[i], (err != -ETIMEDOUT));
	पूर्ण

	अगर (lअगर->hwstamp_rxq)
		err = ionic_qcq_disable(lअगर->hwstamp_rxq, (err != -ETIMEDOUT));

	ionic_lअगर_quiesce(lअगर);
पूर्ण

अटल व्योम ionic_txrx_deinit(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक i;

	अगर (lअगर->txqcqs) अणु
		क्रम (i = 0; i < lअगर->nxqs && lअगर->txqcqs[i]; i++) अणु
			ionic_lअगर_qcq_deinit(lअगर, lअगर->txqcqs[i]);
			ionic_tx_flush(&lअगर->txqcqs[i]->cq);
			ionic_tx_empty(&lअगर->txqcqs[i]->q);
		पूर्ण
	पूर्ण

	अगर (lअगर->rxqcqs) अणु
		क्रम (i = 0; i < lअगर->nxqs && lअगर->rxqcqs[i]; i++) अणु
			ionic_lअगर_qcq_deinit(lअगर, lअगर->rxqcqs[i]);
			ionic_rx_empty(&lअगर->rxqcqs[i]->q);
		पूर्ण
	पूर्ण
	lअगर->rx_mode = 0;

	अगर (lअगर->hwstamp_txq) अणु
		ionic_lअगर_qcq_deinit(lअगर, lअगर->hwstamp_txq);
		ionic_tx_flush(&lअगर->hwstamp_txq->cq);
		ionic_tx_empty(&lअगर->hwstamp_txq->q);
	पूर्ण

	अगर (lअगर->hwstamp_rxq) अणु
		ionic_lअगर_qcq_deinit(lअगर, lअगर->hwstamp_rxq);
		ionic_rx_empty(&lअगर->hwstamp_rxq->q);
	पूर्ण
पूर्ण

अटल व्योम ionic_txrx_मुक्त(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक i;

	अगर (lअगर->txqcqs) अणु
		क्रम (i = 0; i < lअगर->ionic->ntxqs_per_lअगर && lअगर->txqcqs[i]; i++) अणु
			ionic_qcq_मुक्त(lअगर, lअगर->txqcqs[i]);
			devm_kमुक्त(lअगर->ionic->dev, lअगर->txqcqs[i]);
			lअगर->txqcqs[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (lअगर->rxqcqs) अणु
		क्रम (i = 0; i < lअगर->ionic->nrxqs_per_lअगर && lअगर->rxqcqs[i]; i++) अणु
			ionic_qcq_मुक्त(lअगर, lअगर->rxqcqs[i]);
			devm_kमुक्त(lअगर->ionic->dev, lअगर->rxqcqs[i]);
			lअगर->rxqcqs[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (lअगर->hwstamp_txq) अणु
		ionic_qcq_मुक्त(lअगर, lअगर->hwstamp_txq);
		devm_kमुक्त(lअगर->ionic->dev, lअगर->hwstamp_txq);
		lअगर->hwstamp_txq = शून्य;
	पूर्ण

	अगर (lअगर->hwstamp_rxq) अणु
		ionic_qcq_मुक्त(lअगर, lअगर->hwstamp_rxq);
		devm_kमुक्त(lअगर->ionic->dev, lअगर->hwstamp_rxq);
		lअगर->hwstamp_rxq = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ionic_txrx_alloc(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक comp_sz, desc_sz, num_desc, sg_desc_sz;
	अचिन्हित पूर्णांक flags, i;
	पूर्णांक err = 0;

	num_desc = lअगर->ntxq_descs;
	desc_sz = माप(काष्ठा ionic_txq_desc);
	comp_sz = माप(काष्ठा ionic_txq_comp);

	अगर (lअगर->qtype_info[IONIC_QTYPE_TXQ].version >= 1 &&
	    lअगर->qtype_info[IONIC_QTYPE_TXQ].sg_desc_sz ==
					  माप(काष्ठा ionic_txq_sg_desc_v1))
		sg_desc_sz = माप(काष्ठा ionic_txq_sg_desc_v1);
	अन्यथा
		sg_desc_sz = माप(काष्ठा ionic_txq_sg_desc);

	flags = IONIC_QCQ_F_TX_STATS | IONIC_QCQ_F_SG;
	अगर (test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
		flags |= IONIC_QCQ_F_INTR;
	क्रम (i = 0; i < lअगर->nxqs; i++) अणु
		err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_TXQ, i, "tx", flags,
				      num_desc, desc_sz, comp_sz, sg_desc_sz,
				      lअगर->kern_pid, &lअगर->txqcqs[i]);
		अगर (err)
			जाओ err_out;

		अगर (flags & IONIC_QCQ_F_INTR) अणु
			ionic_पूर्णांकr_coal_init(lअगर->ionic->idev.पूर्णांकr_ctrl,
					     lअगर->txqcqs[i]->पूर्णांकr.index,
					     lअगर->tx_coalesce_hw);
			अगर (test_bit(IONIC_LIF_F_TX_DIM_INTR, lअगर->state))
				lअगर->txqcqs[i]->पूर्णांकr.dim_coal_hw = lअगर->tx_coalesce_hw;
		पूर्ण

		ionic_debugfs_add_qcq(lअगर, lअगर->txqcqs[i]);
	पूर्ण

	flags = IONIC_QCQ_F_RX_STATS | IONIC_QCQ_F_SG | IONIC_QCQ_F_INTR;

	num_desc = lअगर->nrxq_descs;
	desc_sz = माप(काष्ठा ionic_rxq_desc);
	comp_sz = माप(काष्ठा ionic_rxq_comp);
	sg_desc_sz = माप(काष्ठा ionic_rxq_sg_desc);

	अगर (lअगर->rxq_features & IONIC_Q_F_2X_CQ_DESC)
		comp_sz *= 2;

	क्रम (i = 0; i < lअगर->nxqs; i++) अणु
		err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_RXQ, i, "rx", flags,
				      num_desc, desc_sz, comp_sz, sg_desc_sz,
				      lअगर->kern_pid, &lअगर->rxqcqs[i]);
		अगर (err)
			जाओ err_out;

		lअगर->rxqcqs[i]->q.features = lअगर->rxq_features;

		ionic_पूर्णांकr_coal_init(lअगर->ionic->idev.पूर्णांकr_ctrl,
				     lअगर->rxqcqs[i]->पूर्णांकr.index,
				     lअगर->rx_coalesce_hw);
		अगर (test_bit(IONIC_LIF_F_RX_DIM_INTR, lअगर->state))
			lअगर->rxqcqs[i]->पूर्णांकr.dim_coal_hw = lअगर->rx_coalesce_hw;

		अगर (!test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
			ionic_link_qcq_पूर्णांकerrupts(lअगर->rxqcqs[i],
						  lअगर->txqcqs[i]);

		ionic_debugfs_add_qcq(lअगर, lअगर->rxqcqs[i]);
	पूर्ण

	वापस 0;

err_out:
	ionic_txrx_मुक्त(lअगर);

	वापस err;
पूर्ण

अटल पूर्णांक ionic_txrx_init(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < lअगर->nxqs; i++) अणु
		err = ionic_lअगर_txq_init(lअगर, lअगर->txqcqs[i]);
		अगर (err)
			जाओ err_out;

		err = ionic_lअगर_rxq_init(lअगर, lअगर->rxqcqs[i]);
		अगर (err) अणु
			ionic_lअगर_qcq_deinit(lअगर, lअगर->txqcqs[i]);
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (lअगर->netdev->features & NETIF_F_RXHASH)
		ionic_lअगर_rss_init(lअगर);

	ionic_set_rx_mode(lअगर->netdev, CAN_SLEEP);

	वापस 0;

err_out:
	जबतक (i--) अणु
		ionic_lअगर_qcq_deinit(lअगर, lअगर->txqcqs[i]);
		ionic_lअगर_qcq_deinit(lअगर, lअगर->rxqcqs[i]);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ionic_txrx_enable(काष्ठा ionic_lअगर *lअगर)
अणु
	पूर्णांक derr = 0;
	पूर्णांक i, err;

	क्रम (i = 0; i < lअगर->nxqs; i++) अणु
		अगर (!(lअगर->rxqcqs[i] && lअगर->txqcqs[i])) अणु
			dev_err(lअगर->ionic->dev, "%s: bad qcq %d\n", __func__, i);
			err = -ENXIO;
			जाओ err_out;
		पूर्ण

		ionic_rx_fill(&lअगर->rxqcqs[i]->q);
		err = ionic_qcq_enable(lअगर->rxqcqs[i]);
		अगर (err)
			जाओ err_out;

		err = ionic_qcq_enable(lअगर->txqcqs[i]);
		अगर (err) अणु
			derr = ionic_qcq_disable(lअगर->rxqcqs[i], (err != -ETIMEDOUT));
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (lअगर->hwstamp_rxq) अणु
		ionic_rx_fill(&lअगर->hwstamp_rxq->q);
		err = ionic_qcq_enable(lअगर->hwstamp_rxq);
		अगर (err)
			जाओ err_out_hwstamp_rx;
	पूर्ण

	अगर (lअगर->hwstamp_txq) अणु
		err = ionic_qcq_enable(lअगर->hwstamp_txq);
		अगर (err)
			जाओ err_out_hwstamp_tx;
	पूर्ण

	वापस 0;

err_out_hwstamp_tx:
	अगर (lअगर->hwstamp_rxq)
		derr = ionic_qcq_disable(lअगर->hwstamp_rxq, (derr != -ETIMEDOUT));
err_out_hwstamp_rx:
	i = lअगर->nxqs;
err_out:
	जबतक (i--) अणु
		derr = ionic_qcq_disable(lअगर->txqcqs[i], (derr != -ETIMEDOUT));
		derr = ionic_qcq_disable(lअगर->rxqcqs[i], (derr != -ETIMEDOUT));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ionic_start_queues(काष्ठा ionic_lअगर *lअगर)
अणु
	पूर्णांक err;

	अगर (test_bit(IONIC_LIF_F_BROKEN, lअगर->state))
		वापस -EIO;

	अगर (test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
		वापस -EBUSY;

	अगर (test_and_set_bit(IONIC_LIF_F_UP, lअगर->state))
		वापस 0;

	err = ionic_txrx_enable(lअगर);
	अगर (err) अणु
		clear_bit(IONIC_LIF_F_UP, lअगर->state);
		वापस err;
	पूर्ण
	netअगर_tx_wake_all_queues(lअगर->netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	पूर्णांक err;

	/* If recovering from a broken state, clear the bit and we'll try again */
	अगर (test_and_clear_bit(IONIC_LIF_F_BROKEN, lअगर->state))
		netdev_info(netdev, "clearing broken state\n");

	err = ionic_txrx_alloc(lअगर);
	अगर (err)
		वापस err;

	err = ionic_txrx_init(lअगर);
	अगर (err)
		जाओ err_txrx_मुक्त;

	err = netअगर_set_real_num_tx_queues(netdev, lअगर->nxqs);
	अगर (err)
		जाओ err_txrx_deinit;

	err = netअगर_set_real_num_rx_queues(netdev, lअगर->nxqs);
	अगर (err)
		जाओ err_txrx_deinit;

	/* करोn't start the queues until we have link */
	अगर (netअगर_carrier_ok(netdev)) अणु
		err = ionic_start_queues(lअगर);
		अगर (err)
			जाओ err_txrx_deinit;
	पूर्ण

	वापस 0;

err_txrx_deinit:
	ionic_txrx_deinit(lअगर);
err_txrx_मुक्त:
	ionic_txrx_मुक्त(lअगर);
	वापस err;
पूर्ण

अटल व्योम ionic_stop_queues(काष्ठा ionic_lअगर *lअगर)
अणु
	अगर (!test_and_clear_bit(IONIC_LIF_F_UP, lअगर->state))
		वापस;

	netअगर_tx_disable(lअगर->netdev);
	ionic_txrx_disable(lअगर);
पूर्ण

अटल पूर्णांक ionic_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	अगर (test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
		वापस 0;

	ionic_stop_queues(lअगर);
	ionic_txrx_deinit(lअगर);
	ionic_txrx_मुक्त(lअगर);

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_करो_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस ionic_lअगर_hwstamp_set(lअगर, अगरr);
	हाल SIOCGHWTSTAMP:
		वापस ionic_lअगर_hwstamp_get(lअगर, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ionic_get_vf_config(काष्ठा net_device *netdev,
			       पूर्णांक vf, काष्ठा अगरla_vf_info *ivf)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक ret = 0;

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_पढ़ो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ivf->vf           = vf;
		ivf->vlan         = le16_to_cpu(ionic->vfs[vf].vlanid);
		ivf->qos	  = 0;
		ivf->spoofchk     = ionic->vfs[vf].spoofchk;
		ivf->linkstate    = ionic->vfs[vf].linkstate;
		ivf->max_tx_rate  = le32_to_cpu(ionic->vfs[vf].maxrate);
		ivf->trusted      = ionic->vfs[vf].trusted;
		ether_addr_copy(ivf->mac, ionic->vfs[vf].macaddr);
	पूर्ण

	up_पढ़ो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_get_vf_stats(काष्ठा net_device *netdev, पूर्णांक vf,
			      काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	काष्ठा ionic_lअगर_stats *vs;
	पूर्णांक ret = 0;

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_पढ़ो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		स_रखो(vf_stats, 0, माप(*vf_stats));
		vs = &ionic->vfs[vf].stats;

		vf_stats->rx_packets = le64_to_cpu(vs->rx_ucast_packets);
		vf_stats->tx_packets = le64_to_cpu(vs->tx_ucast_packets);
		vf_stats->rx_bytes   = le64_to_cpu(vs->rx_ucast_bytes);
		vf_stats->tx_bytes   = le64_to_cpu(vs->tx_ucast_bytes);
		vf_stats->broadcast  = le64_to_cpu(vs->rx_bcast_packets);
		vf_stats->multicast  = le64_to_cpu(vs->rx_mcast_packets);
		vf_stats->rx_dropped = le64_to_cpu(vs->rx_ucast_drop_packets) +
				       le64_to_cpu(vs->rx_mcast_drop_packets) +
				       le64_to_cpu(vs->rx_bcast_drop_packets);
		vf_stats->tx_dropped = le64_to_cpu(vs->tx_ucast_drop_packets) +
				       le64_to_cpu(vs->tx_mcast_drop_packets) +
				       le64_to_cpu(vs->tx_bcast_drop_packets);
	पूर्ण

	up_पढ़ो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक ret;

	अगर (!(is_zero_ether_addr(mac) || is_valid_ether_addr(mac)))
		वापस -EINVAL;

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_ग_लिखो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = ionic_set_vf_config(ionic, vf, IONIC_VF_ATTR_MAC, mac);
		अगर (!ret)
			ether_addr_copy(ionic->vfs[vf].macaddr, mac);
	पूर्ण

	up_ग_लिखो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan,
			     u8 qos, __be16 proto)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक ret;

	/* until someday when we support qos */
	अगर (qos)
		वापस -EINVAL;

	अगर (vlan > 4095)
		वापस -EINVAL;

	अगर (proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_ग_लिखो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = ionic_set_vf_config(ionic, vf,
					  IONIC_VF_ATTR_VLAN, (u8 *)&vlan);
		अगर (!ret)
			ionic->vfs[vf].vlanid = cpu_to_le16(vlan);
	पूर्ण

	up_ग_लिखो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_set_vf_rate(काष्ठा net_device *netdev, पूर्णांक vf,
			     पूर्णांक tx_min, पूर्णांक tx_max)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक ret;

	/* setting the min just seems silly */
	अगर (tx_min)
		वापस -EINVAL;

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_ग_लिखो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = ionic_set_vf_config(ionic, vf,
					  IONIC_VF_ATTR_RATE, (u8 *)&tx_max);
		अगर (!ret)
			lअगर->ionic->vfs[vf].maxrate = cpu_to_le32(tx_max);
	पूर्ण

	up_ग_लिखो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool set)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	u8 data = set;  /* convert to u8 क्रम config */
	पूर्णांक ret;

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_ग_लिखो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = ionic_set_vf_config(ionic, vf,
					  IONIC_VF_ATTR_SPOOFCHK, &data);
		अगर (!ret)
			ionic->vfs[vf].spoofchk = data;
	पूर्ण

	up_ग_लिखो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool set)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	u8 data = set;  /* convert to u8 क्रम config */
	पूर्णांक ret;

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_ग_लिखो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = ionic_set_vf_config(ionic, vf,
					  IONIC_VF_ATTR_TRUST, &data);
		अगर (!ret)
			ionic->vfs[vf].trusted = data;
	पूर्ण

	up_ग_लिखो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ionic_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf, पूर्णांक set)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	u8 data;
	पूर्णांक ret;

	चयन (set) अणु
	हाल IFLA_VF_LINK_STATE_ENABLE:
		data = IONIC_VF_LINK_STATUS_UP;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_DISABLE:
		data = IONIC_VF_LINK_STATUS_DOWN;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_AUTO:
		data = IONIC_VF_LINK_STATUS_AUTO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!netअगर_device_present(netdev))
		वापस -EBUSY;

	करोwn_ग_लिखो(&ionic->vf_op_lock);

	अगर (vf >= pci_num_vf(ionic->pdev) || !ionic->vfs) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = ionic_set_vf_config(ionic, vf,
					  IONIC_VF_ATTR_LINKSTATE, &data);
		अगर (!ret)
			ionic->vfs[vf].linkstate = set;
	पूर्ण

	up_ग_लिखो(&ionic->vf_op_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ionic_netdev_ops = अणु
	.nकरो_खोलो               = ionic_खोलो,
	.nकरो_stop               = ionic_stop,
	.nकरो_करो_ioctl		= ionic_करो_ioctl,
	.nकरो_start_xmit		= ionic_start_xmit,
	.nकरो_get_stats64	= ionic_get_stats64,
	.nकरो_set_rx_mode	= ionic_nकरो_set_rx_mode,
	.nकरो_set_features	= ionic_set_features,
	.nकरो_set_mac_address	= ionic_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout         = ionic_tx_समयout,
	.nकरो_change_mtu         = ionic_change_mtu,
	.nकरो_vlan_rx_add_vid    = ionic_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid   = ionic_vlan_rx_समाप्त_vid,
	.nकरो_set_vf_vlan	= ionic_set_vf_vlan,
	.nकरो_set_vf_trust	= ionic_set_vf_trust,
	.nकरो_set_vf_mac		= ionic_set_vf_mac,
	.nकरो_set_vf_rate	= ionic_set_vf_rate,
	.nकरो_set_vf_spoofchk	= ionic_set_vf_spoofchk,
	.nकरो_get_vf_config	= ionic_get_vf_config,
	.nकरो_set_vf_link_state	= ionic_set_vf_link_state,
	.nकरो_get_vf_stats       = ionic_get_vf_stats,
पूर्ण;

अटल व्योम ionic_swap_queues(काष्ठा ionic_qcq *a, काष्ठा ionic_qcq *b)
अणु
	/* only swapping the queues, not the napi, flags, or other stuff */
	swap(a->q.features,   b->q.features);
	swap(a->q.num_descs,  b->q.num_descs);
	swap(a->q.desc_size,  b->q.desc_size);
	swap(a->q.base,       b->q.base);
	swap(a->q.base_pa,    b->q.base_pa);
	swap(a->q.info,       b->q.info);
	swap(a->q_base,       b->q_base);
	swap(a->q_base_pa,    b->q_base_pa);
	swap(a->q_size,       b->q_size);

	swap(a->q.sg_desc_size, b->q.sg_desc_size);
	swap(a->q.sg_base,    b->q.sg_base);
	swap(a->q.sg_base_pa, b->q.sg_base_pa);
	swap(a->sg_base,      b->sg_base);
	swap(a->sg_base_pa,   b->sg_base_pa);
	swap(a->sg_size,      b->sg_size);

	swap(a->cq.num_descs, b->cq.num_descs);
	swap(a->cq.desc_size, b->cq.desc_size);
	swap(a->cq.base,      b->cq.base);
	swap(a->cq.base_pa,   b->cq.base_pa);
	swap(a->cq.info,      b->cq.info);
	swap(a->cq_base,      b->cq_base);
	swap(a->cq_base_pa,   b->cq_base_pa);
	swap(a->cq_size,      b->cq_size);

	ionic_debugfs_del_qcq(a);
	ionic_debugfs_add_qcq(a->q.lअगर, a);
पूर्ण

पूर्णांक ionic_reconfigure_queues(काष्ठा ionic_lअगर *lअगर,
			     काष्ठा ionic_queue_params *qparam)
अणु
	अचिन्हित पूर्णांक comp_sz, desc_sz, num_desc, sg_desc_sz;
	काष्ठा ionic_qcq **tx_qcqs = शून्य;
	काष्ठा ionic_qcq **rx_qcqs = शून्य;
	अचिन्हित पूर्णांक flags, i;
	पूर्णांक err = -ENOMEM;

	/* allocate temporary qcq arrays to hold new queue काष्ठाs */
	अगर (qparam->nxqs != lअगर->nxqs || qparam->ntxq_descs != lअगर->ntxq_descs) अणु
		tx_qcqs = devm_kसुस्मृति(lअगर->ionic->dev, lअगर->ionic->ntxqs_per_lअगर,
				       माप(काष्ठा ionic_qcq *), GFP_KERNEL);
		अगर (!tx_qcqs)
			जाओ err_out;
	पूर्ण
	अगर (qparam->nxqs != lअगर->nxqs ||
	    qparam->nrxq_descs != lअगर->nrxq_descs ||
	    qparam->rxq_features != lअगर->rxq_features) अणु
		rx_qcqs = devm_kसुस्मृति(lअगर->ionic->dev, lअगर->ionic->nrxqs_per_lअगर,
				       माप(काष्ठा ionic_qcq *), GFP_KERNEL);
		अगर (!rx_qcqs)
			जाओ err_out;
	पूर्ण

	/* allocate new desc_info and rings, but leave the पूर्णांकerrupt setup
	 * until later so as to not mess with the still-running queues
	 */
	अगर (tx_qcqs) अणु
		num_desc = qparam->ntxq_descs;
		desc_sz = माप(काष्ठा ionic_txq_desc);
		comp_sz = माप(काष्ठा ionic_txq_comp);

		अगर (lअगर->qtype_info[IONIC_QTYPE_TXQ].version >= 1 &&
		    lअगर->qtype_info[IONIC_QTYPE_TXQ].sg_desc_sz ==
		    माप(काष्ठा ionic_txq_sg_desc_v1))
			sg_desc_sz = माप(काष्ठा ionic_txq_sg_desc_v1);
		अन्यथा
			sg_desc_sz = माप(काष्ठा ionic_txq_sg_desc);

		क्रम (i = 0; i < qparam->nxqs; i++) अणु
			flags = lअगर->txqcqs[i]->flags & ~IONIC_QCQ_F_INTR;
			err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_TXQ, i, "tx", flags,
					      num_desc, desc_sz, comp_sz, sg_desc_sz,
					      lअगर->kern_pid, &tx_qcqs[i]);
			अगर (err)
				जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (rx_qcqs) अणु
		num_desc = qparam->nrxq_descs;
		desc_sz = माप(काष्ठा ionic_rxq_desc);
		comp_sz = माप(काष्ठा ionic_rxq_comp);
		sg_desc_sz = माप(काष्ठा ionic_rxq_sg_desc);

		अगर (qparam->rxq_features & IONIC_Q_F_2X_CQ_DESC)
			comp_sz *= 2;

		क्रम (i = 0; i < qparam->nxqs; i++) अणु
			flags = lअगर->rxqcqs[i]->flags & ~IONIC_QCQ_F_INTR;
			err = ionic_qcq_alloc(lअगर, IONIC_QTYPE_RXQ, i, "rx", flags,
					      num_desc, desc_sz, comp_sz, sg_desc_sz,
					      lअगर->kern_pid, &rx_qcqs[i]);
			अगर (err)
				जाओ err_out;

			rx_qcqs[i]->q.features = qparam->rxq_features;
		पूर्ण
	पूर्ण

	/* stop and clean the queues */
	ionic_stop_queues_reconfig(lअगर);

	अगर (qparam->nxqs != lअगर->nxqs) अणु
		err = netअगर_set_real_num_tx_queues(lअगर->netdev, qparam->nxqs);
		अगर (err)
			जाओ err_out_reinit_unlock;
		err = netअगर_set_real_num_rx_queues(lअगर->netdev, qparam->nxqs);
		अगर (err) अणु
			netअगर_set_real_num_tx_queues(lअगर->netdev, lअगर->nxqs);
			जाओ err_out_reinit_unlock;
		पूर्ण
	पूर्ण

	/* swap new desc_info and rings, keeping existing पूर्णांकerrupt config */
	अगर (tx_qcqs) अणु
		lअगर->ntxq_descs = qparam->ntxq_descs;
		क्रम (i = 0; i < qparam->nxqs; i++)
			ionic_swap_queues(lअगर->txqcqs[i], tx_qcqs[i]);
	पूर्ण

	अगर (rx_qcqs) अणु
		lअगर->nrxq_descs = qparam->nrxq_descs;
		क्रम (i = 0; i < qparam->nxqs; i++)
			ionic_swap_queues(lअगर->rxqcqs[i], rx_qcqs[i]);
	पूर्ण

	/* अगर we need to change the पूर्णांकerrupt layout, this is the समय */
	अगर (qparam->पूर्णांकr_split != test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state) ||
	    qparam->nxqs != lअगर->nxqs) अणु
		अगर (qparam->पूर्णांकr_split) अणु
			set_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state);
		पूर्ण अन्यथा अणु
			clear_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state);
			lअगर->tx_coalesce_usecs = lअगर->rx_coalesce_usecs;
			lअगर->tx_coalesce_hw = lअगर->rx_coalesce_hw;
		पूर्ण

		/* clear existing पूर्णांकerrupt assignments */
		क्रम (i = 0; i < lअगर->ionic->ntxqs_per_lअगर; i++) अणु
			ionic_qcq_पूर्णांकr_मुक्त(lअगर, lअगर->txqcqs[i]);
			ionic_qcq_पूर्णांकr_मुक्त(lअगर, lअगर->rxqcqs[i]);
		पूर्ण

		/* re-assign the पूर्णांकerrupts */
		क्रम (i = 0; i < qparam->nxqs; i++) अणु
			lअगर->rxqcqs[i]->flags |= IONIC_QCQ_F_INTR;
			err = ionic_alloc_qcq_पूर्णांकerrupt(lअगर, lअगर->rxqcqs[i]);
			ionic_पूर्णांकr_coal_init(lअगर->ionic->idev.पूर्णांकr_ctrl,
					     lअगर->rxqcqs[i]->पूर्णांकr.index,
					     lअगर->rx_coalesce_hw);

			अगर (qparam->पूर्णांकr_split) अणु
				lअगर->txqcqs[i]->flags |= IONIC_QCQ_F_INTR;
				err = ionic_alloc_qcq_पूर्णांकerrupt(lअगर, lअगर->txqcqs[i]);
				ionic_पूर्णांकr_coal_init(lअगर->ionic->idev.पूर्णांकr_ctrl,
						     lअगर->txqcqs[i]->पूर्णांकr.index,
						     lअगर->tx_coalesce_hw);
				अगर (test_bit(IONIC_LIF_F_TX_DIM_INTR, lअगर->state))
					lअगर->txqcqs[i]->पूर्णांकr.dim_coal_hw = lअगर->tx_coalesce_hw;
			पूर्ण अन्यथा अणु
				lअगर->txqcqs[i]->flags &= ~IONIC_QCQ_F_INTR;
				ionic_link_qcq_पूर्णांकerrupts(lअगर->rxqcqs[i], lअगर->txqcqs[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	/* now we can rework the debugfs mappings */
	अगर (tx_qcqs) अणु
		क्रम (i = 0; i < qparam->nxqs; i++) अणु
			ionic_debugfs_del_qcq(lअगर->txqcqs[i]);
			ionic_debugfs_add_qcq(lअगर, lअगर->txqcqs[i]);
		पूर्ण
	पूर्ण

	अगर (rx_qcqs) अणु
		क्रम (i = 0; i < qparam->nxqs; i++) अणु
			ionic_debugfs_del_qcq(lअगर->rxqcqs[i]);
			ionic_debugfs_add_qcq(lअगर, lअगर->rxqcqs[i]);
		पूर्ण
	पूर्ण

	swap(lअगर->nxqs, qparam->nxqs);
	swap(lअगर->rxq_features, qparam->rxq_features);

err_out_reinit_unlock:
	/* re-init the queues, but करोn't lose an error code */
	अगर (err)
		ionic_start_queues_reconfig(lअगर);
	अन्यथा
		err = ionic_start_queues_reconfig(lअगर);

err_out:
	/* मुक्त old allocs without cleaning पूर्णांकr */
	क्रम (i = 0; i < qparam->nxqs; i++) अणु
		अगर (tx_qcqs && tx_qcqs[i]) अणु
			tx_qcqs[i]->flags &= ~IONIC_QCQ_F_INTR;
			ionic_qcq_मुक्त(lअगर, tx_qcqs[i]);
			devm_kमुक्त(lअगर->ionic->dev, tx_qcqs[i]);
			tx_qcqs[i] = शून्य;
		पूर्ण
		अगर (rx_qcqs && rx_qcqs[i]) अणु
			rx_qcqs[i]->flags &= ~IONIC_QCQ_F_INTR;
			ionic_qcq_मुक्त(lअगर, rx_qcqs[i]);
			devm_kमुक्त(lअगर->ionic->dev, rx_qcqs[i]);
			rx_qcqs[i] = शून्य;
		पूर्ण
	पूर्ण

	/* मुक्त q array */
	अगर (rx_qcqs) अणु
		devm_kमुक्त(lअगर->ionic->dev, rx_qcqs);
		rx_qcqs = शून्य;
	पूर्ण
	अगर (tx_qcqs) अणु
		devm_kमुक्त(lअगर->ionic->dev, tx_qcqs);
		tx_qcqs = शून्य;
	पूर्ण

	/* clean the unused dma and info allocations when new set is smaller
	 * than the full array, but leave the qcq shells in place
	 */
	क्रम (i = lअगर->nxqs; i < lअगर->ionic->ntxqs_per_lअगर; i++) अणु
		lअगर->txqcqs[i]->flags &= ~IONIC_QCQ_F_INTR;
		ionic_qcq_मुक्त(lअगर, lअगर->txqcqs[i]);

		lअगर->rxqcqs[i]->flags &= ~IONIC_QCQ_F_INTR;
		ionic_qcq_मुक्त(lअगर, lअगर->rxqcqs[i]);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक ionic_lअगर_alloc(काष्ठा ionic *ionic)
अणु
	काष्ठा device *dev = ionic->dev;
	जोड़ ionic_lअगर_identity *lid;
	काष्ठा net_device *netdev;
	काष्ठा ionic_lअगर *lअगर;
	पूर्णांक tbl_sz;
	पूर्णांक err;

	lid = kzalloc(माप(*lid), GFP_KERNEL);
	अगर (!lid)
		वापस -ENOMEM;

	netdev = alloc_etherdev_mqs(माप(*lअगर),
				    ionic->ntxqs_per_lअगर, ionic->ntxqs_per_lअगर);
	अगर (!netdev) अणु
		dev_err(dev, "Cannot allocate netdev, aborting\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_lid;
	पूर्ण

	SET_NETDEV_DEV(netdev, dev);

	lअगर = netdev_priv(netdev);
	lअगर->netdev = netdev;
	ionic->lअगर = lअगर;
	netdev->netdev_ops = &ionic_netdev_ops;
	ionic_ethtool_set_ops(netdev);

	netdev->watchकरोg_समयo = 2 * HZ;
	netअगर_carrier_off(netdev);

	lअगर->identity = lid;
	lअगर->lअगर_type = IONIC_LIF_TYPE_CLASSIC;
	err = ionic_lअगर_identअगरy(ionic, lअगर->lअगर_type, lअगर->identity);
	अगर (err) अणु
		dev_err(ionic->dev, "Cannot identify type %d: %d\n",
			lअगर->lअगर_type, err);
		जाओ err_out_मुक्त_netdev;
	पूर्ण
	lअगर->netdev->min_mtu = max_t(अचिन्हित पूर्णांक, ETH_MIN_MTU,
				     le32_to_cpu(lअगर->identity->eth.min_frame_size));
	lअगर->netdev->max_mtu =
		le32_to_cpu(lअगर->identity->eth.max_frame_size) - ETH_HLEN - VLAN_HLEN;

	lअगर->neqs = ionic->neqs_per_lअगर;
	lअगर->nxqs = ionic->ntxqs_per_lअगर;

	lअगर->ionic = ionic;
	lअगर->index = 0;
	lअगर->ntxq_descs = IONIC_DEF_TXRX_DESC;
	lअगर->nrxq_descs = IONIC_DEF_TXRX_DESC;

	/* Convert the शेष coalesce value to actual hw resolution */
	lअगर->rx_coalesce_usecs = IONIC_ITR_COAL_USEC_DEFAULT;
	lअगर->rx_coalesce_hw = ionic_coal_usec_to_hw(lअगर->ionic,
						    lअगर->rx_coalesce_usecs);
	lअगर->tx_coalesce_usecs = lअगर->rx_coalesce_usecs;
	lअगर->tx_coalesce_hw = lअगर->rx_coalesce_hw;
	set_bit(IONIC_LIF_F_RX_DIM_INTR, lअगर->state);
	set_bit(IONIC_LIF_F_TX_DIM_INTR, lअगर->state);

	snम_लिखो(lअगर->name, माप(lअगर->name), "lif%u", lअगर->index);

	spin_lock_init(&lअगर->adminq_lock);

	spin_lock_init(&lअगर->deferred.lock);
	INIT_LIST_HEAD(&lअगर->deferred.list);
	INIT_WORK(&lअगर->deferred.work, ionic_lअगर_deferred_work);

	/* allocate lअगर info */
	lअगर->info_sz = ALIGN(माप(*lअगर->info), PAGE_SIZE);
	lअगर->info = dma_alloc_coherent(dev, lअगर->info_sz,
				       &lअगर->info_pa, GFP_KERNEL);
	अगर (!lअगर->info) अणु
		dev_err(dev, "Failed to allocate lif info, aborting\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	ionic_debugfs_add_lअगर(lअगर);

	/* allocate control queues and txrx queue arrays */
	ionic_lअगर_queue_identअगरy(lअगर);
	err = ionic_qcqs_alloc(lअगर);
	अगर (err)
		जाओ err_out_मुक्त_lअगर_info;

	/* allocate rss indirection table */
	tbl_sz = le16_to_cpu(lअगर->ionic->ident.lअगर.eth.rss_ind_tbl_sz);
	lअगर->rss_ind_tbl_sz = माप(*lअगर->rss_ind_tbl) * tbl_sz;
	lअगर->rss_ind_tbl = dma_alloc_coherent(dev, lअगर->rss_ind_tbl_sz,
					      &lअगर->rss_ind_tbl_pa,
					      GFP_KERNEL);

	अगर (!lअगर->rss_ind_tbl) अणु
		err = -ENOMEM;
		dev_err(dev, "Failed to allocate rss indirection table, aborting\n");
		जाओ err_out_मुक्त_qcqs;
	पूर्ण
	netdev_rss_key_fill(lअगर->rss_hash_key, IONIC_RSS_HASH_KEY_SIZE);

	ionic_lअगर_alloc_phc(lअगर);

	वापस 0;

err_out_मुक्त_qcqs:
	ionic_qcqs_मुक्त(lअगर);
err_out_मुक्त_lअगर_info:
	dma_मुक्त_coherent(dev, lअगर->info_sz, lअगर->info, lअगर->info_pa);
	lअगर->info = शून्य;
	lअगर->info_pa = 0;
err_out_मुक्त_netdev:
	मुक्त_netdev(lअगर->netdev);
	lअगर = शून्य;
err_out_मुक्त_lid:
	kमुक्त(lid);

	वापस err;
पूर्ण

अटल व्योम ionic_lअगर_reset(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;

	mutex_lock(&lअगर->ionic->dev_cmd_lock);
	ionic_dev_cmd_lअगर_reset(idev, lअगर->index);
	ionic_dev_cmd_रुको(lअगर->ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&lअगर->ionic->dev_cmd_lock);
पूर्ण

अटल व्योम ionic_lअगर_handle_fw_करोwn(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic *ionic = lअगर->ionic;

	अगर (test_and_set_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
		वापस;

	dev_info(ionic->dev, "FW Down: Stopping LIFs\n");

	netअगर_device_detach(lअगर->netdev);

	अगर (test_bit(IONIC_LIF_F_UP, lअगर->state)) अणु
		dev_info(ionic->dev, "Surprise FW stop, stopping queues\n");
		mutex_lock(&lअगर->queue_lock);
		ionic_stop_queues(lअगर);
		mutex_unlock(&lअगर->queue_lock);
	पूर्ण

	अगर (netअगर_running(lअगर->netdev)) अणु
		ionic_txrx_deinit(lअगर);
		ionic_txrx_मुक्त(lअगर);
	पूर्ण
	ionic_lअगर_deinit(lअगर);
	ionic_reset(ionic);
	ionic_qcqs_मुक्त(lअगर);

	dev_info(ionic->dev, "FW Down: LIFs stopped\n");
पूर्ण

अटल व्योम ionic_lअगर_handle_fw_up(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक err;

	अगर (!test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
		वापस;

	dev_info(ionic->dev, "FW Up: restarting LIFs\n");

	ionic_init_devinfo(ionic);
	err = ionic_identअगरy(ionic);
	अगर (err)
		जाओ err_out;
	err = ionic_port_identअगरy(ionic);
	अगर (err)
		जाओ err_out;
	err = ionic_port_init(ionic);
	अगर (err)
		जाओ err_out;
	err = ionic_qcqs_alloc(lअगर);
	अगर (err)
		जाओ err_out;

	err = ionic_lअगर_init(lअगर);
	अगर (err)
		जाओ err_qcqs_मुक्त;

	अगर (lअगर->रेजिस्टरed)
		ionic_lअगर_set_netdev_info(lअगर);

	ionic_rx_filter_replay(lअगर);

	अगर (netअगर_running(lअगर->netdev)) अणु
		err = ionic_txrx_alloc(lअगर);
		अगर (err)
			जाओ err_lअगरs_deinit;

		err = ionic_txrx_init(lअगर);
		अगर (err)
			जाओ err_txrx_मुक्त;
	पूर्ण

	clear_bit(IONIC_LIF_F_FW_RESET, lअगर->state);
	ionic_link_status_check_request(lअगर, CAN_SLEEP);
	netअगर_device_attach(lअगर->netdev);
	dev_info(ionic->dev, "FW Up: LIFs restarted\n");

	/* restore the hardware बारtamping queues */
	ionic_lअगर_hwstamp_replay(lअगर);

	वापस;

err_txrx_मुक्त:
	ionic_txrx_मुक्त(lअगर);
err_lअगरs_deinit:
	ionic_lअगर_deinit(lअगर);
err_qcqs_मुक्त:
	ionic_qcqs_मुक्त(lअगर);
err_out:
	dev_err(ionic->dev, "FW Up: LIFs restart failed - err %d\n", err);
पूर्ण

व्योम ionic_lअगर_मुक्त(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;

	ionic_lअगर_मुक्त_phc(lअगर);

	/* मुक्त rss indirection table */
	dma_मुक्त_coherent(dev, lअगर->rss_ind_tbl_sz, lअगर->rss_ind_tbl,
			  lअगर->rss_ind_tbl_pa);
	lअगर->rss_ind_tbl = शून्य;
	lअगर->rss_ind_tbl_pa = 0;

	/* मुक्त queues */
	ionic_qcqs_मुक्त(lअगर);
	अगर (!test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
		ionic_lअगर_reset(lअगर);

	/* मुक्त lअगर info */
	kमुक्त(lअगर->identity);
	dma_मुक्त_coherent(dev, lअगर->info_sz, lअगर->info, lअगर->info_pa);
	lअगर->info = शून्य;
	lअगर->info_pa = 0;

	/* unmap करोorbell page */
	ionic_bus_unmap_dbpage(lअगर->ionic, lअगर->kern_dbpage);
	lअगर->kern_dbpage = शून्य;
	kमुक्त(lअगर->dbid_inuse);
	lअगर->dbid_inuse = शून्य;

	/* मुक्त netdev & lअगर */
	ionic_debugfs_del_lअगर(lअगर);
	मुक्त_netdev(lअगर->netdev);
पूर्ण

व्योम ionic_lअगर_deinit(काष्ठा ionic_lअगर *lअगर)
अणु
	अगर (!test_and_clear_bit(IONIC_LIF_F_INITED, lअगर->state))
		वापस;

	अगर (!test_bit(IONIC_LIF_F_FW_RESET, lअगर->state)) अणु
		cancel_work_sync(&lअगर->deferred.work);
		cancel_work_sync(&lअगर->tx_समयout_work);
		ionic_rx_filters_deinit(lअगर);
		अगर (lअगर->netdev->features & NETIF_F_RXHASH)
			ionic_lअगर_rss_deinit(lअगर);
	पूर्ण

	napi_disable(&lअगर->adminqcq->napi);
	ionic_lअगर_qcq_deinit(lअगर, lअगर->notअगरyqcq);
	ionic_lअगर_qcq_deinit(lअगर, lअगर->adminqcq);

	mutex_destroy(&lअगर->queue_lock);
	ionic_lअगर_reset(lअगर);
पूर्ण

अटल पूर्णांक ionic_lअगर_adminq_init(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_q_init_comp comp;
	काष्ठा ionic_dev *idev;
	काष्ठा ionic_qcq *qcq;
	काष्ठा ionic_queue *q;
	पूर्णांक err;

	idev = &lअगर->ionic->idev;
	qcq = lअगर->adminqcq;
	q = &qcq->q;

	mutex_lock(&lअगर->ionic->dev_cmd_lock);
	ionic_dev_cmd_adminq_init(idev, qcq, lअगर->index, qcq->पूर्णांकr.index);
	err = ionic_dev_cmd_रुको(lअगर->ionic, DEVCMD_TIMEOUT);
	ionic_dev_cmd_comp(idev, (जोड़ ionic_dev_cmd_comp *)&comp);
	mutex_unlock(&lअगर->ionic->dev_cmd_lock);
	अगर (err) अणु
		netdev_err(lअगर->netdev, "adminq init failed %d\n", err);
		वापस err;
	पूर्ण

	q->hw_type = comp.hw_type;
	q->hw_index = le32_to_cpu(comp.hw_index);
	q->dbval = IONIC_DBELL_QID(q->hw_index);

	dev_dbg(dev, "adminq->hw_type %d\n", q->hw_type);
	dev_dbg(dev, "adminq->hw_index %d\n", q->hw_index);

	netअगर_napi_add(lअगर->netdev, &qcq->napi, ionic_adminq_napi,
		       NAPI_POLL_WEIGHT);

	napi_enable(&qcq->napi);

	अगर (qcq->flags & IONIC_QCQ_F_INTR)
		ionic_पूर्णांकr_mask(idev->पूर्णांकr_ctrl, qcq->पूर्णांकr.index,
				IONIC_INTR_MASK_CLEAR);

	qcq->flags |= IONIC_QCQ_F_INITED;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_lअगर_notअगरyq_init(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_qcq *qcq = lअगर->notअगरyqcq;
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_queue *q = &qcq->q;
	पूर्णांक err;

	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.q_init = अणु
			.opcode = IONIC_CMD_Q_INIT,
			.lअगर_index = cpu_to_le16(lअगर->index),
			.type = q->type,
			.ver = lअगर->qtype_info[q->type].version,
			.index = cpu_to_le32(q->index),
			.flags = cpu_to_le16(IONIC_QINIT_F_IRQ |
					     IONIC_QINIT_F_ENA),
			.पूर्णांकr_index = cpu_to_le16(lअगर->adminqcq->पूर्णांकr.index),
			.pid = cpu_to_le16(q->pid),
			.ring_size = ilog2(q->num_descs),
			.ring_base = cpu_to_le64(q->base_pa),
		पूर्ण
	पूर्ण;

	dev_dbg(dev, "notifyq_init.pid %d\n", ctx.cmd.q_init.pid);
	dev_dbg(dev, "notifyq_init.index %d\n", ctx.cmd.q_init.index);
	dev_dbg(dev, "notifyq_init.ring_base 0x%llx\n", ctx.cmd.q_init.ring_base);
	dev_dbg(dev, "notifyq_init.ring_size %d\n", ctx.cmd.q_init.ring_size);

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		वापस err;

	lअगर->last_eid = 0;
	q->hw_type = ctx.comp.q_init.hw_type;
	q->hw_index = le32_to_cpu(ctx.comp.q_init.hw_index);
	q->dbval = IONIC_DBELL_QID(q->hw_index);

	dev_dbg(dev, "notifyq->hw_type %d\n", q->hw_type);
	dev_dbg(dev, "notifyq->hw_index %d\n", q->hw_index);

	/* preset the callback info */
	q->info[0].cb_arg = lअगर;

	qcq->flags |= IONIC_QCQ_F_INITED;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_station_set(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा net_device *netdev = lअगर->netdev;
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.lअगर_getattr = अणु
			.opcode = IONIC_CMD_LIF_GETATTR,
			.index = cpu_to_le16(lअगर->index),
			.attr = IONIC_LIF_ATTR_MAC,
		पूर्ण,
	पूर्ण;
	काष्ठा sockaddr addr;
	पूर्णांक err;

	err = ionic_adminq_post_रुको(lअगर, &ctx);
	अगर (err)
		वापस err;
	netdev_dbg(lअगर->netdev, "found initial MAC addr %pM\n",
		   ctx.comp.lअगर_getattr.mac);
	अगर (is_zero_ether_addr(ctx.comp.lअगर_getattr.mac))
		वापस 0;

	अगर (!is_zero_ether_addr(netdev->dev_addr)) अणु
		/* If the netdev mac is non-zero and करोesn't match the शेष
		 * device address, it was set by something earlier and we're
		 * likely here again after a fw-upgrade reset.  We need to be
		 * sure the netdev mac is in our filter list.
		 */
		अगर (!ether_addr_equal(ctx.comp.lअगर_getattr.mac,
				      netdev->dev_addr))
			ionic_lअगर_addr(lअगर, netdev->dev_addr, ADD_ADDR, CAN_SLEEP);
	पूर्ण अन्यथा अणु
		/* Update the netdev mac with the device's mac */
		स_नकल(addr.sa_data, ctx.comp.lअगर_getattr.mac, netdev->addr_len);
		addr.sa_family = AF_INET;
		err = eth_prepare_mac_addr_change(netdev, &addr);
		अगर (err) अणु
			netdev_warn(lअगर->netdev, "ignoring bad MAC addr from NIC %pM - err %d\n",
				    addr.sa_data, err);
			वापस 0;
		पूर्ण

		eth_commit_mac_addr_change(netdev, &addr);
	पूर्ण

	netdev_dbg(lअगर->netdev, "adding station MAC addr %pM\n",
		   netdev->dev_addr);
	ionic_lअगर_addr(lअगर, netdev->dev_addr, ADD_ADDR, CAN_SLEEP);

	वापस 0;
पूर्ण

पूर्णांक ionic_lअगर_init(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_lअगर_init_comp comp;
	पूर्णांक dbpage_num;
	पूर्णांक err;

	mutex_lock(&lअगर->ionic->dev_cmd_lock);
	ionic_dev_cmd_lअगर_init(idev, lअगर->index, lअगर->info_pa);
	err = ionic_dev_cmd_रुको(lअगर->ionic, DEVCMD_TIMEOUT);
	ionic_dev_cmd_comp(idev, (जोड़ ionic_dev_cmd_comp *)&comp);
	mutex_unlock(&lअगर->ionic->dev_cmd_lock);
	अगर (err)
		वापस err;

	lअगर->hw_index = le16_to_cpu(comp.hw_index);
	mutex_init(&lअगर->queue_lock);

	/* now that we have the hw_index we can figure out our करोorbell page */
	lअगर->dbid_count = le32_to_cpu(lअगर->ionic->ident.dev.ndbpgs_per_lअगर);
	अगर (!lअगर->dbid_count) अणु
		dev_err(dev, "No doorbell pages, aborting\n");
		वापस -EINVAL;
	पूर्ण

	lअगर->dbid_inuse = biपंचांगap_alloc(lअगर->dbid_count, GFP_KERNEL);
	अगर (!lअगर->dbid_inuse) अणु
		dev_err(dev, "Failed alloc doorbell id bitmap, aborting\n");
		वापस -ENOMEM;
	पूर्ण

	/* first करोorbell id reserved क्रम kernel (dbid aka pid == zero) */
	set_bit(0, lअगर->dbid_inuse);
	lअगर->kern_pid = 0;

	dbpage_num = ionic_db_page_num(lअगर, lअगर->kern_pid);
	lअगर->kern_dbpage = ionic_bus_map_dbpage(lअगर->ionic, dbpage_num);
	अगर (!lअगर->kern_dbpage) अणु
		dev_err(dev, "Cannot map dbpage, aborting\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_dbid;
	पूर्ण

	err = ionic_lअगर_adminq_init(lअगर);
	अगर (err)
		जाओ err_out_adminq_deinit;

	अगर (lअगर->ionic->nnqs_per_lअगर) अणु
		err = ionic_lअगर_notअगरyq_init(lअगर);
		अगर (err)
			जाओ err_out_notअगरyq_deinit;
	पूर्ण

	err = ionic_init_nic_features(lअगर);
	अगर (err)
		जाओ err_out_notअगरyq_deinit;

	अगर (!test_bit(IONIC_LIF_F_FW_RESET, lअगर->state)) अणु
		err = ionic_rx_filters_init(lअगर);
		अगर (err)
			जाओ err_out_notअगरyq_deinit;
	पूर्ण

	err = ionic_station_set(lअगर);
	अगर (err)
		जाओ err_out_notअगरyq_deinit;

	lअगर->rx_copyअवरोध = IONIC_RX_COPYBREAK_DEFAULT;

	set_bit(IONIC_LIF_F_INITED, lअगर->state);

	INIT_WORK(&lअगर->tx_समयout_work, ionic_tx_समयout_work);

	वापस 0;

err_out_notअगरyq_deinit:
	ionic_lअगर_qcq_deinit(lअगर, lअगर->notअगरyqcq);
err_out_adminq_deinit:
	ionic_lअगर_qcq_deinit(lअगर, lअगर->adminqcq);
	ionic_lअगर_reset(lअगर);
	ionic_bus_unmap_dbpage(lअगर->ionic, lअगर->kern_dbpage);
	lअगर->kern_dbpage = शून्य;
err_out_मुक्त_dbid:
	kमुक्त(lअगर->dbid_inuse);
	lअगर->dbid_inuse = शून्य;

	वापस err;
पूर्ण

अटल व्योम ionic_lअगर_notअगरy_work(काष्ठा work_काष्ठा *ws)
अणु
पूर्ण

अटल व्योम ionic_lअगर_set_netdev_info(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_admin_ctx ctx = अणु
		.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work),
		.cmd.lअगर_setattr = अणु
			.opcode = IONIC_CMD_LIF_SETATTR,
			.index = cpu_to_le16(lअगर->index),
			.attr = IONIC_LIF_ATTR_NAME,
		पूर्ण,
	पूर्ण;

	strlcpy(ctx.cmd.lअगर_setattr.name, lअगर->netdev->name,
		माप(ctx.cmd.lअगर_setattr.name));

	ionic_adminq_post_रुको(lअगर, &ctx);
पूर्ण

अटल काष्ठा ionic_lअगर *ionic_netdev_lअगर(काष्ठा net_device *netdev)
अणु
	अगर (!netdev || netdev->netdev_ops->nकरो_start_xmit != ionic_start_xmit)
		वापस शून्य;

	वापस netdev_priv(netdev);
पूर्ण

अटल पूर्णांक ionic_lअगर_notअगरy(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ event, व्योम *info)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(info);
	काष्ठा ionic *ionic = container_of(nb, काष्ठा ionic, nb);
	काष्ठा ionic_lअगर *lअगर = ionic_netdev_lअगर(ndev);

	अगर (!lअगर || lअगर->ionic != ionic)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		ionic_lअगर_set_netdev_info(lअगर);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक ionic_lअगर_रेजिस्टर(काष्ठा ionic_lअगर *lअगर)
अणु
	पूर्णांक err;

	ionic_lअगर_रेजिस्टर_phc(lअगर);

	INIT_WORK(&lअगर->ionic->nb_work, ionic_lअगर_notअगरy_work);

	lअगर->ionic->nb.notअगरier_call = ionic_lअगर_notअगरy;

	err = रेजिस्टर_netdevice_notअगरier(&lअगर->ionic->nb);
	अगर (err)
		lअगर->ionic->nb.notअगरier_call = शून्य;

	/* only रेजिस्टर LIF0 क्रम now */
	err = रेजिस्टर_netdev(lअगर->netdev);
	अगर (err) अणु
		dev_err(lअगर->ionic->dev, "Cannot register net device, aborting\n");
		ionic_lअगर_unरेजिस्टर_phc(lअगर);
		वापस err;
	पूर्ण

	ionic_link_status_check_request(lअगर, CAN_SLEEP);
	lअगर->रेजिस्टरed = true;
	ionic_lअगर_set_netdev_info(lअगर);

	वापस 0;
पूर्ण

व्योम ionic_lअगर_unरेजिस्टर(काष्ठा ionic_lअगर *lअगर)
अणु
	अगर (lअगर->ionic->nb.notअगरier_call) अणु
		unरेजिस्टर_netdevice_notअगरier(&lअगर->ionic->nb);
		cancel_work_sync(&lअगर->ionic->nb_work);
		lअगर->ionic->nb.notअगरier_call = शून्य;
	पूर्ण

	अगर (lअगर->netdev->reg_state == NETREG_REGISTERED)
		unरेजिस्टर_netdev(lअगर->netdev);

	ionic_lअगर_unरेजिस्टर_phc(lअगर);

	lअगर->रेजिस्टरed = false;
पूर्ण

अटल व्योम ionic_lअगर_queue_identअगरy(काष्ठा ionic_lअगर *lअगर)
अणु
	जोड़ ionic_q_identity __iomem *q_ident;
	काष्ठा ionic *ionic = lअगर->ionic;
	काष्ठा ionic_dev *idev;
	पूर्णांक qtype;
	पूर्णांक err;

	idev = &lअगर->ionic->idev;
	q_ident = (जोड़ ionic_q_identity __iomem *)&idev->dev_cmd_regs->data;

	क्रम (qtype = 0; qtype < ARRAY_SIZE(ionic_qtype_versions); qtype++) अणु
		काष्ठा ionic_qtype_info *qti = &lअगर->qtype_info[qtype];

		/* filter out the ones we know about */
		चयन (qtype) अणु
		हाल IONIC_QTYPE_ADMINQ:
		हाल IONIC_QTYPE_NOTIFYQ:
		हाल IONIC_QTYPE_RXQ:
		हाल IONIC_QTYPE_TXQ:
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		स_रखो(qti, 0, माप(*qti));

		mutex_lock(&ionic->dev_cmd_lock);
		ionic_dev_cmd_queue_identअगरy(idev, lअगर->lअगर_type, qtype,
					     ionic_qtype_versions[qtype]);
		err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
		अगर (!err) अणु
			qti->version   = पढ़ोb(&q_ident->version);
			qti->supported = पढ़ोb(&q_ident->supported);
			qti->features  = पढ़ोq(&q_ident->features);
			qti->desc_sz   = पढ़ोw(&q_ident->desc_sz);
			qti->comp_sz   = पढ़ोw(&q_ident->comp_sz);
			qti->sg_desc_sz   = पढ़ोw(&q_ident->sg_desc_sz);
			qti->max_sg_elems = पढ़ोw(&q_ident->max_sg_elems);
			qti->sg_desc_stride = पढ़ोw(&q_ident->sg_desc_stride);
		पूर्ण
		mutex_unlock(&ionic->dev_cmd_lock);

		अगर (err == -EINVAL) अणु
			dev_err(ionic->dev, "qtype %d not supported\n", qtype);
			जारी;
		पूर्ण अन्यथा अगर (err == -EIO) अणु
			dev_err(ionic->dev, "q_ident failed, not supported on older FW\n");
			वापस;
		पूर्ण अन्यथा अगर (err) अणु
			dev_err(ionic->dev, "q_ident failed, qtype %d: %d\n",
				qtype, err);
			वापस;
		पूर्ण

		dev_dbg(ionic->dev, " qtype[%d].version = %d\n",
			qtype, qti->version);
		dev_dbg(ionic->dev, " qtype[%d].supported = 0x%02x\n",
			qtype, qti->supported);
		dev_dbg(ionic->dev, " qtype[%d].features = 0x%04llx\n",
			qtype, qti->features);
		dev_dbg(ionic->dev, " qtype[%d].desc_sz = %d\n",
			qtype, qti->desc_sz);
		dev_dbg(ionic->dev, " qtype[%d].comp_sz = %d\n",
			qtype, qti->comp_sz);
		dev_dbg(ionic->dev, " qtype[%d].sg_desc_sz = %d\n",
			qtype, qti->sg_desc_sz);
		dev_dbg(ionic->dev, " qtype[%d].max_sg_elems = %d\n",
			qtype, qti->max_sg_elems);
		dev_dbg(ionic->dev, " qtype[%d].sg_desc_stride = %d\n",
			qtype, qti->sg_desc_stride);
	पूर्ण
पूर्ण

पूर्णांक ionic_lअगर_identअगरy(काष्ठा ionic *ionic, u8 lअगर_type,
		       जोड़ ionic_lअगर_identity *lid)
अणु
	काष्ठा ionic_dev *idev = &ionic->idev;
	माप_प्रकार sz;
	पूर्णांक err;

	sz = min(माप(*lid), माप(idev->dev_cmd_regs->data));

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_lअगर_identअगरy(idev, lअगर_type, IONIC_IDENTITY_VERSION_1);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	स_नकल_fromio(lid, &idev->dev_cmd_regs->data, sz);
	mutex_unlock(&ionic->dev_cmd_lock);
	अगर (err)
		वापस (err);

	dev_dbg(ionic->dev, "capabilities 0x%llx\n",
		le64_to_cpu(lid->capabilities));

	dev_dbg(ionic->dev, "eth.max_ucast_filters %d\n",
		le32_to_cpu(lid->eth.max_ucast_filters));
	dev_dbg(ionic->dev, "eth.max_mcast_filters %d\n",
		le32_to_cpu(lid->eth.max_mcast_filters));
	dev_dbg(ionic->dev, "eth.features 0x%llx\n",
		le64_to_cpu(lid->eth.config.features));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_ADMINQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_ADMINQ]));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_NOTIFYQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_NOTIFYQ]));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_RXQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_RXQ]));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_TXQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_TXQ]));
	dev_dbg(ionic->dev, "eth.config.name %s\n", lid->eth.config.name);
	dev_dbg(ionic->dev, "eth.config.mac %pM\n", lid->eth.config.mac);
	dev_dbg(ionic->dev, "eth.config.mtu %d\n",
		le32_to_cpu(lid->eth.config.mtu));

	वापस 0;
पूर्ण

पूर्णांक ionic_lअगर_size(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_identity *ident = &ionic->ident;
	अचिन्हित पूर्णांक nपूर्णांकrs, dev_nपूर्णांकrs;
	जोड़ ionic_lअगर_config *lc;
	अचिन्हित पूर्णांक ntxqs_per_lअगर;
	अचिन्हित पूर्णांक nrxqs_per_lअगर;
	अचिन्हित पूर्णांक neqs_per_lअगर;
	अचिन्हित पूर्णांक nnqs_per_lअगर;
	अचिन्हित पूर्णांक nxqs, neqs;
	अचिन्हित पूर्णांक min_पूर्णांकrs;
	पूर्णांक err;

	lc = &ident->lअगर.eth.config;
	dev_nपूर्णांकrs = le32_to_cpu(ident->dev.nपूर्णांकrs);
	neqs_per_lअगर = le32_to_cpu(ident->lअगर.rdma.eq_qtype.qid_count);
	nnqs_per_lअगर = le32_to_cpu(lc->queue_count[IONIC_QTYPE_NOTIFYQ]);
	ntxqs_per_lअगर = le32_to_cpu(lc->queue_count[IONIC_QTYPE_TXQ]);
	nrxqs_per_lअगर = le32_to_cpu(lc->queue_count[IONIC_QTYPE_RXQ]);

	/* reserve last queue id क्रम hardware बारtamping */
	अगर (lc->features & cpu_to_le64(IONIC_ETH_HW_TIMESTAMP)) अणु
		अगर (ntxqs_per_lअगर <= 1 || nrxqs_per_lअगर <= 1) अणु
			lc->features &= cpu_to_le64(~IONIC_ETH_HW_TIMESTAMP);
		पूर्ण अन्यथा अणु
			ntxqs_per_lअगर -= 1;
			nrxqs_per_lअगर -= 1;
		पूर्ण
	पूर्ण

	nxqs = min(ntxqs_per_lअगर, nrxqs_per_lअगर);
	nxqs = min(nxqs, num_online_cpus());
	neqs = min(neqs_per_lअगर, num_online_cpus());

try_again:
	/* पूर्णांकerrupt usage:
	 *    1 क्रम master lअगर adminq/notअगरyq
	 *    1 क्रम each CPU क्रम master lअगर TxRx queue pairs
	 *    whatever's left is क्रम RDMA queues
	 */
	nपूर्णांकrs = 1 + nxqs + neqs;
	min_पूर्णांकrs = 2;  /* adminq + 1 TxRx queue pair */

	अगर (nपूर्णांकrs > dev_nपूर्णांकrs)
		जाओ try_fewer;

	err = ionic_bus_alloc_irq_vectors(ionic, nपूर्णांकrs);
	अगर (err < 0 && err != -ENOSPC) अणु
		dev_err(ionic->dev, "Can't get intrs from OS: %d\n", err);
		वापस err;
	पूर्ण
	अगर (err == -ENOSPC)
		जाओ try_fewer;

	अगर (err != nपूर्णांकrs) अणु
		ionic_bus_मुक्त_irq_vectors(ionic);
		जाओ try_fewer;
	पूर्ण

	ionic->nnqs_per_lअगर = nnqs_per_lअगर;
	ionic->neqs_per_lअगर = neqs;
	ionic->ntxqs_per_lअगर = nxqs;
	ionic->nrxqs_per_lअगर = nxqs;
	ionic->nपूर्णांकrs = nपूर्णांकrs;

	ionic_debugfs_add_sizes(ionic);

	वापस 0;

try_fewer:
	अगर (nnqs_per_lअगर > 1) अणु
		nnqs_per_lअगर >>= 1;
		जाओ try_again;
	पूर्ण
	अगर (neqs > 1) अणु
		neqs >>= 1;
		जाओ try_again;
	पूर्ण
	अगर (nxqs > 1) अणु
		nxqs >>= 1;
		जाओ try_again;
	पूर्ण
	dev_err(ionic->dev, "Can't get minimum %d intrs from OS\n", min_पूर्णांकrs);
	वापस -ENOSPC;
पूर्ण
