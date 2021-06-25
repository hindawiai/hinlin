<शैली गुरु>
/*
 * Copyright (C) 2013, NVIDIA Corporation.  All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>

अटल DEFINE_MUTEX(panel_lock);
अटल LIST_HEAD(panel_list);

/**
 * DOC: drm panel
 *
 * The DRM panel helpers allow drivers to रेजिस्टर panel objects with a
 * central registry and provide functions to retrieve those panels in display
 * drivers.
 *
 * For easy पूर्णांकegration पूर्णांकo drivers using the &drm_bridge infraकाष्ठाure please
 * take look at drm_panel_bridge_add() and devm_drm_panel_bridge_add().
 */

/**
 * drm_panel_init - initialize a panel
 * @panel: DRM panel
 * @dev: parent device of the panel
 * @funcs: panel operations
 * @connector_type: the connector type (DRM_MODE_CONNECTOR_*) corresponding to
 *	the panel पूर्णांकerface
 *
 * Initialize the panel काष्ठाure क्रम subsequent registration with
 * drm_panel_add().
 */
व्योम drm_panel_init(काष्ठा drm_panel *panel, काष्ठा device *dev,
		    स्थिर काष्ठा drm_panel_funcs *funcs, पूर्णांक connector_type)
अणु
	INIT_LIST_HEAD(&panel->list);
	panel->dev = dev;
	panel->funcs = funcs;
	panel->connector_type = connector_type;
पूर्ण
EXPORT_SYMBOL(drm_panel_init);

/**
 * drm_panel_add - add a panel to the global registry
 * @panel: panel to add
 *
 * Add a panel to the global registry so that it can be looked up by display
 * drivers.
 */
व्योम drm_panel_add(काष्ठा drm_panel *panel)
अणु
	mutex_lock(&panel_lock);
	list_add_tail(&panel->list, &panel_list);
	mutex_unlock(&panel_lock);
पूर्ण
EXPORT_SYMBOL(drm_panel_add);

/**
 * drm_panel_हटाओ - हटाओ a panel from the global registry
 * @panel: DRM panel
 *
 * Removes a panel from the global registry.
 */
व्योम drm_panel_हटाओ(काष्ठा drm_panel *panel)
अणु
	mutex_lock(&panel_lock);
	list_del_init(&panel->list);
	mutex_unlock(&panel_lock);
पूर्ण
EXPORT_SYMBOL(drm_panel_हटाओ);

/**
 * drm_panel_prepare - घातer on a panel
 * @panel: DRM panel
 *
 * Calling this function will enable घातer and deनिश्चित any reset संकेतs to
 * the panel. After this has completed it is possible to communicate with any
 * पूर्णांकegrated circuitry via a command bus.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_panel_prepare(काष्ठा drm_panel *panel)
अणु
	अगर (!panel)
		वापस -EINVAL;

	अगर (panel->funcs && panel->funcs->prepare)
		वापस panel->funcs->prepare(panel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_panel_prepare);

/**
 * drm_panel_unprepare - घातer off a panel
 * @panel: DRM panel
 *
 * Calling this function will completely घातer off a panel (निश्चित the panel's
 * reset, turn off घातer supplies, ...). After this function has completed, it
 * is usually no दीर्घer possible to communicate with the panel until another
 * call to drm_panel_prepare().
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	अगर (!panel)
		वापस -EINVAL;

	अगर (panel->funcs && panel->funcs->unprepare)
		वापस panel->funcs->unprepare(panel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_panel_unprepare);

/**
 * drm_panel_enable - enable a panel
 * @panel: DRM panel
 *
 * Calling this function will cause the panel display drivers to be turned on
 * and the backlight to be enabled. Content will be visible on screen after
 * this call completes.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_panel_enable(काष्ठा drm_panel *panel)
अणु
	पूर्णांक ret;

	अगर (!panel)
		वापस -EINVAL;

	अगर (panel->funcs && panel->funcs->enable) अणु
		ret = panel->funcs->enable(panel);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = backlight_enable(panel->backlight);
	अगर (ret < 0)
		DRM_DEV_INFO(panel->dev, "failed to enable backlight: %d\n",
			     ret);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_panel_enable);

/**
 * drm_panel_disable - disable a panel
 * @panel: DRM panel
 *
 * This will typically turn off the panel's backlight or disable the display
 * drivers. For smart panels it should still be possible to communicate with
 * the पूर्णांकegrated circuitry via any command bus after this call.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_panel_disable(काष्ठा drm_panel *panel)
अणु
	पूर्णांक ret;

	अगर (!panel)
		वापस -EINVAL;

	ret = backlight_disable(panel->backlight);
	अगर (ret < 0)
		DRM_DEV_INFO(panel->dev, "failed to disable backlight: %d\n",
			     ret);

	अगर (panel->funcs && panel->funcs->disable)
		वापस panel->funcs->disable(panel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_panel_disable);

/**
 * drm_panel_get_modes - probe the available display modes of a panel
 * @panel: DRM panel
 * @connector: DRM connector
 *
 * The modes probed from the panel are स्वतःmatically added to the connector
 * that the panel is attached to.
 *
 * Return: The number of modes available from the panel on success or a
 * negative error code on failure.
 */
