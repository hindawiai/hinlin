<शैली गुरु>
/*
 * Copyright (C) 2007 Ben Skeggs.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/kसमय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <trace/events/dma_fence.h>

#समावेश <nvअगर/cl826e.h>
#समावेश <nvअगर/notअगरy.h>
#समावेश <nvअगर/event.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_fence.h"

अटल स्थिर काष्ठा dma_fence_ops nouveau_fence_ops_uevent;
अटल स्थिर काष्ठा dma_fence_ops nouveau_fence_ops_legacy;

अटल अंतरभूत काष्ठा nouveau_fence *
from_fence(काष्ठा dma_fence *fence)
अणु
	वापस container_of(fence, काष्ठा nouveau_fence, base);
पूर्ण

अटल अंतरभूत काष्ठा nouveau_fence_chan *
nouveau_fctx(काष्ठा nouveau_fence *fence)
अणु
	वापस container_of(fence->base.lock, काष्ठा nouveau_fence_chan, lock);
पूर्ण

अटल पूर्णांक
nouveau_fence_संकेत(काष्ठा nouveau_fence *fence)
अणु
	पूर्णांक drop = 0;

	dma_fence_संकेत_locked(&fence->base);
	list_del(&fence->head);
	rcu_assign_poपूर्णांकer(fence->channel, शून्य);

	अगर (test_bit(DMA_FENCE_FLAG_USER_BITS, &fence->base.flags)) अणु
		काष्ठा nouveau_fence_chan *fctx = nouveau_fctx(fence);

		अगर (!--fctx->notअगरy_ref)
			drop = 1;
	पूर्ण

	dma_fence_put(&fence->base);
	वापस drop;
पूर्ण

अटल काष्ठा nouveau_fence *
nouveau_local_fence(काष्ठा dma_fence *fence, काष्ठा nouveau_drm *drm)
अणु
	अगर (fence->ops != &nouveau_fence_ops_legacy &&
	    fence->ops != &nouveau_fence_ops_uevent)
		वापस शून्य;

	अगर (fence->context < drm->chan.context_base ||
	    fence->context >= drm->chan.context_base + drm->chan.nr)
		वापस शून्य;

	वापस from_fence(fence);
पूर्ण

व्योम
nouveau_fence_context_समाप्त(काष्ठा nouveau_fence_chan *fctx, पूर्णांक error)
अणु
	काष्ठा nouveau_fence *fence;

	spin_lock_irq(&fctx->lock);
	जबतक (!list_empty(&fctx->pending)) अणु
		fence = list_entry(fctx->pending.next, typeof(*fence), head);

		अगर (error)
			dma_fence_set_error(&fence->base, error);

		अगर (nouveau_fence_संकेत(fence))
			nvअगर_notअगरy_put(&fctx->notअगरy);
	पूर्ण
	spin_unlock_irq(&fctx->lock);
पूर्ण

व्योम
nouveau_fence_context_del(काष्ठा nouveau_fence_chan *fctx)
अणु
	nouveau_fence_context_समाप्त(fctx, 0);
	nvअगर_notअगरy_dtor(&fctx->notअगरy);
	fctx->dead = 1;

	/*
	 * Ensure that all accesses to fence->channel complete beक्रमe मुक्तing
	 * the channel.
	 */
	synchronize_rcu();
पूर्ण

अटल व्योम
nouveau_fence_context_put(काष्ठा kref *fence_ref)
अणु
	kमुक्त(container_of(fence_ref, काष्ठा nouveau_fence_chan, fence_ref));
पूर्ण

व्योम
nouveau_fence_context_मुक्त(काष्ठा nouveau_fence_chan *fctx)
अणु
	kref_put(&fctx->fence_ref, nouveau_fence_context_put);
पूर्ण

अटल पूर्णांक
nouveau_fence_update(काष्ठा nouveau_channel *chan, काष्ठा nouveau_fence_chan *fctx)
अणु
	काष्ठा nouveau_fence *fence;
	पूर्णांक drop = 0;
	u32 seq = fctx->पढ़ो(chan);

	जबतक (!list_empty(&fctx->pending)) अणु
		fence = list_entry(fctx->pending.next, typeof(*fence), head);

		अगर ((पूर्णांक)(seq - fence->base.seqno) < 0)
			अवरोध;

		drop |= nouveau_fence_संकेत(fence);
	पूर्ण

	वापस drop;
पूर्ण

