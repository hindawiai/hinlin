<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * shmob_drm_backlight.c  --  SH Mobile DRM Backlight
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/backlight.h>

#समावेश "shmob_drm_backlight.h"
#समावेश "shmob_drm_crtc.h"
#समावेश "shmob_drm_drv.h"

अटल पूर्णांक shmob_drm_backlight_update(काष्ठा backlight_device *bdev)
अणु
	काष्ठा shmob_drm_connector *scon = bl_get_data(bdev);
	काष्ठा shmob_drm_device *sdev = scon->connector.dev->dev_निजी;
	स्थिर काष्ठा shmob_drm_backlight_data *bdata = &sdev->pdata->backlight;
	पूर्णांक brightness = bdev->props.brightness;

	अगर (bdev->props.घातer != FB_BLANK_UNBLANK ||
	    bdev->props.state & BL_CORE_SUSPENDED)
		brightness = 0;

	वापस bdata->set_brightness(brightness);
पूर्ण

अटल पूर्णांक shmob_drm_backlight_get_brightness(काष्ठा backlight_device *bdev)
अणु
	काष्ठा shmob_drm_connector *scon = bl_get_data(bdev);
	काष्ठा shmob_drm_device *sdev = scon->connector.dev->dev_निजी;
	स्थिर काष्ठा shmob_drm_backlight_data *bdata = &sdev->pdata->backlight;

	वापस bdata->get_brightness();
पूर्ण

अटल स्थिर काष्ठा backlight_ops shmob_drm_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= shmob_drm_backlight_update,
	.get_brightness	= shmob_drm_backlight_get_brightness,
पूर्ण;

व्योम shmob_drm_backlight_dpms(काष्ठा shmob_drm_connector *scon, पूर्णांक mode)
अणु
	अगर (scon->backlight == शून्य)
		वापस;

	scon->backlight->props.घातer = mode == DRM_MODE_DPMS_ON
				     ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
	backlight_update_status(scon->backlight);
पूर्ण

पूर्णांक shmob_drm_backlight_init(काष्ठा shmob_drm_connector *scon)
अणु
	काष्ठा shmob_drm_device *sdev = scon->connector.dev->dev_निजी;
	स्थिर काष्ठा shmob_drm_backlight_data *bdata = &sdev->pdata->backlight;
	काष्ठा drm_connector *connector = &scon->connector;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा backlight_device *backlight;

	अगर (!bdata->max_brightness)
		वापस 0;

	backlight = backlight_device_रेजिस्टर(bdata->name, dev->dev, scon,
					      &shmob_drm_backlight_ops, शून्य);
	अगर (IS_ERR(backlight)) अणु
		dev_err(dev->dev, "unable to register backlight device: %ld\n",
			PTR_ERR(backlight));
		वापस PTR_ERR(backlight);
	पूर्ण

	backlight->props.max_brightness = bdata->max_brightness;
	backlight->props.brightness = bdata->max_brightness;
	backlight->props.घातer = FB_BLANK_POWERDOWN;
	backlight_update_status(backlight);

	scon->backlight = backlight;
	वापस 0;
पूर्ण

व्योम shmob_drm_backlight_निकास(काष्ठा shmob_drm_connector *scon)
अणु
	backlight_device_unरेजिस्टर(scon->backlight);
पूर्ण
