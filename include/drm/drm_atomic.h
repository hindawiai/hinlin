<शैली गुरु>
/*
 * Copyright (C) 2014 Red Hat
 * Copyright (C) 2014 Intel Corp.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Daniel Vetter <daniel.vetter@ffwll.ch>
 */

#अगर_अघोषित DRM_ATOMIC_H_
#घोषणा DRM_ATOMIC_H_

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_util.h>

/**
 * काष्ठा drm_crtc_commit - track modeset commits on a CRTC
 *
 * This काष्ठाure is used to track pending modeset changes and atomic commit on
 * a per-CRTC basis. Since updating the list should never block, this काष्ठाure
 * is reference counted to allow रुकोers to safely रुको on an event to complete,
 * without holding any locks.
 *
 * It has 3 dअगरferent events in total to allow a fine-grained synchronization
 * between outstanding updates::
 *
 *	atomic commit thपढ़ो			hardware
 *
 * 	ग_लिखो new state पूर्णांकo hardware	---->	...
 * 	संकेत hw_करोne
 * 						चयन to new state on next
 * 	...					v/hblank
 *
 *	रुको क्रम buffers to show up		...
 *
 *	...					send completion irq
 *						irq handler संकेतs flip_करोne
 *	cleanup old buffers
 *
 * 	संकेत cleanup_करोne
 *
 * 	रुको क्रम flip_करोne		<----
 * 	clean up atomic state
 *
 * The important bit to know is that &cleanup_करोne is the terminal event, but the
 * ordering between &flip_करोne and &hw_करोne is entirely up to the specअगरic driver
 * and modeset state change.
 *
 * For an implementation of how to use this look at
 * drm_atomic_helper_setup_commit() from the atomic helper library.
 *
 * See also drm_crtc_commit_रुको().
 */
काष्ठा drm_crtc_commit अणु
	/**
	 * @crtc:
	 *
	 * DRM CRTC क्रम this commit.
	 */
	काष्ठा drm_crtc *crtc;

	/**
	 * @ref:
	 *
	 * Reference count क्रम this काष्ठाure. Needed to allow blocking on
	 * completions without the risk of the completion disappearing
	 * meanजबतक.
	 */
	काष्ठा kref ref;

	/**
	 * @flip_करोne:
	 *
	 * Will be संकेतed when the hardware has flipped to the new set of
	 * buffers. Signals at the same समय as when the drm event क्रम this
	 * commit is sent to userspace, or when an out-fence is singalled. Note
	 * that क्रम most hardware, in most हालs this happens after @hw_करोne is
	 * संकेतled.
	 *
	 * Completion of this stage is संकेतled implicitly by calling
	 * drm_crtc_send_vblank_event() on &drm_crtc_state.event.
	 */
	काष्ठा completion flip_करोne;

	/**
	 * @hw_करोne:
	 *
	 * Will be संकेतled when all hw रेजिस्टर changes क्रम this commit have
	 * been written out. Especially when disabling a pipe this can be much
	 * later than @flip_करोne, since that can संकेत alपढ़ोy when the
	 * screen goes black, whereas to fully shut करोwn a pipe more रेजिस्टर
	 * I/O is required.
	 *
	 * Note that this करोes not need to include separately reference-counted
	 * resources like backing storage buffer pinning, or runसमय pm
	 * management.
	 *
	 * Drivers should call drm_atomic_helper_commit_hw_करोne() to संकेत
	 * completion of this stage.
	 */
	काष्ठा completion hw_करोne;

	/**
	 * @cleanup_करोne:
	 *
	 * Will be संकेतled after old buffers have been cleaned up by calling
	 * drm_atomic_helper_cleanup_planes(). Since this can only happen after
	 * a vblank रुको completed it might be a bit later. This completion is
	 * useful to throttle updates and aव्योम hardware updates getting ahead
	 * of the buffer cleanup too much.
	 *
	 * Drivers should call drm_atomic_helper_commit_cleanup_करोne() to संकेत
	 * completion of this stage.
	 */
	काष्ठा completion cleanup_करोne;

	/**
	 * @commit_entry:
	 *
	 * Entry on the per-CRTC &drm_crtc.commit_list. Protected by
	 * $drm_crtc.commit_lock.
	 */
	काष्ठा list_head commit_entry;

	/**
	 * @event:
	 *
	 * &drm_pending_vblank_event poपूर्णांकer to clean up निजी events.
	 */
	काष्ठा drm_pending_vblank_event *event;

	/**
	 * @पात_completion:
	 *
	 * A flag that's set after drm_atomic_helper_setup_commit() takes a
	 * second reference क्रम the completion of $drm_crtc_state.event. It's
	 * used by the मुक्त code to हटाओ the second reference अगर commit fails.
	 */
	bool पात_completion;
पूर्ण;

काष्ठा __drm_planes_state अणु
	काष्ठा drm_plane *ptr;
	काष्ठा drm_plane_state *state, *old_state, *new_state;
पूर्ण;

काष्ठा __drm_crtcs_state अणु
	काष्ठा drm_crtc *ptr;
	काष्ठा drm_crtc_state *state, *old_state, *new_state;

	/**
	 * @commit:
	 *
	 * A reference to the CRTC commit object that is kept क्रम use by
	 * drm_atomic_helper_रुको_क्रम_flip_करोne() after
	 * drm_atomic_helper_commit_hw_करोne() is called. This ensures that a
	 * concurrent commit won't मुक्त a commit object that is still in use.
	 */
	काष्ठा drm_crtc_commit *commit;

	s32 __user *out_fence_ptr;
	u64 last_vblank_count;
पूर्ण;

