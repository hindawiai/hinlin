<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "mock_context.h"
#समावेश "selftests/mock_drm.h"
#समावेश "selftests/mock_gtt.h"

काष्ठा i915_gem_context *
mock_context(काष्ठा drm_i915_निजी *i915,
	     स्थिर अक्षर *name)
अणु
	काष्ठा i915_gem_context *ctx;
	काष्ठा i915_gem_engines *e;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	kref_init(&ctx->ref);
	INIT_LIST_HEAD(&ctx->link);
	ctx->i915 = i915;

	mutex_init(&ctx->mutex);

	spin_lock_init(&ctx->stale.lock);
	INIT_LIST_HEAD(&ctx->stale.engines);

	i915_gem_context_set_persistence(ctx);

	mutex_init(&ctx->engines_mutex);
	e = शेष_engines(ctx);
	अगर (IS_ERR(e))
		जाओ err_मुक्त;
	RCU_INIT_POINTER(ctx->engines, e);

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	mutex_init(&ctx->lut_mutex);

	अगर (name) अणु
		काष्ठा i915_ppgtt *ppgtt;

		म_नकलन(ctx->name, name, माप(ctx->name) - 1);

		ppgtt = mock_ppgtt(i915, name);
		अगर (!ppgtt)
			जाओ err_put;

		mutex_lock(&ctx->mutex);
		__set_ppgtt(ctx, &ppgtt->vm);
		mutex_unlock(&ctx->mutex);

		i915_vm_put(&ppgtt->vm);
	पूर्ण

	वापस ctx;

err_मुक्त:
	kमुक्त(ctx);
	वापस शून्य;

err_put:
	i915_gem_context_set_बंदd(ctx);
	i915_gem_context_put(ctx);
	वापस शून्य;
पूर्ण

व्योम mock_context_बंद(काष्ठा i915_gem_context *ctx)
अणु
	context_बंद(ctx);
पूर्ण

व्योम mock_init_contexts(काष्ठा drm_i915_निजी *i915)
अणु
	init_contexts(&i915->gem.contexts);
पूर्ण

काष्ठा i915_gem_context *
live_context(काष्ठा drm_i915_निजी *i915, काष्ठा file *file)
अणु
	काष्ठा i915_gem_context *ctx;
	पूर्णांक err;
	u32 id;

	ctx = i915_gem_create_context(i915, 0);
	अगर (IS_ERR(ctx))
		वापस ctx;

	i915_gem_context_set_no_error_capture(ctx);

	err = gem_context_रेजिस्टर(ctx, to_drm_file(file)->driver_priv, &id);
	अगर (err < 0)
		जाओ err_ctx;

	वापस ctx;

err_ctx:
	context_बंद(ctx);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा i915_gem_context *
live_context_क्रम_engine(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा file *file)
अणु
	काष्ठा i915_gem_engines *engines;
	काष्ठा i915_gem_context *ctx;
	काष्ठा पूर्णांकel_context *ce;

	engines = alloc_engines(1);
	अगर (!engines)
		वापस ERR_PTR(-ENOMEM);

	ctx = live_context(engine->i915, file);
	अगर (IS_ERR(ctx)) अणु
		__मुक्त_engines(engines, 0);
		वापस ctx;
	पूर्ण

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce)) अणु
		__मुक्त_engines(engines, 0);
		वापस ERR_CAST(ce);
	पूर्ण

	पूर्णांकel_context_set_gem(ce, ctx);
	engines->engines[0] = ce;
	engines->num_engines = 1;

	mutex_lock(&ctx->engines_mutex);
	i915_gem_context_set_user_engines(ctx);
	engines = rcu_replace_poपूर्णांकer(ctx->engines, engines, 1);
	mutex_unlock(&ctx->engines_mutex);

	engines_idle_release(ctx, engines);

	वापस ctx;
पूर्ण

काष्ठा i915_gem_context *
kernel_context(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_gem_context *ctx;

	ctx = i915_gem_create_context(i915, 0);
	अगर (IS_ERR(ctx))
		वापस ctx;

	i915_gem_context_clear_bannable(ctx);
	i915_gem_context_set_persistence(ctx);
	i915_gem_context_set_no_error_capture(ctx);

	वापस ctx;
पूर्ण

व्योम kernel_context_बंद(काष्ठा i915_gem_context *ctx)
अणु
	context_बंद(ctx);
पूर्ण
