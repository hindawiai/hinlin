<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MIPI Display Bus Interface (DBI) LCD controller support
 *
 * Copyright 2016 Noralf Trथचnnes
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_mipi_dbi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_rect.h>
#समावेश <video/mipi_display.h>

#घोषणा MIPI_DBI_MAX_SPI_READ_SPEED 2000000 /* 2MHz */

#घोषणा DCS_POWER_MODE_DISPLAY			BIT(2)
#घोषणा DCS_POWER_MODE_DISPLAY_NORMAL_MODE	BIT(3)
#घोषणा DCS_POWER_MODE_SLEEP_MODE		BIT(4)
#घोषणा DCS_POWER_MODE_PARTIAL_MODE		BIT(5)
#घोषणा DCS_POWER_MODE_IDLE_MODE		BIT(6)
#घोषणा DCS_POWER_MODE_RESERVED_MASK		(BIT(0) | BIT(1) | BIT(7))

/**
 * DOC: overview
 *
 * This library provides helpers क्रम MIPI Display Bus Interface (DBI)
 * compatible display controllers.
 *
 * Many controllers क्रम tiny lcd displays are MIPI compliant and can use this
 * library. If a controller uses रेजिस्टरs 0x2A and 0x2B to set the area to
 * update and uses रेजिस्टर 0x2C to ग_लिखो to frame memory, it is most likely
 * MIPI compliant.
 *
 * Only MIPI Type 1 displays are supported since a full frame memory is needed.
 *
 * There are 3 MIPI DBI implementation types:
 *
 * A. Motorola 6800 type parallel bus
 *
 * B. Intel 8080 type parallel bus
 *
 * C. SPI type with 3 options:
 *
 *    1. 9-bit with the Data/Command संकेत as the nपूर्णांकh bit
 *    2. Same as above except it's sent as 16 bits
 *    3. 8-bit with the Data/Command संकेत as a separate D/CX pin
 *
 * Currently mipi_dbi only supports Type C options 1 and 3 with
 * mipi_dbi_spi_init().
 */

#घोषणा MIPI_DBI_DEBUG_COMMAND(cmd, data, len) \
(अणु \
	अगर (!len) \
		DRM_DEBUG_DRIVER("cmd=%02x\n", cmd); \
	अन्यथा अगर (len <= 32) \
		DRM_DEBUG_DRIVER("cmd=%02x, par=%*ph\n", cmd, (पूर्णांक)len, data);\
	अन्यथा \
		DRM_DEBUG_DRIVER("cmd=%02x, len=%zu\n", cmd, len); \
पूर्ण)

अटल स्थिर u8 mipi_dbi_dcs_पढ़ो_commands[] = अणु
	MIPI_DCS_GET_DISPLAY_ID,
	MIPI_DCS_GET_RED_CHANNEL,
	MIPI_DCS_GET_GREEN_CHANNEL,
	MIPI_DCS_GET_BLUE_CHANNEL,
	MIPI_DCS_GET_DISPLAY_STATUS,
	MIPI_DCS_GET_POWER_MODE,
	MIPI_DCS_GET_ADDRESS_MODE,
	MIPI_DCS_GET_PIXEL_FORMAT,
	MIPI_DCS_GET_DISPLAY_MODE,
	MIPI_DCS_GET_SIGNAL_MODE,
	MIPI_DCS_GET_DIAGNOSTIC_RESULT,
	MIPI_DCS_READ_MEMORY_START,
	MIPI_DCS_READ_MEMORY_CONTINUE,
	MIPI_DCS_GET_SCANLINE,
	MIPI_DCS_GET_DISPLAY_BRIGHTNESS,
	MIPI_DCS_GET_CONTROL_DISPLAY,
	MIPI_DCS_GET_POWER_SAVE,
	MIPI_DCS_GET_CABC_MIN_BRIGHTNESS,
	MIPI_DCS_READ_DDB_START,
	MIPI_DCS_READ_DDB_CONTINUE,
	0, /* sentinel */
पूर्ण;

