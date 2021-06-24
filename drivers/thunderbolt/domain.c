<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt bus support
 *
 * Copyright (C) 2017, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/dmar.h>
#समावेश <linux/idr.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <crypto/hash.h>

#समावेश "tb.h"

अटल DEFINE_IDA(tb_करोमुख्य_ida);

अटल bool match_service_id(स्थिर काष्ठा tb_service_id *id,
			     स्थिर काष्ठा tb_service *svc)
अणु
	अगर (id->match_flags & TBSVC_MATCH_PROTOCOL_KEY) अणु
		अगर (म_भेद(id->protocol_key, svc->key))
			वापस false;
	पूर्ण

	अगर (id->match_flags & TBSVC_MATCH_PROTOCOL_ID) अणु
		अगर (id->protocol_id != svc->prtcid)
			वापस false;
	पूर्ण

	अगर (id->match_flags & TBSVC_MATCH_PROTOCOL_VERSION) अणु
		अगर (id->protocol_version != svc->prtcvers)
			वापस false;
	पूर्ण

	अगर (id->match_flags & TBSVC_MATCH_PROTOCOL_VERSION) अणु
		अगर (id->protocol_revision != svc->prtcrevs)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा tb_service_id *__tb_service_match(काष्ठा device *dev,
						      काष्ठा device_driver *drv)
अणु
	काष्ठा tb_service_driver *driver;
	स्थिर काष्ठा tb_service_id *ids;
	काष्ठा tb_service *svc;

	svc = tb_to_service(dev);
	अगर (!svc)
		वापस शून्य;

	driver = container_of(drv, काष्ठा tb_service_driver, driver);
	अगर (!driver->id_table)
		वापस शून्य;

	क्रम (ids = driver->id_table; ids->match_flags != 0; ids++) अणु
		अगर (match_service_id(ids, svc))
			वापस ids;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक tb_service_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस !!__tb_service_match(dev, drv);
पूर्ण

अटल पूर्णांक tb_service_probe(काष्ठा device *dev)
अणु
	काष्ठा tb_service *svc = tb_to_service(dev);
	काष्ठा tb_service_driver *driver;
	स्थिर काष्ठा tb_service_id *id;

	driver = container_of(dev->driver, काष्ठा tb_service_driver, driver);
	id = __tb_service_match(dev, &driver->driver);

	वापस driver->probe(svc, id);
पूर्ण

अटल पूर्णांक tb_service_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tb_service *svc = tb_to_service(dev);
	काष्ठा tb_service_driver *driver;

	driver = container_of(dev->driver, काष्ठा tb_service_driver, driver);
	अगर (driver->हटाओ)
		driver->हटाओ(svc);

	वापस 0;
पूर्ण

अटल व्योम tb_service_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा tb_service_driver *driver;
	काष्ठा tb_service *svc;

	svc = tb_to_service(dev);
	अगर (!svc || !dev->driver)
		वापस;

	driver = container_of(dev->driver, काष्ठा tb_service_driver, driver);
	अगर (driver->shutकरोwn)
		driver->shutकरोwn(svc);
पूर्ण

अटल स्थिर अक्षर * स्थिर tb_security_names[] = अणु
	[TB_SECURITY_NONE] = "none",
	[TB_SECURITY_USER] = "user",
	[TB_SECURITY_SECURE] = "secure",
	[TB_SECURITY_DPONLY] = "dponly",
	[TB_SECURITY_USBONLY] = "usbonly",
	[TB_SECURITY_NOPCIE] = "nopcie",
पूर्ण;

अटल sमाप_प्रकार boot_acl_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tb *tb = container_of(dev, काष्ठा tb, dev);
	uuid_t *uuids;
	sमाप_प्रकार ret;
	पूर्णांक i;

	uuids = kसुस्मृति(tb->nboot_acl, माप(uuid_t), GFP_KERNEL);
	अगर (!uuids)
		वापस -ENOMEM;

	pm_runसमय_get_sync(&tb->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ out;
	पूर्ण
	ret = tb->cm_ops->get_boot_acl(tb, uuids, tb->nboot_acl);
	अगर (ret) अणु
		mutex_unlock(&tb->lock);
		जाओ out;
	पूर्ण
	mutex_unlock(&tb->lock);

	क्रम (ret = 0, i = 0; i < tb->nboot_acl; i++) अणु
		अगर (!uuid_is_null(&uuids[i]))
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%pUb",
					&uuids[i]);

		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%s",
			       i < tb->nboot_acl - 1 ? "," : "\n");
	पूर्ण

