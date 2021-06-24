<शैली गुरु>
/*
 * Copyright 2013 Ilia Mirkin
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
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Implementation based on the pre-KMS implementation in xf86-video-nouveau,
 * written by Arthur Huillet.
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "nouveau_drv.h"

#समावेश "nouveau_bo.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_display.h"
#समावेश "nouveau_gem.h"
#समावेश "nvreg.h"
#समावेश "disp.h"

काष्ठा nouveau_plane अणु
	काष्ठा drm_plane base;
	bool flip;
	काष्ठा nouveau_bo *cur;

	काष्ठा अणु
		काष्ठा drm_property *colorkey;
		काष्ठा drm_property *contrast;
		काष्ठा drm_property *brightness;
		काष्ठा drm_property *hue;
		काष्ठा drm_property *saturation;
	पूर्ण props;

	पूर्णांक colorkey;
	पूर्णांक contrast;
	पूर्णांक brightness;
	पूर्णांक hue;
	पूर्णांक saturation;
	क्रमागत drm_color_encoding color_encoding;

	व्योम (*set_params)(काष्ठा nouveau_plane *);
पूर्ण;

अटल uपूर्णांक32_t क्रमmats[] = अणु
	DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV21,
पूर्ण;

/* Sine can be approximated with
 * http://en.wikipedia.org/wiki/Bhaskara_I's_sine_approximation_क्रमmula
 * sin(x degrees) ~= 4 x (180 - x) / (40500 - x (180 - x) )
 * Note that this only works क्रम the range [0, 180].
 * Also note that sin(x) == -sin(x - 180)
 */
अटल अंतरभूत पूर्णांक
sin_mul(पूर्णांक degrees, पूर्णांक factor)
अणु
	अगर (degrees > 180) अणु
		degrees -= 180;
		factor *= -1;
	पूर्ण
	वापस factor * 4 * degrees * (180 - degrees) /
		(40500 - degrees * (180 - degrees));
पूर्ण

/* cos(x) = sin(x + 90) */
अटल अंतरभूत पूर्णांक
cos_mul(पूर्णांक degrees, पूर्णांक factor)
अणु
	वापस sin_mul((degrees + 90) % 360, factor);
पूर्ण

अटल पूर्णांक
verअगरy_scaling(स्थिर काष्ठा drm_framebuffer *fb, uपूर्णांक8_t shअगरt,
               uपूर्णांक32_t src_x, uपूर्णांक32_t src_y, uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
               uपूर्णांक32_t crtc_w, uपूर्णांक32_t crtc_h)
