<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Bus क्रम USB Type-C Alternate Modes
 *
 * Copyright (C) 2018 Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/usb/pd_vकरो.h>

#समावेश "bus.h"
#समावेश "class.h"
#समावेश "mux.h"

अटल अंतरभूत पूर्णांक
typec_alपंचांगode_set_mux(काष्ठा alपंचांगode *alt, अचिन्हित दीर्घ conf, व्योम *data)
अणु
	काष्ठा typec_mux_state state;

	अगर (!alt->mux)
		वापस 0;

	state.alt = &alt->adev;
	state.mode = conf;
	state.data = data;

	वापस alt->mux->set(alt->mux, &state);
पूर्ण

अटल पूर्णांक typec_alपंचांगode_set_state(काष्ठा typec_alपंचांगode *adev,
				   अचिन्हित दीर्घ conf, व्योम *data)
अणु
	bool is_port = is_typec_port(adev->dev.parent);
	काष्ठा alपंचांगode *port_alपंचांगode;

	port_alपंचांगode = is_port ? to_alपंचांगode(adev) : to_alपंचांगode(adev)->partner;

	वापस typec_alपंचांगode_set_mux(port_alपंचांगode, conf, data);
पूर्ण

/* -------------------------------------------------------------------------- */
/* Common API */

/**
 * typec_alपंचांगode_notअगरy - Communication between the OS and alternate mode driver
 * @adev: Handle to the alternate mode
 * @conf: Alternate mode specअगरic configuration value
 * @data: Alternate mode specअगरic data
 *
 * The primary purpose क्रम this function is to allow the alternate mode drivers
 * to tell which pin configuration has been negotiated with the partner. That
 * inक्रमmation will then be used क्रम example to configure the muxes.
 * Communication to the other direction is also possible, and low level device
 * drivers can also send notअगरications to the alternate mode drivers. The actual
 * communication will be specअगरic क्रम every SVID.
 */
पूर्णांक typec_alपंचांगode_notअगरy(काष्ठा typec_alपंचांगode *adev,
			 अचिन्हित दीर्घ conf, व्योम *data)
अणु
	bool is_port;
	काष्ठा alपंचांगode *alपंचांगode;
	काष्ठा alपंचांगode *partner;
	पूर्णांक ret;

	अगर (!adev)
		वापस 0;

	alपंचांगode = to_alपंचांगode(adev);

	अगर (!alपंचांगode->partner)
		वापस -ENODEV;

	is_port = is_typec_port(adev->dev.parent);
	partner = alपंचांगode->partner;

	ret = typec_alपंचांगode_set_mux(is_port ? alपंचांगode : partner, conf, data);
	अगर (ret)
		वापस ret;

	अगर (partner->adev.ops && partner->adev.ops->notअगरy)
		वापस partner->adev.ops->notअगरy(&partner->adev, conf, data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_notअगरy);

/**
 * typec_alपंचांगode_enter - Enter Mode
 * @adev: The alternate mode
 * @vकरो: VDO क्रम the Enter Mode command
 *
 * The alternate mode drivers use this function to enter mode. The port drivers
 * use this to inक्रमm the alternate mode drivers that the partner has initiated
 * Enter Mode command. If the alternate mode करोes not require VDO, @vकरो must be
 * शून्य.
 */
पूर्णांक typec_alपंचांगode_enter(काष्ठा typec_alपंचांगode *adev, u32 *vकरो)
अणु
	काष्ठा alपंचांगode *partner = to_alपंचांगode(adev)->partner;
	काष्ठा typec_alपंचांगode *pdev = &partner->adev;
	पूर्णांक ret;

	अगर (!adev || adev->active)
		वापस 0;

	अगर (!pdev->ops || !pdev->ops->enter)
		वापस -EOPNOTSUPP;

	अगर (is_typec_port(pdev->dev.parent) && !pdev->active)
		वापस -EPERM;

	/* Moving to USB Safe State */
	ret = typec_alपंचांगode_set_state(adev, TYPEC_STATE_SAFE, शून्य);
	अगर (ret)
		वापस ret;

	/* Enter Mode */
	वापस pdev->ops->enter(pdev, vकरो);
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_enter);

/**
 * typec_alपंचांगode_निकास - Exit Mode
 * @adev: The alternate mode
 *
 * The partner of @adev has initiated Exit Mode command.
 */
पूर्णांक typec_alपंचांगode_निकास(काष्ठा typec_alपंचांगode *adev)
अणु
	काष्ठा alपंचांगode *partner = to_alपंचांगode(adev)->partner;
	काष्ठा typec_alपंचांगode *pdev = &partner->adev;
	पूर्णांक ret;

	अगर (!adev || !adev->active)
		वापस 0;

	अगर (!pdev->ops || !pdev->ops->enter)
		वापस -EOPNOTSUPP;

	/* Moving to USB Safe State */
	ret = typec_alपंचांगode_set_state(adev, TYPEC_STATE_SAFE, शून्य);
	अगर (ret)
		वापस ret;

	/* Exit Mode command */
	वापस pdev->ops->निकास(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_निकास);

