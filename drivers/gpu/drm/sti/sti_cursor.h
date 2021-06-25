<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2013
 * Authors: Vincent Abriou <vincent.abriou@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_CURSOR_H_
#घोषणा _STI_CURSOR_H_

काष्ठा drm_device;
काष्ठा device;

काष्ठा drm_plane *sti_cursor_create(काष्ठा drm_device *drm_dev,
				    काष्ठा device *dev, पूर्णांक desc,
				    व्योम __iomem *baseaddr,
				    अचिन्हित पूर्णांक possible_crtcs);

#पूर्ण_अगर
