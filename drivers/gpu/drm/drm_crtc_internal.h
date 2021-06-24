<शैली गुरु>
/*
 * Copyright तऊ 2006 Keith Packard
 * Copyright तऊ 2007-2008 Dave Airlie
 * Copyright तऊ 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 * Copyright तऊ 2014 Intel Corporation
 *   Daniel Vetter <daniel.vetter@ffwll.ch>
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
 */

/*
 * This header file contains mode setting related functions and definitions
 * which are only used within the drm module as पूर्णांकernal implementation details
 * and are not exported to drivers.
 */

#समावेश <linux/types.h>

क्रमागत drm_color_encoding;
क्रमागत drm_color_range;
क्रमागत drm_connector_क्रमce;
क्रमागत drm_mode_status;

काष्ठा drm_atomic_state;
काष्ठा drm_bridge;
काष्ठा drm_connector;
काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा drm_display_mode;
काष्ठा drm_file;
काष्ठा drm_framebuffer;
काष्ठा drm_mode_create_dumb;
काष्ठा drm_mode_fb_cmd2;
काष्ठा drm_mode_fb_cmd;
काष्ठा drm_mode_object;
काष्ठा drm_mode_set;
काष्ठा drm_plane;
काष्ठा drm_plane_state;
काष्ठा drm_property;
काष्ठा edid;
काष्ठा kref;
काष्ठा work_काष्ठा;

/* drm_crtc.c */
पूर्णांक drm_mode_crtc_set_obj_prop(काष्ठा drm_mode_object *obj,
			       काष्ठा drm_property *property,
			       uपूर्णांक64_t value);
पूर्णांक drm_crtc_check_viewport(स्थिर काष्ठा drm_crtc *crtc,
			    पूर्णांक x, पूर्णांक y,
			    स्थिर काष्ठा drm_display_mode *mode,
			    स्थिर काष्ठा drm_framebuffer *fb);
पूर्णांक drm_crtc_रेजिस्टर_all(काष्ठा drm_device *dev);
व्योम drm_crtc_unरेजिस्टर_all(काष्ठा drm_device *dev);
पूर्णांक drm_crtc_क्रमce_disable(काष्ठा drm_crtc *crtc);

काष्ठा dma_fence *drm_crtc_create_fence(काष्ठा drm_crtc *crtc);

काष्ठा drm_property *
drm_create_scaling_filter_prop(काष्ठा drm_device *dev,
			       अचिन्हित पूर्णांक supported_filters);
