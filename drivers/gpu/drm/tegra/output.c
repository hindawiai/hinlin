<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "drm.h"
#समावेश "dc.h"

#समावेश <media/cec-notअगरier.h>

पूर्णांक tegra_output_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	काष्ठा edid *edid = शून्य;
	पूर्णांक err = 0;

	/*
	 * If the panel provides one or more modes, use them exclusively and
	 * ignore any other means of obtaining a mode.
	 */
	अगर (output->panel) अणु
		err = drm_panel_get_modes(output->panel, connector);
		अगर (err > 0)
			वापस err;
	पूर्ण

	अगर (output->edid)
		edid = kmemdup(output->edid, माप(*edid), GFP_KERNEL);
	अन्यथा अगर (output->ddc)
		edid = drm_get_edid(connector, output->ddc);

	cec_notअगरier_set_phys_addr_from_edid(output->cec, edid);
	drm_connector_update_edid_property(connector, edid);

	अगर (edid) अणु
		err = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण

	वापस err;
पूर्ण

क्रमागत drm_connector_status
tegra_output_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);
	क्रमागत drm_connector_status status = connector_status_unknown;

	अगर (output->hpd_gpio) अणु
		अगर (gpiod_get_value(output->hpd_gpio) == 0)
			status = connector_status_disconnected;
		अन्यथा
			status = connector_status_connected;
	पूर्ण अन्यथा अणु
		अगर (!output->panel)
			status = connector_status_disconnected;
		अन्यथा
			status = connector_status_connected;
	पूर्ण

	अगर (status != connector_status_connected)
		cec_notअगरier_phys_addr_invalidate(output->cec);

	वापस status;
पूर्ण

व्योम tegra_output_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा tegra_output *output = connector_to_output(connector);

	अगर (output->cec)
		cec_notअगरier_conn_unरेजिस्टर(output->cec);

	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल irqवापस_t hpd_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_output *output = data;

	अगर (output->connector.dev)
		drm_helper_hpd_irq_event(output->connector.dev);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक tegra_output_probe(काष्ठा tegra_output *output)
अणु
	काष्ठा device_node *ddc, *panel;
	अचिन्हित दीर्घ flags;
	पूर्णांक err, size;

	अगर (!output->of_node)
		output->of_node = output->dev->of_node;

	err = drm_of_find_panel_or_bridge(output->of_node, -1, -1,
					  &output->panel, &output->bridge);
	अगर (err && err != -ENODEV)
		वापस err;

	panel = of_parse_phandle(output->of_node, "nvidia,panel", 0);
	अगर (panel) अणु
		/*
		 * Don't mix nvidia,panel phandle with the graph in a
		 * device-tree.
		 */
		WARN_ON(output->panel || output->bridge);

		output->panel = of_drm_find_panel(panel);
		of_node_put(panel);

		अगर (IS_ERR(output->panel))
			वापस PTR_ERR(output->panel);
	पूर्ण

	output->edid = of_get_property(output->of_node, "nvidia,edid", &size);

	ddc = of_parse_phandle(output->of_node, "nvidia,ddc-i2c-bus", 0);
	अगर (ddc) अणु
		output->ddc = of_get_i2c_adapter_by_node(ddc);
		of_node_put(ddc);

		अगर (!output->ddc) अणु
			err = -EPROBE_DEFER;
			वापस err;
		पूर्ण
	पूर्ण

	output->hpd_gpio = devm_gpiod_get_from_of_node(output->dev,
						       output->of_node,
						       "nvidia,hpd-gpio", 0,
						       GPIOD_IN,
						       "HDMI hotplug detect");
	अगर (IS_ERR(output->hpd_gpio)) अणु
		अगर (PTR_ERR(output->hpd_gpio) != -ENOENT)
			वापस PTR_ERR(output->hpd_gpio);

		output->hpd_gpio = शून्य;
	पूर्ण

	अगर (output->hpd_gpio) अणु
		err = gpiod_to_irq(output->hpd_gpio);
		अगर (err < 0) अणु
			dev_err(output->dev, "gpiod_to_irq(): %d\n", err);
			वापस err;
		पूर्ण

		output->hpd_irq = err;

		flags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			IRQF_ONESHOT;

		err = request_thपढ़ोed_irq(output->hpd_irq, शून्य, hpd_irq,
					   flags, "hpd", output);
		अगर (err < 0) अणु
			dev_err(output->dev, "failed to request IRQ#%u: %d\n",
				output->hpd_irq, err);
			वापस err;
		पूर्ण

		output->connector.polled = DRM_CONNECTOR_POLL_HPD;

		/*
		 * Disable the पूर्णांकerrupt until the connector has been
		 * initialized to aव्योम a race in the hotplug पूर्णांकerrupt
		 * handler.
		 */
		disable_irq(output->hpd_irq);
	पूर्ण

	वापस 0;
पूर्ण

व्योम tegra_output_हटाओ(काष्ठा tegra_output *output)
अणु
	अगर (output->hpd_gpio)
		मुक्त_irq(output->hpd_irq, output);

	अगर (output->ddc)
		i2c_put_adapter(output->ddc);
पूर्ण

पूर्णांक tegra_output_init(काष्ठा drm_device *drm, काष्ठा tegra_output *output)
अणु
	पूर्णांक connector_type;

	/*
	 * The connector is now रेजिस्टरed and पढ़ोy to receive hotplug events
	 * so the hotplug पूर्णांकerrupt can be enabled.
	 */
	अगर (output->hpd_gpio)
		enable_irq(output->hpd_irq);

	connector_type = output->connector.connector_type;
	/*
	 * Create a CEC notअगरier क्रम HDMI connector.
	 */
	अगर (connector_type == DRM_MODE_CONNECTOR_HDMIA ||
	    connector_type == DRM_MODE_CONNECTOR_HDMIB) अणु
		काष्ठा cec_connector_info conn_info;

		cec_fill_conn_info_from_drm(&conn_info, &output->connector);
		output->cec = cec_notअगरier_conn_रेजिस्टर(output->dev, शून्य,
							 &conn_info);
		अगर (!output->cec)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम tegra_output_निकास(काष्ठा tegra_output *output)
अणु
	/*
	 * The connector is going away, so the पूर्णांकerrupt must be disabled to
	 * prevent the hotplug पूर्णांकerrupt handler from potentially crashing.
	 */
	अगर (output->hpd_gpio)
		disable_irq(output->hpd_irq);
पूर्ण

व्योम tegra_output_find_possible_crtcs(काष्ठा tegra_output *output,
				      काष्ठा drm_device *drm)
अणु
	काष्ठा device *dev = output->dev;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक mask = 0;

	drm_क्रम_each_crtc(crtc, drm) अणु
		काष्ठा tegra_dc *dc = to_tegra_dc(crtc);

		अगर (tegra_dc_has_output(dc, dev))
			mask |= drm_crtc_mask(crtc);
	पूर्ण

	अगर (mask == 0) अणु
		dev_warn(dev, "missing output definition for heads in DT\n");
		mask = 0x3;
	पूर्ण

	output->encoder.possible_crtcs = mask;
पूर्ण

पूर्णांक tegra_output_suspend(काष्ठा tegra_output *output)
अणु
	अगर (output->hpd_irq)
		disable_irq(output->hpd_irq);

	वापस 0;
पूर्ण

पूर्णांक tegra_output_resume(काष्ठा tegra_output *output)
अणु
	अगर (output->hpd_irq)
		enable_irq(output->hpd_irq);

	वापस 0;
पूर्ण
