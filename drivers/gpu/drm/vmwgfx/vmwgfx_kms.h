<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#अगर_अघोषित VMWGFX_KMS_H_
#घोषणा VMWGFX_KMS_H_

#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "vmwgfx_drv.h"

/**
 * काष्ठा vmw_du_update_plane - Closure काष्ठाure क्रम vmw_du_helper_plane_update
 * @plane: Plane which is being updated.
 * @old_state: Old state of plane.
 * @dev_priv: Device निजी.
 * @du: Display unit on which to update the plane.
 * @vfb: Framebuffer which is blitted to display unit.
 * @out_fence: Out fence क्रम resource finish.
 * @mutex: The mutex used to protect resource reservation.
 * @cpu_blit: True अगर need cpu blit.
 * @पूर्णांकr: Whether to perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 *
 * This काष्ठाure loosely represent the set of operations needed to perक्रमm a
 * plane update on a display unit. Implementer will define that functionality
 * according to the function callbacks क्रम this काष्ठाure. In brief it involves
 * surface/buffer object validation, populate FIFO commands and command
 * submission to the device.
 */
काष्ठा vmw_du_update_plane अणु
	/**
	 * @calc_fअगरo_size: Calculate fअगरo size.
	 *
	 * Determine fअगरo size क्रम the commands needed क्रम update. The number of
	 * damage clips on display unit @num_hits will be passed to allocate
	 * sufficient fअगरo space.
	 *
	 * Return: Fअगरo size needed
	 */
	uपूर्णांक32_t (*calc_fअगरo_size)(काष्ठा vmw_du_update_plane *update,
				   uपूर्णांक32_t num_hits);

	/**
	 * @post_prepare: Populate fअगरo क्रम resource preparation.
	 *
	 * Some surface resource or buffer object need some extra cmd submission
	 * like update GB image क्रम proxy surface and define a GMRFB क्रम screen
	 * object. That should should be करोne here as this callback will be
	 * called after FIFO allocation with the address of command buufer.
	 *
	 * This callback is optional.
	 *
	 * Return: Size of commands populated to command buffer.
	 */
	uपूर्णांक32_t (*post_prepare)(काष्ठा vmw_du_update_plane *update, व्योम *cmd);

	/**
	 * @pre_clip: Populate fअगरo beक्रमe clip.
	 *
	 * This is where pre clip related command should be populated like
	 * surface copy/DMA, etc.
	 *
	 * This callback is optional.
	 *
	 * Return: Size of commands populated to command buffer.
	 */
	uपूर्णांक32_t (*pre_clip)(काष्ठा vmw_du_update_plane *update, व्योम *cmd,
			     uपूर्णांक32_t num_hits);

	/**
	 * @clip: Populate fअगरo क्रम clip.
	 *
	 * This is where to populate clips क्रम surface copy/dma or blit commands
	 * अगर needed. This will be called बार have damage in display unit,
	 * which is one अगर करोing full update. @clip is the damage in destination
	 * coordinates which is crtc/DU and @src_x, @src_y is damage clip src in
	 * framebuffer coordinate.
	 *
	 * This callback is optional.
	 *
	 * Return: Size of commands populated to command buffer.
	 */
	uपूर्णांक32_t (*clip)(काष्ठा vmw_du_update_plane *update, व्योम *cmd,
			 काष्ठा drm_rect *clip, uपूर्णांक32_t src_x, uपूर्णांक32_t src_y);

	/**
	 * @post_clip: Populate fअगरo after clip.
	 *
	 * This is where to populate display unit update commands or blit
	 * commands.
	 *
	 * Return: Size of commands populated to command buffer.
	 */
	uपूर्णांक32_t (*post_clip)(काष्ठा vmw_du_update_plane *update, व्योम *cmd,
				    काष्ठा drm_rect *bb);

	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_state;
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_display_unit *du;
	काष्ठा vmw_framebuffer *vfb;
	काष्ठा vmw_fence_obj **out_fence;
	काष्ठा mutex *mutex;
	bool cpu_blit;
	bool पूर्णांकr;
पूर्ण;

/**
 * काष्ठा vmw_du_update_plane_surface - closure काष्ठाure क्रम surface
 * @base: base closure काष्ठाure.
 * @cmd_start: FIFO command start address (used by SOU only).
 */
काष्ठा vmw_du_update_plane_surface अणु
	काष्ठा vmw_du_update_plane base;
	/* This member is to handle special हाल SOU surface update */
	व्योम *cmd_start;
पूर्ण;

