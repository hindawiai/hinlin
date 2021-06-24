<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI driver क्रम OMAP5
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Authors:
 *	Yong Zhi
 *	Mythri pk
 *	Archit Taneja <archit@ti.com>
 *	Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#घोषणा DSS_SUBSYS_NAME "HDMI"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/clk.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/component.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <sound/omap-hdmi-audपन.स>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_state_helper.h>

#समावेश "omapdss.h"
#समावेश "hdmi5_core.h"
#समावेश "dss.h"

अटल पूर्णांक hdmi_runसमय_get(काष्ठा omap_hdmi *hdmi)
अणु
	पूर्णांक r;

	DSSDBG("hdmi_runtime_get\n");

	r = pm_runसमय_get_sync(&hdmi->pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_noidle(&hdmi->pdev->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hdmi_runसमय_put(काष्ठा omap_hdmi *hdmi)
अणु
	पूर्णांक r;

	DSSDBG("hdmi_runtime_put\n");

	r = pm_runसमय_put_sync(&hdmi->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

अटल irqवापस_t hdmi_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा omap_hdmi *hdmi = data;
	काष्ठा hdmi_wp_data *wp = &hdmi->wp;
	u32 irqstatus;

	irqstatus = hdmi_wp_get_irqstatus(wp);
	hdmi_wp_set_irqstatus(wp, irqstatus);

	अगर ((irqstatus & HDMI_IRQ_LINK_CONNECT) &&
			irqstatus & HDMI_IRQ_LINK_DISCONNECT) अणु
		u32 v;
		/*
		 * If we get both connect and disconnect पूर्णांकerrupts at the same
		 * समय, turn off the PHY, clear पूर्णांकerrupts, and restart, which
		 * उठाओs connect पूर्णांकerrupt अगर a cable is connected, or nothing
		 * अगर cable is not connected.
		 */

		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_OFF);

		/*
		 * We always get bogus CONNECT & DISCONNECT पूर्णांकerrupts when
		 * setting the PHY to LDOON. To ignore those, we क्रमce the RXDET
		 * line to 0 until the PHY घातer state has been changed.
		 */
		v = hdmi_पढ़ो_reg(hdmi->phy.base, HDMI_TXPHY_PAD_CFG_CTRL);
		v = FLD_MOD(v, 1, 15, 15); /* FORCE_RXDET_HIGH */
		v = FLD_MOD(v, 0, 14, 7); /* RXDET_LINE */
		hdmi_ग_लिखो_reg(hdmi->phy.base, HDMI_TXPHY_PAD_CFG_CTRL, v);

		hdmi_wp_set_irqstatus(wp, HDMI_IRQ_LINK_CONNECT |
				HDMI_IRQ_LINK_DISCONNECT);

		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);

		REG_FLD_MOD(hdmi->phy.base, HDMI_TXPHY_PAD_CFG_CTRL, 0, 15, 15);

	पूर्ण अन्यथा अगर (irqstatus & HDMI_IRQ_LINK_CONNECT) अणु
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_TXON);
	पूर्ण अन्यथा अगर (irqstatus & HDMI_IRQ_LINK_DISCONNECT) अणु
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hdmi_घातer_on_core(काष्ठा omap_hdmi *hdmi)
अणु
	पूर्णांक r;

	r = regulator_enable(hdmi->vdda_reg);
	अगर (r)
		वापस r;

	r = hdmi_runसमय_get(hdmi);
	अगर (r)
		जाओ err_runसमय_get;

	/* Make selection of HDMI in DSS */
	dss_select_hdmi_venc_clk_source(hdmi->dss, DSS_HDMI_M_PCLK);

	hdmi->core_enabled = true;

	वापस 0;

err_runसमय_get:
	regulator_disable(hdmi->vdda_reg);

	वापस r;
पूर्ण

अटल व्योम hdmi_घातer_off_core(काष्ठा omap_hdmi *hdmi)
अणु
	hdmi->core_enabled = false;

	hdmi_runसमय_put(hdmi);
	regulator_disable(hdmi->vdda_reg);
पूर्ण