/**
 * typec_alपंचांगode_attention - Attention command
 * @adev: The alternate mode
 * @vकरो: VDO क्रम the Attention command
 *
 * Notअगरies the partner of @adev about Attention command.
 */
व्योम typec_alपंचांगode_attention(काष्ठा typec_alपंचांगode *adev, u32 vकरो)
अणु
	काष्ठा typec_alपंचांगode *pdev = &to_alपंचांगode(adev)->partner->adev;

	अगर (pdev->ops && pdev->ops->attention)
		pdev->ops->attention(pdev, vकरो);
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_attention);

/**
 * typec_alपंचांगode_vdm - Send Venकरोr Defined Messages (VDM) to the partner
 * @adev: Alternate mode handle
 * @header: VDM Header
 * @vकरो: Array of Venकरोr Defined Data Objects
 * @count: Number of Data Objects
 *
 * The alternate mode drivers use this function क्रम SVID specअगरic communication
 * with the partner. The port drivers use it to deliver the Structured VDMs
 * received from the partners to the alternate mode drivers.
 */
पूर्णांक typec_alपंचांगode_vdm(काष्ठा typec_alपंचांगode *adev,
		      स्थिर u32 header, स्थिर u32 *vकरो, पूर्णांक count)
अणु
	काष्ठा typec_alपंचांगode *pdev;
	काष्ठा alपंचांगode *alपंचांगode;

	अगर (!adev)
		वापस 0;

	alपंचांगode = to_alपंचांगode(adev);

	अगर (!alपंचांगode->partner)
		वापस -ENODEV;

	pdev = &alपंचांगode->partner->adev;

	अगर (!pdev->ops || !pdev->ops->vdm)
		वापस -EOPNOTSUPP;

	वापस pdev->ops->vdm(pdev, header, vकरो, count);
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_vdm);

स्थिर काष्ठा typec_alपंचांगode *
typec_alपंचांगode_get_partner(काष्ठा typec_alपंचांगode *adev)
अणु
	अगर (!adev || !to_alपंचांगode(adev)->partner)
		वापस शून्य;

	वापस &to_alपंचांगode(adev)->partner->adev;
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_get_partner);

/* -------------------------------------------------------------------------- */
/* API क्रम the alternate mode drivers */

/**
 * typec_alपंचांगode_get_plug - Find cable plug alternate mode
 * @adev: Handle to partner alternate mode
 * @index: Cable plug index
 *
 * Increment reference count क्रम cable plug alternate mode device. Returns
 * handle to the cable plug alternate mode, or शून्य अगर none is found.
 */
काष्ठा typec_alपंचांगode *typec_alपंचांगode_get_plug(काष्ठा typec_alपंचांगode *adev,
					     क्रमागत typec_plug_index index)
अणु
	काष्ठा alपंचांगode *port = to_alपंचांगode(adev)->partner;

	अगर (port->plug[index]) अणु
		get_device(&port->plug[index]->adev.dev);
		वापस &port->plug[index]->adev;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_get_plug);

/**
 * typec_alपंचांगode_put_plug - Decrement cable plug alternate mode reference count
 * @plug: Handle to the cable plug alternate mode
 */
व्योम typec_alपंचांगode_put_plug(काष्ठा typec_alपंचांगode *plug)
अणु
	अगर (plug)
		put_device(&plug->dev);
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_put_plug);

पूर्णांक __typec_alपंचांगode_रेजिस्टर_driver(काष्ठा typec_alपंचांगode_driver *drv,
				    काष्ठा module *module)
अणु
	अगर (!drv->probe)
		वापस -EINVAL;

	drv->driver.owner = module;
	drv->driver.bus = &typec_bus;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__typec_alपंचांगode_रेजिस्टर_driver);

