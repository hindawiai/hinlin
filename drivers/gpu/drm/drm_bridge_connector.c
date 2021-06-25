<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_probe_helper.h>

/**
 * DOC: overview
 *
 * The DRM bridge connector helper object provides a DRM connector
 * implementation that wraps a chain of &काष्ठा drm_bridge. The connector
 * operations are fully implemented based on the operations of the bridges in
 * the chain, and करोn't require any पूर्णांकervention from the display controller
 * driver at runसमय.
 *
 * To use the helper, display controller drivers create a bridge connector with
 * a call to drm_bridge_connector_init(). This associates the newly created
 * connector with the chain of bridges passed to the function and रेजिस्टरs it
 * with the DRM device. At that poपूर्णांक the connector becomes fully usable, no
 * further operation is needed.
 *
 * The DRM bridge connector operations are implemented based on the operations
 * provided by the bridges in the chain. Each connector operation is delegated
 * to the bridge बंदst to the connector (at the end of the chain) that
 * provides the relevant functionality.
 *
 * To make use of this helper, all bridges in the chain shall report bridge
 * operation flags (&drm_bridge->ops) and bridge output type
 * (&drm_bridge->type), as well as the DRM_BRIDGE_ATTACH_NO_CONNECTOR attach
 * flag (none of the bridges shall create a DRM connector directly).
 */

/**
 * काष्ठा drm_bridge_connector - A connector backed by a chain of bridges
 */
काष्ठा drm_bridge_connector अणु
	/**
	 * @base: The base DRM connector
	 */
	काष्ठा drm_connector base;
	/**
	 * @encoder:
	 *
	 * The encoder at the start of the bridges chain.
	 */
	काष्ठा drm_encoder *encoder;
	/**
	 * @bridge_edid:
	 *
	 * The last bridge in the chain (बंदst to the connector) that provides
	 * EDID पढ़ो support, अगर any (see &DRM_BRIDGE_OP_EDID).
	 */
	काष्ठा drm_bridge *bridge_edid;
	/**
	 * @bridge_hpd:
	 *
	 * The last bridge in the chain (बंदst to the connector) that provides
	 * hot-plug detection notअगरication, अगर any (see &DRM_BRIDGE_OP_HPD).
	 */
	काष्ठा drm_bridge *bridge_hpd;
	/**
	 * @bridge_detect:
	 *
	 * The last bridge in the chain (बंदst to the connector) that provides
	 * connector detection, अगर any (see &DRM_BRIDGE_OP_DETECT).
	 */
	काष्ठा drm_bridge *bridge_detect;
	/**
	 * @bridge_modes:
	 *
	 * The last bridge in the chain (बंदst to the connector) that provides
	 * connector modes detection, अगर any (see &DRM_BRIDGE_OP_MODES).
	 */
	काष्ठा drm_bridge *bridge_modes;
पूर्ण;

#घोषणा to_drm_bridge_connector(x) \
	container_of(x, काष्ठा drm_bridge_connector, base)

/* -----------------------------------------------------------------------------
 * Bridge Connector Hot-Plug Handling
 */

अटल व्योम drm_bridge_connector_hpd_notअगरy(काष्ठा drm_connector *connector,
					    क्रमागत drm_connector_status status)
अणु
	काष्ठा drm_bridge_connector *bridge_connector =
		to_drm_bridge_connector(connector);
	काष्ठा drm_bridge *bridge;

	/* Notअगरy all bridges in the pipeline of hotplug events. */
	drm_क्रम_each_bridge_in_chain(bridge_connector->encoder, bridge) अणु
		अगर (bridge->funcs->hpd_notअगरy)
			bridge->funcs->hpd_notअगरy(bridge, status);
	पूर्ण
पूर्ण

अटल व्योम drm_bridge_connector_hpd_cb(व्योम *cb_data,
					क्रमागत drm_connector_status status)
अणु
	काष्ठा drm_bridge_connector *drm_bridge_connector = cb_data;
	काष्ठा drm_connector *connector = &drm_bridge_connector->base;
	काष्ठा drm_device *dev = connector->dev;
	क्रमागत drm_connector_status old_status;

	mutex_lock(&dev->mode_config.mutex);
	old_status = connector->status;
	connector->status = status;
	mutex_unlock(&dev->mode_config.mutex);

	अगर (old_status == status)
		वापस;

	drm_bridge_connector_hpd_notअगरy(connector, status);

	drm_kms_helper_hotplug_event(dev);
