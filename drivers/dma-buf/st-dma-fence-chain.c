<शैली गुरु>
// SPDX-License-Identअगरier: MIT

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/dma-fence-chain.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अक्रमom.h>

#समावेश "selftest.h"

#घोषणा CHAIN_SZ (4 << 10)

अटल काष्ठा kmem_cache *slab_fences;

अटल अंतरभूत काष्ठा mock_fence अणु
	काष्ठा dma_fence base;
	spinlock_t lock;
पूर्ण *to_mock_fence(काष्ठा dma_fence *f) अणु
	वापस container_of(f, काष्ठा mock_fence, base);
पूर्ण

अटल स्थिर अक्षर *mock_name(काष्ठा dma_fence *f)
अणु
	वापस "mock";
पूर्ण

अटल व्योम mock_fence_release(काष्ठा dma_fence *f)
अणु
	kmem_cache_मुक्त(slab_fences, to_mock_fence(f));
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops mock_ops = अणु
	.get_driver_name = mock_name,
	.get_समयline_name = mock_name,
	.release = mock_fence_release,
पूर्ण;

अटल काष्ठा dma_fence *mock_fence(व्योम)
अणु
	काष्ठा mock_fence *f;

	f = kmem_cache_alloc(slab_fences, GFP_KERNEL);
	अगर (!f)
		वापस शून्य;

	spin_lock_init(&f->lock);
	dma_fence_init(&f->base, &mock_ops, &f->lock, 0, 0);

	वापस &f->base;
पूर्ण

अटल अंतरभूत काष्ठा mock_chain अणु
	काष्ठा dma_fence_chain base;
पूर्ण *to_mock_chain(काष्ठा dma_fence *f) अणु
	वापस container_of(f, काष्ठा mock_chain, base.base);
पूर्ण

अटल काष्ठा dma_fence *mock_chain(काष्ठा dma_fence *prev,
				    काष्ठा dma_fence *fence,
				    u64 seqno)
अणु
	काष्ठा mock_chain *f;

	f = kदो_स्मृति(माप(*f), GFP_KERNEL);
	अगर (!f)
		वापस शून्य;

	dma_fence_chain_init(&f->base,
			     dma_fence_get(prev),
			     dma_fence_get(fence),
			     seqno);

	वापस &f->base.base;
पूर्ण

अटल पूर्णांक sanitycheck(व्योम *arg)
अणु
	काष्ठा dma_fence *f, *chain;
	पूर्णांक err = 0;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	chain = mock_chain(शून्य, f, 1);
	अगर (!chain)
		err = -ENOMEM;

	dma_fence_संकेत(f);
	dma_fence_put(f);

	dma_fence_put(chain);

	वापस err;
पूर्ण

काष्ठा fence_chains अणु
	अचिन्हित पूर्णांक chain_length;
	काष्ठा dma_fence **fences;
	काष्ठा dma_fence **chains;

	काष्ठा dma_fence *tail;
पूर्ण;

अटल uपूर्णांक64_t seqno_inc(अचिन्हित पूर्णांक i)
अणु
	वापस i + 1;
पूर्ण

अटल पूर्णांक fence_chains_init(काष्ठा fence_chains *fc, अचिन्हित पूर्णांक count,
			     uपूर्णांक64_t (*seqno_fn)(अचिन्हित पूर्णांक))
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	fc->chains = kvदो_स्मृति_array(count, माप(*fc->chains),
				    GFP_KERNEL | __GFP_ZERO);
	अगर (!fc->chains)
		वापस -ENOMEM;

	fc->fences = kvदो_स्मृति_array(count, माप(*fc->fences),
				    GFP_KERNEL | __GFP_ZERO);
	अगर (!fc->fences) अणु
		err = -ENOMEM;
		जाओ err_chains;
	पूर्ण

	fc->tail = शून्य;
	क्रम (i = 0; i < count; i++) अणु
		fc->fences[i] = mock_fence();
		अगर (!fc->fences[i]) अणु
			err = -ENOMEM;
			जाओ unwind;
		पूर्ण

		fc->chains[i] = mock_chain(fc->tail,
					   fc->fences[i],
					   seqno_fn(i));
		अगर (!fc->chains[i]) अणु
			err = -ENOMEM;
			जाओ unwind;
		पूर्ण

		fc->tail = fc->chains[i];
	पूर्ण

	fc->chain_length = i;
	वापस 0;

