<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * shmob_drm_crtc.h  --  SH Mobile DRM CRTCs
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __SHMOB_DRM_CRTC_H__
#घोषणा __SHMOB_DRM_CRTC_H__

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_encoder.h>

काष्ठा backlight_device;
काष्ठा drm_pending_vblank_event;
काष्ठा shmob_drm_device;
काष्ठा shmob_drm_क्रमmat_info;

काष्ठा shmob_drm_crtc अणु
	काष्ठा drm_crtc crtc;

	काष्ठा drm_pending_vblank_event *event;
	पूर्णांक dpms;

	स्थिर काष्ठा shmob_drm_क्रमmat_info *क्रमmat;
	अचिन्हित दीर्घ dma[2];
	अचिन्हित पूर्णांक line_size;
	bool started;
पूर्ण;

काष्ठा shmob_drm_encoder अणु
	काष्ठा drm_encoder encoder;
	पूर्णांक dpms;
पूर्ण;

काष्ठा shmob_drm_connector अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder *encoder;

	काष्ठा backlight_device *backlight;
पूर्ण;

पूर्णांक shmob_drm_crtc_create(काष्ठा shmob_drm_device *sdev);
व्योम shmob_drm_crtc_finish_page_flip(काष्ठा shmob_drm_crtc *scrtc);
व्योम shmob_drm_crtc_suspend(काष्ठा shmob_drm_crtc *scrtc);
व्योम shmob_drm_crtc_resume(काष्ठा shmob_drm_crtc *scrtc);

पूर्णांक shmob_drm_encoder_create(काष्ठा shmob_drm_device *sdev);
पूर्णांक shmob_drm_connector_create(काष्ठा shmob_drm_device *sdev,
			       काष्ठा drm_encoder *encoder);

#पूर्ण_अगर /* __SHMOB_DRM_CRTC_H__ */