काष्ठा __drm_connnectors_state अणु
	काष्ठा drm_connector *ptr;
	काष्ठा drm_connector_state *state, *old_state, *new_state;
	/**
	 * @out_fence_ptr:
	 *
	 * User-provided poपूर्णांकer which the kernel uses to वापस a sync_file
	 * file descriptor. Used by ग_लिखोback connectors to संकेत completion of
	 * the ग_लिखोback.
	 */
	s32 __user *out_fence_ptr;
पूर्ण;

काष्ठा drm_निजी_obj;
काष्ठा drm_निजी_state;

/**
 * काष्ठा drm_निजी_state_funcs - atomic state functions क्रम निजी objects
 *
 * These hooks are used by atomic helpers to create, swap and destroy states of
 * निजी objects. The काष्ठाure itself is used as a vtable to identअगरy the
 * associated निजी object type. Each निजी object type that needs to be
 * added to the atomic states is expected to have an implementation of these
 * hooks and pass a poपूर्णांकer to its drm_निजी_state_funcs काष्ठा to
 * drm_atomic_get_निजी_obj_state().
 */
काष्ठा drm_निजी_state_funcs अणु
	/**
	 * @atomic_duplicate_state:
	 *
	 * Duplicate the current state of the निजी object and वापस it. It
	 * is an error to call this beक्रमe obj->state has been initialized.
	 *
	 * RETURNS:
	 *
	 * Duplicated atomic state or शून्य when obj->state is not
	 * initialized or allocation failed.
	 */
	काष्ठा drm_निजी_state *(*atomic_duplicate_state)(काष्ठा drm_निजी_obj *obj);

	/**
	 * @atomic_destroy_state:
	 *
	 * Frees the निजी object state created with @atomic_duplicate_state.
	 */
	व्योम (*atomic_destroy_state)(काष्ठा drm_निजी_obj *obj,
				     काष्ठा drm_निजी_state *state);
पूर्ण;

/**
 * काष्ठा drm_निजी_obj - base काष्ठा क्रम driver निजी atomic object
 *
 * A driver निजी object is initialized by calling
 * drm_atomic_निजी_obj_init() and cleaned up by calling
 * drm_atomic_निजी_obj_fini().
 *
 * Currently only tracks the state update functions and the opaque driver
 * निजी state itself, but in the future might also track which
 * &drm_modeset_lock is required to duplicate and update this object's state.
 *
 * All निजी objects must be initialized beक्रमe the DRM device they are
 * attached to is रेजिस्टरed to the DRM subप्रणाली (call to drm_dev_रेजिस्टर())
 * and should stay around until this DRM device is unरेजिस्टरed (call to
 * drm_dev_unरेजिस्टर()). In other words, निजी objects lअगरeसमय is tied
 * to the DRM device lअगरeसमय. This implies that:
 *
 * 1/ all calls to drm_atomic_निजी_obj_init() must be करोne beक्रमe calling
 *    drm_dev_रेजिस्टर()
 * 2/ all calls to drm_atomic_निजी_obj_fini() must be करोne after calling
 *    drm_dev_unरेजिस्टर()
 *
 * If that निजी object is used to store a state shared by multiple
 * CRTCs, proper care must be taken to ensure that non-blocking commits are
 * properly ordered to aव्योम a use-after-मुक्त issue.
 *
 * Indeed, assuming a sequence of two non-blocking &drm_atomic_commit on two
 * dअगरferent &drm_crtc using dअगरferent &drm_plane and &drm_connector, so with no
 * resources shared, there's no guarantee on which commit is going to happen
 * first. However, the second &drm_atomic_commit will consider the first
 * &drm_निजी_obj its old state, and will be in अक्षरge of मुक्तing it whenever
 * the second &drm_atomic_commit is करोne.
 *
 * If the first &drm_atomic_commit happens after it, it will consider its
 * &drm_निजी_obj the new state and will be likely to access it, resulting in
 * an access to a मुक्तd memory region. Drivers should store (and get a reference
 * to) the &drm_crtc_commit काष्ठाure in our निजी state in
 * &drm_mode_config_helper_funcs.atomic_commit_setup, and then रुको क्रम that
 * commit to complete as the first step of
 * &drm_mode_config_helper_funcs.atomic_commit_tail, similar to
 * drm_atomic_helper_रुको_क्रम_dependencies().
 */
काष्ठा drm_निजी_obj अणु
	/**
	 * @head: List entry used to attach a निजी object to a &drm_device
	 * (queued to &drm_mode_config.privobj_list).
	 */
	काष्ठा list_head head;

	/**
	 * @lock: Modeset lock to protect the state object.
	 */
	काष्ठा drm_modeset_lock lock;

	/**
	 * @state: Current atomic state क्रम this driver निजी object.
	 */
	काष्ठा drm_निजी_state *state;

	/**
	 * @funcs:
	 *
	 * Functions to manipulate the state of this driver निजी object, see
	 * &drm_निजी_state_funcs.
	 */
	स्थिर काष्ठा drm_निजी_state_funcs *funcs;
पूर्ण;

/**
 * drm_क्रम_each_privobj() - निजी object iterator
 *
 * @privobj: poपूर्णांकer to the current निजी object. Updated after each
 *	     iteration
 * @dev: the DRM device we want get निजी objects from
 *
 * Allows one to iterate over all निजी objects attached to @dev
 */
#घोषणा drm_क्रम_each_privobj(privobj, dev) \
	list_क्रम_each_entry(privobj, &(dev)->mode_config.privobj_list, head)

