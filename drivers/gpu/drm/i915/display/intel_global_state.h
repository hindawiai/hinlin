<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __INTEL_GLOBAL_STATE_H__
#घोषणा __INTEL_GLOBAL_STATE_H__

#समावेश <linux/kref.h>
#समावेश <linux/list.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_global_obj;
काष्ठा पूर्णांकel_global_state;

काष्ठा पूर्णांकel_global_state_funcs अणु
	काष्ठा पूर्णांकel_global_state *(*atomic_duplicate_state)(काष्ठा पूर्णांकel_global_obj *obj);
	व्योम (*atomic_destroy_state)(काष्ठा पूर्णांकel_global_obj *obj,
				     काष्ठा पूर्णांकel_global_state *state);
पूर्ण;

काष्ठा पूर्णांकel_global_obj अणु
	काष्ठा list_head head;
	काष्ठा पूर्णांकel_global_state *state;
	स्थिर काष्ठा पूर्णांकel_global_state_funcs *funcs;
पूर्ण;

#घोषणा पूर्णांकel_क्रम_each_global_obj(obj, dev_priv) \
	list_क्रम_each_entry(obj, &(dev_priv)->global_obj_list, head)

#घोषणा क्रम_each_new_global_obj_in_state(__state, obj, new_obj_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->num_global_objs && \
		     ((obj) = (__state)->global_objs[__i].ptr, \
		      (new_obj_state) = (__state)->global_objs[__i].new_state, 1); \
	     (__i)++) \
		क्रम_each_अगर(obj)

#घोषणा क्रम_each_old_global_obj_in_state(__state, obj, new_obj_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->num_global_objs && \
		     ((obj) = (__state)->global_objs[__i].ptr, \
		      (new_obj_state) = (__state)->global_objs[__i].old_state, 1); \
	     (__i)++) \
		क्रम_each_अगर(obj)

#घोषणा क्रम_each_oldnew_global_obj_in_state(__state, obj, old_obj_state, new_obj_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->num_global_objs && \
		     ((obj) = (__state)->global_objs[__i].ptr, \
		      (old_obj_state) = (__state)->global_objs[__i].old_state, \
		      (new_obj_state) = (__state)->global_objs[__i].new_state, 1); \
	     (__i)++) \
		क्रम_each_अगर(obj)

काष्ठा पूर्णांकel_global_state अणु
	काष्ठा पूर्णांकel_global_obj *obj;
	काष्ठा पूर्णांकel_atomic_state *state;
	काष्ठा kref ref;
	bool changed;
पूर्ण;

काष्ठा __पूर्णांकel_global_objs_state अणु
	काष्ठा पूर्णांकel_global_obj *ptr;
	काष्ठा पूर्णांकel_global_state *state, *old_state, *new_state;
पूर्ण;

व्योम पूर्णांकel_atomic_global_obj_init(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा पूर्णांकel_global_obj *obj,
				  काष्ठा पूर्णांकel_global_state *state,
				  स्थिर काष्ठा पूर्णांकel_global_state_funcs *funcs);
व्योम पूर्णांकel_atomic_global_obj_cleanup(काष्ठा drm_i915_निजी *dev_priv);

काष्ठा पूर्णांकel_global_state *
पूर्णांकel_atomic_get_global_obj_state(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_global_obj *obj);
काष्ठा पूर्णांकel_global_state *
पूर्णांकel_atomic_get_old_global_obj_state(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_global_obj *obj);
काष्ठा पूर्णांकel_global_state *
पूर्णांकel_atomic_get_new_global_obj_state(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_global_obj *obj);

व्योम पूर्णांकel_atomic_swap_global_state(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_atomic_clear_global_state(काष्ठा पूर्णांकel_atomic_state *state);
पूर्णांक पूर्णांकel_atomic_lock_global_state(काष्ठा पूर्णांकel_global_state *obj_state);
पूर्णांक पूर्णांकel_atomic_serialize_global_state(काष्ठा पूर्णांकel_global_state *obj_state);

#पूर्ण_अगर
