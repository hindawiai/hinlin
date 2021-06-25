<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DRM driver क्रम Sitronix ST7586 panels
 *
 * Copyright 2017 David Lechner <david@lechnology.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>
#समावेश <video/mipi_display.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mipi_dbi.h>
#समावेश <drm/drm_rect.h>

/* controller-specअगरic commands */
#घोषणा ST7586_DISP_MODE_GRAY	0x38
#घोषणा ST7586_DISP_MODE_MONO	0x39
#घोषणा ST7586_ENABLE_DDRAM	0x3a
#घोषणा ST7586_SET_DISP_DUTY	0xb0
#घोषणा ST7586_SET_PART_DISP	0xb4
#घोषणा ST7586_SET_NLINE_INV	0xb5
#घोषणा ST7586_SET_VOP		0xc0
#घोषणा ST7586_SET_BIAS_SYSTEM	0xc3
#घोषणा ST7586_SET_BOOST_LEVEL	0xc4
#घोषणा ST7586_SET_VOP_OFFSET	0xc7
#घोषणा ST7586_ENABLE_ANALOG	0xd0
#घोषणा ST7586_AUTO_READ_CTRL	0xd7
#घोषणा ST7586_OTP_RW_CTRL	0xe0
#घोषणा ST7586_OTP_CTRL_OUT	0xe1
#घोषणा ST7586_OTP_READ		0xe3

#घोषणा ST7586_DISP_CTRL_MX	BIT(6)
#घोषणा ST7586_DISP_CTRL_MY	BIT(7)

/*
 * The ST7586 controller has an unusual pixel क्रमmat where 2bpp grayscale is
 * packed 3 pixels per byte with the first two pixels using 3 bits and the 3rd
 * pixel using only 2 bits.
 *
 * |  D7  |  D6  |  D5  ||      |      || 2bpp |
 * | (D4) | (D3) | (D2) ||  D1  |  D0  || GRAY |
 * +------+------+------++------+------++------+
 * |  1   |  1   |  1   ||  1   |  1   || 0  0 | black
 * |  1   |  0   |  0   ||  1   |  0   || 0  1 | dark gray
 * |  0   |  1   |  0   ||  0   |  1   || 1  0 | light gray
 * |  0   |  0   |  0   ||  0   |  0   || 1  1 | white
 */

अटल स्थिर u8 st7586_lookup[] = अणु 0x7, 0x4, 0x2, 0x0 पूर्ण;

अटल व्योम st7586_xrgb8888_to_gray332(u8 *dst, व्योम *vaddr,
				       काष्ठा drm_framebuffer *fb,
				       काष्ठा drm_rect *clip)
अणु
	माप_प्रकार len = (clip->x2 - clip->x1) * (clip->y2 - clip->y1);
	अचिन्हित पूर्णांक x, y;
	u8 *src, *buf, val;

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस;

	drm_fb_xrgb8888_to_gray8(buf, vaddr, fb, clip);
	src = buf;

	क्रम (y = clip->y1; y < clip->y2; y++) अणु
		क्रम (x = clip->x1; x < clip->x2; x += 3) अणु
			val = st7586_lookup[*src++ >> 6] << 5;
			val |= st7586_lookup[*src++ >> 6] << 2;
			val |= st7586_lookup[*src++ >> 6] >> 1;
			*dst++ = val;
		पूर्ण
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल पूर्णांक st7586_buf_copy(व्योम *dst, काष्ठा drm_framebuffer *fb,
			   काष्ठा drm_rect *clip)
अणु
	काष्ठा drm_gem_cma_object *cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	काष्ठा dma_buf_attachment *import_attach = cma_obj->base.import_attach;
	व्योम *src = cma_obj->vaddr;
	पूर्णांक ret = 0;

	अगर (import_attach) अणु
		ret = dma_buf_begin_cpu_access(import_attach->dmabuf,
					       DMA_FROM_DEVICE);
		अगर (ret)
			वापस ret;
	पूर्ण

	st7586_xrgb8888_to_gray332(dst, src, fb, clip);

	अगर (import_attach)
		ret = dma_buf_end_cpu_access(import_attach->dmabuf,
					     DMA_FROM_DEVICE);

	वापस ret;
पूर्ण