/**
 * काष्ठा drm_निजी_state - base काष्ठा क्रम driver निजी object state
 * @state: backpoपूर्णांकer to global drm_atomic_state
 *
 * Currently only contains a backpoपूर्णांकer to the overall atomic update, but in
 * the future also might hold synchronization inक्रमmation similar to e.g.
 * &drm_crtc.commit.
 */
काष्ठा drm_निजी_state अणु
	काष्ठा drm_atomic_state *state;
पूर्ण;

काष्ठा __drm_निजी_objs_state अणु
	काष्ठा drm_निजी_obj *ptr;
	काष्ठा drm_निजी_state *state, *old_state, *new_state;
पूर्ण;

/**
 * काष्ठा drm_atomic_state - the global state object क्रम atomic updates
 * @ref: count of all references to this state (will not be मुक्तd until zero)
 * @dev: parent DRM device
 * @async_update: hपूर्णांक क्रम asynchronous plane update
 * @planes: poपूर्णांकer to array of काष्ठाures with per-plane data
 * @crtcs: poपूर्णांकer to array of CRTC poपूर्णांकers
 * @num_connector: size of the @connectors and @connector_states arrays
 * @connectors: poपूर्णांकer to array of काष्ठाures with per-connector data
 * @num_निजी_objs: size of the @निजी_objs array
 * @निजी_objs: poपूर्णांकer to array of निजी object poपूर्णांकers
 * @acquire_ctx: acquire context क्रम this atomic modeset state update
 *
 * States are added to an atomic update by calling drm_atomic_get_crtc_state(),
 * drm_atomic_get_plane_state(), drm_atomic_get_connector_state(), or क्रम
 * निजी state काष्ठाures, drm_atomic_get_निजी_obj_state().
 */
काष्ठा drm_atomic_state अणु
	काष्ठा kref ref;

	काष्ठा drm_device *dev;

	/**
	 * @allow_modeset:
	 *
	 * Allow full modeset. This is used by the ATOMIC IOCTL handler to
	 * implement the DRM_MODE_ATOMIC_ALLOW_MODESET flag. Drivers should
	 * never consult this flag, instead looking at the output of
	 * drm_atomic_crtc_needs_modeset().
	 */
	bool allow_modeset : 1;
	/**
	 * @legacy_cursor_update:
	 *
	 * Hपूर्णांक to enक्रमce legacy cursor IOCTL semantics.
	 *
	 * WARNING: This is thoroughly broken and pretty much impossible to
	 * implement correctly. Drivers must ignore this and should instead
	 * implement &drm_plane_helper_funcs.atomic_async_check and
	 * &drm_plane_helper_funcs.atomic_async_commit hooks. New users of this
	 * flag are not allowed.
	 */
	bool legacy_cursor_update : 1;
	bool async_update : 1;
	/**
	 * @duplicated:
	 *
	 * Indicates whether or not this atomic state was duplicated using
	 * drm_atomic_helper_duplicate_state(). Drivers and atomic helpers
	 * should use this to fixup normal  inconsistencies in duplicated
	 * states.
	 */
	bool duplicated : 1;
	काष्ठा __drm_planes_state *planes;
	काष्ठा __drm_crtcs_state *crtcs;
	पूर्णांक num_connector;
	काष्ठा __drm_connnectors_state *connectors;
	पूर्णांक num_निजी_objs;
	काष्ठा __drm_निजी_objs_state *निजी_objs;

	काष्ठा drm_modeset_acquire_ctx *acquire_ctx;

	/**
	 * @fake_commit:
	 *
	 * Used क्रम संकेतing unbound planes/connectors.
	 * When a connector or plane is not bound to any CRTC, it's still important
	 * to preserve linearity to prevent the atomic states from being मुक्तd to early.
	 *
	 * This commit (अगर set) is not bound to any CRTC, but will be completed when
	 * drm_atomic_helper_commit_hw_करोne() is called.
	 */
	काष्ठा drm_crtc_commit *fake_commit;

	/**
	 * @commit_work:
	 *
	 * Work item which can be used by the driver or helpers to execute the
	 * commit without blocking.
	 */
	काष्ठा work_काष्ठा commit_work;
पूर्ण;

व्योम __drm_crtc_commit_मुक्त(काष्ठा kref *kref);

/**
 * drm_crtc_commit_get - acquire a reference to the CRTC commit
 * @commit: CRTC commit
 *
 * Increases the reference of @commit.
 *
 * Returns:
 * The poपूर्णांकer to @commit, with reference increased.
 */
अटल अंतरभूत काष्ठा drm_crtc_commit *drm_crtc_commit_get(काष्ठा drm_crtc_commit *commit)
अणु
	kref_get(&commit->ref);
	वापस commit;
पूर्ण

/**
 * drm_crtc_commit_put - release a reference to the CRTC commmit
 * @commit: CRTC commit
 *
 * This releases a reference to @commit which is मुक्तd after removing the
 * final reference. No locking required and callable from any context.
 */
अटल अंतरभूत व्योम drm_crtc_commit_put(काष्ठा drm_crtc_commit *commit)
अणु
	kref_put(&commit->ref, __drm_crtc_commit_मुक्त);
पूर्ण

पूर्णांक drm_crtc_commit_रुको(काष्ठा drm_crtc_commit *commit);

काष्ठा drm_atomic_state * __must_check
drm_atomic_state_alloc(काष्ठा drm_device *dev);
व्योम drm_atomic_state_clear(काष्ठा drm_atomic_state *state);

/**
 * drm_atomic_state_get - acquire a reference to the atomic state
 * @state: The atomic state
 *
 * Returns a new reference to the @state
 */
