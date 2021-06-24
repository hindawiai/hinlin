<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश <uapi/misc/habanaद_असल.h>
#समावेश "habanalabs.h"

#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>

#घोषणा HL_CS_FLAGS_TYPE_MASK	(HL_CS_FLAGS_SIGNAL | HL_CS_FLAGS_WAIT | \
				HL_CS_FLAGS_COLLECTIVE_WAIT)

/**
 * क्रमागत hl_cs_रुको_status - cs रुको status
 * @CS_WAIT_STATUS_BUSY: cs was not completed yet
 * @CS_WAIT_STATUS_COMPLETED: cs completed
 * @CS_WAIT_STATUS_GONE: cs completed but fence is alपढ़ोy gone
 */
क्रमागत hl_cs_रुको_status अणु
	CS_WAIT_STATUS_BUSY,
	CS_WAIT_STATUS_COMPLETED,
	CS_WAIT_STATUS_GONE
पूर्ण;

अटल व्योम job_wq_completion(काष्ठा work_काष्ठा *work);
अटल पूर्णांक _hl_cs_रुको_ioctl(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
				u64 समयout_us, u64 seq,
				क्रमागत hl_cs_रुको_status *status, s64 *बारtamp);
अटल व्योम cs_करो_release(काष्ठा kref *ref);

अटल व्योम hl_sob_reset(काष्ठा kref *ref)
अणु
	काष्ठा hl_hw_sob *hw_sob = container_of(ref, काष्ठा hl_hw_sob,
							kref);
	काष्ठा hl_device *hdev = hw_sob->hdev;

	hdev->asic_funcs->reset_sob(hdev, hw_sob);
पूर्ण

व्योम hl_sob_reset_error(काष्ठा kref *ref)
अणु
	काष्ठा hl_hw_sob *hw_sob = container_of(ref, काष्ठा hl_hw_sob,
							kref);
	काष्ठा hl_device *hdev = hw_sob->hdev;

	dev_crit(hdev->dev,
		"SOB release shouldn't be called here, q_idx: %d, sob_id: %d\n",
		hw_sob->q_idx, hw_sob->sob_id);
पूर्ण

/**
 * hl_gen_sob_mask() - Generates a sob mask to be used in a monitor arm packet
 * @sob_base: sob base id
 * @sob_mask: sob user mask, each bit represents a sob offset from sob base
 * @mask: generated mask
 *
 * Return: 0 अगर given parameters are valid
 */
पूर्णांक hl_gen_sob_mask(u16 sob_base, u8 sob_mask, u8 *mask)
अणु
	पूर्णांक i;

	अगर (sob_mask == 0)
		वापस -EINVAL;

	अगर (sob_mask == 0x1) अणु
		*mask = ~(1 << (sob_base & 0x7));
	पूर्ण अन्यथा अणु
		/* find msb in order to verअगरy sob range is valid */
		क्रम (i = BITS_PER_BYTE - 1 ; i >= 0 ; i--)
			अगर (BIT(i) & sob_mask)
				अवरोध;

		अगर (i > (HL_MAX_SOBS_PER_MONITOR - (sob_base & 0x7) - 1))
			वापस -EINVAL;

		*mask = ~sob_mask;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sob_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hl_cs_compl *hl_cs_cmpl =
		container_of(work, काष्ठा hl_cs_compl, sob_reset_work);
	काष्ठा hl_device *hdev = hl_cs_cmpl->hdev;

	/*
	 * A संकेत CS can get completion जबतक the corresponding रुको
	 * क्रम संकेत CS is on its way to the PQ. The रुको क्रम संकेत CS
	 * will get stuck अगर the संकेत CS incremented the SOB to its
	 * max value and there are no pending (submitted) रुकोs on this
	 * SOB.
	 * We करो the following to व्योम this situation:
	 * 1. The रुको क्रम संकेत CS must get a ref क्रम the संकेत CS as
	 *    soon as possible in cs_ioctl_संकेत_रुको() and put it
	 *    beक्रमe being submitted to the PQ but after it incremented
	 *    the SOB refcnt in init_संकेत_रुको_cs().
	 * 2. Signal/Wait क्रम संकेत CS will decrement the SOB refcnt
	 *    here.
	 * These two measures guarantee that the रुको क्रम संकेत CS will
	 * reset the SOB upon completion rather than the संकेत CS and
	 * hence the above scenario is aव्योमed.
	 */
	kref_put(&hl_cs_cmpl->hw_sob->kref, hl_sob_reset);

	अगर (hl_cs_cmpl->type == CS_TYPE_COLLECTIVE_WAIT)
		hdev->asic_funcs->reset_sob_group(hdev,
				hl_cs_cmpl->sob_group);

	kमुक्त(hl_cs_cmpl);
पूर्ण

अटल व्योम hl_fence_release(काष्ठा kref *kref)
अणु
	काष्ठा hl_fence *fence =
		container_of(kref, काष्ठा hl_fence, refcount);
	काष्ठा hl_cs_compl *hl_cs_cmpl =
		container_of(fence, काष्ठा hl_cs_compl, base_fence);
	काष्ठा hl_device *hdev = hl_cs_cmpl->hdev;

	/* EBUSY means the CS was never submitted and hence we करोn't have
	 * an attached hw_sob object that we should handle here
	 */
	अगर (fence->error == -EBUSY)
		जाओ मुक्त;

	अगर ((hl_cs_cmpl->type == CS_TYPE_SIGNAL) ||
		(hl_cs_cmpl->type == CS_TYPE_WAIT) ||
		(hl_cs_cmpl->type == CS_TYPE_COLLECTIVE_WAIT)) अणु

		dev_dbg(hdev->dev,
			"CS 0x%llx type %d finished, sob_id: %d, sob_val: 0x%x\n",
			hl_cs_cmpl->cs_seq,
			hl_cs_cmpl->type,
			hl_cs_cmpl->hw_sob->sob_id,
			hl_cs_cmpl->sob_val);

		queue_work(hdev->sob_reset_wq, &hl_cs_cmpl->sob_reset_work);

		वापस;
	पूर्ण

मुक्त:
	kमुक्त(hl_cs_cmpl);
पूर्ण

व्योम hl_fence_put(काष्ठा hl_fence *fence)
अणु
	अगर (fence)
		kref_put(&fence->refcount, hl_fence_release);
पूर्ण

व्योम hl_fence_get(काष्ठा hl_fence *fence)
अणु
	अगर (fence)
		kref_get(&fence->refcount);
पूर्ण

अटल व्योम hl_fence_init(काष्ठा hl_fence *fence, u64 sequence)
अणु
	kref_init(&fence->refcount);
	fence->cs_sequence = sequence;
	fence->error = 0;
	fence->बारtamp = kसमय_set(0, 0);
	init_completion(&fence->completion);
पूर्ण

व्योम cs_get(काष्ठा hl_cs *cs)
अणु
	kref_get(&cs->refcount);
पूर्ण

अटल पूर्णांक cs_get_unless_zero(काष्ठा hl_cs *cs)
अणु
	वापस kref_get_unless_zero(&cs->refcount);
पूर्ण

अटल व्योम cs_put(काष्ठा hl_cs *cs)
अणु
	kref_put(&cs->refcount, cs_करो_release);
पूर्ण

अटल व्योम cs_job_करो_release(काष्ठा kref *ref)
अणु
	काष्ठा hl_cs_job *job = container_of(ref, काष्ठा hl_cs_job, refcount);

	kमुक्त(job);
पूर्ण

अटल व्योम cs_job_put(काष्ठा hl_cs_job *job)
अणु
	kref_put(&job->refcount, cs_job_करो_release);
पूर्ण

bool cs_needs_completion(काष्ठा hl_cs *cs)
अणु
	/* In हाल this is a staged CS, only the last CS in sequence should
	 * get a completion, any non staged CS will always get a completion
	 */
	अगर (cs->staged_cs && !cs->staged_last)
		वापस false;

	वापस true;
पूर्ण

bool cs_needs_समयout(काष्ठा hl_cs *cs)
अणु
	/* In हाल this is a staged CS, only the first CS in sequence should
	 * get a समयout, any non staged CS will always get a समयout
	 */
	अगर (cs->staged_cs && !cs->staged_first)
		वापस false;

	वापस true;
पूर्ण

अटल bool is_cb_patched(काष्ठा hl_device *hdev, काष्ठा hl_cs_job *job)
अणु
	/*
	 * Patched CB is created क्रम बाह्यal queues jobs, and क्रम H/W queues
	 * jobs अगर the user CB was allocated by driver and MMU is disabled.
	 */
	वापस (job->queue_type == QUEUE_TYPE_EXT ||
			(job->queue_type == QUEUE_TYPE_HW &&
					job->is_kernel_allocated_cb &&
					!hdev->mmu_enable));
पूर्ण

/*
 * cs_parser - parse the user command submission
 *
 * @hpriv	: poपूर्णांकer to the निजी data of the fd
 * @job        : poपूर्णांकer to the job that holds the command submission info
 *
 * The function parses the command submission of the user. It calls the
 * ASIC specअगरic parser, which वापसs a list of memory blocks to send
 * to the device as dअगरferent command buffers
 *
 */
