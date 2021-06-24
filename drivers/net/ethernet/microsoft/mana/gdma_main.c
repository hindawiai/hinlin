<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2021, Microsoft Corporation. */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "mana.h"

अटल u32 mana_gd_r32(काष्ठा gdma_context *g, u64 offset)
अणु
	वापस पढ़ोl(g->bar0_va + offset);
पूर्ण

अटल u64 mana_gd_r64(काष्ठा gdma_context *g, u64 offset)
अणु
	वापस पढ़ोq(g->bar0_va + offset);
पूर्ण

अटल व्योम mana_gd_init_रेजिस्टरs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा gdma_context *gc = pci_get_drvdata(pdev);

	gc->db_page_size = mana_gd_r32(gc, GDMA_REG_DB_PAGE_SIZE) & 0xFFFF;

	gc->db_page_base = gc->bar0_va +
				mana_gd_r64(gc, GDMA_REG_DB_PAGE_OFFSET);

	gc->shm_base = gc->bar0_va + mana_gd_r64(gc, GDMA_REG_SHM_OFFSET);
पूर्ण

अटल पूर्णांक mana_gd_query_max_resources(काष्ठा pci_dev *pdev)
अणु
	काष्ठा gdma_context *gc = pci_get_drvdata(pdev);
	काष्ठा gdma_query_max_resources_resp resp = अणुपूर्ण;
	काष्ठा gdma_general_req req = अणुपूर्ण;
	पूर्णांक err;

	mana_gd_init_req_hdr(&req.hdr, GDMA_QUERY_MAX_RESOURCES,
			     माप(req), माप(resp));

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status) अणु
		dev_err(gc->dev, "Failed to query resource info: %d, 0x%x\n",
			err, resp.hdr.status);
		वापस err ? err : -EPROTO;
	पूर्ण

	अगर (gc->num_msix_usable > resp.max_msix)
		gc->num_msix_usable = resp.max_msix;

	अगर (gc->num_msix_usable <= 1)
		वापस -ENOSPC;

	gc->max_num_queues = num_online_cpus();
	अगर (gc->max_num_queues > MANA_MAX_NUM_QUEUES)
		gc->max_num_queues = MANA_MAX_NUM_QUEUES;

	अगर (gc->max_num_queues > resp.max_eq)
		gc->max_num_queues = resp.max_eq;

	अगर (gc->max_num_queues > resp.max_cq)
		gc->max_num_queues = resp.max_cq;

	अगर (gc->max_num_queues > resp.max_sq)
		gc->max_num_queues = resp.max_sq;

	अगर (gc->max_num_queues > resp.max_rq)
		gc->max_num_queues = resp.max_rq;

	वापस 0;
पूर्ण

अटल पूर्णांक mana_gd_detect_devices(काष्ठा pci_dev *pdev)
अणु
	काष्ठा gdma_context *gc = pci_get_drvdata(pdev);
	काष्ठा gdma_list_devices_resp resp = अणुपूर्ण;
	काष्ठा gdma_general_req req = अणुपूर्ण;
	काष्ठा gdma_dev_id dev;
	u32 i, max_num_devs;
	u16 dev_type;
	पूर्णांक err;

	mana_gd_init_req_hdr(&req.hdr, GDMA_LIST_DEVICES, माप(req),
			     माप(resp));

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status) अणु
		dev_err(gc->dev, "Failed to detect devices: %d, 0x%x\n", err,
			resp.hdr.status);
		वापस err ? err : -EPROTO;
	पूर्ण

	max_num_devs = min_t(u32, MAX_NUM_GDMA_DEVICES, resp.num_of_devs);

	क्रम (i = 0; i < max_num_devs; i++) अणु
		dev = resp.devs[i];
		dev_type = dev.type;

		/* HWC is alपढ़ोy detected in mana_hwc_create_channel(). */
		अगर (dev_type == GDMA_DEVICE_HWC)
			जारी;

		अगर (dev_type == GDMA_DEVICE_MANA) अणु
			gc->mana.gdma_context = gc;
			gc->mana.dev_id = dev;
		पूर्ण
	पूर्ण

	वापस gc->mana.dev_id.type == 0 ? -ENODEV : 0;
पूर्ण

पूर्णांक mana_gd_send_request(काष्ठा gdma_context *gc, u32 req_len, स्थिर व्योम *req,
			 u32 resp_len, व्योम *resp)
अणु
	काष्ठा hw_channel_context *hwc = gc->hwc.driver_data;

	वापस mana_hwc_send_request(hwc, req_len, req, resp_len, resp);
पूर्ण

पूर्णांक mana_gd_alloc_memory(काष्ठा gdma_context *gc, अचिन्हित पूर्णांक length,
			 काष्ठा gdma_mem_info *gmi)
अणु
	dma_addr_t dma_handle;
	व्योम *buf;

	अगर (length < PAGE_SIZE || !is_घातer_of_2(length))
		वापस -EINVAL;

	gmi->dev = gc->dev;
	buf = dma_alloc_coherent(gmi->dev, length, &dma_handle, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	gmi->dma_handle = dma_handle;
	gmi->virt_addr = buf;
	gmi->length = length;

	वापस 0;
पूर्ण

व्योम mana_gd_मुक्त_memory(काष्ठा gdma_mem_info *gmi)
अणु
	dma_मुक्त_coherent(gmi->dev, gmi->length, gmi->virt_addr,
			  gmi->dma_handle);
पूर्ण

अटल पूर्णांक mana_gd_create_hw_eq(काष्ठा gdma_context *gc,
				काष्ठा gdma_queue *queue)
अणु
	काष्ठा gdma_create_queue_resp resp = अणुपूर्ण;
	काष्ठा gdma_create_queue_req req = अणुपूर्ण;
	पूर्णांक err;

	अगर (queue->type != GDMA_EQ)
		वापस -EINVAL;

	mana_gd_init_req_hdr(&req.hdr, GDMA_CREATE_QUEUE,
			     माप(req), माप(resp));

	req.hdr.dev_id = queue->gdma_dev->dev_id;
	req.type = queue->type;
	req.pdid = queue->gdma_dev->pdid;
	req.करोolbell_id = queue->gdma_dev->करोorbell;
	req.gdma_region = queue->mem_info.gdma_region;
	req.queue_size = queue->queue_size;
	req.log2_throttle_limit = queue->eq.log2_throttle_limit;
	req.eq_pci_msix_index = queue->eq.msix_index;

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status) अणु
		dev_err(gc->dev, "Failed to create queue: %d, 0x%x\n", err,
			resp.hdr.status);
		वापस err ? err : -EPROTO;
	पूर्ण

	queue->id = resp.queue_index;
	queue->eq.disable_needed = true;
	queue->mem_info.gdma_region = GDMA_INVALID_DMA_REGION;
	वापस 0;