अटल bool mipi_dbi_command_is_पढ़ो(काष्ठा mipi_dbi *dbi, u8 cmd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!dbi->पढ़ो_commands)
		वापस false;

	क्रम (i = 0; i < 0xff; i++) अणु
		अगर (!dbi->पढ़ो_commands[i])
			वापस false;
		अगर (cmd == dbi->पढ़ो_commands[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * mipi_dbi_command_पढ़ो - MIPI DCS पढ़ो command
 * @dbi: MIPI DBI काष्ठाure
 * @cmd: Command
 * @val: Value पढ़ो
 *
 * Send MIPI DCS पढ़ो command to the controller.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक mipi_dbi_command_पढ़ो(काष्ठा mipi_dbi *dbi, u8 cmd, u8 *val)
अणु
	अगर (!dbi->पढ़ो_commands)
		वापस -EACCES;

	अगर (!mipi_dbi_command_is_पढ़ो(dbi, cmd))
		वापस -EINVAL;

	वापस mipi_dbi_command_buf(dbi, cmd, val, 1);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_command_पढ़ो);

/**
 * mipi_dbi_command_buf - MIPI DCS command with parameter(s) in an array
 * @dbi: MIPI DBI काष्ठाure
 * @cmd: Command
 * @data: Parameter buffer
 * @len: Buffer length
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक mipi_dbi_command_buf(काष्ठा mipi_dbi *dbi, u8 cmd, u8 *data, माप_प्रकार len)
अणु
	u8 *cmdbuf;
	पूर्णांक ret;

	/* SPI requires dma-safe buffers */
	cmdbuf = kmemdup(&cmd, 1, GFP_KERNEL);
	अगर (!cmdbuf)
		वापस -ENOMEM;

	mutex_lock(&dbi->cmdlock);
	ret = dbi->command(dbi, cmdbuf, data, len);
	mutex_unlock(&dbi->cmdlock);

	kमुक्त(cmdbuf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mipi_dbi_command_buf);

/* This should only be used by mipi_dbi_command() */
पूर्णांक mipi_dbi_command_stackbuf(काष्ठा mipi_dbi *dbi, u8 cmd, स्थिर u8 *data,
			      माप_प्रकार len)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(data, len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = mipi_dbi_command_buf(dbi, cmd, buf, len);

	kमुक्त(buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mipi_dbi_command_stackbuf);

/**
 * mipi_dbi_buf_copy - Copy a framebuffer, transक्रमming it अगर necessary
 * @dst: The destination buffer
 * @fb: The source framebuffer
 * @clip: Clipping rectangle of the area to be copied
 * @swap: When true, swap MSB/LSB of 16-bit values
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक mipi_dbi_buf_copy(व्योम *dst, काष्ठा drm_framebuffer *fb,
		      काष्ठा drm_rect *clip, bool swap)
अणु
	काष्ठा drm_gem_object *gem = drm_gem_fb_get_obj(fb, 0);
	काष्ठा drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(gem);
	काष्ठा dma_buf_attachment *import_attach = gem->import_attach;
	व्योम *src = cma_obj->vaddr;
	पूर्णांक ret = 0;

	अगर (import_attach) अणु
		ret = dma_buf_begin_cpu_access(import_attach->dmabuf,
					       DMA_FROM_DEVICE);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
		अगर (swap)
			drm_fb_swab(dst, src, fb, clip, !import_attach);
		अन्यथा
			drm_fb_स_नकल(dst, src, fb, clip);
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		drm_fb_xrgb8888_to_rgb565(dst, src, fb, clip, swap);
		अवरोध;
	शेष:
		drm_err_once(fb->dev, "Format is not supported: %p4cc\n",
			     &fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (import_attach)
		ret = dma_buf_end_cpu_access(import_attach->dmabuf,
					     DMA_FROM_DEVICE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mipi_dbi_buf_copy);

अटल व्योम mipi_dbi_set_winकरोw_address(काष्ठा mipi_dbi_dev *dbidev,
					अचिन्हित पूर्णांक xs, अचिन्हित पूर्णांक xe,
					अचिन्हित पूर्णांक ys, अचिन्हित पूर्णांक ye)
अणु
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;

	xs += dbidev->left_offset;
	xe += dbidev->left_offset;
	ys += dbidev->top_offset;
	ye += dbidev->top_offset;

	mipi_dbi_command(dbi, MIPI_DCS_SET_COLUMN_ADDRESS, (xs >> 8) & 0xff,
			 xs & 0xff, (xe >> 8) & 0xff, xe & 0xff);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PAGE_ADDRESS, (ys >> 8) & 0xff,
			 ys & 0xff, (ye >> 8) & 0xff, ye & 0xff);
पूर्ण

अटल व्योम mipi_dbi_fb_dirty(काष्ठा drm_framebuffer *fb, काष्ठा drm_rect *rect)
अणु
	काष्ठा drm_gem_object *gem = drm_gem_fb_get_obj(fb, 0);
	काष्ठा drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(gem);
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(fb->dev);
	अचिन्हित पूर्णांक height = rect->y2 - rect->y1;
	अचिन्हित पूर्णांक width = rect->x2 - rect->x1;
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	bool swap = dbi->swap_bytes;
	पूर्णांक idx, ret = 0;
	bool full;
	व्योम *tr;

	अगर (WARN_ON(!fb))
		वापस;

	अगर (!drm_dev_enter(fb->dev, &idx))
		वापस;

	full = width == fb->width && height == fb->height;

	DRM_DEBUG_KMS("Flushing [FB:%d] " DRM_RECT_FMT "\n", fb->base.id, DRM_RECT_ARG(rect));

	अगर (!dbi->dc || !full || swap ||
	    fb->क्रमmat->क्रमmat == DRM_FORMAT_XRGB8888) अणु
		tr = dbidev->tx_buf;
		ret = mipi_dbi_buf_copy(dbidev->tx_buf, fb, rect, swap);
		अगर (ret)
			जाओ err_msg;
	पूर्ण अन्यथा अणु
		tr = cma_obj->vaddr;
	पूर्ण

	mipi_dbi_set_winकरोw_address(dbidev, rect->x1, rect->x2 - 1, rect->y1,
				    rect->y2 - 1);

	ret = mipi_dbi_command_buf(dbi, MIPI_DCS_WRITE_MEMORY_START, tr,
				   width * height * 2);
err_msg:
	अगर (ret)
		drm_err_once(fb->dev, "Failed to update display %d\n", ret);

	drm_dev_निकास(idx);
पूर्ण

/**
 * mipi_dbi_pipe_update - Display pipe update helper
 * @pipe: Simple display pipe
 * @old_state: Old plane state
 *
 * This function handles framebuffer flushing and vblank events. Drivers can use
 * this as their &drm_simple_display_pipe_funcs->update callback.
 */
व्योम mipi_dbi_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
			  काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_rect rect;

	अगर (!pipe->crtc.state->active)
		वापस;

	अगर (drm_atomic_helper_damage_merged(old_state, state, &rect))
		mipi_dbi_fb_dirty(state->fb, &rect);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_pipe_update);

/**
 * mipi_dbi_enable_flush - MIPI DBI enable helper
 * @dbidev: MIPI DBI device काष्ठाure
 * @crtc_state: CRTC state
 * @plane_state: Plane state
 *
 * Flushes the whole framebuffer and enables the backlight. Drivers can use this
 * in their &drm_simple_display_pipe_funcs->enable callback.
 *
 * Note: Drivers which करोn't use mipi_dbi_pipe_update() because they have custom
 * framebuffer flushing, can't use this function since they both use the same
 * flushing code.
 */
व्योम mipi_dbi_enable_flush(काष्ठा mipi_dbi_dev *dbidev,
			   काष्ठा drm_crtc_state *crtc_state,
			   काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा drm_rect rect = अणु
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	पूर्ण;
	पूर्णांक idx;

	अगर (!drm_dev_enter(&dbidev->drm, &idx))
		वापस;

	mipi_dbi_fb_dirty(fb, &rect);
	backlight_enable(dbidev->backlight);

	drm_dev_निकास(idx);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_enable_flush);

अटल व्योम mipi_dbi_blank(काष्ठा mipi_dbi_dev *dbidev)
अणु
	काष्ठा drm_device *drm = &dbidev->drm;
	u16 height = drm->mode_config.min_height;
	u16 width = drm->mode_config.min_width;
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	माप_प्रकार len = width * height * 2;
	पूर्णांक idx;

	अगर (!drm_dev_enter(drm, &idx))
		वापस;

	स_रखो(dbidev->tx_buf, 0, len);

	mipi_dbi_set_winकरोw_address(dbidev, 0, width - 1, 0, height - 1);
	mipi_dbi_command_buf(dbi, MIPI_DCS_WRITE_MEMORY_START,
			     (u8 *)dbidev->tx_buf, len);

	drm_dev_निकास(idx);
पूर्ण

/**
 * mipi_dbi_pipe_disable - MIPI DBI pipe disable helper
 * @pipe: Display pipe
 *
 * This function disables backlight अगर present, अगर not the display memory is
 * blanked. The regulator is disabled अगर in use. Drivers can use this as their
 * &drm_simple_display_pipe_funcs->disable callback.
 */
व्योम mipi_dbi_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);

	DRM_DEBUG_KMS("\n");

	अगर (dbidev->backlight)
		backlight_disable(dbidev->backlight);
	अन्यथा
		mipi_dbi_blank(dbidev);

	अगर (dbidev->regulator)
		regulator_disable(dbidev->regulator);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_pipe_disable);

