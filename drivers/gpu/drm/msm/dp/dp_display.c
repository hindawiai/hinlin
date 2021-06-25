<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/component.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/delay.h>

#समावेश "msm_drv.h"
#समावेश "msm_kms.h"
#समावेश "dp_hpd.h"
#समावेश "dp_parser.h"
#समावेश "dp_power.h"
#समावेश "dp_catalog.h"
#समावेश "dp_aux.h"
#समावेश "dp_reg.h"
#समावेश "dp_link.h"
#समावेश "dp_panel.h"
#समावेश "dp_ctrl.h"
#समावेश "dp_display.h"
#समावेश "dp_drm.h"
#समावेश "dp_audio.h"
#समावेश "dp_debug.h"

अटल काष्ठा msm_dp *g_dp_display;
#घोषणा HPD_STRING_SIZE 30

क्रमागत अणु
	ISR_DISCONNECTED,
	ISR_CONNECT_PENDING,
	ISR_CONNECTED,
	ISR_HPD_REPLUG_COUNT,
	ISR_IRQ_HPD_PULSE_COUNT,
	ISR_HPD_LO_GLITH_COUNT,
पूर्ण;

/* event thपढ़ो connection state */
क्रमागत अणु
	ST_DISCONNECTED,
	ST_CONNECT_PENDING,
	ST_CONNECTED,
	ST_DISCONNECT_PENDING,
	ST_DISPLAY_OFF,
	ST_SUSPENDED,
पूर्ण;

क्रमागत अणु
	EV_NO_EVENT,
	/* hpd events */
	EV_HPD_INIT_SETUP,
	EV_HPD_PLUG_INT,
	EV_IRQ_HPD_INT,
	EV_HPD_REPLUG_INT,
	EV_HPD_UNPLUG_INT,
	EV_USER_NOTIFICATION,
	EV_CONNECT_PENDING_TIMEOUT,
	EV_DISCONNECT_PENDING_TIMEOUT,
पूर्ण;

#घोषणा EVENT_TIMEOUT	(HZ/10)	/* 100ms */
#घोषणा DP_EVENT_Q_MAX	8

#घोषणा DP_TIMEOUT_5_SECOND	(5000/EVENT_TIMEOUT)
#घोषणा DP_TIMEOUT_NONE		0

#घोषणा WAIT_FOR_RESUME_TIMEOUT_JIFFIES (HZ / 2)

काष्ठा dp_event अणु
	u32 event_id;
	u32 data;
	u32 delay;
पूर्ण;

काष्ठा dp_display_निजी अणु
	अक्षर *name;
	पूर्णांक irq;

	/* state variables */
	bool core_initialized;
	bool hpd_irq_on;
	bool audio_supported;

	काष्ठा platक्रमm_device *pdev;
	काष्ठा dentry *root;

	काष्ठा dp_usbpd   *usbpd;
	काष्ठा dp_parser  *parser;
	काष्ठा dp_घातer   *घातer;
	काष्ठा dp_catalog *catalog;
	काष्ठा drm_dp_aux *aux;
	काष्ठा dp_link    *link;
	काष्ठा dp_panel   *panel;
	काष्ठा dp_ctrl    *ctrl;
	काष्ठा dp_debug   *debug;

	काष्ठा dp_usbpd_cb usbpd_cb;
	काष्ठा dp_display_mode dp_mode;
	काष्ठा msm_dp dp_display;

	bool encoder_mode_set;

	/* रुको क्रम audio संकेतing */
	काष्ठा completion audio_comp;

	/* event related only access by event thपढ़ो */
	काष्ठा mutex event_mutex;
	रुको_queue_head_t event_q;
	u32 hpd_state;
	u32 event_pndx;
	u32 event_gndx;
	काष्ठा dp_event event_list[DP_EVENT_Q_MAX];
	spinlock_t event_lock;

	काष्ठा dp_audio *audio;
पूर्ण;

अटल स्थिर काष्ठा of_device_id dp_dt_match[] = अणु
	अणु.compatible = "qcom,sc7180-dp"पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक dp_add_event(काष्ठा dp_display_निजी *dp_priv, u32 event,
						u32 data, u32 delay)
अणु
	अचिन्हित दीर्घ flag;
	काष्ठा dp_event *toकरो;
	पूर्णांक pndx;

	spin_lock_irqsave(&dp_priv->event_lock, flag);
	pndx = dp_priv->event_pndx + 1;
	pndx %= DP_EVENT_Q_MAX;
	अगर (pndx == dp_priv->event_gndx) अणु
		pr_err("event_q is full: pndx=%d gndx=%d\n",
			dp_priv->event_pndx, dp_priv->event_gndx);
		spin_unlock_irqrestore(&dp_priv->event_lock, flag);
		वापस -EPERM;
	पूर्ण
	toकरो = &dp_priv->event_list[dp_priv->event_pndx++];
	dp_priv->event_pndx %= DP_EVENT_Q_MAX;
	toकरो->event_id = event;
	toकरो->data = data;
	toकरो->delay = delay;
	wake_up(&dp_priv->event_q);
	spin_unlock_irqrestore(&dp_priv->event_lock, flag);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_del_event(काष्ठा dp_display_निजी *dp_priv, u32 event)
अणु
	अचिन्हित दीर्घ flag;
	काष्ठा dp_event *toकरो;
	u32	gndx;

	spin_lock_irqsave(&dp_priv->event_lock, flag);
	अगर (dp_priv->event_pndx == dp_priv->event_gndx) अणु
		spin_unlock_irqrestore(&dp_priv->event_lock, flag);
		वापस -ENOENT;
	पूर्ण

	gndx = dp_priv->event_gndx;
	जबतक (dp_priv->event_pndx != gndx) अणु
		toकरो = &dp_priv->event_list[gndx];
		अगर (toकरो->event_id == event) अणु
			toकरो->event_id = EV_NO_EVENT;	/* deleted */
			toकरो->delay = 0;
		पूर्ण
		gndx++;
		gndx %= DP_EVENT_Q_MAX;
	पूर्ण
	spin_unlock_irqrestore(&dp_priv->event_lock, flag);

	वापस 0;
