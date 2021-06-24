<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_utils.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_sysfs.h>

#समावेश <linux/uaccess.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

/**
 * DOC: overview
 *
 * In DRM connectors are the general असलtraction क्रम display sinks, and include
 * also fixed panels or anything अन्यथा that can display pixels in some क्रमm. As
 * opposed to all other KMS objects representing hardware (like CRTC, encoder or
 * plane असलtractions) connectors can be hotplugged and unplugged at runसमय.
 * Hence they are reference-counted using drm_connector_get() and
 * drm_connector_put().
 *
 * KMS driver must create, initialize, रेजिस्टर and attach at a &काष्ठा
 * drm_connector क्रम each such sink. The instance is created as other KMS
 * objects and initialized by setting the following fields. The connector is
 * initialized with a call to drm_connector_init() with a poपूर्णांकer to the
 * &काष्ठा drm_connector_funcs and a connector type, and then exposed to
 * userspace with a call to drm_connector_रेजिस्टर().
 *
 * Connectors must be attached to an encoder to be used. For devices that map
 * connectors to encoders 1:1, the connector should be attached at
 * initialization समय with a call to drm_connector_attach_encoder(). The
 * driver must also set the &drm_connector.encoder field to poपूर्णांक to the
 * attached encoder.
 *
 * For connectors which are not fixed (like built-in panels) the driver needs to
 * support hotplug notअगरications. The simplest way to करो that is by using the
 * probe helpers, see drm_kms_helper_poll_init() क्रम connectors which करोn't have
 * hardware support क्रम hotplug पूर्णांकerrupts. Connectors with hardware hotplug
 * support can instead use e.g. drm_helper_hpd_irq_event().
 */

काष्ठा drm_conn_prop_क्रमागत_list अणु
	पूर्णांक type;
	स्थिर अक्षर *name;
	काष्ठा ida ida;
पूर्ण;

/*
 * Connector and encoder types.
 */
अटल काष्ठा drm_conn_prop_क्रमागत_list drm_connector_क्रमागत_list[] = अणु
	अणु DRM_MODE_CONNECTOR_Unknown, "Unknown" पूर्ण,
	अणु DRM_MODE_CONNECTOR_VGA, "VGA" पूर्ण,
	अणु DRM_MODE_CONNECTOR_DVII, "DVI-I" पूर्ण,
	अणु DRM_MODE_CONNECTOR_DVID, "DVI-D" पूर्ण,
	अणु DRM_MODE_CONNECTOR_DVIA, "DVI-A" पूर्ण,
	अणु DRM_MODE_CONNECTOR_Composite, "Composite" पूर्ण,
	अणु DRM_MODE_CONNECTOR_SVIDEO, "SVIDEO" पूर्ण,
	अणु DRM_MODE_CONNECTOR_LVDS, "LVDS" पूर्ण,
	अणु DRM_MODE_CONNECTOR_Component, "Component" पूर्ण,
	अणु DRM_MODE_CONNECTOR_9PinDIN, "DIN" पूर्ण,
	अणु DRM_MODE_CONNECTOR_DisplayPort, "DP" पूर्ण,
	अणु DRM_MODE_CONNECTOR_HDMIA, "HDMI-A" पूर्ण,
	अणु DRM_MODE_CONNECTOR_HDMIB, "HDMI-B" पूर्ण,
	अणु DRM_MODE_CONNECTOR_TV, "TV" पूर्ण,
	अणु DRM_MODE_CONNECTOR_eDP, "eDP" पूर्ण,
	अणु DRM_MODE_CONNECTOR_VIRTUAL, "Virtual" पूर्ण,
	अणु DRM_MODE_CONNECTOR_DSI, "DSI" पूर्ण,
	अणु DRM_MODE_CONNECTOR_DPI, "DPI" पूर्ण,
	अणु DRM_MODE_CONNECTOR_WRITEBACK, "Writeback" पूर्ण,
	अणु DRM_MODE_CONNECTOR_SPI, "SPI" पूर्ण,
	अणु DRM_MODE_CONNECTOR_USB, "USB" पूर्ण,
पूर्ण;

व्योम drm_connector_ida_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(drm_connector_क्रमागत_list); i++)
		ida_init(&drm_connector_क्रमागत_list[i].ida);
पूर्ण

व्योम drm_connector_ida_destroy(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(drm_connector_क्रमागत_list); i++)
		ida_destroy(&drm_connector_क्रमागत_list[i].ida);
पूर्ण

/**
 * drm_get_connector_type_name - वापस a string क्रम connector type
 * @type: The connector type (DRM_MODE_CONNECTOR_*)
 *
 * Returns: the name of the connector type, or शून्य अगर the type is not valid.
 */
स्थिर अक्षर *drm_get_connector_type_name(अचिन्हित पूर्णांक type)
अणु
	अगर (type < ARRAY_SIZE(drm_connector_क्रमागत_list))
		वापस drm_connector_क्रमागत_list[type].name;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_get_connector_type_name);

/**
 * drm_connector_get_cmdline_mode - पढ़ोs the user's cmdline mode
 * @connector: connector to query
 *
 * The kernel supports per-connector configuration of its consoles through
 * use of the video= parameter. This function parses that option and
 * extracts the user's specअगरied mode (or enable/disable status) क्रम a
 * particular connector. This is typically only used during the early fbdev
 * setup.
 */
अटल व्योम drm_connector_get_cmdline_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_cmdline_mode *mode = &connector->cmdline_mode;
	अक्षर *option = शून्य;

	अगर (fb_get_options(connector->name, &option))
		वापस;

	अगर (!drm_mode_parse_command_line_क्रम_connector(option,
						       connector,
						       mode))
		वापस;

	अगर (mode->क्रमce) अणु
		DRM_INFO("forcing %s connector %s\n", connector->name,
			 drm_get_connector_क्रमce_name(mode->क्रमce));
		connector->क्रमce = mode->क्रमce;
	पूर्ण

	अगर (mode->panel_orientation != DRM_MODE_PANEL_ORIENTATION_UNKNOWN) अणु
		DRM_INFO("cmdline forces connector %s panel_orientation to %d\n",
			 connector->name, mode->panel_orientation);
		drm_connector_set_panel_orientation(connector,
						    mode->panel_orientation);
	पूर्ण

	DRM_DEBUG_KMS("cmdline mode for connector %s %s %dx%d@%dHz%s%s%s\n",
		      connector->name, mode->name,
		      mode->xres, mode->yres,
		      mode->refresh_specअगरied ? mode->refresh : 60,
		      mode->rb ? " reduced blanking" : "",
		      mode->margins ? " with margins" : "",
		      mode->पूर्णांकerlace ?  " interlaced" : "");
पूर्ण

अटल व्योम drm_connector_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा drm_connector *connector =
		container_of(kref, काष्ठा drm_connector, base.refcount);
	काष्ठा drm_device *dev = connector->dev;

	drm_mode_object_unरेजिस्टर(dev, &connector->base);
	connector->funcs->destroy(connector);
पूर्ण

व्योम drm_connector_मुक्त_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_connector *connector, *n;
	काष्ठा drm_device *dev =
		container_of(work, काष्ठा drm_device, mode_config.connector_मुक्त_work);
	काष्ठा drm_mode_config *config = &dev->mode_config;
	अचिन्हित दीर्घ flags;
	काष्ठा llist_node *मुक्तd;

	spin_lock_irqsave(&config->connector_list_lock, flags);
	मुक्तd = llist_del_all(&config->connector_मुक्त_list);
	spin_unlock_irqrestore(&config->connector_list_lock, flags);

	llist_क्रम_each_entry_safe(connector, n, मुक्तd, मुक्त_node) अणु
		drm_mode_object_unरेजिस्टर(dev, &connector->base);
		connector->funcs->destroy(connector);
	पूर्ण
पूर्ण

/**
 * drm_connector_init - Init a pपुनः_स्मृतिated connector
 * @dev: DRM device
 * @connector: the connector to init
 * @funcs: callbacks क्रम this connector
 * @connector_type: user visible type of the connector
 *
 * Initialises a pपुनः_स्मृतिated connector. Connectors should be
 * subclassed as part of driver connector objects.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_connector_init(काष्ठा drm_device *dev,
		       काष्ठा drm_connector *connector,
		       स्थिर काष्ठा drm_connector_funcs *funcs,
		       पूर्णांक connector_type)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	पूर्णांक ret;
	काष्ठा ida *connector_ida =
		&drm_connector_क्रमागत_list[connector_type].ida;

	WARN_ON(drm_drv_uses_atomic_modeset(dev) &&
		(!funcs->atomic_destroy_state ||
		 !funcs->atomic_duplicate_state));

	ret = __drm_mode_object_add(dev, &connector->base,
				    DRM_MODE_OBJECT_CONNECTOR,
				    false, drm_connector_मुक्त);
	अगर (ret)
		वापस ret;

	connector->base.properties = &connector->properties;
	connector->dev = dev;
	connector->funcs = funcs;

	/* connector index is used with 32bit biपंचांगasks */
	ret = ida_simple_get(&config->connector_ida, 0, 32, GFP_KERNEL);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("Failed to allocate %s connector index: %d\n",
			      drm_connector_क्रमागत_list[connector_type].name,
			      ret);
		जाओ out_put;
	पूर्ण
	connector->index = ret;
	ret = 0;

	connector->connector_type = connector_type;
	connector->connector_type_id =
		ida_simple_get(connector_ida, 1, 0, GFP_KERNEL);
	अगर (connector->connector_type_id < 0) अणु
		ret = connector->connector_type_id;
		जाओ out_put_id;
	पूर्ण
	connector->name =
		kaप्र_लिखो(GFP_KERNEL, "%s-%d",
			  drm_connector_क्रमागत_list[connector_type].name,
			  connector->connector_type_id);
	अगर (!connector->name) अणु
		ret = -ENOMEM;
		जाओ out_put_type_id;
	पूर्ण

	INIT_LIST_HEAD(&connector->probed_modes);
	INIT_LIST_HEAD(&connector->modes);
	mutex_init(&connector->mutex);
	connector->edid_blob_ptr = शून्य;
	connector->epoch_counter = 0;
	connector->tile_blob_ptr = शून्य;
	connector->status = connector_status_unknown;
	connector->display_info.panel_orientation =
		DRM_MODE_PANEL_ORIENTATION_UNKNOWN;

	drm_connector_get_cmdline_mode(connector);

	/* We should add connectors at the end to aव्योम upsetting the connector
	 * index too much. */
	spin_lock_irq(&config->connector_list_lock);
	list_add_tail(&connector->head, &config->connector_list);
	config->num_connector++;
	spin_unlock_irq(&config->connector_list_lock);

	अगर (connector_type != DRM_MODE_CONNECTOR_VIRTUAL &&
	    connector_type != DRM_MODE_CONNECTOR_WRITEBACK)
		drm_connector_attach_edid_property(connector);

	drm_object_attach_property(&connector->base,
				      config->dpms_property, 0);

	drm_object_attach_property(&connector->base,
				   config->link_status_property,
				   0);

	drm_object_attach_property(&connector->base,
				   config->non_desktop_property,
				   0);
	drm_object_attach_property(&connector->base,
				   config->tile_property,
				   0);

	अगर (drm_core_check_feature(dev, DRIVER_ATOMIC)) अणु
		drm_object_attach_property(&connector->base, config->prop_crtc_id, 0);
	पूर्ण

	connector->debugfs_entry = शून्य;
out_put_type_id:
	अगर (ret)
		ida_simple_हटाओ(connector_ida, connector->connector_type_id);
out_put_id:
	अगर (ret)
		ida_simple_हटाओ(&config->connector_ida, connector->index);
out_put:
	अगर (ret)
		drm_mode_object_unरेजिस्टर(dev, &connector->base);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_connector_init);

/**
 * drm_connector_init_with_ddc - Init a pपुनः_स्मृतिated connector
 * @dev: DRM device
 * @connector: the connector to init
 * @funcs: callbacks क्रम this connector
 * @connector_type: user visible type of the connector
 * @ddc: poपूर्णांकer to the associated ddc adapter
 *
 * Initialises a pपुनः_स्मृतिated connector. Connectors should be
 * subclassed as part of driver connector objects.
 *
 * Ensures that the ddc field of the connector is correctly set.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_connector_init_with_ddc(काष्ठा drm_device *dev,
				काष्ठा drm_connector *connector,
				स्थिर काष्ठा drm_connector_funcs *funcs,
				पूर्णांक connector_type,
				काष्ठा i2c_adapter *ddc)
अणु
	पूर्णांक ret;

	ret = drm_connector_init(dev, connector, funcs, connector_type);
	अगर (ret)
		वापस ret;

	/* provide ddc symlink in sysfs */
	connector->ddc = ddc;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_connector_init_with_ddc);

