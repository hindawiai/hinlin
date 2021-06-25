<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Authors:
 *    Dave Airlie
 *    Alon Levy
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

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "virtgpu_drv.h"

#घोषणा XRES_MIN    32
#घोषणा YRES_MIN    32

#घोषणा XRES_DEF  1024
#घोषणा YRES_DEF   768

#घोषणा XRES_MAX  8192
#घोषणा YRES_MAX  8192

#घोषणा drm_connector_to_virtio_gpu_output(x) \
	container_of(x, काष्ठा virtio_gpu_output, conn)

अटल स्थिर काष्ठा drm_crtc_funcs virtio_gpu_crtc_funcs = अणु
	.set_config             = drm_atomic_helper_set_config,
	.destroy                = drm_crtc_cleanup,

	.page_flip              = drm_atomic_helper_page_flip,
	.reset                  = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state   = drm_atomic_helper_crtc_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_framebuffer_funcs virtio_gpu_fb_funcs = अणु
	.create_handle = drm_gem_fb_create_handle,
	.destroy = drm_gem_fb_destroy,
	.dirty = drm_atomic_helper_dirtyfb,
पूर्ण;

अटल पूर्णांक
virtio_gpu_framebuffer_init(काष्ठा drm_device *dev,
			    काष्ठा virtio_gpu_framebuffer *vgfb,
			    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			    काष्ठा drm_gem_object *obj)
अणु
	पूर्णांक ret;

	vgfb->base.obj[0] = obj;

	drm_helper_mode_fill_fb_काष्ठा(dev, &vgfb->base, mode_cmd);

	ret = drm_framebuffer_init(dev, &vgfb->base, &virtio_gpu_fb_funcs);
	अगर (ret) अणु
		vgfb->base.obj[0] = शून्य;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम virtio_gpu_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_output *output = drm_crtc_to_virtio_gpu_output(crtc);

	virtio_gpu_cmd_set_scanout(vgdev, output->index, 0,
				   crtc->mode.hdisplay,
				   crtc->mode.vdisplay, 0, 0);
	virtio_gpu_notअगरy(vgdev);
पूर्ण

अटल व्योम virtio_gpu_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल व्योम virtio_gpu_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_output *output = drm_crtc_to_virtio_gpu_output(crtc);

	virtio_gpu_cmd_set_scanout(vgdev, output->index, 0, 0, 0, 0, 0);
	virtio_gpu_notअगरy(vgdev);
पूर्ण

