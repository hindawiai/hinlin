<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"

#समावेश <linux/slab.h>

/**
 * काष्ठा hl_eqe_work - This काष्ठाure is used to schedule work of EQ
 *                      entry and cpucp_reset event
 *
 * @eq_work:          workqueue object to run when EQ entry is received
 * @hdev:             poपूर्णांकer to device काष्ठाure
 * @eq_entry:         copy of the EQ entry
 */
काष्ठा hl_eqe_work अणु
	काष्ठा work_काष्ठा	eq_work;
	काष्ठा hl_device	*hdev;
	काष्ठा hl_eq_entry	eq_entry;
पूर्ण;

/**
 * hl_cq_inc_ptr - increment ci or pi of cq
 *
 * @ptr: the current ci or pi value of the completion queue
 *
 * Increment ptr by 1. If it reaches the number of completion queue
 * entries, set it to 0
 */
अंतरभूत u32 hl_cq_inc_ptr(u32 ptr)
अणु
	ptr++;
	अगर (unlikely(ptr == HL_CQ_LENGTH))
		ptr = 0;
	वापस ptr;
पूर्ण

/**
 * hl_eq_inc_ptr - increment ci of eq
 *
 * @ptr: the current ci value of the event queue
 *
 * Increment ptr by 1. If it reaches the number of event queue
 * entries, set it to 0
 */
अटल अंतरभूत u32 hl_eq_inc_ptr(u32 ptr)
अणु
	ptr++;
	अगर (unlikely(ptr == HL_EQ_LENGTH))
		ptr = 0;
	वापस ptr;
पूर्ण

