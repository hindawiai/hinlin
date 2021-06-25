<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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

#अगर_अघोषित __I915_GEM_H__
#घोषणा __I915_GEM_H__

#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <drm/drm_drv.h>

#समावेश "i915_utils.h"

काष्ठा drm_i915_निजी;

#अगर_घोषित CONFIG_DRM_I915_DEBUG_GEM

#घोषणा GEM_SHOW_DEBUG() drm_debug_enabled(DRM_UT_DRIVER)

#अगर_घोषित CONFIG_DRM_I915_DEBUG_GEM_ONCE
#घोषणा __GEM_BUG(cond) BUG()
#अन्यथा
#घोषणा __GEM_BUG(cond) \
	WARN(1, "%s:%d GEM_BUG_ON(%s)\n", __func__, __LINE__, __stringअगरy(cond))
#पूर्ण_अगर

#घोषणा GEM_BUG_ON(condition) करो अणु अगर (unlikely((condition))) अणु	\
		GEM_TRACE_ERR("%s:%d GEM_BUG_ON(%s)\n", \
			      __func__, __LINE__, __stringअगरy(condition)); \
		GEM_TRACE_DUMP(); \
		__GEM_BUG(condition); \
		पूर्ण \
	पूर्ण जबतक(0)
#घोषणा GEM_WARN_ON(expr) WARN_ON(expr)

#घोषणा GEM_DEBUG_DECL(var) var
#घोषणा GEM_DEBUG_EXEC(expr) expr
#घोषणा GEM_DEBUG_BUG_ON(expr) GEM_BUG_ON(expr)
#घोषणा GEM_DEBUG_WARN_ON(expr) GEM_WARN_ON(expr)

#अन्यथा

#घोषणा GEM_SHOW_DEBUG() (0)

#घोषणा GEM_BUG_ON(expr) BUILD_BUG_ON_INVALID(expr)
#घोषणा GEM_WARN_ON(expr) (अणु unlikely(!!(expr)); पूर्ण)

#घोषणा GEM_DEBUG_DECL(var)
#घोषणा GEM_DEBUG_EXEC(expr) करो अणु पूर्ण जबतक (0)
#घोषणा GEM_DEBUG_BUG_ON(expr)
#घोषणा GEM_DEBUG_WARN_ON(expr) (अणु BUILD_BUG_ON_INVALID(expr); 0; पूर्ण)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DRM_I915_TRACE_GEM)
#घोषणा GEM_TRACE(...) trace_prपूर्णांकk(__VA_ARGS__)
#घोषणा GEM_TRACE_ERR(...) करो अणु						\
	pr_err(__VA_ARGS__);						\
	trace_prपूर्णांकk(__VA_ARGS__);					\
पूर्ण जबतक (0)
#घोषणा GEM_TRACE_DUMP() \
	करो अणु ftrace_dump(DUMP_ALL); __add_taपूर्णांक_क्रम_CI(TAINT_WARN); पूर्ण जबतक (0)
#घोषणा GEM_TRACE_DUMP_ON(expr) \
	करो अणु अगर (expr) GEM_TRACE_DUMP(); पूर्ण जबतक (0)
#अन्यथा
#घोषणा GEM_TRACE(...) करो अणु पूर्ण जबतक (0)
#घोषणा GEM_TRACE_ERR(...) करो अणु पूर्ण जबतक (0)
#घोषणा GEM_TRACE_DUMP() करो अणु पूर्ण जबतक (0)
#घोषणा GEM_TRACE_DUMP_ON(expr) BUILD_BUG_ON_INVALID(expr)
#पूर्ण_अगर

#घोषणा I915_GEM_IDLE_TIMEOUT (HZ / 5)

अटल अंतरभूत व्योम tasklet_lock(काष्ठा tasklet_काष्ठा *t)
अणु
	जबतक (!tasklet_trylock(t))
		cpu_relax();
पूर्ण

अटल अंतरभूत bool tasklet_is_locked(स्थिर काष्ठा tasklet_काष्ठा *t)
अणु
	वापस test_bit(TASKLET_STATE_RUN, &t->state);
पूर्ण

अटल अंतरभूत व्योम __tasklet_disable_sync_once(काष्ठा tasklet_काष्ठा *t)
अणु
	अगर (!atomic_fetch_inc(&t->count))
		tasklet_unlock_spin_रुको(t);
पूर्ण

अटल अंतरभूत bool __tasklet_is_enabled(स्थिर काष्ठा tasklet_काष्ठा *t)
अणु
	वापस !atomic_पढ़ो(&t->count);
पूर्ण

अटल अंतरभूत bool __tasklet_enable(काष्ठा tasklet_काष्ठा *t)
अणु
	वापस atomic_dec_and_test(&t->count);
पूर्ण

अटल अंतरभूत bool __tasklet_is_scheduled(काष्ठा tasklet_काष्ठा *t)
अणु
	वापस test_bit(TASKLET_STATE_SCHED, &t->state);
पूर्ण

काष्ठा i915_gem_ww_ctx अणु
	काष्ठा ww_acquire_ctx ctx;
	काष्ठा list_head obj_list;
	bool पूर्णांकr;
	काष्ठा drm_i915_gem_object *contended;
पूर्ण;

व्योम i915_gem_ww_ctx_init(काष्ठा i915_gem_ww_ctx *ctx, bool पूर्णांकr);
व्योम i915_gem_ww_ctx_fini(काष्ठा i915_gem_ww_ctx *ctx);
पूर्णांक __must_check i915_gem_ww_ctx_backoff(काष्ठा i915_gem_ww_ctx *ctx);
व्योम i915_gem_ww_unlock_single(काष्ठा drm_i915_gem_object *obj);

#पूर्ण_अगर /* __I915_GEM_H__ */