व्योम typec_alपंचांगode_unरेजिस्टर_driver(काष्ठा typec_alपंचांगode_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(typec_alपंचांगode_unरेजिस्टर_driver);

/* -------------------------------------------------------------------------- */
/* API क्रम the port drivers */

/**
 * typec_match_alपंचांगode - Match SVID and mode to an array of alternate modes
 * @alपंचांगodes: Array of alternate modes
 * @n: Number of elements in the array, or -1 क्रम शून्य terminated arrays
 * @svid: Standard or Venकरोr ID to match with
 * @mode: Mode to match with
 *
 * Return poपूर्णांकer to an alternate mode with SVID matching @svid, or शून्य when no
 * match is found.
 */
काष्ठा typec_alपंचांगode *typec_match_alपंचांगode(काष्ठा typec_alपंचांगode **alपंचांगodes,
					  माप_प्रकार n, u16 svid, u8 mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (!alपंचांगodes[i])
			अवरोध;
		अगर (alपंचांगodes[i]->svid == svid && alपंचांगodes[i]->mode == mode)
			वापस alपंचांगodes[i];
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(typec_match_alपंचांगode);

/* -------------------------------------------------------------------------- */

अटल sमाप_प्रकार
description_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा typec_alपंचांगode *alt = to_typec_alपंचांगode(dev);

	वापस प्र_लिखो(buf, "%s\n", alt->desc ? alt->desc : "");
पूर्ण
अटल DEVICE_ATTR_RO(description);

अटल काष्ठा attribute *typec_attrs[] = अणु
	&dev_attr_description.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(typec);

अटल पूर्णांक typec_match(काष्ठा device *dev, काष्ठा device_driver *driver)
अणु
	काष्ठा typec_alपंचांगode_driver *drv = to_alपंचांगode_driver(driver);
	काष्ठा typec_alपंचांगode *alपंचांगode = to_typec_alपंचांगode(dev);
	स्थिर काष्ठा typec_device_id *id;

	क्रम (id = drv->id_table; id->svid; id++)
		अगर (id->svid == alपंचांगode->svid &&
		    (id->mode == TYPEC_ANY_MODE || id->mode == alपंचांगode->mode))
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक typec_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा typec_alपंचांगode *alपंचांगode = to_typec_alपंचांगode(dev);

	अगर (add_uevent_var(env, "SVID=%04X", alपंचांगode->svid))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MODE=%u", alपंचांगode->mode))
		वापस -ENOMEM;

	वापस add_uevent_var(env, "MODALIAS=typec:id%04Xm%02X",
			      alपंचांगode->svid, alपंचांगode->mode);
पूर्ण

अटल पूर्णांक typec_alपंचांगode_create_links(काष्ठा alपंचांगode *alt)
अणु
	काष्ठा device *port_dev = &alt->partner->adev.dev;
	काष्ठा device *dev = &alt->adev.dev;
	पूर्णांक err;

	err = sysfs_create_link(&dev->kobj, &port_dev->kobj, "port");
	अगर (err)
		वापस err;

	err = sysfs_create_link(&port_dev->kobj, &dev->kobj, "partner");
	अगर (err)
		sysfs_हटाओ_link(&dev->kobj, "port");

	वापस err;
पूर्ण

अटल व्योम typec_alपंचांगode_हटाओ_links(काष्ठा alपंचांगode *alt)
अणु
	sysfs_हटाओ_link(&alt->partner->adev.dev.kobj, "partner");
	sysfs_हटाओ_link(&alt->adev.dev.kobj, "port");
पूर्ण

अटल पूर्णांक typec_probe(काष्ठा device *dev)
अणु
	काष्ठा typec_alपंचांगode_driver *drv = to_alपंचांगode_driver(dev->driver);
	काष्ठा typec_alपंचांगode *adev = to_typec_alपंचांगode(dev);
	काष्ठा alपंचांगode *alपंचांगode = to_alपंचांगode(adev);
	पूर्णांक ret;

	/* Fail अगर the port करोes not support the alternate mode */
	अगर (!alपंचांगode->partner)
		वापस -ENODEV;

	ret = typec_alपंचांगode_create_links(alपंचांगode);
	अगर (ret) अणु
		dev_warn(dev, "failed to create symlinks\n");
		वापस ret;
	पूर्ण

	ret = drv->probe(adev);
	अगर (ret)
		typec_alपंचांगode_हटाओ_links(alपंचांगode);

	वापस ret;
पूर्ण

अटल पूर्णांक typec_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा typec_alपंचांगode_driver *drv = to_alपंचांगode_driver(dev->driver);
	काष्ठा typec_alपंचांगode *adev = to_typec_alपंचांगode(dev);
	काष्ठा alपंचांगode *alपंचांगode = to_alपंचांगode(adev);

	typec_alपंचांगode_हटाओ_links(alपंचांगode);

	अगर (drv->हटाओ)
		drv->हटाओ(to_typec_alपंचांगode(dev));

	अगर (adev->active) अणु
		WARN_ON(typec_alपंचांगode_set_state(adev, TYPEC_STATE_SAFE, शून्य));
		typec_alपंचांगode_update_active(adev, false);
	पूर्ण

	adev->desc = शून्य;
	adev->ops = शून्य;

	वापस 0;
पूर्ण

काष्ठा bus_type typec_bus = अणु
	.name = "typec",
	.dev_groups = typec_groups,
	.match = typec_match,
	.uevent = typec_uevent,
	.probe = typec_probe,
	.हटाओ = typec_हटाओ,
पूर्ण;