अटल पूर्णांक cs_parser(काष्ठा hl_fpriv *hpriv, काष्ठा hl_cs_job *job)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_cs_parser parser;
	पूर्णांक rc;

	parser.ctx_id = job->cs->ctx->asid;
	parser.cs_sequence = job->cs->sequence;
	parser.job_id = job->id;

	parser.hw_queue_id = job->hw_queue_id;
	parser.job_userptr_list = &job->userptr_list;
	parser.patched_cb = शून्य;
	parser.user_cb = job->user_cb;
	parser.user_cb_size = job->user_cb_size;
	parser.queue_type = job->queue_type;
	parser.is_kernel_allocated_cb = job->is_kernel_allocated_cb;
	job->patched_cb = शून्य;
	parser.completion = cs_needs_completion(job->cs);

	rc = hdev->asic_funcs->cs_parser(hdev, &parser);

	अगर (is_cb_patched(hdev, job)) अणु
		अगर (!rc) अणु
			job->patched_cb = parser.patched_cb;
			job->job_cb_size = parser.patched_cb_size;
			job->contains_dma_pkt = parser.contains_dma_pkt;
			atomic_inc(&job->patched_cb->cs_cnt);
		पूर्ण

		/*
		 * Whether the parsing worked or not, we करोn't need the
		 * original CB anymore because it was alपढ़ोy parsed and
		 * won't be accessed again क्रम this CS
		 */
		atomic_dec(&job->user_cb->cs_cnt);
		hl_cb_put(job->user_cb);
		job->user_cb = शून्य;
	पूर्ण अन्यथा अगर (!rc) अणु
		job->job_cb_size = job->user_cb_size;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम complete_job(काष्ठा hl_device *hdev, काष्ठा hl_cs_job *job)
अणु
	काष्ठा hl_cs *cs = job->cs;

	अगर (is_cb_patched(hdev, job)) अणु
		hl_userptr_delete_list(hdev, &job->userptr_list);

		/*
		 * We might arrive here from rollback and patched CB wasn't
		 * created, so we need to check it's not शून्य
		 */
		अगर (job->patched_cb) अणु
			atomic_dec(&job->patched_cb->cs_cnt);
			hl_cb_put(job->patched_cb);
		पूर्ण
	पूर्ण

	/* For H/W queue jobs, अगर a user CB was allocated by driver and MMU is
	 * enabled, the user CB isn't released in cs_parser() and thus should be
	 * released here.
	 * This is also true क्रम INT queues jobs which were allocated by driver
	 */
	अगर (job->is_kernel_allocated_cb &&
		((job->queue_type == QUEUE_TYPE_HW && hdev->mmu_enable) ||
				job->queue_type == QUEUE_TYPE_INT)) अणु
		atomic_dec(&job->user_cb->cs_cnt);
		hl_cb_put(job->user_cb);
	पूर्ण

	/*
	 * This is the only place where there can be multiple thपढ़ोs
	 * modअगरying the list at the same समय
	 */
	spin_lock(&cs->job_lock);
	list_del(&job->cs_node);
	spin_unlock(&cs->job_lock);

	hl_debugfs_हटाओ_job(hdev, job);

	/* We decrement reference only क्रम a CS that माला_लो completion
	 * because the reference was incremented only क्रम this kind of CS
	 * right beक्रमe it was scheduled.
	 *
	 * In staged submission, only the last CS marked as 'staged_last'
	 * माला_लो completion, hence its release function will be called from here.
	 * As क्रम all the rest CS's in the staged submission which करो not get
	 * completion, their CS reference will be decremented by the
	 * 'staged_last' CS during the CS release flow.
	 * All relevant PQ CI counters will be incremented during the CS release
	 * flow by calling 'hl_hw_queue_update_ci'.
	 */
	अगर (cs_needs_completion(cs) &&
		(job->queue_type == QUEUE_TYPE_EXT ||
			job->queue_type == QUEUE_TYPE_HW))
		cs_put(cs);

	cs_job_put(job);
पूर्ण

/*
 * hl_staged_cs_find_first - locate the first CS in this staged submission
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @cs_seq: staged submission sequence number
 *
 * @note: This function must be called under 'hdev->cs_mirror_lock'
 *
 * Find and वापस a CS poपूर्णांकer with the given sequence
 */
काष्ठा hl_cs *hl_staged_cs_find_first(काष्ठा hl_device *hdev, u64 cs_seq)
अणु
	काष्ठा hl_cs *cs;

	list_क्रम_each_entry_reverse(cs, &hdev->cs_mirror_list, mirror_node)
		अगर (cs->staged_cs && cs->staged_first &&
				cs->sequence == cs_seq)
			वापस cs;

	वापस शून्य;
पूर्ण

/*
 * is_staged_cs_last_exists - वापसs true अगर the last CS in sequence exists
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @cs: staged submission member
 *
 */
bool is_staged_cs_last_exists(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs)
अणु
	काष्ठा hl_cs *last_entry;

	last_entry = list_last_entry(&cs->staged_cs_node, काष्ठा hl_cs,
								staged_cs_node);

	अगर (last_entry->staged_last)
		वापस true;

	वापस false;
पूर्ण

/*
 * staged_cs_get - get CS reference अगर this CS is a part of a staged CS
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @cs: current CS
 * @cs_seq: staged submission sequence number
 *
 * Increment CS reference क्रम every CS in this staged submission except क्रम
 * the CS which get completion.
 */
अटल व्योम staged_cs_get(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs)
अणु
	/* Only the last CS in this staged submission will get a completion.
	 * We must increment the reference क्रम all other CS's in this
	 * staged submission.
	 * Once we get a completion we will release the whole staged submission.
	 */
	अगर (!cs->staged_last)
		cs_get(cs);
पूर्ण

/*
 * staged_cs_put - put a CS in हाल it is part of staged submission
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @cs: CS to put
 *
 * This function decrements a CS reference (क्रम a non completion CS)
 */
अटल व्योम staged_cs_put(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs)
अणु
	/* We release all CS's in a staged submission except the last
	 * CS which we have never incremented its reference.
	 */
	अगर (!cs_needs_completion(cs))
		cs_put(cs);
पूर्ण

अटल व्योम cs_handle_tdr(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs)
अणु
	bool next_entry_found = false;
	काष्ठा hl_cs *next;

	अगर (!cs_needs_समयout(cs))
		वापस;

	spin_lock(&hdev->cs_mirror_lock);

	/* We need to handle tdr only once क्रम the complete staged submission.
	 * Hence, we choose the CS that reaches this function first which is
	 * the CS marked as 'staged_last'.
	 */
	अगर (cs->staged_cs && cs->staged_last)
		cs = hl_staged_cs_find_first(hdev, cs->staged_sequence);

	spin_unlock(&hdev->cs_mirror_lock);

	/* Don't cancel TDR in हाल this CS was समयकरोut because we might be
	 * running from the TDR context
	 */
	अगर (cs && (cs->समयकरोut ||
			hdev->समयout_jअगरfies == MAX_SCHEDULE_TIMEOUT))
		वापस;

	अगर (cs && cs->tdr_active)
		cancel_delayed_work_sync(&cs->work_tdr);

	spin_lock(&hdev->cs_mirror_lock);

	/* queue TDR क्रम next CS */
	list_क्रम_each_entry(next, &hdev->cs_mirror_list, mirror_node)
		अगर (cs_needs_समयout(next)) अणु
			next_entry_found = true;
			अवरोध;
		पूर्ण

	अगर (next_entry_found && !next->tdr_active) अणु
		next->tdr_active = true;
		schedule_delayed_work(&next->work_tdr, next->समयout_jअगरfies);
	पूर्ण

	spin_unlock(&hdev->cs_mirror_lock);
पूर्ण

अटल व्योम cs_करो_release(काष्ठा kref *ref)
अणु
	काष्ठा hl_cs *cs = container_of(ref, काष्ठा hl_cs, refcount);
	काष्ठा hl_device *hdev = cs->ctx->hdev;
	काष्ठा hl_cs_job *job, *पंचांगp;

	cs->completed = true;

	/*
	 * Although अगर we reached here it means that all बाह्यal jobs have
	 * finished, because each one of them took refcnt to CS, we still
	 * need to go over the पूर्णांकernal jobs and complete them. Otherwise, we
	 * will have leaked memory and what's worse, the CS object (and
	 * potentially the CTX object) could be released, जबतक the JOB
	 * still holds a poपूर्णांकer to them (but no reference).
	 */
	list_क्रम_each_entry_safe(job, पंचांगp, &cs->job_list, cs_node)
		complete_job(hdev, job);

	अगर (!cs->submitted) अणु
		/* In हाल the रुको क्रम संकेत CS was submitted, the put occurs
		 * in init_संकेत_रुको_cs() or collective_रुको_init_cs()
		 * right beक्रमe hanging on the PQ.
		 */
		अगर (cs->type == CS_TYPE_WAIT ||
				cs->type == CS_TYPE_COLLECTIVE_WAIT)
			hl_fence_put(cs->संकेत_fence);

		जाओ out;
	पूर्ण

	/* Need to update CI क्रम all queue jobs that करोes not get completion */
	hl_hw_queue_update_ci(cs);

	/* हटाओ CS from CS mirror list */
	spin_lock(&hdev->cs_mirror_lock);
	list_del_init(&cs->mirror_node);
	spin_unlock(&hdev->cs_mirror_lock);

	cs_handle_tdr(hdev, cs);

	अगर (cs->staged_cs) अणु
		/* the completion CS decrements reference क्रम the entire
		 * staged submission
		 */
		अगर (cs->staged_last) अणु
			काष्ठा hl_cs *staged_cs, *पंचांगp;

			list_क्रम_each_entry_safe(staged_cs, पंचांगp,
					&cs->staged_cs_node, staged_cs_node)
				staged_cs_put(hdev, staged_cs);
		पूर्ण

		/* A staged CS will be a member in the list only after it
		 * was submitted. We used 'cs_mirror_lock' when inserting
		 * it to list so we will use it again when removing it
		 */
		अगर (cs->submitted) अणु
			spin_lock(&hdev->cs_mirror_lock);
			list_del(&cs->staged_cs_node);
			spin_unlock(&hdev->cs_mirror_lock);
		पूर्ण
	पूर्ण