/**
 * काष्ठा vmw_du_update_plane_buffer - Closure काष्ठाure क्रम buffer object
 * @base: Base closure काष्ठाure.
 * @fb_left: x1 क्रम fb damage bounding box.
 * @fb_top: y1 क्रम fb damage bounding box.
 */
काष्ठा vmw_du_update_plane_buffer अणु
	काष्ठा vmw_du_update_plane base;
	पूर्णांक fb_left, fb_top;
पूर्ण;

/**
 * काष्ठा vmw_kms_dirty - closure काष्ठाure क्रम the vmw_kms_helper_dirty
 * function.
 *
 * @fअगरo_commit: Callback that is called once क्रम each display unit after
 * all clip rects. This function must commit the fअगरo space reserved by the
 * helper. Set up by the caller.
 * @clip: Callback that is called क्रम each cliprect on each display unit.
 * Set up by the caller.
 * @fअगरo_reserve_size: Fअगरo size that the helper should try to allocat क्रम
 * each display unit. Set up by the caller.
 * @dev_priv: Poपूर्णांकer to the device निजी. Set up by the helper.
 * @unit: The current display unit. Set up by the helper beक्रमe a call to @clip.
 * @cmd: The allocated fअगरo space. Set up by the helper beक्रमe the first @clip
 * call.
 * @crtc: The crtc क्रम which to build dirty commands.
 * @num_hits: Number of clip rect commands क्रम this display unit.
 * Cleared by the helper beक्रमe the first @clip call. Updated by the @clip
 * callback.
 * @fb_x: Clip rect left side in framebuffer coordinates.
 * @fb_y: Clip rect right side in framebuffer coordinates.
 * @unit_x1: Clip rect left side in crtc coordinates.
 * @unit_y1: Clip rect top side in crtc coordinates.
 * @unit_x2: Clip rect right side in crtc coordinates.
 * @unit_y2: Clip rect bottom side in crtc coordinates.
 *
 * The clip rect coordinates are updated by the helper क्रम each @clip call.
 * Note that this may be derived from अगर more info needs to be passed between
 * helper caller and helper callbacks.
 */
काष्ठा vmw_kms_dirty अणु
	व्योम (*fअगरo_commit)(काष्ठा vmw_kms_dirty *);
	व्योम (*clip)(काष्ठा vmw_kms_dirty *);
	माप_प्रकार fअगरo_reserve_size;
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_display_unit *unit;
	व्योम *cmd;
	काष्ठा drm_crtc *crtc;
	u32 num_hits;
	s32 fb_x;
	s32 fb_y;
	s32 unit_x1;
	s32 unit_y1;
	s32 unit_x2;
	s32 unit_y2;
पूर्ण;

#घोषणा VMWGFX_NUM_DISPLAY_UNITS 8


#घोषणा vmw_framebuffer_to_vfb(x) \
	container_of(x, काष्ठा vmw_framebuffer, base)
#घोषणा vmw_framebuffer_to_vfbs(x) \
	container_of(x, काष्ठा vmw_framebuffer_surface, base.base)
#घोषणा vmw_framebuffer_to_vfbd(x) \
	container_of(x, काष्ठा vmw_framebuffer_bo, base.base)

/**
 * Base class क्रम framebuffers
 *
 * @pin is called the when ever a crtc uses this framebuffer
 * @unpin is called
 */
काष्ठा vmw_framebuffer अणु
	काष्ठा drm_framebuffer base;
	पूर्णांक (*pin)(काष्ठा vmw_framebuffer *fb);
	पूर्णांक (*unpin)(काष्ठा vmw_framebuffer *fb);
	bool bo;
	काष्ठा tपंचांग_base_object *user_obj;
	uपूर्णांक32_t user_handle;
पूर्ण;

/*
 * Clip rectangle
 */
काष्ठा vmw_clip_rect अणु
	पूर्णांक x1, x2, y1, y2;
पूर्ण;

काष्ठा vmw_framebuffer_surface अणु
	काष्ठा vmw_framebuffer base;
	काष्ठा vmw_surface *surface;
	काष्ठा vmw_buffer_object *buffer;
	काष्ठा list_head head;
	bool is_bo_proxy;  /* true अगर this is proxy surface क्रम DMA buf */
पूर्ण;


काष्ठा vmw_framebuffer_bo अणु
	काष्ठा vmw_framebuffer base;
	काष्ठा vmw_buffer_object *buffer;
पूर्ण;


अटल स्थिर uपूर्णांक32_t __maybe_unused vmw_primary_plane_क्रमmats[] = अणु
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर uपूर्णांक32_t __maybe_unused vmw_cursor_plane_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;


