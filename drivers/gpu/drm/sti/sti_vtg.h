<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_VTG_H_
#घोषणा _STI_VTG_H_

#घोषणा VTG_TOP_FIELD_EVENT     1
#घोषणा VTG_BOTTOM_FIELD_EVENT  2

#घोषणा VTG_SYNC_ID_HDMI        1
#घोषणा VTG_SYNC_ID_HDDCS       2
#घोषणा VTG_SYNC_ID_HDF         3
#घोषणा VTG_SYNC_ID_DVO         4

काष्ठा sti_vtg;
काष्ठा drm_crtc;
काष्ठा drm_display_mode;
काष्ठा notअगरier_block;

काष्ठा sti_vtg *of_vtg_find(काष्ठा device_node *np);
व्योम sti_vtg_set_config(काष्ठा sti_vtg *vtg,
		स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक sti_vtg_रेजिस्टर_client(काष्ठा sti_vtg *vtg, काष्ठा notअगरier_block *nb,
			    काष्ठा drm_crtc *crtc);
पूर्णांक sti_vtg_unरेजिस्टर_client(काष्ठा sti_vtg *vtg,
		काष्ठा notअगरier_block *nb);

u32 sti_vtg_get_line_number(काष्ठा drm_display_mode mode, पूर्णांक y);
u32 sti_vtg_get_pixel_number(काष्ठा drm_display_mode mode, पूर्णांक x);

#पूर्ण_अगर