out:
	/* Must be called beक्रमe hl_ctx_put because inside we use ctx to get
	 * the device
	 */
	hl_debugfs_हटाओ_cs(cs);

	hl_ctx_put(cs->ctx);

	/* We need to mark an error क्रम not submitted because in that हाल
	 * the hl fence release flow is dअगरferent. Mainly, we करोn't need
	 * to handle hw_sob क्रम संकेत/रुको
	 */
	अगर (cs->समयकरोut)
		cs->fence->error = -ETIMEDOUT;
	अन्यथा अगर (cs->पातed)
		cs->fence->error = -EIO;
	अन्यथा अगर (!cs->submitted)
		cs->fence->error = -EBUSY;

	अगर (cs->बारtamp)
		cs->fence->बारtamp = kसमय_get();
	complete_all(&cs->fence->completion);
	hl_fence_put(cs->fence);

	kमुक्त(cs->jobs_in_queue_cnt);
	kमुक्त(cs);
पूर्ण

अटल व्योम cs_समयकरोut(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hl_device *hdev;
	पूर्णांक rc;
	काष्ठा hl_cs *cs = container_of(work, काष्ठा hl_cs,
						 work_tdr.work);
	rc = cs_get_unless_zero(cs);
	अगर (!rc)
		वापस;

	अगर ((!cs->submitted) || (cs->completed)) अणु
		cs_put(cs);
		वापस;
	पूर्ण

	/* Mark the CS is समयd out so we won't try to cancel its TDR */
	cs->समयकरोut = true;

	hdev = cs->ctx->hdev;

	चयन (cs->type) अणु
	हाल CS_TYPE_SIGNAL:
		dev_err(hdev->dev,
			"Signal command submission %llu has not finished in time!\n",
			cs->sequence);
		अवरोध;

	हाल CS_TYPE_WAIT:
		dev_err(hdev->dev,
			"Wait command submission %llu has not finished in time!\n",
			cs->sequence);
		अवरोध;

	हाल CS_TYPE_COLLECTIVE_WAIT:
		dev_err(hdev->dev,
			"Collective Wait command submission %llu has not finished in time!\n",
			cs->sequence);
		अवरोध;

	शेष:
		dev_err(hdev->dev,
			"Command submission %llu has not finished in time!\n",
			cs->sequence);
		अवरोध;
	पूर्ण

	cs_put(cs);

	अगर (hdev->reset_on_lockup)
		hl_device_reset(hdev, 0);
	अन्यथा
		hdev->needs_reset = true;
पूर्ण

अटल पूर्णांक allocate_cs(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
			क्रमागत hl_cs_type cs_type, u64 user_sequence,
			काष्ठा hl_cs **cs_new, u32 flags, u32 समयout)
अणु
	काष्ठा hl_cs_counters_atomic *cntr;
	काष्ठा hl_fence *other = शून्य;
	काष्ठा hl_cs_compl *cs_cmpl;
	काष्ठा hl_cs *cs;
	पूर्णांक rc;

	cntr = &hdev->aggregated_cs_counters;

	cs = kzalloc(माप(*cs), GFP_ATOMIC);
	अगर (!cs)
		cs = kzalloc(माप(*cs), GFP_KERNEL);

	अगर (!cs) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		वापस -ENOMEM;
	पूर्ण

	/* increment refcnt क्रम context */
	hl_ctx_get(hdev, ctx);

	cs->ctx = ctx;
	cs->submitted = false;
	cs->completed = false;
	cs->type = cs_type;
	cs->बारtamp = !!(flags & HL_CS_FLAGS_TIMESTAMP);
	cs->समयout_jअगरfies = समयout;
	INIT_LIST_HEAD(&cs->job_list);
	INIT_DELAYED_WORK(&cs->work_tdr, cs_समयकरोut);
	kref_init(&cs->refcount);
	spin_lock_init(&cs->job_lock);

	cs_cmpl = kदो_स्मृति(माप(*cs_cmpl), GFP_ATOMIC);
	अगर (!cs_cmpl)
		cs_cmpl = kदो_स्मृति(माप(*cs_cmpl), GFP_KERNEL);

	अगर (!cs_cmpl) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		rc = -ENOMEM;
		जाओ मुक्त_cs;
	पूर्ण

	cs->jobs_in_queue_cnt = kसुस्मृति(hdev->asic_prop.max_queues,
			माप(*cs->jobs_in_queue_cnt), GFP_ATOMIC);
	अगर (!cs->jobs_in_queue_cnt)
		cs->jobs_in_queue_cnt = kसुस्मृति(hdev->asic_prop.max_queues,
				माप(*cs->jobs_in_queue_cnt), GFP_KERNEL);

	अगर (!cs->jobs_in_queue_cnt) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		rc = -ENOMEM;
		जाओ मुक्त_cs_cmpl;
	पूर्ण

	cs_cmpl->hdev = hdev;
	cs_cmpl->type = cs->type;
	spin_lock_init(&cs_cmpl->lock);
	INIT_WORK(&cs_cmpl->sob_reset_work, sob_reset_work);
	cs->fence = &cs_cmpl->base_fence;

	spin_lock(&ctx->cs_lock);

	cs_cmpl->cs_seq = ctx->cs_sequence;
	other = ctx->cs_pending[cs_cmpl->cs_seq &
				(hdev->asic_prop.max_pending_cs - 1)];

	अगर (other && !completion_करोne(&other->completion)) अणु
		/* If the following statement is true, it means we have reached
		 * a poपूर्णांक in which only part of the staged submission was
		 * submitted and we करोn't have enough room in the 'cs_pending'
		 * array क्रम the rest of the submission.
		 * This causes a deadlock because this CS will never be
		 * completed as it depends on future CS's क्रम completion.
		 */
		अगर (other->cs_sequence == user_sequence)
			dev_crit_ratelimited(hdev->dev,
				"Staged CS %llu deadlock due to lack of resources",
				user_sequence);

		dev_dbg_ratelimited(hdev->dev,
			"Rejecting CS because of too many in-flights CS\n");
		atomic64_inc(&ctx->cs_counters.max_cs_in_flight_drop_cnt);
		atomic64_inc(&cntr->max_cs_in_flight_drop_cnt);
		rc = -EAGAIN;
		जाओ मुक्त_fence;
	पूर्ण

	/* init hl_fence */
	hl_fence_init(&cs_cmpl->base_fence, cs_cmpl->cs_seq);

	cs->sequence = cs_cmpl->cs_seq;

	ctx->cs_pending[cs_cmpl->cs_seq &
			(hdev->asic_prop.max_pending_cs - 1)] =
							&cs_cmpl->base_fence;
	ctx->cs_sequence++;

	hl_fence_get(&cs_cmpl->base_fence);

	hl_fence_put(other);

	spin_unlock(&ctx->cs_lock);

	*cs_new = cs;

	वापस 0;

मुक्त_fence:
	spin_unlock(&ctx->cs_lock);
	kमुक्त(cs->jobs_in_queue_cnt);
मुक्त_cs_cmpl:
	kमुक्त(cs_cmpl);
मुक्त_cs:
	kमुक्त(cs);
	hl_ctx_put(ctx);
	वापस rc;
पूर्ण

अटल व्योम cs_rollback(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs)
अणु
	काष्ठा hl_cs_job *job, *पंचांगp;

	staged_cs_put(hdev, cs);

	list_क्रम_each_entry_safe(job, पंचांगp, &cs->job_list, cs_node)
		complete_job(hdev, job);
पूर्ण

व्योम hl_cs_rollback_all(काष्ठा hl_device *hdev)
अणु
	पूर्णांक i;
	काष्ठा hl_cs *cs, *पंचांगp;

	flush_workqueue(hdev->sob_reset_wq);

	/* flush all completions beक्रमe iterating over the CS mirror list in
	 * order to aव्योम a race with the release functions
	 */
	क्रम (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		flush_workqueue(hdev->cq_wq[i]);

	/* Make sure we करोn't have leftovers in the CS mirror list */
	list_क्रम_each_entry_safe(cs, पंचांगp, &hdev->cs_mirror_list, mirror_node) अणु
		cs_get(cs);
		cs->पातed = true;
		dev_warn_ratelimited(hdev->dev, "Killing CS %d.%llu\n",
				cs->ctx->asid, cs->sequence);
		cs_rollback(hdev, cs);
		cs_put(cs);
	पूर्ण
पूर्ण

व्योम hl_pending_cb_list_flush(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_pending_cb *pending_cb, *पंचांगp;

	list_क्रम_each_entry_safe(pending_cb, पंचांगp,
			&ctx->pending_cb_list, cb_node) अणु
		list_del(&pending_cb->cb_node);
		hl_cb_put(pending_cb->cb);
		kमुक्त(pending_cb);
	पूर्ण
पूर्ण

अटल व्योम
wake_pending_user_पूर्णांकerrupt_thपढ़ोs(काष्ठा hl_user_पूर्णांकerrupt *पूर्णांकerrupt)
अणु
	काष्ठा hl_user_pending_पूर्णांकerrupt *pend;

	spin_lock(&पूर्णांकerrupt->रुको_list_lock);
	list_क्रम_each_entry(pend, &पूर्णांकerrupt->रुको_list_head, रुको_list_node) अणु
		pend->fence.error = -EIO;
		complete_all(&pend->fence.completion);
	पूर्ण
	spin_unlock(&पूर्णांकerrupt->रुको_list_lock);
पूर्ण

व्योम hl_release_pending_user_पूर्णांकerrupts(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_user_पूर्णांकerrupt *पूर्णांकerrupt;
	पूर्णांक i;

	अगर (!prop->user_पूर्णांकerrupt_count)
		वापस;

	/* We iterate through the user पूर्णांकerrupt requests and waking up all
	 * user thपढ़ोs रुकोing क्रम पूर्णांकerrupt completion. We iterate the
	 * list under a lock, this is why all user thपढ़ोs, once awake,
	 * will रुको on the same lock and will release the रुकोing object upon
	 * unlock.
	 */

	क्रम (i = 0 ; i < prop->user_पूर्णांकerrupt_count ; i++) अणु
		पूर्णांकerrupt = &hdev->user_पूर्णांकerrupt[i];
		wake_pending_user_पूर्णांकerrupt_thपढ़ोs(पूर्णांकerrupt);
	पूर्ण

	पूर्णांकerrupt = &hdev->common_user_पूर्णांकerrupt;
	wake_pending_user_पूर्णांकerrupt_thपढ़ोs(पूर्णांकerrupt);
पूर्ण

अटल व्योम job_wq_completion(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hl_cs_job *job = container_of(work, काष्ठा hl_cs_job,
						finish_work);
	काष्ठा hl_cs *cs = job->cs;
	काष्ठा hl_device *hdev = cs->ctx->hdev;

	/* job is no दीर्घer needed */
	complete_job(hdev, job);
पूर्ण

अटल पूर्णांक validate_queue_index(काष्ठा hl_device *hdev,
				काष्ठा hl_cs_chunk *chunk,
				क्रमागत hl_queue_type *queue_type,
				bool *is_kernel_allocated_cb)
अणु
	काष्ठा asic_fixed_properties *asic = &hdev->asic_prop;
	काष्ठा hw_queue_properties *hw_queue_prop;

	/* This must be checked here to prevent out-of-bounds access to
	 * hw_queues_props array
	 */
	अगर (chunk->queue_index >= asic->max_queues) अणु
		dev_err(hdev->dev, "Queue index %d is invalid\n",
			chunk->queue_index);
		वापस -EINVAL;
	पूर्ण

	hw_queue_prop = &asic->hw_queues_props[chunk->queue_index];

	अगर (hw_queue_prop->type == QUEUE_TYPE_NA) अणु
		dev_err(hdev->dev, "Queue index %d is invalid\n",
			chunk->queue_index);
		वापस -EINVAL;
	पूर्ण

	अगर (hw_queue_prop->driver_only) अणु
		dev_err(hdev->dev,
			"Queue index %d is restricted for the kernel driver\n",
			chunk->queue_index);
		वापस -EINVAL;
	पूर्ण

	/* When hw queue type isn't QUEUE_TYPE_HW,
	 * USER_ALLOC_CB flag shall be referred as "don't care".
	 */
	अगर (hw_queue_prop->type == QUEUE_TYPE_HW) अणु
		अगर (chunk->cs_chunk_flags & HL_CS_CHUNK_FLAGS_USER_ALLOC_CB) अणु
			अगर (!(hw_queue_prop->cb_alloc_flags & CB_ALLOC_USER)) अणु
				dev_err(hdev->dev,
					"Queue index %d doesn't support user CB\n",
					chunk->queue_index);
				वापस -EINVAL;
			पूर्ण

			*is_kernel_allocated_cb = false;
		पूर्ण अन्यथा अणु
			अगर (!(hw_queue_prop->cb_alloc_flags &
					CB_ALLOC_KERNEL)) अणु
				dev_err(hdev->dev,
					"Queue index %d doesn't support kernel CB\n",
					chunk->queue_index);
				वापस -EINVAL;
			पूर्ण

			*is_kernel_allocated_cb = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		*is_kernel_allocated_cb = !!(hw_queue_prop->cb_alloc_flags
						& CB_ALLOC_KERNEL);
	पूर्ण

	*queue_type = hw_queue_prop->type;
	वापस 0;
पूर्ण

अटल काष्ठा hl_cb *get_cb_from_cs_chunk(काष्ठा hl_device *hdev,
					काष्ठा hl_cb_mgr *cb_mgr,
					काष्ठा hl_cs_chunk *chunk)
अणु
	काष्ठा hl_cb *cb;
	u32 cb_handle;

	cb_handle = (u32) (chunk->cb_handle >> PAGE_SHIFT);

	cb = hl_cb_get(hdev, cb_mgr, cb_handle);
	अगर (!cb) अणु
		dev_err(hdev->dev, "CB handle 0x%x invalid\n", cb_handle);
		वापस शून्य;
	पूर्ण

	अगर ((chunk->cb_size < 8) || (chunk->cb_size > cb->size)) अणु
		dev_err(hdev->dev, "CB size %u invalid\n", chunk->cb_size);
		जाओ release_cb;
	पूर्ण

	atomic_inc(&cb->cs_cnt);

	वापस cb;

release_cb:
	hl_cb_put(cb);
	वापस शून्य;
पूर्ण

काष्ठा hl_cs_job *hl_cs_allocate_job(काष्ठा hl_device *hdev,
		क्रमागत hl_queue_type queue_type, bool is_kernel_allocated_cb)
अणु
	काष्ठा hl_cs_job *job;

	job = kzalloc(माप(*job), GFP_ATOMIC);
	अगर (!job)
		job = kzalloc(माप(*job), GFP_KERNEL);

	अगर (!job)
		वापस शून्य;

	kref_init(&job->refcount);
	job->queue_type = queue_type;
	job->is_kernel_allocated_cb = is_kernel_allocated_cb;

	अगर (is_cb_patched(hdev, job))
		INIT_LIST_HEAD(&job->userptr_list);

	अगर (job->queue_type == QUEUE_TYPE_EXT)
		INIT_WORK(&job->finish_work, job_wq_completion);

	वापस job;
पूर्ण

अटल क्रमागत hl_cs_type hl_cs_get_cs_type(u32 cs_type_flags)
अणु
	अगर (cs_type_flags & HL_CS_FLAGS_SIGNAL)
		वापस CS_TYPE_SIGNAL;
	अन्यथा अगर (cs_type_flags & HL_CS_FLAGS_WAIT)
		वापस CS_TYPE_WAIT;
	अन्यथा अगर (cs_type_flags & HL_CS_FLAGS_COLLECTIVE_WAIT)
		वापस CS_TYPE_COLLECTIVE_WAIT;
	अन्यथा
		वापस CS_TYPE_DEFAULT;
पूर्ण

अटल पूर्णांक hl_cs_sanity_checks(काष्ठा hl_fpriv *hpriv, जोड़ hl_cs_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	u32 cs_type_flags, num_chunks;
	क्रमागत hl_device_status status;
	क्रमागत hl_cs_type cs_type;

	अगर (!hl_device_operational(hdev, &status)) अणु
		dev_warn_ratelimited(hdev->dev,
			"Device is %s. Can't submit new CS\n",
			hdev->status[status]);
		वापस -EBUSY;
	पूर्ण

	अगर ((args->in.cs_flags & HL_CS_FLAGS_STAGED_SUBMISSION) &&
			!hdev->supports_staged_submission) अणु
		dev_err(hdev->dev, "staged submission not supported");
		वापस -EPERM;
	पूर्ण

	cs_type_flags = args->in.cs_flags & HL_CS_FLAGS_TYPE_MASK;

	अगर (unlikely(cs_type_flags && !is_घातer_of_2(cs_type_flags))) अणु
		dev_err(hdev->dev,
			"CS type flags are mutually exclusive, context %d\n",
			ctx->asid);
		वापस -EINVAL;
	पूर्ण

	cs_type = hl_cs_get_cs_type(cs_type_flags);
	num_chunks = args->in.num_chunks_execute;

	अगर (unlikely((cs_type != CS_TYPE_DEFAULT) &&
					!hdev->supports_sync_stream)) अणु
		dev_err(hdev->dev, "Sync stream CS is not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cs_type == CS_TYPE_DEFAULT) अणु
		अगर (!num_chunks) अणु
			dev_err(hdev->dev,
				"Got execute CS with 0 chunks, context %d\n",
				ctx->asid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (num_chunks != 1) अणु
		dev_err(hdev->dev,
			"Sync stream CS mandates one chunk only, context %d\n",
			ctx->asid);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hl_cs_copy_chunk_array(काष्ठा hl_device *hdev,
					काष्ठा hl_cs_chunk **cs_chunk_array,
					व्योम __user *chunks, u32 num_chunks,
					काष्ठा hl_ctx *ctx)
अणु
	u32 माप_प्रकारo_copy;

	अगर (num_chunks > HL_MAX_JOBS_PER_CS) अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&hdev->aggregated_cs_counters.validation_drop_cnt);
		dev_err(hdev->dev,
			"Number of chunks can NOT be larger than %d\n",
			HL_MAX_JOBS_PER_CS);
		वापस -EINVAL;
	पूर्ण

	*cs_chunk_array = kदो_स्मृति_array(num_chunks, माप(**cs_chunk_array),
					GFP_ATOMIC);
	अगर (!*cs_chunk_array)
		*cs_chunk_array = kदो_स्मृति_array(num_chunks,
					माप(**cs_chunk_array), GFP_KERNEL);
	अगर (!*cs_chunk_array) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&hdev->aggregated_cs_counters.out_of_mem_drop_cnt);
		वापस -ENOMEM;
	पूर्ण

	माप_प्रकारo_copy = num_chunks * माप(काष्ठा hl_cs_chunk);
	अगर (copy_from_user(*cs_chunk_array, chunks, माप_प्रकारo_copy)) अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&hdev->aggregated_cs_counters.validation_drop_cnt);
		dev_err(hdev->dev, "Failed to copy cs chunk array from user\n");
		kमुक्त(*cs_chunk_array);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_staged_submission(काष्ठा hl_device *hdev, काष्ठा hl_cs *cs,
				u64 sequence, u32 flags)
अणु
	अगर (!(flags & HL_CS_FLAGS_STAGED_SUBMISSION))
		वापस 0;

	cs->staged_last = !!(flags & HL_CS_FLAGS_STAGED_SUBMISSION_LAST);
	cs->staged_first = !!(flags & HL_CS_FLAGS_STAGED_SUBMISSION_FIRST);

	अगर (cs->staged_first) अणु
		/* Staged CS sequence is the first CS sequence */
		INIT_LIST_HEAD(&cs->staged_cs_node);
		cs->staged_sequence = cs->sequence;
	पूर्ण अन्यथा अणु
		/* User sequence will be validated in 'hl_hw_queue_schedule_cs'
		 * under the cs_mirror_lock
		 */
		cs->staged_sequence = sequence;
	पूर्ण

	/* Increment CS reference अगर needed */
	staged_cs_get(hdev, cs);

	cs->staged_cs = true;

	वापस 0;
पूर्ण

अटल पूर्णांक cs_ioctl_शेष(काष्ठा hl_fpriv *hpriv, व्योम __user *chunks,
				u32 num_chunks, u64 *cs_seq, u32 flags,
				u32 समयout)
अणु
	bool staged_mid, पूर्णांक_queues_only = true;
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_cs_chunk *cs_chunk_array;
	काष्ठा hl_cs_counters_atomic *cntr;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	काष्ठा hl_cs_job *job;
	काष्ठा hl_cs *cs;
	काष्ठा hl_cb *cb;
	u64 user_sequence;
	पूर्णांक rc, i;

	cntr = &hdev->aggregated_cs_counters;
	user_sequence = *cs_seq;
	*cs_seq = ULदीर्घ_उच्च;

	rc = hl_cs_copy_chunk_array(hdev, &cs_chunk_array, chunks, num_chunks,
			hpriv->ctx);
	अगर (rc)
		जाओ out;

	अगर ((flags & HL_CS_FLAGS_STAGED_SUBMISSION) &&
			!(flags & HL_CS_FLAGS_STAGED_SUBMISSION_FIRST))
		staged_mid = true;
	अन्यथा
		staged_mid = false;

	rc = allocate_cs(hdev, hpriv->ctx, CS_TYPE_DEFAULT,
			staged_mid ? user_sequence : ULदीर्घ_उच्च, &cs, flags,
			समयout);
	अगर (rc)
		जाओ मुक्त_cs_chunk_array;

	*cs_seq = cs->sequence;

	hl_debugfs_add_cs(cs);

	rc = cs_staged_submission(hdev, cs, user_sequence, flags);
	अगर (rc)
		जाओ मुक्त_cs_object;

	/* Validate ALL the CS chunks beक्रमe submitting the CS */
	क्रम (i = 0 ; i < num_chunks ; i++) अणु
		काष्ठा hl_cs_chunk *chunk = &cs_chunk_array[i];
		क्रमागत hl_queue_type queue_type;
		bool is_kernel_allocated_cb;

		rc = validate_queue_index(hdev, chunk, &queue_type,
						&is_kernel_allocated_cb);
		अगर (rc) अणु
			atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
			atomic64_inc(&cntr->validation_drop_cnt);
			जाओ मुक्त_cs_object;
		पूर्ण

		अगर (is_kernel_allocated_cb) अणु
			cb = get_cb_from_cs_chunk(hdev, &hpriv->cb_mgr, chunk);
			अगर (!cb) अणु
				atomic64_inc(
					&ctx->cs_counters.validation_drop_cnt);
				atomic64_inc(&cntr->validation_drop_cnt);
				rc = -EINVAL;
				जाओ मुक्त_cs_object;
			पूर्ण
		पूर्ण अन्यथा अणु
			cb = (काष्ठा hl_cb *) (uपूर्णांकptr_t) chunk->cb_handle;
		पूर्ण

		अगर (queue_type == QUEUE_TYPE_EXT || queue_type == QUEUE_TYPE_HW)
			पूर्णांक_queues_only = false;

		job = hl_cs_allocate_job(hdev, queue_type,
						is_kernel_allocated_cb);
		अगर (!job) अणु
			atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
			atomic64_inc(&cntr->out_of_mem_drop_cnt);
			dev_err(hdev->dev, "Failed to allocate a new job\n");
			rc = -ENOMEM;
			अगर (is_kernel_allocated_cb)
				जाओ release_cb;

			जाओ मुक्त_cs_object;
		पूर्ण

		job->id = i + 1;
		job->cs = cs;
		job->user_cb = cb;
		job->user_cb_size = chunk->cb_size;
		job->hw_queue_id = chunk->queue_index;

		cs->jobs_in_queue_cnt[job->hw_queue_id]++;

		list_add_tail(&job->cs_node, &cs->job_list);

		/*
		 * Increment CS reference. When CS reference is 0, CS is
		 * करोne and can be संकेतed to user and मुक्त all its resources
		 * Only increment क्रम JOB on बाह्यal or H/W queues, because
		 * only क्रम those JOBs we get completion
		 */
		अगर (cs_needs_completion(cs) &&
			(job->queue_type == QUEUE_TYPE_EXT ||
				job->queue_type == QUEUE_TYPE_HW))
			cs_get(cs);

		hl_debugfs_add_job(hdev, job);

		rc = cs_parser(hpriv, job);
		अगर (rc) अणु
			atomic64_inc(&ctx->cs_counters.parsing_drop_cnt);
			atomic64_inc(&cntr->parsing_drop_cnt);
			dev_err(hdev->dev,
				"Failed to parse JOB %d.%llu.%d, err %d, rejecting the CS\n",
				cs->ctx->asid, cs->sequence, job->id, rc);
			जाओ मुक्त_cs_object;
		पूर्ण
	पूर्ण

	/* We allow a CS with any queue type combination as दीर्घ as it करोes
	 * not get a completion
	 */
	अगर (पूर्णांक_queues_only && cs_needs_completion(cs)) अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&cntr->validation_drop_cnt);
		dev_err(hdev->dev,
			"Reject CS %d.%llu since it contains only internal queues jobs and needs completion\n",
			cs->ctx->asid, cs->sequence);
		rc = -EINVAL;
		जाओ मुक्त_cs_object;
	पूर्ण

	rc = hl_hw_queue_schedule_cs(cs);
	अगर (rc) अणु
		अगर (rc != -EAGAIN)
			dev_err(hdev->dev,
				"Failed to submit CS %d.%llu to H/W queues, error %d\n",
				cs->ctx->asid, cs->sequence, rc);
		जाओ मुक्त_cs_object;
	पूर्ण

	rc = HL_CS_STATUS_SUCCESS;
	जाओ put_cs;

release_cb:
	atomic_dec(&cb->cs_cnt);
	hl_cb_put(cb);
मुक्त_cs_object:
	cs_rollback(hdev, cs);
	*cs_seq = ULदीर्घ_उच्च;
	/* The path below is both क्रम good and erroneous निकासs */
put_cs:
	/* We finished with the CS in this function, so put the ref */
	cs_put(cs);
मुक्त_cs_chunk_array:
	kमुक्त(cs_chunk_array);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक pending_cb_create_job(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
		काष्ठा hl_cs *cs, काष्ठा hl_cb *cb, u32 size, u32 hw_queue_id)
अणु
	काष्ठा hw_queue_properties *hw_queue_prop;
	काष्ठा hl_cs_counters_atomic *cntr;
	काष्ठा hl_cs_job *job;

	hw_queue_prop = &hdev->asic_prop.hw_queues_props[hw_queue_id];
	cntr = &hdev->aggregated_cs_counters;

	job = hl_cs_allocate_job(hdev, hw_queue_prop->type, true);
	अगर (!job) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		dev_err(hdev->dev, "Failed to allocate a new job\n");
		वापस -ENOMEM;
	पूर्ण

	job->id = 0;
	job->cs = cs;
	job->user_cb = cb;
	atomic_inc(&job->user_cb->cs_cnt);
	job->user_cb_size = size;
	job->hw_queue_id = hw_queue_id;
	job->patched_cb = job->user_cb;
	job->job_cb_size = job->user_cb_size;

	/* increment refcount as क्रम बाह्यal queues we get completion */
	cs_get(cs);

	cs->jobs_in_queue_cnt[job->hw_queue_id]++;

	list_add_tail(&job->cs_node, &cs->job_list);

	hl_debugfs_add_job(hdev, job);

	वापस 0;
पूर्ण

अटल पूर्णांक hl_submit_pending_cb(काष्ठा hl_fpriv *hpriv)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	काष्ठा hl_pending_cb *pending_cb, *पंचांगp;
	काष्ठा list_head local_cb_list;
	काष्ठा hl_cs *cs;
	काष्ठा hl_cb *cb;
	u32 hw_queue_id;
	u32 cb_size;
	पूर्णांक process_list, rc = 0;

	अगर (list_empty(&ctx->pending_cb_list))
		वापस 0;

	process_list = atomic_cmpxchg(&ctx->thपढ़ो_pending_cb_token, 1, 0);

	/* Only a single thपढ़ो is allowed to process the list */
	अगर (!process_list)
		वापस 0;

	अगर (list_empty(&ctx->pending_cb_list))
		जाओ मुक्त_pending_cb_token;

	/* move all list elements to a local list */
	INIT_LIST_HEAD(&local_cb_list);
	spin_lock(&ctx->pending_cb_lock);
	list_क्रम_each_entry_safe(pending_cb, पंचांगp, &ctx->pending_cb_list,
								cb_node)
		list_move_tail(&pending_cb->cb_node, &local_cb_list);
	spin_unlock(&ctx->pending_cb_lock);

	rc = allocate_cs(hdev, ctx, CS_TYPE_DEFAULT, ULदीर्घ_उच्च, &cs, 0,
				hdev->समयout_jअगरfies);
	अगर (rc)
		जाओ add_list_elements;

	hl_debugfs_add_cs(cs);

	/* Iterate through pending cb list, create jobs and add to CS */
	list_क्रम_each_entry(pending_cb, &local_cb_list, cb_node) अणु
		cb = pending_cb->cb;
		cb_size = pending_cb->cb_size;
		hw_queue_id = pending_cb->hw_queue_id;

		rc = pending_cb_create_job(hdev, ctx, cs, cb, cb_size,
								hw_queue_id);
		अगर (rc)
			जाओ मुक्त_cs_object;
	पूर्ण

	rc = hl_hw_queue_schedule_cs(cs);
	अगर (rc) अणु
		अगर (rc != -EAGAIN)
			dev_err(hdev->dev,
				"Failed to submit CS %d.%llu (%d)\n",
				ctx->asid, cs->sequence, rc);
		जाओ मुक्त_cs_object;
	पूर्ण

	/* pending cb was scheduled successfully */
	list_क्रम_each_entry_safe(pending_cb, पंचांगp, &local_cb_list, cb_node) अणु
		list_del(&pending_cb->cb_node);
		kमुक्त(pending_cb);
	पूर्ण

	cs_put(cs);

	जाओ मुक्त_pending_cb_token;

मुक्त_cs_object:
	cs_rollback(hdev, cs);
	cs_put(cs);
add_list_elements:
	spin_lock(&ctx->pending_cb_lock);
	list_क्रम_each_entry_safe_reverse(pending_cb, पंचांगp, &local_cb_list,
								cb_node)
		list_move(&pending_cb->cb_node, &ctx->pending_cb_list);
	spin_unlock(&ctx->pending_cb_lock);
मुक्त_pending_cb_token:
	atomic_set(&ctx->thपढ़ो_pending_cb_token, 1);

	वापस rc;
पूर्ण

अटल पूर्णांक hl_cs_ctx_चयन(काष्ठा hl_fpriv *hpriv, जोड़ hl_cs_args *args,
				u64 *cs_seq)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	bool need_soft_reset = false;
	पूर्णांक rc = 0, करो_ctx_चयन;
	व्योम __user *chunks;
	u32 num_chunks, पंचांगp;
	पूर्णांक ret;

	करो_ctx_चयन = atomic_cmpxchg(&ctx->thपढ़ो_ctx_चयन_token, 1, 0);

	अगर (करो_ctx_चयन || (args->in.cs_flags & HL_CS_FLAGS_FORCE_RESTORE)) अणु
		mutex_lock(&hpriv->restore_phase_mutex);

		अगर (करो_ctx_चयन) अणु
			rc = hdev->asic_funcs->context_चयन(hdev, ctx->asid);
			अगर (rc) अणु
				dev_err_ratelimited(hdev->dev,
					"Failed to switch to context %d, rejecting CS! %d\n",
					ctx->asid, rc);
				/*
				 * If we समयकरोut, or अगर the device is not IDLE
				 * जबतक we want to करो context-चयन (-EBUSY),
				 * we need to soft-reset because QMAN is
				 * probably stuck. However, we can't call to
				 * reset here directly because of deadlock, so
				 * need to करो it at the very end of this
				 * function
				 */
				अगर ((rc == -ETIMEDOUT) || (rc == -EBUSY))
					need_soft_reset = true;
				mutex_unlock(&hpriv->restore_phase_mutex);
				जाओ out;
			पूर्ण
		पूर्ण

		hdev->asic_funcs->restore_phase_topology(hdev);

		chunks = (व्योम __user *) (uपूर्णांकptr_t) args->in.chunks_restore;
		num_chunks = args->in.num_chunks_restore;

		अगर (!num_chunks) अणु
			dev_dbg(hdev->dev,
				"Need to run restore phase but restore CS is empty\n");
			rc = 0;
		पूर्ण अन्यथा अणु
			rc = cs_ioctl_शेष(hpriv, chunks, num_chunks,
					cs_seq, 0, hdev->समयout_jअगरfies);
		पूर्ण

		mutex_unlock(&hpriv->restore_phase_mutex);

		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to submit restore CS for context %d (%d)\n",
				ctx->asid, rc);
			जाओ out;
		पूर्ण

		/* Need to रुको क्रम restore completion beक्रमe execution phase */
		अगर (num_chunks) अणु
			क्रमागत hl_cs_रुको_status status;
रुको_again:
			ret = _hl_cs_रुको_ioctl(hdev, ctx,
					jअगरfies_to_usecs(hdev->समयout_jअगरfies),
					*cs_seq, &status, शून्य);
			अगर (ret) अणु
				अगर (ret == -ERESTARTSYS) अणु
					usleep_range(100, 200);
					जाओ रुको_again;
				पूर्ण

				dev_err(hdev->dev,
					"Restore CS for context %d failed to complete %d\n",
					ctx->asid, ret);
				rc = -ENOEXEC;
				जाओ out;
			पूर्ण
		पूर्ण

		ctx->thपढ़ो_ctx_चयन_रुको_token = 1;

	पूर्ण अन्यथा अगर (!ctx->thपढ़ो_ctx_चयन_रुको_token) अणु
		rc = hl_poll_समयout_memory(hdev,
			&ctx->thपढ़ो_ctx_चयन_रुको_token, पंचांगp, (पंचांगp == 1),
			100, jअगरfies_to_usecs(hdev->समयout_jअगरfies), false);

		अगर (rc == -ETIMEDOUT) अणु
			dev_err(hdev->dev,
				"context switch phase timeout (%d)\n", पंचांगp);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर ((rc == -ETIMEDOUT || rc == -EBUSY) && (need_soft_reset))
		hl_device_reset(hdev, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक cs_ioctl_extract_संकेत_seq(काष्ठा hl_device *hdev,
		काष्ठा hl_cs_chunk *chunk, u64 *संकेत_seq, काष्ठा hl_ctx *ctx)
अणु
	u64 *संकेत_seq_arr = शून्य;
	u32 माप_प्रकारo_copy, संकेत_seq_arr_len;
	पूर्णांक rc = 0;

	संकेत_seq_arr_len = chunk->num_संकेत_seq_arr;

	/* currently only one संकेत seq is supported */
	अगर (संकेत_seq_arr_len != 1) अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&hdev->aggregated_cs_counters.validation_drop_cnt);
		dev_err(hdev->dev,
			"Wait for signal CS supports only one signal CS seq\n");
		वापस -EINVAL;
	पूर्ण

	संकेत_seq_arr = kदो_स्मृति_array(संकेत_seq_arr_len,
					माप(*संकेत_seq_arr),
					GFP_ATOMIC);
	अगर (!संकेत_seq_arr)
		संकेत_seq_arr = kदो_स्मृति_array(संकेत_seq_arr_len,
					माप(*संकेत_seq_arr),
					GFP_KERNEL);
	अगर (!संकेत_seq_arr) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&hdev->aggregated_cs_counters.out_of_mem_drop_cnt);
		वापस -ENOMEM;
	पूर्ण

	माप_प्रकारo_copy = chunk->num_संकेत_seq_arr * माप(*संकेत_seq_arr);
	अगर (copy_from_user(संकेत_seq_arr,
				u64_to_user_ptr(chunk->संकेत_seq_arr),
				माप_प्रकारo_copy)) अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&hdev->aggregated_cs_counters.validation_drop_cnt);
		dev_err(hdev->dev,
			"Failed to copy signal seq array from user\n");
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	/* currently it is guaranteed to have only one संकेत seq */
	*संकेत_seq = संकेत_seq_arr[0];

out:
	kमुक्त(संकेत_seq_arr);

	वापस rc;
पूर्ण

अटल पूर्णांक cs_ioctl_संकेत_रुको_create_jobs(काष्ठा hl_device *hdev,
		काष्ठा hl_ctx *ctx, काष्ठा hl_cs *cs, क्रमागत hl_queue_type q_type,
		u32 q_idx)
अणु
	काष्ठा hl_cs_counters_atomic *cntr;
	काष्ठा hl_cs_job *job;
	काष्ठा hl_cb *cb;
	u32 cb_size;

	cntr = &hdev->aggregated_cs_counters;

	job = hl_cs_allocate_job(hdev, q_type, true);
	अगर (!job) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		dev_err(hdev->dev, "Failed to allocate a new job\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (cs->type == CS_TYPE_WAIT)
		cb_size = hdev->asic_funcs->get_रुको_cb_size(hdev);
	अन्यथा
		cb_size = hdev->asic_funcs->get_संकेत_cb_size(hdev);

	cb = hl_cb_kernel_create(hdev, cb_size,
				q_type == QUEUE_TYPE_HW && hdev->mmu_enable);
	अगर (!cb) अणु
		atomic64_inc(&ctx->cs_counters.out_of_mem_drop_cnt);
		atomic64_inc(&cntr->out_of_mem_drop_cnt);
		kमुक्त(job);
		वापस -EFAULT;
	पूर्ण

	job->id = 0;
	job->cs = cs;
	job->user_cb = cb;
	atomic_inc(&job->user_cb->cs_cnt);
	job->user_cb_size = cb_size;
	job->hw_queue_id = q_idx;

	/*
	 * No need in parsing, user CB is the patched CB.
	 * We call hl_cb_destroy() out of two reasons - we करोn't need the CB in
	 * the CB idr anymore and to decrement its refcount as it was
	 * incremented inside hl_cb_kernel_create().
	 */
	job->patched_cb = job->user_cb;
	job->job_cb_size = job->user_cb_size;
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb->id << PAGE_SHIFT);

	/* increment refcount as क्रम बाह्यal queues we get completion */
	cs_get(cs);

	cs->jobs_in_queue_cnt[job->hw_queue_id]++;

	list_add_tail(&job->cs_node, &cs->job_list);

	hl_debugfs_add_job(hdev, job);

	वापस 0;
पूर्ण

अटल पूर्णांक cs_ioctl_संकेत_रुको(काष्ठा hl_fpriv *hpriv, क्रमागत hl_cs_type cs_type,
				व्योम __user *chunks, u32 num_chunks,
				u64 *cs_seq, u32 flags, u32 समयout)
अणु
	काष्ठा hl_cs_chunk *cs_chunk_array, *chunk;
	काष्ठा hw_queue_properties *hw_queue_prop;
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_cs_compl *sig_रुकोcs_cmpl;
	u32 q_idx, collective_engine_id = 0;
	काष्ठा hl_cs_counters_atomic *cntr;
	काष्ठा hl_fence *sig_fence = शून्य;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	क्रमागत hl_queue_type q_type;
	काष्ठा hl_cs *cs;
	u64 संकेत_seq;
	पूर्णांक rc;

	cntr = &hdev->aggregated_cs_counters;
	*cs_seq = ULदीर्घ_उच्च;

	rc = hl_cs_copy_chunk_array(hdev, &cs_chunk_array, chunks, num_chunks,
			ctx);
	अगर (rc)
		जाओ out;

	/* currently it is guaranteed to have only one chunk */
	chunk = &cs_chunk_array[0];

	अगर (chunk->queue_index >= hdev->asic_prop.max_queues) अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&cntr->validation_drop_cnt);
		dev_err(hdev->dev, "Queue index %d is invalid\n",
			chunk->queue_index);
		rc = -EINVAL;
		जाओ मुक्त_cs_chunk_array;
	पूर्ण

	q_idx = chunk->queue_index;
	hw_queue_prop = &hdev->asic_prop.hw_queues_props[q_idx];
	q_type = hw_queue_prop->type;

	अगर (!hw_queue_prop->supports_sync_stream) अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&cntr->validation_drop_cnt);
		dev_err(hdev->dev,
			"Queue index %d does not support sync stream operations\n",
			q_idx);
		rc = -EINVAL;
		जाओ मुक्त_cs_chunk_array;
	पूर्ण

	अगर (cs_type == CS_TYPE_COLLECTIVE_WAIT) अणु
		अगर (!(hw_queue_prop->collective_mode == HL_COLLECTIVE_MASTER)) अणु
			atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
			atomic64_inc(&cntr->validation_drop_cnt);
			dev_err(hdev->dev,
				"Queue index %d is invalid\n", q_idx);
			rc = -EINVAL;
			जाओ मुक्त_cs_chunk_array;
		पूर्ण

		collective_engine_id = chunk->collective_engine_id;
	पूर्ण

	अगर (cs_type == CS_TYPE_WAIT || cs_type == CS_TYPE_COLLECTIVE_WAIT) अणु
		rc = cs_ioctl_extract_संकेत_seq(hdev, chunk, &संकेत_seq, ctx);
		अगर (rc)
			जाओ मुक्त_cs_chunk_array;

		sig_fence = hl_ctx_get_fence(ctx, संकेत_seq);
		अगर (IS_ERR(sig_fence)) अणु
			atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
			atomic64_inc(&cntr->validation_drop_cnt);
			dev_err(hdev->dev,
				"Failed to get signal CS with seq 0x%llx\n",
				संकेत_seq);
			rc = PTR_ERR(sig_fence);
			जाओ मुक्त_cs_chunk_array;
		पूर्ण

		अगर (!sig_fence) अणु
			/* संकेत CS alपढ़ोy finished */
			rc = 0;
			जाओ मुक्त_cs_chunk_array;
		पूर्ण

		sig_रुकोcs_cmpl =
			container_of(sig_fence, काष्ठा hl_cs_compl, base_fence);

		अगर (sig_रुकोcs_cmpl->type != CS_TYPE_SIGNAL) अणु
			atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
			atomic64_inc(&cntr->validation_drop_cnt);
			dev_err(hdev->dev,
				"CS seq 0x%llx is not of a signal CS\n",
				संकेत_seq);
			hl_fence_put(sig_fence);
			rc = -EINVAL;
			जाओ मुक्त_cs_chunk_array;
		पूर्ण

		अगर (completion_करोne(&sig_fence->completion)) अणु
			/* संकेत CS alपढ़ोy finished */
			hl_fence_put(sig_fence);
			rc = 0;
			जाओ मुक्त_cs_chunk_array;
		पूर्ण
	पूर्ण

	rc = allocate_cs(hdev, ctx, cs_type, ULदीर्घ_उच्च, &cs, flags, समयout);
	अगर (rc) अणु
		अगर (cs_type == CS_TYPE_WAIT ||
			cs_type == CS_TYPE_COLLECTIVE_WAIT)
			hl_fence_put(sig_fence);
		जाओ मुक्त_cs_chunk_array;
	पूर्ण

	/*
	 * Save the संकेत CS fence क्रम later initialization right beक्रमe
	 * hanging the रुको CS on the queue.
	 */
	अगर (cs_type == CS_TYPE_WAIT || cs_type == CS_TYPE_COLLECTIVE_WAIT)
		cs->संकेत_fence = sig_fence;

	hl_debugfs_add_cs(cs);

	*cs_seq = cs->sequence;

	अगर (cs_type == CS_TYPE_WAIT || cs_type == CS_TYPE_SIGNAL)
		rc = cs_ioctl_संकेत_रुको_create_jobs(hdev, ctx, cs, q_type,
				q_idx);
	अन्यथा अगर (cs_type == CS_TYPE_COLLECTIVE_WAIT)
		rc = hdev->asic_funcs->collective_रुको_create_jobs(hdev, ctx,
				cs, q_idx, collective_engine_id);
	अन्यथा अणु
		atomic64_inc(&ctx->cs_counters.validation_drop_cnt);
		atomic64_inc(&cntr->validation_drop_cnt);
		rc = -EINVAL;
	पूर्ण

	अगर (rc)
		जाओ मुक्त_cs_object;

	rc = hl_hw_queue_schedule_cs(cs);
	अगर (rc) अणु
		अगर (rc != -EAGAIN)
			dev_err(hdev->dev,
				"Failed to submit CS %d.%llu to H/W queues, error %d\n",
				ctx->asid, cs->sequence, rc);
		जाओ मुक्त_cs_object;
	पूर्ण

	rc = HL_CS_STATUS_SUCCESS;
	जाओ put_cs;

