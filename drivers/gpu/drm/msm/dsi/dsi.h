<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DSI_CONNECTOR_H__
#घोषणा __DSI_CONNECTOR_H__

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

#समावेश "msm_drv.h"

#घोषणा DSI_0	0
#घोषणा DSI_1	1
#घोषणा DSI_MAX	2

काष्ठा msm_dsi_phy_shared_timings;
काष्ठा msm_dsi_phy_clk_request;

क्रमागत msm_dsi_phy_useहाल अणु
	MSM_DSI_PHY_STANDALONE,
	MSM_DSI_PHY_MASTER,
	MSM_DSI_PHY_SLAVE,
पूर्ण;

#घोषणा DSI_DEV_REGULATOR_MAX	8
#घोषणा DSI_BUS_CLK_MAX		4

/* Regulators क्रम DSI devices */
काष्ठा dsi_reg_entry अणु
	अक्षर name[32];
	पूर्णांक enable_load;
	पूर्णांक disable_load;
पूर्ण;

काष्ठा dsi_reg_config अणु
	पूर्णांक num;
	काष्ठा dsi_reg_entry regs[DSI_DEV_REGULATOR_MAX];
पूर्ण;

काष्ठा msm_dsi अणु
	काष्ठा drm_device *dev;
	काष्ठा platक्रमm_device *pdev;

	/* connector managed by us when we're connected to a drm_panel */
	काष्ठा drm_connector *connector;
	/* पूर्णांकernal dsi bridge attached to MDP पूर्णांकerface */
	काष्ठा drm_bridge *bridge;

	काष्ठा mipi_dsi_host *host;
	काष्ठा msm_dsi_phy *phy;

	/*
	 * panel/बाह्यal_bridge connected to dsi bridge output, only one of the
	 * two can be valid at a समय
	 */
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *बाह्यal_bridge;

	काष्ठा device *phy_dev;
	bool phy_enabled;

	/* the encoder we are hooked to (outside of dsi block) */
	काष्ठा drm_encoder *encoder;

	पूर्णांक id;
पूर्ण;

/* dsi manager */
काष्ठा drm_bridge *msm_dsi_manager_bridge_init(u8 id);
व्योम msm_dsi_manager_bridge_destroy(काष्ठा drm_bridge *bridge);
काष्ठा drm_connector *msm_dsi_manager_connector_init(u8 id);
काष्ठा drm_connector *msm_dsi_manager_ext_bridge_init(u8 id);
पूर्णांक msm_dsi_manager_cmd_xfer(पूर्णांक id, स्थिर काष्ठा mipi_dsi_msg *msg);
bool msm_dsi_manager_cmd_xfer_trigger(पूर्णांक id, u32 dma_base, u32 len);
व्योम msm_dsi_manager_setup_encoder(पूर्णांक id);
पूर्णांक msm_dsi_manager_रेजिस्टर(काष्ठा msm_dsi *msm_dsi);
व्योम msm_dsi_manager_unरेजिस्टर(काष्ठा msm_dsi *msm_dsi);
bool msm_dsi_manager_validate_current_config(u8 id);

/* msm dsi */
अटल अंतरभूत bool msm_dsi_device_connected(काष्ठा msm_dsi *msm_dsi)
अणु
	वापस msm_dsi->panel || msm_dsi->बाह्यal_bridge;
पूर्ण

काष्ठा drm_encoder *msm_dsi_get_encoder(काष्ठा msm_dsi *msm_dsi);

/* dsi host */
काष्ठा msm_dsi_host;
पूर्णांक msm_dsi_host_xfer_prepare(काष्ठा mipi_dsi_host *host,
					स्थिर काष्ठा mipi_dsi_msg *msg);
व्योम msm_dsi_host_xfer_restore(काष्ठा mipi_dsi_host *host,
					स्थिर काष्ठा mipi_dsi_msg *msg);
पूर्णांक msm_dsi_host_cmd_tx(काष्ठा mipi_dsi_host *host,
					स्थिर काष्ठा mipi_dsi_msg *msg);
पूर्णांक msm_dsi_host_cmd_rx(काष्ठा mipi_dsi_host *host,
					स्थिर काष्ठा mipi_dsi_msg *msg);
व्योम msm_dsi_host_cmd_xfer_commit(काष्ठा mipi_dsi_host *host,
					u32 dma_base, u32 len);
पूर्णांक msm_dsi_host_enable(काष्ठा mipi_dsi_host *host);
पूर्णांक msm_dsi_host_disable(काष्ठा mipi_dsi_host *host);
पूर्णांक msm_dsi_host_घातer_on(काष्ठा mipi_dsi_host *host,
			काष्ठा msm_dsi_phy_shared_timings *phy_shared_timings,
			bool is_dual_dsi);
पूर्णांक msm_dsi_host_घातer_off(काष्ठा mipi_dsi_host *host);
पूर्णांक msm_dsi_host_set_display_mode(काष्ठा mipi_dsi_host *host,
				  स्थिर काष्ठा drm_display_mode *mode);