अटल पूर्णांक mipi_dbi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(connector->dev);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &dbidev->mode);
	अगर (!mode) अणु
		DRM_ERROR("Failed to duplicate mode\n");
		वापस 0;
	पूर्ण

	अगर (mode->name[0] == '\0')
		drm_mode_set_name(mode);

	mode->type |= DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	अगर (mode->width_mm) अणु
		connector->display_info.width_mm = mode->width_mm;
		connector->display_info.height_mm = mode->height_mm;
	पूर्ण

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs mipi_dbi_connector_hfuncs = अणु
	.get_modes = mipi_dbi_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs mipi_dbi_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक mipi_dbi_rotate_mode(काष्ठा drm_display_mode *mode,
				अचिन्हित पूर्णांक rotation)
अणु
	अगर (rotation == 0 || rotation == 180) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (rotation == 90 || rotation == 270) अणु
		swap(mode->hdisplay, mode->vdisplay);
		swap(mode->hsync_start, mode->vsync_start);
		swap(mode->hsync_end, mode->vsync_end);
		swap(mode->htotal, mode->vtotal);
		swap(mode->width_mm, mode->height_mm);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs mipi_dbi_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create_with_dirty,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर uपूर्णांक32_t mipi_dbi_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
पूर्ण;

/**
 * mipi_dbi_dev_init_with_क्रमmats - MIPI DBI device initialization with custom क्रमmats
 * @dbidev: MIPI DBI device काष्ठाure to initialize
 * @funcs: Display pipe functions
 * @क्रमmats: Array of supported क्रमmats (DRM_FORMAT\_\*).
 * @क्रमmat_count: Number of elements in @क्रमmats
 * @mode: Display mode
 * @rotation: Initial rotation in degrees Counter Clock Wise
 * @tx_buf_size: Allocate a transmit buffer of this size.
 *
 * This function sets up a &drm_simple_display_pipe with a &drm_connector that
 * has one fixed &drm_display_mode which is rotated according to @rotation.
 * This mode is used to set the mode config min/max width/height properties.
 *
 * Use mipi_dbi_dev_init() अगर you करोn't need custom क्रमmats.
 *
 * Note:
 * Some of the helper functions expects RGB565 to be the शेष क्रमmat and the
 * transmit buffer sized to fit that.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक mipi_dbi_dev_init_with_क्रमmats(काष्ठा mipi_dbi_dev *dbidev,
				   स्थिर काष्ठा drm_simple_display_pipe_funcs *funcs,
				   स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
				   स्थिर काष्ठा drm_display_mode *mode,
				   अचिन्हित पूर्णांक rotation, माप_प्रकार tx_buf_size)
अणु
	अटल स्थिर uपूर्णांक64_t modअगरiers[] = अणु
		DRM_FORMAT_MOD_LINEAR,
		DRM_FORMAT_MOD_INVALID
	पूर्ण;
	काष्ठा drm_device *drm = &dbidev->drm;
	पूर्णांक ret;

	अगर (!dbidev->dbi.command)
		वापस -EINVAL;

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;

	dbidev->tx_buf = devm_kदो_स्मृति(drm->dev, tx_buf_size, GFP_KERNEL);
	अगर (!dbidev->tx_buf)
		वापस -ENOMEM;

	drm_mode_copy(&dbidev->mode, mode);
	ret = mipi_dbi_rotate_mode(&dbidev->mode, rotation);
	अगर (ret) अणु
		DRM_ERROR("Illegal rotation value %u\n", rotation);
		वापस -EINVAL;
	पूर्ण

	drm_connector_helper_add(&dbidev->connector, &mipi_dbi_connector_hfuncs);
	ret = drm_connector_init(drm, &dbidev->connector, &mipi_dbi_connector_funcs,
				 DRM_MODE_CONNECTOR_SPI);
	अगर (ret)
		वापस ret;

	ret = drm_simple_display_pipe_init(drm, &dbidev->pipe, funcs, क्रमmats, क्रमmat_count,
					   modअगरiers, &dbidev->connector);
	अगर (ret)
		वापस ret;

	drm_plane_enable_fb_damage_clips(&dbidev->pipe.plane);

	drm->mode_config.funcs = &mipi_dbi_mode_config_funcs;
	drm->mode_config.min_width = dbidev->mode.hdisplay;
	drm->mode_config.max_width = dbidev->mode.hdisplay;
	drm->mode_config.min_height = dbidev->mode.vdisplay;
	drm->mode_config.max_height = dbidev->mode.vdisplay;
	dbidev->rotation = rotation;

	DRM_DEBUG_KMS("rotation = %u\n", rotation);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dbi_dev_init_with_क्रमmats);

/**
 * mipi_dbi_dev_init - MIPI DBI device initialization
 * @dbidev: MIPI DBI device काष्ठाure to initialize
 * @funcs: Display pipe functions
 * @mode: Display mode
 * @rotation: Initial rotation in degrees Counter Clock Wise
 *
 * This function sets up a &drm_simple_display_pipe with a &drm_connector that
 * has one fixed &drm_display_mode which is rotated according to @rotation.
 * This mode is used to set the mode config min/max width/height properties.
 * Additionally &mipi_dbi.tx_buf is allocated.
 *
 * Supported क्रमmats: Native RGB565 and emulated XRGB8888.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक mipi_dbi_dev_init(काष्ठा mipi_dbi_dev *dbidev,
		      स्थिर काष्ठा drm_simple_display_pipe_funcs *funcs,
		      स्थिर काष्ठा drm_display_mode *mode, अचिन्हित पूर्णांक rotation)
अणु
	माप_प्रकार bufsize = mode->vdisplay * mode->hdisplay * माप(u16);

	dbidev->drm.mode_config.preferred_depth = 16;

	वापस mipi_dbi_dev_init_with_क्रमmats(dbidev, funcs, mipi_dbi_क्रमmats,
					      ARRAY_SIZE(mipi_dbi_क्रमmats), mode,
					      rotation, bufsize);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_dev_init);

/**
 * mipi_dbi_hw_reset - Hardware reset of controller
 * @dbi: MIPI DBI काष्ठाure
 *
 * Reset controller अगर the &mipi_dbi->reset gpio is set.
 */