अणु
	अगर (crtc_w < (src_w >> shअगरt) || crtc_h < (src_h >> shअगरt)) अणु
		DRM_DEBUG_KMS("Unsuitable framebuffer scaling: %dx%d -> %dx%d\n",
			      src_w, src_h, crtc_w, crtc_h);
		वापस -दुस्फल;
	पूर्ण

	अगर (src_x != 0 || src_y != 0) अणु
		DRM_DEBUG_KMS("Unsuitable framebuffer offset: %d,%d\n",
                              src_x, src_y);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv10_update_plane(काष्ठा drm_plane *plane, काष्ठा drm_crtc *crtc,
		  काष्ठा drm_framebuffer *fb, पूर्णांक crtc_x, पूर्णांक crtc_y,
		  अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
		  uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
		  uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
		  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(plane->dev);
	काष्ठा nvअगर_object *dev = &drm->client.device.object;
	काष्ठा nouveau_plane *nv_plane =
		container_of(plane, काष्ठा nouveau_plane, base);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	काष्ठा nouveau_bo *cur = nv_plane->cur;
	काष्ठा nouveau_bo *nvbo;
	bool flip = nv_plane->flip;
	पूर्णांक soff = NV_PCRTC0_SIZE * nv_crtc->index;
	पूर्णांक soff2 = NV_PCRTC0_SIZE * !nv_crtc->index;
	अचिन्हित shअगरt = drm->client.device.info.chipset >= 0x30 ? 1 : 3;
	अचिन्हित क्रमmat = 0;
	पूर्णांक ret;

	/* Source parameters given in 16.16 fixed poपूर्णांक, ignore fractional. */
	src_x >>= 16;
	src_y >>= 16;
	src_w >>= 16;
	src_h >>= 16;

	ret = verअगरy_scaling(fb, shअगरt, 0, 0, src_w, src_h, crtc_w, crtc_h);
	अगर (ret)
		वापस ret;

	nvbo = nouveau_gem_object(fb->obj[0]);
	ret = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VRAM, false);
	अगर (ret)
		वापस ret;

	nv_plane->cur = nvbo;

	nvअगर_mask(dev, NV_PCRTC_ENGINE_CTRL + soff, NV_CRTC_FSEL_OVERLAY, NV_CRTC_FSEL_OVERLAY);
	nvअगर_mask(dev, NV_PCRTC_ENGINE_CTRL + soff2, NV_CRTC_FSEL_OVERLAY, 0);

	nvअगर_wr32(dev, NV_PVIDEO_BASE(flip), 0);
	nvअगर_wr32(dev, NV_PVIDEO_OFFSET_BUFF(flip), nvbo->offset);
	nvअगर_wr32(dev, NV_PVIDEO_SIZE_IN(flip), src_h << 16 | src_w);
	nvअगर_wr32(dev, NV_PVIDEO_POINT_IN(flip), src_y << 16 | src_x);
	nvअगर_wr32(dev, NV_PVIDEO_DS_DX(flip), (src_w << 20) / crtc_w);
	nvअगर_wr32(dev, NV_PVIDEO_DT_DY(flip), (src_h << 20) / crtc_h);
	nvअगर_wr32(dev, NV_PVIDEO_POINT_OUT(flip), crtc_y << 16 | crtc_x);
	nvअगर_wr32(dev, NV_PVIDEO_SIZE_OUT(flip), crtc_h << 16 | crtc_w);

	अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_YUYV ||
	    fb->क्रमmat->क्रमmat == DRM_FORMAT_NV12)
		क्रमmat |= NV_PVIDEO_FORMAT_COLOR_LE_CR8YB8CB8YA8;
	अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_NV12 ||
	    fb->क्रमmat->क्रमmat == DRM_FORMAT_NV21)
		क्रमmat |= NV_PVIDEO_FORMAT_PLANAR;
	अगर (nv_plane->color_encoding == DRM_COLOR_YCBCR_BT709)
		क्रमmat |= NV_PVIDEO_FORMAT_MATRIX_ITURBT709;
	अगर (nv_plane->colorkey & (1 << 24))
		क्रमmat |= NV_PVIDEO_FORMAT_DISPLAY_COLOR_KEY;

	अगर (क्रमmat & NV_PVIDEO_FORMAT_PLANAR) अणु
		nvअगर_wr32(dev, NV_PVIDEO_UVPLANE_BASE(flip), 0);
		nvअगर_wr32(dev, NV_PVIDEO_UVPLANE_OFFSET_BUFF(flip),
			nvbo->offset + fb->offsets[1]);
	पूर्ण
	nvअगर_wr32(dev, NV_PVIDEO_FORMAT(flip), क्रमmat | fb->pitches[0]);
	nvअगर_wr32(dev, NV_PVIDEO_STOP, 0);
	/* TODO: रुको क्रम vblank? */
	nvअगर_wr32(dev, NV_PVIDEO_BUFFER, flip ? 0x10 : 0x1);
	nv_plane->flip = !flip;

	अगर (cur)
		nouveau_bo_unpin(cur);

	वापस 0;
पूर्ण