पूर्णांक drm_panel_get_modes(काष्ठा drm_panel *panel,
			काष्ठा drm_connector *connector)
अणु
	अगर (!panel)
		वापस -EINVAL;

	अगर (panel->funcs && panel->funcs->get_modes)
		वापस panel->funcs->get_modes(panel, connector);

	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(drm_panel_get_modes);

#अगर_घोषित CONFIG_OF
/**
 * of_drm_find_panel - look up a panel using a device tree node
 * @np: device tree node of the panel
 *
 * Searches the set of रेजिस्टरed panels क्रम one that matches the given device
 * tree node. If a matching panel is found, वापस a poपूर्णांकer to it.
 *
 * Return: A poपूर्णांकer to the panel रेजिस्टरed क्रम the specअगरied device tree
 * node or an ERR_PTR() अगर no panel matching the device tree node can be found.
 *
 * Possible error codes वापसed by this function:
 *
 * - EPROBE_DEFER: the panel device has not been probed yet, and the caller
 *   should retry later
 * - ENODEV: the device is not available (status != "okay" or "ok")
 */
काष्ठा drm_panel *of_drm_find_panel(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा drm_panel *panel;

	अगर (!of_device_is_available(np))
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&panel_lock);

	list_क्रम_each_entry(panel, &panel_list, list) अणु
		अगर (panel->dev->of_node == np) अणु
			mutex_unlock(&panel_lock);
			वापस panel;
		पूर्ण
	पूर्ण

	mutex_unlock(&panel_lock);
	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण
EXPORT_SYMBOL(of_drm_find_panel);

/**
 * of_drm_get_panel_orientation - look up the orientation of the panel through
 * the "rotation" binding from a device tree node
 * @np: device tree node of the panel
 * @orientation: orientation क्रमागत to be filled in
 *
 * Looks up the rotation of a panel in the device tree. The orientation of the
 * panel is expressed as a property name "rotation" in the device tree. The
 * rotation in the device tree is counter घड़ीwise.
 *
 * Return: 0 when a valid rotation value (0, 90, 180, or 270) is पढ़ो or the
 * rotation property करोesn't exist. Return a negative error code on failure.
 */
पूर्णांक of_drm_get_panel_orientation(स्थिर काष्ठा device_node *np,
				 क्रमागत drm_panel_orientation *orientation)
अणु
	पूर्णांक rotation, ret;

	ret = of_property_पढ़ो_u32(np, "rotation", &rotation);
	अगर (ret == -EINVAL) अणु
		/* Don't return an error if there's no rotation property. */
		*orientation = DRM_MODE_PANEL_ORIENTATION_UNKNOWN;
		वापस 0;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	अगर (rotation == 0)
		*orientation = DRM_MODE_PANEL_ORIENTATION_NORMAL;
	अन्यथा अगर (rotation == 90)
		*orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP;
	अन्यथा अगर (rotation == 180)
		*orientation = DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP;
	अन्यथा अगर (rotation == 270)
		*orientation = DRM_MODE_PANEL_ORIENTATION_LEFT_UP;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(of_drm_get_panel_orientation);
#पूर्ण_अगर

#अगर IS_REACHABLE(CONFIG_BACKLIGHT_CLASS_DEVICE)
/**
 * drm_panel_of_backlight - use backlight device node क्रम backlight
 * @panel: DRM panel
 *
 * Use this function to enable backlight handling अगर your panel
 * uses device tree and has a backlight phandle.
 *
 * When the panel is enabled backlight will be enabled after a
 * successful call to &drm_panel_funcs.enable()
 *
 * When the panel is disabled backlight will be disabled beक्रमe the
 * call to &drm_panel_funcs.disable().
 *
 * A typical implementation क्रम a panel driver supporting device tree
 * will call this function at probe समय. Backlight will then be handled
 * transparently without requiring any पूर्णांकervention from the driver.
 * drm_panel_of_backlight() must be called after the call to drm_panel_init().
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_panel_of_backlight(काष्ठा drm_panel *panel)
अणु
	काष्ठा backlight_device *backlight;

	अगर (!panel || !panel->dev)
		वापस -EINVAL;

	backlight = devm_of_find_backlight(panel->dev);

	अगर (IS_ERR(backlight))
		वापस PTR_ERR(backlight);

	panel->backlight = backlight;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_panel_of_backlight);
#पूर्ण_अगर

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("DRM panel infrastructure");
MODULE_LICENSE("GPL and additional rights");
