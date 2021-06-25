<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित TEGRA_PLANE_H
#घोषणा TEGRA_PLANE_H 1

#समावेश <drm/drm_plane.h>

काष्ठा tegra_bo;
काष्ठा tegra_dc;

काष्ठा tegra_plane अणु
	काष्ठा drm_plane base;
	काष्ठा tegra_dc *dc;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक index;
पूर्ण;

काष्ठा tegra_cursor अणु
	काष्ठा tegra_plane base;

	काष्ठा tegra_bo *bo;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_plane *to_tegra_plane(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा tegra_plane, base);
पूर्ण

काष्ठा tegra_plane_legacy_blending_state अणु
	bool alpha;
	bool top;
पूर्ण;

काष्ठा tegra_plane_state अणु
	काष्ठा drm_plane_state base;

	काष्ठा sg_table *sgt[3];
	dma_addr_t iova[3];

	काष्ठा tegra_bo_tiling tiling;
	u32 क्रमmat;
	u32 swap;

	bool reflect_x;
	bool reflect_y;

	/* used क्रम legacy blending support only */
	काष्ठा tegra_plane_legacy_blending_state blending[2];
	bool opaque;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_plane_state *
to_tegra_plane_state(काष्ठा drm_plane_state *state)
अणु
	अगर (state)
		वापस container_of(state, काष्ठा tegra_plane_state, base);

	वापस शून्य;
पूर्ण

बाह्य स्थिर काष्ठा drm_plane_funcs tegra_plane_funcs;

पूर्णांक tegra_plane_prepare_fb(काष्ठा drm_plane *plane,
			   काष्ठा drm_plane_state *state);
व्योम tegra_plane_cleanup_fb(काष्ठा drm_plane *plane,
			    काष्ठा drm_plane_state *state);

पूर्णांक tegra_plane_state_add(काष्ठा tegra_plane *plane,
			  काष्ठा drm_plane_state *state);

पूर्णांक tegra_plane_क्रमmat(u32 fourcc, u32 *क्रमmat, u32 *swap);
bool tegra_plane_क्रमmat_is_yuv(अचिन्हित पूर्णांक क्रमmat, bool *planar);
पूर्णांक tegra_plane_setup_legacy_state(काष्ठा tegra_plane *tegra,
				   काष्ठा tegra_plane_state *state);

#पूर्ण_अगर /* TEGRA_PLANE_H */