unwind:
	क्रम (i = 0; i < count; i++) अणु
		dma_fence_put(fc->fences[i]);
		dma_fence_put(fc->chains[i]);
	पूर्ण
	kvमुक्त(fc->fences);
err_chains:
	kvमुक्त(fc->chains);
	वापस err;
पूर्ण

अटल व्योम fence_chains_fini(काष्ठा fence_chains *fc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < fc->chain_length; i++) अणु
		dma_fence_संकेत(fc->fences[i]);
		dma_fence_put(fc->fences[i]);
	पूर्ण
	kvमुक्त(fc->fences);

	क्रम (i = 0; i < fc->chain_length; i++)
		dma_fence_put(fc->chains[i]);
	kvमुक्त(fc->chains);
पूर्ण

अटल पूर्णांक find_seqno(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	काष्ठा dma_fence *fence;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&fc, 64, seqno_inc);
	अगर (err)
		वापस err;

	fence = dma_fence_get(fc.tail);
	err = dma_fence_chain_find_seqno(&fence, 0);
	dma_fence_put(fence);
	अगर (err) अणु
		pr_err("Reported %d for find_seqno(0)!\n", err);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < fc.chain_length; i++) अणु
		fence = dma_fence_get(fc.tail);
		err = dma_fence_chain_find_seqno(&fence, i + 1);
		dma_fence_put(fence);
		अगर (err) अणु
			pr_err("Reported %d for find_seqno(%d:%d)!\n",
			       err, fc.chain_length + 1, i + 1);
			जाओ err;
		पूर्ण
		अगर (fence != fc.chains[i]) अणु
			pr_err("Incorrect fence reported by find_seqno(%d:%d)\n",
			       fc.chain_length + 1, i + 1);
			err = -EINVAL;
			जाओ err;
		पूर्ण

		dma_fence_get(fence);
		err = dma_fence_chain_find_seqno(&fence, i + 1);
		dma_fence_put(fence);
		अगर (err) अणु
			pr_err("Error reported for finding self\n");
			जाओ err;
		पूर्ण
		अगर (fence != fc.chains[i]) अणु
			pr_err("Incorrect fence reported by find self\n");
			err = -EINVAL;
			जाओ err;
		पूर्ण

		dma_fence_get(fence);
		err = dma_fence_chain_find_seqno(&fence, i + 2);
		dma_fence_put(fence);
		अगर (!err) अणु
			pr_err("Error not reported for future fence: find_seqno(%d:%d)!\n",
			       i + 1, i + 2);
			err = -EINVAL;
			जाओ err;
		पूर्ण

		dma_fence_get(fence);
		err = dma_fence_chain_find_seqno(&fence, i);
		dma_fence_put(fence);
		अगर (err) अणु
			pr_err("Error reported for previous fence!\n");
			जाओ err;
		पूर्ण
		अगर (i > 0 && fence != fc.chains[i - 1]) अणु
			pr_err("Incorrect fence reported by find_seqno(%d:%d)\n",
			       i + 1, i);
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

