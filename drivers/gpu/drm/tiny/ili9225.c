<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DRM driver क्रम Ilitek ILI9225 panels
 *
 * Copyright 2017 David Lechner <david@lechnology.com>
 *
 * Some code copied from mipi-dbi.c
 * Copyright 2016 Noralf Trथचnnes
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
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mipi_dbi.h>
#समावेश <drm/drm_rect.h>

#घोषणा ILI9225_DRIVER_READ_CODE	0x00
#घोषणा ILI9225_DRIVER_OUTPUT_CONTROL	0x01
#घोषणा ILI9225_LCD_AC_DRIVING_CONTROL	0x02
#घोषणा ILI9225_ENTRY_MODE		0x03
#घोषणा ILI9225_DISPLAY_CONTROL_1	0x07
#घोषणा ILI9225_BLANK_PERIOD_CONTROL_1	0x08
#घोषणा ILI9225_FRAME_CYCLE_CONTROL	0x0b
#घोषणा ILI9225_INTERFACE_CONTROL	0x0c
#घोषणा ILI9225_OSCILLATION_CONTROL	0x0f
#घोषणा ILI9225_POWER_CONTROL_1		0x10
#घोषणा ILI9225_POWER_CONTROL_2		0x11
#घोषणा ILI9225_POWER_CONTROL_3		0x12
#घोषणा ILI9225_POWER_CONTROL_4		0x13
#घोषणा ILI9225_POWER_CONTROL_5		0x14
#घोषणा ILI9225_VCI_RECYCLING		0x15
#घोषणा ILI9225_RAM_ADDRESS_SET_1	0x20
#घोषणा ILI9225_RAM_ADDRESS_SET_2	0x21
#घोषणा ILI9225_WRITE_DATA_TO_GRAM	0x22
#घोषणा ILI9225_SOFTWARE_RESET		0x28
#घोषणा ILI9225_GATE_SCAN_CONTROL	0x30
#घोषणा ILI9225_VERTICAL_SCROLL_1	0x31
#घोषणा ILI9225_VERTICAL_SCROLL_2	0x32
#घोषणा ILI9225_VERTICAL_SCROLL_3	0x33
#घोषणा ILI9225_PARTIAL_DRIVING_POS_1	0x34
#घोषणा ILI9225_PARTIAL_DRIVING_POS_2	0x35
#घोषणा ILI9225_HORIZ_WINDOW_ADDR_1	0x36
#घोषणा ILI9225_HORIZ_WINDOW_ADDR_2	0x37
#घोषणा ILI9225_VERT_WINDOW_ADDR_1	0x38
#घोषणा ILI9225_VERT_WINDOW_ADDR_2	0x39
#घोषणा ILI9225_GAMMA_CONTROL_1		0x50
#घोषणा ILI9225_GAMMA_CONTROL_2		0x51
#घोषणा ILI9225_GAMMA_CONTROL_3		0x52
#घोषणा ILI9225_GAMMA_CONTROL_4		0x53
#घोषणा ILI9225_GAMMA_CONTROL_5		0x54
#घोषणा ILI9225_GAMMA_CONTROL_6		0x55
#घोषणा ILI9225_GAMMA_CONTROL_7		0x56
#घोषणा ILI9225_GAMMA_CONTROL_8		0x57
#घोषणा ILI9225_GAMMA_CONTROL_9		0x58
#घोषणा ILI9225_GAMMA_CONTROL_10	0x59

अटल अंतरभूत पूर्णांक ili9225_command(काष्ठा mipi_dbi *dbi, u8 cmd, u16 data)
अणु
	u8 par[2] = अणु data >> 8, data & 0xff पूर्ण;

	वापस mipi_dbi_command_buf(dbi, cmd, par, 2);
पूर्ण

