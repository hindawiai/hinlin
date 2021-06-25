<शैली गुरु>
/*
 * Copyright तऊ 2017 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/prime_numbers.h>

#समावेश "../i915_selftest.h"

अटल पूर्णांक __i915_sw_fence_call
fence_notअगरy(काष्ठा i915_sw_fence *fence, क्रमागत i915_sw_fence_notअगरy state)
अणु
	चयन (state) अणु
	हाल FENCE_COMPLETE:
		अवरोध;

	हाल FENCE_FREE:
		/* Leave the fence क्रम the caller to मुक्त it after testing */
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा i915_sw_fence *alloc_fence(व्योम)
अणु
	काष्ठा i915_sw_fence *fence;

	fence = kदो_स्मृति(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस शून्य;

	i915_sw_fence_init(fence, fence_notअगरy);
	वापस fence;
पूर्ण

अटल व्योम मुक्त_fence(काष्ठा i915_sw_fence *fence)
अणु
	i915_sw_fence_fini(fence);
	kमुक्त(fence);
पूर्ण

अटल पूर्णांक __test_self(काष्ठा i915_sw_fence *fence)
अणु
	अगर (i915_sw_fence_करोne(fence))
		वापस -EINVAL;

	i915_sw_fence_commit(fence);
	अगर (!i915_sw_fence_करोne(fence))
		वापस -EINVAL;

	i915_sw_fence_रुको(fence);
	अगर (!i915_sw_fence_करोne(fence))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक test_self(व्योम *arg)
अणु
	काष्ठा i915_sw_fence *fence;
	पूर्णांक ret;

	/* Test i915_sw_fence संकेतing and completion testing */
	fence = alloc_fence();
	अगर (!fence)
		वापस -ENOMEM;

	ret = __test_self(fence);

	मुक्त_fence(fence);
	वापस ret;
पूर्ण

अटल पूर्णांक test_dag(व्योम *arg)
अणु
	काष्ठा i915_sw_fence *A, *B, *C;
	पूर्णांक ret = -EINVAL;

	/* Test detection of cycles within the i915_sw_fence graphs */
	अगर (!IS_ENABLED(CONFIG_DRM_I915_SW_FENCE_CHECK_DAG))
		वापस 0;

	A = alloc_fence();
	अगर (!A)
		वापस -ENOMEM;

	अगर (i915_sw_fence_aरुको_sw_fence_gfp(A, A, GFP_KERNEL) != -EINVAL) अणु
		pr_err("recursive cycle not detected (AA)\n");
		जाओ err_A;
	पूर्ण

	B = alloc_fence();
	अगर (!B) अणु
		ret = -ENOMEM;
		जाओ err_A;
	पूर्ण

	i915_sw_fence_aरुको_sw_fence_gfp(A, B, GFP_KERNEL);
	अगर (i915_sw_fence_aरुको_sw_fence_gfp(B, A, GFP_KERNEL) != -EINVAL) अणु
		pr_err("single depth cycle not detected (BAB)\n");
		जाओ err_B;
	पूर्ण

	C = alloc_fence();
	अगर (!C) अणु
		ret = -ENOMEM;
		जाओ err_B;
	पूर्ण

	अगर (i915_sw_fence_aरुको_sw_fence_gfp(B, C, GFP_KERNEL) == -EINVAL) अणु
		pr_err("invalid cycle detected\n");
		जाओ err_C;
	पूर्ण
	अगर (i915_sw_fence_aरुको_sw_fence_gfp(C, B, GFP_KERNEL) != -EINVAL) अणु
		pr_err("single depth cycle not detected (CBC)\n");
		जाओ err_C;
	पूर्ण
	अगर (i915_sw_fence_aरुको_sw_fence_gfp(C, A, GFP_KERNEL) != -EINVAL) अणु
		pr_err("cycle not detected (BA, CB, AC)\n");
		जाओ err_C;
	पूर्ण
	अगर (i915_sw_fence_aरुको_sw_fence_gfp(A, C, GFP_KERNEL) == -EINVAL) अणु
		pr_err("invalid cycle detected\n");
		जाओ err_C;
	पूर्ण

	i915_sw_fence_commit(A);
	i915_sw_fence_commit(B);
	i915_sw_fence_commit(C);

	ret = 0;
	अगर (!i915_sw_fence_करोne(C)) अणु
		pr_err("fence C not done\n");
		ret = -EINVAL;
	पूर्ण
	अगर (!i915_sw_fence_करोne(B)) अणु
		pr_err("fence B not done\n");
		ret = -EINVAL;
	पूर्ण
	अगर (!i915_sw_fence_करोne(A)) अणु
		pr_err("fence A not done\n");
		ret = -EINVAL;
	पूर्ण
err_C:
	मुक्त_fence(C);
err_B:
	मुक्त_fence(B);
err_A:
	मुक्त_fence(A);
	वापस ret;
पूर्ण

अटल पूर्णांक test_AB(व्योम *arg)
अणु
	काष्ठा i915_sw_fence *A, *B;
	पूर्णांक ret;

	/* Test i915_sw_fence (A) रुकोing on an event source (B) */
	A = alloc_fence();
	अगर (!A)
		वापस -ENOMEM;
	B = alloc_fence();
	अगर (!B) अणु
		ret = -ENOMEM;
		जाओ err_A;
	पूर्ण

	ret = i915_sw_fence_aरुको_sw_fence_gfp(A, B, GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_B;
	अगर (ret == 0) अणु
		pr_err("Incorrectly reported fence A was complete before await\n");
		ret = -EINVAL;
		जाओ err_B;
	पूर्ण

	ret = -EINVAL;
	i915_sw_fence_commit(A);
	अगर (i915_sw_fence_करोne(A))
		जाओ err_B;

	i915_sw_fence_commit(B);
	अगर (!i915_sw_fence_करोne(B)) अणु
		pr_err("Fence B is not done\n");
		जाओ err_B;
	पूर्ण

	अगर (!i915_sw_fence_करोne(A)) अणु
		pr_err("Fence A is not done\n");
		जाओ err_B;
	पूर्ण

	ret = 0;
err_B:
	मुक्त_fence(B);
err_A:
	मुक्त_fence(A);
	वापस ret;
पूर्ण

अटल पूर्णांक test_ABC(व्योम *arg)
अणु
	काष्ठा i915_sw_fence *A, *B, *C;
	पूर्णांक ret;

	/* Test a chain of fences, A रुकोs on B who रुकोs on C */
	A = alloc_fence();
	अगर (!A)
		वापस -ENOMEM;

	B = alloc_fence();
	अगर (!B) अणु
		ret = -ENOMEM;
		जाओ err_A;
	पूर्ण

	C = alloc_fence();
	अगर (!C) अणु
		ret = -ENOMEM;
		जाओ err_B;
	पूर्ण

	ret = i915_sw_fence_aरुको_sw_fence_gfp(A, B, GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_C;
	अगर (ret == 0) अणु
		pr_err("Incorrectly reported fence B was complete before await\n");
		जाओ err_C;
	पूर्ण

	ret = i915_sw_fence_aरुको_sw_fence_gfp(B, C, GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_C;
	अगर (ret == 0) अणु
		pr_err("Incorrectly reported fence C was complete before await\n");
		जाओ err_C;
	पूर्ण

	ret = -EINVAL;
	i915_sw_fence_commit(A);
	अगर (i915_sw_fence_करोne(A)) अणु
		pr_err("Fence A completed early\n");
		जाओ err_C;
	पूर्ण

	i915_sw_fence_commit(B);
	अगर (i915_sw_fence_करोne(B)) अणु
		pr_err("Fence B completed early\n");
		जाओ err_C;
	पूर्ण

	अगर (i915_sw_fence_करोne(A)) अणु
		pr_err("Fence A completed early (after signaling B)\n");
		जाओ err_C;
	पूर्ण

	i915_sw_fence_commit(C);

	ret = 0;
	अगर (!i915_sw_fence_करोne(C)) अणु
		pr_err("Fence C not done\n");
		ret = -EINVAL;
	पूर्ण
	अगर (!i915_sw_fence_करोne(B)) अणु
		pr_err("Fence B not done\n");
		ret = -EINVAL;
	पूर्ण
	अगर (!i915_sw_fence_करोne(A)) अणु
		pr_err("Fence A not done\n");
		ret = -EINVAL;
	पूर्ण
err_C:
	मुक्त_fence(C);
err_B:
	मुक्त_fence(B);
err_A:
	मुक्त_fence(A);
	वापस ret;
पूर्ण

अटल पूर्णांक test_AB_C(व्योम *arg)
अणु
	काष्ठा i915_sw_fence *A, *B, *C;
	पूर्णांक ret = -EINVAL;

	/* Test multiple fences (AB) रुकोing on a single event (C) */
	A = alloc_fence();
	अगर (!A)
		वापस -ENOMEM;

	B = alloc_fence();
	अगर (!B) अणु
		ret = -ENOMEM;
		जाओ err_A;
	पूर्ण

	C = alloc_fence();
	अगर (!C) अणु
		ret = -ENOMEM;
		जाओ err_B;
	पूर्ण

	ret = i915_sw_fence_aरुको_sw_fence_gfp(A, C, GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_C;
	अगर (ret == 0) अणु
		ret = -EINVAL;
		जाओ err_C;
	पूर्ण

	ret = i915_sw_fence_aरुको_sw_fence_gfp(B, C, GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_C;
	अगर (ret == 0) अणु
		ret = -EINVAL;
		जाओ err_C;
	पूर्ण

	i915_sw_fence_commit(A);
	i915_sw_fence_commit(B);

	ret = 0;
	अगर (i915_sw_fence_करोne(A)) अणु
		pr_err("Fence A completed early\n");
		ret = -EINVAL;
	पूर्ण

	अगर (i915_sw_fence_करोne(B)) अणु
		pr_err("Fence B completed early\n");
		ret = -EINVAL;
	पूर्ण

	i915_sw_fence_commit(C);
	अगर (!i915_sw_fence_करोne(C)) अणु
		pr_err("Fence C not done\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!i915_sw_fence_करोne(B)) अणु
		pr_err("Fence B not done\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!i915_sw_fence_करोne(A)) अणु
		pr_err("Fence A not done\n");
		ret = -EINVAL;
	पूर्ण

err_C:
	मुक्त_fence(C);
err_B:
	मुक्त_fence(B);
err_A:
	मुक्त_fence(A);
	वापस ret;
पूर्ण

अटल पूर्णांक test_C_AB(व्योम *arg)
अणु
	काष्ठा i915_sw_fence *A, *B, *C;
	पूर्णांक ret;

	/* Test multiple event sources (A,B) क्रम a single fence (C) */
	A = alloc_fence();
	अगर (!A)
		वापस -ENOMEM;

	B = alloc_fence();
	अगर (!B) अणु
		ret = -ENOMEM;
		जाओ err_A;
	पूर्ण

	C = alloc_fence();
	अगर (!C) अणु
		ret = -ENOMEM;
		जाओ err_B;
	पूर्ण

	ret = i915_sw_fence_aरुको_sw_fence_gfp(C, A, GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_C;
	अगर (ret == 0) अणु
		ret = -EINVAL;
		जाओ err_C;
	पूर्ण

	ret = i915_sw_fence_aरुको_sw_fence_gfp(C, B, GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_C;
	अगर (ret == 0) अणु
		ret = -EINVAL;
		जाओ err_C;
	पूर्ण

	ret = 0;
	i915_sw_fence_commit(C);
	अगर (i915_sw_fence_करोne(C))
		ret = -EINVAL;

	i915_sw_fence_commit(A);
	i915_sw_fence_commit(B);

	अगर (!i915_sw_fence_करोne(A)) अणु
		pr_err("Fence A not done\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!i915_sw_fence_करोne(B)) अणु
		pr_err("Fence B not done\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!i915_sw_fence_करोne(C)) अणु
		pr_err("Fence C not done\n");
		ret = -EINVAL;
	पूर्ण

err_C:
	मुक्त_fence(C);
err_B:
	मुक्त_fence(B);
err_A:
	मुक्त_fence(A);
	वापस ret;
पूर्ण

अटल पूर्णांक test_chain(व्योम *arg)
अणु
	पूर्णांक nfences = 4096;
	काष्ठा i915_sw_fence **fences;
	पूर्णांक ret, i;

	/* Test a दीर्घ chain of fences */
	fences = kदो_स्मृति_array(nfences, माप(*fences), GFP_KERNEL);
	अगर (!fences)
		वापस -ENOMEM;

	क्रम (i = 0; i < nfences; i++) अणु
		fences[i] = alloc_fence();
		अगर (!fences[i]) अणु
			nfences = i;
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		अगर (i > 0) अणु
			ret = i915_sw_fence_aरुको_sw_fence_gfp(fences[i],
							       fences[i - 1],
							       GFP_KERNEL);
			अगर (ret < 0) अणु
				nfences = i + 1;
				जाओ err;
			पूर्ण

			i915_sw_fence_commit(fences[i]);
		पूर्ण
	पूर्ण

	ret = 0;
	क्रम (i = nfences; --i; ) अणु
		अगर (i915_sw_fence_करोne(fences[i])) अणु
			अगर (ret == 0)
				pr_err("Fence[%d] completed early\n", i);
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	i915_sw_fence_commit(fences[0]);
	क्रम (i = 0; ret == 0 && i < nfences; i++) अणु
		अगर (!i915_sw_fence_करोne(fences[i])) अणु
			pr_err("Fence[%d] is not done\n", i);
			ret = -EINVAL;
		पूर्ण
	पूर्ण

err:
	क्रम (i = 0; i < nfences; i++)
		मुक्त_fence(fences[i]);
	kमुक्त(fences);
	वापस ret;
पूर्ण

काष्ठा task_ipc अणु
	काष्ठा work_काष्ठा work;
	काष्ठा completion started;
	काष्ठा i915_sw_fence *in, *out;
	पूर्णांक value;
पूर्ण;

अटल व्योम task_ipc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा task_ipc *ipc = container_of(work, typeof(*ipc), work);

	complete(&ipc->started);

	i915_sw_fence_रुको(ipc->in);
	smp_store_mb(ipc->value, 1);
	i915_sw_fence_commit(ipc->out);
पूर्ण

अटल पूर्णांक test_ipc(व्योम *arg)
अणु
	काष्ठा task_ipc ipc;
	पूर्णांक ret = 0;

	/* Test use of i915_sw_fence as an पूर्णांकerprocess संकेतing mechanism */
	ipc.in = alloc_fence();
	अगर (!ipc.in)
		वापस -ENOMEM;
	ipc.out = alloc_fence();
	अगर (!ipc.out) अणु
		ret = -ENOMEM;
		जाओ err_in;
	पूर्ण

	/* use a completion to aव्योम chicken-and-egg testing */
	init_completion(&ipc.started);

	ipc.value = 0;
	INIT_WORK_ONSTACK(&ipc.work, task_ipc);
	schedule_work(&ipc.work);

	रुको_क्रम_completion(&ipc.started);

	usleep_range(1000, 2000);
	अगर (READ_ONCE(ipc.value)) अणु
		pr_err("worker updated value before i915_sw_fence was signaled\n");
		ret = -EINVAL;
	पूर्ण

	i915_sw_fence_commit(ipc.in);
	i915_sw_fence_रुको(ipc.out);

	अगर (!READ_ONCE(ipc.value)) अणु
		pr_err("worker signaled i915_sw_fence before value was posted\n");
		ret = -EINVAL;
	पूर्ण

	flush_work(&ipc.work);
	destroy_work_on_stack(&ipc.work);
	मुक्त_fence(ipc.out);
err_in:
	मुक्त_fence(ipc.in);
	वापस ret;
पूर्ण

अटल पूर्णांक test_समयr(व्योम *arg)
अणु
	अचिन्हित दीर्घ target, delay;
	काष्ठा समयd_fence tf;

	preempt_disable();
	समयd_fence_init(&tf, target = jअगरfies);
	अगर (!i915_sw_fence_करोne(&tf.fence)) अणु
		pr_err("Fence with immediate expiration not signaled\n");
		जाओ err;
	पूर्ण
	preempt_enable();
	समयd_fence_fini(&tf);

	क्रम_each_prime_number(delay, i915_selftest.समयout_jअगरfies/2) अणु
		preempt_disable();
		समयd_fence_init(&tf, target = jअगरfies + delay);
		अगर (i915_sw_fence_करोne(&tf.fence)) अणु
			pr_err("Fence with future expiration (%lu jiffies) already signaled\n", delay);
			जाओ err;
		पूर्ण
		preempt_enable();

		i915_sw_fence_रुको(&tf.fence);

		preempt_disable();
		अगर (!i915_sw_fence_करोne(&tf.fence)) अणु
			pr_err("Fence not signaled after wait\n");
			जाओ err;
		पूर्ण
		अगर (समय_beक्रमe(jअगरfies, target)) अणु
			pr_err("Fence signaled too early, target=%lu, now=%lu\n",
			       target, jअगरfies);
			जाओ err;
		पूर्ण
		preempt_enable();
		समयd_fence_fini(&tf);
	पूर्ण

	वापस 0;

err:
	preempt_enable();
	समयd_fence_fini(&tf);
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *mock_name(काष्ठा dma_fence *fence)
अणु
	वापस "mock";
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops mock_fence_ops = अणु
	.get_driver_name = mock_name,
	.get_समयline_name = mock_name,
पूर्ण;

अटल DEFINE_SPINLOCK(mock_fence_lock);

अटल काष्ठा dma_fence *alloc_dma_fence(व्योम)
अणु
	काष्ठा dma_fence *dma;

	dma = kदो_स्मृति(माप(*dma), GFP_KERNEL);
	अगर (dma)
		dma_fence_init(dma, &mock_fence_ops, &mock_fence_lock, 0, 0);

	वापस dma;
पूर्ण

अटल काष्ठा i915_sw_fence *
wrap_dma_fence(काष्ठा dma_fence *dma, अचिन्हित दीर्घ delay)
अणु
	काष्ठा i915_sw_fence *fence;
	पूर्णांक err;

	fence = alloc_fence();
	अगर (!fence)
		वापस ERR_PTR(-ENOMEM);

	err = i915_sw_fence_aरुको_dma_fence(fence, dma, delay, GFP_NOWAIT);
	i915_sw_fence_commit(fence);
	अगर (err < 0) अणु
		मुक्त_fence(fence);
		वापस ERR_PTR(err);
	पूर्ण

	वापस fence;
पूर्ण

अटल पूर्णांक test_dma_fence(व्योम *arg)
अणु
	काष्ठा i915_sw_fence *समयout = शून्य, *not = शून्य;
	अचिन्हित दीर्घ delay = i915_selftest.समयout_jअगरfies;
	अचिन्हित दीर्घ end, sleep;
	काष्ठा dma_fence *dma;
	पूर्णांक err;

	dma = alloc_dma_fence();
	अगर (!dma)
		वापस -ENOMEM;

	समयout = wrap_dma_fence(dma, delay);
	अगर (IS_ERR(समयout)) अणु
		err = PTR_ERR(समयout);
		जाओ err;
	पूर्ण

	not = wrap_dma_fence(dma, 0);
	अगर (IS_ERR(not)) अणु
		err = PTR_ERR(not);
		जाओ err;
	पूर्ण

	err = -EINVAL;
	अगर (i915_sw_fence_करोne(समयout) || i915_sw_fence_करोne(not)) अणु
		pr_err("Fences immediately signaled\n");
		जाओ err;
	पूर्ण

	/* We round the समयout क्रम the fence up to the next second */
	end = round_jअगरfies_up(jअगरfies + delay);

	sleep = jअगरfies_to_usecs(delay) / 3;
	usleep_range(sleep, 2 * sleep);
	अगर (समय_after(jअगरfies, end)) अणु
		pr_debug("Slept too long, delay=%lu, (target=%lu, now=%lu) skipping\n",
			 delay, end, jअगरfies);
		जाओ skip;
	पूर्ण

	अगर (i915_sw_fence_करोne(समयout) || i915_sw_fence_करोne(not)) अणु
		pr_err("Fences signaled too early\n");
		जाओ err;
	पूर्ण

	अगर (!रुको_event_समयout(समयout->रुको,
				i915_sw_fence_करोne(समयout),
				2 * (end - jअगरfies) + 1)) अणु
		pr_err("Timeout fence unsignaled!\n");
		जाओ err;
	पूर्ण

	अगर (i915_sw_fence_करोne(not)) अणु
		pr_err("No timeout fence signaled!\n");
		जाओ err;
	पूर्ण

skip:
	dma_fence_संकेत(dma);

	अगर (!i915_sw_fence_करोne(समयout) || !i915_sw_fence_करोne(not)) अणु
		pr_err("Fences unsignaled\n");
		जाओ err;
	पूर्ण

	मुक्त_fence(not);
	मुक्त_fence(समयout);
	dma_fence_put(dma);

	वापस 0;

err:
	dma_fence_संकेत(dma);
	अगर (!IS_ERR_OR_शून्य(समयout))
		मुक्त_fence(समयout);
	अगर (!IS_ERR_OR_शून्य(not))
		मुक्त_fence(not);
	dma_fence_put(dma);
	वापस err;
पूर्ण

पूर्णांक i915_sw_fence_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(test_self),
		SUBTEST(test_dag),
		SUBTEST(test_AB),
		SUBTEST(test_ABC),
		SUBTEST(test_AB_C),
		SUBTEST(test_C_AB),
		SUBTEST(test_chain),
		SUBTEST(test_ipc),
		SUBTEST(test_समयr),
		SUBTEST(test_dma_fence),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण
