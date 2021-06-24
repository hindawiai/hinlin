<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Type-C Connector Class
 *
 * Copyright (C) 2017, Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/pd_vकरो.h>
#समावेश <linux/usb/typec_mux.h>

#समावेश "bus.h"
#समावेश "class.h"

अटल DEFINE_IDA(typec_index_ida);

काष्ठा class typec_class = अणु
	.name = "typec",
	.owner = THIS_MODULE,
पूर्ण;

/* ------------------------------------------------------------------------- */
/* Common attributes */

अटल स्थिर अक्षर * स्थिर typec_accessory_modes[] = अणु
	[TYPEC_ACCESSORY_NONE]		= "none",
	[TYPEC_ACCESSORY_AUDIO]		= "analog_audio",
	[TYPEC_ACCESSORY_DEBUG]		= "debug",
पूर्ण;

/* Product types defined in USB PD Specअगरication R3.0 V2.0 */
अटल स्थिर अक्षर * स्थिर product_type_ufp[8] = अणु
	[IDH_PTYPE_NOT_UFP]		= "not_ufp",
	[IDH_PTYPE_HUB]			= "hub",
	[IDH_PTYPE_PERIPH]		= "peripheral",
	[IDH_PTYPE_PSD]			= "psd",
	[IDH_PTYPE_AMA]			= "ama",
पूर्ण;

अटल स्थिर अक्षर * स्थिर product_type_dfp[8] = अणु
	[IDH_PTYPE_NOT_DFP]		= "not_dfp",
	[IDH_PTYPE_DFP_HUB]		= "hub",
	[IDH_PTYPE_DFP_HOST]		= "host",
	[IDH_PTYPE_DFP_PB]		= "power_brick",
पूर्ण;

अटल स्थिर अक्षर * स्थिर product_type_cable[8] = अणु
	[IDH_PTYPE_NOT_CABLE]		= "not_cable",
	[IDH_PTYPE_PCABLE]		= "passive",
	[IDH_PTYPE_ACABLE]		= "active",
	[IDH_PTYPE_VPD]			= "vpd",
पूर्ण;

अटल काष्ठा usb_pd_identity *get_pd_identity(काष्ठा device *dev)
अणु
	अगर (is_typec_partner(dev)) अणु
		काष्ठा typec_partner *partner = to_typec_partner(dev);

		वापस partner->identity;
	पूर्ण अन्यथा अगर (is_typec_cable(dev)) अणु
		काष्ठा typec_cable *cable = to_typec_cable(dev);

		वापस cable->identity;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *get_pd_product_type(काष्ठा device *dev)
अणु
	काष्ठा typec_port *port = to_typec_port(dev->parent);
	काष्ठा usb_pd_identity *id = get_pd_identity(dev);
	स्थिर अक्षर *ptype = शून्य;

	अगर (is_typec_partner(dev)) अणु
		अगर (!id)
			वापस शून्य;

		अगर (port->data_role == TYPEC_HOST)
			ptype = product_type_ufp[PD_IDH_PTYPE(id->id_header)];
		अन्यथा
			ptype = product_type_dfp[PD_IDH_DFP_PTYPE(id->id_header)];
	पूर्ण अन्यथा अगर (is_typec_cable(dev)) अणु
		अगर (id)
			ptype = product_type_cable[PD_IDH_PTYPE(id->id_header)];
		अन्यथा
			ptype = to_typec_cable(dev)->active ?
				product_type_cable[IDH_PTYPE_ACABLE] :
				product_type_cable[IDH_PTYPE_PCABLE];
	पूर्ण

	वापस ptype;
पूर्ण

