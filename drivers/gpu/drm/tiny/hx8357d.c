<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DRM driver क्रम the HX8357D LCD controller
 *
 * Copyright 2018 Broadcom
 * Copyright 2018 David Lechner <david@lechnology.com>
 * Copyright 2016 Noralf Trथचnnes
 * Copyright (C) 2015 Adafruit Industries
 * Copyright (C) 2013 Christian Vogelgsang
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
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

#घोषणा HX8357D_SETOSC 0xb0
#घोषणा HX8357D_SETPOWER 0xb1
#घोषणा HX8357D_SETRGB 0xb3
#घोषणा HX8357D_SETCYC 0xb3
#घोषणा HX8357D_SETCOM 0xb6
#घोषणा HX8357D_SETEXTC 0xb9
#घोषणा HX8357D_SETSTBA 0xc0
#घोषणा HX8357D_SETPANEL 0xcc
#घोषणा HX8357D_SETGAMMA 0xe0

#घोषणा HX8357D_MADCTL_MY  0x80
#घोषणा HX8357D_MADCTL_MX  0x40
#घोषणा HX8357D_MADCTL_MV  0x20
#घोषणा HX8357D_MADCTL_ML  0x10
#घोषणा HX8357D_MADCTL_RGB 0x00
#घोषणा HX8357D_MADCTL_BGR 0x08
#घोषणा HX8357D_MADCTL_MH  0x04

अटल व्योम yx240qv29_enable(काष्ठा drm_simple_display_pipe *pipe,
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

	/* setextc */
	mipi_dbi_command(dbi, HX8357D_SETEXTC, 0xFF, 0x83, 0x57);
	msleep(150);

	/* setRGB which also enables SDO */
	mipi_dbi_command(dbi, HX8357D_SETRGB, 0x00, 0x00, 0x06, 0x06);

	/* -1.52V */
	mipi_dbi_command(dbi, HX8357D_SETCOM, 0x25);

	/* Normal mode 70Hz, Idle mode 55 Hz */
	mipi_dbi_command(dbi, HX8357D_SETOSC, 0x68);

	/* Set Panel - BGR, Gate direction swapped */
	mipi_dbi_command(dbi, HX8357D_SETPANEL, 0x05);

	mipi_dbi_command(dbi, HX8357D_SETPOWER,
			 0x00,  /* Not deep standby */
			 0x15,  /* BT */
			 0x1C,  /* VSPR */
			 0x1C,  /* VSNR */
			 0x83,  /* AP */
			 0xAA);  /* FS */

	mipi_dbi_command(dbi, HX8357D_SETSTBA,
			 0x50,  /* OPON normal */
			 0x50,  /* OPON idle */
			 0x01,  /* STBA */
			 0x3C,  /* STBA */
			 0x1E,  /* STBA */
			 0x08);  /* GEN */

	mipi_dbi_command(dbi, HX8357D_SETCYC,
			 0x02,  /* NW 0x02 */
			 0x40,  /* RTN */
			 0x00,  /* DIV */
			 0x2A,  /* DUM */
			 0x2A,  /* DUM */
			 0x0D,  /* GDON */
			 0x78);  /* GDOFF */

	mipi_dbi_command(dbi, HX8357D_SETGAMMA,
			 0x02,
			 0x0A,
			 0x11,
			 0x1d,
			 0x23,
			 0x35,
			 0x41,
			 0x4b,
			 0x4b,
			 0x42,
			 0x3A,
			 0x27,
			 0x1B,
			 0x08,
			 0x09,
			 0x03,
			 0x02,
			 0x0A,
			 0x11,
			 0x1d,
			 0x23,
			 0x35,
			 0x41,
			 0x4b,
			 0x4b,
			 0x42,
			 0x3A,
			 0x27,
			 0x1B,
			 0x08,
			 0x09,
			 0x03,
			 0x00,
			 0x01);

	/* 16 bit */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEL_FORMAT,
			 MIPI_DCS_PIXEL_FMT_16BIT);

	/* TE off */
	mipi_dbi_command(dbi, MIPI_DCS_SET_TEAR_ON, 0x00);

	/* tear line */
	mipi_dbi_command(dbi, MIPI_DCS_SET_TEAR_SCANLINE, 0x00, 0x02);

	/* Exit Sleep */
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(150);

	/* display on */
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPLAY_ON);
	usleep_range(5000, 7000);