/**
 * drm_connector_attach_edid_property - attach edid property.
 * @connector: the connector
 *
 * Some connector types like DRM_MODE_CONNECTOR_VIRTUAL करो not get a
 * edid property attached by शेष.  This function can be used to
 * explicitly enable the edid property in these हालs.
 */
व्योम drm_connector_attach_edid_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_mode_config *config = &connector->dev->mode_config;

	drm_object_attach_property(&connector->base,
				   config->edid_property,
				   0);
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_edid_property);

/**
 * drm_connector_attach_encoder - attach a connector to an encoder
 * @connector: connector to attach
 * @encoder: encoder to attach @connector to
 *
 * This function links up a connector to an encoder. Note that the routing
 * restrictions between encoders and crtcs are exposed to userspace through the
 * possible_clones and possible_crtcs biपंचांगasks.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_attach_encoder(काष्ठा drm_connector *connector,
				 काष्ठा drm_encoder *encoder)
अणु
	/*
	 * In the past, drivers have attempted to model the अटल association
	 * of connector to encoder in simple connector/encoder devices using a
	 * direct assignment of connector->encoder = encoder. This connection
	 * is a logical one and the responsibility of the core, so drivers are
	 * expected not to mess with this.
	 *
	 * Note that the error वापस should've been enough here, but a large
	 * majority of drivers ignores the वापस value, so add in a big WARN
	 * to get people's attention.
	 */
	अगर (WARN_ON(connector->encoder))
		वापस -EINVAL;

	connector->possible_encoders |= drm_encoder_mask(encoder);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_encoder);

/**
 * drm_connector_has_possible_encoder - check अगर the connector and encoder are
 * associated with each other
 * @connector: the connector
 * @encoder: the encoder
 *
 * Returns:
 * True अगर @encoder is one of the possible encoders क्रम @connector.
 */
bool drm_connector_has_possible_encoder(काष्ठा drm_connector *connector,
					काष्ठा drm_encoder *encoder)
अणु
	वापस connector->possible_encoders & drm_encoder_mask(encoder);
पूर्ण
EXPORT_SYMBOL(drm_connector_has_possible_encoder);

अटल व्योम drm_mode_हटाओ(काष्ठा drm_connector *connector,
			    काष्ठा drm_display_mode *mode)
अणु
	list_del(&mode->head);
	drm_mode_destroy(connector->dev, mode);
पूर्ण

/**
 * drm_connector_cleanup - cleans up an initialised connector
 * @connector: connector to cleanup
 *
 * Cleans up the connector but करोesn't मुक्त the object.
 */