out:
	pm_runसमय_mark_last_busy(&tb->dev);
	pm_runसमय_put_स्वतःsuspend(&tb->dev);
	kमुक्त(uuids);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार boot_acl_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tb *tb = container_of(dev, काष्ठा tb, dev);
	अक्षर *str, *s, *uuid_str;
	sमाप_प्रकार ret = 0;
	uuid_t *acl;
	पूर्णांक i = 0;

	/*
	 * Make sure the value is not bigger than tb->nboot_acl * UUID
	 * length + commas and optional "\n". Also the smallest allowable
	 * string is tb->nboot_acl * ",".
	 */
	अगर (count > (UUID_STRING_LEN + 1) * tb->nboot_acl + 1)
		वापस -EINVAL;
	अगर (count < tb->nboot_acl - 1)
		वापस -EINVAL;

	str = kstrdup(buf, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	acl = kसुस्मृति(tb->nboot_acl, माप(uuid_t), GFP_KERNEL);
	अगर (!acl) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_str;
	पूर्ण

	uuid_str = strim(str);
	जबतक ((s = strsep(&uuid_str, ",")) != शून्य && i < tb->nboot_acl) अणु
		माप_प्रकार len = म_माप(s);

		अगर (len) अणु
			अगर (len != UUID_STRING_LEN) अणु
				ret = -EINVAL;
				जाओ err_मुक्त_acl;
			पूर्ण
			ret = uuid_parse(s, &acl[i]);
			अगर (ret)
				जाओ err_मुक्त_acl;
		पूर्ण

		i++;
	पूर्ण

	अगर (s || i < tb->nboot_acl) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_acl;
	पूर्ण

	pm_runसमय_get_sync(&tb->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ err_rpm_put;
	पूर्ण
	ret = tb->cm_ops->set_boot_acl(tb, acl, tb->nboot_acl);
	अगर (!ret) अणु
		/* Notअगरy userspace about the change */
		kobject_uevent(&tb->dev.kobj, KOBJ_CHANGE);
	पूर्ण
	mutex_unlock(&tb->lock);

err_rpm_put:
	pm_runसमय_mark_last_busy(&tb->dev);
	pm_runसमय_put_स्वतःsuspend(&tb->dev);
err_मुक्त_acl:
	kमुक्त(acl);
err_मुक्त_str:
	kमुक्त(str);

	वापस ret ?: count;
पूर्ण
अटल DEVICE_ATTR_RW(boot_acl);

अटल sमाप_प्रकार deauthorization_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	स्थिर काष्ठा tb *tb = container_of(dev, काष्ठा tb, dev);
	bool deauthorization = false;

	/* Only meaningful अगर authorization is supported */
	अगर (tb->security_level == TB_SECURITY_USER ||
	    tb->security_level == TB_SECURITY_SECURE)
		deauthorization = !!tb->cm_ops->disapprove_चयन;

	वापस प्र_लिखो(buf, "%d\n", deauthorization);
पूर्ण
अटल DEVICE_ATTR_RO(deauthorization);

अटल sमाप_प्रकार iommu_dma_protection_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	/*
	 * Kernel DMA protection is a feature where Thunderbolt security is
	 * handled natively using IOMMU. It is enabled when IOMMU is
	 * enabled and ACPI DMAR table has DMAR_PLATFORM_OPT_IN set.
	 */
	वापस प्र_लिखो(buf, "%d\n",
		       iommu_present(&pci_bus_type) && dmar_platक्रमm_optin());
पूर्ण
अटल DEVICE_ATTR_RO(iommu_dma_protection);

अटल sमाप_प्रकार security_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tb *tb = container_of(dev, काष्ठा tb, dev);
	स्थिर अक्षर *name = "unknown";

	अगर (tb->security_level < ARRAY_SIZE(tb_security_names))
		name = tb_security_names[tb->security_level];

	वापस प्र_लिखो(buf, "%s\n", name);
पूर्ण
अटल DEVICE_ATTR_RO(security);

अटल काष्ठा attribute *करोमुख्य_attrs[] = अणु
	&dev_attr_boot_acl.attr,
	&dev_attr_deauthorization.attr,
	&dev_attr_iommu_dma_protection.attr,
	&dev_attr_security.attr,
	शून्य,
पूर्ण;

अटल umode_t करोमुख्य_attr_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा tb *tb = container_of(dev, काष्ठा tb, dev);

	अगर (attr == &dev_attr_boot_acl.attr) अणु
		अगर (tb->nboot_acl &&
		    tb->cm_ops->get_boot_acl &&
		    tb->cm_ops->set_boot_acl)
			वापस attr->mode;
		वापस 0;
	पूर्ण

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group करोमुख्य_attr_group = अणु
	.is_visible = करोमुख्य_attr_is_visible,
	.attrs = करोमुख्य_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *करोमुख्य_attr_groups[] = अणु
	&करोमुख्य_attr_group,
	शून्य,
पूर्ण;

काष्ठा bus_type tb_bus_type = अणु
	.name = "thunderbolt",
	.match = tb_service_match,
	.probe = tb_service_probe,
	.हटाओ = tb_service_हटाओ,
	.shutकरोwn = tb_service_shutकरोwn,
पूर्ण;

अटल व्योम tb_करोमुख्य_release(काष्ठा device *dev)
अणु
	काष्ठा tb *tb = container_of(dev, काष्ठा tb, dev);

	tb_ctl_मुक्त(tb->ctl);
	destroy_workqueue(tb->wq);
	ida_simple_हटाओ(&tb_करोमुख्य_ida, tb->index);
	mutex_destroy(&tb->lock);
	kमुक्त(tb);
पूर्ण

काष्ठा device_type tb_करोमुख्य_type = अणु
	.name = "thunderbolt_domain",
	.release = tb_करोमुख्य_release,
पूर्ण;

अटल bool tb_करोमुख्य_event_cb(व्योम *data, क्रमागत tb_cfg_pkg_type type,
			       स्थिर व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा tb *tb = data;

	अगर (!tb->cm_ops->handle_event) अणु
		tb_warn(tb, "domain does not have event handler\n");
		वापस true;
	पूर्ण

	चयन (type) अणु
	हाल TB_CFG_PKG_XDOMAIN_REQ:
	हाल TB_CFG_PKG_XDOMAIN_RESP:
		अगर (tb_is_xकरोमुख्य_enabled())
			वापस tb_xकरोमुख्य_handle_request(tb, type, buf, size);
		अवरोध;

	शेष:
		tb->cm_ops->handle_event(tb, type, buf, size);
	पूर्ण

	वापस true;
पूर्ण

/**
 * tb_करोमुख्य_alloc() - Allocate a करोमुख्य
 * @nhi: Poपूर्णांकer to the host controller
 * @समयout_msec: Control channel समयout क्रम non-raw messages
 * @privsize: Size of the connection manager निजी data
 *
 * Allocates and initializes a new Thunderbolt करोमुख्य. Connection
 * managers are expected to call this and then fill in @cm_ops
 * accordingly.
 *
 * Call tb_करोमुख्य_put() to release the करोमुख्य beक्रमe it has been added
 * to the प्रणाली.
 *
 * Return: allocated करोमुख्य काष्ठाure on %शून्य in हाल of error
 */
काष्ठा tb *tb_करोमुख्य_alloc(काष्ठा tb_nhi *nhi, पूर्णांक समयout_msec, माप_प्रकार privsize)
अणु
	काष्ठा tb *tb;

	/*
	 * Make sure the काष्ठाure sizes map with that the hardware
	 * expects because bit-fields are being used.
	 */
	BUILD_BUG_ON(माप(काष्ठा tb_regs_चयन_header) != 5 * 4);
	BUILD_BUG_ON(माप(काष्ठा tb_regs_port_header) != 8 * 4);
	BUILD_BUG_ON(माप(काष्ठा tb_regs_hop) != 2 * 4);

	tb = kzalloc(माप(*tb) + privsize, GFP_KERNEL);
	अगर (!tb)
		वापस शून्य;

	tb->nhi = nhi;
	mutex_init(&tb->lock);

	tb->index = ida_simple_get(&tb_करोमुख्य_ida, 0, 0, GFP_KERNEL);
	अगर (tb->index < 0)
		जाओ err_मुक्त;

	tb->wq = alloc_ordered_workqueue("thunderbolt%d", 0, tb->index);
	अगर (!tb->wq)
		जाओ err_हटाओ_ida;

	tb->ctl = tb_ctl_alloc(nhi, समयout_msec, tb_करोमुख्य_event_cb, tb);
	अगर (!tb->ctl)
		जाओ err_destroy_wq;

	tb->dev.parent = &nhi->pdev->dev;
	tb->dev.bus = &tb_bus_type;
	tb->dev.type = &tb_करोमुख्य_type;
	tb->dev.groups = करोमुख्य_attr_groups;
	dev_set_name(&tb->dev, "domain%d", tb->index);
	device_initialize(&tb->dev);

	वापस tb;

err_destroy_wq:
	destroy_workqueue(tb->wq);
err_हटाओ_ida:
	ida_simple_हटाओ(&tb_करोमुख्य_ida, tb->index);
err_मुक्त:
	kमुक्त(tb);

	वापस शून्य;
पूर्ण

/**
 * tb_करोमुख्य_add() - Add करोमुख्य to the प्रणाली
 * @tb: Doमुख्य to add
 *
 * Starts the करोमुख्य and adds it to the प्रणाली. Hotplugging devices will
 * work after this has been वापसed successfully. In order to हटाओ
 * and release the करोमुख्य after this function has been called, call
 * tb_करोमुख्य_हटाओ().
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं in हाल of error
 */
पूर्णांक tb_करोमुख्य_add(काष्ठा tb *tb)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!tb->cm_ops))
		वापस -EINVAL;

	mutex_lock(&tb->lock);
	/*
	 * tb_schedule_hotplug_handler may be called as soon as the config
	 * channel is started. Thats why we have to hold the lock here.
	 */
	tb_ctl_start(tb->ctl);

	अगर (tb->cm_ops->driver_पढ़ोy) अणु
		ret = tb->cm_ops->driver_पढ़ोy(tb);
		अगर (ret)
			जाओ err_ctl_stop;
	पूर्ण

	tb_dbg(tb, "security level set to %s\n",
	       tb_security_names[tb->security_level]);

	ret = device_add(&tb->dev);
	अगर (ret)
		जाओ err_ctl_stop;

	/* Start the करोमुख्य */
	अगर (tb->cm_ops->start) अणु
		ret = tb->cm_ops->start(tb);
		अगर (ret)
			जाओ err_करोमुख्य_del;
	पूर्ण

	/* This starts event processing */
	mutex_unlock(&tb->lock);

	device_init_wakeup(&tb->dev, true);

	pm_runसमय_no_callbacks(&tb->dev);
	pm_runसमय_set_active(&tb->dev);
	pm_runसमय_enable(&tb->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&tb->dev, TB_AUTOSUSPEND_DELAY);
	pm_runसमय_mark_last_busy(&tb->dev);
	pm_runसमय_use_स्वतःsuspend(&tb->dev);

	वापस 0;

err_करोमुख्य_del:
	device_del(&tb->dev);
err_ctl_stop:
	tb_ctl_stop(tb->ctl);
	mutex_unlock(&tb->lock);

	वापस ret;
पूर्ण

/**
 * tb_करोमुख्य_हटाओ() - Removes and releases a करोमुख्य
 * @tb: Doमुख्य to हटाओ
 *
 * Stops the करोमुख्य, हटाओs it from the प्रणाली and releases all
 * resources once the last reference has been released.
 */
व्योम tb_करोमुख्य_हटाओ(काष्ठा tb *tb)
अणु
	mutex_lock(&tb->lock);
	अगर (tb->cm_ops->stop)
		tb->cm_ops->stop(tb);
	/* Stop the करोमुख्य control traffic */
	tb_ctl_stop(tb->ctl);
	mutex_unlock(&tb->lock);

	flush_workqueue(tb->wq);
	device_unरेजिस्टर(&tb->dev);
पूर्ण

/**
 * tb_करोमुख्य_suspend_noirq() - Suspend a करोमुख्य
 * @tb: Doमुख्य to suspend
 *
 * Suspends all devices in the करोमुख्य and stops the control channel.
 */
पूर्णांक tb_करोमुख्य_suspend_noirq(काष्ठा tb *tb)
अणु
	पूर्णांक ret = 0;

	/*
	 * The control channel पूर्णांकerrupt is left enabled during suspend
	 * and taking the lock here prevents any events happening beक्रमe
	 * we actually have stopped the करोमुख्य and the control channel.
	 */
	mutex_lock(&tb->lock);
	अगर (tb->cm_ops->suspend_noirq)
		ret = tb->cm_ops->suspend_noirq(tb);
	अगर (!ret)
		tb_ctl_stop(tb->ctl);
	mutex_unlock(&tb->lock);

	वापस ret;
पूर्ण

/**
 * tb_करोमुख्य_resume_noirq() - Resume a करोमुख्य
 * @tb: Doमुख्य to resume
 *
 * Re-starts the control channel, and resumes all devices connected to
 * the करोमुख्य.
 */
पूर्णांक tb_करोमुख्य_resume_noirq(काष्ठा tb *tb)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&tb->lock);
	tb_ctl_start(tb->ctl);
	अगर (tb->cm_ops->resume_noirq)
		ret = tb->cm_ops->resume_noirq(tb);
	mutex_unlock(&tb->lock);

	वापस ret;