अटल पूर्णांक virtio_gpu_crtc_atomic_check(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	वापस 0;
पूर्ण

अटल व्योम virtio_gpu_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा virtio_gpu_output *output = drm_crtc_to_virtio_gpu_output(crtc);

	/*
	 * virtio-gpu can't करो modeset and plane update operations
	 * independent from each other.  So the actual modeset happens
	 * in the plane update callback, and here we just check
	 * whenever we must क्रमce the modeset.
	 */
	अगर (drm_atomic_crtc_needs_modeset(crtc_state)) अणु
		output->needs_modeset = true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs virtio_gpu_crtc_helper_funcs = अणु
	.mode_set_nofb = virtio_gpu_crtc_mode_set_nofb,
	.atomic_check  = virtio_gpu_crtc_atomic_check,
	.atomic_flush  = virtio_gpu_crtc_atomic_flush,
	.atomic_enable = virtio_gpu_crtc_atomic_enable,
	.atomic_disable = virtio_gpu_crtc_atomic_disable,
पूर्ण;

अटल व्योम virtio_gpu_enc_mode_set(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adjusted_mode)
अणु
पूर्ण

अटल व्योम virtio_gpu_enc_enable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण

अटल व्योम virtio_gpu_enc_disable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण

अटल पूर्णांक virtio_gpu_conn_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा virtio_gpu_output *output =
		drm_connector_to_virtio_gpu_output(connector);
	काष्ठा drm_display_mode *mode = शून्य;
	पूर्णांक count, width, height;

	अगर (output->edid) अणु
		count = drm_add_edid_modes(connector, output->edid);
		अगर (count)
			वापस count;
	पूर्ण

	width  = le32_to_cpu(output->info.r.width);
	height = le32_to_cpu(output->info.r.height);
	count = drm_add_modes_noedid(connector, XRES_MAX, YRES_MAX);

	अगर (width == 0 || height == 0) अणु
		drm_set_preferred_mode(connector, XRES_DEF, YRES_DEF);
	पूर्ण अन्यथा अणु
		DRM_DEBUG("add mode: %dx%d\n", width, height);
		mode = drm_cvt_mode(connector->dev, width, height, 60,
				    false, false, false);
		mode->type |= DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल क्रमागत drm_mode_status virtio_gpu_conn_mode_valid(काष्ठा drm_connector *connector,
				      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा virtio_gpu_output *output =
		drm_connector_to_virtio_gpu_output(connector);
	पूर्णांक width, height;

	width  = le32_to_cpu(output->info.r.width);
	height = le32_to_cpu(output->info.r.height);

	अगर (!(mode->type & DRM_MODE_TYPE_PREFERRED))
		वापस MODE_OK;
	अगर (mode->hdisplay == XRES_DEF && mode->vdisplay == YRES_DEF)
		वापस MODE_OK;
	अगर (mode->hdisplay <= width  && mode->hdisplay >= width - 16 &&
	    mode->vdisplay <= height && mode->vdisplay >= height - 16)
		वापस MODE_OK;

	DRM_DEBUG("del mode: %dx%d\n", mode->hdisplay, mode->vdisplay);
	वापस MODE_BAD;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs virtio_gpu_enc_helper_funcs = अणु
	.mode_set   = virtio_gpu_enc_mode_set,
	.enable     = virtio_gpu_enc_enable,
	.disable    = virtio_gpu_enc_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs virtio_gpu_conn_helper_funcs = अणु
	.get_modes    = virtio_gpu_conn_get_modes,
	.mode_valid   = virtio_gpu_conn_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status virtio_gpu_conn_detect(
			काष्ठा drm_connector *connector,
			bool क्रमce)
अणु
	काष्ठा virtio_gpu_output *output =
		drm_connector_to_virtio_gpu_output(connector);

	अगर (output->info.enabled)
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_disconnected;
पूर्ण

अटल व्योम virtio_gpu_conn_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs virtio_gpu_connector_funcs = अणु
	.detect = virtio_gpu_conn_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = virtio_gpu_conn_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक vgdev_output_init(काष्ठा virtio_gpu_device *vgdev, पूर्णांक index)
अणु
	काष्ठा drm_device *dev = vgdev->ddev;
	काष्ठा virtio_gpu_output *output = vgdev->outमाला_दो + index;
	काष्ठा drm_connector *connector = &output->conn;
	काष्ठा drm_encoder *encoder = &output->enc;
	काष्ठा drm_crtc *crtc = &output->crtc;
	काष्ठा drm_plane *primary, *cursor;

	output->index = index;
	अगर (index == 0) अणु
		output->info.enabled = cpu_to_le32(true);
		output->info.r.width = cpu_to_le32(XRES_DEF);
		output->info.r.height = cpu_to_le32(YRES_DEF);
	पूर्ण

	primary = virtio_gpu_plane_init(vgdev, DRM_PLANE_TYPE_PRIMARY, index);
	अगर (IS_ERR(primary))
		वापस PTR_ERR(primary);
	cursor = virtio_gpu_plane_init(vgdev, DRM_PLANE_TYPE_CURSOR, index);
	अगर (IS_ERR(cursor))
		वापस PTR_ERR(cursor);
	drm_crtc_init_with_planes(dev, crtc, primary, cursor,
				  &virtio_gpu_crtc_funcs, शून्य);
	drm_crtc_helper_add(crtc, &virtio_gpu_crtc_helper_funcs);

	drm_connector_init(dev, connector, &virtio_gpu_connector_funcs,
			   DRM_MODE_CONNECTOR_VIRTUAL);
	drm_connector_helper_add(connector, &virtio_gpu_conn_helper_funcs);
	अगर (vgdev->has_edid)
		drm_connector_attach_edid_property(connector);

	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_VIRTUAL);
	drm_encoder_helper_add(encoder, &virtio_gpu_enc_helper_funcs);
	encoder->possible_crtcs = 1 << index;

	drm_connector_attach_encoder(connector, encoder);
	drm_connector_रेजिस्टर(connector);
	वापस 0;
पूर्ण

अटल काष्ठा drm_framebuffer *
virtio_gpu_user_framebuffer_create(काष्ठा drm_device *dev,
				   काष्ठा drm_file *file_priv,
				   स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_gem_object *obj = शून्य;
	काष्ठा virtio_gpu_framebuffer *virtio_gpu_fb;
	पूर्णांक ret;

	अगर (mode_cmd->pixel_क्रमmat != DRM_FORMAT_HOST_XRGB8888 &&
	    mode_cmd->pixel_क्रमmat != DRM_FORMAT_HOST_ARGB8888)
		वापस ERR_PTR(-ENOENT);

	/* lookup object associated with res handle */
	obj = drm_gem_object_lookup(file_priv, mode_cmd->handles[0]);
	अगर (!obj)
		वापस ERR_PTR(-EINVAL);

	virtio_gpu_fb = kzalloc(माप(*virtio_gpu_fb), GFP_KERNEL);
	अगर (virtio_gpu_fb == शून्य)
		वापस ERR_PTR(-ENOMEM);

	ret = virtio_gpu_framebuffer_init(dev, virtio_gpu_fb, mode_cmd, obj);
	अगर (ret) अणु
		kमुक्त(virtio_gpu_fb);
		drm_gem_object_put(obj);
		वापस शून्य;
	पूर्ण

	वापस &virtio_gpu_fb->base;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs virtio_gpu_mode_funcs = अणु
	.fb_create = virtio_gpu_user_framebuffer_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

पूर्णांक virtio_gpu_modeset_init(काष्ठा virtio_gpu_device *vgdev)
अणु
	पूर्णांक i, ret;

	ret = drmm_mode_config_init(vgdev->ddev);
	अगर (ret)
		वापस ret;

	vgdev->ddev->mode_config.quirk_addfb_prefer_host_byte_order = true;
	vgdev->ddev->mode_config.funcs = &virtio_gpu_mode_funcs;

	/* modes will be validated against the framebuffer size */
	vgdev->ddev->mode_config.min_width = XRES_MIN;
	vgdev->ddev->mode_config.min_height = YRES_MIN;
	vgdev->ddev->mode_config.max_width = XRES_MAX;
	vgdev->ddev->mode_config.max_height = YRES_MAX;

	क्रम (i = 0 ; i < vgdev->num_scanouts; ++i)
		vgdev_output_init(vgdev, i);

	drm_mode_config_reset(vgdev->ddev);
	वापस 0;
पूर्ण

व्योम virtio_gpu_modeset_fini(काष्ठा virtio_gpu_device *vgdev)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < vgdev->num_scanouts; ++i)
		kमुक्त(vgdev->outमाला_दो[i].edid);
पूर्ण
