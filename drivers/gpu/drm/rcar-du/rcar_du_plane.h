<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_plane.h  --  R-Car Display Unit Planes
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_PLANE_H__
#घोषणा __RCAR_DU_PLANE_H__

#समावेश <drm/drm_plane.h>

काष्ठा rcar_du_क्रमmat_info;
काष्ठा rcar_du_group;

/*
 * The RCAR DU has 8 hardware planes, shared between primary and overlay planes.
 * As using overlay planes requires at least one of the CRTCs being enabled, no
 * more than 7 overlay planes can be available. We thus create 1 primary plane
 * per CRTC and 7 overlay planes, क्रम a total of up to 9 KMS planes.
 */
#घोषणा RCAR_DU_NUM_KMS_PLANES		9
#घोषणा RCAR_DU_NUM_HW_PLANES		8

क्रमागत rcar_du_plane_source अणु
	RCAR_DU_PLANE_MEMORY,
	RCAR_DU_PLANE_VSPD0,
	RCAR_DU_PLANE_VSPD1,
पूर्ण;

काष्ठा rcar_du_plane अणु
	काष्ठा drm_plane plane;
	काष्ठा rcar_du_group *group;
पूर्ण;

अटल अंतरभूत काष्ठा rcar_du_plane *to_rcar_plane(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा rcar_du_plane, plane);
पूर्ण

/**
 * काष्ठा rcar_du_plane_state - Driver-specअगरic plane state
 * @state: base DRM plane state
 * @क्रमmat: inक्रमmation about the pixel क्रमmat used by the plane
 * @hwindex: 0-based hardware plane index, -1 means unused
 * @colorkey: value of the plane colorkey property
 */
काष्ठा rcar_du_plane_state अणु
	काष्ठा drm_plane_state state;

	स्थिर काष्ठा rcar_du_क्रमmat_info *क्रमmat;
	पूर्णांक hwindex;
	क्रमागत rcar_du_plane_source source;

	अचिन्हित पूर्णांक colorkey;
पूर्ण;

अटल अंतरभूत काष्ठा rcar_du_plane_state *
to_rcar_plane_state(काष्ठा drm_plane_state *state)
अणु
	वापस container_of(state, काष्ठा rcar_du_plane_state, state);
पूर्ण

पूर्णांक rcar_du_atomic_check_planes(काष्ठा drm_device *dev,
				काष्ठा drm_atomic_state *state);

पूर्णांक __rcar_du_plane_atomic_check(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *state,
				 स्थिर काष्ठा rcar_du_क्रमmat_info **क्रमmat);

पूर्णांक rcar_du_planes_init(काष्ठा rcar_du_group *rgrp);

व्योम __rcar_du_plane_setup(काष्ठा rcar_du_group *rgrp,
			   स्थिर काष्ठा rcar_du_plane_state *state);

अटल अंतरभूत व्योम rcar_du_plane_setup(काष्ठा rcar_du_plane *plane)
अणु
	काष्ठा rcar_du_plane_state *state =
		to_rcar_plane_state(plane->plane.state);

	वापस __rcar_du_plane_setup(plane->group, state);
पूर्ण

#पूर्ण_अगर /* __RCAR_DU_PLANE_H__ */
