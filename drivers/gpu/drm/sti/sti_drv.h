<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_DRV_H_
#घोषणा _STI_DRV_H_

#समावेश <linux/platक्रमm_device.h>

काष्ठा drm_device;
काष्ठा drm_property;
काष्ठा sti_compositor;

/**
 * STI drm निजी काष्ठाure
 * This काष्ठाure is stored as निजी in the drm_device
 *
 * @compo:                 compositor
 * @plane_zorder_property: z-order property क्रम CRTC planes
 * @drm_dev:               drm device
 */
काष्ठा sti_निजी अणु
	काष्ठा sti_compositor *compo;
	काष्ठा drm_property *plane_zorder_property;
	काष्ठा drm_device *drm_dev;
पूर्ण;

बाह्य काष्ठा platक्रमm_driver sti_tvout_driver;
बाह्य काष्ठा platक्रमm_driver sti_hqvdp_driver;
बाह्य काष्ठा platक्रमm_driver sti_hdmi_driver;
बाह्य काष्ठा platक्रमm_driver sti_hda_driver;
बाह्य काष्ठा platक्रमm_driver sti_dvo_driver;
बाह्य काष्ठा platक्रमm_driver sti_vtg_driver;
बाह्य काष्ठा platक्रमm_driver sti_compositor_driver;

#पूर्ण_अगर
