<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface System Aggregator Module (SSAM) client device registry.
 *
 * Registry क्रम non-platक्रमm/non-ACPI SSAM client devices, i.e. devices that
 * cannot be स्वतः-detected. Provides device-hubs and perक्रमms instantiation
 * क्रम these devices.
 *
 * Copyright (C) 2020-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/device.h>


/* -- Device registry. ------------------------------------------------------ */

/*
 * SSAM device names follow the SSAM module alias, meaning they are prefixed
 * with 'ssam:', followed by करोमुख्य, category, target ID, instance ID, and
 * function, each encoded as two-digit hexadecimal, separated by ':'. In other
 * words, it follows the scheme
 *
 *      ssam:dd:cc:tt:ii:ff
 *
 * Where, 'dd', 'cc', 'tt', 'ii', and 'ff' are the two-digit hexadecimal
 * values mentioned above, respectively.
 */

/* Root node. */
अटल स्थिर काष्ठा software_node ssam_node_root = अणु
	.name = "ssam_platform_hub",
पूर्ण;

/* Base device hub (devices attached to Surface Book 3 base). */
अटल स्थिर काष्ठा software_node ssam_node_hub_base = अणु
	.name = "ssam:00:00:02:00:00",
	.parent = &ssam_node_root,
पूर्ण;

/* AC adapter. */
अटल स्थिर काष्ठा software_node ssam_node_bat_ac = अणु
	.name = "ssam:01:02:01:01:01",
	.parent = &ssam_node_root,
पूर्ण;

/* Primary battery. */
अटल स्थिर काष्ठा software_node ssam_node_bat_मुख्य = अणु
	.name = "ssam:01:02:01:01:00",
	.parent = &ssam_node_root,
पूर्ण;

/* Secondary battery (Surface Book 3). */
अटल स्थिर काष्ठा software_node ssam_node_bat_sb3base = अणु
	.name = "ssam:01:02:02:01:00",
	.parent = &ssam_node_hub_base,
पूर्ण;

/* Platक्रमm profile / perक्रमmance-mode device. */
अटल स्थिर काष्ठा software_node ssam_node_पंचांगp_pprof = अणु
	.name = "ssam:01:03:01:00:01",
	.parent = &ssam_node_root,
पूर्ण;

/* DTX / detachment-प्रणाली device (Surface Book 3). */
अटल स्थिर काष्ठा software_node ssam_node_bas_dtx = अणु
	.name = "ssam:01:11:01:00:00",
	.parent = &ssam_node_root,
पूर्ण;

/* HID keyboard. */
अटल स्थिर काष्ठा software_node ssam_node_hid_मुख्य_keyboard = अणु
	.name = "ssam:01:15:02:01:00",
	.parent = &ssam_node_root,
पूर्ण;

/* HID touchpad. */
अटल स्थिर काष्ठा software_node ssam_node_hid_मुख्य_touchpad = अणु
	.name = "ssam:01:15:02:03:00",
	.parent = &ssam_node_root,
पूर्ण;

/* HID device instance 5 (unknown HID device). */
अटल स्थिर काष्ठा software_node ssam_node_hid_मुख्य_iid5 = अणु
	.name = "ssam:01:15:02:05:00",
	.parent = &ssam_node_root,
पूर्ण;

/* HID keyboard (base hub). */
अटल स्थिर काष्ठा software_node ssam_node_hid_base_keyboard = अणु
	.name = "ssam:01:15:02:01:00",
	.parent = &ssam_node_hub_base,
पूर्ण;

/* HID touchpad (base hub). */
अटल स्थिर काष्ठा software_node ssam_node_hid_base_touchpad = अणु
	.name = "ssam:01:15:02:03:00",
	.parent = &ssam_node_hub_base,
पूर्ण;

/* HID device instance 5 (unknown HID device, base hub). */
अटल स्थिर काष्ठा software_node ssam_node_hid_base_iid5 = अणु
	.name = "ssam:01:15:02:05:00",
	.parent = &ssam_node_hub_base,
पूर्ण;

/* HID device instance 6 (unknown HID device, base hub). */
अटल स्थिर काष्ठा software_node ssam_node_hid_base_iid6 = अणु
	.name = "ssam:01:15:02:06:00",
	.parent = &ssam_node_hub_base,
पूर्ण;