अटल पूर्णांक
nv10_disable_plane(काष्ठा drm_plane *plane,
		   काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा nvअगर_object *dev = &nouveau_drm(plane->dev)->client.device.object;
	काष्ठा nouveau_plane *nv_plane =
		container_of(plane, काष्ठा nouveau_plane, base);

	nvअगर_wr32(dev, NV_PVIDEO_STOP, 1);
	अगर (nv_plane->cur) अणु
		nouveau_bo_unpin(nv_plane->cur);
		nv_plane->cur = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nv_destroy_plane(काष्ठा drm_plane *plane)
अणु
	drm_plane_क्रमce_disable(plane);
	drm_plane_cleanup(plane);
	kमुक्त(plane);
पूर्ण

अटल व्योम
nv10_set_params(काष्ठा nouveau_plane *plane)
अणु
	काष्ठा nvअगर_object *dev = &nouveau_drm(plane->base.dev)->client.device.object;
	u32 luma = (plane->brightness - 512) << 16 | plane->contrast;
	u32 chroma = ((sin_mul(plane->hue, plane->saturation) & 0xffff) << 16) |
		(cos_mul(plane->hue, plane->saturation) & 0xffff);
	u32 क्रमmat = 0;

	nvअगर_wr32(dev, NV_PVIDEO_LUMIन_अंकCE(0), luma);
	nvअगर_wr32(dev, NV_PVIDEO_LUMIन_अंकCE(1), luma);
	nvअगर_wr32(dev, NV_PVIDEO_CHROMIन_अंकCE(0), chroma);
	nvअगर_wr32(dev, NV_PVIDEO_CHROMIन_अंकCE(1), chroma);
	nvअगर_wr32(dev, NV_PVIDEO_COLOR_KEY, plane->colorkey & 0xffffff);

	अगर (plane->cur) अणु
		अगर (plane->color_encoding == DRM_COLOR_YCBCR_BT709)
			क्रमmat |= NV_PVIDEO_FORMAT_MATRIX_ITURBT709;
		अगर (plane->colorkey & (1 << 24))
			क्रमmat |= NV_PVIDEO_FORMAT_DISPLAY_COLOR_KEY;
		nvअगर_mask(dev, NV_PVIDEO_FORMAT(plane->flip),
			NV_PVIDEO_FORMAT_MATRIX_ITURBT709 |
			NV_PVIDEO_FORMAT_DISPLAY_COLOR_KEY,
			क्रमmat);
	पूर्ण
पूर्ण

अटल पूर्णांक
nv_set_property(काष्ठा drm_plane *plane,
		काष्ठा drm_property *property,
		uपूर्णांक64_t value)
अणु
	काष्ठा nouveau_plane *nv_plane =
		container_of(plane, काष्ठा nouveau_plane, base);

	अगर (property == nv_plane->props.colorkey)
		nv_plane->colorkey = value;
	अन्यथा अगर (property == nv_plane->props.contrast)
		nv_plane->contrast = value;
	अन्यथा अगर (property == nv_plane->props.brightness)
		nv_plane->brightness = value;
	अन्यथा अगर (property == nv_plane->props.hue)
		nv_plane->hue = value;
	अन्यथा अगर (property == nv_plane->props.saturation)
		nv_plane->saturation = value;
	अन्यथा अगर (property == nv_plane->base.color_encoding_property)
		nv_plane->color_encoding = value;
	अन्यथा
		वापस -EINVAL;

	अगर (nv_plane->set_params)
		nv_plane->set_params(nv_plane);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs nv10_plane_funcs = अणु
	.update_plane = nv10_update_plane,
	.disable_plane = nv10_disable_plane,
	.set_property = nv_set_property,
	.destroy = nv_destroy_plane,
पूर्ण;

अटल व्योम
nv10_overlay_init(काष्ठा drm_device *device)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(device);
	काष्ठा nouveau_plane *plane = kzalloc(माप(काष्ठा nouveau_plane), GFP_KERNEL);
	अचिन्हित पूर्णांक num_क्रमmats = ARRAY_SIZE(क्रमmats);
	पूर्णांक ret;

	अगर (!plane)
		वापस;

	चयन (drm->client.device.info.chipset) अणु
	हाल 0x10:
	हाल 0x11:
	हाल 0x15:
	हाल 0x1a:
	हाल 0x20:
		num_क्रमmats = 2;
		अवरोध;
	पूर्ण

	ret = drm_plane_init(device, &plane->base, 3 /* both crtc's */,
			     &nv10_plane_funcs,
			     क्रमmats, num_क्रमmats, false);
	अगर (ret)
		जाओ err;

	/* Set up the plane properties */
	plane->props.colorkey = drm_property_create_range(
			device, 0, "colorkey", 0, 0x01ffffff);
	plane->props.contrast = drm_property_create_range(
			device, 0, "contrast", 0, 8192 - 1);
	plane->props.brightness = drm_property_create_range(
			device, 0, "brightness", 0, 1024);
	plane->props.hue = drm_property_create_range(
			device, 0, "hue", 0, 359);
	plane->props.saturation = drm_property_create_range(
			device, 0, "saturation", 0, 8192 - 1);
	अगर (!plane->props.colorkey ||
	    !plane->props.contrast ||
	    !plane->props.brightness ||
	    !plane->props.hue ||
	    !plane->props.saturation)
		जाओ cleanup;

	plane->colorkey = 0;
	drm_object_attach_property(&plane->base.base,
				   plane->props.colorkey, plane->colorkey);

	plane->contrast = 0x1000;
	drm_object_attach_property(&plane->base.base,
				   plane->props.contrast, plane->contrast);

	plane->brightness = 512;
	drm_object_attach_property(&plane->base.base,
				   plane->props.brightness, plane->brightness);

	plane->hue = 0;
	drm_object_attach_property(&plane->base.base,
				   plane->props.hue, plane->hue);

	plane->saturation = 0x1000;
	drm_object_attach_property(&plane->base.base,
				   plane->props.saturation, plane->saturation);

	plane->color_encoding = DRM_COLOR_YCBCR_BT601;
	drm_plane_create_color_properties(&plane->base,
					  BIT(DRM_COLOR_YCBCR_BT601) |
					  BIT(DRM_COLOR_YCBCR_BT709),
					  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE),
					  DRM_COLOR_YCBCR_BT601,
					  DRM_COLOR_YCBCR_LIMITED_RANGE);

	plane->set_params = nv10_set_params;
	nv10_set_params(plane);
	drm_plane_क्रमce_disable(&plane->base);
	वापस;