पूर्ण

व्योम dp_display_संकेत_audio_start(काष्ठा msm_dp *dp_display)
अणु
	काष्ठा dp_display_निजी *dp;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	reinit_completion(&dp->audio_comp);
पूर्ण

व्योम dp_display_संकेत_audio_complete(काष्ठा msm_dp *dp_display)
अणु
	काष्ठा dp_display_निजी *dp;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	complete_all(&dp->audio_comp);
पूर्ण

अटल पूर्णांक dp_display_bind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_display_निजी *dp;
	काष्ठा drm_device *drm;
	काष्ठा msm_drm_निजी *priv;

	drm = dev_get_drvdata(master);

	dp = container_of(g_dp_display,
			काष्ठा dp_display_निजी, dp_display);
	अगर (!dp) अणु
		DRM_ERROR("DP driver bind failed. Invalid driver data\n");
		वापस -EINVAL;
	पूर्ण

	dp->dp_display.drm_dev = drm;
	priv = drm->dev_निजी;
	priv->dp = &(dp->dp_display);

	rc = dp->parser->parse(dp->parser);
	अगर (rc) अणु
		DRM_ERROR("device tree parsing failed\n");
		जाओ end;
	पूर्ण

	rc = dp_aux_रेजिस्टर(dp->aux);
	अगर (rc) अणु
		DRM_ERROR("DRM DP AUX register failed\n");
		जाओ end;
	पूर्ण

	rc = dp_घातer_client_init(dp->घातer);
	अगर (rc) अणु
		DRM_ERROR("Power client create failed\n");
		जाओ end;
	पूर्ण

	rc = dp_रेजिस्टर_audio_driver(dev, dp->audio);
	अगर (rc)
		DRM_ERROR("Audio registration Dp failed\n");

end:
	वापस rc;
पूर्ण

अटल व्योम dp_display_unbind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	काष्ठा dp_display_निजी *dp;
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;

	dp = container_of(g_dp_display,
			काष्ठा dp_display_निजी, dp_display);
	अगर (!dp) अणु
		DRM_ERROR("Invalid DP driver data\n");
		वापस;
	पूर्ण

	dp_घातer_client_deinit(dp->घातer);
	dp_aux_unरेजिस्टर(dp->aux);
	priv->dp = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops dp_display_comp_ops = अणु
	.bind = dp_display_bind,
	.unbind = dp_display_unbind,
पूर्ण;

अटल bool dp_display_is_ds_bridge(काष्ठा dp_panel *panel)
अणु
	वापस (panel->dpcd[DP_DOWNSTREAMPORT_PRESENT] &
		DP_DWN_STRM_PORT_PRESENT);
पूर्ण

अटल bool dp_display_is_sink_count_zero(काष्ठा dp_display_निजी *dp)
अणु
	वापस dp_display_is_ds_bridge(dp->panel) &&
		(dp->link->sink_count == 0);
पूर्ण

अटल व्योम dp_display_send_hpd_event(काष्ठा msm_dp *dp_display)
अणु
	काष्ठा dp_display_निजी *dp;
	काष्ठा drm_connector *connector;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	connector = dp->dp_display.connector;
	drm_helper_hpd_irq_event(connector->dev);
पूर्ण


अटल व्योम dp_display_set_encoder_mode(काष्ठा dp_display_निजी *dp)
अणु
	काष्ठा msm_drm_निजी *priv = dp->dp_display.drm_dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;

	अगर (!dp->encoder_mode_set && dp->dp_display.encoder &&
				kms->funcs->set_encoder_mode) अणु
		kms->funcs->set_encoder_mode(kms,
				dp->dp_display.encoder, false);

		dp->encoder_mode_set = true;
	पूर्ण
पूर्ण

अटल पूर्णांक dp_display_send_hpd_notअगरication(काष्ठा dp_display_निजी *dp,
					    bool hpd)
अणु
	अगर ((hpd && dp->dp_display.is_connected) ||
			(!hpd && !dp->dp_display.is_connected)) अणु
		DRM_DEBUG_DP("HPD already %s\n", (hpd ? "on" : "off"));
		वापस 0;
	पूर्ण

	/* reset video pattern flag on disconnect */
	अगर (!hpd)
		dp->panel->video_test = false;

	dp->dp_display.is_connected = hpd;

	dp_display_send_hpd_event(&dp->dp_display);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_display_process_hpd_high(काष्ठा dp_display_निजी *dp)
अणु
	पूर्णांक rc = 0;
	काष्ठा edid *edid;

	dp->panel->max_dp_lanes = dp->parser->max_dp_lanes;

	rc = dp_panel_पढ़ो_sink_caps(dp->panel, dp->dp_display.connector);
	अगर (rc)
		जाओ end;

	dp_link_process_request(dp->link);

	edid = dp->panel->edid;

	dp->audio_supported = drm_detect_monitor_audio(edid);
	dp_panel_handle_sink_request(dp->panel);

	dp->dp_display.max_pclk_khz = DP_MAX_PIXEL_CLK_KHZ;
	dp->dp_display.max_dp_lanes = dp->parser->max_dp_lanes;

	dp_link_reset_phy_params_vx_px(dp->link);
	rc = dp_ctrl_on_link(dp->ctrl);
	अगर (rc) अणु
		DRM_ERROR("failed to complete DP link training\n");
		जाओ end;
	पूर्ण

	dp_add_event(dp, EV_USER_NOTIFICATION, true, 0);

end:
	वापस rc;
पूर्ण

अटल व्योम dp_display_host_init(काष्ठा dp_display_निजी *dp, पूर्णांक reset)
अणु
	bool flip = false;

	अगर (dp->core_initialized) अणु
		DRM_DEBUG_DP("DP core already initialized\n");
		वापस;
	पूर्ण

	अगर (dp->usbpd->orientation == ORIENTATION_CC2)
		flip = true;

	dp_display_set_encoder_mode(dp);

	dp_घातer_init(dp->घातer, flip);
	dp_ctrl_host_init(dp->ctrl, flip, reset);
	dp_aux_init(dp->aux);
	dp->core_initialized = true;
पूर्ण