व्योम drm_connector_cleanup(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *mode, *t;

	/* The connector should have been हटाओd from userspace दीर्घ beक्रमe
	 * it is finally destroyed.
	 */
	अगर (WARN_ON(connector->registration_state ==
		    DRM_CONNECTOR_REGISTERED))
		drm_connector_unरेजिस्टर(connector);

	अगर (connector->tile_group) अणु
		drm_mode_put_tile_group(dev, connector->tile_group);
		connector->tile_group = शून्य;
	पूर्ण

	list_क्रम_each_entry_safe(mode, t, &connector->probed_modes, head)
		drm_mode_हटाओ(connector, mode);

	list_क्रम_each_entry_safe(mode, t, &connector->modes, head)
		drm_mode_हटाओ(connector, mode);

	ida_simple_हटाओ(&drm_connector_क्रमागत_list[connector->connector_type].ida,
			  connector->connector_type_id);

	ida_simple_हटाओ(&dev->mode_config.connector_ida,
			  connector->index);

	kमुक्त(connector->display_info.bus_क्रमmats);
	drm_mode_object_unरेजिस्टर(dev, &connector->base);
	kमुक्त(connector->name);
	connector->name = शून्य;
	spin_lock_irq(&dev->mode_config.connector_list_lock);
	list_del(&connector->head);
	dev->mode_config.num_connector--;
	spin_unlock_irq(&dev->mode_config.connector_list_lock);

	WARN_ON(connector->state && !connector->funcs->atomic_destroy_state);
	अगर (connector->state && connector->funcs->atomic_destroy_state)
		connector->funcs->atomic_destroy_state(connector,
						       connector->state);

	mutex_destroy(&connector->mutex);

	स_रखो(connector, 0, माप(*connector));
पूर्ण
EXPORT_SYMBOL(drm_connector_cleanup);

/**
 * drm_connector_रेजिस्टर - रेजिस्टर a connector
 * @connector: the connector to रेजिस्टर
 *
 * Register userspace पूर्णांकerfaces क्रम a connector. Only call this क्रम connectors
 * which can be hotplugged after drm_dev_रेजिस्टर() has been called alपढ़ोy,
 * e.g. DP MST connectors. All other connectors will be रेजिस्टरed स्वतःmatically
 * when calling drm_dev_रेजिस्टर().
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_connector_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	पूर्णांक ret = 0;

	अगर (!connector->dev->रेजिस्टरed)
		वापस 0;

	mutex_lock(&connector->mutex);
	अगर (connector->registration_state != DRM_CONNECTOR_INITIALIZING)
		जाओ unlock;

	ret = drm_sysfs_connector_add(connector);
	अगर (ret)
		जाओ unlock;

	drm_debugfs_connector_add(connector);

	अगर (connector->funcs->late_रेजिस्टर) अणु
		ret = connector->funcs->late_रेजिस्टर(connector);
		अगर (ret)
			जाओ err_debugfs;
	पूर्ण

	drm_mode_object_रेजिस्टर(connector->dev, &connector->base);

	connector->registration_state = DRM_CONNECTOR_REGISTERED;

	/* Let userspace know we have a new connector */
	drm_sysfs_hotplug_event(connector->dev);

	जाओ unlock;

err_debugfs:
	drm_debugfs_connector_हटाओ(connector);
	drm_sysfs_connector_हटाओ(connector);
unlock:
	mutex_unlock(&connector->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_connector_रेजिस्टर);

/**
 * drm_connector_unरेजिस्टर - unरेजिस्टर a connector
 * @connector: the connector to unरेजिस्टर
 *
 * Unरेजिस्टर userspace पूर्णांकerfaces क्रम a connector. Only call this क्रम
 * connectors which have रेजिस्टरed explicitly by calling drm_dev_रेजिस्टर(),
 * since connectors are unरेजिस्टरed स्वतःmatically when drm_dev_unरेजिस्टर() is
 * called.
 */
व्योम drm_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	mutex_lock(&connector->mutex);
	अगर (connector->registration_state != DRM_CONNECTOR_REGISTERED) अणु
		mutex_unlock(&connector->mutex);
		वापस;
	पूर्ण

	अगर (connector->funcs->early_unरेजिस्टर)
		connector->funcs->early_unरेजिस्टर(connector);

	drm_sysfs_connector_हटाओ(connector);
	drm_debugfs_connector_हटाओ(connector);

	connector->registration_state = DRM_CONNECTOR_UNREGISTERED;
	mutex_unlock(&connector->mutex);
पूर्ण
EXPORT_SYMBOL(drm_connector_unरेजिस्टर);

व्योम drm_connector_unरेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		drm_connector_unरेजिस्टर(connector);
	drm_connector_list_iter_end(&conn_iter);
पूर्ण

पूर्णांक drm_connector_रेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक ret = 0;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		ret = drm_connector_रेजिस्टर(connector);
		अगर (ret)
			अवरोध;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (ret)
		drm_connector_unरेजिस्टर_all(dev);
	वापस ret;
पूर्ण

/**
 * drm_get_connector_status_name - वापस a string क्रम connector status
 * @status: connector status to compute name of
 *
 * In contrast to the other drm_get_*_name functions this one here वापसs a
 * स्थिर poपूर्णांकer and hence is thपढ़ोsafe.
 */
स्थिर अक्षर *drm_get_connector_status_name(क्रमागत drm_connector_status status)
अणु
	अगर (status == connector_status_connected)
		वापस "connected";
	अन्यथा अगर (status == connector_status_disconnected)
		वापस "disconnected";
	अन्यथा
		वापस "unknown";
पूर्ण
EXPORT_SYMBOL(drm_get_connector_status_name);

/**
 * drm_get_connector_क्रमce_name - वापस a string क्रम connector क्रमce
 * @क्रमce: connector क्रमce to get name of
 *
 * Returns: स्थिर poपूर्णांकer to name.
 */
स्थिर अक्षर *drm_get_connector_क्रमce_name(क्रमागत drm_connector_क्रमce क्रमce)
अणु
	चयन (क्रमce) अणु
	हाल DRM_FORCE_UNSPECIFIED:
		वापस "unspecified";
	हाल DRM_FORCE_OFF:
		वापस "off";
	हाल DRM_FORCE_ON:
		वापस "on";
	हाल DRM_FORCE_ON_DIGITAL:
		वापस "digital";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lockdep_map connector_list_iter_dep_map = अणु
	.name = "drm_connector_list_iter"
पूर्ण;
#पूर्ण_अगर

/**
 * drm_connector_list_iter_begin - initialize a connector_list iterator
 * @dev: DRM device
 * @iter: connector_list iterator
 *
 * Sets @iter up to walk the &drm_mode_config.connector_list of @dev. @iter
 * must always be cleaned up again by calling drm_connector_list_iter_end().
 * Iteration itself happens using drm_connector_list_iter_next() or
 * drm_क्रम_each_connector_iter().
 */
व्योम drm_connector_list_iter_begin(काष्ठा drm_device *dev,
				   काष्ठा drm_connector_list_iter *iter)
अणु
	iter->dev = dev;
	iter->conn = शून्य;
	lock_acquire_shared_recursive(&connector_list_iter_dep_map, 0, 1, शून्य, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(drm_connector_list_iter_begin);

/*
 * Extra-safe connector put function that works in any context. Should only be
 * used from the connector_iter functions, where we never really expect to
 * actually release the connector when dropping our final reference.
 */
अटल व्योम
__drm_connector_put_safe(काष्ठा drm_connector *conn)
अणु
	काष्ठा drm_mode_config *config = &conn->dev->mode_config;

	lockdep_निश्चित_held(&config->connector_list_lock);

	अगर (!refcount_dec_and_test(&conn->base.refcount.refcount))
		वापस;

	llist_add(&conn->मुक्त_node, &config->connector_मुक्त_list);
	schedule_work(&config->connector_मुक्त_work);
पूर्ण

/**
 * drm_connector_list_iter_next - वापस next connector
 * @iter: connector_list iterator
 *
 * Returns the next connector क्रम @iter, or शून्य when the list walk has
 * completed.
 */
काष्ठा drm_connector *
drm_connector_list_iter_next(काष्ठा drm_connector_list_iter *iter)
अणु
	काष्ठा drm_connector *old_conn = iter->conn;
	काष्ठा drm_mode_config *config = &iter->dev->mode_config;
	काष्ठा list_head *lhead;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&config->connector_list_lock, flags);
	lhead = old_conn ? &old_conn->head : &config->connector_list;

	करो अणु
		अगर (lhead->next == &config->connector_list) अणु
			iter->conn = शून्य;
			अवरोध;
		पूर्ण

		lhead = lhead->next;
		iter->conn = list_entry(lhead, काष्ठा drm_connector, head);

		/* loop until it's not a zombie connector */
	पूर्ण जबतक (!kref_get_unless_zero(&iter->conn->base.refcount));

	अगर (old_conn)
		__drm_connector_put_safe(old_conn);
	spin_unlock_irqrestore(&config->connector_list_lock, flags);

	वापस iter->conn;
पूर्ण
EXPORT_SYMBOL(drm_connector_list_iter_next);

/**
 * drm_connector_list_iter_end - tear करोwn a connector_list iterator
 * @iter: connector_list iterator
 *
 * Tears करोwn @iter and releases any resources (like &drm_connector references)
 * acquired जबतक walking the list. This must always be called, both when the
 * iteration completes fully or when it was पातed without walking the entire
 * list.
 */
व्योम drm_connector_list_iter_end(काष्ठा drm_connector_list_iter *iter)
अणु
	काष्ठा drm_mode_config *config = &iter->dev->mode_config;
	अचिन्हित दीर्घ flags;

	iter->dev = शून्य;
	अगर (iter->conn) अणु
		spin_lock_irqsave(&config->connector_list_lock, flags);
		__drm_connector_put_safe(iter->conn);
		spin_unlock_irqrestore(&config->connector_list_lock, flags);
	पूर्ण
	lock_release(&connector_list_iter_dep_map, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(drm_connector_list_iter_end);

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_subpixel_क्रमागत_list[] = अणु
	अणु SubPixelUnknown, "Unknown" पूर्ण,
	अणु SubPixelHorizontalRGB, "Horizontal RGB" पूर्ण,
	अणु SubPixelHorizontalBGR, "Horizontal BGR" पूर्ण,
	अणु SubPixelVerticalRGB, "Vertical RGB" पूर्ण,
	अणु SubPixelVerticalBGR, "Vertical BGR" पूर्ण,
	अणु SubPixelNone, "None" पूर्ण,
पूर्ण;

/**
 * drm_get_subpixel_order_name - वापस a string क्रम a given subpixel क्रमागत
 * @order: क्रमागत of subpixel_order
 *
 * Note you could abuse this and वापस something out of bounds, but that
 * would be a caller error.  No unscrubbed user data should make it here.
 */
स्थिर अक्षर *drm_get_subpixel_order_name(क्रमागत subpixel_order order)
अणु
	वापस drm_subpixel_क्रमागत_list[order].name;
पूर्ण
EXPORT_SYMBOL(drm_get_subpixel_order_name);

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_dpms_क्रमागत_list[] = अणु
	अणु DRM_MODE_DPMS_ON, "On" पूर्ण,
	अणु DRM_MODE_DPMS_STANDBY, "Standby" पूर्ण,
	अणु DRM_MODE_DPMS_SUSPEND, "Suspend" पूर्ण,
	अणु DRM_MODE_DPMS_OFF, "Off" पूर्ण
पूर्ण;
DRM_ENUM_NAME_FN(drm_get_dpms_name, drm_dpms_क्रमागत_list)

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_link_status_क्रमागत_list[] = अणु
	अणु DRM_MODE_LINK_STATUS_GOOD, "Good" पूर्ण,
	अणु DRM_MODE_LINK_STATUS_BAD, "Bad" पूर्ण,
पूर्ण;

/**
 * drm_display_info_set_bus_क्रमmats - set the supported bus क्रमmats
 * @info: display info to store bus क्रमmats in
 * @क्रमmats: array containing the supported bus क्रमmats
 * @num_क्रमmats: the number of entries in the fmts array
 *
 * Store the supported bus क्रमmats in display info काष्ठाure.
 * See MEDIA_BUS_FMT_* definitions in include/uapi/linux/media-bus-क्रमmat.h क्रम
 * a full list of available क्रमmats.
 */
पूर्णांक drm_display_info_set_bus_क्रमmats(काष्ठा drm_display_info *info,
				     स्थिर u32 *क्रमmats,
				     अचिन्हित पूर्णांक num_क्रमmats)
अणु
	u32 *fmts = शून्य;

	अगर (!क्रमmats && num_क्रमmats)
		वापस -EINVAL;

	अगर (क्रमmats && num_क्रमmats) अणु
		fmts = kmemdup(क्रमmats, माप(*क्रमmats) * num_क्रमmats,
			       GFP_KERNEL);
		अगर (!fmts)
			वापस -ENOMEM;
	पूर्ण

	kमुक्त(info->bus_क्रमmats);
	info->bus_क्रमmats = fmts;
	info->num_bus_क्रमmats = num_क्रमmats;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_display_info_set_bus_क्रमmats);

/* Optional connector properties. */
अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_scaling_mode_क्रमागत_list[] = अणु
	अणु DRM_MODE_SCALE_NONE, "None" पूर्ण,
	अणु DRM_MODE_SCALE_FULLSCREEN, "Full" पूर्ण,
	अणु DRM_MODE_SCALE_CENTER, "Center" पूर्ण,
	अणु DRM_MODE_SCALE_ASPECT, "Full aspect" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_aspect_ratio_क्रमागत_list[] = अणु
	अणु DRM_MODE_PICTURE_ASPECT_NONE, "Automatic" पूर्ण,
	अणु DRM_MODE_PICTURE_ASPECT_4_3, "4:3" पूर्ण,
	अणु DRM_MODE_PICTURE_ASPECT_16_9, "16:9" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_content_type_क्रमागत_list[] = अणु
	अणु DRM_MODE_CONTENT_TYPE_NO_DATA, "No Data" पूर्ण,
	अणु DRM_MODE_CONTENT_TYPE_GRAPHICS, "Graphics" पूर्ण,
	अणु DRM_MODE_CONTENT_TYPE_PHOTO, "Photo" पूर्ण,
	अणु DRM_MODE_CONTENT_TYPE_CINEMA, "Cinema" पूर्ण,
	अणु DRM_MODE_CONTENT_TYPE_GAME, "Game" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_panel_orientation_क्रमागत_list[] = अणु
	अणु DRM_MODE_PANEL_ORIENTATION_NORMAL,	"Normal"	पूर्ण,
	अणु DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP,	"Upside Down"	पूर्ण,
	अणु DRM_MODE_PANEL_ORIENTATION_LEFT_UP,	"Left Side Up"	पूर्ण,
	अणु DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,	"Right Side Up"	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_dvi_i_select_क्रमागत_list[] = अणु
	अणु DRM_MODE_SUBCONNECTOR_Automatic, "Automatic" पूर्ण, /* DVI-I and TV-out */
	अणु DRM_MODE_SUBCONNECTOR_DVID,      "DVI-D"     पूर्ण, /* DVI-I  */
	अणु DRM_MODE_SUBCONNECTOR_DVIA,      "DVI-A"     पूर्ण, /* DVI-I  */
पूर्ण;
DRM_ENUM_NAME_FN(drm_get_dvi_i_select_name, drm_dvi_i_select_क्रमागत_list)

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_dvi_i_subconnector_क्रमागत_list[] = अणु
	अणु DRM_MODE_SUBCONNECTOR_Unknown,   "Unknown"   पूर्ण, /* DVI-I, TV-out and DP */
	अणु DRM_MODE_SUBCONNECTOR_DVID,      "DVI-D"     पूर्ण, /* DVI-I  */
	अणु DRM_MODE_SUBCONNECTOR_DVIA,      "DVI-A"     पूर्ण, /* DVI-I  */
पूर्ण;
DRM_ENUM_NAME_FN(drm_get_dvi_i_subconnector_name,
		 drm_dvi_i_subconnector_क्रमागत_list)

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_tv_select_क्रमागत_list[] = अणु
	अणु DRM_MODE_SUBCONNECTOR_Automatic, "Automatic" पूर्ण, /* DVI-I and TV-out */
	अणु DRM_MODE_SUBCONNECTOR_Composite, "Composite" पूर्ण, /* TV-out */
	अणु DRM_MODE_SUBCONNECTOR_SVIDEO,    "SVIDEO"    पूर्ण, /* TV-out */
	अणु DRM_MODE_SUBCONNECTOR_Component, "Component" पूर्ण, /* TV-out */
	अणु DRM_MODE_SUBCONNECTOR_SCART,     "SCART"     पूर्ण, /* TV-out */
पूर्ण;
DRM_ENUM_NAME_FN(drm_get_tv_select_name, drm_tv_select_क्रमागत_list)

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_tv_subconnector_क्रमागत_list[] = अणु
	अणु DRM_MODE_SUBCONNECTOR_Unknown,   "Unknown"   पूर्ण, /* DVI-I, TV-out and DP */
	अणु DRM_MODE_SUBCONNECTOR_Composite, "Composite" पूर्ण, /* TV-out */
	अणु DRM_MODE_SUBCONNECTOR_SVIDEO,    "SVIDEO"    पूर्ण, /* TV-out */
	अणु DRM_MODE_SUBCONNECTOR_Component, "Component" पूर्ण, /* TV-out */
	अणु DRM_MODE_SUBCONNECTOR_SCART,     "SCART"     पूर्ण, /* TV-out */
पूर्ण;
DRM_ENUM_NAME_FN(drm_get_tv_subconnector_name,
		 drm_tv_subconnector_क्रमागत_list)

अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_dp_subconnector_क्रमागत_list[] = अणु
	अणु DRM_MODE_SUBCONNECTOR_Unknown,     "Unknown"   पूर्ण, /* DVI-I, TV-out and DP */
	अणु DRM_MODE_SUBCONNECTOR_VGA,	     "VGA"       पूर्ण, /* DP */
	अणु DRM_MODE_SUBCONNECTOR_DVID,	     "DVI-D"     पूर्ण, /* DP */
	अणु DRM_MODE_SUBCONNECTOR_HDMIA,	     "HDMI"      पूर्ण, /* DP */
	अणु DRM_MODE_SUBCONNECTOR_DisplayPort, "DP"        पूर्ण, /* DP */
	अणु DRM_MODE_SUBCONNECTOR_Wireless,    "Wireless"  पूर्ण, /* DP */
	अणु DRM_MODE_SUBCONNECTOR_Native,	     "Native"    पूर्ण, /* DP */
पूर्ण;

DRM_ENUM_NAME_FN(drm_get_dp_subconnector_name,
		 drm_dp_subconnector_क्रमागत_list)

अटल स्थिर काष्ठा drm_prop_क्रमागत_list hdmi_colorspaces[] = अणु
	/* For Default हाल, driver will set the colorspace */
	अणु DRM_MODE_COLORIMETRY_DEFAULT, "Default" पूर्ण,
	/* Standard Definition Colorimetry based on CEA 861 */
	अणु DRM_MODE_COLORIMETRY_SMPTE_170M_YCC, "SMPTE_170M_YCC" पूर्ण,
	अणु DRM_MODE_COLORIMETRY_BT709_YCC, "BT709_YCC" पूर्ण,
	/* Standard Definition Colorimetry based on IEC 61966-2-4 */
	अणु DRM_MODE_COLORIMETRY_XVYCC_601, "XVYCC_601" पूर्ण,
	/* High Definition Colorimetry based on IEC 61966-2-4 */
	अणु DRM_MODE_COLORIMETRY_XVYCC_709, "XVYCC_709" पूर्ण,
	/* Colorimetry based on IEC 61966-2-1/Amendment 1 */
	अणु DRM_MODE_COLORIMETRY_SYCC_601, "SYCC_601" पूर्ण,
	/* Colorimetry based on IEC 61966-2-5 [33] */
	अणु DRM_MODE_COLORIMETRY_OPYCC_601, "opYCC_601" पूर्ण,
	/* Colorimetry based on IEC 61966-2-5 */
	अणु DRM_MODE_COLORIMETRY_OPRGB, "opRGB" पूर्ण,
	/* Colorimetry based on ITU-R BT.2020 */
	अणु DRM_MODE_COLORIMETRY_BT2020_CYCC, "BT2020_CYCC" पूर्ण,
	/* Colorimetry based on ITU-R BT.2020 */
	अणु DRM_MODE_COLORIMETRY_BT2020_RGB, "BT2020_RGB" पूर्ण,
	/* Colorimetry based on ITU-R BT.2020 */
	अणु DRM_MODE_COLORIMETRY_BT2020_YCC, "BT2020_YCC" पूर्ण,
	/* Added as part of Additional Colorimetry Extension in 861.G */
	अणु DRM_MODE_COLORIMETRY_DCI_P3_RGB_D65, "DCI-P3_RGB_D65" पूर्ण,
	अणु DRM_MODE_COLORIMETRY_DCI_P3_RGB_THEATER, "DCI-P3_RGB_Theater" पूर्ण,
पूर्ण;

/*
 * As per DP 1.4a spec, 2.2.5.7.5 VSC SDP Payload क्रम Pixel Encoding/Colorimetry
 * Format Table 2-120
 */
अटल स्थिर काष्ठा drm_prop_क्रमागत_list dp_colorspaces[] = अणु
	/* For Default हाल, driver will set the colorspace */
	अणु DRM_MODE_COLORIMETRY_DEFAULT, "Default" पूर्ण,
	अणु DRM_MODE_COLORIMETRY_RGB_WIDE_FIXED, "RGB_Wide_Gamut_Fixed_Point" पूर्ण,
	/* Colorimetry based on scRGB (IEC 61966-2-2) */
	अणु DRM_MODE_COLORIMETRY_RGB_WIDE_FLOAT, "RGB_Wide_Gamut_Floating_Point" पूर्ण,
	/* Colorimetry based on IEC 61966-2-5 */
	अणु DRM_MODE_COLORIMETRY_OPRGB, "opRGB" पूर्ण,
	/* Colorimetry based on SMPTE RP 431-2 */
	अणु DRM_MODE_COLORIMETRY_DCI_P3_RGB_D65, "DCI-P3_RGB_D65" पूर्ण,
	/* Colorimetry based on ITU-R BT.2020 */
	अणु DRM_MODE_COLORIMETRY_BT2020_RGB, "BT2020_RGB" पूर्ण,
	अणु DRM_MODE_COLORIMETRY_BT601_YCC, "BT601_YCC" पूर्ण,
	अणु DRM_MODE_COLORIMETRY_BT709_YCC, "BT709_YCC" पूर्ण,
	/* Standard Definition Colorimetry based on IEC 61966-2-4 */
	अणु DRM_MODE_COLORIMETRY_XVYCC_601, "XVYCC_601" पूर्ण,
	/* High Definition Colorimetry based on IEC 61966-2-4 */
	अणु DRM_MODE_COLORIMETRY_XVYCC_709, "XVYCC_709" पूर्ण,
	/* Colorimetry based on IEC 61966-2-1/Amendment 1 */
	अणु DRM_MODE_COLORIMETRY_SYCC_601, "SYCC_601" पूर्ण,
	/* Colorimetry based on IEC 61966-2-5 [33] */
	अणु DRM_MODE_COLORIMETRY_OPYCC_601, "opYCC_601" पूर्ण,
	/* Colorimetry based on ITU-R BT.2020 */
	अणु DRM_MODE_COLORIMETRY_BT2020_CYCC, "BT2020_CYCC" पूर्ण,
	/* Colorimetry based on ITU-R BT.2020 */
	अणु DRM_MODE_COLORIMETRY_BT2020_YCC, "BT2020_YCC" पूर्ण,
पूर्ण;

/**
 * DOC: standard connector properties
 *
 * DRM connectors have a few standardized properties:
 *
 * EDID:
 * 	Blob property which contains the current EDID पढ़ो from the sink. This
 * 	is useful to parse sink identअगरication inक्रमmation like venकरोr, model
 * 	and serial. Drivers should update this property by calling
 * 	drm_connector_update_edid_property(), usually after having parsed
 * 	the EDID using drm_add_edid_modes(). Userspace cannot change this
 * 	property.
 *
 * 	User-space should not parse the EDID to obtain inक्रमmation exposed via
 * 	other KMS properties (because the kernel might apply limits, quirks or
 * 	fixups to the EDID). For instance, user-space should not try to parse
 * 	mode lists from the EDID.
 * DPMS:
 * 	Legacy property क्रम setting the घातer state of the connector. For atomic
 * 	drivers this is only provided क्रम backwards compatibility with existing
 * 	drivers, it remaps to controlling the "ACTIVE" property on the CRTC the
 * 	connector is linked to. Drivers should never set this property directly,
 * 	it is handled by the DRM core by calling the &drm_connector_funcs.dpms
 * 	callback. For atomic drivers the remapping to the "ACTIVE" property is
 * 	implemented in the DRM core.
 *
 * 	Note that this property cannot be set through the MODE_ATOMIC ioctl,
 * 	userspace must use "ACTIVE" on the CRTC instead.
 *
 * 	WARNING:
 *
 * 	For userspace also running on legacy drivers the "DPMS" semantics are a
 * 	lot more complicated. First, userspace cannot rely on the "DPMS" value
 * 	वापसed by the GETCONNECTOR actually reflecting reality, because many
 * 	drivers fail to update it. For atomic drivers this is taken care of in
 * 	drm_atomic_helper_update_legacy_modeset_state().
 *
 * 	The second issue is that the DPMS state is only well-defined when the
 * 	connector is connected to a CRTC. In atomic the DRM core enक्रमces that
 * 	"ACTIVE" is off in such a हाल, no such checks exists क्रम "DPMS".
 *
 * 	Finally, when enabling an output using the legacy SETCONFIG ioctl then
 * 	"DPMS" is क्रमced to ON. But see above, that might not be reflected in
 * 	the software value on legacy drivers.
 *
 * 	Summarizing: Only set "DPMS" when the connector is known to be enabled,
 * 	assume that a successful SETCONFIG call also sets "DPMS" to on, and
 * 	never पढ़ो back the value of "DPMS" because it can be incorrect.
 * PATH:
 * 	Connector path property to identअगरy how this sink is physically
 * 	connected. Used by DP MST. This should be set by calling
 * 	drm_connector_set_path_property(), in the हाल of DP MST with the
 * 	path property the MST manager created. Userspace cannot change this
 * 	property.
 * TILE:
 * 	Connector tile group property to indicate how a set of DRM connector
 * 	compose together पूर्णांकo one logical screen. This is used by both high-res
 * 	बाह्यal screens (often only using a single cable, but exposing multiple
 * 	DP MST sinks), or high-res पूर्णांकegrated panels (like dual-link DSI) which
 * 	are not gen-locked. Note that क्रम tiled panels which are genlocked, like
 * 	dual-link LVDS or dual-link DSI, the driver should try to not expose the
 * 	tiling and भवise both &drm_crtc and &drm_plane अगर needed. Drivers
 * 	should update this value using drm_connector_set_tile_property().
 * 	Userspace cannot change this property.
 * link-status:
 *      Connector link-status property to indicate the status of link. The
 *      शेष value of link-status is "GOOD". If something fails during or
 *      after modeset, the kernel driver may set this to "BAD" and issue a
 *      hotplug uevent. Drivers should update this value using
 *      drm_connector_set_link_status_property().
 *
 *      When user-space receives the hotplug uevent and detects a "BAD"
 *      link-status, the sink करोesn't receive pixels anymore (e.g. the screen
 *      becomes completely black). The list of available modes may have
 *      changed. User-space is expected to pick a new mode अगर the current one
 *      has disappeared and perक्रमm a new modeset with link-status set to
 *      "GOOD" to re-enable the connector.
 *
 *      If multiple connectors share the same CRTC and one of them माला_लो a "BAD"
 *      link-status, the other are unaffected (ie. the sinks still जारी to
 *      receive pixels).
 *
 *      When user-space perक्रमms an atomic commit on a connector with a "BAD"
 *      link-status without resetting the property to "GOOD", the sink may
 *      still not receive pixels. When user-space perक्रमms an atomic commit
 *      which resets the link-status property to "GOOD" without the
 *      ALLOW_MODESET flag set, it might fail because a modeset is required.
 *
 *      User-space can only change link-status to "GOOD", changing it to "BAD"
 *      is a no-op.
 *
 *      For backwards compatibility with non-atomic userspace the kernel
 *      tries to स्वतःmatically set the link-status back to "GOOD" in the
 *      SETCRTC IOCTL. This might fail अगर the mode is no दीर्घer valid, similar
 *      to how it might fail अगर a dअगरferent screen has been connected in the
 *      पूर्णांकerim.
 * non_desktop:
 * 	Indicates the output should be ignored क्रम purposes of displaying a
 * 	standard desktop environment or console. This is most likely because
 * 	the output device is not rectilinear.
 * Content Protection:
 *	This property is used by userspace to request the kernel protect future
 *	content communicated over the link. When requested, kernel will apply
 *	the appropriate means of protection (most often HDCP), and use the
 *	property to tell userspace the protection is active.
 *
 *	Drivers can set this up by calling
 *	drm_connector_attach_content_protection_property() on initialization.
 *
 *	The value of this property can be one of the following:
 *
 *	DRM_MODE_CONTENT_PROTECTION_UNDESIRED = 0
 *		The link is not रक्षित, content is transmitted in the clear.
 *	DRM_MODE_CONTENT_PROTECTION_DESIRED = 1
 *		Userspace has requested content protection, but the link is not
 *		currently रक्षित. When in this state, kernel should enable
 *		Content Protection as soon as possible.
 *	DRM_MODE_CONTENT_PROTECTION_ENABLED = 2
 *		Userspace has requested content protection, and the link is
 *		रक्षित. Only the driver can set the property to this value.
 *		If userspace attempts to set to ENABLED, kernel will वापस
 *		-EINVAL.
 *
 *	A few guidelines:
 *
 *	- DESIRED state should be preserved until userspace de-निश्चितs it by
 *	  setting the property to UNDESIRED. This means ENABLED should only
 *	  transition to UNDESIRED when the user explicitly requests it.
 *	- If the state is DESIRED, kernel should attempt to re-authenticate the
 *	  link whenever possible. This includes across disable/enable, dpms,
 *	  hotplug, करोwnstream device changes, link status failures, etc..
 *	- Kernel sends uevent with the connector id and property id through
 *	  @drm_hdcp_update_content_protection, upon below kernel triggered
 *	  scenarios:
 *
 *		- DESIRED -> ENABLED (authentication success)
 *		- ENABLED -> DESIRED (termination of authentication)
 *	- Please note no uevents क्रम userspace triggered property state changes,
 *	  which can't fail such as
 *
 *		- DESIRED/ENABLED -> UNDESIRED
 *		- UNDESIRED -> DESIRED
 *	- Userspace is responsible क्रम polling the property or listen to uevents
 *	  to determine when the value transitions from ENABLED to DESIRED.
 *	  This signअगरies the link is no दीर्घer रक्षित and userspace should
 *	  take appropriate action (whatever that might be).
 *
 * HDCP Content Type:
 *	This Enum property is used by the userspace to declare the content type
 *	of the display stream, to kernel. Here display stream stands क्रम any
 *	display content that userspace पूर्णांकended to display through HDCP
 *	encryption.
 *
 *	Content Type of a stream is decided by the owner of the stream, as
 *	"HDCP Type0" or "HDCP Type1".
 *
 *	The value of the property can be one of the below:
 *	  - "HDCP Type0": DRM_MODE_HDCP_CONTENT_TYPE0 = 0
 *	  - "HDCP Type1": DRM_MODE_HDCP_CONTENT_TYPE1 = 1
 *
 *	When kernel starts the HDCP authentication (see "Content Protection"
 *	क्रम details), it uses the content type in "HDCP Content Type"
 *	क्रम perक्रमming the HDCP authentication with the display sink.
 *
 *	Please note in HDCP spec versions, a link can be authenticated with
 *	HDCP 2.2 क्रम Content Type 0/Content Type 1. Where as a link can be
 *	authenticated with HDCP1.4 only क्रम Content Type 0(though it is implicit
 *	in nature. As there is no reference क्रम Content Type in HDCP1.4).
 *
 *	HDCP2.2 authentication protocol itself takes the "Content Type" as a
 *	parameter, which is a input क्रम the DP HDCP2.2 encryption algo.
 *
 *	In हाल of Type 0 content protection request, kernel driver can choose
 *	either of HDCP spec versions 1.4 and 2.2. When HDCP2.2 is used क्रम
 *	"HDCP Type 0", a HDCP 2.2 capable repeater in the करोwnstream can send
 *	that content to a HDCP 1.4 authenticated HDCP sink (Type0 link).
 *	But अगर the content is classअगरied as "HDCP Type 1", above mentioned
 *	HDCP 2.2 repeater wont send the content to the HDCP sink as it can't
 *	authenticate the HDCP1.4 capable sink क्रम "HDCP Type 1".
 *
 *	Please note userspace can be ignorant of the HDCP versions used by the
 *	kernel driver to achieve the "HDCP Content Type".
 *
 *	At current scenario, classअगरying a content as Type 1 ensures that the
 *	content will be displayed only through the HDCP2.2 encrypted link.
 *
 *	Note that the HDCP Content Type property is पूर्णांकroduced at HDCP 2.2, and
 *	शेषs to type 0. It is only exposed by drivers supporting HDCP 2.2
 *	(hence supporting Type 0 and Type 1). Based on how next versions of
 *	HDCP specs are defined content Type could be used क्रम higher versions
 *	too.
 *
 *	If content type is changed when "Content Protection" is not UNDESIRED,
 *	then kernel will disable the HDCP and re-enable with new type in the
 *	same atomic commit. And when "Content Protection" is ENABLED, it means
 *	that link is HDCP authenticated and encrypted, क्रम the transmission of
 *	the Type of stream mentioned at "HDCP Content Type".
 *
 * HDR_OUTPUT_METADATA:
 *	Connector property to enable userspace to send HDR Metadata to
 *	driver. This metadata is based on the composition and blending
 *	policies decided by user, taking पूर्णांकo account the hardware and
 *	sink capabilities. The driver माला_लो this metadata and creates a
 *	Dynamic Range and Mastering Infoframe (DRM) in हाल of HDMI,
 *	SDP packet (Non-audio INFOFRAME SDP v1.3) क्रम DP. This is then
 *	sent to sink. This notअगरies the sink of the upcoming frame's Color
 *	Encoding and Luminance parameters.
 *
 *	Userspace first need to detect the HDR capabilities of sink by
 *	पढ़ोing and parsing the EDID. Details of HDR metadata क्रम HDMI
 *	are added in CTA 861.G spec. For DP , its defined in VESA DP
 *	Standard v1.4. It needs to then get the metadata inक्रमmation
 *	of the video/game/app content which are encoded in HDR (basically
 *	using HDR transfer functions). With this inक्रमmation it needs to
 *	decide on a blending policy and compose the relevant
 *	layers/overlays पूर्णांकo a common क्रमmat. Once this blending is करोne,
 *	userspace will be aware of the metadata of the composed frame to
 *	be send to sink. It then uses this property to communicate this
 *	metadata to driver which then make a Infoframe packet and sends
 *	to sink based on the type of encoder connected.
 *
 *	Userspace will be responsible to करो Tone mapping operation in हाल:
 *		- Some layers are HDR and others are SDR
 *		- HDR layers luminance is not same as sink
 *
 *	It will even need to करो colorspace conversion and get all layers
 *	to one common colorspace क्रम blending. It can use either GL, Media
 *	or display engine to get this करोne based on the capabilities of the
 *	associated hardware.
 *
 *	Driver expects metadata to be put in &काष्ठा hdr_output_metadata
 *	काष्ठाure from userspace. This is received as blob and stored in
 *	&drm_connector_state.hdr_output_metadata. It parses EDID and saves the
 *	sink metadata in &काष्ठा hdr_sink_metadata, as
 *	&drm_connector.hdr_sink_metadata.  Driver uses
 *	drm_hdmi_infoframe_set_hdr_metadata() helper to set the HDR metadata,
 *	hdmi_drm_infoframe_pack() to pack the infoframe as per spec, in हाल of
 *	HDMI encoder.
 *
 * max bpc:
 *	This range property is used by userspace to limit the bit depth. When
 *	used the driver would limit the bpc in accordance with the valid range
 *	supported by the hardware and sink. Drivers to use the function
 *	drm_connector_attach_max_bpc_property() to create and attach the
 *	property to the connector during initialization.
 *
 * Connectors also have one standardized atomic property:
 *
 * CRTC_ID:
 * 	Mode object ID of the &drm_crtc this connector should be connected to.
 *
 * Connectors क्रम LCD panels may also have one standardized property:
 *
 * panel orientation:
 *	On some devices the LCD panel is mounted in the casing in such a way
 *	that the up/top side of the panel करोes not match with the top side of
 *	the device. Userspace can use this property to check क्रम this.
 *	Note that input coordinates from touchscreens (input devices with
 *	INPUT_PROP_सूचीECT) will still map 1:1 to the actual LCD panel
 *	coordinates, so अगर userspace rotates the picture to adjust क्रम
 *	the orientation it must also apply the same transक्रमmation to the
 *	touchscreen input coordinates. This property is initialized by calling
 *	drm_connector_set_panel_orientation() or
 *	drm_connector_set_panel_orientation_with_quirk()
 *
 * scaling mode:
 *	This property defines how a non-native mode is upscaled to the native
 *	mode of an LCD panel:
 *
 *	None:
 *		No upscaling happens, scaling is left to the panel. Not all
 *		drivers expose this mode.
 *	Full:
 *		The output is upscaled to the full resolution of the panel,
 *		ignoring the aspect ratio.
 *	Center:
 *		No upscaling happens, the output is centered within the native
 *		resolution the panel.
 *	Full aspect:
 *		The output is upscaled to maximize either the width or height
 *		जबतक retaining the aspect ratio.
 *
 *	This property should be set up by calling
 *	drm_connector_attach_scaling_mode_property(). Note that drivers
 *	can also expose this property to बाह्यal outमाला_दो, in which हाल they
 *	must support "None", which should be the शेष (since बाह्यal screens
 *	have a built-in scaler).
 *
 * subconnector:
 *	This property is used by DVI-I, TVout and DisplayPort to indicate dअगरferent
 *	connector subtypes. Enum values more or less match with those from मुख्य
 *	connector types.
 *	For DVI-I and TVout there is also a matching property "select subconnector"
 *	allowing to चयन between संकेत types.
 *	DP subconnector corresponds to a करोwnstream port.
 */

पूर्णांक drm_connector_create_standard_properties(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_property *prop;

	prop = drm_property_create(dev, DRM_MODE_PROP_BLOB |
				   DRM_MODE_PROP_IMMUTABLE,
				   "EDID", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.edid_property = prop;

	prop = drm_property_create_क्रमागत(dev, 0,
				   "DPMS", drm_dpms_क्रमागत_list,
				   ARRAY_SIZE(drm_dpms_क्रमागत_list));
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.dpms_property = prop;

	prop = drm_property_create(dev,
				   DRM_MODE_PROP_BLOB |
				   DRM_MODE_PROP_IMMUTABLE,
				   "PATH", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.path_property = prop;

	prop = drm_property_create(dev,
				   DRM_MODE_PROP_BLOB |
				   DRM_MODE_PROP_IMMUTABLE,
				   "TILE", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.tile_property = prop;

	prop = drm_property_create_क्रमागत(dev, 0, "link-status",
					drm_link_status_क्रमागत_list,
					ARRAY_SIZE(drm_link_status_क्रमागत_list));
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.link_status_property = prop;

	prop = drm_property_create_bool(dev, DRM_MODE_PROP_IMMUTABLE, "non-desktop");
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.non_desktop_property = prop;

	prop = drm_property_create(dev, DRM_MODE_PROP_BLOB,
				   "HDR_OUTPUT_METADATA", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.hdr_output_metadata_property = prop;

	वापस 0;
पूर्ण

/**
 * drm_mode_create_dvi_i_properties - create DVI-I specअगरic connector properties
 * @dev: DRM device
 *
 * Called by a driver the first समय a DVI-I connector is made.
 */
पूर्णांक drm_mode_create_dvi_i_properties(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_property *dvi_i_selector;
	काष्ठा drm_property *dvi_i_subconnector;

	अगर (dev->mode_config.dvi_i_select_subconnector_property)
		वापस 0;

	dvi_i_selector =
		drm_property_create_क्रमागत(dev, 0,
				    "select subconnector",
				    drm_dvi_i_select_क्रमागत_list,
				    ARRAY_SIZE(drm_dvi_i_select_क्रमागत_list));
	dev->mode_config.dvi_i_select_subconnector_property = dvi_i_selector;

	dvi_i_subconnector = drm_property_create_क्रमागत(dev, DRM_MODE_PROP_IMMUTABLE,
				    "subconnector",
				    drm_dvi_i_subconnector_क्रमागत_list,
				    ARRAY_SIZE(drm_dvi_i_subconnector_क्रमागत_list));
	dev->mode_config.dvi_i_subconnector_property = dvi_i_subconnector;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_dvi_i_properties);

/**
 * drm_connector_attach_dp_subconnector_property - create subconnector property क्रम DP
 * @connector: drm_connector to attach property
 *
 * Called by a driver when DP connector is created.
 */
व्योम drm_connector_attach_dp_subconnector_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_mode_config *mode_config = &connector->dev->mode_config;

	अगर (!mode_config->dp_subconnector_property)
		mode_config->dp_subconnector_property =
			drm_property_create_क्रमागत(connector->dev,
				DRM_MODE_PROP_IMMUTABLE,
				"subconnector",
				drm_dp_subconnector_क्रमागत_list,
				ARRAY_SIZE(drm_dp_subconnector_क्रमागत_list));

	drm_object_attach_property(&connector->base,
				   mode_config->dp_subconnector_property,
				   DRM_MODE_SUBCONNECTOR_Unknown);
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_dp_subconnector_property);

/**
 * DOC: HDMI connector properties
 *
 * content type (HDMI specअगरic):
 *	Indicates content type setting to be used in HDMI infoframes to indicate
 *	content type क्रम the बाह्यal device, so that it adjusts its display
 *	settings accordingly.
 *
 *	The value of this property can be one of the following:
 *
 *	No Data:
 *		Content type is unknown
 *	Graphics:
 *		Content type is graphics
 *	Photo:
 *		Content type is photo
 *	Cinema:
 *		Content type is cinema
 *	Game:
 *		Content type is game
 *
 *	Drivers can set up this property by calling
 *	drm_connector_attach_content_type_property(). Decoding to
 *	infoframe values is करोne through drm_hdmi_avi_infoframe_content_type().
 */

/**
 * drm_connector_attach_content_type_property - attach content-type property
 * @connector: connector to attach content type property on.
 *
 * Called by a driver the first समय a HDMI connector is made.
 */
पूर्णांक drm_connector_attach_content_type_property(काष्ठा drm_connector *connector)
अणु
	अगर (!drm_mode_create_content_type_property(connector->dev))
		drm_object_attach_property(&connector->base,
					   connector->dev->mode_config.content_type_property,
					   DRM_MODE_CONTENT_TYPE_NO_DATA);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_content_type_property);


/**
 * drm_hdmi_avi_infoframe_content_type() - fill the HDMI AVI infoframe
 *                                         content type inक्रमmation, based
 *                                         on correspondent DRM property.
 * @frame: HDMI AVI infoframe
 * @conn_state: DRM display connector state
 *
 */
व्योम drm_hdmi_avi_infoframe_content_type(काष्ठा hdmi_avi_infoframe *frame,
					 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	चयन (conn_state->content_type) अणु
	हाल DRM_MODE_CONTENT_TYPE_GRAPHICS:
		frame->content_type = HDMI_CONTENT_TYPE_GRAPHICS;
		अवरोध;
	हाल DRM_MODE_CONTENT_TYPE_CINEMA:
		frame->content_type = HDMI_CONTENT_TYPE_CINEMA;
		अवरोध;
	हाल DRM_MODE_CONTENT_TYPE_GAME:
		frame->content_type = HDMI_CONTENT_TYPE_GAME;
		अवरोध;
	हाल DRM_MODE_CONTENT_TYPE_PHOTO:
		frame->content_type = HDMI_CONTENT_TYPE_PHOTO;
		अवरोध;
	शेष:
		/* Graphics is the शेष(0) */
		frame->content_type = HDMI_CONTENT_TYPE_GRAPHICS;
	पूर्ण

	frame->itc = conn_state->content_type != DRM_MODE_CONTENT_TYPE_NO_DATA;
पूर्ण
EXPORT_SYMBOL(drm_hdmi_avi_infoframe_content_type);

/**
 * drm_connector_attach_tv_margin_properties - attach TV connector margin
 * 	properties
 * @connector: DRM connector
 *
 * Called by a driver when it needs to attach TV margin props to a connector.
 * Typically used on SDTV and HDMI connectors.
 */
व्योम drm_connector_attach_tv_margin_properties(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_left_margin_property,
				   0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_right_margin_property,
				   0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_top_margin_property,
				   0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_bottom_margin_property,
				   0);
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_tv_margin_properties);

/**
 * drm_mode_create_tv_margin_properties - create TV connector margin properties
 * @dev: DRM device
 *
 * Called by a driver's HDMI connector initialization routine, this function
 * creates the TV margin properties क्रम a given device. No need to call this
 * function क्रम an SDTV connector, it's alपढ़ोy called from
 * drm_mode_create_tv_properties().
 */
पूर्णांक drm_mode_create_tv_margin_properties(काष्ठा drm_device *dev)
अणु
	अगर (dev->mode_config.tv_left_margin_property)
		वापस 0;

	dev->mode_config.tv_left_margin_property =
		drm_property_create_range(dev, 0, "left margin", 0, 100);
	अगर (!dev->mode_config.tv_left_margin_property)
		वापस -ENOMEM;

	dev->mode_config.tv_right_margin_property =
		drm_property_create_range(dev, 0, "right margin", 0, 100);
	अगर (!dev->mode_config.tv_right_margin_property)
		वापस -ENOMEM;

	dev->mode_config.tv_top_margin_property =
		drm_property_create_range(dev, 0, "top margin", 0, 100);
	अगर (!dev->mode_config.tv_top_margin_property)
		वापस -ENOMEM;

	dev->mode_config.tv_bottom_margin_property =
		drm_property_create_range(dev, 0, "bottom margin", 0, 100);
	अगर (!dev->mode_config.tv_bottom_margin_property)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_tv_margin_properties);

/**
 * drm_mode_create_tv_properties - create TV specअगरic connector properties
 * @dev: DRM device
 * @num_modes: number of dअगरferent TV क्रमmats (modes) supported
 * @modes: array of poपूर्णांकers to strings containing name of each क्रमmat
 *
 * Called by a driver's TV initialization routine, this function creates
 * the TV specअगरic connector properties क्रम a given device.  Caller is
 * responsible क्रम allocating a list of क्रमmat names and passing them to
 * this routine.
 */
पूर्णांक drm_mode_create_tv_properties(काष्ठा drm_device *dev,
				  अचिन्हित पूर्णांक num_modes,
				  स्थिर अक्षर * स्थिर modes[])
अणु
	काष्ठा drm_property *tv_selector;
	काष्ठा drm_property *tv_subconnector;
	अचिन्हित पूर्णांक i;

	अगर (dev->mode_config.tv_select_subconnector_property)
		वापस 0;

	/*
	 * Basic connector properties
	 */
	tv_selector = drm_property_create_क्रमागत(dev, 0,
					  "select subconnector",
					  drm_tv_select_क्रमागत_list,
					  ARRAY_SIZE(drm_tv_select_क्रमागत_list));
	अगर (!tv_selector)
		जाओ nomem;

	dev->mode_config.tv_select_subconnector_property = tv_selector;

	tv_subconnector =
		drm_property_create_क्रमागत(dev, DRM_MODE_PROP_IMMUTABLE,
				    "subconnector",
				    drm_tv_subconnector_क्रमागत_list,
				    ARRAY_SIZE(drm_tv_subconnector_क्रमागत_list));
	अगर (!tv_subconnector)
		जाओ nomem;
	dev->mode_config.tv_subconnector_property = tv_subconnector;

	/*
	 * Other, TV specअगरic properties: margins & TV modes.
	 */
	अगर (drm_mode_create_tv_margin_properties(dev))
		जाओ nomem;

	dev->mode_config.tv_mode_property =
		drm_property_create(dev, DRM_MODE_PROP_ENUM,
				    "mode", num_modes);
	अगर (!dev->mode_config.tv_mode_property)
		जाओ nomem;

	क्रम (i = 0; i < num_modes; i++)
		drm_property_add_क्रमागत(dev->mode_config.tv_mode_property,
				      i, modes[i]);

	dev->mode_config.tv_brightness_property =
		drm_property_create_range(dev, 0, "brightness", 0, 100);
	अगर (!dev->mode_config.tv_brightness_property)
		जाओ nomem;

	dev->mode_config.tv_contrast_property =
		drm_property_create_range(dev, 0, "contrast", 0, 100);
	अगर (!dev->mode_config.tv_contrast_property)
		जाओ nomem;

	dev->mode_config.tv_flicker_reduction_property =
		drm_property_create_range(dev, 0, "flicker reduction", 0, 100);
	अगर (!dev->mode_config.tv_flicker_reduction_property)
		जाओ nomem;

	dev->mode_config.tv_overscan_property =
		drm_property_create_range(dev, 0, "overscan", 0, 100);
	अगर (!dev->mode_config.tv_overscan_property)
		जाओ nomem;

	dev->mode_config.tv_saturation_property =
		drm_property_create_range(dev, 0, "saturation", 0, 100);
	अगर (!dev->mode_config.tv_saturation_property)
		जाओ nomem;

	dev->mode_config.tv_hue_property =
		drm_property_create_range(dev, 0, "hue", 0, 100);
	अगर (!dev->mode_config.tv_hue_property)
		जाओ nomem;

	वापस 0;
nomem:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_tv_properties);

/**
 * drm_mode_create_scaling_mode_property - create scaling mode property
 * @dev: DRM device
 *
 * Called by a driver the first समय it's needed, must be attached to desired
 * connectors.
 *
 * Atomic drivers should use drm_connector_attach_scaling_mode_property()
 * instead to correctly assign &drm_connector_state.picture_aspect_ratio
 * in the atomic state.
 */
पूर्णांक drm_mode_create_scaling_mode_property(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_property *scaling_mode;

	अगर (dev->mode_config.scaling_mode_property)
		वापस 0;

	scaling_mode =
		drm_property_create_क्रमागत(dev, 0, "scaling mode",
				drm_scaling_mode_क्रमागत_list,
				    ARRAY_SIZE(drm_scaling_mode_क्रमागत_list));

	dev->mode_config.scaling_mode_property = scaling_mode;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_scaling_mode_property);

/**
 * DOC: Variable refresh properties
 *
 * Variable refresh rate capable displays can dynamically adjust their
 * refresh rate by extending the duration of their vertical front porch
 * until page flip or समयout occurs. This can reduce or हटाओ stuttering
 * and latency in scenarios where the page flip करोes not align with the
 * vblank पूर्णांकerval.
 *
 * An example scenario would be an application flipping at a स्थिरant rate
 * of 48Hz on a 60Hz display. The page flip will frequently miss the vblank
 * पूर्णांकerval and the same contents will be displayed twice. This can be
 * observed as stuttering क्रम content with motion.
 *
 * If variable refresh rate was active on a display that supported a
 * variable refresh range from 35Hz to 60Hz no stuttering would be observable
 * क्रम the example scenario. The minimum supported variable refresh rate of
 * 35Hz is below the page flip frequency and the vertical front porch can
 * be extended until the page flip occurs. The vblank पूर्णांकerval will be
 * directly aligned to the page flip rate.
 *
 * Not all userspace content is suitable क्रम use with variable refresh rate.
 * Large and frequent changes in vertical front porch duration may worsen
 * perceived stuttering क्रम input sensitive applications.
 *
 * Panel brightness will also vary with vertical front porch duration. Some
 * panels may have noticeable dअगरferences in brightness between the minimum
 * vertical front porch duration and the maximum vertical front porch duration.
 * Large and frequent changes in vertical front porch duration may produce
 * observable flickering क्रम such panels.
 *
 * Userspace control क्रम variable refresh rate is supported via properties
 * on the &drm_connector and &drm_crtc objects.
 *
 * "vrr_capable":
 *	Optional &drm_connector boolean property that drivers should attach
 *	with drm_connector_attach_vrr_capable_property() on connectors that
 *	could support variable refresh rates. Drivers should update the
 *	property value by calling drm_connector_set_vrr_capable_property().
 *
 *	Absence of the property should indicate असलence of support.
 *
 * "VRR_ENABLED":
 *	Default &drm_crtc boolean property that notअगरies the driver that the
 *	content on the CRTC is suitable क्रम variable refresh rate presentation.
 *	The driver will take this property as a hपूर्णांक to enable variable
 *	refresh rate support अगर the receiver supports it, ie. अगर the
 *	"vrr_capable" property is true on the &drm_connector object. The
 *	vertical front porch duration will be extended until page-flip or
 *	समयout when enabled.
 *
 *	The minimum vertical front porch duration is defined as the vertical
 *	front porch duration क्रम the current mode.
 *
 *	The maximum vertical front porch duration is greater than or equal to
 *	the minimum vertical front porch duration. The duration is derived
 *	from the minimum supported variable refresh rate क्रम the connector.
 *
 *	The driver may place further restrictions within these minimum
 *	and maximum bounds.
 */

/**
 * drm_connector_attach_vrr_capable_property - creates the
 * vrr_capable property
 * @connector: connector to create the vrr_capable property on.
 *
 * This is used by atomic drivers to add support क्रम querying
 * variable refresh rate capability क्रम a connector.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_attach_vrr_capable_property(
	काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_property *prop;

	अगर (!connector->vrr_capable_property) अणु
		prop = drm_property_create_bool(dev, DRM_MODE_PROP_IMMUTABLE,
			"vrr_capable");
		अगर (!prop)
			वापस -ENOMEM;

		connector->vrr_capable_property = prop;
		drm_object_attach_property(&connector->base, prop, 0);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_vrr_capable_property);

/**
 * drm_connector_attach_scaling_mode_property - attach atomic scaling mode property
 * @connector: connector to attach scaling mode property on.
 * @scaling_mode_mask: or'ed mask of BIT(%DRM_MODE_SCALE_\*).
 *
 * This is used to add support क्रम scaling mode to atomic drivers.
 * The scaling mode will be set to &drm_connector_state.picture_aspect_ratio
 * and can be used from &drm_connector_helper_funcs->atomic_check क्रम validation.
 *
 * This is the atomic version of drm_mode_create_scaling_mode_property().
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_attach_scaling_mode_property(काष्ठा drm_connector *connector,
					       u32 scaling_mode_mask)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_property *scaling_mode_property;
	पूर्णांक i;
	स्थिर अचिन्हित valid_scaling_mode_mask =
		(1U << ARRAY_SIZE(drm_scaling_mode_क्रमागत_list)) - 1;

	अगर (WARN_ON(hweight32(scaling_mode_mask) < 2 ||
		    scaling_mode_mask & ~valid_scaling_mode_mask))
		वापस -EINVAL;

	scaling_mode_property =
		drm_property_create(dev, DRM_MODE_PROP_ENUM, "scaling mode",
				    hweight32(scaling_mode_mask));

	अगर (!scaling_mode_property)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(drm_scaling_mode_क्रमागत_list); i++) अणु
		पूर्णांक ret;

		अगर (!(BIT(i) & scaling_mode_mask))
			जारी;

		ret = drm_property_add_क्रमागत(scaling_mode_property,
					    drm_scaling_mode_क्रमागत_list[i].type,
					    drm_scaling_mode_क्रमागत_list[i].name);

		अगर (ret) अणु
			drm_property_destroy(dev, scaling_mode_property);

			वापस ret;
		पूर्ण
	पूर्ण

	drm_object_attach_property(&connector->base,
				   scaling_mode_property, 0);

	connector->scaling_mode_property = scaling_mode_property;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_scaling_mode_property);

/**
 * drm_mode_create_aspect_ratio_property - create aspect ratio property
 * @dev: DRM device
 *
 * Called by a driver the first समय it's needed, must be attached to desired
 * connectors.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_create_aspect_ratio_property(काष्ठा drm_device *dev)
अणु
	अगर (dev->mode_config.aspect_ratio_property)
		वापस 0;

	dev->mode_config.aspect_ratio_property =
		drm_property_create_क्रमागत(dev, 0, "aspect ratio",
				drm_aspect_ratio_क्रमागत_list,
				ARRAY_SIZE(drm_aspect_ratio_क्रमागत_list));

	अगर (dev->mode_config.aspect_ratio_property == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_aspect_ratio_property);

/**
 * DOC: standard connector properties
 *
 * Colorspace:
 *     This property helps select a suitable colorspace based on the sink
 *     capability. Modern sink devices support wider gamut like BT2020.
 *     This helps चयन to BT2020 mode अगर the BT2020 encoded video stream
 *     is being played by the user, same क्रम any other colorspace. Thereby
 *     giving a good visual experience to users.
 *
 *     The expectation from userspace is that it should parse the EDID
 *     and get supported colorspaces. Use this property and चयन to the
 *     one supported. Sink supported colorspaces should be retrieved by
 *     userspace from EDID and driver will not explicitly expose them.
 *
 *     Basically the expectation from userspace is:
 *      - Set up CRTC DEGAMMA/CTM/GAMMA to convert to some sink
 *        colorspace
 *      - Set this new property to let the sink know what it
 *        converted the CRTC output to.
 *      - This property is just to inक्रमm sink what colorspace
 *        source is trying to drive.
 *
 * Because between HDMI and DP have dअगरferent colorspaces,
 * drm_mode_create_hdmi_colorspace_property() is used क्रम HDMI connector and
 * drm_mode_create_dp_colorspace_property() is used क्रम DP connector.
 */

/**
 * drm_mode_create_hdmi_colorspace_property - create hdmi colorspace property
 * @connector: connector to create the Colorspace property on.
 *
 * Called by a driver the first समय it's needed, must be attached to desired
 * HDMI connectors.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_create_hdmi_colorspace_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	अगर (connector->colorspace_property)
		वापस 0;

	connector->colorspace_property =
		drm_property_create_क्रमागत(dev, DRM_MODE_PROP_ENUM, "Colorspace",
					 hdmi_colorspaces,
					 ARRAY_SIZE(hdmi_colorspaces));

	अगर (!connector->colorspace_property)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_hdmi_colorspace_property);

/**
 * drm_mode_create_dp_colorspace_property - create dp colorspace property
 * @connector: connector to create the Colorspace property on.
 *
 * Called by a driver the first समय it's needed, must be attached to desired
 * DP connectors.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_create_dp_colorspace_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	अगर (connector->colorspace_property)
		वापस 0;

	connector->colorspace_property =
		drm_property_create_क्रमागत(dev, DRM_MODE_PROP_ENUM, "Colorspace",
					 dp_colorspaces,
					 ARRAY_SIZE(dp_colorspaces));

	अगर (!connector->colorspace_property)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_dp_colorspace_property);

/**
 * drm_mode_create_content_type_property - create content type property
 * @dev: DRM device
 *
 * Called by a driver the first समय it's needed, must be attached to desired
 * connectors.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_create_content_type_property(काष्ठा drm_device *dev)
अणु
	अगर (dev->mode_config.content_type_property)
		वापस 0;

	dev->mode_config.content_type_property =
		drm_property_create_क्रमागत(dev, 0, "content type",
					 drm_content_type_क्रमागत_list,
					 ARRAY_SIZE(drm_content_type_क्रमागत_list));

	अगर (dev->mode_config.content_type_property == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_content_type_property);

/**
 * drm_mode_create_suggested_offset_properties - create suggests offset properties
 * @dev: DRM device
 *
 * Create the suggested x/y offset property क्रम connectors.
 */
पूर्णांक drm_mode_create_suggested_offset_properties(काष्ठा drm_device *dev)
अणु
	अगर (dev->mode_config.suggested_x_property && dev->mode_config.suggested_y_property)
		वापस 0;

	dev->mode_config.suggested_x_property =
		drm_property_create_range(dev, DRM_MODE_PROP_IMMUTABLE, "suggested X", 0, 0xffffffff);

	dev->mode_config.suggested_y_property =
		drm_property_create_range(dev, DRM_MODE_PROP_IMMUTABLE, "suggested Y", 0, 0xffffffff);

	अगर (dev->mode_config.suggested_x_property == शून्य ||
	    dev->mode_config.suggested_y_property == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_suggested_offset_properties);

/**
 * drm_connector_set_path_property - set tile property on connector
 * @connector: connector to set property on.
 * @path: path to use क्रम property; must not be शून्य.
 *
 * This creates a property to expose to userspace to specअगरy a
 * connector path. This is मुख्यly used क्रम DisplayPort MST where
 * connectors have a topology and we want to allow userspace to give
 * them more meaningful names.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_set_path_property(काष्ठा drm_connector *connector,
				    स्थिर अक्षर *path)
अणु
	काष्ठा drm_device *dev = connector->dev;
	पूर्णांक ret;

	ret = drm_property_replace_global_blob(dev,
	                                       &connector->path_blob_ptr,
	                                       म_माप(path) + 1,
	                                       path,
	                                       &connector->base,
	                                       dev->mode_config.path_property);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_connector_set_path_property);

/**
 * drm_connector_set_tile_property - set tile property on connector
 * @connector: connector to set property on.
 *
 * This looks up the tile inक्रमmation क्रम a connector, and creates a
 * property क्रम userspace to parse अगर it exists. The property is of
 * the क्रमm of 8 पूर्णांकegers using ':' as a separator.
 * This is used क्रम dual port tiled displays with DisplayPort SST
 * or DisplayPort MST connectors.
 *
 * Returns:
 * Zero on success, त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_set_tile_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	अक्षर tile[256];
	पूर्णांक ret;

	अगर (!connector->has_tile) अणु
		ret  = drm_property_replace_global_blob(dev,
		                                        &connector->tile_blob_ptr,
		                                        0,
		                                        शून्य,
		                                        &connector->base,
		                                        dev->mode_config.tile_property);
		वापस ret;
	पूर्ण

	snम_लिखो(tile, 256, "%d:%d:%d:%d:%d:%d:%d:%d",
		 connector->tile_group->id, connector->tile_is_single_monitor,
		 connector->num_h_tile, connector->num_v_tile,
		 connector->tile_h_loc, connector->tile_v_loc,
		 connector->tile_h_size, connector->tile_v_size);

	ret = drm_property_replace_global_blob(dev,
	                                       &connector->tile_blob_ptr,
	                                       म_माप(tile) + 1,
	                                       tile,
	                                       &connector->base,
	                                       dev->mode_config.tile_property);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_connector_set_tile_property);

/**
 * drm_connector_update_edid_property - update the edid property of a connector
 * @connector: drm connector
 * @edid: new value of the edid property
 *
 * This function creates a new blob modeset object and assigns its id to the
 * connector's edid property.
 * Since we also parse tile inक्रमmation from EDID's displayID block, we also
 * set the connector's tile property here. See drm_connector_set_tile_property()
 * क्रम more details.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_update_edid_property(काष्ठा drm_connector *connector,
				       स्थिर काष्ठा edid *edid)
अणु
	काष्ठा drm_device *dev = connector->dev;
	माप_प्रकार size = 0;
	पूर्णांक ret;
	स्थिर काष्ठा edid *old_edid;

	/* ignore requests to set edid when overridden */
	अगर (connector->override_edid)
		वापस 0;

	अगर (edid)
		size = EDID_LENGTH * (1 + edid->extensions);

	/* Set the display info, using edid अगर available, otherwise
	 * resetting the values to शेषs. This duplicates the work
	 * करोne in drm_add_edid_modes, but that function is not
	 * consistently called beक्रमe this one in all drivers and the
	 * computation is cheap enough that it seems better to
	 * duplicate it rather than attempt to ensure some arbitrary
	 * ordering of calls.
	 */
	अगर (edid)
		drm_add_display_info(connector, edid);
	अन्यथा
		drm_reset_display_info(connector);

	drm_update_tile_info(connector, edid);

	अगर (connector->edid_blob_ptr) अणु
		old_edid = (स्थिर काष्ठा edid *)connector->edid_blob_ptr->data;
		अगर (old_edid) अणु
			अगर (!drm_edid_are_equal(edid, old_edid)) अणु
				DRM_DEBUG_KMS("[CONNECTOR:%d:%s] Edid was changed.\n",
					      connector->base.id, connector->name);

				connector->epoch_counter += 1;
				DRM_DEBUG_KMS("Updating change counter to %llu\n",
					      connector->epoch_counter);
			पूर्ण
		पूर्ण
	पूर्ण

	drm_object_property_set_value(&connector->base,
				      dev->mode_config.non_desktop_property,
				      connector->display_info.non_desktop);

	ret = drm_property_replace_global_blob(dev,
					       &connector->edid_blob_ptr,
	                                       size,
	                                       edid,
	                                       &connector->base,
	                                       dev->mode_config.edid_property);
	अगर (ret)
		वापस ret;
	वापस drm_connector_set_tile_property(connector);
पूर्ण
EXPORT_SYMBOL(drm_connector_update_edid_property);

/**
 * drm_connector_set_link_status_property - Set link status property of a connector
 * @connector: drm connector
 * @link_status: new value of link status property (0: Good, 1: Bad)
 *
 * In usual working scenario, this link status property will always be set to
 * "GOOD". If something fails during or after a mode set, the kernel driver
 * may set this link status property to "BAD". The caller then needs to send a
 * hotplug uevent क्रम userspace to re-check the valid modes through
 * GET_CONNECTOR_IOCTL and retry modeset.
 *
 * Note: Drivers cannot rely on userspace to support this property and
 * issue a modeset. As such, they may choose to handle issues (like
 * re-training a link) without userspace's पूर्णांकervention.
 *
 * The reason क्रम adding this property is to handle link training failures, but
 * it is not limited to DP or link training. For example, अगर we implement
 * asynchronous setcrtc, this property can be used to report any failures in that.
 */
व्योम drm_connector_set_link_status_property(काष्ठा drm_connector *connector,
					    uपूर्णांक64_t link_status)
अणु
	काष्ठा drm_device *dev = connector->dev;

	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);
	connector->state->link_status = link_status;
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
पूर्ण
EXPORT_SYMBOL(drm_connector_set_link_status_property);

/**
 * drm_connector_attach_max_bpc_property - attach "max bpc" property
 * @connector: connector to attach max bpc property on.
 * @min: The minimum bit depth supported by the connector.
 * @max: The maximum bit depth supported by the connector.
 *
 * This is used to add support क्रम limiting the bit depth on a connector.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_attach_max_bpc_property(काष्ठा drm_connector *connector,
					  पूर्णांक min, पूर्णांक max)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_property *prop;

	prop = connector->max_bpc_property;
	अगर (!prop) अणु
		prop = drm_property_create_range(dev, 0, "max bpc", min, max);
		अगर (!prop)
			वापस -ENOMEM;

		connector->max_bpc_property = prop;
	पूर्ण

	drm_object_attach_property(&connector->base, prop, max);
	connector->state->max_requested_bpc = max;
	connector->state->max_bpc = max;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_max_bpc_property);

/**
 * drm_connector_set_vrr_capable_property - sets the variable refresh rate
 * capable property क्रम a connector
 * @connector: drm connector
 * @capable: True अगर the connector is variable refresh rate capable
 *
 * Should be used by atomic drivers to update the indicated support क्रम
 * variable refresh rate over a connector.
 */
व्योम drm_connector_set_vrr_capable_property(
		काष्ठा drm_connector *connector, bool capable)
अणु
	drm_object_property_set_value(&connector->base,
				      connector->vrr_capable_property,
				      capable);
पूर्ण
EXPORT_SYMBOL(drm_connector_set_vrr_capable_property);

/**
 * drm_connector_set_panel_orientation - sets the connector's panel_orientation
 * @connector: connector क्रम which to set the panel-orientation property.
 * @panel_orientation: drm_panel_orientation value to set
 *
 * This function sets the connector's panel_orientation and attaches
 * a "panel orientation" property to the connector.
 *
 * Calling this function on a connector where the panel_orientation has
 * alपढ़ोy been set is a no-op (e.g. the orientation has been overridden with
 * a kernel commandline option).
 *
 * It is allowed to call this function with a panel_orientation of
 * DRM_MODE_PANEL_ORIENTATION_UNKNOWN, in which हाल it is a no-op.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_set_panel_orientation(
	काष्ठा drm_connector *connector,
	क्रमागत drm_panel_orientation panel_orientation)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_info *info = &connector->display_info;
	काष्ठा drm_property *prop;

	/* Alपढ़ोy set? */
	अगर (info->panel_orientation != DRM_MODE_PANEL_ORIENTATION_UNKNOWN)
		वापस 0;

	/* Don't attach the property अगर the orientation is unknown */
	अगर (panel_orientation == DRM_MODE_PANEL_ORIENTATION_UNKNOWN)
		वापस 0;

	info->panel_orientation = panel_orientation;

	prop = dev->mode_config.panel_orientation_property;
	अगर (!prop) अणु
		prop = drm_property_create_क्रमागत(dev, DRM_MODE_PROP_IMMUTABLE,
				"panel orientation",
				drm_panel_orientation_क्रमागत_list,
				ARRAY_SIZE(drm_panel_orientation_क्रमागत_list));
		अगर (!prop)
			वापस -ENOMEM;

		dev->mode_config.panel_orientation_property = prop;
	पूर्ण

	drm_object_attach_property(&connector->base, prop,
				   info->panel_orientation);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_connector_set_panel_orientation);