अटल व्योम irq_handle_eqe(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hl_eqe_work *eqe_work = container_of(work, काष्ठा hl_eqe_work,
							eq_work);
	काष्ठा hl_device *hdev = eqe_work->hdev;

	hdev->asic_funcs->handle_eqe(hdev, &eqe_work->eq_entry);

	kमुक्त(eqe_work);
पूर्ण

/**
 * hl_irq_handler_cq - irq handler क्रम completion queue
 *
 * @irq: irq number
 * @arg: poपूर्णांकer to completion queue काष्ठाure
 *
 */
irqवापस_t hl_irq_handler_cq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hl_cq *cq = arg;
	काष्ठा hl_device *hdev = cq->hdev;
	काष्ठा hl_hw_queue *queue;
	काष्ठा hl_cs_job *job;
	bool shaकरोw_index_valid;
	u16 shaकरोw_index;
	काष्ठा hl_cq_entry *cq_entry, *cq_base;

	अगर (hdev->disabled) अणु
		dev_dbg(hdev->dev,
			"Device disabled but received IRQ %d for CQ %d\n",
			irq, cq->hw_queue_id);
		वापस IRQ_HANDLED;
	पूर्ण

	cq_base = cq->kernel_address;

	जबतक (1) अणु
		bool entry_पढ़ोy = ((le32_to_cpu(cq_base[cq->ci].data) &
					CQ_ENTRY_READY_MASK)
						>> CQ_ENTRY_READY_SHIFT);

		अगर (!entry_पढ़ोy)
			अवरोध;

		cq_entry = (काष्ठा hl_cq_entry *) &cq_base[cq->ci];

		/* Make sure we पढ़ो CQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();

		shaकरोw_index_valid = ((le32_to_cpu(cq_entry->data) &
					CQ_ENTRY_SHADOW_INDEX_VALID_MASK)
					>> CQ_ENTRY_SHADOW_INDEX_VALID_SHIFT);

		shaकरोw_index = (u16) ((le32_to_cpu(cq_entry->data) &
					CQ_ENTRY_SHADOW_INDEX_MASK)
					>> CQ_ENTRY_SHADOW_INDEX_SHIFT);

		queue = &hdev->kernel_queues[cq->hw_queue_id];

		अगर ((shaकरोw_index_valid) && (!hdev->disabled)) अणु
			job = queue->shaकरोw_queue[hl_pi_2_offset(shaकरोw_index)];
			queue_work(hdev->cq_wq[cq->cq_idx], &job->finish_work);
		पूर्ण

		atomic_inc(&queue->ci);

		/* Clear CQ entry पढ़ोy bit */
		cq_entry->data = cpu_to_le32(le32_to_cpu(cq_entry->data) &
						~CQ_ENTRY_READY_MASK);

		cq->ci = hl_cq_inc_ptr(cq->ci);

		/* Increment मुक्त slots */
		atomic_inc(&cq->मुक्त_slots_cnt);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम handle_user_cq(काष्ठा hl_device *hdev,
			काष्ठा hl_user_पूर्णांकerrupt *user_cq)
अणु
	काष्ठा hl_user_pending_पूर्णांकerrupt *pend;

	spin_lock(&user_cq->रुको_list_lock);
	list_क्रम_each_entry(pend, &user_cq->रुको_list_head, रुको_list_node)
		complete_all(&pend->fence.completion);
	spin_unlock(&user_cq->रुको_list_lock);
पूर्ण

/**
 * hl_irq_handler_user_cq - irq handler क्रम user completion queues
 *
 * @irq: irq number
 * @arg: poपूर्णांकer to user पूर्णांकerrupt काष्ठाure
 *
 */
irqवापस_t hl_irq_handler_user_cq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hl_user_पूर्णांकerrupt *user_cq = arg;
	काष्ठा hl_device *hdev = user_cq->hdev;

	dev_dbg(hdev->dev,
		"got user completion interrupt id %u",
		user_cq->पूर्णांकerrupt_id);

	/* Handle user cq पूर्णांकerrupts रेजिस्टरed on all पूर्णांकerrupts */
	handle_user_cq(hdev, &hdev->common_user_पूर्णांकerrupt);

	/* Handle user cq पूर्णांकerrupts रेजिस्टरed on this specअगरic पूर्णांकerrupt */
	handle_user_cq(hdev, user_cq);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * hl_irq_handler_शेष - शेष irq handler
 *
 * @irq: irq number
 * @arg: poपूर्णांकer to user पूर्णांकerrupt काष्ठाure
 *
 */
irqवापस_t hl_irq_handler_शेष(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hl_user_पूर्णांकerrupt *user_पूर्णांकerrupt = arg;
	काष्ठा hl_device *hdev = user_पूर्णांकerrupt->hdev;
	u32 पूर्णांकerrupt_id = user_पूर्णांकerrupt->पूर्णांकerrupt_id;

	dev_err(hdev->dev,
		"got invalid user interrupt %u",
		पूर्णांकerrupt_id);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * hl_irq_handler_eq - irq handler क्रम event queue
 *
 * @irq: irq number
 * @arg: poपूर्णांकer to event queue काष्ठाure
 *
 */
irqवापस_t hl_irq_handler_eq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hl_eq *eq = arg;
	काष्ठा hl_device *hdev = eq->hdev;
	काष्ठा hl_eq_entry *eq_entry;
	काष्ठा hl_eq_entry *eq_base;
	काष्ठा hl_eqe_work *handle_eqe_work;

	eq_base = eq->kernel_address;

	जबतक (1) अणु
		bool entry_पढ़ोy =
			((le32_to_cpu(eq_base[eq->ci].hdr.ctl) &
				EQ_CTL_READY_MASK) >> EQ_CTL_READY_SHIFT);

		अगर (!entry_पढ़ोy)
			अवरोध;

		eq_entry = &eq_base[eq->ci];

		/*
		 * Make sure we पढ़ो EQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();

		अगर (hdev->disabled) अणु
			dev_warn(hdev->dev,
				"Device disabled but received IRQ %d for EQ\n",
					irq);
			जाओ skip_irq;
		पूर्ण

		handle_eqe_work = kदो_स्मृति(माप(*handle_eqe_work), GFP_ATOMIC);
		अगर (handle_eqe_work) अणु
			INIT_WORK(&handle_eqe_work->eq_work, irq_handle_eqe);
			handle_eqe_work->hdev = hdev;

			स_नकल(&handle_eqe_work->eq_entry, eq_entry,
					माप(*eq_entry));

			queue_work(hdev->eq_wq, &handle_eqe_work->eq_work);
		पूर्ण
skip_irq:
		/* Clear EQ entry पढ़ोy bit */
		eq_entry->hdr.ctl =
			cpu_to_le32(le32_to_cpu(eq_entry->hdr.ctl) &
							~EQ_CTL_READY_MASK);

		eq->ci = hl_eq_inc_ptr(eq->ci);

		hdev->asic_funcs->update_eq_ci(hdev, eq->ci);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * hl_cq_init - मुख्य initialization function क्रम an cq object
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @q: poपूर्णांकer to cq काष्ठाure
 * @hw_queue_id: The H/W queue ID this completion queue beदीर्घs to
 *
 * Allocate dma-able memory क्रम the completion queue and initialize fields
 * Returns 0 on success
 */
पूर्णांक hl_cq_init(काष्ठा hl_device *hdev, काष्ठा hl_cq *q, u32 hw_queue_id)
अणु
	व्योम *p;

	p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev, HL_CQ_SIZE_IN_BYTES,
				&q->bus_address, GFP_KERNEL | __GFP_ZERO);
	अगर (!p)
		वापस -ENOMEM;

	q->hdev = hdev;
	q->kernel_address = p;
	q->hw_queue_id = hw_queue_id;
	q->ci = 0;
	q->pi = 0;

	atomic_set(&q->मुक्त_slots_cnt, HL_CQ_LENGTH);

	वापस 0;
पूर्ण

/**
 * hl_cq_fini - destroy completion queue
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @q: poपूर्णांकer to cq काष्ठाure
 *
 * Free the completion queue memory
 */
व्योम hl_cq_fini(काष्ठा hl_device *hdev, काष्ठा hl_cq *q)
अणु
	hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev, HL_CQ_SIZE_IN_BYTES,
						 q->kernel_address,
						 q->bus_address);
