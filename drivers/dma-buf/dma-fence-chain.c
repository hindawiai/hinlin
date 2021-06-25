<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fence-chain: chain fences together in a समयline
 *
 * Copyright (C) 2018 Advanced Micro Devices, Inc.
 * Authors:
 *	Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/dma-fence-chain.h>

अटल bool dma_fence_chain_enable_संकेतing(काष्ठा dma_fence *fence);

/**
 * dma_fence_chain_get_prev - use RCU to get a reference to the previous fence
 * @chain: chain node to get the previous node from
 *
 * Use dma_fence_get_rcu_safe to get a reference to the previous fence of the
 * chain node.
 */
अटल काष्ठा dma_fence *dma_fence_chain_get_prev(काष्ठा dma_fence_chain *chain)
अणु
	काष्ठा dma_fence *prev;

	rcu_पढ़ो_lock();
	prev = dma_fence_get_rcu_safe(&chain->prev);
	rcu_पढ़ो_unlock();
	वापस prev;
पूर्ण

/**
 * dma_fence_chain_walk - chain walking function
 * @fence: current chain node
 *
 * Walk the chain to the next node. Returns the next fence or शून्य अगर we are at
 * the end of the chain. Garbage collects chain nodes which are alपढ़ोy
 * संकेतed.
 */
काष्ठा dma_fence *dma_fence_chain_walk(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_chain *chain, *prev_chain;
	काष्ठा dma_fence *prev, *replacement, *पंचांगp;

	chain = to_dma_fence_chain(fence);
	अगर (!chain) अणु
		dma_fence_put(fence);
		वापस शून्य;
	पूर्ण

	जबतक ((prev = dma_fence_chain_get_prev(chain))) अणु

		prev_chain = to_dma_fence_chain(prev);
		अगर (prev_chain) अणु
			अगर (!dma_fence_is_संकेतed(prev_chain->fence))
				अवरोध;

			replacement = dma_fence_chain_get_prev(prev_chain);
		पूर्ण अन्यथा अणु
			अगर (!dma_fence_is_संकेतed(prev))
				अवरोध;

			replacement = शून्य;
		पूर्ण

		पंचांगp = cmpxchg((काष्ठा dma_fence __क्रमce **)&chain->prev,
			      prev, replacement);
		अगर (पंचांगp == prev)
			dma_fence_put(पंचांगp);
		अन्यथा
			dma_fence_put(replacement);
		dma_fence_put(prev);
	पूर्ण

	dma_fence_put(fence);
	वापस prev;
पूर्ण
EXPORT_SYMBOL(dma_fence_chain_walk);

/**
 * dma_fence_chain_find_seqno - find fence chain node by seqno
 * @pfence: poपूर्णांकer to the chain node where to start
 * @seqno: the sequence number to search क्रम
 *
 * Advance the fence poपूर्णांकer to the chain node which will संकेत this sequence
 * number. If no sequence number is provided then this is a no-op.
 *
 * Returns EINVAL अगर the fence is not a chain node or the sequence number has
 * not yet advanced far enough.
 */
पूर्णांक dma_fence_chain_find_seqno(काष्ठा dma_fence **pfence, uपूर्णांक64_t seqno)
अणु
	काष्ठा dma_fence_chain *chain;

	अगर (!seqno)
		वापस 0;

	chain = to_dma_fence_chain(*pfence);
	अगर (!chain || chain->base.seqno < seqno)
		वापस -EINVAL;

	dma_fence_chain_क्रम_each(*pfence, &chain->base) अणु
		अगर ((*pfence)->context != chain->base.context ||
		    to_dma_fence_chain(*pfence)->prev_seqno < seqno)
			अवरोध;
	पूर्ण
	dma_fence_put(&chain->base);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dma_fence_chain_find_seqno);

अटल स्थिर अक्षर *dma_fence_chain_get_driver_name(काष्ठा dma_fence *fence)
अणु
        वापस "dma_fence_chain";
पूर्ण

अटल स्थिर अक्षर *dma_fence_chain_get_समयline_name(काष्ठा dma_fence *fence)
अणु
        वापस "unbound";
पूर्ण

अटल व्योम dma_fence_chain_irq_work(काष्ठा irq_work *work)
अणु
	काष्ठा dma_fence_chain *chain;

	chain = container_of(work, typeof(*chain), work);

	/* Try to rearm the callback */
	अगर (!dma_fence_chain_enable_संकेतing(&chain->base))
		/* Ok, we are करोne. No more unसंकेतed fences left */
		dma_fence_संकेत(&chain->base);
	dma_fence_put(&chain->base);
