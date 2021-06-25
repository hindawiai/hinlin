<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 * Copyright (C) 2017 Broadcom
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

काष्ठा panel_bridge अणु
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;
	काष्ठा drm_panel *panel;
	u32 connector_type;
पूर्ण;

अटल अंतरभूत काष्ठा panel_bridge *
drm_bridge_to_panel_bridge(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा panel_bridge, bridge);
पूर्ण

अटल अंतरभूत काष्ठा panel_bridge *
drm_connector_to_panel_bridge(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा panel_bridge, connector);
पूर्ण

अटल पूर्णांक panel_bridge_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा panel_bridge *panel_bridge =
		drm_connector_to_panel_bridge(connector);

	वापस drm_panel_get_modes(panel_bridge->panel, connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs
panel_bridge_connector_helper_funcs = अणु
	.get_modes = panel_bridge_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs panel_bridge_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक panel_bridge_attach(काष्ठा drm_bridge *bridge,
			       क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);
	काष्ठा drm_connector *connector = &panel_bridge->connector;
	पूर्णांक ret;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Missing encoder\n");
		वापस -ENODEV;
	पूर्ण

	drm_connector_helper_add(connector,
				 &panel_bridge_connector_helper_funcs);

	ret = drm_connector_init(bridge->dev, connector,
				 &panel_bridge_connector_funcs,
				 panel_bridge->connector_type);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector\n");
		वापस ret;
	पूर्ण

	drm_connector_attach_encoder(&panel_bridge->connector,
					  bridge->encoder);

	वापस 0;
पूर्ण

अटल व्योम panel_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);
	काष्ठा drm_connector *connector = &panel_bridge->connector;

	/*
	 * Cleanup the connector अगर we know it was initialized.
	 *
	 * FIXME: This wouldn't be needed अगर the panel_bridge काष्ठाure was
	 * allocated with drmm_kzalloc(). This might be tricky since the
	 * drm_device poपूर्णांकer can only be retrieved when the bridge is attached.
	 */
	अगर (connector->dev)
		drm_connector_cleanup(connector);
पूर्ण

अटल व्योम panel_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);

	drm_panel_prepare(panel_bridge->panel);
पूर्ण

अटल व्योम panel_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);

	drm_panel_enable(panel_bridge->panel);
पूर्ण

अटल व्योम panel_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);

	drm_panel_disable(panel_bridge->panel);
पूर्ण

अटल व्योम panel_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);

	drm_panel_unprepare(panel_bridge->panel);
पूर्ण

अटल पूर्णांक panel_bridge_get_modes(काष्ठा drm_bridge *bridge,
				  काष्ठा drm_connector *connector)
अणु
	काष्ठा panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);

	वापस drm_panel_get_modes(panel_bridge->panel, connector);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs panel_bridge_bridge_funcs = अणु
	.attach = panel_bridge_attach,
	.detach = panel_bridge_detach,
	.pre_enable = panel_bridge_pre_enable,
	.enable = panel_bridge_enable,
	.disable = panel_bridge_disable,
	.post_disable = panel_bridge_post_disable,
	.get_modes = panel_bridge_get_modes,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_get_input_bus_fmts = drm_atomic_helper_bridge_propagate_bus_fmt,
पूर्ण;

/**
 * drm_panel_bridge_add - Creates a &drm_bridge and &drm_connector that
 * just calls the appropriate functions from &drm_panel.
 *
 * @panel: The drm_panel being wrapped.  Must be non-शून्य.
 *
 * For drivers converting from directly using drm_panel: The expected
 * usage pattern is that during either encoder module probe or DSI
 * host attach, a drm_panel will be looked up through
 * drm_of_find_panel_or_bridge().  drm_panel_bridge_add() is used to
 * wrap that panel in the new bridge, and the result can then be
 * passed to drm_bridge_attach().  The drm_panel_prepare() and related
 * functions can be dropped from the encoder driver (they're now
 * called by the KMS helpers beक्रमe calling पूर्णांकo the encoder), aदीर्घ
 * with connector creation.  When करोne with the bridge (after
 * drm_mode_config_cleanup() अगर the bridge has alपढ़ोy been attached), then
 * drm_panel_bridge_हटाओ() to मुक्त it.
 *
 * The connector type is set to @panel->connector_type, which must be set to a
 * known type. Calling this function with a panel whose connector type is
 * DRM_MODE_CONNECTOR_Unknown will वापस ERR_PTR(-EINVAL).
 *
 * See devm_drm_panel_bridge_add() क्रम an स्वतःmatically managed version of this
 * function.
 */
काष्ठा drm_bridge *drm_panel_bridge_add(काष्ठा drm_panel *panel)
अणु
	अगर (WARN_ON(panel->connector_type == DRM_MODE_CONNECTOR_Unknown))
		वापस ERR_PTR(-EINVAL);

	वापस drm_panel_bridge_add_typed(panel, panel->connector_type);
पूर्ण
EXPORT_SYMBOL(drm_panel_bridge_add);

