<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI पूर्णांकerface DSS driver क्रम TI's OMAP4 family of SoCs.
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com/
 * Authors: Yong Zhi
 *	Mythri pk <mythripk@ti.com>
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
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/component.h>
#समावेश <video/omapfb_dss.h>
#समावेश <sound/omap-hdmi-audपन.स>

#समावेश "hdmi4_core.h"
#समावेश "dss.h"
#समावेश "dss_features.h"
#समावेश "hdmi.h"

अटल काष्ठा omap_hdmi hdmi;

अटल पूर्णांक hdmi_runसमय_get(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("hdmi_runtime_get\n");

	r = pm_runसमय_get_sync(&hdmi.pdev->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_sync(&hdmi.pdev->dev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hdmi_runसमय_put(व्योम)
अणु
	पूर्णांक r;

	DSSDBG("hdmi_runtime_put\n");

	r = pm_runसमय_put_sync(&hdmi.pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

अटल irqवापस_t hdmi_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hdmi_wp_data *wp = data;
	u32 irqstatus;

	irqstatus = hdmi_wp_get_irqstatus(wp);
	hdmi_wp_set_irqstatus(wp, irqstatus);

	अगर ((irqstatus & HDMI_IRQ_LINK_CONNECT) &&
			irqstatus & HDMI_IRQ_LINK_DISCONNECT) अणु
		/*
		 * If we get both connect and disconnect पूर्णांकerrupts at the same
		 * समय, turn off the PHY, clear पूर्णांकerrupts, and restart, which
		 * उठाओs connect पूर्णांकerrupt अगर a cable is connected, or nothing
		 * अगर cable is not connected.
		 */
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_OFF);

		hdmi_wp_set_irqstatus(wp, HDMI_IRQ_LINK_CONNECT |
				HDMI_IRQ_LINK_DISCONNECT);

		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	पूर्ण अन्यथा अगर (irqstatus & HDMI_IRQ_LINK_CONNECT) अणु
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_TXON);
	पूर्ण अन्यथा अगर (irqstatus & HDMI_IRQ_LINK_DISCONNECT) अणु
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hdmi_init_regulator(व्योम)
अणु
	काष्ठा regulator *reg;

	अगर (hdmi.vdda_reg != शून्य)
		वापस 0;

	reg = devm_regulator_get(&hdmi.pdev->dev, "vdda");

	अगर (IS_ERR(reg)) अणु
		अगर (PTR_ERR(reg) != -EPROBE_DEFER)
			DSSERR("can't get VDDA regulator\n");
		वापस PTR_ERR(reg);
	पूर्ण

	hdmi.vdda_reg = reg;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_घातer_on_core(काष्ठा omap_dss_device *dssdev)
अणु
	पूर्णांक r;

	r = regulator_enable(hdmi.vdda_reg);
	अगर (r)
		वापस r;

	r = hdmi_runसमय_get();
	अगर (r)
		जाओ err_runसमय_get;

	/* Make selection of HDMI in DSS */
	dss_select_hdmi_venc_clk_source(DSS_HDMI_M_PCLK);

	hdmi.core_enabled = true;

	वापस 0;

err_runसमय_get:
	regulator_disable(hdmi.vdda_reg);

	वापस r;
पूर्ण

अटल व्योम hdmi_घातer_off_core(काष्ठा omap_dss_device *dssdev)
अणु
	hdmi.core_enabled = false;

	hdmi_runसमय_put();
	regulator_disable(hdmi.vdda_reg);
पूर्ण

अटल पूर्णांक hdmi_घातer_on_full(काष्ठा omap_dss_device *dssdev)
अणु
	पूर्णांक r;
	काष्ठा omap_video_timings *p;
	काष्ठा omap_overlay_manager *mgr = hdmi.output.manager;
	काष्ठा hdmi_wp_data *wp = &hdmi.wp;
	काष्ठा dss_pll_घड़ी_info hdmi_cinfo = अणु 0 पूर्ण;

	r = hdmi_घातer_on_core(dssdev);
	अगर (r)
		वापस r;

	/* disable and clear irqs */
	hdmi_wp_clear_irqenable(wp, 0xffffffff);
	hdmi_wp_set_irqstatus(wp, 0xffffffff);

	p = &hdmi.cfg.timings;

	DSSDBG("hdmi_power_on x_res= %d y_res = %d\n", p->x_res, p->y_res);

	hdmi_pll_compute(&hdmi.pll, p->pixelघड़ी, &hdmi_cinfo);

	r = dss_pll_enable(&hdmi.pll.pll);
	अगर (r) अणु
		DSSERR("Failed to enable PLL\n");
		जाओ err_pll_enable;
	पूर्ण

	r = dss_pll_set_config(&hdmi.pll.pll, &hdmi_cinfo);
	अगर (r) अणु
		DSSERR("Failed to configure PLL\n");
		जाओ err_pll_cfg;
	पूर्ण

	r = hdmi_phy_configure(&hdmi.phy, hdmi_cinfo.clkdco,
		hdmi_cinfo.clkout[0]);
	अगर (r) अणु
		DSSDBG("Failed to configure PHY\n");
		जाओ err_phy_cfg;
	पूर्ण

	r = hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	अगर (r)
		जाओ err_phy_pwr;

	hdmi4_configure(&hdmi.core, &hdmi.wp, &hdmi.cfg);

	/* bypass TV gamma table */
	dispc_enable_gamma_table(0);

	/* tv size */
	dss_mgr_set_timings(mgr, p);

	r = hdmi_wp_video_start(&hdmi.wp);
	अगर (r)
		जाओ err_vid_enable;

	r = dss_mgr_enable(mgr);
	अगर (r)
		जाओ err_mgr_enable;

	hdmi_wp_set_irqenable(wp,
		HDMI_IRQ_LINK_CONNECT | HDMI_IRQ_LINK_DISCONNECT);

	वापस 0;

err_mgr_enable:
	hdmi_wp_video_stop(&hdmi.wp);
err_vid_enable:
	hdmi_wp_set_phy_pwr(&hdmi.wp, HDMI_PHYPWRCMD_OFF);
err_phy_pwr:
err_phy_cfg:
err_pll_cfg:
	dss_pll_disable(&hdmi.pll.pll);
err_pll_enable:
	hdmi_घातer_off_core(dssdev);
	वापस -EIO;
पूर्ण

अटल व्योम hdmi_घातer_off_full(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_overlay_manager *mgr = hdmi.output.manager;

	hdmi_wp_clear_irqenable(&hdmi.wp, 0xffffffff);

	dss_mgr_disable(mgr);

	hdmi_wp_video_stop(&hdmi.wp);

	hdmi_wp_set_phy_pwr(&hdmi.wp, HDMI_PHYPWRCMD_OFF);

	dss_pll_disable(&hdmi.pll.pll);

	hdmi_घातer_off_core(dssdev);
पूर्ण

अटल पूर्णांक hdmi_display_check_timing(काष्ठा omap_dss_device *dssdev,
					काष्ठा omap_video_timings *timings)
अणु
	काष्ठा omap_dss_device *out = &hdmi.output;

	अगर (!dispc_mgr_timings_ok(out->dispc_channel, timings))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम hdmi_display_set_timing(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	mutex_lock(&hdmi.lock);

	hdmi.cfg.timings = *timings;

	dispc_set_tv_pclk(timings->pixelघड़ी);

	mutex_unlock(&hdmi.lock);
पूर्ण

अटल व्योम hdmi_display_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	*timings = hdmi.cfg.timings;
पूर्ण

अटल व्योम hdmi_dump_regs(काष्ठा seq_file *s)
अणु
	mutex_lock(&hdmi.lock);

	अगर (hdmi_runसमय_get()) अणु
		mutex_unlock(&hdmi.lock);
		वापस;
	पूर्ण

	hdmi_wp_dump(&hdmi.wp, s);
	hdmi_pll_dump(&hdmi.pll, s);
	hdmi_phy_dump(&hdmi.phy, s);
	hdmi4_core_dump(&hdmi.core, s);

	hdmi_runसमय_put();
	mutex_unlock(&hdmi.lock);
पूर्ण

अटल पूर्णांक पढ़ो_edid(u8 *buf, पूर्णांक len)
अणु
	पूर्णांक r;

	mutex_lock(&hdmi.lock);

	r = hdmi_runसमय_get();
	BUG_ON(r);

	r = hdmi4_पढ़ो_edid(&hdmi.core,  buf, len);

	hdmi_runसमय_put();
	mutex_unlock(&hdmi.lock);

	वापस r;
पूर्ण

अटल व्योम hdmi_start_audio_stream(काष्ठा omap_hdmi *hd)
अणु
	hdmi_wp_audio_enable(&hd->wp, true);
	hdmi4_audio_start(&hd->core, &hd->wp);
पूर्ण

अटल व्योम hdmi_stop_audio_stream(काष्ठा omap_hdmi *hd)
अणु
	hdmi4_audio_stop(&hd->core, &hd->wp);
	hdmi_wp_audio_enable(&hd->wp, false);
पूर्ण

अटल पूर्णांक hdmi_display_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_dss_device *out = &hdmi.output;
	अचिन्हित दीर्घ flags;
	पूर्णांक r = 0;

	DSSDBG("ENTER hdmi_display_enable\n");

	mutex_lock(&hdmi.lock);

	अगर (out->manager == शून्य) अणु
		DSSERR("failed to enable display: no output/manager\n");
		r = -ENODEV;
		जाओ err0;
	पूर्ण

	r = hdmi_घातer_on_full(dssdev);
	अगर (r) अणु
		DSSERR("failed to power on device\n");
		जाओ err0;
	पूर्ण

	अगर (hdmi.audio_configured) अणु
		r = hdmi4_audio_config(&hdmi.core, &hdmi.wp, &hdmi.audio_config,
				       hdmi.cfg.timings.pixelघड़ी);
		अगर (r) अणु
			DSSERR("Error restoring audio configuration: %d", r);
			hdmi.audio_पात_cb(&hdmi.pdev->dev);
			hdmi.audio_configured = false;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&hdmi.audio_playing_lock, flags);
	अगर (hdmi.audio_configured && hdmi.audio_playing)
		hdmi_start_audio_stream(&hdmi);
	hdmi.display_enabled = true;
	spin_unlock_irqrestore(&hdmi.audio_playing_lock, flags);

	mutex_unlock(&hdmi.lock);
	वापस 0;

err0:
	mutex_unlock(&hdmi.lock);
	वापस r;
पूर्ण

अटल व्योम hdmi_display_disable(काष्ठा omap_dss_device *dssdev)
अणु
	अचिन्हित दीर्घ flags;

	DSSDBG("Enter hdmi_display_disable\n");

	mutex_lock(&hdmi.lock);

	spin_lock_irqsave(&hdmi.audio_playing_lock, flags);
	hdmi_stop_audio_stream(&hdmi);
	hdmi.display_enabled = false;
	spin_unlock_irqrestore(&hdmi.audio_playing_lock, flags);

	hdmi_घातer_off_full(dssdev);

	mutex_unlock(&hdmi.lock);
पूर्ण

अटल पूर्णांक hdmi_core_enable(काष्ठा omap_dss_device *dssdev)
अणु
	पूर्णांक r = 0;

	DSSDBG("ENTER omapdss_hdmi_core_enable\n");

	mutex_lock(&hdmi.lock);

	r = hdmi_घातer_on_core(dssdev);
	अगर (r) अणु
		DSSERR("failed to power on device\n");
		जाओ err0;
	पूर्ण

	mutex_unlock(&hdmi.lock);
	वापस 0;

err0:
	mutex_unlock(&hdmi.lock);
	वापस r;
पूर्ण

अटल व्योम hdmi_core_disable(काष्ठा omap_dss_device *dssdev)
अणु
	DSSDBG("Enter omapdss_hdmi_core_disable\n");

	mutex_lock(&hdmi.lock);

	hdmi_घातer_off_core(dssdev);

	mutex_unlock(&hdmi.lock);
पूर्ण

अटल पूर्णांक hdmi_connect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा omap_overlay_manager *mgr;
	पूर्णांक r;

	r = hdmi_init_regulator();
	अगर (r)
		वापस r;

	mgr = omap_dss_get_overlay_manager(dssdev->dispc_channel);
	अगर (!mgr)
		वापस -ENODEV;

	r = dss_mgr_connect(mgr, dssdev);
	अगर (r)
		वापस r;

	r = omapdss_output_set_device(dssdev, dst);
	अगर (r) अणु
		DSSERR("failed to connect output to new device: %s\n",
				dst->name);
		dss_mgr_disconnect(mgr, dssdev);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hdmi_disconnect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	WARN_ON(dst != dssdev->dst);

	अगर (dst != dssdev->dst)
		वापस;

	omapdss_output_unset_device(dssdev);

	अगर (dssdev->manager)
		dss_mgr_disconnect(dssdev->manager, dssdev);
पूर्ण

अटल पूर्णांक hdmi_पढ़ो_edid(काष्ठा omap_dss_device *dssdev,
		u8 *edid, पूर्णांक len)
अणु
	bool need_enable = !hdmi.core_enabled;
	पूर्णांक r;

	अगर (need_enable) अणु
		r = hdmi_core_enable(dssdev);
		अगर (r)
			वापस r;
	पूर्ण

	r = पढ़ो_edid(edid, len);

	अगर (need_enable)
		hdmi_core_disable(dssdev);

	वापस r;
पूर्ण

अटल पूर्णांक hdmi_set_infoframe(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा hdmi_avi_infoframe *avi)
अणु
	hdmi.cfg.infoframe = *avi;
	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_set_hdmi_mode(काष्ठा omap_dss_device *dssdev,
		bool hdmi_mode)
अणु
	hdmi.cfg.hdmi_dvi_mode = hdmi_mode ? HDMI_HDMI : HDMI_DVI;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा omapdss_hdmi_ops hdmi_ops = अणु
	.connect		= hdmi_connect,
	.disconnect		= hdmi_disconnect,

	.enable			= hdmi_display_enable,
	.disable		= hdmi_display_disable,

	.check_timings		= hdmi_display_check_timing,
	.set_timings		= hdmi_display_set_timing,
	.get_timings		= hdmi_display_get_timings,

	.पढ़ो_edid		= hdmi_पढ़ो_edid,
	.set_infoframe		= hdmi_set_infoframe,
	.set_hdmi_mode		= hdmi_set_hdmi_mode,
पूर्ण;

अटल व्योम hdmi_init_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *out = &hdmi.output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_HDMI;
	out->output_type = OMAP_DISPLAY_TYPE_HDMI;
	out->name = "hdmi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_DIGIT;
	out->ops.hdmi = &hdmi_ops;
	out->owner = THIS_MODULE;

	omapdss_रेजिस्टर_output(out);
पूर्ण

अटल व्योम hdmi_uninit_output(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *out = &hdmi.output;

	omapdss_unरेजिस्टर_output(out);
पूर्ण

अटल पूर्णांक hdmi_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *ep;
	पूर्णांक r;

	ep = omapdss_of_get_first_endpoपूर्णांक(node);
	अगर (!ep)
		वापस 0;

	r = hdmi_parse_lanes_of(pdev, ep, &hdmi.phy);
	अगर (r)
		जाओ err;

	of_node_put(ep);
	वापस 0;

err:
	of_node_put(ep);
	वापस r;
पूर्ण

/* Audio callbacks */
अटल पूर्णांक hdmi_audio_startup(काष्ठा device *dev,
			      व्योम (*पात_cb)(काष्ठा device *dev))
अणु
	काष्ठा omap_hdmi *hd = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&hd->lock);

	अगर (!hdmi_mode_has_audio(&hd->cfg) || !hd->display_enabled) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	hd->audio_पात_cb = पात_cb;

out:
	mutex_unlock(&hd->lock);

	वापस ret;
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

	WARN_ON(!hdmi_mode_has_audio(&hd->cfg));

	spin_lock_irqsave(&hd->audio_playing_lock, flags);

	अगर (hd->display_enabled)
		hdmi_start_audio_stream(hd);
	hd->audio_playing = true;

	spin_unlock_irqrestore(&hd->audio_playing_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम hdmi_audio_stop(काष्ठा device *dev)
अणु
	काष्ठा omap_hdmi *hd = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	WARN_ON(!hdmi_mode_has_audio(&hd->cfg));

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
	पूर्णांक ret;

	mutex_lock(&hd->lock);

	अगर (!hdmi_mode_has_audio(&hd->cfg) || !hd->display_enabled) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	ret = hdmi4_audio_config(&hd->core, &hd->wp, dss_audio,
				 hd->cfg.timings.pixelघड़ी);
	अगर (!ret) अणु
		hd->audio_configured = true;
		hd->audio_config = *dss_audio;
	पूर्ण
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

अटल पूर्णांक hdmi_audio_रेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा omap_hdmi_audio_pdata pdata = अणु
		.dev = dev,
		.version = 4,
		.audio_dma_addr = hdmi_wp_get_audio_dma_addr(&hdmi.wp),
		.ops = &hdmi_audio_ops,
	पूर्ण;

	hdmi.audio_pdev = platक्रमm_device_रेजिस्टर_data(
		dev, "omap-hdmi-audio", PLATFORM_DEVID_AUTO,
		&pdata, माप(pdata));

	वापस PTR_ERR_OR_ZERO(hdmi.audio_pdev);
पूर्ण

/* HDMI HW IP initialisation */
अटल पूर्णांक hdmi4_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक r;
	पूर्णांक irq;

	hdmi.pdev = pdev;
	platक्रमm_set_drvdata(pdev, &hdmi);

	mutex_init(&hdmi.lock);
	spin_lock_init(&hdmi.audio_playing_lock);

	अगर (pdev->dev.of_node) अणु
		r = hdmi_probe_of(pdev);
		अगर (r)
			वापस r;
	पूर्ण

	r = hdmi_wp_init(pdev, &hdmi.wp);
	अगर (r)
		वापस r;

	r = hdmi_pll_init(pdev, &hdmi.pll, &hdmi.wp);
	अगर (r)
		वापस r;

	r = hdmi_phy_init(pdev, &hdmi.phy);
	अगर (r)
		जाओ err;

	r = hdmi4_core_init(pdev, &hdmi.core);
	अगर (r)
		जाओ err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		DSSERR("platform_get_irq failed\n");
		r = -ENODEV;
		जाओ err;
	पूर्ण

	r = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
			शून्य, hdmi_irq_handler,
			IRQF_ONESHOT, "OMAP HDMI", &hdmi.wp);
	अगर (r) अणु
		DSSERR("HDMI IRQ request failed\n");
		जाओ err;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	hdmi_init_output(pdev);

	r = hdmi_audio_रेजिस्टर(&pdev->dev);
	अगर (r) अणु
		DSSERR("Registering HDMI audio failed\n");
		hdmi_uninit_output(pdev);
		pm_runसमय_disable(&pdev->dev);
		वापस r;
	पूर्ण

	dss_debugfs_create_file("hdmi", hdmi_dump_regs);

	वापस 0;
err:
	hdmi_pll_uninit(&hdmi.pll);
	वापस r;
पूर्ण

अटल व्योम hdmi4_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (hdmi.audio_pdev)
		platक्रमm_device_unरेजिस्टर(hdmi.audio_pdev);

	hdmi_uninit_output(pdev);

	hdmi_pll_uninit(&hdmi.pll);

	pm_runसमय_disable(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा component_ops hdmi4_component_ops = अणु
	.bind	= hdmi4_bind,
	.unbind	= hdmi4_unbind,
पूर्ण;

अटल पूर्णांक hdmi4_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &hdmi4_component_ops);
पूर्ण

अटल पूर्णांक hdmi4_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &hdmi4_component_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_runसमय_suspend(काष्ठा device *dev)
अणु
	dispc_runसमय_put();

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक r;

	r = dispc_runसमय_get();
	अगर (r < 0)
		वापस r;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hdmi_pm_ops = अणु
	.runसमय_suspend = hdmi_runसमय_suspend,
	.runसमय_resume = hdmi_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hdmi_of_match[] = अणु
	अणु .compatible = "ti,omap4-hdmi", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver omapdss_hdmihw_driver = अणु
	.probe		= hdmi4_probe,
	.हटाओ		= hdmi4_हटाओ,
	.driver         = अणु
		.name   = "omapdss_hdmi",
		.pm	= &hdmi_pm_ops,
		.of_match_table = hdmi_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

पूर्णांक __init hdmi4_init_platक्रमm_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omapdss_hdmihw_driver);
पूर्ण

व्योम hdmi4_uninit_platक्रमm_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omapdss_hdmihw_driver);
पूर्ण
