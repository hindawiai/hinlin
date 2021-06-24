<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _SUN4I_LAYER_H_
#घोषणा _SUN4I_LAYER_H_

काष्ठा sunxi_engine;

काष्ठा sun4i_layer अणु
	काष्ठा drm_plane	plane;
	काष्ठा sun4i_drv	*drv;
	काष्ठा sun4i_backend	*backend;
	पूर्णांक			id;
पूर्ण;

काष्ठा sun4i_layer_state अणु
	काष्ठा drm_plane_state	state;
	अचिन्हित पूर्णांक		pipe;
	bool			uses_frontend;
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_layer *
plane_to_sun4i_layer(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा sun4i_layer, plane);
पूर्ण

अटल अंतरभूत काष्ठा sun4i_layer_state *
state_to_sun4i_layer_state(काष्ठा drm_plane_state *state)
अणु
	वापस container_of(state, काष्ठा sun4i_layer_state, state);
पूर्ण

काष्ठा drm_plane **sun4i_layers_init(काष्ठा drm_device *drm,
				     काष्ठा sunxi_engine *engine);

#पूर्ण_अगर /* _SUN4I_LAYER_H_ */
