<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Analogix DP (Display Port) Core पूर्णांकerface driver.
 *
 * Copyright (C) 2015 Rockchip Electronics Co., Ltd.
 */
#अगर_अघोषित _ANALOGIX_DP_H_
#घोषणा _ANALOGIX_DP_H_

#समावेश <drm/drm_crtc.h>

काष्ठा analogix_dp_device;

क्रमागत analogix_dp_devtype अणु
	EXYNOS_DP,
	RK3288_DP,
	RK3399_EDP,
पूर्ण;

अटल अंतरभूत bool is_rockchip(क्रमागत analogix_dp_devtype type)
अणु
	वापस type == RK3288_DP || type == RK3399_EDP;
पूर्ण

काष्ठा analogix_dp_plat_data अणु
	क्रमागत analogix_dp_devtype dev_type;
	काष्ठा drm_panel *panel;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	bool skip_connector;

	पूर्णांक (*घातer_on_start)(काष्ठा analogix_dp_plat_data *);
	पूर्णांक (*घातer_on_end)(काष्ठा analogix_dp_plat_data *);
	पूर्णांक (*घातer_off)(काष्ठा analogix_dp_plat_data *);
	पूर्णांक (*attach)(काष्ठा analogix_dp_plat_data *, काष्ठा drm_bridge *,
		      काष्ठा drm_connector *);
	पूर्णांक (*get_modes)(काष्ठा analogix_dp_plat_data *,
			 काष्ठा drm_connector *);
पूर्ण;

पूर्णांक analogix_dp_resume(काष्ठा analogix_dp_device *dp);
पूर्णांक analogix_dp_suspend(काष्ठा analogix_dp_device *dp);

काष्ठा analogix_dp_device *
analogix_dp_probe(काष्ठा device *dev, काष्ठा analogix_dp_plat_data *plat_data);
पूर्णांक analogix_dp_bind(काष्ठा analogix_dp_device *dp, काष्ठा drm_device *drm_dev);
व्योम analogix_dp_unbind(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_हटाओ(काष्ठा analogix_dp_device *dp);

पूर्णांक analogix_dp_start_crc(काष्ठा drm_connector *connector);
पूर्णांक analogix_dp_stop_crc(काष्ठा drm_connector *connector);

#पूर्ण_अगर /* _ANALOGIX_DP_H_ */