काष्ठा drm_panel *msm_dsi_host_get_panel(काष्ठा mipi_dsi_host *host);
अचिन्हित दीर्घ msm_dsi_host_get_mode_flags(काष्ठा mipi_dsi_host *host);
काष्ठा drm_bridge *msm_dsi_host_get_bridge(काष्ठा mipi_dsi_host *host);
पूर्णांक msm_dsi_host_रेजिस्टर(काष्ठा mipi_dsi_host *host, bool check_defer);
व्योम msm_dsi_host_unरेजिस्टर(काष्ठा mipi_dsi_host *host);
पूर्णांक msm_dsi_host_set_src_pll(काष्ठा mipi_dsi_host *host,
			काष्ठा msm_dsi_phy *src_phy);
व्योम msm_dsi_host_reset_phy(काष्ठा mipi_dsi_host *host);
व्योम msm_dsi_host_get_phy_clk_req(काष्ठा mipi_dsi_host *host,
	काष्ठा msm_dsi_phy_clk_request *clk_req,
	bool is_dual_dsi);
व्योम msm_dsi_host_destroy(काष्ठा mipi_dsi_host *host);
पूर्णांक msm_dsi_host_modeset_init(काष्ठा mipi_dsi_host *host,
					काष्ठा drm_device *dev);
पूर्णांक msm_dsi_host_init(काष्ठा msm_dsi *msm_dsi);
पूर्णांक msm_dsi_runसमय_suspend(काष्ठा device *dev);
पूर्णांक msm_dsi_runसमय_resume(काष्ठा device *dev);
पूर्णांक dsi_link_clk_set_rate_6g(काष्ठा msm_dsi_host *msm_host);
पूर्णांक dsi_link_clk_set_rate_v2(काष्ठा msm_dsi_host *msm_host);
पूर्णांक dsi_link_clk_enable_6g(काष्ठा msm_dsi_host *msm_host);
पूर्णांक dsi_link_clk_enable_v2(काष्ठा msm_dsi_host *msm_host);
व्योम dsi_link_clk_disable_6g(काष्ठा msm_dsi_host *msm_host);
व्योम dsi_link_clk_disable_v2(काष्ठा msm_dsi_host *msm_host);
पूर्णांक dsi_tx_buf_alloc_6g(काष्ठा msm_dsi_host *msm_host, पूर्णांक size);
पूर्णांक dsi_tx_buf_alloc_v2(काष्ठा msm_dsi_host *msm_host, पूर्णांक size);
व्योम *dsi_tx_buf_get_6g(काष्ठा msm_dsi_host *msm_host);
व्योम *dsi_tx_buf_get_v2(काष्ठा msm_dsi_host *msm_host);
व्योम dsi_tx_buf_put_6g(काष्ठा msm_dsi_host *msm_host);
पूर्णांक dsi_dma_base_get_6g(काष्ठा msm_dsi_host *msm_host, uपूर्णांक64_t *iova);
पूर्णांक dsi_dma_base_get_v2(काष्ठा msm_dsi_host *msm_host, uपूर्णांक64_t *iova);
पूर्णांक dsi_clk_init_v2(काष्ठा msm_dsi_host *msm_host);
पूर्णांक dsi_clk_init_6g_v2(काष्ठा msm_dsi_host *msm_host);
पूर्णांक dsi_calc_clk_rate_v2(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi);
पूर्णांक dsi_calc_clk_rate_6g(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi);

/* dsi phy */
काष्ठा msm_dsi_phy;
काष्ठा msm_dsi_phy_shared_timings अणु
	u32 clk_post;
	u32 clk_pre;
	bool clk_pre_inc_by_2;
पूर्ण;

काष्ठा msm_dsi_phy_clk_request अणु
	अचिन्हित दीर्घ bitclk_rate;
	अचिन्हित दीर्घ escclk_rate;
पूर्ण;

व्योम msm_dsi_phy_driver_रेजिस्टर(व्योम);
व्योम msm_dsi_phy_driver_unरेजिस्टर(व्योम);
पूर्णांक msm_dsi_phy_enable(काष्ठा msm_dsi_phy *phy,
			काष्ठा msm_dsi_phy_clk_request *clk_req);
व्योम msm_dsi_phy_disable(काष्ठा msm_dsi_phy *phy);
व्योम msm_dsi_phy_get_shared_timings(काष्ठा msm_dsi_phy *phy,
			काष्ठा msm_dsi_phy_shared_timings *shared_timing);
व्योम msm_dsi_phy_set_useहाल(काष्ठा msm_dsi_phy *phy,
			     क्रमागत msm_dsi_phy_useहाल uc);
पूर्णांक msm_dsi_phy_get_clk_provider(काष्ठा msm_dsi_phy *phy,
	काष्ठा clk **byte_clk_provider, काष्ठा clk **pixel_clk_provider);
व्योम msm_dsi_phy_pll_save_state(काष्ठा msm_dsi_phy *phy);
पूर्णांक msm_dsi_phy_pll_restore_state(काष्ठा msm_dsi_phy *phy);

#पूर्ण_अगर /* __DSI_CONNECTOR_H__ */