पूर्ण

अटल व्योम dma_fence_chain_cb(काष्ठा dma_fence *f, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा dma_fence_chain *chain;

	chain = container_of(cb, typeof(*chain), cb);
	irq_work_queue(&chain->work);
	dma_fence_put(f);
पूर्ण

अटल bool dma_fence_chain_enable_संकेतing(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_chain *head = to_dma_fence_chain(fence);

	dma_fence_get(&head->base);
	dma_fence_chain_क्रम_each(fence, &head->base) अणु
		काष्ठा dma_fence_chain *chain = to_dma_fence_chain(fence);
		काष्ठा dma_fence *f = chain ? chain->fence : fence;

		dma_fence_get(f);
		अगर (!dma_fence_add_callback(f, &head->cb, dma_fence_chain_cb)) अणु
			dma_fence_put(fence);
			वापस true;
		पूर्ण
		dma_fence_put(f);
	पूर्ण
	dma_fence_put(&head->base);
	वापस false;
पूर्ण

अटल bool dma_fence_chain_संकेतed(काष्ठा dma_fence *fence)
अणु
	dma_fence_chain_क्रम_each(fence, fence) अणु
		काष्ठा dma_fence_chain *chain = to_dma_fence_chain(fence);
		काष्ठा dma_fence *f = chain ? chain->fence : fence;

		अगर (!dma_fence_is_संकेतed(f)) अणु
			dma_fence_put(fence);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम dma_fence_chain_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_chain *chain = to_dma_fence_chain(fence);
	काष्ठा dma_fence *prev;

	/* Manually unlink the chain as much as possible to aव्योम recursion
	 * and potential stack overflow.
	 */
	जबतक ((prev = rcu_dereference_रक्षित(chain->prev, true))) अणु
		काष्ठा dma_fence_chain *prev_chain;

		अगर (kref_पढ़ो(&prev->refcount) > 1)
		       अवरोध;

		prev_chain = to_dma_fence_chain(prev);
		अगर (!prev_chain)
			अवरोध;

		/* No need क्रम atomic operations since we hold the last
		 * reference to prev_chain.
		 */
		chain->prev = prev_chain->prev;
		RCU_INIT_POINTER(prev_chain->prev, शून्य);
		dma_fence_put(prev);
	पूर्ण
	dma_fence_put(prev);

	dma_fence_put(chain->fence);
	dma_fence_मुक्त(fence);
पूर्ण

स्थिर काष्ठा dma_fence_ops dma_fence_chain_ops = अणु
	.use_64bit_seqno = true,
	.get_driver_name = dma_fence_chain_get_driver_name,
	.get_समयline_name = dma_fence_chain_get_समयline_name,
	.enable_संकेतing = dma_fence_chain_enable_संकेतing,
	.संकेतed = dma_fence_chain_संकेतed,
	.release = dma_fence_chain_release,
पूर्ण;
EXPORT_SYMBOL(dma_fence_chain_ops);

/**
 * dma_fence_chain_init - initialize a fence chain
 * @chain: the chain node to initialize
 * @prev: the previous fence
 * @fence: the current fence
 * @seqno: the sequence number to use क्रम the fence chain
 *
 * Initialize a new chain node and either start a new chain or add the node to
 * the existing chain of the previous fence.
 */
व्योम dma_fence_chain_init(काष्ठा dma_fence_chain *chain,
			  काष्ठा dma_fence *prev,
			  काष्ठा dma_fence *fence,
			  uपूर्णांक64_t seqno)
अणु
	काष्ठा dma_fence_chain *prev_chain = to_dma_fence_chain(prev);
	uपूर्णांक64_t context;

	spin_lock_init(&chain->lock);
	rcu_assign_poपूर्णांकer(chain->prev, prev);
	chain->fence = fence;
	chain->prev_seqno = 0;
	init_irq_work(&chain->work, dma_fence_chain_irq_work);

	/* Try to reuse the context of the previous chain node. */
	अगर (prev_chain && __dma_fence_is_later(seqno, prev->seqno, prev->ops)) अणु
		context = prev->context;
		chain->prev_seqno = prev->seqno;
	पूर्ण अन्यथा अणु
		context = dma_fence_context_alloc(1);
		/* Make sure that we always have a valid sequence number. */
		अगर (prev_chain)
			seqno = max(prev->seqno, seqno);
	पूर्ण

	dma_fence_init(&chain->base, &dma_fence_chain_ops,
		       &chain->lock, context, seqno);
पूर्ण
EXPORT_SYMBOL(dma_fence_chain_init);
