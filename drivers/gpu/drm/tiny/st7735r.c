<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DRM driver क्रम display panels connected to a Sitronix ST7715R or ST7735R
 * display controller in SPI mode.
 *
 * Copyright 2017 David Lechner <david@lechnology.com>
 * Copyright (C) 2019 Glider bvba
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-buf.h>
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

#घोषणा ST7735R_FRMCTR1		0xb1
#घोषणा ST7735R_FRMCTR2		0xb2
#घोषणा ST7735R_FRMCTR3		0xb3
#घोषणा ST7735R_INVCTR		0xb4
#घोषणा ST7735R_PWCTR1		0xc0
#घोषणा ST7735R_PWCTR2		0xc1
#घोषणा ST7735R_PWCTR3		0xc2
#घोषणा ST7735R_PWCTR4		0xc3
#घोषणा ST7735R_PWCTR5		0xc4
#घोषणा ST7735R_VMCTR1		0xc5
#घोषणा ST7735R_GAMCTRP1	0xe0
#घोषणा ST7735R_GAMCTRN1	0xe1

#घोषणा ST7735R_MY	BIT(7)
#घोषणा ST7735R_MX	BIT(6)
#घोषणा ST7735R_MV	BIT(5)
#घोषणा ST7735R_RGB	BIT(3)

काष्ठा st7735r_cfg अणु
	स्थिर काष्ठा drm_display_mode mode;
	अचिन्हित पूर्णांक left_offset;
	अचिन्हित पूर्णांक top_offset;
	अचिन्हित पूर्णांक ग_लिखो_only:1;
	अचिन्हित पूर्णांक rgb:1;		/* RGB (vs. BGR) */
पूर्ण;

काष्ठा st7735r_priv अणु
	काष्ठा mipi_dbi_dev dbidev;	/* Must be first क्रम .release() */
	स्थिर काष्ठा st7735r_cfg *cfg;
पूर्ण;

अटल व्योम st7735r_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
				काष्ठा drm_crtc_state *crtc_state,
				काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा mipi_dbi_dev *dbidev = drm_to_mipi_dbi_dev(pipe->crtc.dev);
	काष्ठा st7735r_priv *priv = container_of(dbidev, काष्ठा st7735r_priv,
						 dbidev);
	काष्ठा mipi_dbi *dbi = &dbidev->dbi;
	पूर्णांक ret, idx;
	u8 addr_mode;

	अगर (!drm_dev_enter(pipe->crtc.dev, &idx))
		वापस;

	DRM_DEBUG_KMS("\n");

	ret = mipi_dbi_घातeron_reset(dbidev);
	अगर (ret)
		जाओ out_निकास;

	msleep(150);

	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(500);

	mipi_dbi_command(dbi, ST7735R_FRMCTR1, 0x01, 0x2c, 0x2d);
	mipi_dbi_command(dbi, ST7735R_FRMCTR2, 0x01, 0x2c, 0x2d);
	mipi_dbi_command(dbi, ST7735R_FRMCTR3, 0x01, 0x2c, 0x2d, 0x01, 0x2c,
			 0x2d);
	mipi_dbi_command(dbi, ST7735R_INVCTR, 0x07);
	mipi_dbi_command(dbi, ST7735R_PWCTR1, 0xa2, 0x02, 0x84);
	mipi_dbi_command(dbi, ST7735R_PWCTR2, 0xc5);
	mipi_dbi_command(dbi, ST7735R_PWCTR3, 0x0a, 0x00);
	mipi_dbi_command(dbi, ST7735R_PWCTR4, 0x8a, 0x2a);
	mipi_dbi_command(dbi, ST7735R_PWCTR5, 0x8a, 0xee);
	mipi_dbi_command(dbi, ST7735R_VMCTR1, 0x0e);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_INVERT_MODE);
	चयन (dbidev->rotation) अणु
	शेष:
		addr_mode = ST7735R_MX | ST7735R_MY;
		अवरोध;
	हाल 90:
		addr_mode = ST7735R_MX | ST7735R_MV;
		अवरोध;
	हाल 180:
		addr_mode = 0;
		अवरोध;
	हाल 270:
		addr_mode = ST7735R_MY | ST7735R_MV;
		अवरोध;
	पूर्ण

	अगर (priv->cfg->rgb)
		addr_mode |= ST7735R_RGB;

	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEL_FORMAT,
			 MIPI_DCS_PIXEL_FMT_16BIT);
	mipi_dbi_command(dbi, ST7735R_GAMCTRP1, 0x02, 0x1c, 0x07, 0x12, 0x37,
			 0x32, 0x29, 0x2d, 0x29, 0x25, 0x2b, 0x39, 0x00, 0x01,
			 0x03, 0x10);
	mipi_dbi_command(dbi, ST7735R_GAMCTRN1, 0x03, 0x1d, 0x07, 0x06, 0x2e,
			 0x2c, 0x29, 0x2d, 0x2e, 0x2e, 0x37, 0x3f, 0x00, 0x00,
			 0x02, 0x10);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);

	msleep(100);

	mipi_dbi_command(dbi, MIPI_DCS_ENTER_NORMAL_MODE);

	msleep(20);

	mipi_dbi_enable_flush(dbidev, crtc_state, plane_state);
