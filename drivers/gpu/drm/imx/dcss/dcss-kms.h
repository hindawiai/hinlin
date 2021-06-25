<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 NXP.
 */

#अगर_अघोषित _DCSS_KMS_H_
#घोषणा _DCSS_KMS_H_

#समावेश <drm/drm_encoder.h>

काष्ठा dcss_plane अणु
	काष्ठा drm_plane base;

	पूर्णांक ch_num;
पूर्ण;

काष्ठा dcss_crtc अणु
	काष्ठा drm_crtc		base;
	काष्ठा drm_crtc_state	*state;

	काष्ठा dcss_plane	*plane[3];

	पूर्णांक			irq;

	bool disable_ctxld_kick_irq;
पूर्ण;

काष्ठा dcss_kms_dev अणु
	काष्ठा drm_device base;
	काष्ठा dcss_crtc crtc;
	काष्ठा drm_encoder encoder;
	काष्ठा drm_connector *connector;
पूर्ण;

काष्ठा dcss_kms_dev *dcss_kms_attach(काष्ठा dcss_dev *dcss);
व्योम dcss_kms_detach(काष्ठा dcss_kms_dev *kms);
पूर्णांक dcss_crtc_init(काष्ठा dcss_crtc *crtc, काष्ठा drm_device *drm);
व्योम dcss_crtc_deinit(काष्ठा dcss_crtc *crtc, काष्ठा drm_device *drm);
काष्ठा dcss_plane *dcss_plane_init(काष्ठा drm_device *drm,
				   अचिन्हित पूर्णांक possible_crtcs,
				   क्रमागत drm_plane_type type,
				   अचिन्हित पूर्णांक zpos);

#पूर्ण_अगर