पूर्ण

अटल पूर्णांक mana_gd_disable_queue(काष्ठा gdma_queue *queue)
अणु
	काष्ठा gdma_context *gc = queue->gdma_dev->gdma_context;
	काष्ठा gdma_disable_queue_req req = अणुपूर्ण;
	काष्ठा gdma_general_resp resp = अणुपूर्ण;
	पूर्णांक err;

	WARN_ON(queue->type != GDMA_EQ);

	mana_gd_init_req_hdr(&req.hdr, GDMA_DISABLE_QUEUE,
			     माप(req), माप(resp));

	req.hdr.dev_id = queue->gdma_dev->dev_id;
	req.type = queue->type;
	req.queue_index =  queue->id;
	req.alloc_res_id_on_creation = 1;

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status) अणु
		dev_err(gc->dev, "Failed to disable queue: %d, 0x%x\n", err,
			resp.hdr.status);
		वापस err ? err : -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DOORBELL_OFFSET_SQ	0x0
#घोषणा DOORBELL_OFFSET_RQ	0x400
#घोषणा DOORBELL_OFFSET_CQ	0x800
#घोषणा DOORBELL_OFFSET_EQ	0xFF8

अटल व्योम mana_gd_ring_करोorbell(काष्ठा gdma_context *gc, u32 db_index,
				  क्रमागत gdma_queue_type q_type, u32 qid,
				  u32 tail_ptr, u8 num_req)
अणु
	व्योम __iomem *addr = gc->db_page_base + gc->db_page_size * db_index;
	जोड़ gdma_करोorbell_entry e = अणुपूर्ण;

	चयन (q_type) अणु
	हाल GDMA_EQ:
		e.eq.id = qid;
		e.eq.tail_ptr = tail_ptr;
		e.eq.arm = num_req;

		addr += DOORBELL_OFFSET_EQ;
		अवरोध;

	हाल GDMA_CQ:
		e.cq.id = qid;
		e.cq.tail_ptr = tail_ptr;
		e.cq.arm = num_req;

		addr += DOORBELL_OFFSET_CQ;
		अवरोध;

	हाल GDMA_RQ:
		e.rq.id = qid;
		e.rq.tail_ptr = tail_ptr;
		e.rq.wqe_cnt = num_req;

		addr += DOORBELL_OFFSET_RQ;
		अवरोध;

	हाल GDMA_SQ:
		e.sq.id = qid;
		e.sq.tail_ptr = tail_ptr;

		addr += DOORBELL_OFFSET_SQ;
		अवरोध;

	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	/* Ensure all ग_लिखोs are करोne beक्रमe ring करोorbell */
	wmb();

	ग_लिखोq(e.as_uपूर्णांक64, addr);
पूर्ण

व्योम mana_gd_wq_ring_करोorbell(काष्ठा gdma_context *gc, काष्ठा gdma_queue *queue)
अणु
	mana_gd_ring_करोorbell(gc, queue->gdma_dev->करोorbell, queue->type,
			      queue->id, queue->head * GDMA_WQE_BU_SIZE, 1);
पूर्ण

व्योम mana_gd_arm_cq(काष्ठा gdma_queue *cq)
अणु
	काष्ठा gdma_context *gc = cq->gdma_dev->gdma_context;

	u32 num_cqe = cq->queue_size / GDMA_CQE_SIZE;

	u32 head = cq->head % (num_cqe << GDMA_CQE_OWNER_BITS);

	mana_gd_ring_करोorbell(gc, cq->gdma_dev->करोorbell, cq->type, cq->id,
			      head, SET_ARM_BIT);
पूर्ण

अटल व्योम mana_gd_process_eqe(काष्ठा gdma_queue *eq)
अणु
	u32 head = eq->head % (eq->queue_size / GDMA_EQE_SIZE);
	काष्ठा gdma_context *gc = eq->gdma_dev->gdma_context;
	काष्ठा gdma_eqe *eq_eqe_ptr = eq->queue_mem_ptr;
	जोड़ gdma_eqe_info eqe_info;
	क्रमागत gdma_eqe_type type;
	काष्ठा gdma_event event;
	काष्ठा gdma_queue *cq;
	काष्ठा gdma_eqe *eqe;
	u32 cq_id;

	eqe = &eq_eqe_ptr[head];
	eqe_info.as_uपूर्णांक32 = eqe->eqe_info;
	type = eqe_info.type;

	चयन (type) अणु
	हाल GDMA_EQE_COMPLETION:
		cq_id = eqe->details[0] & 0xFFFFFF;
		अगर (WARN_ON_ONCE(cq_id >= gc->max_num_cqs))
			अवरोध;

		cq = gc->cq_table[cq_id];
		अगर (WARN_ON_ONCE(!cq || cq->type != GDMA_CQ || cq->id != cq_id))
			अवरोध;

		अगर (cq->cq.callback)
			cq->cq.callback(cq->cq.context, cq);

		अवरोध;

	हाल GDMA_EQE_TEST_EVENT:
		gc->test_event_eq_id = eq->id;
		complete(&gc->eq_test_event);
		अवरोध;

	हाल GDMA_EQE_HWC_INIT_EQ_ID_DB:
	हाल GDMA_EQE_HWC_INIT_DATA:
	हाल GDMA_EQE_HWC_INIT_DONE:
		अगर (!eq->eq.callback)
			अवरोध;

		event.type = type;
		स_नकल(&event.details, &eqe->details, GDMA_EVENT_DATA_SIZE);
		eq->eq.callback(eq->eq.context, eq, &event);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mana_gd_process_eq_events(व्योम *arg)