पूर्ण

/**
 * drm_bridge_connector_enable_hpd - Enable hot-plug detection क्रम the connector
 * @connector: The DRM bridge connector
 *
 * This function enables hot-plug detection क्रम the given bridge connector.
 * This is typically used by display drivers in their resume handler.
 */
व्योम drm_bridge_connector_enable_hpd(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_bridge_connector *bridge_connector =
		to_drm_bridge_connector(connector);
	काष्ठा drm_bridge *hpd = bridge_connector->bridge_hpd;

	अगर (hpd)
		drm_bridge_hpd_enable(hpd, drm_bridge_connector_hpd_cb,
				      bridge_connector);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_connector_enable_hpd);

/**
 * drm_bridge_connector_disable_hpd - Disable hot-plug detection क्रम the
 * connector
 * @connector: The DRM bridge connector
 *
 * This function disables hot-plug detection क्रम the given bridge connector.
 * This is typically used by display drivers in their suspend handler.
 */
व्योम drm_bridge_connector_disable_hpd(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_bridge_connector *bridge_connector =
		to_drm_bridge_connector(connector);
	काष्ठा drm_bridge *hpd = bridge_connector->bridge_hpd;

	अगर (hpd)
		drm_bridge_hpd_disable(hpd);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_connector_disable_hpd);

/* -----------------------------------------------------------------------------
 * Bridge Connector Functions
 */