व्योम mipi_dbi_hw_reset(काष्ठा mipi_dbi *dbi)
अणु
	अगर (!dbi->reset)
		वापस;

	gpiod_set_value_cansleep(dbi->reset, 0);
	usleep_range(20, 1000);
	gpiod_set_value_cansleep(dbi->reset, 1);
	msleep(120);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_hw_reset);

/**
 * mipi_dbi_display_is_on - Check अगर display is on
 * @dbi: MIPI DBI काष्ठाure
 *
 * This function checks the Power Mode रेजिस्टर (अगर पढ़ोable) to see अगर
 * display output is turned on. This can be used to see अगर the bootloader
 * has alपढ़ोy turned on the display aव्योमing flicker when the pipeline is
 * enabled.
 *
 * Returns:
 * true अगर the display can be verअगरied to be on, false otherwise.
 */
bool mipi_dbi_display_is_on(काष्ठा mipi_dbi *dbi)
अणु
	u8 val;

	अगर (mipi_dbi_command_पढ़ो(dbi, MIPI_DCS_GET_POWER_MODE, &val))
		वापस false;

	val &= ~DCS_POWER_MODE_RESERVED_MASK;

	/* The घातeron/reset value is 08h DCS_POWER_MODE_DISPLAY_NORMAL_MODE */
	अगर (val != (DCS_POWER_MODE_DISPLAY |
	    DCS_POWER_MODE_DISPLAY_NORMAL_MODE | DCS_POWER_MODE_SLEEP_MODE))
		वापस false;

	DRM_DEBUG_DRIVER("Display is ON\n");

	वापस true;
पूर्ण
EXPORT_SYMBOL(mipi_dbi_display_is_on);

अटल पूर्णांक mipi_dbi_घातeron_reset_conditional(काष्ठा mipi_dbi_dev *dbidev, bool cond)
अणु
	काष्ठा device *dev = dbidev->drm.dev;
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	पूर्णांक ret;

	अगर (dbidev->regulator) अणु
		ret = regulator_enable(dbidev->regulator);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev, "Failed to enable regulator (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (cond && mipi_dbi_display_is_on(dbi))
		वापस 1;

	mipi_dbi_hw_reset(dbi);
	ret = mipi_dbi_command(dbi, MIPI_DCS_SOFT_RESET);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Failed to send reset command (%d)\n", ret);
		अगर (dbidev->regulator)
			regulator_disable(dbidev->regulator);
		वापस ret;
	पूर्ण

	/*
	 * If we did a hw reset, we know the controller is in Sleep mode and
	 * per MIPI DSC spec should रुको 5ms after soft reset. If we didn't,
	 * we assume worst हाल and रुको 120ms.
	 */
	अगर (dbi->reset)
		usleep_range(5000, 20000);
	अन्यथा
		msleep(120);

	वापस 0;