अटल अंतरभूत काष्ठा drm_atomic_state *
drm_atomic_state_get(काष्ठा drm_atomic_state *state)
अणु
	kref_get(&state->ref);
	वापस state;
पूर्ण

व्योम __drm_atomic_state_मुक्त(काष्ठा kref *ref);

/**
 * drm_atomic_state_put - release a reference to the atomic state
 * @state: The atomic state
 *
 * This releases a reference to @state which is मुक्तd after removing the
 * final reference. No locking required and callable from any context.
 */
अटल अंतरभूत व्योम drm_atomic_state_put(काष्ठा drm_atomic_state *state)
अणु
	kref_put(&state->ref, __drm_atomic_state_मुक्त);
पूर्ण

पूर्णांक  __must_check
drm_atomic_state_init(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *state);
व्योम drm_atomic_state_शेष_clear(काष्ठा drm_atomic_state *state);
व्योम drm_atomic_state_शेष_release(काष्ठा drm_atomic_state *state);

काष्ठा drm_crtc_state * __must_check
drm_atomic_get_crtc_state(काष्ठा drm_atomic_state *state,
			  काष्ठा drm_crtc *crtc);
काष्ठा drm_plane_state * __must_check
drm_atomic_get_plane_state(काष्ठा drm_atomic_state *state,
			   काष्ठा drm_plane *plane);
काष्ठा drm_connector_state * __must_check
drm_atomic_get_connector_state(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_connector *connector);

व्योम drm_atomic_निजी_obj_init(काष्ठा drm_device *dev,
				 काष्ठा drm_निजी_obj *obj,
				 काष्ठा drm_निजी_state *state,
				 स्थिर काष्ठा drm_निजी_state_funcs *funcs);
व्योम drm_atomic_निजी_obj_fini(काष्ठा drm_निजी_obj *obj);

काष्ठा drm_निजी_state * __must_check
drm_atomic_get_निजी_obj_state(काष्ठा drm_atomic_state *state,
				 काष्ठा drm_निजी_obj *obj);
काष्ठा drm_निजी_state *
drm_atomic_get_old_निजी_obj_state(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_निजी_obj *obj);
काष्ठा drm_निजी_state *
drm_atomic_get_new_निजी_obj_state(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_निजी_obj *obj);

काष्ठा drm_connector *
drm_atomic_get_old_connector_क्रम_encoder(काष्ठा drm_atomic_state *state,
					 काष्ठा drm_encoder *encoder);
काष्ठा drm_connector *
drm_atomic_get_new_connector_क्रम_encoder(काष्ठा drm_atomic_state *state,
					 काष्ठा drm_encoder *encoder);

/**
 * drm_atomic_get_existing_crtc_state - get CRTC state, अगर it exists
 * @state: global atomic state object
 * @crtc: CRTC to grab
 *
 * This function वापसs the CRTC state क्रम the given CRTC, or शून्य
 * अगर the CRTC is not part of the global atomic state.
 *
 * This function is deprecated, @drm_atomic_get_old_crtc_state or
 * @drm_atomic_get_new_crtc_state should be used instead.
 */
अटल अंतरभूत काष्ठा drm_crtc_state *
drm_atomic_get_existing_crtc_state(काष्ठा drm_atomic_state *state,
				   काष्ठा drm_crtc *crtc)
अणु
	वापस state->crtcs[drm_crtc_index(crtc)].state;
पूर्ण

/**
 * drm_atomic_get_old_crtc_state - get old CRTC state, अगर it exists
 * @state: global atomic state object
 * @crtc: CRTC to grab
 *
 * This function वापसs the old CRTC state क्रम the given CRTC, or
 * शून्य अगर the CRTC is not part of the global atomic state.
 */
अटल अंतरभूत काष्ठा drm_crtc_state *
drm_atomic_get_old_crtc_state(काष्ठा drm_atomic_state *state,
			      काष्ठा drm_crtc *crtc)
अणु
	वापस state->crtcs[drm_crtc_index(crtc)].old_state;
पूर्ण
/**
 * drm_atomic_get_new_crtc_state - get new CRTC state, अगर it exists
 * @state: global atomic state object
 * @crtc: CRTC to grab
 *
 * This function वापसs the new CRTC state क्रम the given CRTC, or
 * शून्य अगर the CRTC is not part of the global atomic state.
 */
अटल अंतरभूत काष्ठा drm_crtc_state *
drm_atomic_get_new_crtc_state(काष्ठा drm_atomic_state *state,
			      काष्ठा drm_crtc *crtc)
अणु
	वापस state->crtcs[drm_crtc_index(crtc)].new_state;
पूर्ण

/**
 * drm_atomic_get_existing_plane_state - get plane state, अगर it exists
 * @state: global atomic state object
 * @plane: plane to grab
 *
 * This function वापसs the plane state क्रम the given plane, or शून्य
 * अगर the plane is not part of the global atomic state.
 *
 * This function is deprecated, @drm_atomic_get_old_plane_state or
 * @drm_atomic_get_new_plane_state should be used instead.
 */
अटल अंतरभूत काष्ठा drm_plane_state *
drm_atomic_get_existing_plane_state(काष्ठा drm_atomic_state *state,
				    काष्ठा drm_plane *plane)
अणु
	वापस state->planes[drm_plane_index(plane)].state;
पूर्ण

/**
 * drm_atomic_get_old_plane_state - get plane state, अगर it exists
 * @state: global atomic state object
 * @plane: plane to grab
 *
 * This function वापसs the old plane state क्रम the given plane, or
 * शून्य अगर the plane is not part of the global atomic state.
 */