मुक्त_cs_object:
	cs_rollback(hdev, cs);
	*cs_seq = ULदीर्घ_उच्च;
	/* The path below is both क्रम good and erroneous निकासs */
put_cs:
	/* We finished with the CS in this function, so put the ref */
	cs_put(cs);
मुक्त_cs_chunk_array:
	kमुक्त(cs_chunk_array);
out:
	वापस rc;
पूर्ण

पूर्णांक hl_cs_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	जोड़ hl_cs_args *args = data;
	क्रमागत hl_cs_type cs_type;
	u64 cs_seq = अच_दीर्घ_उच्च;
	व्योम __user *chunks;
	u32 num_chunks, flags, समयout;
	पूर्णांक rc;

	rc = hl_cs_sanity_checks(hpriv, args);
	अगर (rc)
		जाओ out;

	rc = hl_cs_ctx_चयन(hpriv, args, &cs_seq);
	अगर (rc)
		जाओ out;

	rc = hl_submit_pending_cb(hpriv);
	अगर (rc)
		जाओ out;

	cs_type = hl_cs_get_cs_type(args->in.cs_flags &
					~HL_CS_FLAGS_FORCE_RESTORE);
	chunks = (व्योम __user *) (uपूर्णांकptr_t) args->in.chunks_execute;
	num_chunks = args->in.num_chunks_execute;
	flags = args->in.cs_flags;

	/* In हाल this is a staged CS, user should supply the CS sequence */
	अगर ((flags & HL_CS_FLAGS_STAGED_SUBMISSION) &&
			!(flags & HL_CS_FLAGS_STAGED_SUBMISSION_FIRST))
		cs_seq = args->in.seq;

	समयout = flags & HL_CS_FLAGS_CUSTOM_TIMEOUT
			? msecs_to_jअगरfies(args->in.समयout * 1000)
			: hpriv->hdev->समयout_jअगरfies;

	चयन (cs_type) अणु
	हाल CS_TYPE_SIGNAL:
	हाल CS_TYPE_WAIT:
	हाल CS_TYPE_COLLECTIVE_WAIT:
		rc = cs_ioctl_संकेत_रुको(hpriv, cs_type, chunks, num_chunks,
					&cs_seq, args->in.cs_flags, समयout);
		अवरोध;
	शेष:
		rc = cs_ioctl_शेष(hpriv, chunks, num_chunks, &cs_seq,
						args->in.cs_flags, समयout);
		अवरोध;
	पूर्ण

