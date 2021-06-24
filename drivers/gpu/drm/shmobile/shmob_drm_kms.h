<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * shmob_drm_kms.h  --  SH Mobile DRM Mode Setting
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __SHMOB_DRM_KMS_H__
#घोषणा __SHMOB_DRM_KMS_H__

#समावेश <linux/types.h>

काष्ठा drm_gem_cma_object;
काष्ठा shmob_drm_device;

काष्ठा shmob_drm_क्रमmat_info अणु
	u32 fourcc;
	अचिन्हित पूर्णांक bpp;
	bool yuv;
	u32 lddfr;
पूर्ण;

स्थिर काष्ठा shmob_drm_क्रमmat_info *shmob_drm_क्रमmat_info(u32 fourcc);

पूर्णांक shmob_drm_modeset_init(काष्ठा shmob_drm_device *sdev);

#पूर्ण_अगर /* __SHMOB_DRM_KMS_H__ */