अटल व्योम dp_display_host_deinit(काष्ठा dp_display_निजी *dp)
अणु
	अगर (!dp->core_initialized) अणु
		DRM_DEBUG_DP("DP core not initialized\n");
		वापस;
	पूर्ण

	dp_ctrl_host_deinit(dp->ctrl);
	dp_aux_deinit(dp->aux);
	dp_घातer_deinit(dp->घातer);

	dp->core_initialized = false;
पूर्ण

अटल पूर्णांक dp_display_usbpd_configure_cb(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_display_निजी *dp;

	अगर (!dev) अणु
		DRM_ERROR("invalid dev\n");
		rc = -EINVAL;
		जाओ end;
	पूर्ण

	dp = container_of(g_dp_display,
			काष्ठा dp_display_निजी, dp_display);
	अगर (!dp) अणु
		DRM_ERROR("no driver data found\n");
		rc = -ENODEV;
		जाओ end;
	पूर्ण

	dp_display_host_init(dp, false);

	/*
	 * set sink to normal operation mode -- D0
	 * beक्रमe dpcd पढ़ो
	 */
	dp_link_psm_config(dp->link, &dp->panel->link_info, false);
	rc = dp_display_process_hpd_high(dp);
end:
	वापस rc;
पूर्ण

अटल पूर्णांक dp_display_usbpd_disconnect_cb(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_display_निजी *dp;

	अगर (!dev) अणु
		DRM_ERROR("invalid dev\n");
		rc = -EINVAL;
		वापस rc;
	पूर्ण

	dp = container_of(g_dp_display,
			काष्ठा dp_display_निजी, dp_display);
	अगर (!dp) अणु
		DRM_ERROR("no driver data found\n");
		rc = -ENODEV;
		वापस rc;
	पूर्ण

	dp_add_event(dp, EV_USER_NOTIFICATION, false, 0);

	वापस rc;
पूर्ण

अटल व्योम dp_display_handle_video_request(काष्ठा dp_display_निजी *dp)
अणु
	अगर (dp->link->sink_request & DP_TEST_LINK_VIDEO_PATTERN) अणु
		dp->panel->video_test = true;
		dp_link_send_test_response(dp->link);
	पूर्ण
पूर्ण

अटल पूर्णांक dp_display_handle_port_ststus_changed(काष्ठा dp_display_निजी *dp)
अणु
	पूर्णांक rc = 0;

	अगर (dp_display_is_sink_count_zero(dp)) अणु
		DRM_DEBUG_DP("sink count is zero, nothing to do\n");
		अगर (dp->hpd_state != ST_DISCONNECTED) अणु
			dp->hpd_state = ST_DISCONNECT_PENDING;
			dp_add_event(dp, EV_USER_NOTIFICATION, false, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dp->hpd_state == ST_DISCONNECTED) अणु
			dp->hpd_state = ST_CONNECT_PENDING;
			rc = dp_display_process_hpd_high(dp);
			अगर (rc)
				dp->hpd_state = ST_DISCONNECTED;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dp_display_handle_irq_hpd(काष्ठा dp_display_निजी *dp)
अणु
	u32 sink_request = dp->link->sink_request;

	अगर (dp->hpd_state == ST_DISCONNECTED) अणु
		अगर (sink_request & DP_LINK_STATUS_UPDATED) अणु
			DRM_ERROR("Disconnected, no DP_LINK_STATUS_UPDATED\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dp_ctrl_handle_sink_request(dp->ctrl);

	अगर (sink_request & DP_TEST_LINK_VIDEO_PATTERN)
		dp_display_handle_video_request(dp);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_display_usbpd_attention_cb(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;
	u32 sink_request;
	काष्ठा dp_display_निजी *dp;
	काष्ठा dp_usbpd *hpd;

	अगर (!dev) अणु
		DRM_ERROR("invalid dev\n");
		वापस -EINVAL;
	पूर्ण

	dp = container_of(g_dp_display,
			काष्ठा dp_display_निजी, dp_display);
	अगर (!dp) अणु
		DRM_ERROR("no driver data found\n");
		वापस -ENODEV;
	पूर्ण

	hpd = dp->usbpd;

	/* check क्रम any test request issued by sink */
	rc = dp_link_process_request(dp->link);
	अगर (!rc) अणु
		sink_request = dp->link->sink_request;
		अगर (sink_request & DS_PORT_STATUS_CHANGED)
			rc = dp_display_handle_port_ststus_changed(dp);
		अन्यथा
			rc = dp_display_handle_irq_hpd(dp);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dp_hpd_plug_handle(काष्ठा dp_display_निजी *dp, u32 data)
अणु
	काष्ठा dp_usbpd *hpd = dp->usbpd;
	u32 state;
	u32 tout = DP_TIMEOUT_5_SECOND;
	पूर्णांक ret;

	अगर (!hpd)
		वापस 0;

	mutex_lock(&dp->event_mutex);

	state =  dp->hpd_state;
	अगर (state == ST_DISPLAY_OFF || state == ST_SUSPENDED) अणु
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	अगर (state == ST_CONNECT_PENDING || state == ST_CONNECTED) अणु
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	अगर (state == ST_DISCONNECT_PENDING) अणु
		/* रुको until ST_DISCONNECTED */
		dp_add_event(dp, EV_HPD_PLUG_INT, 0, 1); /* delay = 1 */
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	dp->hpd_state = ST_CONNECT_PENDING;

	hpd->hpd_high = 1;

	ret = dp_display_usbpd_configure_cb(&dp->pdev->dev);
	अगर (ret) अणु	/* link train failed */
		hpd->hpd_high = 0;
		dp->hpd_state = ST_DISCONNECTED;

		अगर (ret == -ECONNRESET) अणु /* cable unplugged */
			dp->core_initialized = false;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* start sentinel checking in हाल of missing uevent */
		dp_add_event(dp, EV_CONNECT_PENDING_TIMEOUT, 0, tout);
	पूर्ण

	mutex_unlock(&dp->event_mutex);

	/* uevent will complete connection part */
	वापस 0;
पूर्ण;

अटल पूर्णांक dp_display_enable(काष्ठा dp_display_निजी *dp, u32 data);
अटल पूर्णांक dp_display_disable(काष्ठा dp_display_निजी *dp, u32 data);

अटल पूर्णांक dp_connect_pending_समयout(काष्ठा dp_display_निजी *dp, u32 data)
अणु
	u32 state;

	mutex_lock(&dp->event_mutex);

	state = dp->hpd_state;
	अगर (state == ST_CONNECT_PENDING)
		dp->hpd_state = ST_CONNECTED;

	mutex_unlock(&dp->event_mutex);

	वापस 0;
पूर्ण

अटल व्योम dp_display_handle_plugged_change(काष्ठा msm_dp *dp_display,
		bool plugged)
अणु
	काष्ठा dp_display_निजी *dp;

	dp = container_of(dp_display,
			काष्ठा dp_display_निजी, dp_display);

	/* notअगरy audio subप्रणाली only अगर sink supports audio */
	अगर (dp_display->plugged_cb && dp_display->codec_dev &&
			dp->audio_supported)
		dp_display->plugged_cb(dp_display->codec_dev, plugged);
पूर्ण

अटल पूर्णांक dp_hpd_unplug_handle(काष्ठा dp_display_निजी *dp, u32 data)
अणु
	काष्ठा dp_usbpd *hpd = dp->usbpd;
	u32 state;

	अगर (!hpd)
		वापस 0;

	mutex_lock(&dp->event_mutex);

	state = dp->hpd_state;
	अगर (state == ST_DISCONNECT_PENDING || state == ST_DISCONNECTED) अणु
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	अगर (state == ST_CONNECT_PENDING) अणु
		/* रुको until CONNECTED */
		dp_add_event(dp, EV_HPD_UNPLUG_INT, 0, 1); /* delay = 1 */
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	dp->hpd_state = ST_DISCONNECT_PENDING;

	/* disable HPD plug पूर्णांकerrupt until disconnect is करोne */
	dp_catalog_hpd_config_पूर्णांकr(dp->catalog, DP_DP_HPD_PLUG_INT_MASK
				| DP_DP_IRQ_HPD_INT_MASK, false);

	hpd->hpd_high = 0;

	/*
	 * We करोn't need separate work क्रम disconnect as
	 * connect/attention पूर्णांकerrupts are disabled
	 */
	dp_display_usbpd_disconnect_cb(&dp->pdev->dev);

	/* start sentinel checking in हाल of missing uevent */
	dp_add_event(dp, EV_DISCONNECT_PENDING_TIMEOUT, 0, DP_TIMEOUT_5_SECOND);

	/* संकेत the disconnect event early to ensure proper tearकरोwn */
	dp_display_handle_plugged_change(g_dp_display, false);

	dp_catalog_hpd_config_पूर्णांकr(dp->catalog, DP_DP_HPD_PLUG_INT_MASK |
					DP_DP_IRQ_HPD_INT_MASK, true);

	/* uevent will complete disconnection part */
	mutex_unlock(&dp->event_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dp_disconnect_pending_समयout(काष्ठा dp_display_निजी *dp, u32 data)
अणु
	u32 state;

	mutex_lock(&dp->event_mutex);

	state =  dp->hpd_state;
	अगर (state == ST_DISCONNECT_PENDING)
		dp->hpd_state = ST_DISCONNECTED;

	mutex_unlock(&dp->event_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_irq_hpd_handle(काष्ठा dp_display_निजी *dp, u32 data)
अणु
	u32 state;
	पूर्णांक ret;

	mutex_lock(&dp->event_mutex);

	/* irq_hpd can happen at either connected or disconnected state */
	state =  dp->hpd_state;
	अगर (state == ST_DISPLAY_OFF) अणु
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	अगर (state == ST_CONNECT_PENDING) अणु
		/* रुको until ST_CONNECTED */
		dp_add_event(dp, EV_IRQ_HPD_INT, 0, 1); /* delay = 1 */
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	अगर (state == ST_CONNECT_PENDING || state == ST_DISCONNECT_PENDING) अणु
		/* रुको until ST_CONNECTED */
		dp_add_event(dp, EV_IRQ_HPD_INT, 0, 1); /* delay = 1 */
		mutex_unlock(&dp->event_mutex);
		वापस 0;
	पूर्ण

	ret = dp_display_usbpd_attention_cb(&dp->pdev->dev);
	अगर (ret == -ECONNRESET) अणु /* cable unplugged */
		dp->core_initialized = false;
	पूर्ण

	mutex_unlock(&dp->event_mutex);

	वापस 0;
पूर्ण

अटल व्योम dp_display_deinit_sub_modules(काष्ठा dp_display_निजी *dp)
अणु
	dp_debug_put(dp->debug);
	dp_ctrl_put(dp->ctrl);
	dp_panel_put(dp->panel);
	dp_aux_put(dp->aux);
	dp_audio_put(dp->audio);
पूर्ण

अटल पूर्णांक dp_init_sub_modules(काष्ठा dp_display_निजी *dp)
अणु
	पूर्णांक rc = 0;
	काष्ठा device *dev = &dp->pdev->dev;
	काष्ठा dp_usbpd_cb *cb = &dp->usbpd_cb;
	काष्ठा dp_panel_in panel_in = अणु
		.dev = dev,
	पूर्ण;

	/* Callback APIs used क्रम cable status change event */
	cb->configure  = dp_display_usbpd_configure_cb;
	cb->disconnect = dp_display_usbpd_disconnect_cb;
	cb->attention  = dp_display_usbpd_attention_cb;

	dp->usbpd = dp_hpd_get(dev, cb);
	अगर (IS_ERR(dp->usbpd)) अणु
		rc = PTR_ERR(dp->usbpd);
		DRM_ERROR("failed to initialize hpd, rc = %d\n", rc);
		dp->usbpd = शून्य;
		जाओ error;
	पूर्ण

	dp->parser = dp_parser_get(dp->pdev);
	अगर (IS_ERR(dp->parser)) अणु
		rc = PTR_ERR(dp->parser);
		DRM_ERROR("failed to initialize parser, rc = %d\n", rc);
		dp->parser = शून्य;
		जाओ error;
	पूर्ण

	dp->catalog = dp_catalog_get(dev, &dp->parser->io);
	अगर (IS_ERR(dp->catalog)) अणु
		rc = PTR_ERR(dp->catalog);
		DRM_ERROR("failed to initialize catalog, rc = %d\n", rc);
		dp->catalog = शून्य;
		जाओ error;
	पूर्ण

	dp->घातer = dp_घातer_get(dev, dp->parser);
	अगर (IS_ERR(dp->घातer)) अणु
		rc = PTR_ERR(dp->घातer);
		DRM_ERROR("failed to initialize power, rc = %d\n", rc);
		dp->घातer = शून्य;
		जाओ error;
	पूर्ण

	dp->aux = dp_aux_get(dev, dp->catalog);
	अगर (IS_ERR(dp->aux)) अणु
		rc = PTR_ERR(dp->aux);
		DRM_ERROR("failed to initialize aux, rc = %d\n", rc);
		dp->aux = शून्य;
		जाओ error;
	पूर्ण

	dp->link = dp_link_get(dev, dp->aux);
	अगर (IS_ERR(dp->link)) अणु
		rc = PTR_ERR(dp->link);
		DRM_ERROR("failed to initialize link, rc = %d\n", rc);
		dp->link = शून्य;
		जाओ error_link;
	पूर्ण

	panel_in.aux = dp->aux;
	panel_in.catalog = dp->catalog;
	panel_in.link = dp->link;

	dp->panel = dp_panel_get(&panel_in);
	अगर (IS_ERR(dp->panel)) अणु
		rc = PTR_ERR(dp->panel);
		DRM_ERROR("failed to initialize panel, rc = %d\n", rc);
		dp->panel = शून्य;
		जाओ error_link;
	पूर्ण

	dp->ctrl = dp_ctrl_get(dev, dp->link, dp->panel, dp->aux,
			       dp->घातer, dp->catalog, dp->parser);
	अगर (IS_ERR(dp->ctrl)) अणु
		rc = PTR_ERR(dp->ctrl);
		DRM_ERROR("failed to initialize ctrl, rc = %d\n", rc);
		dp->ctrl = शून्य;
		जाओ error_ctrl;
	पूर्ण

	dp->audio = dp_audio_get(dp->pdev, dp->panel, dp->catalog);
	अगर (IS_ERR(dp->audio)) अणु
		rc = PTR_ERR(dp->audio);
		pr_err("failed to initialize audio, rc = %d\n", rc);
		dp->audio = शून्य;
		जाओ error_audio;
	पूर्ण

	वापस rc;

error_audio:
	dp_ctrl_put(dp->ctrl);
error_ctrl:
	dp_panel_put(dp->panel);
error_link:
	dp_aux_put(dp->aux);
error:
	वापस rc;
पूर्ण

अटल पूर्णांक dp_display_set_mode(काष्ठा msm_dp *dp_display,
			       काष्ठा dp_display_mode *mode)
अणु
	काष्ठा dp_display_निजी *dp;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	dp->panel->dp_mode.drm_mode = mode->drm_mode;
	dp->panel->dp_mode.bpp = mode->bpp;
	dp->panel->dp_mode.capabilities = mode->capabilities;
	dp_panel_init_panel_info(dp->panel);
	वापस 0;
पूर्ण

अटल पूर्णांक dp_display_prepare(काष्ठा msm_dp *dp)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dp_display_enable(काष्ठा dp_display_निजी *dp, u32 data)
अणु
	पूर्णांक rc = 0;
	काष्ठा msm_dp *dp_display;

	dp_display = g_dp_display;

	अगर (dp_display->घातer_on) अणु
		DRM_DEBUG_DP("Link already setup, return\n");
		वापस 0;
	पूर्ण

	rc = dp_ctrl_on_stream(dp->ctrl);
	अगर (!rc)
		dp_display->घातer_on = true;

	वापस rc;
पूर्ण

अटल पूर्णांक dp_display_post_enable(काष्ठा msm_dp *dp_display)
अणु
	काष्ठा dp_display_निजी *dp;
	u32 rate;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	rate = dp->link->link_params.rate;

	अगर (dp->audio_supported) अणु
		dp->audio->bw_code = drm_dp_link_rate_to_bw_code(rate);
		dp->audio->lane_count = dp->link->link_params.num_lanes;
	पूर्ण

	/* संकेत the connect event late to synchronize video and display */
	dp_display_handle_plugged_change(dp_display, true);
	वापस 0;
पूर्ण

अटल पूर्णांक dp_display_disable(काष्ठा dp_display_निजी *dp, u32 data)
अणु
	काष्ठा msm_dp *dp_display;

	dp_display = g_dp_display;

	अगर (!dp_display->घातer_on)
		वापस 0;

	/* रुको only अगर audio was enabled */
	अगर (dp_display->audio_enabled) अणु
		/* संकेत the disconnect event */
		dp_display_handle_plugged_change(dp_display, false);
		अगर (!रुको_क्रम_completion_समयout(&dp->audio_comp,
				HZ * 5))
			DRM_ERROR("audio comp timeout\n");
	पूर्ण

	dp_display->audio_enabled = false;

	dp_ctrl_off(dp->ctrl);

	dp->core_initialized = false;

	dp_display->घातer_on = false;

	वापस 0;
पूर्ण

अटल पूर्णांक dp_display_unprepare(काष्ठा msm_dp *dp)
अणु
	वापस 0;
पूर्ण

पूर्णांक dp_display_set_plugged_cb(काष्ठा msm_dp *dp_display,
		hdmi_codec_plugged_cb fn, काष्ठा device *codec_dev)
अणु
	bool plugged;

	dp_display->plugged_cb = fn;
	dp_display->codec_dev = codec_dev;
	plugged = dp_display->is_connected;
	dp_display_handle_plugged_change(dp_display, plugged);

	वापस 0;
पूर्ण

पूर्णांक dp_display_validate_mode(काष्ठा msm_dp *dp, u32 mode_pclk_khz)
अणु
	स्थिर u32 num_components = 3, शेष_bpp = 24;
	काष्ठा dp_display_निजी *dp_display;
	काष्ठा dp_link_info *link_info;
	u32 mode_rate_khz = 0, supported_rate_khz = 0, mode_bpp = 0;

	अगर (!dp || !mode_pclk_khz || !dp->connector) अणु
		DRM_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);
	link_info = &dp_display->panel->link_info;

	mode_bpp = dp->connector->display_info.bpc * num_components;
	अगर (!mode_bpp)
		mode_bpp = शेष_bpp;

	mode_bpp = dp_panel_get_mode_bpp(dp_display->panel,
			mode_bpp, mode_pclk_khz);

	mode_rate_khz = mode_pclk_khz * mode_bpp;
	supported_rate_khz = link_info->num_lanes * link_info->rate * 8;

	अगर (mode_rate_khz > supported_rate_khz)
		वापस MODE_BAD;

	वापस MODE_OK;
पूर्ण

पूर्णांक dp_display_get_modes(काष्ठा msm_dp *dp,
				काष्ठा dp_display_mode *dp_mode)
अणु
	काष्ठा dp_display_निजी *dp_display;
	पूर्णांक ret = 0;

	अगर (!dp) अणु
		DRM_ERROR("invalid params\n");
		वापस 0;
	पूर्ण

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);

	ret = dp_panel_get_modes(dp_display->panel,
		dp->connector, dp_mode);
	अगर (dp_mode->drm_mode.घड़ी)
		dp->max_pclk_khz = dp_mode->drm_mode.घड़ी;
	वापस ret;
पूर्ण

bool dp_display_check_video_test(काष्ठा msm_dp *dp)
अणु
	काष्ठा dp_display_निजी *dp_display;

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);

	वापस dp_display->panel->video_test;
पूर्ण

पूर्णांक dp_display_get_test_bpp(काष्ठा msm_dp *dp)
अणु
	काष्ठा dp_display_निजी *dp_display;

	अगर (!dp) अणु
		DRM_ERROR("invalid params\n");
		वापस 0;
	पूर्ण

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);

	वापस dp_link_bit_depth_to_bpp(
		dp_display->link->test_video.test_bit_depth);
पूर्ण

अटल व्योम dp_display_config_hpd(काष्ठा dp_display_निजी *dp)
अणु

	dp_display_host_init(dp, true);
	dp_catalog_ctrl_hpd_config(dp->catalog);

	/* Enable पूर्णांकerrupt first समय
	 * we are leaving dp घड़ीs on during disconnect
	 * and never disable पूर्णांकerrupt
	 */
	enable_irq(dp->irq);
पूर्ण

अटल पूर्णांक hpd_event_thपढ़ो(व्योम *data)
अणु
	काष्ठा dp_display_निजी *dp_priv;
	अचिन्हित दीर्घ flag;
	काष्ठा dp_event *toकरो;
	पूर्णांक समयout_mode = 0;

	dp_priv = (काष्ठा dp_display_निजी *)data;

	जबतक (1) अणु
		अगर (समयout_mode) अणु
			रुको_event_समयout(dp_priv->event_q,
				(dp_priv->event_pndx == dp_priv->event_gndx),
						EVENT_TIMEOUT);
		पूर्ण अन्यथा अणु
			रुको_event_पूर्णांकerruptible(dp_priv->event_q,
				(dp_priv->event_pndx != dp_priv->event_gndx));
		पूर्ण
		spin_lock_irqsave(&dp_priv->event_lock, flag);
		toकरो = &dp_priv->event_list[dp_priv->event_gndx];
		अगर (toकरो->delay) अणु
			काष्ठा dp_event *toकरो_next;

			dp_priv->event_gndx++;
			dp_priv->event_gndx %= DP_EVENT_Q_MAX;

			/* re enter delay event पूर्णांकo q */
			toकरो_next = &dp_priv->event_list[dp_priv->event_pndx++];
			dp_priv->event_pndx %= DP_EVENT_Q_MAX;
			toकरो_next->event_id = toकरो->event_id;
			toकरो_next->data = toकरो->data;
			toकरो_next->delay = toकरो->delay - 1;

			/* clean up older event */
			toकरो->event_id = EV_NO_EVENT;
			toकरो->delay = 0;

			/* चयन to समयout mode */
			समयout_mode = 1;
			spin_unlock_irqrestore(&dp_priv->event_lock, flag);
			जारी;
		पूर्ण

		/* समयout with no events in q */
		अगर (dp_priv->event_pndx == dp_priv->event_gndx) अणु
			spin_unlock_irqrestore(&dp_priv->event_lock, flag);
			जारी;
		पूर्ण

		dp_priv->event_gndx++;
		dp_priv->event_gndx %= DP_EVENT_Q_MAX;
		समयout_mode = 0;
		spin_unlock_irqrestore(&dp_priv->event_lock, flag);

		चयन (toकरो->event_id) अणु
		हाल EV_HPD_INIT_SETUP:
			dp_display_config_hpd(dp_priv);
			अवरोध;
		हाल EV_HPD_PLUG_INT:
			dp_hpd_plug_handle(dp_priv, toकरो->data);
			अवरोध;
		हाल EV_HPD_UNPLUG_INT:
			dp_hpd_unplug_handle(dp_priv, toकरो->data);
			अवरोध;
		हाल EV_IRQ_HPD_INT:
			dp_irq_hpd_handle(dp_priv, toकरो->data);
			अवरोध;
		हाल EV_HPD_REPLUG_INT:
			/* करो nothing */
			अवरोध;
		हाल EV_USER_NOTIFICATION:
			dp_display_send_hpd_notअगरication(dp_priv,
						toकरो->data);
			अवरोध;
		हाल EV_CONNECT_PENDING_TIMEOUT:
			dp_connect_pending_समयout(dp_priv,
						toकरो->data);
			अवरोध;
		हाल EV_DISCONNECT_PENDING_TIMEOUT:
			dp_disconnect_pending_समयout(dp_priv,
						toकरो->data);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dp_hpd_event_setup(काष्ठा dp_display_निजी *dp_priv)
अणु
	init_रुकोqueue_head(&dp_priv->event_q);
	spin_lock_init(&dp_priv->event_lock);

	kthपढ़ो_run(hpd_event_thपढ़ो, dp_priv, "dp_hpd_handler");
पूर्ण

अटल irqवापस_t dp_display_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dp_display_निजी *dp = dev_id;
	irqवापस_t ret = IRQ_HANDLED;
	u32 hpd_isr_status;

	अगर (!dp) अणु
		DRM_ERROR("invalid data\n");
		वापस IRQ_NONE;
	पूर्ण

	hpd_isr_status = dp_catalog_hpd_get_पूर्णांकr_status(dp->catalog);

	अगर (hpd_isr_status & 0x0F) अणु
		/* hpd related पूर्णांकerrupts */
		अगर (hpd_isr_status & DP_DP_HPD_PLUG_INT_MASK ||
			hpd_isr_status & DP_DP_HPD_REPLUG_INT_MASK) अणु
			dp_add_event(dp, EV_HPD_PLUG_INT, 0, 0);
		पूर्ण

		अगर (hpd_isr_status & DP_DP_IRQ_HPD_INT_MASK) अणु
			/* stop sentinel connect pending checking */
			dp_del_event(dp, EV_CONNECT_PENDING_TIMEOUT);
			dp_add_event(dp, EV_IRQ_HPD_INT, 0, 0);
		पूर्ण

		अगर (hpd_isr_status & DP_DP_HPD_REPLUG_INT_MASK)
			dp_add_event(dp, EV_HPD_REPLUG_INT, 0, 0);

		अगर (hpd_isr_status & DP_DP_HPD_UNPLUG_INT_MASK)
			dp_add_event(dp, EV_HPD_UNPLUG_INT, 0, 0);
	पूर्ण

	/* DP controller isr */
	dp_ctrl_isr(dp->ctrl);

	/* DP aux isr */
	dp_aux_isr(dp->aux);

	वापस ret;
पूर्ण

पूर्णांक dp_display_request_irq(काष्ठा msm_dp *dp_display)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_display_निजी *dp;

	अगर (!dp_display) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	dp->irq = irq_of_parse_and_map(dp->pdev->dev.of_node, 0);
	अगर (dp->irq < 0) अणु
		rc = dp->irq;
		DRM_ERROR("failed to get irq: %d\n", rc);
		वापस rc;
	पूर्ण

	rc = devm_request_irq(&dp->pdev->dev, dp->irq,
			dp_display_irq_handler,
			IRQF_TRIGGER_HIGH, "dp_display_isr", dp);
	अगर (rc < 0) अणु
		DRM_ERROR("failed to request IRQ%u: %d\n",
				dp->irq, rc);
		वापस rc;
	पूर्ण
	disable_irq(dp->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_display_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_display_निजी *dp;

	अगर (!pdev || !pdev->dev.of_node) अणु
		DRM_ERROR("pdev not found\n");
		वापस -ENODEV;
	पूर्ण

	dp = devm_kzalloc(&pdev->dev, माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	dp->pdev = pdev;
	dp->name = "drm_dp";

	rc = dp_init_sub_modules(dp);
	अगर (rc) अणु
		DRM_ERROR("init sub module failed\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	mutex_init(&dp->event_mutex);
	g_dp_display = &dp->dp_display;

	/* Store DP audio handle inside DP display */
	g_dp_display->dp_audio = dp->audio;

	init_completion(&dp->audio_comp);

	platक्रमm_set_drvdata(pdev, g_dp_display);

	rc = component_add(&pdev->dev, &dp_display_comp_ops);
	अगर (rc) अणु
		DRM_ERROR("component add failed, rc=%d\n", rc);
		dp_display_deinit_sub_modules(dp);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dp_display_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dp_display_निजी *dp;

	dp = container_of(g_dp_display,
			काष्ठा dp_display_निजी, dp_display);

	dp_display_deinit_sub_modules(dp);

	component_del(&pdev->dev, &dp_display_comp_ops);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा msm_dp *dp_display = platक्रमm_get_drvdata(pdev);
	काष्ठा dp_display_निजी *dp;
	u32 status;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	mutex_lock(&dp->event_mutex);

	/* start from disconnected state */
	dp->hpd_state = ST_DISCONNECTED;

	/* turn on dp ctrl/phy */
	dp_display_host_init(dp, true);

	dp_catalog_ctrl_hpd_config(dp->catalog);

	status = dp_catalog_link_is_connected(dp->catalog);

	/*
	 * can not declared display is connected unless
	 * HDMI cable is plugged in and sink_count of
	 * करोngle become 1
	 */
	अगर (status && dp->link->sink_count)
		dp->dp_display.is_connected = true;
	अन्यथा
		dp->dp_display.is_connected = false;

	mutex_unlock(&dp->event_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा msm_dp *dp_display = platक्रमm_get_drvdata(pdev);
	काष्ठा dp_display_निजी *dp;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	mutex_lock(&dp->event_mutex);

	अगर (dp->core_initialized == true)
		dp_display_host_deinit(dp);

	dp->hpd_state = ST_SUSPENDED;

	/* host_init will be called at pm_resume */
	dp->core_initialized = false;

	mutex_unlock(&dp->event_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_pm_prepare(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम dp_pm_complete(काष्ठा device *dev)
अणु

पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dp_pm_ops = अणु
	.suspend = dp_pm_suspend,
	.resume =  dp_pm_resume,
	.prepare = dp_pm_prepare,
	.complete = dp_pm_complete,
पूर्ण;

अटल काष्ठा platक्रमm_driver dp_display_driver = अणु
	.probe  = dp_display_probe,
	.हटाओ = dp_display_हटाओ,
	.driver = अणु
		.name = "msm-dp-display",
		.of_match_table = dp_dt_match,
		.suppress_bind_attrs = true,
		.pm = &dp_pm_ops,
	पूर्ण,
पूर्ण;

पूर्णांक __init msm_dp_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&dp_display_driver);
	अगर (ret)
		DRM_ERROR("Dp display driver register failed");

	वापस ret;
पूर्ण

व्योम __निकास msm_dp_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dp_display_driver);
पूर्ण

व्योम msm_dp_irq_postinstall(काष्ठा msm_dp *dp_display)
अणु
	काष्ठा dp_display_निजी *dp;

	अगर (!dp_display)
		वापस;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);

	dp_hpd_event_setup(dp);

	dp_add_event(dp, EV_HPD_INIT_SETUP, 0, 100);
पूर्ण

व्योम msm_dp_debugfs_init(काष्ठा msm_dp *dp_display, काष्ठा drm_minor *minor)
अणु
	काष्ठा dp_display_निजी *dp;
	काष्ठा device *dev;
	पूर्णांक rc;

	dp = container_of(dp_display, काष्ठा dp_display_निजी, dp_display);
	dev = &dp->pdev->dev;

	dp->debug = dp_debug_get(dev, dp->panel, dp->usbpd,
					dp->link, &dp->dp_display.connector,
					minor);
	अगर (IS_ERR(dp->debug)) अणु
		rc = PTR_ERR(dp->debug);
		DRM_ERROR("failed to initialize debug, rc = %d\n", rc);
		dp->debug = शून्य;
	पूर्ण
पूर्ण

पूर्णांक msm_dp_modeset_init(काष्ठा msm_dp *dp_display, काष्ठा drm_device *dev,
			काष्ठा drm_encoder *encoder)
अणु
	काष्ठा msm_drm_निजी *priv;
	पूर्णांक ret;

	अगर (WARN_ON(!encoder) || WARN_ON(!dp_display) || WARN_ON(!dev))
		वापस -EINVAL;

	priv = dev->dev_निजी;
	dp_display->drm_dev = dev;

	ret = dp_display_request_irq(dp_display);
	अगर (ret) अणु
		DRM_ERROR("request_irq failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	dp_display->encoder = encoder;

	dp_display->connector = dp_drm_connector_init(dp_display);
	अगर (IS_ERR(dp_display->connector)) अणु
		ret = PTR_ERR(dp_display->connector);
		DRM_DEV_ERROR(dev->dev,
			"failed to create dp connector: %d\n", ret);
		dp_display->connector = शून्य;
		वापस ret;
	पूर्ण

	priv->connectors[priv->num_connectors++] = dp_display->connector;
	वापस 0;
पूर्ण

पूर्णांक msm_dp_display_enable(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_display_निजी *dp_display;
	u32 state;

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);
	अगर (!dp_display->dp_mode.drm_mode.घड़ी) अणु
		DRM_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dp_display->event_mutex);

	/* stop sentinel checking */
	dp_del_event(dp_display, EV_CONNECT_PENDING_TIMEOUT);

	rc = dp_display_set_mode(dp, &dp_display->dp_mode);
	अगर (rc) अणु
		DRM_ERROR("Failed to perform a mode set, rc=%d\n", rc);
		mutex_unlock(&dp_display->event_mutex);
		वापस rc;
	पूर्ण

	rc = dp_display_prepare(dp);
	अगर (rc) अणु
		DRM_ERROR("DP display prepare failed, rc=%d\n", rc);
		mutex_unlock(&dp_display->event_mutex);
		वापस rc;
	पूर्ण

	state =  dp_display->hpd_state;

	अगर (state == ST_DISPLAY_OFF)
		dp_display_host_init(dp_display, true);

	dp_display_enable(dp_display, 0);

	rc = dp_display_post_enable(dp);
	अगर (rc) अणु
		DRM_ERROR("DP display post enable failed, rc=%d\n", rc);
		dp_display_disable(dp_display, 0);
		dp_display_unprepare(dp);
	पूर्ण

	/* manual kick off plug event to train link */
	अगर (state == ST_DISPLAY_OFF)
		dp_add_event(dp_display, EV_IRQ_HPD_INT, 0, 0);

	/* completed connection */
	dp_display->hpd_state = ST_CONNECTED;

	mutex_unlock(&dp_display->event_mutex);

	वापस rc;
पूर्ण

पूर्णांक msm_dp_display_pre_disable(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dp_display_निजी *dp_display;

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);

	dp_ctrl_push_idle(dp_display->ctrl);

	वापस 0;
पूर्ण

पूर्णांक msm_dp_display_disable(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक rc = 0;
	u32 state;
	काष्ठा dp_display_निजी *dp_display;

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);

	mutex_lock(&dp_display->event_mutex);

	/* stop sentinel checking */
	dp_del_event(dp_display, EV_DISCONNECT_PENDING_TIMEOUT);

	dp_display_disable(dp_display, 0);

	rc = dp_display_unprepare(dp);
	अगर (rc)
		DRM_ERROR("DP display unprepare failed, rc=%d\n", rc);

	state =  dp_display->hpd_state;
	अगर (state == ST_DISCONNECT_PENDING) अणु
		/* completed disconnection */
		dp_display->hpd_state = ST_DISCONNECTED;
	पूर्ण अन्यथा अणु
		dp_display->hpd_state = ST_DISPLAY_OFF;
	पूर्ण

	mutex_unlock(&dp_display->event_mutex);
	वापस rc;
पूर्ण

व्योम msm_dp_display_mode_set(काष्ठा msm_dp *dp, काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा dp_display_निजी *dp_display;

	dp_display = container_of(dp, काष्ठा dp_display_निजी, dp_display);

	स_रखो(&dp_display->dp_mode, 0x0, माप(काष्ठा dp_display_mode));

	अगर (dp_display_check_video_test(dp))
		dp_display->dp_mode.bpp = dp_display_get_test_bpp(dp);
	अन्यथा /* Default num_components per pixel = 3 */
		dp_display->dp_mode.bpp = dp->connector->display_info.bpc * 3;

	अगर (!dp_display->dp_mode.bpp)
		dp_display->dp_mode.bpp = 24; /* Default bpp */

	drm_mode_copy(&dp_display->dp_mode.drm_mode, adjusted_mode);

	dp_display->dp_mode.v_active_low =
		!!(dp_display->dp_mode.drm_mode.flags & DRM_MODE_FLAG_NVSYNC);

	dp_display->dp_mode.h_active_low =
		!!(dp_display->dp_mode.drm_mode.flags & DRM_MODE_FLAG_NHSYNC);
पूर्ण