out_enable:
	चयन (dbidev->rotation) अणु
	शेष:
		addr_mode = HX8357D_MADCTL_MX | HX8357D_MADCTL_MY;
		अवरोध;
	हाल 90:
		addr_mode = HX8357D_MADCTL_MV | HX8357D_MADCTL_MY;
		अवरोध;
	हाल 180:
		addr_mode = 0;
		अवरोध;
	हाल 270:
		addr_mode = HX8357D_MADCTL_MV | HX8357D_MADCTL_MX;
		अवरोध;
	पूर्ण
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_enable_flush(dbidev, crtc_state, plane_state);
out_निकास:
	drm_dev_निकास(idx);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs hx8357d_pipe_funcs = अणु
	.enable = yx240qv29_enable,
	.disable = mipi_dbi_pipe_disable,
	.update = mipi_dbi_pipe_update,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode yx350hv15_mode = अणु
	DRM_SIMPLE_MODE(320, 480, 60, 75),
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(hx8357d_fops);

अटल स्थिर काष्ठा drm_driver hx8357d_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &hx8357d_fops,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "hx8357d",
	.desc			= "HX8357D",
	.date			= "20181023",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hx8357d_of_match[] = अणु
	अणु .compatible = "adafruit,yx350hv15" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hx8357d_of_match);

अटल स्थिर काष्ठा spi_device_id hx8357d_id[] = अणु
	अणु "yx350hv15", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, hx8357d_id);

अटल पूर्णांक hx8357d_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा mipi_dbi_dev *dbidev;
	काष्ठा drm_device *drm;
	काष्ठा gpio_desc *dc;
	u32 rotation = 0;
	पूर्णांक ret;

	dbidev = devm_drm_dev_alloc(dev, &hx8357d_driver,
				    काष्ठा mipi_dbi_dev, drm);
	अगर (IS_ERR(dbidev))
		वापस PTR_ERR(dbidev);

	drm = &dbidev->drm;

	dc = devm_gpiod_get(dev, "dc", GPIOD_OUT_LOW);
	अगर (IS_ERR(dc)) अणु
		DRM_DEV_ERROR(dev, "Failed to get gpio 'dc'\n");
		वापस PTR_ERR(dc);
	पूर्ण

	dbidev->backlight = devm_of_find_backlight(dev);
	अगर (IS_ERR(dbidev->backlight))
		वापस PTR_ERR(dbidev->backlight);

	device_property_पढ़ो_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, &dbidev->dbi, dc);
	अगर (ret)
		वापस ret;

	ret = mipi_dbi_dev_init(dbidev, &hx8357d_pipe_funcs, &yx350hv15_mode, rotation);
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

अटल पूर्णांक hx8357d_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा drm_device *drm = spi_get_drvdata(spi);

	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);

	वापस 0;
पूर्ण

अटल व्योम hx8357d_shutकरोwn(काष्ठा spi_device *spi)
अणु
	drm_atomic_helper_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल काष्ठा spi_driver hx8357d_spi_driver = अणु
	.driver = अणु
		.name = "hx8357d",
		.of_match_table = hx8357d_of_match,
	पूर्ण,
	.id_table = hx8357d_id,
	.probe = hx8357d_probe,
	.हटाओ = hx8357d_हटाओ,
	.shutकरोwn = hx8357d_shutकरोwn,
पूर्ण;
module_spi_driver(hx8357d_spi_driver);

MODULE_DESCRIPTION("HX8357D DRM driver");
MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_LICENSE("GPL");