अणु
	u32 owner_bits, new_bits, old_bits;
	जोड़ gdma_eqe_info eqe_info;
	काष्ठा gdma_eqe *eq_eqe_ptr;
	काष्ठा gdma_queue *eq = arg;
	काष्ठा gdma_context *gc;
	काष्ठा gdma_eqe *eqe;
	अचिन्हित पूर्णांक arm_bit;
	u32 head, num_eqe;
	पूर्णांक i;

	gc = eq->gdma_dev->gdma_context;

	num_eqe = eq->queue_size / GDMA_EQE_SIZE;
	eq_eqe_ptr = eq->queue_mem_ptr;

	/* Process up to 5 EQEs at a समय, and update the HW head. */
	क्रम (i = 0; i < 5; i++) अणु
		eqe = &eq_eqe_ptr[eq->head % num_eqe];
		eqe_info.as_uपूर्णांक32 = eqe->eqe_info;
		owner_bits = eqe_info.owner_bits;

		old_bits = (eq->head / num_eqe - 1) & GDMA_EQE_OWNER_MASK;
		/* No more entries */
		अगर (owner_bits == old_bits)
			अवरोध;

		new_bits = (eq->head / num_eqe) & GDMA_EQE_OWNER_MASK;
		अगर (owner_bits != new_bits) अणु
			dev_err(gc->dev, "EQ %d: overflow detected\n", eq->id);
			अवरोध;
		पूर्ण

		mana_gd_process_eqe(eq);

		eq->head++;
	पूर्ण

	/* Always rearm the EQ क्रम HWC. For MANA, rearm it when NAPI is करोne. */
	अगर (mana_gd_is_hwc(eq->gdma_dev)) अणु
		arm_bit = SET_ARM_BIT;
	पूर्ण अन्यथा अगर (eq->eq.work_करोne < eq->eq.budget &&
		   napi_complete_करोne(&eq->eq.napi, eq->eq.work_करोne)) अणु
		arm_bit = SET_ARM_BIT;
	पूर्ण अन्यथा अणु
		arm_bit = 0;
	पूर्ण

	head = eq->head % (num_eqe << GDMA_EQE_OWNER_BITS);

	mana_gd_ring_करोorbell(gc, eq->gdma_dev->करोorbell, eq->type, eq->id,
			      head, arm_bit);
पूर्ण

अटल पूर्णांक mana_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gdma_queue *eq = container_of(napi, काष्ठा gdma_queue, eq.napi);

	eq->eq.work_करोne = 0;
	eq->eq.budget = budget;

	mana_gd_process_eq_events(eq);

	वापस min(eq->eq.work_करोne, budget);
पूर्ण

अटल व्योम mana_gd_schedule_napi(व्योम *arg)
अणु
	काष्ठा gdma_queue *eq = arg;
	काष्ठा napi_काष्ठा *napi;

	napi = &eq->eq.napi;
	napi_schedule_irqoff(napi);
पूर्ण

अटल पूर्णांक mana_gd_रेजिस्टर_irq(काष्ठा gdma_queue *queue,
				स्थिर काष्ठा gdma_queue_spec *spec)
अणु
	काष्ठा gdma_dev *gd = queue->gdma_dev;
	bool is_mana = mana_gd_is_mana(gd);
	काष्ठा gdma_irq_context *gic;
	काष्ठा gdma_context *gc;
	काष्ठा gdma_resource *r;
	अचिन्हित पूर्णांक msi_index;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	gc = gd->gdma_context;
	r = &gc->msix_resource;

	spin_lock_irqsave(&r->lock, flags);

	msi_index = find_first_zero_bit(r->map, r->size);
	अगर (msi_index >= r->size) अणु
		err = -ENOSPC;
	पूर्ण अन्यथा अणु
		biपंचांगap_set(r->map, msi_index, 1);
		queue->eq.msix_index = msi_index;
		err = 0;
	पूर्ण

	spin_unlock_irqrestore(&r->lock, flags);

	अगर (err)
		वापस err;

	WARN_ON(msi_index >= gc->num_msix_usable);

	gic = &gc->irq_contexts[msi_index];

	अगर (is_mana) अणु
		netअगर_napi_add(spec->eq.ndev, &queue->eq.napi, mana_poll,
			       NAPI_POLL_WEIGHT);
		napi_enable(&queue->eq.napi);
	पूर्ण

	WARN_ON(gic->handler || gic->arg);

	gic->arg = queue;

	अगर (is_mana)
		gic->handler = mana_gd_schedule_napi;
	अन्यथा
		gic->handler = mana_gd_process_eq_events;

	वापस 0;
पूर्ण

अटल व्योम mana_gd_deregiser_irq(काष्ठा gdma_queue *queue)
अणु
	काष्ठा gdma_dev *gd = queue->gdma_dev;
	काष्ठा gdma_irq_context *gic;
	काष्ठा gdma_context *gc;
	काष्ठा gdma_resource *r;
	अचिन्हित पूर्णांक msix_index;
	अचिन्हित दीर्घ flags;

	gc = gd->gdma_context;
	r = &gc->msix_resource;

	/* At most num_online_cpus() + 1 पूर्णांकerrupts are used. */
	msix_index = queue->eq.msix_index;
	अगर (WARN_ON(msix_index >= gc->num_msix_usable))
		वापस;

	gic = &gc->irq_contexts[msix_index];
	gic->handler = शून्य;
	gic->arg = शून्य;

	spin_lock_irqsave(&r->lock, flags);
	biपंचांगap_clear(r->map, msix_index, 1);
	spin_unlock_irqrestore(&r->lock, flags);

	queue->eq.msix_index = INVALID_PCI_MSIX_INDEX;
पूर्ण

