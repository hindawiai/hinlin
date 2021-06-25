<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश "msm_kms.h"
#समावेश "dsi.h"

#घोषणा DSI_CLOCK_MASTER	DSI_0
#घोषणा DSI_CLOCK_SLAVE		DSI_1

#घोषणा DSI_LEFT		DSI_0
#घोषणा DSI_RIGHT		DSI_1

/* According to the current drm framework sequence, take the encoder of
 * DSI_1 as master encoder
 */
#घोषणा DSI_ENCODER_MASTER	DSI_1
#घोषणा DSI_ENCODER_SLAVE	DSI_0

काष्ठा msm_dsi_manager अणु
	काष्ठा msm_dsi *dsi[DSI_MAX];

	bool is_dual_dsi;
	bool is_sync_needed;
	पूर्णांक master_dsi_link_id;
पूर्ण;

अटल काष्ठा msm_dsi_manager msm_dsim_glb;

#घोषणा IS_DUAL_DSI()		(msm_dsim_glb.is_dual_dsi)
#घोषणा IS_SYNC_NEEDED()	(msm_dsim_glb.is_sync_needed)
#घोषणा IS_MASTER_DSI_LINK(id)	(msm_dsim_glb.master_dsi_link_id == id)

अटल अंतरभूत काष्ठा msm_dsi *dsi_mgr_get_dsi(पूर्णांक id)
अणु
	वापस msm_dsim_glb.dsi[id];
पूर्ण

अटल अंतरभूत काष्ठा msm_dsi *dsi_mgr_get_other_dsi(पूर्णांक id)
अणु
	वापस msm_dsim_glb.dsi[(id + 1) % DSI_MAX];
पूर्ण

अटल पूर्णांक dsi_mgr_parse_dual_dsi(काष्ठा device_node *np, पूर्णांक id)
अणु
	काष्ठा msm_dsi_manager *msm_dsim = &msm_dsim_glb;

	/* We assume 2 dsi nodes have the same inक्रमmation of dual-dsi and
	 * sync-mode, and only one node specअगरies master in हाल of dual mode.
	 */
	अगर (!msm_dsim->is_dual_dsi)
		msm_dsim->is_dual_dsi = of_property_पढ़ो_bool(
						np, "qcom,dual-dsi-mode");

	अगर (msm_dsim->is_dual_dsi) अणु
		अगर (of_property_पढ़ो_bool(np, "qcom,master-dsi"))
			msm_dsim->master_dsi_link_id = id;
		अगर (!msm_dsim->is_sync_needed)
			msm_dsim->is_sync_needed = of_property_पढ़ो_bool(
					np, "qcom,sync-dual-dsi");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_mgr_setup_components(पूर्णांक id)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *other_dsi = dsi_mgr_get_other_dsi(id);
	काष्ठा msm_dsi *clk_master_dsi = dsi_mgr_get_dsi(DSI_CLOCK_MASTER);
	काष्ठा msm_dsi *clk_slave_dsi = dsi_mgr_get_dsi(DSI_CLOCK_SLAVE);
	पूर्णांक ret;

	अगर (!IS_DUAL_DSI()) अणु
		ret = msm_dsi_host_रेजिस्टर(msm_dsi->host, true);
		अगर (ret)
			वापस ret;

		msm_dsi_phy_set_useहाल(msm_dsi->phy, MSM_DSI_PHY_STANDALONE);
		ret = msm_dsi_host_set_src_pll(msm_dsi->host, msm_dsi->phy);
	पूर्ण अन्यथा अगर (!other_dsi) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		काष्ठा msm_dsi *master_link_dsi = IS_MASTER_DSI_LINK(id) ?
							msm_dsi : other_dsi;
		काष्ठा msm_dsi *slave_link_dsi = IS_MASTER_DSI_LINK(id) ?
							other_dsi : msm_dsi;
		/* Register slave host first, so that slave DSI device
		 * has a chance to probe, and करो not block the master
		 * DSI device's probe.
		 * Also, करो not check defer क्रम the slave host,
		 * because only master DSI device adds the panel to global
		 * panel list. The panel's device is the master DSI device.
		 */
		ret = msm_dsi_host_रेजिस्टर(slave_link_dsi->host, false);
		अगर (ret)
			वापस ret;
		ret = msm_dsi_host_रेजिस्टर(master_link_dsi->host, true);
		अगर (ret)
			वापस ret;

		/* PLL0 is to drive both 2 DSI link घड़ीs in Dual DSI mode. */
		msm_dsi_phy_set_useहाल(clk_master_dsi->phy,
					MSM_DSI_PHY_MASTER);
		msm_dsi_phy_set_useहाल(clk_slave_dsi->phy,
					MSM_DSI_PHY_SLAVE);
		ret = msm_dsi_host_set_src_pll(msm_dsi->host, clk_master_dsi->phy);
		अगर (ret)
			वापस ret;
		ret = msm_dsi_host_set_src_pll(other_dsi->host, clk_master_dsi->phy);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक enable_phy(काष्ठा msm_dsi *msm_dsi,
		      काष्ठा msm_dsi_phy_shared_timings *shared_timings)