अटल व्योम ili9225_fb_dirty(काष्ठा drm_framebuffer *fb, काष्ठा drm_rect *rect)
अणु
	काष्ठा drm_gem_cma_object *cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(fb->dev);
	अचिन्हित पूर्णांक height = rect->y2 - rect->y1;
	अचिन्हित पूर्णांक width = rect->x2 - rect->x1;
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	bool swap = dbi->swap_bytes;
	u16 x_start, y_start;
	u16 x1, x2, y1, y2;
	पूर्णांक idx, ret = 0;
	bool full;
	व्योम *tr;

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

	चयन (dbidev->rotation) अणु
	शेष:
		x1 = rect->x1;
		x2 = rect->x2 - 1;
		y1 = rect->y1;
		y2 = rect->y2 - 1;
		x_start = x1;
		y_start = y1;
		अवरोध;
	हाल 90:
		x1 = rect->y1;
		x2 = rect->y2 - 1;
		y1 = fb->width - rect->x2;
		y2 = fb->width - rect->x1 - 1;
		x_start = x1;
		y_start = y2;
		अवरोध;
	हाल 180:
		x1 = fb->width - rect->x2;
		x2 = fb->width - rect->x1 - 1;
		y1 = fb->height - rect->y2;
		y2 = fb->height - rect->y1 - 1;
		x_start = x2;
		y_start = y2;
		अवरोध;
	हाल 270:
		x1 = fb->height - rect->y2;
		x2 = fb->height - rect->y1 - 1;
		y1 = rect->x1;
		y2 = rect->x2 - 1;
		x_start = x2;
		y_start = y1;
		अवरोध;
	पूर्ण

	ili9225_command(dbi, ILI9225_HORIZ_WINDOW_ADDR_1, x2);
	ili9225_command(dbi, ILI9225_HORIZ_WINDOW_ADDR_2, x1);
	ili9225_command(dbi, ILI9225_VERT_WINDOW_ADDR_1, y2);
	ili9225_command(dbi, ILI9225_VERT_WINDOW_ADDR_2, y1);

	ili9225_command(dbi, ILI9225_RAM_ADDRESS_SET_1, x_start);
	ili9225_command(dbi, ILI9225_RAM_ADDRESS_SET_2, y_start);

	ret = mipi_dbi_command_buf(dbi, ILI9225_WRITE_DATA_TO_GRAM, tr,
				   width * height * 2);
err_msg:
	अगर (ret)
		dev_err_once(fb->dev->dev, "Failed to update display %d\n", ret);

	drm_dev_निकास(idx);
पूर्ण

अटल व्योम ili9225_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
				काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_rect rect;

	अगर (!pipe->crtc.state->active)
		वापस;

	अगर (drm_atomic_helper_damage_merged(old_state, state, &rect))
		ili9225_fb_dirty(state->fb, &rect);
पूर्ण

अटल व्योम ili9225_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
				काष्ठा drm_crtc_state *crtc_state,
				काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा device *dev = pipe->crtc.dev->dev;
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	काष्ठा drm_rect rect = अणु
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	पूर्ण;
	पूर्णांक ret, idx;
	u8 am_id;

	अगर (!drm_dev_enter(pipe->crtc.dev, &idx))
		वापस;

	DRM_DEBUG_KMS("\n");

	mipi_dbi_hw_reset(dbi);

	/*
	 * There करोn't seem to be two example init sequences that match, so
	 * using the one from the popular Arduino library क्रम this display.
	 * https://github.com/Nkawu/TFT_22_ILI9225/blob/master/src/TFT_22_ILI9225.cpp
	 */

	ret = ili9225_command(dbi, ILI9225_POWER_CONTROL_1, 0x0000);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Error sending command %d\n", ret);
		जाओ out_निकास;
	पूर्ण
	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x0000);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_3, 0x0000);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_4, 0x0000);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_5, 0x0000);

	msleep(40);

	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x0018);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_3, 0x6121);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_4, 0x006f);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_5, 0x495f);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_1, 0x0800);

	msleep(10);

	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x103b);

	msleep(50);

	चयन (dbidev->rotation) अणु
	शेष:
		am_id = 0x30;
		अवरोध;
	हाल 90:
		am_id = 0x18;
		अवरोध;
	हाल 180:
		am_id = 0x00;
		अवरोध;
	हाल 270:
		am_id = 0x28;
		अवरोध;
	पूर्ण
	ili9225_command(dbi, ILI9225_DRIVER_OUTPUT_CONTROL, 0x011c);
	ili9225_command(dbi, ILI9225_LCD_AC_DRIVING_CONTROL, 0x0100);
	ili9225_command(dbi, ILI9225_ENTRY_MODE, 0x1000 | am_id);
	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x0000);
	ili9225_command(dbi, ILI9225_BLANK_PERIOD_CONTROL_1, 0x0808);
	ili9225_command(dbi, ILI9225_FRAME_CYCLE_CONTROL, 0x1100);
	ili9225_command(dbi, ILI9225_INTERFACE_CONTROL, 0x0000);
	ili9225_command(dbi, ILI9225_OSCILLATION_CONTROL, 0x0d01);
	ili9225_command(dbi, ILI9225_VCI_RECYCLING, 0x0020);
	ili9225_command(dbi, ILI9225_RAM_ADDRESS_SET_1, 0x0000);
	ili9225_command(dbi, ILI9225_RAM_ADDRESS_SET_2, 0x0000);

	ili9225_command(dbi, ILI9225_GATE_SCAN_CONTROL, 0x0000);
	ili9225_command(dbi, ILI9225_VERTICAL_SCROLL_1, 0x00db);
	ili9225_command(dbi, ILI9225_VERTICAL_SCROLL_2, 0x0000);
	ili9225_command(dbi, ILI9225_VERTICAL_SCROLL_3, 0x0000);
	ili9225_command(dbi, ILI9225_PARTIAL_DRIVING_POS_1, 0x00db);
	ili9225_command(dbi, ILI9225_PARTIAL_DRIVING_POS_2, 0x0000);

	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_1, 0x0000);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_2, 0x0808);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_3, 0x080a);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_4, 0x000a);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_5, 0x0a08);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_6, 0x0808);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_7, 0x0000);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_8, 0x0a00);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_9, 0x0710);
	ili9225_command(dbi, ILI9225_GAMMA_CONTROL_10, 0x0710);

	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x0012);

	msleep(50);

	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x1017);

	ili9225_fb_dirty(fb, &rect);