अटल अंतरभूत काष्ठा drm_plane_state *
drm_atomic_get_old_plane_state(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_plane *plane)
अणु
	वापस state->planes[drm_plane_index(plane)].old_state;
पूर्ण

/**
 * drm_atomic_get_new_plane_state - get plane state, अगर it exists
 * @state: global atomic state object
 * @plane: plane to grab
 *
 * This function वापसs the new plane state क्रम the given plane, or
 * शून्य अगर the plane is not part of the global atomic state.
 */
अटल अंतरभूत काष्ठा drm_plane_state *
drm_atomic_get_new_plane_state(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_plane *plane)
अणु
	वापस state->planes[drm_plane_index(plane)].new_state;
पूर्ण

/**
 * drm_atomic_get_existing_connector_state - get connector state, अगर it exists
 * @state: global atomic state object
 * @connector: connector to grab
 *
 * This function वापसs the connector state क्रम the given connector,
 * or शून्य अगर the connector is not part of the global atomic state.
 *
 * This function is deprecated, @drm_atomic_get_old_connector_state or
 * @drm_atomic_get_new_connector_state should be used instead.
 */
अटल अंतरभूत काष्ठा drm_connector_state *
drm_atomic_get_existing_connector_state(काष्ठा drm_atomic_state *state,
					काष्ठा drm_connector *connector)
अणु
	पूर्णांक index = drm_connector_index(connector);

	अगर (index >= state->num_connector)
		वापस शून्य;

	वापस state->connectors[index].state;
पूर्ण

/**
 * drm_atomic_get_old_connector_state - get connector state, अगर it exists
 * @state: global atomic state object
 * @connector: connector to grab
 *
 * This function वापसs the old connector state क्रम the given connector,
 * or शून्य अगर the connector is not part of the global atomic state.
 */
अटल अंतरभूत काष्ठा drm_connector_state *
drm_atomic_get_old_connector_state(काष्ठा drm_atomic_state *state,
				   काष्ठा drm_connector *connector)
अणु
	पूर्णांक index = drm_connector_index(connector);

	अगर (index >= state->num_connector)
		वापस शून्य;

	वापस state->connectors[index].old_state;
पूर्ण

/**
 * drm_atomic_get_new_connector_state - get connector state, अगर it exists
 * @state: global atomic state object
 * @connector: connector to grab
 *
 * This function वापसs the new connector state क्रम the given connector,
 * or शून्य अगर the connector is not part of the global atomic state.
 */
अटल अंतरभूत काष्ठा drm_connector_state *
drm_atomic_get_new_connector_state(काष्ठा drm_atomic_state *state,
				   काष्ठा drm_connector *connector)
अणु
	पूर्णांक index = drm_connector_index(connector);

	अगर (index >= state->num_connector)
		वापस शून्य;

	वापस state->connectors[index].new_state;
पूर्ण

/**
 * __drm_atomic_get_current_plane_state - get current plane state
 * @state: global atomic state object
 * @plane: plane to grab
 *
 * This function वापसs the plane state क्रम the given plane, either from
 * @state, or अगर the plane isn't part of the atomic state update, from @plane.
 * This is useful in atomic check callbacks, when drivers need to peek at, but
 * not change, state of other planes, since it aव्योमs thपढ़ोing an error code
 * back up the call chain.
 *
 * WARNING:
 *
 * Note that this function is in general unsafe since it करोesn't check क्रम the
 * required locking क्रम access state काष्ठाures. Drivers must ensure that it is
 * safe to access the वापसed state काष्ठाure through other means. One common
 * example is when planes are fixed to a single CRTC, and the driver knows that
 * the CRTC lock is held alपढ़ोy. In that हाल holding the CRTC lock gives a
 * पढ़ो-lock on all planes connected to that CRTC. But अगर planes can be
 * reasचिन्हित things get more tricky. In that हाल it's better to use
 * drm_atomic_get_plane_state and wire up full error handling.
 *
 * Returns:
 *
 * Read-only poपूर्णांकer to the current plane state.
 */
अटल अंतरभूत स्थिर काष्ठा drm_plane_state *
__drm_atomic_get_current_plane_state(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_plane *plane)
अणु
	अगर (state->planes[drm_plane_index(plane)].state)
		वापस state->planes[drm_plane_index(plane)].state;

	वापस plane->state;
पूर्ण

पूर्णांक __must_check
drm_atomic_add_encoder_bridges(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_encoder *encoder);
पूर्णांक __must_check
drm_atomic_add_affected_connectors(काष्ठा drm_atomic_state *state,
				   काष्ठा drm_crtc *crtc);
पूर्णांक __must_check
drm_atomic_add_affected_planes(काष्ठा drm_atomic_state *state,
			       काष्ठा drm_crtc *crtc);

पूर्णांक __must_check drm_atomic_check_only(काष्ठा drm_atomic_state *state);
पूर्णांक __must_check drm_atomic_commit(काष्ठा drm_atomic_state *state);
पूर्णांक __must_check drm_atomic_nonblocking_commit(काष्ठा drm_atomic_state *state);

व्योम drm_state_dump(काष्ठा drm_device *dev, काष्ठा drm_prपूर्णांकer *p);

/**
 * क्रम_each_oldnew_connector_in_state - iterate over all connectors in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @connector: &काष्ठा drm_connector iteration cursor
 * @old_connector_state: &काष्ठा drm_connector_state iteration cursor क्रम the
 * 	old state
 * @new_connector_state: &काष्ठा drm_connector_state iteration cursor क्रम the
 * 	new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all connectors in an atomic update, tracking both old and
 * new state. This is useful in places where the state delta needs to be
 * considered, क्रम example in atomic check functions.
 */
