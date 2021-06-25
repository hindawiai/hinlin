<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"

#समावेश <linux/slab.h>

/*
 * hl_queue_add_ptr - add to pi or ci and checks अगर it wraps around
 *
 * @ptr: the current pi/ci value
 * @val: the amount to add
 *
 * Add val to ptr. It can go until twice the queue length.
 */
अंतरभूत u32 hl_hw_queue_add_ptr(u32 ptr, u16 val)
अणु
	ptr += val;
	ptr &= ((HL_QUEUE_LENGTH << 1) - 1);
	वापस ptr;
पूर्ण
अटल अंतरभूत पूर्णांक queue_ci_get(atomic_t *ci, u32 queue_len)
अणु
	वापस atomic_पढ़ो(ci) & ((queue_len << 1) - 1);
पूर्ण

अटल अंतरभूत पूर्णांक queue_मुक्त_slots(काष्ठा hl_hw_queue *q, u32 queue_len)
अणु
	पूर्णांक delta = (q->pi - queue_ci_get(&q->ci, queue_len));

	अगर (delta >= 0)
		वापस (queue_len - delta);
	अन्यथा
		वापस (असल(delta) - queue_len);
पूर्ण

व्योम hl_hw_queue_update_ci(काष्ठा hl_cs *cs)
अणु
	काष्ठा hl_device *hdev = cs->ctx->hdev;
	काष्ठा hl_hw_queue *q;
	पूर्णांक i;

	अगर (hdev->disabled)
		वापस;

	q = &hdev->kernel_queues[0];

	/* There are no पूर्णांकernal queues अगर H/W queues are being used */
	अगर (!hdev->asic_prop.max_queues || q->queue_type == QUEUE_TYPE_HW)
		वापस;

	/* We must increment CI क्रम every queue that will never get a
	 * completion, there are 2 scenarios this can happen:
	 * 1. All queues of a non completion CS will never get a completion.
	 * 2. Internal queues never माला_लो completion.
	 */
	क्रम (i = 0 ; i < hdev->asic_prop.max_queues ; i++, q++) अणु
		अगर (!cs_needs_completion(cs) || q->queue_type == QUEUE_TYPE_INT)
			atomic_add(cs->jobs_in_queue_cnt[i], &q->ci);
	पूर्ण
पूर्ण

/*
 * ext_and_hw_queue_submit_bd() - Submit a buffer descriptor to an बाह्यal or a
 *                                H/W queue.
 * @hdev: poपूर्णांकer to habanaद_असल device काष्ठाure
 * @q: poपूर्णांकer to habanaद_असल queue काष्ठाure
 * @ctl: BD's control word
 * @len: BD's length
 * @ptr: BD's poपूर्णांकer
 *
 * This function assumes there is enough space on the queue to submit a new
 * BD to it. It initializes the next BD and calls the device specअगरic
 * function to set the pi (and करोorbell)
 *
 * This function must be called when the scheduler mutex is taken
 *
 */
अटल व्योम ext_and_hw_queue_submit_bd(काष्ठा hl_device *hdev,
			काष्ठा hl_hw_queue *q, u32 ctl, u32 len, u64 ptr)
अणु
	काष्ठा hl_bd *bd;

	bd = q->kernel_address;
	bd += hl_pi_2_offset(q->pi);
	bd->ctl = cpu_to_le32(ctl);
	bd->len = cpu_to_le32(len);
	bd->ptr = cpu_to_le64(ptr);

	q->pi = hl_queue_inc_ptr(q->pi);
	hdev->asic_funcs->ring_करोorbell(hdev, q->hw_queue_id, q->pi);
पूर्ण

/*
 * ext_queue_sanity_checks - perक्रमm some sanity checks on बाह्यal queue
 *
 * @hdev              : poपूर्णांकer to hl_device काष्ठाure
 * @q                 :	poपूर्णांकer to hl_hw_queue काष्ठाure
 * @num_of_entries    : how many entries to check क्रम space
 * @reserve_cq_entry  :	whether to reserve an entry in the cq
 *
 * H/W queues spinlock should be taken beक्रमe calling this function
 *
 * Perक्रमm the following:
 * - Make sure we have enough space in the h/w queue
 * - Make sure we have enough space in the completion queue
 * - Reserve space in the completion queue (needs to be reversed अगर there
 *   is a failure करोwn the road beक्रमe the actual submission of work). Only
 *   करो this action अगर reserve_cq_entry is true
 *
 */
अटल पूर्णांक ext_queue_sanity_checks(काष्ठा hl_device *hdev,
				काष्ठा hl_hw_queue *q, पूर्णांक num_of_entries,
				bool reserve_cq_entry)
