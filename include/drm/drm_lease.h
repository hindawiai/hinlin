<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 2017 Keith Packard <keithp@keithp.com>
 */

#अगर_अघोषित _DRM_LEASE_H_
#घोषणा _DRM_LEASE_H_

काष्ठा drm_file;
काष्ठा drm_device;
काष्ठा drm_master;

काष्ठा drm_master *drm_lease_owner(काष्ठा drm_master *master);

व्योम drm_lease_destroy(काष्ठा drm_master *lessee);

bool drm_lease_held(काष्ठा drm_file *file_priv, पूर्णांक id);

bool _drm_lease_held(काष्ठा drm_file *file_priv, पूर्णांक id);

व्योम drm_lease_revoke(काष्ठा drm_master *master);

uपूर्णांक32_t drm_lease_filter_crtcs(काष्ठा drm_file *file_priv, uपूर्णांक32_t crtcs);

पूर्णांक drm_mode_create_lease_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *file_priv);

पूर्णांक drm_mode_list_lessees_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *file_priv);

पूर्णांक drm_mode_get_lease_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *file_priv);

पूर्णांक drm_mode_revoke_lease_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *file_priv);

#पूर्ण_अगर /* _DRM_LEASE_H_ */