अटल पूर्णांक
nouveau_fence_रुको_uevent_handler(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nouveau_fence_chan *fctx =
		container_of(notअगरy, typeof(*fctx), notअगरy);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = NVIF_NOTIFY_KEEP;

	spin_lock_irqsave(&fctx->lock, flags);
	अगर (!list_empty(&fctx->pending)) अणु
		काष्ठा nouveau_fence *fence;
		काष्ठा nouveau_channel *chan;

		fence = list_entry(fctx->pending.next, typeof(*fence), head);
		chan = rcu_dereference_रक्षित(fence->channel, lockdep_is_held(&fctx->lock));
		अगर (nouveau_fence_update(chan, fctx))
			ret = NVIF_NOTIFY_DROP;
	पूर्ण
	spin_unlock_irqrestore(&fctx->lock, flags);

	वापस ret;
पूर्ण

व्योम
nouveau_fence_context_new(काष्ठा nouveau_channel *chan, काष्ठा nouveau_fence_chan *fctx)
अणु
	काष्ठा nouveau_fence_priv *priv = (व्योम*)chan->drm->fence;
	काष्ठा nouveau_cli *cli = (व्योम *)chan->user.client;
	पूर्णांक ret;

	INIT_LIST_HEAD(&fctx->flip);
	INIT_LIST_HEAD(&fctx->pending);
	spin_lock_init(&fctx->lock);
	fctx->context = chan->drm->chan.context_base + chan->chid;

	अगर (chan == chan->drm->cechan)
		म_नकल(fctx->name, "copy engine channel");
	अन्यथा अगर (chan == chan->drm->channel)
		म_नकल(fctx->name, "generic kernel channel");
	अन्यथा
		म_नकल(fctx->name, nvxx_client(&cli->base)->name);

	kref_init(&fctx->fence_ref);
	अगर (!priv->uevent)
		वापस;

	ret = nvअगर_notअगरy_ctor(&chan->user, "fenceNonStallIntr",
			       nouveau_fence_रुको_uevent_handler,
			       false, NV826E_V0_NTFY_NON_STALL_INTERRUPT,
			       &(काष्ठा nvअगर_notअगरy_uevent_req) अणु पूर्ण,
			       माप(काष्ठा nvअगर_notअगरy_uevent_req),
			       माप(काष्ठा nvअगर_notअगरy_uevent_rep),
			       &fctx->notअगरy);

	WARN_ON(ret);
पूर्ण

पूर्णांक
nouveau_fence_emit(काष्ठा nouveau_fence *fence, काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nouveau_fence_chan *fctx = chan->fence;
	काष्ठा nouveau_fence_priv *priv = (व्योम*)chan->drm->fence;
	पूर्णांक ret;

	fence->channel  = chan;
	fence->समयout  = jअगरfies + (15 * HZ);

	अगर (priv->uevent)
		dma_fence_init(&fence->base, &nouveau_fence_ops_uevent,
			       &fctx->lock, fctx->context, ++fctx->sequence);
	अन्यथा
		dma_fence_init(&fence->base, &nouveau_fence_ops_legacy,
			       &fctx->lock, fctx->context, ++fctx->sequence);
	kref_get(&fctx->fence_ref);

	trace_dma_fence_emit(&fence->base);
	ret = fctx->emit(fence);
	अगर (!ret) अणु
		dma_fence_get(&fence->base);
		spin_lock_irq(&fctx->lock);

		अगर (nouveau_fence_update(chan, fctx))
			nvअगर_notअगरy_put(&fctx->notअगरy);

		list_add_tail(&fence->head, &fctx->pending);
		spin_unlock_irq(&fctx->lock);
	पूर्ण

	वापस ret;
पूर्ण

bool
nouveau_fence_करोne(काष्ठा nouveau_fence *fence)
अणु
	अगर (fence->base.ops == &nouveau_fence_ops_legacy ||
	    fence->base.ops == &nouveau_fence_ops_uevent) अणु
		काष्ठा nouveau_fence_chan *fctx = nouveau_fctx(fence);
		काष्ठा nouveau_channel *chan;
		अचिन्हित दीर्घ flags;

		अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->base.flags))
			वापस true;

		spin_lock_irqsave(&fctx->lock, flags);
		chan = rcu_dereference_रक्षित(fence->channel, lockdep_is_held(&fctx->lock));
		अगर (chan && nouveau_fence_update(chan, fctx))
			nvअगर_notअगरy_put(&fctx->notअगरy);
		spin_unlock_irqrestore(&fctx->lock, flags);
	पूर्ण
	वापस dma_fence_is_संकेतed(&fence->base);
पूर्ण

