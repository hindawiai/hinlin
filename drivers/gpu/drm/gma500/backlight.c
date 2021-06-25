<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GMA500 Backlight Interface
 *
 * Copyright (c) 2009-2011, Intel Corporation.
 *
 * Authors: Eric Knopp
 */

#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_intel_drv.h"
#समावेश "intel_bios.h"
#समावेश "power.h"

#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
अटल व्योम करो_gma_backlight_set(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	backlight_update_status(dev_priv->backlight_device);
पूर्ण
#पूर्ण_अगर

व्योम gma_backlight_enable(काष्ठा drm_device *dev)
अणु
#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	dev_priv->backlight_enabled = true;
	अगर (dev_priv->backlight_device) अणु
		dev_priv->backlight_device->props.brightness = dev_priv->backlight_level;
		करो_gma_backlight_set(dev);
	पूर्ण
#पूर्ण_अगर	
पूर्ण

व्योम gma_backlight_disable(काष्ठा drm_device *dev)
अणु
#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	dev_priv->backlight_enabled = false;
	अगर (dev_priv->backlight_device) अणु
		dev_priv->backlight_device->props.brightness = 0;
		करो_gma_backlight_set(dev);
	पूर्ण
#पूर्ण_अगर	
पूर्ण

व्योम gma_backlight_set(काष्ठा drm_device *dev, पूर्णांक v)
अणु
#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	dev_priv->backlight_level = v;
	अगर (dev_priv->backlight_device && dev_priv->backlight_enabled) अणु
		dev_priv->backlight_device->props.brightness = v;
		करो_gma_backlight_set(dev);
	पूर्ण
#पूर्ण_अगर	
पूर्ण

पूर्णांक gma_backlight_init(काष्ठा drm_device *dev)
अणु
#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	dev_priv->backlight_enabled = true;
	वापस dev_priv->ops->backlight_init(dev);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

व्योम gma_backlight_निकास(काष्ठा drm_device *dev)
अणु
#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अगर (dev_priv->backlight_device) अणु
		dev_priv->backlight_device->props.brightness = 0;
		backlight_update_status(dev_priv->backlight_device);
		backlight_device_unरेजिस्टर(dev_priv->backlight_device);
	पूर्ण
#पूर्ण_अगर
पूर्ण