/**
 * drm_connector_set_panel_orientation_with_quirk -
 *	set the connector's panel_orientation after checking क्रम quirks
 * @connector: connector क्रम which to init the panel-orientation property.
 * @panel_orientation: drm_panel_orientation value to set
 * @width: width in pixels of the panel, used क्रम panel quirk detection
 * @height: height in pixels of the panel, used क्रम panel quirk detection
 *
 * Like drm_connector_set_panel_orientation(), but with a check क्रम platक्रमm
 * specअगरic (e.g. DMI based) quirks overriding the passed in panel_orientation.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_set_panel_orientation_with_quirk(
	काष्ठा drm_connector *connector,
	क्रमागत drm_panel_orientation panel_orientation,
	पूर्णांक width, पूर्णांक height)
अणु
	पूर्णांक orientation_quirk;

	orientation_quirk = drm_get_panel_orientation_quirk(width, height);
	अगर (orientation_quirk != DRM_MODE_PANEL_ORIENTATION_UNKNOWN)
		panel_orientation = orientation_quirk;

	वापस drm_connector_set_panel_orientation(connector,
						   panel_orientation);
पूर्ण
EXPORT_SYMBOL(drm_connector_set_panel_orientation_with_quirk);

पूर्णांक drm_connector_set_obj_prop(काष्ठा drm_mode_object *obj,
				    काष्ठा drm_property *property,
				    uपूर्णांक64_t value)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा drm_connector *connector = obj_to_connector(obj);

	/* Do DPMS ourselves */
	अगर (property == connector->dev->mode_config.dpms_property) अणु
		ret = (*connector->funcs->dpms)(connector, (पूर्णांक)value);
	पूर्ण अन्यथा अगर (connector->funcs->set_property)
		ret = connector->funcs->set_property(connector, property, value);

	अगर (!ret)
		drm_object_property_set_value(&connector->base, property, value);
	वापस ret;