#घोषणा vmw_crtc_state_to_vcs(x) container_of(x, काष्ठा vmw_crtc_state, base)
#घोषणा vmw_plane_state_to_vps(x) container_of(x, काष्ठा vmw_plane_state, base)
#घोषणा vmw_connector_state_to_vcs(x) \
		container_of(x, काष्ठा vmw_connector_state, base)

/**
 * Derived class क्रम crtc state object
 *
 * @base DRM crtc object
 */
काष्ठा vmw_crtc_state अणु
	काष्ठा drm_crtc_state base;
पूर्ण;

/**
 * Derived class क्रम plane state object
 *
 * @base DRM plane object
 * @surf Display surface क्रम STDU
 * @bo display bo क्रम SOU
 * @content_fb_type Used by STDU.
 * @bo_size Size of the bo, used by Screen Object Display Unit
 * @pinned pin count क्रम STDU display surface
 */
काष्ठा vmw_plane_state अणु
	काष्ठा drm_plane_state base;
	काष्ठा vmw_surface *surf;
	काष्ठा vmw_buffer_object *bo;

	पूर्णांक content_fb_type;
	अचिन्हित दीर्घ bo_size;

	पूर्णांक pinned;

	/* For CPU Blit */
	अचिन्हित पूर्णांक cpp;
पूर्ण;


/**
 * Derived class क्रम connector state object
 *
 * @base DRM connector object
 * @is_implicit connector property
 *
 */
काष्ठा vmw_connector_state अणु
	काष्ठा drm_connector_state base;

	/**
	 * @gui_x:
	 *
	 * vmwgfx connector property representing the x position of this display
	 * unit (connector is synonymous to display unit) in overall topology.
	 * This is what the device expect as xRoot जबतक creating screen.
	 */
	पूर्णांक gui_x;

	/**
	 * @gui_y:
	 *
	 * vmwgfx connector property representing the y position of this display
	 * unit (connector is synonymous to display unit) in overall topology.
	 * This is what the device expect as yRoot जबतक creating screen.
	 */
	पूर्णांक gui_y;
पूर्ण;

/**
 * Base class display unit.
 *
 * Since the SVGA hw करोesn't have a concept of a crtc, encoder or connector
 * so the display unit is all of them at the same समय. This is true क्रम both
 * legacy multimon and screen objects.
 */
काष्ठा vmw_display_unit अणु
	काष्ठा drm_crtc crtc;
	काष्ठा drm_encoder encoder;
	काष्ठा drm_connector connector;
	काष्ठा drm_plane primary;
	काष्ठा drm_plane cursor;

	काष्ठा vmw_surface *cursor_surface;
	काष्ठा vmw_buffer_object *cursor_bo;
	माप_प्रकार cursor_age;

	पूर्णांक cursor_x;
	पूर्णांक cursor_y;

	पूर्णांक hotspot_x;
	पूर्णांक hotspot_y;
	s32 core_hotspot_x;
	s32 core_hotspot_y;

	अचिन्हित unit;

	/*
	 * Prefered mode tracking.
	 */
	अचिन्हित pref_width;
	अचिन्हित pref_height;
	bool pref_active;
	काष्ठा drm_display_mode *pref_mode;

	/*
	 * Gui positioning
	 */
	पूर्णांक gui_x;
	पूर्णांक gui_y;
	bool is_implicit;
	पूर्णांक set_gui_x;
	पूर्णांक set_gui_y;
पूर्ण;

काष्ठा vmw_validation_ctx अणु
	काष्ठा vmw_resource *res;
	काष्ठा vmw_buffer_object *buf;
पूर्ण;

#घोषणा vmw_crtc_to_du(x) \
	container_of(x, काष्ठा vmw_display_unit, crtc)
#घोषणा vmw_connector_to_du(x) \
	container_of(x, काष्ठा vmw_display_unit, connector)


/*
 * Shared display unit functions - vmwgfx_kms.c
 */