अणु
	काष्ठा msm_dsi_phy_clk_request clk_req;
	पूर्णांक ret;
	bool is_dual_dsi = IS_DUAL_DSI();

	msm_dsi_host_get_phy_clk_req(msm_dsi->host, &clk_req, is_dual_dsi);

	ret = msm_dsi_phy_enable(msm_dsi->phy, &clk_req);
	msm_dsi_phy_get_shared_timings(msm_dsi->phy, shared_timings);

	वापस ret;
पूर्ण

अटल पूर्णांक
dsi_mgr_phy_enable(पूर्णांक id,
		   काष्ठा msm_dsi_phy_shared_timings shared_timings[DSI_MAX])
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *mdsi = dsi_mgr_get_dsi(DSI_CLOCK_MASTER);
	काष्ठा msm_dsi *sdsi = dsi_mgr_get_dsi(DSI_CLOCK_SLAVE);
	पूर्णांक ret;

	/* In हाल of dual DSI, some रेजिस्टरs in PHY1 have been programmed
	 * during PLL0 घड़ी's set_rate. The PHY1 reset called by host1 here
	 * will silently reset those PHY1 रेजिस्टरs. Thereक्रमe we need to reset
	 * and enable both PHYs beक्रमe any PLL घड़ी operation.
	 */
	अगर (IS_DUAL_DSI() && mdsi && sdsi) अणु
		अगर (!mdsi->phy_enabled && !sdsi->phy_enabled) अणु
			msm_dsi_host_reset_phy(mdsi->host);
			msm_dsi_host_reset_phy(sdsi->host);

			ret = enable_phy(mdsi,
					 &shared_timings[DSI_CLOCK_MASTER]);
			अगर (ret)
				वापस ret;
			ret = enable_phy(sdsi,
					 &shared_timings[DSI_CLOCK_SLAVE]);
			अगर (ret) अणु
				msm_dsi_phy_disable(mdsi->phy);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		msm_dsi_host_reset_phy(msm_dsi->host);
		ret = enable_phy(msm_dsi, &shared_timings[id]);
		अगर (ret)
			वापस ret;
	पूर्ण

	msm_dsi->phy_enabled = true;

	वापस 0;
पूर्ण

अटल व्योम dsi_mgr_phy_disable(पूर्णांक id)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *mdsi = dsi_mgr_get_dsi(DSI_CLOCK_MASTER);
	काष्ठा msm_dsi *sdsi = dsi_mgr_get_dsi(DSI_CLOCK_SLAVE);

	/* disable DSI phy
	 * In dual-dsi configuration, the phy should be disabled क्रम the
	 * first controller only when the second controller is disabled.
	 */
	msm_dsi->phy_enabled = false;
	अगर (IS_DUAL_DSI() && mdsi && sdsi) अणु
		अगर (!mdsi->phy_enabled && !sdsi->phy_enabled) अणु
			msm_dsi_phy_disable(sdsi->phy);
			msm_dsi_phy_disable(mdsi->phy);
		पूर्ण
	पूर्ण अन्यथा अणु
		msm_dsi_phy_disable(msm_dsi->phy);
	पूर्ण
पूर्ण

काष्ठा dsi_connector अणु
	काष्ठा drm_connector base;
	पूर्णांक id;
पूर्ण;

काष्ठा dsi_bridge अणु
	काष्ठा drm_bridge base;
	पूर्णांक id;
पूर्ण;

#घोषणा to_dsi_connector(x) container_of(x, काष्ठा dsi_connector, base)
#घोषणा to_dsi_bridge(x) container_of(x, काष्ठा dsi_bridge, base)

