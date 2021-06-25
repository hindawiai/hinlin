<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DRM driver क्रम Multi-Inno MI0283QT panels
 *
 * Copyright 2016 Noralf Trथचnnes
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mipi_dbi.h>
#समावेश <drm/drm_modeset_helper.h>
#समावेश <video/mipi_display.h>

#घोषणा ILI9341_FRMCTR1		0xb1
#घोषणा ILI9341_DISCTRL		0xb6
#घोषणा ILI9341_ETMOD		0xb7

#घोषणा ILI9341_PWCTRL1		0xc0
#घोषणा ILI9341_PWCTRL2		0xc1
#घोषणा ILI9341_VMCTRL1		0xc5
#घोषणा ILI9341_VMCTRL2		0xc7
#घोषणा ILI9341_PWCTRLA		0xcb
#घोषणा ILI9341_PWCTRLB		0xcf

#घोषणा ILI9341_PGAMCTRL	0xe0
#घोषणा ILI9341_NGAMCTRL	0xe1
#घोषणा ILI9341_DTCTRLA		0xe8
#घोषणा ILI9341_DTCTRLB		0xea
#घोषणा ILI9341_PWRSEQ		0xed

#घोषणा ILI9341_EN3GAM		0xf2
#घोषणा ILI9341_PUMPCTRL	0xf7

#घोषणा ILI9341_MADCTL_BGR	BIT(3)
#घोषणा ILI9341_MADCTL_MV	BIT(5)
#घोषणा ILI9341_MADCTL_MX	BIT(6)
#घोषणा ILI9341_MADCTL_MY	BIT(7)

अटल व्योम mi0283qt_enable(काष्ठा drm_simple_display_pipe *pipe,
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

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_OFF);

	mipi_dbi_command(dbi, ILI9341_PWCTRLB, 0x00, 0x83, 0x30);
	mipi_dbi_command(dbi, ILI9341_PWRSEQ, 0x64, 0x03, 0x12, 0x81);
	mipi_dbi_command(dbi, ILI9341_DTCTRLA, 0x85, 0x01, 0x79);
	mipi_dbi_command(dbi, ILI9341_PWCTRLA, 0x39, 0x2c, 0x00, 0x34, 0x02);
	mipi_dbi_command(dbi, ILI9341_PUMPCTRL, 0x20);
	mipi_dbi_command(dbi, ILI9341_DTCTRLB, 0x00, 0x00);

	/* Power Control */
	mipi_dbi_command(dbi, ILI9341_PWCTRL1, 0x26);
	mipi_dbi_command(dbi, ILI9341_PWCTRL2, 0x11);
	/* VCOM */
	mipi_dbi_command(dbi, ILI9341_VMCTRL1, 0x35, 0x3e);
	mipi_dbi_command(dbi, ILI9341_VMCTRL2, 0xbe);

	/* Memory Access Control */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEL_FORMAT, MIPI_DCS_PIXEL_FMT_16BIT);

	/* Frame Rate */
	mipi_dbi_command(dbi, ILI9341_FRMCTR1, 0x00, 0x1b);

	/* Gamma */
	mipi_dbi_command(dbi, ILI9341_EN3GAM, 0x08);
	mipi_dbi_command(dbi, MIPI_DCS_SET_GAMMA_CURVE, 0x01);
	mipi_dbi_command(dbi, ILI9341_PGAMCTRL,
		       0x1f, 0x1a, 0x18, 0x0a, 0x0f, 0x06, 0x45, 0x87,
		       0x32, 0x0a, 0x07, 0x02, 0x07, 0x05, 0x00);
	mipi_dbi_command(dbi, ILI9341_NGAMCTRL,
		       0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3a, 0x78,
		       0x4d, 0x05, 0x18, 0x0d, 0x38, 0x3a, 0x1f);

	/* DDRAM */
	mipi_dbi_command(dbi, ILI9341_ETMOD, 0x07);

	/* Display */
	mipi_dbi_command(dbi, ILI9341_DISCTRL, 0x0a, 0x82, 0x27, 0x00);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(100);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);
	msleep(100);