व्योम vmw_du_cleanup(काष्ठा vmw_display_unit *du);
व्योम vmw_du_crtc_save(काष्ठा drm_crtc *crtc);
व्योम vmw_du_crtc_restore(काष्ठा drm_crtc *crtc);
पूर्णांक vmw_du_crtc_gamma_set(काष्ठा drm_crtc *crtc,
			   u16 *r, u16 *g, u16 *b,
			   uपूर्णांक32_t size,
			   काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक vmw_du_connector_set_property(काष्ठा drm_connector *connector,
				  काष्ठा drm_property *property,
				  uपूर्णांक64_t val);
पूर्णांक vmw_du_connector_atomic_set_property(काष्ठा drm_connector *connector,
					 काष्ठा drm_connector_state *state,
					 काष्ठा drm_property *property,
					 uपूर्णांक64_t val);
पूर्णांक
vmw_du_connector_atomic_get_property(काष्ठा drm_connector *connector,
				     स्थिर काष्ठा drm_connector_state *state,
				     काष्ठा drm_property *property,
				     uपूर्णांक64_t *val);
पूर्णांक vmw_du_connector_dpms(काष्ठा drm_connector *connector, पूर्णांक mode);
व्योम vmw_du_connector_save(काष्ठा drm_connector *connector);
व्योम vmw_du_connector_restore(काष्ठा drm_connector *connector);
क्रमागत drm_connector_status
vmw_du_connector_detect(काष्ठा drm_connector *connector, bool क्रमce);
पूर्णांक vmw_du_connector_fill_modes(काष्ठा drm_connector *connector,
				uपूर्णांक32_t max_width, uपूर्णांक32_t max_height);
पूर्णांक vmw_kms_helper_dirty(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा vmw_framebuffer *framebuffer,
			 स्थिर काष्ठा drm_clip_rect *clips,
			 स्थिर काष्ठा drm_vmw_rect *vclips,
			 s32 dest_x, s32 dest_y,
			 पूर्णांक num_clips,
			 पूर्णांक increment,
			 काष्ठा vmw_kms_dirty *dirty);

व्योम vmw_kms_helper_validation_finish(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा drm_file *file_priv,
				      काष्ठा vmw_validation_context *ctx,
				      काष्ठा vmw_fence_obj **out_fence,
				      काष्ठा drm_vmw_fence_rep __user *
				      user_fence_rep);
पूर्णांक vmw_kms_पढ़ोback(काष्ठा vmw_निजी *dev_priv,
		     काष्ठा drm_file *file_priv,
		     काष्ठा vmw_framebuffer *vfb,
		     काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
		     काष्ठा drm_vmw_rect *vclips,
		     uपूर्णांक32_t num_clips);
काष्ठा vmw_framebuffer *
vmw_kms_new_framebuffer(काष्ठा vmw_निजी *dev_priv,
			काष्ठा vmw_buffer_object *bo,
			काष्ठा vmw_surface *surface,
			bool only_2d,
			स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);
पूर्णांक vmw_kms_fbdev_init_data(काष्ठा vmw_निजी *dev_priv,
			    अचिन्हित unit,
			    u32 max_width,
			    u32 max_height,
			    काष्ठा drm_connector **p_con,
			    काष्ठा drm_crtc **p_crtc,
			    काष्ठा drm_display_mode **p_mode);
व्योम vmw_guess_mode_timing(काष्ठा drm_display_mode *mode);
व्योम vmw_kms_update_implicit_fb(काष्ठा vmw_निजी *dev_priv);
व्योम vmw_kms_create_implicit_placement_property(काष्ठा vmw_निजी *dev_priv);

/* Universal Plane Helpers */
व्योम vmw_du_primary_plane_destroy(काष्ठा drm_plane *plane);
व्योम vmw_du_cursor_plane_destroy(काष्ठा drm_plane *plane);

/* Atomic Helpers */
पूर्णांक vmw_du_primary_plane_atomic_check(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state);
पूर्णांक vmw_du_cursor_plane_atomic_check(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state);
व्योम vmw_du_cursor_plane_atomic_update(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state);
पूर्णांक vmw_du_cursor_plane_prepare_fb(काष्ठा drm_plane *plane,
				   काष्ठा drm_plane_state *new_state);
व्योम vmw_du_plane_cleanup_fb(काष्ठा drm_plane *plane,
			     काष्ठा drm_plane_state *old_state);
व्योम vmw_du_plane_reset(काष्ठा drm_plane *plane);
काष्ठा drm_plane_state *vmw_du_plane_duplicate_state(काष्ठा drm_plane *plane);
व्योम vmw_du_plane_destroy_state(काष्ठा drm_plane *plane,
				काष्ठा drm_plane_state *state);
व्योम vmw_du_plane_unpin_surf(काष्ठा vmw_plane_state *vps,
			     bool unreference);

पूर्णांक vmw_du_crtc_atomic_check(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_atomic_state *state);
व्योम vmw_du_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state);
व्योम vmw_du_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state);
व्योम vmw_du_crtc_reset(काष्ठा drm_crtc *crtc);
काष्ठा drm_crtc_state *vmw_du_crtc_duplicate_state(काष्ठा drm_crtc *crtc);
व्योम vmw_du_crtc_destroy_state(काष्ठा drm_crtc *crtc,
				काष्ठा drm_crtc_state *state);