अटल अंतरभूत पूर्णांक dsi_mgr_connector_get_id(काष्ठा drm_connector *connector)
अणु
	काष्ठा dsi_connector *dsi_connector = to_dsi_connector(connector);
	वापस dsi_connector->id;
पूर्ण

अटल पूर्णांक dsi_mgr_bridge_get_id(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dsi_bridge *dsi_bridge = to_dsi_bridge(bridge);
	वापस dsi_bridge->id;
पूर्ण

अटल bool dsi_mgr_is_cmd_mode(काष्ठा msm_dsi *msm_dsi)
अणु
	अचिन्हित दीर्घ host_flags = msm_dsi_host_get_mode_flags(msm_dsi->host);
	वापस !(host_flags & MIPI_DSI_MODE_VIDEO);
पूर्ण

व्योम msm_dsi_manager_setup_encoder(पूर्णांक id)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_drm_निजी *priv = msm_dsi->dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	काष्ठा drm_encoder *encoder = msm_dsi_get_encoder(msm_dsi);

	अगर (encoder && kms->funcs->set_encoder_mode)
		kms->funcs->set_encoder_mode(kms, encoder,
					     dsi_mgr_is_cmd_mode(msm_dsi));
पूर्ण

अटल पूर्णांक msm_dsi_manager_panel_init(काष्ठा drm_connector *conn, u8 id)
अणु
	काष्ठा msm_drm_निजी *priv = conn->dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *other_dsi = dsi_mgr_get_other_dsi(id);
	काष्ठा msm_dsi *master_dsi, *slave_dsi;
	काष्ठा drm_panel *panel;

	अगर (IS_DUAL_DSI() && !IS_MASTER_DSI_LINK(id)) अणु
		master_dsi = other_dsi;
		slave_dsi = msm_dsi;
	पूर्ण अन्यथा अणु
		master_dsi = msm_dsi;
		slave_dsi = other_dsi;
	पूर्ण

	/*
	 * There is only 1 panel in the global panel list क्रम dual DSI mode.
	 * Thereक्रमe slave dsi should get the drm_panel instance from master
	 * dsi.
	 */
	panel = msm_dsi_host_get_panel(master_dsi->host);
	अगर (IS_ERR(panel)) अणु
		DRM_ERROR("Could not find panel for %u (%ld)\n", msm_dsi->id,
			  PTR_ERR(panel));
		वापस PTR_ERR(panel);
	पूर्ण

	अगर (!panel || !IS_DUAL_DSI())
		जाओ out;

	drm_object_attach_property(&conn->base,
				   conn->dev->mode_config.tile_property, 0);

	/*
	 * Set split display info to kms once dual DSI panel is connected to
	 * both hosts.
	 */
	अगर (other_dsi && other_dsi->panel && kms->funcs->set_split_display) अणु
		kms->funcs->set_split_display(kms, master_dsi->encoder,
					      slave_dsi->encoder,
					      dsi_mgr_is_cmd_mode(msm_dsi));
	पूर्ण

out:
	msm_dsi->panel = panel;
	वापस 0;
पूर्ण

अटल क्रमागत drm_connector_status dsi_mgr_connector_detect(
		काष्ठा drm_connector *connector, bool क्रमce)
अणु
	पूर्णांक id = dsi_mgr_connector_get_id(connector);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);

	वापस msm_dsi->panel ? connector_status_connected :
		connector_status_disconnected;
पूर्ण

अटल व्योम dsi_mgr_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा dsi_connector *dsi_connector = to_dsi_connector(connector);

	DBG("");

	drm_connector_cleanup(connector);

	kमुक्त(dsi_connector);
पूर्ण

अटल पूर्णांक dsi_mgr_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक id = dsi_mgr_connector_get_id(connector);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा drm_panel *panel = msm_dsi->panel;
	पूर्णांक num;

	अगर (!panel)
		वापस 0;

	/*
	 * In dual DSI mode, we have one connector that can be
	 * attached to the drm_panel.
	 */
	num = drm_panel_get_modes(panel, connector);
	अगर (!num)
		वापस 0;

	वापस num;
पूर्ण