अटल व्योम st7586_fb_dirty(काष्ठा drm_framebuffer *fb, काष्ठा drm_rect *rect)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(fb->dev);
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	पूर्णांक start, end, idx, ret = 0;

	अगर (!drm_dev_enter(fb->dev, &idx))
		वापस;

	/* 3 pixels per byte, so grow clip to nearest multiple of 3 */
	rect->x1 = roundकरोwn(rect->x1, 3);
	rect->x2 = roundup(rect->x2, 3);

	DRM_DEBUG_KMS("Flushing [FB:%d] " DRM_RECT_FMT "\n", fb->base.id, DRM_RECT_ARG(rect));

	ret = st7586_buf_copy(dbidev->tx_buf, fb, rect);
	अगर (ret)
		जाओ err_msg;

	/* Pixels are packed 3 per byte */
	start = rect->x1 / 3;
	end = rect->x2 / 3;

	mipi_dbi_command(dbi, MIPI_DCS_SET_COLUMN_ADDRESS,
			 (start >> 8) & 0xFF, start & 0xFF,
			 (end >> 8) & 0xFF, (end - 1) & 0xFF);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PAGE_ADDRESS,
			 (rect->y1 >> 8) & 0xFF, rect->y1 & 0xFF,
			 (rect->y2 >> 8) & 0xFF, (rect->y2 - 1) & 0xFF);

	ret = mipi_dbi_command_buf(dbi, MIPI_DCS_WRITE_MEMORY_START,
				   (u8 *)dbidev->tx_buf,
				   (end - start) * (rect->y2 - rect->y1));
err_msg:
	अगर (ret)
		dev_err_once(fb->dev->dev, "Failed to update display %d\n", ret);

	drm_dev_निकास(idx);
पूर्ण

अटल व्योम st7586_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_rect rect;

	अगर (!pipe->crtc.state->active)
		वापस;

	अगर (drm_atomic_helper_damage_merged(old_state, state, &rect))
		st7586_fb_dirty(state->fb, &rect);
पूर्ण

अटल व्योम st7586_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	काष्ठा drm_rect rect = अणु
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	पूर्ण;
	पूर्णांक idx, ret;
	u8 addr_mode;

	अगर (!drm_dev_enter(pipe->crtc.dev, &idx))
		वापस;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_घातeron_reset(dbidev);
	अगर (ret)
		जाओ out_निकास;

	mipi_dbi_command(dbi, ST7586_AUTO_READ_CTRL, 0x9f);
	mipi_dbi_command(dbi, ST7586_OTP_RW_CTRL, 0x00);

	msleep(10);

	mipi_dbi_command(dbi, ST7586_OTP_READ);

	msleep(20);

	mipi_dbi_command(dbi, ST7586_OTP_CTRL_OUT);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_OFF);

	msleep(50);

	mipi_dbi_command(dbi, ST7586_SET_VOP_OFFSET, 0x00);
	mipi_dbi_command(dbi, ST7586_SET_VOP, 0xe3, 0x00);
	mipi_dbi_command(dbi, ST7586_SET_BIAS_SYSTEM, 0x02);
	mipi_dbi_command(dbi, ST7586_SET_BOOST_LEVEL, 0x04);
	mipi_dbi_command(dbi, ST7586_ENABLE_ANALOG, 0x1d);
	mipi_dbi_command(dbi, ST7586_SET_NLINE_INV, 0x00);
	mipi_dbi_command(dbi, ST7586_DISP_MODE_GRAY);
	mipi_dbi_command(dbi, ST7586_ENABLE_DDRAM, 0x02);

	चयन (dbidev->rotation) अणु
	शेष:
		addr_mode = 0x00;
		अवरोध;
	हाल 90:
		addr_mode = ST7586_DISP_CTRL_MY;
		अवरोध;
	हाल 180:
		addr_mode = ST7586_DISP_CTRL_MX | ST7586_DISP_CTRL_MY;
		अवरोध;
	हाल 270:
		addr_mode = ST7586_DISP_CTRL_MX;
		अवरोध;
	पूर्ण
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);

	mipi_dbi_command(dbi, ST7586_SET_DISP_DUTY, 0x7f);
	mipi_dbi_command(dbi, ST7586_SET_PART_DISP, 0xa0);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PARTIAL_ROWS, 0x00, 0x00, 0x00, 0x77);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_INVERT_MODE);

	msleep(100);

	st7586_fb_dirty(fb, &rect);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);
