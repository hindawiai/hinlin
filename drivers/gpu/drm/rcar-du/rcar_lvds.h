<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rcar_lvds.h  --  R-Car LVDS Encoder
 *
 * Copyright (C) 2013-2018 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_LVDS_H__
#घोषणा __RCAR_LVDS_H__

काष्ठा drm_bridge;

#अगर IS_ENABLED(CONFIG_DRM_RCAR_LVDS)
पूर्णांक rcar_lvds_clk_enable(काष्ठा drm_bridge *bridge, अचिन्हित दीर्घ freq);
व्योम rcar_lvds_clk_disable(काष्ठा drm_bridge *bridge);
bool rcar_lvds_dual_link(काष्ठा drm_bridge *bridge);
#अन्यथा
अटल अंतरभूत पूर्णांक rcar_lvds_clk_enable(काष्ठा drm_bridge *bridge,
				       अचिन्हित दीर्घ freq)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम rcar_lvds_clk_disable(काष्ठा drm_bridge *bridge) अणु पूर्ण
अटल अंतरभूत bool rcar_lvds_dual_link(काष्ठा drm_bridge *bridge)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_DRM_RCAR_LVDS */

#पूर्ण_अगर /* __RCAR_LVDS_H__ */