अटल क्रमागत drm_mode_status dsi_mgr_connector_mode_valid(काष्ठा drm_connector *connector,
				काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक id = dsi_mgr_connector_get_id(connector);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा drm_encoder *encoder = msm_dsi_get_encoder(msm_dsi);
	काष्ठा msm_drm_निजी *priv = connector->dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	दीर्घ actual, requested;

	DBG("");
	requested = 1000 * mode->घड़ी;
	actual = kms->funcs->round_pixclk(kms, requested, encoder);

	DBG("requested=%ld, actual=%ld", requested, actual);
	अगर (actual != requested)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_encoder *
dsi_mgr_connector_best_encoder(काष्ठा drm_connector *connector)
अणु
	पूर्णांक id = dsi_mgr_connector_get_id(connector);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);

	DBG("");
	वापस msm_dsi_get_encoder(msm_dsi);
पूर्ण

अटल व्योम dsi_mgr_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	पूर्णांक id = dsi_mgr_bridge_get_id(bridge);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *msm_dsi1 = dsi_mgr_get_dsi(DSI_1);
	काष्ठा mipi_dsi_host *host = msm_dsi->host;
	काष्ठा drm_panel *panel = msm_dsi->panel;
	काष्ठा msm_dsi_phy_shared_timings phy_shared_timings[DSI_MAX];
	bool is_dual_dsi = IS_DUAL_DSI();
	पूर्णांक ret;

	DBG("id=%d", id);
	अगर (!msm_dsi_device_connected(msm_dsi))
		वापस;

	ret = dsi_mgr_phy_enable(id, phy_shared_timings);
	अगर (ret)
		जाओ phy_en_fail;

	/* Do nothing with the host अगर it is slave-DSI in हाल of dual DSI */
	अगर (is_dual_dsi && !IS_MASTER_DSI_LINK(id))
		वापस;

	ret = msm_dsi_host_घातer_on(host, &phy_shared_timings[id], is_dual_dsi);
	अगर (ret) अणु
		pr_err("%s: power on host %d failed, %d\n", __func__, id, ret);
		जाओ host_on_fail;
	पूर्ण

	अगर (is_dual_dsi && msm_dsi1) अणु
		ret = msm_dsi_host_घातer_on(msm_dsi1->host,
				&phy_shared_timings[DSI_1], is_dual_dsi);
		अगर (ret) अणु
			pr_err("%s: power on host1 failed, %d\n",
							__func__, ret);
			जाओ host1_on_fail;
		पूर्ण
	पूर्ण

	/* Always call panel functions once, because even क्रम dual panels,
	 * there is only one drm_panel instance.
	 */
	अगर (panel) अणु
		ret = drm_panel_prepare(panel);
		अगर (ret) अणु
			pr_err("%s: prepare panel %d failed, %d\n", __func__,
								id, ret);
			जाओ panel_prep_fail;
		पूर्ण
	पूर्ण

	ret = msm_dsi_host_enable(host);
	अगर (ret) अणु
		pr_err("%s: enable host %d failed, %d\n", __func__, id, ret);
		जाओ host_en_fail;
	पूर्ण

	अगर (is_dual_dsi && msm_dsi1) अणु
		ret = msm_dsi_host_enable(msm_dsi1->host);
		अगर (ret) अणु
			pr_err("%s: enable host1 failed, %d\n", __func__, ret);
			जाओ host1_en_fail;
		पूर्ण
	पूर्ण

	वापस;

host1_en_fail:
	msm_dsi_host_disable(host);
host_en_fail:
	अगर (panel)
		drm_panel_unprepare(panel);
panel_prep_fail:
	अगर (is_dual_dsi && msm_dsi1)
		msm_dsi_host_घातer_off(msm_dsi1->host);
host1_on_fail:
	msm_dsi_host_घातer_off(host);
host_on_fail:
	dsi_mgr_phy_disable(id);
phy_en_fail:
	वापस;
पूर्ण