out_निकास:
	drm_dev_निकास(idx);
पूर्ण

अटल व्योम st7586_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);

	/*
	 * This callback is not रक्षित by drm_dev_enter/निकास since we want to
	 * turn off the display on regular driver unload. It's highly unlikely
	 * that the underlying SPI controller is gone should this be called after
	 * unplug.
	 */

	DRM_DEBUG_KMS("\n");

	mipi_dbi_command(&dbidev->dbi, MIPI_DCS_SET_DISPLAY_OFF);
पूर्ण

अटल स्थिर u32 st7586_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs st7586_pipe_funcs = अणु
	.enable		= st7586_pipe_enable,
	.disable	= st7586_pipe_disable,
	.update		= st7586_pipe_update,
	.prepare_fb	= drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode st7586_mode = अणु
	DRM_SIMPLE_MODE(178, 128, 37, 27),
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(st7586_fops);

अटल स्थिर काष्ठा drm_driver st7586_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &st7586_fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "st7586",
	.desc			= "Sitronix ST7586",
	.date			= "20170801",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id st7586_of_match[] = अणु
	अणु .compatible = "lego,ev3-lcd" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st7586_of_match);

अटल स्थिर काष्ठा spi_device_id st7586_id[] = अणु
	अणु "ev3-lcd", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, st7586_id);

अटल पूर्णांक st7586_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा mipi_dbi_dev *dbidev;
	काष्ठा drm_device *drm;
	काष्ठा mipi_dbi *dbi;
	काष्ठा gpio_desc *a0;
	u32 rotation = 0;
	माप_प्रकार bufsize;
	पूर्णांक ret;

	dbidev = devm_drm_dev_alloc(dev, &st7586_driver,
				    काष्ठा mipi_dbi_dev, drm);
	अगर (IS_ERR(dbidev))
		वापस PTR_ERR(dbidev);

	dbi = &dbidev->dbi;
	drm = &dbidev->drm;

	bufsize = (st7586_mode.vdisplay + 2) / 3 * st7586_mode.hdisplay;

	dbi->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(dbi->reset)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
		वापस PTR_ERR(dbi->reset);
	पूर्ण

	a0 = devm_gpiod_get(dev, "a0", GPIOD_OUT_LOW);
	अगर (IS_ERR(a0)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'a0'\n");
		वापस PTR_ERR(a0);
	पूर्ण

	device_property_पढ़ो_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, dbi, a0);
	अगर (ret)
		वापस ret;

	/* Cannot पढ़ो from this controller via SPI */
	dbi->पढ़ो_commands = शून्य;

	ret = mipi_dbi_dev_init_with_क्रमmats(dbidev, &st7586_pipe_funcs,
					     st7586_क्रमmats, ARRAY_SIZE(st7586_क्रमmats),
					     &st7586_mode, rotation, bufsize);
	अगर (ret)
		वापस ret;

	/*
	 * we are using 8-bit data, so we are not actually swapping anything,
	 * but setting mipi->swap_bytes makes mipi_dbi_typec3_command() करो the
	 * right thing and not use 16-bit transfers (which results in swapped
	 * bytes on little-endian प्रणालीs and causes out of order data to be
	 * sent to the display).
	 */
	dbi->swap_bytes = true;

	drm_mode_config_reset(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, drm);

	drm_fbdev_generic_setup(drm, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक st7586_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

अटल व्योम st7586_shutकरोwn(काष्ठा spi_device *spi)
अणु
	drm_atomic_helper_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल काष्ठा spi_driver st7586_spi_driver = अणु
	.driver = अणु
		.name = "st7586",
		.owner = THIS_MODULE,
		.of_match_table = st7586_of_match,
	पूर्ण,
	.id_table = st7586_id,
	.probe = st7586_probe,
	.हटाओ = st7586_हटाओ,
	.shutकरोwn = st7586_shutकरोwn,
पूर्ण;
module_spi_driver(st7586_spi_driver);

MODULE_DESCRIPTION("Sitronix ST7586 DRM driver");
MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_LICENSE("GPL");