अणु
	atomic_t *मुक्त_slots =
			&hdev->completion_queue[q->cq_id].मुक्त_slots_cnt;
	पूर्णांक मुक्त_slots_cnt;

	/* Check we have enough space in the queue */
	मुक्त_slots_cnt = queue_मुक्त_slots(q, HL_QUEUE_LENGTH);

	अगर (मुक्त_slots_cnt < num_of_entries) अणु
		dev_dbg(hdev->dev, "Queue %d doesn't have room for %d CBs\n",
			q->hw_queue_id, num_of_entries);
		वापस -EAGAIN;
	पूर्ण

	अगर (reserve_cq_entry) अणु
		/*
		 * Check we have enough space in the completion queue
		 * Add -1 to counter (decrement) unless counter was alपढ़ोy 0
		 * In that हाल, CQ is full so we can't submit a new CB because
		 * we won't get ack on its completion
		 * atomic_add_unless will वापस 0 अगर counter was alपढ़ोy 0
		 */
		अगर (atomic_add_negative(num_of_entries * -1, मुक्त_slots)) अणु
			dev_dbg(hdev->dev, "No space for %d on CQ %d\n",
				num_of_entries, q->hw_queue_id);
			atomic_add(num_of_entries, मुक्त_slots);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * पूर्णांक_queue_sanity_checks - perक्रमm some sanity checks on पूर्णांकernal queue
 *
 * @hdev              : poपूर्णांकer to hl_device काष्ठाure
 * @q                 :	poपूर्णांकer to hl_hw_queue काष्ठाure
 * @num_of_entries    : how many entries to check क्रम space
 *
 * H/W queues spinlock should be taken beक्रमe calling this function
 *
 * Perक्रमm the following:
 * - Make sure we have enough space in the h/w queue
 *
 */
अटल पूर्णांक पूर्णांक_queue_sanity_checks(काष्ठा hl_device *hdev,
					काष्ठा hl_hw_queue *q,
					पूर्णांक num_of_entries)
अणु
	पूर्णांक मुक्त_slots_cnt;

	अगर (num_of_entries > q->पूर्णांक_queue_len) अणु
		dev_err(hdev->dev,
			"Cannot populate queue %u with %u jobs\n",
			q->hw_queue_id, num_of_entries);
		वापस -ENOMEM;
	पूर्ण

	/* Check we have enough space in the queue */
	मुक्त_slots_cnt = queue_मुक्त_slots(q, q->पूर्णांक_queue_len);

	अगर (मुक्त_slots_cnt < num_of_entries) अणु
		dev_dbg(hdev->dev, "Queue %d doesn't have room for %d CBs\n",
			q->hw_queue_id, num_of_entries);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * hw_queue_sanity_checks() - Make sure we have enough space in the h/w queue
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 * @q: Poपूर्णांकer to hl_hw_queue काष्ठाure.
 * @num_of_entries: How many entries to check क्रम space.
 *
 * Notice: We करो not reserve queue entries so this function mustn't be called
 *         more than once per CS क्रम the same queue
 *
 */
अटल पूर्णांक hw_queue_sanity_checks(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q,
					पूर्णांक num_of_entries)
अणु
	पूर्णांक मुक्त_slots_cnt;

	/* Check we have enough space in the queue */
	मुक्त_slots_cnt = queue_मुक्त_slots(q, HL_QUEUE_LENGTH);

	अगर (मुक्त_slots_cnt < num_of_entries) अणु
		dev_dbg(hdev->dev, "Queue %d doesn't have room for %d CBs\n",
			q->hw_queue_id, num_of_entries);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * hl_hw_queue_send_cb_no_cmpl - send a single CB (not a JOB) without completion
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 * @hw_queue_id: Queue's type
 * @cb_size: size of CB
 * @cb_ptr: poपूर्णांकer to CB location
 *
 * This function sends a single CB, that must NOT generate a completion entry
 *
 */
पूर्णांक hl_hw_queue_send_cb_no_cmpl(काष्ठा hl_device *hdev, u32 hw_queue_id,
				u32 cb_size, u64 cb_ptr)
अणु
	काष्ठा hl_hw_queue *q = &hdev->kernel_queues[hw_queue_id];
	पूर्णांक rc = 0;

	/*
	 * The CPU queue is a synchronous queue with an effective depth of
	 * a single entry (although it is allocated with room क्रम multiple
	 * entries). Thereक्रमe, there is a dअगरferent lock, called
	 * send_cpu_message_lock, that serializes accesses to the CPU queue.
	 * As a result, we करोn't need to lock the access to the entire H/W
	 * queues module when submitting a JOB to the CPU queue
	 */
	अगर (q->queue_type != QUEUE_TYPE_CPU)
		hdev->asic_funcs->hw_queues_lock(hdev);

	अगर (hdev->disabled) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	/*
	 * hl_hw_queue_send_cb_no_cmpl() is called क्रम queues of a H/W queue
	 * type only on init phase, when the queues are empty and being tested,
	 * so there is no need क्रम sanity checks.
	 */
	अगर (q->queue_type != QUEUE_TYPE_HW) अणु
		rc = ext_queue_sanity_checks(hdev, q, 1, false);
		अगर (rc)
			जाओ out;
	पूर्ण

	ext_and_hw_queue_submit_bd(hdev, q, 0, cb_size, cb_ptr);

