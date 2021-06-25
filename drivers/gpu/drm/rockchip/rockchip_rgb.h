<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:
 *      Sandy Huang <hjc@rock-chips.com>
 */

#अगर_घोषित CONFIG_ROCKCHIP_RGB
काष्ठा rockchip_rgb *rockchip_rgb_init(काष्ठा device *dev,
				       काष्ठा drm_crtc *crtc,
				       काष्ठा drm_device *drm_dev);
व्योम rockchip_rgb_fini(काष्ठा rockchip_rgb *rgb);
#अन्यथा
अटल अंतरभूत काष्ठा rockchip_rgb *rockchip_rgb_init(काष्ठा device *dev,
						     काष्ठा drm_crtc *crtc,
						     काष्ठा drm_device *drm_dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम rockchip_rgb_fini(काष्ठा rockchip_rgb *rgb)
अणु
पूर्ण
#पूर्ण_अगर
