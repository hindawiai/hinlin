<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
 */

#अगर_अघोषित __DW_MIPI_DSI__
#घोषणा __DW_MIPI_DSI__

#समावेश <linux/types.h>

#समावेश <drm/drm_modes.h>

काष्ठा drm_display_mode;
काष्ठा drm_encoder;
काष्ठा dw_mipi_dsi;
काष्ठा mipi_dsi_device;
काष्ठा platक्रमm_device;

काष्ठा dw_mipi_dsi_dphy_timing अणु
	u16 data_hs2lp;
	u16 data_lp2hs;
	u16 clk_hs2lp;
	u16 clk_lp2hs;
पूर्ण;

काष्ठा dw_mipi_dsi_phy_ops अणु
	पूर्णांक (*init)(व्योम *priv_data);
	व्योम (*घातer_on)(व्योम *priv_data);
	व्योम (*घातer_off)(व्योम *priv_data);
	पूर्णांक (*get_lane_mbps)(व्योम *priv_data,
			     स्थिर काष्ठा drm_display_mode *mode,
			     अचिन्हित दीर्घ mode_flags, u32 lanes, u32 क्रमmat,
			     अचिन्हित पूर्णांक *lane_mbps);
	पूर्णांक (*get_timing)(व्योम *priv_data, अचिन्हित पूर्णांक lane_mbps,
			  काष्ठा dw_mipi_dsi_dphy_timing *timing);
	पूर्णांक (*get_esc_clk_rate)(व्योम *priv_data, अचिन्हित पूर्णांक *esc_clk_rate);
पूर्ण;

काष्ठा dw_mipi_dsi_host_ops अणु
	पूर्णांक (*attach)(व्योम *priv_data,
		      काष्ठा mipi_dsi_device *dsi);
	पूर्णांक (*detach)(व्योम *priv_data,
		      काष्ठा mipi_dsi_device *dsi);
पूर्ण;

काष्ठा dw_mipi_dsi_plat_data अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक max_data_lanes;

	क्रमागत drm_mode_status (*mode_valid)(व्योम *priv_data,
					   स्थिर काष्ठा drm_display_mode *mode);

	स्थिर काष्ठा dw_mipi_dsi_phy_ops *phy_ops;
	स्थिर काष्ठा dw_mipi_dsi_host_ops *host_ops;

	व्योम *priv_data;
पूर्ण;

काष्ठा dw_mipi_dsi *dw_mipi_dsi_probe(काष्ठा platक्रमm_device *pdev,
				      स्थिर काष्ठा dw_mipi_dsi_plat_data
				      *plat_data);
व्योम dw_mipi_dsi_हटाओ(काष्ठा dw_mipi_dsi *dsi);
पूर्णांक dw_mipi_dsi_bind(काष्ठा dw_mipi_dsi *dsi, काष्ठा drm_encoder *encoder);
व्योम dw_mipi_dsi_unbind(काष्ठा dw_mipi_dsi *dsi);
व्योम dw_mipi_dsi_set_slave(काष्ठा dw_mipi_dsi *dsi, काष्ठा dw_mipi_dsi *slave);

#पूर्ण_अगर /* __DW_MIPI_DSI__ */