अटल sमाप_प्रकार id_header_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा usb_pd_identity *id = get_pd_identity(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", id->id_header);
पूर्ण
अटल DEVICE_ATTR_RO(id_header);

अटल sमाप_प्रकार cert_stat_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा usb_pd_identity *id = get_pd_identity(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", id->cert_stat);
पूर्ण
अटल DEVICE_ATTR_RO(cert_stat);

अटल sमाप_प्रकार product_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा usb_pd_identity *id = get_pd_identity(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", id->product);
पूर्ण
अटल DEVICE_ATTR_RO(product);

अटल sमाप_प्रकार product_type_vकरो1_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा usb_pd_identity *id = get_pd_identity(dev);

	वापस sysfs_emit(buf, "0x%08x\n", id->vकरो[0]);
पूर्ण
अटल DEVICE_ATTR_RO(product_type_vकरो1);

अटल sमाप_प्रकार product_type_vकरो2_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा usb_pd_identity *id = get_pd_identity(dev);

	वापस sysfs_emit(buf, "0x%08x\n", id->vकरो[1]);
पूर्ण
अटल DEVICE_ATTR_RO(product_type_vकरो2);

अटल sमाप_प्रकार product_type_vकरो3_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा usb_pd_identity *id = get_pd_identity(dev);

	वापस sysfs_emit(buf, "0x%08x\n", id->vकरो[2]);
पूर्ण
अटल DEVICE_ATTR_RO(product_type_vकरो3);

अटल काष्ठा attribute *usb_pd_id_attrs[] = अणु
	&dev_attr_id_header.attr,
	&dev_attr_cert_stat.attr,
	&dev_attr_product.attr,
	&dev_attr_product_type_vकरो1.attr,
	&dev_attr_product_type_vकरो2.attr,
	&dev_attr_product_type_vकरो3.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group usb_pd_id_group = अणु
	.name = "identity",
	.attrs = usb_pd_id_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *usb_pd_id_groups[] = अणु
	&usb_pd_id_group,
	शून्य,
पूर्ण;

अटल व्योम typec_product_type_notअगरy(काष्ठा device *dev)
अणु
	अक्षर *envp[2] = अणु पूर्ण;
	स्थिर अक्षर *ptype;

	ptype = get_pd_product_type(dev);
	अगर (!ptype)
		वापस;

	sysfs_notअगरy(&dev->kobj, शून्य, "type");

	envp[0] = kaप्र_लिखो(GFP_KERNEL, "PRODUCT_TYPE=%s", ptype);
	अगर (!envp[0])
		वापस;

	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
	kमुक्त(envp[0]);
पूर्ण

अटल व्योम typec_report_identity(काष्ठा device *dev)
अणु
	sysfs_notअगरy(&dev->kobj, "identity", "id_header");
	sysfs_notअगरy(&dev->kobj, "identity", "cert_stat");
	sysfs_notअगरy(&dev->kobj, "identity", "product");
	sysfs_notअगरy(&dev->kobj, "identity", "product_type_vdo1");
	sysfs_notअगरy(&dev->kobj, "identity", "product_type_vdo2");
	sysfs_notअगरy(&dev->kobj, "identity", "product_type_vdo3");
	typec_product_type_notअगरy(dev);
पूर्ण

अटल sमाप_प्रकार
type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *ptype;

	ptype = get_pd_product_type(dev);
	अगर (!ptype)
		वापस 0;

	वापस sysfs_emit(buf, "%s\n", ptype);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार usb_घातer_delivery_revision_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf);
अटल DEVICE_ATTR_RO(usb_घातer_delivery_revision);

/* ------------------------------------------------------------------------- */
/* Alternate Modes */

अटल पूर्णांक alपंचांगode_match(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा typec_alपंचांगode *adev = to_typec_alपंचांगode(dev);
	काष्ठा typec_device_id *id = data;

	अगर (!is_typec_alपंचांगode(dev))
		वापस 0;

	वापस ((adev->svid == id->svid) && (adev->mode == id->mode));
पूर्ण

अटल व्योम typec_alपंचांगode_set_partner(काष्ठा alपंचांगode *alपंचांगode)
अणु
	काष्ठा typec_alपंचांगode *adev = &alपंचांगode->adev;
	काष्ठा typec_device_id id = अणु adev->svid, adev->mode, पूर्ण;
	काष्ठा typec_port *port = typec_alपंचांगode2port(adev);
	काष्ठा alपंचांगode *partner;
	काष्ठा device *dev;

	dev = device_find_child(&port->dev, &id, alपंचांगode_match);
	अगर (!dev)
		वापस;

	/* Bind the port alt mode to the partner/plug alt mode. */
	partner = to_alपंचांगode(to_typec_alपंचांगode(dev));
	alपंचांगode->partner = partner;

	/* Bind the partner/plug alt mode to the port alt mode. */
	अगर (is_typec_plug(adev->dev.parent)) अणु
		काष्ठा typec_plug *plug = to_typec_plug(adev->dev.parent);

		partner->plug[plug->index] = alपंचांगode;
	पूर्ण अन्यथा अणु
		partner->partner = alपंचांगode;
	पूर्ण
पूर्ण

अटल व्योम typec_alपंचांगode_put_partner(काष्ठा alपंचांगode *alपंचांगode)
अणु
	काष्ठा alपंचांगode *partner = alपंचांगode->partner;
	काष्ठा typec_alपंचांगode *adev;

	अगर (!partner)
		वापस;

	adev = &partner->adev;

	अगर (is_typec_plug(adev->dev.parent)) अणु
		काष्ठा typec_plug *plug = to_typec_plug(adev->dev.parent);

		partner->plug[plug->index] = शून्य;
	पूर्ण अन्यथा अणु
		partner->partner = शून्य;
	पूर्ण
	put_device(&adev->dev);
पूर्ण

/**
 * typec_alपंचांगode_update_active - Report Enter/Exit mode
 * @adev: Handle to the alternate mode
 * @active: True when the mode has been entered
 *
 * If a partner or cable plug executes Enter/Exit Mode command successfully, the
 * drivers use this routine to report the updated state of the mode.
 */
व्योम typec_alपंचांगode_update_active(काष्ठा typec_alपंचांगode *adev, bool active)
अणु
	अक्षर dir[6];

	अगर (adev->active == active)
		वापस;

	अगर (!is_typec_port(adev->dev.parent) && adev->dev.driver) अणु
		अगर (!active)
			module_put(adev->dev.driver->owner);
		अन्यथा
			WARN_ON(!try_module_get(adev->dev.driver->owner));
	पूर्ण

	adev->active = active;
	snम_लिखो(dir, माप(dir), "mode%d", adev->mode);
	sysfs_notअगरy(&adev->dev.kobj, dir, "active");
	sysfs_notअगरy(&adev->dev.kobj, शून्य, "active");
	kobject_uevent(&adev->dev.kobj, KOBJ_CHANGE);
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_update_active);

/**
 * typec_alपंचांगode2port - Alternate Mode to USB Type-C port
 * @alt: The Alternate Mode
 *
 * Returns handle to the port that a cable plug or partner with @alt is
 * connected to.
 */
काष्ठा typec_port *typec_alपंचांगode2port(काष्ठा typec_alपंचांगode *alt)
अणु
	अगर (is_typec_plug(alt->dev.parent))
		वापस to_typec_port(alt->dev.parent->parent->parent);
	अगर (is_typec_partner(alt->dev.parent))
		वापस to_typec_port(alt->dev.parent->parent);
	अगर (is_typec_port(alt->dev.parent))
		वापस to_typec_port(alt->dev.parent);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode2port);

अटल sमाप_प्रकार
vकरो_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_alपंचांगode *alt = to_typec_alपंचांगode(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", alt->vकरो);
पूर्ण
अटल DEVICE_ATTR_RO(vकरो);

अटल sमाप_प्रकार
description_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_alपंचांगode *alt = to_typec_alपंचांगode(dev);

	वापस प्र_लिखो(buf, "%s\n", alt->desc ? alt->desc : "");
पूर्ण
अटल DEVICE_ATTR_RO(description);

अटल sमाप_प्रकार
active_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_alपंचांगode *alt = to_typec_alपंचांगode(dev);

	वापस प्र_लिखो(buf, "%s\n", alt->active ? "yes" : "no");
पूर्ण

अटल sमाप_प्रकार active_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा typec_alपंचांगode *adev = to_typec_alपंचांगode(dev);
	काष्ठा alपंचांगode *alपंचांगode = to_alपंचांगode(adev);
	bool enter;
	पूर्णांक ret;

	ret = kstrtobool(buf, &enter);
	अगर (ret)
		वापस ret;

	अगर (adev->active == enter)
		वापस size;

	अगर (is_typec_port(adev->dev.parent)) अणु
		typec_alपंचांगode_update_active(adev, enter);

		/* Make sure that the partner निकासs the mode beक्रमe disabling */
		अगर (alपंचांगode->partner && !enter && alपंचांगode->partner->adev.active)
			typec_alपंचांगode_निकास(&alपंचांगode->partner->adev);
	पूर्ण अन्यथा अगर (alपंचांगode->partner) अणु
		अगर (enter && !alपंचांगode->partner->adev.active) अणु
			dev_warn(dev, "port has the mode disabled\n");
			वापस -EPERM;
		पूर्ण
	पूर्ण

	/* Note: If there is no driver, the mode will not be entered */
	अगर (adev->ops && adev->ops->activate) अणु
		ret = adev->ops->activate(adev, enter);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(active);

अटल sमाप_प्रकार
supported_roles_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा alपंचांगode *alt = to_alपंचांगode(to_typec_alपंचांगode(dev));
	sमाप_प्रकार ret;

	चयन (alt->roles) अणु
	हाल TYPEC_PORT_SRC:
		ret = प्र_लिखो(buf, "source\n");
		अवरोध;
	हाल TYPEC_PORT_SNK:
		ret = प्र_लिखो(buf, "sink\n");
		अवरोध;
	हाल TYPEC_PORT_DRP:
	शेष:
		ret = प्र_लिखो(buf, "source sink\n");
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(supported_roles);

अटल sमाप_प्रकार
mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_alपंचांगode *adev = to_typec_alपंचांगode(dev);

	वापस प्र_लिखो(buf, "%u\n", adev->mode);
पूर्ण
अटल DEVICE_ATTR_RO(mode);

अटल sमाप_प्रकार
svid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_alपंचांगode *adev = to_typec_alपंचांगode(dev);

	वापस प्र_लिखो(buf, "%04x\n", adev->svid);
पूर्ण
अटल DEVICE_ATTR_RO(svid);

अटल काष्ठा attribute *typec_alपंचांगode_attrs[] = अणु
	&dev_attr_active.attr,
	&dev_attr_mode.attr,
	&dev_attr_svid.attr,
	&dev_attr_vकरो.attr,
	शून्य
पूर्ण;

अटल umode_t typec_alपंचांगode_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा typec_alपंचांगode *adev = to_typec_alपंचांगode(kobj_to_dev(kobj));

	अगर (attr == &dev_attr_active.attr)
		अगर (!adev->ops || !adev->ops->activate)
			वापस 0444;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group typec_alपंचांगode_group = अणु
	.is_visible = typec_alपंचांगode_attr_is_visible,
	.attrs = typec_alपंचांगode_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *typec_alपंचांगode_groups[] = अणु
	&typec_alपंचांगode_group,
	शून्य
पूर्ण;

अटल पूर्णांक alपंचांगode_id_get(काष्ठा device *dev)
अणु
	काष्ठा ida *ids;

	अगर (is_typec_partner(dev))
		ids = &to_typec_partner(dev)->mode_ids;
	अन्यथा अगर (is_typec_plug(dev))
		ids = &to_typec_plug(dev)->mode_ids;
	अन्यथा
		ids = &to_typec_port(dev)->mode_ids;

	वापस ida_simple_get(ids, 0, 0, GFP_KERNEL);
पूर्ण

अटल व्योम alपंचांगode_id_हटाओ(काष्ठा device *dev, पूर्णांक id)
अणु
	काष्ठा ida *ids;

	अगर (is_typec_partner(dev))
		ids = &to_typec_partner(dev)->mode_ids;
	अन्यथा अगर (is_typec_plug(dev))
		ids = &to_typec_plug(dev)->mode_ids;
	अन्यथा
		ids = &to_typec_port(dev)->mode_ids;

	ida_simple_हटाओ(ids, id);
पूर्ण

अटल व्योम typec_alपंचांगode_release(काष्ठा device *dev)
अणु
	काष्ठा alपंचांगode *alt = to_alपंचांगode(to_typec_alपंचांगode(dev));

	typec_alपंचांगode_put_partner(alt);

	alपंचांगode_id_हटाओ(alt->adev.dev.parent, alt->id);
	kमुक्त(alt);
पूर्ण

स्थिर काष्ठा device_type typec_alपंचांगode_dev_type = अणु
	.name = "typec_alternate_mode",
	.groups = typec_alपंचांगode_groups,
	.release = typec_alपंचांगode_release,
पूर्ण;

अटल काष्ठा typec_alपंचांगode *
typec_रेजिस्टर_alपंचांगode(काष्ठा device *parent,
		       स्थिर काष्ठा typec_alपंचांगode_desc *desc)
अणु
	अचिन्हित पूर्णांक id = alपंचांगode_id_get(parent);
	bool is_port = is_typec_port(parent);
	काष्ठा alपंचांगode *alt;
	पूर्णांक ret;

	alt = kzalloc(माप(*alt), GFP_KERNEL);
	अगर (!alt)
		वापस ERR_PTR(-ENOMEM);

	alt->adev.svid = desc->svid;
	alt->adev.mode = desc->mode;
	alt->adev.vकरो = desc->vकरो;
	alt->roles = desc->roles;
	alt->id = id;

	alt->attrs[0] = &dev_attr_vकरो.attr;
	alt->attrs[1] = &dev_attr_description.attr;
	alt->attrs[2] = &dev_attr_active.attr;

	अगर (is_port) अणु
		alt->attrs[3] = &dev_attr_supported_roles.attr;
		alt->adev.active = true; /* Enabled by शेष */
	पूर्ण

	प्र_लिखो(alt->group_name, "mode%d", desc->mode);
	alt->group.name = alt->group_name;
	alt->group.attrs = alt->attrs;
	alt->groups[0] = &alt->group;

	alt->adev.dev.parent = parent;
	alt->adev.dev.groups = alt->groups;
	alt->adev.dev.type = &typec_alपंचांगode_dev_type;
	dev_set_name(&alt->adev.dev, "%s.%u", dev_name(parent), id);

	/* Link partners and plugs with the ports */
	अगर (!is_port)
		typec_alपंचांगode_set_partner(alt);

	/* The partners are bind to drivers */
	अगर (is_typec_partner(parent))
		alt->adev.dev.bus = &typec_bus;

	/* Plug alt modes need a class to generate udev events. */
	अगर (is_typec_plug(parent))
		alt->adev.dev.class = &typec_class;

	ret = device_रेजिस्टर(&alt->adev.dev);
	अगर (ret) अणु
		dev_err(parent, "failed to register alternate mode (%d)\n",
			ret);
		put_device(&alt->adev.dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &alt->adev;
पूर्ण

/**
 * typec_unरेजिस्टर_alपंचांगode - Unरेजिस्टर Alternate Mode
 * @adev: The alternate mode to be unरेजिस्टरed
 *
 * Unरेजिस्टर device created with typec_partner_रेजिस्टर_alपंचांगode(),
 * typec_plug_रेजिस्टर_alपंचांगode() or typec_port_रेजिस्टर_alपंचांगode().
 */
व्योम typec_unरेजिस्टर_alपंचांगode(काष्ठा typec_alपंचांगode *adev)
अणु
	अगर (IS_ERR_OR_शून्य(adev))
		वापस;
	typec_mux_put(to_alपंचांगode(adev)->mux);
	device_unरेजिस्टर(&adev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_unरेजिस्टर_alपंचांगode);

/* ------------------------------------------------------------------------- */
/* Type-C Partners */

अटल sमाप_प्रकार accessory_mode_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा typec_partner *p = to_typec_partner(dev);

	वापस प्र_लिखो(buf, "%s\n", typec_accessory_modes[p->accessory]);
पूर्ण
अटल DEVICE_ATTR_RO(accessory_mode);

अटल sमाप_प्रकार supports_usb_घातer_delivery_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा typec_partner *p = to_typec_partner(dev);

	वापस प्र_लिखो(buf, "%s\n", p->usb_pd ? "yes" : "no");
पूर्ण
अटल DEVICE_ATTR_RO(supports_usb_घातer_delivery);

अटल sमाप_प्रकार number_of_alternate_modes_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा typec_partner *partner;
	काष्ठा typec_plug *plug;
	पूर्णांक num_alपंचांगodes;

	अगर (is_typec_partner(dev)) अणु
		partner = to_typec_partner(dev);
		num_alपंचांगodes = partner->num_alपंचांगodes;
	पूर्ण अन्यथा अगर (is_typec_plug(dev)) अणु
		plug = to_typec_plug(dev);
		num_alपंचांगodes = plug->num_alपंचांगodes;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	वापस sysfs_emit(buf, "%d\n", num_alपंचांगodes);
पूर्ण
अटल DEVICE_ATTR_RO(number_of_alternate_modes);

अटल काष्ठा attribute *typec_partner_attrs[] = अणु
	&dev_attr_accessory_mode.attr,
	&dev_attr_supports_usb_घातer_delivery.attr,
	&dev_attr_number_of_alternate_modes.attr,
	&dev_attr_type.attr,
	&dev_attr_usb_घातer_delivery_revision.attr,
	शून्य
पूर्ण;

अटल umode_t typec_partner_attr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा typec_partner *partner = to_typec_partner(kobj_to_dev(kobj));

	अगर (attr == &dev_attr_number_of_alternate_modes.attr) अणु
		अगर (partner->num_alपंचांगodes < 0)
			वापस 0;
	पूर्ण

	अगर (attr == &dev_attr_type.attr)
		अगर (!get_pd_product_type(kobj_to_dev(kobj)))
			वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group typec_partner_group = अणु
	.is_visible = typec_partner_attr_is_visible,
	.attrs = typec_partner_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *typec_partner_groups[] = अणु
	&typec_partner_group,
	शून्य
पूर्ण;

अटल व्योम typec_partner_release(काष्ठा device *dev)
अणु
	काष्ठा typec_partner *partner = to_typec_partner(dev);

	ida_destroy(&partner->mode_ids);
	kमुक्त(partner);
पूर्ण

स्थिर काष्ठा device_type typec_partner_dev_type = अणु
	.name = "typec_partner",
	.groups = typec_partner_groups,
	.release = typec_partner_release,
पूर्ण;

/**
 * typec_partner_set_identity - Report result from Discover Identity command
 * @partner: The partner updated identity values
 *
 * This routine is used to report that the result of Discover Identity USB घातer
 * delivery command has become available.
 */
पूर्णांक typec_partner_set_identity(काष्ठा typec_partner *partner)
अणु
	अगर (!partner->identity)
		वापस -EINVAL;

	typec_report_identity(&partner->dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(typec_partner_set_identity);

/**
 * typec_partner_set_pd_revision - Set the PD revision supported by the partner
 * @partner: The partner to be updated.
 * @pd_revision:  USB Power Delivery Specअगरication Revision supported by partner
 *
 * This routine is used to report that the PD revision of the port partner has
 * become available.
 */
व्योम typec_partner_set_pd_revision(काष्ठा typec_partner *partner, u16 pd_revision)
अणु
	अगर (partner->pd_revision == pd_revision)
		वापस;

	partner->pd_revision = pd_revision;
	sysfs_notअगरy(&partner->dev.kobj, शून्य, "usb_power_delivery_revision");
	अगर (pd_revision != 0 && !partner->usb_pd) अणु
		partner->usb_pd = 1;
		sysfs_notअगरy(&partner->dev.kobj, शून्य,
			     "supports_usb_power_delivery");
	पूर्ण
	kobject_uevent(&partner->dev.kobj, KOBJ_CHANGE);
पूर्ण
EXPORT_SYMBOL_GPL(typec_partner_set_pd_revision);

/**
 * typec_partner_set_num_alपंचांगodes - Set the number of available partner alपंचांगodes
 * @partner: The partner to be updated.
 * @num_alपंचांगodes: The number of alपंचांगodes we want to specअगरy as available.
 *
 * This routine is used to report the number of alternate modes supported by the
 * partner. This value is *not* enक्रमced in alternate mode registration routines.
 *
 * @partner.num_alपंचांगodes is set to -1 on partner registration, denoting that
 * a valid value has not been set क्रम it yet.
 *
 * Returns 0 on success or negative error number on failure.
 */
पूर्णांक typec_partner_set_num_alपंचांगodes(काष्ठा typec_partner *partner, पूर्णांक num_alपंचांगodes)
अणु
	पूर्णांक ret;

	अगर (num_alपंचांगodes < 0)
		वापस -EINVAL;

	partner->num_alपंचांगodes = num_alपंचांगodes;
	ret = sysfs_update_group(&partner->dev.kobj, &typec_partner_group);
	अगर (ret < 0)
		वापस ret;

	sysfs_notअगरy(&partner->dev.kobj, शून्य, "number_of_alternate_modes");
	kobject_uevent(&partner->dev.kobj, KOBJ_CHANGE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(typec_partner_set_num_alपंचांगodes);

/**
 * typec_partner_रेजिस्टर_alपंचांगode - Register USB Type-C Partner Alternate Mode
 * @partner: USB Type-C Partner that supports the alternate mode
 * @desc: Description of the alternate mode
 *
 * This routine is used to रेजिस्टर each alternate mode inभागidually that
 * @partner has listed in response to Discover SVIDs command. The modes क्रम a
 * SVID listed in response to Discover Modes command need to be listed in an
 * array in @desc.
 *
 * Returns handle to the alternate mode on success or ERR_PTR on failure.
 */
काष्ठा typec_alपंचांगode *
typec_partner_रेजिस्टर_alपंचांगode(काष्ठा typec_partner *partner,
			       स्थिर काष्ठा typec_alपंचांगode_desc *desc)
अणु
	वापस typec_रेजिस्टर_alपंचांगode(&partner->dev, desc);
पूर्ण
EXPORT_SYMBOL_GPL(typec_partner_रेजिस्टर_alपंचांगode);

/**
 * typec_partner_set_svdm_version - Set negotiated Structured VDM (SVDM) Version
 * @partner: USB Type-C Partner that supports SVDM
 * @svdm_version: Negotiated SVDM Version
 *
 * This routine is used to save the negotiated SVDM Version.
 */
व्योम typec_partner_set_svdm_version(काष्ठा typec_partner *partner,
				   क्रमागत usb_pd_svdm_ver svdm_version)
अणु
	partner->svdm_version = svdm_version;
पूर्ण
EXPORT_SYMBOL_GPL(typec_partner_set_svdm_version);

/**
 * typec_रेजिस्टर_partner - Register a USB Type-C Partner
 * @port: The USB Type-C Port the partner is connected to
 * @desc: Description of the partner
 *
 * Registers a device क्रम USB Type-C Partner described in @desc.
 *
 * Returns handle to the partner on success or ERR_PTR on failure.
 */
काष्ठा typec_partner *typec_रेजिस्टर_partner(काष्ठा typec_port *port,
					     काष्ठा typec_partner_desc *desc)
अणु
	काष्ठा typec_partner *partner;
	पूर्णांक ret;

	partner = kzalloc(माप(*partner), GFP_KERNEL);
	अगर (!partner)
		वापस ERR_PTR(-ENOMEM);

	ida_init(&partner->mode_ids);
	partner->usb_pd = desc->usb_pd;
	partner->accessory = desc->accessory;
	partner->num_alपंचांगodes = -1;
	partner->pd_revision = desc->pd_revision;
	partner->svdm_version = port->cap->svdm_version;

	अगर (desc->identity) अणु
		/*
		 * Creating directory क्रम the identity only अगर the driver is
		 * able to provide data to it.
		 */
		partner->dev.groups = usb_pd_id_groups;
		partner->identity = desc->identity;
	पूर्ण

	partner->dev.class = &typec_class;
	partner->dev.parent = &port->dev;
	partner->dev.type = &typec_partner_dev_type;
	dev_set_name(&partner->dev, "%s-partner", dev_name(&port->dev));

	ret = device_रेजिस्टर(&partner->dev);
	अगर (ret) अणु
		dev_err(&port->dev, "failed to register partner (%d)\n", ret);
		put_device(&partner->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस partner;
पूर्ण
EXPORT_SYMBOL_GPL(typec_रेजिस्टर_partner);

/**
 * typec_unरेजिस्टर_partner - Unरेजिस्टर a USB Type-C Partner
 * @partner: The partner to be unरेजिस्टरed
 *
 * Unरेजिस्टर device created with typec_रेजिस्टर_partner().
 */
व्योम typec_unरेजिस्टर_partner(काष्ठा typec_partner *partner)
अणु
	अगर (!IS_ERR_OR_शून्य(partner))
		device_unरेजिस्टर(&partner->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_unरेजिस्टर_partner);

/* ------------------------------------------------------------------------- */
/* Type-C Cable Plugs */

अटल व्योम typec_plug_release(काष्ठा device *dev)
अणु
	काष्ठा typec_plug *plug = to_typec_plug(dev);

	ida_destroy(&plug->mode_ids);
	kमुक्त(plug);
पूर्ण

अटल काष्ठा attribute *typec_plug_attrs[] = अणु
	&dev_attr_number_of_alternate_modes.attr,
	शून्य
पूर्ण;

अटल umode_t typec_plug_attr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा typec_plug *plug = to_typec_plug(kobj_to_dev(kobj));

	अगर (attr == &dev_attr_number_of_alternate_modes.attr) अणु
		अगर (plug->num_alपंचांगodes < 0)
			वापस 0;
	पूर्ण

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group typec_plug_group = अणु
	.is_visible = typec_plug_attr_is_visible,
	.attrs = typec_plug_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *typec_plug_groups[] = अणु
	&typec_plug_group,
	शून्य
पूर्ण;

स्थिर काष्ठा device_type typec_plug_dev_type = अणु
	.name = "typec_plug",
	.groups = typec_plug_groups,
	.release = typec_plug_release,
पूर्ण;

/**
 * typec_plug_set_num_alपंचांगodes - Set the number of available plug alपंचांगodes
 * @plug: The plug to be updated.
 * @num_alपंचांगodes: The number of alपंचांगodes we want to specअगरy as available.
 *
 * This routine is used to report the number of alternate modes supported by the
 * plug. This value is *not* enक्रमced in alternate mode registration routines.
 *
 * @plug.num_alपंचांगodes is set to -1 on plug registration, denoting that
 * a valid value has not been set क्रम it yet.
 *
 * Returns 0 on success or negative error number on failure.
 */
पूर्णांक typec_plug_set_num_alपंचांगodes(काष्ठा typec_plug *plug, पूर्णांक num_alपंचांगodes)
अणु
	पूर्णांक ret;

	अगर (num_alपंचांगodes < 0)
		वापस -EINVAL;

	plug->num_alपंचांगodes = num_alपंचांगodes;
	ret = sysfs_update_group(&plug->dev.kobj, &typec_plug_group);
	अगर (ret < 0)
		वापस ret;

	sysfs_notअगरy(&plug->dev.kobj, शून्य, "number_of_alternate_modes");
	kobject_uevent(&plug->dev.kobj, KOBJ_CHANGE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(typec_plug_set_num_alपंचांगodes);

/**
 * typec_plug_रेजिस्टर_alपंचांगode - Register USB Type-C Cable Plug Alternate Mode
 * @plug: USB Type-C Cable Plug that supports the alternate mode
 * @desc: Description of the alternate mode
 *
 * This routine is used to रेजिस्टर each alternate mode inभागidually that @plug
 * has listed in response to Discover SVIDs command. The modes क्रम a SVID that
 * the plug lists in response to Discover Modes command need to be listed in an
 * array in @desc.
 *
 * Returns handle to the alternate mode on success or ERR_PTR on failure.
 */
काष्ठा typec_alपंचांगode *
typec_plug_रेजिस्टर_alपंचांगode(काष्ठा typec_plug *plug,
			    स्थिर काष्ठा typec_alपंचांगode_desc *desc)
अणु
	वापस typec_रेजिस्टर_alपंचांगode(&plug->dev, desc);
पूर्ण
EXPORT_SYMBOL_GPL(typec_plug_रेजिस्टर_alपंचांगode);

/**
 * typec_रेजिस्टर_plug - Register a USB Type-C Cable Plug
 * @cable: USB Type-C Cable with the plug
 * @desc: Description of the cable plug
 *
 * Registers a device क्रम USB Type-C Cable Plug described in @desc. A USB Type-C
 * Cable Plug represents a plug with electronics in it that can response to USB
 * Power Delivery SOP Prime or SOP Double Prime packages.
 *
 * Returns handle to the cable plug on success or ERR_PTR on failure.
 */
काष्ठा typec_plug *typec_रेजिस्टर_plug(काष्ठा typec_cable *cable,
				       काष्ठा typec_plug_desc *desc)
अणु
	काष्ठा typec_plug *plug;
	अक्षर name[8];
	पूर्णांक ret;

	plug = kzalloc(माप(*plug), GFP_KERNEL);
	अगर (!plug)
		वापस ERR_PTR(-ENOMEM);

	प्र_लिखो(name, "plug%d", desc->index);

	ida_init(&plug->mode_ids);
	plug->num_alपंचांगodes = -1;
	plug->index = desc->index;
	plug->dev.class = &typec_class;
	plug->dev.parent = &cable->dev;
	plug->dev.type = &typec_plug_dev_type;
	dev_set_name(&plug->dev, "%s-%s", dev_name(cable->dev.parent), name);

	ret = device_रेजिस्टर(&plug->dev);
	अगर (ret) अणु
		dev_err(&cable->dev, "failed to register plug (%d)\n", ret);
		put_device(&plug->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस plug;
पूर्ण
EXPORT_SYMBOL_GPL(typec_रेजिस्टर_plug);

/**
 * typec_unरेजिस्टर_plug - Unरेजिस्टर a USB Type-C Cable Plug
 * @plug: The cable plug to be unरेजिस्टरed
 *
 * Unरेजिस्टर device created with typec_रेजिस्टर_plug().
 */
व्योम typec_unरेजिस्टर_plug(काष्ठा typec_plug *plug)
अणु
	अगर (!IS_ERR_OR_शून्य(plug))
		device_unरेजिस्टर(&plug->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_unरेजिस्टर_plug);

/* Type-C Cables */

अटल स्थिर अक्षर * स्थिर typec_plug_types[] = अणु
	[USB_PLUG_NONE]		= "unknown",
	[USB_PLUG_TYPE_A]	= "type-a",
	[USB_PLUG_TYPE_B]	= "type-b",
	[USB_PLUG_TYPE_C]	= "type-c",
	[USB_PLUG_CAPTIVE]	= "captive",
पूर्ण;

अटल sमाप_प्रकार plug_type_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_cable *cable = to_typec_cable(dev);

	वापस प्र_लिखो(buf, "%s\n", typec_plug_types[cable->type]);
पूर्ण
अटल DEVICE_ATTR_RO(plug_type);

अटल काष्ठा attribute *typec_cable_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_plug_type.attr,
	&dev_attr_usb_घातer_delivery_revision.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(typec_cable);

अटल व्योम typec_cable_release(काष्ठा device *dev)
अणु
	काष्ठा typec_cable *cable = to_typec_cable(dev);

	kमुक्त(cable);
पूर्ण

स्थिर काष्ठा device_type typec_cable_dev_type = अणु
	.name = "typec_cable",
	.groups = typec_cable_groups,
	.release = typec_cable_release,
पूर्ण;

अटल पूर्णांक cable_match(काष्ठा device *dev, व्योम *data)
अणु
	वापस is_typec_cable(dev);
पूर्ण

/**
 * typec_cable_get - Get a reference to the USB Type-C cable
 * @port: The USB Type-C Port the cable is connected to
 *
 * The caller must decrement the reference count with typec_cable_put() after
 * use.
 */
काष्ठा typec_cable *typec_cable_get(काष्ठा typec_port *port)
अणु
	काष्ठा device *dev;

	dev = device_find_child(&port->dev, शून्य, cable_match);
	अगर (!dev)
		वापस शून्य;

	वापस to_typec_cable(dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_cable_get);

/**
 * typec_cable_put - Decrement the reference count on USB Type-C cable
 * @cable: The USB Type-C cable
 */
व्योम typec_cable_put(काष्ठा typec_cable *cable)
अणु
	put_device(&cable->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_cable_put);

/**
 * typec_cable_is_active - Check is the USB Type-C cable active or passive
 * @cable: The USB Type-C Cable
 *
 * Return 1 अगर the cable is active or 0 अगर it's passive.
 */
पूर्णांक typec_cable_is_active(काष्ठा typec_cable *cable)
अणु
	वापस cable->active;
पूर्ण
EXPORT_SYMBOL_GPL(typec_cable_is_active);

/**
 * typec_cable_set_identity - Report result from Discover Identity command
 * @cable: The cable updated identity values
 *
 * This routine is used to report that the result of Discover Identity USB घातer
 * delivery command has become available.
 */
पूर्णांक typec_cable_set_identity(काष्ठा typec_cable *cable)
अणु
	अगर (!cable->identity)
		वापस -EINVAL;

	typec_report_identity(&cable->dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(typec_cable_set_identity);

/**
 * typec_रेजिस्टर_cable - Register a USB Type-C Cable
 * @port: The USB Type-C Port the cable is connected to
 * @desc: Description of the cable
 *
 * Registers a device क्रम USB Type-C Cable described in @desc. The cable will be
 * parent क्रम the optional cable plug devises.
 *
 * Returns handle to the cable on success or ERR_PTR on failure.
 */
काष्ठा typec_cable *typec_रेजिस्टर_cable(काष्ठा typec_port *port,
					 काष्ठा typec_cable_desc *desc)
अणु
	काष्ठा typec_cable *cable;
	पूर्णांक ret;

	cable = kzalloc(माप(*cable), GFP_KERNEL);
	अगर (!cable)
		वापस ERR_PTR(-ENOMEM);

	cable->type = desc->type;
	cable->active = desc->active;
	cable->pd_revision = desc->pd_revision;

	अगर (desc->identity) अणु
		/*
		 * Creating directory क्रम the identity only अगर the driver is
		 * able to provide data to it.
		 */
		cable->dev.groups = usb_pd_id_groups;
		cable->identity = desc->identity;
	पूर्ण

	cable->dev.class = &typec_class;
	cable->dev.parent = &port->dev;
	cable->dev.type = &typec_cable_dev_type;
	dev_set_name(&cable->dev, "%s-cable", dev_name(&port->dev));

	ret = device_रेजिस्टर(&cable->dev);
	अगर (ret) अणु
		dev_err(&port->dev, "failed to register cable (%d)\n", ret);
		put_device(&cable->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस cable;
पूर्ण
EXPORT_SYMBOL_GPL(typec_रेजिस्टर_cable);

/**
 * typec_unरेजिस्टर_cable - Unरेजिस्टर a USB Type-C Cable
 * @cable: The cable to be unरेजिस्टरed
 *
 * Unरेजिस्टर device created with typec_रेजिस्टर_cable().
 */
व्योम typec_unरेजिस्टर_cable(काष्ठा typec_cable *cable)
अणु
	अगर (!IS_ERR_OR_शून्य(cable))
		device_unरेजिस्टर(&cable->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_unरेजिस्टर_cable);

/* ------------------------------------------------------------------------- */
/* USB Type-C ports */

अटल स्थिर अक्षर * स्थिर typec_orientations[] = अणु
	[TYPEC_ORIENTATION_NONE]	= "unknown",
	[TYPEC_ORIENTATION_NORMAL]	= "normal",
	[TYPEC_ORIENTATION_REVERSE]	= "reverse",
पूर्ण;

अटल स्थिर अक्षर * स्थिर typec_roles[] = अणु
	[TYPEC_SINK]	= "sink",
	[TYPEC_SOURCE]	= "source",
पूर्ण;

अटल स्थिर अक्षर * स्थिर typec_data_roles[] = अणु
	[TYPEC_DEVICE]	= "device",
	[TYPEC_HOST]	= "host",
पूर्ण;

अटल स्थिर अक्षर * स्थिर typec_port_घातer_roles[] = अणु
	[TYPEC_PORT_SRC] = "source",
	[TYPEC_PORT_SNK] = "sink",
	[TYPEC_PORT_DRP] = "dual",
पूर्ण;

अटल स्थिर अक्षर * स्थिर typec_port_data_roles[] = अणु
	[TYPEC_PORT_DFP] = "host",
	[TYPEC_PORT_UFP] = "device",
	[TYPEC_PORT_DRD] = "dual",
पूर्ण;

अटल स्थिर अक्षर * स्थिर typec_port_types_drp[] = अणु
	[TYPEC_PORT_SRC] = "dual [source] sink",
	[TYPEC_PORT_SNK] = "dual source [sink]",
	[TYPEC_PORT_DRP] = "[dual] source sink",
पूर्ण;

अटल sमाप_प्रकार
preferred_role_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);
	पूर्णांक role;
	पूर्णांक ret;

	अगर (port->cap->type != TYPEC_PORT_DRP) अणु
		dev_dbg(dev, "Preferred role only supported with DRP ports\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!port->ops || !port->ops->try_role) अणु
		dev_dbg(dev, "Setting preferred role not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	role = sysfs_match_string(typec_roles, buf);
	अगर (role < 0) अणु
		अगर (sysfs_streq(buf, "none"))
			role = TYPEC_NO_PREFERRED_ROLE;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	ret = port->ops->try_role(port, role);
	अगर (ret)
		वापस ret;

	port->prefer_role = role;
	वापस size;
पूर्ण

अटल sमाप_प्रकार
preferred_role_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	अगर (port->cap->type != TYPEC_PORT_DRP)
		वापस 0;

	अगर (port->prefer_role < 0)
		वापस 0;

	वापस प्र_लिखो(buf, "%s\n", typec_roles[port->prefer_role]);
पूर्ण
अटल DEVICE_ATTR_RW(preferred_role);

अटल sमाप_प्रकार data_role_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);
	पूर्णांक ret;

	अगर (!port->ops || !port->ops->dr_set) अणु
		dev_dbg(dev, "data role swapping not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = sysfs_match_string(typec_data_roles, buf);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&port->port_type_lock);
	अगर (port->cap->data != TYPEC_PORT_DRD) अणु
		ret = -EOPNOTSUPP;
		जाओ unlock_and_ret;
	पूर्ण

	ret = port->ops->dr_set(port, ret);
	अगर (ret)
		जाओ unlock_and_ret;

	ret = size;
unlock_and_ret:
	mutex_unlock(&port->port_type_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार data_role_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	अगर (port->cap->data == TYPEC_PORT_DRD)
		वापस प्र_लिखो(buf, "%s\n", port->data_role == TYPEC_HOST ?
			       "[host] device" : "host [device]");

	वापस प्र_लिखो(buf, "[%s]\n", typec_data_roles[port->data_role]);
पूर्ण
अटल DEVICE_ATTR_RW(data_role);

अटल sमाप_प्रकार घातer_role_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);
	पूर्णांक ret;

	अगर (!port->ops || !port->ops->pr_set) अणु
		dev_dbg(dev, "power role swapping not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (port->pwr_opmode != TYPEC_PWR_MODE_PD) अणु
		dev_dbg(dev, "partner unable to swap power role\n");
		वापस -EIO;
	पूर्ण

	ret = sysfs_match_string(typec_roles, buf);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&port->port_type_lock);
	अगर (port->port_type != TYPEC_PORT_DRP) अणु
		dev_dbg(dev, "port type fixed at \"%s\"",
			     typec_port_घातer_roles[port->port_type]);
		ret = -EOPNOTSUPP;
		जाओ unlock_and_ret;
	पूर्ण

	ret = port->ops->pr_set(port, ret);
	अगर (ret)
		जाओ unlock_and_ret;

	ret = size;
unlock_and_ret:
	mutex_unlock(&port->port_type_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार घातer_role_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	अगर (port->cap->type == TYPEC_PORT_DRP)
		वापस प्र_लिखो(buf, "%s\n", port->pwr_role == TYPEC_SOURCE ?
			       "[source] sink" : "source [sink]");

	वापस प्र_लिखो(buf, "[%s]\n", typec_roles[port->pwr_role]);
पूर्ण
अटल DEVICE_ATTR_RW(घातer_role);

अटल sमाप_प्रकार
port_type_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);
	पूर्णांक ret;
	क्रमागत typec_port_type type;

	अगर (port->cap->type != TYPEC_PORT_DRP ||
	    !port->ops || !port->ops->port_type_set) अणु
		dev_dbg(dev, "changing port type not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = sysfs_match_string(typec_port_घातer_roles, buf);
	अगर (ret < 0)
		वापस ret;

	type = ret;
	mutex_lock(&port->port_type_lock);

	अगर (port->port_type == type) अणु
		ret = size;
		जाओ unlock_and_ret;
	पूर्ण

	ret = port->ops->port_type_set(port, type);
	अगर (ret)
		जाओ unlock_and_ret;

	port->port_type = type;
	ret = size;

unlock_and_ret:
	mutex_unlock(&port->port_type_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
port_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	अगर (port->cap->type == TYPEC_PORT_DRP)
		वापस प्र_लिखो(buf, "%s\n",
			       typec_port_types_drp[port->port_type]);

	वापस प्र_लिखो(buf, "[%s]\n", typec_port_घातer_roles[port->cap->type]);
पूर्ण
अटल DEVICE_ATTR_RW(port_type);

अटल स्थिर अक्षर * स्थिर typec_pwr_opmodes[] = अणु
	[TYPEC_PWR_MODE_USB]	= "default",
	[TYPEC_PWR_MODE_1_5A]	= "1.5A",
	[TYPEC_PWR_MODE_3_0A]	= "3.0A",
	[TYPEC_PWR_MODE_PD]	= "usb_power_delivery",
पूर्ण;

अटल sमाप_प्रकार घातer_operation_mode_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	वापस प्र_लिखो(buf, "%s\n", typec_pwr_opmodes[port->pwr_opmode]);
पूर्ण
अटल DEVICE_ATTR_RO(घातer_operation_mode);

अटल sमाप_प्रकार vconn_source_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);
	bool source;
	पूर्णांक ret;

	अगर (!port->cap->pd_revision) अणु
		dev_dbg(dev, "VCONN swap depends on USB Power Delivery\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!port->ops || !port->ops->vconn_set) अणु
		dev_dbg(dev, "VCONN swapping not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = kstrtobool(buf, &source);
	अगर (ret)
		वापस ret;

	ret = port->ops->vconn_set(port, (क्रमागत typec_role)source);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल sमाप_प्रकार vconn_source_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	वापस प्र_लिखो(buf, "%s\n",
		       port->vconn_role == TYPEC_SOURCE ? "yes" : "no");
पूर्ण
अटल DEVICE_ATTR_RW(vconn_source);

अटल sमाप_प्रकार supported_accessory_modes_show(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);
	sमाप_प्रकार ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(port->cap->accessory); i++) अणु
		अगर (port->cap->accessory[i])
			ret += प्र_लिखो(buf + ret, "%s ",
			       typec_accessory_modes[port->cap->accessory[i]]);
	पूर्ण

	अगर (!ret)
		वापस प्र_लिखो(buf, "none\n");

	buf[ret - 1] = '\n';

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(supported_accessory_modes);

अटल sमाप_प्रकार usb_typec_revision_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);
	u16 rev = port->cap->revision;

	वापस प्र_लिखो(buf, "%d.%d\n", (rev >> 8) & 0xff, (rev >> 4) & 0xf);
पूर्ण
अटल DEVICE_ATTR_RO(usb_typec_revision);

अटल sमाप_प्रकार usb_घातer_delivery_revision_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	u16 rev = 0;

	अगर (is_typec_partner(dev)) अणु
		काष्ठा typec_partner *partner = to_typec_partner(dev);

		rev = partner->pd_revision;
	पूर्ण अन्यथा अगर (is_typec_cable(dev)) अणु
		काष्ठा typec_cable *cable = to_typec_cable(dev);

		rev = cable->pd_revision;
	पूर्ण अन्यथा अगर (is_typec_port(dev)) अणु
		काष्ठा typec_port *p = to_typec_port(dev);

		rev = p->cap->pd_revision;
	पूर्ण
	वापस sysfs_emit(buf, "%d.%d\n", (rev >> 8) & 0xff, (rev >> 4) & 0xf);
पूर्ण

अटल sमाप_प्रकार orientation_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	वापस प्र_लिखो(buf, "%s\n", typec_orientations[port->orientation]);
पूर्ण
अटल DEVICE_ATTR_RO(orientation);

अटल काष्ठा attribute *typec_attrs[] = अणु
	&dev_attr_data_role.attr,
	&dev_attr_घातer_operation_mode.attr,
	&dev_attr_घातer_role.attr,
	&dev_attr_preferred_role.attr,
	&dev_attr_supported_accessory_modes.attr,
	&dev_attr_usb_घातer_delivery_revision.attr,
	&dev_attr_usb_typec_revision.attr,
	&dev_attr_vconn_source.attr,
	&dev_attr_port_type.attr,
	&dev_attr_orientation.attr,
	शून्य,
पूर्ण;

अटल umode_t typec_attr_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा typec_port *port = to_typec_port(kobj_to_dev(kobj));

	अगर (attr == &dev_attr_data_role.attr) अणु
		अगर (port->cap->data != TYPEC_PORT_DRD ||
		    !port->ops || !port->ops->dr_set)
			वापस 0444;
	पूर्ण अन्यथा अगर (attr == &dev_attr_घातer_role.attr) अणु
		अगर (port->cap->type != TYPEC_PORT_DRP ||
		    !port->ops || !port->ops->pr_set)
			वापस 0444;
	पूर्ण अन्यथा अगर (attr == &dev_attr_vconn_source.attr) अणु
		अगर (!port->cap->pd_revision ||
		    !port->ops || !port->ops->vconn_set)
			वापस 0444;
	पूर्ण अन्यथा अगर (attr == &dev_attr_preferred_role.attr) अणु
		अगर (port->cap->type != TYPEC_PORT_DRP ||
		    !port->ops || !port->ops->try_role)
			वापस 0444;
	पूर्ण अन्यथा अगर (attr == &dev_attr_port_type.attr) अणु
		अगर (!port->ops || !port->ops->port_type_set)
			वापस 0;
		अगर (port->cap->type != TYPEC_PORT_DRP)
			वापस 0444;
	पूर्ण अन्यथा अगर (attr == &dev_attr_orientation.attr) अणु
		अगर (port->cap->orientation_aware)
			वापस 0444;
		वापस 0;
	पूर्ण

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group typec_group = अणु
	.is_visible = typec_attr_is_visible,
	.attrs = typec_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *typec_groups[] = अणु
	&typec_group,
	शून्य
पूर्ण;

अटल पूर्णांक typec_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक ret;

	ret = add_uevent_var(env, "TYPEC_PORT=%s", dev_name(dev));
	अगर (ret)
		dev_err(dev, "failed to add uevent TYPEC_PORT\n");

	वापस ret;
पूर्ण

अटल व्योम typec_release(काष्ठा device *dev)
अणु
	काष्ठा typec_port *port = to_typec_port(dev);

	ida_simple_हटाओ(&typec_index_ida, port->id);
	ida_destroy(&port->mode_ids);
	typec_चयन_put(port->sw);
	typec_mux_put(port->mux);
	kमुक्त(port->cap);
	kमुक्त(port);
पूर्ण

स्थिर काष्ठा device_type typec_port_dev_type = अणु
	.name = "typec_port",
	.groups = typec_groups,
	.uevent = typec_uevent,
	.release = typec_release,
पूर्ण;

/* --------------------------------------- */
/* Driver callbacks to report role updates */

अटल पूर्णांक partner_match(काष्ठा device *dev, व्योम *data)
अणु
	वापस is_typec_partner(dev);
पूर्ण

/**
 * typec_set_data_role - Report data role change
 * @port: The USB Type-C Port where the role was changed
 * @role: The new data role
 *
 * This routine is used by the port drivers to report data role changes.
 */
व्योम typec_set_data_role(काष्ठा typec_port *port, क्रमागत typec_data_role role)
अणु
	काष्ठा device *partner_dev;

	अगर (port->data_role == role)
		वापस;

	port->data_role = role;
	sysfs_notअगरy(&port->dev.kobj, शून्य, "data_role");
	kobject_uevent(&port->dev.kobj, KOBJ_CHANGE);

	partner_dev = device_find_child(&port->dev, शून्य, partner_match);
	अगर (!partner_dev)
		वापस;

	अगर (to_typec_partner(partner_dev)->identity)
		typec_product_type_notअगरy(partner_dev);

	put_device(partner_dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_set_data_role);

/**
 * typec_set_pwr_role - Report घातer role change
 * @port: The USB Type-C Port where the role was changed
 * @role: The new data role
 *
 * This routine is used by the port drivers to report घातer role changes.
 */
व्योम typec_set_pwr_role(काष्ठा typec_port *port, क्रमागत typec_role role)
अणु
	अगर (port->pwr_role == role)
		वापस;

	port->pwr_role = role;
	sysfs_notअगरy(&port->dev.kobj, शून्य, "power_role");
	kobject_uevent(&port->dev.kobj, KOBJ_CHANGE);
पूर्ण
EXPORT_SYMBOL_GPL(typec_set_pwr_role);

/**
 * typec_set_vconn_role - Report VCONN source change
 * @port: The USB Type-C Port which VCONN role changed
 * @role: Source when @port is sourcing VCONN, or Sink when it's not
 *
 * This routine is used by the port drivers to report अगर the VCONN source is
 * changes.
 */
व्योम typec_set_vconn_role(काष्ठा typec_port *port, क्रमागत typec_role role)
अणु
	अगर (port->vconn_role == role)
		वापस;

	port->vconn_role = role;
	sysfs_notअगरy(&port->dev.kobj, शून्य, "vconn_source");
	kobject_uevent(&port->dev.kobj, KOBJ_CHANGE);
पूर्ण
EXPORT_SYMBOL_GPL(typec_set_vconn_role);

/**
 * typec_set_pwr_opmode - Report changed घातer operation mode
 * @port: The USB Type-C Port where the mode was changed
 * @opmode: New घातer operation mode
 *
 * This routine is used by the port drivers to report changed घातer operation
 * mode in @port. The modes are USB (शेष), 1.5A, 3.0A as defined in USB
 * Type-C specअगरication, and "USB Power Delivery" when the घातer levels are
 * negotiated with methods defined in USB Power Delivery specअगरication.
 */
व्योम typec_set_pwr_opmode(काष्ठा typec_port *port,
			  क्रमागत typec_pwr_opmode opmode)
अणु
	काष्ठा device *partner_dev;

	अगर (port->pwr_opmode == opmode)
		वापस;

	port->pwr_opmode = opmode;
	sysfs_notअगरy(&port->dev.kobj, शून्य, "power_operation_mode");
	kobject_uevent(&port->dev.kobj, KOBJ_CHANGE);

	partner_dev = device_find_child(&port->dev, शून्य, partner_match);
	अगर (partner_dev) अणु
		काष्ठा typec_partner *partner = to_typec_partner(partner_dev);

		अगर (opmode == TYPEC_PWR_MODE_PD && !partner->usb_pd) अणु
			partner->usb_pd = 1;
			sysfs_notअगरy(&partner_dev->kobj, शून्य,
				     "supports_usb_power_delivery");
		पूर्ण
		put_device(partner_dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(typec_set_pwr_opmode);

/**
 * typec_find_pwr_opmode - Get the typec घातer operation mode capability
 * @name: घातer operation mode string
 *
 * This routine is used to find the typec_pwr_opmode by its string @name.
 *
 * Returns typec_pwr_opmode अगर success, otherwise negative error code.
 */
पूर्णांक typec_find_pwr_opmode(स्थिर अक्षर *name)
अणु
	वापस match_string(typec_pwr_opmodes,
			    ARRAY_SIZE(typec_pwr_opmodes), name);
पूर्ण
EXPORT_SYMBOL_GPL(typec_find_pwr_opmode);

/**
 * typec_find_orientation - Convert orientation string to क्रमागत typec_orientation
 * @name: Orientation string
 *
 * This routine is used to find the typec_orientation by its string name @name.
 *
 * Returns the orientation value on success, otherwise negative error code.
 */
पूर्णांक typec_find_orientation(स्थिर अक्षर *name)
अणु
	वापस match_string(typec_orientations, ARRAY_SIZE(typec_orientations),
			    name);
पूर्ण
EXPORT_SYMBOL_GPL(typec_find_orientation);

/**
 * typec_find_port_घातer_role - Get the typec port घातer capability
 * @name: port घातer capability string
 *
 * This routine is used to find the typec_port_type by its string name.
 *
 * Returns typec_port_type अगर success, otherwise negative error code.
 */
पूर्णांक typec_find_port_घातer_role(स्थिर अक्षर *name)
अणु
	वापस match_string(typec_port_घातer_roles,
			    ARRAY_SIZE(typec_port_घातer_roles), name);
पूर्ण
EXPORT_SYMBOL_GPL(typec_find_port_घातer_role);

/**
 * typec_find_घातer_role - Find the typec one specअगरic घातer role
 * @name: घातer role string
 *
 * This routine is used to find the typec_role by its string name.
 *
 * Returns typec_role अगर success, otherwise negative error code.
 */
पूर्णांक typec_find_घातer_role(स्थिर अक्षर *name)
अणु
	वापस match_string(typec_roles, ARRAY_SIZE(typec_roles), name);
पूर्ण
EXPORT_SYMBOL_GPL(typec_find_घातer_role);

/**
 * typec_find_port_data_role - Get the typec port data capability
 * @name: port data capability string
 *
 * This routine is used to find the typec_port_data by its string name.
 *
 * Returns typec_port_data अगर success, otherwise negative error code.
 */
पूर्णांक typec_find_port_data_role(स्थिर अक्षर *name)
अणु
	वापस match_string(typec_port_data_roles,
			    ARRAY_SIZE(typec_port_data_roles), name);
पूर्ण
EXPORT_SYMBOL_GPL(typec_find_port_data_role);

/* ------------------------------------------ */
/* API क्रम Multiplexer/DeMultiplexer Switches */

/**
 * typec_set_orientation - Set USB Type-C cable plug orientation
 * @port: USB Type-C Port
 * @orientation: USB Type-C cable plug orientation
 *
 * Set cable plug orientation क्रम @port.
 */
पूर्णांक typec_set_orientation(काष्ठा typec_port *port,
			  क्रमागत typec_orientation orientation)
अणु
	पूर्णांक ret;

	ret = typec_चयन_set(port->sw, orientation);
	अगर (ret)
		वापस ret;

	port->orientation = orientation;
	sysfs_notअगरy(&port->dev.kobj, शून्य, "orientation");
	kobject_uevent(&port->dev.kobj, KOBJ_CHANGE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(typec_set_orientation);

/**
 * typec_get_orientation - Get USB Type-C cable plug orientation
 * @port: USB Type-C Port
 *
 * Get current cable plug orientation क्रम @port.
 */
क्रमागत typec_orientation typec_get_orientation(काष्ठा typec_port *port)
अणु
	वापस port->orientation;
पूर्ण
EXPORT_SYMBOL_GPL(typec_get_orientation);

/**
 * typec_set_mode - Set mode of operation क्रम USB Type-C connector
 * @port: USB Type-C connector
 * @mode: Accessory Mode, USB Operation or Safe State
 *
 * Configure @port क्रम Accessory Mode @mode. This function will configure the
 * muxes needed क्रम @mode.
 */
पूर्णांक typec_set_mode(काष्ठा typec_port *port, पूर्णांक mode)
अणु
	काष्ठा typec_mux_state state = अणु पूर्ण;

	state.mode = mode;

	वापस typec_mux_set(port->mux, &state);
पूर्ण
EXPORT_SYMBOL_GPL(typec_set_mode);

/* --------------------------------------- */

/**
 * typec_get_negotiated_svdm_version - Get negotiated SVDM Version
 * @port: USB Type-C Port.
 *
 * Get the negotiated SVDM Version. The Version is set to the port शेष
 * value stored in typec_capability on partner registration, and updated after
 * a successful Discover Identity अगर the negotiated value is less than the
 * शेष value.
 *
 * Returns usb_pd_svdm_ver अगर the partner has been रेजिस्टरed otherwise -ENODEV.
 */
पूर्णांक typec_get_negotiated_svdm_version(काष्ठा typec_port *port)
अणु
	क्रमागत usb_pd_svdm_ver svdm_version;
	काष्ठा device *partner_dev;

	partner_dev = device_find_child(&port->dev, शून्य, partner_match);
	अगर (!partner_dev)
		वापस -ENODEV;

	svdm_version = to_typec_partner(partner_dev)->svdm_version;
	put_device(partner_dev);

	वापस svdm_version;
पूर्ण
EXPORT_SYMBOL_GPL(typec_get_negotiated_svdm_version);

/**
 * typec_get_drvdata - Return निजी driver data poपूर्णांकer
 * @port: USB Type-C port
 */
व्योम *typec_get_drvdata(काष्ठा typec_port *port)
अणु
	वापस dev_get_drvdata(&port->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_get_drvdata);

/**
 * typec_port_रेजिस्टर_alपंचांगode - Register USB Type-C Port Alternate Mode
 * @port: USB Type-C Port that supports the alternate mode
 * @desc: Description of the alternate mode
 *
 * This routine is used to रेजिस्टर an alternate mode that @port is capable of
 * supporting.
 *
 * Returns handle to the alternate mode on success or ERR_PTR on failure.
 */
काष्ठा typec_alपंचांगode *
typec_port_रेजिस्टर_alपंचांगode(काष्ठा typec_port *port,
			    स्थिर काष्ठा typec_alपंचांगode_desc *desc)
अणु
	काष्ठा typec_alपंचांगode *adev;
	काष्ठा typec_mux *mux;

	mux = typec_mux_get(&port->dev, desc);
	अगर (IS_ERR(mux))
		वापस ERR_CAST(mux);

	adev = typec_रेजिस्टर_alपंचांगode(&port->dev, desc);
	अगर (IS_ERR(adev))
		typec_mux_put(mux);
	अन्यथा
		to_alपंचांगode(adev)->mux = mux;

	वापस adev;
पूर्ण
EXPORT_SYMBOL_GPL(typec_port_रेजिस्टर_alपंचांगode);

व्योम typec_port_रेजिस्टर_alपंचांगodes(काष्ठा typec_port *port,
	स्थिर काष्ठा typec_alपंचांगode_ops *ops, व्योम *drvdata,
	काष्ठा typec_alपंचांगode **alपंचांगodes, माप_प्रकार n)
अणु
	काष्ठा fwnode_handle *alपंचांगodes_node, *child;
	काष्ठा typec_alपंचांगode_desc desc;
	काष्ठा typec_alपंचांगode *alt;
	माप_प्रकार index = 0;
	u32 svid, vकरो;
	पूर्णांक ret;

	alपंचांगodes_node = device_get_named_child_node(&port->dev, "altmodes");
	अगर (!alपंचांगodes_node)
		वापस; /* No alपंचांगodes specअगरied */

	fwnode_क्रम_each_child_node(alपंचांगodes_node, child) अणु
		ret = fwnode_property_पढ़ो_u32(child, "svid", &svid);
		अगर (ret) अणु
			dev_err(&port->dev, "Error reading svid for altmode %s\n",
				fwnode_get_name(child));
			जारी;
		पूर्ण

		ret = fwnode_property_पढ़ो_u32(child, "vdo", &vकरो);
		अगर (ret) अणु
			dev_err(&port->dev, "Error reading vdo for altmode %s\n",
				fwnode_get_name(child));
			जारी;
		पूर्ण

		अगर (index >= n) अणु
			dev_err(&port->dev, "Error not enough space for altmode %s\n",
				fwnode_get_name(child));
			जारी;
		पूर्ण

		desc.svid = svid;
		desc.vकरो = vकरो;
		desc.mode = index + 1;
		alt = typec_port_रेजिस्टर_alपंचांगode(port, &desc);
		अगर (IS_ERR(alt)) अणु
			dev_err(&port->dev, "Error registering altmode %s\n",
				fwnode_get_name(child));
			जारी;
		पूर्ण

		alt->ops = ops;
		typec_alपंचांगode_set_drvdata(alt, drvdata);
		alपंचांगodes[index] = alt;
		index++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(typec_port_रेजिस्टर_alपंचांगodes);

/**
 * typec_रेजिस्टर_port - Register a USB Type-C Port
 * @parent: Parent device
 * @cap: Description of the port
 *
 * Registers a device क्रम USB Type-C Port described in @cap.
 *
 * Returns handle to the port on success or ERR_PTR on failure.
 */
काष्ठा typec_port *typec_रेजिस्टर_port(काष्ठा device *parent,
				       स्थिर काष्ठा typec_capability *cap)
अणु
	काष्ठा typec_port *port;
	पूर्णांक ret;
	पूर्णांक id;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस ERR_PTR(-ENOMEM);

	id = ida_simple_get(&typec_index_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		kमुक्त(port);
		वापस ERR_PTR(id);
	पूर्ण

	चयन (cap->type) अणु
	हाल TYPEC_PORT_SRC:
		port->pwr_role = TYPEC_SOURCE;
		port->vconn_role = TYPEC_SOURCE;
		अवरोध;
	हाल TYPEC_PORT_SNK:
		port->pwr_role = TYPEC_SINK;
		port->vconn_role = TYPEC_SINK;
		अवरोध;
	हाल TYPEC_PORT_DRP:
		अगर (cap->prefer_role != TYPEC_NO_PREFERRED_ROLE)
			port->pwr_role = cap->prefer_role;
		अन्यथा
			port->pwr_role = TYPEC_SINK;
		अवरोध;
	पूर्ण

	चयन (cap->data) अणु
	हाल TYPEC_PORT_DFP:
		port->data_role = TYPEC_HOST;
		अवरोध;
	हाल TYPEC_PORT_UFP:
		port->data_role = TYPEC_DEVICE;
		अवरोध;
	हाल TYPEC_PORT_DRD:
		अगर (cap->prefer_role == TYPEC_SOURCE)
			port->data_role = TYPEC_HOST;
		अन्यथा
			port->data_role = TYPEC_DEVICE;
		अवरोध;
	पूर्ण

	ida_init(&port->mode_ids);
	mutex_init(&port->port_type_lock);
	mutex_init(&port->port_list_lock);
	INIT_LIST_HEAD(&port->port_list);

	port->id = id;
	port->ops = cap->ops;
	port->port_type = cap->type;
	port->prefer_role = cap->prefer_role;

	device_initialize(&port->dev);
	port->dev.class = &typec_class;
	port->dev.parent = parent;
	port->dev.fwnode = cap->fwnode;
	port->dev.type = &typec_port_dev_type;
	dev_set_name(&port->dev, "port%d", id);
	dev_set_drvdata(&port->dev, cap->driver_data);

	port->cap = kmemdup(cap, माप(*cap), GFP_KERNEL);
	अगर (!port->cap) अणु
		put_device(&port->dev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	port->sw = typec_चयन_get(&port->dev);
	अगर (IS_ERR(port->sw)) अणु
		ret = PTR_ERR(port->sw);
		put_device(&port->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	port->mux = typec_mux_get(&port->dev, शून्य);
	अगर (IS_ERR(port->mux)) अणु
		ret = PTR_ERR(port->mux);
		put_device(&port->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = device_add(&port->dev);
	अगर (ret) अणु
		dev_err(parent, "failed to register port (%d)\n", ret);
		put_device(&port->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = typec_link_ports(port);
	अगर (ret)
		dev_warn(&port->dev, "failed to create symlinks (%d)\n", ret);

	वापस port;
पूर्ण
EXPORT_SYMBOL_GPL(typec_रेजिस्टर_port);

/**
 * typec_unरेजिस्टर_port - Unरेजिस्टर a USB Type-C Port
 * @port: The port to be unरेजिस्टरed
 *
 * Unरेजिस्टर device created with typec_रेजिस्टर_port().
 */
व्योम typec_unरेजिस्टर_port(काष्ठा typec_port *port)
अणु
	अगर (!IS_ERR_OR_शून्य(port)) अणु
		typec_unlink_ports(port);
		device_unरेजिस्टर(&port->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(typec_unरेजिस्टर_port);

अटल पूर्णांक __init typec_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&typec_bus);
	अगर (ret)
		वापस ret;

	ret = class_रेजिस्टर(&typec_mux_class);
	अगर (ret)
		जाओ err_unरेजिस्टर_bus;

	ret = class_रेजिस्टर(&typec_class);
	अगर (ret)
		जाओ err_unरेजिस्टर_mux_class;

	वापस 0;

err_unरेजिस्टर_mux_class:
	class_unरेजिस्टर(&typec_mux_class);

err_unरेजिस्टर_bus:
	bus_unरेजिस्टर(&typec_bus);

	वापस ret;
पूर्ण
subsys_initcall(typec_init);

अटल व्योम __निकास typec_निकास(व्योम)
अणु
	class_unरेजिस्टर(&typec_class);
	ida_destroy(&typec_index_ida);
	bus_unरेजिस्टर(&typec_bus);
	class_unरेजिस्टर(&typec_mux_class);
पूर्ण
module_निकास(typec_निकास);

MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("USB Type-C Connector Class");