out:
	अगर (rc != -EAGAIN) अणु
		स_रखो(args, 0, माप(*args));
		args->out.status = rc;
		args->out.seq = cs_seq;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक _hl_cs_रुको_ioctl(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
				u64 समयout_us, u64 seq,
				क्रमागत hl_cs_रुको_status *status, s64 *बारtamp)
अणु
	काष्ठा hl_fence *fence;
	अचिन्हित दीर्घ समयout;
	पूर्णांक rc = 0;
	दीर्घ completion_rc;

	अगर (बारtamp)
		*बारtamp = 0;

	अगर (समयout_us == MAX_SCHEDULE_TIMEOUT)
		समयout = समयout_us;
	अन्यथा
		समयout = usecs_to_jअगरfies(समयout_us);

	hl_ctx_get(hdev, ctx);

	fence = hl_ctx_get_fence(ctx, seq);
	अगर (IS_ERR(fence)) अणु
		rc = PTR_ERR(fence);
		अगर (rc == -EINVAL)
			dev_notice_ratelimited(hdev->dev,
				"Can't wait on CS %llu because current CS is at seq %llu\n",
				seq, ctx->cs_sequence);
	पूर्ण अन्यथा अगर (fence) अणु
		अगर (!समयout_us)
			completion_rc = completion_करोne(&fence->completion);
		अन्यथा
			completion_rc =
				रुको_क्रम_completion_पूर्णांकerruptible_समयout(
					&fence->completion, समयout);

		अगर (completion_rc > 0) अणु
			*status = CS_WAIT_STATUS_COMPLETED;
			अगर (बारtamp)
				*बारtamp = kसमय_प्रकारo_ns(fence->बारtamp);
		पूर्ण अन्यथा अणु
			*status = CS_WAIT_STATUS_BUSY;
		पूर्ण

		अगर (fence->error == -ETIMEDOUT)
			rc = -ETIMEDOUT;
		अन्यथा अगर (fence->error == -EIO)
			rc = -EIO;

		hl_fence_put(fence);
	पूर्ण अन्यथा अणु
		dev_dbg(hdev->dev,
			"Can't wait on seq %llu because current CS is at seq %llu (Fence is gone)\n",
			seq, ctx->cs_sequence);
		*status = CS_WAIT_STATUS_GONE;
	पूर्ण

	hl_ctx_put(ctx);

	वापस rc;
