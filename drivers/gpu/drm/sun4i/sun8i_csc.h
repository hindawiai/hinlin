<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) Jernej Skrabec <jernej.skrabec@siol.net>
 */

#अगर_अघोषित _SUN8I_CSC_H_
#घोषणा _SUN8I_CSC_H_

#समावेश <drm/drm_color_mgmt.h>

काष्ठा sun8i_mixer;

/* VI channel CSC units offsets */
#घोषणा CCSC00_OFFSET 0xAA050
#घोषणा CCSC01_OFFSET 0xFA050
#घोषणा CCSC10_OFFSET 0xA0000
#घोषणा CCSC11_OFFSET 0xF0000

#घोषणा SUN8I_CSC_CTRL(base)		(base + 0x0)
#घोषणा SUN8I_CSC_COEFF(base, i)	(base + 0x10 + 4 * i)

#घोषणा SUN8I_CSC_CTRL_EN		BIT(0)

क्रमागत sun8i_csc_mode अणु
	SUN8I_CSC_MODE_OFF,
	SUN8I_CSC_MODE_YUV2RGB,
	SUN8I_CSC_MODE_YVU2RGB,
पूर्ण;

व्योम sun8i_csc_set_ccsc_coefficients(काष्ठा sun8i_mixer *mixer, पूर्णांक layer,
				     क्रमागत sun8i_csc_mode mode,
				     क्रमागत drm_color_encoding encoding,
				     क्रमागत drm_color_range range);
व्योम sun8i_csc_enable_ccsc(काष्ठा sun8i_mixer *mixer, पूर्णांक layer, bool enable);

#पूर्ण_अगर
