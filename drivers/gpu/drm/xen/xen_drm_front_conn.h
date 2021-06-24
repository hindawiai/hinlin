<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_DRM_FRONT_CONN_H_
#घोषणा __XEN_DRM_FRONT_CONN_H_

#समावेश <linux/types.h>

काष्ठा drm_connector;
काष्ठा xen_drm_front_drm_info;


पूर्णांक xen_drm_front_conn_init(काष्ठा xen_drm_front_drm_info *drm_info,
			    काष्ठा drm_connector *connector);

स्थिर u32 *xen_drm_front_conn_get_क्रमmats(पूर्णांक *क्रमmat_count);

#पूर्ण_अगर /* __XEN_DRM_FRONT_CONN_H_ */