व्योम vmw_du_connector_reset(काष्ठा drm_connector *connector);
काष्ठा drm_connector_state *
vmw_du_connector_duplicate_state(काष्ठा drm_connector *connector);

व्योम vmw_du_connector_destroy_state(काष्ठा drm_connector *connector,
				    काष्ठा drm_connector_state *state);

/*
 * Legacy display unit functions - vmwgfx_ldu.c
 */
पूर्णांक vmw_kms_ldu_init_display(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_kms_ldu_बंद_display(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_kms_ldu_करो_bo_dirty(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_framebuffer *framebuffer,
			    अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक color,
			    काष्ठा drm_clip_rect *clips,
			    अचिन्हित पूर्णांक num_clips, पूर्णांक increment);
पूर्णांक vmw_kms_update_proxy(काष्ठा vmw_resource *res,
			 स्थिर काष्ठा drm_clip_rect *clips,
			 अचिन्हित num_clips,
			 पूर्णांक increment);

/*
 * Screen Objects display functions - vmwgfx_scrn.c
 */
पूर्णांक vmw_kms_sou_init_display(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_kms_sou_करो_surface_dirty(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_framebuffer *framebuffer,
				 काष्ठा drm_clip_rect *clips,
				 काष्ठा drm_vmw_rect *vclips,
				 काष्ठा vmw_resource *srf,
				 s32 dest_x,
				 s32 dest_y,
				 अचिन्हित num_clips, पूर्णांक inc,
				 काष्ठा vmw_fence_obj **out_fence,
				 काष्ठा drm_crtc *crtc);
पूर्णांक vmw_kms_sou_करो_bo_dirty(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_framebuffer *framebuffer,
			    काष्ठा drm_clip_rect *clips,
			    काष्ठा drm_vmw_rect *vclips,
			    अचिन्हित पूर्णांक num_clips, पूर्णांक increment,
			    bool पूर्णांकerruptible,
			    काष्ठा vmw_fence_obj **out_fence,
			    काष्ठा drm_crtc *crtc);
पूर्णांक vmw_kms_sou_पढ़ोback(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा drm_file *file_priv,
			 काष्ठा vmw_framebuffer *vfb,
			 काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
			 काष्ठा drm_vmw_rect *vclips,
			 uपूर्णांक32_t num_clips,
			 काष्ठा drm_crtc *crtc);

/*
 * Screen Target Display Unit functions - vmwgfx_stdu.c
 */
पूर्णांक vmw_kms_stdu_init_display(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_kms_stdu_surface_dirty(काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_framebuffer *framebuffer,
			       काष्ठा drm_clip_rect *clips,
			       काष्ठा drm_vmw_rect *vclips,
			       काष्ठा vmw_resource *srf,
			       s32 dest_x,
			       s32 dest_y,
			       अचिन्हित num_clips, पूर्णांक inc,
			       काष्ठा vmw_fence_obj **out_fence,
			       काष्ठा drm_crtc *crtc);
पूर्णांक vmw_kms_stdu_dma(काष्ठा vmw_निजी *dev_priv,
		     काष्ठा drm_file *file_priv,
		     काष्ठा vmw_framebuffer *vfb,
		     काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
		     काष्ठा drm_clip_rect *clips,
		     काष्ठा drm_vmw_rect *vclips,
		     uपूर्णांक32_t num_clips,
		     पूर्णांक increment,
		     bool to_surface,
		     bool पूर्णांकerruptible,
		     काष्ठा drm_crtc *crtc);

पूर्णांक vmw_du_helper_plane_update(काष्ठा vmw_du_update_plane *update);

/**
 * vmw_du_translate_to_crtc - Translate a rect from framebuffer to crtc
 * @state: Plane state.
 * @r: Rectangle to translate.
 */
अटल अंतरभूत व्योम vmw_du_translate_to_crtc(काष्ठा drm_plane_state *state,
					    काष्ठा drm_rect *r)
अणु
	पूर्णांक translate_crtc_x = -((state->src_x >> 16) - state->crtc_x);
	पूर्णांक translate_crtc_y = -((state->src_y >> 16) - state->crtc_y);

	drm_rect_translate(r, translate_crtc_x, translate_crtc_y);
पूर्ण

#पूर्ण_अगर
