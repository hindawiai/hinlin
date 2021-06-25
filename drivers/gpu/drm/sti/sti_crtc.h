<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_CRTC_H_
#घोषणा _STI_CRTC_H_

काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा drm_plane;
काष्ठा notअगरier_block;
काष्ठा sti_mixer;

पूर्णांक sti_crtc_init(काष्ठा drm_device *drm_dev, काष्ठा sti_mixer *mixer,
		  काष्ठा drm_plane *primary, काष्ठा drm_plane *cursor);
पूर्णांक sti_crtc_vblank_cb(काष्ठा notअगरier_block *nb,
		       अचिन्हित दीर्घ event, व्योम *data);
bool sti_crtc_is_मुख्य(काष्ठा drm_crtc *drm_crtc);

#पूर्ण_अगर