पूर्ण

अटल पूर्णांक hl_cs_रुको_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	जोड़ hl_रुको_cs_args *args = data;
	क्रमागत hl_cs_रुको_status status;
	u64 seq = args->in.seq;
	s64 बारtamp;
	पूर्णांक rc;

	rc = _hl_cs_रुको_ioctl(hdev, hpriv->ctx, args->in.समयout_us, seq,
				&status, &बारtamp);

	स_रखो(args, 0, माप(*args));

	अगर (rc) अणु
		अगर (rc == -ERESTARTSYS) अणु
			dev_err_ratelimited(hdev->dev,
				"user process got signal while waiting for CS handle %llu\n",
				seq);
			args->out.status = HL_WAIT_CS_STATUS_INTERRUPTED;
			rc = -EINTR;
		पूर्ण अन्यथा अगर (rc == -ETIMEDOUT) अणु
			dev_err_ratelimited(hdev->dev,
				"CS %llu has timed-out while user process is waiting for it\n",
				seq);
			args->out.status = HL_WAIT_CS_STATUS_TIMEDOUT;
		पूर्ण अन्यथा अगर (rc == -EIO) अणु
			dev_err_ratelimited(hdev->dev,
				"CS %llu has been aborted while user process is waiting for it\n",
				seq);
			args->out.status = HL_WAIT_CS_STATUS_ABORTED;
		पूर्ण
		वापस rc;
	पूर्ण

	अगर (बारtamp) अणु
		args->out.flags |= HL_WAIT_CS_STATUS_FLAG_TIMESTAMP_VLD;
		args->out.बारtamp_nsec = बारtamp;
	पूर्ण

	चयन (status) अणु
	हाल CS_WAIT_STATUS_GONE:
		args->out.flags |= HL_WAIT_CS_STATUS_FLAG_GONE;
		fallthrough;
	हाल CS_WAIT_STATUS_COMPLETED:
		args->out.status = HL_WAIT_CS_STATUS_COMPLETED;
		अवरोध;
	हाल CS_WAIT_STATUS_BUSY:
	शेष:
		args->out.status = HL_WAIT_CS_STATUS_BUSY;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _hl_पूर्णांकerrupt_रुको_ioctl(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
				u32 समयout_us, u64 user_address,
				u32 target_value, u16 पूर्णांकerrupt_offset,
				क्रमागत hl_cs_रुको_status *status)