अटल दीर्घ
nouveau_fence_रुको_legacy(काष्ठा dma_fence *f, bool पूर्णांकr, दीर्घ रुको)
अणु
	काष्ठा nouveau_fence *fence = from_fence(f);
	अचिन्हित दीर्घ sleep_समय = NSEC_PER_MSEC / 1000;
	अचिन्हित दीर्घ t = jअगरfies, समयout = t + रुको;

	जबतक (!nouveau_fence_करोne(fence)) अणु
		kसमय_प्रकार kt;

		t = jअगरfies;

		अगर (रुको != MAX_SCHEDULE_TIMEOUT && समय_after_eq(t, समयout)) अणु
			__set_current_state(TASK_RUNNING);
			वापस 0;
		पूर्ण

		__set_current_state(पूर्णांकr ? TASK_INTERRUPTIBLE :
					   TASK_UNINTERRUPTIBLE);

		kt = sleep_समय;
		schedule_hrसमयout(&kt, HRTIMER_MODE_REL);
		sleep_समय *= 2;
		अगर (sleep_समय > NSEC_PER_MSEC)
			sleep_समय = NSEC_PER_MSEC;

		अगर (पूर्णांकr && संकेत_pending(current))
			वापस -ERESTARTSYS;
	पूर्ण

	__set_current_state(TASK_RUNNING);

	वापस समयout - t;
पूर्ण