/* Devices क्रम Surface Book 2. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sb2[] = अणु
	&ssam_node_root,
	&ssam_node_पंचांगp_pprof,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Book 3. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sb3[] = अणु
	&ssam_node_root,
	&ssam_node_hub_base,
	&ssam_node_bat_ac,
	&ssam_node_bat_मुख्य,
	&ssam_node_bat_sb3base,
	&ssam_node_पंचांगp_pprof,
	&ssam_node_bas_dtx,
	&ssam_node_hid_base_keyboard,
	&ssam_node_hid_base_touchpad,
	&ssam_node_hid_base_iid5,
	&ssam_node_hid_base_iid6,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Laptop 1. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sl1[] = अणु
	&ssam_node_root,
	&ssam_node_पंचांगp_pprof,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Laptop 2. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sl2[] = अणु
	&ssam_node_root,
	&ssam_node_पंचांगp_pprof,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Laptop 3 and 4. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sl3[] = अणु
	&ssam_node_root,
	&ssam_node_bat_ac,
	&ssam_node_bat_मुख्य,
	&ssam_node_पंचांगp_pprof,
	&ssam_node_hid_मुख्य_keyboard,
	&ssam_node_hid_मुख्य_touchpad,
	&ssam_node_hid_मुख्य_iid5,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Laptop Go. */
अटल स्थिर काष्ठा software_node *ssam_node_group_slg1[] = अणु
	&ssam_node_root,
	&ssam_node_bat_ac,
	&ssam_node_bat_मुख्य,
	&ssam_node_पंचांगp_pprof,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Pro 5. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sp5[] = अणु
	&ssam_node_root,
	&ssam_node_पंचांगp_pprof,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Pro 6. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sp6[] = अणु
	&ssam_node_root,
	&ssam_node_पंचांगp_pprof,
	शून्य,
पूर्ण;

/* Devices क्रम Surface Pro 7 and Surface Pro 7+. */
अटल स्थिर काष्ठा software_node *ssam_node_group_sp7[] = अणु
	&ssam_node_root,
	&ssam_node_bat_ac,
	&ssam_node_bat_मुख्य,
	&ssam_node_पंचांगp_pprof,
	शून्य,
पूर्ण;


/* -- Device registry helper functions. ------------------------------------- */

अटल पूर्णांक ssam_uid_from_string(स्थिर अक्षर *str, काष्ठा ssam_device_uid *uid)
अणु
	u8 d, tc, tid, iid, fn;
	पूर्णांक n;

	n = माला_पूछो(str, "ssam:%hhx:%hhx:%hhx:%hhx:%hhx", &d, &tc, &tid, &iid, &fn);
	अगर (n != 5)
		वापस -EINVAL;

	uid->करोमुख्य = d;
	uid->category = tc;
	uid->target = tid;
	uid->instance = iid;
	uid->function = fn;

	वापस 0;
पूर्ण

अटल पूर्णांक ssam_hub_हटाओ_devices_fn(काष्ठा device *dev, व्योम *data)
अणु
	अगर (!is_ssam_device(dev))
		वापस 0;

	ssam_device_हटाओ(to_ssam_device(dev));
	वापस 0;
पूर्ण

अटल व्योम ssam_hub_हटाओ_devices(काष्ठा device *parent)
अणु
	device_क्रम_each_child_reverse(parent, शून्य, ssam_hub_हटाओ_devices_fn);
पूर्ण

अटल पूर्णांक ssam_hub_add_device(काष्ठा device *parent, काष्ठा ssam_controller *ctrl,
			       काष्ठा fwnode_handle *node)
अणु
	काष्ठा ssam_device_uid uid;
	काष्ठा ssam_device *sdev;
	पूर्णांक status;

	status = ssam_uid_from_string(fwnode_get_name(node), &uid);
	अगर (status)
		वापस status;

	sdev = ssam_device_alloc(ctrl, uid);
	अगर (!sdev)
		वापस -ENOMEM;

	sdev->dev.parent = parent;
	sdev->dev.fwnode = node;

	status = ssam_device_add(sdev);
	अगर (status)
		ssam_device_put(sdev);

	वापस status;
पूर्ण

अटल पूर्णांक ssam_hub_add_devices(काष्ठा device *parent, काष्ठा ssam_controller *ctrl,
				काष्ठा fwnode_handle *node)
अणु
	काष्ठा fwnode_handle *child;
	पूर्णांक status;

	fwnode_क्रम_each_child_node(node, child) अणु
		/*
		 * Try to add the device specअगरied in the firmware node. If
		 * this fails with -EINVAL, the node करोes not specअगरy any SSAM
		 * device, so ignore it and जारी with the next one.
		 */

		status = ssam_hub_add_device(parent, ctrl, child);
		अगर (status && status != -EINVAL)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	ssam_hub_हटाओ_devices(parent);
	वापस status;