अणु
	काष्ठा hl_user_pending_पूर्णांकerrupt *pend;
	काष्ठा hl_user_पूर्णांकerrupt *पूर्णांकerrupt;
	अचिन्हित दीर्घ समयout;
	दीर्घ completion_rc;
	u32 completion_value;
	पूर्णांक rc = 0;

	अगर (समयout_us == U32_MAX)
		समयout = समयout_us;
	अन्यथा
		समयout = usecs_to_jअगरfies(समयout_us);

	hl_ctx_get(hdev, ctx);

	pend = kदो_स्मृति(माप(*pend), GFP_KERNEL);
	अगर (!pend) अणु
		hl_ctx_put(ctx);
		वापस -ENOMEM;
	पूर्ण

	hl_fence_init(&pend->fence, अच_दीर्घ_उच्च);

	अगर (पूर्णांकerrupt_offset == HL_COMMON_USER_INTERRUPT_ID)
		पूर्णांकerrupt = &hdev->common_user_पूर्णांकerrupt;
	अन्यथा
		पूर्णांकerrupt = &hdev->user_पूर्णांकerrupt[पूर्णांकerrupt_offset];

	spin_lock(&पूर्णांकerrupt->रुको_list_lock);
	अगर (!hl_device_operational(hdev, शून्य)) अणु
		rc = -EPERM;
		जाओ unlock_and_मुक्त_fence;
	पूर्ण

	अगर (copy_from_user(&completion_value, u64_to_user_ptr(user_address), 4)) अणु
		dev_err(hdev->dev,
			"Failed to copy completion value from user\n");
		rc = -EFAULT;
		जाओ unlock_and_मुक्त_fence;
	पूर्ण

	अगर (completion_value >= target_value)
		*status = CS_WAIT_STATUS_COMPLETED;
	अन्यथा
		*status = CS_WAIT_STATUS_BUSY;

	अगर (!समयout_us || (*status == CS_WAIT_STATUS_COMPLETED))
		जाओ unlock_and_मुक्त_fence;

	/* Add pending user पूर्णांकerrupt to relevant list क्रम the पूर्णांकerrupt
	 * handler to monitor
	 */
	list_add_tail(&pend->रुको_list_node, &पूर्णांकerrupt->रुको_list_head);
	spin_unlock(&पूर्णांकerrupt->रुको_list_lock);