cleanup:
	drm_plane_cleanup(&plane->base);
err:
	kमुक्त(plane);
	NV_ERROR(drm, "Failed to create plane\n");
पूर्ण

अटल पूर्णांक
nv04_update_plane(काष्ठा drm_plane *plane, काष्ठा drm_crtc *crtc,
		  काष्ठा drm_framebuffer *fb, पूर्णांक crtc_x, पूर्णांक crtc_y,
		  अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
		  uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
		  uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
		  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा nvअगर_object *dev = &nouveau_drm(plane->dev)->client.device.object;
	काष्ठा nouveau_plane *nv_plane =
		container_of(plane, काष्ठा nouveau_plane, base);
	काष्ठा nouveau_bo *cur = nv_plane->cur;
	काष्ठा nouveau_bo *nvbo;
	uपूर्णांक32_t overlay = 1;
	पूर्णांक brightness = (nv_plane->brightness - 512) * 62 / 512;
	पूर्णांक ret, i;

	/* Source parameters given in 16.16 fixed poपूर्णांक, ignore fractional. */
	src_x >>= 16;
	src_y >>= 16;
	src_w >>= 16;
	src_h >>= 16;

	ret = verअगरy_scaling(fb, 0, src_x, src_y, src_w, src_h, crtc_w, crtc_h);
	अगर (ret)
		वापस ret;

	nvbo = nouveau_gem_object(fb->obj[0]);
	ret = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VRAM, false);
	अगर (ret)
		वापस ret;

	nv_plane->cur = nvbo;

	nvअगर_wr32(dev, NV_PVIDEO_OE_STATE, 0);
	nvअगर_wr32(dev, NV_PVIDEO_SU_STATE, 0);
	nvअगर_wr32(dev, NV_PVIDEO_RM_STATE, 0);

	क्रम (i = 0; i < 2; i++) अणु
		nvअगर_wr32(dev, NV_PVIDEO_BUFF0_START_ADDRESS + 4 * i,
			  nvbo->offset);
		nvअगर_wr32(dev, NV_PVIDEO_BUFF0_PITCH_LENGTH + 4 * i,
			  fb->pitches[0]);
		nvअगर_wr32(dev, NV_PVIDEO_BUFF0_OFFSET + 4 * i, 0);
	पूर्ण
	nvअगर_wr32(dev, NV_PVIDEO_WINDOW_START, crtc_y << 16 | crtc_x);
	nvअगर_wr32(dev, NV_PVIDEO_WINDOW_SIZE, crtc_h << 16 | crtc_w);
	nvअगर_wr32(dev, NV_PVIDEO_STEP_SIZE,
		(uपूर्णांक32_t)(((src_h - 1) << 11) / (crtc_h - 1)) << 16 | (uपूर्णांक32_t)(((src_w - 1) << 11) / (crtc_w - 1)));

	/* It should be possible to convert hue/contrast to this */
	nvअगर_wr32(dev, NV_PVIDEO_RED_CSC_OFFSET, 0x69 - brightness);
	nvअगर_wr32(dev, NV_PVIDEO_GREEN_CSC_OFFSET, 0x3e + brightness);
	nvअगर_wr32(dev, NV_PVIDEO_BLUE_CSC_OFFSET, 0x89 - brightness);
	nvअगर_wr32(dev, NV_PVIDEO_CSC_ADJUST, 0);

	nvअगर_wr32(dev, NV_PVIDEO_CONTROL_Y, 0x001); /* (BLUR_ON, LINE_HALF) */
	nvअगर_wr32(dev, NV_PVIDEO_CONTROL_X, 0x111); /* (WEIGHT_HEAVY, SHARPENING_ON, SMOOTHING_ON) */

	nvअगर_wr32(dev, NV_PVIDEO_FIFO_BURST_LENGTH, 0x03);
	nvअगर_wr32(dev, NV_PVIDEO_FIFO_THRES_SIZE, 0x38);

	nvअगर_wr32(dev, NV_PVIDEO_KEY, nv_plane->colorkey);

	अगर (nv_plane->colorkey & (1 << 24))
		overlay |= 0x10;
	अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_YUYV)
		overlay |= 0x100;

	nvअगर_wr32(dev, NV_PVIDEO_OVERLAY, overlay);

	nvअगर_wr32(dev, NV_PVIDEO_SU_STATE, nvअगर_rd32(dev, NV_PVIDEO_SU_STATE) ^ (1 << 16));

	अगर (cur)
		nouveau_bo_unpin(cur);

	वापस 0;