पूर्णांक mana_gd_test_eq(काष्ठा gdma_context *gc, काष्ठा gdma_queue *eq)
अणु
	काष्ठा gdma_generate_test_event_req req = अणुपूर्ण;
	काष्ठा gdma_general_resp resp = अणुपूर्ण;
	काष्ठा device *dev = gc->dev;
	पूर्णांक err;

	mutex_lock(&gc->eq_test_event_mutex);

	init_completion(&gc->eq_test_event);
	gc->test_event_eq_id = INVALID_QUEUE_ID;

	mana_gd_init_req_hdr(&req.hdr, GDMA_GENERATE_TEST_EQE,
			     माप(req), माप(resp));

	req.hdr.dev_id = eq->gdma_dev->dev_id;
	req.queue_index = eq->id;

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err) अणु
		dev_err(dev, "test_eq failed: %d\n", err);
		जाओ out;
	पूर्ण

	err = -EPROTO;

	अगर (resp.hdr.status) अणु
		dev_err(dev, "test_eq failed: 0x%x\n", resp.hdr.status);
		जाओ out;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&gc->eq_test_event, 30 * HZ)) अणु
		dev_err(dev, "test_eq timed out on queue %d\n", eq->id);
		जाओ out;
	पूर्ण

	अगर (eq->id != gc->test_event_eq_id) अणु
		dev_err(dev, "test_eq got an event on wrong queue %d (%d)\n",
			gc->test_event_eq_id, eq->id);
		जाओ out;
	पूर्ण

	err = 0;
out:
	mutex_unlock(&gc->eq_test_event_mutex);
	वापस err;
पूर्ण

अटल व्योम mana_gd_destroy_eq(काष्ठा gdma_context *gc, bool flush_evenets,
			       काष्ठा gdma_queue *queue)
अणु
	पूर्णांक err;

	अगर (flush_evenets) अणु
		err = mana_gd_test_eq(gc, queue);
		अगर (err)
			dev_warn(gc->dev, "Failed to flush EQ: %d\n", err);
	पूर्ण

	mana_gd_deregiser_irq(queue);

	अगर (mana_gd_is_mana(queue->gdma_dev)) अणु
		napi_disable(&queue->eq.napi);
		netअगर_napi_del(&queue->eq.napi);
	पूर्ण

	अगर (queue->eq.disable_needed)
		mana_gd_disable_queue(queue);
पूर्ण

अटल पूर्णांक mana_gd_create_eq(काष्ठा gdma_dev *gd,
			     स्थिर काष्ठा gdma_queue_spec *spec,
			     bool create_hwq, काष्ठा gdma_queue *queue)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा device *dev = gc->dev;
	u32 log2_num_entries;
	पूर्णांक err;

	queue->eq.msix_index = INVALID_PCI_MSIX_INDEX;

	log2_num_entries = ilog2(queue->queue_size / GDMA_EQE_SIZE);

	अगर (spec->eq.log2_throttle_limit > log2_num_entries) अणु
		dev_err(dev, "EQ throttling limit (%lu) > maximum EQE (%u)\n",
			spec->eq.log2_throttle_limit, log2_num_entries);
		वापस -EINVAL;
	पूर्ण

	err = mana_gd_रेजिस्टर_irq(queue, spec);
	अगर (err) अणु
		dev_err(dev, "Failed to register irq: %d\n", err);
		वापस err;
	पूर्ण

	queue->eq.callback = spec->eq.callback;
	queue->eq.context = spec->eq.context;
	queue->head |= INITIALIZED_OWNER_BIT(log2_num_entries);
	queue->eq.log2_throttle_limit = spec->eq.log2_throttle_limit ?: 1;

	अगर (create_hwq) अणु
		err = mana_gd_create_hw_eq(gc, queue);
		अगर (err)
			जाओ out;

		err = mana_gd_test_eq(gc, queue);
		अगर (err)
			जाओ out;
	पूर्ण

	वापस 0;
out:
	dev_err(dev, "Failed to create EQ: %d\n", err);
	mana_gd_destroy_eq(gc, false, queue);
	वापस err;
पूर्ण

अटल व्योम mana_gd_create_cq(स्थिर काष्ठा gdma_queue_spec *spec,
			      काष्ठा gdma_queue *queue)
अणु
	u32 log2_num_entries = ilog2(spec->queue_size / GDMA_CQE_SIZE);

	queue->head |= INITIALIZED_OWNER_BIT(log2_num_entries);
	queue->cq.parent = spec->cq.parent_eq;
	queue->cq.context = spec->cq.context;
	queue->cq.callback = spec->cq.callback;
पूर्ण

अटल व्योम mana_gd_destroy_cq(काष्ठा gdma_context *gc,
			       काष्ठा gdma_queue *queue)
अणु
	u32 id = queue->id;

	अगर (id >= gc->max_num_cqs)
		वापस;

	अगर (!gc->cq_table[id])
		वापस;

	gc->cq_table[id] = शून्य;
पूर्ण

पूर्णांक mana_gd_create_hwc_queue(काष्ठा gdma_dev *gd,
			     स्थिर काष्ठा gdma_queue_spec *spec,
			     काष्ठा gdma_queue **queue_ptr)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा gdma_mem_info *gmi;
	काष्ठा gdma_queue *queue;
	पूर्णांक err;

	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue)
		वापस -ENOMEM;

	gmi = &queue->mem_info;
	err = mana_gd_alloc_memory(gc, spec->queue_size, gmi);
	अगर (err)
		जाओ मुक्त_q;

	queue->head = 0;
	queue->tail = 0;
	queue->queue_mem_ptr = gmi->virt_addr;
	queue->queue_size = spec->queue_size;
	queue->monitor_avl_buf = spec->monitor_avl_buf;
	queue->type = spec->type;
	queue->gdma_dev = gd;

	अगर (spec->type == GDMA_EQ)
		err = mana_gd_create_eq(gd, spec, false, queue);
	अन्यथा अगर (spec->type == GDMA_CQ)
		mana_gd_create_cq(spec, queue);

	अगर (err)
		जाओ out;

	*queue_ptr = queue;
	वापस 0;
out:
	mana_gd_मुक्त_memory(gmi);
मुक्त_q:
	kमुक्त(queue);
	वापस err;
पूर्ण

अटल व्योम mana_gd_destroy_dma_region(काष्ठा gdma_context *gc, u64 gdma_region)
अणु
	काष्ठा gdma_destroy_dma_region_req req = अणुपूर्ण;
	काष्ठा gdma_general_resp resp = अणुपूर्ण;
	पूर्णांक err;

	अगर (gdma_region == GDMA_INVALID_DMA_REGION)
		वापस;

	mana_gd_init_req_hdr(&req.hdr, GDMA_DESTROY_DMA_REGION, माप(req),
			     माप(resp));
	req.gdma_region = gdma_region;

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status)
		dev_err(gc->dev, "Failed to destroy DMA region: %d, 0x%x\n",
			err, resp.hdr.status);