out_निकास:
	drm_dev_निकास(idx);
पूर्ण

अटल व्योम ili9225_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;

	DRM_DEBUG_KMS("\n");

	/*
	 * This callback is not रक्षित by drm_dev_enter/निकास since we want to
	 * turn off the display on regular driver unload. It's highly unlikely
	 * that the underlying SPI controller is gone should this be called after
	 * unplug.
	 */

	ili9225_command(dbi, ILI9225_DISPLAY_CONTROL_1, 0x0000);
	msleep(50);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_2, 0x0007);
	msleep(50);
	ili9225_command(dbi, ILI9225_POWER_CONTROL_1, 0x0a02);
पूर्ण

अटल पूर्णांक ili9225_dbi_command(काष्ठा mipi_dbi *dbi, u8 *cmd, u8 *par,
			       माप_प्रकार num)
अणु
	काष्ठा spi_device *spi = dbi->spi;
	अचिन्हित पूर्णांक bpw = 8;
	u32 speed_hz;
	पूर्णांक ret;

	gpiod_set_value_cansleep(dbi->dc, 0);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, 1);
	ret = mipi_dbi_spi_transfer(spi, speed_hz, 8, cmd, 1);
	अगर (ret || !num)
		वापस ret;

	अगर (*cmd == ILI9225_WRITE_DATA_TO_GRAM && !dbi->swap_bytes)
		bpw = 16;

	gpiod_set_value_cansleep(dbi->dc, 1);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, num);

	वापस mipi_dbi_spi_transfer(spi, speed_hz, bpw, par, num);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs ili9225_pipe_funcs = अणु
	.enable		= ili9225_pipe_enable,
	.disable	= ili9225_pipe_disable,
	.update		= ili9225_pipe_update,
	.prepare_fb	= drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ili9225_mode = अणु
	DRM_SIMPLE_MODE(176, 220, 35, 44),
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(ili9225_fops);

अटल स्थिर काष्ठा drm_driver ili9225_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &ili9225_fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.name			= "ili9225",
	.desc			= "Ilitek ILI9225",
	.date			= "20171106",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ili9225_of_match[] = अणु
	अणु .compatible = "vot,v220hf01a-t" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ili9225_of_match);

अटल स्थिर काष्ठा spi_device_id ili9225_id[] = अणु
	अणु "v220hf01a-t", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, ili9225_id);

अटल पूर्णांक ili9225_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा mipi_dbi_dev *dbidev;
	काष्ठा drm_device *drm;
	काष्ठा mipi_dbi *dbi;
	काष्ठा gpio_desc *rs;
	u32 rotation = 0;
	पूर्णांक ret;

	dbidev = devm_drm_dev_alloc(dev, &ili9225_driver,
				    काष्ठा mipi_dbi_dev, drm);
	अगर (IS_ERR(dbidev))
		वापस PTR_ERR(dbidev);

	dbi = &dbidev->dbi;
	drm = &dbidev->drm;

	dbi->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(dbi->reset)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
		वापस PTR_ERR(dbi->reset);
	पूर्ण

	rs = devm_gpiod_get(dev, "rs", GPIOD_OUT_LOW);
	अगर (IS_ERR(rs)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'rs'\n");
		वापस PTR_ERR(rs);
	पूर्ण

	device_property_पढ़ो_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, dbi, rs);
	अगर (ret)
		वापस ret;

	/* override the command function set in  mipi_dbi_spi_init() */
	dbi->command = ili9225_dbi_command;

	ret = mipi_dbi_dev_init(dbidev, &ili9225_pipe_funcs, &ili9225_mode, rotation);
	अगर (ret)
		वापस ret;

	drm_mode_config_reset(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, drm);

	drm_fbdev_generic_setup(drm, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ili9225_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

अटल व्योम ili9225_shutकरोwn(काष्ठा spi_device *spi)
अणु
	drm_atomic_helper_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल काष्ठा spi_driver ili9225_spi_driver = अणु
	.driver = अणु
		.name = "ili9225",
		.owner = THIS_MODULE,
		.of_match_table = ili9225_of_match,
	पूर्ण,
	.id_table = ili9225_id,
	.probe = ili9225_probe,
	.हटाओ = ili9225_हटाओ,
	.shutकरोwn = ili9225_shutकरोwn,
पूर्ण;
module_spi_driver(ili9225_spi_driver);

MODULE_DESCRIPTION("Ilitek ILI9225 DRM driver");
MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_LICENSE("GPL");