पूर्ण

पूर्णांक drm_connector_property_set_ioctl(काष्ठा drm_device *dev,
				     व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_connector_set_property *conn_set_prop = data;
	काष्ठा drm_mode_obj_set_property obj_set_prop = अणु
		.value = conn_set_prop->value,
		.prop_id = conn_set_prop->prop_id,
		.obj_id = conn_set_prop->connector_id,
		.obj_type = DRM_MODE_OBJECT_CONNECTOR
	पूर्ण;

	/* It करोes all the locking and checking we need */
	वापस drm_mode_obj_set_property_ioctl(dev, &obj_set_prop, file_priv);
पूर्ण

अटल काष्ठा drm_encoder *drm_connector_get_encoder(काष्ठा drm_connector *connector)
अणु
	/* For atomic drivers only state objects are synchronously updated and
	 * रक्षित by modeset locks, so check those first. */
	अगर (connector->state)
		वापस connector->state->best_encoder;
	वापस connector->encoder;
पूर्ण

अटल bool
drm_mode_expose_to_userspace(स्थिर काष्ठा drm_display_mode *mode,
			     स्थिर काष्ठा list_head *modes,
			     स्थिर काष्ठा drm_file *file_priv)
अणु
	/*
	 * If user-space hasn't configured the driver to expose the stereo 3D
	 * modes, करोn't expose them.
	 */
	अगर (!file_priv->stereo_allowed && drm_mode_is_stereo(mode))
		वापस false;
	/*
	 * If user-space hasn't configured the driver to expose the modes
	 * with aspect-ratio, करोn't expose them. However अगर such a mode
	 * is unique, let it be exposed, but reset the aspect-ratio flags
	 * जबतक preparing the list of user-modes.
	 */
	अगर (!file_priv->aspect_ratio_allowed) अणु
		स्थिर काष्ठा drm_display_mode *mode_itr;

		list_क्रम_each_entry(mode_itr, modes, head) अणु
			अगर (mode_itr->expose_to_userspace &&
			    drm_mode_match(mode_itr, mode,
					   DRM_MODE_MATCH_TIMINGS |
					   DRM_MODE_MATCH_CLOCK |
					   DRM_MODE_MATCH_FLAGS |
					   DRM_MODE_MATCH_3D_FLAGS))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक drm_mode_अ_लोonnector(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_get_connector *out_resp = data;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_display_mode *mode;
	पूर्णांक mode_count = 0;
	पूर्णांक encoders_count = 0;
	पूर्णांक ret = 0;
	पूर्णांक copied = 0;
	काष्ठा drm_mode_modeinfo u_mode;
	काष्ठा drm_mode_modeinfo __user *mode_ptr;
	uपूर्णांक32_t __user *encoder_ptr;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	स_रखो(&u_mode, 0, माप(काष्ठा drm_mode_modeinfo));

	connector = drm_connector_lookup(dev, file_priv, out_resp->connector_id);
	अगर (!connector)
		वापस -ENOENT;

	encoders_count = hweight32(connector->possible_encoders);

	अगर ((out_resp->count_encoders >= encoders_count) && encoders_count) अणु
		copied = 0;
		encoder_ptr = (uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)(out_resp->encoders_ptr);

		drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
			अगर (put_user(encoder->base.id, encoder_ptr + copied)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
			copied++;
		पूर्ण
	पूर्ण
	out_resp->count_encoders = encoders_count;

	out_resp->connector_id = connector->base.id;
	out_resp->connector_type = connector->connector_type;
	out_resp->connector_type_id = connector->connector_type_id;

	mutex_lock(&dev->mode_config.mutex);
	अगर (out_resp->count_modes == 0) अणु
		connector->funcs->fill_modes(connector,
					     dev->mode_config.max_width,
					     dev->mode_config.max_height);
	पूर्ण

	out_resp->mm_width = connector->display_info.width_mm;
	out_resp->mm_height = connector->display_info.height_mm;
	out_resp->subpixel = connector->display_info.subpixel_order;
	out_resp->connection = connector->status;

	/* delayed so we get modes regardless of pre-fill_modes state */
	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		WARN_ON(mode->expose_to_userspace);

		अगर (drm_mode_expose_to_userspace(mode, &connector->modes,
						 file_priv)) अणु
			mode->expose_to_userspace = true;
			mode_count++;
		पूर्ण
	पूर्ण

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd समय to fill it.
	 */
	अगर ((out_resp->count_modes >= mode_count) && mode_count) अणु
		copied = 0;
		mode_ptr = (काष्ठा drm_mode_modeinfo __user *)(अचिन्हित दीर्घ)out_resp->modes_ptr;
		list_क्रम_each_entry(mode, &connector->modes, head) अणु
			अगर (!mode->expose_to_userspace)
				जारी;

			/* Clear the tag क्रम the next समय around */
			mode->expose_to_userspace = false;

			drm_mode_convert_to_umode(&u_mode, mode);
			/*
			 * Reset aspect ratio flags of user-mode, अगर modes with
			 * aspect-ratio are not supported.
			 */
			अगर (!file_priv->aspect_ratio_allowed)
				u_mode.flags &= ~DRM_MODE_FLAG_PIC_AR_MASK;
			अगर (copy_to_user(mode_ptr + copied,
					 &u_mode, माप(u_mode))) अणु
				ret = -EFAULT;

				/*
				 * Clear the tag क्रम the rest of
				 * the modes क्रम the next समय around.
				 */
				list_क्रम_each_entry_जारी(mode, &connector->modes, head)
					mode->expose_to_userspace = false;

				mutex_unlock(&dev->mode_config.mutex);

				जाओ out;
			पूर्ण
			copied++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Clear the tag क्रम the next समय around */
		list_क्रम_each_entry(mode, &connector->modes, head)
			mode->expose_to_userspace = false;
	पूर्ण

	out_resp->count_modes = mode_count;
	mutex_unlock(&dev->mode_config.mutex);

	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);
	encoder = drm_connector_get_encoder(connector);
	अगर (encoder)
		out_resp->encoder_id = encoder->base.id;
	अन्यथा
		out_resp->encoder_id = 0;

	/* Only grab properties after probing, to make sure EDID and other
	 * properties reflect the latest status. */
	ret = drm_mode_object_get_properties(&connector->base, file_priv->atomic,
			(uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)(out_resp->props_ptr),
			(uपूर्णांक64_t __user *)(अचिन्हित दीर्घ)(out_resp->prop_values_ptr),
			&out_resp->count_props);
	drm_modeset_unlock(&dev->mode_config.connection_mutex);

out:
	drm_connector_put(connector);

	वापस ret;
पूर्ण


/**
 * DOC: Tile group
 *
 * Tile groups are used to represent tiled monitors with a unique पूर्णांकeger
 * identअगरier. Tiled monitors using DisplayID v1.3 have a unique 8-byte handle,
 * we store this in a tile group, so we have a common identअगरier क्रम all tiles
 * in a monitor group. The property is called "TILE". Drivers can manage tile
 * groups using drm_mode_create_tile_group(), drm_mode_put_tile_group() and
 * drm_mode_get_tile_group(). But this is only needed क्रम पूर्णांकernal panels where
 * the tile group inक्रमmation is exposed through a non-standard way.
 */

अटल व्योम drm_tile_group_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा drm_tile_group *tg = container_of(kref, काष्ठा drm_tile_group, refcount);
	काष्ठा drm_device *dev = tg->dev;

	mutex_lock(&dev->mode_config.idr_mutex);
	idr_हटाओ(&dev->mode_config.tile_idr, tg->id);
	mutex_unlock(&dev->mode_config.idr_mutex);
	kमुक्त(tg);
पूर्ण

/**
 * drm_mode_put_tile_group - drop a reference to a tile group.
 * @dev: DRM device
 * @tg: tile group to drop reference to.
 *
 * drop reference to tile group and मुक्त अगर 0.
 */
व्योम drm_mode_put_tile_group(काष्ठा drm_device *dev,
			     काष्ठा drm_tile_group *tg)
अणु
	kref_put(&tg->refcount, drm_tile_group_मुक्त);
पूर्ण
EXPORT_SYMBOL(drm_mode_put_tile_group);

/**
 * drm_mode_get_tile_group - get a reference to an existing tile group
 * @dev: DRM device
 * @topology: 8-bytes unique per monitor.
 *
 * Use the unique bytes to get a reference to an existing tile group.
 *
 * RETURNS:
 * tile group or शून्य अगर not found.
 */
काष्ठा drm_tile_group *drm_mode_get_tile_group(काष्ठा drm_device *dev,
					       स्थिर अक्षर topology[8])
अणु
	काष्ठा drm_tile_group *tg;
	पूर्णांक id;

	mutex_lock(&dev->mode_config.idr_mutex);
	idr_क्रम_each_entry(&dev->mode_config.tile_idr, tg, id) अणु
		अगर (!स_भेद(tg->group_data, topology, 8)) अणु
			अगर (!kref_get_unless_zero(&tg->refcount))
				tg = शून्य;
			mutex_unlock(&dev->mode_config.idr_mutex);
			वापस tg;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->mode_config.idr_mutex);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_mode_get_tile_group);

