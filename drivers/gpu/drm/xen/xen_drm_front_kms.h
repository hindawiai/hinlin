<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_DRM_FRONT_KMS_H_
#घोषणा __XEN_DRM_FRONT_KMS_H_

#समावेश <linux/types.h>

काष्ठा xen_drm_front_drm_info;
काष्ठा xen_drm_front_drm_pipeline;

पूर्णांक xen_drm_front_kms_init(काष्ठा xen_drm_front_drm_info *drm_info);

व्योम xen_drm_front_kms_fini(काष्ठा xen_drm_front_drm_info *drm_info);

व्योम xen_drm_front_kms_on_frame_करोne(काष्ठा xen_drm_front_drm_pipeline *pipeline,
				     u64 fb_cookie);

#पूर्ण_अगर /* __XEN_DRM_FRONT_KMS_H_ */
