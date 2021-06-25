<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित __DRM_MODE_CONFIG_H__
#घोषणा __DRM_MODE_CONFIG_H__

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/idr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/llist.h>

#समावेश <drm/drm_modeset_lock.h>

काष्ठा drm_file;
काष्ठा drm_device;
काष्ठा drm_atomic_state;
काष्ठा drm_mode_fb_cmd2;
काष्ठा drm_क्रमmat_info;
काष्ठा drm_display_mode;

/**
 * काष्ठा drm_mode_config_funcs - basic driver provided mode setting functions
 *
 * Some global (i.e. not per-CRTC, connector, etc) mode setting functions that
 * involve drivers.
 */
काष्ठा drm_mode_config_funcs अणु
	/**
	 * @fb_create:
	 *
	 * Create a new framebuffer object. The core करोes basic checks on the
	 * requested metadata, but most of that is left to the driver. See
	 * &काष्ठा drm_mode_fb_cmd2 क्रम details.
	 *
	 * To validate the pixel क्रमmat and modअगरier drivers can use
	 * drm_any_plane_has_क्रमmat() to make sure at least one plane supports
	 * the requested values. Note that the driver must first determine the
	 * actual modअगरier used अगर the request करोesn't have it specअगरied,
	 * ie. when (@mode_cmd->flags & DRM_MODE_FB_MODIFIERS) == 0.
	 *
	 * IMPORTANT: These implied modअगरiers क्रम legacy userspace must be
	 * stored in काष्ठा &drm_framebuffer, including all relevant metadata
	 * like &drm_framebuffer.pitches and &drm_framebuffer.offsets अगर the
	 * modअगरier enables additional planes beyond the fourcc pixel क्रमmat
	 * code. This is required by the GETFB2 ioctl.
	 *
	 * If the parameters are deemed valid and the backing storage objects in
	 * the underlying memory manager all exist, then the driver allocates
	 * a new &drm_framebuffer काष्ठाure, subclassed to contain
	 * driver-specअगरic inक्रमmation (like the पूर्णांकernal native buffer object
	 * references). It also needs to fill out all relevant metadata, which
	 * should be करोne by calling drm_helper_mode_fill_fb_काष्ठा().
	 *
	 * The initialization is finalized by calling drm_framebuffer_init(),
	 * which रेजिस्टरs the framebuffer and makes it accessible to other
	 * thपढ़ोs.
	 *
	 * RETURNS:
	 *
	 * A new framebuffer with an initial reference count of 1 or a negative
	 * error code encoded with ERR_PTR().
	 */
	काष्ठा drm_framebuffer *(*fb_create)(काष्ठा drm_device *dev,
					     काष्ठा drm_file *file_priv,
					     स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);

	/**
	 * @get_क्रमmat_info:
	 *
	 * Allows a driver to वापस custom क्रमmat inक्रमmation क्रम special
	 * fb layouts (eg. ones with auxiliary compression control planes).
	 *
	 * RETURNS:
	 *
	 * The क्रमmat inक्रमmation specअगरic to the given fb metadata, or
	 * शून्य अगर none is found.
	 */
	स्थिर काष्ठा drm_क्रमmat_info *(*get_क्रमmat_info)(स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);

	/**
	 * @output_poll_changed:
	 *
	 * Callback used by helpers to inक्रमm the driver of output configuration
	 * changes.
	 *
	 * Drivers implementing fbdev emulation with the helpers can call
	 * drm_fb_helper_hotplug_changed from this hook to inक्रमm the fbdev
	 * helper of output changes.
	 *
	 * FIXME:
	 *
	 * Except that there's no vtable क्रम device-level helper callbacks
	 * there's no reason this is a core function.
	 */
	व्योम (*output_poll_changed)(काष्ठा drm_device *dev);

	/**
	 * @mode_valid:
	 *
	 * Device specअगरic validation of display modes. Can be used to reject
	 * modes that can never be supported. Only device wide स्थिरraपूर्णांकs can
	 * be checked here. crtc/encoder/bridge/connector specअगरic स्थिरraपूर्णांकs
	 * should be checked in the .mode_valid() hook क्रम each specअगरic object.
	 */
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा drm_device *dev,
					   स्थिर काष्ठा drm_display_mode *mode);

	/**
	 * @atomic_check:
	 *
	 * This is the only hook to validate an atomic modeset update. This
	 * function must reject any modeset and state changes which the hardware
	 * or driver करोesn't support. This includes but is of course not limited
	 * to:
	 *
	 *  - Checking that the modes, framebuffers, scaling and placement
	 *    requirements and so on are within the limits of the hardware.
	 *
	 *  - Checking that any hidden shared resources are not oversubscribed.
	 *    This can be shared PLLs, shared lanes, overall memory bandwidth,
	 *    display fअगरo space (where shared between planes or maybe even
	 *    CRTCs).
	 *
	 *  - Checking that भवized resources exported to userspace are not
	 *    oversubscribed. For various reasons it can make sense to expose
	 *    more planes, crtcs or encoders than which are physically there. One
	 *    example is dual-pipe operations (which generally should be hidden
	 *    from userspace अगर when lockstepped in hardware, exposed otherwise),
	 *    where a plane might need 1 hardware plane (अगर it's just on one
	 *    pipe), 2 hardware planes (when it spans both pipes) or maybe even
	 *    shared a hardware plane with a 2nd plane (अगर there's a compatible
	 *    plane requested on the area handled by the other pipe).
	 *
	 *  - Check that any transitional state is possible and that अगर
	 *    requested, the update can indeed be करोne in the vblank period
	 *    without temporarily disabling some functions.
	 *
	 *  - Check any other स्थिरraपूर्णांकs the driver or hardware might have.
	 *
	 *  - This callback also needs to correctly fill out the &drm_crtc_state
	 *    in this update to make sure that drm_atomic_crtc_needs_modeset()
	 *    reflects the nature of the possible update and वापसs true अगर and
	 *    only अगर the update cannot be applied without tearing within one
	 *    vblank on that CRTC. The core uses that inक्रमmation to reject
	 *    updates which require a full modeset (i.e. blanking the screen, or
	 *    at least pausing updates क्रम a substantial amount of समय) अगर
	 *    userspace has disallowed that in its request.
	 *
	 *  - The driver also करोes not need to repeat basic input validation
	 *    like करोne क्रम the corresponding legacy entry poपूर्णांकs. The core करोes
	 *    that beक्रमe calling this hook.
	 *
	 * See the करोcumentation of @atomic_commit क्रम an exhaustive list of
	 * error conditions which करोn't have to be checked at the in this
	 * callback.
	 *
	 * See the करोcumentation क्रम &काष्ठा drm_atomic_state क्रम how exactly
	 * an atomic modeset update is described.
	 *
	 * Drivers using the atomic helpers can implement this hook using
	 * drm_atomic_helper_check(), or one of the exported sub-functions of
	 * it.
	 *
	 * RETURNS:
	 *
	 * 0 on success or one of the below negative error codes:
	 *
	 *  - -EINVAL, अगर any of the above स्थिरraपूर्णांकs are violated.
	 *
	 *  - -EDEADLK, when वापसed from an attempt to acquire an additional
	 *    &drm_modeset_lock through drm_modeset_lock().
	 *
	 *  - -ENOMEM, अगर allocating additional state sub-काष्ठाures failed due
	 *    to lack of memory.
	 *
	 *  - -EINTR, -EAGAIN or -ERESTARTSYS, अगर the IOCTL should be restarted.
	 *    This can either be due to a pending संकेत, or because the driver
	 *    needs to completely bail out to recover from an exceptional
	 *    situation like a GPU hang. From a userspace poपूर्णांक all errors are
	 *    treated equally.
	 */
	पूर्णांक (*atomic_check)(काष्ठा drm_device *dev,
			    काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_commit:
	 *
	 * This is the only hook to commit an atomic modeset update. The core
	 * guarantees that @atomic_check has been called successfully beक्रमe
	 * calling this function, and that nothing has been changed in the
	 * पूर्णांकerim.
	 *
	 * See the करोcumentation क्रम &काष्ठा drm_atomic_state क्रम how exactly
	 * an atomic modeset update is described.
	 *
	 * Drivers using the atomic helpers can implement this hook using
	 * drm_atomic_helper_commit(), or one of the exported sub-functions of
	 * it.
	 *
	 * Nonblocking commits (as indicated with the nonblock parameter) must
	 * करो any preparatory work which might result in an unsuccessful commit
	 * in the context of this callback. The only exceptions are hardware
	 * errors resulting in -EIO. But even in that हाल the driver must
	 * ensure that the display pipe is at least running, to aव्योम
	 * compositors crashing when pageflips करोn't work. Anything अन्यथा,
	 * specअगरically committing the update to the hardware, should be करोne
	 * without blocking the caller. For updates which करो not require a
	 * modeset this must be guaranteed.
	 *
	 * The driver must रुको क्रम any pending rendering to the new
	 * framebuffers to complete beक्रमe executing the flip. It should also
	 * रुको क्रम any pending rendering from other drivers अगर the underlying
	 * buffer is a shared dma-buf. Nonblocking commits must not रुको क्रम
	 * rendering in the context of this callback.
	 *
	 * An application can request to be notअगरied when the atomic commit has
	 * completed. These events are per-CRTC and can be distinguished by the
	 * CRTC index supplied in &drm_event to userspace.
	 *
	 * The drm core will supply a &काष्ठा drm_event in each CRTC's
	 * &drm_crtc_state.event. See the करोcumentation क्रम
	 * &drm_crtc_state.event क्रम more details about the precise semantics of
	 * this event.
	 *
	 * NOTE:
	 *
	 * Drivers are not allowed to shut करोwn any display pipe successfully
	 * enabled through an atomic commit on their own. Doing so can result in
	 * compositors crashing अगर a page flip is suddenly rejected because the
	 * pipe is off.
	 *
	 * RETURNS:
	 *
	 * 0 on success or one of the below negative error codes:
	 *
	 *  - -EBUSY, अगर a nonblocking updated is requested and there is
	 *    an earlier updated pending. Drivers are allowed to support a queue
	 *    of outstanding updates, but currently no driver supports that.
	 *    Note that drivers must रुको क्रम preceding updates to complete अगर a
	 *    synchronous update is requested, they are not allowed to fail the
	 *    commit in that हाल.
	 *
	 *  - -ENOMEM, अगर the driver failed to allocate memory. Specअगरically
	 *    this can happen when trying to pin framebuffers, which must only
	 *    be करोne when committing the state.
	 *
	 *  - -ENOSPC, as a refinement of the more generic -ENOMEM to indicate
	 *    that the driver has run out of vram, iommu space or similar GPU
	 *    address space needed क्रम framebuffer.
	 *
	 *  - -EIO, अगर the hardware completely died.
	 *
	 *  - -EINTR, -EAGAIN or -ERESTARTSYS, अगर the IOCTL should be restarted.
	 *    This can either be due to a pending संकेत, or because the driver
	 *    needs to completely bail out to recover from an exceptional
	 *    situation like a GPU hang. From a userspace poपूर्णांक of view all errors are
	 *    treated equally.
	 *
	 * This list is exhaustive. Specअगरically this hook is not allowed to
	 * वापस -EINVAL (any invalid requests should be caught in
	 * @atomic_check) or -EDEADLK (this function must not acquire
	 * additional modeset locks).
	 */
	पूर्णांक (*atomic_commit)(काष्ठा drm_device *dev,
			     काष्ठा drm_atomic_state *state,
			     bool nonblock);

	/**
	 * @atomic_state_alloc:
	 *
	 * This optional hook can be used by drivers that want to subclass काष्ठा
	 * &drm_atomic_state to be able to track their own driver-निजी global
	 * state easily. If this hook is implemented, drivers must also
	 * implement @atomic_state_clear and @atomic_state_मुक्त.
	 *
	 * Subclassing of &drm_atomic_state is deprecated in favour of using
	 * &drm_निजी_state and &drm_निजी_obj.
	 *
	 * RETURNS:
	 *
	 * A new &drm_atomic_state on success or शून्य on failure.
	 */
	काष्ठा drm_atomic_state *(*atomic_state_alloc)(काष्ठा drm_device *dev);

	/**
	 * @atomic_state_clear:
	 *
	 * This hook must clear any driver निजी state duplicated पूर्णांकo the
	 * passed-in &drm_atomic_state. This hook is called when the caller
	 * encountered a &drm_modeset_lock deadlock and needs to drop all
	 * alपढ़ोy acquired locks as part of the deadlock aव्योमance dance
	 * implemented in drm_modeset_backoff().
	 *
	 * Any duplicated state must be invalidated since a concurrent atomic
	 * update might change it, and the drm atomic पूर्णांकerfaces always apply
	 * updates as relative changes to the current state.
	 *
	 * Drivers that implement this must call drm_atomic_state_शेष_clear()
	 * to clear common state.
	 *
	 * Subclassing of &drm_atomic_state is deprecated in favour of using
	 * &drm_निजी_state and &drm_निजी_obj.
	 */
	व्योम (*atomic_state_clear)(काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_state_मुक्त:
	 *
	 * This hook needs driver निजी resources and the &drm_atomic_state
	 * itself. Note that the core first calls drm_atomic_state_clear() to
	 * aव्योम code duplicate between the clear and मुक्त hooks.
	 *
	 * Drivers that implement this must call
	 * drm_atomic_state_शेष_release() to release common resources.
	 *
	 * Subclassing of &drm_atomic_state is deprecated in favour of using
	 * &drm_निजी_state and &drm_निजी_obj.
	 */
	व्योम (*atomic_state_मुक्त)(काष्ठा drm_atomic_state *state);
पूर्ण;

/**
 * काष्ठा drm_mode_config - Mode configuration control काष्ठाure
 * @min_width: minimum fb pixel width on this device
 * @min_height: minimum fb pixel height on this device
 * @max_width: maximum fb pixel width on this device
 * @max_height: maximum fb pixel height on this device
 * @funcs: core driver provided mode setting functions
 * @fb_base: base address of the framebuffer
 * @poll_enabled: track polling support क्रम this device
 * @poll_running: track polling status क्रम this device
 * @delayed_event: track delayed poll uevent deliver क्रम this device
 * @output_poll_work: delayed work क्रम polling in process context
 * @preferred_depth: preferred RBG pixel depth, used by fb helpers
 * @prefer_shaकरोw: hपूर्णांक to userspace to prefer shaकरोw-fb rendering
 * @cursor_width: hपूर्णांक to userspace क्रम max cursor width
 * @cursor_height: hपूर्णांक to userspace क्रम max cursor height
 * @helper_निजी: mid-layer निजी data
 *
 * Core mode resource tracking काष्ठाure.  All CRTC, encoders, and connectors
 * क्रमागतerated by the driver are added here, as are global properties.  Some
 * global restrictions are also here, e.g. dimension restrictions.
 */
काष्ठा drm_mode_config अणु
	/**
	 * @mutex:
	 *
	 * This is the big scary modeset BKL which protects everything that
	 * isn't protect otherwise. Scope is unclear and fuzzy, try to हटाओ
	 * anything from under its protection and move it पूर्णांकo more well-scoped
	 * locks.
	 *
	 * The one important thing this protects is the use of @acquire_ctx.
	 */
	काष्ठा mutex mutex;

	/**
	 * @connection_mutex:
	 *
	 * This protects connector state and the connector to encoder to CRTC
	 * routing chain.
	 *
	 * For atomic drivers specअगरically this protects &drm_connector.state.
	 */
	काष्ठा drm_modeset_lock connection_mutex;

	/**
	 * @acquire_ctx:
	 *
	 * Global implicit acquire context used by atomic drivers क्रम legacy
	 * IOCTLs. Deprecated, since implicit locking contexts make it
	 * impossible to use driver-निजी &काष्ठा drm_modeset_lock. Users of
	 * this must hold @mutex.
	 */
	काष्ठा drm_modeset_acquire_ctx *acquire_ctx;

	/**
	 * @idr_mutex:
	 *
	 * Mutex क्रम KMS ID allocation and management. Protects both @object_idr
	 * and @tile_idr.
	 */
	काष्ठा mutex idr_mutex;

	/**
	 * @object_idr:
	 *
	 * Main KMS ID tracking object. Use this idr क्रम all IDs, fb, crtc,
	 * connector, modes - just makes lअगरe easier to have only one.
	 */
	काष्ठा idr object_idr;

	/**
	 * @tile_idr:
	 *
	 * Use this idr क्रम allocating new IDs क्रम tiled sinks like use in some
	 * high-res DP MST screens.
	 */
	काष्ठा idr tile_idr;

	/** @fb_lock: Mutex to protect fb the global @fb_list and @num_fb. */
	काष्ठा mutex fb_lock;
	/** @num_fb: Number of entries on @fb_list. */
	पूर्णांक num_fb;
	/** @fb_list: List of all &काष्ठा drm_framebuffer. */
	काष्ठा list_head fb_list;

	/**
	 * @connector_list_lock: Protects @num_connector and
	 * @connector_list and @connector_मुक्त_list.
	 */
	spinlock_t connector_list_lock;
	/**
	 * @num_connector: Number of connectors on this device. Protected by
	 * @connector_list_lock.
	 */
	पूर्णांक num_connector;
	/**
	 * @connector_ida: ID allocator क्रम connector indices.
	 */
	काष्ठा ida connector_ida;
	/**
	 * @connector_list:
	 *
	 * List of connector objects linked with &drm_connector.head. Protected
	 * by @connector_list_lock. Only use drm_क्रम_each_connector_iter() and
	 * &काष्ठा drm_connector_list_iter to walk this list.
	 */
	काष्ठा list_head connector_list;
	/**
	 * @connector_मुक्त_list:
	 *
	 * List of connector objects linked with &drm_connector.मुक्त_head.
	 * Protected by @connector_list_lock. Used by
	 * drm_क्रम_each_connector_iter() and
	 * &काष्ठा drm_connector_list_iter to savely मुक्त connectors using
	 * @connector_मुक्त_work.
	 */
	काष्ठा llist_head connector_मुक्त_list;
	/**
	 * @connector_मुक्त_work: Work to clean up @connector_मुक्त_list.
	 */
	काष्ठा work_काष्ठा connector_मुक्त_work;

	/**
	 * @num_encoder:
	 *
	 * Number of encoders on this device. This is invariant over the
	 * lअगरeसमय of a device and hence करोesn't need any locks.
	 */
	पूर्णांक num_encoder;
	/**
	 * @encoder_list:
	 *
	 * List of encoder objects linked with &drm_encoder.head. This is
	 * invariant over the lअगरeसमय of a device and hence करोesn't need any
	 * locks.
	 */
	काष्ठा list_head encoder_list;

	/**
	 * @num_total_plane:
	 *
	 * Number of universal (i.e. with primary/curso) planes on this device.
	 * This is invariant over the lअगरeसमय of a device and hence करोesn't
	 * need any locks.
	 */
	पूर्णांक num_total_plane;
	/**
	 * @plane_list:
	 *
	 * List of plane objects linked with &drm_plane.head. This is invariant
	 * over the lअगरeसमय of a device and hence करोesn't need any locks.
	 */
	काष्ठा list_head plane_list;

	/**
	 * @num_crtc:
	 *
	 * Number of CRTCs on this device linked with &drm_crtc.head. This is invariant over the lअगरeसमय
	 * of a device and hence करोesn't need any locks.
	 */
	पूर्णांक num_crtc;
	/**
	 * @crtc_list:
	 *
	 * List of CRTC objects linked with &drm_crtc.head. This is invariant
	 * over the lअगरeसमय of a device and hence करोesn't need any locks.
	 */
	काष्ठा list_head crtc_list;

	/**
	 * @property_list:
	 *
	 * List of property type objects linked with &drm_property.head. This is
	 * invariant over the lअगरeसमय of a device and hence करोesn't need any
	 * locks.
	 */
	काष्ठा list_head property_list;

	/**
	 * @privobj_list:
	 *
	 * List of निजी objects linked with &drm_निजी_obj.head. This is
	 * invariant over the lअगरeसमय of a device and hence करोesn't need any
	 * locks.
	 */
	काष्ठा list_head privobj_list;

	पूर्णांक min_width, min_height;
	पूर्णांक max_width, max_height;
	स्थिर काष्ठा drm_mode_config_funcs *funcs;
	resource_माप_प्रकार fb_base;

	/* output poll support */
	bool poll_enabled;
	bool poll_running;
	bool delayed_event;
	काष्ठा delayed_work output_poll_work;

	/**
	 * @blob_lock:
	 *
	 * Mutex क्रम blob property allocation and management, protects
	 * @property_blob_list and &drm_file.blobs.
	 */
	काष्ठा mutex blob_lock;

	/**
	 * @property_blob_list:
	 *
	 * List of all the blob property objects linked with
	 * &drm_property_blob.head. Protected by @blob_lock.
	 */
	काष्ठा list_head property_blob_list;

	/* poपूर्णांकers to standard properties */

	/**
	 * @edid_property: Default connector property to hold the EDID of the
	 * currently connected sink, अगर any.
	 */
	काष्ठा drm_property *edid_property;
	/**
	 * @dpms_property: Default connector property to control the
	 * connector's DPMS state.
	 */
	काष्ठा drm_property *dpms_property;
	/**
	 * @path_property: Default connector property to hold the DP MST path
	 * क्रम the port.
	 */
	काष्ठा drm_property *path_property;
	/**
	 * @tile_property: Default connector property to store the tile
	 * position of a tiled screen, क्रम sinks which need to be driven with
	 * multiple CRTCs.
	 */
	काष्ठा drm_property *tile_property;
	/**
	 * @link_status_property: Default connector property क्रम link status
	 * of a connector
	 */
	काष्ठा drm_property *link_status_property;
	/**
	 * @plane_type_property: Default plane property to dअगरferentiate
	 * CURSOR, PRIMARY and OVERLAY legacy uses of planes.
	 */
	काष्ठा drm_property *plane_type_property;
	/**
	 * @prop_src_x: Default atomic plane property क्रम the plane source
	 * position in the connected &drm_framebuffer.
	 */
	काष्ठा drm_property *prop_src_x;
	/**
	 * @prop_src_y: Default atomic plane property क्रम the plane source
	 * position in the connected &drm_framebuffer.
	 */
	काष्ठा drm_property *prop_src_y;
	/**
	 * @prop_src_w: Default atomic plane property क्रम the plane source
	 * position in the connected &drm_framebuffer.
	 */
	काष्ठा drm_property *prop_src_w;
	/**
	 * @prop_src_h: Default atomic plane property क्रम the plane source
	 * position in the connected &drm_framebuffer.
	 */
	काष्ठा drm_property *prop_src_h;
	/**
	 * @prop_crtc_x: Default atomic plane property क्रम the plane destination
	 * position in the &drm_crtc is being shown on.
	 */
	काष्ठा drm_property *prop_crtc_x;
	/**
	 * @prop_crtc_y: Default atomic plane property क्रम the plane destination
	 * position in the &drm_crtc is being shown on.
	 */
	काष्ठा drm_property *prop_crtc_y;
	/**
	 * @prop_crtc_w: Default atomic plane property क्रम the plane destination
	 * position in the &drm_crtc is being shown on.
	 */
	काष्ठा drm_property *prop_crtc_w;
	/**
	 * @prop_crtc_h: Default atomic plane property क्रम the plane destination
	 * position in the &drm_crtc is being shown on.
	 */
	काष्ठा drm_property *prop_crtc_h;
	/**
	 * @prop_fb_id: Default atomic plane property to specअगरy the
	 * &drm_framebuffer.
	 */
	काष्ठा drm_property *prop_fb_id;
	/**
	 * @prop_in_fence_fd: Sync File fd representing the incoming fences
	 * क्रम a Plane.
	 */
	काष्ठा drm_property *prop_in_fence_fd;
	/**
	 * @prop_out_fence_ptr: Sync File fd poपूर्णांकer representing the
	 * outgoing fences क्रम a CRTC. Userspace should provide a poपूर्णांकer to a
	 * value of type s32, and then cast that poपूर्णांकer to u64.
	 */
	काष्ठा drm_property *prop_out_fence_ptr;
	/**
	 * @prop_crtc_id: Default atomic plane property to specअगरy the
	 * &drm_crtc.
	 */
	काष्ठा drm_property *prop_crtc_id;
	/**
	 * @prop_fb_damage_clips: Optional plane property to mark damaged
	 * regions on the plane in framebuffer coordinates of the framebuffer
	 * attached to the plane.
	 *
	 * The layout of blob data is simply an array of &drm_mode_rect. Unlike
	 * plane src coordinates, damage clips are not in 16.16 fixed poपूर्णांक.
	 */
	काष्ठा drm_property *prop_fb_damage_clips;
	/**
	 * @prop_active: Default atomic CRTC property to control the active
	 * state, which is the simplअगरied implementation क्रम DPMS in atomic
	 * drivers.
	 */
	काष्ठा drm_property *prop_active;
	/**
	 * @prop_mode_id: Default atomic CRTC property to set the mode क्रम a
	 * CRTC. A 0 mode implies that the CRTC is entirely disabled - all
	 * connectors must be of and active must be set to disabled, too.
	 */
	काष्ठा drm_property *prop_mode_id;
	/**
	 * @prop_vrr_enabled: Default atomic CRTC property to indicate
	 * whether variable refresh rate should be enabled on the CRTC.
	 */
	काष्ठा drm_property *prop_vrr_enabled;

	/**
	 * @dvi_i_subconnector_property: Optional DVI-I property to
	 * dअगरferentiate between analog or digital mode.
	 */
	काष्ठा drm_property *dvi_i_subconnector_property;
	/**
	 * @dvi_i_select_subconnector_property: Optional DVI-I property to
	 * select between analog or digital mode.
	 */
	काष्ठा drm_property *dvi_i_select_subconnector_property;

	/**
	 * @dp_subconnector_property: Optional DP property to dअगरferentiate
	 * between dअगरferent DP करोwnstream port types.
	 */
	काष्ठा drm_property *dp_subconnector_property;

	/**
	 * @tv_subconnector_property: Optional TV property to dअगरferentiate
	 * between dअगरferent TV connector types.
	 */
	काष्ठा drm_property *tv_subconnector_property;
	/**
	 * @tv_select_subconnector_property: Optional TV property to select
	 * between dअगरferent TV connector types.
	 */
	काष्ठा drm_property *tv_select_subconnector_property;
	/**
	 * @tv_mode_property: Optional TV property to select
	 * the output TV mode.
	 */
	काष्ठा drm_property *tv_mode_property;
	/**
	 * @tv_left_margin_property: Optional TV property to set the left
	 * margin (expressed in pixels).
	 */
	काष्ठा drm_property *tv_left_margin_property;
	/**
	 * @tv_right_margin_property: Optional TV property to set the right
	 * margin (expressed in pixels).
	 */
	काष्ठा drm_property *tv_right_margin_property;
	/**
	 * @tv_top_margin_property: Optional TV property to set the right
	 * margin (expressed in pixels).
	 */
	काष्ठा drm_property *tv_top_margin_property;
	/**
	 * @tv_bottom_margin_property: Optional TV property to set the right
	 * margin (expressed in pixels).
	 */
	काष्ठा drm_property *tv_bottom_margin_property;
	/**
	 * @tv_brightness_property: Optional TV property to set the
	 * brightness.
	 */
	काष्ठा drm_property *tv_brightness_property;
	/**
	 * @tv_contrast_property: Optional TV property to set the
	 * contrast.
	 */
	काष्ठा drm_property *tv_contrast_property;
	/**
	 * @tv_flicker_reduction_property: Optional TV property to control the
	 * flicker reduction mode.
	 */
	काष्ठा drm_property *tv_flicker_reduction_property;
	/**
	 * @tv_overscan_property: Optional TV property to control the overscan
	 * setting.
	 */
	काष्ठा drm_property *tv_overscan_property;
	/**
	 * @tv_saturation_property: Optional TV property to set the
	 * saturation.
	 */
	काष्ठा drm_property *tv_saturation_property;
	/**
	 * @tv_hue_property: Optional TV property to set the hue.
	 */
	काष्ठा drm_property *tv_hue_property;

	/**
	 * @scaling_mode_property: Optional connector property to control the
	 * upscaling, mostly used क्रम built-in panels.
	 */
	काष्ठा drm_property *scaling_mode_property;
	/**
	 * @aspect_ratio_property: Optional connector property to control the
	 * HDMI infoframe aspect ratio setting.
	 */
	काष्ठा drm_property *aspect_ratio_property;
	/**
	 * @content_type_property: Optional connector property to control the
	 * HDMI infoframe content type setting.
	 */
	काष्ठा drm_property *content_type_property;
	/**
	 * @degamma_lut_property: Optional CRTC property to set the LUT used to
	 * convert the framebuffer's colors to linear gamma.
	 */
	काष्ठा drm_property *degamma_lut_property;
	/**
	 * @degamma_lut_size_property: Optional CRTC property क्रम the size of
	 * the degamma LUT as supported by the driver (पढ़ो-only).
	 */
	काष्ठा drm_property *degamma_lut_size_property;
	/**
	 * @cपंचांग_property: Optional CRTC property to set the
	 * matrix used to convert colors after the lookup in the
	 * degamma LUT.
	 */
	काष्ठा drm_property *cपंचांग_property;
	/**
	 * @gamma_lut_property: Optional CRTC property to set the LUT used to
	 * convert the colors, after the CTM matrix, to the gamma space of the
	 * connected screen.
	 */
	काष्ठा drm_property *gamma_lut_property;
	/**
	 * @gamma_lut_size_property: Optional CRTC property क्रम the size of the
	 * gamma LUT as supported by the driver (पढ़ो-only).
	 */
	काष्ठा drm_property *gamma_lut_size_property;

	/**
	 * @suggested_x_property: Optional connector property with a hपूर्णांक क्रम
	 * the position of the output on the host's screen.
	 */
	काष्ठा drm_property *suggested_x_property;
	/**
	 * @suggested_y_property: Optional connector property with a hपूर्णांक क्रम
	 * the position of the output on the host's screen.
	 */
	काष्ठा drm_property *suggested_y_property;

	/**
	 * @non_desktop_property: Optional connector property with a hपूर्णांक
	 * that device isn't a standard display, and the console/desktop,
	 * should not be displayed on it.
	 */
	काष्ठा drm_property *non_desktop_property;

	/**
	 * @panel_orientation_property: Optional connector property indicating
	 * how the lcd-panel is mounted inside the casing (e.g. normal or
	 * upside-करोwn).
	 */
	काष्ठा drm_property *panel_orientation_property;

	/**
	 * @ग_लिखोback_fb_id_property: Property क्रम ग_लिखोback connectors, storing
	 * the ID of the output framebuffer.
	 * See also: drm_ग_लिखोback_connector_init()
	 */
	काष्ठा drm_property *ग_लिखोback_fb_id_property;

	/**
	 * @ग_लिखोback_pixel_क्रमmats_property: Property क्रम ग_लिखोback connectors,
	 * storing an array of the supported pixel क्रमmats क्रम the ग_लिखोback
	 * engine (पढ़ो-only).
	 * See also: drm_ग_लिखोback_connector_init()
	 */
	काष्ठा drm_property *ग_लिखोback_pixel_क्रमmats_property;
	/**
	 * @ग_लिखोback_out_fence_ptr_property: Property क्रम ग_लिखोback connectors,
	 * fd poपूर्णांकer representing the outgoing fences क्रम a ग_लिखोback
	 * connector. Userspace should provide a poपूर्णांकer to a value of type s32,
	 * and then cast that poपूर्णांकer to u64.
	 * See also: drm_ग_लिखोback_connector_init()
	 */
	काष्ठा drm_property *ग_लिखोback_out_fence_ptr_property;

	/**
	 * @hdr_output_metadata_property: Connector property containing hdr
	 * metatada. This will be provided by userspace compositors based
	 * on HDR content
	 */
	काष्ठा drm_property *hdr_output_metadata_property;

	/**
	 * @content_protection_property: DRM ENUM property क्रम content
	 * protection. See drm_connector_attach_content_protection_property().
	 */
	काष्ठा drm_property *content_protection_property;

	/**
	 * @hdcp_content_type_property: DRM ENUM property क्रम type of
	 * Protected Content.
	 */
	काष्ठा drm_property *hdcp_content_type_property;

	/* dumb ioctl parameters */
	uपूर्णांक32_t preferred_depth, prefer_shaकरोw;

	/**
	 * @prefer_shaकरोw_fbdev:
	 *
	 * Hपूर्णांक to framebuffer emulation to prefer shaकरोw-fb rendering.
	 */
	bool prefer_shaकरोw_fbdev;

	/**
	 * @quirk_addfb_prefer_xbgr_30bpp:
	 *
	 * Special hack क्रम legacy ADDFB to keep nouveau userspace happy. Should
	 * only ever be set by the nouveau kernel driver.
	 */
	bool quirk_addfb_prefer_xbgr_30bpp;

	/**
	 * @quirk_addfb_prefer_host_byte_order:
	 *
	 * When set to true drm_mode_addfb() will pick host byte order
	 * pixel_क्रमmat when calling drm_mode_addfb2().  This is how
	 * drm_mode_addfb() should have worked from day one.  It
	 * didn't though, so we ended up with quirks in both kernel
	 * and userspace drivers to deal with the broken behavior.
	 * Simply fixing drm_mode_addfb() unconditionally would अवरोध
	 * these drivers, so add a quirk bit here to allow drivers
	 * opt-in.
	 */
	bool quirk_addfb_prefer_host_byte_order;

	/**
	 * @async_page_flip: Does this device support async flips on the primary
	 * plane?
	 */
	bool async_page_flip;

	/**
	 * @allow_fb_modअगरiers:
	 *
	 * Whether the driver supports fb modअगरiers in the ADDFB2.1 ioctl call.
	 *
	 * IMPORTANT:
	 *
	 * If this is set the driver must fill out the full implicit modअगरier
	 * inक्रमmation in their &drm_mode_config_funcs.fb_create hook क्रम legacy
	 * userspace which करोes not set modअगरiers. Otherwise the GETFB2 ioctl is
	 * broken क्रम modअगरier aware userspace.
	 */
	bool allow_fb_modअगरiers;

	/**
	 * @normalize_zpos:
	 *
	 * If true the drm core will call drm_atomic_normalize_zpos() as part of
	 * atomic mode checking from drm_atomic_helper_check()
	 */
	bool normalize_zpos;

	/**
	 * @modअगरiers_property: Plane property to list support modअगरier/क्रमmat
	 * combination.
	 */
	काष्ठा drm_property *modअगरiers_property;

	/* cursor size */
	uपूर्णांक32_t cursor_width, cursor_height;

	/**
	 * @suspend_state:
	 *
	 * Atomic state when suspended.
	 * Set by drm_mode_config_helper_suspend() and cleared by
	 * drm_mode_config_helper_resume().
	 */
	काष्ठा drm_atomic_state *suspend_state;

	स्थिर काष्ठा drm_mode_config_helper_funcs *helper_निजी;
पूर्ण;

पूर्णांक __must_check drmm_mode_config_init(काष्ठा drm_device *dev);

/**
 * drm_mode_config_init - DRM mode_configuration काष्ठाure initialization
 * @dev: DRM device
 *
 * This is the unmanaged version of drmm_mode_config_init() क्रम drivers which
 * still explicitly call drm_mode_config_cleanup().
 *
 * FIXME: This function is deprecated and drivers should be converted over to
 * drmm_mode_config_init().
 */
अटल अंतरभूत पूर्णांक drm_mode_config_init(काष्ठा drm_device *dev)
अणु
	वापस drmm_mode_config_init(dev);
पूर्ण

व्योम drm_mode_config_reset(काष्ठा drm_device *dev);
व्योम drm_mode_config_cleanup(काष्ठा drm_device *dev);

#पूर्ण_अगर