पूर्ण

/**
 * mipi_dbi_घातeron_reset - MIPI DBI घातeron and reset
 * @dbidev: MIPI DBI device काष्ठाure
 *
 * This function enables the regulator अगर used and करोes a hardware and software
 * reset.
 *
 * Returns:
 * Zero on success, or a negative error code.
 */
पूर्णांक mipi_dbi_घातeron_reset(काष्ठा mipi_dbi_dev *dbidev)
अणु
	वापस mipi_dbi_घातeron_reset_conditional(dbidev, false);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_घातeron_reset);

/**
 * mipi_dbi_घातeron_conditional_reset - MIPI DBI घातeron and conditional reset
 * @dbidev: MIPI DBI device काष्ठाure
 *
 * This function enables the regulator अगर used and अगर the display is off, it
 * करोes a hardware and software reset. If mipi_dbi_display_is_on() determines
 * that the display is on, no reset is perक्रमmed.
 *
 * Returns:
 * Zero अगर the controller was reset, 1 अगर the display was alपढ़ोy on, or a
 * negative error code.
 */
पूर्णांक mipi_dbi_घातeron_conditional_reset(काष्ठा mipi_dbi_dev *dbidev)
अणु
	वापस mipi_dbi_घातeron_reset_conditional(dbidev, true);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_घातeron_conditional_reset);

#अगर IS_ENABLED(CONFIG_SPI)

/**
 * mipi_dbi_spi_cmd_max_speed - get the maximum SPI bus speed
 * @spi: SPI device
 * @len: The transfer buffer length.
 *
 * Many controllers have a max speed of 10MHz, but can be pushed way beyond
 * that. Increase reliability by running pixel data at max speed and the rest
 * at 10MHz, preventing transfer glitches from messing up the init settings.
 */
u32 mipi_dbi_spi_cmd_max_speed(काष्ठा spi_device *spi, माप_प्रकार len)
अणु
	अगर (len > 64)
		वापस 0; /* use शेष */

	वापस min_t(u32, 10000000, spi->max_speed_hz);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_spi_cmd_max_speed);

अटल bool mipi_dbi_machine_little_endian(व्योम)
अणु
#अगर defined(__LITTLE_ENDIAN)
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/*
 * MIPI DBI Type C Option 1
 *
 * If the SPI controller करोesn't have 9 bits per word support,
 * use blocks of 9 bytes to send 8x 9-bit words using a 8-bit SPI transfer.
 * Pad partial blocks with MIPI_DCS_NOP (zero).
 * This is how the D/C bit (x) is added:
 *     x7654321
 *     0x765432
 *     10x76543
 *     210x7654
 *     3210x765
 *     43210x76
 *     543210x7
 *     6543210x
 *     76543210
 */

अटल पूर्णांक mipi_dbi_spi1e_transfer(काष्ठा mipi_dbi *dbi, पूर्णांक dc,
				   स्थिर व्योम *buf, माप_प्रकार len,
				   अचिन्हित पूर्णांक bpw)