out_निकास:
	drm_dev_निकास(idx);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs st7735r_pipe_funcs = अणु
	.enable		= st7735r_pipe_enable,
	.disable	= mipi_dbi_pipe_disable,
	.update		= mipi_dbi_pipe_update,
	.prepare_fb	= drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा st7735r_cfg jd_t18003_t01_cfg = अणु
	.mode		= अणु DRM_SIMPLE_MODE(128, 160, 28, 35) पूर्ण,
	/* Cannot पढ़ो from Adafruit 1.8" display via SPI */
	.ग_लिखो_only	= true,
पूर्ण;

अटल स्थिर काष्ठा st7735r_cfg rh128128t_cfg = अणु
	.mode		= अणु DRM_SIMPLE_MODE(128, 128, 25, 26) पूर्ण,
	.left_offset	= 2,
	.top_offset	= 3,
	.rgb		= true,
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(st7735r_fops);

अटल स्थिर काष्ठा drm_driver st7735r_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &st7735r_fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "st7735r",
	.desc			= "Sitronix ST7735R",
	.date			= "20171128",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id st7735r_of_match[] = अणु
	अणु .compatible = "jianda,jd-t18003-t01", .data = &jd_t18003_t01_cfg पूर्ण,
	अणु .compatible = "okaya,rh128128t", .data = &rh128128t_cfg पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st7735r_of_match);

अटल स्थिर काष्ठा spi_device_id st7735r_id[] = अणु
	अणु "jd-t18003-t01", (uपूर्णांकptr_t)&jd_t18003_t01_cfg पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, st7735r_id);

अटल पूर्णांक st7735r_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	स्थिर काष्ठा st7735r_cfg *cfg;
	काष्ठा mipi_dbi_dev *dbidev;
	काष्ठा st7735r_priv *priv;
	काष्ठा drm_device *drm;
	काष्ठा mipi_dbi *dbi;
	काष्ठा gpio_desc *dc;
	u32 rotation = 0;
	पूर्णांक ret;

	cfg = device_get_match_data(&spi->dev);
	अगर (!cfg)
		cfg = (व्योम *)spi_get_device_id(spi)->driver_data;

	priv = devm_drm_dev_alloc(dev, &st7735r_driver,
				  काष्ठा st7735r_priv, dbidev.drm);
	अगर (IS_ERR(priv))
		वापस PTR_ERR(priv);

	dbidev = &priv->dbidev;
	priv->cfg = cfg;

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

	अगर (cfg->ग_लिखो_only)
		dbi->पढ़ो_commands = शून्य;

	dbidev->left_offset = cfg->left_offset;
	dbidev->top_offset = cfg->top_offset;

	ret = mipi_dbi_dev_init(dbidev, &st7735r_pipe_funcs, &cfg->mode,
				rotation);
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

अटल पूर्णांक st7735r_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

अटल व्योम st7735r_shutकरोwn(काष्ठा spi_device *spi)
अणु
	drm_atomic_helper_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल काष्ठा spi_driver st7735r_spi_driver = अणु
	.driver = अणु
		.name = "st7735r",
		.of_match_table = st7735r_of_match,
	पूर्ण,
	.id_table = st7735r_id,
	.probe = st7735r_probe,
	.हटाओ = st7735r_हटाओ,
	.shutकरोwn = st7735r_shutकरोwn,
पूर्ण;
module_spi_driver(st7735r_spi_driver);

MODULE_DESCRIPTION("Sitronix ST7735R DRM driver");
MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_LICENSE("GPL");