पूर्ण


/* -- SSAM base-hub driver. ------------------------------------------------- */

/*
 * Some devices (especially battery) may need a bit of समय to be fully usable
 * after being (re-)connected. This delay has been determined via
 * experimentation.
 */
#घोषणा SSAM_BASE_UPDATE_CONNECT_DELAY		msecs_to_jअगरfies(2500)

क्रमागत ssam_base_hub_state अणु
	SSAM_BASE_HUB_UNINITIALIZED,
	SSAM_BASE_HUB_CONNECTED,
	SSAM_BASE_HUB_DISCONNECTED,
पूर्ण;

काष्ठा ssam_base_hub अणु
	काष्ठा ssam_device *sdev;

	क्रमागत ssam_base_hub_state state;
	काष्ठा delayed_work update_work;

	काष्ठा ssam_event_notअगरier notअगर;
पूर्ण;

SSAM_DEFINE_SYNC_REQUEST_R(ssam_bas_query_opmode, u8, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x0d,
	.instance_id     = 0x00,
पूर्ण);

#घोषणा SSAM_BAS_OPMODE_TABLET		0x00
#घोषणा SSAM_EVENT_BAS_CID_CONNECTION	0x0c

अटल पूर्णांक ssam_base_hub_query_state(काष्ठा ssam_base_hub *hub, क्रमागत ssam_base_hub_state *state)
अणु
	u8 opmode;
	पूर्णांक status;

	status = ssam_retry(ssam_bas_query_opmode, hub->sdev->ctrl, &opmode);
	अगर (status < 0) अणु
		dev_err(&hub->sdev->dev, "failed to query base state: %d\n", status);
		वापस status;
	पूर्ण

	अगर (opmode != SSAM_BAS_OPMODE_TABLET)
		*state = SSAM_BASE_HUB_CONNECTED;
	अन्यथा
		*state = SSAM_BASE_HUB_DISCONNECTED;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ssam_base_hub_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा ssam_base_hub *hub = dev_get_drvdata(dev);
	bool connected = hub->state == SSAM_BASE_HUB_CONNECTED;

	वापस sysfs_emit(buf, "%d\n", connected);
पूर्ण

अटल काष्ठा device_attribute ssam_base_hub_attr_state =
	__ATTR(state, 0444, ssam_base_hub_state_show, शून्य);

अटल काष्ठा attribute *ssam_base_hub_attrs[] = अणु
	&ssam_base_hub_attr_state.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ssam_base_hub_group = अणु
	.attrs = ssam_base_hub_attrs,
पूर्ण;

अटल व्योम ssam_base_hub_update_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssam_base_hub *hub = container_of(work, काष्ठा ssam_base_hub, update_work.work);
	काष्ठा fwnode_handle *node = dev_fwnode(&hub->sdev->dev);
	क्रमागत ssam_base_hub_state state;
	पूर्णांक status = 0;

	status = ssam_base_hub_query_state(hub, &state);
	अगर (status)
		वापस;

	अगर (hub->state == state)
		वापस;
	hub->state = state;

	अगर (hub->state == SSAM_BASE_HUB_CONNECTED)
		status = ssam_hub_add_devices(&hub->sdev->dev, hub->sdev->ctrl, node);
	अन्यथा
		ssam_hub_हटाओ_devices(&hub->sdev->dev);

	अगर (status)
		dev_err(&hub->sdev->dev, "failed to update base-hub devices: %d\n", status);
पूर्ण

