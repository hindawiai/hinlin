<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_DRM_FRONT_CFG_H_
#घोषणा __XEN_DRM_FRONT_CFG_H_

#समावेश <linux/types.h>

#घोषणा XEN_DRM_FRONT_MAX_CRTCS	4

काष्ठा xen_drm_front_cfg_connector अणु
	पूर्णांक width;
	पूर्णांक height;
	अक्षर *xenstore_path;
पूर्ण;

काष्ठा xen_drm_front_cfg अणु
	काष्ठा xen_drm_front_info *front_info;
	/* number of connectors in this configuration */
	पूर्णांक num_connectors;
	/* connector configurations */
	काष्ठा xen_drm_front_cfg_connector connectors[XEN_DRM_FRONT_MAX_CRTCS];
	/* set अगर dumb buffers are allocated बाह्यally on backend side */
	bool be_alloc;
पूर्ण;

पूर्णांक xen_drm_front_cfg_card(काष्ठा xen_drm_front_info *front_info,
			   काष्ठा xen_drm_front_cfg *cfg);

#पूर्ण_अगर /* __XEN_DRM_FRONT_CFG_H_ */
