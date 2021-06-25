<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Type-C Multiplexer/DeMultiplexer Switch support
 *
 * Copyright (C) 2018 Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 *         Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

#समावेश "class.h"
#समावेश "mux.h"

अटल bool dev_name_ends_with(काष्ठा device *dev, स्थिर अक्षर *suffix)
अणु
	स्थिर अक्षर *name = dev_name(dev);
	स्थिर पूर्णांक name_len = म_माप(name);
	स्थिर पूर्णांक suffix_len = म_माप(suffix);

	अगर (suffix_len > name_len)
		वापस false;

	वापस म_भेद(name + (name_len - suffix_len), suffix) == 0;
पूर्ण

अटल पूर्णांक चयन_fwnode_match(काष्ठा device *dev, स्थिर व्योम *fwnode)
अणु
	वापस dev_fwnode(dev) == fwnode && dev_name_ends_with(dev, "-switch");
पूर्ण

अटल व्योम *typec_चयन_match(काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *id,
				व्योम *data)
अणु
	काष्ठा device *dev;

	अगर (id && !fwnode_property_present(fwnode, id))
		वापस शून्य;

	dev = class_find_device(&typec_mux_class, शून्य, fwnode,
				चयन_fwnode_match);

	वापस dev ? to_typec_चयन(dev) : ERR_PTR(-EPROBE_DEFER);
पूर्ण

/**
 * fwnode_typec_चयन_get - Find USB Type-C orientation चयन
 * @fwnode: The caller device node
 *
 * Finds a चयन linked with @dev. Returns a reference to the चयन on
 * success, शून्य अगर no matching connection was found, or
 * ERR_PTR(-EPROBE_DEFER) when a connection was found but the चयन
 * has not been क्रमागतerated yet.
 */
काष्ठा typec_चयन *fwnode_typec_चयन_get(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा typec_चयन *sw;

	sw = fwnode_connection_find_match(fwnode, "orientation-switch", शून्य,
					  typec_चयन_match);
	अगर (!IS_ERR_OR_शून्य(sw))
		WARN_ON(!try_module_get(sw->dev.parent->driver->owner));

	वापस sw;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_typec_चयन_get);

/**
 * typec_चयन_put - Release USB Type-C orientation चयन
 * @sw: USB Type-C orientation चयन
 *
 * Decrement reference count क्रम @sw.
 */