अटल व्योम dsi_mgr_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	पूर्णांक id = dsi_mgr_bridge_get_id(bridge);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा drm_panel *panel = msm_dsi->panel;
	bool is_dual_dsi = IS_DUAL_DSI();
	पूर्णांक ret;

	DBG("id=%d", id);
	अगर (!msm_dsi_device_connected(msm_dsi))
		वापस;

	/* Do nothing with the host अगर it is slave-DSI in हाल of dual DSI */
	अगर (is_dual_dsi && !IS_MASTER_DSI_LINK(id))
		वापस;

	अगर (panel) अणु
		ret = drm_panel_enable(panel);
		अगर (ret) अणु
			pr_err("%s: enable panel %d failed, %d\n", __func__, id,
									ret);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dsi_mgr_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	पूर्णांक id = dsi_mgr_bridge_get_id(bridge);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा drm_panel *panel = msm_dsi->panel;
	bool is_dual_dsi = IS_DUAL_DSI();
	पूर्णांक ret;

	DBG("id=%d", id);
	अगर (!msm_dsi_device_connected(msm_dsi))
		वापस;

	/* Do nothing with the host अगर it is slave-DSI in हाल of dual DSI */
	अगर (is_dual_dsi && !IS_MASTER_DSI_LINK(id))
		वापस;

	अगर (panel) अणु
		ret = drm_panel_disable(panel);
		अगर (ret)
			pr_err("%s: Panel %d OFF failed, %d\n", __func__, id,
									ret);
	पूर्ण
पूर्ण

अटल व्योम dsi_mgr_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	पूर्णांक id = dsi_mgr_bridge_get_id(bridge);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *msm_dsi1 = dsi_mgr_get_dsi(DSI_1);
	काष्ठा mipi_dsi_host *host = msm_dsi->host;
	काष्ठा drm_panel *panel = msm_dsi->panel;
	bool is_dual_dsi = IS_DUAL_DSI();
	पूर्णांक ret;

	DBG("id=%d", id);

	अगर (!msm_dsi_device_connected(msm_dsi))
		वापस;

	/*
	 * Do nothing with the host अगर it is slave-DSI in हाल of dual DSI.
	 * It is safe to call dsi_mgr_phy_disable() here because a single PHY
	 * won't be diabled until both PHYs request disable.
	 */
	अगर (is_dual_dsi && !IS_MASTER_DSI_LINK(id))
		जाओ disable_phy;

	ret = msm_dsi_host_disable(host);
	अगर (ret)
		pr_err("%s: host %d disable failed, %d\n", __func__, id, ret);

	अगर (is_dual_dsi && msm_dsi1) अणु
		ret = msm_dsi_host_disable(msm_dsi1->host);
		अगर (ret)
			pr_err("%s: host1 disable failed, %d\n", __func__, ret);
	पूर्ण

	अगर (panel) अणु
		ret = drm_panel_unprepare(panel);
		अगर (ret)
			pr_err("%s: Panel %d unprepare failed,%d\n", __func__,
								id, ret);
	पूर्ण

	/* Save PHY status अगर it is a घड़ी source */
	msm_dsi_phy_pll_save_state(msm_dsi->phy);

	ret = msm_dsi_host_घातer_off(host);
	अगर (ret)
		pr_err("%s: host %d power off failed,%d\n", __func__, id, ret);

	अगर (is_dual_dsi && msm_dsi1) अणु
		ret = msm_dsi_host_घातer_off(msm_dsi1->host);
		अगर (ret)
			pr_err("%s: host1 power off failed, %d\n",
								__func__, ret);
	पूर्ण

disable_phy:
	dsi_mgr_phy_disable(id);
पूर्ण