#घोषणा क्रम_each_oldnew_connector_in_state(__state, connector, old_connector_state, new_connector_state, __i) \
	क्रम ((__i) = 0;								\
	     (__i) < (__state)->num_connector;					\
	     (__i)++)								\
		क्रम_each_अगर ((__state)->connectors[__i].ptr &&			\
			     ((connector) = (__state)->connectors[__i].ptr,	\
			     (व्योम)(connector) /* Only to aव्योम unused-but-set-variable warning */, \
			     (old_connector_state) = (__state)->connectors[__i].old_state,	\
			     (new_connector_state) = (__state)->connectors[__i].new_state, 1))

/**
 * क्रम_each_old_connector_in_state - iterate over all connectors in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @connector: &काष्ठा drm_connector iteration cursor
 * @old_connector_state: &काष्ठा drm_connector_state iteration cursor क्रम the
 * 	old state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all connectors in an atomic update, tracking only the old
 * state. This is useful in disable functions, where we need the old state the
 * hardware is still in.
 */
#घोषणा क्रम_each_old_connector_in_state(__state, connector, old_connector_state, __i) \
	क्रम ((__i) = 0;								\
	     (__i) < (__state)->num_connector;					\
	     (__i)++)								\
		क्रम_each_अगर ((__state)->connectors[__i].ptr &&			\
			     ((connector) = (__state)->connectors[__i].ptr,	\
			     (व्योम)(connector) /* Only to aव्योम unused-but-set-variable warning */, \
			     (old_connector_state) = (__state)->connectors[__i].old_state, 1))

/**
 * क्रम_each_new_connector_in_state - iterate over all connectors in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @connector: &काष्ठा drm_connector iteration cursor
 * @new_connector_state: &काष्ठा drm_connector_state iteration cursor क्रम the
 * 	new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all connectors in an atomic update, tracking only the new
 * state. This is useful in enable functions, where we need the new state the
 * hardware should be in when the atomic commit operation has completed.
 */
#घोषणा क्रम_each_new_connector_in_state(__state, connector, new_connector_state, __i) \
	क्रम ((__i) = 0;								\
	     (__i) < (__state)->num_connector;					\
	     (__i)++)								\
		क्रम_each_अगर ((__state)->connectors[__i].ptr &&			\
			     ((connector) = (__state)->connectors[__i].ptr,	\
			     (व्योम)(connector) /* Only to aव्योम unused-but-set-variable warning */, \
			     (new_connector_state) = (__state)->connectors[__i].new_state, \
			     (व्योम)(new_connector_state) /* Only to aव्योम unused-but-set-variable warning */, 1))

/**
 * क्रम_each_oldnew_crtc_in_state - iterate over all CRTCs in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @crtc: &काष्ठा drm_crtc iteration cursor
 * @old_crtc_state: &काष्ठा drm_crtc_state iteration cursor क्रम the old state
 * @new_crtc_state: &काष्ठा drm_crtc_state iteration cursor क्रम the new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all CRTCs in an atomic update, tracking both old and
 * new state. This is useful in places where the state delta needs to be
 * considered, क्रम example in atomic check functions.
 */
#घोषणा क्रम_each_oldnew_crtc_in_state(__state, crtc, old_crtc_state, new_crtc_state, __i) \
	क्रम ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_crtc;		\
	     (__i)++)							\
		क्रम_each_अगर ((__state)->crtcs[__i].ptr &&		\
			     ((crtc) = (__state)->crtcs[__i].ptr,	\
			      (व्योम)(crtc) /* Only to aव्योम unused-but-set-variable warning */, \
			     (old_crtc_state) = (__state)->crtcs[__i].old_state, \
			     (व्योम)(old_crtc_state) /* Only to aव्योम unused-but-set-variable warning */, \
			     (new_crtc_state) = (__state)->crtcs[__i].new_state, \
			     (व्योम)(new_crtc_state) /* Only to aव्योम unused-but-set-variable warning */, 1))

/**
 * क्रम_each_old_crtc_in_state - iterate over all CRTCs in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @crtc: &काष्ठा drm_crtc iteration cursor
 * @old_crtc_state: &काष्ठा drm_crtc_state iteration cursor क्रम the old state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all CRTCs in an atomic update, tracking only the old
 * state. This is useful in disable functions, where we need the old state the
 * hardware is still in.
 */
#घोषणा क्रम_each_old_crtc_in_state(__state, crtc, old_crtc_state, __i)	\
	क्रम ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_crtc;		\
	     (__i)++)							\
		क्रम_each_अगर ((__state)->crtcs[__i].ptr &&		\
			     ((crtc) = (__state)->crtcs[__i].ptr,	\
			     (व्योम)(crtc) /* Only to aव्योम unused-but-set-variable warning */, \
			     (old_crtc_state) = (__state)->crtcs[__i].old_state, 1))

/**
 * क्रम_each_new_crtc_in_state - iterate over all CRTCs in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @crtc: &काष्ठा drm_crtc iteration cursor
 * @new_crtc_state: &काष्ठा drm_crtc_state iteration cursor क्रम the new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all CRTCs in an atomic update, tracking only the new
 * state. This is useful in enable functions, where we need the new state the
 * hardware should be in when the atomic commit operation has completed.
 */
#घोषणा क्रम_each_new_crtc_in_state(__state, crtc, new_crtc_state, __i)	\
	क्रम ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_crtc;		\
	     (__i)++)							\
		क्रम_each_अगर ((__state)->crtcs[__i].ptr &&		\
			     ((crtc) = (__state)->crtcs[__i].ptr,	\
			     (व्योम)(crtc) /* Only to aव्योम unused-but-set-variable warning */, \
			     (new_crtc_state) = (__state)->crtcs[__i].new_state, \
			     (व्योम)(new_crtc_state) /* Only to aव्योम unused-but-set-variable warning */, 1))