अटल पूर्णांक hdmi_घातer_on_full(काष्ठा omap_hdmi *hdmi)
अणु
	पूर्णांक r;
	स्थिर काष्ठा videomode *vm;
	काष्ठा dss_pll_घड़ी_info hdmi_cinfo = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक pc;

	r = hdmi_घातer_on_core(hdmi);
	अगर (r)
		वापस r;

	vm = &hdmi->cfg.vm;

	DSSDBG("hdmi_power_on hactive= %d vactive = %d\n", vm->hactive,
	       vm->vactive);

	pc = vm->pixelघड़ी;
	अगर (vm->flags & DISPLAY_FLAGS_DOUBLECLK)
		pc *= 2;

	/* DSS_HDMI_TCLK is bitclk / 10 */
	pc *= 10;

	dss_pll_calc_b(&hdmi->pll.pll, clk_get_rate(hdmi->pll.pll.clkin),
		pc, &hdmi_cinfo);

	/* disable and clear irqs */
	hdmi_wp_clear_irqenable(&hdmi->wp, 0xffffffff);
	hdmi_wp_set_irqstatus(&hdmi->wp,
			hdmi_wp_get_irqstatus(&hdmi->wp));

	r = dss_pll_enable(&hdmi->pll.pll);
	अगर (r) अणु
		DSSERR("Failed to enable PLL\n");
		जाओ err_pll_enable;
	पूर्ण

	r = dss_pll_set_config(&hdmi->pll.pll, &hdmi_cinfo);
	अगर (r) अणु
		DSSERR("Failed to configure PLL\n");
		जाओ err_pll_cfg;
	पूर्ण

	r = hdmi_phy_configure(&hdmi->phy, hdmi_cinfo.clkdco,
		hdmi_cinfo.clkout[0]);
	अगर (r) अणु
		DSSDBG("Failed to start PHY\n");
		जाओ err_phy_cfg;
	पूर्ण

	r = hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_LDOON);
	अगर (r)
		जाओ err_phy_pwr;

	hdmi5_configure(&hdmi->core, &hdmi->wp, &hdmi->cfg);

	r = dss_mgr_enable(&hdmi->output);
	अगर (r)
		जाओ err_mgr_enable;

	r = hdmi_wp_video_start(&hdmi->wp);
	अगर (r)
		जाओ err_vid_enable;

	hdmi_wp_set_irqenable(&hdmi->wp,
			HDMI_IRQ_LINK_CONNECT | HDMI_IRQ_LINK_DISCONNECT);

	वापस 0;

err_vid_enable:
	dss_mgr_disable(&hdmi->output);
err_mgr_enable:
	hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_OFF);
err_phy_pwr:
err_phy_cfg:
err_pll_cfg:
	dss_pll_disable(&hdmi->pll.pll);
err_pll_enable:
	hdmi_घातer_off_core(hdmi);
	वापस -EIO;
पूर्ण

अटल व्योम hdmi_घातer_off_full(काष्ठा omap_hdmi *hdmi)
अणु
	hdmi_wp_clear_irqenable(&hdmi->wp, 0xffffffff);

	hdmi_wp_video_stop(&hdmi->wp);

	dss_mgr_disable(&hdmi->output);

	hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_OFF);

	dss_pll_disable(&hdmi->pll.pll);

	hdmi_घातer_off_core(hdmi);
पूर्ण

अटल पूर्णांक hdmi_dump_regs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा omap_hdmi *hdmi = s->निजी;

	mutex_lock(&hdmi->lock);

	अगर (hdmi_runसमय_get(hdmi)) अणु
		mutex_unlock(&hdmi->lock);
		वापस 0;
	पूर्ण

	hdmi_wp_dump(&hdmi->wp, s);
	hdmi_pll_dump(&hdmi->pll, s);
	hdmi_phy_dump(&hdmi->phy, s);
	hdmi5_core_dump(&hdmi->core, s);

	hdmi_runसमय_put(hdmi);
	mutex_unlock(&hdmi->lock);
	वापस 0;
पूर्ण

अटल व्योम hdmi_start_audio_stream(काष्ठा omap_hdmi *hd)
अणु
	REG_FLD_MOD(hd->wp.base, HDMI_WP_SYSCONFIG, 1, 3, 2);
	hdmi_wp_audio_enable(&hd->wp, true);
	hdmi_wp_audio_core_req_enable(&hd->wp, true);
पूर्ण

अटल व्योम hdmi_stop_audio_stream(काष्ठा omap_hdmi *hd)
अणु
	hdmi_wp_audio_core_req_enable(&hd->wp, false);
	hdmi_wp_audio_enable(&hd->wp, false);
	REG_FLD_MOD(hd->wp.base, HDMI_WP_SYSCONFIG, hd->wp_idlemode, 3, 2);