रुको_again:
	/* Wait क्रम पूर्णांकerrupt handler to संकेत completion */
	completion_rc =
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&pend->fence.completion, समयout);

	/* If समयout did not expire we need to perक्रमm the comparison.
	 * If comparison fails, keep रुकोing until समयout expires
	 */
	अगर (completion_rc > 0) अणु
		अगर (copy_from_user(&completion_value,
				u64_to_user_ptr(user_address), 4)) अणु
			dev_err(hdev->dev,
				"Failed to copy completion value from user\n");
			rc = -EFAULT;
			जाओ हटाओ_pending_user_पूर्णांकerrupt;
		पूर्ण

		अगर (completion_value >= target_value) अणु
			*status = CS_WAIT_STATUS_COMPLETED;
		पूर्ण अन्यथा अणु
			समयout = completion_rc;
			जाओ रुको_again;
		पूर्ण
	पूर्ण अन्यथा अणु
		*status = CS_WAIT_STATUS_BUSY;
	पूर्ण

हटाओ_pending_user_पूर्णांकerrupt:
	spin_lock(&पूर्णांकerrupt->रुको_list_lock);
	list_del(&pend->रुको_list_node);

unlock_and_मुक्त_fence:
	spin_unlock(&पूर्णांकerrupt->रुको_list_lock);
	kमुक्त(pend);
	hl_ctx_put(ctx);

	वापस rc;
पूर्ण

अटल पूर्णांक hl_पूर्णांकerrupt_रुको_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	u16 पूर्णांकerrupt_id, पूर्णांकerrupt_offset, first_पूर्णांकerrupt, last_पूर्णांकerrupt;
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा asic_fixed_properties *prop;
	जोड़ hl_रुको_cs_args *args = data;
	क्रमागत hl_cs_रुको_status status;
	पूर्णांक rc;

	prop = &hdev->asic_prop;

	अगर (!prop->user_पूर्णांकerrupt_count) अणु
		dev_err(hdev->dev, "no user interrupts allowed");
		वापस -EPERM;
	पूर्ण

	पूर्णांकerrupt_id =
		FIELD_GET(HL_WAIT_CS_FLAGS_INTERRUPT_MASK, args->in.flags);

	first_पूर्णांकerrupt = prop->first_available_user_msix_पूर्णांकerrupt;
	last_पूर्णांकerrupt = prop->first_available_user_msix_पूर्णांकerrupt +
						prop->user_पूर्णांकerrupt_count - 1;

	अगर ((पूर्णांकerrupt_id < first_पूर्णांकerrupt || पूर्णांकerrupt_id > last_पूर्णांकerrupt) &&
			पूर्णांकerrupt_id != HL_COMMON_USER_INTERRUPT_ID) अणु
		dev_err(hdev->dev, "invalid user interrupt %u", पूर्णांकerrupt_id);
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकerrupt_id == HL_COMMON_USER_INTERRUPT_ID)
		पूर्णांकerrupt_offset = HL_COMMON_USER_INTERRUPT_ID;
	अन्यथा
		पूर्णांकerrupt_offset = पूर्णांकerrupt_id - first_पूर्णांकerrupt;

	rc = _hl_पूर्णांकerrupt_रुको_ioctl(hdev, hpriv->ctx,
				args->in.पूर्णांकerrupt_समयout_us, args->in.addr,
				args->in.target, पूर्णांकerrupt_offset, &status);

	स_रखो(args, 0, माप(*args));

	अगर (rc) अणु
		dev_err_ratelimited(hdev->dev,
			"interrupt_wait_ioctl failed (%d)\n", rc);

		वापस rc;
	पूर्ण

	चयन (status) अणु
	हाल CS_WAIT_STATUS_COMPLETED:
		args->out.status = HL_WAIT_CS_STATUS_COMPLETED;
		अवरोध;
	हाल CS_WAIT_STATUS_BUSY:
	शेष:
		args->out.status = HL_WAIT_CS_STATUS_BUSY;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hl_रुको_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	जोड़ hl_रुको_cs_args *args = data;
	u32 flags = args->in.flags;
	पूर्णांक rc;

	अगर (flags & HL_WAIT_CS_FLAGS_INTERRUPT)
		rc = hl_पूर्णांकerrupt_रुको_ioctl(hpriv, data);
	अन्यथा
		rc = hl_cs_रुको_ioctl(hpriv, data);

	वापस rc;
पूर्ण