पूर्ण

व्योम hl_cq_reset(काष्ठा hl_device *hdev, काष्ठा hl_cq *q)
अणु
	q->ci = 0;
	q->pi = 0;

	atomic_set(&q->मुक्त_slots_cnt, HL_CQ_LENGTH);

	/*
	 * It's not enough to just reset the PI/CI because the H/W may have
	 * written valid completion entries beक्रमe it was halted and thereक्रमe
	 * we need to clean the actual queues so we won't process old entries
	 * when the device is operational again
	 */

	स_रखो(q->kernel_address, 0, HL_CQ_SIZE_IN_BYTES);
पूर्ण

/**
 * hl_eq_init - मुख्य initialization function क्रम an event queue object
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @q: poपूर्णांकer to eq काष्ठाure
 *
 * Allocate dma-able memory क्रम the event queue and initialize fields
 * Returns 0 on success
 */
पूर्णांक hl_eq_init(काष्ठा hl_device *hdev, काष्ठा hl_eq *q)
अणु
	व्योम *p;

	p = hdev->asic_funcs->cpu_accessible_dma_pool_alloc(hdev,
							HL_EQ_SIZE_IN_BYTES,
							&q->bus_address);
	अगर (!p)
		वापस -ENOMEM;

	q->hdev = hdev;
	q->kernel_address = p;
	q->ci = 0;

	वापस 0;
पूर्ण

/**
 * hl_eq_fini - destroy event queue
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @q: poपूर्णांकer to eq काष्ठाure
 *
 * Free the event queue memory
 */
व्योम hl_eq_fini(काष्ठा hl_device *hdev, काष्ठा hl_eq *q)
अणु
	flush_workqueue(hdev->eq_wq);

	hdev->asic_funcs->cpu_accessible_dma_pool_मुक्त(hdev,
					HL_EQ_SIZE_IN_BYTES,
					q->kernel_address);
पूर्ण

व्योम hl_eq_reset(काष्ठा hl_device *hdev, काष्ठा hl_eq *q)
अणु
	q->ci = 0;

	/*
	 * It's not enough to just reset the PI/CI because the H/W may have
	 * written valid completion entries beक्रमe it was halted and thereक्रमe
	 * we need to clean the actual queues so we won't process old entries
	 * when the device is operational again
	 */

	स_रखो(q->kernel_address, 0, HL_EQ_SIZE_IN_BYTES);
पूर्ण