out:
	अगर (q->queue_type != QUEUE_TYPE_CPU)
		hdev->asic_funcs->hw_queues_unlock(hdev);

	वापस rc;
पूर्ण

/*
 * ext_queue_schedule_job - submit a JOB to an बाह्यal queue
 *
 * @job: poपूर्णांकer to the job that needs to be submitted to the queue
 *
 * This function must be called when the scheduler mutex is taken
 *
 */
अटल व्योम ext_queue_schedule_job(काष्ठा hl_cs_job *job)
अणु
	काष्ठा hl_device *hdev = job->cs->ctx->hdev;
	काष्ठा hl_hw_queue *q = &hdev->kernel_queues[job->hw_queue_id];
	काष्ठा hl_cq_entry cq_pkt;
	काष्ठा hl_cq *cq;
	u64 cq_addr;
	काष्ठा hl_cb *cb;
	u32 ctl;
	u32 len;
	u64 ptr;

	/*
	 * Update the JOB ID inside the BD CTL so the device would know what
	 * to ग_लिखो in the completion queue
	 */
	ctl = ((q->pi << BD_CTL_SHADOW_INDEX_SHIFT) & BD_CTL_SHADOW_INDEX_MASK);

	cb = job->patched_cb;
	len = job->job_cb_size;
	ptr = cb->bus_address;

	/* Skip completion flow in हाल this is a non completion CS */
	अगर (!cs_needs_completion(job->cs))
		जाओ submit_bd;

	cq_pkt.data = cpu_to_le32(
			((q->pi << CQ_ENTRY_SHADOW_INDEX_SHIFT)
				& CQ_ENTRY_SHADOW_INDEX_MASK) |
			FIELD_PREP(CQ_ENTRY_SHADOW_INDEX_VALID_MASK, 1) |
			FIELD_PREP(CQ_ENTRY_READY_MASK, 1));

	/*
	 * No need to protect pi_offset because scheduling to the
	 * H/W queues is करोne under the scheduler mutex
	 *
	 * No need to check अगर CQ is full because it was alपढ़ोy
	 * checked in ext_queue_sanity_checks
	 */
	cq = &hdev->completion_queue[q->cq_id];
	cq_addr = cq->bus_address + cq->pi * माप(काष्ठा hl_cq_entry);

	hdev->asic_funcs->add_end_of_cb_packets(hdev, cb->kernel_address, len,
						cq_addr,
						le32_to_cpu(cq_pkt.data),
						q->msi_vec,
						job->contains_dma_pkt);

	q->shaकरोw_queue[hl_pi_2_offset(q->pi)] = job;

	cq->pi = hl_cq_inc_ptr(cq->pi);

submit_bd:
	ext_and_hw_queue_submit_bd(hdev, q, ctl, len, ptr);
पूर्ण

/*
 * पूर्णांक_queue_schedule_job - submit a JOB to an पूर्णांकernal queue
 *
 * @job: poपूर्णांकer to the job that needs to be submitted to the queue
 *
 * This function must be called when the scheduler mutex is taken
 *
 */
अटल व्योम पूर्णांक_queue_schedule_job(काष्ठा hl_cs_job *job)
अणु
	काष्ठा hl_device *hdev = job->cs->ctx->hdev;
	काष्ठा hl_hw_queue *q = &hdev->kernel_queues[job->hw_queue_id];
	काष्ठा hl_bd bd;
	__le64 *pi;

	bd.ctl = 0;
	bd.len = cpu_to_le32(job->job_cb_size);

	अगर (job->is_kernel_allocated_cb)
		/* bus_address is actually a mmu mapped address
		 * allocated from an पूर्णांकernal pool
		 */
		bd.ptr = cpu_to_le64(job->user_cb->bus_address);
	अन्यथा
		bd.ptr = cpu_to_le64((u64) (uपूर्णांकptr_t) job->user_cb);

	pi = q->kernel_address + (q->pi & (q->पूर्णांक_queue_len - 1)) * माप(bd);

	q->pi++;
	q->pi &= ((q->पूर्णांक_queue_len << 1) - 1);

	hdev->asic_funcs->pqe_ग_लिखो(hdev, pi, &bd);

	hdev->asic_funcs->ring_करोorbell(hdev, q->hw_queue_id, q->pi);
पूर्ण

/*
 * hw_queue_schedule_job - submit a JOB to a H/W queue
 *
 * @job: poपूर्णांकer to the job that needs to be submitted to the queue
 *
 * This function must be called when the scheduler mutex is taken
 *
 */