अटल क्रमागत drm_connector_status
drm_bridge_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_bridge_connector *bridge_connector =
		to_drm_bridge_connector(connector);
	काष्ठा drm_bridge *detect = bridge_connector->bridge_detect;
	क्रमागत drm_connector_status status;

	अगर (detect) अणु
		status = detect->funcs->detect(detect);

		drm_bridge_connector_hpd_notअगरy(connector, status);
	पूर्ण अन्यथा अणु
		चयन (connector->connector_type) अणु
		हाल DRM_MODE_CONNECTOR_DPI:
		हाल DRM_MODE_CONNECTOR_LVDS:
		हाल DRM_MODE_CONNECTOR_DSI:
		हाल DRM_MODE_CONNECTOR_eDP:
			status = connector_status_connected;
			अवरोध;
		शेष:
			status = connector_status_unknown;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम drm_bridge_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_bridge_connector *bridge_connector =
		to_drm_bridge_connector(connector);

	अगर (bridge_connector->bridge_hpd) अणु
		काष्ठा drm_bridge *hpd = bridge_connector->bridge_hpd;

		drm_bridge_hpd_disable(hpd);
	पूर्ण

	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);

	kमुक्त(bridge_connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs drm_bridge_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.detect = drm_bridge_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_bridge_connector_destroy,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Bridge Connector Helper Functions
 */

अटल पूर्णांक drm_bridge_connector_get_modes_edid(काष्ठा drm_connector *connector,
					       काष्ठा drm_bridge *bridge)
अणु
	क्रमागत drm_connector_status status;
	काष्ठा edid *edid;
	पूर्णांक n;

	status = drm_bridge_connector_detect(connector, false);
	अगर (status != connector_status_connected)
		जाओ no_edid;

	edid = bridge->funcs->get_edid(bridge, connector);
	अगर (!drm_edid_is_valid(edid)) अणु
		kमुक्त(edid);
		जाओ no_edid;
	पूर्ण

	drm_connector_update_edid_property(connector, edid);
	n = drm_add_edid_modes(connector, edid);

	kमुक्त(edid);
	वापस n;

no_edid:
	drm_connector_update_edid_property(connector, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक drm_bridge_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_bridge_connector *bridge_connector =
		to_drm_bridge_connector(connector);
	काष्ठा drm_bridge *bridge;

	/*
	 * If display exposes EDID, then we parse that in the normal way to
	 * build table of supported modes.
	 */
	bridge = bridge_connector->bridge_edid;
	अगर (bridge)
		वापस drm_bridge_connector_get_modes_edid(connector, bridge);

	/*
	 * Otherwise अगर the display pipeline reports modes (e.g. with a fixed
	 * resolution panel or an analog TV output), query it.
	 */
	bridge = bridge_connector->bridge_modes;
	अगर (bridge)
		वापस bridge->funcs->get_modes(bridge, connector);

	/*
	 * We can't retrieve modes, which can happen क्रम instance क्रम a DVI or
	 * VGA output with the DDC bus unconnected. The KMS core will add the
	 * शेष modes.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs drm_bridge_connector_helper_funcs = अणु
	.get_modes = drm_bridge_connector_get_modes,
	/* No need क्रम .mode_valid(), the bridges are checked by the core. */
पूर्ण;

/* -----------------------------------------------------------------------------
 * Bridge Connector Initialisation
 */

/**
 * drm_bridge_connector_init - Initialise a connector क्रम a chain of bridges
 * @drm: the DRM device
 * @encoder: the encoder where the bridge chain starts
 *
 * Allocate, initialise and रेजिस्टर a &drm_bridge_connector with the @drm
 * device. The connector is associated with a chain of bridges that starts at
 * the @encoder. All bridges in the chain shall report bridge operation flags
 * (&drm_bridge->ops) and bridge output type (&drm_bridge->type), and none of
 * them may create a DRM connector directly.
 *
 * Returns a poपूर्णांकer to the new connector on success, or a negative error
 * poपूर्णांकer otherwise.
 */
काष्ठा drm_connector *drm_bridge_connector_init(काष्ठा drm_device *drm,
						काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_bridge_connector *bridge_connector;
	काष्ठा drm_connector *connector;
	काष्ठा i2c_adapter *ddc = शून्य;
	काष्ठा drm_bridge *bridge;
	पूर्णांक connector_type;

	bridge_connector = kzalloc(माप(*bridge_connector), GFP_KERNEL);
	अगर (!bridge_connector)
		वापस ERR_PTR(-ENOMEM);

	bridge_connector->encoder = encoder;

	/*
	 * TODO: Handle द्विगुनscan_allowed, stereo_allowed and
	 * ycbcr_420_allowed.
	 */
	connector = &bridge_connector->base;
	connector->पूर्णांकerlace_allowed = true;

	/*
	 * Initialise connector status handling. First locate the furthest
	 * bridges in the pipeline that support HPD and output detection. Then
	 * initialise the connector polling mode, using HPD अगर available and
	 * falling back to polling अगर supported. If neither HPD nor output
	 * detection are available, we करोn't support hotplug detection at all.
	 */
	connector_type = DRM_MODE_CONNECTOR_Unknown;
	drm_क्रम_each_bridge_in_chain(encoder, bridge) अणु
		अगर (!bridge->पूर्णांकerlace_allowed)
			connector->पूर्णांकerlace_allowed = false;

		अगर (bridge->ops & DRM_BRIDGE_OP_EDID)
			bridge_connector->bridge_edid = bridge;
		अगर (bridge->ops & DRM_BRIDGE_OP_HPD)
			bridge_connector->bridge_hpd = bridge;
		अगर (bridge->ops & DRM_BRIDGE_OP_DETECT)
			bridge_connector->bridge_detect = bridge;
		अगर (bridge->ops & DRM_BRIDGE_OP_MODES)
			bridge_connector->bridge_modes = bridge;

		अगर (!drm_bridge_get_next_bridge(bridge))
			connector_type = bridge->type;

		अगर (bridge->ddc)
			ddc = bridge->ddc;
	पूर्ण

	अगर (connector_type == DRM_MODE_CONNECTOR_Unknown) अणु
		kमुक्त(bridge_connector);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	drm_connector_init_with_ddc(drm, connector, &drm_bridge_connector_funcs,
				    connector_type, ddc);
	drm_connector_helper_add(connector, &drm_bridge_connector_helper_funcs);

	अगर (bridge_connector->bridge_hpd)
		connector->polled = DRM_CONNECTOR_POLL_HPD;
	अन्यथा अगर (bridge_connector->bridge_detect)
		connector->polled = DRM_CONNECTOR_POLL_CONNECT
				  | DRM_CONNECTOR_POLL_DISCONNECT;

	वापस connector;
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_connector_init);