पूर्ण

पूर्णांक tb_करोमुख्य_suspend(काष्ठा tb *tb)
अणु
	वापस tb->cm_ops->suspend ? tb->cm_ops->suspend(tb) : 0;
पूर्ण

पूर्णांक tb_करोमुख्य_मुक्तze_noirq(काष्ठा tb *tb)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&tb->lock);
	अगर (tb->cm_ops->मुक्तze_noirq)
		ret = tb->cm_ops->मुक्तze_noirq(tb);
	अगर (!ret)
		tb_ctl_stop(tb->ctl);
	mutex_unlock(&tb->lock);

	वापस ret;
पूर्ण

पूर्णांक tb_करोमुख्य_thaw_noirq(काष्ठा tb *tb)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&tb->lock);
	tb_ctl_start(tb->ctl);
	अगर (tb->cm_ops->thaw_noirq)
		ret = tb->cm_ops->thaw_noirq(tb);
	mutex_unlock(&tb->lock);

	वापस ret;
पूर्ण

व्योम tb_करोमुख्य_complete(काष्ठा tb *tb)
अणु
	अगर (tb->cm_ops->complete)
		tb->cm_ops->complete(tb);
पूर्ण

पूर्णांक tb_करोमुख्य_runसमय_suspend(काष्ठा tb *tb)
अणु
	अगर (tb->cm_ops->runसमय_suspend) अणु
		पूर्णांक ret = tb->cm_ops->runसमय_suspend(tb);
		अगर (ret)
			वापस ret;
	पूर्ण
	tb_ctl_stop(tb->ctl);
	वापस 0;