अणु
	bool swap_bytes = (bpw == 16 && mipi_dbi_machine_little_endian());
	माप_प्रकार chunk, max_chunk = dbi->tx_buf9_len;
	काष्ठा spi_device *spi = dbi->spi;
	काष्ठा spi_transfer tr = अणु
		.tx_buf = dbi->tx_buf9,
		.bits_per_word = 8,
	पूर्ण;
	काष्ठा spi_message m;
	स्थिर u8 *src = buf;
	पूर्णांक i, ret;
	u8 *dst;

	अगर (drm_debug_enabled(DRM_UT_DRIVER))
		pr_debug("[drm:%s] dc=%d, max_chunk=%zu, transfers:\n",
			 __func__, dc, max_chunk);

	tr.speed_hz = mipi_dbi_spi_cmd_max_speed(spi, len);
	spi_message_init_with_transfers(&m, &tr, 1);

	अगर (!dc) अणु
		अगर (WARN_ON_ONCE(len != 1))
			वापस -EINVAL;

		/* Command: pad no-op's (zeroes) at beginning of block */
		dst = dbi->tx_buf9;
		स_रखो(dst, 0, 9);
		dst[8] = *src;
		tr.len = 9;

		वापस spi_sync(spi, &m);
	पूर्ण

	/* max with room क्रम adding one bit per byte */
	max_chunk = max_chunk / 9 * 8;
	/* but no bigger than len */
	max_chunk = min(max_chunk, len);
	/* 8 byte blocks */
	max_chunk = max_t(माप_प्रकार, 8, max_chunk & ~0x7);

	जबतक (len) अणु
		माप_प्रकार added = 0;

		chunk = min(len, max_chunk);
		len -= chunk;
		dst = dbi->tx_buf9;

		अगर (chunk < 8) अणु
			u8 val, carry = 0;

			/* Data: pad no-op's (zeroes) at end of block */
			स_रखो(dst, 0, 9);

			अगर (swap_bytes) अणु
				क्रम (i = 1; i < (chunk + 1); i++) अणु
					val = src[1];
					*dst++ = carry | BIT(8 - i) | (val >> i);
					carry = val << (8 - i);
					i++;
					val = src[0];
					*dst++ = carry | BIT(8 - i) | (val >> i);
					carry = val << (8 - i);
					src += 2;
				पूर्ण
				*dst++ = carry;
			पूर्ण अन्यथा अणु
				क्रम (i = 1; i < (chunk + 1); i++) अणु
					val = *src++;
					*dst++ = carry | BIT(8 - i) | (val >> i);
					carry = val << (8 - i);
				पूर्ण
				*dst++ = carry;
			पूर्ण

			chunk = 8;
			added = 1;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < chunk; i += 8) अणु
				अगर (swap_bytes) अणु
					*dst++ =                 BIT(7) | (src[1] >> 1);
					*dst++ = (src[1] << 7) | BIT(6) | (src[0] >> 2);
					*dst++ = (src[0] << 6) | BIT(5) | (src[3] >> 3);
					*dst++ = (src[3] << 5) | BIT(4) | (src[2] >> 4);
					*dst++ = (src[2] << 4) | BIT(3) | (src[5] >> 5);
					*dst++ = (src[5] << 3) | BIT(2) | (src[4] >> 6);
					*dst++ = (src[4] << 2) | BIT(1) | (src[7] >> 7);
					*dst++ = (src[7] << 1) | BIT(0);
					*dst++ = src[6];
				पूर्ण अन्यथा अणु
					*dst++ =                 BIT(7) | (src[0] >> 1);
					*dst++ = (src[0] << 7) | BIT(6) | (src[1] >> 2);
					*dst++ = (src[1] << 6) | BIT(5) | (src[2] >> 3);
					*dst++ = (src[2] << 5) | BIT(4) | (src[3] >> 4);
					*dst++ = (src[3] << 4) | BIT(3) | (src[4] >> 5);
					*dst++ = (src[4] << 3) | BIT(2) | (src[5] >> 6);
					*dst++ = (src[5] << 2) | BIT(1) | (src[6] >> 7);
					*dst++ = (src[6] << 1) | BIT(0);
					*dst++ = src[7];
				पूर्ण

				src += 8;
				added++;
			पूर्ण
		पूर्ण

		tr.len = chunk + added;

		ret = spi_sync(spi, &m);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_dbi_spi1_transfer(काष्ठा mipi_dbi *dbi, पूर्णांक dc,
				  स्थिर व्योम *buf, माप_प्रकार len,
				  अचिन्हित पूर्णांक bpw)
अणु
	काष्ठा spi_device *spi = dbi->spi;
	काष्ठा spi_transfer tr = अणु
		.bits_per_word = 9,
	पूर्ण;
	स्थिर u16 *src16 = buf;
	स्थिर u8 *src8 = buf;
	काष्ठा spi_message m;
	माप_प्रकार max_chunk;
	u16 *dst16;
	पूर्णांक ret;

	अगर (!spi_is_bpw_supported(spi, 9))
		वापस mipi_dbi_spi1e_transfer(dbi, dc, buf, len, bpw);

	tr.speed_hz = mipi_dbi_spi_cmd_max_speed(spi, len);
	max_chunk = dbi->tx_buf9_len;
	dst16 = dbi->tx_buf9;

	अगर (drm_debug_enabled(DRM_UT_DRIVER))
		pr_debug("[drm:%s] dc=%d, max_chunk=%zu, transfers:\n",
			 __func__, dc, max_chunk);

	max_chunk = min(max_chunk / 2, len);

	spi_message_init_with_transfers(&m, &tr, 1);
	tr.tx_buf = dst16;

	जबतक (len) अणु
		माप_प्रकार chunk = min(len, max_chunk);
		अचिन्हित पूर्णांक i;

		अगर (bpw == 16 && mipi_dbi_machine_little_endian()) अणु
			क्रम (i = 0; i < (chunk * 2); i += 2) अणु
				dst16[i]     = *src16 >> 8;
				dst16[i + 1] = *src16++ & 0xFF;
				अगर (dc) अणु
					dst16[i]     |= 0x0100;
					dst16[i + 1] |= 0x0100;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < chunk; i++) अणु
				dst16[i] = *src8++;
				अगर (dc)
					dst16[i] |= 0x0100;
			पूर्ण
		पूर्ण

		tr.len = chunk * 2;
		len -= chunk;

		ret = spi_sync(spi, &m);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_dbi_typec1_command(काष्ठा mipi_dbi *dbi, u8 *cmd,
				   u8 *parameters, माप_प्रकार num)
अणु
	अचिन्हित पूर्णांक bpw = (*cmd == MIPI_DCS_WRITE_MEMORY_START) ? 16 : 8;
	पूर्णांक ret;

	अगर (mipi_dbi_command_is_पढ़ो(dbi, *cmd))
		वापस -EOPNOTSUPP;

	MIPI_DBI_DEBUG_COMMAND(*cmd, parameters, num);

	ret = mipi_dbi_spi1_transfer(dbi, 0, cmd, 1, 8);
	अगर (ret || !num)
		वापस ret;

	वापस mipi_dbi_spi1_transfer(dbi, 1, parameters, num, bpw);
पूर्ण

/* MIPI DBI Type C Option 3 */

अटल पूर्णांक mipi_dbi_typec3_command_पढ़ो(काष्ठा mipi_dbi *dbi, u8 *cmd,
					u8 *data, माप_प्रकार len)