/**
 * क्रम_each_oldnew_plane_in_state - iterate over all planes in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @plane: &काष्ठा drm_plane iteration cursor
 * @old_plane_state: &काष्ठा drm_plane_state iteration cursor क्रम the old state
 * @new_plane_state: &काष्ठा drm_plane_state iteration cursor क्रम the new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all planes in an atomic update, tracking both old and
 * new state. This is useful in places where the state delta needs to be
 * considered, क्रम example in atomic check functions.
 */
#घोषणा क्रम_each_oldnew_plane_in_state(__state, plane, old_plane_state, new_plane_state, __i) \
	क्रम ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_total_plane;	\
	     (__i)++)							\
		क्रम_each_अगर ((__state)->planes[__i].ptr &&		\
			     ((plane) = (__state)->planes[__i].ptr,	\
			      (व्योम)(plane) /* Only to aव्योम unused-but-set-variable warning */, \
			      (old_plane_state) = (__state)->planes[__i].old_state,\
			      (new_plane_state) = (__state)->planes[__i].new_state, 1))

/**
 * क्रम_each_oldnew_plane_in_state_reverse - iterate over all planes in an atomic
 * update in reverse order
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @plane: &काष्ठा drm_plane iteration cursor
 * @old_plane_state: &काष्ठा drm_plane_state iteration cursor क्रम the old state
 * @new_plane_state: &काष्ठा drm_plane_state iteration cursor क्रम the new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all planes in an atomic update in reverse order,
 * tracking both old and  new state. This is useful in places where the
 * state delta needs to be considered, क्रम example in atomic check functions.
 */
#घोषणा क्रम_each_oldnew_plane_in_state_reverse(__state, plane, old_plane_state, new_plane_state, __i) \
	क्रम ((__i) = ((__state)->dev->mode_config.num_total_plane - 1);	\
	     (__i) >= 0;						\
	     (__i)--)							\
		क्रम_each_अगर ((__state)->planes[__i].ptr &&		\
			     ((plane) = (__state)->planes[__i].ptr,	\
			      (old_plane_state) = (__state)->planes[__i].old_state,\
			      (new_plane_state) = (__state)->planes[__i].new_state, 1))

/**
 * क्रम_each_old_plane_in_state - iterate over all planes in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @plane: &काष्ठा drm_plane iteration cursor
 * @old_plane_state: &काष्ठा drm_plane_state iteration cursor क्रम the old state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all planes in an atomic update, tracking only the old
 * state. This is useful in disable functions, where we need the old state the
 * hardware is still in.
 */
#घोषणा क्रम_each_old_plane_in_state(__state, plane, old_plane_state, __i) \
	क्रम ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_total_plane;	\
	     (__i)++)							\
		क्रम_each_अगर ((__state)->planes[__i].ptr &&		\
			     ((plane) = (__state)->planes[__i].ptr,	\
			      (old_plane_state) = (__state)->planes[__i].old_state, 1))
/**
 * क्रम_each_new_plane_in_state - iterate over all planes in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @plane: &काष्ठा drm_plane iteration cursor
 * @new_plane_state: &काष्ठा drm_plane_state iteration cursor क्रम the new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all planes in an atomic update, tracking only the new
 * state. This is useful in enable functions, where we need the new state the
 * hardware should be in when the atomic commit operation has completed.
 */
#घोषणा क्रम_each_new_plane_in_state(__state, plane, new_plane_state, __i) \
	क्रम ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_total_plane;	\
	     (__i)++)							\
		क्रम_each_अगर ((__state)->planes[__i].ptr &&		\
			     ((plane) = (__state)->planes[__i].ptr,	\
			      (व्योम)(plane) /* Only to aव्योम unused-but-set-variable warning */, \
			      (new_plane_state) = (__state)->planes[__i].new_state, \
			      (व्योम)(new_plane_state) /* Only to aव्योम unused-but-set-variable warning */, 1))

/**
 * क्रम_each_oldnew_निजी_obj_in_state - iterate over all निजी objects in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @obj: &काष्ठा drm_निजी_obj iteration cursor
 * @old_obj_state: &काष्ठा drm_निजी_state iteration cursor क्रम the old state
 * @new_obj_state: &काष्ठा drm_निजी_state iteration cursor क्रम the new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all निजी objects in an atomic update, tracking both
 * old and new state. This is useful in places where the state delta needs
 * to be considered, क्रम example in atomic check functions.
 */
#घोषणा क्रम_each_oldnew_निजी_obj_in_state(__state, obj, old_obj_state, new_obj_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->num_निजी_objs && \
		     ((obj) = (__state)->निजी_objs[__i].ptr, \
		      (old_obj_state) = (__state)->निजी_objs[__i].old_state,	\
		      (new_obj_state) = (__state)->निजी_objs[__i].new_state, 1); \
	     (__i)++)

/**
 * क्रम_each_old_निजी_obj_in_state - iterate over all निजी objects in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @obj: &काष्ठा drm_निजी_obj iteration cursor
 * @old_obj_state: &काष्ठा drm_निजी_state iteration cursor क्रम the old state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all निजी objects in an atomic update, tracking only
 * the old state. This is useful in disable functions, where we need the old
 * state the hardware is still in.
 */