पूर्ण

पूर्णांक tb_करोमुख्य_runसमय_resume(काष्ठा tb *tb)
अणु
	tb_ctl_start(tb->ctl);
	अगर (tb->cm_ops->runसमय_resume) अणु
		पूर्णांक ret = tb->cm_ops->runसमय_resume(tb);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * tb_करोमुख्य_disapprove_चयन() - Disapprove चयन
 * @tb: Doमुख्य the चयन beदीर्घs to
 * @sw: Switch to disapprove
 *
 * This will disconnect PCIe tunnel from parent to this @sw.
 *
 * Return: %0 on success and negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक tb_करोमुख्य_disapprove_चयन(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	अगर (!tb->cm_ops->disapprove_चयन)
		वापस -EPERM;

	वापस tb->cm_ops->disapprove_चयन(tb, sw);
पूर्ण

/**
 * tb_करोमुख्य_approve_चयन() - Approve चयन
 * @tb: Doमुख्य the चयन beदीर्घs to
 * @sw: Switch to approve
 *
 * This will approve चयन by connection manager specअगरic means. In
 * हाल of success the connection manager will create PCIe tunnel from
 * parent to @sw.
 */
पूर्णांक tb_करोमुख्य_approve_चयन(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_चयन *parent_sw;

	अगर (!tb->cm_ops->approve_चयन)
		वापस -EPERM;

	/* The parent चयन must be authorized beक्रमe this one */
	parent_sw = tb_to_चयन(sw->dev.parent);
	अगर (!parent_sw || !parent_sw->authorized)
		वापस -EINVAL;

	वापस tb->cm_ops->approve_चयन(tb, sw);
पूर्ण

/**
 * tb_करोमुख्य_approve_चयन_key() - Approve चयन and add key
 * @tb: Doमुख्य the चयन beदीर्घs to
 * @sw: Switch to approve
 *
 * For चयनes that support secure connect, this function first adds
 * key to the चयन NVM using connection manager specअगरic means. If
 * adding the key is successful, the चयन is approved and connected.
 *
 * Return: %0 on success and negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक tb_करोमुख्य_approve_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_चयन *parent_sw;
	पूर्णांक ret;

	अगर (!tb->cm_ops->approve_चयन || !tb->cm_ops->add_चयन_key)
		वापस -EPERM;

	/* The parent चयन must be authorized beक्रमe this one */
	parent_sw = tb_to_चयन(sw->dev.parent);
	अगर (!parent_sw || !parent_sw->authorized)
		वापस -EINVAL;

	ret = tb->cm_ops->add_चयन_key(tb, sw);
	अगर (ret)
		वापस ret;

	वापस tb->cm_ops->approve_चयन(tb, sw);
पूर्ण

/**
 * tb_करोमुख्य_challenge_चयन_key() - Challenge and approve चयन
 * @tb: Doमुख्य the चयन beदीर्घs to
 * @sw: Switch to approve
 *
 * For चयनes that support secure connect, this function generates
 * अक्रमom challenge and sends it to the चयन. The चयन responds to
 * this and अगर the response matches our अक्रमom challenge, the चयन is
 * approved and connected.
 *
 * Return: %0 on success and negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक tb_करोमुख्य_challenge_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw)
अणु
	u8 challenge[TB_SWITCH_KEY_SIZE];
	u8 response[TB_SWITCH_KEY_SIZE];
	u8 hmac[TB_SWITCH_KEY_SIZE];
	काष्ठा tb_चयन *parent_sw;
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *shash;
	पूर्णांक ret;

	अगर (!tb->cm_ops->approve_चयन || !tb->cm_ops->challenge_चयन_key)
		वापस -EPERM;

	/* The parent चयन must be authorized beक्रमe this one */
	parent_sw = tb_to_चयन(sw->dev.parent);
	अगर (!parent_sw || !parent_sw->authorized)
		वापस -EINVAL;

	get_अक्रमom_bytes(challenge, माप(challenge));
	ret = tb->cm_ops->challenge_चयन_key(tb, sw, challenge, response);
	अगर (ret)
		वापस ret;

	tfm = crypto_alloc_shash("hmac(sha256)", 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	ret = crypto_shash_setkey(tfm, sw->key, TB_SWITCH_KEY_SIZE);
	अगर (ret)
		जाओ err_मुक्त_tfm;

	shash = kzalloc(माप(*shash) + crypto_shash_descsize(tfm),
			GFP_KERNEL);
	अगर (!shash) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_tfm;
	पूर्ण

	shash->tfm = tfm;

	स_रखो(hmac, 0, माप(hmac));
	ret = crypto_shash_digest(shash, challenge, माप(hmac), hmac);
	अगर (ret)
		जाओ err_मुक्त_shash;

	/* The वापसed HMAC must match the one we calculated */
	अगर (स_भेद(response, hmac, माप(hmac))) अणु
		ret = -EKEYREJECTED;
		जाओ err_मुक्त_shash;
	पूर्ण

	crypto_मुक्त_shash(tfm);
	kमुक्त(shash);

	वापस tb->cm_ops->approve_चयन(tb, sw);

err_मुक्त_shash:
	kमुक्त(shash);
err_मुक्त_tfm:
	crypto_मुक्त_shash(tfm);

	वापस ret;
पूर्ण

/**
 * tb_करोमुख्य_disconnect_pcie_paths() - Disconnect all PCIe paths
 * @tb: Doमुख्य whose PCIe paths to disconnect
 *
 * This needs to be called in preparation क्रम NVM upgrade of the host
 * controller. Makes sure all PCIe paths are disconnected.
 *
 * Return %0 on success and negative त्रुटि_सं in हाल of error.
 */
पूर्णांक tb_करोमुख्य_disconnect_pcie_paths(काष्ठा tb *tb)
अणु
	अगर (!tb->cm_ops->disconnect_pcie_paths)
		वापस -EPERM;

	वापस tb->cm_ops->disconnect_pcie_paths(tb);
पूर्ण

/**
 * tb_करोमुख्य_approve_xकरोमुख्य_paths() - Enable DMA paths क्रम XDoमुख्य
 * @tb: Doमुख्य enabling the DMA paths
 * @xd: XDoमुख्य DMA paths are created to
 * @transmit_path: HopID we are using to send out packets
 * @transmit_ring: DMA ring used to send out packets
 * @receive_path: HopID the other end is using to send packets to us
 * @receive_ring: DMA ring used to receive packets from @receive_path
 *
 * Calls connection manager specअगरic method to enable DMA paths to the
 * XDoमुख्य in question.
 *
 * Return: 0% in हाल of success and negative त्रुटि_सं otherwise. In
 * particular वापसs %-ENOTSUPP अगर the connection manager
 * implementation करोes not support XDoमुख्यs.
 */
पूर्णांक tb_करोमुख्य_approve_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				    पूर्णांक transmit_path, पूर्णांक transmit_ring,
				    पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	अगर (!tb->cm_ops->approve_xकरोमुख्य_paths)
		वापस -ENOTSUPP;

	वापस tb->cm_ops->approve_xकरोमुख्य_paths(tb, xd, transmit_path,
			transmit_ring, receive_path, receive_ring);
पूर्ण

/**
 * tb_करोमुख्य_disconnect_xकरोमुख्य_paths() - Disable DMA paths क्रम XDoमुख्य
 * @tb: Doमुख्य disabling the DMA paths
 * @xd: XDoमुख्य whose DMA paths are disconnected
 * @transmit_path: HopID we are using to send out packets
 * @transmit_ring: DMA ring used to send out packets
 * @receive_path: HopID the other end is using to send packets to us
 * @receive_ring: DMA ring used to receive packets from @receive_path
 *
 * Calls connection manager specअगरic method to disconnect DMA paths to
 * the XDoमुख्य in question.
 *
 * Return: 0% in हाल of success and negative त्रुटि_सं otherwise. In
 * particular वापसs %-ENOTSUPP अगर the connection manager
 * implementation करोes not support XDoमुख्यs.
 */
पूर्णांक tb_करोमुख्य_disconnect_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				       पूर्णांक transmit_path, पूर्णांक transmit_ring,
				       पूर्णांक receive_path, पूर्णांक receive_ring)
अणु
	अगर (!tb->cm_ops->disconnect_xकरोमुख्य_paths)
		वापस -ENOTSUPP;

	वापस tb->cm_ops->disconnect_xकरोमुख्य_paths(tb, xd, transmit_path,
			transmit_ring, receive_path, receive_ring);
पूर्ण

अटल पूर्णांक disconnect_xकरोमुख्य(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा tb_xकरोमुख्य *xd;
	काष्ठा tb *tb = data;
	पूर्णांक ret = 0;

	xd = tb_to_xकरोमुख्य(dev);
	अगर (xd && xd->tb == tb)
		ret = tb_xकरोमुख्य_disable_all_paths(xd);

	वापस ret;
पूर्ण

/**
 * tb_करोमुख्य_disconnect_all_paths() - Disconnect all paths क्रम the करोमुख्य
 * @tb: Doमुख्य whose paths are disconnected
 *
 * This function can be used to disconnect all paths (PCIe, XDoमुख्य) क्रम
 * example in preparation क्रम host NVM firmware upgrade. After this is
 * called the paths cannot be established without resetting the चयन.
 *
 * Return: %0 in हाल of success and negative त्रुटि_सं otherwise.
 */
पूर्णांक tb_करोमुख्य_disconnect_all_paths(काष्ठा tb *tb)
अणु
	पूर्णांक ret;

	ret = tb_करोमुख्य_disconnect_pcie_paths(tb);
	अगर (ret)
		वापस ret;

	वापस bus_क्रम_each_dev(&tb_bus_type, शून्य, tb, disconnect_xकरोमुख्य);
पूर्ण

पूर्णांक tb_करोमुख्य_init(व्योम)
अणु
	पूर्णांक ret;

	tb_test_init();

	tb_debugfs_init();
	ret = tb_xकरोमुख्य_init();
	अगर (ret)
		जाओ err_debugfs;
	ret = bus_रेजिस्टर(&tb_bus_type);
	अगर (ret)
		जाओ err_xकरोमुख्य;

	वापस 0;

err_xकरोमुख्य:
	tb_xकरोमुख्य_निकास();
err_debugfs:
	tb_debugfs_निकास();
	tb_test_निकास();

	वापस ret;
पूर्ण

व्योम tb_करोमुख्य_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&tb_bus_type);
	ida_destroy(&tb_करोमुख्य_ida);
	tb_nvm_निकास();
	tb_xकरोमुख्य_निकास();
	tb_debugfs_निकास();
	tb_test_निकास();
पूर्ण