अटल व्योम hw_queue_schedule_job(काष्ठा hl_cs_job *job)
अणु
	काष्ठा hl_device *hdev = job->cs->ctx->hdev;
	काष्ठा hl_hw_queue *q = &hdev->kernel_queues[job->hw_queue_id];
	u64 ptr;
	u32 offset, ctl, len;

	/*
	 * Upon PQE completion, COMP_DATA is used as the ग_लिखो data to the
	 * completion queue (QMAN HBW message), and COMP_OFFSET is used as the
	 * ग_लिखो address offset in the SM block (QMAN LBW message).
	 * The ग_लिखो address offset is calculated as "COMP_OFFSET << 2".
	 */
	offset = job->cs->sequence & (hdev->asic_prop.max_pending_cs - 1);
	ctl = ((offset << BD_CTL_COMP_OFFSET_SHIFT) & BD_CTL_COMP_OFFSET_MASK) |
		((q->pi << BD_CTL_COMP_DATA_SHIFT) & BD_CTL_COMP_DATA_MASK);

	len = job->job_cb_size;

	/*
	 * A patched CB is created only अगर a user CB was allocated by driver and
	 * MMU is disabled. If MMU is enabled, the user CB should be used
	 * instead. If the user CB wasn't allocated by driver, assume that it
	 * holds an address.
	 */
	अगर (job->patched_cb)
		ptr = job->patched_cb->bus_address;
	अन्यथा अगर (job->is_kernel_allocated_cb)
		ptr = job->user_cb->bus_address;
	अन्यथा
		ptr = (u64) (uपूर्णांकptr_t) job->user_cb;

	ext_and_hw_queue_submit_bd(hdev, q, ctl, len, ptr);
पूर्ण

अटल व्योम init_संकेत_cs(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_job *job, काष्ठा hl_cs_compl *cs_cmpl)
अणु
	काष्ठा hl_sync_stream_properties *prop;
	काष्ठा hl_hw_sob *hw_sob;
	u32 q_idx;

	q_idx = job->hw_queue_id;
	prop = &hdev->kernel_queues[q_idx].sync_stream_prop;
	hw_sob = &prop->hw_sob[prop->curr_sob_offset];

	cs_cmpl->hw_sob = hw_sob;
	cs_cmpl->sob_val = prop->next_sob_val++;

	dev_dbg(hdev->dev,
		"generate signal CB, sob_id: %d, sob val: 0x%x, q_idx: %d\n",
		cs_cmpl->hw_sob->sob_id, cs_cmpl->sob_val, q_idx);

	/* we set an EB since we must make sure all oeprations are करोne
	 * when sending the संकेत
	 */
	hdev->asic_funcs->gen_संकेत_cb(hdev, job->patched_cb,
				cs_cmpl->hw_sob->sob_id, 0, true);

	kref_get(&hw_sob->kref);

	/* check क्रम wraparound */
	अगर (prop->next_sob_val == HL_MAX_SOB_VAL) अणु
		/*
		 * Decrement as we reached the max value.
		 * The release function won't be called here as we've
		 * just incremented the refcount.
		 */
		kref_put(&hw_sob->kref, hl_sob_reset_error);
		prop->next_sob_val = 1;
		/* only two SOBs are currently in use */
		prop->curr_sob_offset =
			(prop->curr_sob_offset + 1) % HL_RSVD_SOBS;

		dev_dbg(hdev->dev, "switched to SOB %d, q_idx: %d\n",
				prop->curr_sob_offset, q_idx);
	पूर्ण
पूर्ण

अटल व्योम init_रुको_cs(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs,
		काष्ठा hl_cs_job *job, काष्ठा hl_cs_compl *cs_cmpl)
अणु
	काष्ठा hl_cs_compl *संकेत_cs_cmpl;
	काष्ठा hl_sync_stream_properties *prop;
	काष्ठा hl_gen_रुको_properties रुको_prop;
	u32 q_idx;

	q_idx = job->hw_queue_id;
	prop = &hdev->kernel_queues[q_idx].sync_stream_prop;

	संकेत_cs_cmpl = container_of(cs->संकेत_fence,
					काष्ठा hl_cs_compl,
					base_fence);

	/* copy the SOB id and value of the संकेत CS */
	cs_cmpl->hw_sob = संकेत_cs_cmpl->hw_sob;
	cs_cmpl->sob_val = संकेत_cs_cmpl->sob_val;

	dev_dbg(hdev->dev,
		"generate wait CB, sob_id: %d, sob_val: 0x%x, mon_id: %d, q_idx: %d\n",
		cs_cmpl->hw_sob->sob_id, cs_cmpl->sob_val,
		prop->base_mon_id, q_idx);

	रुको_prop.data = (व्योम *) job->patched_cb;
	रुको_prop.sob_base = cs_cmpl->hw_sob->sob_id;
	रुको_prop.sob_mask = 0x1;
	रुको_prop.sob_val = cs_cmpl->sob_val;
	रुको_prop.mon_id = prop->base_mon_id;
	रुको_prop.q_idx = q_idx;
	रुको_prop.size = 0;
	hdev->asic_funcs->gen_रुको_cb(hdev, &रुको_prop);

	kref_get(&cs_cmpl->hw_sob->kref);
	/*
	 * Must put the संकेत fence after the SOB refcnt increment so
	 * the SOB refcnt won't turn 0 and reset the SOB beक्रमe the
	 * रुको CS was submitted.
	 */
	mb();
	hl_fence_put(cs->संकेत_fence);
	cs->संकेत_fence = शून्य;