/**
 * drm_mode_create_tile_group - create a tile group from a displayid description
 * @dev: DRM device
 * @topology: 8-bytes unique per monitor.
 *
 * Create a tile group क्रम the unique monitor, and get a unique
 * identअगरier क्रम the tile group.
 *
 * RETURNS:
 * new tile group or शून्य.
 */
काष्ठा drm_tile_group *drm_mode_create_tile_group(काष्ठा drm_device *dev,
						  स्थिर अक्षर topology[8])
अणु
	काष्ठा drm_tile_group *tg;
	पूर्णांक ret;

	tg = kzalloc(माप(*tg), GFP_KERNEL);
	अगर (!tg)
		वापस शून्य;

	kref_init(&tg->refcount);
	स_नकल(tg->group_data, topology, 8);
	tg->dev = dev;

	mutex_lock(&dev->mode_config.idr_mutex);
	ret = idr_alloc(&dev->mode_config.tile_idr, tg, 1, 0, GFP_KERNEL);
	अगर (ret >= 0) अणु
		tg->id = ret;
	पूर्ण अन्यथा अणु
		kमुक्त(tg);
		tg = शून्य;
	पूर्ण

	mutex_unlock(&dev->mode_config.idr_mutex);
	वापस tg;
पूर्ण
EXPORT_SYMBOL(drm_mode_create_tile_group);
