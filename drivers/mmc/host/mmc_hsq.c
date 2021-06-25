<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *
 * MMC software queue support based on command queue पूर्णांकerfaces
 *
 * Copyright (C) 2019 Linaro, Inc.
 * Author: Baolin Wang <baolin.wang@linaro.org>
 */

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>

#समावेश "mmc_hsq.h"

#घोषणा HSQ_NUM_SLOTS	64
#घोषणा HSQ_INVALID_TAG	HSQ_NUM_SLOTS

अटल व्योम mmc_hsq_retry_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_hsq *hsq = container_of(work, काष्ठा mmc_hsq, retry_work);
	काष्ठा mmc_host *mmc = hsq->mmc;

	mmc->ops->request(mmc, hsq->mrq);
पूर्ण

अटल व्योम mmc_hsq_pump_requests(काष्ठा mmc_hsq *hsq)
अणु
	काष्ठा mmc_host *mmc = hsq->mmc;
	काष्ठा hsq_slot *slot;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hsq->lock, flags);

	/* Make sure we are not alपढ़ोy running a request now */
	अगर (hsq->mrq) अणु
		spin_unlock_irqrestore(&hsq->lock, flags);
		वापस;
	पूर्ण

	/* Make sure there are reमुख्य requests need to pump */
	अगर (!hsq->qcnt || !hsq->enabled) अणु
		spin_unlock_irqrestore(&hsq->lock, flags);
		वापस;
	पूर्ण

	slot = &hsq->slot[hsq->next_tag];
	hsq->mrq = slot->mrq;
	hsq->qcnt--;

	spin_unlock_irqrestore(&hsq->lock, flags);

	अगर (mmc->ops->request_atomic)
		ret = mmc->ops->request_atomic(mmc, hsq->mrq);
	अन्यथा
		mmc->ops->request(mmc, hsq->mrq);

	/*
	 * If वापसing BUSY from request_atomic(), which means the card
	 * may be busy now, and we should change to non-atomic context to
	 * try again क्रम this unusual हाल, to aव्योम समय-consuming operations
	 * in the atomic context.
	 *
	 * Note: we just give a warning क्रम other error हालs, since the host
	 * driver will handle them.
	 */
	अगर (ret == -EBUSY)
		schedule_work(&hsq->retry_work);
	अन्यथा
		WARN_ON_ONCE(ret);
पूर्ण

अटल व्योम mmc_hsq_update_next_tag(काष्ठा mmc_hsq *hsq, पूर्णांक reमुख्यs)
अणु
	काष्ठा hsq_slot *slot;
	पूर्णांक tag;

	/*
	 * If there are no reमुख्य requests in software queue, then set a invalid
	 * tag.
	 */
	अगर (!reमुख्यs) अणु
		hsq->next_tag = HSQ_INVALID_TAG;
		वापस;
	पूर्ण

	/*
	 * Increasing the next tag and check अगर the corresponding request is
	 * available, अगर yes, then we found a candidate request.
	 */
	अगर (++hsq->next_tag != HSQ_INVALID_TAG) अणु
		slot = &hsq->slot[hsq->next_tag];
		अगर (slot->mrq)
			वापस;
	पूर्ण

	/* Othersie we should iterate all slots to find a available tag. */
	क्रम (tag = 0; tag < HSQ_NUM_SLOTS; tag++) अणु
		slot = &hsq->slot[tag];
		अगर (slot->mrq)
			अवरोध;
	पूर्ण

	अगर (tag == HSQ_NUM_SLOTS)
		tag = HSQ_INVALID_TAG;

	hsq->next_tag = tag;
पूर्ण

अटल व्योम mmc_hsq_post_request(काष्ठा mmc_hsq *hsq)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक reमुख्यs;

	spin_lock_irqsave(&hsq->lock, flags);

	reमुख्यs = hsq->qcnt;
	hsq->mrq = शून्य;

	/* Update the next available tag to be queued. */
	mmc_hsq_update_next_tag(hsq, reमुख्यs);

	अगर (hsq->रुकोing_क्रम_idle && !reमुख्यs) अणु
		hsq->रुकोing_क्रम_idle = false;
		wake_up(&hsq->रुको_queue);
	पूर्ण

	/* Do not pump new request in recovery mode. */
	अगर (hsq->recovery_halt) अणु
		spin_unlock_irqrestore(&hsq->lock, flags);
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&hsq->lock, flags);

	 /*
	  * Try to pump new request to host controller as fast as possible,
	  * after completing previous request.
	  */
	अगर (reमुख्यs > 0)
		mmc_hsq_pump_requests(hsq);
पूर्ण

/**
 * mmc_hsq_finalize_request - finalize one request अगर the request is करोne
 * @mmc: the host controller
 * @mrq: the request need to be finalized
 *
 * Return true अगर we finalized the corresponding request in software queue,
 * otherwise वापस false.
 */
bool mmc_hsq_finalize_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_hsq *hsq = mmc->cqe_निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsq->lock, flags);

	अगर (!hsq->enabled || !hsq->mrq || hsq->mrq != mrq) अणु
		spin_unlock_irqrestore(&hsq->lock, flags);
		वापस false;
	पूर्ण

	/*
	 * Clear current completed slot request to make a room क्रम new request.
	 */
	hsq->slot[hsq->next_tag].mrq = शून्य;

	spin_unlock_irqrestore(&hsq->lock, flags);

	mmc_cqe_request_करोne(mmc, hsq->mrq);

	mmc_hsq_post_request(hsq);

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_hsq_finalize_request);

अटल व्योम mmc_hsq_recovery_start(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmc_hsq *hsq = mmc->cqe_निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsq->lock, flags);

	hsq->recovery_halt = true;

	spin_unlock_irqrestore(&hsq->lock, flags);
