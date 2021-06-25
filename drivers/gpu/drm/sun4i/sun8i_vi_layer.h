<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) Jernej Skrabec <jernej.skrabec@siol.net>
 */

#अगर_अघोषित _SUN8I_VI_LAYER_H_
#घोषणा _SUN8I_VI_LAYER_H_

#समावेश <drm/drm_plane.h>

#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_ATTR(base, layer) \
		((base) + 0x30 * (layer) + 0x0)
#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_SIZE(base, layer) \
		((base) + 0x30 * (layer) + 0x4)
#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_COORD(base, layer) \
		((base) + 0x30 * (layer) + 0x8)
#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_PITCH(base, layer, plane) \
		((base) + 0x30 * (layer) + 0xc + 4 * (plane))
#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_TOP_LADDR(base, layer, plane) \
		((base) + 0x30 * (layer) + 0x18 + 4 * (plane))
#घोषणा SUN8I_MIXER_CHAN_VI_OVL_SIZE(base) \
		((base) + 0xe8)
#घोषणा SUN8I_MIXER_CHAN_VI_HDS_Y(base) \
		((base) + 0xf0)
#घोषणा SUN8I_MIXER_CHAN_VI_HDS_UV(base) \
		((base) + 0xf4)
#घोषणा SUN8I_MIXER_CHAN_VI_VDS_Y(base) \
		((base) + 0xf8)
#घोषणा SUN8I_MIXER_CHAN_VI_VDS_UV(base) \
		((base) + 0xfc)

#घोषणा SUN8I_MIXER_FCC_GLOBAL_ALPHA_REG \
		(0xAA000 + 0x90)

#घोषणा SUN8I_MIXER_FCC_GLOBAL_ALPHA(x)			((x) << 24)
#घोषणा SUN8I_MIXER_FCC_GLOBAL_ALPHA_MASK		GENMASK(31, 24)

#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_ATTR_EN		BIT(0)
/* RGB mode should be set क्रम RGB क्रमmats and cleared क्रम YCbCr */
#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_ATTR_RGB_MODE		BIT(15)
#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_OFFSET	8
#घोषणा SUN8I_MIXER_CHAN_VI_LAYER_ATTR_FBFMT_MASK	GENMASK(12, 8)
#घोषणा SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MODE_MASK	GENMASK(2, 1)
#घोषणा SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MASK	GENMASK(31, 24)
#घोषणा SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA(x)	((x) << 24)

#घोषणा SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MODE_PIXEL	((0) << 1)
#घोषणा SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MODE_LAYER	((1) << 1)
#घोषणा SUN50I_MIXER_CHAN_VI_LAYER_ATTR_ALPHA_MODE_COMBINED	((2) << 1)

#घोषणा SUN8I_MIXER_CHAN_VI_DS_N(x)			((x) << 16)
#घोषणा SUN8I_MIXER_CHAN_VI_DS_M(x)			((x) << 0)

काष्ठा sun8i_mixer;

काष्ठा sun8i_vi_layer अणु
	काष्ठा drm_plane	plane;
	काष्ठा sun8i_mixer	*mixer;
	पूर्णांक			channel;
	पूर्णांक			overlay;
पूर्ण;

अटल अंतरभूत काष्ठा sun8i_vi_layer *
plane_to_sun8i_vi_layer(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा sun8i_vi_layer, plane);
पूर्ण

काष्ठा sun8i_vi_layer *sun8i_vi_layer_init_one(काष्ठा drm_device *drm,
					       काष्ठा sun8i_mixer *mixer,
					       पूर्णांक index);
#पूर्ण_अगर /* _SUN8I_VI_LAYER_H_ */
