<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#अगर_घोषित CONFIG_DRM_EXYNOS_G2D
बाह्य पूर्णांक exynos_g2d_get_ver_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
बाह्य पूर्णांक exynos_g2d_set_cmdlist_ioctl(काष्ठा drm_device *dev, व्योम *data,
					काष्ठा drm_file *file_priv);
बाह्य पूर्णांक exynos_g2d_exec_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv);

बाह्य पूर्णांक g2d_खोलो(काष्ठा drm_device *drm_dev, काष्ठा drm_file *file);
बाह्य व्योम g2d_बंद(काष्ठा drm_device *drm_dev, काष्ठा drm_file *file);
#अन्यथा
अटल अंतरभूत पूर्णांक exynos_g2d_get_ver_ioctl(काष्ठा drm_device *dev, व्योम *data,
					   काष्ठा drm_file *file_priv)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक exynos_g2d_set_cmdlist_ioctl(काष्ठा drm_device *dev,
					       व्योम *data,
					       काष्ठा drm_file *file_priv)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक exynos_g2d_exec_ioctl(काष्ठा drm_device *dev, व्योम *data,
					काष्ठा drm_file *file_priv)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक g2d_खोलो(काष्ठा drm_device *drm_dev, काष्ठा drm_file *file)
अणु
	वापस 0;
पूर्ण

व्योम g2d_बंद(काष्ठा drm_device *drm_dev, काष्ठा drm_file *file)
अणु पूर्ण
#पूर्ण_अगर