out_enable:
	/* The PiTFT (ili9340) has a hardware reset circuit that
	 * resets only on घातer-on and not on each reboot through
	 * a gpio like the rpi-display करोes.
	 * As a result, we need to always apply the rotation value
	 * regardless of the display "on/off" state.
	 */
	चयन (dbidev->rotation) अणु
	शेष:
		addr_mode = ILI9341_MADCTL_MV | ILI9341_MADCTL_MY |
			    ILI9341_MADCTL_MX;
		अवरोध;
	हाल 90:
		addr_mode = ILI9341_MADCTL_MY;
		अवरोध;
	हाल 180:
		addr_mode = ILI9341_MADCTL_MV;
		अवरोध;
	हाल 270:
		addr_mode = ILI9341_MADCTL_MX;
		अवरोध;
	पूर्ण
	addr_mode |= ILI9341_MADCTL_BGR;
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_enable_flush(dbidev, crtc_state, plane_state);
out_निकास:
	drm_dev_निकास(idx);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs mi0283qt_pipe_funcs = अणु
	.enable = mi0283qt_enable,
	.disable = mipi_dbi_pipe_disable,
	.update = mipi_dbi_pipe_update,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode mi0283qt_mode = अणु
	DRM_SIMPLE_MODE(320, 240, 58, 43),
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(mi0283qt_fops);

अटल स्थिर काष्ठा drm_driver mi0283qt_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &mi0283qt_fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "mi0283qt",
	.desc			= "Multi-Inno MI0283QT",
	.date			= "20160614",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mi0283qt_of_match[] = अणु
	अणु .compatible = "multi-inno,mi0283qt" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mi0283qt_of_match);

अटल स्थिर काष्ठा spi_device_id mi0283qt_id[] = अणु
	अणु "mi0283qt", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, mi0283qt_id);

अटल पूर्णांक mi0283qt_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा mipi_dbi_dev *dbidev;
	काष्ठा drm_device *drm;
	काष्ठा mipi_dbi *dbi;
	काष्ठा gpio_desc *dc;
	u32 rotation = 0;
	पूर्णांक ret;

	dbidev = devm_drm_dev_alloc(dev, &mi0283qt_driver,
				    काष्ठा mipi_dbi_dev, drm);
	अगर (IS_ERR(dbidev))
		वापस PTR_ERR(dbidev);

	dbi = &dbidev->dbi;
	drm = &dbidev->drm;

	dbi->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(dbi->reset)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
		वापस PTR_ERR(dbi->reset);
	पूर्ण

	dc = devm_gpiod_get_optional(dev, "dc", GPIOD_OUT_LOW);
	अगर (IS_ERR(dc)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'dc'\n");
		वापस PTR_ERR(dc);
	पूर्ण

	dbidev->regulator = devm_regulator_get(dev, "power");
	अगर (IS_ERR(dbidev->regulator))
		वापस PTR_ERR(dbidev->regulator);

	dbidev->backlight = devm_of_find_backlight(dev);
	अगर (IS_ERR(dbidev->backlight))
		वापस PTR_ERR(dbidev->backlight);

	device_property_पढ़ो_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, dbi, dc);
	अगर (ret)
		वापस ret;

	ret = mipi_dbi_dev_init(dbidev, &mi0283qt_pipe_funcs, &mi0283qt_mode, rotation);
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

अटल पूर्णांक mi0283qt_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

अटल व्योम mi0283qt_shutकरोwn(काष्ठा spi_device *spi)
अणु
	drm_atomic_helper_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल पूर्णांक __maybe_unused mi0283qt_pm_suspend(काष्ठा device *dev)
अणु
	वापस drm_mode_config_helper_suspend(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक __maybe_unused mi0283qt_pm_resume(काष्ठा device *dev)
अणु
	drm_mode_config_helper_resume(dev_get_drvdata(dev));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mi0283qt_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mi0283qt_pm_suspend, mi0283qt_pm_resume)
पूर्ण;

अटल काष्ठा spi_driver mi0283qt_spi_driver = अणु
	.driver = अणु
		.name = "mi0283qt",
		.owner = THIS_MODULE,
		.of_match_table = mi0283qt_of_match,
		.pm = &mi0283qt_pm_ops,
	पूर्ण,
	.id_table = mi0283qt_id,
	.probe = mi0283qt_probe,
	.हटाओ = mi0283qt_हटाओ,
	.shutकरोwn = mi0283qt_shutकरोwn,
पूर्ण;
module_spi_driver(mi0283qt_spi_driver);

MODULE_DESCRIPTION("Multi-Inno MI0283QT DRM driver");
MODULE_AUTHOR("Noralf Trथचnnes");
MODULE_LICENSE("GPL");
