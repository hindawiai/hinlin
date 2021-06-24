<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_GDP_H_
#घोषणा _STI_GDP_H_

#समावेश <linux/types.h>

#समावेश <drm/drm_plane.h>

काष्ठा drm_device;
काष्ठा device;

काष्ठा drm_plane *sti_gdp_create(काष्ठा drm_device *drm_dev,
				 काष्ठा device *dev, पूर्णांक desc,
				 व्योम __iomem *baseaddr,
				 अचिन्हित पूर्णांक possible_crtcs,
				 क्रमागत drm_plane_type type);
#पूर्ण_अगर