पूर्ण

अटल पूर्णांक mana_gd_create_dma_region(काष्ठा gdma_dev *gd,
				     काष्ठा gdma_mem_info *gmi)
अणु
	अचिन्हित पूर्णांक num_page = gmi->length / PAGE_SIZE;
	काष्ठा gdma_create_dma_region_req *req = शून्य;
	काष्ठा gdma_create_dma_region_resp resp = अणुपूर्ण;
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा hw_channel_context *hwc;
	u32 length = gmi->length;
	u32 req_msg_size;
	पूर्णांक err;
	पूर्णांक i;

	अगर (length < PAGE_SIZE || !is_घातer_of_2(length))
		वापस -EINVAL;

	अगर (offset_in_page(gmi->virt_addr) != 0)
		वापस -EINVAL;

	hwc = gc->hwc.driver_data;
	req_msg_size = माप(*req) + num_page * माप(u64);
	अगर (req_msg_size > hwc->max_req_msg_size)
		वापस -EINVAL;

	req = kzalloc(req_msg_size, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	mana_gd_init_req_hdr(&req->hdr, GDMA_CREATE_DMA_REGION,
			     req_msg_size, माप(resp));
	req->length = length;
	req->offset_in_page = 0;
	req->gdma_page_type = GDMA_PAGE_TYPE_4K;
	req->page_count = num_page;
	req->page_addr_list_len = num_page;

	क्रम (i = 0; i < num_page; i++)
		req->page_addr_list[i] = gmi->dma_handle +  i * PAGE_SIZE;

	err = mana_gd_send_request(gc, req_msg_size, req, माप(resp), &resp);
	अगर (err)
		जाओ out;

	अगर (resp.hdr.status || resp.gdma_region == GDMA_INVALID_DMA_REGION) अणु
		dev_err(gc->dev, "Failed to create DMA region: 0x%x\n",
			resp.hdr.status);
		err = -EPROTO;
		जाओ out;
	पूर्ण

	gmi->gdma_region = resp.gdma_region;
out:
	kमुक्त(req);
	वापस err;
पूर्ण

पूर्णांक mana_gd_create_mana_eq(काष्ठा gdma_dev *gd,
			   स्थिर काष्ठा gdma_queue_spec *spec,
			   काष्ठा gdma_queue **queue_ptr)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा gdma_mem_info *gmi;
	काष्ठा gdma_queue *queue;
	पूर्णांक err;

	अगर (spec->type != GDMA_EQ)
		वापस -EINVAL;

	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue)
		वापस -ENOMEM;

	gmi = &queue->mem_info;
	err = mana_gd_alloc_memory(gc, spec->queue_size, gmi);
	अगर (err)
		जाओ मुक्त_q;

	err = mana_gd_create_dma_region(gd, gmi);
	अगर (err)
		जाओ out;

	queue->head = 0;
	queue->tail = 0;
	queue->queue_mem_ptr = gmi->virt_addr;
	queue->queue_size = spec->queue_size;
	queue->monitor_avl_buf = spec->monitor_avl_buf;
	queue->type = spec->type;
	queue->gdma_dev = gd;

	err = mana_gd_create_eq(gd, spec, true, queue);
	अगर (err)
		जाओ out;

	*queue_ptr = queue;
	वापस 0;
out:
	mana_gd_मुक्त_memory(gmi);
मुक्त_q:
	kमुक्त(queue);
	वापस err;
पूर्ण

पूर्णांक mana_gd_create_mana_wq_cq(काष्ठा gdma_dev *gd,
			      स्थिर काष्ठा gdma_queue_spec *spec,
			      काष्ठा gdma_queue **queue_ptr)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा gdma_mem_info *gmi;
	काष्ठा gdma_queue *queue;
	पूर्णांक err;

	अगर (spec->type != GDMA_CQ && spec->type != GDMA_SQ &&
	    spec->type != GDMA_RQ)
		वापस -EINVAL;

	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue)
		वापस -ENOMEM;

	gmi = &queue->mem_info;
	err = mana_gd_alloc_memory(gc, spec->queue_size, gmi);
	अगर (err)
		जाओ मुक्त_q;

	err = mana_gd_create_dma_region(gd, gmi);
	अगर (err)
		जाओ out;

	queue->head = 0;
	queue->tail = 0;
	queue->queue_mem_ptr = gmi->virt_addr;
	queue->queue_size = spec->queue_size;
	queue->monitor_avl_buf = spec->monitor_avl_buf;
	queue->type = spec->type;
	queue->gdma_dev = gd;

	अगर (spec->type == GDMA_CQ)
		mana_gd_create_cq(spec, queue);

	*queue_ptr = queue;
	वापस 0;
out:
	mana_gd_मुक्त_memory(gmi);
मुक्त_q:
	kमुक्त(queue);
	वापस err;
पूर्ण

व्योम mana_gd_destroy_queue(काष्ठा gdma_context *gc, काष्ठा gdma_queue *queue)
अणु
	काष्ठा gdma_mem_info *gmi = &queue->mem_info;

	चयन (queue->type) अणु
	हाल GDMA_EQ:
		mana_gd_destroy_eq(gc, queue->eq.disable_needed, queue);
		अवरोध;

	हाल GDMA_CQ:
		mana_gd_destroy_cq(gc, queue);
		अवरोध;

	हाल GDMA_RQ:
		अवरोध;

	हाल GDMA_SQ:
		अवरोध;

	शेष:
		dev_err(gc->dev, "Can't destroy unknown queue: type=%d\n",
			queue->type);
		वापस;
	पूर्ण

	mana_gd_destroy_dma_region(gc, gmi->gdma_region);
	mana_gd_मुक्त_memory(gmi);
	kमुक्त(queue);
पूर्ण