अटल पूर्णांक
nouveau_fence_रुको_busy(काष्ठा nouveau_fence *fence, bool पूर्णांकr)
अणु
	पूर्णांक ret = 0;

	जबतक (!nouveau_fence_करोne(fence)) अणु
		अगर (समय_after_eq(jअगरfies, fence->समयout)) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		__set_current_state(पूर्णांकr ?
				    TASK_INTERRUPTIBLE :
				    TASK_UNINTERRUPTIBLE);

		अगर (पूर्णांकr && संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
	पूर्ण

	__set_current_state(TASK_RUNNING);
	वापस ret;
पूर्ण

पूर्णांक
nouveau_fence_रुको(काष्ठा nouveau_fence *fence, bool lazy, bool पूर्णांकr)
अणु
	दीर्घ ret;

	अगर (!lazy)
		वापस nouveau_fence_रुको_busy(fence, पूर्णांकr);

	ret = dma_fence_रुको_समयout(&fence->base, पूर्णांकr, 15 * HZ);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (!ret)
		वापस -EBUSY;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक
nouveau_fence_sync(काष्ठा nouveau_bo *nvbo, काष्ठा nouveau_channel *chan, bool exclusive, bool पूर्णांकr)
अणु
	काष्ठा nouveau_fence_chan *fctx = chan->fence;
	काष्ठा dma_fence *fence;
	काष्ठा dma_resv *resv = nvbo->bo.base.resv;
	काष्ठा dma_resv_list *fobj;
	काष्ठा nouveau_fence *f;
	पूर्णांक ret = 0, i;

	अगर (!exclusive) अणु
		ret = dma_resv_reserve_shared(resv, 1);

		अगर (ret)
			वापस ret;
	पूर्ण

	fobj = dma_resv_get_list(resv);
	fence = dma_resv_get_excl(resv);

	अगर (fence && (!exclusive || !fobj || !fobj->shared_count)) अणु
		काष्ठा nouveau_channel *prev = शून्य;
		bool must_रुको = true;

		f = nouveau_local_fence(fence, chan->drm);
		अगर (f) अणु
			rcu_पढ़ो_lock();
			prev = rcu_dereference(f->channel);
			अगर (prev && (prev == chan || fctx->sync(f, prev, chan) == 0))
				must_रुको = false;
			rcu_पढ़ो_unlock();
		पूर्ण

		अगर (must_रुको)
			ret = dma_fence_रुको(fence, पूर्णांकr);

		वापस ret;
	पूर्ण

	अगर (!exclusive || !fobj)
		वापस ret;

	क्रम (i = 0; i < fobj->shared_count && !ret; ++i) अणु
		काष्ठा nouveau_channel *prev = शून्य;
		bool must_रुको = true;

		fence = rcu_dereference_रक्षित(fobj->shared[i],
						dma_resv_held(resv));

		f = nouveau_local_fence(fence, chan->drm);
		अगर (f) अणु
			rcu_पढ़ो_lock();
			prev = rcu_dereference(f->channel);
			अगर (prev && (prev == chan || fctx->sync(f, prev, chan) == 0))
				must_रुको = false;
			rcu_पढ़ो_unlock();
		पूर्ण

		अगर (must_रुको)
			ret = dma_fence_रुको(fence, पूर्णांकr);
	पूर्ण

	वापस ret;
पूर्ण

व्योम
nouveau_fence_unref(काष्ठा nouveau_fence **pfence)
अणु
	अगर (*pfence)
		dma_fence_put(&(*pfence)->base);
	*pfence = शून्य;
पूर्ण

पूर्णांक
nouveau_fence_new(काष्ठा nouveau_channel *chan, bool sysmem,
		  काष्ठा nouveau_fence **pfence)
अणु
	काष्ठा nouveau_fence *fence;
	पूर्णांक ret = 0;

	अगर (unlikely(!chan->fence))
		वापस -ENODEV;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस -ENOMEM;

	ret = nouveau_fence_emit(fence, chan);
	अगर (ret)
		nouveau_fence_unref(&fence);

	*pfence = fence;
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nouveau_fence_get_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "nouveau";
पूर्ण

अटल स्थिर अक्षर *nouveau_fence_get_समयline_name(काष्ठा dma_fence *f)
अणु
	काष्ठा nouveau_fence *fence = from_fence(f);
	काष्ठा nouveau_fence_chan *fctx = nouveau_fctx(fence);

	वापस !fctx->dead ? fctx->name : "dead channel";
पूर्ण

/*
 * In an ideal world, पढ़ो would not assume the channel context is still alive.
 * This function may be called from another device, running पूर्णांकo मुक्त memory as a
 * result. The drm node should still be there, so we can derive the index from
 * the fence context.
 */
अटल bool nouveau_fence_is_संकेतed(काष्ठा dma_fence *f)
अणु
	काष्ठा nouveau_fence *fence = from_fence(f);
	काष्ठा nouveau_fence_chan *fctx = nouveau_fctx(fence);
	काष्ठा nouveau_channel *chan;
	bool ret = false;

	rcu_पढ़ो_lock();
	chan = rcu_dereference(fence->channel);
	अगर (chan)
		ret = (पूर्णांक)(fctx->पढ़ो(chan) - fence->base.seqno) >= 0;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल bool nouveau_fence_no_संकेतing(काष्ठा dma_fence *f)
अणु
	काष्ठा nouveau_fence *fence = from_fence(f);

	/*
	 * caller should have a reference on the fence,
	 * अन्यथा fence could get मुक्तd here
	 */
	WARN_ON(kref_पढ़ो(&fence->base.refcount) <= 1);

	/*
	 * This needs uevents to work correctly, but dma_fence_add_callback relies on
	 * being able to enable संकेतing. It will still get संकेतed eventually,
	 * just not right away.
	 */
	अगर (nouveau_fence_is_संकेतed(f)) अणु
		list_del(&fence->head);

		dma_fence_put(&fence->base);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम nouveau_fence_release(काष्ठा dma_fence *f)
अणु
	काष्ठा nouveau_fence *fence = from_fence(f);
	काष्ठा nouveau_fence_chan *fctx = nouveau_fctx(fence);

	kref_put(&fctx->fence_ref, nouveau_fence_context_put);
	dma_fence_मुक्त(&fence->base);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops nouveau_fence_ops_legacy = अणु
	.get_driver_name = nouveau_fence_get_get_driver_name,
	.get_समयline_name = nouveau_fence_get_समयline_name,
	.enable_संकेतing = nouveau_fence_no_संकेतing,
	.संकेतed = nouveau_fence_is_संकेतed,
	.रुको = nouveau_fence_रुको_legacy,
	.release = nouveau_fence_release
पूर्ण;

अटल bool nouveau_fence_enable_संकेतing(काष्ठा dma_fence *f)
अणु
	काष्ठा nouveau_fence *fence = from_fence(f);
	काष्ठा nouveau_fence_chan *fctx = nouveau_fctx(fence);
	bool ret;

	अगर (!fctx->notअगरy_ref++)
		nvअगर_notअगरy_get(&fctx->notअगरy);

	ret = nouveau_fence_no_संकेतing(f);
	अगर (ret)
		set_bit(DMA_FENCE_FLAG_USER_BITS, &fence->base.flags);
	अन्यथा अगर (!--fctx->notअगरy_ref)
		nvअगर_notअगरy_put(&fctx->notअगरy);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops nouveau_fence_ops_uevent = अणु
	.get_driver_name = nouveau_fence_get_get_driver_name,
	.get_समयline_name = nouveau_fence_get_समयline_name,
	.enable_संकेतing = nouveau_fence_enable_संकेतing,
	.संकेतed = nouveau_fence_is_संकेतed,
	.release = nouveau_fence_release
पूर्ण;