अटल पूर्णांक find_संकेतed(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	काष्ठा dma_fence *fence;
	पूर्णांक err;

	err = fence_chains_init(&fc, 2, seqno_inc);
	अगर (err)
		वापस err;

	dma_fence_संकेत(fc.fences[0]);

	fence = dma_fence_get(fc.tail);
	err = dma_fence_chain_find_seqno(&fence, 1);
	dma_fence_put(fence);
	अगर (err) अणु
		pr_err("Reported %d for find_seqno()!\n", err);
		जाओ err;
	पूर्ण

	अगर (fence && fence != fc.chains[0]) अणु
		pr_err("Incorrect chain-fence.seqno:%lld reported for completed seqno:1\n",
		       fence->seqno);

		dma_fence_get(fence);
		err = dma_fence_chain_find_seqno(&fence, 1);
		dma_fence_put(fence);
		अगर (err)
			pr_err("Reported %d for finding self!\n", err);

		err = -EINVAL;
	पूर्ण

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

अटल पूर्णांक find_out_of_order(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	काष्ठा dma_fence *fence;
	पूर्णांक err;

	err = fence_chains_init(&fc, 3, seqno_inc);
	अगर (err)
		वापस err;

	dma_fence_संकेत(fc.fences[1]);

	fence = dma_fence_get(fc.tail);
	err = dma_fence_chain_find_seqno(&fence, 2);
	dma_fence_put(fence);
	अगर (err) अणु
		pr_err("Reported %d for find_seqno()!\n", err);
		जाओ err;
	पूर्ण

	/*
	 * We संकेतed the middle fence (2) of the 1-2-3 chain. The behavior
	 * of the dma-fence-chain is to make us रुको क्रम all the fences up to
	 * the poपूर्णांक we want. Since fence 1 is still not संकेतed, this what
	 * we should get as fence to रुको upon (fence 2 being garbage
	 * collected during the traversal of the chain).
	 */
	अगर (fence != fc.chains[0]) अणु
		pr_err("Incorrect chain-fence.seqno:%lld reported for completed seqno:2\n",
		       fence ? fence->seqno : 0);

		err = -EINVAL;
	पूर्ण

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

अटल uपूर्णांक64_t seqno_inc2(अचिन्हित पूर्णांक i)
अणु
	वापस 2 * i + 2;
पूर्ण

अटल पूर्णांक find_gap(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	काष्ठा dma_fence *fence;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&fc, 64, seqno_inc2);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < fc.chain_length; i++) अणु
		fence = dma_fence_get(fc.tail);
		err = dma_fence_chain_find_seqno(&fence, 2 * i + 1);
		dma_fence_put(fence);
		अगर (err) अणु
			pr_err("Reported %d for find_seqno(%d:%d)!\n",
			       err, fc.chain_length + 1, 2 * i + 1);
			जाओ err;
		पूर्ण
		अगर (fence != fc.chains[i]) अणु
			pr_err("Incorrect fence.seqno:%lld reported by find_seqno(%d:%d)\n",
			       fence->seqno,
			       fc.chain_length + 1,
			       2 * i + 1);
			err = -EINVAL;
			जाओ err;
		पूर्ण

		dma_fence_get(fence);
		err = dma_fence_chain_find_seqno(&fence, 2 * i + 2);
		dma_fence_put(fence);
		अगर (err) अणु
			pr_err("Error reported for finding self\n");
			जाओ err;
		पूर्ण
		अगर (fence != fc.chains[i]) अणु
			pr_err("Incorrect fence reported by find self\n");
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

काष्ठा find_race अणु
	काष्ठा fence_chains fc;
	atomic_t children;
पूर्ण;

अटल पूर्णांक __find_race(व्योम *arg)
अणु
	काष्ठा find_race *data = arg;
	पूर्णांक err = 0;

	जबतक (!kthपढ़ो_should_stop()) अणु
		काष्ठा dma_fence *fence = dma_fence_get(data->fc.tail);
		पूर्णांक seqno;

		seqno = pअक्रमom_u32_max(data->fc.chain_length) + 1;

		err = dma_fence_chain_find_seqno(&fence, seqno);
		अगर (err) अणु
			pr_err("Failed to find fence seqno:%d\n",
			       seqno);
			dma_fence_put(fence);
			अवरोध;
		पूर्ण
		अगर (!fence)
			जाओ संकेत;

		/*
		 * We can only find ourselves अगर we are on fence we were
		 * looking क्रम.
		 */
		अगर (fence->seqno == seqno) अणु
			err = dma_fence_chain_find_seqno(&fence, seqno);
			अगर (err) अणु
				pr_err("Reported an invalid fence for find-self:%d\n",
				       seqno);
				dma_fence_put(fence);
				अवरोध;
			पूर्ण
		पूर्ण

		dma_fence_put(fence);

संकेत:
		seqno = pअक्रमom_u32_max(data->fc.chain_length - 1);
		dma_fence_संकेत(data->fc.fences[seqno]);
		cond_resched();
	पूर्ण

	अगर (atomic_dec_and_test(&data->children))
		wake_up_var(&data->children);
	वापस err;
पूर्ण

अटल पूर्णांक find_race(व्योम *arg)
अणु
	काष्ठा find_race data;
	पूर्णांक ncpus = num_online_cpus();
	काष्ठा task_काष्ठा **thपढ़ोs;
	अचिन्हित दीर्घ count;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&data.fc, CHAIN_SZ, seqno_inc);
	अगर (err)
		वापस err;

	thपढ़ोs = kदो_स्मृति_array(ncpus, माप(*thपढ़ोs), GFP_KERNEL);
	अगर (!thपढ़ोs) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	atomic_set(&data.children, 0);
	क्रम (i = 0; i < ncpus; i++) अणु
		thपढ़ोs[i] = kthपढ़ो_run(__find_race, &data, "dmabuf/%d", i);
		अगर (IS_ERR(thपढ़ोs[i])) अणु
			ncpus = i;
			अवरोध;
		पूर्ण
		atomic_inc(&data.children);
		get_task_काष्ठा(thपढ़ोs[i]);
	पूर्ण

	रुको_var_event_समयout(&data.children,
			       !atomic_पढ़ो(&data.children),
			       5 * HZ);

	क्रम (i = 0; i < ncpus; i++) अणु
		पूर्णांक ret;

		ret = kthपढ़ो_stop(thपढ़ोs[i]);
		अगर (ret && !err)
			err = ret;
		put_task_काष्ठा(thपढ़ोs[i]);
	पूर्ण
	kमुक्त(thपढ़ोs);

	count = 0;
	क्रम (i = 0; i < data.fc.chain_length; i++)
		अगर (dma_fence_is_संकेतed(data.fc.fences[i]))
			count++;
	pr_info("Completed %lu cycles\n", count);