अटल u32 ssam_base_hub_notअगर(काष्ठा ssam_event_notअगरier *nf, स्थिर काष्ठा ssam_event *event)
अणु
	काष्ठा ssam_base_hub *hub = container_of(nf, काष्ठा ssam_base_hub, notअगर);
	अचिन्हित दीर्घ delay;

	अगर (event->command_id != SSAM_EVENT_BAS_CID_CONNECTION)
		वापस 0;

	अगर (event->length < 1) अणु
		dev_err(&hub->sdev->dev, "unexpected payload size: %u\n", event->length);
		वापस 0;
	पूर्ण

	/*
	 * Delay update when the base is being connected to give devices/EC
	 * some समय to set up.
	 */
	delay = event->data[0] ? SSAM_BASE_UPDATE_CONNECT_DELAY : 0;

	schedule_delayed_work(&hub->update_work, delay);

	/*
	 * Do not वापस SSAM_NOTIF_HANDLED: The event should be picked up and
	 * consumed by the detachment प्रणाली driver. We're just a (more or less)
	 * silent observer.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ssam_base_hub_resume(काष्ठा device *dev)
अणु
	काष्ठा ssam_base_hub *hub = dev_get_drvdata(dev);

	schedule_delayed_work(&hub->update_work, 0);
	वापस 0;
पूर्ण
अटल SIMPLE_DEV_PM_OPS(ssam_base_hub_pm_ops, शून्य, ssam_base_hub_resume);

अटल पूर्णांक ssam_base_hub_probe(काष्ठा ssam_device *sdev)
अणु
	काष्ठा ssam_base_hub *hub;
	पूर्णांक status;

	hub = devm_kzalloc(&sdev->dev, माप(*hub), GFP_KERNEL);
	अगर (!hub)
		वापस -ENOMEM;

	hub->sdev = sdev;
	hub->state = SSAM_BASE_HUB_UNINITIALIZED;

	hub->notअगर.base.priority = पूर्णांक_उच्च;  /* This notअगरier should run first. */
	hub->notअगर.base.fn = ssam_base_hub_notअगर;
	hub->notअगर.event.reg = SSAM_EVENT_REGISTRY_SAM;
	hub->notअगर.event.id.target_category = SSAM_SSH_TC_BAS,
	hub->notअगर.event.id.instance = 0,
	hub->notअगर.event.mask = SSAM_EVENT_MASK_NONE;
	hub->notअगर.event.flags = SSAM_EVENT_SEQUENCED;

	INIT_DELAYED_WORK(&hub->update_work, ssam_base_hub_update_workfn);

	ssam_device_set_drvdata(sdev, hub);

	status = ssam_notअगरier_रेजिस्टर(sdev->ctrl, &hub->notअगर);
	अगर (status)
		वापस status;

	status = sysfs_create_group(&sdev->dev.kobj, &ssam_base_hub_group);
	अगर (status)
		जाओ err;

	schedule_delayed_work(&hub->update_work, 0);
	वापस 0;

err:
	ssam_notअगरier_unरेजिस्टर(sdev->ctrl, &hub->notअगर);
	cancel_delayed_work_sync(&hub->update_work);
	ssam_hub_हटाओ_devices(&sdev->dev);
	वापस status;
पूर्ण

अटल व्योम ssam_base_hub_हटाओ(काष्ठा ssam_device *sdev)
अणु
	काष्ठा ssam_base_hub *hub = ssam_device_get_drvdata(sdev);

	sysfs_हटाओ_group(&sdev->dev.kobj, &ssam_base_hub_group);

	ssam_notअगरier_unरेजिस्टर(sdev->ctrl, &hub->notअगर);
	cancel_delayed_work_sync(&hub->update_work);
	ssam_hub_हटाओ_devices(&sdev->dev);
पूर्ण

अटल स्थिर काष्ठा ssam_device_id ssam_base_hub_match[] = अणु
	अणु SSAM_VDEV(HUB, 0x02, SSAM_ANY_IID, 0x00) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ssam_device_driver ssam_base_hub_driver = अणु
	.probe = ssam_base_hub_probe,
	.हटाओ = ssam_base_hub_हटाओ,
	.match_table = ssam_base_hub_match,
	.driver = अणु
		.name = "surface_aggregator_base_hub",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm = &ssam_base_hub_pm_ops,
	पूर्ण,
पूर्ण;


/* -- SSAM platक्रमm/meta-hub driver. ---------------------------------------- */

