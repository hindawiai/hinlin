<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on sun4i_layer.h, which is:
 *   Copyright (C) 2015 Free Electrons
 *   Copyright (C) 2015 NextThing Co
 *
 *   Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _SUN8I_UI_LAYER_H_
#घोषणा _SUN8I_UI_LAYER_H_

#समावेश <drm/drm_plane.h>

#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR(base, layer) \
			((base) + 0x20 * (layer) + 0x0)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_SIZE(base, layer) \
			((base) + 0x20 * (layer) + 0x4)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_COORD(base, layer) \
			((base) + 0x20 * (layer) + 0x8)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_PITCH(base, layer) \
			((base) + 0x20 * (layer) + 0xc)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_TOP_LADDR(base, layer) \
			((base) + 0x20 * (layer) + 0x10)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_BOT_LADDR(base, layer) \
			((base) + 0x20 * (layer) + 0x14)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_FCOLOR(base, layer) \
			((base) + 0x20 * (layer) + 0x18)
#घोषणा SUN8I_MIXER_CHAN_UI_TOP_HADDR(base) \
			((base) + 0x80)
#घोषणा SUN8I_MIXER_CHAN_UI_BOT_HADDR(base) \
			((base) + 0x84)
#घोषणा SUN8I_MIXER_CHAN_UI_OVL_SIZE(base) \
			((base) + 0x88)

#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_EN		BIT(0)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MODE_MASK	GENMASK(2, 1)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_FBFMT_MASK	GENMASK(12, 8)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_FBFMT_OFFSET	8
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MASK	GENMASK(31, 24)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA(x)		((x) << 24)

#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MODE_PIXEL		((0) << 1)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MODE_LAYER		((1) << 1)
#घोषणा SUN8I_MIXER_CHAN_UI_LAYER_ATTR_ALPHA_MODE_COMBINED	((2) << 1)

काष्ठा sun8i_mixer;

काष्ठा sun8i_ui_layer अणु
	काष्ठा drm_plane	plane;
	काष्ठा sun8i_mixer	*mixer;
	पूर्णांक			channel;
	पूर्णांक			overlay;
पूर्ण;

अटल अंतरभूत काष्ठा sun8i_ui_layer *
plane_to_sun8i_ui_layer(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा sun8i_ui_layer, plane);
पूर्ण

काष्ठा sun8i_ui_layer *sun8i_ui_layer_init_one(काष्ठा drm_device *drm,
					       काष्ठा sun8i_mixer *mixer,
					       पूर्णांक index);
#पूर्ण_अगर /* _SUN8I_UI_LAYER_H_ */