err:
	fence_chains_fini(&data.fc);
	वापस err;
पूर्ण

अटल पूर्णांक संकेत_क्रमward(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&fc, 64, seqno_inc);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < fc.chain_length; i++) अणु
		dma_fence_संकेत(fc.fences[i]);

		अगर (!dma_fence_is_संकेतed(fc.chains[i])) अणु
			pr_err("chain[%d] not signaled!\n", i);
			err = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (i + 1 < fc.chain_length &&
		    dma_fence_is_संकेतed(fc.chains[i + 1])) अणु
			pr_err("chain[%d] is signaled!\n", i);
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

अटल पूर्णांक संकेत_backward(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&fc, 64, seqno_inc);
	अगर (err)
		वापस err;

	क्रम (i = fc.chain_length; i--; ) अणु
		dma_fence_संकेत(fc.fences[i]);

		अगर (i > 0 && dma_fence_is_संकेतed(fc.chains[i])) अणु
			pr_err("chain[%d] is signaled!\n", i);
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < fc.chain_length; i++) अणु
		अगर (!dma_fence_is_संकेतed(fc.chains[i])) अणु
			pr_err("chain[%d] was not signaled!\n", i);
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

अटल पूर्णांक __रुको_fence_chains(व्योम *arg)
अणु
	काष्ठा fence_chains *fc = arg;

	अगर (dma_fence_रुको(fc->tail, false))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_क्रमward(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&fc, CHAIN_SZ, seqno_inc);
	अगर (err)
		वापस err;

	tsk = kthपढ़ो_run(__रुको_fence_chains, &fc, "dmabuf/wait");
	अगर (IS_ERR(tsk)) अणु
		err = PTR_ERR(tsk);
		जाओ err;
	पूर्ण
	get_task_काष्ठा(tsk);
	yield_to(tsk, true);

	क्रम (i = 0; i < fc.chain_length; i++)
		dma_fence_संकेत(fc.fences[i]);

	err = kthपढ़ो_stop(tsk);
	put_task_काष्ठा(tsk);

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

