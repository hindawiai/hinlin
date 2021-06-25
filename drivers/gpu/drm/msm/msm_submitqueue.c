<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kref.h>
#समावेश <linux/uaccess.h>

#समावेश "msm_gpu.h"

व्योम msm_submitqueue_destroy(काष्ठा kref *kref)
अणु
	काष्ठा msm_gpu_submitqueue *queue = container_of(kref,
		काष्ठा msm_gpu_submitqueue, ref);

	msm_file_निजी_put(queue->ctx);

	kमुक्त(queue);
पूर्ण

काष्ठा msm_gpu_submitqueue *msm_submitqueue_get(काष्ठा msm_file_निजी *ctx,
		u32 id)
अणु
	काष्ठा msm_gpu_submitqueue *entry;

	अगर (!ctx)
		वापस शून्य;

	पढ़ो_lock(&ctx->queuelock);

	list_क्रम_each_entry(entry, &ctx->submitqueues, node) अणु
		अगर (entry->id == id) अणु
			kref_get(&entry->ref);
			पढ़ो_unlock(&ctx->queuelock);

			वापस entry;
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&ctx->queuelock);
	वापस शून्य;
पूर्ण

व्योम msm_submitqueue_बंद(काष्ठा msm_file_निजी *ctx)
अणु
	काष्ठा msm_gpu_submitqueue *entry, *पंचांगp;

	अगर (!ctx)
		वापस;

	/*
	 * No lock needed in बंद and there won't
	 * be any more user ioctls coming our way
	 */
	list_क्रम_each_entry_safe(entry, पंचांगp, &ctx->submitqueues, node) अणु
		list_del(&entry->node);
		msm_submitqueue_put(entry);
	पूर्ण
पूर्ण

पूर्णांक msm_submitqueue_create(काष्ठा drm_device *drm, काष्ठा msm_file_निजी *ctx,
		u32 prio, u32 flags, u32 *id)
अणु
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	काष्ठा msm_gpu_submitqueue *queue;

	अगर (!ctx)
		वापस -ENODEV;

	queue = kzalloc(माप(*queue), GFP_KERNEL);

	अगर (!queue)
		वापस -ENOMEM;

	kref_init(&queue->ref);
	queue->flags = flags;

	अगर (priv->gpu) अणु
		अगर (prio >= priv->gpu->nr_rings) अणु
			kमुक्त(queue);
			वापस -EINVAL;
		पूर्ण

		queue->prio = prio;
	पूर्ण

	ग_लिखो_lock(&ctx->queuelock);

	queue->ctx = msm_file_निजी_get(ctx);
	queue->id = ctx->queueid++;

	अगर (id)
		*id = queue->id;

	list_add_tail(&queue->node, &ctx->submitqueues);

	ग_लिखो_unlock(&ctx->queuelock);

	वापस 0;
पूर्ण

पूर्णांक msm_submitqueue_init(काष्ठा drm_device *drm, काष्ठा msm_file_निजी *ctx)
अणु
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	पूर्णांक शेष_prio;

	अगर (!ctx)
		वापस 0;

	/*
	 * Select priority 2 as the "default priority" unless nr_rings is less
	 * than 2 and then pick the lowest pirority
	 */
	शेष_prio = priv->gpu ?
		clamp_t(uपूर्णांक32_t, 2, 0, priv->gpu->nr_rings - 1) : 0;

	INIT_LIST_HEAD(&ctx->submitqueues);

	rwlock_init(&ctx->queuelock);

	वापस msm_submitqueue_create(drm, ctx, शेष_prio, 0, शून्य);
पूर्ण

अटल पूर्णांक msm_submitqueue_query_faults(काष्ठा msm_gpu_submitqueue *queue,
		काष्ठा drm_msm_submitqueue_query *args)
अणु
	माप_प्रकार size = min_t(माप_प्रकार, args->len, माप(queue->faults));
	पूर्णांक ret;

	/* If a zero length was passed in, वापस the data size we expect */
	अगर (!args->len) अणु
		args->len = माप(queue->faults);
		वापस 0;
	पूर्ण

	/* Set the length to the actual size of the data */
	args->len = size;

	ret = copy_to_user(u64_to_user_ptr(args->data), &queue->faults, size);

	वापस ret ? -EFAULT : 0;
पूर्ण

पूर्णांक msm_submitqueue_query(काष्ठा drm_device *drm, काष्ठा msm_file_निजी *ctx,
		काष्ठा drm_msm_submitqueue_query *args)
अणु
	काष्ठा msm_gpu_submitqueue *queue;
	पूर्णांक ret = -EINVAL;

	अगर (args->pad)
		वापस -EINVAL;

	queue = msm_submitqueue_get(ctx, args->id);
	अगर (!queue)
		वापस -ENOENT;

	अगर (args->param == MSM_SUBMITQUEUE_PARAM_FAULTS)
		ret = msm_submitqueue_query_faults(queue, args);

	msm_submitqueue_put(queue);

	वापस ret;
पूर्ण

पूर्णांक msm_submitqueue_हटाओ(काष्ठा msm_file_निजी *ctx, u32 id)
अणु
	काष्ठा msm_gpu_submitqueue *entry;

	अगर (!ctx)
		वापस 0;

	/*
	 * id 0 is the "default" queue and can't be destroyed
	 * by the user
	 */
	अगर (!id)
		वापस -ENOENT;

	ग_लिखो_lock(&ctx->queuelock);

	list_क्रम_each_entry(entry, &ctx->submitqueues, node) अणु
		अगर (entry->id == id) अणु
			list_del(&entry->node);
			ग_लिखो_unlock(&ctx->queuelock);

			msm_submitqueue_put(entry);
			वापस 0;
		पूर्ण
	पूर्ण

	ग_लिखो_unlock(&ctx->queuelock);
	वापस -ENOENT;
पूर्ण