पूर्ण

/*
 * init_संकेत_रुको_cs - initialize a संकेत/रुको CS
 * @cs: poपूर्णांकer to the संकेत/रुको CS
 *
 * H/W queues spinlock should be taken beक्रमe calling this function
 */
अटल व्योम init_संकेत_रुको_cs(काष्ठा hl_cs *cs)
अणु
	काष्ठा hl_ctx *ctx = cs->ctx;
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_cs_job *job;
	काष्ठा hl_cs_compl *cs_cmpl =
			container_of(cs->fence, काष्ठा hl_cs_compl, base_fence);

	/* There is only one job in a संकेत/रुको CS */
	job = list_first_entry(&cs->job_list, काष्ठा hl_cs_job,
				cs_node);

	अगर (cs->type & CS_TYPE_SIGNAL)
		init_संकेत_cs(hdev, job, cs_cmpl);
	अन्यथा अगर (cs->type & CS_TYPE_WAIT)
		init_रुको_cs(hdev, cs, job, cs_cmpl);
पूर्ण

/*
 * hl_hw_queue_schedule_cs - schedule a command submission
 * @cs: poपूर्णांकer to the CS
 */
पूर्णांक hl_hw_queue_schedule_cs(काष्ठा hl_cs *cs)
अणु
	क्रमागत hl_device_status status;
	काष्ठा hl_cs_counters_atomic *cntr;
	काष्ठा hl_ctx *ctx = cs->ctx;
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_cs_job *job, *पंचांगp;
	काष्ठा hl_hw_queue *q;
	पूर्णांक rc = 0, i, cq_cnt;
	bool first_entry;
	u32 max_queues;

	cntr = &hdev->aggregated_cs_counters;

	hdev->asic_funcs->hw_queues_lock(hdev);

	अगर (!hl_device_operational(hdev, &status)) अणु
		atomic64_inc(&cntr->device_in_reset_drop_cnt);
		atomic64_inc(&ctx->cs_counters.device_in_reset_drop_cnt);
		dev_err(hdev->dev,
			"device is %s, CS rejected!\n", hdev->status[status]);
		rc = -EPERM;
		जाओ out;
	पूर्ण

	max_queues = hdev->asic_prop.max_queues;

	q = &hdev->kernel_queues[0];
	क्रम (i = 0, cq_cnt = 0 ; i < max_queues ; i++, q++) अणु
		अगर (cs->jobs_in_queue_cnt[i]) अणु
			चयन (q->queue_type) अणु
			हाल QUEUE_TYPE_EXT:
				rc = ext_queue_sanity_checks(hdev, q,
						cs->jobs_in_queue_cnt[i],
						cs_needs_completion(cs) ?
								true : false);
				अवरोध;
			हाल QUEUE_TYPE_INT:
				rc = पूर्णांक_queue_sanity_checks(hdev, q,
						cs->jobs_in_queue_cnt[i]);
				अवरोध;
			हाल QUEUE_TYPE_HW:
				rc = hw_queue_sanity_checks(hdev, q,
						cs->jobs_in_queue_cnt[i]);
				अवरोध;
			शेष:
				dev_err(hdev->dev, "Queue type %d is invalid\n",
					q->queue_type);
				rc = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (rc) अणु
				atomic64_inc(
					&ctx->cs_counters.queue_full_drop_cnt);
				atomic64_inc(&cntr->queue_full_drop_cnt);
				जाओ unroll_cq_resv;
			पूर्ण

			अगर (q->queue_type == QUEUE_TYPE_EXT)
				cq_cnt++;
		पूर्ण
	पूर्ण

	अगर ((cs->type == CS_TYPE_SIGNAL) || (cs->type == CS_TYPE_WAIT))
		init_संकेत_रुको_cs(cs);
	अन्यथा अगर (cs->type == CS_TYPE_COLLECTIVE_WAIT)
		hdev->asic_funcs->collective_रुको_init_cs(cs);

	spin_lock(&hdev->cs_mirror_lock);

	/* Verअगरy staged CS exists and add to the staged list */
	अगर (cs->staged_cs && !cs->staged_first) अणु
		काष्ठा hl_cs *staged_cs;

		staged_cs = hl_staged_cs_find_first(hdev, cs->staged_sequence);
		अगर (!staged_cs) अणु
			dev_err(hdev->dev,
				"Cannot find staged submission sequence %llu",
				cs->staged_sequence);
			rc = -EINVAL;
			जाओ unlock_cs_mirror;
		पूर्ण

		अगर (is_staged_cs_last_exists(hdev, staged_cs)) अणु
			dev_err(hdev->dev,
				"Staged submission sequence %llu already submitted",
				cs->staged_sequence);
			rc = -EINVAL;
			जाओ unlock_cs_mirror;
		पूर्ण

		list_add_tail(&cs->staged_cs_node, &staged_cs->staged_cs_node);
	पूर्ण

	list_add_tail(&cs->mirror_node, &hdev->cs_mirror_list);

	/* Queue TDR अगर the CS is the first entry and अगर समयout is wanted */
	first_entry = list_first_entry(&hdev->cs_mirror_list,
					काष्ठा hl_cs, mirror_node) == cs;
	अगर ((hdev->समयout_jअगरfies != MAX_SCHEDULE_TIMEOUT) &&
				first_entry && cs_needs_समयout(cs)) अणु
		cs->tdr_active = true;
		schedule_delayed_work(&cs->work_tdr, cs->समयout_jअगरfies);

	पूर्ण

	spin_unlock(&hdev->cs_mirror_lock);

	list_क्रम_each_entry_safe(job, पंचांगp, &cs->job_list, cs_node)
		चयन (job->queue_type) अणु
		हाल QUEUE_TYPE_EXT:
			ext_queue_schedule_job(job);
			अवरोध;
		हाल QUEUE_TYPE_INT:
			पूर्णांक_queue_schedule_job(job);
			अवरोध;
		हाल QUEUE_TYPE_HW:
			hw_queue_schedule_job(job);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	cs->submitted = true;

	जाओ out;

