<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/माला.स>

#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_display_types.h"
#समावेश "intel_global_state.h"

अटल व्योम __पूर्णांकel_atomic_global_state_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा पूर्णांकel_global_state *obj_state =
		container_of(kref, काष्ठा पूर्णांकel_global_state, ref);
	काष्ठा पूर्णांकel_global_obj *obj = obj_state->obj;

	obj->funcs->atomic_destroy_state(obj, obj_state);
पूर्ण

अटल व्योम पूर्णांकel_atomic_global_state_put(काष्ठा पूर्णांकel_global_state *obj_state)
अणु
	kref_put(&obj_state->ref, __पूर्णांकel_atomic_global_state_मुक्त);
पूर्ण

अटल काष्ठा पूर्णांकel_global_state *
पूर्णांकel_atomic_global_state_get(काष्ठा पूर्णांकel_global_state *obj_state)
अणु
	kref_get(&obj_state->ref);

	वापस obj_state;
पूर्ण

व्योम पूर्णांकel_atomic_global_obj_init(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा पूर्णांकel_global_obj *obj,
				  काष्ठा पूर्णांकel_global_state *state,
				  स्थिर काष्ठा पूर्णांकel_global_state_funcs *funcs)
अणु
	स_रखो(obj, 0, माप(*obj));

	state->obj = obj;

	kref_init(&state->ref);

	obj->state = state;
	obj->funcs = funcs;
	list_add_tail(&obj->head, &dev_priv->global_obj_list);
पूर्ण

व्योम पूर्णांकel_atomic_global_obj_cleanup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_global_obj *obj, *next;

	list_क्रम_each_entry_safe(obj, next, &dev_priv->global_obj_list, head) अणु
		list_del(&obj->head);

		drm_WARN_ON(&dev_priv->drm, kref_पढ़ो(&obj->state->ref) != 1);
		पूर्णांकel_atomic_global_state_put(obj->state);
	पूर्ण
पूर्ण

अटल व्योम निश्चित_global_state_ग_लिखो_locked(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc)
		drm_modeset_lock_निश्चित_held(&crtc->base.mutex);
पूर्ण

अटल bool modeset_lock_is_held(काष्ठा drm_modeset_acquire_ctx *ctx,
				 काष्ठा drm_modeset_lock *lock)
अणु
	काष्ठा drm_modeset_lock *l;

	list_क्रम_each_entry(l, &ctx->locked, head) अणु
		अगर (lock == l)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम निश्चित_global_state_पढ़ो_locked(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_modeset_acquire_ctx *ctx = state->base.acquire_ctx;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		अगर (modeset_lock_is_held(ctx, &crtc->base.mutex))
			वापस;
	पूर्ण

	drm_WARN(&dev_priv->drm, 1, "Global state not read locked\n");
पूर्ण

काष्ठा पूर्णांकel_global_state *
पूर्णांकel_atomic_get_global_obj_state(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_global_obj *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(state->base.dev);
	पूर्णांक index, num_objs, i;
	माप_प्रकार size;
	काष्ठा __पूर्णांकel_global_objs_state *arr;
	काष्ठा पूर्णांकel_global_state *obj_state;

	क्रम (i = 0; i < state->num_global_objs; i++)
		अगर (obj == state->global_objs[i].ptr)
			वापस state->global_objs[i].state;

	निश्चित_global_state_पढ़ो_locked(state);

	num_objs = state->num_global_objs + 1;
	size = माप(*state->global_objs) * num_objs;
	arr = kपुनः_स्मृति(state->global_objs, size, GFP_KERNEL);
	अगर (!arr)
		वापस ERR_PTR(-ENOMEM);

	state->global_objs = arr;
	index = state->num_global_objs;
	स_रखो(&state->global_objs[index], 0, माप(*state->global_objs));

	obj_state = obj->funcs->atomic_duplicate_state(obj);
	अगर (!obj_state)
		वापस ERR_PTR(-ENOMEM);

	obj_state->obj = obj;
	obj_state->changed = false;

	kref_init(&obj_state->ref);

	state->global_objs[index].state = obj_state;
	state->global_objs[index].old_state =
		पूर्णांकel_atomic_global_state_get(obj->state);
	state->global_objs[index].new_state = obj_state;
	state->global_objs[index].ptr = obj;
	obj_state->state = state;

	state->num_global_objs = num_objs;

	drm_dbg_atomic(&i915->drm, "Added new global object %p state %p to %p\n",
		       obj, obj_state, state);

	वापस obj_state;
पूर्ण

काष्ठा पूर्णांकel_global_state *
पूर्णांकel_atomic_get_old_global_obj_state(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_global_obj *obj)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < state->num_global_objs; i++)
		अगर (obj == state->global_objs[i].ptr)
			वापस state->global_objs[i].old_state;

	वापस शून्य;
पूर्ण

काष्ठा पूर्णांकel_global_state *
पूर्णांकel_atomic_get_new_global_obj_state(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_global_obj *obj)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < state->num_global_objs; i++)
		अगर (obj == state->global_objs[i].ptr)
			वापस state->global_objs[i].new_state;

	वापस शून्य;
पूर्ण

व्योम पूर्णांकel_atomic_swap_global_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_global_state *old_obj_state, *new_obj_state;
	काष्ठा पूर्णांकel_global_obj *obj;
	पूर्णांक i;

	क्रम_each_oldnew_global_obj_in_state(state, obj, old_obj_state,
					    new_obj_state, i) अणु
		drm_WARN_ON(&dev_priv->drm, obj->state != old_obj_state);

		/*
		 * If the new state wasn't modअगरied (and properly
		 * locked क्रम ग_लिखो access) we throw it away.
		 */
		अगर (!new_obj_state->changed)
			जारी;

		निश्चित_global_state_ग_लिखो_locked(dev_priv);

		old_obj_state->state = state;
		new_obj_state->state = शून्य;

		state->global_objs[i].state = old_obj_state;

		पूर्णांकel_atomic_global_state_put(obj->state);
		obj->state = पूर्णांकel_atomic_global_state_get(new_obj_state);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_atomic_clear_global_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < state->num_global_objs; i++) अणु
		पूर्णांकel_atomic_global_state_put(state->global_objs[i].old_state);
		पूर्णांकel_atomic_global_state_put(state->global_objs[i].new_state);

		state->global_objs[i].ptr = शून्य;
		state->global_objs[i].state = शून्य;
		state->global_objs[i].old_state = शून्य;
		state->global_objs[i].new_state = शून्य;
	पूर्ण
	state->num_global_objs = 0;
पूर्ण

पूर्णांक पूर्णांकel_atomic_lock_global_state(काष्ठा पूर्णांकel_global_state *obj_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = obj_state->state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		पूर्णांक ret;

		ret = drm_modeset_lock(&crtc->base.mutex,
				       state->base.acquire_ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	obj_state->changed = true;

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_atomic_serialize_global_state(काष्ठा पूर्णांकel_global_state *obj_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = obj_state->state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state;

		crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);
	पूर्ण

	obj_state->changed = true;

	वापस 0;
पूर्ण
