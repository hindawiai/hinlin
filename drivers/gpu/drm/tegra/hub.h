<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित TEGRA_HUB_H
#घोषणा TEGRA_HUB_H 1

#समावेश <drm/drm_plane.h>

#समावेश "plane.h"

काष्ठा tegra_dc;

काष्ठा tegra_winकरोwgroup अणु
	अचिन्हित पूर्णांक usecount;
	काष्ठा mutex lock;

	अचिन्हित पूर्णांक index;
	काष्ठा host1x_client *parent;
	काष्ठा reset_control *rst;
पूर्ण;

काष्ठा tegra_shared_plane अणु
	काष्ठा tegra_plane base;
	काष्ठा tegra_winकरोwgroup *wgrp;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_shared_plane *
to_tegra_shared_plane(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा tegra_shared_plane, base.base);
पूर्ण

काष्ठा tegra_display_hub_soc अणु
	अचिन्हित पूर्णांक num_wgrps;
	bool supports_dsc;
पूर्ण;

काष्ठा tegra_display_hub अणु
	काष्ठा drm_निजी_obj base;
	काष्ठा host1x_client client;
	काष्ठा clk *clk_disp;
	काष्ठा clk *clk_dsc;
	काष्ठा clk *clk_hub;
	काष्ठा reset_control *rst;

	अचिन्हित पूर्णांक num_heads;
	काष्ठा clk **clk_heads;

	स्थिर काष्ठा tegra_display_hub_soc *soc;
	काष्ठा tegra_winकरोwgroup *wgrps;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_display_hub *
to_tegra_display_hub(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_display_hub, client);
पूर्ण

काष्ठा tegra_display_hub_state अणु
	काष्ठा drm_निजी_state base;

	काष्ठा tegra_dc *dc;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_display_hub_state *
to_tegra_display_hub_state(काष्ठा drm_निजी_state *priv)
अणु
	वापस container_of(priv, काष्ठा tegra_display_hub_state, base);
पूर्ण

काष्ठा tegra_dc;
काष्ठा tegra_plane;

पूर्णांक tegra_display_hub_prepare(काष्ठा tegra_display_hub *hub);
व्योम tegra_display_hub_cleanup(काष्ठा tegra_display_hub *hub);

काष्ठा drm_plane *tegra_shared_plane_create(काष्ठा drm_device *drm,
					    काष्ठा tegra_dc *dc,
					    अचिन्हित पूर्णांक wgrp,
					    अचिन्हित पूर्णांक index);

पूर्णांक tegra_display_hub_atomic_check(काष्ठा drm_device *drm,
				   काष्ठा drm_atomic_state *state);
व्योम tegra_display_hub_atomic_commit(काष्ठा drm_device *drm,
				     काष्ठा drm_atomic_state *state);

#घोषणा DC_CMD_IHUB_COMMON_MISC_CTL 0x068
#घोषणा  LATENCY_EVENT (1 << 3)

#घोषणा DC_DISP_IHUB_COMMON_DISPLAY_FETCH_METER 0x451
#घोषणा  CURS_SLOTS(x) (((x) & 0xff) << 8)
#घोषणा  WGRP_SLOTS(x) (((x) & 0xff) << 0)

#पूर्ण_अगर /* TEGRA_HUB_H */