unlock_cs_mirror:
	spin_unlock(&hdev->cs_mirror_lock);
unroll_cq_resv:
	q = &hdev->kernel_queues[0];
	क्रम (i = 0 ; (i < max_queues) && (cq_cnt > 0) ; i++, q++) अणु
		अगर ((q->queue_type == QUEUE_TYPE_EXT) &&
						(cs->jobs_in_queue_cnt[i])) अणु
			atomic_t *मुक्त_slots =
				&hdev->completion_queue[i].मुक्त_slots_cnt;
			atomic_add(cs->jobs_in_queue_cnt[i], मुक्त_slots);
			cq_cnt--;
		पूर्ण
	पूर्ण

out:
	hdev->asic_funcs->hw_queues_unlock(hdev);

	वापस rc;
पूर्ण

/*
 * hl_hw_queue_inc_ci_kernel - increment ci क्रम kernel's queue
 *
 * @hdev: poपूर्णांकer to hl_device काष्ठाure
 * @hw_queue_id: which queue to increment its ci
 */
व्योम hl_hw_queue_inc_ci_kernel(काष्ठा hl_device *hdev, u32 hw_queue_id)
अणु
	काष्ठा hl_hw_queue *q = &hdev->kernel_queues[hw_queue_id];

	atomic_inc(&q->ci);
पूर्ण

अटल पूर्णांक ext_and_cpu_queue_init(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q,
					bool is_cpu_queue)
अणु
	व्योम *p;
	पूर्णांक rc;

	अगर (is_cpu_queue)
		p = hdev->asic_funcs->cpu_accessible_dma_pool_alloc(hdev,
							HL_QUEUE_SIZE_IN_BYTES,
							&q->bus_address);
	अन्यथा
		p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev,
						HL_QUEUE_SIZE_IN_BYTES,
						&q->bus_address,
						GFP_KERNEL | __GFP_ZERO);
	अगर (!p)
		वापस -ENOMEM;

	q->kernel_address = p;

	q->shaकरोw_queue = kदो_स्मृति_array(HL_QUEUE_LENGTH,
					माप(*q->shaकरोw_queue),
					GFP_KERNEL);
	अगर (!q->shaकरोw_queue) अणु
		dev_err(hdev->dev,
			"Failed to allocate shadow queue for H/W queue %d\n",
			q->hw_queue_id);
		rc = -ENOMEM;
		जाओ मुक्त_queue;
	पूर्ण

	/* Make sure पढ़ो/ग_लिखो poपूर्णांकers are initialized to start of queue */
	atomic_set(&q->ci, 0);
	q->pi = 0;

	वापस 0;

मुक्त_queue:
	अगर (is_cpu_queue)
		hdev->asic_funcs->cpu_accessible_dma_pool_मुक्त(hdev,
					HL_QUEUE_SIZE_IN_BYTES,
					q->kernel_address);
	अन्यथा
		hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
					HL_QUEUE_SIZE_IN_BYTES,
					q->kernel_address,
					q->bus_address);

	वापस rc;
पूर्ण