अणु
	काष्ठा spi_device *spi = dbi->spi;
	u32 speed_hz = min_t(u32, MIPI_DBI_MAX_SPI_READ_SPEED,
			     spi->max_speed_hz / 2);
	काष्ठा spi_transfer tr[2] = अणु
		अणु
			.speed_hz = speed_hz,
			.tx_buf = cmd,
			.len = 1,
		पूर्ण, अणु
			.speed_hz = speed_hz,
			.len = len,
		पूर्ण,
	पूर्ण;
	काष्ठा spi_message m;
	u8 *buf;
	पूर्णांक ret;

	अगर (!len)
		वापस -EINVAL;

	/*
	 * Support non-standard 24-bit and 32-bit Nokia पढ़ो commands which
	 * start with a dummy घड़ी, so we need to पढ़ो an extra byte.
	 */
	अगर (*cmd == MIPI_DCS_GET_DISPLAY_ID ||
	    *cmd == MIPI_DCS_GET_DISPLAY_STATUS) अणु
		अगर (!(len == 3 || len == 4))
			वापस -EINVAL;

		tr[1].len = len + 1;
	पूर्ण

	buf = kदो_स्मृति(tr[1].len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	tr[1].rx_buf = buf;
	gpiod_set_value_cansleep(dbi->dc, 0);

	spi_message_init_with_transfers(&m, tr, ARRAY_SIZE(tr));
	ret = spi_sync(spi, &m);
	अगर (ret)
		जाओ err_मुक्त;

	अगर (tr[1].len == len) अणु
		स_नकल(data, buf, len);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < len; i++)
			data[i] = (buf[i] << 1) | (buf[i + 1] >> 7);
	पूर्ण

	MIPI_DBI_DEBUG_COMMAND(*cmd, data, len);

err_मुक्त:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक mipi_dbi_typec3_command(काष्ठा mipi_dbi *dbi, u8 *cmd,
				   u8 *par, माप_प्रकार num)
अणु
	काष्ठा spi_device *spi = dbi->spi;
	अचिन्हित पूर्णांक bpw = 8;
	u32 speed_hz;
	पूर्णांक ret;

	अगर (mipi_dbi_command_is_पढ़ो(dbi, *cmd))
		वापस mipi_dbi_typec3_command_पढ़ो(dbi, cmd, par, num);

	MIPI_DBI_DEBUG_COMMAND(*cmd, par, num);

	gpiod_set_value_cansleep(dbi->dc, 0);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, 1);
	ret = mipi_dbi_spi_transfer(spi, speed_hz, 8, cmd, 1);
	अगर (ret || !num)
		वापस ret;

	अगर (*cmd == MIPI_DCS_WRITE_MEMORY_START && !dbi->swap_bytes)
		bpw = 16;

	gpiod_set_value_cansleep(dbi->dc, 1);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, num);

	वापस mipi_dbi_spi_transfer(spi, speed_hz, bpw, par, num);
पूर्ण