पूर्ण

अटल पूर्णांक hdmi_core_enable(काष्ठा omap_hdmi *hdmi)
अणु
	पूर्णांक r = 0;

	DSSDBG("ENTER omapdss_hdmi_core_enable\n");

	mutex_lock(&hdmi->lock);

	r = hdmi_घातer_on_core(hdmi);
	अगर (r) अणु
		DSSERR("failed to power on device\n");
		जाओ err0;
	पूर्ण

	mutex_unlock(&hdmi->lock);
	वापस 0;

err0:
	mutex_unlock(&hdmi->lock);
	वापस r;
पूर्ण

अटल व्योम hdmi_core_disable(काष्ठा omap_hdmi *hdmi)
अणु
	DSSDBG("Enter omapdss_hdmi_core_disable\n");

	mutex_lock(&hdmi->lock);

	hdmi_घातer_off_core(hdmi);

	mutex_unlock(&hdmi->lock);
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

अटल पूर्णांक hdmi5_bridge_attach(काष्ठा drm_bridge *bridge,
			       क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा omap_hdmi *hdmi = drm_bridge_to_hdmi(bridge);

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	वापस drm_bridge_attach(bridge->encoder, hdmi->output.next_bridge,
				 bridge, flags);
पूर्ण

अटल व्योम hdmi5_bridge_mode_set(काष्ठा drm_bridge *bridge,
				  स्थिर काष्ठा drm_display_mode *mode,
				  स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा omap_hdmi *hdmi = drm_bridge_to_hdmi(bridge);

	mutex_lock(&hdmi->lock);

	drm_display_mode_to_videomode(adjusted_mode, &hdmi->cfg.vm);

	dispc_set_tv_pclk(hdmi->dss->dispc, adjusted_mode->घड़ी * 1000);

	mutex_unlock(&hdmi->lock);
पूर्ण

अटल व्योम hdmi5_bridge_enable(काष्ठा drm_bridge *bridge,
				काष्ठा drm_bridge_state *bridge_state)
अणु
	काष्ठा omap_hdmi *hdmi = drm_bridge_to_hdmi(bridge);
	काष्ठा drm_atomic_state *state = bridge_state->base.state;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_crtc_state *crtc_state;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * None of these should fail, as the bridge can't be enabled without a
	 * valid CRTC to connector path with fully populated new states.
	 */
	connector = drm_atomic_get_new_connector_क्रम_encoder(state,
							     bridge->encoder);
	अगर (WARN_ON(!connector))
		वापस;
	conn_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (WARN_ON(!conn_state))
		वापस;
	crtc_state = drm_atomic_get_new_crtc_state(state, conn_state->crtc);
	अगर (WARN_ON(!crtc_state))
		वापस;

	hdmi->cfg.hdmi_dvi_mode = connector->display_info.is_hdmi
				? HDMI_HDMI : HDMI_DVI;

	अगर (connector->display_info.is_hdmi) अणु
		स्थिर काष्ठा drm_display_mode *mode;
		काष्ठा hdmi_avi_infoframe avi;

		mode = &crtc_state->adjusted_mode;
		ret = drm_hdmi_avi_infoframe_from_display_mode(&avi, connector,
							       mode);
		अगर (ret == 0)
			hdmi->cfg.infoframe = avi;
	पूर्ण

	mutex_lock(&hdmi->lock);

	ret = hdmi_घातer_on_full(hdmi);
	अगर (ret) अणु
		DSSERR("failed to power on device\n");
		जाओ करोne;
	पूर्ण

	अगर (hdmi->audio_configured) अणु
		ret = hdmi5_audio_config(&hdmi->core, &hdmi->wp,
					 &hdmi->audio_config,
					 hdmi->cfg.vm.pixelघड़ी);
		अगर (ret) अणु
			DSSERR("Error restoring audio configuration: %d", ret);
			hdmi->audio_पात_cb(&hdmi->pdev->dev);
			hdmi->audio_configured = false;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&hdmi->audio_playing_lock, flags);
	अगर (hdmi->audio_configured && hdmi->audio_playing)
		hdmi_start_audio_stream(hdmi);
	hdmi->display_enabled = true;
	spin_unlock_irqrestore(&hdmi->audio_playing_lock, flags);

करोne:
	mutex_unlock(&hdmi->lock);
पूर्ण

अटल व्योम hdmi5_bridge_disable(काष्ठा drm_bridge *bridge,
				 काष्ठा drm_bridge_state *bridge_state)
अणु
	काष्ठा omap_hdmi *hdmi = drm_bridge_to_hdmi(bridge);
	अचिन्हित दीर्घ flags;

	mutex_lock(&hdmi->lock);

	spin_lock_irqsave(&hdmi->audio_playing_lock, flags);
	hdmi_stop_audio_stream(hdmi);
	hdmi->display_enabled = false;
	spin_unlock_irqrestore(&hdmi->audio_playing_lock, flags);

	hdmi_घातer_off_full(hdmi);

	mutex_unlock(&hdmi->lock);
पूर्ण

अटल काष्ठा edid *hdmi5_bridge_get_edid(काष्ठा drm_bridge *bridge,
					  काष्ठा drm_connector *connector)
अणु
	काष्ठा omap_hdmi *hdmi = drm_bridge_to_hdmi(bridge);
	काष्ठा edid *edid;
	bool need_enable;
	पूर्णांक idlemode;
	पूर्णांक r;

	need_enable = hdmi->core_enabled == false;

	अगर (need_enable) अणु
		r = hdmi_core_enable(hdmi);
		अगर (r)
			वापस शून्य;
	पूर्ण

	mutex_lock(&hdmi->lock);
	r = hdmi_runसमय_get(hdmi);
	BUG_ON(r);

	idlemode = REG_GET(hdmi->wp.base, HDMI_WP_SYSCONFIG, 3, 2);
	/* No-idle mode */
	REG_FLD_MOD(hdmi->wp.base, HDMI_WP_SYSCONFIG, 1, 3, 2);

	hdmi5_core_ddc_init(&hdmi->core);

	edid = drm_करो_get_edid(connector, hdmi5_core_ddc_पढ़ो, &hdmi->core);

	hdmi5_core_ddc_uninit(&hdmi->core);

	REG_FLD_MOD(hdmi->wp.base, HDMI_WP_SYSCONFIG, idlemode, 3, 2);

	hdmi_runसमय_put(hdmi);
	mutex_unlock(&hdmi->lock);

	अगर (need_enable)
		hdmi_core_disable(hdmi);

	वापस (काष्ठा edid *)edid;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs hdmi5_bridge_funcs = अणु
	.attach = hdmi5_bridge_attach,
	.mode_set = hdmi5_bridge_mode_set,
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.atomic_enable = hdmi5_bridge_enable,
	.atomic_disable = hdmi5_bridge_disable,
	.get_edid = hdmi5_bridge_get_edid,
पूर्ण;

अटल व्योम hdmi5_bridge_init(काष्ठा omap_hdmi *hdmi)
अणु
	hdmi->bridge.funcs = &hdmi5_bridge_funcs;
	hdmi->bridge.of_node = hdmi->pdev->dev.of_node;
	hdmi->bridge.ops = DRM_BRIDGE_OP_EDID;
	hdmi->bridge.type = DRM_MODE_CONNECTOR_HDMIA;

	drm_bridge_add(&hdmi->bridge);
पूर्ण

अटल व्योम hdmi5_bridge_cleanup(काष्ठा omap_hdmi *hdmi)
अणु
	drm_bridge_हटाओ(&hdmi->bridge);
पूर्ण

/* -----------------------------------------------------------------------------
 * Audio Callbacks
 */

अटल पूर्णांक hdmi_audio_startup(काष्ठा device *dev,
			      व्योम (*पात_cb)(काष्ठा device *dev))
अणु
	काष्ठा omap_hdmi *hd = dev_get_drvdata(dev);

	mutex_lock(&hd->lock);

	WARN_ON(hd->audio_पात_cb != शून्य);

	hd->audio_पात_cb = पात_cb;

	mutex_unlock(&hd->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_audio_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा omap_hdmi *hd = dev_get_drvdata(dev);

	mutex_lock(&hd->lock);
	hd->audio_पात_cb = शून्य;
	hd->audio_configured = false;
	hd->audio_playing = false;
	mutex_unlock(&hd->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_audio_start(काष्ठा device *dev)
अणु
	काष्ठा omap_hdmi *hd = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hd->audio_playing_lock, flags);

	अगर (hd->display_enabled) अणु
		अगर (!hdmi_mode_has_audio(&hd->cfg))
			DSSERR("%s: Video mode does not support audio\n",
			       __func__);
		hdmi_start_audio_stream(hd);
	पूर्ण
	hd->audio_playing = true;

	spin_unlock_irqrestore(&hd->audio_playing_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम hdmi_audio_stop(काष्ठा device *dev)
अणु
	काष्ठा omap_hdmi *hd = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	अगर (!hdmi_mode_has_audio(&hd->cfg))
		DSSERR("%s: Video mode does not support audio\n", __func__);

	spin_lock_irqsave(&hd->audio_playing_lock, flags);

	अगर (hd->display_enabled)
		hdmi_stop_audio_stream(hd);
	hd->audio_playing = false;

	spin_unlock_irqrestore(&hd->audio_playing_lock, flags);
पूर्ण

अटल पूर्णांक hdmi_audio_config(काष्ठा device *dev,
			     काष्ठा omap_dss_audio *dss_audio)
अणु
	काष्ठा omap_hdmi *hd = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&hd->lock);

	अगर (hd->display_enabled) अणु
		ret = hdmi5_audio_config(&hd->core, &hd->wp, dss_audio,
					 hd->cfg.vm.pixelघड़ी);
		अगर (ret)
			जाओ out;
	पूर्ण

	hd->audio_configured = true;
	hd->audio_config = *dss_audio;
out:
	mutex_unlock(&hd->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा omap_hdmi_audio_ops hdmi_audio_ops = अणु
	.audio_startup = hdmi_audio_startup,
	.audio_shutकरोwn = hdmi_audio_shutकरोwn,
	.audio_start = hdmi_audio_start,
	.audio_stop = hdmi_audio_stop,
	.audio_config = hdmi_audio_config,
पूर्ण;

अटल पूर्णांक hdmi_audio_रेजिस्टर(काष्ठा omap_hdmi *hdmi)
अणु
	काष्ठा omap_hdmi_audio_pdata pdata = अणु
		.dev = &hdmi->pdev->dev,
		.version = 5,
		.audio_dma_addr = hdmi_wp_get_audio_dma_addr(&hdmi->wp),
		.ops = &hdmi_audio_ops,
	पूर्ण;

	hdmi->audio_pdev = platक्रमm_device_रेजिस्टर_data(
		&hdmi->pdev->dev, "omap-hdmi-audio", PLATFORM_DEVID_AUTO,
		&pdata, माप(pdata));

	अगर (IS_ERR(hdmi->audio_pdev))
		वापस PTR_ERR(hdmi->audio_pdev);

	hdmi_runसमय_get(hdmi);
	hdmi->wp_idlemode =
		REG_GET(hdmi->wp.base, HDMI_WP_SYSCONFIG, 3, 2);
	hdmi_runसमय_put(hdmi);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Component Bind & Unbind
 */

अटल पूर्णांक hdmi5_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा dss_device *dss = dss_get_device(master);
	काष्ठा omap_hdmi *hdmi = dev_get_drvdata(dev);
	पूर्णांक r;

	hdmi->dss = dss;

	r = hdmi_pll_init(dss, hdmi->pdev, &hdmi->pll, &hdmi->wp);
	अगर (r)
		वापस r;

	r = hdmi_audio_रेजिस्टर(hdmi);
	अगर (r) अणु
		DSSERR("Registering HDMI audio failed %d\n", r);
		जाओ err_pll_uninit;
	पूर्ण

	hdmi->debugfs = dss_debugfs_create_file(dss, "hdmi", hdmi_dump_regs,
						hdmi);

	वापस 0;

err_pll_uninit:
	hdmi_pll_uninit(&hdmi->pll);
	वापस r;
पूर्ण

अटल व्योम hdmi5_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा omap_hdmi *hdmi = dev_get_drvdata(dev);

	dss_debugfs_हटाओ_file(hdmi->debugfs);

	अगर (hdmi->audio_pdev)
		platक्रमm_device_unरेजिस्टर(hdmi->audio_pdev);

	hdmi_pll_uninit(&hdmi->pll);
पूर्ण

अटल स्थिर काष्ठा component_ops hdmi5_component_ops = अणु
	.bind	= hdmi5_bind,
	.unbind	= hdmi5_unbind,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe & Remove, Suspend & Resume
 */

अटल पूर्णांक hdmi5_init_output(काष्ठा omap_hdmi *hdmi)
अणु
	काष्ठा omap_dss_device *out = &hdmi->output;
	पूर्णांक r;

	hdmi5_bridge_init(hdmi);

	out->dev = &hdmi->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_HDMI;
	out->type = OMAP_DISPLAY_TYPE_HDMI;
	out->name = "hdmi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_DIGIT;
	out->of_port = 0;

	r = omapdss_device_init_output(out, &hdmi->bridge);
	अगर (r < 0) अणु
		hdmi5_bridge_cleanup(hdmi);
		वापस r;
	पूर्ण

	omapdss_device_रेजिस्टर(out);

	वापस 0;
पूर्ण

अटल व्योम hdmi5_uninit_output(काष्ठा omap_hdmi *hdmi)
अणु
	काष्ठा omap_dss_device *out = &hdmi->output;

	omapdss_device_unरेजिस्टर(out);
	omapdss_device_cleanup_output(out);

	hdmi5_bridge_cleanup(hdmi);
पूर्ण

अटल पूर्णांक hdmi5_probe_of(काष्ठा omap_hdmi *hdmi)
अणु
	काष्ठा platक्रमm_device *pdev = hdmi->pdev;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *ep;
	पूर्णांक r;

	ep = of_graph_get_endpoपूर्णांक_by_regs(node, 0, 0);
	अगर (!ep)
		वापस 0;

	r = hdmi_parse_lanes_of(pdev, ep, &hdmi->phy);
	of_node_put(ep);
	वापस r;
पूर्ण

अटल पूर्णांक hdmi5_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_hdmi *hdmi;
	पूर्णांक irq;
	पूर्णांक r;

	hdmi = kzalloc(माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	hdmi->pdev = pdev;

	dev_set_drvdata(&pdev->dev, hdmi);

	mutex_init(&hdmi->lock);
	spin_lock_init(&hdmi->audio_playing_lock);

	r = hdmi5_probe_of(hdmi);
	अगर (r)
		जाओ err_मुक्त;

	r = hdmi_wp_init(pdev, &hdmi->wp, 5);
	अगर (r)
		जाओ err_मुक्त;

	r = hdmi_phy_init(pdev, &hdmi->phy, 5);
	अगर (r)
		जाओ err_मुक्त;

	r = hdmi5_core_init(pdev, &hdmi->core);
	अगर (r)
		जाओ err_मुक्त;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		DSSERR("platform_get_irq failed\n");
		r = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	r = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
			शून्य, hdmi_irq_handler,
			IRQF_ONESHOT, "OMAP HDMI", hdmi);
	अगर (r) अणु
		DSSERR("HDMI IRQ request failed\n");
		जाओ err_मुक्त;
	पूर्ण

	hdmi->vdda_reg = devm_regulator_get(&pdev->dev, "vdda");
	अगर (IS_ERR(hdmi->vdda_reg)) अणु
		r = PTR_ERR(hdmi->vdda_reg);
		अगर (r != -EPROBE_DEFER)
			DSSERR("can't get VDDA regulator\n");
		जाओ err_मुक्त;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	r = hdmi5_init_output(hdmi);
	अगर (r)
		जाओ err_pm_disable;

	r = component_add(&pdev->dev, &hdmi5_component_ops);
	अगर (r)
		जाओ err_uninit_output;

	वापस 0;

err_uninit_output:
	hdmi5_uninit_output(hdmi);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
err_मुक्त:
	kमुक्त(hdmi);
	वापस r;
पूर्ण

अटल पूर्णांक hdmi5_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_hdmi *hdmi = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &hdmi5_component_ops);

	hdmi5_uninit_output(hdmi);

	pm_runसमय_disable(&pdev->dev);

	kमुक्त(hdmi);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hdmi_of_match[] = अणु
	अणु .compatible = "ti,omap5-hdmi", पूर्ण,
	अणु .compatible = "ti,dra7-hdmi", पूर्ण,
	अणुपूर्ण,
पूर्ण;

काष्ठा platक्रमm_driver omapdss_hdmi5hw_driver = अणु
	.probe		= hdmi5_probe,
	.हटाओ		= hdmi5_हटाओ,
	.driver         = अणु
		.name   = "omapdss_hdmi5",
		.of_match_table = hdmi_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