पूर्णांक mana_gd_verअगरy_vf_version(काष्ठा pci_dev *pdev)
अणु
	काष्ठा gdma_context *gc = pci_get_drvdata(pdev);
	काष्ठा gdma_verअगरy_ver_resp resp = अणुपूर्ण;
	काष्ठा gdma_verअगरy_ver_req req = अणुपूर्ण;
	पूर्णांक err;

	mana_gd_init_req_hdr(&req.hdr, GDMA_VERIFY_VF_DRIVER_VERSION,
			     माप(req), माप(resp));

	req.protocol_ver_min = GDMA_PROTOCOL_FIRST;
	req.protocol_ver_max = GDMA_PROTOCOL_LAST;

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status) अणु
		dev_err(gc->dev, "VfVerifyVersionOutput: %d, status=0x%x\n",
			err, resp.hdr.status);
		वापस err ? err : -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mana_gd_रेजिस्टर_device(काष्ठा gdma_dev *gd)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा gdma_रेजिस्टर_device_resp resp = अणुपूर्ण;
	काष्ठा gdma_general_req req = अणुपूर्ण;
	पूर्णांक err;

	gd->pdid = INVALID_PDID;
	gd->करोorbell = INVALID_DOORBELL;
	gd->gpa_mkey = INVALID_MEM_KEY;

	mana_gd_init_req_hdr(&req.hdr, GDMA_REGISTER_DEVICE, माप(req),
			     माप(resp));

	req.hdr.dev_id = gd->dev_id;

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status) अणु
		dev_err(gc->dev, "gdma_register_device_resp failed: %d, 0x%x\n",
			err, resp.hdr.status);
		वापस err ? err : -EPROTO;
	पूर्ण

	gd->pdid = resp.pdid;
	gd->gpa_mkey = resp.gpa_mkey;
	gd->करोorbell = resp.db_id;

	वापस 0;
पूर्ण

पूर्णांक mana_gd_deरेजिस्टर_device(काष्ठा gdma_dev *gd)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा gdma_general_resp resp = अणुपूर्ण;
	काष्ठा gdma_general_req req = अणुपूर्ण;
	पूर्णांक err;

	अगर (gd->pdid == INVALID_PDID)
		वापस -EINVAL;

	mana_gd_init_req_hdr(&req.hdr, GDMA_DEREGISTER_DEVICE, माप(req),
			     माप(resp));

	req.hdr.dev_id = gd->dev_id;

	err = mana_gd_send_request(gc, माप(req), &req, माप(resp), &resp);
	अगर (err || resp.hdr.status) अणु
		dev_err(gc->dev, "Failed to deregister device: %d, 0x%x\n",
			err, resp.hdr.status);
		अगर (!err)
			err = -EPROTO;
	पूर्ण

	gd->pdid = INVALID_PDID;
	gd->करोorbell = INVALID_DOORBELL;
	gd->gpa_mkey = INVALID_MEM_KEY;

	वापस err;
पूर्ण

u32 mana_gd_wq_avail_space(काष्ठा gdma_queue *wq)
अणु
	u32 used_space = (wq->head - wq->tail) * GDMA_WQE_BU_SIZE;
	u32 wq_size = wq->queue_size;

	WARN_ON_ONCE(used_space > wq_size);

	वापस wq_size - used_space;
पूर्ण

u8 *mana_gd_get_wqe_ptr(स्थिर काष्ठा gdma_queue *wq, u32 wqe_offset)
अणु
	u32 offset = (wqe_offset * GDMA_WQE_BU_SIZE) & (wq->queue_size - 1);

	WARN_ON_ONCE((offset + GDMA_WQE_BU_SIZE) > wq->queue_size);

	वापस wq->queue_mem_ptr + offset;
पूर्ण

अटल u32 mana_gd_ग_लिखो_client_oob(स्थिर काष्ठा gdma_wqe_request *wqe_req,
				    क्रमागत gdma_queue_type q_type,
				    u32 client_oob_size, u32 sgl_data_size,
				    u8 *wqe_ptr)
अणु
	bool oob_in_sgl = !!(wqe_req->flags & GDMA_WR_OOB_IN_SGL);
	bool pad_data = !!(wqe_req->flags & GDMA_WR_PAD_BY_SGE0);
	काष्ठा gdma_wqe *header = (काष्ठा gdma_wqe *)wqe_ptr;
	u8 *ptr;

	स_रखो(header, 0, माप(काष्ठा gdma_wqe));
	header->num_sge = wqe_req->num_sge;
	header->अंतरभूत_oob_size_भाग4 = client_oob_size / माप(u32);

	अगर (oob_in_sgl) अणु
		WARN_ON_ONCE(!pad_data || wqe_req->num_sge < 2);

		header->client_oob_in_sgl = 1;

		अगर (pad_data)
			header->last_vbytes = wqe_req->sgl[0].size;
	पूर्ण

	अगर (q_type == GDMA_SQ)
		header->client_data_unit = wqe_req->client_data_unit;

	/* The size of gdma_wqe + client_oob_size must be less than or equal
	 * to one Basic Unit (i.e. 32 bytes), so the poपूर्णांकer can't go beyond
	 * the queue memory buffer boundary.
	 */
	ptr = wqe_ptr + माप(header);

	अगर (wqe_req->अंतरभूत_oob_data && wqe_req->अंतरभूत_oob_size > 0) अणु
		स_नकल(ptr, wqe_req->अंतरभूत_oob_data, wqe_req->अंतरभूत_oob_size);

		अगर (client_oob_size > wqe_req->अंतरभूत_oob_size)
			स_रखो(ptr + wqe_req->अंतरभूत_oob_size, 0,
			       client_oob_size - wqe_req->अंतरभूत_oob_size);
	पूर्ण

	वापस माप(header) + client_oob_size;
पूर्ण

अटल व्योम mana_gd_ग_लिखो_sgl(काष्ठा gdma_queue *wq, u8 *wqe_ptr,
			      स्थिर काष्ठा gdma_wqe_request *wqe_req)
अणु
	u32 sgl_size = माप(काष्ठा gdma_sge) * wqe_req->num_sge;
	स्थिर u8 *address = (u8 *)wqe_req->sgl;
	u8 *base_ptr, *end_ptr;
	u32 माप_प्रकारo_end;

	base_ptr = wq->queue_mem_ptr;
	end_ptr = base_ptr + wq->queue_size;
	माप_प्रकारo_end = (u32)(end_ptr - wqe_ptr);

	अगर (माप_प्रकारo_end < sgl_size) अणु
		स_नकल(wqe_ptr, address, माप_प्रकारo_end);

		wqe_ptr = base_ptr;
		address += माप_प्रकारo_end;
		sgl_size -= माप_प्रकारo_end;
	पूर्ण

	स_नकल(wqe_ptr, address, sgl_size);