/* IOCTLs */
पूर्णांक drm_mode_अ_लोrtc(काष्ठा drm_device *dev,
		     व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_setcrtc(काष्ठा drm_device *dev,
		     व्योम *data, काष्ठा drm_file *file_priv);


/* drm_mode_config.c */
पूर्णांक drm_modeset_रेजिस्टर_all(काष्ठा drm_device *dev);
व्योम drm_modeset_unरेजिस्टर_all(काष्ठा drm_device *dev);
व्योम drm_mode_config_validate(काष्ठा drm_device *dev);

/* drm_modes.c */
स्थिर अक्षर *drm_get_mode_status_name(क्रमागत drm_mode_status status);

/* IOCTLs */
पूर्णांक drm_mode_getresources(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv);


/* drm_dumb_buffers.c */
पूर्णांक drm_mode_create_dumb(काष्ठा drm_device *dev,
			 काष्ठा drm_mode_create_dumb *args,
			 काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_destroy_dumb(काष्ठा drm_device *dev, u32 handle,
			  काष्ठा drm_file *file_priv);

/* IOCTLs */
पूर्णांक drm_mode_create_dumb_ioctl(काष्ठा drm_device *dev,
			       व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_mmap_dumb_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_destroy_dumb_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *file_priv);

/* drm_color_mgmt.c */
स्थिर अक्षर *drm_get_color_encoding_name(क्रमागत drm_color_encoding encoding);
स्थिर अक्षर *drm_get_color_range_name(क्रमागत drm_color_range range);

/* IOCTLs */
पूर्णांक drm_mode_gamma_get_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_gamma_set_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *file_priv);

/* drm_property.c */
व्योम drm_property_destroy_user_blobs(काष्ठा drm_device *dev,
				     काष्ठा drm_file *file_priv);
bool drm_property_change_valid_get(काष्ठा drm_property *property,
				   uपूर्णांक64_t value,
				   काष्ठा drm_mode_object **ref);
व्योम drm_property_change_valid_put(काष्ठा drm_property *property,
				   काष्ठा drm_mode_object *ref);

/* IOCTL */
पूर्णांक drm_mode_getproperty_ioctl(काष्ठा drm_device *dev,
			       व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_getblob_ioctl(काष्ठा drm_device *dev,
			   व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_createblob_ioctl(काष्ठा drm_device *dev,
			      व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_destroyblob_ioctl(काष्ठा drm_device *dev,
			       व्योम *data, काष्ठा drm_file *file_priv);

/* drm_mode_object.c */
पूर्णांक __drm_mode_object_add(काष्ठा drm_device *dev, काष्ठा drm_mode_object *obj,
			  uपूर्णांक32_t obj_type, bool रेजिस्टर_obj,
			  व्योम (*obj_मुक्त_cb)(काष्ठा kref *kref));
पूर्णांक drm_mode_object_add(काष्ठा drm_device *dev, काष्ठा drm_mode_object *obj,
			uपूर्णांक32_t obj_type);
व्योम drm_mode_object_रेजिस्टर(काष्ठा drm_device *dev,
			      काष्ठा drm_mode_object *obj);
काष्ठा drm_mode_object *__drm_mode_object_find(काष्ठा drm_device *dev,
					       काष्ठा drm_file *file_priv,
					       uपूर्णांक32_t id, uपूर्णांक32_t type);
व्योम drm_mode_object_unरेजिस्टर(काष्ठा drm_device *dev,
				काष्ठा drm_mode_object *object);
पूर्णांक drm_mode_object_get_properties(काष्ठा drm_mode_object *obj, bool atomic,
				   uपूर्णांक32_t __user *prop_ptr,
				   uपूर्णांक64_t __user *prop_values,
				   uपूर्णांक32_t *arg_count_props);
काष्ठा drm_property *drm_mode_obj_find_prop_id(काष्ठा drm_mode_object *obj,
					       uपूर्णांक32_t prop_id);

/* IOCTL */

पूर्णांक drm_mode_obj_get_properties_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_obj_set_property_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);

/* drm_encoder.c */
पूर्णांक drm_encoder_रेजिस्टर_all(काष्ठा drm_device *dev);
व्योम drm_encoder_unरेजिस्टर_all(काष्ठा drm_device *dev);

/* IOCTL */
पूर्णांक drm_mode_getencoder(काष्ठा drm_device *dev,
			व्योम *data, काष्ठा drm_file *file_priv);

/* drm_connector.c */
व्योम drm_connector_ida_init(व्योम);
व्योम drm_connector_ida_destroy(व्योम);
व्योम drm_connector_unरेजिस्टर_all(काष्ठा drm_device *dev);
पूर्णांक drm_connector_रेजिस्टर_all(काष्ठा drm_device *dev);
पूर्णांक drm_connector_set_obj_prop(काष्ठा drm_mode_object *obj,
				    काष्ठा drm_property *property,
				    uपूर्णांक64_t value);
पूर्णांक drm_connector_create_standard_properties(काष्ठा drm_device *dev);
स्थिर अक्षर *drm_get_connector_क्रमce_name(क्रमागत drm_connector_क्रमce क्रमce);
व्योम drm_connector_मुक्त_work_fn(काष्ठा work_काष्ठा *work);

/* IOCTL */
पूर्णांक drm_connector_property_set_ioctl(काष्ठा drm_device *dev,
				     व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_अ_लोonnector(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv);

/* drm_framebuffer.c */
काष्ठा drm_framebuffer *
drm_पूर्णांकernal_framebuffer_create(काष्ठा drm_device *dev,
				स्थिर काष्ठा drm_mode_fb_cmd2 *r,
				काष्ठा drm_file *file_priv);
व्योम drm_framebuffer_मुक्त(काष्ठा kref *kref);
पूर्णांक drm_framebuffer_check_src_coords(uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
				     uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
				     स्थिर काष्ठा drm_framebuffer *fb);
व्योम drm_fb_release(काष्ठा drm_file *file_priv);

पूर्णांक drm_mode_addfb(काष्ठा drm_device *dev, काष्ठा drm_mode_fb_cmd *or,
		   काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_addfb2(काष्ठा drm_device *dev,
		    व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_rmfb(काष्ठा drm_device *dev, u32 fb_id,
		  काष्ठा drm_file *file_priv);


/* IOCTL */
पूर्णांक drm_mode_addfb_ioctl(काष्ठा drm_device *dev,
			 व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_addfb2_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_rmfb_ioctl(काष्ठा drm_device *dev,
			व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_getfb(काष्ठा drm_device *dev,
		   व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_getfb2_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_dirtyfb_ioctl(काष्ठा drm_device *dev,
			   व्योम *data, काष्ठा drm_file *file_priv);

/* drm_atomic.c */
#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा drm_minor;
व्योम drm_atomic_debugfs_init(काष्ठा drm_minor *minor);
#पूर्ण_अगर

पूर्णांक __drm_atomic_helper_disable_plane(काष्ठा drm_plane *plane,
				      काष्ठा drm_plane_state *plane_state);
पूर्णांक __drm_atomic_helper_set_config(काष्ठा drm_mode_set *set,
				   काष्ठा drm_atomic_state *state);

व्योम drm_atomic_prपूर्णांक_state(स्थिर काष्ठा drm_atomic_state *state);

/* drm_atomic_uapi.c */
पूर्णांक drm_atomic_connector_commit_dpms(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_connector *connector,
				     पूर्णांक mode);
पूर्णांक drm_atomic_set_property(काष्ठा drm_atomic_state *state,
			    काष्ठा drm_file *file_priv,
			    काष्ठा drm_mode_object *obj,
			    काष्ठा drm_property *prop,
			    uपूर्णांक64_t prop_value);
पूर्णांक drm_atomic_get_property(काष्ठा drm_mode_object *obj,
			    काष्ठा drm_property *property, uपूर्णांक64_t *val);

/* IOCTL */
पूर्णांक drm_mode_atomic_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv);


/* drm_plane.c */
पूर्णांक drm_plane_रेजिस्टर_all(काष्ठा drm_device *dev);
व्योम drm_plane_unरेजिस्टर_all(काष्ठा drm_device *dev);
पूर्णांक drm_plane_check_pixel_क्रमmat(काष्ठा drm_plane *plane,
				 u32 क्रमmat, u64 modअगरier);

/* drm_bridge.c */
व्योम drm_bridge_detach(काष्ठा drm_bridge *bridge);

/* IOCTL */
पूर्णांक drm_mode_getplane_res(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_getplane(काष्ठा drm_device *dev,
		      व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_setplane(काष्ठा drm_device *dev,
		      व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_cursor_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_cursor2_ioctl(काष्ठा drm_device *dev,
			   व्योम *data, काष्ठा drm_file *file_priv);
पूर्णांक drm_mode_page_flip_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *file_priv);

/* drm_edid.c */
व्योम drm_mode_fixup_1366x768(काष्ठा drm_display_mode *mode);
व्योम drm_reset_display_info(काष्ठा drm_connector *connector);
u32 drm_add_display_info(काष्ठा drm_connector *connector, स्थिर काष्ठा edid *edid);
व्योम drm_update_tile_info(काष्ठा drm_connector *connector, स्थिर काष्ठा edid *edid);