अटल स्थिर काष्ठा acpi_device_id ssam_platक्रमm_hub_match[] = अणु
	/* Surface Pro 4, 5, and 6 (OMBR < 0x10) */
	अणु "MSHW0081", (अचिन्हित दीर्घ)ssam_node_group_sp5 पूर्ण,

	/* Surface Pro 6 (OMBR >= 0x10) */
	अणु "MSHW0111", (अचिन्हित दीर्घ)ssam_node_group_sp6 पूर्ण,

	/* Surface Pro 7 */
	अणु "MSHW0116", (अचिन्हित दीर्घ)ssam_node_group_sp7 पूर्ण,

	/* Surface Pro 7+ */
	अणु "MSHW0119", (अचिन्हित दीर्घ)ssam_node_group_sp7 पूर्ण,

	/* Surface Book 2 */
	अणु "MSHW0107", (अचिन्हित दीर्घ)ssam_node_group_sb2 पूर्ण,

	/* Surface Book 3 */
	अणु "MSHW0117", (अचिन्हित दीर्घ)ssam_node_group_sb3 पूर्ण,

	/* Surface Laptop 1 */
	अणु "MSHW0086", (अचिन्हित दीर्घ)ssam_node_group_sl1 पूर्ण,

	/* Surface Laptop 2 */
	अणु "MSHW0112", (अचिन्हित दीर्घ)ssam_node_group_sl2 पूर्ण,

	/* Surface Laptop 3 (13", Intel) */
	अणु "MSHW0114", (अचिन्हित दीर्घ)ssam_node_group_sl3 पूर्ण,

	/* Surface Laptop 3 (15", AMD) and 4 (15", AMD) */
	अणु "MSHW0110", (अचिन्हित दीर्घ)ssam_node_group_sl3 पूर्ण,

	/* Surface Laptop 4 (13", Intel) */
	अणु "MSHW0250", (अचिन्हित दीर्घ)ssam_node_group_sl3 पूर्ण,

	/* Surface Laptop Go 1 */
	अणु "MSHW0118", (अचिन्हित दीर्घ)ssam_node_group_slg1 पूर्ण,

	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ssam_platक्रमm_hub_match);

अटल पूर्णांक ssam_platक्रमm_hub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा software_node **nodes;
	काष्ठा ssam_controller *ctrl;
	काष्ठा fwnode_handle *root;
	पूर्णांक status;

	nodes = (स्थिर काष्ठा software_node **)acpi_device_get_match_data(&pdev->dev);
	अगर (!nodes)
		वापस -ENODEV;

	/*
	 * As we're adding the SSAM client devices as children under this device
	 * and not the SSAM controller, we need to add a device link to the
	 * controller to ensure that we हटाओ all of our devices beक्रमe the
	 * controller is हटाओd. This also guarantees proper ordering क्रम
	 * suspend/resume of the devices on this hub.
	 */
	ctrl = ssam_client_bind(&pdev->dev);
	अगर (IS_ERR(ctrl))
		वापस PTR_ERR(ctrl) == -ENODEV ? -EPROBE_DEFER : PTR_ERR(ctrl);

	status = software_node_रेजिस्टर_node_group(nodes);
	अगर (status)
		वापस status;

	root = software_node_fwnode(&ssam_node_root);
	अगर (!root) अणु
		software_node_unरेजिस्टर_node_group(nodes);
		वापस -ENOENT;
	पूर्ण

	set_secondary_fwnode(&pdev->dev, root);

	status = ssam_hub_add_devices(&pdev->dev, ctrl, root);
	अगर (status) अणु
		set_secondary_fwnode(&pdev->dev, शून्य);
		software_node_unरेजिस्टर_node_group(nodes);
	पूर्ण

	platक्रमm_set_drvdata(pdev, nodes);
	वापस status;
पूर्ण

अटल पूर्णांक ssam_platक्रमm_hub_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा software_node **nodes = platक्रमm_get_drvdata(pdev);

	ssam_hub_हटाओ_devices(&pdev->dev);
	set_secondary_fwnode(&pdev->dev, शून्य);
	software_node_unरेजिस्टर_node_group(nodes);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ssam_platक्रमm_hub_driver = अणु
	.probe = ssam_platक्रमm_hub_probe,
	.हटाओ = ssam_platक्रमm_hub_हटाओ,
	.driver = अणु
		.name = "surface_aggregator_platform_hub",
		.acpi_match_table = ssam_platक्रमm_hub_match,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;


/* -- Module initialization. ------------------------------------------------ */

अटल पूर्णांक __init ssam_device_hub_init(व्योम)
अणु
	पूर्णांक status;

	status = platक्रमm_driver_रेजिस्टर(&ssam_platक्रमm_hub_driver);
	अगर (status)
		वापस status;

	status = ssam_device_driver_रेजिस्टर(&ssam_base_hub_driver);
	अगर (status)
		platक्रमm_driver_unरेजिस्टर(&ssam_platक्रमm_hub_driver);

	वापस status;
पूर्ण
module_init(ssam_device_hub_init);

अटल व्योम __निकास ssam_device_hub_निकास(व्योम)
अणु
	ssam_device_driver_unरेजिस्टर(&ssam_base_hub_driver);
	platक्रमm_driver_unरेजिस्टर(&ssam_platक्रमm_hub_driver);
पूर्ण
module_निकास(ssam_device_hub_निकास);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Device-registry for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