पूर्ण

अटल पूर्णांक
nv04_disable_plane(काष्ठा drm_plane *plane,
		   काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा nvअगर_object *dev = &nouveau_drm(plane->dev)->client.device.object;
	काष्ठा nouveau_plane *nv_plane =
		container_of(plane, काष्ठा nouveau_plane, base);

	nvअगर_mask(dev, NV_PVIDEO_OVERLAY, 1, 0);
	nvअगर_wr32(dev, NV_PVIDEO_OE_STATE, 0);
	nvअगर_wr32(dev, NV_PVIDEO_SU_STATE, 0);
	nvअगर_wr32(dev, NV_PVIDEO_RM_STATE, 0);
	अगर (nv_plane->cur) अणु
		nouveau_bo_unpin(nv_plane->cur);
		nv_plane->cur = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs nv04_plane_funcs = अणु
	.update_plane = nv04_update_plane,
	.disable_plane = nv04_disable_plane,
	.set_property = nv_set_property,
	.destroy = nv_destroy_plane,
पूर्ण;

अटल व्योम
nv04_overlay_init(काष्ठा drm_device *device)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(device);
	काष्ठा nouveau_plane *plane = kzalloc(माप(काष्ठा nouveau_plane), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!plane)
		वापस;

	ret = drm_plane_init(device, &plane->base, 1 /* single crtc */,
			     &nv04_plane_funcs,
			     क्रमmats, 2, false);
	अगर (ret)
		जाओ err;

	/* Set up the plane properties */
	plane->props.colorkey = drm_property_create_range(
			device, 0, "colorkey", 0, 0x01ffffff);
	plane->props.brightness = drm_property_create_range(
			device, 0, "brightness", 0, 1024);
	अगर (!plane->props.colorkey ||
	    !plane->props.brightness)
		जाओ cleanup;

	plane->colorkey = 0;
	drm_object_attach_property(&plane->base.base,
				   plane->props.colorkey, plane->colorkey);

	plane->brightness = 512;
	drm_object_attach_property(&plane->base.base,
				   plane->props.brightness, plane->brightness);

	drm_plane_क्रमce_disable(&plane->base);
	वापस;
cleanup:
	drm_plane_cleanup(&plane->base);
err:
	kमुक्त(plane);
	NV_ERROR(drm, "Failed to create plane\n");
पूर्ण

व्योम
nouveau_overlay_init(काष्ठा drm_device *device)
अणु
	काष्ठा nvअगर_device *dev = &nouveau_drm(device)->client.device;
	अगर (dev->info.chipset < 0x10)
		nv04_overlay_init(device);
	अन्यथा अगर (dev->info.chipset <= 0x40)
		nv10_overlay_init(device);
पूर्ण