व्योम typec_चयन_put(काष्ठा typec_चयन *sw)
अणु
	अगर (!IS_ERR_OR_शून्य(sw)) अणु
		module_put(sw->dev.parent->driver->owner);
		put_device(&sw->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(typec_चयन_put);

अटल व्योम typec_चयन_release(काष्ठा device *dev)
अणु
	kमुक्त(to_typec_चयन(dev));
पूर्ण

अटल स्थिर काष्ठा device_type typec_चयन_dev_type = अणु
	.name = "orientation_switch",
	.release = typec_चयन_release,
पूर्ण;

/**
 * typec_चयन_रेजिस्टर - Register USB Type-C orientation चयन
 * @parent: Parent device
 * @desc: Orientation चयन description
 *
 * This function रेजिस्टरs a चयन that can be used क्रम routing the correct
 * data pairs depending on the cable plug orientation from the USB Type-C
 * connector to the USB controllers. USB Type-C plugs can be inserted
 * right-side-up or upside-करोwn.
 */
काष्ठा typec_चयन *
typec_चयन_रेजिस्टर(काष्ठा device *parent,
		      स्थिर काष्ठा typec_चयन_desc *desc)
अणु
	काष्ठा typec_चयन *sw;
	पूर्णांक ret;

	अगर (!desc || !desc->set)
		वापस ERR_PTR(-EINVAL);

	sw = kzalloc(माप(*sw), GFP_KERNEL);
	अगर (!sw)
		वापस ERR_PTR(-ENOMEM);

	sw->set = desc->set;

	device_initialize(&sw->dev);
	sw->dev.parent = parent;
	sw->dev.fwnode = desc->fwnode;
	sw->dev.class = &typec_mux_class;
	sw->dev.type = &typec_चयन_dev_type;
	sw->dev.driver_data = desc->drvdata;
	dev_set_name(&sw->dev, "%s-switch",
		     desc->name ? desc->name : dev_name(parent));

	ret = device_add(&sw->dev);
	अगर (ret) अणु
		dev_err(parent, "failed to register switch (%d)\n", ret);
		put_device(&sw->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस sw;
पूर्ण
EXPORT_SYMBOL_GPL(typec_चयन_रेजिस्टर);

पूर्णांक typec_चयन_set(काष्ठा typec_चयन *sw,
		     क्रमागत typec_orientation orientation)
अणु
	अगर (IS_ERR_OR_शून्य(sw))
		वापस 0;

	वापस sw->set(sw, orientation);
पूर्ण
EXPORT_SYMBOL_GPL(typec_चयन_set);

/**
 * typec_चयन_unरेजिस्टर - Unरेजिस्टर USB Type-C orientation चयन
 * @sw: USB Type-C orientation चयन
 *
 * Unरेजिस्टर चयन that was रेजिस्टरed with typec_चयन_रेजिस्टर().
 */
व्योम typec_चयन_unरेजिस्टर(काष्ठा typec_चयन *sw)
अणु
	अगर (!IS_ERR_OR_शून्य(sw))
		device_unरेजिस्टर(&sw->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_चयन_unरेजिस्टर);

व्योम typec_चयन_set_drvdata(काष्ठा typec_चयन *sw, व्योम *data)
अणु
	dev_set_drvdata(&sw->dev, data);
पूर्ण
EXPORT_SYMBOL_GPL(typec_चयन_set_drvdata);

व्योम *typec_चयन_get_drvdata(काष्ठा typec_चयन *sw)
अणु
	वापस dev_get_drvdata(&sw->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_चयन_get_drvdata);

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mux_fwnode_match(काष्ठा device *dev, स्थिर व्योम *fwnode)
अणु
	वापस dev_fwnode(dev) == fwnode && dev_name_ends_with(dev, "-mux");
पूर्ण

अटल व्योम *typec_mux_match(काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *id,
			     व्योम *data)
अणु
	स्थिर काष्ठा typec_alपंचांगode_desc *desc = data;
	काष्ठा device *dev;
	bool match;
	पूर्णांक nval;
	u16 *val;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Check has the identअगरier alपढ़ोy been "consumed". If it
	 * has, no need to करो any extra connection identअगरication.
	 */
	match = !id;
	अगर (match)
		जाओ find_mux;

	/* Accessory Mode muxes */
	अगर (!desc) अणु
		match = fwnode_property_present(fwnode, "accessory");
		अगर (match)
			जाओ find_mux;
		वापस शून्य;
	पूर्ण

	/* Alternate Mode muxes */
	nval = fwnode_property_count_u16(fwnode, "svid");
	अगर (nval <= 0)
		वापस शून्य;

	val = kसुस्मृति(nval, माप(*val), GFP_KERNEL);
	अगर (!val)
		वापस ERR_PTR(-ENOMEM);

	ret = fwnode_property_पढ़ो_u16_array(fwnode, "svid", val, nval);
	अगर (ret < 0) अणु
		kमुक्त(val);
		वापस ERR_PTR(ret);
	पूर्ण

	क्रम (i = 0; i < nval; i++) अणु
		match = val[i] == desc->svid;
		अगर (match) अणु
			kमुक्त(val);
			जाओ find_mux;
		पूर्ण
	पूर्ण
	kमुक्त(val);
	वापस शून्य;

find_mux:
	dev = class_find_device(&typec_mux_class, शून्य, fwnode,
				mux_fwnode_match);

	वापस dev ? to_typec_mux(dev) : ERR_PTR(-EPROBE_DEFER);
पूर्ण

/**
 * fwnode_typec_mux_get - Find USB Type-C Multiplexer
 * @fwnode: The caller device node
 * @desc: Alt Mode description
 *
 * Finds a mux linked to the caller. This function is primarily meant क्रम the
 * Type-C drivers. Returns a reference to the mux on success, शून्य अगर no
 * matching connection was found, or ERR_PTR(-EPROBE_DEFER) when a connection
 * was found but the mux has not been क्रमागतerated yet.
 */
काष्ठा typec_mux *fwnode_typec_mux_get(काष्ठा fwnode_handle *fwnode,
				       स्थिर काष्ठा typec_alपंचांगode_desc *desc)
अणु
	काष्ठा typec_mux *mux;

	mux = fwnode_connection_find_match(fwnode, "mode-switch", (व्योम *)desc,
					   typec_mux_match);
	अगर (!IS_ERR_OR_शून्य(mux))
		WARN_ON(!try_module_get(mux->dev.parent->driver->owner));

	वापस mux;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_typec_mux_get);

/**
 * typec_mux_put - Release handle to a Multiplexer
 * @mux: USB Type-C Connector Multiplexer/DeMultiplexer
 *
 * Decrements reference count क्रम @mux.
 */
व्योम typec_mux_put(काष्ठा typec_mux *mux)
अणु
	अगर (!IS_ERR_OR_शून्य(mux)) अणु
		module_put(mux->dev.parent->driver->owner);
		put_device(&mux->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(typec_mux_put);

पूर्णांक typec_mux_set(काष्ठा typec_mux *mux, काष्ठा typec_mux_state *state)
अणु
	अगर (IS_ERR_OR_शून्य(mux))
		वापस 0;

	वापस mux->set(mux, state);
पूर्ण
EXPORT_SYMBOL_GPL(typec_mux_set);

अटल व्योम typec_mux_release(काष्ठा device *dev)
अणु
	kमुक्त(to_typec_mux(dev));
पूर्ण

अटल स्थिर काष्ठा device_type typec_mux_dev_type = अणु
	.name = "mode_switch",
	.release = typec_mux_release,
पूर्ण;

/**
 * typec_mux_रेजिस्टर - Register Multiplexer routing USB Type-C pins
 * @parent: Parent device
 * @desc: Multiplexer description
 *
 * USB Type-C connectors can be used क्रम alternate modes of operation besides
 * USB when Accessory/Alternate Modes are supported. With some of those modes,
 * the pins on the connector need to be reconfigured. This function रेजिस्टरs
 * multiplexer चयनes routing the pins on the connector.
 */
काष्ठा typec_mux *
typec_mux_रेजिस्टर(काष्ठा device *parent, स्थिर काष्ठा typec_mux_desc *desc)
अणु
	काष्ठा typec_mux *mux;
	पूर्णांक ret;

	अगर (!desc || !desc->set)
		वापस ERR_PTR(-EINVAL);

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	mux->set = desc->set;

	device_initialize(&mux->dev);
	mux->dev.parent = parent;
	mux->dev.fwnode = desc->fwnode;
	mux->dev.class = &typec_mux_class;
	mux->dev.type = &typec_mux_dev_type;
	mux->dev.driver_data = desc->drvdata;
	dev_set_name(&mux->dev, "%s-mux",
		     desc->name ? desc->name : dev_name(parent));

	ret = device_add(&mux->dev);
	अगर (ret) अणु
		dev_err(parent, "failed to register mux (%d)\n", ret);
		put_device(&mux->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस mux;
पूर्ण
EXPORT_SYMBOL_GPL(typec_mux_रेजिस्टर);

/**
 * typec_mux_unरेजिस्टर - Unरेजिस्टर Multiplexer Switch
 * @mux: USB Type-C Connector Multiplexer/DeMultiplexer
 *
 * Unरेजिस्टर mux that was रेजिस्टरed with typec_mux_रेजिस्टर().
 */
व्योम typec_mux_unरेजिस्टर(काष्ठा typec_mux *mux)
अणु
	अगर (!IS_ERR_OR_शून्य(mux))
		device_unरेजिस्टर(&mux->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_mux_unरेजिस्टर);

व्योम typec_mux_set_drvdata(काष्ठा typec_mux *mux, व्योम *data)
अणु
	dev_set_drvdata(&mux->dev, data);
पूर्ण
EXPORT_SYMBOL_GPL(typec_mux_set_drvdata);

व्योम *typec_mux_get_drvdata(काष्ठा typec_mux *mux)
अणु
	वापस dev_get_drvdata(&mux->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_mux_get_drvdata);

काष्ठा class typec_mux_class = अणु
	.name = "typec_mux",
	.owner = THIS_MODULE,
पूर्ण;