अटल पूर्णांक रुको_backward(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&fc, CHAIN_SZ, seqno_inc);
	अगर (err)
		वापस err;

	tsk = kthपढ़ो_run(__रुको_fence_chains, &fc, "dmabuf/wait");
	अगर (IS_ERR(tsk)) अणु
		err = PTR_ERR(tsk);
		जाओ err;
	पूर्ण
	get_task_काष्ठा(tsk);
	yield_to(tsk, true);

	क्रम (i = fc.chain_length; i--; )
		dma_fence_संकेत(fc.fences[i]);

	err = kthपढ़ो_stop(tsk);
	put_task_काष्ठा(tsk);

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

अटल व्योम अक्रमomise_fences(काष्ठा fence_chains *fc)
अणु
	अचिन्हित पूर्णांक count = fc->chain_length;

	/* Fisher-Yates shuffle courtesy of Knuth */
	जबतक (--count) अणु
		अचिन्हित पूर्णांक swp;

		swp = pअक्रमom_u32_max(count + 1);
		अगर (swp == count)
			जारी;

		swap(fc->fences[count], fc->fences[swp]);
	पूर्ण
पूर्ण

अटल पूर्णांक रुको_अक्रमom(व्योम *arg)
अणु
	काष्ठा fence_chains fc;
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक err;
	पूर्णांक i;

	err = fence_chains_init(&fc, CHAIN_SZ, seqno_inc);
	अगर (err)
		वापस err;

	अक्रमomise_fences(&fc);

	tsk = kthपढ़ो_run(__रुको_fence_chains, &fc, "dmabuf/wait");
	अगर (IS_ERR(tsk)) अणु
		err = PTR_ERR(tsk);
		जाओ err;
	पूर्ण
	get_task_काष्ठा(tsk);
	yield_to(tsk, true);

	क्रम (i = 0; i < fc.chain_length; i++)
		dma_fence_संकेत(fc.fences[i]);

	err = kthपढ़ो_stop(tsk);
	put_task_काष्ठा(tsk);

err:
	fence_chains_fini(&fc);
	वापस err;
पूर्ण

पूर्णांक dma_fence_chain(व्योम)
अणु
	अटल स्थिर काष्ठा subtest tests[] = अणु
		SUBTEST(sanitycheck),
		SUBTEST(find_seqno),
		SUBTEST(find_संकेतed),
		SUBTEST(find_out_of_order),
		SUBTEST(find_gap),
		SUBTEST(find_race),
		SUBTEST(संकेत_क्रमward),
		SUBTEST(संकेत_backward),
		SUBTEST(रुको_क्रमward),
		SUBTEST(रुको_backward),
		SUBTEST(रुको_अक्रमom),
	पूर्ण;
	पूर्णांक ret;

	pr_info("sizeof(dma_fence_chain)=%zu\n",
		माप(काष्ठा dma_fence_chain));

	slab_fences = KMEM_CACHE(mock_fence,
				 SLAB_TYPESAFE_BY_RCU |
				 SLAB_HWCACHE_ALIGN);
	अगर (!slab_fences)
		वापस -ENOMEM;

	ret = subtests(tests, शून्य);

	kmem_cache_destroy(slab_fences);
	वापस ret;
पूर्ण