पूर्ण

पूर्णांक mana_gd_post_work_request(काष्ठा gdma_queue *wq,
			      स्थिर काष्ठा gdma_wqe_request *wqe_req,
			      काष्ठा gdma_posted_wqe_info *wqe_info)
अणु
	u32 client_oob_size = wqe_req->अंतरभूत_oob_size;
	काष्ठा gdma_context *gc;
	u32 sgl_data_size;
	u32 max_wqe_size;
	u32 wqe_size;
	u8 *wqe_ptr;

	अगर (wqe_req->num_sge == 0)
		वापस -EINVAL;

	अगर (wq->type == GDMA_RQ) अणु
		अगर (client_oob_size != 0)
			वापस -EINVAL;

		client_oob_size = INLINE_OOB_SMALL_SIZE;

		max_wqe_size = GDMA_MAX_RQE_SIZE;
	पूर्ण अन्यथा अणु
		अगर (client_oob_size != INLINE_OOB_SMALL_SIZE &&
		    client_oob_size != INLINE_OOB_LARGE_SIZE)
			वापस -EINVAL;

		max_wqe_size = GDMA_MAX_SQE_SIZE;
	पूर्ण

	sgl_data_size = माप(काष्ठा gdma_sge) * wqe_req->num_sge;
	wqe_size = ALIGN(माप(काष्ठा gdma_wqe) + client_oob_size +
			 sgl_data_size, GDMA_WQE_BU_SIZE);
	अगर (wqe_size > max_wqe_size)
		वापस -EINVAL;

	अगर (wq->monitor_avl_buf && wqe_size > mana_gd_wq_avail_space(wq)) अणु
		gc = wq->gdma_dev->gdma_context;
		dev_err(gc->dev, "unsuccessful flow control!\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (wqe_info)
		wqe_info->wqe_size_in_bu = wqe_size / GDMA_WQE_BU_SIZE;

	wqe_ptr = mana_gd_get_wqe_ptr(wq, wq->head);
	wqe_ptr += mana_gd_ग_लिखो_client_oob(wqe_req, wq->type, client_oob_size,
					    sgl_data_size, wqe_ptr);
	अगर (wqe_ptr >= (u8 *)wq->queue_mem_ptr + wq->queue_size)
		wqe_ptr -= wq->queue_size;

	mana_gd_ग_लिखो_sgl(wq, wqe_ptr, wqe_req);

	wq->head += wqe_size / GDMA_WQE_BU_SIZE;

	वापस 0;
पूर्ण

पूर्णांक mana_gd_post_and_ring(काष्ठा gdma_queue *queue,
			  स्थिर काष्ठा gdma_wqe_request *wqe_req,
			  काष्ठा gdma_posted_wqe_info *wqe_info)
अणु
	काष्ठा gdma_context *gc = queue->gdma_dev->gdma_context;
	पूर्णांक err;

	err = mana_gd_post_work_request(queue, wqe_req, wqe_info);
	अगर (err)
		वापस err;

	mana_gd_wq_ring_करोorbell(gc, queue);

	वापस 0;
पूर्ण

अटल पूर्णांक mana_gd_पढ़ो_cqe(काष्ठा gdma_queue *cq, काष्ठा gdma_comp *comp)
अणु
	अचिन्हित पूर्णांक num_cqe = cq->queue_size / माप(काष्ठा gdma_cqe);
	काष्ठा gdma_cqe *cq_cqe = cq->queue_mem_ptr;
	u32 owner_bits, new_bits, old_bits;
	काष्ठा gdma_cqe *cqe;

	cqe = &cq_cqe[cq->head % num_cqe];
	owner_bits = cqe->cqe_info.owner_bits;

	old_bits = (cq->head / num_cqe - 1) & GDMA_CQE_OWNER_MASK;
	/* Return 0 अगर no more entries. */
	अगर (owner_bits == old_bits)
		वापस 0;

	new_bits = (cq->head / num_cqe) & GDMA_CQE_OWNER_MASK;
	/* Return -1 अगर overflow detected. */
	अगर (owner_bits != new_bits)
		वापस -1;

	comp->wq_num = cqe->cqe_info.wq_num;
	comp->is_sq = cqe->cqe_info.is_sq;
	स_नकल(comp->cqe_data, cqe->cqe_data, GDMA_COMP_DATA_SIZE);

	वापस 1;
पूर्ण

पूर्णांक mana_gd_poll_cq(काष्ठा gdma_queue *cq, काष्ठा gdma_comp *comp, पूर्णांक num_cqe)
अणु
	पूर्णांक cqe_idx;
	पूर्णांक ret;

	क्रम (cqe_idx = 0; cqe_idx < num_cqe; cqe_idx++) अणु
		ret = mana_gd_पढ़ो_cqe(cq, &comp[cqe_idx]);

		अगर (ret < 0) अणु
			cq->head -= cqe_idx;
			वापस ret;
		पूर्ण

		अगर (ret == 0)
			अवरोध;

		cq->head++;
	पूर्ण

	वापस cqe_idx;
पूर्ण

अटल irqवापस_t mana_gd_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा gdma_irq_context *gic = arg;

	अगर (gic->handler)
		gic->handler(gic->arg);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mana_gd_alloc_res_map(u32 res_avail, काष्ठा gdma_resource *r)
अणु
	r->map = biपंचांगap_zalloc(res_avail, GFP_KERNEL);
	अगर (!r->map)
		वापस -ENOMEM;

	r->size = res_avail;
	spin_lock_init(&r->lock);

	वापस 0;
पूर्ण

व्योम mana_gd_मुक्त_res_map(काष्ठा gdma_resource *r)
अणु
	biपंचांगap_मुक्त(r->map);
	r->map = शून्य;
	r->size = 0;
पूर्ण

अटल पूर्णांक mana_gd_setup_irqs(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक max_queues_per_port = num_online_cpus();
	काष्ठा gdma_context *gc = pci_get_drvdata(pdev);
	काष्ठा gdma_irq_context *gic;
	अचिन्हित पूर्णांक max_irqs;
	पूर्णांक nvec, irq;
	पूर्णांक err, i, j;

	अगर (max_queues_per_port > MANA_MAX_NUM_QUEUES)
		max_queues_per_port = MANA_MAX_NUM_QUEUES;

	max_irqs = max_queues_per_port * MAX_PORTS_IN_MANA_DEV;

	/* Need 1 पूर्णांकerrupt क्रम the Hardware communication Channel (HWC) */
	max_irqs++;

	nvec = pci_alloc_irq_vectors(pdev, 2, max_irqs, PCI_IRQ_MSIX);
	अगर (nvec < 0)
		वापस nvec;

	gc->irq_contexts = kसुस्मृति(nvec, माप(काष्ठा gdma_irq_context),
				   GFP_KERNEL);
	अगर (!gc->irq_contexts) अणु
		err = -ENOMEM;
		जाओ मुक्त_irq_vector;
	पूर्ण

	क्रम (i = 0; i < nvec; i++) अणु
		gic = &gc->irq_contexts[i];
		gic->handler = शून्य;
		gic->arg = शून्य;

		irq = pci_irq_vector(pdev, i);
		अगर (irq < 0) अणु
			err = irq;
			जाओ मुक्त_irq;
		पूर्ण

		err = request_irq(irq, mana_gd_पूर्णांकr, 0, "mana_intr", gic);
		अगर (err)
			जाओ मुक्त_irq;
	पूर्ण

	err = mana_gd_alloc_res_map(nvec, &gc->msix_resource);
	अगर (err)
		जाओ मुक्त_irq;

	gc->max_num_msix = nvec;
	gc->num_msix_usable = nvec;

	वापस 0;

मुक्त_irq:
	क्रम (j = i - 1; j >= 0; j--) अणु
		irq = pci_irq_vector(pdev, j);
		gic = &gc->irq_contexts[j];
		मुक्त_irq(irq, gic);
	पूर्ण

	kमुक्त(gc->irq_contexts);
	gc->irq_contexts = शून्य;
मुक्त_irq_vector:
	pci_मुक्त_irq_vectors(pdev);
	वापस err;
पूर्ण

अटल व्योम mana_gd_हटाओ_irqs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा gdma_context *gc = pci_get_drvdata(pdev);
	काष्ठा gdma_irq_context *gic;
	पूर्णांक irq, i;

	अगर (gc->max_num_msix < 1)
		वापस;

	mana_gd_मुक्त_res_map(&gc->msix_resource);

	क्रम (i = 0; i < gc->max_num_msix; i++) अणु
		irq = pci_irq_vector(pdev, i);
		अगर (irq < 0)
			जारी;

		gic = &gc->irq_contexts[i];
		मुक्त_irq(irq, gic);
	पूर्ण

	pci_मुक्त_irq_vectors(pdev);

	gc->max_num_msix = 0;
	gc->num_msix_usable = 0;
	kमुक्त(gc->irq_contexts);
	gc->irq_contexts = शून्य;
पूर्ण

अटल पूर्णांक mana_gd_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा gdma_context *gc;
	व्योम __iomem *bar0_va;
	पूर्णांक bar = 0;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस -ENXIO;

	pci_set_master(pdev);

	err = pci_request_regions(pdev, "mana");
	अगर (err)
		जाओ disable_dev;

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err)
		जाओ release_region;

	err = -ENOMEM;
	gc = vzalloc(माप(*gc));
	अगर (!gc)
		जाओ release_region;

	bar0_va = pci_iomap(pdev, bar, 0);
	अगर (!bar0_va)
		जाओ मुक्त_gc;

	gc->bar0_va = bar0_va;
	gc->dev = &pdev->dev;

	pci_set_drvdata(pdev, gc);

	mana_gd_init_रेजिस्टरs(pdev);

	mana_smc_init(&gc->shm_channel, gc->dev, gc->shm_base);

	err = mana_gd_setup_irqs(pdev);
	अगर (err)
		जाओ unmap_bar;

	mutex_init(&gc->eq_test_event_mutex);

	err = mana_hwc_create_channel(gc);
	अगर (err)
		जाओ हटाओ_irq;

	err = mana_gd_verअगरy_vf_version(pdev);
	अगर (err)
		जाओ हटाओ_irq;

	err = mana_gd_query_max_resources(pdev);
	अगर (err)
		जाओ हटाओ_irq;

	err = mana_gd_detect_devices(pdev);
	अगर (err)
		जाओ हटाओ_irq;

	err = mana_probe(&gc->mana);
	अगर (err)
		जाओ clean_up_gdma;

	वापस 0;

clean_up_gdma:
	mana_hwc_destroy_channel(gc);
	vमुक्त(gc->cq_table);
	gc->cq_table = शून्य;
हटाओ_irq:
	mana_gd_हटाओ_irqs(pdev);
unmap_bar:
	pci_iounmap(pdev, bar0_va);
मुक्त_gc:
	vमुक्त(gc);
release_region:
	pci_release_regions(pdev);
disable_dev:
	pci_clear_master(pdev);
	pci_disable_device(pdev);
	dev_err(&pdev->dev, "gdma probe failed: err = %d\n", err);
	वापस err;
पूर्ण

अटल व्योम mana_gd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा gdma_context *gc = pci_get_drvdata(pdev);

	mana_हटाओ(&gc->mana);

	mana_hwc_destroy_channel(gc);
	vमुक्त(gc->cq_table);
	gc->cq_table = शून्य;

	mana_gd_हटाओ_irqs(pdev);

	pci_iounmap(pdev, gc->bar0_va);

	vमुक्त(gc);

	pci_release_regions(pdev);
	pci_clear_master(pdev);
	pci_disable_device(pdev);
पूर्ण

#अगर_अघोषित PCI_VENDOR_ID_MICROSOFT
#घोषणा PCI_VENDOR_ID_MICROSOFT 0x1414
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id mana_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MICROSOFT, 0x00BA) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver mana_driver = अणु
	.name		= "mana",
	.id_table	= mana_id_table,
	.probe		= mana_gd_probe,
	.हटाओ		= mana_gd_हटाओ,
पूर्ण;

module_pci_driver(mana_driver);

MODULE_DEVICE_TABLE(pci, mana_id_table);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Microsoft Azure Network Adapter driver");
