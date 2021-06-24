<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * Freescale DCU drm device driver
 */

#अगर_अघोषित __FSL_DCU_DRM_CONNECTOR_H__
#घोषणा __FSL_DCU_DRM_CONNECTOR_H__

काष्ठा fsl_dcu_drm_connector अणु
	काष्ठा drm_connector base;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_panel *panel;
पूर्ण;

अटल अंतरभूत काष्ठा fsl_dcu_drm_connector *
to_fsl_dcu_connector(काष्ठा drm_connector *con)
अणु
	वापस con ? container_of(con, काष्ठा fsl_dcu_drm_connector, base)
		     : शून्य;
पूर्ण

पूर्णांक fsl_dcu_drm_encoder_create(काष्ठा fsl_dcu_drm_device *fsl_dev,
			       काष्ठा drm_crtc *crtc);
पूर्णांक fsl_dcu_create_outमाला_दो(काष्ठा fsl_dcu_drm_device *fsl_dev);

#पूर्ण_अगर /* __FSL_DCU_DRM_CONNECTOR_H__ */