#घोषणा क्रम_each_old_निजी_obj_in_state(__state, obj, old_obj_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->num_निजी_objs && \
		     ((obj) = (__state)->निजी_objs[__i].ptr, \
		      (old_obj_state) = (__state)->निजी_objs[__i].old_state, 1); \
	     (__i)++)

/**
 * क्रम_each_new_निजी_obj_in_state - iterate over all निजी objects in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @obj: &काष्ठा drm_निजी_obj iteration cursor
 * @new_obj_state: &काष्ठा drm_निजी_state iteration cursor क्रम the new state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all निजी objects in an atomic update, tracking only
 * the new state. This is useful in enable functions, where we need the new state the
 * hardware should be in when the atomic commit operation has completed.
 */
#घोषणा क्रम_each_new_निजी_obj_in_state(__state, obj, new_obj_state, __i) \
	क्रम ((__i) = 0; \
	     (__i) < (__state)->num_निजी_objs && \
		     ((obj) = (__state)->निजी_objs[__i].ptr, \
		      (new_obj_state) = (__state)->निजी_objs[__i].new_state, 1); \
	     (__i)++)

/**
 * drm_atomic_crtc_needs_modeset - compute combined modeset need
 * @state: &drm_crtc_state क्रम the CRTC
 *
 * To give drivers flexibility &काष्ठा drm_crtc_state has 3 booleans to track
 * whether the state CRTC changed enough to need a full modeset cycle:
 * mode_changed, active_changed and connectors_changed. This helper simply
 * combines these three to compute the overall need क्रम a modeset क्रम @state.
 *
 * The atomic helper code sets these booleans, but drivers can and should
 * change them appropriately to accurately represent whether a modeset is
 * really needed. In general, drivers should aव्योम full modesets whenever
 * possible.
 *
 * For example अगर the CRTC mode has changed, and the hardware is able to enact
 * the requested mode change without going through a full modeset, the driver
 * should clear mode_changed in its &drm_mode_config_funcs.atomic_check
 * implementation.
 */
अटल अंतरभूत bool
drm_atomic_crtc_needs_modeset(स्थिर काष्ठा drm_crtc_state *state)
अणु
	वापस state->mode_changed || state->active_changed ||
	       state->connectors_changed;
पूर्ण

/**
 * drm_atomic_crtc_effectively_active - compute whether CRTC is actually active
 * @state: &drm_crtc_state क्रम the CRTC
 *
 * When in self refresh mode, the crtc_state->active value will be false, since
 * the CRTC is off. However in some हालs we're पूर्णांकerested in whether the CRTC
 * is active, or effectively active (ie: it's connected to an active display).
 * In these हालs, use this function instead of just checking active.
 */
अटल अंतरभूत bool
drm_atomic_crtc_effectively_active(स्थिर काष्ठा drm_crtc_state *state)
अणु
	वापस state->active || state->self_refresh_active;
पूर्ण

/**
 * काष्ठा drm_bus_cfg - bus configuration
 *
 * This काष्ठाure stores the configuration of a physical bus between two
 * components in an output pipeline, usually between two bridges, an encoder
 * and a bridge, or a bridge and a connector.
 *
 * The bus configuration is stored in &drm_bridge_state separately क्रम the
 * input and output buses, as seen from the poपूर्णांक of view of each bridge. The
 * bus configuration of a bridge output is usually identical to the
 * configuration of the next bridge's input, but may dअगरfer अगर the संकेतs are
 * modअगरied between the two bridges, क्रम instance by an inverter on the board.
 * The input and output configurations of a bridge may dअगरfer अगर the bridge
 * modअगरies the संकेतs पूर्णांकernally, क्रम instance by perक्रमming क्रमmat
 * conversion, or modअगरying संकेतs polarities.
 */
काष्ठा drm_bus_cfg अणु
	/**
	 * @क्रमmat: क्रमmat used on this bus (one of the MEDIA_BUS_FMT_* क्रमmat)
	 *
	 * This field should not be directly modअगरied by drivers
	 * (drm_atomic_bridge_chain_select_bus_fmts() takes care of the bus
	 * क्रमmat negotiation).
	 */
	u32 क्रमmat;

	/**
	 * @flags: DRM_BUS_* flags used on this bus
	 */
	u32 flags;
पूर्ण;

/**
 * काष्ठा drm_bridge_state - Atomic bridge state object
 */
काष्ठा drm_bridge_state अणु
	/**
	 * @base: inherit from &drm_निजी_state
	 */
	काष्ठा drm_निजी_state base;

	/**
	 * @bridge: the bridge this state refers to
	 */
	काष्ठा drm_bridge *bridge;

	/**
	 * @input_bus_cfg: input bus configuration
	 */
	काष्ठा drm_bus_cfg input_bus_cfg;

	/**
	 * @output_bus_cfg: input bus configuration
	 */
	काष्ठा drm_bus_cfg output_bus_cfg;
पूर्ण;

अटल अंतरभूत काष्ठा drm_bridge_state *
drm_priv_to_bridge_state(काष्ठा drm_निजी_state *priv)
अणु
	वापस container_of(priv, काष्ठा drm_bridge_state, base);
पूर्ण

काष्ठा drm_bridge_state *
drm_atomic_get_bridge_state(काष्ठा drm_atomic_state *state,
			    काष्ठा drm_bridge *bridge);
काष्ठा drm_bridge_state *
drm_atomic_get_old_bridge_state(काष्ठा drm_atomic_state *state,
				काष्ठा drm_bridge *bridge);
काष्ठा drm_bridge_state *
drm_atomic_get_new_bridge_state(काष्ठा drm_atomic_state *state,
				काष्ठा drm_bridge *bridge);

#पूर्ण_अगर /* DRM_ATOMIC_H_ */