अटल पूर्णांक पूर्णांक_queue_init(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q)
अणु
	व्योम *p;

	p = hdev->asic_funcs->get_पूर्णांक_queue_base(hdev, q->hw_queue_id,
					&q->bus_address, &q->पूर्णांक_queue_len);
	अगर (!p) अणु
		dev_err(hdev->dev,
			"Failed to get base address for internal queue %d\n",
			q->hw_queue_id);
		वापस -EFAULT;
	पूर्ण

	q->kernel_address = p;
	q->pi = 0;
	atomic_set(&q->ci, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cpu_queue_init(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q)
अणु
	वापस ext_and_cpu_queue_init(hdev, q, true);
पूर्ण

अटल पूर्णांक ext_queue_init(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q)
अणु
	वापस ext_and_cpu_queue_init(hdev, q, false);
पूर्ण

अटल पूर्णांक hw_queue_init(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q)
अणु
	व्योम *p;

	p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev,
						HL_QUEUE_SIZE_IN_BYTES,
						&q->bus_address,
						GFP_KERNEL | __GFP_ZERO);
	अगर (!p)
		वापस -ENOMEM;

	q->kernel_address = p;

	/* Make sure पढ़ो/ग_लिखो poपूर्णांकers are initialized to start of queue */
	atomic_set(&q->ci, 0);
	q->pi = 0;

	वापस 0;
पूर्ण

अटल व्योम sync_stream_queue_init(काष्ठा hl_device *hdev, u32 q_idx)
अणु
	काष्ठा hl_sync_stream_properties *sync_stream_prop;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_hw_sob *hw_sob;
	पूर्णांक sob, reserved_mon_idx, queue_idx;

	sync_stream_prop = &hdev->kernel_queues[q_idx].sync_stream_prop;

	/* We use 'collective_mon_idx' as a running index in order to reserve
	 * monitors क्रम collective master/slave queues.
	 * collective master queue माला_लो 2 reserved monitors
	 * collective slave queue माला_लो 1 reserved monitor
	 */
	अगर (hdev->kernel_queues[q_idx].collective_mode ==
			HL_COLLECTIVE_MASTER) अणु
		reserved_mon_idx = hdev->collective_mon_idx;

		/* reserve the first monitor क्रम collective master queue */
		sync_stream_prop->collective_mstr_mon_id[0] =
			prop->collective_first_mon + reserved_mon_idx;

		/* reserve the second monitor क्रम collective master queue */
		sync_stream_prop->collective_mstr_mon_id[1] =
			prop->collective_first_mon + reserved_mon_idx + 1;

		hdev->collective_mon_idx += HL_COLLECTIVE_RSVD_MSTR_MONS;
	पूर्ण अन्यथा अगर (hdev->kernel_queues[q_idx].collective_mode ==
			HL_COLLECTIVE_SLAVE) अणु
		reserved_mon_idx = hdev->collective_mon_idx++;

		/* reserve a monitor क्रम collective slave queue */
		sync_stream_prop->collective_slave_mon_id =
			prop->collective_first_mon + reserved_mon_idx;
	पूर्ण

	अगर (!hdev->kernel_queues[q_idx].supports_sync_stream)
		वापस;

	queue_idx = hdev->sync_stream_queue_idx++;

	sync_stream_prop->base_sob_id = prop->sync_stream_first_sob +
			(queue_idx * HL_RSVD_SOBS);
	sync_stream_prop->base_mon_id = prop->sync_stream_first_mon +
			(queue_idx * HL_RSVD_MONS);
	sync_stream_prop->next_sob_val = 1;
	sync_stream_prop->curr_sob_offset = 0;

	क्रम (sob = 0 ; sob < HL_RSVD_SOBS ; sob++) अणु
		hw_sob = &sync_stream_prop->hw_sob[sob];
		hw_sob->hdev = hdev;
		hw_sob->sob_id = sync_stream_prop->base_sob_id + sob;
		hw_sob->q_idx = q_idx;
		kref_init(&hw_sob->kref);
	पूर्ण
पूर्ण

अटल व्योम sync_stream_queue_reset(काष्ठा hl_device *hdev, u32 q_idx)
अणु
	काष्ठा hl_sync_stream_properties *prop =
			&hdev->kernel_queues[q_idx].sync_stream_prop;

	/*
	 * In हाल we got here due to a stuck CS, the refcnt might be bigger
	 * than 1 and thereक्रमe we reset it.
	 */
	kref_init(&prop->hw_sob[prop->curr_sob_offset].kref);
	prop->curr_sob_offset = 0;
	prop->next_sob_val = 1;
पूर्ण

/*
 * queue_init - मुख्य initialization function क्रम H/W queue object
 *
 * @hdev: poपूर्णांकer to hl_device device काष्ठाure
 * @q: poपूर्णांकer to hl_hw_queue queue काष्ठाure
 * @hw_queue_id: The id of the H/W queue
 *
 * Allocate dma-able memory क्रम the queue and initialize fields
 * Returns 0 on success
 */
अटल पूर्णांक queue_init(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q,
			u32 hw_queue_id)