/**
 * drm_panel_bridge_add_typed - Creates a &drm_bridge and &drm_connector with
 * an explicit connector type.
 * @panel: The drm_panel being wrapped.  Must be non-शून्य.
 * @connector_type: The connector type (DRM_MODE_CONNECTOR_*)
 *
 * This is just like drm_panel_bridge_add(), but क्रमces the connector type to
 * @connector_type instead of infering it from the panel.
 *
 * This function is deprecated and should not be used in new drivers. Use
 * drm_panel_bridge_add() instead, and fix panel drivers as necessary अगर they
 * करोn't report a connector type.
 */
काष्ठा drm_bridge *drm_panel_bridge_add_typed(काष्ठा drm_panel *panel,
					      u32 connector_type)
अणु
	काष्ठा panel_bridge *panel_bridge;

	अगर (!panel)
		वापस ERR_PTR(-EINVAL);

	panel_bridge = devm_kzalloc(panel->dev, माप(*panel_bridge),
				    GFP_KERNEL);
	अगर (!panel_bridge)
		वापस ERR_PTR(-ENOMEM);

	panel_bridge->connector_type = connector_type;
	panel_bridge->panel = panel;

	panel_bridge->bridge.funcs = &panel_bridge_bridge_funcs;
#अगर_घोषित CONFIG_OF
	panel_bridge->bridge.of_node = panel->dev->of_node;
#पूर्ण_अगर
	panel_bridge->bridge.ops = DRM_BRIDGE_OP_MODES;
	panel_bridge->bridge.type = connector_type;

	drm_bridge_add(&panel_bridge->bridge);

	वापस &panel_bridge->bridge;
पूर्ण
EXPORT_SYMBOL(drm_panel_bridge_add_typed);

/**
 * drm_panel_bridge_हटाओ - Unरेजिस्टरs and मुक्तs a drm_bridge
 * created by drm_panel_bridge_add().
 *
 * @bridge: The drm_bridge being मुक्तd.
 */
व्योम drm_panel_bridge_हटाओ(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा panel_bridge *panel_bridge;

	अगर (!bridge)
		वापस;

	अगर (bridge->funcs != &panel_bridge_bridge_funcs)
		वापस;

	panel_bridge = drm_bridge_to_panel_bridge(bridge);

	drm_bridge_हटाओ(bridge);
	devm_kमुक्त(panel_bridge->panel->dev, bridge);
पूर्ण
EXPORT_SYMBOL(drm_panel_bridge_हटाओ);

अटल व्योम devm_drm_panel_bridge_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा drm_bridge **bridge = res;

	drm_panel_bridge_हटाओ(*bridge);
पूर्ण

/**
 * devm_drm_panel_bridge_add - Creates a managed &drm_bridge and &drm_connector
 * that just calls the appropriate functions from &drm_panel.
 * @dev: device to tie the bridge lअगरeसमय to
 * @panel: The drm_panel being wrapped.  Must be non-शून्य.
 *
 * This is the managed version of drm_panel_bridge_add() which स्वतःmatically
 * calls drm_panel_bridge_हटाओ() when @dev is unbound.
 */
काष्ठा drm_bridge *devm_drm_panel_bridge_add(काष्ठा device *dev,
					     काष्ठा drm_panel *panel)
अणु
	अगर (WARN_ON(panel->connector_type == DRM_MODE_CONNECTOR_Unknown))
		वापस ERR_PTR(-EINVAL);

	वापस devm_drm_panel_bridge_add_typed(dev, panel,
					       panel->connector_type);
पूर्ण
EXPORT_SYMBOL(devm_drm_panel_bridge_add);

/**
 * devm_drm_panel_bridge_add_typed - Creates a managed &drm_bridge and
 * &drm_connector with an explicit connector type.
 * @dev: device to tie the bridge lअगरeसमय to
 * @panel: The drm_panel being wrapped.  Must be non-शून्य.
 * @connector_type: The connector type (DRM_MODE_CONNECTOR_*)
 *
 * This is just like devm_drm_panel_bridge_add(), but क्रमces the connector type
 * to @connector_type instead of infering it from the panel.
 *
 * This function is deprecated and should not be used in new drivers. Use
 * devm_drm_panel_bridge_add() instead, and fix panel drivers as necessary अगर
 * they करोn't report a connector type.
 */
काष्ठा drm_bridge *devm_drm_panel_bridge_add_typed(काष्ठा device *dev,
						   काष्ठा drm_panel *panel,
						   u32 connector_type)
अणु
	काष्ठा drm_bridge **ptr, *bridge;

	ptr = devres_alloc(devm_drm_panel_bridge_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	bridge = drm_panel_bridge_add_typed(panel, connector_type);
	अगर (!IS_ERR(bridge)) अणु
		*ptr = bridge;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस bridge;
पूर्ण
EXPORT_SYMBOL(devm_drm_panel_bridge_add_typed);

/**
 * drm_panel_bridge_connector - वापस the connector क्रम the panel bridge
 * @bridge: The drm_bridge.
 *
 * drm_panel_bridge creates the connector.
 * This function gives बाह्यal access to the connector.
 *
 * Returns: Poपूर्णांकer to drm_connector
 */
काष्ठा drm_connector *drm_panel_bridge_connector(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा panel_bridge *panel_bridge;

	panel_bridge = drm_bridge_to_panel_bridge(bridge);

	वापस &panel_bridge->connector;
पूर्ण
EXPORT_SYMBOL(drm_panel_bridge_connector);