पूर्ण

अटल व्योम mmc_hsq_recovery_finish(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmc_hsq *hsq = mmc->cqe_निजी;
	पूर्णांक reमुख्यs;

	spin_lock_irq(&hsq->lock);

	hsq->recovery_halt = false;
	reमुख्यs = hsq->qcnt;

	spin_unlock_irq(&hsq->lock);

	/*
	 * Try to pump new request अगर there are request pending in software
	 * queue after finishing recovery.
	 */
	अगर (reमुख्यs > 0)
		mmc_hsq_pump_requests(hsq);
पूर्ण

अटल पूर्णांक mmc_hsq_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_hsq *hsq = mmc->cqe_निजी;
	पूर्णांक tag = mrq->tag;

	spin_lock_irq(&hsq->lock);

	अगर (!hsq->enabled) अणु
		spin_unlock_irq(&hsq->lock);
		वापस -ESHUTDOWN;
	पूर्ण

	/* Do not queue any new requests in recovery mode. */
	अगर (hsq->recovery_halt) अणु
		spin_unlock_irq(&hsq->lock);
		वापस -EBUSY;
	पूर्ण

	hsq->slot[tag].mrq = mrq;

	/*
	 * Set the next tag as current request tag अगर no available
	 * next tag.
	 */
	अगर (hsq->next_tag == HSQ_INVALID_TAG)
		hsq->next_tag = tag;

	hsq->qcnt++;

	spin_unlock_irq(&hsq->lock);

	mmc_hsq_pump_requests(hsq);

	वापस 0;
पूर्ण

अटल व्योम mmc_hsq_post_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	अगर (mmc->ops->post_req)
		mmc->ops->post_req(mmc, mrq, 0);
पूर्ण

अटल bool mmc_hsq_queue_is_idle(काष्ठा mmc_hsq *hsq, पूर्णांक *ret)
अणु
	bool is_idle;

	spin_lock_irq(&hsq->lock);

	is_idle = (!hsq->mrq && !hsq->qcnt) ||
		hsq->recovery_halt;

	*ret = hsq->recovery_halt ? -EBUSY : 0;
	hsq->रुकोing_क्रम_idle = !is_idle;

	spin_unlock_irq(&hsq->lock);

	वापस is_idle;
पूर्ण

अटल पूर्णांक mmc_hsq_रुको_क्रम_idle(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmc_hsq *hsq = mmc->cqe_निजी;
	पूर्णांक ret;

	रुको_event(hsq->रुको_queue,
		   mmc_hsq_queue_is_idle(hsq, &ret));

	वापस ret;
पूर्ण

अटल व्योम mmc_hsq_disable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmc_hsq *hsq = mmc->cqe_निजी;
	u32 समयout = 500;
	पूर्णांक ret;

	spin_lock_irq(&hsq->lock);

	अगर (!hsq->enabled) अणु
		spin_unlock_irq(&hsq->lock);
		वापस;
	पूर्ण

	spin_unlock_irq(&hsq->lock);

	ret = रुको_event_समयout(hsq->रुको_queue,
				 mmc_hsq_queue_is_idle(hsq, &ret),
				 msecs_to_jअगरfies(समयout));
	अगर (ret == 0) अणु
		pr_warn("could not stop mmc software queue\n");
		वापस;
	पूर्ण

	spin_lock_irq(&hsq->lock);

	hsq->enabled = false;

	spin_unlock_irq(&hsq->lock);
पूर्ण

अटल पूर्णांक mmc_hsq_enable(काष्ठा mmc_host *mmc, काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_hsq *hsq = mmc->cqe_निजी;

	spin_lock_irq(&hsq->lock);

	अगर (hsq->enabled) अणु
		spin_unlock_irq(&hsq->lock);
		वापस -EBUSY;
	पूर्ण

	hsq->enabled = true;

	spin_unlock_irq(&hsq->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mmc_cqe_ops mmc_hsq_ops = अणु
	.cqe_enable = mmc_hsq_enable,
	.cqe_disable = mmc_hsq_disable,
	.cqe_request = mmc_hsq_request,
	.cqe_post_req = mmc_hsq_post_req,
	.cqe_रुको_क्रम_idle = mmc_hsq_रुको_क्रम_idle,
	.cqe_recovery_start = mmc_hsq_recovery_start,
	.cqe_recovery_finish = mmc_hsq_recovery_finish,
पूर्ण;

पूर्णांक mmc_hsq_init(काष्ठा mmc_hsq *hsq, काष्ठा mmc_host *mmc)
अणु
	hsq->num_slots = HSQ_NUM_SLOTS;
	hsq->next_tag = HSQ_INVALID_TAG;

	hsq->slot = devm_kसुस्मृति(mmc_dev(mmc), hsq->num_slots,
				 माप(काष्ठा hsq_slot), GFP_KERNEL);
	अगर (!hsq->slot)
		वापस -ENOMEM;

	hsq->mmc = mmc;
	hsq->mmc->cqe_निजी = hsq;
	mmc->cqe_ops = &mmc_hsq_ops;

	INIT_WORK(&hsq->retry_work, mmc_hsq_retry_handler);
	spin_lock_init(&hsq->lock);
	init_रुकोqueue_head(&hsq->रुको_queue);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mmc_hsq_init);

व्योम mmc_hsq_suspend(काष्ठा mmc_host *mmc)
अणु
	mmc_hsq_disable(mmc);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_hsq_suspend);

पूर्णांक mmc_hsq_resume(काष्ठा mmc_host *mmc)
अणु
	वापस mmc_hsq_enable(mmc, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(mmc_hsq_resume);

MODULE_DESCRIPTION("MMC Host Software Queue support");
MODULE_LICENSE("GPL v2");
