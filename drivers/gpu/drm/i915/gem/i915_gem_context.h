<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_CONTEXT_H__
#घोषणा __I915_GEM_CONTEXT_H__

#समावेश "i915_gem_context_types.h"

#समावेश "gt/intel_context.h"

#समावेश "i915_drv.h"
#समावेश "i915_gem.h"
#समावेश "i915_scheduler.h"
#समावेश "intel_device_info.h"

काष्ठा drm_device;
काष्ठा drm_file;

अटल अंतरभूत bool i915_gem_context_is_बंदd(स्थिर काष्ठा i915_gem_context *ctx)
अणु
	वापस test_bit(CONTEXT_CLOSED, &ctx->flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_set_बंदd(काष्ठा i915_gem_context *ctx)
अणु
	GEM_BUG_ON(i915_gem_context_is_बंदd(ctx));
	set_bit(CONTEXT_CLOSED, &ctx->flags);
पूर्ण

अटल अंतरभूत bool i915_gem_context_no_error_capture(स्थिर काष्ठा i915_gem_context *ctx)
अणु
	वापस test_bit(UCONTEXT_NO_ERROR_CAPTURE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_set_no_error_capture(काष्ठा i915_gem_context *ctx)
अणु
	set_bit(UCONTEXT_NO_ERROR_CAPTURE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_clear_no_error_capture(काष्ठा i915_gem_context *ctx)
अणु
	clear_bit(UCONTEXT_NO_ERROR_CAPTURE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत bool i915_gem_context_is_bannable(स्थिर काष्ठा i915_gem_context *ctx)
अणु
	वापस test_bit(UCONTEXT_BANNABLE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_set_bannable(काष्ठा i915_gem_context *ctx)
अणु
	set_bit(UCONTEXT_BANNABLE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_clear_bannable(काष्ठा i915_gem_context *ctx)
अणु
	clear_bit(UCONTEXT_BANNABLE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत bool i915_gem_context_is_recoverable(स्थिर काष्ठा i915_gem_context *ctx)
अणु
	वापस test_bit(UCONTEXT_RECOVERABLE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_set_recoverable(काष्ठा i915_gem_context *ctx)
अणु
	set_bit(UCONTEXT_RECOVERABLE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_clear_recoverable(काष्ठा i915_gem_context *ctx)
अणु
	clear_bit(UCONTEXT_RECOVERABLE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत bool i915_gem_context_is_persistent(स्थिर काष्ठा i915_gem_context *ctx)
अणु
	वापस test_bit(UCONTEXT_PERSISTENCE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_set_persistence(काष्ठा i915_gem_context *ctx)
अणु
	set_bit(UCONTEXT_PERSISTENCE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_clear_persistence(काष्ठा i915_gem_context *ctx)
अणु
	clear_bit(UCONTEXT_PERSISTENCE, &ctx->user_flags);
पूर्ण

अटल अंतरभूत bool
i915_gem_context_user_engines(स्थिर काष्ठा i915_gem_context *ctx)
अणु
	वापस test_bit(CONTEXT_USER_ENGINES, &ctx->flags);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_context_set_user_engines(काष्ठा i915_gem_context *ctx)
अणु
	set_bit(CONTEXT_USER_ENGINES, &ctx->flags);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_context_clear_user_engines(काष्ठा i915_gem_context *ctx)
अणु
	clear_bit(CONTEXT_USER_ENGINES, &ctx->flags);
पूर्ण

/* i915_gem_context.c */
व्योम i915_gem_init__contexts(काष्ठा drm_i915_निजी *i915);

पूर्णांक i915_gem_context_खोलो(काष्ठा drm_i915_निजी *i915,
			  काष्ठा drm_file *file);
व्योम i915_gem_context_बंद(काष्ठा drm_file *file);

व्योम i915_gem_context_release(काष्ठा kref *ctx_ref);

पूर्णांक i915_gem_vm_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file);
पूर्णांक i915_gem_vm_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file);

पूर्णांक i915_gem_context_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file);
पूर्णांक i915_gem_context_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file);
पूर्णांक i915_gem_context_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
पूर्णांक i915_gem_context_setparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
पूर्णांक i915_gem_context_reset_stats_ioctl(काष्ठा drm_device *dev, व्योम *data,
				       काष्ठा drm_file *file);

अटल अंतरभूत काष्ठा i915_gem_context *
i915_gem_context_get(काष्ठा i915_gem_context *ctx)
अणु
	kref_get(&ctx->ref);
	वापस ctx;
पूर्ण

अटल अंतरभूत व्योम i915_gem_context_put(काष्ठा i915_gem_context *ctx)
अणु
	kref_put(&ctx->ref, i915_gem_context_release);
पूर्ण

अटल अंतरभूत काष्ठा i915_address_space *
i915_gem_context_vm(काष्ठा i915_gem_context *ctx)
अणु
	वापस rcu_dereference_रक्षित(ctx->vm, lockdep_is_held(&ctx->mutex));
पूर्ण

अटल अंतरभूत काष्ठा i915_address_space *
i915_gem_context_get_vm_rcu(काष्ठा i915_gem_context *ctx)
अणु
	काष्ठा i915_address_space *vm;

	rcu_पढ़ो_lock();
	vm = rcu_dereference(ctx->vm);
	अगर (!vm)
		vm = &ctx->i915->ggtt.vm;
	vm = i915_vm_get(vm);
	rcu_पढ़ो_unlock();

	वापस vm;
पूर्ण

अटल अंतरभूत काष्ठा i915_gem_engines *
i915_gem_context_engines(काष्ठा i915_gem_context *ctx)
अणु
	वापस rcu_dereference_रक्षित(ctx->engines,
					 lockdep_is_held(&ctx->engines_mutex));
पूर्ण

अटल अंतरभूत काष्ठा i915_gem_engines *
i915_gem_context_lock_engines(काष्ठा i915_gem_context *ctx)
	__acquires(&ctx->engines_mutex)
अणु
	mutex_lock(&ctx->engines_mutex);
	वापस i915_gem_context_engines(ctx);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_context_unlock_engines(काष्ठा i915_gem_context *ctx)
	__releases(&ctx->engines_mutex)
अणु
	mutex_unlock(&ctx->engines_mutex);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_context *
i915_gem_context_get_engine(काष्ठा i915_gem_context *ctx, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_context *ce;

	rcu_पढ़ो_lock(); अणु
		काष्ठा i915_gem_engines *e = rcu_dereference(ctx->engines);
		अगर (unlikely(!e)) /* context was बंदd! */
			ce = ERR_PTR(-ENOENT);
		अन्यथा अगर (likely(idx < e->num_engines && e->engines[idx]))
			ce = पूर्णांकel_context_get(e->engines[idx]);
		अन्यथा
			ce = ERR_PTR(-EINVAL);
	पूर्ण rcu_पढ़ो_unlock();

	वापस ce;
पूर्ण

अटल अंतरभूत व्योम
i915_gem_engines_iter_init(काष्ठा i915_gem_engines_iter *it,
			   काष्ठा i915_gem_engines *engines)
अणु
	it->engines = engines;
	it->idx = 0;
पूर्ण

काष्ठा पूर्णांकel_context *
i915_gem_engines_iter_next(काष्ठा i915_gem_engines_iter *it);

#घोषणा क्रम_each_gem_engine(ce, engines, it) \
	क्रम (i915_gem_engines_iter_init(&(it), (engines)); \
	     ((ce) = i915_gem_engines_iter_next(&(it)));)

काष्ठा i915_lut_handle *i915_lut_handle_alloc(व्योम);
व्योम i915_lut_handle_मुक्त(काष्ठा i915_lut_handle *lut);

पूर्णांक i915_gem_user_to_context_sseu(काष्ठा पूर्णांकel_gt *gt,
				  स्थिर काष्ठा drm_i915_gem_context_param_sseu *user,
				  काष्ठा पूर्णांकel_sseu *context);

#पूर्ण_अगर /* !__I915_GEM_CONTEXT_H__ */
