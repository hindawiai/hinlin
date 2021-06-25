<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DRM driver क्रम Ilitek ILI9486 panels
 *
 * Copyright 2020 Kamlesh Gurudasani <kamlesh.gurudasani@gmail.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mipi_dbi.h>
#समावेश <drm/drm_modeset_helper.h>

#घोषणा ILI9486_ITFCTR1         0xb0
#घोषणा ILI9486_PWCTRL1         0xc2
#घोषणा ILI9486_VMCTRL1         0xc5
#घोषणा ILI9486_PGAMCTRL        0xe0
#घोषणा ILI9486_NGAMCTRL        0xe1
#घोषणा ILI9486_DGAMCTRL        0xe2
#घोषणा ILI9486_MADCTL_BGR      BIT(3)
#घोषणा ILI9486_MADCTL_MV       BIT(5)
#घोषणा ILI9486_MADCTL_MX       BIT(6)
#घोषणा ILI9486_MADCTL_MY       BIT(7)

/*
 * The PiScreen/waveshare rpi-lcd-35 has a SPI to 16-bit parallel bus converter
 * in front of the  display controller. This means that 8-bit values have to be
 * transferred as 16-bit.
 */
अटल पूर्णांक waveshare_command(काष्ठा mipi_dbi *mipi, u8 *cmd, u8 *par,
			     माप_प्रकार num)
अणु
	काष्ठा spi_device *spi = mipi->spi;
	व्योम *data = par;
	u32 speed_hz;
	पूर्णांक i, ret;
	__be16 *buf;

	buf = kदो_स्मृति(32 * माप(u16), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/*
	 * The displays are Raspberry Pi HATs and connected to the 8-bit only
	 * SPI controller, so 16-bit command and parameters need byte swapping
	 * beक्रमe being transferred as 8-bit on the big endian SPI bus.
	 * Pixel data bytes have alपढ़ोy been swapped beक्रमe this function is
	 * called.
	 */
	buf[0] = cpu_to_be16(*cmd);
	gpiod_set_value_cansleep(mipi->dc, 0);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, 2);
	ret = mipi_dbi_spi_transfer(spi, speed_hz, 8, buf, 2);
	अगर (ret || !num)
		जाओ मुक्त;

	/* 8-bit configuration data, not 16-bit pixel data */
	अगर (num <= 32) अणु
		क्रम (i = 0; i < num; i++)
			buf[i] = cpu_to_be16(par[i]);
		num *= 2;
		speed_hz = mipi_dbi_spi_cmd_max_speed(spi, num);
		data = buf;
	पूर्ण

	gpiod_set_value_cansleep(mipi->dc, 1);
	ret = mipi_dbi_spi_transfer(spi, speed_hz, 8, data, num);
 मुक्त:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल व्योम waveshare_enable(काष्ठा drm_simple_display_pipe *pipe,
			     काष्ठा drm_crtc_state *crtc_state,
			     काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	u8 addr_mode;
	पूर्णांक ret, idx;

	अगर (!drm_dev_enter(pipe->crtc.dev, &idx))
		वापस;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_घातeron_conditional_reset(dbidev);
	अगर (ret < 0)
		जाओ out_निकास;
	अगर (ret == 1)
		जाओ out_enable;

	mipi_dbi_command(dbi, ILI9486_ITFCTR1);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(250);

	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEL_FORMAT, 0x55);

	mipi_dbi_command(dbi, ILI9486_PWCTRL1, 0x44);

	mipi_dbi_command(dbi, ILI9486_VMCTRL1, 0x00, 0x00, 0x00, 0x00);

	mipi_dbi_command(dbi, ILI9486_PGAMCTRL,
			 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98,
			 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x0);
	mipi_dbi_command(dbi, ILI9486_NGAMCTRL,
			 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
			 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00);
	mipi_dbi_command(dbi, ILI9486_DGAMCTRL,
			 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
			 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);
	msleep(100);

 out_enable:
	चयन (dbidev->rotation) अणु
	हाल 90:
		addr_mode = ILI9486_MADCTL_MY;
		अवरोध;
	हाल 180:
		addr_mode = ILI9486_MADCTL_MV;
		अवरोध;
	हाल 270:
		addr_mode = ILI9486_MADCTL_MX;
		अवरोध;
	शेष:
		addr_mode = ILI9486_MADCTL_MV | ILI9486_MADCTL_MY |
			ILI9486_MADCTL_MX;
		अवरोध;
	पूर्ण
	addr_mode |= ILI9486_MADCTL_BGR;
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_enable_flush(dbidev, crtc_state, plane_state);
 out_निकास:
	drm_dev_निकास(idx);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs waveshare_pipe_funcs = अणु
	.enable = waveshare_enable,
	.disable = mipi_dbi_pipe_disable,
	.update = mipi_dbi_pipe_update,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode waveshare_mode = अणु
	DRM_SIMPLE_MODE(480, 320, 73, 49),
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(ili9486_fops);

अटल स्थिर काष्ठा drm_driver ili9486_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &ili9486_fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "ili9486",
	.desc			= "Ilitek ILI9486",
	.date			= "20200118",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ili9486_of_match[] = अणु
	अणु .compatible = "waveshare,rpi-lcd-35" पूर्ण,
	अणु .compatible = "ozzmaker,piscreen" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ili9486_of_match);

अटल स्थिर काष्ठा spi_device_id ili9486_id[] = अणु
	अणु "ili9486", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ili9486_id);

अटल पूर्णांक ili9486_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा mipi_dbi_dev *dbidev;
	काष्ठा drm_device *drm;
	काष्ठा mipi_dbi *dbi;
	काष्ठा gpio_desc *dc;
	u32 rotation = 0;
	पूर्णांक ret;

	dbidev = devm_drm_dev_alloc(dev, &ili9486_driver,
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

	dc = devm_gpiod_get(dev, "dc", GPIOD_OUT_LOW);
	अगर (IS_ERR(dc)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'dc'\n");
		वापस PTR_ERR(dc);
	पूर्ण

	dbidev->backlight = devm_of_find_backlight(dev);
	अगर (IS_ERR(dbidev->backlight))
		वापस PTR_ERR(dbidev->backlight);

	device_property_पढ़ो_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, dbi, dc);
	अगर (ret)
		वापस ret;

	dbi->command = waveshare_command;
	dbi->पढ़ो_commands = शून्य;

	ret = mipi_dbi_dev_init(dbidev, &waveshare_pipe_funcs,
				&waveshare_mode, rotation);
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

अटल पूर्णांक ili9486_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

अटल व्योम ili9486_shutकरोwn(काष्ठा spi_device *spi)
अणु
	drm_atomic_helper_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल काष्ठा spi_driver ili9486_spi_driver = अणु
	.driver = अणु
		.name = "ili9486",
		.of_match_table = ili9486_of_match,
	पूर्ण,
	.id_table = ili9486_id,
	.probe = ili9486_probe,
	.हटाओ = ili9486_हटाओ,
	.shutकरोwn = ili9486_shutकरोwn,
पूर्ण;
module_spi_driver(ili9486_spi_driver);

MODULE_DESCRIPTION("Ilitek ILI9486 DRM driver");
MODULE_AUTHOR("Kamlesh Gurudasani <kamlesh.gurudasani@gmail.com>");
MODULE_LICENSE("GPL");