/**
 * mipi_dbi_spi_init - Initialize MIPI DBI SPI पूर्णांकerface
 * @spi: SPI device
 * @dbi: MIPI DBI काष्ठाure to initialize
 * @dc: D/C gpio (optional)
 *
 * This function sets &mipi_dbi->command, enables &mipi_dbi->पढ़ो_commands क्रम the
 * usual पढ़ो commands. It should be followed by a call to mipi_dbi_dev_init() or
 * a driver-specअगरic init.
 *
 * If @dc is set, a Type C Option 3 पूर्णांकerface is assumed, अगर not
 * Type C Option 1.
 *
 * If the SPI master driver करोesn't support the necessary bits per word,
 * the following transक्रमmation is used:
 *
 * - 9-bit: reorder buffer as 9x 8-bit words, padded with no-op command.
 * - 16-bit: अगर big endian send as 8-bit, अगर little endian swap bytes
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक mipi_dbi_spi_init(काष्ठा spi_device *spi, काष्ठा mipi_dbi *dbi,
		      काष्ठा gpio_desc *dc)
अणु
	काष्ठा device *dev = &spi->dev;
	पूर्णांक ret;

	/*
	 * Even though it's not the SPI device that करोes DMA (the master करोes),
	 * the dma mask is necessary क्रम the dma_alloc_wc() in
	 * drm_gem_cma_create(). The dma_addr वापसed will be a physical
	 * address which might be dअगरferent from the bus address, but this is
	 * not a problem since the address will not be used.
	 * The भव address is used in the transfer and the SPI core
	 * re-maps it on the SPI master device using the DMA streaming API
	 * (spi_map_buf()).
	 */
	अगर (!dev->coherent_dma_mask) अणु
		ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_warn(dev, "Failed to set dma mask %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dbi->spi = spi;
	dbi->पढ़ो_commands = mipi_dbi_dcs_पढ़ो_commands;

	अगर (dc) अणु
		dbi->command = mipi_dbi_typec3_command;
		dbi->dc = dc;
		अगर (mipi_dbi_machine_little_endian() && !spi_is_bpw_supported(spi, 16))
			dbi->swap_bytes = true;
	पूर्ण अन्यथा अणु
		dbi->command = mipi_dbi_typec1_command;
		dbi->tx_buf9_len = SZ_16K;
		dbi->tx_buf9 = devm_kदो_स्मृति(dev, dbi->tx_buf9_len, GFP_KERNEL);
		अगर (!dbi->tx_buf9)
			वापस -ENOMEM;
	पूर्ण

	mutex_init(&dbi->cmdlock);

	DRM_DEBUG_DRIVER("SPI speed: %uMHz\n", spi->max_speed_hz / 1000000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dbi_spi_init);

/**
 * mipi_dbi_spi_transfer - SPI transfer helper
 * @spi: SPI device
 * @speed_hz: Override speed (optional)
 * @bpw: Bits per word
 * @buf: Buffer to transfer
 * @len: Buffer length
 *
 * This SPI transfer helper अवरोधs up the transfer of @buf पूर्णांकo chunks which
 * the SPI controller driver can handle.
 *
 * Returns:
 * Zero on success, negative error code on failure.
 */
पूर्णांक mipi_dbi_spi_transfer(काष्ठा spi_device *spi, u32 speed_hz,
			  u8 bpw, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	माप_प्रकार max_chunk = spi_max_transfer_size(spi);
	काष्ठा spi_transfer tr = अणु
		.bits_per_word = bpw,
		.speed_hz = speed_hz,
	पूर्ण;
	काष्ठा spi_message m;
	माप_प्रकार chunk;
	पूर्णांक ret;

	spi_message_init_with_transfers(&m, &tr, 1);

	जबतक (len) अणु
		chunk = min(len, max_chunk);

		tr.tx_buf = buf;
		tr.len = chunk;
		buf += chunk;
		len -= chunk;

		ret = spi_sync(spi, &m);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dbi_spi_transfer);

#पूर्ण_अगर /* CONFIG_SPI */

#अगर_घोषित CONFIG_DEBUG_FS

अटल sमाप_प्रकार mipi_dbi_debugfs_command_ग_लिखो(काष्ठा file *file,
					      स्थिर अक्षर __user *ubuf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा mipi_dbi_dev *dbidev = m->निजी;
	u8 val, cmd = 0, parameters[64];
	अक्षर *buf, *pos, *token;
	पूर्णांक i, ret, idx;

	अगर (!drm_dev_enter(&dbidev->drm, &idx))
		वापस -ENODEV;

	buf = memdup_user_nul(ubuf, count);
	अगर (IS_ERR(buf)) अणु
		ret = PTR_ERR(buf);
		जाओ err_निकास;
	पूर्ण

	/* strip trailing whitespace */
	क्रम (i = count - 1; i > 0; i--)
		अगर (है_खाली(buf[i]))
			buf[i] = '\0';
		अन्यथा
			अवरोध;
	i = 0;
	pos = buf;
	जबतक (pos) अणु
		token = strsep(&pos, " ");
		अगर (!token) अणु
			ret = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण

		ret = kstrtou8(token, 16, &val);
		अगर (ret < 0)
			जाओ err_मुक्त;

		अगर (token == buf)
			cmd = val;
		अन्यथा
			parameters[i++] = val;

		अगर (i == 64) अणु
			ret = -E2BIG;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	ret = mipi_dbi_command_buf(&dbidev->dbi, cmd, parameters, i);

err_मुक्त:
	kमुक्त(buf);
err_निकास:
	drm_dev_निकास(idx);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल पूर्णांक mipi_dbi_debugfs_command_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा mipi_dbi_dev *dbidev = m->निजी;
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	u8 cmd, val[4];
	पूर्णांक ret, idx;
	माप_प्रकार len;

	अगर (!drm_dev_enter(&dbidev->drm, &idx))
		वापस -ENODEV;

	क्रम (cmd = 0; cmd < 255; cmd++) अणु
		अगर (!mipi_dbi_command_is_पढ़ो(dbi, cmd))
			जारी;

		चयन (cmd) अणु
		हाल MIPI_DCS_READ_MEMORY_START:
		हाल MIPI_DCS_READ_MEMORY_CONTINUE:
			len = 2;
			अवरोध;
		हाल MIPI_DCS_GET_DISPLAY_ID:
			len = 3;
			अवरोध;
		हाल MIPI_DCS_GET_DISPLAY_STATUS:
			len = 4;
			अवरोध;
		शेष:
			len = 1;
			अवरोध;
		पूर्ण

		seq_म_लिखो(m, "%02x: ", cmd);
		ret = mipi_dbi_command_buf(dbi, cmd, val, len);
		अगर (ret) अणु
			seq_माला_दो(m, "XX\n");
			जारी;
		पूर्ण
		seq_म_लिखो(m, "%*phN\n", (पूर्णांक)len, val);
	पूर्ण

	drm_dev_निकास(idx);

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_dbi_debugfs_command_खोलो(काष्ठा inode *inode,
					 काष्ठा file *file)
अणु
	वापस single_खोलो(file, mipi_dbi_debugfs_command_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations mipi_dbi_debugfs_command_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = mipi_dbi_debugfs_command_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = mipi_dbi_debugfs_command_ग_लिखो,
पूर्ण;

/**
 * mipi_dbi_debugfs_init - Create debugfs entries
 * @minor: DRM minor
 *
 * This function creates a 'command' debugfs file क्रम sending commands to the
 * controller or getting the पढ़ो command values.
 * Drivers can use this as their &drm_driver->debugfs_init callback.
 *
 */
व्योम mipi_dbi_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(minor->dev);
	umode_t mode = S_IFREG | S_IWUSR;

	अगर (dbidev->dbi.पढ़ो_commands)
		mode |= S_IRUGO;
	debugfs_create_file("command", mode, minor->debugfs_root, dbidev,
			    &mipi_dbi_debugfs_command_fops);
पूर्ण
EXPORT_SYMBOL(mipi_dbi_debugfs_init);

#पूर्ण_अगर

MODULE_LICENSE("GPL");