अटल व्योम dsi_mgr_bridge_mode_set(काष्ठा drm_bridge *bridge,
		स्थिर काष्ठा drm_display_mode *mode,
		स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	पूर्णांक id = dsi_mgr_bridge_get_id(bridge);
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *other_dsi = dsi_mgr_get_other_dsi(id);
	काष्ठा mipi_dsi_host *host = msm_dsi->host;
	bool is_dual_dsi = IS_DUAL_DSI();

	DBG("set mode: " DRM_MODE_FMT, DRM_MODE_ARG(mode));

	अगर (is_dual_dsi && !IS_MASTER_DSI_LINK(id))
		वापस;

	msm_dsi_host_set_display_mode(host, adjusted_mode);
	अगर (is_dual_dsi && other_dsi)
		msm_dsi_host_set_display_mode(other_dsi->host, adjusted_mode);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs dsi_mgr_connector_funcs = अणु
	.detect = dsi_mgr_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = dsi_mgr_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs dsi_mgr_conn_helper_funcs = अणु
	.get_modes = dsi_mgr_connector_get_modes,
	.mode_valid = dsi_mgr_connector_mode_valid,
	.best_encoder = dsi_mgr_connector_best_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_bridge_funcs dsi_mgr_bridge_funcs = अणु
	.pre_enable = dsi_mgr_bridge_pre_enable,
	.enable = dsi_mgr_bridge_enable,
	.disable = dsi_mgr_bridge_disable,
	.post_disable = dsi_mgr_bridge_post_disable,
	.mode_set = dsi_mgr_bridge_mode_set,
पूर्ण;

/* initialize connector when we're connected to a drm_panel */
काष्ठा drm_connector *msm_dsi_manager_connector_init(u8 id)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा dsi_connector *dsi_connector;
	पूर्णांक ret;

	dsi_connector = kzalloc(माप(*dsi_connector), GFP_KERNEL);
	अगर (!dsi_connector)
		वापस ERR_PTR(-ENOMEM);

	dsi_connector->id = id;

	connector = &dsi_connector->base;

	ret = drm_connector_init(msm_dsi->dev, connector,
			&dsi_mgr_connector_funcs, DRM_MODE_CONNECTOR_DSI);
	अगर (ret)
		वापस ERR_PTR(ret);

	drm_connector_helper_add(connector, &dsi_mgr_conn_helper_funcs);

	/* Enable HPD to let hpd event is handled
	 * when panel is attached to the host.
	 */
	connector->polled = DRM_CONNECTOR_POLL_HPD;

	/* Display driver करोesn't support पूर्णांकerlace now. */
	connector->पूर्णांकerlace_allowed = 0;
	connector->द्विगुनscan_allowed = 0;

	drm_connector_attach_encoder(connector, msm_dsi->encoder);

	ret = msm_dsi_manager_panel_init(connector, id);
	अगर (ret) अणु
		DRM_DEV_ERROR(msm_dsi->dev->dev, "init panel failed %d\n", ret);
		जाओ fail;
	पूर्ण

	वापस connector;

fail:
	connector->funcs->destroy(msm_dsi->connector);
	वापस ERR_PTR(ret);
पूर्ण

bool msm_dsi_manager_validate_current_config(u8 id)
अणु
	bool is_dual_dsi = IS_DUAL_DSI();

	/*
	 * For dual DSI, we only have one drm panel. For this
	 * use हाल, we रेजिस्टर only one bridge/connector.
	 * Skip bridge/connector initialisation अगर it is
	 * slave-DSI क्रम dual DSI configuration.
	 */
	अगर (is_dual_dsi && !IS_MASTER_DSI_LINK(id)) अणु
		DBG("Skip bridge registration for slave DSI->id: %d\n", id);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* initialize bridge */
काष्ठा drm_bridge *msm_dsi_manager_bridge_init(u8 id)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा drm_bridge *bridge = शून्य;
	काष्ठा dsi_bridge *dsi_bridge;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	dsi_bridge = devm_kzalloc(msm_dsi->dev->dev,
				माप(*dsi_bridge), GFP_KERNEL);
	अगर (!dsi_bridge) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	dsi_bridge->id = id;

	encoder = msm_dsi->encoder;

	bridge = &dsi_bridge->base;
	bridge->funcs = &dsi_mgr_bridge_funcs;

	ret = drm_bridge_attach(encoder, bridge, शून्य, 0);
	अगर (ret)
		जाओ fail;

	वापस bridge;

fail:
	अगर (bridge)
		msm_dsi_manager_bridge_destroy(bridge);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा drm_connector *msm_dsi_manager_ext_bridge_init(u8 id)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा drm_device *dev = msm_dsi->dev;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *पूर्णांक_bridge, *ext_bridge;
	काष्ठा drm_connector *connector;
	काष्ठा list_head *connector_list;

	पूर्णांक_bridge = msm_dsi->bridge;
	ext_bridge = msm_dsi->बाह्यal_bridge =
			msm_dsi_host_get_bridge(msm_dsi->host);

	encoder = msm_dsi->encoder;

	/* link the पूर्णांकernal dsi bridge to the बाह्यal bridge */
	drm_bridge_attach(encoder, ext_bridge, पूर्णांक_bridge, 0);

	/*
	 * we need the drm_connector created by the बाह्यal bridge
	 * driver (or someone अन्यथा) to feed it to our driver's
	 * priv->connector[] list, मुख्यly क्रम msm_fbdev_init()
	 */
	connector_list = &dev->mode_config.connector_list;

	list_क्रम_each_entry(connector, connector_list, head) अणु
		अगर (drm_connector_has_possible_encoder(connector, encoder))
			वापस connector;
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

व्योम msm_dsi_manager_bridge_destroy(काष्ठा drm_bridge *bridge)
अणु
पूर्ण

पूर्णांक msm_dsi_manager_cmd_xfer(पूर्णांक id, स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *msm_dsi0 = dsi_mgr_get_dsi(DSI_0);
	काष्ठा mipi_dsi_host *host = msm_dsi->host;
	bool is_पढ़ो = (msg->rx_buf && msg->rx_len);
	bool need_sync = (IS_SYNC_NEEDED() && !is_पढ़ो);
	पूर्णांक ret;

	अगर (!msg->tx_buf || !msg->tx_len)
		वापस 0;

	/* In dual master हाल, panel requires the same commands sent to
	 * both DSI links. Host issues the command trigger to both links
	 * when DSI_1 calls the cmd transfer function, no matter it happens
	 * beक्रमe or after DSI_0 cmd transfer.
	 */
	अगर (need_sync && (id == DSI_0))
		वापस is_पढ़ो ? msg->rx_len : msg->tx_len;

	अगर (need_sync && msm_dsi0) अणु
		ret = msm_dsi_host_xfer_prepare(msm_dsi0->host, msg);
		अगर (ret) अणु
			pr_err("%s: failed to prepare non-trigger host, %d\n",
				__func__, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	ret = msm_dsi_host_xfer_prepare(host, msg);
	अगर (ret) अणु
		pr_err("%s: failed to prepare host, %d\n", __func__, ret);
		जाओ restore_host0;
	पूर्ण

	ret = is_पढ़ो ? msm_dsi_host_cmd_rx(host, msg) :
			msm_dsi_host_cmd_tx(host, msg);

	msm_dsi_host_xfer_restore(host, msg);

restore_host0:
	अगर (need_sync && msm_dsi0)
		msm_dsi_host_xfer_restore(msm_dsi0->host, msg);

	वापस ret;
पूर्ण

bool msm_dsi_manager_cmd_xfer_trigger(पूर्णांक id, u32 dma_base, u32 len)
अणु
	काष्ठा msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	काष्ठा msm_dsi *msm_dsi0 = dsi_mgr_get_dsi(DSI_0);
	काष्ठा mipi_dsi_host *host = msm_dsi->host;

	अगर (IS_SYNC_NEEDED() && (id == DSI_0))
		वापस false;

	अगर (IS_SYNC_NEEDED() && msm_dsi0)
		msm_dsi_host_cmd_xfer_commit(msm_dsi0->host, dma_base, len);

	msm_dsi_host_cmd_xfer_commit(host, dma_base, len);

	वापस true;
पूर्ण

पूर्णांक msm_dsi_manager_रेजिस्टर(काष्ठा msm_dsi *msm_dsi)
अणु
	काष्ठा msm_dsi_manager *msm_dsim = &msm_dsim_glb;
	पूर्णांक id = msm_dsi->id;
	पूर्णांक ret;

	अगर (id >= DSI_MAX) अणु
		pr_err("%s: invalid id %d\n", __func__, id);
		वापस -EINVAL;
	पूर्ण

	अगर (msm_dsim->dsi[id]) अणु
		pr_err("%s: dsi%d already registered\n", __func__, id);
		वापस -EBUSY;
	पूर्ण

	msm_dsim->dsi[id] = msm_dsi;

	ret = dsi_mgr_parse_dual_dsi(msm_dsi->pdev->dev.of_node, id);
	अगर (ret) अणु
		pr_err("%s: failed to parse dual DSI info\n", __func__);
		जाओ fail;
	पूर्ण

	ret = dsi_mgr_setup_components(id);
	अगर (ret) अणु
		pr_err("%s: failed to register mipi dsi host for DSI %d\n",
			__func__, id);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	msm_dsim->dsi[id] = शून्य;
	वापस ret;
पूर्ण

व्योम msm_dsi_manager_unरेजिस्टर(काष्ठा msm_dsi *msm_dsi)
अणु
	काष्ठा msm_dsi_manager *msm_dsim = &msm_dsim_glb;

	अगर (msm_dsi->host)
		msm_dsi_host_unरेजिस्टर(msm_dsi->host);

	अगर (msm_dsi->id >= 0)
		msm_dsim->dsi[msm_dsi->id] = शून्य;
पूर्ण