अणु
	पूर्णांक rc;

	q->hw_queue_id = hw_queue_id;

	चयन (q->queue_type) अणु
	हाल QUEUE_TYPE_EXT:
		rc = ext_queue_init(hdev, q);
		अवरोध;
	हाल QUEUE_TYPE_INT:
		rc = पूर्णांक_queue_init(hdev, q);
		अवरोध;
	हाल QUEUE_TYPE_CPU:
		rc = cpu_queue_init(hdev, q);
		अवरोध;
	हाल QUEUE_TYPE_HW:
		rc = hw_queue_init(hdev, q);
		अवरोध;
	हाल QUEUE_TYPE_NA:
		q->valid = 0;
		वापस 0;
	शेष:
		dev_crit(hdev->dev, "wrong queue type %d during init\n",
			q->queue_type);
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	sync_stream_queue_init(hdev, q->hw_queue_id);

	अगर (rc)
		वापस rc;

	q->valid = 1;

	वापस 0;
पूर्ण

/*
 * hw_queue_fini - destroy queue
 *
 * @hdev: poपूर्णांकer to hl_device device काष्ठाure
 * @q: poपूर्णांकer to hl_hw_queue queue काष्ठाure
 *
 * Free the queue memory
 */
अटल व्योम queue_fini(काष्ठा hl_device *hdev, काष्ठा hl_hw_queue *q)
अणु
	अगर (!q->valid)
		वापस;

	/*
	 * If we arrived here, there are no jobs रुकोing on this queue
	 * so we can safely हटाओ it.
	 * This is because this function can only called when:
	 * 1. Either a context is deleted, which only can occur अगर all its
	 *    jobs were finished
	 * 2. A context wasn't able to be created due to failure or समयout,
	 *    which means there are no jobs on the queue yet
	 *
	 * The only exception are the queues of the kernel context, but
	 * अगर they are being destroyed, it means that the entire module is
	 * being हटाओd. If the module is हटाओd, it means there is no खोलो
	 * user context. It also means that अगर a job was submitted by
	 * the kernel driver (e.g. context creation), the job itself was
	 * released by the kernel driver when a समयout occurred on its
	 * Completion. Thus, we करोn't need to release it again.
	 */

	अगर (q->queue_type == QUEUE_TYPE_INT)
		वापस;

	kमुक्त(q->shaकरोw_queue);

	अगर (q->queue_type == QUEUE_TYPE_CPU)
		hdev->asic_funcs->cpu_accessible_dma_pool_मुक्त(hdev,
					HL_QUEUE_SIZE_IN_BYTES,
					q->kernel_address);
	अन्यथा
		hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev,
					HL_QUEUE_SIZE_IN_BYTES,
					q->kernel_address,
					q->bus_address);
पूर्ण

पूर्णांक hl_hw_queues_create(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *asic = &hdev->asic_prop;
	काष्ठा hl_hw_queue *q;
	पूर्णांक i, rc, q_पढ़ोy_cnt;

	hdev->kernel_queues = kसुस्मृति(asic->max_queues,
				माप(*hdev->kernel_queues), GFP_KERNEL);

	अगर (!hdev->kernel_queues) अणु
		dev_err(hdev->dev, "Not enough memory for H/W queues\n");
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the H/W queues */
	क्रम (i = 0, q_पढ़ोy_cnt = 0, q = hdev->kernel_queues;
			i < asic->max_queues ; i++, q_पढ़ोy_cnt++, q++) अणु

		q->queue_type = asic->hw_queues_props[i].type;
		q->supports_sync_stream =
				asic->hw_queues_props[i].supports_sync_stream;
		q->collective_mode = asic->hw_queues_props[i].collective_mode;
		rc = queue_init(hdev, q, i);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"failed to initialize queue %d\n", i);
			जाओ release_queues;
		पूर्ण
	पूर्ण

	वापस 0;

release_queues:
	क्रम (i = 0, q = hdev->kernel_queues ; i < q_पढ़ोy_cnt ; i++, q++)
		queue_fini(hdev, q);

	kमुक्त(hdev->kernel_queues);

	वापस rc;
पूर्ण

व्योम hl_hw_queues_destroy(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_hw_queue *q;
	u32 max_queues = hdev->asic_prop.max_queues;
	पूर्णांक i;

	क्रम (i = 0, q = hdev->kernel_queues ; i < max_queues ; i++, q++)
		queue_fini(hdev, q);

	kमुक्त(hdev->kernel_queues);
पूर्ण

व्योम hl_hw_queue_reset(काष्ठा hl_device *hdev, bool hard_reset)
अणु
	काष्ठा hl_hw_queue *q;
	u32 max_queues = hdev->asic_prop.max_queues;
	पूर्णांक i;

	क्रम (i = 0, q = hdev->kernel_queues ; i < max_queues ; i++, q++) अणु
		अगर ((!q->valid) ||
			((!hard_reset) && (q->queue_type == QUEUE_TYPE_CPU)))
			जारी;
		q->pi = 0;
		atomic_set(&q->ci, 0);

		अगर (q->supports_sync_stream)
			sync_stream_queue_reset(hdev, q->hw_queue_id);
	पूर्ण
पूर्ण
