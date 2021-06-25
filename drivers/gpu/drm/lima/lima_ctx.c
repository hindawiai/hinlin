<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2018-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/slab.h>

#समावेश "lima_device.h"
#समावेश "lima_ctx.h"

पूर्णांक lima_ctx_create(काष्ठा lima_device *dev, काष्ठा lima_ctx_mgr *mgr, u32 *id)
अणु
	काष्ठा lima_ctx *ctx;
	पूर्णांक i, err;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->dev = dev;
	kref_init(&ctx->refcnt);

	क्रम (i = 0; i < lima_pipe_num; i++) अणु
		err = lima_sched_context_init(dev->pipe + i, ctx->context + i, &ctx->guilty);
		अगर (err)
			जाओ err_out0;
	पूर्ण

	err = xa_alloc(&mgr->handles, id, ctx, xa_limit_32b, GFP_KERNEL);
	अगर (err < 0)
		जाओ err_out0;

	ctx->pid = task_pid_nr(current);
	get_task_comm(ctx->pname, current);

	वापस 0;

err_out0:
	क्रम (i--; i >= 0; i--)
		lima_sched_context_fini(dev->pipe + i, ctx->context + i);
	kमुक्त(ctx);
	वापस err;
पूर्ण

अटल व्योम lima_ctx_करो_release(काष्ठा kref *ref)
अणु
	काष्ठा lima_ctx *ctx = container_of(ref, काष्ठा lima_ctx, refcnt);
	पूर्णांक i;

	क्रम (i = 0; i < lima_pipe_num; i++)
		lima_sched_context_fini(ctx->dev->pipe + i, ctx->context + i);
	kमुक्त(ctx);
पूर्ण

पूर्णांक lima_ctx_मुक्त(काष्ठा lima_ctx_mgr *mgr, u32 id)
अणु
	काष्ठा lima_ctx *ctx;
	पूर्णांक ret = 0;

	mutex_lock(&mgr->lock);
	ctx = xa_erase(&mgr->handles, id);
	अगर (ctx)
		kref_put(&ctx->refcnt, lima_ctx_करो_release);
	अन्यथा
		ret = -EINVAL;
	mutex_unlock(&mgr->lock);
	वापस ret;
पूर्ण

काष्ठा lima_ctx *lima_ctx_get(काष्ठा lima_ctx_mgr *mgr, u32 id)
अणु
	काष्ठा lima_ctx *ctx;

	mutex_lock(&mgr->lock);
	ctx = xa_load(&mgr->handles, id);
	अगर (ctx)
		kref_get(&ctx->refcnt);
	mutex_unlock(&mgr->lock);
	वापस ctx;
पूर्ण

व्योम lima_ctx_put(काष्ठा lima_ctx *ctx)
अणु
	kref_put(&ctx->refcnt, lima_ctx_करो_release);
पूर्ण

व्योम lima_ctx_mgr_init(काष्ठा lima_ctx_mgr *mgr)
अणु
	mutex_init(&mgr->lock);
	xa_init_flags(&mgr->handles, XA_FLAGS_ALLOC);
पूर्ण

व्योम lima_ctx_mgr_fini(काष्ठा lima_ctx_mgr *mgr)
अणु
	काष्ठा lima_ctx *ctx;
	अचिन्हित दीर्घ id;

	xa_क्रम_each(&mgr->handles, id, ctx) अणु
		kref_put(&ctx->refcnt, lima_ctx_करो_release);
	पूर्ण

	xa_destroy(&mgr->handles);
	mutex_destroy(&mgr->lock);
पूर्ण
